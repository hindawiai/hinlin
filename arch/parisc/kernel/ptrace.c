<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Kernel support क्रम the ptrace() and syscall tracing पूर्णांकerfaces.
 *
 * Copyright (C) 2000 Hewlett-Packard Co, Linuxcare Inc.
 * Copyright (C) 2000 Matthew Wilcox <matthew@wil.cx>
 * Copyright (C) 2000 David Huggins-Daines <dhd@debian.org>
 * Copyright (C) 2008-2016 Helge Deller <deller@gmx.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/elf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/user.h>
#समावेश <linux/personality.h>
#समावेश <linux/regset.h>
#समावेश <linux/security.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/compat.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/audit.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/यंत्र-offsets.h>

/* PSW bits we allow the debugger to modअगरy */
#घोषणा USER_PSW_BITS	(PSW_N | PSW_B | PSW_V | PSW_CB)

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

/*
 * These are our native regset flavors.
 */
क्रमागत parisc_regset अणु
	REGSET_GENERAL,
	REGSET_FP
पूर्ण;

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure single step bits etc are not set.
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *task)
अणु
	clear_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP);
	clear_tsk_thपढ़ो_flag(task, TIF_BLOCKSTEP);

	/* make sure the trap bits are not set */
	pa_psw(task)->r = 0;
	pa_psw(task)->t = 0;
	pa_psw(task)->h = 0;
	pa_psw(task)->l = 0;
पूर्ण

/*
 * The following functions are called by ptrace_resume() when
 * enabling or disabling single/block tracing.
 */
व्योम user_disable_single_step(काष्ठा task_काष्ठा *task)
अणु
	ptrace_disable(task);
पूर्ण

व्योम user_enable_single_step(काष्ठा task_काष्ठा *task)
अणु
	clear_tsk_thपढ़ो_flag(task, TIF_BLOCKSTEP);
	set_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP);

	अगर (pa_psw(task)->n) अणु
		/* Nullअगरied, just crank over the queue. */
		task_regs(task)->iaoq[0] = task_regs(task)->iaoq[1];
		task_regs(task)->iasq[0] = task_regs(task)->iasq[1];
		task_regs(task)->iaoq[1] = task_regs(task)->iaoq[0] + 4;
		pa_psw(task)->n = 0;
		pa_psw(task)->x = 0;
		pa_psw(task)->y = 0;
		pa_psw(task)->z = 0;
		pa_psw(task)->b = 0;
		ptrace_disable(task);
		/* Don't wake up the task, but let the
		   parent know something happened. */
		क्रमce_sig_fault_to_task(SIGTRAP, TRAP_TRACE,
					(व्योम __user *) (task_regs(task)->iaoq[0] & ~3),
					task);
		/* notअगरy_parent(task, SIGCHLD); */
		वापस;
	पूर्ण

	/* Enable recovery counter traps.  The recovery counter
	 * itself will be set to zero on a task चयन.  If the
	 * task is suspended on a syscall then the syscall वापस
	 * path will overग_लिखो the recovery counter with a suitable
	 * value such that it traps once back in user space.  We
	 * disable पूर्णांकerrupts in the tasks PSW here also, to aव्योम
	 * पूर्णांकerrupts जबतक the recovery counter is decrementing.
	 */
	pa_psw(task)->r = 1;
	pa_psw(task)->t = 0;
	pa_psw(task)->h = 0;
	pa_psw(task)->l = 0;
पूर्ण

