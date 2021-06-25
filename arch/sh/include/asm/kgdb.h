<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_KGDB_H
#घोषणा __ASM_SH_KGDB_H

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/ptrace.h>

क्रमागत regnames अणु
	GDB_R0, GDB_R1, GDB_R2, GDB_R3, GDB_R4, GDB_R5, GDB_R6, GDB_R7,
	GDB_R8, GDB_R9, GDB_R10, GDB_R11, GDB_R12, GDB_R13, GDB_R14, GDB_R15,

	GDB_PC, GDB_PR, GDB_SR, GDB_GBR, GDB_MACH, GDB_MACL, GDB_VBR,
पूर्ण;

#घोषणा _GP_REGS	16
#घोषणा _EXTRA_REGS	7
#घोषणा GDB_SIZखातापूर्ण_REG	माप(u32)

#घोषणा DBG_MAX_REG_NUM	(_GP_REGS + _EXTRA_REGS)
#घोषणा NUMREGBYTES	(DBG_MAX_REG_NUM * माप(GDB_SIZखातापूर्ण_REG))

अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("trapa #0x3c\n");
पूर्ण

#घोषणा BREAK_INSTR_SIZE	2
#घोषणा BUFMAX			2048

#अगर_घोषित CONFIG_SMP
# define CACHE_FLUSH_IS_SAFE	0
#अन्यथा
# define CACHE_FLUSH_IS_SAFE	1
#पूर्ण_अगर

#घोषणा GDB_ADJUSTS_BREAK_OFFSET

#पूर्ण_अगर /* __ASM_SH_KGDB_H */
