#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;

class CodeObject
{
public:
	vector<Token*>* co_names;
	vector<Token*>* co_varnames;
	vector<Token*>* co_consts;
	vector<string> cmp_op;

	CodeObject();
};