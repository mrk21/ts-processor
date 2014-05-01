cmake_minimum_required(VERSION 2.8)
project(ts-processor)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(LIB_NAME ts_processor)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/vendor/bitfield)
add_subdirectory(src/ts_processor)

if(IS_TEST)
  add_subdirectory(test)
else()
  add_subdirectory(src)
endif()
