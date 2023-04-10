#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Object.h"

using namespace std;


Object::Object(ObjectType type)
{
	this->type = type;
}

StringObject::StringObject(ObjectType type, string value) : Object(type)
{
	this->value = value;
}

string StringObject::Repr()
{
	return value;
}


IntObject::IntObject(ObjectType type, int value) : Object(type)
{
	this->value = value;
}

string IntObject::Repr()
{
	return to_string(value);
}


BoolObject::BoolObject(ObjectType type, bool value) : Object(type)
{
	this->value = value;
}

string BoolObject::Repr()
{
	return value ? "true" : "false";
}


ListObject::ListObject(ObjectType type, vector<Object*>* list) : Object(type)
{
	this->list = list;
}

string ListObject::Repr()
{
	stringstream value;
	value << "[";
	for (int i = 0; i < list->size(); i++)
	{
		value << list->at(i)->Repr();
		if (i < list->size() - 1)
			value << ", ";
	}
	value << "]";
	return value.str();
}


IdentifierObject::IdentifierObject(ObjectType type, string name) : Object(type)
{
	this->name = name;
}

string IdentifierObject::Repr()
{
	return name;
}


GlobalObject::GlobalObject(ObjectType type, string name) : Object(type)
{
	this->name = name;
}

string GlobalObject::Repr()
{
	return name;
}