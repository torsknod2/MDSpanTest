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

#include "mdspan.hpp" // Assuming this is the header where mdspan_extent_iterator is defined
#include <gtest/gtest.h>

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

class DynamicMDSpanExtentIteratorTest : public ::testing::Test {
protected:
  std::experimental::mdarray<float,
                             std::experimental::extents<std::size_t, 2, 4>>
      vertices{std::vector<float>(2 * 4)};
  std::experimental::mdspan<float,
                            std::experimental::extents<std::size_t, 2, 4>>
      vertices_mdspan = vertices.to_mdspan();

  void SetUp() override {

    vertices_mdspan = vertices.to_mdspan();
    ASSERT_EQ(vertices_mdspan.rank(), 2);
    ASSERT_EQ(vertices_mdspan.size(), 8);
    ASSERT_EQ(vertices_mdspan.extent(0), 2);
    ASSERT_EQ(vertices_mdspan.extent(1), 4);
  }

  void SetArrayContent() {
    vertices[0, 0] = 2.0f;
    vertices[0, 1] = 5.0f;
    vertices[0, 2] = 11.0f;
    vertices[0, 3] = 17.0f;
    vertices[1, 0] = 3.0f;
    vertices[1, 1] = 7.0f;
    vertices[1, 2] = 13.0f;
    vertices[1, 3] = 19.0f;
  }

  void TestArrayContent() {
    ASSERT_EQ(vertices.rank(), 2);
    ASSERT_EQ(vertices.size(), 8);
    ASSERT_EQ(vertices.extent(0), 2);
    ASSERT_EQ(vertices.extent(1), 4);
    ASSERT_FLOAT_EQ((vertices[0, 0]), 2.0f);
    ASSERT_FLOAT_EQ((vertices[0, 1]), 5.0f);
    ASSERT_FLOAT_EQ((vertices[0, 2]), 11.0f);
    ASSERT_FLOAT_EQ((vertices[0, 3]), 17.0f);
    ASSERT_FLOAT_EQ((vertices[1, 0]), 3.0f);
    ASSERT_FLOAT_EQ((vertices[1, 1]), 7.0f);
    ASSERT_FLOAT_EQ((vertices[1, 2]), 13.0f);
    ASSERT_FLOAT_EQ((vertices[1, 3]), 19.0f);
  }
};

TEST_F(DynamicMDSpanExtentIteratorTest, SizeCorrect) {
  SetArrayContent();
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

TEST_F(DynamicMDSpanExtentIteratorTest, CanDoSingleAssignment) {

  mdspan_extent_iterator<decltype(vertices_mdspan), 1> iterator =
      std::begin<decltype(vertices_mdspan), 1>(vertices_mdspan);
  ASSERT_EQ((*iterator).rank(), 1);
  ASSERT_EQ((*iterator).size(), 2);
  ASSERT_EQ((*iterator).extent(0), 2);
  // ASSERT_EQ((*iterator).extent(2), 0);
  /* FIXME This is really ugly, but due to what I described in GenerateTest not
   * better possible apparently. */
  (*iterator)[0] = 2.0f;
  (*iterator++)[1] = 3.0f;
  (*iterator)[0] = 5.0f;
  (*iterator++)[1] = 7.0f;
  (*iterator)[0] = 11.0f;
  (*iterator++)[1] = 13.0f;
  (*iterator)[0] = 17.0f;
  (*iterator++)[1] = 19.0f;
  TestArrayContent();
}

TEST_F(DynamicMDSpanExtentIteratorTest, Equality) {

  mdspan_extent_iterator<decltype(vertices_mdspan), 1> iterator =
      std::begin<decltype(vertices_mdspan), 1>(vertices_mdspan);
  mdspan_extent_iterator<decltype(vertices_mdspan), 1> sentinel =
      std::end<decltype(vertices_mdspan), 1>(vertices_mdspan);
  ASSERT_EQ((*iterator).rank(), 1);
  ASSERT_EQ((*iterator).size(), 2);
  ASSERT_EQ((*iterator).extent(0), 2);
  ASSERT_EQ(iterator, iterator);
  ASSERT_EQ(sentinel, sentinel);
}

TEST_F(DynamicMDSpanExtentIteratorTest, NonEquality) {
  mdspan_extent_iterator<decltype(vertices_mdspan), 1> iterator =
      std::begin<decltype(vertices_mdspan), 1>(vertices_mdspan);
  mdspan_extent_iterator<decltype(vertices_mdspan), 1> sentinel =
      std::end<decltype(vertices_mdspan), 1>(vertices_mdspan);
  ASSERT_EQ((*iterator).rank(), 1);
  ASSERT_EQ((*iterator).size(), 2);
  ASSERT_EQ((*iterator).extent(0), 2);
  ASSERT_NE(iterator, sentinel);
  ASSERT_NE(sentinel, iterator);
}
