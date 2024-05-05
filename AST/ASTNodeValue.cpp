#include "ASTNodeValue.h"

CValue ASTNodeValue::evaluate(
        const CSheet &map) const {
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
                result += '\"'; // '\"' need to be doubled to make sure that parser does its job
                                // e.g. "=\"ahoj \"\" ahoj\"" → ahoj " ahoj
        }
        result = "\"" + result;
        result += "\"";
        return result;

    }
    return "1/0"; // if the value is undefined, use e.g. this since it ensures that the cell will hold undefined value

}

std::shared_ptr<ASTNode> ASTNodeValue::clone() const {
    ASTNodeValue node(this->m_Val);
    return std::make_shared<ASTNodeValue>(node);
}
