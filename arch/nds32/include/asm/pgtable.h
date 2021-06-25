<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित _ASMNDS32_PGTABLE_H
#घोषणा _ASMNDS32_PGTABLE_H

#समावेश <यंत्र-generic/pgtable-nopmd.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/nds32.h>
#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/fixmap.h>
#समावेश <nds32_पूर्णांकrinsic.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_ANDES_PAGE_SIZE_4KB
#घोषणा PGसूची_SHIFT      22
#घोषणा PTRS_PER_PGD     1024
#घोषणा PTRS_PER_PTE     1024
#पूर्ण_अगर

#अगर_घोषित CONFIG_ANDES_PAGE_SIZE_8KB
#घोषणा PGसूची_SHIFT      24
#घोषणा PTRS_PER_PGD     256
#घोषणा PTRS_PER_PTE     2048
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम __pte_error(स्थिर अक्षर *file, पूर्णांक line, अचिन्हित दीर्घ val);
बाह्य व्योम __pgd_error(स्थिर अक्षर *file, पूर्णांक line, अचिन्हित दीर्घ val);

#घोषणा pte_ERROR(pte)		__pte_error(__खाता__, __LINE__, pte_val(pte))
#घोषणा pgd_ERROR(pgd)		__pgd_error(__खाता__, __LINE__, pgd_val(pgd))
#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा PMD_SIZE		(1UL << PMD_SHIFT)
#घोषणा PMD_MASK		(~(PMD_SIZE-1))
#घोषणा PGसूची_SIZE		(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK		(~(PGसूची_SIZE-1))

/*
 * This is the lowest भव address we can permit any user space
 * mapping to be mapped at.  This is particularly important क्रम
 * non-high vector CPUs.
 */
#घोषणा FIRST_USER_ADDRESS	0x8000

#अगर_घोषित CONFIG_HIGHMEM
#घोषणा CONSISTENT_BASE		((PKMAP_BASE) - (SZ_2M))
#घोषणा CONSISTENT_END		(PKMAP_BASE)
#अन्यथा
#घोषणा CONSISTENT_BASE		(FIXADDR_START - SZ_2M)
#घोषणा CONSISTENT_END		(FIXADDR_START)
#पूर्ण_अगर
#घोषणा CONSISTENT_OFFSET(x)	(((अचिन्हित दीर्घ)(x) - CONSISTENT_BASE) >> PAGE_SHIFT)

#अगर_घोषित CONFIG_HIGHMEM
#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/highस्मृति.स>
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा VMALLOC_RESERVE 	SZ_128M
#घोषणा VMALLOC_END		(CONSISTENT_BASE - PAGE_SIZE)
#घोषणा VMALLOC_START		((VMALLOC_END) - VMALLOC_RESERVE)
#घोषणा VMALLOC_VMADDR(x)	((अचिन्हित दीर्घ)(x))
#घोषणा MAXMEM			__pa(VMALLOC_START)
#घोषणा MAXMEM_PFN		PFN_DOWN(MAXMEM)

#घोषणा FIRST_USER_PGD_NR	0
#घोषणा USER_PTRS_PER_PGD	((TASK_SIZE/PGसूची_SIZE) + FIRST_USER_PGD_NR)

/* L2 PTE */
#घोषणा _PAGE_V			(1UL << 0)

#घोषणा _PAGE_M_XKRW            (0UL << 1)
#घोषणा _PAGE_M_UR_KR		(1UL << 1)
#घोषणा _PAGE_M_UR_KRW		(2UL << 1)
#घोषणा _PAGE_M_URW_KRW		(3UL << 1)
#घोषणा _PAGE_M_KR		(5UL << 1)
#घोषणा _PAGE_M_KRW		(7UL << 1)

#घोषणा _PAGE_D			(1UL << 4)
#घोषणा _PAGE_E			(1UL << 5)
#घोषणा _PAGE_A			(1UL << 6)
#घोषणा _PAGE_G			(1UL << 7)

