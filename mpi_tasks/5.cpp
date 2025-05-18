#include <mpi.h>
#include <iostream>

#define SIZE 128

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    float A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

    if (r == 0) {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }
    }

    float localA[SIZE * SIZE / s], localC[SIZE * SIZE / s];
    MPI_Scatter(A, SIZE * SIZE / s, MPI_FLOAT,
        localA, SIZE * SIZE / s, MPI_FLOAT,
        0, MPI_COMM_WORLD);

    for (int i = 0; i < SIZE / s; ++i)
        for (int j = 0; j < SIZE; ++j) {
            localC[i * SIZE + j] = 0;
            for (int k = 0; k < SIZE; ++k) {
                localC[i * SIZE + j] += localA[i * SIZE + k] * B[k][j];
            }
        }

    MPI_Gather(localC, SIZE * SIZE / s, MPI_FLOAT,
        C, SIZE * SIZE / s, MPI_FLOAT,
        0, MPI_COMM_WORLD);

    if (r == 0) {
        std::cout << "Done.\n";
    }

    MPI_Finalize();
    return 0;
}