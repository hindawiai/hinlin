<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/pgtable-3level.h
 *
 * Copyright (C) 2011 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 */
#अगर_अघोषित _ASM_PGTABLE_3LEVEL_H
#घोषणा _ASM_PGTABLE_3LEVEL_H

/*
 * With LPAE, there are 3 levels of page tables. Each level has 512 entries of
 * 8 bytes each, occupying a 4K page. The first level table covers a range of
 * 512GB, each entry representing 1GB. Since we are limited to 4GB input
 * address range, only 4 entries in the PGD are used.
 *
 * There are enough spare bits in a page table entry क्रम the kernel specअगरic
 * state.
 */
#घोषणा PTRS_PER_PTE		512
#घोषणा PTRS_PER_PMD		512
#घोषणा PTRS_PER_PGD		4

#घोषणा PTE_HWTABLE_PTRS	(0)
#घोषणा PTE_HWTABLE_OFF		(0)
#घोषणा PTE_HWTABLE_SIZE	(PTRS_PER_PTE * माप(u64))

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS 40

/*
 * PGसूची_SHIFT determines the size a top-level page table entry can map.
 */
#घोषणा PGसूची_SHIFT		30

/*
 * PMD_SHIFT determines the size a middle-level page table entry can map.
 */
#घोषणा PMD_SHIFT		21

#घोषणा PMD_SIZE		(1UL << PMD_SHIFT)
#घोषणा PMD_MASK		(~((1 << PMD_SHIFT) - 1))
#घोषणा PGसूची_SIZE		(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK		(~((1 << PGसूची_SHIFT) - 1))

/*
 * section address mask and size definitions.
 */
#घोषणा SECTION_SHIFT		21
#घोषणा SECTION_SIZE		(1UL << SECTION_SHIFT)
#घोषणा SECTION_MASK		(~((1 << SECTION_SHIFT) - 1))

#घोषणा USER_PTRS_PER_PGD	(PAGE_OFFSET / PGसूची_SIZE)

/*
 * Hugetlb definitions.
 */
#घोषणा HPAGE_SHIFT		PMD_SHIFT
#घोषणा HPAGE_SIZE		(_AC(1, UL) << HPAGE_SHIFT)
#घोषणा HPAGE_MASK		(~(HPAGE_SIZE - 1))
#घोषणा HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)

/*
 * "Linux" PTE definitions क्रम LPAE.
 *
 * These bits overlap with the hardware bits but the naming is preserved क्रम
 * consistency with the classic page table क्रमmat.
 */
#घोषणा L_PTE_VALID		(_AT(pteval_t, 1) << 0)		/* Valid */
#घोषणा L_PTE_PRESENT		(_AT(pteval_t, 3) << 0)		/* Present */
#घोषणा L_PTE_USER		(_AT(pteval_t, 1) << 6)		/* AP[1] */
#घोषणा L_PTE_SHARED		(_AT(pteval_t, 3) << 8)		/* SH[1:0], inner shareable */
#घोषणा L_PTE_YOUNG		(_AT(pteval_t, 1) << 10)	/* AF */
#घोषणा L_PTE_XN		(_AT(pteval_t, 1) << 54)	/* XN */
#घोषणा L_PTE_सूचीTY		(_AT(pteval_t, 1) << 55)
#घोषणा L_PTE_SPECIAL		(_AT(pteval_t, 1) << 56)
#घोषणा L_PTE_NONE		(_AT(pteval_t, 1) << 57)	/* PROT_NONE */
#घोषणा L_PTE_RDONLY		(_AT(pteval_t, 1) << 58)	/* READ ONLY */

#घोषणा L_PMD_SECT_VALID	(_AT(pmdval_t, 1) << 0)
#घोषणा L_PMD_SECT_सूचीTY	(_AT(pmdval_t, 1) << 55)
#घोषणा L_PMD_SECT_NONE		(_AT(pmdval_t, 1) << 57)
#घोषणा L_PMD_SECT_RDONLY	(_AT(pteval_t, 1) << 58)

/*
 * To be used in assembly code with the upper page attributes.
 */
#घोषणा L_PTE_XN_HIGH		(1 << (54 - 32))
#घोषणा L_PTE_सूचीTY_HIGH	(1 << (55 - 32))

/*
 * AttrIndx[2:0] encoding (mapping attributes defined in the MAIR* रेजिस्टरs).
 */