व्योम user_enable_block_step(काष्ठा task_काष्ठा *task)
अणु
	clear_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP);
	set_tsk_thपढ़ो_flag(task, TIF_BLOCKSTEP);

	/* Enable taken branch trap. */
	pa_psw(task)->r = 0;
	pa_psw(task)->t = 1;
	pa_psw(task)->h = 0;
	pa_psw(task)->l = 0;
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	अचिन्हित दीर्घ __user *datap = (अचिन्हित दीर्घ __user *)data;
	अचिन्हित दीर्घ पंचांगp;
	दीर्घ ret = -EIO;

	चयन (request) अणु

	/* Read the word at location addr in the USER area.  For ptraced
	   processes, the kernel saves all regs on a syscall. */
	हाल PTRACE_PEEKUSR:
		अगर ((addr & (माप(अचिन्हित दीर्घ)-1)) ||
		     addr >= माप(काष्ठा pt_regs))
			अवरोध;
		पंचांगp = *(अचिन्हित दीर्घ *) ((अक्षर *) task_regs(child) + addr);
		ret = put_user(पंचांगp, datap);
		अवरोध;

	/* Write the word at location addr in the USER area.  This will need
	   to change when the kernel no दीर्घer saves all regs on a syscall.
	   FIXME.  There is a problem at the moment in that r3-r18 are only
	   saved अगर the process is ptraced on syscall entry, and even then
	   those values are overwritten by actual रेजिस्टर values on syscall
	   निकास. */
	हाल PTRACE_POKEUSR:
		/* Some रेजिस्टर values written here may be ignored in
		 * entry.S:syscall_restore_rfi; e.g. iaoq is written with
		 * r31/r31+4, and not with the values in pt_regs.
		 */
		अगर (addr == PT_PSW) अणु
			/* Allow writing to Nullअगरy, Divide-step-correction,
			 * and carry/borrow bits.
			 * BEWARE, अगर you set N, and then single step, it won't
			 * stop on the nullअगरied inकाष्ठाion.
			 */
			data &= USER_PSW_BITS;
			task_regs(child)->gr[0] &= ~USER_PSW_BITS;
			task_regs(child)->gr[0] |= data;
			ret = 0;
			अवरोध;
		पूर्ण

		अगर ((addr & (माप(अचिन्हित दीर्घ)-1)) ||
		     addr >= माप(काष्ठा pt_regs))
			अवरोध;
		अगर (addr == PT_IAOQ0 || addr == PT_IAOQ1) अणु
			data |= 3; /* ensure userspace privilege */
		पूर्ण
		अगर ((addr >= PT_GR1 && addr <= PT_GR31) ||
				addr == PT_IAOQ0 || addr == PT_IAOQ1 ||
				(addr >= PT_FR0 && addr <= PT_FR31 + 4) ||
				addr == PT_SAR) अणु
			*(अचिन्हित दीर्घ *) ((अक्षर *) task_regs(child) + addr) = data;
			ret = 0;
		पूर्ण
		अवरोध;

	हाल PTRACE_GETREGS:	/* Get all gp regs from the child. */
		वापस copy_regset_to_user(child,
					   task_user_regset_view(current),
					   REGSET_GENERAL,
					   0, माप(काष्ठा user_regs_काष्ठा),
					   datap);

	हाल PTRACE_SETREGS:	/* Set all gp regs in the child. */
		वापस copy_regset_from_user(child,
					     task_user_regset_view(current),
					     REGSET_GENERAL,
					     0, माप(काष्ठा user_regs_काष्ठा),
					     datap);

	हाल PTRACE_GETFPREGS:	/* Get the child FPU state. */
		वापस copy_regset_to_user(child,
					   task_user_regset_view(current),
					   REGSET_FP,
					   0, माप(काष्ठा user_fp_काष्ठा),
					   datap);

	हाल PTRACE_SETFPREGS:	/* Set the child FPU state. */
		वापस copy_regset_from_user(child,
					     task_user_regset_view(current),
					     REGSET_FP,
					     0, माप(काष्ठा user_fp_काष्ठा),
					     datap);

	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


#अगर_घोषित CONFIG_COMPAT

/* This function is needed to translate 32 bit pt_regs offsets in to
 * 64 bit pt_regs offsets.  For example, a 32 bit gdb under a 64 bit kernel
 * will request offset 12 अगर it wants gr3, but the lower 32 bits of
 * the 64 bit kernels view of gr3 will be at offset 28 (3*8 + 4).
 * This code relies on a 32 bit pt_regs being comprised of 32 bit values
 * except क्रम the fp रेजिस्टरs which (a) are 64 bits, and (b) follow
 * the gr रेजिस्टरs at the start of pt_regs.  The 32 bit pt_regs should
 * be half the size of the 64 bit pt_regs, plus 32*4 to allow क्रम fr[]
 * being 64 bit in both हालs.
 */

