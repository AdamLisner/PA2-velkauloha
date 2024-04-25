#include "AST.h"
using CValue = std::variant<std::monostate, double, std::string>;

// ASTNodeDouble implementation
CValue ASTNodeValue::evaluate() const {
    // Implement evaluation logic for double node
    return std::monostate();
}


// ASTAdd implementation
CValue ASTAdd::evaluate() const {
    // Implement addition operation evaluation
     return std::monostate();
}

// ASTSub implementation
CValue ASTSub::evaluate() const {
    // Implement subtraction operation evaluation
    return std::monostate();

}

// ASTDiv implementation
CValue ASTDiv::evaluate() const {
    // Implement division operation evaluation
    return std::monostate();

}

// ASTMul implementation
CValue ASTMul::evaluate() const {
    // Implement multiplication operation evaluation
    return std::monostate();

}

// ASTPow implementation
CValue ASTPow::evaluate() const {
    // Implement exponentiation operation evaluation
    return std::monostate();

}



