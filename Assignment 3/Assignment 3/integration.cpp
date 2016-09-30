//
//  main.cpp
//  Assignment 3
//
//  Created by William Rosmon on 9/8/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cmath>


double function(double, double, int);
double f(double);
double function(double, double, int, int);
double f(double, int);

int main(int argc, const char * argv[]) {
    
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int numPoints = atoi(argv[3]);
    int complexity = atoi(argv[4]);
    
    std::cout << "Sequential: ";
    std::cout << function(a, b, numPoints) << std::endl;
    
    std::cout << "with an intensity of " << complexity << ": ";
    std::cout << function(a, b, numPoints, complexity) << std::endl;
    
    return 0;
}

double function(double a, double b, int n) {
    double sol = 0;
    //f(x) = 1
    
    for(int i = 0; i < n; i++) {
        double inside = (a + i * ( ( b - a ) / n ) ) ;
        sol += f(inside) * ( ( b - a) / n );
    }
    
    return sol;
}

double function(double a, double b, int n, int c) {
    double sol = 0;
    for(int i = 0; i < n; i++) {
        double inside = (a + i * ( ( b - a ) / n ) );
        sol += f(inside, c) * ((b-a) / n);
    }
    return sol;
}

double f(double a) {
    return 1;
}

double f(double a, int c) {
    int x;
    for(int i = 0; i < c; i++) {
        x = pow(1, 2);
        x = sqrt(1);
    }
    return 1;
}