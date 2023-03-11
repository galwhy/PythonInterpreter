#include <iostream>
#include <string>
#include <vector>
#include "CodeObject.h"

CodeObject::CodeObject()
{
	this->co_names = new vector<Token*>();
	this->co_varnames = new vector<Token*>();
	this->co_consts = new vector<Token*>();
}