<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_PGTABLE_H
#घोषणा _PARISC_PGTABLE_H

#समावेश <यंत्र/page.h>

#अगर CONFIG_PGTABLE_LEVELS == 3
#समावेश <यंत्र-generic/pgtable-nopud.h>
#या_अगर CONFIG_PGTABLE_LEVELS == 2
#समावेश <यंत्र-generic/pgtable-nopmd.h>
#पूर्ण_अगर

#समावेश <यंत्र/fixmap.h>

#अगर_अघोषित __ASSEMBLY__
/*
 * we simulate an x86-style page table क्रम the linux mm code
 */

#समावेश <linux/bitops.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm_types.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cache.h>

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
 * XXX Need to implement this क्रम parisc.
 */
#घोषणा kern_addr_valid(addr)	(1)

/* This is क्रम the serialization of PxTLB broadcasts. At least on the N class
 * प्रणालीs, only one PxTLB पूर्णांकer processor broadcast can be active at any one
 * समय on the Merced bus. */
बाह्य spinlock_t pa_tlb_flush_lock;
#अगर defined(CONFIG_64BIT) && defined(CONFIG_SMP)
बाह्य पूर्णांक pa_serialize_tlb_flushes;
#अन्यथा
#घोषणा pa_serialize_tlb_flushes        (0)
#पूर्ण_अगर

#घोषणा purge_tlb_start(flags)  करो अणु \
	अगर (pa_serialize_tlb_flushes)	\
		spin_lock_irqsave(&pa_tlb_flush_lock, flags); \
	अन्यथा \
		local_irq_save(flags);	\
	पूर्ण जबतक (0)
#घोषणा purge_tlb_end(flags)	करो अणु \
	अगर (pa_serialize_tlb_flushes)	\
		spin_unlock_irqrestore(&pa_tlb_flush_lock, flags); \
	अन्यथा \
		local_irq_restore(flags); \
	पूर्ण जबतक (0)

/* Purge data and inकाष्ठाion TLB entries. The TLB purge inकाष्ठाions
 * are slow on SMP machines since the purge must be broadcast to all CPUs.
 */

अटल अंतरभूत व्योम purge_tlb_entries(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ flags;

	purge_tlb_start(flags);
	mtsp(mm->context, 1);
	pdtlb(addr);
	pitlb(addr);
	purge_tlb_end(flags);
पूर्ण

/* Certain architectures need to करो special things when PTEs
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */
#घोषणा set_pte(pteptr, pteval)			\
	करो अणु					\
		*(pteptr) = (pteval);		\
		barrier();			\
	पूर्ण जबतक(0)

#घोषणा set_pte_at(mm, addr, pteptr, pteval)	\
	करो अणु					\
		*(pteptr) = (pteval);		\
		purge_tlb_entries(mm, addr);	\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, pte_val(e))
#अगर CONFIG_PGTABLE_LEVELS == 3
#घोषणा pmd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pmd %08lx.\n", __खाता__, __LINE__, (अचिन्हित दीर्घ)pmd_val(e))
#पूर्ण_अगर
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, (अचिन्हित दीर्घ)pgd_val(e))

/* This is the size of the initially mapped kernel memory */
#अगर defined(CONFIG_64BIT)
#घोषणा KERNEL_INITIAL_ORDER	26	/* 1<<26 = 64MB */
#अन्यथा
#घोषणा KERNEL_INITIAL_ORDER	25	/* 1<<25 = 32MB */
#पूर्ण_अगर
#घोषणा KERNEL_INITIAL_SIZE	(1 << KERNEL_INITIAL_ORDER)

#अगर CONFIG_PGTABLE_LEVELS == 3
#घोषणा PMD_ORDER	1
#घोषणा PGD_ORDER	0
#अन्यथा
#घोषणा PGD_ORDER	1
#पूर्ण_अगर

