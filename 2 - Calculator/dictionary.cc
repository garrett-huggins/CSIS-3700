#include "dictionary.h"

// Hash Dictionary

static uint32_t hash(const std::string &s) {
    uint32_t
        sum = 0;

    for (uint32_t i=0;i<s.length();i++) {
        sum = sum * i + s[i];
    }

    return sum;
}

void Dictionary::clear() {

    for (uint32_t i=0;i<TABLE_SIZE;i++) {
         status[i] = UNUSED;
    }

    nItems = 0;
}

void Dictionary::add(const std::string &key,const Fraction value) {
    // hash key to get a position
    uint32_t
        pos = hash(key) % TABLE_SIZE;

    // sequential search for key
    while (status[pos] != UNUSED) {

        // if key found, update value and return
        if (status[pos] == IN_USE && keys[pos] == key) {
            values[pos] = value;
            return;
        }

        pos = (pos + 1) % TABLE_SIZE;
    }

    // not found... is table too full? If so, exception
    if (nItems == MAX_ITEMS) {
        throw std::overflow_error("Dictionary is full");
    }

    // not too full... search again stopping at first open spot
    if (nItems < MAX_ITEMS) {
        int32_t table_size = TABLE_SIZE;
        pos = hash(key) % TABLE_SIZE; //reset position

        while (status[pos] != UNUSED) {

            if (status[pos] == DELETED) {
                table_size = pos;
            }

            pos = (pos + 1) % TABLE_SIZE;
        }
        
        if (table_size == TABLE_SIZE) {
            table_size = pos;
        }

        keys[table_size] = key;
        values[table_size] = value;
        status[table_size] = IN_USE;

        nItems = nItems + 1;
    }

}

Fraction Dictionary::search(const std::string &key) {
    // hash key to get a position
    uint32_t
        pos = hash(key) % TABLE_SIZE;

    // sequential search for key; stop at unused
    while (status[pos] != UNUSED) {

        // if key found, update value and return
        if (status[pos] == IN_USE && keys[pos] == key) {
            return values[pos]; // if key found, return value
        }

        pos = (pos + 1) % TABLE_SIZE;
    }

    // if we get here, key isn't here, throw exception
    throw std::domain_error("Search: Key not found");
}

void Dictionary::remove(const std::string &key) {
    // hash key to get a position
    uint32_t
        pos = hash(key) % TABLE_SIZE;

    // sequential search for key; stop at unused
    while (status[pos] != UNUSED) {

        // if key found, delete value and return
        if (status[pos] == IN_USE && keys[pos] == key) {
            status[pos] = DELETED;
            return;
        }
        pos = (pos + 1) % TABLE_SIZE;
    }
    
    // if we get here, key isn't here, throw exception
    throw std::domain_error("Deletion: Key not found");

}
