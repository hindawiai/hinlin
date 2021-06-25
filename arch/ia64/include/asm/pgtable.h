<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_PGTABLE_H
#घोषणा _ASM_IA64_PGTABLE_H

/*
 * This file contains the functions and defines necessary to modअगरy and use
 * the IA-64 page table tree.
 *
 * This hopefully works with any (fixed) IA-64 page-size, as defined
 * in <यंत्र/page.h>.
 *
 * Copyright (C) 1998-2005 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */


#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/types.h>

#घोषणा IA64_MAX_PHYS_BITS	50	/* max. number of physical address bits (architected) */

/*
 * First, define the various bits in a PTE.  Note that the PTE क्रमmat
 * matches the VHPT लघु क्रमmat, the firt द्विगुनword of the VHPD दीर्घ
 * क्रमmat, and the first द्विगुनword of the TLB insertion क्रमmat.
 */
#घोषणा _PAGE_P_BIT		0
#घोषणा _PAGE_A_BIT		5
#घोषणा _PAGE_D_BIT		6

#घोषणा _PAGE_P			(1 << _PAGE_P_BIT)	/* page present bit */
#घोषणा _PAGE_MA_WB		(0x0 <<  2)	/* ग_लिखो back memory attribute */
#घोषणा _PAGE_MA_UC		(0x4 <<  2)	/* uncacheable memory attribute */
#घोषणा _PAGE_MA_UCE		(0x5 <<  2)	/* UC exported attribute */
#घोषणा _PAGE_MA_WC		(0x6 <<  2)	/* ग_लिखो coalescing memory attribute */
#घोषणा _PAGE_MA_NAT		(0x7 <<  2)	/* not-a-thing attribute */
#घोषणा _PAGE_MA_MASK		(0x7 <<  2)
#घोषणा _PAGE_PL_0		(0 <<  7)	/* privilege level 0 (kernel) */
#घोषणा _PAGE_PL_1		(1 <<  7)	/* privilege level 1 (unused) */
#घोषणा _PAGE_PL_2		(2 <<  7)	/* privilege level 2 (unused) */
#घोषणा _PAGE_PL_3		(3 <<  7)	/* privilege level 3 (user) */
#घोषणा _PAGE_PL_MASK		(3 <<  7)
#घोषणा _PAGE_AR_R		(0 <<  9)	/* पढ़ो only */
#घोषणा _PAGE_AR_RX		(1 <<  9)	/* पढ़ो & execute */
#घोषणा _PAGE_AR_RW		(2 <<  9)	/* पढ़ो & ग_लिखो */
#घोषणा _PAGE_AR_RWX		(3 <<  9)	/* पढ़ो, ग_लिखो & execute */
#घोषणा _PAGE_AR_R_RW		(4 <<  9)	/* पढ़ो / पढ़ो & ग_लिखो */
#घोषणा _PAGE_AR_RX_RWX		(5 <<  9)	/* पढ़ो & exec / पढ़ो, ग_लिखो & exec */
#घोषणा _PAGE_AR_RWX_RW		(6 <<  9)	/* पढ़ो, ग_लिखो & exec / पढ़ो & ग_लिखो */
#घोषणा _PAGE_AR_X_RX		(7 <<  9)	/* exec & promote / पढ़ो & exec */
#घोषणा _PAGE_AR_MASK		(7 <<  9)
#घोषणा _PAGE_AR_SHIFT		9
#घोषणा _PAGE_A			(1 << _PAGE_A_BIT)	/* page accessed bit */
#घोषणा _PAGE_D			(1 << _PAGE_D_BIT)	/* page dirty bit */
#घोषणा _PAGE_PPN_MASK		(((__IA64_UL(1) << IA64_MAX_PHYS_BITS) - 1) & ~0xfffUL)
#घोषणा _PAGE_ED		(__IA64_UL(1) << 52)	/* exception deferral */
#घोषणा _PAGE_PROTNONE		(__IA64_UL(1) << 63)

#घोषणा _PFN_MASK		_PAGE_PPN_MASK
/* Mask of bits which may be changed by pte_modअगरy(); the odd bits are there क्रम _PAGE_PROTNONE */
#घोषणा _PAGE_CHG_MASK	(_PAGE_P | _PAGE_PROTNONE | _PAGE_PL_MASK | _PAGE_AR_MASK | _PAGE_ED)

