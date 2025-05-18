#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    int dims[2], coords[2], periods[2] = { 0, 0 };
    dims[0] = 0; dims[1] = 0;
    MPI_Dims_create(s, 2, dims);
    MPI_Comm cart_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart_comm);
    MPI_Cart_coords(cart_comm, r, 2, coords);

    std::cout << "[Proc " << r << "] Coords: (" << coords[0] << "," << coords[1] << ")\n";

    MPI_Finalize();
    return 0;
}