<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/ptrace.h>
#समावेश <linux/regset.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/elf.h>
#समावेश <linux/sched/task_stack.h>

क्रमागत nds32_regset अणु
	REGSET_GPR,
पूर्ण;

अटल पूर्णांक gpr_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	वापस membuf_ग_लिखो(&to, &task_pt_regs(target)->user_regs,
				माप(काष्ठा user_pt_regs));
पूर्ण

अटल पूर्णांक gpr_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user * ubuf)
अणु
	पूर्णांक err;
	काष्ठा user_pt_regs newregs = task_pt_regs(target)->user_regs;

	err = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &newregs, 0, -1);
	अगर (err)
		वापस err;

	task_pt_regs(target)->user_regs = newregs;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा user_regset nds32_regsets[] = अणु
	[REGSET_GPR] = अणु
			.core_note_type = NT_PRSTATUS,
			.n = माप(काष्ठा user_pt_regs) / माप(u32),
			.size = माप(elf_greg_t),
			.align = माप(elf_greg_t),
			.regset_get = gpr_get,
			.set = gpr_setपूर्ण
पूर्ण;

अटल स्थिर काष्ठा user_regset_view nds32_user_view = अणु
	.name = "nds32",
	.e_machine = EM_NDS32,
	.regsets = nds32_regsets,
	.n = ARRAY_SIZE(nds32_regsets)
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &nds32_user_view;
पूर्ण

व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	user_disable_single_step(child);
पूर्ण

/* करो_ptrace()
 *
 * Provide ptrace defined service.
 */
दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request, अचिन्हित दीर्घ addr,
		 अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret = -EIO;

	चयन (request) अणु
	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	काष्ठा pt_regs *regs;
	regs = task_pt_regs(child);
	regs->ipsw |= PSW_mskHSS;
	set_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	काष्ठा pt_regs *regs;
	regs = task_pt_regs(child);
	regs->ipsw &= ~PSW_mskHSS;
	clear_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);
पूर्ण

/* sys_trace()
 *
 * syscall trace handler.
 */

यंत्रlinkage पूर्णांक syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE)) अणु
		अगर (tracehook_report_syscall_entry(regs))
			क्रमget_syscall(regs);
	पूर्ण
	वापस regs->syscallno;
पूर्ण

यंत्रlinkage व्योम syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
	पूर्णांक step = test_thपढ़ो_flag(TIF_SINGLESTEP);
	अगर (step || test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, step);

पूर्ण
