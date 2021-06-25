<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_PGTABLE_H
#घोषणा __ASM_CSKY_PGTABLE_H

#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <abi/pgtable-bits.h>
#समावेश <यंत्र-generic/pgtable-nopmd.h>

#घोषणा PGसूची_SHIFT		22
#घोषणा PGसूची_SIZE		(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK		(~(PGसूची_SIZE-1))

#घोषणा USER_PTRS_PER_PGD	(PAGE_OFFSET/PGसूची_SIZE)
#घोषणा FIRST_USER_ADDRESS	0UL

/*
 * C-SKY is two-level paging काष्ठाure:
 */
#घोषणा PGD_ORDER	0
#घोषणा PTE_ORDER	0

#घोषणा PTRS_PER_PGD	((PAGE_SIZE << PGD_ORDER) / माप(pgd_t))
#घोषणा PTRS_PER_PMD	1
#घोषणा PTRS_PER_PTE	((PAGE_SIZE << PTE_ORDER) / माप(pte_t))

#घोषणा pte_ERROR(e) \
	pr_err("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, (e).pte_low)
#घोषणा pgd_ERROR(e) \
	pr_err("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))

#घोषणा pmd_page(pmd)	(pfn_to_page(pmd_phys(pmd) >> PAGE_SHIFT))
#घोषणा pte_clear(mm, addr, ptep)	set_pte((ptep), \
	(((अचिन्हित पूर्णांक) addr >= PAGE_OFFSET) ? __pte(_PAGE_GLOBAL) : __pte(0)))
#घोषणा pte_none(pte)		(!(pte_val(pte) & ~_PAGE_GLOBAL))
#घोषणा pte_present(pte)	(pte_val(pte) & _PAGE_PRESENT)
#घोषणा pte_pfn(x)	((अचिन्हित दीर्घ)((x).pte_low >> PAGE_SHIFT))
#घोषणा pfn_pte(pfn, prot) __pte(((अचिन्हित दीर्घ दीर्घ)(pfn) << PAGE_SHIFT) \
				| pgprot_val(prot))

#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val पूर्ण)

#घोषणा pte_page(x)			pfn_to_page(pte_pfn(x))
#घोषणा __mk_pte(page_nr, pgprot)	__pte(((page_nr) << PAGE_SHIFT) | \
					pgprot_val(pgprot))

/*
 * C-SKY only has VALID and सूचीTY bit in hardware. So we need to use the
 * two bits emulate PRESENT, READ, WRITE, EXEC, MODIFIED, ACCESSED.
 */
#घोषणा _PAGE_BASE	(_PAGE_PRESENT | _PAGE_ACCESSED)

#घोषणा PAGE_NONE	__pgprot(_PAGE_PROT_NONE)
#घोषणा PAGE_READ	__pgprot(_PAGE_BASE | _PAGE_READ | \
				_CACHE_CACHED)
#घोषणा PAGE_WRITE	__pgprot(_PAGE_BASE | _PAGE_READ | _PAGE_WRITE | \
				_CACHE_CACHED)
#घोषणा PAGE_SHARED PAGE_WRITE

#घोषणा PAGE_KERNEL	__pgprot(_PAGE_BASE | _PAGE_READ | _PAGE_VALID | \
				_PAGE_WRITE | _PAGE_सूचीTY | _PAGE_MODIFIED | \
				_PAGE_GLOBAL | \
				_CACHE_CACHED)

#घोषणा _PAGE_IOREMAP		(_PAGE_BASE | _PAGE_READ | _PAGE_VALID | \
				_PAGE_WRITE | _PAGE_सूचीTY | _PAGE_MODIFIED | \
				_PAGE_GLOBAL | \
				_CACHE_UNCACHED | _PAGE_SO)

#घोषणा _PAGE_CHG_MASK	(~(अचिन्हित दीर्घ) \
				(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | \
				_CACHE_MASK | _PAGE_GLOBAL))

#घोषणा MAX_SWAPखाताS_CHECK() \
		BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT != 5)

#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READ
#घोषणा __P010	PAGE_READ
#घोषणा __P011	PAGE_READ
#घोषणा __P100	PAGE_READ
#घोषणा __P101	PAGE_READ
#घोषणा __P110	PAGE_READ
#घोषणा __P111	PAGE_READ

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READ
#घोषणा __S010	PAGE_WRITE
#घोषणा __S011	PAGE_WRITE
#घोषणा __S100	PAGE_READ
#घोषणा __S101	PAGE_READ
#घोषणा __S110	PAGE_WRITE
#घोषणा __S111	PAGE_WRITE

बाह्य अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)];
#घोषणा ZERO_PAGE(vaddr)	(virt_to_page(empty_zero_page))

