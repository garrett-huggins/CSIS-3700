#ifndef _BST_DICTIONARY_H
#define _BST_DICTIONARY_H

#include <cstdint> // for uint32_t
#include <stdexcept> // for domain_error

#define GET_COUNT(n) (((n) == NULL_INDEX) ? 0 : counts[n])
#define GET_HEIGHT(n) (((n) == NULL_INDEX) ? 0 : heights[n])

static const uint32_t
NULL_INDEX = 0xffffffff,
DEFAULT_INITIAL_CAPACITY = 16;

template <typename KeyType,typename ValueType>
class BSTDictionary {
public:
    explicit BSTDictionary(uint32_t _cap = DEFAULT_INITIAL_CAPACITY) {
        if (nTrees == 0) {

            left = new uint32_t[_cap];
            right = new uint32_t[_cap];
            counts = new uint32_t[_cap];
            heights = new uint32_t[_cap];
            keys = new KeyType[_cap];
            values = new ValueType[_cap];

            // _cap is the initial size of all arrays
            capacity = _cap;

            for (int i=0; i < capacity - 1; i++) {
                left[i] = i + 1;
            }

            left[capacity-1] = NULL_INDEX;

            freeListHead = 0;

            for (int i=0; i < capacity - 1; i++) {
                left[i] = i + 1;
            }
        
        }

        nTrees = nTrees + 1;

        root = NULL_INDEX;
    }

    ~BSTDictionary() {
        nTrees = nTrees - 1;

        if (nTrees == 0) {
            delete[] values;
            delete[] keys;
            delete[] heights;
            delete[] counts;
            delete[] right;
            delete[] left;
        } else
            prvClear(root);
    }

    void clear() { prvClear(root); root = NULL_INDEX; }


    uint32_t size() { return GET_COUNT(root); }

    uint32_t height() { return GET_HEIGHT(root); }

    bool isEmpty() { return root == NULL_INDEX; }

    ValueType &search(const KeyType &k) {
        uint32_t n = root;

        while (n != NULL_INDEX) {
            if (k == keys[n]) {
                return values[n];
            } else 
            if (k < keys[n]) {
                n = left[n];
            } else {
                n = right[n];
            }
        }
        throw std::domain_error("Search: key not found");
    }

    ValueType &operator[](const KeyType &k) {
        uint32_t tmp = prvAllocate();
        uint32_t n = tmp;

        root = prvInsert(root, n, k);

        if (n != tmp) {
            prvFree(tmp);   // deallocate unused node
        }
        return values[n];
    }

    void remove(const KeyType &k) {

    }

// -- private --
private:
    uint32_t
        root; // tree root

    static uint32_t // this is the shared data
        *counts, // counts for each node
        *heights, // heights for each node
        *left, // left node indexes
        *right, // right node indexes
        nTrees, // number of BSTs with this key and value type
        capacity, // size of the arrays
        freeListHead; // the head of the unused node list (the free list)

    static KeyType
        *keys; // pool of keys
    static ValueType
        *values; // pool of values

    // uint32_t getHeight(uint32_t node) {
    //     if (node == NULL_INDEX) {
    //         return 0;
    //     } else {
    //         uint32_t left_side = getHeight(node[left]);
    //         uint32_t right_side = getHeight(node[right]);

    //         if (left_side > right_side) {
    //             return left_side + 1;
    //         } else {
    //             return right_side + 1;
    //         }
    //     }
    // }

    // uint32_t getCount(uint32_t tree) {
    //     int count = 0;
    //     if (tree == NULL_INDEX) {
    //         return 0;
    //     } else {
    //         count += getCount(tree[left]);
    //         count += getCount(tree[right]);
    //         return count;
    //     }
    // }


    uint32_t prvAllocate() {
        // start = capacity
        // end = 2 * capacity - 1
        if (freeListHead == NULL_INDEX) {
            // allocate tmp arrays with 2 x capacity elements
            auto
                tmpLeft = new uint32_t[2*capacity];
            auto
                tmpRight = new uint32_t[2*capacity];
            auto
                tmpCounts = new uint32_t[2*capacity];
            auto
                tmpHeights = new uint32_t[2*capacity];
            auto
                tmpColors = new uint8_t[2*capacity];
            auto
                tmpKeys = new KeyType[2*capacity];
            auto
                tmpValues = new ValueType[2*capacity];

            // copy data from old arrays to tmp arrays
            for (int32_t i = 0; i < capacity; i++) {
                tmpLeft[i] = left[i];
                tmpRight[i] = right[i];
                tmpCounts[i] = counts[i];
                tmpHeights[i] = heights[i];
                tmpKeys[i] = keys[i];
                tmpValues[i] = values[i];
            }

            // delete old arrays

            delete[] values;
            delete[] keys;
            delete[] heights;
            delete[] counts;
            delete[] right;
            delete[] left;

            // point shared pointers to tmp arrays
            
            left = tmpLeft;
            right = tmpRight;
            counts = tmpCounts;
            heights = tmpHeights;
            keys = tmpKeys;
            values = tmpValues;

            // regen free list

            for (int32_t i = capacity; i < 2*capacity-1; i++) {
                left[i] = i + 1;
            }

            left[2*capacity-1] = NULL_INDEX;

            freeListHead = capacity;

            capacity = 2 * capacity;
        }

        uint32_t tmp = freeListHead;

        left[tmp] = NULL_INDEX;
        right[tmp] = NULL_INDEX;
        counts[tmp] = 1;
        heights[tmp] = 1;

        return tmp;
    }

