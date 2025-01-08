# Copyright 2025 Torsten Knodt
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http: //www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.30)

# TODO If this is not directly a tag, have the revisions since then as the tweak version
execute_process(
    COMMAND git describe --tags --always
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_PROJECT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(${GIT_PROJECT_VERSION} MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+$")
    project(MDSpanTest VERSION ${GIT_PROJECT_VERSION} LANGUAGES CXX)
else()
    execute_process(
        COMMAND git rev-list --count HEAD
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_COUNT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE GIT_COMMIT_COUNT_RESULT
    )
    if(NOT GIT_COMMIT_COUNT_RESULT EQUAL 0)
        project(MDSpanTest VERSION 0.0.0.${GIT_COMMIT_COUNT} LANGUAGES CXX)
    else()
        project(MDSpanTest LANGUAGES CXX)
    endif()
endif()

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CheckCXXCompilerFlag)
function(CheckAndUseCXXCompilerFlag flag)
    string(MAKE_C_IDENTIFIER ${flag} VAR)
    string(TOUPPER ${VAR} VAR)
    check_cxx_compiler_flag(${flag} HAVE_CXX_${VAR})
    if (HAVE_CXX_${VAR})
        add_compile_options(${flag})
    ENDIF(HAVE_CXX_${VAR})
endfunction(CheckAndUseCXXCompilerFlag)

# FIXME CheckAndUseCXXCompilerFlag(-D_GLIBCXX_PARALLEL)
CheckAndUseCXXCompilerFlag(-fanalyzer)
CheckAndUseCXXCompilerFlag(-fcallgraph-info)
CheckAndUseCXXCompilerFlag(-fconcepts-diagnostics-depth=255)
CheckAndUseCXXCompilerFlag(-fdata-sections)
CheckAndUseCXXCompilerFlag(-fdiagnostics-all-candidates)
CheckAndUseCXXCompilerFlag(-ffunction-sections)
CheckAndUseCXXCompilerFlag(-fhardened)
CheckAndUseCXXCompilerFlag(-fimplicit-constexpr)
CheckAndUseCXXCompilerFlag(-flto)
CheckAndUseCXXCompilerFlag(-fopenacc)
check_cxx_compiler_flag(-fsanitize=undefined HAVE_CXX_F_SANITIZE_UNDEFINED)
CheckAndUseCXXCompilerFlag(-fstack-usage)
CheckAndUseCXXCompilerFlag(-fuse-linker-plugin)
# CheckAndUseCXXCompilerFlag(-H)
CheckAndUseCXXCompilerFlag(-march=native)
CheckAndUseCXXCompilerFlag(-mtune=native)
CheckAndUseCXXCompilerFlag(-save-temps)
CheckAndUseCXXCompilerFlag(-Wall)
CheckAndUseCXXCompilerFlag(-Wextra)

find_package(OpenMP)

add_compile_options(${OpenMP_CXX_FLAGS})
add_link_options(${OpenMP_CXX_FLAGS})

include(CheckLinkerFlag)
function(CheckAndUseCXXLinkerFlag flag)
    string(MAKE_C_IDENTIFIER ${flag} VAR)
    string(TOUPPER ${VAR} VAR)
    check_linker_flag(CXX ${flag} HAVE_LD_${VAR})
    if (HAVE_LD_${VAR})
        add_link_options(${flag})
    ENDIF(HAVE_LD_${VAR})
endfunction(CheckAndUseCXXLinkerFlag)
CheckAndUseCXXLinkerFlag(--print-memory-usage)
check_linker_flag(CXX -fsanitize=undefined HAVE_LD_F_SANITIZE_UNDEFINED)
CheckAndUseCXXLinkerFlag(-flto)
CheckAndUseCXXLinkerFlag(-Wl,--gc-sections)
CheckAndUseCXXCompilerFlag(-foffload=default)
CheckAndUseCXXCompilerFlag(-fdiagnostics-set-output=text:experimental-nesting=yes,experimental-nesting-show-locations=yes,experimental-nesting-show-levels=yes)
CheckAndUseCXXCompilerFlag(-fdiagnostics-add-output=sarif-file)
CheckAndUseCXXCompilerFlag(-fdiagnostics-add-output=json-file)

if (HAVE_CXX_F_SANITIZE_UNDEFINED AND HAVE_LD_F_SANITIZE_UNDEFINED)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
ENDIF(HAVE_CXX_F_SANITIZE_UNDEFINED AND HAVE_LD_F_SANITIZE_UNDEFINED)

check_cxx_compiler_flag(-Oz HAVE_CXX_OPTIMIZE_FOR_SIZE_AGGRESSIVLY)
if(HAVE_CXX_OPTIMIZE_FOR_SIZE_AGGRESSIVLY)
    string(APPEND CMAKE_CXX_FLAGS_MINSIZEREL " -Oz")
endif(HAVE_CXX_OPTIMIZE_FOR_SIZE_AGGRESSIVLY)

check_cxx_compiler_flag(-Os HAVE_CXX_OPTIMIZE_FOR_SIZE)
if(HAVE_CXX_F_OPTIMIZE_FOR_SIZE_AGGRESSIVLY)
    string(APPEND CMAKE_CXX_FLAGS_MINSIZEREL " -Oz")
elseif(HAVE_CXX_OPTIMIZE_FOR_SIZE)
    string(APPEND CMAKE_CXX_FLAGS_MINSIZEREL " -Os")
endif()

check_cxx_compiler_flag(-Og HAVE_CXX_OPTIMIZE_FOR_DEBUG)
IF(HAVE_CXX_OPTIMIZE_FOR_DEBUG)
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " -Og")
ENDIF(HAVE_CXX_OPTIMIZE_FOR_DEBUG)

