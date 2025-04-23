#include <iostream>
#include "HashSet.h"
#include <unordered_set>
#include <random>

int main() {
    HashSet<double> hashSet (1);

    std::random_device rd;                      
    std::mt19937 gen(rd());                     
    std::uniform_real_distribution<> dist(0.0, 1.0);

    std::cout << hashSet.getSize() << '\n';
    hashSet.insert(dist(gen));
    hashSet.insert(dist(gen));
    hashSet.insert(0.6);
    std::cout << hashSet[0.6] << '\n';
    std::cout << hashSet[0.5]<< '\n';
    hashSet.remove(0.6);
    std::cout << hashSet[0.6] << '\n';
    //hashSet.insert(dist(gen));

    std::cout << hashSet;
    //for (auto i : hashSet) {
    //    std::cout << i << '\n';
    //}
    return 0;
}