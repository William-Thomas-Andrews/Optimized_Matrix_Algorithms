#include "Matrix.hpp"
#include "DotProductFunctions.hpp"
#include <iomanip>






int main() {
    const int size = 500*500;
    std::vector<double> vector1(749*499);
    std::vector<double> vector2(499*849);
    std::vector<double> vector3(749*499);
    std::vector<double> vector4(499*849);

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

    Matrix matrix_A = Matrix(vector1, 749, 499);
    Matrix matrix_B = Matrix(vector2, 499, 849);
    Matrix matrix_C = Matrix(vector1, 749, 499);
    Matrix matrix_D = Matrix(vector2, 499, 849);
    
    // std::vector<double> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    // Matrix matrix_A = Matrix(vec, 2, 4);
    // Matrix matrix_B = Matrix(vec, 4, 2);
    // std::cout << matrix_A << std::endl;

    const int n = 100000; 
  
    auto start_time = std::chrono::high_resolution_clock::now(); 
    Matrix result_serial = dot_serial(matrix_A, matrix_B); 
    auto end_time = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> serial_duration = end_time - start_time; 

    start_time = std::chrono::high_resolution_clock::now(); 
    Matrix result_static_parallel_for = dot_static_parallel_for(matrix_C, matrix_D); 
    end_time = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> static_parallel_for_duration = end_time - start_time; 

    start_time = std::chrono::high_resolution_clock::now(); 
    Matrix result_dynamic_parallel_for = dot_dynamic_parallel_for(matrix_C, matrix_D); 
    end_time = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> dynamic_parallel_for_duration = end_time - start_time; 
  
    start_time = std::chrono::high_resolution_clock::now(); 
    Matrix result_fine_grained = dot_fine_grained(matrix_C, matrix_D); 
    end_time = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> fine_grained_duration = end_time - start_time; 

    // std::cout << "Serial result: " << result_serial 
            //   << std::endl; 
    // std::cout << "Parallel result: " << result_parallel 
            //   << std::endl; 
    std::cout << "Serial duration: "<< serial_duration.count() << " seconds" << std::endl; 
    std::cout << "Static partitioned parallel_for duration: " << static_parallel_for_duration.count() << " seconds" << std::endl; 
    // std::cout << "Speedup: " << serial_duration.count() / static_parallel_for_duration.count() << " times the parallel speed." << std::endl; 
    std::cout << "Dynamic partitioned parallel_for duration: " << dynamic_parallel_for_duration.count() << " seconds" << std::endl; 
    std::cout << "Fine grained duration: " << fine_grained_duration.count() << " seconds" << std::endl; 
    
    std::cout << std::setprecision(20) << result_serial(488, 0) << std::endl;

    std::cout << std::setprecision(20) << result_fine_grained(488, 0) << std::endl;

    if (result_serial == result_fine_grained) {
        std::cout << "Results are equal" << std::endl;
    }
    // std::cout << result_serial << std::endl;

    if (matrix_C == matrix_D) {
        std::cout << "Test matrices are equal" << std::endl;
    }

    // Matrix test1 = Matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    // Matrix test2 = Matrix({1, 2, 3, 4, 5 ,6}, 3, 2);

    // Matrix test_result = dot_fine_grained(test1, test2);
    // std::cout << test_result << std::endl << std::endl;

    // test_result = dot_static_parallel_for(test1, test2);
    // std::cout << test_result << std::endl << std::endl;

    // test_result = dot_dynamic_parallel_for(test1, test2);
    // std::cout << test_result << std::endl << std::endl;

    // test_result = dot_serial(test1, test2);
    // std::cout << test_result << std::endl << std::endl;

    return 0; 
}