#घोषणा _PAGE_C_DEV		(0UL << 8)
#घोषणा _PAGE_C_DEV_WB		(1UL << 8)
#घोषणा _PAGE_C_MEM		(2UL << 8)
#घोषणा _PAGE_C_MEM_SHRD_WB	(4UL << 8)
#घोषणा _PAGE_C_MEM_SHRD_WT	(5UL << 8)
#घोषणा _PAGE_C_MEM_WB		(6UL << 8)
#घोषणा _PAGE_C_MEM_WT		(7UL << 8)

#घोषणा _PAGE_L			(1UL << 11)

#घोषणा _HAVE_PAGE_L		(_PAGE_L)
#घोषणा _PAGE_खाता		(1UL << 1)
#घोषणा _PAGE_YOUNG		0
#घोषणा _PAGE_M_MASK		_PAGE_M_KRW
#घोषणा _PAGE_C_MASK		_PAGE_C_MEM_WT

#अगर_घोषित CONFIG_SMP
#अगर_घोषित CONFIG_CPU_DCACHE_WRITETHROUGH
#घोषणा _PAGE_CACHE_SHRD	_PAGE_C_MEM_SHRD_WT
#अन्यथा
#घोषणा _PAGE_CACHE_SHRD	_PAGE_C_MEM_SHRD_WB
#पूर्ण_अगर
#अन्यथा
#अगर_घोषित CONFIG_CPU_DCACHE_WRITETHROUGH
#घोषणा _PAGE_CACHE_SHRD	_PAGE_C_MEM_WT
#अन्यथा
#घोषणा _PAGE_CACHE_SHRD	_PAGE_C_MEM_WB
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_DCACHE_WRITETHROUGH
#घोषणा _PAGE_CACHE		_PAGE_C_MEM_WT
#अन्यथा
#घोषणा _PAGE_CACHE		_PAGE_C_MEM_WB
#पूर्ण_अगर

#घोषणा _PAGE_IOREMAP \
	(_PAGE_V | _PAGE_M_KRW | _PAGE_D | _PAGE_G | _PAGE_C_DEV)

/*
 * + Level 1 descriptor (PMD)
 */
#घोषणा PMD_TYPE_TABLE		0

#अगर_अघोषित __ASSEMBLY__

#घोषणा _PAGE_USER_TABLE     PMD_TYPE_TABLE
#घोषणा _PAGE_KERNEL_TABLE   PMD_TYPE_TABLE

#घोषणा PAGE_EXEC	__pgprot(_PAGE_V | _PAGE_M_XKRW | _PAGE_E)
#घोषणा PAGE_NONE	__pgprot(_PAGE_V | _PAGE_M_KRW | _PAGE_A)
#घोषणा PAGE_READ	__pgprot(_PAGE_V | _PAGE_M_UR_KR)
#घोषणा PAGE_RDWR	__pgprot(_PAGE_V | _PAGE_M_URW_KRW | _PAGE_D)
#घोषणा PAGE_COPY	__pgprot(_PAGE_V | _PAGE_M_UR_KR)

