#pragma once

#include "Matrix.hpp"


// Normal Dot Product
Matrix dot_serial(const Matrix& A, const Matrix& B);

// parallel_for - #include <tbb/parallel_for.h> 
Matrix dot_static_parallel_for(const Matrix& A, const Matrix& B);

// parallel_for - #include <tbb/parallel_for.h> 
Matrix dot_dynamic_parallel_for(const Matrix& A, const Matrix& B);

Matrix dot_fine_grained(const Matrix& A, const Matrix& B);