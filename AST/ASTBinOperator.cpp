#include "ASTBinOperator.h"

void ASTBinOperator::moveRelative(std::pair<size_t, size_t> offset) {
    m_Left->moveRelative(offset);
    m_Right->moveRelative(offset);
}

bool ASTBinOperator::checkCycle(COpenNodes &openNodes, const CSheet &map) const {
    return m_Left->checkCycle(openNodes, map) || m_Right->checkCycle(openNodes, map);
}