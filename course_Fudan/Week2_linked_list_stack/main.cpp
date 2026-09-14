#include <iostream>

#include "singly_list.h"

int main() {
    using namespace fudan_ds::lec03;

    LinkList list = nullptr;
    initList(list);

    pushBack(list, 2);
    pushFront(list, 1);
    pushBack(list, 3);

    std::cout << "After insertion: ";
    printList(list);
    std::cout << '\n';

    int removed = 0;
    if (popFront(list, removed)) {
        std::cout << "Removed: " << removed << '\n';
    }

    std::cout << "After removal: ";
    printList(list);
    std::cout << '\n';

    destroyList(list);
    return 0;
}

