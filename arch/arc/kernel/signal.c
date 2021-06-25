<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Signal Handling क्रम ARC
 *
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: Jan 2010 (Restarting of समयr related syscalls)
 *
 * vineetg: Nov 2009 (Everything needed क्रम TIF_RESTORE_SIGMASK)
 *  -करो_संकेत() supports TIF_RESTORE_SIGMASK
 *  -करो_संकेत() no loner needs oldset, required by OLD sys_संक_रोको
 *  -sys_rt_संक_रोको() now comes from generic code, so discard arch implemen
 *  -sys_संक_रोको() no दीर्घer needs to fudge ptregs, hence that arg हटाओd
 *  -sys_संक_रोको() no दीर्घer loops क्रम करो_संकेत(), sets TIF_xxx and leaves
 *   the job to करो_संकेत()
 *
 * vineetg: July 2009
 *  -Modअगरied Code to support the uClibc provided userland sigवापस stub
 *   to aव्योम kernel synthesing it on user stack at runसमय, costing TLB
 *   probes and Cache line flushes.
 *
 * vineetg: July 2009
 *  -In stash_usr_regs( ) and restore_usr_regs( ), save/restore of user regs
 *   in करोne in block copy rather than one word at a समय.
 *   This saves around 2K of code and improves LMBench lat_sig <catch>
 *
 * rajeshwarr: Feb 2009
 *  - Support क्रम Realसमय Signals
 *
 * vineetg: Aug 11th 2008: Bug #94183
 *  -ViXS were still seeing crashes when using insmod to load drivers.
 *   It turned out that the code to change Execute permssions क्रम TLB entries
 *   of user was not guarded क्रम पूर्णांकerrupts (mod_tlb_permission)
 *   This was causing TLB entries to be overwritten on unrelated indexes
 *
 * Vineetg: July 15th 2008: Bug #94183
 *  -Exception happens in Delay slot of a JMP, and beक्रमe user space resumes,
 *   Signal is delivered (Ctrl + C) = >संक_विघ्न.
 *   setup_frame( ) sets up PC,SP,BLINK to enable user space संकेत handler
 *   to run, but करोesn't clear the Delay slot bit from status32. As a result,
 *   on resuming user mode, संकेत handler branches off to BTA of orig JMP
 *  -FIX: clear the DE bit from status32 in setup_frame( )
 *
 * Rahul Trivedi, Kanika Nema: Codito Technologies 2004
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/personality.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/ucontext.h>

काष्ठा rt_sigframe अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
#घोषणा MAGIC_SIGALTSTK		0x07302004
	अचिन्हित पूर्णांक sigret_magic;
पूर्ण;

अटल पूर्णांक save_arcv2_regs(काष्ठा sigcontext *mctx, काष्ठा pt_regs *regs)
अणु
	पूर्णांक err = 0;
#अगर_अघोषित CONFIG_ISA_ARCOMPACT
	काष्ठा user_regs_arcv2 v2abi;

	v2abi.r30 = regs->r30;
#अगर_घोषित CONFIG_ARC_HAS_ACCL_REGS
	v2abi.r58 = regs->r58;
	v2abi.r59 = regs->r59;
#अन्यथा
	v2abi.r58 = v2abi.r59 = 0;
#पूर्ण_अगर
	err = __copy_to_user(&mctx->v2abi, &v2abi, माप(v2abi));
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल पूर्णांक restore_arcv2_regs(काष्ठा sigcontext *mctx, काष्ठा pt_regs *regs)
अणु
	पूर्णांक err = 0;
#अगर_अघोषित CONFIG_ISA_ARCOMPACT
	काष्ठा user_regs_arcv2 v2abi;

	err = __copy_from_user(&v2abi, &mctx->v2abi, माप(v2abi));

	regs->r30 = v2abi.r30;
#अगर_घोषित CONFIG_ARC_HAS_ACCL_REGS
	regs->r58 = v2abi.r58;
	regs->r59 = v2abi.r59;
#पूर्ण_अगर
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल पूर्णांक
stash_usr_regs(काष्ठा rt_sigframe __user *sf, काष्ठा pt_regs *regs,
	       sigset_t *set)
