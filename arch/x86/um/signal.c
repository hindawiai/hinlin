<शैली गुरु>
/*
 * Copyright (C) 2003 PathScale, Inc.
 * Copyright (C) 2003 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */


#समावेश <linux/personality.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/unistd.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <frame_kern.h>
#समावेश <skas.h>

#अगर_घोषित CONFIG_X86_32

/*
 * FPU tag word conversions.
 */

अटल अंतरभूत अचिन्हित लघु twd_i387_to_fxsr(अचिन्हित लघु twd)
अणु
	अचिन्हित पूर्णांक पंचांगp; /* to aव्योम 16 bit prefixes in the code */

	/* Transक्रमm each pair of bits पूर्णांकo 01 (valid) or 00 (empty) */
	पंचांगp = ~twd;
	पंचांगp = (पंचांगp | (पंचांगp>>1)) & 0x5555; /* 0V0V0V0V0V0V0V0V */
	/* and move the valid bits to the lower byte. */
	पंचांगp = (पंचांगp | (पंचांगp >> 1)) & 0x3333; /* 00VV00VV00VV00VV */
	पंचांगp = (पंचांगp | (पंचांगp >> 2)) & 0x0f0f; /* 0000VVVV0000VVVV */
	पंचांगp = (पंचांगp | (पंचांगp >> 4)) & 0x00ff; /* 00000000VVVVVVVV */
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ twd_fxsr_to_i387(काष्ठा user_fxsr_काष्ठा *fxsave)
अणु
	काष्ठा _fpxreg *st = शून्य;
	अचिन्हित दीर्घ twd = (अचिन्हित दीर्घ) fxsave->twd;
	अचिन्हित दीर्घ tag;
	अचिन्हित दीर्घ ret = 0xffff0000;
	पूर्णांक i;

#घोषणा FPREG_ADDR(f, n)	((अक्षर *)&(f)->st_space + (n) * 16)

	क्रम (i = 0; i < 8; i++) अणु
		अगर (twd & 0x1) अणु
			st = (काष्ठा _fpxreg *) FPREG_ADDR(fxsave, i);

			चयन (st->exponent & 0x7fff) अणु
			हाल 0x7fff:
				tag = 2;		/* Special */
				अवरोध;
			हाल 0x0000:
				अगर ( !st->signअगरicand[0] &&
				     !st->signअगरicand[1] &&
				     !st->signअगरicand[2] &&
				     !st->signअगरicand[3] ) अणु
					tag = 1;	/* Zero */
				पूर्ण अन्यथा अणु
					tag = 2;	/* Special */
				पूर्ण
				अवरोध;
			शेष:
				अगर (st->signअगरicand[3] & 0x8000) अणु
					tag = 0;	/* Valid */
				पूर्ण अन्यथा अणु
					tag = 2;	/* Special */
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			tag = 3;			/* Empty */
		पूर्ण
		ret |= (tag << (2 * i));
		twd = twd >> 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक convert_fxsr_to_user(काष्ठा _fpstate __user *buf,
				काष्ठा user_fxsr_काष्ठा *fxsave)
अणु
	अचिन्हित दीर्घ env[7];
	काष्ठा _fpreg __user *to;
	काष्ठा _fpxreg *from;
	पूर्णांक i;

	env[0] = (अचिन्हित दीर्घ)fxsave->cwd | 0xffff0000ul;
	env[1] = (अचिन्हित दीर्घ)fxsave->swd | 0xffff0000ul;
	env[2] = twd_fxsr_to_i387(fxsave);
	env[3] = fxsave->fip;
	env[4] = fxsave->fcs | ((अचिन्हित दीर्घ)fxsave->fop << 16);
	env[5] = fxsave->foo;
	env[6] = fxsave->fos;

	अगर (__copy_to_user(buf, env, 7 * माप(अचिन्हित दीर्घ)))
		वापस 1;

	to = &buf->_st[0];
	from = (काष्ठा _fpxreg *) &fxsave->st_space[0];
	क्रम (i = 0; i < 8; i++, to++, from++) अणु
		अचिन्हित दीर्घ __user *t = (अचिन्हित दीर्घ __user *)to;
		अचिन्हित दीर्घ *f = (अचिन्हित दीर्घ *)from;

		अगर (__put_user(*f, t) ||
				__put_user(*(f + 1), t + 1) ||
				__put_user(from->exponent, &to->exponent))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक convert_fxsr_from_user(काष्ठा user_fxsr_काष्ठा *fxsave,
				  काष्ठा _fpstate __user *buf)
