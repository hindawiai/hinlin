<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_PGTABLE_2LEVEL_H
#घोषणा __ASM_SH_PGTABLE_2LEVEL_H

#समावेश <यंत्र-generic/pgtable-nopmd.h>

/*
 * traditional two-level paging काष्ठाure
 */
#घोषणा PAGETABLE_LEVELS	2

/* PTE bits */
#घोषणा PTE_MAGNITUDE		2	/* 32-bit PTEs */

#घोषणा PTE_SHIFT		PAGE_SHIFT
#घोषणा PTE_BITS		(PTE_SHIFT - PTE_MAGNITUDE)

/* PGD bits */
#घोषणा PGसूची_SHIFT		(PTE_SHIFT + PTE_BITS)

#घोषणा PTRS_PER_PGD		(PAGE_SIZE / (1 << PTE_MAGNITUDE))
#घोषणा USER_PTRS_PER_PGD	(TASK_SIZE/PGसूची_SIZE)

#पूर्ण_अगर /* __ASM_SH_PGTABLE_2LEVEL_H */
