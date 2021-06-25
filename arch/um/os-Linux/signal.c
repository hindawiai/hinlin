<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Anton Ivanov (aivanov@अणुbrocade.com,kot-begemot.co.ukपूर्ण)
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2004 PathScale, Inc
 * Copyright (C) 2004 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <strings.h>
#समावेश <as-layout.h>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <sysdep/mcontext.h>
#समावेश <um_दो_स्मृति.h>
#समावेश <sys/ucontext.h>

व्योम (*sig_info[NSIG])(पूर्णांक, काष्ठा siginfo *, काष्ठा uml_pt_regs *) = अणु
	[SIGTRAP]	= relay_संकेत,
	[संक_भ_त्रुटि]	= relay_संकेत,
	[संक_अवैध]	= relay_संकेत,
	[SIGWINCH]	= winch,
	[SIGBUS]	= bus_handler,
	[संक_अंश]	= segv_handler,
	[SIGIO]		= sigio_handler,
पूर्ण;

अटल व्योम sig_handler_common(पूर्णांक sig, काष्ठा siginfo *si, mcontext_t *mc)
अणु
	काष्ठा uml_pt_regs r;
	पूर्णांक save_त्रुटि_सं = त्रुटि_सं;

	r.is_user = 0;
	अगर (sig == संक_अंश) अणु
		/* For segfaults, we want the data from the sigcontext. */
		get_regs_from_mc(&r, mc);
		GET_FAULTINFO_FROM_MC(r.faultinfo, mc);
	पूर्ण

	/* enable संकेतs अगर sig isn't IRQ संकेत */
	अगर ((sig != SIGIO) && (sig != SIGWINCH))
		unblock_संकेतs_trace();

	(*sig_info[sig])(sig, si, &r);

	त्रुटि_सं = save_त्रुटि_सं;
पूर्ण

/*
 * These are the asynchronous संकेतs.  SIGPROF is excluded because we want to
 * be able to profile all of UML, not just the non-critical sections.  If
 * profiling is not thपढ़ो-safe, then that is not my problem.  We can disable
 * profiling when SMP is enabled in that हाल.
 */
#घोषणा SIGIO_BIT 0
#घोषणा SIGIO_MASK (1 << SIGIO_BIT)

#घोषणा SIGALRM_BIT 1
#घोषणा SIGALRM_MASK (1 << SIGALRM_BIT)

अटल पूर्णांक संकेतs_enabled;
अटल अचिन्हित पूर्णांक संकेतs_pending;
अटल अचिन्हित पूर्णांक संकेतs_active = 0;

व्योम sig_handler(पूर्णांक sig, काष्ठा siginfo *si, mcontext_t *mc)
अणु
	पूर्णांक enabled;

	enabled = संकेतs_enabled;
	अगर (!enabled && (sig == SIGIO)) अणु
		संकेतs_pending |= SIGIO_MASK;
		वापस;
	पूर्ण

	block_संकेतs_trace();

	sig_handler_common(sig, si, mc);

	set_संकेतs_trace(enabled);
पूर्ण

अटल व्योम समयr_real_alarm_handler(mcontext_t *mc)
अणु
	काष्ठा uml_pt_regs regs;

	अगर (mc != शून्य)
		get_regs_from_mc(&regs, mc);
	अन्यथा
		स_रखो(&regs, 0, माप(regs));
	समयr_handler(SIGALRM, शून्य, &regs);
पूर्ण

व्योम समयr_alarm_handler(पूर्णांक sig, काष्ठा siginfo *unused_si, mcontext_t *mc)
अणु
	पूर्णांक enabled;

	enabled = संकेतs_enabled;
	अगर (!संकेतs_enabled) अणु
		संकेतs_pending |= SIGALRM_MASK;
		वापस;
	पूर्ण

	block_संकेतs_trace();

	संकेतs_active |= SIGALRM_MASK;

	समयr_real_alarm_handler(mc);

	संकेतs_active &= ~SIGALRM_MASK;

	set_संकेतs_trace(enabled);
पूर्ण

व्योम deliver_alarm(व्योम) अणु
    समयr_alarm_handler(SIGALRM, शून्य, शून्य);
पूर्ण

व्योम समयr_set_संकेत_handler(व्योम)
अणु
	set_handler(SIGALRM);
