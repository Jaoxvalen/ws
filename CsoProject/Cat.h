#pragma once
#include <math.h>
#include "Globals.h"
#include "Classe.h"
#include "Teacher.h"
#include "Utils.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Cat
{
public:
    Cat()
    {
    }
    Cat(vector<vector<int> > _self)
    {
        self = _self;
    }
    
    // int self[nClassMax][35];
    vector<vector<int> > self;
    void createCat(int nClass, vector<Classe>& classes)
    {
        self.resize(nClass, vector<int>(35));
        for(int j = 0; j < nClass; j++) {
            // seteamos los valores por defecto de teachersOfClassAndHoursRemaining para luego ir asignando y restando
            for(int i = 0; i < classes[j].numberOfTeachers; i++) {
                for(int k = 0; k < 3; k++) {
                    classes[j].teachersOfClassAndHoursRemaining[i][k] = classes[j].teachersOfClassAndHours[i][k];
                }
            }
        }

        for(int j = 0; j < nClass; j++) {
            // seteamos los slots -1 por defecto
            for(int timeslot = 0; timeslot < 35; timeslot++) {
                self[j][timeslot] = -1;
            }

            for(int i = 0; i < classes[j].numberOfTeachers; i++) {
                while(classes[j].teachersOfClassAndHoursRemaining[i][1] > 0) {
                    int timeslot = Utils::randint(0, 34);
                    if(self[j][timeslot] == -1) {
                        self[j][timeslot] = classes[j].teachersOfClassAndHours[i][0];
                        classes[j].teachersOfClassAndHoursRemaining[i][1]--;
                    }
                }
            }
        }
        // regresamos la configuracion de las horas restantes para que no afecte a los demas gatos
        for(int j = 0; j < nClass; j++) {
            for(int i = 0; i < classes[j].numberOfTeachers; i++) {
                for(int k = 0; k < 3; k++) {
                    classes[j].teachersOfClassAndHoursRemaining[i][k] = classes[j].teachersOfClassAndHours[i][k];
                }
            }
        }
    }

    void move(bool seek,
              bool isCoteaching,
              Cat oLeader,
              vector<Classe>& classes,
              vector<Teacher>& teachers,
              int mCoClass[nClassMax][nTeachersMax],
              int mCoTeacher[nTeachersMax][nClassMax])
    {
        if(seek) {
            moveSeek(isCoteaching, oLeader, classes, teachers, mCoClass, mCoTeacher);
        } else {
            moveTrace(classes.size(), oLeader, teachers, mCoClass, mCoTeacher);
        }
    }

    void moveSeek(bool isCoteaching,
                  Cat BestGlobal,
                  vector<Classe>& classes,
                  vector<Teacher>& teachers,
                  int mCoClass[nClassMax][nTeachersMax],
                  int mCoTeacher[nTeachersMax][nClassMax])
    {
        double nFitness, nBestFitness;
        vector<double> fs(nSMP);
        vector<double> cfs(nSMP);
        vector<double> prob(nSMP);
        Cat auxCat, auxCat2;
        vector<int> mCelsRandom(35);
        vector<int> mCelsRandom1(35);
        vector<int> mClassRandom(classes.size());
        
        nBestFitness = calculateFitness(isCoteaching, classes, teachers, mCoClass, mCoTeacher, 0, 35);
        int j =
            nSMP -
            nSPC; // Numero de copias del gato, si SPC es 1 entonces consideramos la pos actual como candidato tambien
        vector<Cat> catsCopys;
        // tc = CDC*Number_of_time_slots , Note: total number of timeslots to be replaced
        int k;

        for(int i = 0; i < nSMP; i++) {
            Cat copy(self);
            catsCopys.push_back(copy);
        }

        int tc = floor(((double)nCDC / 100) * 35);
        if(tc <= 0)
            tc = 1;
        // sm = SRD*Number_of_classes*Number_of_time_slots , Note: total number of swaps to be made
        int sm = floor(((double)nSRD / 100) * (double)classes.size() * 35);

        for(int i = 0; i < j; i++) {
            
            auxCat.self = catsCopys[i].self;
            // change random procedure
            
            createSuffleVector(mCelsRandom); // creamos el randonint

            for(int tci = 0; tci < tc; tci++) {
                insertColum(isCoteaching,
                            classes,
                            teachers,
                            mCoClass,
                            mCoTeacher,
                            BestGlobal.self,
                            auxCat.self,
                            mCelsRandom[tci],
                            0,
                            35);
                auxCat2.self = auxCat.self; // guardamos una copia del gato a evaluar
                // hacemos single swap a la copia del gato
                createSuffleVector(mCelsRandom1); // creamos el randonint
                createSuffleVector(mClassRandom);

                for(int smi = 0; smi < sm; smi++) {
                    bool isValid = auxCat.singleSwap(mCelsRandom1[1],
                                                     mCelsRandom1[2],
                                                     mClassRandom[1],
                                                     classes.size(),
                                                     teachers,
                                                     mCoClass,
                                                     mCoTeacher);
                    random_shuffle(mCelsRandom1.begin(), mCelsRandom1.end());
                    random_shuffle(mClassRandom.begin(), mClassRandom.end());
                    if(isValid) {
                        nFitness =
                            auxCat.calculateFitness(isCoteaching, classes, teachers, mCoClass, mCoTeacher, 0, 35);
                        if(nFitness <= nBestFitness) {
                            nBestFitness = nFitness;
                            fs[i] = nFitness;
                            cfs[i] = nFitness;
                            catsCopys[i].self = auxCat.self;
                        }
                        auxCat.self = auxCat2.self;
                    }
                }
            }
        }
        if(nSPC == 1) // el ultimo es nuestro gato original
        {
            fs[nSMP - 1] =
                catsCopys[nSMP - 1].calculateFitness(isCoteaching, classes, teachers, mCoClass, mCoTeacher, 0, 35);
            cfs[nSMP - 1] = fs[nSMP - 1];
        }
        for(int i = 0; i < nSMP; i++) {
            for(int j = 1; j < nSMP; j++)
                if(cfs[j] < cfs[j - 1]) {
                    k = cfs[j - 1];
                    cfs[j - 1] = cfs[j];
                    cfs[j] = k;
                }
        }

        int nFitnessMax = cfs[nSMP - 1];
        int nFitnessMin = cfs[0];

        if(nFitnessMax == nFitnessMin) {
            int selectCat = Utils::randint(0, nSMP - 1);
            self = catsCopys[selectCat].self;
        } else {
            for(int i = 0; i < nSMP; i++) {
                prob[i] = fabs(fs[i] - nFitnessMax) / (nFitnessMax - nFitnessMin);
            }

            double probMacth = Utils::randdouble(0.0, 1.0);

            for(int i = 0; i < nSMP; i++) {
                if(probMacth <= prob[i]) {
                    self = catsCopys[i].self;
                }
            }
        }
    }

    void moveTrace(int nClass,
                   Cat oLeader,
                   vector<Teacher>& teachers,
                   int mCoClass[nClassMax][nTeachersMax],
                   int mCoTeacher[nTeachersMax][nClassMax])
    {
        int similaridad = 0;
        // calculamos la similaridad, oomprarando celda a celda
        for(int k = 0; k < nClass; k++) {
            for(int j = 0; j < 35; j++) {
                if(self[k][j] == oLeader.self[k][j]) {
                    similaridad++;
                }
            }
        }

        // ahora sacamos la distacis (el maximo valor del gato leader): numeroClases*timeSlots (nClass*35)
        int distance = nClass * 35;
        // calculamos cs (cantidad de celdas a cambiar) tal como dice el CSO original: R1(un random enre 0 y 1) *
        // distance
        double cs = round(Utils::randdouble(0.0, 1.0) * distance);

        vector<int> mCelsRandom(35);
        createSuffleVector(mCelsRandom);
        vector<int> mClassRandom(nClass);
        createSuffleVector(mClassRandom);

        // hacemos cs numeros de swaps aleatorios
        for(int i = 0; i < cs; i++) {
            singleSwap(mCelsRandom[1], mCelsRandom[2], mClassRandom[1], nClass, teachers, mCoClass, mCoTeacher);
            random_shuffle(mCelsRandom.begin(), mCelsRandom.end());
            random_shuffle(mClassRandom.begin(), mClassRandom.end());
        }
    }
    // funciones auxiliares del gato:

    // sustituye una columna de un catCopy por una del leader
    void insertColum(bool isCoteaching,
                     vector<Classe>& classes,
                     vector<Teacher>& teachers,
                     int mCoClass[nClassMax][nTeachersMax],
                     int mCoTeacher[nTeachersMax][nClassMax],
                     vector<vector<int> >& source,
                     vector<vector<int> >& destination,
                     int nColumn,
                     int begin,
                     int end)
    {
        int i, j, jj, temp;
        int aux[21];
        double store_positions_and_fitness[2][21], ff, smaller_fitness;
        int index, z, skip;

        for(i = 0; i < classes.size(); i++) {
            if((nColumn == 6 || nColumn == 13 || nColumn == 20 || nColumn == 27 || nColumn == 34) &&
               destination[i][nColumn] == -1) {
                continue;
            }

            if(destination[i][nColumn] == source[i][nColumn]) {
                continue;
            }

            jj = 0;

            for(j = begin; j < end; j++) {
                if(destination[i][j] == source[i][nColumn] && j != nColumn) {
                    aux[jj] = j;
                    jj++;
                }
            }
            skip = 0;
            for(z = 0; z < jj; z++) {
                if(aux[z] == nColumn) {
                    skip = 1;
                    continue;
                }

                // swap int
                temp = destination[i][aux[z]];
                destination[i][aux[z]] = destination[i][nColumn];
                destination[i][nColumn] = temp;

                ff = calculateFitness(isCoteaching, classes, teachers, mCoClass, mCoTeacher, 0, 35);

                if(skip == 0) {
                    store_positions_and_fitness[0][z] = aux[z];
                    store_positions_and_fitness[1][z] = ff;
                } else {
                    store_positions_and_fitness[0][z - 1] = aux[z];
                    store_positions_and_fitness[1][z - 1] = ff;
                }

                temp = destination[i][aux[z]];
                destination[i][aux[z]] = destination[i][nColumn];
                destination[i][nColumn] = temp;
            }

            smaller_fitness = inf;
            index = 0;
            for(z = 0; z < jj; z++) {
                if(store_positions_and_fitness[1][z] < smaller_fitness) {
                    smaller_fitness = store_positions_and_fitness[1][z];
                    index = z;
                }
            }

            int temp = destination[i][aux[index]];
            destination[i][aux[index]] = destination[i][nColumn];
            destination[i][nColumn] = temp;
        }
    }

    void createSuffleVector(vector<int>& v)
    {
        for(int i = 0; i < v.size(); i++) {
            v[i] = i;
        }
        random_shuffle(v.begin(), v.end());
    }

    // cambia el valor de dos celdas de una misma clase(fila) si se cumplen las condiciones definidas en el paper:
    bool singleSwap(int timeslot1,
                    int timeslot2,
                    int nFila,
                    int nClass,
                    vector<Teacher>& teachers,
                    int mCoClass[nClassMax][nTeachersMax],
                    int mCoTeacher[nTeachersMax][nClassMax])
    {
        int i, co_class1, co_teacher1;

        if(timeslot1 == timeslot2) // misma posicion
            return false;
        if(self[nFila][timeslot1] == self[nFila][timeslot2]) // mismo teacher
            return false;
        if(self[nFila][timeslot1] == -1 || self[nFila][timeslot2] == -1) // no esta asignada
            return false;

        // si no rompe la restriccion de que el teacher enseña en la misma hora en otra clase
        for(i = 0; i < nClass; i++) {
            if(self[i][timeslot1] == self[nFila][timeslot2])
                return false;
            if(self[i][timeslot2] == self[nFila][timeslot1])
                return false;
        }

        swap(nFila, timeslot1, timeslot2);

        // si son coteacher debemos acualizar los valores de los co-teachers y hacer el swap para ellos
        if(teachers[self[nFila][timeslot1]].isCoteacher == 1) {
            int nCoClass = mCoClass[nFila][self[nFila][timeslot1]];
            int nCoTeacher = mCoTeacher[self[nFila][timeslot1]][nFila];
            if(nCoClass != -1 && ((nCoTeacher < 0 && self[nCoClass][timeslot1] == -nCoTeacher) ||
                                  (nCoTeacher > 0 && self[nCoClass][timeslot1] == nCoTeacher)))
                swap(nCoClass, timeslot1, timeslot2);
        }
        return true;
    }

    int swap(int nFila, int timeslot1, int timeslot2)
    { // swaps two timeslots
        int temp = self[nFila][timeslot1];
        self[nFila][timeslot1] = self[nFila][timeslot2];
        self[nFila][timeslot2] = temp;
        return 1;
    }

    // fin de funciones axuiliares

    double calculateFitness(bool isCoteaching,
                            vector<Classe>& classes,
                            vector<Teacher>& teachers,
                            int mCoClass[nClassMax][nTeachersMax],
                            int mCoTeacher[nTeachersMax][nClassMax],
                            int start,
                            int end)
    {
        double cost = 0;
        // calculamos los subcostos
        // restricciones hards
        cost += evalTeacherUnavailability(isCoteaching, classes, teachers, mCoClass, mCoTeacher, start, end);
        cost += evalEmptyPeriods(classes.size(), start, end);
        cost += evalParallelTeaching(isCoteaching, teachers, classes.size(), mCoClass, mCoTeacher, start, end);
        cost += evalWrongCoTeacher(classes, mCoClass, mCoTeacher, start, end);
        // restricciones softs
        cost += evalClassLessonDispersion(classes, start, end, mCoClass, mCoTeacher);
        cost += evalTEacherEmptySpaces(isCoteaching, teachers, mCoClass, mCoTeacher, start, end);
    }

    // soft constraints

    double evalTEacherEmptySpaces(bool isCoteaching,
                                  vector<Teacher>& teachers,
                                  int mCoClass[nClassMax][nTeachersMax],
                                  int mCoTeacher[nTeachersMax][nClassMax],
                                  int begin,
                                  int end)
    {
        int nTotalEmptyxTeacher = 0;
        int nTotalEmptyGlobal, nDays, nEmptys, nHoursTeaching, nUltimaLesson, nFirstLesson;
        bool bFlag, bHayLesson;
        double cost, totalCost;
        if(!isCoteaching) {
            for(int i = 0; i < teachers.size(); i++) {
                cost = 0.0;
                nTotalEmptyGlobal = 0;
                nDays = 0;
                for(int start = begin; start < end; start = start + 7) {
                    nEmptys = 0;
                    nHoursTeaching = 0;
                    nUltimaLesson = start;
                    nFirstLesson = start;
                    bFlag = true;
                    bHayLesson = false;
                    for(int t = start; t < start + 7; t++) {
                        for(int j = 0; j < teachers[i].numOfClasses; j++) {
                            int nClassHe = teachers[i].classesHeTeaches[j][0];
                            if(self[nClassHe][t] == i) {
                                bHayLesson = true;
                                if(bFlag) {
                                    nFirstLesson = t;
                                    bFlag = false;
                                }
                                nUltimaLesson = t;
                                nHoursTeaching++;
                                break;
                            }
                        }
                    }

                    if(bHayLesson) {
                        nEmptys = nUltimaLesson - nFirstLesson + 1 - nHoursTeaching;
                        nTotalEmptyGlobal += nEmptys;
                    }

                    if(nEmptys > 0) {
                        nTotalEmptyxTeacher += nEmptys;
                        nDays++;
                    }
                }
                if(nDays > 0) {
                    cost = TEPW * nTotalEmptyGlobal * pow(nBASE, nDays);
                }
                totalCost += cost;
            }
        } else {
            int nClass, ncoClass, nCoteacher;
            for(int i = 0; i < teachers.size(); i++) {
                cost = 0.0;
                nTotalEmptyGlobal = 0;
                nDays = 0;
                for(int start = begin; start < end; start = start + 7) {
                    nEmptys = 0;
                    nHoursTeaching = 0;
                    nUltimaLesson = start;
                    nFirstLesson = start;
                    bFlag = true;
                    bHayLesson = false;
                    for(int t = start; t < start + 7; t++) {
                        for(int j = 0; j < teachers[i].numOfClasses; j++) {
                            nClass = teachers[i].classesHeTeaches[j][0];
                            if(teachers[i].isCoteacher) {
                                if(self[nClass][t] == i) {
                                    bHayLesson = true;
                                    if(bFlag) {
                                        nFirstLesson = t;
                                        bFlag = false;
                                    }
                                    nUltimaLesson = t;
                                    nHoursTeaching++;
                                    break;
                                }
                            } else {
                                ncoClass = mCoClass[nClass][i];
                                if(ncoClass == nClass) {
                                    nCoteacher = mCoTeacher[i][ncoClass];
                                } else {
                                    nCoteacher = bigNumber;
                                }
                                if(nCoteacher < 0) {
                                    if(self[nClass][t] == i) {
                                        bHayLesson = true;
                                        if(bFlag) {
                                            nFirstLesson = t;
                                            bFlag = false;
                                        }
                                        nUltimaLesson = t;
                                        nHoursTeaching++;
                                        break;
                                    }
                                } else {
                                    if(self[nClass][t] == i || self[nClass][t] == nCoteacher) {
                                        bHayLesson = true;
                                        if(bFlag) {
                                            nFirstLesson = t;
                                            bFlag = false;
                                        }
                                        nUltimaLesson = t;
                                        nHoursTeaching++;
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    if(bHayLesson) {
                        nEmptys = nUltimaLesson - nFirstLesson + 1 - nHoursTeaching;
                        nTotalEmptyGlobal += nEmptys;
                    }

                    if(nEmptys > 0) {
                        nTotalEmptyxTeacher += nEmptys;
                        nDays++;
                    }
                }
                if(nDays > 0) {
                    // casos++;
                    cost = TEPW * nTotalEmptyGlobal * pow(nBASE, nDays);
                }

                totalCost += cost;
            }
        }

        return totalCost;
    }

    double evalClassLessonDispersion(vector<Classe>& classes,
                                     int begin,
                                     int end,
                                     int mCoClass[nClassMax][nTeachersMax],
                                     int mCoTeacher[nTeachersMax][nClassMax])
    {
        int nProblemDays, nTotalProblemAtDays, nTotalHoursClass, nHours, nHoursPerDayTeacher, nTeacher, nCoClass,
            nCoTeacher;
        double cost, totalCost;
        for(int i = 0; i < classes.size(); i++) {
            nProblemDays = 0;
            cost = 0;
            nTotalHoursClass = 0;
            for(int start = begin; start < end; start = start + 7) {
                nHours = 0;
                for(int k = 0; k < classes[i].numberOfTeachers; k++) {
                    nHoursPerDayTeacher = 0;
                    nTeacher = classes[i].teachersOfClassAndHours[k][0];
                    nCoClass = mCoClass[i][nTeacher];
                    if(nCoClass == i) {
                        nCoTeacher = mCoTeacher[nTeacher][nCoClass];
                    } else {
                        nCoTeacher = bigNumber;
                    }
                    for(int t = start; t < start + 7; t++) {
                        if((self[i][t] == nTeacher && nCoClass == -1) || self[i][t] == nCoTeacher) {
                            nHoursPerDayTeacher++;
                        }
                    }
                    if(classes[i].teachersOfClassAndHours[k][2] > 0 &&
                       nHoursPerDayTeacher > classes[i].teachersOfClassAndHours[k][2]) {
                        nHours += nHoursPerDayTeacher - classes[i].teachersOfClassAndHours[k][2];
                    } else if(classes[i].teachersOfClassAndHours[k][2] == 0) {
                        int l = 0;
                        for(l = 0; l < classes[i].numberOfTeachers; l++) {
                            if(classes[i].teachersOfClassAndHours[l][0] == nCoTeacher) {
                                break;
                            }
                        }

                        if(nHoursPerDayTeacher > classes[i].teachersOfClassAndHours[l][2]) {
                            nHours = nHours + nHoursPerDayTeacher - classes[i].teachersOfClassAndHours[k][2];
                        }
                    }
                }

                if(nHours > 0) {
                    nTotalHoursClass += nHours;
                    nProblemDays++;
                }
            }

            if(nProblemDays > 0) {
                nTotalProblemAtDays += nProblemDays;
                cost = ICDW * nTotalHoursClass * pow(nBASE, nProblemDays);
            }
            totalCost += cost;
        }
        return totalCost;
    }

    // hard constraints
    double evalWrongCoTeacher(vector<Classe>& classes,
                              int mCoClass[nClassMax][nTeachersMax],
                              int mCoTeacher[nTeachersMax][nClassMax],
                              int start,
                              int end)
    {
        double cost = 0;
        int nTeacher, nCoteacher, nClass2, nCasos;
        for(int k = start; k < end; k = k + 7) {
            for(int t = k; t < k + 7; t++) {
                for(int i = 0; i < classes.size(); i++) {
                    for(int j = 0; j < classes[i].numberOfTeachers; j++) {
                        nTeacher = classes[i].teachersOfClassAndHours[j][0];
                        nClass2 = mCoClass[i][nTeacher];
                        if(nClass2 != -1) {
                            nCoteacher = mCoTeacher[nTeacher][nClass2];
                        } else {
                            nCoteacher = bigNumber;
                        }

                        if(nClass2 != -1 && nClass2 != i) {
                            if(nCoteacher != bigNumber && self[i][t] == nTeacher && self[nClass2][t] != nCoteacher) {
                                nCasos++;
                            }
                        }
                    }
                }
            }
        }
        cost = nCasos * HCW * pow(2 * nBASE, nBASE);
        return cost;
    }

    double evalParallelTeaching(bool isCoteaching,
                                vector<Teacher>& teachers,
                                int nClass,
                                int mCoClass[nClassMax][nTeachersMax],
                                int mCoTeacher[nTeachersMax][nClassMax],
                                int start,
                                int end)
    {
        int nCasosParallel;
        double cost = 0;
        if(!isCoteaching) {
            for(int i = 0; i < teachers.size(); i++) {
                for(int idTeacher = start; idTeacher < end; idTeacher++) {
                    nCasosParallel = 0;
                    for(int j = 0; j < nClass; j++) {
                        if(self[j][idTeacher] == i)
                            nCasosParallel++;
                    }

                    if(nCasosParallel > 1) {
                        cost = cost + HCW * pow(nBASE, nCasosParallel - 1);
                    }
                }
            }
        } else {
            int nCoClass;
            int nCoTeacher;
            for(int i = 0; i < teachers.size(); i++) {
                for(int t = start; t < end; t++) {
                    nCasosParallel = 0;
                    for(int j = 0; j < nClass; j++) {
                        if(!teachers[i].isCoteacher) {
                            if(self[j][t] == i)
                                nCasosParallel++;
                        } else {
                            nCoClass = mCoClass[j][i];
                            if(nCoClass == j) {
                                nCoTeacher = mCoTeacher[i][nCoClass];
                            } else {
                                nCoTeacher = bigNumber;
                            }

                            if(nCoTeacher < 0) {
                                if(self[j][t] == i) {
                                    nCasosParallel++;
                                }
                            } else {
                                if(self[j][t] == i || self[j][t] == nCoTeacher) {
                                    nCasosParallel++;
                                }
                            }
                        }
                    }

                    if(nCasosParallel > 1) {
                        cost = cost + HCW * pow(nBASE, nCasosParallel - 1);
                    }
                }
            }
        }
        return cost;
    }

    double evalEmptyPeriods(int nClasses, int start, int end)
    {
        double cost = 0;
        for(int i = 0; i < nClasses; i++) {
            for(int j = start; j < end; j += 7) {
                for(int t = j; t < j + 7; t++) {
                    // la restriccion dice que no debe ser la ultima hora del dia, por eso !=6, !=13...!=34
                    if(self[i][t] == -1 && t != 6 && t != 13 && t != 20 && t != 27 && t != 34) {
                        cost = cost + HCW * pow(2 * nBASE, nBASE);
                    }
                }
            }
        }
        return cost;
    }

    double evalTeacherUnavailability(bool isCoteaching,
                                     vector<Classe>& classes,
                                     vector<Teacher>& teachers,
                                     int mCoClass[nClassMax][nTeachersMax],
                                     int mCoTeacher[nTeachersMax][nClassMax],
                                     int start,
                                     int end)
    {
        int nCasos = 0;
        double cost = 0.0;
        if(!isCoteaching) {
            for(int i = 0; i < classes.size(); i++) {
                for(int j = 0; j < classes[i].numberOfTeachers; j++) {
                    for(int t = start; t < end; t++)
                        if(self[i][t] == classes[i].teachersOfClassAndHours[j][0] &&
                           teachers[classes[i].teachersOfClassAndHours[j][0]].unavailableTimeslots[t] == 1) {
                            nCasos++;
                        }
                }
            }
        } else {
            int nCoClass, nCoTeacher, nTeacher;
            for(int i = 0; i < classes.size(); i++) {
                for(int j = 0; j < classes[i].numberOfTeachers; j++) {
                    nTeacher = classes[i].teachersOfClassAndHours[j][0];
                    for(int t = start; t < end; t++) {
                        if(!teachers[nTeacher].isCoteacher) {
                            if(nTeacher == self[i][t] && teachers[nTeacher].unavailableTimeslots[t] == 1) {
                                nCasos++;
                            }
                        } else {
                            nCoClass = mCoClass[i][nTeacher];
                            if(nCoClass == i)
                                nCoTeacher = mCoTeacher[nTeacher][nCoClass];
                            else
                                nCoTeacher = bigNumber;

                            if(nCoTeacher < 0) {
                                if(nTeacher == self[i][t] && teachers[nTeacher].unavailableTimeslots[t] == 1) {
                                    nCasos++;
                                }

                            } else if(nCoTeacher == bigNumber) {
                                if(nTeacher == self[i][t] && teachers[nTeacher].unavailableTimeslots[t] == 1) {
                                    nCasos++;
                                }

                            } else if(nCoTeacher > 0 && nCoTeacher != bigNumber) {
                                if(nCoTeacher == self[i][t] && teachers[nTeacher].unavailableTimeslots[t] == 1) {
                                    nCasos++;
                                }
                            }
                        }
                    }
                }
            }
        }
        cost = nCasos * HCW * pow(nBASE, 4.75);
        return cost;
    }
};
