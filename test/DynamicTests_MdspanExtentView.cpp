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

#include "mdspan_extensions.hpp"

#include "DynamicTestsBase.hpp"

TYPED_TEST(DynamicMDSpanExtentTest, DefaultConstructor) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view();
  EXPECT_EQ(view.extent(), 0);
}

TYPED_TEST(DynamicMDSpanExtentTest, ConstructFromMDSpan) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view(
      this->vertices_mdspan);
  EXPECT_EQ(view.extent(), 5);
}

TYPED_TEST(DynamicMDSpanExtentTest, CopyConstructor) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> original(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> copy(original);
  EXPECT_EQ(copy.extent(), 7);
}

TYPED_TEST(DynamicMDSpanExtentTest, AssignmentOperator) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> original(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> assigned();
  assigned = original;
  EXPECT_EQ(assigned.extent(), 3);
}

TYPED_TEST(DynamicMDSpanExtentTest, MoveConstructor) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> original(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> moved(
      std::move(original));
  EXPECT_EQ(moved.extent(), 4);
  EXPECT_EQ(original.extent(),
            0); // Assuming moved-from object is set to default state
}

TYPED_TEST(DynamicMDSpanExtentTest, MoveAssignmentOperator) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> original(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> moved();
  moved = std::move(original);
  EXPECT_EQ(moved.extent(), 6);
  EXPECT_EQ(original.extent(),
            0); // Assuming moved-from object is set to default state
}

TYPED_TEST(DynamicMDSpanExtentTest, EqualityOperator) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view1(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view2(
      this->vertices_mdspan);
  EXPECT_TRUE(view1 == view2);
}

TYPED_TEST(DynamicMDSpanExtentTest, InequalityOperator) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view1(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view2(9);
  EXPECT_TRUE(view1 != view2);
}

TYPED_TEST(DynamicMDSpanExtentTest, SizeCorrect) {
  this->setArrayContent();
  /*
  ASSERT_EQ((std::ranges::size<decltype(vertices_mdspan), 1>(vertices_mdspan)),
            (static_cast<size_t>(4)));
  ASSERT_EQ((std::ranges::size<decltype(vertices_mdspan), 2>(vertices_mdspan)),
            (static_cast<size_t>(2)));
            */
  FAIL() << "FIXME This is not working, because it claims that the referenze "
            "to size is ambiguous. I guess this has to do with the template "
            "template parameters I require, but I am not really sure.";
}

TYPED_TEST(DynamicMDSpanExtentTest, GenerateTest) {
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