<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 ARM Ltd.
 */

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cacheflush.h>

व्योम स_नकल_flushcache(व्योम *dst, स्थिर व्योम *src, माप_प्रकार cnt)
अणु
	/*
	 * We assume this should not be called with @dst poपूर्णांकing to
	 * non-cacheable memory, such that we करोn't need an explicit
	 * barrier to order the cache मुख्यtenance against the स_नकल.
	 */
	स_नकल(dst, src, cnt);
	__clean_dcache_area_pop(dst, cnt);
पूर्ण
EXPORT_SYMBOL_GPL(स_नकल_flushcache);

व्योम स_नकल_page_flushcache(अक्षर *to, काष्ठा page *page, माप_प्रकार offset,
			    माप_प्रकार len)
अणु
	स_नकल_flushcache(to, page_address(page) + offset, len);
पूर्ण

अचिन्हित दीर्घ __copy_user_flushcache(व्योम *to, स्थिर व्योम __user *from,
				     अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ rc;

	rc = raw_copy_from_user(to, from, n);

	/* See above */
	__clean_dcache_area_pop(to, n - rc);
	वापस rc;
पूर्ण
