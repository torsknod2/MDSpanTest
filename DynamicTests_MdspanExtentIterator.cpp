#include <gtest/gtest.h>
#include "mdspan.hpp" // Assuming this is the header where mdspan_extent_iterator is defined

// Test fixture for mdspan_extent_iterator
class MdspanExtentIteratorTest : public ::testing::Test {
protected:
    // You can add shared setup code here if needed
};

// Test case for default construction
TEST_F(MdspanExtentIteratorTest, DefaultConstruction) {
    mdspan_extent_iterator<int> it;
    EXPECT_EQ(it.current_extent(), 0);
}

// Test case for construction with initial extent
TEST_F(MdspanExtentIteratorTest, ConstructionWithInitialExtent) {
    mdspan_extent_iterator<int> it(5);
    EXPECT_EQ(it.current_extent(), 5);
}

// Test case for increment operation
TEST_F(MdspanExtentIteratorTest, IncrementOperation) {
    mdspan_extent_iterator<int> it(5);
    ++it;
    EXPECT_EQ(it.current_extent(), 6);
}

// Test case for decrement operation
TEST_F(MdspanExtentIteratorTest, DecrementOperation) {
    mdspan_extent_iterator<int> it(5);
    --it;
    EXPECT_EQ(it.current_extent(), 4);
}

// Test case for equality comparison
TEST_F(MdspanExtentIteratorTest, EqualityComparison) {
    mdspan_extent_iterator<int> it1(5);
    mdspan_extent_iterator<int> it2(5);
    EXPECT_TRUE(it1 == it2);
}

// Test case for inequality comparison
TEST_F(MdspanExtentIteratorTest, InequalityComparison) {
    mdspan_extent_iterator<int> it1(5);
    mdspan_extent_iterator<int> it2(6);
    EXPECT_TRUE(it1 != it2);
}

// Test case for dereference operation
TEST_F(MdspanExtentIteratorTest, DereferenceOperation) {
    mdspan_extent_iterator<int> it(5);
    EXPECT_EQ(*it, 5);
}

// Test case for addition operation
TEST_F(MdspanExtentIteratorTest, AdditionOperation) {
    mdspan_extent_iterator<int> it(5);
    it = it + 3;
    EXPECT_EQ(it.current_extent(), 8);
}

// Test case for subtraction operation
TEST_F(MdspanExtentIteratorTest, SubtractionOperation) {
    mdspan_extent_iterator<int> it(5);
    it = it - 2;
    EXPECT_EQ(it.current_extent(), 3);
}