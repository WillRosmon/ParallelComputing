//
//  main.cpp
//  Assignment5
//
//  Created by William Rosmon on 10/11/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <omp.h>
#include <ctime>
#include <chrono>

void mainTask(int*, int*, int);
void fillArray(int*, int);
void computeMin(int*, int*, int);

int main(int argc, const char * argv[]) {
    int arraySize = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    
    omp_set_num_threads(numThreads);
    int randomArray[arraySize];
    fillArray(randomArray, arraySize);
    for(int i = 0; i < arraySize; i++) {
        std::cout << randomArray[i] << " ";
    }
    int arrayMinimum = randomArray[0];
    int* minimum = &arrayMinimum;
#pragma omp parallel
    {
#pragma omp single
        mainTask(randomArray, minimum, arraySize);
    }
}

void fillArray(int* randomArray, int size) {
    srand(time(NULL));
#pragma omp parallel for schedule(runtime)
    for(int i = 0; i < size; i++) {
        randomArray[i] = rand() % size;
    }
}

void mainTask(int* array, int* minimum, int size) {
    
#pragma omp task
    computeMin(array, minimum, size);
#pragma omp taskwait
    std::cout << "the minimum value in the array is: " << *minimum;
}

void computeMin(int* array, int* minimum, int size) {
#pragma omp for schedule(runtime)
    for(int i = 0; i < size; i++) {
        if(array[i] < *minimum) {
            *minimum = array[i];
        }
    }
}