अणु
	अचिन्हित दीर्घ env[7];
	काष्ठा _fpxreg *to;
	काष्ठा _fpreg __user *from;
	पूर्णांक i;

	अगर (copy_from_user( env, buf, 7 * माप(दीर्घ)))
		वापस 1;

	fxsave->cwd = (अचिन्हित लघु)(env[0] & 0xffff);
	fxsave->swd = (अचिन्हित लघु)(env[1] & 0xffff);
	fxsave->twd = twd_i387_to_fxsr((अचिन्हित लघु)(env[2] & 0xffff));
	fxsave->fip = env[3];
	fxsave->fop = (अचिन्हित लघु)((env[4] & 0xffff0000ul) >> 16);
	fxsave->fcs = (env[4] & 0xffff);
	fxsave->foo = env[5];
	fxsave->fos = env[6];

	to = (काष्ठा _fpxreg *) &fxsave->st_space[0];
	from = &buf->_st[0];
	क्रम (i = 0; i < 8; i++, to++, from++) अणु
		अचिन्हित दीर्घ *t = (अचिन्हित दीर्घ *)to;
		अचिन्हित दीर्घ __user *f = (अचिन्हित दीर्घ __user *)from;

		अगर (__get_user(*t, f) ||
		    __get_user(*(t + 1), f + 1) ||
		    __get_user(to->exponent, &from->exponent))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

बाह्य पूर्णांक have_fpx_regs;

#पूर्ण_अगर

अटल पूर्णांक copy_sc_from_user(काष्ठा pt_regs *regs,
			     काष्ठा sigcontext __user *from)
अणु
	काष्ठा sigcontext sc;
	पूर्णांक err, pid;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	err = copy_from_user(&sc, from, माप(sc));
	अगर (err)
		वापस err;

#घोषणा GETREG(regno, regname) regs->regs.gp[HOST_##regno] = sc.regname

#अगर_घोषित CONFIG_X86_32
	GETREG(GS, gs);
	GETREG(FS, fs);
	GETREG(ES, es);
	GETREG(DS, ds);
#पूर्ण_अगर
	GETREG(DI, di);
	GETREG(SI, si);
	GETREG(BP, bp);
	GETREG(SP, sp);
	GETREG(BX, bx);
	GETREG(DX, dx);
	GETREG(CX, cx);
	GETREG(AX, ax);
	GETREG(IP, ip);

#अगर_घोषित CONFIG_X86_64
	GETREG(R8, r8);
	GETREG(R9, r9);
	GETREG(R10, r10);
	GETREG(R11, r11);
	GETREG(R12, r12);
	GETREG(R13, r13);
	GETREG(R14, r14);
	GETREG(R15, r15);
#पूर्ण_अगर

	GETREG(CS, cs);
	GETREG(EFLAGS, flags);
#अगर_घोषित CONFIG_X86_32
	GETREG(SS, ss);
#पूर्ण_अगर

#अघोषित GETREG

	pid = userspace_pid[current_thपढ़ो_info()->cpu];
#अगर_घोषित CONFIG_X86_32
	अगर (have_fpx_regs) अणु
		काष्ठा user_fxsr_काष्ठा fpx;

		err = copy_from_user(&fpx,
			&((काष्ठा _fpstate __user *)sc.fpstate)->_fxsr_env[0],
				     माप(काष्ठा user_fxsr_काष्ठा));
		अगर (err)
			वापस 1;

		err = convert_fxsr_from_user(&fpx, (व्योम *)sc.fpstate);
		अगर (err)
			वापस 1;

		err = restore_fpx_रेजिस्टरs(pid, (अचिन्हित दीर्घ *) &fpx);
		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR "copy_sc_from_user - "
			       "restore_fpx_registers failed, errno = %d\n",
			       -err);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		err = copy_from_user(regs->regs.fp, (व्योम *)sc.fpstate,
				     माप(काष्ठा _xstate));
		अगर (err)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक copy_sc_to_user(काष्ठा sigcontext __user *to,
			   काष्ठा _xstate __user *to_fp, काष्ठा pt_regs *regs,
			   अचिन्हित दीर्घ mask)
अणु
	काष्ठा sigcontext sc;
	काष्ठा faultinfo * fi = &current->thपढ़ो.arch.faultinfo;
	पूर्णांक err, pid;
	स_रखो(&sc, 0, माप(काष्ठा sigcontext));

