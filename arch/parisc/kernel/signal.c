<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/parisc/kernel/संकेत.c: Architecture-specअगरic संकेत
 *  handling support.
 *
 *  Copyright (C) 2000 David Huggins-Daines <dhd@debian.org>
 *  Copyright (C) 2000 Linuxcare, Inc.
 *
 *  Based on the ia64, i386, and alpha versions.
 *
 *  Like the IA-64, we are a recent enough port (we are *starting*
 *  with glibc2.2) that we करो not need to support the old non-realसमय
 *  Linux संकेतs.  Thereक्रमe we करोn't.
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/compat.h>
#समावेश <linux/elf.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/rt_sigframe.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/यंत्र-offsets.h>

#अगर_घोषित CONFIG_COMPAT
#समावेश "signal32.h"
#पूर्ण_अगर

#घोषणा DEBUG_SIG 0 
#घोषणा DEBUG_SIG_LEVEL 2

#अगर DEBUG_SIG
#घोषणा DBG(LEVEL, ...) \
        ((DEBUG_SIG_LEVEL >= LEVEL) \
	? prपूर्णांकk(__VA_ARGS__) : (व्योम) 0)
#अन्यथा
#घोषणा DBG(LEVEL, ...)
#पूर्ण_अगर
	
/* gcc will complain अगर a poपूर्णांकer is cast to an पूर्णांकeger of dअगरferent
 * size.  If you really need to करो this (and we करो क्रम an ELF32 user
 * application in an ELF64 kernel) then you have to करो a cast to an
 * पूर्णांकeger of the same size first.  The A() macro accomplishes
 * this. */
#घोषणा A(__x)	((अचिन्हित दीर्घ)(__x))

/*
 * Do a संकेत वापस - restore sigcontext.
 */

/* Trampoline क्रम calling rt_sigवापस() */
#घोषणा INSN_LDI_R25_0	 0x34190000 /* ldi  0,%r25 (in_syscall=0) */
#घोषणा INSN_LDI_R25_1	 0x34190002 /* ldi  1,%r25 (in_syscall=1) */
#घोषणा INSN_LDI_R20	 0x3414015a /* ldi  __NR_rt_sigवापस,%r20 */
#घोषणा INSN_BLE_SR2_R0  0xe4008200 /* be,l 0x100(%sr2,%r0),%sr0,%r31 */
/* For debugging */
#घोषणा INSN_DIE_HORRIBLY 0x68000ccc /* stw %r0,0x666(%sr0,%r0) */

अटल दीर्घ
restore_sigcontext(काष्ठा sigcontext __user *sc, काष्ठा pt_regs *regs)
अणु
	दीर्घ err = 0;

	err |= __copy_from_user(regs->gr, sc->sc_gr, माप(regs->gr));
	err |= __copy_from_user(regs->fr, sc->sc_fr, माप(regs->fr));
	err |= __copy_from_user(regs->iaoq, sc->sc_iaoq, माप(regs->iaoq));
	err |= __copy_from_user(regs->iasq, sc->sc_iasq, माप(regs->iasq));
	err |= __get_user(regs->sar, &sc->sc_sar);
	DBG(2,"restore_sigcontext: iaoq is %#lx / %#lx\n",
			regs->iaoq[0],regs->iaoq[1]);
	DBG(2,"restore_sigcontext: r28 is %ld\n", regs->gr[28]);
	वापस err;
पूर्ण

व्योम
sys_rt_sigवापस(काष्ठा pt_regs *regs, पूर्णांक in_syscall)
अणु
	काष्ठा rt_sigframe __user *frame;
	sigset_t set;
	अचिन्हित दीर्घ usp = (regs->gr[30] & ~(0x01UL));
	अचिन्हित दीर्घ sigframe_size = PARISC_RT_SIGFRAME_SIZE;
#अगर_घोषित CONFIG_64BIT
	काष्ठा compat_rt_sigframe __user * compat_frame;
	
	अगर (is_compat_task())
		sigframe_size = PARISC_RT_SIGFRAME_SIZE32;
#पूर्ण_अगर

	current->restart_block.fn = करो_no_restart_syscall;

	/* Unwind the user stack to get the rt_sigframe काष्ठाure. */
	frame = (काष्ठा rt_sigframe __user *)
		(usp - sigframe_size);
	DBG(2,"sys_rt_sigreturn: frame is %p\n", frame);

	regs->orig_r28 = 1; /* no restarts क्रम sigवापस */

