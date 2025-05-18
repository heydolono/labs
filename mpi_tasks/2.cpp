#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    int nxt = (r + 1) % s;
    int prv = (r - 1 + s) % s;
    int snd = r, rcv;

    MPI_Sendrecv(&snd, 1, MPI_INT, nxt, 0, &rcv, 1, MPI_INT, prv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "[" << r << "] Got: " << rcv << "\n";

    MPI_Finalize();
    return 0;
}