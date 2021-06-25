<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 2000, 2001, 2002 Andi Kleen, SuSE Lअसल
 *  Copyright (C) 2011	Don Zickus Red Hat, Inc.
 *
 *  Pentium III FXSR, SSE support
 *	Gareth Hughes <gareth@valinux.com>, May 2000
 */

/*
 * Handle hardware traps and faults.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/nmi.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/mach_traps.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/sev.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/nmi.h>

काष्ठा nmi_desc अणु
	raw_spinlock_t lock;
	काष्ठा list_head head;
पूर्ण;

अटल काष्ठा nmi_desc nmi_desc[NMI_MAX] = 
अणु
	अणु
		.lock = __RAW_SPIN_LOCK_UNLOCKED(&nmi_desc[0].lock),
		.head = LIST_HEAD_INIT(nmi_desc[0].head),
	पूर्ण,
	अणु
		.lock = __RAW_SPIN_LOCK_UNLOCKED(&nmi_desc[1].lock),
		.head = LIST_HEAD_INIT(nmi_desc[1].head),
	पूर्ण,
	अणु
		.lock = __RAW_SPIN_LOCK_UNLOCKED(&nmi_desc[2].lock),
		.head = LIST_HEAD_INIT(nmi_desc[2].head),
	पूर्ण,
	अणु
		.lock = __RAW_SPIN_LOCK_UNLOCKED(&nmi_desc[3].lock),
		.head = LIST_HEAD_INIT(nmi_desc[3].head),
	पूर्ण,

पूर्ण;

काष्ठा nmi_stats अणु
	अचिन्हित पूर्णांक normal;
	अचिन्हित पूर्णांक unknown;
	अचिन्हित पूर्णांक बाह्यal;
	अचिन्हित पूर्णांक swallow;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा nmi_stats, nmi_stats);

अटल पूर्णांक ignore_nmis __पढ़ो_mostly;

पूर्णांक unknown_nmi_panic;
/*
 * Prevent NMI reason port (0x61) being accessed simultaneously, can
 * only be used in NMI handler.
 */
अटल DEFINE_RAW_SPINLOCK(nmi_reason_lock);

अटल पूर्णांक __init setup_unknown_nmi_panic(अक्षर *str)
अणु
	unknown_nmi_panic = 1;
	वापस 1;
पूर्ण
__setup("unknown_nmi_panic", setup_unknown_nmi_panic);

#घोषणा nmi_to_desc(type) (&nmi_desc[type])

अटल u64 nmi_दीर्घest_ns = 1 * NSEC_PER_MSEC;

अटल पूर्णांक __init nmi_warning_debugfs(व्योम)
अणु
	debugfs_create_u64("nmi_longest_ns", 0644,
			arch_debugfs_dir, &nmi_दीर्घest_ns);
	वापस 0;
पूर्ण
fs_initcall(nmi_warning_debugfs);

अटल व्योम nmi_check_duration(काष्ठा nmiaction *action, u64 duration)
अणु
	पूर्णांक reमुख्यder_ns, decimal_msecs;

	अगर (duration < nmi_दीर्घest_ns || duration < action->max_duration)
		वापस;

	action->max_duration = duration;

	reमुख्यder_ns = करो_भाग(duration, (1000 * 1000));
	decimal_msecs = reमुख्यder_ns / 1000;

	prपूर्णांकk_ratelimited(KERN_INFO
		"INFO: NMI handler (%ps) took too long to run: %lld.%03d msecs\n",
		action->handler, duration, decimal_msecs);
पूर्ण

अटल पूर्णांक nmi_handle(अचिन्हित पूर्णांक type, काष्ठा pt_regs *regs)
अणु
	काष्ठा nmi_desc *desc = nmi_to_desc(type);
	काष्ठा nmiaction *a;
	पूर्णांक handled=0;

	rcu_पढ़ो_lock();

	/*
	 * NMIs are edge-triggered, which means अगर you have enough
	 * of them concurrently, you can lose some because only one
	 * can be latched at any given समय.  Walk the whole list
	 * to handle those situations.
	 */
	list_क्रम_each_entry_rcu(a, &desc->head, list) अणु
		पूर्णांक thishandled;
		u64 delta;

		delta = sched_घड़ी();
		thishandled = a->handler(type, regs);
		handled += thishandled;
		delta = sched_घड़ी() - delta;
		trace_nmi_handler(a->handler, (पूर्णांक)delta, thishandled);

		nmi_check_duration(a, delta);
	पूर्ण

	rcu_पढ़ो_unlock();

	/* वापस total number of NMI events handled */
	वापस handled;
