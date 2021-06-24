<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KFENCE guarded object allocator and fault handling.
 *
 * Copyright (C) 2020, Google LLC.
 */

#घोषणा pr_fmt(fmt) "kfence: " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/kcsan-checks.h>
#समावेश <linux/kfence.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/memblock.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/kfence.h>

#समावेश "kfence.h"

/* Disables KFENCE on the first warning assuming an irrecoverable error. */
#घोषणा KFENCE_WARN_ON(cond)                                                   \
	(अणु                                                                     \
		स्थिर bool __cond = WARN_ON(cond);                             \
		अगर (unlikely(__cond))                                          \
			WRITE_ONCE(kfence_enabled, false);                     \
		__cond;                                                        \
	पूर्ण)

/* === Data ================================================================= */

अटल bool kfence_enabled __पढ़ो_mostly;

अटल अचिन्हित दीर्घ kfence_sample_पूर्णांकerval __पढ़ो_mostly = CONFIG_KFENCE_SAMPLE_INTERVAL;

#अगर_घोषित MODULE_PARAM_PREFIX
#अघोषित MODULE_PARAM_PREFIX
#पूर्ण_अगर
#घोषणा MODULE_PARAM_PREFIX "kfence."

अटल पूर्णांक param_set_sample_पूर्णांकerval(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ num;
	पूर्णांक ret = kम_से_अदीर्घ(val, 0, &num);

	अगर (ret < 0)
		वापस ret;

	अगर (!num) /* Using 0 to indicate KFENCE is disabled. */
		WRITE_ONCE(kfence_enabled, false);
	अन्यथा अगर (!READ_ONCE(kfence_enabled) && प्रणाली_state != SYSTEM_BOOTING)
		वापस -EINVAL; /* Cannot (re-)enable KFENCE on-the-fly. */

	*((अचिन्हित दीर्घ *)kp->arg) = num;
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_sample_पूर्णांकerval(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!READ_ONCE(kfence_enabled))
		वापस प्र_लिखो(buffer, "0\n");

	वापस param_get_uदीर्घ(buffer, kp);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops sample_पूर्णांकerval_param_ops = अणु
	.set = param_set_sample_पूर्णांकerval,
	.get = param_get_sample_पूर्णांकerval,
पूर्ण;
module_param_cb(sample_पूर्णांकerval, &sample_पूर्णांकerval_param_ops, &kfence_sample_पूर्णांकerval, 0600);

/* The pool of pages used क्रम guard pages and objects. */
अक्षर *__kfence_pool __ro_after_init;
EXPORT_SYMBOL(__kfence_pool); /* Export क्रम test modules. */

/*
 * Per-object metadata, with one-to-one mapping of object metadata to
 * backing pages (in __kfence_pool).
 */
अटल_निश्चित(CONFIG_KFENCE_NUM_OBJECTS > 0);
काष्ठा kfence_metadata kfence_metadata[CONFIG_KFENCE_NUM_OBJECTS];

/* Freelist with available objects. */
अटल काष्ठा list_head kfence_मुक्तlist = LIST_HEAD_INIT(kfence_मुक्तlist);
अटल DEFINE_RAW_SPINLOCK(kfence_मुक्तlist_lock); /* Lock protecting मुक्तlist. */

#अगर_घोषित CONFIG_KFENCE_STATIC_KEYS
/* The अटल key to set up a KFENCE allocation. */
DEFINE_STATIC_KEY_FALSE(kfence_allocation_key);
#पूर्ण_अगर

/* Gates the allocation, ensuring only one succeeds in a given period. */
atomic_t kfence_allocation_gate = ATOMIC_INIT(1);

/* Statistics counters क्रम debugfs. */
क्रमागत kfence_counter_id अणु
	KFENCE_COUNTER_ALLOCATED,
	KFENCE_COUNTER_ALLOCS,
	KFENCE_COUNTER_FREES,
	KFENCE_COUNTER_ZOMBIES,
	KFENCE_COUNTER_BUGS,
	KFENCE_COUNTER_COUNT,
पूर्ण;
अटल atomic_दीर्घ_t counters[KFENCE_COUNTER_COUNT];
अटल स्थिर अक्षर *स्थिर counter_names[] = अणु
	[KFENCE_COUNTER_ALLOCATED]	= "currently allocated",
	[KFENCE_COUNTER_ALLOCS]		= "total allocations",
	[KFENCE_COUNTER_FREES]		= "total frees",
	[KFENCE_COUNTER_ZOMBIES]	= "zombie allocations",
	[KFENCE_COUNTER_BUGS]		= "total bugs",
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(counter_names) == KFENCE_COUNTER_COUNT);

