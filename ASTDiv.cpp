#include "ASTDiv.h"

CValue ASTDiv::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    CValue divisor = m_Right->evaluate(map);

    if (std::holds_alternative<double>(divisor)) {
        double divisorValue = std::get<double>(divisor);
        if (divisorValue == 0.0) {
            return std::monostate();
        } else {
            CValue dividend = m_Left->evaluate(map);
            if (std::holds_alternative<double>(dividend)) {
                double dividendValue = std::get<double>(dividend);
                return dividendValue / divisorValue;
            } else {
                return std::monostate();
            }
        }
    } else {
        return std::monostate();
    }
}

std::string ASTDiv::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += "/";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTDiv::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTDiv node(left, right);
    return std::make_shared<ASTDiv>(node);
}