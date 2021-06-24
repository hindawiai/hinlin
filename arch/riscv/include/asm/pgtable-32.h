<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_PGTABLE_32_H
#घोषणा _ASM_RISCV_PGTABLE_32_H

#समावेश <यंत्र-generic/pgtable-nopmd.h>
#समावेश <linux/स्थिर.h>

/* Size of region mapped by a page global directory */
#घोषणा PGसूची_SHIFT     22
#घोषणा PGसूची_SIZE      (_AC(1, UL) << PGसूची_SHIFT)
#घोषणा PGसूची_MASK      (~(PGसूची_SIZE - 1))

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS 34

#पूर्ण_अगर /* _ASM_RISCV_PGTABLE_32_H */
