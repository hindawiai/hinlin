<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_PGTABLE_H
#घोषणा _ALPHA_PGTABLE_H

#समावेश <यंत्र-generic/pgtable-nopud.h>

/*
 * This file contains the functions and defines necessary to modअगरy and use
 * the Alpha page table tree.
 *
 * This hopefully works with any standard Alpha page-size, as defined
 * in <यंत्र/page.h> (currently 8192).
 */
#समावेश <linux/mmzone.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>	/* For TASK_SIZE */
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/setup.h>

काष्ठा mm_काष्ठा;
काष्ठा vm_area_काष्ठा;

/* Certain architectures need to करो special things when PTEs
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */
#घोषणा set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
#घोषणा set_pte_at(mm,addr,ptep,pteval) set_pte(ptep,pteval)

/* PMD_SHIFT determines the size of the area a second-level page table can map */
#घोषणा PMD_SHIFT	(PAGE_SHIFT + (PAGE_SHIFT-3))
#घोषणा PMD_SIZE	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))

/* PGसूची_SHIFT determines what a third-level page table entry can map */
#घोषणा PGसूची_SHIFT	(PAGE_SHIFT + 2*(PAGE_SHIFT-3))
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/*
 * Entries per page directory level:  the Alpha is three-level, with
 * all levels having a one-page page table.
 */
#घोषणा PTRS_PER_PTE	(1UL << (PAGE_SHIFT-3))
#घोषणा PTRS_PER_PMD	(1UL << (PAGE_SHIFT-3))
#घोषणा PTRS_PER_PGD	(1UL << (PAGE_SHIFT-3))
#घोषणा USER_PTRS_PER_PGD	(TASK_SIZE / PGसूची_SIZE)
#घोषणा FIRST_USER_ADDRESS	0UL

/* Number of poपूर्णांकers that fit on a page:  this will go away. */
#घोषणा PTRS_PER_PAGE	(1UL << (PAGE_SHIFT-3))

#अगर_घोषित CONFIG_ALPHA_LARGE_VMALLOC
#घोषणा VMALLOC_START		0xfffffe0000000000
#अन्यथा
#घोषणा VMALLOC_START		(-2*PGसूची_SIZE)
#पूर्ण_अगर
#घोषणा VMALLOC_END		(-PGसूची_SIZE)

/*
 * OSF/1 PAL-code-imposed page table bits
 */
#घोषणा _PAGE_VALID	0x0001
#घोषणा _PAGE_FOR	0x0002	/* used क्रम page protection (fault on पढ़ो) */
#घोषणा _PAGE_FOW	0x0004	/* used क्रम page protection (fault on ग_लिखो) */
#घोषणा _PAGE_FOE	0x0008	/* used क्रम page protection (fault on exec) */
#घोषणा _PAGE_ASM	0x0010
#घोषणा _PAGE_KRE	0x0100	/* xxx - see below on the "accessed" bit */
#घोषणा _PAGE_URE	0x0200	/* xxx */
#घोषणा _PAGE_KWE	0x1000	/* used to करो the dirty bit in software */
#घोषणा _PAGE_UWE	0x2000	/* used to करो the dirty bit in software */

/* .. and these are ours ... */
#घोषणा _PAGE_सूचीTY	0x20000
#घोषणा _PAGE_ACCESSED	0x40000

/*
 * NOTE! The "accessed" bit isn't necessarily exact:  it can be kept exactly
 * by software (use the KRE/URE/KWE/UWE bits appropriately), but I'll fake it.
 * Under Linux/AXP, the "accessed" bit just means "read", and I'll just use
 * the KRE/URE bits to watch क्रम it. That way we करोn't need to overload the
 * KWE/UWE bits with both handling dirty and accessed.
 *
 * Note that the kernel uses the accessed bit just to check whether to page
 * out a page or not, so it करोesn't have to be exact anyway.
 */

#घोषणा __सूचीTY_BITS	(_PAGE_सूचीTY | _PAGE_KWE | _PAGE_UWE)
#घोषणा __ACCESS_BITS	(_PAGE_ACCESSED | _PAGE_KRE | _PAGE_URE)

#घोषणा _PFN_MASK	0xFFFFFFFF00000000UL

#घोषणा _PAGE_TABLE	(_PAGE_VALID | __सूचीTY_BITS | __ACCESS_BITS)
#घोषणा _PAGE_CHG_MASK	(_PFN_MASK | __सूचीTY_BITS | __ACCESS_BITS)

/*
 * All the normal masks have the "page accessed" bits on, as any समय they are used,
 * the page is accessed. They are cleared only by the page-out routines
 */