अणु
	पूर्णांक err;
	काष्ठा user_regs_काष्ठा uregs;

	uregs.scratch.bta	= regs->bta;
	uregs.scratch.lp_start	= regs->lp_start;
	uregs.scratch.lp_end	= regs->lp_end;
	uregs.scratch.lp_count	= regs->lp_count;
	uregs.scratch.status32	= regs->status32;
	uregs.scratch.ret	= regs->ret;
	uregs.scratch.blink	= regs->blink;
	uregs.scratch.fp	= regs->fp;
	uregs.scratch.gp	= regs->r26;
	uregs.scratch.r12	= regs->r12;
	uregs.scratch.r11	= regs->r11;
	uregs.scratch.r10	= regs->r10;
	uregs.scratch.r9	= regs->r9;
	uregs.scratch.r8	= regs->r8;
	uregs.scratch.r7	= regs->r7;
	uregs.scratch.r6	= regs->r6;
	uregs.scratch.r5	= regs->r5;
	uregs.scratch.r4	= regs->r4;
	uregs.scratch.r3	= regs->r3;
	uregs.scratch.r2	= regs->r2;
	uregs.scratch.r1	= regs->r1;
	uregs.scratch.r0	= regs->r0;
	uregs.scratch.sp	= regs->sp;

	err = __copy_to_user(&(sf->uc.uc_mcontext.regs.scratch), &uregs.scratch,
			     माप(sf->uc.uc_mcontext.regs.scratch));

	अगर (is_isa_arcv2())
		err |= save_arcv2_regs(&(sf->uc.uc_mcontext), regs);

	err |= __copy_to_user(&sf->uc.uc_sigmask, set, माप(sigset_t));

	वापस err ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक restore_usr_regs(काष्ठा pt_regs *regs, काष्ठा rt_sigframe __user *sf)
अणु
	sigset_t set;
	पूर्णांक err;
	काष्ठा user_regs_काष्ठा uregs;

	err = __copy_from_user(&set, &sf->uc.uc_sigmask, माप(set));
	err |= __copy_from_user(&uregs.scratch,
				&(sf->uc.uc_mcontext.regs.scratch),
				माप(sf->uc.uc_mcontext.regs.scratch));

	अगर (is_isa_arcv2())
		err |= restore_arcv2_regs(&(sf->uc.uc_mcontext), regs);

	अगर (err)
		वापस -EFAULT;

	set_current_blocked(&set);
	regs->bta	= uregs.scratch.bta;
	regs->lp_start	= uregs.scratch.lp_start;
	regs->lp_end	= uregs.scratch.lp_end;
	regs->lp_count	= uregs.scratch.lp_count;
	regs->status32	= uregs.scratch.status32;
	regs->ret	= uregs.scratch.ret;
	regs->blink	= uregs.scratch.blink;
	regs->fp	= uregs.scratch.fp;
	regs->r26	= uregs.scratch.gp;
	regs->r12	= uregs.scratch.r12;
	regs->r11	= uregs.scratch.r11;
	regs->r10	= uregs.scratch.r10;
	regs->r9	= uregs.scratch.r9;
	regs->r8	= uregs.scratch.r8;
	regs->r7	= uregs.scratch.r7;
	regs->r6	= uregs.scratch.r6;
	regs->r5	= uregs.scratch.r5;
	regs->r4	= uregs.scratch.r4;
	regs->r3	= uregs.scratch.r3;
	regs->r2	= uregs.scratch.r2;
	regs->r1	= uregs.scratch.r1;
	regs->r0	= uregs.scratch.r0;
	regs->sp	= uregs.scratch.sp;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_करो_ss_needed(अचिन्हित पूर्णांक magic)
