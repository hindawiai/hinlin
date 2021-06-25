<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_2LEVEL_DEFS_H
#घोषणा _ASM_X86_PGTABLE_2LEVEL_DEFS_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

प्रकार अचिन्हित दीर्घ	pteval_t;
प्रकार अचिन्हित दीर्घ	pmdval_t;
प्रकार अचिन्हित दीर्घ	pudval_t;
प्रकार अचिन्हित दीर्घ	p4dval_t;
प्रकार अचिन्हित दीर्घ	pgdval_t;
प्रकार अचिन्हित दीर्घ	pgprotval_t;

प्रकार जोड़ अणु
	pteval_t pte;
	pteval_t pte_low;
पूर्ण pte_t;
#पूर्ण_अगर	/* !__ASSEMBLY__ */

#घोषणा SHARED_KERNEL_PMD	0

#घोषणा ARCH_PAGE_TABLE_SYNC_MASK	PGTBL_PMD_MODIFIED

/*
 * traditional i386 two-level paging काष्ठाure:
 */

#घोषणा PGसूची_SHIFT	22
#घोषणा PTRS_PER_PGD	1024


/*
 * the i386 is two-level, so we करोn't really have any
 * PMD directory physically.
 */

#घोषणा PTRS_PER_PTE	1024

/* This covers all VMSPLIT_* and VMSPLIT_*_OPT variants */
#घोषणा PGD_KERNEL_START	(CONFIG_PAGE_OFFSET >> PGसूची_SHIFT)

#पूर्ण_अगर /* _ASM_X86_PGTABLE_2LEVEL_DEFS_H */
