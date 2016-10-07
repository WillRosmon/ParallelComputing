//
//  main.cpp
//  Assignment4
//
//  Created by William Rosmon on 9/29/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <omp.h>
#include <ctime>
#include <chrono>
#include <cmath>

//OMP_SCHEDULE="dynamic,12" ./a.out

int main(int argc, const char * argv[]) {
    int arraySize = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    srand(time(NULL));
    
    double randArray[arraySize];
    omp_set_num_threads(numThreads);
    
#pragma omp parallel for schedule(runtime)
    //set random values to random array
        for(int i = 0; i < arraySize; i++) {
            randArray[i] = rand();
        }
    
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
#pragma omp parallel for schedule(runtime)
    //square root each value
        for(int i = 0; i < arraySize; i++) {
            randArray[i] = sqrt(randArray[i]);
        }
    

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - start;
    
    std::cout << "Square Root Time Elapsed: " << seconds.count();
    
    start = std::chrono::system_clock::now();
    int minimum = randArray[0];
    
#pragma omp parallel for reduction(min:minimum) schedule(runtime)
    
    //find the minimum value in the array
        for(int i = 0; i < arraySize; i++) {
            if(randArray[i] < minimum)
                minimum = randArray[i];
        }
    
    
    end = std::chrono::system_clock::now();
    seconds = end - start;
    std::cout << "Minimum Reduction Time Elapsed: " << seconds.count();
    
    
    return 0;
}

