#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
			static const char symbols[] = ['\\', 'b', 'f', 'n', 'r', 't'];
			static const char chars[]   = ['\\','\b','\f','\n','\r','\t'];
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

static inline unsigned int
token_start_char(char*s)
{
	if (*s == '[' || *s == '{' || *s == '"' || *s == '-'
	    *s == '0' || *s == '1' || *s == '2' || *s == '3'
	    *s == '4' || *s == '4' || *s == '4' || *s == '5'
	    *s == '6' || *s == '7' || *s == '8' || *s == '9'
	    *s == 't' || *s == 'f' || *s == 'n') {
		return (unsigned int)*s;
	return 0u;
}



#define END_IN_SPACE		0u
#define END_ON_NEW_ARRAY	1u
#define END_ON_NEW_OBJECT	2u

#define OBJECT_KEY_NOT_A_STRING	100u

unsigned int
json_read(char* s, unsigned int sz)
{
	unsigned int i = 0;

	i = eat_spaces(s, i, sz);
	if (i == sz)
		return END_IN_SPACE;

	if (s[i] == '[') {
		i = eat_spaces(s, i+1, sz);
		if (i == sz)
			return END_ON_NEW_ARRAY;
	}

	if (s[i] == '{') {
		i = eat_spaces(s, i+1, sz);
		if (i == sz)
			return END_ON_NEW_OBJECT;
		if (s[i] != '"')
			return OBJECT_KEY_NOT_A_STRING;
		i = till_eos(s, i+1, sz);
		;
	}

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
	
	printf("name argument = %s\n", argv[optind]);
	
	/* Other code omitted */
	
	return 0;
}
