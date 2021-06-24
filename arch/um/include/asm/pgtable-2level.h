<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)
 * Copyright 2003 PathScale, Inc.
 * Derived from include/यंत्र-i386/pgtable.h
 */

#अगर_अघोषित __UM_PGTABLE_2LEVEL_H
#घोषणा __UM_PGTABLE_2LEVEL_H

#समावेश <यंत्र-generic/pgtable-nopmd.h>

/* PGसूची_SHIFT determines what a third-level page table entry can map */

#घोषणा PGसूची_SHIFT	22
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/*
 * entries per page directory level: the i386 is two-level, so
 * we करोn't really have any PMD directory physically.
 */
#घोषणा PTRS_PER_PTE	1024
#घोषणा USER_PTRS_PER_PGD ((TASK_SIZE + (PGसूची_SIZE - 1)) / PGसूची_SIZE)
#घोषणा PTRS_PER_PGD	1024
#घोषणा FIRST_USER_ADDRESS	0UL

#घोषणा pte_ERROR(e) \
        prपूर्णांकk("%s:%d: bad pte %p(%08lx).\n", __खाता__, __LINE__, &(e), \
	       pte_val(e))
#घोषणा pgd_ERROR(e) \
        prपूर्णांकk("%s:%d: bad pgd %p(%08lx).\n", __खाता__, __LINE__, &(e), \
	       pgd_val(e))

अटल अंतरभूत पूर्णांक pgd_newpage(pgd_t pgd)	अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pgd_mkuptodate(pgd_t pgd)	अणु पूर्ण

#घोषणा set_pmd(pmdptr, pmdval) (*(pmdptr) = (pmdval))

#घोषणा pte_pfn(x) phys_to_pfn(pte_val(x))
#घोषणा pfn_pte(pfn, prot) __pte(pfn_to_phys(pfn) | pgprot_val(prot))
#घोषणा pfn_pmd(pfn, prot) __pmd(pfn_to_phys(pfn) | pgprot_val(prot))

#पूर्ण_अगर
