//
//  mergeSort.cpp
//  Assignment5
//
//  Created by William Rosmon on 11/19/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>

void populateArray(int*, int);
void mainTask(int*, int);
void mergeSort(int*, int, int, int);
void merge(int*, int, int, int, int);
void swap(int*, int*);

int main(int argc, const char* argv[]) {
    int arraySize = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    
    if(arraySize == 0 || numThreads == 0) {
        std::cout << "Invalid Parameters" << std::endl;
        return 0;
    }
    
    omp_set_num_threads(numThreads);
    int* randomArray = new int[arraySize];
    populateArray(randomArray, arraySize);
    
    std::cout << "Original Array: " << std::endl;
    for(int i = 0; i < arraySize; i++) {
        std::cout << randomArray[i] << " ";
    }
    
    std::chrono::time_point<std::chrono::system_clock> begin, end;
    
    //begin the clock
    begin = std::chrono::system_clock::now();
#pragma omp parallel
    {
#pragma omp single
        mainTask(randomArray, arraySize);
    }
    
    //Debugging
    std::cout << "Sorted Array";
    for(int i = 0; i < arraySize; i ++) {
        std::cout << randomArray[i] << " ";
    }
    
    //calculate and print the run time
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - begin;
    std::cout << "Merge Sort: Time taken: " << seconds.count();
    std::cout << " Num threads: " << numThreads << std::endl;
    
    //clean up memory
    delete[] randomArray;
    randomArray = NULL;
}

//Fill the array with values of 1 - size
void populateArray(int* array, int size) {
    srand(time(NULL));
#pragma omp parallel for schedule(guided)
    for(int i = 0; i < size; i++) {
        array[i] = (rand() % size) + 1;
    }
}

void mainTask(int* array, int size) {
    int* sortedArray = new int[size];
#pragma omp task
    {
    mergeSort(array, 0, size-1, size);
    }
#pragma omp taskwait
}

void mergeSort(int* array, int begin, int end, int size) {
    if(size < 2) {
        return;
    }

    int leftSize = size / 2;
    int rightSize = size - leftSize;
    int leftEnd = begin + leftSize - 1;
    
#pragma omp task
    {
        mergeSort(array, begin, leftEnd, leftSize);
    }
#pragma omp task
    {
        mergeSort(array, leftEnd, end, rightSize);
    }
#pragma omp taskwait
    merge(array, begin, leftEnd, end, size);
}

void merge(int* array, int begin, int rightBegin, int end, int size) {
    int a, b, c;
    a = begin;
    b = rightBegin;
    c = 0;
    int* tempArray = new int[size];
    while(a < rightBegin && b < end) {
        if(array[a] > array[b]) {
            tempArray[c] = array[b];
            b++;
        } else {
            tempArray[c] = array[a];
            a++;
        }
        c++;
    }
    
    
    //copy temp array back into original array
    c = 0;
    for(int i = begin; i < end; i++)
    {
        array[i] = tempArray[c];
        c++;
    }
    //clean up tempArray
    delete[] tempArray;
    tempArray = NULL;
}

