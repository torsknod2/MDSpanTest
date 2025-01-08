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

#include <StaticTests.hpp>

#include <gtest/gtest.h>

#include <mdspan_extensions.hpp>

enum class Precondition { Init, Started, Passed };

static Precondition inputOrOutputIteratorTestStatus = Precondition::Init;
static Precondition indirectlyReadableTestStatus = Precondition::Init;
static Precondition indirectlyWriteableTestStatus = Precondition::Init;

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
