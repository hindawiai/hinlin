<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Written by Mark Hemment, 1996 (markhe@nextd.demon.co.uk).
 *
 * (C) SGI 2006, Christoph Lameter
 * 	Cleaned up and reकाष्ठाured to ease the addition of alternative
 * 	implementations of SLAB allocators.
 * (C) Linux Foundation 2008-2013
 *      Unअगरied पूर्णांकerface क्रम all slab allocators
 */

#अगर_अघोषित _LINUX_SLAB_H
#घोषणा	_LINUX_SLAB_H

#समावेश <linux/gfp.h>
#समावेश <linux/overflow.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/percpu-refcount.h>


/*
 * Flags to pass to kmem_cache_create().
 * The ones marked DEBUG are only valid अगर CONFIG_DEBUG_SLAB is set.
 */
/* DEBUG: Perक्रमm (expensive) checks on alloc/मुक्त */
#घोषणा SLAB_CONSISTENCY_CHECKS	((slab_flags_t __क्रमce)0x00000100U)
/* DEBUG: Red zone objs in a cache */
#घोषणा SLAB_RED_ZONE		((slab_flags_t __क्रमce)0x00000400U)
/* DEBUG: Poison objects */
#घोषणा SLAB_POISON		((slab_flags_t __क्रमce)0x00000800U)
/* Align objs on cache lines */
#घोषणा SLAB_HWCACHE_ALIGN	((slab_flags_t __क्रमce)0x00002000U)
/* Use GFP_DMA memory */
#घोषणा SLAB_CACHE_DMA		((slab_flags_t __क्रमce)0x00004000U)
/* Use GFP_DMA32 memory */
#घोषणा SLAB_CACHE_DMA32	((slab_flags_t __क्रमce)0x00008000U)
/* DEBUG: Store the last owner क्रम bug hunting */
#घोषणा SLAB_STORE_USER		((slab_flags_t __क्रमce)0x00010000U)
/* Panic अगर kmem_cache_create() fails */
#घोषणा SLAB_PANIC		((slab_flags_t __क्रमce)0x00040000U)
/*
 * SLAB_TYPESAFE_BY_RCU - **WARNING** READ THIS!
 *
 * This delays मुक्तing the SLAB page by a grace period, it करोes _NOT_
 * delay object मुक्तing. This means that अगर you करो kmem_cache_मुक्त()
 * that memory location is मुक्त to be reused at any समय. Thus it may
 * be possible to see another object there in the same RCU grace period.
 *
 * This feature only ensures the memory location backing the object
 * stays valid, the trick to using this is relying on an independent
 * object validation pass. Something like:
 *
 *  rcu_पढ़ो_lock()
 * again:
 *  obj = lockless_lookup(key);
 *  अगर (obj) अणु
 *    अगर (!try_get_ref(obj)) // might fail क्रम मुक्त objects
 *      जाओ again;
 *
 *    अगर (obj->key != key) अणु // not the object we expected
 *      put_ref(obj);
 *      जाओ again;
 *    पूर्ण
 *  पूर्ण
 *  rcu_पढ़ो_unlock();
 *
 * This is useful अगर we need to approach a kernel काष्ठाure obliquely,
 * from its address obtained without the usual locking. We can lock
 * the काष्ठाure to stabilize it and check it's still at the given address,
 * only अगर we can be sure that the memory has not been meanजबतक reused
 * क्रम some other kind of object (which our subप्रणाली's lock might corrupt).
 *
 * rcu_पढ़ो_lock beक्रमe पढ़ोing the address, then rcu_पढ़ो_unlock after
 * taking the spinlock within the काष्ठाure expected at that address.
 *
 * Note that SLAB_TYPESAFE_BY_RCU was originally named SLAB_DESTROY_BY_RCU.
 */
/* Defer मुक्तing sद_असल to RCU */
#घोषणा SLAB_TYPESAFE_BY_RCU	((slab_flags_t __क्रमce)0x00080000U)
/* Spपढ़ो some memory over cpuset */
#घोषणा SLAB_MEM_SPREAD		((slab_flags_t __क्रमce)0x00100000U)
/* Trace allocations and मुक्तs */
#घोषणा SLAB_TRACE		((slab_flags_t __क्रमce)0x00200000U)

