#include "Globals.h"
#include "Cat.h"
#include "Teacher.h"

class Context
{
public:
    Cat Cats[nCats]; //lista de gatos
    Cat oGlobalBest; // el mejor gato global
    Teacher teachers[nTeachers]; // los maestros
    Classe Classes[nClass];// las clases 
};