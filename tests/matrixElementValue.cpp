#include <gtest/gtest.h>
#include "../include/matrix.hpp"


TEST(MatrixElementValue, defualtValue){
    Matrix<int, -1> matrix;
    ASSERT_EQ(matrix[0][0], -1);
}

TEST(MatrixElementValue, settedValue){
    Matrix<int, -1> matrix;
    matrix[0][0]=314;
    ASSERT_EQ(matrix[0][0], 314);
}

TEST(MatrixElementValue, equalAnotherElementOfSameMatrix) {
    Matrix<int, -1> matrixA;
    matrixA[0][0] = 10;
    Matrix<int, -1> matrixB;
    matrixB[1][1] = 10;
    ASSERT_EQ(matrixA[0][0], matrixB[1][1]);
}

TEST(MatrixElementValue, equalElementOfAnotherMatrix) {
    Matrix<int, -1> matrixA;
    matrixA[0][0] = 10;
    Matrix<int, -1> matrixB;
    matrixB[0][0] = 10;
    ASSERT_EQ(matrixA[0][0], matrixB[0][0]);
}

TEST(MatrixElementValue, equalElementOfAnotherMatrixWithAnotherDefaultValue) {
    Matrix<int, -1> matrixA;
    matrixA[0][0] = 120;
    Matrix<int, 10> matrixB;
    matrixB[0][0] = 120;
    ASSERT_EQ(matrixA[0][0], matrixB[0][0]);
}