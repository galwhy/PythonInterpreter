#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "ByteCode.h"


ByteCode::ByteCode(OpCodeCommands opCode, int operandArg)
{
	this->OpCode = opCode;
	this->OperandArg = operandArg;
}

ByteCode::ByteCode(OpCodeCommands opCode)
{
	this->OpCode = opCode;
}