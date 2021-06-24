<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_PGALLOC_64_H
#घोषणा _ASM_POWERPC_PGALLOC_64_H
/*
 */

#समावेश <linux/slab.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/percpu.h>

काष्ठा vmemmap_backing अणु
	काष्ठा vmemmap_backing *list;
	अचिन्हित दीर्घ phys;
	अचिन्हित दीर्घ virt_addr;
पूर्ण;
बाह्य काष्ठा vmemmap_backing *vmemmap_list;

#घोषणा p4d_populate(MM, P4D, PUD)	p4d_set(P4D, (अचिन्हित दीर्घ)PUD)

अटल अंतरभूत pud_t *pud_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस kmem_cache_alloc(PGT_CACHE(PUD_INDEX_SIZE),
			pgtable_gfp_flags(mm, GFP_KERNEL));
पूर्ण

अटल अंतरभूत व्योम pud_मुक्त(काष्ठा mm_काष्ठा *mm, pud_t *pud)
अणु
	kmem_cache_मुक्त(PGT_CACHE(PUD_INDEX_SIZE), pud);
पूर्ण

अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	pud_set(pud, (अचिन्हित दीर्घ)pmd);
पूर्ण

अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				       pte_t *pte)
अणु
	pmd_set(pmd, (अचिन्हित दीर्घ)pte);
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				pgtable_t pte_page)
अणु
	pmd_set(pmd, (अचिन्हित दीर्घ)pte_page);
पूर्ण

अटल अंतरभूत pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस kmem_cache_alloc(PGT_CACHE(PMD_CACHE_INDEX),
			pgtable_gfp_flags(mm, GFP_KERNEL));
पूर्ण

अटल अंतरभूत व्योम pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	kmem_cache_मुक्त(PGT_CACHE(PMD_CACHE_INDEX), pmd);
पूर्ण

#घोषणा __pmd_मुक्त_tlb(tlb, pmd, addr)		      \
	pgtable_मुक्त_tlb(tlb, pmd, PMD_CACHE_INDEX)
#घोषणा __pud_मुक्त_tlb(tlb, pud, addr)		      \
	pgtable_मुक्त_tlb(tlb, pud, PUD_INDEX_SIZE)

#पूर्ण_अगर /* _ASM_POWERPC_PGALLOC_64_H */
