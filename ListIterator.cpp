#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
//    current = list.head;
    first();
}

// tetha(1)
void ListIterator::first(){
    current = list.head;
    done = 1;
}

//tetha(1)
void ListIterator::last() {
    current = list.tail;
    done = 1;
}

// tetha(1)
void ListIterator::next(){
    if(valid() && done <= list.length) {
        current = list.next[current];
        done ++;
    }
    else
        throw exception();
}
// tetha(1)
void ListIterator::prev(){
    if(valid() && done <= list.length) {
        current = list.prev[current];
        done ++;
    }
    else
        throw exception();
}

//void ListIterator::makeInvalid() {
//    done = list.length+1;
//}

// tetha(1)
bool ListIterator::valid() const{
    if(current == -1 || done > list.length)
        return false;
    return true;
}

// tetha(1)
TComp ListIterator::getCurrent() const{
    if(valid())
        return list.elem[current];
    else
        return NULL_TCOMP;
}

ListIterator::ListIterator(ListIterator &a) : list(a.list), done(a.done), current(a.current) {};
//
//ListIterator ListIterator::operator = (ListIterator& other) {
//    this->list = other.list;
//    this->done = other.done;
//    this->current = other.current;
//    return *this;
//}