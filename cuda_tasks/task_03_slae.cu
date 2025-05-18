#include <cuda_runtime.h>
#include <cmath>

#define N 10240
#define EPS 1e-6

__global__ void solveStep(double *A, double *F, double *X0, double *X1) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < N) {
        double sum = 0;
        for (int j = 0; j < N; ++j) sum += A[j + i * N] * X0[j];
        X1[i] = X0[i] + (F[i] - sum) / A[i + i * N];
    }
}

__global__ void diffVectors(double *X0, double *X1, double *delta) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < N) {
        delta[i] = fabs(X0[i] - X1[i]);
        X0[i] = X1[i];
    }
}

int main() {
    double *hA = new double[N * N], *hF = new double[N], *hX0 = new double[N], *hX1 = new double[N], *hDelta = new double[N];
    double *dA, *dF, *dX0, *dX1, *dDelta;

    size_t szA = N * N * sizeof(double);
    size_t szX = N * sizeof(double);

    cudaMalloc(&dA, szA);
    cudaMalloc(&dF, szX);
    cudaMalloc(&dX0, szX);
    cudaMalloc(&dX1, szX);
    cudaMalloc(&dDelta, szX);

    cudaMemcpy(dA, hA, szA, cudaMemcpyHostToDevice);
    cudaMemcpy(dF, hF, szX, cudaMemcpyHostToDevice);
    cudaMemcpy(dX0, hX0, szX, cudaMemcpyHostToDevice);

    int iter = 0;
    double err = 1.0;

    while (err > EPS) {
        solveStep<<<1, N>>>(dA, dF, dX0, dX1);
        diffVectors<<<1, N>>>(dX0, dX1, dDelta);
        cudaMemcpy(hDelta, dDelta, szX, cudaMemcpyDeviceToHost);
        err = 0;
        for (int i = 0; i < N; ++i) err += hDelta[i];
        err /= N;
        iter++;
    }

    cudaFree(dA); cudaFree(dF); cudaFree(dX0); cudaFree(dX1); cudaFree(dDelta);
    delete[] hA; delete[] hF; delete[] hX0; delete[] hX1; delete[] hDelta;
    return 0;
}