<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MOTOROLA_PGTABLE_H
#घोषणा _MOTOROLA_PGTABLE_H


/*
 * Definitions क्रम MMU descriptors
 */
#घोषणा _PAGE_PRESENT	0x001
#घोषणा _PAGE_SHORT	0x002
#घोषणा _PAGE_RONLY	0x004
#घोषणा _PAGE_READWRITE	0x000
#घोषणा _PAGE_ACCESSED	0x008
#घोषणा _PAGE_सूचीTY	0x010
#घोषणा _PAGE_SUPER	0x080	/* 68040 supervisor only */
#घोषणा _PAGE_GLOBAL040	0x400	/* 68040 global bit, used क्रम kva descs */
#घोषणा _PAGE_NOCACHE030 0x040	/* 68030 no-cache mode */
#घोषणा _PAGE_NOCACHE	0x060	/* 68040 cache mode, non-serialized */
#घोषणा _PAGE_NOCACHE_S	0x040	/* 68040 no-cache mode, serialized */
#घोषणा _PAGE_CACHE040	0x020	/* 68040 cache mode, cachable, copyback */
#घोषणा _PAGE_CACHE040W	0x000	/* 68040 cache mode, cachable, ग_लिखो-through */

#घोषणा _DESCTYPE_MASK	0x003

#घोषणा _CACHEMASK040	(~0x060)

/*
 * Currently set to the minimum alignment of table poपूर्णांकers (256 bytes).
 * The hardware only uses the low 4 bits क्रम state:
 *
 *    3 - Used
 *    2 - Write Protected
 *  0,1 - Descriptor Type
 *
 * and has the rest of the bits reserved.
 */
#घोषणा _TABLE_MASK	(0xffffff00)

#घोषणा _PAGE_TABLE	(_PAGE_SHORT)
#घोषणा _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_ACCESSED | _PAGE_सूचीTY | _PAGE_NOCACHE)

#घोषणा _PAGE_PROTNONE	0x004

#अगर_अघोषित __ASSEMBLY__

/* This is the cache mode to be used क्रम pages containing page descriptors क्रम
 * processors >= '040. It is in pte_mknocache(), and the variable is defined
 * and initialized in head.S */
बाह्य पूर्णांक m68k_pgtable_cachemode;

/* This is the cache mode क्रम normal pages, क्रम supervisor access on
 * processors >= '040. It is used in pte_mkcache(), and the variable is
 * defined and initialized in head.S */

#अगर defined(CPU_M68060_ONLY) && defined(CONFIG_060_WRITETHROUGH)
#घोषणा m68k_supervisor_cachemode _PAGE_CACHE040W
#या_अगर defined(CPU_M68040_OR_M68060_ONLY)
#घोषणा m68k_supervisor_cachemode _PAGE_CACHE040
#या_अगर defined(CPU_M68020_OR_M68030_ONLY)
#घोषणा m68k_supervisor_cachemode 0
#अन्यथा
बाह्य पूर्णांक m68k_supervisor_cachemode;
#पूर्ण_अगर

#अगर defined(CPU_M68040_OR_M68060_ONLY)
#घोषणा mm_cachebits _PAGE_CACHE040
#या_अगर defined(CPU_M68020_OR_M68030_ONLY)
#घोषणा mm_cachebits 0
#अन्यथा
बाह्य अचिन्हित दीर्घ mm_cachebits;
#पूर्ण_अगर

#घोषणा PAGE_NONE	__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED | mm_cachebits)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | mm_cachebits)
#घोषणा PAGE_COPY	__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED | mm_cachebits)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED | mm_cachebits)
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_PRESENT | _PAGE_सूचीTY | _PAGE_ACCESSED | mm_cachebits)

/* Alternate definitions that are compile समय स्थिरants, क्रम
   initializing protection_map.  The cachebits are fixed later.  */
#घोषणा PAGE_NONE_C	__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED)
#घोषणा PAGE_SHARED_C	__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
#घोषणा PAGE_COPY_C	__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED)
#घोषणा PAGE_READONLY_C	__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED)

/*
 * The m68k can't करो page protection क्रम execute, and considers that the same are पढ़ो.
 * Also, ग_लिखो permissions imply पढ़ो permissions. This is the बंदst we can get..
 */
#घोषणा __P000	PAGE_NONE_C
#घोषणा __P001	PAGE_READONLY_C
#घोषणा __P010	PAGE_COPY_C
#घोषणा __P011	PAGE_COPY_C
#घोषणा __P100	PAGE_READONLY_C
#घोषणा __P101	PAGE_READONLY_C
#घोषणा __P110	PAGE_COPY_C
#घोषणा __P111	PAGE_COPY_C

#घोषणा __S000	PAGE_NONE_C
#घोषणा __S001	PAGE_READONLY_C
#घोषणा __S010	PAGE_SHARED_C
#घोषणा __S011	PAGE_SHARED_C
#घोषणा __S100	PAGE_READONLY_C
#घोषणा __S101	PAGE_READONLY_C
#घोषणा __S110	PAGE_SHARED_C
#घोषणा __S111	PAGE_SHARED_C

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा mk_pte(page, pgprot) pfn_pte(page_to_pfn(page), (pgprot))

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte_val(pte) = (pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot);
	वापस pte;
