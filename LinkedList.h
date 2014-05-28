/** @file */
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H
//链表

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T>
class LinkedList {
friend class Iterator;
private:
struct node {
    T data;
    node * prev, * next;
    node(){
        prev = next = 0;
    }
    node(T x){
        data = x;
        prev = next = 0;
    }
};
node * head, * tail;
int total;
long long opCnt;
public:
    class Iterator{
    private:
        LinkedList::node * pt;
        LinkedList * owner;
        long long opCnt;
        bool removed;
    public:
        Iterator(LinkedList * ll){
            owner = ll;
            pt = ll->head;
            opCnt = owner->opCnt;
            removed = false;
        }
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
            if (pt->next->next != 0) return true;
            return false;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next() {
            if (!hasNext()){throw ElementNotExist("");}
            pt = pt->next;
            removed = false;
            return pt->data;
        }

        /**
         * TODO Removes from the underlying collection the last element
         * returned by the iterator
         * The behavior of an iterator is unspecified if the underlying
         * collection is modified while the iteration is in progress in
         * any way other than by calling this method.
         * @throw ElementNotExist
         */
        void remove() {
            if (opCnt != owner->opCnt || !pt->prev || !pt->next || removed){throw ElementNotExist("");}
            ++opCnt;
            ++owner->opCnt;
            pt = pt->prev;
            LinkedList::node * tmp = pt->next;
            pt->next = pt->next->next;
            pt->next->prev = pt;
            --owner->total;
            delete tmp;
            removed = true;
            return;
        }
    };
   

    /**
     * TODO Constructs an empty linked list
     */
    LinkedList() {
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prev = head;
        total = 0;
        opCnt = 0;
    }

    /**
     * TODO Copy constructor
     */
    LinkedList(const LinkedList<T> &c) {
        head = new node();
        tail = new node();
        total = c.total;
        node * p1 = c.head->next;
        node * p = head;
        for (int i = 0; i < c.total; ++i){
            node * newNode = new node(p1->data);
            p -> next = newNode;
            newNode->prev = p;
            p = p->next;
            p1 = p1->next;
        }
        tail->prev = p;
        p->next = tail;
        opCnt = 0;
    }

    /**
     * TODO Assignment operator
     */
    LinkedList<T>& operator=(const LinkedList<T> &c) {
        clear();
        total = c.total;
        node * p1 = c.head->next;
        node * p = head;
        for (int i = 0; i < c.total; ++i){
            node * newNode = new node(p1->data);
            p -> next = newNode;
            newNode->prev = p;
            p = p->next;
            p1 = p1->next;
        }
        tail->prev = p;
        p->next = tail;
        opCnt = c.opCnt;
        return *this;
    }

    /**
     * TODO Desturctor
     */
    ~LinkedList() {
        node * p = head;
        while (p != tail){
            p = p->next;
            delete p->prev;
        }
        delete p;
    }

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e) {
        addLast(e);
        return true;
    }

    /**
     * TODO Inserts the specified element to the beginning of this list.
     */
    void addFirst(const T& elem) {
        ++opCnt;
        node * newNode = new node(elem);
        newNode->prev = head;
        newNode->next = head->next;
        newNode->next->prev = newNode;
        head->next = newNode;
        ++total;
    }

    /**
     * TODO Insert the specified element to the end of this list.
     * Equivalent to add.
     */
    void addLast(const T &elem) {
        node * newNode = new node(elem);
        newNode->next = tail;
        newNode->prev = tail->prev;
        newNode->prev->next = newNode;
        tail->prev = newNode;
        ++total;
        ++opCnt;
    }

    /**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index=size means appending to the end.
     * @throw IndexOutOfBound
     */
    void add(int index, const T& element) {
        if (index > total || index < 0){throw IndexOutOfBound();}
        node * p = head, * newNode = new node(element);
        for (int i = 0; i < index; ++i){
            p = p->next;
        }
        newNode->prev = p;
        newNode->next = p->next;
        p->next = newNode;
        newNode->next->prev = newNode;
        ++total;
        ++opCnt;
        return;
    }

    /**
     * TODO Removes all of the elements from this list.
     */
    void clear() {
        node * p = head->next;
        while (p != tail){
            p = p->next;
            delete p->prev;
        }
        head->next = tail;
        tail->prev = head;
        total = 0;
        ++opCnt;
        return;
    }

    /**
     * TODO Returns true if this list contains the specified element.
     */
    bool contains(const T& e) const {
        node * p = head->next;
        while (p != tail){
            if (p->data == e){
                return true;
            }
            p = p->next;
        }
        return false;
    }

    /**
     * TODO Returns a const reference to the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const {
        if ((index >= total) || (index < 0)){
            throw IndexOutOfBound();
        }
        node * p = head->next;
        for (int i = 0; i < index; ++i){
            p = p->next;
        }
        return p->data;
    }

    /**
     * TODO Returns a const reference to the first element.
     * @throw ElementNotExist
     */
    const T& getFirst() const {
        if (total == 0){throw ElementNotExist("");}
        return head->next->data;
    }

    /**
     * TODO Returns a const reference to the last element.
     * @throw ElementNotExist
     */
    const T& getLast() const {
        if (total == 0){throw ElementNotExist("");}
        return tail->prev->data;
    }

    /**
     * TODO Returns true if this list contains no elements.
     */
    bool isEmpty() const {
        return !total;
    }

    /**
     * TODO Removes the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void removeIndex(int index) {
        if (index < 0 || index >= total){throw IndexOutOfBound();}
        node * p = head->next;
        for (int i = 0; i < index; ++i){
            p = p->next;
        }
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --total;
        ++opCnt;
        return;
    }

    /**
     * TODO Removes the first occurrence of the specified element from this list, if it is present.
     * Returns true if it was present in the list, otherwise false.
     */
    bool remove(const T &e) {
        node * p = head->next;
        while (p != tail){
            if (p->data == e){break;}
            p = p->next;
        }
        if (p == tail){return false;}
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --total;
        ++opCnt;
        return true;
    }

    /**
     * TODO Removes the first element from this list.
     * @throw ElementNotExist
     */
    void removeFirst() {
        if (total == 0){throw ElementNotExist("");}
        node * p = head->next;
        head->next = p->next;
        p->next->prev = head;
        delete p;
        --total;
        ++opCnt;
        return;
    }

    /**
     * TODO Removes the last element from this list.
     * @throw ElementNotExist
     */
    void removeLast() {
        if (total == 0){throw ElementNotExist("");}
        node * p = tail->prev;
        tail->prev = p->prev;
        p->prev->next = tail;
        delete p;
        --total;
        ++opCnt;
        return;
    }

    /**
     * TODO Replaces the element at the specified position in this list with the specified element.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void set(int index, const T &element) {
        if (index < 0 || index >= total){throw IndexOutOfBound();}
        node * p = head->next;
        for (int i = 0; i < index; ++i){
            p = p->next;
        }
        p->data = element;
        ++opCnt;
    }

    /**
     * TODO Returns the number of elements in this list.
     */
    int size() const {
        return total;
    }

    /**
     * TODO Returns an iterator over the elements in this list.
     */
    Iterator iterator() {
        Iterator result(this);
        return result;
    }
};

#endif