/* Definitions क्रम 3rd level (we use PLD here क्रम Page Lower directory
 * because PTE_SHIFT is used lower करोwn to mean shअगरt that has to be
 * करोne to get usable bits out of the PTE) */
#घोषणा PLD_SHIFT	PAGE_SHIFT
#घोषणा PLD_SIZE	PAGE_SIZE
#घोषणा BITS_PER_PTE	(PAGE_SHIFT - BITS_PER_PTE_ENTRY)
#घोषणा PTRS_PER_PTE    (1UL << BITS_PER_PTE)

/* Definitions क्रम 2nd level */
#अगर CONFIG_PGTABLE_LEVELS == 3
#घोषणा PMD_SHIFT       (PLD_SHIFT + BITS_PER_PTE)
#घोषणा PMD_SIZE	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))
#घोषणा BITS_PER_PMD	(PAGE_SHIFT + PMD_ORDER - BITS_PER_PMD_ENTRY)
#घोषणा PTRS_PER_PMD    (1UL << BITS_PER_PMD)
#अन्यथा
#घोषणा BITS_PER_PMD	0
#पूर्ण_अगर

/* Definitions क्रम 1st level */
#घोषणा PGसूची_SHIFT	(PLD_SHIFT + BITS_PER_PTE + BITS_PER_PMD)
#अगर (PGसूची_SHIFT + PAGE_SHIFT + PGD_ORDER - BITS_PER_PGD_ENTRY) > BITS_PER_LONG
#घोषणा BITS_PER_PGD	(BITS_PER_LONG - PGसूची_SHIFT)
#अन्यथा
#घोषणा BITS_PER_PGD	(PAGE_SHIFT + PGD_ORDER - BITS_PER_PGD_ENTRY)
#पूर्ण_अगर
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))
#घोषणा PTRS_PER_PGD    (1UL << BITS_PER_PGD)
#घोषणा USER_PTRS_PER_PGD       PTRS_PER_PGD

#अगर_घोषित CONFIG_64BIT
#घोषणा MAX_ADDRBITS	(PGसूची_SHIFT + BITS_PER_PGD)
#घोषणा MAX_ADDRESS	(1UL << MAX_ADDRBITS)
#घोषणा SPACEID_SHIFT	(MAX_ADDRBITS - 32)
#अन्यथा
#घोषणा MAX_ADDRBITS	(BITS_PER_LONG)
#घोषणा MAX_ADDRESS	(1UL << MAX_ADDRBITS)
#घोषणा SPACEID_SHIFT	0
#पूर्ण_अगर

/* This calculates the number of initial pages we need क्रम the initial
 * page tables */
#अगर (KERNEL_INITIAL_ORDER) >= (PMD_SHIFT)
# define PT_INITIAL	(1 << (KERNEL_INITIAL_ORDER - PMD_SHIFT))
#अन्यथा
# define PT_INITIAL	(1)  /* all initial PTEs fit पूर्णांकo one page */
#पूर्ण_अगर

/*
 * pgd entries used up by user/kernel:
 */

#घोषणा FIRST_USER_ADDRESS	0UL

/* NB: The tlb miss handlers make certain assumptions about the order */
/*     of the following bits, so be careful (One example, bits 25-31  */
/*     are moved together in one inकाष्ठाion).                        */

#घोषणा _PAGE_READ_BIT     31   /* (0x001) पढ़ो access allowed */
#घोषणा _PAGE_WRITE_BIT    30   /* (0x002) ग_लिखो access allowed */
#घोषणा _PAGE_EXEC_BIT     29   /* (0x004) execute access allowed */
#घोषणा _PAGE_GATEWAY_BIT  28   /* (0x008) privilege promotion allowed */
#घोषणा _PAGE_DMB_BIT      27   /* (0x010) Data Memory Break enable (B bit) */
#घोषणा _PAGE_सूचीTY_BIT    26   /* (0x020) Page Dirty (D bit) */
#घोषणा _PAGE_REFTRAP_BIT  25   /* (0x040) Page Ref. Trap enable (T bit) */
#घोषणा _PAGE_NO_CACHE_BIT 24   /* (0x080) Uncached Page (U bit) */
#घोषणा _PAGE_ACCESSED_BIT 23   /* (0x100) Software: Page Accessed */
#घोषणा _PAGE_PRESENT_BIT  22   /* (0x200) Software: translation valid */
#घोषणा _PAGE_HPAGE_BIT    21   /* (0x400) Software: Huge Page */
#घोषणा _PAGE_USER_BIT     20   /* (0x800) Software: User accessible page */

