/* SPDX-License-Identifier: MPL-2.0
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
 * Returns how many characters have been inserted.
 */
size_t
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

size_t
CTK_StrInsert(char *restrict dest,
              const size_t dest_size,
              const size_t pos,
              const char *restrict src)
{
	size_t new_len;
	size_t old_len;
	size_t paste_len;
	long   push_back;
	size_t src_len;

	old_len = strlen(dest);
	src_len = strlen(src);
	new_len = old_len + src_len;
	if (new_len >= dest_size)
		new_len = dest_size - 1;

	push_back = dest_size - pos - src_len - 1;
	paste_len = src_len;
	if (paste_len >= dest_size - pos)
		paste_len = dest_size - pos - 1;

	if (push_back > 0)
		memmove(&dest[pos + src_len], &dest[pos], push_back);

	memmove(&dest[pos], src, paste_len);
	dest[new_len] = '\0';

	return paste_len;
}

#endif /* CTK_IMPLEMENTATION */

#endif /* _CTK_STRING_H */
