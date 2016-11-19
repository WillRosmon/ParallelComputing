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

int main(int argc, const char* argv[]) {
    int arraySize = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    
    if(arraySize == 0 || numThreads == 0) {
        std::cout << "Invalid Parameters" << std::endl;
        return 0;
    }
    
    omp_set_num_threads(numThreads);
    int* randomArray = new int[arraySize];
    populateArray(randomArray, size);
    
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
