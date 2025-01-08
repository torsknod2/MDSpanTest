/*
Copyright 2025 Torsten Knodt

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http: //www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include <vector>

class DynamicTestsBase {
public:
  // Virtual destructor for proper cleanup of derived classes
  virtual ~DynamicTestsBase() {}

  // Method to initialize the test with a given size
  virtual void initializeTest(size_t size) = 0;

  // Method to compare the generated sequence with a Fibonacci sequence
  virtual bool compareWithFibonacci(const std::vector<int> &sequence) = 0;

protected:
  // Helper method to generate a Fibonacci sequence of a given size
  std::vector<int> generateFibonacciSequence(size_t size) {
    std::vector<int> fibonacci(size);
    if (size > 0)
      fibonacci[0] = 0;
    if (size > 1)
      fibonacci[1] = 1;
    for (size_t i = 2; i < size; ++i) {
      fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }
    return fibonacci;
  }
};
