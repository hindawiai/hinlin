<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * High memory handling common code and variables.
 *
 * (C) 1999 Andrea Arcangeli, SuSE GmbH, andrea@suse.de
 *          Gerhard Wichert, Siemens AG, Gerhard.Wichert@pdb.siemens.de
 *
 *
 * Redeचिन्हित the x86 32-bit VM architecture to deal with
 * 64-bit physical space. With current x86 CPUs this
 * means up to 64 Gigabytes physical RAM.
 *
 * Rewrote high memory support to move the page cache पूर्णांकo
 * high memory. Implemented permanent (schedulable) kmaps
 * based on Linus' idea.
 *
 * Copyright (C) 1999 Ingo Molnar <mingo@redhat.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/swap.h>
#समावेश <linux/bपन.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/mempool.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/hash.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kgdb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/vदो_स्मृति.h>

/*
 * Virtual_count is not a pure "count".
 *  0 means that it is not mapped, and has not been mapped
 *    since a TLB flush - it is usable.
 *  1 means that there are no users, but it has been mapped
 *    since the last TLB flush - so we can't use it.
 *  n means that there are (n-1) current users of it.
 */
#अगर_घोषित CONFIG_HIGHMEM

/*
 * Architecture with aliasing data cache may define the following family of
 * helper functions in its यंत्र/highस्मृति.स to control cache color of भव
 * addresses where physical memory pages are mapped by kmap.
 */
#अगर_अघोषित get_pkmap_color

/*
 * Determine color of भव address where the page should be mapped.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_pkmap_color(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण
#घोषणा get_pkmap_color get_pkmap_color

/*
 * Get next index क्रम mapping inside PKMAP region क्रम page with given color.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_next_pkmap_nr(अचिन्हित पूर्णांक color)
अणु
	अटल अचिन्हित पूर्णांक last_pkmap_nr;

	last_pkmap_nr = (last_pkmap_nr + 1) & LAST_PKMAP_MASK;
	वापस last_pkmap_nr;
पूर्ण

/*
 * Determine अगर page index inside PKMAP region (pkmap_nr) of given color
 * has wrapped around PKMAP region end. When this happens an attempt to
 * flush all unused PKMAP slots is made.
 */
अटल अंतरभूत पूर्णांक no_more_pkmaps(अचिन्हित पूर्णांक pkmap_nr, अचिन्हित पूर्णांक color)
अणु
	वापस pkmap_nr == 0;
पूर्ण

/*
 * Get the number of PKMAP entries of the given color. If no मुक्त slot is
 * found after checking that many entries, kmap will sleep रुकोing क्रम
 * someone to call kunmap and मुक्त PKMAP slot.
 */
अटल अंतरभूत पूर्णांक get_pkmap_entries_count(अचिन्हित पूर्णांक color)
अणु
	वापस LAST_PKMAP;
पूर्ण

/*
 * Get head of a रुको queue क्रम PKMAP entries of the given color.
 * Wait queues क्रम dअगरferent mapping colors should be independent to aव्योम
 * unnecessary wakeups caused by मुक्तing of slots of other colors.
 */
अटल अंतरभूत रुको_queue_head_t *get_pkmap_रुको_queue_head(अचिन्हित पूर्णांक color)
अणु
	अटल DECLARE_WAIT_QUEUE_HEAD(pkmap_map_रुको);

	वापस &pkmap_map_रुको;
पूर्ण
#पूर्ण_अगर

atomic_दीर्घ_t _totalhigh_pages __पढ़ो_mostly;
EXPORT_SYMBOL(_totalhigh_pages);

अचिन्हित पूर्णांक __nr_मुक्त_highpages(व्योम)
अणु
	काष्ठा zone *zone;
	अचिन्हित पूर्णांक pages = 0;

	क्रम_each_populated_zone(zone) अणु
		अगर (is_highmem(zone))
			pages += zone_page_state(zone, NR_FREE_PAGES);
	पूर्ण

	वापस pages;
पूर्ण

