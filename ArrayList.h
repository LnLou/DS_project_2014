/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H
//顺序表

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, where it means
 * the length of the array of your internal implemention
 *
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class T>
class ArrayList {
friend class Iterator;
private:
    T * data;
    int maxSize;
    int currentSize;
    long long opCnt;
    void doubleSpace(){
        maxSize *= 2;
        T * tmp = data;
        data = new T[maxSize];
        for (int i = 0 ; i < currentSize; ++i){
            data[i] = tmp[i];
        }
        delete [] tmp;
    }
public:
    class Iterator {
    private:
        int index;
        ArrayList * owner;
        long long opCnt;
        bool removed;
    public:
        Iterator(ArrayList * al){
            owner = al;
            index = -1;
            opCnt = al->opCnt;
            removed = false;
        }
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
            return index + 1 < owner->currentSize;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next() {
            removed = false;
            if (!hasNext()){throw ElementNotExist("");}
            return owner->data[++index];
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
            if (opCnt < owner->opCnt || index < 0 || index >= owner->currentSize || removed){throw ElementNotExist("");}
            ++opcnt;
            ++owner->opcnt;
            for (int i = index; i < owner->currentSize - 1; ++i){
                owner->data[i] = owner->data[i+1];
            }
            --index;
            --owner->currentSize;
            removed = true;
        }
    };

    /**
     * TODO Constructs an empty array list.
     */
    ArrayList(int size = 256) {
        currentSize = 0;
        maxSize = size;
        data = new T[size];
        opCnt = 0;
    }

    /**
     * TODO Destructor
     */
    ~ArrayList() {
        delete [] data;
    }

    /**
     * TODO Assignment operator
     */
    ArrayList& operator=(const ArrayList& x) {
        clear();
        while (x.currentSize >= maxSize){doubleSpace();}
        currentSize = x.currentSize;
        for (int i = 0 ; i < currentSize; ++i){
            data[i] = x.data[i];
        }
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    ArrayList(const ArrayList& x) {
        opCnt = 0;
        currentSize = x.currentSize;
        maxSize = x.maxSize;
        data = new T[maxSize];
        for (int i = 0; i < currentSize; ++i){  
            data[i] = x.data[i];
        }
    }

    /**
     * TODO Appends the specified element to the end of this list.
     * Always returns true.
     */
    bool add(const T& e) {
        ++opCnt;
        if (currentSize == maxSize){doubleSpace();}
        data[currentSize++] = e;
        return true;
    }

    /**
     * TODO Inserts the specified element to the specified position in this list.
     * The range of index parameter is [0, size], where index=0 means inserting to the head,
     * and index=size means appending to the end.
     * @throw IndexOutOfBound
     */
    void add(int index, const T& element) {
        ++opCnt;
        ++currentSize;
        if (index < 0 || index > currentSize){throw IndexOutOfBound();}
        if (currentSize == maxSize){doubleSpace();}
        for (int i = currentSize; i > index; --i){
            data[i] = data[i-1];
        }
        data[index] = element;
    }

    /**
     * TODO Removes all of the elements from this list.
     */
    void clear() {
        ++opCnt;
        currentSize = 0;
    }

    /**
     * TODO Returns true if this list contains the specified element.
     */
    bool contains(const T& e) const {
        for (int i = 0; i < currentSize; ++i){
            if (data[i] == e){
                return true;
            }
        }
        return false;
    }

    /**
     * TODO Returns a const reference to the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    const T& get(int index) const {
        if (index < 0 || index >= currentSize){throw IndexOutOfBound();}
        return data[index];
    }

    /**
     * TODO Returns true if this list contains no elements.
     */
    bool isEmpty() const {
        return !currentSize;
    }

    /**
     * TODO Removes the element at the specified position in this list.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void removeIndex(int index) {
        if (index < 0 || index >= currentSize){throw IndexOutOfBound();}
        for (int i = index; i < currentSize-1; ++i){
            data[i] = data[i+1];
        }
        --currentSize;
        ++opCnt;
    }

    /**
     * TODO Removes the first occurrence of the specified element from this list, if it is present.
     * Returns true if it was present in the list, otherwise false.
     */
    bool remove(const T &e) {
        ++opCnt;
        for (int i = 0; i < currentSize; ++i){
            if (data[i] == e){
                removeIndex(i);
                return true;
            }
        }
        return false;
    }

    /**
     * TODO Replaces the element at the specified position in this list with the specified element.
     * The index is zero-based, with range [0, size).
     * @throw IndexOutOfBound
     */
    void set(int index, const T &element) {
        if (index < 0 || index >= currentSize){throw IndexOutOfBound();}
        ++opCnt;
        data[index] = element;
    }

    /**
     * TODO Returns the number of elements in this list.
     */
    int size() const {
        return currentSize;
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
