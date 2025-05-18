#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    MPI_File file;
    MPI_File_open(MPI_COMM_WORLD, "input.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &file);

    int chunk = 1024;
    char buffer[chunk];
    MPI_Status status;

    MPI_File_read_at(file, r * chunk, buffer, chunk, MPI_CHAR, &status);

    std::cout << "[Proc " << r << "] Read: " << buffer << "\n";

    MPI_File_close(&file);
    MPI_Finalize();
    return 0;
}