पूर्ण

व्योम set_sigstack(व्योम *sig_stack, पूर्णांक size)
अणु
	stack_t stack = अणु
		.ss_flags = 0,
		.ss_sp = sig_stack,
		.ss_size = size - माप(व्योम *)
	पूर्ण;

	अगर (sigaltstack(&stack, शून्य) != 0)
		panic("enabling signal stack failed, errno = %d\n", त्रुटि_सं);
पूर्ण

अटल व्योम sigusr1_handler(पूर्णांक sig, काष्ठा siginfo *unused_si, mcontext_t *mc)
अणु
	uml_pm_wake();
पूर्ण

व्योम रेजिस्टर_pm_wake_संकेत(व्योम)
अणु
	set_handler(SIGUSR1);
पूर्ण

अटल व्योम (*handlers[_NSIG])(पूर्णांक sig, काष्ठा siginfo *si, mcontext_t *mc) = अणु
	[संक_अंश] = sig_handler,
	[SIGBUS] = sig_handler,
	[संक_अवैध] = sig_handler,
	[संक_भ_त्रुटि] = sig_handler,
	[SIGTRAP] = sig_handler,

	[SIGIO] = sig_handler,
	[SIGWINCH] = sig_handler,
	[SIGALRM] = समयr_alarm_handler,

	[SIGUSR1] = sigusr1_handler,
पूर्ण;

अटल व्योम hard_handler(पूर्णांक sig, siginfo_t *si, व्योम *p)
अणु
	ucontext_t *uc = p;
	mcontext_t *mc = &uc->uc_mcontext;
	अचिन्हित दीर्घ pending = 1UL << sig;

	करो अणु
		पूर्णांक nested, bail;

		/*
		 * pending comes back with one bit set क्रम each
		 * पूर्णांकerrupt that arrived जबतक setting up the stack,
		 * plus a bit क्रम this पूर्णांकerrupt, plus the zero bit is
		 * set अगर this is a nested पूर्णांकerrupt.
		 * If bail is true, then we पूर्णांकerrupted another
		 * handler setting up the stack.  In this हाल, we
		 * have to वापस, and the upper handler will deal
		 * with this पूर्णांकerrupt.
		 */
		bail = to_irq_stack(&pending);
		अगर (bail)
			वापस;

		nested = pending & 1;
		pending &= ~1;

		जबतक ((sig = ffs(pending)) != 0)अणु
			sig--;
			pending &= ~(1 << sig);
			(*handlers[sig])(sig, (काष्ठा siginfo *)si, mc);
		पूर्ण

		/*
		 * Again, pending comes back with a mask of संकेतs
		 * that arrived जबतक tearing करोwn the stack.  If this
		 * is non-zero, we just go back, set up the stack
		 * again, and handle the new पूर्णांकerrupts.
		 */
		अगर (!nested)
			pending = from_irq_stack(nested);
	पूर्ण जबतक (pending);
पूर्ण

व्योम set_handler(पूर्णांक sig)
अणु
	काष्ठा sigaction action;
	पूर्णांक flags = SA_SIGINFO | SA_ONSTACK;
	sigset_t sig_mask;

	action.sa_sigaction = hard_handler;

	/* block irq ones */
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGIO);
	sigaddset(&action.sa_mask, SIGWINCH);
	sigaddset(&action.sa_mask, SIGALRM);

	अगर (sig == संक_अंश)
		flags |= SA_NODEFER;

	अगर (sigismember(&action.sa_mask, sig))
		flags |= SA_RESTART; /* अगर it's an irq संकेत */

	action.sa_flags = flags;
	action.sa_restorer = शून्य;
	अगर (sigaction(sig, &action, शून्य) < 0)
		panic("sigaction failed - errno = %d\n", त्रुटि_सं);

	sigemptyset(&sig_mask);
	sigaddset(&sig_mask, sig);
	अगर (sigprocmask(SIG_UNBLOCK, &sig_mask, शून्य) < 0)
		panic("sigprocmask failed - errno = %d\n", त्रुटि_सं);
पूर्ण

व्योम send_sigio_to_self(व्योम)
अणु
	समाप्त(os_getpid(), SIGIO);
पूर्ण