#घोषणा PUTREG(regno, regname) sc.regname = regs->regs.gp[HOST_##regno]

#अगर_घोषित CONFIG_X86_32
	PUTREG(GS, gs);
	PUTREG(FS, fs);
	PUTREG(ES, es);
	PUTREG(DS, ds);
#पूर्ण_अगर
	PUTREG(DI, di);
	PUTREG(SI, si);
	PUTREG(BP, bp);
	PUTREG(SP, sp);
	PUTREG(BX, bx);
	PUTREG(DX, dx);
	PUTREG(CX, cx);
	PUTREG(AX, ax);
#अगर_घोषित CONFIG_X86_64
	PUTREG(R8, r8);
	PUTREG(R9, r9);
	PUTREG(R10, r10);
	PUTREG(R11, r11);
	PUTREG(R12, r12);
	PUTREG(R13, r13);
	PUTREG(R14, r14);
	PUTREG(R15, r15);
#पूर्ण_अगर

	sc.cr2 = fi->cr2;
	sc.err = fi->error_code;
	sc.trapno = fi->trap_no;
	PUTREG(IP, ip);
	PUTREG(CS, cs);
	PUTREG(EFLAGS, flags);
#अगर_घोषित CONFIG_X86_32
	PUTREG(SP, sp_at_संकेत);
	PUTREG(SS, ss);
#पूर्ण_अगर
#अघोषित PUTREG
	sc.oldmask = mask;
	sc.fpstate = (अचिन्हित दीर्घ)to_fp;

	err = copy_to_user(to, &sc, माप(काष्ठा sigcontext));
	अगर (err)
		वापस 1;

	pid = userspace_pid[current_thपढ़ो_info()->cpu];

#अगर_घोषित CONFIG_X86_32
	अगर (have_fpx_regs) अणु
		काष्ठा user_fxsr_काष्ठा fpx;

		err = save_fpx_रेजिस्टरs(pid, (अचिन्हित दीर्घ *) &fpx);
		अगर (err < 0)अणु
			prपूर्णांकk(KERN_ERR "copy_sc_to_user - save_fpx_registers "
			       "failed, errno = %d\n", err);
			वापस 1;
		पूर्ण

		err = convert_fxsr_to_user(&to_fp->fpstate, &fpx);
		अगर (err)
			वापस 1;

		err |= __put_user(fpx.swd, &to_fp->fpstate.status);
		err |= __put_user(X86_FXSR_MAGIC, &to_fp->fpstate.magic);
		अगर (err)
			वापस 1;

		अगर (copy_to_user(&to_fp->fpstate._fxsr_env[0], &fpx,
				 माप(काष्ठा user_fxsr_काष्ठा)))
			वापस 1;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अगर (copy_to_user(to_fp, regs->regs.fp, माप(काष्ठा _xstate)))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल पूर्णांक copy_ucontext_to_user(काष्ठा ucontext __user *uc,
				 काष्ठा _xstate __user *fp, sigset_t *set,
				 अचिन्हित दीर्घ sp)
अणु
	पूर्णांक err = 0;

	err |= __save_altstack(&uc->uc_stack, sp);
	err |= copy_sc_to_user(&uc->uc_mcontext, fp, &current->thपढ़ो.regs, 0);
	err |= copy_to_user(&uc->uc_sigmask, set, माप(*set));
	वापस err;
पूर्ण

काष्ठा sigframe
अणु
	अक्षर __user *pretcode;
	पूर्णांक sig;
	काष्ठा sigcontext sc;
	काष्ठा _xstate fpstate;
	अचिन्हित दीर्घ extramask[_NSIG_WORDS-1];
	अक्षर retcode[8];
पूर्ण;

काष्ठा rt_sigframe
अणु
	अक्षर __user *pretcode;
	पूर्णांक sig;
	काष्ठा siginfo __user *pinfo;
	व्योम __user *puc;
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
	काष्ठा _xstate fpstate;
	अक्षर retcode[8];
पूर्ण;

पूर्णांक setup_संकेत_stack_sc(अचिन्हित दीर्घ stack_top, काष्ठा kसंकेत *ksig,
			  काष्ठा pt_regs *regs, sigset_t *mask)