पूर्ण
NOKPROBE_SYMBOL(nmi_handle);

पूर्णांक __रेजिस्टर_nmi_handler(अचिन्हित पूर्णांक type, काष्ठा nmiaction *action)
अणु
	काष्ठा nmi_desc *desc = nmi_to_desc(type);
	अचिन्हित दीर्घ flags;

	अगर (!action->handler)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&desc->lock, flags);

	/*
	 * Indicate अगर there are multiple registrations on the
	 * पूर्णांकernal NMI handler call chains (SERR and IO_CHECK).
	 */
	WARN_ON_ONCE(type == NMI_SERR && !list_empty(&desc->head));
	WARN_ON_ONCE(type == NMI_IO_CHECK && !list_empty(&desc->head));

	/*
	 * some handlers need to be executed first otherwise a fake
	 * event confuses some handlers (kdump uses this flag)
	 */
	अगर (action->flags & NMI_FLAG_FIRST)
		list_add_rcu(&action->list, &desc->head);
	अन्यथा
		list_add_tail_rcu(&action->list, &desc->head);
	
	raw_spin_unlock_irqrestore(&desc->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__रेजिस्टर_nmi_handler);

व्योम unरेजिस्टर_nmi_handler(अचिन्हित पूर्णांक type, स्थिर अक्षर *name)
अणु
	काष्ठा nmi_desc *desc = nmi_to_desc(type);
	काष्ठा nmiaction *n;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&desc->lock, flags);

	list_क्रम_each_entry_rcu(n, &desc->head, list) अणु
		/*
		 * the name passed in to describe the nmi handler
		 * is used as the lookup key
		 */
		अगर (!म_भेद(n->name, name)) अणु
			WARN(in_nmi(),
				"Trying to free NMI (%s) from NMI context!\n", n->name);
			list_del_rcu(&n->list);
			अवरोध;
		पूर्ण
	पूर्ण

	raw_spin_unlock_irqrestore(&desc->lock, flags);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_nmi_handler);

अटल व्योम
pci_serr_error(अचिन्हित अक्षर reason, काष्ठा pt_regs *regs)
अणु
	/* check to see अगर anyone रेजिस्टरed against these types of errors */
	अगर (nmi_handle(NMI_SERR, regs))
		वापस;

	pr_emerg("NMI: PCI system error (SERR) for reason %02x on CPU %d.\n",
		 reason, smp_processor_id());

	अगर (panic_on_unrecovered_nmi)
		nmi_panic(regs, "NMI: Not continuing");

	pr_emerg("Dazed and confused, but trying to continue\n");

	/* Clear and disable the PCI SERR error line. */
	reason = (reason & NMI_REASON_CLEAR_MASK) | NMI_REASON_CLEAR_SERR;
	outb(reason, NMI_REASON_PORT);
पूर्ण
NOKPROBE_SYMBOL(pci_serr_error);

