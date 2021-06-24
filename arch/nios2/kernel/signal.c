<शैली गुरु>
/*
 * Copyright (C) 2013-2014 Altera Corporation
 * Copyright (C) 2011-2012 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd
 * Copyright (C) 1991, 1992 Linus Torvalds
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/unistd.h>
#समावेश <linux/personality.h>
#समावेश <linux/tracehook.h>

#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/cacheflush.h>

#घोषणा _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))

/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 *
 * Keep the वापस code on the stack quadword aligned!
 * That makes the cache flush below easier.
 */

काष्ठा rt_sigframe अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
पूर्ण;

अटल अंतरभूत पूर्णांक rt_restore_ucontext(काष्ठा pt_regs *regs,
					काष्ठा चयन_stack *sw,
					काष्ठा ucontext *uc, पूर्णांक *pr2)
अणु
	पूर्णांक temp;
	अचिन्हित दीर्घ *gregs = uc->uc_mcontext.gregs;
	पूर्णांक err;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	err = __get_user(temp, &uc->uc_mcontext.version);
	अगर (temp != MCONTEXT_VERSION)
		जाओ badframe;
	/* restore passed रेजिस्टरs */
	err |= __get_user(regs->r1, &gregs[0]);
	err |= __get_user(regs->r2, &gregs[1]);
	err |= __get_user(regs->r3, &gregs[2]);
	err |= __get_user(regs->r4, &gregs[3]);
	err |= __get_user(regs->r5, &gregs[4]);
	err |= __get_user(regs->r6, &gregs[5]);
	err |= __get_user(regs->r7, &gregs[6]);
	err |= __get_user(regs->r8, &gregs[7]);
	err |= __get_user(regs->r9, &gregs[8]);
	err |= __get_user(regs->r10, &gregs[9]);
	err |= __get_user(regs->r11, &gregs[10]);
	err |= __get_user(regs->r12, &gregs[11]);
	err |= __get_user(regs->r13, &gregs[12]);
	err |= __get_user(regs->r14, &gregs[13]);
	err |= __get_user(regs->r15, &gregs[14]);
	err |= __get_user(sw->r16, &gregs[15]);
	err |= __get_user(sw->r17, &gregs[16]);
	err |= __get_user(sw->r18, &gregs[17]);
	err |= __get_user(sw->r19, &gregs[18]);
	err |= __get_user(sw->r20, &gregs[19]);
	err |= __get_user(sw->r21, &gregs[20]);
	err |= __get_user(sw->r22, &gregs[21]);
	err |= __get_user(sw->r23, &gregs[22]);
	/* gregs[23] is handled below */
	err |= __get_user(sw->fp, &gregs[24]);  /* Verअगरy, should this be
							settable */
	err |= __get_user(sw->gp, &gregs[25]);  /* Verअगरy, should this be
							settable */

	err |= __get_user(temp, &gregs[26]);  /* Not really necessary no user
							settable bits */
	err |= __get_user(regs->ea, &gregs[27]);

	err |= __get_user(regs->ra, &gregs[23]);
	err |= __get_user(regs->sp, &gregs[28]);

	regs->orig_r2 = -1;		/* disable syscall checks */

	err |= restore_altstack(&uc->uc_stack);
	अगर (err)
		जाओ badframe;

	*pr2 = regs->r2;
	वापस err;

badframe:
	वापस 1;
पूर्ण

यंत्रlinkage पूर्णांक करो_rt_sigवापस(काष्ठा चयन_stack *sw)
अणु
	काष्ठा pt_regs *regs = (काष्ठा pt_regs *)(sw + 1);
	/* Verअगरy, can we follow the stack back */
	काष्ठा rt_sigframe *frame = (काष्ठा rt_sigframe *) regs->sp;
	sigset_t set;
	पूर्णांक rval;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;

	अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (rt_restore_ucontext(regs, sw, &frame->uc, &rval))
		जाओ badframe;

	वापस rval;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rt_setup_ucontext(काष्ठा ucontext *uc, काष्ठा pt_regs *regs)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *)regs - 1;
	अचिन्हित दीर्घ *gregs = uc->uc_mcontext.gregs;
	पूर्णांक err = 0;

	err |= __put_user(MCONTEXT_VERSION, &uc->uc_mcontext.version);
	err |= __put_user(regs->r1, &gregs[0]);
	err |= __put_user(regs->r2, &gregs[1]);
	err |= __put_user(regs->r3, &gregs[2]);
	err |= __put_user(regs->r4, &gregs[3]);
	err |= __put_user(regs->r5, &gregs[4]);
	err |= __put_user(regs->r6, &gregs[5]);
	err |= __put_user(regs->r7, &gregs[6]);
	err |= __put_user(regs->r8, &gregs[7]);
	err |= __put_user(regs->r9, &gregs[8]);
	err |= __put_user(regs->r10, &gregs[9]);
	err |= __put_user(regs->r11, &gregs[10]);
	err |= __put_user(regs->r12, &gregs[11]);
	err |= __put_user(regs->r13, &gregs[12]);
	err |= __put_user(regs->r14, &gregs[13]);
	err |= __put_user(regs->r15, &gregs[14]);
	err |= __put_user(sw->r16, &gregs[15]);
	err |= __put_user(sw->r17, &gregs[16]);
	err |= __put_user(sw->r18, &gregs[17]);
	err |= __put_user(sw->r19, &gregs[18]);
	err |= __put_user(sw->r20, &gregs[19]);
	err |= __put_user(sw->r21, &gregs[20]);
	err |= __put_user(sw->r22, &gregs[21]);
	err |= __put_user(sw->r23, &gregs[22]);
	err |= __put_user(regs->ra, &gregs[23]);
	err |= __put_user(sw->fp, &gregs[24]);
	err |= __put_user(sw->gp, &gregs[25]);
	err |= __put_user(regs->ea, &gregs[27]);
	err |= __put_user(regs->sp, &gregs[28]);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs,
				 माप_प्रकार frame_size)
