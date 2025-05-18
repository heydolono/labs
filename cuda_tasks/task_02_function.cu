#include <math.h>
#include <cuda_runtime.h>
#include <iostream>

#define N (1 << 20)

__global__ void kernelB(float *x, float *y) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < N) y[i] = sinf(x[i]) * cosf(x[i]);
}

int main() {
    float *dX, *dY;
    size_t sz = N * sizeof(float);

    cudaMalloc(&dX, sz);
    cudaMalloc(&dY, sz);

    dim3 block(256), grid((N + block.x - 1) / block.x);
    kernelB<<<grid, block>>>(dX, dY);

    cudaFree(dX); cudaFree(dY);
    return 0;
}