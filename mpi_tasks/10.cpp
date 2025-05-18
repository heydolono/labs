#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    if (s < 2) return 1;

    MPI_Request req;
    MPI_Status stat;
    char msg[] = "Hello async";

    if (r == 0) {
        MPI_Isend(msg, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &req);
        MPI_Wait(&req, &stat);
    }
    else if (r == 1) {
        char buff[100];
        MPI_Irecv(buff, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &req);
        MPI_Wait(&req, &stat);
        std::cout << "[1] Got: " << buff << "\n";
    }

    MPI_Finalize();
    return 0;
}