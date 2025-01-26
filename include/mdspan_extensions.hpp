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

#include <concepts>
#include <functional>
#include <optional>
#include <type_traits>
#include <utility>

#include <experimental/mdspan>

/// @brief Iterate over std::experimental::submdspan's of an
/// std::experimental:mdspan.
/// @tparam MDS Is the std::experimental:mdspan
/// @tparam EXTENT Is the extent of the mdspan to iterate over.
template <typename MDS, MDS::rank_type EXTENT>
  requires std::derived_from<
      MDS, std::experimental::mdspan<
               typename MDS::element_type, typename MDS::extents_type,
               typename MDS::layout_type, typename MDS::accessor_type>>
class mdspan_extent_iterator {

private:
  std::optional<std::reference_wrapper<const MDS>> mdspan = std::nullopt;
  typename MDS::index_type index = static_cast<typename MDS::index_type>(0);

public:
  using difference_type = std::make_signed_t<typename MDS::index_type>;
  using iterator_category = std::random_access_iterator_tag;
  /// FIXME not working using iterator_concept =
  /// std::random_access_iterator_tag;
  // using value_type = decltype(*std::declval<mdspan_extent_iterator>);
  using reference = decltype(*std::declval<mdspan_extent_iterator>);

  mdspan_extent_iterator() = default;

  mdspan_extent_iterator(const mdspan_extent_iterator &other) = default;

  mdspan_extent_iterator(MDS &&mdspan,
                         const typename MDS::index_type index =
                             static_cast<typename MDS::index_type>(0))
      : mdspan(std::forward<MDS>(mdspan)), index(index) {}

  mdspan_extent_iterator(const MDS &mdspan,
                         const typename MDS::index_type index =
                             static_cast<typename MDS::index_type>(0))
      : mdspan(mdspan), index(index) {}

  /// @fixme This is not fullfiling the requirements for operator* of an output
  /// iterator, because the assignment to the return value, which is a
  /// std::experimental::submdspan result, which is again a
  /// std::experimental::mdspan, is changing the reference to the underlying
  /// data, but not the data itself.
  const auto operator*() const {
    return []<typename MDS::rank_type... PRE_EXTENTS,
              typename MDS::rank_type... POST_EXTENTS>(
               const MDS &mdspan,
               const std::integer_sequence<typename MDS::rank_type,
                                           PRE_EXTENTS...>,
               typename MDS::index_type index,
               const std::integer_sequence<typename MDS::rank_type,
                                           POST_EXTENTS...>) {
      return std::experimental::submdspan(
          mdspan,
          (static_cast<void>(PRE_EXTENTS), std::experimental::full_extent)...,
          index,
          (static_cast<void>(POST_EXTENTS), std::experimental::full_extent)...);
    }(mdspan.value(),
           std::make_integer_sequence<typename MDS::rank_type, EXTENT>{}, index,
           std::make_integer_sequence<typename MDS::rank_type,
                                      MDS::rank() - EXTENT - 1>{});
  }

  /// @fixme This is not fullfiling the requirements for operator[] of an output
  /// iterator, because the assignment to the return value, which is a
  /// std::experimental::submdspan result, which is again a
  /// std::experimental::mdspan, is changing the reference to the underlying
  /// data, but not the data itself.
  const auto operator[](const MDS::index_type offset) const {
    return []<typename MDS::rank_type... PRE_EXTENTS,
              typename MDS::rank_type... POST_EXTENTS>(
               const MDS &mdspan,
               const std::integer_sequence<typename MDS::rank_type,
                                           PRE_EXTENTS...>,
               typename MDS::index_type index,
               const std::integer_sequence<typename MDS::rank_type,
                                           POST_EXTENTS...>) {
      return std::experimental::submdspan(
          mdspan,
          (static_cast<void>(PRE_EXTENTS), std::experimental::full_extent)...,
          index,
          (static_cast<void>(POST_EXTENTS), std::experimental::full_extent)...);
    }(mdspan.value(),
           std::make_integer_sequence<typename MDS::rank_type, EXTENT>{},
           index + offset,
           std::make_integer_sequence<typename MDS::rank_type,
                                      MDS::rank() - EXTENT - 1>{});
  }

