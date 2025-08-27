#pragma once

#include <tbb/parallel_for.h> 
#include <execution>
#include <algorithm>

#include "Matrix.hpp"


// Normal Dot Product
Matrix dot_serial(const Matrix& A, const Matrix& B);

// parallel_for - #include <tbb/parallel_for.h> 
// g++ -std=c++2b -I/opt/homebrew/Cellar/tbb/2022.0.0/include -L/opt/homebrew/Cellar/tbb/2022.0.0/lib -ltbb Main.cpp && ./a.out
Matrix dot_static_parallel_for(const Matrix& A, const Matrix& B);

// parallel_for - #include <tbb/parallel_for.h> 
// g++ -std=c++2b -I/opt/homebrew/Cellar/tbb/2022.0.0/include -L/opt/homebrew/Cellar/tbb/2022.0.0/lib -ltbb Main.cpp && ./a.out
Matrix dot_dynamic_parallel_for(const Matrix& A, const Matrix& B);

// // c++ STL parallel for_each
// Matrix dot_for_each(const Matrix& A, const Matrix& B) {
//     std::atomic<int> ops = 0;
//     std::vector<int> rows(A.rows);
//     // std::vector<int> 
//     std::iota(rows.begin(), rows.end(), 0);
//     if (A.columns != B.rows) {
//         throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
//     }
//     Matrix to_return = Matrix(A.rows, B.columns); 
//     std::for_each(std::execution::par_unseq, std::begin(rows), std::end(rows), [&](int &n, Matrix to_return) {
//             for (int j = 0; j < B.columns; j++) {
//                 for (int k = 0; k < B.rows; k++) {
//                     to_return(n, j) += A(n, k) * B(k, j);
//                     ops++;
//                 }
//             }
//         }
//     );
//     return to_return;
// }

Matrix dot_fine_grained(const Matrix& A, const Matrix& B);