#include "Token.h"
#include <iostream>
#include <string>

using namespace std;
 

Token::Token(Type type, string value, int indentation, int line)
{
	this->type = type;
	this->value = value;
	this->indentation = indentation;
	this->line = line;
	this->priority = 0;
}

Token::Token()
{
	this->indentation = 0;
	this->value = "";
	this->priority = 0;
}

