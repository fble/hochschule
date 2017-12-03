#include "../includes/DoubleLinkedList.h"

template<class Value> DoublyLinkedList<Value>::DoublyLinkedList() : first(), lastGot(), last(), length(), lastGotIndex() {

}

template<class Value> DoublyLinkedList<Value>::~DoublyLinkedList() {
    if (length != 0) {
        delete first;
    }
}

template<class Value> void DoublyLinkedList<Value>::addLast(Value* value) {
    ListElement* addme = new ListElement(value);
    if (length != 0) {
        last->next = addme;
        addme->previous = last;
    } else {
        first = addme;
        lastGot = addme;
    }
    last = addme;
    length++;
}

template<class Value> unsigned int DoublyLinkedList<Value>::getSize() {
    return length;
}

template<class Value> Value* DoublyLinkedList<Value>::get(unsigned int nr) {
    if (nr < 0 || length <= nr) {
        throw std::out_of_range("Index out of range - DoublyLinkedList.get()");
        return 0;
    } else if (nr == lastGotIndex) {
        // return the same as before
    } else if (nr == lastGotIndex + 1) {
        // sequential +
        lastGot = lastGot->next;
    } else if (nr == lastGotIndex - 1) {
        // sequential -
        lastGot = lastGot->previous;
    } else {
        // some random index
        bool forward;
        if (nr < lastGotIndex) {
            if (nr < lastGotIndex-nr) {
                // shortest: first -> nr (+)
                lastGot = first;
                lastGotIndex = 0;
                forward = true;
            } else {
                // shortest: lastGot -> nr (-)
                forward = false;
            }
        } else {
            if (nr - lastGotIndex < length - nr) {
                // shortest: lastGot -> nr (+)
                forward = true;
            } else {
                // shortest: last -> nr (-)
                lastGot = last;
                lastGotIndex = length - 1;
                forward = false;
            }
        }
        if (forward) {
            for (int i = lastGotIndex; i < nr; i++) {
                lastGot = lastGot->next;
            }
        } else {
            for (int i = lastGotIndex; i > nr; i--) {
                lastGot = lastGot->previous;
            }
        }
    }
    lastGotIndex = nr;
    return lastGot->value;
}

template<class Value> DoublyLinkedList<Value>::ListElement::ListElement(Value* value) : next(), previous() {
    this->value = value;
}

template<class Value> DoublyLinkedList<Value>::ListElement::~ListElement() {
    if (next != 0) {
        delete next;
    }
    //TODO do I have to delete the content?
    delete value;
}