/* Flag to prevent checks on मुक्त */
#अगर_घोषित CONFIG_DEBUG_OBJECTS
# define SLAB_DEBUG_OBJECTS	((slab_flags_t __क्रमce)0x00400000U)
#अन्यथा
# define SLAB_DEBUG_OBJECTS	0
#पूर्ण_अगर

/* Aव्योम kmemleak tracing */
#घोषणा SLAB_NOLEAKTRACE	((slab_flags_t __क्रमce)0x00800000U)

/* Fault injection mark */
#अगर_घोषित CONFIG_FAILSLAB
# define SLAB_FAILSLAB		((slab_flags_t __क्रमce)0x02000000U)
#अन्यथा
# define SLAB_FAILSLAB		0
#पूर्ण_अगर
/* Account to memcg */
#अगर_घोषित CONFIG_MEMCG_KMEM
# define SLAB_ACCOUNT		((slab_flags_t __क्रमce)0x04000000U)
#अन्यथा
# define SLAB_ACCOUNT		0
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN
#घोषणा SLAB_KASAN		((slab_flags_t __क्रमce)0x08000000U)
#अन्यथा
#घोषणा SLAB_KASAN		0
#पूर्ण_अगर

/* The following flags affect the page allocator grouping pages by mobility */
/* Objects are reclaimable */
#घोषणा SLAB_RECLAIM_ACCOUNT	((slab_flags_t __क्रमce)0x00020000U)
#घोषणा SLAB_TEMPORARY		SLAB_RECLAIM_ACCOUNT	/* Objects are लघु-lived */

/* Slab deactivation flag */
#घोषणा SLAB_DEACTIVATED	((slab_flags_t __क्रमce)0x10000000U)

/*
 * ZERO_SIZE_PTR will be वापसed क्रम zero sized kदो_स्मृति requests.
 *
 * Dereferencing ZERO_SIZE_PTR will lead to a distinct access fault.
 *
 * ZERO_SIZE_PTR can be passed to kमुक्त though in the same way that शून्य can.
 * Both make kमुक्त a no-op.
 */
#घोषणा ZERO_SIZE_PTR ((व्योम *)16)

#घोषणा ZERO_OR_शून्य_PTR(x) ((अचिन्हित दीर्घ)(x) <= \
				(अचिन्हित दीर्घ)ZERO_SIZE_PTR)

#समावेश <linux/kasan.h>

काष्ठा mem_cgroup;
/*
 * काष्ठा kmem_cache related prototypes
 */
व्योम __init kmem_cache_init(व्योम);
bool slab_is_available(व्योम);

बाह्य bool usercopy_fallback;

काष्ठा kmem_cache *kmem_cache_create(स्थिर अक्षर *name, अचिन्हित पूर्णांक size,
			अचिन्हित पूर्णांक align, slab_flags_t flags,
			व्योम (*ctor)(व्योम *));
काष्ठा kmem_cache *kmem_cache_create_usercopy(स्थिर अक्षर *name,
			अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक align,
			slab_flags_t flags,
			अचिन्हित पूर्णांक useroffset, अचिन्हित पूर्णांक usersize,
			व्योम (*ctor)(व्योम *));
व्योम kmem_cache_destroy(काष्ठा kmem_cache *);
पूर्णांक kmem_cache_shrink(काष्ठा kmem_cache *);

/*
 * Please use this macro to create slab caches. Simply specअगरy the
 * name of the काष्ठाure and maybe some flags that are listed above.
 *
 * The alignment of the काष्ठा determines object alignment. If you
 * f.e. add ____cacheline_aligned_in_smp to the काष्ठा declaration
 * then the objects will be properly aligned in SMP configurations.
 */
#घोषणा KMEM_CACHE(__काष्ठा, __flags)					\
		kmem_cache_create(#__काष्ठा, माप(काष्ठा __काष्ठा),	\
			__alignof__(काष्ठा __काष्ठा), (__flags), शून्य)

/*
 * To whitelist a single field क्रम copying to/from usercopy, use this
 * macro instead क्रम KMEM_CACHE() above.
 */
