<शैली गुरु>
/*
 *  linux/arch/h8300/kernel/संकेत.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

/*
 * uClinux H8/300 support by Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *                and David McCullough <davidm@snapgear.com>
 *
 * Based on
 * Linux/m68k by Hamish Macकरोnald
 */

/*
 * ++roman (07/09/96): implemented संकेत stacks (specially क्रम tosemu on
 * Atari :-) Current limitation: Only one sigstack can be active at one समय.
 * If a second संकेत with SA_ONSTACK set arrives जबतक working on a sigstack,
 * SA_ONSTACK is ignored. This behaviour aव्योमs lots of trouble with nested
 * संकेत handlers!
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/highuid.h>
#समावेश <linux/personality.h>
#समावेश <linux/tty.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/tracehook.h>

#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/ucontext.h>

/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 *
 * Keep the वापस code on the stack quadword aligned!
 * That makes the cache flush below easier.
 */

काष्ठा rt_sigframe अणु
	दीर्घ dummy_er0;
	दीर्घ dummy_vector;
#अगर defined(CONFIG_CPU_H8S)
	लघु dummy_exr;
#पूर्ण_अगर
	दीर्घ dummy_pc;
	अक्षर *pretcode;
	काष्ठा siginfo *pinfo;
	व्योम *puc;
	अचिन्हित अक्षर retcode[8];
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
	पूर्णांक sig;
पूर्ण __packed __aligned(2);

अटल अंतरभूत पूर्णांक
restore_sigcontext(काष्ठा sigcontext *usc, पूर्णांक *pd0)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक ccr;
	अचिन्हित पूर्णांक usp;
	अचिन्हित पूर्णांक er0;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/* restore passed रेजिस्टरs */
#घोषणा COPY(r)  करो अणु err |= get_user(regs->r, &usc->sc_##r); पूर्ण जबतक (0)
	COPY(er1);
	COPY(er2);
	COPY(er3);
	COPY(er5);
	COPY(pc);
	ccr = regs->ccr & 0x10;
	COPY(ccr);
#अघोषित COPY
	regs->ccr &= 0xef;
	regs->ccr |= ccr;
	regs->orig_er0 = -1;		/* disable syscall checks */
	err |= __get_user(usp, &usc->sc_usp);
	regs->sp = usp;

	err |= __get_user(er0, &usc->sc_er0);
	*pd0 = er0;
	वापस err;
पूर्ण

यंत्रlinkage पूर्णांक sys_rt_sigवापस(व्योम)
अणु
	अचिन्हित दीर्घ usp = rdusp();
	काष्ठा rt_sigframe *frame = (काष्ठा rt_sigframe *)(usp - 4);
	sigset_t set;
	पूर्णांक er0;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(&frame->uc.uc_mcontext, &er0))
		जाओ badframe;

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस er0;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

अटल पूर्णांक setup_sigcontext(काष्ठा sigcontext __user *sc, काष्ठा pt_regs *regs,
			     अचिन्हित दीर्घ mask)
अणु
	पूर्णांक err = 0;

	err |= __put_user(regs->er0, &sc->sc_er0);
	err |= __put_user(regs->er1, &sc->sc_er1);
	err |= __put_user(regs->er2, &sc->sc_er2);
	err |= __put_user(regs->er3, &sc->sc_er3);
	err |= __put_user(regs->er4, &sc->sc_er4);
	err |= __put_user(regs->er5, &sc->sc_er5);
	err |= __put_user(regs->er6, &sc->sc_er6);
	err |= __put_user(rdusp(),   &sc->sc_usp);
	err |= __put_user(regs->pc,  &sc->sc_pc);
	err |= __put_user(regs->ccr, &sc->sc_ccr);
	err |= __put_user(mask,      &sc->sc_mask);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम __user *
get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs, माप_प्रकार frame_size)
अणु
	वापस (व्योम __user *)((sigsp(rdusp(), ksig) - frame_size) & -8UL);
पूर्ण

अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
			  काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe *frame;
	पूर्णांक err = 0;
	अचिन्हित अक्षर *ret;

	frame = get_sigframe(ksig, regs, माप(*frame));

	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext.  */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(0, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, rdusp());
	err |= setup_sigcontext(&frame->uc.uc_mcontext, regs, set->sig[0]);
	err |= copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));
	अगर (err)
		वापस -EFAULT;

	/* Set up to वापस from userspace.  */
	ret = (अचिन्हित अक्षर *)&frame->retcode;
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER)
		ret = (अचिन्हित अक्षर *)(ksig->ka.sa.sa_restorer);
	अन्यथा अणु
		/* sub.l er0,er0; mov.b #__NR_rt_sigवापस,r0l; trapa #0 */
		err |= __put_user(0x1a80f800 + (__NR_rt_sigवापस & 0xff),
				  (अचिन्हित दीर्घ *)(frame->retcode + 0));
		err |= __put_user(0x5700,
				  (अचिन्हित लघु *)(frame->retcode + 4));
	पूर्ण
	err |= __put_user(ret, &frame->pretcode);

	अगर (err)
		वापस -EFAULT;

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->sp  = (अचिन्हित दीर्घ)frame;
	regs->pc  = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;
	regs->er0 = ksig->sig;
	regs->er1 = (अचिन्हित दीर्घ)&(frame->info);
	regs->er2 = (अचिन्हित दीर्घ)&frame->uc;
	regs->er5 = current->mm->start_data;	/* GOT base */

	वापस 0;
पूर्ण

अटल व्योम
handle_restart(काष्ठा pt_regs *regs, काष्ठा k_sigaction *ka)
अणु
	चयन (regs->er0) अणु
	हाल -ERESTARTNOHAND:
		अगर (!ka)
			जाओ करो_restart;
		regs->er0 = -EINTR;
		अवरोध;
	हाल -ERESTART_RESTARTBLOCK:
		अगर (!ka) अणु
			regs->er0 = __NR_restart_syscall;
			regs->pc -= 2;
		पूर्ण अन्यथा
			regs->er0 = -EINTR;
		अवरोध;
	हाल -ERESTARTSYS:
		अगर (!(ka->sa.sa_flags & SA_RESTART)) अणु
			regs->er0 = -EINTR;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल -ERESTARTNOINTR:
करो_restart:
		regs->er0 = regs->orig_er0;
		regs->pc -= 2;
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
	/* are we from a प्रणाली call? */
	अगर (regs->orig_er0 >= 0)
		handle_restart(regs, &ksig->ka);

	ret = setup_rt_frame(ksig, oldset, regs);

	संकेत_setup_करोne(ret, ksig, 0);
पूर्ण

/*
 * Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 */
अटल व्योम करो_संकेत(काष्ठा pt_regs *regs)
अणु
	काष्ठा kसंकेत ksig;

	current->thपढ़ो.esp0 = (अचिन्हित दीर्घ) regs;

	अगर (get_संकेत(&ksig)) अणु
		/* Whee!  Actually deliver the संकेत.  */
		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण
	/* Did we come from a प्रणाली call? */
	अगर (regs->orig_er0 >= 0)
		handle_restart(regs, शून्य);

	/* If there's no संकेत to deliver, we just restore the saved mask.  */
	restore_saved_sigmask();
पूर्ण

यंत्रlinkage व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, u32 thपढ़ो_info_flags)
अणु
	अगर (thपढ़ो_info_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs);

	अगर (thपढ़ो_info_flags & _TIF_NOTIFY_RESUME)
		tracehook_notअगरy_resume(regs);
पूर्ण
