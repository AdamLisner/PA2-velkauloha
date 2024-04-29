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
            const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const override;

    bool checkCycle(std::unordered_set<std::pair<size_t, size_t>, hash_pair> &openNodes,
                    std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const override;

protected:
private:
    CValue m_Val;
};