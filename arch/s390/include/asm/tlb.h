<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _S390_TLB_H
#घोषणा _S390_TLB_H

/*
 * TLB flushing on s390 is complicated. The following requirement
 * from the principles of operation is the most arduous:
 *
 * "A valid table entry must not be changed जबतक it is attached
 * to any CPU and may be used क्रम translation by that CPU except to
 * (1) invalidate the entry by using INVALIDATE PAGE TABLE ENTRY,
 * or INVALIDATE DAT TABLE ENTRY, (2) alter bits 56-63 of a page
 * table entry, or (3) make a change by means of a COMPARE AND SWAP
 * AND PURGE inकाष्ठाion that purges the TLB."
 *
 * The modअगरication of a pte of an active mm काष्ठा thereक्रमe is
 * a two step process: i) invalidate the pte, ii) store the new pte.
 * This is true क्रम the page protection bit as well.
 * The only possible optimization is to flush at the beginning of
 * a tlb_gather_mmu cycle अगर the mm_काष्ठा is currently not in use.
 *
 * Pages used क्रम the page tables is a dअगरferent story. FIXME: more
 */

व्योम __tlb_हटाओ_table(व्योम *_table);
अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb);
अटल अंतरभूत bool __tlb_हटाओ_page_size(काष्ठा mmu_gather *tlb,
					  काष्ठा page *page, पूर्णांक page_size);

#घोषणा tlb_start_vma(tlb, vma)			करो अणु पूर्ण जबतक (0)
#घोषणा tlb_end_vma(tlb, vma)			करो अणु पूर्ण जबतक (0)

#घोषणा tlb_flush tlb_flush
#घोषणा pte_मुक्त_tlb pte_मुक्त_tlb
#घोषणा pmd_मुक्त_tlb pmd_मुक्त_tlb
#घोषणा p4d_मुक्त_tlb p4d_मुक्त_tlb
#घोषणा pud_मुक्त_tlb pud_मुक्त_tlb

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र-generic/tlb.h>

/*
 * Release the page cache reference क्रम a pte हटाओd by
 * tlb_ptep_clear_flush. In both flush modes the tlb क्रम a page cache page
 * has alपढ़ोy been मुक्तd, so just करो मुक्त_page_and_swap_cache.
 */
अटल अंतरभूत bool __tlb_हटाओ_page_size(काष्ठा mmu_gather *tlb,
					  काष्ठा page *page, पूर्णांक page_size)
अणु
	मुक्त_page_and_swap_cache(page);
	वापस false;
पूर्ण

अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	__tlb_flush_mm_lazy(tlb->mm);
पूर्ण

/*
 * pte_मुक्त_tlb मुक्तs a pte table and clears the CRSTE क्रम the
 * page table from the tlb.
 */
अटल अंतरभूत व्योम pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, pgtable_t pte,
                                अचिन्हित दीर्घ address)
अणु
	__tlb_adjust_range(tlb, address, PAGE_SIZE);
	tlb->mm->context.flush_mm = 1;
	tlb->मुक्तd_tables = 1;
	tlb->cleared_pmds = 1;
	/*
	 * page_table_मुक्त_rcu takes care of the allocation bit masks
	 * of the 2K table fragments in the 4K page table page,
	 * then calls tlb_हटाओ_table.
	 */
	page_table_मुक्त_rcu(tlb, (अचिन्हित दीर्घ *) pte, address);
पूर्ण

/*
 * pmd_मुक्त_tlb मुक्तs a pmd table and clears the CRSTE क्रम the
 * segment table entry from the tlb.
 * If the mm uses a two level page table the single pmd is मुक्तd
 * as the pgd. pmd_मुक्त_tlb checks the asce_limit against 2GB
 * to aव्योम the द्विगुन मुक्त of the pmd in this हाल.
 */
अटल अंतरभूत व्योम pmd_मुक्त_tlb(काष्ठा mmu_gather *tlb, pmd_t *pmd,
				अचिन्हित दीर्घ address)
अणु
	अगर (mm_pmd_folded(tlb->mm))
		वापस;
	pgtable_pmd_page_dtor(virt_to_page(pmd));
	__tlb_adjust_range(tlb, address, PAGE_SIZE);
	tlb->mm->context.flush_mm = 1;
	tlb->मुक्तd_tables = 1;
	tlb->cleared_puds = 1;
	tlb_हटाओ_table(tlb, pmd);
पूर्ण

/*
 * p4d_मुक्त_tlb मुक्तs a pud table and clears the CRSTE क्रम the
 * region second table entry from the tlb.
 * If the mm uses a four level page table the single p4d is मुक्तd
 * as the pgd. p4d_मुक्त_tlb checks the asce_limit against 8PB
 * to aव्योम the द्विगुन मुक्त of the p4d in this हाल.
 */
अटल अंतरभूत व्योम p4d_मुक्त_tlb(काष्ठा mmu_gather *tlb, p4d_t *p4d,
				अचिन्हित दीर्घ address)
अणु
	अगर (mm_p4d_folded(tlb->mm))
		वापस;
	__tlb_adjust_range(tlb, address, PAGE_SIZE);
	tlb->mm->context.flush_mm = 1;
	tlb->मुक्तd_tables = 1;
	tlb_हटाओ_table(tlb, p4d);
पूर्ण

/*
 * pud_मुक्त_tlb मुक्तs a pud table and clears the CRSTE क्रम the
 * region third table entry from the tlb.
 * If the mm uses a three level page table the single pud is मुक्तd
 * as the pgd. pud_मुक्त_tlb checks the asce_limit against 4TB
 * to aव्योम the द्विगुन मुक्त of the pud in this हाल.
 */
अटल अंतरभूत व्योम pud_मुक्त_tlb(काष्ठा mmu_gather *tlb, pud_t *pud,
				अचिन्हित दीर्घ address)
अणु
	अगर (mm_pud_folded(tlb->mm))
		वापस;
	tlb->mm->context.flush_mm = 1;
	tlb->मुक्तd_tables = 1;
	tlb->cleared_p4ds = 1;
	tlb_हटाओ_table(tlb, pud);
पूर्ण


#पूर्ण_अगर /* _S390_TLB_H */
