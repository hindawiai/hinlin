<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Memory Migration functionality - linux/mm/migrate.c
 *
 * Copyright (C) 2006 Silicon Graphics, Inc., Christoph Lameter
 *
 * Page migration was first developed in the context of the memory hotplug
 * project. The मुख्य authors of the migration code are:
 *
 * IWAMOTO Toshihiro <iwamoto@valinux.co.jp>
 * Hirokazu Takahashi <taka@valinux.co.jp>
 * Dave Hansen <haveblue@us.ibm.com>
 * Christoph Lameter
 */

#समावेश <linux/migrate.h>
#समावेश <linux/export.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/ksm.h>
#समावेश <linux/rmap.h>
#समावेश <linux/topology.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/security.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/compaction.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/compat.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/hugetlb_cgroup.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pagewalk.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/memremap.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/balloon_compaction.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/page_idle.h>
#समावेश <linux/page_owner.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/oom.h>

#समावेश <यंत्र/tlbflush.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/migrate.h>

#समावेश "internal.h"

पूर्णांक isolate_movable_page(काष्ठा page *page, isolate_mode_t mode)
अणु
	काष्ठा address_space *mapping;

	/*
	 * Aव्योम burning cycles with pages that are yet under __मुक्त_pages(),
	 * or just got मुक्तd under us.
	 *
	 * In हाल we 'win' a race क्रम a movable page being मुक्तd under us and
	 * उठाओ its refcount preventing __मुक्त_pages() from करोing its job
	 * the put_page() at the end of this block will take care of
	 * release this page, thus aव्योमing a nasty leakage.
	 */
	अगर (unlikely(!get_page_unless_zero(page)))
		जाओ out;

	/*
	 * Check PageMovable beक्रमe holding a PG_lock because page's owner
	 * assumes anybody करोesn't touch PG_lock of newly allocated page
	 * so unconditionally grabbing the lock ruins page's owner side.
	 */
	अगर (unlikely(!__PageMovable(page)))
		जाओ out_putpage;
	/*
	 * As movable pages are not isolated from LRU lists, concurrent
	 * compaction thपढ़ोs can race against page migration functions
	 * as well as race against the releasing a page.
	 *
	 * In order to aव्योम having an alपढ़ोy isolated movable page
	 * being (wrongly) re-isolated जबतक it is under migration,
	 * or to aव्योम attempting to isolate pages being released,
	 * lets be sure we have the page lock
	 * beक्रमe proceeding with the movable page isolation steps.
	 */
	अगर (unlikely(!trylock_page(page)))
		जाओ out_putpage;

	अगर (!PageMovable(page) || PageIsolated(page))
		जाओ out_no_isolated;

	mapping = page_mapping(page);
	VM_BUG_ON_PAGE(!mapping, page);

	अगर (!mapping->a_ops->isolate_page(page, mode))
		जाओ out_no_isolated;

	/* Driver shouldn't use PG_isolated bit of page->flags */
	WARN_ON_ONCE(PageIsolated(page));
	__SetPageIsolated(page);
	unlock_page(page);

	वापस 0;

out_no_isolated:
	unlock_page(page);
out_putpage:
	put_page(page);
out:
	वापस -EBUSY;
पूर्ण

अटल व्योम putback_movable_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;

	mapping = page_mapping(page);
	mapping->a_ops->putback_page(page);
	__ClearPageIsolated(page);
पूर्ण

/*
 * Put previously isolated pages back onto the appropriate lists
 * from where they were once taken off क्रम compaction/migration.
 *
 * This function shall be used whenever the isolated pageset has been
 * built from lru, balloon, hugetlbfs page. See isolate_migratepages_range()
 * and isolate_huge_page().
 */
व्योम putback_movable_pages(काष्ठा list_head *l)
अणु
	काष्ठा page *page;
	काष्ठा page *page2;

	list_क्रम_each_entry_safe(page, page2, l, lru) अणु
		अगर (unlikely(PageHuge(page))) अणु
			putback_active_hugepage(page);
			जारी;
		पूर्ण
		list_del(&page->lru);
		/*
		 * We isolated non-lru movable page so here we can use
		 * __PageMovable because LRU page's mapping cannot have
		 * PAGE_MAPPING_MOVABLE.
		 */
		अगर (unlikely(__PageMovable(page))) अणु
			VM_BUG_ON_PAGE(!PageIsolated(page), page);
			lock_page(page);
			अगर (PageMovable(page))
				putback_movable_page(page);
			अन्यथा
				__ClearPageIsolated(page);
			unlock_page(page);
			put_page(page);
		पूर्ण अन्यथा अणु
			mod_node_page_state(page_pgdat(page), NR_ISOLATED_ANON +
					page_is_file_lru(page), -thp_nr_pages(page));
			putback_lru_page(page);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Restore a potential migration pte to a working pte entry
 */
अटल bool हटाओ_migration_pte(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ addr, व्योम *old)
अणु
	काष्ठा page_vma_mapped_walk pvmw = अणु
		.page = old,
		.vma = vma,
		.address = addr,
		.flags = PVMW_SYNC | PVMW_MIGRATION,
	पूर्ण;
	काष्ठा page *new;
	pte_t pte;
	swp_entry_t entry;

	VM_BUG_ON_PAGE(PageTail(page), page);
	जबतक (page_vma_mapped_walk(&pvmw)) अणु
		अगर (PageKsm(page))
			new = page;
		अन्यथा
			new = page - pvmw.page->index +
				linear_page_index(vma, pvmw.address);

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
		/* PMD-mapped THP migration entry */
		अगर (!pvmw.pte) अणु
			VM_BUG_ON_PAGE(PageHuge(page) || !PageTransCompound(page), page);
			हटाओ_migration_pmd(&pvmw, new);
			जारी;
		पूर्ण
#पूर्ण_अगर

		get_page(new);
		pte = pte_mkold(mk_pte(new, READ_ONCE(vma->vm_page_prot)));
		अगर (pte_swp_soft_dirty(*pvmw.pte))
			pte = pte_mksoft_dirty(pte);

		/*
		 * Recheck VMA as permissions can change since migration started
		 */
		entry = pte_to_swp_entry(*pvmw.pte);
		अगर (is_ग_लिखो_migration_entry(entry))
			pte = maybe_mkग_लिखो(pte, vma);
		अन्यथा अगर (pte_swp_uffd_wp(*pvmw.pte))
			pte = pte_mkuffd_wp(pte);

		अगर (unlikely(is_device_निजी_page(new))) अणु
			entry = make_device_निजी_entry(new, pte_ग_लिखो(pte));
			pte = swp_entry_to_pte(entry);
			अगर (pte_swp_soft_dirty(*pvmw.pte))
				pte = pte_swp_mksoft_dirty(pte);
			अगर (pte_swp_uffd_wp(*pvmw.pte))
				pte = pte_swp_mkuffd_wp(pte);
		पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
		अगर (PageHuge(new)) अणु
			pte = pte_mkhuge(pte);
			pte = arch_make_huge_pte(pte, vma, new, 0);
			set_huge_pte_at(vma->vm_mm, pvmw.address, pvmw.pte, pte);
			अगर (PageAnon(new))
				hugepage_add_anon_rmap(new, vma, pvmw.address);
			अन्यथा
				page_dup_rmap(new, true);
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			set_pte_at(vma->vm_mm, pvmw.address, pvmw.pte, pte);

			अगर (PageAnon(new))
				page_add_anon_rmap(new, vma, pvmw.address, false);
			अन्यथा
				page_add_file_rmap(new, false);
		पूर्ण
		अगर (vma->vm_flags & VM_LOCKED && !PageTransCompound(new))
			mlock_vma_page(new);

		अगर (PageTransHuge(page) && PageMlocked(page))
			clear_page_mlock(page);

		/* No need to invalidate - it was non-present beक्रमe */
		update_mmu_cache(vma, pvmw.address, pvmw.pte);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Get rid of all migration entries and replace them by
 * references to the indicated page.
 */
व्योम हटाओ_migration_ptes(काष्ठा page *old, काष्ठा page *new, bool locked)
अणु
	काष्ठा rmap_walk_control rwc = अणु
		.rmap_one = हटाओ_migration_pte,
		.arg = old,
	पूर्ण;

	अगर (locked)
		rmap_walk_locked(new, &rwc);
	अन्यथा
		rmap_walk(new, &rwc);
पूर्ण

/*
 * Something used the pte of a page under migration. We need to
 * get to the page and रुको until migration is finished.
 * When we वापस from this function the fault will be retried.
 */
व्योम __migration_entry_रुको(काष्ठा mm_काष्ठा *mm, pte_t *ptep,
				spinlock_t *ptl)
अणु
	pte_t pte;
	swp_entry_t entry;
	काष्ठा page *page;

	spin_lock(ptl);
	pte = *ptep;
	अगर (!is_swap_pte(pte))
		जाओ out;

	entry = pte_to_swp_entry(pte);
	अगर (!is_migration_entry(entry))
		जाओ out;

	page = migration_entry_to_page(entry);
	page = compound_head(page);

	/*
	 * Once page cache replacement of page migration started, page_count
	 * is zero; but we must not call put_and_रुको_on_page_locked() without
	 * a ref. Use get_page_unless_zero(), and just fault again अगर it fails.
	 */
	अगर (!get_page_unless_zero(page))
		जाओ out;
	pte_unmap_unlock(ptep, ptl);
	put_and_रुको_on_page_locked(page, TASK_UNINTERRUPTIBLE);
	वापस;
out:
	pte_unmap_unlock(ptep, ptl);
पूर्ण

व्योम migration_entry_रुको(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				अचिन्हित दीर्घ address)
अणु
	spinlock_t *ptl = pte_lockptr(mm, pmd);
	pte_t *ptep = pte_offset_map(pmd, address);
	__migration_entry_रुको(mm, ptep, ptl);
पूर्ण