#अगर_घोषित CONFIG_64BIT
	compat_frame = (काष्ठा compat_rt_sigframe __user *)frame;
	
	अगर (is_compat_task()) अणु
		DBG(2,"sys_rt_sigreturn: ELF32 process.\n");
		अगर (get_compat_sigset(&set, &compat_frame->uc.uc_sigmask))
			जाओ give_sigsegv;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
			जाओ give_sigsegv;
	पूर्ण
		
	set_current_blocked(&set);

	/* Good thing we saved the old gr[30], eh? */
#अगर_घोषित CONFIG_64BIT
	अगर (is_compat_task()) अणु
		DBG(1,"sys_rt_sigreturn: compat_frame->uc.uc_mcontext 0x%p\n",
				&compat_frame->uc.uc_mcontext);
// FIXME: Load upper half from रेजिस्टर file
		अगर (restore_sigcontext32(&compat_frame->uc.uc_mcontext, 
					&compat_frame->regs, regs))
			जाओ give_sigsegv;
		DBG(1,"sys_rt_sigreturn: usp %#08lx stack 0x%p\n", 
				usp, &compat_frame->uc.uc_stack);
		अगर (compat_restore_altstack(&compat_frame->uc.uc_stack))
			जाओ give_sigsegv;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		DBG(1,"sys_rt_sigreturn: frame->uc.uc_mcontext 0x%p\n",
				&frame->uc.uc_mcontext);
		अगर (restore_sigcontext(&frame->uc.uc_mcontext, regs))
			जाओ give_sigsegv;
		DBG(1,"sys_rt_sigreturn: usp %#08lx stack 0x%p\n", 
				usp, &frame->uc.uc_stack);
		अगर (restore_altstack(&frame->uc.uc_stack))
			जाओ give_sigsegv;
	पूर्ण
		


	/* If we are on the syscall path IAOQ will not be restored, and
	 * अगर we are on the पूर्णांकerrupt path we must not corrupt gr31.
	 */
	अगर (in_syscall)
		regs->gr[31] = regs->iaoq[0];
#अगर DEBUG_SIG
	DBG(1,"sys_rt_sigreturn: returning to %#lx, DUMPING REGS:\n", regs->iaoq[0]);
	show_regs(regs);
#पूर्ण_अगर
	वापस;

give_sigsegv:
	DBG(1,"sys_rt_sigreturn: Sending SIGSEGV\n");
	क्रमce_sig(संक_अंश);
	वापस;
पूर्ण

/*
 * Set up a संकेत frame.
 */

अटल अंतरभूत व्योम __user *
get_sigframe(काष्ठा k_sigaction *ka, अचिन्हित दीर्घ sp, माप_प्रकार frame_size)
अणु
	/*FIXME: ELF32 vs. ELF64 has dअगरferent frame_size, but since we
	  करोn't use the parameter it doesn't matter */

	DBG(1,"get_sigframe: ka = %#lx, sp = %#lx, frame_size = %#lx\n",
			(अचिन्हित दीर्घ)ka, sp, frame_size);
	
	/* Align alternate stack and reserve 64 bytes क्रम the संकेत
	   handler's frame marker.  */
	अगर ((ka->sa.sa_flags & SA_ONSTACK) != 0 && ! sas_ss_flags(sp))
		sp = (current->sas_ss_sp + 0x7f) & ~0x3f; /* Stacks grow up! */

	DBG(1,"get_sigframe: Returning sp = %#lx\n", (अचिन्हित दीर्घ)sp);
	वापस (व्योम __user *) sp; /* Stacks grow up.  Fun. */
पूर्ण

अटल दीर्घ
setup_sigcontext(काष्ठा sigcontext __user *sc, काष्ठा pt_regs *regs, पूर्णांक in_syscall)
		 
