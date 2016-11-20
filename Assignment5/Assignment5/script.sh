g++ reductionTask.cpp -fopenmp -std=c++11
#OMP_SCHEDULE="dynamic,50" ./a.out 1 100000000 1000
#OMP_SCHEDULE="dynamic,50" ./a.out 2 100000000 1000
#OMP_SCHEDULE="dynamic,50" ./a.out 4 100000000 1000
#OMP_SCHEDULE="dynamic,50" ./a.out 8 100000000 1000
OMP_SCHEDULE="dynamic,50" ./a.out 16 100000000 1000
#OMP_SCHEDULE="dynamic,50" ./a.out 1 100000000 10000
#OMP_SCHEDULE="dynamic,50" ./a.out 2 100000000 10000
#OMP_SCHEDULE="dynamic,50" ./a.out 4 100000000 10000
#OMP_SCHEDULE="dynamic,50" ./a.out 8 100000000 10000
OMP_SCHEDULE="dynamic,50" ./a.out 16 100000000 10000

