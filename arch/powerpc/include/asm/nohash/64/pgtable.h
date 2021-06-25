<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_64_PGTABLE_H
#घोषणा _ASM_POWERPC_NOHASH_64_PGTABLE_H
/*
 * This file contains the functions and defines necessary to modअगरy and use
 * the ppc64 non-hashed page table.
 */

#समावेश <linux/sizes.h>

#समावेश <यंत्र/nohash/64/pgtable-4k.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/यंत्र-स्थिर.h>

#घोषणा FIRST_USER_ADDRESS	0UL

/*
 * Size of EA range mapped by our pagetables.
 */
#घोषणा PGTABLE_EADDR_SIZE (PTE_INDEX_SIZE + PMD_INDEX_SIZE + \
			    PUD_INDEX_SIZE + PGD_INDEX_SIZE + PAGE_SHIFT)
#घोषणा PGTABLE_RANGE (ASM_CONST(1) << PGTABLE_EADDR_SIZE)

#घोषणा PMD_CACHE_INDEX	PMD_INDEX_SIZE
#घोषणा PUD_CACHE_INDEX PUD_INDEX_SIZE

/*
 * Define the address range of the kernel non-linear भव area
 */
#घोषणा KERN_VIRT_START ASM_CONST(0x8000000000000000)
#घोषणा KERN_VIRT_SIZE	ASM_CONST(0x0000100000000000)

/*
 * The vदो_स्मृति space starts at the beginning of that region, and
 * occupies a quarter of it on Book3E
 * (we keep a quarter क्रम the भव memmap)
 */
#घोषणा VMALLOC_START	KERN_VIRT_START
#घोषणा VMALLOC_SIZE	(KERN_VIRT_SIZE >> 2)
#घोषणा VMALLOC_END	(VMALLOC_START + VMALLOC_SIZE)

/*
 * The second half of the kernel भव space is used क्रम IO mappings,
 * it's itself carved पूर्णांकo the PIO region (ISA and PHB IO space) and
 * the ioremap space
 *
 *  ISA_IO_BASE = KERN_IO_START, 64K reserved area
 *  PHB_IO_BASE = ISA_IO_BASE + 64K to ISA_IO_BASE + 2G, PHB IO spaces
 * IOREMAP_BASE = ISA_IO_BASE + 2G to VMALLOC_START + PGTABLE_RANGE
 */
#घोषणा KERN_IO_START	(KERN_VIRT_START + (KERN_VIRT_SIZE >> 1))
#घोषणा FULL_IO_SIZE	0x80000000ul
#घोषणा  ISA_IO_BASE	(KERN_IO_START)
#घोषणा  ISA_IO_END	(KERN_IO_START + 0x10000ul)
#घोषणा  PHB_IO_BASE	(ISA_IO_END)
#घोषणा  PHB_IO_END	(KERN_IO_START + FULL_IO_SIZE)
#घोषणा IOREMAP_BASE	(PHB_IO_END)
#घोषणा IOREMAP_START	(ioremap_bot)
#घोषणा IOREMAP_END	(KERN_VIRT_START + KERN_VIRT_SIZE - FIXADDR_SIZE)
#घोषणा FIXADDR_SIZE	SZ_32M


/*
 * Region IDs
 */
#घोषणा REGION_SHIFT		60UL
#घोषणा REGION_MASK		(0xfUL << REGION_SHIFT)
#घोषणा REGION_ID(ea)		(((अचिन्हित दीर्घ)(ea)) >> REGION_SHIFT)

#घोषणा VMALLOC_REGION_ID	(REGION_ID(VMALLOC_START))
#घोषणा KERNEL_REGION_ID	(REGION_ID(PAGE_OFFSET))
#घोषणा USER_REGION_ID		(0UL)

/*
 * Defines the address of the vmemap area, in its own region on
 * after the vदो_स्मृति space on Book3E
 */
#घोषणा VMEMMAP_BASE		VMALLOC_END
#घोषणा VMEMMAP_END		KERN_IO_START
#घोषणा vmemmap			((काष्ठा page *)VMEMMAP_BASE)


