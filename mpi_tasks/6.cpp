#include <mpi.h>
#include <omp.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

#pragma omp parallel
    {
        int t = omp_get_thread_num();
        int tn = omp_get_num_threads();

        std::cout << "[MPI " << r << "/" << s << "] Thread " << t << "/" << tn << "\n";
    }

    MPI_Finalize();
    return 0;
}