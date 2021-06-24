<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/mm/slab.c
 * Written by Mark Hemment, 1996/97.
 * (markhe@nextd.demon.co.uk)
 *
 * kmem_cache_destroy() + some cleanup - 1999 Andrea Arcangeli
 *
 * Major cleanup, dअगरferent bufctl logic, per-cpu arrays
 *	(c) 2000 Manfred Spraul
 *
 * Cleanup, make the head arrays unconditional, preparation क्रम NUMA
 * 	(c) 2002 Manfred Spraul
 *
 * An implementation of the Slab Allocator as described in outline in;
 *	UNIX Internals: The New Frontiers by Uresh Vahalia
 *	Pub: Prentice Hall	ISBN 0-13-101908-2
 * or with a little more detail in;
 *	The Slab Allocator: An Object-Caching Kernel Memory Allocator
 *	Jeff Bonwick (Sun Microप्रणालीs).
 *	Presented at: USENIX Summer 1994 Technical Conference
 *
 * The memory is organized in caches, one cache क्रम each object type.
 * (e.g. inode_cache, dentry_cache, buffer_head, vm_area_काष्ठा)
 * Each cache consists out of many sद_असल (they are small (usually one
 * page दीर्घ) and always contiguous), and each slab contains multiple
 * initialized objects.
 *
 * This means, that your स्थिरructor is used only क्रम newly allocated
 * sद_असल and you must pass objects with the same initializations to
 * kmem_cache_मुक्त.
 *
 * Each cache can only support one memory type (GFP_DMA, GFP_HIGHMEM,
 * normal). If you need a special memory type, then must create a new
 * cache क्रम that memory type.
 *
 * In order to reduce fragmentation, the sद_असल are sorted in 3 groups:
 *   full sद_असल with 0 मुक्त objects
 *   partial sद_असल
 *   empty sद_असल with no allocated objects
 *
 * If partial sद_असल exist, then new allocations come from these sद_असल,
 * otherwise from empty sद_असल or new sद_असल are allocated.
 *
 * kmem_cache_destroy() CAN CRASH अगर you try to allocate from the cache
 * during kmem_cache_destroy(). The caller must prevent concurrent allocs.
 *
 * Each cache has a लघु per-cpu head array, most allocs
 * and मुक्तs go पूर्णांकo that array, and अगर that array overflows, then 1/2
 * of the entries in the array are given back पूर्णांकo the global cache.
 * The head array is strictly LIFO and should improve the cache hit rates.
 * On SMP, it additionally reduces the spinlock operations.
 *
 * The c_cpuarray may not be पढ़ो with enabled local पूर्णांकerrupts -
 * it's changed with a smp_call_function().
 *
 * SMP synchronization:
 *  स्थिरructors and deकाष्ठाors are called without any locking.
 *  Several members in काष्ठा kmem_cache and काष्ठा slab never change, they
 *	are accessed without any locking.
 *  The per-cpu arrays are never accessed from the wrong cpu, no locking,
 *  	and local पूर्णांकerrupts are disabled so slab code is preempt-safe.
 *  The non-स्थिरant members are रक्षित with a per-cache irq spinlock.
 *
 * Many thanks to Mark Hemment, who wrote another per-cpu slab patch
 * in 2000 - many ideas in the current implementation are derived from
 * his patch.
 *
 * Further notes from the original करोcumentation:
 *
 * 11 April '97.  Started multi-thपढ़ोing - markhe
 *	The global cache-chain is रक्षित by the mutex 'slab_mutex'.
 *	The sem is only needed when accessing/extending the cache-chain, which
 *	can never happen inside an पूर्णांकerrupt (kmem_cache_create(),
 *	kmem_cache_shrink() and kmem_cache_reap()).
 *
 *	At present, each engine can be growing a cache.  This should be blocked.
 *
 * 15 March 2005. NUMA slab allocator.
 *	Shai Fultheim <shai@scalex86.org>.
 *	Shobhit Dayal <shobhit@calsoftinc.com>
 *	Alok N Kataria <alokk@calsoftinc.com>
 *	Christoph Lameter <christoph@lameter.com>
 *
 *	Modअगरied the slab allocator to be node aware on NUMA प्रणालीs.
 *	Each node has its own list of partial, मुक्त and full sद_असल.
 *	All object allocations क्रम a node occur from node specअगरic slab lists.
 */

#समावेश	<linux/slab.h>
#समावेश	<linux/mm.h>
#समावेश	<linux/poison.h>
#समावेश	<linux/swap.h>
#समावेश	<linux/cache.h>
#समावेश	<linux/पूर्णांकerrupt.h>
#समावेश	<linux/init.h>
#समावेश	<linux/compiler.h>
#समावेश	<linux/cpuset.h>
#समावेश	<linux/proc_fs.h>
#समावेश	<linux/seq_file.h>
#समावेश	<linux/notअगरier.h>
#समावेश	<linux/kallsyms.h>
#समावेश	<linux/kfence.h>
#समावेश	<linux/cpu.h>
#समावेश	<linux/sysctl.h>
#समावेश	<linux/module.h>
#समावेश	<linux/rcupdate.h>
#समावेश	<linux/माला.स>
#समावेश	<linux/uaccess.h>
#समावेश	<linux/nodemask.h>
#समावेश	<linux/kmemleak.h>
#समावेश	<linux/mempolicy.h>
#समावेश	<linux/mutex.h>
#समावेश	<linux/fault-inject.h>
#समावेश	<linux/rपंचांगutex.h>
#समावेश	<linux/reciprocal_भाग.h>
#समावेश	<linux/debugobjects.h>
#समावेश	<linux/memory.h>
#समावेश	<linux/prefetch.h>
#समावेश	<linux/sched/task_stack.h>

#समावेश	<net/sock.h>

#समावेश	<यंत्र/cacheflush.h>
#समावेश	<यंत्र/tlbflush.h>
#समावेश	<यंत्र/page.h>

#समावेश <trace/events/kस्मृति.स>

#समावेश	"internal.h"

#समावेश	"slab.h"

/*
 * DEBUG	- 1 क्रम kmem_cache_create() to honour; SLAB_RED_ZONE & SLAB_POISON.
 *		  0 क्रम faster, smaller code (especially in the critical paths).
 *
 * STATS	- 1 to collect stats क्रम /proc/slabinfo.
 *		  0 क्रम faster, smaller code (especially in the critical paths).
 *
 * FORCED_DEBUG	- 1 enables SLAB_RED_ZONE and SLAB_POISON (अगर possible)
 */

#अगर_घोषित CONFIG_DEBUG_SLAB
#घोषणा	DEBUG		1
#घोषणा	STATS		1
#घोषणा	FORCED_DEBUG	1
#अन्यथा
#घोषणा	DEBUG		0
#घोषणा	STATS		0
#घोषणा	FORCED_DEBUG	0
#पूर्ण_अगर

/* Shouldn't this be in a header file somewhere? */
#घोषणा	BYTES_PER_WORD		माप(व्योम *)
#घोषणा	REDZONE_ALIGN		max(BYTES_PER_WORD, __alignof__(अचिन्हित दीर्घ दीर्घ))

#अगर_अघोषित ARCH_KMALLOC_FLAGS
#घोषणा ARCH_KMALLOC_FLAGS SLAB_HWCACHE_ALIGN
#पूर्ण_अगर

#घोषणा FREELIST_BYTE_INDEX (((PAGE_SIZE >> BITS_PER_BYTE) \
				<= SLAB_OBJ_MIN_SIZE) ? 1 : 0)

#अगर FREELIST_BYTE_INDEX
प्रकार अचिन्हित अक्षर मुक्तlist_idx_t;
#अन्यथा
प्रकार अचिन्हित लघु मुक्तlist_idx_t;
#पूर्ण_अगर

#घोषणा SLAB_OBJ_MAX_NUM ((1 << माप(मुक्तlist_idx_t) * BITS_PER_BYTE) - 1)

/*
 * काष्ठा array_cache
 *
 * Purpose:
 * - LIFO ordering, to hand out cache-warm objects from _alloc
 * - reduce the number of linked list operations
 * - reduce spinlock operations
 *
 * The limit is stored in the per-cpu काष्ठाure to reduce the data cache
 * footprपूर्णांक.
 *
 */
काष्ठा array_cache अणु
	अचिन्हित पूर्णांक avail;
	अचिन्हित पूर्णांक limit;
	अचिन्हित पूर्णांक batchcount;
	अचिन्हित पूर्णांक touched;
	व्योम *entry[];	/*
			 * Must have this definition in here क्रम the proper
			 * alignment of array_cache. Also simplअगरies accessing
			 * the entries.
			 */
पूर्ण;

काष्ठा alien_cache अणु
	spinlock_t lock;
	काष्ठा array_cache ac;
पूर्ण;

/*
 * Need this क्रम bootstrapping a per node allocator.
 */
#घोषणा NUM_INIT_LISTS (2 * MAX_NUMNODES)
अटल काष्ठा kmem_cache_node __initdata init_kmem_cache_node[NUM_INIT_LISTS];
#घोषणा	CACHE_CACHE 0
#घोषणा	SIZE_NODE (MAX_NUMNODES)

अटल पूर्णांक drain_मुक्तlist(काष्ठा kmem_cache *cache,
			काष्ठा kmem_cache_node *n, पूर्णांक toमुक्त);
अटल व्योम मुक्त_block(काष्ठा kmem_cache *cachep, व्योम **objpp, पूर्णांक len,
			पूर्णांक node, काष्ठा list_head *list);
अटल व्योम sद_असल_destroy(काष्ठा kmem_cache *cachep, काष्ठा list_head *list);
अटल पूर्णांक enable_cpucache(काष्ठा kmem_cache *cachep, gfp_t gfp);
अटल व्योम cache_reap(काष्ठा work_काष्ठा *unused);

अटल अंतरभूत व्योम fixup_objमुक्तlist_debug(काष्ठा kmem_cache *cachep,
						व्योम **list);
अटल अंतरभूत व्योम fixup_slab_list(काष्ठा kmem_cache *cachep,
				काष्ठा kmem_cache_node *n, काष्ठा page *page,
				व्योम **list);
अटल पूर्णांक slab_early_init = 1;

#घोषणा INDEX_NODE kदो_स्मृति_index(माप(काष्ठा kmem_cache_node))

अटल व्योम kmem_cache_node_init(काष्ठा kmem_cache_node *parent)
अणु
	INIT_LIST_HEAD(&parent->sद_असल_full);
	INIT_LIST_HEAD(&parent->sद_असल_partial);
	INIT_LIST_HEAD(&parent->sद_असल_मुक्त);
	parent->total_sद_असल = 0;
	parent->मुक्त_sद_असल = 0;
	parent->shared = शून्य;
	parent->alien = शून्य;
	parent->colour_next = 0;
	spin_lock_init(&parent->list_lock);
	parent->मुक्त_objects = 0;
	parent->मुक्त_touched = 0;
पूर्ण

#घोषणा MAKE_LIST(cachep, listp, slab, nodeid)				\
	करो अणु								\
		INIT_LIST_HEAD(listp);					\
		list_splice(&get_node(cachep, nodeid)->slab, listp);	\
	पूर्ण जबतक (0)

#घोषणा	MAKE_ALL_LISTS(cachep, ptr, nodeid)				\
	करो अणु								\
	MAKE_LIST((cachep), (&(ptr)->sद_असल_full), sद_असल_full, nodeid);	\
	MAKE_LIST((cachep), (&(ptr)->sद_असल_partial), sद_असल_partial, nodeid); \
	MAKE_LIST((cachep), (&(ptr)->sद_असल_मुक्त), sद_असल_मुक्त, nodeid);	\
	पूर्ण जबतक (0)

#घोषणा CFLGS_OBJFREELIST_SLAB	((slab_flags_t __क्रमce)0x40000000U)
#घोषणा CFLGS_OFF_SLAB		((slab_flags_t __क्रमce)0x80000000U)
#घोषणा	OBJFREELIST_SLAB(x)	((x)->flags & CFLGS_OBJFREELIST_SLAB)
#घोषणा	OFF_SLAB(x)	((x)->flags & CFLGS_OFF_SLAB)

#घोषणा BATCHREFILL_LIMIT	16
/*
 * Optimization question: fewer reaps means less probability क्रम unnecessary
 * cpucache drain/refill cycles.
 *
 * OTOH the cpuarrays can contain lots of objects,
 * which could lock up otherwise मुक्तable sद_असल.
 */
#घोषणा REAPTIMEOUT_AC		(2*HZ)
#घोषणा REAPTIMEOUT_NODE	(4*HZ)

#अगर STATS
#घोषणा	STATS_INC_ACTIVE(x)	((x)->num_active++)
#घोषणा	STATS_DEC_ACTIVE(x)	((x)->num_active--)
#घोषणा	STATS_INC_ALLOCED(x)	((x)->num_allocations++)
#घोषणा	STATS_INC_GROWN(x)	((x)->grown++)
#घोषणा	STATS_ADD_REAPED(x, y)	((x)->reaped += (y))
#घोषणा	STATS_SET_HIGH(x)						\
	करो अणु								\
		अगर ((x)->num_active > (x)->high_mark)			\
			(x)->high_mark = (x)->num_active;		\
	पूर्ण जबतक (0)
#घोषणा	STATS_INC_ERR(x)	((x)->errors++)
#घोषणा	STATS_INC_NODEALLOCS(x)	((x)->node_allocs++)
#घोषणा	STATS_INC_NODEFREES(x)	((x)->node_मुक्तs++)
#घोषणा STATS_INC_ACOVERFLOW(x)   ((x)->node_overflow++)
#घोषणा	STATS_SET_FREEABLE(x, i)					\
	करो अणु								\
		अगर ((x)->max_मुक्तable < i)				\
			(x)->max_मुक्तable = i;				\
	पूर्ण जबतक (0)
#घोषणा STATS_INC_ALLOCHIT(x)	atomic_inc(&(x)->allochit)
#घोषणा STATS_INC_ALLOCMISS(x)	atomic_inc(&(x)->allocmiss)
#घोषणा STATS_INC_FREEHIT(x)	atomic_inc(&(x)->मुक्तhit)
#घोषणा STATS_INC_FREEMISS(x)	atomic_inc(&(x)->मुक्तmiss)
#अन्यथा
#घोषणा	STATS_INC_ACTIVE(x)	करो अणु पूर्ण जबतक (0)
#घोषणा	STATS_DEC_ACTIVE(x)	करो अणु पूर्ण जबतक (0)
#घोषणा	STATS_INC_ALLOCED(x)	करो अणु पूर्ण जबतक (0)
#घोषणा	STATS_INC_GROWN(x)	करो अणु पूर्ण जबतक (0)
#घोषणा	STATS_ADD_REAPED(x, y)	करो अणु (व्योम)(y); पूर्ण जबतक (0)
#घोषणा	STATS_SET_HIGH(x)	करो अणु पूर्ण जबतक (0)
#घोषणा	STATS_INC_ERR(x)	करो अणु पूर्ण जबतक (0)
#घोषणा	STATS_INC_NODEALLOCS(x)	करो अणु पूर्ण जबतक (0)
#घोषणा	STATS_INC_NODEFREES(x)	करो अणु पूर्ण जबतक (0)
#घोषणा STATS_INC_ACOVERFLOW(x)   करो अणु पूर्ण जबतक (0)
#घोषणा	STATS_SET_FREEABLE(x, i) करो अणु पूर्ण जबतक (0)
#घोषणा STATS_INC_ALLOCHIT(x)	करो अणु पूर्ण जबतक (0)
#घोषणा STATS_INC_ALLOCMISS(x)	करो अणु पूर्ण जबतक (0)
#घोषणा STATS_INC_FREEHIT(x)	करो अणु पूर्ण जबतक (0)
#घोषणा STATS_INC_FREEMISS(x)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर DEBUG

/*
 * memory layout of objects:
 * 0		: objp
 * 0 .. cachep->obj_offset - BYTES_PER_WORD - 1: padding. This ensures that
 * 		the end of an object is aligned with the end of the real
 * 		allocation. Catches ग_लिखोs behind the end of the allocation.
 * cachep->obj_offset - BYTES_PER_WORD .. cachep->obj_offset - 1:
 * 		redzone word.
 * cachep->obj_offset: The real object.
 * cachep->size - 2* BYTES_PER_WORD: redzone word [BYTES_PER_WORD दीर्घ]
 * cachep->size - 1* BYTES_PER_WORD: last caller address
 *					[BYTES_PER_WORD दीर्घ]
 */
अटल पूर्णांक obj_offset(काष्ठा kmem_cache *cachep)
अणु
	वापस cachep->obj_offset;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ *dbg_redzone1(काष्ठा kmem_cache *cachep, व्योम *objp)
अणु
	BUG_ON(!(cachep->flags & SLAB_RED_ZONE));
	वापस (अचिन्हित दीर्घ दीर्घ *) (objp + obj_offset(cachep) -
				      माप(अचिन्हित दीर्घ दीर्घ));
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ *dbg_redzone2(काष्ठा kmem_cache *cachep, व्योम *objp)
अणु
	BUG_ON(!(cachep->flags & SLAB_RED_ZONE));
	अगर (cachep->flags & SLAB_STORE_USER)
		वापस (अचिन्हित दीर्घ दीर्घ *)(objp + cachep->size -
					      माप(अचिन्हित दीर्घ दीर्घ) -
					      REDZONE_ALIGN);
	वापस (अचिन्हित दीर्घ दीर्घ *) (objp + cachep->size -
				       माप(अचिन्हित दीर्घ दीर्घ));
पूर्ण

अटल व्योम **dbg_userword(काष्ठा kmem_cache *cachep, व्योम *objp)
अणु
	BUG_ON(!(cachep->flags & SLAB_STORE_USER));
	वापस (व्योम **)(objp + cachep->size - BYTES_PER_WORD);
पूर्ण

#अन्यथा

#घोषणा obj_offset(x)			0
#घोषणा dbg_redzone1(cachep, objp)	(अणुBUG(); (अचिन्हित दीर्घ दीर्घ *)शून्य;पूर्ण)
#घोषणा dbg_redzone2(cachep, objp)	(अणुBUG(); (अचिन्हित दीर्घ दीर्घ *)शून्य;पूर्ण)
#घोषणा dbg_userword(cachep, objp)	(अणुBUG(); (व्योम **)शून्य;पूर्ण)

#पूर्ण_अगर

/*
 * Do not go above this order unless 0 objects fit पूर्णांकo the slab or
 * overridden on the command line.
 */
#घोषणा	SLAB_MAX_ORDER_HI	1
#घोषणा	SLAB_MAX_ORDER_LO	0
अटल पूर्णांक slab_max_order = SLAB_MAX_ORDER_LO;
अटल bool slab_max_order_set __initdata;

अटल अंतरभूत व्योम *index_to_obj(काष्ठा kmem_cache *cache, काष्ठा page *page,
				 अचिन्हित पूर्णांक idx)
अणु
	वापस page->s_mem + cache->size * idx;
पूर्ण

#घोषणा BOOT_CPUCACHE_ENTRIES	1
/* पूर्णांकernal cache of cache description objs */
अटल काष्ठा kmem_cache kmem_cache_boot = अणु
	.batchcount = 1,
	.limit = BOOT_CPUCACHE_ENTRIES,
	.shared = 1,
	.size = माप(काष्ठा kmem_cache),
	.name = "kmem_cache",
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा delayed_work, slab_reap_work);

अटल अंतरभूत काष्ठा array_cache *cpu_cache_get(काष्ठा kmem_cache *cachep)
अणु
	वापस this_cpu_ptr(cachep->cpu_cache);