अटल compat_uदीर्घ_t translate_usr_offset(compat_uदीर्घ_t offset)
अणु
	compat_uदीर्घ_t pos;

	अगर (offset < 32*4)	/* gr[0..31] */
		pos = offset * 2 + 4;
	अन्यथा अगर (offset < 32*4+32*8)	/* fr[0] ... fr[31] */
		pos = (offset - 32*4) + PT_FR0;
	अन्यथा अगर (offset < माप(काष्ठा pt_regs)/2 + 32*4) /* sr[0] ... ipsw */
		pos = (offset - 32*4 - 32*8) * 2 + PT_SR0 + 4;
	अन्यथा
		pos = माप(काष्ठा pt_regs);

	वापस pos;
पूर्ण

दीर्घ compat_arch_ptrace(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			compat_uदीर्घ_t addr, compat_uदीर्घ_t data)
अणु
	compat_uपूर्णांक_t पंचांगp;
	दीर्घ ret = -EIO;

	चयन (request) अणु

	हाल PTRACE_PEEKUSR:
		अगर (addr & (माप(compat_uपूर्णांक_t)-1))
			अवरोध;
		addr = translate_usr_offset(addr);
		अगर (addr >= माप(काष्ठा pt_regs))
			अवरोध;

		पंचांगp = *(compat_uपूर्णांक_t *) ((अक्षर *) task_regs(child) + addr);
		ret = put_user(पंचांगp, (compat_uपूर्णांक_t *) (अचिन्हित दीर्घ) data);
		अवरोध;

	/* Write the word at location addr in the USER area.  This will need
	   to change when the kernel no दीर्घer saves all regs on a syscall.
	   FIXME.  There is a problem at the moment in that r3-r18 are only
	   saved अगर the process is ptraced on syscall entry, and even then
	   those values are overwritten by actual रेजिस्टर values on syscall
	   निकास. */
	हाल PTRACE_POKEUSR:
		/* Some रेजिस्टर values written here may be ignored in
		 * entry.S:syscall_restore_rfi; e.g. iaoq is written with
		 * r31/r31+4, and not with the values in pt_regs.
		 */
		अगर (addr == PT_PSW) अणु
			/* Since PT_PSW==0, it is valid क्रम 32 bit processes
			 * under 64 bit kernels as well.
			 */
			ret = arch_ptrace(child, request, addr, data);
		पूर्ण अन्यथा अणु
			अगर (addr & (माप(compat_uपूर्णांक_t)-1))
				अवरोध;
			addr = translate_usr_offset(addr);
			अगर (addr >= माप(काष्ठा pt_regs))
				अवरोध;
			अगर (addr == PT_IAOQ0+4 || addr == PT_IAOQ1+4) अणु
				data |= 3; /* ensure userspace privilege */
			पूर्ण
			अगर (addr >= PT_FR0 && addr <= PT_FR31 + 4) अणु
				/* Special हाल, fp regs are 64 bits anyway */
				*(__u32 *) ((अक्षर *) task_regs(child) + addr) = data;
				ret = 0;
			पूर्ण
			अन्यथा अगर ((addr >= PT_GR1+4 && addr <= PT_GR31+4) ||
					addr == PT_IAOQ0+4 || addr == PT_IAOQ1+4 ||
					addr == PT_SAR+4) अणु
				/* Zero the top 32 bits */
				*(__u32 *) ((अक्षर *) task_regs(child) + addr - 4) = 0;
				*(__u32 *) ((अक्षर *) task_regs(child) + addr) = data;
				ret = 0;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		ret = compat_ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE)) अणु
		पूर्णांक rc = tracehook_report_syscall_entry(regs);

		/*
		 * As tracesys_next करोes not set %r28 to -ENOSYS
		 * when %r20 is set to -1, initialize it here.
		 */
		regs->gr[28] = -ENOSYS;

		अगर (rc) अणु
			/*
			 * A nonzero वापस code from
			 * tracehook_report_syscall_entry() tells us
			 * to prevent the syscall execution.  Skip
			 * the syscall call and the syscall restart handling.
			 *
			 * Note that the tracer may also just change
			 * regs->gr[20] to an invalid syscall number,
			 * that is handled by tracesys_next.
			 */
			regs->gr[20] = -1UL;
			वापस -1;
		पूर्ण
	पूर्ण

	/* Do the secure computing check after ptrace. */
	अगर (secure_computing() == -1)
		वापस -1;

