#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;
void merge(int, int, int, int*);
void merge_sort(int low, int high, int* p){
    int pivot;
    static int i(1);
    if (high>low)
    {
        cout << "calling merge_sort: "<<i<<endl; i++;
        pivot = low + ((high - low)/2);
        cout << pivot << endl;
        merge_sort(low, pivot, p);
        merge_sort(pivot+1, high, p);
        merge(low, pivot, high, p);

    }
}
void merge(int l, int pi, int h,int* arr)
{
            int start = l;
        int mid = pi+1;
        while((start<=pi)&&(mid <=h)){
            if (arr[start] > arr[mid])
            {
                int temp = arr[mid];
                arr[mid] = arr[start];
                arr[start] = temp;
                mid++;
             }
            else
                start++;
    }
}
int main() 
{
    int a[] = {2, 42, 3, 7, 1};
    merge_sort(0, 4, a);
    for (int i = 0; i<=4 ; i++)
        cout << a[i] << endl;
    return (0);

}