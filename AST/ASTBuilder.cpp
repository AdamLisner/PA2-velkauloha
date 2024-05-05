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
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();

    ASTAdd add(left, right);

    m_Stack.push(std::make_shared<ASTAdd>(add));
}

void ASTBuilder::opSub() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTSub sub(left, right);
    m_Stack.push(std::make_shared<ASTSub>(sub));
}

void ASTBuilder::opMul() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTMul mul(left, right);
    m_Stack.push(std::make_shared<ASTMul>(mul));
}

void ASTBuilder::opDiv() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTDiv div(left, right);
    m_Stack.push(std::make_shared<ASTDiv>(div));
}

void ASTBuilder::opPow() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTPow pow(left, right);
    m_Stack.push(std::make_shared<ASTPow>(pow));
}

void ASTBuilder::opNeg() {
    ANode child = m_Stack.top();
    m_Stack.pop();
    ASTNeg minus(child);
    m_Stack.push(std::make_shared<ASTNeg>(minus));
}

void ASTBuilder::opEq() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTEq eq(left, right);
    m_Stack.push(std::make_shared<ASTEq>(eq));
}

void ASTBuilder::opNe() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTNe ne(left, right);
    m_Stack.push(std::make_shared<ASTNe>(ne));
}

void ASTBuilder::opLt() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTLt lt(left, right);
    m_Stack.push(std::make_shared<ASTLt>(lt));
}

void ASTBuilder::opLe() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTLe le(left, right);
    m_Stack.push(std::make_shared<ASTLe>(le));
}

void ASTBuilder::opGt() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTGt gt(left, right);
    m_Stack.push(std::make_shared<ASTGt>(gt));
}

void ASTBuilder::opGe() {
    ANode right = m_Stack.top();
    m_Stack.pop();
    ANode left = m_Stack.top();
    m_Stack.pop();
    ASTGe ge(left, right);
    m_Stack.push(std::make_shared<ASTGe>(ge));
}

void ASTBuilder::valNumber(double val) {
    ASTNodeValue node(val);
    m_Stack.push(std::make_shared<ASTNodeValue>(node));
}

void ASTBuilder::valString(std::string val) {
    ASTNodeValue node(val);
    m_Stack.push(std::make_shared<ASTNodeValue>(node));
}

void ASTBuilder::valReference(std::string val) {
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

void ASTBuilder::valRange(std::string val) {}

void ASTBuilder::funcCall(std::string fnName, int paramCount) {}