#घोषणा PAGE_NONE	__pgprot(_PAGE_VALID | __ACCESS_BITS | _PAGE_FOR | _PAGE_FOW | _PAGE_FOE)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_VALID | __ACCESS_BITS)
#घोषणा PAGE_COPY	__pgprot(_PAGE_VALID | __ACCESS_BITS | _PAGE_FOW)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_VALID | __ACCESS_BITS | _PAGE_FOW)
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_VALID | _PAGE_ASM | _PAGE_KRE | _PAGE_KWE)

#घोषणा _PAGE_NORMAL(x) __pgprot(_PAGE_VALID | __ACCESS_BITS | (x))

#घोषणा _PAGE_P(x) _PAGE_NORMAL((x) | (((x) & _PAGE_FOW)?0:_PAGE_FOW))
#घोषणा _PAGE_S(x) _PAGE_NORMAL(x)

/*
 * The hardware can handle ग_लिखो-only mappings, but as the Alpha
 * architecture करोes byte-wide ग_लिखोs with a पढ़ो-modअगरy-ग_लिखो
 * sequence, it's not practical to have ग_लिखो-without-पढ़ो privs.
 * Thus the "-w- -> rw-" and "-wx -> rwx" mapping here (and in
 * arch/alpha/mm/fault.c)
 */
	/* xwr */
#घोषणा __P000	_PAGE_P(_PAGE_FOE | _PAGE_FOW | _PAGE_FOR)
#घोषणा __P001	_PAGE_P(_PAGE_FOE | _PAGE_FOW)
#घोषणा __P010	_PAGE_P(_PAGE_FOE)
#घोषणा __P011	_PAGE_P(_PAGE_FOE)
#घोषणा __P100	_PAGE_P(_PAGE_FOW | _PAGE_FOR)
#घोषणा __P101	_PAGE_P(_PAGE_FOW)
#घोषणा __P110	_PAGE_P(0)
#घोषणा __P111	_PAGE_P(0)

#घोषणा __S000	_PAGE_S(_PAGE_FOE | _PAGE_FOW | _PAGE_FOR)
#घोषणा __S001	_PAGE_S(_PAGE_FOE | _PAGE_FOW)
#घोषणा __S010	_PAGE_S(_PAGE_FOE)
#घोषणा __S011	_PAGE_S(_PAGE_FOE)
#घोषणा __S100	_PAGE_S(_PAGE_FOW | _PAGE_FOR)
#घोषणा __S101	_PAGE_S(_PAGE_FOW)
#घोषणा __S110	_PAGE_S(0)
#घोषणा __S111	_PAGE_S(0)

/*
 * pgprot_noncached() is only क्रम infiniband pci support, and a real
 * implementation क्रम RAM would be more complicated.
 */
#घोषणा pgprot_noncached(prot)	(prot)

/*
 * BAD_PAGETABLE is used when we need a bogus page-table, जबतक
 * BAD_PAGE is used क्रम a bogus page.
 *
 * ZERO_PAGE is a global shared page that is always zero:  used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य pte_t __bad_page(व्योम);
बाह्य pmd_t * __bad_pagetable(व्योम);

बाह्य अचिन्हित दीर्घ __zero_page(व्योम);

#घोषणा BAD_PAGETABLE	__bad_pagetable()
#घोषणा BAD_PAGE	__bad_page()
#घोषणा ZERO_PAGE(vaddr)	(virt_to_page(ZERO_PGE))

/* number of bits that fit पूर्णांकo a memory poपूर्णांकer */
#घोषणा BITS_PER_PTR			(8*माप(अचिन्हित दीर्घ))

/* to align the poपूर्णांकer to a poपूर्णांकer address */
#घोषणा PTR_MASK			(~(माप(व्योम*)-1))

/* माप(व्योम*)==1<<SIZखातापूर्ण_PTR_LOG2 */
#घोषणा SIZखातापूर्ण_PTR_LOG2			3

/* to find an entry in a page-table */
#घोषणा PAGE_PTR(address)		\
  ((अचिन्हित दीर्घ)(address)>>(PAGE_SHIFT-SIZखातापूर्ण_PTR_LOG2)&PTR_MASK&~PAGE_MASK)

/*
 * On certain platक्रमms whose physical address space can overlap KSEG,
 * namely EV6 and above, we must re-twiddle the physaddr to restore the
 * correct high-order bits.
 *
 * This is extremely confusing until you realize that this is actually
 * just working around a userspace bug.  The X server was पूर्णांकending to
 * provide the physical address but instead provided the KSEG address.
 * Or tried to, except it's not representable.
 * 
 * On Tsunami there's nothing meaningful at 0x40000000000, so this is
 * a safe thing to करो.  Come the first core logic that करोes put something
 * in this area -- memory or whathaveyou -- then this hack will have
 * to go away.  So be prepared!
 */

