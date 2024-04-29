#include "ASTNodeReference.h"

CValue ASTNodeReference::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
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
    result += CPos::intToPos(m_Coor.first);
    return result + (m_AbsRow ? "$" : "") + std::to_string(m_Coor.second);
}

std::shared_ptr<ASTNode> ASTNodeReference::clone() const {
    ASTNodeReference node = *this;
    return std::make_shared<ASTNodeReference>(node);
}

bool ASTNodeReference::checkCycle(std::unordered_set<std::pair<size_t, size_t>, hash_pair> &openNodes,
                                  std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    if (openNodes.contains(this->m_Coor)) return true;
    openNodes.insert(this->m_Coor);
    ANode a;
    if (!map.contains(this->m_Coor)) return false;
    a = map[this->m_Coor];
    if (a->checkCycle(openNodes, map)) return true;
    openNodes.erase(this->m_Coor);
    return false;
}
