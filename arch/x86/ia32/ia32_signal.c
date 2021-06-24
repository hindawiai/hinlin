<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/x86_64/ia32/ia32_संकेत.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  1997-11-28  Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 *  2000-06-20  Pentium III FXSR, SSE support by Gareth Hughes
 *  2000-12-*   x86-64 compatibility mode संकेत handling by Andi Kleen
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/personality.h>
#समावेश <linux/compat.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/fpu/संकेत.स>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/ia32_unistd.h>
#समावेश <यंत्र/user32.h>
#समावेश <uapi/यंत्र/sigcontext.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/sigframe.h>
#समावेश <यंत्र/sighandling.h>
#समावेश <यंत्र/smap.h>

अटल अंतरभूत व्योम reload_segments(काष्ठा sigcontext_32 *sc)
अणु
	अचिन्हित पूर्णांक cur;

	savesegment(gs, cur);
	अगर ((sc->gs | 0x03) != cur)
		load_gs_index(sc->gs | 0x03);
	savesegment(fs, cur);
	अगर ((sc->fs | 0x03) != cur)
		loadsegment(fs, sc->fs | 0x03);
	savesegment(ds, cur);
	अगर ((sc->ds | 0x03) != cur)
		loadsegment(ds, sc->ds | 0x03);
	savesegment(es, cur);
	अगर ((sc->es | 0x03) != cur)
		loadsegment(es, sc->es | 0x03);
पूर्ण

/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 */
अटल पूर्णांक ia32_restore_sigcontext(काष्ठा pt_regs *regs,
				   काष्ठा sigcontext_32 __user *usc)
अणु
	काष्ठा sigcontext_32 sc;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	अगर (unlikely(copy_from_user(&sc, usc, माप(sc))))
		वापस -EFAULT;

	/* Get only the ia32 रेजिस्टरs. */
	regs->bx = sc.bx;
	regs->cx = sc.cx;
	regs->dx = sc.dx;
	regs->si = sc.si;
	regs->di = sc.di;
	regs->bp = sc.bp;
	regs->ax = sc.ax;
	regs->sp = sc.sp;
	regs->ip = sc.ip;

	/* Get CS/SS and क्रमce CPL3 */
	regs->cs = sc.cs | 0x03;
	regs->ss = sc.ss | 0x03;

	regs->flags = (regs->flags & ~FIX_EFLAGS) | (sc.flags & FIX_EFLAGS);
	/* disable syscall checks */
	regs->orig_ax = -1;

	/*
	 * Reload fs and gs अगर they have changed in the संकेत
	 * handler.  This करोes not handle दीर्घ fs/gs base changes in
	 * the handler, but करोes not clobber them at least in the
	 * normal हाल.
	 */
	reload_segments(&sc);
	वापस fpu__restore_sig(compat_ptr(sc.fpstate), 1);
पूर्ण

COMPAT_SYSCALL_DEFINE0(sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा sigframe_ia32 __user *frame = (काष्ठा sigframe_ia32 __user *)(regs->sp-8);
	sigset_t set;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__get_user(set.sig[0], &frame->sc.oldmask)
	    || __get_user(((__u32 *)&set)[1], &frame->extramask[0]))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (ia32_restore_sigcontext(regs, &frame->sc))
		जाओ badframe;
	वापस regs->ax;

badframe:
	संकेत_fault(regs, frame, "32bit sigreturn");
	वापस 0;
पूर्ण

