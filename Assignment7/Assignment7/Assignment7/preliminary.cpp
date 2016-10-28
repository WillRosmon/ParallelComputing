//
//  main.cpp
//  Assignment7
//
//  Created by William Rosmon on 10/20/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char * argv[]) {
    
    int rank, size;
    int hostNameSize = 1024;
    char hostName[hostNameSize];
    
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(gethostname(hostName, hostNameSize) == 0) {
        hostName[hostNameSize - 1] = '\0';
        std::cout << "Host Name is: " << hostName << std::endl;
    } else {
        std::cout << "An Error occured trying to retrieve host name." << std::endl;
    }
    
    std::cout << "Rank is: " << rank << std::endl;
    
    MPI_Finalize();
    
    return 0;
}