#अगर_घोषित CONFIG_HAVE_SYSCALL_TRACEPOINTS
	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->gr[20]);
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
	अगर (!is_compat_task())
		audit_syscall_entry(regs->gr[20], regs->gr[26], regs->gr[25],
				    regs->gr[24], regs->gr[23]);
	अन्यथा
#पूर्ण_अगर
		audit_syscall_entry(regs->gr[20] & 0xffffffff,
			regs->gr[26] & 0xffffffff,
			regs->gr[25] & 0xffffffff,
			regs->gr[24] & 0xffffffff,
			regs->gr[23] & 0xffffffff);

	/*
	 * Sign extend the syscall number to 64bit since it may have been
	 * modअगरied by a compat ptrace call
	 */
	वापस (पूर्णांक) ((u32) regs->gr[20]);
पूर्ण

व्योम करो_syscall_trace_निकास(काष्ठा pt_regs *regs)
अणु
	पूर्णांक stepping = test_thपढ़ो_flag(TIF_SINGLESTEP) ||
		test_thपढ़ो_flag(TIF_BLOCKSTEP);

	audit_syscall_निकास(regs);

#अगर_घोषित CONFIG_HAVE_SYSCALL_TRACEPOINTS
	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_निकास(regs, regs->gr[20]);
#पूर्ण_अगर

	अगर (stepping || test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, stepping);
पूर्ण


/*
 * regset functions.
 */

अटल पूर्णांक fpr_get(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to)
अणु
	काष्ठा pt_regs *regs = task_regs(target);

	वापस membuf_ग_लिखो(&to, regs->fr, ELF_NFPREG * माप(__u64));
पूर्ण

अटल पूर्णांक fpr_set(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_regs(target);
	स्थिर __u64 *k = kbuf;
	स्थिर __u64 __user *u = ubuf;
	__u64 reg;

	pos /= माप(reg);
	count /= माप(reg);

	अगर (kbuf)
		क्रम (; count > 0 && pos < ELF_NFPREG; --count)
			regs->fr[pos++] = *k++;
	अन्यथा
		क्रम (; count > 0 && pos < ELF_NFPREG; --count) अणु
			अगर (__get_user(reg, u++))
				वापस -EFAULT;
			regs->fr[pos++] = reg;
		पूर्ण

	kbuf = k;
	ubuf = u;
	pos *= माप(reg);
	count *= माप(reg);
	वापस user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					 ELF_NFPREG * माप(reg), -1);
पूर्ण

#घोषणा RI(reg) (दुरत्व(काष्ठा user_regs_काष्ठा,reg) / माप(दीर्घ))

अटल अचिन्हित दीर्घ get_reg(काष्ठा pt_regs *regs, पूर्णांक num)
अणु
	चयन (num) अणु
	हाल RI(gr[0]) ... RI(gr[31]):	वापस regs->gr[num - RI(gr[0])];
	हाल RI(sr[0]) ... RI(sr[7]):	वापस regs->sr[num - RI(sr[0])];
	हाल RI(iasq[0]):		वापस regs->iasq[0];
	हाल RI(iasq[1]):		वापस regs->iasq[1];
	हाल RI(iaoq[0]):		वापस regs->iaoq[0];
	हाल RI(iaoq[1]):		वापस regs->iaoq[1];
	हाल RI(sar):			वापस regs->sar;
	हाल RI(iir):			वापस regs->iir;
	हाल RI(isr):			वापस regs->isr;
	हाल RI(ior):			वापस regs->ior;
	हाल RI(ipsw):			वापस regs->ipsw;
	हाल RI(cr27):			वापस regs->cr27;
	हाल RI(cr0):			वापस mfctl(0);
	हाल RI(cr24):			वापस mfctl(24);
	हाल RI(cr25):			वापस mfctl(25);
	हाल RI(cr26):			वापस mfctl(26);
	हाल RI(cr28):			वापस mfctl(28);
	हाल RI(cr29):			वापस mfctl(29);
	हाल RI(cr30):			वापस mfctl(30);
	हाल RI(cr31):			वापस mfctl(31);
	हाल RI(cr8):			वापस mfctl(8);
	हाल RI(cr9):			वापस mfctl(9);
	हाल RI(cr12):			वापस mfctl(12);
	हाल RI(cr13):			वापस mfctl(13);
	हाल RI(cr10):			वापस mfctl(10);
	हाल RI(cr15):			वापस mfctl(15);
	शेष:			वापस 0;
	पूर्ण
