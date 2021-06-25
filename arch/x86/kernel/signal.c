<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 2000, 2001, 2002 Andi Kleen SuSE Lअसल
 *
 *  1997-11-28  Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 *  2000-06-20  Pentium III FXSR, SSE support by Gareth Hughes
 *  2000-2002   x86-64 support by Andi Kleen
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/personality.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/user-वापस-notअगरier.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/entry-common.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/fpu/संकेत.स>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/sighandling.h>
#समावेश <यंत्र/vm86.h>

#अगर_घोषित CONFIG_X86_64
#समावेश <linux/compat.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/ia32_unistd.h>
#पूर्ण_अगर /* CONFIG_X86_64 */

#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/sigframe.h>
#समावेश <यंत्र/संकेत.स>

#अगर_घोषित CONFIG_X86_64
/*
 * If regs->ss will cause an IRET fault, change it.  Otherwise leave it
 * alone.  Using this generally makes no sense unless
 * user_64bit_mode(regs) would वापस true.
 */
अटल व्योम क्रमce_valid_ss(काष्ठा pt_regs *regs)
अणु
	u32 ar;
	यंत्र अस्थिर ("lar %[old_ss], %[ar]\n\t"
		      "jz 1f\n\t"		/* If invalid: */
		      "xorl %[ar], %[ar]\n\t"	/* set ar = 0 */
		      "1:"
		      : [ar] "=r" (ar)
		      : [old_ss] "rm" ((u16)regs->ss));

	/*
	 * For a valid 64-bit user context, we need DPL 3, type
	 * पढ़ो-ग_लिखो data or पढ़ो-ग_लिखो exp-करोwn data, and S and P
	 * set.  We can't use VERW because VERW doesn't check the
	 * P bit.
	 */
	ar &= AR_DPL_MASK | AR_S | AR_P | AR_TYPE_MASK;
	अगर (ar != (AR_DPL3 | AR_S | AR_P | AR_TYPE_RWDATA) &&
	    ar != (AR_DPL3 | AR_S | AR_P | AR_TYPE_RWDATA_EXPDOWN))
		regs->ss = __USER_DS;
पूर्ण
# define CONTEXT_COPY_SIZE	दुरत्व(काष्ठा sigcontext, reserved1)
#अन्यथा
# define CONTEXT_COPY_SIZE	माप(काष्ठा sigcontext)
#पूर्ण_अगर

अटल पूर्णांक restore_sigcontext(काष्ठा pt_regs *regs,
			      काष्ठा sigcontext __user *usc,
			      अचिन्हित दीर्घ uc_flags)
अणु
	काष्ठा sigcontext sc;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	अगर (copy_from_user(&sc, usc, CONTEXT_COPY_SIZE))
		वापस -EFAULT;

#अगर_घोषित CONFIG_X86_32
	set_user_gs(regs, sc.gs);
	regs->fs = sc.fs;
	regs->es = sc.es;
	regs->ds = sc.ds;
#पूर्ण_अगर /* CONFIG_X86_32 */

	regs->bx = sc.bx;
	regs->cx = sc.cx;
	regs->dx = sc.dx;
	regs->si = sc.si;
	regs->di = sc.di;
	regs->bp = sc.bp;
	regs->ax = sc.ax;
	regs->sp = sc.sp;
	regs->ip = sc.ip;

#अगर_घोषित CONFIG_X86_64
	regs->r8 = sc.r8;
	regs->r9 = sc.r9;
	regs->r10 = sc.r10;
	regs->r11 = sc.r11;
	regs->r12 = sc.r12;
	regs->r13 = sc.r13;
	regs->r14 = sc.r14;
	regs->r15 = sc.r15;
#पूर्ण_अगर /* CONFIG_X86_64 */

	/* Get CS/SS and क्रमce CPL3 */
	regs->cs = sc.cs | 0x03;
	regs->ss = sc.ss | 0x03;

	regs->flags = (regs->flags & ~FIX_EFLAGS) | (sc.flags & FIX_EFLAGS);
	/* disable syscall checks */
	regs->orig_ax = -1;

