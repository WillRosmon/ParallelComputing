//
//  staticIntegration.cpp
//  Assignment7
//
//  Created by William Rosmon on 10/27/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <mpi.h>
#include <stdlib.h>

double function(double, double, int, int, int);
double f(double);


int main(int argc, char * argv[]) {
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int numPoints = atoi(argv[3]);
    
    int rank, size;
    double buff;
    
    
    MPI_Init(&argc, &argv);
    MPI_Status status;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::cout << "Initializing " << rank << std::endl;
    double sol = 0;
    
    if(rank != 0) {
        MPI_Recv(&buff, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        std::cout << "rank " << rank << " received " << buff << std::endl;
        sol = function(a, b, numPoints, rank, size);
        MPI_Send(&sol, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        std::cout << "Rank 0 initialized" << std::endl;
        for(int i = 1; i < size; i++) {
            
            MPI_Send(&sol, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
        
        for(int i = 1; i < size; i++) {
            MPI_Recv(&buff, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            sol += buff;
        }
    }
    
    if(rank == 0) {
        sol += function(a, b, numPoints, rank, size);
        std::cout << "Static integration results: " << sol << std::endl;
    }
    MPI_Finalize();
    
    return 0;
}


double function(double a, double b, int n, int rank, int size) {
    int start, end;
    double sol = 0;
    start = rank * (n / size);
    end = start + (n / size) - 1;
    //perform the integration
    for(int i = start; i <= end; i++) {
        
        double inside = (a + i * ( ( b - a ) / n ) ) ;
        sol += f(inside) * ( ( b - a) / n );
    }
    
    return sol;
}

double f(double a) {
    return 1;
}