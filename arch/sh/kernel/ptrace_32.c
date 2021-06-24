<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH process tracing
 *
 * Copyright (C) 1999, 2000  Kaz Kojima & Niibe Yutaka
 * Copyright (C) 2002 - 2009  Paul Mundt
 *
 * Audit support by Yuichi Nakamura <ynakam@hitachisoft.jp>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/security.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/पन.स>
#समावेश <linux/audit.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/elf.h>
#समावेश <linux/regset.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/fpu.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

/*
 * This routine will get a word off of the process kernel stack.
 */
अटल अंतरभूत पूर्णांक get_stack_दीर्घ(काष्ठा task_काष्ठा *task, पूर्णांक offset)
अणु
	अचिन्हित अक्षर *stack;

	stack = (अचिन्हित अक्षर *)task_pt_regs(task);
	stack += offset;
	वापस (*((पूर्णांक *)stack));
पूर्ण

/*
 * This routine will put a word on the process kernel stack.
 */
अटल अंतरभूत पूर्णांक put_stack_दीर्घ(काष्ठा task_काष्ठा *task, पूर्णांक offset,
				 अचिन्हित दीर्घ data)
अणु
	अचिन्हित अक्षर *stack;

	stack = (अचिन्हित अक्षर *)task_pt_regs(task);
	stack += offset;
	*(अचिन्हित दीर्घ *) stack = data;
	वापस 0;
पूर्ण

व्योम ptrace_triggered(काष्ठा perf_event *bp,
		      काष्ठा perf_sample_data *data, काष्ठा pt_regs *regs)
अणु
	काष्ठा perf_event_attr attr;

	/*
	 * Disable the अवरोधpoपूर्णांक request here since ptrace has defined a
	 * one-shot behaviour क्रम अवरोधpoपूर्णांक exceptions.
	 */
	attr = bp->attr;
	attr.disabled = true;
	modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
पूर्ण

अटल पूर्णांक set_single_step(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr)
अणु
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &tsk->thपढ़ो;
	काष्ठा perf_event *bp;
	काष्ठा perf_event_attr attr;

	bp = thपढ़ो->ptrace_bps[0];
	अगर (!bp) अणु
		ptrace_अवरोधpoपूर्णांक_init(&attr);

		attr.bp_addr = addr;
		attr.bp_len = HW_BREAKPOINT_LEN_2;
		attr.bp_type = HW_BREAKPOINT_R;

		bp = रेजिस्टर_user_hw_अवरोधpoपूर्णांक(&attr, ptrace_triggered,
						 शून्य, tsk);
		अगर (IS_ERR(bp))
			वापस PTR_ERR(bp);

		thपढ़ो->ptrace_bps[0] = bp;
	पूर्ण अन्यथा अणु
		पूर्णांक err;

		attr = bp->attr;
		attr.bp_addr = addr;
		/* reenable अवरोधpoपूर्णांक */
		attr.disabled = false;
		err = modअगरy_user_hw_अवरोधpoपूर्णांक(bp, &attr);
		अगर (unlikely(err))
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	अचिन्हित दीर्घ pc = get_stack_दीर्घ(child, दुरत्व(काष्ठा pt_regs, pc));

	set_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);

	set_single_step(child, pc);
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	clear_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);
पूर्ण

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure single step bits etc are not set.
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	user_disable_single_step(child);
पूर्ण

अटल पूर्णांक genregs_get(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = task_pt_regs(target);

	वापस membuf_ग_लिखो(&to, regs, माप(काष्ठा pt_regs));
पूर्ण

अटल पूर्णांक genregs_set(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	पूर्णांक ret;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 regs->regs,
				 0, 16 * माप(अचिन्हित दीर्घ));
	अगर (!ret && count > 0)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &regs->pc,
					 दुरत्व(काष्ठा pt_regs, pc),
					 माप(काष्ठा pt_regs));
	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						माप(काष्ठा pt_regs), -1);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SH_FPU
अटल पूर्णांक fpregs_get(काष्ठा task_काष्ठा *target,
	       स्थिर काष्ठा user_regset *regset,
	       काष्ठा membuf to)
अणु
	पूर्णांक ret;

	ret = init_fpu(target);
	अगर (ret)
		वापस ret;

	वापस membuf_ग_लिखो(&to, target->thपढ़ो.xstate,
			    माप(काष्ठा user_fpu_काष्ठा));
पूर्ण

अटल पूर्णांक fpregs_set(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;

	ret = init_fpu(target);
	अगर (ret)
		वापस ret;

	set_stopped_child_used_math(target);

	अगर ((boot_cpu_data.flags & CPU_HAS_FPU))
		वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					  &target->thपढ़ो.xstate->hardfpu, 0, -1);

	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  &target->thपढ़ो.xstate->softfpu, 0, -1);
