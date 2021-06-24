<शैली गुरु>
/*
 * zsदो_स्मृति memory allocator
 *
 * Copyright (C) 2011  Nitin Gupta
 * Copyright (C) 2012, 2013 Minchan Kim
 *
 * This code is released using a dual license strategy: BSD/GPL
 * You can choose the license that better fits your requirements.
 *
 * Released under the terms of 3-clause BSD License
 * Released under the terms of GNU General Public License Version 2.0
 */

#अगर_अघोषित _ZS_MALLOC_H_
#घोषणा _ZS_MALLOC_H_

#समावेश <linux/types.h>

/*
 * zsदो_स्मृति mapping modes
 *
 * NOTE: These only make a dअगरference when a mapped object spans pages.
 */
क्रमागत zs_mapmode अणु
	ZS_MM_RW, /* normal पढ़ो-ग_लिखो mapping */
	ZS_MM_RO, /* पढ़ो-only (no copy-out at unmap समय) */
	ZS_MM_WO /* ग_लिखो-only (no copy-in at map समय) */
	/*
	 * NOTE: ZS_MM_WO should only be used क्रम initializing new
	 * (uninitialized) allocations.  Partial ग_लिखोs to alपढ़ोy
	 * initialized allocations should use ZS_MM_RW to preserve the
	 * existing data.
	 */
पूर्ण;

काष्ठा zs_pool_stats अणु
	/* How many pages were migrated (मुक्तd) */
	atomic_दीर्घ_t pages_compacted;
पूर्ण;

काष्ठा zs_pool;

काष्ठा zs_pool *zs_create_pool(स्थिर अक्षर *name);
व्योम zs_destroy_pool(काष्ठा zs_pool *pool);

अचिन्हित दीर्घ zs_दो_स्मृति(काष्ठा zs_pool *pool, माप_प्रकार size, gfp_t flags);
व्योम zs_मुक्त(काष्ठा zs_pool *pool, अचिन्हित दीर्घ obj);

माप_प्रकार zs_huge_class_size(काष्ठा zs_pool *pool);

व्योम *zs_map_object(काष्ठा zs_pool *pool, अचिन्हित दीर्घ handle,
			क्रमागत zs_mapmode mm);
व्योम zs_unmap_object(काष्ठा zs_pool *pool, अचिन्हित दीर्घ handle);

अचिन्हित दीर्घ zs_get_total_pages(काष्ठा zs_pool *pool);
अचिन्हित दीर्घ zs_compact(काष्ठा zs_pool *pool);

व्योम zs_pool_stats(काष्ठा zs_pool *pool, काष्ठा zs_pool_stats *stats);
#पूर्ण_अगर