/*
 * Include the PTE bits definitions
 */
#समावेश <यंत्र/nohash/pte-book3e.h>

#घोषणा _PAGE_SAO	0

#घोषणा PTE_RPN_MASK	(~((1UL << PTE_RPN_SHIFT) - 1))

/*
 * _PAGE_CHG_MASK masks of bits that are to be preserved across
 * pgprot changes.
 */
#घोषणा _PAGE_CHG_MASK	(PTE_RPN_MASK | _PAGE_सूचीTY | _PAGE_ACCESSED | _PAGE_SPECIAL)

#घोषणा H_PAGE_4K_PFN 0

#अगर_अघोषित __ASSEMBLY__
/* pte_clear moved to later in this file */

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_RW);
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_RW);
पूर्ण

अटल अंतरभूत pte_t pte_mkexec(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_EXEC);
पूर्ण

#घोषणा PMD_BAD_BITS		(PTE_TABLE_SIZE-1)
#घोषणा PUD_BAD_BITS		(PMD_TABLE_SIZE-1)

अटल अंतरभूत व्योम pmd_set(pmd_t *pmdp, अचिन्हित दीर्घ val)
अणु
	*pmdp = __pmd(val);
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	*pmdp = __pmd(0);
पूर्ण

अटल अंतरभूत pte_t pmd_pte(pmd_t pmd)
अणु
	वापस __pte(pmd_val(pmd));
पूर्ण

#घोषणा pmd_none(pmd)		(!pmd_val(pmd))
#घोषणा	pmd_bad(pmd)		(!is_kernel_addr(pmd_val(pmd)) \
				 || (pmd_val(pmd) & PMD_BAD_BITS))
#घोषणा	pmd_present(pmd)	(!pmd_none(pmd))
#घोषणा pmd_page_vaddr(pmd)	(pmd_val(pmd) & ~PMD_MASKED_BITS)
बाह्य काष्ठा page *pmd_page(pmd_t pmd);

अटल अंतरभूत व्योम pud_set(pud_t *pudp, अचिन्हित दीर्घ val)
अणु
	*pudp = __pud(val);
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pudp)
अणु
	*pudp = __pud(0);
पूर्ण

#घोषणा pud_none(pud)		(!pud_val(pud))
#घोषणा	pud_bad(pud)		(!is_kernel_addr(pud_val(pud)) \
				 || (pud_val(pud) & PUD_BAD_BITS))
#घोषणा pud_present(pud)	(pud_val(pud) != 0)
#घोषणा pud_page_vaddr(pud)	(pud_val(pud) & ~PUD_MASKED_BITS)

बाह्य काष्ठा page *pud_page(pud_t pud);

अटल अंतरभूत pte_t pud_pte(pud_t pud)
अणु
	वापस __pte(pud_val(pud));
पूर्ण

अटल अंतरभूत pud_t pte_pud(pte_t pte)
अणु
	वापस __pud(pte_val(pte));
पूर्ण
#घोषणा pud_ग_लिखो(pud)		pte_ग_लिखो(pud_pte(pud))
#घोषणा p4d_ग_लिखो(pgd)		pte_ग_लिखो(p4d_pte(p4d))

अटल अंतरभूत व्योम p4d_set(p4d_t *p4dp, अचिन्हित दीर्घ val)
अणु
	*p4dp = __p4d(val);
पूर्ण

/* Atomic PTE updates */
अटल अंतरभूत अचिन्हित दीर्घ pte_update(काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ addr,
				       pte_t *ptep, अचिन्हित दीर्घ clr,
				       अचिन्हित दीर्घ set,
				       पूर्णांक huge)
अणु
	अचिन्हित दीर्घ old = pte_val(*ptep);
	*ptep = __pte((old & ~clr) | set);

	/* huge pages use the old page table lock */
	अगर (!huge)
		निश्चित_pte_locked(mm, addr);

	वापस old;
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_ACCESSED;
पूर्ण

