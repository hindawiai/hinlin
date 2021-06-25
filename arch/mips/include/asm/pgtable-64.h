<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 2003 Ralf Baechle
 * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_PGTABLE_64_H
#घोषणा _ASM_PGTABLE_64_H

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/fixmap.h>

#अगर CONFIG_PGTABLE_LEVELS == 2
#समावेश <यंत्र-generic/pgtable-nopmd.h>
#या_अगर CONFIG_PGTABLE_LEVELS == 3
#समावेश <यंत्र-generic/pgtable-nopud.h>
#अन्यथा
#समावेश <यंत्र-generic/pgtable-nop4d.h>
#पूर्ण_अगर

/*
 * Each address space has 2 4K pages as its page directory, giving 1024
 * (== PTRS_PER_PGD) 8 byte poपूर्णांकers to pmd tables. Each pmd table is a
 * single 4K page, giving 512 (== PTRS_PER_PMD) 8 byte poपूर्णांकers to page
 * tables. Each page table is also a single 4K page, giving 512 (==
 * PTRS_PER_PTE) 8 byte ptes. Each pud entry is initialized to poपूर्णांक to
 * invalid_pmd_table, each pmd entry is initialized to poपूर्णांक to
 * invalid_pte_table, each pte is initialized to 0.
 *
 * Kernel mappings: kernel mappings are held in the swapper_pg_table.
 * The layout is identical to userspace except it's indexed with the
 * fault address - VMALLOC_START.
 */


/* PGसूची_SHIFT determines what a third-level page table entry can map */
#अगर_घोषित __PAGETABLE_PMD_FOLDED
#घोषणा PGसूची_SHIFT	(PAGE_SHIFT + PAGE_SHIFT + PTE_ORDER - 3)
#अन्यथा

/* PMD_SHIFT determines the size of the area a second-level page table can map */
#घोषणा PMD_SHIFT	(PAGE_SHIFT + (PAGE_SHIFT + PTE_ORDER - 3))
#घोषणा PMD_SIZE	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))

# अगरdef __PAGETABLE_PUD_FOLDED
# define PGसूची_SHIFT	(PMD_SHIFT + (PAGE_SHIFT + PMD_ORDER - 3))
# endअगर
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
#घोषणा PUD_SHIFT	(PMD_SHIFT + (PAGE_SHIFT + PMD_ORDER - 3))
#घोषणा PUD_SIZE	(1UL << PUD_SHIFT)
#घोषणा PUD_MASK	(~(PUD_SIZE-1))
#घोषणा PGसूची_SHIFT	(PUD_SHIFT + (PAGE_SHIFT + PUD_ORDER - 3))
#पूर्ण_अगर

#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/*
 * For 4kB page size we use a 3 level page tree and an 8kB pud, which
 * permits us mapping 40 bits of भव address space.
 *
 * We used to implement 41 bits by having an order 1 pmd level but that seemed
 * rather poपूर्णांकless.
 *
 * For 8kB page size we use a 3 level page tree which permits a total of
 * 8TB of address space.  Alternatively a 33-bit / 8GB organization using
 * two levels would be easy to implement.
 *
 * For 16kB page size we use a 2 level page tree which permits a total of
 * 36 bits of भव address space.  We could add a third level but it seems
 * like at the moment there's no need क्रम this.
 *
 * For 64kB page size we use a 2 level page table tree क्रम a total of 42 bits
 * of भव address space.
 */
#अगर_घोषित CONFIG_PAGE_SIZE_4KB
# अगरdef CONFIG_MIPS_VA_BITS_48
#  define PGD_ORDER		0
#  define PUD_ORDER		0
# अन्यथा
#  define PGD_ORDER		1
#  define PUD_ORDER		aieeee_attempt_to_allocate_pud
# endअगर
#घोषणा PMD_ORDER		0
#घोषणा PTE_ORDER		0
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_8KB
#घोषणा PGD_ORDER		0
#घोषणा PUD_ORDER		aieeee_attempt_to_allocate_pud
#घोषणा PMD_ORDER		0
#घोषणा PTE_ORDER		0
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_16KB
#अगर_घोषित CONFIG_MIPS_VA_BITS_48
#घोषणा PGD_ORDER               1
#अन्यथा
#घोषणा PGD_ORDER               0
#पूर्ण_अगर
#घोषणा PUD_ORDER		aieeee_attempt_to_allocate_pud
#घोषणा PMD_ORDER		0
#घोषणा PTE_ORDER		0
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_32KB
#घोषणा PGD_ORDER		0
#घोषणा PUD_ORDER		aieeee_attempt_to_allocate_pud
#घोषणा PMD_ORDER		0
#घोषणा PTE_ORDER		0
#पूर्ण_अगर
#अगर_घोषित CONFIG_PAGE_SIZE_64KB
#घोषणा PGD_ORDER		0
#घोषणा PUD_ORDER		aieeee_attempt_to_allocate_pud
#अगर_घोषित CONFIG_MIPS_VA_BITS_48
#घोषणा PMD_ORDER		0
#अन्यथा
#घोषणा PMD_ORDER		aieeee_attempt_to_allocate_pmd
#पूर्ण_अगर
#घोषणा PTE_ORDER		0
#पूर्ण_अगर

