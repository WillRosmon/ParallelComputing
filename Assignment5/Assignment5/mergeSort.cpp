//
//  mergeSort.cpp
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

void fillArray(int*, int);
void mainTask(int*, int);
void mergeSort(int*, int, int, int);
void merge(int*, int, int, int, int);
void swap(int*, int*);

int lmain(int argc, const char* argv[]) {
    int arraySize = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    
    if(arraySize == 0 || numThreads == 0) {
        std::cout << "Invalid Parameters" << std::endl;
        return 0;
    }
    
    //omp_set_num_threads(numThreads);
    int* randomArray = new int[arraySize];
    fillArray(randomArray, arraySize);
    
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
    
    //calculate and print the run time
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - begin;
    std::cout << "Merge Sort: Time taken: " << seconds.count();
    std::cout << " Num threads: " << numThreads << std::endl;
    std::cout << std::endl << std::endl;
    //clean up memory
    delete[] randomArray;
    randomArray = NULL;
    
    return 0;
}

//Fill the array with values of 1 - size
void fillArray(int* array, int size) {
    srand(time(NULL));
#pragma omp parallel for schedule(guided)
    for(int i = 0; i < size; i++) {
        array[i] = (rand() % size) + 1;
    }
}

void mainTask(int* array, int size) {
#pragma omp task
    {
        mergeSort(array, 0, size-1, size);
    }
#pragma omp taskwait
    std::cout << "Sorted Array after taskwait:\n";
    for(int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void mergeSort(int* array, int begin, int end, int size) {
    if(size < 2) {
        return;
    }
    
    int leftSize = size / 2;
    int rightSize = size - leftSize;
    int leftEnd = begin + leftSize + 1;
    
#pragma omp task
    {
        mergeSort(array, begin, leftEnd, leftSize);
    }
#pragma omp task
    {
        mergeSort(array, leftEnd+1, end, rightSize);
    }
#pragma omp taskwait
    merge(array, begin, leftEnd, end, size);
}

void merge(int* array, int begin, int rightBegin, int end, int size) {
    if(size == 1) {
        return;
    }
    std::cout << "\nIn Merge: Array Size: " << size << " ";
    std::cout << "Parameters: Begin " << begin << " End: "
        << end << " Right Begin: " << rightBegin << " values: ";
    for(int i = begin; i <= end; i++) {
        if(i < rightBegin) {
        }
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    if(size <= 2) {
        std::cout << "Array size is 2, checking for swap" << std::endl;
        if(array[end] < array[begin]) {
            std::cout << " Elements require swapping";
            swap(&array[end], &array[begin]);
            std::cout << " Array after swapping: ";
            for(int i = begin; i <= end; i++) {
                std::cout << array[i] << " ";
            }
            std::cout << std::endl;
        }
    } else {
        
        int a, b, c, anum, bnum;
        a = begin;
        b = rightBegin + 1;
        int aEnd = b;
        c = 0;
        int* tempArray = new int[size];
        std::cout << "A's starting position is: " << a << std::endl;
        std::cout << "B's starting position is: " << b << std::endl;
        while(c < size) {
            if(array[a] > array[b] && b <= end) {
                std::cout << array[b] << " is being inserted into the temporary array from B slot " << b << "at slot " << c << std::endl;
                tempArray[c] = array[b];
                std::cout << "value of that slot after insertion is: " << tempArray[c] << std::endl;
                b++;
                std::cout << "Value of B: " << b << std::endl;
            } else if (a <= aEnd) {
                tempArray[c] = array[a];
                std::cout << array[a] << " is being inserted into the temporary array from A slot " << a << "at slot " << c << std::endl;
                std::cout << "value of that slot after insertion is: " << tempArray[c] << std::endl;
                a++;
                std::cout << "A's position: " << a;
            }
            c++;
        }
        std::cout << "Values in temp array post merge: ";
        for(int i = 0; i < size; i++) {
            std::cout << tempArray[i] << " ";
        }
        std::cout << std::endl;
        
        //copy temp array back into original array
        c = 0;
        for(int i = begin; i <= end; i++)
        {
            array[i] = tempArray[c];
            c++;
        }
        //clean up tempArray
        delete[] tempArray;
        tempArray = NULL;
        
        
    }
    
    std::cout << "Solution thus far: " << std::endl;
    for(int i = 0; i < 10; i++) {
        std::cout << i << "      " << array[i] << std::endl;
    }
    std::cout << std::endl;
}

void swap(int* a, int* b) {
    int tempA = *a;
    int tempB = *b;
    *b = tempA;
    *a = tempB;
}