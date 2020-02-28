#ifndef SYMBOL
#define SYMBOL
#include <string>
#include <vector>

class SymbolTableClass {
    public:
        bool Exists(const std::string & s);
        //return True is <s> already exists in the symbol table
        
        void AddEntry(const std::string & s);
        //adds <s> to the symbol table
        //OR quit if s already exists already there
        
        int GetValue(const std::string & s);
        //return the current value of variable <s>, on interpret
        // Meaningless on Code and Execute
        //Print a message and quit if variable <s> does not exist
        
        void SetValue(const std::string & s,int v);
        //set variable <s> to given value on interpret
        //Meaningless on Code and Execute
        //print a message and quit if <s> does not exist

        int GetIndex(const std::string & s);
        //return the index of where variable <s> is
        //return -1 if <s> is not found
        int GetCount();
        //return the current number of varibles in the symbol table
    private:
        struct Variable{
            std::string mLabel;
            int mValue;
        };
        std::vector<Variable> SymbolTable;

};

#endif