अणु
	अचिन्हित दीर्घ flags = 0;
	दीर्घ err = 0;

	अगर (on_sig_stack((अचिन्हित दीर्घ) sc))
		flags |= PARISC_SC_FLAG_ONSTACK;
	अगर (in_syscall) अणु
		flags |= PARISC_SC_FLAG_IN_SYSCALL;
		/* regs->iaoq is undefined in the syscall वापस path */
		err |= __put_user(regs->gr[31], &sc->sc_iaoq[0]);
		err |= __put_user(regs->gr[31]+4, &sc->sc_iaoq[1]);
		err |= __put_user(regs->sr[3], &sc->sc_iasq[0]);
		err |= __put_user(regs->sr[3], &sc->sc_iasq[1]);
		DBG(1,"setup_sigcontext: iaoq %#lx / %#lx (in syscall)\n",
			regs->gr[31], regs->gr[31]+4);
	पूर्ण अन्यथा अणु
		err |= __copy_to_user(sc->sc_iaoq, regs->iaoq, माप(regs->iaoq));
		err |= __copy_to_user(sc->sc_iasq, regs->iasq, माप(regs->iasq));
		DBG(1,"setup_sigcontext: iaoq %#lx / %#lx (not in syscall)\n", 
			regs->iaoq[0], regs->iaoq[1]);
	पूर्ण

	err |= __put_user(flags, &sc->sc_flags);
	err |= __copy_to_user(sc->sc_gr, regs->gr, माप(regs->gr));
	err |= __copy_to_user(sc->sc_fr, regs->fr, माप(regs->fr));
	err |= __put_user(regs->sar, &sc->sc_sar);
	DBG(1,"setup_sigcontext: r28 is %ld\n", regs->gr[28]);

	वापस err;
पूर्ण

अटल दीर्घ
setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set, काष्ठा pt_regs *regs,
	       पूर्णांक in_syscall)
अणु
	काष्ठा rt_sigframe __user *frame;
	अचिन्हित दीर्घ rp, usp;
	अचिन्हित दीर्घ haddr, sigframe_size;
	अचिन्हित दीर्घ start, end;
	पूर्णांक err = 0;
#अगर_घोषित CONFIG_64BIT
	काष्ठा compat_rt_sigframe __user * compat_frame;
#पूर्ण_अगर
	
	usp = (regs->gr[30] & ~(0x01UL));
	/*FIXME: frame_size parameter is unused, हटाओ it. */
	frame = get_sigframe(&ksig->ka, usp, माप(*frame));

	DBG(1,"SETUP_RT_FRAME: START\n");
	DBG(1,"setup_rt_frame: frame %p info %p\n", frame, ksig->info);

	
#अगर_घोषित CONFIG_64BIT

	compat_frame = (काष्ठा compat_rt_sigframe __user *)frame;
	
	अगर (is_compat_task()) अणु
		DBG(1,"setup_rt_frame: frame->info = 0x%p\n", &compat_frame->info);
		err |= copy_siginfo_to_user32(&compat_frame->info, &ksig->info);
		err |= __compat_save_altstack( &compat_frame->uc.uc_stack, regs->gr[30]);
		DBG(1,"setup_rt_frame: frame->uc = 0x%p\n", &compat_frame->uc);
		DBG(1,"setup_rt_frame: frame->uc.uc_mcontext = 0x%p\n", &compat_frame->uc.uc_mcontext);
		err |= setup_sigcontext32(&compat_frame->uc.uc_mcontext, 
					&compat_frame->regs, regs, in_syscall);
		err |= put_compat_sigset(&compat_frame->uc.uc_sigmask, set,
					 माप(compat_sigset_t));
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु	
		DBG(1,"setup_rt_frame: frame->info = 0x%p\n", &frame->info);
		err |= copy_siginfo_to_user(&frame->info, &ksig->info);
		err |= __save_altstack(&frame->uc.uc_stack, regs->gr[30]);
		DBG(1,"setup_rt_frame: frame->uc = 0x%p\n", &frame->uc);
		DBG(1,"setup_rt_frame: frame->uc.uc_mcontext = 0x%p\n", &frame->uc.uc_mcontext);
		err |= setup_sigcontext(&frame->uc.uc_mcontext, regs, in_syscall);
		/* FIXME: Should probably be converted as well क्रम the compat हाल */
		err |= __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));
	पूर्ण
	
	अगर (err)
		वापस -EFAULT;

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace. The first words of tramp are used to
	   save the previous sigrestartblock trampoline that might be
	   on the stack. We start the sigवापस trampoline at 
	   SIGRESTARTBLOCK_TRAMP+X. */
	err |= __put_user(in_syscall ? INSN_LDI_R25_1 : INSN_LDI_R25_0,
			&frame->tramp[SIGRESTARTBLOCK_TRAMP+0]);
	err |= __put_user(INSN_LDI_R20, 
			&frame->tramp[SIGRESTARTBLOCK_TRAMP+1]);
	err |= __put_user(INSN_BLE_SR2_R0, 
			&frame->tramp[SIGRESTARTBLOCK_TRAMP+2]);
	err |= __put_user(INSN_NOP, &frame->tramp[SIGRESTARTBLOCK_TRAMP+3]);

