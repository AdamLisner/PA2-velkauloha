#include "ASTNeg.h"

CValue ASTNeg::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    CValue child = m_Child->evaluate(map);
    if (std::holds_alternative<double>(child)) {
        return -1 * std::get<double>(child);
    }
    return std::monostate();
}

std::string ASTNeg::toString() const {
    std::string s;
    s += "(-";
    s += m_Child->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTNeg::clone() const {
    ANode child = this->m_Child->clone();
    ASTNeg node(child);
    return std::make_shared<ASTNeg>(node);
}
