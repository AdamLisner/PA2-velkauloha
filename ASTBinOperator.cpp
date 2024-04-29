#include "ASTBinOperator.h"

void ASTBinOperator::moveRelative(std::pair<size_t, size_t> offset) {
    m_Left->moveRelative(offset);
    m_Right->moveRelative(offset);
}

bool ASTBinOperator::checkCycle(std::unordered_set<std::pair<size_t, size_t>, hash_pair> &openNodes,
                                std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    return m_Left->checkCycle(openNodes, map) || m_Right->checkCycle(openNodes, map);
}