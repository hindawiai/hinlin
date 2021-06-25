<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Cache flush operations क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_CACHEFLUSH_H
#घोषणा _ASM_CACHEFLUSH_H

#समावेश <linux/mm_types.h>

/* Cache flushing:
 *
 *  - flush_cache_all() flushes entire cache
 *  - flush_cache_mm(mm) flushes the specअगरied mm context's cache lines
 *  - flush_cache_page(mm, vmaddr, pfn) flushes a single page
 *  - flush_cache_range(vma, start, end) flushes a range of pages
 *  - flush_icache_range(start, end) flush a range of inकाष्ठाions
 *  - flush_dcache_page(pg) flushes(wback&invalidates) a page क्रम dcache
 *  - flush_icache_page(vma, pg) flushes(invalidates) a page क्रम icache
 *
 *  Need to द्विगुनcheck which one is really needed क्रम ptrace stuff to work.
 */
#घोषणा LINESIZE	32
#घोषणा LINEBITS	5

/*
 * Flush Dcache range through current map.
 */
बाह्य व्योम flush_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#घोषणा flush_dcache_range flush_dcache_range

/*
 * Flush Icache range through current map.
 */
बाह्य व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#घोषणा flush_icache_range flush_icache_range

/*
 * Memory-management related flushes are there to ensure in non-physically
 * indexed cache schemes that stale lines beदीर्घing to a given ASID aren't
 * in the cache to confuse things.  The prototype Hexagon Virtual Machine
 * only uses a single ASID क्रम all user-mode maps, which should
 * mean that they aren't necessary.  A brute-क्रमce, flush-everything
 * implementation, with the name xxxxx_hexagon() is present in
 * arch/hexagon/mm/cache.c, but let's not wire it up until we know
 * it is needed.
 */
बाह्य व्योम flush_cache_all_hexagon(व्योम);

/*
 * This may or may not ever have to be non-null, depending on the
 * भव machine MMU.  For a native kernel, it's definitiely  a no-op
 *
 * This is also the place where deferred cache coherency stuff seems
 * to happen, classically...  but instead we करो it like ia64 and
 * clean the cache when the PTE is set.
 *
 */
अटल अंतरभूत व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	/*  generic_ptrace_pokedata करोesn't wind up here, करोes it?  */
पूर्ण

व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		       अचिन्हित दीर्घ vaddr, व्योम *dst, व्योम *src, पूर्णांक len);
#घोषणा copy_to_user_page copy_to_user_page

#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len) \
	स_नकल(dst, src, len)

बाह्य व्योम hexagon_inv_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम hexagon_clean_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#समावेश <यंत्र-generic/cacheflush.h>

#पूर्ण_अगर
