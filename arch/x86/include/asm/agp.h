<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_AGP_H
#घोषणा _ASM_X86_AGP_H

#समावेश <linux/pgtable.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * Functions to keep the agpgart mappings coherent with the MMU. The
 * GART gives the CPU a physical alias of pages in memory. The alias
 * region is mapped uncacheable. Make sure there are no conflicting
 * mappings with dअगरferent cacheability attributes क्रम the same
 * page. This aव्योमs data corruption on some CPUs.
 */

#घोषणा map_page_पूर्णांकo_agp(page) set_pages_uc(page, 1)
#घोषणा unmap_page_from_agp(page) set_pages_wb(page, 1)

/*
 * Could use CLFLUSH here अगर the cpu supports it. But then it would
 * need to be called क्रम each cacheline of the whole page so it may
 * not be worth it. Would need a page क्रम it.
 */
#घोषणा flush_agp_cache() wbinvd()

/* GATT allocation. Returns/accepts GATT kernel भव address. */
#घोषणा alloc_gatt_pages(order)		\
	((अक्षर *)__get_मुक्त_pages(GFP_KERNEL, (order)))
#घोषणा मुक्त_gatt_pages(table, order)	\
	मुक्त_pages((अचिन्हित दीर्घ)(table), (order))

#पूर्ण_अगर /* _ASM_X86_AGP_H */