पूर्ण

अटल पूर्णांक fpregs_active(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset)
अणु
	वापस tsk_used_math(target) ? regset->n : 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SH_DSP
अटल पूर्णांक dspregs_get(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_dspregs *regs =
		(काष्ठा pt_dspregs *)&target->thपढ़ो.dsp_status.dsp_regs;

	वापस membuf_ग_लिखो(&to, regs, माप(काष्ठा pt_dspregs));
पूर्ण

अटल पूर्णांक dspregs_set(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_dspregs *regs =
		(काष्ठा pt_dspregs *)&target->thपढ़ो.dsp_status.dsp_regs;
	पूर्णांक ret;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, regs,
				 0, माप(काष्ठा pt_dspregs));
	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						माप(काष्ठा pt_dspregs), -1);

	वापस ret;
पूर्ण

अटल पूर्णांक dspregs_active(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);

	वापस regs->sr & SR_DSP ? regset->n : 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
	REGS_OFFSET_NAME(0),
	REGS_OFFSET_NAME(1),
	REGS_OFFSET_NAME(2),
	REGS_OFFSET_NAME(3),
	REGS_OFFSET_NAME(4),
	REGS_OFFSET_NAME(5),
	REGS_OFFSET_NAME(6),
	REGS_OFFSET_NAME(7),
	REGS_OFFSET_NAME(8),
	REGS_OFFSET_NAME(9),
	REGS_OFFSET_NAME(10),
	REGS_OFFSET_NAME(11),
	REGS_OFFSET_NAME(12),
	REGS_OFFSET_NAME(13),
	REGS_OFFSET_NAME(14),
	REGS_OFFSET_NAME(15),
	REG_OFFSET_NAME(pc),
	REG_OFFSET_NAME(pr),
	REG_OFFSET_NAME(sr),
	REG_OFFSET_NAME(gbr),
	REG_OFFSET_NAME(mach),
	REG_OFFSET_NAME(macl),
	REG_OFFSET_NAME(tra),
	REG_OFFSET_END,
पूर्ण;

/*
 * These are our native regset flavours.
 */
क्रमागत sh_regset अणु
	REGSET_GENERAL,
#अगर_घोषित CONFIG_SH_FPU
	REGSET_FPU,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SH_DSP
	REGSET_DSP,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset sh_regsets[] = अणु
	/*
	 * Format is:
	 *	R0 --> R15
	 *	PC, PR, SR, GBR, MACH, MACL, TRA
	 */
	[REGSET_GENERAL] = अणु
		.core_note_type	= NT_PRSTATUS,
		.n		= ELF_NGREG,
		.size		= माप(दीर्घ),
		.align		= माप(दीर्घ),
		.regset_get		= genregs_get,
		.set		= genregs_set,
	पूर्ण,

