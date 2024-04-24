#include "expression.h"
#include "AST.h"
#include "stack"
#include "memory"
#include <iostream>


class ASTBuilder: public CExprBuilder {
public:
     void opAdd() ;

     void opSub() ;

     void opMul() ;

     void opDiv() ;

     void opPow() ;

     void opNeg() ;

     void opEq() ;

     void opNe() ;

     void opLt() ;

     void opLe() ;

     void opGt() ;

     void opGe();

     void valNumber(double val);

     void valString(std::string val);

     void valReference(std::string val);

     void valRange(std::string val);

     void funcCall(std::string fnName,
                          int paramCount);
private:

    std::stack<std::shared_ptr<ASTNode>> m_Stack;

};