//
// Created by adam on 23.4.24.
//
#include "cstdlib"

class CCell {
public:
    CCell(const std::shared_ptr<ASTNode>& root) : m_Root(root){};
    CCell(){
        ASTNodeValue c;
        m_Root = std::make_shared<ASTNodeValue>(c);
    };
private:

    std::shared_ptr<ASTNode> m_Root;
};
