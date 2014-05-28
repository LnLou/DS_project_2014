/** @file */
#ifndef __PRIORITYQUEUE_H
#define __PRIORITYQUEUE_H

#include "ArrayList.h"
#include "ElementNotExist.h"
#include "Less.h"

/**
 * This is a priority queue based on a priority priority queue. The
 * elements of the priority queue are ordered according to their 
 * natual ordering (operator<), or by a Comparator provided as the
 * second template parameter.
 * The head of this queue is the least element with respect to the
 * specified ordering (different from C++ STL).
 * The iterator does not return the elements in any particular order.
 * But it is required that the iterator will eventually return every
 * element in this queue (even if removals are performed).
 */

template <class V, class C = Less<V> >
class PriorityQueue{
friend class Iterator;
private:
    struct node{
        V data;
        int index;
        node * prev, * next;
        node (const V & x, int i = 0, node * p = 0, node * n = 0){
            data = x;
            index = i;
            prev = p;
            next = n;
        }
        node (){
            index = 0;
            prev = next = 0;
        }
    };
    node * head, * tail, ** data;
    int maxSize, currentSize;
    long long opCnt;
    C Cmp;
    inline bool cmp(int a, int b){
        return Cmp(data[a]->data, data[b]->data);
    }
    inline void swap(int a, int b){
        node * tmp = data[a];
        data[a] = data[b];
        data[b] = tmp;
        data[a]->index = a;
        data[b]->index = b;
    }
    void heapify(int i){
        int l = 2*i, r = 2*i + 1;
        while (currentSize >= l){
            if (currentSize >= r){
                if (!cmp(l, i) && !cmp (r, i)){break;}
                if (cmp(l, r)){
                    swap(i, l);
                    i = l;
                }
                else {
                    swap(i, r);
                    i = r;
                }
            }
            else {
                if (!cmp(l, i)){break;}
                swap(i, l);
                i = l;
            }
            l = 2*i;
            r = l+1;
        }
        return;
    }
    void doubleSpace(){
        maxSize *= 2;
        node ** tmp = data;
        data = new node*[maxSize];
        data[0] = head;
        for (int i = 1; i <= currentSize; ++i){
            data[i] = tmp[i];
        }
        data[currentSize]->next = tail;
        tail->prev = data[currentSize];
        delete [] tmp;
    }
public:
    class Iterator {
    private:
        PriorityQueue * owner;
        PriorityQueue::node * nd;
        long long opCnt;
        bool removed;
    public:
        Iterator(PriorityQueue * pq, PriorityQueue::node * x){
            owner = pq;
            nd = x;
            opCnt = owner->opCnt;
            removed = false;
        }
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
            return (nd->next != owner->tail) ;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const V &next() {
            if (!hasNext()){throw ElementNotExist();}
            removed = false;
            nd = nd->next;
            return nd->data;
        }

        /**
         * TODO Removes from the underlying collection the last element
         * returned by the iterator.
         * The behavior of an iterator is unspecified if the underlying
         * collection is modified while the iteration is in progress in
         * any way other than by calling this method.
         * @throw ElementNotExist
         */
        void remove() {
            if (removed || !nd->prev || !nd->next || opCnt != owner->opCnt){
                throw ElementNotExist();
            }
            removed = true;
            node * tmp = nd;
            owner->swap(nd->index, owner->currentSize);
            --owner->currentSize;
            if (owner->cmp(nd->index / 2, nd->index)){
                owner->heapify(nd->index);
            }
            else {
                for (int i = nd->index; i > 1; i = i>>1){
                    if (!owner->cmp(nd->index / 2, nd->index)){
                        owner->swap(nd->index / 2, nd->index);
                    }
                    else {break;}
                }
            }
            delete tmp;
        }
    };