#घोषणा _PAGE_SIZE_4K	12
#घोषणा _PAGE_SIZE_8K	13
#घोषणा _PAGE_SIZE_16K	14
#घोषणा _PAGE_SIZE_64K	16
#घोषणा _PAGE_SIZE_256K	18
#घोषणा _PAGE_SIZE_1M	20
#घोषणा _PAGE_SIZE_4M	22
#घोषणा _PAGE_SIZE_16M	24
#घोषणा _PAGE_SIZE_64M	26
#घोषणा _PAGE_SIZE_256M	28
#घोषणा _PAGE_SIZE_1G	30
#घोषणा _PAGE_SIZE_4G	32

#घोषणा __ACCESS_BITS		_PAGE_ED | _PAGE_A | _PAGE_P | _PAGE_MA_WB
#घोषणा __सूचीTY_BITS_NO_ED	_PAGE_A | _PAGE_P | _PAGE_D | _PAGE_MA_WB
#घोषणा __सूचीTY_BITS		_PAGE_ED | __सूचीTY_BITS_NO_ED

/*
 * How many poपूर्णांकers will a page table level hold expressed in shअगरt
 */
#घोषणा PTRS_PER_PTD_SHIFT	(PAGE_SHIFT-3)

/*
 * Definitions क्रम fourth level:
 */
#घोषणा PTRS_PER_PTE	(__IA64_UL(1) << (PTRS_PER_PTD_SHIFT))

/*
 * Definitions क्रम third level:
 *
 * PMD_SHIFT determines the size of the area a third-level page table
 * can map.
 */
#घोषणा PMD_SHIFT	(PAGE_SHIFT + (PTRS_PER_PTD_SHIFT))
#घोषणा PMD_SIZE	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))
#घोषणा PTRS_PER_PMD	(1UL << (PTRS_PER_PTD_SHIFT))

#अगर CONFIG_PGTABLE_LEVELS == 4
/*
 * Definitions क्रम second level:
 *
 * PUD_SHIFT determines the size of the area a second-level page table
 * can map.
 */
#घोषणा PUD_SHIFT	(PMD_SHIFT + (PTRS_PER_PTD_SHIFT))
#घोषणा PUD_SIZE	(1UL << PUD_SHIFT)
#घोषणा PUD_MASK	(~(PUD_SIZE-1))
#घोषणा PTRS_PER_PUD	(1UL << (PTRS_PER_PTD_SHIFT))
#पूर्ण_अगर

/*
 * Definitions क्रम first level:
 *
 * PGसूची_SHIFT determines what a first-level page table entry can map.
 */
#अगर CONFIG_PGTABLE_LEVELS == 4
#घोषणा PGसूची_SHIFT		(PUD_SHIFT + (PTRS_PER_PTD_SHIFT))
#अन्यथा
#घोषणा PGसूची_SHIFT		(PMD_SHIFT + (PTRS_PER_PTD_SHIFT))
#पूर्ण_अगर
#घोषणा PGसूची_SIZE		(__IA64_UL(1) << PGसूची_SHIFT)
#घोषणा PGसूची_MASK		(~(PGसूची_SIZE-1))
#घोषणा PTRS_PER_PGD_SHIFT	PTRS_PER_PTD_SHIFT
#घोषणा PTRS_PER_PGD		(1UL << PTRS_PER_PGD_SHIFT)
#घोषणा USER_PTRS_PER_PGD	(5*PTRS_PER_PGD/8)	/* regions 0-4 are user regions */
#घोषणा FIRST_USER_ADDRESS	0UL

/*
 * All the normal masks have the "page accessed" bits on, as any समय
 * they are used, the page is accessed. They are cleared only by the
 * page-out routines.
 */
