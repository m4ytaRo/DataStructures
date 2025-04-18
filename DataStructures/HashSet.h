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
    
    struct Line {
        double* key_ = nullptr;
        bool deleted_ = false;
    };
    size_t size_;
    size_t number_;
    Line* table_;

public:
    static int calculateHash(double value, double k) {
        return value * k;
    }
    HashSet() : size_(100), table_(new Line[100]) {};
    HashSet(size_t size) : size_(size), table_(new Line[size]) {

    }
};

#endif