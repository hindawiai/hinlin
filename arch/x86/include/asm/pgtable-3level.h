<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_3LEVEL_H
#घोषणा _ASM_X86_PGTABLE_3LEVEL_H

#समावेश <यंत्र/atomic64_32.h>

/*
 * Intel Physical Address Extension (PAE) Mode - three-level page
 * tables on PPro+ CPUs.
 *
 * Copyright (C) 1999 Ingo Molnar <mingo@redhat.com>
 */

#घोषणा pte_ERROR(e)							\
	pr_err("%s:%d: bad pte %p(%08lx%08lx)\n",			\
	       __खाता__, __LINE__, &(e), (e).pte_high, (e).pte_low)
#घोषणा pmd_ERROR(e)							\
	pr_err("%s:%d: bad pmd %p(%016Lx)\n",				\
	       __खाता__, __LINE__, &(e), pmd_val(e))
#घोषणा pgd_ERROR(e)							\
	pr_err("%s:%d: bad pgd %p(%016Lx)\n",				\
	       __खाता__, __LINE__, &(e), pgd_val(e))

/* Rules क्रम using set_pte: the pte being asचिन्हित *must* be
 * either not present or in a state where the hardware will
 * not attempt to update the pte.  In places where this is
 * not possible, use pte_get_and_clear to obtain the old pte
 * value and then use set_pte to update it.  -ben
 */
अटल अंतरभूत व्योम native_set_pte(pte_t *ptep, pte_t pte)
अणु
	ptep->pte_high = pte.pte_high;
	smp_wmb();
	ptep->pte_low = pte.pte_low;
पूर्ण

#घोषणा pmd_पढ़ो_atomic pmd_पढ़ो_atomic
/*
 * pte_offset_map_lock() on 32-bit PAE kernels was पढ़ोing the pmd_t with
 * a "*pmdp" dereference करोne by GCC. Problem is, in certain places
 * where pte_offset_map_lock() is called, concurrent page faults are
 * allowed, अगर the mmap_lock is hold क्रम पढ़ोing. An example is mincore
 * vs page faults vs MADV_DONTNEED. On the page fault side
 * pmd_populate() rightfully करोes a set_64bit(), but अगर we're पढ़ोing the
 * pmd_t with a "*pmdp" on the mincore side, a SMP race can happen
 * because GCC will not पढ़ो the 64-bit value of the pmd atomically.
 *
 * To fix this all places running pte_offset_map_lock() जबतक holding the
 * mmap_lock in पढ़ो mode, shall पढ़ो the pmdp poपूर्णांकer using this
 * function to know अगर the pmd is null or not, and in turn to know अगर
 * they can run pte_offset_map_lock() or pmd_trans_huge() or other pmd
 * operations.
 *
 * Without THP अगर the mmap_lock is held क्रम पढ़ोing, the pmd can only
 * transition from null to not null जबतक pmd_पढ़ो_atomic() runs. So
 * we can always वापस atomic pmd values with this function.
 *
 * With THP अगर the mmap_lock is held क्रम पढ़ोing, the pmd can become
 * trans_huge or none or poपूर्णांक to a pte (and in turn become "stable")
 * at any समय under pmd_पढ़ो_atomic(). We could पढ़ो it truly
 * atomically here with an atomic64_पढ़ो() क्रम the THP enabled हाल (and
 * it would be a whole lot simpler), but to aव्योम using cmpxchg8b we
 * only वापस an atomic pmdval अगर the low part of the pmdval is later
 * found to be stable (i.e. poपूर्णांकing to a pte). We are also वापसing a
 * 'none' (zero) pmdval अगर the low part of the pmd is zero.
 *
 * In some हालs the high and low part of the pmdval वापसed may not be
 * consistent अगर THP is enabled (the low part may poपूर्णांक to previously
 * mapped hugepage, जबतक the high part may poपूर्णांक to a more recently
 * mapped hugepage), but pmd_none_or_trans_huge_or_clear_bad() only
 * needs the low part of the pmd to be पढ़ो atomically to decide अगर the
 * pmd is unstable or not, with the only exception when the low part
 * of the pmd is zero, in which हाल we वापस a 'none' pmd.
 */
