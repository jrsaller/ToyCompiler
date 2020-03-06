#include <sstream>
#include "Parser.h"
#include "Token.h"
#include "Scanner.h"
#include "Debug.h"

ParserClass::ParserClass(ScannerClass * scanner, SymbolTableClass * st) {
    mScanner = scanner;
    mSymbolTable = st;
}

TokenClass ParserClass::Match(TokenType expectedType) {
    TokenClass currentToken = mScanner->GetNextToken();
    if (currentToken.GetTokenType() != expectedType) {
        std::cerr << "Error in ParserClass::Match" << std::endl;
        std::cerr << "Line " << mScanner->GetLineNumber() << ": Expected Token " << TokenClass::GetTokenTypeName(expectedType) << ", but got type " << currentToken.GetTokenTypeName() << std::endl;
        exit(1);
    }
    std::stringstream ss;
    ss << "\tSuccessful match Token Type: " << currentToken.GetTokenTypeName() << "/ Lexeme: \"" << currentToken.GetLexeme() << "\"";
    MSG(ss.str());
    return currentToken;
}


void ParserClass::Start() {
    Program();
    Match(ENDFILE_TOKEN);
}

void ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    Block();
}

void ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroup();
    Match(RCURLY_TOKEN);
}

void ParserClass::StatementGroup() {
    MSG("Statement Group")
    while(true) {
        bool result = Statement();
        if (result == false) {
            return;
        }
    }
}

bool ParserClass::Statement() {
    MSG("Statement");
    TokenClass tt = mScanner->PeekNextToken();
    MSG("Fin peek token in Statement")
    TokenType t = tt.GetTokenType();
    if (t==INT_TOKEN) {
        DeclarationStatement();
        return true;
    } else if (t==IDENTIFIER_TOKEN) {
        AssignmentStatement();
        return true;
    } else if (t==COUT_TOKEN) {
        CoutStatement();
        return true;
    } else if (t == LPAREN_TOKEN) {
        Block();
        return true;
    } else  {
        return false;
    }
}

void ParserClass::DeclarationStatement(){
    MSG("Declaration Statement");
    Match(INT_TOKEN);
    Identifier();
    Match(SEMICOLON_TOKEN);
}
void ParserClass::AssignmentStatement(){
    MSG("Assignment Statement");
    Identifier();
    Match(ASSIGNMENT_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
}
void ParserClass::CoutStatement(){
    MSG("cout statement");
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
}

void ParserClass::Expression() {
    MSG("Expression");
    Relational();
}

void ParserClass::Relational() {
    MSG("Relational");
    PlusMinus();
    //Handle Optional tail
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt==LESS_TOKEN) {
        Match(tt);
        PlusMinus();
    } else if (tt == LESSEQUAL_TOKEN) {
        Match(tt);
        PlusMinus();
    } else if (tt == GREATER_TOKEN) {
        Match(tt);
        PlusMinus();
    } else if (tt == GREATEREQUAL_TOKEN) {
        Match(tt);
        PlusMinus();
    } else if (tt == EQUAL_TOKEN) {
        Match(tt);
        PlusMinus();
    } else if (tt == NOTEQUAL_TOKEN){
        Match(tt);
        PlusMinus();
    }else {
        return;
    }
}

void ParserClass::PlusMinus() {
    MSG("Plus Minus");
    TimesDivide();
    MSG("FINISH TIMES DIVIDE")
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt==PLUS_TOKEN) {
            Match(tt);
            TimesDivide();
        } else if (tt == MINUS_TOKEN) {
            Match(tt);
            TimesDivide();
        } else {
            return;
        }
    }
}

void ParserClass::TimesDivide() {
    MSG("Times Divide");
    Factor();
    MSG("FINISH FACTOR");
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == TIMES_TOKEN) {
            Match(tt);
            Factor();
        } else if (tt == DIVIDE_TOKEN) {
            Match(tt);
            Factor();
        } else {
            return;
        }
    }
}

void ParserClass::Factor() {
    MSG("Factor");
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == IDENTIFIER_TOKEN) {
        Identifier();
    } else if (tt == INTEGER_TOKEN) {
        Integer();
    } else if (tt == LPAREN_TOKEN) {
        Match(tt);
        Expression();
        Match(RPAREN_TOKEN);
    } else {
        std::cerr << "In ParserClass::Factor, unexpected token \"" << TokenClass::GetTokenTypeName(tt) << std::endl;
        exit(1);
    }
}

void ParserClass::Identifier() {
    Match(IDENTIFIER_TOKEN);
}

void ParserClass::Integer() {
    Match(INTEGER_TOKEN);
}