COMPAT_SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा rt_sigframe_ia32 __user *frame;
	sigset_t set;

	frame = (काष्ठा rt_sigframe_ia32 __user *)(regs->sp - 4);

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__get_user(set.sig[0], (__u64 __user *)&frame->uc.uc_sigmask))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (ia32_restore_sigcontext(regs, &frame->uc.uc_mcontext))
		जाओ badframe;

	अगर (compat_restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस regs->ax;

badframe:
	संकेत_fault(regs, frame, "32bit rt sigreturn");
	वापस 0;
पूर्ण

/*
 * Set up a संकेत frame.
 */

#घोषणा get_user_seg(seg)	(अणु अचिन्हित पूर्णांक v; savesegment(seg, v); v; पूर्ण)

अटल __always_अंतरभूत पूर्णांक
__unsafe_setup_sigcontext32(काष्ठा sigcontext_32 __user *sc,
			    व्योम __user *fpstate,
			    काष्ठा pt_regs *regs, अचिन्हित पूर्णांक mask)
अणु
	unsafe_put_user(get_user_seg(gs), (अचिन्हित पूर्णांक __user *)&sc->gs, Efault);
	unsafe_put_user(get_user_seg(fs), (अचिन्हित पूर्णांक __user *)&sc->fs, Efault);
	unsafe_put_user(get_user_seg(ds), (अचिन्हित पूर्णांक __user *)&sc->ds, Efault);
	unsafe_put_user(get_user_seg(es), (अचिन्हित पूर्णांक __user *)&sc->es, Efault);

	unsafe_put_user(regs->di, &sc->di, Efault);
	unsafe_put_user(regs->si, &sc->si, Efault);
	unsafe_put_user(regs->bp, &sc->bp, Efault);
	unsafe_put_user(regs->sp, &sc->sp, Efault);
	unsafe_put_user(regs->bx, &sc->bx, Efault);
	unsafe_put_user(regs->dx, &sc->dx, Efault);
	unsafe_put_user(regs->cx, &sc->cx, Efault);
	unsafe_put_user(regs->ax, &sc->ax, Efault);
	unsafe_put_user(current->thपढ़ो.trap_nr, &sc->trapno, Efault);
	unsafe_put_user(current->thपढ़ो.error_code, &sc->err, Efault);
	unsafe_put_user(regs->ip, &sc->ip, Efault);
	unsafe_put_user(regs->cs, (अचिन्हित पूर्णांक __user *)&sc->cs, Efault);
	unsafe_put_user(regs->flags, &sc->flags, Efault);
	unsafe_put_user(regs->sp, &sc->sp_at_संकेत, Efault);
	unsafe_put_user(regs->ss, (अचिन्हित पूर्णांक __user *)&sc->ss, Efault);

	unsafe_put_user(ptr_to_compat(fpstate), &sc->fpstate, Efault);

	/* non-iBCS2 extensions.. */
	unsafe_put_user(mask, &sc->oldmask, Efault);
	unsafe_put_user(current->thपढ़ो.cr2, &sc->cr2, Efault);
	वापस 0;

Efault:
	वापस -EFAULT;
पूर्ण

#घोषणा unsafe_put_sigcontext32(sc, fp, regs, set, label)		\
करो अणु									\
	अगर (__unsafe_setup_sigcontext32(sc, fp, regs, set->sig[0]))	\
		जाओ label;						\
पूर्ण जबतक(0)

/*
 * Determine which stack to use..
 */
अटल व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs,
				 माप_प्रकार frame_size,
				 व्योम __user **fpstate)
अणु
	अचिन्हित दीर्घ sp, fx_aligned, math_size;

	/* Default to using normal stack */
	sp = regs->sp;

	/* This is the X/Open sanctioned संकेत stack चयनing.  */
	अगर (ksig->ka.sa.sa_flags & SA_ONSTACK)
		sp = sigsp(sp, ksig);
	/* This is the legacy संकेत stack चयनing. */
	अन्यथा अगर (regs->ss != __USER32_DS &&
		!(ksig->ka.sa.sa_flags & SA_RESTORER) &&
		 ksig->ka.sa.sa_restorer)
		sp = (अचिन्हित दीर्घ) ksig->ka.sa.sa_restorer;

	sp = fpu__alloc_mathframe(sp, 1, &fx_aligned, &math_size);
	*fpstate = (काष्ठा _fpstate_32 __user *) sp;
	अगर (copy_fpstate_to_sigframe(*fpstate, (व्योम __user *)fx_aligned,
				     math_size) < 0)
		वापस (व्योम __user *) -1L;

	sp -= frame_size;
	/* Align the stack poपूर्णांकer according to the i386 ABI,
	 * i.e. so that on function entry ((sp + 4) & 15) == 0. */
	sp = ((sp + 4) & -16ul) - 4;
	वापस (व्योम __user *) sp;
पूर्ण

पूर्णांक ia32_setup_frame(पूर्णांक sig, काष्ठा kसंकेत *ksig,
		     compat_sigset_t *set, काष्ठा pt_regs *regs)
