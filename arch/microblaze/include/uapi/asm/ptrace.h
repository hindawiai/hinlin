<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _UAPI_ASM_MICROBLAZE_PTRACE_H
#घोषणा _UAPI_ASM_MICROBLAZE_PTRACE_H

#अगर_अघोषित __ASSEMBLY__

प्रकार अचिन्हित दीर्घ microblaze_reg_t;

काष्ठा pt_regs अणु
	microblaze_reg_t r0;
	microblaze_reg_t r1;
	microblaze_reg_t r2;
	microblaze_reg_t r3;
	microblaze_reg_t r4;
	microblaze_reg_t r5;
	microblaze_reg_t r6;
	microblaze_reg_t r7;
	microblaze_reg_t r8;
	microblaze_reg_t r9;
	microblaze_reg_t r10;
	microblaze_reg_t r11;
	microblaze_reg_t r12;
	microblaze_reg_t r13;
	microblaze_reg_t r14;
	microblaze_reg_t r15;
	microblaze_reg_t r16;
	microblaze_reg_t r17;
	microblaze_reg_t r18;
	microblaze_reg_t r19;
	microblaze_reg_t r20;
	microblaze_reg_t r21;
	microblaze_reg_t r22;
	microblaze_reg_t r23;
	microblaze_reg_t r24;
	microblaze_reg_t r25;
	microblaze_reg_t r26;
	microblaze_reg_t r27;
	microblaze_reg_t r28;
	microblaze_reg_t r29;
	microblaze_reg_t r30;
	microblaze_reg_t r31;
	microblaze_reg_t pc;
	microblaze_reg_t msr;
	microblaze_reg_t ear;
	microblaze_reg_t esr;
	microblaze_reg_t fsr;
	पूर्णांक pt_mode;
पूर्ण;

#अगर_अघोषित __KERNEL__

/* pt_regs offsets used by gdbserver etc in ptrace syscalls */
#घोषणा PT_GPR(n)	((n) * माप(microblaze_reg_t))
#घोषणा PT_PC		(32 * माप(microblaze_reg_t))
#घोषणा PT_MSR		(33 * माप(microblaze_reg_t))
#घोषणा PT_EAR		(34 * माप(microblaze_reg_t))
#घोषणा PT_ESR		(35 * माप(microblaze_reg_t))
#घोषणा PT_FSR		(36 * माप(microblaze_reg_t))
#घोषणा PT_KERNEL_MODE	(37 * माप(microblaze_reg_t))

#पूर्ण_अगर /* __KERNEL */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI_ASM_MICROBLAZE_PTRACE_H */
