#include <fstream>
#include <stdlib.h>
#include "Token.h"
#include "Scanner.h"
#include "StateMachine.h"
#include "Debug.h"

ScannerClass::ScannerClass(std::string filename) {
    MSG("Initialzing Scanner object")
    mFin.open(filename,std::ifstream::in);
    if (!mFin.is_open()) {
        std::cout <<"ERROR: unable to open file: " << filename;
        exit(EXIT_FAILURE);
    } 
    mLineNumber = 1;
    MSG("Scanner object created!")
}

ScannerClass::~ScannerClass() {
    mFin.close();
    MSG("Scanner object destroyed.")

}

TokenClass ScannerClass::GetNextToken() {
    StateMachineClass stateMachine;
    MachineState state = START_STATE;
    TokenType CTT;
    std::string lexeme;
    do {
        char c = mFin.get();
        
        state = stateMachine.UpdateState(c,CTT);
        //if (state != CANTMOVE_STATE) {
        lexeme+=c;
        //}
        if (state == START_STATE || state == COMMENT_STATE) {
            lexeme = "";
        }
        if (c == '\n' && state != CANTMOVE_STATE) {
            mLineNumber+=1;
        }
        
    } while(state != CANTMOVE_STATE);
    mFin.unget();
    if (CTT == BAD_TOKEN) {
        std::cout << "Error: BAD_TOKEN_TYPE on " << lexeme << std::endl;
        exit(EXIT_FAILURE);
    } 
    lexeme.pop_back();
    TokenClass token(CTT,lexeme);
    token.CheckReserved();
    
    return token;
}

TokenClass ScannerClass::PeekNextToken() {
    MSG("PEEKING TOKEN")
    int pos = mFin.tellg();
    int currentLine = mLineNumber;
    TokenClass tx = GetNextToken();
    if (!mFin) {
        mFin.clear();
    }
    mLineNumber = currentLine;
    mFin.seekg(pos);
    MSG("TOKEN PEEKED")
    return tx;
}
