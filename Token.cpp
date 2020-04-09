#include <string>
#include <iostream>
#include "Token.h"
#include "Debug.h"

TokenClass::TokenClass(){};
TokenClass::TokenClass(TokenType type, const std::string & lexeme){
    MSG("Creating Token with")
    MSG(GetTokenTypeName(type));
    MSG(lexeme);
    mType=type;
    mLexeme=lexeme;
    MSG("Token Created")
};

void TokenClass::CheckReserved(){
    if (mLexeme == "void") {
        mType = VOID_TOKEN;
    } else if (mLexeme == "main") {
        mType = MAIN_TOKEN;
    } else if (mLexeme == "int") {
        mType=INT_TOKEN;
    } else if (mLexeme == "cout") {
        mType=COUT_TOKEN;
    } else if (mLexeme == "if") {
        mType=IF_TOKEN;
    } else if (mLexeme == "while") {
        mType = WHILE_TOKEN;
    }
}
std::ostream& operator<<(std::ostream & out, const TokenClass & tc){
    out << tc.GetTokenType() << " ";
    out << tc.GetTokenTypeName() << " ";
    out << tc.GetLexeme();
    return out;
}