#अगर_घोषित CONFIG_SH_FPU
	[REGSET_FPU] = अणु
		.core_note_type	= NT_PRFPREG,
		.n		= माप(काष्ठा user_fpu_काष्ठा) / माप(दीर्घ),
		.size		= माप(दीर्घ),
		.align		= माप(दीर्घ),
		.regset_get		= fpregs_get,
		.set		= fpregs_set,
		.active		= fpregs_active,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_SH_DSP
	[REGSET_DSP] = अणु
		.n		= माप(काष्ठा pt_dspregs) / माप(दीर्घ),
		.size		= माप(दीर्घ),
		.align		= माप(दीर्घ),
		.regset_get		= dspregs_get,
		.set		= dspregs_set,
		.active		= dspregs_active,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_sh_native_view = अणु
	.name		= "sh",
	.e_machine	= EM_SH,
	.regsets	= sh_regsets,
	.n		= ARRAY_SIZE(sh_regsets),
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &user_sh_native_view;
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	अचिन्हित दीर्घ __user *datap = (अचिन्हित दीर्घ __user *)data;
	पूर्णांक ret;

	चयन (request) अणु
	/* पढ़ो the word at location addr in the USER area. */
	हाल PTRACE_PEEKUSR: अणु
		अचिन्हित दीर्घ पंचांगp;

		ret = -EIO;
		अगर ((addr & 3) || addr < 0 ||
		    addr > माप(काष्ठा user) - 3)
			अवरोध;

		अगर (addr < माप(काष्ठा pt_regs))
			पंचांगp = get_stack_दीर्घ(child, addr);
		अन्यथा अगर (addr >= दुरत्व(काष्ठा user, fpu) &&
			 addr < दुरत्व(काष्ठा user, u_fpvalid)) अणु
			अगर (!tsk_used_math(child)) अणु
				अगर (addr == दुरत्व(काष्ठा user, fpu.fpscr))
					पंचांगp = FPSCR_INIT;
				अन्यथा
					पंचांगp = 0;
			पूर्ण अन्यथा अणु
				अचिन्हित दीर्घ index;
				ret = init_fpu(child);
				अगर (ret)
					अवरोध;
				index = addr - दुरत्व(काष्ठा user, fpu);
				पंचांगp = ((अचिन्हित दीर्घ *)child->thपढ़ो.xstate)
					[index >> 2];
			पूर्ण
		पूर्ण अन्यथा अगर (addr == दुरत्व(काष्ठा user, u_fpvalid))
			पंचांगp = !!tsk_used_math(child);
		अन्यथा अगर (addr == PT_TEXT_ADDR)
			पंचांगp = child->mm->start_code;
		अन्यथा अगर (addr == PT_DATA_ADDR)
			पंचांगp = child->mm->start_data;
		अन्यथा अगर (addr == PT_TEXT_END_ADDR)
			पंचांगp = child->mm->end_code;
		अन्यथा अगर (addr == PT_TEXT_LEN)
			पंचांगp = child->mm->end_code - child->mm->start_code;
		अन्यथा
			पंचांगp = 0;
		ret = put_user(पंचांगp, datap);
		अवरोध;
	पूर्ण

	हाल PTRACE_POKEUSR: /* ग_लिखो the word at location addr in the USER area */
		ret = -EIO;
		अगर ((addr & 3) || addr < 0 ||
		    addr > माप(काष्ठा user) - 3)
			अवरोध;

		अगर (addr < माप(काष्ठा pt_regs))
			ret = put_stack_दीर्घ(child, addr, data);
		अन्यथा अगर (addr >= दुरत्व(काष्ठा user, fpu) &&
			 addr < दुरत्व(काष्ठा user, u_fpvalid)) अणु
			अचिन्हित दीर्घ index;
			ret = init_fpu(child);
			अगर (ret)
				अवरोध;
			index = addr - दुरत्व(काष्ठा user, fpu);
			set_stopped_child_used_math(child);
			((अचिन्हित दीर्घ *)child->thपढ़ो.xstate)
				[index >> 2] = data;
			ret = 0;
		पूर्ण अन्यथा अगर (addr == दुरत्व(काष्ठा user, u_fpvalid)) अणु
			conditional_stopped_child_used_math(data, child);
			ret = 0;
		पूर्ण
		अवरोध;

	हाल PTRACE_GETREGS:
		वापस copy_regset_to_user(child, &user_sh_native_view,
					   REGSET_GENERAL,
					   0, माप(काष्ठा pt_regs),
					   datap);
	हाल PTRACE_SETREGS:
		वापस copy_regset_from_user(child, &user_sh_native_view,
					     REGSET_GENERAL,
					     0, माप(काष्ठा pt_regs),
					     datap);
#अगर_घोषित CONFIG_SH_FPU
	हाल PTRACE_GETFPREGS:
		वापस copy_regset_to_user(child, &user_sh_native_view,
					   REGSET_FPU,
					   0, माप(काष्ठा user_fpu_काष्ठा),
					   datap);
	हाल PTRACE_SETFPREGS:
		वापस copy_regset_from_user(child, &user_sh_native_view,
					     REGSET_FPU,
					     0, माप(काष्ठा user_fpu_काष्ठा),
					     datap);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SH_DSP
	हाल PTRACE_GETDSPREGS:
		वापस copy_regset_to_user(child, &user_sh_native_view,
					   REGSET_DSP,
					   0, माप(काष्ठा pt_dspregs),
					   datap);
	हाल PTRACE_SETDSPREGS:
		वापस copy_regset_from_user(child, &user_sh_native_view,
					     REGSET_DSP,
					     0, माप(काष्ठा pt_dspregs),
					     datap);
#पूर्ण_अगर
	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

यंत्रlinkage दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE) &&
	    tracehook_report_syscall_entry(regs)) अणु
		regs->regs[0] = -ENOSYS;
		वापस -1;
	पूर्ण

	अगर (secure_computing() == -1)
		वापस -1;

	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->regs[0]);

	audit_syscall_entry(regs->regs[3], regs->regs[4], regs->regs[5],
			    regs->regs[6], regs->regs[7]);

	वापस 0;
पूर्ण

यंत्रlinkage व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
	पूर्णांक step;

	audit_syscall_निकास(regs);

	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_निकास(regs, regs->regs[0]);

	step = test_thपढ़ो_flag(TIF_SINGLESTEP);
	अगर (step || test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, step);
पूर्ण