अटल व्योम
io_check_error(अचिन्हित अक्षर reason, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ i;

	/* check to see अगर anyone रेजिस्टरed against these types of errors */
	अगर (nmi_handle(NMI_IO_CHECK, regs))
		वापस;

	pr_emerg(
	"NMI: IOCK error (debug interrupt?) for reason %02x on CPU %d.\n",
		 reason, smp_processor_id());
	show_regs(regs);

	अगर (panic_on_io_nmi) अणु
		nmi_panic(regs, "NMI IOCK error: Not continuing");

		/*
		 * If we end up here, it means we have received an NMI जबतक
		 * processing panic(). Simply वापस without delaying and
		 * re-enabling NMIs.
		 */
		वापस;
	पूर्ण

	/* Re-enable the IOCK line, रुको क्रम a few seconds */
	reason = (reason & NMI_REASON_CLEAR_MASK) | NMI_REASON_CLEAR_IOCHK;
	outb(reason, NMI_REASON_PORT);

	i = 20000;
	जबतक (--i) अणु
		touch_nmi_watchकरोg();
		udelay(100);
	पूर्ण

	reason &= ~NMI_REASON_CLEAR_IOCHK;
	outb(reason, NMI_REASON_PORT);
पूर्ण
NOKPROBE_SYMBOL(io_check_error);

अटल व्योम
unknown_nmi_error(अचिन्हित अक्षर reason, काष्ठा pt_regs *regs)
अणु
	पूर्णांक handled;

	/*
	 * Use 'false' as back-to-back NMIs are dealt with one level up.
	 * Of course this makes having multiple 'unknown' handlers useless
	 * as only the first one is ever run (unless it can actually determine
	 * अगर it caused the NMI)
	 */
	handled = nmi_handle(NMI_UNKNOWN, regs);
	अगर (handled) अणु
		__this_cpu_add(nmi_stats.unknown, handled);
		वापस;
	पूर्ण

	__this_cpu_add(nmi_stats.unknown, 1);

	pr_emerg("Uhhuh. NMI received for unknown reason %02x on CPU %d.\n",
		 reason, smp_processor_id());

	pr_emerg("Do you have a strange power saving mode enabled?\n");
	अगर (unknown_nmi_panic || panic_on_unrecovered_nmi)
		nmi_panic(regs, "NMI: Not continuing");

	pr_emerg("Dazed and confused, but trying to continue\n");
पूर्ण
NOKPROBE_SYMBOL(unknown_nmi_error);

अटल DEFINE_PER_CPU(bool, swallow_nmi);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, last_nmi_rip);

अटल noinstr व्योम शेष_करो_nmi(काष्ठा pt_regs *regs)
अणु
	अचिन्हित अक्षर reason = 0;
	पूर्णांक handled;
	bool b2b = false;

	/*
	 * CPU-specअगरic NMI must be processed beक्रमe non-CPU-specअगरic
	 * NMI, otherwise we may lose it, because the CPU-specअगरic
	 * NMI can not be detected/processed on other CPUs.
	 */

	/*
	 * Back-to-back NMIs are पूर्णांकeresting because they can either
	 * be two NMI or more than two NMIs (any thing over two is dropped
	 * due to NMI being edge-triggered).  If this is the second half
	 * of the back-to-back NMI, assume we dropped things and process
	 * more handlers.  Otherwise reset the 'swallow' NMI behaviour
	 */
	अगर (regs->ip == __this_cpu_पढ़ो(last_nmi_rip))
		b2b = true;
	अन्यथा
		__this_cpu_ग_लिखो(swallow_nmi, false);

	__this_cpu_ग_लिखो(last_nmi_rip, regs->ip);

	instrumentation_begin();

	handled = nmi_handle(NMI_LOCAL, regs);
	__this_cpu_add(nmi_stats.normal, handled);
	अगर (handled) अणु
		/*
		 * There are हालs when a NMI handler handles multiple
		 * events in the current NMI.  One of these events may
		 * be queued क्रम in the next NMI.  Because the event is
		 * alपढ़ोy handled, the next NMI will result in an unknown
		 * NMI.  Instead lets flag this क्रम a potential NMI to
		 * swallow.
		 */
		अगर (handled > 1)
			__this_cpu_ग_लिखो(swallow_nmi, true);
		जाओ out;
	पूर्ण

	/*
	 * Non-CPU-specअगरic NMI: NMI sources can be processed on any CPU.
	 *
	 * Another CPU may be processing panic routines जबतक holding
	 * nmi_reason_lock. Check अगर the CPU issued the IPI क्रम crash dumping,
	 * and अगर so, call its callback directly.  If there is no CPU preparing
	 * crash dump, we simply loop here.
	 */
	जबतक (!raw_spin_trylock(&nmi_reason_lock)) अणु
		run_crash_ipi_callback(regs);
		cpu_relax();
	पूर्ण

	reason = x86_platक्रमm.get_nmi_reason();

	अगर (reason & NMI_REASON_MASK) अणु
		अगर (reason & NMI_REASON_SERR)
			pci_serr_error(reason, regs);
		अन्यथा अगर (reason & NMI_REASON_IOCHK)
			io_check_error(reason, regs);
