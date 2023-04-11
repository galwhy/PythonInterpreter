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
	vector<Object*>::iterator iter;
	vector<Object*>* list;

public:
	ListIterator(ListObject* list);

	virtual	void Next();

	virtual	Object* GetCurrent() const;
};