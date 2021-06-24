<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * kgdb support क्रम ARC
 *
 * Copyright (C) 2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ARC_KGDB_H__
#घोषणा __ARC_KGDB_H__

#अगर_घोषित CONFIG_KGDB

#समावेश <यंत्र/ptrace.h>

/* to ensure compatibility with Linux 2.6.35, we करोn't implement the get/set
 * रेजिस्टर API yet */
#अघोषित DBG_MAX_REG_NUM

#घोषणा GDB_MAX_REGS		87

#घोषणा BREAK_INSTR_SIZE	2
#घोषणा CACHE_FLUSH_IS_SAFE	1
#घोषणा NUMREGBYTES		(GDB_MAX_REGS * 4)
#घोषणा BUFMAX			2048

अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("trap_s	0x4\n");
पूर्ण

बाह्य व्योम kgdb_trap(काष्ठा pt_regs *regs);

/* This is the numbering of रेजिस्टरs according to the GDB. See GDB's
 * arc-tdep.h क्रम details.
 *
 * Registers are ordered क्रम GDB 7.5. It is incompatible with GDB 6.8. */
क्रमागत arc_linux_regnums अणु
	_R0		= 0,
	_R1, _R2, _R3, _R4, _R5, _R6, _R7, _R8, _R9, _R10, _R11, _R12, _R13,
	_R14, _R15, _R16, _R17, _R18, _R19, _R20, _R21, _R22, _R23, _R24,
	_R25, _R26,
	_FP		= 27,
	__SP		= 28,
	_R30		= 30,
	_BLINK		= 31,
	_LP_COUNT	= 60,
	_STOP_PC	= 64,
	_RET		= 64,
	_LP_START	= 65,
	_LP_END		= 66,
	_STATUS32	= 67,
	_ECR		= 76,
	_BTA		= 82,
पूर्ण;

#अन्यथा
#घोषणा kgdb_trap(regs)
#पूर्ण_अगर

#पूर्ण_अगर	/* __ARC_KGDB_H__ */