#घोषणा L_PTE_MT_UNCACHED	(_AT(pteval_t, 0) << 2)	/* strongly ordered */
#घोषणा L_PTE_MT_BUFFERABLE	(_AT(pteval_t, 1) << 2)	/* normal non-cacheable */
#घोषणा L_PTE_MT_WRITETHROUGH	(_AT(pteval_t, 2) << 2)	/* normal inner ग_लिखो-through */
#घोषणा L_PTE_MT_WRITEBACK	(_AT(pteval_t, 3) << 2)	/* normal inner ग_लिखो-back */
#घोषणा L_PTE_MT_WRITEALLOC	(_AT(pteval_t, 7) << 2)	/* normal inner ग_लिखो-alloc */
#घोषणा L_PTE_MT_DEV_SHARED	(_AT(pteval_t, 4) << 2)	/* device */
#घोषणा L_PTE_MT_DEV_NONSHARED	(_AT(pteval_t, 4) << 2)	/* device */
#घोषणा L_PTE_MT_DEV_WC		(_AT(pteval_t, 1) << 2)	/* normal non-cacheable */
#घोषणा L_PTE_MT_DEV_CACHED	(_AT(pteval_t, 3) << 2)	/* normal inner ग_लिखो-back */
#घोषणा L_PTE_MT_MASK		(_AT(pteval_t, 7) << 2)

/*
 * Software PGD flags.
 */
#घोषणा L_PGD_SWAPPER		(_AT(pgdval_t, 1) << 55)	/* swapper_pg_dir entry */

#अगर_अघोषित __ASSEMBLY__

#घोषणा pud_none(pud)		(!pud_val(pud))
#घोषणा pud_bad(pud)		(!(pud_val(pud) & 2))
#घोषणा pud_present(pud)	(pud_val(pud))
#घोषणा pmd_table(pmd)		((pmd_val(pmd) & PMD_TYPE_MASK) == \
						 PMD_TYPE_TABLE)
#घोषणा pmd_sect(pmd)		((pmd_val(pmd) & PMD_TYPE_MASK) == \
						 PMD_TYPE_SECT)
#घोषणा pmd_large(pmd)		pmd_sect(pmd)
#घोषणा pmd_leaf(pmd)		pmd_sect(pmd)

#घोषणा pud_clear(pudp)			\
	करो अणु				\
		*pudp = __pud(0);	\
		clean_pmd_entry(pudp);	\
	पूर्ण जबतक (0)

#घोषणा set_pud(pudp, pud)		\
	करो अणु				\
		*pudp = pud;		\
		flush_pmd_entry(pudp);	\
	पूर्ण जबतक (0)

अटल अंतरभूत pmd_t *pud_page_vaddr(pud_t pud)
अणु
	वापस __va(pud_val(pud) & PHYS_MASK & (s32)PAGE_MASK);
पूर्ण

#घोषणा pmd_bad(pmd)		(!(pmd_val(pmd) & 2))

#घोषणा copy_pmd(pmdpd,pmdps)		\
	करो अणु				\
		*pmdpd = *pmdps;	\
		flush_pmd_entry(pmdpd);	\
	पूर्ण जबतक (0)

#घोषणा pmd_clear(pmdp)			\
	करो अणु				\
		*pmdp = __pmd(0);	\
		clean_pmd_entry(pmdp);	\
	पूर्ण जबतक (0)

/*
 * For 3 levels of paging the PTE_EXT_NG bit will be set क्रम user address ptes
 * that are written to a page table but not क्रम ptes created with mk_pte.
 *
 * In hugetlb_no_page, a new huge pte (new_pte) is generated and passed to
 * hugetlb_cow, where it is compared with an entry in a page table.
 * This comparison test fails erroneously leading ultimately to a memory leak.
 *
 * To correct this behaviour, we mask off PTE_EXT_NG क्रम any pte that is
 * present beक्रमe running the comparison.
 */
#घोषणा __HAVE_ARCH_PTE_SAME
#घोषणा pte_same(pte_a,pte_b)	((pte_present(pte_a) ? pte_val(pte_a) & ~PTE_EXT_NG	\
					: pte_val(pte_a))				\
				== (pte_present(pte_b) ? pte_val(pte_b) & ~PTE_EXT_NG	\
					: pte_val(pte_b)))

#घोषणा set_pte_ext(ptep,pte,ext) cpu_set_pte_ext(ptep,__pte(pte_val(pte)|(ext)))

#घोषणा pte_huge(pte)		(pte_val(pte) && !(pte_val(pte) & PTE_TABLE_BIT))
#घोषणा pte_mkhuge(pte)		(__pte(pte_val(pte) & ~PTE_TABLE_BIT))

