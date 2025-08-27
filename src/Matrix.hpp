#pragma once

#include <iostream>
#include <stdexcept> 
#include <vector> 
#include <random>
#include <thread>


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

    int get_size() const ;

    std::vector<double> get_data() const ;
    std::string get_string() ;
    int get(int row_index, int col_index) ;

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