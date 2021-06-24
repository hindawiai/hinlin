<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/kbuild.h>
#समावेश <linux/ptrace.h>
#समावेश <यंत्र/hardirq.h>
#समावेश <यंत्र/page.h>


पूर्णांक मुख्य(व्योम)
अणु
	DEFINE(TASK_THREAD, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो));
	DEFINE(TASK_THREAD_INFO, दुरत्व(काष्ठा task_काष्ठा, stack));

	BLANK();

	DEFINE(THREAD_KSP, दुरत्व(काष्ठा thपढ़ो_काष्ठा, ksp));
	DEFINE(THREAD_CALLEE_REG, दुरत्व(काष्ठा thपढ़ो_काष्ठा, callee_reg));
	DEFINE(THREAD_FAULT_ADDR,
	       दुरत्व(काष्ठा thपढ़ो_काष्ठा, fault_address));

	BLANK();

	DEFINE(THREAD_INFO_FLAGS, दुरत्व(काष्ठा thपढ़ो_info, flags));
	DEFINE(THREAD_INFO_PREEMPT_COUNT,
	       दुरत्व(काष्ठा thपढ़ो_info, preempt_count));

	BLANK();

	DEFINE(TASK_ACT_MM, दुरत्व(काष्ठा task_काष्ठा, active_mm));
	DEFINE(TASK_TGID, दुरत्व(काष्ठा task_काष्ठा, tgid));
	DEFINE(TASK_PID, दुरत्व(काष्ठा task_काष्ठा, pid));
	DEFINE(TASK_COMM, दुरत्व(काष्ठा task_काष्ठा, comm));

	DEFINE(MM_CTXT, दुरत्व(काष्ठा mm_काष्ठा, context));
	DEFINE(MM_PGD, दुरत्व(काष्ठा mm_काष्ठा, pgd));

	DEFINE(MM_CTXT_ASID, दुरत्व(mm_context_t, asid));

	BLANK();

	DEFINE(PT_status32, दुरत्व(काष्ठा pt_regs, status32));
	DEFINE(PT_event, दुरत्व(काष्ठा pt_regs, event));
	DEFINE(PT_sp, दुरत्व(काष्ठा pt_regs, sp));
	DEFINE(PT_r0, दुरत्व(काष्ठा pt_regs, r0));
	DEFINE(PT_r1, दुरत्व(काष्ठा pt_regs, r1));
	DEFINE(PT_r2, दुरत्व(काष्ठा pt_regs, r2));
	DEFINE(PT_r3, दुरत्व(काष्ठा pt_regs, r3));
	DEFINE(PT_r4, दुरत्व(काष्ठा pt_regs, r4));
	DEFINE(PT_r5, दुरत्व(काष्ठा pt_regs, r5));
	DEFINE(PT_r6, दुरत्व(काष्ठा pt_regs, r6));
	DEFINE(PT_r7, दुरत्व(काष्ठा pt_regs, r7));
	DEFINE(PT_r8, दुरत्व(काष्ठा pt_regs, r8));
	DEFINE(PT_r10, दुरत्व(काष्ठा pt_regs, r10));
	DEFINE(PT_r26, दुरत्व(काष्ठा pt_regs, r26));
	DEFINE(PT_ret, दुरत्व(काष्ठा pt_regs, ret));
	DEFINE(PT_blink, दुरत्व(काष्ठा pt_regs, blink));
	DEFINE(PT_lpe, दुरत्व(काष्ठा pt_regs, lp_end));
	DEFINE(PT_lpc, दुरत्व(काष्ठा pt_regs, lp_count));
	DEFINE(PT_user_r25, दुरत्व(काष्ठा pt_regs, user_r25));

	DEFINE(SZ_CALLEE_REGS, माप(काष्ठा callee_regs));
	DEFINE(SZ_PT_REGS, माप(काष्ठा pt_regs));

#अगर_घोषित CONFIG_ISA_ARCV2
	OFFSET(PT_r12, pt_regs, r12);
	OFFSET(PT_r30, pt_regs, r30);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARC_HAS_ACCL_REGS
	OFFSET(PT_r58, pt_regs, r58);
	OFFSET(PT_r59, pt_regs, r59);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARC_DSP_SAVE_RESTORE_REGS
	OFFSET(PT_DSP_CTRL, pt_regs, DSP_CTRL);
#पूर्ण_अगर

	वापस 0;
पूर्ण
