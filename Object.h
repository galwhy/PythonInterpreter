#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class Type
{
	String,
	Int,
	Bool
};

class Object
{
public:
	Type type;

	Object(Type type);
};

class StringObject : public Object
{
public:
	string value;

	StringObject(Type type, string value);
};

class IntObject : public Object
{
public:
	int value;

	IntObject(Type type, int value);
};

class BoolObject : public Object
{
public:
	bool value;

	BoolObject(Type type, bool value);
};