#घोषणा PAGE_NONE	__pgprot(_PAGE_PROTNONE | _PAGE_A)
#घोषणा PAGE_SHARED	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RW)
#घोषणा PAGE_READONLY	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_R)
#घोषणा PAGE_COPY	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_R)
#घोषणा PAGE_COPY_EXEC	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RX)
#घोषणा PAGE_GATE	__pgprot(__ACCESS_BITS | _PAGE_PL_0 | _PAGE_AR_X_RX)
#घोषणा PAGE_KERNEL	__pgprot(__सूचीTY_BITS  | _PAGE_PL_0 | _PAGE_AR_RWX)
#घोषणा PAGE_KERNELRX	__pgprot(__ACCESS_BITS | _PAGE_PL_0 | _PAGE_AR_RX)
#घोषणा PAGE_KERNEL_UC	__pgprot(__सूचीTY_BITS  | _PAGE_PL_0 | _PAGE_AR_RWX | \
				 _PAGE_MA_UC)

# अगरndef __ASSEMBLY__

#समावेश <linux/sched/mm.h>	/* क्रम mm_काष्ठा */
#समावेश <linux/bitops.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mmu_context.h>

/*
 * Next come the mappings that determine how mmap() protection bits
 * (PROT_EXEC, PROT_READ, PROT_WRITE, PROT_NONE) get implemented.  The
 * _P version माला_लो used क्रम a निजी shared memory segment, the _S
 * version माला_लो used क्रम a shared memory segment with MAP_SHARED on.
 * In a निजी shared memory segment, we करो a copy-on-ग_लिखो अगर a task
 * attempts to ग_लिखो to the page.
 */
	/* xwr */
#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READONLY
#घोषणा __P010	PAGE_READONLY	/* ग_लिखो to priv pg -> copy & make writable */
#घोषणा __P011	PAGE_READONLY	/* ditto */
#घोषणा __P100	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_X_RX)
#घोषणा __P101	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RX)
#घोषणा __P110	PAGE_COPY_EXEC
#घोषणा __P111	PAGE_COPY_EXEC

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READONLY
#घोषणा __S010	PAGE_SHARED	/* we करोn't have (and don't need) ग_लिखो-only */
#घोषणा __S011	PAGE_SHARED
#घोषणा __S100	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_X_RX)
#घोषणा __S101	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RX)
#घोषणा __S110	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RWX)
#घोषणा __S111	__pgprot(__ACCESS_BITS | _PAGE_PL_3 | _PAGE_AR_RWX)

#घोषणा pgd_ERROR(e)	prपूर्णांकk("%s:%d: bad pgd %016lx.\n", __खाता__, __LINE__, pgd_val(e))
#अगर CONFIG_PGTABLE_LEVELS == 4
#घोषणा pud_ERROR(e)	prपूर्णांकk("%s:%d: bad pud %016lx.\n", __खाता__, __LINE__, pud_val(e))
#पूर्ण_अगर
#घोषणा pmd_ERROR(e)	prपूर्णांकk("%s:%d: bad pmd %016lx.\n", __खाता__, __LINE__, pmd_val(e))
#घोषणा pte_ERROR(e)	prपूर्णांकk("%s:%d: bad pte %016lx.\n", __खाता__, __LINE__, pte_val(e))


/*
 * Some definitions to translate between mem_map, PTEs, and page addresses:
 */


/* Quick test to see अगर ADDR is a (potentially) valid physical address. */
अटल अंतरभूत दीर्घ
ia64_phys_addr_valid (अचिन्हित दीर्घ addr)
अणु
	वापस (addr & (local_cpu_data->unimpl_pa_mask)) == 0;
पूर्ण

/*
 * kern_addr_valid(ADDR) tests अगर ADDR is poपूर्णांकing to valid kernel
 * memory.  For the वापस value to be meaningful, ADDR must be >=
 * PAGE_OFFSET.  This operation can be relatively expensive (e.g.,
 * require a hash-, or multi-level tree-lookup or something of that
 * sort) but it guarantees to वापस TRUE only अगर accessing the page
 * at that address करोes not cause an error.  Note that there may be
 * addresses क्रम which kern_addr_valid() वापसs FALSE even though an
 * access would not cause an error (e.g., this is typically true क्रम
 * memory mapped I/O regions.
 *
 * XXX Need to implement this क्रम IA-64.
 */
#घोषणा kern_addr_valid(addr)	(1)


/*
 * Now come the defines and routines to manage and access the three-level
 * page table.
 */


