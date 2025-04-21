#include <iostream>
#include "HashSet.h"
#include <unordered_set>

int main() {
    HashSet<double> hashSet (100);
    std::cout << hashSet.getSize();
    hashSet.insert(0.1);
    for (auto i : hashSet) {
        std::cout << i;
    }
    return 0;
}