#घोषणा PAGE_UXKRWX_V1	__pgprot(_PAGE_V | _PAGE_M_KRW | _PAGE_D | _PAGE_E | _PAGE_G | _PAGE_CACHE_SHRD)
#घोषणा PAGE_UXKRWX_V2	__pgprot(_PAGE_V | _PAGE_M_XKRW | _PAGE_D | _PAGE_E | _PAGE_G | _PAGE_CACHE_SHRD)
#घोषणा PAGE_URXKRWX_V2	__pgprot(_PAGE_V | _PAGE_M_UR_KRW | _PAGE_D | _PAGE_E | _PAGE_G | _PAGE_CACHE_SHRD)
#घोषणा PAGE_CACHE_L1	__pgprot(_HAVE_PAGE_L | _PAGE_V | _PAGE_M_KRW | _PAGE_D | _PAGE_E | _PAGE_G | _PAGE_CACHE)
#घोषणा PAGE_MEMORY	__pgprot(_HAVE_PAGE_L | _PAGE_V | _PAGE_M_KRW | _PAGE_D | _PAGE_E | _PAGE_G | _PAGE_CACHE_SHRD)
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_V | _PAGE_M_KRW | _PAGE_D | _PAGE_E | _PAGE_G | _PAGE_CACHE_SHRD)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_V | _PAGE_M_URW_KRW | _PAGE_D | _PAGE_CACHE_SHRD)
#घोषणा PAGE_DEVICE    __pgprot(_PAGE_V | _PAGE_M_KRW | _PAGE_D | _PAGE_G | _PAGE_C_DEV)
#पूर्ण_अगर /* __ASSEMBLY__ */

/*         xwr */
#घोषणा __P000  (PAGE_NONE | _PAGE_CACHE_SHRD)
#घोषणा __P001  (PAGE_READ | _PAGE_CACHE_SHRD)
#घोषणा __P010  (PAGE_COPY | _PAGE_CACHE_SHRD)
#घोषणा __P011  (PAGE_COPY | _PAGE_CACHE_SHRD)
#घोषणा __P100  (PAGE_EXEC | _PAGE_CACHE_SHRD)
#घोषणा __P101  (PAGE_READ | _PAGE_E | _PAGE_CACHE_SHRD)
#घोषणा __P110  (PAGE_COPY | _PAGE_E | _PAGE_CACHE_SHRD)
#घोषणा __P111  (PAGE_COPY | _PAGE_E | _PAGE_CACHE_SHRD)

#घोषणा __S000  (PAGE_NONE | _PAGE_CACHE_SHRD)
#घोषणा __S001  (PAGE_READ | _PAGE_CACHE_SHRD)
#घोषणा __S010  (PAGE_RDWR | _PAGE_CACHE_SHRD)
#घोषणा __S011  (PAGE_RDWR | _PAGE_CACHE_SHRD)
#घोषणा __S100  (PAGE_EXEC | _PAGE_CACHE_SHRD)
#घोषणा __S101  (PAGE_READ | _PAGE_E | _PAGE_CACHE_SHRD)
#घोषणा __S110  (PAGE_RDWR | _PAGE_E | _PAGE_CACHE_SHRD)
#घोषणा __S111  (PAGE_RDWR | _PAGE_E | _PAGE_CACHE_SHRD)

#अगर_अघोषित __ASSEMBLY__
/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य काष्ठा page *empty_zero_page;
बाह्य व्योम paging_init(व्योम);
#घोषणा ZERO_PAGE(vaddr)	(empty_zero_page)

#घोषणा pte_pfn(pte)		(pte_val(pte) >> PAGE_SHIFT)
#घोषणा pfn_pte(pfn,prot)	(__pte(((pfn) << PAGE_SHIFT) | pgprot_val(prot)))

#घोषणा pte_none(pte)	        !(pte_val(pte))
#घोषणा pte_clear(mm,addr,ptep)	set_pte_at((mm),(addr),(ptep), __pte(0))
#घोषणा pte_page(pte)		(pfn_to_page(pte_pfn(pte)))

अटल अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस ((अचिन्हित दीर्घ) __va(pmd_val(pmd) & PAGE_MASK));
पूर्ण

#घोषणा set_pte_at(mm,addr,ptep,pteval) set_pte(ptep,pteval)
/*
 * Set a level 1 translation table entry, and clean it out of
 * any caches such that the MMUs can load it correctly.
 */
अटल अंतरभूत व्योम set_pmd(pmd_t * pmdp, pmd_t pmd)
अणु

	*pmdp = pmd;
