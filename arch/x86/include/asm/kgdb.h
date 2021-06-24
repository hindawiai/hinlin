<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_KGDB_H
#घोषणा _ASM_X86_KGDB_H

/*
 * Copyright (C) 2001-2004 Amit S. Kale
 * Copyright (C) 2008 Wind River Systems, Inc.
 */

#समावेश <यंत्र/ptrace.h>

/*
 * BUFMAX defines the maximum number of अक्षरacters in inbound/outbound
 * buffers at least NUMREGBYTES*2 are needed क्रम रेजिस्टर packets
 * Longer buffer is needed to list all thपढ़ोs
 */
#घोषणा BUFMAX			1024

/*
 *  Note that this रेजिस्टर image is in a dअगरferent order than
 *  the रेजिस्टर image that Linux produces at पूर्णांकerrupt समय.
 *
 *  Linux's रेजिस्टर image is defined by काष्ठा pt_regs in ptrace.h.
 *  Just why GDB uses a dअगरferent order is a historical mystery.
 */
#अगर_घोषित CONFIG_X86_32
क्रमागत regnames अणु
	GDB_AX,			/* 0 */
	GDB_CX,			/* 1 */
	GDB_DX,			/* 2 */
	GDB_BX,			/* 3 */
	GDB_SP,			/* 4 */
	GDB_BP,			/* 5 */
	GDB_SI,			/* 6 */
	GDB_DI,			/* 7 */
	GDB_PC,			/* 8 also known as eip */
	GDB_PS,			/* 9 also known as eflags */
	GDB_CS,			/* 10 */
	GDB_SS,			/* 11 */
	GDB_DS,			/* 12 */
	GDB_ES,			/* 13 */
	GDB_FS,			/* 14 */
	GDB_GS,			/* 15 */
पूर्ण;
#घोषणा GDB_ORIG_AX		41
#घोषणा DBG_MAX_REG_NUM		16
#घोषणा NUMREGBYTES		((GDB_GS+1)*4)
#अन्यथा /* ! CONFIG_X86_32 */
क्रमागत regnames अणु
	GDB_AX,			/* 0 */
	GDB_BX,			/* 1 */
	GDB_CX,			/* 2 */
	GDB_DX,			/* 3 */
	GDB_SI,			/* 4 */
	GDB_DI,			/* 5 */
	GDB_BP,			/* 6 */
	GDB_SP,			/* 7 */
	GDB_R8,			/* 8 */
	GDB_R9,			/* 9 */
	GDB_R10,		/* 10 */
	GDB_R11,		/* 11 */
	GDB_R12,		/* 12 */
	GDB_R13,		/* 13 */
	GDB_R14,		/* 14 */
	GDB_R15,		/* 15 */
	GDB_PC,			/* 16 */
	GDB_PS,			/* 17 */
	GDB_CS,			/* 18 */
	GDB_SS,			/* 19 */
	GDB_DS,			/* 20 */
	GDB_ES,			/* 21 */
	GDB_FS,			/* 22 */
	GDB_GS,			/* 23 */
पूर्ण;
#घोषणा GDB_ORIG_AX		57
#घोषणा DBG_MAX_REG_NUM		24
/* 17 64 bit regs and 5 32 bit regs */
#घोषणा NUMREGBYTES		((17 * 8) + (5 * 4))
#पूर्ण_अगर /* ! CONFIG_X86_32 */

अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	यंत्र("   int $3");
पूर्ण
#घोषणा BREAK_INSTR_SIZE	1
#घोषणा CACHE_FLUSH_IS_SAFE	1
#घोषणा GDB_ADJUSTS_BREAK_OFFSET

बाह्य पूर्णांक kgdb_ll_trap(पूर्णांक cmd, स्थिर अक्षर *str,
			काष्ठा pt_regs *regs, दीर्घ err, पूर्णांक trap, पूर्णांक sig);

#पूर्ण_अगर /* _ASM_X86_KGDB_H */
