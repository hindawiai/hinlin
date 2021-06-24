<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/balloon_compaction.c
 *
 * Common पूर्णांकerface क्रम making balloon pages movable by compaction.
 *
 * Copyright (C) 2012, Red Hat, Inc.  Rafael Aquini <aquini@redhat.com>
 */
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/balloon_compaction.h>

अटल व्योम balloon_page_enqueue_one(काष्ठा balloon_dev_info *b_dev_info,
				     काष्ठा page *page)
अणु
	/*
	 * Block others from accessing the 'page' when we get around to
	 * establishing additional references. We should be the only one
	 * holding a reference to the 'page' at this poपूर्णांक. If we are not, then
	 * memory corruption is possible and we should stop execution.
	 */
	BUG_ON(!trylock_page(page));
	balloon_page_insert(b_dev_info, page);
	unlock_page(page);
	__count_vm_event(BALLOON_INFLATE);
पूर्ण

/**
 * balloon_page_list_enqueue() - inserts a list of pages पूर्णांकo the balloon page
 *				 list.
 * @b_dev_info: balloon device descriptor where we will insert a new page to
 * @pages: pages to enqueue - allocated using balloon_page_alloc.
 *
 * Driver must call this function to properly enqueue balloon pages beक्रमe
 * definitively removing them from the guest प्रणाली.
 *
 * Return: number of pages that were enqueued.
 */
माप_प्रकार balloon_page_list_enqueue(काष्ठा balloon_dev_info *b_dev_info,
				 काष्ठा list_head *pages)
अणु
	काष्ठा page *page, *पंचांगp;
	अचिन्हित दीर्घ flags;
	माप_प्रकार n_pages = 0;

	spin_lock_irqsave(&b_dev_info->pages_lock, flags);
	list_क्रम_each_entry_safe(page, पंचांगp, pages, lru) अणु
		list_del(&page->lru);
		balloon_page_enqueue_one(b_dev_info, page);
		n_pages++;
	पूर्ण
	spin_unlock_irqrestore(&b_dev_info->pages_lock, flags);
	वापस n_pages;
पूर्ण
EXPORT_SYMBOL_GPL(balloon_page_list_enqueue);

/**
 * balloon_page_list_dequeue() - हटाओs pages from balloon's page list and
 *				 वापसs a list of the pages.
 * @b_dev_info: balloon device descriptor where we will grab a page from.
 * @pages: poपूर्णांकer to the list of pages that would be वापसed to the caller.
 * @n_req_pages: number of requested pages.
 *
 * Driver must call this function to properly de-allocate a previous enlisted
 * balloon pages beक्रमe definitively releasing it back to the guest प्रणाली.
 * This function tries to हटाओ @n_req_pages from the ballooned pages and
 * वापस them to the caller in the @pages list.
 *
 * Note that this function may fail to dequeue some pages even अगर the balloon
 * isn't empty - since the page list can be temporarily empty due to compaction
 * of isolated pages.
 *
 * Return: number of pages that were added to the @pages list.
 */
माप_प्रकार balloon_page_list_dequeue(काष्ठा balloon_dev_info *b_dev_info,
				 काष्ठा list_head *pages, माप_प्रकार n_req_pages)
अणु
	काष्ठा page *page, *पंचांगp;
	अचिन्हित दीर्घ flags;
	माप_प्रकार n_pages = 0;

	spin_lock_irqsave(&b_dev_info->pages_lock, flags);
	list_क्रम_each_entry_safe(page, पंचांगp, &b_dev_info->pages, lru) अणु
		अगर (n_pages == n_req_pages)
			अवरोध;

		/*
		 * Block others from accessing the 'page' जबतक we get around to
		 * establishing additional references and preparing the 'page'
		 * to be released by the balloon driver.
		 */
		अगर (!trylock_page(page))
			जारी;

		अगर (IS_ENABLED(CONFIG_BALLOON_COMPACTION) &&
		    PageIsolated(page)) अणु
			/* raced with isolation */
			unlock_page(page);
			जारी;
		पूर्ण
		balloon_page_delete(page);
		__count_vm_event(BALLOON_DEFLATE);
		list_add(&page->lru, pages);
		unlock_page(page);
		n_pages++;
	पूर्ण
	spin_unlock_irqrestore(&b_dev_info->pages_lock, flags);

	वापस n_pages;
पूर्ण
EXPORT_SYMBOL_GPL(balloon_page_list_dequeue);

/*
 * balloon_page_alloc - allocates a new page क्रम insertion पूर्णांकo the balloon
 *			page list.
 *
 * Driver must call this function to properly allocate a new balloon page.
 * Driver must call balloon_page_enqueue beक्रमe definitively removing the page
 * from the guest प्रणाली.
 *
 * Return: काष्ठा page क्रम the allocated page or शून्य on allocation failure.
 */
काष्ठा page *balloon_page_alloc(व्योम)
अणु
	काष्ठा page *page = alloc_page(balloon_mapping_gfp_mask() |
				       __GFP_NOMEMALLOC | __GFP_NORETRY |
				       __GFP_NOWARN);
	वापस page;