#अगर_घोषित CONFIG_X86_64
	/*
	 * Fix up SS अगर needed क्रम the benefit of old DOSEMU and
	 * CRIU.
	 */
	अगर (unlikely(!(uc_flags & UC_STRICT_RESTORE_SS) && user_64bit_mode(regs)))
		क्रमce_valid_ss(regs);
#पूर्ण_अगर

	वापस fpu__restore_sig((व्योम __user *)sc.fpstate,
			       IS_ENABLED(CONFIG_X86_32));
पूर्ण

अटल __always_अंतरभूत पूर्णांक
__unsafe_setup_sigcontext(काष्ठा sigcontext __user *sc, व्योम __user *fpstate,
		     काष्ठा pt_regs *regs, अचिन्हित दीर्घ mask)
अणु
#अगर_घोषित CONFIG_X86_32
	unsafe_put_user(get_user_gs(regs),
				  (अचिन्हित पूर्णांक __user *)&sc->gs, Efault);
	unsafe_put_user(regs->fs, (अचिन्हित पूर्णांक __user *)&sc->fs, Efault);
	unsafe_put_user(regs->es, (अचिन्हित पूर्णांक __user *)&sc->es, Efault);
	unsafe_put_user(regs->ds, (अचिन्हित पूर्णांक __user *)&sc->ds, Efault);
#पूर्ण_अगर /* CONFIG_X86_32 */

	unsafe_put_user(regs->di, &sc->di, Efault);
	unsafe_put_user(regs->si, &sc->si, Efault);
	unsafe_put_user(regs->bp, &sc->bp, Efault);
	unsafe_put_user(regs->sp, &sc->sp, Efault);
	unsafe_put_user(regs->bx, &sc->bx, Efault);
	unsafe_put_user(regs->dx, &sc->dx, Efault);
	unsafe_put_user(regs->cx, &sc->cx, Efault);
	unsafe_put_user(regs->ax, &sc->ax, Efault);
#अगर_घोषित CONFIG_X86_64
	unsafe_put_user(regs->r8, &sc->r8, Efault);
	unsafe_put_user(regs->r9, &sc->r9, Efault);
	unsafe_put_user(regs->r10, &sc->r10, Efault);
	unsafe_put_user(regs->r11, &sc->r11, Efault);
	unsafe_put_user(regs->r12, &sc->r12, Efault);
	unsafe_put_user(regs->r13, &sc->r13, Efault);
	unsafe_put_user(regs->r14, &sc->r14, Efault);
	unsafe_put_user(regs->r15, &sc->r15, Efault);
#पूर्ण_अगर /* CONFIG_X86_64 */

	unsafe_put_user(current->thपढ़ो.trap_nr, &sc->trapno, Efault);
	unsafe_put_user(current->thपढ़ो.error_code, &sc->err, Efault);
	unsafe_put_user(regs->ip, &sc->ip, Efault);
#अगर_घोषित CONFIG_X86_32
	unsafe_put_user(regs->cs, (अचिन्हित पूर्णांक __user *)&sc->cs, Efault);
	unsafe_put_user(regs->flags, &sc->flags, Efault);
	unsafe_put_user(regs->sp, &sc->sp_at_संकेत, Efault);
	unsafe_put_user(regs->ss, (अचिन्हित पूर्णांक __user *)&sc->ss, Efault);
#अन्यथा /* !CONFIG_X86_32 */
	unsafe_put_user(regs->flags, &sc->flags, Efault);
	unsafe_put_user(regs->cs, &sc->cs, Efault);
	unsafe_put_user(0, &sc->gs, Efault);
	unsafe_put_user(0, &sc->fs, Efault);
	unsafe_put_user(regs->ss, &sc->ss, Efault);
