#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "Node.h"
#include "ByteCode.h"
#include "CodeObject.h"


Node::Node()
{
	this->Children = new vector<Node*>();
}

Node::Node(Token* Value)
{
	this->Value = Value;
	this->Children = new vector<Node*>();
}

Node::Node(Token* Value, Node* Parent)
{
	this->Value = Value;
	this->Children = new vector<Node*>();
	this->Parent = Parent;
}

void Node::InsertChild(Node* node)
{
	this->Children->push_back(node);
}

Node* Node::GetParent()
{
	if (this->Parent != NULL)
	{
		return Parent;
	}
}

Node* Node::GetChild(int index)
{
	return this->Children->at(index);
}

Node* Node::GetLastChild()
{
	return this->Children->at(this->Children->size() - 1);
}

void Node::CheckChild(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList, Node* child)
{
	if (child->Value->type == Type::Literal)
	{
		int index;
		for (int i = 1; i < codeObject->co_consts.size(); i++)
		{
			if (codeObject->co_consts.at(i)->Repr()  == child->Value->value)
			{
				index = i;
				break;
			}
		}
		ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, index);
		ByteCodeList->push_back(byteCode);
	}
	else if (child->Value->type == Type::Identifier)
	{
		int index;
		for (int i = 0; i < codeObject->co_varnames.size(); i++)
		{
			if (codeObject->co_varnames.at(i)->Repr() == child->Value->value)
			{
				index = i;
				break;
			}
		}
		ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_FAST, index);
		ByteCodeList->push_back(byteCode);
	}
	else
	{
		child->ToByteCode(codeObject, ByteCodeList);
	}
}



RootNode::RootNode() : Node() {};

RootNode::RootNode(Token* Value) : Node(Value) {};

RootNode::RootNode(Token* Value, Node* Parent) : Node(Value, Parent) {};

void RootNode::ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList)
{
	for (Node* child : *Children)
	{
		child->ToByteCode(codeObject, ByteCodeList);
	}
}



EqualNode::EqualNode() : Node() {};

EqualNode::EqualNode(Token* Value) : Node(Value) {};

EqualNode::EqualNode(Token* Value, Node* Parent) : Node(Value, Parent) {};

void EqualNode::ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList)
{
	CheckChild(codeObject, ByteCodeList, Children->at(1));

	//if (Children->at(1)->Value->type == Type::Literal)
	//{
	//	int index;
	//	for (int i = 1; i < codeObject->co_consts->size(); i++)
	//	{
	//		if (codeObject->co_consts->at(i)->value == Children->at(1)->Value->value)
	//		{
	//			index = i;
	//			break;
	//		}
	//	}
	//	ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, index);
	//	ByteCodeList->push_back(byteCode);
	//}
	//else if (Children->at(1)->Value->type == Type::Identifier)
	//{
	//	int index;
	//	for (int i = 0; i < codeObject->co_varnames->size(); i++)
	//	{
	//		if (codeObject->co_varnames->at(i)->value == Children->at(1)->Value->value)
	//		{
	//			index = i;
	//			break;
	//		}
	//	}
	//	ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_FAST, index);
	//	ByteCodeList->push_back(byteCode);
	//}
	//else
	//{
	//	Children->at(1)->ToByteCode(codeObject, ByteCodeList);
	//}

	int index;
	for (int i = 0; i < codeObject->co_varnames.size(); i++)
	{
		if (codeObject->co_varnames.at(i)->Repr() == Children->at(0)->Value->value)
		{
			index = i;
			break;
		}
	}
	ByteCode* byteCode = new ByteCode(OpCodeCommands::STORE_FAST, index);
	ByteCodeList->push_back(byteCode);
}



OperatorNode::OperatorNode() : Node() {};

OperatorNode::OperatorNode(Token* Value) : Node(Value) {};

OperatorNode::OperatorNode(Token* Value, Node* Parent) : Node(Value, Parent) {};

