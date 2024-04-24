#include "memory"
class ASTNode {};

class ASTNodeValue        : public ASTNode {};

class ASTNodeLiteral      : public ASTNodeValue {};

class ASTNodeDouble       : public ASTNodeLiteral {};

class ASTNodeString       : public ASTNodeLiteral {};

class ASTNodeRelative     : public ASTNodeValue {};

class ASTNodeRelativeFull : public ASTNodeRelative{};

class ASTNodeRelativeCol  : public ASTNodeRelative{};

class ASTNodeRelativeRow  : public ASTNodeRelative{};

class ASTNodeOperand      : public ASTNode {
public:
protected:
    std::shared_ptr<ASTNode> m_Left;
    std::shared_ptr<ASTNode> m_Right;
};

class ASTAdd         : public ASTNodeOperand {};
class ASTSub         : public ASTNodeOperand {};
class ASTDiv         : public ASTNodeOperand {};
class ASTMul         : public ASTNodeOperand {};
class ASTPow         : public ASTNodeOperand {};