पूर्ण

/*
 * Calculate the number of objects and left-over bytes क्रम a given buffer size.
 */
अटल अचिन्हित पूर्णांक cache_estimate(अचिन्हित दीर्घ gfporder, माप_प्रकार buffer_size,
		slab_flags_t flags, माप_प्रकार *left_over)
अणु
	अचिन्हित पूर्णांक num;
	माप_प्रकार slab_size = PAGE_SIZE << gfporder;

	/*
	 * The slab management काष्ठाure can be either off the slab or
	 * on it. For the latter हाल, the memory allocated क्रम a
	 * slab is used क्रम:
	 *
	 * - @buffer_size bytes क्रम each object
	 * - One मुक्तlist_idx_t क्रम each object
	 *
	 * We करोn't need to consider alignment of मुक्तlist because
	 * मुक्तlist will be at the end of slab page. The objects will be
	 * at the correct alignment.
	 *
	 * If the slab management काष्ठाure is off the slab, then the
	 * alignment will alपढ़ोy be calculated पूर्णांकo the size. Because
	 * the sद_असल are all pages aligned, the objects will be at the
	 * correct alignment when allocated.
	 */
	अगर (flags & (CFLGS_OBJFREELIST_SLAB | CFLGS_OFF_SLAB)) अणु
		num = slab_size / buffer_size;
		*left_over = slab_size % buffer_size;
	पूर्ण अन्यथा अणु
		num = slab_size / (buffer_size + माप(मुक्तlist_idx_t));
		*left_over = slab_size %
			(buffer_size + माप(मुक्तlist_idx_t));
	पूर्ण

	वापस num;
पूर्ण

#अगर DEBUG
#घोषणा slab_error(cachep, msg) __slab_error(__func__, cachep, msg)

अटल व्योम __slab_error(स्थिर अक्षर *function, काष्ठा kmem_cache *cachep,
			अक्षर *msg)
अणु
	pr_err("slab error in %s(): cache `%s': %s\n",
	       function, cachep->name, msg);
	dump_stack();
	add_taपूर्णांक(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);
पूर्ण
#पूर्ण_अगर

/*
 * By शेष on NUMA we use alien caches to stage the मुक्तing of
 * objects allocated from other nodes. This causes massive memory
 * inefficiencies when using fake NUMA setup to split memory पूर्णांकo a
 * large number of small nodes, so it can be disabled on the command
 * line
  */

अटल पूर्णांक use_alien_caches __पढ़ो_mostly = 1;
अटल पूर्णांक __init noaliencache_setup(अक्षर *s)
अणु
	use_alien_caches = 0;
	वापस 1;
पूर्ण
__setup("noaliencache", noaliencache_setup);

अटल पूर्णांक __init slab_max_order_setup(अक्षर *str)
अणु
	get_option(&str, &slab_max_order);
	slab_max_order = slab_max_order < 0 ? 0 :
				min(slab_max_order, MAX_ORDER - 1);
	slab_max_order_set = true;

	वापस 1;
पूर्ण
__setup("slab_max_order=", slab_max_order_setup);

#अगर_घोषित CONFIG_NUMA
/*
 * Special reaping functions क्रम NUMA प्रणालीs called from cache_reap().
 * These take care of करोing round robin flushing of alien caches (containing
 * objects मुक्तd on dअगरferent nodes from which they were allocated) and the
 * flushing of remote pcps by calling drain_node_pages.
 */
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, slab_reap_node);

अटल व्योम init_reap_node(पूर्णांक cpu)
अणु
	per_cpu(slab_reap_node, cpu) = next_node_in(cpu_to_mem(cpu),
						    node_online_map);
पूर्ण

अटल व्योम next_reap_node(व्योम)
अणु
	पूर्णांक node = __this_cpu_पढ़ो(slab_reap_node);

	node = next_node_in(node, node_online_map);
	__this_cpu_ग_लिखो(slab_reap_node, node);
पूर्ण

#अन्यथा
#घोषणा init_reap_node(cpu) करो अणु पूर्ण जबतक (0)
#घोषणा next_reap_node(व्योम) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Initiate the reap समयr running on the target CPU.  We run at around 1 to 2Hz
 * via the workqueue/eventd.
 * Add the CPU number पूर्णांकo the expiration समय to minimize the possibility of
 * the CPUs getting पूर्णांकo lockstep and contending क्रम the global cache chain
 * lock.
 */
अटल व्योम start_cpu_समयr(पूर्णांक cpu)
अणु
	काष्ठा delayed_work *reap_work = &per_cpu(slab_reap_work, cpu);

	अगर (reap_work->work.func == शून्य) अणु
		init_reap_node(cpu);
		INIT_DEFERRABLE_WORK(reap_work, cache_reap);
		schedule_delayed_work_on(cpu, reap_work,
					__round_jअगरfies_relative(HZ, cpu));
	पूर्ण
पूर्ण

अटल व्योम init_arraycache(काष्ठा array_cache *ac, पूर्णांक limit, पूर्णांक batch)
अणु
	अगर (ac) अणु
		ac->avail = 0;
		ac->limit = limit;
		ac->batchcount = batch;
		ac->touched = 0;
	पूर्ण
पूर्ण

अटल काष्ठा array_cache *alloc_arraycache(पूर्णांक node, पूर्णांक entries,
					    पूर्णांक batchcount, gfp_t gfp)
अणु
	माप_प्रकार memsize = माप(व्योम *) * entries + माप(काष्ठा array_cache);
	काष्ठा array_cache *ac = शून्य;

	ac = kदो_स्मृति_node(memsize, gfp, node);
	/*
	 * The array_cache काष्ठाures contain poपूर्णांकers to मुक्त object.
	 * However, when such objects are allocated or transferred to another
	 * cache the poपूर्णांकers are not cleared and they could be counted as
	 * valid references during a kmemleak scan. Thereक्रमe, kmemleak must
	 * not scan such objects.
	 */
	kmemleak_no_scan(ac);
	init_arraycache(ac, entries, batchcount);
	वापस ac;
पूर्ण

अटल noअंतरभूत व्योम cache_मुक्त_pfmeदो_स्मृति(काष्ठा kmem_cache *cachep,
					काष्ठा page *page, व्योम *objp)
अणु
	काष्ठा kmem_cache_node *n;
	पूर्णांक page_node;
	LIST_HEAD(list);

	page_node = page_to_nid(page);
	n = get_node(cachep, page_node);

	spin_lock(&n->list_lock);
	मुक्त_block(cachep, &objp, 1, page_node, &list);
	spin_unlock(&n->list_lock);

	sद_असल_destroy(cachep, &list);
पूर्ण

/*
 * Transfer objects in one arraycache to another.
 * Locking must be handled by the caller.
 *
 * Return the number of entries transferred.
 */
अटल पूर्णांक transfer_objects(काष्ठा array_cache *to,
		काष्ठा array_cache *from, अचिन्हित पूर्णांक max)
अणु
	/* Figure out how many entries to transfer */
	पूर्णांक nr = min3(from->avail, max, to->limit - to->avail);

	अगर (!nr)
		वापस 0;

	स_नकल(to->entry + to->avail, from->entry + from->avail - nr,
			माप(व्योम *) *nr);

	from->avail -= nr;
	to->avail += nr;
	वापस nr;
पूर्ण

/* &alien->lock must be held by alien callers. */
अटल __always_अंतरभूत व्योम __मुक्त_one(काष्ठा array_cache *ac, व्योम *objp)
अणु
	/* Aव्योम trivial द्विगुन-मुक्त. */
	अगर (IS_ENABLED(CONFIG_SLAB_FREELIST_HARDENED) &&
	    WARN_ON_ONCE(ac->avail > 0 && ac->entry[ac->avail - 1] == objp))
		वापस;
	ac->entry[ac->avail++] = objp;
पूर्ण

#अगर_अघोषित CONFIG_NUMA

#घोषणा drain_alien_cache(cachep, alien) करो अणु पूर्ण जबतक (0)
#घोषणा reap_alien(cachep, n) करो अणु पूर्ण जबतक (0)

