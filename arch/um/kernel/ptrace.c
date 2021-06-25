<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/audit.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace-abi.h>

व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	child->ptrace |= PT_DTRACE;
	child->thपढ़ो.singlestep_syscall = 0;

#अगर_घोषित SUBARCH_SET_SINGLESTEPPING
	SUBARCH_SET_SINGLESTEPPING(child, 1);
#पूर्ण_अगर
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	child->ptrace &= ~PT_DTRACE;
	child->thपढ़ो.singlestep_syscall = 0;

#अगर_घोषित SUBARCH_SET_SINGLESTEPPING
	SUBARCH_SET_SINGLESTEPPING(child, 0);
#पूर्ण_अगर
पूर्ण

/*
 * Called by kernel/ptrace.c when detaching..
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	user_disable_single_step(child);
पूर्ण

बाह्य पूर्णांक peek_user(काष्ठा task_काष्ठा * child, दीर्घ addr, दीर्घ data);
बाह्य पूर्णांक poke_user(काष्ठा task_काष्ठा * child, दीर्घ addr, दीर्घ data);

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक i, ret;
	अचिन्हित दीर्घ __user *p = (व्योम __user *)data;
	व्योम __user *vp = p;

	चयन (request) अणु
	/* पढ़ो the word at location addr in the USER area. */
	हाल PTRACE_PEEKUSR:
		ret = peek_user(child, addr, data);
		अवरोध;

	/* ग_लिखो the word at location addr in the USER area */
	हाल PTRACE_POKEUSR:
		ret = poke_user(child, addr, data);
		अवरोध;

	हाल PTRACE_SYSEMU:
	हाल PTRACE_SYSEMU_SINGLESTEP:
		ret = -EIO;
		अवरोध;

#अगर_घोषित PTRACE_GETREGS
	हाल PTRACE_GETREGS: अणु /* Get all gp regs from the child. */
		अगर (!access_ok(p, MAX_REG_OFFSET)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		क्रम ( i = 0; i < MAX_REG_OFFSET; i += माप(दीर्घ) ) अणु
			__put_user(getreg(child, i), p);
			p++;
		पूर्ण
		ret = 0;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित PTRACE_SETREGS
	हाल PTRACE_SETREGS: अणु /* Set all gp regs in the child. */
		अचिन्हित दीर्घ पंचांगp = 0;
		अगर (!access_ok(p, MAX_REG_OFFSET)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		क्रम ( i = 0; i < MAX_REG_OFFSET; i += माप(दीर्घ) ) अणु
			__get_user(पंचांगp, p);
			putreg(child, i, पंचांगp);
			p++;
		पूर्ण
		ret = 0;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल PTRACE_GET_THREAD_AREA:
		ret = ptrace_get_thपढ़ो_area(child, addr, vp);
		अवरोध;

	हाल PTRACE_SET_THREAD_AREA:
		ret = ptrace_set_thपढ़ो_area(child, addr, vp);
		अवरोध;

	शेष:
		ret = ptrace_request(child, request, addr, data);
		अगर (ret == -EIO)
			ret = subarch_ptrace(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम send_sigtrap(काष्ठा uml_pt_regs *regs, पूर्णांक error_code)
अणु
	/* Send us the fake SIGTRAP */
	क्रमce_sig_fault(SIGTRAP, TRAP_BRKPT,
			/* User-mode eip? */
			UPT_IS_USER(regs) ? (व्योम __user *) UPT_IP(regs) : शून्य);
पूर्ण

/*
 * XXX Check PT_DTRACE vs TIF_SINGLESTEP क्रम singlestepping check and
 * PT_PTRACED vs TIF_SYSCALL_TRACE क्रम syscall tracing check
 */
पूर्णांक syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	audit_syscall_entry(UPT_SYSCALL_NR(&regs->regs),
			    UPT_SYSCALL_ARG1(&regs->regs),
			    UPT_SYSCALL_ARG2(&regs->regs),
			    UPT_SYSCALL_ARG3(&regs->regs),
			    UPT_SYSCALL_ARG4(&regs->regs));

	अगर (!test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		वापस 0;

	वापस tracehook_report_syscall_entry(regs);
पूर्ण

व्योम syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
	पूर्णांक ptraced = current->ptrace;

	audit_syscall_निकास(regs);

	/* Fake a debug trap */
	अगर (ptraced & PT_DTRACE)
		send_sigtrap(&regs->regs, 0);

	अगर (!test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		वापस;

	tracehook_report_syscall_निकास(regs, 0);
	/* क्रमce करो_संकेत() --> is_syscall() */
	अगर (ptraced & PT_PTRACED)
		set_thपढ़ो_flag(TIF_SIGPENDING);
पूर्ण
