#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Object.h"
#include "ObjectIterator.h"
#include "Token.h"

using namespace std;


Object::Object(ObjectType type)
{
	this->type = type;
}

bool Object::compare(Token* token) { throw exception("Unable to compare Token"); }

Object* Object::Add(Object* obj) { throw exception("Unable to add objects"); }

Object* Object::subtract(Object* obj) { throw exception("Unable to subtract objects"); }

Object* Object::multiply(Object* obj) { throw exception("Unable to multiply objects"); }

Object* Object::divide(Object* obj) { throw exception("Unable to divide objects"); }

Object* Object::IsEqual(Object* obj) { throw exception("Unable to compare objects"); }

Object* Object::IsBigger(Object* obj) { throw exception("Unable to compare objects"); }

Object* Object::IsSmaller(Object* obj){ throw exception("Unable to compare objects"); }

Object* Object::GetIterator() { throw exception("Object is not iteratable"); }

Object* Object::GetIndex(Object* obj) { throw exception("Unable to get item from index"); }

string Object::Repr() { throw exception("Unable to call Repr"); }


StringObject::StringObject(string value) : Object(ObjectType::String)
{
	this->value = value;
}

bool StringObject::compare(Token* token)
{
	if (token->literalType != ObjectType::String)
	{
		return false;
	}
	if (this->Repr() == token->value)
	{
		return true;
	}
	return false;
}

Object* StringObject::Add(Object* obj)
{
	if (obj->type != ObjectType::String) {
		throw std::exception("Unable to add different object types");
	}

	StringObject* rhs = (StringObject*)obj;
	StringObject* newObj = new StringObject(value + rhs->value);
	return newObj;
}

Object* StringObject::IsEqual(Object* obj)
{
	if (obj->type != ObjectType::String) {
		throw std::exception("Unable to compare different object types");
	}

	StringObject* rhs = (StringObject*)obj;
	BoolObject* newObj = new BoolObject(value == rhs->value);
	return newObj;
}

Object* StringObject::IsBigger(Object* obj)
{
	if (obj->type != ObjectType::String) {
		throw std::exception("Unable to compare different object types");
	}

	StringObject* rhs = (StringObject*)obj;
	BoolObject* newObj = new BoolObject(value > rhs->value);
	return newObj;
}

Object* StringObject::IsSmaller(Object* obj)
{
	if (obj->type != ObjectType::String) {
		throw std::exception("Unable to compare different object types");
	}

	StringObject* rhs = (StringObject*)obj;
	BoolObject* newObj = new BoolObject(value < rhs->value);
	return newObj;
}

Object* StringObject::GetIterator()
{
	ObjectIterator* itr = new StringIterator(this);
	return itr;
}

Object* StringObject::GetIndex(Object* obj)
{
	if (obj->type != ObjectType::Int) {
		throw std::exception("Index has to be an Integer");
	}

	IntObject* rhs = (IntObject*)obj;
	std::string s(1, value[rhs->value]);
	StringObject* newObj = new StringObject(s);
	return newObj;
}

string StringObject::Repr()
{
	return "'"  + value + "'";
}


IntObject::IntObject(int value) : Object(ObjectType::Int)
{
	this->value = value;
}

bool IntObject::compare(Token* token)
{
	if (token->literalType != ObjectType::Int)
	{
		return false;
	}
	if (this->Repr() == token->value)
	{
		return true;
	}
	return false;

}

Object* IntObject::Add(Object* obj)
{
	if (obj->type != ObjectType::Int) {
		throw std::exception("Unable to add different object types");
	}

	IntObject* rhs = (IntObject*)obj;
	IntObject* newObj = new IntObject(value + rhs->value);
	return newObj;
}

Object* IntObject::subtract(Object* obj)
{
	if (obj->type != ObjectType::Int) {
		throw std::exception("Unable to subtract different object types");
	}

	IntObject* rhs = (IntObject*)obj;
	IntObject* newObj = new IntObject(value - rhs->value);
	return newObj;
}