अटल अंतरभूत pmd_t pmd_पढ़ो_atomic(pmd_t *pmdp)
अणु
	pmdval_t ret;
	u32 *पंचांगp = (u32 *)pmdp;

	ret = (pmdval_t) (*पंचांगp);
	अगर (ret) अणु
		/*
		 * If the low part is null, we must not पढ़ो the high part
		 * or we can end up with a partial pmd.
		 */
		smp_rmb();
		ret |= ((pmdval_t)*(पंचांगp + 1)) << 32;
	पूर्ण

	वापस (pmd_t) अणु ret पूर्ण;
पूर्ण

अटल अंतरभूत व्योम native_set_pte_atomic(pte_t *ptep, pte_t pte)
अणु
	set_64bit((अचिन्हित दीर्घ दीर्घ *)(ptep), native_pte_val(pte));
पूर्ण

अटल अंतरभूत व्योम native_set_pmd(pmd_t *pmdp, pmd_t pmd)
अणु
	set_64bit((अचिन्हित दीर्घ दीर्घ *)(pmdp), native_pmd_val(pmd));
पूर्ण

अटल अंतरभूत व्योम native_set_pud(pud_t *pudp, pud_t pud)
अणु
#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
	pud.p4d.pgd = pti_set_user_pgtbl(&pudp->p4d.pgd, pud.p4d.pgd);
#पूर्ण_अगर
	set_64bit((अचिन्हित दीर्घ दीर्घ *)(pudp), native_pud_val(pud));
पूर्ण

/*
 * For PTEs and PDEs, we must clear the P-bit first when clearing a page table
 * entry, so clear the bottom half first and enक्रमce ordering with a compiler
 * barrier.
 */
अटल अंतरभूत व्योम native_pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				    pte_t *ptep)
अणु
	ptep->pte_low = 0;
	smp_wmb();
	ptep->pte_high = 0;
पूर्ण

अटल अंतरभूत व्योम native_pmd_clear(pmd_t *pmd)
अणु
	u32 *पंचांगp = (u32 *)pmd;
	*पंचांगp = 0;
	smp_wmb();
	*(पंचांगp + 1) = 0;
पूर्ण

अटल अंतरभूत व्योम native_pud_clear(pud_t *pudp)
अणु
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pudp)
अणु
	set_pud(pudp, __pud(0));

	/*
	 * According to Intel App note "TLBs, Paging-Structure Caches,
	 * and Their Invalidation", April 2007, करोcument 317080-001,
	 * section 8.1: in PAE mode we explicitly have to flush the
	 * TLB via cr3 अगर the top-level pgd is changed...
	 *
	 * Currently all places where pud_clear() is called either have
	 * flush_tlb_mm() followed or करोn't need TLB flush (x86_64 code or
	 * pud_clear_bad()), so we करोn't need TLB flush here.
	 */
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत pte_t native_ptep_get_and_clear(pte_t *ptep)
अणु
	pte_t res;

	res.pte = (pteval_t)arch_atomic64_xchg((atomic64_t *)ptep, 0);

	वापस res;
पूर्ण
#अन्यथा
#घोषणा native_ptep_get_and_clear(xp) native_local_ptep_get_and_clear(xp)
#पूर्ण_अगर

जोड़ split_pmd अणु
	काष्ठा अणु
		u32 pmd_low;
		u32 pmd_high;
	पूर्ण;
	pmd_t pmd;
पूर्ण;

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत pmd_t native_pmdp_get_and_clear(pmd_t *pmdp)
अणु
	जोड़ split_pmd res, *orig = (जोड़ split_pmd *)pmdp;

	/* xchg acts as a barrier beक्रमe setting of the high bits */
	res.pmd_low = xchg(&orig->pmd_low, 0);
	res.pmd_high = orig->pmd_high;
	orig->pmd_high = 0;

	वापस res.pmd;
पूर्ण
#अन्यथा
#घोषणा native_pmdp_get_and_clear(xp) native_local_pmdp_get_and_clear(xp)
#पूर्ण_अगर

