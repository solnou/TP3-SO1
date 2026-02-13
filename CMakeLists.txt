cmake_minimum_required(VERSION 3.10)

# Set the project name
project(memory VERSION 1.0.0 DESCRIPTION "Management of memory" LANGUAGES C)

# Include directories
include_directories(include)

# Add Conan toolchain
include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

# Find packages
find_package(unity REQUIRED)

# Include directories
include_directories(${UNITY_INCLUDE_DIRS} include)

# Add the source files
add_library(memory_lib STATIC
    ${CMAKE_SOURCE_DIR}/lib/memory/src/memory.c
    ${CMAKE_SOURCE_DIR}/lib/memory/include/memory.h
)

# Add the executable for the main program
add_executable(memory_manager
    ${CMAKE_SOURCE_DIR}/lib/memory/src/memory.c
    ${CMAKE_SOURCE_DIR}/main.c
)

# Link the library and dependencies to the executable
target_link_libraries(memory_manager PRIVATE memory_lib unity::unity m)

# Set C standard
set_target_properties(memory_lib PROPERTIES
    C_STANDARD 17
)

# Enable testing
enable_testing()

# Add subdirectory for tests
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/memory/tests)