IF(CMAKE_BUILD_TYPE STREQUAL Debug)
    CheckAndUseCXXCompilerFlag(-Wno-error=hardened)
    CheckAndUseCXXLinkerFlag(-Wno-error=hardened)
    CheckAndUseCXXCompilerFlag(-ggdb)
    CheckAndUseCXXLinkerFlag(-ggdb)
    CheckAndUseCXXCompilerFlag(--coverage)
    CheckAndUseCXXLinkerFlag(--coverage)
    CheckAndUseCXXCompilerFlag(-fprofile-arcs)
    CheckAndUseCXXLinkerFlag(-fprofile-arcs)
    CheckAndUseCXXCompilerFlag(-ftest-coverage)
    CheckAndUseCXXLinkerFlag(-ftest-coverage)
    CheckAndUseCXXCompilerFlag(-fcondition-coverage)
ENDIF(CMAKE_BUILD_TYPE STREQUAL Debug)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.1
  URL https://github.com/google/benchmark/archive/v1.9.1.zip
)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
set(BENCHMARK_ENABLE_LTO OFF)
FetchContent_MakeAvailable(googlebenchmark)

FetchContent_Declare(
  mdspan
  GIT_REPOSITORY https://github.com/kokkos/mdspan.git
  GIT_TAG mdspan-0.6.0
  URL https://github.com/kokkos/mdspan/archive/refs/tags/mdspan-0.6.0.zip
)
FetchContent_MakeAvailable(mdspan)

add_library(mdspan_header INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/mdspan_extensions.hpp)
target_link_libraries(mdspan_header INTERFACE std::mdspan)
target_include_directories(mdspan_header INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(GenerateExportHeader)
# TODO generate_export_header(mdspan_header)

include(GNUInstallDirs)
install(TARGETS mdspan_header)

add_executable(BenchmarkMain ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/BenchmarkMain.cpp)
target_link_libraries(BenchmarkMain PRIVATE benchmark::benchmark mdspan_header)

include(CTest)
enable_testing()
include(GoogleTest)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest GTest::gtest_main std::mdspan mdspan_header)
    gtest_discover_tests(${TEST_NAME}
        TEST_PREFIX MDSpanTest_${TEST_NAME}_
        XML_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/GTestOutputDir/${TEST_NAME})
endforeach()

find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
if(Doxygen_FOUND)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      # FIXME Select the right version
      file(DOWNLOAD https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/libstdc++.tag libstdc++.tag SHOW_PROGRESS)
      set(DOXYGEN_TAGFILES libstdc++.tag)
  # FIXME Add a case for clang
  else(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      file(DOWNLOAD https://upload.cppreference.com/w/File:cppreference-doxygen-web.tag.xml?action=render cppreference-doxygen-web.tag.xml SHOW_PROGRESS)
      set(DOXYGEN_TAGFILES cppreference-doxygen-web.tag.xml)
  endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

  set(DOXYGEN_EXCLUDE_PATTERNS ${CMAKE_CURRENT_BINARY_DIR} data)
  set(DOXYGEN_EXTRACT_ALL YES)

  doxygen_add_docs(doxygen ALL USE_STAMP_FILE)
endif(Doxygen_FOUND)

include(FeatureSummary)
feature_summary(DEFAULT_DESCRIPTION WHAT ALL)