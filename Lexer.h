#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;


class Lexer
{
	vector<Token*> *TokenList;

	vector<string> NumOperators;
	vector<string> BoolOperators;
	vector<string> EqualOperators;
	vector<string> KeyWords;
	vector<string> Branches;
	vector<string> Delimiters;
public:
	static int line;

	Lexer();

	int CheckIndentation(string* CodeLine);

	void Lex(string CodeLine);

	vector<Token*>* GetTokenList();

	void ToString();
};
