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


class ASTNodeDouble : public ASTNode {
public:
    CValue evaluate() const override;
protected:
private:
    double m_Val;
};

class ASTNodeString : public ASTNode {
public:
    CValue evaluate() const override;
protected:
private:
    std::string m_Val;
};


class ASTNodeRelativeFull : public ASTNode {
};

class ASTNodeRelativeCol : public ASTNode {
};

class ASTNodeRelativeRow : public ASTNode {
};

using ASTLeaf = std::shared_ptr<ASTNode>;

class ASTOperator : public ASTNode {
public:
    virtual CValue evaluate() = 0;
    ASTOperator(ASTLeaf left, ASTLeaf right): m_Left(std::move(left)), m_Right(std::move(right)){};
protected:
    ASTLeaf m_Left;
    ASTLeaf m_Right;
};



class ASTAdd : public ASTOperator {
public:
    CValue evaluate() const override;


    ASTAdd(ASTLeaf left, ASTLeaf right): ASTOperator(left,right){};
};

class ASTSub : public ASTOperator {
public:
    CValue evaluate() const override;
    ASTSub(ASTLeaf left, ASTLeaf right): ASTOperator(left,right){};

};

class ASTDiv : public ASTOperator {
public:
    CValue evaluate() const override;
    ASTDiv(ASTLeaf left, ASTLeaf right): ASTOperator(left,right){};

};

class ASTMul : public ASTOperator {
public:
    CValue evaluate() const override;
    ASTMul(ASTLeaf left, ASTLeaf right): ASTOperator(left,right){};

};

class ASTPow : public ASTOperator {
public:
    CValue evaluate() const override;
    ASTPow(ASTLeaf left, ASTLeaf right): ASTOperator(left,right){};

};

