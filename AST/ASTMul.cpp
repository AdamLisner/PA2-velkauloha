#include "ASTMul.h"

CValue ASTMul::evaluate(const CSheet &map) const {
    CValue left = m_Left->evaluate(map);
    if (!std::holds_alternative<double>(left))
        return std::monostate();
    CValue right = m_Right->evaluate(map);
    if (!std::holds_alternative<double>(right))
        return std::monostate();
    return std::get<double>(left) * std::get<double>(right);
}

std::string ASTMul::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += "*";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTMul::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTMul node(left, right);
    return std::make_shared<ASTMul>(node);
}