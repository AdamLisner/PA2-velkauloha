#pragma once

#include "AST.h"


class ASTUnOperator : public ASTNode {
public:
    ASTUnOperator(ANode child) : m_Child(std::move(child)) {};

    void moveRelative(std::pair<size_t, size_t> offset) override;

    bool checkCycle(COpenNodes &openNodes, const CSheet &map) const override;
protected:
    ANode m_Child;
};


