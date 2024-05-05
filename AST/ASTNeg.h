//
// Created by adam on 29.4.24.
//

#pragma once

#include "ASTUnOperator.h"

class ASTNeg : public ASTUnOperator {
public:
    CValue evaluate(const CSheet &map) const override;

    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    ASTNeg(ANode child) : ASTUnOperator(std::move(child)) {};
};


