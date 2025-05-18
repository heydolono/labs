#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    MPI_File file;
    MPI_Status status;

    MPI_File_open(MPI_COMM_WORLD, "output.txt",
        MPI_MODE_CREATE | MPI_MODE_WRONLY,
        MPI_INFO_NULL, &file);

    const char* msg = "Hello from process\n";
    MPI_File_write_ordered(file, msg, 17, MPI_CHAR, &status);

    MPI_File_close(&file);

    MPI_Finalize();
    return 0;
}