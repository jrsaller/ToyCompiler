#ifndef PARSER
#define PARSER
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"

class ParserClass {
    public:
        ParserClass(ScannerClass * scanner,SymbolTableClass * st);
        void Start();
    private:
        TokenClass Match(TokenType expectedType);
        void Program();
        void Term();
        void Block();
        void StatementGroup();
        bool Statement();
        void Expression();
        void Relational();
        void PlusMinus();
        void TimesDivide();
        void Factor();
        void Identifier();
        void Integer();
        void DeclarationStatement();
        void AssignmentStatement();
        void CoutStatement();
        ScannerClass * mScanner;
        SymbolTableClass * mSymbolTable;
};




#endif