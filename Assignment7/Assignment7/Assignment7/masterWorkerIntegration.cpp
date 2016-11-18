//
//  masterWorkerIntegration.cpp
//  Assignment7
//
//  Created by William Rosmon on 10/27/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <mpi.h>
#include <stdlib.h>

double function(double, double, int);
double f(double);
void master(double, double, int, double);
void worker();


int main(int argc, char * argv[]) {
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int numPoints = atoi(argv[3]);
    
    int rank;
    double buff;
    double sol = 0;
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0) {
        master(a, b, numPoints, sol);
    } else {
        worker();
    }
    if(rank == 0) {
        std::cout << "Integration Results: " << sol << std::endl;
    }
    MPI_Finalize();
    
    return 0;
}

void master(double a, double b, int numPoints, double sol) {
    int size;
    double work = a;
    double pointIncrement = (b - a) / numPoints;
    int rank = 1;
    double partialSolution = 0;
    MPI_Status status;
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    for(rank = 1; rank < size; rank++) {
        if(work <= b) {
            MPI_Send((void*)&work, 1, MPI_DOUBLE, rank, 0, MPI_COMM_WORLD);
            work += pointIncrement;
        }
    }
    
    while(work <= b) {
        MPI_Recv(&partialSolution, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        sol += partialSolution;
        work += pointIncrement;
        if(work <= b) {
            MPI_Send(&work, 1, MPI_DOUBLE, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
            work+= pointIncrement;
        }
    }
    
    for(rank = 1; rank < size; rank++) {
        MPI_Recv(&partialSolution, 1, MPI_DOUBLE, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sol += partialSolution;
    }
    
    for(rank = 1; rank < size; rank++) {
        MPI_Send(-1, 1, MPI_DOUBLE, rank, 0, MPI_COMM_WORLD);
    }
}

void worker() {
    double partialSolution = 0;
    double work;
    MPI_Status status;
    
    MPI_Recv(&work, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
    
    if(work == -1) {
        return;
    } else {
        partialSolution = function(work, work, 1);
        MPI_Send(&partialSolution, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
}


double function(double a, double b, int n) {
    //perform the integration
    double sol = 0;
    for(int i = a; i <= b; i++) {
        
        double inside = (a + i * ( ( b - a ) / n ) ) ;
        sol += f(inside) * ( ( b - a) / n );
    }
    
    return sol;
}

double f(double a) {
    return 1;
}