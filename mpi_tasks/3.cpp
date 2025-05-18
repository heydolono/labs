#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    for (int i = 0; i < s; ++i) {
        if (i != r) {
            MPI_Send(&r, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    int m;
    for (int i = 0; i < s; ++i) {
        if (i != r) {
            MPI_Recv(&m, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "[" << r << "] From " << i << ": " << m << "\n";
        }
    }

    MPI_Finalize();
    return 0;
}