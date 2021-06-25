<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/mm/compaction.c
 *
 * Memory compaction क्रम the reduction of बाह्यal fragmentation. Note that
 * this heavily depends upon page migration to करो all the real heavy
 * lअगरting
 *
 * Copyright IBM Corp. 2007-2010 Mel Gorman <mel@csn.ul.ie>
 */
#समावेश <linux/cpu.h>
#समावेश <linux/swap.h>
#समावेश <linux/migrate.h>
#समावेश <linux/compaction.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/page-isolation.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/page_owner.h>
#समावेश <linux/psi.h>
#समावेश "internal.h"

#अगर_घोषित CONFIG_COMPACTION
अटल अंतरभूत व्योम count_compact_event(क्रमागत vm_event_item item)
अणु
	count_vm_event(item);
पूर्ण

अटल अंतरभूत व्योम count_compact_events(क्रमागत vm_event_item item, दीर्घ delta)
अणु
	count_vm_events(item, delta);
पूर्ण
#अन्यथा
#घोषणा count_compact_event(item) करो अणु पूर्ण जबतक (0)
#घोषणा count_compact_events(item, delta) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर defined CONFIG_COMPACTION || defined CONFIG_CMA

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/compaction.h>

#घोषणा block_start_pfn(pfn, order)	round_करोwn(pfn, 1UL << (order))
#घोषणा block_end_pfn(pfn, order)	ALIGN((pfn) + 1, 1UL << (order))
#घोषणा pageblock_start_pfn(pfn)	block_start_pfn(pfn, pageblock_order)
#घोषणा pageblock_end_pfn(pfn)		block_end_pfn(pfn, pageblock_order)

/*
 * Fragmentation score check पूर्णांकerval क्रम proactive compaction purposes.
 */
अटल स्थिर अचिन्हित पूर्णांक HPAGE_FRAG_CHECK_INTERVAL_MSEC = 500;

/*
 * Page order with-respect-to which proactive compaction
 * calculates बाह्यal fragmentation, which is used as
 * the "fragmentation score" of a node/zone.
 */
#अगर defined CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा COMPACTION_HPAGE_ORDER	HPAGE_PMD_ORDER
#या_अगर defined CONFIG_HUGETLBFS
#घोषणा COMPACTION_HPAGE_ORDER	HUGETLB_PAGE_ORDER
#अन्यथा
#घोषणा COMPACTION_HPAGE_ORDER	(PMD_SHIFT - PAGE_SHIFT)
#पूर्ण_अगर

अटल अचिन्हित दीर्घ release_मुक्तpages(काष्ठा list_head *मुक्तlist)
अणु
	काष्ठा page *page, *next;
	अचिन्हित दीर्घ high_pfn = 0;

	list_क्रम_each_entry_safe(page, next, मुक्तlist, lru) अणु
		अचिन्हित दीर्घ pfn = page_to_pfn(page);
		list_del(&page->lru);
		__मुक्त_page(page);
		अगर (pfn > high_pfn)
			high_pfn = pfn;
	पूर्ण

	वापस high_pfn;
पूर्ण

अटल व्योम split_map_pages(काष्ठा list_head *list)
अणु
	अचिन्हित पूर्णांक i, order, nr_pages;
	काष्ठा page *page, *next;
	LIST_HEAD(पंचांगp_list);

	list_क्रम_each_entry_safe(page, next, list, lru) अणु
		list_del(&page->lru);

		order = page_निजी(page);
		nr_pages = 1 << order;

		post_alloc_hook(page, order, __GFP_MOVABLE);
		अगर (order)
			split_page(page, order);

		क्रम (i = 0; i < nr_pages; i++) अणु
			list_add(&page->lru, &पंचांगp_list);
			page++;
		पूर्ण
	पूर्ण

	list_splice(&पंचांगp_list, list);
पूर्ण

#अगर_घोषित CONFIG_COMPACTION

