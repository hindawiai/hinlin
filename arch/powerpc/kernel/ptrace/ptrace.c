<शैली गुरु>
/*
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Derived from "arch/m68k/kernel/ptrace.c"
 *  Copyright (C) 1994 by Hamish Macकरोnald
 *  Taken from linux/kernel/ptrace.c and modअगरied क्रम M680x0.
 *  linux/kernel/ptrace.c is by Ross Biro 1/23/92, edited by Linus Torvalds
 *
 * Modअगरied by Cort Dougan (cort@hq.fsmद_असल.com)
 * and Paul Mackerras (paulus@samba.org).
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file README.legal in the मुख्य directory of
 * this archive क्रम more details.
 */

#समावेश <linux/regset.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/audit.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/debug.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

#समावेश "ptrace-decl.h"

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure single step bits etc are not set.
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	/* make sure the single step bit is not set. */
	user_disable_single_step(child);
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret = -EPERM;
	व्योम __user *datavp = (व्योम __user *) data;
	अचिन्हित दीर्घ __user *datalp = datavp;

	चयन (request) अणु
	/* पढ़ो the word at location addr in the USER area. */
	हाल PTRACE_PEEKUSR: अणु
		अचिन्हित दीर्घ index, पंचांगp;

		ret = -EIO;
		/* convert to index and check */
		index = addr / माप(दीर्घ);
		अगर ((addr & (माप(दीर्घ) - 1)) || !child->thपढ़ो.regs)
			अवरोध;

		अगर (index < PT_FPR0)
			ret = ptrace_get_reg(child, (पूर्णांक) index, &पंचांगp);
		अन्यथा
			ret = ptrace_get_fpr(child, index, &पंचांगp);

		अगर (ret)
			अवरोध;
		ret = put_user(पंचांगp, datalp);
		अवरोध;
	पूर्ण

	/* ग_लिखो the word at location addr in the USER area */
	हाल PTRACE_POKEUSR: अणु
		अचिन्हित दीर्घ index;

		ret = -EIO;
		/* convert to index and check */
		index = addr / माप(दीर्घ);
		अगर ((addr & (माप(दीर्घ) - 1)) || !child->thपढ़ो.regs)
			अवरोध;

		अगर (index < PT_FPR0)
			ret = ptrace_put_reg(child, index, data);
		अन्यथा
			ret = ptrace_put_fpr(child, index, data);
		अवरोध;
	पूर्ण

	हाल PPC_PTRACE_GETHWDBGINFO: अणु
		काष्ठा ppc_debug_info dbginfo;

		ppc_gethwdinfo(&dbginfo);

		अगर (copy_to_user(datavp, &dbginfo,
				 माप(काष्ठा ppc_debug_info)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	हाल PPC_PTRACE_SETHWDEBUG: अणु
		काष्ठा ppc_hw_अवरोधpoपूर्णांक bp_info;

		अगर (copy_from_user(&bp_info, datavp,
				   माप(काष्ठा ppc_hw_अवरोधpoपूर्णांक)))
			वापस -EFAULT;
		वापस ppc_set_hwdebug(child, &bp_info);
	पूर्ण

	हाल PPC_PTRACE_DELHWDEBUG: अणु
		ret = ppc_del_hwdebug(child, data);
		अवरोध;
	पूर्ण

	हाल PTRACE_GET_DEBUGREG:
		ret = ptrace_get_debugreg(child, addr, datalp);
		अवरोध;

	हाल PTRACE_SET_DEBUGREG:
		ret = ptrace_set_debugreg(child, addr, data);
		अवरोध;

#अगर_घोषित CONFIG_PPC64
	हाल PTRACE_GETREGS64:
#पूर्ण_अगर
	हाल PTRACE_GETREGS:	/* Get all pt_regs from the child. */
		वापस copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_GPR,
					   0, माप(काष्ठा user_pt_regs),
					   datavp);

#अगर_घोषित CONFIG_PPC64
	हाल PTRACE_SETREGS64:
#पूर्ण_अगर
	हाल PTRACE_SETREGS:	/* Set all gp regs in the child. */
		वापस copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_GPR,
					     0, माप(काष्ठा user_pt_regs),
					     datavp);

	हाल PTRACE_GETFPREGS: /* Get the child FPU state (FPR0...31 + FPSCR) */
		वापस copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_FPR,
					   0, माप(elf_fpregset_t),
					   datavp);

	हाल PTRACE_SETFPREGS: /* Set the child FPU state (FPR0...31 + FPSCR) */
		वापस copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_FPR,
					     0, माप(elf_fpregset_t),
					     datavp);

