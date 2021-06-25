<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC ptrace.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2005 Gyorgy Jeney <nog@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/माला.स>

#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/audit.h>
#समावेश <linux/regset.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/elf.h>

#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/page.h>

/*
 * Copy the thपढ़ो state to a regset that can be पूर्णांकerpreted by userspace.
 *
 * It करोesn't matter what our पूर्णांकernal pt_regs काष्ठाure looks like.  The
 * important thing is that we export a consistent view of the thपढ़ो state
 * to userspace.  As such, we need to make sure that the regset reमुख्यs
 * ABI compatible as defined by the काष्ठा user_regs_काष्ठा:
 *
 * (Each item is a 32-bit word)
 * r0 = 0 (exported क्रम clarity)
 * 31 GPRS r1-r31
 * PC (Program counter)
 * SR (Supervision रेजिस्टर)
 */
अटल पूर्णांक genregs_get(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = task_pt_regs(target);

	/* r0 */
	membuf_zero(&to, 4);
	membuf_ग_लिखो(&to, regs->gpr + 1, 31 * 4);
	membuf_store(&to, regs->pc);
	वापस membuf_store(&to, regs->sr);
पूर्ण

/*
 * Set the thपढ़ो state from a regset passed in via ptrace
 */
अटल पूर्णांक genregs_set(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		       स्थिर व्योम *kbuf, स्थिर व्योम __user * ubuf)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	पूर्णांक ret;

	/* ignore r0 */
	ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf, 0, 4);
	/* r1 - r31 */
	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 regs->gpr+1, 4, 4*32);
	/* PC */
	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &regs->pc, 4*32, 4*33);
	/*
	 * Skip SR and padding... userspace isn't allowed to changes bits in
	 * the Supervision रेजिस्टर
	 */
	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						4*33, -1);

	वापस ret;
पूर्ण

/*
 * Define the रेजिस्टर sets available on OpenRISC under Linux
 */
क्रमागत or1k_regset अणु
	REGSET_GENERAL,
पूर्ण;

अटल स्थिर काष्ठा user_regset or1k_regsets[] = अणु
	[REGSET_GENERAL] = अणु
			    .core_note_type = NT_PRSTATUS,
			    .n = ELF_NGREG,
			    .size = माप(दीर्घ),
			    .align = माप(दीर्घ),
			    .regset_get = genregs_get,
			    .set = genregs_set,
			    पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_or1k_native_view = अणु
	.name = "or1k",
	.e_machine = EM_OPENRISC,
	.regsets = or1k_regsets,
	.n = ARRAY_SIZE(or1k_regsets),
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &user_or1k_native_view;
पूर्ण

/*
 * करोes not yet catch संकेतs sent when the child dies.
 * in निकास.c or in संकेत.c.
 */


/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure the single step bit is not set.
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	pr_debug("ptrace_disable(): TODO\n");

	user_disable_single_step(child);
	clear_tsk_thपढ़ो_flag(child, TIF_SYSCALL_TRACE);
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request, अचिन्हित दीर्घ addr,
		 अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret;

	चयन (request) अणु
	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Notअगरication of प्रणाली call entry/निकास
 * - triggered by current->work.syscall_trace
 */
यंत्रlinkage दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	दीर्घ ret = 0;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE) &&
	    tracehook_report_syscall_entry(regs))
		/*
		 * Tracing decided this syscall should not happen.
		 * We'll वापस a bogus call number to get an ENOSYS
		 * error, but leave the original number in <something>.
		 */
		ret = -1L;

	audit_syscall_entry(regs->gpr[11], regs->gpr[3], regs->gpr[4],
			    regs->gpr[5], regs->gpr[6]);

	वापस ret ? : regs->gpr[11];
पूर्ण

यंत्रlinkage व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
	पूर्णांक step;

	audit_syscall_निकास(regs);

	step = test_thपढ़ो_flag(TIF_SINGLESTEP);
	अगर (step || test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, step);
पूर्ण
