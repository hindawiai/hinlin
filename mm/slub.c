<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SLUB: A slab allocator that limits cache line use instead of queuing
 * objects in per cpu and per node lists.
 *
 * The allocator synchronizes using per slab locks or atomic operations
 * and only uses a centralized lock to manage a pool of partial sद_असल.
 *
 * (C) 2007 SGI, Christoph Lameter
 * (C) 2011 Linux Foundation, Christoph Lameter
 */

#समावेश <linux/mm.h>
#समावेश <linux/swap.h> /* काष्ठा reclaim_state */
#समावेश <linux/module.h>
#समावेश <linux/bit_spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/swab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश "slab.h"
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kasan.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugobjects.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kfence.h>
#समावेश <linux/memory.h>
#समावेश <linux/math64.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/अक्रमom.h>

#समावेश <trace/events/kस्मृति.स>

#समावेश "internal.h"

/*
 * Lock order:
 *   1. slab_mutex (Global Mutex)
 *   2. node->list_lock
 *   3. slab_lock(page) (Only on some arches and क्रम debugging)
 *
 *   slab_mutex
 *
 *   The role of the slab_mutex is to protect the list of all the sद_असल
 *   and to synchronize major metadata changes to slab cache काष्ठाures.
 *
 *   The slab_lock is only used क्रम debugging and on arches that करो not
 *   have the ability to करो a cmpxchg_द्विगुन. It only protects:
 *	A. page->मुक्तlist	-> List of object मुक्त in a page
 *	B. page->inuse		-> Number of objects in use
 *	C. page->objects	-> Number of objects in page
 *	D. page->frozen		-> frozen state
 *
 *   If a slab is frozen then it is exempt from list management. It is not
 *   on any list except per cpu partial list. The processor that froze the
 *   slab is the one who can perक्रमm list operations on the page. Other
 *   processors may put objects onto the मुक्तlist but the processor that
 *   froze the slab is the only one that can retrieve the objects from the
 *   page's मुक्तlist.
 *
 *   The list_lock protects the partial and full list on each node and
 *   the partial slab counter. If taken then no new sद_असल may be added or
 *   हटाओd from the lists nor make the number of partial sद_असल be modअगरied.
 *   (Note that the total number of sद_असल is an atomic value that may be
 *   modअगरied without taking the list lock).
 *
 *   The list_lock is a centralized lock and thus we aव्योम taking it as
 *   much as possible. As दीर्घ as SLUB करोes not have to handle partial
 *   sद_असल, operations can जारी without any centralized lock. F.e.
 *   allocating a दीर्घ series of objects that fill up sद_असल करोes not require
 *   the list lock.
 *   Interrupts are disabled during allocation and deallocation in order to
 *   make the slab allocator safe to use in the context of an irq. In addition
 *   पूर्णांकerrupts are disabled to ensure that the processor करोes not change
 *   जबतक handling per_cpu sद_असल, due to kernel preemption.
 *
 * SLUB assigns one slab क्रम allocation to each processor.
 * Allocations only occur from these sद_असल called cpu sद_असल.
 *
 * Sद_असल with मुक्त elements are kept on a partial list and during regular
 * operations no list क्रम full sद_असल is used. If an object in a full slab is
 * मुक्तd then the slab will show up again on the partial lists.
 * We track full sद_असल क्रम debugging purposes though because otherwise we
 * cannot scan all objects.
 *
 * Sद_असल are मुक्तd when they become empty. Tearकरोwn and setup is
 * minimal so we rely on the page allocators per cpu caches क्रम
 * fast मुक्तs and allocs.
 *
 * page->frozen		The slab is frozen and exempt from list processing.
 * 			This means that the slab is dedicated to a purpose
 * 			such as satisfying allocations क्रम a specअगरic
 * 			processor. Objects may be मुक्तd in the slab जबतक
 * 			it is frozen but slab_मुक्त will then skip the usual
 * 			list operations. It is up to the processor holding
 * 			the slab to पूर्णांकegrate the slab पूर्णांकo the slab lists
 * 			when the slab is no दीर्घer needed.
 *
 * 			One use of this flag is to mark sद_असल that are
 * 			used क्रम allocations. Then such a slab becomes a cpu
 * 			slab. The cpu slab may be equipped with an additional
 * 			मुक्तlist that allows lockless access to
 * 			मुक्त objects in addition to the regular मुक्तlist
 * 			that requires the slab lock.
 *
 * SLAB_DEBUG_FLAGS	Slab requires special handling due to debug
 * 			options set. This moves	slab handling out of
 * 			the fast path and disables lockless मुक्तlists.
 */

#अगर_घोषित CONFIG_SLUB_DEBUG
#अगर_घोषित CONFIG_SLUB_DEBUG_ON
DEFINE_STATIC_KEY_TRUE(slub_debug_enabled);
#अन्यथा
DEFINE_STATIC_KEY_FALSE(slub_debug_enabled);
#पूर्ण_अगर
#पूर्ण_अगर

अटल अंतरभूत bool kmem_cache_debug(काष्ठा kmem_cache *s)
अणु
	वापस kmem_cache_debug_flags(s, SLAB_DEBUG_FLAGS);
पूर्ण

व्योम *fixup_red_left(काष्ठा kmem_cache *s, व्योम *p)
अणु
	अगर (kmem_cache_debug_flags(s, SLAB_RED_ZONE))
		p += s->red_left_pad;

	वापस p;
पूर्ण

अटल अंतरभूत bool kmem_cache_has_cpu_partial(काष्ठा kmem_cache *s)
अणु
#अगर_घोषित CONFIG_SLUB_CPU_PARTIAL
	वापस !kmem_cache_debug(s);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/*
 * Issues still to be resolved:
 *
 * - Support PAGE_ALLOC_DEBUG. Should be easy to करो.
 *
 * - Variable sizing of the per node arrays
 */

/* Enable to test recovery from slab corruption on boot */
#अघोषित SLUB_RESILIENCY_TEST

/* Enable to log cmpxchg failures */
#अघोषित SLUB_DEBUG_CMPXCHG

/*
 * Minimum number of partial sद_असल. These will be left on the partial
 * lists even अगर they are empty. kmem_cache_shrink may reclaim them.
 */
#घोषणा MIN_PARTIAL 5

/*
 * Maximum number of desirable partial sद_असल.
 * The existence of more partial sद_असल makes kmem_cache_shrink
 * sort the partial list by the number of objects in use.
 */
#घोषणा MAX_PARTIAL 10

#घोषणा DEBUG_DEFAULT_FLAGS (SLAB_CONSISTENCY_CHECKS | SLAB_RED_ZONE | \
				SLAB_POISON | SLAB_STORE_USER)

/*
 * These debug flags cannot use CMPXCHG because there might be consistency
 * issues when checking or पढ़ोing debug inक्रमmation
 */
#घोषणा SLAB_NO_CMPXCHG (SLAB_CONSISTENCY_CHECKS | SLAB_STORE_USER | \
				SLAB_TRACE)


/*
 * Debugging flags that require metadata to be stored in the slab.  These get
 * disabled when slub_debug=O is used and a cache's min order increases with
 * metadata.
 */
#घोषणा DEBUG_METADATA_FLAGS (SLAB_RED_ZONE | SLAB_POISON | SLAB_STORE_USER)

#घोषणा OO_SHIFT	16
#घोषणा OO_MASK		((1 << OO_SHIFT) - 1)
#घोषणा MAX_OBJS_PER_PAGE	32767 /* since page.objects is u15 */

/* Internal SLUB flags */
/* Poison object */
#घोषणा __OBJECT_POISON		((slab_flags_t __क्रमce)0x80000000U)
/* Use cmpxchg_द्विगुन */
#घोषणा __CMPXCHG_DOUBLE	((slab_flags_t __क्रमce)0x40000000U)

/*
 * Tracking user of a slab.
 */
#घोषणा TRACK_ADDRS_COUNT 16
काष्ठा track अणु
	अचिन्हित दीर्घ addr;	/* Called from address */
#अगर_घोषित CONFIG_STACKTRACE
	अचिन्हित दीर्घ addrs[TRACK_ADDRS_COUNT];	/* Called from address */
#पूर्ण_अगर
	पूर्णांक cpu;		/* Was running on cpu */
	पूर्णांक pid;		/* Pid context */
	अचिन्हित दीर्घ when;	/* When did the operation occur */
पूर्ण;

क्रमागत track_item अणु TRACK_ALLOC, TRACK_FREE पूर्ण;

#अगर_घोषित CONFIG_SYSFS
अटल पूर्णांक sysfs_slab_add(काष्ठा kmem_cache *);
अटल पूर्णांक sysfs_slab_alias(काष्ठा kmem_cache *, स्थिर अक्षर *);
#अन्यथा
अटल अंतरभूत पूर्णांक sysfs_slab_add(काष्ठा kmem_cache *s) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक sysfs_slab_alias(काष्ठा kmem_cache *s, स्थिर अक्षर *p)
							अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम stat(स्थिर काष्ठा kmem_cache *s, क्रमागत stat_item si)
अणु
#अगर_घोषित CONFIG_SLUB_STATS
	/*
	 * The rmw is racy on a preemptible kernel but this is acceptable, so
	 * aव्योम this_cpu_add()'s irq-disable overhead.
	 */
	raw_cpu_inc(s->cpu_slab->stat[si]);
#पूर्ण_अगर
पूर्ण

/*
 * Tracks क्रम which NUMA nodes we have kmem_cache_nodes allocated.
 * Corresponds to node_state[N_NORMAL_MEMORY], but can temporarily
 * dअगरfer during memory hotplug/hotहटाओ operations.
 * Protected by slab_mutex.
 */
अटल nodemask_t slab_nodes;

/********************************************************************
 * 			Core slab cache functions
 *******************************************************************/

/*
 * Returns मुक्तlist poपूर्णांकer (ptr). With hardening, this is obfuscated
 * with an XOR of the address where the poपूर्णांकer is held and a per-cache
 * अक्रमom number.
 */
अटल अंतरभूत व्योम *मुक्तlist_ptr(स्थिर काष्ठा kmem_cache *s, व्योम *ptr,
				 अचिन्हित दीर्घ ptr_addr)
अणु
#अगर_घोषित CONFIG_SLAB_FREELIST_HARDENED
	/*
	 * When CONFIG_KASAN_SW/HW_TAGS is enabled, ptr_addr might be tagged.
	 * Normally, this करोesn't cause any issues, as both set_मुक्तpoपूर्णांकer()
	 * and get_मुक्तpoपूर्णांकer() are called with a poपूर्णांकer with the same tag.
	 * However, there are some issues with CONFIG_SLUB_DEBUG code. For
	 * example, when __मुक्त_slub() iterates over objects in a cache, it
	 * passes untagged poपूर्णांकers to check_object(). check_object() in turns
	 * calls get_मुक्तpoपूर्णांकer() with an untagged poपूर्णांकer, which causes the
	 * मुक्तpoपूर्णांकer to be restored incorrectly.
	 */
	वापस (व्योम *)((अचिन्हित दीर्घ)ptr ^ s->अक्रमom ^
			swab((अचिन्हित दीर्घ)kasan_reset_tag((व्योम *)ptr_addr)));
#अन्यथा
	वापस ptr;
#पूर्ण_अगर
पूर्ण

/* Returns the मुक्तlist poपूर्णांकer recorded at location ptr_addr. */
अटल अंतरभूत व्योम *मुक्तlist_dereference(स्थिर काष्ठा kmem_cache *s,
					 व्योम *ptr_addr)
अणु
	वापस मुक्तlist_ptr(s, (व्योम *)*(अचिन्हित दीर्घ *)(ptr_addr),
			    (अचिन्हित दीर्घ)ptr_addr);
पूर्ण

अटल अंतरभूत व्योम *get_मुक्तpoपूर्णांकer(काष्ठा kmem_cache *s, व्योम *object)
अणु
	object = kasan_reset_tag(object);
	वापस मुक्तlist_dereference(s, object + s->offset);
पूर्ण

अटल व्योम prefetch_मुक्तpoपूर्णांकer(स्थिर काष्ठा kmem_cache *s, व्योम *object)
अणु
	prefetch(object + s->offset);
पूर्ण

अटल अंतरभूत व्योम *get_मुक्तpoपूर्णांकer_safe(काष्ठा kmem_cache *s, व्योम *object)
अणु
	अचिन्हित दीर्घ मुक्तpoपूर्णांकer_addr;
	व्योम *p;

	अगर (!debug_pagealloc_enabled_अटल())
		वापस get_मुक्तpoपूर्णांकer(s, object);

	object = kasan_reset_tag(object);
	मुक्तpoपूर्णांकer_addr = (अचिन्हित दीर्घ)object + s->offset;
	copy_from_kernel_nofault(&p, (व्योम **)मुक्तpoपूर्णांकer_addr, माप(p));
	वापस मुक्तlist_ptr(s, p, मुक्तpoपूर्णांकer_addr);
पूर्ण

अटल अंतरभूत व्योम set_मुक्तpoपूर्णांकer(काष्ठा kmem_cache *s, व्योम *object, व्योम *fp)
अणु
	अचिन्हित दीर्घ मुक्तptr_addr = (अचिन्हित दीर्घ)object + s->offset;

#अगर_घोषित CONFIG_SLAB_FREELIST_HARDENED
	BUG_ON(object == fp); /* naive detection of द्विगुन मुक्त or corruption */
#पूर्ण_अगर

	मुक्तptr_addr = (अचिन्हित दीर्घ)kasan_reset_tag((व्योम *)मुक्तptr_addr);
	*(व्योम **)मुक्तptr_addr = मुक्तlist_ptr(s, fp, मुक्तptr_addr);
पूर्ण

/* Loop over all objects in a slab */
#घोषणा क्रम_each_object(__p, __s, __addr, __objects) \
	क्रम (__p = fixup_red_left(__s, __addr); \
		__p < (__addr) + (__objects) * (__s)->size; \
		__p += (__s)->size)

अटल अंतरभूत अचिन्हित पूर्णांक order_objects(अचिन्हित पूर्णांक order, अचिन्हित पूर्णांक size)
अणु
	वापस ((अचिन्हित पूर्णांक)PAGE_SIZE << order) / size;
पूर्ण

अटल अंतरभूत काष्ठा kmem_cache_order_objects oo_make(अचिन्हित पूर्णांक order,
		अचिन्हित पूर्णांक size)
अणु
	काष्ठा kmem_cache_order_objects x = अणु
		(order << OO_SHIFT) + order_objects(order, size)
	पूर्ण;

	वापस x;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक oo_order(काष्ठा kmem_cache_order_objects x)
अणु
	वापस x.x >> OO_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक oo_objects(काष्ठा kmem_cache_order_objects x)
अणु
	वापस x.x & OO_MASK;
पूर्ण

/*
 * Per slab locking using the pagelock
 */
