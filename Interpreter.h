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
	stack<Object*> CallStack;
	MapCall byteCodeMap;
	CodeObject* codeObject;
	int ByteCodePointer;
	static Interpreter* instance;
	Interpreter(CodeObject* codeObject);

public:
	static Interpreter* getInstance(CodeObject* codeObject);

	void Interprete(vector<ByteCode*>* byteCodeList);

	void static LoadConst(int index);

	void static LoadFast(int index);

	void static StoreFast(int index);

	void static BinaryAdd(int index);

	void static BinarySubtract(int index);

	void static BinaryMultiply(int index);

	void static BinaryDivide(int index);

	void static LoadGlobal(int index);

	void static CallFunction(int index);

	void static PopTop(int index);

	void static CompareOp(int index);

	void static GetIter(int index);

	void static ForIter(int index);

	void static JumpIfFalse(int index);

	void static JumpIfTrue(int index);

	void static JumpAbsolute(int index);

	void static JumpForward(int index);

	void static binarySubscr(int index);

	void static ReturnValue(int index);

	void static Print(vector<Object*> operators);

};