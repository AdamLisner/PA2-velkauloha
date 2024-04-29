//
// Created by adam on 29.4.24.
//

#include "ASTAdd.h"

CValue
ASTAdd::evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    CValue leftVal = m_Left->evaluate(map);
    CValue rightVal = m_Right->evaluate(map);

    if (std::holds_alternative<double>(leftVal) && std::holds_alternative<double>(rightVal)) {
        double result = std::get<double>(leftVal) + std::get<double>(rightVal);
        return result;
    } else if (std::holds_alternative<std::string>(leftVal) && std::holds_alternative<std::string>(rightVal)) {
        std::string result = std::get<std::string>(leftVal) + std::get<std::string>(rightVal);
        return result;
    } else if (std::holds_alternative<std::string>(leftVal) || std::holds_alternative<std::string>(rightVal)) {
        std::string result;
        if (std::holds_alternative<std::string>(leftVal)) {
            result = std::get<std::string>(leftVal) + std::to_string(std::get<double>(rightVal));
        } else {
            result = std::to_string(std::get<double>(leftVal)) + std::get<std::string>(rightVal);
        }
        return result;
    } else {
        return std::monostate();
    }
}

std::string ASTAdd::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += "+";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTAdd::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTAdd node(left, right);
    return std::make_shared<ASTAdd>(node);
}
