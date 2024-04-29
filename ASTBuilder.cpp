#include "ASTBuilder.h"
#include "ASTAdd.h"
#include "ASTSub.h"
#include "ASTMul.h"
#include "ASTDiv.h"
#include "ASTPow.h"
#include "ASTNeg.h"
#include "ASTEq.h"
#include "ASTNe.h"
#include "ASTLt.h"
#include "ASTLe.h"
#include "ASTGt.h"
#include "ASTGe.h"
#include "ASTNodeValue.h"
#include "ASTNodeReference.h"

using ANode = std::shared_ptr<ASTNode>;


void ASTBuilder::opAdd() {
//    std::cout << " + ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();

    ASTAdd add(left, right);

    m_Stack.push(std::make_shared<ASTAdd>(add));
}

void ASTBuilder::opSub() {
//    std::cout << " - ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTSub sub(left, right);
    m_Stack.push(std::make_shared<ASTSub>(sub));
}

void ASTBuilder::opMul() {
//    std::cout << " * ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTMul mul(left, right);
    m_Stack.push(std::make_shared<ASTMul>(mul));
}

void ASTBuilder::opDiv() {
//    std::cout << " / ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTDiv div(left, right);
    m_Stack.push(std::make_shared<ASTDiv>(div));
}

void ASTBuilder::opPow() {
    //ASTPow pow;
//    std::cout << " ^ ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTPow pow(left, right);
    m_Stack.push(std::make_shared<ASTPow>(pow));
}

void ASTBuilder::opNeg() {
//    std::cout << " - ";
    ANode child = m_Stack.top();
    m_Stack.pop();
    ASTNeg minus(child);
    m_Stack.push(std::make_shared<ASTNeg>(minus));

    // Implementation for negation operator
}

void ASTBuilder::opEq() {
//    std::cout << " == ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTEq eq(left, right);
    m_Stack.push(std::make_shared<ASTEq>(eq));
    // Implementation for equality operator
}

void ASTBuilder::opNe() {
//    std::cout << " != ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTNe ne(left, right);
    m_Stack.push(std::make_shared<ASTNe>(ne));
    // Implementation for inequality operator
}

void ASTBuilder::opLt() {
//    std::cout << " < ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTLt lt(left, right);
    m_Stack.push(std::make_shared<ASTLt>(lt));
    // Implementation for less than operator
}

void ASTBuilder::opLe() {
//    std::cout << " <= ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTLe le(left, right);
    m_Stack.push(std::make_shared<ASTLe>(le));
    // Implementation for less than or equal to operator
}

void ASTBuilder::opGt() {
//    std::cout << " > ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTGt gt(left, right);
    m_Stack.push(std::make_shared<ASTGt>(gt));
    // Implementation for greater than operator
}

void ASTBuilder::opGe() {
//    std::cout << " >= ";
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTGe ge(left, right);
    m_Stack.push(std::make_shared<ASTGe>(ge));
    // Implementation for greater than or equal to operator
}

void ASTBuilder::valNumber(double val) {
    // Implementation for handling numeric value
    ASTNodeValue node(val);
    m_Stack.push(std::make_shared<ASTNodeValue>(node));
//    std::cout << val;
}

void ASTBuilder::valString(std::string val) {
    // Implementation for handling string value
    ASTNodeValue node(val);
    m_Stack.push(std::make_shared<ASTNodeValue>(node));
//    std::cout << val;
}

void ASTBuilder::valReference(std::string val) {
    // Implementation for handling reference value
//    std::cout << " " << val << " ";
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
    if (count == 1 && val[0] == '$')
        absCol = true;
    else if (count == 1 && val[0] != '$')
        absRow = true;

    size_t pos = val.find('$');
    while (pos != std::string::npos) {
        val.erase(pos, 1);
        pos = val.find('$', pos);
    }
    std::pair<size_t, size_t> coor = CPos::strToPair(val);

    ASTNodeReference node(absCol, absRow, coor);

    stack().push(std::make_shared<ASTNodeReference>(node));
}

void ASTBuilder::valRange(std::string val) {
    // Implementation for handling range value
    std::cout << val;

}

void ASTBuilder::funcCall(std::string fnName, int paramCount) {
    // Implementation for function call
}