पूर्ण

अटल अंतरभूत व्योम pmd_set(pmd_t *pmdp, pte_t *ptep)
अणु
	pmd_val(*pmdp) = virt_to_phys(ptep) | _PAGE_TABLE | _PAGE_ACCESSED;
पूर्ण

अटल अंतरभूत व्योम pud_set(pud_t *pudp, pmd_t *pmdp)
अणु
	pud_val(*pudp) = _PAGE_TABLE | _PAGE_ACCESSED | __pa(pmdp);
पूर्ण

#घोषणा __pte_page(pte) ((अचिन्हित दीर्घ)__va(pte_val(pte) & PAGE_MASK))
#घोषणा pmd_page_vaddr(pmd) ((अचिन्हित दीर्घ)__va(pmd_val(pmd) & _TABLE_MASK))
#घोषणा pud_page_vaddr(pud) ((अचिन्हित दीर्घ)__va(pud_val(pud) & _TABLE_MASK))


#घोषणा pte_none(pte)		(!pte_val(pte))
#घोषणा pte_present(pte)	(pte_val(pte) & (_PAGE_PRESENT | _PAGE_PROTNONE))
#घोषणा pte_clear(mm,addr,ptep)		(अणु pte_val(*(ptep)) = 0; पूर्ण)

#घोषणा pte_page(pte)		virt_to_page(__va(pte_val(pte)))
#घोषणा pte_pfn(pte)		(pte_val(pte) >> PAGE_SHIFT)
#घोषणा pfn_pte(pfn, prot)	__pte(((pfn) << PAGE_SHIFT) | pgprot_val(prot))

#घोषणा pmd_none(pmd)		(!pmd_val(pmd))
#घोषणा pmd_bad(pmd)		((pmd_val(pmd) & _DESCTYPE_MASK) != _PAGE_TABLE)
#घोषणा pmd_present(pmd)	(pmd_val(pmd) & _PAGE_TABLE)
#घोषणा pmd_clear(pmdp)		(अणु pmd_val(*pmdp) = 0; पूर्ण)

/*
 * m68k करोes not have huge pages (020/030 actually could), but generic code
 * expects pmd_page() to exists, only to then DCE it all. Provide a dummy to
 * make the compiler happy.
 */
#घोषणा pmd_page(pmd)		शून्य


#घोषणा pud_none(pud)		(!pud_val(pud))
#घोषणा pud_bad(pud)		((pud_val(pud) & _DESCTYPE_MASK) != _PAGE_TABLE)
#घोषणा pud_present(pud)	(pud_val(pud) & _PAGE_TABLE)
#घोषणा pud_clear(pudp)		(अणु pud_val(*pudp) = 0; पूर्ण)
#घोषणा pud_page(pud)		(mem_map + ((अचिन्हित दीर्घ)(__va(pud_val(pud)) - PAGE_OFFSET) >> PAGE_SHIFT))

#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, pte_val(e))
#घोषणा pmd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pmd %08lx.\n", __खाता__, __LINE__, pmd_val(e))
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))


/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)		अणु वापस !(pte_val(pte) & _PAGE_RONLY); पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_सूचीTY; पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_ACCESSED; पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)	अणु pte_val(pte) |= _PAGE_RONLY; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkclean(pte_t pte)	अणु pte_val(pte) &= ~_PAGE_सूचीTY; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkold(pte_t pte)	अणु pte_val(pte) &= ~_PAGE_ACCESSED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)	अणु pte_val(pte) &= ~_PAGE_RONLY; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)	अणु pte_val(pte) |= _PAGE_सूचीTY; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)	अणु pte_val(pte) |= _PAGE_ACCESSED; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mknocache(pte_t pte)
अणु
	pte_val(pte) = (pte_val(pte) & _CACHEMASK040) | m68k_pgtable_cachemode;
	वापस pte;
पूर्ण
अटल अंतरभूत pte_t pte_mkcache(pte_t pte)
अणु
	pte_val(pte) = (pte_val(pte) & _CACHEMASK040) | m68k_supervisor_cachemode;
	वापस pte;
पूर्ण

#घोषणा swapper_pg_dir kernel_pg_dir
बाह्य pgd_t kernel_pg_dir[128];

/* Encode and de-code a swap entry (must be !pte_none(e) && !pte_present(e)) */
#घोषणा __swp_type(x)		(((x).val >> 4) & 0xff)
#घोषणा __swp_offset(x)		((x).val >> 12)
#घोषणा __swp_entry(type, offset) ((swp_entry_t) अणु ((type) << 4) | ((offset) << 12) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)

#पूर्ण_अगर	/* !__ASSEMBLY__ */
#पूर्ण_अगर /* _MOTOROLA_PGTABLE_H */
