<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_64_H
#घोषणा _ASM_X86_PGTABLE_64_H

#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/pgtable_64_types.h>

#अगर_अघोषित __ASSEMBLY__

/*
 * This file contains the functions and defines necessary to modअगरy and use
 * the x86-64 page table tree.
 */
#समावेश <यंत्र/processor.h>
#समावेश <linux/bitops.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/fixmap.h>

बाह्य p4d_t level4_kernel_pgt[512];
बाह्य p4d_t level4_ident_pgt[512];
बाह्य pud_t level3_kernel_pgt[512];
बाह्य pud_t level3_ident_pgt[512];
बाह्य pmd_t level2_kernel_pgt[512];
बाह्य pmd_t level2_fixmap_pgt[512];
बाह्य pmd_t level2_ident_pgt[512];
बाह्य pte_t level1_fixmap_pgt[512 * FIXMAP_PMD_NUM];
बाह्य pgd_t init_top_pgt[];

#घोषणा swapper_pg_dir init_top_pgt

बाह्य व्योम paging_init(व्योम);
अटल अंतरभूत व्योम sync_initial_page_table(व्योम) अणु पूर्ण

#घोषणा pte_ERROR(e)					\
	pr_err("%s:%d: bad pte %p(%016lx)\n",		\
	       __खाता__, __LINE__, &(e), pte_val(e))
#घोषणा pmd_ERROR(e)					\
	pr_err("%s:%d: bad pmd %p(%016lx)\n",		\
	       __खाता__, __LINE__, &(e), pmd_val(e))
#घोषणा pud_ERROR(e)					\
	pr_err("%s:%d: bad pud %p(%016lx)\n",		\
	       __खाता__, __LINE__, &(e), pud_val(e))

#अगर CONFIG_PGTABLE_LEVELS >= 5
#घोषणा p4d_ERROR(e)					\
	pr_err("%s:%d: bad p4d %p(%016lx)\n",		\
	       __खाता__, __LINE__, &(e), p4d_val(e))
#पूर्ण_अगर

#घोषणा pgd_ERROR(e)					\
	pr_err("%s:%d: bad pgd %p(%016lx)\n",		\
	       __खाता__, __LINE__, &(e), pgd_val(e))

काष्ठा mm_काष्ठा;

#घोषणा mm_p4d_folded mm_p4d_folded
अटल अंतरभूत bool mm_p4d_folded(काष्ठा mm_काष्ठा *mm)
अणु
	वापस !pgtable_l5_enabled();
पूर्ण

व्योम set_pte_vaddr_p4d(p4d_t *p4d_page, अचिन्हित दीर्घ vaddr, pte_t new_pte);
व्योम set_pte_vaddr_pud(pud_t *pud_page, अचिन्हित दीर्घ vaddr, pte_t new_pte);

अटल अंतरभूत व्योम native_set_pte(pte_t *ptep, pte_t pte)
अणु
	WRITE_ONCE(*ptep, pte);
पूर्ण

अटल अंतरभूत व्योम native_pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				    pte_t *ptep)
अणु
	native_set_pte(ptep, native_make_pte(0));
पूर्ण

अटल अंतरभूत व्योम native_set_pte_atomic(pte_t *ptep, pte_t pte)
अणु
	native_set_pte(ptep, pte);
पूर्ण

अटल अंतरभूत व्योम native_set_pmd(pmd_t *pmdp, pmd_t pmd)
अणु
	WRITE_ONCE(*pmdp, pmd);
पूर्ण

अटल अंतरभूत व्योम native_pmd_clear(pmd_t *pmd)
अणु
	native_set_pmd(pmd, native_make_pmd(0));
पूर्ण

अटल अंतरभूत pte_t native_ptep_get_and_clear(pte_t *xp)
अणु
#अगर_घोषित CONFIG_SMP
	वापस native_make_pte(xchg(&xp->pte, 0));
#अन्यथा
	/* native_local_ptep_get_and_clear,
	   but duplicated because of cyclic dependency */
	pte_t ret = *xp;
	native_pte_clear(शून्य, 0, xp);
	वापस ret;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत pmd_t native_pmdp_get_and_clear(pmd_t *xp)
अणु
#अगर_घोषित CONFIG_SMP
	वापस native_make_pmd(xchg(&xp->pmd, 0));
#अन्यथा
	/* native_local_pmdp_get_and_clear,
	   but duplicated because of cyclic dependency */
	pmd_t ret = *xp;
	native_pmd_clear(xp);
	वापस ret;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम native_set_pud(pud_t *pudp, pud_t pud)
अणु
	WRITE_ONCE(*pudp, pud);
पूर्ण

अटल अंतरभूत व्योम native_pud_clear(pud_t *pud)
अणु
	native_set_pud(pud, native_make_pud(0));
पूर्ण

अटल अंतरभूत pud_t native_pudp_get_and_clear(pud_t *xp)
अणु
#अगर_घोषित CONFIG_SMP
	वापस native_make_pud(xchg(&xp->pud, 0));
#अन्यथा
	/* native_local_pudp_get_and_clear,
	 * but duplicated because of cyclic dependency
	 */
	pud_t ret = *xp;

	native_pud_clear(xp);
	वापस ret;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम native_set_p4d(p4d_t *p4dp, p4d_t p4d)
