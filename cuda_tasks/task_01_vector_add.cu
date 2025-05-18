#include <stdio.h>
#include <cuda_runtime.h>

#define SIZE (1 << 20)

__global__ void kernelA(float *a, float *b, float *c) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < SIZE) c[i] = a[i] + b[i];
}

template<typename T>
void safeFree(T*& ptr) {
    if (ptr) { cudaFree(ptr); ptr = nullptr; }
}

int main() {
    float *hA = new float[SIZE], *hB = new float[SIZE], *hC = new float[SIZE];
    float *dA, *dB, *dC;

    cudaMalloc(&dA, SIZE * sizeof(float));
    cudaMalloc(&dB, SIZE * sizeof(float));
    cudaMalloc(&dC, SIZE * sizeof(float));

    for (int i = 0; i < SIZE; ++i) {
        hA[i] = i;
        hB[i] = i * 2;
    }

    cudaMemcpy(dA, hA, SIZE * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dB, hB, SIZE * sizeof(float), cudaMemcpyHostToDevice);

    dim3 block(256), grid((SIZE + block.x - 1) / block.x);
    kernelA<<<grid, block>>>(dA, dB, dC);

    cudaMemcpy(hC, dC, SIZE * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Result: %f\n", hC[0]);

    delete[] hA; delete[] hB; delete[] hC;
    safeFree(dA); safeFree(dB); safeFree(dC);
    return 0;
}