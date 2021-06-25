<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PAGEISOLATION_H
#घोषणा __LINUX_PAGEISOLATION_H

#अगर_घोषित CONFIG_MEMORY_ISOLATION
अटल अंतरभूत bool has_isolate_pageblock(काष्ठा zone *zone)
अणु
	वापस zone->nr_isolate_pageblock;
पूर्ण
अटल अंतरभूत bool is_migrate_isolate_page(काष्ठा page *page)
अणु
	वापस get_pageblock_migratetype(page) == MIGRATE_ISOLATE;
पूर्ण
अटल अंतरभूत bool is_migrate_isolate(पूर्णांक migratetype)
अणु
	वापस migratetype == MIGRATE_ISOLATE;
पूर्ण
#अन्यथा
अटल अंतरभूत bool has_isolate_pageblock(काष्ठा zone *zone)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool is_migrate_isolate_page(काष्ठा page *page)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool is_migrate_isolate(पूर्णांक migratetype)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#घोषणा MEMORY_OFFLINE	0x1
#घोषणा REPORT_FAILURE	0x2

काष्ठा page *has_unmovable_pages(काष्ठा zone *zone, काष्ठा page *page,
				 पूर्णांक migratetype, पूर्णांक flags);
व्योम set_pageblock_migratetype(काष्ठा page *page, पूर्णांक migratetype);
पूर्णांक move_मुक्तpages_block(काष्ठा zone *zone, काष्ठा page *page,
				पूर्णांक migratetype, पूर्णांक *num_movable);

/*
 * Changes migrate type in [start_pfn, end_pfn) to be MIGRATE_ISOLATE.
 */
पूर्णांक
start_isolate_page_range(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			 अचिन्हित migratetype, पूर्णांक flags);

/*
 * Changes MIGRATE_ISOLATE to MIGRATE_MOVABLE.
 * target range is [start_pfn, end_pfn)
 */
व्योम
unकरो_isolate_page_range(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			अचिन्हित migratetype);

/*
 * Test all pages in [start_pfn, end_pfn) are isolated or not.
 */
पूर्णांक test_pages_isolated(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			पूर्णांक isol_flags);

काष्ठा page *alloc_migrate_target(काष्ठा page *page, अचिन्हित दीर्घ निजी);

#पूर्ण_अगर
