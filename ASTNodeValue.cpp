#include "ASTNodeValue.h"

CValue ASTNodeValue::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    return m_Val;
}

std::string ASTNodeValue::toString() const {
    if (std::holds_alternative<double>(m_Val)) {
        return std::to_string(std::get<double>(m_Val));
    } else if (std::holds_alternative<std::string>(m_Val)) {
        std::string value = std::get<std::string>(m_Val);
        std::string result;
        for (char c: value) {
            result += c;
            if (c == '\"')
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

bool ASTNodeValue::checkCycle(std::unordered_set<std::pair<size_t, size_t>, hash_pair> &openNodes,
                              std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map) const {
    return false;
}