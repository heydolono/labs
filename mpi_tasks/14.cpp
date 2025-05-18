#include <mpi.h>
#include <iostream>

struct Data {
    int id;
    float val;
};

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    MPI_Datatype MPI_DATA;
    MPI_Type_contiguous(2, MPI_INT, &MPI_DATA);
    MPI_Type_commit(&MPI_DATA);

    Data send = { r, 3.14f };
    Data recv;

    MPI_Sendrecv(&send, 1, MPI_DATA, (r + 1) % s, 0,
        &recv, 1, MPI_DATA, (r + s - 1) % s, 0,
        MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "[Proc " << r << "] Got ID: " << recv.id << ", Val: " << recv.val << "\n";

    MPI_Type_free(&MPI_DATA);
    MPI_Finalize();
    return 0;
}