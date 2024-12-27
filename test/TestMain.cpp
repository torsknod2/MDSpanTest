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
#include <experimental/mdarray>
#include <experimental/mdspan>
#include <iterator>
#include <ranges>
#include <tuple>
#include <vector>

#include <mdspan_extensions.hpp>

#include <gtest/gtest.h>

enum class Precondition { Init, Started, Passed };

static Precondition inputOrOutputIteratorTestStatus = Precondition::Init;
static Precondition indirectlyReadableTestStatus = Precondition::Init;
static Precondition indirectlyWriteableTestStatus = Precondition::Init;

TEST(StaticMDSpanExtentView, StaticMDSpanExtentViewIsRange) {
  static_assert(
      std::ranges::range<mdspan_extent_view<
          std::experimental::mdspan<
              float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
          1>>);
}

TEST(StaticMDSpanExtentView, StaticMDSpanExtentViewIsView) {
  static_assert(
      std::ranges::view<mdspan_extent_view<
          std::experimental::mdspan<
              float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
          1>>);
}

TEST(StaticMDSpanExtentIterator, BeginIsAnInputOrOutputIterator) {
  inputOrOutputIteratorTestStatus = Precondition::Started;
  static_assert(
      std::input_or_output_iterator<mdspan_extent_iterator<
          std::experimental::mdspan<
              float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
          1>>);
  inputOrOutputIteratorTestStatus = Precondition::Passed;
}

TEST(StaticMDSpanExtentIterator, BeginIsIndirectlyReadable) {
  indirectlyReadableTestStatus = Precondition::Started;
  ASSERT_TRUE(static_cast<bool>(
      std::indirectly_readable<mdspan_extent_iterator<
          std::experimental::mdspan<
              float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
          1>>));
  indirectlyReadableTestStatus = Precondition::Passed;
}

TEST(StaticMDSpanExtentIterator, BeginIsIndirectlyWriteable) {
  indirectlyWriteableTestStatus = Precondition::Started;
  ASSERT_TRUE(static_cast<bool>(
      std::indirectly_writable<
          mdspan_extent_iterator<
              std::experimental::mdspan<
                  float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
              1>,
          std::experimental::mdspan<
              float, std::experimental::extents<std::intmax_t, 2, 5>>>));
  indirectlyWriteableTestStatus = Precondition::Passed;
}

TEST(StaticMDSpanExtentIterator, EndIsSentinelForBegin) {
  if (inputOrOutputIteratorTestStatus == Precondition::Started)
    GTEST_SKIP() << "The test for input_or_output_iterator failed, so the test "
                    "for input_iterator does not make sense and gets skipped.";
  else
    static_assert(
        std::sentinel_for<
            mdspan_extent_iterator<
                std::experimental::mdspan<
                    float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
                1>,
            mdspan_extent_iterator<
                std::experimental::mdspan<
                    float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
                1>>);
}

TEST(StaticMDSpanExtentIterator, BeginIsAnInputIterator) {
  if (inputOrOutputIteratorTestStatus == Precondition::Started &&
      indirectlyReadableTestStatus == Precondition::Started)
    GTEST_SKIP() << "The test for input_or_output_iterator and/ or "
                    "indirectly_readble failed, so the test "
                    "for input_iterator does not make sense and gets skipped.";
  else
    ASSERT_TRUE(static_cast<bool>(
        std::input_iterator<mdspan_extent_iterator<
            std::experimental::mdspan<
                float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
            1>>));
}

TEST(StaticMDSpanExtentIterator, BeginIsAnOutputIterator) {
  if (inputOrOutputIteratorTestStatus == Precondition::Started &&
      indirectlyWriteableTestStatus == Precondition::Started)
    GTEST_SKIP() << "The test for input_or_output_iterator and/ or "
                    "indirectly_writeable failed, so the test "
                    "for output_iterator does not make sense and gets skipped.";
  else {
    ASSERT_TRUE(static_cast<bool>(
        std::output_iterator<
            mdspan_extent_iterator<
                std::experimental::mdspan<
                    float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
                1>,
            std::experimental::mdspan<
                float, std::experimental::extents<std::intmax_t, 2, 5>>>));
    FAIL()
        << "FIXME Long error message when changing to a static assertion, but "
           "I do not fully get it frankly. I guess what it wants to say me is "
           "basically why GenerateTest obviously has to fail.";
  }
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

TEST(StaticMDSpanOutputRange, IsAnOutputRange) {
  /*
static_assert(static_cast<bool>(
    std::ranges::output_range<
        mdspan_range_submdspans<
            std::experimental::mdspan<
                float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
            1>,
        std::experimental::mdspan<
            float, std::experimental::extents<std::intmax_t, 2, 5>>>));
            */
  FAIL() << "FIXME Root-Cause for this to fail are the iterators, see above. "
            "Also see the comments in the std::begin and std::end overrides.";
}
