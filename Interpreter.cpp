#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "Token.h"
#include "ByteCode.h"
#include "AbstractSyntaxTree.h"
#include "CodeObject.h"
#include "Interpreter.h"


Interpreter::Interpreter(CodeObject* codeObject)
{
	this->codeObject = codeObject;
	this->ByteCodePointer = 0;

	byteCodeMap.emplace(OpCodeCommands::LOAD_CONST, &LoadConst);
	byteCodeMap.emplace(OpCodeCommands::LOAD_FAST, &LoadFast);
	byteCodeMap.emplace(OpCodeCommands::STORE_FAST, &StoreFast);
	byteCodeMap.emplace(OpCodeCommands::BINARY_ADD, &BinaryAdd);
	byteCodeMap.emplace(OpCodeCommands::BINARY_SUBTRACT, &BinarySubtract);
	byteCodeMap.emplace(OpCodeCommands::BINARY_MULTIPLY, &BinaryMultiply);
	byteCodeMap.emplace(OpCodeCommands::BINARY_DIVIDE, &BinaryDivide);
	byteCodeMap.emplace(OpCodeCommands::LOAD_GLOBAL, &LoadGlobal);
	byteCodeMap.emplace(OpCodeCommands::CALL_FUNCTION, &CallFunction);
	byteCodeMap.emplace(OpCodeCommands::POP_TOP, &PopTop);
	byteCodeMap.emplace(OpCodeCommands::COMPARE_OP, &CompareOp);
	byteCodeMap.emplace(OpCodeCommands::GET_ITER, &GetIter);
	byteCodeMap.emplace(OpCodeCommands::FOR_ITER, &ForIter);
	byteCodeMap.emplace(OpCodeCommands::JUMP_IF_FALSE, &JumpIfFalse);
	byteCodeMap.emplace(OpCodeCommands::JUMP_IF_TRUE, &JumpIfTrue);
	byteCodeMap.emplace(OpCodeCommands::JUMP_ABSOLUTE, &JumpAbsolute);
	byteCodeMap.emplace(OpCodeCommands::RETURN_VALUE, &ReturnValue);
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
	}
}

void Interpreter::LoadConst(int index)
{
	CallStack.push(codeObject->co_consts->at(index));
}

void Interpreter::LoadFast(int index)
{
	CallStack.push(codeObject->co_varnames->at(index));
}

void Interpreter::BinaryAdd(int index)
{
	Token* num1 = CallStack.top();
	CallStack.pop();
	Token* num2 = CallStack.top();
	CallStack.pop();
	Token* result;
	if(num1->literalType == LiteralType::Int && num2->literalType == LiteralType::Int)
		result = new Token(Type::Literal, to_string(stoi(num1->value) + stoi(num2->value)));
	if (num1->literalType == LiteralType::String && num2->literalType == LiteralType::String)
		result = new Token(Type::Literal, num1->value + num2->value);
	else
	{
		cout << "Error";
		return;
	}
	CallStack.push(result);
}

void Interpreter::BinarySubtract(int index)
{
	Token* num1 = CallStack.top();
	CallStack.pop();
	Token* num2 = CallStack.top();
	CallStack.pop();
	Token* result;
	if (num1->literalType == LiteralType::Int && num2->literalType == LiteralType::Int)
		result = new Token(Type::Literal, to_string(stoi(num1->value) - stoi(num2->value)));
	else
	{
		cout << "Error";
		return;
	}
	CallStack.push(result);
}

void Interpreter::BinaryMultiply(int index)
{
	Token* num1 = CallStack.top();
	CallStack.pop();
	Token* num2 = CallStack.top();
	CallStack.pop();
	Token* result;
	if (num1->literalType == LiteralType::Int && num2->literalType == LiteralType::Int)
		result = new Token(Type::Literal, to_string(stoi(num1->value) * stoi(num2->value)));
	else
	{
		cout << "Error";
		return;
	}
	CallStack.push(result);
}

void Interpreter::BinaryDivide(int index)
{
	Token* num1 = CallStack.top();
	CallStack.pop();
	Token* num2 = CallStack.top();
	CallStack.pop();
	Token* result;
	if (num1->literalType == LiteralType::Int && num2->literalType == LiteralType::Int)
		result = new Token(Type::Literal, to_string(stoi(num1->value) / stoi(num2->value)));
	else
	{
		cout << "Error";
		return;
	}
	CallStack.push(result);
}

void Interpreter::LoadGlobal(int index)
{
	CallStack.push(codeObject->co_names->at(index));

}

void Interpreter::CallFunction(int index)
{

}

void Interpreter::PopTop(int index)
{
	CallStack.pop();
}

void Interpreter::CompareOp(int index)
{
	Token* value1 = CallStack.top();
	CallStack.pop();
	Token* value2 = CallStack.top();
	CallStack.pop();
	string cmpOp = codeObject->cmp_op.at(index);
	Token* result;
	if (cmpOp == ">")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			Token* result = new Token(Type::Literal, to_string(stoi(value1->value) > stoi(value2->value)));
		if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			Token* result = new Token(Type::Literal, to_string(value1->value > value2->value));
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == ">=")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			Token* result = new Token(Type::Literal, to_string(stoi(value1->value) >= stoi(value2->value)));
		if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			Token* result = new Token(Type::Literal, to_string(value1->value >= value2->value));
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == "<")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			Token* result = new Token(Type::Literal, to_string(stoi(value1->value) < stoi(value2->value)));
		if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			Token* result = new Token(Type::Literal, to_string(value1->value < value2->value));
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == "<=")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			Token* result = new Token(Type::Literal, to_string(stoi(value1->value) <= stoi(value2->value)));
		if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			Token* result = new Token(Type::Literal, to_string(value1->value <= value2->value));
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == "==")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			Token* result = new Token(Type::Literal, to_string(stoi(value1->value) == stoi(value2->value)));
		if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			Token* result = new Token(Type::Literal, to_string(value1->value == value2->value));
		else
		{
			cout << "Error";
			return;
		}
	}
	else if (cmpOp == "!=")
	{
		if (value1->literalType == LiteralType::Int && value2->literalType == LiteralType::Int)
			Token* result = new Token(Type::Literal, to_string(stoi(value1->value) != stoi(value2->value)));
		if (value1->literalType == LiteralType::String && value2->literalType == LiteralType::String)
			Token* result = new Token(Type::Literal, to_string(value1->value != value2->value));
		else
		{
			cout << "Error";
			return;
		}
	}
	CallStack.push(result);
}

void Interpreter::GetIter(int index)
{

}

void Interpreter::ForIter(int index)
{

}

void Interpreter::JumpIfFalse(int index)
{
	Token* value = CallStack.top();
	if (value->value == "false")
		ByteCodePointer = index;
}

void Interpreter::JumpIfTrue(int index)
{
	Token* value = CallStack.top();
	if (value->value == "true")
		ByteCodePointer = index;
}

void Interpreter::JumpAbsolute(int index)
{
	ByteCodePointer = index;
}

void Interpreter::ReturnValue(int index)
{
	ByteCodePointer = -1;
}