अटल अंतरभूत पूर्णांक __ptep_test_and_clear_young(काष्ठा mm_काष्ठा *mm,
					      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ old;

	अगर (pte_young(*ptep))
		वापस 0;
	old = pte_update(mm, addr, ptep, _PAGE_ACCESSED, 0, 0);
	वापस (old & _PAGE_ACCESSED) != 0;
पूर्ण
#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
#घोषणा ptep_test_and_clear_young(__vma, __addr, __ptep)		   \
(अणु									   \
	पूर्णांक __r;							   \
	__r = __ptep_test_and_clear_young((__vma)->vm_mm, __addr, __ptep); \
	__r;								   \
पूर्ण)

#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				      pte_t *ptep)
अणु

	अगर ((pte_val(*ptep) & _PAGE_RW) == 0)
		वापस;

	pte_update(mm, addr, ptep, _PAGE_RW, 0, 0);
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अगर ((pte_val(*ptep) & _PAGE_RW) == 0)
		वापस;

	pte_update(mm, addr, ptep, _PAGE_RW, 0, 1);
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
#घोषणा ptep_clear_flush_young(__vma, __address, __ptep)		\
(अणु									\
	पूर्णांक __young = __ptep_test_and_clear_young((__vma)->vm_mm, __address, \
						  __ptep);		\
	__young;							\
पूर्ण)

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ old = pte_update(mm, addr, ptep, ~0UL, 0, 0);
	वापस __pte(old);
पूर्ण

अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			     pte_t * ptep)
अणु
	pte_update(mm, addr, ptep, ~0UL, 0, 0);
पूर्ण


/* Set the dirty and/or accessed bits atomically in a linux PTE */
अटल अंतरभूत व्योम __ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					   pte_t *ptep, pte_t entry,
					   अचिन्हित दीर्घ address,
					   पूर्णांक psize)
अणु
	अचिन्हित दीर्घ bits = pte_val(entry) &
		(_PAGE_सूचीTY | _PAGE_ACCESSED | _PAGE_RW | _PAGE_EXEC);

	अचिन्हित दीर्घ old = pte_val(*ptep);
	*ptep = __pte(old | bits);

	flush_tlb_page(vma, address);
पूर्ण

#घोषणा __HAVE_ARCH_PTE_SAME
#घोषणा pte_same(A,B)	((pte_val(A) ^ pte_val(B)) == 0)

#घोषणा pte_ERROR(e) \
	pr_err("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, pte_val(e))
#घोषणा pmd_ERROR(e) \
	pr_err("%s:%d: bad pmd %08lx.\n", __खाता__, __LINE__, pmd_val(e))
#घोषणा pgd_ERROR(e) \
	pr_err("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))

/* Encode and de-code a swap entry */
#घोषणा MAX_SWAPखाताS_CHECK() करो अणु \
	BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT > SWP_TYPE_BITS); \
	पूर्ण जबतक (0)

#घोषणा SWP_TYPE_BITS 5
#घोषणा __swp_type(x)		(((x).val >> _PAGE_BIT_SWAP_TYPE) \
				& ((1UL << SWP_TYPE_BITS) - 1))
#घोषणा __swp_offset(x)		((x).val >> PTE_RPN_SHIFT)
#घोषणा __swp_entry(type, offset)	((swp_entry_t) अणु \
					((type) << _PAGE_BIT_SWAP_TYPE) \
					| ((offset) << PTE_RPN_SHIFT) पूर्ण)

#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val((pte)) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		__pte((x).val)

पूर्णांक map_kernel_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa, pgprot_t prot);
बाह्य पूर्णांक __meminit vmemmap_create_mapping(अचिन्हित दीर्घ start,
					    अचिन्हित दीर्घ page_size,
					    अचिन्हित दीर्घ phys);
बाह्य व्योम vmemmap_हटाओ_mapping(अचिन्हित दीर्घ start,
				   अचिन्हित दीर्घ page_size);
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_NOHASH_64_PGTABLE_H */
