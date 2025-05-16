#include "Matrix.hpp"
#include "DotProductFunctions.hpp"





int main() {
    const int size = 1000*1000;
    std::vector<double> vector1(size);
    std::vector<double> vector2(size);
    std::vector<double> vector3(size);
    std::vector<double> vector4(size);

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 10000.0);

    // Fill vectors with random values
    for (int i = 0; i < size; ++i) {
        vector1[i] = dis(gen);
        vector2[i] = dis(gen);
        vector3[i] = dis(gen);
        vector4[i] = dis(gen);
    }

    // Matrix<100, 100> matrix_A = Matrix<100, 100>(vector1);
    // Matrix<100, 100> matrix_B = Matrix<100, 100>(vector2);
    // Matrix<100, 100> matrix_C = Matrix<100, 100>(vector1);
    // Matrix<100, 100> matrix_D = Matrix<100, 100>(vector2);

    Matrix matrix_A = Matrix(vector1, 1000, 1000);
    Matrix matrix_B = Matrix(vector2, 1000, 1000);
    Matrix matrix_C = Matrix(vector1, 1000, 1000);
    Matrix matrix_D = Matrix(vector2, 1000, 1000);
    
    // std::vector<double> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    // Matrix matrix_A = Matrix(vec, 2, 4);
    // Matrix matrix_B = Matrix(vec, 4, 2);
    // std::cout << matrix_A << std::endl;

    const int n = 100000; 
  
    auto start_time 
        = std::chrono::high_resolution_clock::now(); 
  
    Matrix result_serial = dot_serial(matrix_A, matrix_B); 
  
    auto end_time 
        = std::chrono::high_resolution_clock::now(); 
  
    std::chrono::duration<double> serial_duration 
        = end_time - start_time; 

    // std::cout << "hey" << std::endl;
  
    // start_time = std::chrono::high_resolution_clock::now(); 

    // Matrix result_parallel = dot_product_coarse_grained(matrix_C, matrix_D); 
    // end_time = std::chrono::high_resolution_clock::now(); 
    // std::chrono::duration<double> parallel_duration 
    //     = end_time - start_time; 
  
    // std::cout << "Serial result: " << result_serial 
    //           << std::endl; 
    // std::cout << "Parallel result: " << result_parallel 
    //           << std::endl; 
    std::cout << "Serial duration: "
              << serial_duration.count() << " seconds"
              << std::endl; 
    // std::cout << "Parallel duration: "
            //   << parallel_duration.count() << " seconds"
            //   << std::endl; 
    // std::cout << "Speedup: "
            //   << serial_duration.count() 
                    //  / parallel_duration.count()
            //   << " times the parallel speed." 
            //   << std::endl; 
    
    // std::cout << matrix_A(1, 0) << std::endl;

    return 0; 
}