अटल अंतरभूत काष्ठा alien_cache **alloc_alien_cache(पूर्णांक node,
						पूर्णांक limit, gfp_t gfp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम मुक्त_alien_cache(काष्ठा alien_cache **ac_ptr)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक cache_मुक्त_alien(काष्ठा kmem_cache *cachep, व्योम *objp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *alternate_node_alloc(काष्ठा kmem_cache *cachep,
		gfp_t flags)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम *____cache_alloc_node(काष्ठा kmem_cache *cachep,
		 gfp_t flags, पूर्णांक nodeid)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत gfp_t gfp_exact_node(gfp_t flags)
अणु
	वापस flags & ~__GFP_NOFAIL;
पूर्ण

#अन्यथा	/* CONFIG_NUMA */

अटल व्योम *____cache_alloc_node(काष्ठा kmem_cache *, gfp_t, पूर्णांक);
अटल व्योम *alternate_node_alloc(काष्ठा kmem_cache *, gfp_t);

अटल काष्ठा alien_cache *__alloc_alien_cache(पूर्णांक node, पूर्णांक entries,
						पूर्णांक batch, gfp_t gfp)
अणु
	माप_प्रकार memsize = माप(व्योम *) * entries + माप(काष्ठा alien_cache);
	काष्ठा alien_cache *alc = शून्य;

	alc = kदो_स्मृति_node(memsize, gfp, node);
	अगर (alc) अणु
		kmemleak_no_scan(alc);
		init_arraycache(&alc->ac, entries, batch);
		spin_lock_init(&alc->lock);
	पूर्ण
	वापस alc;
पूर्ण

अटल काष्ठा alien_cache **alloc_alien_cache(पूर्णांक node, पूर्णांक limit, gfp_t gfp)
अणु
	काष्ठा alien_cache **alc_ptr;
	पूर्णांक i;

	अगर (limit > 1)
		limit = 12;
	alc_ptr = kसुस्मृति_node(nr_node_ids, माप(व्योम *), gfp, node);
	अगर (!alc_ptr)
		वापस शून्य;

	क्रम_each_node(i) अणु
		अगर (i == node || !node_online(i))
			जारी;
		alc_ptr[i] = __alloc_alien_cache(node, limit, 0xbaadf00d, gfp);
		अगर (!alc_ptr[i]) अणु
			क्रम (i--; i >= 0; i--)
				kमुक्त(alc_ptr[i]);
			kमुक्त(alc_ptr);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस alc_ptr;
पूर्ण

अटल व्योम मुक्त_alien_cache(काष्ठा alien_cache **alc_ptr)
अणु
	पूर्णांक i;

	अगर (!alc_ptr)
		वापस;
	क्रम_each_node(i)
	    kमुक्त(alc_ptr[i]);
	kमुक्त(alc_ptr);
पूर्ण

अटल व्योम __drain_alien_cache(काष्ठा kmem_cache *cachep,
				काष्ठा array_cache *ac, पूर्णांक node,
				काष्ठा list_head *list)
अणु
	काष्ठा kmem_cache_node *n = get_node(cachep, node);

	अगर (ac->avail) अणु
		spin_lock(&n->list_lock);
		/*
		 * Stuff objects पूर्णांकo the remote nodes shared array first.
		 * That way we could aव्योम the overhead of putting the objects
		 * पूर्णांकo the मुक्त lists and getting them back later.
		 */
		अगर (n->shared)
			transfer_objects(n->shared, ac, ac->limit);

		मुक्त_block(cachep, ac->entry, ac->avail, node, list);
		ac->avail = 0;
		spin_unlock(&n->list_lock);
	पूर्ण
पूर्ण

/*
 * Called from cache_reap() to regularly drain alien caches round robin.
 */
अटल व्योम reap_alien(काष्ठा kmem_cache *cachep, काष्ठा kmem_cache_node *n)
अणु
	पूर्णांक node = __this_cpu_पढ़ो(slab_reap_node);

	अगर (n->alien) अणु
		काष्ठा alien_cache *alc = n->alien[node];
		काष्ठा array_cache *ac;

		अगर (alc) अणु
			ac = &alc->ac;
			अगर (ac->avail && spin_trylock_irq(&alc->lock)) अणु
				LIST_HEAD(list);

				__drain_alien_cache(cachep, ac, node, &list);
				spin_unlock_irq(&alc->lock);
				sद_असल_destroy(cachep, &list);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम drain_alien_cache(काष्ठा kmem_cache *cachep,
				काष्ठा alien_cache **alien)
अणु
	पूर्णांक i = 0;
	काष्ठा alien_cache *alc;
	काष्ठा array_cache *ac;
	अचिन्हित दीर्घ flags;

	क्रम_each_online_node(i) अणु
		alc = alien[i];
		अगर (alc) अणु
			LIST_HEAD(list);

			ac = &alc->ac;
			spin_lock_irqsave(&alc->lock, flags);
			__drain_alien_cache(cachep, ac, i, &list);
			spin_unlock_irqrestore(&alc->lock, flags);
			sद_असल_destroy(cachep, &list);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __cache_मुक्त_alien(काष्ठा kmem_cache *cachep, व्योम *objp,
				पूर्णांक node, पूर्णांक page_node)
अणु
	काष्ठा kmem_cache_node *n;
	काष्ठा alien_cache *alien = शून्य;
	काष्ठा array_cache *ac;
	LIST_HEAD(list);

	n = get_node(cachep, node);
	STATS_INC_NODEFREES(cachep);
	अगर (n->alien && n->alien[page_node]) अणु
		alien = n->alien[page_node];
		ac = &alien->ac;
		spin_lock(&alien->lock);
		अगर (unlikely(ac->avail == ac->limit)) अणु
			STATS_INC_ACOVERFLOW(cachep);
			__drain_alien_cache(cachep, ac, page_node, &list);
		पूर्ण
		__मुक्त_one(ac, objp);
		spin_unlock(&alien->lock);
		sद_असल_destroy(cachep, &list);
	पूर्ण अन्यथा अणु
		n = get_node(cachep, page_node);
		spin_lock(&n->list_lock);
		मुक्त_block(cachep, &objp, 1, page_node, &list);
		spin_unlock(&n->list_lock);
		sद_असल_destroy(cachep, &list);
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक cache_मुक्त_alien(काष्ठा kmem_cache *cachep, व्योम *objp)
अणु
	पूर्णांक page_node = page_to_nid(virt_to_page(objp));
	पूर्णांक node = numa_mem_id();
	/*
	 * Make sure we are not मुक्तing a object from another node to the array
	 * cache on this cpu.
	 */
	अगर (likely(node == page_node))
		वापस 0;

	वापस __cache_मुक्त_alien(cachep, objp, node, page_node);
पूर्ण

/*
 * Conकाष्ठा gfp mask to allocate from a specअगरic node but करो not reclaim or
 * warn about failures.
 */
अटल अंतरभूत gfp_t gfp_exact_node(gfp_t flags)
अणु
	वापस (flags | __GFP_THISNODE | __GFP_NOWARN) & ~(__GFP_RECLAIM|__GFP_NOFAIL);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक init_cache_node(काष्ठा kmem_cache *cachep, पूर्णांक node, gfp_t gfp)
अणु
	काष्ठा kmem_cache_node *n;

	/*
	 * Set up the kmem_cache_node क्रम cpu beक्रमe we can
	 * begin anything. Make sure some other cpu on this
	 * node has not alपढ़ोy allocated this
	 */
	n = get_node(cachep, node);
	अगर (n) अणु
		spin_lock_irq(&n->list_lock);
		n->मुक्त_limit = (1 + nr_cpus_node(node)) * cachep->batchcount +
				cachep->num;
		spin_unlock_irq(&n->list_lock);

		वापस 0;
	पूर्ण

	n = kदो_स्मृति_node(माप(काष्ठा kmem_cache_node), gfp, node);
	अगर (!n)
		वापस -ENOMEM;

	kmem_cache_node_init(n);
	n->next_reap = jअगरfies + REAPTIMEOUT_NODE +
		    ((अचिन्हित दीर्घ)cachep) % REAPTIMEOUT_NODE;

	n->मुक्त_limit =
		(1 + nr_cpus_node(node)) * cachep->batchcount + cachep->num;

	/*
	 * The kmem_cache_nodes करोn't come and go as CPUs
	 * come and go.  slab_mutex is sufficient
	 * protection here.
	 */
	cachep->node[node] = n;

	वापस 0;
पूर्ण

#अगर (defined(CONFIG_NUMA) && defined(CONFIG_MEMORY_HOTPLUG)) || defined(CONFIG_SMP)
/*
 * Allocates and initializes node क्रम a node on each slab cache, used क्रम
 * either memory or cpu hotplug.  If memory is being hot-added, the kmem_cache_node
 * will be allocated off-node since memory is not yet online क्रम the new node.
 * When hotplugging memory or a cpu, existing node are not replaced अगर
 * alपढ़ोy in use.
 *
 * Must hold slab_mutex.
 */
अटल पूर्णांक init_cache_node_node(पूर्णांक node)
अणु
	पूर्णांक ret;
	काष्ठा kmem_cache *cachep;

	list_क्रम_each_entry(cachep, &slab_caches, list) अणु
		ret = init_cache_node(cachep, node, GFP_KERNEL);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक setup_kmem_cache_node(काष्ठा kmem_cache *cachep,
				पूर्णांक node, gfp_t gfp, bool क्रमce_change)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा kmem_cache_node *n;
	काष्ठा array_cache *old_shared = शून्य;
	काष्ठा array_cache *new_shared = शून्य;
	काष्ठा alien_cache **new_alien = शून्य;
	LIST_HEAD(list);

	अगर (use_alien_caches) अणु
		new_alien = alloc_alien_cache(node, cachep->limit, gfp);
		अगर (!new_alien)
			जाओ fail;
	पूर्ण

	अगर (cachep->shared) अणु
		new_shared = alloc_arraycache(node,
			cachep->shared * cachep->batchcount, 0xbaadf00d, gfp);
		अगर (!new_shared)
			जाओ fail;
	पूर्ण

	ret = init_cache_node(cachep, node, gfp);
	अगर (ret)
		जाओ fail;

	n = get_node(cachep, node);
	spin_lock_irq(&n->list_lock);
	अगर (n->shared && क्रमce_change) अणु
		मुक्त_block(cachep, n->shared->entry,
				n->shared->avail, node, &list);
		n->shared->avail = 0;
	पूर्ण

	अगर (!n->shared || क्रमce_change) अणु
		old_shared = n->shared;
		n->shared = new_shared;
		new_shared = शून्य;
	पूर्ण

	अगर (!n->alien) अणु
		n->alien = new_alien;
		new_alien = शून्य;
	पूर्ण

	spin_unlock_irq(&n->list_lock);
	sद_असल_destroy(cachep, &list);

	/*
	 * To protect lockless access to n->shared during irq disabled context.
	 * If n->shared isn't शून्य in irq disabled context, accessing to it is
	 * guaranteed to be valid until irq is re-enabled, because it will be
	 * मुक्तd after synchronize_rcu().
	 */
	अगर (old_shared && क्रमce_change)
		synchronize_rcu();

fail:
	kमुक्त(old_shared);
	kमुक्त(new_shared);
	मुक्त_alien_cache(new_alien);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम cpuup_canceled(दीर्घ cpu)
अणु
	काष्ठा kmem_cache *cachep;
	काष्ठा kmem_cache_node *n = शून्य;
	पूर्णांक node = cpu_to_mem(cpu);
	स्थिर काष्ठा cpumask *mask = cpumask_of_node(node);

	list_क्रम_each_entry(cachep, &slab_caches, list) अणु
		काष्ठा array_cache *nc;
		काष्ठा array_cache *shared;
		काष्ठा alien_cache **alien;
		LIST_HEAD(list);

		n = get_node(cachep, node);
		अगर (!n)
			जारी;

		spin_lock_irq(&n->list_lock);

		/* Free limit क्रम this kmem_cache_node */
		n->मुक्त_limit -= cachep->batchcount;

		/* cpu is dead; no one can alloc from it. */
		nc = per_cpu_ptr(cachep->cpu_cache, cpu);
		मुक्त_block(cachep, nc->entry, nc->avail, node, &list);
		nc->avail = 0;

		अगर (!cpumask_empty(mask)) अणु
			spin_unlock_irq(&n->list_lock);
			जाओ मुक्त_slab;
		पूर्ण

		shared = n->shared;
		अगर (shared) अणु
			मुक्त_block(cachep, shared->entry,
				   shared->avail, node, &list);
			n->shared = शून्य;
		पूर्ण

		alien = n->alien;
		n->alien = शून्य;

		spin_unlock_irq(&n->list_lock);

		kमुक्त(shared);
		अगर (alien) अणु
			drain_alien_cache(cachep, alien);
			मुक्त_alien_cache(alien);
		पूर्ण

मुक्त_slab:
		sद_असल_destroy(cachep, &list);
	पूर्ण
	/*
	 * In the previous loop, all the objects were मुक्तd to
	 * the respective cache's sद_असल,  now we can go ahead and
	 * shrink each nodelist to its limit.
	 */
	list_क्रम_each_entry(cachep, &slab_caches, list) अणु
		n = get_node(cachep, node);
		अगर (!n)
			जारी;
		drain_मुक्तlist(cachep, n, पूर्णांक_उच्च);
	पूर्ण
पूर्ण

अटल पूर्णांक cpuup_prepare(दीर्घ cpu)
अणु
	काष्ठा kmem_cache *cachep;
	पूर्णांक node = cpu_to_mem(cpu);
	पूर्णांक err;

	/*
	 * We need to करो this right in the beginning since
	 * alloc_arraycache's are going to use this list.
	 * kदो_स्मृति_node allows us to add the slab to the right
	 * kmem_cache_node and not this cpu's kmem_cache_node
	 */
	err = init_cache_node_node(node);
	अगर (err < 0)
		जाओ bad;

	/*
	 * Now we can go ahead with allocating the shared arrays and
	 * array caches
	 */
	list_क्रम_each_entry(cachep, &slab_caches, list) अणु
		err = setup_kmem_cache_node(cachep, node, GFP_KERNEL, false);
		अगर (err)
			जाओ bad;
	पूर्ण

	वापस 0;
bad:
	cpuup_canceled(cpu);
	वापस -ENOMEM;
पूर्ण

पूर्णांक slab_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक err;

	mutex_lock(&slab_mutex);
	err = cpuup_prepare(cpu);
	mutex_unlock(&slab_mutex);
	वापस err;
पूर्ण

/*
 * This is called क्रम a failed online attempt and क्रम a successful
 * offline.
 *
 * Even अगर all the cpus of a node are करोwn, we करोn't मुक्त the
 * kmem_cache_node of any cache. This to aव्योम a race between cpu_करोwn, and
 * a kदो_स्मृति allocation from another cpu क्रम memory from the node of
 * the cpu going करोwn.  The kmem_cache_node काष्ठाure is usually allocated from
 * kmem_cache_create() and माला_लो destroyed at kmem_cache_destroy().
 */
पूर्णांक slab_dead_cpu(अचिन्हित पूर्णांक cpu)
अणु
	mutex_lock(&slab_mutex);
	cpuup_canceled(cpu);
	mutex_unlock(&slab_mutex);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक slab_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	start_cpu_समयr(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक slab_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * Shutकरोwn cache reaper. Note that the slab_mutex is held so
	 * that अगर cache_reap() is invoked it cannot करो anything
	 * expensive but will only modअगरy reap_work and reschedule the
	 * समयr.
	 */
	cancel_delayed_work_sync(&per_cpu(slab_reap_work, cpu));
	/* Now the cache_reaper is guaranteed to be not running. */
	per_cpu(slab_reap_work, cpu).work.func = शून्य;
	वापस 0;
पूर्ण

#अगर defined(CONFIG_NUMA) && defined(CONFIG_MEMORY_HOTPLUG)
/*
 * Drains मुक्तlist क्रम a node on each slab cache, used क्रम memory hot-हटाओ.
 * Returns -EBUSY अगर all objects cannot be drained so that the node is not
 * हटाओd.
 *
 * Must hold slab_mutex.
 */
अटल पूर्णांक __meminit drain_cache_node_node(पूर्णांक node)
अणु
	काष्ठा kmem_cache *cachep;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(cachep, &slab_caches, list) अणु
		काष्ठा kmem_cache_node *n;

		n = get_node(cachep, node);
		अगर (!n)
			जारी;

		drain_मुक्तlist(cachep, n, पूर्णांक_उच्च);

		अगर (!list_empty(&n->sद_असल_full) ||
		    !list_empty(&n->sद_असल_partial)) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __meminit slab_memory_callback(काष्ठा notअगरier_block *self,
					अचिन्हित दीर्घ action, व्योम *arg)
अणु
	काष्ठा memory_notअगरy *mnb = arg;
	पूर्णांक ret = 0;
	पूर्णांक nid;

	nid = mnb->status_change_nid;
	अगर (nid < 0)
		जाओ out;

	चयन (action) अणु
	हाल MEM_GOING_ONLINE:
		mutex_lock(&slab_mutex);
		ret = init_cache_node_node(nid);
		mutex_unlock(&slab_mutex);
		अवरोध;
	हाल MEM_GOING_OFFLINE:
		mutex_lock(&slab_mutex);
		ret = drain_cache_node_node(nid);
		mutex_unlock(&slab_mutex);
		अवरोध;
	हाल MEM_ONLINE:
	हाल MEM_OFFLINE:
	हाल MEM_CANCEL_ONLINE:
	हाल MEM_CANCEL_OFFLINE:
		अवरोध;
	पूर्ण
out:
	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA && CONFIG_MEMORY_HOTPLUG */

/*
 * swap the अटल kmem_cache_node with kदो_स्मृतिed memory
 */
अटल व्योम __init init_list(काष्ठा kmem_cache *cachep, काष्ठा kmem_cache_node *list,
				पूर्णांक nodeid)
अणु
	काष्ठा kmem_cache_node *ptr;

	ptr = kदो_स्मृति_node(माप(काष्ठा kmem_cache_node), GFP_NOWAIT, nodeid);
	BUG_ON(!ptr);

	स_नकल(ptr, list, माप(काष्ठा kmem_cache_node));
	/*
	 * Do not assume that spinlocks can be initialized via स_नकल:
	 */
	spin_lock_init(&ptr->list_lock);

	MAKE_ALL_LISTS(cachep, ptr, nodeid);
	cachep->node[nodeid] = ptr;
पूर्ण

/*
 * For setting up all the kmem_cache_node क्रम cache whose buffer_size is same as
 * size of kmem_cache_node.
 */
अटल व्योम __init set_up_node(काष्ठा kmem_cache *cachep, पूर्णांक index)
अणु
	पूर्णांक node;

	क्रम_each_online_node(node) अणु
		cachep->node[node] = &init_kmem_cache_node[index + node];
		cachep->node[node]->next_reap = jअगरfies +
		    REAPTIMEOUT_NODE +
		    ((अचिन्हित दीर्घ)cachep) % REAPTIMEOUT_NODE;
	पूर्ण
पूर्ण

/*
 * Initialisation.  Called after the page allocator have been initialised and
 * beक्रमe smp_init().
 */
व्योम __init kmem_cache_init(व्योम)
अणु
	पूर्णांक i;

	kmem_cache = &kmem_cache_boot;

	अगर (!IS_ENABLED(CONFIG_NUMA) || num_possible_nodes() == 1)
		use_alien_caches = 0;

	क्रम (i = 0; i < NUM_INIT_LISTS; i++)
		kmem_cache_node_init(&init_kmem_cache_node[i]);

	/*
	 * Fragmentation resistance on low memory - only use bigger
	 * page orders on machines with more than 32MB of memory अगर
	 * not overridden on the command line.
	 */
	अगर (!slab_max_order_set && totalram_pages() > (32 << 20) >> PAGE_SHIFT)
		slab_max_order = SLAB_MAX_ORDER_HI;

	/* Bootstrap is tricky, because several objects are allocated
	 * from caches that करो not exist yet:
	 * 1) initialize the kmem_cache cache: it contains the काष्ठा
	 *    kmem_cache काष्ठाures of all caches, except kmem_cache itself:
	 *    kmem_cache is अटलally allocated.
	 *    Initially an __init data area is used क्रम the head array and the
	 *    kmem_cache_node काष्ठाures, it's replaced with a kदो_स्मृति allocated
	 *    array at the end of the bootstrap.
	 * 2) Create the first kदो_स्मृति cache.
	 *    The काष्ठा kmem_cache क्रम the new cache is allocated normally.
	 *    An __init data area is used क्रम the head array.
	 * 3) Create the reमुख्यing kदो_स्मृति caches, with minimally sized
	 *    head arrays.
	 * 4) Replace the __init data head arrays क्रम kmem_cache and the first
	 *    kदो_स्मृति cache with kदो_स्मृति allocated arrays.
	 * 5) Replace the __init data क्रम kmem_cache_node क्रम kmem_cache and
	 *    the other cache's with kदो_स्मृति allocated memory.
	 * 6) Resize the head arrays of the kदो_स्मृति caches to their final sizes.
	 */

	/* 1) create the kmem_cache */

	/*
	 * काष्ठा kmem_cache size depends on nr_node_ids & nr_cpu_ids
	 */
	create_boot_cache(kmem_cache, "kmem_cache",
		दुरत्व(काष्ठा kmem_cache, node) +
				  nr_node_ids * माप(काष्ठा kmem_cache_node *),
				  SLAB_HWCACHE_ALIGN, 0, 0);
	list_add(&kmem_cache->list, &slab_caches);
	slab_state = PARTIAL;

	/*
	 * Initialize the caches that provide memory क्रम the  kmem_cache_node
	 * काष्ठाures first.  Without this, further allocations will bug.
	 */
	kदो_स्मृति_caches[KMALLOC_NORMAL][INDEX_NODE] = create_kदो_स्मृति_cache(
				kदो_स्मृति_info[INDEX_NODE].name[KMALLOC_NORMAL],
				kदो_स्मृति_info[INDEX_NODE].size,
				ARCH_KMALLOC_FLAGS, 0,
				kदो_स्मृति_info[INDEX_NODE].size);
	slab_state = PARTIAL_NODE;
	setup_kदो_स्मृति_cache_index_table();

	slab_early_init = 0;

	/* 5) Replace the bootstrap kmem_cache_node */
	अणु
		पूर्णांक nid;

		क्रम_each_online_node(nid) अणु
			init_list(kmem_cache, &init_kmem_cache_node[CACHE_CACHE + nid], nid);

			init_list(kदो_स्मृति_caches[KMALLOC_NORMAL][INDEX_NODE],
					  &init_kmem_cache_node[SIZE_NODE + nid], nid);
		पूर्ण
	पूर्ण

	create_kदो_स्मृति_caches(ARCH_KMALLOC_FLAGS);
पूर्ण

व्योम __init kmem_cache_init_late(व्योम)
अणु
	काष्ठा kmem_cache *cachep;

	/* 6) resize the head arrays to their final sizes */
	mutex_lock(&slab_mutex);
	list_क्रम_each_entry(cachep, &slab_caches, list)
		अगर (enable_cpucache(cachep, GFP_NOWAIT))
			BUG();
	mutex_unlock(&slab_mutex);

	/* Done! */
	slab_state = FULL;

#अगर_घोषित CONFIG_NUMA
	/*
	 * Register a memory hotplug callback that initializes and मुक्तs
	 * node.
	 */
	hotplug_memory_notअगरier(slab_memory_callback, SLAB_CALLBACK_PRI);
#पूर्ण_अगर

	/*
	 * The reap समयrs are started later, with a module init call: That part
	 * of the kernel is not yet operational.
	 */
पूर्ण

अटल पूर्णांक __init cpucache_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * Register the समयrs that वापस unneeded pages to the page allocator
	 */
	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "SLAB online",
				slab_online_cpu, slab_offline_cpu);
	WARN_ON(ret < 0);

	वापस 0;
पूर्ण
__initcall(cpucache_init);

अटल noअंतरभूत व्योम
slab_out_of_memory(काष्ठा kmem_cache *cachep, gfp_t gfpflags, पूर्णांक nodeid)
अणु
#अगर DEBUG
	काष्ठा kmem_cache_node *n;
	अचिन्हित दीर्घ flags;
	पूर्णांक node;
	अटल DEFINE_RATELIMIT_STATE(slab_oom_rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);

	अगर ((gfpflags & __GFP_NOWARN) || !__ratelimit(&slab_oom_rs))
		वापस;

	pr_warn("SLAB: Unable to allocate memory on node %d, gfp=%#x(%pGg)\n",
		nodeid, gfpflags, &gfpflags);
	pr_warn("  cache: %s, object size: %d, order: %d\n",
		cachep->name, cachep->size, cachep->gfporder);

	क्रम_each_kmem_cache_node(cachep, node, n) अणु
		अचिन्हित दीर्घ total_sद_असल, मुक्त_sद_असल, मुक्त_objs;

		spin_lock_irqsave(&n->list_lock, flags);
		total_sद_असल = n->total_sद_असल;
		मुक्त_sद_असल = n->मुक्त_sद_असल;
		मुक्त_objs = n->मुक्त_objects;
		spin_unlock_irqrestore(&n->list_lock, flags);

		pr_warn("  node %d: slabs: %ld/%ld, objs: %ld/%ld\n",
			node, total_sद_असल - मुक्त_sद_असल, total_sद_असल,
			(total_sद_असल * cachep->num) - मुक्त_objs,
			total_sद_असल * cachep->num);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Interface to प्रणाली's page allocator. No need to hold the
 * kmem_cache_node ->list_lock.
 *
 * If we requested dmaable memory, we will get it. Even अगर we
 * did not request dmaable memory, we might get it, but that
 * would be relatively rare and ignorable.
 */
अटल काष्ठा page *kmem_getpages(काष्ठा kmem_cache *cachep, gfp_t flags,
								पूर्णांक nodeid)
अणु
	काष्ठा page *page;

	flags |= cachep->allocflags;

	page = __alloc_pages_node(nodeid, flags, cachep->gfporder);
	अगर (!page) अणु
		slab_out_of_memory(cachep, flags, nodeid);
		वापस शून्य;
	पूर्ण

	account_slab_page(page, cachep->gfporder, cachep, flags);
	__SetPageSlab(page);
	/* Record अगर ALLOC_NO_WATERMARKS was set when allocating the slab */
	अगर (sk_meदो_स्मृति_socks() && page_is_pfmeदो_स्मृति(page))
		SetPageSlabPfmeदो_स्मृति(page);

	वापस page;
पूर्ण

/*
 * Interface to प्रणाली's page release.
 */
अटल व्योम kmem_मुक्तpages(काष्ठा kmem_cache *cachep, काष्ठा page *page)
अणु
	पूर्णांक order = cachep->gfporder;

	BUG_ON(!PageSlab(page));
	__ClearPageSlabPfmeदो_स्मृति(page);
	__ClearPageSlab(page);
	page_mapcount_reset(page);
	/* In जोड़ with page->mapping where page allocator expects शून्य */
	page->slab_cache = शून्य;

	अगर (current->reclaim_state)
		current->reclaim_state->reclaimed_slab += 1 << order;
	unaccount_slab_page(page, order, cachep);
	__मुक्त_pages(page, order);
पूर्ण

अटल व्योम kmem_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा kmem_cache *cachep;
	काष्ठा page *page;

	page = container_of(head, काष्ठा page, rcu_head);
	cachep = page->slab_cache;

	kmem_मुक्तpages(cachep, page);
पूर्ण

#अगर DEBUG
अटल bool is_debug_pagealloc_cache(काष्ठा kmem_cache *cachep)
अणु
	अगर (debug_pagealloc_enabled_अटल() && OFF_SLAB(cachep) &&
		(cachep->size % PAGE_SIZE) == 0)
		वापस true;

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
अटल व्योम slab_kernel_map(काष्ठा kmem_cache *cachep, व्योम *objp, पूर्णांक map)
अणु
	अगर (!is_debug_pagealloc_cache(cachep))
		वापस;

	__kernel_map_pages(virt_to_page(objp), cachep->size / PAGE_SIZE, map);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम slab_kernel_map(काष्ठा kmem_cache *cachep, व्योम *objp,
				पूर्णांक map) अणुपूर्ण

#पूर्ण_अगर

अटल व्योम poison_obj(काष्ठा kmem_cache *cachep, व्योम *addr, अचिन्हित अक्षर val)
अणु
	पूर्णांक size = cachep->object_size;
	addr = &((अक्षर *)addr)[obj_offset(cachep)];

	स_रखो(addr, val, size);
	*(अचिन्हित अक्षर *)(addr + size - 1) = POISON_END;
पूर्ण

अटल व्योम dump_line(अक्षर *data, पूर्णांक offset, पूर्णांक limit)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर error = 0;
	पूर्णांक bad_count = 0;

	pr_err("%03x: ", offset);
	क्रम (i = 0; i < limit; i++) अणु
		अगर (data[offset + i] != POISON_FREE) अणु
			error = data[offset + i];
			bad_count++;
		पूर्ण
	पूर्ण
	prपूर्णांक_hex_dump(KERN_CONT, "", 0, 16, 1,
			&data[offset], limit, 1);

	अगर (bad_count == 1) अणु
		error ^= POISON_FREE;
		अगर (!(error & (error - 1))) अणु
			pr_err("Single bit error detected. Probably bad RAM.\n");
#अगर_घोषित CONFIG_X86
			pr_err("Run memtest86+ or a similar memory test tool.\n");
#अन्यथा
			pr_err("Run a memory test tool.\n");
#पूर्ण_अगर
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर DEBUG

अटल व्योम prपूर्णांक_objinfo(काष्ठा kmem_cache *cachep, व्योम *objp, पूर्णांक lines)
अणु
	पूर्णांक i, size;
	अक्षर *realobj;

	अगर (cachep->flags & SLAB_RED_ZONE) अणु
		pr_err("Redzone: 0x%llx/0x%llx\n",
		       *dbg_redzone1(cachep, objp),
		       *dbg_redzone2(cachep, objp));
	पूर्ण

	अगर (cachep->flags & SLAB_STORE_USER)
		pr_err("Last user: (%pSR)\n", *dbg_userword(cachep, objp));
	realobj = (अक्षर *)objp + obj_offset(cachep);
	size = cachep->object_size;
	क्रम (i = 0; i < size && lines; i += 16, lines--) अणु
		पूर्णांक limit;
		limit = 16;
		अगर (i + limit > size)
			limit = size - i;
		dump_line(realobj, i, limit);
	पूर्ण
पूर्ण

अटल व्योम check_poison_obj(काष्ठा kmem_cache *cachep, व्योम *objp)
अणु
	अक्षर *realobj;
	पूर्णांक size, i;
	पूर्णांक lines = 0;

	अगर (is_debug_pagealloc_cache(cachep))
		वापस;

	realobj = (अक्षर *)objp + obj_offset(cachep);
	size = cachep->object_size;

	क्रम (i = 0; i < size; i++) अणु
		अक्षर exp = POISON_FREE;
		अगर (i == size - 1)
			exp = POISON_END;
		अगर (realobj[i] != exp) अणु
			पूर्णांक limit;
			/* Mismatch ! */
			/* Prपूर्णांक header */
			अगर (lines == 0) अणु
				pr_err("Slab corruption (%s): %s start=%px, len=%d\n",
				       prपूर्णांक_taपूर्णांकed(), cachep->name,
				       realobj, size);
				prपूर्णांक_objinfo(cachep, objp, 0);
			पूर्ण
			/* Hexdump the affected line */
			i = (i / 16) * 16;
			limit = 16;
			अगर (i + limit > size)
				limit = size - i;
			dump_line(realobj, i, limit);
			i += 16;
			lines++;
			/* Limit to 5 lines */
			अगर (lines > 5)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (lines != 0) अणु
		/* Prपूर्णांक some data about the neighboring objects, अगर they
		 * exist:
		 */
		काष्ठा page *page = virt_to_head_page(objp);
		अचिन्हित पूर्णांक objnr;

		objnr = obj_to_index(cachep, page, objp);
		अगर (objnr) अणु
			objp = index_to_obj(cachep, page, objnr - 1);
			realobj = (अक्षर *)objp + obj_offset(cachep);
			pr_err("Prev obj: start=%px, len=%d\n", realobj, size);
			prपूर्णांक_objinfo(cachep, objp, 2);
		पूर्ण
		अगर (objnr + 1 < cachep->num) अणु
			objp = index_to_obj(cachep, page, objnr + 1);
			realobj = (अक्षर *)objp + obj_offset(cachep);
			pr_err("Next obj: start=%px, len=%d\n", realobj, size);
			prपूर्णांक_objinfo(cachep, objp, 2);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर DEBUG
अटल व्योम slab_destroy_debugcheck(काष्ठा kmem_cache *cachep,
						काष्ठा page *page)
अणु
	पूर्णांक i;

	अगर (OBJFREELIST_SLAB(cachep) && cachep->flags & SLAB_POISON) अणु
		poison_obj(cachep, page->मुक्तlist - obj_offset(cachep),
			POISON_FREE);
	पूर्ण

	क्रम (i = 0; i < cachep->num; i++) अणु
		व्योम *objp = index_to_obj(cachep, page, i);

		अगर (cachep->flags & SLAB_POISON) अणु
			check_poison_obj(cachep, objp);
			slab_kernel_map(cachep, objp, 1);
		पूर्ण
		अगर (cachep->flags & SLAB_RED_ZONE) अणु
			अगर (*dbg_redzone1(cachep, objp) != RED_INACTIVE)
				slab_error(cachep, "start of a freed object was overwritten");
			अगर (*dbg_redzone2(cachep, objp) != RED_INACTIVE)
				slab_error(cachep, "end of a freed object was overwritten");
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम slab_destroy_debugcheck(काष्ठा kmem_cache *cachep,
						काष्ठा page *page)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * slab_destroy - destroy and release all objects in a slab
 * @cachep: cache poपूर्णांकer being destroyed
 * @page: page poपूर्णांकer being destroyed
 *
 * Destroy all the objs in a slab page, and release the mem back to the प्रणाली.
 * Beक्रमe calling the slab page must have been unlinked from the cache. The
 * kmem_cache_node ->list_lock is not held/needed.
 */
अटल व्योम slab_destroy(काष्ठा kmem_cache *cachep, काष्ठा page *page)
अणु
	व्योम *मुक्तlist;

	मुक्तlist = page->मुक्तlist;
	slab_destroy_debugcheck(cachep, page);
	अगर (unlikely(cachep->flags & SLAB_TYPESAFE_BY_RCU))
		call_rcu(&page->rcu_head, kmem_rcu_मुक्त);
	अन्यथा
		kmem_मुक्तpages(cachep, page);

	/*
	 * From now on, we करोn't use मुक्तlist
	 * although actual page can be मुक्तd in rcu context
	 */
	अगर (OFF_SLAB(cachep))
		kmem_cache_मुक्त(cachep->मुक्तlist_cache, मुक्तlist);
पूर्ण

/*
 * Update the size of the caches beक्रमe calling sद_असल_destroy as it may
 * recursively call kमुक्त.
 */
अटल व्योम sद_असल_destroy(काष्ठा kmem_cache *cachep, काष्ठा list_head *list)
अणु
	काष्ठा page *page, *n;

	list_क्रम_each_entry_safe(page, n, list, slab_list) अणु
		list_del(&page->slab_list);
		slab_destroy(cachep, page);
	पूर्ण
पूर्ण

/**
 * calculate_slab_order - calculate size (page order) of sद_असल
 * @cachep: poपूर्णांकer to the cache that is being created
 * @size: size of objects to be created in this cache.
 * @flags: slab allocation flags
 *
 * Also calculates the number of objects per slab.
 *
 * This could be made much more पूर्णांकelligent.  For now, try to aव्योम using
 * high order pages क्रम sद_असल.  When the gfp() functions are more मित्रly
 * towards high-order requests, this should be changed.
 *
 * Return: number of left-over bytes in a slab
 */
अटल माप_प्रकार calculate_slab_order(काष्ठा kmem_cache *cachep,
				माप_प्रकार size, slab_flags_t flags)
अणु
	माप_प्रकार left_over = 0;
	पूर्णांक gfporder;

	क्रम (gfporder = 0; gfporder <= KMALLOC_MAX_ORDER; gfporder++) अणु
		अचिन्हित पूर्णांक num;
		माप_प्रकार reमुख्यder;

		num = cache_estimate(gfporder, size, flags, &reमुख्यder);
		अगर (!num)
			जारी;

		/* Can't handle number of objects more than SLAB_OBJ_MAX_NUM */
		अगर (num > SLAB_OBJ_MAX_NUM)
			अवरोध;

		अगर (flags & CFLGS_OFF_SLAB) अणु
			काष्ठा kmem_cache *मुक्तlist_cache;
			माप_प्रकार मुक्तlist_size;

			मुक्तlist_size = num * माप(मुक्तlist_idx_t);
			मुक्तlist_cache = kदो_स्मृति_slab(मुक्तlist_size, 0u);
			अगर (!मुक्तlist_cache)
				जारी;

			/*
			 * Needed to aव्योम possible looping condition
			 * in cache_grow_begin()
			 */
			अगर (OFF_SLAB(मुक्तlist_cache))
				जारी;

			/* check अगर off slab has enough benefit */
			अगर (मुक्तlist_cache->size > cachep->size / 2)
				जारी;
		पूर्ण

		/* Found something acceptable - save it away */
		cachep->num = num;
		cachep->gfporder = gfporder;
		left_over = reमुख्यder;

		/*
		 * A VFS-reclaimable slab tends to have most allocations
		 * as GFP_NOFS and we really करोn't want to have to be allocating
		 * higher-order pages when we are unable to shrink dcache.
		 */
		अगर (flags & SLAB_RECLAIM_ACCOUNT)
			अवरोध;

		/*
		 * Large number of objects is good, but very large sद_असल are
		 * currently bad क्रम the gfp()s.
		 */
		अगर (gfporder >= slab_max_order)
			अवरोध;

		/*
		 * Acceptable पूर्णांकernal fragmentation?
		 */
		अगर (left_over * 8 <= (PAGE_SIZE << gfporder))
			अवरोध;
	पूर्ण
	वापस left_over;
पूर्ण

अटल काष्ठा array_cache __percpu *alloc_kmem_cache_cpus(
		काष्ठा kmem_cache *cachep, पूर्णांक entries, पूर्णांक batchcount)
अणु
	पूर्णांक cpu;
	माप_प्रकार size;
	काष्ठा array_cache __percpu *cpu_cache;

	size = माप(व्योम *) * entries + माप(काष्ठा array_cache);
	cpu_cache = __alloc_percpu(size, माप(व्योम *));

	अगर (!cpu_cache)
		वापस शून्य;

	क्रम_each_possible_cpu(cpu) अणु
		init_arraycache(per_cpu_ptr(cpu_cache, cpu),
				entries, batchcount);
	पूर्ण

	वापस cpu_cache;
पूर्ण

अटल पूर्णांक __ref setup_cpu_cache(काष्ठा kmem_cache *cachep, gfp_t gfp)
अणु
	अगर (slab_state >= FULL)
		वापस enable_cpucache(cachep, gfp);

	cachep->cpu_cache = alloc_kmem_cache_cpus(cachep, 1, 1);
	अगर (!cachep->cpu_cache)
		वापस 1;

	अगर (slab_state == DOWN) अणु
		/* Creation of first cache (kmem_cache). */
		set_up_node(kmem_cache, CACHE_CACHE);
	पूर्ण अन्यथा अगर (slab_state == PARTIAL) अणु
		/* For kmem_cache_node */
		set_up_node(cachep, SIZE_NODE);
	पूर्ण अन्यथा अणु
		पूर्णांक node;

		क्रम_each_online_node(node) अणु
			cachep->node[node] = kदो_स्मृति_node(
				माप(काष्ठा kmem_cache_node), gfp, node);
			BUG_ON(!cachep->node[node]);
			kmem_cache_node_init(cachep->node[node]);
		पूर्ण
	पूर्ण

	cachep->node[numa_mem_id()]->next_reap =
			jअगरfies + REAPTIMEOUT_NODE +
			((अचिन्हित दीर्घ)cachep) % REAPTIMEOUT_NODE;

	cpu_cache_get(cachep)->avail = 0;
	cpu_cache_get(cachep)->limit = BOOT_CPUCACHE_ENTRIES;
	cpu_cache_get(cachep)->batchcount = 1;
	cpu_cache_get(cachep)->touched = 0;
	cachep->batchcount = 1;
	cachep->limit = BOOT_CPUCACHE_ENTRIES;
	वापस 0;
पूर्ण

slab_flags_t kmem_cache_flags(अचिन्हित पूर्णांक object_size,
	slab_flags_t flags, स्थिर अक्षर *name)
अणु
	वापस flags;
पूर्ण

काष्ठा kmem_cache *
__kmem_cache_alias(स्थिर अक्षर *name, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक align,
		   slab_flags_t flags, व्योम (*ctor)(व्योम *))
अणु
	काष्ठा kmem_cache *cachep;

	cachep = find_mergeable(size, align, flags, name, ctor);
	अगर (cachep) अणु
		cachep->refcount++;

		/*
		 * Adjust the object sizes so that we clear
		 * the complete object on kzalloc.
		 */
		cachep->object_size = max_t(पूर्णांक, cachep->object_size, size);
	पूर्ण
	वापस cachep;
पूर्ण

अटल bool set_objमुक्तlist_slab_cache(काष्ठा kmem_cache *cachep,
			माप_प्रकार size, slab_flags_t flags)
अणु
	माप_प्रकार left;

	cachep->num = 0;

	/*
	 * If slab स्वतः-initialization on मुक्त is enabled, store the मुक्तlist
	 * off-slab, so that its contents करोn't end up in one of the allocated
	 * objects.
	 */
	अगर (unlikely(slab_want_init_on_मुक्त(cachep)))
		वापस false;

	अगर (cachep->ctor || flags & SLAB_TYPESAFE_BY_RCU)
		वापस false;

	left = calculate_slab_order(cachep, size,
			flags | CFLGS_OBJFREELIST_SLAB);
	अगर (!cachep->num)
		वापस false;

	अगर (cachep->num * माप(मुक्तlist_idx_t) > cachep->object_size)
		वापस false;

	cachep->colour = left / cachep->colour_off;

	वापस true;
पूर्ण

अटल bool set_off_slab_cache(काष्ठा kmem_cache *cachep,
			माप_प्रकार size, slab_flags_t flags)
अणु
	माप_प्रकार left;

	cachep->num = 0;

	/*
	 * Always use on-slab management when SLAB_NOLEAKTRACE
	 * to aव्योम recursive calls पूर्णांकo kmemleak.
	 */
	अगर (flags & SLAB_NOLEAKTRACE)
		वापस false;

	/*
	 * Size is large, assume best to place the slab management obj
	 * off-slab (should allow better packing of objs).
	 */
	left = calculate_slab_order(cachep, size, flags | CFLGS_OFF_SLAB);
	अगर (!cachep->num)
		वापस false;

	/*
	 * If the slab has been placed off-slab, and we have enough space then
	 * move it on-slab. This is at the expense of any extra colouring.
	 */
	अगर (left >= cachep->num * माप(मुक्तlist_idx_t))
		वापस false;

	cachep->colour = left / cachep->colour_off;

	वापस true;
पूर्ण

अटल bool set_on_slab_cache(काष्ठा kmem_cache *cachep,
			माप_प्रकार size, slab_flags_t flags)
अणु
	माप_प्रकार left;

	cachep->num = 0;

	left = calculate_slab_order(cachep, size, flags);
	अगर (!cachep->num)
		वापस false;

	cachep->colour = left / cachep->colour_off;

	वापस true;
पूर्ण

/**
 * __kmem_cache_create - Create a cache.
 * @cachep: cache management descriptor
 * @flags: SLAB flags
 *
 * Returns a ptr to the cache on success, शून्य on failure.
 * Cannot be called within a पूर्णांक, but can be पूर्णांकerrupted.
 * The @ctor is run when new pages are allocated by the cache.
 *
 * The flags are
 *
 * %SLAB_POISON - Poison the slab with a known test pattern (a5a5a5a5)
 * to catch references to uninitialised memory.
 *
 * %SLAB_RED_ZONE - Insert `Red' zones around the allocated memory to check
 * क्रम buffer overruns.
 *
 * %SLAB_HWCACHE_ALIGN - Align the objects in this cache to a hardware
 * cacheline.  This can be beneficial अगर you're counting cycles as बंदly
 * as davem.
 *
 * Return: a poपूर्णांकer to the created cache or %शून्य in हाल of error
 */
पूर्णांक __kmem_cache_create(काष्ठा kmem_cache *cachep, slab_flags_t flags)
अणु
	माप_प्रकार ralign = BYTES_PER_WORD;
	gfp_t gfp;
	पूर्णांक err;
	अचिन्हित पूर्णांक size = cachep->size;

#अगर DEBUG
#अगर FORCED_DEBUG
	/*
	 * Enable redzoning and last user accounting, except क्रम caches with
	 * large objects, अगर the increased size would increase the object size
	 * above the next घातer of two: caches with object sizes just above a
	 * घातer of two have a signअगरicant amount of पूर्णांकernal fragmentation.
	 */
	अगर (size < 4096 || fls(size - 1) == fls(size-1 + REDZONE_ALIGN +
						2 * माप(अचिन्हित दीर्घ दीर्घ)))
		flags |= SLAB_RED_ZONE | SLAB_STORE_USER;
	अगर (!(flags & SLAB_TYPESAFE_BY_RCU))
		flags |= SLAB_POISON;
#पूर्ण_अगर
#पूर्ण_अगर

	/*
	 * Check that size is in terms of words.  This is needed to aव्योम
	 * unaligned accesses क्रम some archs when redzoning is used, and makes
	 * sure any on-slab bufctl's are also correctly aligned.
	 */
	size = ALIGN(size, BYTES_PER_WORD);

	अगर (flags & SLAB_RED_ZONE) अणु
		ralign = REDZONE_ALIGN;
		/* If redzoning, ensure that the second redzone is suitably
		 * aligned, by adjusting the object size accordingly. */
		size = ALIGN(size, REDZONE_ALIGN);
	पूर्ण

	/* 3) caller mandated alignment */
	अगर (ralign < cachep->align) अणु
		ralign = cachep->align;
	पूर्ण
	/* disable debug अगर necessary */
	अगर (ralign > __alignof__(अचिन्हित दीर्घ दीर्घ))
		flags &= ~(SLAB_RED_ZONE | SLAB_STORE_USER);
	/*
	 * 4) Store it.
	 */
	cachep->align = ralign;
	cachep->colour_off = cache_line_size();
	/* Offset must be a multiple of the alignment. */
	अगर (cachep->colour_off < cachep->align)
		cachep->colour_off = cachep->align;

	अगर (slab_is_available())
		gfp = GFP_KERNEL;
	अन्यथा
		gfp = GFP_NOWAIT;

#अगर DEBUG

	/*
	 * Both debugging options require word-alignment which is calculated
	 * पूर्णांकo align above.
	 */
	अगर (flags & SLAB_RED_ZONE) अणु
		/* add space क्रम red zone words */
		cachep->obj_offset += माप(अचिन्हित दीर्घ दीर्घ);
		size += 2 * माप(अचिन्हित दीर्घ दीर्घ);
	पूर्ण
	अगर (flags & SLAB_STORE_USER) अणु
		/* user store requires one word storage behind the end of
		 * the real object. But अगर the second red zone needs to be
		 * aligned to 64 bits, we must allow that much space.
		 */
		अगर (flags & SLAB_RED_ZONE)
			size += REDZONE_ALIGN;
		अन्यथा
			size += BYTES_PER_WORD;
	पूर्ण
#पूर्ण_अगर

	kasan_cache_create(cachep, &size, &flags);

	size = ALIGN(size, cachep->align);
	/*
	 * We should restrict the number of objects in a slab to implement
	 * byte sized index. Refer comment on SLAB_OBJ_MIN_SIZE definition.
	 */
	अगर (FREELIST_BYTE_INDEX && size < SLAB_OBJ_MIN_SIZE)
		size = ALIGN(SLAB_OBJ_MIN_SIZE, cachep->align);

#अगर DEBUG
	/*
	 * To activate debug pagealloc, off-slab management is necessary
	 * requirement. In early phase of initialization, small sized slab
	 * करोesn't get initialized so it would not be possible. So, we need
	 * to check size >= 256. It guarantees that all necessary small
	 * sized slab is initialized in current slab initialization sequence.
	 */
	अगर (debug_pagealloc_enabled_अटल() && (flags & SLAB_POISON) &&
		size >= 256 && cachep->object_size > cache_line_size()) अणु
		अगर (size < PAGE_SIZE || size % PAGE_SIZE == 0) अणु
			माप_प्रकार पंचांगp_size = ALIGN(size, PAGE_SIZE);

			अगर (set_off_slab_cache(cachep, पंचांगp_size, flags)) अणु
				flags |= CFLGS_OFF_SLAB;
				cachep->obj_offset += पंचांगp_size - size;
				size = पंचांगp_size;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (set_objमुक्तlist_slab_cache(cachep, size, flags)) अणु
		flags |= CFLGS_OBJFREELIST_SLAB;
		जाओ करोne;
	पूर्ण

	अगर (set_off_slab_cache(cachep, size, flags)) अणु
		flags |= CFLGS_OFF_SLAB;
		जाओ करोne;
	पूर्ण

	अगर (set_on_slab_cache(cachep, size, flags))
		जाओ करोne;

	वापस -E2BIG;

करोne:
	cachep->मुक्तlist_size = cachep->num * माप(मुक्तlist_idx_t);
	cachep->flags = flags;
	cachep->allocflags = __GFP_COMP;
	अगर (flags & SLAB_CACHE_DMA)
		cachep->allocflags |= GFP_DMA;
	अगर (flags & SLAB_CACHE_DMA32)
		cachep->allocflags |= GFP_DMA32;
	अगर (flags & SLAB_RECLAIM_ACCOUNT)
		cachep->allocflags |= __GFP_RECLAIMABLE;
	cachep->size = size;
	cachep->reciprocal_buffer_size = reciprocal_value(size);

#अगर DEBUG
	/*
	 * If we're going to use the generic kernel_map_pages()
	 * poisoning, then it's going to smash the contents of
	 * the redzone and userword anyhow, so चयन them off.
	 */
	अगर (IS_ENABLED(CONFIG_PAGE_POISONING) &&
		(cachep->flags & SLAB_POISON) &&
		is_debug_pagealloc_cache(cachep))
		cachep->flags &= ~(SLAB_RED_ZONE | SLAB_STORE_USER);
#पूर्ण_अगर

	अगर (OFF_SLAB(cachep)) अणु
		cachep->मुक्तlist_cache =
			kदो_स्मृति_slab(cachep->मुक्तlist_size, 0u);
	पूर्ण

	err = setup_cpu_cache(cachep, gfp);
	अगर (err) अणु
		__kmem_cache_release(cachep);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#अगर DEBUG
अटल व्योम check_irq_off(व्योम)
अणु
	BUG_ON(!irqs_disabled());
पूर्ण

अटल व्योम check_irq_on(व्योम)
अणु
	BUG_ON(irqs_disabled());
पूर्ण

अटल व्योम check_mutex_acquired(व्योम)
अणु
	BUG_ON(!mutex_is_locked(&slab_mutex));
पूर्ण

अटल व्योम check_spinlock_acquired(काष्ठा kmem_cache *cachep)
अणु
#अगर_घोषित CONFIG_SMP
	check_irq_off();
	निश्चित_spin_locked(&get_node(cachep, numa_mem_id())->list_lock);
#पूर्ण_अगर
पूर्ण

अटल व्योम check_spinlock_acquired_node(काष्ठा kmem_cache *cachep, पूर्णांक node)
अणु
#अगर_घोषित CONFIG_SMP
	check_irq_off();
	निश्चित_spin_locked(&get_node(cachep, node)->list_lock);
#पूर्ण_अगर
पूर्ण

#अन्यथा
#घोषणा check_irq_off()	करो अणु पूर्ण जबतक(0)
#घोषणा check_irq_on()	करो अणु पूर्ण जबतक(0)
#घोषणा check_mutex_acquired()	करो अणु पूर्ण जबतक(0)
#घोषणा check_spinlock_acquired(x) करो अणु पूर्ण जबतक(0)
#घोषणा check_spinlock_acquired_node(x, y) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल व्योम drain_array_locked(काष्ठा kmem_cache *cachep, काष्ठा array_cache *ac,
				पूर्णांक node, bool मुक्त_all, काष्ठा list_head *list)
अणु
	पूर्णांक toमुक्त;

	अगर (!ac || !ac->avail)
		वापस;

	toमुक्त = मुक्त_all ? ac->avail : (ac->limit + 4) / 5;
	अगर (toमुक्त > ac->avail)
		toमुक्त = (ac->avail + 1) / 2;

	मुक्त_block(cachep, ac->entry, toमुक्त, node, list);
	ac->avail -= toमुक्त;
	स_हटाओ(ac->entry, &(ac->entry[toमुक्त]), माप(व्योम *) * ac->avail);
पूर्ण

अटल व्योम करो_drain(व्योम *arg)
अणु
	काष्ठा kmem_cache *cachep = arg;
	काष्ठा array_cache *ac;
	पूर्णांक node = numa_mem_id();
	काष्ठा kmem_cache_node *n;
	LIST_HEAD(list);

	check_irq_off();
	ac = cpu_cache_get(cachep);
	n = get_node(cachep, node);
	spin_lock(&n->list_lock);
	मुक्त_block(cachep, ac->entry, ac->avail, node, &list);
	spin_unlock(&n->list_lock);
	ac->avail = 0;
	sद_असल_destroy(cachep, &list);
पूर्ण

अटल व्योम drain_cpu_caches(काष्ठा kmem_cache *cachep)
अणु
	काष्ठा kmem_cache_node *n;
	पूर्णांक node;
	LIST_HEAD(list);

	on_each_cpu(करो_drain, cachep, 1);
	check_irq_on();
	क्रम_each_kmem_cache_node(cachep, node, n)
		अगर (n->alien)
			drain_alien_cache(cachep, n->alien);

	क्रम_each_kmem_cache_node(cachep, node, n) अणु
		spin_lock_irq(&n->list_lock);
		drain_array_locked(cachep, n->shared, node, true, &list);
		spin_unlock_irq(&n->list_lock);

		sद_असल_destroy(cachep, &list);
	पूर्ण
पूर्ण

/*
 * Remove sद_असल from the list of मुक्त sद_असल.
 * Specअगरy the number of sद_असल to drain in toमुक्त.
 *
 * Returns the actual number of sद_असल released.
 */
अटल पूर्णांक drain_मुक्तlist(काष्ठा kmem_cache *cache,
			काष्ठा kmem_cache_node *n, पूर्णांक toमुक्त)
अणु
	काष्ठा list_head *p;
	पूर्णांक nr_मुक्तd;
	काष्ठा page *page;

	nr_मुक्तd = 0;
	जबतक (nr_मुक्तd < toमुक्त && !list_empty(&n->sद_असल_मुक्त)) अणु

		spin_lock_irq(&n->list_lock);
		p = n->sद_असल_मुक्त.prev;
		अगर (p == &n->sद_असल_मुक्त) अणु
			spin_unlock_irq(&n->list_lock);
			जाओ out;
		पूर्ण

		page = list_entry(p, काष्ठा page, slab_list);
		list_del(&page->slab_list);
		n->मुक्त_sद_असल--;
		n->total_sद_असल--;
		/*
		 * Safe to drop the lock. The slab is no दीर्घer linked
		 * to the cache.
		 */
		n->मुक्त_objects -= cache->num;
		spin_unlock_irq(&n->list_lock);
		slab_destroy(cache, page);
		nr_मुक्तd++;
	पूर्ण
out:
	वापस nr_मुक्तd;
पूर्ण

bool __kmem_cache_empty(काष्ठा kmem_cache *s)
अणु
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	क्रम_each_kmem_cache_node(s, node, n)
		अगर (!list_empty(&n->sद_असल_full) ||
		    !list_empty(&n->sद_असल_partial))
			वापस false;
	वापस true;
पूर्ण

पूर्णांक __kmem_cache_shrink(काष्ठा kmem_cache *cachep)
अणु
	पूर्णांक ret = 0;
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	drain_cpu_caches(cachep);

	check_irq_on();
	क्रम_each_kmem_cache_node(cachep, node, n) अणु
		drain_मुक्तlist(cachep, n, पूर्णांक_उच्च);

		ret += !list_empty(&n->sद_असल_full) ||
			!list_empty(&n->sद_असल_partial);
	पूर्ण
	वापस (ret ? 1 : 0);
पूर्ण

पूर्णांक __kmem_cache_shutकरोwn(काष्ठा kmem_cache *cachep)
अणु
	वापस __kmem_cache_shrink(cachep);
पूर्ण

व्योम __kmem_cache_release(काष्ठा kmem_cache *cachep)
अणु
	पूर्णांक i;
	काष्ठा kmem_cache_node *n;

	cache_अक्रमom_seq_destroy(cachep);

	मुक्त_percpu(cachep->cpu_cache);

	/* NUMA: मुक्त the node काष्ठाures */
	क्रम_each_kmem_cache_node(cachep, i, n) अणु
		kमुक्त(n->shared);
		मुक्त_alien_cache(n->alien);
		kमुक्त(n);
		cachep->node[i] = शून्य;
	पूर्ण
पूर्ण

/*
 * Get the memory क्रम a slab management obj.
 *
 * For a slab cache when the slab descriptor is off-slab, the
 * slab descriptor can't come from the same cache which is being created,
 * Because अगर it is the हाल, that means we defer the creation of
 * the kदो_स्मृति_अणुdma,पूर्ण_cache of size माप(slab descriptor) to this poपूर्णांक.
 * And we eventually call करोwn to __kmem_cache_create(), which
 * in turn looks up in the kदो_स्मृति_अणुdma,पूर्ण_caches क्रम the desired-size one.
 * This is a "chicken-and-egg" problem.
 *
 * So the off-slab slab descriptor shall come from the kदो_स्मृति_अणुdma,पूर्ण_caches,
 * which are all initialized during kmem_cache_init().
 */
अटल व्योम *alloc_slabmgmt(काष्ठा kmem_cache *cachep,
				   काष्ठा page *page, पूर्णांक colour_off,
				   gfp_t local_flags, पूर्णांक nodeid)
अणु
	व्योम *मुक्तlist;
	व्योम *addr = page_address(page);

	page->s_mem = addr + colour_off;
	page->active = 0;

	अगर (OBJFREELIST_SLAB(cachep))
		मुक्तlist = शून्य;
	अन्यथा अगर (OFF_SLAB(cachep)) अणु
		/* Slab management obj is off-slab. */
		मुक्तlist = kmem_cache_alloc_node(cachep->मुक्तlist_cache,
					      local_flags, nodeid);
	पूर्ण अन्यथा अणु
		/* We will use last bytes at the slab क्रम मुक्तlist */
		मुक्तlist = addr + (PAGE_SIZE << cachep->gfporder) -
				cachep->मुक्तlist_size;
	पूर्ण

	वापस मुक्तlist;
पूर्ण

अटल अंतरभूत मुक्तlist_idx_t get_मुक्त_obj(काष्ठा page *page, अचिन्हित पूर्णांक idx)
अणु
	वापस ((मुक्तlist_idx_t *)page->मुक्तlist)[idx];
पूर्ण

अटल अंतरभूत व्योम set_मुक्त_obj(काष्ठा page *page,
					अचिन्हित पूर्णांक idx, मुक्तlist_idx_t val)
अणु
	((मुक्तlist_idx_t *)(page->मुक्तlist))[idx] = val;
पूर्ण

अटल व्योम cache_init_objs_debug(काष्ठा kmem_cache *cachep, काष्ठा page *page)
अणु
#अगर DEBUG
	पूर्णांक i;

	क्रम (i = 0; i < cachep->num; i++) अणु
		व्योम *objp = index_to_obj(cachep, page, i);

		अगर (cachep->flags & SLAB_STORE_USER)
			*dbg_userword(cachep, objp) = शून्य;

		अगर (cachep->flags & SLAB_RED_ZONE) अणु
			*dbg_redzone1(cachep, objp) = RED_INACTIVE;
			*dbg_redzone2(cachep, objp) = RED_INACTIVE;
		पूर्ण
		/*
		 * Conकाष्ठाors are not allowed to allocate memory from the same
		 * cache which they are a स्थिरructor क्रम.  Otherwise, deadlock.
		 * They must also be thपढ़ोed.
		 */
		अगर (cachep->ctor && !(cachep->flags & SLAB_POISON)) अणु
			kasan_unpoison_object_data(cachep,
						   objp + obj_offset(cachep));
			cachep->ctor(objp + obj_offset(cachep));
			kasan_poison_object_data(
				cachep, objp + obj_offset(cachep));
		पूर्ण

		अगर (cachep->flags & SLAB_RED_ZONE) अणु
			अगर (*dbg_redzone2(cachep, objp) != RED_INACTIVE)
				slab_error(cachep, "constructor overwrote the end of an object");
			अगर (*dbg_redzone1(cachep, objp) != RED_INACTIVE)
				slab_error(cachep, "constructor overwrote the start of an object");
		पूर्ण
		/* need to poison the objs? */
		अगर (cachep->flags & SLAB_POISON) अणु
			poison_obj(cachep, objp, POISON_FREE);
			slab_kernel_map(cachep, objp, 0);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SLAB_FREELIST_RANDOM
/* Hold inक्रमmation during a मुक्तlist initialization */
जोड़ मुक्तlist_init_state अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक pos;
		अचिन्हित पूर्णांक *list;
		अचिन्हित पूर्णांक count;
	पूर्ण;
	काष्ठा rnd_state rnd_state;
पूर्ण;

/*
 * Initialize the state based on the अक्रमomization method available.
 * वापस true अगर the pre-computed list is available, false otherwise.
 */
अटल bool मुक्तlist_state_initialize(जोड़ मुक्तlist_init_state *state,
				काष्ठा kmem_cache *cachep,
				अचिन्हित पूर्णांक count)
अणु
	bool ret;
	अचिन्हित पूर्णांक अक्रम;

	/* Use best entropy available to define a अक्रमom shअगरt */
	अक्रम = get_अक्रमom_पूर्णांक();

	/* Use a अक्रमom state अगर the pre-computed list is not available */
	अगर (!cachep->अक्रमom_seq) अणु
		pअक्रमom_seed_state(&state->rnd_state, अक्रम);
		ret = false;
	पूर्ण अन्यथा अणु
		state->list = cachep->अक्रमom_seq;
		state->count = count;
		state->pos = अक्रम % count;
		ret = true;
	पूर्ण
	वापस ret;
पूर्ण

/* Get the next entry on the list and अक्रमomize it using a अक्रमom shअगरt */
अटल मुक्तlist_idx_t next_अक्रमom_slot(जोड़ मुक्तlist_init_state *state)
अणु
	अगर (state->pos >= state->count)
		state->pos = 0;
	वापस state->list[state->pos++];
पूर्ण

/* Swap two मुक्तlist entries */
अटल व्योम swap_मुक्त_obj(काष्ठा page *page, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	swap(((मुक्तlist_idx_t *)page->मुक्तlist)[a],
		((मुक्तlist_idx_t *)page->मुक्तlist)[b]);
पूर्ण

/*
 * Shuffle the मुक्तlist initialization state based on pre-computed lists.
 * वापस true अगर the list was successfully shuffled, false otherwise.
 */
अटल bool shuffle_मुक्तlist(काष्ठा kmem_cache *cachep, काष्ठा page *page)
अणु
	अचिन्हित पूर्णांक objमुक्तlist = 0, i, अक्रम, count = cachep->num;
	जोड़ मुक्तlist_init_state state;
	bool precomputed;

	अगर (count < 2)
		वापस false;

	precomputed = मुक्तlist_state_initialize(&state, cachep, count);

	/* Take a अक्रमom entry as the objमुक्तlist */
	अगर (OBJFREELIST_SLAB(cachep)) अणु
		अगर (!precomputed)
			objमुक्तlist = count - 1;
		अन्यथा
			objमुक्तlist = next_अक्रमom_slot(&state);
		page->मुक्तlist = index_to_obj(cachep, page, objमुक्तlist) +
						obj_offset(cachep);
		count--;
	पूर्ण

	/*
	 * On early boot, generate the list dynamically.
	 * Later use a pre-computed list क्रम speed.
	 */
	अगर (!precomputed) अणु
		क्रम (i = 0; i < count; i++)
			set_मुक्त_obj(page, i, i);

		/* Fisher-Yates shuffle */
		क्रम (i = count - 1; i > 0; i--) अणु
			अक्रम = pअक्रमom_u32_state(&state.rnd_state);
			अक्रम %= (i + 1);
			swap_मुक्त_obj(page, i, अक्रम);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < count; i++)
			set_मुक्त_obj(page, i, next_अक्रमom_slot(&state));
	पूर्ण

	अगर (OBJFREELIST_SLAB(cachep))
		set_मुक्त_obj(page, cachep->num - 1, objमुक्तlist);

	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool shuffle_मुक्तlist(काष्ठा kmem_cache *cachep,
				काष्ठा page *page)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_SLAB_FREELIST_RANDOM */

अटल व्योम cache_init_objs(काष्ठा kmem_cache *cachep,
			    काष्ठा page *page)
अणु
	पूर्णांक i;
	व्योम *objp;
	bool shuffled;

	cache_init_objs_debug(cachep, page);

	/* Try to अक्रमomize the मुक्तlist अगर enabled */
	shuffled = shuffle_मुक्तlist(cachep, page);

	अगर (!shuffled && OBJFREELIST_SLAB(cachep)) अणु
		page->मुक्तlist = index_to_obj(cachep, page, cachep->num - 1) +
						obj_offset(cachep);
	पूर्ण

	क्रम (i = 0; i < cachep->num; i++) अणु
		objp = index_to_obj(cachep, page, i);
		objp = kasan_init_slab_obj(cachep, objp);

		/* स्थिरructor could अवरोध poison info */
		अगर (DEBUG == 0 && cachep->ctor) अणु
			kasan_unpoison_object_data(cachep, objp);
			cachep->ctor(objp);
			kasan_poison_object_data(cachep, objp);
		पूर्ण

		अगर (!shuffled)
			set_मुक्त_obj(page, i, i);
	पूर्ण
पूर्ण

अटल व्योम *slab_get_obj(काष्ठा kmem_cache *cachep, काष्ठा page *page)
अणु
	व्योम *objp;

	objp = index_to_obj(cachep, page, get_मुक्त_obj(page, page->active));
	page->active++;

	वापस objp;
पूर्ण

अटल व्योम slab_put_obj(काष्ठा kmem_cache *cachep,
			काष्ठा page *page, व्योम *objp)
अणु
	अचिन्हित पूर्णांक objnr = obj_to_index(cachep, page, objp);
#अगर DEBUG
	अचिन्हित पूर्णांक i;

	/* Verअगरy द्विगुन मुक्त bug */
	क्रम (i = page->active; i < cachep->num; i++) अणु
		अगर (get_मुक्त_obj(page, i) == objnr) अणु
			pr_err("slab: double free detected in cache '%s', objp %px\n",
			       cachep->name, objp);
			BUG();
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	page->active--;
	अगर (!page->मुक्तlist)
		page->मुक्तlist = objp + obj_offset(cachep);

	set_मुक्त_obj(page, page->active, objnr);
पूर्ण

/*
 * Map pages beginning at addr to the given cache and slab. This is required
 * क्रम the slab allocator to be able to lookup the cache and slab of a
 * भव address क्रम kमुक्त, ksize, and slab debugging.
 */
अटल व्योम slab_map_pages(काष्ठा kmem_cache *cache, काष्ठा page *page,
			   व्योम *मुक्तlist)
अणु
	page->slab_cache = cache;
	page->मुक्तlist = मुक्तlist;
पूर्ण

/*
 * Grow (by 1) the number of sद_असल within a cache.  This is called by
 * kmem_cache_alloc() when there are no active objs left in a cache.
 */
अटल काष्ठा page *cache_grow_begin(काष्ठा kmem_cache *cachep,
				gfp_t flags, पूर्णांक nodeid)
अणु
	व्योम *मुक्तlist;
	माप_प्रकार offset;
	gfp_t local_flags;
	पूर्णांक page_node;
	काष्ठा kmem_cache_node *n;
	काष्ठा page *page;

	/*
	 * Be lazy and only check क्रम valid flags here,  keeping it out of the
	 * critical path in kmem_cache_alloc().
	 */
	अगर (unlikely(flags & GFP_SLAB_BUG_MASK))
		flags = kदो_स्मृति_fix_flags(flags);

	WARN_ON_ONCE(cachep->ctor && (flags & __GFP_ZERO));
	local_flags = flags & (GFP_CONSTRAINT_MASK|GFP_RECLAIM_MASK);

	check_irq_off();
	अगर (gfpflags_allow_blocking(local_flags))
		local_irq_enable();

	/*
	 * Get mem क्रम the objs.  Attempt to allocate a physical page from
	 * 'nodeid'.
	 */
	page = kmem_getpages(cachep, local_flags, nodeid);
	अगर (!page)
		जाओ failed;

	page_node = page_to_nid(page);
	n = get_node(cachep, page_node);

	/* Get colour क्रम the slab, and cal the next value. */
	n->colour_next++;
	अगर (n->colour_next >= cachep->colour)
		n->colour_next = 0;

	offset = n->colour_next;
	अगर (offset >= cachep->colour)
		offset = 0;

	offset *= cachep->colour_off;

	/*
	 * Call kasan_poison_slab() beक्रमe calling alloc_slabmgmt(), so
	 * page_address() in the latter वापसs a non-tagged poपूर्णांकer,
	 * as it should be क्रम slab pages.
	 */
	kasan_poison_slab(page);

	/* Get slab management. */
	मुक्तlist = alloc_slabmgmt(cachep, page, offset,
			local_flags & ~GFP_CONSTRAINT_MASK, page_node);
	अगर (OFF_SLAB(cachep) && !मुक्तlist)
		जाओ opps1;

	slab_map_pages(cachep, page, मुक्तlist);

	cache_init_objs(cachep, page);

	अगर (gfpflags_allow_blocking(local_flags))
		local_irq_disable();

	वापस page;

opps1:
	kmem_मुक्तpages(cachep, page);
failed:
	अगर (gfpflags_allow_blocking(local_flags))
		local_irq_disable();
	वापस शून्य;
पूर्ण

अटल व्योम cache_grow_end(काष्ठा kmem_cache *cachep, काष्ठा page *page)
अणु
	काष्ठा kmem_cache_node *n;
	व्योम *list = शून्य;

	check_irq_off();

	अगर (!page)
		वापस;

	INIT_LIST_HEAD(&page->slab_list);
	n = get_node(cachep, page_to_nid(page));

	spin_lock(&n->list_lock);
	n->total_sद_असल++;
	अगर (!page->active) अणु
		list_add_tail(&page->slab_list, &n->sद_असल_मुक्त);
		n->मुक्त_sद_असल++;
	पूर्ण अन्यथा
		fixup_slab_list(cachep, n, page, &list);

	STATS_INC_GROWN(cachep);
	n->मुक्त_objects += cachep->num - page->active;
	spin_unlock(&n->list_lock);

	fixup_objमुक्तlist_debug(cachep, &list);
पूर्ण

#अगर DEBUG

/*
 * Perक्रमm extra मुक्तing checks:
 * - detect bad poपूर्णांकers.
 * - POISON/RED_ZONE checking
 */
अटल व्योम kमुक्त_debugcheck(स्थिर व्योम *objp)
अणु
	अगर (!virt_addr_valid(objp)) अणु
		pr_err("kfree_debugcheck: out of range ptr %lxh\n",
		       (अचिन्हित दीर्घ)objp);
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम verअगरy_redzone_मुक्त(काष्ठा kmem_cache *cache, व्योम *obj)
अणु
	अचिन्हित दीर्घ दीर्घ redzone1, redzone2;

	redzone1 = *dbg_redzone1(cache, obj);
	redzone2 = *dbg_redzone2(cache, obj);

	/*
	 * Redzone is ok.
	 */
	अगर (redzone1 == RED_ACTIVE && redzone2 == RED_ACTIVE)
		वापस;

	अगर (redzone1 == RED_INACTIVE && redzone2 == RED_INACTIVE)
		slab_error(cache, "double free detected");
	अन्यथा
		slab_error(cache, "memory outside object was overwritten");

	pr_err("%px: redzone 1:0x%llx, redzone 2:0x%llx\n",
	       obj, redzone1, redzone2);
पूर्ण

अटल व्योम *cache_मुक्त_debugcheck(काष्ठा kmem_cache *cachep, व्योम *objp,
				   अचिन्हित दीर्घ caller)
अणु
	अचिन्हित पूर्णांक objnr;
	काष्ठा page *page;

	BUG_ON(virt_to_cache(objp) != cachep);

	objp -= obj_offset(cachep);
	kमुक्त_debugcheck(objp);
	page = virt_to_head_page(objp);

	अगर (cachep->flags & SLAB_RED_ZONE) अणु
		verअगरy_redzone_मुक्त(cachep, objp);
		*dbg_redzone1(cachep, objp) = RED_INACTIVE;
		*dbg_redzone2(cachep, objp) = RED_INACTIVE;
	पूर्ण
	अगर (cachep->flags & SLAB_STORE_USER)
		*dbg_userword(cachep, objp) = (व्योम *)caller;

	objnr = obj_to_index(cachep, page, objp);

	BUG_ON(objnr >= cachep->num);
	BUG_ON(objp != index_to_obj(cachep, page, objnr));

	अगर (cachep->flags & SLAB_POISON) अणु
		poison_obj(cachep, objp, POISON_FREE);
		slab_kernel_map(cachep, objp, 0);
	पूर्ण
	वापस objp;
पूर्ण

#अन्यथा
#घोषणा kमुक्त_debugcheck(x) करो अणु पूर्ण जबतक(0)
#घोषणा cache_मुक्त_debugcheck(x, objp, z) (objp)
#पूर्ण_अगर

अटल अंतरभूत व्योम fixup_objमुक्तlist_debug(काष्ठा kmem_cache *cachep,
						व्योम **list)
अणु
#अगर DEBUG
	व्योम *next = *list;
	व्योम *objp;

	जबतक (next) अणु
		objp = next - obj_offset(cachep);
		next = *(व्योम **)next;
		poison_obj(cachep, objp, POISON_FREE);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम fixup_slab_list(काष्ठा kmem_cache *cachep,
				काष्ठा kmem_cache_node *n, काष्ठा page *page,
				व्योम **list)
अणु
	/* move slabp to correct slabp list: */
	list_del(&page->slab_list);
	अगर (page->active == cachep->num) अणु
		list_add(&page->slab_list, &n->sद_असल_full);
		अगर (OBJFREELIST_SLAB(cachep)) अणु
#अगर DEBUG
			/* Poisoning will be करोne without holding the lock */
			अगर (cachep->flags & SLAB_POISON) अणु
				व्योम **objp = page->मुक्तlist;

				*objp = *list;
				*list = objp;
			पूर्ण
#पूर्ण_अगर
			page->मुक्तlist = शून्य;
		पूर्ण
	पूर्ण अन्यथा
		list_add(&page->slab_list, &n->sद_असल_partial);
पूर्ण

/* Try to find non-pfmeदो_स्मृति slab अगर needed */
अटल noअंतरभूत काष्ठा page *get_valid_first_slab(काष्ठा kmem_cache_node *n,
					काष्ठा page *page, bool pfmeदो_स्मृति)
अणु
	अगर (!page)
		वापस शून्य;

	अगर (pfmeदो_स्मृति)
		वापस page;

	अगर (!PageSlabPfmeदो_स्मृति(page))
		वापस page;

	/* No need to keep pfmeदो_स्मृति slab अगर we have enough मुक्त objects */
	अगर (n->मुक्त_objects > n->मुक्त_limit) अणु
		ClearPageSlabPfmeदो_स्मृति(page);
		वापस page;
	पूर्ण

	/* Move pfmeदो_स्मृति slab to the end of list to speed up next search */
	list_del(&page->slab_list);
	अगर (!page->active) अणु
		list_add_tail(&page->slab_list, &n->sद_असल_मुक्त);
		n->मुक्त_sद_असल++;
	पूर्ण अन्यथा
		list_add_tail(&page->slab_list, &n->sद_असल_partial);

	list_क्रम_each_entry(page, &n->sद_असल_partial, slab_list) अणु
		अगर (!PageSlabPfmeदो_स्मृति(page))
			वापस page;
	पूर्ण

	n->मुक्त_touched = 1;
	list_क्रम_each_entry(page, &n->sद_असल_मुक्त, slab_list) अणु
		अगर (!PageSlabPfmeदो_स्मृति(page)) अणु
			n->मुक्त_sद_असल--;
			वापस page;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा page *get_first_slab(काष्ठा kmem_cache_node *n, bool pfmeदो_स्मृति)
अणु
	काष्ठा page *page;

	निश्चित_spin_locked(&n->list_lock);
	page = list_first_entry_or_null(&n->sद_असल_partial, काष्ठा page,
					slab_list);
	अगर (!page) अणु
		n->मुक्त_touched = 1;
		page = list_first_entry_or_null(&n->sद_असल_मुक्त, काष्ठा page,
						slab_list);
		अगर (page)
			n->मुक्त_sद_असल--;
	पूर्ण

	अगर (sk_meदो_स्मृति_socks())
		page = get_valid_first_slab(n, page, pfmeदो_स्मृति);

	वापस page;
पूर्ण

अटल noअंतरभूत व्योम *cache_alloc_pfmeदो_स्मृति(काष्ठा kmem_cache *cachep,
				काष्ठा kmem_cache_node *n, gfp_t flags)
अणु
	काष्ठा page *page;
	व्योम *obj;
	व्योम *list = शून्य;

	अगर (!gfp_pfmeदो_स्मृति_allowed(flags))
		वापस शून्य;

	spin_lock(&n->list_lock);
	page = get_first_slab(n, true);
	अगर (!page) अणु
		spin_unlock(&n->list_lock);
		वापस शून्य;
	पूर्ण

	obj = slab_get_obj(cachep, page);
	n->मुक्त_objects--;

	fixup_slab_list(cachep, n, page, &list);

	spin_unlock(&n->list_lock);
	fixup_objमुक्तlist_debug(cachep, &list);

	वापस obj;
पूर्ण

/*
 * Slab list should be fixed up by fixup_slab_list() क्रम existing slab
 * or cache_grow_end() क्रम new slab
 */
अटल __always_अंतरभूत पूर्णांक alloc_block(काष्ठा kmem_cache *cachep,
		काष्ठा array_cache *ac, काष्ठा page *page, पूर्णांक batchcount)
अणु
	/*
	 * There must be at least one object available क्रम
	 * allocation.
	 */
	BUG_ON(page->active >= cachep->num);

	जबतक (page->active < cachep->num && batchcount--) अणु
		STATS_INC_ALLOCED(cachep);
		STATS_INC_ACTIVE(cachep);
		STATS_SET_HIGH(cachep);

		ac->entry[ac->avail++] = slab_get_obj(cachep, page);
	पूर्ण

	वापस batchcount;
पूर्ण

अटल व्योम *cache_alloc_refill(काष्ठा kmem_cache *cachep, gfp_t flags)
अणु
	पूर्णांक batchcount;
	काष्ठा kmem_cache_node *n;
	काष्ठा array_cache *ac, *shared;
	पूर्णांक node;
	व्योम *list = शून्य;
	काष्ठा page *page;

	check_irq_off();
	node = numa_mem_id();

	ac = cpu_cache_get(cachep);
	batchcount = ac->batchcount;
	अगर (!ac->touched && batchcount > BATCHREFILL_LIMIT) अणु
		/*
		 * If there was little recent activity on this cache, then
		 * perक्रमm only a partial refill.  Otherwise we could generate
		 * refill bouncing.
		 */
		batchcount = BATCHREFILL_LIMIT;
	पूर्ण
	n = get_node(cachep, node);

	BUG_ON(ac->avail > 0 || !n);
	shared = READ_ONCE(n->shared);
	अगर (!n->मुक्त_objects && (!shared || !shared->avail))
		जाओ direct_grow;

	spin_lock(&n->list_lock);
	shared = READ_ONCE(n->shared);

	/* See अगर we can refill from the shared array */
	अगर (shared && transfer_objects(ac, shared, batchcount)) अणु
		shared->touched = 1;
		जाओ alloc_करोne;
	पूर्ण

	जबतक (batchcount > 0) अणु
		/* Get slab alloc is to come from. */
		page = get_first_slab(n, false);
		अगर (!page)
			जाओ must_grow;

		check_spinlock_acquired(cachep);

		batchcount = alloc_block(cachep, ac, page, batchcount);
		fixup_slab_list(cachep, n, page, &list);
	पूर्ण

must_grow:
	n->मुक्त_objects -= ac->avail;
alloc_करोne:
	spin_unlock(&n->list_lock);
	fixup_objमुक्तlist_debug(cachep, &list);

direct_grow:
	अगर (unlikely(!ac->avail)) अणु
		/* Check अगर we can use obj in pfmeदो_स्मृति slab */
		अगर (sk_meदो_स्मृति_socks()) अणु
			व्योम *obj = cache_alloc_pfmeदो_स्मृति(cachep, n, flags);

			अगर (obj)
				वापस obj;
		पूर्ण

		page = cache_grow_begin(cachep, gfp_exact_node(flags), node);

		/*
		 * cache_grow_begin() can reenable पूर्णांकerrupts,
		 * then ac could change.
		 */
		ac = cpu_cache_get(cachep);
		अगर (!ac->avail && page)
			alloc_block(cachep, ac, page, batchcount);
		cache_grow_end(cachep, page);

		अगर (!ac->avail)
			वापस शून्य;
	पूर्ण
	ac->touched = 1;

	वापस ac->entry[--ac->avail];
पूर्ण

अटल अंतरभूत व्योम cache_alloc_debugcheck_beक्रमe(काष्ठा kmem_cache *cachep,
						gfp_t flags)
अणु
	might_sleep_अगर(gfpflags_allow_blocking(flags));
पूर्ण

#अगर DEBUG
अटल व्योम *cache_alloc_debugcheck_after(काष्ठा kmem_cache *cachep,
				gfp_t flags, व्योम *objp, अचिन्हित दीर्घ caller)
अणु
	WARN_ON_ONCE(cachep->ctor && (flags & __GFP_ZERO));
	अगर (!objp || is_kfence_address(objp))
		वापस objp;
	अगर (cachep->flags & SLAB_POISON) अणु
		check_poison_obj(cachep, objp);
		slab_kernel_map(cachep, objp, 1);
		poison_obj(cachep, objp, POISON_INUSE);
	पूर्ण
	अगर (cachep->flags & SLAB_STORE_USER)
		*dbg_userword(cachep, objp) = (व्योम *)caller;

	अगर (cachep->flags & SLAB_RED_ZONE) अणु
		अगर (*dbg_redzone1(cachep, objp) != RED_INACTIVE ||
				*dbg_redzone2(cachep, objp) != RED_INACTIVE) अणु
			slab_error(cachep, "double free, or memory outside object was overwritten");
			pr_err("%px: redzone 1:0x%llx, redzone 2:0x%llx\n",
			       objp, *dbg_redzone1(cachep, objp),
			       *dbg_redzone2(cachep, objp));
		पूर्ण
		*dbg_redzone1(cachep, objp) = RED_ACTIVE;
		*dbg_redzone2(cachep, objp) = RED_ACTIVE;
	पूर्ण

	objp += obj_offset(cachep);
	अगर (cachep->ctor && cachep->flags & SLAB_POISON)
		cachep->ctor(objp);
	अगर (ARCH_SLAB_MINALIGN &&
	    ((अचिन्हित दीर्घ)objp & (ARCH_SLAB_MINALIGN-1))) अणु
		pr_err("0x%px: not aligned to ARCH_SLAB_MINALIGN=%d\n",
		       objp, (पूर्णांक)ARCH_SLAB_MINALIGN);
	पूर्ण
	वापस objp;
पूर्ण
#अन्यथा
#घोषणा cache_alloc_debugcheck_after(a, b, objp, d) (objp)
#पूर्ण_अगर

अटल अंतरभूत व्योम *____cache_alloc(काष्ठा kmem_cache *cachep, gfp_t flags)
अणु
	व्योम *objp;
	काष्ठा array_cache *ac;

	check_irq_off();

	ac = cpu_cache_get(cachep);
	अगर (likely(ac->avail)) अणु
		ac->touched = 1;
		objp = ac->entry[--ac->avail];

		STATS_INC_ALLOCHIT(cachep);
		जाओ out;
	पूर्ण

	STATS_INC_ALLOCMISS(cachep);
	objp = cache_alloc_refill(cachep, flags);
	/*
	 * the 'ac' may be updated by cache_alloc_refill(),
	 * and kmemleak_erase() requires its correct value.
	 */
	ac = cpu_cache_get(cachep);

out:
	/*
	 * To aव्योम a false negative, अगर an object that is in one of the
	 * per-CPU caches is leaked, we need to make sure kmemleak करोesn't
	 * treat the array poपूर्णांकers as a reference to the object.
	 */
	अगर (objp)
		kmemleak_erase(&ac->entry[ac->avail]);
	वापस objp;
पूर्ण

#अगर_घोषित CONFIG_NUMA
/*
 * Try allocating on another node अगर PFA_SPREAD_SLAB is a mempolicy is set.
 *
 * If we are in_पूर्णांकerrupt, then process context, including cpusets and
 * mempolicy, may not apply and should not be used क्रम allocation policy.
 */
अटल व्योम *alternate_node_alloc(काष्ठा kmem_cache *cachep, gfp_t flags)
अणु
	पूर्णांक nid_alloc, nid_here;

	अगर (in_पूर्णांकerrupt() || (flags & __GFP_THISNODE))
		वापस शून्य;
	nid_alloc = nid_here = numa_mem_id();
	अगर (cpuset_करो_slab_mem_spपढ़ो() && (cachep->flags & SLAB_MEM_SPREAD))
		nid_alloc = cpuset_slab_spपढ़ो_node();
	अन्यथा अगर (current->mempolicy)
		nid_alloc = mempolicy_slab_node();
	अगर (nid_alloc != nid_here)
		वापस ____cache_alloc_node(cachep, flags, nid_alloc);
	वापस शून्य;
पूर्ण

/*
 * Fallback function अगर there was no memory available and no objects on a
 * certain node and fall back is permitted. First we scan all the
 * available node क्रम available objects. If that fails then we
 * perक्रमm an allocation without specअगरying a node. This allows the page
 * allocator to करो its reclaim / fallback magic. We then insert the
 * slab पूर्णांकo the proper nodelist and then allocate from it.
 */
अटल व्योम *fallback_alloc(काष्ठा kmem_cache *cache, gfp_t flags)
अणु
	काष्ठा zonelist *zonelist;
	काष्ठा zoneref *z;
	काष्ठा zone *zone;
	क्रमागत zone_type highest_zoneidx = gfp_zone(flags);
	व्योम *obj = शून्य;
	काष्ठा page *page;
	पूर्णांक nid;
	अचिन्हित पूर्णांक cpuset_mems_cookie;

	अगर (flags & __GFP_THISNODE)
		वापस शून्य;

retry_cpuset:
	cpuset_mems_cookie = पढ़ो_mems_allowed_begin();
	zonelist = node_zonelist(mempolicy_slab_node(), flags);

retry:
	/*
	 * Look through allowed nodes क्रम objects available
	 * from existing per node queues.
	 */
	क्रम_each_zone_zonelist(zone, z, zonelist, highest_zoneidx) अणु
		nid = zone_to_nid(zone);

		अगर (cpuset_zone_allowed(zone, flags) &&
			get_node(cache, nid) &&
			get_node(cache, nid)->मुक्त_objects) अणु
				obj = ____cache_alloc_node(cache,
					gfp_exact_node(flags), nid);
				अगर (obj)
					अवरोध;
		पूर्ण
	पूर्ण

	अगर (!obj) अणु
		/*
		 * This allocation will be perक्रमmed within the स्थिरraपूर्णांकs
		 * of the current cpuset / memory policy requirements.
		 * We may trigger various क्रमms of reclaim on the allowed
		 * set and go पूर्णांकo memory reserves अगर necessary.
		 */
		page = cache_grow_begin(cache, flags, numa_mem_id());
		cache_grow_end(cache, page);
		अगर (page) अणु
			nid = page_to_nid(page);
			obj = ____cache_alloc_node(cache,
				gfp_exact_node(flags), nid);

			/*
			 * Another processor may allocate the objects in
			 * the slab since we are not holding any locks.
			 */
			अगर (!obj)
				जाओ retry;
		पूर्ण
	पूर्ण

	अगर (unlikely(!obj && पढ़ो_mems_allowed_retry(cpuset_mems_cookie)))
		जाओ retry_cpuset;
	वापस obj;
पूर्ण

/*
 * A पूर्णांकerface to enable slab creation on nodeid
 */
अटल व्योम *____cache_alloc_node(काष्ठा kmem_cache *cachep, gfp_t flags,
				पूर्णांक nodeid)
अणु
	काष्ठा page *page;
	काष्ठा kmem_cache_node *n;
	व्योम *obj = शून्य;
	व्योम *list = शून्य;

	VM_BUG_ON(nodeid < 0 || nodeid >= MAX_NUMNODES);
	n = get_node(cachep, nodeid);
	BUG_ON(!n);

	check_irq_off();
	spin_lock(&n->list_lock);
	page = get_first_slab(n, false);
	अगर (!page)
		जाओ must_grow;

	check_spinlock_acquired_node(cachep, nodeid);

	STATS_INC_NODEALLOCS(cachep);
	STATS_INC_ACTIVE(cachep);
	STATS_SET_HIGH(cachep);

	BUG_ON(page->active == cachep->num);

	obj = slab_get_obj(cachep, page);
	n->मुक्त_objects--;

	fixup_slab_list(cachep, n, page, &list);

	spin_unlock(&n->list_lock);
	fixup_objमुक्तlist_debug(cachep, &list);
	वापस obj;

must_grow:
	spin_unlock(&n->list_lock);
	page = cache_grow_begin(cachep, gfp_exact_node(flags), nodeid);
	अगर (page) अणु
		/* This slab isn't counted yet so don't update मुक्त_objects */
		obj = slab_get_obj(cachep, page);
	पूर्ण
	cache_grow_end(cachep, page);

	वापस obj ? obj : fallback_alloc(cachep, flags);
पूर्ण

अटल __always_अंतरभूत व्योम *
slab_alloc_node(काष्ठा kmem_cache *cachep, gfp_t flags, पूर्णांक nodeid, माप_प्रकार orig_size,
		   अचिन्हित दीर्घ caller)
अणु
	अचिन्हित दीर्घ save_flags;
	व्योम *ptr;
	पूर्णांक slab_node = numa_mem_id();
	काष्ठा obj_cgroup *objcg = शून्य;
	bool init = false;

	flags &= gfp_allowed_mask;
	cachep = slab_pre_alloc_hook(cachep, &objcg, 1, flags);
	अगर (unlikely(!cachep))
		वापस शून्य;

	ptr = kfence_alloc(cachep, orig_size, flags);
	अगर (unlikely(ptr))
		जाओ out_hooks;

	cache_alloc_debugcheck_beक्रमe(cachep, flags);
	local_irq_save(save_flags);

	अगर (nodeid == NUMA_NO_NODE)
		nodeid = slab_node;

	अगर (unlikely(!get_node(cachep, nodeid))) अणु
		/* Node not bootstrapped yet */
		ptr = fallback_alloc(cachep, flags);
		जाओ out;
	पूर्ण

	अगर (nodeid == slab_node) अणु
		/*
		 * Use the locally cached objects अगर possible.
		 * However ____cache_alloc करोes not allow fallback
		 * to other nodes. It may fail जबतक we still have
		 * objects on other nodes available.
		 */
		ptr = ____cache_alloc(cachep, flags);
		अगर (ptr)
			जाओ out;
	पूर्ण
	/* ___cache_alloc_node can fall back to other nodes */
	ptr = ____cache_alloc_node(cachep, flags, nodeid);
  out:
	local_irq_restore(save_flags);
	ptr = cache_alloc_debugcheck_after(cachep, flags, ptr, caller);
	init = slab_want_init_on_alloc(flags, cachep);

out_hooks:
	slab_post_alloc_hook(cachep, objcg, flags, 1, &ptr, init);
	वापस ptr;
पूर्ण

अटल __always_अंतरभूत व्योम *
__करो_cache_alloc(काष्ठा kmem_cache *cache, gfp_t flags)
अणु
	व्योम *objp;

	अगर (current->mempolicy || cpuset_करो_slab_mem_spपढ़ो()) अणु
		objp = alternate_node_alloc(cache, flags);
		अगर (objp)
			जाओ out;
	पूर्ण
	objp = ____cache_alloc(cache, flags);

	/*
	 * We may just have run out of memory on the local node.
	 * ____cache_alloc_node() knows how to locate memory on other nodes
	 */
	अगर (!objp)
		objp = ____cache_alloc_node(cache, flags, numa_mem_id());

  out:
	वापस objp;
पूर्ण
#अन्यथा

अटल __always_अंतरभूत व्योम *
__करो_cache_alloc(काष्ठा kmem_cache *cachep, gfp_t flags)
अणु
	वापस ____cache_alloc(cachep, flags);
पूर्ण

#पूर्ण_अगर /* CONFIG_NUMA */

अटल __always_अंतरभूत व्योम *
slab_alloc(काष्ठा kmem_cache *cachep, gfp_t flags, माप_प्रकार orig_size, अचिन्हित दीर्घ caller)
अणु
	अचिन्हित दीर्घ save_flags;
	व्योम *objp;
	काष्ठा obj_cgroup *objcg = शून्य;
	bool init = false;

	flags &= gfp_allowed_mask;
	cachep = slab_pre_alloc_hook(cachep, &objcg, 1, flags);
	अगर (unlikely(!cachep))
		वापस शून्य;

	objp = kfence_alloc(cachep, orig_size, flags);
	अगर (unlikely(objp))
		जाओ out;

	cache_alloc_debugcheck_beक्रमe(cachep, flags);
	local_irq_save(save_flags);
	objp = __करो_cache_alloc(cachep, flags);
	local_irq_restore(save_flags);
	objp = cache_alloc_debugcheck_after(cachep, flags, objp, caller);
	prefetchw(objp);
	init = slab_want_init_on_alloc(flags, cachep);

out:
	slab_post_alloc_hook(cachep, objcg, flags, 1, &objp, init);
	वापस objp;
पूर्ण

/*
 * Caller needs to acquire correct kmem_cache_node's list_lock
 * @list: List of detached मुक्त sद_असल should be मुक्तd by caller
 */
अटल व्योम मुक्त_block(काष्ठा kmem_cache *cachep, व्योम **objpp,
			पूर्णांक nr_objects, पूर्णांक node, काष्ठा list_head *list)
अणु
	पूर्णांक i;
	काष्ठा kmem_cache_node *n = get_node(cachep, node);
	काष्ठा page *page;

	n->मुक्त_objects += nr_objects;

	क्रम (i = 0; i < nr_objects; i++) अणु
		व्योम *objp;
		काष्ठा page *page;

		objp = objpp[i];

		page = virt_to_head_page(objp);
		list_del(&page->slab_list);
		check_spinlock_acquired_node(cachep, node);
		slab_put_obj(cachep, page, objp);
		STATS_DEC_ACTIVE(cachep);

		/* fixup slab chains */
		अगर (page->active == 0) अणु
			list_add(&page->slab_list, &n->sद_असल_मुक्त);
			n->मुक्त_sद_असल++;
		पूर्ण अन्यथा अणु
			/* Unconditionally move a slab to the end of the
			 * partial list on मुक्त - maximum समय क्रम the
			 * other objects to be मुक्तd, too.
			 */
			list_add_tail(&page->slab_list, &n->sद_असल_partial);
		पूर्ण
	पूर्ण

	जबतक (n->मुक्त_objects > n->मुक्त_limit && !list_empty(&n->sद_असल_मुक्त)) अणु
		n->मुक्त_objects -= cachep->num;

		page = list_last_entry(&n->sद_असल_मुक्त, काष्ठा page, slab_list);
		list_move(&page->slab_list, list);
		n->मुक्त_sद_असल--;
		n->total_sद_असल--;
	पूर्ण
पूर्ण

अटल व्योम cache_flusharray(काष्ठा kmem_cache *cachep, काष्ठा array_cache *ac)
अणु
	पूर्णांक batchcount;
	काष्ठा kmem_cache_node *n;
	पूर्णांक node = numa_mem_id();
	LIST_HEAD(list);

	batchcount = ac->batchcount;

	check_irq_off();
	n = get_node(cachep, node);
	spin_lock(&n->list_lock);
	अगर (n->shared) अणु
		काष्ठा array_cache *shared_array = n->shared;
		पूर्णांक max = shared_array->limit - shared_array->avail;
		अगर (max) अणु
			अगर (batchcount > max)
				batchcount = max;
			स_नकल(&(shared_array->entry[shared_array->avail]),
			       ac->entry, माप(व्योम *) * batchcount);
			shared_array->avail += batchcount;
			जाओ मुक्त_करोne;
		पूर्ण
	पूर्ण

	मुक्त_block(cachep, ac->entry, batchcount, node, &list);
मुक्त_करोne:
#अगर STATS
	अणु
		पूर्णांक i = 0;
		काष्ठा page *page;

		list_क्रम_each_entry(page, &n->sद_असल_मुक्त, slab_list) अणु
			BUG_ON(page->active);

			i++;
		पूर्ण
		STATS_SET_FREEABLE(cachep, i);
	पूर्ण
#पूर्ण_अगर
	spin_unlock(&n->list_lock);
	ac->avail -= batchcount;
	स_हटाओ(ac->entry, &(ac->entry[batchcount]), माप(व्योम *)*ac->avail);
	sद_असल_destroy(cachep, &list);
पूर्ण

/*
 * Release an obj back to its cache. If the obj has a स्थिरructed state, it must
 * be in this state _beक्रमe_ it is released.  Called with disabled पूर्णांकs.
 */
अटल __always_अंतरभूत व्योम __cache_मुक्त(काष्ठा kmem_cache *cachep, व्योम *objp,
					 अचिन्हित दीर्घ caller)
अणु
	bool init;

	अगर (is_kfence_address(objp)) अणु
		kmemleak_मुक्त_recursive(objp, cachep->flags);
		__kfence_मुक्त(objp);
		वापस;
	पूर्ण

	/*
	 * As memory initialization might be पूर्णांकegrated पूर्णांकo KASAN,
	 * kasan_slab_मुक्त and initialization स_रखो must be
	 * kept together to aव्योम discrepancies in behavior.
	 */
	init = slab_want_init_on_मुक्त(cachep);
	अगर (init && !kasan_has_पूर्णांकegrated_init())
		स_रखो(objp, 0, cachep->object_size);
	/* KASAN might put objp पूर्णांकo memory quarantine, delaying its reuse. */
	अगर (kasan_slab_मुक्त(cachep, objp, init))
		वापस;

	/* Use KCSAN to help debug racy use-after-मुक्त. */
	अगर (!(cachep->flags & SLAB_TYPESAFE_BY_RCU))
		__kcsan_check_access(objp, cachep->object_size,
				     KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ASSERT);

	___cache_मुक्त(cachep, objp, caller);
पूर्ण

व्योम ___cache_मुक्त(काष्ठा kmem_cache *cachep, व्योम *objp,
		अचिन्हित दीर्घ caller)
अणु
	काष्ठा array_cache *ac = cpu_cache_get(cachep);

	check_irq_off();
	kmemleak_मुक्त_recursive(objp, cachep->flags);
	objp = cache_मुक्त_debugcheck(cachep, objp, caller);
	memcg_slab_मुक्त_hook(cachep, &objp, 1);

	/*
	 * Skip calling cache_मुक्त_alien() when the platक्रमm is not numa.
	 * This will aव्योम cache misses that happen जबतक accessing slabp (which
	 * is per page memory  reference) to get nodeid. Instead use a global
	 * variable to skip the call, which is mostly likely to be present in
	 * the cache.
	 */
	अगर (nr_online_nodes > 1 && cache_मुक्त_alien(cachep, objp))
		वापस;

	अगर (ac->avail < ac->limit) अणु
		STATS_INC_FREEHIT(cachep);
	पूर्ण अन्यथा अणु
		STATS_INC_FREEMISS(cachep);
		cache_flusharray(cachep, ac);
	पूर्ण

	अगर (sk_meदो_स्मृति_socks()) अणु
		काष्ठा page *page = virt_to_head_page(objp);

		अगर (unlikely(PageSlabPfmeदो_स्मृति(page))) अणु
			cache_मुक्त_pfmeदो_स्मृति(cachep, page, objp);
			वापस;
		पूर्ण
	पूर्ण

	__मुक्त_one(ac, objp);
पूर्ण

/**
 * kmem_cache_alloc - Allocate an object
 * @cachep: The cache to allocate from.
 * @flags: See kदो_स्मृति().
 *
 * Allocate an object from this cache.  The flags are only relevant
 * अगर the cache has no available objects.
 *
 * Return: poपूर्णांकer to the new object or %शून्य in हाल of error
 */
व्योम *kmem_cache_alloc(काष्ठा kmem_cache *cachep, gfp_t flags)
अणु
	व्योम *ret = slab_alloc(cachep, flags, cachep->object_size, _RET_IP_);

	trace_kmem_cache_alloc(_RET_IP_, ret,
			       cachep->object_size, cachep->size, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc);

अटल __always_अंतरभूत व्योम
cache_alloc_debugcheck_after_bulk(काष्ठा kmem_cache *s, gfp_t flags,
				  माप_प्रकार size, व्योम **p, अचिन्हित दीर्घ caller)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < size; i++)
		p[i] = cache_alloc_debugcheck_after(s, flags, p[i], caller);
