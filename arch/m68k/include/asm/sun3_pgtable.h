<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SUN3_PGTABLE_H
#घोषणा _SUN3_PGTABLE_H

#समावेश <यंत्र/sun3mmu.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/virtconvert.h>
#समावेश <linux/linkage.h>

/*
 * This file contains all the things which change drastically क्रम the sun3
 * pagetable stuff, to aव्योम making too much of a mess of the generic m68k
 * `pgtable.h'; this should only be included from the generic file. --m
 */

/* For भव address to physical address conversion */
#घोषणा VTOP(addr)	__pa(addr)
#घोषणा PTOV(addr)	__va(addr)


#पूर्ण_अगर	/* !__ASSEMBLY__ */

/* These need to be defined क्रम compatibility although the sun3 करोesn't use them */
#घोषणा _PAGE_NOCACHE030 0x040
#घोषणा _CACHEMASK040   (~0x060)
#घोषणा _PAGE_NOCACHE_S 0x040

/* Page protection values within PTE. */
#घोषणा SUN3_PAGE_VALID     (0x80000000)
#घोषणा SUN3_PAGE_WRITEABLE (0x40000000)
#घोषणा SUN3_PAGE_SYSTEM    (0x20000000)
#घोषणा SUN3_PAGE_NOCACHE   (0x10000000)
#घोषणा SUN3_PAGE_ACCESSED  (0x02000000)
#घोषणा SUN3_PAGE_MODIFIED  (0x01000000)


/* Externally used page protection values. */
#घोषणा _PAGE_PRESENT	(SUN3_PAGE_VALID)
#घोषणा _PAGE_ACCESSED	(SUN3_PAGE_ACCESSED)

/* Compound page protection values. */
//toकरो: work out which ones *should* have SUN3_PAGE_NOCACHE and fix...
// is it just PAGE_KERNEL and PAGE_SHARED?
#घोषणा PAGE_NONE	__pgprot(SUN3_PAGE_VALID \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_NOCACHE)
#घोषणा PAGE_SHARED	__pgprot(SUN3_PAGE_VALID \
				 | SUN3_PAGE_WRITEABLE \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_NOCACHE)
#घोषणा PAGE_COPY	__pgprot(SUN3_PAGE_VALID \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_NOCACHE)
#घोषणा PAGE_READONLY	__pgprot(SUN3_PAGE_VALID \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_NOCACHE)
#घोषणा PAGE_KERNEL	__pgprot(SUN3_PAGE_VALID \
				 | SUN3_PAGE_WRITEABLE \
				 | SUN3_PAGE_SYSTEM \
				 | SUN3_PAGE_NOCACHE \
				 | SUN3_PAGE_ACCESSED \
				 | SUN3_PAGE_MODIFIED)
#घोषणा PAGE_INIT	__pgprot(SUN3_PAGE_VALID \
				 | SUN3_PAGE_WRITEABLE \
				 | SUN3_PAGE_SYSTEM \
				 | SUN3_PAGE_NOCACHE)

/*
 * Page protections क्रम initialising protection_map. The sun3 has only two
 * protection settings, valid (implying पढ़ो and execute) and ग_लिखोable. These
 * are as बंद as we can get...
 */
#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READONLY
#घोषणा __P010	PAGE_COPY
#घोषणा __P011	PAGE_COPY
#घोषणा __P100	PAGE_READONLY
#घोषणा __P101	PAGE_READONLY
#घोषणा __P110	PAGE_COPY
#घोषणा __P111	PAGE_COPY

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READONLY
#घोषणा __S010	PAGE_SHARED
#घोषणा __S011	PAGE_SHARED
#घोषणा __S100	PAGE_READONLY
#घोषणा __S101	PAGE_READONLY
#घोषणा __S110	PAGE_SHARED
#घोषणा __S111	PAGE_SHARED

/* Use these fake page-protections on PMDs. */
#घोषणा SUN3_PMD_VALID	(0x00000001)
#घोषणा SUN3_PMD_MASK	(0x0000003F)
#घोषणा SUN3_PMD_MAGIC	(0x0000002B)

#अगर_अघोषित __ASSEMBLY__

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा mk_pte(page, pgprot) pfn_pte(page_to_pfn(page), (pgprot))

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte_val(pte) = (pte_val(pte) & SUN3_PAGE_CHG_MASK) | pgprot_val(newprot);
	वापस pte;
पूर्ण

#घोषणा pmd_set(pmdp,ptep) करो अणुपूर्ण जबतक (0)