void OperatorNode::ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList)
{
	
	for (Node* child : *Children)
	{
		CheckChild(codeObject, ByteCodeList, child);
		/*if (child->Value->type == Type::Literal)
		{
			int index;
			for (int i = 1; i < codeObject->co_consts->size(); i++)
			{
				if (codeObject->co_consts->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, index);
			ByteCodeList->push_back(byteCode);
		}
		else if (child->Value->type == Type::Identifier)
		{
			int index;
			for (int i = 0; i < codeObject->co_varnames->size(); i++)
			{
				if (codeObject->co_varnames->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_FAST, index);
			ByteCodeList->push_back(byteCode);
		}
		else
		{
			child->ToByteCode(codeObject, ByteCodeList);
		}*/
	}
	
	ByteCode* byteCode;
	if (Value->value == "+")
		byteCode = new ByteCode(OpCodeCommands::BINARY_ADD);
	else if (Value->value == "-")
		byteCode = new ByteCode(OpCodeCommands::BINARY_SUBTRACT);

	else if (Value->value == "*")
		byteCode = new ByteCode(OpCodeCommands::BINARY_MULTIPLY);

	else if (Value->value == "/")
		byteCode = new ByteCode(OpCodeCommands::BINARY_DIVIDE);

	ByteCodeList->push_back(byteCode);
}



GlobalNode::GlobalNode() : Node() {};

GlobalNode::GlobalNode(Token* Value) : Node(Value) {};

GlobalNode::GlobalNode(Token* Value, Node* Parent) : Node(Value, Parent) {};

void GlobalNode::ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList)
{
	int index;
	for (int i = 0; i < codeObject->co_names.size(); i++)
	{
		if (codeObject->co_names.at(i)->Repr() == Value->value)
		{
			index = i;
			break;
		}
	}
	ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_GLOBAL, index);
	ByteCodeList->push_back(byteCode);

	for (Node* child : *Children)
	{
		CheckChild(codeObject, ByteCodeList, child);

		/*if (child->Value->type == Type::Literal)
		{
			int index;
			for (int i = 1; i < codeObject->co_consts->size(); i++)
			{
				if (codeObject->co_consts->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, index);
			ByteCodeList->push_back(byteCode);
		}
		else if (child->Value->type == Type::Identifier)
		{
			int index;
			for (int i = 0; i < codeObject->co_varnames->size(); i++)
			{
				if (codeObject->co_varnames->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_FAST, index);
			ByteCodeList->push_back(byteCode);
		}
		else
		{
			child->ToByteCode(codeObject, ByteCodeList);
		}*/
	}

	byteCode = new ByteCode(OpCodeCommands::CALL_FUNCTION, Children->size());
	ByteCodeList->push_back(byteCode);

	byteCode = new ByteCode(OpCodeCommands::POP_TOP);
	ByteCodeList->push_back(byteCode);
}



CompareNode::CompareNode() : Node() {};

CompareNode::CompareNode(Token* Value) : Node(Value) {};

CompareNode::CompareNode(Token* Value, Node* Parent) : Node(Value, Parent) {};

void CompareNode::ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList)
{
	for (Node* child : *Children)
	{
		CheckChild(codeObject, ByteCodeList, child);

		/*if (child->Value->type == Type::Literal)
		{
			int index;
			for (int i = 1; i < codeObject->co_consts->size(); i++)
			{
				if (codeObject->co_consts->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, index);
			ByteCodeList->push_back(byteCode);
		}
		else if (child->Value->type == Type::Identifier)
		{
			int index;
			for (int i = 0; i < codeObject->co_varnames->size(); i++)
			{
				if (codeObject->co_varnames->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_FAST, index);
			ByteCodeList->push_back(byteCode);
		}
		else
		{
			child->ToByteCode(codeObject, ByteCodeList);
		}*/
	}

	auto it = find(codeObject->cmp_op.begin(), codeObject->cmp_op.end(), Value->value);
	int index = it - codeObject->cmp_op.begin();
	ByteCode* byteCode = new ByteCode(OpCodeCommands::COMPARE_OP, index);
	ByteCodeList->push_back(byteCode);
}



BranchNode::BranchNode() : Node() {};

BranchNode::BranchNode(Token* Value) : Node(Value) {};

BranchNode::BranchNode(Token* Value, Node* Parent) : Node(Value, Parent) {};

