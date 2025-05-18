#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    int r, s;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    MPI_Group world_group, new_group;
    MPI_Comm new_comm;

    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
    int ranks[s];
    for (int i = 0; i < s; ++i) ranks[i] = i;
    MPI_Group_incl(world_group, s, ranks, &new_group);
    MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

    if (r == 0) {
        std::cout << "Group created.\n";
    }

    MPI_Finalize();
    return 0;
}