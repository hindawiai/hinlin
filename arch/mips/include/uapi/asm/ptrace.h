<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित _UAPI_ASM_PTRACE_H
#घोषणा _UAPI_ASM_PTRACE_H

#समावेश <linux/types.h>

/* 0 - 31 are पूर्णांकeger रेजिस्टरs, 32 - 63 are fp रेजिस्टरs.  */
#घोषणा FPR_BASE	32
#घोषणा PC		64
#घोषणा CAUSE		65
#घोषणा BADVADDR	66
#घोषणा MMHI		67
#घोषणा MMLO		68
#घोषणा FPC_CSR		69
#घोषणा FPC_EIR		70
#घोषणा DSP_BASE	71		/* 3 more hi / lo रेजिस्टर pairs */
#घोषणा DSP_CONTROL	77
#घोषणा ACX		78

/*
 * This काष्ठा defines the रेजिस्टरs as used by PTRACE_अणुGET,SETपूर्णREGS. The
 * क्रमmat is the same क्रम both 32- and 64-bit processes. Registers क्रम 32-bit
 * processes are sign extended.
 */
#अगर_घोषित __KERNEL__
काष्ठा user_pt_regs अणु
#अन्यथा
काष्ठा pt_regs अणु
#पूर्ण_अगर
	/* Saved मुख्य processor रेजिस्टरs. */
	__u64 regs[32];

	/* Saved special रेजिस्टरs. */
	__u64 lo;
	__u64 hi;
	__u64 cp0_epc;
	__u64 cp0_badvaddr;
	__u64 cp0_status;
	__u64 cp0_cause;
पूर्ण __attribute__ ((aligned (8)));

/* Arbitrarily choose the same ptrace numbers as used by the Sparc code. */
#घोषणा PTRACE_GETREGS		12
#घोषणा PTRACE_SETREGS		13
#घोषणा PTRACE_GETFPREGS		14
#घोषणा PTRACE_SETFPREGS		15
/* #घोषणा PTRACE_GETFPXREGS		18 */
/* #घोषणा PTRACE_SETFPXREGS		19 */

#घोषणा PTRACE_OLDSETOPTIONS	21

#घोषणा PTRACE_GET_THREAD_AREA	25
#घोषणा PTRACE_SET_THREAD_AREA	26

/* Calls to trace a 64bit program from a 32bit program.	 */
#घोषणा PTRACE_PEEKTEXT_3264	0xc0
#घोषणा PTRACE_PEEKDATA_3264	0xc1
#घोषणा PTRACE_POKETEXT_3264	0xc2
#घोषणा PTRACE_POKEDATA_3264	0xc3
#घोषणा PTRACE_GET_THREAD_AREA_3264	0xc4

/* Read and ग_लिखो watchpoपूर्णांक रेजिस्टरs.	 */
क्रमागत pt_watch_style अणु
	pt_watch_style_mips32,
	pt_watch_style_mips64
पूर्ण;
काष्ठा mips32_watch_regs अणु
	अचिन्हित पूर्णांक watchlo[8];
	/* Lower 16 bits of watchhi. */
	अचिन्हित लघु watchhi[8];
	/* Valid mask and I R W bits.
	 * bit 0 -- 1 अगर W bit is usable.
	 * bit 1 -- 1 अगर R bit is usable.
	 * bit 2 -- 1 अगर I bit is usable.
	 * bits 3 - 11 -- Valid watchhi mask bits.
	 */
	अचिन्हित लघु watch_masks[8];
	/* The number of valid watch रेजिस्टर pairs.  */
	अचिन्हित पूर्णांक num_valid;
पूर्ण __attribute__((aligned(8)));

काष्ठा mips64_watch_regs अणु
	अचिन्हित दीर्घ दीर्घ watchlo[8];
	अचिन्हित लघु watchhi[8];
	अचिन्हित लघु watch_masks[8];
	अचिन्हित पूर्णांक num_valid;
पूर्ण __attribute__((aligned(8)));

काष्ठा pt_watch_regs अणु
	क्रमागत pt_watch_style style;
	जोड़ अणु
		काष्ठा mips32_watch_regs mips32;
		काष्ठा mips64_watch_regs mips64;
	पूर्ण;
पूर्ण;

#घोषणा PTRACE_GET_WATCH_REGS	0xd0
#घोषणा PTRACE_SET_WATCH_REGS	0xd1


#पूर्ण_अगर /* _UAPI_ASM_PTRACE_H */
