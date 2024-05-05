#include "ASTUnOperator.h"

void ASTUnOperator::moveRelative(std::pair<size_t, size_t> offset) {
    m_Child->moveRelative(offset);
}

bool ASTUnOperator::checkCycle(COpenNodes &openNodes, const CSheet &map) const {
    return m_Child->checkCycle(openNodes, map);
}
