<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 01, 02, 03 by Ralf Baechle
 * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_CACHEFLUSH_H
#घोषणा _ASM_CACHEFLUSH_H

/* Keep includes the same across arches.  */
#समावेश <linux/mm.h>
#समावेश <यंत्र/cpu-features.h>

/* Cache flushing:
 *
 *  - flush_cache_all() flushes entire cache
 *  - flush_cache_mm(mm) flushes the specअगरied mm context's cache lines
 *  - flush_cache_dup mm(mm) handles cache flushing when विभाजनing
 *  - flush_cache_page(mm, vmaddr, pfn) flushes a single page
 *  - flush_cache_range(vma, start, end) flushes a range of pages
 *  - flush_icache_range(start, end) flush a range of inकाष्ठाions
 *  - flush_dcache_page(pg) flushes(wback&invalidates) a page क्रम dcache
 *
 * MIPS specअगरic flush operations:
 *
 *  - flush_icache_all() flush the entire inकाष्ठाion cache
 *  - flush_data_cache_page() flushes a page from the data cache
 *  - __flush_icache_user_range(start, end) flushes range of user inकाष्ठाions
 */

 /*
 * This flag is used to indicate that the page poपूर्णांकed to by a pte
 * is dirty and requires cleaning beक्रमe वापसing it to the user.
 */
#घोषणा PG_dcache_dirty			PG_arch_1

#घोषणा Page_dcache_dirty(page)		\
	test_bit(PG_dcache_dirty, &(page)->flags)
#घोषणा SetPageDcacheDirty(page)	\
	set_bit(PG_dcache_dirty, &(page)->flags)
#घोषणा ClearPageDcacheDirty(page)	\
	clear_bit(PG_dcache_dirty, &(page)->flags)

बाह्य व्योम (*flush_cache_all)(व्योम);
बाह्य व्योम (*__flush_cache_all)(व्योम);
बाह्य व्योम (*flush_cache_mm)(काष्ठा mm_काष्ठा *mm);
#घोषणा flush_cache_dup_mm(mm)	करो अणु (व्योम) (mm); पूर्ण जबतक (0)
बाह्य व्योम (*flush_cache_range)(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम (*flush_cache_page)(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page, अचिन्हित दीर्घ pfn);
बाह्य व्योम __flush_dcache_page(काष्ठा page *page);

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
अटल अंतरभूत व्योम flush_dcache_page(काष्ठा page *page)
अणु
	अगर (cpu_has_dc_aliases)
		__flush_dcache_page(page);
	अन्यथा अगर (!cpu_has_ic_fills_f_dc)
		SetPageDcacheDirty(page);
पूर्ण

#घोषणा flush_dcache_mmap_lock(mapping)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_dcache_mmap_unlock(mapping)	करो अणु पूर्ण जबतक (0)

#घोषणा ARCH_HAS_FLUSH_ANON_PAGE
बाह्य व्योम __flush_anon_page(काष्ठा page *, अचिन्हित दीर्घ);
अटल अंतरभूत व्योम flush_anon_page(काष्ठा vm_area_काष्ठा *vma,
	काष्ठा page *page, अचिन्हित दीर्घ vmaddr)
अणु
	अगर (cpu_has_dc_aliases && PageAnon(page))
		__flush_anon_page(page, vmaddr);
पूर्ण

अटल अंतरभूत व्योम flush_icache_page(काष्ठा vm_area_काष्ठा *vma,
	काष्ठा page *page)
अणु
पूर्ण

बाह्य व्योम (*flush_icache_range)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम (*local_flush_icache_range)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम (*__flush_icache_user_range)(अचिन्हित दीर्घ start,
					 अचिन्हित दीर्घ end);
बाह्य व्योम (*__local_flush_icache_user_range)(अचिन्हित दीर्घ start,
					       अचिन्हित दीर्घ end);

बाह्य व्योम (*__flush_cache_vmap)(व्योम);

अटल अंतरभूत व्योम flush_cache_vmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (cpu_has_dc_aliases)
		__flush_cache_vmap();
पूर्ण

बाह्य व्योम (*__flush_cache_vunmap)(व्योम);

अटल अंतरभूत व्योम flush_cache_vunmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (cpu_has_dc_aliases)
		__flush_cache_vunmap();
पूर्ण

बाह्य व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma,
	काष्ठा page *page, अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
	अचिन्हित दीर्घ len);

बाह्य व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma,
	काष्ठा page *page, अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
	अचिन्हित दीर्घ len);

बाह्य व्योम (*flush_icache_all)(व्योम);
बाह्य व्योम (*local_flush_data_cache_page)(व्योम * addr);
बाह्य व्योम (*flush_data_cache_page)(अचिन्हित दीर्घ addr);

/* Run kernel code uncached, useful क्रम cache probing functions. */
अचिन्हित दीर्घ run_uncached(व्योम *func);

बाह्य व्योम *kmap_coherent(काष्ठा page *page, अचिन्हित दीर्घ addr);
बाह्य व्योम kunmap_coherent(व्योम);
बाह्य व्योम *kmap_noncoherent(काष्ठा page *page, अचिन्हित दीर्घ addr);

अटल अंतरभूत व्योम kunmap_noncoherent(व्योम)
अणु
	kunmap_coherent();
पूर्ण

#घोषणा ARCH_HAS_FLUSH_KERNEL_DCACHE_PAGE
अटल अंतरभूत व्योम flush_kernel_dcache_page(काष्ठा page *page)
अणु
	BUG_ON(cpu_has_dc_aliases && PageHighMem(page));
	flush_dcache_page(page);
पूर्ण

/*
 * For now flush_kernel_vmap_range and invalidate_kernel_vmap_range both करो a
 * cache ग_लिखोback and invalidate operation.
 */
बाह्य व्योम (*__flush_kernel_vmap_range)(अचिन्हित दीर्घ vaddr, पूर्णांक size);

अटल अंतरभूत व्योम flush_kernel_vmap_range(व्योम *vaddr, पूर्णांक size)
अणु
	अगर (cpu_has_dc_aliases)
		__flush_kernel_vmap_range((अचिन्हित दीर्घ) vaddr, size);
पूर्ण

अटल अंतरभूत व्योम invalidate_kernel_vmap_range(व्योम *vaddr, पूर्णांक size)
अणु
	अगर (cpu_has_dc_aliases)
		__flush_kernel_vmap_range((अचिन्हित दीर्घ) vaddr, size);
पूर्ण

#पूर्ण_अगर /* _ASM_CACHEFLUSH_H */
