#ifndef HASHSET_H
#define HASHSET_H

template <typename Key>
class HashSet
{
    static_assert(
        sizeof(Key) == 0, "Unsupported key type.\n"
        );

};

template<>
class HashSet<double> {

private:
    size_t size;
    struct Line {

    };

public:
    HashSet(size_t size = 10) : size(size) {

    }
};

#endif