#घोषणा PTRS_PER_PGD	((PAGE_SIZE << PGD_ORDER) / माप(pgd_t))
#अगर_अघोषित __PAGETABLE_PUD_FOLDED
#घोषणा PTRS_PER_PUD	((PAGE_SIZE << PUD_ORDER) / माप(pud_t))
#पूर्ण_अगर
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
#घोषणा PTRS_PER_PMD	((PAGE_SIZE << PMD_ORDER) / माप(pmd_t))
#पूर्ण_अगर
#घोषणा PTRS_PER_PTE	((PAGE_SIZE << PTE_ORDER) / माप(pte_t))

#घोषणा USER_PTRS_PER_PGD       ((TASK_SIZE64 / PGसूची_SIZE)?(TASK_SIZE64 / PGसूची_SIZE):1)
#घोषणा FIRST_USER_ADDRESS	0UL

/*
 * TLB refill handlers also map the vदो_स्मृति area पूर्णांकo xuseg.  Aव्योम
 * the first couple of pages so शून्य poपूर्णांकer dereferences will still
 * reliably trap.
 */
#घोषणा VMALLOC_START		(MAP_BASE + (2 * PAGE_SIZE))
#घोषणा VMALLOC_END	\
	(MAP_BASE + \
	 min(PTRS_PER_PGD * PTRS_PER_PUD * PTRS_PER_PMD * PTRS_PER_PTE * PAGE_SIZE, \
	     (1UL << cpu_vmbits)) - (1UL << 32))

#अगर defined(CONFIG_MODULES) && defined(KBUILD_64BIT_SYM32) && \
	VMALLOC_START != CKSSEG
/* Load modules पूर्णांकo 32bit-compatible segment. */
#घोषणा MODULE_START	CKSSEG
#घोषणा MODULE_END	(FIXADDR_START-2*PAGE_SIZE)
#पूर्ण_अगर

#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %016lx.\n", __खाता__, __LINE__, pte_val(e))
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
#घोषणा pmd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pmd %016lx.\n", __खाता__, __LINE__, pmd_val(e))
#पूर्ण_अगर
#अगर_अघोषित __PAGETABLE_PUD_FOLDED
#घोषणा pud_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pud %016lx.\n", __खाता__, __LINE__, pud_val(e))
#पूर्ण_अगर
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pgd %016lx.\n", __खाता__, __LINE__, pgd_val(e))

बाह्य pte_t invalid_pte_table[PTRS_PER_PTE];

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
/*
 * For 4-level pagetables we defines these ourselves, क्रम 3-level the
 * definitions are below, क्रम 2-level the
 * definitions are supplied by <यंत्र-generic/pgtable-nopmd.h>.
 */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pud; पूर्ण pud_t;
#घोषणा pud_val(x)	((x).pud)
#घोषणा __pud(x)	((pud_t) अणु (x) पूर्ण)

बाह्य pud_t invalid_pud_table[PTRS_PER_PUD];

/*
 * Empty pgd entries poपूर्णांक to the invalid_pud_table.
 */
अटल अंतरभूत पूर्णांक p4d_none(p4d_t p4d)
अणु
	वापस p4d_val(p4d) == (अचिन्हित दीर्घ)invalid_pud_table;
पूर्ण

अटल अंतरभूत पूर्णांक p4d_bad(p4d_t p4d)
अणु
	अगर (unlikely(p4d_val(p4d) & ~PAGE_MASK))
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक p4d_present(p4d_t p4d)
अणु
	वापस p4d_val(p4d) != (अचिन्हित दीर्घ)invalid_pud_table;
पूर्ण

अटल अंतरभूत व्योम p4d_clear(p4d_t *p4dp)
अणु
	p4d_val(*p4dp) = (अचिन्हित दीर्घ)invalid_pud_table;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ p4d_page_vaddr(p4d_t p4d)
अणु
	वापस p4d_val(p4d);
पूर्ण

