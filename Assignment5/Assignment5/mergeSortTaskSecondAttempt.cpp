//
//  mergeSortTask.cpp
//  Assignment5
//
//  Created by William Rosmon on 11/19/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <stdio.h>
#include <iostream>
//#include <omp.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <math.h>

void populateArray(int*, int);
void mainTask(int*, int);
void mergeSort(int*, int, int*);
void merge(int*, int*, int*, int, int, int);
void swap(int*, int*);
void printArray(int*, int);

int main(int argc, const char* argv[]) {
//    if(argc < 3) {
//        std::cout << "Invalid Arguments.";
//        return -1;
//    }
    int arraySize = 10;//atoi(argv[1]);
    int numThreads = 2;//atoi(argv[2]);
    
    if(arraySize == 0 || numThreads == 0) {
        std::cout << "Invalid Parameters" << std::endl;
        return 0;
    }
    
    //omp_set_num_threads(numThreads);
    int* randomArray = new int[arraySize];
    populateArray(randomArray, arraySize);
    int* solutionArray = new int[arraySize];
    std::cout << "Original Array: ";
    printArray(randomArray, arraySize);

    std::chrono::time_point<std::chrono::system_clock> begin, end;
    
    //begin the clock
    begin = std::chrono::system_clock::now();
#pragma omp parallel
    {
#pragma omp for schedule(guided)
        for(int i = 0; i < arraySize; i++) {
            solutionArray[i] = 0;
        }
#pragma omp single
        mergeSort(randomArray, arraySize, solutionArray);
    }
    
    printArray(solutionArray, arraySize);
    
    //calculate and print the run time
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - begin;
    std::cout << "Merge Sort: Time taken: " << seconds.count();
    std::cout << " Num threads: " << numThreads << std::endl;
    std::cout << std::endl << std::endl;
    //clean up memory
    delete[] randomArray;
    delete[] solutionArray;
    randomArray = NULL;
    solutionArray = NULL;
}

//Fill the array with values of 1 - size
void populateArray(int* array, int size) {
    srand(time(NULL));
#pragma omp parallel for schedule(guided)
    for(int i = 0; i < size; i++) {
        array[i] = (rand() % size) + 1;
    }
}


void mergeSort(int* array, int size, int* worker) {
    if(size < 2) {
        worker[0] = array[0];
        return;
    }
    int leftArraySize;
    int rightArraySize;
    leftArraySize = size / 2;
    rightArraySize = size - leftArraySize;
    //std::cout << "Left Array Size: " << leftArraySize << "\n";
    //std::cout << "Right Array Size: " << rightArraySize << std::endl;
    int* tempLeftArray = new int[leftArraySize];
    int* tempRightArray = new int[rightArraySize];

#pragma omp for schedule(guided)
    for(int i = 0; i < size; i++) {
        if(i < leftArraySize) {
            tempLeftArray[i] = array[i];
        } else {
            tempRightArray[i - leftArraySize] = array[i];
        }
    }
    
    int* rightSorted = new int[rightArraySize];
    int* leftSorted = new int[leftArraySize];
    
    //initialize local arrays
#pragma omp for schedule(guided)
    for(int i = 0; i < size / 2 + 1; i++) {
        if(i < leftArraySize) {
            leftSorted[i] = 0;
        }
        if(i < rightArraySize) {
            leftSorted[i] = 0;
        }
    }
    
    std::cout << "Original Left Array Values: ";
    printArray(tempLeftArray, leftArraySize);
    std::cout << "Original Right Array Values: ";
    printArray(tempRightArray, rightArraySize);
#pragma omp task
    {
        mergeSort(tempLeftArray, leftArraySize, leftSorted);
    }
#pragma omp task
    {
        mergeSort(tempRightArray, rightArraySize, rightSorted);
    }
#pragma omp taskwait
    merge(leftSorted, rightSorted, worker, size, leftArraySize, rightArraySize);
    
    //clean up temporary arrays
    delete[] tempLeftArray;
    delete[] tempRightArray;
    delete[] leftSorted;
    delete[] rightSorted;
    tempLeftArray = NULL;
    tempRightArray = NULL;
    leftSorted = NULL;
    rightSorted = NULL;
}

void merge(int* leftArray, int* rightArray, int* sol, int size, int leftSize, int rightSize) {
    int leftIndex = 0;
    int rightIndex = 0;
    int solIndex = 0;
    
    std::cout << "Left Array Values: ";
    printArray(leftArray, leftSize);
    std::cout << "Right array values: ";
    printArray(rightArray, rightSize);
    
    
    while(leftIndex < leftSize && rightIndex < rightSize && solIndex < size) {
        std::cout << "MERGING   ";
        if(leftArray[leftIndex] <= rightArray[rightIndex]) {
            sol[solIndex] = leftArray[leftIndex];
            leftIndex++;
        } else {
            sol[solIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        solIndex++;
        std::cout << "Sol Index: " << solIndex << std::endl;
        std::cout << "Sol Size: " << size << std::endl;
        std::cout << "right index: " << rightIndex << std::endl;
        std::cout << "right size: " << rightSize << std::endl;
        std::cout << "left index: " << leftIndex << std::endl;
        std::cout << "Left Size: " << leftSize << std::endl;
    }
    
    if(rightIndex < rightSize) {
        //std::cout << "Moving remaining elements from right to sol" << std::endl;
        while (rightIndex < rightSize && solIndex < size) {
            sol[solIndex] = rightArray[rightIndex];
            rightIndex++;
            solIndex++;
        }
    } else if(leftIndex < leftSize) {
        //std::cout << "Moving remaining elements from Left to sol" << std::endl;
        while(leftIndex < leftSize && solIndex < size) {
            sol[solIndex] = leftArray[leftIndex];
            solIndex++;
            leftIndex++;
        }
    }
    
    std::cout << " +++++++++++++ POST MERGE VALUES +++++++++++++++\n";
    std::cout << "Right Array - original: ";
    printArray(rightArray, rightSize);
    std::cout << "Left Array - Original: ";
    printArray(leftArray, leftSize);
    std::cout << "SOL VALUES: ";
    printArray(sol, size);
    std::cout << " +++++++++++++ ////POST MERGE VALUES\\\\ +++++++++++++++\n";
}

void newMerge(int* leftArray, int* rightArray, int* sol, int size, int leftSize, int rightSize, int* mergedArray) {
    
}

void printArray(int* array, int size) {
    for(int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
