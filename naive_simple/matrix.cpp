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
