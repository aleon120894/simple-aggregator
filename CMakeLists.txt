cmake_minimum_required(VERSION 3.10)
project(simple_aggregator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a library for the core functionality
add_library(aggregator_lib STATIC
    src/utils.cpp
)


target_include_directories(aggregator_lib
    PUBLIC
    include
)

# Add executable
add_executable(simple_aggregator src/main.cpp)

# Link the executable to the library
target_link_libraries(simple_aggregator aggregator_lib)

# Optional: Add compiler flags for stricter warnings (good practice)
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(aggregator_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(simple_aggregator PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Enable address sanitizer for debugging (if available)
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(aggregator_lib PRIVATE -fsanitize=address)
    target_link_options(aggregator_lib PRIVATE -fsanitize=address)
    target_compile_options(news_aggregator PRIVATE -fsanitize=address)
    target_link_options(news_aggregator PRIVATE -fsanitize=address)
endif()