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

double function(double, double, int, int, int);
double f(double);

int main(int argc, char * argv[]) {
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int numPoints = atoi(argv[3]);
    
    int rank, size;
    double buff;
    double sol = 0;
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(rank == 0) {
        
    } else {
        
    }
    
    if(rank  == 0) {
        for(int i = 0; i < size; i++) {
            MPI_RECV(buff, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sol += buff;
        }
    }
    
    if(rank == 0) {
        std::cout << "Advanced Master Worker Integration Results: " << sol << std::endl;
    }
    
    MPI_FINALIZE();
    return 0;
}