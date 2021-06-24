<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

अटल काष्ठा kmem_cache *pgd_cachep;
#अगर PAGETABLE_LEVELS > 2
अटल काष्ठा kmem_cache *pmd_cachep;
#पूर्ण_अगर

व्योम pgd_ctor(व्योम *x)
अणु
	pgd_t *pgd = x;

	स_रखो(pgd, 0, USER_PTRS_PER_PGD * माप(pgd_t));
	स_नकल(pgd + USER_PTRS_PER_PGD,
	       swapper_pg_dir + USER_PTRS_PER_PGD,
	       (PTRS_PER_PGD - USER_PTRS_PER_PGD) * माप(pgd_t));
पूर्ण

व्योम pgtable_cache_init(व्योम)
अणु
	pgd_cachep = kmem_cache_create("pgd_cache",
				       PTRS_PER_PGD * (1<<PTE_MAGNITUDE),
				       PAGE_SIZE, SLAB_PANIC, pgd_ctor);
#अगर PAGETABLE_LEVELS > 2
	pmd_cachep = kmem_cache_create("pmd_cache",
				       PTRS_PER_PMD * (1<<PTE_MAGNITUDE),
				       PAGE_SIZE, SLAB_PANIC, शून्य);
#पूर्ण_अगर
पूर्ण

pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस kmem_cache_alloc(pgd_cachep, GFP_KERNEL);
पूर्ण

व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	kmem_cache_मुक्त(pgd_cachep, pgd);
पूर्ण

#अगर PAGETABLE_LEVELS > 2
व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	set_pud(pud, __pud((अचिन्हित दीर्घ)pmd));
पूर्ण

pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address)
अणु
	वापस kmem_cache_alloc(pmd_cachep, GFP_KERNEL | __GFP_ZERO);
पूर्ण

व्योम pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	kmem_cache_मुक्त(pmd_cachep, pmd);
पूर्ण
#पूर्ण_अगर /* PAGETABLE_LEVELS > 2 */