#अगर !defined(CONFIG_CPU_DCACHE_DISABLE) && !defined(CONFIG_CPU_DCACHE_WRITETHROUGH)
	__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (pmdp):"memory");
	__nds32__msync_all();
	__nds32__dsb();
#पूर्ण_अगर
पूर्ण

/*
 * Set a PTE and flush it out
 */
अटल अंतरभूत व्योम set_pte(pte_t * ptep, pte_t pte)
अणु

	*ptep = pte;
#अगर !defined(CONFIG_CPU_DCACHE_DISABLE) && !defined(CONFIG_CPU_DCACHE_WRITETHROUGH)
	__यंत्र__ अस्थिर ("\n\tcctl %0, L1D_VA_WB"::"r" (ptep):"memory");
	__nds32__msync_all();
	__nds32__dsb();
#पूर्ण_अगर
पूर्ण

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */

/*
 * pte_ग_लिखो: 	     this page is ग_लिखोable क्रम user mode
 * pte_पढ़ो:         this page is पढ़ोable क्रम user mode
 * pte_kernel_ग_लिखो: this page is ग_लिखोable क्रम kernel mode
 *
 * We करोn't have pte_kernel_पढ़ो because kernel always can पढ़ो.
 *
 * */

#घोषणा pte_present(pte)        (pte_val(pte) & _PAGE_V)
#घोषणा pte_ग_लिखो(pte)          ((pte_val(pte) & _PAGE_M_MASK) == _PAGE_M_URW_KRW)
#घोषणा pte_पढ़ो(pte)		(((pte_val(pte) & _PAGE_M_MASK) == _PAGE_M_UR_KR) || \
				((pte_val(pte) & _PAGE_M_MASK) == _PAGE_M_UR_KRW) || \
				((pte_val(pte) & _PAGE_M_MASK) == _PAGE_M_URW_KRW))
#घोषणा pte_kernel_ग_लिखो(pte)   (((pte_val(pte) & _PAGE_M_MASK) == _PAGE_M_URW_KRW) || \
				((pte_val(pte) & _PAGE_M_MASK) == _PAGE_M_UR_KRW) || \
				((pte_val(pte) & _PAGE_M_MASK) == _PAGE_M_KRW) || \
				(((pte_val(pte) & _PAGE_M_MASK) == _PAGE_M_XKRW) && pte_exec(pte)))
#घोषणा pte_exec(pte)		(pte_val(pte) & _PAGE_E)
#घोषणा pte_dirty(pte)		(pte_val(pte) & _PAGE_D)
#घोषणा pte_young(pte)		(pte_val(pte) & _PAGE_YOUNG)

/*
 * The following only works अगर pte_present() is not true.
 */
#घोषणा pte_file(pte)		(pte_val(pte) & _PAGE_खाता)
#घोषणा pte_to_pgoff(x)		(pte_val(x) >> 2)
#घोषणा pgoff_to_pte(x)		__pte(((x) << 2) | _PAGE_खाता)

#घोषणा PTE_खाता_MAX_BITS	29

#घोषणा PTE_BIT_FUNC(fn,op) \
अटल अंतरभूत pte_t pte_##fn(pte_t pte) अणु pte_val(pte) op; वापस pte; पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	pte_val(pte) = pte_val(pte) & ~_PAGE_M_MASK;
	pte_val(pte) = pte_val(pte) | _PAGE_M_UR_KR;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte_val(pte) = pte_val(pte) & ~_PAGE_M_MASK;
	pte_val(pte) = pte_val(pte) | _PAGE_M_URW_KRW;
	वापस pte;
पूर्ण

PTE_BIT_FUNC(exprotect, &=~_PAGE_E);
PTE_BIT_FUNC(mkexec, |=_PAGE_E);
PTE_BIT_FUNC(mkclean, &=~_PAGE_D);
PTE_BIT_FUNC(सूची_गढ़ोty, |=_PAGE_D);
PTE_BIT_FUNC(mkold, &=~_PAGE_YOUNG);
PTE_BIT_FUNC(mkyoung, |=_PAGE_YOUNG);

