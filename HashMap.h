/** @file */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "ElementNotExist.h"

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your internal implemention, not the current number of the
 * elements.
 *
 * Template argument H are used to specify the hash function.
 * H should be a class with a static function named ``hashCode'',
 * which takes a parameter of type K and returns a value of type int.
 * For example, the following class
 * @code
 *      class Hashint {
 *      public:
 *          static int hashCode(int obj) {
 *              return obj;
 *          }
 *      };
 * @endcode
 * specifies an hash function for integers. Then we can define:
 * @code
 *      HashMap<int, int, Hashint> hash;
 * @endcode
 *
 * Hash function passed to this class should observe the following rule: if two keys
 * are equal (which means key1 == key2), then the hash code of them should be the
 * same. However, it is not generally required that the hash function should work in
 * the other direction: if the hash code of two keys are equal, the two keys could be
 * different.
 *
 * Note that the correctness of HashMap should not rely on the choice of hash function.
 * This is to say that, even the given hash function always returns the same hash code
 * for all keys (thus causing a serious collision), methods of HashMap should still
 * function correctly, though the performance will be poor in this case.
 *
 * The order of iteration could be arbitary in HashMap. But it should be guaranteed
 * that each (key, value) pair be iterated exactly once.
 */
template <class K, class V, class H>
class HashMap {
public:
    class Entry {
    friend class HashMap;
    friend class HashMap::node;
    private:
        K key;
        V value;
    public:
        Entry(K k, V v) {
            key = k;
            value = v;
        }

        K getKey() const {
            return key;
        }

        V getValue() const {
            return value;
        }
    };
private:
    struct node {
        Entry * data;
        node * next, * prev;
        node(HashMap::Entry * et, node * n = 0, node * p = 0){
            data = et;
            next = n;
            prev = p;
        }
        node(){
            data = 0;
            next = prev = 0;
        }
        ~node(){
            if (prev){
                prev->next = next;
            }
            if (next){
                next->prev = prev;
            }
            if (data) {delete data;}
        }
        void insert(node * nd){
            nd->prev = this;
            nd->next = next;
            if (next){next->prev = nd;}
            next = nd;
        }
    };
    H h;
    node ** data;
    int currentSize, maxSize;
    long long opCnt;
    inline int hash(const K & x) const{
        int result = h.hashCode(x) % maxSize;
        if (result >= 0){
            return result;
        }
        result += maxSize;
        return result;
    }
    void doubleSpace(){
        node ** tmp = data;
        ++opCnt;
        maxSize *= 2;
        data = new node*[maxSize];
        for (int i = 0; i < maxSize; ++i){
            data[i] = new node();
        }
        for (int i = 0; i < maxSize/2; ++i){
            node * p = tmp[i]->next, * q;
            while (p){
                q = p->next;
                data[hash(p->data->key)]->insert(p);
                p = q;
            }
            delete tmp[i];
        }
        delete[] tmp;
    }
public:
    
    class Iterator {
    private:
        HashMap::node * nd;
        int index;
        const HashMap * owner;
        long long opCnt;
    public:
        Iterator(const HashMap * hm):owner(hm){
            nd = hm->data[0];
            index = 0;
            //owner = hm;
            opCnt = hm->opCnt;
        }
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
            if (nd->next){return true;}
            for (int i = index+1; i < owner->maxSize; ++i){
                if (owner->data[i]->next){return true;}
            }
            return false;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const Entry &next() {
            if (!hasNext()){throw ElementNotExist();}
            if (nd->next){
                nd = nd->next;
            }
            else{
                for (int i = index+1; i < owner->maxSize; ++i){
                    if (owner->data[i]->next){
                        index = i;
                        nd = owner->data[i]->next;
                        break;
                    }
                }
            }
            return *(nd->data);
        }
    };

    /**
     * TODO Constructs an empty hash map.
     */
    HashMap(int x = 16) {
        maxSize = x;
        opCnt = 0;
        currentSize = 0;
        data = new node*[maxSize];
        for (int i = 0; i < maxSize; ++i){
            data[i] = new node();
        }
    }

