#include "Test.hpp"

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

    Matrix matrix_A = Matrix(vector1, 749, 499);
    Matrix matrix_B = Matrix(vector2, 499, 849);
    Matrix matrix_C = Matrix(vector1, 749, 499);
    Matrix matrix_D = Matrix(vector2, 499, 849);

    const int n = 100000; 
  
    std::cout << "\nActivating Serial (single thread) matrix multiplication..." << std::endl; 
    auto start_time = std::chrono::high_resolution_clock::now(); 
    Matrix result_serial = dot_serial(matrix_A, matrix_B); 
    auto end_time = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> serial_duration = end_time - start_time;

    for (int i = 0; i < 2; i++) {
        start_time = std::chrono::high_resolution_clock::now(); 
        result_serial = dot_serial(matrix_A, matrix_B); 
        end_time = std::chrono::high_resolution_clock::now(); 
        serial_duration += end_time - start_time;
    }

    std::cout << "Done!\nActivating static parallel-for matrix multiplication..." << std::endl; 
    start_time = std::chrono::high_resolution_clock::now(); 
    Matrix result_static_parallel_for = dot_static_parallel_for(matrix_C, matrix_D); 
    end_time = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> static_parallel_for_duration = end_time - start_time; 

    for (int i = 0; i < 2; i++) {
        start_time = std::chrono::high_resolution_clock::now(); 
        result_static_parallel_for = dot_static_parallel_for(matrix_A, matrix_B); 
        end_time = std::chrono::high_resolution_clock::now(); 
        static_parallel_for_duration += end_time - start_time;
    }

    std::cout << "Done!\nActivating dynamic parallel-for matrix multiplication..." << std::endl; 
    start_time = std::chrono::high_resolution_clock::now(); 
    Matrix result_dynamic_parallel_for = dot_dynamic_parallel_for(matrix_C, matrix_D); 
    end_time = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> dynamic_parallel_for_duration = end_time - start_time; 

    for (int i = 0; i < 2; i++) {
        start_time = std::chrono::high_resolution_clock::now(); 
        result_dynamic_parallel_for = dot_dynamic_parallel_for(matrix_A, matrix_B); 
        end_time = std::chrono::high_resolution_clock::now(); 
        dynamic_parallel_for_duration += end_time - start_time;
    }
  
    std::cout << "Done!\nActivating fine-grained matrix multiplication..." << std::endl; 
    start_time = std::chrono::high_resolution_clock::now(); 
    Matrix result_fine_grained = dot_fine_grained(matrix_C, matrix_D); 
    end_time = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> fine_grained_duration = end_time - start_time; 

    for (int i = 0; i < 2; i++) {
        start_time = std::chrono::high_resolution_clock::now(); 
        result_fine_grained = dot_fine_grained(matrix_A, matrix_B); 
        end_time = std::chrono::high_resolution_clock::now(); 
        fine_grained_duration += end_time - start_time;
    }

    std::cout << "Done!\n\nSerial duration: "<< serial_duration.count() << " seconds" << std::endl; 
    std::cout << "Static partitioned parallel_for duration: " << static_parallel_for_duration.count() << " seconds" << std::endl; 
    std::cout << "Dynamic partitioned parallel_for duration: " << dynamic_parallel_for_duration.count() << " seconds" << std::endl; 
    std::cout << "Fine grained duration: " << fine_grained_duration.count() << " seconds\n" << std::endl; 

    if (result_serial == result_static_parallel_for and result_serial == result_dynamic_parallel_for and result_serial == result_fine_grained and
        result_static_parallel_for == result_dynamic_parallel_for and result_static_parallel_for == result_fine_grained and result_dynamic_parallel_for == result_fine_grained) {
        std::cout << "All resulting matrix outputs are equal!" << std::endl;
    }

    if (matrix_C == matrix_D) {
        std::cout << "Test matrices are equal" << std::endl;
    }

    return 0; 
}