#अगर DEBUG_SIG
	/* Assert that we're flushing in the correct space... */
	अणु
		अचिन्हित दीर्घ sid;
		यंत्र ("mfsp %%sr3,%0" : "=r" (sid));
		DBG(1,"setup_rt_frame: Flushing 64 bytes at space %#x offset %p\n",
		       sid, frame->tramp);
	पूर्ण
#पूर्ण_अगर

	start = (अचिन्हित दीर्घ) &frame->tramp[0];
	end = (अचिन्हित दीर्घ) &frame->tramp[TRAMP_SIZE];
	flush_user_dcache_range_यंत्र(start, end);
	flush_user_icache_range_यंत्र(start, end);

	/* TRAMP Words 0-4, Length 5 = SIGRESTARTBLOCK_TRAMP
	 * TRAMP Words 5-9, Length 4 = SIGRETURN_TRAMP
	 * So the SIGRETURN_TRAMP is at the end of SIGRESTARTBLOCK_TRAMP
	 */
	rp = (अचिन्हित दीर्घ) &frame->tramp[SIGRESTARTBLOCK_TRAMP];

	अगर (err)
		वापस -EFAULT;

	haddr = A(ksig->ka.sa.sa_handler);
	/* The sa_handler may be a poपूर्णांकer to a function descriptor */
#अगर_घोषित CONFIG_64BIT
	अगर (is_compat_task()) अणु
#पूर्ण_अगर
		अगर (haddr & PA_PLABEL_FDESC) अणु
			Elf32_Fdesc fdesc;
			Elf32_Fdesc __user *ufdesc = (Elf32_Fdesc __user *)A(haddr & ~3);

			err = __copy_from_user(&fdesc, ufdesc, माप(fdesc));

			अगर (err)
				वापस -EFAULT;

			haddr = fdesc.addr;
			regs->gr[19] = fdesc.gp;
		पूर्ण
#अगर_घोषित CONFIG_64BIT
	पूर्ण अन्यथा अणु
		Elf64_Fdesc fdesc;
		Elf64_Fdesc __user *ufdesc = (Elf64_Fdesc __user *)A(haddr & ~3);
		
		err = __copy_from_user(&fdesc, ufdesc, माप(fdesc));
		
		अगर (err)
			वापस -EFAULT;
		
		haddr = fdesc.addr;
		regs->gr[19] = fdesc.gp;
		DBG(1,"setup_rt_frame: 64 bit signal, exe=%#lx, r19=%#lx, in_syscall=%d\n",
		     haddr, regs->gr[19], in_syscall);
	पूर्ण
#पूर्ण_अगर

	/* The syscall वापस path will create IAOQ values from r31.
	 */
	sigframe_size = PARISC_RT_SIGFRAME_SIZE;
#अगर_घोषित CONFIG_64BIT
	अगर (is_compat_task())
		sigframe_size = PARISC_RT_SIGFRAME_SIZE32;
#पूर्ण_अगर
	अगर (in_syscall) अणु
		regs->gr[31] = haddr;
#अगर_घोषित CONFIG_64BIT
		अगर (!test_thपढ़ो_flag(TIF_32BIT))
			sigframe_size |= 1;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ psw = USER_PSW;
#अगर_घोषित CONFIG_64BIT
		अगर (!test_thपढ़ो_flag(TIF_32BIT))
			psw |= PSW_W;
#पूर्ण_अगर

		/* If we are singlestepping, arrange a trap to be delivered
		   when we वापस to userspace. Note the semantics -- we
		   should trap beक्रमe the first insn in the handler is
		   executed. Ref:
			http://sources.redhat.com/ml/gdb/2004-11/msg00245.hपंचांगl
		 */
		अगर (pa_psw(current)->r) अणु
			pa_psw(current)->r = 0;
			psw |= PSW_R;
			mtctl(-1, 0);
		पूर्ण

		regs->gr[0] = psw;
		regs->iaoq[0] = haddr | 3;
		regs->iaoq[1] = regs->iaoq[0] + 4;
	पूर्ण

	regs->gr[2]  = rp;                /* userland वापस poपूर्णांकer */
	regs->gr[26] = ksig->sig;               /* संकेत number */
	