    // deallocate node
    void prvFree(uint32_t n) {
        left[n] = freeListHead;
        freeListHead = n;
    }

    void prvClear(uint32_t r) {
        if (r != NULL_INDEX) {
            prvClear(left[r]);
            prvClear(right[r]);

            prvFree(r);
        }
    }

    void prvAdjust(uint32_t r) {
        uint32_t
            leftCount = GET_COUNT(left[r]),
            rightCount = GET_COUNT(right[r]),
            leftHeight = GET_HEIGHT(left[r]),
            rightHeight = GET_HEIGHT(right[r]);

        counts[r] = 1 + leftCount + rightCount;
        heights[r] = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
    }

    // recursive inser / update / access
    uint32_t prvInsert(uint32_t r,uint32_t &n,const KeyType &k) {
        if (r == NULL_INDEX) {
            keys[n] = k;
            return n;
        }

        if (k < keys[r]) {
            n = r;
        } else
        if (k < keys[r]) {
            left[r] = prvInsert(left[r], n, k);
        } else {
            right[r] = prvInsert(right[r], n, k);
        }

        prvAdjust(r);

        return r;
    }

    uint32_t prvRemove(uint32_t r,uint32_t &ntbd,const KeyType &k) {
        if (r == NULL_INDEX) {
            std::__throw_domain_error("Remove: key not found");
        }

        if (k < keys[r]) {
            left[r] = prvRemove(left[r], ntbd, k);
        } else
        if (k > keys[r]) {
            right[r] = prvRemove(right[r], ntbd, k);
        } else {
            ntbd = r;

            if (left[r] == NULL_INDEX) {
                if (right[r] == NULL_INDEX) {
                    r = NULL_INDEX;
                } else {
                    r = right[r];
                }
            } else {
                if (right[r] == NULL_INDEX) {
                    r = left[r];
                } else {
                    // reduce two-child case to one-child case
                    if (GET_HEIGHT(right[r]) > GET_HEIGHT(left[r])) {
                        uint32_t tmp = right[r];

                        while (left[tmp] != NULL_INDEX) {
                            tmp = left[tmp];
                        }

                        keys[r] = keys[tmp];
                        values[r] = values[tmp];
                        // swap keys[r] and keys[tmp]
                        // swap values[r] and values[tmp]

                        right[r] = prvRemove(right[r], ntbd, k);
                    } else {
                        uint32_t tmp = left[r];

                        while (right[tmp] != NULL_INDEX) {
                            tmp = right[tmp];
                        }

                        keys[r] = keys[tmp];
                        values[r] = values[tmp];
                        // swap keys[r] and keys[tmp]
                        // swap values[r] and values[tmp]

                        left[r] = prvRemove(left[r], ntbd, k);
                    }
                }
            }
        }
        if (r != NULL_INDEX) {
            prvAdjust(r);
        }
        return r;
    }

};

template <typename KeyType,typename ValueType>
uint32_t BSTDictionary<KeyType,ValueType>::capacity = 0;

template <typename KeyType,typename ValueType>
uint32_t BSTDictionary<KeyType,ValueType>::freeListHead = 0;

template <typename KeyType,typename ValueType>
uint32_t BSTDictionary<KeyType,ValueType>::nTrees = 0;

template <typename KeyType,typename ValueType>
uint32_t *BSTDictionary<KeyType,ValueType>::left = nullptr;

template <typename KeyType,typename ValueType>
uint32_t *BSTDictionary<KeyType,ValueType>::right = nullptr;

template <typename KeyType,typename ValueType>
uint32_t *BSTDictionary<KeyType,ValueType>::counts = nullptr;

template <typename KeyType,typename ValueType>
uint32_t *BSTDictionary<KeyType,ValueType>::heights = nullptr;

template <typename KeyType,typename ValueType>
KeyType *BSTDictionary<KeyType,ValueType>::keys = nullptr;

template <typename KeyType,typename ValueType>
ValueType *BSTDictionary<KeyType,ValueType>::values = nullptr;

#endif
