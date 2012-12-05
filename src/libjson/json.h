#ifndef LIBJSON_JSON_H_INCLUDED
#  include <stddef.h> // size_t
#  define LIBJSON_JSON_H_INCLUDED
#  define JSON_STRING                    1u
#  define JSON_NUMBER                    2u
#  define JSON_NULL                      3u
#  define JSON_FALSE                     4u
#  define JSON_TRUE                      5u
#  define JSON_OPEN_OBJECT               6u
#  define JSON_CLOSE_OBJECT              7u
#  define JSON_OPEN_ARRAY                8u
#  define JSON_CLOSE_ARRAY               9u
#  define JSON_CONTINUE                 10u

#  define JSON_END_IN_SPACE	           100u
#  define JSON_END_ON_NEW_ARRAY        101u
#  define JSON_END_ON_NEW_OBJECT       102u
#  define JSON_END_ON_STRING           103u
#  define JSON_END_IN_STRING_TABLE     104u

#  define JSON_OBJECT_KEY_NOT_A_STRING 200u

union json_value
{
    double number;
    char*  string;
};

#  if defined(__cplusplus)
#    define JSON_BEGIN_DECLS   extern "C" {
#    define JSON_END_DECLS     }
#  else
#    define JSON_BEGIN_DECLS
#    define JSON_END_DECLS
#  endif

JSON_BEGIN_DECLS

const char*
json_type_name(unsigned int type);

unsigned int
json_encode_value(unsigned int type, union json_value value, char dst[], size_t max);

JSON_END_DECLS

#endif