पूर्ण

पूर्णांक kmem_cache_alloc_bulk(काष्ठा kmem_cache *s, gfp_t flags, माप_प्रकार size,
			  व्योम **p)
अणु
	माप_प्रकार i;
	काष्ठा obj_cgroup *objcg = शून्य;

	s = slab_pre_alloc_hook(s, &objcg, size, flags);
	अगर (!s)
		वापस 0;

	cache_alloc_debugcheck_beक्रमe(s, flags);

	local_irq_disable();
	क्रम (i = 0; i < size; i++) अणु
		व्योम *objp = kfence_alloc(s, s->object_size, flags) ?: __करो_cache_alloc(s, flags);

		अगर (unlikely(!objp))
			जाओ error;
		p[i] = objp;
	पूर्ण
	local_irq_enable();

	cache_alloc_debugcheck_after_bulk(s, flags, size, p, _RET_IP_);

	/*
	 * memcg and kmem_cache debug support and memory initialization.
	 * Done outside of the IRQ disabled section.
	 */
	slab_post_alloc_hook(s, objcg, flags, size, p,
				slab_want_init_on_alloc(flags, s));
	/* FIXME: Trace call missing. Christoph would like a bulk variant */
	वापस size;
error:
	local_irq_enable();
	cache_alloc_debugcheck_after_bulk(s, flags, i, p, _RET_IP_);
	slab_post_alloc_hook(s, objcg, flags, i, p, false);
	__kmem_cache_मुक्त_bulk(s, i, p);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_bulk);