/* === Internals ============================================================ */

अटल bool kfence_protect(अचिन्हित दीर्घ addr)
अणु
	वापस !KFENCE_WARN_ON(!kfence_protect_page(ALIGN_DOWN(addr, PAGE_SIZE), true));
पूर्ण

अटल bool kfence_unprotect(अचिन्हित दीर्घ addr)
अणु
	वापस !KFENCE_WARN_ON(!kfence_protect_page(ALIGN_DOWN(addr, PAGE_SIZE), false));
पूर्ण

अटल अंतरभूत काष्ठा kfence_metadata *addr_to_metadata(अचिन्हित दीर्घ addr)
अणु
	दीर्घ index;

	/* The checks करो not affect perक्रमmance; only called from slow-paths. */

	अगर (!is_kfence_address((व्योम *)addr))
		वापस शून्य;

	/*
	 * May be an invalid index अगर called with an address at the edge of
	 * __kfence_pool, in which हाल we would report an "invalid access"
	 * error.
	 */
	index = (addr - (अचिन्हित दीर्घ)__kfence_pool) / (PAGE_SIZE * 2) - 1;
	अगर (index < 0 || index >= CONFIG_KFENCE_NUM_OBJECTS)
		वापस शून्य;

	वापस &kfence_metadata[index];
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ metadata_to_pageaddr(स्थिर काष्ठा kfence_metadata *meta)
अणु
	अचिन्हित दीर्घ offset = (meta - kfence_metadata + 1) * PAGE_SIZE * 2;
	अचिन्हित दीर्घ pageaddr = (अचिन्हित दीर्घ)&__kfence_pool[offset];

	/* The checks करो not affect perक्रमmance; only called from slow-paths. */

	/* Only call with a poपूर्णांकer पूर्णांकo kfence_metadata. */
	अगर (KFENCE_WARN_ON(meta < kfence_metadata ||
			   meta >= kfence_metadata + CONFIG_KFENCE_NUM_OBJECTS))
		वापस 0;

	/*
	 * This metadata object only ever maps to 1 page; verअगरy that the stored
	 * address is in the expected range.
	 */
	अगर (KFENCE_WARN_ON(ALIGN_DOWN(meta->addr, PAGE_SIZE) != pageaddr))
		वापस 0;

	वापस pageaddr;
पूर्ण

/*
 * Update the object's metadata state, including updating the alloc/मुक्त stacks
 * depending on the state transition.
 */
अटल noअंतरभूत व्योम metadata_update_state(काष्ठा kfence_metadata *meta,
					   क्रमागत kfence_object_state next)
अणु
	काष्ठा kfence_track *track =
		next == KFENCE_OBJECT_FREED ? &meta->मुक्त_track : &meta->alloc_track;

	lockdep_निश्चित_held(&meta->lock);

	/*
	 * Skip over 1 (this) functions; noअंतरभूत ensures we करो not accidentally
	 * skip over the caller by never inlining.
	 */
	track->num_stack_entries = stack_trace_save(track->stack_entries, KFENCE_STACK_DEPTH, 1);
	track->pid = task_pid_nr(current);

	/*
	 * Pairs with READ_ONCE() in
	 *	kfence_shutकरोwn_cache(),
	 *	kfence_handle_page_fault().
	 */
	WRITE_ONCE(meta->state, next);
पूर्ण

/* Write canary byte to @addr. */
अटल अंतरभूत bool set_canary_byte(u8 *addr)
अणु
	*addr = KFENCE_CANARY_PATTERN(addr);
	वापस true;
पूर्ण

/* Check canary byte at @addr. */
अटल अंतरभूत bool check_canary_byte(u8 *addr)
अणु
	अगर (likely(*addr == KFENCE_CANARY_PATTERN(addr)))
		वापस true;

	atomic_दीर्घ_inc(&counters[KFENCE_COUNTER_BUGS]);
	kfence_report_error((अचिन्हित दीर्घ)addr, false, शून्य, addr_to_metadata((अचिन्हित दीर्घ)addr),
			    KFENCE_ERROR_CORRUPTION);
	वापस false;
पूर्ण