अटल __always_अंतरभूत व्योम slab_lock(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(PageTail(page), page);
	bit_spin_lock(PG_locked, &page->flags);
पूर्ण

अटल __always_अंतरभूत व्योम slab_unlock(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(PageTail(page), page);
	__bit_spin_unlock(PG_locked, &page->flags);
पूर्ण

/* Interrupts must be disabled (क्रम the fallback code to work right) */
अटल अंतरभूत bool __cmpxchg_द्विगुन_slab(काष्ठा kmem_cache *s, काष्ठा page *page,
		व्योम *मुक्तlist_old, अचिन्हित दीर्घ counters_old,
		व्योम *मुक्तlist_new, अचिन्हित दीर्घ counters_new,
		स्थिर अक्षर *n)
अणु
	VM_BUG_ON(!irqs_disabled());
#अगर defined(CONFIG_HAVE_CMPXCHG_DOUBLE) && \
    defined(CONFIG_HAVE_ALIGNED_STRUCT_PAGE)
	अगर (s->flags & __CMPXCHG_DOUBLE) अणु
		अगर (cmpxchg_द्विगुन(&page->मुक्तlist, &page->counters,
				   मुक्तlist_old, counters_old,
				   मुक्तlist_new, counters_new))
			वापस true;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		slab_lock(page);
		अगर (page->मुक्तlist == मुक्तlist_old &&
					page->counters == counters_old) अणु
			page->मुक्तlist = मुक्तlist_new;
			page->counters = counters_new;
			slab_unlock(page);
			वापस true;
		पूर्ण
		slab_unlock(page);
	पूर्ण

	cpu_relax();
	stat(s, CMPXCHG_DOUBLE_FAIL);

#अगर_घोषित SLUB_DEBUG_CMPXCHG
	pr_info("%s %s: cmpxchg double redo ", n, s->name);
#पूर्ण_अगर

	वापस false;
पूर्ण

अटल अंतरभूत bool cmpxchg_द्विगुन_slab(काष्ठा kmem_cache *s, काष्ठा page *page,
		व्योम *मुक्तlist_old, अचिन्हित दीर्घ counters_old,
		व्योम *मुक्तlist_new, अचिन्हित दीर्घ counters_new,
		स्थिर अक्षर *n)
अणु
#अगर defined(CONFIG_HAVE_CMPXCHG_DOUBLE) && \
    defined(CONFIG_HAVE_ALIGNED_STRUCT_PAGE)
	अगर (s->flags & __CMPXCHG_DOUBLE) अणु
		अगर (cmpxchg_द्विगुन(&page->मुक्तlist, &page->counters,
				   मुक्तlist_old, counters_old,
				   मुक्तlist_new, counters_new))
			वापस true;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		slab_lock(page);
		अगर (page->मुक्तlist == मुक्तlist_old &&
					page->counters == counters_old) अणु
			page->मुक्तlist = मुक्तlist_new;
			page->counters = counters_new;
			slab_unlock(page);
			local_irq_restore(flags);
			वापस true;
		पूर्ण
		slab_unlock(page);
		local_irq_restore(flags);
	पूर्ण

	cpu_relax();
	stat(s, CMPXCHG_DOUBLE_FAIL);

#अगर_घोषित SLUB_DEBUG_CMPXCHG
	pr_info("%s %s: cmpxchg double redo ", n, s->name);
#पूर्ण_अगर

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_SLUB_DEBUG
अटल अचिन्हित दीर्घ object_map[BITS_TO_LONGS(MAX_OBJS_PER_PAGE)];
अटल DEFINE_SPINLOCK(object_map_lock);

/*
 * Determine a map of object in use on a page.
 *
 * Node listlock must be held to guarantee that the page करोes
 * not vanish from under us.
 */
अटल अचिन्हित दीर्घ *get_map(काष्ठा kmem_cache *s, काष्ठा page *page)
	__acquires(&object_map_lock)
अणु
	व्योम *p;
	व्योम *addr = page_address(page);

	VM_BUG_ON(!irqs_disabled());

	spin_lock(&object_map_lock);

	biपंचांगap_zero(object_map, page->objects);

	क्रम (p = page->मुक्तlist; p; p = get_मुक्तpoपूर्णांकer(s, p))
		set_bit(__obj_to_index(s, addr, p), object_map);

	वापस object_map;
पूर्ण

अटल व्योम put_map(अचिन्हित दीर्घ *map) __releases(&object_map_lock)
अणु
	VM_BUG_ON(map != object_map);
	spin_unlock(&object_map_lock);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक size_from_object(काष्ठा kmem_cache *s)
अणु
	अगर (s->flags & SLAB_RED_ZONE)
		वापस s->size - s->red_left_pad;

	वापस s->size;
पूर्ण

अटल अंतरभूत व्योम *restore_red_left(काष्ठा kmem_cache *s, व्योम *p)
अणु
	अगर (s->flags & SLAB_RED_ZONE)
		p -= s->red_left_pad;

	वापस p;
पूर्ण

/*
 * Debug settings:
 */
#अगर defined(CONFIG_SLUB_DEBUG_ON)
अटल slab_flags_t slub_debug = DEBUG_DEFAULT_FLAGS;
#अन्यथा
अटल slab_flags_t slub_debug;
#पूर्ण_अगर

अटल अक्षर *slub_debug_string;
अटल पूर्णांक disable_higher_order_debug;

/*
 * slub is about to manipulate पूर्णांकernal object metadata.  This memory lies
 * outside the range of the allocated object, so accessing it would normally
 * be reported by kasan as a bounds error.  metadata_access_enable() is used
 * to tell kasan that these accesses are OK.
 */
अटल अंतरभूत व्योम metadata_access_enable(व्योम)
अणु
	kasan_disable_current();
पूर्ण

अटल अंतरभूत व्योम metadata_access_disable(व्योम)
अणु
	kasan_enable_current();
पूर्ण

/*
 * Object debugging
 */

/* Verअगरy that a poपूर्णांकer has an address that is valid within a slab page */
अटल अंतरभूत पूर्णांक check_valid_poपूर्णांकer(काष्ठा kmem_cache *s,
				काष्ठा page *page, व्योम *object)
अणु
	व्योम *base;

	अगर (!object)
		वापस 1;

	base = page_address(page);
	object = kasan_reset_tag(object);
	object = restore_red_left(s, object);
	अगर (object < base || object >= base + page->objects * s->size ||
		(object - base) % s->size) अणु
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम prपूर्णांक_section(अक्षर *level, अक्षर *text, u8 *addr,
			  अचिन्हित पूर्णांक length)
अणु
	metadata_access_enable();
	prपूर्णांक_hex_dump(level, kasan_reset_tag(text), DUMP_PREFIX_ADDRESS,
			16, 1, addr, length, 1);
	metadata_access_disable();
पूर्ण

/*
 * See comment in calculate_sizes().
 */
अटल अंतरभूत bool मुक्तptr_outside_object(काष्ठा kmem_cache *s)
अणु
	वापस s->offset >= s->inuse;
पूर्ण

/*
 * Return offset of the end of info block which is inuse + मुक्त poपूर्णांकer अगर
 * not overlapping with object.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_info_end(काष्ठा kmem_cache *s)
अणु
	अगर (मुक्तptr_outside_object(s))
		वापस s->inuse + माप(व्योम *);
	अन्यथा
		वापस s->inuse;
पूर्ण

अटल काष्ठा track *get_track(काष्ठा kmem_cache *s, व्योम *object,
	क्रमागत track_item alloc)
अणु
	काष्ठा track *p;

	p = object + get_info_end(s);

	वापस kasan_reset_tag(p + alloc);
पूर्ण

अटल व्योम set_track(काष्ठा kmem_cache *s, व्योम *object,
			क्रमागत track_item alloc, अचिन्हित दीर्घ addr)
अणु
	काष्ठा track *p = get_track(s, object, alloc);

	अगर (addr) अणु
#अगर_घोषित CONFIG_STACKTRACE
		अचिन्हित पूर्णांक nr_entries;

		metadata_access_enable();
		nr_entries = stack_trace_save(kasan_reset_tag(p->addrs),
					      TRACK_ADDRS_COUNT, 3);
		metadata_access_disable();

		अगर (nr_entries < TRACK_ADDRS_COUNT)
			p->addrs[nr_entries] = 0;
#पूर्ण_अगर
		p->addr = addr;
		p->cpu = smp_processor_id();
		p->pid = current->pid;
		p->when = jअगरfies;
	पूर्ण अन्यथा अणु
		स_रखो(p, 0, माप(काष्ठा track));
	पूर्ण
पूर्ण

अटल व्योम init_tracking(काष्ठा kmem_cache *s, व्योम *object)
अणु
	अगर (!(s->flags & SLAB_STORE_USER))
		वापस;

	set_track(s, object, TRACK_FREE, 0UL);
	set_track(s, object, TRACK_ALLOC, 0UL);
पूर्ण

अटल व्योम prपूर्णांक_track(स्थिर अक्षर *s, काष्ठा track *t, अचिन्हित दीर्घ pr_समय)
अणु
	अगर (!t->addr)
		वापस;

	pr_err("%s in %pS age=%lu cpu=%u pid=%d\n",
	       s, (व्योम *)t->addr, pr_समय - t->when, t->cpu, t->pid);
#अगर_घोषित CONFIG_STACKTRACE
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < TRACK_ADDRS_COUNT; i++)
			अगर (t->addrs[i])
				pr_err("\t%pS\n", (व्योम *)t->addrs[i]);
			अन्यथा
				अवरोध;
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम prपूर्णांक_tracking(काष्ठा kmem_cache *s, व्योम *object)
अणु
	अचिन्हित दीर्घ pr_समय = jअगरfies;
	अगर (!(s->flags & SLAB_STORE_USER))
		वापस;

	prपूर्णांक_track("Allocated", get_track(s, object, TRACK_ALLOC), pr_समय);
	prपूर्णांक_track("Freed", get_track(s, object, TRACK_FREE), pr_समय);
पूर्ण

अटल व्योम prपूर्णांक_page_info(काष्ठा page *page)
अणु
	pr_err("Slab 0x%p objects=%u used=%u fp=0x%p flags=%#lx(%pGp)\n",
	       page, page->objects, page->inuse, page->मुक्तlist,
	       page->flags, &page->flags);

पूर्ण

अटल व्योम slab_bug(काष्ठा kmem_cache *s, अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_err("=============================================================================\n");
	pr_err("BUG %s (%s): %pV\n", s->name, prपूर्णांक_taपूर्णांकed(), &vaf);
	pr_err("-----------------------------------------------------------------------------\n\n");

	add_taपूर्णांक(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);
	बहु_पूर्ण(args);
पूर्ण

अटल व्योम slab_fix(काष्ठा kmem_cache *s, अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_err("FIX %s: %pV\n", s->name, &vaf);
	बहु_पूर्ण(args);
पूर्ण

अटल bool मुक्तlist_corrupted(काष्ठा kmem_cache *s, काष्ठा page *page,
			       व्योम **मुक्तlist, व्योम *nextमुक्त)
अणु
	अगर ((s->flags & SLAB_CONSISTENCY_CHECKS) &&
	    !check_valid_poपूर्णांकer(s, page, nextमुक्त) && मुक्तlist) अणु
		object_err(s, page, *मुक्तlist, "Freechain corrupt");
		*मुक्तlist = शून्य;
		slab_fix(s, "Isolate corrupted freechain");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम prपूर्णांक_trailer(काष्ठा kmem_cache *s, काष्ठा page *page, u8 *p)
अणु
	अचिन्हित पूर्णांक off;	/* Offset of last byte */
	u8 *addr = page_address(page);

	prपूर्णांक_tracking(s, p);

	prपूर्णांक_page_info(page);

	pr_err("Object 0x%p @offset=%tu fp=0x%p\n\n",
	       p, p - addr, get_मुक्तpoपूर्णांकer(s, p));

	अगर (s->flags & SLAB_RED_ZONE)
		prपूर्णांक_section(KERN_ERR, "Redzone  ", p - s->red_left_pad,
			      s->red_left_pad);
	अन्यथा अगर (p > addr + 16)
		prपूर्णांक_section(KERN_ERR, "Bytes b4 ", p - 16, 16);

	prपूर्णांक_section(KERN_ERR,         "Object   ", p,
		      min_t(अचिन्हित पूर्णांक, s->object_size, PAGE_SIZE));
	अगर (s->flags & SLAB_RED_ZONE)
		prपूर्णांक_section(KERN_ERR, "Redzone  ", p + s->object_size,
			s->inuse - s->object_size);

	off = get_info_end(s);

	अगर (s->flags & SLAB_STORE_USER)
		off += 2 * माप(काष्ठा track);

	off += kasan_metadata_size(s);

	अगर (off != size_from_object(s))
		/* Beginning of the filler is the मुक्त poपूर्णांकer */
		prपूर्णांक_section(KERN_ERR, "Padding  ", p + off,
			      size_from_object(s) - off);

	dump_stack();
पूर्ण

व्योम object_err(काष्ठा kmem_cache *s, काष्ठा page *page,
			u8 *object, अक्षर *reason)
अणु
	slab_bug(s, "%s", reason);
	prपूर्णांक_trailer(s, page, object);
पूर्ण

अटल __म_लिखो(3, 4) व्योम slab_err(काष्ठा kmem_cache *s, काष्ठा page *page,
			स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[100];

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);
	slab_bug(s, "%s", buf);
	prपूर्णांक_page_info(page);
	dump_stack();
पूर्ण

अटल व्योम init_object(काष्ठा kmem_cache *s, व्योम *object, u8 val)
अणु
	u8 *p = kasan_reset_tag(object);

	अगर (s->flags & SLAB_RED_ZONE)
		स_रखो(p - s->red_left_pad, val, s->red_left_pad);

	अगर (s->flags & __OBJECT_POISON) अणु
		स_रखो(p, POISON_FREE, s->object_size - 1);
		p[s->object_size - 1] = POISON_END;
	पूर्ण

	अगर (s->flags & SLAB_RED_ZONE)
		स_रखो(p + s->object_size, val, s->inuse - s->object_size);
पूर्ण

अटल व्योम restore_bytes(काष्ठा kmem_cache *s, अक्षर *message, u8 data,
						व्योम *from, व्योम *to)
अणु
	slab_fix(s, "Restoring 0x%p-0x%p=0x%x\n", from, to - 1, data);
	स_रखो(from, data, to - from);
पूर्ण

अटल पूर्णांक check_bytes_and_report(काष्ठा kmem_cache *s, काष्ठा page *page,
			u8 *object, अक्षर *what,
			u8 *start, अचिन्हित पूर्णांक value, अचिन्हित पूर्णांक bytes)
अणु
	u8 *fault;
	u8 *end;
	u8 *addr = page_address(page);

	metadata_access_enable();
	fault = स_प्रथम_inv(kasan_reset_tag(start), value, bytes);
	metadata_access_disable();
	अगर (!fault)
		वापस 1;

	end = start + bytes;
	जबतक (end > fault && end[-1] == value)
		end--;

	slab_bug(s, "%s overwritten", what);
	pr_err("0x%p-0x%p @offset=%tu. First byte 0x%x instead of 0x%x\n",
					fault, end - 1, fault - addr,
					fault[0], value);
	prपूर्णांक_trailer(s, page, object);

	restore_bytes(s, what, value, fault, end);
	वापस 0;
पूर्ण

/*
 * Object layout:
 *
 * object address
 * 	Bytes of the object to be managed.
 * 	If the मुक्तpoपूर्णांकer may overlay the object then the मुक्त
 *	poपूर्णांकer is at the middle of the object.
 *
 * 	Poisoning uses 0x6b (POISON_FREE) and the last byte is
 * 	0xa5 (POISON_END)
 *
 * object + s->object_size
 * 	Padding to reach word boundary. This is also used क्रम Redzoning.
 * 	Padding is extended by another word अगर Redzoning is enabled and
 * 	object_size == inuse.
 *
 * 	We fill with 0xbb (RED_INACTIVE) क्रम inactive objects and with
 * 	0xcc (RED_ACTIVE) क्रम objects in use.
 *
 * object + s->inuse
 * 	Meta data starts here.
 *
 * 	A. Free poपूर्णांकer (अगर we cannot overग_लिखो object on मुक्त)
 * 	B. Tracking data क्रम SLAB_STORE_USER
 *	C. Padding to reach required alignment boundary or at minimum
 * 		one word अगर debugging is on to be able to detect ग_लिखोs
 * 		beक्रमe the word boundary.
 *
 *	Padding is करोne using 0x5a (POISON_INUSE)
 *
 * object + s->size
 * 	Nothing is used beyond s->size.
 *
 * If slabcaches are merged then the object_size and inuse boundaries are mostly
 * ignored. And thereक्रमe no slab options that rely on these boundaries
 * may be used with merged slabcaches.
 */

अटल पूर्णांक check_pad_bytes(काष्ठा kmem_cache *s, काष्ठा page *page, u8 *p)
अणु
	अचिन्हित दीर्घ off = get_info_end(s);	/* The end of info */

	अगर (s->flags & SLAB_STORE_USER)
		/* We also have user inक्रमmation there */
		off += 2 * माप(काष्ठा track);

	off += kasan_metadata_size(s);

	अगर (size_from_object(s) == off)
		वापस 1;

	वापस check_bytes_and_report(s, page, p, "Object padding",
			p + off, POISON_INUSE, size_from_object(s) - off);
पूर्ण

/* Check the pad bytes at the end of a slab page */
अटल पूर्णांक slab_pad_check(काष्ठा kmem_cache *s, काष्ठा page *page)
अणु
	u8 *start;
	u8 *fault;
	u8 *end;
	u8 *pad;
	पूर्णांक length;
	पूर्णांक reमुख्यder;

	अगर (!(s->flags & SLAB_POISON))
		वापस 1;

	start = page_address(page);
	length = page_size(page);
	end = start + length;
	reमुख्यder = length % s->size;
	अगर (!reमुख्यder)
		वापस 1;

	pad = end - reमुख्यder;
	metadata_access_enable();
	fault = स_प्रथम_inv(kasan_reset_tag(pad), POISON_INUSE, reमुख्यder);
	metadata_access_disable();
	अगर (!fault)
		वापस 1;
	जबतक (end > fault && end[-1] == POISON_INUSE)
		end--;

	slab_err(s, page, "Padding overwritten. 0x%p-0x%p @offset=%tu",
			fault, end - 1, fault - start);
	prपूर्णांक_section(KERN_ERR, "Padding ", pad, reमुख्यder);

	restore_bytes(s, "slab padding", POISON_INUSE, fault, end);
	वापस 0;
पूर्ण

अटल पूर्णांक check_object(काष्ठा kmem_cache *s, काष्ठा page *page,
					व्योम *object, u8 val)
अणु
	u8 *p = object;
	u8 *enकरोbject = object + s->object_size;

	अगर (s->flags & SLAB_RED_ZONE) अणु
		अगर (!check_bytes_and_report(s, page, object, "Left Redzone",
			object - s->red_left_pad, val, s->red_left_pad))
			वापस 0;

		अगर (!check_bytes_and_report(s, page, object, "Right Redzone",
			enकरोbject, val, s->inuse - s->object_size))
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर ((s->flags & SLAB_POISON) && s->object_size < s->inuse) अणु
			check_bytes_and_report(s, page, p, "Alignment padding",
				enकरोbject, POISON_INUSE,
				s->inuse - s->object_size);
		पूर्ण
	पूर्ण

	अगर (s->flags & SLAB_POISON) अणु
		अगर (val != SLUB_RED_ACTIVE && (s->flags & __OBJECT_POISON) &&
			(!check_bytes_and_report(s, page, p, "Poison", p,
					POISON_FREE, s->object_size - 1) ||
			 !check_bytes_and_report(s, page, p, "End Poison",
				p + s->object_size - 1, POISON_END, 1)))
			वापस 0;
		/*
		 * check_pad_bytes cleans up on its own.
		 */
		check_pad_bytes(s, page, p);
	पूर्ण

	अगर (!मुक्तptr_outside_object(s) && val == SLUB_RED_ACTIVE)
		/*
		 * Object and मुक्तpoपूर्णांकer overlap. Cannot check
		 * मुक्तpoपूर्णांकer जबतक object is allocated.
		 */
		वापस 1;

	/* Check मुक्त poपूर्णांकer validity */
	अगर (!check_valid_poपूर्णांकer(s, page, get_मुक्तpoपूर्णांकer(s, p))) अणु
		object_err(s, page, p, "Freepointer corrupt");
		/*
		 * No choice but to zap it and thus lose the reमुख्यder
		 * of the मुक्त objects in this slab. May cause
		 * another error because the object count is now wrong.
		 */
		set_मुक्तpoपूर्णांकer(s, p, शून्य);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक check_slab(काष्ठा kmem_cache *s, काष्ठा page *page)
अणु
	पूर्णांक maxobj;

	VM_BUG_ON(!irqs_disabled());

	अगर (!PageSlab(page)) अणु
		slab_err(s, page, "Not a valid slab page");
		वापस 0;
	पूर्ण

	maxobj = order_objects(compound_order(page), s->size);
	अगर (page->objects > maxobj) अणु
		slab_err(s, page, "objects %u > max %u",
			page->objects, maxobj);
		वापस 0;
	पूर्ण
	अगर (page->inuse > page->objects) अणु
		slab_err(s, page, "inuse %u > max %u",
			page->inuse, page->objects);
		वापस 0;
	पूर्ण
	/* Slab_pad_check fixes things up after itself */
	slab_pad_check(s, page);
	वापस 1;
पूर्ण

/*
 * Determine अगर a certain object on a page is on the मुक्तlist. Must hold the
 * slab lock to guarantee that the chains are in a consistent state.
 */
अटल पूर्णांक on_मुक्तlist(काष्ठा kmem_cache *s, काष्ठा page *page, व्योम *search)
अणु
	पूर्णांक nr = 0;
	व्योम *fp;
	व्योम *object = शून्य;
	पूर्णांक max_objects;

	fp = page->मुक्तlist;
	जबतक (fp && nr <= page->objects) अणु
		अगर (fp == search)
			वापस 1;
		अगर (!check_valid_poपूर्णांकer(s, page, fp)) अणु
			अगर (object) अणु
				object_err(s, page, object,
					"Freechain corrupt");
				set_मुक्तpoपूर्णांकer(s, object, शून्य);
			पूर्ण अन्यथा अणु
				slab_err(s, page, "Freepointer corrupt");
				page->मुक्तlist = शून्य;
				page->inuse = page->objects;
				slab_fix(s, "Freelist cleared");
				वापस 0;
			पूर्ण
			अवरोध;
		पूर्ण
		object = fp;
		fp = get_मुक्तpoपूर्णांकer(s, object);
		nr++;
	पूर्ण

	max_objects = order_objects(compound_order(page), s->size);
	अगर (max_objects > MAX_OBJS_PER_PAGE)
		max_objects = MAX_OBJS_PER_PAGE;

	अगर (page->objects != max_objects) अणु
		slab_err(s, page, "Wrong number of objects. Found %d but should be %d",
			 page->objects, max_objects);
		page->objects = max_objects;
		slab_fix(s, "Number of objects adjusted.");
	पूर्ण
	अगर (page->inuse != page->objects - nr) अणु
		slab_err(s, page, "Wrong object count. Counter is %d but counted were %d",
			 page->inuse, page->objects - nr);
		page->inuse = page->objects - nr;
		slab_fix(s, "Object count adjusted.");
	पूर्ण
	वापस search == शून्य;
पूर्ण

अटल व्योम trace(काष्ठा kmem_cache *s, काष्ठा page *page, व्योम *object,
								पूर्णांक alloc)
अणु
	अगर (s->flags & SLAB_TRACE) अणु
		pr_info("TRACE %s %s 0x%p inuse=%d fp=0x%p\n",
			s->name,
			alloc ? "alloc" : "free",
			object, page->inuse,
			page->मुक्तlist);

		अगर (!alloc)
			prपूर्णांक_section(KERN_INFO, "Object ", (व्योम *)object,
					s->object_size);

		dump_stack();
	पूर्ण
पूर्ण

/*
 * Tracking of fully allocated sद_असल क्रम debugging purposes.
 */
अटल व्योम add_full(काष्ठा kmem_cache *s,
	काष्ठा kmem_cache_node *n, काष्ठा page *page)
अणु
	अगर (!(s->flags & SLAB_STORE_USER))
		वापस;

	lockdep_निश्चित_held(&n->list_lock);
	list_add(&page->slab_list, &n->full);
पूर्ण

अटल व्योम हटाओ_full(काष्ठा kmem_cache *s, काष्ठा kmem_cache_node *n, काष्ठा page *page)
अणु
	अगर (!(s->flags & SLAB_STORE_USER))
		वापस;

	lockdep_निश्चित_held(&n->list_lock);
	list_del(&page->slab_list);
पूर्ण

/* Tracking of the number of sद_असल क्रम debugging purposes */
अटल अंतरभूत अचिन्हित दीर्घ sद_असल_node(काष्ठा kmem_cache *s, पूर्णांक node)
अणु
	काष्ठा kmem_cache_node *n = get_node(s, node);

	वापस atomic_दीर्घ_पढ़ो(&n->nr_sद_असल);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ node_nr_sद_असल(काष्ठा kmem_cache_node *n)
अणु
	वापस atomic_दीर्घ_पढ़ो(&n->nr_sद_असल);
पूर्ण

अटल अंतरभूत व्योम inc_sद_असल_node(काष्ठा kmem_cache *s, पूर्णांक node, पूर्णांक objects)
अणु
	काष्ठा kmem_cache_node *n = get_node(s, node);

	/*
	 * May be called early in order to allocate a slab क्रम the
	 * kmem_cache_node काष्ठाure. Solve the chicken-egg
	 * dilemma by deferring the increment of the count during
	 * bootstrap (see early_kmem_cache_node_alloc).
	 */
	अगर (likely(n)) अणु
		atomic_दीर्घ_inc(&n->nr_sद_असल);
		atomic_दीर्घ_add(objects, &n->total_objects);
	पूर्ण
पूर्ण
अटल अंतरभूत व्योम dec_sद_असल_node(काष्ठा kmem_cache *s, पूर्णांक node, पूर्णांक objects)
अणु
	काष्ठा kmem_cache_node *n = get_node(s, node);

	atomic_दीर्घ_dec(&n->nr_sद_असल);
	atomic_दीर्घ_sub(objects, &n->total_objects);
पूर्ण

/* Object debug checks क्रम alloc/मुक्त paths */
अटल व्योम setup_object_debug(काष्ठा kmem_cache *s, काष्ठा page *page,
								व्योम *object)
अणु
	अगर (!kmem_cache_debug_flags(s, SLAB_STORE_USER|SLAB_RED_ZONE|__OBJECT_POISON))
		वापस;

	init_object(s, object, SLUB_RED_INACTIVE);
	init_tracking(s, object);
पूर्ण

अटल
व्योम setup_page_debug(काष्ठा kmem_cache *s, काष्ठा page *page, व्योम *addr)
अणु
	अगर (!kmem_cache_debug_flags(s, SLAB_POISON))
		वापस;

	metadata_access_enable();
	स_रखो(kasan_reset_tag(addr), POISON_INUSE, page_size(page));
	metadata_access_disable();
पूर्ण

अटल अंतरभूत पूर्णांक alloc_consistency_checks(काष्ठा kmem_cache *s,
					काष्ठा page *page, व्योम *object)
अणु
	अगर (!check_slab(s, page))
		वापस 0;

	अगर (!check_valid_poपूर्णांकer(s, page, object)) अणु
		object_err(s, page, object, "Freelist Pointer check fails");
		वापस 0;
	पूर्ण

	अगर (!check_object(s, page, object, SLUB_RED_INACTIVE))
		वापस 0;

	वापस 1;
पूर्ण

अटल noअंतरभूत पूर्णांक alloc_debug_processing(काष्ठा kmem_cache *s,
					काष्ठा page *page,
					व्योम *object, अचिन्हित दीर्घ addr)
अणु
	अगर (s->flags & SLAB_CONSISTENCY_CHECKS) अणु
		अगर (!alloc_consistency_checks(s, page, object))
			जाओ bad;
	पूर्ण

	/* Success perक्रमm special debug activities क्रम allocs */
	अगर (s->flags & SLAB_STORE_USER)
		set_track(s, object, TRACK_ALLOC, addr);
	trace(s, page, object, 1);
	init_object(s, object, SLUB_RED_ACTIVE);
	वापस 1;

bad:
	अगर (PageSlab(page)) अणु
		/*
		 * If this is a slab page then lets करो the best we can
		 * to aव्योम issues in the future. Marking all objects
		 * as used aव्योमs touching the reमुख्यing objects.
		 */
		slab_fix(s, "Marking all objects used");
		page->inuse = page->objects;
		page->मुक्तlist = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक मुक्त_consistency_checks(काष्ठा kmem_cache *s,
		काष्ठा page *page, व्योम *object, अचिन्हित दीर्घ addr)
अणु
	अगर (!check_valid_poपूर्णांकer(s, page, object)) अणु
		slab_err(s, page, "Invalid object pointer 0x%p", object);
		वापस 0;
	पूर्ण

	अगर (on_मुक्तlist(s, page, object)) अणु
		object_err(s, page, object, "Object already free");
		वापस 0;
	पूर्ण

	अगर (!check_object(s, page, object, SLUB_RED_ACTIVE))
		वापस 0;

	अगर (unlikely(s != page->slab_cache)) अणु
		अगर (!PageSlab(page)) अणु
			slab_err(s, page, "Attempt to free object(0x%p) outside of slab",
				 object);
		पूर्ण अन्यथा अगर (!page->slab_cache) अणु
			pr_err("SLUB <none>: no slab for object 0x%p.\n",
			       object);
			dump_stack();
		पूर्ण अन्यथा
			object_err(s, page, object,
					"page slab pointer corrupt.");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/* Supports checking bulk मुक्त of a स्थिरructed मुक्तlist */
अटल noअंतरभूत पूर्णांक मुक्त_debug_processing(
	काष्ठा kmem_cache *s, काष्ठा page *page,
	व्योम *head, व्योम *tail, पूर्णांक bulk_cnt,
	अचिन्हित दीर्घ addr)
अणु
	काष्ठा kmem_cache_node *n = get_node(s, page_to_nid(page));
	व्योम *object = head;
	पूर्णांक cnt = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&n->list_lock, flags);
	slab_lock(page);

	अगर (s->flags & SLAB_CONSISTENCY_CHECKS) अणु
		अगर (!check_slab(s, page))
			जाओ out;
	पूर्ण

next_object:
	cnt++;

	अगर (s->flags & SLAB_CONSISTENCY_CHECKS) अणु
		अगर (!मुक्त_consistency_checks(s, page, object, addr))
			जाओ out;
	पूर्ण

	अगर (s->flags & SLAB_STORE_USER)
		set_track(s, object, TRACK_FREE, addr);
	trace(s, page, object, 0);
	/* Freepoपूर्णांकer not overwritten by init_object(), SLAB_POISON moved it */
	init_object(s, object, SLUB_RED_INACTIVE);

	/* Reached end of स्थिरructed मुक्तlist yet? */
	अगर (object != tail) अणु
		object = get_मुक्तpoपूर्णांकer(s, object);
		जाओ next_object;
	पूर्ण
	ret = 1;

out:
	अगर (cnt != bulk_cnt)
		slab_err(s, page, "Bulk freelist count(%d) invalid(%d)\n",
			 bulk_cnt, cnt);

	slab_unlock(page);
	spin_unlock_irqrestore(&n->list_lock, flags);
	अगर (!ret)
		slab_fix(s, "Object at 0x%p not freed", object);
	वापस ret;
पूर्ण

/*
 * Parse a block of slub_debug options. Blocks are delimited by ';'
 *
 * @str:    start of block
 * @flags:  वापसs parsed flags, or DEBUG_DEFAULT_FLAGS अगर none specअगरied
 * @sद_असल:  वापस start of list of sद_असल, or शून्य when there's no list
 * @init:   assume this is initial parsing and not per-kmem-create parsing
 *
 * वापसs the start of next block अगर there's any, or शून्य
 */
अटल अक्षर *
parse_slub_debug_flags(अक्षर *str, slab_flags_t *flags, अक्षर **sद_असल, bool init)
अणु
	bool higher_order_disable = false;

	/* Skip any completely empty blocks */
	जबतक (*str && *str == ';')
		str++;

	अगर (*str == ',') अणु
		/*
		 * No options but restriction on sद_असल. This means full
		 * debugging क्रम sद_असल matching a pattern.
		 */
		*flags = DEBUG_DEFAULT_FLAGS;
		जाओ check_sद_असल;
	पूर्ण
	*flags = 0;

	/* Determine which debug features should be चयनed on */
	क्रम (; *str && *str != ',' && *str != ';'; str++) अणु
		चयन (छोटे(*str)) अणु
		हाल '-':
			*flags = 0;
			अवरोध;
		हाल 'f':
			*flags |= SLAB_CONSISTENCY_CHECKS;
			अवरोध;
		हाल 'z':
			*flags |= SLAB_RED_ZONE;
			अवरोध;
		हाल 'p':
			*flags |= SLAB_POISON;
			अवरोध;
		हाल 'u':
			*flags |= SLAB_STORE_USER;
			अवरोध;
		हाल 't':
			*flags |= SLAB_TRACE;
			अवरोध;
		हाल 'a':
			*flags |= SLAB_FAILSLAB;
			अवरोध;
		हाल 'o':
			/*
			 * Aव्योम enabling debugging on caches अगर its minimum
			 * order would increase as a result.
			 */
			higher_order_disable = true;
			अवरोध;
		शेष:
			अगर (init)
				pr_err("slub_debug option '%c' unknown. skipped\n", *str);
		पूर्ण
	पूर्ण
check_sद_असल:
	अगर (*str == ',')
		*sद_असल = ++str;
	अन्यथा
		*sद_असल = शून्य;

	/* Skip over the slab list */
	जबतक (*str && *str != ';')
		str++;

	/* Skip any completely empty blocks */
	जबतक (*str && *str == ';')
		str++;

	अगर (init && higher_order_disable)
		disable_higher_order_debug = 1;

	अगर (*str)
		वापस str;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक __init setup_slub_debug(अक्षर *str)
अणु
	slab_flags_t flags;
	अक्षर *saved_str;
	अक्षर *slab_list;
	bool global_slub_debug_changed = false;
	bool slab_list_specअगरied = false;

	slub_debug = DEBUG_DEFAULT_FLAGS;
	अगर (*str++ != '=' || !*str)
		/*
		 * No options specअगरied. Switch on full debugging.
		 */
		जाओ out;

	saved_str = str;
	जबतक (str) अणु
		str = parse_slub_debug_flags(str, &flags, &slab_list, true);

		अगर (!slab_list) अणु
			slub_debug = flags;
			global_slub_debug_changed = true;
		पूर्ण अन्यथा अणु
			slab_list_specअगरied = true;
		पूर्ण
	पूर्ण

	/*
	 * For backwards compatibility, a single list of flags with list of
	 * sद_असल means debugging is only enabled क्रम those sद_असल, so the global
	 * slub_debug should be 0. We can extended that to multiple lists as
	 * दीर्घ as there is no option specअगरying flags without a slab list.
	 */
	अगर (slab_list_specअगरied) अणु
		अगर (!global_slub_debug_changed)
			slub_debug = 0;
		slub_debug_string = saved_str;
	पूर्ण
out:
	अगर (slub_debug != 0 || slub_debug_string)
		अटल_branch_enable(&slub_debug_enabled);
	अगर ((अटल_branch_unlikely(&init_on_alloc) ||
	     अटल_branch_unlikely(&init_on_मुक्त)) &&
	    (slub_debug & SLAB_POISON))
		pr_info("mem auto-init: SLAB_POISON will take precedence over init_on_alloc/init_on_free\n");
	वापस 1;
पूर्ण

__setup("slub_debug", setup_slub_debug);

/*
 * kmem_cache_flags - apply debugging options to the cache
 * @object_size:	the size of an object without meta data
 * @flags:		flags to set
 * @name:		name of the cache
 *
 * Debug option(s) are applied to @flags. In addition to the debug
 * option(s), अगर a slab name (or multiple) is specअगरied i.e.
 * slub_debug=<Debug-Options>,<slab name1>,<slab name2> ...
 * then only the select sद_असल will receive the debug option(s).
 */
slab_flags_t kmem_cache_flags(अचिन्हित पूर्णांक object_size,
	slab_flags_t flags, स्थिर अक्षर *name)
अणु
	अक्षर *iter;
	माप_प्रकार len;
	अक्षर *next_block;
	slab_flags_t block_flags;
	slab_flags_t slub_debug_local = slub_debug;

	/*
	 * If the slab cache is क्रम debugging (e.g. kmemleak) then
	 * करोn't store user (stack trace) inक्रमmation by शेष,
	 * but let the user enable it via the command line below.
	 */
	अगर (flags & SLAB_NOLEAKTRACE)
		slub_debug_local &= ~SLAB_STORE_USER;

	len = म_माप(name);
	next_block = slub_debug_string;
	/* Go through all blocks of debug options, see अगर any matches our slab's name */
	जबतक (next_block) अणु
		next_block = parse_slub_debug_flags(next_block, &block_flags, &iter, false);
		अगर (!iter)
			जारी;
		/* Found a block that has a slab list, search it */
		जबतक (*iter) अणु
			अक्षर *end, *glob;
			माप_प्रकार cmplen;

			end = म_अक्षरnul(iter, ',');
			अगर (next_block && next_block < end)
				end = next_block - 1;

			glob = strnchr(iter, end - iter, '*');
			अगर (glob)
				cmplen = glob - iter;
			अन्यथा
				cmplen = max_t(माप_प्रकार, len, (end - iter));

			अगर (!म_भेदन(name, iter, cmplen)) अणु
				flags |= block_flags;
				वापस flags;
			पूर्ण

			अगर (!*end || *end == ';')
				अवरोध;
			iter = end + 1;
		पूर्ण
	पूर्ण

	वापस flags | slub_debug_local;
पूर्ण
#अन्यथा /* !CONFIG_SLUB_DEBUG */
अटल अंतरभूत व्योम setup_object_debug(काष्ठा kmem_cache *s,
			काष्ठा page *page, व्योम *object) अणुपूर्ण
अटल अंतरभूत
व्योम setup_page_debug(काष्ठा kmem_cache *s, काष्ठा page *page, व्योम *addr) अणुपूर्ण

अटल अंतरभूत पूर्णांक alloc_debug_processing(काष्ठा kmem_cache *s,
	काष्ठा page *page, व्योम *object, अचिन्हित दीर्घ addr) अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक मुक्त_debug_processing(
	काष्ठा kmem_cache *s, काष्ठा page *page,
	व्योम *head, व्योम *tail, पूर्णांक bulk_cnt,
	अचिन्हित दीर्घ addr) अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक slab_pad_check(काष्ठा kmem_cache *s, काष्ठा page *page)
			अणु वापस 1; पूर्ण
अटल अंतरभूत पूर्णांक check_object(काष्ठा kmem_cache *s, काष्ठा page *page,
			व्योम *object, u8 val) अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम add_full(काष्ठा kmem_cache *s, काष्ठा kmem_cache_node *n,
					काष्ठा page *page) अणुपूर्ण
अटल अंतरभूत व्योम हटाओ_full(काष्ठा kmem_cache *s, काष्ठा kmem_cache_node *n,
					काष्ठा page *page) अणुपूर्ण
slab_flags_t kmem_cache_flags(अचिन्हित पूर्णांक object_size,
	slab_flags_t flags, स्थिर अक्षर *name)
अणु
	वापस flags;
पूर्ण
#घोषणा slub_debug 0

#घोषणा disable_higher_order_debug 0

अटल अंतरभूत अचिन्हित दीर्घ sद_असल_node(काष्ठा kmem_cache *s, पूर्णांक node)
							अणु वापस 0; पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ node_nr_sद_असल(काष्ठा kmem_cache_node *n)
							अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम inc_sद_असल_node(काष्ठा kmem_cache *s, पूर्णांक node,
							पूर्णांक objects) अणुपूर्ण
अटल अंतरभूत व्योम dec_sद_असल_node(काष्ठा kmem_cache *s, पूर्णांक node,
							पूर्णांक objects) अणुपूर्ण

अटल bool मुक्तlist_corrupted(काष्ठा kmem_cache *s, काष्ठा page *page,
			       व्योम **मुक्तlist, व्योम *nextमुक्त)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_SLUB_DEBUG */

/*
 * Hooks क्रम other subप्रणालीs that check memory allocations. In a typical
 * production configuration these hooks all should produce no code at all.
 */
अटल अंतरभूत व्योम *kदो_स्मृति_large_node_hook(व्योम *ptr, माप_प्रकार size, gfp_t flags)
अणु
	ptr = kasan_kदो_स्मृति_large(ptr, size, flags);
	/* As ptr might get tagged, call kmemleak hook after KASAN. */
	kmemleak_alloc(ptr, size, 1, flags);
	वापस ptr;
पूर्ण

अटल __always_अंतरभूत व्योम kमुक्त_hook(व्योम *x)
अणु
	kmemleak_मुक्त(x);
	kasan_kमुक्त_large(x);
पूर्ण

अटल __always_अंतरभूत bool slab_मुक्त_hook(काष्ठा kmem_cache *s,
						व्योम *x, bool init)
अणु
	kmemleak_मुक्त_recursive(x, s->flags);

	/*
	 * Trouble is that we may no दीर्घer disable पूर्णांकerrupts in the fast path
	 * So in order to make the debug calls that expect irqs to be
	 * disabled we need to disable पूर्णांकerrupts temporarily.
	 */
#अगर_घोषित CONFIG_LOCKDEP
	अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		debug_check_no_locks_मुक्तd(x, s->object_size);
		local_irq_restore(flags);
	पूर्ण
#पूर्ण_अगर
	अगर (!(s->flags & SLAB_DEBUG_OBJECTS))
		debug_check_no_obj_मुक्तd(x, s->object_size);

	/* Use KCSAN to help debug racy use-after-मुक्त. */
	अगर (!(s->flags & SLAB_TYPESAFE_BY_RCU))
		__kcsan_check_access(x, s->object_size,
				     KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ASSERT);

	/*
	 * As memory initialization might be पूर्णांकegrated पूर्णांकo KASAN,
	 * kasan_slab_मुक्त and initialization स_रखो's must be
	 * kept together to aव्योम discrepancies in behavior.
	 *
	 * The initialization स_रखो's clear the object and the metadata,
	 * but करोn't touch the SLAB redzone.
	 */
	अगर (init) अणु
		पूर्णांक rsize;

		अगर (!kasan_has_पूर्णांकegrated_init())
			स_रखो(kasan_reset_tag(x), 0, s->object_size);
		rsize = (s->flags & SLAB_RED_ZONE) ? s->red_left_pad : 0;
		स_रखो((अक्षर *)kasan_reset_tag(x) + s->inuse, 0,
		       s->size - s->inuse - rsize);
	पूर्ण
	/* KASAN might put x पूर्णांकo memory quarantine, delaying its reuse. */
	वापस kasan_slab_मुक्त(s, x, init);
पूर्ण

अटल अंतरभूत bool slab_मुक्त_मुक्तlist_hook(काष्ठा kmem_cache *s,
					   व्योम **head, व्योम **tail)
अणु

	व्योम *object;
	व्योम *next = *head;
	व्योम *old_tail = *tail ? *tail : *head;

	अगर (is_kfence_address(next)) अणु
		slab_मुक्त_hook(s, next, false);
		वापस true;
	पूर्ण

	/* Head and tail of the reस्थिरructed मुक्तlist */
	*head = शून्य;
	*tail = शून्य;

	करो अणु
		object = next;
		next = get_मुक्तpoपूर्णांकer(s, object);

		/* If object's reuse doesn't have to be delayed */
		अगर (!slab_मुक्त_hook(s, object, slab_want_init_on_मुक्त(s))) अणु
			/* Move object to the new मुक्तlist */
			set_मुक्तpoपूर्णांकer(s, object, *head);
			*head = object;
			अगर (!*tail)
				*tail = object;
		पूर्ण
	पूर्ण जबतक (object != old_tail);

	अगर (*head == *tail)
		*tail = शून्य;

	वापस *head != शून्य;
पूर्ण

अटल व्योम *setup_object(काष्ठा kmem_cache *s, काष्ठा page *page,
				व्योम *object)
अणु
	setup_object_debug(s, page, object);
	object = kasan_init_slab_obj(s, object);
	अगर (unlikely(s->ctor)) अणु
		kasan_unpoison_object_data(s, object);
		s->ctor(object);
		kasan_poison_object_data(s, object);
	पूर्ण
	वापस object;
पूर्ण

/*
 * Slab allocation and मुक्तing
 */
अटल अंतरभूत काष्ठा page *alloc_slab_page(काष्ठा kmem_cache *s,
		gfp_t flags, पूर्णांक node, काष्ठा kmem_cache_order_objects oo)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक order = oo_order(oo);

	अगर (node == NUMA_NO_NODE)
		page = alloc_pages(flags, order);
	अन्यथा
		page = __alloc_pages_node(node, flags, order);

	वापस page;
पूर्ण

#अगर_घोषित CONFIG_SLAB_FREELIST_RANDOM
/* Pre-initialize the अक्रमom sequence cache */
अटल पूर्णांक init_cache_अक्रमom_seq(काष्ठा kmem_cache *s)
अणु
	अचिन्हित पूर्णांक count = oo_objects(s->oo);
	पूर्णांक err;

	/* Bailout अगर alपढ़ोy initialised */
	अगर (s->अक्रमom_seq)
		वापस 0;

	err = cache_अक्रमom_seq_create(s, count, GFP_KERNEL);
	अगर (err) अणु
		pr_err("SLUB: Unable to initialize free list for %s\n",
			s->name);
		वापस err;
	पूर्ण

	/* Transक्रमm to an offset on the set of pages */
	अगर (s->अक्रमom_seq) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < count; i++)
			s->अक्रमom_seq[i] *= s->size;
	पूर्ण
	वापस 0;
