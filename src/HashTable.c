#include "../include/Core/HashTable.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SiZE 10
unsigned int hash(const char* key) {
    unsigned int len = strnlen(key, 50);
    unsigned int hash_value = 0;
    for (int i = 0; i < len; i++) {
        hash_value += key[i] * len;
    }
    hash_value %= TABLE_SiZE;
    return hash_value;
}

ht_t* ht_create() {
    ht_t* hash_table = (ht_t*)malloc(sizeof(*hash_table));
    hash_table->data = (hash_entry**)malloc(sizeof(hash_entry*) * TABLE_SiZE);

    for (int i = 0; i < TABLE_SiZE; i++) {
        hash_table->data[i] = NULL;
    }

    return hash_table;
}

void ht_free(ht_t *hash_table) {
    for (int i = 0; i < TABLE_SiZE; i++) {
        hash_entry* head = hash_table->data[i];
        hash_entry* tmp;

        while (head != NULL) {
            tmp = head;
            head = head->next;
            free(tmp->value);
            tmp->value = NULL;
            free(tmp);
            tmp = NULL;
        }
    }
    printf("Freed hashtable\n");
}

hash_entry* ht_pair(const char* key, void* value) {
    hash_entry* e = (hash_entry*)malloc(sizeof(hash_entry));
    strcpy(e->key, key);
    e->value = value;
    e->next = NULL;
    return e;
}

void ht_set(ht_t *hash_table, const char *key, void *value) {
    unsigned int slot = hash(key);

    hash_entry *entry = hash_table->data[slot];

    // if the head is not set yet
    if (entry == NULL) {
        hash_table->data[slot] = ht_pair(key, value);
        return;
    }

    hash_entry *prev;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            free(entry->value);
            entry->value = malloc(sizeof(value));
            entry->value = value;
            return;
        }
        prev = entry;
        entry = prev->next;
    }
    prev->next = ht_pair(key, value);
}

void* ht_get(ht_t *hash_table, const char *key) {
    unsigned int slot = hash(key);
    hash_entry* entry = hash_table->data[slot];
    if (entry == NULL)
        return NULL;

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0)
            return entry->value;

        entry = entry->next;
    }
    return NULL;
}

void ht_del(ht_t *hash_table, const char *key) {

    unsigned int bucket = hash(key);

    // try to find a valid bucket
    hash_entry *entry = hash_table->data[bucket];

    // no bucket means no entry
    if (entry == NULL) {
        return;
    }

    hash_entry *prev;
    int idx = 0;

    // walk through each entry until either the end is reached or a matching key is found
    while (entry != NULL) {
        // check key
        if (strcmp(entry->key, key) == 0) {
            // first item and no next entry
            if (entry->next == NULL && idx == 0) {
                hash_table->data[bucket] = NULL;
            }

            // first item with a next entry
            if (entry->next != NULL && idx == 0) {
                hash_table->data[bucket] = entry->next;
            }

            // last item
            if (entry->next == NULL && idx != 0) {
                prev->next = NULL;
            }

            // middle item
            if (entry->next != NULL && idx != 0) {
                prev->next = entry->next;
            }

            // free the deleted entry
            free(entry->key);
            free(entry->value);
            free(entry);

            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;

        ++idx;
    }
}

void ht_dump(ht_t* hash_table) {
    for (int i = 0; i < TABLE_SiZE; i++) {
        hash_entry* entry = hash_table->data[i];
        if (entry == NULL)
            continue;

        printf("slot[%4d]: ", i);

        for (;;) {
            printf("%s=%p", entry->key, entry->value);
            if (entry->next == NULL)
                break;
            entry = entry->next;
        }
        printf("\n");
    }
}