/* __always_अंतरभूत this to ensure we won't करो an indirect call to fn. */
अटल __always_अंतरभूत व्योम क्रम_each_canary(स्थिर काष्ठा kfence_metadata *meta, bool (*fn)(u8 *))
अणु
	स्थिर अचिन्हित दीर्घ pageaddr = ALIGN_DOWN(meta->addr, PAGE_SIZE);
	अचिन्हित दीर्घ addr;

	lockdep_निश्चित_held(&meta->lock);

	/*
	 * We'll iterate over each canary byte per-side until fn() वापसs
	 * false. However, we'll still iterate over the canary bytes to the
	 * right of the object even अगर there was an error in the canary bytes to
	 * the left of the object. Specअगरically, अगर check_canary_byte()
	 * generates an error, showing both sides might give more clues as to
	 * what the error is about when displaying which bytes were corrupted.
	 */

	/* Apply to left of object. */
	क्रम (addr = pageaddr; addr < meta->addr; addr++) अणु
		अगर (!fn((u8 *)addr))
			अवरोध;
	पूर्ण

	/* Apply to right of object. */
	क्रम (addr = meta->addr + meta->size; addr < pageaddr + PAGE_SIZE; addr++) अणु
		अगर (!fn((u8 *)addr))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम *kfence_guarded_alloc(काष्ठा kmem_cache *cache, माप_प्रकार size, gfp_t gfp)
अणु
	काष्ठा kfence_metadata *meta = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा page *page;
	व्योम *addr;

	/* Try to obtain a मुक्त object. */
	raw_spin_lock_irqsave(&kfence_मुक्तlist_lock, flags);
	अगर (!list_empty(&kfence_मुक्तlist)) अणु
		meta = list_entry(kfence_मुक्तlist.next, काष्ठा kfence_metadata, list);
		list_del_init(&meta->list);
	पूर्ण
	raw_spin_unlock_irqrestore(&kfence_मुक्तlist_lock, flags);
	अगर (!meta)
		वापस शून्य;

	अगर (unlikely(!raw_spin_trylock_irqsave(&meta->lock, flags))) अणु
		/*
		 * This is extremely unlikely -- we are reporting on a
		 * use-after-मुक्त, which locked meta->lock, and the reporting
		 * code via prपूर्णांकk calls kदो_स्मृति() which ends up in
		 * kfence_alloc() and tries to grab the same object that we're
		 * reporting on. While it has never been observed, lockdep करोes
		 * report that there is a possibility of deadlock. Fix it by
		 * using trylock and bailing out gracefully.
		 */
		raw_spin_lock_irqsave(&kfence_मुक्तlist_lock, flags);
		/* Put the object back on the मुक्तlist. */
		list_add_tail(&meta->list, &kfence_मुक्तlist);
		raw_spin_unlock_irqrestore(&kfence_मुक्तlist_lock, flags);

		वापस शून्य;
	पूर्ण

	meta->addr = metadata_to_pageaddr(meta);
	/* Unprotect अगर we're reusing this page. */
	अगर (meta->state == KFENCE_OBJECT_FREED)
		kfence_unprotect(meta->addr);

	/*
	 * Note: क्रम allocations made beक्रमe RNG initialization, will always
	 * वापस zero. We still benefit from enabling KFENCE as early as
	 * possible, even when the RNG is not yet available, as this will allow
	 * KFENCE to detect bugs due to earlier allocations. The only करोwnside
	 * is that the out-of-bounds accesses detected are deterministic क्रम
	 * such allocations.
	 */
	अगर (pअक्रमom_u32_max(2)) अणु
		/* Allocate on the "right" side, re-calculate address. */
		meta->addr += PAGE_SIZE - size;
		meta->addr = ALIGN_DOWN(meta->addr, cache->align);
	पूर्ण

	addr = (व्योम *)meta->addr;

	/* Update reमुख्यing metadata. */
	metadata_update_state(meta, KFENCE_OBJECT_ALLOCATED);
	/* Pairs with READ_ONCE() in kfence_shutकरोwn_cache(). */
	WRITE_ONCE(meta->cache, cache);
	meta->size = size;
	क्रम_each_canary(meta, set_canary_byte);

	/* Set required काष्ठा page fields. */
	page = virt_to_page(meta->addr);
	page->slab_cache = cache;
	अगर (IS_ENABLED(CONFIG_SLUB))
		page->objects = 1;
	अगर (IS_ENABLED(CONFIG_SLAB))
		page->s_mem = addr;

	raw_spin_unlock_irqrestore(&meta->lock, flags);

	/* Memory initialization. */

	/*
	 * We check slab_want_init_on_alloc() ourselves, rather than letting
	 * SL*B करो the initialization, as otherwise we might overग_लिखो KFENCE's
	 * redzone.
	 */
	अगर (unlikely(slab_want_init_on_alloc(gfp, cache)))
		memzero_explicit(addr, size);
	अगर (cache->ctor)
		cache->ctor(addr);

	अगर (CONFIG_KFENCE_STRESS_TEST_FAULTS && !pअक्रमom_u32_max(CONFIG_KFENCE_STRESS_TEST_FAULTS))
		kfence_protect(meta->addr); /* Ranकरोm "faults" by protecting the object. */

	atomic_दीर्घ_inc(&counters[KFENCE_COUNTER_ALLOCATED]);
	atomic_दीर्घ_inc(&counters[KFENCE_COUNTER_ALLOCS]);

	वापस addr;
