#include "ASTSub.h"

CValue ASTSub::evaluate(const CSheet &map) const {
    CValue leftVal = m_Left->evaluate(map);
    CValue rightVal = m_Right->evaluate(map);

    if (std::holds_alternative<double>(leftVal) && std::holds_alternative<double>(rightVal)) {
        double result = std::get<double>(leftVal) - std::get<double>(rightVal);
        return result;
    } else {
        return std::monostate();
    }
}

std::string ASTSub::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += "-";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTSub::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTSub node(left, right);
    return std::make_shared<ASTSub>(node);
}