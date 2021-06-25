<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MCF_PGTABLE_H
#घोषणा _MCF_PGTABLE_H

#समावेश <यंत्र/mcfmmu.h>
#समावेश <यंत्र/page.h>

/*
 * MMUDR bits, in proper place. We ग_लिखो these directly पूर्णांकo the MMUDR
 * after masking from the pte.
 */
#घोषणा CF_PAGE_LOCKED		MMUDR_LK	/* 0x00000002 */
#घोषणा CF_PAGE_EXEC		MMUDR_X		/* 0x00000004 */
#घोषणा CF_PAGE_WRITABLE	MMUDR_W		/* 0x00000008 */
#घोषणा CF_PAGE_READABLE	MMUDR_R		/* 0x00000010 */
#घोषणा CF_PAGE_SYSTEM		MMUDR_SP	/* 0x00000020 */
#घोषणा CF_PAGE_COPYBACK	MMUDR_CM_CCB	/* 0x00000040 */
#घोषणा CF_PAGE_NOCACHE		MMUDR_CM_NCP	/* 0x00000080 */

#घोषणा CF_CACHEMASK		(~MMUDR_CM_CCB)
#घोषणा CF_PAGE_MMUDR_MASK	0x000000fe

#घोषणा _PAGE_NOCACHE030	CF_PAGE_NOCACHE

/*
 * MMUTR bits, need shअगरting करोwn.
 */
#घोषणा CF_PAGE_MMUTR_MASK	0x00000c00
#घोषणा CF_PAGE_MMUTR_SHIFT	10

#घोषणा CF_PAGE_VALID		(MMUTR_V << CF_PAGE_MMUTR_SHIFT)
#घोषणा CF_PAGE_SHARED		(MMUTR_SG << CF_PAGE_MMUTR_SHIFT)

/*
 * Fake bits, not implemented in CF, will get masked out beक्रमe
 * hitting hardware.
 */
#घोषणा CF_PAGE_सूचीTY		0x00000001
#घोषणा CF_PAGE_ACCESSED	0x00001000

#घोषणा _PAGE_CACHE040		0x020   /* 68040 cache mode, cachable, copyback */
#घोषणा _PAGE_NOCACHE_S		0x040   /* 68040 no-cache mode, serialized */
#घोषणा _PAGE_NOCACHE		0x060   /* 68040 cache mode, non-serialized */
#घोषणा _PAGE_CACHE040W		0x000   /* 68040 cache mode, cachable, ग_लिखो-through */
#घोषणा _DESCTYPE_MASK		0x003
#घोषणा _CACHEMASK040		(~0x060)
#घोषणा _PAGE_GLOBAL040		0x400   /* 68040 global bit, used क्रम kva descs */

/*
 * Externally used page protection values.
 */
#घोषणा _PAGE_PRESENT	(CF_PAGE_VALID)
#घोषणा _PAGE_ACCESSED	(CF_PAGE_ACCESSED)
#घोषणा _PAGE_सूचीTY	(CF_PAGE_सूचीTY)
#घोषणा _PAGE_READWRITE (CF_PAGE_READABLE \
				| CF_PAGE_WRITABLE \
				| CF_PAGE_SYSTEM \
				| CF_PAGE_SHARED)

/*
 * Compound page protection values.
 */
#घोषणा PAGE_NONE	__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED)

#घोषणा PAGE_SHARED     __pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_SHARED)

#घोषणा PAGE_INIT	__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_READABLE \
				 | CF_PAGE_WRITABLE \
				 | CF_PAGE_EXEC \
				 | CF_PAGE_SYSTEM)

#घोषणा PAGE_KERNEL	__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_READABLE \
				 | CF_PAGE_WRITABLE \
				 | CF_PAGE_EXEC \
				 | CF_PAGE_SYSTEM \
				 | CF_PAGE_SHARED)

#घोषणा PAGE_COPY	__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_READABLE \
				 | CF_PAGE_सूचीTY)

/*
 * Page protections क्रम initialising protection_map. See mm/mmap.c
 * क्रम use. In general, the bit positions are xwr, and P-items are
 * निजी, the S-items are shared.
 */
#घोषणा __P000		PAGE_NONE
#घोषणा __P001		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_READABLE)
#घोषणा __P010		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_WRITABLE)
#घोषणा __P011		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_READABLE \
				 | CF_PAGE_WRITABLE)
#घोषणा __P100		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_EXEC)
#घोषणा __P101		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_READABLE \
				 | CF_PAGE_EXEC)
#घोषणा __P110		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_WRITABLE \
				 | CF_PAGE_EXEC)
#घोषणा __P111		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_READABLE \
				 | CF_PAGE_WRITABLE \
				 | CF_PAGE_EXEC)

#घोषणा __S000		PAGE_NONE
#घोषणा __S001		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_READABLE)
#घोषणा __S010		PAGE_SHARED
#घोषणा __S011		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_SHARED \
				 | CF_PAGE_READABLE)
#घोषणा __S100		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_EXEC)
#घोषणा __S101		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_READABLE \
				 | CF_PAGE_EXEC)
#घोषणा __S110		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_SHARED \
				 | CF_PAGE_EXEC)
#घोषणा __S111		__pgprot(CF_PAGE_VALID \
				 | CF_PAGE_ACCESSED \
				 | CF_PAGE_SHARED \
				 | CF_PAGE_READABLE \
				 | CF_PAGE_EXEC)

