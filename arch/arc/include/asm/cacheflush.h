<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 *  vineetg: May 2011: क्रम Non-aliasing VIPT D-cache following can be NOPs
 *   -flush_cache_dup_mm (विभाजन)
 *   -likewise क्रम flush_cache_mm (निकास/execve)
 *   -likewise क्रम flush_cache_अणुrange,pageपूर्ण (munmap, निकास, COW-अवरोध)
 *
 *  vineetg: April 2008
 *   -Added a critical CacheLine flush to copy_to_user_page( ) which
 *     was causing gdbserver to not setup अवरोधpoपूर्णांकs consistently
 */

#अगर_अघोषित _ASM_CACHEFLUSH_H
#घोषणा _ASM_CACHEFLUSH_H

#समावेश <linux/mm.h>
#समावेश <यंत्र/shmparam.h>

/*
 * Semantically we need this because icache करोesn't snoop dcache/dma.
 * However ARC Cache flush requires paddr as well as vaddr, latter not available
 * in the flush_icache_page() API. So we no-op it but करो the equivalent work
 * in update_mmu_cache()
 */
#घोषणा flush_icache_page(vma, page)

व्योम flush_cache_all(व्योम);

व्योम flush_icache_range(अचिन्हित दीर्घ kstart, अचिन्हित दीर्घ kend);
व्योम __sync_icache_dcache(phys_addr_t paddr, अचिन्हित दीर्घ vaddr, पूर्णांक len);
व्योम __inv_icache_page(phys_addr_t paddr, अचिन्हित दीर्घ vaddr);
व्योम __flush_dcache_page(phys_addr_t paddr, अचिन्हित दीर्घ vaddr);

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1

व्योम flush_dcache_page(काष्ठा page *page);

व्योम dma_cache_wback_inv(phys_addr_t start, अचिन्हित दीर्घ sz);
व्योम dma_cache_inv(phys_addr_t start, अचिन्हित दीर्घ sz);
व्योम dma_cache_wback(phys_addr_t start, अचिन्हित दीर्घ sz);

#घोषणा flush_dcache_mmap_lock(mapping)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_dcache_mmap_unlock(mapping)	करो अणु पूर्ण जबतक (0)

/* TBD: optimize this */
#घोषणा flush_cache_vmap(start, end)		flush_cache_all()
#घोषणा flush_cache_vunmap(start, end)		flush_cache_all()

#घोषणा flush_cache_dup_mm(mm)			/* called on विभाजन (VIVT only) */

#अगर_अघोषित CONFIG_ARC_CACHE_VIPT_ALIASING

#घोषणा flush_cache_mm(mm)			/* called on munmap/निकास */
#घोषणा flush_cache_range(mm, u_vstart, u_vend)
#घोषणा flush_cache_page(vma, u_vaddr, pfn)	/* PF handling/COW-अवरोध */

#अन्यथा	/* VIPT aliasing dcache */

/* To clear out stale userspace mappings */
व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm);
व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ start,अचिन्हित दीर्घ end);
व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ user_addr, अचिन्हित दीर्घ page);

/*
 * To make sure that userspace mapping is flushed to memory beक्रमe
 * get_user_pages() uses a kernel mapping to access the page
 */
#घोषणा ARCH_HAS_FLUSH_ANON_PAGE
व्योम flush_anon_page(काष्ठा vm_area_काष्ठा *vma,
	काष्ठा page *page, अचिन्हित दीर्घ u_vaddr);

#पूर्ण_अगर	/* CONFIG_ARC_CACHE_VIPT_ALIASING */

/*
 * A new pagecache page has PG_arch_1 clear - thus dcache dirty by शेष
 * This works around some PIO based drivers which करोn't call flush_dcache_page
 * to record that they dirtied the dcache
 */
#घोषणा PG_dc_clean	PG_arch_1

#घोषणा CACHE_COLORS_NUM	4
#घोषणा CACHE_COLORS_MSK	(CACHE_COLORS_NUM - 1)
#घोषणा CACHE_COLOR(addr)	(((अचिन्हित दीर्घ)(addr) >> (PAGE_SHIFT)) & CACHE_COLORS_MSK)

/*
 * Simple wrapper over config option
 * Bootup code ensures that hardware matches kernel configuration
 */
अटल अंतरभूत पूर्णांक cache_is_vipt_aliasing(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARC_CACHE_VIPT_ALIASING);
पूर्ण

/*
 * checks अगर two addresses (after page aligning) index पूर्णांकo same cache set
 */
#घोषणा addr_not_cache_congruent(addr1, addr2)				\
(अणु									\
	cache_is_vipt_aliasing() ? 					\
		(CACHE_COLOR(addr1) != CACHE_COLOR(addr2)) : 0;		\
पूर्ण)

#घोषणा copy_to_user_page(vma, page, vaddr, dst, src, len)		\
करो अणु									\
	स_नकल(dst, src, len);						\
	अगर (vma->vm_flags & VM_EXEC)					\
		__sync_icache_dcache((अचिन्हित दीर्घ)(dst), vaddr, len);	\
पूर्ण जबतक (0)

#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len)		\
	स_नकल(dst, src, len);						\

#पूर्ण_अगर
