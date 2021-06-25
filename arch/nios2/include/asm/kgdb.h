<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Altera Corporation
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 *
 * Based on the code posted by Kazuyasu on the Altera Forum at:
 * http://www.alteraक्रमum.com/क्रमum/showpost.php?p=77003&postcount=20
 */

#अगर_अघोषित _ASM_NIOS2_KGDB_H
#घोषणा _ASM_NIOS2_KGDB_H

#घोषणा CACHE_FLUSH_IS_SAFE	1
#घोषणा BUFMAX			2048

क्रमागत regnames अणु
	GDB_R0 = 0,
	GDB_AT,
	GDB_R2,
	GDB_R3,
	GDB_R4,
	GDB_R5,
	GDB_R6,
	GDB_R7,
	GDB_R8,
	GDB_R9,
	GDB_R10,
	GDB_R11,
	GDB_R12,
	GDB_R13,
	GDB_R14,
	GDB_R15,
	GDB_R16,
	GDB_R17,
	GDB_R18,
	GDB_R19,
	GDB_R20,
	GDB_R21,
	GDB_R22,
	GDB_R23,
	GDB_ET,
	GDB_BT,
	GDB_GP,
	GDB_SP,
	GDB_FP,
	GDB_EA,
	GDB_BA,
	GDB_RA,
	GDB_PC,
	GDB_STATUS,
	GDB_ESTATUS,
	GDB_BSTATUS,
	GDB_IENABLE,
	GDB_IPENDING,
	GDB_CPUID,
	GDB_CTL6,
	GDB_EXCEPTION,
	GDB_PTEADDR,
	GDB_TLBACC,
	GDB_TLBMISC,
	GDB_ECCINJ,
	GDB_BADADDR,
	GDB_CONFIG,
	GDB_MPUBASE,
	GDB_MPUACC,
	/* करो not change the last entry or anything below! */
	GDB_NUMREGBYTES		/* number of रेजिस्टरs */
पूर्ण;

#घोषणा GDB_SIZखातापूर्ण_REG		माप(u32)
#घोषणा DBG_MAX_REG_NUM	(49)
#घोषणा NUMREGBYTES		(DBG_MAX_REG_NUM * माप(GDB_SIZखातापूर्ण_REG))

#घोषणा BREAK_INSTR_SIZE	4
अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	__यंत्र__ __अस्थिर__("trap 30\n");
पूर्ण

#पूर्ण_अगर /* _ASM_NIOS2_KGDB_H */
