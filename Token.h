#pragma once
#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

enum class Type {
	NumOperator,
	BoolOperator,
	EqualOperator,
	IteratorOperator,
	Literal,
	Identifier,
	Keyword,
	Delimiter,
	EndLine,
	Branch,
	EndBranch
};

class Token
{
public:
	Type type;
	ObjectType literalType;
	string value;
	int indentation;
	int line;
	int priority;

	Token();

	Token(Type type, string value, int indentation, int line);

	Token(Type type, string value);

};