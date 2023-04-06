#include <iostream>
#include <string>
#include "Object.h"

using namespace std;


Object::Object(Type type)
{
	this->type = type;
}

StringObject::StringObject(Type type, string value) : Object(type)
{
	this->value = value;
}

IntObject::IntObject(Type type, int value) : Object(type)
{
	this->value = value;
}

BoolObject::BoolObject(Type type, bool value) : Object(type)
{
	this->value = value;
}