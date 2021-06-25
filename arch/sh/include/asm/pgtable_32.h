<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_PGTABLE_32_H
#घोषणा __ASM_SH_PGTABLE_32_H

/*
 * Linux PTEL encoding.
 *
 * Hardware and software bit definitions क्रम the PTEL value (see below क्रम
 * notes on SH-X2 MMUs and 64-bit PTEs):
 *
 * - Bits 0 and 7 are reserved on SH-3 (_PAGE_WT and _PAGE_SZ1 on SH-4).
 *
 * - Bit 1 is the SH-bit, but is unused on SH-3 due to an MMU bug (the
 *   hardware PTEL value can't have the SH-bit set when MMUCR.IX is set,
 *   which is the शेष in cpu-sh3/mmu_context.h:MMU_CONTROL_INIT).
 *
 *   In order to keep this relatively clean, करो not use these क्रम defining
 *   SH-3 specअगरic flags until all of the other unused bits have been
 *   exhausted.
 *
 * - Bit 9 is reserved by everyone and used by _PAGE_PROTNONE.
 *
 * - Bits 10 and 11 are low bits of the PPN that are reserved on >= 4K pages.
 *   Bit 10 is used क्रम _PAGE_ACCESSED, and bit 11 is used क्रम _PAGE_SPECIAL.
 *
 * - On 29 bit platक्रमms, bits 31 to 29 are used क्रम the space attributes
 *   and timing control which (together with bit 0) are moved पूर्णांकo the
 *   old-style PTEA on the parts that support it.
 *
 * SH-X2 MMUs and extended PTEs
 *
 * SH-X2 supports an extended mode TLB with split data arrays due to the
 * number of bits needed क्रम PR and SZ (now EPR and ESZ) encodings. The PR and
 * SZ bit placeholders still exist in data array 1, but are implemented as
 * reserved bits, with the real logic existing in data array 2.
 *
 * The करोwnside to this is that we can no दीर्घer fit everything in to a 32-bit
 * PTE encoding, so a 64-bit pte_t is necessary क्रम these parts. On the plus
 * side, this gives us quite a few spare bits to play with क्रम future usage.
 */
/* Legacy and compat mode bits */
#घोषणा	_PAGE_WT	0x001		/* WT-bit on SH-4, 0 on SH-3 */
#घोषणा _PAGE_HW_SHARED	0x002		/* SH-bit  : shared among processes */
#घोषणा _PAGE_सूचीTY	0x004		/* D-bit   : page changed */
#घोषणा _PAGE_CACHABLE	0x008		/* C-bit   : cachable */
#घोषणा _PAGE_SZ0	0x010		/* SZ0-bit : Size of page */
#घोषणा _PAGE_RW	0x020		/* PR0-bit : ग_लिखो access allowed */
#घोषणा _PAGE_USER	0x040		/* PR1-bit : user space access allowed*/
#घोषणा _PAGE_SZ1	0x080		/* SZ1-bit : Size of page (on SH-4) */
#घोषणा _PAGE_PRESENT	0x100		/* V-bit   : page is valid */
#घोषणा _PAGE_PROTNONE	0x200		/* software: अगर not present  */
#घोषणा _PAGE_ACCESSED	0x400		/* software: page referenced */
#घोषणा _PAGE_SPECIAL	0x800		/* software: special page */

#घोषणा _PAGE_SZ_MASK	(_PAGE_SZ0 | _PAGE_SZ1)
#घोषणा _PAGE_PR_MASK	(_PAGE_RW | _PAGE_USER)

/* Extended mode bits */
#घोषणा _PAGE_EXT_ESZ0		0x0010	/* ESZ0-bit: Size of page */
#घोषणा _PAGE_EXT_ESZ1		0x0020	/* ESZ1-bit: Size of page */
#घोषणा _PAGE_EXT_ESZ2		0x0040	/* ESZ2-bit: Size of page */
#घोषणा _PAGE_EXT_ESZ3		0x0080	/* ESZ3-bit: Size of page */

