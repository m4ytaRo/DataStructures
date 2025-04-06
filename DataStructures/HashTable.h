#pragma once

template <typename Key, typename Value>
class HashTable
{
    static_assert(
        sizeof(Key) == 0, "Unsupported key type.\n"
        );

};

template <typename Value>
class HashTable<double, Value> {

};
