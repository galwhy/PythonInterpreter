#include <iostream>
#include <string>
#include <vector>
#include "CodeObject.h"

CodeObject::CodeObject()
{
	this->co_consts.push_back(NULL);
	this->cmp_op = {"<", "<=", "==", "!=", ">", ">="};
}