#ifndef NODE
#define NODE

#include <vector>
#include <string>
#include "Symbol.h"
#include "Instructions.h"

class Node;
class StartNode;
class ProgramNode;
class StatementGroupNode;

class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class BlockNode;
class IfStatementNode;
class WhileStatementNode;

class ExpressionNode;
class IntegerNode;
class IdentifierNode;

class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class NotEqualNode;
class EqualNode;
class AndNode;
class OrNode;

class Node {
    public:
        virtual ~Node();
        virtual void Interpret()=0;
        virtual void Code(InstructionsClass &machineCode)=0;
};

class StartNode : public Node {
    public:
        StartNode(ProgramNode* node);
        ~StartNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        ProgramNode* mNode;
};

class ProgramNode : public Node {
    public:
        ProgramNode(BlockNode* node);
        ~ProgramNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        BlockNode* mNode;
};

class StatementGroupNode : public Node {
    public:
        StatementGroupNode();
        ~StatementGroupNode();
        void AddStatement(StatementNode* node);
        void Interpret();
        void Code(InstructionsClass &machineCode);

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
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        IdentifierNode* mNode;
};

class AssignmentStatementNode:public StatementNode {
    public:
        AssignmentStatementNode(IdentifierNode* idnode,ExpressionNode* expnode);
        ~AssignmentStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        IdentifierNode* mIdNode;
        ExpressionNode* mExpNode;
};

class CoutStatementNode: public StatementNode {
    public:
        CoutStatementNode(std::vector<ExpressionNode*> nodes);
        ~CoutStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        std::vector<ExpressionNode*> mNodes;
};
class BlockNode : public StatementNode {
    public:
        BlockNode(StatementGroupNode* node);
        ~BlockNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        StatementGroupNode* mNode;
};

class IfStatementNode : public StatementNode {
    public:
        IfStatementNode(ExpressionNode * exp,StatementNode * statement);
        ~IfStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        ExpressionNode * mExpression;
        StatementNode * mStatement;

};

class WhileStatementNode : public StatementNode {
    public:
        WhileStatementNode(ExpressionNode * exp,StatementNode * statement);
        ~WhileStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        ExpressionNode * mExpression;
        StatementNode * mStatement;

};


class ExpressionNode {
    public:
        virtual int Evaluate() = 0;
        virtual ~ExpressionNode();
        //virtual void Interpret() = 0;
        virtual void CodeEvaluate(InstructionsClass &machineCode)=0;
};



class IntegerNode: public ExpressionNode {
    public:
        IntegerNode(int num);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
        ~IntegerNode();
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
        void CodeEvaluate(InstructionsClass &machineCode);
        ~IdentifierNode();
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
        void CodeEvaluate(InstructionsClass &machineCode);
};

class MinusNode: public BinaryOperatorNode {
    public:
        MinusNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class TimesNode: public BinaryOperatorNode {
    public:
        TimesNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class DivideNode: public BinaryOperatorNode {
    public:
        DivideNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class LessNode: public BinaryOperatorNode {
    public:
        LessNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class LessEqualNode: public BinaryOperatorNode {
    public:
        LessEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class GreaterNode: public BinaryOperatorNode {
    public:
        GreaterNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class GreaterEqualNode: public BinaryOperatorNode {
    public:
        GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};


class EqualNode: public BinaryOperatorNode {
    public:
        EqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class NotEqualNode: public BinaryOperatorNode {
    public:
        NotEqualNode(ExpressionNode* left, ExpressionNode* right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class AndNode : public BinaryOperatorNode {
    public:
        AndNode(ExpressionNode * left, ExpressionNode * right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class OrNode : public BinaryOperatorNode {
    public:
        OrNode(ExpressionNode * left, ExpressionNode * right);
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};


#endif