पूर्ण

/* Initialize each अक्रमom sequence मुक्तlist per cache */
अटल व्योम __init init_मुक्तlist_अक्रमomization(व्योम)
अणु
	काष्ठा kmem_cache *s;

	mutex_lock(&slab_mutex);

	list_क्रम_each_entry(s, &slab_caches, list)
		init_cache_अक्रमom_seq(s);

	mutex_unlock(&slab_mutex);
पूर्ण

/* Get the next entry on the pre-computed मुक्तlist अक्रमomized */
अटल व्योम *next_मुक्तlist_entry(काष्ठा kmem_cache *s, काष्ठा page *page,
				अचिन्हित दीर्घ *pos, व्योम *start,
				अचिन्हित दीर्घ page_limit,
				अचिन्हित दीर्घ मुक्तlist_count)
अणु
	अचिन्हित पूर्णांक idx;

	/*
	 * If the target page allocation failed, the number of objects on the
	 * page might be smaller than the usual size defined by the cache.
	 */
	करो अणु
		idx = s->अक्रमom_seq[*pos];
		*pos += 1;
		अगर (*pos >= मुक्तlist_count)
			*pos = 0;
	पूर्ण जबतक (unlikely(idx >= page_limit));

	वापस (अक्षर *)start + idx;
पूर्ण

/* Shuffle the single linked मुक्तlist based on a अक्रमom pre-computed sequence */
अटल bool shuffle_मुक्तlist(काष्ठा kmem_cache *s, काष्ठा page *page)
अणु
	व्योम *start;
	व्योम *cur;
	व्योम *next;
	अचिन्हित दीर्घ idx, pos, page_limit, मुक्तlist_count;

	अगर (page->objects < 2 || !s->अक्रमom_seq)
		वापस false;

	मुक्तlist_count = oo_objects(s->oo);
	pos = get_अक्रमom_पूर्णांक() % मुक्तlist_count;

	page_limit = page->objects * s->size;
	start = fixup_red_left(s, page_address(page));

	/* First entry is used as the base of the मुक्तlist */
	cur = next_मुक्तlist_entry(s, page, &pos, start, page_limit,
				मुक्तlist_count);
	cur = setup_object(s, page, cur);
	page->मुक्तlist = cur;

	क्रम (idx = 1; idx < page->objects; idx++) अणु
		next = next_मुक्तlist_entry(s, page, &pos, start, page_limit,
			मुक्तlist_count);
		next = setup_object(s, page, next);
		set_मुक्तpoपूर्णांकer(s, cur, next);
		cur = next;
	पूर्ण
	set_मुक्तpoपूर्णांकer(s, cur, शून्य);

	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक init_cache_अक्रमom_seq(काष्ठा kmem_cache *s)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम init_मुक्तlist_अक्रमomization(व्योम) अणु पूर्ण
अटल अंतरभूत bool shuffle_मुक्तlist(काष्ठा kmem_cache *s, काष्ठा page *page)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_SLAB_FREELIST_RANDOM */

अटल काष्ठा page *allocate_slab(काष्ठा kmem_cache *s, gfp_t flags, पूर्णांक node)
अणु
	काष्ठा page *page;
	काष्ठा kmem_cache_order_objects oo = s->oo;
	gfp_t alloc_gfp;
	व्योम *start, *p, *next;
	पूर्णांक idx;
	bool shuffle;

	flags &= gfp_allowed_mask;

	अगर (gfpflags_allow_blocking(flags))
		local_irq_enable();

	flags |= s->allocflags;

	/*
	 * Let the initial higher-order allocation fail under memory pressure
	 * so we fall-back to the minimum order allocation.
	 */
	alloc_gfp = (flags | __GFP_NOWARN | __GFP_NORETRY) & ~__GFP_NOFAIL;
	अगर ((alloc_gfp & __GFP_सूचीECT_RECLAIM) && oo_order(oo) > oo_order(s->min))
		alloc_gfp = (alloc_gfp | __GFP_NOMEMALLOC) & ~(__GFP_RECLAIM|__GFP_NOFAIL);

	page = alloc_slab_page(s, alloc_gfp, node, oo);
	अगर (unlikely(!page)) अणु
		oo = s->min;
		alloc_gfp = flags;
		/*
		 * Allocation may have failed due to fragmentation.
		 * Try a lower order alloc अगर possible
		 */
		page = alloc_slab_page(s, alloc_gfp, node, oo);
		अगर (unlikely(!page))
			जाओ out;
		stat(s, ORDER_FALLBACK);
	पूर्ण

	page->objects = oo_objects(oo);

	account_slab_page(page, oo_order(oo), s, flags);

	page->slab_cache = s;
	__SetPageSlab(page);
	अगर (page_is_pfmeदो_स्मृति(page))
		SetPageSlabPfmeदो_स्मृति(page);

	kasan_poison_slab(page);

	start = page_address(page);

	setup_page_debug(s, page, start);

	shuffle = shuffle_मुक्तlist(s, page);

	अगर (!shuffle) अणु
		start = fixup_red_left(s, start);
		start = setup_object(s, page, start);
		page->मुक्तlist = start;
		क्रम (idx = 0, p = start; idx < page->objects - 1; idx++) अणु
			next = p + s->size;
			next = setup_object(s, page, next);
			set_मुक्तpoपूर्णांकer(s, p, next);
			p = next;
		पूर्ण
		set_मुक्तpoपूर्णांकer(s, p, शून्य);
	पूर्ण

	page->inuse = page->objects;
	page->frozen = 1;

out:
	अगर (gfpflags_allow_blocking(flags))
		local_irq_disable();
	अगर (!page)
		वापस शून्य;

	inc_sद_असल_node(s, page_to_nid(page), page->objects);

	वापस page;
पूर्ण

अटल काष्ठा page *new_slab(काष्ठा kmem_cache *s, gfp_t flags, पूर्णांक node)
अणु
	अगर (unlikely(flags & GFP_SLAB_BUG_MASK))
		flags = kदो_स्मृति_fix_flags(flags);

	वापस allocate_slab(s,
		flags & (GFP_RECLAIM_MASK | GFP_CONSTRAINT_MASK), node);
पूर्ण

अटल व्योम __मुक्त_slab(काष्ठा kmem_cache *s, काष्ठा page *page)
अणु
	पूर्णांक order = compound_order(page);
	पूर्णांक pages = 1 << order;

	अगर (kmem_cache_debug_flags(s, SLAB_CONSISTENCY_CHECKS)) अणु
		व्योम *p;

		slab_pad_check(s, page);
		क्रम_each_object(p, s, page_address(page),
						page->objects)
			check_object(s, page, p, SLUB_RED_INACTIVE);
	पूर्ण

	__ClearPageSlabPfmeदो_स्मृति(page);
	__ClearPageSlab(page);
	/* In जोड़ with page->mapping where page allocator expects शून्य */
	page->slab_cache = शून्य;
	अगर (current->reclaim_state)
		current->reclaim_state->reclaimed_slab += pages;
	unaccount_slab_page(page, order, s);
	__मुक्त_pages(page, order);
पूर्ण

अटल व्योम rcu_मुक्त_slab(काष्ठा rcu_head *h)
अणु
	काष्ठा page *page = container_of(h, काष्ठा page, rcu_head);

	__मुक्त_slab(page->slab_cache, page);
पूर्ण

अटल व्योम मुक्त_slab(काष्ठा kmem_cache *s, काष्ठा page *page)
अणु
	अगर (unlikely(s->flags & SLAB_TYPESAFE_BY_RCU)) अणु
		call_rcu(&page->rcu_head, rcu_मुक्त_slab);
	पूर्ण अन्यथा
		__मुक्त_slab(s, page);
पूर्ण

अटल व्योम discard_slab(काष्ठा kmem_cache *s, काष्ठा page *page)
अणु
	dec_sद_असल_node(s, page_to_nid(page), page->objects);
	मुक्त_slab(s, page);
पूर्ण

/*
 * Management of partially allocated sद_असल.
 */
अटल अंतरभूत व्योम
__add_partial(काष्ठा kmem_cache_node *n, काष्ठा page *page, पूर्णांक tail)
अणु
	n->nr_partial++;
	अगर (tail == DEACTIVATE_TO_TAIL)
		list_add_tail(&page->slab_list, &n->partial);
	अन्यथा
		list_add(&page->slab_list, &n->partial);
पूर्ण

अटल अंतरभूत व्योम add_partial(काष्ठा kmem_cache_node *n,
				काष्ठा page *page, पूर्णांक tail)
अणु
	lockdep_निश्चित_held(&n->list_lock);
	__add_partial(n, page, tail);
पूर्ण

अटल अंतरभूत व्योम हटाओ_partial(काष्ठा kmem_cache_node *n,
					काष्ठा page *page)
अणु
	lockdep_निश्चित_held(&n->list_lock);
	list_del(&page->slab_list);
	n->nr_partial--;
पूर्ण

/*
 * Remove slab from the partial list, मुक्तze it and
 * वापस the poपूर्णांकer to the मुक्तlist.
 *
 * Returns a list of objects or शून्य अगर it fails.
 */
अटल अंतरभूत व्योम *acquire_slab(काष्ठा kmem_cache *s,
		काष्ठा kmem_cache_node *n, काष्ठा page *page,
		पूर्णांक mode, पूर्णांक *objects)
अणु
	व्योम *मुक्तlist;
	अचिन्हित दीर्घ counters;
	काष्ठा page new;

	lockdep_निश्चित_held(&n->list_lock);

	/*
	 * Zap the मुक्तlist and set the frozen bit.
	 * The old मुक्तlist is the list of objects क्रम the
	 * per cpu allocation list.
	 */
	मुक्तlist = page->मुक्तlist;
	counters = page->counters;
	new.counters = counters;
	*objects = new.objects - new.inuse;
	अगर (mode) अणु
		new.inuse = page->objects;
		new.मुक्तlist = शून्य;
	पूर्ण अन्यथा अणु
		new.मुक्तlist = मुक्तlist;
	पूर्ण

	VM_BUG_ON(new.frozen);
	new.frozen = 1;

	अगर (!__cmpxchg_द्विगुन_slab(s, page,
			मुक्तlist, counters,
			new.मुक्तlist, new.counters,
			"acquire_slab"))
		वापस शून्य;

	हटाओ_partial(n, page);
	WARN_ON(!मुक्तlist);
	वापस मुक्तlist;
पूर्ण

अटल व्योम put_cpu_partial(काष्ठा kmem_cache *s, काष्ठा page *page, पूर्णांक drain);
अटल अंतरभूत bool pfmeदो_स्मृति_match(काष्ठा page *page, gfp_t gfpflags);

/*
 * Try to allocate a partial slab from a specअगरic node.
 */
अटल व्योम *get_partial_node(काष्ठा kmem_cache *s, काष्ठा kmem_cache_node *n,
				काष्ठा kmem_cache_cpu *c, gfp_t flags)
अणु
	काष्ठा page *page, *page2;
	व्योम *object = शून्य;
	अचिन्हित पूर्णांक available = 0;
	पूर्णांक objects;

	/*
	 * Racy check. If we mistakenly see no partial sद_असल then we
	 * just allocate an empty slab. If we mistakenly try to get a
	 * partial slab and there is none available then get_partial()
	 * will वापस शून्य.
	 */
	अगर (!n || !n->nr_partial)
		वापस शून्य;

	spin_lock(&n->list_lock);
	list_क्रम_each_entry_safe(page, page2, &n->partial, slab_list) अणु
		व्योम *t;

		अगर (!pfmeदो_स्मृति_match(page, flags))
			जारी;

		t = acquire_slab(s, n, page, object == शून्य, &objects);
		अगर (!t)
			अवरोध;

		available += objects;
		अगर (!object) अणु
			c->page = page;
			stat(s, ALLOC_FROM_PARTIAL);
			object = t;
		पूर्ण अन्यथा अणु
			put_cpu_partial(s, page, 0);
			stat(s, CPU_PARTIAL_NODE);
		पूर्ण
		अगर (!kmem_cache_has_cpu_partial(s)
			|| available > slub_cpu_partial(s) / 2)
			अवरोध;

	पूर्ण
	spin_unlock(&n->list_lock);
	वापस object;
पूर्ण

/*
 * Get a page from somewhere. Search in increasing NUMA distances.
 */
अटल व्योम *get_any_partial(काष्ठा kmem_cache *s, gfp_t flags,
		काष्ठा kmem_cache_cpu *c)
अणु
#अगर_घोषित CONFIG_NUMA
	काष्ठा zonelist *zonelist;
	काष्ठा zoneref *z;
	काष्ठा zone *zone;
	क्रमागत zone_type highest_zoneidx = gfp_zone(flags);
	व्योम *object;
	अचिन्हित पूर्णांक cpuset_mems_cookie;

	/*
	 * The defrag ratio allows a configuration of the tradeoffs between
	 * पूर्णांकer node defragmentation and node local allocations. A lower
	 * defrag_ratio increases the tendency to करो local allocations
	 * instead of attempting to obtain partial sद_असल from other nodes.
	 *
	 * If the defrag_ratio is set to 0 then kदो_स्मृति() always
	 * वापसs node local objects. If the ratio is higher then kदो_स्मृति()
	 * may वापस off node objects because partial sद_असल are obtained
	 * from other nodes and filled up.
	 *
	 * If /sys/kernel/slab/xx/remote_node_defrag_ratio is set to 100
	 * (which makes defrag_ratio = 1000) then every (well almost)
	 * allocation will first attempt to defrag slab caches on other nodes.
	 * This means scanning over all nodes to look क्रम partial sद_असल which
	 * may be expensive अगर we करो it every समय we are trying to find a slab
	 * with available objects.
	 */
	अगर (!s->remote_node_defrag_ratio ||
			get_cycles() % 1024 > s->remote_node_defrag_ratio)
		वापस शून्य;

	करो अणु
		cpuset_mems_cookie = पढ़ो_mems_allowed_begin();
		zonelist = node_zonelist(mempolicy_slab_node(), flags);
		क्रम_each_zone_zonelist(zone, z, zonelist, highest_zoneidx) अणु
			काष्ठा kmem_cache_node *n;

			n = get_node(s, zone_to_nid(zone));

			अगर (n && cpuset_zone_allowed(zone, flags) &&
					n->nr_partial > s->min_partial) अणु
				object = get_partial_node(s, n, c, flags);
				अगर (object) अणु
					/*
					 * Don't check पढ़ो_mems_allowed_retry()
					 * here - अगर mems_allowed was updated in
					 * parallel, that was a harmless race
					 * between allocation and the cpuset
					 * update
					 */
					वापस object;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण जबतक (पढ़ो_mems_allowed_retry(cpuset_mems_cookie));
#पूर्ण_अगर	/* CONFIG_NUMA */
	वापस शून्य;
पूर्ण

/*
 * Get a partial page, lock it and वापस it.
 */
अटल व्योम *get_partial(काष्ठा kmem_cache *s, gfp_t flags, पूर्णांक node,
		काष्ठा kmem_cache_cpu *c)
अणु
	व्योम *object;
	पूर्णांक searchnode = node;

	अगर (node == NUMA_NO_NODE)
		searchnode = numa_mem_id();

	object = get_partial_node(s, get_node(s, searchnode), c, flags);
	अगर (object || node != NUMA_NO_NODE)
		वापस object;

	वापस get_any_partial(s, flags, c);
पूर्ण

#अगर_घोषित CONFIG_PREEMPTION
/*
 * Calculate the next globally unique transaction क्रम disambiguation
 * during cmpxchg. The transactions start with the cpu number and are then
 * incremented by CONFIG_NR_CPUS.
 */
#घोषणा TID_STEP  roundup_घात_of_two(CONFIG_NR_CPUS)
#अन्यथा
/*
 * No preemption supported thereक्रमe also no need to check क्रम
 * dअगरferent cpus.
 */
#घोषणा TID_STEP 1
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ next_tid(अचिन्हित दीर्घ tid)
अणु
	वापस tid + TID_STEP;
पूर्ण

