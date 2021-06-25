<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) 2001 - 2013 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_CACHEFLUSH_H
#घोषणा _XTENSA_CACHEFLUSH_H

#समावेश <linux/mm.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/page.h>

/*
 * Lo-level routines क्रम cache flushing.
 *
 * invalidate data or inकाष्ठाion cache:
 *
 * __invalidate_icache_all()
 * __invalidate_icache_page(adr)
 * __invalidate_dcache_page(adr)
 * __invalidate_icache_range(from,size)
 * __invalidate_dcache_range(from,size)
 *
 * flush data cache:
 *
 * __flush_dcache_page(adr)
 *
 * flush and invalidate data cache:
 *
 * __flush_invalidate_dcache_all()
 * __flush_invalidate_dcache_page(adr)
 * __flush_invalidate_dcache_range(from,size)
 *
 * specials क्रम cache aliasing:
 *
 * __flush_invalidate_dcache_page_alias(vaddr,paddr)
 * __invalidate_dcache_page_alias(vaddr,paddr)
 * __invalidate_icache_page_alias(vaddr,paddr)
 */

बाह्य व्योम __invalidate_dcache_all(व्योम);
बाह्य व्योम __invalidate_icache_all(व्योम);
बाह्य व्योम __invalidate_dcache_page(अचिन्हित दीर्घ);
बाह्य व्योम __invalidate_icache_page(अचिन्हित दीर्घ);
बाह्य व्योम __invalidate_icache_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम __invalidate_dcache_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ);

#अगर XCHAL_DCACHE_IS_WRITEBACK
बाह्य व्योम __flush_invalidate_dcache_all(व्योम);
बाह्य व्योम __flush_dcache_page(अचिन्हित दीर्घ);
बाह्य व्योम __flush_dcache_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम __flush_invalidate_dcache_page(अचिन्हित दीर्घ);
बाह्य व्योम __flush_invalidate_dcache_range(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
#अन्यथा
अटल अंतरभूत व्योम __flush_dcache_page(अचिन्हित दीर्घ va)
अणु
पूर्ण
अटल अंतरभूत व्योम __flush_dcache_range(अचिन्हित दीर्घ va, अचिन्हित दीर्घ sz)
अणु
पूर्ण
# define __flush_invalidate_dcache_all()	__invalidate_dcache_all()
# define __flush_invalidate_dcache_page(p)	__invalidate_dcache_page(p)
# define __flush_invalidate_dcache_range(p,s)	__invalidate_dcache_range(p,s)
#पूर्ण_अगर

#अगर defined(CONFIG_MMU) && (DCACHE_WAY_SIZE > PAGE_SIZE)
बाह्य व्योम __flush_invalidate_dcache_page_alias(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम __invalidate_dcache_page_alias(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
#अन्यथा
अटल अंतरभूत व्योम __flush_invalidate_dcache_page_alias(अचिन्हित दीर्घ virt,
							अचिन्हित दीर्घ phys) अणु पूर्ण
अटल अंतरभूत व्योम __invalidate_dcache_page_alias(अचिन्हित दीर्घ virt,
						  अचिन्हित दीर्घ phys) अणु पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_MMU) && (ICACHE_WAY_SIZE > PAGE_SIZE)
बाह्य व्योम __invalidate_icache_page_alias(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
#अन्यथा
अटल अंतरभूत व्योम __invalidate_icache_page_alias(अचिन्हित दीर्घ virt,
						अचिन्हित दीर्घ phys) अणु पूर्ण
#पूर्ण_अगर

/*
 * We have physically tagged caches - nothing to करो here -
 * unless we have cache aliasing.
 *
 * Pages can get remapped. Because this might change the 'color' of that page,
 * we have to flush the cache beक्रमe the PTE is changed.
 * (see also Documentation/core-api/cachetlb.rst)
 */

#अगर defined(CONFIG_MMU) && \
	((DCACHE_WAY_SIZE > PAGE_SIZE) || defined(CONFIG_SMP))

#अगर_घोषित CONFIG_SMP
व्योम flush_cache_all(व्योम);
व्योम flush_cache_range(काष्ठा vm_area_काष्ठा*, uदीर्घ, uदीर्घ);
व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम flush_cache_page(काष्ठा vm_area_काष्ठा*,
			     अचिन्हित दीर्घ, अचिन्हित दीर्घ);
#अन्यथा
#घोषणा flush_cache_all local_flush_cache_all
#घोषणा flush_cache_range local_flush_cache_range
#घोषणा flush_icache_range local_flush_icache_range
#घोषणा flush_cache_page  local_flush_cache_page
#पूर्ण_अगर

#घोषणा local_flush_cache_all()						\
	करो अणु								\
		__flush_invalidate_dcache_all();			\
		__invalidate_icache_all();				\
	पूर्ण जबतक (0)

#घोषणा flush_cache_mm(mm)		flush_cache_all()
#घोषणा flush_cache_dup_mm(mm)		flush_cache_mm(mm)

#घोषणा flush_cache_vmap(start,end)	flush_cache_all()
#घोषणा flush_cache_vunmap(start,end)	flush_cache_all()

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
बाह्य व्योम flush_dcache_page(काष्ठा page*);

व्योम local_flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम local_flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, अचिन्हित दीर्घ pfn);

#अन्यथा

#घोषणा flush_cache_all()				करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_mm(mm)				करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_dup_mm(mm)				करो अणु पूर्ण जबतक (0)

#घोषणा flush_cache_vmap(start,end)			करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_vunmap(start,end)			करो अणु पूर्ण जबतक (0)

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 0
#घोषणा flush_dcache_page(page)				करो अणु पूर्ण जबतक (0)

#घोषणा flush_icache_range local_flush_icache_range
#घोषणा flush_cache_page(vma, addr, pfn)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_range(vma, start, end)		करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

#घोषणा flush_icache_user_range flush_icache_range

/* Ensure consistency between data and inकाष्ठाion cache. */
#घोषणा local_flush_icache_range(start, end)				\
	करो अणु								\
		__flush_dcache_range(start, (end) - (start));		\
		__invalidate_icache_range(start,(end) - (start));	\
	पूर्ण जबतक (0)

/* This is not required, see Documentation/core-api/cachetlb.rst */
#घोषणा	flush_icache_page(vma,page)			करो अणु पूर्ण जबतक (0)

#घोषणा flush_dcache_mmap_lock(mapping)			करो अणु पूर्ण जबतक (0)
#घोषणा flush_dcache_mmap_unlock(mapping)		करो अणु पूर्ण जबतक (0)

#अगर defined(CONFIG_MMU) && (DCACHE_WAY_SIZE > PAGE_SIZE)

बाह्य व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा*, काष्ठा page*,
		अचिन्हित दीर्घ, व्योम*, स्थिर व्योम*, अचिन्हित दीर्घ);
बाह्य व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा*, काष्ठा page*,
		अचिन्हित दीर्घ, व्योम*, स्थिर व्योम*, अचिन्हित दीर्घ);

#अन्यथा

#घोषणा copy_to_user_page(vma, page, vaddr, dst, src, len)		\
	करो अणु								\
		स_नकल(dst, src, len);					\
		__flush_dcache_range((अचिन्हित दीर्घ) dst, len);		\
		__invalidate_icache_range((अचिन्हित दीर्घ) dst, len);	\
	पूर्ण जबतक (0)

#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len) \
	स_नकल(dst, src, len)

#पूर्ण_अगर

#पूर्ण_अगर /* _XTENSA_CACHEFLUSH_H */
