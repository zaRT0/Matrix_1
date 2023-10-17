#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <exception>
#include "container.h"
using namespace std;
namespace matrix {
    template <typename T>
    class Matrix {
    private:
        int _rows;
        int _cols;
        Container<T>* _array;
    public:
        Matrix() : _rows(0), _cols(0), _array(nullptr) {}
        Matrix(int rows, int cols, const T& value);
        Matrix(int rows, int cols, T upper_bound, T lower_bound);
        Matrix (const Matrix<T>& matrix);
        int get_rows() const;
        int get_cols() const;
        Container<T>* get_array();
        T operator()(int index_one, int index_two) const;
        T& operator()(int index_one, int index_two);
        Matrix<T>& operator+(const Matrix<T>& arr);
        Matrix<T>& operator-(const Matrix<T>& arr);
        Matrix<T>& operator*(const Matrix<T>& arr);
        Matrix<T>& operator*=(const T& value);
        Matrix<T>& operator/=(const T& value);
        Matrix<T>& operator=(const Matrix<T>& other);
        T trace();
        ~Matrix();
    };

    template <typename T>
    Matrix<T>::Matrix(int rows, int cols, const T& value) {
        if (rows <= 0 || cols <= 0) {
            throw runtime_error("Invalid sizes of matrix");
        }
        this->_rows = rows;
        this->_cols = cols;
        this->_array = new Container<T>[_rows];
        for (int i = 0; i < _rows; ++i) {
            this->_array[i] = Container<T>(_cols);
        }
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                this->_array[i][j] = value;
            }
        }
    }

    template <typename T>
    Matrix<T>::Matrix(int rows, int cols, T upper_bound, T lower_bound) {
        if (rows <= 0 || cols <= 0) {
            throw runtime_error("Invalid sizes of matrix");
        }
        this->_rows = rows;
        this->_cols = cols;
        _array = new Container<T>[_rows];
        for (int i = 0; i < _rows; ++i) {
            _array[i] = Container<T>[_cols];
        }
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                _array[i][j] = rand() % upper_bound + lower_bound;
            }
        }
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix<T>& matrix) {
        this->_rows = matrix._rows;
        this->_cols = matrix._cols;
        this->_array = new Container<T>[_rows];
        for (int i = 0; i < _rows; ++i) {
            this->_array[i] = Container<T>(_cols);
            for (int j = 0; j < _cols; ++j) {
                this->_array[i][j] = matrix._array[i][j];
            }
        }
    }

    template <typename T>
    int Matrix<T>::get_rows() const {
        return _rows;
    }

    template <typename T>
    int Matrix<T>::get_cols() const {
        return _cols;
    }

    template<typename T>
    Container<T>* Matrix<T>::get_array() {
        return _array;
    }

    template <typename T>
    T Matrix<T>::operator()(int index_one, int index_two) const {
        if (index_one < 0 || index_two < 0 || index_one >= this->_rows || index_two >= this->_cols) {
            throw runtime_error("Index out of range");
        }
        return this->_array[index_one][index_two];
    }

    template <typename T>
    T& Matrix<T>::operator()(int index_one, int index_two) {
        if (index_one < 0 || index_two < 0 || index_one >= this->_rows || index_two >= this->_cols) {
            throw runtime_error("Index out of range");
        }
        return this->_array[index_one][index_two];
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator + (const Matrix<T>& arr) {
        if (this->_rows != arr.get_rows() || this->_cols != arr.get_cols()) {
            throw runtime_error("Size mismatch");
        }
        Matrix<T>* temp = new Matrix<T>(get_rows(), get_cols(), 0);
        for (int i = 0; i < this->_rows; ++i) {
            for (int j = 0; j < this->_cols; ++j) {
                temp->_array[i][j] = this->_array[i][j] + arr._array[i][j];
            }
        }
        return *temp;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator - (const Matrix<T>& arr) {
        if (this->_rows != arr.get_rows() || this->_cols != arr.get_cols()) {
            throw runtime_error("Size mismatch");
        }
        Matrix<T>* temp = new Matrix<T>(get_rows(), get_cols(), 0);
        for (int i = 0; i < this->_rows; ++i) {
            for (int j = 0; j < this->_cols; ++j) {
                temp->_array[i][j] = this->_array[i][j] - arr._array[i][j];
            }
        }
        return *temp;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator *(const Matrix<T>& arr) {
        if (this->_cols != arr.get_rows()) {
            throw runtime_error("Incompatible matrix sizes for multiplication");
        }
        Matrix<T>* temp = new Matrix<T>(get_rows(), arr.get_cols(), 0);
        for (int i = 0; i < this->_rows; ++i) {
            for (int j = 0; j < arr._cols; ++j) {
                for (int k = 0; k < this->_cols; ++k) {
                    temp->_array[i][j] += this->_array[i][k] * arr._array[k][j];
                }
            }
        }
        return *temp;
    }

    template <typename T>
    Matrix<T> operator*(const T& value, const Matrix<T> matrix) {
        Matrix<T> temp(matrix.get_rows(), matrix.get_cols(), T(0));
        for (int i = 0; i < temp.get_cols(); ++i) {
            for (int j = 0; j < temp.get_rows(); ++j) {
                temp(i, j) = value * matrix(i, j);
            }
        }
        return temp;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator*=(const T& value) {
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                _array[i][j] *= value;
            }
        }
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator /= (const T& value) {
        if (value == 0) {
            throw runtime_error("Invalid argument");
        }
        for (int i = 0; i < this->_rows; ++i) {
            for (int j = 0; j < this->_cols; ++j) {
                this->_array[i][j] /= value;
            }
        }
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
        if (this != &other) {
            if (this->_array) {
                delete[] this->_array;
            }
            this->_rows = other._rows;
            this->_cols = other._cols;
            this->_array = new Container<T>[this->_rows];
            for (int i = 0; i < this->_rows; ++i) {
                this->_array[i] = other._array[i];
            }
        }
        return *this;
    }

    template <typename T>
    T Matrix<T>::trace() {
        if (this->_rows != this->_cols) {
            throw runtime_error("Impossible to calculate the trace");
        }
        T temp = 0;
        for (int i = 0; i < this->_rows; ++i) {
            for (int j = i; j <= i; ++j) {
                temp += this->_array[i][j];
            }
        }
        return temp;
    }

    template<typename T>
    ostream& operator <<(ostream& stream, const Matrix<T>& matrix) {
        for (int i = 0; i < matrix.get_rows(); ++i) {
            for (int j = 0; j < matrix.get_cols(); ++j) {
                stream << matrix(i, j) << "\t";
            }
            stream << endl;
        }
        return stream;
    }

    template <typename T>
    Matrix<T>::~Matrix() {
        cout << "Вызвался деструктор!" << endl;
        delete[] this->_array;
    }

    template<typename T>
    bool checking_for_coplanarity(const Matrix<T>& arr1, const Matrix<T>& arr2, const Matrix<T>& arr3) {
        Matrix<T> matrix(3, 3, 0);
        for (int i = 0; i < 3; i++) {
            matrix(0, i) = arr1(0, i);
            matrix(1, i) = arr2(0, i);
            matrix(2, i) = arr3(0, i);
        }
        T determinant = (matrix(0, 0) * matrix(1, 1) * matrix(2, 2)) + (matrix(0, 1) * matrix(1, 2) * matrix(2, 0)) + (matrix(1, 0) * matrix(0, 2) * matrix(2, 1)) - (matrix(0, 2) * matrix(1, 1) * matrix(2, 0)) - (matrix(0, 1) * matrix(1, 0) * matrix(2, 2)) - (matrix(0, 0) * matrix(2, 1) * matrix(1, 2));
        if (determinant == T(0)) {
            return true;
        }
        else {
            return false;
        }
    }

    template <typename T>
    T determinant(const Matrix<T>& mat) {
        int rows = mat.get_rows();
        int cols = mat.get_cols();
        if (rows != cols) {
            throw std::runtime_error("Matrix is not square; determinant cannot be calculated.");
        }
        if (rows == 1) {
            return mat(0, 0);
        }
        if (rows == 2) {
            return mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0);
        }
        T det = 0;
        for (int col = 0; col < cols; col++) {
            Matrix<T> minor(rows - 1, cols - 1, T(0));
            for (int i = 1; i < rows; i++) {
                for (int j = 0, minor_col = 0; j < cols; j++) {
                    if (j == col) {
                        continue;
                    }
                    minor(i - 1, minor_col) = mat(i, j);
                    minor_col++;
                }
            }
            T minor_det = determinant(minor);
            if (col % 2 == 0) {
                det += mat(0, col) * minor_det;
            }
            else {
                det -= mat(0, col) * minor_det;
            }
        }
        return det;
    }

    template <typename T>
    Matrix<T> transpose(const Matrix<T>& mat) {
        int rows = mat.get_rows();
        int cols = mat.get_cols();
        Matrix<T> transposed(cols, rows, T(0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                transposed(j, i) = mat(i, j);
            }
        }
        return transposed;
    }

    template <typename T>
    Matrix<T> inverse(const Matrix<T>& mat) {
        int n = mat.get_rows();
        if (n != mat.get_cols()) {
            throw std::runtime_error("Matrix is not square; inverse matrix cannot be calculated.");
        }
        T det = determinant(mat);
        if (det == T(0)) {
            throw std::runtime_error("Matrix is singular; inverse matrix does not exist.");
        }
        Matrix<T> adjoint(n, n, T(0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Matrix<T> minor(n - 1, n - 1, T(0));
                for (int row = 0, m = 0; row < n; row++) {
                    if (row == i) continue;
                    for (int col = 0, k = 0; col < n; col++) {
                        if (col == j) continue;
                        minor(m, k) = mat(row, col);
                        k++;
                    }
                    m++;
                }
                T minor_det = determinant(minor);
                adjoint(i, j) = ((i + j) % 2 == 0) ? minor_det : -minor_det;
            }
        }
        Matrix<T> inverse_mat = transpose(adjoint) / det;
        return inverse_mat;
    }

    template <typename T>
    Matrix<T> operator / (const Matrix<T>& mat, const T& scalar) {
        int rows = mat.get_rows();
        int cols = mat.get_cols();
        Matrix<T> result(rows, cols, 0);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = mat(i, j) / scalar;
            }
        }
        return result;
    }
}