#घोषणा KMEM_CACHE_USERCOPY(__काष्ठा, __flags, __field)			\
		kmem_cache_create_usercopy(#__काष्ठा,			\
			माप(काष्ठा __काष्ठा),			\
			__alignof__(काष्ठा __काष्ठा), (__flags),	\
			दुरत्व(काष्ठा __काष्ठा, __field),		\
			माप_field(काष्ठा __काष्ठा, __field), शून्य)

/*
 * Common kदो_स्मृति functions provided by all allocators
 */
व्योम * __must_check kपुनः_स्मृति(स्थिर व्योम *, माप_प्रकार, gfp_t);
व्योम kमुक्त(स्थिर व्योम *);
व्योम kमुक्त_sensitive(स्थिर व्योम *);
माप_प्रकार __ksize(स्थिर व्योम *);
माप_प्रकार ksize(स्थिर व्योम *);
#अगर_घोषित CONFIG_PRINTK
bool kmem_valid_obj(व्योम *object);
व्योम kmem_dump_obj(व्योम *object);
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_HARDENED_USERCOPY_ALLOCATOR
व्योम __check_heap_object(स्थिर व्योम *ptr, अचिन्हित दीर्घ n, काष्ठा page *page,
			bool to_user);
#अन्यथा
अटल अंतरभूत व्योम __check_heap_object(स्थिर व्योम *ptr, अचिन्हित दीर्घ n,
				       काष्ठा page *page, bool to_user) अणु पूर्ण
#पूर्ण_अगर

/*
 * Some archs want to perक्रमm DMA पूर्णांकo kदो_स्मृति caches and need a guaranteed
 * alignment larger than the alignment of a 64-bit पूर्णांकeger.
 * Setting ARCH_KMALLOC_MINALIGN in arch headers allows that.
 */
#अगर defined(ARCH_DMA_MINALIGN) && ARCH_DMA_MINALIGN > 8
#घोषणा ARCH_KMALLOC_MINALIGN ARCH_DMA_MINALIGN
#घोषणा KMALLOC_MIN_SIZE ARCH_DMA_MINALIGN
#घोषणा KMALLOC_SHIFT_LOW ilog2(ARCH_DMA_MINALIGN)
#अन्यथा
#घोषणा ARCH_KMALLOC_MINALIGN __alignof__(अचिन्हित दीर्घ दीर्घ)
#पूर्ण_अगर

/*
 * Setting ARCH_SLAB_MINALIGN in arch headers allows a dअगरferent alignment.
 * Intended क्रम arches that get misalignment faults even क्रम 64 bit पूर्णांकeger
 * aligned buffers.
 */
#अगर_अघोषित ARCH_SLAB_MINALIGN
#घोषणा ARCH_SLAB_MINALIGN __alignof__(अचिन्हित दीर्घ दीर्घ)
#पूर्ण_अगर

/*
 * kदो_स्मृति and मित्रs वापस ARCH_KMALLOC_MINALIGN aligned
 * poपूर्णांकers. kmem_cache_alloc and मित्रs वापस ARCH_SLAB_MINALIGN
 * aligned poपूर्णांकers.
 */
#घोषणा __assume_kदो_स्मृति_alignment __assume_aligned(ARCH_KMALLOC_MINALIGN)
#घोषणा __assume_slab_alignment __assume_aligned(ARCH_SLAB_MINALIGN)
#घोषणा __assume_page_alignment __assume_aligned(PAGE_SIZE)

/*
 * Kदो_स्मृति array related definitions
 */

#अगर_घोषित CONFIG_SLAB
/*
 * The largest kदो_स्मृति size supported by the SLAB allocators is
 * 32 megabyte (2^25) or the maximum allocatable page order अगर that is
 * less than 32 MB.
 *
 * WARNING: Its not easy to increase this value since the allocators have
 * to करो various tricks to work around compiler limitations in order to
 * ensure proper स्थिरant folding.
 */
#घोषणा KMALLOC_SHIFT_HIGH	((MAX_ORDER + PAGE_SHIFT - 1) <= 25 ? \
				(MAX_ORDER + PAGE_SHIFT - 1) : 25)
