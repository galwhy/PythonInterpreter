#pragma once
#include <iostream>
#include <string>

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

enum class LiteralType {
	String,
	Int,
	Bool
};

class Token
{
public:
	Type type;
	LiteralType literalType;
	string value;
	int indentation;
	int line;
	int priority;

	Token();

	Token(Type type, string value, int indentation, int line);

	Token(Type type, string value);

};