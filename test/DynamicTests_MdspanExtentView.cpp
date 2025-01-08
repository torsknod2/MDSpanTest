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
  EXPECT_EQ(original.extent(),
            0); // Assuming moved-from object is set to default state
}

// Test case to check the move assignment operator
TEST(MdspanExtentViewTest, MoveAssignmentOperator) {
  mdspan_extent_view<int> original(6);
  mdspan_extent_view<int> moved;
  moved = std::move(original);
  EXPECT_EQ(moved.extent(), 6);
  EXPECT_EQ(original.extent(),
            0); // Assuming moved-from object is set to default state
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

TEST_F(DynamicMDSpanExtentIteratorTest, GenerateTest) {
  FAIL()
      << "FIXME Beside not matching current TestArrayContent implementation, "
         "this fails because the assignment to the returned mdspan is only "
         "possible from another mdspan and not replacing the references "
         "values. Having opertor[] returning something which allows this, "
         "would also resolve the problem, but it does not support "
         "std::experimental::full_extent as index.";
  /*
std::generate(
    mdspan_extent_iterator<decltype(vertices_mdspan), 1>(vertices_mdspan),
    mdspan_extent_iterator<decltype(vertices_mdspan), 1>(
        vertices_mdspan, vertices_mdspan.extent(1)),
    []() -> std::tuple<float, float> {
      auto fibonacci_generator = [a = 0.0f, b = 1.0f]() mutable -> float {
        float next = a + b;
        a = b;
        b = next;
        return a;
      };
      return std::make_tuple<float, float>(fibonacci_generator(),
                                           fibonacci_generator());
    });
TestArrayContent();
*/
}