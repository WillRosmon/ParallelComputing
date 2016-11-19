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

omp_lock_t minLock; //I'm honestly not sure if we needed to use this
                    //I just felt it necessary for this assignment.

int main(int argc, const char * argv[]) {
    
    int numThreads = atoi(argv[1]);
    int arraySize = atoi(argv[2]);
    int granularity = atoi(argv[3]);
    
    //validate arguements
    if(numThreads == 0 || arraySize == 0 || granularity == 0) {
        std::cout << "Invalid arguements";
        return 0;
    }
    
    omp_set_num_threads(numThreads);
    int* randomArray = new int[arraySize]; //Allocate the array to heap
                                           //because it is too large for the stack
    fillArrayRandom(randomArray, arraySize);
    
    omp_init_lock(&minLock);  //Initialize the omp lock for the minimum variable
    
    int minimum = randomArray[0]; //set min to first value in array
    std::chrono::time_point<std::chrono::system_clock> begin, end;
    begin = std::chrono::system_clock::now();
    //begin parallel portion
#pragma omp parallel
    {
#pragma omp single
        mainTask(randomArray, &minimum, granularity, arraySize);  //initialize the main task
    }
    std::cout << "Minimum of the array is: " << minimum << std::endl;
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - begin;
    std::cout << "Reduction: Time taken: " << seconds.count();
    std::cout << " Granularity " << granularity << " num of Threads: " << numThreads << std::endl;
    
    //Clean up memory
    omp_destroy_lock(&minLock);
    delete[] randomArray;
    randomArray = NULL;
}

//fill the array with values between 1 and size
void fillArrayRandom(int* array, int size) {
    srand(time(NULL));
#pragma omp parallel for schedule(runtime)
    for(int i = 0; i < size; i++) {
        array[i] = (rand() % size) + 1;
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
        //set new start and end values to be passed into the findMin function
        start = end;
        end += granularity;
    }
    std::cout << "waiting for tasks to complete" << std::endl;
#pragma omp taskwait //wait for all tasks to complete before returning to main
}

//Called from main task to find the minimum of the array
//I'm not sure if this was supposed to be an omp loop, my program got hung up when it was
//so I took it out
void findMin(int* array, int start, int end, int* min, int size) {
    if(end > size) {  //ensure we do not move past the end of the array
        end = size;
    }
    for(int i = start; i < end; i++) {
        if(array[i] < *min) {
            newMin(min, &array[i]); //make the new minimum value the array's minimum
        }
    }
}

void newMin(int* minimum, int* newMin) {
    omp_set_lock(&minLock); //make sure only one thread is updating the minimum at a time
    if(*newMin < *minimum){
        *minimum =  *newMin;
    }
    omp_unset_lock(&minLock); //unlock minimum to allow other threads to modify
}