#अगर_घोषित SLUB_DEBUG_CMPXCHG
अटल अंतरभूत अचिन्हित पूर्णांक tid_to_cpu(अचिन्हित दीर्घ tid)
अणु
	वापस tid % TID_STEP;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ tid_to_event(अचिन्हित दीर्घ tid)
अणु
	वापस tid / TID_STEP;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक init_tid(पूर्णांक cpu)
अणु
	वापस cpu;
पूर्ण

अटल अंतरभूत व्योम note_cmpxchg_failure(स्थिर अक्षर *n,
		स्थिर काष्ठा kmem_cache *s, अचिन्हित दीर्घ tid)
अणु
#अगर_घोषित SLUB_DEBUG_CMPXCHG
	अचिन्हित दीर्घ actual_tid = __this_cpu_पढ़ो(s->cpu_slab->tid);

	pr_info("%s %s: cmpxchg redo ", n, s->name);

#अगर_घोषित CONFIG_PREEMPTION
	अगर (tid_to_cpu(tid) != tid_to_cpu(actual_tid))
		pr_warn("due to cpu change %d -> %d\n",
			tid_to_cpu(tid), tid_to_cpu(actual_tid));
	अन्यथा
#पूर्ण_अगर
	अगर (tid_to_event(tid) != tid_to_event(actual_tid))
		pr_warn("due to cpu running other code. Event %ld->%ld\n",
			tid_to_event(tid), tid_to_event(actual_tid));
	अन्यथा
		pr_warn("for unknown reason: actual=%lx was=%lx target=%lx\n",
			actual_tid, tid, next_tid(tid));
#पूर्ण_अगर
	stat(s, CMPXCHG_DOUBLE_CPU_FAIL);
पूर्ण

अटल व्योम init_kmem_cache_cpus(काष्ठा kmem_cache *s)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		per_cpu_ptr(s->cpu_slab, cpu)->tid = init_tid(cpu);
पूर्ण

/*
 * Remove the cpu slab
 */
अटल व्योम deactivate_slab(काष्ठा kmem_cache *s, काष्ठा page *page,
				व्योम *मुक्तlist, काष्ठा kmem_cache_cpu *c)
अणु
	क्रमागत slab_modes अणु M_NONE, M_PARTIAL, M_FULL, M_FREE पूर्ण;
	काष्ठा kmem_cache_node *n = get_node(s, page_to_nid(page));
	पूर्णांक lock = 0, मुक्त_delta = 0;
	क्रमागत slab_modes l = M_NONE, m = M_NONE;
	व्योम *nextमुक्त, *मुक्तlist_iter, *मुक्तlist_tail;
	पूर्णांक tail = DEACTIVATE_TO_HEAD;
	काष्ठा page new;
	काष्ठा page old;

	अगर (page->मुक्तlist) अणु
		stat(s, DEACTIVATE_REMOTE_FREES);
		tail = DEACTIVATE_TO_TAIL;
	पूर्ण

	/*
	 * Stage one: Count the objects on cpu's मुक्तlist as मुक्त_delta and
	 * remember the last object in मुक्तlist_tail क्रम later splicing.
	 */
	मुक्तlist_tail = शून्य;
	मुक्तlist_iter = मुक्तlist;
	जबतक (मुक्तlist_iter) अणु
		nextमुक्त = get_मुक्तpoपूर्णांकer(s, मुक्तlist_iter);

		/*
		 * If 'nextfree' is invalid, it is possible that the object at
		 * 'freelist_iter' is alपढ़ोy corrupted.  So isolate all objects
		 * starting at 'freelist_iter' by skipping them.
		 */
		अगर (मुक्तlist_corrupted(s, page, &मुक्तlist_iter, nextमुक्त))
			अवरोध;

		मुक्तlist_tail = मुक्तlist_iter;
		मुक्त_delta++;

		मुक्तlist_iter = nextमुक्त;
	पूर्ण

	/*
	 * Stage two: Unमुक्तze the page जबतक splicing the per-cpu
	 * मुक्तlist to the head of page's मुक्तlist.
	 *
	 * Ensure that the page is unfrozen जबतक the list presence
	 * reflects the actual number of objects during unमुक्तze.
	 *
	 * We setup the list membership and then perक्रमm a cmpxchg
	 * with the count. If there is a mismatch then the page
	 * is not unfrozen but the page is on the wrong list.
	 *
	 * Then we restart the process which may have to हटाओ
	 * the page from the list that we just put it on again
	 * because the number of objects in the slab may have
	 * changed.
	 */
reकरो:

	old.मुक्तlist = READ_ONCE(page->मुक्तlist);
	old.counters = READ_ONCE(page->counters);
	VM_BUG_ON(!old.frozen);

	/* Determine target state of the slab */
	new.counters = old.counters;
	अगर (मुक्तlist_tail) अणु
		new.inuse -= मुक्त_delta;
		set_मुक्तpoपूर्णांकer(s, मुक्तlist_tail, old.मुक्तlist);
		new.मुक्तlist = मुक्तlist;
	पूर्ण अन्यथा
		new.मुक्तlist = old.मुक्तlist;

	new.frozen = 0;

	अगर (!new.inuse && n->nr_partial >= s->min_partial)
		m = M_FREE;
	अन्यथा अगर (new.मुक्तlist) अणु
		m = M_PARTIAL;
		अगर (!lock) अणु
			lock = 1;
			/*
			 * Taking the spinlock हटाओs the possibility
			 * that acquire_slab() will see a slab page that
			 * is frozen
			 */
			spin_lock(&n->list_lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		m = M_FULL;
		अगर (kmem_cache_debug_flags(s, SLAB_STORE_USER) && !lock) अणु
			lock = 1;
			/*
			 * This also ensures that the scanning of full
			 * sद_असल from diagnostic functions will not see
			 * any frozen sद_असल.
			 */
			spin_lock(&n->list_lock);
		पूर्ण
	पूर्ण

	अगर (l != m) अणु
		अगर (l == M_PARTIAL)
			हटाओ_partial(n, page);
		अन्यथा अगर (l == M_FULL)
			हटाओ_full(s, n, page);

		अगर (m == M_PARTIAL)
			add_partial(n, page, tail);
		अन्यथा अगर (m == M_FULL)
			add_full(s, n, page);
	पूर्ण

	l = m;
	अगर (!__cmpxchg_द्विगुन_slab(s, page,
				old.मुक्तlist, old.counters,
				new.मुक्तlist, new.counters,
				"unfreezing slab"))
		जाओ reकरो;

	अगर (lock)
		spin_unlock(&n->list_lock);

	अगर (m == M_PARTIAL)
		stat(s, tail);
	अन्यथा अगर (m == M_FULL)
		stat(s, DEACTIVATE_FULL);
	अन्यथा अगर (m == M_FREE) अणु
		stat(s, DEACTIVATE_EMPTY);
		discard_slab(s, page);
		stat(s, FREE_SLAB);
	पूर्ण

	c->page = शून्य;
	c->मुक्तlist = शून्य;
पूर्ण

/*
 * Unमुक्तze all the cpu partial sद_असल.
 *
 * This function must be called with पूर्णांकerrupts disabled
 * क्रम the cpu using c (or some other guarantee must be there
 * to guarantee no concurrent accesses).
 */
अटल व्योम unमुक्तze_partials(काष्ठा kmem_cache *s,
		काष्ठा kmem_cache_cpu *c)
अणु
#अगर_घोषित CONFIG_SLUB_CPU_PARTIAL
	काष्ठा kmem_cache_node *n = शून्य, *n2 = शून्य;
	काष्ठा page *page, *discard_page = शून्य;

	जबतक ((page = slub_percpu_partial(c))) अणु
		काष्ठा page new;
		काष्ठा page old;

		slub_set_percpu_partial(c, page);

		n2 = get_node(s, page_to_nid(page));
		अगर (n != n2) अणु
			अगर (n)
				spin_unlock(&n->list_lock);

			n = n2;
			spin_lock(&n->list_lock);
		पूर्ण

		करो अणु

			old.मुक्तlist = page->मुक्तlist;
			old.counters = page->counters;
			VM_BUG_ON(!old.frozen);

			new.counters = old.counters;
			new.मुक्तlist = old.मुक्तlist;

			new.frozen = 0;

		पूर्ण जबतक (!__cmpxchg_द्विगुन_slab(s, page,
				old.मुक्तlist, old.counters,
				new.मुक्तlist, new.counters,
				"unfreezing slab"));

		अगर (unlikely(!new.inuse && n->nr_partial >= s->min_partial)) अणु
			page->next = discard_page;
			discard_page = page;
		पूर्ण अन्यथा अणु
			add_partial(n, page, DEACTIVATE_TO_TAIL);
			stat(s, FREE_ADD_PARTIAL);
		पूर्ण
	पूर्ण

	अगर (n)
		spin_unlock(&n->list_lock);

	जबतक (discard_page) अणु
		page = discard_page;
		discard_page = discard_page->next;

		stat(s, DEACTIVATE_EMPTY);
		discard_slab(s, page);
		stat(s, FREE_SLAB);
	पूर्ण
#पूर्ण_अगर	/* CONFIG_SLUB_CPU_PARTIAL */
पूर्ण

/*
 * Put a page that was just frozen (in __slab_मुक्त|get_partial_node) पूर्णांकo a
 * partial page slot अगर available.
 *
 * If we did not find a slot then simply move all the partials to the
 * per node partial list.
 */
अटल व्योम put_cpu_partial(काष्ठा kmem_cache *s, काष्ठा page *page, पूर्णांक drain)
अणु
#अगर_घोषित CONFIG_SLUB_CPU_PARTIAL
	काष्ठा page *oldpage;
	पूर्णांक pages;
	पूर्णांक pobjects;

	preempt_disable();
	करो अणु
		pages = 0;
		pobjects = 0;
		oldpage = this_cpu_पढ़ो(s->cpu_slab->partial);

		अगर (oldpage) अणु
			pobjects = oldpage->pobjects;
			pages = oldpage->pages;
			अगर (drain && pobjects > slub_cpu_partial(s)) अणु
				अचिन्हित दीर्घ flags;
				/*
				 * partial array is full. Move the existing
				 * set to the per node partial list.
				 */
				local_irq_save(flags);
				unमुक्तze_partials(s, this_cpu_ptr(s->cpu_slab));
				local_irq_restore(flags);
				oldpage = शून्य;
				pobjects = 0;
				pages = 0;
				stat(s, CPU_PARTIAL_DRAIN);
			पूर्ण
		पूर्ण

		pages++;
		pobjects += page->objects - page->inuse;

		page->pages = pages;
		page->pobjects = pobjects;
		page->next = oldpage;

	पूर्ण जबतक (this_cpu_cmpxchg(s->cpu_slab->partial, oldpage, page)
								!= oldpage);
	अगर (unlikely(!slub_cpu_partial(s))) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		unमुक्तze_partials(s, this_cpu_ptr(s->cpu_slab));
		local_irq_restore(flags);
	पूर्ण
	preempt_enable();
#पूर्ण_अगर	/* CONFIG_SLUB_CPU_PARTIAL */
पूर्ण

अटल अंतरभूत व्योम flush_slab(काष्ठा kmem_cache *s, काष्ठा kmem_cache_cpu *c)
अणु
	stat(s, CPUSLAB_FLUSH);
	deactivate_slab(s, c->page, c->मुक्तlist, c);

	c->tid = next_tid(c->tid);
पूर्ण

/*
 * Flush cpu slab.
 *
 * Called from IPI handler with पूर्णांकerrupts disabled.
 */
अटल अंतरभूत व्योम __flush_cpu_slab(काष्ठा kmem_cache *s, पूर्णांक cpu)
अणु
	काष्ठा kmem_cache_cpu *c = per_cpu_ptr(s->cpu_slab, cpu);

	अगर (c->page)
		flush_slab(s, c);

	unमुक्तze_partials(s, c);
पूर्ण

अटल व्योम flush_cpu_slab(व्योम *d)
अणु
	काष्ठा kmem_cache *s = d;

	__flush_cpu_slab(s, smp_processor_id());
पूर्ण

अटल bool has_cpu_slab(पूर्णांक cpu, व्योम *info)
अणु
	काष्ठा kmem_cache *s = info;
	काष्ठा kmem_cache_cpu *c = per_cpu_ptr(s->cpu_slab, cpu);

	वापस c->page || slub_percpu_partial(c);
पूर्ण

अटल व्योम flush_all(काष्ठा kmem_cache *s)
अणु
	on_each_cpu_cond(has_cpu_slab, flush_cpu_slab, s, 1);
पूर्ण

/*
 * Use the cpu notअगरier to insure that the cpu sद_असल are flushed when
 * necessary.
 */
अटल पूर्णांक slub_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा kmem_cache *s;
	अचिन्हित दीर्घ flags;

	mutex_lock(&slab_mutex);
	list_क्रम_each_entry(s, &slab_caches, list) अणु
		local_irq_save(flags);
		__flush_cpu_slab(s, cpu);
		local_irq_restore(flags);
	पूर्ण
	mutex_unlock(&slab_mutex);
	वापस 0;
पूर्ण

/*
 * Check अगर the objects in a per cpu काष्ठाure fit numa
 * locality expectations.
 */
अटल अंतरभूत पूर्णांक node_match(काष्ठा page *page, पूर्णांक node)
अणु
#अगर_घोषित CONFIG_NUMA
	अगर (node != NUMA_NO_NODE && page_to_nid(page) != node)
		वापस 0;
#पूर्ण_अगर
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_SLUB_DEBUG
अटल पूर्णांक count_मुक्त(काष्ठा page *page)
अणु
	वापस page->objects - page->inuse;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ node_nr_objs(काष्ठा kmem_cache_node *n)
अणु
	वापस atomic_दीर्घ_पढ़ो(&n->total_objects);
पूर्ण
#पूर्ण_अगर /* CONFIG_SLUB_DEBUG */

#अगर defined(CONFIG_SLUB_DEBUG) || defined(CONFIG_SYSFS)
अटल अचिन्हित दीर्घ count_partial(काष्ठा kmem_cache_node *n,
					पूर्णांक (*get_count)(काष्ठा page *))
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ x = 0;
	काष्ठा page *page;

	spin_lock_irqsave(&n->list_lock, flags);
	list_क्रम_each_entry(page, &n->partial, slab_list)
		x += get_count(page);
	spin_unlock_irqrestore(&n->list_lock, flags);
	वापस x;
पूर्ण
#पूर्ण_अगर /* CONFIG_SLUB_DEBUG || CONFIG_SYSFS */

अटल noअंतरभूत व्योम
slab_out_of_memory(काष्ठा kmem_cache *s, gfp_t gfpflags, पूर्णांक nid)
अणु
#अगर_घोषित CONFIG_SLUB_DEBUG
	अटल DEFINE_RATELIMIT_STATE(slub_oom_rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	अगर ((gfpflags & __GFP_NOWARN) || !__ratelimit(&slub_oom_rs))
		वापस;

	pr_warn("SLUB: Unable to allocate memory on node %d, gfp=%#x(%pGg)\n",
		nid, gfpflags, &gfpflags);
	pr_warn("  cache: %s, object size: %u, buffer size: %u, default order: %u, min order: %u\n",
		s->name, s->object_size, s->size, oo_order(s->oo),
		oo_order(s->min));

	अगर (oo_order(s->min) > get_order(s->object_size))
		pr_warn("  %s debugging increased min order, use slub_debug=O to disable.\n",
			s->name);

	क्रम_each_kmem_cache_node(s, node, n) अणु
		अचिन्हित दीर्घ nr_sद_असल;
		अचिन्हित दीर्घ nr_objs;
		अचिन्हित दीर्घ nr_मुक्त;

		nr_मुक्त  = count_partial(n, count_मुक्त);
		nr_sद_असल = node_nr_sद_असल(n);
		nr_objs  = node_nr_objs(n);

		pr_warn("  node %d: slabs: %ld, objs: %ld, free: %ld\n",
			node, nr_sद_असल, nr_objs, nr_मुक्त);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम *new_slab_objects(काष्ठा kmem_cache *s, gfp_t flags,
			पूर्णांक node, काष्ठा kmem_cache_cpu **pc)
अणु
	व्योम *मुक्तlist;
	काष्ठा kmem_cache_cpu *c = *pc;
	काष्ठा page *page;

	WARN_ON_ONCE(s->ctor && (flags & __GFP_ZERO));

	मुक्तlist = get_partial(s, flags, node, c);

	अगर (मुक्तlist)
		वापस मुक्तlist;

	page = new_slab(s, flags, node);
	अगर (page) अणु
		c = raw_cpu_ptr(s->cpu_slab);
		अगर (c->page)
			flush_slab(s, c);

		/*
		 * No other reference to the page yet so we can
		 * muck around with it मुक्तly without cmpxchg
		 */
		मुक्तlist = page->मुक्तlist;
		page->मुक्तlist = शून्य;

		stat(s, ALLOC_SLAB);
		c->page = page;
		*pc = c;
	पूर्ण

	वापस मुक्तlist;
पूर्ण

अटल अंतरभूत bool pfmeदो_स्मृति_match(काष्ठा page *page, gfp_t gfpflags)
अणु
	अगर (unlikely(PageSlabPfmeदो_स्मृति(page)))
		वापस gfp_pfmeदो_स्मृति_allowed(gfpflags);

	वापस true;
पूर्ण

/*
 * Check the page->मुक्तlist of a page and either transfer the मुक्तlist to the
 * per cpu मुक्तlist or deactivate the page.
 *
 * The page is still frozen अगर the वापस value is not शून्य.
 *
 * If this function वापसs शून्य then the page has been unfrozen.
 *
 * This function must be called with पूर्णांकerrupt disabled.
 */
अटल अंतरभूत व्योम *get_मुक्तlist(काष्ठा kmem_cache *s, काष्ठा page *page)
अणु
	काष्ठा page new;
	अचिन्हित दीर्घ counters;
	व्योम *मुक्तlist;

	करो अणु
		मुक्तlist = page->मुक्तlist;
		counters = page->counters;

		new.counters = counters;
		VM_BUG_ON(!new.frozen);

		new.inuse = page->objects;
		new.frozen = मुक्तlist != शून्य;

	पूर्ण जबतक (!__cmpxchg_द्विगुन_slab(s, page,
		मुक्तlist, counters,
		शून्य, new.counters,
		"get_freelist"));

	वापस मुक्तlist;
पूर्ण

/*
 * Slow path. The lockless मुक्तlist is empty or we need to perक्रमm
 * debugging duties.
 *
 * Processing is still very fast अगर new objects have been मुक्तd to the
 * regular मुक्तlist. In that हाल we simply take over the regular मुक्तlist
 * as the lockless मुक्तlist and zap the regular मुक्तlist.
 *
 * If that is not working then we fall back to the partial lists. We take the
 * first element of the मुक्तlist as the object to allocate now and move the
 * rest of the मुक्तlist to the lockless मुक्तlist.
 *
 * And अगर we were unable to get a new slab from the partial slab lists then
 * we need to allocate a new slab. This is the slowest path since it involves
 * a call to the page allocator and the setup of a new slab.
 *
 * Version of __slab_alloc to use when we know that पूर्णांकerrupts are
 * alपढ़ोy disabled (which is the हाल क्रम bulk allocation).
 */
अटल व्योम *___slab_alloc(काष्ठा kmem_cache *s, gfp_t gfpflags, पूर्णांक node,
			  अचिन्हित दीर्घ addr, काष्ठा kmem_cache_cpu *c)
अणु
	व्योम *मुक्तlist;
	काष्ठा page *page;

	stat(s, ALLOC_SLOWPATH);

	page = c->page;
	अगर (!page) अणु
		/*
		 * अगर the node is not online or has no normal memory, just
		 * ignore the node स्थिरraपूर्णांक
		 */
		अगर (unlikely(node != NUMA_NO_NODE &&
			     !node_isset(node, slab_nodes)))
			node = NUMA_NO_NODE;
		जाओ new_slab;
	पूर्ण
reकरो:

	अगर (unlikely(!node_match(page, node))) अणु
		/*
		 * same as above but node_match() being false alपढ़ोy
		 * implies node != NUMA_NO_NODE
		 */
		अगर (!node_isset(node, slab_nodes)) अणु
			node = NUMA_NO_NODE;
			जाओ reकरो;
		पूर्ण अन्यथा अणु
			stat(s, ALLOC_NODE_MISMATCH);
			deactivate_slab(s, page, c->मुक्तlist, c);
			जाओ new_slab;
		पूर्ण
	पूर्ण

	/*
	 * By rights, we should be searching क्रम a slab page that was
	 * PFMEMALLOC but right now, we are losing the pfmeदो_स्मृति
	 * inक्रमmation when the page leaves the per-cpu allocator
	 */
	अगर (unlikely(!pfmeदो_स्मृति_match(page, gfpflags))) अणु
		deactivate_slab(s, page, c->मुक्तlist, c);
		जाओ new_slab;
	पूर्ण

	/* must check again c->मुक्तlist in हाल of cpu migration or IRQ */
	मुक्तlist = c->मुक्तlist;
	अगर (मुक्तlist)
		जाओ load_मुक्तlist;

	मुक्तlist = get_मुक्तlist(s, page);

	अगर (!मुक्तlist) अणु
		c->page = शून्य;
		stat(s, DEACTIVATE_BYPASS);
		जाओ new_slab;
	पूर्ण

	stat(s, ALLOC_REFILL);

load_मुक्तlist:
	/*
	 * मुक्तlist is poपूर्णांकing to the list of objects to be used.
	 * page is poपूर्णांकing to the page from which the objects are obtained.
	 * That page must be frozen क्रम per cpu allocations to work.
	 */
	VM_BUG_ON(!c->page->frozen);
	c->मुक्तlist = get_मुक्तpoपूर्णांकer(s, मुक्तlist);
	c->tid = next_tid(c->tid);
	वापस मुक्तlist;

new_slab:

	अगर (slub_percpu_partial(c)) अणु
		page = c->page = slub_percpu_partial(c);
		slub_set_percpu_partial(c, page);
		stat(s, CPU_PARTIAL_ALLOC);
		जाओ reकरो;
	पूर्ण

	मुक्तlist = new_slab_objects(s, gfpflags, node, &c);

	अगर (unlikely(!मुक्तlist)) अणु
		slab_out_of_memory(s, gfpflags, node);
		वापस शून्य;
	पूर्ण

	page = c->page;
	अगर (likely(!kmem_cache_debug(s) && pfmeदो_स्मृति_match(page, gfpflags)))
		जाओ load_मुक्तlist;

	/* Only entered in the debug हाल */
	अगर (kmem_cache_debug(s) &&
			!alloc_debug_processing(s, page, मुक्तlist, addr))
		जाओ new_slab;	/* Slab failed checks. Next slab needed */

	deactivate_slab(s, page, get_मुक्तpoपूर्णांकer(s, मुक्तlist), c);
	वापस मुक्तlist;
पूर्ण

/*
 * Another one that disabled पूर्णांकerrupt and compensates क्रम possible
 * cpu changes by refetching the per cpu area poपूर्णांकer.
 */
अटल व्योम *__slab_alloc(काष्ठा kmem_cache *s, gfp_t gfpflags, पूर्णांक node,
			  अचिन्हित दीर्घ addr, काष्ठा kmem_cache_cpu *c)
अणु
	व्योम *p;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
#अगर_घोषित CONFIG_PREEMPTION
	/*
	 * We may have been preempted and rescheduled on a dअगरferent
	 * cpu beक्रमe disabling पूर्णांकerrupts. Need to reload cpu area
	 * poपूर्णांकer.
	 */
	c = this_cpu_ptr(s->cpu_slab);
#पूर्ण_अगर

	p = ___slab_alloc(s, gfpflags, node, addr, c);
	local_irq_restore(flags);
	वापस p;
पूर्ण

/*
 * If the object has been wiped upon मुक्त, make sure it's fully initialized by
 * zeroing out मुक्तlist poपूर्णांकer.
 */
अटल __always_अंतरभूत व्योम maybe_wipe_obj_मुक्तptr(काष्ठा kmem_cache *s,
						   व्योम *obj)
अणु
	अगर (unlikely(slab_want_init_on_मुक्त(s)) && obj)
		स_रखो((व्योम *)((अक्षर *)kasan_reset_tag(obj) + s->offset),
			0, माप(व्योम *));
पूर्ण

/*
 * Inlined fastpath so that allocation functions (kदो_स्मृति, kmem_cache_alloc)
 * have the fastpath folded पूर्णांकo their functions. So no function call
 * overhead क्रम requests that can be satisfied on the fastpath.
 *
 * The fastpath works by first checking अगर the lockless मुक्तlist can be used.
 * If not then __slab_alloc is called क्रम slow processing.
 *
 * Otherwise we can simply pick the next object from the lockless मुक्त list.
 */
अटल __always_अंतरभूत व्योम *slab_alloc_node(काष्ठा kmem_cache *s,
		gfp_t gfpflags, पूर्णांक node, अचिन्हित दीर्घ addr, माप_प्रकार orig_size)
अणु
	व्योम *object;
	काष्ठा kmem_cache_cpu *c;
	काष्ठा page *page;
	अचिन्हित दीर्घ tid;
	काष्ठा obj_cgroup *objcg = शून्य;
	bool init = false;

	s = slab_pre_alloc_hook(s, &objcg, 1, gfpflags);
	अगर (!s)
		वापस शून्य;

	object = kfence_alloc(s, orig_size, gfpflags);
	अगर (unlikely(object))
		जाओ out;

reकरो:
	/*
	 * Must पढ़ो kmem_cache cpu data via this cpu ptr. Preemption is
	 * enabled. We may चयन back and क्रमth between cpus जबतक
	 * पढ़ोing from one cpu area. That करोes not matter as दीर्घ
	 * as we end up on the original cpu again when करोing the cmpxchg.
	 *
	 * We should guarantee that tid and kmem_cache are retrieved on
	 * the same cpu. It could be dअगरferent अगर CONFIG_PREEMPTION so we need
	 * to check अगर it is matched or not.
	 */
	करो अणु
		tid = this_cpu_पढ़ो(s->cpu_slab->tid);
		c = raw_cpu_ptr(s->cpu_slab);
	पूर्ण जबतक (IS_ENABLED(CONFIG_PREEMPTION) &&
		 unlikely(tid != READ_ONCE(c->tid)));

	/*
	 * Irqless object alloc/मुक्त algorithm used here depends on sequence
	 * of fetching cpu_slab's data. tid should be fetched beक्रमe anything
	 * on c to guarantee that object and page associated with previous tid
	 * won't be used with current tid. If we fetch tid first, object and
	 * page could be one associated with next tid and our alloc/मुक्त
	 * request will be failed. In this हाल, we will retry. So, no problem.
	 */
	barrier();

	/*
	 * The transaction ids are globally unique per cpu and per operation on
	 * a per cpu queue. Thus they can be guarantee that the cmpxchg_द्विगुन
	 * occurs on the right processor and that there was no operation on the
	 * linked list in between.
	 */

	object = c->मुक्तlist;
	page = c->page;
	अगर (unlikely(!object || !page || !node_match(page, node))) अणु
		object = __slab_alloc(s, gfpflags, node, addr, c);
	पूर्ण अन्यथा अणु
		व्योम *next_object = get_मुक्तpoपूर्णांकer_safe(s, object);

		/*
		 * The cmpxchg will only match अगर there was no additional
		 * operation and अगर we are on the right processor.
		 *
		 * The cmpxchg करोes the following atomically (without lock
		 * semantics!)
		 * 1. Relocate first poपूर्णांकer to the current per cpu area.
		 * 2. Verअगरy that tid and मुक्तlist have not been changed
		 * 3. If they were not changed replace tid and मुक्तlist
		 *
		 * Since this is without lock semantics the protection is only
		 * against code executing on this cpu *not* from access by
		 * other cpus.
		 */
		अगर (unlikely(!this_cpu_cmpxchg_द्विगुन(
				s->cpu_slab->मुक्तlist, s->cpu_slab->tid,
				object, tid,
				next_object, next_tid(tid)))) अणु

			note_cmpxchg_failure("slab_alloc", s, tid);
			जाओ reकरो;
		पूर्ण
		prefetch_मुक्तpoपूर्णांकer(s, next_object);
		stat(s, ALLOC_FASTPATH);
	पूर्ण

	maybe_wipe_obj_मुक्तptr(s, object);
	init = slab_want_init_on_alloc(gfpflags, s);

out:
	slab_post_alloc_hook(s, objcg, gfpflags, 1, &object, init);

	वापस object;
पूर्ण

अटल __always_अंतरभूत व्योम *slab_alloc(काष्ठा kmem_cache *s,
		gfp_t gfpflags, अचिन्हित दीर्घ addr, माप_प्रकार orig_size)
अणु
	वापस slab_alloc_node(s, gfpflags, NUMA_NO_NODE, addr, orig_size);
पूर्ण

व्योम *kmem_cache_alloc(काष्ठा kmem_cache *s, gfp_t gfpflags)
अणु
	व्योम *ret = slab_alloc(s, gfpflags, _RET_IP_, s->object_size);

	trace_kmem_cache_alloc(_RET_IP_, ret, s->object_size,
				s->size, gfpflags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc);

#अगर_घोषित CONFIG_TRACING
व्योम *kmem_cache_alloc_trace(काष्ठा kmem_cache *s, gfp_t gfpflags, माप_प्रकार size)
अणु
	व्योम *ret = slab_alloc(s, gfpflags, _RET_IP_, size);
	trace_kदो_स्मृति(_RET_IP_, ret, size, s->size, gfpflags);
	ret = kasan_kदो_स्मृति(s, ret, size, gfpflags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_trace);
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA
व्योम *kmem_cache_alloc_node(काष्ठा kmem_cache *s, gfp_t gfpflags, पूर्णांक node)
अणु
	व्योम *ret = slab_alloc_node(s, gfpflags, node, _RET_IP_, s->object_size);

	trace_kmem_cache_alloc_node(_RET_IP_, ret,
				    s->object_size, s->size, gfpflags, node);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_node);

#अगर_घोषित CONFIG_TRACING
व्योम *kmem_cache_alloc_node_trace(काष्ठा kmem_cache *s,
				    gfp_t gfpflags,
				    पूर्णांक node, माप_प्रकार size)
अणु
	व्योम *ret = slab_alloc_node(s, gfpflags, node, _RET_IP_, size);

	trace_kदो_स्मृति_node(_RET_IP_, ret,
			   size, s->size, gfpflags, node);

	ret = kasan_kदो_स्मृति(s, ret, size, gfpflags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_node_trace);
#पूर्ण_अगर
#पूर्ण_अगर	/* CONFIG_NUMA */

/*
 * Slow path handling. This may still be called frequently since objects
 * have a दीर्घer lअगरeसमय than the cpu sद_असल in most processing loads.
 *
 * So we still attempt to reduce cache line usage. Just take the slab
 * lock and मुक्त the item. If there is no additional partial page
 * handling required then we can वापस immediately.
 */
अटल व्योम __slab_मुक्त(काष्ठा kmem_cache *s, काष्ठा page *page,
			व्योम *head, व्योम *tail, पूर्णांक cnt,
			अचिन्हित दीर्घ addr)

अणु
	व्योम *prior;
	पूर्णांक was_frozen;
	काष्ठा page new;
	अचिन्हित दीर्घ counters;
	काष्ठा kmem_cache_node *n = शून्य;
	अचिन्हित दीर्घ flags;

	stat(s, FREE_SLOWPATH);

	अगर (kfence_मुक्त(head))
		वापस;

	अगर (kmem_cache_debug(s) &&
	    !मुक्त_debug_processing(s, page, head, tail, cnt, addr))
		वापस;

	करो अणु
		अगर (unlikely(n)) अणु
			spin_unlock_irqrestore(&n->list_lock, flags);
			n = शून्य;
		पूर्ण
		prior = page->मुक्तlist;
		counters = page->counters;
		set_मुक्तpoपूर्णांकer(s, tail, prior);
		new.counters = counters;
		was_frozen = new.frozen;
		new.inuse -= cnt;
		अगर ((!new.inuse || !prior) && !was_frozen) अणु

			अगर (kmem_cache_has_cpu_partial(s) && !prior) अणु

				/*
				 * Slab was on no list beक्रमe and will be
				 * partially empty
				 * We can defer the list move and instead
				 * मुक्तze it.
				 */
				new.frozen = 1;

			पूर्ण अन्यथा अणु /* Needs to be taken off a list */

				n = get_node(s, page_to_nid(page));
				/*
				 * Speculatively acquire the list_lock.
				 * If the cmpxchg करोes not succeed then we may
				 * drop the list_lock without any processing.
				 *
				 * Otherwise the list_lock will synchronize with
				 * other processors updating the list of sद_असल.
				 */
				spin_lock_irqsave(&n->list_lock, flags);

			पूर्ण
		पूर्ण

	पूर्ण जबतक (!cmpxchg_द्विगुन_slab(s, page,
		prior, counters,
		head, new.counters,
		"__slab_free"));

	अगर (likely(!n)) अणु

		अगर (likely(was_frozen)) अणु
			/*
			 * The list lock was not taken thereक्रमe no list
			 * activity can be necessary.
			 */
			stat(s, FREE_FROZEN);
		पूर्ण अन्यथा अगर (new.frozen) अणु
			/*
			 * If we just froze the page then put it onto the
			 * per cpu partial list.
			 */
			put_cpu_partial(s, page, 1);
			stat(s, CPU_PARTIAL_FREE);
		पूर्ण

		वापस;
	पूर्ण

	अगर (unlikely(!new.inuse && n->nr_partial >= s->min_partial))
		जाओ slab_empty;

	/*
	 * Objects left in the slab. If it was not on the partial list beक्रमe
	 * then add it.
	 */
	अगर (!kmem_cache_has_cpu_partial(s) && unlikely(!prior)) अणु
		हटाओ_full(s, n, page);
		add_partial(n, page, DEACTIVATE_TO_TAIL);
		stat(s, FREE_ADD_PARTIAL);
	पूर्ण
	spin_unlock_irqrestore(&n->list_lock, flags);
	वापस;

slab_empty:
	अगर (prior) अणु
		/*
		 * Slab on the partial list.
		 */
		हटाओ_partial(n, page);
		stat(s, FREE_REMOVE_PARTIAL);
	पूर्ण अन्यथा अणु
		/* Slab must be on the full list */
		हटाओ_full(s, n, page);
	पूर्ण

	spin_unlock_irqrestore(&n->list_lock, flags);
	stat(s, FREE_SLAB);
	discard_slab(s, page);
पूर्ण

/*
 * Fastpath with क्रमced inlining to produce a kमुक्त and kmem_cache_मुक्त that
 * can perक्रमm fastpath मुक्तing without additional function calls.
 *
 * The fastpath is only possible अगर we are मुक्तing to the current cpu slab
 * of this processor. This typically the हाल अगर we have just allocated
 * the item beक्रमe.
 *
 * If fastpath is not possible then fall back to __slab_मुक्त where we deal
 * with all sorts of special processing.
 *
 * Bulk मुक्त of a मुक्तlist with several objects (all poपूर्णांकing to the
 * same page) possible by specअगरying head and tail ptr, plus objects
 * count (cnt). Bulk मुक्त indicated by tail poपूर्णांकer being set.
 */
अटल __always_अंतरभूत व्योम करो_slab_मुक्त(काष्ठा kmem_cache *s,
				काष्ठा page *page, व्योम *head, व्योम *tail,
				पूर्णांक cnt, अचिन्हित दीर्घ addr)
अणु
	व्योम *tail_obj = tail ? : head;
	काष्ठा kmem_cache_cpu *c;
	अचिन्हित दीर्घ tid;

	memcg_slab_मुक्त_hook(s, &head, 1);
reकरो:
	/*
	 * Determine the currently cpus per cpu slab.
	 * The cpu may change afterward. However that करोes not matter since
	 * data is retrieved via this poपूर्णांकer. If we are on the same cpu
	 * during the cmpxchg then the मुक्त will succeed.
	 */
	करो अणु
		tid = this_cpu_पढ़ो(s->cpu_slab->tid);
		c = raw_cpu_ptr(s->cpu_slab);
	पूर्ण जबतक (IS_ENABLED(CONFIG_PREEMPTION) &&
		 unlikely(tid != READ_ONCE(c->tid)));

	/* Same with comment on barrier() in slab_alloc_node() */
	barrier();

	अगर (likely(page == c->page)) अणु
		व्योम **मुक्तlist = READ_ONCE(c->मुक्तlist);

		set_मुक्तpoपूर्णांकer(s, tail_obj, मुक्तlist);

		अगर (unlikely(!this_cpu_cmpxchg_द्विगुन(
				s->cpu_slab->मुक्तlist, s->cpu_slab->tid,
				मुक्तlist, tid,
				head, next_tid(tid)))) अणु

			note_cmpxchg_failure("slab_free", s, tid);
			जाओ reकरो;
		पूर्ण
		stat(s, FREE_FASTPATH);
	पूर्ण अन्यथा
		__slab_मुक्त(s, page, head, tail_obj, cnt, addr);

पूर्ण

अटल __always_अंतरभूत व्योम slab_मुक्त(काष्ठा kmem_cache *s, काष्ठा page *page,
				      व्योम *head, व्योम *tail, पूर्णांक cnt,
				      अचिन्हित दीर्घ addr)
अणु
	/*
	 * With KASAN enabled slab_मुक्त_मुक्तlist_hook modअगरies the मुक्तlist
	 * to हटाओ objects, whose reuse must be delayed.
	 */
	अगर (slab_मुक्त_मुक्तlist_hook(s, &head, &tail))
		करो_slab_मुक्त(s, page, head, tail, cnt, addr);
पूर्ण

#अगर_घोषित CONFIG_KASAN_GENERIC
व्योम ___cache_मुक्त(काष्ठा kmem_cache *cache, व्योम *x, अचिन्हित दीर्घ addr)
अणु
	करो_slab_मुक्त(cache, virt_to_head_page(x), x, शून्य, 1, addr);
पूर्ण
#पूर्ण_अगर

व्योम kmem_cache_मुक्त(काष्ठा kmem_cache *s, व्योम *x)
अणु
	s = cache_from_obj(s, x);
	अगर (!s)
		वापस;
	slab_मुक्त(s, virt_to_head_page(x), x, शून्य, 1, _RET_IP_);
	trace_kmem_cache_मुक्त(_RET_IP_, x, s->name);
पूर्ण
EXPORT_SYMBOL(kmem_cache_मुक्त);

काष्ठा detached_मुक्तlist अणु
	काष्ठा page *page;
	व्योम *tail;
	व्योम *मुक्तlist;
	पूर्णांक cnt;
	काष्ठा kmem_cache *s;
पूर्ण;

/*
 * This function progressively scans the array with मुक्त objects (with
 * a limited look ahead) and extract objects beदीर्घing to the same
 * page.  It builds a detached मुक्तlist directly within the given
 * page/objects.  This can happen without any need क्रम
 * synchronization, because the objects are owned by running process.
 * The मुक्तlist is build up as a single linked list in the objects.
 * The idea is, that this detached मुक्तlist can then be bulk
 * transferred to the real मुक्तlist(s), but only requiring a single
 * synchronization primitive.  Look ahead in the array is limited due
 * to perक्रमmance reasons.
 */
अटल अंतरभूत
पूर्णांक build_detached_मुक्तlist(काष्ठा kmem_cache *s, माप_प्रकार size,
			    व्योम **p, काष्ठा detached_मुक्तlist *df)
अणु
	माप_प्रकार first_skipped_index = 0;
	पूर्णांक lookahead = 3;
	व्योम *object;
	काष्ठा page *page;

	/* Always re-init detached_मुक्तlist */
	df->page = शून्य;

	करो अणु
		object = p[--size];
		/* Do we need !ZERO_OR_शून्य_PTR(object) here? (क्रम kमुक्त) */
	पूर्ण जबतक (!object && size);

	अगर (!object)
		वापस 0;

	page = virt_to_head_page(object);
	अगर (!s) अणु
		/* Handle kalloc'ed objects */
		अगर (unlikely(!PageSlab(page))) अणु
			BUG_ON(!PageCompound(page));
			kमुक्त_hook(object);
			__मुक्त_pages(page, compound_order(page));
			p[size] = शून्य; /* mark object processed */
			वापस size;
		पूर्ण
		/* Derive kmem_cache from object */
		df->s = page->slab_cache;
	पूर्ण अन्यथा अणु
		df->s = cache_from_obj(s, object); /* Support क्रम memcg */
	पूर्ण

	अगर (is_kfence_address(object)) अणु
		slab_मुक्त_hook(df->s, object, false);
		__kfence_मुक्त(object);
		p[size] = शून्य; /* mark object processed */
		वापस size;
	पूर्ण

	/* Start new detached मुक्तlist */
	df->page = page;
	set_मुक्तpoपूर्णांकer(df->s, object, शून्य);
	df->tail = object;
	df->मुक्तlist = object;
	p[size] = शून्य; /* mark object processed */
	df->cnt = 1;

	जबतक (size) अणु
		object = p[--size];
		अगर (!object)
			जारी; /* Skip processed objects */

		/* df->page is always set at this poपूर्णांक */
		अगर (df->page == virt_to_head_page(object)) अणु
			/* Opportunity build मुक्तlist */
			set_मुक्तpoपूर्णांकer(df->s, object, df->मुक्तlist);
			df->मुक्तlist = object;
			df->cnt++;
			p[size] = शून्य; /* mark object processed */

			जारी;
		पूर्ण

		/* Limit look ahead search */
		अगर (!--lookahead)
			अवरोध;

		अगर (!first_skipped_index)
			first_skipped_index = size + 1;
	पूर्ण

	वापस first_skipped_index;
पूर्ण

/* Note that पूर्णांकerrupts must be enabled when calling this function. */
व्योम kmem_cache_मुक्त_bulk(काष्ठा kmem_cache *s, माप_प्रकार size, व्योम **p)
अणु
	अगर (WARN_ON(!size))
		वापस;

	memcg_slab_मुक्त_hook(s, p, size);
	करो अणु
		काष्ठा detached_मुक्तlist df;

		size = build_detached_मुक्तlist(s, size, p, &df);
		अगर (!df.page)
			जारी;

		slab_मुक्त(df.s, df.page, df.मुक्तlist, df.tail, df.cnt, _RET_IP_);
	पूर्ण जबतक (likely(size));
पूर्ण
EXPORT_SYMBOL(kmem_cache_मुक्त_bulk);

/* Note that पूर्णांकerrupts must be enabled when calling this function. */
पूर्णांक kmem_cache_alloc_bulk(काष्ठा kmem_cache *s, gfp_t flags, माप_प्रकार size,
			  व्योम **p)
अणु
	काष्ठा kmem_cache_cpu *c;
	पूर्णांक i;
	काष्ठा obj_cgroup *objcg = शून्य;

	/* memcg and kmem_cache debug support */
	s = slab_pre_alloc_hook(s, &objcg, size, flags);
	अगर (unlikely(!s))
		वापस false;
	/*
	 * Drain objects in the per cpu slab, जबतक disabling local
	 * IRQs, which protects against PREEMPT and पूर्णांकerrupts
	 * handlers invoking normal fastpath.
	 */
	local_irq_disable();
	c = this_cpu_ptr(s->cpu_slab);

	क्रम (i = 0; i < size; i++) अणु
		व्योम *object = kfence_alloc(s, s->object_size, flags);

		अगर (unlikely(object)) अणु
			p[i] = object;
			जारी;
		पूर्ण

		object = c->मुक्तlist;
		अगर (unlikely(!object)) अणु
			/*
			 * We may have हटाओd an object from c->मुक्तlist using
			 * the fastpath in the previous iteration; in that हाल,
			 * c->tid has not been bumped yet.
			 * Since ___slab_alloc() may reenable पूर्णांकerrupts जबतक
			 * allocating memory, we should bump c->tid now.
			 */
			c->tid = next_tid(c->tid);

			/*
			 * Invoking slow path likely have side-effect
			 * of re-populating per CPU c->मुक्तlist
			 */
			p[i] = ___slab_alloc(s, flags, NUMA_NO_NODE,
					    _RET_IP_, c);
			अगर (unlikely(!p[i]))
				जाओ error;

			c = this_cpu_ptr(s->cpu_slab);
			maybe_wipe_obj_मुक्तptr(s, p[i]);

			जारी; /* जाओ क्रम-loop */
		पूर्ण
		c->मुक्तlist = get_मुक्तpoपूर्णांकer(s, object);
		p[i] = object;
		maybe_wipe_obj_मुक्तptr(s, p[i]);
	पूर्ण
	c->tid = next_tid(c->tid);
	local_irq_enable();

	/*
	 * memcg and kmem_cache debug support and memory initialization.
	 * Done outside of the IRQ disabled fastpath loop.
	 */
	slab_post_alloc_hook(s, objcg, flags, size, p,
				slab_want_init_on_alloc(flags, s));
	वापस i;
error:
	local_irq_enable();
	slab_post_alloc_hook(s, objcg, flags, i, p, false);
	__kmem_cache_मुक्त_bulk(s, i, p);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_bulk);


