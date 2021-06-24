<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains hardware tag-based KASAN specअगरic error reporting code.
 *
 * Copyright (c) 2020 Google, Inc.
 * Author: Andrey Konovalov <andreyknvl@google.com>
 */

#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memory.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश "kasan.h"

स्थिर अक्षर *kasan_get_bug_type(काष्ठा kasan_access_info *info)
अणु
	वापस "invalid-access";
पूर्ण

व्योम *kasan_find_first_bad_addr(व्योम *addr, माप_प्रकार size)
अणु
	वापस kasan_reset_tag(addr);
पूर्ण

व्योम kasan_metadata_fetch_row(अक्षर *buffer, व्योम *row)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < META_BYTES_PER_ROW; i++)
		buffer[i] = hw_get_mem_tag(row + i * KASAN_GRANULE_SIZE);
पूर्ण

व्योम kasan_prपूर्णांक_tags(u8 addr_tag, स्थिर व्योम *addr)
अणु
	u8 memory_tag = hw_get_mem_tag((व्योम *)addr);

	pr_err("Pointer tag: [%02x], memory tag: [%02x]\n",
		addr_tag, memory_tag);
पूर्ण
