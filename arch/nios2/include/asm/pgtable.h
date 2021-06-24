<शैली गुरु>
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009 Wind River Systems Inc
 *
 * Based on यंत्र/pgtable-32.h from mips which is:
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 2003 Ralf Baechle
 * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_PGTABLE_H
#घोषणा _ASM_NIOS2_PGTABLE_H

#समावेश <linux/पन.स>
#समावेश <linux/bug.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <यंत्र/pgtable-bits.h>
#समावेश <यंत्र-generic/pgtable-nopmd.h>

#घोषणा FIRST_USER_ADDRESS	0UL

#घोषणा VMALLOC_START		CONFIG_NIOS2_KERNEL_MMU_REGION_BASE
#घोषणा VMALLOC_END		(CONFIG_NIOS2_KERNEL_REGION_BASE - 1)

काष्ठा mm_काष्ठा;

/* Helper macro */
#घोषणा MKP(x, w, r) __pgprot(_PAGE_PRESENT | _PAGE_CACHED |		\
				((x) ? _PAGE_EXEC : 0) |		\
				((r) ? _PAGE_READ : 0) |		\
				((w) ? _PAGE_WRITE : 0))
/*
 * These are the macros that generic kernel code needs
 * (to populate protection_map[])
 */

/* Remove W bit on निजी pages क्रम COW support */
#घोषणा __P000	MKP(0, 0, 0)
#घोषणा __P001	MKP(0, 0, 1)
#घोषणा __P010	MKP(0, 0, 0)	/* COW */
#घोषणा __P011	MKP(0, 0, 1)	/* COW */
#घोषणा __P100	MKP(1, 0, 0)
#घोषणा __P101	MKP(1, 0, 1)
#घोषणा __P110	MKP(1, 0, 0)	/* COW */
#घोषणा __P111	MKP(1, 0, 1)	/* COW */

/* Shared pages can have exact HW mapping */
#घोषणा __S000	MKP(0, 0, 0)
#घोषणा __S001	MKP(0, 0, 1)
#घोषणा __S010	MKP(0, 1, 0)
#घोषणा __S011	MKP(0, 1, 1)
#घोषणा __S100	MKP(1, 0, 0)
#घोषणा __S101	MKP(1, 0, 1)
#घोषणा __S110	MKP(1, 1, 0)
#घोषणा __S111	MKP(1, 1, 1)

/* Used all over the kernel */
#घोषणा PAGE_KERNEL __pgprot(_PAGE_PRESENT | _PAGE_CACHED | _PAGE_READ | \
			     _PAGE_WRITE | _PAGE_EXEC | _PAGE_GLOBAL)

#घोषणा PAGE_SHARED __pgprot(_PAGE_PRESENT | _PAGE_CACHED | _PAGE_READ | \
			     _PAGE_WRITE | _PAGE_ACCESSED)

#घोषणा PAGE_COPY MKP(0, 0, 1)

#घोषणा PGD_ORDER	0
#घोषणा PTE_ORDER	0

#घोषणा PTRS_PER_PGD	((PAGE_SIZE << PGD_ORDER) / माप(pgd_t))
#घोषणा PTRS_PER_PTE	((PAGE_SIZE << PTE_ORDER) / माप(pte_t))

#घोषणा USER_PTRS_PER_PGD	\
	(CONFIG_NIOS2_KERNEL_MMU_REGION_BASE / PGसूची_SIZE)

#घोषणा PGसूची_SHIFT	22
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)];
#घोषणा ZERO_PAGE(vaddr)	(virt_to_page(empty_zero_page))

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];
बाह्य pte_t invalid_pte_table[PAGE_SIZE/माप(pte_t)];

/*
 * (pmds are folded पूर्णांकo puds so this करोesn't get actually called,
 * but the define is needed क्रम a generic अंतरभूत function.)
 */
अटल अंतरभूत व्योम set_pmd(pmd_t *pmdptr, pmd_t pmdval)
अणु
	*pmdptr = pmdval;
पूर्ण

अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)		\
	अणु वापस pte_val(pte) & _PAGE_WRITE; पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)		\
	अणु वापस pte_val(pte) & _PAGE_सूचीTY; पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte)		\
	अणु वापस pte_val(pte) & _PAGE_ACCESSED; पूर्ण

#घोषणा pgprot_noncached pgprot_noncached