/*
 * Mark the prot value as uncacheable and unbufferable.
 */
#घोषणा pgprot_noncached(prot)	   __pgprot((pgprot_val(prot)&~_PAGE_C_MASK) | _PAGE_C_DEV)
#घोषणा pgprot_ग_लिखोcombine(prot)  __pgprot((pgprot_val(prot)&~_PAGE_C_MASK) | _PAGE_C_DEV_WB)

#घोषणा pmd_none(pmd)         (pmd_val(pmd)&0x1)
#घोषणा pmd_present(pmd)      (!pmd_none(pmd))
#घोषणा	pmd_bad(pmd)	      pmd_none(pmd)

#घोषणा copy_pmd(pmdpd,pmdps)	set_pmd((pmdpd), *(pmdps))
#घोषणा pmd_clear(pmdp)		set_pmd((pmdp), __pmd(1))

अटल अंतरभूत pmd_t __mk_pmd(pte_t * ptep, अचिन्हित दीर्घ prot)
अणु
	अचिन्हित दीर्घ ptr = (अचिन्हित दीर्घ)ptep;
	pmd_t pmd;

	/*
	 * The pmd must be loaded with the physical
	 * address of the PTE table
	 */

	pmd_val(pmd) = __virt_to_phys(ptr) | prot;
	वापस pmd;
पूर्ण

#घोषणा pmd_page(pmd)        virt_to_page(__va(pmd_val(pmd)))

/*
 * Permanent address of a page. We never have highmem, so this is trivial.
 */
#घोषणा pages_to_mb(x)       ((x) >> (20 - PAGE_SHIFT))

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा mk_pte(page,prot)	pfn_pte(page_to_pfn(page),prot)

/*
 * The "pgd_xxx()" functions here are trivial क्रम a folded two-level
 * setup: the pgd is never bad, and a pmd always exists (as it's folded
 * पूर्णांकo the pgd entry)
 */
#घोषणा pgd_none(pgd)		(0)
#घोषणा pgd_bad(pgd)		(0)
#घोषणा pgd_present(pgd)  	(1)
#घोषणा pgd_clear(pgdp)		करो अणु पूर्ण जबतक (0)

#घोषणा page_pte_prot(page,prot)     	mk_pte(page, prot)
#घोषणा page_pte(page)		        mk_pte(page, __pgprot(0))
/*
 *     L1PTE = $mr1 + ((virt >> PMD_SHIFT) << 2);
 *     L2PTE = (((virt >> PAGE_SHIFT) & (PTRS_PER_PTE -1 )) << 2);
 *     PPN = (phys & 0xfffff000);
 *
*/

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	स्थिर अचिन्हित दीर्घ mask = 0xfff;
	pte_val(pte) = (pte_val(pte) & ~mask) | (pgprot_val(newprot) & mask);
	वापस pte;
पूर्ण

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];

/* Encode and decode a swap entry.
 *
 * We support up to 32GB of swap on 4k machines
 */
#घोषणा __swp_type(x)	 	     (((x).val >> 2) & 0x7f)
#घोषणा __swp_offset(x)	   	     ((x).val >> 9)
#घोषणा __swp_entry(type,offset)     ((swp_entry_t) अणु ((type) << 2) | ((offset) << 9) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)	     ((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(swp)	     ((pte_t) अणु (swp).val पूर्ण)

/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
#घोषणा kern_addr_valid(addr)	(1)

/*
 * We provide our own arch_get_unmapped_area to cope with VIPT caches.
 */
#घोषणा HAVE_ARCH_UNMAPPED_AREA

/*
 * remap a physical address `phys' of size `size' with page protection `prot'
 * पूर्णांकo भव address `from'
 */

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASMNDS32_PGTABLE_H */
