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

#include "till_eos.h"
#include "json.h"



void
json_quick_print(unsigned int type, union json_value value)
{
    char buff[1024];
    unsigned int n = json_encode_value(type, value, buff, 1023);
    buff[n] = '\0';
    printf("%s\n", buff);
}

unsigned int
json_decode_value(char* s, unsigned int sz, void (*cb)(unsigned int,union json_value))
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

/*
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
			 help 
			break;
		    case 'v':
			 version 
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
}*/
