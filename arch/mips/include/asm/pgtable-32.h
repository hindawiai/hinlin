<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 2003 Ralf Baechle
 * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_PGTABLE_32_H
#घोषणा _ASM_PGTABLE_32_H

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/page.h>

#समावेश <linux/linkage.h>
#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/fixmap.h>

#समावेश <यंत्र-generic/pgtable-nopmd.h>

#अगर_घोषित CONFIG_HIGHMEM
#समावेश <यंत्र/highस्मृति.स>
#पूर्ण_अगर

/*
 * Regarding 32-bit MIPS huge page support (and the tradeoff it entails):
 *
 *  We use the same huge page sizes as 64-bit MIPS. Assuming a 4KB page size,
 * our 2-level table layout would normally have a PGD entry cover a contiguous
 * 4MB भव address region (poपूर्णांकing to a 4KB PTE page of 1,024 32-bit pte_t
 * poपूर्णांकers, each poपूर्णांकing to a 4KB physical page). The problem is that 4MB,
 * spanning both halves of a TLB EntryLo0,1 pair, requires 2MB hardware page
 * support, not one of the standard supported sizes (1MB,4MB,16MB,...).
 *  To correct क्रम this, when huge pages are enabled, we halve the number of
 * poपूर्णांकers a PTE page holds, making its last half go to waste. Correspondingly,
 * we द्विगुन the number of PGD pages. Overall, page table memory overhead
 * increases to match 64-bit MIPS, but PTE lookups reमुख्य CPU cache-मित्रly.
 *
 * NOTE: We करोn't yet support huge pages अगर extended-addressing is enabled
 *       (i.e. EVA, XPA, 36-bit Alchemy/Netlogic).
 */

बाह्य पूर्णांक temp_tlb_entry;

/*
 * - add_temporary_entry() add a temporary TLB entry. We use TLB entries
 *	starting at the top and working करोwn. This is क्रम populating the
 *	TLB beक्रमe trap_init() माला_दो the TLB miss handler in place. It
 *	should be used only क्रम entries matching the actual page tables,
 *	to prevent inconsistencies.
 */
बाह्य पूर्णांक add_temporary_entry(अचिन्हित दीर्घ entrylo0, अचिन्हित दीर्घ entrylo1,
			       अचिन्हित दीर्घ entryhi, अचिन्हित दीर्घ pagemask);

/*
 * Basically we have the same two-level (which is the logical three level
 * Linux page table layout folded) page tables as the i386.  Some day
 * when we have proper page coloring support we can have a 1% quicker
 * tlb refill handling mechanism, but क्रम now it is a bit slower but
 * works even with the cache aliasing problem the R4k and above have.
 */

/* PGसूची_SHIFT determines what a third-level page table entry can map */
#अगर defined(CONFIG_MIPS_HUGE_TLB_SUPPORT) && !defined(CONFIG_PHYS_ADDR_T_64BIT)
# define PGसूची_SHIFT	(2 * PAGE_SHIFT + PTE_ORDER - PTE_T_LOG2 - 1)
#अन्यथा
# define PGसूची_SHIFT	(2 * PAGE_SHIFT + PTE_ORDER - PTE_T_LOG2)
#पूर्ण_अगर

#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/*
 * Entries per page directory level: we use two-level, so
 * we करोn't really have any PUD/PMD directory physically.
 */
#अगर defined(CONFIG_MIPS_HUGE_TLB_SUPPORT) && !defined(CONFIG_PHYS_ADDR_T_64BIT)
# define __PGD_ORDER	(32 - 3 * PAGE_SHIFT + PGD_T_LOG2 + PTE_T_LOG2 + 1)
#अन्यथा
# define __PGD_ORDER	(32 - 3 * PAGE_SHIFT + PGD_T_LOG2 + PTE_T_LOG2)
#पूर्ण_अगर

#घोषणा PGD_ORDER	(__PGD_ORDER >= 0 ? __PGD_ORDER : 0)
#घोषणा PUD_ORDER	aieeee_attempt_to_allocate_pud
#घोषणा PMD_ORDER	aieeee_attempt_to_allocate_pmd
#घोषणा PTE_ORDER	0

#घोषणा PTRS_PER_PGD	(USER_PTRS_PER_PGD * 2)
#अगर defined(CONFIG_MIPS_HUGE_TLB_SUPPORT) && !defined(CONFIG_PHYS_ADDR_T_64BIT)
# define PTRS_PER_PTE	((PAGE_SIZE << PTE_ORDER) / माप(pte_t) / 2)
#अन्यथा
# define PTRS_PER_PTE	((PAGE_SIZE << PTE_ORDER) / माप(pte_t))
#पूर्ण_अगर

#घोषणा USER_PTRS_PER_PGD	(0x80000000UL/PGसूची_SIZE)
#घोषणा FIRST_USER_ADDRESS	0UL

#घोषणा VMALLOC_START	  MAP_BASE

#घोषणा PKMAP_END	((FIXADDR_START) & ~((LAST_PKMAP << PAGE_SHIFT)-1))
#घोषणा PKMAP_BASE	(PKMAP_END - PAGE_SIZE * LAST_PKMAP)

#अगर_घोषित CONFIG_HIGHMEM
# define VMALLOC_END	(PKMAP_BASE-2*PAGE_SIZE)
#अन्यथा
# define VMALLOC_END	(FIXADDR_START-2*PAGE_SIZE)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %016Lx.\n", __खाता__, __LINE__, pte_val(e))
#अन्यथा
#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, pte_val(e))
#पूर्ण_अगर
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))

