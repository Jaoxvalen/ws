#include <armadillo>
#include <cmath>
#include <vector>

using namespace std;
using namespace arma;

template <class T> class ALFunctions
{
public:



    //crout 
    void Crout(Mat<T>& A,Mat<T>& L, Mat<T>& U)
    {
        U.set_size(A.n_rows, A.n_cols);
        U=U.eye();
        L.set_size(A.n_rows, A.n_cols);
        L.zeros();
        L.col(0)=A.col(0);
        
        
        for(int j=1; j<A.n_rows;j++)
        {
            U(0,j)=A(0,j)/L(0,0);
        }
        
        for(int i=1; i<A.n_rows; i++)
        {
            for(int j=1; j<i;j++)
            {
                T acum=0;
                for(int k=0; k<j-1; k++)
                {
                    acum+=L(i,k)*U(k,j);
                }
                L(i,j)=A(i,j)-acum;
            }
            for(int j=i+1; j<A.n_rows; j++)
            {
                T acum=0;
                for(int k=0; k<i-1;k++)
                {
                    acum+=L(i,k)*U(k,j);
                }
                U(i,j)=(A(i,j)-acum)/L(i,i);
            }
        }
    }
    
    
    //QR factorization

    
    void QR_Gram_Schmidt(Mat<T>& Q, Mat<T>& R, Mat<T>& A)
    {
        R.set_size(A.n_rows,A.n_cols);
        R.eye();
        Q.set_size(A.n_rows,A.n_cols);
        Q.col(0)=A.col(0);
        
        
        for(int i=1; i<A.n_rows;i++)
        {
            Q.col(i)=A.col(i);
            for(int m=0;m<i; m++)
            {
                R(m,i)=as_scalar((Q.col(m).t()*A.col(i))/(norm(Q.col(m))*norm(Q.col(m))));
                Q.col(i)-=R(m,i);
            }
        }
    }
    
    //Lu factorization
    int selectPivotF(Mat<T>& U, int col)
    {
        int max = -1;
        int ir = -1;
        for(int i = col; i < U.n_cols; i++) {
            T p = abs(U(i, col));
            if(abs(U(i, col)) > max) {
                max = abs(U(i, col));
                ir = i;
            }
        }
        return ir;
    }

    void selectPivotTotal(Mat<T>& U, int col, int &ir, int &jr)
    {
        int max = -1;
        for(int i = col; i < U.n_rows; i++) {
            for(int j = col; j < U.n_cols; j++) {
                T p = abs(U(i, j));
                if(p>max)
                {
                    max=p;
                    ir=i;
                    jr=j;
                }
            }
        }
    }

    void LU_partial_pivot(Mat<T>& L, Mat<T>& U, Mat<T>& P, Mat<T>& A)
    {
        U = A;
        P.set_size(A.n_rows, A.n_cols);
        P.eye();
        L.set_size(A.n_rows, A.n_cols);
        L.zeros();
        for(int i = 0; i < U.n_cols; i++) {
            int pivot = selectPivotF(U, i);
            U.swap_rows(i, pivot);
            L.swap_rows(i, pivot);
            P.swap_rows(i, pivot);
            for(int j = i + 1; j < U.n_cols; j++) {
                T mk = U(j, i) / U(i, i);
                for(int k = 0; k < U.n_cols; k++) {
                    U(j, k) -= mk * U(i, k);
                }
                L(j, i) = mk;
            }
        }
        Mat<T> I(A.n_rows, A.n_rows);
        I.eye();
        L = L + I;
    }

    void LU_total_pivot(Mat<T>& L, Mat<T>& U, Mat<T>& P, Mat<T>& Q, Mat<T>& A)
    {
        U = A;
        P.set_size(A.n_rows, A.n_cols);
        P.eye();
        Q=P;
        L.set_size(A.n_rows, A.n_cols);
        L.zeros();
        for(int i = 0; i < U.n_cols; i++) {
            int pi=-1, pj=-1;
            selectPivotTotal(U, i, pi, pj);
            
            U.swap_rows(i, pi);
            L.swap_rows(i, pi);
            P.swap_rows(i, pi);
            
            U.swap_cols(i, pj);
            L.swap_cols(i, pj);
            Q.swap_cols(i, pj);
            
            
            for(int j = i + 1; j < U.n_cols; j++) {
                T mk = U(j, i) / U(i, i);
                for(int k = 0; k < U.n_cols; k++) {
                    U(j, k) -= mk * U(i, k);
                }
                L(j, i) = mk;
            }
        }
        Mat<T> I(A.n_rows, A.n_rows);
        I.eye();
        L = L + I;
    }
};