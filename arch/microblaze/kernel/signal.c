<शैली गुरु>
/*
 * Signal handling
 *
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2003,2004 John Williams <jwilliams@itee.uq.edu.au>
 * Copyright (C) 2001 NEC Corporation
 * Copyright (C) 2001 Miles Bader <miles@gnu.org>
 * Copyright (C) 1999,2000 Niibe Yutaka & Kaz Kojima
 * Copyright (C) 1991,1992 Linus Torvalds
 *
 * 1997-11-28 Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 *
 * This file was was derived from the sh version, arch/sh/kernel/संकेत.c
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/personality.h>
#समावेश <linux/percpu.h>
#समावेश <linux/linkage.h>
#समावेश <linux/tracehook.h>
#समावेश <यंत्र/entry.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/syscalls.h>

/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 */
काष्ठा sigframe अणु
	काष्ठा sigcontext sc;
	अचिन्हित दीर्घ extramask[_NSIG_WORDS-1];
	अचिन्हित दीर्घ tramp[2];	/* संकेत trampoline */
पूर्ण;

काष्ठा rt_sigframe अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
	अचिन्हित दीर्घ tramp[2];	/* संकेत trampoline */
पूर्ण;

अटल पूर्णांक restore_sigcontext(काष्ठा pt_regs *regs,
				काष्ठा sigcontext __user *sc, पूर्णांक *rval_p)
अणु
	अचिन्हित पूर्णांक err = 0;

#घोषणा COPY(x)		अणुerr |= __get_user(regs->x, &sc->regs.x); पूर्ण
	COPY(r0);
	COPY(r1);
	COPY(r2);	COPY(r3);	COPY(r4);	COPY(r5);
	COPY(r6);	COPY(r7);	COPY(r8);	COPY(r9);
	COPY(r10);	COPY(r11);	COPY(r12);	COPY(r13);
	COPY(r14);	COPY(r15);	COPY(r16);	COPY(r17);
	COPY(r18);	COPY(r19);	COPY(r20);	COPY(r21);
	COPY(r22);	COPY(r23);	COPY(r24);	COPY(r25);
	COPY(r26);	COPY(r27);	COPY(r28);	COPY(r29);
	COPY(r30);	COPY(r31);
	COPY(pc);	COPY(ear);	COPY(esr);	COPY(fsr);
#अघोषित COPY

	*rval_p = regs->r3;

	वापस err;
पूर्ण

यंत्रlinkage दीर्घ sys_rt_sigवापस(काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame =
		(काष्ठा rt_sigframe __user *)(regs->r1);

	sigset_t set;
	पूर्णांक rval;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;

	अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(regs, &frame->uc.uc_mcontext, &rval))
		जाओ badframe;

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस rval;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

/*
 * Set up a संकेत frame.
 */

अटल पूर्णांक
setup_sigcontext(काष्ठा sigcontext __user *sc, काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ mask)
अणु
	पूर्णांक err = 0;

#घोषणा COPY(x)		अणुerr |= __put_user(regs->x, &sc->regs.x); पूर्ण
	COPY(r0);
	COPY(r1);
	COPY(r2);	COPY(r3);	COPY(r4);	COPY(r5);
	COPY(r6);	COPY(r7);	COPY(r8);	COPY(r9);
	COPY(r10);	COPY(r11);	COPY(r12);	COPY(r13);
	COPY(r14);	COPY(r15);	COPY(r16);	COPY(r17);
	COPY(r18);	COPY(r19);	COPY(r20);	COPY(r21);
	COPY(r22);	COPY(r23);	COPY(r24);	COPY(r25);
	COPY(r26);	COPY(r27);	COPY(r28);	COPY(r29);
	COPY(r30);	COPY(r31);
	COPY(pc);	COPY(ear);	COPY(esr);	COPY(fsr);
#अघोषित COPY

	err |= __put_user(mask, &sc->oldmask);

	वापस err;
पूर्ण

/*
 * Determine which stack to use..
 */
अटल अंतरभूत व्योम __user *
get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs, माप_प्रकार frame_size)
अणु
	/* Default to using normal stack */
	अचिन्हित दीर्घ sp = sigsp(regs->r1, ksig);

	वापस (व्योम __user *)((sp - frame_size) & -8UL);
पूर्ण

अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
			  काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;
	पूर्णांक err = 0, sig = ksig->sig;
	अचिन्हित दीर्घ address = 0;
	pmd_t *pmdp;
	pte_t *ptep;

	frame = get_sigframe(ksig, regs, माप(*frame));

	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext. */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(शून्य, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, regs->r1);
	err |= setup_sigcontext(&frame->uc.uc_mcontext,
			regs, set->sig[0]);
	err |= __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));

	/* Set up to वापस from userspace. If provided, use a stub
	 alपढ़ोy in userspace. */
	/* minus 8 is offset to cater क्रम "rtsd r15,8" */
	/* addi r12, r0, __NR_sigवापस */
	err |= __put_user(0x31800000 | __NR_rt_sigवापस ,
			frame->tramp + 0);
	/* brki r14, 0x8 */
	err |= __put_user(0xb9cc0008, frame->tramp + 1);

	/* Return from sighandler will jump to the tramp.
	 Negative 8 offset because वापस is rtsd r15, 8 */
	regs->r15 = ((अचिन्हित दीर्घ)frame->tramp)-8;

	address = ((अचिन्हित दीर्घ)frame->tramp);
	pmdp = pmd_off(current->mm, address);

	preempt_disable();
	ptep = pte_offset_map(pmdp, address);
	अगर (pte_present(*ptep)) अणु
		address = (अचिन्हित दीर्घ) page_address(pte_page(*ptep));
		/* MS: I need add offset in page */
		address += ((अचिन्हित दीर्घ)frame->tramp) & ~PAGE_MASK;
		/* MS address is भव */
		address = __virt_to_phys(address);
		invalidate_icache_range(address, address + 8);
		flush_dcache_range(address, address + 8);
	पूर्ण
	pte_unmap(ptep);
	preempt_enable();
	अगर (err)
		वापस -EFAULT;

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->r1 = (अचिन्हित दीर्घ) frame;

	/* Signal handler args: */
	regs->r5 = sig; /* arg 0: signum */
	regs->r6 = (अचिन्हित दीर्घ) &frame->info; /* arg 1: siginfo */
	regs->r7 = (अचिन्हित दीर्घ) &frame->uc; /* arg2: ucontext */
	/* Offset to handle microblaze rtid r14, 0 */
	regs->pc = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;

#अगर_घोषित DEBUG_SIG
	pr_info("SIG deliver (%s:%d): sp=%p pc=%08lx\n",
		current->comm, current->pid, frame, regs->pc);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Handle restarting प्रणाली calls */
अटल अंतरभूत व्योम
handle_restart(काष्ठा pt_regs *regs, काष्ठा k_sigaction *ka, पूर्णांक has_handler)
अणु
	चयन (regs->r3) अणु
	हाल -ERESTART_RESTARTBLOCK:
	हाल -ERESTARTNOHAND:
		अगर (!has_handler)
			जाओ करो_restart;
		regs->r3 = -EINTR;
		अवरोध;
	हाल -ERESTARTSYS:
		अगर (has_handler && !(ka->sa.sa_flags & SA_RESTART)) अणु
			regs->r3 = -EINTR;
			अवरोध;
	पूर्ण
		fallthrough;
	हाल -ERESTARTNOINTR:
करो_restart:
		/* offset of 4 bytes to re-execute trap (brki) inकाष्ठाion */
		regs->pc -= 4;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * OK, we're invoking a handler
 */

अटल व्योम
handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक ret;

	/* Set up the stack frame */
	ret = setup_rt_frame(ksig, oldset, regs);

	संकेत_setup_करोne(ret, ksig, test_thपढ़ो_flag(TIF_SINGLESTEP));
पूर्ण

/*
 * Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 *
 * Note that we go through the संकेतs twice: once to check the संकेतs that
 * the kernel can handle, and then we build all the user-level संकेत handling
 * stack-frames in one go after that.
 */
अटल व्योम करो_संकेत(काष्ठा pt_regs *regs, पूर्णांक in_syscall)
अणु
	काष्ठा kसंकेत ksig;

#अगर_घोषित DEBUG_SIG
	pr_info("do signal: %p %d\n", regs, in_syscall);
	pr_info("do signal2: %lx %lx %ld [%lx]\n", regs->pc, regs->r1,
			regs->r12, current_thपढ़ो_info()->flags);
#पूर्ण_अगर

	अगर (get_संकेत(&ksig)) अणु
		/* Whee! Actually deliver the संकेत. */
		अगर (in_syscall)
			handle_restart(regs, &ksig.ka, 1);
		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण

	अगर (in_syscall)
		handle_restart(regs, शून्य, 0);

	/*
	 * If there's no संकेत to deliver, we just put the saved sigmask
	 * back.
	 */
	restore_saved_sigmask();
पूर्ण

यंत्रlinkage व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, पूर्णांक in_syscall)
अणु
	अगर (test_thपढ़ो_flag(TIF_SIGPENDING) ||
	    test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs, in_syscall);

	अगर (test_thपढ़ो_flag(TIF_NOTIFY_RESUME))
		tracehook_notअगरy_resume(regs);
पूर्ण
