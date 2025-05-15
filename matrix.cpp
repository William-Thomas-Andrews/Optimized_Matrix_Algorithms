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
#include <span>
#include <execution>
#include <algorithm>
#include <chrono> 
#include <climits>
// #include <omp.h>
#include <tbb/parallel_for.h>
#include<tbb/tbb.h>






class Matrix
{
    private:
        double* matrixArray;
        int size = 0;
        int rows = 0;
        int columns = 0;
        
    public:
        Matrix(int num_rows, int num_columns) : rows(num_rows), columns(num_columns), size(num_rows*num_columns)
        {
            
            matrixArray = new double[size];
            for (int i = 0; i < size; i++)
            {
                matrixArray[i] = 0;
            }
        }
        Matrix(int item, int num_rows, int num_columns) : rows(num_rows), columns(num_columns), size(num_rows*num_columns)
        {
            matrixArray = new double[size];
            for (int i = 0; i < size; i++)
            {
                matrixArray[i] = item;
            }
        }
        Matrix(const std::vector<double>& data, int num_rows, int num_columns) : rows(num_rows), columns(num_columns), size(num_rows*num_columns)
        {
            if (data.size() != size)
            {
                throw std::invalid_argument("Size of array does not match dimension sizes.");
            }
            matrixArray = new double[size];
            for (int i = 0; i < size; i++)
            {
                matrixArray[i] = data[i];
            }
        }
        Matrix(const double* data, int data_size, int num_rows, int num_columns) : rows(num_rows), columns(num_columns), size(num_rows*num_columns)
        {
            if (data_size != size)
            {
                throw std::invalid_argument("Size of array does not match dimension sizes.");
            }
            matrixArray = new double[size];
            for (int i = 0; i < size; i++)
            {
                matrixArray[i] = data[i];
            }
        }

        ~Matrix()
        {
            delete[] matrixArray;
        }

