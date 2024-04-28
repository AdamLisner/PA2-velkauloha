#ifndef __PROGTEST__

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>
#include "expression.h"


using namespace std::literals;
using CValue = std::variant<std::monostate, double, std::string>;

constexpr unsigned SPREADSHEET_CYCLIC_DEPS = 0x01;
constexpr unsigned SPREADSHEET_FUNCTIONS = 0x02;
constexpr unsigned SPREADSHEET_FILE_IO = 0x04;
constexpr unsigned SPREADSHEET_SPEED = 0x08;
constexpr unsigned SPREADSHEET_PARSER = 0x10;
#endif /* __PROGTEST__ */


struct hash_pair {
    std::size_t operator () (const std::pair<size_t, size_t>& p) const {
        return (p.first + 0x9e3779b9 + (p.first >> 6) + (p.first << 8))^(p.second + 0x9e3779b9 + (p.second << 7) + (p.second >> 3));
    }
};

class CPos {
public:

    static std::pair<size_t, size_t> strToPair(const std::string &str);

    CPos(const std::string &pos) : m_Pos(strToPair(pos)) {};
    CPos(size_t col, size_t row) : m_Pos(std::make_pair(col,row)){};

    std::pair<size_t, size_t> getPos() const {
        return m_Pos;
    }

    static std::string intToPos(size_t i) {
        std::string result;
        while (i > 0) {
            size_t remainder = i % 26;
            char letter = 'A' - 1 + remainder;
            result = letter + result;
            i = (i - remainder) / 26;
        }
        return result;
    }

private:
    std::pair<size_t, size_t> m_Pos;
};


std::pair<size_t, size_t> CPos::strToPair(const std::string &str) {

    std::string pos;

    size_t col = 0;
    size_t row = 0;
    size_t i = 0;
    int mul = 26;
    for (; !isdigit(str[i]); i++) {
        char c = (toupper)(str[i]);
        if (c < 'A' || c > 'Z') {
            throw std::invalid_argument("invalid argument passed");
        }
        col *= mul;
        col += c - 'A' + 1;
    }

    for (; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') {
            throw std::invalid_argument("invalid argument passed");
        }
        row *= 10;
        row += str[i] - '0';
    }

    return std::make_pair(col, row);
}


using CValue = std::variant<std::monostate, double, std::string>;
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void moveRelative(std::pair<size_t,size_t> offset) = 0;
    virtual CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map, const std::pair<size_t,size_t>& pos) const = 0;
    virtual std::string toString() const = 0;
    virtual std::shared_ptr<ASTNode> clone() const = 0;
protected:
private:
};


class ASTNodeValue : public ASTNode {
public:
    ASTNodeValue() : m_Val(std::monostate()) {};

    ASTNodeValue(CValue c) : m_Val(std::move(c)) {};

    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    void moveRelative(std::pair<size_t, size_t> offset) override{

    };

    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map,const std::pair<size_t,size_t>& pos) const override;

protected:
private:
    CValue m_Val;
};


using ANode = std::shared_ptr<ASTNode>;

class ASTNodeReference : public ASTNode {
public:
    ASTNodeReference(bool aCol, bool aRow, const std::pair<size_t,size_t> &coor):m_AbsCol(aCol),m_AbsRow(aRow),m_Coor(coor){};
    void moveRelative(std::pair<size_t, size_t> offset) override;
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map, const std::pair<size_t,size_t>& pos) const override;
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

private:
    bool m_AbsCol = false;
    bool m_AbsRow = false;
    std::pair<size_t,size_t> m_Coor;
};

class ASTBinOperator : public ASTNode {
public:
    ASTBinOperator(ANode left, ANode right) : m_Left(std::move(left)), m_Right(std::move(right)) {};
    void moveRelative(std::pair<size_t, size_t> offset) override;
    virtual std::string toString() const = 0;

    virtual std::shared_ptr<ASTNode> clone() const = 0;

protected:
    ANode m_Left;
    ANode m_Right;
};


class ASTAdd : public ASTBinOperator {
public:
    ASTAdd(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map, const std::pair<size_t,size_t>& pos) const override;
};

class ASTSub : public ASTBinOperator {
public:
    ASTSub(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
    std::string toString() const override;
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map, const std::pair<size_t,size_t>& pos) const override;

    std::shared_ptr<ASTNode> clone() const override;

};

class ASTDiv : public ASTBinOperator {
public:
    ASTDiv(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
    std::string toString() const override;

    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map, const std::pair<size_t,size_t>& pos) const override;

    std::shared_ptr<ASTNode> clone() const override;
};

class ASTMul : public ASTBinOperator {
public:
    ASTMul(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map, const std::pair<size_t,size_t>& pos) const override;

};

