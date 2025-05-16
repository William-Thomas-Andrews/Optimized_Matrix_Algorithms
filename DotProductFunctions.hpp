#pragma once

#include "Matrix.hpp"
#include <tbb/parallel_for.h> 
#include <execution>
#include <algorithm>

// Normal Dot Product
Matrix dot_serial(const Matrix& A, const Matrix& B) {
    if (A.columns != B.rows) { throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows."); }
    // int ops = 0;
    Matrix result = Matrix(A.rows, B.columns);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < B.columns; j++) {
            for (int k = 0; k < B.rows; k++) {
                result(i, j) += A(i, k) * B(k, j);
                // ops++;
            }
        }
    }
    // std::cout << "This serial algorithm had " << ops << " number of operations\n";
    return result;
}


// parallel_for - #include <tbb/parallel_for.h> 
// g++ -std=c++2b -I/opt/homebrew/Cellar/tbb/2022.0.0/include -L/opt/homebrew/Cellar/tbb/2022.0.0/lib -ltbb Main.cpp && ./a.out
Matrix dot_static_parallel_for(const Matrix& A, const Matrix& B) {
    if (A.columns != B.rows) { throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows."); }
    // std::atomic<int> ops = 0;
    Matrix to_return = Matrix(A.rows, B.columns);
    tbb::parallel_for(tbb::blocked_range<int>(0, A.rows), [&](tbb::blocked_range<int> r) {
        for (int i = r.begin(); i < r.end(); i++) {
            for (int j = 0; j < B.columns; j++) {
                for (int k = 0; k < B.rows; k++) {
                    to_return(i, j) += A(i, k) * B(k, j);
                    // ops++;
                }
            }
        }
    });
    // std::cout << "This parallel_for algorithm had " << ops << " number of operations\n";
    return to_return;
}

// parallel_for - #include <tbb/parallel_for.h> 
// g++ -std=c++2b -I/opt/homebrew/Cellar/tbb/2022.0.0/include -L/opt/homebrew/Cellar/tbb/2022.0.0/lib -ltbb Main.cpp && ./a.out
Matrix dot_dynamic_parallel_for(const Matrix& A, const Matrix& B) {
    if (A.columns != B.rows) { throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows."); }
    // std::atomic<int> ops = 0;
    Matrix to_return = Matrix(A.rows, B.columns);
    tbb::parallel_for(tbb::blocked_range<int>(0, A.rows), [&](tbb::blocked_range<int> r) {
        for (int i = r.begin(); i < r.end(); i++) {
            for (int j = 0; j < B.columns; j++) {
                for (int k = 0; k < B.rows; k++) {
                    to_return(i, j) += A(i, k) * B(k, j);
                    // ops++;
                }
            }
        }
    }, tbb::static_partitioner());
    // std::cout << "This parallel_for algorithm had " << ops << " number of operations\n";
    return to_return;
}


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

Matrix dot_fine_grained(const Matrix& A, const Matrix& B) {
    if (A.columns != B.rows) { throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows."); }
    // std::atomic<int> ops = 0;
    Matrix to_return = Matrix(A.rows, B.columns);
    // TODO Dynamically allocate correct number of threads to use without messing up the algorithm
    int num_threads = 50;
    int items_per_thread = A.rows / num_threads;
    auto loop = [&](int thread_id) {
        for (int i = thread_id; i < thread_id+items_per_thread; i++) {
            for (int j  = 0; j < B.columns; j++) {
                for (int k = 0; k < B.rows; k++) {
                    to_return(i, j) += A(i, k) * B(k, j);
                    // ops++;
                }
            }
        }
    };
    std::vector<std::thread> threads;
    for (int i  = 0; i < num_threads; i++) {
        int start = i * items_per_thread;
        threads.emplace_back(loop, start);
    }

    std::cout << "Number of threads active: " << threads.size() << std::endl;
    
    for (auto& t : threads) {
        t.join();
    }
    // std::cout << std::thread::hardware_concurrency() << std::endl;

    // std::cout << "This fine_grained algorithm had " << ops << " number of operations\n";
    return to_return;
}

