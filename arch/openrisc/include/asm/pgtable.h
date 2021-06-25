<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

/* or32 pgtable.h - macros and functions to manipulate page tables
 *
 * Based on:
 * include/यंत्र-cris/pgtable.h
 */

#अगर_अघोषित __ASM_OPENRISC_PGTABLE_H
#घोषणा __ASM_OPENRISC_PGTABLE_H

#समावेश <यंत्र-generic/pgtable-nopmd.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/fixmap.h>

/*
 * The Linux memory management assumes a three-level page table setup. On
 * or32, we use that, but "fold" the mid level पूर्णांकo the top-level page
 * table. Since the MMU TLB is software loaded through an पूर्णांकerrupt, it
 * supports any page table काष्ठाure, so we could have used a three-level
 * setup, but क्रम the amounts of memory we normally use, a two-level is
 * probably more efficient.
 *
 * This file contains the functions and defines necessary to modअगरy and use
 * the or32 page table tree.
 */

बाह्य व्योम paging_init(व्योम);

/* Certain architectures need to करो special things when pte's
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */
#घोषणा set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
#घोषणा set_pte_at(mm, addr, ptep, pteval) set_pte(ptep, pteval)
/*
 * (pmds are folded पूर्णांकo pgds so this करोesn't get actually called,
 * but the define is needed क्रम a generic अंतरभूत function.)
 */
#घोषणा set_pmd(pmdptr, pmdval) (*(pmdptr) = pmdval)

#घोषणा PGसूची_SHIFT	(PAGE_SHIFT + (PAGE_SHIFT-2))
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/*
 * entries per page directory level: we use a two-level, so
 * we करोn't really have any PMD directory physically.
 * poपूर्णांकers are 4 bytes so we can use the page size and
 * भागide it by 4 (shअगरt by 2).
 */
#घोषणा PTRS_PER_PTE	(1UL << (PAGE_SHIFT-2))

#घोषणा PTRS_PER_PGD	(1UL << (32-PGसूची_SHIFT))

/* calculate how many PGD entries a user-level program can use
 * the first mappable भव address is 0
 * (TASK_SIZE is the maximum भव address space)
 */

#घोषणा USER_PTRS_PER_PGD       (TASK_SIZE/PGसूची_SIZE)
#घोषणा FIRST_USER_ADDRESS      0UL

/*
 * Kernels own भव memory area.
 */

/*
 * The size and location of the vदो_स्मृति area are chosen so that modules
 * placed in this area aren't more than a 28-bit चिन्हित offset from any
 * kernel functions that they may need.  This greatly simplअगरies handling
 * of the relocations क्रम l.j and l.jal inकाष्ठाions as we करोn't need to
 * पूर्णांकroduce any trampolines क्रम reaching "distant" code.
 *
 * 64 MB of vदो_स्मृति area is comparable to what's available on other arches.
 */

#घोषणा VMALLOC_START	(PAGE_OFFSET-0x04000000UL)
#घोषणा VMALLOC_END	(PAGE_OFFSET)
#घोषणा VMALLOC_VMADDR(x) ((अचिन्हित दीर्घ)(x))

/* Define some higher level generic page attributes.
 *
 * If you change _PAGE_CI definition be sure to change it in
 * पन.स क्रम ioremap() too.
 */

/*
 * An OR32 PTE looks like this:
 *
 * |  31 ... 10 |  9  |  8 ... 6  |  5  |  4  |  3  |  2  |  1  |  0  |
 *  Phys pg.num    L     PP Index    D     A    WOM   WBC   CI    CC
 *
 *  L  : link
 *  PPI: Page protection index
 *  D  : Dirty
 *  A  : Accessed
 *  WOM: Weakly ordered memory
 *  WBC: Write-back cache
 *  CI : Cache inhibit
 *  CC : Cache coherent
 *
 * The protection bits below should correspond to the layout of the actual
 * PTE as per above
 */

