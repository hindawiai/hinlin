<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_PGTABLE_H
#घोषणा _M68K_PGTABLE_H


#अगर defined(CONFIG_SUN3) || defined(CONFIG_COLDFIRE)
#समावेश <यंत्र-generic/pgtable-nopmd.h>
#अन्यथा
#समावेश <यंत्र-generic/pgtable-nopud.h>
#पूर्ण_अगर

#समावेश <यंत्र/setup.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/processor.h>
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ोs.h>

/*
 * This file contains the functions and defines necessary to modअगरy and use
 * the m68k page table tree.
 */

#समावेश <यंत्र/virtconvert.h>

/* Certain architectures need to करो special things when pte's
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */
#घोषणा set_pte(pteptr, pteval)					\
	करोअणु							\
		*(pteptr) = (pteval);				\
	पूर्ण जबतक(0)
#घोषणा set_pte_at(mm,addr,ptep,pteval) set_pte(ptep,pteval)


/* PMD_SHIFT determines the size of the area a second-level page table can map */
#अगर CONFIG_PGTABLE_LEVELS == 3
#घोषणा PMD_SHIFT	18
#पूर्ण_अगर
#घोषणा PMD_SIZE	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))

/* PGसूची_SHIFT determines what a third-level page table entry can map */
#अगर_घोषित CONFIG_SUN3
#घोषणा PGसूची_SHIFT     17
#या_अगर defined(CONFIG_COLDFIRE)
#घोषणा PGसूची_SHIFT     22
#अन्यथा
#घोषणा PGसूची_SHIFT	25
#पूर्ण_अगर
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/*
 * entries per page directory level: the m68k is configured as three-level,
 * so we करो have PMD level physically.
 */
#अगर_घोषित CONFIG_SUN3
#घोषणा PTRS_PER_PTE   16
#घोषणा __PAGETABLE_PMD_FOLDED 1
#घोषणा PTRS_PER_PMD   1
#घोषणा PTRS_PER_PGD   2048
#या_अगर defined(CONFIG_COLDFIRE)
#घोषणा PTRS_PER_PTE	512
#घोषणा __PAGETABLE_PMD_FOLDED 1
#घोषणा PTRS_PER_PMD	1
#घोषणा PTRS_PER_PGD	1024
#अन्यथा
#घोषणा PTRS_PER_PTE	64
#घोषणा PTRS_PER_PMD	128
#घोषणा PTRS_PER_PGD	128
#पूर्ण_अगर
#घोषणा USER_PTRS_PER_PGD	(TASK_SIZE/PGसूची_SIZE)
#घोषणा FIRST_USER_ADDRESS	0UL

/* Virtual address region क्रम use by kernel_map() */
#अगर_घोषित CONFIG_SUN3
#घोषणा KMAP_START	0x0dc00000
#घोषणा KMAP_END	0x0e000000
#या_अगर defined(CONFIG_COLDFIRE)
#घोषणा KMAP_START	0xe0000000
#घोषणा KMAP_END	0xf0000000
#अन्यथा
#घोषणा	KMAP_START	0xd0000000
#घोषणा	KMAP_END	0xf0000000
#पूर्ण_अगर

#अगर_घोषित CONFIG_SUN3
बाह्य अचिन्हित दीर्घ m68k_vदो_स्मृति_end;
#घोषणा VMALLOC_START 0x0f800000
#घोषणा VMALLOC_END m68k_vदो_स्मृति_end
#या_अगर defined(CONFIG_COLDFIRE)
#घोषणा VMALLOC_START	0xd0000000
#घोषणा VMALLOC_END	0xe0000000
#अन्यथा
/* Just any arbitrary offset to the start of the vदो_स्मृति VM area: the
 * current 8MB value just means that there will be a 8MB "hole" after the
 * physical memory until the kernel भव memory starts.  That means that
 * any out-of-bounds memory accesses will hopefully be caught.
 * The vदो_स्मृति() routines leaves a hole of 4kB between each vदो_स्मृतिed
 * area क्रम the same reason. ;)
 */
#घोषणा VMALLOC_OFFSET	(8*1024*1024)
#घोषणा VMALLOC_START (((अचिन्हित दीर्घ) high_memory + VMALLOC_OFFSET) & ~(VMALLOC_OFFSET-1))
#घोषणा VMALLOC_END KMAP_START
#पूर्ण_अगर

/* zero page used क्रम uninitialized stuff */
बाह्य व्योम *empty_zero_page;

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
#घोषणा ZERO_PAGE(vaddr)	(virt_to_page(empty_zero_page))

/* number of bits that fit पूर्णांकo a memory poपूर्णांकer */
#घोषणा BITS_PER_PTR			(8*माप(अचिन्हित दीर्घ))

/* to align the poपूर्णांकer to a poपूर्णांकer address */
#घोषणा PTR_MASK			(~(माप(व्योम*)-1))

/* माप(व्योम*)==1<<SIZखातापूर्ण_PTR_LOG2 */
/* 64-bit machines, beware!  SRB. */
#घोषणा SIZखातापूर्ण_PTR_LOG2			       2

बाह्य व्योम kernel_set_cachemode(व्योम *addr, अचिन्हित दीर्घ size, पूर्णांक cmode);

/*
 * The m68k करोesn't have any बाह्यal MMU info: the kernel page
 * tables contain all the necessary inक्रमmation.  The Sun3 करोes, but
 * they are updated on demand.
 */
अटल अंतरभूत व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ address, pte_t *ptep)
अणु
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा kern_addr_valid(addr)	(1)

/* MMU-specअगरic headers */

#अगर_घोषित CONFIG_SUN3
#समावेश <यंत्र/sun3_pgtable.h>
#या_अगर defined(CONFIG_COLDFIRE)
#समावेश <यंत्र/mcf_pgtable.h>
#अन्यथा
#समावेश <यंत्र/motorola_pgtable.h>
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
/*
 * Macro to mark a page protection value as "uncacheable".
 */
#अगर_घोषित CONFIG_COLDFIRE
# define pgprot_noncached(prot) (__pgprot(pgprot_val(prot) | CF_PAGE_NOCACHE))
#अन्यथा
#अगर_घोषित SUN3_PAGE_NOCACHE
# define __SUN3_PAGE_NOCACHE	SUN3_PAGE_NOCACHE
#अन्यथा
# define __SUN3_PAGE_NOCACHE	0
#पूर्ण_अगर
#घोषणा pgprot_noncached(prot)							\
	(MMU_IS_SUN3								\
	 ? (__pgprot(pgprot_val(prot) | __SUN3_PAGE_NOCACHE))			\
	 : ((MMU_IS_851 || MMU_IS_030)						\
	    ? (__pgprot(pgprot_val(prot) | _PAGE_NOCACHE030))			\
	    : (MMU_IS_040 || MMU_IS_060)					\
	    ? (__pgprot((pgprot_val(prot) & _CACHEMASK040) | _PAGE_NOCACHE_S))	\
	    : (prot)))

pgprot_t pgprot_dmacoherent(pgprot_t prot);
#घोषणा pgprot_dmacoherent(prot)	pgprot_dmacoherent(prot)

#पूर्ण_अगर /* CONFIG_COLDFIRE */
#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _M68K_PGTABLE_H */
