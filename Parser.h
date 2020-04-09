#ifndef PARSER
#define PARSER
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"

class ParserClass {
    public:
        ParserClass(ScannerClass * scanner,SymbolTableClass * st);
        StartNode * Start();
    private:
        TokenClass Match(TokenType expectedType);
        ProgramNode * Program();
        void Term();
        BlockNode * Block();
        StatementGroupNode * StatementGroup();
        StatementNode * Statement();
        ExpressionNode * Expression();
        ExpressionNode * Or();
        ExpressionNode * And();
        ExpressionNode * Relational();
        ExpressionNode * PlusMinus();
        ExpressionNode * TimesDivide();
        ExpressionNode * Factor();
        IdentifierNode * Identifier();
        IntegerNode * Integer();
        DeclarationStatementNode * DeclarationStatement();
        AssignmentStatementNode * AssignmentStatement();
        CoutStatementNode * CoutStatement();
        IfStatementNode * IfStatement();
        WhileStatementNode * WhileStatement();
        ScannerClass * mScanner;
        SymbolTableClass * mSymbolTable;
};




#endif