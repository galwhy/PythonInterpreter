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

	AbstractSyntaxTree(Token* Value);

	AbstractSyntaxTree(Token* Value, Node* Parent);

	void ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList);

	//void InsertChild(AbstractSyntaxTree* syntaxTree);

	//AbstractSyntaxTree* GetParent();

	//AbstractSyntaxTree* GetChild(int index);

	//AbstractSyntaxTree* GetLastChild();
};
