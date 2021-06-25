<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Collabora Ltd.
 */
#समावेश <linux/sched.h>
#समावेश <linux/prctl.h>
#समावेश <linux/syscall_user_dispatch.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/elf.h>

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/syscall.h>

#समावेश "common.h"

अटल व्योम trigger_sigsys(काष्ठा pt_regs *regs)
अणु
	काष्ठा kernel_siginfo info;

	clear_siginfo(&info);
	info.si_signo = SIGSYS;
	info.si_code = SYS_USER_DISPATCH;
	info.si_call_addr = (व्योम __user *)KSTK_EIP(current);
	info.si_त्रुटि_सं = 0;
	info.si_arch = syscall_get_arch(current);
	info.si_syscall = syscall_get_nr(current, regs);

	क्रमce_sig_info(&info);
पूर्ण

bool syscall_user_dispatch(काष्ठा pt_regs *regs)
अणु
	काष्ठा syscall_user_dispatch *sd = &current->syscall_dispatch;
	अक्षर state;

	अगर (likely(inकाष्ठाion_poपूर्णांकer(regs) - sd->offset < sd->len))
		वापस false;

	अगर (unlikely(arch_syscall_is_vdso_sigवापस(regs)))
		वापस false;

	अगर (likely(sd->selector)) अणु
		/*
		 * access_ok() is perक्रमmed once, at prctl समय, when
		 * the selector is loaded by userspace.
		 */
		अगर (unlikely(__get_user(state, sd->selector)))
			करो_निकास(संक_अंश);

		अगर (likely(state == SYSCALL_DISPATCH_FILTER_ALLOW))
			वापस false;

		अगर (state != SYSCALL_DISPATCH_FILTER_BLOCK)
			करो_निकास(SIGSYS);
	पूर्ण

	sd->on_dispatch = true;
	syscall_rollback(current, regs);
	trigger_sigsys(regs);

	वापस true;
पूर्ण

पूर्णांक set_syscall_user_dispatch(अचिन्हित दीर्घ mode, अचिन्हित दीर्घ offset,
			      अचिन्हित दीर्घ len, अक्षर __user *selector)
अणु
	चयन (mode) अणु
	हाल PR_SYS_DISPATCH_OFF:
		अगर (offset || len || selector)
			वापस -EINVAL;
		अवरोध;
	हाल PR_SYS_DISPATCH_ON:
		/*
		 * Validate the direct dispatcher region just क्रम basic
		 * sanity against overflow and a 0-sized dispatcher
		 * region.  If the user is able to submit a syscall from
		 * an address, that address is obviously valid.
		 */
		अगर (offset && offset + len <= offset)
			वापस -EINVAL;

		अगर (selector && !access_ok(selector, माप(*selector)))
			वापस -EFAULT;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	current->syscall_dispatch.selector = selector;
	current->syscall_dispatch.offset = offset;
	current->syscall_dispatch.len = len;
	current->syscall_dispatch.on_dispatch = false;

	अगर (mode == PR_SYS_DISPATCH_ON)
		set_syscall_work(SYSCALL_USER_DISPATCH);
	अन्यथा
		clear_syscall_work(SYSCALL_USER_DISPATCH);

	वापस 0;
पूर्ण
