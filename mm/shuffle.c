<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright(c) 2018 Intel Corporation. All rights reserved.

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/moduleparam.h>
#समावेश "internal.h"
#समावेश "shuffle.h"

DEFINE_STATIC_KEY_FALSE(page_alloc_shuffle_key);

अटल bool shuffle_param;
अटल पूर्णांक shuffle_show(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%c\n", shuffle_param ? 'Y' : 'N');
पूर्ण

अटल __meminit पूर्णांक shuffle_store(स्थिर अक्षर *val,
		स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rc = param_set_bool(val, kp);

	अगर (rc < 0)
		वापस rc;
	अगर (shuffle_param)
		अटल_branch_enable(&page_alloc_shuffle_key);
	वापस 0;
पूर्ण
module_param_call(shuffle, shuffle_store, shuffle_show, &shuffle_param, 0400);

/*
 * For two pages to be swapped in the shuffle, they must be मुक्त (on a
 * 'free_area' lru), have the same order, and have the same migratetype.
 */
अटल काष्ठा page * __meminit shuffle_valid_page(काष्ठा zone *zone,
						  अचिन्हित दीर्घ pfn, पूर्णांक order)
अणु
	काष्ठा page *page = pfn_to_online_page(pfn);

	/*
	 * Given we're dealing with अक्रमomly selected pfns in a zone we
	 * need to ask questions like...
	 */

	/* ... is the page managed by the buddy? */
	अगर (!page)
		वापस शून्य;

	/* ... is the page asचिन्हित to the same zone? */
	अगर (page_zone(page) != zone)
		वापस शून्य;

	/* ...is the page मुक्त and currently on a मुक्त_area list? */
	अगर (!PageBuddy(page))
		वापस शून्य;

	/*
	 * ...is the page on the same list as the page we will
	 * shuffle it with?
	 */
	अगर (buddy_order(page) != order)
		वापस शून्य;

	वापस page;
पूर्ण

/*
 * Fisher-Yates shuffle the मुक्तlist which prescribes iterating through an
 * array, pfns in this हाल, and अक्रमomly swapping each entry with another in
 * the span, end_pfn - start_pfn.
 *
 * To keep the implementation simple it करोes not attempt to correct क्रम sources
 * of bias in the distribution, like modulo bias or pseuकरो-अक्रमom number
 * generator bias. I.e. the expectation is that this shuffling उठाओs the bar
 * क्रम attacks that exploit the predictability of page allocations, but need not
 * be a perfect shuffle.
 */
#घोषणा SHUFFLE_RETRY 10
व्योम __meminit __shuffle_zone(काष्ठा zone *z)
अणु
	अचिन्हित दीर्घ i, flags;
	अचिन्हित दीर्घ start_pfn = z->zone_start_pfn;
	अचिन्हित दीर्घ end_pfn = zone_end_pfn(z);
	स्थिर पूर्णांक order = SHUFFLE_ORDER;
	स्थिर पूर्णांक order_pages = 1 << order;

	spin_lock_irqsave(&z->lock, flags);
	start_pfn = ALIGN(start_pfn, order_pages);
	क्रम (i = start_pfn; i < end_pfn; i += order_pages) अणु
		अचिन्हित दीर्घ j;
		पूर्णांक migratetype, retry;
		काष्ठा page *page_i, *page_j;

		/*
		 * We expect page_i, in the sub-range of a zone being added
		 * (@start_pfn to @end_pfn), to more likely be valid compared to
		 * page_j अक्रमomly selected in the span @zone_start_pfn to
		 * @spanned_pages.
		 */
		page_i = shuffle_valid_page(z, i, order);
		अगर (!page_i)
			जारी;

		क्रम (retry = 0; retry < SHUFFLE_RETRY; retry++) अणु
			/*
			 * Pick a अक्रमom order aligned page in the zone span as
			 * a swap target. If the selected pfn is a hole, retry
			 * up to SHUFFLE_RETRY attempts find a अक्रमom valid pfn
			 * in the zone.
			 */
			j = z->zone_start_pfn +
				ALIGN_DOWN(get_अक्रमom_दीर्घ() % z->spanned_pages,
						order_pages);
			page_j = shuffle_valid_page(z, j, order);
			अगर (page_j && page_j != page_i)
				अवरोध;
		पूर्ण
		अगर (retry >= SHUFFLE_RETRY) अणु
			pr_debug("%s: failed to swap %#lx\n", __func__, i);
			जारी;
		पूर्ण

		/*
		 * Each migratetype corresponds to its own list, make sure the
		 * types match otherwise we're moving pages to lists where they
		 * करो not beदीर्घ.
		 */
		migratetype = get_pageblock_migratetype(page_i);
		अगर (get_pageblock_migratetype(page_j) != migratetype) अणु
			pr_debug("%s: migratetype mismatch %#lx\n", __func__, i);
			जारी;
		पूर्ण

		list_swap(&page_i->lru, &page_j->lru);

		pr_debug("%s: swap: %#lx -> %#lx\n", __func__, i, j);

		/* take it easy on the zone lock */
		अगर ((i % (100 * order_pages)) == 0) अणु
			spin_unlock_irqrestore(&z->lock, flags);
			cond_resched();
			spin_lock_irqsave(&z->lock, flags);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&z->lock, flags);
पूर्ण

/*
 * __shuffle_मुक्त_memory - reduce the predictability of the page allocator
 * @pgdat: node page data
 */
व्योम __meminit __shuffle_मुक्त_memory(pg_data_t *pgdat)
अणु
	काष्ठा zone *z;

	क्रम (z = pgdat->node_zones; z < pgdat->node_zones + MAX_NR_ZONES; z++)
		shuffle_zone(z);
पूर्ण

bool shuffle_pick_tail(व्योम)
अणु
	अटल u64 अक्रम;
	अटल u8 अक्रम_bits;
	bool ret;

	/*
	 * The lack of locking is deliberate. If 2 thपढ़ोs race to
	 * update the अक्रम state it just adds to the entropy.
	 */
	अगर (अक्रम_bits == 0) अणु
		अक्रम_bits = 64;
		अक्रम = get_अक्रमom_u64();
	पूर्ण

	ret = अक्रम & 1;

	अक्रम_bits--;
	अक्रम >>= 1;

	वापस ret;
पूर्ण
