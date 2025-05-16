#pragma once


#include <array>
#include <iostream>
#include <string>
#include <stdexcept> 
#include <vector>
#include <initializer_list>
#include <cmath>
#include <cstdlib>
#include <ranges>
#include <concepts> 
#include <iomanip>
#include <thread>
#include <future>
#include <type_traits>
#include <variant>
#include <any>
#include <execution>
#include <algorithm>
// #include <omp.h>
#include <chrono> 
#include <random>




// template<int ROW, int COL>
class Matrix {
    private:
    int rows;
    int columns;
    std::vector<double> data;
    
public:
    Matrix(int r, int c) : rows(r), columns(c), data(r*c, 0.0) {}
    Matrix(int item, int r, int c) : rows(r), columns(c), data(r*c, item) {}
    Matrix(const std::vector<double> input_data, int r, int c) : rows(r), columns(c), data(input_data) { if (input_data.size() != r*c) { throw std::invalid_argument("Size of array does not match dimension sizes."); } }
    Matrix(const double* input_data, int input_data_size, int r, int c) : rows(r), columns(c), data(input_data, input_data + input_data_size) { if (input_data_size != r*c) { throw std::invalid_argument("Size of array does not match dimension sizes."); } }
    // TODO std::array input
    ~Matrix() {}
    void print() { std::cout << get_string(); }

