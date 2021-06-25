<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd
 *
 * based on m68k यंत्र/processor.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _UAPI_ASM_NIOS2_PTRACE_H
#घोषणा _UAPI_ASM_NIOS2_PTRACE_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

/*
 * Register numbers used by 'ptrace' प्रणाली call पूर्णांकerface.
 */

/* GP रेजिस्टरs */
#घोषणा PTR_R0		0
#घोषणा PTR_R1		1
#घोषणा PTR_R2		2
#घोषणा PTR_R3		3
#घोषणा PTR_R4		4
#घोषणा PTR_R5		5
#घोषणा PTR_R6		6
#घोषणा PTR_R7		7
#घोषणा PTR_R8		8
#घोषणा PTR_R9		9
#घोषणा PTR_R10		10
#घोषणा PTR_R11		11
#घोषणा PTR_R12		12
#घोषणा PTR_R13		13
#घोषणा PTR_R14		14
#घोषणा PTR_R15		15
#घोषणा PTR_R16		16
#घोषणा PTR_R17		17
#घोषणा PTR_R18		18
#घोषणा PTR_R19		19
#घोषणा PTR_R20		20
#घोषणा PTR_R21		21
#घोषणा PTR_R22		22
#घोषणा PTR_R23		23
#घोषणा PTR_R24		24
#घोषणा PTR_R25		25
#घोषणा PTR_GP		26
#घोषणा PTR_SP		27
#घोषणा PTR_FP		28
#घोषणा PTR_EA		29
#घोषणा PTR_BA		30
#घोषणा PTR_RA		31
/* Control रेजिस्टरs */
#घोषणा PTR_PC		32
#घोषणा PTR_STATUS	33
#घोषणा PTR_ESTATUS	34
#घोषणा PTR_BSTATUS	35
#घोषणा PTR_IENABLE	36
#घोषणा PTR_IPENDING	37
#घोषणा PTR_CPUID	38
#घोषणा PTR_CTL6	39
#घोषणा PTR_EXCEPTION	40
#घोषणा PTR_PTEADDR	41
#घोषणा PTR_TLBACC	42
#घोषणा PTR_TLBMISC	43
#घोषणा PTR_ECCINJ	44
#घोषणा PTR_BADADDR	45
#घोषणा PTR_CONFIG	46
#घोषणा PTR_MPUBASE	47
#घोषणा PTR_MPUACC	48

#घोषणा NUM_PTRACE_REG (PTR_MPUACC + 1)

/* User काष्ठाures क्रम general purpose रेजिस्टरs.  */
काष्ठा user_pt_regs अणु
	__u32		regs[49];
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _UAPI_ASM_NIOS2_PTRACE_H */