#घोषणा VMALLOC_START		(RGN_BASE(RGN_GATE) + 0x200000000UL)
#अगर defined(CONFIG_SPARSEMEM) && defined(CONFIG_SPARSEMEM_VMEMMAP)
/* SPARSEMEM_VMEMMAP uses half of vदो_स्मृति... */
# define VMALLOC_END		(RGN_BASE(RGN_GATE) + (1UL << (4*PAGE_SHIFT - 10)))
# define vmemmap		((काष्ठा page *)VMALLOC_END)
#अन्यथा
# define VMALLOC_END		(RGN_BASE(RGN_GATE) + (1UL << (4*PAGE_SHIFT - 9)))
#पूर्ण_अगर

/* fs/proc/kcore.c */
#घोषणा	kc_vaddr_to_offset(v) ((v) - RGN_BASE(RGN_GATE))
#घोषणा	kc_offset_to_vaddr(o) ((o) + RGN_BASE(RGN_GATE))

#घोषणा RGN_MAP_SHIFT (PGसूची_SHIFT + PTRS_PER_PGD_SHIFT - 3)
#घोषणा RGN_MAP_LIMIT	((1UL << RGN_MAP_SHIFT) - PAGE_SIZE)	/* per region addr limit */

/*
 * Conversion functions: convert page frame number (pfn) and a protection value to a page
 * table entry (pte).
 */
#घोषणा pfn_pte(pfn, pgprot) \
(अणु pte_t __pte; pte_val(__pte) = ((pfn) << PAGE_SHIFT) | pgprot_val(pgprot); __pte; पूर्ण)

/* Extract pfn from pte.  */
#घोषणा pte_pfn(_pte)		((pte_val(_pte) & _PFN_MASK) >> PAGE_SHIFT)

#घोषणा mk_pte(page, pgprot)	pfn_pte(page_to_pfn(page), (pgprot))

/* This takes a physical page address that is used by the remapping functions */
#घोषणा mk_pte_phys(physpage, pgprot) \
(अणु pte_t __pte; pte_val(__pte) = physpage + pgprot_val(pgprot); __pte; पूर्ण)

#घोषणा pte_modअगरy(_pte, newprot) \
	(__pte((pte_val(_pte) & ~_PAGE_CHG_MASK) | (pgprot_val(newprot) & _PAGE_CHG_MASK)))

#घोषणा pte_none(pte) 			(!pte_val(pte))
#घोषणा pte_present(pte)		(pte_val(pte) & (_PAGE_P | _PAGE_PROTNONE))
#घोषणा pte_clear(mm,addr,pte)		(pte_val(*(pte)) = 0UL)
/* pte_page() वापसs the "struct page *" corresponding to the PTE: */
#घोषणा pte_page(pte)			virt_to_page(((pte_val(pte) & _PFN_MASK) + PAGE_OFFSET))

#घोषणा pmd_none(pmd)			(!pmd_val(pmd))
#घोषणा pmd_bad(pmd)			(!ia64_phys_addr_valid(pmd_val(pmd)))
#घोषणा pmd_present(pmd)		(pmd_val(pmd) != 0UL)
#घोषणा pmd_clear(pmdp)			(pmd_val(*(pmdp)) = 0UL)
#घोषणा pmd_page_vaddr(pmd)		((अचिन्हित दीर्घ) __va(pmd_val(pmd) & _PFN_MASK))
#घोषणा pmd_page(pmd)			virt_to_page((pmd_val(pmd) + PAGE_OFFSET))

#घोषणा pud_none(pud)			(!pud_val(pud))
#घोषणा pud_bad(pud)			(!ia64_phys_addr_valid(pud_val(pud)))
#घोषणा pud_present(pud)		(pud_val(pud) != 0UL)
#घोषणा pud_clear(pudp)			(pud_val(*(pudp)) = 0UL)
#घोषणा pud_page_vaddr(pud)		((अचिन्हित दीर्घ) __va(pud_val(pud) & _PFN_MASK))
#घोषणा pud_page(pud)			virt_to_page((pud_val(pud) + PAGE_OFFSET))