        void print()
        {
            std::cout << this->getString();
        }
        // Operators
        const Matrix operator+(const Matrix& other)
        {
            if (this->rows != other.rows)
            {
                throw std::invalid_argument("Row sizes must match to perform matrix addition.");
            }
            if (this->columns != other.columns)
            {
                throw std::invalid_argument("Column sizes must match to perform matrix addition.");
            }
            Matrix return_matrix = Matrix(this->matrixArray, this->size, this->rows, this->columns);
            for (int i = 0; i < this->size; i++)
            {
                return_matrix.matrixArray[i] += other.matrixArray[i];
            }
            return return_matrix;
        }
        Matrix operator-(const Matrix& other)
        {
            if (this->rows != other.rows)
            {
                throw std::invalid_argument("Row sizes must match to perform matrix addition.");
            }
            if (this->columns != other.columns)
            {
                throw std::invalid_argument("Column sizes must match to perform matrix addition.");
            }
            Matrix return_matrix = Matrix(this->matrixArray, this->size, this->rows, this->columns);
            for (int i = 0; i < this->size; i++)
            {
                return_matrix.matrixArray[i] -= other.matrixArray[i];
            }
            return return_matrix;
        }
        Matrix operator*(const Matrix& other)
        {
            if (this->rows != other.rows)
            {
                throw std::invalid_argument("Row sizes must match to perform matrix addition.");
            }
            if (this->columns != other.columns)
            {
                throw std::invalid_argument("Column sizes must match to perform matrix addition.");
            }
            Matrix return_matrix = Matrix(this->matrixArray, this->size, this->rows, this->columns);
            for (int i = 0; i < this->size; i++)
            {
                return_matrix.matrixArray[i] *= other.matrixArray[i];
            }
            return return_matrix;
        }
        Matrix operator/(const Matrix& other) 
        {
            if (this->rows != other.rows)
            {
                throw std::invalid_argument("Row sizes must match to perform matrix addition.");
            }
            if (this->columns != other.columns)
            {
                throw std::invalid_argument("Column sizes must match to perform matrix addition.");
            }
            Matrix return_matrix = Matrix(this->matrixArray, this->size, this->rows, this->columns);
            for (int i = 0; i < this->size; i++)
            {
                return_matrix.matrixArray[i] /= other.matrixArray[i];
            }
            return return_matrix;
        }
        void operator=(const Matrix& other) 
        {
            if (this == &other) return;
            for (int i = 0; i < other.size; i++)
            {
                this->matrixArray[i] = other.matrixArray[i];
            }
            this->size = other.size;
            this->rows = other.rows;
            this->columns = other.columns;
        }
        bool operator==(const Matrix& other)
        {
            if ((this->rows != other.rows) || (this->columns != other.columns))
            {
                return false;
            }
            if (this->size != other.size)
            {
                return false;
            }
            for (int i = 0; i < other.size; i++)
            {
                if (this->matrixArray[i] != other.matrixArray[i])
                {
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const Matrix& other)
        {
            if ((this->rows != other.rows) || (this->columns != other.columns))
            {
                return true;
            }
            if (this->size != other.size)
            {
                return true;
            }
            for (int i = 0; i < other.size; i++)
            {
                if (this->matrixArray[i] != other.matrixArray[i])
                {
                    return true;
                }
            }
            return false;
        }
        std::vector<double> getData() const // a copy of the data
        {
            std::vector<double> vec({});
            for (int i = 0; i < size; i++)
            {
                vec.push_back(matrixArray[i]);
            }
            return vec;
        }
        std::string getString() // a copy of the data in a string format (originally arithmetic data)
        {
            std::string str = "";
            for (int i = 0; i < size; i++)
            {
                str += std::to_string(matrixArray[i]);
                str += " ";
                if ((((i+1) % columns) == 0) && (i != size-1))
                {
                    str += '\n';
                }
            }
            return str;
        }
        int get(int rowIndex, int colIndex)
        {
            if (rows <= rowIndex)
            {
                throw std::out_of_range("Row index out of range");
                return INT_MIN;
            }
            if (0 > rowIndex)
            {
                throw std::out_of_range("Row index cannot be negative");
                return INT_MIN;
            }
            if (columns <= colIndex)
            {
                throw std::out_of_range("Column index out of range");
                return INT_MIN;
            }
            if (0 > colIndex)
            {
                throw std::out_of_range("Column index cannot be negative");
                return INT_MIN;
            }
            return matrixArray[(rowIndex * columns) + colIndex];
        }
        Matrix Transpose()
        {
            Matrix B = Matrix(columns, rows);
            int bIndex = 0;
            for (int i = 0; i < columns; i++)
            {
                for (int j = i; j < i+(columns*rows); j+=columns)
                {
                    B.matrixArray[bIndex] = matrixArray[j];
                    bIndex++;
                }
            }
            return B;
        }
        Matrix operator()(int rowIndex) const
        {
            if (rows <= rowIndex)
            {
                throw std::out_of_range("Row index out of range");
                exit(1);
            }
            if (0 > rowIndex)
            {
                throw std::out_of_range("Row index cannot be negative");
                exit(1);
            }
            std::vector<double> returnData = {};
            for (int i = 0; i < columns; i++)
            {
                returnData.push_back(matrixArray[i + rowIndex*columns]);
            }
            return Matrix(returnData, 1, columns);
        }
        double& operator()(int rowIndex, int colIndex) const
        {
            if (rows <= rowIndex)
            {
                throw std::out_of_range("Row index out of range");
                exit(1);
            }
            if (0 > rowIndex)
            {
                throw std::out_of_range("Row index cannot be negative");
                exit(1);
            }
            if (columns <= colIndex)
            {
                throw std::out_of_range("Column index out of range");
                exit(1);
            }
            if (0 > colIndex)
            {
                throw std::out_of_range("Column index cannot be negative");
                exit(1);
            }
            return matrixArray[(rowIndex * columns) + colIndex];
        }
        // std::ostream& printToStream(std::ostream& os) const
        // {
        //     // os << dataToStream(matrixArray, os);
        //     os << 
        //     return os;
        // }
        template <typename T>
        friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
        friend Matrix dotProduct_serial(const Matrix& A, const Matrix& B);
        friend Matrix dotProduct_parallel_for(const Matrix& A, const Matrix& B);
        // friend Matrix dotProduct_parallel_for_STL(const Matrix& A, const Matrix& B);
        friend Matrix dot_product_coarse_grained(const Matrix& A, const Matrix& B);
        friend Matrix dotProduct_fine_grained(const Matrix& A, const Matrix& B);
        friend Matrix transpose(const Matrix& A);
};

std::ostream& operator<<(std::ostream& os, Matrix& A)
{
    os << A.getString();
    return os;
}


// use open mp and/or cache optimization and test speed with different versions of the same function
// Normal Dot Product
Matrix dotProduct_serial(const Matrix& A, const Matrix& B)
{
    int operations = 0;
    if (A.columns != B.rows)
    {
        throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
    }
    Matrix toReturn = Matrix(A.rows, B.columns);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < B.columns; j++)
        {
            for (int k = 0; k < B.rows; k++)
            {
                toReturn(i, j) += A(i, k) * B(k, j);
                operations++;
            }
        }
    }
    std::cout << "This serial algorithm had " << operations << " number of operations\n";
    return toReturn;
}


