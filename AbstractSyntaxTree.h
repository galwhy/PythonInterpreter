#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "Node.h"
#include "ByteCode.h"

using namespace std;

class AbstractSyntaxTree
{
public:

	RootNode* Root;
	//Token* Value;
	//vector<AbstractSyntaxTree*>* Children;
	//AbstractSyntaxTree* Parent;

	AbstractSyntaxTree();

	~AbstractSyntaxTree();

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};
