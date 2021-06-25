<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/kbuild.h>
#समावेश <abi/regdef.h>

पूर्णांक मुख्य(व्योम)
अणु
	/* offsets पूर्णांकo the task काष्ठा */
	DEFINE(TASK_STATE,        दुरत्व(काष्ठा task_काष्ठा, state));
	DEFINE(TASK_THREAD_INFO,  दुरत्व(काष्ठा task_काष्ठा, stack));
	DEFINE(TASK_FLAGS,        दुरत्व(काष्ठा task_काष्ठा, flags));
	DEFINE(TASK_PTRACE,       दुरत्व(काष्ठा task_काष्ठा, ptrace));
	DEFINE(TASK_THREAD,       दुरत्व(काष्ठा task_काष्ठा, thपढ़ो));
	DEFINE(TASK_MM,           दुरत्व(काष्ठा task_काष्ठा, mm));
	DEFINE(TASK_ACTIVE_MM,    दुरत्व(काष्ठा task_काष्ठा, active_mm));

	/* offsets पूर्णांकo the thपढ़ो काष्ठा */
	DEFINE(THREAD_KSP,        दुरत्व(काष्ठा thपढ़ो_काष्ठा, sp));
	DEFINE(THREAD_FESR,       दुरत्व(काष्ठा thपढ़ो_काष्ठा, user_fp.fesr));
	DEFINE(THREAD_FCR,        दुरत्व(काष्ठा thपढ़ो_काष्ठा, user_fp.fcr));
	DEFINE(THREAD_FPREG,      दुरत्व(काष्ठा thपढ़ो_काष्ठा, user_fp.vr));

	/* offsets पूर्णांकo the thपढ़ो_info काष्ठा */
	DEFINE(TINFO_FLAGS,       दुरत्व(काष्ठा thपढ़ो_info, flags));
	DEFINE(TINFO_PREEMPT,     दुरत्व(काष्ठा thपढ़ो_info, preempt_count));
	DEFINE(TINFO_ADDR_LIMIT,  दुरत्व(काष्ठा thपढ़ो_info, addr_limit));
	DEFINE(TINFO_TP_VALUE,   दुरत्व(काष्ठा thपढ़ो_info, tp_value));
	DEFINE(TINFO_TASK,        दुरत्व(काष्ठा thपढ़ो_info, task));

	/* offsets पूर्णांकo the pt_regs */
	DEFINE(PT_PC,             दुरत्व(काष्ठा pt_regs, pc));
	DEFINE(PT_ORIG_AO,        दुरत्व(काष्ठा pt_regs, orig_a0));
	DEFINE(PT_SR,             दुरत्व(काष्ठा pt_regs, sr));

	DEFINE(PT_A0,             दुरत्व(काष्ठा pt_regs, a0));
	DEFINE(PT_A1,             दुरत्व(काष्ठा pt_regs, a1));
	DEFINE(PT_A2,             दुरत्व(काष्ठा pt_regs, a2));
	DEFINE(PT_A3,             दुरत्व(काष्ठा pt_regs, a3));
	DEFINE(PT_REGS0,          दुरत्व(काष्ठा pt_regs, regs[0]));
	DEFINE(PT_REGS1,          दुरत्व(काष्ठा pt_regs, regs[1]));
	DEFINE(PT_REGS2,          दुरत्व(काष्ठा pt_regs, regs[2]));
	DEFINE(PT_REGS3,          दुरत्व(काष्ठा pt_regs, regs[3]));
	DEFINE(PT_REGS4,          दुरत्व(काष्ठा pt_regs, regs[4]));
	DEFINE(PT_REGS5,          दुरत्व(काष्ठा pt_regs, regs[5]));
	DEFINE(PT_REGS6,          दुरत्व(काष्ठा pt_regs, regs[6]));
	DEFINE(PT_REGS7,          दुरत्व(काष्ठा pt_regs, regs[7]));
	DEFINE(PT_REGS8,          दुरत्व(काष्ठा pt_regs, regs[8]));
	DEFINE(PT_REGS9,          दुरत्व(काष्ठा pt_regs, regs[9]));
	DEFINE(PT_R15,            दुरत्व(काष्ठा pt_regs, lr));
#अगर defined(__CSKYABIV2__)
	DEFINE(PT_R16,            दुरत्व(काष्ठा pt_regs, exregs[0]));
	DEFINE(PT_R17,            दुरत्व(काष्ठा pt_regs, exregs[1]));
	DEFINE(PT_R18,            दुरत्व(काष्ठा pt_regs, exregs[2]));
	DEFINE(PT_R19,            दुरत्व(काष्ठा pt_regs, exregs[3]));
	DEFINE(PT_R20,            दुरत्व(काष्ठा pt_regs, exregs[4]));
	DEFINE(PT_R21,            दुरत्व(काष्ठा pt_regs, exregs[5]));
	DEFINE(PT_R22,            दुरत्व(काष्ठा pt_regs, exregs[6]));
	DEFINE(PT_R23,            दुरत्व(काष्ठा pt_regs, exregs[7]));
	DEFINE(PT_R24,            दुरत्व(काष्ठा pt_regs, exregs[8]));
	DEFINE(PT_R25,            दुरत्व(काष्ठा pt_regs, exregs[9]));
	DEFINE(PT_R26,            दुरत्व(काष्ठा pt_regs, exregs[10]));
	DEFINE(PT_R27,            दुरत्व(काष्ठा pt_regs, exregs[11]));
	DEFINE(PT_R28,            दुरत्व(काष्ठा pt_regs, exregs[12]));
	DEFINE(PT_R29,            दुरत्व(काष्ठा pt_regs, exregs[13]));
	DEFINE(PT_R30,            दुरत्व(काष्ठा pt_regs, exregs[14]));
	DEFINE(PT_R31,            दुरत्व(काष्ठा pt_regs, exregs[15]));
	DEFINE(PT_RHI,            दुरत्व(काष्ठा pt_regs, rhi));
	DEFINE(PT_RLO,            दुरत्व(काष्ठा pt_regs, rlo));
#पूर्ण_अगर
	DEFINE(PT_USP,            दुरत्व(काष्ठा pt_regs, usp));
	DEFINE(PT_FRAME_SIZE,     माप(काष्ठा pt_regs));

	/* offsets पूर्णांकo the irq_cpustat_t काष्ठा */
	DEFINE(CPUSTAT_SOFTIRQ_PENDING, दुरत्व(irq_cpustat_t,
						__softirq_pending));

	/* संकेत defines */
	DEFINE(संक_अंश, संक_अंश);
	DEFINE(SIGTRAP, SIGTRAP);

	वापस 0;
पूर्ण
