#pragma once
#include <iostream>
#include <string>
#include "AbstractSyntaxTree.h"
#include "Token.h"

class Parser
{
	AbstractSyntaxTree syntaxTree;

	vector<string> ConditionOperators;

public:
	Parser();

	void Parse(vector<Token*> TokenList);

	int CheckSyntax(Node* node);

	void CheckSyntax();

	AbstractSyntaxTree* GetSyntaxTree();

	void ToString(const std::string& prefix, Node* node);

	void ToString();
};