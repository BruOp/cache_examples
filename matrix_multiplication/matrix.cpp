#include "matrix.h"

Matrix::Matrix(size_t rowSize, size_t colSize)
    : rowSize(rowSize)
    , colSize(colSize)
    , data()
{
    data.resize(rowSize, std::vector<Value>(colSize));
}

void Matrix::fill()
{
    for (size_t i = 0; i < rowSize; i++) {
        for (size_t j = 0; j < colSize; j++) {
            data[i][j] = static_cast<Value>(i * j);
        }
    }
}

void multiplySimple(const Matrix& matA, const Matrix& matB)
{
    // Assert matA * matB is actually possible :)
    size_t N = matA.rowSize;
    size_t M = matA.colSize;
    size_t P = matB.colSize;

    Matrix matC(N, P);
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < P; j++) {
            matC[i][j] = 0;
            for (size_t k = 0; k < M; k++) {
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

void multiplyTranspose(const Matrix& matA, const Matrix& matB)
{
    // Assert matA * matB is actually possible :)
    size_t N = matA.rowSize;
    size_t M = matA.colSize;
    size_t P = matB.colSize;

    Matrix matT{ matB.colSize, matB.rowSize };
    for (size_t i = 0; i < matT.rowSize; i++) {
        for (size_t j = 0; j < matT.colSize; j++) {
            matT[i][j] = matB[j][i];
        }
    }

    Matrix matC(N, P);
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < P; j++) {
            matC[i][j] = 0;
            for (size_t k = 0; k < M; k++) {
                matC[i][j] += matA[i][k] * matT[j][k];
            }
        }
    }
}
