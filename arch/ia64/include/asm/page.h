<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_PAGE_H
#घोषणा _ASM_IA64_PAGE_H
/*
 * Pagetable related stuff.
 *
 * Copyright (C) 1998, 1999, 2002 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/types.h>

/*
 * The top three bits of an IA64 address are its Region Number.
 * Dअगरferent regions are asचिन्हित to dअगरferent purposes.
 */
#घोषणा RGN_SHIFT	(61)
#घोषणा RGN_BASE(r)	(__IA64_UL_CONST(r)<<RGN_SHIFT)
#घोषणा RGN_BITS	(RGN_BASE(-1))

#घोषणा RGN_KERNEL	7	/* Identity mapped region */
#घोषणा RGN_UNCACHED    6	/* Identity mapped I/O region */
#घोषणा RGN_GATE	5	/* Gate page, Kernel text, etc */
#घोषणा RGN_HPAGE	4	/* For Huge TLB pages */

/*
 * PAGE_SHIFT determines the actual kernel page size.
 */
#अगर defined(CONFIG_IA64_PAGE_SIZE_4KB)
# define PAGE_SHIFT	12
#या_अगर defined(CONFIG_IA64_PAGE_SIZE_8KB)
# define PAGE_SHIFT	13
#या_अगर defined(CONFIG_IA64_PAGE_SIZE_16KB)
# define PAGE_SHIFT	14
#या_अगर defined(CONFIG_IA64_PAGE_SIZE_64KB)
# define PAGE_SHIFT	16
#अन्यथा
# error Unsupported page size!
#पूर्ण_अगर

#घोषणा PAGE_SIZE		(__IA64_UL_CONST(1) << PAGE_SHIFT)
#घोषणा PAGE_MASK		(~(PAGE_SIZE - 1))

#घोषणा PERCPU_PAGE_SHIFT	18	/* log2() of max. size of per-CPU area */
#घोषणा PERCPU_PAGE_SIZE	(__IA64_UL_CONST(1) << PERCPU_PAGE_SHIFT)


#अगर_घोषित CONFIG_HUGETLB_PAGE
# define HPAGE_REGION_BASE	RGN_BASE(RGN_HPAGE)
# define HPAGE_SHIFT		hpage_shअगरt
# define HPAGE_SHIFT_DEFAULT	28	/* check ia64 SDM क्रम architecture supported size */
# define HPAGE_SIZE		(__IA64_UL_CONST(1) << HPAGE_SHIFT)
# define HPAGE_MASK		(~(HPAGE_SIZE - 1))

# define HAVE_ARCH_HUGETLB_UNMAPPED_AREA
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

#अगर_घोषित __ASSEMBLY__
# define __pa(x)		((x) - PAGE_OFFSET)
# define __va(x)		((x) + PAGE_OFFSET)
#अन्यथा /* !__ASSEMBLY */
#  define STRICT_MM_TYPECHECKS

बाह्य व्योम clear_page (व्योम *page);
बाह्य व्योम copy_page (व्योम *to, व्योम *from);

/*
 * clear_user_page() and copy_user_page() can't be अंतरभूत functions because
 * flush_dcache_page() can't be defined until later...
 */
#घोषणा clear_user_page(addr, vaddr, page)	\
करो अणु						\
	clear_page(addr);			\
	flush_dcache_page(page);		\
पूर्ण जबतक (0)

#घोषणा copy_user_page(to, from, vaddr, page)	\
करो अणु						\
	copy_page((to), (from));		\
	flush_dcache_page(page);		\
पूर्ण जबतक (0)


#घोषणा __alloc_zeroed_user_highpage(movableflags, vma, vaddr)		\
(अणु									\
	काष्ठा page *page = alloc_page_vma(				\
		GFP_HIGHUSER | __GFP_ZERO | movableflags, vma, vaddr);	\
	अगर (page)							\
 		flush_dcache_page(page);				\
	page;								\
पूर्ण)

#घोषणा __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE

#घोषणा virt_addr_valid(kaddr)	pfn_valid(__pa(kaddr) >> PAGE_SHIFT)

#समावेश <यंत्र-generic/memory_model.h>

#अगर_घोषित CONFIG_FLATMEM
# define pfn_valid(pfn)		((pfn) < max_mapnr)
#पूर्ण_अगर

#घोषणा page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)
#घोषणा virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)
#घोषणा pfn_to_kaddr(pfn)	__va((pfn) << PAGE_SHIFT)