  mdspan_extent_iterator &operator++() {
    ++index;
    return *this;
  }

  mdspan_extent_iterator operator++(int) {
    mdspan_extent_iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  mdspan_extent_iterator &operator--() {
    --index;
    return *this;
  }

  mdspan_extent_iterator operator--(int) {
    mdspan_extent_iterator tmp = *this;
    --(*this);
    return tmp;
  }

  mdspan_extent_iterator operator+(const MDS::index_type n) {
    mdspan_extent_iterator tmp = *this;
    tmp.index += n;
    return tmp;
  }

  mdspan_extent_iterator operator-(const MDS::index_type n) {
    mdspan_extent_iterator tmp = *this;
    tmp.index -= n;
    return tmp;
  }

  auto operator<=>(const mdspan_extent_iterator &other) const {
    return index <=> other.index;
  }

  bool operator==(const mdspan_extent_iterator &other) const {
    return index == other.index;
  }

  bool operator!=(const mdspan_extent_iterator &other) const {
    return index != other.index;
  }

  mdspan_extent_iterator &operator=(const mdspan_extent_iterator &other) {
    mdspan = other.mdspan;
    index = other.index;
    return *this;
  };

  mdspan_extent_iterator &operator=(mdspan_extent_iterator &&other) noexcept {
    if (this != &other) {
      mdspan = std::move(other.mdspan);
      index = other.index;
    }
    return *this;
  }
};

template <typename MDS, MDS::rank_type EXTENT>
  requires std::derived_from<
      MDS, std::experimental::mdspan<
               typename MDS::element_type, typename MDS::extents_type,
               typename MDS::layout_type, typename MDS::accessor_type>>
class mdspan_extent_view
    : public std::ranges::view_interface<mdspan_extent_view<MDS, EXTENT>> {

private:
  std::optional<std::reference_wrapper<const MDS>> mdspan = std::nullopt;
  typename MDS::index_type index = static_cast<typename MDS::index_type>(0);

public:
  mdspan_extent_view() = default;

  mdspan_extent_view(const mdspan_extent_view &other) = default;

  mdspan_extent_view(MDS &&mdspan, const typename MDS::index_type index =
                                       static_cast<typename MDS::index_type>(0))
      : mdspan(std::forward<MDS>(mdspan)), index(index) {}

  mdspan_extent_view(const MDS &mdspan,
                     const typename MDS::index_type index =
                         static_cast<typename MDS::index_type>(0))
      : mdspan(mdspan), index(index) {}

  mdspan_extent_view &operator=(const mdspan_extent_view &other) = default;

  mdspan_extent_view &operator=(mdspan_extent_view &&other) noexcept = default;

  mdspan_extent_iterator<MDS, EXTENT> begin() const {
    return mdspan_extent_iterator<MDS, EXTENT>(mdspan.value());
  }

  mdspan_extent_iterator<MDS, EXTENT> end() const {
    return mdspan_extent_iterator<MDS, EXTENT>(
        mdspan.value(), mdspan.value().get().extent(EXTENT));
  }

  constexpr typename MDS::index_type size() const {
    return mdspan.has_value() ? mdspan.value().get().extent(EXTENT) : 0;
  }

  constexpr typename MDS::index_type ssize() const
    requires std::is_signed_v<typename MDS::index_type>
  {
    return size();
  }
};

namespace std {
namespace ranges {

template <typename MDS, MDS::rank_type EXTENT>
inline constexpr bool enable_view<mdspan_extent_view<MDS, EXTENT>> = true;

template <typename MDS, MDS::rank_type EXTENT>
inline constexpr bool enable_borrowed_range<mdspan_extent_view<MDS, EXTENT>> =
    true;
} // namespace ranges
} // namespace std
