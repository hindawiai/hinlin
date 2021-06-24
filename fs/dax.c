<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/dax.c - Direct Access fileप्रणाली code
 * Copyright (c) 2013-2014 Intel Corporation
 * Author: Matthew Wilcox <matthew.r.wilcox@पूर्णांकel.com>
 * Author: Ross Zwisler <ross.zwisler@linux.पूर्णांकel.com>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/dax.h>
#समावेश <linux/fs.h>
#समावेश <linux/genhd.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uपन.स>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/pfn_t.h>
#समावेश <linux/sizes.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/iomap.h>
#समावेश <यंत्र/pgभाग.स>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/fs_dax.h>

अटल अंतरभूत अचिन्हित पूर्णांक pe_order(क्रमागत page_entry_size pe_size)
अणु
	अगर (pe_size == PE_SIZE_PTE)
		वापस PAGE_SHIFT - PAGE_SHIFT;
	अगर (pe_size == PE_SIZE_PMD)
		वापस PMD_SHIFT - PAGE_SHIFT;
	अगर (pe_size == PE_SIZE_PUD)
		वापस PUD_SHIFT - PAGE_SHIFT;
	वापस ~0;
पूर्ण

/* We choose 4096 entries - same as per-zone page रुको tables */
#घोषणा DAX_WAIT_TABLE_BITS 12
#घोषणा DAX_WAIT_TABLE_ENTRIES (1 << DAX_WAIT_TABLE_BITS)

/* The 'colour' (ie low bits) within a PMD of a page offset.  */
#घोषणा PG_PMD_COLOUR	((PMD_SIZE >> PAGE_SHIFT) - 1)
#घोषणा PG_PMD_NR	(PMD_SIZE >> PAGE_SHIFT)

/* The order of a PMD entry */
#घोषणा PMD_ORDER	(PMD_SHIFT - PAGE_SHIFT)

अटल रुको_queue_head_t रुको_table[DAX_WAIT_TABLE_ENTRIES];

अटल पूर्णांक __init init_dax_रुको_table(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DAX_WAIT_TABLE_ENTRIES; i++)
		init_रुकोqueue_head(रुको_table + i);
	वापस 0;
पूर्ण
fs_initcall(init_dax_रुको_table);

/*
 * DAX pagecache entries use XArray value entries so they can't be mistaken
 * क्रम pages.  We use one bit क्रम locking, one bit क्रम the entry size (PMD)
 * and two more to tell us अगर the entry is a zero page or an empty entry that
 * is just used क्रम locking.  In total four special bits.
 *
 * If the PMD bit isn't set the entry has size PAGE_SIZE, and अगर the ZERO_PAGE
 * and EMPTY bits aren't set the entry is a normal DAX entry with a fileप्रणाली
 * block allocation.
 */
#घोषणा DAX_SHIFT	(4)
#घोषणा DAX_LOCKED	(1UL << 0)
#घोषणा DAX_PMD		(1UL << 1)
#घोषणा DAX_ZERO_PAGE	(1UL << 2)
#घोषणा DAX_EMPTY	(1UL << 3)

अटल अचिन्हित दीर्घ dax_to_pfn(व्योम *entry)
अणु
	वापस xa_to_value(entry) >> DAX_SHIFT;
पूर्ण

अटल व्योम *dax_make_entry(pfn_t pfn, अचिन्हित दीर्घ flags)
अणु
	वापस xa_mk_value(flags | (pfn_t_to_pfn(pfn) << DAX_SHIFT));
पूर्ण

अटल bool dax_is_locked(व्योम *entry)
अणु
	वापस xa_to_value(entry) & DAX_LOCKED;
पूर्ण

अटल अचिन्हित पूर्णांक dax_entry_order(व्योम *entry)
अणु
	अगर (xa_to_value(entry) & DAX_PMD)
		वापस PMD_ORDER;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ dax_is_pmd_entry(व्योम *entry)
अणु
	वापस xa_to_value(entry) & DAX_PMD;
पूर्ण

अटल bool dax_is_pte_entry(व्योम *entry)
अणु
	वापस !(xa_to_value(entry) & DAX_PMD);
पूर्ण

अटल पूर्णांक dax_is_zero_entry(व्योम *entry)
अणु
	वापस xa_to_value(entry) & DAX_ZERO_PAGE;
पूर्ण

अटल पूर्णांक dax_is_empty_entry(व्योम *entry)
अणु
	वापस xa_to_value(entry) & DAX_EMPTY;
पूर्ण

/*
 * true अगर the entry that was found is of a smaller order than the entry
 * we were looking क्रम
 */
अटल bool dax_is_conflict(व्योम *entry)
अणु
	वापस entry == XA_RETRY_ENTRY;
पूर्ण

/*
 * DAX page cache entry locking
 */
काष्ठा exceptional_entry_key अणु
	काष्ठा xarray *xa;
	pgoff_t entry_start;
पूर्ण;

काष्ठा रुको_exceptional_entry_queue अणु
	रुको_queue_entry_t रुको;
	काष्ठा exceptional_entry_key key;
पूर्ण;

/**
 * क्रमागत dax_wake_mode: रुकोqueue wakeup behaviour
 * @WAKE_ALL: wake all रुकोers in the रुकोqueue
 * @WAKE_NEXT: wake only the first रुकोer in the रुकोqueue
 */
क्रमागत dax_wake_mode अणु
	WAKE_ALL,
	WAKE_NEXT,
पूर्ण;

अटल रुको_queue_head_t *dax_entry_रुकोqueue(काष्ठा xa_state *xas,
		व्योम *entry, काष्ठा exceptional_entry_key *key)
अणु
	अचिन्हित दीर्घ hash;
	अचिन्हित दीर्घ index = xas->xa_index;

	/*
	 * If 'entry' is a PMD, align the 'index' that we use क्रम the रुको
	 * queue to the start of that PMD.  This ensures that all offsets in
	 * the range covered by the PMD map to the same bit lock.
	 */
	अगर (dax_is_pmd_entry(entry))
		index &= ~PG_PMD_COLOUR;
	key->xa = xas->xa;
	key->entry_start = index;

	hash = hash_दीर्घ((अचिन्हित दीर्घ)xas->xa ^ index, DAX_WAIT_TABLE_BITS);
	वापस रुको_table + hash;
पूर्ण

अटल पूर्णांक wake_exceptional_entry_func(रुको_queue_entry_t *रुको,
		अचिन्हित पूर्णांक mode, पूर्णांक sync, व्योम *keyp)
अणु
	काष्ठा exceptional_entry_key *key = keyp;
	काष्ठा रुको_exceptional_entry_queue *eरुको =
		container_of(रुको, काष्ठा रुको_exceptional_entry_queue, रुको);

	अगर (key->xa != eरुको->key.xa ||
	    key->entry_start != eरुको->key.entry_start)
		वापस 0;
	वापस स्वतःहटाओ_wake_function(रुको, mode, sync, शून्य);
पूर्ण

/*
 * @entry may no दीर्घer be the entry at the index in the mapping.
 * The important inक्रमmation it's conveying is whether the entry at
 * this index used to be a PMD entry.
 */
अटल व्योम dax_wake_entry(काष्ठा xa_state *xas, व्योम *entry,
			   क्रमागत dax_wake_mode mode)
अणु
	काष्ठा exceptional_entry_key key;
	रुको_queue_head_t *wq;

	wq = dax_entry_रुकोqueue(xas, entry, &key);

	/*
	 * Checking क्रम locked entry and prepare_to_रुको_exclusive() happens
	 * under the i_pages lock, ditto क्रम entry handling in our callers.
	 * So at this poपूर्णांक all tasks that could have seen our entry locked
	 * must be in the रुकोqueue and the following check will see them.
	 */
	अगर (रुकोqueue_active(wq))
		__wake_up(wq, TASK_NORMAL, mode == WAKE_ALL ? 0 : 1, &key);
पूर्ण

/*
 * Look up entry in page cache, रुको क्रम it to become unlocked अगर it
 * is a DAX entry and वापस it.  The caller must subsequently call
 * put_unlocked_entry() अगर it did not lock the entry or dax_unlock_entry()
 * अगर it did.  The entry वापसed may have a larger order than @order.
 * If @order is larger than the order of the entry found in i_pages, this
 * function वापसs a dax_is_conflict entry.
 *
 * Must be called with the i_pages lock held.
 */
