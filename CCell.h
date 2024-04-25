//
// Created by adam on 23.4.24.
//
#include "cstdlib"

class CCell {
public:
    CCell(std::string formula, const std::shared_ptr<ASTNode>& root) : m_Formula(std::move(formula)), m_Root(root){};
    CCell(){
        m_Root = std::make_shared<ASTNodeValue>();
    };
private:
    std::string m_Formula;
    //std::pair<size_t, size_t> m_Pos;
    std::shared_ptr<ASTNode> m_Root;
};
