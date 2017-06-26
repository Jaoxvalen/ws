#include <omp.h>

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define TI 10
#define TK 5


float image[TI][TI];
float kernel[TK][TK];
float result[TI][TI]; 

using namespace std;


//i , j relativo a la matriz image
float getAcum(int Im_i, int Im_j)
{
    int f=TI-TK;
    float acum=0;
    float c=0;
    for(int Ker_i=0; Ker_i<TK; Ker_i++)
    {
        for(int ker_j=0; Ker_i<TK; ker_j++)
        {
            int iii=Ker_i-f+Im_i;
            int ijj=Ker_i-f+Im_j;
            if(iii>=0 && ijj>=0 && iii<TI && ijj<TI)
            {
                c++;
                acum+=image[Ker_i-f+Im_i][Ker_i-f+Im_j]*kernel[Ker_i][ker_j];
            }
        }
    }
    acum=acum/c;
    return acum;
}
using namespace std;

int main(int argc, char** argv) {
    
    for(int i=0; i<TK; i++)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      for(int i=0; i<TK; i++)
    {
        for(int j=0;j<TK; j++)
        {
            kernel[i][j]=2;
        }
    }
    
    for(int i=0; i<TI; i++)
    {
        for(int j=0;j<TI; j++)
        {
            image[i][j]=1;
        }
    }
    
    for(int i=0; i<TI; i++)
    {
        for(int j=0;j<TI; j++)
        {
            result[i][j]=image[i][j]*getAcum(i,j);
        }
    }
    return 0;
}