<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_CACHEFLUSH_H
#घोषणा _SPARC64_CACHEFLUSH_H

#समावेश <यंत्र/page.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/mm.h>

/* Cache flush operations. */
#घोषणा flushw_all()	__यंत्र__ __अस्थिर__("flushw")

व्योम __flushw_user(व्योम);
#घोषणा flushw_user() __flushw_user()

#घोषणा flush_user_winकरोws flushw_user
#घोषणा flush_रेजिस्टर_winकरोws flushw_all

/* These are the same regardless of whether this is an SMP kernel or not. */
#घोषणा flush_cache_mm(__mm) \
	करो अणु अगर ((__mm) == current->mm) flushw_user(); पूर्ण जबतक(0)
#घोषणा flush_cache_dup_mm(mm) flush_cache_mm(mm)
#घोषणा flush_cache_range(vma, start, end) \
	flush_cache_mm((vma)->vm_mm)
#घोषणा flush_cache_page(vma, page, pfn) \
	flush_cache_mm((vma)->vm_mm)

/*
 * On spitfire, the icache करोesn't snoop local stores and we don't
 * use block commit stores (which invalidate icache lines) during
 * module load, so we need this.
 */
व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम __flush_icache_page(अचिन्हित दीर्घ);

व्योम __flush_dcache_page(व्योम *addr, पूर्णांक flush_icache);
व्योम flush_dcache_page_impl(काष्ठा page *page);
#अगर_घोषित CONFIG_SMP
व्योम smp_flush_dcache_page_impl(काष्ठा page *page, पूर्णांक cpu);
व्योम flush_dcache_page_all(काष्ठा mm_काष्ठा *mm, काष्ठा page *page);
#अन्यथा
#घोषणा smp_flush_dcache_page_impl(page,cpu) flush_dcache_page_impl(page)
#घोषणा flush_dcache_page_all(mm,page) flush_dcache_page_impl(page)
#पूर्ण_अगर

व्योम __flush_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
व्योम flush_dcache_page(काष्ठा page *page);

#घोषणा flush_icache_page(vma, pg)	करो अणु पूर्ण जबतक(0)

व्योम flush_ptrace_access(काष्ठा vm_area_काष्ठा *, काष्ठा page *,
			 अचिन्हित दीर्घ uaddr, व्योम *kaddr,
			 अचिन्हित दीर्घ len, पूर्णांक ग_लिखो);

#घोषणा copy_to_user_page(vma, page, vaddr, dst, src, len)		\
	करो अणु								\
		flush_cache_page(vma, vaddr, page_to_pfn(page));	\
		स_नकल(dst, src, len);					\
		flush_ptrace_access(vma, page, vaddr, src, len, 0);	\
	पूर्ण जबतक (0)

#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len) 		\
	करो अणु								\
		flush_cache_page(vma, vaddr, page_to_pfn(page));	\
		स_नकल(dst, src, len);					\
		flush_ptrace_access(vma, page, vaddr, dst, len, 1);	\
	पूर्ण जबतक (0)

#घोषणा flush_dcache_mmap_lock(mapping)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_dcache_mmap_unlock(mapping)	करो अणु पूर्ण जबतक (0)

#घोषणा flush_cache_vmap(start, end)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_cache_vunmap(start, end)		करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _SPARC64_CACHEFLUSH_H */
