<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SLUB_DEF_H
#घोषणा _LINUX_SLUB_DEF_H

/*
 * SLUB : A Slab allocator without object queues.
 *
 * (C) 2007 SGI, Christoph Lameter
 */
#समावेश <linux/kfence.h>
#समावेश <linux/kobject.h>
#समावेश <linux/reciprocal_भाग.h>

क्रमागत stat_item अणु
	ALLOC_FASTPATH,		/* Allocation from cpu slab */
	ALLOC_SLOWPATH,		/* Allocation by getting a new cpu slab */
	FREE_FASTPATH,		/* Free to cpu slab */
	FREE_SLOWPATH,		/* Freeing not to cpu slab */
	FREE_FROZEN,		/* Freeing to frozen slab */
	FREE_ADD_PARTIAL,	/* Freeing moves slab to partial list */
	FREE_REMOVE_PARTIAL,	/* Freeing हटाओs last object */
	ALLOC_FROM_PARTIAL,	/* Cpu slab acquired from node partial list */
	ALLOC_SLAB,		/* Cpu slab acquired from page allocator */
	ALLOC_REFILL,		/* Refill cpu slab from slab मुक्तlist */
	ALLOC_NODE_MISMATCH,	/* Switching cpu slab */
	FREE_SLAB,		/* Slab मुक्तd to the page allocator */
	CPUSLAB_FLUSH,		/* Abanकरोning of the cpu slab */
	DEACTIVATE_FULL,	/* Cpu slab was full when deactivated */
	DEACTIVATE_EMPTY,	/* Cpu slab was empty when deactivated */
	DEACTIVATE_TO_HEAD,	/* Cpu slab was moved to the head of partials */
	DEACTIVATE_TO_TAIL,	/* Cpu slab was moved to the tail of partials */
	DEACTIVATE_REMOTE_FREES,/* Slab contained remotely मुक्तd objects */
	DEACTIVATE_BYPASS,	/* Implicit deactivation */
	ORDER_FALLBACK,		/* Number of बार fallback was necessary */
	CMPXCHG_DOUBLE_CPU_FAIL,/* Failure of this_cpu_cmpxchg_द्विगुन */
	CMPXCHG_DOUBLE_FAIL,	/* Number of बार that cmpxchg द्विगुन did not match */
	CPU_PARTIAL_ALLOC,	/* Used cpu partial on alloc */
	CPU_PARTIAL_FREE,	/* Refill cpu partial on मुक्त */
	CPU_PARTIAL_NODE,	/* Refill cpu partial from node partial */
	CPU_PARTIAL_DRAIN,	/* Drain cpu partial to node partial */
	NR_SLUB_STAT_ITEMS पूर्ण;

काष्ठा kmem_cache_cpu अणु
	व्योम **मुक्तlist;	/* Poपूर्णांकer to next available object */
	अचिन्हित दीर्घ tid;	/* Globally unique transaction id */
	काष्ठा page *page;	/* The slab from which we are allocating */
#अगर_घोषित CONFIG_SLUB_CPU_PARTIAL
	काष्ठा page *partial;	/* Partially allocated frozen sद_असल */
#पूर्ण_अगर
#अगर_घोषित CONFIG_SLUB_STATS
	अचिन्हित stat[NR_SLUB_STAT_ITEMS];
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SLUB_CPU_PARTIAL
#घोषणा slub_percpu_partial(c)		((c)->partial)

#घोषणा slub_set_percpu_partial(c, p)		\
(अणु						\
	slub_percpu_partial(c) = (p)->next;	\
पूर्ण)

#घोषणा slub_percpu_partial_पढ़ो_once(c)     READ_ONCE(slub_percpu_partial(c))
#अन्यथा
#घोषणा slub_percpu_partial(c)			शून्य

#घोषणा slub_set_percpu_partial(c, p)

#घोषणा slub_percpu_partial_पढ़ो_once(c)	शून्य
#पूर्ण_अगर // CONFIG_SLUB_CPU_PARTIAL

/*
 * Word size काष्ठाure that can be atomically updated or पढ़ो and that
 * contains both the order and the number of objects that a slab of the
 * given order would contain.
 */
काष्ठा kmem_cache_order_objects अणु
	अचिन्हित पूर्णांक x;
पूर्ण;

/*
 * Slab cache management.
 */
काष्ठा kmem_cache अणु
	काष्ठा kmem_cache_cpu __percpu *cpu_slab;
	/* Used क्रम retrieving partial sद_असल, etc. */
	slab_flags_t flags;
	अचिन्हित दीर्घ min_partial;
	अचिन्हित पूर्णांक size;	/* The size of an object including metadata */
	अचिन्हित पूर्णांक object_size;/* The size of an object without metadata */
	काष्ठा reciprocal_value reciprocal_size;
	अचिन्हित पूर्णांक offset;	/* Free poपूर्णांकer offset */
