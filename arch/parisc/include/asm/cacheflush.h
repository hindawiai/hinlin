<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_CACHEFLUSH_H
#घोषणा _PARISC_CACHEFLUSH_H

#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/tlbflush.h>

/* The usual comment is "Caches aren't brain-dead on the <architecture>".
 * Unक्रमtunately, that करोesn't apply to PA-RISC. */

/* Internal implementation */
व्योम flush_data_cache_local(व्योम *);  /* flushes local data-cache only */
व्योम flush_inकाष्ठाion_cache_local(व्योम *); /* flushes local code-cache only */
#अगर_घोषित CONFIG_SMP
व्योम flush_data_cache(व्योम); /* flushes data-cache only (all processors) */
व्योम flush_inकाष्ठाion_cache(व्योम); /* flushes i-cache only (all processors) */
#अन्यथा
#घोषणा flush_data_cache() flush_data_cache_local(शून्य)
#घोषणा flush_inकाष्ठाion_cache() flush_inकाष्ठाion_cache_local(शून्य)
#पूर्ण_अगर

#घोषणा flush_cache_dup_mm(mm) flush_cache_mm(mm)

व्योम flush_user_icache_range_यंत्र(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
व्योम flush_kernel_icache_range_यंत्र(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
व्योम flush_user_dcache_range_यंत्र(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
व्योम flush_kernel_dcache_range_यंत्र(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
व्योम purge_kernel_dcache_range_यंत्र(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
व्योम flush_kernel_dcache_page_यंत्र(व्योम *);
व्योम flush_kernel_icache_page(व्योम *);

/* Cache flush operations */

व्योम flush_cache_all_local(व्योम);
व्योम flush_cache_all(व्योम);
व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm);

#घोषणा ARCH_HAS_FLUSH_KERNEL_DCACHE_PAGE
व्योम flush_kernel_dcache_page_addr(व्योम *addr);
अटल अंतरभूत व्योम flush_kernel_dcache_page(काष्ठा page *page)
अणु
	flush_kernel_dcache_page_addr(page_address(page));
पूर्ण

#घोषणा flush_kernel_dcache_range(start,size) \
	flush_kernel_dcache_range_यंत्र((start), (start)+(size));

व्योम flush_kernel_vmap_range(व्योम *vaddr, पूर्णांक size);
व्योम invalidate_kernel_vmap_range(व्योम *vaddr, पूर्णांक size);

#घोषणा flush_cache_vmap(start, end)		flush_cache_all()
#घोषणा flush_cache_vunmap(start, end)		flush_cache_all()

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
बाह्य व्योम flush_dcache_page(काष्ठा page *page);

#घोषणा flush_dcache_mmap_lock(mapping)		xa_lock_irq(&mapping->i_pages)
#घोषणा flush_dcache_mmap_unlock(mapping)	xa_unlock_irq(&mapping->i_pages)

#घोषणा flush_icache_page(vma,page)	करो अणु 		\
	flush_kernel_dcache_page(page);			\
	flush_kernel_icache_page(page_address(page)); 	\
पूर्ण जबतक (0)

#घोषणा flush_icache_range(s,e)		करो अणु 		\
	flush_kernel_dcache_range_यंत्र(s,e); 		\
	flush_kernel_icache_range_यंत्र(s,e); 		\
पूर्ण जबतक (0)

#घोषणा copy_to_user_page(vma, page, vaddr, dst, src, len) \
करो अणु \
	flush_cache_page(vma, vaddr, page_to_pfn(page)); \
	स_नकल(dst, src, len); \
	flush_kernel_dcache_range_यंत्र((अचिन्हित दीर्घ)dst, (अचिन्हित दीर्घ)dst + len); \
पूर्ण जबतक (0)

#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len) \
करो अणु \
	flush_cache_page(vma, vaddr, page_to_pfn(page)); \
	स_नकल(dst, src, len); \
पूर्ण जबतक (0)

व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr, अचिन्हित दीर्घ pfn);
व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

/* defined in pacache.S exported in cache.c used by flush_anon_page */
व्योम flush_dcache_page_यंत्र(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ vaddr);

#घोषणा ARCH_HAS_FLUSH_ANON_PAGE
अटल अंतरभूत व्योम
flush_anon_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page, अचिन्हित दीर्घ vmaddr)
अणु
	अगर (PageAnon(page)) अणु
		flush_tlb_page(vma, vmaddr);
		preempt_disable();
		flush_dcache_page_यंत्र(page_to_phys(page), vmaddr);
		preempt_enable();
	पूर्ण
पूर्ण

#घोषणा ARCH_HAS_FLUSH_ON_KUNMAP
अटल अंतरभूत व्योम kunmap_flush_on_unmap(व्योम *addr)
अणु
	flush_kernel_dcache_page_addr(addr);
पूर्ण

#पूर्ण_अगर /* _PARISC_CACHEFLUSH_H */