#घोषणा _PAGE_EXT_USER_EXEC	0x0100	/* EPR0-bit: User space executable */
#घोषणा _PAGE_EXT_USER_WRITE	0x0200	/* EPR1-bit: User space writable */
#घोषणा _PAGE_EXT_USER_READ	0x0400	/* EPR2-bit: User space पढ़ोable */

#घोषणा _PAGE_EXT_KERN_EXEC	0x0800	/* EPR3-bit: Kernel space executable */
#घोषणा _PAGE_EXT_KERN_WRITE	0x1000	/* EPR4-bit: Kernel space writable */
#घोषणा _PAGE_EXT_KERN_READ	0x2000	/* EPR5-bit: Kernel space पढ़ोable */

#घोषणा _PAGE_EXT_WIRED		0x4000	/* software: Wire TLB entry */

/* Wrapper क्रम extended mode pgprot twiddling */
#घोषणा _PAGE_EXT(x)		((अचिन्हित दीर्घ दीर्घ)(x) << 32)

#अगर_घोषित CONFIG_X2TLB
#घोषणा _PAGE_PCC_MASK	0x00000000	/* No legacy PTEA support */
#अन्यथा

/* software: moves to PTEA.TC (Timing Control) */
#घोषणा _PAGE_PCC_AREA5	0x00000000	/* use BSC रेजिस्टरs क्रम area5 */
#घोषणा _PAGE_PCC_AREA6	0x80000000	/* use BSC रेजिस्टरs क्रम area6 */

/* software: moves to PTEA.SA[2:0] (Space Attributes) */
#घोषणा _PAGE_PCC_IODYN 0x00000001	/* IO space, dynamically sized bus */
#घोषणा _PAGE_PCC_IO8	0x20000000	/* IO space, 8 bit bus */
#घोषणा _PAGE_PCC_IO16	0x20000001	/* IO space, 16 bit bus */
#घोषणा _PAGE_PCC_COM8	0x40000000	/* Common Memory space, 8 bit bus */
#घोषणा _PAGE_PCC_COM16	0x40000001	/* Common Memory space, 16 bit bus */
#घोषणा _PAGE_PCC_ATR8	0x60000000	/* Attribute Memory space, 8 bit bus */
#घोषणा _PAGE_PCC_ATR16	0x60000001	/* Attribute Memory space, 6 bit bus */

#घोषणा _PAGE_PCC_MASK	0xe0000001

/* copy the ptea attributes */
अटल अंतरभूत अचिन्हित दीर्घ copy_ptea_attributes(अचिन्हित दीर्घ x)
अणु
	वापस	((x >> 28) & 0xe) | (x & 0x1);
पूर्ण
#पूर्ण_अगर

/* Mask which drops unused bits from the PTEL value */
#अगर defined(CONFIG_CPU_SH3)
#घोषणा _PAGE_CLEAR_FLAGS	(_PAGE_PROTNONE | _PAGE_ACCESSED| \
				  _PAGE_SZ1	| _PAGE_HW_SHARED)
#या_अगर defined(CONFIG_X2TLB)
/* Get rid of the legacy PR/SZ bits when using extended mode */
#घोषणा _PAGE_CLEAR_FLAGS	(_PAGE_PROTNONE | _PAGE_ACCESSED | \
				 _PAGE_PR_MASK | _PAGE_SZ_MASK)
#अन्यथा
#घोषणा _PAGE_CLEAR_FLAGS	(_PAGE_PROTNONE | _PAGE_ACCESSED)
#पूर्ण_अगर

#घोषणा _PAGE_FLAGS_HARDWARE_MASK	(phys_addr_mask() & ~(_PAGE_CLEAR_FLAGS))

/* Hardware flags, page size encoding */
#अगर !defined(CONFIG_MMU)
# define _PAGE_FLAGS_HARD	0ULL
#या_अगर defined(CONFIG_X2TLB)
# अगर defined(CONFIG_PAGE_SIZE_4KB)
#  define _PAGE_FLAGS_HARD	_PAGE_EXT(_PAGE_EXT_ESZ0)
# elअगर defined(CONFIG_PAGE_SIZE_8KB)
#  define _PAGE_FLAGS_HARD	_PAGE_EXT(_PAGE_EXT_ESZ1)
# elअगर defined(CONFIG_PAGE_SIZE_64KB)
#  define _PAGE_FLAGS_HARD	_PAGE_EXT(_PAGE_EXT_ESZ2)
# endअगर
#अन्यथा
# अगर defined(CONFIG_PAGE_SIZE_4KB)
#  define _PAGE_FLAGS_HARD	_PAGE_SZ0
# elअगर defined(CONFIG_PAGE_SIZE_64KB)
#  define _PAGE_FLAGS_HARD	_PAGE_SZ1
# endअगर
#पूर्ण_अगर