    /**
     * TODO Constructs an empty priority queue.
     */
    PriorityQueue(int size = 16) {
        head = new node;
        tail = new node;
        head->next = tail;
        tail->prev = head;
        data = new node*[size];
        data[0] = head;
        maxSize = size;
        currentSize = 0;
        opCnt = 0;
    }

    /**
     * TODO Destructor
     */
    ~PriorityQueue() {
        for (int i = 0; i <= currentSize; ++i){
            delete data[i];
        }
        delete tail;
        delete [] data;
    }

    /**
     * TODO Assignment operator
     */
    PriorityQueue &operator=(const PriorityQueue &x) {
        clear();
        while (maxSize <= x.currentSize){doubleSpace();}
        currentSize = x.currentSize;
        data[0] = head;
        for (int i = 1; i <= currentSize; ++i){
            node * tmp = x.data[i];
            data[i] = new node(tmp->data, tmp->index);
            data[i-1]->next = data[i];
            data[i]->prev = data[i-1];
        }
        data[currentSize]->next = tail;
        tail->prev = data[currentSize];
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    PriorityQueue(const PriorityQueue &x) {
        head = new node();
        tail = new node();
        maxSize = x.maxSize;
        data = new node*[x.maxSize];
        data[0] = head;
        currentSize = x.currentSize;
        for (int i = 1; i <= currentSize; ++i){
            node * tmp = x.data[i];
            data[i] = new node(tmp->data, i);
            data[i-1]->next = data[i];
            data[i]->prev = data[i-1];
        }
        data[currentSize]->next = tail;
        tail->prev = data[currentSize];
        opCnt = 0;
    }

    /**
     * TODO Initializer_list-constructor
     * Constructs a priority queue over the elements in this Array List.
     * Requires to finish in O(n) time.
     */
    PriorityQueue(const ArrayList<V> &x) {
        opCnt = 0;
        head = new node();
        tail = new node();
        head -> next = tail;
        tail -> prev = head;
        currentSize = x.size();
        maxSize = 256;
        while (maxSize <= currentSize){maxSize *= 2;}
        data = new node * [maxSize];
        data[0] = head;
        for (int i = 0; i < currentSize; ++i){
            data[i+1] = new node(x.get(i), i+1, data[i]);
            data[i]->next = data[i+1];
        }
        data[currentSize]->next = tail;
        tail->prev = data[currentSize];
        for (int i = currentSize / 2; i > 0; --i){
            heapify(i);
        }
    }

    /**
     * TODO Returns an iterator over the elements in this priority queue.
     */
    Iterator iterator() {
        Iterator result(this, head);
        return result;
    }

    /**
     * TODO Removes all of the elements from this priority queue.
     */
    void clear() {
        for (int i = 1; i <= currentSize; ++i){
            delete data[i];
        }
        head->next = tail;
        tail->prev = head;
        currentSize = 0;
        ++opCnt;
    }

    /**
     * TODO Returns a const reference to the front of the priority queue.
     * If there are no elements, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &front() const {
        if (currentSize == 0){throw ElementNotExist();}
        return data[1]->data;
    }

    /**
     * TODO Returns true if this PriorityQueue contains no elements.
     */
    bool empty() const {
        return !currentSize;
    }

    /**
     * TODO Add an element to the priority queue.
     */
    void push(const V &value) {
        ++opCnt;
        if (currentSize + 2 >= maxSize){doubleSpace();}
        ++currentSize;
        data[currentSize] = new node(value, currentSize, head, head->next);
        head->next->prev = data[currentSize];
        head->next = data[currentSize];
        for (int i = currentSize; i > 1; i = i>>1){
            if (!cmp(i/2, i)){
                swap(i/2, i);
            }
            else {break;}
        }
    }

    /**
     * TODO Removes the top element of this priority queue if present.
     * If there is no element, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void pop() {
        ++opCnt;
        swap(1, currentSize);
        delete data[currentSize];
        --currentSize;
        heapify(1);
    }

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const {
        return currentSize;
    }
};

#endif