Object* IntObject::multiply(Object* obj)
{
	if (obj->type != ObjectType::Int) {
		throw std::exception("Unable to multiply different object types");
	}

	IntObject* rhs = (IntObject*)obj;
	IntObject* newObj = new IntObject(value * rhs->value);
	return newObj;
}

Object* IntObject::divide(Object* obj)
{
	if (obj->type != ObjectType::Int) {
		throw std::exception("Unable to divide different object types");
	}

	IntObject* rhs = (IntObject*)obj;
	IntObject* newObj = new IntObject(value / rhs->value);
	return newObj;
}

Object* IntObject::IsEqual(Object* obj)
{
	if (obj->type != ObjectType::Int) {
		throw std::exception("Unable to compare different object types");
	}

	IntObject* rhs = (IntObject*)obj;
	BoolObject* newObj = new BoolObject(value == rhs->value);
	return newObj;
}

Object* IntObject::IsBigger(Object* obj)
{
	if (obj->type != ObjectType::Int) {
		throw std::exception("Unable to compare different object types");
	}

	IntObject* rhs = (IntObject*)obj;
	BoolObject* newObj = new BoolObject(value > rhs->value);
	return newObj;
}

Object* IntObject::IsSmaller(Object* obj)
{
	if (obj->type != ObjectType::Int) {
		throw std::exception("Unable to compare different object types");
	}

	IntObject* rhs = (IntObject*)obj;
	BoolObject* newObj = new BoolObject(value < rhs->value);
	return newObj;
}

string IntObject::Repr()
{
	return to_string(value);
}


BoolObject::BoolObject(bool value) : Object(ObjectType::Bool)
{
	this->value = value;
}

bool BoolObject::compare(Token* token)
{
	if (token->literalType != ObjectType::Bool)
	{
		return false;
	}
	if (this->Repr() == token->value)
	{
		return true;
	}
	return false;

}

Object* BoolObject::IsEqual(Object* obj)
{
	if (obj->type != ObjectType::Bool) {
		throw std::exception("Unable to compare different object types");
	}

	BoolObject* rhs = (BoolObject*)obj;
	BoolObject* newObj = new BoolObject(value == rhs->value);
	return newObj;
}

string BoolObject::Repr()
{
	return value ? "true" : "false";
}


ListObject::ListObject(vector<Object*>* list) : Object(ObjectType::List)
{
	this->list = list;
}

bool ListObject::compare(Token* token)
{
	if (token->literalType != ObjectType::List)
	{
		return false;
	}
	string value = token->value;
	int listIndex = 0;
	int index = 1;
	int delimeter = 0;
	while (index < value.size() - 1)
	{
		int delimeter = value.find(",", index);
		if (delimeter == -1)
			delimeter = value.length() - 1;
		while (value[index] == ' ')
		{
			index++;
		}
		string listValue = value.substr(index, delimeter - index);
		if (listValue.length() == 0)
		{
			index++;
			continue;
		}
		if (list->at(listIndex)->Repr() != listValue)
		{
			return false;
		}
		index += listValue.length();
		listIndex++;
	}
	return true;

}

Object* ListObject::GetIterator()
{
	ObjectIterator* itr = new ListIterator(this);
	return itr;
}

Object* ListObject::GetIndex(Object* obj)
{
	if (obj->type != ObjectType::Int) {
		throw std::exception("Index has to be an Integer");
	}

	IntObject* rhs = (IntObject*)obj;
	return list->at(rhs->value);;
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


IdentifierObject::IdentifierObject(string name) : Object(ObjectType::Identifier)
{
	this->name = name;
}

bool IdentifierObject::compare(Token* token)
{
	if (this->Repr() == token->value)
	{
		return true;
	}
	return false;

}

string IdentifierObject::Repr()
{
	return name;
}


GlobalObject::GlobalObject(string name) : Object(ObjectType::Global)
{
	this->name = name;
}

bool GlobalObject::compare(Token* token)
{
	if (this->Repr() == token->value)
	{
		return true;
	}
	return false;

}

string GlobalObject::Repr()
{
	return name;
}