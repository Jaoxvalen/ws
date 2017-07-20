#pragma once
#include <string>

using namespace std;
class Teacher
{
public:
    string name;
    bool isCoteacher; // it is 1 if the teacher participates in a co-teaching
    int totalHours; // total teaching hours of teacher
    int RemainingHours; // remaining hours of teacher
    int availabilityHours; // number of hours during which the teacher is available
    int availableDays; // number of days druing which the teacher is available
	int isAvailableAtDay[5]; // it is 1 if the teacher is available at that day, else it is -1
	int unavailableTimeslots[35]; // it is 1 if the teacher is not available at that timeslot, else it is -1
	int classesHeTeaches[nClassMax][3];; // contains the classes, the hours and the lessons of the teacher
	int numOfClasses; // number of classes
	int coteachings[15][5]; // matrix used in co-teaching cases
	int countOfCoteachers; // number of co-teachers of the teacher
};