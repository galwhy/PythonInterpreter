#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "AbstractSyntaxTree.h"
#include "Node.h"

AbstractSyntaxTree::AbstractSyntaxTree()
{
	RootNode* root = new RootNode();
	this->Root = root;
}

AbstractSyntaxTree::~AbstractSyntaxTree()
{
	delete this->Root;
}

void AbstractSyntaxTree::ToByteCode(CodeObject &codeObject, vector<ByteCode*> &ByteCodeList)
{
	Root->ToByteCode(codeObject, ByteCodeList);
}