अणु
	काष्ठा sigframe_ia32 __user *frame;
	व्योम __user *restorer;
	व्योम __user *fp = शून्य;

	/* copy_to_user optimizes that पूर्णांकo a single 8 byte store */
	अटल स्थिर काष्ठा अणु
		u16 poplmovl;
		u32 val;
		u16 पूर्णांक80;
	पूर्ण __attribute__((packed)) code = अणु
		0xb858,		 /* popl %eax ; movl $...,%eax */
		__NR_ia32_sigवापस,
		0x80cd,		/* पूर्णांक $0x80 */
	पूर्ण;

	frame = get_sigframe(ksig, regs, माप(*frame), &fp);

	अगर (ksig->ka.sa.sa_flags & SA_RESTORER) अणु
		restorer = ksig->ka.sa.sa_restorer;
	पूर्ण अन्यथा अणु
		/* Return stub is in 32bit vsyscall page */
		अगर (current->mm->context.vdso)
			restorer = current->mm->context.vdso +
				vdso_image_32.sym___kernel_sigवापस;
		अन्यथा
			restorer = &frame->retcode;
	पूर्ण

	अगर (!user_access_begin(frame, माप(*frame)))
		वापस -EFAULT;

	unsafe_put_user(sig, &frame->sig, Efault);
	unsafe_put_sigcontext32(&frame->sc, fp, regs, set, Efault);
	unsafe_put_user(set->sig[1], &frame->extramask[0], Efault);
	unsafe_put_user(ptr_to_compat(restorer), &frame->pretcode, Efault);
	/*
	 * These are actually not used anymore, but left because some
	 * gdb versions depend on them as a marker.
	 */
	unsafe_put_user(*((u64 *)&code), (u64 __user *)frame->retcode, Efault);
	user_access_end();

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->sp = (अचिन्हित दीर्घ) frame;
	regs->ip = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;

	/* Make -mregparm=3 work */
	regs->ax = sig;
	regs->dx = 0;
	regs->cx = 0;

	loadsegment(ds, __USER32_DS);
	loadsegment(es, __USER32_DS);

	regs->cs = __USER32_CS;
	regs->ss = __USER32_DS;

	वापस 0;
Efault:
	user_access_end();
	वापस -EFAULT;
पूर्ण

पूर्णांक ia32_setup_rt_frame(पूर्णांक sig, काष्ठा kसंकेत *ksig,
			compat_sigset_t *set, काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe_ia32 __user *frame;
	व्योम __user *restorer;
	व्योम __user *fp = शून्य;

	/* unsafe_put_user optimizes that पूर्णांकo a single 8 byte store */
	अटल स्थिर काष्ठा अणु
		u8 movl;
		u32 val;
		u16 पूर्णांक80;
		u8  pad;
	पूर्ण __attribute__((packed)) code = अणु
		0xb8,
		__NR_ia32_rt_sigवापस,
		0x80cd,
		0,
	पूर्ण;

	frame = get_sigframe(ksig, regs, माप(*frame), &fp);

	अगर (!user_access_begin(frame, माप(*frame)))
		वापस -EFAULT;

	unsafe_put_user(sig, &frame->sig, Efault);
	unsafe_put_user(ptr_to_compat(&frame->info), &frame->pinfo, Efault);
	unsafe_put_user(ptr_to_compat(&frame->uc), &frame->puc, Efault);

	/* Create the ucontext.  */
	अगर (अटल_cpu_has(X86_FEATURE_XSAVE))
		unsafe_put_user(UC_FP_XSTATE, &frame->uc.uc_flags, Efault);
	अन्यथा
		unsafe_put_user(0, &frame->uc.uc_flags, Efault);
	unsafe_put_user(0, &frame->uc.uc_link, Efault);
	unsafe_compat_save_altstack(&frame->uc.uc_stack, regs->sp, Efault);

	अगर (ksig->ka.sa.sa_flags & SA_RESTORER)
		restorer = ksig->ka.sa.sa_restorer;
	अन्यथा
		restorer = current->mm->context.vdso +
			vdso_image_32.sym___kernel_rt_sigवापस;
	unsafe_put_user(ptr_to_compat(restorer), &frame->pretcode, Efault);

	/*
	 * Not actually used anymore, but left because some gdb
	 * versions need it.
	 */
	unsafe_put_user(*((u64 *)&code), (u64 __user *)frame->retcode, Efault);
	unsafe_put_sigcontext32(&frame->uc.uc_mcontext, fp, regs, set, Efault);
	unsafe_put_user(*(__u64 *)set, (__u64 __user *)&frame->uc.uc_sigmask, Efault);
	user_access_end();

	अगर (__copy_siginfo_to_user32(&frame->info, &ksig->info))
		वापस -EFAULT;

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->sp = (अचिन्हित दीर्घ) frame;
	regs->ip = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;

	/* Make -mregparm=3 work */
	regs->ax = sig;
	regs->dx = (अचिन्हित दीर्घ) &frame->info;
	regs->cx = (अचिन्हित दीर्घ) &frame->uc;

	loadsegment(ds, __USER32_DS);
	loadsegment(es, __USER32_DS);

	regs->cs = __USER32_CS;
	regs->ss = __USER32_DS;

	वापस 0;
Efault:
	user_access_end();
	वापस -EFAULT;
पूर्ण
