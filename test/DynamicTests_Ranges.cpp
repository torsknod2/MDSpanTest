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

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

// Function to perform a simple test on a range
void testRange(const std::vector<int> &data) {
  auto evenNumbers =
      data | std::views::filter([](int n) { return n % 2 == 0; });
  std::cout << "Even numbers: ";
  for (int n : evenNumbers) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}

// Function to perform a test that calculates the sum of a range
void testRangeSum(const std::vector<int> &data) {
  auto sum = std::accumulate(data.begin(), data.end(), 0);
  std::cout << "Sum of numbers: " << sum << std::endl;
}

// Function to perform a test that finds the maximum in a range
void testRangeMax(const std::vector<int> &data) {
  if (!data.empty()) {
    auto maxElement = *std::ranges::max_element(data);
    std::cout << "Maximum number: " << maxElement << std::endl;
  } else {
    std::cout << "The range is empty." << std::endl;
  }
}

// Main function to execute dynamic tests
int main() {
  std::vector<int> testData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::cout << "Running dynamic tests on testData..." << std::endl;
  testRange(testData);
  testRangeSum(testData);
  testRangeMax(testData);

  return 0;
}