पूर्ण

अटल व्योम kfence_guarded_मुक्त(व्योम *addr, काष्ठा kfence_metadata *meta, bool zombie)
अणु
	काष्ठा kcsan_scoped_access निश्चित_page_exclusive;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&meta->lock, flags);

	अगर (meta->state != KFENCE_OBJECT_ALLOCATED || meta->addr != (अचिन्हित दीर्घ)addr) अणु
		/* Invalid or द्विगुन-मुक्त, bail out. */
		atomic_दीर्घ_inc(&counters[KFENCE_COUNTER_BUGS]);
		kfence_report_error((अचिन्हित दीर्घ)addr, false, शून्य, meta,
				    KFENCE_ERROR_INVALID_FREE);
		raw_spin_unlock_irqrestore(&meta->lock, flags);
		वापस;
	पूर्ण

	/* Detect racy use-after-मुक्त, or incorrect पुनः_स्मृतिation of this page by KFENCE. */
	kcsan_begin_scoped_access((व्योम *)ALIGN_DOWN((अचिन्हित दीर्घ)addr, PAGE_SIZE), PAGE_SIZE,
				  KCSAN_ACCESS_SCOPED | KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ASSERT,
				  &निश्चित_page_exclusive);

	अगर (CONFIG_KFENCE_STRESS_TEST_FAULTS)
		kfence_unprotect((अचिन्हित दीर्घ)addr); /* To check canary bytes. */

	/* Restore page protection अगर there was an OOB access. */
	अगर (meta->unरक्षित_page) अणु
		memzero_explicit((व्योम *)ALIGN_DOWN(meta->unरक्षित_page, PAGE_SIZE), PAGE_SIZE);
		kfence_protect(meta->unरक्षित_page);
		meta->unरक्षित_page = 0;
	पूर्ण

	/* Check canary bytes क्रम memory corruption. */
	क्रम_each_canary(meta, check_canary_byte);

	/*
	 * Clear memory अगर init-on-मुक्त is set. While we protect the page, the
	 * data is still there, and after a use-after-मुक्त is detected, we
	 * unprotect the page, so the data is still accessible.
	 */
	अगर (!zombie && unlikely(slab_want_init_on_मुक्त(meta->cache)))
		memzero_explicit(addr, meta->size);

	/* Mark the object as मुक्तd. */
	metadata_update_state(meta, KFENCE_OBJECT_FREED);

	raw_spin_unlock_irqrestore(&meta->lock, flags);

	/* Protect to detect use-after-मुक्तs. */
	kfence_protect((अचिन्हित दीर्घ)addr);

	kcsan_end_scoped_access(&निश्चित_page_exclusive);
	अगर (!zombie) अणु
		/* Add it to the tail of the मुक्तlist क्रम reuse. */
		raw_spin_lock_irqsave(&kfence_मुक्तlist_lock, flags);
		KFENCE_WARN_ON(!list_empty(&meta->list));
		list_add_tail(&meta->list, &kfence_मुक्तlist);
		raw_spin_unlock_irqrestore(&kfence_मुक्तlist_lock, flags);

		atomic_दीर्घ_dec(&counters[KFENCE_COUNTER_ALLOCATED]);
		atomic_दीर्घ_inc(&counters[KFENCE_COUNTER_FREES]);
	पूर्ण अन्यथा अणु
		/* See kfence_shutकरोwn_cache(). */
		atomic_दीर्घ_inc(&counters[KFENCE_COUNTER_ZOMBIES]);
	पूर्ण
पूर्ण

