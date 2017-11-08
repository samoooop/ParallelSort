#include<iostream>
#include<cstdlib>

#define SIZE 100000000

int a[SIZE]

int main(){
    std::srand(0);
    for(int i=0;i<SIZE;i++){
        a[i] = std::rand();
    }
}

void bubble_sort(){
    for (i=0; i<(SIZE/2); i++) {
        #pragma omp parallel for
        for(j=0; j<(SIZE-1); j+=2)
            if (a[j] > a[j+1]) {
                tmp = a[j+1];
                a[j+1] = a[j];
                a[j] = tmp;
            }
        #pragma omp parallel for
        for(j=1; j<(SIZE-1); j+=2)
            if (a[j] > a[j+1]) {
                tmp = a[j+1];
                a[j+1] = a[j];
                a[j] = tmp;
            }
    }
}