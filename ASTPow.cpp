#include "ASTPow.h"

CValue ASTPow::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    CValue baseValue = m_Left->evaluate(map);
    CValue exponentValue = m_Right->evaluate(map);

    if (std::holds_alternative<double>(baseValue) && std::holds_alternative<double>(exponentValue)) {
        double base = std::get<double>(baseValue);
        double exponent = std::get<double>(exponentValue);
        return std::pow(base, exponent);
    } else {
        return std::monostate();
    }
}

std::string ASTPow::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += "^";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTPow::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTPow node(left, right);
    return std::make_shared<ASTPow>(node);
}