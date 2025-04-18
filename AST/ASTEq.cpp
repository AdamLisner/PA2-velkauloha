#include "ASTEq.h"

CValue ASTEq::evaluate(const CSheet &map) const {
    CValue leftValue = m_Left->evaluate(map);
    CValue rightValue = m_Right->evaluate(map);

    if (leftValue.index() != rightValue.index()) {
        return std::monostate();
    }

    if (std::holds_alternative<double>(leftValue)) {
        return (std::get<double>(leftValue) == std::get<double>(rightValue)) ? 1.0 : 0.0;
    } else if (std::holds_alternative<std::string>(leftValue)) {
        return std::get<std::string>(leftValue) == std::get<std::string>(rightValue) ? 1.0 : 0.0;
    }

    return std::monostate();

}

std::string ASTEq::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += "==";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTEq::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTEq node(left, right);
    return std::make_shared<ASTEq>(node);
}