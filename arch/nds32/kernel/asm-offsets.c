<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kbuild.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/ptrace.h>

पूर्णांक मुख्य(व्योम)
अणु
	DEFINE(TSK_TI_FLAGS, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो_info.flags));
	DEFINE(TSK_TI_PREEMPT,
	       दुरत्व(काष्ठा task_काष्ठा, thपढ़ो_info.preempt_count));
	DEFINE(THREAD_CPU_CONTEXT,
	       दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.cpu_context));
	DEFINE(OSP_OFFSET, दुरत्व(काष्ठा pt_regs, osp));
	DEFINE(SP_OFFSET, दुरत्व(काष्ठा pt_regs, sp));
	DEFINE(FUCOP_CTL_OFFSET, दुरत्व(काष्ठा pt_regs, fucop_ctl));
	DEFINE(IPSW_OFFSET, दुरत्व(काष्ठा pt_regs, ipsw));
	DEFINE(SYSCALLNO_OFFSET, दुरत्व(काष्ठा pt_regs, syscallno));
	DEFINE(IPC_OFFSET, दुरत्व(काष्ठा pt_regs, ipc));
	DEFINE(R0_OFFSET, दुरत्व(काष्ठा pt_regs, uregs[0]));
	DEFINE(R15_OFFSET, दुरत्व(काष्ठा pt_regs, uregs[15]));
	DEFINE(CLOCK_REALTIME_RES, MONOTONIC_RES_NSEC);
	DEFINE(CLOCK_COARSE_RES, LOW_RES_NSEC);
	वापस 0;
पूर्ण
