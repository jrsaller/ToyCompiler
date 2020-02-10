#include <iostream>
#include <string>
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"

//TOKEN CLASS PASS OFF
/* int main() {
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
} */
//SYMBOL TABLE TESTING/PASSOFF
int main() {
    SymbolTableClass s = SymbolTableClass();
    std::cout << "DOES IT EXIST? " << s.Exists("hello") << std::endl;
    s.AddEntry("hello");
    s.SetValue("hello",10);
   
    std::cout << "hello" << std::endl;
    std::cout << "DOES IT EXIST NOW? " << s.Exists("hello") << std::endl;
    std::cout << "WHAT IS THE VALUE? " << s.GetValue("hello") << std::endl;
    std::cout << "WHAT IS THE INDEX? " << s.GetIndex("hello") << std::endl;
    std::cout << "WHAT IS THE NUMBER OF VARIABLES? " << s.GetCount() << std::endl;
    s.AddEntry("world");
    s.SetValue("world",45);
    std::cout << "world" << std::endl;
    std::cout << "DOES IT EXIST NOW? " << s.Exists("world") << std::endl;
    std::cout << "WHAT IS THE VALUE? " << s.GetValue("world") << std::endl;
    std::cout << "WHAT IS THE INDEX? " << s.GetIndex("world") << std::endl;
    std::cout << "WHAT IS THE NUMBER OF VARIABLES? " << s.GetCount() << std::endl;
    //s.AddEntry("hello");
    std::cout << "DOES DANG HAVE AN INDEX? " << s.GetIndex("dang") << std::endl;
}