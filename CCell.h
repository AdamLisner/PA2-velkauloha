//
// Created by adam on 23.4.24.
//
#include "cstdlib"

class CCell {
public:
    CCell(std::string formula) : m_Formula(std::move(formula)), m_Root(){};
private:
    std::string m_Formula;
    //std::pair<size_t, size_t> m_Pos;
    std::shared_ptr<ASTNode> m_Root;
};