#घोषणा KMALLOC_SHIFT_MAX	KMALLOC_SHIFT_HIGH
#अगर_अघोषित KMALLOC_SHIFT_LOW
#घोषणा KMALLOC_SHIFT_LOW	5
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_SLUB
/*
 * SLUB directly allocates requests fitting in to an order-1 page
 * (PAGE_SIZE*2).  Larger requests are passed to the page allocator.
 */
#घोषणा KMALLOC_SHIFT_HIGH	(PAGE_SHIFT + 1)
#घोषणा KMALLOC_SHIFT_MAX	(MAX_ORDER + PAGE_SHIFT - 1)
#अगर_अघोषित KMALLOC_SHIFT_LOW
#घोषणा KMALLOC_SHIFT_LOW	3
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_SLOB
/*
 * SLOB passes all requests larger than one page to the page allocator.
 * No kदो_स्मृति array is necessary since objects of dअगरferent sizes can
 * be allocated from the same page.
 */
#घोषणा KMALLOC_SHIFT_HIGH	PAGE_SHIFT
#घोषणा KMALLOC_SHIFT_MAX	(MAX_ORDER + PAGE_SHIFT - 1)
#अगर_अघोषित KMALLOC_SHIFT_LOW
#घोषणा KMALLOC_SHIFT_LOW	3
#पूर्ण_अगर
#पूर्ण_अगर

/* Maximum allocatable size */
#घोषणा KMALLOC_MAX_SIZE	(1UL << KMALLOC_SHIFT_MAX)
/* Maximum size क्रम which we actually use a slab cache */
#घोषणा KMALLOC_MAX_CACHE_SIZE	(1UL << KMALLOC_SHIFT_HIGH)
/* Maximum order allocatable via the slab allocator */
#घोषणा KMALLOC_MAX_ORDER	(KMALLOC_SHIFT_MAX - PAGE_SHIFT)

/*
 * Kदो_स्मृति subप्रणाली.
 */
#अगर_अघोषित KMALLOC_MIN_SIZE
#घोषणा KMALLOC_MIN_SIZE (1 << KMALLOC_SHIFT_LOW)
#पूर्ण_अगर

/*
 * This restriction comes from byte sized index implementation.
 * Page size is normally 2^12 bytes and, in this हाल, अगर we want to use
 * byte sized index which can represent 2^8 entries, the size of the object
 * should be equal or greater to 2^12 / 2^8 = 2^4 = 16.
 * If minimum size of kदो_स्मृति is less than 16, we use it as minimum object
 * size and give up to use byte sized index.
 */
#घोषणा SLAB_OBJ_MIN_SIZE      (KMALLOC_MIN_SIZE < 16 ? \
                               (KMALLOC_MIN_SIZE) : 16)

/*
 * Whenever changing this, take care of that kदो_स्मृति_type() and
 * create_kदो_स्मृति_caches() still work as पूर्णांकended.
 */
क्रमागत kदो_स्मृति_cache_type अणु
	KMALLOC_NORMAL = 0,
	KMALLOC_RECLAIM,
#अगर_घोषित CONFIG_ZONE_DMA
	KMALLOC_DMA,
#पूर्ण_अगर
	NR_KMALLOC_TYPES
पूर्ण;

#अगर_अघोषित CONFIG_SLOB
बाह्य काष्ठा kmem_cache *
kदो_स्मृति_caches[NR_KMALLOC_TYPES][KMALLOC_SHIFT_HIGH + 1];

अटल __always_अंतरभूत क्रमागत kदो_स्मृति_cache_type kदो_स्मृति_type(gfp_t flags)
अणु
#अगर_घोषित CONFIG_ZONE_DMA
	/*
	 * The most common हाल is KMALLOC_NORMAL, so test क्रम it
	 * with a single branch क्रम both flags.
	 */
	अगर (likely((flags & (__GFP_DMA | __GFP_RECLAIMABLE)) == 0))
		वापस KMALLOC_NORMAL;

	/*
	 * At least one of the flags has to be set. If both are, __GFP_DMA
	 * is more important.
	 */
	वापस flags & __GFP_DMA ? KMALLOC_DMA : KMALLOC_RECLAIM;
