<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_PGALLOC_H
#घोषणा _SPARC64_PGALLOC_H

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/page.h>

/* Page table allocation/मुक्तing. */

बाह्य काष्ठा kmem_cache *pgtable_cache;

अटल अंतरभूत व्योम __p4d_populate(p4d_t *p4d, pud_t *pud)
अणु
	p4d_set(p4d, pud);
पूर्ण

#घोषणा p4d_populate(MM, P4D, PUD)	__p4d_populate(P4D, PUD)

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस kmem_cache_alloc(pgtable_cache, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	kmem_cache_मुक्त(pgtable_cache, pgd);
पूर्ण

अटल अंतरभूत व्योम __pud_populate(pud_t *pud, pmd_t *pmd)
अणु
	pud_set(pud, pmd);
पूर्ण

#घोषणा pud_populate(MM, PUD, PMD)	__pud_populate(PUD, PMD)

अटल अंतरभूत pud_t *pud_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस kmem_cache_alloc(pgtable_cache, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम pud_मुक्त(काष्ठा mm_काष्ठा *mm, pud_t *pud)
अणु
	kmem_cache_मुक्त(pgtable_cache, pud);
पूर्ण

अटल अंतरभूत pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस kmem_cache_alloc(pgtable_cache, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	kmem_cache_मुक्त(pgtable_cache, pmd);
पूर्ण

pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm);
pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm);
व्योम pte_मुक्त_kernel(काष्ठा mm_काष्ठा *mm, pte_t *pte);
व्योम pte_मुक्त(काष्ठा mm_काष्ठा *mm, pgtable_t ptepage);

#घोषणा pmd_populate_kernel(MM, PMD, PTE)	pmd_set(MM, PMD, PTE)
#घोषणा pmd_populate(MM, PMD, PTE)		pmd_set(MM, PMD, PTE)
#घोषणा pmd_pgtable(PMD)			((pte_t *)pmd_page_vaddr(PMD))

व्योम pgtable_मुक्त(व्योम *table, bool is_page);

#अगर_घोषित CONFIG_SMP

काष्ठा mmu_gather;
व्योम tlb_हटाओ_table(काष्ठा mmu_gather *, व्योम *);

अटल अंतरभूत व्योम pgtable_मुक्त_tlb(काष्ठा mmu_gather *tlb, व्योम *table, bool is_page)
अणु
	अचिन्हित दीर्घ pgf = (अचिन्हित दीर्घ)table;
	अगर (is_page)
		pgf |= 0x1UL;
	tlb_हटाओ_table(tlb, (व्योम *)pgf);
पूर्ण

अटल अंतरभूत व्योम __tlb_हटाओ_table(व्योम *_table)
अणु
	व्योम *table = (व्योम *)((अचिन्हित दीर्घ)_table & ~0x1UL);
	bool is_page = false;

	अगर ((अचिन्हित दीर्घ)_table & 0x1UL)
		is_page = true;
	pgtable_मुक्त(table, is_page);
पूर्ण
#अन्यथा /* CONFIG_SMP */
अटल अंतरभूत व्योम pgtable_मुक्त_tlb(काष्ठा mmu_gather *tlb, व्योम *table, bool is_page)
अणु
	pgtable_मुक्त(table, is_page);
पूर्ण
#पूर्ण_अगर /* !CONFIG_SMP */

अटल अंतरभूत व्योम __pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, pte_t *pte,
				  अचिन्हित दीर्घ address)
अणु
	pgtable_मुक्त_tlb(tlb, pte, true);
पूर्ण

#घोषणा __pmd_मुक्त_tlb(tlb, pmd, addr)		      \
	pgtable_मुक्त_tlb(tlb, pmd, false)

#घोषणा __pud_मुक्त_tlb(tlb, pud, addr)		      \
	pgtable_मुक्त_tlb(tlb, pud, false)

#पूर्ण_अगर /* _SPARC64_PGALLOC_H */
