<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/mm/page_isolation.c
 */

#समावेश <linux/mm.h>
#समावेश <linux/page-isolation.h>
#समावेश <linux/pageblock-flags.h>
#समावेश <linux/memory.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/page_owner.h>
#समावेश <linux/migrate.h>
#समावेश "internal.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/page_isolation.h>

अटल पूर्णांक set_migratetype_isolate(काष्ठा page *page, पूर्णांक migratetype, पूर्णांक isol_flags)
अणु
	काष्ठा zone *zone = page_zone(page);
	काष्ठा page *unmovable;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&zone->lock, flags);

	/*
	 * We assume the caller पूर्णांकended to SET migrate type to isolate.
	 * If it is alपढ़ोy set, then someone अन्यथा must have raced and
	 * set it beक्रमe us.
	 */
	अगर (is_migrate_isolate_page(page)) अणु
		spin_unlock_irqrestore(&zone->lock, flags);
		वापस -EBUSY;
	पूर्ण

	/*
	 * FIXME: Now, memory hotplug करोesn't call shrink_slab() by itself.
	 * We just check MOVABLE pages.
	 */
	unmovable = has_unmovable_pages(zone, page, migratetype, isol_flags);
	अगर (!unmovable) अणु
		अचिन्हित दीर्घ nr_pages;
		पूर्णांक mt = get_pageblock_migratetype(page);

		set_pageblock_migratetype(page, MIGRATE_ISOLATE);
		zone->nr_isolate_pageblock++;
		nr_pages = move_मुक्तpages_block(zone, page, MIGRATE_ISOLATE,
									शून्य);

		__mod_zone_मुक्तpage_state(zone, -nr_pages, mt);
		spin_unlock_irqrestore(&zone->lock, flags);
		वापस 0;
	पूर्ण

	spin_unlock_irqrestore(&zone->lock, flags);
	अगर (isol_flags & REPORT_FAILURE) अणु
		/*
		 * prपूर्णांकk() with zone->lock held will likely trigger a
		 * lockdep splat, so defer it here.
		 */
		dump_page(unmovable, "unmovable page");
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल व्योम unset_migratetype_isolate(काष्ठा page *page, अचिन्हित migratetype)
अणु
	काष्ठा zone *zone;
	अचिन्हित दीर्घ flags, nr_pages;
	bool isolated_page = false;
	अचिन्हित पूर्णांक order;
	अचिन्हित दीर्घ pfn, buddy_pfn;
	काष्ठा page *buddy;

	zone = page_zone(page);
	spin_lock_irqsave(&zone->lock, flags);
	अगर (!is_migrate_isolate_page(page))
		जाओ out;

	/*
	 * Because मुक्तpage with more than pageblock_order on isolated
	 * pageblock is restricted to merge due to मुक्तpage counting problem,
	 * it is possible that there is मुक्त buddy page.
	 * move_मुक्तpages_block() करोesn't care of merge so we need other
	 * approach in order to merge them. Isolation and मुक्त will make
	 * these pages to be merged.
	 */
	अगर (PageBuddy(page)) अणु
		order = buddy_order(page);
		अगर (order >= pageblock_order && order < MAX_ORDER - 1) अणु
			pfn = page_to_pfn(page);
			buddy_pfn = __find_buddy_pfn(pfn, order);
			buddy = page + (buddy_pfn - pfn);

			अगर (pfn_valid_within(buddy_pfn) &&
			    !is_migrate_isolate_page(buddy)) अणु
				__isolate_मुक्त_page(page, order);
				isolated_page = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If we isolate मुक्तpage with more than pageblock_order, there
	 * should be no मुक्तpage in the range, so we could aव्योम costly
	 * pageblock scanning क्रम मुक्तpage moving.
	 *
	 * We didn't actually touch any of the isolated pages, so place them
	 * to the tail of the मुक्तlist. This is an optimization क्रम memory
	 * onlining - just onlined memory won't immediately be considered क्रम
	 * allocation.
	 */
	अगर (!isolated_page) अणु
		nr_pages = move_मुक्तpages_block(zone, page, migratetype, शून्य);
		__mod_zone_मुक्तpage_state(zone, nr_pages, migratetype);
	पूर्ण
	set_pageblock_migratetype(page, migratetype);
	अगर (isolated_page)
		__putback_isolated_page(page, order, migratetype);
	zone->nr_isolate_pageblock--;
