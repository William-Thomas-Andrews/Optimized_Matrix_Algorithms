# Parallel Matrix Multiplication in C++

This project implements a custom `Matrix` class in C++ along with multiple algorithms for matrix multiplication, both serial and parallel.  
The goal is to explore **parallelism in C++** using Intel Threading Building Blocks (TBB), C++ Standard Library parallel execution policies, and manual threading.

---

## Features

- **Custom `Matrix` class**
  - Dynamic allocation with bounds checking
  - Operator overloading (`+`, `-`, `*`, `/`, `==`, `!=`)
  - Row and element indexing
  - Transpose operation
  - String/stream printing

- **Matrix multiplication algorithms**
  - `dot_serial` → baseline single-threaded implementation
  - `dot_static_parallel_for` → TBB `parallel_for` with default partitioning
  - `dot_dynamic_parallel_for` → TBB `parallel_for` with `static_partitioner`
  - `dot_fine_grained` → manual multi-threading with `std::thread`
  - (experimental) `dot_for_each` using `std::for_each` with execution policies

---

## Dependencies

- **C++20 or later** (C++2b features supported)
- [Intel TBB](https://github.com/oneapi-src/oneTBB) (for parallel `parallel_for`)
- Standard C++ libraries (`<execution>`, `<thread>`, `<future>`, etc.)

On macOS with Homebrew:
```bash
brew install tbb
```

On Windows with vcpkg
```shell
vcpkg install tbb
```

On Linux (Debian/Ubuntu-based systems) with APT
```bash
sudo apt-get install libtbb-dev
```


How to run
```bash
# Clone the repository
git clone https://github.com/William-Thomas-Andrews/Shortest_Path_Algorithms.git
cd Shortest_Path_Algorithms

# Build
cd scripts/
./configure.sh
./build.sh
./run.sh
```