#अगर defined(CONFIG_ALPHA_GENERIC) && defined(USE_48_BIT_KSEG)
#त्रुटि "EV6-only feature in a generic kernel"
#पूर्ण_अगर
#अगर defined(CONFIG_ALPHA_GENERIC) || \
    (defined(CONFIG_ALPHA_EV6) && !defined(USE_48_BIT_KSEG))
#घोषणा KSEG_PFN	(0xc0000000000UL >> PAGE_SHIFT)
#घोषणा PHYS_TWIDDLE(pfn) \
  ((((pfn) & KSEG_PFN) == (0x40000000000UL >> PAGE_SHIFT)) \
  ? ((pfn) ^= KSEG_PFN) : (pfn))
#अन्यथा
#घोषणा PHYS_TWIDDLE(pfn) (pfn)
#पूर्ण_अगर

/*
 * Conversion functions:  convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा page_to_pa(page)	(page_to_pfn(page) << PAGE_SHIFT)
#घोषणा pte_pfn(pte)	(pte_val(pte) >> 32)

#अगर_अघोषित CONFIG_DISCONTIGMEM
#घोषणा pte_page(pte)	pfn_to_page(pte_pfn(pte))
#घोषणा mk_pte(page, pgprot)						\
(अणु									\
	pte_t pte;							\
									\
	pte_val(pte) = (page_to_pfn(page) << 32) | pgprot_val(pgprot);	\
	pte;								\
पूर्ण)
#पूर्ण_अगर

बाह्य अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ physpfn, pgprot_t pgprot)
अणु pte_t pte; pte_val(pte) = (PHYS_TWIDDLE(physpfn) << 32) | pgprot_val(pgprot); वापस pte; पूर्ण

बाह्य अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु pte_val(pte) = (pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot); वापस pte; पूर्ण

बाह्य अंतरभूत व्योम pmd_set(pmd_t * pmdp, pte_t * ptep)
अणु pmd_val(*pmdp) = _PAGE_TABLE | ((((अचिन्हित दीर्घ) ptep) - PAGE_OFFSET) << (32-PAGE_SHIFT)); पूर्ण

बाह्य अंतरभूत व्योम pud_set(pud_t * pudp, pmd_t * pmdp)
अणु pud_val(*pudp) = _PAGE_TABLE | ((((अचिन्हित दीर्घ) pmdp) - PAGE_OFFSET) << (32-PAGE_SHIFT)); पूर्ण


बाह्य अंतरभूत अचिन्हित दीर्घ
pmd_page_vaddr(pmd_t pmd)
अणु
	वापस ((pmd_val(pmd) & _PFN_MASK) >> (32-PAGE_SHIFT)) + PAGE_OFFSET;
पूर्ण

#घोषणा pmd_page(pmd)	(pfn_to_page(pmd_val(pmd) >> 32))
#घोषणा pud_page(pud)	(pfn_to_page(pud_val(pud) >> 32))

बाह्य अंतरभूत अचिन्हित दीर्घ pud_page_vaddr(pud_t pgd)
अणु वापस PAGE_OFFSET + ((pud_val(pgd) & _PFN_MASK) >> (32-PAGE_SHIFT)); पूर्ण

बाह्य अंतरभूत पूर्णांक pte_none(pte_t pte)		अणु वापस !pte_val(pte); पूर्ण
बाह्य अंतरभूत पूर्णांक pte_present(pte_t pte)	अणु वापस pte_val(pte) & _PAGE_VALID; पूर्ण
बाह्य अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_val(*ptep) = 0;
पूर्ण

बाह्य अंतरभूत पूर्णांक pmd_none(pmd_t pmd)		अणु वापस !pmd_val(pmd); पूर्ण
बाह्य अंतरभूत पूर्णांक pmd_bad(pmd_t pmd)		अणु वापस (pmd_val(pmd) & ~_PFN_MASK) != _PAGE_TABLE; पूर्ण
बाह्य अंतरभूत पूर्णांक pmd_present(pmd_t pmd)	अणु वापस pmd_val(pmd) & _PAGE_VALID; पूर्ण
बाह्य अंतरभूत व्योम pmd_clear(pmd_t * pmdp)	अणु pmd_val(*pmdp) = 0; पूर्ण

बाह्य अंतरभूत पूर्णांक pud_none(pud_t pud)		अणु वापस !pud_val(pud); पूर्ण
बाह्य अंतरभूत पूर्णांक pud_bad(pud_t pud)		अणु वापस (pud_val(pud) & ~_PFN_MASK) != _PAGE_TABLE; पूर्ण
बाह्य अंतरभूत पूर्णांक pud_present(pud_t pud)	अणु वापस pud_val(pud) & _PAGE_VALID; पूर्ण
बाह्य अंतरभूत व्योम pud_clear(pud_t * pudp)	अणु pud_val(*pudp) = 0; पूर्ण

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
बाह्य अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)		अणु वापस !(pte_val(pte) & _PAGE_FOW); पूर्ण
बाह्य अंतरभूत पूर्णांक pte_dirty(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_सूचीTY; पूर्ण
बाह्य अंतरभूत पूर्णांक pte_young(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_ACCESSED; पूर्ण

बाह्य अंतरभूत pte_t pte_wrprotect(pte_t pte)	अणु pte_val(pte) |= _PAGE_FOW; वापस pte; पूर्ण
बाह्य अंतरभूत pte_t pte_mkclean(pte_t pte)	अणु pte_val(pte) &= ~(__सूचीTY_BITS); वापस pte; पूर्ण
बाह्य अंतरभूत pte_t pte_mkold(pte_t pte)	अणु pte_val(pte) &= ~(__ACCESS_BITS); वापस pte; पूर्ण
बाह्य अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)	अणु pte_val(pte) &= ~_PAGE_FOW; वापस pte; पूर्ण
बाह्य अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)	अणु pte_val(pte) |= __सूचीTY_BITS; वापस pte; पूर्ण
बाह्य अंतरभूत pte_t pte_mkyoung(pte_t pte)	अणु pte_val(pte) |= __ACCESS_BITS; वापस pte; पूर्ण

/*
 * The smp_rmb() in the following functions are required to order the load of
 * *dir (the poपूर्णांकer in the top level page table) with any subsequent load of
 * the वापसed pmd_t *ret (ret is data dependent on *dir).
 *
 * If this ordering is not enक्रमced, the CPU might load an older value of
 * *ret, which may be uninitialized data. See mm/memory.c:__pte_alloc क्रम
 * more details.
 *
 * Note that we never change the mm->pgd poपूर्णांकer after the task is running, so
 * pgd_offset करोes not require such a barrier.
 */