अटल व्योम rcu_guarded_मुक्त(काष्ठा rcu_head *h)
अणु
	काष्ठा kfence_metadata *meta = container_of(h, काष्ठा kfence_metadata, rcu_head);

	kfence_guarded_मुक्त((व्योम *)meta->addr, meta, false);
पूर्ण

अटल bool __init kfence_init_pool(व्योम)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)__kfence_pool;
	काष्ठा page *pages;
	पूर्णांक i;

	अगर (!__kfence_pool)
		वापस false;

	अगर (!arch_kfence_init_pool())
		जाओ err;

	pages = virt_to_page(addr);

	/*
	 * Set up object pages: they must have PG_slab set, to aव्योम मुक्तing
	 * these as real pages.
	 *
	 * We also want to aव्योम inserting kfence_मुक्त() in the kमुक्त()
	 * fast-path in SLUB, and thereक्रमe need to ensure kमुक्त() correctly
	 * enters __slab_मुक्त() slow-path.
	 */
	क्रम (i = 0; i < KFENCE_POOL_SIZE / PAGE_SIZE; i++) अणु
		अगर (!i || (i % 2))
			जारी;

		/* Verअगरy we करो not have a compound head page. */
		अगर (WARN_ON(compound_head(&pages[i]) != &pages[i]))
			जाओ err;

		__SetPageSlab(&pages[i]);
	पूर्ण

	/*
	 * Protect the first 2 pages. The first page is mostly unnecessary, and
	 * merely serves as an extended guard page. However, adding one
	 * additional page in the beginning gives us an even number of pages,
	 * which simplअगरies the mapping of address to metadata index.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (unlikely(!kfence_protect(addr)))
			जाओ err;

		addr += PAGE_SIZE;
	पूर्ण

	क्रम (i = 0; i < CONFIG_KFENCE_NUM_OBJECTS; i++) अणु
		काष्ठा kfence_metadata *meta = &kfence_metadata[i];

		/* Initialize metadata. */
		INIT_LIST_HEAD(&meta->list);
		raw_spin_lock_init(&meta->lock);
		meta->state = KFENCE_OBJECT_UNUSED;
		meta->addr = addr; /* Initialize क्रम validation in metadata_to_pageaddr(). */
		list_add_tail(&meta->list, &kfence_मुक्तlist);

		/* Protect the right redzone. */
		अगर (unlikely(!kfence_protect(addr + PAGE_SIZE)))
			जाओ err;

		addr += 2 * PAGE_SIZE;
	पूर्ण

	/*
	 * The pool is live and will never be deallocated from this poपूर्णांक on.
	 * Remove the pool object from the kmemleak object tree, as it would
	 * otherwise overlap with allocations वापसed by kfence_alloc(), which
	 * are रेजिस्टरed with kmemleak through the slab post-alloc hook.
	 */
	kmemleak_मुक्त(__kfence_pool);

	वापस true;

err:
	/*
	 * Only release unरक्षित pages, and करो not try to go back and change
	 * page attributes due to risk of failing to करो so as well. If changing
	 * page attributes क्रम some pages fails, it is very likely that it also
	 * fails क्रम the first page, and thereक्रमe expect addr==__kfence_pool in
	 * most failure हालs.
	 */
	memblock_मुक्त_late(__pa(addr), KFENCE_POOL_SIZE - (addr - (अचिन्हित दीर्घ)__kfence_pool));
	__kfence_pool = शून्य;
	वापस false;
पूर्ण

/* === DebugFS Interface ==================================================== */

अटल पूर्णांक stats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i;

	seq_म_लिखो(seq, "enabled: %i\n", READ_ONCE(kfence_enabled));
	क्रम (i = 0; i < KFENCE_COUNTER_COUNT; i++)
		seq_म_लिखो(seq, "%s: %ld\n", counter_names[i], atomic_दीर्घ_पढ़ो(&counters[i]));

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(stats);

/*
 * debugfs seq_file operations क्रम /sys/kernel/debug/kfence/objects.
 * start_object() and next_object() वापस the object index + 1, because शून्य is used
 * to stop iteration.
 */
अटल व्योम *start_object(काष्ठा seq_file *seq, loff_t *pos)
अणु
	अगर (*pos < CONFIG_KFENCE_NUM_OBJECTS)
		वापस (व्योम *)((दीर्घ)*pos + 1);
	वापस शून्य;
पूर्ण