#अगर_घोषित CONFIG_TRACING
व्योम *
kmem_cache_alloc_trace(काष्ठा kmem_cache *cachep, gfp_t flags, माप_प्रकार size)
अणु
	व्योम *ret;

	ret = slab_alloc(cachep, flags, size, _RET_IP_);

	ret = kasan_kदो_स्मृति(cachep, ret, size, flags);
	trace_kदो_स्मृति(_RET_IP_, ret,
		      size, cachep->size, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_trace);
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA
/**
 * kmem_cache_alloc_node - Allocate an object on the specअगरied node
 * @cachep: The cache to allocate from.
 * @flags: See kदो_स्मृति().
 * @nodeid: node number of the target node.
 *
 * Identical to kmem_cache_alloc but it will allocate memory on the given
 * node, which can improve the perक्रमmance क्रम cpu bound काष्ठाures.
 *
 * Fallback to other node is possible अगर __GFP_THISNODE is not set.
 *
 * Return: poपूर्णांकer to the new object or %शून्य in हाल of error
 */
व्योम *kmem_cache_alloc_node(काष्ठा kmem_cache *cachep, gfp_t flags, पूर्णांक nodeid)
अणु
	व्योम *ret = slab_alloc_node(cachep, flags, nodeid, cachep->object_size, _RET_IP_);

	trace_kmem_cache_alloc_node(_RET_IP_, ret,
				    cachep->object_size, cachep->size,
				    flags, nodeid);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_node);

