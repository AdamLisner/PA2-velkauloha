#pragma once
#include "AST.h"

class ASTNodeReference : public ASTNode {
public:
    ASTNodeReference(bool aCol, bool aRow, const std::pair<size_t, size_t> &coor) : m_AbsCol(aCol), m_AbsRow(aRow),
                                                                                    m_Coor(coor) {};

    void moveRelative(std::pair<size_t, size_t> offset) override;

    CValue evaluate(
            const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const override;

    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    bool checkCycle(std::unordered_set<std::pair<size_t, size_t>, hash_pair> &openNodes,
                    std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const override;


private:
    bool m_AbsCol = false;
    bool m_AbsRow = false;
    std::pair<size_t, size_t> m_Coor;
};