#अगर defined(CONFIG_X2TLB)
# अगर defined(CONFIG_HUGETLB_PAGE_SIZE_64K)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ2)
# elअगर defined(CONFIG_HUGETLB_PAGE_SIZE_256K)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ0 | _PAGE_EXT_ESZ2)
# elअगर defined(CONFIG_HUGETLB_PAGE_SIZE_1MB)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ0 | _PAGE_EXT_ESZ1 | _PAGE_EXT_ESZ2)
# elअगर defined(CONFIG_HUGETLB_PAGE_SIZE_4MB)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ3)
# elअगर defined(CONFIG_HUGETLB_PAGE_SIZE_64MB)
#  define _PAGE_SZHUGE	(_PAGE_EXT_ESZ2 | _PAGE_EXT_ESZ3)
# endअगर
# define _PAGE_WIRED	(_PAGE_EXT(_PAGE_EXT_WIRED))
#अन्यथा
# अगर defined(CONFIG_HUGETLB_PAGE_SIZE_64K)
#  define _PAGE_SZHUGE	(_PAGE_SZ1)
# elअगर defined(CONFIG_HUGETLB_PAGE_SIZE_1MB)
#  define _PAGE_SZHUGE	(_PAGE_SZ0 | _PAGE_SZ1)
# endअगर
# define _PAGE_WIRED	(0)
#पूर्ण_अगर

/*
 * Stub out _PAGE_SZHUGE अगर we करोn't have a good definition क्रम it,
 * to make pte_mkhuge() happy.
 */
#अगर_अघोषित _PAGE_SZHUGE
# define _PAGE_SZHUGE	(_PAGE_FLAGS_HARD)
#पूर्ण_अगर

/*
 * Mask of bits that are to be preserved across pgprot changes.
 */
#घोषणा _PAGE_CHG_MASK \
	(PTE_MASK | _PAGE_ACCESSED | _PAGE_CACHABLE | \
	 _PAGE_सूचीTY | _PAGE_SPECIAL)

#अगर_अघोषित __ASSEMBLY__

#अगर defined(CONFIG_X2TLB) /* SH-X2 TLB */
#घोषणा PAGE_NONE	__pgprot(_PAGE_PROTNONE | _PAGE_CACHABLE | \
				 _PAGE_ACCESSED | _PAGE_FLAGS_HARD)

#घोषणा PAGE_SHARED	__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABLE | _PAGE_FLAGS_HARD | \
				 _PAGE_EXT(_PAGE_EXT_KERN_READ  | \
					   _PAGE_EXT_KERN_WRITE | \
					   _PAGE_EXT_USER_READ  | \
					   _PAGE_EXT_USER_WRITE))

#घोषणा PAGE_EXECREAD	__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABLE | _PAGE_FLAGS_HARD | \
				 _PAGE_EXT(_PAGE_EXT_KERN_EXEC | \
					   _PAGE_EXT_KERN_READ | \
					   _PAGE_EXT_USER_EXEC | \
					   _PAGE_EXT_USER_READ))

#घोषणा PAGE_COPY	PAGE_EXECREAD

#घोषणा PAGE_READONLY	__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABLE | _PAGE_FLAGS_HARD | \
				 _PAGE_EXT(_PAGE_EXT_KERN_READ | \
					   _PAGE_EXT_USER_READ))

#घोषणा PAGE_WRITEONLY	__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABLE | _PAGE_FLAGS_HARD | \
				 _PAGE_EXT(_PAGE_EXT_KERN_WRITE | \
					   _PAGE_EXT_USER_WRITE))