#अगर_घोषित CONFIG_64BIT
	अगर (is_compat_task()) अणु
		regs->gr[25] = A(&compat_frame->info); /* siginfo poपूर्णांकer */
		regs->gr[24] = A(&compat_frame->uc);   /* ucontext poपूर्णांकer */
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु		
		regs->gr[25] = A(&frame->info); /* siginfo poपूर्णांकer */
		regs->gr[24] = A(&frame->uc);   /* ucontext poपूर्णांकer */
	पूर्ण
	
	DBG(1,"setup_rt_frame: making sigreturn frame: %#lx + %#lx = %#lx\n",
	       regs->gr[30], sigframe_size,
	       regs->gr[30] + sigframe_size);
	/* Raise the user stack poपूर्णांकer to make a proper call frame. */
	regs->gr[30] = (A(frame) + sigframe_size);


	DBG(1,"setup_rt_frame: sig deliver (%s,%d) frame=0x%p sp=%#lx iaoq=%#lx/%#lx rp=%#lx\n",
	       current->comm, current->pid, frame, regs->gr[30],
	       regs->iaoq[0], regs->iaoq[1], rp);

	वापस 0;
पूर्ण

/*
 * OK, we're invoking a handler.
 */	

अटल व्योम
handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs, पूर्णांक in_syscall)
अणु
	पूर्णांक ret;
	sigset_t *oldset = sigmask_to_save();

	DBG(1,"handle_signal: sig=%ld, ka=%p, info=%p, oldset=%p, regs=%p\n",
	       ksig->sig, ksig->ka, ksig->info, oldset, regs);
	
	/* Set up the stack frame */
	ret = setup_rt_frame(ksig, oldset, regs, in_syscall);

	संकेत_setup_करोne(ret, ksig, test_thपढ़ो_flag(TIF_SINGLESTEP) ||
			  test_thपढ़ो_flag(TIF_BLOCKSTEP));

	DBG(1,KERN_DEBUG "do_signal: Exit (success), regs->gr[28] = %ld\n",
		regs->gr[28]);
पूर्ण

/*
 * Check how the syscall number माला_लो loaded पूर्णांकo %r20 within
 * the delay branch in userspace and adjust as needed.
 */

अटल व्योम check_syscallno_in_delay_branch(काष्ठा pt_regs *regs)
अणु
	u32 opcode, source_reg;
	u32 __user *uaddr;
	पूर्णांक err;

	/* Usually we करोn't have to restore %r20 (the प्रणाली call number)
	 * because it माला_लो loaded in the delay slot of the branch बाह्यal
	 * inकाष्ठाion via the ldi inकाष्ठाion.
	 * In some हालs a रेजिस्टर-to-रेजिस्टर copy inकाष्ठाion might have
	 * been used instead, in which हाल we need to copy the syscall
	 * number पूर्णांकo the source रेजिस्टर beक्रमe वापसing to userspace.
	 */

	/* A syscall is just a branch, so all we have to करो is fiddle the
	 * वापस poपूर्णांकer so that the ble inकाष्ठाion माला_लो executed again.
	 */
	regs->gr[31] -= 8; /* delayed branching */

	/* Get assembler opcode of code in delay branch */
	uaddr = (अचिन्हित पूर्णांक *) ((regs->gr[31] & ~3) + 4);
	err = get_user(opcode, uaddr);
	अगर (err)
		वापस;

	/* Check अगर delay branch uses "ldi int,%r20" */
	अगर ((opcode & 0xffff0000) == 0x34140000)
		वापस;	/* everything ok, just वापस */

	/* Check अगर delay branch uses "nop" */
	अगर (opcode == INSN_NOP)
		वापस;

	/* Check अगर delay branch uses "copy %rX,%r20" */
	अगर ((opcode & 0xffe0ffff) == 0x08000254) अणु
		source_reg = (opcode >> 16) & 31;
		regs->gr[source_reg] = regs->gr[20];
		वापस;
	पूर्ण

	pr_warn("syscall restart: %s (pid %d): unexpected opcode 0x%08x\n",
		current->comm, task_pid_nr(current), opcode);
पूर्ण

