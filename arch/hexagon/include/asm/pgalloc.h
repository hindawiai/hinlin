<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Page table support क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_PGALLOC_H
#घोषणा _ASM_PGALLOC_H

#समावेश <यंत्र/mem-layout.h>
#समावेश <यंत्र/atomic.h>

#समावेश <यंत्र-generic/pgभाग.स>

बाह्य अचिन्हित दीर्घ दीर्घ kmap_generation;

/*
 * Page table creation पूर्णांकerface
 */
अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *pgd;

	pgd = (pgd_t *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);

	/*
	 * There may be better ways to करो this, but to ensure
	 * that new address spaces always contain the kernel
	 * base mapping, and to ensure that the user area is
	 * initially marked invalid, initialize the new map
	 * map with a copy of the kernel's persistent map.
	 */

	स_नकल(pgd, swapper_pg_dir, PTRS_PER_PGD*माप(pgd_t));
	mm->context.generation = kmap_generation;

	/* Physical version is what is passed to भव machine on चयन */
	mm->context.ptbase = __pa(pgd);

	वापस pgd;
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				pgtable_t pte)
अणु
	/*
	 * Conveniently, zero in 3 LSB means indirect 4K page table.
	 * Not so convenient when you're trying to vary the page size.
	 */
	set_pmd(pmd, __pmd(((अचिन्हित दीर्घ)page_to_pfn(pte) << PAGE_SHIFT) |
		HEXAGON_L1_PTE_SIZE));
पूर्ण

/*
 * Other architectures seem to have ways of making all processes
 * share the same pmd's क्रम their kernel mappings, but the v0.3
 * Hexagon VM spec has a "monolithic" L1 table क्रम user and kernel
 * segments.  We track "generations" of the kernel map to minimize
 * overhead, and update the "slave" copies of the kernel mappings
 * as part of चयन_mm.  However, we still need to update the
 * kernel map of the active thपढ़ो who's calling pmd_populate_kernel...
 */
अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				       pte_t *pte)
अणु
	बाह्य spinlock_t kmap_gen_lock;
	pmd_t *ppmd;
	पूर्णांक pmdindex;

	spin_lock(&kmap_gen_lock);
	kmap_generation++;
	mm->context.generation = kmap_generation;
	current->active_mm->context.generation = kmap_generation;
	spin_unlock(&kmap_gen_lock);

	set_pmd(pmd, __pmd(((अचिन्हित दीर्घ)__pa(pte)) | HEXAGON_L1_PTE_SIZE));

	/*
	 * Now the "slave" copy of the current thपढ़ो.
	 * This is poपूर्णांकer arithmetic, not byte addresses!
	 */
	pmdindex = (pgd_t *)pmd - mm->pgd;
	ppmd = (pmd_t *)current->active_mm->pgd + pmdindex;
	set_pmd(ppmd, __pmd(((अचिन्हित दीर्घ)__pa(pte)) | HEXAGON_L1_PTE_SIZE));
	अगर (pmdindex > max_kernel_seg)
		max_kernel_seg = pmdindex;
पूर्ण

#घोषणा __pte_मुक्त_tlb(tlb, pte, addr)		\
करो अणु						\
	pgtable_pte_page_dtor((pte));		\
	tlb_हटाओ_page((tlb), (pte));		\
पूर्ण जबतक (0)

#पूर्ण_अगर
