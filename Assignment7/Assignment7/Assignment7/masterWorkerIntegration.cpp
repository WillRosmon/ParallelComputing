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
        for(int i = 0; i < size; i++) {
            int start, end;
            start = rank * (numPoints / size);
            end = start + (numPoints / size) - 1;
            int b[2];
            b[0] = start;
            b[1] = end;
            MPI_Send(b, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
//        for(int i = 1; i < size; i++) {
//            MPI_Recv((void*)&buff, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//            sol += (int)buff;
//        }
        } else {
            int bu[2];
            MPI_Recv((void*)&b, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sol = function(a, b, numPoints, bu[0], bu[1]);
            MPI_Send((void*)&sol, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    if(rank == 0) {
        std::cout << "Integration Results: " << sol << std::endl;
    }
    MPI_Finalize();
    
    return 0;
}


double function(double a, double b, int n, int start, int end) {
    //perform the integration
    int sol = 0;
    for(int i = start; i <= end; i++) {
        
        double inside = (a + i * ( ( b - a ) / n ) ) ;
        sol += f(inside) * ( ( b - a) / n );
    }
    
    return sol;
}

double f(double a) {
    return 1;
}