#घोषणा PAGE_RWX	__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | \
				 _PAGE_CACHABLE | _PAGE_FLAGS_HARD | \
				 _PAGE_EXT(_PAGE_EXT_KERN_WRITE | \
					   _PAGE_EXT_KERN_READ  | \
					   _PAGE_EXT_KERN_EXEC  | \
					   _PAGE_EXT_USER_WRITE | \
					   _PAGE_EXT_USER_READ  | \
					   _PAGE_EXT_USER_EXEC))

#घोषणा PAGE_KERNEL	__pgprot(_PAGE_PRESENT | _PAGE_CACHABLE | \
				 _PAGE_सूचीTY | _PAGE_ACCESSED | \
				 _PAGE_HW_SHARED | _PAGE_FLAGS_HARD | \
				 _PAGE_EXT(_PAGE_EXT_KERN_READ | \
					   _PAGE_EXT_KERN_WRITE | \
					   _PAGE_EXT_KERN_EXEC))

#घोषणा PAGE_KERNEL_NOCACHE \
			__pgprot(_PAGE_PRESENT | _PAGE_सूचीTY | \
				 _PAGE_ACCESSED | _PAGE_HW_SHARED | \
				 _PAGE_FLAGS_HARD | \
				 _PAGE_EXT(_PAGE_EXT_KERN_READ | \
					   _PAGE_EXT_KERN_WRITE | \
					   _PAGE_EXT_KERN_EXEC))

#घोषणा PAGE_KERNEL_RO	__pgprot(_PAGE_PRESENT | _PAGE_CACHABLE | \
				 _PAGE_सूचीTY | _PAGE_ACCESSED | \
				 _PAGE_HW_SHARED | _PAGE_FLAGS_HARD | \
				 _PAGE_EXT(_PAGE_EXT_KERN_READ | \
					   _PAGE_EXT_KERN_EXEC))

#घोषणा PAGE_KERNEL_PCC(slot, type) \
			__pgprot(0)

#या_अगर defined(CONFIG_MMU) /* SH-X TLB */
#घोषणा PAGE_NONE	__pgprot(_PAGE_PROTNONE | _PAGE_CACHABLE | \
				 _PAGE_ACCESSED | _PAGE_FLAGS_HARD)

#घोषणा PAGE_SHARED	__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | \
				 _PAGE_CACHABLE | _PAGE_ACCESSED | \
				 _PAGE_FLAGS_HARD)

#घोषणा PAGE_COPY	__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_CACHABLE | \
				 _PAGE_ACCESSED | _PAGE_FLAGS_HARD)

#घोषणा PAGE_READONLY	__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_CACHABLE | \
				 _PAGE_ACCESSED | _PAGE_FLAGS_HARD)

#घोषणा PAGE_EXECREAD	PAGE_READONLY
#घोषणा PAGE_RWX	PAGE_SHARED
#घोषणा PAGE_WRITEONLY	PAGE_SHARED

#घोषणा PAGE_KERNEL	__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_CACHABLE | \
				 _PAGE_सूचीTY | _PAGE_ACCESSED | \
				 _PAGE_HW_SHARED | _PAGE_FLAGS_HARD)

#घोषणा PAGE_KERNEL_NOCACHE \
			__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_सूचीTY | \
				 _PAGE_ACCESSED | _PAGE_HW_SHARED | \
				 _PAGE_FLAGS_HARD)

#घोषणा PAGE_KERNEL_RO	__pgprot(_PAGE_PRESENT | _PAGE_CACHABLE | \
				 _PAGE_सूचीTY | _PAGE_ACCESSED | \
				 _PAGE_HW_SHARED | _PAGE_FLAGS_HARD)

#घोषणा PAGE_KERNEL_PCC(slot, type) \
			__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_सूचीTY | \
				 _PAGE_ACCESSED | _PAGE_FLAGS_HARD | \
				 (slot ? _PAGE_PCC_AREA5 : _PAGE_PCC_AREA6) | \
				 (type))
