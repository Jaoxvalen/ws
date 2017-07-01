#include <omp.h>

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define TI 8000
#define TK 5
#define KC 2

#define NUM_THREADS 8

float image[TI][TI];
float kernel[TK][TK];
float result[TI][TI];

using namespace std;

// i , j relativo a la matriz image
void getAcum(int &Im_i, int &Im_j)
{
    int di = Im_i - KC;
    int dj = Im_j - KC;

    float acum = 0;
    // float c=0;
    for(int ker_i = 0; ker_i < TK; ker_i++) {
        for(int ker_j = 0; ker_j < TK; ker_j++) {
            int im = ker_i + di;
            int jm = ker_j + dj;
            if(im >= 0 && im < TI && jm >= 0 && jm < TI) {
                acum += image[im][jm] * kernel[ker_i][ker_j];
            }
        }
    }
    result[Im_i][Im_j]=acum;
}

int main(int argc, char** argv)
{

    // llenamos las matrices con aleatorios
    for(int i = 0; i < TK; i++)
        for(int i = 0; i < TK; i++) {
            for(int j = 0; j < TK; j++) {
                kernel[i][j] = 2; //(std::rand() % 5) * 2;
            }
        }

    for(int i = 0; i < TI; i++) {
        for(int j = 0; j < TI; j++) {
            image[i][j] = 1; //(std::rand() % 5) * 2;
        }
    }
    // fin de llenado de matrices

    double t1, tp, sp, ep, end, start;

    /*CALCULO CON UN CPU*/

    
    start = omp_get_wtime();
    for(int i = 0; i < TI; i++) {
        for(int j = 0; j < TI; j++) {
            getAcum(i, j);
        }
    }
    end = omp_get_wtime();
    t1 = end - start;
    

    // aplicamos la convolucion

    start = omp_get_wtime();
    // omp_set_num_threads(NUM_THREADS);
    // int steps = TI / NUM_THREADS;

    // int id = omp_get_thread_num();
    // int ini = steps * id;

    #pragma omp parallel for collapse(2) 
    for(int i = 0; i < TI; i++) {
        for(int j = 0; j < TI; j++) {
            getAcum(i, j);
        }
    }

    end = omp_get_wtime();
    tp = end - start;

    //cout << "T(P)=" << tp << endl;

    
        sp=t1/tp;
        ep=tp/NUM_THREADS;

        cout<<"NUM_THREADS="<<NUM_THREADS<<endl;
        cout<<"T(1)="<<t1<<endl;
        cout<<"T(P)="<<tp<<endl;
        cout<<"S(P)="<<sp<<endl;
        cout<<"E(P)="<<ep<<endl;
    

    
    /*
    for(int i = 0; i < TI; i++) {
        for(int j = 0; j < TI; j++) {
            cout<<result[i][j]<<" ";
        }
        cout<<endl;
    }
    */
    
    

    return 0;
}