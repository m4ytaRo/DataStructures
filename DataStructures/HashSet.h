#ifndef HASHSET_H
#define HASHSET_H

#include <stdexcept>
#include <type_traits> //for SFINAE in class with using IsCorrectType
#include <limits> 



namespace mutils {
    template <typename T>
    struct IsCorrectType : std::false_type {};

    template <>
    struct IsCorrectType<double> : std::true_type {};

    //It was not my task
    //template <>
    //struct IsCorrectType<std::string> : std::true_type {};
}


template <typename Key, typename = std::enable_if_t<mutils::IsCorrectType<Key>::value>>
class HashSet
{

private:
    static constexpr float LOAD_FACTOR = 0.75f;
    static constexpr unsigned short int smallPrimes[] = {
        5, 11, 17, 23, 37, 53, 79, 97, 131, 193,
        257, 389, 521, 769, 1031, 1543, 2053, 3079,
        4099, 6151, 8209, 12289, 16381, 24593, 32771, 49157, 65521
    };
    static constexpr unsigned int largePrimes[] = {
            131101, 262147, 524309, 1048583,
            2097169, 4194319, 8388617, 16777259
    };

    static size_t quadraticProbe(size_t hash, size_t attempt, size_t capacity) {
        return (static_cast<size_t>(hash + 0.5 * attempt + 0.5 * attempt * attempt)) % capacity;
    }

    struct Line {
        ~Line() { delete key_; }
        Key* key_ = nullptr;
        bool isDeleted_ = false;
    };

    class Iterator {
    public:
        Iterator(Line* table, size_t index, size_t size) : table_(table), index_(index), size_(size) {
            goToNextValid();
        }

        Key& operator* () {
            return *table_[index_].key_;
        }

        Iterator& operator++() {
            index_++;
            goToNextValid();
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return index_ != other.index_ || table_ != other.table_;
        }

    private:
        void goToNextValid() {
            while (index_ < size_) {
                if (table_[index_].key_ && !table_[index_].isDeleted_)
                    break;
                ++index_;
            }
        }
        size_t index_;
        size_t size_;
        Line* table_;

    };

    size_t size_;
    size_t number_;
    Line* table_;

public:

    static size_t calculateHash(double value, size_t capacity) {
        return value * capacity;
    }

    size_t getNextSize(size_t size) {
        for (const size_t i : smallPrimes) {
            if (i > size)
                return i;
        }
        for (const size_t i : largePrimes) {
            if (i > size)
                return i;
        }
        if (size > (std::numeric_limits<size_t>::max() - 1) / 2)
            throw std::overflow_error("Hash table size overflow");
        return size * 2 + 1;
    }

    HashSet() : size_(100), table_(new Line[100]) {};
    HashSet(size_t size, bool makePrime = true) : size_(size) {
        if (makePrime)
            size_ = getNextSize(size_);
        table_ = new Line[size_];

    }
    ~HashSet() noexcept {
        delete[] table_;
    }
    HashSet(HashSet&& hashSet) = delete;
    HashSet(const HashSet& hashSet) = delete;
    HashSet& operator= (HashSet&& hashSet) = delete;
    HashSet& operator= (const HashSet& hashSet) = delete;

    size_t getNumber() const noexcept {
        return number_;
    }

    size_t getSize() const noexcept {
        return size_;
    }

    void rehash() {
        Line* newTable = nullptr;
        for (int attempt = 0; attempt < 5; ++attempt) {
            //global attempts to rehash
            size_t newSize = size_;
            newSize = getNextSize(newSize);
            delete[] newTable;
            newTable = new Line[newSize];

            bool flagSuccessfullyTransitioned = true;

            for (int i = 0; i < size_; ++i) { //going through all previous table
                if (!table_[i].key_)
                    continue;
                const size_t initialHash = calculateHash(*table_[i].key_, newSize);
                size_t pos = initialHash;
                bool flagPositionFound = false;
                for (size_t j = 0; j < newSize; ++j) {  //trying to calculate hash exactly newSize times
                    
                    pos = quadraticProbe(pos, j, newSize);
                    if (!newTable[pos].key_ || newTable[pos].isDeleted_) {
                        if (newTable[pos].isDeleted_) {
                            delete newTable[pos].key_;
                        }
                        newTable[pos].key_ = new Key(*table_[i].key_);
                        newTable[pos].isDeleted_ = false;
                        flagPositionFound = true;
                        break;
                    }

                }
                if (!flagPositionFound) { //if we didnt find position for at least one object, we need to rehash
                    flagSuccessfullyTransitioned = false;
                    break;
                }
            }
            if (flagSuccessfullyTransitioned) {
                delete[] table_;
                table_ = newTable;
                size_ = newSize;
                return;
            }

        }
        delete[] newTable;
        throw std::runtime_error("Unexpected error while rehashing\n");
    }

    bool insert(const Key& key) {
        if (number_ + 1 >= size_ * LOAD_FACTOR)
            rehash();
        const size_t initialHash = calculateHash(key, size_);
        for (int globalAttempt = 0; globalAttempt < 5; ++globalAttempt) {
            size_t pos = initialHash;
            for (int i = 0; i < size_; ++i) {
                pos = quadraticProbe(pos, i, size_);
                if (table_[pos].key_ && *table_[pos].key_ == key)
                    return false;
                if (!table_[pos].key_ || table_[pos].isDeleted_) {
                    if (table_[pos].isDeleted_) {
                        delete table_[pos].key_;
                    }
                    table_[pos].key_ = new Key(key);
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

    bool operator[] (const Key& key) {
        const size_t initialHash = calculateHash(key, size_);
        size_t pos = initialHash;
        for (size_t i = 0; i < size_; ++i) {
            pos = quadraticProbe(pos, i, size_);
            if (table_[i].key_ && key == *table_[i].key_) {
                if (!table_[i].isDeleted_)
                    return true;
                return false;
            }
                
        }
        return false;
    }

    bool remove(const Key& key) {
        const size_t initialHash = calculateHash(key, size_);
        size_t pos = initialHash;
        for (size_t i = 0; i < size_; ++i) {
            pos = quadraticProbe(pos, i, size_);
            if (table_[i].key_ && key == *table_[i].key_) {
                if (!table_[i].isDeleted_) {
                    table_[i].isDeleted_ = true;
                    return true;
                }
                    
                return false;
            }

        }
        return false;
    }

    Iterator begin() {
        return Iterator(table_, 0, size_);
    }    
    Iterator end() {
        return Iterator(table_, size_, size_);
    }
};


#endif