व्योम migration_entry_रुको_huge(काष्ठा vm_area_काष्ठा *vma,
		काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	spinlock_t *ptl = huge_pte_lockptr(hstate_vma(vma), mm, pte);
	__migration_entry_रुको(mm, pte, ptl);
पूर्ण

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
व्योम pmd_migration_entry_रुको(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	spinlock_t *ptl;
	काष्ठा page *page;

	ptl = pmd_lock(mm, pmd);
	अगर (!is_pmd_migration_entry(*pmd))
		जाओ unlock;
	page = migration_entry_to_page(pmd_to_swp_entry(*pmd));
	अगर (!get_page_unless_zero(page))
		जाओ unlock;
	spin_unlock(ptl);
	put_and_रुको_on_page_locked(page, TASK_UNINTERRUPTIBLE);
	वापस;
unlock:
	spin_unlock(ptl);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक expected_page_refs(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	पूर्णांक expected_count = 1;

	/*
	 * Device निजी pages have an extra refcount as they are
	 * ZONE_DEVICE pages.
	 */
	expected_count += is_device_निजी_page(page);
	अगर (mapping)
		expected_count += thp_nr_pages(page) + page_has_निजी(page);

	वापस expected_count;
पूर्ण

/*
 * Replace the page in the mapping.
 *
 * The number of reमुख्यing references must be:
 * 1 क्रम anonymous pages without a mapping
 * 2 क्रम pages with a mapping
 * 3 क्रम pages with a mapping and PagePrivate/PagePrivate2 set.
 */
पूर्णांक migrate_page_move_mapping(काष्ठा address_space *mapping,
		काष्ठा page *newpage, काष्ठा page *page, पूर्णांक extra_count)
अणु
	XA_STATE(xas, &mapping->i_pages, page_index(page));
	काष्ठा zone *oldzone, *newzone;
	पूर्णांक dirty;
	पूर्णांक expected_count = expected_page_refs(mapping, page) + extra_count;
	पूर्णांक nr = thp_nr_pages(page);

	अगर (!mapping) अणु
		/* Anonymous page without mapping */
		अगर (page_count(page) != expected_count)
			वापस -EAGAIN;

		/* No turning back from here */
		newpage->index = page->index;
		newpage->mapping = page->mapping;
		अगर (PageSwapBacked(page))
			__SetPageSwapBacked(newpage);

		वापस MIGRATEPAGE_SUCCESS;
	पूर्ण

	oldzone = page_zone(page);
	newzone = page_zone(newpage);

	xas_lock_irq(&xas);
	अगर (page_count(page) != expected_count || xas_load(&xas) != page) अणु
		xas_unlock_irq(&xas);
		वापस -EAGAIN;
	पूर्ण

	अगर (!page_ref_मुक्तze(page, expected_count)) अणु
		xas_unlock_irq(&xas);
		वापस -EAGAIN;
	पूर्ण

	/*
	 * Now we know that no one अन्यथा is looking at the page:
	 * no turning back from here.
	 */
	newpage->index = page->index;
	newpage->mapping = page->mapping;
	page_ref_add(newpage, nr); /* add cache reference */
	अगर (PageSwapBacked(page)) अणु
		__SetPageSwapBacked(newpage);
		अगर (PageSwapCache(page)) अणु
			SetPageSwapCache(newpage);
			set_page_निजी(newpage, page_निजी(page));
		पूर्ण
	पूर्ण अन्यथा अणु
		VM_BUG_ON_PAGE(PageSwapCache(page), page);
	पूर्ण

	/* Move dirty जबतक page refs frozen and newpage not yet exposed */
	dirty = PageDirty(page);
	अगर (dirty) अणु
		ClearPageDirty(page);
		SetPageDirty(newpage);
	पूर्ण

	xas_store(&xas, newpage);
	अगर (PageTransHuge(page)) अणु
		पूर्णांक i;

		क्रम (i = 1; i < nr; i++) अणु
			xas_next(&xas);
			xas_store(&xas, newpage);
		पूर्ण
	पूर्ण

	/*
	 * Drop cache reference from old page by unमुक्तzing
	 * to one less reference.
	 * We know this isn't the last reference.
	 */
	page_ref_unमुक्तze(page, expected_count - nr);

	xas_unlock(&xas);
	/* Leave irq disabled to prevent preemption जबतक updating stats */

	/*
	 * If moved to a dअगरferent zone then also account
	 * the page क्रम that zone. Other VM counters will be
	 * taken care of when we establish references to the
	 * new page and drop references to the old page.
	 *
	 * Note that anonymous pages are accounted क्रम
	 * via NR_खाता_PAGES and NR_ANON_MAPPED अगर they
	 * are mapped to swap space.
	 */
	अगर (newzone != oldzone) अणु
		काष्ठा lruvec *old_lruvec, *new_lruvec;
		काष्ठा mem_cgroup *memcg;

		memcg = page_memcg(page);
		old_lruvec = mem_cgroup_lruvec(memcg, oldzone->zone_pgdat);
		new_lruvec = mem_cgroup_lruvec(memcg, newzone->zone_pgdat);

		__mod_lruvec_state(old_lruvec, NR_खाता_PAGES, -nr);
		__mod_lruvec_state(new_lruvec, NR_खाता_PAGES, nr);
		अगर (PageSwapBacked(page) && !PageSwapCache(page)) अणु
			__mod_lruvec_state(old_lruvec, NR_SHMEM, -nr);
			__mod_lruvec_state(new_lruvec, NR_SHMEM, nr);
		पूर्ण
#अगर_घोषित CONFIG_SWAP
		अगर (PageSwapCache(page)) अणु
			__mod_lruvec_state(old_lruvec, NR_SWAPCACHE, -nr);
			__mod_lruvec_state(new_lruvec, NR_SWAPCACHE, nr);
		पूर्ण
#पूर्ण_अगर
		अगर (dirty && mapping_can_ग_लिखोback(mapping)) अणु
			__mod_lruvec_state(old_lruvec, NR_खाता_सूचीTY, -nr);
			__mod_zone_page_state(oldzone, NR_ZONE_WRITE_PENDING, -nr);
			__mod_lruvec_state(new_lruvec, NR_खाता_सूचीTY, nr);
			__mod_zone_page_state(newzone, NR_ZONE_WRITE_PENDING, nr);
		पूर्ण
	पूर्ण
	local_irq_enable();

	वापस MIGRATEPAGE_SUCCESS;
पूर्ण
EXPORT_SYMBOL(migrate_page_move_mapping);

/*
 * The expected number of reमुख्यing references is the same as that
 * of migrate_page_move_mapping().
 */
पूर्णांक migrate_huge_page_move_mapping(काष्ठा address_space *mapping,
				   काष्ठा page *newpage, काष्ठा page *page)
अणु
	XA_STATE(xas, &mapping->i_pages, page_index(page));
	पूर्णांक expected_count;

	xas_lock_irq(&xas);
	expected_count = 2 + page_has_निजी(page);
	अगर (page_count(page) != expected_count || xas_load(&xas) != page) अणु
		xas_unlock_irq(&xas);
		वापस -EAGAIN;
	पूर्ण

	अगर (!page_ref_मुक्तze(page, expected_count)) अणु
		xas_unlock_irq(&xas);
		वापस -EAGAIN;
	पूर्ण

	newpage->index = page->index;
	newpage->mapping = page->mapping;

	get_page(newpage);

	xas_store(&xas, newpage);

	page_ref_unमुक्तze(page, expected_count - 1);

	xas_unlock_irq(&xas);

	वापस MIGRATEPAGE_SUCCESS;
पूर्ण

/*
 * Gigantic pages are so large that we करो not guarantee that page++ poपूर्णांकer
 * arithmetic will work across the entire page.  We need something more
 * specialized.
 */
अटल व्योम __copy_gigantic_page(काष्ठा page *dst, काष्ठा page *src,
				पूर्णांक nr_pages)
अणु
	पूर्णांक i;
	काष्ठा page *dst_base = dst;
	काष्ठा page *src_base = src;

	क्रम (i = 0; i < nr_pages; ) अणु
		cond_resched();
		copy_highpage(dst, src);

		i++;
		dst = mem_map_next(dst, dst_base, i);
		src = mem_map_next(src, src_base, i);
	पूर्ण
पूर्ण

अटल व्योम copy_huge_page(काष्ठा page *dst, काष्ठा page *src)
अणु
	पूर्णांक i;
	पूर्णांक nr_pages;

	अगर (PageHuge(src)) अणु
		/* hugetlbfs page */
		काष्ठा hstate *h = page_hstate(src);
		nr_pages = pages_per_huge_page(h);

		अगर (unlikely(nr_pages > MAX_ORDER_NR_PAGES)) अणु
			__copy_gigantic_page(dst, src, nr_pages);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* thp page */
		BUG_ON(!PageTransHuge(src));
		nr_pages = thp_nr_pages(src);
	पूर्ण

	क्रम (i = 0; i < nr_pages; i++) अणु
		cond_resched();
		copy_highpage(dst + i, src + i);
	पूर्ण
पूर्ण

/*
 * Copy the page to its new location
 */
व्योम migrate_page_states(काष्ठा page *newpage, काष्ठा page *page)
अणु
	पूर्णांक cpupid;

	अगर (PageError(page))
		SetPageError(newpage);
	अगर (PageReferenced(page))
		SetPageReferenced(newpage);
	अगर (PageUptodate(page))
		SetPageUptodate(newpage);
	अगर (TestClearPageActive(page)) अणु
		VM_BUG_ON_PAGE(PageUnevictable(page), page);
		SetPageActive(newpage);
	पूर्ण अन्यथा अगर (TestClearPageUnevictable(page))
		SetPageUnevictable(newpage);
	अगर (PageWorkingset(page))
		SetPageWorkingset(newpage);
	अगर (PageChecked(page))
		SetPageChecked(newpage);
	अगर (PageMappedToDisk(page))
		SetPageMappedToDisk(newpage);

	/* Move dirty on pages not करोne by migrate_page_move_mapping() */
	अगर (PageDirty(page))
		SetPageDirty(newpage);

	अगर (page_is_young(page))
		set_page_young(newpage);
	अगर (page_is_idle(page))
		set_page_idle(newpage);

	/*
	 * Copy NUMA inक्रमmation to the new page, to prevent over-eager
	 * future migrations of this same page.
	 */
	cpupid = page_cpupid_xchg_last(page, -1);
	page_cpupid_xchg_last(newpage, cpupid);

	ksm_migrate_page(newpage, page);
	/*
	 * Please करो not reorder this without considering how mm/ksm.c's
	 * get_ksm_page() depends upon ksm_migrate_page() and PageSwapCache().
	 */
	अगर (PageSwapCache(page))
		ClearPageSwapCache(page);
	ClearPagePrivate(page);
	set_page_निजी(page, 0);

	/*
	 * If any रुकोers have accumulated on the new page then
	 * wake them up.
	 */
	अगर (PageWriteback(newpage))
		end_page_ग_लिखोback(newpage);

	/*
	 * PG_पढ़ोahead shares the same bit with PG_reclaim.  The above
	 * end_page_ग_लिखोback() may clear PG_पढ़ोahead mistakenly, so set the
	 * bit after that.
	 */
	अगर (PageReadahead(page))
		SetPageReadahead(newpage);

	copy_page_owner(page, newpage);

	अगर (!PageHuge(page))
		mem_cgroup_migrate(page, newpage);
पूर्ण
EXPORT_SYMBOL(migrate_page_states);

व्योम migrate_page_copy(काष्ठा page *newpage, काष्ठा page *page)
अणु
	अगर (PageHuge(page) || PageTransHuge(page))
		copy_huge_page(newpage, page);
	अन्यथा
		copy_highpage(newpage, page);

	migrate_page_states(newpage, page);
पूर्ण
EXPORT_SYMBOL(migrate_page_copy);

/************************************************************
 *                    Migration functions
 ***********************************************************/

/*
 * Common logic to directly migrate a single LRU page suitable क्रम
 * pages that करो not use PagePrivate/PagePrivate2.
 *
 * Pages are locked upon entry and निकास.
 */
पूर्णांक migrate_page(काष्ठा address_space *mapping,
		काष्ठा page *newpage, काष्ठा page *page,
		क्रमागत migrate_mode mode)
अणु
	पूर्णांक rc;

	BUG_ON(PageWriteback(page));	/* Writeback must be complete */

	rc = migrate_page_move_mapping(mapping, newpage, page, 0);

	अगर (rc != MIGRATEPAGE_SUCCESS)
		वापस rc;

	अगर (mode != MIGRATE_SYNC_NO_COPY)
		migrate_page_copy(newpage, page);
	अन्यथा
		migrate_page_states(newpage, page);
	वापस MIGRATEPAGE_SUCCESS;
पूर्ण
EXPORT_SYMBOL(migrate_page);

#अगर_घोषित CONFIG_BLOCK
/* Returns true अगर all buffers are successfully locked */
अटल bool buffer_migrate_lock_buffers(काष्ठा buffer_head *head,
							क्रमागत migrate_mode mode)
अणु
	काष्ठा buffer_head *bh = head;

	/* Simple हाल, sync compaction */
	अगर (mode != MIGRATE_ASYNC) अणु
		करो अणु
			lock_buffer(bh);
			bh = bh->b_this_page;

		पूर्ण जबतक (bh != head);

		वापस true;
	पूर्ण

	/* async हाल, we cannot block on lock_buffer so use trylock_buffer */
	करो अणु
		अगर (!trylock_buffer(bh)) अणु
			/*
			 * We failed to lock the buffer and cannot stall in
			 * async migration. Release the taken locks
			 */
			काष्ठा buffer_head *failed_bh = bh;
			bh = head;
			जबतक (bh != failed_bh) अणु
				unlock_buffer(bh);
				bh = bh->b_this_page;
			पूर्ण
			वापस false;
		पूर्ण

		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
	वापस true;
पूर्ण

अटल पूर्णांक __buffer_migrate_page(काष्ठा address_space *mapping,
		काष्ठा page *newpage, काष्ठा page *page, क्रमागत migrate_mode mode,
		bool check_refs)
अणु
	काष्ठा buffer_head *bh, *head;
	पूर्णांक rc;
	पूर्णांक expected_count;

	अगर (!page_has_buffers(page))
		वापस migrate_page(mapping, newpage, page, mode);

	/* Check whether page करोes not have extra refs beक्रमe we करो more work */
	expected_count = expected_page_refs(mapping, page);
	अगर (page_count(page) != expected_count)
		वापस -EAGAIN;

	head = page_buffers(page);
	अगर (!buffer_migrate_lock_buffers(head, mode))
		वापस -EAGAIN;

	अगर (check_refs) अणु
		bool busy;
		bool invalidated = false;

recheck_buffers:
		busy = false;
		spin_lock(&mapping->निजी_lock);
		bh = head;
		करो अणु
			अगर (atomic_पढ़ो(&bh->b_count)) अणु
				busy = true;
				अवरोध;
			पूर्ण
			bh = bh->b_this_page;
		पूर्ण जबतक (bh != head);
		अगर (busy) अणु
			अगर (invalidated) अणु
				rc = -EAGAIN;
				जाओ unlock_buffers;
			पूर्ण
			spin_unlock(&mapping->निजी_lock);
			invalidate_bh_lrus();
			invalidated = true;
			जाओ recheck_buffers;
		पूर्ण
	पूर्ण

	rc = migrate_page_move_mapping(mapping, newpage, page, 0);
	अगर (rc != MIGRATEPAGE_SUCCESS)
		जाओ unlock_buffers;

	attach_page_निजी(newpage, detach_page_निजी(page));

	bh = head;
	करो अणु
		set_bh_page(bh, newpage, bh_offset(bh));
		bh = bh->b_this_page;

	पूर्ण जबतक (bh != head);

	अगर (mode != MIGRATE_SYNC_NO_COPY)
		migrate_page_copy(newpage, page);
	अन्यथा
		migrate_page_states(newpage, page);

	rc = MIGRATEPAGE_SUCCESS;
unlock_buffers:
	अगर (check_refs)
		spin_unlock(&mapping->निजी_lock);
	bh = head;
	करो अणु
		unlock_buffer(bh);
		bh = bh->b_this_page;

	पूर्ण जबतक (bh != head);

	वापस rc;
पूर्ण

/*
 * Migration function क्रम pages with buffers. This function can only be used
 * अगर the underlying fileप्रणाली guarantees that no other references to "page"
 * exist. For example attached buffer heads are accessed only under page lock.
 */
पूर्णांक buffer_migrate_page(काष्ठा address_space *mapping,
		काष्ठा page *newpage, काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	वापस __buffer_migrate_page(mapping, newpage, page, mode, false);
पूर्ण
EXPORT_SYMBOL(buffer_migrate_page);

/*
 * Same as above except that this variant is more careful and checks that there
 * are also no buffer head references. This function is the right one क्रम
 * mappings where buffer heads are directly looked up and referenced (such as
 * block device mappings).
 */
पूर्णांक buffer_migrate_page_norefs(काष्ठा address_space *mapping,
		काष्ठा page *newpage, काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	वापस __buffer_migrate_page(mapping, newpage, page, mode, true);
पूर्ण
#पूर्ण_अगर

/*
 * Writeback a page to clean the dirty state
 */
अटल पूर्णांक ग_लिखोout(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_NONE,
		.nr_to_ग_लिखो = 1,
		.range_start = 0,
		.range_end = Lदीर्घ_उच्च,
		.क्रम_reclaim = 1
	पूर्ण;
	पूर्णांक rc;

	अगर (!mapping->a_ops->ग_लिखोpage)
		/* No ग_लिखो method क्रम the address space */
		वापस -EINVAL;

	अगर (!clear_page_dirty_क्रम_io(page))
		/* Someone अन्यथा alपढ़ोy triggered a ग_लिखो */
		वापस -EAGAIN;

	/*
	 * A dirty page may imply that the underlying fileप्रणाली has
	 * the page on some queue. So the page must be clean क्रम
	 * migration. Writeout may mean we loose the lock and the
	 * page state is no दीर्घer what we checked क्रम earlier.
	 * At this poपूर्णांक we know that the migration attempt cannot
	 * be successful.
	 */
	हटाओ_migration_ptes(page, page, false);

	rc = mapping->a_ops->ग_लिखोpage(page, &wbc);

	अगर (rc != AOP_WRITEPAGE_ACTIVATE)
		/* unlocked. Relock */
		lock_page(page);

	वापस (rc < 0) ? -EIO : -EAGAIN;
पूर्ण

/*
 * Default handling अगर a fileप्रणाली करोes not provide a migration function.
 */
अटल पूर्णांक fallback_migrate_page(काष्ठा address_space *mapping,
	काष्ठा page *newpage, काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	अगर (PageDirty(page)) अणु
		/* Only ग_लिखोback pages in full synchronous migration */
		चयन (mode) अणु
		हाल MIGRATE_SYNC:
		हाल MIGRATE_SYNC_NO_COPY:
			अवरोध;
		शेष:
			वापस -EBUSY;
		पूर्ण
		वापस ग_लिखोout(mapping, page);
	पूर्ण

	/*
	 * Buffers may be managed in a fileप्रणाली specअगरic way.
	 * We must have no buffers or drop them.
	 */
	अगर (page_has_निजी(page) &&
	    !try_to_release_page(page, GFP_KERNEL))
		वापस mode == MIGRATE_SYNC ? -EAGAIN : -EBUSY;

	वापस migrate_page(mapping, newpage, page, mode);
पूर्ण

/*
 * Move a page to a newly allocated page
 * The page is locked and all ptes have been successfully हटाओd.
 *
 * The new page will have replaced the old page अगर this function
 * is successful.
 *
 * Return value:
 *   < 0 - error code
 *  MIGRATEPAGE_SUCCESS - success
 */
अटल पूर्णांक move_to_new_page(काष्ठा page *newpage, काष्ठा page *page,
				क्रमागत migrate_mode mode)
अणु
	काष्ठा address_space *mapping;
	पूर्णांक rc = -EAGAIN;
	bool is_lru = !__PageMovable(page);

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(!PageLocked(newpage), newpage);

	mapping = page_mapping(page);

	अगर (likely(is_lru)) अणु
		अगर (!mapping)
			rc = migrate_page(mapping, newpage, page, mode);
		अन्यथा अगर (mapping->a_ops->migratepage)
			/*
			 * Most pages have a mapping and most fileप्रणालीs
			 * provide a migratepage callback. Anonymous pages
			 * are part of swap space which also has its own
			 * migratepage callback. This is the most common path
			 * क्रम page migration.
			 */
			rc = mapping->a_ops->migratepage(mapping, newpage,
							page, mode);
		अन्यथा
			rc = fallback_migrate_page(mapping, newpage,
							page, mode);
	पूर्ण अन्यथा अणु
		/*
		 * In हाल of non-lru page, it could be released after
		 * isolation step. In that हाल, we shouldn't try migration.
		 */
		VM_BUG_ON_PAGE(!PageIsolated(page), page);
		अगर (!PageMovable(page)) अणु
			rc = MIGRATEPAGE_SUCCESS;
			__ClearPageIsolated(page);
			जाओ out;
		पूर्ण

		rc = mapping->a_ops->migratepage(mapping, newpage,
						page, mode);
		WARN_ON_ONCE(rc == MIGRATEPAGE_SUCCESS &&
			!PageIsolated(page));
	पूर्ण

	/*
	 * When successful, old pagecache page->mapping must be cleared beक्रमe
	 * page is मुक्तd; but stats require that PageAnon be left as PageAnon.
	 */
	अगर (rc == MIGRATEPAGE_SUCCESS) अणु
		अगर (__PageMovable(page)) अणु
			VM_BUG_ON_PAGE(!PageIsolated(page), page);

			/*
			 * We clear PG_movable under page_lock so any compactor
			 * cannot try to migrate this page.
			 */
			__ClearPageIsolated(page);
		पूर्ण

		/*
		 * Anonymous and movable page->mapping will be cleared by
		 * मुक्त_pages_prepare so करोn't reset it here क्रम keeping
		 * the type to work PageAnon, क्रम example.
		 */
		अगर (!PageMappingFlags(page))
			page->mapping = शून्य;

		अगर (likely(!is_zone_device_page(newpage)))
			flush_dcache_page(newpage);

	पूर्ण
out:
	वापस rc;
पूर्ण

अटल पूर्णांक __unmap_and_move(काष्ठा page *page, काष्ठा page *newpage,
				पूर्णांक क्रमce, क्रमागत migrate_mode mode)
अणु
	पूर्णांक rc = -EAGAIN;
	पूर्णांक page_was_mapped = 0;
	काष्ठा anon_vma *anon_vma = शून्य;
	bool is_lru = !__PageMovable(page);

	अगर (!trylock_page(page)) अणु
		अगर (!क्रमce || mode == MIGRATE_ASYNC)
			जाओ out;

		/*
		 * It's not safe क्रम direct compaction to call lock_page.
		 * For example, during page पढ़ोahead pages are added locked
		 * to the LRU. Later, when the IO completes the pages are
		 * marked uptodate and unlocked. However, the queueing
		 * could be merging multiple pages क्रम one bio (e.g.
		 * mpage_पढ़ोahead). If an allocation happens क्रम the
		 * second or third page, the process can end up locking
		 * the same page twice and deadlocking. Rather than
		 * trying to be clever about what pages can be locked,
		 * aव्योम the use of lock_page क्रम direct compaction
		 * altogether.
		 */
		अगर (current->flags & PF_MEMALLOC)
			जाओ out;

		lock_page(page);
	पूर्ण

	अगर (PageWriteback(page)) अणु
		/*
		 * Only in the हाल of a full synchronous migration is it
		 * necessary to रुको क्रम PageWriteback. In the async हाल,
		 * the retry loop is too लघु and in the sync-light हाल,
		 * the overhead of stalling is too much
		 */
		चयन (mode) अणु
		हाल MIGRATE_SYNC:
		हाल MIGRATE_SYNC_NO_COPY:
			अवरोध;
		शेष:
			rc = -EBUSY;
			जाओ out_unlock;
		पूर्ण
		अगर (!क्रमce)
			जाओ out_unlock;
		रुको_on_page_ग_लिखोback(page);
	पूर्ण

	/*
	 * By try_to_unmap(), page->mapcount goes करोwn to 0 here. In this हाल,
	 * we cannot notice that anon_vma is मुक्तd जबतक we migrates a page.
	 * This get_anon_vma() delays मुक्तing anon_vma poपूर्णांकer until the end
	 * of migration. File cache pages are no problem because of page_lock()
	 * File Caches may use ग_लिखो_page() or lock_page() in migration, then,
	 * just care Anon page here.
	 *
	 * Only page_get_anon_vma() understands the subtleties of
	 * getting a hold on an anon_vma from outside one of its mms.
	 * But अगर we cannot get anon_vma, then we won't need it anyway,
	 * because that implies that the anon page is no दीर्घer mapped
	 * (and cannot be remapped so दीर्घ as we hold the page lock).
	 */
	अगर (PageAnon(page) && !PageKsm(page))
		anon_vma = page_get_anon_vma(page);

	/*
	 * Block others from accessing the new page when we get around to
	 * establishing additional references. We are usually the only one
	 * holding a reference to newpage at this poपूर्णांक. We used to have a BUG
	 * here अगर trylock_page(newpage) fails, but would like to allow क्रम
	 * हालs where there might be a race with the previous use of newpage.
	 * This is much like races on refcount of oldpage: just करोn't BUG().
	 */
	अगर (unlikely(!trylock_page(newpage)))
		जाओ out_unlock;

	अगर (unlikely(!is_lru)) अणु
		rc = move_to_new_page(newpage, page, mode);
		जाओ out_unlock_both;
	पूर्ण

	/*
	 * Corner हाल handling:
	 * 1. When a new swap-cache page is पढ़ो पूर्णांकo, it is added to the LRU
	 * and treated as swapcache but it has no rmap yet.
	 * Calling try_to_unmap() against a page->mapping==शून्य page will
	 * trigger a BUG.  So handle it here.
	 * 2. An orphaned page (see truncate_cleanup_page) might have
	 * fs-निजी metadata. The page can be picked up due to memory
	 * offlining.  Everywhere अन्यथा except page reclaim, the page is
	 * invisible to the vm, so the page can not be migrated.  So try to
	 * मुक्त the metadata, so the page can be मुक्तd.
	 */
	अगर (!page->mapping) अणु
		VM_BUG_ON_PAGE(PageAnon(page), page);
		अगर (page_has_निजी(page)) अणु
			try_to_मुक्त_buffers(page);
			जाओ out_unlock_both;
		पूर्ण
	पूर्ण अन्यथा अगर (page_mapped(page)) अणु
		/* Establish migration ptes */
		VM_BUG_ON_PAGE(PageAnon(page) && !PageKsm(page) && !anon_vma,
				page);
		try_to_unmap(page, TTU_MIGRATION|TTU_IGNORE_MLOCK);
		page_was_mapped = 1;
	पूर्ण

	अगर (!page_mapped(page))
		rc = move_to_new_page(newpage, page, mode);

	अगर (page_was_mapped)
		हटाओ_migration_ptes(page,
			rc == MIGRATEPAGE_SUCCESS ? newpage : page, false);

out_unlock_both:
	unlock_page(newpage);
out_unlock:
	/* Drop an anon_vma reference अगर we took one */
	अगर (anon_vma)
		put_anon_vma(anon_vma);
	unlock_page(page);
out:
	/*
	 * If migration is successful, decrease refcount of the newpage
	 * which will not मुक्त the page because new page owner increased
	 * refcounter. As well, अगर it is LRU page, add the page to LRU
	 * list in here. Use the old state of the isolated source page to
	 * determine अगर we migrated a LRU page. newpage was alपढ़ोy unlocked
	 * and possibly modअगरied by its owner - करोn't rely on the page
	 * state.
	 */
	अगर (rc == MIGRATEPAGE_SUCCESS) अणु
		अगर (unlikely(!is_lru))
			put_page(newpage);
		अन्यथा
			putback_lru_page(newpage);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Obtain the lock on page, हटाओ all ptes and migrate the page
 * to the newly allocated page in newpage.
 */
अटल पूर्णांक unmap_and_move(new_page_t get_new_page,
				   मुक्त_page_t put_new_page,
				   अचिन्हित दीर्घ निजी, काष्ठा page *page,
				   पूर्णांक क्रमce, क्रमागत migrate_mode mode,
				   क्रमागत migrate_reason reason,
				   काष्ठा list_head *ret)
अणु
	पूर्णांक rc = MIGRATEPAGE_SUCCESS;
	काष्ठा page *newpage = शून्य;

	अगर (!thp_migration_supported() && PageTransHuge(page))
		वापस -ENOSYS;

	अगर (page_count(page) == 1) अणु
		/* page was मुक्तd from under us. So we are करोne. */
		ClearPageActive(page);
		ClearPageUnevictable(page);
		अगर (unlikely(__PageMovable(page))) अणु
			lock_page(page);
			अगर (!PageMovable(page))
				__ClearPageIsolated(page);
			unlock_page(page);
		पूर्ण
		जाओ out;
	पूर्ण

	newpage = get_new_page(page, निजी);
	अगर (!newpage)
		वापस -ENOMEM;

	rc = __unmap_and_move(page, newpage, क्रमce, mode);
	अगर (rc == MIGRATEPAGE_SUCCESS)
		set_page_owner_migrate_reason(newpage, reason);

out:
	अगर (rc != -EAGAIN) अणु
		/*
		 * A page that has been migrated has all references
		 * हटाओd and will be मुक्तd. A page that has not been
		 * migrated will have kept its references and be restored.
		 */
		list_del(&page->lru);
	पूर्ण

	/*
	 * If migration is successful, releases reference grabbed during
	 * isolation. Otherwise, restore the page to right list unless
	 * we want to retry.
	 */
	अगर (rc == MIGRATEPAGE_SUCCESS) अणु
		/*
		 * Compaction can migrate also non-LRU pages which are
		 * not accounted to NR_ISOLATED_*. They can be recognized
		 * as __PageMovable
		 */
		अगर (likely(!__PageMovable(page)))
			mod_node_page_state(page_pgdat(page), NR_ISOLATED_ANON +
					page_is_file_lru(page), -thp_nr_pages(page));

		अगर (reason != MR_MEMORY_FAILURE)
			/*
			 * We release the page in page_handle_poison.
			 */
			put_page(page);
	पूर्ण अन्यथा अणु
		अगर (rc != -EAGAIN)
			list_add_tail(&page->lru, ret);

		अगर (put_new_page)
			put_new_page(newpage, निजी);
		अन्यथा
			put_page(newpage);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Counterpart of unmap_and_move_page() क्रम hugepage migration.
 *
 * This function करोesn't रुको the completion of hugepage I/O
 * because there is no race between I/O and migration क्रम hugepage.
 * Note that currently hugepage I/O occurs only in direct I/O
 * where no lock is held and PG_ग_लिखोback is irrelevant,
 * and ग_लिखोback status of all subpages are counted in the reference
 * count of the head page (i.e. अगर all subpages of a 2MB hugepage are
 * under direct I/O, the reference of the head page is 512 and a bit more.)
 * This means that when we try to migrate hugepage whose subpages are
 * करोing direct I/O, some references reमुख्य after try_to_unmap() and
 * hugepage migration fails without data corruption.
 *
 * There is also no race when direct I/O is issued on the page under migration,
 * because then pte is replaced with migration swap entry and direct I/O code
 * will रुको in the page fault क्रम migration to complete.
 */
अटल पूर्णांक unmap_and_move_huge_page(new_page_t get_new_page,
				मुक्त_page_t put_new_page, अचिन्हित दीर्घ निजी,
				काष्ठा page *hpage, पूर्णांक क्रमce,
				क्रमागत migrate_mode mode, पूर्णांक reason,
				काष्ठा list_head *ret)
अणु
	पूर्णांक rc = -EAGAIN;
	पूर्णांक page_was_mapped = 0;
	काष्ठा page *new_hpage;
	काष्ठा anon_vma *anon_vma = शून्य;
	काष्ठा address_space *mapping = शून्य;

	/*
	 * Migratability of hugepages depends on architectures and their size.
	 * This check is necessary because some callers of hugepage migration
	 * like soft offline and memory hotहटाओ करोn't walk through page
	 * tables or check whether the hugepage is pmd-based or not beक्रमe
	 * kicking migration.
	 */
	अगर (!hugepage_migration_supported(page_hstate(hpage))) अणु
		list_move_tail(&hpage->lru, ret);
		वापस -ENOSYS;
	पूर्ण

	अगर (page_count(hpage) == 1) अणु
		/* page was मुक्तd from under us. So we are करोne. */
		putback_active_hugepage(hpage);
		वापस MIGRATEPAGE_SUCCESS;
	पूर्ण

	new_hpage = get_new_page(hpage, निजी);
	अगर (!new_hpage)
		वापस -ENOMEM;

	अगर (!trylock_page(hpage)) अणु
		अगर (!क्रमce)
			जाओ out;
		चयन (mode) अणु
		हाल MIGRATE_SYNC:
		हाल MIGRATE_SYNC_NO_COPY:
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
		lock_page(hpage);
	पूर्ण

	/*
	 * Check क्रम pages which are in the process of being मुक्तd.  Without
	 * page_mapping() set, hugetlbfs specअगरic move page routine will not
	 * be called and we could leak usage counts क्रम subpools.
	 */
	अगर (page_निजी(hpage) && !page_mapping(hpage)) अणु
		rc = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	अगर (PageAnon(hpage))
		anon_vma = page_get_anon_vma(hpage);

	अगर (unlikely(!trylock_page(new_hpage)))
		जाओ put_anon;

	अगर (page_mapped(hpage)) अणु
		bool mapping_locked = false;
		क्रमागत ttu_flags ttu = TTU_MIGRATION|TTU_IGNORE_MLOCK;

		अगर (!PageAnon(hpage)) अणु
			/*
			 * In shared mappings, try_to_unmap could potentially
			 * call huge_pmd_unshare.  Because of this, take
			 * semaphore in ग_लिखो mode here and set TTU_RMAP_LOCKED
			 * to let lower levels know we have taken the lock.
			 */
			mapping = hugetlb_page_mapping_lock_ग_लिखो(hpage);
			अगर (unlikely(!mapping))
				जाओ unlock_put_anon;

			mapping_locked = true;
			ttu |= TTU_RMAP_LOCKED;
		पूर्ण

		try_to_unmap(hpage, ttu);
		page_was_mapped = 1;

		अगर (mapping_locked)
			i_mmap_unlock_ग_लिखो(mapping);
	पूर्ण

	अगर (!page_mapped(hpage))
		rc = move_to_new_page(new_hpage, hpage, mode);

	अगर (page_was_mapped)
		हटाओ_migration_ptes(hpage,
			rc == MIGRATEPAGE_SUCCESS ? new_hpage : hpage, false);

unlock_put_anon:
	unlock_page(new_hpage);

put_anon:
	अगर (anon_vma)
		put_anon_vma(anon_vma);

	अगर (rc == MIGRATEPAGE_SUCCESS) अणु
		move_hugetlb_state(hpage, new_hpage, reason);
		put_new_page = शून्य;
	पूर्ण

out_unlock:
	unlock_page(hpage);
out:
	अगर (rc == MIGRATEPAGE_SUCCESS)
		putback_active_hugepage(hpage);
	अन्यथा अगर (rc != -EAGAIN)
		list_move_tail(&hpage->lru, ret);

	/*
	 * If migration was not successful and there's a मुक्तing callback, use
	 * it.  Otherwise, put_page() will drop the reference grabbed during
	 * isolation.
	 */
	अगर (put_new_page)
		put_new_page(new_hpage, निजी);
	अन्यथा
		putback_active_hugepage(new_hpage);

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक try_split_thp(काष्ठा page *page, काष्ठा page **page2,
				काष्ठा list_head *from)
अणु
	पूर्णांक rc = 0;

	lock_page(page);
	rc = split_huge_page_to_list(page, from);
	unlock_page(page);
	अगर (!rc)
		list_safe_reset_next(page, *page2, lru);

	वापस rc;
पूर्ण

/*
 * migrate_pages - migrate the pages specअगरied in a list, to the मुक्त pages
 *		   supplied as the target क्रम the page migration
 *
 * @from:		The list of pages to be migrated.
 * @get_new_page:	The function used to allocate मुक्त pages to be used
 *			as the target of the page migration.
 * @put_new_page:	The function used to मुक्त target pages अगर migration
 *			fails, or शून्य अगर no special handling is necessary.
 * @निजी:		Private data to be passed on to get_new_page()
 * @mode:		The migration mode that specअगरies the स्थिरraपूर्णांकs क्रम
 *			page migration, अगर any.
 * @reason:		The reason क्रम page migration.
 *
 * The function वापसs after 10 attempts or अगर no pages are movable any more
 * because the list has become empty or no retryable pages exist any more.
 * It is caller's responsibility to call putback_movable_pages() to वापस pages
 * to the LRU or मुक्त list only अगर ret != 0.
 *
 * Returns the number of pages that were not migrated, or an error code.
 */
पूर्णांक migrate_pages(काष्ठा list_head *from, new_page_t get_new_page,
		मुक्त_page_t put_new_page, अचिन्हित दीर्घ निजी,
		क्रमागत migrate_mode mode, पूर्णांक reason)
अणु
	पूर्णांक retry = 1;
	पूर्णांक thp_retry = 1;
	पूर्णांक nr_failed = 0;
	पूर्णांक nr_succeeded = 0;
	पूर्णांक nr_thp_succeeded = 0;
	पूर्णांक nr_thp_failed = 0;
	पूर्णांक nr_thp_split = 0;
	पूर्णांक pass = 0;
	bool is_thp = false;
	काष्ठा page *page;
	काष्ठा page *page2;
	पूर्णांक swapग_लिखो = current->flags & PF_SWAPWRITE;
	पूर्णांक rc, nr_subpages;
	LIST_HEAD(ret_pages);

	trace_mm_migrate_pages_start(mode, reason);

	अगर (!swapग_लिखो)
		current->flags |= PF_SWAPWRITE;

	क्रम (pass = 0; pass < 10 && (retry || thp_retry); pass++) अणु
		retry = 0;
		thp_retry = 0;

		list_क्रम_each_entry_safe(page, page2, from, lru) अणु
retry:
			/*
			 * THP statistics is based on the source huge page.
			 * Capture required inक्रमmation that might get lost
			 * during migration.
			 */
			is_thp = PageTransHuge(page) && !PageHuge(page);
			nr_subpages = thp_nr_pages(page);
			cond_resched();

			अगर (PageHuge(page))
				rc = unmap_and_move_huge_page(get_new_page,
						put_new_page, निजी, page,
						pass > 2, mode, reason,
						&ret_pages);
			अन्यथा
				rc = unmap_and_move(get_new_page, put_new_page,
						निजी, page, pass > 2, mode,
						reason, &ret_pages);
			/*
			 * The rules are:
			 *	Success: non hugetlb page will be मुक्तd, hugetlb
			 *		 page will be put back
			 *	-EAGAIN: stay on the from list
			 *	-ENOMEM: stay on the from list
			 *	Other त्रुटि_सं: put on ret_pages list then splice to
			 *		     from list
			 */
			चयन(rc) अणु
			/*
			 * THP migration might be unsupported or the
			 * allocation could've failed so we should
			 * retry on the same page with the THP split
			 * to base pages.
			 *
			 * Head page is retried immediately and tail
			 * pages are added to the tail of the list so
			 * we encounter them after the rest of the list
			 * is processed.
			 */
			हाल -ENOSYS:
				/* THP migration is unsupported */
				अगर (is_thp) अणु
					अगर (!try_split_thp(page, &page2, from)) अणु
						nr_thp_split++;
						जाओ retry;
					पूर्ण

					nr_thp_failed++;
					nr_failed += nr_subpages;
					अवरोध;
				पूर्ण

				/* Hugetlb migration is unsupported */
				nr_failed++;
				अवरोध;
			हाल -ENOMEM:
				/*
				 * When memory is low, करोn't bother to try to migrate
				 * other pages, just निकास.
				 */
				अगर (is_thp) अणु
					अगर (!try_split_thp(page, &page2, from)) अणु
						nr_thp_split++;
						जाओ retry;
					पूर्ण

					nr_thp_failed++;
					nr_failed += nr_subpages;
					जाओ out;
				पूर्ण
				nr_failed++;
				जाओ out;
			हाल -EAGAIN:
				अगर (is_thp) अणु
					thp_retry++;
					अवरोध;
				पूर्ण
				retry++;
				अवरोध;
			हाल MIGRATEPAGE_SUCCESS:
				अगर (is_thp) अणु
					nr_thp_succeeded++;
					nr_succeeded += nr_subpages;
					अवरोध;
				पूर्ण
				nr_succeeded++;
				अवरोध;
			शेष:
				/*
				 * Permanent failure (-EBUSY, etc.):
				 * unlike -EAGAIN हाल, the failed page is
				 * हटाओd from migration page list and not
				 * retried in the next outer loop.
				 */
				अगर (is_thp) अणु
					nr_thp_failed++;
					nr_failed += nr_subpages;
					अवरोध;
				पूर्ण
				nr_failed++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	nr_failed += retry + thp_retry;
	nr_thp_failed += thp_retry;
	rc = nr_failed;
out:
	/*
	 * Put the permanent failure page back to migration list, they
	 * will be put back to the right list by the caller.
	 */
	list_splice(&ret_pages, from);

	count_vm_events(PGMIGRATE_SUCCESS, nr_succeeded);
	count_vm_events(PGMIGRATE_FAIL, nr_failed);
	count_vm_events(THP_MIGRATION_SUCCESS, nr_thp_succeeded);
	count_vm_events(THP_MIGRATION_FAIL, nr_thp_failed);
	count_vm_events(THP_MIGRATION_SPLIT, nr_thp_split);
	trace_mm_migrate_pages(nr_succeeded, nr_failed, nr_thp_succeeded,
			       nr_thp_failed, nr_thp_split, mode, reason);

	अगर (!swapग_लिखो)
		current->flags &= ~PF_SWAPWRITE;

	वापस rc;
पूर्ण

काष्ठा page *alloc_migration_target(काष्ठा page *page, अचिन्हित दीर्घ निजी)
अणु
	काष्ठा migration_target_control *mtc;
	gfp_t gfp_mask;
	अचिन्हित पूर्णांक order = 0;
	काष्ठा page *new_page = शून्य;
	पूर्णांक nid;
	पूर्णांक zidx;

	mtc = (काष्ठा migration_target_control *)निजी;
	gfp_mask = mtc->gfp_mask;
	nid = mtc->nid;
	अगर (nid == NUMA_NO_NODE)
		nid = page_to_nid(page);

	अगर (PageHuge(page)) अणु
		काष्ठा hstate *h = page_hstate(compound_head(page));

		gfp_mask = htlb_modअगरy_alloc_mask(h, gfp_mask);
		वापस alloc_huge_page_nodemask(h, nid, mtc->nmask, gfp_mask);
	पूर्ण

	अगर (PageTransHuge(page)) अणु
		/*
		 * clear __GFP_RECLAIM to make the migration callback
		 * consistent with regular THP allocations.
		 */
		gfp_mask &= ~__GFP_RECLAIM;
		gfp_mask |= GFP_TRANSHUGE;
		order = HPAGE_PMD_ORDER;
	पूर्ण
	zidx = zone_idx(page_zone(page));
	अगर (is_highmem_idx(zidx) || zidx == ZONE_MOVABLE)
		gfp_mask |= __GFP_HIGHMEM;

	new_page = __alloc_pages(gfp_mask, order, nid, mtc->nmask);

	अगर (new_page && PageTransHuge(new_page))
		prep_transhuge_page(new_page);

	वापस new_page;
पूर्ण

#अगर_घोषित CONFIG_NUMA

अटल पूर्णांक store_status(पूर्णांक __user *status, पूर्णांक start, पूर्णांक value, पूर्णांक nr)
अणु
	जबतक (nr-- > 0) अणु
		अगर (put_user(value, status + start))
			वापस -EFAULT;
		start++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_move_pages_to_node(काष्ठा mm_काष्ठा *mm,
		काष्ठा list_head *pagelist, पूर्णांक node)
अणु
	पूर्णांक err;
	काष्ठा migration_target_control mtc = अणु
		.nid = node,
		.gfp_mask = GFP_HIGHUSER_MOVABLE | __GFP_THISNODE,
	पूर्ण;

	err = migrate_pages(pagelist, alloc_migration_target, शून्य,
			(अचिन्हित दीर्घ)&mtc, MIGRATE_SYNC, MR_SYSCALL);
	अगर (err)
		putback_movable_pages(pagelist);
	वापस err;
पूर्ण

/*
 * Resolves the given address to a काष्ठा page, isolates it from the LRU and
 * माला_दो it to the given pagelist.
 * Returns:
 *     त्रुटि_सं - अगर the page cannot be found/isolated
 *     0 - when it करोesn't have to be migrated because it is alपढ़ोy on the
 *         target node
 *     1 - when it has been queued
 */
अटल पूर्णांक add_page_क्रम_migration(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		पूर्णांक node, काष्ठा list_head *pagelist, bool migrate_all)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा page *page;
	अचिन्हित पूर्णांक follflags;
	पूर्णांक err;

	mmap_पढ़ो_lock(mm);
	err = -EFAULT;
	vma = find_vma(mm, addr);
	अगर (!vma || addr < vma->vm_start || !vma_migratable(vma))
		जाओ out;

	/* FOLL_DUMP to ignore special (like zero) pages */
	follflags = FOLL_GET | FOLL_DUMP;
	page = follow_page(vma, addr, follflags);

	err = PTR_ERR(page);
	अगर (IS_ERR(page))
		जाओ out;

	err = -ENOENT;
	अगर (!page)
		जाओ out;

	err = 0;
	अगर (page_to_nid(page) == node)
		जाओ out_putpage;

	err = -EACCES;
	अगर (page_mapcount(page) > 1 && !migrate_all)
		जाओ out_putpage;

	अगर (PageHuge(page)) अणु
		अगर (PageHead(page)) अणु
			isolate_huge_page(page, pagelist);
			err = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा page *head;

		head = compound_head(page);
		err = isolate_lru_page(head);
		अगर (err)
			जाओ out_putpage;

		err = 1;
		list_add_tail(&head->lru, pagelist);
		mod_node_page_state(page_pgdat(head),
			NR_ISOLATED_ANON + page_is_file_lru(head),
			thp_nr_pages(head));
	पूर्ण
out_putpage:
	/*
	 * Either हटाओ the duplicate refcount from
	 * isolate_lru_page() or drop the page ref अगर it was
	 * not isolated.
	 */
	put_page(page);
out:
	mmap_पढ़ो_unlock(mm);
	वापस err;
पूर्ण

अटल पूर्णांक move_pages_and_store_status(काष्ठा mm_काष्ठा *mm, पूर्णांक node,
		काष्ठा list_head *pagelist, पूर्णांक __user *status,
		पूर्णांक start, पूर्णांक i, अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक err;

	अगर (list_empty(pagelist))
		वापस 0;

	err = करो_move_pages_to_node(mm, pagelist, node);
	अगर (err) अणु
		/*
		 * Positive err means the number of failed
		 * pages to migrate.  Since we are going to
		 * पात and वापस the number of non-migrated
		 * pages, so need to include the rest of the
		 * nr_pages that have not been attempted as
		 * well.
		 */
		अगर (err > 0)
			err += nr_pages - i - 1;
		वापस err;
	पूर्ण
	वापस store_status(status, start, node, i - start);
पूर्ण

/*
 * Migrate an array of page address onto an array of nodes and fill
 * the corresponding array of status.
 */
अटल पूर्णांक करो_pages_move(काष्ठा mm_काष्ठा *mm, nodemask_t task_nodes,
			 अचिन्हित दीर्घ nr_pages,
			 स्थिर व्योम __user * __user *pages,
			 स्थिर पूर्णांक __user *nodes,
			 पूर्णांक __user *status, पूर्णांक flags)
अणु
	पूर्णांक current_node = NUMA_NO_NODE;
	LIST_HEAD(pagelist);
	पूर्णांक start, i;
	पूर्णांक err = 0, err1;

	lru_cache_disable();

	क्रम (i = start = 0; i < nr_pages; i++) अणु
		स्थिर व्योम __user *p;
		अचिन्हित दीर्घ addr;
		पूर्णांक node;

		err = -EFAULT;
		अगर (get_user(p, pages + i))
			जाओ out_flush;
		अगर (get_user(node, nodes + i))
			जाओ out_flush;
		addr = (अचिन्हित दीर्घ)untagged_addr(p);

		err = -ENODEV;
		अगर (node < 0 || node >= MAX_NUMNODES)
			जाओ out_flush;
		अगर (!node_state(node, N_MEMORY))
			जाओ out_flush;

		err = -EACCES;
		अगर (!node_isset(node, task_nodes))
			जाओ out_flush;

		अगर (current_node == NUMA_NO_NODE) अणु
			current_node = node;
			start = i;
		पूर्ण अन्यथा अगर (node != current_node) अणु
			err = move_pages_and_store_status(mm, current_node,
					&pagelist, status, start, i, nr_pages);
			अगर (err)
				जाओ out;
			start = i;
			current_node = node;
		पूर्ण

		/*
		 * Errors in the page lookup or isolation are not fatal and we simply
		 * report them via status
		 */
		err = add_page_क्रम_migration(mm, addr, current_node,
				&pagelist, flags & MPOL_MF_MOVE_ALL);

		अगर (err > 0) अणु
			/* The page is successfully queued क्रम migration */
			जारी;
		पूर्ण

		/*
		 * If the page is alपढ़ोy on the target node (!err), store the
		 * node, otherwise, store the err.
		 */
		err = store_status(status, i, err ? : current_node, 1);
		अगर (err)
			जाओ out_flush;

		err = move_pages_and_store_status(mm, current_node, &pagelist,
				status, start, i, nr_pages);
		अगर (err)
			जाओ out;
		current_node = NUMA_NO_NODE;
	पूर्ण
out_flush:
	/* Make sure we करो not overग_लिखो the existing error */
	err1 = move_pages_and_store_status(mm, current_node, &pagelist,
				status, start, i, nr_pages);
	अगर (err >= 0)
		err = err1;
out:
	lru_cache_enable();
	वापस err;
पूर्ण

/*
 * Determine the nodes of an array of pages and store it in an array of status.
 */
अटल व्योम करो_pages_stat_array(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ nr_pages,
				स्थिर व्योम __user **pages, पूर्णांक *status)
अणु
	अचिन्हित दीर्घ i;

	mmap_पढ़ो_lock(mm);

	क्रम (i = 0; i < nr_pages; i++) अणु
		अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)(*pages);
		काष्ठा vm_area_काष्ठा *vma;
		काष्ठा page *page;
		पूर्णांक err = -EFAULT;

		vma = find_vma(mm, addr);
		अगर (!vma || addr < vma->vm_start)
			जाओ set_status;

		/* FOLL_DUMP to ignore special (like zero) pages */
		page = follow_page(vma, addr, FOLL_DUMP);

		err = PTR_ERR(page);
		अगर (IS_ERR(page))
			जाओ set_status;

		err = page ? page_to_nid(page) : -ENOENT;
set_status:
		*status = err;

		pages++;
		status++;
	पूर्ण

	mmap_पढ़ो_unlock(mm);
पूर्ण

/*
 * Determine the nodes of a user array of pages and store it in
 * a user array of status.
 */
अटल पूर्णांक करो_pages_stat(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ nr_pages,
			 स्थिर व्योम __user * __user *pages,
			 पूर्णांक __user *status)
अणु
#घोषणा DO_PAGES_STAT_CHUNK_NR 16
	स्थिर व्योम __user *chunk_pages[DO_PAGES_STAT_CHUNK_NR];
	पूर्णांक chunk_status[DO_PAGES_STAT_CHUNK_NR];

	जबतक (nr_pages) अणु
		अचिन्हित दीर्घ chunk_nr;

		chunk_nr = nr_pages;
		अगर (chunk_nr > DO_PAGES_STAT_CHUNK_NR)
			chunk_nr = DO_PAGES_STAT_CHUNK_NR;

		अगर (copy_from_user(chunk_pages, pages, chunk_nr * माप(*chunk_pages)))
			अवरोध;

		करो_pages_stat_array(mm, chunk_nr, chunk_pages, chunk_status);

		अगर (copy_to_user(status, chunk_status, chunk_nr * माप(*status)))
			अवरोध;

		pages += chunk_nr;
		status += chunk_nr;
		nr_pages -= chunk_nr;
	पूर्ण
	वापस nr_pages ? -EFAULT : 0;
पूर्ण

अटल काष्ठा mm_काष्ठा *find_mm_काष्ठा(pid_t pid, nodemask_t *mem_nodes)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा mm_काष्ठा *mm;

	/*
	 * There is no need to check अगर current process has the right to modअगरy
	 * the specअगरied process when they are same.
	 */
	अगर (!pid) अणु
		mmget(current->mm);
		*mem_nodes = cpuset_mems_allowed(current);
		वापस current->mm;
	पूर्ण

	/* Find the mm_काष्ठा */
	rcu_पढ़ो_lock();
	task = find_task_by_vpid(pid);
	अगर (!task) अणु
		rcu_पढ़ो_unlock();
		वापस ERR_PTR(-ESRCH);
	पूर्ण
	get_task_काष्ठा(task);

	/*
	 * Check अगर this process has the right to modअगरy the specअगरied
	 * process. Use the regular "ptrace_may_access()" checks.
	 */
	अगर (!ptrace_may_access(task, PTRACE_MODE_READ_REALCREDS)) अणु
		rcu_पढ़ो_unlock();
		mm = ERR_PTR(-EPERM);
		जाओ out;
	पूर्ण
	rcu_पढ़ो_unlock();

	mm = ERR_PTR(security_task_movememory(task));
	अगर (IS_ERR(mm))
		जाओ out;
	*mem_nodes = cpuset_mems_allowed(task);
	mm = get_task_mm(task);
out:
	put_task_काष्ठा(task);
	अगर (!mm)
		mm = ERR_PTR(-EINVAL);
	वापस mm;
पूर्ण

/*
 * Move a list of pages in the address space of the currently executing
 * process.
 */
अटल पूर्णांक kernel_move_pages(pid_t pid, अचिन्हित दीर्घ nr_pages,
			     स्थिर व्योम __user * __user *pages,
			     स्थिर पूर्णांक __user *nodes,
			     पूर्णांक __user *status, पूर्णांक flags)
अणु
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक err;
	nodemask_t task_nodes;

	/* Check flags */
	अगर (flags & ~(MPOL_MF_MOVE|MPOL_MF_MOVE_ALL))
		वापस -EINVAL;

	अगर ((flags & MPOL_MF_MOVE_ALL) && !capable(CAP_SYS_NICE))
		वापस -EPERM;

	mm = find_mm_काष्ठा(pid, &task_nodes);
	अगर (IS_ERR(mm))
		वापस PTR_ERR(mm);

	अगर (nodes)
		err = करो_pages_move(mm, task_nodes, nr_pages, pages,
				    nodes, status, flags);
	अन्यथा
		err = करो_pages_stat(mm, nr_pages, pages, status);

	mmput(mm);
	वापस err;
पूर्ण

SYSCALL_DEFINE6(move_pages, pid_t, pid, अचिन्हित दीर्घ, nr_pages,
		स्थिर व्योम __user * __user *, pages,
		स्थिर पूर्णांक __user *, nodes,
		पूर्णांक __user *, status, पूर्णांक, flags)
अणु
	वापस kernel_move_pages(pid, nr_pages, pages, nodes, status, flags);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE6(move_pages, pid_t, pid, compat_uदीर्घ_t, nr_pages,
		       compat_uptr_t __user *, pages32,
		       स्थिर पूर्णांक __user *, nodes,
		       पूर्णांक __user *, status,
		       पूर्णांक, flags)
अणु
	स्थिर व्योम __user * __user *pages;
	पूर्णांक i;

	pages = compat_alloc_user_space(nr_pages * माप(व्योम *));
	क्रम (i = 0; i < nr_pages; i++) अणु
		compat_uptr_t p;

		अगर (get_user(p, pages32 + i) ||
			put_user(compat_ptr(p), pages + i))
			वापस -EFAULT;
	पूर्ण
	वापस kernel_move_pages(pid, nr_pages, pages, nodes, status, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

#अगर_घोषित CONFIG_NUMA_BALANCING
/*
 * Returns true अगर this is a safe migration target node क्रम misplaced NUMA
 * pages. Currently it only checks the watermarks which crude
 */
अटल bool migrate_balanced_pgdat(काष्ठा pglist_data *pgdat,
				   अचिन्हित दीर्घ nr_migrate_pages)
अणु
	पूर्णांक z;

	क्रम (z = pgdat->nr_zones - 1; z >= 0; z--) अणु
		काष्ठा zone *zone = pgdat->node_zones + z;

		अगर (!populated_zone(zone))
			जारी;

		/* Aव्योम waking kswapd by allocating pages_to_migrate pages. */
		अगर (!zone_watermark_ok(zone, 0,
				       high_wmark_pages(zone) +
				       nr_migrate_pages,
				       ZONE_MOVABLE, 0))
			जारी;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा page *alloc_misplaced_dst_page(काष्ठा page *page,
					   अचिन्हित दीर्घ data)
अणु
	पूर्णांक nid = (पूर्णांक) data;
	काष्ठा page *newpage;

	newpage = __alloc_pages_node(nid,
					 (GFP_HIGHUSER_MOVABLE |
					  __GFP_THISNODE | __GFP_NOMEMALLOC |
					  __GFP_NORETRY | __GFP_NOWARN) &
					 ~__GFP_RECLAIM, 0);

	वापस newpage;
पूर्ण

अटल पूर्णांक numamigrate_isolate_page(pg_data_t *pgdat, काष्ठा page *page)
अणु
	पूर्णांक page_lru;

	VM_BUG_ON_PAGE(compound_order(page) && !PageTransHuge(page), page);

	/* Aव्योम migrating to a node that is nearly full */
	अगर (!migrate_balanced_pgdat(pgdat, compound_nr(page)))
		वापस 0;

	अगर (isolate_lru_page(page))
		वापस 0;

	/*
	 * migrate_misplaced_transhuge_page() skips page migration's usual
	 * check on page_count(), so we must करो it here, now that the page
	 * has been isolated: a GUP pin, or any other pin, prevents migration.
	 * The expected page count is 3: 1 क्रम page's mapcount and 1 क्रम the
	 * caller's pin and 1 क्रम the reference taken by isolate_lru_page().
	 */
	अगर (PageTransHuge(page) && page_count(page) != 3) अणु
		putback_lru_page(page);
		वापस 0;
	पूर्ण

	page_lru = page_is_file_lru(page);
	mod_node_page_state(page_pgdat(page), NR_ISOLATED_ANON + page_lru,
				thp_nr_pages(page));

	/*
	 * Isolating the page has taken another reference, so the
	 * caller's reference can be safely dropped without the page
	 * disappearing underneath us during migration.
	 */
	put_page(page);
	वापस 1;
पूर्ण

bool pmd_trans_migrating(pmd_t pmd)
अणु
	काष्ठा page *page = pmd_page(pmd);
	वापस PageLocked(page);
पूर्ण

/*
 * Attempt to migrate a misplaced page to the specअगरied destination
 * node. Caller is expected to have an elevated reference count on
 * the page that will be dropped by this function beक्रमe वापसing.
 */
पूर्णांक migrate_misplaced_page(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma,
			   पूर्णांक node)
अणु
	pg_data_t *pgdat = NODE_DATA(node);
	पूर्णांक isolated;
	पूर्णांक nr_reमुख्यing;
	LIST_HEAD(migratepages);

	/*
	 * Don't migrate file pages that are mapped in multiple processes
	 * with execute permissions as they are probably shared libraries.
	 */
	अगर (page_mapcount(page) != 1 && page_is_file_lru(page) &&
	    (vma->vm_flags & VM_EXEC))
		जाओ out;

	/*
	 * Also करो not migrate dirty pages as not all fileप्रणालीs can move
	 * dirty pages in MIGRATE_ASYNC mode which is a waste of cycles.
	 */
	अगर (page_is_file_lru(page) && PageDirty(page))
		जाओ out;

	isolated = numamigrate_isolate_page(pgdat, page);
	अगर (!isolated)
		जाओ out;

	list_add(&page->lru, &migratepages);
	nr_reमुख्यing = migrate_pages(&migratepages, alloc_misplaced_dst_page,
				     शून्य, node, MIGRATE_ASYNC,
				     MR_NUMA_MISPLACED);
	अगर (nr_reमुख्यing) अणु
		अगर (!list_empty(&migratepages)) अणु
			list_del(&page->lru);
			dec_node_page_state(page, NR_ISOLATED_ANON +
					page_is_file_lru(page));
			putback_lru_page(page);
		पूर्ण
		isolated = 0;
	पूर्ण अन्यथा
		count_vm_numa_event(NUMA_PAGE_MIGRATE);
	BUG_ON(!list_empty(&migratepages));
	वापस isolated;

out:
	put_page(page);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#अगर defined(CONFIG_NUMA_BALANCING) && defined(CONFIG_TRANSPARENT_HUGEPAGE)
/*
 * Migrates a THP to a given target node. page must be locked and is unlocked
 * beक्रमe वापसing.
 */
पूर्णांक migrate_misplaced_transhuge_page(काष्ठा mm_काष्ठा *mm,
				काष्ठा vm_area_काष्ठा *vma,
				pmd_t *pmd, pmd_t entry,
				अचिन्हित दीर्घ address,
				काष्ठा page *page, पूर्णांक node)
अणु
	spinlock_t *ptl;
	pg_data_t *pgdat = NODE_DATA(node);
	पूर्णांक isolated = 0;
	काष्ठा page *new_page = शून्य;
	पूर्णांक page_lru = page_is_file_lru(page);
	अचिन्हित दीर्घ start = address & HPAGE_PMD_MASK;

	new_page = alloc_pages_node(node,
		(GFP_TRANSHUGE_LIGHT | __GFP_THISNODE),
		HPAGE_PMD_ORDER);
	अगर (!new_page)
		जाओ out_fail;
	prep_transhuge_page(new_page);

	isolated = numamigrate_isolate_page(pgdat, page);
	अगर (!isolated) अणु
		put_page(new_page);
		जाओ out_fail;
	पूर्ण

	/* Prepare a page as a migration target */
	__SetPageLocked(new_page);
	अगर (PageSwapBacked(page))
		__SetPageSwapBacked(new_page);

	/* anon mapping, we can simply copy page->mapping to the new page: */
	new_page->mapping = page->mapping;
	new_page->index = page->index;
	/* flush the cache beक्रमe copying using the kernel भव address */
	flush_cache_range(vma, start, start + HPAGE_PMD_SIZE);
	migrate_page_copy(new_page, page);
	WARN_ON(PageLRU(new_page));

	/* Recheck the target PMD */
	ptl = pmd_lock(mm, pmd);
	अगर (unlikely(!pmd_same(*pmd, entry) || !page_ref_मुक्तze(page, 2))) अणु
		spin_unlock(ptl);

		/* Reverse changes made by migrate_page_copy() */
		अगर (TestClearPageActive(new_page))
			SetPageActive(page);
		अगर (TestClearPageUnevictable(new_page))
			SetPageUnevictable(page);

		unlock_page(new_page);
		put_page(new_page);		/* Free it */

		/* Retake the callers reference and putback on LRU */
		get_page(page);
		putback_lru_page(page);
		mod_node_page_state(page_pgdat(page),
			 NR_ISOLATED_ANON + page_lru, -HPAGE_PMD_NR);

		जाओ out_unlock;
	पूर्ण

	entry = mk_huge_pmd(new_page, vma->vm_page_prot);
	entry = maybe_pmd_mkग_लिखो(pmd_सूची_गढ़ोty(entry), vma);

	/*
	 * Overग_लिखो the old entry under pagetable lock and establish
	 * the new PTE. Any parallel GUP will either observe the old
	 * page blocking on the page lock, block on the page table
	 * lock or observe the new page. The SetPageUptodate on the
	 * new page and page_add_new_anon_rmap guarantee the copy is
	 * visible beक्रमe the pagetable update.
	 */
	page_add_anon_rmap(new_page, vma, start, true);
	/*
	 * At this poपूर्णांक the pmd is numa/protnone (i.e. non present) and the TLB
	 * has alपढ़ोy been flushed globally.  So no TLB can be currently
	 * caching this non present pmd mapping.  There's no need to clear the
	 * pmd beक्रमe करोing set_pmd_at(), nor to flush the TLB after
	 * set_pmd_at().  Clearing the pmd here would पूर्णांकroduce a race
	 * condition against MADV_DONTNEED, because MADV_DONTNEED only holds the
	 * mmap_lock क्रम पढ़ोing.  If the pmd is set to शून्य at any given समय,
	 * MADV_DONTNEED won't wait on the pmd lock and it'll skip clearing this
	 * pmd.
	 */
	set_pmd_at(mm, start, pmd, entry);
	update_mmu_cache_pmd(vma, address, &entry);

	page_ref_unमुक्तze(page, 2);
	mlock_migrate_page(new_page, page);
	page_हटाओ_rmap(page, true);
	set_page_owner_migrate_reason(new_page, MR_NUMA_MISPLACED);

	spin_unlock(ptl);

	/* Take an "isolate" reference and put new page on the LRU. */
	get_page(new_page);
	putback_lru_page(new_page);

	unlock_page(new_page);
	unlock_page(page);
	put_page(page);			/* Drop the rmap reference */
	put_page(page);			/* Drop the LRU isolation reference */

	count_vm_events(PGMIGRATE_SUCCESS, HPAGE_PMD_NR);
	count_vm_numa_events(NUMA_PAGE_MIGRATE, HPAGE_PMD_NR);

	mod_node_page_state(page_pgdat(page),
			NR_ISOLATED_ANON + page_lru,
			-HPAGE_PMD_NR);
	वापस isolated;

out_fail:
	count_vm_events(PGMIGRATE_FAIL, HPAGE_PMD_NR);
	ptl = pmd_lock(mm, pmd);
	अगर (pmd_same(*pmd, entry)) अणु
		entry = pmd_modअगरy(entry, vma->vm_page_prot);
		set_pmd_at(mm, start, pmd, entry);
		update_mmu_cache_pmd(vma, address, &entry);
	पूर्ण
	spin_unlock(ptl);

out_unlock:
	unlock_page(page);
	put_page(page);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#पूर्ण_अगर /* CONFIG_NUMA */

#अगर_घोषित CONFIG_DEVICE_PRIVATE
अटल पूर्णांक migrate_vma_collect_skip(अचिन्हित दीर्घ start,
				    अचिन्हित दीर्घ end,
				    काष्ठा mm_walk *walk)
अणु
	काष्ठा migrate_vma *migrate = walk->निजी;
	अचिन्हित दीर्घ addr;

	क्रम (addr = start; addr < end; addr += PAGE_SIZE) अणु
		migrate->dst[migrate->npages] = 0;
		migrate->src[migrate->npages++] = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक migrate_vma_collect_hole(अचिन्हित दीर्घ start,
				    अचिन्हित दीर्घ end,
				    __always_unused पूर्णांक depth,
				    काष्ठा mm_walk *walk)
अणु
	काष्ठा migrate_vma *migrate = walk->निजी;
	अचिन्हित दीर्घ addr;

	/* Only allow populating anonymous memory. */
	अगर (!vma_is_anonymous(walk->vma))
		वापस migrate_vma_collect_skip(start, end, walk);

	क्रम (addr = start; addr < end; addr += PAGE_SIZE) अणु
		migrate->src[migrate->npages] = MIGRATE_PFN_MIGRATE;
		migrate->dst[migrate->npages] = 0;
		migrate->npages++;
		migrate->cpages++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक migrate_vma_collect_pmd(pmd_t *pmdp,
				   अचिन्हित दीर्घ start,
				   अचिन्हित दीर्घ end,
				   काष्ठा mm_walk *walk)
अणु
	काष्ठा migrate_vma *migrate = walk->निजी;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ addr = start, unmapped = 0;
	spinlock_t *ptl;
	pte_t *ptep;

again:
	अगर (pmd_none(*pmdp))
		वापस migrate_vma_collect_hole(start, end, -1, walk);

	अगर (pmd_trans_huge(*pmdp)) अणु
		काष्ठा page *page;

		ptl = pmd_lock(mm, pmdp);
		अगर (unlikely(!pmd_trans_huge(*pmdp))) अणु
			spin_unlock(ptl);
			जाओ again;
		पूर्ण

		page = pmd_page(*pmdp);
		अगर (is_huge_zero_page(page)) अणु
			spin_unlock(ptl);
			split_huge_pmd(vma, pmdp, addr);
			अगर (pmd_trans_unstable(pmdp))
				वापस migrate_vma_collect_skip(start, end,
								walk);
		पूर्ण अन्यथा अणु
			पूर्णांक ret;

			get_page(page);
			spin_unlock(ptl);
			अगर (unlikely(!trylock_page(page)))
				वापस migrate_vma_collect_skip(start, end,
								walk);
			ret = split_huge_page(page);
			unlock_page(page);
			put_page(page);
			अगर (ret)
				वापस migrate_vma_collect_skip(start, end,
								walk);
			अगर (pmd_none(*pmdp))
				वापस migrate_vma_collect_hole(start, end, -1,
								walk);
		पूर्ण
	पूर्ण

	अगर (unlikely(pmd_bad(*pmdp)))
		वापस migrate_vma_collect_skip(start, end, walk);

	ptep = pte_offset_map_lock(mm, pmdp, addr, &ptl);
	arch_enter_lazy_mmu_mode();

	क्रम (; addr < end; addr += PAGE_SIZE, ptep++) अणु
		अचिन्हित दीर्घ mpfn = 0, pfn;
		काष्ठा page *page;
		swp_entry_t entry;
		pte_t pte;

		pte = *ptep;

		अगर (pte_none(pte)) अणु
			अगर (vma_is_anonymous(vma)) अणु
				mpfn = MIGRATE_PFN_MIGRATE;
				migrate->cpages++;
			पूर्ण
			जाओ next;
		पूर्ण

		अगर (!pte_present(pte)) अणु
			/*
			 * Only care about unaddressable device page special
			 * page table entry. Other special swap entries are not
			 * migratable, and we ignore regular swapped page.
			 */
			entry = pte_to_swp_entry(pte);
			अगर (!is_device_निजी_entry(entry))
				जाओ next;

			page = device_निजी_entry_to_page(entry);
			अगर (!(migrate->flags &
				MIGRATE_VMA_SELECT_DEVICE_PRIVATE) ||
			    page->pgmap->owner != migrate->pgmap_owner)
				जाओ next;

			mpfn = migrate_pfn(page_to_pfn(page)) |
					MIGRATE_PFN_MIGRATE;
			अगर (is_ग_लिखो_device_निजी_entry(entry))
				mpfn |= MIGRATE_PFN_WRITE;
		पूर्ण अन्यथा अणु
			अगर (!(migrate->flags & MIGRATE_VMA_SELECT_SYSTEM))
				जाओ next;
			pfn = pte_pfn(pte);
			अगर (is_zero_pfn(pfn)) अणु
				mpfn = MIGRATE_PFN_MIGRATE;
				migrate->cpages++;
				जाओ next;
			पूर्ण
			page = vm_normal_page(migrate->vma, addr, pte);
			mpfn = migrate_pfn(pfn) | MIGRATE_PFN_MIGRATE;
			mpfn |= pte_ग_लिखो(pte) ? MIGRATE_PFN_WRITE : 0;
		पूर्ण

		/* FIXME support THP */
		अगर (!page || !page->mapping || PageTransCompound(page)) अणु
			mpfn = 0;
			जाओ next;
		पूर्ण

		/*
		 * By getting a reference on the page we pin it and that blocks
		 * any kind of migration. Side effect is that it "freezes" the
		 * pte.
		 *
		 * We drop this reference after isolating the page from the lru
		 * क्रम non device page (device page are not on the lru and thus
		 * can't be dropped from it).
		 */
		get_page(page);
		migrate->cpages++;

		/*
		 * Optimize क्रम the common हाल where page is only mapped once
		 * in one process. If we can lock the page, then we can safely
		 * set up a special migration page table entry now.
		 */
		अगर (trylock_page(page)) अणु
			pte_t swp_pte;

			mpfn |= MIGRATE_PFN_LOCKED;
			ptep_get_and_clear(mm, addr, ptep);

			/* Setup special migration page table entry */
			entry = make_migration_entry(page, mpfn &
						     MIGRATE_PFN_WRITE);
			swp_pte = swp_entry_to_pte(entry);
			अगर (pte_present(pte)) अणु
				अगर (pte_soft_dirty(pte))
					swp_pte = pte_swp_mksoft_dirty(swp_pte);
				अगर (pte_uffd_wp(pte))
					swp_pte = pte_swp_mkuffd_wp(swp_pte);
			पूर्ण अन्यथा अणु
				अगर (pte_swp_soft_dirty(pte))
					swp_pte = pte_swp_mksoft_dirty(swp_pte);
				अगर (pte_swp_uffd_wp(pte))
					swp_pte = pte_swp_mkuffd_wp(swp_pte);
			पूर्ण
			set_pte_at(mm, addr, ptep, swp_pte);

			/*
			 * This is like regular unmap: we हटाओ the rmap and
			 * drop page refcount. Page won't be मुक्तd, as we took
			 * a reference just above.
			 */
			page_हटाओ_rmap(page, false);
			put_page(page);

			अगर (pte_present(pte))
				unmapped++;
		पूर्ण

next:
		migrate->dst[migrate->npages] = 0;
		migrate->src[migrate->npages++] = mpfn;
	पूर्ण
	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(ptep - 1, ptl);

	/* Only flush the TLB अगर we actually modअगरied any entries */
	अगर (unmapped)
		flush_tlb_range(walk->vma, start, end);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops migrate_vma_walk_ops = अणु
	.pmd_entry		= migrate_vma_collect_pmd,
	.pte_hole		= migrate_vma_collect_hole,
पूर्ण;

/*
 * migrate_vma_collect() - collect pages over a range of भव addresses
 * @migrate: migrate काष्ठा containing all migration inक्रमmation
 *
 * This will walk the CPU page table. For each भव address backed by a
 * valid page, it updates the src array and takes a reference on the page, in
 * order to pin the page until we lock it and unmap it.
 */
अटल व्योम migrate_vma_collect(काष्ठा migrate_vma *migrate)
अणु
	काष्ठा mmu_notअगरier_range range;

	/*
	 * Note that the pgmap_owner is passed to the mmu notअगरier callback so
	 * that the रेजिस्टरed device driver can skip invalidating device
	 * निजी page mappings that won't be migrated.
	 */
	mmu_notअगरier_range_init_migrate(&range, 0, migrate->vma,
		migrate->vma->vm_mm, migrate->start, migrate->end,
		migrate->pgmap_owner);
	mmu_notअगरier_invalidate_range_start(&range);

	walk_page_range(migrate->vma->vm_mm, migrate->start, migrate->end,
			&migrate_vma_walk_ops, migrate);

	mmu_notअगरier_invalidate_range_end(&range);
	migrate->end = migrate->start + (migrate->npages << PAGE_SHIFT);
पूर्ण

/*
 * migrate_vma_check_page() - check अगर page is pinned or not
 * @page: काष्ठा page to check
 *
 * Pinned pages cannot be migrated. This is the same test as in
 * migrate_page_move_mapping(), except that here we allow migration of a
 * ZONE_DEVICE page.
 */
अटल bool migrate_vma_check_page(काष्ठा page *page)
अणु
	/*
	 * One extra ref because caller holds an extra reference, either from
	 * isolate_lru_page() क्रम a regular page, or migrate_vma_collect() क्रम
	 * a device page.
	 */
	पूर्णांक extra = 1;

	/*
	 * FIXME support THP (transparent huge page), it is bit more complex to
	 * check them than regular pages, because they can be mapped with a pmd
	 * or with a pte (split pte mapping).
	 */
	अगर (PageCompound(page))
		वापस false;

	/* Page from ZONE_DEVICE have one extra reference */
	अगर (is_zone_device_page(page)) अणु
		/*
		 * Private page can never be pin as they have no valid pte and
		 * GUP will fail क्रम those. Yet अगर there is a pending migration
		 * a thपढ़ो might try to रुको on the pte migration entry and
		 * will bump the page reference count. Sadly there is no way to
		 * dअगरferentiate a regular pin from migration रुको. Hence to
		 * aव्योम 2 racing thपढ़ो trying to migrate back to CPU to enter
		 * infinite loop (one stopping migration because the other is
		 * रुकोing on pte migration entry). We always वापस true here.
		 *
		 * FIXME proper solution is to rework migration_entry_रुको() so
		 * it करोes not need to take a reference on page.
		 */
		वापस is_device_निजी_page(page);
	पूर्ण

	/* For file back page */
	अगर (page_mapping(page))
		extra += 1 + page_has_निजी(page);

	अगर ((page_count(page) - extra) > page_mapcount(page))
		वापस false;

	वापस true;
पूर्ण

/*
 * migrate_vma_prepare() - lock pages and isolate them from the lru
 * @migrate: migrate काष्ठा containing all migration inक्रमmation
 *
 * This locks pages that have been collected by migrate_vma_collect(). Once each
 * page is locked it is isolated from the lru (क्रम non-device pages). Finally,
 * the ref taken by migrate_vma_collect() is dropped, as locked pages cannot be
 * migrated by concurrent kernel thपढ़ोs.
 */
अटल व्योम migrate_vma_prepare(काष्ठा migrate_vma *migrate)
अणु
	स्थिर अचिन्हित दीर्घ npages = migrate->npages;
	स्थिर अचिन्हित दीर्घ start = migrate->start;
	अचिन्हित दीर्घ addr, i, restore = 0;
	bool allow_drain = true;

	lru_add_drain();

	क्रम (i = 0; (i < npages) && migrate->cpages; i++) अणु
		काष्ठा page *page = migrate_pfn_to_page(migrate->src[i]);
		bool remap = true;

		अगर (!page)
			जारी;

		अगर (!(migrate->src[i] & MIGRATE_PFN_LOCKED)) अणु
			/*
			 * Because we are migrating several pages there can be
			 * a deadlock between 2 concurrent migration where each
			 * are रुकोing on each other page lock.
			 *
			 * Make migrate_vma() a best efक्रमt thing and backoff
			 * क्रम any page we can not lock right away.
			 */
			अगर (!trylock_page(page)) अणु
				migrate->src[i] = 0;
				migrate->cpages--;
				put_page(page);
				जारी;
			पूर्ण
			remap = false;
			migrate->src[i] |= MIGRATE_PFN_LOCKED;
		पूर्ण

		/* ZONE_DEVICE pages are not on LRU */
		अगर (!is_zone_device_page(page)) अणु
			अगर (!PageLRU(page) && allow_drain) अणु
				/* Drain CPU's pagevec */
				lru_add_drain_all();
				allow_drain = false;
			पूर्ण

			अगर (isolate_lru_page(page)) अणु
				अगर (remap) अणु
					migrate->src[i] &= ~MIGRATE_PFN_MIGRATE;
					migrate->cpages--;
					restore++;
				पूर्ण अन्यथा अणु
					migrate->src[i] = 0;
					unlock_page(page);
					migrate->cpages--;
					put_page(page);
				पूर्ण
				जारी;
			पूर्ण

			/* Drop the reference we took in collect */
			put_page(page);
		पूर्ण

		अगर (!migrate_vma_check_page(page)) अणु
			अगर (remap) अणु
				migrate->src[i] &= ~MIGRATE_PFN_MIGRATE;
				migrate->cpages--;
				restore++;

				अगर (!is_zone_device_page(page)) अणु
					get_page(page);
					putback_lru_page(page);
				पूर्ण
			पूर्ण अन्यथा अणु
				migrate->src[i] = 0;
				unlock_page(page);
				migrate->cpages--;

				अगर (!is_zone_device_page(page))
					putback_lru_page(page);
				अन्यथा
					put_page(page);
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0, addr = start; i < npages && restore; i++, addr += PAGE_SIZE) अणु
		काष्ठा page *page = migrate_pfn_to_page(migrate->src[i]);

		अगर (!page || (migrate->src[i] & MIGRATE_PFN_MIGRATE))
			जारी;

		हटाओ_migration_pte(page, migrate->vma, addr, page);

		migrate->src[i] = 0;
		unlock_page(page);
		put_page(page);
		restore--;
	पूर्ण
पूर्ण

/*
 * migrate_vma_unmap() - replace page mapping with special migration pte entry
 * @migrate: migrate काष्ठा containing all migration inक्रमmation
 *
 * Replace page mapping (CPU page table pte) with a special migration pte entry
 * and check again अगर it has been pinned. Pinned pages are restored because we
 * cannot migrate them.
 *
 * This is the last step beक्रमe we call the device driver callback to allocate
 * destination memory and copy contents of original page over to new page.
 */
अटल व्योम migrate_vma_unmap(काष्ठा migrate_vma *migrate)
अणु
	पूर्णांक flags = TTU_MIGRATION | TTU_IGNORE_MLOCK;
	स्थिर अचिन्हित दीर्घ npages = migrate->npages;
	स्थिर अचिन्हित दीर्घ start = migrate->start;
	अचिन्हित दीर्घ addr, i, restore = 0;

	क्रम (i = 0; i < npages; i++) अणु
		काष्ठा page *page = migrate_pfn_to_page(migrate->src[i]);

		अगर (!page || !(migrate->src[i] & MIGRATE_PFN_MIGRATE))
			जारी;

		अगर (page_mapped(page)) अणु
			try_to_unmap(page, flags);
			अगर (page_mapped(page))
				जाओ restore;
		पूर्ण

		अगर (migrate_vma_check_page(page))
			जारी;

restore:
		migrate->src[i] &= ~MIGRATE_PFN_MIGRATE;
		migrate->cpages--;
		restore++;
	पूर्ण

	क्रम (addr = start, i = 0; i < npages && restore; addr += PAGE_SIZE, i++) अणु
		काष्ठा page *page = migrate_pfn_to_page(migrate->src[i]);

		अगर (!page || (migrate->src[i] & MIGRATE_PFN_MIGRATE))
			जारी;

		हटाओ_migration_ptes(page, page, false);

		migrate->src[i] = 0;
		unlock_page(page);
		restore--;

		अगर (is_zone_device_page(page))
			put_page(page);
		अन्यथा
			putback_lru_page(page);
	पूर्ण
पूर्ण

/**
 * migrate_vma_setup() - prepare to migrate a range of memory
 * @args: contains the vma, start, and pfns arrays क्रम the migration
 *
 * Returns: negative त्रुटि_सं on failures, 0 when 0 or more pages were migrated
 * without an error.
 *
 * Prepare to migrate a range of memory भव address range by collecting all
 * the pages backing each भव address in the range, saving them inside the
 * src array.  Then lock those pages and unmap them. Once the pages are locked
 * and unmapped, check whether each page is pinned or not.  Pages that aren't
 * pinned have the MIGRATE_PFN_MIGRATE flag set (by this function) in the
 * corresponding src array entry.  Then restores any pages that are pinned, by
 * remapping and unlocking those pages.
 *
 * The caller should then allocate destination memory and copy source memory to
 * it क्रम all those entries (ie with MIGRATE_PFN_VALID and MIGRATE_PFN_MIGRATE
 * flag set).  Once these are allocated and copied, the caller must update each
 * corresponding entry in the dst array with the pfn value of the destination
 * page and with the MIGRATE_PFN_VALID and MIGRATE_PFN_LOCKED flags set
 * (destination pages must have their काष्ठा pages locked, via lock_page()).
 *
 * Note that the caller करोes not have to migrate all the pages that are marked
 * with MIGRATE_PFN_MIGRATE flag in src array unless this is a migration from
 * device memory to प्रणाली memory.  If the caller cannot migrate a device page
 * back to प्रणाली memory, then it must वापस VM_FAULT_SIGBUS, which has severe
 * consequences क्रम the userspace process, so it must be aव्योमed अगर at all
 * possible.
 *
 * For empty entries inside CPU page table (pte_none() or pmd_none() is true) we
 * करो set MIGRATE_PFN_MIGRATE flag inside the corresponding source array thus
 * allowing the caller to allocate device memory क्रम those unbacked भव
 * addresses.  For this the caller simply has to allocate device memory and
 * properly set the destination entry like क्रम regular migration.  Note that
 * this can still fail, and thus inside the device driver you must check अगर the
 * migration was successful क्रम those entries after calling migrate_vma_pages(),
 * just like क्रम regular migration.
 *
 * After that, the callers must call migrate_vma_pages() to go over each entry
 * in the src array that has the MIGRATE_PFN_VALID and MIGRATE_PFN_MIGRATE flag
 * set. If the corresponding entry in dst array has MIGRATE_PFN_VALID flag set,
 * then migrate_vma_pages() to migrate काष्ठा page inक्रमmation from the source
 * काष्ठा page to the destination काष्ठा page.  If it fails to migrate the
 * काष्ठा page inक्रमmation, then it clears the MIGRATE_PFN_MIGRATE flag in the
 * src array.
 *
 * At this poपूर्णांक all successfully migrated pages have an entry in the src
 * array with MIGRATE_PFN_VALID and MIGRATE_PFN_MIGRATE flag set and the dst
 * array entry with MIGRATE_PFN_VALID flag set.
 *
 * Once migrate_vma_pages() वापसs the caller may inspect which pages were
 * successfully migrated, and which were not.  Successfully migrated pages will
 * have the MIGRATE_PFN_MIGRATE flag set क्रम their src array entry.
 *
 * It is safe to update device page table after migrate_vma_pages() because
 * both destination and source page are still locked, and the mmap_lock is held
 * in पढ़ो mode (hence no one can unmap the range being migrated).
 *
 * Once the caller is करोne cleaning up things and updating its page table (अगर it
 * chose to करो so, this is not an obligation) it finally calls
 * migrate_vma_finalize() to update the CPU page table to poपूर्णांक to new pages
 * क्रम successfully migrated pages or otherwise restore the CPU page table to
 * poपूर्णांक to the original source pages.
 */
पूर्णांक migrate_vma_setup(काष्ठा migrate_vma *args)
अणु
	दीर्घ nr_pages = (args->end - args->start) >> PAGE_SHIFT;

	args->start &= PAGE_MASK;
	args->end &= PAGE_MASK;
	अगर (!args->vma || is_vm_hugetlb_page(args->vma) ||
	    (args->vma->vm_flags & VM_SPECIAL) || vma_is_dax(args->vma))
		वापस -EINVAL;
	अगर (nr_pages <= 0)
		वापस -EINVAL;
	अगर (args->start < args->vma->vm_start ||
	    args->start >= args->vma->vm_end)
		वापस -EINVAL;
	अगर (args->end <= args->vma->vm_start || args->end > args->vma->vm_end)
		वापस -EINVAL;
	अगर (!args->src || !args->dst)
		वापस -EINVAL;

	स_रखो(args->src, 0, माप(*args->src) * nr_pages);
	args->cpages = 0;
	args->npages = 0;

	migrate_vma_collect(args);

	अगर (args->cpages)
		migrate_vma_prepare(args);
	अगर (args->cpages)
		migrate_vma_unmap(args);

	/*
	 * At this poपूर्णांक pages are locked and unmapped, and thus they have
	 * stable content and can safely be copied to destination memory that
	 * is allocated by the drivers.
	 */
	वापस 0;

पूर्ण
EXPORT_SYMBOL(migrate_vma_setup);

/*
 * This code बंदly matches the code in:
 *   __handle_mm_fault()
 *     handle_pte_fault()
 *       करो_anonymous_page()
 * to map in an anonymous zero page but the काष्ठा page will be a ZONE_DEVICE
 * निजी page.
 */
अटल व्योम migrate_vma_insert_page(काष्ठा migrate_vma *migrate,
				    अचिन्हित दीर्घ addr,
				    काष्ठा page *page,
				    अचिन्हित दीर्घ *src)
अणु
	काष्ठा vm_area_काष्ठा *vma = migrate->vma;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	bool flush = false;
	spinlock_t *ptl;
	pte_t entry;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	/* Only allow populating anonymous memory */
	अगर (!vma_is_anonymous(vma))
		जाओ पात;

	pgdp = pgd_offset(mm, addr);
	p4dp = p4d_alloc(mm, pgdp, addr);
	अगर (!p4dp)
		जाओ पात;
	pudp = pud_alloc(mm, p4dp, addr);
	अगर (!pudp)
		जाओ पात;
	pmdp = pmd_alloc(mm, pudp, addr);
	अगर (!pmdp)
		जाओ पात;

	अगर (pmd_trans_huge(*pmdp) || pmd_devmap(*pmdp))
		जाओ पात;

	/*
	 * Use pte_alloc() instead of pte_alloc_map().  We can't run
	 * pte_offset_map() on pmds where a huge pmd might be created
	 * from a dअगरferent thपढ़ो.
	 *
	 * pte_alloc_map() is safe to use under mmap_ग_लिखो_lock(mm) or when
	 * parallel thपढ़ोs are excluded by other means.
	 *
	 * Here we only have mmap_पढ़ो_lock(mm).
	 */
	अगर (pte_alloc(mm, pmdp))
		जाओ पात;

	/* See the comment in pte_alloc_one_map() */
	अगर (unlikely(pmd_trans_unstable(pmdp)))
		जाओ पात;

	अगर (unlikely(anon_vma_prepare(vma)))
		जाओ पात;
	अगर (mem_cgroup_अक्षरge(page, vma->vm_mm, GFP_KERNEL))
		जाओ पात;

	/*
	 * The memory barrier inside __SetPageUptodate makes sure that
	 * preceding stores to the page contents become visible beक्रमe
	 * the set_pte_at() ग_लिखो.
	 */
	__SetPageUptodate(page);

	अगर (is_zone_device_page(page)) अणु
		अगर (is_device_निजी_page(page)) अणु
			swp_entry_t swp_entry;

			swp_entry = make_device_निजी_entry(page, vma->vm_flags & VM_WRITE);
			entry = swp_entry_to_pte(swp_entry);
		पूर्ण अन्यथा अणु
			/*
			 * For now we only support migrating to un-addressable
			 * device memory.
			 */
			pr_warn_once("Unsupported ZONE_DEVICE page type.\n");
			जाओ पात;
		पूर्ण
	पूर्ण अन्यथा अणु
		entry = mk_pte(page, vma->vm_page_prot);
		अगर (vma->vm_flags & VM_WRITE)
			entry = pte_mkग_लिखो(pte_सूची_गढ़ोty(entry));
	पूर्ण

	ptep = pte_offset_map_lock(mm, pmdp, addr, &ptl);

	अगर (check_stable_address_space(mm))
		जाओ unlock_पात;

	अगर (pte_present(*ptep)) अणु
		अचिन्हित दीर्घ pfn = pte_pfn(*ptep);

		अगर (!is_zero_pfn(pfn))
			जाओ unlock_पात;
		flush = true;
	पूर्ण अन्यथा अगर (!pte_none(*ptep))
		जाओ unlock_पात;

	/*
	 * Check क्रम userfaultfd but करो not deliver the fault. Instead,
	 * just back off.
	 */
	अगर (userfaultfd_missing(vma))
		जाओ unlock_पात;

	inc_mm_counter(mm, MM_ANONPAGES);
	page_add_new_anon_rmap(page, vma, addr, false);
	अगर (!is_zone_device_page(page))
		lru_cache_add_inactive_or_unevictable(page, vma);
	get_page(page);

	अगर (flush) अणु
		flush_cache_page(vma, addr, pte_pfn(*ptep));
		ptep_clear_flush_notअगरy(vma, addr, ptep);
		set_pte_at_notअगरy(mm, addr, ptep, entry);
		update_mmu_cache(vma, addr, ptep);
	पूर्ण अन्यथा अणु
		/* No need to invalidate - it was non-present beक्रमe */
		set_pte_at(mm, addr, ptep, entry);
		update_mmu_cache(vma, addr, ptep);
	पूर्ण

	pte_unmap_unlock(ptep, ptl);
	*src = MIGRATE_PFN_MIGRATE;
	वापस;

unlock_पात:
	pte_unmap_unlock(ptep, ptl);
पात:
	*src &= ~MIGRATE_PFN_MIGRATE;
पूर्ण

/**
 * migrate_vma_pages() - migrate meta-data from src page to dst page
 * @migrate: migrate काष्ठा containing all migration inक्रमmation
 *
 * This migrates काष्ठा page meta-data from source काष्ठा page to destination
 * काष्ठा page. This effectively finishes the migration from source page to the
 * destination page.
 */
व्योम migrate_vma_pages(काष्ठा migrate_vma *migrate)
अणु
	स्थिर अचिन्हित दीर्घ npages = migrate->npages;
	स्थिर अचिन्हित दीर्घ start = migrate->start;
	काष्ठा mmu_notअगरier_range range;
	अचिन्हित दीर्घ addr, i;
	bool notअगरied = false;

	क्रम (i = 0, addr = start; i < npages; addr += PAGE_SIZE, i++) अणु
		काष्ठा page *newpage = migrate_pfn_to_page(migrate->dst[i]);
		काष्ठा page *page = migrate_pfn_to_page(migrate->src[i]);
		काष्ठा address_space *mapping;
		पूर्णांक r;

		अगर (!newpage) अणु
			migrate->src[i] &= ~MIGRATE_PFN_MIGRATE;
			जारी;
		पूर्ण

		अगर (!page) अणु
			अगर (!(migrate->src[i] & MIGRATE_PFN_MIGRATE))
				जारी;
			अगर (!notअगरied) अणु
				notअगरied = true;

				mmu_notअगरier_range_init_migrate(&range, 0,
					migrate->vma, migrate->vma->vm_mm,
					addr, migrate->end,
					migrate->pgmap_owner);
				mmu_notअगरier_invalidate_range_start(&range);
			पूर्ण
			migrate_vma_insert_page(migrate, addr, newpage,
						&migrate->src[i]);
			जारी;
		पूर्ण

		mapping = page_mapping(page);

		अगर (is_zone_device_page(newpage)) अणु
			अगर (is_device_निजी_page(newpage)) अणु
				/*
				 * For now only support निजी anonymous when
				 * migrating to un-addressable device memory.
				 */
				अगर (mapping) अणु
					migrate->src[i] &= ~MIGRATE_PFN_MIGRATE;
					जारी;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * Other types of ZONE_DEVICE page are not
				 * supported.
				 */
				migrate->src[i] &= ~MIGRATE_PFN_MIGRATE;
				जारी;
			पूर्ण
		पूर्ण

		r = migrate_page(mapping, newpage, page, MIGRATE_SYNC_NO_COPY);
		अगर (r != MIGRATEPAGE_SUCCESS)
			migrate->src[i] &= ~MIGRATE_PFN_MIGRATE;
	पूर्ण

	/*
	 * No need to द्विगुन call mmu_notअगरier->invalidate_range() callback as
	 * the above ptep_clear_flush_notअगरy() inside migrate_vma_insert_page()
	 * did alपढ़ोy call it.
	 */
	अगर (notअगरied)
		mmu_notअगरier_invalidate_range_only_end(&range);
पूर्ण
EXPORT_SYMBOL(migrate_vma_pages);

/**
 * migrate_vma_finalize() - restore CPU page table entry
 * @migrate: migrate काष्ठा containing all migration inक्रमmation
 *
 * This replaces the special migration pte entry with either a mapping to the
 * new page अगर migration was successful क्रम that page, or to the original page
 * otherwise.
 *
 * This also unlocks the pages and माला_दो them back on the lru, or drops the extra
 * refcount, क्रम device pages.
 */
व्योम migrate_vma_finalize(काष्ठा migrate_vma *migrate)
अणु
	स्थिर अचिन्हित दीर्घ npages = migrate->npages;
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < npages; i++) अणु
		काष्ठा page *newpage = migrate_pfn_to_page(migrate->dst[i]);
		काष्ठा page *page = migrate_pfn_to_page(migrate->src[i]);

		अगर (!page) अणु
			अगर (newpage) अणु
				unlock_page(newpage);
				put_page(newpage);
			पूर्ण
			जारी;
		पूर्ण

		अगर (!(migrate->src[i] & MIGRATE_PFN_MIGRATE) || !newpage) अणु
			अगर (newpage) अणु
				unlock_page(newpage);
				put_page(newpage);
			पूर्ण
			newpage = page;
		पूर्ण

		हटाओ_migration_ptes(page, newpage, false);
		unlock_page(page);

		अगर (is_zone_device_page(page))
			put_page(page);
		अन्यथा
			putback_lru_page(page);

		अगर (newpage != page) अणु
			unlock_page(newpage);
			अगर (is_zone_device_page(newpage))
				put_page(newpage);
			अन्यथा
				putback_lru_page(newpage);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(migrate_vma_finalize);
#पूर्ण_अगर /* CONFIG_DEVICE_PRIVATE */
