#pragma once

#include "AST.h"

class ASTNodeReference : public ASTNode {
public:
    ASTNodeReference(bool aCol, bool aRow, const std::pair<size_t, size_t> &coor) : m_AbsCol(aCol), m_AbsRow(aRow),
                                                                                    m_Coor(coor) {};

    void moveRelative(std::pair<size_t, size_t> offset) override;

    CValue evaluate(const CSheet &map) const override;

    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    bool checkCycle(COpenNodes &openNodes, const CSheet &map) const override;


private:
    bool m_AbsCol = false;
    bool m_AbsRow = false;
    std::pair<size_t, size_t> m_Coor;
};