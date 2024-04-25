#include <variant>
#include "memory"

using CValue = std::variant<std::monostate, double, std::string>;

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual CValue evaluate() const = 0;
protected:
private:
};


class ASTNodeValue : public ASTNode {
public:
    ASTNodeValue() : m_Val(std::monostate()){};
    ASTNodeValue(const CValue& c): m_Val(c){};
    CValue evaluate() const override;
protected:
private:
    CValue m_Val;
};




class ASTNodeReference : public ASTNode {
public:
private:
    bool absCol;
    bool absRow;
};

using ASTLeaf = std::shared_ptr<ASTNode>;

class ASTBinOperator : public ASTNode {
public:
    ASTBinOperator(ASTLeaf left, ASTLeaf right): m_Left(std::move(left)), m_Right(std::move(right)){};
protected:
    ASTLeaf m_Left;
    ASTLeaf m_Right;
};



class ASTAdd : public ASTBinOperator {
public:
    ASTAdd(ASTLeaf left, ASTLeaf right): ASTBinOperator(std::move(left), std::move(right)){};
    CValue evaluate() const override;
};

class ASTSub : public ASTBinOperator {
public:
    ASTSub(ASTLeaf left, ASTLeaf right): ASTBinOperator(std::move(left), std::move(right)){};
    CValue evaluate() const override;

};

class ASTDiv : public ASTBinOperator {
public:
    ASTDiv(ASTLeaf left, ASTLeaf right): ASTBinOperator(std::move(left), std::move(right)){};
    CValue evaluate() const override;

};

class ASTMul : public ASTBinOperator {
public:
    ASTMul(ASTLeaf left, ASTLeaf right): ASTBinOperator(std::move(left), std::move(right)){};
    CValue evaluate() const override;

};

class ASTPow : public ASTBinOperator {
public:
    CValue evaluate() const override;
    ASTPow(ASTLeaf left, ASTLeaf right): ASTBinOperator(left, right){};

};

