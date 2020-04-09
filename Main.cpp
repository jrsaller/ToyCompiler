#include <iostream>
#include <string>
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include "Parser.h"

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
/*int main() {
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
    s.AddEntry("hello");
    std::cout << "DOES DANG HAVE AN INDEX? " << s.GetIndex("dang") << std::endl;
}*/

//CHAPTER 5: NODE PASS OFF

/*int main() {
    //Start Node
    //  Program Node
    //      BlockNode
    //          StatementGroup Node
    //              Statement Nodes (Declaration,Assignment,etc.)
    SymbolTableClass* st = new SymbolTableClass();
    
    IntegerNode* i1 = new IntegerNode(12);
    CoutStatementNode* c1 = new CoutStatementNode(i1);
    IntegerNode* i2 = new IntegerNode(8);    
    CoutStatementNode* c2 = new CoutStatementNode(i2);
    
    IntegerNode* plus1 = new IntegerNode(15);
    IntegerNode* plus2 = new IntegerNode(5);
    PlusNode* plus = new PlusNode(plus1,plus2);
    IdentifierNode* id = new IdentifierNode("total",st);
    AssignmentStatementNode* an = new AssignmentStatementNode(id,plus);
    
    IntegerNode* minus1 = new IntegerNode(5);
    IntegerNode* minus2 = new IntegerNode(5);
    MinusNode* minus = new MinusNode(minus1,minus2);
    IdentifierNode* id1 = new IdentifierNode("min_total",st);
    AssignmentStatementNode* an1 = new AssignmentStatementNode(id1,minus);
    
    IntegerNode* times1 = new IntegerNode(7);
    IntegerNode* times2 = new IntegerNode(10);
    TimesNode* times = new TimesNode(times1,times2);
    IdentifierNode* id2 = new IdentifierNode("times_total",st);
    AssignmentStatementNode* an2 = new AssignmentStatementNode(id2,times);

    IntegerNode* divide1 = new IntegerNode(72);
    IntegerNode* divide2 = new IntegerNode(12);
    DivideNode* divide = new DivideNode(divide1,divide2);
    IdentifierNode* id3 = new IdentifierNode("div_total",st);
    AssignmentStatementNode* an3 = new AssignmentStatementNode(id3,divide);

    //less
    IntegerNode* less1 = new IntegerNode(72);
    IntegerNode* less2 = new IntegerNode(12);
    LessNode* l = new LessNode(less1,less2);
    IdentifierNode* lenode = new IdentifierNode("lessnode",st);
    AssignmentStatementNode* an4 = new AssignmentStatementNode(lenode,l);

    //lessequal
    IntegerNode* lessequal1 = new IntegerNode(72);
    IntegerNode* lessequal2 = new IntegerNode(12);
    LessEqualNode* l1 = new LessEqualNode(lessequal1,lessequal2);
    IdentifierNode* lessequalnode = new IdentifierNode("lessequalnode",st);
    AssignmentStatementNode* an5 = new AssignmentStatementNode(lessequalnode,l1);
    
    //greater
    IntegerNode* greater1 = new IntegerNode(72);
    IntegerNode* greater2 = new IntegerNode(12);
    GreaterNode* l2 = new GreaterNode(greater1,greater2);
    IdentifierNode* greaternode = new IdentifierNode("greaternode",st);
    AssignmentStatementNode* an6 = new AssignmentStatementNode(greaternode,l2);
    
    //greaterequal
    IntegerNode* ge1 = new IntegerNode(72);
    IntegerNode* ge2 = new IntegerNode(12);
    GreaterEqualNode* l3 = new GreaterEqualNode(ge1,ge2);
    IdentifierNode* greaterequalnode = new IdentifierNode("greaterequalnode",st);
    AssignmentStatementNode* an7 = new AssignmentStatementNode(greaterequalnode,l3);
    
    //equal
    IntegerNode* equal1 = new IntegerNode(72);
    IntegerNode* equal2 = new IntegerNode(12);
    EqualNode* l4 = new EqualNode(equal1,equal2);
    IdentifierNode* equalnode = new IdentifierNode("equalnode",st);
    AssignmentStatementNode* an8 = new AssignmentStatementNode(equalnode,l4);
    
    //notequal
    IntegerNode* ne1 = new IntegerNode(72);
    IntegerNode* ne2 = new IntegerNode(12);
    NotEqualNode* l5 = new NotEqualNode(ne1,ne2);
    IdentifierNode* notequalnode = new IdentifierNode("notequalnode",st);
    AssignmentStatementNode* an9 = new AssignmentStatementNode(notequalnode,l5);
    
    IdentifierNode* id10 = new IdentifierNode("val",st);
    DeclarationStatementNode* an10 = new DeclarationStatementNode(id10);
    
    
    
    StatementGroupNode* sg = new StatementGroupNode();
    sg->AddStatement(c1);
    sg->AddStatement(c2);
    sg->AddStatement(an);
    sg->AddStatement(an1);
    sg->AddStatement(an2);
    sg->AddStatement(an3);
    sg->AddStatement(an4);
    sg->AddStatement(an5);
    sg->AddStatement(an6);
    sg->AddStatement(an7);
    sg->AddStatement(an8);
    sg->AddStatement(an9);
    sg->AddStatement(an10);
    BlockNode* b = new BlockNode(sg);
    ProgramNode* p = new ProgramNode(b);
    StartNode* s = new StartNode(p);
    delete(s);
    std::cout << false << std::endl;
}
*/

/*
int main() {
    ScannerClass scanner("testfile.cpp");
    SymbolTableClass st;
    ParserClass parse(&scanner,&st);
    StartNode * sn = parse.Start();
    sn->Interpret();
    
    std::cout << "You've got valid code!" << std::endl;
    delete sn;
    return 0;
}*/

using namespace std;
int main()
{
	unsigned char mCode[] = {0x55, 0x8B, 0xEC, 0X5d, 0XC3};
	cout << "About to Execute the machine code...\n";
	void * ptr = mCode;
	void (*f)(void);
	f = (void (*)(void)) ptr ;
	f(); // call the array as if it were a function
	cout << "There and back again!\n\n";
	return 0;
}