#अन्यथा
	वापस flags & __GFP_RECLAIMABLE ? KMALLOC_RECLAIM : KMALLOC_NORMAL;
#पूर्ण_अगर
पूर्ण

/*
 * Figure out which kदो_स्मृति slab an allocation of a certain size
 * beदीर्घs to.
 * 0 = zero alloc
 * 1 =  65 .. 96 bytes
 * 2 = 129 .. 192 bytes
 * n = 2^(n-1)+1 .. 2^n
 */
अटल __always_अंतरभूत अचिन्हित पूर्णांक kदो_स्मृति_index(माप_प्रकार size)
अणु
	अगर (!size)
		वापस 0;

	अगर (size <= KMALLOC_MIN_SIZE)
		वापस KMALLOC_SHIFT_LOW;

	अगर (KMALLOC_MIN_SIZE <= 32 && size > 64 && size <= 96)
		वापस 1;
	अगर (KMALLOC_MIN_SIZE <= 64 && size > 128 && size <= 192)
		वापस 2;
	अगर (size <=          8) वापस 3;
	अगर (size <=         16) वापस 4;
	अगर (size <=         32) वापस 5;
	अगर (size <=         64) वापस 6;
	अगर (size <=        128) वापस 7;
	अगर (size <=        256) वापस 8;
	अगर (size <=        512) वापस 9;
	अगर (size <=       1024) वापस 10;
	अगर (size <=   2 * 1024) वापस 11;
	अगर (size <=   4 * 1024) वापस 12;
	अगर (size <=   8 * 1024) वापस 13;
	अगर (size <=  16 * 1024) वापस 14;
	अगर (size <=  32 * 1024) वापस 15;
	अगर (size <=  64 * 1024) वापस 16;
	अगर (size <= 128 * 1024) वापस 17;
	अगर (size <= 256 * 1024) वापस 18;
	अगर (size <= 512 * 1024) वापस 19;
	अगर (size <= 1024 * 1024) वापस 20;
	अगर (size <=  2 * 1024 * 1024) वापस 21;
	अगर (size <=  4 * 1024 * 1024) वापस 22;
	अगर (size <=  8 * 1024 * 1024) वापस 23;
	अगर (size <=  16 * 1024 * 1024) वापस 24;
	अगर (size <=  32 * 1024 * 1024) वापस 25;
	अगर (size <=  64 * 1024 * 1024) वापस 26;
	BUG();

	/* Will never be reached. Needed because the compiler may complain */
	वापस -1;
पूर्ण
#पूर्ण_अगर /* !CONFIG_SLOB */

व्योम *__kदो_स्मृति(माप_प्रकार size, gfp_t flags) __assume_kदो_स्मृति_alignment __दो_स्मृति;
व्योम *kmem_cache_alloc(काष्ठा kmem_cache *, gfp_t flags) __assume_slab_alignment __दो_स्मृति;
व्योम kmem_cache_मुक्त(काष्ठा kmem_cache *, व्योम *);

/*
 * Bulk allocation and मुक्तing operations. These are accelerated in an
 * allocator specअगरic way to aव्योम taking locks repeatedly or building
 * metadata काष्ठाures unnecessarily.
 *
 * Note that पूर्णांकerrupts must be enabled when calling these functions.
 */
व्योम kmem_cache_मुक्त_bulk(काष्ठा kmem_cache *, माप_प्रकार, व्योम **);
पूर्णांक kmem_cache_alloc_bulk(काष्ठा kmem_cache *, gfp_t, माप_प्रकार, व्योम **);

/*
 * Caller must not use kमुक्त_bulk() on memory not originally allocated
 * by kदो_स्मृति(), because the SLOB allocator cannot handle this.
 */
अटल __always_अंतरभूत व्योम kमुक्त_bulk(माप_प्रकार size, व्योम **p)
अणु
	kmem_cache_मुक्त_bulk(शून्य, size, p);
पूर्ण