#अन्यथा /* no mmu */
#घोषणा PAGE_NONE		__pgprot(0)
#घोषणा PAGE_SHARED		__pgprot(0)
#घोषणा PAGE_COPY		__pgprot(0)
#घोषणा PAGE_EXECREAD		__pgprot(0)
#घोषणा PAGE_RWX		__pgprot(0)
#घोषणा PAGE_READONLY		__pgprot(0)
#घोषणा PAGE_WRITEONLY		__pgprot(0)
#घोषणा PAGE_KERNEL		__pgprot(0)
#घोषणा PAGE_KERNEL_NOCACHE	__pgprot(0)
#घोषणा PAGE_KERNEL_RO		__pgprot(0)

#घोषणा PAGE_KERNEL_PCC(slot, type) \
				__pgprot(0)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर_अघोषित __ASSEMBLY__

/*
 * Certain architectures need to करो special things when PTEs
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */
#अगर_घोषित CONFIG_X2TLB
अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pte)
अणु
	ptep->pte_high = pte.pte_high;
	smp_wmb();
	ptep->pte_low = pte.pte_low;
पूर्ण
#अन्यथा
#घोषणा set_pte(pteptr, pteval) (*(pteptr) = pteval)
#पूर्ण_अगर

#घोषणा set_pte_at(mm,addr,ptep,pteval) set_pte(ptep,pteval)

/*
 * (pmds are folded पूर्णांकo pgds so this करोesn't get actually called,
 * but the define is needed क्रम a generic अंतरभूत function.)
 */
#घोषणा set_pmd(pmdptr, pmdval) (*(pmdptr) = pmdval)

#घोषणा pfn_pte(pfn, prot) \
	__pte(((अचिन्हित दीर्घ दीर्घ)(pfn) << PAGE_SHIFT) | pgprot_val(prot))
#घोषणा pfn_pmd(pfn, prot) \
	__pmd(((अचिन्हित दीर्घ दीर्घ)(pfn) << PAGE_SHIFT) | pgprot_val(prot))

#घोषणा pte_none(x)		(!pte_val(x))
#घोषणा pte_present(x)		((x).pte_low & (_PAGE_PRESENT | _PAGE_PROTNONE))

#घोषणा pte_clear(mm,addr,xp) करो अणु set_pte_at(mm, addr, xp, __pte(0)); पूर्ण जबतक (0)

#घोषणा pmd_none(x)	(!pmd_val(x))
#घोषणा pmd_present(x)	(pmd_val(x))
#घोषणा pmd_clear(xp)	करो अणु set_pmd(xp, __pmd(0)); पूर्ण जबतक (0)
#घोषणा	pmd_bad(x)	(pmd_val(x) & ~PAGE_MASK)

#घोषणा pages_to_mb(x)	((x) >> (20-PAGE_SHIFT))
#घोषणा pte_page(x)	pfn_to_page(pte_pfn(x))

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
#घोषणा pte_not_present(pte)	(!((pte).pte_low & _PAGE_PRESENT))
#घोषणा pte_dirty(pte)		((pte).pte_low & _PAGE_सूचीTY)
#घोषणा pte_young(pte)		((pte).pte_low & _PAGE_ACCESSED)
#घोषणा pte_special(pte)	((pte).pte_low & _PAGE_SPECIAL)

#अगर_घोषित CONFIG_X2TLB
#घोषणा pte_ग_लिखो(pte) \
	((pte).pte_high & (_PAGE_EXT_USER_WRITE | _PAGE_EXT_KERN_WRITE))
#अन्यथा
#घोषणा pte_ग_लिखो(pte)		((pte).pte_low & _PAGE_RW)
#पूर्ण_अगर

#घोषणा PTE_BIT_FUNC(h,fn,op) \
अटल अंतरभूत pte_t pte_##fn(pte_t pte) अणु pte.pte_##h op; वापस pte; पूर्ण

#अगर_घोषित CONFIG_X2TLB
/*
 * We cheat a bit in the SH-X2 TLB हाल. As the permission bits are
 * inभागidually toggled (and user permissions are entirely decoupled from
 * kernel permissions), we attempt to couple them a bit more sanely here.
 */
