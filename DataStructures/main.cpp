#include <iostream>
#include "HashSet.h"
#include <unordered_set>

int main() {
    HashSet<double> hashSet (18, true);
    std::cout << hashSet.getSize();
    return 0;
}