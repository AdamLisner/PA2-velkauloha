#include "AST.h"
#include "CPos.h"

using CValue = std::variant<std::monostate, double, std::string>;

// ASTNodeDouble implementation
CValue ASTNodeValue::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    // Implement evaluation logic for double node
    return m_Val;
}

std::string ASTNodeValue::toString() const {
    if (std::holds_alternative<double>(m_Val)) {
        return std::to_string(std::get<double>(m_Val));
    } else if (std::holds_alternative<std::string>(m_Val)) {
        std::string value = std::get<std::string>(m_Val);
        std::string result = "";
        for(char c : value) {
            result += c;
            if(c == '\"')
                result += '\"';
        }
        result = "\"" + result;
        result += "\"";
        return result;

    }
    return "1/0";

}

std::shared_ptr<ASTNode> ASTNodeValue::clone() const {
    ASTNodeValue node(this->m_Val);
    return std::make_shared<ASTNodeValue>(node);
}

CValue
ASTAdd::evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    // Evaluate left and right operands
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

// ASTSub implementation
CValue ASTSub::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    // Evaluate left and right operands
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

// ASTDiv implementation
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

// ASTMul implementation
CValue ASTMul::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
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

// ASTPow implementation
CValue ASTPow::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    // Evaluate the base
    CValue baseValue = m_Left->evaluate(map);
    // Evaluate the exponent
    CValue exponentValue = m_Right->evaluate(map);

    // Check if both base and exponent are doubles
    if (std::holds_alternative<double>(baseValue) && std::holds_alternative<double>(exponentValue)) {
        double base = std::get<double>(baseValue);
        double exponent = std::get<double>(exponentValue);

        // Perform exponentiation and return the result
        return std::pow(base, exponent);
    } else {
        // If any operand is not a double, return std::monostate() (invalid operation)
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

CValue ASTEq::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    // Evaluate the left and right operands
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

CValue ASTNe::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    CValue leftValue = m_Left->evaluate(map);
    CValue rightValue = m_Right->evaluate(map);

    if (leftValue.index() != rightValue.index()) {
        return std::monostate();
    }

    if (std::holds_alternative<double>(leftValue)) {
        return (std::get<double>(leftValue) != std::get<double>(rightValue)) ? 1.0 : 0.0;
    } else if (std::holds_alternative<std::string>(leftValue)) {
        return std::get<std::string>(leftValue) != std::get<std::string>(rightValue) ? 1.0 : 0.0;
    }

    return std::monostate();
}

std::string ASTNe::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += "!=";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTNe::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTNe node(left, right);
    return std::make_shared<ASTNe>(node);
}

CValue ASTLt::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    CValue leftValue = m_Left->evaluate(map);
    CValue rightValue = m_Right->evaluate(map);

    if (leftValue.index() != rightValue.index()) {
        return std::monostate();
    }

    if (std::holds_alternative<double>(leftValue)) {
        return (std::get<double>(leftValue) < std::get<double>(rightValue)) ? 1.0 : 0.0;
    } else if (std::holds_alternative<std::string>(leftValue)) {
        return std::get<std::string>(leftValue) < std::get<std::string>(rightValue) ? 1.0 : 0.0;
    }

    return std::monostate();
}

std::string ASTLt::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += "<";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTLt::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTLt node(left, right);
    return std::make_shared<ASTLt>(node);
}

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

CValue ASTGt::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    CValue leftValue = m_Left->evaluate(map);
    CValue rightValue = m_Right->evaluate(map);

    if (leftValue.index() != rightValue.index()) {
        return std::monostate();
    }

    if (std::holds_alternative<double>(leftValue)) {
        return (std::get<double>(leftValue) > std::get<double>(rightValue)) ? 1.0 : 0.0;
    } else if (std::holds_alternative<std::string>(leftValue)) {
        return std::get<std::string>(leftValue) > std::get<std::string>(rightValue) ? 1.0 : 0.0;
    }

    return std::monostate();
}

std::string ASTGt::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += ">";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTGt::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTGt node(left, right);
    return std::make_shared<ASTGt>(node);
}

CValue ASTGe::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    CValue leftValue = m_Left->evaluate(map);
    CValue rightValue = m_Right->evaluate(map);

    if (leftValue.index() != rightValue.index()) {
        return std::monostate();
    }

    if (std::holds_alternative<double>(leftValue)) {
        return (std::get<double>(leftValue) >= std::get<double>(rightValue)) ? 1.0 : 0.0;
    } else if (std::holds_alternative<std::string>(leftValue)) {
        return std::get<std::string>(leftValue) >= std::get<std::string>(rightValue) ? 1.0 : 0.0;
    }

    return std::monostate();
}

std::string ASTGe::toString() const {
    std::string s;
    s += "(";
    s += m_Left->toString();
    s += ">=";
    s += m_Right->toString();
    s += ")";
    return s;
}

std::shared_ptr<ASTNode> ASTGe::clone() const {
    ANode left = this->m_Left->clone();
    ANode right = this->m_Right->clone();
    ASTGe node(left, right);
    return std::make_shared<ASTGe>(node);
}

CValue ASTNodeReference::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    std::shared_ptr<ASTNode> a;
    try {
        a = map.at(this->m_Coor);
    } catch (const std::out_of_range &o) {
        return std::monostate();
    }
    return a->evaluate(map);

}

void ASTNodeReference::moveRelative(std::pair<size_t, size_t> offset) {
    if (m_AbsCol && m_AbsRow) return;

    auto tmp = *this;

    if (!tmp.m_AbsRow) {
        tmp.m_Coor.second += offset.second;
    }

    if (!tmp.m_AbsCol) {
        tmp.m_Coor.first += offset.first;
    }

    *this = tmp;
}

std::string ASTNodeReference::toString() const {
    std::string result = m_AbsCol ? "$" : "";
    result += CPos::intToPos(m_Coor.first);
    return result + (m_AbsRow ? "$" : "") + std::to_string(m_Coor.second);
}

std::shared_ptr<ASTNode> ASTNodeReference::clone() const {
    ASTNodeReference node = *this;
    return std::make_shared<ASTNodeReference>(node);
}

void ASTUnOperator::moveRelative(std::pair<size_t, size_t> offset) {
    m_Child->moveRelative(offset);
}

void ASTBinOperator::moveRelative(std::pair<size_t, size_t> offset) {
    m_Left->moveRelative(offset);
    m_Right->moveRelative(offset);
}