#पूर्ण_अगर /* CONFIG_X86_32 */

	unsafe_put_user(fpstate, (अचिन्हित दीर्घ __user *)&sc->fpstate, Efault);

	/* non-iBCS2 extensions.. */
	unsafe_put_user(mask, &sc->oldmask, Efault);
	unsafe_put_user(current->thपढ़ो.cr2, &sc->cr2, Efault);
	वापस 0;
Efault:
	वापस -EFAULT;
पूर्ण

#घोषणा unsafe_put_sigcontext(sc, fp, regs, set, label)			\
करो अणु									\
	अगर (__unsafe_setup_sigcontext(sc, fp, regs, set->sig[0]))	\
		जाओ label;						\
पूर्ण जबतक(0);

#घोषणा unsafe_put_sigmask(set, frame, label) \
	unsafe_put_user(*(__u64 *)(set), \
			(__u64 __user *)&(frame)->uc.uc_sigmask, \
			label)

/*
 * Set up a संकेत frame.
 */

/*
 * Determine which stack to use..
 */
अटल अचिन्हित दीर्घ align_sigframe(अचिन्हित दीर्घ sp)
अणु
#अगर_घोषित CONFIG_X86_32
	/*
	 * Align the stack poपूर्णांकer according to the i386 ABI,
	 * i.e. so that on function entry ((sp + 4) & 15) == 0.
	 */
	sp = ((sp + 4) & -16ul) - 4;
#अन्यथा /* !CONFIG_X86_32 */
	sp = round_करोwn(sp, 16) - 8;
#पूर्ण_अगर
	वापस sp;
पूर्ण

अटल व्योम __user *
get_sigframe(काष्ठा k_sigaction *ka, काष्ठा pt_regs *regs, माप_प्रकार frame_size,
	     व्योम __user **fpstate)
अणु
	/* Default to using normal stack */
	अचिन्हित दीर्घ math_size = 0;
	अचिन्हित दीर्घ sp = regs->sp;
	अचिन्हित दीर्घ buf_fx = 0;
	पूर्णांक onsigstack = on_sig_stack(sp);
	पूर्णांक ret;

	/* redzone */
	अगर (IS_ENABLED(CONFIG_X86_64))
		sp -= 128;

	/* This is the X/Open sanctioned संकेत stack चयनing.  */
	अगर (ka->sa.sa_flags & SA_ONSTACK) अणु
		अगर (sas_ss_flags(sp) == 0)
			sp = current->sas_ss_sp + current->sas_ss_size;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_X86_32) &&
		   !onsigstack &&
		   regs->ss != __USER_DS &&
		   !(ka->sa.sa_flags & SA_RESTORER) &&
		   ka->sa.sa_restorer) अणु
		/* This is the legacy संकेत stack चयनing. */
		sp = (अचिन्हित दीर्घ) ka->sa.sa_restorer;
	पूर्ण

	sp = fpu__alloc_mathframe(sp, IS_ENABLED(CONFIG_X86_32),
				  &buf_fx, &math_size);
	*fpstate = (व्योम __user *)sp;

	sp = align_sigframe(sp - frame_size);

	/*
	 * If we are on the alternate संकेत stack and would overflow it, करोn't.
	 * Return an always-bogus address instead so we will die with संक_अंश.
	 */
	अगर (onsigstack && !likely(on_sig_stack(sp)))
		वापस (व्योम __user *)-1L;

	/* save i387 and extended state */
	ret = copy_fpstate_to_sigframe(*fpstate, (व्योम __user *)buf_fx, math_size);
	अगर (ret < 0)
		वापस (व्योम __user *)-1L;

	वापस (व्योम __user *)sp;
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल स्थिर काष्ठा अणु
	u16 poplmovl;
	u32 val;
	u16 पूर्णांक80;
पूर्ण __attribute__((packed)) retcode = अणु
	0xb858,		/* popl %eax; movl $..., %eax */
	__NR_sigवापस,
	0x80cd,		/* पूर्णांक $0x80 */
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8  movl;
	u32 val;
	u16 पूर्णांक80;
	u8  pad;
