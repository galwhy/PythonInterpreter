#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <cassert>
#include "Token.h"
#include "ByteCode.h"
#include "AbstractSyntaxTree.h"
#include "CodeObject.h"

using namespace std;
typedef void (*voidFunctionType)(int);
typedef map<OpCodeCommands, voidFunctionType> MapCall;

class Interpreter
{
private:
	stack<Token*> CallStack;
	MapCall byteCodeMap;
	CodeObject* codeObject;
	int ByteCodePointer;

public:
	Interpreter(CodeObject* codeObject);
	
	void Interprete(vector<ByteCode*>* byteCodeList);

	void LoadConst(int index);

	void LoadFast(int index);

	void StoreFast(int index);

	void BinaryAdd(int index);

	void BinarySubtract(int index);

	void BinaryMultiply(int index);

	void BinaryDivide(int index);

	void LoadGlobal(int index);

	void CallFunction(int index);

	void PopTop(int index);

	void CompareOp(int index);

	void GetIter(int index);

	void ForIter(int index);

	void JumpIfFalse(int index);

	void JumpIfTrue(int index);

	void JumpAbsolute(int index);

	void ReturnValue(int index);

};