    // Operators
    Matrix operator()(int row_index) const { // Index operator, returns a new vector of the same data (still a matrix)
        if (rows <= row_index) {
            throw std::out_of_range("Row index out of range");
            exit(1);
        }
        if (0 > row_index) {
            throw std::out_of_range("Row index cannot be negative");
            exit(1);
        }
        std::vector<double> return_data = {};
        for (int i = 0; i < columns; i++) {
            return_data.push_back(data[i + row_index*columns]);
        }
        return Matrix(return_data, 1, columns);
    }
    double& operator()(int row_index, int col_index) { // Index operator, returns an entry in the matrix
        if (rows <= row_index) {
            throw std::out_of_range("Row index out of range");
            exit(1);
        }
        if (0 > row_index) {
            throw std::out_of_range("Row index cannot be negative");
            exit(1);
        }
        if (columns <= col_index) {
            throw std::out_of_range("Column index out of range");
            exit(1);
        }
        if (0 > col_index) {
            throw std::out_of_range("Column index cannot be negative");
            exit(1);
        }
        return data[(row_index * columns) + col_index];
    }
    const double& operator()(int row_index, int col_index) const { // Index operator, returns an entry in the matrix
        if (rows <= row_index) {
            throw std::out_of_range("Row index out of range");
            exit(1);
        }
        if (0 > row_index) {
            throw std::out_of_range("Row index cannot be negative");
            exit(1);
        }
        if (columns <= col_index) {
            throw std::out_of_range("Column index out of range");
            exit(1);
        }
        if (0 > col_index) {
            throw std::out_of_range("Column index cannot be negative");
            exit(1);
        }
        return data[(row_index * columns) + col_index];
    }
    Matrix operator+(const Matrix& other) {
        if (this->rows != other.rows) {
            throw std::invalid_argument("Row sizes must match to perform matrix addition.");
        }
        if (this->columns != other.columns) {
            throw std::invalid_argument("Column sizes must match to perform matrix addition.");
        }
        Matrix return_matrix = Matrix(data, rows, columns);
        // Matrix return_matrix = Matrix(this.data, this.size, this.rows, this.columns);
        for (int i = 0; i < this->get_size(); i++) {
            return_matrix.data[i] += other.data[i];
        }
        return return_matrix;
    }
    Matrix operator-(const Matrix& other) {
        if (this->rows != other.rows) {
            throw std::invalid_argument("Row sizes must match to perform matrix addition.");
        }
        if (this->columns != other.columns) {
            throw std::invalid_argument("Column sizes must match to perform matrix addition.");
        }
        Matrix return_matrix = Matrix(data, this->rows, this->columns);
        for (int i = 0; i < this->get_size(); i++) {
            return_matrix.data[i] -= other.data[i];
        }
        return return_matrix;
    }
    Matrix operator*(const Matrix& other) {
        if (this->rows != other.rows) {
            throw std::invalid_argument("Row sizes must match to perform matrix addition.");
        }
        if (this->columns != other.columns) {
            throw std::invalid_argument("Column sizes must match to perform matrix addition.");
        }
        Matrix return_matrix = Matrix(data, rows, columns);
        for (int i = 0; i < this->get_size(); i++) {
            return_matrix.data[i] *= other.data[i];
        }
        return return_matrix;
    }
    Matrix operator/(const Matrix& other) {
        if (this->rows != other.rows) {
            throw std::invalid_argument("Row sizes must match to perform matrix addition.");
        }
        if (this->columns != other.columns) {
            throw std::invalid_argument("Column sizes must match to perform matrix addition.");
        }
        Matrix return_matrix = Matrix(data, rows, columns);
        for (int i = 0; i < this->get_size(); i++) {
            return_matrix.data[i] /= other.data[i];
        }
        return return_matrix;
    }
    void operator=(const Matrix& other) {
        if (this == &other) return;
        for (int i = 0; i < other.get_size(); i++) {
            this->data[i] = other.data[i];
        }
        // this->size = other.size;
        this->rows = other.rows;
        this->columns = other.columns;
    }
    bool operator==(const Matrix& other) {
        if ((this->rows != other.rows) || (this->columns != other.columns)) {
            return false;
        }
        if (this->get_size() != other.get_size()) {
            return false;
        }
        for (int i = 0; i < other.get_size(); i++) {
            if (this->data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Matrix& other) {
        if ((this->rows != other.rows) || (this->columns != other.columns)) {
            return true;
        }
        if (this->get_size() != other.get_size()) {
            return true;
        }
        for (int i = 0; i < other.get_size(); i++) {
            if (this->data[i] != other.data[i]) {
                return true;
            }
        }
        return false;
    }

    // Gettrs
    int get_size() const { return data.size(); }

    std::vector<double> get_data() const { // a copy of the data
        std::vector<double> vec({});
        for (int i = 0; i < get_size(); i++) {
            vec.push_back(data[i]);
        }
        return vec;
    }
    std::string get_string() { // a copy of the data in a string format (originally arithmetic data)
        std::string str = "";
        for (int i = 0; i < get_size(); i++) {
            str += std::to_string(data[i]);
            str += " ";
            if ((((i+1) % columns) == 0) && (i != get_size()-1)) {
                str += '\n';
            }
        }
        return str;
    }
    int get(int row_index, int col_index) {
        if (rows <= row_index) {
            throw std::out_of_range("Row index out of range");
            return INT_MIN;
        }
        if (0 > row_index) {
            throw std::out_of_range("Row index cannot be negative");
            return INT_MIN;
        }
        if (columns <= col_index) {
            throw std::out_of_range("Column index out of range");
            return INT_MIN;
        }
        if (0 > col_index) {
            throw std::out_of_range("Column index cannot be negative");
            return INT_MIN;
        }
        return data[(row_index * columns) + col_index];
    }

    // The transpose operation
    Matrix Transpose() {
        Matrix B = Matrix(columns, rows);
        int B_index = 0;
        for (int i = 0; i < columns; i++) {
            for (int j = i; j < i+(columns*rows); j+=columns) {
                B.data[B_index] = data[j];
                B_index++;
            }
        }
        return B;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
    friend Matrix dot_serial(const Matrix& A, const Matrix& B);
    friend Matrix dot_static_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_dynamic_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_for_each(const Matrix& A, const Matrix& B);
    friend Matrix dot_coarse_grained(const Matrix& A, const Matrix& B);
    friend Matrix dot_fine_grained(const Matrix& A, const Matrix& B);
};

std::ostream& operator<<(std::ostream& os, Matrix& A) {
    os << A.get_string();
    return os;
}