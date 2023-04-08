#pragma once
#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

enum class Type {
	NumOperator,
	BoolOperator,
	EqualOperator,
	Literal,
	Identifier,
	Keyword,
	Delimiter,
	EndLine,
	Branch
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