#अगर_घोषित CONFIG_TRACING
व्योम *kmem_cache_alloc_node_trace(काष्ठा kmem_cache *cachep,
				  gfp_t flags,
				  पूर्णांक nodeid,
				  माप_प्रकार size)
अणु
	व्योम *ret;

	ret = slab_alloc_node(cachep, flags, nodeid, size, _RET_IP_);

	ret = kasan_kदो_स्मृति(cachep, ret, size, flags);
	trace_kदो_स्मृति_node(_RET_IP_, ret,
			   size, cachep->size,
			   flags, nodeid);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(kmem_cache_alloc_node_trace);
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम *
__करो_kदो_स्मृति_node(माप_प्रकार size, gfp_t flags, पूर्णांक node, अचिन्हित दीर्घ caller)
अणु
	काष्ठा kmem_cache *cachep;
	व्योम *ret;

	अगर (unlikely(size > KMALLOC_MAX_CACHE_SIZE))
		वापस शून्य;
	cachep = kदो_स्मृति_slab(size, flags);
	अगर (unlikely(ZERO_OR_शून्य_PTR(cachep)))
		वापस cachep;
	ret = kmem_cache_alloc_node_trace(cachep, flags, node, size);
	ret = kasan_kदो_स्मृति(cachep, ret, size, flags);

	वापस ret;
