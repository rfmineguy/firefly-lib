#ifndef FL_COREHASHTABLE_H
#define FL_COREHASHTABLE_H
#include <stdbool.h>

enum Type {INT, FLOAT, DOUBLE, C_STR};

typedef struct hash_entry {
    char key[25];
    void* value;
    struct hash_entry* next;
} hash_entry;

typedef struct {
    hash_entry** data;
} ht_t;

unsigned int hash(const char* key);
ht_t* ht_create();
void ht_free(ht_t*);

hash_entry* ht_pair(const char*, void*);
void ht_set(ht_t*, const char*, void*);
void* ht_get(ht_t*, const char*);
void ht_del(ht_t*, const char*);

void ht_dump(ht_t*);

#endif
