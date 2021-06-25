<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XEN_PAGE_H
#घोषणा _XEN_PAGE_H

#समावेश <यंत्र/page.h>

/* The hypercall पूर्णांकerface supports only 4KB page */
#घोषणा XEN_PAGE_SHIFT	12
#घोषणा XEN_PAGE_SIZE	(_AC(1, UL) << XEN_PAGE_SHIFT)
#घोषणा XEN_PAGE_MASK	(~(XEN_PAGE_SIZE-1))
#घोषणा xen_offset_in_page(p)	((अचिन्हित दीर्घ)(p) & ~XEN_PAGE_MASK)

/*
 * We assume that PAGE_SIZE is a multiple of XEN_PAGE_SIZE
 * XXX: Add a BUILD_BUG_ON?
 */

#घोषणा xen_pfn_to_page(xen_pfn)	\
	(pfn_to_page((अचिन्हित दीर्घ)(xen_pfn) >> (PAGE_SHIFT - XEN_PAGE_SHIFT)))
#घोषणा page_to_xen_pfn(page)		\
	((page_to_pfn(page)) << (PAGE_SHIFT - XEN_PAGE_SHIFT))

#घोषणा XEN_PFN_PER_PAGE	(PAGE_SIZE / XEN_PAGE_SIZE)

#घोषणा XEN_PFN_DOWN(x)	((x) >> XEN_PAGE_SHIFT)
#घोषणा XEN_PFN_UP(x)	(((x) + XEN_PAGE_SIZE-1) >> XEN_PAGE_SHIFT)

#समावेश <यंत्र/xen/page.h>

/* Return the GFN associated to the first 4KB of the page */
अटल अंतरभूत अचिन्हित दीर्घ xen_page_to_gfn(काष्ठा page *page)
अणु
	वापस pfn_to_gfn(page_to_xen_pfn(page));
पूर्ण

काष्ठा xen_memory_region अणु
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ n_pfns;
पूर्ण;

#घोषणा XEN_EXTRA_MEM_MAX_REGIONS 128 /* == E820_MAX_ENTRIES_ZEROPAGE */

बाह्य __initdata
काष्ठा xen_memory_region xen_extra_mem[XEN_EXTRA_MEM_MAX_REGIONS];

बाह्य अचिन्हित दीर्घ xen_released_pages;

#पूर्ण_अगर	/* _XEN_PAGE_H */