अणु
	अचिन्हित दीर्घ usp;

	/* Default to using normal stack.  */
	usp = regs->sp;

	/* This is the X/Open sanctioned संकेत stack चयनing.  */
	usp = sigsp(usp, ksig);

	/* Verअगरy, is it 32 or 64 bit aligned */
	वापस (व्योम *)((usp - frame_size) & -8UL);
पूर्ण

अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
			  काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe *frame;
	पूर्णांक err = 0;

	frame = get_sigframe(ksig, regs, माप(*frame));

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext.  */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(0, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, regs->sp);
	err |= rt_setup_ucontext(&frame->uc, regs);
	err |= copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));

	अगर (err)
		जाओ give_sigsegv;

	/* Set up to वापस from userspace; jump to fixed address sigवापस
	   trampoline on kuser page.  */
	regs->ra = (अचिन्हित दीर्घ) (0x1044);

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->sp = (अचिन्हित दीर्घ) frame;
	regs->r4 = (अचिन्हित दीर्घ) ksig->sig;
	regs->r5 = (अचिन्हित दीर्घ) &frame->info;
	regs->r6 = (अचिन्हित दीर्घ) &frame->uc;
	regs->ea = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	वापस 0;

give_sigsegv:
	क्रमce_sigsegv(ksig->sig);
	वापस -EFAULT;
पूर्ण

/*
 * OK, we're invoking a handler
 */
अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;
	sigset_t *oldset = sigmask_to_save();

	/* set up the stack frame */
	ret = setup_rt_frame(ksig, oldset, regs);

	संकेत_setup_करोne(ret, ksig, 0);
पूर्ण

अटल पूर्णांक करो_संकेत(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक retval = 0, जारी_addr = 0, restart_addr = 0;
	पूर्णांक restart = 0;
	काष्ठा kसंकेत ksig;

	current->thपढ़ो.kregs = regs;

	/*
	 * If we were from a प्रणाली call, check क्रम प्रणाली call restarting...
	 */
	अगर (regs->orig_r2 >= 0) अणु
		जारी_addr = regs->ea;
		restart_addr = जारी_addr - 4;
		retval = regs->r2;

		/*
		 * Prepare क्रम प्रणाली call restart. We करो this here so that a
		 * debugger will see the alपढ़ोy changed PC.
		 */
		चयन (retval) अणु
		हाल ERESTART_RESTARTBLOCK:
			restart = -2;
			fallthrough;
		हाल ERESTARTNOHAND:
		हाल ERESTARTSYS:
		हाल ERESTARTNOINTR:
			restart++;
			regs->r2 = regs->orig_r2;
			regs->r7 = regs->orig_r7;
			regs->ea = restart_addr;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (get_संकेत(&ksig)) अणु
		/* handler */
		अगर (unlikely(restart && regs->ea == restart_addr)) अणु
			अगर (retval == ERESTARTNOHAND ||
			    retval == ERESTART_RESTARTBLOCK ||
			     (retval == ERESTARTSYS
				&& !(ksig.ka.sa.sa_flags & SA_RESTART))) अणु
				regs->r2 = EINTR;
				regs->r7 = 1;
				regs->ea = जारी_addr;
			पूर्ण
		पूर्ण
		handle_संकेत(&ksig, regs);
		वापस 0;
	पूर्ण

	/*
	 * No handler present
	 */
	अगर (unlikely(restart) && regs->ea == restart_addr) अणु
		regs->ea = जारी_addr;
		regs->r2 = __NR_restart_syscall;
	पूर्ण

	/*
	* If there's no संकेत to deliver, we just put the saved sigmask back.
	*/
	restore_saved_sigmask();

	वापस restart;
पूर्ण

यंत्रlinkage पूर्णांक करो_notअगरy_resume(काष्ठा pt_regs *regs)
अणु
	/*
	 * We want the common हाल to go fast, which is why we may in certain
	 * हालs get here from kernel mode. Just वापस without करोing anything
	 * अगर so.
	 */
	अगर (!user_mode(regs))
		वापस 0;

	अगर (test_thपढ़ो_flag(TIF_SIGPENDING) ||
	    test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL)) अणु
		पूर्णांक restart = करो_संकेत(regs);

		अगर (unlikely(restart)) अणु
			/*
			 * Restart without handlers.
			 * Deal with it without leaving
			 * the kernel space.
			 */
			वापस restart;
		पूर्ण
	पूर्ण अन्यथा अगर (test_thपढ़ो_flag(TIF_NOTIFY_RESUME))
		tracehook_notअगरy_resume(regs);

	वापस 0;
पूर्ण