पूर्ण

व्योम *__kदो_स्मृति_node(माप_प्रकार size, gfp_t flags, पूर्णांक node)
अणु
	वापस __करो_kदो_स्मृति_node(size, flags, node, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति_node);

व्योम *__kदो_स्मृति_node_track_caller(माप_प्रकार size, gfp_t flags,
		पूर्णांक node, अचिन्हित दीर्घ caller)
अणु
	वापस __करो_kदो_स्मृति_node(size, flags, node, caller);
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति_node_track_caller);
#पूर्ण_अगर /* CONFIG_NUMA */

#अगर_घोषित CONFIG_PRINTK
व्योम kmem_obj_info(काष्ठा kmem_obj_info *kpp, व्योम *object, काष्ठा page *page)
अणु
	काष्ठा kmem_cache *cachep;
	अचिन्हित पूर्णांक objnr;
	व्योम *objp;

	kpp->kp_ptr = object;
	kpp->kp_page = page;
	cachep = page->slab_cache;
	kpp->kp_slab_cache = cachep;
	objp = object - obj_offset(cachep);
	kpp->kp_data_offset = obj_offset(cachep);
	page = virt_to_head_page(objp);
	objnr = obj_to_index(cachep, page, objp);
	objp = index_to_obj(cachep, page, objnr);
	kpp->kp_objp = objp;
	अगर (DEBUG && cachep->flags & SLAB_STORE_USER)
		kpp->kp_ret = *dbg_userword(cachep, objp);
पूर्ण
#पूर्ण_अगर

/**
 * __करो_kदो_स्मृति - allocate memory
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate (see kदो_स्मृति).
 * @caller: function caller क्रम debug tracking of the caller
 *
 * Return: poपूर्णांकer to the allocated memory or %शून्य in हाल of error
 */