अटल व्योम stop_object(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल व्योम *next_object(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	अगर (*pos < CONFIG_KFENCE_NUM_OBJECTS)
		वापस (व्योम *)((दीर्घ)*pos + 1);
	वापस शून्य;
पूर्ण

अटल पूर्णांक show_object(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा kfence_metadata *meta = &kfence_metadata[(दीर्घ)v - 1];
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&meta->lock, flags);
	kfence_prपूर्णांक_object(seq, meta);
	raw_spin_unlock_irqrestore(&meta->lock, flags);
	seq_माला_दो(seq, "---------------------------------\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations object_seqops = अणु
	.start = start_object,
	.next = next_object,
	.stop = stop_object,
	.show = show_object,
पूर्ण;

अटल पूर्णांक खोलो_objects(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &object_seqops);
पूर्ण

अटल स्थिर काष्ठा file_operations objects_fops = अणु
	.खोलो = खोलो_objects,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
पूर्ण;

अटल पूर्णांक __init kfence_debugfs_init(व्योम)
अणु
	काष्ठा dentry *kfence_dir = debugfs_create_dir("kfence", शून्य);

	debugfs_create_file("stats", 0444, kfence_dir, शून्य, &stats_fops);
	debugfs_create_file("objects", 0400, kfence_dir, शून्य, &objects_fops);
	वापस 0;
पूर्ण

late_initcall(kfence_debugfs_init);

/* === Allocation Gate Timer ================================================ */

#अगर_घोषित CONFIG_KFENCE_STATIC_KEYS
/* Wait queue to wake up allocation-gate समयr task. */
अटल DECLARE_WAIT_QUEUE_HEAD(allocation_रुको);

अटल व्योम wake_up_kfence_समयr(काष्ठा irq_work *work)
अणु
	wake_up(&allocation_रुको);
पूर्ण
अटल DEFINE_IRQ_WORK(wake_up_kfence_समयr_work, wake_up_kfence_समयr);
#पूर्ण_अगर

/*
 * Set up delayed work, which will enable and disable the अटल key. We need to
 * use a work queue (rather than a simple समयr), since enabling and disabling a
 * अटल key cannot be करोne from an पूर्णांकerrupt.
 *
 * Note: Toggling a अटल branch currently causes IPIs, and here we'll end up
 * with a total of 2 IPIs to all CPUs. If this ends up a problem in future (with
 * more aggressive sampling पूर्णांकervals), we could get away with a variant that
 * aव्योमs IPIs, at the cost of not immediately capturing allocations अगर the
 * inकाष्ठाions reमुख्य cached.
 */
अटल काष्ठा delayed_work kfence_समयr;
अटल व्योम toggle_allocation_gate(काष्ठा work_काष्ठा *work)
अणु
	अगर (!READ_ONCE(kfence_enabled))
		वापस;

	atomic_set(&kfence_allocation_gate, 0);
#अगर_घोषित CONFIG_KFENCE_STATIC_KEYS
	/* Enable अटल key, and aरुको allocation to happen. */
	अटल_branch_enable(&kfence_allocation_key);

	अगर (sysctl_hung_task_समयout_secs) अणु
		/*
		 * During low activity with no allocations we might रुको a
		 * जबतक; let's aव्योम the hung task warning.
		 */
		रुको_event_idle_समयout(allocation_रुको, atomic_पढ़ो(&kfence_allocation_gate),
					sysctl_hung_task_समयout_secs * HZ / 2);
	पूर्ण अन्यथा अणु
		रुको_event_idle(allocation_रुको, atomic_पढ़ो(&kfence_allocation_gate));
	पूर्ण

	/* Disable अटल key and reset समयr. */
	अटल_branch_disable(&kfence_allocation_key);
#पूर्ण_अगर
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &kfence_समयr,
			   msecs_to_jअगरfies(kfence_sample_पूर्णांकerval));
पूर्ण
अटल DECLARE_DELAYED_WORK(kfence_समयr, toggle_allocation_gate);

/* === Public पूर्णांकerface ===================================================== */

व्योम __init kfence_alloc_pool(व्योम)
अणु
	अगर (!kfence_sample_पूर्णांकerval)
		वापस;

	__kfence_pool = memblock_alloc(KFENCE_POOL_SIZE, PAGE_SIZE);

	अगर (!__kfence_pool)
		pr_err("failed to allocate pool\n");
पूर्ण

व्योम __init kfence_init(व्योम)
अणु
	/* Setting kfence_sample_पूर्णांकerval to 0 on boot disables KFENCE. */
	अगर (!kfence_sample_पूर्णांकerval)
		वापस;

	अगर (!kfence_init_pool()) अणु
		pr_err("%s failed\n", __func__);
		वापस;
	पूर्ण

	WRITE_ONCE(kfence_enabled, true);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &kfence_समयr, 0);
	pr_info("initialized - using %lu bytes for %d objects at 0x%p-0x%p\n", KFENCE_POOL_SIZE,
		CONFIG_KFENCE_NUM_OBJECTS, (व्योम *)__kfence_pool,
		(व्योम *)(__kfence_pool + KFENCE_POOL_SIZE));
पूर्ण

व्योम kfence_shutकरोwn_cache(काष्ठा kmem_cache *s)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा kfence_metadata *meta;
	पूर्णांक i;

	क्रम (i = 0; i < CONFIG_KFENCE_NUM_OBJECTS; i++) अणु
		bool in_use;

		meta = &kfence_metadata[i];

		/*
		 * If we observe some inconsistent cache and state pair where we
		 * should have वापसed false here, cache deकाष्ठाion is racing
		 * with either kmem_cache_alloc() or kmem_cache_मुक्त(). Taking
		 * the lock will not help, as dअगरferent critical section
		 * serialization will have the same outcome.
		 */
		अगर (READ_ONCE(meta->cache) != s ||
		    READ_ONCE(meta->state) != KFENCE_OBJECT_ALLOCATED)
			जारी;

		raw_spin_lock_irqsave(&meta->lock, flags);
		in_use = meta->cache == s && meta->state == KFENCE_OBJECT_ALLOCATED;
		raw_spin_unlock_irqrestore(&meta->lock, flags);

		अगर (in_use) अणु
			/*
			 * This cache still has allocations, and we should not
			 * release them back पूर्णांकo the मुक्तlist so they can still
			 * safely be used and retain the kernel's शेष
			 * behaviour of keeping the allocations alive (leak the
			 * cache); however, they effectively become "zombie
			 * allocations" as the KFENCE objects are the only ones
			 * still in use and the owning cache is being destroyed.
			 *
			 * We mark them मुक्तd, so that any subsequent use shows
			 * more useful error messages that will include stack
			 * traces of the user of the object, the original
			 * allocation, and caller to shutकरोwn_cache().
			 */
			kfence_guarded_मुक्त((व्योम *)meta->addr, meta, /*zombie=*/true);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < CONFIG_KFENCE_NUM_OBJECTS; i++) अणु
		meta = &kfence_metadata[i];

		/* See above. */
		अगर (READ_ONCE(meta->cache) != s || READ_ONCE(meta->state) != KFENCE_OBJECT_FREED)
			जारी;

		raw_spin_lock_irqsave(&meta->lock, flags);
		अगर (meta->cache == s && meta->state == KFENCE_OBJECT_FREED)
			meta->cache = शून्य;
		raw_spin_unlock_irqrestore(&meta->lock, flags);
	पूर्ण
