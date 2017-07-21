#pragma once
#include "Globals.h"
#include "Classe.h"
#include "Utils.h"
#include <vector>

using namespace std;

class Cat
{
public:
    //int self[nClassMax][35];
    vector<vector<int> > self;
    void createCat(int nClass, vector<Classe>& classes)
    {
        self.resize(nClass,vector<int>(35));
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
        //regresamos la configuracion de las horas restantes para que no afecte a los demas gatos
        for(int j = 0; j < nClass; j++) {
            for(int i = 0; i < classes[j].numberOfTeachers; i++) {
                for(int k = 0; k < 3; k++) {
                    classes[j].teachersOfClassAndHoursRemaining[i][k] = classes[j].teachersOfClassAndHours[i][k];
                }
            }
        }
    }
};
