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

populateArray(int*, int);
mainTask(int*);

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
    
    std::chrono::time_point<std::chrono::system_clock> begin, end;
    
    //begin the clock
    begin = std::chrono::system_clock::now();
#pragma omp parallel
    {
#pragma omp single
        mainTask(randomArray);
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

void mainTask(int* array) {
    
}

void mergeSort(int* array, int begin, int end) {
    
}

void merge(int* a, int* b, int* sol) {
    
}
