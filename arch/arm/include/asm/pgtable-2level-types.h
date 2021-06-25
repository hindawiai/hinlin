<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/pgtable-2level-types.h
 *
 * Copyright (C) 1995-2003 Russell King
 */
#अगर_अघोषित _ASM_PGTABLE_2LEVEL_TYPES_H
#घोषणा _ASM_PGTABLE_2LEVEL_TYPES_H

#समावेश <यंत्र/types.h>

प्रकार u32 pteval_t;
प्रकार u32 pmdval_t;

#अघोषित STRICT_MM_TYPECHECKS

#अगर_घोषित STRICT_MM_TYPECHECKS
/*
 * These are used to make use of C type-checking..
 */
प्रकार काष्ठा अणु pteval_t pte; पूर्ण pte_t;
प्रकार काष्ठा अणु pmdval_t pmd; पूर्ण pmd_t;
प्रकार काष्ठा अणु pmdval_t pgd[2]; पूर्ण pgd_t;
प्रकार काष्ठा अणु pteval_t pgprot; पूर्ण pgprot_t;

#घोषणा pte_val(x)      ((x).pte)
#घोषणा pmd_val(x)      ((x).pmd)
#घोषणा pgd_val(x)	((x).pgd[0])
#घोषणा pgprot_val(x)   ((x).pgprot)

#घोषणा __pte(x)        ((pte_t) अणु (x) पूर्ण )
#घोषणा __pmd(x)        ((pmd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)     ((pgprot_t) अणु (x) पूर्ण )

#अन्यथा
/*
 * .. जबतक these make it easier on the compiler
 */
प्रकार pteval_t pte_t;
प्रकार pmdval_t pmd_t;
प्रकार pmdval_t pgd_t[2];
प्रकार pteval_t pgprot_t;

#घोषणा pte_val(x)      (x)
#घोषणा pmd_val(x)      (x)
#घोषणा pgd_val(x)	((x)[0])
#घोषणा pgprot_val(x)   (x)

#घोषणा __pte(x)        (x)
#घोषणा __pmd(x)        (x)
#घोषणा __pgprot(x)     (x)

#पूर्ण_अगर /* STRICT_MM_TYPECHECKS */

#पूर्ण_अगर	/* _ASM_PGTABLE_2LEVEL_TYPES_H */
