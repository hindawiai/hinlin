<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Page table types definitions.
 *
 * Copyright (C) 2014 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 */

#अगर_अघोषित __ASM_PGTABLE_TYPES_H
#घोषणा __ASM_PGTABLE_TYPES_H

#समावेश <यंत्र/types.h>

प्रकार u64 pteval_t;
प्रकार u64 pmdval_t;
प्रकार u64 pudval_t;
प्रकार u64 p4dval_t;
प्रकार u64 pgdval_t;

/*
 * These are used to make use of C type-checking..
 */
प्रकार काष्ठा अणु pteval_t pte; पूर्ण pte_t;
#घोषणा pte_val(x)	((x).pte)
#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )

#अगर CONFIG_PGTABLE_LEVELS > 2
प्रकार काष्ठा अणु pmdval_t pmd; पूर्ण pmd_t;
#घोषणा pmd_val(x)	((x).pmd)
#घोषणा __pmd(x)	((pmd_t) अणु (x) पूर्ण )
#पूर्ण_अगर

#अगर CONFIG_PGTABLE_LEVELS > 3
प्रकार काष्ठा अणु pudval_t pud; पूर्ण pud_t;
#घोषणा pud_val(x)	((x).pud)
#घोषणा __pud(x)	((pud_t) अणु (x) पूर्ण )
#पूर्ण_अगर

प्रकार काष्ठा अणु pgdval_t pgd; पूर्ण pgd_t;
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण )

प्रकार काष्ठा अणु pteval_t pgprot; पूर्ण pgprot_t;
#घोषणा pgprot_val(x)	((x).pgprot)
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

#अगर CONFIG_PGTABLE_LEVELS == 2
#समावेश <यंत्र-generic/pgtable-nopmd.h>
#या_अगर CONFIG_PGTABLE_LEVELS == 3
#समावेश <यंत्र-generic/pgtable-nopud.h>
#या_अगर CONFIG_PGTABLE_LEVELS == 4
#समावेश <यंत्र-generic/pgtable-nop4d.h>
#पूर्ण_अगर

#पूर्ण_अगर	/* __ASM_PGTABLE_TYPES_H */
