//
//  reductionTask.cpp
//  Assignment5
//
//  Created by William Rosmon on 11/18/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

void mainTask(int*, int*, int, int);
void fillArrayRandom(int*, int);
void newMin(int*, int*);
void findMin(int*, int, int, int*, int);


#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>

omp_lock_t minLock;

int main(int argc, const char * argv[]) {

    int numThreads = atoi(argv[1]);
    int arraySize = atoi(argv[2]);
    int granularity = atoi(argv[3]);
    omp_set_num_threads(numThreads);
    int* randomArray = new int[arraySize];
    fillArrayRandom(randomArray, arraySize);

    omp_init_lock(&minLock);

    int minimum = randomArray[0]; //set min to first value in array
    int threads = omp_get_num_threads();
#pragma omp parallel
    {
#pragma omp single
        mainTask(randomArray, &minimum, granularity, arraySize);
    }
	std::cout << "Minimum of the array is: " << minimum << std::endl;
	//Clean up memory
	omp_destroy_lock(&minLock);
	delete[] randomArray;
	randomArray = NULL;
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
    numTasks = size / granularity;
    int start = 0;
    int end = start + granularity;
    for(int i = 0; i < numTasks; i++) {
#pragma omp task
	{
            findMin(array, start, end, minimum, size);
        }
        start = end;
	end += granularity;
    }
	std::cout << "waiting for tasks to complete" << std::endl;
#pragma omp taskwait
}

void findMin(int* array, int start, int end, int* min, int size) {
    if(end > size) {
        end = size;
    }
    for(int i = start; i < end; i++) {
        if(array[i] < *min) {
            newMin(min, &array[i]);
        }
    }
}

void newMin(int* minimum, int* newMin) {
	omp_set_lock(&minLock);
	if(*newMin < *minimum){
   	 *minimum =  *newMin;
	}
	omp_unset_lock(&minLock);
}
