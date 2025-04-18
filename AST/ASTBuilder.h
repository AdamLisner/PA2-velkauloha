#pragma once

#include "AST.h"


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

    std::stack<std::shared_ptr<ASTNode>> &stack() {
        return m_Stack;
    }

private:

    std::stack<std::shared_ptr<ASTNode>> m_Stack;

};