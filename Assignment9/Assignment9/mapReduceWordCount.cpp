//
//  main.cpp
//  Assignment9
//
//  Created by William Rosmon on 11/20/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <mpi.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"
#include "mapreduce.h"
#include "keyvalue.h"

using namespace MAPREDUCE_NS;


void fileReader(int taskID, char* fileName,int listSize, KeyValue* keyValue, void* voidPtr) {
    struct stat stbuff;
    int err = stat(fileName, &stbuff);
    if(err < 0) {
        std::cout << "Error Opening File.";
        MPI_Abort(MPI_COMM_WORLD, 1);
        return;
    }
    int fileSize = stbuff.st_size;
    
    FILE* filePointer = fopen(fileName, "r");
    char* fileText = new char[fileSize+1];
    int size = fread(fileText, 1, fileSize, filePointer);
    fileText[size] = '\0';
    
    char* delimiters = " \n\t\f\r\0";
    char* word = strtok(fileText, delimiters);
    
    while(word != NULL) {
        keyValue->add(word, strlen(word)+1, NULL, 0);
        word = strtok(NULL, delimiters);
    }
    
    delete[] fileText;
    fileText = NULL;
}

int main(int argc, const char * argv[]) {
    
    if(argc <= 1) {
        std::cout << "Not enough arguments entered. Exiting\n";
        std::cout << "Please enter at least one file name \n";
        return -1;
    }
    
    char filesList;
    int rank, size;
    
    MPI_Init(&argc, (char***)&argv);
    
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    MapReduce* mapreduce = new MapReduce(MPI_COMM_WORLD);
    mapreduce -> verbosity = 2;
    mapreduce->mapstyle = 2;
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    //int nmap, int nstr, char **strings, int recurse, int readfile, char sepchar, int delta, void (*mymap)(int, char *, int, KeyValue *, void *), void *ptr
    
    int nstrings = argc - 1;
    int numTasks = (size * nstrings) / 2;
    mapreduce-> map(numTasks, nstrings,(char**) argv, 0, 0, '\n', 1000, fileReader, NULL);

    MPI_Barrier(MPI_COMM_WORLD);
    mapreduce -> collate(NULL);
    MPI_Barrier(MPI_COMM_WORLD);
    
    
    
    MPI_Finalize();
    return 0;
}
