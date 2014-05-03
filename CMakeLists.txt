cmake_minimum_required(VERSION 2.8)
project(ts-processor)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message(FATAL_ERROR "Support the Clang only!")
endif()

set(CMAKE_CXX_FLAGS "-std=gnu++1y -stdlib=libc++ -Wall -Wextra -Wno-sign-compare")
set(LIB_NAME ts_processor)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/vendor/bitfield)
add_subdirectory(src/ts_processor)

if(IS_TEST)
  add_subdirectory(test)
else()
  add_subdirectory(src)
endif()
