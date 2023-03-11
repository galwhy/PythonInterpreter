#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "CodeObject.h"
#include "ByteCode.h"

using namespace std;

class Node
{
public:

	Token* Value;
	vector<Node*>* Children;
	Node* Parent;

	Node();

	Node(Token* Value);

	Node(Token* Value, Node* Parent);

	void InsertChild(Node* node);

	Node* GetParent();

	Node* GetChild(int index);

	Node* GetLastChild();

	virtual void ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList) {};
};

class RootNode : public Node
{
public:
	RootNode();

	RootNode(Token* Value);

	RootNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList);
};

class EqualNode : public Node
{
public:
	EqualNode();

	EqualNode(Token* Value);

	EqualNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList);
};

class OperatorNode : public Node
{
public:
	OperatorNode();

	OperatorNode(Token* Value);

	OperatorNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList);
};

class GlobalNode : public Node
{
public:
	GlobalNode();

	GlobalNode(Token* Value);

	GlobalNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList);
};
