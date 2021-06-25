<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PGTABLE_INVERT_H
#घोषणा _ASM_PGTABLE_INVERT_H 1

#अगर_अघोषित __ASSEMBLY__

/*
 * A clear pte value is special, and करोesn't get inverted.
 *
 * Note that even users that only pass a pgprot_t (rather
 * than a full pte) won't trigger the special zero हाल,
 * because even PAGE_NONE has _PAGE_PROTNONE | _PAGE_ACCESSED
 * set. So the all zero हाल really is limited to just the
 * cleared page table entry हाल.
 */
अटल अंतरभूत bool __pte_needs_invert(u64 val)
अणु
	वापस val && !(val & _PAGE_PRESENT);
पूर्ण

/* Get a mask to xor with the page table entry to get the correct pfn. */
अटल अंतरभूत u64 protnone_mask(u64 val)
अणु
	वापस __pte_needs_invert(val) ?  ~0ull : 0;
पूर्ण

अटल अंतरभूत u64 flip_protnone_guard(u64 oldval, u64 val, u64 mask)
अणु
	/*
	 * When a PTE transitions from NONE to !NONE or vice-versa
	 * invert the PFN part to stop speculation.
	 * pte_pfn unकरोes this when needed.
	 */
	अगर (__pte_needs_invert(oldval) != __pte_needs_invert(val))
		val = (val & ~mask) | (~val & mask);
	वापस val;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
