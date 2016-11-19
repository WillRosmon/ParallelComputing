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
void merge(int*, int, int);
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
#pragma omp task
    mergeSort(array, 0, size-1, size);
#pragma omp taskwait
    int numPieces = omp_get_num_threads();
    bool merged = false;
    if(numPieces == 1)    {merged = true;}
    while(!merged) {
        numPieces /= 2;
        int start = 0;
        int increment = size / numPieces;
        int end = start + increment;
        for(int i = 0; i < numPieces; i++) {
#pragma omp task
            merge(array, start, end);
        }
#pragma omp taskwait
        start = end;
        if(end += increment >= size - 1) {
            end = size-1;
        }
        merged = end == (size-1);
    }
}

void mergeSort(int* array, int begin, int end, int size) {
    if(size <= 2 || begin <= end) {
        std::cout << "Size of smallest piece: " << size;
        std::cout << "Beginning: " << begin << "Ending: " << end << std::endl;
        return;
    }
    int sizeLeftHalf = size / 2;
    int sizeRightHalf = size - sizeLeftHalf;
    int midpoint = begin + sizeLeftHalf;
    mergeSort(array, begin, midpoint, sizeLeftHalf);
    mergeSort(array, midpoint + 1, end, sizeRightHalf);
    return merge(array, begin, end);
}
                     
void merge(int* array, int begin, int end) {
    if(end <= begin) {
        return;
    } else {
        int a = begin;
        int b = (begin + end) / 2;
        
        while (a < b && b < end) {
            while(array[b] < array[a]) {
                swap(&array[a], &array[b]);
                b++;
            }
            a++;
        }
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
