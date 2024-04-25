cmake_minimum_required(VERSION 3.10)
project(VelkaUloha)

set(CMAKE_CXX_STANDARD 20)

# Add your source files
set(SOURCES
        test.cpp
        ASTBuilder.cpp
        AST.cpp
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Linker options
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/x86_64-linux-gnu)

# Add executable
add_executable(VelkaUloha ${SOURCES})

# Link against the library
target_link_libraries(VelkaUloha PRIVATE expression_parser)
