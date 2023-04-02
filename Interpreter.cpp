#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "Token.h"
#include "ByteCode.h"
#include "AbstractSyntaxTree.h"
#include "CodeObject.h"
#include "Interpreter.h"

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
	instance->CallStack.push(instance->codeObject->co_consts->at(index));
}

void Interpreter::LoadFast(int index)
{
	instance->CallStack.push(instance->codeObject->co_varnames->at(index));
}

void Interpreter::StoreFast(int index)
{
	instance->codeObject->co_varnames->at(index) = instance->CallStack.top();
	instance->CallStack.pop();
}

void Interpreter::BinaryAdd(int index)
{
	Token* num1 = instance->CallStack.top();
	instance->CallStack.pop();
	Token* num2 = instance->CallStack.top();
	instance->CallStack.pop();
	Token* result;
	if(num1->literalType == LiteralType::Int && num2->literalType == LiteralType::Int)
		result = new Token(Type::Literal, to_string(stoi(num1->value) + stoi(num2->value)));
	else if (num1->literalType == LiteralType::String && num2->literalType == LiteralType::String)
		result = new Token(Type::Literal, num1->value + num2->value);
	else
	{
		cout << "Error";
		return;
	}
	result->literalType = LiteralType::Int;
	instance->CallStack.push(result);
}

void Interpreter::BinarySubtract(int index)
{
	Token* num1 = instance->CallStack.top();
	instance->CallStack.pop();
	Token* num2 = instance->CallStack.top();
	instance->CallStack.pop();
	Token* result;
	if (num1->literalType == LiteralType::Int && num2->literalType == LiteralType::Int)
		result = new Token(Type::Literal, to_string(stoi(num1->value) - stoi(num2->value)));
	else
	{
		cout << "Error";
		return;
	}
	result->literalType = LiteralType::Int;
	instance->CallStack.push(result);
}

void Interpreter::BinaryMultiply(int index)
{
	Token* num1 = instance->CallStack.top();
	instance->CallStack.pop();
	Token* num2 = instance->CallStack.top();
	instance->CallStack.pop();
	Token* result;
	if (num1->literalType == LiteralType::Int && num2->literalType == LiteralType::Int)
		result = new Token(Type::Literal, to_string(stoi(num1->value) * stoi(num2->value)));
	else
	{
		cout << "Error";
		return;
	}
	result->literalType = LiteralType::Int;
	instance->CallStack.push(result);
}

void Interpreter::BinaryDivide(int index)
{
	Token* num1 = instance->CallStack.top();
	instance->CallStack.pop();
	Token* num2 = instance->CallStack.top();
	instance->CallStack.pop();
	Token* result;
	if (num1->literalType == LiteralType::Int && num2->literalType == LiteralType::Int)
		result = new Token(Type::Literal, to_string(stoi(num1->value) / stoi(num2->value)));
	else
	{
		cout << "Error";
		return;
	}
	result->literalType = LiteralType::Int;
	instance->CallStack.push(result);
}

void Interpreter::LoadGlobal(int index)
{
	instance->CallStack.push(instance->codeObject->co_names->at(index));

}

void Interpreter::CallFunction(int index)
{
	vector<Token*> operators;
	for (int i = 0; i < index; i++)
	{
		operators.push_back(instance->CallStack.top());
		instance->CallStack.pop();
	}
	if (instance->CallStack.top()->value == "print")
		Print(operators);
}

void Interpreter::PopTop(int index)
{
	instance->CallStack.pop();
}

void Interpreter::CompareOp(int index)
{
	Token* value1 = instance->CallStack.top();
	instance->CallStack.pop();
	Token* value2 = instance->CallStack.top();
	instance->CallStack.pop();
	string cmpOp = instance->codeObject->cmp_op.at(index);
	Token* result = NULL;
	if (cmpOp == ">")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			result = new Token(Type::Literal, stoi(value2->value) > stoi(value1->value) ? "true" : "false");
		else if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			result = new Token(Type::Literal, value2->value > value1->value ? "true" : "false");
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == ">=")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			result = new Token(Type::Literal, stoi(value2->value) >= stoi(value1->value) ? "true" : "false");
		else if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			result = new Token(Type::Literal, value2->value >= value1->value ? "true" : "false");
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == "<")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			result = new Token(Type::Literal, stoi(value2->value) < stoi(value1->value) ? "true" : "false");
		else if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			result = new Token(Type::Literal, value2->value < value1->value ? "true" : "false");
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == "<=")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			result = new Token(Type::Literal, stoi(value2->value) <= stoi(value1->value) ? "true" : "false");
		else if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			result = new Token(Type::Literal, value2->value <= value1->value ? "true" : "false");
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == "==")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			result = new Token(Type::Literal, stoi(value2->value) == stoi(value1->value) ? "true" : "false");
		else if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			result = new Token(Type::Literal, value2->value == value1->value ? "true" : "false");
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == "!=")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			result = new Token(Type::Literal, stoi(value2->value) != stoi(value1->value) ? "true" : "false");
		else if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			result = new Token(Type::Literal, value2->value != value1->value ? "true" : "false");
		else
		{
			cout << "Error";
			return;
		}
	}
	result->literalType = LiteralType::Bool;
	instance->CallStack.push(result);
}

void Interpreter::GetIter(int index)
{

}

void Interpreter::ForIter(int index)
{

}

void Interpreter::JumpIfFalse(int index)
{
	Token* value = instance->CallStack.top();
	instance->CallStack.pop();
	if (value->value == "false")
		instance->ByteCodePointer = index/2 - 1;
}

void Interpreter::JumpIfTrue(int index)
{
	Token* value = instance->CallStack.top();
	instance->CallStack.pop();
	if (value->value == "true")
		instance->ByteCodePointer = index / 2 - 1;
}

void Interpreter::JumpAbsolute(int index)
{
	instance->ByteCodePointer = index / 2 - 1;
}

void Interpreter::ReturnValue(int index)
{
	instance->ByteCodePointer = -2;
}

void Interpreter::Print(vector<Token*> operators)
{
	cout << operators[0]->value << endl;
}