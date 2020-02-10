
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "Symbol.h"

bool SymbolTableClass::Exists(const std::string & s){
    for (int i=0;i<SymbolTable.size();i++) {
        if (SymbolTable[i].mLabel == s) {
            return true;
        }
    }
    return false;
}
        
void SymbolTableClass::AddEntry(const std::string & s){
        if (!Exists(s)) {
                Variable v = Variable();
                v.mLabel = s;
                SymbolTable.push_back(v);
        } else {
                std::cout << "Variable \"" << s << "\" already exists" << std::endl;
                std::cout << "Quitting" << std::endl;
                exit(EXIT_FAILURE);
        }
}
        //adds <s> to the symbol table
        //OR quit if s already exists already there
        
int SymbolTableClass::GetValue(const std::string & s){
        for (int i = 0;i<SymbolTable.size();i++) {
                if (SymbolTable[i].mLabel == s) {
                        return SymbolTable[i].mValue;
                }
        }
        std::cout << "Variable \"" << s << "\" does not exist" << std::endl;
        //QUIT HERE
        exit(EXIT_FAILURE);
}
        //return the current value of variable <s>, on interpret
        // Meaningless on Code and Execute
        //Print a message and quit if variable <s> does not exist
        
void SymbolTableClass::SetValue(const std::string & s,int v){
        for (int i=0;i<SymbolTable.size();i++) {
                if (SymbolTable[i].mLabel == s) {
                        SymbolTable[i].mValue=v;
                        return;
                }
        }
        std::cout << "Variable \"" << s << "\" does not exist" << std::endl;
        exit(EXIT_FAILURE);
        
}
        //set variable <s> to given value on interpret
        //Meaningless on Code and Execute
        //print a message and quit if <s> does not exist

int SymbolTableClass::GetIndex(const std::string & s){
        for (int i=0;i<SymbolTable.size();i++) {
                if (SymbolTable[i].mLabel == s) {
                        return i;
                }
        }
        return -1;
}
        //return the index of where variable <s> is
        //return -1 if <s> is not found
int SymbolTableClass::GetCount(){
        return SymbolTable.size();
}
        //return the current number of varibles in the symbol table