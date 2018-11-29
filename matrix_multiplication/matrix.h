#pragma once

#include <cstdint>
#include <vector>

struct Matrix {
    typedef uint32_t Value;
    size_t rowSize;
    size_t colSize;
    std::vector<std::vector<Value>> data;

    Matrix(size_t rowSize, size_t colSize);

    void fill();

    inline const std::vector<Value>& operator[](size_t index) const
    {
        return data[index];
    }

    inline std::vector<Value>& operator[](size_t index)
    {
        return data[index];
    }
};

void multiplySimple(const Matrix& matA, const Matrix& matB);
void multiplyTranspose(const Matrix& matA, const Matrix& matB);