#घोषणा pmd_isset(pmd, val)	((u32)(val) == (val) ? pmd_val(pmd) & (val) \
						: !!(pmd_val(pmd) & (val)))
#घोषणा pmd_isclear(pmd, val)	(!(pmd_val(pmd) & (val)))

#घोषणा pmd_present(pmd)	(pmd_isset((pmd), L_PMD_SECT_VALID))
#घोषणा pmd_young(pmd)		(pmd_isset((pmd), PMD_SECT_AF))
#घोषणा pte_special(pte)	(pte_isset((pte), L_PTE_SPECIAL))
अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	pte_val(pte) |= L_PTE_SPECIAL;
	वापस pte;
पूर्ण

#घोषणा pmd_ग_लिखो(pmd)		(pmd_isclear((pmd), L_PMD_SECT_RDONLY))
#घोषणा pmd_dirty(pmd)		(pmd_isset((pmd), L_PMD_SECT_सूचीTY))

#घोषणा pmd_hugewillfault(pmd)	(!pmd_young(pmd) || !pmd_ग_लिखो(pmd))
#घोषणा pmd_thp_or_huge(pmd)	(pmd_huge(pmd) || pmd_trans_huge(pmd))

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा pmd_trans_huge(pmd)	(pmd_val(pmd) && !pmd_table(pmd))
#पूर्ण_अगर

#घोषणा PMD_BIT_FUNC(fn,op) \
अटल अंतरभूत pmd_t pmd_##fn(pmd_t pmd) अणु pmd_val(pmd) op; वापस pmd; पूर्ण

PMD_BIT_FUNC(wrprotect,	|= L_PMD_SECT_RDONLY);
PMD_BIT_FUNC(mkold,	&= ~PMD_SECT_AF);
PMD_BIT_FUNC(mkग_लिखो,   &= ~L_PMD_SECT_RDONLY);
PMD_BIT_FUNC(सूची_गढ़ोty,   |= L_PMD_SECT_सूचीTY);
PMD_BIT_FUNC(mkclean,   &= ~L_PMD_SECT_सूचीTY);
PMD_BIT_FUNC(mkyoung,   |= PMD_SECT_AF);

#घोषणा pmd_mkhuge(pmd)		(__pmd(pmd_val(pmd) & ~PMD_TABLE_BIT))

#घोषणा pmd_pfn(pmd)		(((pmd_val(pmd) & PMD_MASK) & PHYS_MASK) >> PAGE_SHIFT)
#घोषणा pfn_pmd(pfn,prot)	(__pmd(((phys_addr_t)(pfn) << PAGE_SHIFT) | pgprot_val(prot)))
#घोषणा mk_pmd(page,prot)	pfn_pmd(page_to_pfn(page),prot)

/* No hardware dirty/accessed bits -- generic_pmdp_establish() fits */
#घोषणा pmdp_establish generic_pmdp_establish

/* represent a notpresent pmd by faulting entry, this is used by pmdp_invalidate */
अटल अंतरभूत pmd_t pmd_mkinvalid(pmd_t pmd)
अणु
	वापस __pmd(pmd_val(pmd) & ~L_PMD_SECT_VALID);
पूर्ण

अटल अंतरभूत pmd_t pmd_modअगरy(pmd_t pmd, pgprot_t newprot)
अणु
	स्थिर pmdval_t mask = PMD_SECT_USER | PMD_SECT_XN | L_PMD_SECT_RDONLY |
				L_PMD_SECT_VALID | L_PMD_SECT_NONE;
	pmd_val(pmd) = (pmd_val(pmd) & ~mask) | (pgprot_val(newprot) & mask);
	वापस pmd;
पूर्ण

अटल अंतरभूत व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pmd_t *pmdp, pmd_t pmd)
अणु
	BUG_ON(addr >= TASK_SIZE);

	/* create a faulting entry अगर PROT_NONE रक्षित */
	अगर (pmd_val(pmd) & L_PMD_SECT_NONE)
		pmd_val(pmd) &= ~L_PMD_SECT_VALID;

	अगर (pmd_ग_लिखो(pmd) && pmd_dirty(pmd))
		pmd_val(pmd) &= ~PMD_SECT_AP2;
	अन्यथा
		pmd_val(pmd) |= PMD_SECT_AP2;

	*pmdp = __pmd(pmd_val(pmd) | PMD_SECT_nG);
	flush_pmd_entry(pmdp);
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_PGTABLE_3LEVEL_H */
