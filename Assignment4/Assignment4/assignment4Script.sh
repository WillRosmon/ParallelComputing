#!/bin/sh

#  assignment4Script.sh
#  Assignment4
#
#  Created by William Rosmon on 10/6/16.
#  Copyright © 2016 William Rosmon. All rights reserved.

g++ findFirst.cpp -fopenmp
./a.out 100000000 5000 1
./a.out 100000000 5000 2
./a.out 100000000 5000 4
./a.out 100000000 5000 8
./a.out 100000000 5000 16

g++ prefixSum.cpp -fopenmp
./a.out 1000000000 1
./a.out 1000000000 2
./a.out 1000000000 4
./a.out 1000000000 8
./a.out 1000000000 16

g++ integration.cpp -fopenmp
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000 1
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000 2
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000 4
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000 8
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000 16
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000 1
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000 2
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000 4
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000 8
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000 16
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000000000 1
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000000000 2
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000000000 4
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000000000 8
OMP_SCHEDULE="dynamic,1" ./a.out 0 100 1000000000 16
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000000000 1
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000000000 2
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000000000 4
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000000000 8
OMP_SCHEDULE="dynamic,1000" ./a.out 0 100 1000000000 16

g++ main.cpp -fopenmp
