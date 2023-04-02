#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "ByteCode.h"
#include "AbstractSyntaxTree.h"
#include "CodeObject.h"

class Compiler
{
private:
	CodeObject* codeObject;
	vector<ByteCode*>* ByteCodeList;
	

public:
	Compiler();

	void Compile(AbstractSyntaxTree* syntaxTree);

	void BuildCode(Node* node);

	CodeObject* GetCodeObject();

	vector<ByteCode*>* GetByteCodeList();



	void ToString();
};