/* N.B. The bits are defined in terms of a 32 bit word above, so the */
/*      following macro is ok क्रम both 32 and 64 bit.                */

#घोषणा xlate_pabit(x) (31 - x)

/* this defines the shअगरt to the usable bits in the PTE it is set so
 * that the valid bits _PAGE_PRESENT_BIT and _PAGE_USER_BIT are set
 * to zero */
#घोषणा PTE_SHIFT	   	xlate_pabit(_PAGE_USER_BIT)

/* PFN_PTE_SHIFT defines the shअगरt of a PTE value to access the PFN field */
#घोषणा PFN_PTE_SHIFT		12

#घोषणा _PAGE_READ     (1 << xlate_pabit(_PAGE_READ_BIT))
#घोषणा _PAGE_WRITE    (1 << xlate_pabit(_PAGE_WRITE_BIT))
#घोषणा _PAGE_RW       (_PAGE_READ | _PAGE_WRITE)
#घोषणा _PAGE_EXEC     (1 << xlate_pabit(_PAGE_EXEC_BIT))
#घोषणा _PAGE_GATEWAY  (1 << xlate_pabit(_PAGE_GATEWAY_BIT))
#घोषणा _PAGE_DMB      (1 << xlate_pabit(_PAGE_DMB_BIT))
#घोषणा _PAGE_सूचीTY    (1 << xlate_pabit(_PAGE_सूचीTY_BIT))
#घोषणा _PAGE_REFTRAP  (1 << xlate_pabit(_PAGE_REFTRAP_BIT))
#घोषणा _PAGE_NO_CACHE (1 << xlate_pabit(_PAGE_NO_CACHE_BIT))
#घोषणा _PAGE_ACCESSED (1 << xlate_pabit(_PAGE_ACCESSED_BIT))
#घोषणा _PAGE_PRESENT  (1 << xlate_pabit(_PAGE_PRESENT_BIT))
#घोषणा _PAGE_HUGE     (1 << xlate_pabit(_PAGE_HPAGE_BIT))
#घोषणा _PAGE_USER     (1 << xlate_pabit(_PAGE_USER_BIT))

#घोषणा _PAGE_TABLE	(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | _PAGE_सूचीTY | _PAGE_ACCESSED)
#घोषणा _PAGE_CHG_MASK	(PAGE_MASK | _PAGE_ACCESSED | _PAGE_सूचीTY)
#घोषणा _PAGE_KERNEL_RO	(_PAGE_PRESENT | _PAGE_READ | _PAGE_सूचीTY | _PAGE_ACCESSED)
#घोषणा _PAGE_KERNEL_EXEC	(_PAGE_KERNEL_RO | _PAGE_EXEC)
#घोषणा _PAGE_KERNEL_RWX	(_PAGE_KERNEL_EXEC | _PAGE_WRITE)
#घोषणा _PAGE_KERNEL		(_PAGE_KERNEL_RO | _PAGE_WRITE)

/* The pgd/pmd contains a ptr (in phys addr space); since all pgds/pmds
 * are page-aligned, we करोn't care about the PAGE_OFFSET bits, except
 * क्रम a few meta-inक्रमmation bits, so we shअगरt the address to be
 * able to effectively address 40/42/44-bits of physical address space
 * depending on 4k/16k/64k PAGE_SIZE */
