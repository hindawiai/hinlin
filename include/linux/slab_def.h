<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SLAB_DEF_H
#घोषणा	_LINUX_SLAB_DEF_H

#समावेश <linux/kfence.h>
#समावेश <linux/reciprocal_भाग.h>

/*
 * Definitions unique to the original Linux SLAB allocator.
 */

काष्ठा kmem_cache अणु
	काष्ठा array_cache __percpu *cpu_cache;

/* 1) Cache tunables. Protected by slab_mutex */
	अचिन्हित पूर्णांक batchcount;
	अचिन्हित पूर्णांक limit;
	अचिन्हित पूर्णांक shared;

	अचिन्हित पूर्णांक size;
	काष्ठा reciprocal_value reciprocal_buffer_size;
/* 2) touched by every alloc & मुक्त from the backend */

	slab_flags_t flags;		/* स्थिरant flags */
	अचिन्हित पूर्णांक num;		/* # of objs per slab */

/* 3) cache_grow/shrink */
	/* order of pgs per slab (2^n) */
	अचिन्हित पूर्णांक gfporder;

	/* क्रमce GFP flags, e.g. GFP_DMA */
	gfp_t allocflags;

	माप_प्रकार colour;			/* cache colouring range */
	अचिन्हित पूर्णांक colour_off;	/* colour offset */
	काष्ठा kmem_cache *मुक्तlist_cache;
	अचिन्हित पूर्णांक मुक्तlist_size;

	/* स्थिरructor func */
	व्योम (*ctor)(व्योम *obj);

/* 4) cache creation/removal */
	स्थिर अक्षर *name;
	काष्ठा list_head list;
	पूर्णांक refcount;
	पूर्णांक object_size;
	पूर्णांक align;

/* 5) statistics */
#अगर_घोषित CONFIG_DEBUG_SLAB
	अचिन्हित दीर्घ num_active;
	अचिन्हित दीर्घ num_allocations;
	अचिन्हित दीर्घ high_mark;
	अचिन्हित दीर्घ grown;
	अचिन्हित दीर्घ reaped;
	अचिन्हित दीर्घ errors;
	अचिन्हित दीर्घ max_मुक्तable;
	अचिन्हित दीर्घ node_allocs;
	अचिन्हित दीर्घ node_मुक्तs;
	अचिन्हित दीर्घ node_overflow;
	atomic_t allochit;
	atomic_t allocmiss;
	atomic_t मुक्तhit;
	atomic_t मुक्तmiss;

	/*
	 * If debugging is enabled, then the allocator can add additional
	 * fields and/or padding to every object. 'size' contains the total
	 * object size including these पूर्णांकernal fields, जबतक 'obj_offset'
	 * and 'object_size' contain the offset to the user object and its
	 * size.
	 */
	पूर्णांक obj_offset;
#पूर्ण_अगर /* CONFIG_DEBUG_SLAB */

#अगर_घोषित CONFIG_KASAN
	काष्ठा kasan_cache kasan_info;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SLAB_FREELIST_RANDOM
	अचिन्हित पूर्णांक *अक्रमom_seq;
#पूर्ण_अगर

	अचिन्हित पूर्णांक useroffset;	/* Usercopy region offset */
	अचिन्हित पूर्णांक usersize;		/* Usercopy region size */

	काष्ठा kmem_cache_node *node[MAX_NUMNODES];
पूर्ण;

अटल अंतरभूत व्योम *nearest_obj(काष्ठा kmem_cache *cache, काष्ठा page *page,
				व्योम *x)
अणु
	व्योम *object = x - (x - page->s_mem) % cache->size;
	व्योम *last_object = page->s_mem + (cache->num - 1) * cache->size;

	अगर (unlikely(object > last_object))
		वापस last_object;
	अन्यथा
		वापस object;
पूर्ण

/*
 * We want to aव्योम an expensive भागide : (offset / cache->size)
 *   Using the fact that size is a स्थिरant क्रम a particular cache,
 *   we can replace (offset / cache->size) by
 *   reciprocal_भागide(offset, cache->reciprocal_buffer_size)
 */
अटल अंतरभूत अचिन्हित पूर्णांक obj_to_index(स्थिर काष्ठा kmem_cache *cache,
					स्थिर काष्ठा page *page, व्योम *obj)
अणु
	u32 offset = (obj - page->s_mem);
	वापस reciprocal_भागide(offset, cache->reciprocal_buffer_size);
पूर्ण

अटल अंतरभूत पूर्णांक objs_per_slab_page(स्थिर काष्ठा kmem_cache *cache,
				     स्थिर काष्ठा page *page)
अणु
	अगर (is_kfence_address(page_address(page)))
		वापस 1;
	वापस cache->num;
पूर्ण

#पूर्ण_अगर	/* _LINUX_SLAB_DEF_H */
