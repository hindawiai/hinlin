<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PGALLOC_H
#घोषणा _ASM_POWERPC_PGALLOC_H

#समावेश <linux/mm.h>

#अगर_अघोषित MODULE
अटल अंतरभूत gfp_t pgtable_gfp_flags(काष्ठा mm_काष्ठा *mm, gfp_t gfp)
अणु
	अगर (unlikely(mm == &init_mm))
		वापस gfp;
	वापस gfp | __GFP_ACCOUNT;
पूर्ण
#अन्यथा /* !MODULE */
अटल अंतरभूत gfp_t pgtable_gfp_flags(काष्ठा mm_काष्ठा *mm, gfp_t gfp)
अणु
	वापस gfp | __GFP_ACCOUNT;
पूर्ण
#पूर्ण_अगर /* MODULE */

#घोषणा PGALLOC_GFP (GFP_KERNEL | __GFP_ZERO)

pte_t *pte_fragment_alloc(काष्ठा mm_काष्ठा *mm, पूर्णांक kernel);

अटल अंतरभूत pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	वापस (pte_t *)pte_fragment_alloc(mm, 1);
पूर्ण

अटल अंतरभूत pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	वापस (pgtable_t)pte_fragment_alloc(mm, 0);
पूर्ण

व्योम pte_frag_destroy(व्योम *pte_frag);
व्योम pte_fragment_मुक्त(अचिन्हित दीर्घ *table, पूर्णांक kernel);

अटल अंतरभूत व्योम pte_मुक्त_kernel(काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	pte_fragment_मुक्त((अचिन्हित दीर्घ *)pte, 1);
पूर्ण

अटल अंतरभूत व्योम pte_मुक्त(काष्ठा mm_काष्ठा *mm, pgtable_t ptepage)
अणु
	pte_fragment_मुक्त((अचिन्हित दीर्घ *)ptepage, 0);
पूर्ण

/*
 * Functions that deal with pagetables that could be at any level of
 * the table need to be passed an "index_size" so they know how to
 * handle allocation.  For PTE pages, the allocation size will be
 * (2^index_size * माप(poपूर्णांकer)) and allocations are drawn from
 * the kmem_cache in PGT_CACHE(index_size).
 *
 * The maximum index size needs to be big enough to allow any
 * pagetable sizes we need, but small enough to fit in the low bits of
 * any page table poपूर्णांकer.  In other words all pagetables, even tiny
 * ones, must be aligned to allow at least enough low 0 bits to
 * contain this value.  This value is also used as a mask, so it must
 * be one less than a घातer of two.
 */
#घोषणा MAX_PGTABLE_INDEX_SIZE	0xf

बाह्य काष्ठा kmem_cache *pgtable_cache[];
#घोषणा PGT_CACHE(shअगरt) pgtable_cache[shअगरt]

#अगर_घोषित CONFIG_PPC_BOOK3S
#समावेश <यंत्र/book3s/pgभाग.स>
#अन्यथा
#समावेश <यंत्र/nohash/pgभाग.स>
#पूर्ण_अगर

अटल अंतरभूत pgtable_t pmd_pgtable(pmd_t pmd)
अणु
	वापस (pgtable_t)pmd_page_vaddr(pmd);
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_PGALLOC_H */
