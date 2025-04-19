#ifndef HASHSET_H
#define HASHSET_H

#include <stdexcept>

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
    static size_t quadraticProbe1(size_t hash, size_t attempt, size_t capacity) {
        return (hash + attempt * attempt) % capacity;
    }

    static size_t quadraticProbe2(size_t hash, size_t attempt, size_t capacity) {
        return (hash + 2 * attempt * attempt) % capacity; 
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
        if (makePrime) 
            size = ((size % 3 == 0) ? size + 1 : size) * 4 + 3;
        table_ = new Line[size];
        
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

    void rehash() {
        
    }

    bool insert(double key) {
        if (number_ >= size_ * 0.7)
            rehash();
        const size_t initialHash = calculateHash(key, size_);
        for (int globalAttempt = 0; globalAttempt < 5; ++globalAttempt) {
            size_t pos = initialHash;
            for (int i = 0; i < size_ / 2; ++i) {
                pos = quadraticProbe1(pos, i, size_);
                if (table_[pos].key_ && *table_[pos].key_ == key)
                    return false;
                if (!table_[pos].key_ || table_[pos].isDeleted_) {
                    if (table_[pos].isDeleted_) {
                        delete table_[pos].key_;
                    }
                    table_[pos].key_ = new double (key);
                    table_[pos].isDeleted_ = false;
                    ++number_;
                    return true;
                }
            }
            rehash();

        }

        throw std::runtime_error("Unexpected error while inserting element");
        return false;

    }
};

#endif