#include <iostream>
#include "Node.h"
#include "Debug.h"

Node::~Node() {}

StartNode::StartNode(ProgramNode* node) {
    MSG("CREATED START");
    this->mNode = node;
}

StartNode::~StartNode() {
    MSG("DELETED START NODE");
    delete(mNode);
}

void StartNode::Interpret() {
    mNode->Interpret();
}

ProgramNode::ProgramNode(BlockNode* node){
    MSG("CREATED PROGRAM");
    this->mNode = node;
}

ProgramNode::~ProgramNode(){
    MSG("DELETED PROGRAM NODE");
    delete(mNode);
}

void ProgramNode::Interpret() {
    mNode->Interpret();
}

BlockNode::BlockNode(StatementGroupNode* node) {
    MSG("CREATED BLOCK");
    this->mNode = node;
}

BlockNode::~BlockNode() {
    MSG("DELETED BLOCK NODE");
    delete(mNode);
}

void BlockNode::Interpret() {
    mNode->Interpret();
}

StatementGroupNode::StatementGroupNode() {
    MSG("CREATED STATEMENT GROUP");
}

StatementGroupNode::~StatementGroupNode() {
    MSG("DELETED STATEMENTGROUP NODE");
    for (int i = 0;i<mNodes.size();i++) {
        MSG(i);
        delete(mNodes[i]);
    }
}

void StatementGroupNode::AddStatement(StatementNode* node) {
    mNodes.push_back(node);
}

void StatementGroupNode::Interpret() {
    for (StatementNode* node: mNodes) {
        node->Interpret();
    }
}

StatementNode::~StatementNode() {
    MSG("DELETE STATEMENT NODE");
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* node) {
    mNode = node;
    MSG("CREATED DECLARATION STATEMENT NODE");
}

DeclarationStatementNode::~DeclarationStatementNode() {
    MSG("DELETED DECLARATIONSTATEMENT NODE");
    delete(mNode);
}

void DeclarationStatementNode::Interpret() {
    mNode->DeclareVariable();
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* idnode,ExpressionNode* expnode) {
    mIdNode = idnode;
    mExpNode = expnode;
    MSG("CREATED ASSIGNMENT STATEMENT NODE");
}

AssignmentStatementNode::~AssignmentStatementNode() {
    MSG("DELETED ASSIGNMENT NODE");
    delete(mIdNode);
    delete(mExpNode);
}

void AssignmentStatementNode::Interpret() {
    int val = mExpNode->Evaluate();
    mIdNode->SetValue(val);
}

CoutStatementNode::CoutStatementNode(ExpressionNode* node) {
    mNode = node;
    MSG("CREATED COUT NODE");
}

CoutStatementNode::~CoutStatementNode() {
    MSG("DELETED COUT NODE");
    delete(mNode);
}

void CoutStatementNode::Interpret() {
    int val = mNode->Evaluate();
    std::cout << val << std::endl;
}

ExpressionNode::~ExpressionNode() {
    MSG("DELETE EXPRESSION NODE")
}

IntegerNode::IntegerNode(int num) {
    mInt = num;
    MSG("CREATE INTEGER NODE")
}

int IntegerNode::Evaluate() {
    return mInt;
}

IntegerNode::~IntegerNode() {
    MSG("DELETING INTEGER NODE WITH " << mInt);
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass* st) {
    mSymbolTable = st;
    mLabel = label;
    MSG("CREATE ID NODE "<<mLabel);
}

void IdentifierNode::DeclareVariable() {
    mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v) {
    mSymbolTable->SetValue(mLabel,v);
}

int IdentifierNode::GetIndex() {
    return mSymbolTable->GetIndex(mLabel);
}

int IdentifierNode::Evaluate() {
    return mSymbolTable->GetValue(mLabel);
}

IdentifierNode::~IdentifierNode() {
    MSG("DELETING IDENTIFIER NODE WITH " << mLabel);
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* lnode,ExpressionNode* rnode) {
    mLeftNode = lnode;
    mRightNode = rnode;
    MSG("CREATE BIN OP NODE");
}

BinaryOperatorNode::~BinaryOperatorNode() {
    MSG("DELETED BINOP NODE");
    delete(mLeftNode);
    delete(mRightNode);
}


PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE PLUS NODE");
    }

int PlusNode::Evaluate() {
    return mLeftNode->Evaluate() + mRightNode->Evaluate();
}

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE MINUS NODE");
    }

int MinusNode::Evaluate() {
    return mLeftNode->Evaluate() - mRightNode->Evaluate();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE TIMES NODE");
    }

int TimesNode::Evaluate() {
    return mLeftNode->Evaluate() * mRightNode->Evaluate();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE DIVIDE NODE");
    }

int DivideNode::Evaluate() {
    return mLeftNode->Evaluate() / mRightNode->Evaluate();
}

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE LESS NODE");
    }

int LessNode::Evaluate() {
    return mLeftNode->Evaluate() < mRightNode->Evaluate();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE LESSEQUAL NODE");
    }

int LessEqualNode::Evaluate() {
    return mLeftNode->Evaluate() <= mRightNode->Evaluate();
}


GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED GREATER NODE");
    }

int GreaterNode::Evaluate() {
    return mLeftNode->Evaluate() > mRightNode->Evaluate();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED GREATER EQUAL NODE");
    }

int GreaterEqualNode::Evaluate() {
    return mLeftNode->Evaluate() >= mRightNode->Evaluate();
}


EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED EQUAL NODE");
    }

int EqualNode::Evaluate() {
    return mLeftNode->Evaluate() == mRightNode->Evaluate();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED NOT EQUAL NODE");
    }

int NotEqualNode::Evaluate() {
    return mLeftNode->Evaluate() != mRightNode->Evaluate();
}
