#ifndef XORLINKED_LIST_H
#define XORLINKED_LIST_H

#include <cstdint>
#include <ostream>

template <class T>
class XORLinkedList
{
private:
    struct Node {
        T data;
        Node* xorProduct;
        Node(const T& data, Node* xorProduct = nullptr) : data(data), xorProduct(xorProduct) {};
    };

    template <class U>
    friend std::ostream& operator << (std::ostream& out, const XORLinkedList<U>& list);

    Node* getXorProduct(Node* a, Node* b) const;
    Node* head;
    Node* tail;
public:
    XORLinkedList() : head(nullptr), tail(nullptr) {};
    XORLinkedList(XORLinkedList&& list) = delete;
    XORLinkedList(const XORLinkedList& list) = delete;
    XORLinkedList& operator=(XORLinkedList&& list) = delete;
    XORLinkedList& operator=(const XORLinkedList& list) = delete;

    bool insert(const T& data, int positionIndex);
    void push_back(const T& data);
    void push_front(const T& data);
    void pop_back();
    void pop_front();
    void remove(const T& data, int number);
    T& front();
    T& back();
    void print(std::ostream& out) const;
};

template <class T>
typename XORLinkedList<T>::Node* XORLinkedList<T>::getXorProduct(typename XORLinkedList<T>::Node* a, typename XORLinkedList<T>::Node* b) const{
    return reinterpret_cast<Node*> (reinterpret_cast<uintptr_t> (a) ^ reinterpret_cast<uintptr_t> (b));
    /*
    We cant do xor operations with Node pointer
    Thus, we use uintptr_t - type, which is designed to store pointers as integer values
    At the end we cast value back to Node pointer
    */
}

template <class T>
bool XORLinkedList<T>::insert(const T& data, int positionIndex) {

}

template <class T>
void XORLinkedList<T>::push_back(const T& data) {
    if (!head) {
        head = tail = new Node(data, getXorProduct(nullptr, nullptr));
    }
    else {
        Node* prevTail = tail;
        Node* prevPrev = getXorProduct(prevTail->xorProduct, nullptr); // getting the adress of tail's prev element
        tail = new Node(data, getXorProduct(nullptr, prevTail));
        prevTail->xorProduct = getXorProduct(prevPrev, tail);
    }
}

template <class T>
void XORLinkedList<T>::push_front(const T& data) {

}

template <class T>
void XORLinkedList<T>::pop_front() {

}

template <class T>
void XORLinkedList<T>::pop_back() {

}

template <class T>
T& XORLinkedList<T>::front() {
    
}

template <class T>
T& XORLinkedList<T>::back() {

}

template <class T>
void XORLinkedList<T>::remove(const T& data, int number) {

}

template <class T>
void XORLinkedList<T>::print (std::ostream& out) const{
    if (!head) {
        out << "List is empty\n";
        return;
    }
    Node* ptr = head;
    Node* ptrPrev = nullptr;
    while (ptr) {
        out << ptr->data << ' ';
        Node* next = getXorProduct(ptr->xorProduct, ptrPrev);
        ptrPrev = ptr;
        ptr = next;
    }
    out << '\n';
}

template <class T>
std::ostream& operator << (std::ostream& out, const XORLinkedList<T>& list) {
    list.print(out);
    return out;
}
#endif