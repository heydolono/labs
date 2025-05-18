#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    const int BUF_SIZE = 100;
    char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];

    sprintf(send_buf, "Message from %d", r);

    MPI_Bsend(send_buf, BUF_SIZE, MPI_CHAR, (r + 1) % s, 0, MPI_COMM_WORLD);

    MPI_Recv(recv_buf, BUF_SIZE, MPI_CHAR, (r + s - 1) % s, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "[Proc " << r << "] Received: " << recv_buf << "\n";

    MPI_Finalize();
    return 0;
}