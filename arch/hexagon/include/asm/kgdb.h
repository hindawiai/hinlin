<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/hexagon/include/यंत्र/kgdb.h - Hexagon KGDB Support
 *
 * Copyright (c) 2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __HEXAGON_KGDB_H__
#घोषणा __HEXAGON_KGDB_H__

#घोषणा BREAK_INSTR_SIZE 4
#घोषणा CACHE_FLUSH_IS_SAFE   1
#घोषणा BUFMAX       ((NUMREGBYTES * 2) + 512)

अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	यंत्र("trap0(#0xDB)");
पूर्ण

/* Registers:
 * 32 gpr + sa0/1 + lc0/1 + m0/1 + gp + ugp + pred + pc = 42 total.
 * vm regs = psp+elr+est+badva = 4
 * syscall+restart = 2 more
 * also add cs0/1 = 2
 * so 48 = 42 + 4 + 2 + 2
 */
#घोषणा DBG_USER_REGS 42
#घोषणा DBG_MAX_REG_NUM (DBG_USER_REGS + 8)
#घोषणा NUMREGBYTES  (DBG_MAX_REG_NUM*4)

#पूर्ण_अगर /* __HEXAGON_KGDB_H__ */