अटल अंतरभूत व्योम
syscall_restart(काष्ठा pt_regs *regs, काष्ठा k_sigaction *ka)
अणु
	अगर (regs->orig_r28)
		वापस;
	regs->orig_r28 = 1; /* no more restarts */
	/* Check the वापस code */
	चयन (regs->gr[28]) अणु
	हाल -ERESTART_RESTARTBLOCK:
	हाल -ERESTARTNOHAND:
		DBG(1,"ERESTARTNOHAND: returning -EINTR\n");
		regs->gr[28] = -EINTR;
		अवरोध;

	हाल -ERESTARTSYS:
		अगर (!(ka->sa.sa_flags & SA_RESTART)) अणु
			DBG(1,"ERESTARTSYS: putting -EINTR\n");
			regs->gr[28] = -EINTR;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल -ERESTARTNOINTR:
		check_syscallno_in_delay_branch(regs);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
insert_restart_trampoline(काष्ठा pt_regs *regs)
अणु
	अगर (regs->orig_r28)
		वापस;
	regs->orig_r28 = 1; /* no more restarts */
	चयन(regs->gr[28]) अणु
	हाल -ERESTART_RESTARTBLOCK: अणु
		/* Restart the प्रणाली call - no handlers present */
		अचिन्हित पूर्णांक *usp = (अचिन्हित पूर्णांक *)regs->gr[30];
		अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) &usp[2];
		अचिन्हित दीर्घ end  = (अचिन्हित दीर्घ) &usp[5];
		दीर्घ err = 0;

		/* Setup a trampoline to restart the syscall
		 * with __NR_restart_syscall
		 *
		 *  0: <वापस address (orig r31)>
		 *  4: <2nd half क्रम 64-bit>
		 *  8: ldw 0(%sp), %r31
		 * 12: be 0x100(%sr2, %r0)
		 * 16: ldi __NR_restart_syscall, %r20
		 */
#अगर_घोषित CONFIG_64BIT
		err |= put_user(regs->gr[31] >> 32, &usp[0]);
		err |= put_user(regs->gr[31] & 0xffffffff, &usp[1]);
		err |= put_user(0x0fc010df, &usp[2]);
#अन्यथा
		err |= put_user(regs->gr[31], &usp[0]);
		err |= put_user(0x0fc0109f, &usp[2]);
#पूर्ण_अगर
		err |= put_user(0xe0008200, &usp[3]);
		err |= put_user(0x34140000, &usp[4]);

		WARN_ON(err);

		/* flush data/inकाष्ठाion cache क्रम new insns */
		flush_user_dcache_range_यंत्र(start, end);
		flush_user_icache_range_यंत्र(start, end);

		regs->gr[31] = regs->gr[30] + 8;
		वापस;
	पूर्ण
	हाल -ERESTARTNOHAND:
	हाल -ERESTARTSYS:
	हाल -ERESTARTNOINTR:
		check_syscallno_in_delay_branch(regs);
		वापस;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 *
 * We need to be able to restore the syscall arguments (r21-r26) to
 * restart syscalls.  Thus, the syscall path should save them in the
 * pt_regs काष्ठाure (it's okay to करो so since they are caller-save
 * रेजिस्टरs).  As noted below, the syscall number माला_लो restored क्रम
 * us due to the magic of delayed branching.
 */
यंत्रlinkage व्योम
करो_संकेत(काष्ठा pt_regs *regs, दीर्घ in_syscall)
अणु
	काष्ठा kसंकेत ksig;

	DBG(1,"\ndo_signal: regs=0x%p, sr7 %#lx, in_syscall=%d\n",
	       regs, regs->sr[7], in_syscall);

	अगर (get_संकेत(&ksig)) अणु
		DBG(3,"do_signal: signr = %d, regs->gr[28] = %ld\n", signr, regs->gr[28]);
		/* Restart a प्रणाली call अगर necessary. */
		अगर (in_syscall)
			syscall_restart(regs, &ksig.ka);

		handle_संकेत(&ksig, regs, in_syscall);
		वापस;
	पूर्ण

	/* Did we come from a प्रणाली call? */
	अगर (in_syscall)
		insert_restart_trampoline(regs);
	
	DBG(1,"do_signal: Exit (not delivered), regs->gr[28] = %ld\n", 
		regs->gr[28]);

	restore_saved_sigmask();
पूर्ण

व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, दीर्घ in_syscall)
अणु
	अगर (test_thपढ़ो_flag(TIF_SIGPENDING) ||
	    test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs, in_syscall);

	अगर (test_thपढ़ो_flag(TIF_NOTIFY_RESUME))
		tracehook_notअगरy_resume(regs);
पूर्ण
