#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "ByteCode.h"
#include "AbstractSyntaxTree.h"
#include "Compiler.h"
#include "CodeObject.h"
#include "Object.h"

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
	bool doesExist = false;
	if (node != nullptr)
	{
		if (node->Value != NULL)
		{
			if (node->Value->type == Type::Identifier)
			{
				for (Object* value : codeObject->co_varnames)
				{
					if (value->Repr() == node->Value->value)
						doesExist = true;
				}
				if (!doesExist)
				{
					IdentifierObject* obj = new IdentifierObject(node->Value->value);
					codeObject->co_varnames.push_back(obj);
				}
			}
			if (node->Value->type == Type::Keyword)
			{
				for (Object* value : codeObject->co_names)
				{
					if (value->Repr() == node->Value->value)
						doesExist = true;
				}
				if (!doesExist)
				{
					GlobalObject* obj = new GlobalObject(node->Value->value);
					codeObject->co_names.push_back(obj);

				}
			}
			if (node->Value->type == Type::Literal)
			{
				for (Object* value : codeObject->co_consts)
				{
					if (value != NULL && value->Repr() == node->Value->value)
						doesExist = true;
				}
				if (!doesExist)
				{
					Object* obj;
					if (node->Value->literalType == ObjectType::List)
					{
						string value = node->Value->value;
						int index = 1;
						int delimeter = 0;
						vector<Object*>* list = new vector<Object*>();
						while (index < value.size() - 1)
						{
							int delimeter = value.find(",", index);
							if (delimeter == -1)
								delimeter = value.length() - 1;
							while (value[index] == ' ')
							{
								index++;
							}
							string listValue = value.substr(index, delimeter - index);
							if (listValue.length() == 0)
							{
								index++;
								continue;
							}
							Object* obj;
							if (listValue[0] == '"')
							{
								obj = new StringObject(listValue.substr(1, listValue.size() - 1));
							}
							else if (listValue == "true" || listValue == "false")
							{
								obj = new BoolObject((listValue == "true"));
							}
							else
							{
								obj = new IntObject(stoi(listValue));
							}
							list->push_back(obj);
							index += listValue.length();
						}
						obj = new ListObject(list);

					}
					else if (node->Value->literalType == ObjectType::String)
						obj = new StringObject(node->Value->value);
					else if (node->Value->literalType == ObjectType::Int)
						obj = new IntObject(stoi(node->Value->value));
					else if (node->Value->literalType == ObjectType::Bool)
						obj = new BoolObject((node->Value->value == "true"));
					codeObject->co_consts.push_back(obj);
				}
			}
		}
		
		for (Node* Tree : *treeList)
		{
			BuildCode(Tree);
		}
	}
}

CodeObject* Compiler::GetCodeObject()
{
	return codeObject;
}

vector<ByteCode*>* Compiler::GetByteCodeList()
{
	return ByteCodeList;
}

void Compiler::ToString()
{
	for (ByteCode* b : *ByteCodeList)
	{
		cout << b->OpCode << b->OperandArg << endl;
	}
}