#घोषणा _PAGE_CC       0x001 /* software: pte contains a translation */
#घोषणा _PAGE_CI       0x002 /* cache inhibit          */
#घोषणा _PAGE_WBC      0x004 /* ग_लिखो back cache       */
#घोषणा _PAGE_WOM      0x008 /* weakly ordered memory  */

#घोषणा _PAGE_A        0x010 /* accessed               */
#घोषणा _PAGE_D        0x020 /* dirty                  */
#घोषणा _PAGE_URE      0x040 /* user पढ़ो enable       */
#घोषणा _PAGE_UWE      0x080 /* user ग_लिखो enable      */

#घोषणा _PAGE_SRE      0x100 /* superuser पढ़ो enable  */
#घोषणा _PAGE_SWE      0x200 /* superuser ग_लिखो enable */
#घोषणा _PAGE_EXEC     0x400 /* software: page is executable */
#घोषणा _PAGE_U_SHARED 0x800 /* software: page is shared in user space */

/* 0x001 is cache coherency bit, which should always be set to
 *       1 - क्रम SMP (when we support it)
 *       0 - otherwise
 *
 * we just reuse this bit in software क्रम _PAGE_PRESENT and
 * क्रमce it to 0 when loading it पूर्णांकo TLB.
 */
#घोषणा _PAGE_PRESENT  _PAGE_CC
#घोषणा _PAGE_USER     _PAGE_URE
#घोषणा _PAGE_WRITE    (_PAGE_UWE | _PAGE_SWE)
#घोषणा _PAGE_सूचीTY    _PAGE_D
#घोषणा _PAGE_ACCESSED _PAGE_A
#घोषणा _PAGE_NO_CACHE _PAGE_CI
#घोषणा _PAGE_SHARED   _PAGE_U_SHARED
#घोषणा _PAGE_READ     (_PAGE_URE | _PAGE_SRE)

#घोषणा _PAGE_CHG_MASK	(PAGE_MASK | _PAGE_ACCESSED | _PAGE_सूचीTY)
#घोषणा _PAGE_BASE     (_PAGE_PRESENT | _PAGE_ACCESSED)
#घोषणा _PAGE_ALL      (_PAGE_PRESENT | _PAGE_ACCESSED)
#घोषणा _KERNPG_TABLE \
	(_PAGE_BASE | _PAGE_SRE | _PAGE_SWE | _PAGE_ACCESSED | _PAGE_सूचीTY)

#घोषणा PAGE_NONE       __pgprot(_PAGE_ALL)
#घोषणा PAGE_READONLY   __pgprot(_PAGE_ALL | _PAGE_URE | _PAGE_SRE)
#घोषणा PAGE_READONLY_X __pgprot(_PAGE_ALL | _PAGE_URE | _PAGE_SRE | _PAGE_EXEC)
#घोषणा PAGE_SHARED \
	__pgprot(_PAGE_ALL | _PAGE_URE | _PAGE_SRE | _PAGE_UWE | _PAGE_SWE \
		 | _PAGE_SHARED)
#घोषणा PAGE_SHARED_X \
	__pgprot(_PAGE_ALL | _PAGE_URE | _PAGE_SRE | _PAGE_UWE | _PAGE_SWE \
		 | _PAGE_SHARED | _PAGE_EXEC)
#घोषणा PAGE_COPY       __pgprot(_PAGE_ALL | _PAGE_URE | _PAGE_SRE)
#घोषणा PAGE_COPY_X     __pgprot(_PAGE_ALL | _PAGE_URE | _PAGE_SRE | _PAGE_EXEC)

#घोषणा PAGE_KERNEL \
	__pgprot(_PAGE_ALL | _PAGE_SRE | _PAGE_SWE \
		 | _PAGE_SHARED | _PAGE_सूचीTY | _PAGE_EXEC)
#घोषणा PAGE_KERNEL_RO \
	__pgprot(_PAGE_ALL | _PAGE_SRE \
		 | _PAGE_SHARED | _PAGE_सूचीTY | _PAGE_EXEC)
