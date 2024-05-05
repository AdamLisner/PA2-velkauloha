//
// Created by adam on 29.4.24.
//

#pragma once

#include "ASTBinOperator.h"


class ASTAdd : public ASTBinOperator {
public:
    ASTAdd(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};

    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    CValue evaluate(const CSheet &map) const override;
};