// There is a race condition here that needs to be eliminated
// parallel_for - #include <tbb/parallel_for.h> 
// g++ -std=c++17 -I/opt/homebrew/Cellar/tbb/2022.0.0/include -L/opt/homebrew/Cellar/tbb/2022.0.0/lib -ltbb 0_static.cpp && ./a.out
Matrix dotProduct_parallel_for(const Matrix& A, const Matrix& B)
{
    std::atomic<int> operations = 0;
    if (A.columns != B.rows)
    {
        throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
    }
    Matrix toReturn = Matrix(A.rows, B.columns);
    tbb::parallel_for(tbb::blocked_range<int>(0, A.rows),
                [&](tbb::blocked_range<int> r)
    {
        for (int i = r.begin(); i < r.end(); i++)
        {
            for (int j = 0; j < B.columns; j++)
            {
                for (int k = 0; k < B.rows; k++)
                {
                    toReturn(i, j) += A(i, k) * B(k, j);
                    operations++;
                }
            }
        }
    });
    std::cout << "This parallel_for algorithm had " << operations << " number of operations\n";
    return toReturn;
}


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

Matrix dot_product_coarse_grained(const Matrix& A, const Matrix& B) {
    if (A.columns != B.rows) {
        throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
    }
    std::atomic<int> operations = 0;
    Matrix to_return = Matrix(A.rows, B.columns);
        // Random number generator
    std::random_device rd;
    std::mt19937 mt(rd());

    // Create 4 distributions
    std::uniform_int_distribution bin_1(1, 25);
    std::uniform_int_distribution bin_2(26, 50);
    std::uniform_int_distribution bin_3(51, 75);
    std::uniform_int_distribution bin_4(76, 100);

    // Calculate the number of elements per bin
    int num_work_items = 1 << 18;
    int n_bins = 4;
    int elements_per_bin = num_work_items / n_bins;

    // Create work items
    std::vector<int> work_items;
    std::generate_n(std::back_inserter(work_items), elements_per_bin,
                    [&] {return bin_1(mt); });
    std::generate_n(std::back_inserter(work_items), elements_per_bin,
                    [&] {return bin_2(mt); });
    std::generate_n(std::back_inserter(work_items), elements_per_bin,
                    [&] {return bin_3(mt); });
    std::generate_n(std::back_inserter(work_items), elements_per_bin,
                    [&] {return bin_4(mt); });

    // Create a lambda to process a range of items
    auto work = [](std::span<int> items) {
        for (const auto item : items) {
            std::this_thread::sleep_for(std::chrono::microseconds(item));
        }
    };

    // Calculate the number of items per thread (assume this equally divides)
    int num_threads = 8;
    int items_per_thread = num_work_items / num_threads;

    // Spawn threads (join in destructor of jthread)
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++) {
        int start = i * items_per_thread;
        threads.emplace_back(work, std::span(work_items.begin() + start, items_per_thread));
        // int* start_ptr = work_items.data() + i * items_per_thread;
        // threads.emplace_back(work, std::span<int>(start_ptr, items_per_thread));
    }

    for (auto& t : threads) {
        t.join();
    }

    // Now implement this into matrix multiplication

    return to_return;
}

