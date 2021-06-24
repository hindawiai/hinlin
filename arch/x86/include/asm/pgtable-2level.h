<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_2LEVEL_H
#घोषणा _ASM_X86_PGTABLE_2LEVEL_H

#घोषणा pte_ERROR(e) \
	pr_err("%s:%d: bad pte %08lx\n", __खाता__, __LINE__, (e).pte_low)
#घोषणा pgd_ERROR(e) \
	pr_err("%s:%d: bad pgd %08lx\n", __खाता__, __LINE__, pgd_val(e))

/*
 * Certain architectures need to करो special things when PTEs
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */
अटल अंतरभूत व्योम native_set_pte(pte_t *ptep , pte_t pte)
अणु
	*ptep = pte;
पूर्ण

अटल अंतरभूत व्योम native_set_pmd(pmd_t *pmdp, pmd_t pmd)
अणु
	*pmdp = pmd;
पूर्ण

अटल अंतरभूत व्योम native_set_pud(pud_t *pudp, pud_t pud)
अणु
पूर्ण

अटल अंतरभूत व्योम native_set_pte_atomic(pte_t *ptep, pte_t pte)
अणु
	native_set_pte(ptep, pte);
पूर्ण

अटल अंतरभूत व्योम native_pmd_clear(pmd_t *pmdp)
अणु
	native_set_pmd(pmdp, __pmd(0));
पूर्ण

अटल अंतरभूत व्योम native_pud_clear(pud_t *pudp)
अणु
पूर्ण

अटल अंतरभूत व्योम native_pte_clear(काष्ठा mm_काष्ठा *mm,
				    अचिन्हित दीर्घ addr, pte_t *xp)
अणु
	*xp = native_make_pte(0);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत pte_t native_ptep_get_and_clear(pte_t *xp)
अणु
	वापस __pte(xchg(&xp->pte_low, 0));
पूर्ण
#अन्यथा
#घोषणा native_ptep_get_and_clear(xp) native_local_ptep_get_and_clear(xp)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत pmd_t native_pmdp_get_and_clear(pmd_t *xp)
अणु
	वापस __pmd(xchg((pmdval_t *)xp, 0));
पूर्ण
#अन्यथा
#घोषणा native_pmdp_get_and_clear(xp) native_local_pmdp_get_and_clear(xp)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत pud_t native_pudp_get_and_clear(pud_t *xp)
अणु
	वापस __pud(xchg((pudval_t *)xp, 0));
पूर्ण
#अन्यथा
#घोषणा native_pudp_get_and_clear(xp) native_local_pudp_get_and_clear(xp)
#पूर्ण_अगर

/* Bit manipulation helper on pte/pgoff entry */
अटल अंतरभूत अचिन्हित दीर्घ pte_bitop(अचिन्हित दीर्घ value, अचिन्हित पूर्णांक rightshअगरt,
				      अचिन्हित दीर्घ mask, अचिन्हित पूर्णांक leftshअगरt)
अणु
	वापस ((value >> rightshअगरt) & mask) << leftshअगरt;
पूर्ण

/* Encode and de-code a swap entry */
#घोषणा SWP_TYPE_BITS 5
#घोषणा SWP_OFFSET_SHIFT (_PAGE_BIT_PROTNONE + 1)

#घोषणा MAX_SWAPखाताS_CHECK() BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT > SWP_TYPE_BITS)

#घोषणा __swp_type(x)			(((x).val >> (_PAGE_BIT_PRESENT + 1)) \
					 & ((1U << SWP_TYPE_BITS) - 1))
#घोषणा __swp_offset(x)			((x).val >> SWP_OFFSET_SHIFT)
#घोषणा __swp_entry(type, offset)	((swp_entry_t) अणु \
					 ((type) << (_PAGE_BIT_PRESENT + 1)) \
					 | ((offset) << SWP_OFFSET_SHIFT) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु (pte).pte_low पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु .pte = (x).val पूर्ण)

/* No inverted PFNs on 2 level page tables */

अटल अंतरभूत u64 protnone_mask(u64 val)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u64 flip_protnone_guard(u64 oldval, u64 val, u64 mask)
अणु
	वापस val;
पूर्ण

अटल अंतरभूत bool __pte_needs_invert(u64 val)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_PGTABLE_2LEVEL_H */