अटल __always_अंतरभूत व्योम *__करो_kदो_स्मृति(माप_प्रकार size, gfp_t flags,
					  अचिन्हित दीर्घ caller)
अणु
	काष्ठा kmem_cache *cachep;
	व्योम *ret;

	अगर (unlikely(size > KMALLOC_MAX_CACHE_SIZE))
		वापस शून्य;
	cachep = kदो_स्मृति_slab(size, flags);
	अगर (unlikely(ZERO_OR_शून्य_PTR(cachep)))
		वापस cachep;
	ret = slab_alloc(cachep, flags, size, caller);

	ret = kasan_kदो_स्मृति(cachep, ret, size, flags);
	trace_kदो_स्मृति(caller, ret,
		      size, cachep->size, flags);

	वापस ret;
पूर्ण

व्योम *__kदो_स्मृति(माप_प्रकार size, gfp_t flags)
अणु
	वापस __करो_kदो_स्मृति(size, flags, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति);

व्योम *__kदो_स्मृति_track_caller(माप_प्रकार size, gfp_t flags, अचिन्हित दीर्घ caller)
अणु
	वापस __करो_kदो_स्मृति(size, flags, caller);
पूर्ण
EXPORT_SYMBOL(__kदो_स्मृति_track_caller);

/**
 * kmem_cache_मुक्त - Deallocate an object
 * @cachep: The cache the allocation was from.
 * @objp: The previously allocated object.
 *
 * Free an object which was previously allocated from this
 * cache.
 */
व्योम kmem_cache_मुक्त(काष्ठा kmem_cache *cachep, व्योम *objp)
अणु
	अचिन्हित दीर्घ flags;
	cachep = cache_from_obj(cachep, objp);
	अगर (!cachep)
		वापस;

	local_irq_save(flags);
	debug_check_no_locks_मुक्तd(objp, cachep->object_size);
	अगर (!(cachep->flags & SLAB_DEBUG_OBJECTS))
		debug_check_no_obj_मुक्तd(objp, cachep->object_size);
	__cache_मुक्त(cachep, objp, _RET_IP_);
	local_irq_restore(flags);

	trace_kmem_cache_मुक्त(_RET_IP_, objp, cachep->name);
पूर्ण
EXPORT_SYMBOL(kmem_cache_मुक्त);

व्योम kmem_cache_मुक्त_bulk(काष्ठा kmem_cache *orig_s, माप_प्रकार size, व्योम **p)
अणु
	काष्ठा kmem_cache *s;
	माप_प्रकार i;

	local_irq_disable();
	क्रम (i = 0; i < size; i++) अणु
		व्योम *objp = p[i];

		अगर (!orig_s) /* called via kमुक्त_bulk */
			s = virt_to_cache(objp);
		अन्यथा
			s = cache_from_obj(orig_s, objp);
		अगर (!s)
			जारी;

		debug_check_no_locks_मुक्तd(objp, s->object_size);
		अगर (!(s->flags & SLAB_DEBUG_OBJECTS))
			debug_check_no_obj_मुक्तd(objp, s->object_size);

		__cache_मुक्त(s, objp, _RET_IP_);
	पूर्ण
	local_irq_enable();

	/* FIXME: add tracing */
पूर्ण
EXPORT_SYMBOL(kmem_cache_मुक्त_bulk);

/**
 * kमुक्त - मुक्त previously allocated memory
 * @objp: poपूर्णांकer वापसed by kदो_स्मृति.
 *
 * If @objp is शून्य, no operation is perक्रमmed.
 *
 * Don't मुक्त memory not originally allocated by kदो_स्मृति()
 * or you will run पूर्णांकo trouble.
 */
व्योम kमुक्त(स्थिर व्योम *objp)
अणु
	काष्ठा kmem_cache *c;
	अचिन्हित दीर्घ flags;

	trace_kमुक्त(_RET_IP_, objp);

	अगर (unlikely(ZERO_OR_शून्य_PTR(objp)))
		वापस;
	local_irq_save(flags);
	kमुक्त_debugcheck(objp);
	c = virt_to_cache(objp);
	अगर (!c) अणु
		local_irq_restore(flags);
		वापस;
	पूर्ण
	debug_check_no_locks_मुक्तd(objp, c->object_size);

	debug_check_no_obj_मुक्तd(objp, c->object_size);
	__cache_मुक्त(c, (व्योम *)objp, _RET_IP_);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(kमुक्त);

/*
 * This initializes kmem_cache_node or resizes various caches क्रम all nodes.
 */
अटल पूर्णांक setup_kmem_cache_nodes(काष्ठा kmem_cache *cachep, gfp_t gfp)
अणु
	पूर्णांक ret;
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	क्रम_each_online_node(node) अणु
		ret = setup_kmem_cache_node(cachep, node, gfp, true);
		अगर (ret)
			जाओ fail;

	पूर्ण

	वापस 0;

fail:
	अगर (!cachep->list.next) अणु
		/* Cache is not active yet. Roll back what we did */
		node--;
		जबतक (node >= 0) अणु
			n = get_node(cachep, node);
			अगर (n) अणु
				kमुक्त(n->shared);
				मुक्त_alien_cache(n->alien);
				kमुक्त(n);
				cachep->node[node] = शून्य;
			पूर्ण
			node--;
		पूर्ण
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/* Always called with the slab_mutex held */
अटल पूर्णांक करो_tune_cpucache(काष्ठा kmem_cache *cachep, पूर्णांक limit,
			    पूर्णांक batchcount, पूर्णांक shared, gfp_t gfp)
अणु
	काष्ठा array_cache __percpu *cpu_cache, *prev;
	पूर्णांक cpu;

	cpu_cache = alloc_kmem_cache_cpus(cachep, limit, batchcount);
	अगर (!cpu_cache)
		वापस -ENOMEM;

	prev = cachep->cpu_cache;
	cachep->cpu_cache = cpu_cache;
	/*
	 * Without a previous cpu_cache there's no need to synchronize remote
	 * cpus, so skip the IPIs.
	 */
	अगर (prev)
		kick_all_cpus_sync();

	check_irq_on();
	cachep->batchcount = batchcount;
	cachep->limit = limit;
	cachep->shared = shared;

	अगर (!prev)
		जाओ setup_node;

	क्रम_each_online_cpu(cpu) अणु
		LIST_HEAD(list);
		पूर्णांक node;
		काष्ठा kmem_cache_node *n;
		काष्ठा array_cache *ac = per_cpu_ptr(prev, cpu);

		node = cpu_to_mem(cpu);
		n = get_node(cachep, node);
		spin_lock_irq(&n->list_lock);
		मुक्त_block(cachep, ac->entry, ac->avail, node, &list);
		spin_unlock_irq(&n->list_lock);
		sद_असल_destroy(cachep, &list);
	पूर्ण
	मुक्त_percpu(prev);

setup_node:
	वापस setup_kmem_cache_nodes(cachep, gfp);
पूर्ण

/* Called with slab_mutex held always */
अटल पूर्णांक enable_cpucache(काष्ठा kmem_cache *cachep, gfp_t gfp)
अणु
	पूर्णांक err;
	पूर्णांक limit = 0;
	पूर्णांक shared = 0;
	पूर्णांक batchcount = 0;

	err = cache_अक्रमom_seq_create(cachep, cachep->num, gfp);
	अगर (err)
		जाओ end;

	अगर (limit && shared && batchcount)
		जाओ skip_setup;
	/*
	 * The head array serves three purposes:
	 * - create a LIFO ordering, i.e. वापस objects that are cache-warm
	 * - reduce the number of spinlock operations.
	 * - reduce the number of linked list operations on the slab and
	 *   bufctl chains: array operations are cheaper.
	 * The numbers are guessed, we should स्वतः-tune as described by
	 * Bonwick.
	 */
	अगर (cachep->size > 131072)
		limit = 1;
	अन्यथा अगर (cachep->size > PAGE_SIZE)
		limit = 8;
	अन्यथा अगर (cachep->size > 1024)
		limit = 24;
	अन्यथा अगर (cachep->size > 256)
		limit = 54;
	अन्यथा
		limit = 120;

	/*
	 * CPU bound tasks (e.g. network routing) can exhibit cpu bound
	 * allocation behaviour: Most allocs on one cpu, most मुक्त operations
	 * on another cpu. For these हालs, an efficient object passing between
	 * cpus is necessary. This is provided by a shared array. The array
	 * replaces Bonwick's magazine layer.
	 * On uniprocessor, it's functionally equivalent (but less efficient)
	 * to a larger limit. Thus disabled by शेष.
	 */
	shared = 0;
	अगर (cachep->size <= PAGE_SIZE && num_possible_cpus() > 1)
		shared = 8;

#अगर DEBUG
	/*
	 * With debugging enabled, large batchcount lead to excessively दीर्घ
	 * periods with disabled local पूर्णांकerrupts. Limit the batchcount
	 */
	अगर (limit > 32)
		limit = 32;
#पूर्ण_अगर
	batchcount = (limit + 1) / 2;
skip_setup:
	err = करो_tune_cpucache(cachep, limit, batchcount, shared, gfp);
end:
	अगर (err)
		pr_err("enable_cpucache failed for %s, error %d\n",
		       cachep->name, -err);
	वापस err;
पूर्ण

/*
 * Drain an array अगर it contains any elements taking the node lock only अगर
 * necessary. Note that the node listlock also protects the array_cache
 * अगर drain_array() is used on the shared array.
 */
अटल व्योम drain_array(काष्ठा kmem_cache *cachep, काष्ठा kmem_cache_node *n,
			 काष्ठा array_cache *ac, पूर्णांक node)
अणु
	LIST_HEAD(list);

	/* ac from n->shared can be मुक्तd अगर we करोn't hold the slab_mutex. */
	check_mutex_acquired();

	अगर (!ac || !ac->avail)
		वापस;

	अगर (ac->touched) अणु
		ac->touched = 0;
		वापस;
	पूर्ण

	spin_lock_irq(&n->list_lock);
	drain_array_locked(cachep, ac, node, false, &list);
	spin_unlock_irq(&n->list_lock);

	sद_असल_destroy(cachep, &list);
पूर्ण

/**
 * cache_reap - Reclaim memory from caches.
 * @w: work descriptor
 *
 * Called from workqueue/eventd every few seconds.
 * Purpose:
 * - clear the per-cpu caches क्रम this CPU.
 * - वापस मुक्तable pages to the मुख्य मुक्त memory pool.
 *
 * If we cannot acquire the cache chain mutex then just give up - we'll try
 * again on the next iteration.
 */
अटल व्योम cache_reap(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा kmem_cache *searchp;
	काष्ठा kmem_cache_node *n;
	पूर्णांक node = numa_mem_id();
	काष्ठा delayed_work *work = to_delayed_work(w);

	अगर (!mutex_trylock(&slab_mutex))
		/* Give up. Setup the next iteration. */
		जाओ out;

	list_क्रम_each_entry(searchp, &slab_caches, list) अणु
		check_irq_on();

		/*
		 * We only take the node lock अगर असलolutely necessary and we
		 * have established with reasonable certaपूर्णांकy that
		 * we can करो some work अगर the lock was obtained.
		 */
		n = get_node(searchp, node);

		reap_alien(searchp, n);

		drain_array(searchp, n, cpu_cache_get(searchp), node);

		/*
		 * These are racy checks but it करोes not matter
		 * अगर we skip one check or scan twice.
		 */
		अगर (समय_after(n->next_reap, jअगरfies))
			जाओ next;

		n->next_reap = jअगरfies + REAPTIMEOUT_NODE;

		drain_array(searchp, n, n->shared, node);

		अगर (n->मुक्त_touched)
			n->मुक्त_touched = 0;
		अन्यथा अणु
			पूर्णांक मुक्तd;

			मुक्तd = drain_मुक्तlist(searchp, n, (n->मुक्त_limit +
				5 * searchp->num - 1) / (5 * searchp->num));
			STATS_ADD_REAPED(searchp, मुक्तd);
		पूर्ण
next:
		cond_resched();
	पूर्ण
	check_irq_on();
	mutex_unlock(&slab_mutex);
	next_reap_node();
out:
	/* Set up the next iteration */
	schedule_delayed_work_on(smp_processor_id(), work,
				round_jअगरfies_relative(REAPTIMEOUT_AC));
पूर्ण

व्योम get_slabinfo(काष्ठा kmem_cache *cachep, काष्ठा slabinfo *sinfo)
अणु
	अचिन्हित दीर्घ active_objs, num_objs, active_sद_असल;
	अचिन्हित दीर्घ total_sद_असल = 0, मुक्त_objs = 0, shared_avail = 0;
	अचिन्हित दीर्घ मुक्त_sद_असल = 0;
	पूर्णांक node;
	काष्ठा kmem_cache_node *n;

	क्रम_each_kmem_cache_node(cachep, node, n) अणु
		check_irq_on();
		spin_lock_irq(&n->list_lock);

		total_sद_असल += n->total_sद_असल;
		मुक्त_sद_असल += n->मुक्त_sद_असल;
		मुक्त_objs += n->मुक्त_objects;

		अगर (n->shared)
			shared_avail += n->shared->avail;

		spin_unlock_irq(&n->list_lock);
	पूर्ण
	num_objs = total_sद_असल * cachep->num;
	active_sद_असल = total_sद_असल - मुक्त_sद_असल;
	active_objs = num_objs - मुक्त_objs;

	sinfo->active_objs = active_objs;
	sinfo->num_objs = num_objs;
	sinfo->active_sद_असल = active_sद_असल;
	sinfo->num_sद_असल = total_sद_असल;
	sinfo->shared_avail = shared_avail;
	sinfo->limit = cachep->limit;
	sinfo->batchcount = cachep->batchcount;
	sinfo->shared = cachep->shared;
	sinfo->objects_per_slab = cachep->num;
	sinfo->cache_order = cachep->gfporder;
पूर्ण

व्योम slabinfo_show_stats(काष्ठा seq_file *m, काष्ठा kmem_cache *cachep)
अणु
#अगर STATS
	अणु			/* node stats */
		अचिन्हित दीर्घ high = cachep->high_mark;
		अचिन्हित दीर्घ allocs = cachep->num_allocations;
		अचिन्हित दीर्घ grown = cachep->grown;
		अचिन्हित दीर्घ reaped = cachep->reaped;
		अचिन्हित दीर्घ errors = cachep->errors;
		अचिन्हित दीर्घ max_मुक्तable = cachep->max_मुक्तable;
		अचिन्हित दीर्घ node_allocs = cachep->node_allocs;
		अचिन्हित दीर्घ node_मुक्तs = cachep->node_मुक्तs;
		अचिन्हित दीर्घ overflows = cachep->node_overflow;

		seq_म_लिखो(m, " : globalstat %7lu %6lu %5lu %4lu %4lu %4lu %4lu %4lu %4lu",
			   allocs, high, grown,
			   reaped, errors, max_मुक्तable, node_allocs,
			   node_मुक्तs, overflows);
	पूर्ण
	/* cpu stats */
	अणु
		अचिन्हित दीर्घ allochit = atomic_पढ़ो(&cachep->allochit);
		अचिन्हित दीर्घ allocmiss = atomic_पढ़ो(&cachep->allocmiss);
		अचिन्हित दीर्घ मुक्तhit = atomic_पढ़ो(&cachep->मुक्तhit);
		अचिन्हित दीर्घ मुक्तmiss = atomic_पढ़ो(&cachep->मुक्तmiss);

		seq_म_लिखो(m, " : cpustat %6lu %6lu %6lu %6lu",
			   allochit, allocmiss, मुक्तhit, मुक्तmiss);
	पूर्ण
#पूर्ण_अगर
पूर्ण

#घोषणा MAX_SLABINFO_WRITE 128
/**
 * slabinfo_ग_लिखो - Tuning क्रम the slab allocator
 * @file: unused
 * @buffer: user buffer
 * @count: data length
 * @ppos: unused
 *
 * Return: %0 on success, negative error code otherwise.
 */
sमाप_प्रकार slabinfo_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
		       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर kbuf[MAX_SLABINFO_WRITE + 1], *पंचांगp;
	पूर्णांक limit, batchcount, shared, res;
	काष्ठा kmem_cache *cachep;

	अगर (count > MAX_SLABINFO_WRITE)
		वापस -EINVAL;
	अगर (copy_from_user(&kbuf, buffer, count))
		वापस -EFAULT;
	kbuf[MAX_SLABINFO_WRITE] = '\0';

	पंचांगp = म_अक्षर(kbuf, ' ');
	अगर (!पंचांगp)
		वापस -EINVAL;
	*पंचांगp = '\0';
	पंचांगp++;
	अगर (माला_पूछो(पंचांगp, " %d %d %d", &limit, &batchcount, &shared) != 3)
		वापस -EINVAL;

	/* Find the cache in the chain of caches. */
	mutex_lock(&slab_mutex);
	res = -EINVAL;
	list_क्रम_each_entry(cachep, &slab_caches, list) अणु
		अगर (!म_भेद(cachep->name, kbuf)) अणु
			अगर (limit < 1 || batchcount < 1 ||
					batchcount > limit || shared < 0) अणु
				res = 0;
			पूर्ण अन्यथा अणु
				res = करो_tune_cpucache(cachep, limit,
						       batchcount, shared,
						       GFP_KERNEL);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&slab_mutex);
	अगर (res >= 0)
		res = count;
	वापस res;
पूर्ण

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
	काष्ठा kmem_cache *cachep;
	अचिन्हित पूर्णांक objnr;
	अचिन्हित दीर्घ offset;

	ptr = kasan_reset_tag(ptr);

	/* Find and validate object. */
	cachep = page->slab_cache;
	objnr = obj_to_index(cachep, page, (व्योम *)ptr);
	BUG_ON(objnr >= cachep->num);

	/* Find offset within object. */
	अगर (is_kfence_address(ptr))
		offset = ptr - kfence_object_start(ptr);
	अन्यथा
		offset = ptr - index_to_obj(cachep, page, objnr) - obj_offset(cachep);

	/* Allow address range falling entirely within usercopy region. */
	अगर (offset >= cachep->useroffset &&
	    offset - cachep->useroffset <= cachep->usersize &&
	    n <= cachep->useroffset - offset + cachep->usersize)
		वापस;

	/*
	 * If the copy is still within the allocated object, produce
	 * a warning instead of rejecting the copy. This is पूर्णांकended
	 * to be a temporary method to find any missing usercopy
	 * whitelists.
	 */
	अगर (usercopy_fallback &&
	    offset <= cachep->object_size &&
	    n <= cachep->object_size - offset) अणु
		usercopy_warn("SLAB object", cachep->name, to_user, offset, n);
		वापस;
	पूर्ण

	usercopy_पात("SLAB object", cachep->name, to_user, offset, n);
पूर्ण
#पूर्ण_अगर /* CONFIG_HARDENED_USERCOPY */

/**
 * __ksize -- Uninstrumented ksize.
 * @objp: poपूर्णांकer to the object
 *
 * Unlike ksize(), __ksize() is uninstrumented, and करोes not provide the same
 * safety checks as ksize() with KASAN instrumentation enabled.
 *
 * Return: size of the actual memory used by @objp in bytes
 */
माप_प्रकार __ksize(स्थिर व्योम *objp)
अणु
	काष्ठा kmem_cache *c;
	माप_प्रकार size;

	BUG_ON(!objp);
	अगर (unlikely(objp == ZERO_SIZE_PTR))
		वापस 0;

	c = virt_to_cache(objp);
	size = c ? c->object_size : 0;

	वापस size;
पूर्ण
EXPORT_SYMBOL(__ksize);