#अगर_घोषित CONFIG_ALTIVEC
	हाल PTRACE_GETVRREGS:
		वापस copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_VMX,
					   0, (33 * माप(vector128) +
					       माप(u32)),
					   datavp);

	हाल PTRACE_SETVRREGS:
		वापस copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_VMX,
					     0, (33 * माप(vector128) +
						 माप(u32)),
					     datavp);
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	हाल PTRACE_GETVSRREGS:
		वापस copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_VSX,
					   0, 32 * माप(द्विगुन),
					   datavp);

	हाल PTRACE_SETVSRREGS:
		वापस copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_VSX,
					     0, 32 * माप(द्विगुन),
					     datavp);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPE
	हाल PTRACE_GETEVRREGS:
		/* Get the child spe रेजिस्टर state. */
		वापस copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_SPE, 0, 35 * माप(u32),
					   datavp);

	हाल PTRACE_SETEVRREGS:
		/* Set the child spe रेजिस्टर state. */
		वापस copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_SPE, 0, 35 * माप(u32),
					     datavp);
#पूर्ण_अगर

	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SECCOMP
अटल पूर्णांक करो_seccomp(काष्ठा pt_regs *regs)
अणु
	अगर (!test_thपढ़ो_flag(TIF_SECCOMP))
		वापस 0;

	/*
	 * The ABI we present to seccomp tracers is that r3 contains
	 * the syscall वापस value and orig_gpr3 contains the first
	 * syscall parameter. This is dअगरferent to the ptrace ABI where
	 * both r3 and orig_gpr3 contain the first syscall parameter.
	 */
	regs->gpr[3] = -ENOSYS;

	/*
	 * We use the __ version here because we have alपढ़ोy checked
	 * TIF_SECCOMP. If this fails, there is nothing left to करो, we
	 * have alपढ़ोy loaded -ENOSYS पूर्णांकo r3, or seccomp has put
	 * something अन्यथा in r3 (via SECCOMP_RET_ERRNO/TRACE).
	 */
	अगर (__secure_computing(शून्य))
		वापस -1;

	/*
	 * The syscall was allowed by seccomp, restore the रेजिस्टर
	 * state to what audit expects.
	 * Note that we use orig_gpr3, which means a seccomp tracer can
	 * modअगरy the first syscall parameter (in orig_gpr3) and also
	 * allow the syscall to proceed.
	 */
	regs->gpr[3] = regs->orig_gpr3;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक करो_seccomp(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_SECCOMP */

/**
 * करो_syscall_trace_enter() - Do syscall tracing on kernel entry.
 * @regs: the pt_regs of the task to trace (current)
 *
 * Perक्रमms various types of tracing on syscall entry. This includes seccomp,
 * ptrace, syscall tracepoपूर्णांकs and audit.
 *
 * The pt_regs are potentially visible to userspace via ptrace, so their
 * contents is ABI.
 *
 * One or more of the tracers may modअगरy the contents of pt_regs, in particular
 * to modअगरy arguments or even the syscall number itself.
 *
 * It's also possible that a tracer can choose to reject the प्रणाली call. In
 * that हाल this function will वापस an illegal syscall number, and will put
 * an appropriate वापस value in regs->r3.
 *
 * Return: the (possibly changed) syscall number.
 */
दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	u32 flags;

	flags = READ_ONCE(current_thपढ़ो_info()->flags) &
		(_TIF_SYSCALL_EMU | _TIF_SYSCALL_TRACE);

	अगर (flags) अणु
		पूर्णांक rc = tracehook_report_syscall_entry(regs);

		अगर (unlikely(flags & _TIF_SYSCALL_EMU)) अणु
			/*
			 * A nonzero वापस code from
			 * tracehook_report_syscall_entry() tells us to prevent
			 * the syscall execution, but we are not going to
			 * execute it anyway.
			 *
			 * Returning -1 will skip the syscall execution. We want
			 * to aव्योम clobbering any रेजिस्टरs, so we करोn't जाओ
			 * the skip label below.
			 */
			वापस -1;
		पूर्ण

		अगर (rc) अणु
			/*
			 * The tracer decided to पात the syscall. Note that
			 * the tracer may also just change regs->gpr[0] to an
			 * invalid syscall number, that is handled below on the
			 * निकास path.
			 */
			जाओ skip;
		पूर्ण
	पूर्ण

	/* Run seccomp after ptrace; allow it to set gpr[3]. */
	अगर (करो_seccomp(regs))
		वापस -1;

	/* Aव्योम trace and audit when syscall is invalid. */
	अगर (regs->gpr[0] >= NR_syscalls)
		जाओ skip;

	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->gpr[0]);

	अगर (!is_32bit_task())
		audit_syscall_entry(regs->gpr[0], regs->gpr[3], regs->gpr[4],
				    regs->gpr[5], regs->gpr[6]);
	अन्यथा
		audit_syscall_entry(regs->gpr[0],
				    regs->gpr[3] & 0xffffffff,
				    regs->gpr[4] & 0xffffffff,
				    regs->gpr[5] & 0xffffffff,
				    regs->gpr[6] & 0xffffffff);

	/* Return the possibly modअगरied but valid syscall number */
	वापस regs->gpr[0];

