#include "ASTBuilder.h"

void ASTBuilder::opAdd() {
    ASTAdd add;
    std::cout << " + ";
    m_Stack.push(std::make_shared<ASTNode>(add));
}

void ASTBuilder::opSub() {
    ASTSub sub;
    std::cout << " - ";
    m_Stack.push(std::make_shared<ASTNode>(sub));
}

void ASTBuilder::opMul() {
    ASTMul mul;
    std::cout << " * ";
    m_Stack.push(std::make_shared<ASTNode>(mul));
}

void ASTBuilder::opDiv() {
    ASTDiv div;
    std::cout << " / ";
    m_Stack.push(std::make_shared<ASTNode>(div));
}

void ASTBuilder::opPow() {
    ASTPow pow;
    std::cout << " ^ ";
    m_Stack.push(std::make_shared<ASTNode>(pow));
}

void ASTBuilder::opNeg() {
    // Implementation for negation operator
}

void ASTBuilder::opEq() {
    // Implementation for equality operator
}

void ASTBuilder::opNe() {
    // Implementation for inequality operator
}

void ASTBuilder::opLt() {
    // Implementation for less than operator
}

void ASTBuilder::opLe() {
    // Implementation for less than or equal to operator
}

void ASTBuilder::opGt() {
    // Implementation for greater than operator
}

void ASTBuilder::opGe() {
    // Implementation for greater than or equal to operator
}

void ASTBuilder::valNumber(double val) {
    // Implementation for handling numeric value
}

void ASTBuilder::valString(std::string val) {
    // Implementation for handling string value
}

void ASTBuilder::valReference(std::string val) {
    // Implementation for handling reference value
}

void ASTBuilder::valRange(std::string val) {
    // Implementation for handling range value
}

void ASTBuilder::funcCall(std::string fnName, int paramCount) {
    // Implementation for function call
}