पूर्णांक change_sig(पूर्णांक संकेत, पूर्णांक on)
अणु
	sigset_t sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, संकेत);
	अगर (sigprocmask(on ? SIG_UNBLOCK : SIG_BLOCK, &sigset, शून्य) < 0)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

व्योम block_संकेतs(व्योम)
अणु
	संकेतs_enabled = 0;
	/*
	 * This must वापस with संकेतs disabled, so this barrier
	 * ensures that ग_लिखोs are flushed out beक्रमe the वापस.
	 * This might matter अगर gcc figures out how to अंतरभूत this and
	 * decides to shuffle this code पूर्णांकo the caller.
	 */
	barrier();
पूर्ण

व्योम unblock_संकेतs(व्योम)
अणु
	पूर्णांक save_pending;

	अगर (संकेतs_enabled == 1)
		वापस;

	संकेतs_enabled = 1;
#अगर_घोषित UML_CONFIG_UML_TIME_TRAVEL_SUPPORT
	deliver_समय_प्रकारravel_irqs();
#पूर्ण_अगर

	/*
	 * We loop because the IRQ handler वापसs with पूर्णांकerrupts off.  So,
	 * पूर्णांकerrupts may have arrived and we need to re-enable them and
	 * recheck संकेतs_pending.
	 */
	जबतक (1) अणु
		/*
		 * Save and reset save_pending after enabling संकेतs.  This
		 * way, संकेतs_pending won't be changed while we're पढ़ोing it.
		 *
		 * Setting संकेतs_enabled and पढ़ोing संकेतs_pending must
		 * happen in this order, so have the barrier here.
		 */
		barrier();

		save_pending = संकेतs_pending;
		अगर (save_pending == 0)
			वापस;

		संकेतs_pending = 0;

		/*
		 * We have pending पूर्णांकerrupts, so disable संकेतs, as the
		 * handlers expect them off when they are called.  They will
		 * be enabled again above. We need to trace this, as we're
		 * expected to be enabling पूर्णांकerrupts alपढ़ोy, but any more
		 * tracing that happens inside the handlers we call क्रम the
		 * pending संकेतs will mess up the tracing state.
		 */
		संकेतs_enabled = 0;
		um_trace_संकेतs_off();

		/*
		 * Deal with SIGIO first because the alarm handler might
		 * schedule, leaving the pending SIGIO stअक्रमed until we come
		 * back here.
		 *
		 * SIGIO's handler doesn't use siginfo or mcontext,
		 * so they can be शून्य.
		 */
		अगर (save_pending & SIGIO_MASK)
			sig_handler_common(SIGIO, शून्य, शून्य);

		/* Do not reenter the handler */

		अगर ((save_pending & SIGALRM_MASK) && (!(संकेतs_active & SIGALRM_MASK)))
			समयr_real_alarm_handler(शून्य);

		/* Rerun the loop only अगर there is still pending SIGIO and not in TIMER handler */

		अगर (!(संकेतs_pending & SIGIO_MASK) && (संकेतs_active & SIGALRM_MASK))
			वापस;

		/* Re-enable संकेतs and trace that we're करोing so. */
		um_trace_संकेतs_on();
		संकेतs_enabled = 1;
	पूर्ण
पूर्ण

पूर्णांक get_संकेतs(व्योम)
अणु
	वापस संकेतs_enabled;
पूर्ण

पूर्णांक set_संकेतs(पूर्णांक enable)
अणु
	पूर्णांक ret;
	अगर (संकेतs_enabled == enable)
		वापस enable;

	ret = संकेतs_enabled;
	अगर (enable)
		unblock_संकेतs();
	अन्यथा block_संकेतs();

	वापस ret;
पूर्ण

पूर्णांक set_संकेतs_trace(पूर्णांक enable)
अणु
	पूर्णांक ret;
	अगर (संकेतs_enabled == enable)
		वापस enable;

	ret = संकेतs_enabled;
	अगर (enable)
		unblock_संकेतs_trace();
	अन्यथा
		block_संकेतs_trace();

	वापस ret;
पूर्ण

पूर्णांक os_is_संकेत_stack(व्योम)
अणु
	stack_t ss;
	sigaltstack(शून्य, &ss);

	वापस ss.ss_flags & SS_ONSTACK;
पूर्ण
