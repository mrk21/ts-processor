find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/test)
include_directories(${PROJECT_SOURCE_DIR}/vendor/bandit)
include_directories(${PROJECT_SOURCE_DIR}/vendor/bandit_with_gmock)
include_directories(${PROJECT_SOURCE_DIR}/vendor/googlemock/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/googlemock/gtest/include)

link_directories(${PROJECT_SOURCE_DIR}/vendor/googlemock)
link_directories(${PROJECT_SOURCE_DIR}/vendor/googlemock/gtest)

file(GLOB_RECURSE SRCS "spec/*_spec.cpp")
add_executable(spec spec.cpp ${SRCS})

target_link_libraries(spec ${LIB_NAME} pthread gtest gmock)
