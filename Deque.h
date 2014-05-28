/** @file */
#ifndef __DEQUE_H
#define __DEQUE_H

#include "ElementNotExist.h"
#include "IndexOutOfBound.h"

/**
 * An deque is a linear collection that supports element insertion and removal at both ends.
 * The name deque is short for "double ended queue" and is usually pronounced "deck".
 * Remember: all functions but "contains" and "clear" should be finished in O(1) time.
 *
 * You need to implement both iterators in proper sequential order and ones in reverse sequential order. 
 */
template <class T>
class Deque{
friend class Iterator;
private:
	T * data;
	int maxSize;
	int currentSize;
	int head;
	long long opCnt;
	int mod(int a) const{
		if (!maxSize){return 0;}
		int result = a % maxSize;
		if (result >= 0){return result;}
		result+=maxSize;
		return result;
	}
	void doubleSpace(){
		T * tmp = data;
		data = new T[maxSize * 2];
		maxSize *= 2;
		for (int i = head; i < head + currentSize; ++i){
			data[mod(i)] = tmp[mod(i) % (maxSize / 2)];
		}
		delete [] tmp;
	}
public:
    class Iterator{
    private:
    	int index;
    	long long opCnt;
    	bool isAscending;
    	bool removed;
    	Deque * owner;
    public:
    	Iterator(Deque * dq, bool asc){
    		owner = dq;
    		isAscending = asc;
    		opCnt = dq->opCnt;
    		removed = false;
    		if (asc){
    			index = -1;
    		}
    		else {
    			index = owner->currentSize;
    		}
    	}
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
        	if (isAscending){
        		if (index + 1 < 0 || index + 1 >= owner->currentSize){
        			return false;
        		}
        		return true;
        	}
        	if (index - 1 < 0 || index - 1 >= owner->currentSize){
        		return false;
        	}
        	return true;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const T &next() {
        	if (!hasNext()){throw ElementNotExist("");}
        	if (isAscending){
        		++index;
        		removed = false;
        		return owner->data[owner->mod(owner->head + index)];
        	}
        	--index;
        	removed = false;
        	return owner->data[owner->mod(owner->head + index)];
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
        	if (removed || opCnt < owner->opCnt){throw ElementNotExist("");}
        	++opCnt;
        	++owner->opCnt;
        	removed = true;
        	--owner->currentSize;
        	for (int i = index; i < owner->currentSize; ++i){
        		int tmp = owner->head + i;
        		owner->data[owner->mod(tmp)] = owner->data[owner->mod(tmp + 1)];
			}
			if (isAscending){--index;}
        }
    };

    /**
     * TODO Constructs an empty deque.
     */
    Deque(int size = 256) {
    	data = new T[size];
    	maxSize = size;
    	currentSize = 0;
    	head = 0;
    	opCnt = 0;
    }

    /**
     * TODO Destructor
     */
    ~Deque() {
    	delete [] data;
    }

    /**
     * TODO Assignment operator
     */
    Deque& operator=(const Deque& x) {
    	clear();
    	while (x.currentSize >= maxSize){doubleSpace();}
    	currentSize = x.currentSize;
    	head = 0;
    	for (int i = 0; i < currentSize; ++i){
    		data[i] = x.data[x.mod(i + x.head)];
    	}
    	return *this;
    }

    /**
     * TODO Copy-constructor
     */
    Deque(const Deque& x) {
    	data = new T[x.maxSize];
    	maxSize = x.maxSize;
    	currentSize = x.currentSize;
    	head = 0;
    	opCnt = 0;
    	for (int i = 0; i < currentSize; ++i){
    		data[i] = x.data[x.mod(x.head + i)];
    	}
    }
	
	/**
	 * TODO Inserts the specified element at the front of this deque. 
	 */
	void addFirst(const T& e) {
		if (currentSize == maxSize){doubleSpace();}
		++currentSize;
		head -= 1;
		data[mod(head)] = e;
		++opCnt;
	}

	/**
	 * TODO Inserts the specified element at the end of this deque.
	 */
	void addLast(const T& e) {
		if (currentSize == maxSize){doubleSpace();}
		data[mod(head + currentSize)] = e;
		++currentSize;
		++opCnt;
	}

	/**
	 * TODO Returns true if this deque contains the specified element.
	 */
	bool contains(const T& e) const {
		for (int i = head; i < head + currentSize; ++i){
			if (data[mod(i)] == e){return true;}
		}
		return false;
	}

	/**
	 * TODO Removes all of the elements from this deque.
	 */
	 void clear() {
	 	currentSize = 0;
	 	head = 0;
	 	++opCnt;
	 }

	 /**
	  * TODO Returns true if this deque contains no elements.
	  */
	bool isEmpty() const {
		return !currentSize;
	}

	/**
	 * TODO Retrieves, but does not remove, the first element of this deque.
	 * @throw ElementNotExist
	 */
	const T& getFirst() {
		if (!currentSize){throw ElementNotExist("");}
		return data[mod(head)];
	}

	 /**
	  * TODO Retrieves, but does not remove, the last element of this deque.
	  * @throw ElementNotExist
	  */
	const T& getLast() {
	 	if (!currentSize){throw ElementNotExist("");}
	 	return data[mod(head + currentSize - 1)];
	}

	 /**
	  * TODO Removes the first element of this deque.
	  * @throw ElementNotExist
	  */
	void removeFirst() {
		if (!currentSize){throw ElementNotExist("");}
		--currentSize;
		++head;
		++opCnt;
		head = mod(head);
	}

	/**
	 * TODO Removes the last element of this deque.
	 * @throw ElementNotExist
	 */
	void removeLast() {
		if (!currentSize){throw ElementNotExist("");}
		--currentSize;
		++opCnt;
	}

	/**
	 * TODO Returns a const reference to the element at the specified position in this deque.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	const T& get(int index) const {
		if (index < 0 || index >= currentSize){throw IndexOutOfBound();}
		return data[mod(head + index)];
	}
	
	/**
	 * TODO Replaces the element at the specified position in this deque with the specified element.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	void set(int index, const T& e) {
		++opCnt;
		if (index < 0 || index >= currentSize){throw IndexOutOfBound();}
		data[mod(head + index)] = e;
	}

	/**
	 * TODO Returns the number of elements in this deque.
	 */
	 int size() const {
	 	return currentSize;
	 }

	 /**
	  * TODO Returns an iterator over the elements in this deque in proper sequence.
	  */
	Iterator iterator() {
	 	Iterator result(this, true);
	 	return result;
	}

	/**
	 * TODO Returns an iterator over the elements in this deque in reverse sequential order.
	 */
	Iterator descendingIterator() {
		Iterator result(this, false);
		return result;
	}
};

#endif
