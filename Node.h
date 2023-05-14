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

	virtual ~Node();

	Node(Token* Value);

	Node(Token* Value, Node* Parent);

	void InsertChild(Node* node);

	Node* GetParent();

	Node* GetChild(int index);

	Node* GetLastChild();

	void CheckChild(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList, Node* child);

	virtual void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList) {};
};

class RootNode : public Node
{
public:
	RootNode();

	RootNode(Token* Value);

	RootNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class EqualNode : public Node
{
public:
	EqualNode();

	EqualNode(Token* Value);

	EqualNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class IteratorNode : public Node
{
public:
	IteratorNode();

	IteratorNode(Token* Value);

	IteratorNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class OperatorNode : public Node
{
public:
	OperatorNode();

	OperatorNode(Token* Value);

	OperatorNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class GlobalNode : public Node
{
public:
	GlobalNode();

	GlobalNode(Token* Value);

	GlobalNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class IndexNode : public Node
{
public:
	IndexNode();

	IndexNode(Token* Value);

	IndexNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class CompareNode : public Node
{
public:
	CompareNode();

	CompareNode(Token* Value);

	CompareNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class BranchNode : public Node
{
public:
	BranchNode();

	BranchNode(Token* Value);

	BranchNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class EndBranchNode : public Node
{
public:
	EndBranchNode();

	EndBranchNode(Token* Value);

	EndBranchNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class BoolNode : public Node
{
public:
	BoolNode();

	BoolNode(Token* Value);

	BoolNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};

class ReturnNode : public Node
{
public:
	ReturnNode();

	ReturnNode(Token* Value);

	ReturnNode(Token* Value, Node* Parent);

	void ToByteCode(CodeObject& codeObject, vector<ByteCode*>& ByteCodeList);
};