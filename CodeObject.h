#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "Object.h"

using namespace std;

class CodeObject
{
public:
	vector<Object*> co_names;
	vector<Object*> co_varnames;
	vector<Object*> co_consts;
	vector<string> cmp_op;

	CodeObject();
};