अटल पूर्णांक pkmap_count[LAST_PKMAP];
अटल  __cacheline_aligned_in_smp DEFINE_SPINLOCK(kmap_lock);

pte_t *pkmap_page_table;

/*
 * Most architectures have no use क्रम kmap_high_get(), so let's असलtract
 * the disabling of IRQ out of the locking in that हाल to save on a
 * potential useless overhead.
 */
#अगर_घोषित ARCH_NEEDS_KMAP_HIGH_GET
#घोषणा lock_kmap()             spin_lock_irq(&kmap_lock)
#घोषणा unlock_kmap()           spin_unlock_irq(&kmap_lock)
#घोषणा lock_kmap_any(flags)    spin_lock_irqsave(&kmap_lock, flags)
#घोषणा unlock_kmap_any(flags)  spin_unlock_irqrestore(&kmap_lock, flags)
#अन्यथा
#घोषणा lock_kmap()             spin_lock(&kmap_lock)
#घोषणा unlock_kmap()           spin_unlock(&kmap_lock)
#घोषणा lock_kmap_any(flags)    \
		करो अणु spin_lock(&kmap_lock); (व्योम)(flags); पूर्ण जबतक (0)
#घोषणा unlock_kmap_any(flags)  \
		करो अणु spin_unlock(&kmap_lock); (व्योम)(flags); पूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा page *__kmap_to_page(व्योम *vaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)vaddr;

	अगर (addr >= PKMAP_ADDR(0) && addr < PKMAP_ADDR(LAST_PKMAP)) अणु
		पूर्णांक i = PKMAP_NR(addr);

		वापस pte_page(pkmap_page_table[i]);
	पूर्ण

	वापस virt_to_page(addr);
पूर्ण
EXPORT_SYMBOL(__kmap_to_page);

