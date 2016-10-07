//
//  integration.cpp
//  Assignment4
//
//  Created by William Rosmon on 10/4/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <omp.h>
#include <ctime>
#include <chrono>
#include <cmath>

double function(double, double, int);
double f(double);

int main(int argc, const char * argv[]) {
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int numPoints = atoi(argv[3]);
    int numThreads = atoi(argv[4]);
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::cout << function(a, b, numPoints) << std::endl;
    end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> seconds = end - start;
    
    std::cout << "Integration Time Elapsed: " << seconds.count();
    
    return 0;
}

double function(double a, double b, int n) {
    double sol = 0;
    
#pragma omp parallel for schedule(runtime)
    //perfoem the integration
        for(int i = 0; i < n; i++) {
            double inside = (a + i * ( ( b - a ) / n ) ) ;
            sol += f(inside) * ( ( b - a) / n );
        }
    
    
    return sol;
}
//Easy integration of f(x) = 1 to ensure correctness
double f(double a) {
    return 1;
}
