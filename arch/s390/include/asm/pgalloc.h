<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 *    Author(s): Harपंचांगut Penner (hp@de.ibm.com)
 *               Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Derived from "include/asm-i386/pgalloc.h"
 *    Copyright (C) 1994  Linus Torvalds
 */

#अगर_अघोषित _S390_PGALLOC_H
#घोषणा _S390_PGALLOC_H

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/माला.स>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>

#घोषणा CRST_ALLOC_ORDER 2

अचिन्हित दीर्घ *crst_table_alloc(काष्ठा mm_काष्ठा *);
व्योम crst_table_मुक्त(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ *);

अचिन्हित दीर्घ *page_table_alloc(काष्ठा mm_काष्ठा *);
काष्ठा page *page_table_alloc_pgste(काष्ठा mm_काष्ठा *mm);
व्योम page_table_मुक्त(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ *);
व्योम page_table_मुक्त_rcu(काष्ठा mmu_gather *, अचिन्हित दीर्घ *, अचिन्हित दीर्घ);
व्योम page_table_मुक्त_pgste(काष्ठा page *page);
बाह्य पूर्णांक page_table_allocate_pgste;

अटल अंतरभूत व्योम crst_table_init(अचिन्हित दीर्घ *crst, अचिन्हित दीर्घ entry)
अणु
	स_रखो64((u64 *)crst, entry, _CRST_ENTRIES);
पूर्ण

पूर्णांक crst_table_upgrade(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ limit);

अटल अंतरभूत अचिन्हित दीर्घ check_asce_limit(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
					     अचिन्हित दीर्घ len)
अणु
	पूर्णांक rc;

	अगर (addr + len > mm->context.asce_limit &&
	    addr + len <= TASK_SIZE) अणु
		rc = crst_table_upgrade(mm, addr + len);
		अगर (rc)
			वापस (अचिन्हित दीर्घ) rc;
	पूर्ण
	वापस addr;
पूर्ण

अटल अंतरभूत p4d_t *p4d_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ *table = crst_table_alloc(mm);

	अगर (table)
		crst_table_init(table, _REGION2_ENTRY_EMPTY);
	वापस (p4d_t *) table;
पूर्ण

अटल अंतरभूत व्योम p4d_मुक्त(काष्ठा mm_काष्ठा *mm, p4d_t *p4d)
अणु
	अगर (!mm_p4d_folded(mm))
		crst_table_मुक्त(mm, (अचिन्हित दीर्घ *) p4d);
पूर्ण

अटल अंतरभूत pud_t *pud_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ *table = crst_table_alloc(mm);
	अगर (table)
		crst_table_init(table, _REGION3_ENTRY_EMPTY);
	वापस (pud_t *) table;
पूर्ण

अटल अंतरभूत व्योम pud_मुक्त(काष्ठा mm_काष्ठा *mm, pud_t *pud)
अणु
	अगर (!mm_pud_folded(mm))
		crst_table_मुक्त(mm, (अचिन्हित दीर्घ *) pud);
पूर्ण

अटल अंतरभूत pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr)
अणु
	अचिन्हित दीर्घ *table = crst_table_alloc(mm);

	अगर (!table)
		वापस शून्य;
	crst_table_init(table, _SEGMENT_ENTRY_EMPTY);
	अगर (!pgtable_pmd_page_ctor(virt_to_page(table))) अणु
		crst_table_मुक्त(mm, table);
		वापस शून्य;
	पूर्ण
	वापस (pmd_t *) table;
पूर्ण

अटल अंतरभूत व्योम pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	अगर (mm_pmd_folded(mm))
		वापस;
	pgtable_pmd_page_dtor(virt_to_page(pmd));
	crst_table_मुक्त(mm, (अचिन्हित दीर्घ *) pmd);
पूर्ण

अटल अंतरभूत व्योम pgd_populate(काष्ठा mm_काष्ठा *mm, pgd_t *pgd, p4d_t *p4d)
अणु
	pgd_val(*pgd) = _REGION1_ENTRY | __pa(p4d);
पूर्ण

अटल अंतरभूत व्योम p4d_populate(काष्ठा mm_काष्ठा *mm, p4d_t *p4d, pud_t *pud)
अणु
	p4d_val(*p4d) = _REGION2_ENTRY | __pa(pud);
पूर्ण

अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	pud_val(*pud) = _REGION3_ENTRY | __pa(pmd);
पूर्ण

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस (pgd_t *) crst_table_alloc(mm);
पूर्ण

अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	crst_table_मुक्त(mm, (अचिन्हित दीर्घ *) pgd);
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm,
				pmd_t *pmd, pgtable_t pte)
अणु
	pmd_val(*pmd) = _SEGMENT_ENTRY + __pa(pte);
पूर्ण

#घोषणा pmd_populate_kernel(mm, pmd, pte) pmd_populate(mm, pmd, pte)

#घोषणा pmd_pgtable(pmd) \
	((pgtable_t)__va(pmd_val(pmd) & -माप(pte_t)*PTRS_PER_PTE))

/*
 * page table entry allocation/मुक्त routines.
 */
#घोषणा pte_alloc_one_kernel(mm) ((pte_t *)page_table_alloc(mm))
#घोषणा pte_alloc_one(mm) ((pte_t *)page_table_alloc(mm))

#घोषणा pte_मुक्त_kernel(mm, pte) page_table_मुक्त(mm, (अचिन्हित दीर्घ *) pte)
#घोषणा pte_मुक्त(mm, pte) page_table_मुक्त(mm, (अचिन्हित दीर्घ *) pte)

व्योम vmem_map_init(व्योम);
व्योम *vmem_crst_alloc(अचिन्हित दीर्घ val);
pte_t *vmem_pte_alloc(व्योम);

अचिन्हित दीर्घ base_asce_alloc(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ num_pages);
व्योम base_asce_मुक्त(अचिन्हित दीर्घ asce);

#पूर्ण_अगर /* _S390_PGALLOC_H */
