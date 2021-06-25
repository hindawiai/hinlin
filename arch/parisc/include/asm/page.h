<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_PAGE_H
#घोषणा _PARISC_PAGE_H

#समावेश <linux/स्थिर.h>

#अगर defined(CONFIG_PARISC_PAGE_SIZE_4KB)
# define PAGE_SHIFT	12
#या_अगर defined(CONFIG_PARISC_PAGE_SIZE_16KB)
# define PAGE_SHIFT	14
#या_अगर defined(CONFIG_PARISC_PAGE_SIZE_64KB)
# define PAGE_SHIFT	16
#अन्यथा
# error "unknown default kernel page size"
#पूर्ण_अगर
#घोषणा PAGE_SIZE	(_AC(1,UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))


#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/cache.h>

#घोषणा clear_page(page)	clear_page_यंत्र((व्योम *)(page))
#घोषणा copy_page(to, from)	copy_page_यंत्र((व्योम *)(to), (व्योम *)(from))

काष्ठा page;

व्योम clear_page_यंत्र(व्योम *page);
व्योम copy_page_यंत्र(व्योम *to, व्योम *from);
#घोषणा clear_user_page(vto, vaddr, page) clear_page_यंत्र(vto)
व्योम copy_user_page(व्योम *vto, व्योम *vfrom, अचिन्हित दीर्घ vaddr,
			काष्ठा page *pg);

/*
 * These are used to make use of C type-checking..
 */
#घोषणा STRICT_MM_TYPECHECKS
#अगर_घोषित STRICT_MM_TYPECHECKS
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t; /* either 32 or 64bit */

/* NOTE: even on 64 bits, these entries are __u32 because we allocate
 * the pmd and pgd in ZONE_DMA (i.e. under 4GB) */
प्रकार काष्ठा अणु __u32 pgd; पूर्ण pgd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;

#अगर CONFIG_PGTABLE_LEVELS == 3
प्रकार काष्ठा अणु __u32 pmd; पूर्ण pmd_t;
#घोषणा __pmd(x)	((pmd_t) अणु (x) पूर्ण )
/* pXd_val() करो not work as lvalues, so make sure we करोn't use them as such. */
#घोषणा pmd_val(x)	((x).pmd + 0)
#पूर्ण_अगर

#घोषणा pte_val(x)	((x).pte)
#घोषणा pgd_val(x)	((x).pgd + 0)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

#अन्यथा
/*
 * .. जबतक these make it easier on the compiler
 */
प्रकार अचिन्हित दीर्घ pte_t;

#अगर CONFIG_PGTABLE_LEVELS == 3
प्रकार         __u32 pmd_t;
#घोषणा pmd_val(x)      (x)
#घोषणा __pmd(x)	(x)
#पूर्ण_अगर

प्रकार         __u32 pgd_t;
प्रकार अचिन्हित दीर्घ pgprot_t;

#घोषणा pte_val(x)      (x)
#घोषणा pgd_val(x)      (x)
#घोषणा pgprot_val(x)   (x)

#घोषणा __pte(x)        (x)
#घोषणा __pgd(x)        (x)
#घोषणा __pgprot(x)     (x)

#पूर्ण_अगर /* STRICT_MM_TYPECHECKS */

#घोषणा set_pmd(pmdptr, pmdval) (*(pmdptr) = (pmdval))
#अगर CONFIG_PGTABLE_LEVELS == 3
#घोषणा set_pud(pudptr, pudval) (*(pudptr) = (pudval))
#पूर्ण_अगर

प्रकार काष्ठा page *pgtable_t;

प्रकार काष्ठा __physmem_range अणु
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ pages;       /* PAGE_SIZE pages */
पूर्ण physmem_range_t;

