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