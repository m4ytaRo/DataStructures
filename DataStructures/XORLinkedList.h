#ifndef XORLINKED_LIST_H
#define XORLINKED_LIST_H

#include <cstdint>

template <class T>
class XORLinkedList
{
private:
    struct Node {
        T data;
        Node* xorProduct;
        Node(const T& data, Node* xorProduct = nullptr) {};
    };
    Node* getXorProduct(Node* a, Node* b);
    Node* head;
public:
    XORLinkedList() : head(nullptr) {};
    XORLinkedList(XORLinkedList&& list) = delete;
    XORLinkedList(const XORLinkedList& list) = delete;
    XORLinkedList& operator=(XORLinkedList&& list) = delete;
    XORLinkedList& operator=(const XORLinkedList& list) = delete;

    void insert(const T& data);
    void remove();
    void remove(const T& data, int number);
};

template <class T>
typename XORLinkedList<T>::Node* XORLinkedList<T>::getXorProduct(typename XORLinkedList<T>::Node* a, typename XORLinkedList<T>::Node* b) {
    return reinterpret_cast<Node*> (reinterpret_cast<uintptr_t> (a) ^ reinterpret_cast<uintptr_t> (b));
    /*
    We cant do xor operations with Node pointer
    Thus, we use uintptr_t - type, which is designed to store pointers as integer values
    At the end we cast value back to Node pointer
    */
}

template <class T>
void XORLinkedList<T>::insert(const T& data) {

}

template <class T>
void XORLinkedList<T>::remove() {

}

template <class T>
void XORLinkedList<T>::remove(const T& data, int number) {

}
#endif