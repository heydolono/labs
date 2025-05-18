#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    int win_size = sizeof(int);
    int* window;
    MPI_Win win;

    MPI_Win_allocate(win_size, sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &window, &win);
    *window = 0;

    MPI_Barrier(MPI_COMM_WORLD);

    int one = 1;
    MPI_Fetch_and_op(&one, window, MPI_SUM, 0, 0, win);

    MPI_Win_fence(0, win);

    if (r == 0) {
        std::cout << "Final value: " << *window << "\n";
    }

    MPI_Win_free(&win);
    MPI_Finalize();
    return 0;
}