/* Find an entry in the second-level page table.. */
बाह्य अंतरभूत pmd_t * pmd_offset(pud_t * dir, अचिन्हित दीर्घ address)
अणु
	pmd_t *ret = (pmd_t *) pud_page_vaddr(*dir) + ((address >> PMD_SHIFT) & (PTRS_PER_PAGE - 1));
	smp_rmb(); /* see above */
	वापस ret;
पूर्ण
#घोषणा pmd_offset pmd_offset

/* Find an entry in the third-level page table.. */
बाह्य अंतरभूत pte_t * pte_offset_kernel(pmd_t * dir, अचिन्हित दीर्घ address)
अणु
	pte_t *ret = (pte_t *) pmd_page_vaddr(*dir)
		+ ((address >> PAGE_SHIFT) & (PTRS_PER_PAGE - 1));
	smp_rmb(); /* see above */
	वापस ret;
पूर्ण
#घोषणा pte_offset_kernel pte_offset_kernel

बाह्य pgd_t swapper_pg_dir[1024];

/*
 * The Alpha करोesn't have any बाह्यal MMU info:  the kernel page
 * tables contain all the necessary inक्रमmation.
 */
बाह्य अंतरभूत व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा * vma,
	अचिन्हित दीर्घ address, pte_t *ptep)
अणु
पूर्ण

/*
 * Non-present pages:  high 24 bits are offset, next 8 bits type,
 * low 32 bits zero.
 */
बाह्य अंतरभूत pte_t mk_swap_pte(अचिन्हित दीर्घ type, अचिन्हित दीर्घ offset)
अणु pte_t pte; pte_val(pte) = (type << 32) | (offset << 40); वापस pte; पूर्ण

#घोषणा __swp_type(x)		(((x).val >> 32) & 0xff)
#घोषणा __swp_offset(x)		((x).val >> 40)
#घोषणा __swp_entry(type, off)	((swp_entry_t) अणु pte_val(mk_swap_pte((type), (off))) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)

#अगर_अघोषित CONFIG_DISCONTIGMEM
#घोषणा kern_addr_valid(addr)	(1)
#पूर्ण_अगर

#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %016lx.\n", __खाता__, __LINE__, pte_val(e))
#घोषणा pmd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pmd %016lx.\n", __खाता__, __LINE__, pmd_val(e))
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pgd %016lx.\n", __खाता__, __LINE__, pgd_val(e))

बाह्य व्योम paging_init(व्योम);

/* We have our own get_unmapped_area to cope with ADDR_LIMIT_32BIT.  */
#घोषणा HAVE_ARCH_UNMAPPED_AREA

#पूर्ण_अगर /* _ALPHA_PGTABLE_H */
