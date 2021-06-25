<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_PGALLOC_H
#घोषणा __ASM_CSKY_PGALLOC_H

#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>

#घोषणा __HAVE_ARCH_PTE_ALLOC_ONE_KERNEL
#समावेश <यंत्र-generic/pgभाग.स>

अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
					pte_t *pte)
अणु
	set_pmd(pmd, __pmd(__pa(pte)));
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
					pgtable_t pte)
अणु
	set_pmd(pmd, __pmd(__pa(page_address(pte))));
पूर्ण

#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

बाह्य व्योम pgd_init(अचिन्हित दीर्घ *p);

अटल अंतरभूत pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	pte_t *pte;
	अचिन्हित दीर्घ i;

	pte = (pte_t *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!pte)
		वापस शून्य;

	क्रम (i = 0; i < PAGE_SIZE/माप(pte_t); i++)
		(pte + i)->pte_low = _PAGE_GLOBAL;

	वापस pte;
पूर्ण

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *ret;
	pgd_t *init;

	ret = (pgd_t *) __get_मुक्त_pages(GFP_KERNEL, PGD_ORDER);
	अगर (ret) अणु
		init = pgd_offset(&init_mm, 0UL);
		pgd_init((अचिन्हित दीर्घ *)ret);
		स_नकल(ret + USER_PTRS_PER_PGD, init + USER_PTRS_PER_PGD,
			(PTRS_PER_PGD - USER_PTRS_PER_PGD) * माप(pgd_t));
		/* prevent out of order excute */
		smp_mb();
#अगर_घोषित CONFIG_CPU_NEED_TLBSYNC
		dcache_wb_range((अचिन्हित पूर्णांक)ret,
				(अचिन्हित पूर्णांक)(ret + PTRS_PER_PGD));
#पूर्ण_अगर
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा __pte_मुक्त_tlb(tlb, pte, address)		\
करो अणु							\
	pgtable_pte_page_dtor(pte);			\
	tlb_हटाओ_page(tlb, pte);			\
पूर्ण जबतक (0)

बाह्य व्योम pagetable_init(व्योम);
बाह्य व्योम mmu_init(अचिन्हित दीर्घ min_pfn, अचिन्हित दीर्घ max_pfn);
बाह्य व्योम pre_trap_init(व्योम);

#पूर्ण_अगर /* __ASM_CSKY_PGALLOC_H */
