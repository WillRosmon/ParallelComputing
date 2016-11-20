//
//  advancedMaster_Worker.cpp
//  Assignment7
//
//  Created by William Rosmon on 11/19/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h>

const int WORK_ASSIGNMENT = 0;
const int REQUEST_WORK = 1;
const int WORK_COMPLETED = 2;
const int TERMINATE = 3;

double f(double x, int complexity) {
    for(int i = 0; i < complexity; i++) {
        x = pow(x, 2);
        x = sqrt(x);
    }
    return x;
};

double function(double a, double b, int n, int start, int end, int complexity) {
    //perform the integration
    double sol = 0;
    for(int i = start; i <= end; i++) {
        double inside = (a + i * ( ( b - a ) / n ) ) ;
        sol += f(inside, complexity) * ( ( b - a) / n );
    }
    
    return sol;
}

void initializeBuffer(double* buffer, double a, double b, int numPoints) {
    double increment = (b - a) / numPoints;
    for(int i = 0; i < numPoints; i++) {
        buffer[i] = increment * i + a;
    }
}

double master(double a, double b, int numPoints, double* sol, int initialSize, double* buffer) {
    int size                = MPI_COMM_size(MPI_COMM_WORLD, &size);
    int sizeToSend          = initialSize;
    int bufferPos           = 0;
    double* bufferPoint     = &buffer[bufferPos];
    int workToComplete      = numPoints;
    MPI_Status status;
    double partialSolution = 0;
    double inputBuffer
    
    initializeBuffer(bufferPoint,a, b, numPoints);
    MPI_Request requests[size];
    
    //send initial requests
    for(int i = 1; i < size; i++) {
        if(workToComplete == 0) {
            break;
        }
        if(workToComplete >= sizeToSend) {
            MPI_Isend(&bufferPoint, sizeToSend, MPI_DOUBLE, i, 0, &requests[i]);
            bufferPoint = &buffer[i * sizeToSend];
            workToComplete -= sizeToSend;
        } else {
            MPI_Isend(&bufferPoint, workToComplete, MPI_DOUBLE, i, 0, &requests[i]);
            workToSend = 0;
        }
    }
    while(workToComplete > 0) {
        MPI_Recv();
    }
    
    //Send termination signal to all worker processed
    for(int i = 0; i < )
}

void incrementBufferPosition(int* position, int bufferSize) {
    int newPosition = *position + 1;
    *position = newPosition;
    if( *position >= bufferSize) {
        *position = 0;
    }
}

void incrementRequestBuffer(int* position, int bufferSize) {
    int newPosition = *position + 1;
    *position = newPosition;
    if(*position >= bufferSize) {
        *position = 0;
    }
}

void worker(int rank, int initialBufferSize) {
    double* buffer = new double[initialBufferSize];
    double* emptyBufferBegin = &buffer[0];
    double* sendBuffer[initialBufferSize];
    int nextWorkPosition = 0;
    int nextSendBufferPosition = 0;
    int emptyBufferSize = initialBufferSize;
    int workRequestAmount = 0;
    MPI_Status status;
    MPI_Request requests[initialBufferSize];
    int newRequest = 0;
    int count;
    bool terminate = false;
    
    //Receive initial payload
    MPI_Recv(&buffer, initialBufferSize, MPI_DOUBLE, 0, WORK_ASSIGNMENT, MPI_COMM_WORLD, &status);
    int receivedCount = MPI_GET_COUNT(&status, MPI_DOUBLE, &count);
    emptyBuffersize = initilBufferSize - receivedCount;
    if(emptyBufferSize > 0) {
        if(emptyBufferSize < 10) {
            workRequestAmount = 9;
        } else {
            workRequestAmount = emptyBufferSize;
        }
        
        MPI_Isend(&workRequestAmount, 1, MPI_DOUBLE, 0, REQUEST_WORK, MPI_COMM_WORLD, &request[newRequest]);
        incrementRequestBuffer(&newRequest, initialBufferSize);
    }
    
    //continue processing work
    while(!terminate) {
        double partialSolution = function((double)work, (double)work + 1, 1);
        sendBuffer[nextSendBufferPosition] = partialSolution;
        incrementBufferPosition(&nextSendBufferPosition, initialBufferSize);
        MPI_Isend(sendBuffer[nextSendBufferPosition], 1, MPI_DOUBLE, 0, WORK_COMPLETED, MPI_COMM_WORLD, &request[newRequest]);
        incrementRequestBuffer(&newRequest, initialBufferSize);
        
        
    }
}

int main(int argc, char * argv[]) {
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int numPoints = atoi(argv[3]);
    int initialBufferSize = atoi(argv[4]);
    int rank, size, sizeToSend;
    double* buffer = new double[numPoints];
    double sol = 0;
    
    //create and populate array of random integers
    
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank == 0) {
        master(a, b, numPoints, &sol, initialBufferSize, buffer);
    } else {
        worker(rank, initialBufferSize);
    }
    
    if(rank == 0) {
        MPI_FINALIZE();
    }
}









