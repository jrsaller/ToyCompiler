#include <iostream>
#include <string>
#include "Token.h"
#include "Scanner.h"


int main() {
    ScannerClass scanner("testfile.cpp");
    TokenClass NextToken;
    while(true) {
        NextToken = scanner.GetNextToken();
        std::cout << "Line " << scanner.GetLineNumber() << ": " <<  NextToken << std::endl;
        if (NextToken.GetTokenType() == ENDFILE_TOKEN) {
            break;
        }
    }

    return 0;
}