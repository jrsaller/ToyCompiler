#include <sstream>
#include <stdlib.h>
#include "Node.h"
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

//OK
StartNode * ParserClass::Start() {
    ProgramNode *pn = Program();
    Match(ENDFILE_TOKEN);
    StartNode * sn = new StartNode(pn);
    return sn;
}

//OK
ProgramNode *  ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode * bn = Block();
    ProgramNode * p = new ProgramNode(bn);
    return p;
}

//OK
BlockNode *  ParserClass::Block() {
    MSG("Block");
    Match(LCURLY_TOKEN);
    StatementGroupNode * s = StatementGroup();
    Match(RCURLY_TOKEN);
    BlockNode * b = new BlockNode(s);
    return b;
}

//OK
StatementGroupNode * ParserClass::StatementGroup() {
    MSG("Statement Group")
    StatementGroupNode * s = new StatementGroupNode();
    while(true) {
        StatementNode * result = Statement();
        if (!result) {
            return s;
        } else {
            s->AddStatement(result);
        }
    }
}

//OK
StatementNode *  ParserClass::Statement() {
    MSG("Statement");
    TokenClass tt = mScanner->PeekNextToken();
    TokenType t = tt.GetTokenType();
    if (t==INT_TOKEN) {
        DeclarationStatementNode * s = DeclarationStatement();
        return s;
    } else if (t==IDENTIFIER_TOKEN) {
        AssignmentStatementNode * s =  AssignmentStatement();
        return s;
    } else if (t==COUT_TOKEN) {
        CoutStatementNode * s = CoutStatement();
        return s;
    } else if (t == LCURLY_TOKEN) {
        BlockNode * s = Block();
        return s;
    } else if (t==IF_TOKEN) {
        IfStatementNode * s = IfStatement();
        return s;
    } else if (t==WHILE_TOKEN) {
        WhileStatementNode * s = WhileStatement();
        return s;
    } else   {
        return 0;
    }
}


DeclarationStatementNode * ParserClass::DeclarationStatement(){
    MSG("Declaration Statement");
    Match(INT_TOKEN);
    IdentifierNode * s = Identifier();
    Match(SEMICOLON_TOKEN);
    DeclarationStatementNode * d = new DeclarationStatementNode(s);
    return d;
}
AssignmentStatementNode * ParserClass::AssignmentStatement(){
    MSG("Assignment Statement");
    IdentifierNode * id = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode * e = Expression();
    Match(SEMICOLON_TOKEN);
    return new AssignmentStatementNode(id,e);
}
CoutStatementNode * ParserClass::CoutStatement(){
    MSG("Cout Statement");
    std::vector<ExpressionNode*> nodes;
    Match(COUT_TOKEN);
    //needs endl or expression
    TokenClass tt = mScanner->PeekNextToken();
    TokenType t = tt.GetTokenType();
    do {
        Match(INSERTION_TOKEN);
        t = mScanner->PeekNextToken().GetTokenType();
        if (t == ENDL_TOKEN) {
            Match(t);
            nodes.push_back(NULL);
        }else{
            ExpressionNode * e = Expression();
            nodes.push_back(e);
        }
    } while (mScanner->PeekNextToken().GetTokenType() == INSERTION_TOKEN);
    Match(SEMICOLON_TOKEN);
    return new CoutStatementNode(nodes);
}

IfStatementNode * ParserClass::IfStatement() {
    MSG("If Statement");
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * expression = Expression();
    Match(RPAREN_TOKEN);
    StatementNode * statement = Statement();
    return new IfStatementNode(expression,statement);
}


WhileStatementNode * ParserClass::WhileStatement() {
    MSG("While Statement");
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode * expression = Expression();
    Match(RPAREN_TOKEN);
    StatementNode * statement = Statement();
    return new WhileStatementNode(expression,statement);
}

ExpressionNode * ParserClass::Expression() {
    MSG("Expression");
    ExpressionNode * e = Or();
    return e;
}

ExpressionNode * ParserClass::Or() {
    MSG("Parser.cpp : Or");
    ExpressionNode * current = And();
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt==OR_TOKEN) {
            Match(tt);
            current = new OrNode(current,And());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::And() {
    MSG("Parser.cpp : And");
    ExpressionNode * current = Relational();
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt==AND_TOKEN) {
            Match(tt);
            current = new AndNode(current,Relational());
        } else {
            return current;
        }
    }
}

ExpressionNode * ParserClass::Relational() {
    MSG("Parser.cpp : Relational");
    ExpressionNode * current = PlusMinus();
    //Handle Optional tail
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt==LESS_TOKEN) {
        Match(tt);
        current = new LessNode(current,PlusMinus());
    } else if (tt == LESSEQUAL_TOKEN) {
        Match(tt);
        current = new LessEqualNode(current,PlusMinus());
    } else if (tt == GREATER_TOKEN) {
        Match(tt);
        current = new GreaterNode(current,PlusMinus());
    } else if (tt == GREATEREQUAL_TOKEN) {
        Match(tt);
        current = new GreaterEqualNode(current,PlusMinus());
    } else if (tt == EQUAL_TOKEN) {
        Match(tt);
        current = new EqualNode(current,PlusMinus());
    } else if (tt == NOTEQUAL_TOKEN){
        Match(tt);
        current = new NotEqualNode(current,PlusMinus());
    }
    return current;
}

ExpressionNode * ParserClass::PlusMinus() {
    MSG("Parser.cpp : Plus Minus");
    ExpressionNode * current = TimesDivide();
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt==PLUS_TOKEN) {
            Match(tt);
            current = new PlusNode(current,TimesDivide());
        } else if (tt == MINUS_TOKEN) {
            Match(tt);
            current = new MinusNode(current,TimesDivide());
        } else {
            MSG("LEAVING PARSERCLASS::PLUSMINUS")
            return current;
        }
    }
}

ExpressionNode * ParserClass::TimesDivide() {
    MSG("Parser.cpp : Times Divide");
    ExpressionNode * current = Factor();
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if (tt == TIMES_TOKEN) {
            Match(tt);
            current = new  TimesNode(current,Factor());
        } else if (tt == DIVIDE_TOKEN) {
            Match(tt);
            current = new DivideNode(current,Factor());
        } else {
            MSG("LEAVING PARSERCLASS::TIMESDIVIDE")
            return current;
        }
    }
}


ExpressionNode * ParserClass::Factor() {
    MSG("Parser.cpp : Factor");
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == IDENTIFIER_TOKEN) {
        return Identifier();
    } else if (tt == INTEGER_TOKEN) {
        return Integer();
    } else if (tt == LPAREN_TOKEN) {
        Match(tt);
        ExpressionNode * e = Expression();
        Match(RPAREN_TOKEN);
    } else {
        std::cerr << "In ParserClass::Factor, unexpected token \"" << TokenClass::GetTokenTypeName(tt) << std::endl;
        exit(1);
    }
}

IdentifierNode * ParserClass::Identifier() {
    MSG("Parser.cpp : Identifier");
    TokenClass t = Match(IDENTIFIER_TOKEN);
    //Use lexeme to make and return ID node
    std::string lex = t.GetLexeme();
    IdentifierNode * id = new IdentifierNode(lex,mSymbolTable);
    return id;


}

IntegerNode * ParserClass::Integer() {
    MSG("Parser.cpp : Integer")
    TokenClass t = Match(INTEGER_TOKEN);
    std::string lex = t.GetLexeme();
    int num = atoi(lex.c_str());
    IntegerNode * n = new IntegerNode(num);
    MSG("LEAVING INTEGER");
    return n;
}