<शैली गुरु>
/*
 * include/यंत्र-xtensa/page.h
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version2 as
 * published by the Free Software Foundation.
 *
 * Copyright (C) 2001 - 2007 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_PAGE_H
#घोषणा _XTENSA_PAGE_H

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/kmem_layout.h>

/*
 * PAGE_SHIFT determines the page size
 */

#घोषणा PAGE_SHIFT	12
#घोषणा PAGE_SIZE	(__XTENSA_UL_CONST(1) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))

#अगर_घोषित CONFIG_MMU
#घोषणा PAGE_OFFSET	XCHAL_KSEG_CACHED_VADDR
#घोषणा PHYS_OFFSET	XCHAL_KSEG_PADDR
#घोषणा MAX_LOW_PFN	(PHYS_PFN(XCHAL_KSEG_PADDR) + \
			 PHYS_PFN(XCHAL_KSEG_SIZE))
#अन्यथा
#घोषणा PAGE_OFFSET	_AC(CONFIG_DEFAULT_MEM_START, UL)
#घोषणा PHYS_OFFSET	_AC(CONFIG_DEFAULT_MEM_START, UL)
#घोषणा MAX_LOW_PFN	PHYS_PFN(0xfffffffful)
#पूर्ण_अगर

/*
 * Cache aliasing:
 *
 * If the cache size क्रम one way is greater than the page size, we have to
 * deal with cache aliasing. The cache index is wider than the page size:
 *
 * |    |cache| cache index
 * | pfn  |off|	भव address
 * |xxxx:X|zzz|
 * |    : |   |
 * | \  / |   |
 * |trans.|   |
 * | /  \ |   |
 * |yyyy:Y|zzz|	physical address
 *
 * When the page number is translated to the physical page address, the lowest
 * bit(s) (X) that are part of the cache index are also translated (Y).
 * If this translation changes bit(s) (X), the cache index is also afected,
 * thus resulting in a dअगरferent cache line than beक्रमe.
 * The kernel करोes not provide a mechanism to ensure that the page color
 * (represented by this bit) reमुख्यs the same when allocated or when pages
 * are remapped. When user pages are mapped पूर्णांकo kernel space, the color of
 * the page might also change.
 *
 * We use the address space VMALLOC_END ... VMALLOC_END + DCACHE_WAY_SIZE * 2
 * to temporarily map a patch so we can match the color.
 */

#अगर DCACHE_WAY_SIZE > PAGE_SIZE
# define DCACHE_ALIAS_ORDER	(DCACHE_WAY_SHIFT - PAGE_SHIFT)
# define DCACHE_ALIAS_MASK	(PAGE_MASK & (DCACHE_WAY_SIZE - 1))
# define DCACHE_ALIAS(a)	(((a) & DCACHE_ALIAS_MASK) >> PAGE_SHIFT)
# define DCACHE_ALIAS_EQ(a,b)	((((a) ^ (b)) & DCACHE_ALIAS_MASK) == 0)
#अन्यथा
# define DCACHE_ALIAS_ORDER	0
# define DCACHE_ALIAS(a)	((व्योम)(a), 0)
#पूर्ण_अगर
#घोषणा DCACHE_N_COLORS		(1 << DCACHE_ALIAS_ORDER)

#अगर ICACHE_WAY_SIZE > PAGE_SIZE
# define ICACHE_ALIAS_ORDER	(ICACHE_WAY_SHIFT - PAGE_SHIFT)
# define ICACHE_ALIAS_MASK	(PAGE_MASK & (ICACHE_WAY_SIZE - 1))
# define ICACHE_ALIAS(a)	(((a) & ICACHE_ALIAS_MASK) >> PAGE_SHIFT)
# define ICACHE_ALIAS_EQ(a,b)	((((a) ^ (b)) & ICACHE_ALIAS_MASK) == 0)
#अन्यथा
# define ICACHE_ALIAS_ORDER	0
#पूर्ण_अगर


#अगर_घोषित __ASSEMBLY__

#घोषणा __pgprot(x)	(x)

#अन्यथा

/*
 * These are used to make use of C type-checking..
 */

प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;		/* page table entry */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;		/* PGD table entry */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;
प्रकार काष्ठा page *pgtable_t;

