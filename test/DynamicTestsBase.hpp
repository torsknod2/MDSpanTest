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

#pragma once

#include <algorithm>
#include <generator>
#include <iterator>
#include <ranges>
#include <vector>

#include <experimental/mdarray>
#include <experimental/mdspan>

#include <gtest/gtest.h>

template <typename ValueType>
class DynamicMDSpanExtentTest : public ::testing::Test {
protected:
  std::experimental::mdarray<ValueType,
                             std::experimental::extents<size_t, 2, 3, 5>>
      vertices{std::vector<ValueType>(2 * 3 * 5), 2, 3, 5};
  std::experimental::mdspan<ValueType,
                            std::experimental::extents<size_t, 2, 3, 5>>
      vertices_mdspan = vertices.to_mdspan();

  void SetUp() override {
    ASSERT_EQ(vertices_mdspan.rank(), 3);
    ASSERT_EQ(vertices_mdspan.size(), 30);
    ASSERT_EQ(vertices_mdspan.extent(0), 2);
    ASSERT_EQ(vertices_mdspan.extent(1), 3);
    ASSERT_EQ(vertices_mdspan.extent(2), 5);
  }

  template <typename SizeType = std::uintmax_t>
  std::generator<ValueType> fibonacciGenerator(
      SizeType number = std::numeric_limits<SizeType>::max()) const
    requires(std::unsigned_integral<SizeType> &&
             std::numeric_limits<ValueType>::max() >
                 std::numeric_limits<decltype(number)>::max())
  {
    float a = static_cast<ValueType>(0);
    if (number-- > 0) {
      co_yield a;
      float b = static_cast<ValueType>(1);
      while (number-- > 0) {
        co_yield a = std::exchange(b, a + b);
      }
    }
  }

  void setArrayContent() {
    std::ranges::copy(fibonacciGenerator(vertices.size()), vertices.data());

    testArrayContent();
  }

  void testArrayContent() const {
    std::ranges::for_each(
        std::views::zip(std::views::counted(vertices.data(), vertices.size()),
                        fibonacciGenerator(vertices.size())),
        [](const std::tuple<ValueType, ValueType> &pair) {
          ASSERT_EQ(std::get<0>(pair), std::get<1>(pair));
        });
  }
};

using DynamicMDSpanExtentTestTypes = ::testing::Types<float>;
TYPED_TEST_SUITE(DynamicMDSpanExtentTest, DynamicMDSpanExtentTestTypes);