/*
 * Object placement in a slab is made very easy because we always start at
 * offset 0. If we tune the size of the object to the alignment then we can
 * get the required alignment by putting one properly sized object after
 * another.
 *
 * Notice that the allocation order determines the sizes of the per cpu
 * caches. Each processor has always one slab available क्रम allocations.
 * Increasing the allocation order reduces the number of बार that sद_असल
 * must be moved on and off the partial lists and is thereक्रमe a factor in
 * locking overhead.
 */

/*
 * Minimum / Maximum order of slab pages. This influences locking overhead
 * and slab fragmentation. A higher order reduces the number of partial sद_असल
 * and increases the number of allocations possible without having to
 * take the list_lock.
 */
अटल अचिन्हित पूर्णांक slub_min_order;
अटल अचिन्हित पूर्णांक slub_max_order = PAGE_ALLOC_COSTLY_ORDER;
अटल अचिन्हित पूर्णांक slub_min_objects;

/*
 * Calculate the order of allocation given an slab object size.
 *
 * The order of allocation has signअगरicant impact on perक्रमmance and other
 * प्रणाली components. Generally order 0 allocations should be preferred since
 * order 0 करोes not cause fragmentation in the page allocator. Larger objects
 * be problematic to put पूर्णांकo order 0 sद_असल because there may be too much
 * unused space left. We go to a higher order अगर more than 1/16th of the slab
 * would be wasted.
 *
 * In order to reach satisfactory perक्रमmance we must ensure that a minimum
 * number of objects is in one slab. Otherwise we may generate too much
 * activity on the partial lists which requires taking the list_lock. This is
 * less a concern क्रम large sद_असल though which are rarely used.
 *
 * slub_max_order specअगरies the order where we begin to stop considering the
 * number of objects in a slab as critical. If we reach slub_max_order then
 * we try to keep the page order as low as possible. So we accept more waste
 * of space in favor of a small page order.
 *
 * Higher order allocations also allow the placement of more objects in a
 * slab and thereby reduce object handling overhead. If the user has
 * requested a higher minimum order then we start with that one instead of
 * the smallest order which will fit the object.
 */
अटल अंतरभूत अचिन्हित पूर्णांक slab_order(अचिन्हित पूर्णांक size,
		अचिन्हित पूर्णांक min_objects, अचिन्हित पूर्णांक max_order,
		अचिन्हित पूर्णांक fract_leftover)
अणु
	अचिन्हित पूर्णांक min_order = slub_min_order;
	अचिन्हित पूर्णांक order;

	अगर (order_objects(min_order, size) > MAX_OBJS_PER_PAGE)
		वापस get_order(size * MAX_OBJS_PER_PAGE) - 1;

	क्रम (order = max(min_order, (अचिन्हित पूर्णांक)get_order(min_objects * size));
			order <= max_order; order++) अणु

		अचिन्हित पूर्णांक slab_size = (अचिन्हित पूर्णांक)PAGE_SIZE << order;
		अचिन्हित पूर्णांक rem;

		rem = slab_size % size;

		अगर (rem <= slab_size / fract_leftover)
			अवरोध;
	पूर्ण

	वापस order;
पूर्ण

