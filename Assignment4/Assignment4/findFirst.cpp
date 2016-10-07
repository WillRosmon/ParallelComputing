//
//  findFirst.cpp
//  Assignment4
//
//  Created by William Rosmon on 10/6/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <omp.h>
#include <ctime>
#include <chrono>
#include <cmath>

int findFirstOn(int[], int, int);
int findFirstOPos(int[], int, int);

int main(int argc, const char * argv[]) {
    int arraySize = atoi(argv[1]);
    int numToFind = atoi(argv[2]);
    int numThreads = atoi(argv[3]);
    srand(time(NULL));
    
    int randArray[arraySize];
    omp_set_num_threads(numThreads);
    
#pragma omp parallel for schedule(guided)
        for(int i = 0; i < arraySize; i++) {
            randArray[i] = rand() % arraySize;
        }
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    int pos = arraySize;
    pos = findFirstOn(randArray, numToFind, arraySize);
    end = std::chrono::system_clock::now();
    if(pos == arraySize) {
        std::cout << numToFind << " was not found in the array" << std::endl;
    } else {
        std::cout << numToFind << " was found at position: " << pos << std::endl;
    }
    
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "Time elapsed for O(n): " << seconds.count();
    
    start = std::chrono::system_clock::now();
    pos = findFirstOPos(randArray, numToFind, arraySize);
    end = std::chrono::system_clock::now();
    if(pos == arraySize) {
        std::cout << numToFind << " was not found in the array" << std::endl;
    } else {
        std::cout << numToFind << " was found at position: " << pos << std::endl;
    }
}

int findFirstOn (int array[], int numToFind, int size) {
    int pos = size;
#pragma omp parallel for schedule(guided)
        for(int i = 0; i < size; i++) {
            if(array[i] == numToFind && i < pos)
                pos = i;
        }
    
    return pos;
}

int findFirstOPos(int array[], int numToFind, int size) {
    int pos = size;
#pragma omp parallel for schedule(dynamic)
        for(int i = 0; i < size; i++) {
            if(array[i] == numToFind) {
                pos = i;
                i = size;
            }
        }
    return pos;
    
}
