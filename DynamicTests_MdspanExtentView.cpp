// This file contains dynamic test cases for mdspan_extent_view

#include <gtest/gtest.h>
#include "mdspan_extent_view.hpp" // Assuming this is the header file for mdspan_extent_view

// Test case to check the default constructor
TEST(MdspanExtentViewTest, DefaultConstructor) {
    mdspan_extent_view<int> view;
    EXPECT_EQ(view.extent(), 0);
}

// Test case to check construction with a specific extent
TEST(MdspanExtentViewTest, ConstructorWithExtent) {
    mdspan_extent_view<int> view(5);
    EXPECT_EQ(view.extent(), 5);
}

// Test case to check the extent method
TEST(MdspanExtentViewTest, ExtentMethod) {
    mdspan_extent_view<int> view(10);
    EXPECT_EQ(view.extent(), 10);
}

// Test case to check the copy constructor
TEST(MdspanExtentViewTest, CopyConstructor) {
    mdspan_extent_view<int> original(7);
    mdspan_extent_view<int> copy(original);
    EXPECT_EQ(copy.extent(), 7);
}

// Test case to check the assignment operator
TEST(MdspanExtentViewTest, AssignmentOperator) {
    mdspan_extent_view<int> original(3);
    mdspan_extent_view<int> assigned;
    assigned = original;
    EXPECT_EQ(assigned.extent(), 3);
}

// Test case to check the move constructor
TEST(MdspanExtentViewTest, MoveConstructor) {
    mdspan_extent_view<int> original(4);
    mdspan_extent_view<int> moved(std::move(original));
    EXPECT_EQ(moved.extent(), 4);
    EXPECT_EQ(original.extent(), 0); // Assuming moved-from object is set to default state
}

// Test case to check the move assignment operator
TEST(MdspanExtentViewTest, MoveAssignmentOperator) {
    mdspan_extent_view<int> original(6);
    mdspan_extent_view<int> moved;
    moved = std::move(original);
    EXPECT_EQ(moved.extent(), 6);
    EXPECT_EQ(original.extent(), 0); // Assuming moved-from object is set to default state
}

// Test case to check the equality operator
TEST(MdspanExtentViewTest, EqualityOperator) {
    mdspan_extent_view<int> view1(8);
    mdspan_extent_view<int> view2(8);
    EXPECT_TRUE(view1 == view2);
}

// Test case to check the inequality operator
TEST(MdspanExtentViewTest, InequalityOperator) {
    mdspan_extent_view<int> view1(8);
    mdspan_extent_view<int> view2(9);
    EXPECT_TRUE(view1 != view2);
}

#endif // MDSPAN_EXTENT_VIEW_TESTS_HPP