    /**
     * TODO Destructor
     */
    ~HashMap() {
        for (int i = 0; i < maxSize; ++i){
            node * p = data[i], *q;
            while (p){
                q = p->next;
                delete p;
                p = q;
            }
        }
    }

    /**
     * TODO Assignment operator
     */
    HashMap &operator=(const HashMap &x) {
        clear();
        while (maxSize < x.maxSize){doubleSpace();}
        currentSize = x.currentSize;
        for (int i = 0; i < maxSize; ++i){
            node * p = x.data[i]->next;
            while (p){
                Entry * et = new Entry(p->data->key, p->data->value);
                node * nd = new node(et, 0, 0);
                data[i]->insert(nd);
                p = p->next;
            }
        }
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    HashMap(const HashMap &x) {
        maxSize = x.maxSize;
        currentSize = x.currentSize;
        opCnt = 0;
        data = new node*[maxSize];
        for (int i = 0; i < maxSize; ++i){
            data[i] = new node();
        }
        for (int i = 0; i < maxSize; ++i){
            node * p = x.data[i];
            while (p->next){
                p = p->next;
                Entry * et = new Entry(p->data->key, p->data->value);
                node * nd = new node(et, 0, 0);
                data[i]->insert(nd);
            }
        }
    }

    /**
     * TODO Returns an iterator over the elements in this map.
     */
    Iterator iterator() const {
        Iterator result(this);
        return result;
    }

    /**
     * TODO Removes all of the mappings from this map.
     */
    void clear() {
        for (int i = 0; i < maxSize; ++i){
            node *p=data[i]->next,*q;
            while (p){
                q=p->next;
                delete p;
                p=q;
            }
            data[i]->next=0;
        }
        currentSize = 0;
        ++opCnt;
    }

    /**
     * TODO Returns true if this map contains a mapping for the specified key.
     */
    bool containsKey(const K &key) const {
        int index = hash(key);
        node * p = data[index];
        while (p->next){
            p = p->next;
            if (p->data->key == key){
                return true;
            }
        }
        return false;
    }

    /**
     * TODO Returns true if this map maps one or more keys to the specified value.
     */
    bool containsValue(const V &value) const {
        for (int i = 0; i < maxSize; ++i){
            node * p = data[i];
            while (p->next){
                p = p->next;
                if (p->data->value == value){
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * TODO Returns a const reference to the value to which the specified key is mapped.
     * If the key is not present in this map, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &get(const K &key) const {
        int index = hash(key);
        node * p = data[index]->next;
        while (p){
            if (p->data->key == key){
                return p->data->value;
            }
            p = p->next;
        }
        throw ElementNotExist();
    }

    /**
     * TODO Returns true if this map contains no key-value mappings.
     */
    bool isEmpty() const {
        return !currentSize;
    }

    /**
     * TODO Associates the specified value with the specified key in this map.
     */
    void put(const K &key, const V &value) {
        ++opCnt;
        int index = hash(key);
        node * p = data[index];
        while (p->next){
            p = p->next;
            if (p->data->key == key){
                p->data->value = value;
                return;
            }
        }
        if (currentSize * 2 >= maxSize){
            doubleSpace();
            index = hash(key);
        }
        ++currentSize;
        Entry * et = new Entry(key, value);
        node * pt = new node(et);
        data[index]->insert(pt);
    }

    /**
     * TODO Removes the mapping for the specified key from this map if present.
     * If there is no mapping for the specified key, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void remove(const K &key) {
        ++opCnt;
        int index = hash(key);
        node * p = data[index]->next, * q;
        while (p){
            q = p->next;
            if (p->data->key == key){
                delete p;
                --currentSize;
                return;
            }
            p = q;
        }
        throw ElementNotExist();
    }

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const {
        return currentSize;
    }
};

#endif
