#include "json.h"
#include <stdio.h> // snprintf

unsigned int
json_encode_value(unsigned int type, union json_value value, char dst[], size_t max)
{
    switch (type) {
        case JSON_STRING: {
            return (unsigned)snprintf(dst, max, "\"%s\"", value.string);
        }
        case JSON_NUMBER: {
            return (unsigned)snprintf(dst, max, "%f", value.number);
        }
        case JSON_NULL: {
            return (unsigned)snprintf(dst, max, "%s", "null");
        }
        case JSON_FALSE: {
            return (unsigned)snprintf(dst, max, "%s", "false");
        }
        case JSON_TRUE: {
            return (unsigned)snprintf(dst, max, "%s", "true");
        }
        case JSON_OPEN_OBJECT: {
            return (unsigned)snprintf(dst, max, "%s", "{");
        }
        case JSON_CLOSE_OBJECT: {
            return (unsigned)snprintf(dst, max, "%s", "}");
        }
        case JSON_OPEN_ARRAY: {
            return (unsigned)snprintf(dst, max, "%s", "[");
        }
        case JSON_CLOSE_ARRAY: {
            return (unsigned)snprintf(dst, max, "%s", "]");
        }
        case JSON_CONTINUE:             return 0;
        case JSON_END_IN_SPACE:         return 0;
        case JSON_END_ON_NEW_ARRAY:     return 0;
        case JSON_END_ON_NEW_OBJECT:    return 0;
        case JSON_END_ON_STRING:        return 0;
        case JSON_END_IN_STRING_TABLE:  return 0;
        default: return 0;
    }
}
