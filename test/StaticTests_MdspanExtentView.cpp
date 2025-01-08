// StaticTests_MdspanExtentView.cpp

#include <iostream>
#include <ranges>
#include <cassert>

void test_extent_view() {
    // Test case 1: Check if the extent view correctly reflects the size of the range
    {
        std::array<int, 5> arr = {1, 2, 3, 4, 5};
        auto extent_view = std::ranges::views::all(arr);
        assert(extent_view.size() == 5);
    }

    // Test case 2: Check if the extent view works with an empty range
    {
        std::array<int, 0> arr = {};
        auto extent_view = std::ranges::views::all(arr);
        assert(extent_view.size() == 0);
    }

    // Test case 3: Check if the extent view works with a subrange
    {
        std::array<int, 5> arr = {1, 2, 3, 4, 5};
        auto subrange = std::ranges::subrange(arr.begin(), arr.begin() + 3);
        auto extent_view = std::ranges::views::all(subrange);
        assert(extent_view.size() == 3);
    }

    // Test case 4: Check if the extent view works with a different container
    {
        std::vector<int> vec = {1, 2, 3, 4, 5, 6};
        auto extent_view = std::ranges::views::all(vec);
        assert(extent_view.size() == 6);
    }

    // Test case 5: Check if the extent view works with a string
    {
        std::string str = "hello";
        auto extent_view = std::ranges::views::all(str);
        assert(extent_view.size() == 5);
    }

    std::cout << "All static extent view tests passed!" << std::endl;
}

int main() {
    test_extent_view();
    return 0;
}