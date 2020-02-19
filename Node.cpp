#include "Node.h"

Node::~Node() {}

StartNode::StartNode(ProgramNode* node) {
    this->node = node;
}

StartNode::~StartNode() {
    delete(node);
}

ProgramNode::ProgramNode(BlockNode* node){
    this->node = node;
}

ProgramNode::~ProgramNode(){
    delete(node);
}

BlockNode::BlockNode(StatementGroupNode* node) {
    this->node = node;
}

BlockNode::~BlockNode() {
    delete(node);
}

StatementGroupNode::StatementGroupNode() {

}

StatementGroupNode::~StatementGroupNode() {
    for (int i = 0;i<nodes.size();i++) {
        delete(nodes[i]);
    }
}

void StatementGroupNode::AddStatement(StatementNode* node) {
    nodes.push_back(node);
}

StatementNode::~StatementNode() {}