अटल अंतरभूत पूर्णांक calculate_order(अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक order;
	अचिन्हित पूर्णांक min_objects;
	अचिन्हित पूर्णांक max_objects;
	अचिन्हित पूर्णांक nr_cpus;

	/*
	 * Attempt to find best configuration क्रम a slab. This
	 * works by first attempting to generate a layout with
	 * the best configuration and backing off gradually.
	 *
	 * First we increase the acceptable waste in a slab. Then
	 * we reduce the minimum objects required in a slab.
	 */
	min_objects = slub_min_objects;
	अगर (!min_objects) अणु
		/*
		 * Some architectures will only update present cpus when
		 * onlining them, so करोn't trust the number if it's just 1. But
		 * we also करोn't want to use nr_cpu_ids always, as on some other
		 * architectures, there can be many possible cpus, but never
		 * onlined. Here we compromise between trying to aव्योम too high
		 * order on प्रणालीs that appear larger than they are, and too
		 * low order on प्रणालीs that appear smaller than they are.
		 */
		nr_cpus = num_present_cpus();
		अगर (nr_cpus <= 1)
			nr_cpus = nr_cpu_ids;
		min_objects = 4 * (fls(nr_cpus) + 1);
	पूर्ण
	max_objects = order_objects(slub_max_order, size);
	min_objects = min(min_objects, max_objects);

	जबतक (min_objects > 1) अणु
		अचिन्हित पूर्णांक fraction;

		fraction = 16;
		जबतक (fraction >= 4) अणु
			order = slab_order(size, min_objects,
					slub_max_order, fraction);
			अगर (order <= slub_max_order)
				वापस order;
			fraction /= 2;
		पूर्ण
		min_objects--;
	पूर्ण

	/*
	 * We were unable to place multiple objects in a slab. Now
	 * lets see अगर we can place a single object there.
	 */
	order = slab_order(size, 1, slub_max_order, 1);
	अगर (order <= slub_max_order)
		वापस order;

	/*
	 * Doh this slab cannot be placed using slub_max_order.
	 */
	order = slab_order(size, 1, MAX_ORDER, 1);
	अगर (order < MAX_ORDER)
		वापस order;
	वापस -ENOSYS;
पूर्ण

अटल व्योम
init_kmem_cache_node(काष्ठा kmem_cache_node *n)
अणु
	n->nr_partial = 0;
	spin_lock_init(&n->list_lock);
	INIT_LIST_HEAD(&n->partial);
#अगर_घोषित CONFIG_SLUB_DEBUG
	atomic_दीर्घ_set(&n->nr_sद_असल, 0);
	atomic_दीर्घ_set(&n->total_objects, 0);
	INIT_LIST_HEAD(&n->full);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक alloc_kmem_cache_cpus(काष्ठा kmem_cache *s)
अणु
	BUILD_BUG_ON(PERCPU_DYNAMIC_EARLY_SIZE <
			KMALLOC_SHIFT_HIGH * माप(काष्ठा kmem_cache_cpu));

	/*
	 * Must align to द्विगुन word boundary क्रम the द्विगुन cmpxchg
	 * inकाष्ठाions to work; see __pcpu_द्विगुन_call_वापस_bool().
	 */
	s->cpu_slab = __alloc_percpu(माप(काष्ठा kmem_cache_cpu),
				     2 * माप(व्योम *));

	अगर (!s->cpu_slab)
		वापस 0;

	init_kmem_cache_cpus(s);

	वापस 1;
पूर्ण

अटल काष्ठा kmem_cache *kmem_cache_node;

/*
 * No kदो_स्मृति_node yet so करो it by hand. We know that this is the first
 * slab on the node क्रम this slabcache. There are no concurrent accesses
 * possible.
 *
 * Note that this function only works on the kmem_cache_node
 * when allocating क्रम the kmem_cache_node. This is used क्रम bootstrapping
 * memory on a fresh node that has no slab काष्ठाures yet.
 */
अटल व्योम early_kmem_cache_node_alloc(पूर्णांक node)
अणु
	काष्ठा page *page;
	काष्ठा kmem_cache_node *n;

	BUG_ON(kmem_cache_node->size < माप(काष्ठा kmem_cache_node));

	page = new_slab(kmem_cache_node, GFP_NOWAIT, node);

	BUG_ON(!page);
	अगर (page_to_nid(page) != node) अणु
		pr_err("SLUB: Unable to allocate memory from node %d\n", node);
		pr_err("SLUB: Allocating a useless per node structure in order to be able to continue\n");
	पूर्ण

	n = page->मुक्तlist;
	BUG_ON(!n);
#अगर_घोषित CONFIG_SLUB_DEBUG
	init_object(kmem_cache_node, n, SLUB_RED_ACTIVE);
	init_tracking(kmem_cache_node, n);
#पूर्ण_अगर
	n = kasan_slab_alloc(kmem_cache_node, n, GFP_KERNEL, false);
	page->मुक्तlist = get_मुक्तpoपूर्णांकer(kmem_cache_node, n);
	page->inuse = 1;
	page->frozen = 0;
	kmem_cache_node->node[node] = n;
	init_kmem_cache_node(n);
	inc_sद_असल_node(kmem_cache_node, node, page->objects);

	/*
	 * No locks need to be taken here as it has just been
	 * initialized and there is no concurrent access.
	 */
	__add_partial(n, page, DEACTIVATE_TO_HEAD);
पूर्ण

अटल व्योम मुक्त_kmem_cache_nodes(काष्ठा kmem_cache *s)
अणु
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	क्रम_each_kmem_cache_node(s, node, n) अणु
		s->node[node] = शून्य;
		kmem_cache_मुक्त(kmem_cache_node, n);
	पूर्ण
पूर्ण

व्योम __kmem_cache_release(काष्ठा kmem_cache *s)
अणु
	cache_अक्रमom_seq_destroy(s);
	मुक्त_percpu(s->cpu_slab);
	मुक्त_kmem_cache_nodes(s);
पूर्ण

अटल पूर्णांक init_kmem_cache_nodes(काष्ठा kmem_cache *s)
अणु
	पूर्णांक node;

	क्रम_each_node_mask(node, slab_nodes) अणु
		काष्ठा kmem_cache_node *n;

		अगर (slab_state == DOWN) अणु
			early_kmem_cache_node_alloc(node);
			जारी;
		पूर्ण
		n = kmem_cache_alloc_node(kmem_cache_node,
						GFP_KERNEL, node);

		अगर (!n) अणु
			मुक्त_kmem_cache_nodes(s);
			वापस 0;
		पूर्ण

		init_kmem_cache_node(n);
		s->node[node] = n;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम set_min_partial(काष्ठा kmem_cache *s, अचिन्हित दीर्घ min)
अणु
	अगर (min < MIN_PARTIAL)
		min = MIN_PARTIAL;
	अन्यथा अगर (min > MAX_PARTIAL)
		min = MAX_PARTIAL;
	s->min_partial = min;
पूर्ण

अटल व्योम set_cpu_partial(काष्ठा kmem_cache *s)
अणु
#अगर_घोषित CONFIG_SLUB_CPU_PARTIAL
	/*
	 * cpu_partial determined the maximum number of objects kept in the
	 * per cpu partial lists of a processor.
	 *
	 * Per cpu partial lists मुख्यly contain sद_असल that just have one
	 * object मुक्तd. If they are used क्रम allocation then they can be
	 * filled up again with minimal efक्रमt. The slab will never hit the
	 * per node partial lists and thereक्रमe no locking will be required.
	 *
	 * This setting also determines
	 *
	 * A) The number of objects from per cpu partial sद_असल dumped to the
	 *    per node list when we reach the limit.
	 * B) The number of objects in cpu partial sद_असल to extract from the
	 *    per node list when we run out of per cpu objects. We only fetch
	 *    50% to keep some capacity around क्रम मुक्तs.
	 */
	अगर (!kmem_cache_has_cpu_partial(s))
		slub_set_cpu_partial(s, 0);
	अन्यथा अगर (s->size >= PAGE_SIZE)
		slub_set_cpu_partial(s, 2);
	अन्यथा अगर (s->size >= 1024)
		slub_set_cpu_partial(s, 6);
	अन्यथा अगर (s->size >= 256)
		slub_set_cpu_partial(s, 13);
	अन्यथा
		slub_set_cpu_partial(s, 30);
#पूर्ण_अगर
पूर्ण

/*
 * calculate_sizes() determines the order and the distribution of data within
 * a slab object.
 */
अटल पूर्णांक calculate_sizes(काष्ठा kmem_cache *s, पूर्णांक क्रमced_order)
अणु
	slab_flags_t flags = s->flags;
	अचिन्हित पूर्णांक size = s->object_size;
	अचिन्हित पूर्णांक order;

	/*
	 * Round up object size to the next word boundary. We can only
	 * place the मुक्त poपूर्णांकer at word boundaries and this determines
	 * the possible location of the मुक्त poपूर्णांकer.
	 */
	size = ALIGN(size, माप(व्योम *));

#अगर_घोषित CONFIG_SLUB_DEBUG
	/*
	 * Determine अगर we can poison the object itself. If the user of
	 * the slab may touch the object after मुक्त or beक्रमe allocation
	 * then we should never poison the object itself.
	 */
	अगर ((flags & SLAB_POISON) && !(flags & SLAB_TYPESAFE_BY_RCU) &&
			!s->ctor)
		s->flags |= __OBJECT_POISON;
	अन्यथा
		s->flags &= ~__OBJECT_POISON;


	/*
	 * If we are Redzoning then check अगर there is some space between the
	 * end of the object and the मुक्त poपूर्णांकer. If not then add an
	 * additional word to have some bytes to store Redzone inक्रमmation.
	 */
	अगर ((flags & SLAB_RED_ZONE) && size == s->object_size)
		size += माप(व्योम *);
#पूर्ण_अगर

	/*
	 * With that we have determined the number of bytes in actual use
	 * by the object and redzoning.
	 */
	s->inuse = size;

	अगर ((flags & (SLAB_TYPESAFE_BY_RCU | SLAB_POISON)) ||
	    ((flags & SLAB_RED_ZONE) && s->object_size < माप(व्योम *)) ||
	    s->ctor) अणु
		/*
		 * Relocate मुक्त poपूर्णांकer after the object अगर it is not
		 * permitted to overग_लिखो the first word of the object on
		 * kmem_cache_मुक्त.
		 *
		 * This is the हाल अगर we करो RCU, have a स्थिरructor or
		 * deकाष्ठाor, are poisoning the objects, or are
		 * redzoning an object smaller than माप(व्योम *).
		 *
		 * The assumption that s->offset >= s->inuse means मुक्त
		 * poपूर्णांकer is outside of the object is used in the
		 * मुक्तptr_outside_object() function. If that is no
		 * दीर्घer true, the function needs to be modअगरied.
		 */
		s->offset = size;
		size += माप(व्योम *);
	पूर्ण अन्यथा अणु
		/*
		 * Store मुक्तlist poपूर्णांकer near middle of object to keep
		 * it away from the edges of the object to aव्योम small
		 * sized over/underflows from neighboring allocations.
		 */
		s->offset = ALIGN_DOWN(s->object_size / 2, माप(व्योम *));
	पूर्ण

#अगर_घोषित CONFIG_SLUB_DEBUG
	अगर (flags & SLAB_STORE_USER)
		/*
		 * Need to store inक्रमmation about allocs and मुक्तs after
		 * the object.
		 */
		size += 2 * माप(काष्ठा track);
#पूर्ण_अगर

	kasan_cache_create(s, &size, &s->flags);
#अगर_घोषित CONFIG_SLUB_DEBUG
	अगर (flags & SLAB_RED_ZONE) अणु
		/*
		 * Add some empty padding so that we can catch
		 * overग_लिखोs from earlier objects rather than let
		 * tracking inक्रमmation or the मुक्त poपूर्णांकer be
		 * corrupted अगर a user ग_लिखोs beक्रमe the start
		 * of the object.
		 */
		size += माप(व्योम *);

		s->red_left_pad = माप(व्योम *);
		s->red_left_pad = ALIGN(s->red_left_pad, s->align);
		size += s->red_left_pad;
	पूर्ण
#पूर्ण_अगर

	/*
	 * SLUB stores one object immediately after another beginning from
	 * offset 0. In order to align the objects we have to simply size
	 * each object to conक्रमm to the alignment.
	 */
	size = ALIGN(size, s->align);
	s->size = size;
	s->reciprocal_size = reciprocal_value(size);
	अगर (क्रमced_order >= 0)
		order = क्रमced_order;
	अन्यथा
		order = calculate_order(size);

	अगर ((पूर्णांक)order < 0)
		वापस 0;

	s->allocflags = 0;
	अगर (order)
		s->allocflags |= __GFP_COMP;

	अगर (s->flags & SLAB_CACHE_DMA)
		s->allocflags |= GFP_DMA;

	अगर (s->flags & SLAB_CACHE_DMA32)
		s->allocflags |= GFP_DMA32;

	अगर (s->flags & SLAB_RECLAIM_ACCOUNT)
		s->allocflags |= __GFP_RECLAIMABLE;

	/*
	 * Determine the number of objects per slab
	 */
	s->oo = oo_make(order, size);
	s->min = oo_make(get_order(size), size);
	अगर (oo_objects(s->oo) > oo_objects(s->max))
		s->max = s->oo;

	वापस !!oo_objects(s->oo);
पूर्ण

अटल पूर्णांक kmem_cache_खोलो(काष्ठा kmem_cache *s, slab_flags_t flags)
अणु
	s->flags = kmem_cache_flags(s->size, flags, s->name);
#अगर_घोषित CONFIG_SLAB_FREELIST_HARDENED
	s->अक्रमom = get_अक्रमom_दीर्घ();
#पूर्ण_अगर

	अगर (!calculate_sizes(s, -1))
		जाओ error;
	अगर (disable_higher_order_debug) अणु
		/*
		 * Disable debugging flags that store metadata अगर the min slab
		 * order increased.
		 */
		अगर (get_order(s->size) > get_order(s->object_size)) अणु
			s->flags &= ~DEBUG_METADATA_FLAGS;
			s->offset = 0;
			अगर (!calculate_sizes(s, -1))
				जाओ error;
		पूर्ण
	पूर्ण

#अगर defined(CONFIG_HAVE_CMPXCHG_DOUBLE) && \
    defined(CONFIG_HAVE_ALIGNED_STRUCT_PAGE)
	अगर (प्रणाली_has_cmpxchg_द्विगुन() && (s->flags & SLAB_NO_CMPXCHG) == 0)
		/* Enable fast mode */
		s->flags |= __CMPXCHG_DOUBLE;
#पूर्ण_अगर

	/*
	 * The larger the object size is, the more pages we want on the partial
	 * list to aव्योम pounding the page allocator excessively.
	 */
	set_min_partial(s, ilog2(s->size) / 2);

	set_cpu_partial(s);

#अगर_घोषित CONFIG_NUMA
	s->remote_node_defrag_ratio = 1000;
#पूर्ण_अगर

	/* Initialize the pre-computed अक्रमomized मुक्तlist अगर slab is up */
	अगर (slab_state >= UP) अणु
		अगर (init_cache_अक्रमom_seq(s))
			जाओ error;
	पूर्ण

	अगर (!init_kmem_cache_nodes(s))
		जाओ error;

	अगर (alloc_kmem_cache_cpus(s))
		वापस 0;

	मुक्त_kmem_cache_nodes(s);
error:
	वापस -EINVAL;
पूर्ण

अटल व्योम list_slab_objects(काष्ठा kmem_cache *s, काष्ठा page *page,
			      स्थिर अक्षर *text)
अणु
#अगर_घोषित CONFIG_SLUB_DEBUG
	व्योम *addr = page_address(page);
	अचिन्हित दीर्घ *map;
	व्योम *p;

	slab_err(s, page, text, s->name);
	slab_lock(page);

	map = get_map(s, page);
	क्रम_each_object(p, s, addr, page->objects) अणु

		अगर (!test_bit(__obj_to_index(s, addr, p), map)) अणु
			pr_err("Object 0x%p @offset=%tu\n", p, p - addr);
			prपूर्णांक_tracking(s, p);
		पूर्ण
	पूर्ण
	put_map(map);
	slab_unlock(page);
#पूर्ण_अगर
पूर्ण

/*
 * Attempt to मुक्त all partial sद_असल on a node.
 * This is called from __kmem_cache_shutकरोwn(). We must take list_lock
 * because sysfs file might still access partial list after the shutकरोwning.
 */
अटल व्योम मुक्त_partial(काष्ठा kmem_cache *s, काष्ठा kmem_cache_node *n)
अणु
	LIST_HEAD(discard);
	काष्ठा page *page, *h;

	BUG_ON(irqs_disabled());
	spin_lock_irq(&n->list_lock);
	list_क्रम_each_entry_safe(page, h, &n->partial, slab_list) अणु
		अगर (!page->inuse) अणु
			हटाओ_partial(n, page);
			list_add(&page->slab_list, &discard);
		पूर्ण अन्यथा अणु
			list_slab_objects(s, page,
			  "Objects remaining in %s on __kmem_cache_shutdown()");
		पूर्ण
	पूर्ण
	spin_unlock_irq(&n->list_lock);

	list_क्रम_each_entry_safe(page, h, &discard, slab_list)
		discard_slab(s, page);
पूर्ण

bool __kmem_cache_empty(काष्ठा kmem_cache *s)
अणु
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	क्रम_each_kmem_cache_node(s, node, n)
		अगर (n->nr_partial || sद_असल_node(s, node))
			वापस false;
	वापस true;
पूर्ण

/*
 * Release all resources used by a slab cache.
 */
पूर्णांक __kmem_cache_shutकरोwn(काष्ठा kmem_cache *s)
अणु
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	flush_all(s);
	/* Attempt to मुक्त all objects */
	क्रम_each_kmem_cache_node(s, node, n) अणु
		मुक्त_partial(s, n);
		अगर (n->nr_partial || sद_असल_node(s, node))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PRINTK
व्योम kmem_obj_info(काष्ठा kmem_obj_info *kpp, व्योम *object, काष्ठा page *page)
अणु
	व्योम *base;
	पूर्णांक __maybe_unused i;
	अचिन्हित पूर्णांक objnr;
	व्योम *objp;
	व्योम *objp0;
	काष्ठा kmem_cache *s = page->slab_cache;
	काष्ठा track __maybe_unused *trackp;

	kpp->kp_ptr = object;
	kpp->kp_page = page;
	kpp->kp_slab_cache = s;
	base = page_address(page);
	objp0 = kasan_reset_tag(object);
#अगर_घोषित CONFIG_SLUB_DEBUG
	objp = restore_red_left(s, objp0);
#अन्यथा
	objp = objp0;
#पूर्ण_अगर
	objnr = obj_to_index(s, page, objp);
	kpp->kp_data_offset = (अचिन्हित दीर्घ)((अक्षर *)objp0 - (अक्षर *)objp);
	objp = base + s->size * objnr;
	kpp->kp_objp = objp;
	अगर (WARN_ON_ONCE(objp < base || objp >= base + page->objects * s->size || (objp - base) % s->size) ||
	    !(s->flags & SLAB_STORE_USER))
		वापस;
#अगर_घोषित CONFIG_SLUB_DEBUG
	trackp = get_track(s, objp, TRACK_ALLOC);
	kpp->kp_ret = (व्योम *)trackp->addr;
#अगर_घोषित CONFIG_STACKTRACE
	क्रम (i = 0; i < KS_ADDRS_COUNT && i < TRACK_ADDRS_COUNT; i++) अणु
		kpp->kp_stack[i] = (व्योम *)trackp->addrs[i];
		अगर (!kpp->kp_stack[i])
			अवरोध;
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

/********************************************************************
 *		Kदो_स्मृति subप्रणाली
 *******************************************************************/

अटल पूर्णांक __init setup_slub_min_order(अक्षर *str)
अणु
	get_option(&str, (पूर्णांक *)&slub_min_order);

	वापस 1;
पूर्ण

__setup("slub_min_order=", setup_slub_min_order);

अटल पूर्णांक __init setup_slub_max_order(अक्षर *str)
अणु
	get_option(&str, (पूर्णांक *)&slub_max_order);
	slub_max_order = min(slub_max_order, (अचिन्हित पूर्णांक)MAX_ORDER - 1);

	वापस 1;
पूर्ण

__setup("slub_max_order=", setup_slub_max_order);

अटल पूर्णांक __init setup_slub_min_objects(अक्षर *str)
अणु
	get_option(&str, (पूर्णांक *)&slub_min_objects);

	वापस 1;
पूर्ण

__setup("slub_min_objects=", setup_slub_min_objects);

व्योम *__kदो_स्मृति(माप_प्रकार size, gfp_t flags)
अणु
	काष्ठा kmem_cache *s;
	व्योम *ret;

	अगर (unlikely(size > KMALLOC_MAX_CACHE_SIZE))
		वापस kदो_स्मृति_large(size, flags);

	s = kदो_स्मृति_slab(size, flags);

	अगर (unlikely(ZERO_OR_शून्य_PTR(s)))
		वापस s;

	ret = slab_alloc(s, flags, _RET_IP_, size);

	trace_kदो_स्मृति(_RET_IP_, ret, size, s->size, flags);

	ret = kasan_kदो_स्मृति(s, ret, size, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति);

#अगर_घोषित CONFIG_NUMA
अटल व्योम *kदो_स्मृति_large_node(माप_प्रकार size, gfp_t flags, पूर्णांक node)
अणु
	काष्ठा page *page;
	व्योम *ptr = शून्य;
	अचिन्हित पूर्णांक order = get_order(size);

	flags |= __GFP_COMP;
	page = alloc_pages_node(node, flags, order);
	अगर (page) अणु
		ptr = page_address(page);
		mod_lruvec_page_state(page, NR_SLAB_UNRECLAIMABLE_B,
				      PAGE_SIZE << order);
	पूर्ण

	वापस kदो_स्मृति_large_node_hook(ptr, size, flags);
पूर्ण

व्योम *__kदो_स्मृति_node(माप_प्रकार size, gfp_t flags, पूर्णांक node)
अणु
	काष्ठा kmem_cache *s;
	व्योम *ret;

	अगर (unlikely(size > KMALLOC_MAX_CACHE_SIZE)) अणु
		ret = kदो_स्मृति_large_node(size, flags, node);

		trace_kदो_स्मृति_node(_RET_IP_, ret,
				   size, PAGE_SIZE << get_order(size),
				   flags, node);

		वापस ret;
	पूर्ण

	s = kदो_स्मृति_slab(size, flags);

	अगर (unlikely(ZERO_OR_शून्य_PTR(s)))
		वापस s;

	ret = slab_alloc_node(s, flags, node, _RET_IP_, size);

	trace_kदो_स्मृति_node(_RET_IP_, ret, size, s->size, flags, node);

	ret = kasan_kदो_स्मृति(s, ret, size, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति_node);
#पूर्ण_अगर	/* CONFIG_NUMA */

#अगर_घोषित CONFIG_HARDENED_USERCOPY
/*
 * Rejects incorrectly sized objects and objects that are to be copied
 * to/from userspace but करो not fall entirely within the containing slab
 * cache's usercopy region.
 *
 * Returns शून्य अगर check passes, otherwise स्थिर अक्षर * to name of cache
 * to indicate an error.
 */
व्योम __check_heap_object(स्थिर व्योम *ptr, अचिन्हित दीर्घ n, काष्ठा page *page,
			 bool to_user)
अणु
	काष्ठा kmem_cache *s;
	अचिन्हित पूर्णांक offset;
	माप_प्रकार object_size;
	bool is_kfence = is_kfence_address(ptr);

	ptr = kasan_reset_tag(ptr);

	/* Find object and usable object size. */
	s = page->slab_cache;

	/* Reject impossible poपूर्णांकers. */
	अगर (ptr < page_address(page))
		usercopy_पात("SLUB object not in SLUB page?!", शून्य,
			       to_user, 0, n);

	/* Find offset within object. */
	अगर (is_kfence)
		offset = ptr - kfence_object_start(ptr);
	अन्यथा
		offset = (ptr - page_address(page)) % s->size;

	/* Adjust क्रम redzone and reject अगर within the redzone. */
	अगर (!is_kfence && kmem_cache_debug_flags(s, SLAB_RED_ZONE)) अणु
		अगर (offset < s->red_left_pad)
			usercopy_पात("SLUB object in left red zone",
				       s->name, to_user, offset, n);
		offset -= s->red_left_pad;
	पूर्ण

	/* Allow address range falling entirely within usercopy region. */
	अगर (offset >= s->useroffset &&
	    offset - s->useroffset <= s->usersize &&
	    n <= s->useroffset - offset + s->usersize)
		वापस;

	/*
	 * If the copy is still within the allocated object, produce
	 * a warning instead of rejecting the copy. This is पूर्णांकended
	 * to be a temporary method to find any missing usercopy
	 * whitelists.
	 */
	object_size = slab_ksize(s);
	अगर (usercopy_fallback &&
	    offset <= object_size && n <= object_size - offset) अणु
		usercopy_warn("SLUB object", s->name, to_user, offset, n);
		वापस;
	पूर्ण

	usercopy_पात("SLUB object", s->name, to_user, offset, n);
पूर्ण
#पूर्ण_अगर /* CONFIG_HARDENED_USERCOPY */

माप_प्रकार __ksize(स्थिर व्योम *object)
अणु
	काष्ठा page *page;

	अगर (unlikely(object == ZERO_SIZE_PTR))
		वापस 0;

	page = virt_to_head_page(object);

	अगर (unlikely(!PageSlab(page))) अणु
		WARN_ON(!PageCompound(page));
		वापस page_size(page);
	पूर्ण

	वापस slab_ksize(page->slab_cache);
पूर्ण
EXPORT_SYMBOL(__ksize);

व्योम kमुक्त(स्थिर व्योम *x)
अणु
	काष्ठा page *page;
	व्योम *object = (व्योम *)x;

	trace_kमुक्त(_RET_IP_, x);

	अगर (unlikely(ZERO_OR_शून्य_PTR(x)))
		वापस;

	page = virt_to_head_page(x);
	अगर (unlikely(!PageSlab(page))) अणु
		अचिन्हित पूर्णांक order = compound_order(page);

		BUG_ON(!PageCompound(page));
		kमुक्त_hook(object);
		mod_lruvec_page_state(page, NR_SLAB_UNRECLAIMABLE_B,
				      -(PAGE_SIZE << order));
		__मुक्त_pages(page, order);
		वापस;
	पूर्ण
	slab_मुक्त(page->slab_cache, page, object, शून्य, 1, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(kमुक्त);

#घोषणा SHRINK_PROMOTE_MAX 32

/*
 * kmem_cache_shrink discards empty sद_असल and promotes the sद_असल filled
 * up most to the head of the partial lists. New allocations will then
 * fill those up and thus they can be हटाओd from the partial lists.
 *
 * The sद_असल with the least items are placed last. This results in them
 * being allocated from last increasing the chance that the last objects
 * are मुक्तd in them.
 */
पूर्णांक __kmem_cache_shrink(काष्ठा kmem_cache *s)
अणु
	पूर्णांक node;
	पूर्णांक i;
	काष्ठा kmem_cache_node *n;
	काष्ठा page *page;
	काष्ठा page *t;
	काष्ठा list_head discard;
	काष्ठा list_head promote[SHRINK_PROMOTE_MAX];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	flush_all(s);
	क्रम_each_kmem_cache_node(s, node, n) अणु
		INIT_LIST_HEAD(&discard);
		क्रम (i = 0; i < SHRINK_PROMOTE_MAX; i++)
			INIT_LIST_HEAD(promote + i);

		spin_lock_irqsave(&n->list_lock, flags);

		/*
		 * Build lists of sद_असल to discard or promote.
		 *
		 * Note that concurrent मुक्तs may occur जबतक we hold the
		 * list_lock. page->inuse here is the upper limit.
		 */
		list_क्रम_each_entry_safe(page, t, &n->partial, slab_list) अणु
			पूर्णांक मुक्त = page->objects - page->inuse;

			/* Do not reपढ़ो page->inuse */
			barrier();

			/* We करो not keep full sद_असल on the list */
			BUG_ON(मुक्त <= 0);

			अगर (मुक्त == page->objects) अणु
				list_move(&page->slab_list, &discard);
				n->nr_partial--;
			पूर्ण अन्यथा अगर (मुक्त <= SHRINK_PROMOTE_MAX)
				list_move(&page->slab_list, promote + मुक्त - 1);
		पूर्ण

		/*
		 * Promote the sद_असल filled up most to the head of the
		 * partial list.
		 */
		क्रम (i = SHRINK_PROMOTE_MAX - 1; i >= 0; i--)
			list_splice(promote + i, &n->partial);

		spin_unlock_irqrestore(&n->list_lock, flags);

		/* Release empty sद_असल */
		list_क्रम_each_entry_safe(page, t, &discard, slab_list)
			discard_slab(s, page);

		अगर (sद_असल_node(s, node))
			ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक slab_mem_going_offline_callback(व्योम *arg)
अणु
	काष्ठा kmem_cache *s;

	mutex_lock(&slab_mutex);
	list_क्रम_each_entry(s, &slab_caches, list)
		__kmem_cache_shrink(s);
	mutex_unlock(&slab_mutex);

	वापस 0;
पूर्ण

अटल व्योम slab_mem_offline_callback(व्योम *arg)
अणु
	काष्ठा memory_notअगरy *marg = arg;
	पूर्णांक offline_node;

	offline_node = marg->status_change_nid_normal;

	/*
	 * If the node still has available memory. we need kmem_cache_node
	 * क्रम it yet.
	 */
	अगर (offline_node < 0)
		वापस;

	mutex_lock(&slab_mutex);
	node_clear(offline_node, slab_nodes);
	/*
	 * We no दीर्घer मुक्त kmem_cache_node काष्ठाures here, as it would be
	 * racy with all get_node() users, and infeasible to protect them with
	 * slab_mutex.
	 */
	mutex_unlock(&slab_mutex);
पूर्ण

अटल पूर्णांक slab_mem_going_online_callback(व्योम *arg)
अणु
	काष्ठा kmem_cache_node *n;
	काष्ठा kmem_cache *s;
	काष्ठा memory_notअगरy *marg = arg;
	पूर्णांक nid = marg->status_change_nid_normal;
	पूर्णांक ret = 0;

	/*
	 * If the node's memory is alपढ़ोy available, then kmem_cache_node is
	 * alपढ़ोy created. Nothing to करो.
	 */
	अगर (nid < 0)
		वापस 0;

	/*
	 * We are bringing a node online. No memory is available yet. We must
	 * allocate a kmem_cache_node काष्ठाure in order to bring the node
	 * online.
	 */
	mutex_lock(&slab_mutex);
	list_क्रम_each_entry(s, &slab_caches, list) अणु
		/*
		 * The काष्ठाure may alपढ़ोy exist अगर the node was previously
		 * onlined and offlined.
		 */
		अगर (get_node(s, nid))
			जारी;
		/*
		 * XXX: kmem_cache_alloc_node will fallback to other nodes
		 *      since memory is not yet available from the node that
		 *      is brought up.
		 */
		n = kmem_cache_alloc(kmem_cache_node, GFP_KERNEL);
		अगर (!n) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		init_kmem_cache_node(n);
		s->node[nid] = n;
	पूर्ण
	/*
	 * Any cache created after this poपूर्णांक will also have kmem_cache_node
	 * initialized क्रम the new node.
	 */
	node_set(nid, slab_nodes);
out:
	mutex_unlock(&slab_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक slab_memory_callback(काष्ठा notअगरier_block *self,
				अचिन्हित दीर्घ action, व्योम *arg)
अणु
	पूर्णांक ret = 0;

	चयन (action) अणु
	हाल MEM_GOING_ONLINE:
		ret = slab_mem_going_online_callback(arg);
		अवरोध;
	हाल MEM_GOING_OFFLINE:
		ret = slab_mem_going_offline_callback(arg);
		अवरोध;
	हाल MEM_OFFLINE:
	हाल MEM_CANCEL_ONLINE:
		slab_mem_offline_callback(arg);
		अवरोध;
	हाल MEM_ONLINE:
	हाल MEM_CANCEL_OFFLINE:
		अवरोध;
	पूर्ण
	अगर (ret)
		ret = notअगरier_from_त्रुटि_सं(ret);
	अन्यथा
		ret = NOTIFY_OK;
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block slab_memory_callback_nb = अणु
	.notअगरier_call = slab_memory_callback,
	.priority = SLAB_CALLBACK_PRI,
पूर्ण;

/********************************************************************
 *			Basic setup of sद_असल
 *******************************************************************/

/*
 * Used क्रम early kmem_cache काष्ठाures that were allocated using
 * the page allocator. Allocate them properly then fix up the poपूर्णांकers
 * that may be poपूर्णांकing to the wrong kmem_cache काष्ठाure.
 */

अटल काष्ठा kmem_cache * __init bootstrap(काष्ठा kmem_cache *अटल_cache)
अणु
	पूर्णांक node;
	काष्ठा kmem_cache *s = kmem_cache_zalloc(kmem_cache, GFP_NOWAIT);
	काष्ठा kmem_cache_node *n;

	स_नकल(s, अटल_cache, kmem_cache->object_size);

	/*
	 * This runs very early, and only the boot processor is supposed to be
	 * up.  Even अगर it weren't true, IRQs are not up so we couldn't fire
	 * IPIs around.
	 */
	__flush_cpu_slab(s, smp_processor_id());
	क्रम_each_kmem_cache_node(s, node, n) अणु
		काष्ठा page *p;

		list_क्रम_each_entry(p, &n->partial, slab_list)
			p->slab_cache = s;

#अगर_घोषित CONFIG_SLUB_DEBUG
		list_क्रम_each_entry(p, &n->full, slab_list)
			p->slab_cache = s;
#पूर्ण_अगर
	पूर्ण
	list_add(&s->list, &slab_caches);
	वापस s;
पूर्ण

व्योम __init kmem_cache_init(व्योम)
अणु
	अटल __initdata काष्ठा kmem_cache boot_kmem_cache,
		boot_kmem_cache_node;
	पूर्णांक node;

	अगर (debug_guardpage_minorder())
		slub_max_order = 0;

	kmem_cache_node = &boot_kmem_cache_node;
	kmem_cache = &boot_kmem_cache;

	/*
	 * Initialize the nodemask क्रम which we will allocate per node
	 * काष्ठाures. Here we करोn't need taking slab_mutex yet.
	 */
	क्रम_each_node_state(node, N_NORMAL_MEMORY)
		node_set(node, slab_nodes);

	create_boot_cache(kmem_cache_node, "kmem_cache_node",
		माप(काष्ठा kmem_cache_node), SLAB_HWCACHE_ALIGN, 0, 0);

	रेजिस्टर_hoपंचांगemory_notअगरier(&slab_memory_callback_nb);

	/* Able to allocate the per node काष्ठाures */
	slab_state = PARTIAL;

	create_boot_cache(kmem_cache, "kmem_cache",
			दुरत्व(काष्ठा kmem_cache, node) +
				nr_node_ids * माप(काष्ठा kmem_cache_node *),
		       SLAB_HWCACHE_ALIGN, 0, 0);

	kmem_cache = bootstrap(&boot_kmem_cache);
	kmem_cache_node = bootstrap(&boot_kmem_cache_node);

	/* Now we can use the kmem_cache to allocate kदो_स्मृति sद_असल */
	setup_kदो_स्मृति_cache_index_table();
	create_kदो_स्मृति_caches(0);

	/* Setup अक्रमom मुक्तlists क्रम each cache */
	init_मुक्तlist_अक्रमomization();

	cpuhp_setup_state_nocalls(CPUHP_SLUB_DEAD, "slub:dead", शून्य,
				  slub_cpu_dead);

	pr_info("SLUB: HWalign=%d, Order=%u-%u, MinObjects=%u, CPUs=%u, Nodes=%u\n",
		cache_line_size(),
		slub_min_order, slub_max_order, slub_min_objects,
		nr_cpu_ids, nr_node_ids);
पूर्ण

व्योम __init kmem_cache_init_late(व्योम)
अणु
पूर्ण

काष्ठा kmem_cache *
__kmem_cache_alias(स्थिर अक्षर *name, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक align,
		   slab_flags_t flags, व्योम (*ctor)(व्योम *))
अणु
	काष्ठा kmem_cache *s;

	s = find_mergeable(size, align, flags, name, ctor);
	अगर (s) अणु
		s->refcount++;

		/*
		 * Adjust the object sizes so that we clear
		 * the complete object on kzalloc.
		 */
		s->object_size = max(s->object_size, size);
		s->inuse = max(s->inuse, ALIGN(size, माप(व्योम *)));

		अगर (sysfs_slab_alias(s, name)) अणु
			s->refcount--;
			s = शून्य;
		पूर्ण
	पूर्ण

	वापस s;
पूर्ण

पूर्णांक __kmem_cache_create(काष्ठा kmem_cache *s, slab_flags_t flags)
अणु
	पूर्णांक err;

	err = kmem_cache_खोलो(s, flags);
	अगर (err)
		वापस err;

	/* Mutex is not taken during early boot */
	अगर (slab_state <= UP)
		वापस 0;

	err = sysfs_slab_add(s);
	अगर (err)
		__kmem_cache_release(s);

	वापस err;
पूर्ण

व्योम *__kदो_स्मृति_track_caller(माप_प्रकार size, gfp_t gfpflags, अचिन्हित दीर्घ caller)
अणु
	काष्ठा kmem_cache *s;
	व्योम *ret;

	अगर (unlikely(size > KMALLOC_MAX_CACHE_SIZE))
		वापस kदो_स्मृति_large(size, gfpflags);

	s = kदो_स्मृति_slab(size, gfpflags);

	अगर (unlikely(ZERO_OR_शून्य_PTR(s)))
		वापस s;

	ret = slab_alloc(s, gfpflags, caller, size);

	/* Honor the call site poपूर्णांकer we received. */
	trace_kदो_स्मृति(caller, ret, size, s->size, gfpflags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति_track_caller);

#अगर_घोषित CONFIG_NUMA
व्योम *__kदो_स्मृति_node_track_caller(माप_प्रकार size, gfp_t gfpflags,
					पूर्णांक node, अचिन्हित दीर्घ caller)
अणु
	काष्ठा kmem_cache *s;
	व्योम *ret;

	अगर (unlikely(size > KMALLOC_MAX_CACHE_SIZE)) अणु
		ret = kदो_स्मृति_large_node(size, gfpflags, node);

		trace_kदो_स्मृति_node(caller, ret,
				   size, PAGE_SIZE << get_order(size),
				   gfpflags, node);

		वापस ret;
	पूर्ण

	s = kदो_स्मृति_slab(size, gfpflags);

	अगर (unlikely(ZERO_OR_शून्य_PTR(s)))
		वापस s;

	ret = slab_alloc_node(s, gfpflags, node, caller, size);

	/* Honor the call site poपूर्णांकer we received. */
	trace_kदो_स्मृति_node(caller, ret, size, s->size, gfpflags, node);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति_node_track_caller);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSFS
अटल पूर्णांक count_inuse(काष्ठा page *page)
अणु
	वापस page->inuse;
पूर्ण

अटल पूर्णांक count_total(काष्ठा page *page)
अणु
	वापस page->objects;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SLUB_DEBUG
अटल व्योम validate_slab(काष्ठा kmem_cache *s, काष्ठा page *page)
अणु
	व्योम *p;
	व्योम *addr = page_address(page);
	अचिन्हित दीर्घ *map;

	slab_lock(page);

	अगर (!check_slab(s, page) || !on_मुक्तlist(s, page, शून्य))
		जाओ unlock;

	/* Now we know that a valid मुक्तlist exists */
	map = get_map(s, page);
	क्रम_each_object(p, s, addr, page->objects) अणु
		u8 val = test_bit(__obj_to_index(s, addr, p), map) ?
			 SLUB_RED_INACTIVE : SLUB_RED_ACTIVE;

		अगर (!check_object(s, page, p, val))
			अवरोध;
	पूर्ण
	put_map(map);
unlock:
	slab_unlock(page);
पूर्ण

अटल पूर्णांक validate_slab_node(काष्ठा kmem_cache *s,
		काष्ठा kmem_cache_node *n)
अणु
	अचिन्हित दीर्घ count = 0;
	काष्ठा page *page;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&n->list_lock, flags);

	list_क्रम_each_entry(page, &n->partial, slab_list) अणु
		validate_slab(s, page);
		count++;
	पूर्ण
	अगर (count != n->nr_partial)
		pr_err("SLUB %s: %ld partial slabs counted but counter=%ld\n",
		       s->name, count, n->nr_partial);

	अगर (!(s->flags & SLAB_STORE_USER))
		जाओ out;

	list_क्रम_each_entry(page, &n->full, slab_list) अणु
		validate_slab(s, page);
		count++;
	पूर्ण
	अगर (count != atomic_दीर्घ_पढ़ो(&n->nr_sद_असल))
		pr_err("SLUB: %s %ld slabs counted but counter=%ld\n",
		       s->name, count, atomic_दीर्घ_पढ़ो(&n->nr_sद_असल));

out:
	spin_unlock_irqrestore(&n->list_lock, flags);
	वापस count;
पूर्ण

अटल दीर्घ validate_slab_cache(काष्ठा kmem_cache *s)
अणु
	पूर्णांक node;
	अचिन्हित दीर्घ count = 0;
	काष्ठा kmem_cache_node *n;

	flush_all(s);
	क्रम_each_kmem_cache_node(s, node, n)
		count += validate_slab_node(s, n);

	वापस count;
पूर्ण
/*
 * Generate lists of code addresses where slabcache objects are allocated
 * and मुक्तd.
 */

काष्ठा location अणु
	अचिन्हित दीर्घ count;
	अचिन्हित दीर्घ addr;
	दीर्घ दीर्घ sum_समय;
	दीर्घ min_समय;
	दीर्घ max_समय;
	दीर्घ min_pid;
	दीर्घ max_pid;
	DECLARE_BITMAP(cpus, NR_CPUS);
	nodemask_t nodes;
पूर्ण;

काष्ठा loc_track अणु
	अचिन्हित दीर्घ max;
	अचिन्हित दीर्घ count;
	काष्ठा location *loc;
पूर्ण;

अटल व्योम मुक्त_loc_track(काष्ठा loc_track *t)
अणु
	अगर (t->max)
		मुक्त_pages((अचिन्हित दीर्घ)t->loc,
			get_order(माप(काष्ठा location) * t->max));
पूर्ण

अटल पूर्णांक alloc_loc_track(काष्ठा loc_track *t, अचिन्हित दीर्घ max, gfp_t flags)
अणु
	काष्ठा location *l;
	पूर्णांक order;

	order = get_order(माप(काष्ठा location) * max);

	l = (व्योम *)__get_मुक्त_pages(flags, order);
	अगर (!l)
		वापस 0;

	अगर (t->count) अणु
		स_नकल(l, t->loc, माप(काष्ठा location) * t->count);
		मुक्त_loc_track(t);
	पूर्ण
	t->max = max;
	t->loc = l;
	वापस 1;
पूर्ण

अटल पूर्णांक add_location(काष्ठा loc_track *t, काष्ठा kmem_cache *s,
				स्थिर काष्ठा track *track)
अणु
	दीर्घ start, end, pos;
	काष्ठा location *l;
	अचिन्हित दीर्घ caddr;
	अचिन्हित दीर्घ age = jअगरfies - track->when;

	start = -1;
	end = t->count;

	क्रम ( ; ; ) अणु
		pos = start + (end - start + 1) / 2;

		/*
		 * There is nothing at "end". If we end up there
		 * we need to add something to beक्रमe end.
		 */
		अगर (pos == end)
			अवरोध;

		caddr = t->loc[pos].addr;
		अगर (track->addr == caddr) अणु

			l = &t->loc[pos];
			l->count++;
			अगर (track->when) अणु
				l->sum_समय += age;
				अगर (age < l->min_समय)
					l->min_समय = age;
				अगर (age > l->max_समय)
					l->max_समय = age;

				अगर (track->pid < l->min_pid)
					l->min_pid = track->pid;
				अगर (track->pid > l->max_pid)
					l->max_pid = track->pid;

				cpumask_set_cpu(track->cpu,
						to_cpumask(l->cpus));
			पूर्ण
			node_set(page_to_nid(virt_to_page(track)), l->nodes);
			वापस 1;
		पूर्ण

		अगर (track->addr < caddr)
			end = pos;
		अन्यथा
			start = pos;
	पूर्ण

	/*
	 * Not found. Insert new tracking element.
	 */
	अगर (t->count >= t->max && !alloc_loc_track(t, 2 * t->max, GFP_ATOMIC))
		वापस 0;

	l = t->loc + pos;
	अगर (pos < t->count)
		स_हटाओ(l + 1, l,
			(t->count - pos) * माप(काष्ठा location));
	t->count++;
	l->count = 1;
	l->addr = track->addr;
	l->sum_समय = age;
	l->min_समय = age;
	l->max_समय = age;
	l->min_pid = track->pid;
	l->max_pid = track->pid;
	cpumask_clear(to_cpumask(l->cpus));
	cpumask_set_cpu(track->cpu, to_cpumask(l->cpus));
	nodes_clear(l->nodes);
	node_set(page_to_nid(virt_to_page(track)), l->nodes);
	वापस 1;
पूर्ण

अटल व्योम process_slab(काष्ठा loc_track *t, काष्ठा kmem_cache *s,
		काष्ठा page *page, क्रमागत track_item alloc)
अणु
	व्योम *addr = page_address(page);
	व्योम *p;
	अचिन्हित दीर्घ *map;

	map = get_map(s, page);
	क्रम_each_object(p, s, addr, page->objects)
		अगर (!test_bit(__obj_to_index(s, addr, p), map))
			add_location(t, s, get_track(s, p, alloc));
	put_map(map);
पूर्ण

अटल पूर्णांक list_locations(काष्ठा kmem_cache *s, अक्षर *buf,
			  क्रमागत track_item alloc)
अणु
	पूर्णांक len = 0;
	अचिन्हित दीर्घ i;
	काष्ठा loc_track t = अणु 0, 0, शून्य पूर्ण;
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	अगर (!alloc_loc_track(&t, PAGE_SIZE / माप(काष्ठा location),
			     GFP_KERNEL)) अणु
		वापस sysfs_emit(buf, "Out of memory\n");
	पूर्ण
	/* Push back cpu sद_असल */
	flush_all(s);

	क्रम_each_kmem_cache_node(s, node, n) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा page *page;

		अगर (!atomic_दीर्घ_पढ़ो(&n->nr_sद_असल))
			जारी;

		spin_lock_irqsave(&n->list_lock, flags);
		list_क्रम_each_entry(page, &n->partial, slab_list)
			process_slab(&t, s, page, alloc);
		list_क्रम_each_entry(page, &n->full, slab_list)
			process_slab(&t, s, page, alloc);
		spin_unlock_irqrestore(&n->list_lock, flags);
	पूर्ण

	क्रम (i = 0; i < t.count; i++) अणु
		काष्ठा location *l = &t.loc[i];

		len += sysfs_emit_at(buf, len, "%7ld ", l->count);

		अगर (l->addr)
			len += sysfs_emit_at(buf, len, "%pS", (व्योम *)l->addr);
		अन्यथा
			len += sysfs_emit_at(buf, len, "<not-available>");

		अगर (l->sum_समय != l->min_समय)
			len += sysfs_emit_at(buf, len, " age=%ld/%ld/%ld",
					     l->min_समय,
					     (दीर्घ)भाग_u64(l->sum_समय,
							   l->count),
					     l->max_समय);
		अन्यथा
			len += sysfs_emit_at(buf, len, " age=%ld", l->min_समय);

		अगर (l->min_pid != l->max_pid)
			len += sysfs_emit_at(buf, len, " pid=%ld-%ld",
					     l->min_pid, l->max_pid);
		अन्यथा
			len += sysfs_emit_at(buf, len, " pid=%ld",
					     l->min_pid);

		अगर (num_online_cpus() > 1 &&
		    !cpumask_empty(to_cpumask(l->cpus)))
			len += sysfs_emit_at(buf, len, " cpus=%*pbl",
					     cpumask_pr_args(to_cpumask(l->cpus)));

		अगर (nr_online_nodes > 1 && !nodes_empty(l->nodes))
			len += sysfs_emit_at(buf, len, " nodes=%*pbl",
					     nodemask_pr_args(&l->nodes));

		len += sysfs_emit_at(buf, len, "\n");
	पूर्ण

	मुक्त_loc_track(&t);
	अगर (!t.count)
		len += sysfs_emit_at(buf, len, "No data\n");

	वापस len;
पूर्ण
#पूर्ण_अगर	/* CONFIG_SLUB_DEBUG */

#अगर_घोषित SLUB_RESILIENCY_TEST
अटल व्योम __init resiliency_test(व्योम)
अणु
	u8 *p;
	पूर्णांक type = KMALLOC_NORMAL;

	BUILD_BUG_ON(KMALLOC_MIN_SIZE > 16 || KMALLOC_SHIFT_HIGH < 10);

	pr_err("SLUB resiliency testing\n");
	pr_err("-----------------------\n");
	pr_err("A. Corruption after allocation\n");

	p = kzalloc(16, GFP_KERNEL);
	p[16] = 0x12;
	pr_err("\n1. kmalloc-16: Clobber Redzone/next pointer 0x12->0x%p\n\n",
	       p + 16);

	validate_slab_cache(kदो_स्मृति_caches[type][4]);

	/* Hmmm... The next two are dangerous */
	p = kzalloc(32, GFP_KERNEL);
	p[32 + माप(व्योम *)] = 0x34;
	pr_err("\n2. kmalloc-32: Clobber next pointer/next slab 0x34 -> -0x%p\n",
	       p);
	pr_err("If allocated object is overwritten then not detectable\n\n");

	validate_slab_cache(kदो_स्मृति_caches[type][5]);
	p = kzalloc(64, GFP_KERNEL);
	p += 64 + (get_cycles() & 0xff) * माप(व्योम *);
	*p = 0x56;
	pr_err("\n3. kmalloc-64: corrupting random byte 0x56->0x%p\n",
	       p);
	pr_err("If allocated object is overwritten then not detectable\n\n");
	validate_slab_cache(kदो_स्मृति_caches[type][6]);

	pr_err("\nB. Corruption after free\n");
	p = kzalloc(128, GFP_KERNEL);
	kमुक्त(p);
	*p = 0x78;
	pr_err("1. kmalloc-128: Clobber first word 0x78->0x%p\n\n", p);
	validate_slab_cache(kदो_स्मृति_caches[type][7]);

	p = kzalloc(256, GFP_KERNEL);
	kमुक्त(p);
	p[50] = 0x9a;
	pr_err("\n2. kmalloc-256: Clobber 50th byte 0x9a->0x%p\n\n", p);
	validate_slab_cache(kदो_स्मृति_caches[type][8]);

	p = kzalloc(512, GFP_KERNEL);
	kमुक्त(p);
	p[512] = 0xab;
	pr_err("\n3. kmalloc-512: Clobber redzone 0xab->0x%p\n\n", p);
	validate_slab_cache(kदो_स्मृति_caches[type][9]);
पूर्ण
#अन्यथा
#अगर_घोषित CONFIG_SYSFS
अटल व्योम resiliency_test(व्योम) अणुपूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर	/* SLUB_RESILIENCY_TEST */

#अगर_घोषित CONFIG_SYSFS
क्रमागत slab_stat_type अणु
	SL_ALL,			/* All sद_असल */
	SL_PARTIAL,		/* Only partially allocated sद_असल */
	SL_CPU,			/* Only sद_असल used क्रम cpu caches */
	SL_OBJECTS,		/* Determine allocated objects not sद_असल */
	SL_TOTAL		/* Determine object capacity not sद_असल */
पूर्ण;

#घोषणा SO_ALL		(1 << SL_ALL)
#घोषणा SO_PARTIAL	(1 << SL_PARTIAL)
#घोषणा SO_CPU		(1 << SL_CPU)
#घोषणा SO_OBJECTS	(1 << SL_OBJECTS)
#घोषणा SO_TOTAL	(1 << SL_TOTAL)

अटल sमाप_प्रकार show_slab_objects(काष्ठा kmem_cache *s,
				 अक्षर *buf, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ total = 0;
	पूर्णांक node;
	पूर्णांक x;
	अचिन्हित दीर्घ *nodes;
	पूर्णांक len = 0;

	nodes = kसुस्मृति(nr_node_ids, माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!nodes)
		वापस -ENOMEM;

	अगर (flags & SO_CPU) अणु
		पूर्णांक cpu;

		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा kmem_cache_cpu *c = per_cpu_ptr(s->cpu_slab,
							       cpu);
			पूर्णांक node;
			काष्ठा page *page;

			page = READ_ONCE(c->page);
			अगर (!page)
				जारी;

			node = page_to_nid(page);
			अगर (flags & SO_TOTAL)
				x = page->objects;
			अन्यथा अगर (flags & SO_OBJECTS)
				x = page->inuse;
			अन्यथा
				x = 1;

			total += x;
			nodes[node] += x;

			page = slub_percpu_partial_पढ़ो_once(c);
			अगर (page) अणु
				node = page_to_nid(page);
				अगर (flags & SO_TOTAL)
					WARN_ON_ONCE(1);
				अन्यथा अगर (flags & SO_OBJECTS)
					WARN_ON_ONCE(1);
				अन्यथा
					x = page->pages;
				total += x;
				nodes[node] += x;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * It is impossible to take "mem_hotplug_lock" here with "kernfs_mutex"
	 * alपढ़ोy held which will conflict with an existing lock order:
	 *
	 * mem_hotplug_lock->slab_mutex->kernfs_mutex
	 *
	 * We करोn't really need mem_hotplug_lock (to hold off
	 * slab_mem_going_offline_callback) here because slab's memory hot
	 * unplug code करोesn't destroy the kmem_cache->node[] data.
	 */

#अगर_घोषित CONFIG_SLUB_DEBUG
	अगर (flags & SO_ALL) अणु
		काष्ठा kmem_cache_node *n;

		क्रम_each_kmem_cache_node(s, node, n) अणु

			अगर (flags & SO_TOTAL)
				x = atomic_दीर्घ_पढ़ो(&n->total_objects);
			अन्यथा अगर (flags & SO_OBJECTS)
				x = atomic_दीर्घ_पढ़ो(&n->total_objects) -
					count_partial(n, count_मुक्त);
			अन्यथा
				x = atomic_दीर्घ_पढ़ो(&n->nr_sद_असल);
			total += x;
			nodes[node] += x;
		पूर्ण

	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (flags & SO_PARTIAL) अणु
		काष्ठा kmem_cache_node *n;

		क्रम_each_kmem_cache_node(s, node, n) अणु
			अगर (flags & SO_TOTAL)
				x = count_partial(n, count_total);
			अन्यथा अगर (flags & SO_OBJECTS)
				x = count_partial(n, count_inuse);
			अन्यथा
				x = n->nr_partial;
			total += x;
			nodes[node] += x;
		पूर्ण
	पूर्ण

	len += sysfs_emit_at(buf, len, "%lu", total);
#अगर_घोषित CONFIG_NUMA
	क्रम (node = 0; node < nr_node_ids; node++) अणु
		अगर (nodes[node])
			len += sysfs_emit_at(buf, len, " N%d=%lu",
					     node, nodes[node]);
	पूर्ण
#पूर्ण_अगर
	len += sysfs_emit_at(buf, len, "\n");
	kमुक्त(nodes);

	वापस len;
पूर्ण

#घोषणा to_slab_attr(n) container_of(n, काष्ठा slab_attribute, attr)
#घोषणा to_slab(n) container_of(n, काष्ठा kmem_cache, kobj)

काष्ठा slab_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा kmem_cache *s, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा kmem_cache *s, स्थिर अक्षर *x, माप_प्रकार count);
पूर्ण;

