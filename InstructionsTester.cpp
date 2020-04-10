#include <iostream>
#include "Instructions.h"
using namespace std;
int main() {
	InstructionsClass code;
	
	code.PushValue(1000);
	code.PopAndWrite();

	code.PushVariable(10);
	code.PopAndStore(11);
	code.PushVariable(10);
	code.PushVariable(11);
	code.PopPopAddPush();
	code.PopAndWrite();

	code.PushValue(10);
	code.PushValue(5);
	code.PopPopSubPush();
	code.PopAndWrite();

	code.PushValue(10);
	code.PushValue(5);
	code.PopPopMulPush();
	code.PopAndWrite();

	code.PushValue(10);
	code.PushValue(5);
	code.PopPopDivPush();
	code.PopAndWrite();

	code.PushValue(10);
	code.PushValue(5);
	code.PopPopLessPush();
	code.PopAndWrite();
	
	code.PushValue(10);
	code.PushValue(5);
	code.PopPopLessEqualPush();
	code.PopAndWrite();
	
	code.PushValue(10);
	code.PushValue(5);
	code.PopPopGreaterPush();
	code.PopAndWrite();
	
	code.PushValue(10);
	code.PushValue(5);
	code.PopPopGreaterEqualPush();
	code.PopAndWrite();
	
	code.PushValue(10);
	code.PushValue(5);
	code.PopPopEqualPush();
	code.PopAndWrite();
	
	code.PushValue(10);
	code.PushValue(5);
	code.PopPopNotEqualPush();
	code.PopAndWrite();
	
	code.PushValue(10);
	code.PushValue(5);
	code.PopPopAndPush();
	code.PopAndWrite();
	
	code.PushValue(10);
	code.PushValue(5);
	code.PopPopOrPush();
	code.PopAndWrite();

	code.Finish();
	code.Execute();
	cout << "Back to the test Main!"<< endl;
	return 0;
}