#अगर_घोषित CONFIG_X86_32
		/*
		 * Reनिश्चित NMI in हाल it became active
		 * meanजबतक as it's edge-triggered:
		 */
		reनिश्चित_nmi();
#पूर्ण_अगर
		__this_cpu_add(nmi_stats.बाह्यal, 1);
		raw_spin_unlock(&nmi_reason_lock);
		जाओ out;
	पूर्ण
	raw_spin_unlock(&nmi_reason_lock);

	/*
	 * Only one NMI can be latched at a समय.  To handle
	 * this we may process multiple nmi handlers at once to
	 * cover the हाल where an NMI is dropped.  The करोwnside
	 * to this approach is we may process an NMI prematurely,
	 * जबतक its real NMI is sitting latched.  This will cause
	 * an unknown NMI on the next run of the NMI processing.
	 *
	 * We tried to flag that condition above, by setting the
	 * swallow_nmi flag when we process more than one event.
	 * This condition is also only present on the second half
	 * of a back-to-back NMI, so we flag that condition too.
	 *
	 * If both are true, we assume we alपढ़ोy processed this
	 * NMI previously and we swallow it.  Otherwise we reset
	 * the logic.
	 *
	 * There are scenarios where we may accidentally swallow
	 * a 'real' unknown NMI.  For example, जबतक processing
	 * a perf NMI another perf NMI comes in aदीर्घ with a
	 * 'real' unknown NMI.  These two NMIs get combined पूर्णांकo
	 * one (as described above).  When the next NMI माला_लो
	 * processed, it will be flagged by perf as handled, but
	 * no one will know that there was a 'real' unknown NMI sent
	 * also.  As a result it माला_लो swallowed.  Or अगर the first
	 * perf NMI वापसs two events handled then the second
	 * NMI will get eaten by the logic below, again losing a
	 * 'real' unknown NMI.  But this is the best we can करो
	 * क्रम now.
	 */
	अगर (b2b && __this_cpu_पढ़ो(swallow_nmi))
		__this_cpu_add(nmi_stats.swallow, 1);
	अन्यथा
		unknown_nmi_error(reason, regs);

out:
	instrumentation_end();
पूर्ण

/*
 * NMIs can page fault or hit अवरोधpoपूर्णांकs which will cause it to lose
 * its NMI context with the CPU when the अवरोधpoपूर्णांक or page fault करोes an IRET.
 *
 * As a result, NMIs can nest अगर NMIs get unmasked due an IRET during
 * NMI processing.  On x86_64, the यंत्र glue protects us from nested NMIs
 * अगर the outer NMI came from kernel mode, but we can still nest अगर the
 * outer NMI came from user mode.
 *
 * To handle these nested NMIs, we have three states:
 *
 *  1) not running
 *  2) executing
 *  3) latched
 *
 * When no NMI is in progress, it is in the "not running" state.
 * When an NMI comes in, it goes पूर्णांकo the "executing" state.
 * Normally, अगर another NMI is triggered, it करोes not पूर्णांकerrupt
 * the running NMI and the HW will simply latch it so that when
 * the first NMI finishes, it will restart the second NMI.
 * (Note, the latch is binary, thus multiple NMIs triggering,
 *  when one is running, are ignored. Only one NMI is restarted.)
 *
 * If an NMI executes an iret, another NMI can preempt it. We करो not
 * want to allow this new NMI to run, but we want to execute it when the
 * first one finishes.  We set the state to "latched", and the निकास of
 * the first NMI will perक्रमm a dec_वापस, अगर the result is zero
 * (NOT_RUNNING), then it will simply निकास the NMI handler. If not, the
 * dec_वापस would have set the state to NMI_EXECUTING (what we want it
 * to be when we are running). In this हाल, we simply jump back to
 * rerun the NMI handler again, and restart the 'latched' NMI.
 *
 * No trap (अवरोधpoपूर्णांक or page fault) should be hit beक्रमe nmi_restart,
 * thus there is no race between the first check of state क्रम NOT_RUNNING
 * and setting it to NMI_EXECUTING. The HW will prevent nested NMIs
 * at this poपूर्णांक.
 *
 * In हाल the NMI takes a page fault, we need to save off the CR2
 * because the NMI could have preempted another page fault and corrupt
 * the CR2 that is about to be पढ़ो. As nested NMIs must be restarted
 * and they can not take अवरोधpoपूर्णांकs or page faults, the update of the
 * CR2 must be करोne beक्रमe converting the nmi state back to NOT_RUNNING.
 * Otherwise, there would be a race of another nested NMI coming in
 * after setting state to NOT_RUNNING but beक्रमe updating the nmi_cr2.
 */
