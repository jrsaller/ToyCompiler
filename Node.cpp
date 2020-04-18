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
    MSG("INTERPRET START");
    mNode->Interpret();
}

void StartNode::Code(InstructionsClass &machineCode) {
    mNode->Code(machineCode);
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
    MSG("INTERPRET PROGRAM");
    mNode->Interpret();
}

void ProgramNode::Code(InstructionsClass &machineCode) {
    mNode->Code(machineCode);
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
    MSG("INTERPRET BLOCK");
    mNode->Interpret();
}

void BlockNode::Code(InstructionsClass &machineCode) {
    mNode->Code(machineCode);
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
    MSG("INTERPRET STATEMENTGROUP");
    for (StatementNode* node: mNodes) {
        node->Interpret();
    }
}

void StatementGroupNode::Code(InstructionsClass &machineCode) {
    for (StatementNode* node: mNodes) {
        node->Code(machineCode);
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
    MSG("INTERPRET DECLARATION STATEMENT");
    mNode->DeclareVariable();
}

void DeclarationStatementNode::Code(InstructionsClass &machineCode) {
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
    MSG("INTERPRET ASSIGNMENT STATEMENT");
    int val = mExpNode->Evaluate();
    mIdNode->SetValue(val);
}

void AssignmentStatementNode::Code(InstructionsClass &machineCode) {
    mExpNode->CodeEvaluate(machineCode);
    int index = mIdNode->GetIndex();
    machineCode.PopAndStore(index);
}

CoutStatementNode::CoutStatementNode(std::vector<ExpressionNode*> nodes) {
    mNodes = nodes;
    MSG("CREATED COUT NODE");
}

CoutStatementNode::~CoutStatementNode() {
    MSG("DELETED COUT NODE");
    for (ExpressionNode* node: mNodes) {
        delete(node);
    }
}

void CoutStatementNode::Interpret() {
    MSG("INTERPRET COUT");
    for (ExpressionNode* node: mNodes) {
        if (node){ 
            int val = node->Evaluate();
            std::cout << val;
        } else {
            std::cout << std::endl;
        }
    }
}

void CoutStatementNode::Code(InstructionsClass& machineCode) {
    for (ExpressionNode* node: mNodes) {
        node->CodeEvaluate(machineCode);
        machineCode.PopAndWrite();
    }
}

ExpressionNode::~ExpressionNode() {
    MSG("DELETE EXPRESSION NODE");
}

IfStatementNode::IfStatementNode(ExpressionNode * exp,StatementNode * statement) {
    mExpression = exp;
    mStatement = statement;
}

IfStatementNode::~IfStatementNode() {
    MSG("DELETE IFSTATEMENT NODE");
    delete(mExpression);
    delete(mStatement);

}

void IfStatementNode::Interpret() {
    if (mExpression->Evaluate()) {
        mStatement->Interpret();
    }
}

void IfStatementNode::Code(InstructionsClass& machineCode){
    mExpression->CodeEvaluate(machineCode);
    unsigned char * InsertAddress = machineCode.SkipIfZeroStack();
    unsigned char * address1 = machineCode.GetAddress();
    mStatement->Code(machineCode);
    unsigned char * address2 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddress,(int)(address2-address1));
}

WhileStatementNode::WhileStatementNode(ExpressionNode * exp,StatementNode * statement) {
    mExpression = exp;
    mStatement = statement;
}

WhileStatementNode::~WhileStatementNode() {
    MSG("DELETE WHILE STATEMENT NODE");
    delete(mExpression);
    delete(mStatement);

}

void WhileStatementNode::Interpret() {
    while (mExpression->Evaluate()) {
        MSG("INTERPRET TIME");
        mStatement->Interpret();
    }
}

void WhileStatementNode::Code(InstructionsClass& machineCode) {
    unsigned char * address1 = machineCode.GetAddress();
    mExpression->CodeEvaluate(machineCode);
    unsigned char * InsertAddressToSkip = machineCode.SkipIfZeroStack();
    unsigned char * address2 = machineCode.GetAddress();
    mStatement->Code(machineCode);
    unsigned char * InsertAddressToJump = machineCode.Jump();
    unsigned char * address3 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddressToSkip,(int)(address3-address2));
    machineCode.SetOffset(InsertAddressToJump,(int)(address1-address3));
    
}


IntegerNode::IntegerNode(int num) {
    mInt = num;
    MSG("CREATE INTEGER NODE");
}

int IntegerNode::Evaluate() {
    return mInt;
}

void IntegerNode::CodeEvaluate(InstructionsClass& machineCode){
    machineCode.PushValue(mInt);
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

void IdentifierNode::CodeEvaluate(InstructionsClass& machineCode){
    machineCode.PushVariable(this->GetIndex());
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

void PlusNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
}

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE MINUS NODE");
    }

int MinusNode::Evaluate() {
    return mLeftNode->Evaluate() - mRightNode->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE TIMES NODE");
    }

int TimesNode::Evaluate() {
    return mLeftNode->Evaluate() * mRightNode->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE DIVIDE NODE");
    }

int DivideNode::Evaluate() {
    return mLeftNode->Evaluate() / mRightNode->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopDivPush();
}

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE LESS NODE");
    }

int LessNode::Evaluate() {
    MSG("EVAL LESS NODE");
    return mLeftNode->Evaluate() < mRightNode->Evaluate();
}

void LessNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATE LESSEQUAL NODE");
    }

int LessEqualNode::Evaluate() {
    return mLeftNode->Evaluate() <= mRightNode->Evaluate();
}

void LessEqualNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopLessEqualPush();
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED GREATER NODE");
    }

int GreaterNode::Evaluate() {
    return mLeftNode->Evaluate() > mRightNode->Evaluate();
}

void GreaterNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED GREATER EQUAL NODE");
    }

int GreaterEqualNode::Evaluate() {
    return mLeftNode->Evaluate() >= mRightNode->Evaluate();
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterEqualPush();
}


EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED EQUAL NODE");
    }

int EqualNode::Evaluate() {
    return mLeftNode->Evaluate() == mRightNode->Evaluate();
}

void EqualNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopEqualPush();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED NOT EQUAL NODE");
    }

int NotEqualNode::Evaluate() {
    return mLeftNode->Evaluate() != mRightNode->Evaluate();
}

void NotEqualNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopNotEqualPush();
}

AndNode::AndNode(ExpressionNode * left, ExpressionNode * right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED AND NODE");
    }

int AndNode::Evaluate() {
    return mLeftNode->Evaluate() && mRightNode->Evaluate();
} 

void AndNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}

OrNode::OrNode(ExpressionNode * left, ExpressionNode * right)
    :BinaryOperatorNode(left,right) {
        MSG("CREATED OR NODE");
    }

int OrNode::Evaluate() {
    return mLeftNode->Evaluate() || mRightNode->Evaluate();
} 

void OrNode::CodeEvaluate(InstructionsClass& machineCode){
    mLeftNode->CodeEvaluate(machineCode);
    mRightNode->CodeEvaluate(machineCode);
    machineCode.PopPopOrPush();
}