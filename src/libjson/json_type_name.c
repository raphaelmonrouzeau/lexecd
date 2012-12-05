#include "json.h"

const char*
json_type_name(unsigned int type)
{
    switch (type) {
        case JSON_STRING:               return "JSON_STRING";
        case JSON_NUMBER:               return "JSON_NUMBER";
        case JSON_NULL:                 return "JSON_NULL";
        case JSON_FALSE:                return "JSON_FALSE";
        case JSON_TRUE:                 return "JSON_TRUE";
        case JSON_OPEN_OBJECT:          return "JSON_OPEN_OBJECT";
        case JSON_CLOSE_OBJECT:         return "JSON_CLOSE_OBJECT";
        case JSON_OPEN_ARRAY:           return "JSON_OPEN_ARRAY";
        case JSON_CLOSE_ARRAY:          return "JSON_CLOSE_ARRAY";
        case JSON_CONTINUE:             return "JSON_CONTINUE";
        case JSON_END_IN_SPACE:         return "JSON_END_IN_SPACE";
        case JSON_END_ON_NEW_ARRAY:     return "JSON_END_ON_NEW_ARRAY";
        case JSON_END_ON_NEW_OBJECT:    return "JSON_END_ON_NEW_OBJECT";
        case JSON_END_ON_STRING:        return "JSON_END_ON_STRING";
        case JSON_END_IN_STRING_TABLE:  return "JSON_END_IN_STRING_TABLE";
        default: return "JSON_UNKNOWN";
    }
}

