//
//  findFirst.cpp
//  Assignment5
//
//  Created by William Rosmon on 10/13/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <ctime>
//#include <omp.h>


void fillArray(int*, int);
void mainTask(int*, int, int*, int);
void findFirst(int*, int, int*, int);

int main(int argc, const char * argv[]) {
    int numThreads = atoi(argv[1]);
    int searchNumber = atoi(argv[2]);
    int arraySize = 1000;
    int randomArray[arraySize];
    fillArray(randomArray, arraySize);
    int errorPosition = arraySize;
    int* minimumPosition = &errorPosition;
    
//#pragma omp single
    {
        mainTask(randomArray, arraySize, minimumPosition, searchNumber);
    }
    
    return 0;
}

void fillArray(int* array, int size) {
    srand(time(NULL));
//#pragma omp parallel for schedule(guided)
    for(int i = 0; i < size; i++) {
        array[i] = rand() % size;
    }
}

void mainTask(int* array, int size, int* firstPosition, int search) {
//#pragma omp parallel
    {
        findFirst(array, size, firstPosition, search);
    }
//#pragma omp taskwait
    if(*firstPosition == size) {
        std::cout << search << " was not found in the array";
    } else {
        std::cout << "The first position of: " << search << " is: " << *firstPosition;
    }
}

void findFirst(int* array, int size, int* firstPosition, int search) {
    bool swapped;
#pragma omp for schedule(dynamic, 100)
    for(int i = 0; i < size; i++) {
        swapped = false;
        while(!swapped){
            if(array[i] == search && i < *firstPosition) {
                
            }
        }
    }
}