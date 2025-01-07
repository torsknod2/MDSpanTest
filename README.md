# std::(experimental::)mdspan testing

This repository contains my trial & error to understand std::(experimental::)mdspan well enough to use it with std::linalg.
Right now I try to allow to have a `std::ranges::view` of an extent of an `std::mdspan`.
The goal is to be able to use the iterators with the `std` algorithm's to test how good GCC (and Clang and perhaps others) generates code for it to evaluate the current usability for me.
Stretch goal, if using proper execution policies with the `std` algorithm's is not sufficiently efficient, is to integrate them with std::(experimental::)simd .
Feedback from the people working on the `std::mdspan` reference implementation and others would be really appreciated.
It's my first time trying to contribute to the standard library.

## Status Badges

- [![Dependabot Updates](https://github.com/torsknod2/MDSpanTest/actions/workflows/dependabot/dependabot-updates/badge.svg)](https://github.com/torsknod2/MDSpanTest/actions/workflows/dependabot/dependabot-updates)
- [![C++ CI](https://github.com/torsknod2/MDSpanTest/actions/workflows/ci.yml/badge.svg)](https://github.com/torsknod2/MDSpanTest/actions/workflows/ci.yml)
- [![OpenSSF Scorecard](https://api.scorecard.dev/projects/github.com/torsknod2/MDSpanTest/badge)](https://scorecard.dev/viewer/?uri=github.com/torsknod2/MDSpanTest)
- [![OpenSSF Best Practices](https://bestpractices.coreinfrastructure.org/projects/9894/badge)](https://bestpractices.coreinfrastructure.org/projects/9894)

## Project Structure

|      File/Directory      	  |                                                        Description                                                          	|
|:------------------------------|:-----------------------------------------------------------------------------------------------------------------------------|
| `.clang-format`          	  | Clang format configuration file based on `llvm` as this seems to be the main target of the `mdspan` reference implementation.|
| `.clang-tidy`            	  | Clang tidy configuration file based on `llvm` as this seems to be the main target of the `mdspan` reference implementation.  |
| `.github/`               	  | GitHub related files. I should improve the content based on https://stackoverflow.com/a/61301254/1950725 .                   |
| &nbsp;`CODEOWNERS`            | Code Owners File giving (only) me the ownership over everything in the repository.                                           |
| &nbsp;`dependabot.yml`        | DependaBot configuration file                                                                                                |
| &nbsp;`workflow/`             | GitHub Action workflow files                                                                                                 |
| &nbsp;&nbsp;`ci.yml`          | GitHub Actions workflow file                                                                                                 |
| `.gitignore`             	  | Git ignore file                                                                                                              |
| `CMakeLists.txt`         	  | CMake build configuration file                                                                                               |
| `LICENSE`                	  | License file, license intentionally equal to the one of the `mdspan` reference implementation.                               |
| `README.md`              	  | Project readme file/ this file. Hopefully you find everything from here.                                                     |
| `include/`               	  | C++ headers/ include files.                                                                                                  |
| &nbsp;`mdspan_extensions.hpp` | Header file for my draft/ work-in-progress/ to-be-proposed mdspan extensions.                                                |
| `benchmark/`                  | Google Benchmarks to be able to compare the performance using various execution policies and so on.                          |
| &nbsp;`BenchmarkMain.cpp`     | Dummy Benchmarks right now, first the tests have to pass.                                                                    |
| `test/`                  	  | Google Test based functionality tests to be passed before benchmarks make sense.                                             |
| &nbsp;`TestMain.cpp`          | The one and only tests right now I have.                                                                                     |

## Requirements

- C++26 compatible compiler
- CMake
- std::(experimental::)mdspan
- Google Benchmark
- Google Test

## Building the Project

1. Clone the repository:
   ```
   git clone <repository-url>
   cd MDSpanTest
   ```

2. Create a build directory:
   ```
   mkdir build
   cd build
   ```

3. Configure the project using CMake:
   ```
   cmake ..
   ```

4. Build the project:
   ```
   cmake --build .
   ```

## Running Tests

To run the Google Test cases, execute the following command in the build directory:
```
ctest
```

## Running Benchmarks

To run the Google Benchmark tests, execute the following command in the build directory:
```
./benchmark/BenchmarkMain
```

## CI/CD

This project includes a GitHub Actions workflow configured to build the project using all available C++26 toolchains, run the tests and benchmarks, and report the results. The workflow file is located at `.github/workflows/ci.yml`.

## License

This project is licensed under the terms of the Apache License 2.0. See the LICENSE file for details.
