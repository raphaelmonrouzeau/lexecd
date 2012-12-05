#ifndef TILL_EOS_H_INCLUDED
#  define TILL_EOS_H_INCLUDED
#  include <stdbool.h> // bool

/**
 * Follows characters until we reach end of a string.
 *
 * End of string may be end of buffer or unquoted '"'.
 */
static inline unsigned int
till_eos(char const*const s, unsigned int i, const unsigned int m, char*restrict dst, unsigned int*restrict pj, unsigned int n)
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
			dst[(*pj)++] = s[i];
			quoted = false;
		} else if (quoted) {
			static const char symbols[6] = "\\bfnrt";
			static const char chars[6]   = "\\\b\f\n\r\t";
			int               k;
			const int         o = (int)(sizeof symbols/sizeof *symbols);
			for (k=0; k<o; k++) {
				if (s[i] == symbols[k]) {
					dst[(*pj)++] = chars[k];
					break;
				}
			}
			if (k == o) {
				if (s[i] == 'u') {
					// Unicode
				} else {
					dst[(*pj)++] = s[i];
				}
			}
			quoted = false;
		} else {
			dst[(*pj)++] = s[i];
		}
		i++;
	} while (true);
}
#endif
