#include "ASTUnOperator.h"

void ASTUnOperator::moveRelative(std::pair<size_t, size_t> offset) {
    m_Child->moveRelative(offset);
}

bool ASTUnOperator::checkCycle(std::unordered_set<std::pair<size_t, size_t>, hash_pair> &openNodes,
                               std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    return m_Child->checkCycle(openNodes, map);
}