अणु
	pgd_t pgd;

	अगर (pgtable_l5_enabled() || !IS_ENABLED(CONFIG_PAGE_TABLE_ISOLATION)) अणु
		WRITE_ONCE(*p4dp, p4d);
		वापस;
	पूर्ण

	pgd = native_make_pgd(native_p4d_val(p4d));
	pgd = pti_set_user_pgtbl((pgd_t *)p4dp, pgd);
	WRITE_ONCE(*p4dp, native_make_p4d(native_pgd_val(pgd)));
पूर्ण

अटल अंतरभूत व्योम native_p4d_clear(p4d_t *p4d)
अणु
	native_set_p4d(p4d, native_make_p4d(0));
पूर्ण

अटल अंतरभूत व्योम native_set_pgd(pgd_t *pgdp, pgd_t pgd)
अणु
	WRITE_ONCE(*pgdp, pti_set_user_pgtbl(pgdp, pgd));
पूर्ण

अटल अंतरभूत व्योम native_pgd_clear(pgd_t *pgd)
अणु
	native_set_pgd(pgd, native_make_pgd(0));
पूर्ण

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */

/* PGD - Level 4 access */

/* PUD - Level 3 access */

/* PMD - Level 2 access */

/* PTE - Level 1 access */

/*
 * Encode and de-code a swap entry
 *
 * |     ...            | 11| 10|  9|8|7|6|5| 4| 3|2| 1|0| <- bit number
 * |     ...            |SW3|SW2|SW1|G|L|D|A|CD|WT|U| W|P| <- bit names
 * | TYPE (59-63) | ~OFFSET (9-58)  |0|0|X|X| X| X|F|SD|0| <- swp entry
 *
 * G (8) is aliased and used as a PROT_NONE indicator क्रम
 * !present ptes.  We need to start storing swap entries above
 * there.  We also need to aव्योम using A and D because of an
 * erratum where they can be incorrectly set by hardware on
 * non-present PTEs.
 *
 * SD Bits 1-4 are not used in non-present क्रमmat and available क्रम
 * special use described below:
 *
 * SD (1) in swp entry is used to store soft dirty bit, which helps us
 * remember soft dirty over page migration
 *
 * F (2) in swp entry is used to record when a pagetable is
 * ग_लिखोरक्षित by userfaultfd WP support.
 *
 * Bit 7 in swp entry should be 0 because pmd_present checks not only P,
 * but also L and G.
 *
 * The offset is inverted by a binary not operation to make the high
 * physical bits set.
 */
#घोषणा SWP_TYPE_BITS		5

#घोषणा SWP_OFFSET_FIRST_BIT	(_PAGE_BIT_PROTNONE + 1)

/* We always extract/encode the offset by shअगरting it all the way up, and then करोwn again */
#घोषणा SWP_OFFSET_SHIFT	(SWP_OFFSET_FIRST_BIT+SWP_TYPE_BITS)

#घोषणा MAX_SWAPखाताS_CHECK() BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT > SWP_TYPE_BITS)

/* Extract the high bits क्रम type */
#घोषणा __swp_type(x) ((x).val >> (64 - SWP_TYPE_BITS))

/* Shअगरt up (to get rid of type), then करोwn to get value */
#घोषणा __swp_offset(x) (~(x).val << SWP_TYPE_BITS >> SWP_OFFSET_SHIFT)

/*
 * Shअगरt the offset up "too far" by TYPE bits, then करोwn again
 * The offset is inverted by a binary not operation to make the high
 * physical bits set.
 */
#घोषणा __swp_entry(type, offset) ((swp_entry_t) अणु \
	(~(अचिन्हित दीर्घ)(offset) << SWP_OFFSET_SHIFT >> SWP_TYPE_BITS) \
	| ((अचिन्हित दीर्घ)(type) << (64-SWP_TYPE_BITS)) पूर्ण)

#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val((pte)) पूर्ण)
#घोषणा __pmd_to_swp_entry(pmd)		((swp_entry_t) अणु pmd_val((pmd)) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु .pte = (x).val पूर्ण)
#घोषणा __swp_entry_to_pmd(x)		((pmd_t) अणु .pmd = (x).val पूर्ण)

बाह्य पूर्णांक kern_addr_valid(अचिन्हित दीर्घ addr);
बाह्य व्योम cleanup_highmap(व्योम);

#घोषणा HAVE_ARCH_UNMAPPED_AREA
#घोषणा HAVE_ARCH_UNMAPPED_AREA_TOPDOWN

#घोषणा PAGE_AGP    PAGE_KERNEL_NOCACHE
#घोषणा HAVE_PAGE_AGP 1

/* fs/proc/kcore.c */
#घोषणा	kc_vaddr_to_offset(v) ((v) & __VIRTUAL_MASK)
#घोषणा	kc_offset_to_vaddr(o) ((o) | ~__VIRTUAL_MASK)

#घोषणा __HAVE_ARCH_PTE_SAME

#घोषणा vmemmap ((काष्ठा page *)VMEMMAP_START)

बाह्य व्योम init_extra_mapping_uc(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size);
बाह्य व्योम init_extra_mapping_wb(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size);

#घोषणा gup_fast_permitted gup_fast_permitted
अटल अंतरभूत bool gup_fast_permitted(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (end >> __VIRTUAL_MASK_SHIFT)
		वापस false;
	वापस true;
पूर्ण

#समावेश <यंत्र/pgtable-invert.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_PGTABLE_64_H */