#अगर CONFIG_PGTABLE_LEVELS == 4
#घोषणा p4d_none(p4d)			(!p4d_val(p4d))
#घोषणा p4d_bad(p4d)			(!ia64_phys_addr_valid(p4d_val(p4d)))
#घोषणा p4d_present(p4d)		(p4d_val(p4d) != 0UL)
#घोषणा p4d_clear(p4dp)			(p4d_val(*(p4dp)) = 0UL)
#घोषणा p4d_page_vaddr(p4d)		((अचिन्हित दीर्घ) __va(p4d_val(p4d) & _PFN_MASK))
#घोषणा p4d_page(p4d)			virt_to_page((p4d_val(p4d) + PAGE_OFFSET))
#पूर्ण_अगर

/*
 * The following have defined behavior only work अगर pte_present() is true.
 */
#घोषणा pte_ग_लिखो(pte)	((अचिन्हित) (((pte_val(pte) & _PAGE_AR_MASK) >> _PAGE_AR_SHIFT) - 2) <= 4)
#घोषणा pte_exec(pte)		((pte_val(pte) & _PAGE_AR_RX) != 0)
#घोषणा pte_dirty(pte)		((pte_val(pte) & _PAGE_D) != 0)
#घोषणा pte_young(pte)		((pte_val(pte) & _PAGE_A) != 0)

/*
 * Note: we convert AR_RWX to AR_RX and AR_RW to AR_R by clearing the 2nd bit in the
 * access rights:
 */
#घोषणा pte_wrprotect(pte)	(__pte(pte_val(pte) & ~_PAGE_AR_RW))
#घोषणा pte_mkग_लिखो(pte)	(__pte(pte_val(pte) | _PAGE_AR_RW))
#घोषणा pte_mkold(pte)		(__pte(pte_val(pte) & ~_PAGE_A))
#घोषणा pte_mkyoung(pte)	(__pte(pte_val(pte) | _PAGE_A))
#घोषणा pte_mkclean(pte)	(__pte(pte_val(pte) & ~_PAGE_D))
#घोषणा pte_सूची_गढ़ोty(pte)	(__pte(pte_val(pte) | _PAGE_D))
#घोषणा pte_mkhuge(pte)		(__pte(pte_val(pte)))

/*
 * Because ia64's Icache and Dcache is not coherent (on a cpu), we need to
 * sync icache and dcache when we insert *new* executable page.
 *  __ia64_sync_icache_dcache() check Pg_arch_1 bit and flush icache
 * अगर necessary.
 *
 *  set_pte() is also called by the kernel, but we can expect that the kernel
 *  flushes icache explicitly अगर necessary.
 */
#घोषणा pte_present_exec_user(pte)\
	((pte_val(pte) & (_PAGE_P | _PAGE_PL_MASK | _PAGE_AR_RX)) == \
		(_PAGE_P | _PAGE_PL_3 | _PAGE_AR_RX))

बाह्य व्योम __ia64_sync_icache_dcache(pte_t pteval);
अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pteval)
अणु
	/* page is present && page is user  && page is executable
	 * && (page swapin or new page or page migration
	 *	|| copy_on_ग_लिखो with page copying.)
	 */
	अगर (pte_present_exec_user(pteval) &&
	    (!pte_present(*ptep) ||
		pte_pfn(*ptep) != pte_pfn(pteval)))
		/* load_module() calles flush_icache_range() explicitly*/
		__ia64_sync_icache_dcache(pteval);
	*ptep = pteval;
पूर्ण

#घोषणा set_pte_at(mm,addr,ptep,pteval) set_pte(ptep,pteval)

/*
 * Make page protection values cacheable, uncacheable, or ग_लिखो-
 * combining.  Note that "protection" is really a misnomer here as the
 * protection value contains the memory attribute bits, dirty bits, and
 * various other bits as well.
 */
#घोषणा pgprot_cacheable(prot)		__pgprot((pgprot_val(prot) & ~_PAGE_MA_MASK) | _PAGE_MA_WB)
#घोषणा pgprot_noncached(prot)		__pgprot((pgprot_val(prot) & ~_PAGE_MA_MASK) | _PAGE_MA_UC)
#घोषणा pgprot_ग_लिखोcombine(prot)	__pgprot((pgprot_val(prot) & ~_PAGE_MA_MASK) | _PAGE_MA_WC)

काष्ठा file;
बाह्य pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t vma_prot);
#घोषणा __HAVE_PHYS_MEM_ACCESS_PROT

