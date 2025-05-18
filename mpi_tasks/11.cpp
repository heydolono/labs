#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    const int N = 1000000;
    float data[N];
    float local_sum = 0, total_sum = 0;

    for (int i = 0; i < N; ++i) data[i] = 1.0f;

    int chunk = N / s;
    float* local_data = new float[chunk];

    MPI_Scatter(data, chunk, MPI_FLOAT,
        local_data, chunk, MPI_FLOAT,
        0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; ++i) local_sum += local_data[i];

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (r == 0) {
        std::cout << "Total sum: " << total_sum << "\n";
    }

    delete[] local_data;
    MPI_Finalize();
    return 0;
}