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
- Standard C++ libraries

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

Example output
```txt
[ 25%] Building CXX object CMakeFiles/OPT.dir/test/Test.cpp.o
[ 50%] Linking CXX executable bin/OPT
[100%] Built target OPT

Activating Serial (single thread) matrix multiplication...
Done!
Activating static parallel-for matrix multiplication...
Done!
Activating dynamic parallel-for matrix multiplication...
Done!
Activating fine-grained matrix multiplication...
Done!

Serial duration: 7.02779 seconds
Static partitioned parallel_for duration: 1.46243 seconds
Dynamic partitioned parallel_for duration: 1.49554 seconds
Fine grained duration: 1.58466 seconds

All resulting matrix outputs are equal!
```

## License
This project is provided under the MIT License.
Intel TBB is distributed under the Apache 2.0 License.