बाह्य व्योम load_pgd(अचिन्हित दीर्घ pg_dir);
बाह्य pte_t invalid_pte_table[PTRS_PER_PTE];

अटल अंतरभूत व्योम set_pte(pte_t *p, pte_t pte)
अणु
	*p = pte;
#अगर defined(CONFIG_CPU_NEED_TLBSYNC)
	dcache_wb_line((u32)p);
#पूर्ण_अगर
	/* prevent out of order excution */
	smp_mb();
पूर्ण
#घोषणा set_pte_at(mm, addr, ptep, pteval) set_pte(ptep, pteval)

अटल अंतरभूत pte_t *pmd_page_vaddr(pmd_t pmd)
अणु
	अचिन्हित दीर्घ ptr;

	ptr = pmd_val(pmd);

	वापस __va(ptr);
पूर्ण

#घोषणा pmd_phys(pmd) pmd_val(pmd)

अटल अंतरभूत व्योम set_pmd(pmd_t *p, pmd_t pmd)
अणु
	*p = pmd;
#अगर defined(CONFIG_CPU_NEED_TLBSYNC)
	dcache_wb_line((u32)p);
#पूर्ण_अगर
	/* prevent specul excute */
	smp_mb();
पूर्ण


अटल अंतरभूत पूर्णांक pmd_none(pmd_t pmd)
अणु
	वापस pmd_val(pmd) == __pa(invalid_pte_table);
पूर्ण

#घोषणा pmd_bad(pmd)	(pmd_val(pmd) & ~PAGE_MASK)

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) != __pa(invalid_pte_table));
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *p)
अणु
	pmd_val(*p) = (__pa(invalid_pte_table));
#अगर defined(CONFIG_CPU_NEED_TLBSYNC)
	dcache_wb_line((u32)p);
#पूर्ण_अगर
पूर्ण

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
अटल अंतरभूत पूर्णांक pte_पढ़ो(pte_t pte)
अणु
	वापस pte.pte_low & _PAGE_READ;
पूर्ण

अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस (pte).pte_low & _PAGE_WRITE;
पूर्ण

अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)
अणु
	वापस (pte).pte_low & _PAGE_MODIFIED;
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस (pte).pte_low & _PAGE_ACCESSED;
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_WRITE | _PAGE_सूचीTY);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_MODIFIED|_PAGE_सूचीTY);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_ACCESSED|_PAGE_VALID);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_WRITE;
	अगर (pte_val(pte) & _PAGE_MODIFIED)
		pte_val(pte) |= _PAGE_सूचीTY;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_MODIFIED;
	अगर (pte_val(pte) & _PAGE_WRITE)
		pte_val(pte) |= _PAGE_सूचीTY;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_ACCESSED;
	अगर (pte_val(pte) & _PAGE_READ)
		pte_val(pte) |= _PAGE_VALID;
	वापस pte;
पूर्ण

#घोषणा __HAVE_PHYS_MEM_ACCESS_PROT
काष्ठा file;
बाह्य pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t vma_prot);

/*
 * Macro to make mark a page protection value as "uncacheable".  Note
 * that "protection" is really a misnomer here as the protection value
 * contains the memory attribute bits, dirty bits, and various other
 * bits as well.
 */
#घोषणा pgprot_noncached pgprot_noncached

अटल अंतरभूत pgprot_t pgprot_noncached(pgprot_t _prot)
अणु
	अचिन्हित दीर्घ prot = pgprot_val(_prot);

	prot = (prot & ~_CACHE_MASK) | _CACHE_UNCACHED | _PAGE_SO;

	वापस __pgprot(prot);
पूर्ण

#घोषणा pgprot_ग_लिखोcombine pgprot_ग_लिखोcombine
अटल अंतरभूत pgprot_t pgprot_ग_लिखोcombine(pgprot_t _prot)
अणु
	अचिन्हित दीर्घ prot = pgprot_val(_prot);

	prot = (prot & ~_CACHE_MASK) | _CACHE_UNCACHED;

	वापस __pgprot(prot);
पूर्ण

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा mk_pte(page, pgprot)    pfn_pte(page_to_pfn(page), (pgprot))
अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	वापस __pte((pte_val(pte) & _PAGE_CHG_MASK) |
		     (pgprot_val(newprot)));
पूर्ण

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];
बाह्य व्योम paging_init(व्योम);

व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		      pte_t *pte);

/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
#घोषणा kern_addr_valid(addr)	(1)

#घोषणा io_remap_pfn_range(vma, vaddr, pfn, size, prot) \
	remap_pfn_range(vma, vaddr, pfn, size, prot)

#पूर्ण_अगर /* __ASM_CSKY_PGTABLE_H */