अटल व्योम *get_unlocked_entry(काष्ठा xa_state *xas, अचिन्हित पूर्णांक order)
अणु
	व्योम *entry;
	काष्ठा रुको_exceptional_entry_queue eरुको;
	रुको_queue_head_t *wq;

	init_रुको(&eरुको.रुको);
	eरुको.रुको.func = wake_exceptional_entry_func;

	क्रम (;;) अणु
		entry = xas_find_conflict(xas);
		अगर (!entry || WARN_ON_ONCE(!xa_is_value(entry)))
			वापस entry;
		अगर (dax_entry_order(entry) < order)
			वापस XA_RETRY_ENTRY;
		अगर (!dax_is_locked(entry))
			वापस entry;

		wq = dax_entry_रुकोqueue(xas, entry, &eरुको.key);
		prepare_to_रुको_exclusive(wq, &eरुको.रुको,
					  TASK_UNINTERRUPTIBLE);
		xas_unlock_irq(xas);
		xas_reset(xas);
		schedule();
		finish_रुको(wq, &eरुको.रुको);
		xas_lock_irq(xas);
	पूर्ण
पूर्ण

/*
 * The only thing keeping the address space around is the i_pages lock
 * (it's cycled in clear_inode() after removing the entries from i_pages)
 * After we call xas_unlock_irq(), we cannot touch xas->xa.
 */
अटल व्योम रुको_entry_unlocked(काष्ठा xa_state *xas, व्योम *entry)
अणु
	काष्ठा रुको_exceptional_entry_queue eरुको;
	रुको_queue_head_t *wq;

	init_रुको(&eरुको.रुको);
	eरुको.रुको.func = wake_exceptional_entry_func;

	wq = dax_entry_रुकोqueue(xas, entry, &eरुको.key);
	/*
	 * Unlike get_unlocked_entry() there is no guarantee that this
	 * path ever successfully retrieves an unlocked entry beक्रमe an
	 * inode dies. Perक्रमm a non-exclusive रुको in हाल this path
	 * never successfully perक्रमms its own wake up.
	 */
	prepare_to_रुको(wq, &eरुको.रुको, TASK_UNINTERRUPTIBLE);
	xas_unlock_irq(xas);
	schedule();
	finish_रुको(wq, &eरुको.रुको);
पूर्ण

अटल व्योम put_unlocked_entry(काष्ठा xa_state *xas, व्योम *entry,
			       क्रमागत dax_wake_mode mode)
अणु
	अगर (entry && !dax_is_conflict(entry))
		dax_wake_entry(xas, entry, mode);
पूर्ण

/*
 * We used the xa_state to get the entry, but then we locked the entry and
 * dropped the xa_lock, so we know the xa_state is stale and must be reset
 * beक्रमe use.
 */
अटल व्योम dax_unlock_entry(काष्ठा xa_state *xas, व्योम *entry)
अणु
	व्योम *old;

	BUG_ON(dax_is_locked(entry));
	xas_reset(xas);
	xas_lock_irq(xas);
	old = xas_store(xas, entry);
	xas_unlock_irq(xas);
	BUG_ON(!dax_is_locked(old));
	dax_wake_entry(xas, entry, WAKE_NEXT);
पूर्ण

/*
 * Return: The entry stored at this location beक्रमe it was locked.
 */
अटल व्योम *dax_lock_entry(काष्ठा xa_state *xas, व्योम *entry)
अणु
	अचिन्हित दीर्घ v = xa_to_value(entry);
	वापस xas_store(xas, xa_mk_value(v | DAX_LOCKED));
पूर्ण

अटल अचिन्हित दीर्घ dax_entry_size(व्योम *entry)
अणु
	अगर (dax_is_zero_entry(entry))
		वापस 0;
	अन्यथा अगर (dax_is_empty_entry(entry))
		वापस 0;
	अन्यथा अगर (dax_is_pmd_entry(entry))
		वापस PMD_SIZE;
	अन्यथा
		वापस PAGE_SIZE;
पूर्ण

अटल अचिन्हित दीर्घ dax_end_pfn(व्योम *entry)
अणु
	वापस dax_to_pfn(entry) + dax_entry_size(entry) / PAGE_SIZE;
पूर्ण

/*
 * Iterate through all mapped pfns represented by an entry, i.e. skip
 * 'empty' and 'zero' entries.
 */
#घोषणा क्रम_each_mapped_pfn(entry, pfn) \
	क्रम (pfn = dax_to_pfn(entry); \
			pfn < dax_end_pfn(entry); pfn++)

/*
 * TODO: क्रम reflink+dax we need a way to associate a single page with
 * multiple address_space instances at dअगरferent linear_page_index()
 * offsets.
 */
अटल व्योम dax_associate_entry(व्योम *entry, काष्ठा address_space *mapping,
		काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ size = dax_entry_size(entry), pfn, index;
	पूर्णांक i = 0;

	अगर (IS_ENABLED(CONFIG_FS_DAX_LIMITED))
		वापस;

	index = linear_page_index(vma, address & ~(size - 1));
	क्रम_each_mapped_pfn(entry, pfn) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		WARN_ON_ONCE(page->mapping);
		page->mapping = mapping;
		page->index = index + i++;
	पूर्ण
पूर्ण

अटल व्योम dax_disassociate_entry(व्योम *entry, काष्ठा address_space *mapping,
		bool trunc)
अणु
	अचिन्हित दीर्घ pfn;

	अगर (IS_ENABLED(CONFIG_FS_DAX_LIMITED))
		वापस;

	क्रम_each_mapped_pfn(entry, pfn) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		WARN_ON_ONCE(trunc && page_ref_count(page) > 1);
		WARN_ON_ONCE(page->mapping && page->mapping != mapping);
		page->mapping = शून्य;
		page->index = 0;
	पूर्ण
पूर्ण

अटल काष्ठा page *dax_busy_page(व्योम *entry)
अणु
	अचिन्हित दीर्घ pfn;

	क्रम_each_mapped_pfn(entry, pfn) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		अगर (page_ref_count(page) > 1)
			वापस page;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * dax_lock_mapping_entry - Lock the DAX entry corresponding to a page
 * @page: The page whose entry we want to lock
 *
 * Context: Process context.
 * Return: A cookie to pass to dax_unlock_page() or 0 अगर the entry could
 * not be locked.
 */
dax_entry_t dax_lock_page(काष्ठा page *page)
अणु
	XA_STATE(xas, शून्य, 0);
	व्योम *entry;

	/* Ensure page->mapping isn't मुक्तd जबतक we look at it */
	rcu_पढ़ो_lock();
	क्रम (;;) अणु
		काष्ठा address_space *mapping = READ_ONCE(page->mapping);

		entry = शून्य;
		अगर (!mapping || !dax_mapping(mapping))
			अवरोध;

		/*
		 * In the device-dax हाल there's no need to lock, a
		 * काष्ठा dev_pagemap pin is sufficient to keep the
		 * inode alive, and we assume we have dev_pagemap pin
		 * otherwise we would not have a valid pfn_to_page()
		 * translation.
		 */
		entry = (व्योम *)~0UL;
		अगर (S_ISCHR(mapping->host->i_mode))
			अवरोध;

		xas.xa = &mapping->i_pages;
		xas_lock_irq(&xas);
		अगर (mapping != page->mapping) अणु
			xas_unlock_irq(&xas);
			जारी;
		पूर्ण
		xas_set(&xas, page->index);
		entry = xas_load(&xas);
		अगर (dax_is_locked(entry)) अणु
			rcu_पढ़ो_unlock();
			रुको_entry_unlocked(&xas, entry);
			rcu_पढ़ो_lock();
			जारी;
		पूर्ण
		dax_lock_entry(&xas, entry);
		xas_unlock_irq(&xas);
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस (dax_entry_t)entry;
पूर्ण

व्योम dax_unlock_page(काष्ठा page *page, dax_entry_t cookie)
अणु
	काष्ठा address_space *mapping = page->mapping;
	XA_STATE(xas, &mapping->i_pages, page->index);

	अगर (S_ISCHR(mapping->host->i_mode))
		वापस;

	dax_unlock_entry(&xas, (व्योम *)cookie);
पूर्ण

/*
 * Find page cache entry at given index. If it is a DAX entry, वापस it
 * with the entry locked. If the page cache करोesn't contain an entry at
 * that index, add a locked empty entry.
 *
 * When requesting an entry with size DAX_PMD, grab_mapping_entry() will
 * either वापस that locked entry or will वापस VM_FAULT_FALLBACK.
 * This will happen अगर there are any PTE entries within the PMD range
 * that we are requesting.
 *
 * We always favor PTE entries over PMD entries. There isn't a flow where we
 * evict PTE entries in order to 'upgrade' them to a PMD entry.  A PMD
 * insertion will fail अगर it finds any PTE entries alपढ़ोy in the tree, and a
 * PTE insertion will cause an existing PMD entry to be unmapped and
 * करोwngraded to PTE entries.  This happens क्रम both PMD zero pages as
 * well as PMD empty entries.
 *
 * The exception to this करोwngrade path is क्रम PMD entries that have
 * real storage backing them.  We will leave these real PMD entries in
 * the tree, and PTE ग_लिखोs will simply dirty the entire PMD entry.
 *
 * Note: Unlike filemap_fault() we करोn't honor FAULT_FLAG_RETRY flags. For
 * persistent memory the benefit is करोubtful. We can add that later अगर we can
 * show it helps.
 *
 * On error, this function करोes not वापस an ERR_PTR.  Instead it वापसs
 * a VM_FAULT code, encoded as an xarray पूर्णांकernal entry.  The ERR_PTR values
 * overlap with xarray value entries.
 */
अटल व्योम *grab_mapping_entry(काष्ठा xa_state *xas,
		काष्ठा address_space *mapping, अचिन्हित पूर्णांक order)
अणु
	अचिन्हित दीर्घ index = xas->xa_index;
	bool pmd_करोwngrade = false; /* splitting PMD entry पूर्णांकo PTE entries? */
	व्योम *entry;

retry:
	xas_lock_irq(xas);
	entry = get_unlocked_entry(xas, order);

	अगर (entry) अणु
		अगर (dax_is_conflict(entry))
			जाओ fallback;
		अगर (!xa_is_value(entry)) अणु
			xas_set_err(xas, -EIO);
			जाओ out_unlock;
		पूर्ण

		अगर (order == 0) अणु
			अगर (dax_is_pmd_entry(entry) &&
			    (dax_is_zero_entry(entry) ||
			     dax_is_empty_entry(entry))) अणु
				pmd_करोwngrade = true;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pmd_करोwngrade) अणु
		/*
		 * Make sure 'entry' reमुख्यs valid जबतक we drop
		 * the i_pages lock.
		 */
		dax_lock_entry(xas, entry);

		/*
		 * Besides huge zero pages the only other thing that माला_लो
		 * करोwngraded are empty entries which करोn't need to be
		 * unmapped.
		 */
		अगर (dax_is_zero_entry(entry)) अणु
			xas_unlock_irq(xas);
			unmap_mapping_pages(mapping,
					xas->xa_index & ~PG_PMD_COLOUR,
					PG_PMD_NR, false);
			xas_reset(xas);
			xas_lock_irq(xas);
		पूर्ण

		dax_disassociate_entry(entry, mapping, false);
		xas_store(xas, शून्य);	/* unकरो the PMD join */
		dax_wake_entry(xas, entry, WAKE_ALL);
		mapping->nrpages -= PG_PMD_NR;
		entry = शून्य;
		xas_set(xas, index);
	पूर्ण

	अगर (entry) अणु
		dax_lock_entry(xas, entry);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags = DAX_EMPTY;

		अगर (order > 0)
			flags |= DAX_PMD;
		entry = dax_make_entry(pfn_to_pfn_t(0), flags);
		dax_lock_entry(xas, entry);
		अगर (xas_error(xas))
			जाओ out_unlock;
		mapping->nrpages += 1UL << order;
	पूर्ण

