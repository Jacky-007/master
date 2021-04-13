#pragma once
#include <iostream>
#include <utility>
#include <vector>

namespace GEO {
// Lab5. Transform2D below

template <int Rows, int Cols, typename T = float> struct Matrix {

  T data[Rows * Cols];

  constexpr static int rows() { return Rows; }
  constexpr static int cols() { return Cols; }
  void set_zero() { memset(data, 0, sizeof(T) * Rows * Cols); }
  constexpr static Matrix<Rows, Cols> zero() { return {0}; }
  constexpr static Matrix<Rows, Cols> one() {
    Matrix<Rows, Cols> one;
    one.set_zero();
    for (int i = 0; i < (Rows < Cols ? Rows : Cols); i++) {
      one(i, i) = T(1);
    }
    return one;
  }

  // Row major, index from (0, 0) -> (Rows, Cols), value access method
  T *operator[](int row) { return data + row * Cols; }
  T const *operator[](int row) const { return data + row * Cols; }
  T &operator()(int row, int col) { return data[row * Cols + col]; }
  T operator()(int row, int col) const { return data[row * Cols + col]; }
  T at(int row, int col) const { return data[row * Cols + col]; }

  // for vector like matrix
  T x() const { return data[0]; };
  T y() const { return data[Rows]; };
  T z() const { return data[Rows + Rows]; };

  template <int _Rows, int _Cols> T dot(const Matrix<_Rows, _Cols> &rhs) const {
    static_assert(Rows == _Rows && Cols == _Cols,
                  "Element shape must equal when use dot operation");
    T result = 0;
    for (int i = 0; i < Rows * Cols; i++) {
      result += data[i] * rhs[i];
    }
    return result;
  }

  template <int _Rows, int _Cols>
  Matrix<Rows, _Cols> operator*(const Matrix<_Rows, _Cols> &rhs) {
    static_assert(cols() == rhs.rows(),
                  "Matrix multiplication dimensions do not match");
    const Matrix<Rows, Cols> &A = *this;
    const Matrix<_Rows, _Cols> &B = rhs;
    Matrix<Rows, _Cols> C;
    C.set_zero();
	// @TODO: Implement Matrix multiplication here C = A * B
	for (int i = 0; i < rows(); i++) {
		for (int j = 0; j < rhs.cols(); j++) {
			for (int k = 0; k < cols(); k++) {
				C(i, j) += A(i, k) * B(k, j);
			}
		}
	
	}
  


    return C;
  }

  template <int Rows, int Cols>
  friend std::istream &operator>>(std::istream &in, Matrix<Rows, Cols> &);
  template <int Rows, int Cols>
  friend std::ostream &operator<<(std::ostream &out, Matrix<Rows, Cols> &);
};

template <int Rows, int Cols>
std::ostream &operator<<(std::ostream &out, Matrix<Rows, Cols> &m) {
  for (int i = 0; i < Rows; i++) {
    for (int j = 0; j < Cols; j++) {
      out << m(i, j) << " \n"[j + 1 == Cols && i + 1 != Rows];
    }
  }
  return out;
}
template <int Rows, int Cols>
std::istream &operator>>(std::istream &in, Matrix<Rows, Cols> &m) {
  for (int i = 0; i < Rows; i++) {
    for (int j = 0; j < Cols; j++) {
      in >> m(i, j);
    }
  }
  return in;
}

typedef Matrix<3, 3> Matrix3x3;
typedef Matrix<4, 4> Matrix4x4;
typedef Matrix<1, 3> Vector3;
typedef Matrix<1, 4> Vector4;
typedef Vector3 Point2D;
typedef Vector4 Point3D;

// @TODO: implement transform basic function in 2D here
Matrix3x3 rotate_matrix(float alpha);
Matrix3x3 translate_matrix(float dx, float dy);
Matrix3x3 scale_matrix(float sx, float sy);

// implement draw line with midpoint-bresenham algorithm
void draw_line(int src_x, int src_y, int dst_x, int dst_y,
               std::vector<std::pair<int, int>> &buffer);
void draw_symmetry_point(int xc, int yc, int x, int y,
                         std::vector<std::pair<int, int>> &buffer);
// implement draw circle with midpoint algorithm
void draw_circle_midpoint_bresenham(int xc, int yc, int r,
                                    std::vector<std::pair<int, int>> &buffer);
// implement draw ellipse with midpoint-bresenham algorithm
void draw_ellipse_midpoint_bresenham(int xc, int yc, int rx, int ry,
                                     std::vector<std::pair<int, int>> &buffer);
} // namespace GEO