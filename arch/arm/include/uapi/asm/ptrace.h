<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  arch/arm/include/यंत्र/ptrace.h
 *
 *  Copyright (C) 1996-2003 Russell King
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#अगर_अघोषित _UAPI__ASM_ARM_PTRACE_H
#घोषणा _UAPI__ASM_ARM_PTRACE_H

#समावेश <यंत्र/hwcap.h>

#घोषणा PTRACE_GETREGS		12
#घोषणा PTRACE_SETREGS		13
#घोषणा PTRACE_GETFPREGS	14
#घोषणा PTRACE_SETFPREGS	15
/* PTRACE_ATTACH is 16 */
/* PTRACE_DETACH is 17 */
#घोषणा PTRACE_GETWMMXREGS	18
#घोषणा PTRACE_SETWMMXREGS	19
/* 20 is unused */
#घोषणा PTRACE_OLDSETOPTIONS	21
#घोषणा PTRACE_GET_THREAD_AREA	22
#घोषणा PTRACE_SET_SYSCALL	23
/* PTRACE_SYSCALL is 24 */
#घोषणा PTRACE_GETCRUNCHREGS	25
#घोषणा PTRACE_SETCRUNCHREGS	26
#घोषणा PTRACE_GETVFPREGS	27
#घोषणा PTRACE_SETVFPREGS	28
#घोषणा PTRACE_GETHBPREGS	29
#घोषणा PTRACE_SETHBPREGS	30
#घोषणा PTRACE_GETFDPIC		31

#घोषणा PTRACE_GETFDPIC_EXEC	0
#घोषणा PTRACE_GETFDPIC_INTERP	1

/*
 * PSR bits
 * Note on V7M there is no mode contained in the PSR
 */
#घोषणा USR26_MODE	0x00000000
#घोषणा FIQ26_MODE	0x00000001
#घोषणा IRQ26_MODE	0x00000002
#घोषणा SVC26_MODE	0x00000003
#अगर defined(__KERNEL__) && defined(CONFIG_CPU_V7M)
/*
 * Use 0 here to get code right that creates a userspace
 * or kernel space thपढ़ो.
 */
#घोषणा USR_MODE	0x00000000
#घोषणा SVC_MODE	0x00000000
#अन्यथा
#घोषणा USR_MODE	0x00000010
#घोषणा SVC_MODE	0x00000013
#पूर्ण_अगर
#घोषणा FIQ_MODE	0x00000011
#घोषणा IRQ_MODE	0x00000012
#घोषणा MON_MODE	0x00000016
#घोषणा ABT_MODE	0x00000017
#घोषणा HYP_MODE	0x0000001a
#घोषणा UND_MODE	0x0000001b
#घोषणा SYSTEM_MODE	0x0000001f
#घोषणा MODE32_BIT	0x00000010
#घोषणा MODE_MASK	0x0000001f

#घोषणा V4_PSR_T_BIT	0x00000020	/* >= V4T, but not V7M */
#घोषणा V7M_PSR_T_BIT	0x01000000
#अगर defined(__KERNEL__) && defined(CONFIG_CPU_V7M)
#घोषणा PSR_T_BIT	V7M_PSR_T_BIT
#अन्यथा
/* क्रम compatibility */
#घोषणा PSR_T_BIT	V4_PSR_T_BIT
#पूर्ण_अगर

#घोषणा PSR_F_BIT	0x00000040	/* >= V4, but not V7M */
#घोषणा PSR_I_BIT	0x00000080	/* >= V4, but not V7M */
#घोषणा PSR_A_BIT	0x00000100	/* >= V6, but not V7M */
#घोषणा PSR_E_BIT	0x00000200	/* >= V6, but not V7M */
#घोषणा PSR_J_BIT	0x01000000	/* >= V5J, but not V7M */
#घोषणा PSR_Q_BIT	0x08000000	/* >= V5E, including V7M */
#घोषणा PSR_V_BIT	0x10000000
#घोषणा PSR_C_BIT	0x20000000
#घोषणा PSR_Z_BIT	0x40000000
#घोषणा PSR_N_BIT	0x80000000

/*
 * Groups of PSR bits
 */
#घोषणा PSR_f		0xff000000	/* Flags		*/
#घोषणा PSR_s		0x00ff0000	/* Status		*/
#घोषणा PSR_x		0x0000ff00	/* Extension		*/
#घोषणा PSR_c		0x000000ff	/* Control		*/

/*
 * ARMv7 groups of PSR bits
 */
#घोषणा APSR_MASK	0xf80f0000	/* N, Z, C, V, Q and GE flags */
#घोषणा PSR_ISET_MASK	0x01000010	/* ISA state (J, T) mask */
#घोषणा PSR_IT_MASK	0x0600fc00	/* If-Then execution state mask */
#घोषणा PSR_ENDIAN_MASK	0x00000200	/* Endianness state mask */

/*
 * Default endianness state
 */
#अगर_घोषित CONFIG_CPU_ENDIAN_BE8
#घोषणा PSR_ENDSTATE	PSR_E_BIT
#अन्यथा
#घोषणा PSR_ENDSTATE	0
#पूर्ण_अगर

/* 
 * These are 'magic' values क्रम PTRACE_PEEKUSR that वापस info about where a
 * process is located in memory.
 */
#घोषणा PT_TEXT_ADDR		0x10000
#घोषणा PT_DATA_ADDR		0x10004
#घोषणा PT_TEXT_END_ADDR	0x10008

#अगर_अघोषित __ASSEMBLY__

/*
 * This काष्ठा defines the way the रेजिस्टरs are stored on the
 * stack during a प्रणाली call.  Note that माप(काष्ठा pt_regs)
 * has to be a multiple of 8.
 */
#अगर_अघोषित __KERNEL__
काष्ठा pt_regs अणु
	दीर्घ uregs[18];
पूर्ण;
#पूर्ण_अगर /* __KERNEL__ */

#घोषणा ARM_cpsr	uregs[16]
#घोषणा ARM_pc		uregs[15]
#घोषणा ARM_lr		uregs[14]
#घोषणा ARM_sp		uregs[13]
#घोषणा ARM_ip		uregs[12]
#घोषणा ARM_fp		uregs[11]
#घोषणा ARM_r10		uregs[10]
#घोषणा ARM_r9		uregs[9]
#घोषणा ARM_r8		uregs[8]
#घोषणा ARM_r7		uregs[7]
#घोषणा ARM_r6		uregs[6]
#घोषणा ARM_r5		uregs[5]
#घोषणा ARM_r4		uregs[4]
#घोषणा ARM_r3		uregs[3]
#घोषणा ARM_r2		uregs[2]
#घोषणा ARM_r1		uregs[1]
#घोषणा ARM_r0		uregs[0]
#घोषणा ARM_ORIG_r0	uregs[17]

/*
 * The size of the user-visible VFP state as seen by PTRACE_GET/SETVFPREGS
 * and core dumps.
 */
#घोषणा ARM_VFPREGS_SIZE ( 32 * 8 /*fpregs*/ + 4 /*fpscr*/ )


#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI__ASM_ARM_PTRACE_H */
