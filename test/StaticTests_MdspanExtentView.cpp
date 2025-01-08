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

TEST(StaticMDSpanExtentView, MDSpanExtentViewIsRange) {
  static_assert(
      std::ranges::range<mdspan_extent_view<
          std::experimental::mdspan<
              float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
          1>>);
}

TEST(StaticMDSpanExtentView, MDSpanExtentViewIsView) {
  static_assert(
      std::ranges::view<mdspan_extent_view<
          std::experimental::mdspan<
              float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
          1>>);
}

TEST(StaticMDSpanExtentView, IsAnOutputRange) {
  ASSERT_TRUE(static_cast<bool>(
      std::ranges::output_range<
          mdspan_range_submdspans<
              std::experimental::mdspan<
                  float, std::experimental::extents<std::intmax_t, 2, 3, 5>>,
              1>,
          std::experimental::mdspan<
              float, std::experimental::extents<std::intmax_t, 2, 5>>>));
  FAIL() << "FIXME Root-Cause for this to fail are the iterators, see above. "
            "Also see the comments in the std::begin and std::end overrides.";
}