skip:
	/*
	 * If we are पातing explicitly, or अगर the syscall number is
	 * now invalid, set the वापस value to -ENOSYS.
	 */
	regs->gpr[3] = -ENOSYS;
	वापस -1;
पूर्ण

व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
	पूर्णांक step;

	audit_syscall_निकास(regs);

	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_निकास(regs, regs->result);

	step = test_thपढ़ो_flag(TIF_SINGLESTEP);
	अगर (step || test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, step);
पूर्ण

व्योम __init pt_regs_check(व्योम);

/*
 * Dummy function, its purpose is to अवरोध the build अगर काष्ठा pt_regs and
 * काष्ठा user_pt_regs करोn't match.
 */
व्योम __init pt_regs_check(व्योम)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, gpr) !=
		     दुरत्व(काष्ठा user_pt_regs, gpr));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, nip) !=
		     दुरत्व(काष्ठा user_pt_regs, nip));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, msr) !=
		     दुरत्व(काष्ठा user_pt_regs, msr));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, orig_gpr3) !=
		     दुरत्व(काष्ठा user_pt_regs, orig_gpr3));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, ctr) !=
		     दुरत्व(काष्ठा user_pt_regs, ctr));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, link) !=
		     दुरत्व(काष्ठा user_pt_regs, link));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, xer) !=
		     दुरत्व(काष्ठा user_pt_regs, xer));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, ccr) !=
		     दुरत्व(काष्ठा user_pt_regs, ccr));
#अगर_घोषित __घातerpc64__
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, softe) !=
		     दुरत्व(काष्ठा user_pt_regs, softe));
#अन्यथा
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, mq) !=
		     दुरत्व(काष्ठा user_pt_regs, mq));
