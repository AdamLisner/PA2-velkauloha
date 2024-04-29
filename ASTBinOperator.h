//
// Created by adam on 29.4.24.
//

#pragma once

#include "AST.h"


class ASTBinOperator : public ASTNode {
public:
    ASTBinOperator(ANode left, ANode right) : m_Left(std::move(left)), m_Right(std::move(right)) {};

    void moveRelative(std::pair<size_t, size_t> offset) override;

    virtual std::string toString() const = 0;

    bool checkCycle(std::unordered_set<std::pair<size_t, size_t>, hash_pair> &openNodes,
                    std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const override;

    virtual std::shared_ptr<ASTNode> clone() const = 0;


protected:
    ANode m_Left;
    ANode m_Right;
};


