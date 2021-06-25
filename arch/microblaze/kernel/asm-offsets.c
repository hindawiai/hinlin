<शैली गुरु>
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/kbuild.h>
#समावेश <यंत्र/cpuinfo.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	/* काष्ठा pt_regs */
	DEFINE(PT_SIZE, माप(काष्ठा pt_regs));
	DEFINE(PT_MSR, दुरत्व(काष्ठा pt_regs, msr));
	DEFINE(PT_EAR, दुरत्व(काष्ठा pt_regs, ear));
	DEFINE(PT_ESR, दुरत्व(काष्ठा pt_regs, esr));
	DEFINE(PT_FSR, दुरत्व(काष्ठा pt_regs, fsr));
	DEFINE(PT_PC, दुरत्व(काष्ठा pt_regs, pc));
	DEFINE(PT_R0, दुरत्व(काष्ठा pt_regs, r0));
	DEFINE(PT_R1, दुरत्व(काष्ठा pt_regs, r1));
	DEFINE(PT_R2, दुरत्व(काष्ठा pt_regs, r2));
	DEFINE(PT_R3, दुरत्व(काष्ठा pt_regs, r3));
	DEFINE(PT_R4, दुरत्व(काष्ठा pt_regs, r4));
	DEFINE(PT_R5, दुरत्व(काष्ठा pt_regs, r5));
	DEFINE(PT_R6, दुरत्व(काष्ठा pt_regs, r6));
	DEFINE(PT_R7, दुरत्व(काष्ठा pt_regs, r7));
	DEFINE(PT_R8, दुरत्व(काष्ठा pt_regs, r8));
	DEFINE(PT_R9, दुरत्व(काष्ठा pt_regs, r9));
	DEFINE(PT_R10, दुरत्व(काष्ठा pt_regs, r10));
	DEFINE(PT_R11, दुरत्व(काष्ठा pt_regs, r11));
	DEFINE(PT_R12, दुरत्व(काष्ठा pt_regs, r12));
	DEFINE(PT_R13, दुरत्व(काष्ठा pt_regs, r13));
	DEFINE(PT_R14, दुरत्व(काष्ठा pt_regs, r14));
	DEFINE(PT_R15, दुरत्व(काष्ठा pt_regs, r15));
	DEFINE(PT_R16, दुरत्व(काष्ठा pt_regs, r16));
	DEFINE(PT_R17, दुरत्व(काष्ठा pt_regs, r17));
	DEFINE(PT_R18, दुरत्व(काष्ठा pt_regs, r18));
	DEFINE(PT_R19, दुरत्व(काष्ठा pt_regs, r19));
	DEFINE(PT_R20, दुरत्व(काष्ठा pt_regs, r20));
	DEFINE(PT_R21, दुरत्व(काष्ठा pt_regs, r21));
	DEFINE(PT_R22, दुरत्व(काष्ठा pt_regs, r22));
	DEFINE(PT_R23, दुरत्व(काष्ठा pt_regs, r23));
	DEFINE(PT_R24, दुरत्व(काष्ठा pt_regs, r24));
	DEFINE(PT_R25, दुरत्व(काष्ठा pt_regs, r25));
	DEFINE(PT_R26, दुरत्व(काष्ठा pt_regs, r26));
	DEFINE(PT_R27, दुरत्व(काष्ठा pt_regs, r27));
	DEFINE(PT_R28, दुरत्व(काष्ठा pt_regs, r28));
	DEFINE(PT_R29, दुरत्व(काष्ठा pt_regs, r29));
	DEFINE(PT_R30, दुरत्व(काष्ठा pt_regs, r30));
	DEFINE(PT_R31, दुरत्व(काष्ठा pt_regs, r31));
	DEFINE(PT_MODE, दुरत्व(काष्ठा pt_regs, pt_mode));
	BLANK();

	/* Magic offsets क्रम PTRACE PEEK/POKE etc */
	DEFINE(PT_TEXT_ADDR, माप(काष्ठा pt_regs) + 1);
	DEFINE(PT_TEXT_LEN, माप(काष्ठा pt_regs) + 2);
	DEFINE(PT_DATA_ADDR, माप(काष्ठा pt_regs) + 3);
	BLANK();

	/* काष्ठा task_काष्ठा */
	DEFINE(TS_THREAD_INFO, दुरत्व(काष्ठा task_काष्ठा, stack));
	DEFINE(TASK_STATE, दुरत्व(काष्ठा task_काष्ठा, state));
	DEFINE(TASK_FLAGS, दुरत्व(काष्ठा task_काष्ठा, flags));
	DEFINE(TASK_PTRACE, दुरत्व(काष्ठा task_काष्ठा, ptrace));
	DEFINE(TASK_BLOCKED, दुरत्व(काष्ठा task_काष्ठा, blocked));
	DEFINE(TASK_MM, दुरत्व(काष्ठा task_काष्ठा, mm));
	DEFINE(TASK_ACTIVE_MM, दुरत्व(काष्ठा task_काष्ठा, active_mm));
	DEFINE(TASK_PID, दुरत्व(काष्ठा task_काष्ठा, pid));
	DEFINE(TASK_THREAD, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो));
	DEFINE(THREAD_KSP, दुरत्व(काष्ठा thपढ़ो_काष्ठा, ksp));
	BLANK();

	DEFINE(PGसूची, दुरत्व(काष्ठा thपढ़ो_काष्ठा, pgdir));
	BLANK();

	/* काष्ठा thपढ़ो_info */
	DEFINE(TI_TASK, दुरत्व(काष्ठा thपढ़ो_info, task));
	DEFINE(TI_FLAGS, दुरत्व(काष्ठा thपढ़ो_info, flags));
	DEFINE(TI_ADDR_LIMIT, दुरत्व(काष्ठा thपढ़ो_info, addr_limit));
	DEFINE(TI_CPU_CONTEXT, दुरत्व(काष्ठा thपढ़ो_info, cpu_context));
	DEFINE(TI_PREEMPT_COUNT, दुरत्व(काष्ठा thपढ़ो_info, preempt_count));
	BLANK();

	/* काष्ठा cpu_context */
	DEFINE(CC_R1, दुरत्व(काष्ठा cpu_context, r1)); /* r1 */
	DEFINE(CC_R2, दुरत्व(काष्ठा cpu_context, r2));
	/* dedicated रेजिस्टरs */
	DEFINE(CC_R13, दुरत्व(काष्ठा cpu_context, r13));
	DEFINE(CC_R14, दुरत्व(काष्ठा cpu_context, r14));
	DEFINE(CC_R15, दुरत्व(काष्ठा cpu_context, r15));
	DEFINE(CC_R16, दुरत्व(काष्ठा cpu_context, r16));
	DEFINE(CC_R17, दुरत्व(काष्ठा cpu_context, r17));
	DEFINE(CC_R18, दुरत्व(काष्ठा cpu_context, r18));
	/* non-अस्थिर रेजिस्टरs */
	DEFINE(CC_R19, दुरत्व(काष्ठा cpu_context, r19));
	DEFINE(CC_R20, दुरत्व(काष्ठा cpu_context, r20));
	DEFINE(CC_R21, दुरत्व(काष्ठा cpu_context, r21));
	DEFINE(CC_R22, दुरत्व(काष्ठा cpu_context, r22));
	DEFINE(CC_R23, दुरत्व(काष्ठा cpu_context, r23));
	DEFINE(CC_R24, दुरत्व(काष्ठा cpu_context, r24));
	DEFINE(CC_R25, दुरत्व(काष्ठा cpu_context, r25));
	DEFINE(CC_R26, दुरत्व(काष्ठा cpu_context, r26));
	DEFINE(CC_R27, दुरत्व(काष्ठा cpu_context, r27));
	DEFINE(CC_R28, दुरत्व(काष्ठा cpu_context, r28));
	DEFINE(CC_R29, दुरत्व(काष्ठा cpu_context, r29));
	DEFINE(CC_R30, दुरत्व(काष्ठा cpu_context, r30));
	/* special purpose रेजिस्टरs */
	DEFINE(CC_MSR, दुरत्व(काष्ठा cpu_context, msr));
	DEFINE(CC_EAR, दुरत्व(काष्ठा cpu_context, ear));
	DEFINE(CC_ESR, दुरत्व(काष्ठा cpu_context, esr));
	DEFINE(CC_FSR, दुरत्व(काष्ठा cpu_context, fsr));
	BLANK();

	वापस 0;
पूर्ण