class ASTPow : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map, const std::pair<size_t,size_t>& pos) const override;

    std::shared_ptr<ASTNode> clone() const override;

    std::string toString() const override;

    ASTPow(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTEq : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map,const std::pair<size_t,size_t>& pos) const override;
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    ASTEq(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTNe : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map, const std::pair<size_t,size_t>& pos) const override;
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    ASTNe(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTLt : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map,const std::pair<size_t,size_t>& pos) const override;
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    ASTLt(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTLe : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map, const std::pair<size_t,size_t>& pos) const override;
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    ASTLe(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTGt : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map,const std::pair<size_t,size_t>& pos) const override;
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    ASTGt(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTGe : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map,const std::pair<size_t,size_t>& pos) const override;
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    ASTGe(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTUnOperator : public ASTNode {
public:
    ASTUnOperator(ANode child) : m_Child(std::move(child)) {};
    void moveRelative(std::pair<size_t, size_t> offset) override;
    virtual std::string toString() const = 0;

    virtual std::shared_ptr<ASTNode> clone() const = 0;

protected:
    ANode m_Child;
};

class ASTNeg : public ASTUnOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map,const std::pair<size_t,size_t>& pos) const override;
    std::string toString() const override;

    std::shared_ptr<ASTNode> clone() const override;

    ASTNeg(ANode child) : ASTUnOperator(std::move(child)) {};
};


using CValue = std::variant<std::monostate, double, std::string>;

// ASTNodeDouble implementation
CValue ASTNodeValue::evaluate(
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    // Implement evaluation logic for double node
    return m_Val;
}