पूर्ण __attribute__((packed)) rt_retcode = अणु
	0xb8,		/* movl $..., %eax */
	__NR_rt_sigवापस,
	0x80cd,		/* पूर्णांक $0x80 */
	0
पूर्ण;

अटल पूर्णांक
__setup_frame(पूर्णांक sig, काष्ठा kसंकेत *ksig, sigset_t *set,
	      काष्ठा pt_regs *regs)
अणु
	काष्ठा sigframe __user *frame;
	व्योम __user *restorer;
	व्योम __user *fp = शून्य;

	frame = get_sigframe(&ksig->ka, regs, माप(*frame), &fp);

	अगर (!user_access_begin(frame, माप(*frame)))
		वापस -EFAULT;

	unsafe_put_user(sig, &frame->sig, Efault);
	unsafe_put_sigcontext(&frame->sc, fp, regs, set, Efault);
	unsafe_put_user(set->sig[1], &frame->extramask[0], Efault);
	अगर (current->mm->context.vdso)
		restorer = current->mm->context.vdso +
			vdso_image_32.sym___kernel_sigवापस;
	अन्यथा
		restorer = &frame->retcode;
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER)
		restorer = ksig->ka.sa.sa_restorer;

	/* Set up to वापस from userspace.  */
	unsafe_put_user(restorer, &frame->pretcode, Efault);

	/*
	 * This is popl %eax ; movl $__NR_sigवापस, %eax ; पूर्णांक $0x80
	 *
	 * WE DO NOT USE IT ANY MORE! It's only left here क्रम historical
	 * reasons and because gdb uses it as a signature to notice
	 * संकेत handler stack frames.
	 */
	unsafe_put_user(*((u64 *)&retcode), (u64 *)frame->retcode, Efault);
	user_access_end();

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->sp = (अचिन्हित दीर्घ)frame;
	regs->ip = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;
	regs->ax = (अचिन्हित दीर्घ)sig;
	regs->dx = 0;
	regs->cx = 0;

	regs->ds = __USER_DS;
	regs->es = __USER_DS;
	regs->ss = __USER_DS;
	regs->cs = __USER_CS;

	वापस 0;

Efault:
	user_access_end();
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक __setup_rt_frame(पूर्णांक sig, काष्ठा kसंकेत *ksig,
			    sigset_t *set, काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;
	व्योम __user *restorer;
	व्योम __user *fp = शून्य;

	frame = get_sigframe(&ksig->ka, regs, माप(*frame), &fp);

	अगर (!user_access_begin(frame, माप(*frame)))
		वापस -EFAULT;

	unsafe_put_user(sig, &frame->sig, Efault);
	unsafe_put_user(&frame->info, &frame->pinfo, Efault);
	unsafe_put_user(&frame->uc, &frame->puc, Efault);

	/* Create the ucontext.  */
	अगर (अटल_cpu_has(X86_FEATURE_XSAVE))
		unsafe_put_user(UC_FP_XSTATE, &frame->uc.uc_flags, Efault);
	अन्यथा
		unsafe_put_user(0, &frame->uc.uc_flags, Efault);
	unsafe_put_user(0, &frame->uc.uc_link, Efault);
	unsafe_save_altstack(&frame->uc.uc_stack, regs->sp, Efault);

	/* Set up to वापस from userspace.  */
	restorer = current->mm->context.vdso +
		vdso_image_32.sym___kernel_rt_sigवापस;
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER)
		restorer = ksig->ka.sa.sa_restorer;
	unsafe_put_user(restorer, &frame->pretcode, Efault);

	/*
	 * This is movl $__NR_rt_sigवापस, %ax ; पूर्णांक $0x80
	 *
	 * WE DO NOT USE IT ANY MORE! It's only left here क्रम historical
	 * reasons and because gdb uses it as a signature to notice
	 * संकेत handler stack frames.
	 */
	unsafe_put_user(*((u64 *)&rt_retcode), (u64 *)frame->retcode, Efault);
	unsafe_put_sigcontext(&frame->uc.uc_mcontext, fp, regs, set, Efault);
	unsafe_put_sigmask(set, frame, Efault);
	user_access_end();
	
	अगर (copy_siginfo_to_user(&frame->info, &ksig->info))
		वापस -EFAULT;

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->sp = (अचिन्हित दीर्घ)frame;
	regs->ip = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;
	regs->ax = (अचिन्हित दीर्घ)sig;
	regs->dx = (अचिन्हित दीर्घ)&frame->info;
	regs->cx = (अचिन्हित दीर्घ)&frame->uc;

	regs->ds = __USER_DS;
	regs->es = __USER_DS;
	regs->ss = __USER_DS;
	regs->cs = __USER_CS;

	वापस 0;
