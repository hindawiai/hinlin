<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ABI_CSKY_CACHEFLUSH_H
#घोषणा __ABI_CSKY_CACHEFLUSH_H

/* Keep includes the same across arches.  */
#समावेश <linux/mm.h>

/*
 * The cache करोesn't need to be flushed when TLB entries change when
 * the cache is mapped to physical memory, not भव memory
 */
#घोषणा flush_cache_all()			करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_mm(mm)			करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_dup_mm(mm)			करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_range(vma, start, end)	करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_page(vma, vmaddr, pfn)	करो अणु पूर्ण जबतक (0)

#घोषणा PG_dcache_clean		PG_arch_1

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
अटल अंतरभूत व्योम flush_dcache_page(काष्ठा page *page)
अणु
	अगर (test_bit(PG_dcache_clean, &page->flags))
		clear_bit(PG_dcache_clean, &page->flags);
पूर्ण

#घोषणा flush_dcache_mmap_lock(mapping)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_dcache_mmap_unlock(mapping)	करो अणु पूर्ण जबतक (0)
#घोषणा flush_icache_page(vma, page)		करो अणु पूर्ण जबतक (0)

#घोषणा flush_icache_range(start, end)		cache_wbinv_range(start, end)

व्योम flush_icache_mm_range(काष्ठा mm_काष्ठा *mm,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम flush_icache_deferred(काष्ठा mm_काष्ठा *mm);

#घोषणा flush_cache_vmap(start, end)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_vunmap(start, end)		करो अणु पूर्ण जबतक (0)

#घोषणा copy_to_user_page(vma, page, vaddr, dst, src, len) \
करो अणु \
	स_नकल(dst, src, len); \
	अगर (vma->vm_flags & VM_EXEC) अणु \
		dcache_wb_range((अचिन्हित दीर्घ)dst, \
				(अचिन्हित दीर्घ)dst + len); \
		flush_icache_mm_range(current->mm, \
				(अचिन्हित दीर्घ)dst, \
				(अचिन्हित दीर्घ)dst + len); \
		पूर्ण \
पूर्ण जबतक (0)
#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len) \
	स_नकल(dst, src, len)

#पूर्ण_अगर /* __ABI_CSKY_CACHEFLUSH_H */