#घोषणा p4d_phys(p4d)		virt_to_phys((व्योम *)p4d_val(p4d))
#घोषणा p4d_page(p4d)		(pfn_to_page(p4d_phys(p4d) >> PAGE_SHIFT))

#घोषणा p4d_index(address)	(((address) >> P4D_SHIFT) & (PTRS_PER_P4D - 1))

अटल अंतरभूत व्योम set_p4d(p4d_t *p4d, p4d_t p4dval)
अणु
	*p4d = p4dval;
पूर्ण

#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
/*
 * For 3-level pagetables we defines these ourselves, क्रम 2-level the
 * definitions are supplied by <यंत्र-generic/pgtable-nopmd.h>.
 */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
#घोषणा pmd_val(x)	((x).pmd)
#घोषणा __pmd(x)	((pmd_t) अणु (x) पूर्ण )


बाह्य pmd_t invalid_pmd_table[PTRS_PER_PMD];
#पूर्ण_अगर

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
#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	अगर (unlikely(pmd_val(pmd) & _PAGE_HUGE))
		वापस pmd_val(pmd) & _PAGE_PRESENT;
#पूर्ण_अगर

	वापस pmd_val(pmd) != (अचिन्हित दीर्घ) invalid_pte_table;
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	pmd_val(*pmdp) = ((अचिन्हित दीर्घ) invalid_pte_table);
पूर्ण
#अगर_अघोषित __PAGETABLE_PMD_FOLDED

/*
 * Empty pud entries poपूर्णांक to the invalid_pmd_table.
 */
अटल अंतरभूत पूर्णांक pud_none(pud_t pud)
अणु
	वापस pud_val(pud) == (अचिन्हित दीर्घ) invalid_pmd_table;
पूर्ण

अटल अंतरभूत पूर्णांक pud_bad(pud_t pud)
अणु
	वापस pud_val(pud) & ~PAGE_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक pud_present(pud_t pud)
अणु
	वापस pud_val(pud) != (अचिन्हित दीर्घ) invalid_pmd_table;
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pudp)
अणु
	pud_val(*pudp) = ((अचिन्हित दीर्घ) invalid_pmd_table);
पूर्ण
#पूर्ण_अगर

#घोषणा pte_page(x)		pfn_to_page(pte_pfn(x))

#अगर_घोषित CONFIG_CPU_VR41XX
#घोषणा pte_pfn(x)		((अचिन्हित दीर्घ)((x).pte >> (PAGE_SHIFT + 2)))
#घोषणा pfn_pte(pfn, prot)	__pte(((pfn) << (PAGE_SHIFT + 2)) | pgprot_val(prot))
#अन्यथा
#घोषणा pte_pfn(x)		((अचिन्हित दीर्घ)((x).pte >> _PFN_SHIFT))
#घोषणा pfn_pte(pfn, prot)	__pte(((pfn) << _PFN_SHIFT) | pgprot_val(prot))
#घोषणा pfn_pmd(pfn, prot)	__pmd(((pfn) << _PFN_SHIFT) | pgprot_val(prot))
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
अटल अंतरभूत अचिन्हित दीर्घ pud_page_vaddr(pud_t pud)
अणु
	वापस pud_val(pud);
पूर्ण
#घोषणा pud_phys(pud)		virt_to_phys((व्योम *)pud_val(pud))
#घोषणा pud_page(pud)		(pfn_to_page(pud_phys(pud) >> PAGE_SHIFT))

#पूर्ण_अगर

/*
 * Initialize a new pgd / pmd table with invalid poपूर्णांकers.
 */
बाह्य व्योम pgd_init(अचिन्हित दीर्घ page);
बाह्य व्योम pud_init(अचिन्हित दीर्घ page, अचिन्हित दीर्घ pagetable);
बाह्य व्योम pmd_init(अचिन्हित दीर्घ page, अचिन्हित दीर्घ pagetable);

/*
 * Non-present pages:  high 40 bits are offset, next 8 bits type,
 * low 16 bits zero.
 */
अटल अंतरभूत pte_t mk_swap_pte(अचिन्हित दीर्घ type, अचिन्हित दीर्घ offset)
अणु pte_t pte; pte_val(pte) = (type << 16) | (offset << 24); वापस pte; पूर्ण

#घोषणा __swp_type(x)		(((x).val >> 16) & 0xff)
#घोषणा __swp_offset(x)		((x).val >> 24)
#घोषणा __swp_entry(type, offset) ((swp_entry_t) अणु pte_val(mk_swap_pte((type), (offset))) पूर्ण)
#घोषणा __pte_to_swp_entry(pte) ((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)

#पूर्ण_अगर /* _ASM_PGTABLE_64_H */