#घोषणा pte_val(x)	((x).pte)
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

/*
 * Pure 2^n version of get_order
 * Use 'nsau' inकाष्ठाions अगर supported by the processor or the generic version.
 */

#अगर XCHAL_HAVE_NSA

अटल अंतरभूत __attribute_स्थिर__ पूर्णांक get_order(अचिन्हित दीर्घ size)
अणु
	पूर्णांक lz;
	यंत्र ("nsau %0, %1" : "=r" (lz) : "r" ((size - 1) >> PAGE_SHIFT));
	वापस 32 - lz;
पूर्ण

#अन्यथा

# include <यंत्र-generic/getorder.h>

#पूर्ण_अगर

काष्ठा page;
काष्ठा vm_area_काष्ठा;
बाह्य व्योम clear_page(व्योम *page);
बाह्य व्योम copy_page(व्योम *to, व्योम *from);

/*
 * If we have cache aliasing and ग_लिखोback caches, we might have to करो
 * some extra work
 */

#अगर defined(CONFIG_MMU) && DCACHE_WAY_SIZE > PAGE_SIZE
बाह्य व्योम clear_page_alias(व्योम *vaddr, अचिन्हित दीर्घ paddr);
बाह्य व्योम copy_page_alias(व्योम *to, व्योम *from,
			    अचिन्हित दीर्घ to_paddr, अचिन्हित दीर्घ from_paddr);

#घोषणा clear_user_highpage clear_user_highpage
व्योम clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr);
#घोषणा __HAVE_ARCH_COPY_USER_HIGHPAGE
व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma);
#अन्यथा
# define clear_user_page(page, vaddr, pg)	clear_page(page)
# define copy_user_page(to, from, vaddr, pg)	copy_page(to, from)
#पूर्ण_अगर

/*
 * This handles the memory map.  We handle pages at
 * XCHAL_KSEG_CACHED_VADDR क्रम kernels with 32 bit address space.
 * These macros are क्रम conversion of kernel address, not user
 * addresses.
 */

#घोषणा ARCH_PFN_OFFSET		(PHYS_OFFSET >> PAGE_SHIFT)

#अगर_घोषित CONFIG_MMU
अटल अंतरभूत अचिन्हित दीर्घ ___pa(अचिन्हित दीर्घ va)
अणु
	अचिन्हित दीर्घ off = va - PAGE_OFFSET;

	अगर (off >= XCHAL_KSEG_SIZE)
		off -= XCHAL_KSEG_SIZE;

#अगर_अघोषित CONFIG_XIP_KERNEL
	वापस off + PHYS_OFFSET;
#अन्यथा
	अगर (off < XCHAL_KSEG_SIZE)
		वापस off + PHYS_OFFSET;

	off -= XCHAL_KSEG_SIZE;
	अगर (off >= XCHAL_KIO_SIZE)
		off -= XCHAL_KIO_SIZE;

	वापस off + XCHAL_KIO_PADDR;
#पूर्ण_अगर
पूर्ण
#घोषणा __pa(x)	___pa((अचिन्हित दीर्घ)(x))
#अन्यथा
#घोषणा __pa(x)	\
	((अचिन्हित दीर्घ) (x) - PAGE_OFFSET + PHYS_OFFSET)
#पूर्ण_अगर
#घोषणा __va(x)	\
	((व्योम *)((अचिन्हित दीर्घ) (x) - PHYS_OFFSET + PAGE_OFFSET))
#घोषणा pfn_valid(pfn) \
	((pfn) >= ARCH_PFN_OFFSET && ((pfn) - ARCH_PFN_OFFSET) < max_mapnr)

#अगर_घोषित CONFIG_DISCONTIGMEM
# error CONFIG_DISCONTIGMEM not supported
#पूर्ण_अगर

#घोषणा virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)
#घोषणा page_to_virt(page)	__va(page_to_pfn(page) << PAGE_SHIFT)
#घोषणा virt_addr_valid(kaddr)	pfn_valid(__pa(kaddr) >> PAGE_SHIFT)
#घोषणा page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)

#पूर्ण_अगर /* __ASSEMBLY__ */

#समावेश <यंत्र-generic/memory_model.h>
#पूर्ण_अगर /* _XTENSA_PAGE_H */
