//
//  prefixSum.cpp
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


int main(int argc, const char * argv[]) {
    int arraySize = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    srand(time(NULL));
    
    int randArray[arraySize];
    int prefixSum[arraySize];
    omp_set_num_threads(numThreads);
    
    int lastPositions[numThreads];
    int lastPositionValues[numThreads];
    std::chrono::time_point<std::chrono::system_clock> start, end;
    
#pragma omp parallel
    {
#pragma omp for schedule(static)
        {
            //Get indices of last positions for each thread
            for(int i = 0; i < numThreads; i++) {
                lastPositions[i] = arraySize / numThreads * (i + 1) - 1;
            }
        }
#pragma omp for schedule(guided)
        {
            for(int i = 0; i < arraySize; i++) {
                randArray[i] = rand() % arraySize;
                prefixSum[i] = 0;
            }
        }
        
        
        start = std::chrono::system_clock::now();
#pragma omp for schedule(static)
        {
            for(int i = 0; i < arraySize; i++) {
                prefixSum[i] = prefixSum[i-1] + randArray[i];
            }
        }
        
#pragma omp for shceudle(static)
        {
            for(int i = 0; i < numThreads; i++) {
                lastPositionValues[i] = prefixSum[lastPositions[i]];
            }
        }
    }
    
#pragma omp for scheudle(static)
    {
        for(int i = 0; i < numThreads; i++) {
            for(int j = lastPositions[i]; j < arraySize; i++) {
                prefixSum[j] += lastPositionValues[i];
            }
        }
    }
    
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - start;
    
    std::cout << "Time taken for prefix sum: " << seconds.count();
    
}