<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: June 2011
 *  -"/proc/meminfo | grep PageTables" kept on increasing
 *   Recently added pgtable dtor was not getting called.
 *
 * vineetg: May 2011
 *  -Variable pg-sz means that Page Tables could be variable sized themselves
 *    So calculate it based on addr traversal split [pgd-bits:pte-bits:xxx]
 *  -Page Table size capped to max 1 to save memory - hence verअगरied.
 *  -Since these deal with स्थिरants, gcc compile-समय optimizes them.
 *
 * vineetg: Nov 2010
 *  -Added pgtable ctor/dtor used क्रम pgtable mem accounting
 *
 * vineetg: April 2010
 *  -Switched pgtable_t from being काष्ठा page * to अचिन्हित दीर्घ
 *      =Needed so that Page Table allocator (pte_alloc_one) is not क्रमced to
 *       deal with काष्ठा page. That way in future we can make it allocate
 *       multiple PG Tbls in one Page Frame
 *      =sweet side effect is aव्योमing calls to ugly page_address( ) from the
 *       pg-tlb allocator sub-sys (pte_alloc_one, ptr_मुक्त, pmd_populate)
 *
 *  Amit Bhor, Sameer Dhavale: Codito Technologies 2004
 */

#अगर_अघोषित _ASM_ARC_PGALLOC_H
#घोषणा _ASM_ARC_PGALLOC_H

#समावेश <linux/mm.h>
#समावेश <linux/log2.h>

अटल अंतरभूत व्योम
pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, pte_t *pte)
अणु
	pmd_set(pmd, pte);
पूर्ण

अटल अंतरभूत व्योम
pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, pgtable_t ptep)
अणु
	pmd_set(pmd, (pte_t *) ptep);
पूर्ण

अटल अंतरभूत पूर्णांक __get_order_pgd(व्योम)
अणु
	वापस get_order(PTRS_PER_PGD * माप(pgd_t));
पूर्ण

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक num, num2;
	pgd_t *ret = (pgd_t *) __get_मुक्त_pages(GFP_KERNEL, __get_order_pgd());

	अगर (ret) अणु
		num = USER_PTRS_PER_PGD + USER_KERNEL_GUTTER / PGसूची_SIZE;
		memzero(ret, num * माप(pgd_t));

		num2 = VMALLOC_SIZE / PGसूची_SIZE;
		स_नकल(ret + num, swapper_pg_dir + num, num2 * माप(pgd_t));

		memzero(ret + num + num2,
			       (PTRS_PER_PGD - num - num2) * माप(pgd_t));

	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)pgd, __get_order_pgd());
पूर्ण


/*
 * With software-only page-tables, addr-split क्रम traversal is tweakable and
 * that directly governs how big tables would be at each level.
 * Further, the MMU page size is configurable.
 * Thus we need to programatically निश्चित the size स्थिरraपूर्णांक
 * All of this is स्थिर math, allowing gcc to करो स्थिरant folding/propagation.
 */

अटल अंतरभूत पूर्णांक __get_order_pte(व्योम)
अणु
	वापस get_order(PTRS_PER_PTE * माप(pte_t));
पूर्ण

अटल अंतरभूत pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	pte_t *pte;

	pte = (pte_t *) __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					 __get_order_pte());

	वापस pte;
पूर्ण

अटल अंतरभूत pgtable_t
pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	pgtable_t pte_pg;
	काष्ठा page *page;

	pte_pg = (pgtable_t)__get_मुक्त_pages(GFP_KERNEL, __get_order_pte());
	अगर (!pte_pg)
		वापस 0;
	memzero((व्योम *)pte_pg, PTRS_PER_PTE * माप(pte_t));
	page = virt_to_page(pte_pg);
	अगर (!pgtable_pte_page_ctor(page)) अणु
		__मुक्त_page(page);
		वापस 0;
	पूर्ण

	वापस pte_pg;
पूर्ण

अटल अंतरभूत व्योम pte_मुक्त_kernel(काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)pte, __get_order_pte()); /* takes phy addr */
पूर्ण

अटल अंतरभूत व्योम pte_मुक्त(काष्ठा mm_काष्ठा *mm, pgtable_t ptep)
अणु
	pgtable_pte_page_dtor(virt_to_page(ptep));
	मुक्त_pages((अचिन्हित दीर्घ)ptep, __get_order_pte());
पूर्ण

#घोषणा __pte_मुक्त_tlb(tlb, pte, addr)  pte_मुक्त((tlb)->mm, pte)

#घोषणा pmd_pgtable(pmd)	((pgtable_t) pmd_page_vaddr(pmd))

#पूर्ण_अगर /* _ASM_ARC_PGALLOC_H */
