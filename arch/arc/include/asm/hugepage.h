<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013-15 Synopsys, Inc. (www.synopsys.com)
 */


#अगर_अघोषित _ASM_ARC_HUGEPAGE_H
#घोषणा _ASM_ARC_HUGEPAGE_H

#समावेश <linux/types.h>
#समावेश <यंत्र-generic/pgtable-nopmd.h>

अटल अंतरभूत pte_t pmd_pte(pmd_t pmd)
अणु
	वापस __pte(pmd_val(pmd));
पूर्ण

अटल अंतरभूत pmd_t pte_pmd(pte_t pte)
अणु
	वापस __pmd(pte_val(pte));
पूर्ण

#घोषणा pmd_wrprotect(pmd)	pte_pmd(pte_wrprotect(pmd_pte(pmd)))
#घोषणा pmd_mkग_लिखो(pmd)	pte_pmd(pte_mkग_लिखो(pmd_pte(pmd)))
#घोषणा pmd_सूची_गढ़ोty(pmd)	pte_pmd(pte_सूची_गढ़ोty(pmd_pte(pmd)))
#घोषणा pmd_mkold(pmd)		pte_pmd(pte_mkold(pmd_pte(pmd)))
#घोषणा pmd_mkyoung(pmd)	pte_pmd(pte_mkyoung(pmd_pte(pmd)))
#घोषणा pmd_mkhuge(pmd)		pte_pmd(pte_mkhuge(pmd_pte(pmd)))
#घोषणा pmd_mkinvalid(pmd)	pte_pmd(pte_mknotpresent(pmd_pte(pmd)))
#घोषणा pmd_mkclean(pmd)	pte_pmd(pte_mkclean(pmd_pte(pmd)))

#घोषणा pmd_ग_लिखो(pmd)		pte_ग_लिखो(pmd_pte(pmd))
#घोषणा pmd_young(pmd)		pte_young(pmd_pte(pmd))
#घोषणा pmd_pfn(pmd)		pte_pfn(pmd_pte(pmd))
#घोषणा pmd_dirty(pmd)		pte_dirty(pmd_pte(pmd))

#घोषणा mk_pmd(page, prot)	pte_pmd(mk_pte(page, prot))

#घोषणा pmd_trans_huge(pmd)	(pmd_val(pmd) & _PAGE_HW_SZ)

#घोषणा pfn_pmd(pfn, prot)	(__pmd(((pfn) << PAGE_SHIFT) | pgprot_val(prot)))

अटल अंतरभूत pmd_t pmd_modअगरy(pmd_t pmd, pgprot_t newprot)
अणु
        /*
         * खोलो-coded pte_modअगरy() with additional retaining of HW_SZ bit
         * so that pmd_trans_huge() reमुख्यs true क्रम this PMD
         */
        वापस __pmd((pmd_val(pmd) & (_PAGE_CHG_MASK | _PAGE_HW_SZ)) | pgprot_val(newprot));
पूर्ण

अटल अंतरभूत व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pmd_t *pmdp, pmd_t pmd)
अणु
	*pmdp = pmd;
पूर्ण

बाह्य व्योम update_mmu_cache_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				 pmd_t *pmd);

/* Generic variants assume pgtable_t is काष्ठा page *, hence need क्रम these */
#घोषणा __HAVE_ARCH_PGTABLE_DEPOSIT
बाह्य व्योम pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				       pgtable_t pgtable);

#घोषणा __HAVE_ARCH_PGTABLE_WITHDRAW
बाह्य pgtable_t pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp);

#घोषणा __HAVE_ARCH_FLUSH_PMD_TLB_RANGE
बाह्य व्योम flush_pmd_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ end);

/* We करोn't have hardware dirty/accessed bits, generic_pmdp_establish is fine.*/
#घोषणा pmdp_establish generic_pmdp_establish

#पूर्ण_अगर
