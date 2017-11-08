
#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>
#include<chrono>
#include<cstring>

void bubble_sort();

using namespace std;
unsigned long long SIZE = 100000;
vector<int> a;

int main(int argc,char**args){
    SIZE = atoi(args[2]);
    std::srand(0);
    for(int i=0;i<SIZE;i++){
        a.push_back(rand());
    }
    //cout << "finish generating numbers" << endl;
    auto start = chrono::system_clock::now();
    if strcmp(args[1],"bubble" == 0)
        bubble_sort();
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end-start;
    cout <<  elapsed.count() << endl;
}

void bubble_sort(){
    int i,j,tmp;
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
