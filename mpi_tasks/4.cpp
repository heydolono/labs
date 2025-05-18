#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    const int ALPHABET = 26;
    const int N = 1024;
    char str[N];
    int local[ALPHABET] = { 0 }, total[ALPHABET] = { 0 };

    if (r == 0) {
        std::cin >> str;
    }

    MPI_Bcast(str, N, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = r; i < N; ++i += s) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            local[str[i] - 'a']++;
        }
    }

    MPI_Reduce(local, total, ALPHABET, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (r == 0) {
        for (int i = 0; i < ALPHABET; ++i) {
            if (total[i]) {
                std::cout << (char)('a' + i) << " : " << total[i] << "\n";
            }
        }
    }

    MPI_Finalize();
    return 0;
}