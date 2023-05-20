#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
    cap = 2;
    length = 0;
    head = -1;
    tail = -1;
    elem = new TComp[cap];
    next = new TComp[cap];
    prev = new TComp[cap];
    firstFree = 0;
    for(int i = 0; i < cap-1; i ++) {
        next[i] = i+1;
        prev[i+1] = i;
    }
    prev[0] = -1;
    next[cap-1] = -1;
    rel = r;
}

int SortedIteratedList::size() const {
	return length;
}

bool SortedIteratedList::isEmpty() const {
	return (length == 0);
}

ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);
}

// tetha(1)
TComp SortedIteratedList::getElement(ListIterator poz) const {
    if(!poz.valid())
        throw exception();
    return poz.getCurrent();
}

// tetha(1)
TComp SortedIteratedList::remove(ListIterator& poz) {
    if(!poz.valid())
        throw exception();
    auto toReturn = poz.getCurrent();
    int i = poz.current;
    poz.current=next[poz.current];
//    std::cout << "Before removal of pos " << i << ", next list is: (head is " << head << ")\n";
//    for(int i = 0; i < cap; i ++) {
//        std::cout << next[i] << ' ';
//    }
//    std::cout << '\n';
    if(length == 1) {
        head = tail = -1;
        next[i] = -1;
        prev[i] = -1;
    } else if(i == head) {
        prev[next[i]] = -1;
        head = next[i];
    } else if(i == tail) {
        next[prev[i]] = next[i];
        tail = prev[i];
    } else {
        next[prev[i]] = next[i];
        prev[next[i]] = prev[i];
    }
    freeP(i);
//    std::cout << "For removal of pos " << i << ", next list is: (head is " << head << ")\n";
//    for(int i = 0; i < cap; i ++) {
//        std::cout << next[i] << ' ';
//    }
//    std::cout << '\n';

    return toReturn;
}


// O(n)
// bc tetha(1)
// wc tetha(n)
ListIterator SortedIteratedList::search(TComp e) const {
    auto it = ListIterator(*this);
    for(; it.valid(); it.next()) {
//        std::cout << "it: " << it.getCurrent() << " e: " << e << '\n';
        if(it.getCurrent() == e) {
            return it;
        }
    }
    return it;
}

// O(n)
// bc tetha(1)
// wc tetha(n)
void SortedIteratedList::add(TComp e) {
    if(head == -1 && tail == -1) {
        int i = allocateP();
        elem[i] = e;
        head = tail = i;
        return;
    }
    if(rel(elem[head], e) == 0) {
        int i = allocateP();
        elem[i] = e;
        next[i] = head;
        prev[head] = i;
        head = i;
    } else if(rel(elem[tail], e) == 1) {
        int i = allocateP();
        elem[i] = e;
        next[tail] = i;
        prev[i] = tail;
        tail = i;
    }
    else
    for(int i = head; i != -1; i = next[i]) {
        if(rel(elem[i], e) == 0) {
            int j = allocateP();
            elem[j] = e;
            prev[j] = prev[i];
            next[prev[i]] = j;
            next[j] = i;
            prev[i] = j;
            next[tail] = firstFree;
            break;
        }
    }
//    std::cout << "For insertion of elem " << e << ", next list is: (head is " << head << ")\n";
//    for(int i = 0; i < cap; i ++) {
//        std::cout << next[i] << ' ';
//    }
//    std::cout << '\n';
}

SortedIteratedList::~SortedIteratedList() {
    delete[] elem;
    delete[] next;
    delete[] prev;
}

// o(1)...
int SortedIteratedList::allocateP() {
    if(length == cap-1) {
        cap *= 2;
        //...
        TComp* newElem = new TComp [cap];
        for(int i = 0; i <= cap/2; i ++) {
            newElem[i] = elem[i];
        }
        delete[] elem;
        elem = newElem;
        TComp* newNext = new TComp [cap];
        for(int i = 0; i <= cap/2; i ++) {
            newNext[i] = next[i];
        }
        delete[] next;
        next = newNext;
        TComp* newPrev = new TComp [cap];
        for(int i = 0; i <= cap/2; i ++) {
            newPrev[i] = prev[i];
        }
        delete[] prev;
        prev = newPrev;
        for(int i = cap/2; i < cap-1; i ++) {
            next[i] = i+1;
            prev[i+1] = i;
        }
        next[firstFree] = cap/2;
        prev[cap/2] = firstFree;
        next[cap-1] = -1;
    }
    int newFreePos = firstFree;
    firstFree = next[newFreePos];

    length ++;
    return newFreePos;
}

// tetha(1)
void SortedIteratedList::freeP(int i) {
    next[i] = firstFree;
    firstFree = i;
    length--;
}

// O(n)
// bc Tetha(1)
// wc Tetha(n)
//ListIterator SortedIteratedList::lastIndexOf(TComp elem) const {
//    auto it = ListIterator(*this);
//    auto last = ListIterator(*this);
//    bool found = false;
////    last.makeInvalid();
//    for(; it.valid(); it.next()) {
//        if(it.getCurrent() == elem) {
//            last = it;
//            found = true;
//        } else if(found == true)
//            break;
//    }
//    if(found == false)
//        return it; // which is an invalid iterator
//    else
//        return last;
//}


// O(n)
// bc Tetha(1)
// wc Tetha(n)
ListIterator SortedIteratedList::lastIndexOf(TComp e) const {
    auto it = ListIterator(*this);
    for(it.last(); it.valid(); it.prev()) {
        if(it.getCurrent() == e) {
            return it;
        }
    }
    return it;
}