#अगर_अघोषित pmdp_establish
#घोषणा pmdp_establish pmdp_establish
अटल अंतरभूत pmd_t pmdp_establish(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, pmd_t *pmdp, pmd_t pmd)
अणु
	pmd_t old;

	/*
	 * If pmd has present bit cleared we can get away without expensive
	 * cmpxchg64: we can update pmdp half-by-half without racing with
	 * anybody.
	 */
	अगर (!(pmd_val(pmd) & _PAGE_PRESENT)) अणु
		जोड़ split_pmd old, new, *ptr;

		ptr = (जोड़ split_pmd *)pmdp;

		new.pmd = pmd;

		/* xchg acts as a barrier beक्रमe setting of the high bits */
		old.pmd_low = xchg(&ptr->pmd_low, new.pmd_low);
		old.pmd_high = ptr->pmd_high;
		ptr->pmd_high = new.pmd_high;
		वापस old.pmd;
	पूर्ण

	करो अणु
		old = *pmdp;
	पूर्ण जबतक (cmpxchg64(&pmdp->pmd, old.pmd, pmd.pmd) != old.pmd);

	वापस old;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
जोड़ split_pud अणु
	काष्ठा अणु
		u32 pud_low;
		u32 pud_high;
	पूर्ण;
	pud_t pud;
पूर्ण;

अटल अंतरभूत pud_t native_pudp_get_and_clear(pud_t *pudp)
अणु
	जोड़ split_pud res, *orig = (जोड़ split_pud *)pudp;

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
	pti_set_user_pgtbl(&pudp->p4d.pgd, __pgd(0));
#पूर्ण_अगर

	/* xchg acts as a barrier beक्रमe setting of the high bits */
	res.pud_low = xchg(&orig->pud_low, 0);
	res.pud_high = orig->pud_high;
	orig->pud_high = 0;

	वापस res.pud;
पूर्ण
#अन्यथा
#घोषणा native_pudp_get_and_clear(xp) native_local_pudp_get_and_clear(xp)
#पूर्ण_अगर

/* Encode and de-code a swap entry */
#घोषणा SWP_TYPE_BITS		5

#घोषणा SWP_OFFSET_FIRST_BIT	(_PAGE_BIT_PROTNONE + 1)

/* We always extract/encode the offset by shअगरting it all the way up, and then करोwn again */
#घोषणा SWP_OFFSET_SHIFT	(SWP_OFFSET_FIRST_BIT + SWP_TYPE_BITS)

#घोषणा MAX_SWAPखाताS_CHECK() BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT > 5)
#घोषणा __swp_type(x)			(((x).val) & 0x1f)
#घोषणा __swp_offset(x)			((x).val >> 5)
#घोषणा __swp_entry(type, offset)	((swp_entry_t)अणु(type) | (offset) << 5पूर्ण)

/*
 * Normally, __swp_entry() converts from arch-independent swp_entry_t to
 * arch-dependent swp_entry_t, and __swp_entry_to_pte() just stores the result
 * to pte. But here we have 32bit swp_entry_t and 64bit pte, and need to use the
 * whole 64 bits. Thus, we shअगरt the "real" arch-dependent conversion to
 * __swp_entry_to_pte() through the following helper macro based on 64bit
 * __swp_entry().
 */
#घोषणा __swp_pteval_entry(type, offset) ((pteval_t) अणु \
	(~(pteval_t)(offset) << SWP_OFFSET_SHIFT >> SWP_TYPE_BITS) \
	| ((pteval_t)(type) << (64 - SWP_TYPE_BITS)) पूर्ण)

#घोषणा __swp_entry_to_pte(x)	((pte_t)अणु .pte = \
		__swp_pteval_entry(__swp_type(x), __swp_offset(x)) पूर्ण)
/*
 * Analogically, __pte_to_swp_entry() करोesn't just extract the arch-dependent
 * swp_entry_t, but also has to convert it from 64bit to the 32bit
 * पूर्णांकermediate representation, using the following macros based on 64bit
 * __swp_type() and __swp_offset().
 */
#घोषणा __pteval_swp_type(x) ((अचिन्हित दीर्घ)((x).pte >> (64 - SWP_TYPE_BITS)))
#घोषणा __pteval_swp_offset(x) ((अचिन्हित दीर्घ)(~((x).pte) << SWP_TYPE_BITS >> SWP_OFFSET_SHIFT))

#घोषणा __pte_to_swp_entry(pte)	(__swp_entry(__pteval_swp_type(pte), \
					     __pteval_swp_offset(pte)))

#समावेश <यंत्र/pgtable-invert.h>

#पूर्ण_अगर /* _ASM_X86_PGTABLE_3LEVEL_H */
