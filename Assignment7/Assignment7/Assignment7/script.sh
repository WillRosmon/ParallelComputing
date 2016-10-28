#!/bin/sh

#  script.sh
#  Assignment7
#
#  Created by William Rosmon on 10/20/16.
#  Copyright © 2016 William Rosmon. All rights reserved.

mpicxx preliminary.cpp
mpiexec -np 32 ./a.out

mpicxx staticIntegration.cpp
mpiexec -np 1 ./a.out 0 100 1000 10
mpiexec -np 1 ./a.out 0 100 1000000000 10
mpiexec -np 1 ./a.out 0 100 1000 1000
mpiexec -np 1 ./a.out 0 100 1000000000 1000

mpiexec -np 2 ./a.out 0 100 1000 10
mpiexec -np 2 ./a.out 0 100 1000000000 10
mpiexec -np 2 ./a.out 0 100 1000 1000
mpiexec -np 2 ./a.out 0 100 1000000000 1000

mpiexec -np 4 ./a.out 0 100 1000 10
mpiexec -np 4 ./a.out 0 100 1000000000 10
mpiexec -np 4 ./a.out 0 100 1000 1000
mpiexec -np 4 ./a.out 0 100 1000000000 1000

mpiexec -np 8 ./a.out 0 100 1000 10
mpiexec -np 8 ./a.out 0 100 1000000000 10
mpiexec -np 8 ./a.out 0 100 1000 1000
mpiexec -np 8 ./a.out 0 100 1000000000 1000

mpiexec -np 16 ./a.out 0 100 1000 10
mpiexec -np 16 ./a.out 0 100 1000000000 10
mpiexec -np 16 ./a.out 0 100 1000 1000
mpiexec -np 16 ./a.out 0 100 1000000000 1000

mpiexec -np 32 ./a.out 0 100 1000 10
mpiexec -np 32 ./a.out 0 100 1000000000 10
mpiexec -np 32 ./a.out 0 100 1000 1000
mpiexec -np 32 ./a.out 0 100 1000000000 1000

mpicxx masterWorkerIntegration.cpp