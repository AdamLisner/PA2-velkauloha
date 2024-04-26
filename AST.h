#include <utility>
#include <variant>
#include <cmath>
#include <unordered_map>
#include "memory"
#include "hash_pair.h"

using CValue = std::variant<std::monostate, double, std::string>;
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void moveRelative(std::pair<size_t,size_t> offset) = 0;
    virtual CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const = 0;
    virtual std::string toString() const = 0;
protected:
private:
};


class ASTNodeValue : public ASTNode {
public:
    ASTNodeValue() : m_Val(std::monostate()) {};

    ASTNodeValue(CValue c) : m_Val(std::move(c)) {};

    std::string toString() const override;

    void moveRelative(std::pair<size_t, size_t> offset) override{

    };

    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;

protected:
private:
    CValue m_Val;
};


using ANode = std::shared_ptr<ASTNode>;

class ASTNodeReference : public ASTNode {
public:
    ASTNodeReference(bool aCol, bool aRow, const std::pair<size_t,size_t> &coor):m_AbsCol(aCol),m_AbsRow(aRow),m_Coor(coor){};
    void moveRelative(std::pair<size_t, size_t> offset) override;
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
    std::string toString() const override;

private:
    bool m_AbsCol = false;
    bool m_AbsRow = false;
    std::pair<size_t,size_t> m_Coor;
};

class ASTBinOperator : public ASTNode {
public:
    ASTBinOperator(ANode left, ANode right) : m_Left(std::move(left)), m_Right(std::move(right)) {};
    void moveRelative(std::pair<size_t, size_t> offset) override;
    virtual std::string toString() const = 0;

protected:
    ANode m_Left;
    ANode m_Right;
};


class ASTAdd : public ASTBinOperator {
public:
    ASTAdd(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
    std::string toString() const override;
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
};

class ASTSub : public ASTBinOperator {
public:
    ASTSub(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
    std::string toString() const override;
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;

};

class ASTDiv : public ASTBinOperator {
public:
    ASTDiv(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
    std::string toString() const override;

    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;

};

class ASTMul : public ASTBinOperator {
public:
    ASTMul(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
    std::string toString() const override;

    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;

};

class ASTPow : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
    std::string toString() const override;

    ASTPow(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTEq : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
    std::string toString() const override;

    ASTEq(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTNe : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
    std::string toString() const override;

    ASTNe(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTLt : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
    std::string toString() const override;

    ASTLt(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTLe : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
    std::string toString() const override;

    ASTLe(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTGt : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
    std::string toString() const override;

    ASTGt(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTGe : public ASTBinOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
    std::string toString() const override;

    ASTGe(ANode left, ANode right) : ASTBinOperator(std::move(left), std::move(right)) {};
};

class ASTUnOperator : public ASTNode {
public:
    ASTUnOperator(ANode child) : m_Child(std::move(child)) {};
    void moveRelative(std::pair<size_t, size_t> offset) override;
    virtual std::string toString() const = 0;

protected:
    ANode m_Child;
};

class ASTNeg : public ASTUnOperator {
public:
    CValue evaluate(const std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<ASTNode>,hash_pair> &map) const override;
    std::string toString() const override;

    ASTNeg(ANode child) : ASTUnOperator(std::move(child)) {};
};


