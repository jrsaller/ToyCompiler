#ifndef NODE
#define NODE

#include <vector>
#include <string>
#include "Symbol.h"

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
        ProgramNode* mNode;
};

class ProgramNode : public Node {
    public:
        ProgramNode(BlockNode* node);
        ~ProgramNode();
    private:
        BlockNode* mNode;
};
class BlockNode : public Node {
    public:
        BlockNode(StatementGroupNode* node);
        ~BlockNode();
    private:
        StatementGroupNode* mNode;
};
class StatementGroupNode : public Node {
    public:
        StatementGroupNode();
        ~StatementGroupNode();
        void AddStatement(StatementNode* node);

    private:
        std::vector<StatementNode*> mNodes;
};

class StatementNode: public Node {
    public:
        virtual ~StatementNode();
};

class DeclarationStatementNode: public StatementNode {
    public:
        DeclarationStatementNode(IdentifierNode* mNode);
        ~DeclarationStatementNode();
    private:
        IdentifierNode* mNode;
};

class AssignmentStatementNode:public StatementNode {
    public:
        AssignmentStatementNode(IdentifierNode* idnode,ExpressionNode* expnode);
        ~AssignmentStatementNode();
    private:
        IdentifierNode* mIdNode;
        ExpressionNode* mExpNode;
};

class CoutStatementNode: public StatementNode {
    public:
        CoutStatementNode(ExpressionNode* node);
        ~CoutStatementNode();
    private:
        ExpressionNode* mNode;
};

class ExpressionNode {
    public:
        virtual int Evaluate() = 0;
        virtual ~ExpressionNode();
        //virtual void Interpret() = 0;
};

class IntegerNode: public ExpressionNode {
    public:
        IntegerNode(int num);
        int Evaluate();
    private:
        int mInt;
};

class IdentifierNode: public ExpressionNode {
    public:
        IdentifierNode(std::string label, SymbolTableClass* st);
        void DeclareVariable();
        void SetValue(int v);
        int GetIndex();
        int Evaluate();
    private:
        std::string mLabel;
        SymbolTableClass* mSymbolTable;
};

class BinaryOperatorNode: public ExpressionNode {
    public:
        BinaryOperatorNode(ExpressionNode* lnode,ExpressionNode* rnode);
        ~BinaryOperatorNode();
    protected:
        ExpressionNode* mLeftNode;
        ExpressionNode* mRightNode;
};   

class PlusNode: public BinaryOperatorNode {
    public:
        PlusNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};

class MinusNode: public BinaryOperatorNode {
    public:
        MinusNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};

class TimesNode: public BinaryOperatorNode {
    public:
        TimesNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};

class DivideNode: public BinaryOperatorNode {
    public:
        DivideNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};

class LessNode: public BinaryOperatorNode {
    public:
        LessNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};

class LessEqualNode: public BinaryOperatorNode {
    public:
        LessEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};

class GreaterNode: public BinaryOperatorNode {
    public:
        GreaterNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};

class GreaterEqualNode: public BinaryOperatorNode {
    public:
        GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};


class EqualNode: public BinaryOperatorNode {
    public:
        EqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};

class NotEqualNode: public BinaryOperatorNode {
    public:
        NotEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
};

#endif