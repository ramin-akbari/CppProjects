#include "Matrix.h"
#include <omp.h>
#include <stdexcept>

Matrix::Matrix(int row, int col, bool rand_fill) : mRow(row), mCol(col) {
  mContainer = std::make_unique<double[]>(mRow * mCol);
  mSkipRow = mCol;
  mSkipCol = 1;
  if (rand_fill)
    fill();
}

void Matrix::transpose(bool contiguous) {

  if (contiguous) {
    auto temp = std::make_unique<double[]>(mRow * mCol);
#pragma omp parallel for
    for (int i = 0; i < mRow; i++) {
      for (int j = 0; j < mCol; j++) {
        temp[j * mRow + i] = mContainer[i * mCol + j];
      }
    }
    mContainer = std::move(temp);
    mSkipRow = mRow;
  } else {
    std::swap(mSkipRow, mSkipCol);
  }
  std::swap(mRow, mCol);
}

Matrix::Matrix(const Matrix &other) {
  mRow = other.get_rows();
  mCol = other.get_cols();
  mContainer = std::make_unique<double[]>(mRow * mCol);
  for (int i = 0; i < mRow; i++) {
    for (int j = 0; j < mCol; j++) {
      mContainer[i * mCol + j] = other(i, j);
    }
  }
}

Matrix Matrix::operator()(const int &i) {
  auto out = Matrix(1, mCol);
  for (int k = 0; k < mCol; k++) {
    out(0, k) = mContainer[i * mCol + k];
  }
  return out;
}

Matrix Matrix::operator+(const Matrix &other) {
  if (check_size(other)) {
    Matrix out = Matrix(mRow, mCol);
    for (int i = 0; i < mRow; i++) {
      for (int j = 0; j < mCol; j++) {
        out(i, j) = (*this)(i, j) + other(i, j);
      }
    }
    return out;
  }
  throw std::runtime_error("dimension mismatch for matrix summation ");
}

Matrix Matrix::multiply(const Matrix &other) {
  Matrix out = Matrix(mRow, other.get_cols());
#pragma omp parallel for
  for (int i = 0; i < mRow; i++) {
    for (int k = 0; k < mCol; k++) {
      for (int j = 0; j < other.get_cols(); j++) {
        out(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  return out;
}

Matrix Matrix::operator*(const Matrix &other) {
  if (other.get_rows() != mCol)
    throw std::runtime_error("dimension mismatch for matrix multiplication");

  return multiply(other);
}

std::ostream &Matrix::operator>>(std::ostream &stream) {
  stream << std::fixed;
  stream << std::left;
  for (int i = 0; i < mRow; i++) {
    for (int j = 0; j < mCol - 1; j++) {
      stream << std::setprecision(5);
      stream << std::setw(10);
      stream << (*this)(i, j) << "\t";
    }
    stream << (*this)(i, mCol - 1) << "\n";
  }
  return stream;
}

void Matrix::fill(bool gauss) {
  std::unique_ptr<Random> gen;
  if (gauss) {
    gen = std::make_unique<Gaussian>();
  } else {
    gen = std::make_unique<Uniform>();
  }
  for (int i = 0; i < mRow; i++) {
    for (int j = 0; j < mCol; j++) {
      mContainer[i * mCol + j] = gen->Rand();
    }
  }
}
