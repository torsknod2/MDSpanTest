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

#include <experimental/mdarray>
#include <experimental/mdspan>

#include <benchmark/benchmark.h>

#include <mdspan_extensions.hpp>

void mdSpanBenchmark(benchmark::State &State) {
  constexpr std::size_t VERTICES = 40000;
  std::experimental::mdarray<
      float, std::experimental::extents<std::size_t, VERTICES, 4>>
      Vertices{};
  const auto VerticesMDSpan = Vertices.to_mdspan();

  for (auto _ : State) {
    for (std::size_t I = 0; I < VerticesMDSpan.extent(0); ++I) {
      auto SubMDSpan = std::experimental::submdspan(
          VerticesMDSpan, I, std::experimental::full_extent);
      benchmark::DoNotOptimize(SubMDSpan);
    }
  }
}

BENCHMARK(mdSpanBenchmark);

BENCHMARK_MAIN();