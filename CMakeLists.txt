cmake_minimum_required(VERSION 3.10)
project(VelkaUloha)

set(CMAKE_CXX_STANDARD 20)

# Add your source files
set(SOURCES
        test.cpp
        AST/ASTBuilder.cpp
        AST/ASTUnOperator.cpp
        AST/ASTBinOperator.cpp
        AST/ASTNodeValue.cpp
        AST/ASTAdd.cpp
        AST/ASTSub.cpp
        AST/ASTDiv.cpp
        AST/ASTMul.cpp
        AST/ASTEq.cpp
        AST/ASTNe.cpp
        AST/ASTLe.cpp
        AST/ASTGe.cpp
        AST/ASTNodeReference.cpp
        AST/ASTPow.cpp
        AST/ASTGt.cpp
        AST/ASTLt.cpp
        AST/ASTNeg.cpp
        CSpreadsheet.cpp
        CPos.cpp
        CPos.h
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Linker options
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/x86_64-linux-gnu)

# Add executable
add_executable(VelkaUloha ${SOURCES})

# Link against the library
target_link_libraries(VelkaUloha PRIVATE expression_parser)
