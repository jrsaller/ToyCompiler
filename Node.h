#include <vector>
class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;

class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;

class ExpressionNode;
class IntegerNode;
class IdentifierNode;

class BinaryOperatorNode;
class PlusNode;

class Node {
    public:
        virtual ~Node();
};

class StartNode : public Node {
    public:
        StartNode(ProgramNode* node);
        ~StartNode();
    private:
        ProgramNode* node;
};

class ProgramNode : public Node {
    public:
        ProgramNode(BlockNode* node);
        ~ProgramNode();
    private:
        BlockNode* node;
};
class BlockNode : public Node {
    public:
        BlockNode(StatementGroupNode* node);
        ~BlockNode();
    private:
        StatementGroupNode* node;
};
class StatementGroupNode : public Node {
    public:
        StatementGroupNode();
        ~StatementGroupNode();
        void AddStatement(StatementNode* node);

    private:
        std::vector<StatementNode*> nodes;
};

class StatementNode: public Node {
    public:
        virtual ~StatementNode();
};