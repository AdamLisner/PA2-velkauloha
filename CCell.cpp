//
// Created by adam on 23.4.24.
//
#include "cstdlib"
#include "ASTBuilder.h"
#include "AST.h"
class CCell {
public:
    // Constructor that takes a string argument
    CCell(std::string  contents) : m_Contents(std::move(contents)) {}

    // Default constructor
    CCell() = default;

private:
    std::string m_Contents;
    std::shared_ptr<ASTNode> root;
};