बाह्य physmem_range_t pmem_ranges[];
बाह्य पूर्णांक npmem_ranges;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/* WARNING: The definitions below must match exactly to माप(pte_t)
 * etc
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा BITS_PER_PTE_ENTRY	3
#घोषणा BITS_PER_PMD_ENTRY	2
#घोषणा BITS_PER_PGD_ENTRY	2
#अन्यथा
#घोषणा BITS_PER_PTE_ENTRY	2
#घोषणा BITS_PER_PMD_ENTRY	2
#घोषणा BITS_PER_PGD_ENTRY	2
#पूर्ण_अगर
#घोषणा PGD_ENTRY_SIZE	(1UL << BITS_PER_PGD_ENTRY)
#घोषणा PMD_ENTRY_SIZE	(1UL << BITS_PER_PMD_ENTRY)
#घोषणा PTE_ENTRY_SIZE	(1UL << BITS_PER_PTE_ENTRY)

#घोषणा LINUX_GATEWAY_SPACE     0

/* This governs the relationship between भव and physical addresses.
 * If you alter it, make sure to take care of our various fixed mapping
 * segments in fixmap.h */
#अगर_घोषित CONFIG_64BIT
#घोषणा __PAGE_OFFSET_DEFAULT	(0x40000000)	/* 1GB */
#अन्यथा
#घोषणा __PAGE_OFFSET_DEFAULT	(0x10000000)	/* 256MB */
#पूर्ण_अगर

#अगर defined(BOOTLOADER)
#घोषणा __PAGE_OFFSET	(0)	/* bootloader uses physical addresses */
#अन्यथा
#घोषणा __PAGE_OFFSET	__PAGE_OFFSET_DEFAULT
#पूर्ण_अगर /* BOOTLOADER */

#घोषणा PAGE_OFFSET		((अचिन्हित दीर्घ)__PAGE_OFFSET)

/* The size of the gateway page (we leave lots of room क्रम expansion) */
#घोषणा GATEWAY_PAGE_SIZE	0x4000

/* The start of the actual kernel binary---used in vmlinux.lds.S
 * Leave some space after __PAGE_OFFSET क्रम detecting kernel null
 * ptr derefs */
#घोषणा KERNEL_BINARY_TEXT_START	(__PAGE_OFFSET + 0x100000)

/* These macros करोn't work for 64-bit C code -- don't allow in C at all */
#अगर_घोषित __ASSEMBLY__
#   define PA(x)	((x)-__PAGE_OFFSET)
#   define VA(x)	((x)+__PAGE_OFFSET)
#पूर्ण_अगर
#घोषणा __pa(x)			((अचिन्हित दीर्घ)(x)-PAGE_OFFSET)
#घोषणा __va(x)			((व्योम *)((अचिन्हित दीर्घ)(x)+PAGE_OFFSET))

#अगर_अघोषित CONFIG_SPARSEMEM
#घोषणा pfn_valid(pfn)		((pfn) < max_mapnr)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HUGETLB_PAGE
#घोषणा HPAGE_SHIFT		PMD_SHIFT /* fixed क्रम transparent huge pages */
#घोषणा HPAGE_SIZE      	((1UL) << HPAGE_SHIFT)
#घोषणा HPAGE_MASK		(~(HPAGE_SIZE - 1))
#घोषणा HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)

#अगर defined(CONFIG_64BIT) && defined(CONFIG_PARISC_PAGE_SIZE_4KB)
# define REAL_HPAGE_SHIFT	20 /* 20 = 1MB */
# define _HUGE_PAGE_SIZE_ENCODING_DEFAULT _PAGE_SIZE_ENCODING_1M
#या_अगर !defined(CONFIG_64BIT) && defined(CONFIG_PARISC_PAGE_SIZE_4KB)
# define REAL_HPAGE_SHIFT	22 /* 22 = 4MB */
# define _HUGE_PAGE_SIZE_ENCODING_DEFAULT _PAGE_SIZE_ENCODING_4M
#अन्यथा
# define REAL_HPAGE_SHIFT	24 /* 24 = 16MB */
# define _HUGE_PAGE_SIZE_ENCODING_DEFAULT _PAGE_SIZE_ENCODING_16M
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

#घोषणा virt_addr_valid(kaddr)	pfn_valid(__pa(kaddr) >> PAGE_SHIFT)

#घोषणा page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)
#घोषणा virt_to_page(kaddr)     pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>
#समावेश <यंत्र/pdc.h>

#घोषणा PAGE0   ((काष्ठा zeropage *)__PAGE_OFFSET)

/* DEFINITION OF THE ZERO-PAGE (PAG0) */
/* based on work by Jason Eckhardt (jason@equator.com) */

#पूर्ण_अगर /* _PARISC_PAGE_H */