#पूर्ण_अगर
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, trap) !=
		     दुरत्व(काष्ठा user_pt_regs, trap));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, dar) !=
		     दुरत्व(काष्ठा user_pt_regs, dar));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, dsisr) !=
		     दुरत्व(काष्ठा user_pt_regs, dsisr));
	BUILD_BUG_ON(दुरत्व(काष्ठा pt_regs, result) !=
		     दुरत्व(काष्ठा user_pt_regs, result));

	BUILD_BUG_ON(माप(काष्ठा user_pt_regs) > माप(काष्ठा pt_regs));

	// Now check that the pt_regs offsets match the uapi #घोषणाs
	#घोषणा CHECK_REG(_pt, _reg) \
		BUILD_BUG_ON(_pt != (दुरत्व(काष्ठा user_pt_regs, _reg) / \
				     माप(अचिन्हित दीर्घ)));

	CHECK_REG(PT_R0,  gpr[0]);
	CHECK_REG(PT_R1,  gpr[1]);
	CHECK_REG(PT_R2,  gpr[2]);
	CHECK_REG(PT_R3,  gpr[3]);
	CHECK_REG(PT_R4,  gpr[4]);
	CHECK_REG(PT_R5,  gpr[5]);
	CHECK_REG(PT_R6,  gpr[6]);
	CHECK_REG(PT_R7,  gpr[7]);
	CHECK_REG(PT_R8,  gpr[8]);
	CHECK_REG(PT_R9,  gpr[9]);
	CHECK_REG(PT_R10, gpr[10]);
	CHECK_REG(PT_R11, gpr[11]);
	CHECK_REG(PT_R12, gpr[12]);
	CHECK_REG(PT_R13, gpr[13]);
	CHECK_REG(PT_R14, gpr[14]);
	CHECK_REG(PT_R15, gpr[15]);
	CHECK_REG(PT_R16, gpr[16]);
	CHECK_REG(PT_R17, gpr[17]);
	CHECK_REG(PT_R18, gpr[18]);
	CHECK_REG(PT_R19, gpr[19]);
	CHECK_REG(PT_R20, gpr[20]);
	CHECK_REG(PT_R21, gpr[21]);
	CHECK_REG(PT_R22, gpr[22]);
	CHECK_REG(PT_R23, gpr[23]);
	CHECK_REG(PT_R24, gpr[24]);
	CHECK_REG(PT_R25, gpr[25]);
	CHECK_REG(PT_R26, gpr[26]);
	CHECK_REG(PT_R27, gpr[27]);
	CHECK_REG(PT_R28, gpr[28]);
	CHECK_REG(PT_R29, gpr[29]);
	CHECK_REG(PT_R30, gpr[30]);
	CHECK_REG(PT_R31, gpr[31]);
	CHECK_REG(PT_NIP, nip);
	CHECK_REG(PT_MSR, msr);
	CHECK_REG(PT_ORIG_R3, orig_gpr3);
	CHECK_REG(PT_CTR, ctr);
	CHECK_REG(PT_LNK, link);
	CHECK_REG(PT_XER, xer);
	CHECK_REG(PT_CCR, ccr);
#अगर_घोषित CONFIG_PPC64
	CHECK_REG(PT_SOFTE, softe);
#अन्यथा
	CHECK_REG(PT_MQ, mq);
#पूर्ण_अगर
	CHECK_REG(PT_TRAP, trap);
	CHECK_REG(PT_DAR, dar);
	CHECK_REG(PT_DSISR, dsisr);
	CHECK_REG(PT_RESULT, result);
	#अघोषित CHECK_REG

	BUILD_BUG_ON(PT_REGS_COUNT != माप(काष्ठा user_pt_regs) / माप(अचिन्हित दीर्घ));

	/*
	 * PT_DSCR isn't a real reg, but it's important that it doesn't overlap the
	 * real रेजिस्टरs.
	 */
	BUILD_BUG_ON(PT_DSCR < माप(काष्ठा user_pt_regs) / माप(अचिन्हित दीर्घ));
पूर्ण
