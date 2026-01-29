/* SPDX-License-Identifier: LGPL-2.1-only
 * Copyright (C) 2025 - 2026  Andy Frank Schoknecht
 */

#ifndef _STR_H
#define _STR_H

#include <stddef.h>

#include "CTK_version.h"

#define STR_TEXT_BLOCK_SIZE 32

#define STR_VERSION LIB_VERSION

/* Cuts from a string, reducing its size, by setting a null byte
 */
char*
STR_Cut(char *str,
        const size_t pos,
        const size_t len);

/* Inserts into a string, pushing old content back
 */
char*
STR_Insert(char         **restrict dest,
           size_t        *dest_size,
           const size_t   pos,
           const char    *restrict src);

#endif /* _STR_H */
