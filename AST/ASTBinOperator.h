//
// Created by adam on 29.4.24.
//

#pragma once

#include "AST.h"


class ASTBinOperator : public ASTNode {
public:

    ASTBinOperator(ANode left, ANode right) : m_Left(std::move(left)), m_Right(std::move(right)) {};

    void moveRelative(std::pair<size_t, size_t> offset) override;

    bool checkCycle(COpenNodes &openNodes, const CSheet &map) const override;


protected:
    ANode m_Left;
    ANode m_Right;
};


