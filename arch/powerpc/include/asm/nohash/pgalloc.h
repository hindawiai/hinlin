<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_PGALLOC_H
#घोषणा _ASM_POWERPC_NOHASH_PGALLOC_H

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

बाह्य व्योम tlb_हटाओ_table(काष्ठा mmu_gather *tlb, व्योम *table);
#अगर_घोषित CONFIG_PPC64
बाह्य व्योम tlb_flush_pgtable(काष्ठा mmu_gather *tlb, अचिन्हित दीर्घ address);
#अन्यथा
/* 44x etc which is BOOKE not BOOK3E */
अटल अंतरभूत व्योम tlb_flush_pgtable(काष्ठा mmu_gather *tlb,
				     अचिन्हित दीर्घ address)
अणु

पूर्ण
#पूर्ण_अगर /* !CONFIG_PPC_BOOK3E */

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस kmem_cache_alloc(PGT_CACHE(PGD_INDEX_SIZE),
			pgtable_gfp_flags(mm, GFP_KERNEL));
पूर्ण

अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	kmem_cache_मुक्त(PGT_CACHE(PGD_INDEX_SIZE), pgd);
पूर्ण

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/nohash/64/pgभाग.स>
#अन्यथा
#समावेश <यंत्र/nohash/32/pgभाग.स>
#पूर्ण_अगर

अटल अंतरभूत व्योम pgtable_मुक्त(व्योम *table, पूर्णांक shअगरt)
अणु
	अगर (!shअगरt) अणु
		pte_fragment_मुक्त((अचिन्हित दीर्घ *)table, 0);
	पूर्ण अन्यथा अणु
		BUG_ON(shअगरt > MAX_PGTABLE_INDEX_SIZE);
		kmem_cache_मुक्त(PGT_CACHE(shअगरt), table);
	पूर्ण
पूर्ण

#घोषणा get_hugepd_cache_index(x)	(x)

अटल अंतरभूत व्योम pgtable_मुक्त_tlb(काष्ठा mmu_gather *tlb, व्योम *table, पूर्णांक shअगरt)
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
	tlb_flush_pgtable(tlb, address);
	pgtable_मुक्त_tlb(tlb, table, 0);
पूर्ण
#पूर्ण_अगर /* _ASM_POWERPC_NOHASH_PGALLOC_H */
