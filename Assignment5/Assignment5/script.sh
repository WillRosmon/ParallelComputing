g++ reductionTask.cpp -fopenmp -std=c++11
OMP_SCHEDULE="dynamic,50" ./a.out 16 1000000000 1000