out_unlock:
	xas_unlock_irq(xas);
	अगर (xas_nomem(xas, mapping_gfp_mask(mapping) & ~__GFP_HIGHMEM))
		जाओ retry;
	अगर (xas->xa_node == XA_ERROR(-ENOMEM))
		वापस xa_mk_पूर्णांकernal(VM_FAULT_OOM);
	अगर (xas_error(xas))
		वापस xa_mk_पूर्णांकernal(VM_FAULT_SIGBUS);
	वापस entry;
fallback:
	xas_unlock_irq(xas);
	वापस xa_mk_पूर्णांकernal(VM_FAULT_FALLBACK);
पूर्ण

/**
 * dax_layout_busy_page_range - find first pinned page in @mapping
 * @mapping: address space to scan क्रम a page with ref count > 1
 * @start: Starting offset. Page containing 'start' is included.
 * @end: End offset. Page containing 'end' is included. If 'end' is Lदीर्घ_उच्च,
 *       pages from 'start' till the end of file are included.
 *
 * DAX requires ZONE_DEVICE mapped pages. These pages are never
 * 'onlined' to the page allocator so they are considered idle when
 * page->count == 1. A fileप्रणाली uses this पूर्णांकerface to determine अगर
 * any page in the mapping is busy, i.e. क्रम DMA, or other
 * get_user_pages() usages.
 *
 * It is expected that the fileप्रणाली is holding locks to block the
 * establishment of new mappings in this address_space. I.e. it expects
 * to be able to run unmap_mapping_range() and subsequently not race
 * mapping_mapped() becoming true.
 */
काष्ठा page *dax_layout_busy_page_range(काष्ठा address_space *mapping,
					loff_t start, loff_t end)
अणु
	व्योम *entry;
	अचिन्हित पूर्णांक scanned = 0;
	काष्ठा page *page = शून्य;
	pgoff_t start_idx = start >> PAGE_SHIFT;
	pgoff_t end_idx;
	XA_STATE(xas, &mapping->i_pages, start_idx);

	/*
	 * In the 'limited' हाल get_user_pages() क्रम dax is disabled.
	 */
	अगर (IS_ENABLED(CONFIG_FS_DAX_LIMITED))
		वापस शून्य;

	अगर (!dax_mapping(mapping) || !mapping_mapped(mapping))
		वापस शून्य;

	/* If end == Lदीर्घ_उच्च, all pages from start to till end of file */
	अगर (end == Lदीर्घ_उच्च)
		end_idx = अच_दीर्घ_उच्च;
	अन्यथा
		end_idx = end >> PAGE_SHIFT;
	/*
	 * If we race get_user_pages_fast() here either we'll see the
	 * elevated page count in the iteration and रुको, or
	 * get_user_pages_fast() will see that the page it took a reference
	 * against is no दीर्घer mapped in the page tables and bail to the
	 * get_user_pages() slow path.  The slow path is रक्षित by
	 * pte_lock() and pmd_lock(). New references are not taken without
	 * holding those locks, and unmap_mapping_pages() will not zero the
	 * pte or pmd without holding the respective lock, so we are
	 * guaranteed to either see new references or prevent new
	 * references from being established.
	 */
	unmap_mapping_pages(mapping, start_idx, end_idx - start_idx + 1, 0);

	xas_lock_irq(&xas);
	xas_क्रम_each(&xas, entry, end_idx) अणु
		अगर (WARN_ON_ONCE(!xa_is_value(entry)))
			जारी;
		अगर (unlikely(dax_is_locked(entry)))
			entry = get_unlocked_entry(&xas, 0);
		अगर (entry)
			page = dax_busy_page(entry);
		put_unlocked_entry(&xas, entry, WAKE_NEXT);
		अगर (page)
			अवरोध;
		अगर (++scanned % XA_CHECK_SCHED)
			जारी;

		xas_छोड़ो(&xas);
		xas_unlock_irq(&xas);
		cond_resched();
		xas_lock_irq(&xas);
	पूर्ण
	xas_unlock_irq(&xas);
	वापस page;
पूर्ण
EXPORT_SYMBOL_GPL(dax_layout_busy_page_range);

काष्ठा page *dax_layout_busy_page(काष्ठा address_space *mapping)
अणु
	वापस dax_layout_busy_page_range(mapping, 0, Lदीर्घ_उच्च);
पूर्ण
EXPORT_SYMBOL_GPL(dax_layout_busy_page);

अटल पूर्णांक __dax_invalidate_entry(काष्ठा address_space *mapping,
					  pgoff_t index, bool trunc)
अणु
	XA_STATE(xas, &mapping->i_pages, index);
	पूर्णांक ret = 0;
	व्योम *entry;

	xas_lock_irq(&xas);
	entry = get_unlocked_entry(&xas, 0);
	अगर (!entry || WARN_ON_ONCE(!xa_is_value(entry)))
		जाओ out;
	अगर (!trunc &&
	    (xas_get_mark(&xas, PAGECACHE_TAG_सूचीTY) ||
	     xas_get_mark(&xas, PAGECACHE_TAG_TOWRITE)))
		जाओ out;
	dax_disassociate_entry(entry, mapping, trunc);
	xas_store(&xas, शून्य);
	mapping->nrpages -= 1UL << dax_entry_order(entry);
	ret = 1;
out:
	put_unlocked_entry(&xas, entry, WAKE_ALL);
	xas_unlock_irq(&xas);
	वापस ret;