// Matrix dotProduct_fine_grained(const Matrix& A, const Matrix& B)
// {
//     if (A.columns != B.rows)
//     {
//         throw std::invalid_argument("Matrix 1 colums do not match Matrix 2 rows.");
//     }
//     Matrix toReturn = Matrix(A.rows, B.columns);

//     // Calculate the number of elements per bin
//     int num_work_items = toReturn.size; // 10000 - get rid of
//     // int n_bins = 10; // 10
//     // int elements_per_bin = num_work_items / n_bins; // 10000 / 10 = 1000

//     // Create work items
//     // std::vector<int> work_items;
//     // std::generate_n(std::back_inserter(work_items), elements_per_bin,
//     //                 [&] {return bin_1(mt); });
//     // std::generate_n(std::back_inserter(work_items), elements_per_bin,
//     //                 [&] {return bin_2(mt); });
//     // std::generate_n(std::back_inserter(work_items), elements_per_bin,
//     //                 [&] {return bin_3(mt); });
//     // std::generate_n(std::back_inserter(work_items), elements_per_bin,
//     //                 [&] {return bin_4(mt); });

//     // Number of threads to spawn
//     int num_threads = 10; // 10 - customize

//     // Create a lambda to process a range of items
//     auto work = [&](int thread_id, int iteration) {

//         for (int i = thread_id * num_threads; i < num_threads + (thread_id * num_threads); i++)
//         {
//             // std::cout << i << std::endl;
//             for (int j = thread_id * iteration; j < num_threads + (thread_id * iteration); j++)
//             {
//                 for (int k = thread_id * num_threads; k < num_threads + (thread_id * num_threads); k++)
//                 {
//                     std::cout << k << std::endl;
//                     toReturn(i, j) += A(i, k) * B(k, j);
//                 }
//             }
//         }

//         // for (int i = thread_id; i < num_work_items; i += num_threads) {
//         //     // std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(toReturn.matrixArray[i])));
//         //     // for (int i = r.begin(); i < r.end(); i++)
//         //     // {
//         //     //     for (int j = 0; j < B.columns; j++)
//         //     //     {
//         //     //         for (int k = 0; k < B.rows; k++)
//         //     //         {
//         //     //             toReturn(i, j) += A(i, k) * B(k, j);
//         //     //         }
//         //     //     }
//         //     // }
//         // }
//     };

//     // just write it out on paper

//     // Spawn threads (join in destructor of jthread)
//     std::vector<std::jthread> threads;
//     for (int i = 0; i < num_threads; i++) {
//         for (int j = 0; j < num_threads; j++) {
//             threads.emplace_back(work, i, j);
//         }
//     }

//     // tbb::parallel_for(tbb::blocked_range<int>(0, A.rows),
//     //             [&](tbb::blocked_range<int> r)
//     // {
//     //     // for (int i = r.begin(); i < r.end(); i++)
//     //     // {
//     //     //     for (int j = 0; j < B.columns; j++)
//     //     //     {
//     //     //         for (int k = 0; k < B.rows; k++)
//     //     //         {
//     //     //             toReturn(i, j) += A(i, k) * B(k, j);
//     //     //         }
//     //     //     }
//     //     // }
//     // });

//     return toReturn;
// }