पूर्ण
EXPORT_SYMBOL_GPL(balloon_page_alloc);

/*
 * balloon_page_enqueue - inserts a new page पूर्णांकo the balloon page list.
 *
 * @b_dev_info: balloon device descriptor where we will insert a new page
 * @page: new page to enqueue - allocated using balloon_page_alloc.
 *
 * Drivers must call this function to properly enqueue a new allocated balloon
 * page beक्रमe definitively removing the page from the guest प्रणाली.
 *
 * Drivers must not call balloon_page_enqueue on pages that have been pushed to
 * a list with balloon_page_push beक्रमe removing them with balloon_page_pop. To
 * enqueue a list of pages, use balloon_page_list_enqueue instead.
 */
व्योम balloon_page_enqueue(काष्ठा balloon_dev_info *b_dev_info,
			  काष्ठा page *page)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&b_dev_info->pages_lock, flags);
	balloon_page_enqueue_one(b_dev_info, page);
	spin_unlock_irqrestore(&b_dev_info->pages_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(balloon_page_enqueue);

/*
 * balloon_page_dequeue - हटाओs a page from balloon's page list and वापसs
 *			  its address to allow the driver to release the page.
 * @b_dev_info: balloon device descriptor where we will grab a page from.
 *
 * Driver must call this function to properly dequeue a previously enqueued page
 * beक्रमe definitively releasing it back to the guest प्रणाली.
 *
 * Caller must perक्रमm its own accounting to ensure that this
 * function is called only अगर some pages are actually enqueued.
 *
 * Note that this function may fail to dequeue some pages even अगर there are
 * some enqueued pages - since the page list can be temporarily empty due to
 * the compaction of isolated pages.
 *
 * TODO: हटाओ the caller accounting requirements, and allow caller to रुको
 * until all pages can be dequeued.
 *
 * Return: काष्ठा page क्रम the dequeued page, or शून्य अगर no page was dequeued.
 */
काष्ठा page *balloon_page_dequeue(काष्ठा balloon_dev_info *b_dev_info)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(pages);
	पूर्णांक n_pages;

	n_pages = balloon_page_list_dequeue(b_dev_info, &pages, 1);

	अगर (n_pages != 1) अणु
		/*
		 * If we are unable to dequeue a balloon page because the page
		 * list is empty and there are no isolated pages, then something
		 * went out of track and some balloon pages are lost.
		 * BUG() here, otherwise the balloon driver may get stuck in
		 * an infinite loop जबतक attempting to release all its pages.
		 */
		spin_lock_irqsave(&b_dev_info->pages_lock, flags);
		अगर (unlikely(list_empty(&b_dev_info->pages) &&
			     !b_dev_info->isolated_pages))
			BUG();
		spin_unlock_irqrestore(&b_dev_info->pages_lock, flags);
		वापस शून्य;
	पूर्ण
	वापस list_first_entry(&pages, काष्ठा page, lru);
पूर्ण
EXPORT_SYMBOL_GPL(balloon_page_dequeue);

#अगर_घोषित CONFIG_BALLOON_COMPACTION

bool balloon_page_isolate(काष्ठा page *page, isolate_mode_t mode)

अणु
	काष्ठा balloon_dev_info *b_dev_info = balloon_page_device(page);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&b_dev_info->pages_lock, flags);
	list_del(&page->lru);
	b_dev_info->isolated_pages++;
	spin_unlock_irqrestore(&b_dev_info->pages_lock, flags);

	वापस true;
पूर्ण

व्योम balloon_page_putback(काष्ठा page *page)
अणु
	काष्ठा balloon_dev_info *b_dev_info = balloon_page_device(page);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&b_dev_info->pages_lock, flags);
	list_add(&page->lru, &b_dev_info->pages);
	b_dev_info->isolated_pages--;
	spin_unlock_irqrestore(&b_dev_info->pages_lock, flags);
पूर्ण


/* move_to_new_page() counterpart क्रम a ballooned page */
पूर्णांक balloon_page_migrate(काष्ठा address_space *mapping,
		काष्ठा page *newpage, काष्ठा page *page,
		क्रमागत migrate_mode mode)
अणु
	काष्ठा balloon_dev_info *balloon = balloon_page_device(page);

	/*
	 * We can not easily support the no copy हाल here so ignore it as it
	 * is unlikely to be used with balloon pages. See include/linux/hmm.h
	 * क्रम a user of the MIGRATE_SYNC_NO_COPY mode.
	 */
	अगर (mode == MIGRATE_SYNC_NO_COPY)
		वापस -EINVAL;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(!PageLocked(newpage), newpage);

	वापस balloon->migratepage(balloon, newpage, page, mode);
पूर्ण

स्थिर काष्ठा address_space_operations balloon_aops = अणु
	.migratepage = balloon_page_migrate,
	.isolate_page = balloon_page_isolate,
	.putback_page = balloon_page_putback,
पूर्ण;
EXPORT_SYMBOL_GPL(balloon_aops);

#पूर्ण_अगर /* CONFIG_BALLOON_COMPACTION */
