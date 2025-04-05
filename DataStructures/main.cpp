#include <iostream>
#include "XORLinkedList.h"

int main() {
    XORLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    std::cout << list;
    return 0;
}