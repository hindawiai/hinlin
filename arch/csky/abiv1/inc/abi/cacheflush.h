<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ABI_CSKY_CACHEFLUSH_H
#घोषणा __ABI_CSKY_CACHEFLUSH_H

#समावेश <linux/mm.h>
#समावेश <यंत्र/माला.स>
#समावेश <यंत्र/cache.h>

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
बाह्य व्योम flush_dcache_page(काष्ठा page *);

#घोषणा flush_cache_mm(mm)			dcache_wbinv_all()
#घोषणा flush_cache_page(vma, page, pfn)	cache_wbinv_all()
#घोषणा flush_cache_dup_mm(mm)			cache_wbinv_all()

#घोषणा ARCH_HAS_FLUSH_KERNEL_DCACHE_PAGE
बाह्य व्योम flush_kernel_dcache_page(काष्ठा page *);

#घोषणा flush_dcache_mmap_lock(mapping)		xa_lock_irq(&mapping->i_pages)
#घोषणा flush_dcache_mmap_unlock(mapping)	xa_unlock_irq(&mapping->i_pages)

अटल अंतरभूत व्योम flush_kernel_vmap_range(व्योम *addr, पूर्णांक size)
अणु
	dcache_wbinv_all();
पूर्ण
अटल अंतरभूत व्योम invalidate_kernel_vmap_range(व्योम *addr, पूर्णांक size)
अणु
	dcache_wbinv_all();
पूर्ण

#घोषणा ARCH_HAS_FLUSH_ANON_PAGE
अटल अंतरभूत व्योम flush_anon_page(काष्ठा vm_area_काष्ठा *vma,
			 काष्ठा page *page, अचिन्हित दीर्घ vmaddr)
अणु
	अगर (PageAnon(page))
		cache_wbinv_all();
पूर्ण

/*
 * अगर (current_mm != vma->mm) cache_wbinv_range(start, end) will be broken.
 * Use cache_wbinv_all() here and need to be improved in future.
 */
बाह्य व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#घोषणा flush_cache_vmap(start, end)		cache_wbinv_all()
#घोषणा flush_cache_vunmap(start, end)		cache_wbinv_all()

#घोषणा flush_icache_page(vma, page)		करो अणुपूर्ण जबतक (0);
#घोषणा flush_icache_range(start, end)		cache_wbinv_range(start, end)
#घोषणा flush_icache_mm_range(mm, start, end)	cache_wbinv_range(start, end)
#घोषणा flush_icache_deferred(mm)		करो अणुपूर्ण जबतक (0);

#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len) \
करो अणु \
	स_नकल(dst, src, len); \
पूर्ण जबतक (0)

#घोषणा copy_to_user_page(vma, page, vaddr, dst, src, len) \
करो अणु \
	स_नकल(dst, src, len); \
	cache_wbinv_all(); \
पूर्ण जबतक (0)

#पूर्ण_अगर /* __ABI_CSKY_CACHEFLUSH_H */