पूर्ण

अटल व्योम set_reg(काष्ठा pt_regs *regs, पूर्णांक num, अचिन्हित दीर्घ val)
अणु
	चयन (num) अणु
	हाल RI(gr[0]): /*
			 * PSW is in gr[0].
			 * Allow writing to Nullअगरy, Divide-step-correction,
			 * and carry/borrow bits.
			 * BEWARE, अगर you set N, and then single step, it won't
			 * stop on the nullअगरied inकाष्ठाion.
			 */
			val &= USER_PSW_BITS;
			regs->gr[0] &= ~USER_PSW_BITS;
			regs->gr[0] |= val;
			वापस;
	हाल RI(gr[1]) ... RI(gr[31]):
			regs->gr[num - RI(gr[0])] = val;
			वापस;
	हाल RI(iaoq[0]):
	हाल RI(iaoq[1]):
			/* set 2 lowest bits to ensure userspace privilege: */
			regs->iaoq[num - RI(iaoq[0])] = val | 3;
			वापस;
	हाल RI(sar):	regs->sar = val;
			वापस;
	शेष:	वापस;
#अगर 0
	/* करो not allow to change any of the following रेजिस्टरs (yet) */
	हाल RI(sr[0]) ... RI(sr[7]):	वापस regs->sr[num - RI(sr[0])];
	हाल RI(iasq[0]):		वापस regs->iasq[0];
	हाल RI(iasq[1]):		वापस regs->iasq[1];
	हाल RI(iir):			वापस regs->iir;
	हाल RI(isr):			वापस regs->isr;
	हाल RI(ior):			वापस regs->ior;
	हाल RI(ipsw):			वापस regs->ipsw;
	हाल RI(cr27):			वापस regs->cr27;
        हाल cr0, cr24, cr25, cr26, cr27, cr28, cr29, cr30, cr31;
        हाल cr8, cr9, cr12, cr13, cr10, cr15;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक gpr_get(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to)
अणु
	काष्ठा pt_regs *regs = task_regs(target);
	अचिन्हित पूर्णांक pos;

	क्रम (pos = 0; pos < ELF_NGREG; pos++)
		membuf_store(&to, get_reg(regs, pos));
	वापस 0;
पूर्ण

अटल पूर्णांक gpr_set(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_regs(target);
	स्थिर अचिन्हित दीर्घ *k = kbuf;
	स्थिर अचिन्हित दीर्घ __user *u = ubuf;
	अचिन्हित दीर्घ reg;

	pos /= माप(reg);
	count /= माप(reg);

	अगर (kbuf)
		क्रम (; count > 0 && pos < ELF_NGREG; --count)
			set_reg(regs, pos++, *k++);
	अन्यथा
		क्रम (; count > 0 && pos < ELF_NGREG; --count) अणु
			अगर (__get_user(reg, u++))
				वापस -EFAULT;
			set_reg(regs, pos++, reg);
		पूर्ण

	kbuf = k;
	ubuf = u;
	pos *= माप(reg);
	count *= माप(reg);
	वापस user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					 ELF_NGREG * माप(reg), -1);
पूर्ण

अटल स्थिर काष्ठा user_regset native_regsets[] = अणु
	[REGSET_GENERAL] = अणु
		.core_note_type = NT_PRSTATUS, .n = ELF_NGREG,
		.size = माप(दीर्घ), .align = माप(दीर्घ),
		.regset_get = gpr_get, .set = gpr_set
	पूर्ण,
	[REGSET_FP] = अणु
		.core_note_type = NT_PRFPREG, .n = ELF_NFPREG,
		.size = माप(__u64), .align = माप(__u64),
		.regset_get = fpr_get, .set = fpr_set
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_parisc_native_view = अणु
	.name = "parisc", .e_machine = ELF_ARCH, .ei_osabi = ELFOSABI_LINUX,
	.regsets = native_regsets, .n = ARRAY_SIZE(native_regsets)