अटल अंतरभूत अचिन्हित दीर्घ
pgd_index (अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ region = address >> 61;
	अचिन्हित दीर्घ l1index = (address >> PGसूची_SHIFT) & ((PTRS_PER_PGD >> 3) - 1);

	वापस (region << (PAGE_SHIFT - 6)) | l1index;
पूर्ण
#घोषणा pgd_index pgd_index

/*
 * In the kernel's mapped region we know everything is in region number 5, so
 * as an optimisation its PGD alपढ़ोy poपूर्णांकs to the area क्रम that region.
 * However, this also means that we cannot use pgd_index() and we must
 * never add the region here.
 */
#घोषणा pgd_offset_k(addr) \
	(init_mm.pgd + (((addr) >> PGसूची_SHIFT) & (PTRS_PER_PGD - 1)))

/* Look up a pgd entry in the gate area.  On IA-64, the gate-area
   resides in the kernel-mapped segment, hence we use pgd_offset_k()
   here.  */
#घोषणा pgd_offset_gate(mm, addr)	pgd_offset_k(addr)

/* atomic versions of the some PTE manipulations: */

अटल अंतरभूत पूर्णांक
ptep_test_and_clear_young (काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (!pte_young(*ptep))
		वापस 0;
	वापस test_and_clear_bit(_PAGE_A_BIT, ptep);
#अन्यथा
	pte_t pte = *ptep;
	अगर (!pte_young(pte))
		वापस 0;
	set_pte_at(vma->vm_mm, addr, ptep, pte_mkold(pte));
	वापस 1;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत pte_t
ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
#अगर_घोषित CONFIG_SMP
	वापस __pte(xchg((दीर्घ *) ptep, 0));
#अन्यथा
	pte_t pte = *ptep;
	pte_clear(mm, addr, ptep);
	वापस pte;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम
ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ new, old;

	करो अणु
		old = pte_val(*ptep);
		new = pte_val(pte_wrprotect(__pte (old)));
	पूर्ण जबतक (cmpxchg((अचिन्हित दीर्घ *) ptep, old, new) != old);
#अन्यथा
	pte_t old_pte = *ptep;
	set_pte_at(mm, addr, ptep, pte_wrprotect(old_pte));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक
pte_same (pte_t a, pte_t b)
अणु
	वापस pte_val(a) == pte_val(b);
पूर्ण

#घोषणा update_mmu_cache(vma, address, ptep) करो अणु पूर्ण जबतक (0)

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];
बाह्य व्योम paging_init (व्योम);

/*
 * Note: The macros below rely on the fact that MAX_SWAPखाताS_SHIFT <= number of
 *	 bits in the swap-type field of the swap pte.  It would be nice to
 *	 enक्रमce that, but we can't easily include <linux/swap.h> here.
 *	 (Of course, better still would be to define MAX_SWAPखाताS_SHIFT here...).
 *
 * Format of swap pte:
 *	bit   0   : present bit (must be zero)
 *	bits  1- 7: swap-type
 *	bits  8-62: swap offset
 *	bit  63   : _PAGE_PROTNONE bit
 */
#घोषणा __swp_type(entry)		(((entry).val >> 1) & 0x7f)
#घोषणा __swp_offset(entry)		(((entry).val << 1) >> 9)
#घोषणा __swp_entry(type,offset)	((swp_entry_t) अणु ((type) << 1) | ((दीर्घ) (offset) << 8) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val पूर्ण)

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE/माप(अचिन्हित दीर्घ)];
बाह्य काष्ठा page *zero_page_memmap_ptr;
#घोषणा ZERO_PAGE(vaddr) (zero_page_memmap_ptr)

/* We provide our own get_unmapped_area to cope with VA holes क्रम userland */
#घोषणा HAVE_ARCH_UNMAPPED_AREA

#अगर_घोषित CONFIG_HUGETLB_PAGE
#घोषणा HUGETLB_PGसूची_SHIFT	(HPAGE_SHIFT + 2*(PAGE_SHIFT-3))
#घोषणा HUGETLB_PGसूची_SIZE	(__IA64_UL(1) << HUGETLB_PGसूची_SHIFT)
#घोषणा HUGETLB_PGसूची_MASK	(~(HUGETLB_PGसूची_SIZE-1))
#पूर्ण_अगर


