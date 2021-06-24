<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_PAGE_NO_H
#घोषणा _M68K_PAGE_NO_H

#अगर_अघोषित __ASSEMBLY__
 
बाह्य अचिन्हित दीर्घ memory_start;
बाह्य अचिन्हित दीर्घ memory_end;

#घोषणा clear_page(page)	स_रखो((page), 0, PAGE_SIZE)
#घोषणा copy_page(to,from)	स_नकल((to), (from), PAGE_SIZE)

#घोषणा clear_user_page(page, vaddr, pg)	clear_page(page)
#घोषणा copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

#घोषणा __alloc_zeroed_user_highpage(movableflags, vma, vaddr) \
	alloc_page_vma(GFP_HIGHUSER | __GFP_ZERO | movableflags, vma, vaddr)
#घोषणा __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE

#घोषणा __pa(vaddr)		((अचिन्हित दीर्घ)(vaddr))
#घोषणा __va(paddr)		((व्योम *)((अचिन्हित दीर्घ)(paddr)))

#घोषणा virt_to_pfn(kaddr)	(__pa(kaddr) >> PAGE_SHIFT)
#घोषणा pfn_to_virt(pfn)	__va((pfn) << PAGE_SHIFT)

#घोषणा virt_to_page(addr)	(mem_map + (((अचिन्हित दीर्घ)(addr)-PAGE_OFFSET) >> PAGE_SHIFT))
#घोषणा page_to_virt(page)	__va(((((page) - mem_map) << PAGE_SHIFT) + PAGE_OFFSET))

#घोषणा pfn_to_page(pfn)	virt_to_page(pfn_to_virt(pfn))
#घोषणा page_to_pfn(page)	virt_to_pfn(page_to_virt(page))
#घोषणा pfn_valid(pfn)	        ((pfn) < max_mapnr)

#घोषणा	virt_addr_valid(kaddr)	(((अचिन्हित दीर्घ)(kaddr) >= PAGE_OFFSET) && \
				((अचिन्हित दीर्घ)(kaddr) < memory_end))

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _M68K_PAGE_NO_H */
