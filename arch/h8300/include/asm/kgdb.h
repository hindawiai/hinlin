<शैली गुरु>
/*
 * Copyright (C) 2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_H8300_KGDB_H
#घोषणा _ASM_H8300_KGDB_H

#घोषणा CACHE_FLUSH_IS_SAFE	1
#घोषणा BUFMAX			2048

क्रमागत regnames अणु
	GDB_ER0, GDB_ER1, GDB_ER2, GDB_ER3,
	GDB_ER4, GDB_ER5, GDB_ER6, GDB_SP,
	GDB_CCR, GDB_PC,
	GDB_CYCLLE,
#अगर defined(CONFIG_CPU_H8S)
	GDB_EXR,
#पूर्ण_अगर
	GDB_TICK, GDB_INST,
#अगर defined(CONFIG_CPU_H8S)
	GDB_MACH, GDB_MACL,
#पूर्ण_अगर
	/* करो not change the last entry or anything below! */
	GDB_NUMREGBYTES,		/* number of रेजिस्टरs */
पूर्ण;

#घोषणा GDB_SIZखातापूर्ण_REG		माप(u32)
#अगर defined(CONFIG_CPU_H8300H)
#घोषणा DBG_MAX_REG_NUM		(13)
#या_अगर defined(CONFIG_CPU_H8S)
#घोषणा DBG_MAX_REG_NUM		(14)
#पूर्ण_अगर
#घोषणा NUMREGBYTES		(DBG_MAX_REG_NUM * GDB_SIZखातापूर्ण_REG)

#घोषणा BREAK_INSTR_SIZE	2
अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	__यंत्र__ __अस्थिर__("trapa #2");
पूर्ण

#पूर्ण_अगर /* _ASM_H8300_KGDB_H */
