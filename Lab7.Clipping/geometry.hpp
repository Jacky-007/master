#pragma once
#include <iostream>
#include <utility>
#include <vector>

namespace GEO {
// Lab5. Transform2D below

template <int Rows, int Cols, typename T = double> struct Matrix {

  T data[Rows * Cols];
  /* remove constexpr for older c++*/
  static int rows() { return Rows; }
  static int cols() { return Cols; }
  T *array() { return data; }
  void set_zero() { memset(data, 0, sizeof(T) * Rows * Cols); }
  static Matrix<Rows, Cols, T> zero() { return {0}; }
  static Matrix<Rows, Cols, T> identity() {
    Matrix<Rows, Cols, T> one;
    one.set_zero();
    for (int i = 0; i < (Rows < Cols ? Rows : Cols); i++) {
      one(i, i) = T(1);
    }
    return one;
  }

  // Define data conversion (not safe)
  template <typename _T> Matrix<Rows, Cols, _T> cast() {
    Matrix<Rows, Cols, _T> result;
    for (auto i = 0; i < Rows * Cols; ++i) {
      result.data[i] = static_cast<_T>(data[i]);
    }
    return result;
  }
  template <int _Rows, int _Cols, typename _T>
  operator Matrix<_Rows, _Cols, _T>() {
    Matrix<_Rows, _Cols, _T> result;
    memcpy(result.data, this->cast<_T>().data, sizeof(_T) * _Rows * _Cols);
    return result;
  }

  // Row major, index from (0, 0) -> (Rows, Cols), value access method
  T *operator[](int row) { return data + row * Cols; }
  T const *operator[](int row) const { return data + row * Cols; }
  T &operator()(int row, int col) { return data[row * Cols + col]; }
  T operator()(int row, int col) const { return data[row * Cols + col]; }
  T at(int row, int col) const { return data[row * Cols + col]; }

  // For vector like matrix
  T x() const { return data[0]; };
  T y() const { return data[Rows]; };
  T z() const { return data[Rows + Rows]; };
  T w() const { return data[Rows + Rows + Rows]; }

  T &x() { return data[0]; };
  T &y() { return data[Rows]; };
  T &z() { return data[Rows + Rows]; };
  T &w() { return data[Rows + Rows + Rows]; }

  template <int _Rows, int _Cols>
  Matrix<Rows, _Cols, T> operator*(const Matrix<_Rows, _Cols, T> &rhs) const {
    static_assert(Cols == _Rows, "Matrix multiplication dimension not match");
    const Matrix<Rows, Cols, T> &A = *this;
    const Matrix<_Rows, _Cols, T> &B = rhs;
    Matrix<Rows, _Cols, T> C;
    C.set_zero();

    // Implement Matrix multiplication here C = A * B
    for (int k = 0; k < B.rows(); k++) {
      for (int i = 0; i < A.rows(); i++) {
        for (int j = 0; j < B.cols(); j++) {
          C[i][j] += A[i][k] * B[k][j];
        }
      }
    }
    return C;
  }

  template <int _Rows, int _Cols>
  Matrix<Rows, Cols, T> operator-(const Matrix<_Rows, _Cols, T> &rhs) const {
    return _elemt_wise_op(
        rhs, [&](const T &lhs, const T &rhs) { return lhs - rhs; });
  }

  template <int _Rows, int _Cols>
  Matrix<Rows, Cols, T> operator+(const Matrix<_Rows, _Cols, T> &rhs) const {
    return _elemt_wise_op(
        rhs, [&](const T &lhs, const T &rhs) { return lhs + rhs; });
  }

  // For matrix input & output
  template <int Rows, int Cols, typename T>
  friend std::istream &operator>>(std::istream &in, Matrix<Rows, Cols, T> &);
  template <int Rows, int Cols, typename T>
  friend std::ostream &operator<<(std::ostream &out,
                                  Matrix<Rows, Cols, T> const &);

private:
  template <int _Rows, int _Cols, typename OP>
  Matrix<_Rows, _Cols, T> _elemt_wise_op(const Matrix<_Rows, _Cols, T> &rhs,
                                         OP operate) const {
    static_assert(Rows == _Rows && Cols == _Cols,
                  "Element shape must equal when use element wise operation");
    Matrix<_Rows, _Cols, T> result;
    for (int i = 0; i < Rows * Cols; i++) {
      result.data[i] = operate(data[i], rhs.data[i]);
    }
    return result;
  }
};

template <int Rows, int Cols, typename T>
std::ostream &operator<<(std::ostream &out, Matrix<Rows, Cols, T> const &m) {
  for (int i = 0; i < Rows; i++) {
    for (int j = 0; j < Cols; j++) {
      out << m(i, j) << " \n"[j + 1 == Cols && i + 1 != Rows];
    }
  }
  return out;
}
template <int Rows, int Cols, typename T>
std::istream &operator>>(std::istream &in, Matrix<Rows, Cols, T> &m) {
  for (int i = 0; i < Rows; i++) {
    for (int j = 0; j < Cols; j++) {
      in >> m(i, j);
    }
  }
  return in;
}

typedef Matrix<2, 2> Matrix2;
typedef Matrix<3, 3> Matrix3;
typedef Matrix<3, 3, int> Matrix3i;
typedef Matrix<4, 4> Matrix4;

typedef Matrix<1, 2> Vector2;
typedef Matrix<1, 2, int> Vector2i;
typedef Matrix<1, 3> Vector3;
typedef Matrix<1, 4> Vector4;

// implement transform basic function in 2D here
Matrix3 rotate_matrix(float alpha);
Matrix3 translate_matrix(float dx, float dy);
Matrix3 scale_matrix(float sx, float sy);

double cross_product(const Vector2 &u, const Vector2 &v);
bool is_turn_left(const Vector2 &u, const Vector2 &v, const Vector2 &w);

} // namespace GEO