अणु
	काष्ठा sigframe __user *frame;
	व्योम __user *restorer;
	पूर्णांक err = 0, sig = ksig->sig;

	/* This is the same calculation as i386 - ((sp + 4) & 15) == 0 */
	stack_top = ((stack_top + 4) & -16UL) - 4;
	frame = (काष्ठा sigframe __user *) stack_top - 1;
	अगर (!access_ok(frame, माप(*frame)))
		वापस 1;

	restorer = frame->retcode;
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER)
		restorer = ksig->ka.sa.sa_restorer;

	err |= __put_user(restorer, &frame->pretcode);
	err |= __put_user(sig, &frame->sig);
	err |= copy_sc_to_user(&frame->sc, &frame->fpstate, regs, mask->sig[0]);
	अगर (_NSIG_WORDS > 1)
		err |= __copy_to_user(&frame->extramask, &mask->sig[1],
				      माप(frame->extramask));

	/*
	 * This is popl %eax ; movl $,%eax ; पूर्णांक $0x80
	 *
	 * WE DO NOT USE IT ANY MORE! It's only left here क्रम historical
	 * reasons and because gdb uses it as a signature to notice
	 * संकेत handler stack frames.
	 */
	err |= __put_user(0xb858, (लघु __user *)(frame->retcode+0));
	err |= __put_user(__NR_sigवापस, (पूर्णांक __user *)(frame->retcode+2));
	err |= __put_user(0x80cd, (लघु __user *)(frame->retcode+6));

	अगर (err)
		वापस err;

	PT_REGS_SP(regs) = (अचिन्हित दीर्घ) frame;
	PT_REGS_IP(regs) = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	PT_REGS_AX(regs) = (अचिन्हित दीर्घ) sig;
	PT_REGS_DX(regs) = (अचिन्हित दीर्घ) 0;
	PT_REGS_CX(regs) = (अचिन्हित दीर्घ) 0;
	वापस 0;
पूर्ण

पूर्णांक setup_संकेत_stack_si(अचिन्हित दीर्घ stack_top, काष्ठा kसंकेत *ksig,
			  काष्ठा pt_regs *regs, sigset_t *mask)
अणु
	काष्ठा rt_sigframe __user *frame;
	व्योम __user *restorer;
	पूर्णांक err = 0, sig = ksig->sig;

	stack_top &= -8UL;
	frame = (काष्ठा rt_sigframe __user *) stack_top - 1;
	अगर (!access_ok(frame, माप(*frame)))
		वापस 1;

	restorer = frame->retcode;
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER)
		restorer = ksig->ka.sa.sa_restorer;

	err |= __put_user(restorer, &frame->pretcode);
	err |= __put_user(sig, &frame->sig);
	err |= __put_user(&frame->info, &frame->pinfo);
	err |= __put_user(&frame->uc, &frame->puc);
	err |= copy_siginfo_to_user(&frame->info, &ksig->info);
	err |= copy_ucontext_to_user(&frame->uc, &frame->fpstate, mask,
					PT_REGS_SP(regs));

	/*
	 * This is movl $,%eax ; पूर्णांक $0x80
	 *
	 * WE DO NOT USE IT ANY MORE! It's only left here क्रम historical
	 * reasons and because gdb uses it as a signature to notice
	 * संकेत handler stack frames.
	 */
	err |= __put_user(0xb8, (अक्षर __user *)(frame->retcode+0));
	err |= __put_user(__NR_rt_sigवापस, (पूर्णांक __user *)(frame->retcode+1));
	err |= __put_user(0x80cd, (लघु __user *)(frame->retcode+5));

	अगर (err)
		वापस err;

	PT_REGS_SP(regs) = (अचिन्हित दीर्घ) frame;
	PT_REGS_IP(regs) = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	PT_REGS_AX(regs) = (अचिन्हित दीर्घ) sig;
	PT_REGS_DX(regs) = (अचिन्हित दीर्घ) &frame->info;
	PT_REGS_CX(regs) = (अचिन्हित दीर्घ) &frame->uc;
	वापस 0;
पूर्ण

दीर्घ sys_sigवापस(व्योम)
अणु
	अचिन्हित दीर्घ sp = PT_REGS_SP(&current->thपढ़ो.regs);
	काष्ठा sigframe __user *frame = (काष्ठा sigframe __user *)(sp - 8);
	sigset_t set;
	काष्ठा sigcontext __user *sc = &frame->sc;
	पूर्णांक sig_size = (_NSIG_WORDS - 1) * माप(अचिन्हित दीर्घ);

	अगर (copy_from_user(&set.sig[0], &sc->oldmask, माप(set.sig[0])) ||
	    copy_from_user(&set.sig[1], frame->extramask, sig_size))
		जाओ segfault;

	set_current_blocked(&set);

	अगर (copy_sc_from_user(&current->thपढ़ो.regs, sc))
		जाओ segfault;

	/* Aव्योम ERESTART handling */
	PT_REGS_SYSCALL_NR(&current->thपढ़ो.regs) = -1;
	वापस PT_REGS_SYSCALL_RET(&current->thपढ़ो.regs);

 segfault:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

