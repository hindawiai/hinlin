<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains software tag-based KASAN specअगरic error reporting code.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 *
 * Some code borrowed from https://github.com/xairy/kasan-prototype by
 *        Andrey Konovalov <andreyknvl@gmail.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/stackdepot.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/kasan.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/sections.h>

#समावेश "kasan.h"
#समावेश "../slab.h"

स्थिर अक्षर *kasan_get_bug_type(काष्ठा kasan_access_info *info)
अणु
#अगर_घोषित CONFIG_KASAN_SW_TAGS_IDENTIFY
	काष्ठा kasan_alloc_meta *alloc_meta;
	काष्ठा kmem_cache *cache;
	काष्ठा page *page;
	स्थिर व्योम *addr;
	व्योम *object;
	u8 tag;
	पूर्णांक i;

	tag = get_tag(info->access_addr);
	addr = kasan_reset_tag(info->access_addr);
	page = kasan_addr_to_page(addr);
	अगर (page && PageSlab(page)) अणु
		cache = page->slab_cache;
		object = nearest_obj(cache, page, (व्योम *)addr);
		alloc_meta = kasan_get_alloc_meta(cache, object);

		अगर (alloc_meta) अणु
			क्रम (i = 0; i < KASAN_NR_FREE_STACKS; i++) अणु
				अगर (alloc_meta->मुक्त_poपूर्णांकer_tag[i] == tag)
					वापस "use-after-free";
			पूर्ण
		पूर्ण
		वापस "out-of-bounds";
	पूर्ण

#पूर्ण_अगर
	/*
	 * If access_size is a negative number, then it has reason to be
	 * defined as out-of-bounds bug type.
	 *
	 * Casting negative numbers to माप_प्रकार would indeed turn up as
	 * a large माप_प्रकार and its value will be larger than अच_दीर्घ_उच्च/2,
	 * so that this can qualअगरy as out-of-bounds.
	 */
	अगर (info->access_addr + info->access_size < info->access_addr)
		वापस "out-of-bounds";

	वापस "invalid-access";
पूर्ण

व्योम *kasan_find_first_bad_addr(व्योम *addr, माप_प्रकार size)
अणु
	u8 tag = get_tag(addr);
	व्योम *p = kasan_reset_tag(addr);
	व्योम *end = p + size;

	जबतक (p < end && tag == *(u8 *)kasan_mem_to_shaकरोw(p))
		p += KASAN_GRANULE_SIZE;
	वापस p;
पूर्ण

व्योम kasan_metadata_fetch_row(अक्षर *buffer, व्योम *row)
अणु
	स_नकल(buffer, kasan_mem_to_shaकरोw(row), META_BYTES_PER_ROW);
पूर्ण

व्योम kasan_prपूर्णांक_tags(u8 addr_tag, स्थिर व्योम *addr)
अणु
	u8 *shaकरोw = (u8 *)kasan_mem_to_shaकरोw(addr);

	pr_err("Pointer tag: [%02x], memory tag: [%02x]\n", addr_tag, *shaकरोw);
पूर्ण
