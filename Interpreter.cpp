#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "Token.h"
#include "ByteCode.h"
#include "AbstractSyntaxTree.h"
#include "CodeObject.h"
#include "Interpreter.h"
#include "ObjectIterator.h"

Interpreter* Interpreter::instance;

Interpreter* Interpreter::getInstance(CodeObject* codeObject)
{
	if (instance == NULL)
	{
		instance = new Interpreter(codeObject);
	}
	return instance;
}


Interpreter::Interpreter(CodeObject* codeObject)
{
	this->codeObject = codeObject;
	this->ByteCodePointer = 0;

	byteCodeMap.emplace(OpCodeCommands::LOAD_CONST, &Interpreter::LoadConst);
	byteCodeMap.emplace(OpCodeCommands::LOAD_FAST, &Interpreter::LoadFast);
	byteCodeMap.emplace(OpCodeCommands::STORE_FAST, &Interpreter::StoreFast);
	byteCodeMap.emplace(OpCodeCommands::BINARY_ADD, &Interpreter::BinaryAdd);
	byteCodeMap.emplace(OpCodeCommands::BINARY_SUBTRACT, &Interpreter::BinarySubtract);
	byteCodeMap.emplace(OpCodeCommands::BINARY_MULTIPLY, &Interpreter::BinaryMultiply);
	byteCodeMap.emplace(OpCodeCommands::BINARY_DIVIDE, &Interpreter::BinaryDivide);
	byteCodeMap.emplace(OpCodeCommands::LOAD_GLOBAL, &Interpreter::LoadGlobal);
	byteCodeMap.emplace(OpCodeCommands::CALL_FUNCTION, &Interpreter::CallFunction);
	byteCodeMap.emplace(OpCodeCommands::POP_TOP, &Interpreter::PopTop);
	byteCodeMap.emplace(OpCodeCommands::COMPARE_OP, &Interpreter::CompareOp);
	byteCodeMap.emplace(OpCodeCommands::GET_ITER, &Interpreter::GetIter);
	byteCodeMap.emplace(OpCodeCommands::FOR_ITER, &Interpreter::ForIter);
	byteCodeMap.emplace(OpCodeCommands::JUMP_IF_FALSE, &Interpreter::JumpIfFalse);
	byteCodeMap.emplace(OpCodeCommands::JUMP_IF_TRUE, &Interpreter::JumpIfTrue);
	byteCodeMap.emplace(OpCodeCommands::JUMP_ABSOLUTE, &Interpreter::JumpAbsolute);
	byteCodeMap.emplace(OpCodeCommands::BINARY_SUBSCR, &Interpreter::binarySubscr);
	byteCodeMap.emplace(OpCodeCommands::RETURN_VALUE, &Interpreter::ReturnValue);
}

void Interpreter::Interprete(vector<ByteCode*>* byteCodeList)
{
	while(ByteCodePointer != -1)
	{
		auto call = byteCodeMap.find(byteCodeList->at(ByteCodePointer)->OpCode);
		if (call != byteCodeMap.end())
			(*call).second(byteCodeList->at(ByteCodePointer)->OperandArg);
		else
			cout << "Unknown call requested" << endl;
		ByteCodePointer++;
	}
}

void Interpreter::LoadConst(int index)
{
	instance->CallStack.push(instance->codeObject->co_consts.at(index));
}

void Interpreter::LoadFast(int index)
{
	instance->CallStack.push(instance->codeObject->co_varnames.at(index));
}

void Interpreter::StoreFast(int index)
{
	instance->codeObject->co_varnames.at(index) = instance->CallStack.top();
	instance->CallStack.pop();
}

void Interpreter::BinaryAdd(int index)
{
	Object* num1 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* num2 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* result = num2->Add(num1);

	instance->CallStack.push(result);
}

void Interpreter::BinarySubtract(int index)
{
	Object* num1 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* num2 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* result = num2->subtract(num1);;

	instance->CallStack.push(result);
}

