#include "ASTBuilder.h"

using ASTLeaf = std::shared_ptr<ASTNode>;


void ASTBuilder::opAdd() {
    std::cout << " + ";
    ASTLeaf right = m_Stack.top();
    m_Stack.pop();
    ASTLeaf left = m_Stack.top();
    m_Stack.pop();

    ASTAdd add(left,right);

    m_Stack.push(std::make_shared<ASTAdd>(add));
}

void ASTBuilder::opSub() {
    std::cout << " - ";
    ASTLeaf right = m_Stack.top();
    m_Stack.pop();
    ASTLeaf left = m_Stack.top();
    m_Stack.pop();
    ASTSub sub(left,right);
    m_Stack.push(std::make_shared<ASTSub>(sub));
}

void ASTBuilder::opMul() {
    std::cout << " * ";
    ASTLeaf right = m_Stack.top();
    m_Stack.pop();
    ASTLeaf left = m_Stack.top();
    m_Stack.pop();
    ASTMul mul(left,right);
    m_Stack.push(std::make_shared<ASTMul>(mul));
}

void ASTBuilder::opDiv() {
    std::cout << " / ";
    ASTLeaf right = m_Stack.top();
    m_Stack.pop();
    ASTLeaf left = m_Stack.top();
    m_Stack.pop();
    ASTDiv div(left,right);
    m_Stack.push(std::make_shared<ASTDiv>(div));
}

void ASTBuilder::opPow() {
    //ASTPow pow;
    std::cout << " ^ ";
    ASTLeaf right = m_Stack.top();
    m_Stack.pop();
    ASTLeaf left = m_Stack.top();
    m_Stack.pop();
    ASTPow pow(left,right);
    m_Stack.push(std::make_shared<ASTPow>(pow));
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
    ASTNodeValue node(val);
    m_Stack.push(std::make_shared<ASTNodeValue>(node));
    std::cout << val;
}

void ASTBuilder::valRange(std::string val) {
    // Implementation for handling range value
    std::cout << val;

}

void ASTBuilder::funcCall(std::string fnName, int paramCount) {
    // Implementation for function call
}