#अगर_घोषित CONFIG_NUMA
व्योम *__kदो_स्मृति_node(माप_प्रकार size, gfp_t flags, पूर्णांक node) __assume_kदो_स्मृति_alignment __दो_स्मृति;
व्योम *kmem_cache_alloc_node(काष्ठा kmem_cache *, gfp_t flags, पूर्णांक node) __assume_slab_alignment __दो_स्मृति;
#अन्यथा
अटल __always_अंतरभूत व्योम *__kदो_स्मृति_node(माप_प्रकार size, gfp_t flags, पूर्णांक node)
अणु
	वापस __kदो_स्मृति(size, flags);
पूर्ण

अटल __always_अंतरभूत व्योम *kmem_cache_alloc_node(काष्ठा kmem_cache *s, gfp_t flags, पूर्णांक node)
अणु
	वापस kmem_cache_alloc(s, flags);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRACING
बाह्य व्योम *kmem_cache_alloc_trace(काष्ठा kmem_cache *, gfp_t, माप_प्रकार) __assume_slab_alignment __दो_स्मृति;

#अगर_घोषित CONFIG_NUMA
बाह्य व्योम *kmem_cache_alloc_node_trace(काष्ठा kmem_cache *s,
					   gfp_t gfpflags,
					   पूर्णांक node, माप_प्रकार size) __assume_slab_alignment __दो_स्मृति;
#अन्यथा
अटल __always_अंतरभूत व्योम *
kmem_cache_alloc_node_trace(काष्ठा kmem_cache *s,
			      gfp_t gfpflags,
			      पूर्णांक node, माप_प्रकार size)
अणु
	वापस kmem_cache_alloc_trace(s, gfpflags, size);
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */

#अन्यथा /* CONFIG_TRACING */
अटल __always_अंतरभूत व्योम *kmem_cache_alloc_trace(काष्ठा kmem_cache *s,
		gfp_t flags, माप_प्रकार size)
अणु
	व्योम *ret = kmem_cache_alloc(s, flags);

	ret = kasan_kदो_स्मृति(s, ret, size, flags);
	वापस ret;
पूर्ण

अटल __always_अंतरभूत व्योम *
kmem_cache_alloc_node_trace(काष्ठा kmem_cache *s,
			      gfp_t gfpflags,
			      पूर्णांक node, माप_प्रकार size)
अणु
	व्योम *ret = kmem_cache_alloc_node(s, gfpflags, node);

	ret = kasan_kदो_स्मृति(s, ret, size, gfpflags);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRACING */

बाह्य व्योम *kदो_स्मृति_order(माप_प्रकार size, gfp_t flags, अचिन्हित पूर्णांक order) __assume_page_alignment __दो_स्मृति;

#अगर_घोषित CONFIG_TRACING
बाह्य व्योम *kदो_स्मृति_order_trace(माप_प्रकार size, gfp_t flags, अचिन्हित पूर्णांक order) __assume_page_alignment __दो_स्मृति;
#अन्यथा
अटल __always_अंतरभूत व्योम *
kदो_स्मृति_order_trace(माप_प्रकार size, gfp_t flags, अचिन्हित पूर्णांक order)
अणु
	वापस kदो_स्मृति_order(size, flags, order);
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम *kदो_स्मृति_large(माप_प्रकार size, gfp_t flags)
अणु
	अचिन्हित पूर्णांक order = get_order(size);
	वापस kदो_स्मृति_order_trace(size, flags, order);
पूर्ण