#घोषणा __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
/*
 * Update PTEP with ENTRY, which is guaranteed to be a less
 * restrictive PTE.  That is, ENTRY may have the ACCESSED, सूचीTY, and
 * WRITABLE bits turned on, when the value at PTEP did not.  The
 * WRITABLE bit may only be turned अगर SAFELY_WRITABLE is TRUE.
 *
 * SAFELY_WRITABLE is TRUE अगर we can update the value at PTEP without
 * having to worry about races.  On SMP machines, there are only two
 * हालs where this is true:
 *
 *	(1) *PTEP has the PRESENT bit turned OFF
 *	(2) ENTRY has the सूचीTY bit turned ON
 *
 * On ia64, we could implement this routine with a cmpxchg()-loop
 * which ORs in the _PAGE_A/_PAGE_D bit अगर they're set in ENTRY.
 * However, like on x86, we can get a more streamlined version by
 * observing that it is OK to drop ACCESSED bit updates when
 * SAFELY_WRITABLE is FALSE.  Besides being rare, all that would करो is
 * result in an extra Access-bit fault, which would then turn on the
 * ACCESSED bit in the low-level fault handler (iaccess_bit or
 * daccess_bit in ivt.S).
 */
#अगर_घोषित CONFIG_SMP
# define ptep_set_access_flags(__vma, __addr, __ptep, __entry, __safely_writable) \
(अणु									\
	पूर्णांक __changed = !pte_same(*(__ptep), __entry);			\
	अगर (__changed && __safely_writable) अणु				\
		set_pte(__ptep, __entry);				\
		flush_tlb_page(__vma, __addr);				\
	पूर्ण								\
	__changed;							\
पूर्ण)
#अन्यथा
# define ptep_set_access_flags(__vma, __addr, __ptep, __entry, __safely_writable) \
(अणु									\
	पूर्णांक __changed = !pte_same(*(__ptep), __entry);			\
	अगर (__changed) अणु						\
		set_pte_at((__vma)->vm_mm, (__addr), __ptep, __entry);	\
		flush_tlb_page(__vma, __addr);				\
	पूर्ण								\
	__changed;							\
पूर्ण)
#पूर्ण_अगर
# endअगर /* !__ASSEMBLY__ */

/*
 * Identity-mapped regions use a large page size.  We'll call such large pages
 * "granules".  If you can think of a better name that's unambiguous, let me
 * know...
 */
#अगर defined(CONFIG_IA64_GRANULE_64MB)
# define IA64_GRANULE_SHIFT	_PAGE_SIZE_64M
#या_अगर defined(CONFIG_IA64_GRANULE_16MB)
# define IA64_GRANULE_SHIFT	_PAGE_SIZE_16M
#पूर्ण_अगर
#घोषणा IA64_GRANULE_SIZE	(1 << IA64_GRANULE_SHIFT)
/*
 * log2() of the page size we use to map the kernel image (IA64_TR_KERNEL):
 */
#घोषणा KERNEL_TR_PAGE_SHIFT	_PAGE_SIZE_64M
#घोषणा KERNEL_TR_PAGE_SIZE	(1 << KERNEL_TR_PAGE_SHIFT)

/* These tell get_user_pages() that the first gate page is accessible from user-level.  */
#घोषणा FIXADDR_USER_START	GATE_ADDR
#अगर_घोषित HAVE_BUGGY_SEGREL
# define FIXADDR_USER_END	(GATE_ADDR + 2*PAGE_SIZE)
#अन्यथा
# define FIXADDR_USER_END	(GATE_ADDR + 2*PERCPU_PAGE_SIZE)
#पूर्ण_अगर

#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
#घोषणा __HAVE_ARCH_PTE_SAME
#घोषणा __HAVE_ARCH_PGD_OFFSET_GATE


#अगर CONFIG_PGTABLE_LEVELS == 3
#समावेश <यंत्र-generic/pgtable-nopud.h>
#पूर्ण_अगर
#समावेश <यंत्र-generic/pgtable-nop4d.h>

#पूर्ण_अगर /* _ASM_IA64_PGTABLE_H */
