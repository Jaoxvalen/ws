#include "Globals.h"
#include "Cat.h"
#include "Teacher.h"
#include "Classe.h"
#include <string>
#include <fstream>
#include <iostream>
#include "Utils.h"

using namespace std;
class Context
{
public:
    
    vector<Cat> Cats; //lista de gatos
    Cat oGlobalBest; // el mejor gato global
    vector<Teacher> teachers; // los maestros
    vector<Classe> classes;// las clases 
    
    //variables despues de leer el archivo:
    bool isCoteaching;
    int nClass;
    int nTeachers;
    
    
    void inputData(string dir)
    {
        int data_entry_ok = 0;
        ifstream fichero(dir);
        while (data_entry_ok == 0) { // reads and checks the integrity of the input file
            string line;
            Utils::getWord(fichero,line);//la primera linea indica si se manejaran coteachings
            isCoteaching = stoi(line.c_str());
            Utils::getWord(fichero,line);//el numero de clases
            nClass= stoi(line.c_str());
            Utils::getWord(fichero,line);//el numero de maestros
            nTeachers=stoi(line.c_str());
            
        
            //seteamos los valores iniciales de las clases
            classes.resize(nClass);
            for (int i = 0; i < nClass; i++) {
                classes[i].classNumber=i;
                classes[i].numberOfTeachers = 0;
                Utils::getWord(fichero,line);//el nombre de la clase
                classes[i].className=line;
                Utils::getWord(fichero,line);//las horas por semana de la clase
                classes[i].hoursPerWeek=stoi(line.c_str());
            }
            
            //seteamos los valores iniciales de los teachers
            teachers.resize(nTeachers);
            for (int i = 0; i < nTeachers; i++) {
                teachers[i].availabilityHours = 35;
                Utils::getWord(fichero,line);// nombre del teacher
                teachers[i].name=line;
                Utils::getWord(fichero,line);// es coteacher
                teachers[i].isCoteacher=stoi(line.c_str());
                
                teachers[i].numOfClasses = 0;
                teachers[i].totalHours = 0;
                
                Utils::getWord(fichero,line);// la clase asignada al teacher
                while(stoi(line.c_str())!=-1)
                {
                    
                    Utils::getWord(fichero,line);// la clase asignada al teacher
                }
                
                
            }
            
            
            data_entry_ok=1;//todo esta ok con el fichero
        }
        fichero.close(); 
    }
    void start(string dir)
    {
        inputData(dir);
    }
};