<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/kbuild.h>

पूर्णांक मुख्य(व्योम)
अणु
	/* काष्ठा task_काष्ठा */
	OFFSET(TASK_THREAD, task_काष्ठा, thपढ़ो);
	BLANK();

	/* काष्ठा thपढ़ो_काष्ठा */
	OFFSET(THREAD_KSP, thपढ़ो_काष्ठा, ksp);
	OFFSET(THREAD_KPSR, thपढ़ो_काष्ठा, kpsr);
	BLANK();

	/* काष्ठा pt_regs */
	OFFSET(PT_ORIG_R2, pt_regs, orig_r2);
	OFFSET(PT_ORIG_R7, pt_regs, orig_r7);

	OFFSET(PT_R1, pt_regs, r1);
	OFFSET(PT_R2, pt_regs, r2);
	OFFSET(PT_R3, pt_regs, r3);
	OFFSET(PT_R4, pt_regs, r4);
	OFFSET(PT_R5, pt_regs, r5);
	OFFSET(PT_R6, pt_regs, r6);
	OFFSET(PT_R7, pt_regs, r7);
	OFFSET(PT_R8, pt_regs, r8);
	OFFSET(PT_R9, pt_regs, r9);
	OFFSET(PT_R10, pt_regs, r10);
	OFFSET(PT_R11, pt_regs, r11);
	OFFSET(PT_R12, pt_regs, r12);
	OFFSET(PT_R13, pt_regs, r13);
	OFFSET(PT_R14, pt_regs, r14);
	OFFSET(PT_R15, pt_regs, r15);
	OFFSET(PT_EA, pt_regs, ea);
	OFFSET(PT_RA, pt_regs, ra);
	OFFSET(PT_FP, pt_regs, fp);
	OFFSET(PT_SP, pt_regs, sp);
	OFFSET(PT_GP, pt_regs, gp);
	OFFSET(PT_ESTATUS, pt_regs, estatus);
	DEFINE(PT_REGS_SIZE, माप(काष्ठा pt_regs));
	BLANK();

	/* काष्ठा चयन_stack */
	OFFSET(SW_R16, चयन_stack, r16);
	OFFSET(SW_R17, चयन_stack, r17);
	OFFSET(SW_R18, चयन_stack, r18);
	OFFSET(SW_R19, चयन_stack, r19);
	OFFSET(SW_R20, चयन_stack, r20);
	OFFSET(SW_R21, चयन_stack, r21);
	OFFSET(SW_R22, चयन_stack, r22);
	OFFSET(SW_R23, चयन_stack, r23);
	OFFSET(SW_FP, चयन_stack, fp);
	OFFSET(SW_GP, चयन_stack, gp);
	OFFSET(SW_RA, चयन_stack, ra);
	DEFINE(SWITCH_STACK_SIZE, माप(काष्ठा चयन_stack));
	BLANK();

	/* काष्ठा thपढ़ो_info */
	OFFSET(TI_FLAGS, thपढ़ो_info, flags);
	OFFSET(TI_PREEMPT_COUNT, thपढ़ो_info, preempt_count);
	BLANK();

	वापस 0;
पूर्ण
