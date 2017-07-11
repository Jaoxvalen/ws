#include <omp.h>

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#define TI 8000

#define NUM_THREADS 8

float image[TI][TI];
float result[TI][TI];

using namespace std;

void getAcum(int& im, int& jm)
{
    int i, j, li_i, ls_i, li_j, ls_j;
    float acum = 0, n = 0;
    li_i = max(im - 2, 0);
    ls_i = min(im + 2, TI);
    li_j = max(jm - 2, 0);
    ls_j = min(jm + 2, TI);
    n = ((ls_i - li_i) + 1) * ((ls_i - li_i) + 1);
    for(i = li_i; i < ls_i; i++) {
        for(j = li_j; j < ls_j; j++) {
            acum += image[i][j];
        }
    }
    result[im][jm] = acum = acum / n;
}

int main(int argc, char** argv)
{

    // llenado de matrices
    for(int i = 0; i < TI; i++) {
        for(int j = 0; j < TI; j++) {
            image[i][j] = (std::rand() % 5) * 2;
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

    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for  collapse(2)
    for(int i = 0; i < TI; i++) {
        for(int j = 0; j < TI; j++) {
            getAcum(i, j);
        }
    }

    end = omp_get_wtime();
    tp = end - start;

    sp = t1 / tp;
    ep = sp / NUM_THREADS;

    cout << "NUM_THREADS=" << NUM_THREADS << endl;
    cout << "T(1)=" << t1 << endl;
    cout << "T(P)=" << tp << endl;
    cout << "S(P)=" << sp << endl;
    cout << "E(P)=" << ep << endl;

    return 0;
}