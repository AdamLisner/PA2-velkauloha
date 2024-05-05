#pragma once

#include "AST.h"


class ASTNodeValue : public ASTNode {
public:
    ASTNodeValue() : m_Val(std::monostate()) {};

    ASTNodeValue(CValue c) : m_Val(std::move(c)) {};

    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    void moveRelative(std::pair<size_t, size_t> offset) override {};

    CValue evaluate(
            const CSheet &map) const override;

    bool checkCycle(COpenNodes &openNodes, const CSheet &map) const override {
        return false; // entered leaf, no cycle can happen
    };

protected:
private:
    CValue m_Val;
};