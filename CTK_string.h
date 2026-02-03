/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025 - 2026  Andy Frank Schoknecht
 */

#ifndef _CTK_STRING_H
#define _CTK_STRING_H

#include <stdlib.h>
#include <string.h>

/* Cuts from a string, reducing its size, by setting a null byte
 */
char*
CTK_StrCut(char *str,
           const size_t pos,
           const size_t len);

/* Inserts into a string, pushing old content back
 */
char*
CTK_StrInsert(char *restrict dest,
              const size_t dest_size,
              const size_t pos,
              const char *restrict src);

#ifdef CTK_IMPLEMENTATION

char*
CTK_StrCut(char *str,
           const size_t pos,
           const size_t len)
{
	size_t i;
	size_t str_len;

	str_len = strlen(str);

	if (pos + len > str_len) {
		return NULL;
	}

	for (i = pos + len; i < str_len; i++) {
		str[i - len] = str[i];
	}
	str[str_len - len] = '\0';

	return str;
}

char*
CTK_StrInsert(char *restrict dest,
              const size_t dest_size,
              const size_t pos,
              const char *restrict src)
{
	size_t new_len;
	size_t old_len;
	size_t src_len;

	old_len = strlen(dest);
	src_len = strlen(src);

	memmove(&dest[pos + src_len], &dest[pos], dest_size - pos - src_len - 1);
	memmove(&dest[pos], src, src_len);

	new_len = old_len + src_len;
	if (new_len >= dest_size)
		new_len = dest_size - 1;
	dest[new_len] = '\0';

	return dest;
}

#endif /* CTK_IMPLEMENTATION */

#endif /* _CTK_STRING_H */
