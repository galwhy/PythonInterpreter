#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "ByteCode.h"
#include "AbstractSyntaxTree.h"
#include "Compiler.h"
#include "CodeObject.h"

Compiler::Compiler()
{
	this->ByteCodeList = new vector<ByteCode*>();
	this->codeObject = new CodeObject();
}

void Compiler::Compile(AbstractSyntaxTree* syntaxTree)
{
	syntaxTree->ToByteCode(codeObject, ByteCodeList);
	/*vector<Node*>* treeList = node->Children;
	if (node != nullptr)
	{
		if (node->Value != NULL)
		{

			if (node->Value->type == Type::EqualOperator)
			{
				if (node->Value->value == "=")
				{

					if (treeList->at(1)->Value->type == Type::Literal)
					{

						auto it = find(codeObject->co_consts->begin(), codeObject->co_consts->end(), treeList->at(1)->Value);
						int index = it - codeObject->co_consts->begin();
						ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_CONST, index);
						ByteCodeList->push_back(byteCode);
					}
					else if (treeList->at(1)->Value->type == Type::Identifier)
					{
						auto it = find(codeObject->co_varnames->begin(), codeObject->co_varnames->end(), treeList->at(1)->Value);
						int index = it - codeObject->co_varnames->begin();
						ByteCode* byteCode = new ByteCode(OpCodeCommands::LOAD_NAME, index);
						ByteCodeList->push_back(byteCode);
					}

					auto it = find(codeObject->co_varnames->begin(), codeObject->co_varnames->begin(), treeList->at(0)->Value);
					int index = it - codeObject->co_varnames->begin();
					ByteCode* byteCode = new ByteCode(OpCodeCommands::STORE_FAST, index);
					ByteCodeList->push_back(byteCode);
				}
			}

		}

		for (Node* Tree : *treeList)
		{
			Compile(Tree);
		}
	}*/
}

void Compiler::BuildCode(Node* node)
{
	vector<Node*>* treeList = node->Children;
	if (node != nullptr)
	{
		if (node->Value != NULL)
		{
			if (node->Value->type == Type::Identifier)
			{
				codeObject->co_varnames->push_back(node->Value);
			}
			if (node->Value->type == Type::Keyword)
			{
				codeObject->co_names->push_back(node->Value);
			}
			if (node->Value->type == Type::Literal)
			{
				codeObject->co_consts->push_back(node->Value);
			}
		}
		
		for (Node* Tree : *treeList)
		{
			BuildCode(Tree);
		}
	}
}

void Compiler::ToString()
{
	for (ByteCode* b : *ByteCodeList)
	{
		cout << b->OpCode << b->OperandArg << endl;
	}
}