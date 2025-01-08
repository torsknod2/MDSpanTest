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

#include <experimental/mdspan>

namespace static_tests {

using std::experimental::dextents;
using std::experimental::dynamic_extent;
using std::experimental::extents;
using std::experimental::layout_left;
using std::experimental::layout_right;
using std::experimental::mdspan;

// Define a static extent mdspan for testing
template <typename ElementType, size_t... Extents>
using static_mdspan = mdspan<ElementType, extents<Extents...>>;

// Define a dynamic extent mdspan for testing
template <typename ElementType, size_t Rank>
using dynamic_mdspan = mdspan<ElementType, dextents<Rank>>;

} // namespace static_tests