#घोषणा _PxD_PRESENT_BIT   31
#घोषणा _PxD_VALID_BIT     30

#घोषणा PxD_FLAG_PRESENT  (1 << xlate_pabit(_PxD_PRESENT_BIT))
#घोषणा PxD_FLAG_VALID    (1 << xlate_pabit(_PxD_VALID_BIT))
#घोषणा PxD_FLAG_MASK     (0xf)
#घोषणा PxD_FLAG_SHIFT    (4)
#घोषणा PxD_VALUE_SHIFT   (PFN_PTE_SHIFT-PxD_FLAG_SHIFT)

#अगर_अघोषित __ASSEMBLY__

#घोषणा PAGE_NONE	__pgprot(_PAGE_PRESENT | _PAGE_USER)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | _PAGE_WRITE)
/* Others seem to make this executable, I करोn't know if that's correct
   or not.  The stack is mapped this way though so this is necessary
   in the लघु term - dhd@linuxcare.com, 2000-08-08 */
#घोषणा PAGE_READONLY	__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ)
#घोषणा PAGE_WRITEONLY  __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_WRITE)
#घोषणा PAGE_EXECREAD   __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | _PAGE_EXEC)
#घोषणा PAGE_COPY       PAGE_EXECREAD
#घोषणा PAGE_RWX        __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_READ | _PAGE_WRITE | _PAGE_EXEC)
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_KERNEL)
#घोषणा PAGE_KERNEL_EXEC	__pgprot(_PAGE_KERNEL_EXEC)
#घोषणा PAGE_KERNEL_RWX	__pgprot(_PAGE_KERNEL_RWX)
#घोषणा PAGE_KERNEL_RO	__pgprot(_PAGE_KERNEL_RO)
#घोषणा PAGE_KERNEL_UNC	__pgprot(_PAGE_KERNEL | _PAGE_NO_CACHE)
#घोषणा PAGE_GATEWAY    __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_GATEWAY| _PAGE_READ)


/*
 * We could have an execute only page using "gateway - promote to priv
 * level 3", but that is kind of silly. So, the way things are defined
 * now, we must always have पढ़ो permission क्रम pages with execute
 * permission. For the fun of it we'll go ahead and support ग_लिखो only
 * pages.
 */

	 /*xwr*/
#घोषणा __P000  PAGE_NONE
#घोषणा __P001  PAGE_READONLY
#घोषणा __P010  __P000 /* copy on ग_लिखो */
#घोषणा __P011  __P001 /* copy on ग_लिखो */
#घोषणा __P100  PAGE_EXECREAD
#घोषणा __P101  PAGE_EXECREAD
#घोषणा __P110  __P100 /* copy on ग_लिखो */
#घोषणा __P111  __P101 /* copy on ग_लिखो */

#घोषणा __S000  PAGE_NONE
#घोषणा __S001  PAGE_READONLY
#घोषणा __S010  PAGE_WRITEONLY
#घोषणा __S011  PAGE_SHARED
#घोषणा __S100  PAGE_EXECREAD
#घोषणा __S101  PAGE_EXECREAD
#घोषणा __S110  PAGE_RWX
#घोषणा __S111  PAGE_RWX


बाह्य pgd_t swapper_pg_dir[]; /* declared in init_task.c */

/* initial page tables क्रम 0-8MB क्रम kernel */

बाह्य pte_t pg0[];

/* zero page used क्रम uninitialized stuff */

बाह्य अचिन्हित दीर्घ *empty_zero_page;

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */

#घोषणा ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))

#घोषणा pte_none(x)     (pte_val(x) == 0)
#घोषणा pte_present(x)	(pte_val(x) & _PAGE_PRESENT)
#घोषणा pte_clear(mm, addr, xp)  set_pte_at(mm, addr, xp, __pte(0))