#घोषणा PAGE_KERNEL_NOCACHE \
	__pgprot(_PAGE_ALL | _PAGE_SRE | _PAGE_SWE \
		 | _PAGE_SHARED | _PAGE_सूचीTY | _PAGE_EXEC | _PAGE_CI)

#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READONLY_X
#घोषणा __P010	PAGE_COPY
#घोषणा __P011	PAGE_COPY_X
#घोषणा __P100	PAGE_READONLY
#घोषणा __P101	PAGE_READONLY_X
#घोषणा __P110	PAGE_COPY
#घोषणा __P111	PAGE_COPY_X

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READONLY_X
#घोषणा __S010	PAGE_SHARED
#घोषणा __S011	PAGE_SHARED_X
#घोषणा __S100	PAGE_READONLY
#घोषणा __S101	PAGE_READONLY_X
#घोषणा __S110	PAGE_SHARED
#घोषणा __S111	PAGE_SHARED_X

/* zero page used क्रम uninitialized stuff */
बाह्य अचिन्हित दीर्घ empty_zero_page[2048];
#घोषणा ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))

/* number of bits that fit पूर्णांकo a memory poपूर्णांकer */
#घोषणा BITS_PER_PTR			(8*माप(अचिन्हित दीर्घ))

/* to align the poपूर्णांकer to a poपूर्णांकer address */
#घोषणा PTR_MASK			(~(माप(व्योम *)-1))

/* माप(व्योम*)==1<<SIZखातापूर्ण_PTR_LOG2 */
/* 64-bit machines, beware!  SRB. */
#घोषणा SIZखातापूर्ण_PTR_LOG2			2

/* to find an entry in a page-table */
#घोषणा PAGE_PTR(address) \
((अचिन्हित दीर्घ)(address)>>(PAGE_SHIFT-SIZखातापूर्ण_PTR_LOG2)&PTR_MASK&~PAGE_MASK)

/* to set the page-dir */
#घोषणा SET_PAGE_सूची(tsk, pgdir)

#घोषणा pte_none(x)	(!pte_val(x))
#घोषणा pte_present(x)	(pte_val(x) & _PAGE_PRESENT)
#घोषणा pte_clear(mm, addr, xp)	करो अणु pte_val(*(xp)) = 0; पूर्ण जबतक (0)

#घोषणा pmd_none(x)	(!pmd_val(x))
#घोषणा	pmd_bad(x)	((pmd_val(x) & (~PAGE_MASK)) != _KERNPG_TABLE)
#घोषणा pmd_present(x)	(pmd_val(x) & _PAGE_PRESENT)
#घोषणा pmd_clear(xp)	करो अणु pmd_val(*(xp)) = 0; पूर्ण जबतक (0)

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */

