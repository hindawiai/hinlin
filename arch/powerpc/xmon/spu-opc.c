<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SPU opcode list

   Copyright 2006 Free Software Foundation, Inc.

   This file is part of GDB, GAS, and the GNU binutils.

 */

#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश "spu.h"

/* This file holds the Spu opcode table */


/*
   Example contents of spu-insn.h
      id_tag	mode	mode	type	opcode	mnemonic	यंत्रtype	    dependency		FPU	L/S?	branch?	inकाष्ठाion   
                QUAD	WORD                                               (0,RC,RB,RA,RT)    latency  			              		
   APUOP(M_LQD,	1,	0,	RI9,	0x1f8,	"lqd",		ASM_RI9IDX,	00012,		FXU,	1,	0)	Load Quadword d-क्रमm 
 */

स्थिर काष्ठा spu_opcode spu_opcodes[] = अणु
#घोषणा APUOP(TAG,MACFORMAT,OPCODE,MNEMONIC,ASMFORMAT,DEP,PIPE) \
	अणु MACFORMAT, OPCODE, MNEMONIC, ASMFORMAT पूर्ण,
#घोषणा APUOPFB(TAG,MACFORMAT,OPCODE,FB,MNEMONIC,ASMFORMAT,DEP,PIPE) \
	अणु MACFORMAT, OPCODE, MNEMONIC, ASMFORMAT पूर्ण,
#समावेश "spu-insns.h"
#अघोषित APUOP
#अघोषित APUOPFB
पूर्ण;

स्थिर पूर्णांक spu_num_opcodes = ARRAY_SIZE(spu_opcodes);