#घोषणा pmd_flag(x)	(pmd_val(x) & PxD_FLAG_MASK)
#घोषणा pmd_address(x)	((अचिन्हित दीर्घ)(pmd_val(x) &~ PxD_FLAG_MASK) << PxD_VALUE_SHIFT)
#घोषणा pud_flag(x)	(pud_val(x) & PxD_FLAG_MASK)
#घोषणा pud_address(x)	((अचिन्हित दीर्घ)(pud_val(x) &~ PxD_FLAG_MASK) << PxD_VALUE_SHIFT)
#घोषणा pgd_flag(x)	(pgd_val(x) & PxD_FLAG_MASK)
#घोषणा pgd_address(x)	((अचिन्हित दीर्घ)(pgd_val(x) &~ PxD_FLAG_MASK) << PxD_VALUE_SHIFT)

#घोषणा pmd_none(x)	(!pmd_val(x))
#घोषणा pmd_bad(x)	(!(pmd_flag(x) & PxD_FLAG_VALID))
#घोषणा pmd_present(x)	(pmd_flag(x) & PxD_FLAG_PRESENT)
अटल अंतरभूत व्योम pmd_clear(pmd_t *pmd) अणु
		set_pmd(pmd,  __pmd(0));
पूर्ण



#अगर CONFIG_PGTABLE_LEVELS == 3
#घोषणा pud_page_vaddr(pud) ((अचिन्हित दीर्घ) __va(pud_address(pud)))
#घोषणा pud_page(pud)	virt_to_page((व्योम *)pud_page_vaddr(pud))

/* For 64 bit we have three level tables */

#घोषणा pud_none(x)     (!pud_val(x))
#घोषणा pud_bad(x)      (!(pud_flag(x) & PxD_FLAG_VALID))
#घोषणा pud_present(x)  (pud_flag(x) & PxD_FLAG_PRESENT)
अटल अंतरभूत व्योम pud_clear(pud_t *pud) अणु
	set_pud(pud, __pud(0));
पूर्ण
#पूर्ण_अगर

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_सूचीTY; पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_ACCESSED; पूर्ण
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_WRITE; पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)	अणु pte_val(pte) &= ~_PAGE_सूचीTY; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkold(pte_t pte)	अणु pte_val(pte) &= ~_PAGE_ACCESSED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)	अणु pte_val(pte) &= ~_PAGE_WRITE; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)	अणु pte_val(pte) |= _PAGE_सूचीTY; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)	अणु pte_val(pte) |= _PAGE_ACCESSED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)	अणु pte_val(pte) |= _PAGE_WRITE; वापस pte; पूर्ण

/*
 * Huge pte definitions.
 */
#अगर_घोषित CONFIG_HUGETLB_PAGE
#घोषणा pte_huge(pte)           (pte_val(pte) & _PAGE_HUGE)
#घोषणा pte_mkhuge(pte)         (__pte(pte_val(pte) | \
				 (parisc_requires_coherency() ? 0 : _PAGE_HUGE)))
#अन्यथा
#घोषणा pte_huge(pte)           (0)
#घोषणा pte_mkhuge(pte)         (pte)
#पूर्ण_अगर


/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा __mk_pte(addr,pgprot) \
(अणु									\
	pte_t __pte;							\
									\
	pte_val(__pte) = ((((addr)>>PAGE_SHIFT)<<PFN_PTE_SHIFT) + pgprot_val(pgprot));	\
									\
	__pte;								\
पूर्ण)

#घोषणा mk_pte(page, pgprot)	pfn_pte(page_to_pfn(page), (pgprot))

अटल अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ pfn, pgprot_t pgprot)
अणु
	pte_t pte;
	pte_val(pte) = (pfn << PFN_PTE_SHIFT) | pgprot_val(pgprot);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु pte_val(pte) = (pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot); वापस pte; पूर्ण

/* Permanent address of a page.  On parisc we करोn't have highmem. */

#घोषणा pte_pfn(x)		(pte_val(x) >> PFN_PTE_SHIFT)