पूर्णांक PageMovable(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	अगर (!__PageMovable(page))
		वापस 0;

	mapping = page_mapping(page);
	अगर (mapping && mapping->a_ops && mapping->a_ops->isolate_page)
		वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(PageMovable);

व्योम __SetPageMovable(काष्ठा page *page, काष्ठा address_space *mapping)
अणु
	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE((अचिन्हित दीर्घ)mapping & PAGE_MAPPING_MOVABLE, page);
	page->mapping = (व्योम *)((अचिन्हित दीर्घ)mapping | PAGE_MAPPING_MOVABLE);
पूर्ण
EXPORT_SYMBOL(__SetPageMovable);

व्योम __ClearPageMovable(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!PageMovable(page), page);
	/*
	 * Clear रेजिस्टरed address_space val with keeping PAGE_MAPPING_MOVABLE
	 * flag so that VM can catch up released page by driver after isolation.
	 * With it, VM migration करोesn't try to put it back.
	 */
	page->mapping = (व्योम *)((अचिन्हित दीर्घ)page->mapping &
				PAGE_MAPPING_MOVABLE);
पूर्ण
EXPORT_SYMBOL(__ClearPageMovable);

/* Do not skip compaction more than 64 बार */
#घोषणा COMPACT_MAX_DEFER_SHIFT 6

/*
 * Compaction is deferred when compaction fails to result in a page
 * allocation success. 1 << compact_defer_shअगरt, compactions are skipped up
 * to a limit of 1 << COMPACT_MAX_DEFER_SHIFT
 */
अटल व्योम defer_compaction(काष्ठा zone *zone, पूर्णांक order)
अणु
	zone->compact_considered = 0;
	zone->compact_defer_shअगरt++;

	अगर (order < zone->compact_order_failed)
		zone->compact_order_failed = order;

	अगर (zone->compact_defer_shअगरt > COMPACT_MAX_DEFER_SHIFT)
		zone->compact_defer_shअगरt = COMPACT_MAX_DEFER_SHIFT;

	trace_mm_compaction_defer_compaction(zone, order);
पूर्ण

/* Returns true अगर compaction should be skipped this समय */
अटल bool compaction_deferred(काष्ठा zone *zone, पूर्णांक order)
अणु
	अचिन्हित दीर्घ defer_limit = 1UL << zone->compact_defer_shअगरt;

	अगर (order < zone->compact_order_failed)
		वापस false;

	/* Aव्योम possible overflow */
	अगर (++zone->compact_considered >= defer_limit) अणु
		zone->compact_considered = defer_limit;
		वापस false;
	पूर्ण

	trace_mm_compaction_deferred(zone, order);

	वापस true;
पूर्ण

/*
 * Update defer tracking counters after successful compaction of given order,
 * which means an allocation either succeeded (alloc_success == true) or is
 * expected to succeed.
 */
व्योम compaction_defer_reset(काष्ठा zone *zone, पूर्णांक order,
		bool alloc_success)
अणु
	अगर (alloc_success) अणु
		zone->compact_considered = 0;
		zone->compact_defer_shअगरt = 0;
	पूर्ण
	अगर (order >= zone->compact_order_failed)
		zone->compact_order_failed = order + 1;

	trace_mm_compaction_defer_reset(zone, order);
पूर्ण

/* Returns true अगर restarting compaction after many failures */
अटल bool compaction_restarting(काष्ठा zone *zone, पूर्णांक order)
अणु
	अगर (order < zone->compact_order_failed)
		वापस false;

	वापस zone->compact_defer_shअगरt == COMPACT_MAX_DEFER_SHIFT &&
		zone->compact_considered >= 1UL << zone->compact_defer_shअगरt;
पूर्ण

/* Returns true अगर the pageblock should be scanned क्रम pages to isolate. */
अटल अंतरभूत bool isolation_suitable(काष्ठा compact_control *cc,
					काष्ठा page *page)
अणु
	अगर (cc->ignore_skip_hपूर्णांक)
		वापस true;

	वापस !get_pageblock_skip(page);
पूर्ण

अटल व्योम reset_cached_positions(काष्ठा zone *zone)
अणु
	zone->compact_cached_migrate_pfn[0] = zone->zone_start_pfn;
	zone->compact_cached_migrate_pfn[1] = zone->zone_start_pfn;
	zone->compact_cached_मुक्त_pfn =
				pageblock_start_pfn(zone_end_pfn(zone) - 1);
पूर्ण

/*
 * Compound pages of >= pageblock_order should consistently be skipped until
 * released. It is always poपूर्णांकless to compact pages of such order (अगर they are
 * migratable), and the pageblocks they occupy cannot contain any मुक्त pages.
 */
अटल bool pageblock_skip_persistent(काष्ठा page *page)
अणु
	अगर (!PageCompound(page))
		वापस false;

	page = compound_head(page);

	अगर (compound_order(page) >= pageblock_order)
		वापस true;

	वापस false;
पूर्ण

अटल bool
__reset_isolation_pfn(काष्ठा zone *zone, अचिन्हित दीर्घ pfn, bool check_source,
							bool check_target)
अणु
	काष्ठा page *page = pfn_to_online_page(pfn);
	काष्ठा page *block_page;
	काष्ठा page *end_page;
	अचिन्हित दीर्घ block_pfn;

	अगर (!page)
		वापस false;
	अगर (zone != page_zone(page))
		वापस false;
	अगर (pageblock_skip_persistent(page))
		वापस false;

	/*
	 * If skip is alपढ़ोy cleared करो no further checking once the
	 * restart poपूर्णांकs have been set.
	 */
	अगर (check_source && check_target && !get_pageblock_skip(page))
		वापस true;

	/*
	 * If clearing skip क्रम the target scanner, करो not select a
	 * non-movable pageblock as the starting poपूर्णांक.
	 */
	अगर (!check_source && check_target &&
	    get_pageblock_migratetype(page) != MIGRATE_MOVABLE)
		वापस false;

	/* Ensure the start of the pageblock or zone is online and valid */
	block_pfn = pageblock_start_pfn(pfn);
	block_pfn = max(block_pfn, zone->zone_start_pfn);
	block_page = pfn_to_online_page(block_pfn);
	अगर (block_page) अणु
		page = block_page;
		pfn = block_pfn;
	पूर्ण

	/* Ensure the end of the pageblock or zone is online and valid */
	block_pfn = pageblock_end_pfn(pfn) - 1;
	block_pfn = min(block_pfn, zone_end_pfn(zone) - 1);
	end_page = pfn_to_online_page(block_pfn);
	अगर (!end_page)
		वापस false;

	/*
	 * Only clear the hपूर्णांक अगर a sample indicates there is either a
	 * मुक्त page or an LRU page in the block. One or other condition
	 * is necessary क्रम the block to be a migration source/target.
	 */
	करो अणु
		अगर (pfn_valid_within(pfn)) अणु
			अगर (check_source && PageLRU(page)) अणु
				clear_pageblock_skip(page);
				वापस true;
			पूर्ण

			अगर (check_target && PageBuddy(page)) अणु
				clear_pageblock_skip(page);
				वापस true;
			पूर्ण
		पूर्ण

		page += (1 << PAGE_ALLOC_COSTLY_ORDER);
		pfn += (1 << PAGE_ALLOC_COSTLY_ORDER);
	पूर्ण जबतक (page <= end_page);

	वापस false;
पूर्ण

/*
 * This function is called to clear all cached inक्रमmation on pageblocks that
 * should be skipped क्रम page isolation when the migrate and मुक्त page scanner
 * meet.
 */
अटल व्योम __reset_isolation_suitable(काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ migrate_pfn = zone->zone_start_pfn;
	अचिन्हित दीर्घ मुक्त_pfn = zone_end_pfn(zone) - 1;
	अचिन्हित दीर्घ reset_migrate = मुक्त_pfn;
	अचिन्हित दीर्घ reset_मुक्त = migrate_pfn;
	bool source_set = false;
	bool मुक्त_set = false;

	अगर (!zone->compact_blockskip_flush)
		वापस;

	zone->compact_blockskip_flush = false;

	/*
	 * Walk the zone and update pageblock skip inक्रमmation. Source looks
	 * क्रम PageLRU जबतक target looks क्रम PageBuddy. When the scanner
	 * is found, both PageBuddy and PageLRU are checked as the pageblock
	 * is suitable as both source and target.
	 */
	क्रम (; migrate_pfn < मुक्त_pfn; migrate_pfn += pageblock_nr_pages,
					मुक्त_pfn -= pageblock_nr_pages) अणु
		cond_resched();

		/* Update the migrate PFN */
		अगर (__reset_isolation_pfn(zone, migrate_pfn, true, source_set) &&
		    migrate_pfn < reset_migrate) अणु
			source_set = true;
			reset_migrate = migrate_pfn;
			zone->compact_init_migrate_pfn = reset_migrate;
			zone->compact_cached_migrate_pfn[0] = reset_migrate;
			zone->compact_cached_migrate_pfn[1] = reset_migrate;
		पूर्ण

		/* Update the मुक्त PFN */
		अगर (__reset_isolation_pfn(zone, मुक्त_pfn, मुक्त_set, true) &&
		    मुक्त_pfn > reset_मुक्त) अणु
			मुक्त_set = true;
			reset_मुक्त = मुक्त_pfn;
			zone->compact_init_मुक्त_pfn = reset_मुक्त;
			zone->compact_cached_मुक्त_pfn = reset_मुक्त;
		पूर्ण
	पूर्ण

	/* Leave no distance अगर no suitable block was reset */
	अगर (reset_migrate >= reset_मुक्त) अणु
		zone->compact_cached_migrate_pfn[0] = migrate_pfn;
		zone->compact_cached_migrate_pfn[1] = migrate_pfn;
		zone->compact_cached_मुक्त_pfn = मुक्त_pfn;
	पूर्ण
पूर्ण

व्योम reset_isolation_suitable(pg_data_t *pgdat)
अणु
	पूर्णांक zoneid;

	क्रम (zoneid = 0; zoneid < MAX_NR_ZONES; zoneid++) अणु
		काष्ठा zone *zone = &pgdat->node_zones[zoneid];
		अगर (!populated_zone(zone))
			जारी;

		/* Only flush अगर a full compaction finished recently */
		अगर (zone->compact_blockskip_flush)
			__reset_isolation_suitable(zone);
	पूर्ण
पूर्ण

/*
 * Sets the pageblock skip bit अगर it was clear. Note that this is a hपूर्णांक as
 * locks are not required क्रम पढ़ो/ग_लिखोrs. Returns true अगर it was alपढ़ोy set.
 */
अटल bool test_and_set_skip(काष्ठा compact_control *cc, काष्ठा page *page,
							अचिन्हित दीर्घ pfn)
अणु
	bool skip;

	/* Do no update अगर skip hपूर्णांक is being ignored */
	अगर (cc->ignore_skip_hपूर्णांक)
		वापस false;

	अगर (!IS_ALIGNED(pfn, pageblock_nr_pages))
		वापस false;

	skip = get_pageblock_skip(page);
	अगर (!skip && !cc->no_set_skip_hपूर्णांक)
		set_pageblock_skip(page);

	वापस skip;
पूर्ण

अटल व्योम update_cached_migrate(काष्ठा compact_control *cc, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा zone *zone = cc->zone;

	pfn = pageblock_end_pfn(pfn);

	/* Set क्रम isolation rather than compaction */
	अगर (cc->no_set_skip_hपूर्णांक)
		वापस;

	अगर (pfn > zone->compact_cached_migrate_pfn[0])
		zone->compact_cached_migrate_pfn[0] = pfn;
	अगर (cc->mode != MIGRATE_ASYNC &&
	    pfn > zone->compact_cached_migrate_pfn[1])
		zone->compact_cached_migrate_pfn[1] = pfn;
पूर्ण

/*
 * If no pages were isolated then mark this pageblock to be skipped in the
 * future. The inक्रमmation is later cleared by __reset_isolation_suitable().
 */
अटल व्योम update_pageblock_skip(काष्ठा compact_control *cc,
			काष्ठा page *page, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा zone *zone = cc->zone;

	अगर (cc->no_set_skip_hपूर्णांक)
		वापस;

	अगर (!page)
		वापस;

	set_pageblock_skip(page);

	/* Update where async and sync compaction should restart */
	अगर (pfn < zone->compact_cached_मुक्त_pfn)
		zone->compact_cached_मुक्त_pfn = pfn;
पूर्ण
#अन्यथा
अटल अंतरभूत bool isolation_suitable(काष्ठा compact_control *cc,
					काष्ठा page *page)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool pageblock_skip_persistent(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम update_pageblock_skip(काष्ठा compact_control *cc,
			काष्ठा page *page, अचिन्हित दीर्घ pfn)
अणु
पूर्ण

अटल व्योम update_cached_migrate(काष्ठा compact_control *cc, अचिन्हित दीर्घ pfn)
अणु
पूर्ण

अटल bool test_and_set_skip(काष्ठा compact_control *cc, काष्ठा page *page,
							अचिन्हित दीर्घ pfn)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPACTION */

/*
 * Compaction requires the taking of some coarse locks that are potentially
 * very heavily contended. For async compaction, trylock and record अगर the
 * lock is contended. The lock will still be acquired but compaction will
 * पात when the current block is finished regardless of success rate.
 * Sync compaction acquires the lock.
 *
 * Always वापसs true which makes it easier to track lock state in callers.
 */
अटल bool compact_lock_irqsave(spinlock_t *lock, अचिन्हित दीर्घ *flags,
						काष्ठा compact_control *cc)
	__acquires(lock)
अणु
	/* Track अगर the lock is contended in async mode */
	अगर (cc->mode == MIGRATE_ASYNC && !cc->contended) अणु
		अगर (spin_trylock_irqsave(lock, *flags))
			वापस true;

		cc->contended = true;
	पूर्ण

	spin_lock_irqsave(lock, *flags);
	वापस true;
पूर्ण

/*
 * Compaction requires the taking of some coarse locks that are potentially
 * very heavily contended. The lock should be periodically unlocked to aव्योम
 * having disabled IRQs क्रम a दीर्घ समय, even when there is nobody रुकोing on
 * the lock. It might also be that allowing the IRQs will result in
 * need_resched() becoming true. If scheduling is needed, async compaction
 * पातs. Sync compaction schedules.
 * Either compaction type will also पात अगर a fatal संकेत is pending.
 * In either हाल अगर the lock was locked, it is dropped and not regained.
 *
 * Returns true अगर compaction should पात due to fatal संकेत pending, or
 *		async compaction due to need_resched()
 * Returns false when compaction can जारी (sync compaction might have
 *		scheduled)
 */
अटल bool compact_unlock_should_पात(spinlock_t *lock,
		अचिन्हित दीर्घ flags, bool *locked, काष्ठा compact_control *cc)
अणु
	अगर (*locked) अणु
		spin_unlock_irqrestore(lock, flags);
		*locked = false;
	पूर्ण

	अगर (fatal_संकेत_pending(current)) अणु
		cc->contended = true;
		वापस true;
	पूर्ण

	cond_resched();

	वापस false;
पूर्ण

/*
 * Isolate मुक्त pages onto a निजी मुक्तlist. If @strict is true, will पात
 * वापसing 0 on any invalid PFNs or non-मुक्त pages inside of the pageblock
 * (even though it may still end up isolating some pages).
 */
अटल अचिन्हित दीर्घ isolate_मुक्तpages_block(काष्ठा compact_control *cc,
				अचिन्हित दीर्घ *start_pfn,
				अचिन्हित दीर्घ end_pfn,
				काष्ठा list_head *मुक्तlist,
				अचिन्हित पूर्णांक stride,
				bool strict)
अणु
	पूर्णांक nr_scanned = 0, total_isolated = 0;
	काष्ठा page *cursor;
	अचिन्हित दीर्घ flags = 0;
	bool locked = false;
	अचिन्हित दीर्घ blockpfn = *start_pfn;
	अचिन्हित पूर्णांक order;

	/* Strict mode is क्रम isolation, speed is secondary */
	अगर (strict)
		stride = 1;

	cursor = pfn_to_page(blockpfn);

	/* Isolate मुक्त pages. */
	क्रम (; blockpfn < end_pfn; blockpfn += stride, cursor += stride) अणु
		पूर्णांक isolated;
		काष्ठा page *page = cursor;

		/*
		 * Periodically drop the lock (अगर held) regardless of its
		 * contention, to give chance to IRQs. Abort अगर fatal संकेत
		 * pending or async compaction detects need_resched()
		 */
		अगर (!(blockpfn % SWAP_CLUSTER_MAX)
		    && compact_unlock_should_पात(&cc->zone->lock, flags,
								&locked, cc))
			अवरोध;

		nr_scanned++;
		अगर (!pfn_valid_within(blockpfn))
			जाओ isolate_fail;

		/*
		 * For compound pages such as THP and hugetlbfs, we can save
		 * potentially a lot of iterations अगर we skip them at once.
		 * The check is racy, but we can consider only valid values
		 * and the only danger is skipping too much.
		 */
		अगर (PageCompound(page)) अणु
			स्थिर अचिन्हित पूर्णांक order = compound_order(page);

			अगर (likely(order < MAX_ORDER)) अणु
				blockpfn += (1UL << order) - 1;
				cursor += (1UL << order) - 1;
			पूर्ण
			जाओ isolate_fail;
		पूर्ण

		अगर (!PageBuddy(page))
			जाओ isolate_fail;

		/*
		 * If we alपढ़ोy hold the lock, we can skip some rechecking.
		 * Note that अगर we hold the lock now, checked_pageblock was
		 * alपढ़ोy set in some previous iteration (or strict is true),
		 * so it is correct to skip the suitable migration target
		 * recheck as well.
		 */
		अगर (!locked) अणु
			locked = compact_lock_irqsave(&cc->zone->lock,
								&flags, cc);

			/* Recheck this is a buddy page under lock */
			अगर (!PageBuddy(page))
				जाओ isolate_fail;
		पूर्ण

		/* Found a मुक्त page, will अवरोध it पूर्णांकo order-0 pages */
		order = buddy_order(page);
		isolated = __isolate_मुक्त_page(page, order);
		अगर (!isolated)
			अवरोध;
		set_page_निजी(page, order);

		total_isolated += isolated;
		cc->nr_मुक्तpages += isolated;
		list_add_tail(&page->lru, मुक्तlist);

		अगर (!strict && cc->nr_migratepages <= cc->nr_मुक्तpages) अणु
			blockpfn += isolated;
			अवरोध;
		पूर्ण
		/* Advance to the end of split page */
		blockpfn += isolated - 1;
		cursor += isolated - 1;
		जारी;

isolate_fail:
		अगर (strict)
			अवरोध;
		अन्यथा
			जारी;

	पूर्ण

	अगर (locked)
		spin_unlock_irqrestore(&cc->zone->lock, flags);

	/*
	 * There is a tiny chance that we have पढ़ो bogus compound_order(),
	 * so be careful to not go outside of the pageblock.
	 */
	अगर (unlikely(blockpfn > end_pfn))
		blockpfn = end_pfn;

	trace_mm_compaction_isolate_मुक्तpages(*start_pfn, blockpfn,
					nr_scanned, total_isolated);

	/* Record how far we have got within the block */
	*start_pfn = blockpfn;

	/*
	 * If strict isolation is requested by CMA then check that all the
	 * pages requested were isolated. If there were any failures, 0 is
	 * वापसed and CMA will fail.
	 */
	अगर (strict && blockpfn < end_pfn)
		total_isolated = 0;

	cc->total_मुक्त_scanned += nr_scanned;
	अगर (total_isolated)
		count_compact_events(COMPACTISOLATED, total_isolated);
	वापस total_isolated;
पूर्ण

/**
 * isolate_मुक्तpages_range() - isolate मुक्त pages.
 * @cc:        Compaction control काष्ठाure.
 * @start_pfn: The first PFN to start isolating.
 * @end_pfn:   The one-past-last PFN.
 *
 * Non-मुक्त pages, invalid PFNs, or zone boundaries within the
 * [start_pfn, end_pfn) range are considered errors, cause function to
 * unकरो its actions and वापस zero.
 *
 * Otherwise, function वापसs one-past-the-last PFN of isolated page
 * (which may be greater then end_pfn अगर end fell in a middle of
 * a मुक्त page).
 */
अचिन्हित दीर्घ
isolate_मुक्तpages_range(काष्ठा compact_control *cc,
			अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ isolated, pfn, block_start_pfn, block_end_pfn;
	LIST_HEAD(मुक्तlist);

	pfn = start_pfn;
	block_start_pfn = pageblock_start_pfn(pfn);
	अगर (block_start_pfn < cc->zone->zone_start_pfn)
		block_start_pfn = cc->zone->zone_start_pfn;
	block_end_pfn = pageblock_end_pfn(pfn);

	क्रम (; pfn < end_pfn; pfn += isolated,
				block_start_pfn = block_end_pfn,
				block_end_pfn += pageblock_nr_pages) अणु
		/* Protect pfn from changing by isolate_मुक्तpages_block */
		अचिन्हित दीर्घ isolate_start_pfn = pfn;

		block_end_pfn = min(block_end_pfn, end_pfn);

		/*
		 * pfn could pass the block_end_pfn अगर isolated मुक्तpage
		 * is more than pageblock order. In this हाल, we adjust
		 * scanning range to right one.
		 */
		अगर (pfn >= block_end_pfn) अणु
			block_start_pfn = pageblock_start_pfn(pfn);
			block_end_pfn = pageblock_end_pfn(pfn);
			block_end_pfn = min(block_end_pfn, end_pfn);
		पूर्ण

		अगर (!pageblock_pfn_to_page(block_start_pfn,
					block_end_pfn, cc->zone))
			अवरोध;

		isolated = isolate_मुक्तpages_block(cc, &isolate_start_pfn,
					block_end_pfn, &मुक्तlist, 0, true);

		/*
		 * In strict mode, isolate_मुक्तpages_block() वापसs 0 अगर
		 * there are any holes in the block (ie. invalid PFNs or
		 * non-मुक्त pages).
		 */
		अगर (!isolated)
			अवरोध;

		/*
		 * If we managed to isolate pages, it is always (1 << n) *
		 * pageblock_nr_pages क्रम some non-negative n.  (Max order
		 * page may span two pageblocks).
		 */
	पूर्ण

	/* __isolate_मुक्त_page() करोes not map the pages */
	split_map_pages(&मुक्तlist);

	अगर (pfn < end_pfn) अणु
		/* Loop terminated early, cleanup. */
		release_मुक्तpages(&मुक्तlist);
		वापस 0;
	पूर्ण

	/* We करोn't use मुक्तlists क्रम anything. */
	वापस pfn;
पूर्ण

/* Similar to reclaim, but dअगरferent enough that they करोn't share logic */
अटल bool too_many_isolated(pg_data_t *pgdat)
अणु
	अचिन्हित दीर्घ active, inactive, isolated;

	inactive = node_page_state(pgdat, NR_INACTIVE_खाता) +
			node_page_state(pgdat, NR_INACTIVE_ANON);
	active = node_page_state(pgdat, NR_ACTIVE_खाता) +
			node_page_state(pgdat, NR_ACTIVE_ANON);
	isolated = node_page_state(pgdat, NR_ISOLATED_खाता) +
			node_page_state(pgdat, NR_ISOLATED_ANON);

	वापस isolated > (inactive + active) / 2;
पूर्ण

/**
 * isolate_migratepages_block() - isolate all migrate-able pages within
 *				  a single pageblock
 * @cc:		Compaction control काष्ठाure.
 * @low_pfn:	The first PFN to isolate
 * @end_pfn:	The one-past-the-last PFN to isolate, within same pageblock
 * @isolate_mode: Isolation mode to be used.
 *
 * Isolate all pages that can be migrated from the range specअगरied by
 * [low_pfn, end_pfn). The range is expected to be within same pageblock.
 * Returns त्रुटि_सं, like -EAGAIN or -EINTR in हाल e.g संकेत pending or congestion,
 * -ENOMEM in हाल we could not allocate a page, or 0.
 * cc->migrate_pfn will contain the next pfn to scan.
 *
 * The pages are isolated on cc->migratepages list (not required to be empty),
 * and cc->nr_migratepages is updated accordingly.
 */
अटल पूर्णांक
isolate_migratepages_block(काष्ठा compact_control *cc, अचिन्हित दीर्घ low_pfn,
			अचिन्हित दीर्घ end_pfn, isolate_mode_t isolate_mode)
अणु
	pg_data_t *pgdat = cc->zone->zone_pgdat;
	अचिन्हित दीर्घ nr_scanned = 0, nr_isolated = 0;
	काष्ठा lruvec *lruvec;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा lruvec *locked = शून्य;
	काष्ठा page *page = शून्य, *valid_page = शून्य;
	अचिन्हित दीर्घ start_pfn = low_pfn;
	bool skip_on_failure = false;
	अचिन्हित दीर्घ next_skip_pfn = 0;
	bool skip_updated = false;
	पूर्णांक ret = 0;

	cc->migrate_pfn = low_pfn;

	/*
	 * Ensure that there are not too many pages isolated from the LRU
	 * list by either parallel reclaimers or compaction. If there are,
	 * delay क्रम some समय until fewer pages are isolated
	 */
	जबतक (unlikely(too_many_isolated(pgdat))) अणु
		/* stop isolation अगर there are still pages not migrated */
		अगर (cc->nr_migratepages)
			वापस -EAGAIN;

		/* async migration should just पात */
		अगर (cc->mode == MIGRATE_ASYNC)
			वापस -EAGAIN;

		congestion_रुको(BLK_RW_ASYNC, HZ/10);

		अगर (fatal_संकेत_pending(current))
			वापस -EINTR;
	पूर्ण

	cond_resched();

	अगर (cc->direct_compaction && (cc->mode == MIGRATE_ASYNC)) अणु
		skip_on_failure = true;
		next_skip_pfn = block_end_pfn(low_pfn, cc->order);
	पूर्ण

	/* Time to isolate some pages क्रम migration */
	क्रम (; low_pfn < end_pfn; low_pfn++) अणु

		अगर (skip_on_failure && low_pfn >= next_skip_pfn) अणु
			/*
			 * We have isolated all migration candidates in the
			 * previous order-aligned block, and did not skip it due
			 * to failure. We should migrate the pages now and
			 * hopefully succeed compaction.
			 */
			अगर (nr_isolated)
				अवरोध;

			/*
			 * We failed to isolate in the previous order-aligned
			 * block. Set the new boundary to the end of the
			 * current block. Note we can't simply increase
			 * next_skip_pfn by 1 << order, as low_pfn might have
			 * been incremented by a higher number due to skipping
			 * a compound or a high-order buddy page in the
			 * previous loop iteration.
			 */
			next_skip_pfn = block_end_pfn(low_pfn, cc->order);
		पूर्ण

		/*
		 * Periodically drop the lock (अगर held) regardless of its
		 * contention, to give chance to IRQs. Abort completely अगर
		 * a fatal संकेत is pending.
		 */
		अगर (!(low_pfn % SWAP_CLUSTER_MAX)) अणु
			अगर (locked) अणु
				unlock_page_lruvec_irqrestore(locked, flags);
				locked = शून्य;
			पूर्ण

			अगर (fatal_संकेत_pending(current)) अणु
				cc->contended = true;
				ret = -EINTR;

				जाओ fatal_pending;
			पूर्ण

			cond_resched();
		पूर्ण

		अगर (!pfn_valid_within(low_pfn))
			जाओ isolate_fail;
		nr_scanned++;

		page = pfn_to_page(low_pfn);

		/*
		 * Check अगर the pageblock has alपढ़ोy been marked skipped.
		 * Only the aligned PFN is checked as the caller isolates
		 * COMPACT_CLUSTER_MAX at a समय so the second call must
		 * not falsely conclude that the block should be skipped.
		 */
		अगर (!valid_page && IS_ALIGNED(low_pfn, pageblock_nr_pages)) अणु
			अगर (!cc->ignore_skip_hपूर्णांक && get_pageblock_skip(page)) अणु
				low_pfn = end_pfn;
				page = शून्य;
				जाओ isolate_पात;
			पूर्ण
			valid_page = page;
		पूर्ण

		अगर (PageHuge(page) && cc->alloc_contig) अणु
			ret = isolate_or_dissolve_huge_page(page, &cc->migratepages);

			/*
			 * Fail isolation in हाल isolate_or_dissolve_huge_page()
			 * reports an error. In हाल of -ENOMEM, पात right away.
			 */
			अगर (ret < 0) अणु
				 /* Do not report -EBUSY करोwn the chain */
				अगर (ret == -EBUSY)
					ret = 0;
				low_pfn += (1UL << compound_order(page)) - 1;
				जाओ isolate_fail;
			पूर्ण

			अगर (PageHuge(page)) अणु
				/*
				 * Hugepage was successfully isolated and placed
				 * on the cc->migratepages list.
				 */
				low_pfn += compound_nr(page) - 1;
				जाओ isolate_success_no_list;
			पूर्ण

			/*
			 * Ok, the hugepage was dissolved. Now these pages are
			 * Buddy and cannot be re-allocated because they are
			 * isolated. Fall-through as the check below handles
			 * Buddy pages.
			 */
		पूर्ण

		/*
		 * Skip अगर मुक्त. We पढ़ो page order here without zone lock
		 * which is generally unsafe, but the race winकरोw is small and
		 * the worst thing that can happen is that we skip some
		 * potential isolation tarमाला_लो.
		 */
		अगर (PageBuddy(page)) अणु
			अचिन्हित दीर्घ मुक्तpage_order = buddy_order_unsafe(page);

			/*
			 * Without lock, we cannot be sure that what we got is
			 * a valid page order. Consider only values in the
			 * valid order range to prevent low_pfn overflow.
			 */
			अगर (मुक्तpage_order > 0 && मुक्तpage_order < MAX_ORDER)
				low_pfn += (1UL << मुक्तpage_order) - 1;
			जारी;
		पूर्ण

		/*
		 * Regardless of being on LRU, compound pages such as THP and
		 * hugetlbfs are not to be compacted unless we are attempting
		 * an allocation much larger than the huge page size (eg CMA).
		 * We can potentially save a lot of iterations अगर we skip them
		 * at once. The check is racy, but we can consider only valid
		 * values and the only danger is skipping too much.
		 */
		अगर (PageCompound(page) && !cc->alloc_contig) अणु
			स्थिर अचिन्हित पूर्णांक order = compound_order(page);

			अगर (likely(order < MAX_ORDER))
				low_pfn += (1UL << order) - 1;
			जाओ isolate_fail;
		पूर्ण

		/*
		 * Check may be lockless but that's ok as we recheck later.
		 * It's possible to migrate LRU and non-lru movable pages.
		 * Skip any other type of page
		 */
		अगर (!PageLRU(page)) अणु
			/*
			 * __PageMovable can वापस false positive so we need
			 * to verअगरy it under page_lock.
			 */
			अगर (unlikely(__PageMovable(page)) &&
					!PageIsolated(page)) अणु
				अगर (locked) अणु
					unlock_page_lruvec_irqrestore(locked, flags);
					locked = शून्य;
				पूर्ण

				अगर (!isolate_movable_page(page, isolate_mode))
					जाओ isolate_success;
			पूर्ण

			जाओ isolate_fail;
		पूर्ण

		/*
		 * Migration will fail अगर an anonymous page is pinned in memory,
		 * so aव्योम taking lru_lock and isolating it unnecessarily in an
		 * admittedly racy check.
		 */
		अगर (!page_mapping(page) &&
		    page_count(page) > page_mapcount(page))
			जाओ isolate_fail;

		/*
		 * Only allow to migrate anonymous pages in GFP_NOFS context
		 * because those करो not depend on fs locks.
		 */
		अगर (!(cc->gfp_mask & __GFP_FS) && page_mapping(page))
			जाओ isolate_fail;

		/*
		 * Be careful not to clear PageLRU until after we're
		 * sure the page is not being मुक्तd अन्यथाwhere -- the
		 * page release code relies on it.
		 */
		अगर (unlikely(!get_page_unless_zero(page)))
			जाओ isolate_fail;

		अगर (!__isolate_lru_page_prepare(page, isolate_mode))
			जाओ isolate_fail_put;

		/* Try isolate the page */
		अगर (!TestClearPageLRU(page))
			जाओ isolate_fail_put;

		lruvec = mem_cgroup_page_lruvec(page, pgdat);

		/* If we alपढ़ोy hold the lock, we can skip some rechecking */
		अगर (lruvec != locked) अणु
			अगर (locked)
				unlock_page_lruvec_irqrestore(locked, flags);

			compact_lock_irqsave(&lruvec->lru_lock, &flags, cc);
			locked = lruvec;

			lruvec_memcg_debug(lruvec, page);

			/* Try get exclusive access under lock */
			अगर (!skip_updated) अणु
				skip_updated = true;
				अगर (test_and_set_skip(cc, page, low_pfn))
					जाओ isolate_पात;
			पूर्ण

			/*
			 * Page become compound since the non-locked check,
			 * and it's on LRU. It can only be a THP so the order
			 * is safe to पढ़ो and it's 0 क्रम tail pages.
			 */
			अगर (unlikely(PageCompound(page) && !cc->alloc_contig)) अणु
				low_pfn += compound_nr(page) - 1;
				SetPageLRU(page);
				जाओ isolate_fail_put;
			पूर्ण
		पूर्ण

		/* The whole page is taken off the LRU; skip the tail pages. */
		अगर (PageCompound(page))
			low_pfn += compound_nr(page) - 1;

		/* Successfully isolated */
		del_page_from_lru_list(page, lruvec);
		mod_node_page_state(page_pgdat(page),
				NR_ISOLATED_ANON + page_is_file_lru(page),
				thp_nr_pages(page));

isolate_success:
		list_add(&page->lru, &cc->migratepages);
isolate_success_no_list:
		cc->nr_migratepages += compound_nr(page);
		nr_isolated += compound_nr(page);

		/*
		 * Aव्योम isolating too much unless this block is being
		 * rescanned (e.g. dirty/ग_लिखोback pages, parallel allocation)
		 * or a lock is contended. For contention, isolate quickly to
		 * potentially हटाओ one source of contention.
		 */
		अगर (cc->nr_migratepages >= COMPACT_CLUSTER_MAX &&
		    !cc->rescan && !cc->contended) अणु
			++low_pfn;
			अवरोध;
		पूर्ण

		जारी;

isolate_fail_put:
		/* Aव्योम potential deadlock in मुक्तing page under lru_lock */
		अगर (locked) अणु
			unlock_page_lruvec_irqrestore(locked, flags);
			locked = शून्य;
		पूर्ण
		put_page(page);

isolate_fail:
		अगर (!skip_on_failure && ret != -ENOMEM)
			जारी;

		/*
		 * We have isolated some pages, but then failed. Release them
		 * instead of migrating, as we cannot क्रमm the cc->order buddy
		 * page anyway.
		 */
		अगर (nr_isolated) अणु
			अगर (locked) अणु
				unlock_page_lruvec_irqrestore(locked, flags);
				locked = शून्य;
			पूर्ण
			putback_movable_pages(&cc->migratepages);
			cc->nr_migratepages = 0;
			nr_isolated = 0;
		पूर्ण

		अगर (low_pfn < next_skip_pfn) अणु
			low_pfn = next_skip_pfn - 1;
			/*
			 * The check near the loop beginning would have updated
			 * next_skip_pfn too, but this is a bit simpler.
			 */
			next_skip_pfn += 1UL << cc->order;
		पूर्ण

		अगर (ret == -ENOMEM)
			अवरोध;
	पूर्ण

	/*
	 * The PageBuddy() check could have potentially brought us outside
	 * the range to be scanned.
	 */
	अगर (unlikely(low_pfn > end_pfn))
		low_pfn = end_pfn;

	page = शून्य;

isolate_पात:
	अगर (locked)
		unlock_page_lruvec_irqrestore(locked, flags);
	अगर (page) अणु
		SetPageLRU(page);
		put_page(page);
	पूर्ण

	/*
	 * Updated the cached scanner pfn once the pageblock has been scanned
	 * Pages will either be migrated in which हाल there is no poपूर्णांक
	 * scanning in the near future or migration failed in which हाल the
	 * failure reason may persist. The block is marked क्रम skipping अगर
	 * there were no pages isolated in the block or अगर the block is
	 * rescanned twice in a row.
	 */
	अगर (low_pfn == end_pfn && (!nr_isolated || cc->rescan)) अणु
		अगर (valid_page && !skip_updated)
			set_pageblock_skip(valid_page);
		update_cached_migrate(cc, low_pfn);
	पूर्ण

	trace_mm_compaction_isolate_migratepages(start_pfn, low_pfn,
						nr_scanned, nr_isolated);

fatal_pending:
	cc->total_migrate_scanned += nr_scanned;
	अगर (nr_isolated)
		count_compact_events(COMPACTISOLATED, nr_isolated);

	cc->migrate_pfn = low_pfn;

	वापस ret;
पूर्ण

/**
 * isolate_migratepages_range() - isolate migrate-able pages in a PFN range
 * @cc:        Compaction control काष्ठाure.
 * @start_pfn: The first PFN to start isolating.
 * @end_pfn:   The one-past-last PFN.
 *
 * Returns -EAGAIN when contented, -EINTR in हाल of a संकेत pending, -ENOMEM
 * in हाल we could not allocate a page, or 0.
 */
पूर्णांक
isolate_migratepages_range(काष्ठा compact_control *cc, अचिन्हित दीर्घ start_pfn,
							अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn, block_start_pfn, block_end_pfn;
	पूर्णांक ret = 0;

	/* Scan block by block. First and last block may be incomplete */
	pfn = start_pfn;
	block_start_pfn = pageblock_start_pfn(pfn);
	अगर (block_start_pfn < cc->zone->zone_start_pfn)
		block_start_pfn = cc->zone->zone_start_pfn;
	block_end_pfn = pageblock_end_pfn(pfn);

	क्रम (; pfn < end_pfn; pfn = block_end_pfn,
				block_start_pfn = block_end_pfn,
				block_end_pfn += pageblock_nr_pages) अणु

		block_end_pfn = min(block_end_pfn, end_pfn);

		अगर (!pageblock_pfn_to_page(block_start_pfn,
					block_end_pfn, cc->zone))
			जारी;

		ret = isolate_migratepages_block(cc, pfn, block_end_pfn,
						 ISOLATE_UNEVICTABLE);

		अगर (ret)
			अवरोध;

		अगर (cc->nr_migratepages >= COMPACT_CLUSTER_MAX)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPACTION || CONFIG_CMA */
#अगर_घोषित CONFIG_COMPACTION

अटल bool suitable_migration_source(काष्ठा compact_control *cc,
							काष्ठा page *page)
अणु
	पूर्णांक block_mt;

	अगर (pageblock_skip_persistent(page))
		वापस false;

	अगर ((cc->mode != MIGRATE_ASYNC) || !cc->direct_compaction)
		वापस true;

	block_mt = get_pageblock_migratetype(page);

	अगर (cc->migratetype == MIGRATE_MOVABLE)
		वापस is_migrate_movable(block_mt);
	अन्यथा
		वापस block_mt == cc->migratetype;
पूर्ण

/* Returns true अगर the page is within a block suitable क्रम migration to */
अटल bool suitable_migration_target(काष्ठा compact_control *cc,
							काष्ठा page *page)
अणु
	/* If the page is a large मुक्त page, then disallow migration */
	अगर (PageBuddy(page)) अणु
		/*
		 * We are checking page_order without zone->lock taken. But
		 * the only small danger is that we skip a potentially suitable
		 * pageblock, so it's not worth to check order क्रम valid range.
		 */
		अगर (buddy_order_unsafe(page) >= pageblock_order)
			वापस false;
	पूर्ण

	अगर (cc->ignore_block_suitable)
		वापस true;

	/* If the block is MIGRATE_MOVABLE or MIGRATE_CMA, allow migration */
	अगर (is_migrate_movable(get_pageblock_migratetype(page)))
		वापस true;

	/* Otherwise skip the block */
	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
मुक्तlist_scan_limit(काष्ठा compact_control *cc)
अणु
	अचिन्हित लघु shअगरt = BITS_PER_LONG - 1;

	वापस (COMPACT_CLUSTER_MAX >> min(shअगरt, cc->fast_search_fail)) + 1;
पूर्ण

/*
 * Test whether the मुक्त scanner has reached the same or lower pageblock than
 * the migration scanner, and compaction should thus terminate.
 */
अटल अंतरभूत bool compact_scanners_met(काष्ठा compact_control *cc)
अणु
	वापस (cc->मुक्त_pfn >> pageblock_order)
		<= (cc->migrate_pfn >> pageblock_order);
पूर्ण

/*
 * Used when scanning क्रम a suitable migration target which scans मुक्तlists
 * in reverse. Reorders the list such as the unscanned pages are scanned
 * first on the next iteration of the मुक्त scanner
 */
अटल व्योम
move_मुक्तlist_head(काष्ठा list_head *मुक्तlist, काष्ठा page *मुक्तpage)
अणु
	LIST_HEAD(sublist);

	अगर (!list_is_last(मुक्तlist, &मुक्तpage->lru)) अणु
		list_cut_beक्रमe(&sublist, मुक्तlist, &मुक्तpage->lru);
		अगर (!list_empty(&sublist))
			list_splice_tail(&sublist, मुक्तlist);
	पूर्ण
पूर्ण

/*
 * Similar to move_मुक्तlist_head except used by the migration scanner
 * when scanning क्रमward. It's possible क्रम these list operations to
 * move against each other अगर they search the मुक्त list exactly in
 * lockstep.
 */
अटल व्योम
move_मुक्तlist_tail(काष्ठा list_head *मुक्तlist, काष्ठा page *मुक्तpage)
अणु
	LIST_HEAD(sublist);

	अगर (!list_is_first(मुक्तlist, &मुक्तpage->lru)) अणु
		list_cut_position(&sublist, मुक्तlist, &मुक्तpage->lru);
		अगर (!list_empty(&sublist))
			list_splice_tail(&sublist, मुक्तlist);
	पूर्ण
पूर्ण

अटल व्योम
fast_isolate_around(काष्ठा compact_control *cc, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_isolated)
अणु
	अचिन्हित दीर्घ start_pfn, end_pfn;
	काष्ठा page *page;

	/* Do not search around अगर there are enough pages alपढ़ोy */
	अगर (cc->nr_मुक्तpages >= cc->nr_migratepages)
		वापस;

	/* Minimise scanning during async compaction */
	अगर (cc->direct_compaction && cc->mode == MIGRATE_ASYNC)
		वापस;

	/* Pageblock boundaries */
	start_pfn = max(pageblock_start_pfn(pfn), cc->zone->zone_start_pfn);
	end_pfn = min(pageblock_end_pfn(pfn), zone_end_pfn(cc->zone));

	page = pageblock_pfn_to_page(start_pfn, end_pfn, cc->zone);
	अगर (!page)
		वापस;

	/* Scan beक्रमe */
	अगर (start_pfn != pfn) अणु
		isolate_मुक्तpages_block(cc, &start_pfn, pfn, &cc->मुक्तpages, 1, false);
		अगर (cc->nr_मुक्तpages >= cc->nr_migratepages)
			वापस;
	पूर्ण

	/* Scan after */
	start_pfn = pfn + nr_isolated;
	अगर (start_pfn < end_pfn)
		isolate_मुक्तpages_block(cc, &start_pfn, end_pfn, &cc->मुक्तpages, 1, false);

	/* Skip this pageblock in the future as it's full or nearly full */
	अगर (cc->nr_मुक्तpages < cc->nr_migratepages)
		set_pageblock_skip(page);
पूर्ण

/* Search orders in round-robin fashion */
अटल पूर्णांक next_search_order(काष्ठा compact_control *cc, पूर्णांक order)
अणु
	order--;
	अगर (order < 0)
		order = cc->order - 1;

	/* Search wrapped around? */
	अगर (order == cc->search_order) अणु
		cc->search_order--;
		अगर (cc->search_order < 0)
			cc->search_order = cc->order - 1;
		वापस -1;
	पूर्ण

	वापस order;
पूर्ण

अटल अचिन्हित दीर्घ
fast_isolate_मुक्तpages(काष्ठा compact_control *cc)
अणु
	अचिन्हित पूर्णांक limit = min(1U, मुक्तlist_scan_limit(cc) >> 1);
	अचिन्हित पूर्णांक nr_scanned = 0;
	अचिन्हित दीर्घ low_pfn, min_pfn, highest = 0;
	अचिन्हित दीर्घ nr_isolated = 0;
	अचिन्हित दीर्घ distance;
	काष्ठा page *page = शून्य;
	bool scan_start = false;
	पूर्णांक order;

	/* Full compaction passes in a negative order */
	अगर (cc->order <= 0)
		वापस cc->मुक्त_pfn;

	/*
	 * If starting the scan, use a deeper search and use the highest
	 * PFN found अगर a suitable one is not found.
	 */
	अगर (cc->मुक्त_pfn >= cc->zone->compact_init_मुक्त_pfn) अणु
		limit = pageblock_nr_pages >> 1;
		scan_start = true;
	पूर्ण

	/*
	 * Preferred poपूर्णांक is in the top quarter of the scan space but take
	 * a pfn from the top half अगर the search is problematic.
	 */
	distance = (cc->मुक्त_pfn - cc->migrate_pfn);
	low_pfn = pageblock_start_pfn(cc->मुक्त_pfn - (distance >> 2));
	min_pfn = pageblock_start_pfn(cc->मुक्त_pfn - (distance >> 1));

	अगर (WARN_ON_ONCE(min_pfn > low_pfn))
		low_pfn = min_pfn;

	/*
	 * Search starts from the last successful isolation order or the next
	 * order to search after a previous failure
	 */
	cc->search_order = min_t(अचिन्हित पूर्णांक, cc->order - 1, cc->search_order);

	क्रम (order = cc->search_order;
	     !page && order >= 0;
	     order = next_search_order(cc, order)) अणु
		काष्ठा मुक्त_area *area = &cc->zone->मुक्त_area[order];
		काष्ठा list_head *मुक्तlist;
		काष्ठा page *मुक्तpage;
		अचिन्हित दीर्घ flags;
		अचिन्हित पूर्णांक order_scanned = 0;
		अचिन्हित दीर्घ high_pfn = 0;

		अगर (!area->nr_मुक्त)
			जारी;

		spin_lock_irqsave(&cc->zone->lock, flags);
		मुक्तlist = &area->मुक्त_list[MIGRATE_MOVABLE];
		list_क्रम_each_entry_reverse(मुक्तpage, मुक्तlist, lru) अणु
			अचिन्हित दीर्घ pfn;

			order_scanned++;
			nr_scanned++;
			pfn = page_to_pfn(मुक्तpage);

			अगर (pfn >= highest)
				highest = max(pageblock_start_pfn(pfn),
					      cc->zone->zone_start_pfn);

			अगर (pfn >= low_pfn) अणु
				cc->fast_search_fail = 0;
				cc->search_order = order;
				page = मुक्तpage;
				अवरोध;
			पूर्ण

			अगर (pfn >= min_pfn && pfn > high_pfn) अणु
				high_pfn = pfn;

				/* Shorten the scan अगर a candidate is found */
				limit >>= 1;
			पूर्ण

			अगर (order_scanned >= limit)
				अवरोध;
		पूर्ण

		/* Use a minimum pfn अगर a preferred one was not found */
		अगर (!page && high_pfn) अणु
			page = pfn_to_page(high_pfn);

			/* Update मुक्तpage क्रम the list reorder below */
			मुक्तpage = page;
		पूर्ण

		/* Reorder to so a future search skips recent pages */
		move_मुक्तlist_head(मुक्तlist, मुक्तpage);

		/* Isolate the page अगर available */
		अगर (page) अणु
			अगर (__isolate_मुक्त_page(page, order)) अणु
				set_page_निजी(page, order);
				nr_isolated = 1 << order;
				cc->nr_मुक्तpages += nr_isolated;
				list_add_tail(&page->lru, &cc->मुक्तpages);
				count_compact_events(COMPACTISOLATED, nr_isolated);
			पूर्ण अन्यथा अणु
				/* If isolation fails, पात the search */
				order = cc->search_order + 1;
				page = शून्य;
			पूर्ण
		पूर्ण

		spin_unlock_irqrestore(&cc->zone->lock, flags);

		/*
		 * Smaller scan on next order so the total scan ig related
		 * to मुक्तlist_scan_limit.
		 */
		अगर (order_scanned >= limit)
			limit = min(1U, limit >> 1);
	पूर्ण

	अगर (!page) अणु
		cc->fast_search_fail++;
		अगर (scan_start) अणु
			/*
			 * Use the highest PFN found above min. If one was
			 * not found, be pessimistic क्रम direct compaction
			 * and use the min mark.
			 */
			अगर (highest) अणु
				page = pfn_to_page(highest);
				cc->मुक्त_pfn = highest;
			पूर्ण अन्यथा अणु
				अगर (cc->direct_compaction && pfn_valid(min_pfn)) अणु
					page = pageblock_pfn_to_page(min_pfn,
						min(pageblock_end_pfn(min_pfn),
						    zone_end_pfn(cc->zone)),
						cc->zone);
					cc->मुक्त_pfn = min_pfn;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (highest && highest >= cc->zone->compact_cached_मुक्त_pfn) अणु
		highest -= pageblock_nr_pages;
		cc->zone->compact_cached_मुक्त_pfn = highest;
	पूर्ण

	cc->total_मुक्त_scanned += nr_scanned;
	अगर (!page)
		वापस cc->मुक्त_pfn;

	low_pfn = page_to_pfn(page);
	fast_isolate_around(cc, low_pfn, nr_isolated);
	वापस low_pfn;
पूर्ण

/*
 * Based on inक्रमmation in the current compact_control, find blocks
 * suitable क्रम isolating मुक्त pages from and then isolate them.
 */
अटल व्योम isolate_मुक्तpages(काष्ठा compact_control *cc)
अणु
	काष्ठा zone *zone = cc->zone;
	काष्ठा page *page;
	अचिन्हित दीर्घ block_start_pfn;	/* start of current pageblock */
	अचिन्हित दीर्घ isolate_start_pfn; /* exact pfn we start at */
	अचिन्हित दीर्घ block_end_pfn;	/* end of current pageblock */
	अचिन्हित दीर्घ low_pfn;	     /* lowest pfn scanner is able to scan */
	काष्ठा list_head *मुक्तlist = &cc->मुक्तpages;
	अचिन्हित पूर्णांक stride;

	/* Try a small search of the मुक्त lists क्रम a candidate */
	isolate_start_pfn = fast_isolate_मुक्तpages(cc);
	अगर (cc->nr_मुक्तpages)
		जाओ spliपंचांगap;

	/*
	 * Initialise the मुक्त scanner. The starting poपूर्णांक is where we last
	 * successfully isolated from, zone-cached value, or the end of the
	 * zone when isolating क्रम the first समय. For looping we also need
	 * this pfn aligned करोwn to the pageblock boundary, because we करो
	 * block_start_pfn -= pageblock_nr_pages in the क्रम loop.
	 * For ending poपूर्णांक, take care when isolating in last pageblock of a
	 * zone which ends in the middle of a pageblock.
	 * The low boundary is the end of the pageblock the migration scanner
	 * is using.
	 */
	isolate_start_pfn = cc->मुक्त_pfn;
	block_start_pfn = pageblock_start_pfn(isolate_start_pfn);
	block_end_pfn = min(block_start_pfn + pageblock_nr_pages,
						zone_end_pfn(zone));
	low_pfn = pageblock_end_pfn(cc->migrate_pfn);
	stride = cc->mode == MIGRATE_ASYNC ? COMPACT_CLUSTER_MAX : 1;

	/*
	 * Isolate मुक्त pages until enough are available to migrate the
	 * pages on cc->migratepages. We stop searching अगर the migrate
	 * and मुक्त page scanners meet or enough मुक्त pages are isolated.
	 */
	क्रम (; block_start_pfn >= low_pfn;
				block_end_pfn = block_start_pfn,
				block_start_pfn -= pageblock_nr_pages,
				isolate_start_pfn = block_start_pfn) अणु
		अचिन्हित दीर्घ nr_isolated;

		/*
		 * This can iterate a massively दीर्घ zone without finding any
		 * suitable migration tarमाला_लो, so periodically check resched.
		 */
		अगर (!(block_start_pfn % (SWAP_CLUSTER_MAX * pageblock_nr_pages)))
			cond_resched();

		page = pageblock_pfn_to_page(block_start_pfn, block_end_pfn,
									zone);
		अगर (!page)
			जारी;

		/* Check the block is suitable क्रम migration */
		अगर (!suitable_migration_target(cc, page))
			जारी;

		/* If isolation recently failed, करो not retry */
		अगर (!isolation_suitable(cc, page))
			जारी;

		/* Found a block suitable क्रम isolating मुक्त pages from. */
		nr_isolated = isolate_मुक्तpages_block(cc, &isolate_start_pfn,
					block_end_pfn, मुक्तlist, stride, false);

		/* Update the skip hपूर्णांक अगर the full pageblock was scanned */
		अगर (isolate_start_pfn == block_end_pfn)
			update_pageblock_skip(cc, page, block_start_pfn);

		/* Are enough मुक्तpages isolated? */
		अगर (cc->nr_मुक्तpages >= cc->nr_migratepages) अणु
			अगर (isolate_start_pfn >= block_end_pfn) अणु
				/*
				 * Restart at previous pageblock अगर more
				 * मुक्तpages can be isolated next समय.
				 */
				isolate_start_pfn =
					block_start_pfn - pageblock_nr_pages;
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (isolate_start_pfn < block_end_pfn) अणु
			/*
			 * If isolation failed early, करो not जारी
			 * needlessly.
			 */
			अवरोध;
		पूर्ण

		/* Adjust stride depending on isolation */
		अगर (nr_isolated) अणु
			stride = 1;
			जारी;
		पूर्ण
		stride = min_t(अचिन्हित पूर्णांक, COMPACT_CLUSTER_MAX, stride << 1);
	पूर्ण

	/*
	 * Record where the मुक्त scanner will restart next समय. Either we
	 * broke from the loop and set isolate_start_pfn based on the last
	 * call to isolate_मुक्तpages_block(), or we met the migration scanner
	 * and the loop terminated due to isolate_start_pfn < low_pfn
	 */
	cc->मुक्त_pfn = isolate_start_pfn;

spliपंचांगap:
	/* __isolate_मुक्त_page() करोes not map the pages */
	split_map_pages(मुक्तlist);
पूर्ण

/*
 * This is a migrate-callback that "allocates" मुक्तpages by taking pages
 * from the isolated मुक्तlists in the block we are migrating to.
 */
अटल काष्ठा page *compaction_alloc(काष्ठा page *migratepage,
					अचिन्हित दीर्घ data)
अणु
	काष्ठा compact_control *cc = (काष्ठा compact_control *)data;
	काष्ठा page *मुक्तpage;

	अगर (list_empty(&cc->मुक्तpages)) अणु
		isolate_मुक्तpages(cc);

		अगर (list_empty(&cc->मुक्तpages))
			वापस शून्य;
	पूर्ण

	मुक्तpage = list_entry(cc->मुक्तpages.next, काष्ठा page, lru);
	list_del(&मुक्तpage->lru);
	cc->nr_मुक्तpages--;

	वापस मुक्तpage;
पूर्ण

/*
 * This is a migrate-callback that "frees" मुक्तpages back to the isolated
 * मुक्तlist.  All pages on the मुक्तlist are from the same zone, so there is no
 * special handling needed क्रम NUMA.
 */
अटल व्योम compaction_मुक्त(काष्ठा page *page, अचिन्हित दीर्घ data)
अणु
	काष्ठा compact_control *cc = (काष्ठा compact_control *)data;

	list_add(&page->lru, &cc->मुक्तpages);
	cc->nr_मुक्तpages++;
पूर्ण

/* possible outcome of isolate_migratepages */
प्रकार क्रमागत अणु
	ISOLATE_ABORT,		/* Abort compaction now */
	ISOLATE_NONE,		/* No pages isolated, जारी scanning */
	ISOLATE_SUCCESS,	/* Pages isolated, migrate */
पूर्ण isolate_migrate_t;

/*
 * Allow userspace to control policy on scanning the unevictable LRU क्रम
 * compactable pages.
 */
#अगर_घोषित CONFIG_PREEMPT_RT
पूर्णांक sysctl_compact_unevictable_allowed __पढ़ो_mostly = 0;
#अन्यथा
पूर्णांक sysctl_compact_unevictable_allowed __पढ़ो_mostly = 1;
#पूर्ण_अगर

अटल अंतरभूत व्योम
update_fast_start_pfn(काष्ठा compact_control *cc, अचिन्हित दीर्घ pfn)
अणु
	अगर (cc->fast_start_pfn == अच_दीर्घ_उच्च)
		वापस;

	अगर (!cc->fast_start_pfn)
		cc->fast_start_pfn = pfn;

	cc->fast_start_pfn = min(cc->fast_start_pfn, pfn);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
reinit_migrate_pfn(काष्ठा compact_control *cc)
अणु
	अगर (!cc->fast_start_pfn || cc->fast_start_pfn == अच_दीर्घ_उच्च)
		वापस cc->migrate_pfn;

	cc->migrate_pfn = cc->fast_start_pfn;
	cc->fast_start_pfn = अच_दीर्घ_उच्च;

	वापस cc->migrate_pfn;
पूर्ण

/*
 * Briefly search the मुक्त lists क्रम a migration source that alपढ़ोy has
 * some मुक्त pages to reduce the number of pages that need migration
 * beक्रमe a pageblock is मुक्त.
 */
अटल अचिन्हित दीर्घ fast_find_migrateblock(काष्ठा compact_control *cc)
अणु
	अचिन्हित पूर्णांक limit = मुक्तlist_scan_limit(cc);
	अचिन्हित पूर्णांक nr_scanned = 0;
	अचिन्हित दीर्घ distance;
	अचिन्हित दीर्घ pfn = cc->migrate_pfn;
	अचिन्हित दीर्घ high_pfn;
	पूर्णांक order;
	bool found_block = false;

	/* Skip hपूर्णांकs are relied on to aव्योम repeats on the fast search */
	अगर (cc->ignore_skip_hपूर्णांक)
		वापस pfn;

	/*
	 * If the migrate_pfn is not at the start of a zone or the start
	 * of a pageblock then assume this is a continuation of a previous
	 * scan restarted due to COMPACT_CLUSTER_MAX.
	 */
	अगर (pfn != cc->zone->zone_start_pfn && pfn != pageblock_start_pfn(pfn))
		वापस pfn;

	/*
	 * For smaller orders, just linearly scan as the number of pages
	 * to migrate should be relatively small and करोes not necessarily
	 * justअगरy मुक्तing up a large block क्रम a small allocation.
	 */
	अगर (cc->order <= PAGE_ALLOC_COSTLY_ORDER)
		वापस pfn;

	/*
	 * Only allow kcompactd and direct requests क्रम movable pages to
	 * quickly clear out a MOVABLE pageblock क्रम allocation. This
	 * reduces the risk that a large movable pageblock is मुक्तd क्रम
	 * an unmovable/reclaimable small allocation.
	 */
	अगर (cc->direct_compaction && cc->migratetype != MIGRATE_MOVABLE)
		वापस pfn;

	/*
	 * When starting the migration scanner, pick any pageblock within the
	 * first half of the search space. Otherwise try and pick a pageblock
	 * within the first eighth to reduce the chances that a migration
	 * target later becomes a source.
	 */
	distance = (cc->मुक्त_pfn - cc->migrate_pfn) >> 1;
	अगर (cc->migrate_pfn != cc->zone->zone_start_pfn)
		distance >>= 2;
	high_pfn = pageblock_start_pfn(cc->migrate_pfn + distance);

	क्रम (order = cc->order - 1;
	     order >= PAGE_ALLOC_COSTLY_ORDER && !found_block && nr_scanned < limit;
	     order--) अणु
		काष्ठा मुक्त_area *area = &cc->zone->मुक्त_area[order];
		काष्ठा list_head *मुक्तlist;
		अचिन्हित दीर्घ flags;
		काष्ठा page *मुक्तpage;

		अगर (!area->nr_मुक्त)
			जारी;

		spin_lock_irqsave(&cc->zone->lock, flags);
		मुक्तlist = &area->मुक्त_list[MIGRATE_MOVABLE];
		list_क्रम_each_entry(मुक्तpage, मुक्तlist, lru) अणु
			अचिन्हित दीर्घ मुक्त_pfn;

			अगर (nr_scanned++ >= limit) अणु
				move_मुक्तlist_tail(मुक्तlist, मुक्तpage);
				अवरोध;
			पूर्ण

			मुक्त_pfn = page_to_pfn(मुक्तpage);
			अगर (मुक्त_pfn < high_pfn) अणु
				/*
				 * Aव्योम अगर skipped recently. Ideally it would
				 * move to the tail but even safe iteration of
				 * the list assumes an entry is deleted, not
				 * reordered.
				 */
				अगर (get_pageblock_skip(मुक्तpage))
					जारी;

				/* Reorder to so a future search skips recent pages */
				move_मुक्तlist_tail(मुक्तlist, मुक्तpage);

				update_fast_start_pfn(cc, मुक्त_pfn);
				pfn = pageblock_start_pfn(मुक्त_pfn);
				cc->fast_search_fail = 0;
				found_block = true;
				set_pageblock_skip(मुक्तpage);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&cc->zone->lock, flags);
	पूर्ण

	cc->total_migrate_scanned += nr_scanned;

	/*
	 * If fast scanning failed then use a cached entry क्रम a page block
	 * that had मुक्त pages as the basis क्रम starting a linear scan.
	 */
	अगर (!found_block) अणु
		cc->fast_search_fail++;
		pfn = reinit_migrate_pfn(cc);
	पूर्ण
	वापस pfn;
पूर्ण

/*
 * Isolate all pages that can be migrated from the first suitable block,
 * starting at the block poपूर्णांकed to by the migrate scanner pfn within
 * compact_control.
 */
अटल isolate_migrate_t isolate_migratepages(काष्ठा compact_control *cc)
अणु
	अचिन्हित दीर्घ block_start_pfn;
	अचिन्हित दीर्घ block_end_pfn;
	अचिन्हित दीर्घ low_pfn;
	काष्ठा page *page;
	स्थिर isolate_mode_t isolate_mode =
		(sysctl_compact_unevictable_allowed ? ISOLATE_UNEVICTABLE : 0) |
		(cc->mode != MIGRATE_SYNC ? ISOLATE_ASYNC_MIGRATE : 0);
	bool fast_find_block;

	/*
	 * Start at where we last stopped, or beginning of the zone as
	 * initialized by compact_zone(). The first failure will use
	 * the lowest PFN as the starting poपूर्णांक क्रम linear scanning.
	 */
	low_pfn = fast_find_migrateblock(cc);
	block_start_pfn = pageblock_start_pfn(low_pfn);
	अगर (block_start_pfn < cc->zone->zone_start_pfn)
		block_start_pfn = cc->zone->zone_start_pfn;

	/*
	 * fast_find_migrateblock marks a pageblock skipped so to aव्योम
	 * the isolation_suitable check below, check whether the fast
	 * search was successful.
	 */
	fast_find_block = low_pfn != cc->migrate_pfn && !cc->fast_search_fail;

	/* Only scan within a pageblock boundary */
	block_end_pfn = pageblock_end_pfn(low_pfn);

	/*
	 * Iterate over whole pageblocks until we find the first suitable.
	 * Do not cross the मुक्त scanner.
	 */
	क्रम (; block_end_pfn <= cc->मुक्त_pfn;
			fast_find_block = false,
			cc->migrate_pfn = low_pfn = block_end_pfn,
			block_start_pfn = block_end_pfn,
			block_end_pfn += pageblock_nr_pages) अणु

		/*
		 * This can potentially iterate a massively दीर्घ zone with
		 * many pageblocks unsuitable, so periodically check अगर we
		 * need to schedule.
		 */
		अगर (!(low_pfn % (SWAP_CLUSTER_MAX * pageblock_nr_pages)))
			cond_resched();

		page = pageblock_pfn_to_page(block_start_pfn,
						block_end_pfn, cc->zone);
		अगर (!page)
			जारी;

		/*
		 * If isolation recently failed, करो not retry. Only check the
		 * pageblock once. COMPACT_CLUSTER_MAX causes a pageblock
		 * to be visited multiple बार. Assume skip was checked
		 * beक्रमe making it "skip" so other compaction instances करो
		 * not scan the same block.
		 */
		अगर (IS_ALIGNED(low_pfn, pageblock_nr_pages) &&
		    !fast_find_block && !isolation_suitable(cc, page))
			जारी;

		/*
		 * For async compaction, also only scan in MOVABLE blocks
		 * without huge pages. Async compaction is optimistic to see
		 * अगर the minimum amount of work satisfies the allocation.
		 * The cached PFN is updated as it's possible that all
		 * reमुख्यing blocks between source and target are unsuitable
		 * and the compaction scanners fail to meet.
		 */
		अगर (!suitable_migration_source(cc, page)) अणु
			update_cached_migrate(cc, block_end_pfn);
			जारी;
		पूर्ण

		/* Perक्रमm the isolation */
		अगर (isolate_migratepages_block(cc, low_pfn, block_end_pfn,
						isolate_mode))
			वापस ISOLATE_ABORT;

		/*
		 * Either we isolated something and proceed with migration. Or
		 * we failed and compact_zone should decide अगर we should
		 * जारी or not.
		 */
		अवरोध;
	पूर्ण

	वापस cc->nr_migratepages ? ISOLATE_SUCCESS : ISOLATE_NONE;
पूर्ण

/*
 * order == -1 is expected when compacting via
 * /proc/sys/vm/compact_memory
 */
अटल अंतरभूत bool is_via_compact_memory(पूर्णांक order)
अणु
	वापस order == -1;
पूर्ण

अटल bool kswapd_is_running(pg_data_t *pgdat)
अणु
	वापस pgdat->kswapd && (pgdat->kswapd->state == TASK_RUNNING);
पूर्ण

/*
 * A zone's fragmentation score is the बाह्यal fragmentation wrt to the
 * COMPACTION_HPAGE_ORDER. It वापसs a value in the range [0, 100].
 */
अटल अचिन्हित पूर्णांक fragmentation_score_zone(काष्ठा zone *zone)
अणु
	वापस extfrag_क्रम_order(zone, COMPACTION_HPAGE_ORDER);
पूर्ण

/*
 * A weighted zone's fragmentation score is the बाह्यal fragmentation
 * wrt to the COMPACTION_HPAGE_ORDER scaled by the zone's size. It
 * वापसs a value in the range [0, 100].
 *
 * The scaling factor ensures that proactive compaction focuses on larger
 * zones like ZONE_NORMAL, rather than smaller, specialized zones like
 * ZONE_DMA32. For smaller zones, the score value reमुख्यs बंद to zero,
 * and thus never exceeds the high threshold क्रम proactive compaction.
 */
अटल अचिन्हित पूर्णांक fragmentation_score_zone_weighted(काष्ठा zone *zone)
अणु
	अचिन्हित दीर्घ score;

	score = zone->present_pages * fragmentation_score_zone(zone);
	वापस भाग64_ul(score, zone->zone_pgdat->node_present_pages + 1);
पूर्ण

/*
 * The per-node proactive (background) compaction process is started by its
 * corresponding kcompactd thपढ़ो when the node's fragmentation score
 * exceeds the high threshold. The compaction process reमुख्यs active till
 * the node's score falls below the low threshold, or one of the back-off
 * conditions is met.
 */
अटल अचिन्हित पूर्णांक fragmentation_score_node(pg_data_t *pgdat)
अणु
	अचिन्हित पूर्णांक score = 0;
	पूर्णांक zoneid;

	क्रम (zoneid = 0; zoneid < MAX_NR_ZONES; zoneid++) अणु
		काष्ठा zone *zone;

		zone = &pgdat->node_zones[zoneid];
		score += fragmentation_score_zone_weighted(zone);
	पूर्ण

	वापस score;
पूर्ण

अटल अचिन्हित पूर्णांक fragmentation_score_wmark(pg_data_t *pgdat, bool low)
अणु
	अचिन्हित पूर्णांक wmark_low;

	/*
	 * Cap the low watermark to aव्योम excessive compaction
	 * activity in हाल a user sets the proactiveness tunable
	 * बंद to 100 (maximum).
	 */
	wmark_low = max(100U - sysctl_compaction_proactiveness, 5U);
	वापस low ? wmark_low : min(wmark_low + 10, 100U);
पूर्ण

अटल bool should_proactive_compact_node(pg_data_t *pgdat)
अणु
	पूर्णांक wmark_high;

	अगर (!sysctl_compaction_proactiveness || kswapd_is_running(pgdat))
		वापस false;

	wmark_high = fragmentation_score_wmark(pgdat, false);
	वापस fragmentation_score_node(pgdat) > wmark_high;
पूर्ण

अटल क्रमागत compact_result __compact_finished(काष्ठा compact_control *cc)
अणु
	अचिन्हित पूर्णांक order;
	स्थिर पूर्णांक migratetype = cc->migratetype;
	पूर्णांक ret;

	/* Compaction run completes अगर the migrate and मुक्त scanner meet */
	अगर (compact_scanners_met(cc)) अणु
		/* Let the next compaction start anew. */
		reset_cached_positions(cc->zone);

		/*
		 * Mark that the PG_migrate_skip inक्रमmation should be cleared
		 * by kswapd when it goes to sleep. kcompactd करोes not set the
		 * flag itself as the decision to be clear should be directly
		 * based on an allocation request.
		 */
		अगर (cc->direct_compaction)
			cc->zone->compact_blockskip_flush = true;

		अगर (cc->whole_zone)
			वापस COMPACT_COMPLETE;
		अन्यथा
			वापस COMPACT_PARTIAL_SKIPPED;
	पूर्ण

	अगर (cc->proactive_compaction) अणु
		पूर्णांक score, wmark_low;
		pg_data_t *pgdat;

		pgdat = cc->zone->zone_pgdat;
		अगर (kswapd_is_running(pgdat))
			वापस COMPACT_PARTIAL_SKIPPED;

		score = fragmentation_score_zone(cc->zone);
		wmark_low = fragmentation_score_wmark(pgdat, true);

		अगर (score > wmark_low)
			ret = COMPACT_CONTINUE;
		अन्यथा
			ret = COMPACT_SUCCESS;

		जाओ out;
	पूर्ण

	अगर (is_via_compact_memory(cc->order))
		वापस COMPACT_CONTINUE;

	/*
	 * Always finish scanning a pageblock to reduce the possibility of
	 * fallbacks in the future. This is particularly important when
	 * migration source is unmovable/reclaimable but it's not worth
	 * special casing.
	 */
	अगर (!IS_ALIGNED(cc->migrate_pfn, pageblock_nr_pages))
		वापस COMPACT_CONTINUE;

	/* Direct compactor: Is a suitable page मुक्त? */
	ret = COMPACT_NO_SUITABLE_PAGE;
	क्रम (order = cc->order; order < MAX_ORDER; order++) अणु
		काष्ठा मुक्त_area *area = &cc->zone->मुक्त_area[order];
		bool can_steal;

		/* Job करोne अगर page is मुक्त of the right migratetype */
		अगर (!मुक्त_area_empty(area, migratetype))
			वापस COMPACT_SUCCESS;

#अगर_घोषित CONFIG_CMA
		/* MIGRATE_MOVABLE can fallback on MIGRATE_CMA */
		अगर (migratetype == MIGRATE_MOVABLE &&
			!मुक्त_area_empty(area, MIGRATE_CMA))
			वापस COMPACT_SUCCESS;
#पूर्ण_अगर
		/*
		 * Job करोne अगर allocation would steal मुक्तpages from
		 * other migratetype buddy lists.
		 */
		अगर (find_suitable_fallback(area, order, migratetype,
						true, &can_steal) != -1) अणु

			/* movable pages are OK in any pageblock */
			अगर (migratetype == MIGRATE_MOVABLE)
				वापस COMPACT_SUCCESS;

			/*
			 * We are stealing क्रम a non-movable allocation. Make
			 * sure we finish compacting the current pageblock
			 * first so it is as मुक्त as possible and we won't
			 * have to steal another one soon. This only applies
			 * to sync compaction, as async compaction operates
			 * on pageblocks of the same migratetype.
			 */
			अगर (cc->mode == MIGRATE_ASYNC ||
					IS_ALIGNED(cc->migrate_pfn,
							pageblock_nr_pages)) अणु
				वापस COMPACT_SUCCESS;
			पूर्ण

			ret = COMPACT_CONTINUE;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	अगर (cc->contended || fatal_संकेत_pending(current))
		ret = COMPACT_CONTENDED;

	वापस ret;
पूर्ण

अटल क्रमागत compact_result compact_finished(काष्ठा compact_control *cc)
अणु
	पूर्णांक ret;

	ret = __compact_finished(cc);
	trace_mm_compaction_finished(cc->zone, cc->order, ret);
	अगर (ret == COMPACT_NO_SUITABLE_PAGE)
		ret = COMPACT_CONTINUE;

	वापस ret;
पूर्ण

अटल क्रमागत compact_result __compaction_suitable(काष्ठा zone *zone, पूर्णांक order,
					अचिन्हित पूर्णांक alloc_flags,
					पूर्णांक highest_zoneidx,
					अचिन्हित दीर्घ wmark_target)
अणु
	अचिन्हित दीर्घ watermark;

	अगर (is_via_compact_memory(order))
		वापस COMPACT_CONTINUE;

	watermark = wmark_pages(zone, alloc_flags & ALLOC_WMARK_MASK);
	/*
	 * If watermarks क्रम high-order allocation are alपढ़ोy met, there
	 * should be no need क्रम compaction at all.
	 */
	अगर (zone_watermark_ok(zone, order, watermark, highest_zoneidx,
								alloc_flags))
		वापस COMPACT_SUCCESS;

	/*
	 * Watermarks क्रम order-0 must be met क्रम compaction to be able to
	 * isolate मुक्त pages क्रम migration tarमाला_लो. This means that the
	 * watermark and alloc_flags have to match, or be more pessimistic than
	 * the check in __isolate_मुक्त_page(). We करोn't use the direct
	 * compactor's alloc_flags, as they are not relevant क्रम मुक्तpage
	 * isolation. We however करो use the direct compactor's highest_zoneidx
	 * to skip over zones where lowmem reserves would prevent allocation
	 * even अगर compaction succeeds.
	 * For costly orders, we require low watermark instead of min क्रम
	 * compaction to proceed to increase its chances.
	 * ALLOC_CMA is used, as pages in CMA pageblocks are considered
	 * suitable migration tarमाला_लो
	 */
	watermark = (order > PAGE_ALLOC_COSTLY_ORDER) ?
				low_wmark_pages(zone) : min_wmark_pages(zone);
	watermark += compact_gap(order);
	अगर (!__zone_watermark_ok(zone, 0, watermark, highest_zoneidx,
						ALLOC_CMA, wmark_target))
		वापस COMPACT_SKIPPED;

	वापस COMPACT_CONTINUE;
पूर्ण

/*
 * compaction_suitable: Is this suitable to run compaction on this zone now?
 * Returns
 *   COMPACT_SKIPPED  - If there are too few मुक्त pages क्रम compaction
 *   COMPACT_SUCCESS  - If the allocation would succeed without compaction
 *   COMPACT_CONTINUE - If compaction should run now
 */
क्रमागत compact_result compaction_suitable(काष्ठा zone *zone, पूर्णांक order,
					अचिन्हित पूर्णांक alloc_flags,
					पूर्णांक highest_zoneidx)
अणु
	क्रमागत compact_result ret;
	पूर्णांक fragindex;

	ret = __compaction_suitable(zone, order, alloc_flags, highest_zoneidx,
				    zone_page_state(zone, NR_FREE_PAGES));
	/*
	 * fragmentation index determines अगर allocation failures are due to
	 * low memory or बाह्यal fragmentation
	 *
	 * index of -1000 would imply allocations might succeed depending on
	 * watermarks, but we alपढ़ोy failed the high-order watermark check
	 * index towards 0 implies failure is due to lack of memory
	 * index towards 1000 implies failure is due to fragmentation
	 *
	 * Only compact अगर a failure would be due to fragmentation. Also
	 * ignore fragindex क्रम non-costly orders where the alternative to
	 * a successful reclaim/compaction is OOM. Fragindex and the
	 * vm.extfrag_threshold sysctl is meant as a heuristic to prevent
	 * excessive compaction क्रम costly orders, but it should not be at the
	 * expense of प्रणाली stability.
	 */
	अगर (ret == COMPACT_CONTINUE && (order > PAGE_ALLOC_COSTLY_ORDER)) अणु
		fragindex = fragmentation_index(zone, order);
		अगर (fragindex >= 0 && fragindex <= sysctl_extfrag_threshold)
			ret = COMPACT_NOT_SUITABLE_ZONE;
	पूर्ण

	trace_mm_compaction_suitable(zone, order, ret);
	अगर (ret == COMPACT_NOT_SUITABLE_ZONE)
		ret = COMPACT_SKIPPED;

	वापस ret;
पूर्ण

bool compaction_zonelist_suitable(काष्ठा alloc_context *ac, पूर्णांक order,
		पूर्णांक alloc_flags)
अणु
	काष्ठा zone *zone;
	काष्ठा zoneref *z;

	/*
	 * Make sure at least one zone would pass __compaction_suitable अगर we जारी
	 * retrying the reclaim.
	 */
	क्रम_each_zone_zonelist_nodemask(zone, z, ac->zonelist,
				ac->highest_zoneidx, ac->nodemask) अणु
		अचिन्हित दीर्घ available;
		क्रमागत compact_result compact_result;

		/*
		 * Do not consider all the reclaimable memory because we करो not
		 * want to trash just क्रम a single high order allocation which
		 * is even not guaranteed to appear even अगर __compaction_suitable
		 * is happy about the watermark check.
		 */
		available = zone_reclaimable_pages(zone) / order;
		available += zone_page_state_snapshot(zone, NR_FREE_PAGES);
		compact_result = __compaction_suitable(zone, order, alloc_flags,
				ac->highest_zoneidx, available);
		अगर (compact_result != COMPACT_SKIPPED)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल क्रमागत compact_result
compact_zone(काष्ठा compact_control *cc, काष्ठा capture_control *capc)
अणु
	क्रमागत compact_result ret;
	अचिन्हित दीर्घ start_pfn = cc->zone->zone_start_pfn;
	अचिन्हित दीर्घ end_pfn = zone_end_pfn(cc->zone);
	अचिन्हित दीर्घ last_migrated_pfn;
	स्थिर bool sync = cc->mode != MIGRATE_ASYNC;
	bool update_cached;

	/*
	 * These counters track activities during zone compaction.  Initialize
	 * them beक्रमe compacting a new zone.
	 */
	cc->total_migrate_scanned = 0;
	cc->total_मुक्त_scanned = 0;
	cc->nr_migratepages = 0;
	cc->nr_मुक्तpages = 0;
	INIT_LIST_HEAD(&cc->मुक्तpages);
	INIT_LIST_HEAD(&cc->migratepages);

	cc->migratetype = gfp_migratetype(cc->gfp_mask);
	ret = compaction_suitable(cc->zone, cc->order, cc->alloc_flags,
							cc->highest_zoneidx);
	/* Compaction is likely to fail */
	अगर (ret == COMPACT_SUCCESS || ret == COMPACT_SKIPPED)
		वापस ret;

	/* huh, compaction_suitable is वापसing something unexpected */
	VM_BUG_ON(ret != COMPACT_CONTINUE);

	/*
	 * Clear pageblock skip अगर there were failures recently and compaction
	 * is about to be retried after being deferred.
	 */
	अगर (compaction_restarting(cc->zone, cc->order))
		__reset_isolation_suitable(cc->zone);

	/*
	 * Setup to move all movable pages to the end of the zone. Used cached
	 * inक्रमmation on where the scanners should start (unless we explicitly
	 * want to compact the whole zone), but check that it is initialised
	 * by ensuring the values are within zone boundaries.
	 */
	cc->fast_start_pfn = 0;
	अगर (cc->whole_zone) अणु
		cc->migrate_pfn = start_pfn;
		cc->मुक्त_pfn = pageblock_start_pfn(end_pfn - 1);
	पूर्ण अन्यथा अणु
		cc->migrate_pfn = cc->zone->compact_cached_migrate_pfn[sync];
		cc->मुक्त_pfn = cc->zone->compact_cached_मुक्त_pfn;
		अगर (cc->मुक्त_pfn < start_pfn || cc->मुक्त_pfn >= end_pfn) अणु
			cc->मुक्त_pfn = pageblock_start_pfn(end_pfn - 1);
			cc->zone->compact_cached_मुक्त_pfn = cc->मुक्त_pfn;
		पूर्ण
		अगर (cc->migrate_pfn < start_pfn || cc->migrate_pfn >= end_pfn) अणु
			cc->migrate_pfn = start_pfn;
			cc->zone->compact_cached_migrate_pfn[0] = cc->migrate_pfn;
			cc->zone->compact_cached_migrate_pfn[1] = cc->migrate_pfn;
		पूर्ण

		अगर (cc->migrate_pfn <= cc->zone->compact_init_migrate_pfn)
			cc->whole_zone = true;
	पूर्ण

	last_migrated_pfn = 0;

	/*
	 * Migrate has separate cached PFNs क्रम ASYNC and SYNC* migration on
	 * the basis that some migrations will fail in ASYNC mode. However,
	 * अगर the cached PFNs match and pageblocks are skipped due to having
	 * no isolation candidates, then the sync state करोes not matter.
	 * Until a pageblock with isolation candidates is found, keep the
	 * cached PFNs in sync to aव्योम revisiting the same blocks.
	 */
	update_cached = !sync &&
		cc->zone->compact_cached_migrate_pfn[0] == cc->zone->compact_cached_migrate_pfn[1];

	trace_mm_compaction_begin(start_pfn, cc->migrate_pfn,
				cc->मुक्त_pfn, end_pfn, sync);

	/* lru_add_drain_all could be expensive with involving other CPUs */
	lru_add_drain();

	जबतक ((ret = compact_finished(cc)) == COMPACT_CONTINUE) अणु
		पूर्णांक err;
		अचिन्हित दीर्घ iteration_start_pfn = cc->migrate_pfn;

		/*
		 * Aव्योम multiple rescans which can happen अगर a page cannot be
		 * isolated (dirty/ग_लिखोback in async mode) or अगर the migrated
		 * pages are being allocated beक्रमe the pageblock is cleared.
		 * The first rescan will capture the entire pageblock क्रम
		 * migration. If it fails, it'll be marked skip and scanning
		 * will proceed as normal.
		 */
		cc->rescan = false;
		अगर (pageblock_start_pfn(last_migrated_pfn) ==
		    pageblock_start_pfn(iteration_start_pfn)) अणु
			cc->rescan = true;
		पूर्ण

		चयन (isolate_migratepages(cc)) अणु
		हाल ISOLATE_ABORT:
			ret = COMPACT_CONTENDED;
			putback_movable_pages(&cc->migratepages);
			cc->nr_migratepages = 0;
			जाओ out;
		हाल ISOLATE_NONE:
			अगर (update_cached) अणु
				cc->zone->compact_cached_migrate_pfn[1] =
					cc->zone->compact_cached_migrate_pfn[0];
			पूर्ण

			/*
			 * We haven't isolated and migrated anything, but
			 * there might still be unflushed migrations from
			 * previous cc->order aligned block.
			 */
			जाओ check_drain;
		हाल ISOLATE_SUCCESS:
			update_cached = false;
			last_migrated_pfn = iteration_start_pfn;
		पूर्ण

		err = migrate_pages(&cc->migratepages, compaction_alloc,
				compaction_मुक्त, (अचिन्हित दीर्घ)cc, cc->mode,
				MR_COMPACTION);

		trace_mm_compaction_migratepages(cc->nr_migratepages, err,
							&cc->migratepages);

		/* All pages were either migrated or will be released */
		cc->nr_migratepages = 0;
		अगर (err) अणु
			putback_movable_pages(&cc->migratepages);
			/*
			 * migrate_pages() may वापस -ENOMEM when scanners meet
			 * and we want compact_finished() to detect it
			 */
			अगर (err == -ENOMEM && !compact_scanners_met(cc)) अणु
				ret = COMPACT_CONTENDED;
				जाओ out;
			पूर्ण
			/*
			 * We failed to migrate at least one page in the current
			 * order-aligned block, so skip the rest of it.
			 */
			अगर (cc->direct_compaction &&
						(cc->mode == MIGRATE_ASYNC)) अणु
				cc->migrate_pfn = block_end_pfn(
						cc->migrate_pfn - 1, cc->order);
				/* Draining pcplists is useless in this हाल */
				last_migrated_pfn = 0;
			पूर्ण
		पूर्ण

check_drain:
		/*
		 * Has the migration scanner moved away from the previous
		 * cc->order aligned block where we migrated from? If yes,
		 * flush the pages that were मुक्तd, so that they can merge and
		 * compact_finished() can detect immediately अगर allocation
		 * would succeed.
		 */
		अगर (cc->order > 0 && last_migrated_pfn) अणु
			अचिन्हित दीर्घ current_block_start =
				block_start_pfn(cc->migrate_pfn, cc->order);

			अगर (last_migrated_pfn < current_block_start) अणु
				lru_add_drain_cpu_zone(cc->zone);
				/* No more flushing until we migrate again */
				last_migrated_pfn = 0;
			पूर्ण
		पूर्ण

		/* Stop अगर a page has been captured */
		अगर (capc && capc->page) अणु
			ret = COMPACT_SUCCESS;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	/*
	 * Release मुक्त pages and update where the मुक्त scanner should restart,
	 * so we करोn't leave any वापसed pages behind in the next attempt.
	 */
	अगर (cc->nr_मुक्तpages > 0) अणु
		अचिन्हित दीर्घ मुक्त_pfn = release_मुक्तpages(&cc->मुक्तpages);

		cc->nr_मुक्तpages = 0;
		VM_BUG_ON(मुक्त_pfn == 0);
		/* The cached pfn is always the first in a pageblock */
		मुक्त_pfn = pageblock_start_pfn(मुक्त_pfn);
		/*
		 * Only go back, not क्रमward. The cached pfn might have been
		 * alपढ़ोy reset to zone end in compact_finished()
		 */
		अगर (मुक्त_pfn > cc->zone->compact_cached_मुक्त_pfn)
			cc->zone->compact_cached_मुक्त_pfn = मुक्त_pfn;
	पूर्ण

	count_compact_events(COMPACTMIGRATE_SCANNED, cc->total_migrate_scanned);
	count_compact_events(COMPACTFREE_SCANNED, cc->total_मुक्त_scanned);

	trace_mm_compaction_end(start_pfn, cc->migrate_pfn,
				cc->मुक्त_pfn, end_pfn, sync, ret);

	वापस ret;
पूर्ण

अटल क्रमागत compact_result compact_zone_order(काष्ठा zone *zone, पूर्णांक order,
		gfp_t gfp_mask, क्रमागत compact_priority prio,
		अचिन्हित पूर्णांक alloc_flags, पूर्णांक highest_zoneidx,
		काष्ठा page **capture)
अणु
	क्रमागत compact_result ret;
	काष्ठा compact_control cc = अणु
		.order = order,
		.search_order = order,
		.gfp_mask = gfp_mask,
		.zone = zone,
		.mode = (prio == COMPACT_PRIO_ASYNC) ?
					MIGRATE_ASYNC :	MIGRATE_SYNC_LIGHT,
		.alloc_flags = alloc_flags,
		.highest_zoneidx = highest_zoneidx,
		.direct_compaction = true,
		.whole_zone = (prio == MIN_COMPACT_PRIORITY),
		.ignore_skip_hपूर्णांक = (prio == MIN_COMPACT_PRIORITY),
		.ignore_block_suitable = (prio == MIN_COMPACT_PRIORITY)
	पूर्ण;
	काष्ठा capture_control capc = अणु
		.cc = &cc,
		.page = शून्य,
	पूर्ण;

	/*
	 * Make sure the काष्ठाs are really initialized beक्रमe we expose the
	 * capture control, in हाल we are पूर्णांकerrupted and the पूर्णांकerrupt handler
	 * मुक्तs a page.
	 */
	barrier();
	WRITE_ONCE(current->capture_control, &capc);

	ret = compact_zone(&cc, &capc);

	VM_BUG_ON(!list_empty(&cc.मुक्तpages));
	VM_BUG_ON(!list_empty(&cc.migratepages));

	/*
	 * Make sure we hide capture control first beक्रमe we पढ़ो the captured
	 * page poपूर्णांकer, otherwise an पूर्णांकerrupt could मुक्त and capture a page
	 * and we would leak it.
	 */
	WRITE_ONCE(current->capture_control, शून्य);
	*capture = READ_ONCE(capc.page);
	/*
	 * Technically, it is also possible that compaction is skipped but
	 * the page is still captured out of luck(IRQ came and मुक्तd the page).
	 * Returning COMPACT_SUCCESS in such हालs helps in properly accounting
	 * the COMPACT[STALL|FAIL] when compaction is skipped.
	 */
	अगर (*capture)
		ret = COMPACT_SUCCESS;

	वापस ret;
पूर्ण

पूर्णांक sysctl_extfrag_threshold = 500;

/**
 * try_to_compact_pages - Direct compact to satisfy a high-order allocation
 * @gfp_mask: The GFP mask of the current allocation
 * @order: The order of the current allocation
 * @alloc_flags: The allocation flags of the current allocation
 * @ac: The context of current allocation
 * @prio: Determines how hard direct compaction should try to succeed
 * @capture: Poपूर्णांकer to मुक्त page created by compaction will be stored here
 *
 * This is the मुख्य entry poपूर्णांक क्रम direct page compaction.
 */
क्रमागत compact_result try_to_compact_pages(gfp_t gfp_mask, अचिन्हित पूर्णांक order,
		अचिन्हित पूर्णांक alloc_flags, स्थिर काष्ठा alloc_context *ac,
		क्रमागत compact_priority prio, काष्ठा page **capture)
अणु
	पूर्णांक may_perक्रमm_io = gfp_mask & __GFP_IO;
	काष्ठा zoneref *z;
	काष्ठा zone *zone;
	क्रमागत compact_result rc = COMPACT_SKIPPED;

	/*
	 * Check अगर the GFP flags allow compaction - GFP_NOIO is really
	 * tricky context because the migration might require IO
	 */
	अगर (!may_perक्रमm_io)
		वापस COMPACT_SKIPPED;

	trace_mm_compaction_try_to_compact_pages(order, gfp_mask, prio);

	/* Compact each zone in the list */
	क्रम_each_zone_zonelist_nodemask(zone, z, ac->zonelist,
					ac->highest_zoneidx, ac->nodemask) अणु
		क्रमागत compact_result status;

		अगर (prio > MIN_COMPACT_PRIORITY
					&& compaction_deferred(zone, order)) अणु
			rc = max_t(क्रमागत compact_result, COMPACT_DEFERRED, rc);
			जारी;
		पूर्ण

		status = compact_zone_order(zone, order, gfp_mask, prio,
				alloc_flags, ac->highest_zoneidx, capture);
		rc = max(status, rc);

		/* The allocation should succeed, stop compacting */
		अगर (status == COMPACT_SUCCESS) अणु
			/*
			 * We think the allocation will succeed in this zone,
			 * but it is not certain, hence the false. The caller
			 * will repeat this with true अगर allocation indeed
			 * succeeds in this zone.
			 */
			compaction_defer_reset(zone, order, false);

			अवरोध;
		पूर्ण

		अगर (prio != COMPACT_PRIO_ASYNC && (status == COMPACT_COMPLETE ||
					status == COMPACT_PARTIAL_SKIPPED))
			/*
			 * We think that allocation won't succeed in this zone
			 * so we defer compaction there. If it ends up
			 * succeeding after all, it will be reset.
			 */
			defer_compaction(zone, order);

		/*
		 * We might have stopped compacting due to need_resched() in
		 * async compaction, or due to a fatal संकेत detected. In that
		 * हाल करो not try further zones
		 */
		अगर ((prio == COMPACT_PRIO_ASYNC && need_resched())
					|| fatal_संकेत_pending(current))
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Compact all zones within a node till each zone's fragmentation score
 * reaches within proactive compaction thresholds (as determined by the
 * proactiveness tunable).
 *
 * It is possible that the function वापसs beक्रमe reaching score tarमाला_लो
 * due to various back-off conditions, such as, contention on per-node or
 * per-zone locks.
 */
अटल व्योम proactive_compact_node(pg_data_t *pgdat)
अणु
	पूर्णांक zoneid;
	काष्ठा zone *zone;
	काष्ठा compact_control cc = अणु
		.order = -1,
		.mode = MIGRATE_SYNC_LIGHT,
		.ignore_skip_hपूर्णांक = true,
		.whole_zone = true,
		.gfp_mask = GFP_KERNEL,
		.proactive_compaction = true,
	पूर्ण;

	क्रम (zoneid = 0; zoneid < MAX_NR_ZONES; zoneid++) अणु
		zone = &pgdat->node_zones[zoneid];
		अगर (!populated_zone(zone))
			जारी;

		cc.zone = zone;

		compact_zone(&cc, शून्य);

		VM_BUG_ON(!list_empty(&cc.मुक्तpages));
		VM_BUG_ON(!list_empty(&cc.migratepages));
	पूर्ण
पूर्ण

/* Compact all zones within a node */
अटल व्योम compact_node(पूर्णांक nid)
अणु
	pg_data_t *pgdat = NODE_DATA(nid);
	पूर्णांक zoneid;
	काष्ठा zone *zone;
	काष्ठा compact_control cc = अणु
		.order = -1,
		.mode = MIGRATE_SYNC,
		.ignore_skip_hपूर्णांक = true,
		.whole_zone = true,
		.gfp_mask = GFP_KERNEL,
	पूर्ण;


	क्रम (zoneid = 0; zoneid < MAX_NR_ZONES; zoneid++) अणु

		zone = &pgdat->node_zones[zoneid];
		अगर (!populated_zone(zone))
			जारी;

		cc.zone = zone;

		compact_zone(&cc, शून्य);

		VM_BUG_ON(!list_empty(&cc.मुक्तpages));
		VM_BUG_ON(!list_empty(&cc.migratepages));
	पूर्ण
पूर्ण

/* Compact all nodes in the प्रणाली */
अटल व्योम compact_nodes(व्योम)
अणु
	पूर्णांक nid;

	/* Flush pending updates to the LRU lists */
	lru_add_drain_all();

	क्रम_each_online_node(nid)
		compact_node(nid);
पूर्ण

/*
 * Tunable क्रम proactive compaction. It determines how
 * aggressively the kernel should compact memory in the
 * background. It takes values in the range [0, 100].
 */
अचिन्हित पूर्णांक __पढ़ो_mostly sysctl_compaction_proactiveness = 20;

/*
 * This is the entry poपूर्णांक क्रम compacting all nodes via
 * /proc/sys/vm/compact_memory
 */
पूर्णांक sysctl_compaction_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	अगर (ग_लिखो)
		compact_nodes();

	वापस 0;
पूर्ण

#अगर defined(CONFIG_SYSFS) && defined(CONFIG_NUMA)
अटल sमाप_प्रकार sysfs_compact_node(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nid = dev->id;

	अगर (nid >= 0 && nid < nr_node_ids && node_online(nid)) अणु
		/* Flush pending updates to the LRU lists */
		lru_add_drain_all();

		compact_node(nid);
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(compact, 0200, शून्य, sysfs_compact_node);

पूर्णांक compaction_रेजिस्टर_node(काष्ठा node *node)
अणु
	वापस device_create_file(&node->dev, &dev_attr_compact);
पूर्ण

व्योम compaction_unरेजिस्टर_node(काष्ठा node *node)
अणु
	वापस device_हटाओ_file(&node->dev, &dev_attr_compact);
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSFS && CONFIG_NUMA */

अटल अंतरभूत bool kcompactd_work_requested(pg_data_t *pgdat)
अणु
	वापस pgdat->kcompactd_max_order > 0 || kthपढ़ो_should_stop();
पूर्ण

अटल bool kcompactd_node_suitable(pg_data_t *pgdat)
अणु
	पूर्णांक zoneid;
	काष्ठा zone *zone;
	क्रमागत zone_type highest_zoneidx = pgdat->kcompactd_highest_zoneidx;

	क्रम (zoneid = 0; zoneid <= highest_zoneidx; zoneid++) अणु
		zone = &pgdat->node_zones[zoneid];

		अगर (!populated_zone(zone))
			जारी;

		अगर (compaction_suitable(zone, pgdat->kcompactd_max_order, 0,
					highest_zoneidx) == COMPACT_CONTINUE)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम kcompactd_करो_work(pg_data_t *pgdat)
अणु
	/*
	 * With no special task, compact all zones so that a page of requested
	 * order is allocatable.
	 */
	पूर्णांक zoneid;
	काष्ठा zone *zone;
	काष्ठा compact_control cc = अणु
		.order = pgdat->kcompactd_max_order,
		.search_order = pgdat->kcompactd_max_order,
		.highest_zoneidx = pgdat->kcompactd_highest_zoneidx,
		.mode = MIGRATE_SYNC_LIGHT,
		.ignore_skip_hपूर्णांक = false,
		.gfp_mask = GFP_KERNEL,
	पूर्ण;
	trace_mm_compaction_kcompactd_wake(pgdat->node_id, cc.order,
							cc.highest_zoneidx);
	count_compact_event(KCOMPACTD_WAKE);

	क्रम (zoneid = 0; zoneid <= cc.highest_zoneidx; zoneid++) अणु
		पूर्णांक status;

		zone = &pgdat->node_zones[zoneid];
		अगर (!populated_zone(zone))
			जारी;

		अगर (compaction_deferred(zone, cc.order))
			जारी;

		अगर (compaction_suitable(zone, cc.order, 0, zoneid) !=
							COMPACT_CONTINUE)
			जारी;

		अगर (kthपढ़ो_should_stop())
			वापस;

		cc.zone = zone;
		status = compact_zone(&cc, शून्य);

		अगर (status == COMPACT_SUCCESS) अणु
			compaction_defer_reset(zone, cc.order, false);
		पूर्ण अन्यथा अगर (status == COMPACT_PARTIAL_SKIPPED || status == COMPACT_COMPLETE) अणु
			/*
			 * Buddy pages may become stअक्रमed on pcps that could
			 * otherwise coalesce on the zone's मुक्त area क्रम
			 * order >= cc.order.  This is ratelimited by the
			 * upcoming deferral.
			 */
			drain_all_pages(zone);

			/*
			 * We use sync migration mode here, so we defer like
			 * sync direct compaction करोes.
			 */
			defer_compaction(zone, cc.order);
		पूर्ण

		count_compact_events(KCOMPACTD_MIGRATE_SCANNED,
				     cc.total_migrate_scanned);
		count_compact_events(KCOMPACTD_FREE_SCANNED,
				     cc.total_मुक्त_scanned);

		VM_BUG_ON(!list_empty(&cc.मुक्तpages));
		VM_BUG_ON(!list_empty(&cc.migratepages));
	पूर्ण

	/*
	 * Regardless of success, we are करोne until woken up next. But remember
	 * the requested order/highest_zoneidx in हाल it was higher/tighter
	 * than our current ones
	 */
	अगर (pgdat->kcompactd_max_order <= cc.order)
		pgdat->kcompactd_max_order = 0;
	अगर (pgdat->kcompactd_highest_zoneidx >= cc.highest_zoneidx)
		pgdat->kcompactd_highest_zoneidx = pgdat->nr_zones - 1;
पूर्ण

व्योम wakeup_kcompactd(pg_data_t *pgdat, पूर्णांक order, पूर्णांक highest_zoneidx)
अणु
	अगर (!order)
		वापस;

	अगर (pgdat->kcompactd_max_order < order)
		pgdat->kcompactd_max_order = order;

	अगर (pgdat->kcompactd_highest_zoneidx > highest_zoneidx)
		pgdat->kcompactd_highest_zoneidx = highest_zoneidx;

	/*
	 * Pairs with implicit barrier in रुको_event_मुक्तzable()
	 * such that wakeups are not missed.
	 */
	अगर (!wq_has_sleeper(&pgdat->kcompactd_रुको))
		वापस;

	अगर (!kcompactd_node_suitable(pgdat))
		वापस;

	trace_mm_compaction_wakeup_kcompactd(pgdat->node_id, order,
							highest_zoneidx);
	wake_up_पूर्णांकerruptible(&pgdat->kcompactd_रुको);
पूर्ण

/*
 * The background compaction daemon, started as a kernel thपढ़ो
 * from the init process.
 */
अटल पूर्णांक kcompactd(व्योम *p)
अणु
	pg_data_t *pgdat = (pg_data_t *)p;
	काष्ठा task_काष्ठा *tsk = current;
	अचिन्हित पूर्णांक proactive_defer = 0;

	स्थिर काष्ठा cpumask *cpumask = cpumask_of_node(pgdat->node_id);

	अगर (!cpumask_empty(cpumask))
		set_cpus_allowed_ptr(tsk, cpumask);

	set_मुक्तzable();

	pgdat->kcompactd_max_order = 0;
	pgdat->kcompactd_highest_zoneidx = pgdat->nr_zones - 1;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अचिन्हित दीर्घ pflags;

		trace_mm_compaction_kcompactd_sleep(pgdat->node_id);
		अगर (रुको_event_मुक्तzable_समयout(pgdat->kcompactd_रुको,
			kcompactd_work_requested(pgdat),
			msecs_to_jअगरfies(HPAGE_FRAG_CHECK_INTERVAL_MSEC))) अणु

			psi_memstall_enter(&pflags);
			kcompactd_करो_work(pgdat);
			psi_memstall_leave(&pflags);
			जारी;
		पूर्ण

		/* kcompactd रुको समयout */
		अगर (should_proactive_compact_node(pgdat)) अणु
			अचिन्हित पूर्णांक prev_score, score;

			अगर (proactive_defer) अणु
				proactive_defer--;
				जारी;
			पूर्ण
			prev_score = fragmentation_score_node(pgdat);
			proactive_compact_node(pgdat);
			score = fragmentation_score_node(pgdat);
			/*
			 * Defer proactive compaction अगर the fragmentation
			 * score did not go करोwn i.e. no progress made.
			 */
			proactive_defer = score < prev_score ?
					0 : 1 << COMPACT_MAX_DEFER_SHIFT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This kcompactd start function will be called by init and node-hot-add.
 * On node-hot-add, kcompactd will moved to proper cpus अगर cpus are hot-added.
 */
पूर्णांक kcompactd_run(पूर्णांक nid)
अणु
	pg_data_t *pgdat = NODE_DATA(nid);
	पूर्णांक ret = 0;

	अगर (pgdat->kcompactd)
		वापस 0;

	pgdat->kcompactd = kthपढ़ो_run(kcompactd, pgdat, "kcompactd%d", nid);
	अगर (IS_ERR(pgdat->kcompactd)) अणु
		pr_err("Failed to start kcompactd on node %d\n", nid);
		ret = PTR_ERR(pgdat->kcompactd);
		pgdat->kcompactd = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Called by memory hotplug when all memory in a node is offlined. Caller must
 * hold mem_hotplug_begin/end().
 */
व्योम kcompactd_stop(पूर्णांक nid)
अणु
	काष्ठा task_काष्ठा *kcompactd = NODE_DATA(nid)->kcompactd;

	अगर (kcompactd) अणु
		kthपढ़ो_stop(kcompactd);
		NODE_DATA(nid)->kcompactd = शून्य;
	पूर्ण
पूर्ण

/*
 * It's optimal to keep kcompactd on the same CPUs as their memory, but
 * not required क्रम correctness. So अगर the last cpu in a node goes
 * away, we get changed to run anywhere: as the first one comes back,
 * restore their cpu bindings.
 */
अटल पूर्णांक kcompactd_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक nid;

	क्रम_each_node_state(nid, N_MEMORY) अणु
		pg_data_t *pgdat = NODE_DATA(nid);
		स्थिर काष्ठा cpumask *mask;

		mask = cpumask_of_node(pgdat->node_id);

		अगर (cpumask_any_and(cpu_online_mask, mask) < nr_cpu_ids)
			/* One of our CPUs online: restore mask */
			set_cpus_allowed_ptr(pgdat->kcompactd, mask);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init kcompactd_init(व्योम)
अणु
	पूर्णांक nid;
	पूर्णांक ret;

	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					"mm/compaction:online",
					kcompactd_cpu_online, शून्य);
	अगर (ret < 0) अणु
		pr_err("kcompactd: failed to register hotplug callbacks.\n");
		वापस ret;
	पूर्ण

	क्रम_each_node_state(nid, N_MEMORY)
		kcompactd_run(nid);
	वापस 0;
पूर्ण
subsys_initcall(kcompactd_init)

#पूर्ण_अगर /* CONFIG_COMPACTION */
