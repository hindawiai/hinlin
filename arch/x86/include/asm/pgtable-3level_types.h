<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_3LEVEL_DEFS_H
#घोषणा _ASM_X86_PGTABLE_3LEVEL_DEFS_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

प्रकार u64	pteval_t;
प्रकार u64	pmdval_t;
प्रकार u64	pudval_t;
प्रकार u64	p4dval_t;
प्रकार u64	pgdval_t;
प्रकार u64	pgprotval_t;

प्रकार जोड़ अणु
	काष्ठा अणु
		अचिन्हित दीर्घ pte_low, pte_high;
	पूर्ण;
	pteval_t pte;
पूर्ण pte_t;
#पूर्ण_अगर	/* !__ASSEMBLY__ */

#घोषणा SHARED_KERNEL_PMD	(!अटल_cpu_has(X86_FEATURE_PTI))

#घोषणा ARCH_PAGE_TABLE_SYNC_MASK	(SHARED_KERNEL_PMD ? 0 : PGTBL_PMD_MODIFIED)

/*
 * PGसूची_SHIFT determines what a top-level page table entry can map
 */
#घोषणा PGसूची_SHIFT	30
#घोषणा PTRS_PER_PGD	4

/*
 * PMD_SHIFT determines the size of the area a middle-level
 * page table can map
 */
#घोषणा PMD_SHIFT	21
#घोषणा PTRS_PER_PMD	512

/*
 * entries per page directory level
 */
#घोषणा PTRS_PER_PTE	512

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS	36
#घोषणा PGD_KERNEL_START	(CONFIG_PAGE_OFFSET >> PGसूची_SHIFT)

#पूर्ण_अगर /* _ASM_X86_PGTABLE_3LEVEL_DEFS_H */
