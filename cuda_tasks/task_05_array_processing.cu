#include <cuda_runtime.h>
#include <math.h>

#define N (512 * 50000)

__global__ void processArray(float *A, float *B, float *C) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < N) {
        float val = A[i] * B[i];
        float sum = 0;
        for (int j = 0; j < 100; ++j) sum += sinf(j + val);
        C[i] = sum;
    }
}

int main() {
    float *dA, *dB, *dC;
    size_t sz = N * sizeof(float);

    cudaMalloc(&dA, sz);
    cudaMalloc(&dB, sz);
    cudaMalloc(&dC, sz);

    dim3 block(256), grid((N + block.x - 1) / block.x);
    processArray<<<grid, block>>>(dA, dB, dC);

    cudaFree(dA); cudaFree(dB); cudaFree(dC);
    return 0;
}