std::string ASTNodeValue::toString() const {
    if (std::holds_alternative<double>(m_Val)) {
        return std::to_string(std::get<double>(m_Val));
    } else if (std::holds_alternative<std::string>(m_Val)) {
        std::string value = std::get<std::string>(m_Val);
        std::string result = "";
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

CValue
ASTAdd::evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
                 const std::pair<size_t, size_t> &pos) const {
    // Evaluate left and right operands
    CValue leftVal = m_Left->evaluate(map,pos);
    CValue rightVal = m_Right->evaluate(map,pos);

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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    // Evaluate left and right operands
    CValue leftVal = m_Left->evaluate(map,pos);
    CValue rightVal = m_Right->evaluate(map,pos);

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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    CValue divisor = m_Right->evaluate(map,pos);

    if (std::holds_alternative<double>(divisor)) {
        double divisorValue = std::get<double>(divisor);
        if (divisorValue == 0.0) {
            return std::monostate();
        } else {
            CValue dividend = m_Left->evaluate(map,pos);
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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    CValue left = m_Left->evaluate(map,pos);
    if (!std::holds_alternative<double>(left))
        return std::monostate();
    CValue right = m_Right->evaluate(map,pos);
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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    // Evaluate the base
    CValue baseValue = m_Left->evaluate(map,pos);
    // Evaluate the exponent
    CValue exponentValue = m_Right->evaluate(map,pos);

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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    CValue child = m_Child->evaluate(map,pos);
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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    // Evaluate the left and right operands
    CValue leftValue = m_Left->evaluate(map,pos);
    CValue rightValue = m_Right->evaluate(map,pos);

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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    CValue leftValue = m_Left->evaluate(map,pos);
    CValue rightValue = m_Right->evaluate(map,pos);

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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    CValue leftValue = m_Left->evaluate(map,pos);
    CValue rightValue = m_Right->evaluate(map,pos);

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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    CValue leftValue = m_Left->evaluate(map,pos);
    CValue rightValue = m_Right->evaluate(map,pos);

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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    CValue leftValue = m_Left->evaluate(map,pos);
    CValue rightValue = m_Right->evaluate(map,pos);

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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    CValue leftValue = m_Left->evaluate(map,pos);
    CValue rightValue = m_Right->evaluate(map,pos);

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
        const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &map,
        const std::pair<size_t, size_t> &pos) const {
    if (m_Coor == pos) return CValue();
    std::shared_ptr<ASTNode> a;
    try {
        a = map.at(this->m_Coor);
    } catch (const std::out_of_range &o) {
        return std::monostate();
    }
    return a->evaluate(map, pos);

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


class ASTBuilder : public CExprBuilder {
public:

    void opAdd() override;

    void opSub() override;

    void opMul() override;

    void opDiv() override;

    void opPow() override;

    void opNeg() override;

    void opEq() override;

    void opNe() override;

    void opLt() override;

    void opLe() override;

    void opGt() override;

    void opGe() override;

    void valNumber(double val) override;

    void valString(std::string val) override;

    void valReference(std::string val) override;

    void valRange(std::string val) override;

    void funcCall(std::string fnName,
                  int paramCount) override;
    std::stack<std::shared_ptr<ASTNode>>& stack() {
        return m_Stack;
    }
private:

    std::stack<std::shared_ptr<ASTNode>> m_Stack;

};


using ANode = std::shared_ptr<ASTNode>;


void ASTBuilder::opAdd() {
    std::cout << " + ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();

    ASTAdd add(left,right);

    m_Stack.push(std::make_shared<ASTAdd>(add));
}

void ASTBuilder::opSub() {
    std::cout << " - ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTSub sub(left,right);
    m_Stack.push(std::make_shared<ASTSub>(sub));
}

void ASTBuilder::opMul() {
    std::cout << " * ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTMul mul(left,right);
    m_Stack.push(std::make_shared<ASTMul>(mul));
}

void ASTBuilder::opDiv() {
    std::cout << " / ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTDiv div(left,right);
    m_Stack.push(std::make_shared<ASTDiv>(div));
}

void ASTBuilder::opPow() {
    //ASTPow pow;
    std::cout << " ^ ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTPow pow(left,right);
    m_Stack.push(std::make_shared<ASTPow>(pow));
}

void ASTBuilder::opNeg() {
    std::cout << " - ";
    ANode child = m_Stack.top();
    m_Stack.pop();
    ASTNeg minus(child);
    m_Stack.push(std::make_shared<ASTNeg>(minus));

    // Implementation for negation operator
}

void ASTBuilder::opEq() {
    std::cout << " == ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTEq eq(left,right);
    m_Stack.push(std::make_shared<ASTEq>(eq));
    // Implementation for equality operator
}

void ASTBuilder::opNe() {
    std::cout << " != ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTNe ne(left,right);
    m_Stack.push(std::make_shared<ASTNe>(ne));
    // Implementation for inequality operator
}

void ASTBuilder::opLt() {
    std::cout << " < ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTLt lt(left,right);
    m_Stack.push(std::make_shared<ASTLt>(lt));
    // Implementation for less than operator
}

void ASTBuilder::opLe() {
    std::cout << " <= ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTLe le(left,right);
    m_Stack.push(std::make_shared<ASTLe>(le));
    // Implementation for less than or equal to operator
}

void ASTBuilder::opGt() {
    std::cout << " > ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTGt gt(left,right);
    m_Stack.push(std::make_shared<ASTGt>(gt));
    // Implementation for greater than operator
}

void ASTBuilder::opGe() {
    std::cout << " >= ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTGe ge(left,right);
    m_Stack.push(std::make_shared<ASTGe>(ge));
    // Implementation for greater than or equal to operator
}

void ASTBuilder::valNumber(double val) {
    // Implementation for handling numeric value
    ASTNodeValue node(val);
    m_Stack.push(std::make_shared<ASTNodeValue>(node));
    std::cout << val;
}

void ASTBuilder::valString(std::string val) {
    // Implementation for handling string value
    ASTNodeValue node(val);
    m_Stack.push(std::make_shared<ASTNodeValue>(node));
    std::cout << val;
}

void ASTBuilder::valReference(std::string val) {
    // Implementation for handling reference value
    std::cout << " " << val << " ";
    int count = 0;
    bool absCol = false;
    bool absRow = false;
    for (char c: val) {
        if (c == '$')
            count++;
        if (count == 2) {
            absCol = absRow = true;
            break;
        }
    }
    if(count == 1 && val[0] == '$')
        absCol = true;
    else if (count == 1 && val[0] != '$')
        absRow = true;

    size_t pos = val.find('$');
    while (pos != std::string::npos) {
        val.erase(pos, 1);
        pos = val.find('$', pos);
    }
    std::pair<size_t , size_t> coor = CPos::strToPair(val);

    ASTNodeReference node(absCol,absRow,coor);

    stack().push(std::make_shared<ASTNodeReference>(node));
}

void ASTBuilder::valRange(std::string val) {
    // Implementation for handling range value
    std::cout << val;

}

void ASTBuilder::funcCall(std::string fnName, int paramCount) {
    // Implementation for function call
}


class CSpreadsheet {
public:
    static unsigned capabilities() {
        return SPREADSHEET_CYCLIC_DEPS | SPREADSHEET_FILE_IO | SPREADSHEET_SPEED;
    }

    CSpreadsheet() = default;

    bool load(std::istream &is);

    bool save(std::ostream &os) const;

    bool setCell(CPos pos,
                 std::string contents);

    CValue getValue(CPos pos);

    void copyRect(CPos dst,
                  CPos src,
                  int w = 1,
                  int h = 1);

    const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &getMSheet() const;

    friend std::ostream &operator<<(std::ostream &os, const CSpreadsheet &sheet) {
        for (const auto &key: sheet.m_Sheet) {
            std::string str = key.second->toString();
            os << "{" << key.first.first << "," << key.first.second << "," << str.length() << ",=" << str << "}";
        }
        return os;
    }

private:
    ASTBuilder builder;
    std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> m_Sheet;
};


bool CSpreadsheet::setCell(CPos pos, std::string contents) {
    try {
        parseExpression(contents, builder);
    } catch (const std::invalid_argument &ex) {
        return false;
    }
    m_Sheet[pos.getPos()] = builder.stack().top();
    builder.stack().pop();
    std::cout << std::endl;
    return true;
}

CValue CSpreadsheet::getValue(CPos pos) {
    std::shared_ptr<ASTNode> c;
    try {
        c = m_Sheet.at(pos.getPos());
    } catch (const std::out_of_range& o) {
        return std::monostate();
    }
    return c->evaluate(m_Sheet, pos.getPos());
}

bool CSpreadsheet::load(std::istream &is) {
    this->m_Sheet.clear();
    while (true) {

        size_t col, row, length;
        char open, delim, end;
        if (is.eof()) {
            return true;
        }

        if (!(is >> open && open == '{')) {
            return false;
        }
        if (is.eof()) return false;
        if (!(is >> col >> delim && delim == ',')) {
            return false;
        }
        if (is.eof()) return false;
        if (!(is >> row >> delim && delim == ',')) {
            return false;
        }
        if (is.eof()) return false;

        if (!(is >> length >> delim && delim == ',')) {
            return false;
        }
        if (is.eof()) return false;

        std::string data;
        for (size_t i = 0; i <= length; ++i) {
            char c;
            if (!(is >> std::noskipws >> c) || is.eof()) {
                return false; // Failed to read character
            }
            data += c;
        }
        if (is.eof()) return false;

        if (!(is >> end && end == '}')) {
            return false;
        }

        setCell({col, row}, data);
        is.peek();
    }
    return true;

}

bool CSpreadsheet::save(std::ostream &os) const {
    if (!os.good()) {
        std::cerr << "Error: Invalid output stream." << std::endl;
        return false;
    }
    os << *this;
    if (os.good()) {
        std::cout << "Spreadsheet saved successfully." << std::endl;
        return true;
    } else {
        std::cerr << "Error: Failed to save spreadsheet." << std::endl;
        return false;
    }
}

void CSpreadsheet::copyRect(CPos dst, CPos src, int w, int h) {
    auto dstPos = dst.getPos();
    auto srcPos = src.getPos();
    if (dstPos == srcPos) return;
    auto offset = std::make_pair(dstPos.first - srcPos.first, dstPos.second - srcPos.second);
    std::deque<std::shared_ptr<ASTNode>> treesToCopy;
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            std::shared_ptr<ASTNode> a;

            if (m_Sheet.contains({srcPos.first + i, srcPos.second + j})) {
                treesToCopy.push_back(m_Sheet[{srcPos.first + i, srcPos.second + j}]->clone());
            } else {
                treesToCopy.push_back(std::make_shared<ASTNodeValue>(CValue()));
            }
        }
    }

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            treesToCopy.front()->moveRelative(offset);
            m_Sheet[{dstPos.first + i, dstPos.second + j}] = treesToCopy.front();
            treesToCopy.pop_front();
        }
    }


}

