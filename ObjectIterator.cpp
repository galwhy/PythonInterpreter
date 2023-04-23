#include <vector>
#include "Object.h"
#include "ObjectIterator.h"

ObjectIterator::ObjectIterator() : Object(ObjectType::Iterator){}

ListIterator::ListIterator(ListObject* list) : ObjectIterator()
{
	this->iter = list->list->begin();
	this->list = list->list;
}

void ListIterator::Next()
{
	if(this->iter < this->list->end())
		this->iter++;
}

Object* ListIterator::GetCurrent() const
{
	if(this->iter < this->list->end())
		return *this->iter;
	return NULL;
}


StringIterator::StringIterator(StringObject* str) : ObjectIterator()
{
	this->string = str->value;
	this->iter = this->string.begin();
}

void StringIterator::Next()
{
	if (this->iter < this->string.end())
		this->iter++;
}

Object* StringIterator::GetCurrent() const
{
	if (this->iter < this->string.end())
	{
		std::string s(1, *this->iter);
		return new StringObject(s);
	}
	return NULL;
}