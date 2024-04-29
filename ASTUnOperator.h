#pragma once
#include "AST.h"


class ASTUnOperator : public ASTNode {
public:

    ASTUnOperator(ANode child) : m_Child(std::move(child)) {};

    void moveRelative(std::pair<size_t, size_t> offset) override;

    virtual std::string toString() const = 0;

    bool checkCycle(std::unordered_set<std::pair<size_t, size_t>, hash_pair> &openNodes,
                    std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const override;

    virtual std::shared_ptr<ASTNode> clone() const = 0;

protected:
    ANode m_Child;
};