पूर्ण

व्योम *__kfence_alloc(काष्ठा kmem_cache *s, माप_प्रकार size, gfp_t flags)
अणु
	/*
	 * allocation_gate only needs to become non-zero, so it करोesn't make
	 * sense to जारी writing to it and pay the associated contention
	 * cost, in हाल we have a large number of concurrent allocations.
	 */
	अगर (atomic_पढ़ो(&kfence_allocation_gate) || atomic_inc_वापस(&kfence_allocation_gate) > 1)
		वापस शून्य;
#अगर_घोषित CONFIG_KFENCE_STATIC_KEYS
	/*
	 * रुकोqueue_active() is fully ordered after the update of
	 * kfence_allocation_gate per atomic_inc_वापस().
	 */
	अगर (रुकोqueue_active(&allocation_रुको)) अणु
		/*
		 * Calling wake_up() here may deadlock when allocations happen
		 * from within समयr code. Use an irq_work to defer it.
		 */
		irq_work_queue(&wake_up_kfence_समयr_work);
	पूर्ण
#पूर्ण_अगर

	अगर (!READ_ONCE(kfence_enabled))
		वापस शून्य;

	अगर (size > PAGE_SIZE)
		वापस शून्य;

	वापस kfence_guarded_alloc(s, size, flags);
पूर्ण

माप_प्रकार kfence_ksize(स्थिर व्योम *addr)
अणु
	स्थिर काष्ठा kfence_metadata *meta = addr_to_metadata((अचिन्हित दीर्घ)addr);

	/*
	 * Read locklessly -- अगर there is a race with __kfence_alloc(), this is
	 * either a use-after-मुक्त or invalid access.
	 */
	वापस meta ? meta->size : 0;