const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>, hash_pair> &
CSpreadsheet::getMSheet() const {
    return m_Sheet;
}


#ifndef __PROGTEST__

bool valueMatch(const CValue &r,
                const CValue &s) {
    if (r.index() != s.index())
        return false;
    if (r.index() == 0)
        return true;
    if (r.index() == 2)
        return std::get<std::string>(r) == std::get<std::string>(s);
    if (std::isnan(std::get<double>(r)) && std::isnan(std::get<double>(s)))
        return true;
    if (std::isinf(std::get<double>(r)) && std::isinf(std::get<double>(s)))
        return (std::get<double>(r) < 0 && std::get<double>(s) < 0)
               || (std::get<double>(r) > 0 && std::get<double>(s) > 0);
    return fabs(std::get<double>(r) - std::get<double>(s)) <= 1e8 * DBL_EPSILON * fabs(std::get<double>(r));
}

int main() {
    /*CSpreadsheet x0, x1;
    std::ostringstream oss;
    std::istringstream iss;
    std::string data;
    assert (x0.setCell(CPos("A6"), "raw text with any characters, including a quote \" or a newline\n"));
    oss.clear();
    oss.str("");
    assert (x0.save(oss));
    data = oss.str();

    iss.str(data);
    assert (!x1.load(iss));
    assert (x0.setCell(CPos("A1"), "10"));
    assert (x0.setCell(CPos("A2"), "20.5"));
    assert (x0.setCell(CPos("A3"), "3e1"));
    assert (x0.setCell(CPos("A4"), "=40"));
    assert (x0.setCell(CPos("A5"), "=5e+1"));
    assert (!x0.setCell(CPos("A69"), "=ahoj + negre"));
    x0.copyRect(CPos("C1"), CPos("A1"), 2, 5);
    std::cout << x0 << std::endl;
    // assert(valueMatch(x0.getValue(CPos("C1")), CValue(10.0)));

    assert (x0.setCell(CPos("A68"), "=\"ahoj \"\" ahoj\""));
    assert (valueMatch(x0.getValue(CPos("A7")), CValue()));

    assert (x0.setCell(CPos("A7"),
                       "quoted string, quotes must be doubled: \". Moreover, backslashes are needed for C++."));
    //assert (x0.setCell(CPos("A55"), "=\"ahoj\" + \"petre\""));
    //assert (valueMatch(x0.getValue(CPos("A55")), CValue()));
    assert (valueMatch(x0.getValue(CPos("A1")), CValue(10.0)));
    assert (valueMatch(x0.getValue(CPos("A2")), CValue(20.5)));
    assert (valueMatch(x0.getValue(CPos("A3")), CValue(30.0)));
    assert (valueMatch(x0.getValue(CPos("A4")), CValue(40.0)));
    assert (valueMatch(x0.getValue(CPos("A5")), CValue(50.0)));
    assert (valueMatch(x0.getValue(CPos("A6")),
                       CValue("raw text with any characters, including a quote \" or a newline\n")));
    assert (valueMatch(x0.getValue(CPos("A7")),
                       CValue("quoted string, quotes must be doubled: \". Moreover, backslashes are needed for C++.")));
    assert (valueMatch(x0.getValue(CPos("A8")), CValue()));
    assert (valueMatch(x0.getValue(CPos("AAAA9999")), CValue()));
    assert (x0.setCell(CPos("B1"), "=A1+A2*A3"));
    assert (x0.setCell(CPos("B2"), "= -A1 ^ 2 - A2 / 2   "));
    assert (x0.setCell(CPos("B3"), "= 2 ^ $A$1"));
    assert (x0.setCell(CPos("B4"), "=($A1+A$2)^2"));
    assert (x0.setCell(CPos("B5"), "=B1+B2+B3+B4"));
    assert (x0.setCell(CPos("B6"), "=B1+B2+B3+B4+B5"));
    //   x0.copyRect(CPos("A5"),CPos("B5"));

    std::cout << x0 << std::endl;

    auto i = x0.getValue(CPos("A5"));
    assert (valueMatch(x0.getValue(CPos("B1")), CValue(625.0)));
    CValue value = x0.getValue(CPos("B2"));
    assert (valueMatch(x0.getValue(CPos("B2")), CValue(-110.25)));
    assert (valueMatch(x0.getValue(CPos("B3")), CValue(1024.0)));
    assert (valueMatch(x0.getValue(CPos("B4")), CValue(930.25)));
    assert (valueMatch(x0.getValue(CPos("B5")), CValue(2469.0)));
    assert (valueMatch(x0.getValue(CPos("B6")), CValue(4938.0)));
    assert (x0.setCell(CPos("A1"), "12"));
    assert (valueMatch(x0.getValue(CPos("B1")), CValue(627.0)));
    assert (valueMatch(x0.getValue(CPos("B2")), CValue(-154.25)));
    assert (valueMatch(x0.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x0.getValue(CPos("B4")), CValue(1056.25)));
    assert (valueMatch(x0.getValue(CPos("B5")), CValue(5625.0)));
    assert (valueMatch(x0.getValue(CPos("B6")), CValue(11250.0)));
    x1 = x0;
    assert (x0.setCell(CPos("A2"), "100"));
    assert (x1.setCell(CPos("A2"), "=A3+A5+A4"));
    assert (valueMatch(x0.getValue(CPos("B1")), CValue(3012.0)));
    assert (valueMatch(x0.getValue(CPos("B2")), CValue(-194.0)));
    assert (valueMatch(x0.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x0.getValue(CPos("B4")), CValue(12544.0)));
    assert (valueMatch(x0.getValue(CPos("B5")), CValue(19458.0)));
    assert (valueMatch(x0.getValue(CPos("B6")), CValue(38916.0)));
    assert (valueMatch(x1.getValue(CPos("B1")), CValue(3612.0)));
    assert (valueMatch(x1.getValue(CPos("B2")), CValue(-204.0)));
    assert (valueMatch(x1.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x1.getValue(CPos("B4")), CValue(17424.0)));
    assert (valueMatch(x1.getValue(CPos("B5")), CValue(24928.0)));
    assert (valueMatch(x1.getValue(CPos("B6")), CValue(49856.0)));

    oss.clear();
    oss.str("");
    assert (x0.save(oss));
    data = oss.str();
    iss.clear();
    iss.str(data);
    assert (x1.load(iss));
    assert (valueMatch(x1.getValue(CPos("B1")), CValue(3012.0)));
    assert (valueMatch(x1.getValue(CPos("B2")), CValue(-194.0)));
    assert (valueMatch(x1.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x1.getValue(CPos("B4")), CValue(12544.0)));
    assert (valueMatch(x1.getValue(CPos("B5")), CValue(19458.0)));
    assert (valueMatch(x1.getValue(CPos("B6")), CValue(38916.0)));
    assert (x0.setCell(CPos("A3"), "4e1"));
    assert (valueMatch(x1.getValue(CPos("B1")), CValue(3012.0)));
    assert (valueMatch(x1.getValue(CPos("B2")), CValue(-194.0)));
    assert (valueMatch(x1.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x1.getValue(CPos("B4")), CValue(12544.0)));
    assert (valueMatch(x1.getValue(CPos("B5")), CValue(19458.0)));
    assert (valueMatch(x1.getValue(CPos("B6")), CValue(38916.0)));
    oss.clear();
    oss.str("");
    assert (x0.save(oss));
    data = oss.str();
    for (size_t i = 0; i < std::min<size_t>(data.length(), 10); i++)
        data[i] ^= 0x5a;
    iss.clear();
    iss.str(data);
    assert (!x1.load(iss));
    assert (x0.setCell(CPos("D0"), "10"));
    assert (x0.setCell(CPos("D1"), "20"));
    assert (x0.setCell(CPos("D2"), "30"));
    assert (x0.setCell(CPos("D3"), "40"));
    assert (x0.setCell(CPos("D4"), "50"));
    assert (x0.setCell(CPos("E0"), "60"));
    assert (x0.setCell(CPos("E1"), "70"));
    assert (x0.setCell(CPos("E2"), "80"));
    assert (x0.setCell(CPos("E3"), "90"));
    assert (x0.setCell(CPos("E4"), "100"));
    assert (x0.setCell(CPos("F10"), "=D0+5"));
    assert (x0.setCell(CPos("F11"), "=$D0+5"));
    assert (x0.setCell(CPos("F12"), "=D$0+5"));
    assert (x0.setCell(CPos("F13"), "=$D$0+5"));
    x0.copyRect(CPos("G11"), CPos("F10"), 1, 4);
    assert (valueMatch(x0.getValue(CPos("F10")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F11")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F12")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F13")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F14")), CValue()));
    assert (valueMatch(x0.getValue(CPos("G10")), CValue()));
    assert (valueMatch(x0.getValue(CPos("G11")), CValue(75.0)));
    assert (valueMatch(x0.getValue(CPos("G12")), CValue(25.0)));
    assert (valueMatch(x0.getValue(CPos("G13")), CValue(65.0)));
    assert (valueMatch(x0.getValue(CPos("G14")), CValue(15.0)));
    x0.copyRect(CPos("G11"), CPos("F10"), 2, 4);
    assert (valueMatch(x0.getValue(CPos("F10")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F11")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F12")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F13")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F14")), CValue()));
    assert (valueMatch(x0.getValue(CPos("G10")), CValue()));
    assert (valueMatch(x0.getValue(CPos("G11")), CValue(75.0)));
    assert (valueMatch(x0.getValue(CPos("G12")), CValue(25.0)));
    assert (valueMatch(x0.getValue(CPos("G13")), CValue(65.0)));
    assert (valueMatch(x0.getValue(CPos("G14")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("H10")), CValue()));
    assert (valueMatch(x0.getValue(CPos("H11")), CValue()));
    assert (valueMatch(x0.getValue(CPos("H12")), CValue()));
    assert (valueMatch(x0.getValue(CPos("H13")), CValue(35.0)));
    assert (valueMatch(x0.getValue(CPos("H14")), CValue()));
    assert (x0.setCell(CPos("F0"), "-27"));
    assert (valueMatch(x0.getValue(CPos("H14")), CValue(-22.0)));
    x0.copyRect(CPos("H12"), CPos("H13"), 1, 2);
    assert (valueMatch(x0.getValue(CPos("H12")), CValue(25.0)));
    assert (valueMatch(x0.getValue(CPos("H13")), CValue(-22.0)));
    assert (valueMatch(x0.getValue(CPos("H14")), CValue(-22.0)));
    return EXIT_SUCCESS;*/
    CSpreadsheet x0, x1;
    std::ostringstream oss;
    std::istringstream iss;
    std::string data;
    assert (x0.setCell(CPos("A1"), "=A2"));
    assert (x0.setCell(CPos("A2"), "=A3"));
    assert (x0.setCell(CPos("A3"), "=A4"));
    assert (x0.setCell(CPos("A4"), "=A5"));
    assert (x0.setCell(CPos("A5"), "=A6"));
    assert (x0.setCell(CPos("A6"), "=A1"));
    assert (valueMatch(x0.getValue(CPos("A1")), CValue()));
    assert (x0.setCell(CPos("A1"), "10"));
    assert (x0.setCell(CPos("A2"), "20.5"));
    assert (x0.setCell(CPos("A3"), "3e1"));
    assert (x0.setCell(CPos("A4"), "=40"));
    assert (x0.setCell(CPos("A5"), "=5e+1"));
    assert (x0.setCell(CPos("A6"), "raw text with any characters, including a quote \" or a newline\n"));
    assert (x0.setCell(CPos("A7"),
                       "=\"quoted string, quotes must be doubled: \"\". Moreover, backslashes are needed for C++.\""));
    assert (valueMatch(x0.getValue(CPos("A1")), CValue(10.0)));
    assert (valueMatch(x0.getValue(CPos("A2")), CValue(20.5)));
    assert (valueMatch(x0.getValue(CPos("A3")), CValue(30.0)));
    assert (valueMatch(x0.getValue(CPos("A4")), CValue(40.0)));
    assert (valueMatch(x0.getValue(CPos("A5")), CValue(50.0)));
    assert (valueMatch(x0.getValue(CPos("A6")),
                       CValue("raw text with any characters, including a quote \" or a newline\n")));
    assert (valueMatch(x0.getValue(CPos("A7")),
                       CValue("quoted string, quotes must be doubled: \". Moreover, backslashes are needed for C++.")));
    assert (valueMatch(x0.getValue(CPos("A8")), CValue()));
    assert (valueMatch(x0.getValue(CPos("AAAA9999")), CValue()));
    assert (x0.setCell(CPos("B1"), "=A1+A2*A3"));
    assert (x0.setCell(CPos("B2"), "= -A1 ^ 2 - A2 / 2   "));
    assert (x0.setCell(CPos("B3"), "= 2 ^ $A$1"));
    assert (x0.setCell(CPos("B4"), "=($A1+A$2)^2"));
    assert (x0.setCell(CPos("B5"), "=B1+B2+B3+B4"));
    assert (x0.setCell(CPos("B6"), "=B1+B2+B3+B4+B5"));
    assert (valueMatch(x0.getValue(CPos("B1")), CValue(625.0)));
    assert (valueMatch(x0.getValue(CPos("B2")), CValue(-110.25)));
    assert (valueMatch(x0.getValue(CPos("B3")), CValue(1024.0)));
    assert (valueMatch(x0.getValue(CPos("B4")), CValue(930.25)));
    assert (valueMatch(x0.getValue(CPos("B5")), CValue(2469.0)));
    assert (valueMatch(x0.getValue(CPos("B6")), CValue(4938.0)));
    assert (x0.setCell(CPos("A1"), "12"));
    assert (valueMatch(x0.getValue(CPos("B1")), CValue(627.0)));
    assert (valueMatch(x0.getValue(CPos("B2")), CValue(-154.25)));
    assert (valueMatch(x0.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x0.getValue(CPos("B4")), CValue(1056.25)));
    assert (valueMatch(x0.getValue(CPos("B5")), CValue(5625.0)));
    assert (valueMatch(x0.getValue(CPos("B6")), CValue(11250.0)));
    x1 = x0;
    assert (x0.setCell(CPos("A2"), "100"));
    assert (x1.setCell(CPos("A2"), "=A3+A5+A4"));
    assert (valueMatch(x0.getValue(CPos("B1")), CValue(3012.0)));
    assert (valueMatch(x0.getValue(CPos("B2")), CValue(-194.0)));
    assert (valueMatch(x0.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x0.getValue(CPos("B4")), CValue(12544.0)));
    assert (valueMatch(x0.getValue(CPos("B5")), CValue(19458.0)));
    assert (valueMatch(x0.getValue(CPos("B6")), CValue(38916.0)));
    assert (valueMatch(x1.getValue(CPos("B1")), CValue(3612.0)));
    assert (valueMatch(x1.getValue(CPos("B2")), CValue(-204.0)));
    assert (valueMatch(x1.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x1.getValue(CPos("B4")), CValue(17424.0)));
    assert (valueMatch(x1.getValue(CPos("B5")), CValue(24928.0)));
    assert (valueMatch(x1.getValue(CPos("B6")), CValue(49856.0)));
    oss.clear();
    oss.str("");
    assert (x0.save(oss));
    data = oss.str();
    iss.clear();
    iss.str(data);
    std::cout << x0 << std::endl;
    assert (x1.load(iss));
    assert (valueMatch(x1.getValue(CPos("B1")), CValue(3012.0)));
    assert (valueMatch(x1.getValue(CPos("B2")), CValue(-194.0)));
    assert (valueMatch(x1.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x1.getValue(CPos("B4")), CValue(12544.0)));
    assert (valueMatch(x1.getValue(CPos("B5")), CValue(19458.0)));
    assert (valueMatch(x1.getValue(CPos("B6")), CValue(38916.0)));
    assert (x0.setCell(CPos("A3"), "4e1"));
    assert (valueMatch(x1.getValue(CPos("B1")), CValue(3012.0)));
    assert (valueMatch(x1.getValue(CPos("B2")), CValue(-194.0)));
    assert (valueMatch(x1.getValue(CPos("B3")), CValue(4096.0)));
    assert (valueMatch(x1.getValue(CPos("B4")), CValue(12544.0)));
    assert (valueMatch(x1.getValue(CPos("B5")), CValue(19458.0)));
    assert (valueMatch(x1.getValue(CPos("B6")), CValue(38916.0)));
    oss.clear();
    oss.str("");
    assert (x0.save(oss));
    data = oss.str();
    for (size_t i = 0; i < std::min<size_t>(data.length(), 10); i++)
        data[i] ^= 0x5a;
    iss.clear();
    iss.str(data);
    assert (!x1.load(iss));
    assert (x0.setCell(CPos("D0"), "10"));
    assert (x0.setCell(CPos("D1"), "20"));
    assert (x0.setCell(CPos("D2"), "30"));
    assert (x0.setCell(CPos("D3"), "40"));
    assert (x0.setCell(CPos("D4"), "50"));
    assert (x0.setCell(CPos("E0"), "60"));
    assert (x0.setCell(CPos("E1"), "70"));
    assert (x0.setCell(CPos("E2"), "80"));
    assert (x0.setCell(CPos("E3"), "90"));
    assert (x0.setCell(CPos("E4"), "100"));
    assert (x0.setCell(CPos("F10"), "=D0+5"));
    assert (x0.setCell(CPos("F11"), "=$D0+5"));
    assert (x0.setCell(CPos("F12"), "=D$0+5"));
    assert (x0.setCell(CPos("F13"), "=$D$0+5"));
    x0.copyRect(CPos("G11"), CPos("F10"), 1, 4);
    assert (valueMatch(x0.getValue(CPos("F10")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F11")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F12")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F13")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F14")), CValue()));
    assert (valueMatch(x0.getValue(CPos("G10")), CValue()));
    assert (valueMatch(x0.getValue(CPos("G11")), CValue(75.0)));
    assert (valueMatch(x0.getValue(CPos("G12")), CValue(25.0)));
    assert (valueMatch(x0.getValue(CPos("G13")), CValue(65.0)));
    assert (valueMatch(x0.getValue(CPos("G14")), CValue(15.0)));
    x0.copyRect(CPos("G11"), CPos("F10"), 2, 4);
    assert (valueMatch(x0.getValue(CPos("F10")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F11")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F12")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F13")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("F14")), CValue()));
    assert (valueMatch(x0.getValue(CPos("G10")), CValue()));
    assert (valueMatch(x0.getValue(CPos("G11")), CValue(75.0)));
    assert (valueMatch(x0.getValue(CPos("G12")), CValue(25.0)));
    assert (valueMatch(x0.getValue(CPos("G13")), CValue(65.0)));
    assert (valueMatch(x0.getValue(CPos("G14")), CValue(15.0)));
    assert (valueMatch(x0.getValue(CPos("H10")), CValue()));
    assert (valueMatch(x0.getValue(CPos("H11")), CValue()));
    assert (valueMatch(x0.getValue(CPos("H12")), CValue()));
    assert (valueMatch(x0.getValue(CPos("H13")), CValue(35.0)));
    assert (valueMatch(x0.getValue(CPos("H14")), CValue()));
    assert (x0.setCell(CPos("F0"), "-27"));
    assert (valueMatch(x0.getValue(CPos("H14")), CValue(-22.0)));
    x0.copyRect(CPos("H12"), CPos("H13"), 1, 2);
    assert (valueMatch(x0.getValue(CPos("H12")), CValue(25.0)));
    assert (valueMatch(x0.getValue(CPos("H13")), CValue(-22.0)));
    assert (valueMatch(x0.getValue(CPos("H14")), CValue(-22.0)));
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
