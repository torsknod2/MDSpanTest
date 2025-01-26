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
  [[maybe_unused]] mdspan_extent_view<decltype(this->vertices_mdspan), 1> view;
  ASSERT_EQ(std::ranges::size(view), 0);
  ASSERT_EQ(std::ranges::ssize(view), 1);
  FAIL()
      << "Review requirements to a default constructed view beside being "
         "assignable and so on. Perhaps the right thing is just to check that, "
         "but I would like to be sure that the view is in the right state "
         "before.";
}

TYPED_TEST(DynamicMDSpanExtentTest, ConstructFromMDSpan) {
  this->setArrayContent();
  [[maybe_unused]] mdspan_extent_view<decltype(this->vertices_mdspan), 1> view(
      this->vertices_mdspan);
  FAIL() << "Check for equality of all values once iteration is working";
}

TYPED_TEST(DynamicMDSpanExtentTest, CopyConstructor) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> original(
      this->vertices_mdspan);
  [[maybe_unused]] mdspan_extent_view<decltype(this->vertices_mdspan), 1> copy(
      original);
  FAIL() << "Check for equality of all values once iteration is working";
}

TYPED_TEST(DynamicMDSpanExtentTest, AssignmentOperator) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> original(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> assigned;
  assigned = original;
  FAIL() << "Check for equality of all values once iteration is working";
}

TYPED_TEST(DynamicMDSpanExtentTest, MoveConstructor) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> original(
      this->vertices_mdspan);
  [[maybe_unused]] mdspan_extent_view<decltype(this->vertices_mdspan), 1> moved(
      std::move(original));
  FAIL() << "Check for correct values \"in\" new object and check for "
            "\"default\" values in moved-from object";
}

TYPED_TEST(DynamicMDSpanExtentTest, MoveAssignmentOperator) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> original(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> moved;
  moved = std::move(original);
  FAIL() << "Check for correct values \"in\" new object and check for "
            "\"default\" values in moved-from object";
}

/* TODO Why did I add them? Or was this CoPilot and I missed it?
TYPED_TEST(DynamicMDSpanExtentTest, EqualityOperator) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view1(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view2(
      this->vertices_mdspan);
  EXPECT_EQ(view1, view2);
}

TYPED_TEST(DynamicMDSpanExtentTest, InequalityOperator) {
  this->setArrayContent();
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view1(
      this->vertices_mdspan);
  mdspan_extent_view<decltype(this->vertices_mdspan), 1> view2(9);
  EXPECT_NE(view1, view2);
}

*/

TYPED_TEST(DynamicMDSpanExtentTest, SizeCorrect) {
  [[maybe_unused]] mdspan_extent_view<decltype(this->vertices_mdspan), 1> view(
      this->vertices_mdspan);
  ASSERT_EQ(std::ranges::size(view), 3);
}

TYPED_TEST(DynamicMDSpanExtentTest, SignedSizeCorrect) {
  [[maybe_unused]] mdspan_extent_view<decltype(this->vertices_mdspan), 1> view(
      this->vertices_mdspan);
  ASSERT_EQ(std::ranges::ssize(view), 3);
}