#अगर_घोषित CONFIG_SLUB_CPU_PARTIAL
	/* Number of per cpu partial objects to keep around */
	अचिन्हित पूर्णांक cpu_partial;
#पूर्ण_अगर
	काष्ठा kmem_cache_order_objects oo;

	/* Allocation and मुक्तing of sद_असल */
	काष्ठा kmem_cache_order_objects max;
	काष्ठा kmem_cache_order_objects min;
	gfp_t allocflags;	/* gfp flags to use on each alloc */
	पूर्णांक refcount;		/* Refcount क्रम slab cache destroy */
	व्योम (*ctor)(व्योम *);
	अचिन्हित पूर्णांक inuse;		/* Offset to metadata */
	अचिन्हित पूर्णांक align;		/* Alignment */
	अचिन्हित पूर्णांक red_left_pad;	/* Left redzone padding size */
	स्थिर अक्षर *name;	/* Name (only क्रम display!) */
	काष्ठा list_head list;	/* List of slab caches */
#अगर_घोषित CONFIG_SYSFS
	काष्ठा kobject kobj;	/* For sysfs */
#पूर्ण_अगर
#अगर_घोषित CONFIG_SLAB_FREELIST_HARDENED
	अचिन्हित दीर्घ अक्रमom;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA
	/*
	 * Defragmentation by allocating from a remote node.
	 */
	अचिन्हित पूर्णांक remote_node_defrag_ratio;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SLAB_FREELIST_RANDOM
	अचिन्हित पूर्णांक *अक्रमom_seq;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN
	काष्ठा kasan_cache kasan_info;
#पूर्ण_अगर

	अचिन्हित पूर्णांक useroffset;	/* Usercopy region offset */
	अचिन्हित पूर्णांक usersize;		/* Usercopy region size */

	काष्ठा kmem_cache_node *node[MAX_NUMNODES];
पूर्ण;

#अगर_घोषित CONFIG_SLUB_CPU_PARTIAL
#घोषणा slub_cpu_partial(s)		((s)->cpu_partial)
#घोषणा slub_set_cpu_partial(s, n)		\
(अणु						\
	slub_cpu_partial(s) = (n);		\
पूर्ण)
#अन्यथा
#घोषणा slub_cpu_partial(s)		(0)
#घोषणा slub_set_cpu_partial(s, n)
#पूर्ण_अगर /* CONFIG_SLUB_CPU_PARTIAL */

#अगर_घोषित CONFIG_SYSFS
#घोषणा SLAB_SUPPORTS_SYSFS
व्योम sysfs_slab_unlink(काष्ठा kmem_cache *);
व्योम sysfs_slab_release(काष्ठा kmem_cache *);
#अन्यथा
अटल अंतरभूत व्योम sysfs_slab_unlink(काष्ठा kmem_cache *s)
अणु
पूर्ण
अटल अंतरभूत व्योम sysfs_slab_release(काष्ठा kmem_cache *s)
अणु
पूर्ण
#पूर्ण_अगर

व्योम object_err(काष्ठा kmem_cache *s, काष्ठा page *page,
		u8 *object, अक्षर *reason);

व्योम *fixup_red_left(काष्ठा kmem_cache *s, व्योम *p);

अटल अंतरभूत व्योम *nearest_obj(काष्ठा kmem_cache *cache, काष्ठा page *page,
				व्योम *x) अणु
	व्योम *object = x - (x - page_address(page)) % cache->size;
	व्योम *last_object = page_address(page) +
		(page->objects - 1) * cache->size;
	व्योम *result = (unlikely(object > last_object)) ? last_object : object;

	result = fixup_red_left(cache, result);
	वापस result;
पूर्ण

/* Determine object index from a given position */
अटल अंतरभूत अचिन्हित पूर्णांक __obj_to_index(स्थिर काष्ठा kmem_cache *cache,
					  व्योम *addr, व्योम *obj)
अणु
	वापस reciprocal_भागide(kasan_reset_tag(obj) - addr,
				 cache->reciprocal_size);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक obj_to_index(स्थिर काष्ठा kmem_cache *cache,
					स्थिर काष्ठा page *page, व्योम *obj)
अणु
	अगर (is_kfence_address(obj))
		वापस 0;
	वापस __obj_to_index(cache, page_address(page), obj);
पूर्ण

अटल अंतरभूत पूर्णांक objs_per_slab_page(स्थिर काष्ठा kmem_cache *cache,
				     स्थिर काष्ठा page *page)
अणु
	वापस page->objects;
पूर्ण
#पूर्ण_अगर /* _LINUX_SLUB_DEF_H */