बाह्य व्योम load_pgd(अचिन्हित दीर्घ pg_dir);

बाह्य pte_t invalid_pte_table[PTRS_PER_PTE];

/*
 * Empty pgd/pmd entries poपूर्णांक to the invalid_pte_table.
 */
अटल अंतरभूत पूर्णांक pmd_none(pmd_t pmd)
अणु
	वापस pmd_val(pmd) == (अचिन्हित दीर्घ) invalid_pte_table;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_bad(pmd_t pmd)
अणु
#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	/* pmd_huge(pmd) but अंतरभूत */
	अगर (unlikely(pmd_val(pmd) & _PAGE_HUGE))
		वापस 0;
#पूर्ण_अगर

	अगर (unlikely(pmd_val(pmd) & ~PAGE_MASK))
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	वापस pmd_val(pmd) != (अचिन्हित दीर्घ) invalid_pte_table;
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	pmd_val(*pmdp) = ((अचिन्हित दीर्घ) invalid_pte_table);
पूर्ण

#अगर defined(CONFIG_XPA)

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS 40
#घोषणा pte_pfn(x)		(((अचिन्हित दीर्घ)((x).pte_high >> _PFN_SHIFT)) | (अचिन्हित दीर्घ)((x).pte_low << _PAGE_PRESENT_SHIFT))
अटल अंतरभूत pte_t
pfn_pte(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t pte;

	pte.pte_low = (pfn >> _PAGE_PRESENT_SHIFT) |
				(pgprot_val(prot) & ~_PFNX_MASK);
	pte.pte_high = (pfn << _PFN_SHIFT) |
				(pgprot_val(prot) & ~_PFN_MASK);
	वापस pte;
पूर्ण

#या_अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS 36
#घोषणा pte_pfn(x)		((अचिन्हित दीर्घ)((x).pte_high >> 6))

अटल अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t pte;

	pte.pte_high = (pfn << 6) | (pgprot_val(prot) & 0x3f);
	pte.pte_low = pgprot_val(prot);

	वापस pte;
पूर्ण

#अन्यथा

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS 32
#अगर_घोषित CONFIG_CPU_VR41XX
#घोषणा pte_pfn(x)		((अचिन्हित दीर्घ)((x).pte >> (PAGE_SHIFT + 2)))
#घोषणा pfn_pte(pfn, prot)	__pte(((pfn) << (PAGE_SHIFT + 2)) | pgprot_val(prot))
#अन्यथा
#घोषणा pte_pfn(x)		((अचिन्हित दीर्घ)((x).pte >> _PFN_SHIFT))
#घोषणा pfn_pte(pfn, prot)	__pte(((अचिन्हित दीर्घ दीर्घ)(pfn) << _PFN_SHIFT) | pgprot_val(prot))
#घोषणा pfn_pmd(pfn, prot)	__pmd(((अचिन्हित दीर्घ दीर्घ)(pfn) << _PFN_SHIFT) | pgprot_val(prot))
#पूर्ण_अगर
#पूर्ण_अगर /* defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32) */

#घोषणा pte_page(x)		pfn_to_page(pte_pfn(x))

#अगर defined(CONFIG_CPU_R3K_TLB)

/* Swap entries must have VALID bit cleared. */
#घोषणा __swp_type(x)			(((x).val >> 10) & 0x1f)
#घोषणा __swp_offset(x)			((x).val >> 15)
#घोषणा __swp_entry(type,offset)	((swp_entry_t) अणु ((type) << 10) | ((offset) << 15) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val पूर्ण)

#अन्यथा

#अगर defined(CONFIG_XPA)

/* Swap entries must have VALID and GLOBAL bits cleared. */
#घोषणा __swp_type(x)			(((x).val >> 4) & 0x1f)
#घोषणा __swp_offset(x)			 ((x).val >> 9)
#घोषणा __swp_entry(type,offset)	((swp_entry_t)  अणु ((type) << 4) | ((offset) << 9) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु (pte).pte_high पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु 0, (x).val पूर्ण)

#या_अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)

/* Swap entries must have VALID and GLOBAL bits cleared. */
#घोषणा __swp_type(x)			(((x).val >> 2) & 0x1f)
#घोषणा __swp_offset(x)			 ((x).val >> 7)
#घोषणा __swp_entry(type, offset)	((swp_entry_t)  अणु ((type) << 2) | ((offset) << 7) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु (pte).pte_high पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु 0, (x).val पूर्ण)

#अन्यथा
/*
 * Constraपूर्णांकs:
 *      _PAGE_PRESENT at bit 0
 *      _PAGE_MODIFIED at bit 4
 *      _PAGE_GLOBAL at bit 6
 *      _PAGE_VALID at bit 7
 */
#घोषणा __swp_type(x)			(((x).val >> 8) & 0x1f)
#घोषणा __swp_offset(x)			 ((x).val >> 13)
#घोषणा __swp_entry(type,offset)	((swp_entry_t)	अणु ((type) << 8) | ((offset) << 13) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val पूर्ण)

#पूर्ण_अगर /* defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32) */

#पूर्ण_अगर /* defined(CONFIG_CPU_R3K_TLB) */

#पूर्ण_अगर /* _ASM_PGTABLE_32_H */
