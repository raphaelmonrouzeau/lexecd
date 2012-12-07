#include "json.h"
#include <stdlib.h> // malloc
#include <string.h> // memcpy

#define JSON_ITEMS_BLOCK_SIZE 1024

extern inline void
json_items_init(struct json_items* json_items, unsigned int length)
{
    if (length < 1)
        return;
    json_items->items[0].value.next = 0;
    json_items->length = length;
}

struct json_items*
json_items_create(unsigned int n)
{
    if (n < 1)
        return NULL;
    
    struct json_items* json_items = malloc(sizeof(struct json_items)+n*sizeof(struct json_item));
    json_items_init(json_items, n);
    return json_items;
}

void
json_items_add_item(struct json_items**restrict pitems, unsigned int type, union json_value value)
{
    struct json_items*restrict json_items = *pitems;

    if (json_items->items[0].value.next == json_items->length) {
        struct json_items*restrict new = realloc(json_items, json_items->length+JSON_ITEMS_BLOCK_SIZE);
        if (new == NULL) {
            return;
        }
        json_items->length += JSON_ITEMS_BLOCK_SIZE;
        *pitems = json_items = new;
    }

    unsigned int*restrict pn = &json_items->items[0].value.next;

    if (type == JSON_OPEN_OBJECT || type == JSON_OPEN_ARRAY) {
        json_items->level++;
        json_items->parent = *pn;
    } else if (type == JSON_CLOSE_OBJECT || type == JSON_CLOSE_ARRAY) {
        json_items->level--;
    }

    int l = 0;

    for (unsigned int i=0; i<*pn;) {
        struct json_item*restrict item = &json_items->items[i];

        if (item->type == JSON_OPEN_OBJECT || item->type == JSON_OPEN_ARRAY) {
            l++;
            if (l<(signed)json_items->level) {
                item->value.next++;
                i++;
            } else {
                i += item->value.next;
            }
        } else if (item->type == JSON_CLOSE_OBJECT || item->type == JSON_OPEN_OBJECT) {
            l--;
        }
    }

    struct json_item*restrict item = &json_items->items[*pn];

    item->type  = type;
    memcpy(&item->value, &value, sizeof(union json_value));
}