अटल अंतरभूत पूर्णांक pte_पढ़ो(pte_t pte)  अणु वापस pte_val(pte) & _PAGE_READ; पूर्ण
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte) अणु वापस pte_val(pte) & _PAGE_WRITE; पूर्ण
अटल अंतरभूत पूर्णांक pte_exec(pte_t pte)  अणु वापस pte_val(pte) & _PAGE_EXEC; पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte) अणु वापस pte_val(pte) & _PAGE_सूचीTY; पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte) अणु वापस pte_val(pte) & _PAGE_ACCESSED; पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_WRITE);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_rdprotect(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_READ);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_exprotect(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_EXEC);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_सूचीTY);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_ACCESSED);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_WRITE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkपढ़ो(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_READ;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkexec(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_EXEC;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_सूचीTY;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_ACCESSED;
	वापस pte;
पूर्ण

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */

/* What actually goes as arguments to the various functions is less than
 * obvious, but a rule of thumb is that काष्ठा page's goes as काष्ठा page *,
 * really physical DRAM addresses are अचिन्हित दीर्घ's, and DRAM "virtual"
 * addresses (the 0xc0xxxxxx's) goes as void *'s.
 */

अटल अंतरभूत pte_t __mk_pte(व्योम *page, pgprot_t pgprot)
अणु
	pte_t pte;
	/* the PTE needs a physical address */
	pte_val(pte) = __pa(page) | pgprot_val(pgprot);
	वापस pte;
पूर्ण

#घोषणा mk_pte(page, pgprot) __mk_pte(page_address(page), (pgprot))

#घोषणा mk_pte_phys(physpage, pgprot) \
(अणु                                                                      \
	pte_t __pte;                                                    \
									\
	pte_val(__pte) = (physpage) + pgprot_val(pgprot);               \
	__pte;                                                          \
पूर्ण)

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte_val(pte) = (pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot);
	वापस pte;
पूर्ण


/*
 * pte_val refers to a page in the 0x0xxxxxxx physical DRAM पूर्णांकerval
 * __pte_page(pte_val) refers to the "virtual" DRAM पूर्णांकerval
 * pte_pagenr refers to the page-number counted starting from the भव
 * DRAM start
 */

अटल अंतरभूत अचिन्हित दीर्घ __pte_page(pte_t pte)
अणु
	/* the PTE contains a physical address */
	वापस (अचिन्हित दीर्घ)__va(pte_val(pte) & PAGE_MASK);
पूर्ण

#घोषणा pte_pagenr(pte)         ((__pte_page(pte) - PAGE_OFFSET) >> PAGE_SHIFT)

/* permanent address of a page */

#घोषणा __page_address(page) (PAGE_OFFSET + (((page) - mem_map) << PAGE_SHIFT))
#घोषणा pte_page(pte)		(mem_map+pte_pagenr(pte))

/*
 * only the pte's themselves need to poपूर्णांक to physical DRAM (see above)
 * the pagetable links are purely handled within the kernel SW and thus
 * करोn't need the __pa and __va transक्रमmations.
 */
अटल अंतरभूत व्योम pmd_set(pmd_t *pmdp, pte_t *ptep)
अणु
	pmd_val(*pmdp) = _KERNPG_TABLE | (अचिन्हित दीर्घ) ptep;
पूर्ण

#घोषणा pmd_page(pmd)		(pfn_to_page(pmd_val(pmd) >> PAGE_SHIFT))

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस ((अचिन्हित दीर्घ) __va(pmd_val(pmd) & PAGE_MASK));
पूर्ण

#घोषणा __pmd_offset(address) \
	(((address) >> PMD_SHIFT) & (PTRS_PER_PMD-1))

#घोषणा pte_pfn(x)		((अचिन्हित दीर्घ)(((x).pte)) >> PAGE_SHIFT)
#घोषणा pfn_pte(pfn, prot)  __pte((((pfn) << PAGE_SHIFT)) | pgprot_val(prot))

#घोषणा pte_ERROR(e) \
	prपूर्णांकk(KERN_ERR "%s:%d: bad pte %p(%08lx).\n", \
	       __खाता__, __LINE__, &(e), pte_val(e))
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk(KERN_ERR "%s:%d: bad pgd %p(%08lx).\n", \
	       __खाता__, __LINE__, &(e), pgd_val(e))

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD]; /* defined in head.S */

काष्ठा vm_area_काष्ठा;

अटल अंतरभूत व्योम update_tlb(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ address, pte_t *pte)
अणु
पूर्ण

बाह्य व्योम update_cache(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ address, pte_t *pte);

अटल अंतरभूत व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ address, pte_t *pte)
अणु
	update_tlb(vma, address, pte);
	update_cache(vma, address, pte);
पूर्ण

/* __PHX__ FIXME, SWAP, this probably करोesn't work */

/* Encode and de-code a swap entry (must be !pte_none(e) && !pte_present(e)) */
/* Since the PAGE_PRESENT bit is bit 4, we can use the bits above */

#घोषणा __swp_type(x)			(((x).val >> 5) & 0x7f)
#घोषणा __swp_offset(x)			((x).val >> 12)
#घोषणा __swp_entry(type, offset) \
	((swp_entry_t) अणु ((type) << 5) | ((offset) << 12) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val पूर्ण)

#घोषणा kern_addr_valid(addr)           (1)

प्रकार pte_t *pte_addr_t;

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_OPENRISC_PGTABLE_H */
