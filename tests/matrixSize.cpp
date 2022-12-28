#include <gtest/gtest.h>
#include "../include/matrix.hpp"


TEST(matrixSize, zero) {
    Matrix<int, -1> matrix;
    ASSERT_EQ(matrix.size(), 0);
}

TEST(matrixSize, one) {
    Matrix<int, -1> matrix;
    matrix[0][0] = 1;
    ASSERT_EQ(matrix.size(), 1);
}

TEST(matrixSize, two) {
    Matrix<int, -1> matrix;
    matrix[0][0] = 1;
    std::cout << matrix[1][1] << std::endl;
    matrix[2][2] = 2;
    ASSERT_EQ(matrix.size(), 2);
}