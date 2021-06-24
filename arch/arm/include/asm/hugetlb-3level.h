<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/hugetlb-3level.h
 *
 * Copyright (C) 2012 ARM Ltd.
 *
 * Based on arch/x86/include/यंत्र/hugetlb.h.
 */

#अगर_अघोषित _ASM_ARM_HUGETLB_3LEVEL_H
#घोषणा _ASM_ARM_HUGETLB_3LEVEL_H


/*
 * If our huge pte is non-zero then mark the valid bit.
 * This allows pte_present(huge_ptep_get(ptep)) to वापस true क्रम non-zero
 * ptes.
 * (The valid bit is स्वतःmatically cleared by set_pte_at क्रम PROT_NONE ptes).
 */
#घोषणा __HAVE_ARCH_HUGE_PTEP_GET
अटल अंतरभूत pte_t huge_ptep_get(pte_t *ptep)
अणु
	pte_t retval = *ptep;
	अगर (pte_val(retval))
		pte_val(retval) |= L_PTE_VALID;
	वापस retval;
पूर्ण

#पूर्ण_अगर /* _ASM_ARM_HUGETLB_3LEVEL_H */
