// StaticTests_MdspanExtentIterator.cpp

#include <iostream>
#include <vector>
#include <cassert>

// A simple iterator class for demonstration purposes
template<typename T>
class SimpleIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    SimpleIterator(pointer ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    // Prefix increment
    SimpleIterator& operator++() { 
        m_ptr++; 
        return *this; 
    }  

    // Postfix increment
    SimpleIterator operator++(int) { 
        SimpleIterator tmp = *this; 
        ++(*this); 
        return tmp; 
    }

    friend bool operator==(const SimpleIterator& a, const SimpleIterator& b) { 
        return a.m_ptr == b.m_ptr; 
    }

    friend bool operator!=(const SimpleIterator& a, const SimpleIterator& b) { 
        return a.m_ptr != b.m_ptr; 
    }

private:
    pointer m_ptr;
};

// Static test cases using the SimpleIterator
void staticTestCases() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    SimpleIterator<int> begin(data.data());
    SimpleIterator<int> end(data.data() + data.size());

    // Test case 1: Check if the iterator correctly iterates over the elements
    int expectedValue = 1;
    for (auto it = begin; it != end; ++it) {
        assert(*it == expectedValue);
        expectedValue++;
    }

    // Test case 2: Check if the iterator correctly identifies the end
    SimpleIterator<int> it = begin;
    for (size_t i = 0; i < data.size(); ++i) {
        ++it;
    }
    assert(it == end);

    // Test case 3: Check if dereferencing works correctly
    it = begin;
    assert(*it == 1);
    ++it;
    assert(*it == 2);
}

int main() {
    staticTestCases();
    std::cout << "All static test cases passed." << std::endl;
    return 0;
}