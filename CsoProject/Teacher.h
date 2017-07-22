#pragma once
#include <string>
#include <vector>

using namespace std;
class Teacher
{
public:
    int idTeacher; // the index into vector of teachers
    string name;
    bool isCoteacher;                   // it is 1 if the teacher participates in a co-teaching
    int totalHours;                     // total teaching hours of teacher
    int RemainingHours;                 // remaining hours of teacher
    int availabilityHours;              // number of hours during which the teacher is available
    int availableDays;                  // number of days druing which the teacher is available
    int isAvailableAtDay[5];            // it is 1 if the teacher is available at that day, else it is -1
    int unavailableTimeslots[35];       // it is 1 if the teacher is not available at that timeslot, else it is -1
    int classesHeTeaches[nClassMax][3]; // contains the classes, the hours and the lessons of the teacher
    int numOfClasses;                   // number of classes
    int coteachings[10][5];             // matrix used in co-teaching cases //i:idcoteacher, 1: , 2:number of lessons
    int countOfCoteachers;              // number of co-teachers of the teacher

    void fixCoTeachersImpliedHours(int nTeachers, vector<Teacher>& teachers)
    {
        // si es un caso de co-teaching debemos corregir el total de horas ya que a veces la data esta X 0 0 (cero
        // horas) debido a que las horas se asignan al otro teacher y este queda con horas implicitas
        if(isCoteacher) {
            int nHoursImplied=0;
            for(int i = 0; i < nTeachers; i++) {
                for(int j = 0; j < teachers[i].countOfCoteachers; j++) {
                    if(teachers[i].coteachings[j][0] == idTeacher &&
                       teachers[i].coteachings[j][3] == teachers[i].coteachings[j][4]) {
                        int class1 = teachers[i].coteachings[j][3];
                        for(int k = 0; k < numOfClasses; k++) {
                            int class2 = classesHeTeaches[k][0];
                            if(classesHeTeaches[k][1] == 0 && class2 == class1) {
                                nHoursImplied+= teachers[i].coteachings[j][1];
                            }
                        }
                    }
                }
            }
            totalHours+= nHoursImplied;
        }
    }
};