void BranchNode::ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList)
{
	int startLine = (ByteCodeList->size())*2;

	for (int i = 0; i < Children->size(); i++)
	{
		CheckChild(codeObject, ByteCodeList, Children->at(i));

		/*if (Children->at(i)->Value->type == Type::Literal)
		{
			int index;
			for (int i = 1; i < codeObject->co_consts->size(); i++)
			{
				if (codeObject->co_consts->at(i)->value == Children->at(i)->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, index);
			ByteCodeList->push_back(byteCode);
		}
		else if (Children->at(i)->Value->type == Type::Identifier)
		{
			int index;
			for (int i = 0; i < codeObject->co_varnames->size(); i++)
			{
				if (codeObject->co_varnames->at(i)->value == Children->at(i)->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_FAST, index);
			ByteCodeList->push_back(byteCode);
		}
		else
		{
			Children->at(i)->ToByteCode(codeObject, ByteCodeList);
		}*/
		
		if (i == 0)
		{
			if (Value->value == "for")
			{
				ByteCode* byteCode = new ByteCode(OpCodeCommands::GET_ITER);
				ByteCodeList->push_back(byteCode);
				byteCode = new ByteCode(OpCodeCommands::FOR_ITER);
				ByteCodeList->push_back(byteCode);
				startLine = ByteCodeList->size() * 2;
			}
			else
			{
				if (Children->at(0)->Value->value != "or" && Children->at(0)->Value->value != "and")
				{
					ByteCode* byteCode = new ByteCode(OpCodeCommands::JUMP_IF_FALSE, -1);
					ByteCodeList->push_back(byteCode);
				}
			}
		}
		
	}
	if (Value->value == "while" || Value->value == "for")
	{
		if (Value->value == "for")
		{
			ByteCodeList->at(startLine)->OperandArg = (ByteCodeList->size()) * 2;
		}
		ByteCode* byteCode = new ByteCode(OpCodeCommands::JUMP_ABSOLUTE, startLine);
		ByteCodeList->push_back(byteCode);
	}
	for (int i = startLine/2; i < ByteCodeList->size(); i++)
	{
		if (ByteCodeList->at(i)->OpCode == OpCodeCommands::JUMP_IF_FALSE || ByteCodeList->at(i)->OpCode == OpCodeCommands::JUMP_IF_TRUE)
		{
			if (ByteCodeList->at(i)->OperandArg == -1)
				ByteCodeList->at(i)->OperandArg = (ByteCodeList->size()) * 2;
		}
	}
}



BoolNode::BoolNode() : Node() {};

BoolNode::BoolNode(Token* Value) : Node(Value) {};

BoolNode::BoolNode(Token* Value, Node* Parent) : Node(Value, Parent) {};

void BoolNode::ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList)
{
	for (Node* child : *Children)
	{
		CheckChild(codeObject, ByteCodeList, child);

		/*if (child->Value->type == Type::Literal)
		{
			int index;
			for (int i = 1; i < codeObject->co_consts->size(); i++)
			{
				if (codeObject->co_consts->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, index);
			ByteCodeList->push_back(byteCode);
		}
		else if (child->Value->type == Type::Identifier)
		{
			int index;
			for (int i = 0; i < codeObject->co_varnames->size(); i++)
			{
				if (codeObject->co_varnames->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_FAST, index);
			ByteCodeList->push_back(byteCode);
		}
		else
		{
			child->ToByteCode(codeObject, ByteCodeList);
		}*/

		ByteCode* byteCode;
		if (Value->value == "or")
		{
			byteCode = new ByteCode(OpCodeCommands::JUMP_IF_FALSE, -1);
		}
		else if (Value->value == "and")
		{
			byteCode = new ByteCode(OpCodeCommands::JUMP_IF_TRUE, -1);
		}
		ByteCodeList->push_back(byteCode);

	}
	ByteCodeList->back()->OpCode = OpCodeCommands::JUMP_IF_TRUE;

}



ReturnNode::ReturnNode() : Node() {};

ReturnNode::ReturnNode(Token* Value) : Node(Value) {};

ReturnNode::ReturnNode(Token* Value, Node* Parent) : Node(Value, Parent) {};

void ReturnNode::ToByteCode(CodeObject* codeObject, vector<ByteCode*>* ByteCodeList)
{
	for (Node* child : *Children)
	{
		CheckChild(codeObject, ByteCodeList, child);

		/*if (child->Value->type == Type::Literal)
		{
			int index;
			for (int i = 1; i < codeObject->co_consts->size(); i++)
			{
				if (codeObject->co_consts->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, index);
			ByteCodeList->push_back(byteCode);
		}
		else if (child->Value->type == Type::Identifier)
		{
			int index;
			for (int i = 0; i < codeObject->co_varnames->size(); i++)
			{
				if (codeObject->co_varnames->at(i)->value == child->Value->value)
				{
					index = i;
					break;
				}
			}
			ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_FAST, index);
			ByteCodeList->push_back(byteCode);
		}
		else
		{
			child->ToByteCode(codeObject, ByteCodeList);
		}*/
	}
	if (Children->size() == 0)
	{
		ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, 0);
		ByteCodeList->push_back(byteCode);
	}
	ByteCode* byteCode = new ByteCode(OpCodeCommands::RETURN_VALUE);
	ByteCodeList->push_back(byteCode);
}