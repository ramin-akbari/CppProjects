#include "Random.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>

class Matrix {
public:
  Matrix() = delete;
  Matrix(int row, int col, bool rand_fill = false);
  Matrix(const Matrix &other);

  double &operator()(int i, int j) {
    return mContainer[i * mSkipRow + j * mSkipCol];
  }
  const double &operator()(int i, int j) const {
    return mContainer[i * mSkipRow + j * mSkipCol];
  }

  Matrix operator()(const int &i);
  Matrix operator+(const Matrix &other);
  Matrix operator*(const Matrix &other);

  const int &get_rows() const { return mRow; }
  const int &get_cols() const { return mCol; }
  void transpose(bool contiguous = true);

  std::ostream &operator>>(std::ostream &stream);

private:
  int mCol = 1;
  int mRow = 1;
  int mSkipRow = 1;
  int mSkipCol = 1;
  bool mIsTransposed = false; // not used yet
  std::unique_ptr<double[]> mContainer = nullptr;
  void fill(bool gauss = false);
  bool check_size(const Matrix &other) {
    return (mRow == other.get_rows()) && (mCol == other.get_cols());
  }
  Matrix multiply(const Matrix &other);
  Matrix tr_multiply(const Matrix &other);
};