अणु
	अगर (MAGIC_SIGALTSTK == magic)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा rt_sigframe __user *sf;
	अचिन्हित पूर्णांक magic;
	काष्ठा pt_regs *regs = current_pt_regs();

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/* Since we stacked the संकेत on a word boundary,
	 * then 'sp' should be word aligned here.  If it's
	 * not, then the user is trying to mess with us.
	 */
	अगर (regs->sp & 3)
		जाओ badframe;

	sf = (काष्ठा rt_sigframe __क्रमce __user *)(regs->sp);

	अगर (!access_ok(sf, माप(*sf)))
		जाओ badframe;

	अगर (__get_user(magic, &sf->sigret_magic))
		जाओ badframe;

	अगर (unlikely(is_करो_ss_needed(magic)))
		अगर (restore_altstack(&sf->uc.uc_stack))
			जाओ badframe;

	अगर (restore_usr_regs(regs, sf))
		जाओ badframe;

	/* Don't restart from sigवापस */
	syscall_wont_restart(regs);

	/*
	 * Ensure that sigवापस always वापसs to user mode (in हाल the
	 * regs saved on user stack got fudged between save and sigवापस)
	 * Otherwise it is easy to panic the kernel with a custom
	 * संकेत handler and/or restorer which clobberes the status32/ret
	 * to वापस to a bogus location in kernel mode.
	 */
	regs->status32 |= STATUS_U_MASK;

	वापस regs->r0;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

/*
 * Determine which stack to use..
 */
अटल अंतरभूत व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig,
					काष्ठा pt_regs *regs,
					अचिन्हित दीर्घ framesize)
अणु
	अचिन्हित दीर्घ sp = sigsp(regs->sp, ksig);
	व्योम __user *frame;

	/* No matter what happens, 'sp' must be word
	 * aligned otherwise nasty things could happen
	 */

	/* ATPCS B01 mandates 8-byte alignment */
	frame = (व्योम __user *)((sp - framesize) & ~7);

	/* Check that we can actually ग_लिखो to the संकेत frame */
	अगर (!access_ok(frame, framesize))
		frame = शून्य;

	वापस frame;
पूर्ण

अटल पूर्णांक
setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set, काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *sf;
	अचिन्हित पूर्णांक magic = 0;
	पूर्णांक err = 0;

	sf = get_sigframe(ksig, regs, माप(काष्ठा rt_sigframe));
	अगर (!sf)
		वापस 1;

	/*
	 * w/o SA_SIGINFO, काष्ठा ucontext is partially populated (only
	 * uc_mcontext/uc_sigmask) क्रम kernel's normal user state preservation
	 * during संकेत handler execution. This works क्रम SA_SIGINFO as well
	 * although the semantics are now overloaded (the same reg state can be
	 * inspected by userland: but are they allowed to fiddle with it ?
	 */
	err |= stash_usr_regs(sf, regs, set);

	/*
	 * SA_SIGINFO requires 3 args to संकेत handler:
	 *  #1: sig-no (common to any handler)
	 *  #2: काष्ठा siginfo
	 *  #3: काष्ठा ucontext (completely populated)
	 */
	अगर (unlikely(ksig->ka.sa.sa_flags & SA_SIGINFO)) अणु
		err |= copy_siginfo_to_user(&sf->info, &ksig->info);
		err |= __put_user(0, &sf->uc.uc_flags);
		err |= __put_user(शून्य, &sf->uc.uc_link);
		err |= __save_altstack(&sf->uc.uc_stack, regs->sp);

		/* setup args 2 and 3 क्रम user mode handler */
		regs->r1 = (अचिन्हित दीर्घ)&sf->info;
		regs->r2 = (अचिन्हित दीर्घ)&sf->uc;

		/*
		 * small optim to aव्योम unconditionally calling करो_sigaltstack
		 * in sigवापस path, now that we only have rt_sigवापस
		 */
		magic = MAGIC_SIGALTSTK;
	पूर्ण

	err |= __put_user(magic, &sf->sigret_magic);
	अगर (err)
		वापस err;

	/* #1 arg to the user Signal handler */
	regs->r0 = ksig->sig;

	/* setup PC of user space संकेत handler */
	regs->ret = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;

	/*
	 * handler वापसs using sigवापस stub provided alपढ़ोy by userpsace
	 * If not, nuke the process right away
	 */
	अगर(!(ksig->ka.sa.sa_flags & SA_RESTORER))
		वापस 1;

	regs->blink = (अचिन्हित दीर्घ)ksig->ka.sa.sa_restorer;

	/* User Stack क्रम संकेत handler will be above the frame just carved */
	regs->sp = (अचिन्हित दीर्घ)sf;

	/*
	 * Bug 94183, Clear the DE bit, so that when संकेत handler
	 * starts to run, it करोesn't use BTA
	 */
	regs->status32 &= ~STATUS_DE_MASK;
	regs->status32 |= STATUS_L_MASK;

	वापस err;