out:
	spin_unlock_irqrestore(&zone->lock, flags);
पूर्ण

अटल अंतरभूत काष्ठा page *
__first_valid_page(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_pages; i++) अणु
		काष्ठा page *page;

		page = pfn_to_online_page(pfn + i);
		अगर (!page)
			जारी;
		वापस page;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * start_isolate_page_range() - make page-allocation-type of range of pages to
 * be MIGRATE_ISOLATE.
 * @start_pfn:		The lower PFN of the range to be isolated.
 * @end_pfn:		The upper PFN of the range to be isolated.
 *			start_pfn/end_pfn must be aligned to pageblock_order.
 * @migratetype:	Migrate type to set in error recovery.
 * @flags:		The following flags are allowed (they can be combined in
 *			a bit mask)
 *			MEMORY_OFFLINE - isolate to offline (!allocate) memory
 *					 e.g., skip over PageHWPoison() pages
 *					 and PageOffline() pages.
 *			REPORT_FAILURE - report details about the failure to
 *			isolate the range
 *
 * Making page-allocation-type to be MIGRATE_ISOLATE means मुक्त pages in
 * the range will never be allocated. Any मुक्त pages and pages मुक्तd in the
 * future will not be allocated again. If specअगरied range includes migrate types
 * other than MOVABLE or CMA, this will fail with -EBUSY. For isolating all
 * pages in the range finally, the caller have to मुक्त all pages in the range.
 * test_page_isolated() can be used क्रम test it.
 *
 * There is no high level synchronization mechanism that prevents two thपढ़ोs
 * from trying to isolate overlapping ranges. If this happens, one thपढ़ो
 * will notice pageblocks in the overlapping range alपढ़ोy set to isolate.
 * This happens in set_migratetype_isolate, and set_migratetype_isolate
 * वापसs an error. We then clean up by restoring the migration type on
 * pageblocks we may have modअगरied and वापस -EBUSY to caller. This
 * prevents two thपढ़ोs from simultaneously working on overlapping ranges.
 *
 * Please note that there is no strong synchronization with the page allocator
 * either. Pages might be मुक्तd जबतक their page blocks are marked ISOLATED.
 * A call to drain_all_pages() after isolation can flush most of them. However
 * in some हालs pages might still end up on pcp lists and that would allow
 * क्रम their allocation even when they are in fact isolated alपढ़ोy. Depending
 * on how strong of a guarantee the caller needs, zone_pcp_disable/enable()
 * might be used to flush and disable pcplist beक्रमe isolation and enable after
 * unisolation.
 *
 * Return: 0 on success and -EBUSY अगर any part of range cannot be isolated.
 */
पूर्णांक start_isolate_page_range(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			     अचिन्हित migratetype, पूर्णांक flags)
अणु
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ unकरो_pfn;
	काष्ठा page *page;

	BUG_ON(!IS_ALIGNED(start_pfn, pageblock_nr_pages));
	BUG_ON(!IS_ALIGNED(end_pfn, pageblock_nr_pages));

	क्रम (pfn = start_pfn;
	     pfn < end_pfn;
	     pfn += pageblock_nr_pages) अणु
		page = __first_valid_page(pfn, pageblock_nr_pages);
		अगर (page) अणु
			अगर (set_migratetype_isolate(page, migratetype, flags)) अणु
				unकरो_pfn = pfn;
				जाओ unकरो;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
