//
// Created by adam on 29.4.24.
//

#pragma once

#include "ASTBinOperator.h"


class ASTDiv : public ASTBinOperator {
public:
    ASTDiv(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};

    std::string toString() const override;

    CValue evaluate(
            const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const override;

    std::shared_ptr<ASTNode> clone() const override;
};