#घोषणा PTE_MASK	PAGE_MASK
#घोषणा CF_PAGE_CHG_MASK (PTE_MASK | CF_PAGE_ACCESSED | CF_PAGE_सूचीTY)

#अगर_अघोषित __ASSEMBLY__

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा mk_pte(page, pgprot) pfn_pte(page_to_pfn(page), (pgprot))

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte_val(pte) = (pte_val(pte) & CF_PAGE_CHG_MASK) | pgprot_val(newprot);
	वापस pte;
पूर्ण

#घोषणा pmd_set(pmdp, ptep) करो अणुपूर्ण जबतक (0)

अटल अंतरभूत व्योम pgd_set(pgd_t *pgdp, pmd_t *pmdp)
अणु
	pgd_val(*pgdp) = virt_to_phys(pmdp);
पूर्ण

#घोषणा __pte_page(pte)	((अचिन्हित दीर्घ) (pte_val(pte) & PAGE_MASK))
#घोषणा pmd_page_vaddr(pmd)	((अचिन्हित दीर्घ) (pmd_val(pmd)))

अटल अंतरभूत पूर्णांक pte_none(pte_t pte)
अणु
	वापस !pte_val(pte);
पूर्ण

अटल अंतरभूत पूर्णांक pte_present(pte_t pte)
अणु
	वापस pte_val(pte) & CF_PAGE_VALID;
पूर्ण

अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
	pte_t *ptep)
अणु
	pte_val(*ptep) = 0;
पूर्ण

#घोषणा pte_pagenr(pte)	((__pte_page(pte) - PAGE_OFFSET) >> PAGE_SHIFT)
#घोषणा pte_page(pte)	virt_to_page(__pte_page(pte))

अटल अंतरभूत पूर्णांक pmd_none2(pmd_t *pmd) अणु वापस !pmd_val(*pmd); पूर्ण
#घोषणा pmd_none(pmd) pmd_none2(&(pmd))
अटल अंतरभूत पूर्णांक pmd_bad2(pmd_t *pmd) अणु वापस 0; पूर्ण
#घोषणा pmd_bad(pmd) pmd_bad2(&(pmd))
#घोषणा pmd_present(pmd) (!pmd_none2(&(pmd)))
अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp) अणु pmd_val(*pmdp) = 0; पूर्ण

#घोषणा pte_ERROR(e) \
	prपूर्णांकk(KERN_ERR "%s:%d: bad pte %08lx.\n",	\
	__खाता__, __LINE__, pte_val(e))
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk(KERN_ERR "%s:%d: bad pgd %08lx.\n",	\
	__खाता__, __LINE__, pgd_val(e))

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not...
 * [we have the full set here even अगर they करोn't change from m68k]
 */
अटल अंतरभूत पूर्णांक pte_पढ़ो(pte_t pte)
अणु
	वापस pte_val(pte) & CF_PAGE_READABLE;
पूर्ण

अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस pte_val(pte) & CF_PAGE_WRITABLE;
पूर्ण

अटल अंतरभूत पूर्णांक pte_exec(pte_t pte)
अणु
	वापस pte_val(pte) & CF_PAGE_EXEC;
पूर्ण

अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)
अणु
	वापस pte_val(pte) & CF_PAGE_सूचीTY;
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस pte_val(pte) & CF_PAGE_ACCESSED;
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	pte_val(pte) &= ~CF_PAGE_WRITABLE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_rdprotect(pte_t pte)
अणु
	pte_val(pte) &= ~CF_PAGE_READABLE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_exprotect(pte_t pte)
अणु
	pte_val(pte) &= ~CF_PAGE_EXEC;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte_val(pte) &= ~CF_PAGE_सूचीTY;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	pte_val(pte) &= ~CF_PAGE_ACCESSED;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte_val(pte) |= CF_PAGE_WRITABLE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkपढ़ो(pte_t pte)
अणु
	pte_val(pte) |= CF_PAGE_READABLE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkexec(pte_t pte)
अणु
	pte_val(pte) |= CF_PAGE_EXEC;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	pte_val(pte) |= CF_PAGE_सूचीTY;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	pte_val(pte) |= CF_PAGE_ACCESSED;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mknocache(pte_t pte)
अणु
	pte_val(pte) |= 0x80 | (pte_val(pte) & ~0x40);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkcache(pte_t pte)
अणु
	pte_val(pte) &= ~CF_PAGE_NOCACHE;
	वापस pte;
पूर्ण

#घोषणा swapper_pg_dir kernel_pg_dir
बाह्य pgd_t kernel_pg_dir[PTRS_PER_PGD];

/*
 * Encode and de-code a swap entry (must be !pte_none(e) && !pte_present(e))
 */
#घोषणा __swp_type(x)		((x).val & 0xFF)
#घोषणा __swp_offset(x)		((x).val >> 11)
#घोषणा __swp_entry(typ, off)	((swp_entry_t) अणु (typ) | \
					(off << 11) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	(__pte((x).val))

#घोषणा pmd_page(pmd)		(pfn_to_page(pmd_val(pmd) >> PAGE_SHIFT))

#घोषणा pfn_pte(pfn, prot)	__pte(((pfn) << PAGE_SHIFT) | pgprot_val(prot))
#घोषणा pte_pfn(pte)		(pte_val(pte) >> PAGE_SHIFT)

#पूर्ण_अगर	/* !__ASSEMBLY__ */
#पूर्ण_अगर	/* _MCF_PGTABLE_H */
