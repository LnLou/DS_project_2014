/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "ElementNotExist.h"
#include <cstdlib>

/**
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K, class V>
class TreeMap {
public:
    class Entry {
    friend class TreeMap;
    friend class TreeMap::node;
    private:
        K key;
        V value;
    public:
        Entry(K k, V v) {
            key = k;
            value = v;
        }

        const K & getKey() const {
            return key;
        }

        const V & getValue() const {
            return value;
        }
    };
private:
    struct node{
        Entry * data;
        int key;
        node * parent, * child[2];
        node (Entry * x = 0){
            data = x;
            key = rand();
            child[0] = child[1] = parent = 0;
        }
        ~node (){
            if (data){
                delete data;
            }
        }
        node (const node * const x){
            Entry * et = new Entry(x->data->key, x->data->value);
            data = et;
            key = x->key;
            child[0] = child[1] = parent = 0;
        }
    };
    node * root;
    int currentSize;
    long long opCnt;
    inline bool getIndex(const node * x) const{
        return (x->parent->child[1] == x);
    }
    void rotate(node * x){
        node * p = x->parent;
        int index = getIndex(x);
        if (p->parent){
            p->parent->child[getIndex(p)] = x;
        }
        else {
            root = x;
        }
        x->parent = p->parent;
        p->child[index] = x->child[1-index];
        if (p->child[index]){
            p->child[index]->parent = p;
        }
        x->child[1-index] = p;
        p->parent = x;
    }
    void cpyNode(node * x, node * target){
        if (!x){return;}
        for (int i = 0; i < 2; ++i){
            if (x->child[i]){
                target->child[i] = new node(x->child[i]);
                target->child[i]->parent = target;
                cpyNode(x->child[i], target->child[i]);
            }
            else {
                target->child[i] = 0;
            }
        }
    }
    void delNode(node * x){
        if (!x){return;}
        for (int i = 0; i < 2; ++i){
            delNode(x->child[i]);
        }
        delete x;
    }
    node * findKey(const K & key, node * nd) const{
        if (!nd){return nd;}
        if (nd->data->key == key){return nd;}
        if (key < nd->data->key){return findKey(key, nd->child[0]);}
        return findKey(key, nd->child[1]);
    }
    void insert(const K & key, const V & value, node * nd){
        if (key < nd->data->key){
            if (nd->child[0]){
                insert(key, value, nd->child[0]);
            }
            else {
                Entry * et = new Entry(key, value);
                nd->child[0] = new node(et);
                nd->child[0]->parent = nd;
                node * p = nd->child[0], * q;
                while (p != root){
                    q = p->parent;
                    if (p->key < q->key){
                        rotate(p);
                    }
                    else {
                        break;
                    }
                    //p = q;
                }
            }
        }
        else {
            if (nd->child[1]){
                insert(key, value, nd->child[1]);
            }
            else {
                Entry * et = new Entry(key, value);
                nd->child[1] = new node(et);
                nd->child[1]->parent = nd;
                node * p = nd->child[1], * q;
                while (p != root){
                    q = p->parent;
                    if (p->key < q->key){
                        rotate(p);
                    }
                    else {
                        break;
                    }
                    p = q;
                }
            }
        }
    }
    bool findValue(const V &value, const node * nd) const{
        if (!nd){return false;}
        if (nd->data->value == value){return true;}
        bool result = findValue(value, nd->child[0]) || findValue(value, nd->child[1]);
        return result;
    }
public:
    class Iterator {
    private:
        const TreeMap::node * nd;
        const TreeMap * owner;
        long long opCnt;
        bool isFirst;
    public:
        Iterator(const TreeMap * tm):owner(tm){
            opCnt = tm->opCnt;
            nd = tm->root;
            if (!nd){return;}
            while (nd->child[0]){
                nd = nd->child[0];
            }
            isFirst = true;
        }
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext() {
            if (!nd){return false;}
            if (nd->child[1]){return true;}
            const TreeMap::node * p = nd;
            while (p->parent){
                if (!owner->getIndex(p)){
                    return true;
                }
                p = p->parent;
            }
            return false;
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const Entry &next() {
            if (!hasNext()){throw ElementNotExist();}
            if (isFirst){
                isFirst = false;
                return *nd->data;
            }
            if (nd->child[1]){
                nd = nd->child[1];
                while (nd->child[0]){
                    nd = nd->child[0];
                }
            }
            else {
                while (nd->parent){
                    if (!owner->getIndex(nd)){
                        nd = nd->parent;
                        break;
                    }
                    else {
                        nd = nd->parent;
                    }
                }
            }
            return * nd->data;
        }
    };
    friend class TreeMap::Iterator;

    /**
     * TODO Constructs an empty tree map.
     */
    TreeMap() {
        root = 0;
        currentSize = 0;
        opCnt = 0;
    }

    /**
     * TODO Destructor
     */
    ~TreeMap() {
        clear();
    }

    /**
     * TODO Assignment operator
     */
    TreeMap &operator=(const TreeMap &x) {
        clear();
        root = new node(x.root);
        cpyNode(x.root, root);
        currentSize = x.currentSize;
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    TreeMap(const TreeMap &x) {
        opCnt = 0;
        currentSize = x.currentSize;
        if (x.isEmpty()){
            root = 0;
            return;
        }
        root = new node(x.root);
        cpyNode(x.root, root);
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
        ++opCnt;
        currentSize = 0;
        delNode(root);
        root = 0;
    }

    /**
     * TODO Returns true if this map contains a mapping for the specified key.
     */
    bool containsKey(const K &key) const {
        return findKey(key, root);
    }

    /**
     * TODO Returns true if this map maps one or more keys to the specified value.
     */
    bool containsValue(const V &value) const {
        return findValue(value, root);
    }

    /**
     * TODO Returns a const reference to the value to which the specified key is mapped.
     * If the key is not present in this map, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &get(const K &key) const {
        node * p = findKey(key, root);
        if (!p){throw ElementNotExist();}
        return p->data->value;
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
        node * p = findKey(key, root);
        if (p){
            p->data->value = value;
        }
        else {
            if (!currentSize){
                Entry * et = new Entry(key, value);
                root = new node(et);
            }
            else {
                insert(key, value, root);
            }
            ++currentSize;
        }
    }

    /**
     * TODO Removes the mapping for the specified key from this map if present.
     * If there is no mapping for the specified key, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void remove(const K &key) {
        node * nd = findKey(key, root);
        if (!nd){throw ElementNotExist();}
        ++opCnt;
        --currentSize;
        while (nd->child[0] || nd->child[1]){
            if (!nd->child[0]){
                rotate(nd->child[1]);
            }
            else if (!nd->child[1]){
                rotate(nd->child[0]);
            }
            else if (nd->child[0]->key < nd->child[1]->key){
                rotate(nd->child[0]);
            }
            else {
                rotate(nd->child[1]);
            }
        }
        if (nd == root){
            root = 0;
        }
        else {
            nd->parent->child[getIndex(nd)] = 0;
        }
        delete nd;
    }

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const {
        return currentSize;
    }
};

#endif
