#pragma once

#include "ASTBinOperator.h"


class ASTSub : public ASTBinOperator {
public:
    ASTSub(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};

    std::string toString() const override;

    CValue evaluate(const CSheet &map) const override;

    std::shared_ptr<ASTNode> clone() const override;

};