/**
 * kदो_स्मृति - allocate memory
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate.
 *
 * kदो_स्मृति is the normal method of allocating memory
 * क्रम objects smaller than page size in the kernel.
 *
 * The allocated object address is aligned to at least ARCH_KMALLOC_MINALIGN
 * bytes. For @size of घातer of two bytes, the alignment is also guaranteed
 * to be at least to the size.
 *
 * The @flags argument may be one of the GFP flags defined at
 * include/linux/gfp.h and described at
 * :ref:`Documentation/core-api/mm-api.rst <mm-api-gfp-flags>`
 *
 * The recommended usage of the @flags is described at
 * :ref:`Documentation/core-api/memory-allocation.rst <memory_allocation>`
 *
 * Below is a brief outline of the most useful GFP flags
 *
 * %GFP_KERNEL
 *	Allocate normal kernel ram. May sleep.
 *
 * %GFP_NOWAIT
 *	Allocation will not sleep.
 *
 * %GFP_ATOMIC
 *	Allocation will not sleep.  May use emergency pools.
 *
 * %GFP_HIGHUSER
 *	Allocate memory from high memory on behalf of user.
 *
 * Also it is possible to set dअगरferent flags by OR'ing
 * in one or more of the following additional @flags:
 *
 * %__GFP_HIGH
 *	This allocation has high priority and may use emergency pools.
 *
 * %__GFP_NOFAIL
 *	Indicate that this allocation is in no way allowed to fail
 *	(think twice beक्रमe using).
 *
 * %__GFP_NORETRY
 *	If memory is not immediately available,
 *	then give up at once.
 *
 * %__GFP_NOWARN
 *	If allocation fails, करोn't issue any warnings.
 *
 * %__GFP_RETRY_MAYFAIL
 *	Try really hard to succeed the allocation but fail
 *	eventually.
 */
अटल __always_अंतरभूत व्योम *kदो_स्मृति(माप_प्रकार size, gfp_t flags)
अणु
	अगर (__builtin_स्थिरant_p(size)) अणु
#अगर_अघोषित CONFIG_SLOB
		अचिन्हित पूर्णांक index;
#पूर्ण_अगर
		अगर (size > KMALLOC_MAX_CACHE_SIZE)
			वापस kदो_स्मृति_large(size, flags);
#अगर_अघोषित CONFIG_SLOB
		index = kदो_स्मृति_index(size);

		अगर (!index)
			वापस ZERO_SIZE_PTR;

		वापस kmem_cache_alloc_trace(
				kदो_स्मृति_caches[kदो_स्मृति_type(flags)][index],
				flags, size);
#पूर्ण_अगर
	पूर्ण
	वापस __kदो_स्मृति(size, flags);
पूर्ण

अटल __always_अंतरभूत व्योम *kदो_स्मृति_node(माप_प्रकार size, gfp_t flags, पूर्णांक node)
अणु
#अगर_अघोषित CONFIG_SLOB
	अगर (__builtin_स्थिरant_p(size) &&
		size <= KMALLOC_MAX_CACHE_SIZE) अणु
		अचिन्हित पूर्णांक i = kदो_स्मृति_index(size);

		अगर (!i)
			वापस ZERO_SIZE_PTR;

		वापस kmem_cache_alloc_node_trace(
				kदो_स्मृति_caches[kदो_स्मृति_type(flags)][i],
						flags, node, size);
	पूर्ण
#पूर्ण_अगर
	वापस __kदो_स्मृति_node(size, flags, node);
पूर्ण

/**
 * kदो_स्मृति_array - allocate memory क्रम an array.
 * @n: number of elements.
 * @size: element size.
 * @flags: the type of memory to allocate (see kदो_स्मृति).
 */
