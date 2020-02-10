#ifndef STATEMACHINE
#define STATEMACHINE
#include "Token.h"

enum MachineState {
    START_STATE,IDENTIFIER_STATE, INTEGER_STATE,CANTMOVE_STATE,
    //Relational Operator States
    EQUAL_STATE,LESS_STATE,LESSEQUAL_STATE,GREATER_STATE,GREATEREQUAL_STATE,NOTEQUAL_STATE,
	// Other Operators States
	INSERTION_STATE, ASSIGNMENT_STATE, PLUS_STATE, MINUS_STATE, TIMES_STATE, DIVIDE_STATE,
	// Other STATES
	SEMICOLON_STATE, LPAREN_STATE, RPAREN_STATE, LCURLY_STATE, RCURLY_STATE,
	ENDFILE_STATE, COMMENT_STATE, LINECOMMENT_STATE,HALFENDCOMMENT_STATE, NOT_STATE,
    NUM_STATES
};

enum CharacterType {
    LETTER_CHAR,DIGIT_CHAR, BAD_CHAR, WHITESPACE_CHAR,NEWLINE_CHAR,
    //Relational Operator States
    LESS_CHAR,GREATER_CHAR,EQUAL_CHAR,
	// Other Operators:
	PLUS_CHAR, DASH_CHAR, STAR_CHAR, FSLASH_CHAR,BSLASH_CHAR,
	// Other Characters:
	SEMICOLON_CHAR, LPAREN_CHAR, RPAREN_CHAR, LCURLY_CHAR, RCURLY_CHAR, UNDERSCORE_CHAR,EXCLAMATION_CHAR,
	// Other Token Types
    ENDFILE_CHAR,
    NUM_CHARS
};

class StateMachineClass {
    public:
        StateMachineClass();

        MachineState UpdateState(char currentCharacter,TokenType & correspondingTokenType);
    private:
        MachineState mCurrentState;
        MachineState mLegalMoves[NUM_STATES][NUM_CHARS];

        TokenType mCorrespondingTokenTypes[NUM_STATES];
};

#endif // STATEMACHINE