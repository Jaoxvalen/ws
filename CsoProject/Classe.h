#pragma once
#include <string>

class Classe
{
public:
    int classNumber; // sequence number of class
	string className; // name of class
	int hoursPerWeek; // number of teaching hours per week of class
	int remainingHours; // number of remaining hours of class
	int teachersOfClassAndHours[35][3]; // matrix with the teachers, the teaching hours and the number of lessons that are taught in the class
	int numberOfTeachers; // number of teachers
	int teachersOfClassAndHoursRemaining[35][3]; // remaining teaching hours of every teacher of class
};