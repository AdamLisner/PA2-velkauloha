#include "ASTLe.h"


CValue ASTLe::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    CValue leftValue = m_Left->evaluate(map);
    CValue rightValue = m_Right->evaluate(map);

    if (leftValue.index() != rightValue.index()) {
        return std::monostate();
    }

    if (std::holds_alternative<double>(leftValue)) {
        return (std::get<double>(leftValue) <= std::get<double>(rightValue)) ? 1.0 : 0.0;
    } else if (std::holds_alternative<std::string>(leftValue)) {
        return std::get<std::string>(leftValue) <= std::get<std::string>(rightValue) ? 1.0 : 0.0;
    }

    return std::monostate();
}

std::string ASTLe::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += "<=";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTLe::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTLe node(left, right);
    return std::make_shared<ASTLe>(node);
}