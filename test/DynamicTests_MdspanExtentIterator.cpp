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

#include <algorithm>
#include <execution>
#include <iterator>
#include <ranges>
#include <type_traits>

#include <gtest/gtest.h>

#include "mdspan_extensions.hpp"

#include "DynamicTestsBase.hpp"

/*
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

*/

TYPED_TEST(DynamicMDSpanExtentTest, CanDoSingleAssignment) {

  mdspan_extent_iterator<decltype(this->vertices_mdspan), 1> iterator(
      this->vertices_mdspan);
  ASSERT_EQ((*iterator).rank(), 2);
  ASSERT_EQ((*iterator).size(), 10);
  ASSERT_EQ((*iterator).extent(0), 2);
  ASSERT_EQ((*iterator).extent(1), 5);
  /* FIXME This is really ugly, but due to what I described in GenerateTest not
   * better possible apparently. */
  auto FibonacciGenerator = this->fibonacciGenerator();
  FAIL() << "Need indirectly readable iterators first";
  /*
  std::ranges::for_each(
      std::views::zip(
          this->fibonacciGenerator(this->vertices.size()),
          std::views::cartesian_product(
              std::views::counted(iterator, this->vertices.extent(1)),
              std::views::iota(
                  static_cast<decltype(this->vertices.extent(0))>(0),
                  this->vertices.extent(0)),
              std::views::iota(
                  static_cast<decltype(this->vertices.extent(0))>(2),
                  this->vertices.extent(2)))),
      [](const std::tuple<
          TypeParam, std::tuple<std::size_t, decltype(*iterator), std::size_t>,
          TypeParam> &tuple) {
        const TypeParam value = std::get<0>(tuple);
        const std::tuple<std::size_t, decltype(*iterator), std::size_t> axes =
            std::get<1>(tuple);
        const auto &element = std::get<1>(axes);
        element[std::get<0>(axes), std::get<2>(axes)] = value;
      });
      */
  this->testArrayContent();
}

TYPED_TEST(DynamicMDSpanExtentTest, Equality) {
  mdspan_extent_iterator<decltype(this->vertices_mdspan), 1> iterator(
      this->vertices_mdspan);
  mdspan_extent_iterator<decltype(this->vertices_mdspan), 1> sentinel(
      this->vertices_mdspan, this->vertices_mdspan.extent(1));
  ASSERT_EQ((*iterator).rank(), 2);
  ASSERT_EQ((*iterator).size(), 10);
  ASSERT_EQ((*iterator).extent(0), 2);
  ASSERT_EQ((*iterator).extent(1), 5);
  ASSERT_EQ(iterator, iterator);
  ASSERT_EQ(sentinel, sentinel);
}

TYPED_TEST(DynamicMDSpanExtentTest, NonEquality) {
  mdspan_extent_iterator<decltype(this->vertices_mdspan), 1> iterator(
      this->vertices_mdspan);
  mdspan_extent_iterator<decltype(this->vertices_mdspan), 1> sentinel(
      this->vertices_mdspan, this->vertices_mdspan.extent(1));
  ASSERT_EQ((*iterator).rank(), 2);
  ASSERT_EQ((*iterator).size(), 10);
  ASSERT_EQ((*iterator).extent(0), 2);
  ASSERT_EQ((*iterator).extent(1), 5);
  ASSERT_NE(iterator, sentinel);
  ASSERT_NE(sentinel, iterator);
}
