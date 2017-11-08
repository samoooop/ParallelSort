
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstring>
#include <omp.h>

void bubble_sort();
int merge(int l, int r, int u);
void merge_sort();
void qs(int first, int last);

using namespace std;
unsigned long long SIZE = 100000;
int NUMTHREADS = 1;
vector<int> a, b, v;

int main(int argc, char **args)
{
    SIZE = atoi(args[2]);
    NUMTHREADS = atoi(args[3]);
    std::srand(0);
    for (int i = 0; i < SIZE; i++)
    {
        a.push_back(rand());
        b.push_back(0);
    }
    v = a;
    //cout << "finish generating numbers" << endl;
    auto start = chrono::system_clock::now();
    if (strcmp(args[1], "bubble") == 0)
        bubble_sort();
    if (strcmp(args[1], "merge") == 0)
        merge_sort();
    if (strcmp(args[1], "quick") == 0){
        omp_set_nested(1);
        qs(0,a.size() - 1);
    }
    
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << elapsed.count() << endl;
}

void bubble_sort()
{
    int i, j, tmp;
    for (i = 0; i < (SIZE / 2); i++)
    {
#pragma omp parallel for
        for (j = 0; j < (SIZE - 1); j += 2)
            if (a[j] > a[j + 1])
            {
                tmp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = tmp;
            }
#pragma omp parallel for
        for (j = 1; j < (SIZE - 1); j += 2)
            if (a[j] > a[j + 1])
            {
                tmp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = tmp;
            }
    }
}

void merge_sort()
{
    int i, j, k;
    for (i = 1; i <= SIZE; i *= 2)
    {
        #pragma omp parallel for private(k)
        for (j = 0; j < SIZE; j += 2 * i)
        {
            k = j + 2 * i - 1;
            if (k > SIZE - 1)
                k = SIZE - 1;
            merge(j, j + i, k);
        }
    }
}

int merge(int l, int r, int u)
{
    int i, j, k;
    i = l;
    j = r;
    k = l;
    while (i < r && j <= u)
    {
        if (a[i] <= a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
        k++;
    }
    while (i < r)
    {
        b[k] = a[i];
        i++;
        k++;
    }
    while (j <= u)
    {
        b[k] = a[j];
        j++;
        k++;
    }
    for (k = l; k <= u; k++)
    {
        a[k] = b[k];
    }
}

void qs(int first, int last)
{
    int start[2], end[2], pivot, i, temp;
    if (first < last)
    {
        start[0] = first;
        end[0] = last;
        start[1] = first;
        end[1] = last;
        pivot = v[(first + last) / 2];
        while (start[1] <= end[0])
        {
            while (v[start[1]] < pivot)
                start[1]++;
            while (pivot < v[end[0]])
                end[0]--;
            if (start[1] <= end[0])
            {
                temp = v[start[1]];
                v[start[1]] = v[end[0]];
                v[end[0]] = temp;
                start[1]++;
                end[0]--;
            }
        }
        if (last - first >= SIZE / NUMTHREADS)
        {
            /* For large data size, sort the two partitions in parallel */
            #pragma omp parallel num_threads(2)
            {
                #pragma omp sections nowait
                {
                    #pragma omp section
                    qs(start[0], end[0]);
                    #pragma omp section
                    qs(start[1], end[1]);
                } 
            }
        }
        else
        {
            /* For small data, sort sequentially */
            qs(start[0], end[0]);
            qs(start[0], end[0]);
        }
    }
}