#ifndef DYNAMIC_TESTS_BASE_HPP
#define DYNAMIC_TESTS_BASE_HPP

#include <vector>

class DynamicTestsBase {
public:
    // Virtual destructor for proper cleanup of derived classes
    virtual ~DynamicTestsBase() {}

    // Method to initialize the test with a given size
    virtual void initializeTest(size_t size) = 0;

    // Method to compare the generated sequence with a Fibonacci sequence
    virtual bool compareWithFibonacci(const std::vector<int>& sequence) = 0;

protected:
    // Helper method to generate a Fibonacci sequence of a given size
    std::vector<int> generateFibonacciSequence(size_t size) {
        std::vector<int> fibonacci(size);
        if (size > 0) fibonacci[0] = 0;
        if (size > 1) fibonacci[1] = 1;
        for (size_t i = 2; i < size; ++i) {
            fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        }
        return fibonacci;
    }
};

#endif // DYNAMIC_TESTS_BASE_HPP