पूर्ण

अटल व्योम arc_restart_syscall(काष्ठा k_sigaction *ka, काष्ठा pt_regs *regs)
अणु
	चयन (regs->r0) अणु
	हाल -ERESTART_RESTARTBLOCK:
	हाल -ERESTARTNOHAND:
		/*
		 * ERESTARTNOHAND means that the syscall should
		 * only be restarted अगर there was no handler क्रम
		 * the संकेत, and since we only get here अगर there
		 * is a handler, we करोn't restart
		 */
		regs->r0 = -EINTR;   /* ERESTART_xxx is पूर्णांकernal */
		अवरोध;

	हाल -ERESTARTSYS:
		/*
		 * ERESTARTSYS means to restart the syscall अगर
		 * there is no handler or the handler was
		 * रेजिस्टरed with SA_RESTART
		 */
		अगर (!(ka->sa.sa_flags & SA_RESTART)) अणु
			regs->r0 = -EINTR;
			अवरोध;
		पूर्ण
		fallthrough;

	हाल -ERESTARTNOINTR:
		/*
		 * ERESTARTNOINTR means that the syscall should
		 * be called again after the संकेत handler वापसs.
		 * Setup reg state just as it was beक्रमe करोing the trap
		 * r0 has been clobbered with sys call ret code thus it
		 * needs to be reloaded with orig first arg to syscall
		 * in orig_r0. Rest of relevant reg-file:
		 * r8 (syscall num) and (r1 - r7) will be reset to
		 * their orig user space value when we ret from kernel
		 */
		regs->r0 = regs->orig_r0;
		regs->ret -= is_isa_arcv2() ? 2 : 4;
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
	पूर्णांक failed;

	/* Set up the stack frame */
	failed = setup_rt_frame(ksig, oldset, regs);

	संकेत_setup_करोne(failed, ksig, 0);
पूर्ण

व्योम करो_संकेत(काष्ठा pt_regs *regs)
अणु
	काष्ठा kसंकेत ksig;
	पूर्णांक restart_scall;

	restart_scall = in_syscall(regs) && syscall_restartable(regs);

	अगर (test_thपढ़ो_flag(TIF_SIGPENDING) && get_संकेत(&ksig)) अणु
		अगर (restart_scall) अणु
			arc_restart_syscall(&ksig.ka, regs);
			syscall_wont_restart(regs);	/* No more restarts */
		पूर्ण
		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण

	अगर (restart_scall) अणु
		/* No handler क्रम syscall: restart it */
		अगर (regs->r0 == -ERESTARTNOHAND ||
		    regs->r0 == -ERESTARTSYS || regs->r0 == -ERESTARTNOINTR) अणु
			regs->r0 = regs->orig_r0;
			regs->ret -= is_isa_arcv2() ? 2 : 4;
		पूर्ण अन्यथा अगर (regs->r0 == -ERESTART_RESTARTBLOCK) अणु
			regs->r8 = __NR_restart_syscall;
			regs->ret -= is_isa_arcv2() ? 2 : 4;
		पूर्ण
		syscall_wont_restart(regs);	/* No more restarts */
	पूर्ण

	/* If there's no संकेत to deliver, restore the saved sigmask back */
	restore_saved_sigmask();
पूर्ण

व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs)
अणु
	/*
	 * ASM glue guarantees that this is only called when वापसing to
	 * user mode
	 */
	अगर (test_thपढ़ो_flag(TIF_NOTIFY_RESUME))
		tracehook_notअगरy_resume(regs);
पूर्ण
