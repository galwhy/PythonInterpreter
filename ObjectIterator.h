#pragma once
#include "Object.h"
#include <vector>

using namespace std;

class ObjectIterator
{
public:
	virtual ObjectIterator* Next() const = 0;

	virtual Object* GetCurrent() const = 0;

};

class ListIterator : public ObjectIterator
{
	vector<Object*>::iterator iter;

public:
	ListIterator();

	ObjectIterator* Next() const;

	Object* GetCurrent() const;
};