#pragma once
#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
	const SortedIteratedList& list;
	ListIterator(const SortedIteratedList& list);
    int current;
    int done;
public:
	void first();
    void last();
	void next();
    void prev();
	bool valid() const;
    TComp getCurrent() const;
//    void makeInvalid();
//    ListIterator operator = (ListIterator& other);
    ListIterator(ListIterator &a);
};


