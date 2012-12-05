#include <unistd.h>     // getopt?
#include <stdlib.h>     // malloc/realloc
#include <stdio.h>      // fprintf
#include <stdbool.h>    // bool
#include <string.h>     // strerror
#include <errno.h>      // errno

//#include "../submodules/ultrajson/lib/ultrajson.h"
//#include "../submodules/ultrajson/lib/ultrajsondec.c"



static inline unsigned int
eat_spaces(char*s, unsigned int i, const unsigned int m)
{
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		if (++i==m)
			return i;
	return i;
}

static inline unsigned int
till_eos(char*restrict s, unsigned int i, const unsigned int m, char*restrict dst, unsigned int* pj, unsigned int n)
{
	bool quoted = false;

	do {
		if (i == m)
			return i;
		if (*pj == n)
			return i;
		if (s[i] == '\\') {
			quoted = true;
		} else if (s[i] == '"') {
			if (!quoted)
				return i;
			dst[*(pj++)] = s[i];
			quoted = false;
		} else if (quoted) {
			static const char symbols[6] = "\\bfnrt";
			static const char chars[6]   = "\\\b\f\n\r\t";
			int               k;
			const int         o = (int)(sizeof symbols/sizeof *symbols);
			for (k=0; k<o; k++) {
				if (s[i] == symbols[k]) {
					dst[*(pj++)] = chars[k];
					break;
				}
			}
			if (k == o) {
				if (s[i] == 'u') {
					// Unicode
				} else {
					dst[*(pj++)] = s[i];
				}
			}
			quoted = false;
		} else {
			dst[*(pj++)] = s[i];
		}
		i++;
	} while (true);
};



#define JSON_STRING                    1u
#define JSON_NUMBER                    2u
#define JSON_NULL                      3u
#define JSON_FALSE                     4u
#define JSON_TRUE                      5u
#define JSON_OPEN_OBJECT               6u
#define JSON_CLOSE_OBJECT              7u
#define JSON_OPEN_ARRAY                8u
#define JSON_CLOSE_ARRAY               9u
#define JSON_CONTINUE                 10u

#define JSON_END_IN_SPACE		     100u
#define JSON_END_ON_NEW_ARRAY	     101u
#define JSON_END_ON_NEW_OBJECT	     102u
#define JSON_END_ON_STRING           103u
#define JSON_END_IN_STRING_TABLE     104u

#define JSON_OBJECT_KEY_NOT_A_STRING 200u

union json_value
{
    double number;
    char*  string;
};

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

void
json_quick_print(unsigned int type, union json_value value)
{
    char buff[1024];
    unsigned int n = json_encode_value(type, value, buff, 1023);
    buff[n] = '\0';
    printf("%s\n", buff);
}

unsigned int
json_read(char* s, unsigned int sz, void (*cb)(unsigned int,union json_value))
{
	unsigned int i = 0;

    char sts[1024];
    unsigned int sti = 0;
    unsigned int stsz = 1024u;

    union json_value value;

	i = eat_spaces(s, i, sz);
	if (i == sz) {
		cb(JSON_END_IN_SPACE, value);
        return i;
    }

	if (s[i] == '[') {
		i = eat_spaces(s, i+1, sz);
		if (i == sz) {
			cb(JSON_END_ON_NEW_ARRAY, value);
            return i;
        }
	}

	if (s[i] == '{') {
        cb(JSON_OPEN_OBJECT, value);
		i = eat_spaces(s, i+1, sz);
		if (i == sz) {
			cb(JSON_END_ON_NEW_OBJECT, value);
            return i;
        }
        if (s[i] == '}') {
            cb(JSON_CLOSE_OBJECT, value);
        } else if (s[i] != '"') {
			cb(JSON_OBJECT_KEY_NOT_A_STRING, value);
            return i;
        }
		i = till_eos(s, i+1, sz, sts, &sti, stsz);
		;
	}

    if (s[i] == '"') {
        char* string = &sts[sti];
        i = till_eos(s, i+1, sz, sts, &sti, stsz);
        printf("eos: i=%u sz=%u\n",i,sz);
        if (i == sz) {
            cb(JSON_END_ON_STRING, value);
            return i;
        } else if (sti == stsz) {
            cb(JSON_END_IN_STRING_TABLE, value);
            return i;
        }
        sts[sti++] = '\0';
        value.string = string;
        cb(JSON_STRING, value);
    }

    return i;
}

static void callback(unsigned int type, union json_value value)
{
    printf("%s\n", json_type_name(type));
    char buff[1024];
    unsigned int n = json_encode_value(type, value, buff, 1023);
    buff[n] = '\0';
    printf("%s\n", buff);
}

int
main(int argc, char *const argv[])
{
	int opt;
	
	while ((opt = getopt(argc, argv, "h:vc:")) != -1) {
		switch (opt) {
		    case 'h':
			/* help */
			break;
		    case 'v':
			/* version */
			break;
		    case '?':
		    default:
			fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
			        argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	
	
	
	if (optind >= argc) {
		fprintf(stderr, "Expected file path\n");
		exit(EXIT_FAILURE);
	}
	
	printf("file path = %s\n", argv[optind]);
	
	char* file_path = argv[optind];

    FILE* file_handle = fopen(file_path, "r");
	
    if (file_handle == NULL) {
        fprintf(stderr, "Can't open file '%s' for reading: %s\n",
                file_path, strerror(errno));
        return 1;
    }

    char* content = NULL;
    const size_t inc = 4096;
    size_t size = 0;

    do {
        size += inc;
        content = realloc(content, size);
        size_t tmp = fread(content, 1, inc, file_handle);
        if (tmp != inc) {
            if (ferror(file_handle)) {
                fprintf(stderr, "Error reading file '%s'\n",
                        file_path);
                return 1;
            }
            size += tmp;
            break;
        }
    } while (0);

    //char string_table[1024];

    unsigned int i = json_read(content, size, callback);

    fprintf(stdout, "read: i=%u\n", i);

	return 0;
}