PTE_BIT_FUNC(high, wrprotect, &= ~(_PAGE_EXT_USER_WRITE | _PAGE_EXT_KERN_WRITE));
PTE_BIT_FUNC(high, mkग_लिखो, |= _PAGE_EXT_USER_WRITE | _PAGE_EXT_KERN_WRITE);
PTE_BIT_FUNC(high, mkhuge, |= _PAGE_SZHUGE);
#अन्यथा
PTE_BIT_FUNC(low, wrprotect, &= ~_PAGE_RW);
PTE_BIT_FUNC(low, mkग_लिखो, |= _PAGE_RW);
PTE_BIT_FUNC(low, mkhuge, |= _PAGE_SZHUGE);
#पूर्ण_अगर

PTE_BIT_FUNC(low, mkclean, &= ~_PAGE_सूचीTY);
PTE_BIT_FUNC(low, सूची_गढ़ोty, |= _PAGE_सूचीTY);
PTE_BIT_FUNC(low, mkold, &= ~_PAGE_ACCESSED);
PTE_BIT_FUNC(low, mkyoung, |= _PAGE_ACCESSED);
PTE_BIT_FUNC(low, mkspecial, |= _PAGE_SPECIAL);

/*
 * Macro and implementation to make a page protection as uncachable.
 */
#घोषणा pgprot_ग_लिखोcombine(prot) \
	__pgprot(pgprot_val(prot) & ~_PAGE_CACHABLE)

#घोषणा pgprot_noncached	 pgprot_ग_लिखोcombine

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 *
 * बाह्य pte_t mk_pte(काष्ठा page *page, pgprot_t pgprot)
 */
#घोषणा mk_pte(page, pgprot)	pfn_pte(page_to_pfn(page), (pgprot))

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte.pte_low &= _PAGE_CHG_MASK;
	pte.pte_low |= pgprot_val(newprot);

#अगर_घोषित CONFIG_X2TLB
	pte.pte_high |= pgprot_val(newprot) >> 32;
#पूर्ण_अगर

	वापस pte;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस (अचिन्हित दीर्घ)pmd_val(pmd);
पूर्ण

#घोषणा pmd_page(pmd)		(virt_to_page(pmd_val(pmd)))

#अगर_घोषित CONFIG_X2TLB
#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %p(%08lx%08lx).\n", __खाता__, __LINE__, \
	       &(e), (e).pte_high, (e).pte_low)
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pgd %016llx.\n", __खाता__, __LINE__, pgd_val(e))
#अन्यथा
#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, pte_val(e))
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))
#पूर्ण_अगर

/*
 * Encode and de-code a swap entry
 *
 * Constraपूर्णांकs:
 *	_PAGE_PRESENT at bit 8
 *	_PAGE_PROTNONE at bit 9
 *
 * For the normal हाल, we encode the swap type पूर्णांकo bits 0:7 and the
 * swap offset पूर्णांकo bits 10:30. For the 64-bit PTE हाल, we keep the
 * preserved bits in the low 32-bits and use the upper 32 as the swap
 * offset (aदीर्घ with a 5-bit type), following the same approach as x86
 * PAE. This keeps the logic quite simple.
 *
 * As is evident by the Alpha code, अगर we ever get a 64-bit अचिन्हित
 * दीर्घ (swp_entry_t) to match up with the 64-bit PTEs, this all becomes
 * much cleaner..
 *
 * NOTE: We should set ZEROs at the position of _PAGE_PRESENT
 *       and _PAGE_PROTNONE bits
 */
#अगर_घोषित CONFIG_X2TLB
#घोषणा __swp_type(x)			((x).val & 0x1f)
#घोषणा __swp_offset(x)			((x).val >> 5)
#घोषणा __swp_entry(type, offset)	((swp_entry_t)अणु (type) | (offset) << 5पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t)अणु (pte).pte_high पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t)अणु 0, (x).val पूर्ण)

#अन्यथा
#घोषणा __swp_type(x)			((x).val & 0xff)
#घोषणा __swp_offset(x)			((x).val >> 10)
#घोषणा __swp_entry(type, offset)	((swp_entry_t)अणु(type) | (offset) <<10पूर्ण)

#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) >> 1 पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val << 1 पूर्ण)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_SH_PGTABLE_32_H */