unकरो:
	क्रम (pfn = start_pfn;
	     pfn < unकरो_pfn;
	     pfn += pageblock_nr_pages) अणु
		काष्ठा page *page = pfn_to_online_page(pfn);
		अगर (!page)
			जारी;
		unset_migratetype_isolate(page, migratetype);
	पूर्ण

	वापस -EBUSY;
पूर्ण

/*
 * Make isolated pages available again.
 */
व्योम unकरो_isolate_page_range(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			    अचिन्हित migratetype)
अणु
	अचिन्हित दीर्घ pfn;
	काष्ठा page *page;

	BUG_ON(!IS_ALIGNED(start_pfn, pageblock_nr_pages));
	BUG_ON(!IS_ALIGNED(end_pfn, pageblock_nr_pages));

	क्रम (pfn = start_pfn;
	     pfn < end_pfn;
	     pfn += pageblock_nr_pages) अणु
		page = __first_valid_page(pfn, pageblock_nr_pages);
		अगर (!page || !is_migrate_isolate_page(page))
			जारी;
		unset_migratetype_isolate(page, migratetype);
	पूर्ण
पूर्ण
/*
 * Test all pages in the range is मुक्त(means isolated) or not.
 * all pages in [start_pfn...end_pfn) must be in the same zone.
 * zone->lock must be held beक्रमe call this.
 *
 * Returns the last tested pfn.
 */
अटल अचिन्हित दीर्घ
__test_page_isolated_in_pageblock(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ end_pfn,
				  पूर्णांक flags)
अणु
	काष्ठा page *page;

	जबतक (pfn < end_pfn) अणु
		अगर (!pfn_valid_within(pfn)) अणु
			pfn++;
			जारी;
		पूर्ण
		page = pfn_to_page(pfn);
		अगर (PageBuddy(page))
			/*
			 * If the page is on a मुक्त list, it has to be on
			 * the correct MIGRATE_ISOLATE मुक्तlist. There is no
			 * simple way to verअगरy that as VM_BUG_ON(), though.
			 */
			pfn += 1 << buddy_order(page);
		अन्यथा अगर ((flags & MEMORY_OFFLINE) && PageHWPoison(page))
			/* A HWPoisoned page cannot be also PageBuddy */
			pfn++;
		अन्यथा अगर ((flags & MEMORY_OFFLINE) && PageOffline(page) &&
			 !page_count(page))
			/*
			 * The responsible driver agreed to skip PageOffline()
			 * pages when offlining memory by dropping its
			 * reference in MEM_GOING_OFFLINE.
			 */
			pfn++;
		अन्यथा
			अवरोध;
	पूर्ण

	वापस pfn;
पूर्ण

/* Caller should ensure that requested range is in a single zone */
पूर्णांक test_pages_isolated(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			पूर्णांक isol_flags)
अणु
	अचिन्हित दीर्घ pfn, flags;
	काष्ठा page *page;
	काष्ठा zone *zone;

	/*
	 * Note: pageblock_nr_pages != MAX_ORDER. Then, chunks of मुक्त pages
	 * are not aligned to pageblock_nr_pages.
	 * Then we just check migratetype first.
	 */
	क्रम (pfn = start_pfn; pfn < end_pfn; pfn += pageblock_nr_pages) अणु
		page = __first_valid_page(pfn, pageblock_nr_pages);
		अगर (page && !is_migrate_isolate_page(page))
			अवरोध;
	पूर्ण
	page = __first_valid_page(start_pfn, end_pfn - start_pfn);
	अगर ((pfn < end_pfn) || !page)
		वापस -EBUSY;
	/* Check all pages are मुक्त or marked as ISOLATED */
	zone = page_zone(page);
	spin_lock_irqsave(&zone->lock, flags);
	pfn = __test_page_isolated_in_pageblock(start_pfn, end_pfn, isol_flags);
	spin_unlock_irqrestore(&zone->lock, flags);

	trace_test_pages_isolated(start_pfn, end_pfn, pfn);

	वापस pfn < end_pfn ? -EBUSY : 0;
पूर्ण