अटल अंतरभूत व्योम *kदो_स्मृति_array(माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	माप_प्रकार bytes;

	अगर (unlikely(check_mul_overflow(n, size, &bytes)))
		वापस शून्य;
	अगर (__builtin_स्थिरant_p(n) && __builtin_स्थिरant_p(size))
		वापस kदो_स्मृति(bytes, flags);
	वापस __kदो_स्मृति(bytes, flags);
पूर्ण

/**
 * kपुनः_स्मृति_array - पुनः_स्मृतिate memory क्रम an array.
 * @p: poपूर्णांकer to the memory chunk to पुनः_स्मृतिate
 * @new_n: new number of elements to alloc
 * @new_size: new size of a single member of the array
 * @flags: the type of memory to allocate (see kदो_स्मृति)
 */
अटल __must_check अंतरभूत व्योम *
kपुनः_स्मृति_array(व्योम *p, माप_प्रकार new_n, माप_प्रकार new_size, gfp_t flags)
अणु
	माप_प्रकार bytes;

	अगर (unlikely(check_mul_overflow(new_n, new_size, &bytes)))
		वापस शून्य;

	वापस kपुनः_स्मृति(p, bytes, flags);
पूर्ण

/**
 * kसुस्मृति - allocate memory क्रम an array. The memory is set to zero.
 * @n: number of elements.
 * @size: element size.
 * @flags: the type of memory to allocate (see kदो_स्मृति).
 */
अटल अंतरभूत व्योम *kसुस्मृति(माप_प्रकार n, माप_प्रकार size, gfp_t flags)
अणु
	वापस kदो_स्मृति_array(n, size, flags | __GFP_ZERO);
पूर्ण

/*
 * kदो_स्मृति_track_caller is a special version of kदो_स्मृति that records the
 * calling function of the routine calling it क्रम slab leak tracking instead
 * of just the calling function (confusing, eh?).
 * It's useful when the call to kदो_स्मृति comes from a widely-used standard
 * allocator where we care about the real place the memory allocation
 * request comes from.
 */
बाह्य व्योम *__kदो_स्मृति_track_caller(माप_प्रकार, gfp_t, अचिन्हित दीर्घ);
#घोषणा kदो_स्मृति_track_caller(size, flags) \
	__kदो_स्मृति_track_caller(size, flags, _RET_IP_)

अटल अंतरभूत व्योम *kदो_स्मृति_array_node(माप_प्रकार n, माप_प्रकार size, gfp_t flags,
				       पूर्णांक node)
अणु
	माप_प्रकार bytes;

	अगर (unlikely(check_mul_overflow(n, size, &bytes)))
		वापस शून्य;
	अगर (__builtin_स्थिरant_p(n) && __builtin_स्थिरant_p(size))
		वापस kदो_स्मृति_node(bytes, flags, node);
	वापस __kदो_स्मृति_node(bytes, flags, node);
पूर्ण

अटल अंतरभूत व्योम *kसुस्मृति_node(माप_प्रकार n, माप_प्रकार size, gfp_t flags, पूर्णांक node)
अणु
	वापस kदो_स्मृति_array_node(n, size, flags | __GFP_ZERO, node);
पूर्ण


#अगर_घोषित CONFIG_NUMA
बाह्य व्योम *__kदो_स्मृति_node_track_caller(माप_प्रकार, gfp_t, पूर्णांक, अचिन्हित दीर्घ);
#घोषणा kदो_स्मृति_node_track_caller(size, flags, node) \
	__kदो_स्मृति_node_track_caller(size, flags, node, \
			_RET_IP_)

#अन्यथा /* CONFIG_NUMA */

#घोषणा kदो_स्मृति_node_track_caller(size, flags, node) \
	kदो_स्मृति_track_caller(size, flags)

#पूर्ण_अगर /* CONFIG_NUMA */

/*
 * Shortcuts
 */
अटल अंतरभूत व्योम *kmem_cache_zalloc(काष्ठा kmem_cache *k, gfp_t flags)
अणु
	वापस kmem_cache_alloc(k, flags | __GFP_ZERO);
पूर्ण

/**
 * kzalloc - allocate memory. The memory is set to zero.
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate (see kदो_स्मृति).
 */
अटल अंतरभूत व्योम *kzalloc(माप_प्रकार size, gfp_t flags)
अणु
	वापस kदो_स्मृति(size, flags | __GFP_ZERO);
पूर्ण

/**
 * kzalloc_node - allocate zeroed memory from a particular memory node.
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate (see kदो_स्मृति).
 * @node: memory node from which to allocate
 */
अटल अंतरभूत व्योम *kzalloc_node(माप_प्रकार size, gfp_t flags, पूर्णांक node)
अणु
	वापस kदो_स्मृति_node(size, flags | __GFP_ZERO, node);
पूर्ण

अचिन्हित पूर्णांक kmem_cache_size(काष्ठा kmem_cache *s);
व्योम __init kmem_cache_init_late(व्योम);

#अगर defined(CONFIG_SMP) && defined(CONFIG_SLAB)
पूर्णांक slab_prepare_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक slab_dead_cpu(अचिन्हित पूर्णांक cpu);
#अन्यथा
#घोषणा slab_prepare_cpu	शून्य
#घोषणा slab_dead_cpu		शून्य
#पूर्ण_अगर

#पूर्ण_अगर	/* _LINUX_SLAB_H */
