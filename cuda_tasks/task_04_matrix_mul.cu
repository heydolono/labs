#include <cuda_runtime.h>

#define N 2048
#define BS 32

__global__ void matMul(float *A, float *B, float *C) {
    int row = blockIdx.y * BS + threadIdx.y;
    int col = blockIdx.x * BS + threadIdx.x;
    float sum = 0;
    if (row < N && col < N) {
        for (int k = 0; k < N; ++k)
            sum += A[row * N + k] * B[k * N + col];
        C[row * N + col] = sum;
    }
}

int main() {
    float *dA, *dB, *dC;
    size_t sz = N * N * sizeof(float);

    cudaMalloc(&dA, sz);
    cudaMalloc(&dB, sz);
    cudaMalloc(&dC, sz);

    dim3 block(BS, BS), grid(N / BS, N / BS);
    matMul<<<grid, block>>>(dA, dB, dC);

    cudaFree(dA); cudaFree(dB); cudaFree(dC);
    return 0;
}