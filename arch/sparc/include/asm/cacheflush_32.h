<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_CACHEFLUSH_H
#घोषणा _SPARC_CACHEFLUSH_H

#समावेश <यंत्र/cachetlb_32.h>

#घोषणा flush_cache_all() \
	sparc32_cachetlb_ops->cache_all()
#घोषणा flush_cache_mm(mm) \
	sparc32_cachetlb_ops->cache_mm(mm)
#घोषणा flush_cache_dup_mm(mm) \
	sparc32_cachetlb_ops->cache_mm(mm)
#घोषणा flush_cache_range(vma,start,end) \
	sparc32_cachetlb_ops->cache_range(vma, start, end)
#घोषणा flush_cache_page(vma,addr,pfn) \
	sparc32_cachetlb_ops->cache_page(vma, addr)
#घोषणा flush_icache_range(start, end)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_icache_page(vma, pg)		करो अणु पूर्ण जबतक (0)

#घोषणा copy_to_user_page(vma, page, vaddr, dst, src, len) \
	करो अणु							\
		flush_cache_page(vma, vaddr, page_to_pfn(page));\
		स_नकल(dst, src, len);				\
	पूर्ण जबतक (0)
#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len) \
	करो अणु							\
		flush_cache_page(vma, vaddr, page_to_pfn(page));\
		स_नकल(dst, src, len);				\
	पूर्ण जबतक (0)

#घोषणा __flush_page_to_ram(addr) \
	sparc32_cachetlb_ops->page_to_ram(addr)
#घोषणा flush_sig_insns(mm,insn_addr) \
	sparc32_cachetlb_ops->sig_insns(mm, insn_addr)
#घोषणा flush_page_क्रम_dma(addr) \
	sparc32_cachetlb_ops->page_क्रम_dma(addr)

व्योम sparc_flush_page_to_ram(काष्ठा page *page);

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
#घोषणा flush_dcache_page(page)			sparc_flush_page_to_ram(page)
#घोषणा flush_dcache_mmap_lock(mapping)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_dcache_mmap_unlock(mapping)	करो अणु पूर्ण जबतक (0)

#घोषणा flush_cache_vmap(start, end)		flush_cache_all()
#घोषणा flush_cache_vunmap(start, end)		flush_cache_all()

/* When a context चयन happens we must flush all user winकरोws so that
 * the winकरोws of the current process are flushed onto its stack. This
 * way the winकरोws are all clean क्रम the next process and the stack
 * frames are up to date.
 */
व्योम flush_user_winकरोws(व्योम);
व्योम समाप्त_user_winकरोws(व्योम);
व्योम flushw_all(व्योम);

#पूर्ण_अगर /* _SPARC_CACHEFLUSH_H */