#घोषणा pte_page(pte)		(pfn_to_page(pte_pfn(pte)))

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस ((अचिन्हित दीर्घ) __va(pmd_address(pmd)));
पूर्ण

#घोषणा __pmd_page(pmd) ((अचिन्हित दीर्घ) __va(pmd_address(pmd)))
#घोषणा pmd_page(pmd)	virt_to_page((व्योम *)__pmd_page(pmd))

/* Find an entry in the second-level page table.. */

बाह्य व्योम paging_init (व्योम);

/* Used क्रम deferring calls to flush_dcache_page() */

#घोषणा PG_dcache_dirty         PG_arch_1

बाह्य व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ, pte_t *);

/* Encode and de-code a swap entry */

#घोषणा __swp_type(x)                     ((x).val & 0x1f)
#घोषणा __swp_offset(x)                   ( (((x).val >> 6) &  0x7) | \
					  (((x).val >> 8) & ~0x7) )
#घोषणा __swp_entry(type, offset)         ((swp_entry_t) अणु (type) | \
					    ((offset &  0x7) << 6) | \
					    ((offset & ~0x7) << 8) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val पूर्ण)

अटल अंतरभूत पूर्णांक ptep_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t pte;

	अगर (!pte_young(*ptep))
		वापस 0;

	pte = *ptep;
	अगर (!pte_young(pte)) अणु
		वापस 0;
	पूर्ण
	set_pte_at(vma->vm_mm, addr, ptep, pte_mkold(pte));
	वापस 1;
पूर्ण

काष्ठा mm_काष्ठा;
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t old_pte;

	old_pte = *ptep;
	set_pte_at(mm, addr, ptep, __pte(0));

	वापस old_pte;
पूर्ण

अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	set_pte_at(mm, addr, ptep, pte_wrprotect(*ptep));
पूर्ण

#घोषणा pte_same(A,B)	(pte_val(A) == pte_val(B))

काष्ठा seq_file;
बाह्य व्योम arch_report_meminfo(काष्ठा seq_file *m);

#पूर्ण_अगर /* !__ASSEMBLY__ */


/* TLB page size encoding - see table 3-1 in parisc20.pdf */
#घोषणा _PAGE_SIZE_ENCODING_4K		0
#घोषणा _PAGE_SIZE_ENCODING_16K		1
#घोषणा _PAGE_SIZE_ENCODING_64K		2
#घोषणा _PAGE_SIZE_ENCODING_256K	3
#घोषणा _PAGE_SIZE_ENCODING_1M		4
#घोषणा _PAGE_SIZE_ENCODING_4M		5
#घोषणा _PAGE_SIZE_ENCODING_16M		6
#घोषणा _PAGE_SIZE_ENCODING_64M		7

#अगर defined(CONFIG_PARISC_PAGE_SIZE_4KB)
# define _PAGE_SIZE_ENCODING_DEFAULT _PAGE_SIZE_ENCODING_4K
#या_अगर defined(CONFIG_PARISC_PAGE_SIZE_16KB)
# define _PAGE_SIZE_ENCODING_DEFAULT _PAGE_SIZE_ENCODING_16K
#या_अगर defined(CONFIG_PARISC_PAGE_SIZE_64KB)
# define _PAGE_SIZE_ENCODING_DEFAULT _PAGE_SIZE_ENCODING_64K
#पूर्ण_अगर


#घोषणा pgprot_noncached(prot) __pgprot(pgprot_val(prot) | _PAGE_NO_CACHE)

/* We provide our own get_unmapped_area to provide cache coherency */

#घोषणा HAVE_ARCH_UNMAPPED_AREA
#घोषणा HAVE_ARCH_UNMAPPED_AREA_TOPDOWN

#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
#घोषणा __HAVE_ARCH_PTE_SAME

#पूर्ण_अगर /* _PARISC_PGTABLE_H */
