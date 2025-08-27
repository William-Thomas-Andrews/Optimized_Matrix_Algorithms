#include <tbb/parallel_for.h> 

#include "DotProduct.hpp"


// Normal Dot Product
Matrix dot_serial(const Matrix& A, const Matrix& B) {
    if (A.columns != B.rows) { throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows."); }
    // int ops = 0;
    Matrix result = Matrix(A.rows, B.columns);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < B.columns; j++) {
            double sum = 0.0;
            for (int k = 0; k < B.rows; k++) {
                result(i, j) += A(i, k) * B(k, j);
                // ops++;
                sum += A(i, k) * B(k, j);
            }
            result(i, j) = sum;
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
                double sum = 0.0;
                for (int k = 0; k < B.rows; k++) {
                    // to_return(i, j) += A(i, k) * B(k, j);
                    // ops++;
                    sum += A(i, k) * B(k, j);
                }
                to_return(i, j) = sum;
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
                double sum = 0.0;
                for (int k = 0; k < B.rows; k++) {
                    // to_return(i, j) += A(i, k) * B(k, j);
                    sum += A(i, k) * B(k, j);
                    // ops++;
                }
                to_return(i, j) = sum;
            }
        }
    }, tbb::static_partitioner());
    // std::cout << "This parallel_for algorithm had " << ops << " number of operations\n";
    return to_return;
}


Matrix dot_fine_grained(const Matrix& A, const Matrix& B) {
    if (A.columns != B.rows) { throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows."); }
    // std::atomic<int> ops = 0;
    Matrix to_return = Matrix(A.rows, B.columns);
    int num_threads = std::min((unsigned) A.rows, std::thread::hardware_concurrency());
    int items_per_thread = A.rows / (num_threads-1);
    auto main_loop = [&](int thread_id) {
        for (int i = thread_id; i < thread_id+items_per_thread; i++) {
            for (int j = 0; j < B.columns; j++) {
                double sum = 0.0;
                for (int k = 0; k < B.rows; k++) {
                    // to_return(i, j) += A(i, k) * B(k, j);
                    sum += A(i, k) * B(k, j);
                    // ops++;
                }
                to_return(i, j) = sum;
            }
        }
    };
    auto extended_loop = [&](int thread_id) {
        int extended_index = A.rows % (num_threads-1);
        // if (extended_index == 0) { extended_index = 8; }
        for (int i = thread_id; i < thread_id+extended_index; i++) {
            for (int j = 0; j < B.columns; j++) {
                for (int k = 0; k < B.rows; k++) {
                    to_return(i, j) += A(i, k) * B(k, j);
                    // ops++;
                }
            }
        }
    };
    std::vector<std::thread> threads;
    for (int i  = 0; i < num_threads-1; i++) {
        int start = i * items_per_thread;
        threads.emplace_back(main_loop, start);
    }
    threads.emplace_back(extended_loop, (num_threads-1)*items_per_thread);
    // std::cout << "Number of threads active: " << threads.size() << std::endl;
    for (auto& t : threads) { t.join(); }
    // std::cout << "This fine_grained algorithm had " << ops << " number of operations\n";
    return to_return;
}

