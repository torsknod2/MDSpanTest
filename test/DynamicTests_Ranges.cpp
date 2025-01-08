// DynamicTests_Ranges.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

// Function to perform a simple test on a range
void testRange(const std::vector<int>& data) {
    auto evenNumbers = data | std::views::filter([](int n) { return n % 2 == 0; });
    std::cout << "Even numbers: ";
    for (int n : evenNumbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

// Function to perform a test that calculates the sum of a range
void testRangeSum(const std::vector<int>& data) {
    auto sum = std::accumulate(data.begin(), data.end(), 0);
    std::cout << "Sum of numbers: " << sum << std::endl;
}

// Function to perform a test that finds the maximum in a range
void testRangeMax(const std::vector<int>& data) {
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