क्रमागत nmi_states अणु
	NMI_NOT_RUNNING = 0,
	NMI_EXECUTING,
	NMI_LATCHED,
पूर्ण;
अटल DEFINE_PER_CPU(क्रमागत nmi_states, nmi_state);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, nmi_cr2);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, nmi_dr7);

DEFINE_IDTENTRY_RAW(exc_nmi)
अणु
	irqentry_state_t irq_state;

	/*
	 * Re-enable NMIs right here when running as an SEV-ES guest. This might
	 * cause nested NMIs, but those can be handled safely.
	 */
	sev_es_nmi_complete();

	अगर (IS_ENABLED(CONFIG_SMP) && arch_cpu_is_offline(smp_processor_id()))
		वापस;

	अगर (this_cpu_पढ़ो(nmi_state) != NMI_NOT_RUNNING) अणु
		this_cpu_ग_लिखो(nmi_state, NMI_LATCHED);
		वापस;
	पूर्ण
	this_cpu_ग_लिखो(nmi_state, NMI_EXECUTING);
	this_cpu_ग_लिखो(nmi_cr2, पढ़ो_cr2());
nmi_restart:

	/*
	 * Needs to happen beक्रमe DR7 is accessed, because the hypervisor can
	 * पूर्णांकercept DR7 पढ़ोs/ग_लिखोs, turning those पूर्णांकo #VC exceptions.
	 */
	sev_es_ist_enter(regs);

	this_cpu_ग_लिखो(nmi_dr7, local_db_save());

	irq_state = irqentry_nmi_enter(regs);

	inc_irq_stat(__nmi_count);

	अगर (!ignore_nmis)
		शेष_करो_nmi(regs);

	irqentry_nmi_निकास(regs, irq_state);

	local_db_restore(this_cpu_पढ़ो(nmi_dr7));

	sev_es_ist_निकास();

	अगर (unlikely(this_cpu_पढ़ो(nmi_cr2) != पढ़ो_cr2()))
		ग_लिखो_cr2(this_cpu_पढ़ो(nmi_cr2));
	अगर (this_cpu_dec_वापस(nmi_state))
		जाओ nmi_restart;

	अगर (user_mode(regs))
		mds_user_clear_cpu_buffers();
पूर्ण

#अगर defined(CONFIG_X86_64) && IS_ENABLED(CONFIG_KVM_INTEL)
DEFINE_IDTENTRY_RAW(exc_nmi_noist)
अणु
	exc_nmi(regs);
पूर्ण
#पूर्ण_अगर
#अगर IS_MODULE(CONFIG_KVM_INTEL)
EXPORT_SYMBOL_GPL(यंत्र_exc_nmi_noist);
#पूर्ण_अगर

व्योम stop_nmi(व्योम)
अणु
	ignore_nmis++;
पूर्ण

व्योम restart_nmi(व्योम)
अणु
	ignore_nmis--;
पूर्ण

/* reset the back-to-back NMI logic */
व्योम local_touch_nmi(व्योम)
अणु
	__this_cpu_ग_लिखो(last_nmi_rip, 0);
पूर्ण
EXPORT_SYMBOL_GPL(local_touch_nmi);