प्रकार जोड़ ia64_va अणु
	काष्ठा अणु
		अचिन्हित दीर्घ off : 61;		/* पूर्णांकra-region offset */
		अचिन्हित दीर्घ reg :  3;		/* region number */
	पूर्ण f;
	अचिन्हित दीर्घ l;
	व्योम *p;
पूर्ण ia64_va;

/*
 * Note: These macros depend on the fact that PAGE_OFFSET has all
 * region bits set to 1 and all other bits set to zero.  They are
 * expressed in this way to ensure they result in a single "dep"
 * inकाष्ठाion.
 */
#घोषणा __pa(x)		(अणुia64_va _v; _v.l = (दीर्घ) (x); _v.f.reg = 0; _v.l;पूर्ण)
#घोषणा __va(x)		(अणुia64_va _v; _v.l = (दीर्घ) (x); _v.f.reg = -1; _v.p;पूर्ण)

#घोषणा REGION_NUMBER(x)	(अणुia64_va _v; _v.l = (दीर्घ) (x); _v.f.reg;पूर्ण)
#घोषणा REGION_OFFSET(x)	(अणुia64_va _v; _v.l = (दीर्घ) (x); _v.f.off;पूर्ण)

#अगर_घोषित CONFIG_HUGETLB_PAGE
# define htlbpage_to_page(x)	(((अचिन्हित दीर्घ) REGION_NUMBER(x) << 61)			\
				 | (REGION_OFFSET(x) >> (HPAGE_SHIFT-PAGE_SHIFT)))
# define HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)
बाह्य अचिन्हित पूर्णांक hpage_shअगरt;
#पूर्ण_अगर

अटल __अंतरभूत__ पूर्णांक
get_order (अचिन्हित दीर्घ size)
अणु
	दीर्घ द्विगुन d = size - 1;
	दीर्घ order;

	order = ia64_getf_exp(d);
	order = order - PAGE_SHIFT - 0xffff + 1;
	अगर (order < 0)
		order = 0;
	वापस order;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#अगर_घोषित STRICT_MM_TYPECHECKS
  /*
   * These are used to make use of C type-checking..
   */
  प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
  प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
#अगर CONFIG_PGTABLE_LEVELS == 4
  प्रकार काष्ठा अणु अचिन्हित दीर्घ pud; पूर्ण pud_t;
#पूर्ण_अगर
  प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
  प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;
  प्रकार काष्ठा page *pgtable_t;

# define pte_val(x)	((x).pte)
# define pmd_val(x)	((x).pmd)
#अगर CONFIG_PGTABLE_LEVELS == 4
# define pud_val(x)	((x).pud)
#पूर्ण_अगर
# define pgd_val(x)	((x).pgd)
# define pgprot_val(x)	((x).pgprot)

# define __pte(x)	((pte_t) अणु (x) पूर्ण )
# define __pmd(x)	((pmd_t) अणु (x) पूर्ण )
# define __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

#अन्यथा /* !STRICT_MM_TYPECHECKS */
  /*
   * .. जबतक these make it easier on the compiler
   */
# अगरndef __ASSEMBLY__
    प्रकार अचिन्हित दीर्घ pte_t;
    प्रकार अचिन्हित दीर्घ pmd_t;
    प्रकार अचिन्हित दीर्घ pgd_t;
    प्रकार अचिन्हित दीर्घ pgprot_t;
    प्रकार काष्ठा page *pgtable_t;
# endअगर

# define pte_val(x)	(x)
# define pmd_val(x)	(x)
# define pgd_val(x)	(x)
# define pgprot_val(x)	(x)

# define __pte(x)	(x)
# define __pgd(x)	(x)
# define __pgprot(x)	(x)
#पूर्ण_अगर /* !STRICT_MM_TYPECHECKS */

#घोषणा PAGE_OFFSET			RGN_BASE(RGN_KERNEL)

#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_TSK_EXEC

#घोषणा GATE_ADDR		RGN_BASE(RGN_GATE)

/*
 * 0xa000000000000000+2*PERCPU_PAGE_SIZE
 * - 0xa000000000000000+3*PERCPU_PAGE_SIZE reमुख्य unmapped (guard page)
 */
#घोषणा KERNEL_START		 (GATE_ADDR+__IA64_UL_CONST(0x100000000))
#घोषणा PERCPU_ADDR		(-PERCPU_PAGE_SIZE)
#घोषणा LOAD_OFFSET		(KERNEL_START - KERNEL_TR_PAGE_SIZE)

#घोषणा __HAVE_ARCH_GATE_AREA	1

#पूर्ण_अगर /* _ASM_IA64_PAGE_H */
