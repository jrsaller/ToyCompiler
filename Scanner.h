#ifndef SCANNER
#define SCANNER

#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"

class ScannerClass {
    public:
        
        ScannerClass(std::string filename);
        ~ScannerClass();
        TokenClass GetNextToken();
        int GetLineNumber() const { return mLineNumber; }
    private:
        std::ifstream mFin;
        int mLineNumber;
};


#endif // SCANNER