पूर्ण

/*
 * Delete DAX entry at @index from @mapping.  Wait क्रम it
 * to be unlocked beक्रमe deleting it.
 */
पूर्णांक dax_delete_mapping_entry(काष्ठा address_space *mapping, pgoff_t index)
अणु
	पूर्णांक ret = __dax_invalidate_entry(mapping, index, true);

	/*
	 * This माला_लो called from truncate / punch_hole path. As such, the caller
	 * must hold locks protecting against concurrent modअगरications of the
	 * page cache (usually fs-निजी i_mmap_sem क्रम writing). Since the
	 * caller has seen a DAX entry क्रम this index, we better find it
	 * at that index as well...
	 */
	WARN_ON_ONCE(!ret);
	वापस ret;
पूर्ण

/*
 * Invalidate DAX entry अगर it is clean.
 */
पूर्णांक dax_invalidate_mapping_entry_sync(काष्ठा address_space *mapping,
				      pgoff_t index)
अणु
	वापस __dax_invalidate_entry(mapping, index, false);
पूर्ण

अटल पूर्णांक copy_cow_page_dax(काष्ठा block_device *bdev, काष्ठा dax_device *dax_dev,
			     sector_t sector, काष्ठा page *to, अचिन्हित दीर्घ vaddr)
अणु
	व्योम *vto, *kaddr;
	pgoff_t pgoff;
	दीर्घ rc;
	पूर्णांक id;

	rc = bdev_dax_pgoff(bdev, sector, PAGE_SIZE, &pgoff);
	अगर (rc)
		वापस rc;

	id = dax_पढ़ो_lock();
	rc = dax_direct_access(dax_dev, pgoff, PHYS_PFN(PAGE_SIZE), &kaddr, शून्य);
	अगर (rc < 0) अणु
		dax_पढ़ो_unlock(id);
		वापस rc;
	पूर्ण
	vto = kmap_atomic(to);
	copy_user_page(vto, (व्योम __क्रमce *)kaddr, vaddr, to);
	kunmap_atomic(vto);
	dax_पढ़ो_unlock(id);
	वापस 0;
पूर्ण

/*
 * By this poपूर्णांक grab_mapping_entry() has ensured that we have a locked entry
 * of the appropriate size so we करोn't have to worry about करोwngrading PMDs to
 * PTEs.  If we happen to be trying to insert a PTE and there is a PMD
 * alपढ़ोy in the tree, we will skip the insertion and just dirty the PMD as
 * appropriate.
 */
अटल व्योम *dax_insert_entry(काष्ठा xa_state *xas,
		काष्ठा address_space *mapping, काष्ठा vm_fault *vmf,
		व्योम *entry, pfn_t pfn, अचिन्हित दीर्घ flags, bool dirty)
अणु
	व्योम *new_entry = dax_make_entry(pfn, flags);

	अगर (dirty)
		__mark_inode_dirty(mapping->host, I_सूचीTY_PAGES);

	अगर (dax_is_zero_entry(entry) && !(flags & DAX_ZERO_PAGE)) अणु
		अचिन्हित दीर्घ index = xas->xa_index;
		/* we are replacing a zero page with block mapping */
		अगर (dax_is_pmd_entry(entry))
			unmap_mapping_pages(mapping, index & ~PG_PMD_COLOUR,
					PG_PMD_NR, false);
		अन्यथा /* pte entry */
			unmap_mapping_pages(mapping, index, 1, false);
	पूर्ण

	xas_reset(xas);
	xas_lock_irq(xas);
	अगर (dax_is_zero_entry(entry) || dax_is_empty_entry(entry)) अणु
		व्योम *old;

		dax_disassociate_entry(entry, mapping, false);
		dax_associate_entry(new_entry, mapping, vmf->vma, vmf->address);
		/*
		 * Only swap our new entry पूर्णांकo the page cache अगर the current
		 * entry is a zero page or an empty entry.  If a normal PTE or
		 * PMD entry is alपढ़ोy in the cache, we leave it alone.  This
		 * means that अगर we are trying to insert a PTE and the
		 * existing entry is a PMD, we will just leave the PMD in the
		 * tree and dirty it अगर necessary.
		 */
		old = dax_lock_entry(xas, new_entry);
		WARN_ON_ONCE(old != xa_mk_value(xa_to_value(entry) |
					DAX_LOCKED));
		entry = new_entry;
	पूर्ण अन्यथा अणु
		xas_load(xas);	/* Walk the xa_state */
	पूर्ण

	अगर (dirty)
		xas_set_mark(xas, PAGECACHE_TAG_सूचीTY);

	xas_unlock_irq(xas);
	वापस entry;
पूर्ण

