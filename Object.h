#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class ObjectType
{
	String,
	Int,
	Bool,
	Identifier,
	Global
};

class Object
{
public:
	ObjectType type;

	Object(ObjectType type);

	virtual string Repr() = 0;
};

class StringObject : public Object
{
public:
	string value;

	StringObject(ObjectType type, string value);

	string Repr();
};

class IntObject : public Object
{
public:
	int value;

	IntObject(ObjectType type, int value);

	string Repr();
};

class BoolObject : public Object
{
public:
	bool value;

	BoolObject(ObjectType type, bool value);

	string Repr();
};

class IdentifierObject : public Object
{
public:
	string name;

	IdentifierObject(ObjectType type , string name);

	string Repr();
};

class GlobalObject : public Object
{
public:
	string name;

	GlobalObject(ObjectType type, string name);

	string Repr();
};