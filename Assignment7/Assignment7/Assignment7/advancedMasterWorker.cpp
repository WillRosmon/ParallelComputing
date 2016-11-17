//
//  advancedMasterWorker.cpp
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
    double sol = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(rank == 0) {
        for(int i = 0; i < size; i++) {
            MPI_ISend(i, 1, MPI_INT, i, 0, MPI_COMM_WORLD, 0);
        }
        
        while(i <= size) {
            MPI_Recv(buff, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            MPI_ISend(i++, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD, 0);
            sol += buff;
        }
        for(int i = 0; i < size; i++) {
            MPI_ISend(-1, 1, MPI_INT, i, 0, MPI_COMM_WORLD, 0);
        }
        
        
    } else {
        int b = 0;
        while(b != -1){
            MPI_Recv(b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            sol = function(a, b, numPoints, b, b);
            MPI_Send(sol, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, 0);
        }
    }
    
    if(rank == 0) {
        std::cout << "Advanced Master Worker Integration Results: " << sol << std::endl;
    }
    
    MPI_Finalize();
    return 0;
}

double function(double a, double b, int n, int start, int end) {
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