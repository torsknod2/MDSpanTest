#ifndef STATIC_TESTS_HPP
#define STATIC_TESTS_HPP

#include <experimental/mdspan>

namespace static_tests {

using std::experimental::mdspan;
using std::experimental::dextents;
using std::experimental::extents;
using std::experimental::layout_left;
using std::experimental::layout_right;
using std::experimental::dynamic_extent;

// Define a static extent mdspan for testing
template<typename ElementType, size_t... Extents>
using static_mdspan = mdspan<ElementType, extents<Extents...>>;

// Define a dynamic extent mdspan for testing
template<typename ElementType, size_t Rank>
using dynamic_mdspan = mdspan<ElementType, dextents<Rank>>;

} // namespace static_tests

#endif // STATIC_TESTS_HPP