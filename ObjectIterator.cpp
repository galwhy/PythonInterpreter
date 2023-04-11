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