अटल व्योम flush_all_zero_pkmaps(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक need_flush = 0;

	flush_cache_kmaps();

	क्रम (i = 0; i < LAST_PKMAP; i++) अणु
		काष्ठा page *page;

		/*
		 * zero means we करोn't have anything to करो,
		 * >1 means that it is still in use. Only
		 * a count of 1 means that it is मुक्त but
		 * needs to be unmapped
		 */
		अगर (pkmap_count[i] != 1)
			जारी;
		pkmap_count[i] = 0;

		/* sanity check */
		BUG_ON(pte_none(pkmap_page_table[i]));

		/*
		 * Don't need an atomic fetch-and-clear op here;
		 * no-one has the page mapped, and cannot get at
		 * its भव address (and hence PTE) without first
		 * getting the kmap_lock (which is held here).
		 * So no dangers, even with speculative execution.
		 */
		page = pte_page(pkmap_page_table[i]);
		pte_clear(&init_mm, PKMAP_ADDR(i), &pkmap_page_table[i]);

		set_page_address(page, शून्य);
		need_flush = 1;
	पूर्ण
	अगर (need_flush)
		flush_tlb_kernel_range(PKMAP_ADDR(0), PKMAP_ADDR(LAST_PKMAP));
पूर्ण

व्योम __kmap_flush_unused(व्योम)
अणु
	lock_kmap();
	flush_all_zero_pkmaps();
	unlock_kmap();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ map_new_भव(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ vaddr;
	पूर्णांक count;
	अचिन्हित पूर्णांक last_pkmap_nr;
	अचिन्हित पूर्णांक color = get_pkmap_color(page);

start:
	count = get_pkmap_entries_count(color);
	/* Find an empty entry */
	क्रम (;;) अणु
		last_pkmap_nr = get_next_pkmap_nr(color);
		अगर (no_more_pkmaps(last_pkmap_nr, color)) अणु
			flush_all_zero_pkmaps();
			count = get_pkmap_entries_count(color);
		पूर्ण
		अगर (!pkmap_count[last_pkmap_nr])
			अवरोध;	/* Found a usable entry */
		अगर (--count)
			जारी;

		/*
		 * Sleep क्रम somebody अन्यथा to unmap their entries
		 */
		अणु
			DECLARE_WAITQUEUE(रुको, current);
			रुको_queue_head_t *pkmap_map_रुको =
				get_pkmap_रुको_queue_head(color);

			__set_current_state(TASK_UNINTERRUPTIBLE);
			add_रुको_queue(pkmap_map_रुको, &रुको);
			unlock_kmap();
			schedule();
			हटाओ_रुको_queue(pkmap_map_रुको, &रुको);
			lock_kmap();

			/* Somebody अन्यथा might have mapped it जबतक we slept */
			अगर (page_address(page))
				वापस (अचिन्हित दीर्घ)page_address(page);

			/* Re-start */
			जाओ start;
		पूर्ण
	पूर्ण
	vaddr = PKMAP_ADDR(last_pkmap_nr);
	set_pte_at(&init_mm, vaddr,
		   &(pkmap_page_table[last_pkmap_nr]), mk_pte(page, kmap_prot));

	pkmap_count[last_pkmap_nr] = 1;
	set_page_address(page, (व्योम *)vaddr);

	वापस vaddr;
पूर्ण

/**
 * kmap_high - map a highmem page पूर्णांकo memory
 * @page: &काष्ठा page to map
 *
 * Returns the page's भव memory address.
 *
 * We cannot call this from पूर्णांकerrupts, as it may block.
 */
व्योम *kmap_high(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ vaddr;

	/*
	 * For highmem pages, we can't trust "virtual" until
	 * after we have the lock.
	 */
	lock_kmap();
	vaddr = (अचिन्हित दीर्घ)page_address(page);
	अगर (!vaddr)
		vaddr = map_new_भव(page);
	pkmap_count[PKMAP_NR(vaddr)]++;
	BUG_ON(pkmap_count[PKMAP_NR(vaddr)] < 2);
	unlock_kmap();
	वापस (व्योम *) vaddr;
पूर्ण
EXPORT_SYMBOL(kmap_high);

#अगर_घोषित ARCH_NEEDS_KMAP_HIGH_GET
/**
 * kmap_high_get - pin a highmem page पूर्णांकo memory
 * @page: &काष्ठा page to pin
 *
 * Returns the page's current भव memory address, or शून्य अगर no mapping
 * exists.  If and only अगर a non null address is वापसed then a
 * matching call to kunmap_high() is necessary.
 *
 * This can be called from any context.
 */
व्योम *kmap_high_get(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ vaddr, flags;

	lock_kmap_any(flags);
	vaddr = (अचिन्हित दीर्घ)page_address(page);
	अगर (vaddr) अणु
		BUG_ON(pkmap_count[PKMAP_NR(vaddr)] < 1);
		pkmap_count[PKMAP_NR(vaddr)]++;
	पूर्ण
	unlock_kmap_any(flags);
	वापस (व्योम *) vaddr;
पूर्ण
#पूर्ण_अगर

/**
 * kunmap_high - unmap a highmem page पूर्णांकo memory
 * @page: &काष्ठा page to unmap
 *
 * If ARCH_NEEDS_KMAP_HIGH_GET is not defined then this may be called
 * only from user context.
 */
व्योम kunmap_high(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ vaddr;
	अचिन्हित दीर्घ nr;
	अचिन्हित दीर्घ flags;
	पूर्णांक need_wakeup;
	अचिन्हित पूर्णांक color = get_pkmap_color(page);
	रुको_queue_head_t *pkmap_map_रुको;

	lock_kmap_any(flags);
	vaddr = (अचिन्हित दीर्घ)page_address(page);
	BUG_ON(!vaddr);
	nr = PKMAP_NR(vaddr);

	/*
	 * A count must never go करोwn to zero
	 * without a TLB flush!
	 */
	need_wakeup = 0;
	चयन (--pkmap_count[nr]) अणु
	हाल 0:
		BUG();
	हाल 1:
		/*
		 * Aव्योम an unnecessary wake_up() function call.
		 * The common हाल is pkmap_count[] == 1, but
		 * no रुकोers.
		 * The tasks queued in the रुको-queue are guarded
		 * by both the lock in the रुको-queue-head and by
		 * the kmap_lock.  As the kmap_lock is held here,
		 * no need क्रम the रुको-queue-head's lock.  Simply
		 * test अगर the queue is empty.
		 */
		pkmap_map_रुको = get_pkmap_रुको_queue_head(color);
		need_wakeup = रुकोqueue_active(pkmap_map_रुको);
	पूर्ण
	unlock_kmap_any(flags);

	/* करो wake-up, अगर needed, race-मुक्त outside of the spin lock */
	अगर (need_wakeup)
		wake_up(pkmap_map_रुको);
पूर्ण
EXPORT_SYMBOL(kunmap_high);

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
व्योम zero_user_segments(काष्ठा page *page, अचिन्हित start1, अचिन्हित end1,
		अचिन्हित start2, अचिन्हित end2)
अणु
	अचिन्हित पूर्णांक i;

	BUG_ON(end1 > page_size(page) || end2 > page_size(page));

	अगर (start1 >= end1)
		start1 = end1 = 0;
	अगर (start2 >= end2)
		start2 = end2 = 0;

	क्रम (i = 0; i < compound_nr(page); i++) अणु
		व्योम *kaddr = शून्य;

		अगर (start1 >= PAGE_SIZE) अणु
			start1 -= PAGE_SIZE;
			end1 -= PAGE_SIZE;
		पूर्ण अन्यथा अणु
			अचिन्हित this_end = min_t(अचिन्हित, end1, PAGE_SIZE);

			अगर (end1 > start1) अणु
				kaddr = kmap_atomic(page + i);
				स_रखो(kaddr + start1, 0, this_end - start1);
			पूर्ण
			end1 -= this_end;
			start1 = 0;
		पूर्ण

		अगर (start2 >= PAGE_SIZE) अणु
			start2 -= PAGE_SIZE;
			end2 -= PAGE_SIZE;
		पूर्ण अन्यथा अणु
			अचिन्हित this_end = min_t(अचिन्हित, end2, PAGE_SIZE);

			अगर (end2 > start2) अणु
				अगर (!kaddr)
					kaddr = kmap_atomic(page + i);
				स_रखो(kaddr + start2, 0, this_end - start2);
			पूर्ण
			end2 -= this_end;
			start2 = 0;
		पूर्ण

		अगर (kaddr) अणु
			kunmap_atomic(kaddr);
			flush_dcache_page(page + i);
		पूर्ण

		अगर (!end1 && !end2)
			अवरोध;
	पूर्ण

	BUG_ON((start1 | start2 | end1 | end2) != 0);
पूर्ण
EXPORT_SYMBOL(zero_user_segments);
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
#पूर्ण_अगर /* CONFIG_HIGHMEM */

#अगर_घोषित CONFIG_KMAP_LOCAL

#समावेश <यंत्र/kmap_size.h>

/*
 * With DEBUG_KMAP_LOCAL the stack depth is द्विगुनd and every second
 * slot is unused which acts as a guard page
 */
#अगर_घोषित CONFIG_DEBUG_KMAP_LOCAL
# define KM_INCR	2
#अन्यथा
# define KM_INCR	1
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक kmap_local_idx_push(व्योम)
अणु
	WARN_ON_ONCE(in_irq() && !irqs_disabled());
	current->kmap_ctrl.idx += KM_INCR;
	BUG_ON(current->kmap_ctrl.idx >= KM_MAX_IDX);
	वापस current->kmap_ctrl.idx - 1;
पूर्ण

अटल अंतरभूत पूर्णांक kmap_local_idx(व्योम)
अणु
	वापस current->kmap_ctrl.idx - 1;
पूर्ण

अटल अंतरभूत व्योम kmap_local_idx_pop(व्योम)
अणु
	current->kmap_ctrl.idx -= KM_INCR;
	BUG_ON(current->kmap_ctrl.idx < 0);
पूर्ण

#अगर_अघोषित arch_kmap_local_post_map
# define arch_kmap_local_post_map(vaddr, pteval)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित arch_kmap_local_pre_unmap
# define arch_kmap_local_pre_unmap(vaddr)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित arch_kmap_local_post_unmap
# define arch_kmap_local_post_unmap(vaddr)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित arch_kmap_local_map_idx
#घोषणा arch_kmap_local_map_idx(idx, pfn)	kmap_local_calc_idx(idx)
#पूर्ण_अगर

#अगर_अघोषित arch_kmap_local_unmap_idx
#घोषणा arch_kmap_local_unmap_idx(idx, vaddr)	kmap_local_calc_idx(idx)
#पूर्ण_अगर

#अगर_अघोषित arch_kmap_local_high_get
अटल अंतरभूत व्योम *arch_kmap_local_high_get(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_kmap_local_set_pte
#घोषणा arch_kmap_local_set_pte(mm, vaddr, ptep, ptev)	\
	set_pte_at(mm, vaddr, ptep, ptev)
#पूर्ण_अगर

/* Unmap a local mapping which was obtained by kmap_high_get() */
अटल अंतरभूत bool kmap_high_unmap_local(अचिन्हित दीर्घ vaddr)
अणु
#अगर_घोषित ARCH_NEEDS_KMAP_HIGH_GET
	अगर (vaddr >= PKMAP_ADDR(0) && vaddr < PKMAP_ADDR(LAST_PKMAP)) अणु
		kunmap_high(pte_page(pkmap_page_table[PKMAP_NR(vaddr)]));
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक kmap_local_calc_idx(पूर्णांक idx)
अणु
	वापस idx + KM_MAX_IDX * smp_processor_id();
पूर्ण

अटल pte_t *__kmap_pte;

अटल pte_t *kmap_get_pte(व्योम)
अणु
	अगर (!__kmap_pte)
		__kmap_pte = virt_to_kpte(__fix_to_virt(FIX_KMAP_BEGIN));
	वापस __kmap_pte;
पूर्ण

व्योम *__kmap_local_pfn_prot(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t pteval, *kmap_pte = kmap_get_pte();
	अचिन्हित दीर्घ vaddr;
	पूर्णांक idx;

	/*
	 * Disable migration so resulting भव address is stable
	 * across preemption.
	 */
	migrate_disable();
	preempt_disable();
	idx = arch_kmap_local_map_idx(kmap_local_idx_push(), pfn);
	vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
	BUG_ON(!pte_none(*(kmap_pte - idx)));
	pteval = pfn_pte(pfn, prot);
	arch_kmap_local_set_pte(&init_mm, vaddr, kmap_pte - idx, pteval);
	arch_kmap_local_post_map(vaddr, pteval);
	current->kmap_ctrl.pteval[kmap_local_idx()] = pteval;
	preempt_enable();

	वापस (व्योम *)vaddr;
पूर्ण
EXPORT_SYMBOL_GPL(__kmap_local_pfn_prot);

व्योम *__kmap_local_page_prot(काष्ठा page *page, pgprot_t prot)
अणु
	व्योम *kmap;

	/*
	 * To broaden the usage of the actual kmap_local() machinery always map
	 * pages when debugging is enabled and the architecture has no problems
	 * with alias mappings.
	 */
	अगर (!IS_ENABLED(CONFIG_DEBUG_KMAP_LOCAL_FORCE_MAP) && !PageHighMem(page))
		वापस page_address(page);

	/* Try kmap_high_get() अगर architecture has it enabled */
	kmap = arch_kmap_local_high_get(page);
	अगर (kmap)
		वापस kmap;

	वापस __kmap_local_pfn_prot(page_to_pfn(page), prot);
पूर्ण
EXPORT_SYMBOL(__kmap_local_page_prot);

व्योम kunmap_local_indexed(व्योम *vaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) vaddr & PAGE_MASK;
	pte_t *kmap_pte = kmap_get_pte();
	पूर्णांक idx;

	अगर (addr < __fix_to_virt(FIX_KMAP_END) ||
	    addr > __fix_to_virt(FIX_KMAP_BEGIN)) अणु
		अगर (IS_ENABLED(CONFIG_DEBUG_KMAP_LOCAL_FORCE_MAP)) अणु
			/* This _should_ never happen! See above. */
			WARN_ON_ONCE(1);
			वापस;
		पूर्ण
		/*
		 * Handle mappings which were obtained by kmap_high_get()
		 * first as the भव address of such mappings is below
		 * PAGE_OFFSET. Warn क्रम all other addresses which are in
		 * the user space part of the भव address space.
		 */
		अगर (!kmap_high_unmap_local(addr))
			WARN_ON_ONCE(addr < PAGE_OFFSET);
		वापस;
	पूर्ण

	preempt_disable();
	idx = arch_kmap_local_unmap_idx(kmap_local_idx(), addr);
	WARN_ON_ONCE(addr != __fix_to_virt(FIX_KMAP_BEGIN + idx));

	arch_kmap_local_pre_unmap(addr);
	pte_clear(&init_mm, addr, kmap_pte - idx);
	arch_kmap_local_post_unmap(addr);
	current->kmap_ctrl.pteval[kmap_local_idx()] = __pte(0);
	kmap_local_idx_pop();
	preempt_enable();
	migrate_enable();
पूर्ण
EXPORT_SYMBOL(kunmap_local_indexed);

/*
 * Invoked beक्रमe चयन_to(). This is safe even when during or after
 * clearing the maps an पूर्णांकerrupt which needs a kmap_local happens because
 * the task::kmap_ctrl.idx is not modअगरied by the unmapping code so a
 * nested kmap_local will use the next unused index and restore the index
 * on unmap. The alपढ़ोy cleared kmaps of the outgoing task are irrelevant
 * because the पूर्णांकerrupt context करोes not know about them. The same applies
 * when scheduling back in क्रम an पूर्णांकerrupt which happens beक्रमe the
 * restore is complete.
 */
व्योम __kmap_local_sched_out(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	pte_t *kmap_pte = kmap_get_pte();
	पूर्णांक i;

	/* Clear kmaps */
	क्रम (i = 0; i < tsk->kmap_ctrl.idx; i++) अणु
		pte_t pteval = tsk->kmap_ctrl.pteval[i];
		अचिन्हित दीर्घ addr;
		पूर्णांक idx;

		/* With debug all even slots are unmapped and act as guard */
		अगर (IS_ENABLED(CONFIG_DEBUG_KMAP_LOCAL) && !(i & 0x01)) अणु
			WARN_ON_ONCE(!pte_none(pteval));
			जारी;
		पूर्ण
		अगर (WARN_ON_ONCE(pte_none(pteval)))
			जारी;

		/*
		 * This is a horrible hack क्रम XTENSA to calculate the
		 * coloured PTE index. Uses the PFN encoded पूर्णांकo the pteval
		 * and the map index calculation because the actual mapped
		 * भव address is not stored in task::kmap_ctrl.
		 * For any sane architecture this is optimized out.
		 */
		idx = arch_kmap_local_map_idx(i, pte_pfn(pteval));

		addr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
		arch_kmap_local_pre_unmap(addr);
		pte_clear(&init_mm, addr, kmap_pte - idx);
		arch_kmap_local_post_unmap(addr);
	पूर्ण
पूर्ण

व्योम __kmap_local_sched_in(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	pte_t *kmap_pte = kmap_get_pte();
	पूर्णांक i;

	/* Restore kmaps */
	क्रम (i = 0; i < tsk->kmap_ctrl.idx; i++) अणु
		pte_t pteval = tsk->kmap_ctrl.pteval[i];
		अचिन्हित दीर्घ addr;
		पूर्णांक idx;

		/* With debug all even slots are unmapped and act as guard */
		अगर (IS_ENABLED(CONFIG_DEBUG_KMAP_LOCAL) && !(i & 0x01)) अणु
			WARN_ON_ONCE(!pte_none(pteval));
			जारी;
		पूर्ण
		अगर (WARN_ON_ONCE(pte_none(pteval)))
			जारी;

		/* See comment in __kmap_local_sched_out() */
		idx = arch_kmap_local_map_idx(i, pte_pfn(pteval));
		addr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
		set_pte_at(&init_mm, addr, kmap_pte - idx, pteval);
		arch_kmap_local_post_map(addr, pteval);
	पूर्ण
पूर्ण

व्योम kmap_local_विभाजन(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (WARN_ON_ONCE(tsk->kmap_ctrl.idx))
		स_रखो(&tsk->kmap_ctrl, 0, माप(tsk->kmap_ctrl));
पूर्ण

#पूर्ण_अगर

#अगर defined(HASHED_PAGE_VIRTUAL)

#घोषणा PA_HASH_ORDER	7

/*
 * Describes one page->भव association
 */
काष्ठा page_address_map अणु
	काष्ठा page *page;
	व्योम *भव;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा page_address_map page_address_maps[LAST_PKMAP];

/*
 * Hash table bucket
 */
अटल काष्ठा page_address_slot अणु
	काष्ठा list_head lh;			/* List of page_address_maps */
	spinlock_t lock;			/* Protect this bucket's list */
पूर्ण ____cacheline_aligned_in_smp page_address_htable[1<<PA_HASH_ORDER];

अटल काष्ठा page_address_slot *page_slot(स्थिर काष्ठा page *page)
अणु
	वापस &page_address_htable[hash_ptr(page, PA_HASH_ORDER)];
पूर्ण

/**
 * page_address - get the mapped भव address of a page
 * @page: &काष्ठा page to get the भव address of
 *
 * Returns the page's भव address.
 */
व्योम *page_address(स्थिर काष्ठा page *page)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *ret;
	काष्ठा page_address_slot *pas;

	अगर (!PageHighMem(page))
		वापस lowmem_page_address(page);

	pas = page_slot(page);
	ret = शून्य;
	spin_lock_irqsave(&pas->lock, flags);
	अगर (!list_empty(&pas->lh)) अणु
		काष्ठा page_address_map *pam;

		list_क्रम_each_entry(pam, &pas->lh, list) अणु
			अगर (pam->page == page) अणु
				ret = pam->भव;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
करोne:
	spin_unlock_irqrestore(&pas->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(page_address);

/**
 * set_page_address - set a page's भव address
 * @page: &काष्ठा page to set
 * @भव: भव address to use
 */
व्योम set_page_address(काष्ठा page *page, व्योम *भव)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा page_address_slot *pas;
	काष्ठा page_address_map *pam;

	BUG_ON(!PageHighMem(page));

	pas = page_slot(page);
	अगर (भव) अणु		/* Add */
		pam = &page_address_maps[PKMAP_NR((अचिन्हित दीर्घ)भव)];
		pam->page = page;
		pam->भव = भव;

		spin_lock_irqsave(&pas->lock, flags);
		list_add_tail(&pam->list, &pas->lh);
		spin_unlock_irqrestore(&pas->lock, flags);
	पूर्ण अन्यथा अणु		/* Remove */
		spin_lock_irqsave(&pas->lock, flags);
		list_क्रम_each_entry(pam, &pas->lh, list) अणु
			अगर (pam->page == page) अणु
				list_del(&pam->list);
				spin_unlock_irqrestore(&pas->lock, flags);
				जाओ करोne;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&pas->lock, flags);
	पूर्ण
करोne:
	वापस;
पूर्ण

व्योम __init page_address_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(page_address_htable); i++) अणु
		INIT_LIST_HEAD(&page_address_htable[i].lh);
		spin_lock_init(&page_address_htable[i].lock);
	पूर्ण
पूर्ण

#पूर्ण_अगर	/* defined(HASHED_PAGE_VIRTUAL) */
