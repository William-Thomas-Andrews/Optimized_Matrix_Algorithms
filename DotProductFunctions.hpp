// #ifndef DOT_PRODUCT_HPP
// #define DOT_PRODUCT_HPP

#pragma once

#include "Matrix.hpp"

// Normal Dot Product
// template <int ROW_A, int COL_A, int ROW_B, int COL_B>
// template <int ROW_B, int COL_B>
// Matrix<ROW_A, COL_B> dot_serial(const Matrix<ROW_A, COL_A>& A, const Matrix<ROW_B, COL_B>& B)
Matrix dot_serial(const Matrix& A, const Matrix& B) {
    int operations = 0;
    if (A.columns != B.rows)
    {
        throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
    }
    // Matrix<ROW_A, COL_B> result = Matrix<ROW_A, COL_B>();
    Matrix result = Matrix(A.rows, B.columns);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < B.columns; j++)
        {
            for (int k = 0; k < B.rows; k++)
            {
                result(i, j) += A(i, k) * B(k, j);
                operations++;
            }
        }
    }
    std::cout << "This serial algorithm had " << operations << " number of operations\n";
    return result;
}


// There is a race condition here that needs to be eliminated
// parallel_for - #include <tbb/parallel_for.h> 
// g++ -std=c++17 -I/opt/homebrew/Cellar/tbb/2022.0.0/include -L/opt/homebrew/Cellar/tbb/2022.0.0/lib -ltbb 0_static.cpp && ./a.out
// Matrix dot_parallel_for(const Matrix& A, const Matrix& B) {
//     std::atomic<int> operations = 0;
//     if (A.columns != B.rows)
//     {
//         throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
//     }
//     Matrix to_return = Matrix(A.rows, B.columns);
//     tbb::parallel_for(tbb::blocked_range<int>(0, A.rows),
//                 [&](tbb::blocked_range<int> r)
//     {
//         for (int i = r.begin(); i < r.end(); i++)
//         {
//             for (int j = 0; j < B.columns; j++)
//             {
//                 for (int k = 0; k < B.rows; k++)
//                 {
//                     to_return(i, j) += A(i, k) * B(k, j);
//                     operations++;
//                 }
//             }
//         }
//     });
//     std::cout << "This parallel_for algorithm had " << operations << " number of operations\n";
//     return to_return;
// }


// // c++ STL parallel for
// Matrix dotProduct_parallel_for_STL(const Matrix& A, const Matrix& B) {
//     std::atomic<int> operations = 0;
//     std::vector<int> rows(A.rows);
//     // std::vector<int> 
//     std::iota(rows.begin(), rows.end(), 0);
//     if (A.columns != B.rows) {
//         throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
//     }
//     Matrix to_return = Matrix(A.rows, B.columns); 
//     std::for_each(
//         std::execution::par_unseq,
//         rows.begin(), rows.end(), 
//         [&](int &n, Matrix to_return) {
//             for (int j = 0; j < B.columns; j++) {
//                 for (int k = 0; k < B.rows; k++) {
//                     to_return(n, j) += A(n, k) * B(k, j);
//                     operations++;
//                 }
//             }
//         }

//     );
//     return to_return;
// }

// Matrix dot_product_coarse_grained(const Matrix& A, const Matrix& B) {
//     if (A.columns != B.rows) {
//         throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
//     }
//     std::atomic<int> operations = 0;
//     Matrix to_return = Matrix(A.rows, B.columns);
//         // Random number generator
//     std::random_device rd;
//     std::mt19937 mt(rd());

//     // Create 4 distributions
//     std::uniform_int_distribution bin_1(1, 25);
//     std::uniform_int_distribution bin_2(26, 50);
//     std::uniform_int_distribution bin_3(51, 75);
//     std::uniform_int_distribution bin_4(76, 100);

//     // Calculate the number of elements per bin
//     int num_work_items = 1 << 18;
//     int n_bins = 4;
//     int elements_per_bin = num_work_items / n_bins;

//     // Create work items
//     std::vector<int> work_items;
//     std::generate_n(std::back_inserter(work_items), elements_per_bin,
//                     [&] {return bin_1(mt); });
//     std::generate_n(std::back_inserter(work_items), elements_per_bin,
//                     [&] {return bin_2(mt); });
//     std::generate_n(std::back_inserter(work_items), elements_per_bin,
//                     [&] {return bin_3(mt); });
//     std::generate_n(std::back_inserter(work_items), elements_per_bin,
//                     [&] {return bin_4(mt); });

//     std::cout << work_items.size() << std::endl;

//     // Create a lambda to process a range of items
//     auto work = [](std::span<int> items) {
//         for (const auto item : items) {
//             std::this_thread::sleep_for(std::chrono::microseconds(item));
//         }
//     };

//     // Calculate the number of items per thread (assume this equally divides)
//     int num_threads = 8;
//     int items_per_thread = num_work_items / num_threads;

//     // Spawn threads (join after)
//     std::vector<std::thread> threads;
//     for (int i = 0; i < num_threads; i++) {
//         int start = i * items_per_thread;
//         threads.emplace_back(work, std::span(work_items.begin() + start, items_per_thread));
//         // int* start_ptr = work_items.data() + i * items_per_thread;
//         // threads.emplace_back(work, std::span<int>(start_ptr, items_per_thread));
//     }

//     for (auto& t : threads) {
//         t.join();
//     }

//     // Now implement this into matrix multiplication
//     num_threads = 8;
//     num_work_items = 1000000;
//     items_per_thread = num_work_items / num_threads;

//     std::vector<std::thread> threads;
//     for (int i  = 0; i < num_threads; i++) {
//         int start = i * items_per_thread;
//         threads.emplace_back(function, std::span(std::begin(A.matrixArray) + start, items_per_thread));
//     }

//     return to_return;
// }

// #endif // DOT_PRODUCT_HPP