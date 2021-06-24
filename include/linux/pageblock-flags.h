<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Macros क्रम manipulating and testing flags related to a
 * pageblock_nr_pages number of pages.
 *
 * Copyright (C) IBM Corporation, 2006
 *
 * Original author, Mel Gorman
 * Major cleanups and reduction of bit operations, Andy Whitcroft
 */
#अगर_अघोषित PAGEBLOCK_FLAGS_H
#घोषणा PAGEBLOCK_FLAGS_H

#समावेश <linux/types.h>

#घोषणा PB_migratetype_bits 3
/* Bit indices that affect a whole block of pages */
क्रमागत pageblock_bits अणु
	PB_migrate,
	PB_migrate_end = PB_migrate + PB_migratetype_bits - 1,
			/* 3 bits required क्रम migrate types */
	PB_migrate_skip,/* If set the block is skipped by compaction */

	/*
	 * Assume the bits will always align on a word. If this assumption
	 * changes then get/set pageblock needs updating.
	 */
	NR_PAGEBLOCK_BITS
पूर्ण;

#अगर_घोषित CONFIG_HUGETLB_PAGE

#अगर_घोषित CONFIG_HUGETLB_PAGE_SIZE_VARIABLE

/* Huge page sizes are variable */
बाह्य अचिन्हित पूर्णांक pageblock_order;

#अन्यथा /* CONFIG_HUGETLB_PAGE_SIZE_VARIABLE */

/* Huge pages are a स्थिरant size */
#घोषणा pageblock_order		HUGETLB_PAGE_ORDER

#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE_SIZE_VARIABLE */

#अन्यथा /* CONFIG_HUGETLB_PAGE */

/* If huge pages are not used, group by MAX_ORDER_NR_PAGES */
#घोषणा pageblock_order		(MAX_ORDER-1)

#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

#घोषणा pageblock_nr_pages	(1UL << pageblock_order)

/* Forward declaration */
काष्ठा page;

अचिन्हित दीर्घ get_pfnblock_flags_mask(काष्ठा page *page,
				अचिन्हित दीर्घ pfn,
				अचिन्हित दीर्घ mask);

व्योम set_pfnblock_flags_mask(काष्ठा page *page,
				अचिन्हित दीर्घ flags,
				अचिन्हित दीर्घ pfn,
				अचिन्हित दीर्घ mask);

/* Declarations क्रम getting and setting flags. See mm/page_alloc.c */
#अगर_घोषित CONFIG_COMPACTION
#घोषणा get_pageblock_skip(page) \
	get_pfnblock_flags_mask(page, page_to_pfn(page),	\
			(1 << (PB_migrate_skip)))
#घोषणा clear_pageblock_skip(page) \
	set_pfnblock_flags_mask(page, 0, page_to_pfn(page),	\
			(1 << PB_migrate_skip))
#घोषणा set_pageblock_skip(page) \
	set_pfnblock_flags_mask(page, (1 << PB_migrate_skip),	\
			page_to_pfn(page),			\
			(1 << PB_migrate_skip))
#अन्यथा
अटल अंतरभूत bool get_pageblock_skip(काष्ठा page *page)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम clear_pageblock_skip(काष्ठा page *page)
अणु
पूर्ण
अटल अंतरभूत व्योम set_pageblock_skip(काष्ठा page *page)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPACTION */

#पूर्ण_अगर	/* PAGEBLOCK_FLAGS_H */
