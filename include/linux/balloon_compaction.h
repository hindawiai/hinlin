<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/balloon_compaction.h
 *
 * Common पूर्णांकerface definitions क्रम making balloon pages movable by compaction.
 *
 * Balloon page migration makes use of the general non-lru movable page
 * feature.
 *
 * page->निजी is used to reference the responsible balloon device.
 * page->mapping is used in context of non-lru page migration to reference
 * the address space operations क्रम page isolation/migration/compaction.
 *
 * As the page isolation scanning step a compaction thपढ़ो करोes is a lockless
 * procedure (from a page standpoपूर्णांक), it might bring some racy situations जबतक
 * perक्रमming balloon page compaction. In order to sort out these racy scenarios
 * and safely perक्रमm balloon's page compaction and migration we must, always,
 * ensure following these simple rules:
 *
 *   i. when updating a balloon's page ->mapping element, strictly करो it under
 *      the following lock order, independently of the far superior
 *      locking scheme (lru_lock, balloon_lock):
 *	    +-page_lock(page);
 *	      +--spin_lock_irq(&b_dev_info->pages_lock);
 *	            ... page->mapping updates here ...
 *
 *  ii. isolation or dequeueing procedure must हटाओ the page from balloon
 *      device page list under b_dev_info->pages_lock.
 *
 * The functions provided by this पूर्णांकerface are placed to help on coping with
 * the aक्रमementioned balloon page corner हाल, as well as to ensure the simple
 * set of exposed rules are satisfied जबतक we are dealing with balloon pages
 * compaction / migration.
 *
 * Copyright (C) 2012, Red Hat, Inc.  Rafael Aquini <aquini@redhat.com>
 */
#अगर_अघोषित _LINUX_BALLOON_COMPACTION_H
#घोषणा _LINUX_BALLOON_COMPACTION_H
#समावेश <linux/pagemap.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/migrate.h>
#समावेश <linux/gfp.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>

/*
 * Balloon device inक्रमmation descriptor.
 * This काष्ठा is used to allow the common balloon compaction पूर्णांकerface
 * procedures to find the proper balloon device holding memory pages they'll
 * have to cope क्रम page compaction / migration, as well as it serves the
 * balloon driver as a page book-keeper क्रम its रेजिस्टरed balloon devices.
 */
काष्ठा balloon_dev_info अणु
	अचिन्हित दीर्घ isolated_pages;	/* # of isolated pages क्रम migration */
	spinlock_t pages_lock;		/* Protection to pages list */
	काष्ठा list_head pages;		/* Pages enqueued & handled to Host */
	पूर्णांक (*migratepage)(काष्ठा balloon_dev_info *, काष्ठा page *newpage,
			काष्ठा page *page, क्रमागत migrate_mode mode);
	काष्ठा inode *inode;
पूर्ण;

बाह्य काष्ठा page *balloon_page_alloc(व्योम);
बाह्य व्योम balloon_page_enqueue(काष्ठा balloon_dev_info *b_dev_info,
				 काष्ठा page *page);
बाह्य काष्ठा page *balloon_page_dequeue(काष्ठा balloon_dev_info *b_dev_info);
बाह्य माप_प्रकार balloon_page_list_enqueue(काष्ठा balloon_dev_info *b_dev_info,
				      काष्ठा list_head *pages);
बाह्य माप_प्रकार balloon_page_list_dequeue(काष्ठा balloon_dev_info *b_dev_info,
				     काष्ठा list_head *pages, माप_प्रकार n_req_pages);

अटल अंतरभूत व्योम balloon_devinfo_init(काष्ठा balloon_dev_info *balloon)
अणु
	balloon->isolated_pages = 0;
	spin_lock_init(&balloon->pages_lock);
	INIT_LIST_HEAD(&balloon->pages);
	balloon->migratepage = शून्य;
	balloon->inode = शून्य;
पूर्ण

#अगर_घोषित CONFIG_BALLOON_COMPACTION
बाह्य स्थिर काष्ठा address_space_operations balloon_aops;
बाह्य bool balloon_page_isolate(काष्ठा page *page,
				isolate_mode_t mode);