Efault:
	user_access_end();
	वापस -EFAULT;
पूर्ण
#अन्यथा /* !CONFIG_X86_32 */
अटल अचिन्हित दीर्घ frame_uc_flags(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags;

	अगर (boot_cpu_has(X86_FEATURE_XSAVE))
		flags = UC_FP_XSTATE | UC_SIGCONTEXT_SS;
	अन्यथा
		flags = UC_SIGCONTEXT_SS;

	अगर (likely(user_64bit_mode(regs)))
		flags |= UC_STRICT_RESTORE_SS;

	वापस flags;
पूर्ण

अटल पूर्णांक __setup_rt_frame(पूर्णांक sig, काष्ठा kसंकेत *ksig,
			    sigset_t *set, काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;
	व्योम __user *fp = शून्य;
	अचिन्हित दीर्घ uc_flags;

	/* x86-64 should always use SA_RESTORER. */
	अगर (!(ksig->ka.sa.sa_flags & SA_RESTORER))
		वापस -EFAULT;

	frame = get_sigframe(&ksig->ka, regs, माप(काष्ठा rt_sigframe), &fp);
	uc_flags = frame_uc_flags(regs);

	अगर (!user_access_begin(frame, माप(*frame)))
		वापस -EFAULT;

	/* Create the ucontext.  */
	unsafe_put_user(uc_flags, &frame->uc.uc_flags, Efault);
	unsafe_put_user(0, &frame->uc.uc_link, Efault);
	unsafe_save_altstack(&frame->uc.uc_stack, regs->sp, Efault);

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace.  */
	unsafe_put_user(ksig->ka.sa.sa_restorer, &frame->pretcode, Efault);
	unsafe_put_sigcontext(&frame->uc.uc_mcontext, fp, regs, set, Efault);
	unsafe_put_sigmask(set, frame, Efault);
	user_access_end();

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO) अणु
		अगर (copy_siginfo_to_user(&frame->info, &ksig->info))
			वापस -EFAULT;
	पूर्ण

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->di = sig;
	/* In हाल the संकेत handler was declared without prototypes */
	regs->ax = 0;

	/* This also works क्रम non SA_SIGINFO handlers because they expect the
	   next argument after the संकेत number on the stack. */
	regs->si = (अचिन्हित दीर्घ)&frame->info;
	regs->dx = (अचिन्हित दीर्घ)&frame->uc;
	regs->ip = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;

	regs->sp = (अचिन्हित दीर्घ)frame;

	/*
	 * Set up the CS and SS रेजिस्टरs to run संकेत handlers in
	 * 64-bit mode, even अगर the handler happens to be पूर्णांकerrupting
	 * 32-bit or 16-bit code.
	 *
	 * SS is subtle.  In 64-bit mode, we करोn't need any particular
	 * SS descriptor, but we करो need SS to be valid.  It's possible
	 * that the old SS is entirely bogus -- this can happen अगर the
	 * संकेत we're trying to deliver is #GP or #SS caused by a bad
	 * SS value.  We also have a compatibility issue here: DOSEMU
	 * relies on the contents of the SS रेजिस्टर indicating the
	 * SS value at the समय of the संकेत, even though that code in
	 * DOSEMU predates sigवापस's ability to restore SS.  (DOSEMU
	 * aव्योमs relying on sigवापस to restore SS; instead it uses
	 * a trampoline.)  So we करो our best: अगर the old SS was valid,
	 * we keep it.  Otherwise we replace it.
	 */
	regs->cs = __USER_CS;

	अगर (unlikely(regs->ss != __USER_DS))
		क्रमce_valid_ss(regs);

	वापस 0;

Efault:
	user_access_end();
	वापस -EFAULT;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_32 */

#अगर_घोषित CONFIG_X86_X32_ABI
अटल पूर्णांक x32_copy_siginfo_to_user(काष्ठा compat_siginfo __user *to,
		स्थिर काष्ठा kernel_siginfo *from)
अणु
	काष्ठा compat_siginfo new;

	copy_siginfo_to_बाह्यal32(&new, from);
	अगर (from->si_signo == SIGCHLD) अणु
		new._sअगरields._sigchld_x32._uसमय = from->si_uसमय;
		new._sअगरields._sigchld_x32._sसमय = from->si_sसमय;
	पूर्ण
	अगर (copy_to_user(to, &new, माप(काष्ठा compat_siginfo)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक copy_siginfo_to_user32(काष्ठा compat_siginfo __user *to,
			   स्थिर काष्ठा kernel_siginfo *from)
अणु
	अगर (in_x32_syscall())
		वापस x32_copy_siginfo_to_user(to, from);
	वापस __copy_siginfo_to_user32(to, from);
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_X32_ABI */

अटल पूर्णांक x32_setup_rt_frame(काष्ठा kसंकेत *ksig,
			      compat_sigset_t *set,
			      काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_X86_X32_ABI
	काष्ठा rt_sigframe_x32 __user *frame;
	अचिन्हित दीर्घ uc_flags;
	व्योम __user *restorer;
	व्योम __user *fp = शून्य;

	अगर (!(ksig->ka.sa.sa_flags & SA_RESTORER))
		वापस -EFAULT;

	frame = get_sigframe(&ksig->ka, regs, माप(*frame), &fp);

	uc_flags = frame_uc_flags(regs);

	अगर (!user_access_begin(frame, माप(*frame)))
		वापस -EFAULT;

	/* Create the ucontext.  */
	unsafe_put_user(uc_flags, &frame->uc.uc_flags, Efault);
	unsafe_put_user(0, &frame->uc.uc_link, Efault);
	unsafe_compat_save_altstack(&frame->uc.uc_stack, regs->sp, Efault);
	unsafe_put_user(0, &frame->uc.uc__pad0, Efault);
	restorer = ksig->ka.sa.sa_restorer;
	unsafe_put_user(restorer, (अचिन्हित दीर्घ __user *)&frame->pretcode, Efault);
	unsafe_put_sigcontext(&frame->uc.uc_mcontext, fp, regs, set, Efault);
	unsafe_put_sigmask(set, frame, Efault);
	user_access_end();

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO) अणु
		अगर (x32_copy_siginfo_to_user(&frame->info, &ksig->info))
			वापस -EFAULT;
	पूर्ण

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->sp = (अचिन्हित दीर्घ) frame;
	regs->ip = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;

	/* We use the x32 calling convention here... */
	regs->di = ksig->sig;
	regs->si = (अचिन्हित दीर्घ) &frame->info;
	regs->dx = (अचिन्हित दीर्घ) &frame->uc;

	loadsegment(ds, __USER_DS);
	loadsegment(es, __USER_DS);

	regs->cs = __USER_CS;
	regs->ss = __USER_DS;
#पूर्ण_अगर	/* CONFIG_X86_X32_ABI */

	वापस 0;
#अगर_घोषित CONFIG_X86_X32_ABI
Efault:
	user_access_end();
	वापस -EFAULT;
#पूर्ण_अगर
पूर्ण

/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 */
#अगर_घोषित CONFIG_X86_32
SYSCALL_DEFINE0(sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा sigframe __user *frame;
	sigset_t set;

	frame = (काष्ठा sigframe __user *)(regs->sp - 8);

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__get_user(set.sig[0], &frame->sc.oldmask) ||
	    __get_user(set.sig[1], &frame->extramask[0]))
		जाओ badframe;

	set_current_blocked(&set);

	/*
	 * x86_32 has no uc_flags bits relevant to restore_sigcontext.
	 * Save a few cycles by skipping the __get_user.
	 */
	अगर (restore_sigcontext(regs, &frame->sc, 0))
		जाओ badframe;
	वापस regs->ax;

badframe:
	संकेत_fault(regs, frame, "sigreturn");

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_32 */

SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा rt_sigframe __user *frame;
	sigset_t set;
	अचिन्हित दीर्घ uc_flags;

	frame = (काष्ठा rt_sigframe __user *)(regs->sp - माप(दीर्घ));
	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__get_user(*(__u64 *)&set, (__u64 __user *)&frame->uc.uc_sigmask))
		जाओ badframe;
	अगर (__get_user(uc_flags, &frame->uc.uc_flags))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(regs, &frame->uc.uc_mcontext, uc_flags))
		जाओ badframe;

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस regs->ax;

badframe:
	संकेत_fault(regs, frame, "rt_sigreturn");
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_ia32_compat_frame(काष्ठा kसंकेत *ksig)
अणु
	वापस IS_ENABLED(CONFIG_IA32_EMULATION) &&
		ksig->ka.sa.sa_flags & SA_IA32_ABI;
पूर्ण

अटल अंतरभूत पूर्णांक is_ia32_frame(काष्ठा kसंकेत *ksig)
अणु
	वापस IS_ENABLED(CONFIG_X86_32) || is_ia32_compat_frame(ksig);
पूर्ण

अटल अंतरभूत पूर्णांक is_x32_frame(काष्ठा kसंकेत *ksig)
अणु
	वापस IS_ENABLED(CONFIG_X86_X32_ABI) &&
		ksig->ka.sa.sa_flags & SA_X32_ABI;
पूर्ण

अटल पूर्णांक
setup_rt_frame(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	पूर्णांक usig = ksig->sig;
	sigset_t *set = sigmask_to_save();
	compat_sigset_t *cset = (compat_sigset_t *) set;

	/* Perक्रमm fixup क्रम the pre-संकेत frame. */
	rseq_संकेत_deliver(ksig, regs);

	/* Set up the stack frame */
	अगर (is_ia32_frame(ksig)) अणु
		अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
			वापस ia32_setup_rt_frame(usig, ksig, cset, regs);
		अन्यथा
			वापस ia32_setup_frame(usig, ksig, cset, regs);
	पूर्ण अन्यथा अगर (is_x32_frame(ksig)) अणु
		वापस x32_setup_rt_frame(ksig, cset, regs);
	पूर्ण अन्यथा अणु
		वापस __setup_rt_frame(ksig->sig, ksig, set, regs);
	पूर्ण
पूर्ण

अटल व्योम
handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	bool stepping, failed;
	काष्ठा fpu *fpu = &current->thपढ़ो.fpu;

	अगर (v8086_mode(regs))
		save_v86_state((काष्ठा kernel_vm86_regs *) regs, VM86_SIGNAL);

	/* Are we from a प्रणाली call? */
	अगर (syscall_get_nr(current, regs) >= 0) अणु
		/* If so, check प्रणाली call restarting.. */
		चयन (syscall_get_error(current, regs)) अणु
		हाल -ERESTART_RESTARTBLOCK:
		हाल -ERESTARTNOHAND:
			regs->ax = -EINTR;
			अवरोध;

		हाल -ERESTARTSYS:
			अगर (!(ksig->ka.sa.sa_flags & SA_RESTART)) अणु
				regs->ax = -EINTR;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल -ERESTARTNOINTR:
			regs->ax = regs->orig_ax;
			regs->ip -= 2;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If TF is set due to a debugger (TIF_FORCED_TF), clear TF now
	 * so that रेजिस्टर inक्रमmation in the sigcontext is correct and
	 * then notअगरy the tracer beक्रमe entering the संकेत handler.
	 */
	stepping = test_thपढ़ो_flag(TIF_SINGLESTEP);
	अगर (stepping)
		user_disable_single_step(current);

	failed = (setup_rt_frame(ksig, regs) < 0);
	अगर (!failed) अणु
		/*
		 * Clear the direction flag as per the ABI क्रम function entry.
		 *
		 * Clear RF when entering the संकेत handler, because
		 * it might disable possible debug exception from the
		 * संकेत handler.
		 *
		 * Clear TF क्रम the हाल when it wasn't set by debugger to
		 * aव्योम the recursive send_sigtrap() in SIGTRAP handler.
		 */
		regs->flags &= ~(X86_EFLAGS_DF|X86_EFLAGS_RF|X86_EFLAGS_TF);
		/*
		 * Ensure the संकेत handler starts with the new fpu state.
		 */
		fpu__clear_user_states(fpu);
	पूर्ण
	संकेत_setup_करोne(failed, ksig, stepping);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_nr_restart_syscall(स्थिर काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_IA32_EMULATION
	अगर (current->restart_block.arch_data & TS_COMPAT)
		वापस __NR_ia32_restart_syscall;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_X32_ABI
	वापस __NR_restart_syscall | (regs->orig_ax & __X32_SYSCALL_BIT);
#अन्यथा
	वापस __NR_restart_syscall;
#पूर्ण_अगर
पूर्ण

/*
 * Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 */
व्योम arch_करो_संकेत_or_restart(काष्ठा pt_regs *regs, bool has_संकेत)
अणु
	काष्ठा kसंकेत ksig;

	अगर (has_संकेत && get_संकेत(&ksig)) अणु
		/* Whee! Actually deliver the संकेत.  */
		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण

	/* Did we come from a प्रणाली call? */
	अगर (syscall_get_nr(current, regs) >= 0) अणु
		/* Restart the प्रणाली call - no handlers present */
		चयन (syscall_get_error(current, regs)) अणु
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
			regs->ax = regs->orig_ax;
			regs->ip -= 2;
			अवरोध;

		हाल -ERESTART_RESTARTBLOCK:
			regs->ax = get_nr_restart_syscall(regs);
			regs->ip -= 2;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If there's no संकेत to deliver, we just put the saved sigmask
	 * back.
	 */
	restore_saved_sigmask();
पूर्ण

व्योम संकेत_fault(काष्ठा pt_regs *regs, व्योम __user *frame, अक्षर *where)
अणु
	काष्ठा task_काष्ठा *me = current;

	अगर (show_unhandled_संकेतs && prपूर्णांकk_ratelimit()) अणु
		prपूर्णांकk("%s"
		       "%s[%d] bad frame in %s frame:%p ip:%lx sp:%lx orax:%lx",
		       task_pid_nr(current) > 1 ? KERN_INFO : KERN_EMERG,
		       me->comm, me->pid, where, frame,
		       regs->ip, regs->sp, regs->orig_ax);
		prपूर्णांक_vma_addr(KERN_CONT " in ", regs->ip);
		pr_cont("\n");
	पूर्ण

	क्रमce_sig(संक_अंश);
पूर्ण

#अगर_घोषित CONFIG_X86_X32_ABI
COMPAT_SYSCALL_DEFINE0(x32_rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा rt_sigframe_x32 __user *frame;
	sigset_t set;
	अचिन्हित दीर्घ uc_flags;

	frame = (काष्ठा rt_sigframe_x32 __user *)(regs->sp - 8);

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__get_user(set.sig[0], (__u64 __user *)&frame->uc.uc_sigmask))
		जाओ badframe;
	अगर (__get_user(uc_flags, &frame->uc.uc_flags))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(regs, &frame->uc.uc_mcontext, uc_flags))
		जाओ badframe;

	अगर (compat_restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस regs->ax;

badframe:
	संकेत_fault(regs, frame, "x32 rt_sigreturn");
	वापस 0;
पूर्ण
#पूर्ण_अगर
