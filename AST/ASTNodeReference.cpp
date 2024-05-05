#include "ASTNodeReference.h"

CValue ASTNodeReference::evaluate(const CSheet &map) const {
    std::shared_ptr<ASTNode> a;
    try {
        a = map.at(this->m_Coor);
    } catch (const std::out_of_range &o) {
        return std::monostate();
    }
    return a->evaluate(map);

}

void ASTNodeReference::moveRelative(std::pair<size_t, size_t> offset) {
    if (m_AbsCol && m_AbsRow) return;

    auto tmp = *this;

    if (!tmp.m_AbsRow) {
        tmp.m_Coor.second += offset.second;
    }

    if (!tmp.m_AbsCol) {
        tmp.m_Coor.first += offset.first;
    }

    *this = tmp;
}

std::string ASTNodeReference::toString() const {
    std::string result = m_AbsCol ? "$" : "";
    result += CPos::intToCol(m_Coor.first);
    return result + (m_AbsRow ? "$" : "") + std::to_string(m_Coor.second);
}

std::shared_ptr<ASTNode> ASTNodeReference::clone() const {
    ASTNodeReference node = *this;
    return std::make_shared<ASTNodeReference>(node);
}

bool ASTNodeReference::checkCycle(COpenNodes &openNodes, const CSheet &map) const {

    if (openNodes.contains(this->m_Coor))
        return true; // entered a node, that has been entered and not closed → found a cycle

    openNodes.insert(this->m_Coor);

    if (!map.contains(this->m_Coor)) { // entered a node, that is not in the spreadsheet, no cycle can happen
        return false;
    }

    ANode a;
    a = map.at(this->m_Coor);

    if (a->checkCycle(openNodes, map))
        return true;

    openNodes.erase(this->m_Coor); // returning from recursive call, "pop" this node

    return false;
}
