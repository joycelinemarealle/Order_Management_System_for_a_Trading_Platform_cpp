cmake_minimum_required(VERSION 3.14)

# Set project name
project(OrderManagementSystem)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SRC_FILES
        src/main.cpp
        src/Order.cpp
        src/OrderManager.cpp
)

# Create the executable
add_executable(OrderManagementSystem ${SRC_FILES})

# -------- GoogleTest Setup ----------
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# For Mac ARM64 compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test files
add_executable(UnitTests
        tests/OrderTest.cpp
        tests/OrderManagerTest.cpp
        src/Order.cpp
        src/OrderManager.cpp
)

target_link_libraries(UnitTests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(UnitTests)