बाह्य व्योम balloon_page_putback(काष्ठा page *page);
बाह्य पूर्णांक balloon_page_migrate(काष्ठा address_space *mapping,
				काष्ठा page *newpage,
				काष्ठा page *page, क्रमागत migrate_mode mode);

/*
 * balloon_page_insert - insert a page पूर्णांकo the balloon's page list and make
 *			 the page->निजी assignment accordingly.
 * @balloon : poपूर्णांकer to balloon device
 * @page    : page to be asचिन्हित as a 'balloon page'
 *
 * Caller must ensure the page is locked and the spin_lock protecting balloon
 * pages list is held beक्रमe inserting a page पूर्णांकo the balloon device.
 */
अटल अंतरभूत व्योम balloon_page_insert(काष्ठा balloon_dev_info *balloon,
				       काष्ठा page *page)
अणु
	__SetPageOffline(page);
	__SetPageMovable(page, balloon->inode->i_mapping);
	set_page_निजी(page, (अचिन्हित दीर्घ)balloon);
	list_add(&page->lru, &balloon->pages);
पूर्ण

/*
 * balloon_page_delete - delete a page from balloon's page list and clear
 *			 the page->निजी assignement accordingly.
 * @page    : page to be released from balloon's page list
 *
 * Caller must ensure the page is locked and the spin_lock protecting balloon
 * pages list is held beक्रमe deleting a page from the balloon device.
 */
अटल अंतरभूत व्योम balloon_page_delete(काष्ठा page *page)
अणु
	__ClearPageOffline(page);
	__ClearPageMovable(page);
	set_page_निजी(page, 0);
	/*
	 * No touch page.lru field once @page has been isolated
	 * because VM is using the field.
	 */
	अगर (!PageIsolated(page))
		list_del(&page->lru);
पूर्ण

/*
 * balloon_page_device - get the b_dev_info descriptor क्रम the balloon device
 *			 that enqueues the given page.
 */
अटल अंतरभूत काष्ठा balloon_dev_info *balloon_page_device(काष्ठा page *page)
अणु
	वापस (काष्ठा balloon_dev_info *)page_निजी(page);
पूर्ण

अटल अंतरभूत gfp_t balloon_mapping_gfp_mask(व्योम)
अणु
	वापस GFP_HIGHUSER_MOVABLE;
पूर्ण

#अन्यथा /* !CONFIG_BALLOON_COMPACTION */

अटल अंतरभूत व्योम balloon_page_insert(काष्ठा balloon_dev_info *balloon,
				       काष्ठा page *page)
अणु
	__SetPageOffline(page);
	list_add(&page->lru, &balloon->pages);
पूर्ण

अटल अंतरभूत व्योम balloon_page_delete(काष्ठा page *page)
अणु
	__ClearPageOffline(page);
	list_del(&page->lru);
पूर्ण

अटल अंतरभूत bool balloon_page_isolate(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम balloon_page_putback(काष्ठा page *page)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक balloon_page_migrate(काष्ठा page *newpage,
				काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत gfp_t balloon_mapping_gfp_mask(व्योम)
अणु
	वापस GFP_HIGHUSER;
पूर्ण

#पूर्ण_अगर /* CONFIG_BALLOON_COMPACTION */

/*
 * balloon_page_push - insert a page पूर्णांकo a page list.
 * @head : poपूर्णांकer to list
 * @page : page to be added
 *
 * Caller must ensure the page is निजी and protect the list.
 */
अटल अंतरभूत व्योम balloon_page_push(काष्ठा list_head *pages, काष्ठा page *page)
अणु
	list_add(&page->lru, pages);
पूर्ण

/*
 * balloon_page_pop - हटाओ a page from a page list.
 * @head : poपूर्णांकer to list
 * @page : page to be added
 *
 * Caller must ensure the page is निजी and protect the list.
 */
अटल अंतरभूत काष्ठा page *balloon_page_pop(काष्ठा list_head *pages)
अणु
	काष्ठा page *page = list_first_entry_or_null(pages, काष्ठा page, lru);

	अगर (!page)
		वापस शून्य;

	list_del(&page->lru);
	वापस page;
पूर्ण
#पूर्ण_अगर /* _LINUX_BALLOON_COMPACTION_H */
