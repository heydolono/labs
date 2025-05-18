#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    double start = MPI_Wtime();

    // Просто пауза
    for (long long i = 0; i < 100000000; ++i);

    double end = MPI_Wtime();

    if (r == 0) {
        std::cout << "Time: " << end - start << " sec\n";
    }

    MPI_Finalize();
    return 0;
}