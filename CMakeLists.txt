cmake_minimum_required(VERSION 3.10)
project(IrrigationSystemProject)

# Locate and include Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add your source files and test files
add_executable(YourExecutable src/receive_humidity_on_sensor.c tests/your_test_files.cpp)

# Link your executable with Google Test and pthread library
target_link_libraries(YourExecutable ${GTEST_BOTH_LIBRARIES} pthread)