#घोषणा __pte_page(pte) \
((अचिन्हित दीर्घ) __va ((pte_val (pte) & SUN3_PAGE_PGNUM_MASK) << PAGE_SHIFT))

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस (अचिन्हित दीर्घ)__va(pmd_val(pmd) & PAGE_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक pte_none (pte_t pte) अणु वापस !pte_val (pte); पूर्ण
अटल अंतरभूत पूर्णांक pte_present (pte_t pte) अणु वापस pte_val (pte) & SUN3_PAGE_VALID; पूर्ण
अटल अंतरभूत व्योम pte_clear (काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_val (*ptep) = 0;
पूर्ण

#घोषणा pte_pfn(pte)            (pte_val(pte) & SUN3_PAGE_PGNUM_MASK)
#घोषणा pfn_pte(pfn, pgprot) \
(अणु pte_t __pte; pte_val(__pte) = pfn | pgprot_val(pgprot); __pte; पूर्ण)

#घोषणा pte_page(pte)		virt_to_page(__pte_page(pte))
#घोषणा pmd_page(pmd)		virt_to_page(pmd_page_vaddr(pmd))


अटल अंतरभूत पूर्णांक pmd_none2 (pmd_t *pmd) अणु वापस !pmd_val (*pmd); पूर्ण
#घोषणा pmd_none(pmd) pmd_none2(&(pmd))
//अटल अंतरभूत पूर्णांक pmd_bad (pmd_t pmd) अणु वापस (pmd_val (pmd) & SUN3_PMD_MASK) != SUN3_PMD_MAGIC; पूर्ण
अटल अंतरभूत पूर्णांक pmd_bad2 (pmd_t *pmd) अणु वापस 0; पूर्ण
#घोषणा pmd_bad(pmd) pmd_bad2(&(pmd))
अटल अंतरभूत पूर्णांक pmd_present2 (pmd_t *pmd) अणु वापस pmd_val (*pmd) & SUN3_PMD_VALID; पूर्ण
/* #घोषणा pmd_present(pmd) pmd_present2(&(pmd)) */
#घोषणा pmd_present(pmd) (!pmd_none2(&(pmd)))
अटल अंतरभूत व्योम pmd_clear (pmd_t *pmdp) अणु pmd_val (*pmdp) = 0; पूर्ण


#घोषणा pte_ERROR(e) \
	pr_err("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, pte_val(e))
#घोषणा pgd_ERROR(e) \
	pr_err("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))


/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not...
 * [we have the full set here even अगर they करोn't change from m68k]
 */
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)		अणु वापस pte_val(pte) & SUN3_PAGE_WRITEABLE; पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)		अणु वापस pte_val(pte) & SUN3_PAGE_MODIFIED; पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte)		अणु वापस pte_val(pte) & SUN3_PAGE_ACCESSED; पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)	अणु pte_val(pte) &= ~SUN3_PAGE_WRITEABLE; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkclean(pte_t pte)	अणु pte_val(pte) &= ~SUN3_PAGE_MODIFIED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkold(pte_t pte)	अणु pte_val(pte) &= ~SUN3_PAGE_ACCESSED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)	अणु pte_val(pte) |= SUN3_PAGE_WRITEABLE; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)	अणु pte_val(pte) |= SUN3_PAGE_MODIFIED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)	अणु pte_val(pte) |= SUN3_PAGE_ACCESSED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mknocache(pte_t pte)	अणु pte_val(pte) |= SUN3_PAGE_NOCACHE; वापस pte; पूर्ण
// use this version when caches work...
//अटल अंतरभूत pte_t pte_mkcache(pte_t pte)	अणु pte_val(pte) &= SUN3_PAGE_NOCACHE; वापस pte; पूर्ण
// until then, use:
अटल अंतरभूत pte_t pte_mkcache(pte_t pte)	अणु वापस pte; पूर्ण

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];
बाह्य pgd_t kernel_pg_dir[PTRS_PER_PGD];

/* Macros to (de)स्थिरruct the fake PTEs representing swap pages. */
#घोषणा __swp_type(x)		((x).val & 0x7F)
#घोषणा __swp_offset(x)		(((x).val) >> 7)
#घोषणा __swp_entry(type,offset) ((swp_entry_t) अणु ((type) | ((offset) << 7)) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)

#पूर्ण_अगर	/* !__ASSEMBLY__ */
#पूर्ण_अगर	/* !_SUN3_PGTABLE_H */