पूर्ण;

#अगर_घोषित CONFIG_64BIT
अटल पूर्णांक gpr32_get(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to)
अणु
	काष्ठा pt_regs *regs = task_regs(target);
	अचिन्हित पूर्णांक pos;

	क्रम (pos = 0; pos < ELF_NGREG; pos++)
		membuf_store(&to, (compat_uदीर्घ_t)get_reg(regs, pos));

	वापस 0;
पूर्ण

अटल पूर्णांक gpr32_set(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_regs(target);
	स्थिर compat_uदीर्घ_t *k = kbuf;
	स्थिर compat_uदीर्घ_t __user *u = ubuf;
	compat_uदीर्घ_t reg;

	pos /= माप(reg);
	count /= माप(reg);

	अगर (kbuf)
		क्रम (; count > 0 && pos < ELF_NGREG; --count)
			set_reg(regs, pos++, *k++);
	अन्यथा
		क्रम (; count > 0 && pos < ELF_NGREG; --count) अणु
			अगर (__get_user(reg, u++))
				वापस -EFAULT;
			set_reg(regs, pos++, reg);
		पूर्ण

	kbuf = k;
	ubuf = u;
	pos *= माप(reg);
	count *= माप(reg);
	वापस user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					 ELF_NGREG * माप(reg), -1);
पूर्ण

/*
 * These are the regset flavors matching the 32bit native set.
 */
अटल स्थिर काष्ठा user_regset compat_regsets[] = अणु
	[REGSET_GENERAL] = अणु
		.core_note_type = NT_PRSTATUS, .n = ELF_NGREG,
		.size = माप(compat_दीर्घ_t), .align = माप(compat_दीर्घ_t),
		.regset_get = gpr32_get, .set = gpr32_set
	पूर्ण,
	[REGSET_FP] = अणु
		.core_note_type = NT_PRFPREG, .n = ELF_NFPREG,
		.size = माप(__u64), .align = माप(__u64),
		.regset_get = fpr_get, .set = fpr_set
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_parisc_compat_view = अणु
	.name = "parisc", .e_machine = EM_PARISC, .ei_osabi = ELFOSABI_LINUX,
	.regsets = compat_regsets, .n = ARRAY_SIZE(compat_regsets)
पूर्ण;
#पूर्ण_अगर	/* CONFIG_64BIT */

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	BUILD_BUG_ON(माप(काष्ठा user_regs_काष्ठा)/माप(दीर्घ) != ELF_NGREG);
	BUILD_BUG_ON(माप(काष्ठा user_fp_काष्ठा)/माप(__u64) != ELF_NFPREG);
#अगर_घोषित CONFIG_64BIT
	अगर (is_compat_task())
		वापस &user_parisc_compat_view;
#पूर्ण_अगर
	वापस &user_parisc_native_view;
पूर्ण


/* HAVE_REGS_AND_STACK_ACCESS_API feature */

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_NAME(r)    अणु.name = #r, .offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
#घोषणा REG_OFFSET_INDEX(r,i) अणु.name = #r#i, .offset = दुरत्व(काष्ठा pt_regs, r[i])पूर्ण
#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण

अटल स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
	REG_OFFSET_INDEX(gr,0),
	REG_OFFSET_INDEX(gr,1),
	REG_OFFSET_INDEX(gr,2),
	REG_OFFSET_INDEX(gr,3),
	REG_OFFSET_INDEX(gr,4),
	REG_OFFSET_INDEX(gr,5),
	REG_OFFSET_INDEX(gr,6),
	REG_OFFSET_INDEX(gr,7),
	REG_OFFSET_INDEX(gr,8),
	REG_OFFSET_INDEX(gr,9),
	REG_OFFSET_INDEX(gr,10),
	REG_OFFSET_INDEX(gr,11),
	REG_OFFSET_INDEX(gr,12),
	REG_OFFSET_INDEX(gr,13),
	REG_OFFSET_INDEX(gr,14),
	REG_OFFSET_INDEX(gr,15),
	REG_OFFSET_INDEX(gr,16),
	REG_OFFSET_INDEX(gr,17),
	REG_OFFSET_INDEX(gr,18),
	REG_OFFSET_INDEX(gr,19),
	REG_OFFSET_INDEX(gr,20),
	REG_OFFSET_INDEX(gr,21),
	REG_OFFSET_INDEX(gr,22),
	REG_OFFSET_INDEX(gr,23),
	REG_OFFSET_INDEX(gr,24),
	REG_OFFSET_INDEX(gr,25),
	REG_OFFSET_INDEX(gr,26),
	REG_OFFSET_INDEX(gr,27),
	REG_OFFSET_INDEX(gr,28),
	REG_OFFSET_INDEX(gr,29),
	REG_OFFSET_INDEX(gr,30),
	REG_OFFSET_INDEX(gr,31),
	REG_OFFSET_INDEX(sr,0),
	REG_OFFSET_INDEX(sr,1),
	REG_OFFSET_INDEX(sr,2),
	REG_OFFSET_INDEX(sr,3),
	REG_OFFSET_INDEX(sr,4),
	REG_OFFSET_INDEX(sr,5),
	REG_OFFSET_INDEX(sr,6),
	REG_OFFSET_INDEX(sr,7),
	REG_OFFSET_INDEX(iasq,0),
	REG_OFFSET_INDEX(iasq,1),
	REG_OFFSET_INDEX(iaoq,0),
	REG_OFFSET_INDEX(iaoq,1),
	REG_OFFSET_NAME(cr27),
	REG_OFFSET_NAME(ksp),
	REG_OFFSET_NAME(kpc),
	REG_OFFSET_NAME(sar),
	REG_OFFSET_NAME(iir),
	REG_OFFSET_NAME(isr),
	REG_OFFSET_NAME(ior),
	REG_OFFSET_NAME(ipsw),
	REG_OFFSET_END,
पूर्ण;

/**
 * regs_query_रेजिस्टर_offset() - query रेजिस्टर offset from its name
 * @name:	the name of a रेजिस्टर
 *
 * regs_query_रेजिस्टर_offset() वापसs the offset of a रेजिस्टर in काष्ठा
 * pt_regs from its name. If the name is invalid, this वापसs -EINVAL;
 */
पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;
	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (!म_भेद(roff->name, name))
			वापस roff->offset;
	वापस -EINVAL;
पूर्ण

/**
 * regs_query_रेजिस्टर_name() - query रेजिस्टर name from its offset
 * @offset:	the offset of a रेजिस्टर in काष्ठा pt_regs.
 *
 * regs_query_रेजिस्टर_name() वापसs the name of a रेजिस्टर from its
 * offset in काष्ठा pt_regs. If the @offset is invalid, this वापसs शून्य;
 */
स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;
	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (roff->offset == offset)
			वापस roff->name;
	वापस शून्य;
पूर्ण

/**
 * regs_within_kernel_stack() - check the address in the stack
 * @regs:      pt_regs which contains kernel stack poपूर्णांकer.
 * @addr:      address which is checked.
 *
 * regs_within_kernel_stack() checks @addr is within the kernel stack page(s).
 * If @addr is within the kernel stack, it वापसs true. If not, वापसs false.
 */
पूर्णांक regs_within_kernel_stack(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	वापस ((addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_poपूर्णांकer(regs) & ~(THREAD_SIZE - 1)));
पूर्ण

/**
 * regs_get_kernel_stack_nth() - get Nth entry of the stack
 * @regs:	pt_regs which contains kernel stack poपूर्णांकer.
 * @n:		stack entry number.
 *
 * regs_get_kernel_stack_nth() वापसs @n th entry of the kernel stack which
 * is specअगरied by @regs. If the @n th entry is NOT in the kernel stack,
 * this वापसs 0.
 */
अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *)kernel_stack_poपूर्णांकer(regs);

	addr -= n;

	अगर (!regs_within_kernel_stack(regs, (अचिन्हित दीर्घ)addr))
		वापस 0;

	वापस *addr;
पूर्ण
