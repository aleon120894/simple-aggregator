cmake_minimum_required(VERSION 3.10)
    project(simple_aggregator)

    # Check for g++
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "C++ Compiler is GNU (g++)")
    # Optionally, set compiler flags specifically for g++
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "C++ Compiler is Clang")
    #  Add  Clang specific flags if needed
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed")
    else()
    message(WARNING "C++ Compiler is not GNU (g++) or Clang, it is: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "C++ Compiler Path: ${CMAKE_CXX_COMPILER}")
    endif()

    # Set C++ standard
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Create a library for the core functionality
    add_library(aggregator_lib STATIC
        src/utils.cpp
        src/newsfetcher.cpp
        src/newsitem.cpp
        src/newsdisplay.cpp
        src/newsfilter.cpp
    )

    include_directories(include)
    target_include_directories(aggregator_lib PUBLIC include)

    # Add executable
    add_executable(simple_aggregator src/main.cpp)
    target_link_libraries(simple_aggregator aggregator_lib)

    # Optional: Add compiler flags
    if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        target_compile_options(aggregator_lib PRIVATE -Wall -Wextra -Wpedantic)
        target_compile_options(simple_aggregator PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    # Disable ASan by commenting out these lines:
    if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
       target_compile_options(aggregator_lib PRIVATE -fsanitize=address)
       target_link_options(aggregator_lib PRIVATE -fsanitize=address)
       target_compile_options(news_aggregator PRIVATE -fsanitize=address)
       target_link_options(news_aggregator PRIVATE -fsanitize=address)
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed")
