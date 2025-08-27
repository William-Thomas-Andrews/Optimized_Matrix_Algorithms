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
    Matrix(int r, int c);
    Matrix(double item, int r, int c);
    Matrix(const std::vector<double> input_data, int r, int c);
    Matrix(const double* input_data, int input_data_size, int r, int c);
    ~Matrix();
    void print();

    // Operators
    Matrix operator()(int row_index) const ;
    double& operator()(int row_index, int col_index);
    const double& operator()(int row_index, int col_index) const ;
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix operator/(const Matrix& other);
    void operator=(const Matrix& other);
    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);

    // Gettrs
    int get_size() const ;

    std::vector<double> get_data() const ;
    std::string get_string() ;
    int get(int row_index, int col_index) ;

    // The transpose operation
    Matrix Transpose();

    friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
    friend Matrix dot_serial(const Matrix& A, const Matrix& B);
    friend Matrix dot_static_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_dynamic_parallel_for(const Matrix& A, const Matrix& B);
    friend Matrix dot_for_each(const Matrix& A, const Matrix& B);
    friend Matrix dot_coarse_grained(const Matrix& A, const Matrix& B);
    friend Matrix dot_fine_grained(const Matrix& A, const Matrix& B);
};

std::ostream& operator<<(std::ostream& os, Matrix& A);