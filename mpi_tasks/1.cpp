#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    if (s < 2) return 1;

    if (r == 0) {
        const char* msg = "Hello from 0";
        MPI_Send(msg, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    }
    else if (r == 1) {
        char buff[100];
        MPI_Recv(buff, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "[1] Recv: " << buff << "\n";
    }

    MPI_Finalize();
    return 0;
}