अटल अंतरभूत pgprot_t pgprot_noncached(pgprot_t _prot)
अणु
	अचिन्हित दीर्घ prot = pgprot_val(_prot);

	prot &= ~_PAGE_CACHED;

	वापस __pgprot(prot);
पूर्ण

अटल अंतरभूत पूर्णांक pte_none(pte_t pte)
अणु
	वापस !(pte_val(pte) & ~(_PAGE_GLOBAL|0xf));
पूर्ण

अटल अंतरभूत पूर्णांक pte_present(pte_t pte)	\
	अणु वापस pte_val(pte) & _PAGE_PRESENT; पूर्ण

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_WRITE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_सूचीTY;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_ACCESSED;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_WRITE;
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

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	स्थिर अचिन्हित दीर्घ mask = _PAGE_READ | _PAGE_WRITE | _PAGE_EXEC;

	pte_val(pte) = (pte_val(pte) & ~mask) | (pgprot_val(newprot) & mask);
	वापस pte;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) != (अचिन्हित दीर्घ) invalid_pte_table)
			&& (pmd_val(pmd) != 0UL);
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	pmd_val(*pmdp) = (अचिन्हित दीर्घ) invalid_pte_table;
पूर्ण

#घोषणा pte_pfn(pte)		(pte_val(pte) & 0xfffff)
#घोषणा pfn_pte(pfn, prot)	(__pte(pfn | pgprot_val(prot)))
#घोषणा pte_page(pte)		(pfn_to_page(pte_pfn(pte)))

/*
 * Store a linux PTE पूर्णांकo the linux page table.
 */
अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pteval)
अणु
	*ptep = pteval;
पूर्ण

अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep, pte_t pteval)
अणु
	अचिन्हित दीर्घ paddr = (अचिन्हित दीर्घ)page_to_virt(pte_page(pteval));

	flush_dcache_range(paddr, paddr + PAGE_SIZE);
	set_pte(ptep, pteval);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_none(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) ==
		(अचिन्हित दीर्घ) invalid_pte_table) || (pmd_val(pmd) == 0UL);
पूर्ण

#घोषणा pmd_bad(pmd)	(pmd_val(pmd) & ~PAGE_MASK)

अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t null;

	pte_val(null) = (addr >> PAGE_SHIFT) & 0xf;

	set_pte_at(mm, addr, ptep, null);
पूर्ण

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा mk_pte(page, prot)	(pfn_pte(page_to_pfn(page), prot))

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा pmd_phys(pmd)		virt_to_phys((व्योम *)pmd_val(pmd))
#घोषणा pmd_page(pmd)		(pfn_to_page(pmd_phys(pmd) >> PAGE_SHIFT))

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस pmd_val(pmd);
पूर्ण

#घोषणा pte_ERROR(e) \
	pr_err("%s:%d: bad pte %08lx.\n", \
		__खाता__, __LINE__, pte_val(e))
#घोषणा pgd_ERROR(e) \
	pr_err("%s:%d: bad pgd %08lx.\n", \
		__खाता__, __LINE__, pgd_val(e))

/*
 * Encode and decode a swap entry (must be !pte_none(pte) && !pte_present(pte):
 *
 * 31 30 29 28 27 26 25 24 23 22 21 20 19 18 ...  1  0
 *  0  0  0  0 type.  0  0  0  0  0  0 offset.........
 *
 * This gives us up to 2**2 = 4 swap files and 2**20 * 4K = 4G per swap file.
 *
 * Note that the offset field is always non-zero, thus !pte_none(pte) is always
 * true.
 */
#घोषणा __swp_type(swp)		(((swp).val >> 26) & 0x3)
#घोषणा __swp_offset(swp)	((swp).val & 0xfffff)
#घोषणा __swp_entry(type, off)	((swp_entry_t) अणु (((type) & 0x3) << 26) \
						 | ((off) & 0xfffff) पूर्ण)
#घोषणा __swp_entry_to_pte(swp)	((pte_t) अणु (swp).val पूर्ण)
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)

#घोषणा kern_addr_valid(addr)		(1)

बाह्य व्योम __init paging_init(व्योम);
बाह्य व्योम __init mmu_init(व्योम);

बाह्य व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ address, pte_t *pte);

#पूर्ण_अगर /* _ASM_NIOS2_PGTABLE_H */
