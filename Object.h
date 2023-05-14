#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class ObjectType
{
	String,
	Int,
	Bool,
	List,
	Identifier,
	Global,
	Iterator
};

class ObjectIterator;

class Token;

class Object
{
public:
	ObjectType type;

	Object(ObjectType type);

	virtual string Repr();

	virtual bool compare(Token* token);

	virtual Object* Add(Object* obj);

	virtual Object* subtract(Object* obj);

	virtual Object* multiply(Object* obj);

	virtual Object* divide(Object* obj);

	virtual Object* IsEqual(Object* obj);

	virtual Object* IsBigger(Object* obj);

	virtual Object* IsSmaller(Object* obj);

	virtual Object* GetIterator();

	virtual Object* GetIndex(Object* obj);

	virtual string ToString();
};

class StringObject : public Object
{
public:
	string value;

	StringObject(string value);

	virtual bool compare(Token* token);

	virtual Object* Add(Object* obj);

	virtual	Object* IsEqual(Object* obj);

	virtual	Object* IsBigger(Object* obj);

	virtual	Object* IsSmaller(Object* obj);

	virtual Object* GetIterator();

	virtual Object* GetIndex(Object* obj);

	virtual	string Repr();

	virtual string ToString();
};

class IntObject : public Object
{
public:
	int value;

	IntObject(int value);

	virtual bool compare(Token* token);

	virtual Object* Add(Object* obj);

	virtual	Object* subtract(Object* obj);

	virtual	Object* multiply(Object* obj);

	virtual	Object* divide(Object* obj);

	virtual	Object* IsEqual(Object* obj);

	virtual	Object* IsBigger(Object* obj);

	virtual	Object* IsSmaller(Object* obj);

	virtual	string Repr();

	virtual string ToString();
};

class BoolObject : public Object
{
public:
	bool value;

	BoolObject(bool value);

	virtual bool compare(Token* token);

	virtual	Object* IsEqual(Object* obj);

	virtual	string Repr();

	virtual string ToString();
};

class ListObject : public Object
{
public:
	vector<Object*>* list;

	ListObject(vector<Object*>* list);

	virtual bool compare(Token* token);

	virtual Object* GetIterator();

	virtual Object* GetIndex(Object* obj);

	virtual	string Repr();

	virtual string ToString();
};

class IdentifierObject : public Object
{
public:
	string name;

	IdentifierObject(string name);

	virtual bool compare(Token* token);

	virtual	string Repr();
};

class GlobalObject : public Object
{
public:
	string name;

	GlobalObject(string name);

	virtual bool compare(Token* token);

	virtual	string Repr();
};