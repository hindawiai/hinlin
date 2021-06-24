<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)
 * Copyright 2003 PathScale, Inc.
 * Derived from include/यंत्र-i386/pgभाग.स and include/यंत्र-i386/pgtable.h
 */

#अगर_अघोषित __UM_PGALLOC_H
#घोषणा __UM_PGALLOC_H

#समावेश <linux/mm.h>

#समावेश <यंत्र-generic/pgभाग.स>

#घोषणा pmd_populate_kernel(mm, pmd, pte) \
	set_pmd(pmd, __pmd(_PAGE_TABLE + (अचिन्हित दीर्घ) __pa(pte)))

#घोषणा pmd_populate(mm, pmd, pte) 				\
	set_pmd(pmd, __pmd(_PAGE_TABLE +			\
		((अचिन्हित दीर्घ दीर्घ)page_to_pfn(pte) <<	\
			(अचिन्हित दीर्घ दीर्घ) PAGE_SHIFT)))
#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

/*
 * Allocate and मुक्त page tables.
 */
बाह्य pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *);

#घोषणा __pte_मुक्त_tlb(tlb,pte, address)		\
करो अणु							\
	pgtable_pte_page_dtor(pte);			\
	tlb_हटाओ_page((tlb),(pte));			\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_3_LEVEL_PGTABLES

#घोषणा __pmd_मुक्त_tlb(tlb, pmd, address)		\
करो अणु							\
	pgtable_pmd_page_dtor(virt_to_page(pmd));	\
	tlb_हटाओ_page((tlb),virt_to_page(pmd));	\
पूर्ण जबतक (0)						\

#पूर्ण_अगर

#पूर्ण_अगर