पूर्ण

व्योम *kfence_object_start(स्थिर व्योम *addr)
अणु
	स्थिर काष्ठा kfence_metadata *meta = addr_to_metadata((अचिन्हित दीर्घ)addr);

	/*
	 * Read locklessly -- अगर there is a race with __kfence_alloc(), this is
	 * either a use-after-मुक्त or invalid access.
	 */
	वापस meta ? (व्योम *)meta->addr : शून्य;
पूर्ण

व्योम __kfence_मुक्त(व्योम *addr)
अणु
	काष्ठा kfence_metadata *meta = addr_to_metadata((अचिन्हित दीर्घ)addr);

	/*
	 * If the objects of the cache are SLAB_TYPESAFE_BY_RCU, defer मुक्तing
	 * the object, as the object page may be recycled क्रम other-typed
	 * objects once it has been मुक्तd. meta->cache may be शून्य अगर the cache
	 * was destroyed.
	 */
	अगर (unlikely(meta->cache && (meta->cache->flags & SLAB_TYPESAFE_BY_RCU)))
		call_rcu(&meta->rcu_head, rcu_guarded_मुक्त);
	अन्यथा
		kfence_guarded_मुक्त(addr, meta, false);
पूर्ण

bool kfence_handle_page_fault(अचिन्हित दीर्घ addr, bool is_ग_लिखो, काष्ठा pt_regs *regs)
अणु
	स्थिर पूर्णांक page_index = (addr - (अचिन्हित दीर्घ)__kfence_pool) / PAGE_SIZE;
	काष्ठा kfence_metadata *to_report = शून्य;
	क्रमागत kfence_error_type error_type;
	अचिन्हित दीर्घ flags;

	अगर (!is_kfence_address((व्योम *)addr))
		वापस false;

	अगर (!READ_ONCE(kfence_enabled)) /* If disabled at runसमय ... */
		वापस kfence_unprotect(addr); /* ... unprotect and proceed. */

	atomic_दीर्घ_inc(&counters[KFENCE_COUNTER_BUGS]);

	अगर (page_index % 2) अणु
		/* This is a redzone, report a buffer overflow. */
		काष्ठा kfence_metadata *meta;
		पूर्णांक distance = 0;

		meta = addr_to_metadata(addr - PAGE_SIZE);
		अगर (meta && READ_ONCE(meta->state) == KFENCE_OBJECT_ALLOCATED) अणु
			to_report = meta;
			/* Data race ok; distance calculation approximate. */
			distance = addr - data_race(meta->addr + meta->size);
		पूर्ण

		meta = addr_to_metadata(addr + PAGE_SIZE);
		अगर (meta && READ_ONCE(meta->state) == KFENCE_OBJECT_ALLOCATED) अणु
			/* Data race ok; distance calculation approximate. */
			अगर (!to_report || distance > data_race(meta->addr) - addr)
				to_report = meta;
		पूर्ण

		अगर (!to_report)
			जाओ out;

		raw_spin_lock_irqsave(&to_report->lock, flags);
		to_report->unरक्षित_page = addr;
		error_type = KFENCE_ERROR_OOB;

		/*
		 * If the object was मुक्तd beक्रमe we took the look we can still
		 * report this as an OOB -- the report will simply show the
		 * stacktrace of the मुक्त as well.
		 */
	पूर्ण अन्यथा अणु
		to_report = addr_to_metadata(addr);
		अगर (!to_report)
			जाओ out;

		raw_spin_lock_irqsave(&to_report->lock, flags);
		error_type = KFENCE_ERROR_UAF;
		/*
		 * We may race with __kfence_alloc(), and it is possible that a
		 * मुक्तd object may be पुनः_स्मृतिated. We simply report this as a
		 * use-after-मुक्त, with the stack trace showing the place where
		 * the object was re-allocated.
		 */
	पूर्ण

out:
	अगर (to_report) अणु
		kfence_report_error(addr, is_ग_लिखो, regs, to_report, error_type);
		raw_spin_unlock_irqrestore(&to_report->lock, flags);
	पूर्ण अन्यथा अणु
		/* This may be a UAF or OOB access, but we can't be sure. */
		kfence_report_error(addr, is_ग_लिखो, regs, शून्य, KFENCE_ERROR_INVALID);
	पूर्ण

	वापस kfence_unprotect(addr); /* Unprotect and let access proceed. */
पूर्ण
