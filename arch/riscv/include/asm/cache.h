<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 Chen Liqin <liqin.chen@sunplusct.com>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_CACHE_H
#घोषणा _ASM_RISCV_CACHE_H

#घोषणा L1_CACHE_SHIFT		6

#घोषणा L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

/*
 * RISC-V requires the stack poपूर्णांकer to be 16-byte aligned, so ensure that
 * the flat loader aligns it accordingly.
 */
#अगर_अघोषित CONFIG_MMU
#घोषणा ARCH_SLAB_MINALIGN	16
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_CACHE_H */
