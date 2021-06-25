<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_MM_INLINE_H
#घोषणा LINUX_MM_INLINE_H

#समावेश <linux/huge_mm.h>
#समावेश <linux/swap.h>

/**
 * page_is_file_lru - should the page be on a file LRU or anon LRU?
 * @page: the page to test
 *
 * Returns 1 अगर @page is a regular fileप्रणाली backed page cache page or a lazily
 * मुक्तd anonymous page (e.g. via MADV_FREE).  Returns 0 अगर @page is a normal
 * anonymous page, a पंचांगpfs page or otherwise ram or swap backed page.  Used by
 * functions that manipulate the LRU lists, to sort a page onto the right LRU
 * list.
 *
 * We would like to get this info without a page flag, but the state
 * needs to survive until the page is last deleted from the LRU, which
 * could be as far करोwn as __page_cache_release.
 */
अटल अंतरभूत पूर्णांक page_is_file_lru(काष्ठा page *page)
अणु
	वापस !PageSwapBacked(page);
पूर्ण

अटल __always_अंतरभूत व्योम update_lru_size(काष्ठा lruvec *lruvec,
				क्रमागत lru_list lru, क्रमागत zone_type zid,
				पूर्णांक nr_pages)
अणु
	काष्ठा pglist_data *pgdat = lruvec_pgdat(lruvec);

	__mod_lruvec_state(lruvec, NR_LRU_BASE + lru, nr_pages);
	__mod_zone_page_state(&pgdat->node_zones[zid],
				NR_ZONE_LRU_BASE + lru, nr_pages);
#अगर_घोषित CONFIG_MEMCG
	mem_cgroup_update_lru_size(lruvec, lru, zid, nr_pages);
#पूर्ण_अगर
पूर्ण

/**
 * __clear_page_lru_flags - clear page lru flags beक्रमe releasing a page
 * @page: the page that was on lru and now has a zero reference
 */
अटल __always_अंतरभूत व्योम __clear_page_lru_flags(काष्ठा page *page)
अणु
	VM_BUG_ON_PAGE(!PageLRU(page), page);

	__ClearPageLRU(page);

	/* this shouldn't happen, so leave the flags to bad_page() */
	अगर (PageActive(page) && PageUnevictable(page))
		वापस;

	__ClearPageActive(page);
	__ClearPageUnevictable(page);
पूर्ण

/**
 * page_lru - which LRU list should a page be on?
 * @page: the page to test
 *
 * Returns the LRU list a page should be on, as an index
 * पूर्णांकo the array of LRU lists.
 */
अटल __always_अंतरभूत क्रमागत lru_list page_lru(काष्ठा page *page)
अणु
	क्रमागत lru_list lru;

	VM_BUG_ON_PAGE(PageActive(page) && PageUnevictable(page), page);

	अगर (PageUnevictable(page))
		वापस LRU_UNEVICTABLE;

	lru = page_is_file_lru(page) ? LRU_INACTIVE_खाता : LRU_INACTIVE_ANON;
	अगर (PageActive(page))
		lru += LRU_ACTIVE;

	वापस lru;
पूर्ण

अटल __always_अंतरभूत व्योम add_page_to_lru_list(काष्ठा page *page,
				काष्ठा lruvec *lruvec)
अणु
	क्रमागत lru_list lru = page_lru(page);

	update_lru_size(lruvec, lru, page_zonक्रमागत(page), thp_nr_pages(page));
	list_add(&page->lru, &lruvec->lists[lru]);
पूर्ण

अटल __always_अंतरभूत व्योम add_page_to_lru_list_tail(काष्ठा page *page,
				काष्ठा lruvec *lruvec)
अणु
	क्रमागत lru_list lru = page_lru(page);

	update_lru_size(lruvec, lru, page_zonक्रमागत(page), thp_nr_pages(page));
	list_add_tail(&page->lru, &lruvec->lists[lru]);
पूर्ण

अटल __always_अंतरभूत व्योम del_page_from_lru_list(काष्ठा page *page,
				काष्ठा lruvec *lruvec)
अणु
	list_del(&page->lru);
	update_lru_size(lruvec, page_lru(page), page_zonक्रमागत(page),
			-thp_nr_pages(page));
पूर्ण
#पूर्ण_अगर
