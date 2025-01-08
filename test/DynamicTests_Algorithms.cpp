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

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Function to test if a vector is sorted
bool isSorted(const std::vector<int>& vec) {
    return std::is_sorted(vec.begin(), vec.end());
}

// Function to test finding an element in a vector
bool findElement(const std::vector<int>& vec, int element) {
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

// Function to test counting occurrences of an element in a vector
int countOccurrences(const std::vector<int>& vec, int element) {
    return std::count(vec.begin(), vec.end(), element);
}

// Function to test reversing a vector
std::vector<int> reverseVector(const std::vector<int>& vec) {
    std::vector<int> reversedVec = vec;
    std::reverse(reversedVec.begin(), reversedVec.end());
    return reversedVec;
}

// Function to test sorting a vector
std::vector<int> sortVector(const std::vector<int>& vec) {
    std::vector<int> sortedVec = vec;
    std::sort(sortedVec.begin(), sortedVec.end());
    return sortedVec;
}

// Main function to run dynamic tests
void runDynamicTests() {
    std::vector<int> testVec = {5, 3, 8, 1, 2, 7, 4, 6};

    // Test if the vector is sorted
    assert(!isSorted(testVec));

    // Test finding an element
    assert(findElement(testVec, 3));
    assert(!findElement(testVec, 10));

    // Test counting occurrences
    assert(countOccurrences(testVec, 1) == 1);
    assert(countOccurrences(testVec, 10) == 0);

    // Test reversing the vector
    std::vector<int> reversedVec = reverseVector(testVec);
    assert(reversedVec.front() == 6 && reversedVec.back() == 5);

    // Test sorting the vector
    std::vector<int> sortedVec = sortVector(testVec);
    assert(isSorted(sortedVec));
    assert(sortedVec.front() == 1 && sortedVec.back() == 8);
}

int main() {
    runDynamicTests();
    std::cout << "All dynamic tests passed successfully." << std::endl;
    return 0;
}