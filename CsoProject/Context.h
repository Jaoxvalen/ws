#pragma once
#include "Globals.h"
#include <string>
#include <fstream>
#include <iostream>
#include "Utils.h"
#include "Cat.h"
#include "Teacher.h"
#include "Classe.h"

using namespace std;

class Context
{
public:
    vector<Cat> cats;         // lista de gatos
    Cat oGlobalBest;          // el mejor gato global
    vector<Teacher> teachers; // los maestros
    vector<Classe> classes;   // las clases

    // variables despues de leer el archivo:
    bool isCoteaching;
    int nClass;
    int nTeachers;

    // matrices de relacion co-teaching
    //vector<vector<int> >mCoClass;
    //vector<vector<int> >mCoTeacher;
    
    int mCoClass[nClassMax][nTeachersMax];   // contains the class with which there is co-teaching
    int mCoTeacher[nTeachersMax][nClassMax]; // contains the teacher that participates in a co-teaching

    void inputData(string dir)
    {
        cout << "i: Leyendo datos del archivo..." << endl;
        int data_entry_ok = 0;
        ifstream fichero(dir);
        while(data_entry_ok == 0) { // reads and checks the integrity of the input file
            string line;
            Utils::getWord(fichero, line); // la primera linea indica si se manejaran coteachings
            isCoteaching = stoi(line.c_str());
            Utils::getWord(fichero, line); // el numero de clases
            nClass = stoi(line.c_str());
            Utils::getWord(fichero, line); // el numero de maestros
            nTeachers = stoi(line.c_str());

            // seteamos los valores iniciales de las clases
            classes.resize(nClass);
            for(int i = 0; i < nClass; i++) {
                classes[i].classNumber = i;
                classes[i].numberOfTeachers = 0;
                Utils::getWord(fichero, line); // el nombre de la clase
                classes[i].className = line;
                Utils::getWord(fichero, line); // las horas por semana de la clase
                classes[i].hoursPerWeek = stoi(line.c_str());
            }

            // seteamos los valores iniciales de los teachers
            teachers.resize(nTeachers);
            for(int i = 0; i < nTeachers; i++) {
                teachers[i].availabilityHours = 35;
                Utils::getWord(fichero, line); // nombre del teacher
                teachers[i].name = line;
                Utils::getWord(fichero, line); // es coteacher
                teachers[i].isCoteacher = stoi(line.c_str());

                teachers[i].numOfClasses = 0;
                teachers[i].totalHours = 0;

                // Seccion para llenar las clases, horas y lecciones a los teachers
                Utils::getWord(fichero, line); // la clase asignada al teacher
                int nPosClassTeacher = 0;
                int idClass = stoi(line.c_str());
                while(idClass != -1) {
                    // el id de la clase que enseña
                    teachers[i].classesHeTeaches[nPosClassTeacher][0] = idClass;
                    classes[idClass].teachersOfClassAndHours[classes[idClass].numberOfTeachers][0] = i;

                    // las horas por semana que enseña la clase por semana
                    Utils::getWord(fichero, line);
                    int horas = stoi(line.c_str());
                    teachers[i].classesHeTeaches[nPosClassTeacher][1] = horas;
                    teachers[i].totalHours += horas;
                    classes[idClass].teachersOfClassAndHours[classes[idClass].numberOfTeachers][1] = horas;

                    // el numero de lecciones que enseña en la clase
                    Utils::getWord(fichero, line);
                    int lesson = stoi(line.c_str());
                    teachers[i].classesHeTeaches[nPosClassTeacher][2] = lesson;
                    classes[idClass].teachersOfClassAndHours[classes[idClass].numberOfTeachers][2] = lesson;

                    classes[idClass].numberOfTeachers++;
                    nPosClassTeacher++;
                    teachers[i].numOfClasses = nPosClassTeacher;

                    Utils::getWord(fichero, line); // la clase asignada al teacher
                    idClass = stoi(line.c_str());
                }

                // seteamos los valores por defecto para los slots de los teachers
                for(int j = 0; j < 35; j++) {
                    teachers[i].unavailableTimeslots[j] = -1;
                }
                for(int k = 0; k < 5; k++) {
                    teachers[i].isAvailableAtDay[k] = 1;
                }

                // Seccion para saber que tiempos los teachers no están disponibles
                Utils::getWord(fichero, line); // el slot de no disponible de los teachers
                int nSlot = stoi(line.c_str());
                while(nSlot != -1) {
                    teachers[i].unavailableTimeslots[nSlot] = 1;
                    teachers[i].availabilityHours--;

                    Utils::getWord(fichero, line); // el slot de no disponible de los teachers
                    nSlot = stoi(line.c_str());
                }

                teachers[i].availableDays = 5;
                for(int start = 0; start < 29; start = start + 7) {
                    int nSubtractDay = 0;
                    for(int t = start; t < start + 7; t++) {
                        if(teachers[i].unavailableTimeslots[t] == 1)
                            nSubtractDay++;
                        if(nSubtractDay == 7) {
                            teachers[i].availableDays--;
                            teachers[i].isAvailableAtDay[start / 7] = -1;
                        }
                    }
                }
            }

            for(int i = 0; i < nTeachers; i++) {
                for(int j = 0; j < nClass; j++) {
                    mCoClass[j][i] = -1;
                    mCoTeacher[i][j] = bigNumber;
                }
            }

            // seccion para setear los datos de co-teaching
            if(isCoteaching) {

                // seteamos la matriz de coteaching de cada teacher como -1 por defecto
                for(int i = 0; i < nTeachers; i++) {
                    for(int j = 0; j < 10; j++) {
                        for(int n = 0; n < 5; n++) {
                            teachers[i].coteachings[j][n] = -1;
                        }
                    }
                    teachers[i].countOfCoteachers = 0;
                }

                // seccion para llenar la info de coteaching de cada teacher
                Utils::getWord(fichero, line); // el id del primer teacher que va a co-techear
                int nIdCoTeacherA = stoi(line.c_str());
                while(nIdCoTeacherA != -1) {
                    Utils::getWord(fichero, line); // el id del segundo teacher que va a co-techear
                    int nIdCoTeacherB = stoi(line.c_str());
                    Utils::getWord(fichero, line); // horas que van a co-techear juntos
                    int nHoras = stoi(line.c_str());
                    Utils::getWord(fichero, line); // numero de lecciones que van a co-techear
                    int nLessons = stoi(line.c_str());
                    Utils::getWord(fichero, line); // el id de la claseA que va a co-techear
                    int nIdClassA = stoi(line.c_str());
                    Utils::getWord(fichero,
                                   line); // el id de la claseB que va a co-techear (puede ser que sea igual al A)
                    int nIdClassB = stoi(line.c_str());

                    teachers[nIdCoTeacherA].coteachings[teachers[nIdCoTeacherA].countOfCoteachers][0] = nIdCoTeacherB;
                    teachers[nIdCoTeacherA].coteachings[teachers[nIdCoTeacherA].countOfCoteachers][1] = nHoras;
                    teachers[nIdCoTeacherA].coteachings[teachers[nIdCoTeacherA].countOfCoteachers][2] = nLessons;
                    teachers[nIdCoTeacherA].coteachings[teachers[nIdCoTeacherA].countOfCoteachers][3] = nIdClassA;
                    teachers[nIdCoTeacherA].coteachings[teachers[nIdCoTeacherA].countOfCoteachers][4] = nIdClassB;

                    teachers[nIdCoTeacherB].coteachings[teachers[nIdCoTeacherB].countOfCoteachers][0] = nIdCoTeacherA;
                    teachers[nIdCoTeacherB].coteachings[teachers[nIdCoTeacherB].countOfCoteachers][1] = nHoras;
                    teachers[nIdCoTeacherB].coteachings[teachers[nIdCoTeacherB].countOfCoteachers][2] = nLessons;
                    teachers[nIdCoTeacherB].coteachings[teachers[nIdCoTeacherB].countOfCoteachers][3] = nIdClassB;
                    teachers[nIdCoTeacherB].coteachings[teachers[nIdCoTeacherB].countOfCoteachers][4] = nIdClassA;

                    if(nIdClassA == nIdClassB) {
                        mCoClass[nIdClassA][nIdCoTeacherA] = nIdClassA;
                        mCoClass[nIdClassA][nIdCoTeacherB] = nIdClassA;
                        mCoTeacher[nIdCoTeacherA][nIdClassA] =
                            -nIdCoTeacherB; //- para contrarestar al evaluar la restrinccion suave
                        mCoTeacher[nIdCoTeacherB][nIdClassA] = nIdCoTeacherA;
                    } else {
                        mCoClass[nIdClassA][nIdCoTeacherA] = nIdClassB;
                        mCoTeacher[nIdCoTeacherA][nIdClassB] = nIdCoTeacherB;
                    }

                    teachers[nIdCoTeacherA].countOfCoteachers++;
                    teachers[nIdCoTeacherB].countOfCoteachers++;

                    Utils::getWord(fichero, line); // el id del primer teacher que va a co-techear
                    nIdCoTeacherA = stoi(line.c_str());
                }
            }

            data_entry_ok = 1; // todo esta ok con el fichero
        }
        fichero.close();
        cout << "i: lectura de datos completa" << endl;
    }

    void initializeCats()
    {
        cout << "i: Inicializando los gatos..." << endl;
        cats.resize(nCats);
        for(int i=0; i<cats.size(); i++)
        {
            cats[i].createCat(nClass,classes);
        }
        cout << "i: Se han creado "<<nCats<<" gatos correctamente." << endl;
    }

    void start(string dir)
    {
        inputData(dir);
        initializeCats();
    }
};