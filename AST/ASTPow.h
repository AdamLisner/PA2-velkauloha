//
// Created by adam on 29.4.24.
//

#pragma once

#include "ASTBinOperator.h"


class ASTPow : public ASTBinOperator {
public:
    CValue evaluate(const CSheet &map) const override;

    std::shared_ptr<ASTNode> clone() const override;

    std::string toString() const override;

    ASTPow(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};


