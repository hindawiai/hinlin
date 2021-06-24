<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_32_TYPES_H
#घोषणा _ASM_X86_PGTABLE_32_TYPES_H

/*
 * The Linux x86 paging architecture is 'compile-time dual-mode', it
 * implements both the traditional 2-level x86 page tables and the
 * newer 3-level PAE-mode page tables.
 */
#अगर_घोषित CONFIG_X86_PAE
# include <यंत्र/pgtable-3level_types.h>
# define PMD_SIZE	(1UL << PMD_SHIFT)
# define PMD_MASK	(~(PMD_SIZE - 1))
#अन्यथा
# include <यंत्र/pgtable-2level_types.h>
#पूर्ण_अगर

#घोषणा pgtable_l5_enabled() 0

#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE - 1))

#पूर्ण_अगर /* _ASM_X86_PGTABLE_32_TYPES_H */
