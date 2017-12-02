//
// Created by stefan on 02.12.17.
//

#ifndef TREE_INCLUDES_DOUBLELINKEDLIST
#define TREE_INCLUDES_DOUBLELINKEDLIST

template <class Value>
/**
 * A simple generic Linked List storing key-value-pairs.
 * Value is generic, key is fixed to char*.
 * @author Benjamin Büscher
 */
class DoublyLinkedList {
public:

    /**
     * Creates an instance of LinkedList.
     */
    DoublyLinkedList();

    /**
     * deletes the LinkedList.
     */
    virtual ~DoublyLinkedList();

    /**
     * adds the given value at the end of the list.
     * @param value the value to be added
     */
    void addLast(Value* value);

    /**
     * returns the value at the given index (nr).
     * @return the value at index nr
     */
    Value* get(unsigned int nr);

    /**
     * returns the number of elements in this list.
     * @return number of elements in this list
     */
    unsigned int getSize();
private:
    class ListElement {
    public:
        ListElement(Value* value);
        virtual ~ListElement();

        ListElement* next;
        ListElement* previous;
        Value* value;
    };

    //so nen dateityp: int, Value* = directData
    //Dann: directData lastReturned;, um schnelleres sequenzielles durchlaufen zu bauen.

    ListElement* first;
    ListElement* lastGot;
    ListElement* last;
    unsigned int length;
    unsigned int lastGotIndex;

};
#include "../src/DoublyLinkedList.cpp"

#endif TREE_INCLUDES_DOUBLELINKEDLIST
