#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedIteratedList.h"
#include "ListIterator.h"

bool cmp(TComp e1, TComp e2) {
    return e1 < e2;
}

void myOwnTests() {
    SortedIteratedList a = SortedIteratedList(cmp);
    a.add(2);
    a.add(9);
    a.add(6);
    a.add(3);
    a.add(4);
    std::cout << "\nWhole list:\n";
    for(auto it = a.first(); it.valid(); it.next()) {
        std::cout << it.getCurrent() << ' ';
    }
    std::cout << '\n';
    auto it4 = a.search(4);
    a.remove(it4);

    std::cout << "\nWhole list:\n";
    for(auto it = a.first(); it.valid(); it.next()) {
        std::cout << it.getCurrent() << ' ';
    }

    a.add(5);
    std::cout << "\nWhole list:\n";
    for(auto it = a.first(); it.valid(); it.next()) {
        std::cout << it.getCurrent() << ' ';
    }
    std::cout << "It validations:\n";
    std::cout << a.search(2).valid() << '\n';
    std::cout << a.search(10).valid() << '\n';
    std::cout << a.search(9).valid() << '\n';
    std::cout << a.search(4).valid() << '\n';
    std::cout << a.search(3).valid() << '\n';
    std::cout << a.lastIndexOf(10).getCurrent() << '\n';
    assert(a.lastIndexOf(9).getCurrent() == 9);

    auto it = a.first();
    for(it.last(); it.valid(); it.prev()) {
        std::cout << it.getCurrent() << ' ';
    }
    std::cout << '\n';

    auto toremove = a.search(5);
    a.remove(toremove);

    for(it.last(); it.valid(); it.prev()) {
        std::cout << it.getCurrent() << ' ';
    }
    std::cout << '\n';


    auto toremove2 = a.search(9);
    a.remove(toremove2);

    for(it.last(); it.valid(); it.prev()) {
        std::cout << it.getCurrent() << ' ';
    }
    std::cout << '\n';

    auto toremove3 = a.search(2);
    a.remove(toremove3);

    for(it.last(); it.valid(); it.prev()) {
        std::cout << it.getCurrent() << ' ';
    }
    std::cout << '\n';

    a.add(1);
    a.add(5);
    a.add(99);

    for(it.last(); it.valid(); it.prev()) {
        std::cout << it.getCurrent() << ' ';
    }
    std::cout << '\n';
}

int main(){
//    myOwnTests();
//    std::cout << "Finished my own tests!" << std::endl;
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
//	system("pause");
}