#घोषणा SLAB_ATTR_RO(_name) \
	अटल काष्ठा slab_attribute _name##_attr = \
	__ATTR(_name, 0400, _name##_show, शून्य)

#घोषणा SLAB_ATTR(_name) \
	अटल काष्ठा slab_attribute _name##_attr =  \
	__ATTR(_name, 0600, _name##_show, _name##_store)

अटल sमाप_प्रकार slab_size_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", s->size);
पूर्ण
SLAB_ATTR_RO(slab_size);

अटल sमाप_प्रकार align_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", s->align);
पूर्ण
SLAB_ATTR_RO(align);

अटल sमाप_प्रकार object_size_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", s->object_size);
पूर्ण
SLAB_ATTR_RO(object_size);

अटल sमाप_प्रकार objs_per_slab_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", oo_objects(s->oo));
पूर्ण
SLAB_ATTR_RO(objs_per_slab);

अटल sमाप_प्रकार order_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", oo_order(s->oo));
पूर्ण
SLAB_ATTR_RO(order);

अटल sमाप_प्रकार min_partial_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lu\n", s->min_partial);
पूर्ण

अटल sमाप_प्रकार min_partial_store(काष्ठा kmem_cache *s, स्थिर अक्षर *buf,
				 माप_प्रकार length)
अणु
	अचिन्हित दीर्घ min;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &min);
	अगर (err)
		वापस err;

	set_min_partial(s, min);
	वापस length;
पूर्ण
SLAB_ATTR(min_partial);

अटल sमाप_प्रकार cpu_partial_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", slub_cpu_partial(s));
पूर्ण

अटल sमाप_प्रकार cpu_partial_store(काष्ठा kmem_cache *s, स्थिर अक्षर *buf,
				 माप_प्रकार length)
अणु
	अचिन्हित पूर्णांक objects;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &objects);
	अगर (err)
		वापस err;
	अगर (objects && !kmem_cache_has_cpu_partial(s))
		वापस -EINVAL;

	slub_set_cpu_partial(s, objects);
	flush_all(s);
	वापस length;
