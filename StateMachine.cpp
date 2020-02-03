#include "StateMachine.h"
#include "Debug.h"

StateMachineClass::StateMachineClass(){
    MSG("Initializing State Machine object...")
    mCurrentState = START_STATE;

    for (int i = 0; i< NUM_STATES;i++) {
        for (int j=0;j<NUM_CHARS;j++) {
            mLegalMoves[i][j] = CANTMOVE_STATE;
        }
    }

    mLegalMoves[START_STATE][LETTER_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[START_STATE][WHITESPACE_CHAR]= START_STATE;
    mLegalMoves[START_STATE][NEWLINE_CHAR]= START_STATE;
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][UNDERSCORE_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[START_STATE][DIGIT_CHAR]= INTEGER_STATE;
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
    mLegalMoves[START_STATE][EXCLAMATION_CHAR] = NOT_STATE;
    mLegalMoves[NOT_STATE][EQUAL_CHAR] = NOTEQUAL_STATE;
    mLegalMoves[START_STATE][LESS_CHAR]= LESS_STATE;
    mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
    mLegalMoves[LESS_STATE][EQUAL_CHAR] = LESSEQUAL_STATE;
    mLegalMoves[START_STATE][GREATER_CHAR]= GREATER_STATE;
    mLegalMoves[START_STATE][EQUAL_CHAR]= ASSIGNMENT_STATE;
    mLegalMoves[GREATER_STATE][EQUAL_CHAR] = GREATEREQUAL_STATE;;
    mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR]= EQUAL_STATE;
    mLegalMoves[START_STATE][PLUS_CHAR]= PLUS_STATE;
    mLegalMoves[START_STATE][DASH_CHAR]= MINUS_STATE;
    mLegalMoves[START_STATE][STAR_CHAR]= TIMES_STATE;
    mLegalMoves[START_STATE][FSLASH_CHAR]= DIVIDE_STATE;
    mLegalMoves[DIVIDE_STATE][STAR_CHAR]= COMMENT_STATE;
    mLegalMoves[DIVIDE_STATE][FSLASH_CHAR] = LINECOMMENT_STATE;
    mLegalMoves[START_STATE][SEMICOLON_CHAR]= SEMICOLON_STATE;
    mLegalMoves[START_STATE][LPAREN_CHAR]= LPAREN_STATE;
    mLegalMoves[START_STATE][RPAREN_CHAR]= RPAREN_STATE;
    mLegalMoves[START_STATE][LCURLY_CHAR]= LCURLY_STATE;
    mLegalMoves[START_STATE][RCURLY_CHAR]= RCURLY_STATE;
    mLegalMoves[START_STATE][ENDFILE_CHAR]= ENDFILE_STATE;
    for (int j=0;j<NUM_CHARS;j++) {
            mLegalMoves[COMMENT_STATE][j] = COMMENT_STATE;
            mLegalMoves[HALFENDCOMMENT_STATE][j] = COMMENT_STATE;
            mLegalMoves[LINECOMMENT_STATE][j] = LINECOMMENT_STATE;
    }
    mLegalMoves[COMMENT_STATE][ENDFILE_CHAR]= CANTMOVE_STATE;
    mLegalMoves[COMMENT_STATE][STAR_CHAR]= HALFENDCOMMENT_STATE;
    mLegalMoves[HALFENDCOMMENT_STATE][FSLASH_CHAR]= START_STATE;
    mLegalMoves[LINECOMMENT_STATE][NEWLINE_CHAR] = START_STATE;





    for (int i = 0;i< NUM_STATES;i++) {
        mCorrespondingTokenTypes[i]=BAD_TOKEN;
    }
    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenTypes[GREATER_STATE] =GREATER_TOKEN;
    mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenTypes[NOTEQUAL_STATE] =NOTEQUAL_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenTypes[RPAREN_STATE] =RPAREN_TOKEN;
    mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
    mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;

    MSG("State Machine object created!")

}
MachineState StateMachineClass::UpdateState(char currentCharacter,TokenType & correspondingTokenType){
    CharacterType charType=BAD_CHAR;
    if(isdigit(currentCharacter)) {
        charType=DIGIT_CHAR;
    } else if(isalpha(currentCharacter)) {
        charType=LETTER_CHAR;
    } else if(isspace(currentCharacter)) {
        charType=WHITESPACE_CHAR;
        if (currentCharacter == '\n') {
            charType = NEWLINE_CHAR;
        }
    } else if(currentCharacter == '+') {
        charType=PLUS_CHAR;
    } else if(currentCharacter == '<') {
        charType=LESS_CHAR;
    } else if(currentCharacter == '>') {
        charType=GREATER_CHAR;
    } else if(currentCharacter == '=') {
        charType=EQUAL_CHAR;
    } else if(currentCharacter == '-') {
        charType=DASH_CHAR;
    } else if(currentCharacter == '*') {
        charType=STAR_CHAR;
    } else if(currentCharacter == '/') {
        charType=FSLASH_CHAR;
    } else if(currentCharacter == '\\') { 
        charType=BSLASH_CHAR;
    } else if(currentCharacter == ';') {
        charType=SEMICOLON_CHAR;
    } else if(currentCharacter == '(') {
        charType=LPAREN_CHAR;
    } else if(currentCharacter == ')') {
        charType=RPAREN_CHAR;
    } else if(currentCharacter == '{') {
        charType=LCURLY_CHAR;
    } else if(currentCharacter == '}') {
        charType=RCURLY_CHAR;
    } else if(currentCharacter == '_') {
        charType=UNDERSCORE_CHAR;
    } else if (currentCharacter == -1) {
        charType = ENDFILE_CHAR;
    } else if (currentCharacter == '!') {
        charType = EXCLAMATION_CHAR;
    }

    correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
    mCurrentState = mLegalMoves[mCurrentState][charType];
    return mCurrentState;

}
