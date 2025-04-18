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
    static size_t quadraticProbe(size_t hash, size_t attempt, size_t capacity) {
        return (hash + ((attempt % 2 == 0) ? -1 : 1) * (attempt * attempt) / 2) % capacity;
    }
    struct Line {
        double* key_ = nullptr;
        bool isDeleted_ = false;
    };
    size_t size_;
    size_t number_;
    Line* table_;

public:
    static int calculateHash(double value, int k) {
        return value * k;
    }
    HashSet() : size_(100), table_(new Line[100]) {};
    HashSet(size_t size, bool makePrime = false) : size_(size) {
        if (!makePrime) {
            table_ = new Line[size];
            return;
        }
        table_ = new Line[((size % 3 == 0) ? size + 1 : size) * 4 + 3];
    }
    ~HashSet() noexcept {
        delete[] table_;
    }
    HashSet(HashSet&& hashSet) = delete;
    HashSet(const HashSet& hashSet) = delete;
    HashSet& operator= (HashSet&& hashSet) = delete;
    HashSet& operator= (const HashSet& hashSet) = delete;

    size_t getNumber() const noexcept{
        return number_;
    }


};

#endif