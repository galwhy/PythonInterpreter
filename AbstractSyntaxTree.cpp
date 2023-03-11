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

AbstractSyntaxTree::AbstractSyntaxTree(Token* Value)
{
	RootNode* root = new RootNode(Value);
	this->Root = root;
}

AbstractSyntaxTree::AbstractSyntaxTree(Token* Value, Node* Parent)
{
	RootNode* root = new RootNode(Value, Parent);
	this->Root = root;
}

void AbstractSyntaxTree::ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList)
{
	Root->ToByteCode(codeObject, ByteCodeList);
}

//void AbstractSyntaxTree::InsertChild(AbstractSyntaxTree* syntaxTree)
//{
//	this->Children->push_back(syntaxTree);
//}
//
//AbstractSyntaxTree* AbstractSyntaxTree::GetParent()
//{
//	if (this->Parent != NULL)
//	{
//		return Parent;
//	}
//}
//
//AbstractSyntaxTree* AbstractSyntaxTree::GetChild(int index)
//{
//	return this->Children->at(index);
//}
//
//AbstractSyntaxTree* AbstractSyntaxTree::GetLastChild()
//{
//	return this->Children->at(this->Children->size()-1);
//}