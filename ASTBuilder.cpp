#include "ASTBuilder.h"

void ASTBuilder::opAdd() {
    //ASTAdd add;
    std::cout << " + ";
    //m_Stack.push(std::make_shared<ASTNode>(add));
}

void ASTBuilder::opSub() {
    //ASTSub sub;
    std::cout << " - ";
    //m_Stack.push(std::make_shared<ASTNode>(sub));
}

void ASTBuilder::opMul() {
    //ASTMul mul;
    std::cout << " * ";
    //m_Stack.push(std::make_shared<ASTNode>(mul));
}

void ASTBuilder::opDiv() {
    //ASTDiv div;
    std::cout << " / ";
    //m_Stack.push(std::make_shared<ASTNode>(div));
}

void ASTBuilder::opPow() {
    //ASTPow pow;
    std::cout << " ^ ";
    //m_Stack.push(std::make_shared<ASTNode>(pow));
}

void ASTBuilder::opNeg() {
    std::cout << " ! ";

    // Implementation for negation operator
}

void ASTBuilder::opEq() {
    std::cout << " == ";

    // Implementation for equality operator
}

void ASTBuilder::opNe() {
    std::cout << " != ";

    // Implementation for inequality operator
}

void ASTBuilder::opLt() {
    std::cout << " < ";

    // Implementation for less than operator
}

void ASTBuilder::opLe() {
    std::cout << " <= ";

    // Implementation for less than or equal to operator
}

void ASTBuilder::opGt() {
    std::cout << " > ";

    // Implementation for greater than operator
}

void ASTBuilder::opGe() {
    std::cout << " >= ";

    // Implementation for greater than or equal to operator
}

void ASTBuilder::valNumber(double val) {
    // Implementation for handling numeric value
    std::cout << val;
}

void ASTBuilder::valString(std::string val) {
    // Implementation for handling string value
    std::cout << val;
}

void ASTBuilder::valReference(std::string val) {
    // Implementation for handling reference value
    std::cout << val;
}

void ASTBuilder::valRange(std::string val) {
    // Implementation for handling range value
    std::cout << val;

}

void ASTBuilder::funcCall(std::string fnName, int paramCount) {
    // Implementation for function call
}