अटल अंतरभूत
अचिन्हित दीर्घ pgoff_address(pgoff_t pgoff, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ address;

	address = vma->vm_start + ((pgoff - vma->vm_pgoff) << PAGE_SHIFT);
	VM_BUG_ON_VMA(address < vma->vm_start || address >= vma->vm_end, vma);
	वापस address;
पूर्ण

/* Walk all mappings of a given index of a file and ग_लिखोprotect them */
अटल व्योम dax_entry_mkclean(काष्ठा address_space *mapping, pgoff_t index,
		अचिन्हित दीर्घ pfn)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	pte_t pte, *ptep = शून्य;
	pmd_t *pmdp = शून्य;
	spinlock_t *ptl;

	i_mmap_lock_पढ़ो(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(vma, &mapping->i_mmap, index, index) अणु
		काष्ठा mmu_notअगरier_range range;
		अचिन्हित दीर्घ address;

		cond_resched();

		अगर (!(vma->vm_flags & VM_SHARED))
			जारी;

		address = pgoff_address(index, vma);

		/*
		 * follow_invalidate_pte() will use the range to call
		 * mmu_notअगरier_invalidate_range_start() on our behalf beक्रमe
		 * taking any lock.
		 */
		अगर (follow_invalidate_pte(vma->vm_mm, address, &range, &ptep,
					  &pmdp, &ptl))
			जारी;

		/*
		 * No need to call mmu_notअगरier_invalidate_range() as we are
		 * करोwngrading page table protection not changing it to poपूर्णांक
		 * to a new page.
		 *
		 * See Documentation/vm/mmu_notअगरier.rst
		 */
		अगर (pmdp) अणु
#अगर_घोषित CONFIG_FS_DAX_PMD
			pmd_t pmd;

			अगर (pfn != pmd_pfn(*pmdp))
				जाओ unlock_pmd;
			अगर (!pmd_dirty(*pmdp) && !pmd_ग_लिखो(*pmdp))
				जाओ unlock_pmd;

			flush_cache_page(vma, address, pfn);
			pmd = pmdp_invalidate(vma, address, pmdp);
			pmd = pmd_wrprotect(pmd);
			pmd = pmd_mkclean(pmd);
			set_pmd_at(vma->vm_mm, address, pmdp, pmd);
unlock_pmd:
#पूर्ण_अगर
			spin_unlock(ptl);
		पूर्ण अन्यथा अणु
			अगर (pfn != pte_pfn(*ptep))
				जाओ unlock_pte;
			अगर (!pte_dirty(*ptep) && !pte_ग_लिखो(*ptep))
				जाओ unlock_pte;

			flush_cache_page(vma, address, pfn);
			pte = ptep_clear_flush(vma, address, ptep);
			pte = pte_wrprotect(pte);
			pte = pte_mkclean(pte);
			set_pte_at(vma->vm_mm, address, ptep, pte);
unlock_pte:
			pte_unmap_unlock(ptep, ptl);
		पूर्ण

		mmu_notअगरier_invalidate_range_end(&range);
	पूर्ण
	i_mmap_unlock_पढ़ो(mapping);
पूर्ण

अटल पूर्णांक dax_ग_लिखोback_one(काष्ठा xa_state *xas, काष्ठा dax_device *dax_dev,
		काष्ठा address_space *mapping, व्योम *entry)
अणु
	अचिन्हित दीर्घ pfn, index, count;
	दीर्घ ret = 0;

	/*
	 * A page got tagged dirty in DAX mapping? Something is seriously
	 * wrong.
	 */
	अगर (WARN_ON(!xa_is_value(entry)))
		वापस -EIO;

	अगर (unlikely(dax_is_locked(entry))) अणु
		व्योम *old_entry = entry;

		entry = get_unlocked_entry(xas, 0);

		/* Entry got punched out / पुनः_स्मृतिated? */
		अगर (!entry || WARN_ON_ONCE(!xa_is_value(entry)))
			जाओ put_unlocked;
		/*
		 * Entry got पुनः_स्मृतिated अन्यथाwhere? No need to ग_लिखोback.
		 * We have to compare pfns as we must not bail out due to
		 * dअगरference in lockbit or entry type.
		 */
		अगर (dax_to_pfn(old_entry) != dax_to_pfn(entry))
			जाओ put_unlocked;
		अगर (WARN_ON_ONCE(dax_is_empty_entry(entry) ||
					dax_is_zero_entry(entry))) अणु
			ret = -EIO;
			जाओ put_unlocked;
		पूर्ण

		/* Another fsync thपढ़ो may have alपढ़ोy करोne this entry */
		अगर (!xas_get_mark(xas, PAGECACHE_TAG_TOWRITE))
			जाओ put_unlocked;
	पूर्ण

	/* Lock the entry to serialize with page faults */
	dax_lock_entry(xas, entry);

	/*
	 * We can clear the tag now but we have to be careful so that concurrent
	 * dax_ग_लिखोback_one() calls क्रम the same index cannot finish beक्रमe we
	 * actually flush the caches. This is achieved as the calls will look
	 * at the entry only under the i_pages lock and once they करो that
	 * they will see the entry locked and रुको क्रम it to unlock.
	 */
	xas_clear_mark(xas, PAGECACHE_TAG_TOWRITE);
	xas_unlock_irq(xas);

	/*
	 * If dax_ग_लिखोback_mapping_range() was given a wbc->range_start
	 * in the middle of a PMD, the 'index' we use needs to be
	 * aligned to the start of the PMD.
	 * This allows us to flush क्रम PMD_SIZE and not have to worry about
	 * partial PMD ग_लिखोbacks.
	 */
	pfn = dax_to_pfn(entry);
	count = 1UL << dax_entry_order(entry);
	index = xas->xa_index & ~(count - 1);

	dax_entry_mkclean(mapping, index, pfn);
	dax_flush(dax_dev, page_address(pfn_to_page(pfn)), count * PAGE_SIZE);
	/*
	 * After we have flushed the cache, we can clear the dirty tag. There
	 * cannot be new dirty data in the pfn after the flush has completed as
	 * the pfn mappings are ग_लिखोरक्षित and fault रुकोs क्रम mapping
	 * entry lock.
	 */
	xas_reset(xas);
	xas_lock_irq(xas);
	xas_store(xas, entry);
	xas_clear_mark(xas, PAGECACHE_TAG_सूचीTY);
	dax_wake_entry(xas, entry, WAKE_NEXT);

	trace_dax_ग_लिखोback_one(mapping->host, index, count);
	वापस ret;

 put_unlocked:
	put_unlocked_entry(xas, entry, WAKE_NEXT);
	वापस ret;
पूर्ण

/*
 * Flush the mapping to the persistent करोमुख्य within the byte range of [start,
 * end]. This is required by data पूर्णांकegrity operations to ensure file data is
 * on persistent storage prior to completion of the operation.
 */
पूर्णांक dax_ग_लिखोback_mapping_range(काष्ठा address_space *mapping,
		काष्ठा dax_device *dax_dev, काष्ठा ग_लिखोback_control *wbc)
अणु
	XA_STATE(xas, &mapping->i_pages, wbc->range_start >> PAGE_SHIFT);
	काष्ठा inode *inode = mapping->host;
	pgoff_t end_index = wbc->range_end >> PAGE_SHIFT;
	व्योम *entry;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक scanned = 0;

	अगर (WARN_ON_ONCE(inode->i_blkbits != PAGE_SHIFT))
		वापस -EIO;

	अगर (mapping_empty(mapping) || wbc->sync_mode != WB_SYNC_ALL)
		वापस 0;

	trace_dax_ग_लिखोback_range(inode, xas.xa_index, end_index);

	tag_pages_क्रम_ग_लिखोback(mapping, xas.xa_index, end_index);

	xas_lock_irq(&xas);
	xas_क्रम_each_marked(&xas, entry, end_index, PAGECACHE_TAG_TOWRITE) अणु
		ret = dax_ग_लिखोback_one(&xas, dax_dev, mapping, entry);
		अगर (ret < 0) अणु
			mapping_set_error(mapping, ret);
			अवरोध;
		पूर्ण
		अगर (++scanned % XA_CHECK_SCHED)
			जारी;

		xas_छोड़ो(&xas);
		xas_unlock_irq(&xas);
		cond_resched();
		xas_lock_irq(&xas);
	पूर्ण
	xas_unlock_irq(&xas);
	trace_dax_ग_लिखोback_range_करोne(inode, xas.xa_index, end_index);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dax_ग_लिखोback_mapping_range);

अटल sector_t dax_iomap_sector(काष्ठा iomap *iomap, loff_t pos)
अणु
	वापस (iomap->addr + (pos & PAGE_MASK) - iomap->offset) >> 9;
पूर्ण

अटल पूर्णांक dax_iomap_pfn(काष्ठा iomap *iomap, loff_t pos, माप_प्रकार size,
			 pfn_t *pfnp)
अणु
	स्थिर sector_t sector = dax_iomap_sector(iomap, pos);
	pgoff_t pgoff;
	पूर्णांक id, rc;
	दीर्घ length;

	rc = bdev_dax_pgoff(iomap->bdev, sector, size, &pgoff);
	अगर (rc)
		वापस rc;
	id = dax_पढ़ो_lock();
	length = dax_direct_access(iomap->dax_dev, pgoff, PHYS_PFN(size),
				   शून्य, pfnp);
	अगर (length < 0) अणु
		rc = length;
		जाओ out;
	पूर्ण
	rc = -EINVAL;
	अगर (PFN_PHYS(length) < size)
		जाओ out;
	अगर (pfn_t_to_pfn(*pfnp) & (PHYS_PFN(size)-1))
		जाओ out;
	/* For larger pages we need devmap */
	अगर (length > 1 && !pfn_t_devmap(*pfnp))
		जाओ out;
	rc = 0;
out:
	dax_पढ़ो_unlock(id);
	वापस rc;
पूर्ण

/*
 * The user has perक्रमmed a load from a hole in the file.  Allocating a new
 * page in the file would cause excessive storage usage क्रम workloads with
 * sparse files.  Instead we insert a पढ़ो-only mapping of the 4k zero page.
 * If this page is ever written to we will re-fault and change the mapping to
 * poपूर्णांक to real DAX storage instead.
 */
अटल vm_fault_t dax_load_hole(काष्ठा xa_state *xas,
		काष्ठा address_space *mapping, व्योम **entry,
		काष्ठा vm_fault *vmf)
अणु
	काष्ठा inode *inode = mapping->host;
	अचिन्हित दीर्घ vaddr = vmf->address;
	pfn_t pfn = pfn_to_pfn_t(my_zero_pfn(vaddr));
	vm_fault_t ret;

	*entry = dax_insert_entry(xas, mapping, vmf, *entry, pfn,
			DAX_ZERO_PAGE, false);

	ret = vmf_insert_mixed(vmf->vma, vaddr, pfn);
	trace_dax_load_hole(inode, vmf, ret);
	वापस ret;
पूर्ण

s64 dax_iomap_zero(loff_t pos, u64 length, काष्ठा iomap *iomap)
अणु
	sector_t sector = iomap_sector(iomap, pos & PAGE_MASK);
	pgoff_t pgoff;
	दीर्घ rc, id;
	व्योम *kaddr;
	bool page_aligned = false;
	अचिन्हित offset = offset_in_page(pos);
	अचिन्हित size = min_t(u64, PAGE_SIZE - offset, length);

	अगर (IS_ALIGNED(sector << SECTOR_SHIFT, PAGE_SIZE) &&
	    (size == PAGE_SIZE))
		page_aligned = true;

	rc = bdev_dax_pgoff(iomap->bdev, sector, PAGE_SIZE, &pgoff);
	अगर (rc)
		वापस rc;

	id = dax_पढ़ो_lock();

	अगर (page_aligned)
		rc = dax_zero_page_range(iomap->dax_dev, pgoff, 1);
	अन्यथा
		rc = dax_direct_access(iomap->dax_dev, pgoff, 1, &kaddr, शून्य);
	अगर (rc < 0) अणु
		dax_पढ़ो_unlock(id);
		वापस rc;
	पूर्ण

	अगर (!page_aligned) अणु
		स_रखो(kaddr + offset, 0, size);
		dax_flush(iomap->dax_dev, kaddr + offset, size);
	पूर्ण
	dax_पढ़ो_unlock(id);
	वापस size;
पूर्ण

अटल loff_t
dax_iomap_actor(काष्ठा inode *inode, loff_t pos, loff_t length, व्योम *data,
		काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	काष्ठा block_device *bdev = iomap->bdev;
	काष्ठा dax_device *dax_dev = iomap->dax_dev;
	काष्ठा iov_iter *iter = data;
	loff_t end = pos + length, करोne = 0;
	sमाप_प्रकार ret = 0;
	माप_प्रकार xfer;
	पूर्णांक id;

	अगर (iov_iter_rw(iter) == READ) अणु
		end = min(end, i_size_पढ़ो(inode));
		अगर (pos >= end)
			वापस 0;

		अगर (iomap->type == IOMAP_HOLE || iomap->type == IOMAP_UNWRITTEN)
			वापस iov_iter_zero(min(length, end - pos), iter);
	पूर्ण

	अगर (WARN_ON_ONCE(iomap->type != IOMAP_MAPPED))
		वापस -EIO;

	/*
	 * Write can allocate block क्रम an area which has a hole page mapped
	 * पूर्णांकo page tables. We have to tear करोwn these mappings so that data
	 * written by ग_लिखो(2) is visible in mmap.
	 */
	अगर (iomap->flags & IOMAP_F_NEW) अणु
		invalidate_inode_pages2_range(inode->i_mapping,
					      pos >> PAGE_SHIFT,
					      (end - 1) >> PAGE_SHIFT);
	पूर्ण

	id = dax_पढ़ो_lock();
	जबतक (pos < end) अणु
		अचिन्हित offset = pos & (PAGE_SIZE - 1);
		स्थिर माप_प्रकार size = ALIGN(length + offset, PAGE_SIZE);
		स्थिर sector_t sector = dax_iomap_sector(iomap, pos);
		sमाप_प्रकार map_len;
		pgoff_t pgoff;
		व्योम *kaddr;

		अगर (fatal_संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण

		ret = bdev_dax_pgoff(bdev, sector, size, &pgoff);
		अगर (ret)
			अवरोध;

		map_len = dax_direct_access(dax_dev, pgoff, PHYS_PFN(size),
				&kaddr, शून्य);
		अगर (map_len < 0) अणु
			ret = map_len;
			अवरोध;
		पूर्ण

		map_len = PFN_PHYS(map_len);
		kaddr += offset;
		map_len -= offset;
		अगर (map_len > end - pos)
			map_len = end - pos;

		/*
		 * The userspace address क्रम the memory copy has alपढ़ोy been
		 * validated via access_ok() in either vfs_पढ़ो() or
		 * vfs_ग_लिखो(), depending on which operation we are करोing.
		 */
		अगर (iov_iter_rw(iter) == WRITE)
			xfer = dax_copy_from_iter(dax_dev, pgoff, kaddr,
					map_len, iter);
		अन्यथा
			xfer = dax_copy_to_iter(dax_dev, pgoff, kaddr,
					map_len, iter);

		pos += xfer;
		length -= xfer;
		करोne += xfer;

		अगर (xfer == 0)
			ret = -EFAULT;
		अगर (xfer < map_len)
			अवरोध;
	पूर्ण
	dax_पढ़ो_unlock(id);

	वापस करोne ? करोne : ret;
पूर्ण

/**
 * dax_iomap_rw - Perक्रमm I/O to a DAX file
 * @iocb:	The control block क्रम this I/O
 * @iter:	The addresses to करो I/O from or to
 * @ops:	iomap ops passed from the file प्रणाली
 *
 * This function perक्रमms पढ़ो and ग_लिखो operations to directly mapped
 * persistent memory.  The callers needs to take care of पढ़ो/ग_लिखो exclusion
 * and evicting any page cache pages in the region under I/O.
 */
sमाप_प्रकार
dax_iomap_rw(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा address_space *mapping = iocb->ki_filp->f_mapping;
	काष्ठा inode *inode = mapping->host;
	loff_t pos = iocb->ki_pos, ret = 0, करोne = 0;
	अचिन्हित flags = 0;

	अगर (iov_iter_rw(iter) == WRITE) अणु
		lockdep_निश्चित_held_ग_लिखो(&inode->i_rwsem);
		flags |= IOMAP_WRITE;
	पूर्ण अन्यथा अणु
		lockdep_निश्चित_held(&inode->i_rwsem);
	पूर्ण

	अगर (iocb->ki_flags & IOCB_NOWAIT)
		flags |= IOMAP_NOWAIT;

	जबतक (iov_iter_count(iter)) अणु
		ret = iomap_apply(inode, pos, iov_iter_count(iter), flags, ops,
				iter, dax_iomap_actor);
		अगर (ret <= 0)
			अवरोध;
		pos += ret;
		करोne += ret;
	पूर्ण

	iocb->ki_pos += करोne;
	वापस करोne ? करोne : ret;
पूर्ण
EXPORT_SYMBOL_GPL(dax_iomap_rw);

अटल vm_fault_t dax_fault_वापस(पूर्णांक error)
अणु
	अगर (error == 0)
		वापस VM_FAULT_NOPAGE;
	वापस vmf_error(error);
पूर्ण

/*
 * MAP_SYNC on a dax mapping guarantees dirty metadata is
 * flushed on ग_लिखो-faults (non-cow), but not पढ़ो-faults.
 */
अटल bool dax_fault_is_synchronous(अचिन्हित दीर्घ flags,
		काष्ठा vm_area_काष्ठा *vma, काष्ठा iomap *iomap)
अणु
	वापस (flags & IOMAP_WRITE) && (vma->vm_flags & VM_SYNC)
		&& (iomap->flags & IOMAP_F_सूचीTY);
पूर्ण

अटल vm_fault_t dax_iomap_pte_fault(काष्ठा vm_fault *vmf, pfn_t *pfnp,
			       पूर्णांक *iomap_errp, स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा address_space *mapping = vma->vm_file->f_mapping;
	XA_STATE(xas, &mapping->i_pages, vmf->pgoff);
	काष्ठा inode *inode = mapping->host;
	अचिन्हित दीर्घ vaddr = vmf->address;
	loff_t pos = (loff_t)vmf->pgoff << PAGE_SHIFT;
	काष्ठा iomap iomap = अणु .type = IOMAP_HOLE पूर्ण;
	काष्ठा iomap srcmap = अणु .type = IOMAP_HOLE पूर्ण;
	अचिन्हित flags = IOMAP_FAULT;
	पूर्णांक error, major = 0;
	bool ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;
	bool sync;
	vm_fault_t ret = 0;
	व्योम *entry;
	pfn_t pfn;

	trace_dax_pte_fault(inode, vmf, ret);
	/*
	 * Check whether offset isn't beyond end of file now. Caller is supposed
	 * to hold locks serializing us with truncate / punch hole so this is
	 * a reliable test.
	 */
	अगर (pos >= i_size_पढ़ो(inode)) अणु
		ret = VM_FAULT_SIGBUS;
		जाओ out;
	पूर्ण

	अगर (ग_लिखो && !vmf->cow_page)
		flags |= IOMAP_WRITE;

	entry = grab_mapping_entry(&xas, mapping, 0);
	अगर (xa_is_पूर्णांकernal(entry)) अणु
		ret = xa_to_पूर्णांकernal(entry);
		जाओ out;
	पूर्ण

	/*
	 * It is possible, particularly with mixed पढ़ोs & ग_लिखोs to निजी
	 * mappings, that we have raced with a PMD fault that overlaps with
	 * the PTE we need to set up.  If so just वापस and the fault will be
	 * retried.
	 */
	अगर (pmd_trans_huge(*vmf->pmd) || pmd_devmap(*vmf->pmd)) अणु
		ret = VM_FAULT_NOPAGE;
		जाओ unlock_entry;
	पूर्ण

	/*
	 * Note that we करोn't bother to use iomap_apply here: DAX required
	 * the file प्रणाली block size to be equal the page size, which means
	 * that we never have to deal with more than a single extent here.
	 */
	error = ops->iomap_begin(inode, pos, PAGE_SIZE, flags, &iomap, &srcmap);
	अगर (iomap_errp)
		*iomap_errp = error;
	अगर (error) अणु
		ret = dax_fault_वापस(error);
		जाओ unlock_entry;
	पूर्ण
	अगर (WARN_ON_ONCE(iomap.offset + iomap.length < pos + PAGE_SIZE)) अणु
		error = -EIO;	/* fs corruption? */
		जाओ error_finish_iomap;
	पूर्ण

	अगर (vmf->cow_page) अणु
		sector_t sector = dax_iomap_sector(&iomap, pos);

		चयन (iomap.type) अणु
		हाल IOMAP_HOLE:
		हाल IOMAP_UNWRITTEN:
			clear_user_highpage(vmf->cow_page, vaddr);
			अवरोध;
		हाल IOMAP_MAPPED:
			error = copy_cow_page_dax(iomap.bdev, iomap.dax_dev,
						  sector, vmf->cow_page, vaddr);
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			error = -EIO;
			अवरोध;
		पूर्ण

		अगर (error)
			जाओ error_finish_iomap;

		__SetPageUptodate(vmf->cow_page);
		ret = finish_fault(vmf);
		अगर (!ret)
			ret = VM_FAULT_DONE_COW;
		जाओ finish_iomap;
	पूर्ण

	sync = dax_fault_is_synchronous(flags, vma, &iomap);

	चयन (iomap.type) अणु
	हाल IOMAP_MAPPED:
		अगर (iomap.flags & IOMAP_F_NEW) अणु
			count_vm_event(PGMAJFAULT);
			count_memcg_event_mm(vma->vm_mm, PGMAJFAULT);
			major = VM_FAULT_MAJOR;
		पूर्ण
		error = dax_iomap_pfn(&iomap, pos, PAGE_SIZE, &pfn);
		अगर (error < 0)
			जाओ error_finish_iomap;

		entry = dax_insert_entry(&xas, mapping, vmf, entry, pfn,
						 0, ग_लिखो && !sync);

		/*
		 * If we are करोing synchronous page fault and inode needs fsync,
		 * we can insert PTE पूर्णांकo page tables only after that happens.
		 * Skip insertion क्रम now and वापस the pfn so that caller can
		 * insert it after fsync is करोne.
		 */
		अगर (sync) अणु
			अगर (WARN_ON_ONCE(!pfnp)) अणु
				error = -EIO;
				जाओ error_finish_iomap;
			पूर्ण
			*pfnp = pfn;
			ret = VM_FAULT_NEEDDSYNC | major;
			जाओ finish_iomap;
		पूर्ण
		trace_dax_insert_mapping(inode, vmf, entry);
		अगर (ग_लिखो)
			ret = vmf_insert_mixed_mkग_लिखो(vma, vaddr, pfn);
		अन्यथा
			ret = vmf_insert_mixed(vma, vaddr, pfn);

		जाओ finish_iomap;
	हाल IOMAP_UNWRITTEN:
	हाल IOMAP_HOLE:
		अगर (!ग_लिखो) अणु
			ret = dax_load_hole(&xas, mapping, &entry, vmf);
			जाओ finish_iomap;
		पूर्ण
		fallthrough;
	शेष:
		WARN_ON_ONCE(1);
		error = -EIO;
		अवरोध;
	पूर्ण

 error_finish_iomap:
	ret = dax_fault_वापस(error);
 finish_iomap:
	अगर (ops->iomap_end) अणु
		पूर्णांक copied = PAGE_SIZE;

		अगर (ret & VM_FAULT_ERROR)
			copied = 0;
		/*
		 * The fault is करोne by now and there's no way back (other
		 * thपढ़ो may be alपढ़ोy happily using PTE we have installed).
		 * Just ignore error from ->iomap_end since we cannot करो much
		 * with it.
		 */
		ops->iomap_end(inode, pos, PAGE_SIZE, copied, flags, &iomap);
	पूर्ण
 unlock_entry:
	dax_unlock_entry(&xas, entry);
 out:
	trace_dax_pte_fault_करोne(inode, vmf, ret);
	वापस ret | major;
पूर्ण

#अगर_घोषित CONFIG_FS_DAX_PMD
अटल vm_fault_t dax_pmd_load_hole(काष्ठा xa_state *xas, काष्ठा vm_fault *vmf,
		काष्ठा iomap *iomap, व्योम **entry)
अणु
	काष्ठा address_space *mapping = vmf->vma->vm_file->f_mapping;
	अचिन्हित दीर्घ pmd_addr = vmf->address & PMD_MASK;
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा inode *inode = mapping->host;
	pgtable_t pgtable = शून्य;
	काष्ठा page *zero_page;
	spinlock_t *ptl;
	pmd_t pmd_entry;
	pfn_t pfn;

	zero_page = mm_get_huge_zero_page(vmf->vma->vm_mm);

	अगर (unlikely(!zero_page))
		जाओ fallback;

	pfn = page_to_pfn_t(zero_page);
	*entry = dax_insert_entry(xas, mapping, vmf, *entry, pfn,
			DAX_PMD | DAX_ZERO_PAGE, false);

	अगर (arch_needs_pgtable_deposit()) अणु
		pgtable = pte_alloc_one(vma->vm_mm);
		अगर (!pgtable)
			वापस VM_FAULT_OOM;
	पूर्ण

	ptl = pmd_lock(vmf->vma->vm_mm, vmf->pmd);
	अगर (!pmd_none(*(vmf->pmd))) अणु
		spin_unlock(ptl);
		जाओ fallback;
	पूर्ण

	अगर (pgtable) अणु
		pgtable_trans_huge_deposit(vma->vm_mm, vmf->pmd, pgtable);
		mm_inc_nr_ptes(vma->vm_mm);
	पूर्ण
	pmd_entry = mk_pmd(zero_page, vmf->vma->vm_page_prot);
	pmd_entry = pmd_mkhuge(pmd_entry);
	set_pmd_at(vmf->vma->vm_mm, pmd_addr, vmf->pmd, pmd_entry);
	spin_unlock(ptl);
	trace_dax_pmd_load_hole(inode, vmf, zero_page, *entry);
	वापस VM_FAULT_NOPAGE;

fallback:
	अगर (pgtable)
		pte_मुक्त(vma->vm_mm, pgtable);
	trace_dax_pmd_load_hole_fallback(inode, vmf, zero_page, *entry);
	वापस VM_FAULT_FALLBACK;
पूर्ण

अटल vm_fault_t dax_iomap_pmd_fault(काष्ठा vm_fault *vmf, pfn_t *pfnp,
			       स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा address_space *mapping = vma->vm_file->f_mapping;
	XA_STATE_ORDER(xas, &mapping->i_pages, vmf->pgoff, PMD_ORDER);
	अचिन्हित दीर्घ pmd_addr = vmf->address & PMD_MASK;
	bool ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;
	bool sync;
	अचिन्हित पूर्णांक iomap_flags = (ग_लिखो ? IOMAP_WRITE : 0) | IOMAP_FAULT;
	काष्ठा inode *inode = mapping->host;
	vm_fault_t result = VM_FAULT_FALLBACK;
	काष्ठा iomap iomap = अणु .type = IOMAP_HOLE पूर्ण;
	काष्ठा iomap srcmap = अणु .type = IOMAP_HOLE पूर्ण;
	pgoff_t max_pgoff;
	व्योम *entry;
	loff_t pos;
	पूर्णांक error;
	pfn_t pfn;

	/*
	 * Check whether offset isn't beyond end of file now. Caller is
	 * supposed to hold locks serializing us with truncate / punch hole so
	 * this is a reliable test.
	 */
	max_pgoff = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);

	trace_dax_pmd_fault(inode, vmf, max_pgoff, 0);

	/*
	 * Make sure that the faulting address's PMD offset (color) matches
	 * the PMD offset from the start of the file.  This is necessary so
	 * that a PMD range in the page table overlaps exactly with a PMD
	 * range in the page cache.
	 */
	अगर ((vmf->pgoff & PG_PMD_COLOUR) !=
	    ((vmf->address >> PAGE_SHIFT) & PG_PMD_COLOUR))
		जाओ fallback;

	/* Fall back to PTEs अगर we're going to COW */
	अगर (ग_लिखो && !(vma->vm_flags & VM_SHARED))
		जाओ fallback;

	/* If the PMD would extend outside the VMA */
	अगर (pmd_addr < vma->vm_start)
		जाओ fallback;
	अगर ((pmd_addr + PMD_SIZE) > vma->vm_end)
		जाओ fallback;

	अगर (xas.xa_index >= max_pgoff) अणु
		result = VM_FAULT_SIGBUS;
		जाओ out;
	पूर्ण

	/* If the PMD would extend beyond the file size */
	अगर ((xas.xa_index | PG_PMD_COLOUR) >= max_pgoff)
		जाओ fallback;

	/*
	 * grab_mapping_entry() will make sure we get an empty PMD entry,
	 * a zero PMD entry or a DAX PMD.  If it can't (because a PTE
	 * entry is alपढ़ोy in the array, क्रम instance), it will वापस
	 * VM_FAULT_FALLBACK.
	 */
	entry = grab_mapping_entry(&xas, mapping, PMD_ORDER);
	अगर (xa_is_पूर्णांकernal(entry)) अणु
		result = xa_to_पूर्णांकernal(entry);
		जाओ fallback;
	पूर्ण

	/*
	 * It is possible, particularly with mixed पढ़ोs & ग_लिखोs to निजी
	 * mappings, that we have raced with a PTE fault that overlaps with
	 * the PMD we need to set up.  If so just वापस and the fault will be
	 * retried.
	 */
	अगर (!pmd_none(*vmf->pmd) && !pmd_trans_huge(*vmf->pmd) &&
			!pmd_devmap(*vmf->pmd)) अणु
		result = 0;
		जाओ unlock_entry;
	पूर्ण

	/*
	 * Note that we करोn't use iomap_apply here.  We aren't करोing I/O, only
	 * setting up a mapping, so really we're using iomap_begin() as a way
	 * to look up our fileप्रणाली block.
	 */
	pos = (loff_t)xas.xa_index << PAGE_SHIFT;
	error = ops->iomap_begin(inode, pos, PMD_SIZE, iomap_flags, &iomap,
			&srcmap);
	अगर (error)
		जाओ unlock_entry;

	अगर (iomap.offset + iomap.length < pos + PMD_SIZE)
		जाओ finish_iomap;

	sync = dax_fault_is_synchronous(iomap_flags, vma, &iomap);

	चयन (iomap.type) अणु
	हाल IOMAP_MAPPED:
		error = dax_iomap_pfn(&iomap, pos, PMD_SIZE, &pfn);
		अगर (error < 0)
			जाओ finish_iomap;

		entry = dax_insert_entry(&xas, mapping, vmf, entry, pfn,
						DAX_PMD, ग_लिखो && !sync);

		/*
		 * If we are करोing synchronous page fault and inode needs fsync,
		 * we can insert PMD पूर्णांकo page tables only after that happens.
		 * Skip insertion क्रम now and वापस the pfn so that caller can
		 * insert it after fsync is करोne.
		 */
		अगर (sync) अणु
			अगर (WARN_ON_ONCE(!pfnp))
				जाओ finish_iomap;
			*pfnp = pfn;
			result = VM_FAULT_NEEDDSYNC;
			जाओ finish_iomap;
		पूर्ण

		trace_dax_pmd_insert_mapping(inode, vmf, PMD_SIZE, pfn, entry);
		result = vmf_insert_pfn_pmd(vmf, pfn, ग_लिखो);
		अवरोध;
	हाल IOMAP_UNWRITTEN:
	हाल IOMAP_HOLE:
		अगर (WARN_ON_ONCE(ग_लिखो))
			अवरोध;
		result = dax_pmd_load_hole(&xas, vmf, &iomap, &entry);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

 finish_iomap:
	अगर (ops->iomap_end) अणु
		पूर्णांक copied = PMD_SIZE;

		अगर (result == VM_FAULT_FALLBACK)
			copied = 0;
		/*
		 * The fault is करोne by now and there's no way back (other
		 * thपढ़ो may be alपढ़ोy happily using PMD we have installed).
		 * Just ignore error from ->iomap_end since we cannot करो much
		 * with it.
		 */
		ops->iomap_end(inode, pos, PMD_SIZE, copied, iomap_flags,
				&iomap);
	पूर्ण
 unlock_entry:
	dax_unlock_entry(&xas, entry);
 fallback:
	अगर (result == VM_FAULT_FALLBACK) अणु
		split_huge_pmd(vma, vmf->pmd, vmf->address);
		count_vm_event(THP_FAULT_FALLBACK);
	पूर्ण
out:
	trace_dax_pmd_fault_करोne(inode, vmf, max_pgoff, result);
	वापस result;
पूर्ण
#अन्यथा
अटल vm_fault_t dax_iomap_pmd_fault(काष्ठा vm_fault *vmf, pfn_t *pfnp,
			       स्थिर काष्ठा iomap_ops *ops)
अणु
	वापस VM_FAULT_FALLBACK;
पूर्ण
#पूर्ण_अगर /* CONFIG_FS_DAX_PMD */

/**
 * dax_iomap_fault - handle a page fault on a DAX file
 * @vmf: The description of the fault
 * @pe_size: Size of the page to fault in
 * @pfnp: PFN to insert क्रम synchronous faults अगर fsync is required
 * @iomap_errp: Storage क्रम detailed error code in हाल of error
 * @ops: Iomap ops passed from the file प्रणाली
 *
 * When a page fault occurs, fileप्रणालीs may call this helper in
 * their fault handler क्रम DAX files. dax_iomap_fault() assumes the caller
 * has करोne all the necessary locking क्रम page fault to proceed
 * successfully.
 */
vm_fault_t dax_iomap_fault(काष्ठा vm_fault *vmf, क्रमागत page_entry_size pe_size,
		    pfn_t *pfnp, पूर्णांक *iomap_errp, स्थिर काष्ठा iomap_ops *ops)
अणु
	चयन (pe_size) अणु
	हाल PE_SIZE_PTE:
		वापस dax_iomap_pte_fault(vmf, pfnp, iomap_errp, ops);
	हाल PE_SIZE_PMD:
		वापस dax_iomap_pmd_fault(vmf, pfnp, ops);
	शेष:
		वापस VM_FAULT_FALLBACK;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dax_iomap_fault);

/*
 * dax_insert_pfn_mkग_लिखो - insert PTE or PMD entry पूर्णांकo page tables
 * @vmf: The description of the fault
 * @pfn: PFN to insert
 * @order: Order of entry to insert.
 *
 * This function inserts a ग_लिखोable PTE or PMD entry पूर्णांकo the page tables
 * क्रम an mmaped DAX file.  It also marks the page cache entry as dirty.
 */
अटल vm_fault_t
dax_insert_pfn_mkग_लिखो(काष्ठा vm_fault *vmf, pfn_t pfn, अचिन्हित पूर्णांक order)
अणु
	काष्ठा address_space *mapping = vmf->vma->vm_file->f_mapping;
	XA_STATE_ORDER(xas, &mapping->i_pages, vmf->pgoff, order);
	व्योम *entry;
	vm_fault_t ret;

	xas_lock_irq(&xas);
	entry = get_unlocked_entry(&xas, order);
	/* Did we race with someone splitting entry or so? */
	अगर (!entry || dax_is_conflict(entry) ||
	    (order == 0 && !dax_is_pte_entry(entry))) अणु
		put_unlocked_entry(&xas, entry, WAKE_NEXT);
		xas_unlock_irq(&xas);
		trace_dax_insert_pfn_mkग_लिखो_no_entry(mapping->host, vmf,
						      VM_FAULT_NOPAGE);
		वापस VM_FAULT_NOPAGE;
	पूर्ण
	xas_set_mark(&xas, PAGECACHE_TAG_सूचीTY);
	dax_lock_entry(&xas, entry);
	xas_unlock_irq(&xas);
	अगर (order == 0)
		ret = vmf_insert_mixed_mkग_लिखो(vmf->vma, vmf->address, pfn);
#अगर_घोषित CONFIG_FS_DAX_PMD
	अन्यथा अगर (order == PMD_ORDER)
		ret = vmf_insert_pfn_pmd(vmf, pfn, FAULT_FLAG_WRITE);
#पूर्ण_अगर
	अन्यथा
		ret = VM_FAULT_FALLBACK;
	dax_unlock_entry(&xas, entry);
	trace_dax_insert_pfn_mkग_लिखो(mapping->host, vmf, ret);
	वापस ret;
पूर्ण

/**
 * dax_finish_sync_fault - finish synchronous page fault
 * @vmf: The description of the fault
 * @pe_size: Size of entry to be inserted
 * @pfn: PFN to insert
 *
 * This function ensures that the file range touched by the page fault is
 * stored persistently on the media and handles inserting of appropriate page
 * table entry.
 */
vm_fault_t dax_finish_sync_fault(काष्ठा vm_fault *vmf,
		क्रमागत page_entry_size pe_size, pfn_t pfn)
अणु
	पूर्णांक err;
	loff_t start = ((loff_t)vmf->pgoff) << PAGE_SHIFT;
	अचिन्हित पूर्णांक order = pe_order(pe_size);
	माप_प्रकार len = PAGE_SIZE << order;

	err = vfs_fsync_range(vmf->vma->vm_file, start, start + len - 1, 1);
	अगर (err)
		वापस VM_FAULT_SIGBUS;
	वापस dax_insert_pfn_mkग_लिखो(vmf, pfn, order);
पूर्ण
EXPORT_SYMBOL_GPL(dax_finish_sync_fault);
