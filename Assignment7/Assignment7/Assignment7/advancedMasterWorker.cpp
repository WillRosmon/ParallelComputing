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
void master(double, double, int, double*);

int main(int argc, char * argv[]) {
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int numPoints = atoi(argv[3]);
    int initialBufferSize = atoi(argv[4]);
    
    int rank, size;
    double buff;
    double sol = 0;
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    MPI_status status[size];

    
    if(rank == 0) {
//        for(int i = 0; i < size; i++) {
//            MPI_Isend(i, 1, MPI_INT, i, 0, MPI_COMM_WORLD, 0);
//        }
//        
//        while(i <= size) {
//            MPI_Recv(buff, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
//            MPI_ISend(i++, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD, 0);
//            sol += buff;
//        }
//        for(int i = 0; i < size; i++) {
//            MPI_ISend(-1, 1, MPI_INT, i, 0, MPI_COMM_WORLD, 0);
//        }
        
        master(a, b, numPoints, &sol);
        
    } else {
        int b = 0;
        while(b != -1){
            MPI_Recv(b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            sol = function(a, b, numPoints, b, b);
            MPI_ISend(sol, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, 0);
        }
    }
    
    if(rank == 0) {
        std::cout << "Advanced Master Worker Integration Results: " << sol << std::endl;
    }
    
    MPI_Finalize();
    return 0;
}

double master(double a, double b, int numPoints, double* sol) {
    int rank = 1;
    double work = a;
    double pointIncrement = (b - a) / numPoints;
    double partialSolution;
    int size;
    double initialbuffer[3];
    MPI_request requests[size];
    int nextRequest = 0;
    
    MPI_COMM_size(MPI_COMM_WORLD, &size);
    
    //Send initial 3 pieces of work to each process
    for(rank = 1; rank < size; rank++) {
        for(int i = 0; i < 3 && work < b; i++) {
            buffer[0] = work;
            work += pointIncrement;
        }
        
        MPI_Isend(&initialbuffer, 3, MPI_DOUBLE, rank, 0, MPI_COMM_WORLD)
    }
    
    while(work <= b) {
        MPI_Recv(&partialSolution, 1, MPI_Double, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            sol += partialSum;
            work += partialSolution;
            MPI_Isend(&work, 1, MPI_DOUBLE, status.MPI_SOURCE, 0, MPI_COMM_WORLD, &request[status.MPI_SOURCE]);
        }
    }
}

double function(double a, double b, int n, int start, int end) {
    //perform the integration
    double sol = 0;
    for(int i = start; i <= end; i++) {
        
        double inside = (a + i * ( ( b - a ) / n ) ) ;
        sol += f(inside) * ( ( b - a) / n );
    }
    
    return sol;
}

double f(double a) {
    return 1;
}