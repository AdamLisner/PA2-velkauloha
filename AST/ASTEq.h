//
// Created by adam on 29.4.24.
//

#pragma once

#include "ASTBinOperator.h"


class ASTEq : public ASTBinOperator {
public:
    CValue evaluate(const CSheet &sheet) const override;

    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    ASTEq(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};