पूर्ण
SLAB_ATTR(cpu_partial);

अटल sमाप_प्रकार ctor_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	अगर (!s->ctor)
		वापस 0;
	वापस sysfs_emit(buf, "%pS\n", s->ctor);
पूर्ण
SLAB_ATTR_RO(ctor);

अटल sमाप_प्रकार aliases_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", s->refcount < 0 ? 0 : s->refcount - 1);
पूर्ण
SLAB_ATTR_RO(aliases);

अटल sमाप_प्रकार partial_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस show_slab_objects(s, buf, SO_PARTIAL);
पूर्ण
SLAB_ATTR_RO(partial);

अटल sमाप_प्रकार cpu_sद_असल_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस show_slab_objects(s, buf, SO_CPU);
पूर्ण
SLAB_ATTR_RO(cpu_sद_असल);

अटल sमाप_प्रकार objects_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस show_slab_objects(s, buf, SO_ALL|SO_OBJECTS);
पूर्ण
SLAB_ATTR_RO(objects);

अटल sमाप_प्रकार objects_partial_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस show_slab_objects(s, buf, SO_PARTIAL|SO_OBJECTS);
पूर्ण
SLAB_ATTR_RO(objects_partial);

अटल sमाप_प्रकार sद_असल_cpu_partial_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	पूर्णांक objects = 0;
	पूर्णांक pages = 0;
	पूर्णांक cpu;
	पूर्णांक len = 0;

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा page *page;

		page = slub_percpu_partial(per_cpu_ptr(s->cpu_slab, cpu));

		अगर (page) अणु
			pages += page->pages;
			objects += page->pobjects;
		पूर्ण
	पूर्ण

	len += sysfs_emit_at(buf, len, "%d(%d)", objects, pages);

#अगर_घोषित CONFIG_SMP
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा page *page;

		page = slub_percpu_partial(per_cpu_ptr(s->cpu_slab, cpu));
		अगर (page)
			len += sysfs_emit_at(buf, len, " C%d=%d(%d)",
					     cpu, page->pobjects, page->pages);
	पूर्ण
#पूर्ण_अगर
	len += sysfs_emit_at(buf, len, "\n");

	वापस len;
पूर्ण
SLAB_ATTR_RO(sद_असल_cpu_partial);

अटल sमाप_प्रकार reclaim_account_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_RECLAIM_ACCOUNT));
पूर्ण
SLAB_ATTR_RO(reclaim_account);

अटल sमाप_प्रकार hwcache_align_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_HWCACHE_ALIGN));
पूर्ण
SLAB_ATTR_RO(hwcache_align);

#अगर_घोषित CONFIG_ZONE_DMA
अटल sमाप_प्रकार cache_dma_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_CACHE_DMA));
पूर्ण
SLAB_ATTR_RO(cache_dma);
#पूर्ण_अगर

अटल sमाप_प्रकार usersize_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", s->usersize);
पूर्ण
SLAB_ATTR_RO(usersize);

अटल sमाप_प्रकार destroy_by_rcu_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_TYPESAFE_BY_RCU));
पूर्ण
SLAB_ATTR_RO(destroy_by_rcu);

#अगर_घोषित CONFIG_SLUB_DEBUG
अटल sमाप_प्रकार sद_असल_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस show_slab_objects(s, buf, SO_ALL);
पूर्ण
SLAB_ATTR_RO(sद_असल);

अटल sमाप_प्रकार total_objects_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस show_slab_objects(s, buf, SO_ALL|SO_TOTAL);
पूर्ण
SLAB_ATTR_RO(total_objects);

अटल sमाप_प्रकार sanity_checks_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_CONSISTENCY_CHECKS));
पूर्ण
SLAB_ATTR_RO(sanity_checks);

अटल sमाप_प्रकार trace_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_TRACE));
पूर्ण
SLAB_ATTR_RO(trace);

अटल sमाप_प्रकार red_zone_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_RED_ZONE));
पूर्ण

SLAB_ATTR_RO(red_zone);

अटल sमाप_प्रकार poison_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_POISON));
पूर्ण

SLAB_ATTR_RO(poison);

अटल sमाप_प्रकार store_user_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_STORE_USER));
पूर्ण

SLAB_ATTR_RO(store_user);

अटल sमाप_प्रकार validate_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार validate_store(काष्ठा kmem_cache *s,
			स्थिर अक्षर *buf, माप_प्रकार length)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (buf[0] == '1') अणु
		ret = validate_slab_cache(s);
		अगर (ret >= 0)
			ret = length;
	पूर्ण
	वापस ret;
पूर्ण
SLAB_ATTR(validate);

अटल sमाप_प्रकार alloc_calls_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	अगर (!(s->flags & SLAB_STORE_USER))
		वापस -ENOSYS;
	वापस list_locations(s, buf, TRACK_ALLOC);
पूर्ण
SLAB_ATTR_RO(alloc_calls);

अटल sमाप_प्रकार मुक्त_calls_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	अगर (!(s->flags & SLAB_STORE_USER))
		वापस -ENOSYS;
	वापस list_locations(s, buf, TRACK_FREE);
पूर्ण
SLAB_ATTR_RO(मुक्त_calls);
#पूर्ण_अगर /* CONFIG_SLUB_DEBUG */

#अगर_घोषित CONFIG_FAILSLAB
अटल sमाप_प्रकार failslab_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", !!(s->flags & SLAB_FAILSLAB));
पूर्ण
SLAB_ATTR_RO(failslab);
#पूर्ण_अगर

अटल sमाप_प्रकार shrink_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार shrink_store(काष्ठा kmem_cache *s,
			स्थिर अक्षर *buf, माप_प्रकार length)
अणु
	अगर (buf[0] == '1')
		kmem_cache_shrink(s);
	अन्यथा
		वापस -EINVAL;
	वापस length;
पूर्ण
SLAB_ATTR(shrink);

#अगर_घोषित CONFIG_NUMA
अटल sमाप_प्रकार remote_node_defrag_ratio_show(काष्ठा kmem_cache *s, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", s->remote_node_defrag_ratio / 10);
पूर्ण

अटल sमाप_प्रकार remote_node_defrag_ratio_store(काष्ठा kmem_cache *s,
				स्थिर अक्षर *buf, माप_प्रकार length)
अणु
	अचिन्हित पूर्णांक ratio;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &ratio);
	अगर (err)
		वापस err;
	अगर (ratio > 100)
		वापस -दुस्फल;

	s->remote_node_defrag_ratio = ratio * 10;

	वापस length;
पूर्ण
SLAB_ATTR(remote_node_defrag_ratio);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SLUB_STATS
अटल पूर्णांक show_stat(काष्ठा kmem_cache *s, अक्षर *buf, क्रमागत stat_item si)
अणु
	अचिन्हित दीर्घ sum  = 0;
	पूर्णांक cpu;
	पूर्णांक len = 0;
	पूर्णांक *data = kदो_स्मृति_array(nr_cpu_ids, माप(पूर्णांक), GFP_KERNEL);

	अगर (!data)
		वापस -ENOMEM;

	क्रम_each_online_cpu(cpu) अणु
		अचिन्हित x = per_cpu_ptr(s->cpu_slab, cpu)->stat[si];

		data[cpu] = x;
		sum += x;
	पूर्ण

	len += sysfs_emit_at(buf, len, "%lu", sum);

#अगर_घोषित CONFIG_SMP
	क्रम_each_online_cpu(cpu) अणु
		अगर (data[cpu])
			len += sysfs_emit_at(buf, len, " C%d=%u",
					     cpu, data[cpu]);
	पूर्ण
#पूर्ण_अगर
	kमुक्त(data);
	len += sysfs_emit_at(buf, len, "\n");

	वापस len;
पूर्ण

अटल व्योम clear_stat(काष्ठा kmem_cache *s, क्रमागत stat_item si)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		per_cpu_ptr(s->cpu_slab, cpu)->stat[si] = 0;
पूर्ण

#घोषणा STAT_ATTR(si, text) 					\
अटल sमाप_प्रकार text##_show(काष्ठा kmem_cache *s, अक्षर *buf)	\
अणु								\
	वापस show_stat(s, buf, si);				\
पूर्ण								\
अटल sमाप_प्रकार text##_store(काष्ठा kmem_cache *s,		\
				स्थिर अक्षर *buf, माप_प्रकार length)	\
अणु								\
	अगर (buf[0] != '0')					\
		वापस -EINVAL;					\
	clear_stat(s, si);					\
	वापस length;						\
पूर्ण								\
SLAB_ATTR(text);						\

STAT_ATTR(ALLOC_FASTPATH, alloc_fastpath);
STAT_ATTR(ALLOC_SLOWPATH, alloc_slowpath);
STAT_ATTR(FREE_FASTPATH, मुक्त_fastpath);
STAT_ATTR(FREE_SLOWPATH, मुक्त_slowpath);
STAT_ATTR(FREE_FROZEN, मुक्त_frozen);
STAT_ATTR(FREE_ADD_PARTIAL, मुक्त_add_partial);
STAT_ATTR(FREE_REMOVE_PARTIAL, मुक्त_हटाओ_partial);
STAT_ATTR(ALLOC_FROM_PARTIAL, alloc_from_partial);
STAT_ATTR(ALLOC_SLAB, alloc_slab);
STAT_ATTR(ALLOC_REFILL, alloc_refill);
STAT_ATTR(ALLOC_NODE_MISMATCH, alloc_node_mismatch);
STAT_ATTR(FREE_SLAB, मुक्त_slab);
STAT_ATTR(CPUSLAB_FLUSH, cpuslab_flush);
STAT_ATTR(DEACTIVATE_FULL, deactivate_full);
STAT_ATTR(DEACTIVATE_EMPTY, deactivate_empty);
STAT_ATTR(DEACTIVATE_TO_HEAD, deactivate_to_head);
STAT_ATTR(DEACTIVATE_TO_TAIL, deactivate_to_tail);
STAT_ATTR(DEACTIVATE_REMOTE_FREES, deactivate_remote_मुक्तs);
STAT_ATTR(DEACTIVATE_BYPASS, deactivate_bypass);
STAT_ATTR(ORDER_FALLBACK, order_fallback);
STAT_ATTR(CMPXCHG_DOUBLE_CPU_FAIL, cmpxchg_द्विगुन_cpu_fail);
STAT_ATTR(CMPXCHG_DOUBLE_FAIL, cmpxchg_द्विगुन_fail);
STAT_ATTR(CPU_PARTIAL_ALLOC, cpu_partial_alloc);
STAT_ATTR(CPU_PARTIAL_FREE, cpu_partial_मुक्त);
STAT_ATTR(CPU_PARTIAL_NODE, cpu_partial_node);
STAT_ATTR(CPU_PARTIAL_DRAIN, cpu_partial_drain);
#पूर्ण_अगर	/* CONFIG_SLUB_STATS */

अटल काष्ठा attribute *slab_attrs[] = अणु
	&slab_size_attr.attr,
	&object_size_attr.attr,
	&objs_per_slab_attr.attr,
	&order_attr.attr,
	&min_partial_attr.attr,
	&cpu_partial_attr.attr,
	&objects_attr.attr,
	&objects_partial_attr.attr,
	&partial_attr.attr,
	&cpu_sद_असल_attr.attr,
	&ctor_attr.attr,
	&aliases_attr.attr,
	&align_attr.attr,
	&hwcache_align_attr.attr,
	&reclaim_account_attr.attr,
	&destroy_by_rcu_attr.attr,
	&shrink_attr.attr,
	&sद_असल_cpu_partial_attr.attr,
#अगर_घोषित CONFIG_SLUB_DEBUG
	&total_objects_attr.attr,
	&sद_असल_attr.attr,
	&sanity_checks_attr.attr,
	&trace_attr.attr,
	&red_zone_attr.attr,
	&poison_attr.attr,
	&store_user_attr.attr,
	&validate_attr.attr,
	&alloc_calls_attr.attr,
	&मुक्त_calls_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ZONE_DMA
	&cache_dma_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	&remote_node_defrag_ratio_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SLUB_STATS
	&alloc_fastpath_attr.attr,
	&alloc_slowpath_attr.attr,
	&मुक्त_fastpath_attr.attr,
	&मुक्त_slowpath_attr.attr,
	&मुक्त_frozen_attr.attr,
	&मुक्त_add_partial_attr.attr,
	&मुक्त_हटाओ_partial_attr.attr,
	&alloc_from_partial_attr.attr,
	&alloc_slab_attr.attr,
	&alloc_refill_attr.attr,
	&alloc_node_mismatch_attr.attr,
	&मुक्त_slab_attr.attr,
	&cpuslab_flush_attr.attr,
	&deactivate_full_attr.attr,
	&deactivate_empty_attr.attr,
	&deactivate_to_head_attr.attr,
	&deactivate_to_tail_attr.attr,
	&deactivate_remote_मुक्तs_attr.attr,
	&deactivate_bypass_attr.attr,
	&order_fallback_attr.attr,
	&cmpxchg_द्विगुन_fail_attr.attr,
	&cmpxchg_द्विगुन_cpu_fail_attr.attr,
	&cpu_partial_alloc_attr.attr,
	&cpu_partial_मुक्त_attr.attr,
	&cpu_partial_node_attr.attr,
	&cpu_partial_drain_attr.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FAILSLAB
	&failslab_attr.attr,
#पूर्ण_अगर
	&usersize_attr.attr,

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group slab_attr_group = अणु
	.attrs = slab_attrs,
पूर्ण;

अटल sमाप_प्रकार slab_attr_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा slab_attribute *attribute;
	काष्ठा kmem_cache *s;
	पूर्णांक err;

	attribute = to_slab_attr(attr);
	s = to_slab(kobj);

	अगर (!attribute->show)
		वापस -EIO;

	err = attribute->show(s, buf);

	वापस err;
पूर्ण

अटल sमाप_प्रकार slab_attr_store(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा slab_attribute *attribute;
	काष्ठा kmem_cache *s;
	पूर्णांक err;

	attribute = to_slab_attr(attr);
	s = to_slab(kobj);

	अगर (!attribute->store)
		वापस -EIO;

	err = attribute->store(s, buf, len);
	वापस err;
पूर्ण

अटल व्योम kmem_cache_release(काष्ठा kobject *k)
अणु
	slab_kmem_cache_release(to_slab(k));
पूर्ण

अटल स्थिर काष्ठा sysfs_ops slab_sysfs_ops = अणु
	.show = slab_attr_show,
	.store = slab_attr_store,
पूर्ण;

अटल काष्ठा kobj_type slab_ktype = अणु
	.sysfs_ops = &slab_sysfs_ops,
	.release = kmem_cache_release,
पूर्ण;

अटल काष्ठा kset *slab_kset;

अटल अंतरभूत काष्ठा kset *cache_kset(काष्ठा kmem_cache *s)
अणु
	वापस slab_kset;
पूर्ण

#घोषणा ID_STR_LENGTH 64

/* Create a unique string id क्रम a slab cache:
 *
 * Format	:[flags-]size
 */
अटल अक्षर *create_unique_id(काष्ठा kmem_cache *s)
अणु
	अक्षर *name = kदो_स्मृति(ID_STR_LENGTH, GFP_KERNEL);
	अक्षर *p = name;

	BUG_ON(!name);

	*p++ = ':';
	/*
	 * First flags affecting slabcache operations. We will only
	 * get here क्रम aliasable sद_असल so we करो not need to support
	 * too many flags. The flags here must cover all flags that
	 * are matched during merging to guarantee that the id is
	 * unique.
	 */
	अगर (s->flags & SLAB_CACHE_DMA)
		*p++ = 'd';
	अगर (s->flags & SLAB_CACHE_DMA32)
		*p++ = 'D';
	अगर (s->flags & SLAB_RECLAIM_ACCOUNT)
		*p++ = 'a';
	अगर (s->flags & SLAB_CONSISTENCY_CHECKS)
		*p++ = 'F';
	अगर (s->flags & SLAB_ACCOUNT)
		*p++ = 'A';
	अगर (p != name + 1)
		*p++ = '-';
	p += प्र_लिखो(p, "%07u", s->size);

	BUG_ON(p > name + ID_STR_LENGTH - 1);
	वापस name;
पूर्ण

अटल पूर्णांक sysfs_slab_add(काष्ठा kmem_cache *s)
अणु
	पूर्णांक err;
	स्थिर अक्षर *name;
	काष्ठा kset *kset = cache_kset(s);
	पूर्णांक unmergeable = slab_unmergeable(s);

	अगर (!kset) अणु
		kobject_init(&s->kobj, &slab_ktype);
		वापस 0;
	पूर्ण

	अगर (!unmergeable && disable_higher_order_debug &&
			(slub_debug & DEBUG_METADATA_FLAGS))
		unmergeable = 1;

	अगर (unmergeable) अणु
		/*
		 * Slabcache can never be merged so we can use the name proper.
		 * This is typically the हाल क्रम debug situations. In that
		 * हाल we can catch duplicate names easily.
		 */
		sysfs_हटाओ_link(&slab_kset->kobj, s->name);
		name = s->name;
	पूर्ण अन्यथा अणु
		/*
		 * Create a unique name क्रम the slab as a target
		 * क्रम the symlinks.
		 */
		name = create_unique_id(s);
	पूर्ण

	s->kobj.kset = kset;
	err = kobject_init_and_add(&s->kobj, &slab_ktype, शून्य, "%s", name);
	अगर (err)
		जाओ out;

	err = sysfs_create_group(&s->kobj, &slab_attr_group);
	अगर (err)
		जाओ out_del_kobj;

	अगर (!unmergeable) अणु
		/* Setup first alias */
		sysfs_slab_alias(s, s->name);
	पूर्ण
out:
	अगर (!unmergeable)
		kमुक्त(name);
	वापस err;
out_del_kobj:
	kobject_del(&s->kobj);
	जाओ out;
पूर्ण

व्योम sysfs_slab_unlink(काष्ठा kmem_cache *s)
अणु
	अगर (slab_state >= FULL)
		kobject_del(&s->kobj);
पूर्ण

व्योम sysfs_slab_release(काष्ठा kmem_cache *s)
अणु
	अगर (slab_state >= FULL)
		kobject_put(&s->kobj);
पूर्ण

/*
 * Need to buffer aliases during bootup until sysfs becomes
 * available lest we lose that inक्रमmation.
 */
काष्ठा saved_alias अणु
	काष्ठा kmem_cache *s;
	स्थिर अक्षर *name;
	काष्ठा saved_alias *next;
पूर्ण;

अटल काष्ठा saved_alias *alias_list;

अटल पूर्णांक sysfs_slab_alias(काष्ठा kmem_cache *s, स्थिर अक्षर *name)
अणु
	काष्ठा saved_alias *al;

	अगर (slab_state == FULL) अणु
		/*
		 * If we have a leftover link then हटाओ it.
		 */
		sysfs_हटाओ_link(&slab_kset->kobj, name);
		वापस sysfs_create_link(&slab_kset->kobj, &s->kobj, name);
	पूर्ण

	al = kदो_स्मृति(माप(काष्ठा saved_alias), GFP_KERNEL);
	अगर (!al)
		वापस -ENOMEM;

	al->s = s;
	al->name = name;
	al->next = alias_list;
	alias_list = al;
	वापस 0;
पूर्ण

अटल पूर्णांक __init slab_sysfs_init(व्योम)
अणु
	काष्ठा kmem_cache *s;
	पूर्णांक err;

	mutex_lock(&slab_mutex);

	slab_kset = kset_create_and_add("slab", शून्य, kernel_kobj);
	अगर (!slab_kset) अणु
		mutex_unlock(&slab_mutex);
		pr_err("Cannot register slab subsystem.\n");
		वापस -ENOSYS;
	पूर्ण

	slab_state = FULL;

	list_क्रम_each_entry(s, &slab_caches, list) अणु
		err = sysfs_slab_add(s);
		अगर (err)
			pr_err("SLUB: Unable to add boot slab %s to sysfs\n",
			       s->name);
	पूर्ण

	जबतक (alias_list) अणु
		काष्ठा saved_alias *al = alias_list;

		alias_list = alias_list->next;
		err = sysfs_slab_alias(al->s, al->name);
		अगर (err)
			pr_err("SLUB: Unable to add boot slab alias %s to sysfs\n",
			       al->name);
		kमुक्त(al);
	पूर्ण

	mutex_unlock(&slab_mutex);
	resiliency_test();
	वापस 0;
पूर्ण

__initcall(slab_sysfs_init);
#पूर्ण_अगर /* CONFIG_SYSFS */

/*
 * The /proc/slabinfo ABI
 */
#अगर_घोषित CONFIG_SLUB_DEBUG
व्योम get_slabinfo(काष्ठा kmem_cache *s, काष्ठा slabinfo *sinfo)
अणु
	अचिन्हित दीर्घ nr_sद_असल = 0;
	अचिन्हित दीर्घ nr_objs = 0;
	अचिन्हित दीर्घ nr_मुक्त = 0;
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	क्रम_each_kmem_cache_node(s, node, n) अणु
		nr_sद_असल += node_nr_sद_असल(n);
		nr_objs += node_nr_objs(n);
		nr_मुक्त += count_partial(n, count_मुक्त);
	पूर्ण

	sinfo->active_objs = nr_objs - nr_मुक्त;
	sinfo->num_objs = nr_objs;
	sinfo->active_sद_असल = nr_sद_असल;
	sinfo->num_sद_असल = nr_sद_असल;
	sinfo->objects_per_slab = oo_objects(s->oo);
	sinfo->cache_order = oo_order(s->oo);
पूर्ण

व्योम slabinfo_show_stats(काष्ठा seq_file *m, काष्ठा kmem_cache *s)
अणु
पूर्ण

sमाप_प्रकार slabinfo_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		       माप_प्रकार count, loff_t *ppos)
अणु
	वापस -EIO;
पूर्ण
#पूर्ण_अगर /* CONFIG_SLUB_DEBUG */
