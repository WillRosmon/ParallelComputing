//
//  reductionTask.cpp
//  Assignment5
//
//  Created by William Rosmon on 11/18/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

void mainTask(int*, int*);
void fillArrayRandom(int*, int);


#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <mutex>

std::mutex mutex;

int main(int argc, const char * argv[]) {

    int numThreads = atoi(argv[1]);
    int arraySize = atoi(argv[2]);
    int granularity = atoi(argv[3]);
    
    int* randomArray = new int[arraySize];
    fillArrayRandom(randomArray, arraySize);
    
    int minumum = randomArray[0];
    
    omp_set_num_threads(numThreads);
    
#pragma omp parallel
    {
#pragma omp single
        mainTask(randomArray, &minumum, granularity);
        std::cout << "Minimum: " << minumum << std::endl;
    }
    
    
}

void fillArrayRandom(int* array, int size) {
    srand(time(NULL));
#pragma omp parallel for schedule(runtime)
    for(int i = 0; i < size; i++) {
        array[i] = rand() % size;
    }
}

void mainTask(int* array, int* minimum, int granularity, int size) {
    int numTasks = 0;
    numTasks = size / granularity
    int start = 0;
    int end = start + granularity;
#pragma omp for schedule(runtime)
    for(int i = 0; i < numTasks; i++) {
        if(size > start + granularity) {
#pragma omp task
            findMin(array, start, end);
        } else {
#pragma omp task
            findMin(array, start, size-1);
        }
#pragma omp taskwait
    }
}



void newMin(int minimum, int* newMin) {
    mutex.lock();
    minimum = *newMin;
    mutex.unlock();
}