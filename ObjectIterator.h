#pragma once
#include "Object.h"
#include <vector>

using namespace std;

class ObjectIterator : public Object
{
public:
	ObjectIterator();

	virtual void Next() = 0;

	virtual Object* GetCurrent() const = 0;

};

class ListIterator : public ObjectIterator
{
	std::iterator<std::forward_iterator_tag, Object*> current;


	vector<Object*>::iterator iter;
	vector<Object*>* list;

public:
	ListIterator(ListObject* list);

	virtual	void Next();

	virtual	Object* GetCurrent() const;
};

class StringIterator : public ObjectIterator
{
	string::iterator iter;
	string string;

public:
	StringIterator(StringObject* str);

	virtual	void Next();

	virtual	Object* GetCurrent() const;
};