#अन्यथा

काष्ठा rt_sigframe
अणु
	अक्षर __user *pretcode;
	काष्ठा ucontext uc;
	काष्ठा siginfo info;
	काष्ठा _xstate fpstate;
पूर्ण;

पूर्णांक setup_संकेत_stack_si(अचिन्हित दीर्घ stack_top, काष्ठा kसंकेत *ksig,
			  काष्ठा pt_regs *regs, sigset_t *set)
अणु
	काष्ठा rt_sigframe __user *frame;
	पूर्णांक err = 0, sig = ksig->sig;
	अचिन्हित दीर्घ fp_to;

	frame = (काष्ठा rt_sigframe __user *)
		round_करोwn(stack_top - माप(काष्ठा rt_sigframe), 16);
	/* Subtract 128 क्रम a red zone and 8 क्रम proper alignment */
	frame = (काष्ठा rt_sigframe __user *) ((अचिन्हित दीर्घ) frame - 128 - 8);

	अगर (!access_ok(frame, माप(*frame)))
		जाओ out;

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO) अणु
		err |= copy_siginfo_to_user(&frame->info, &ksig->info);
		अगर (err)
			जाओ out;
	पूर्ण

	/* Create the ucontext.  */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(0, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, PT_REGS_SP(regs));
	err |= copy_sc_to_user(&frame->uc.uc_mcontext, &frame->fpstate, regs,
			       set->sig[0]);

	fp_to = (अचिन्हित दीर्घ)&frame->fpstate;

	err |= __put_user(fp_to, &frame->uc.uc_mcontext.fpstate);
	अगर (माप(*set) == 16) अणु
		err |= __put_user(set->sig[0], &frame->uc.uc_sigmask.sig[0]);
		err |= __put_user(set->sig[1], &frame->uc.uc_sigmask.sig[1]);
	पूर्ण
	अन्यथा
		err |= __copy_to_user(&frame->uc.uc_sigmask, set,
				      माप(*set));

	/*
	 * Set up to वापस from userspace.  If provided, use a stub
	 * alपढ़ोy in userspace.
	 */
	/* x86-64 should always use SA_RESTORER. */
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER)
		err |= __put_user((व्योम *)ksig->ka.sa.sa_restorer,
				  &frame->pretcode);
	अन्यथा
		/* could use a vstub here */
		वापस err;

	अगर (err)
		वापस err;

	PT_REGS_SP(regs) = (अचिन्हित दीर्घ) frame;
	PT_REGS_DI(regs) = sig;
	/* In हाल the संकेत handler was declared without prototypes */
	PT_REGS_AX(regs) = 0;

	/*
	 * This also works क्रम non SA_SIGINFO handlers because they expect the
	 * next argument after the संकेत number on the stack.
	 */
	PT_REGS_SI(regs) = (अचिन्हित दीर्घ) &frame->info;
	PT_REGS_DX(regs) = (अचिन्हित दीर्घ) &frame->uc;
	PT_REGS_IP(regs) = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
 out:
	वापस err;
पूर्ण
#पूर्ण_अगर

दीर्घ sys_rt_sigवापस(व्योम)
अणु
	अचिन्हित दीर्घ sp = PT_REGS_SP(&current->thपढ़ो.regs);
	काष्ठा rt_sigframe __user *frame =
		(काष्ठा rt_sigframe __user *)(sp - माप(दीर्घ));
	काष्ठा ucontext __user *uc = &frame->uc;
	sigset_t set;

	अगर (copy_from_user(&set, &uc->uc_sigmask, माप(set)))
		जाओ segfault;

	set_current_blocked(&set);

	अगर (copy_sc_from_user(&current->thपढ़ो.regs, &uc->uc_mcontext))
		जाओ segfault;

	/* Aव्योम ERESTART handling */
	PT_REGS_SYSCALL_NR(&current->thपढ़ो.regs) = -1;
	वापस PT_REGS_SYSCALL_RET(&current->thपढ़ो.regs);

 segfault:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण
