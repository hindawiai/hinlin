<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_32_PGALLOC_H
#घोषणा _ASM_POWERPC_BOOK3S_32_PGALLOC_H

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/slab.h>

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस kmem_cache_alloc(PGT_CACHE(PGD_INDEX_SIZE),
			pgtable_gfp_flags(mm, GFP_KERNEL));
पूर्ण

अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	kmem_cache_मुक्त(PGT_CACHE(PGD_INDEX_SIZE), pgd);
पूर्ण

/*
 * We करोn't have any real pmd's, and this code never triggers because
 * the pgd will always be present..
 */
/* #घोषणा pmd_alloc_one(mm,address)       (अणु BUG(); ((pmd_t *)2); पूर्ण) */
#घोषणा pmd_मुक्त(mm, x) 		करो अणु पूर्ण जबतक (0)
#घोषणा __pmd_मुक्त_tlb(tlb,x,a)		करो अणु पूर्ण जबतक (0)
/* #घोषणा pgd_populate(mm, pmd, pte)      BUG() */

अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				       pte_t *pte)
अणु
	*pmdp = __pmd(__pa(pte) | _PMD_PRESENT);
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				pgtable_t pte_page)
अणु
	*pmdp = __pmd(__pa(pte_page) | _PMD_PRESENT);
पूर्ण

अटल अंतरभूत व्योम pgtable_मुक्त(व्योम *table, अचिन्हित index_size)
अणु
	अगर (!index_size) अणु
		pte_fragment_मुक्त((अचिन्हित दीर्घ *)table, 0);
	पूर्ण अन्यथा अणु
		BUG_ON(index_size > MAX_PGTABLE_INDEX_SIZE);
		kmem_cache_मुक्त(PGT_CACHE(index_size), table);
	पूर्ण
पूर्ण

#घोषणा get_hugepd_cache_index(x)  (x)

अटल अंतरभूत व्योम pgtable_मुक्त_tlb(काष्ठा mmu_gather *tlb,
				    व्योम *table, पूर्णांक shअगरt)
अणु
	अचिन्हित दीर्घ pgf = (अचिन्हित दीर्घ)table;
	BUG_ON(shअगरt > MAX_PGTABLE_INDEX_SIZE);
	pgf |= shअगरt;
	tlb_हटाओ_table(tlb, (व्योम *)pgf);
पूर्ण

अटल अंतरभूत व्योम __tlb_हटाओ_table(व्योम *_table)
अणु
	व्योम *table = (व्योम *)((अचिन्हित दीर्घ)_table & ~MAX_PGTABLE_INDEX_SIZE);
	अचिन्हित shअगरt = (अचिन्हित दीर्घ)_table & MAX_PGTABLE_INDEX_SIZE;

	pgtable_मुक्त(table, shअगरt);
पूर्ण

अटल अंतरभूत व्योम __pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, pgtable_t table,
				  अचिन्हित दीर्घ address)
अणु
	pgtable_मुक्त_tlb(tlb, table, 0);
पूर्ण
#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_32_PGALLOC_H */