void Interpreter::BinaryMultiply(int index)
{
	Object* num1 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* num2 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* result = num2->multiply(num1);;

	instance->CallStack.push(result);
}

void Interpreter::BinaryDivide(int index)
{
	Object* num1 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* num2 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* result = num2->divide(num1);;

	instance->CallStack.push(result);
}

void Interpreter::LoadGlobal(int index)
{
	instance->CallStack.push(instance->codeObject->co_names.at(index));
}

void Interpreter::CallFunction(int index)
{
	vector<Object*> operators;
	for (int i = 0; i < index; i++)
	{
		operators.push_back(instance->CallStack.top());
		instance->CallStack.pop();
	}
	if (instance->CallStack.top()->Repr() == "print")
		Print(operators);
}

void Interpreter::PopTop(int index)
{
	instance->CallStack.pop();
}

void Interpreter::CompareOp(int index)
{
	Object* value1 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* value2 = instance->CallStack.top();
	instance->CallStack.pop();
	string cmpOp = instance->codeObject->cmp_op.at(index);
	Object* result = NULL;
	if (cmpOp == ">")
	{
		result = value2->IsBigger(value1);
	}
	else if (cmpOp == ">=")
	{
		result = new BoolObject(value2->IsBigger(value1)->Repr() == "true" || value2->IsEqual(value1)->Repr() == "true");
		/*if (value1->type == value2->type)
		{
			if (value1->type == ObjectType::Int)
			{
				result = new BoolObject(ObjectType::Bool, stoi(value2->Repr()) >= stoi(value1->Repr()));
			}
			else if (value1->type == ObjectType::String)
			{
				result = new BoolObject(ObjectType::Bool, value2->Repr() >= value1->Repr());
			}
		}
		else
		{
			cout << "Error";
			return;
		}*/
	}
	else if (cmpOp == "<")
	{
		result = value2->IsSmaller(value1);
	}
	else if (cmpOp == "<=")
	{
		result = new BoolObject(value2->IsSmaller(value1)->Repr() == "true" || value2->IsEqual(value1)->Repr() == "true");
	}
	else if (cmpOp == "==")
	{
		result = value2->IsEqual(value1);
	}
	else if (cmpOp == "!=")
	{
	result = new BoolObject(value2->IsEqual(value1)->Repr() == "false");
	}
	instance->CallStack.push(result);
}

void Interpreter::GetIter(int index)
{
	Object* value = instance->CallStack.top();
	instance->CallStack.pop();

	instance->CallStack.push(value->GetIterator());
}

void Interpreter::ForIter(int index)
{
	Object* value = instance->CallStack.top();
	if (value->type == ObjectType::Iterator)
	{
		ObjectIterator* rhs = (ObjectIterator*)value;
		Object* newValue = rhs->GetCurrent();
		rhs->Next();

		if (newValue == NULL)
		{
			instance->CallStack.pop();
			instance->ByteCodePointer = index/2-1;
		}
		else
		{
			instance->CallStack.push(newValue);
		}
	}
}

void Interpreter::JumpIfFalse(int index)
{
	Object* value = instance->CallStack.top();
	instance->CallStack.pop();
	if (value->Repr() == "false")
		instance->ByteCodePointer = index/2 - 1;
}

void Interpreter::JumpIfTrue(int index)
{
	Object* value = instance->CallStack.top();
	instance->CallStack.pop();
	if (value->Repr() == "true")
		instance->ByteCodePointer = index / 2 - 1;
}

void Interpreter::JumpAbsolute(int index)
{
	instance->ByteCodePointer = index / 2 - 1;
}

void Interpreter::binarySubscr(int index)
{
	Object* value1 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* value2 = instance->CallStack.top();
	instance->CallStack.pop();
	Object* result = value1->GetIndex(value2);

	instance->CallStack.push(result);
}

void Interpreter::ReturnValue(int index)
{
	instance->ByteCodePointer = -2;
}

void Interpreter::Print(vector<Object*> operators)
{
	cout << operators[0]->Repr() << endl;
}