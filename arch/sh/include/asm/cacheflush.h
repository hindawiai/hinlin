<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CACHEFLUSH_H
#घोषणा __ASM_SH_CACHEFLUSH_H

#समावेश <linux/mm.h>

/*
 * Cache flushing:
 *
 *  - flush_cache_all() flushes entire cache
 *  - flush_cache_mm(mm) flushes the specअगरied mm context's cache lines
 *  - flush_cache_dup mm(mm) handles cache flushing when विभाजनing
 *  - flush_cache_page(mm, vmaddr, pfn) flushes a single page
 *  - flush_cache_range(vma, start, end) flushes a range of pages
 *
 *  - flush_dcache_page(pg) flushes(wback&invalidates) a page क्रम dcache
 *  - flush_icache_range(start, end) flushes(invalidates) a range क्रम icache
 *  - flush_icache_page(vma, pg) flushes(invalidates) a page क्रम icache
 *  - flush_cache_sigtramp(vaddr) flushes the संकेत trampoline
 */
बाह्य व्योम (*local_flush_cache_all)(व्योम *args);
बाह्य व्योम (*local_flush_cache_mm)(व्योम *args);
बाह्य व्योम (*local_flush_cache_dup_mm)(व्योम *args);
बाह्य व्योम (*local_flush_cache_page)(व्योम *args);
बाह्य व्योम (*local_flush_cache_range)(व्योम *args);
बाह्य व्योम (*local_flush_dcache_page)(व्योम *args);
बाह्य व्योम (*local_flush_icache_range)(व्योम *args);
बाह्य व्योम (*local_flush_icache_page)(व्योम *args);
बाह्य व्योम (*local_flush_cache_sigtramp)(व्योम *args);

अटल अंतरभूत व्योम cache_noop(व्योम *args) अणु पूर्ण

बाह्य व्योम (*__flush_wback_region)(व्योम *start, पूर्णांक size);
बाह्य व्योम (*__flush_purge_region)(व्योम *start, पूर्णांक size);
बाह्य व्योम (*__flush_invalidate_region)(व्योम *start, पूर्णांक size);

बाह्य व्योम flush_cache_all(व्योम);
बाह्य व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_cache_dup_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn);
बाह्य व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
बाह्य व्योम flush_dcache_page(काष्ठा page *page);
बाह्य व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#घोषणा flush_icache_user_range flush_icache_range
बाह्य व्योम flush_icache_page(काष्ठा vm_area_काष्ठा *vma,
				 काष्ठा page *page);
बाह्य व्योम flush_cache_sigtramp(अचिन्हित दीर्घ address);

काष्ठा flusher_data अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ addr1, addr2;
पूर्ण;

#घोषणा ARCH_HAS_FLUSH_ANON_PAGE
बाह्य व्योम __flush_anon_page(काष्ठा page *page, अचिन्हित दीर्घ);

अटल अंतरभूत व्योम flush_anon_page(काष्ठा vm_area_काष्ठा *vma,
				   काष्ठा page *page, अचिन्हित दीर्घ vmaddr)
अणु
	अगर (boot_cpu_data.dcache.n_aliases && PageAnon(page))
		__flush_anon_page(page, vmaddr);
पूर्ण
अटल अंतरभूत व्योम flush_kernel_vmap_range(व्योम *addr, पूर्णांक size)
अणु
	__flush_wback_region(addr, size);
पूर्ण
अटल अंतरभूत व्योम invalidate_kernel_vmap_range(व्योम *addr, पूर्णांक size)
अणु
	__flush_invalidate_region(addr, size);
पूर्ण

#घोषणा ARCH_HAS_FLUSH_KERNEL_DCACHE_PAGE
अटल अंतरभूत व्योम flush_kernel_dcache_page(काष्ठा page *page)
अणु
	flush_dcache_page(page);
पूर्ण

बाह्य व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma,
	काष्ठा page *page, अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
	अचिन्हित दीर्घ len);

बाह्य व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma,
	काष्ठा page *page, अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
	अचिन्हित दीर्घ len);

#घोषणा flush_cache_vmap(start, end)		local_flush_cache_all(शून्य)
#घोषणा flush_cache_vunmap(start, end)		local_flush_cache_all(शून्य)

#घोषणा flush_dcache_mmap_lock(mapping)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_dcache_mmap_unlock(mapping)	करो अणु पूर्ण जबतक (0)

व्योम kmap_coherent_init(व्योम);
व्योम *kmap_coherent(काष्ठा page *page, अचिन्हित दीर्घ addr);
व्योम kunmap_coherent(व्योम *kvaddr);

#घोषणा PG_dcache_clean	PG_arch_1

व्योम cpu_cache_init(व्योम);

अटल अंतरभूत व्योम *sh_cacheop_vaddr(व्योम *vaddr)
अणु
	अगर (__in_29bit_mode())
		vaddr = (व्योम *)CAC_ADDR((अचिन्हित दीर्घ)vaddr);
	वापस vaddr;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_CACHEFLUSH_H */
