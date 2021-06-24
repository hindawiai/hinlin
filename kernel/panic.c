<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/kernel/panic.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/*
 * This function is used through-out the kernel (including mm and fs)
 * to indicate a major problem.
 */
#समावेश <linux/debug_locks.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/reboot.h>
#समावेश <linux/delay.h>
#समावेश <linux/kexec.h>
#समावेश <linux/sched.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/init.h>
#समावेश <linux/nmi.h>
#समावेश <linux/console.h>
#समावेश <linux/bug.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/debugfs.h>
#समावेश <यंत्र/sections.h>

#घोषणा PANIC_TIMER_STEP 100
#घोषणा PANIC_BLINK_SPD 18

#अगर_घोषित CONFIG_SMP
/*
 * Should we dump all CPUs backtraces in an oops event?
 * Defaults to 0, can be changed via sysctl.
 */
अचिन्हित पूर्णांक __पढ़ो_mostly sysctl_oops_all_cpu_backtrace;
#पूर्ण_अगर /* CONFIG_SMP */

पूर्णांक panic_on_oops = CONFIG_PANIC_ON_OOPS_VALUE;
अटल अचिन्हित दीर्घ taपूर्णांकed_mask =
	IS_ENABLED(CONFIG_GCC_PLUGIN_RANDSTRUCT) ? (1 << TAINT_RANDSTRUCT) : 0;
अटल पूर्णांक छोड़ो_on_oops;
अटल पूर्णांक छोड़ो_on_oops_flag;
अटल DEFINE_SPINLOCK(छोड़ो_on_oops_lock);
bool crash_kexec_post_notअगरiers;
पूर्णांक panic_on_warn __पढ़ो_mostly;
अचिन्हित दीर्घ panic_on_taपूर्णांक;
bool panic_on_taपूर्णांक_nousertaपूर्णांक = false;

पूर्णांक panic_समयout = CONFIG_PANIC_TIMEOUT;
EXPORT_SYMBOL_GPL(panic_समयout);

#घोषणा PANIC_PRINT_TASK_INFO		0x00000001
#घोषणा PANIC_PRINT_MEM_INFO		0x00000002
#घोषणा PANIC_PRINT_TIMER_INFO		0x00000004
#घोषणा PANIC_PRINT_LOCK_INFO		0x00000008
#घोषणा PANIC_PRINT_FTRACE_INFO		0x00000010
#घोषणा PANIC_PRINT_ALL_PRINTK_MSG	0x00000020
अचिन्हित दीर्घ panic_prपूर्णांक;

ATOMIC_NOTIFIER_HEAD(panic_notअगरier_list);

EXPORT_SYMBOL(panic_notअगरier_list);

अटल दीर्घ no_blink(पूर्णांक state)
अणु
	वापस 0;
पूर्ण

/* Returns how दीर्घ it रुकोed in ms */
दीर्घ (*panic_blink)(पूर्णांक state);
EXPORT_SYMBOL(panic_blink);

/*
 * Stop ourself in panic -- architecture code may override this
 */
व्योम __weak panic_smp_self_stop(व्योम)
अणु
	जबतक (1)
		cpu_relax();
पूर्ण

/*
 * Stop ourselves in NMI context अगर another CPU has alपढ़ोy panicked. Arch code
 * may override this to prepare क्रम crash dumping, e.g. save regs info.
 */
व्योम __weak nmi_panic_self_stop(काष्ठा pt_regs *regs)
अणु
	panic_smp_self_stop();
पूर्ण

/*
 * Stop other CPUs in panic.  Architecture dependent code may override this
 * with more suitable version.  For example, अगर the architecture supports
 * crash dump, it should save रेजिस्टरs of each stopped CPU and disable
 * per-CPU features such as भवization extensions.
 */
व्योम __weak crash_smp_send_stop(व्योम)
अणु
	अटल पूर्णांक cpus_stopped;

	/*
	 * This function can be called twice in panic path, but obviously
	 * we execute this only once.
	 */
	अगर (cpus_stopped)
		वापस;

	/*
	 * Note smp_send_stop is the usual smp shutकरोwn function, which
	 * unक्रमtunately means it may not be hardened to work in a panic
	 * situation.
	 */
	smp_send_stop();
	cpus_stopped = 1;
पूर्ण

atomic_t panic_cpu = ATOMIC_INIT(PANIC_CPU_INVALID);

/*
 * A variant of panic() called from NMI context. We वापस अगर we've alपढ़ोy
 * panicked on this CPU. If another CPU alपढ़ोy panicked, loop in
 * nmi_panic_self_stop() which can provide architecture dependent code such
 * as saving रेजिस्टर state क्रम crash dump.
 */
व्योम nmi_panic(काष्ठा pt_regs *regs, स्थिर अक्षर *msg)
अणु
	पूर्णांक old_cpu, cpu;

	cpu = raw_smp_processor_id();
	old_cpu = atomic_cmpxchg(&panic_cpu, PANIC_CPU_INVALID, cpu);

	अगर (old_cpu == PANIC_CPU_INVALID)
		panic("%s", msg);
	अन्यथा अगर (old_cpu != cpu)
		nmi_panic_self_stop(regs);
पूर्ण
EXPORT_SYMBOL(nmi_panic);

अटल व्योम panic_prपूर्णांक_sys_info(व्योम)
अणु
	अगर (panic_prपूर्णांक & PANIC_PRINT_ALL_PRINTK_MSG)
		console_flush_on_panic(CONSOLE_REPLAY_ALL);

	अगर (panic_prपूर्णांक & PANIC_PRINT_TASK_INFO)
		show_state();

	अगर (panic_prपूर्णांक & PANIC_PRINT_MEM_INFO)
		show_mem(0, शून्य);

	अगर (panic_prपूर्णांक & PANIC_PRINT_TIMER_INFO)
		sysrq_समयr_list_show();

	अगर (panic_prपूर्णांक & PANIC_PRINT_LOCK_INFO)
		debug_show_all_locks();

	अगर (panic_prपूर्णांक & PANIC_PRINT_FTRACE_INFO)
		ftrace_dump(DUMP_ALL);
पूर्ण

/**
 *	panic - halt the प्रणाली
 *	@fmt: The text string to prपूर्णांक
 *
 *	Display a message, then perक्रमm cleanups.
 *
 *	This function never वापसs.
 */
व्योम panic(स्थिर अक्षर *fmt, ...)
अणु
	अटल अक्षर buf[1024];
	बहु_सूची args;
	दीर्घ i, i_next = 0, len;
	पूर्णांक state = 0;
	पूर्णांक old_cpu, this_cpu;
	bool _crash_kexec_post_notअगरiers = crash_kexec_post_notअगरiers;

	/*
	 * Disable local पूर्णांकerrupts. This will prevent panic_smp_self_stop
	 * from deadlocking the first cpu that invokes the panic, since
	 * there is nothing to prevent an पूर्णांकerrupt handler (that runs
	 * after setting panic_cpu) from invoking panic() again.
	 */
	local_irq_disable();
	preempt_disable_notrace();

	/*
	 * It's possible to come here directly from a panic-निश्चितion and
	 * not have preempt disabled. Some functions called from here want
	 * preempt to be disabled. No poपूर्णांक enabling it later though...
	 *
	 * Only one CPU is allowed to execute the panic code from here. For
	 * multiple parallel invocations of panic, all other CPUs either
	 * stop themself or will रुको until they are stopped by the 1st CPU
	 * with smp_send_stop().
	 *
	 * `old_cpu == PANIC_CPU_INVALID' means this is the 1st CPU which
	 * comes here, so go ahead.
	 * `old_cpu == this_cpu' means we came from nmi_panic() which sets
	 * panic_cpu to this CPU.  In this हाल, this is also the 1st CPU.
	 */
	this_cpu = raw_smp_processor_id();
	old_cpu  = atomic_cmpxchg(&panic_cpu, PANIC_CPU_INVALID, this_cpu);

	अगर (old_cpu != PANIC_CPU_INVALID && old_cpu != this_cpu)
		panic_smp_self_stop();

	console_verbose();
	bust_spinlocks(1);
	बहु_शुरू(args, fmt);
	len = vscnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);

	अगर (len && buf[len - 1] == '\n')
		buf[len - 1] = '\0';

	pr_emerg("Kernel panic - not syncing: %s\n", buf);
#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
	/*
	 * Aव्योम nested stack-dumping अगर a panic occurs during oops processing
	 */
	अगर (!test_taपूर्णांक(TAINT_DIE) && oops_in_progress <= 1)
		dump_stack();
#पूर्ण_अगर

	/*
	 * If kgdb is enabled, give it a chance to run beक्रमe we stop all
	 * the other CPUs or अन्यथा we won't be able to debug processes left
	 * running on them.
	 */
	kgdb_panic(buf);

	/*
	 * If we have crashed and we have a crash kernel loaded let it handle
	 * everything अन्यथा.
	 * If we want to run this after calling panic_notअगरiers, pass
	 * the "crash_kexec_post_notifiers" option to the kernel.
	 *
	 * Bypass the panic_cpu check and call __crash_kexec directly.
	 */
	अगर (!_crash_kexec_post_notअगरiers) अणु
		prपूर्णांकk_safe_flush_on_panic();
		__crash_kexec(शून्य);

		/*
		 * Note smp_send_stop is the usual smp shutकरोwn function, which
		 * unक्रमtunately means it may not be hardened to work in a
		 * panic situation.
		 */
		smp_send_stop();
	पूर्ण अन्यथा अणु
		/*
		 * If we want to करो crash dump after notअगरier calls and
		 * kmsg_dump, we will need architecture dependent extra
		 * works in addition to stopping other CPUs.
		 */
		crash_smp_send_stop();
	पूर्ण

	/*
	 * Run any panic handlers, including those that might need to
	 * add inक्रमmation to the kmsg dump output.
	 */
	atomic_notअगरier_call_chain(&panic_notअगरier_list, 0, buf);

	/* Call flush even twice. It tries harder with a single online CPU */
	prपूर्णांकk_safe_flush_on_panic();
	kmsg_dump(KMSG_DUMP_PANIC);

	/*
	 * If you करोubt kdump always works fine in any situation,
	 * "crash_kexec_post_notifiers" offers you a chance to run
	 * panic_notअगरiers and dumping kmsg beक्रमe kdump.
	 * Note: since some panic_notअगरiers can make crashed kernel
	 * more unstable, it can increase risks of the kdump failure too.
	 *
	 * Bypass the panic_cpu check and call __crash_kexec directly.
	 */
	अगर (_crash_kexec_post_notअगरiers)
		__crash_kexec(शून्य);

#अगर_घोषित CONFIG_VT
	unblank_screen();
#पूर्ण_अगर
	console_unblank();

	/*
	 * We may have ended up stopping the CPU holding the lock (in
	 * smp_send_stop()) जबतक still having some valuable data in the console
	 * buffer.  Try to acquire the lock then release it regardless of the
	 * result.  The release will also prपूर्णांक the buffers out.  Locks debug
	 * should be disabled to aव्योम reporting bad unlock balance when
	 * panic() is not being callled from OOPS.
	 */
	debug_locks_off();
	console_flush_on_panic(CONSOLE_FLUSH_PENDING);

	panic_prपूर्णांक_sys_info();

	अगर (!panic_blink)
		panic_blink = no_blink;

	अगर (panic_समयout > 0) अणु
		/*
		 * Delay समयout seconds beक्रमe rebooting the machine.
		 * We can't use the "normal" समयrs since we just panicked.
		 */
		pr_emerg("Rebooting in %d seconds..\n", panic_समयout);

		क्रम (i = 0; i < panic_समयout * 1000; i += PANIC_TIMER_STEP) अणु
			touch_nmi_watchकरोg();
			अगर (i >= i_next) अणु
				i += panic_blink(state ^= 1);
				i_next = i + 3600 / PANIC_BLINK_SPD;
			पूर्ण
			mdelay(PANIC_TIMER_STEP);
		पूर्ण
	पूर्ण
	अगर (panic_समयout != 0) अणु
		/*
		 * This will not be a clean reboot, with everything
		 * shutting करोwn.  But अगर there is a chance of
		 * rebooting the प्रणाली it will be rebooted.
		 */
		अगर (panic_reboot_mode != REBOOT_UNDEFINED)
			reboot_mode = panic_reboot_mode;
		emergency_restart();
	पूर्ण
#अगर_घोषित __sparc__
	अणु
		बाह्य पूर्णांक stop_a_enabled;
		/* Make sure the user can actually press Stop-A (L1-A) */
		stop_a_enabled = 1;
		pr_emerg("Press Stop-A (L1-A) from sun keyboard or send break\n"
			 "twice on console to return to the boot prom\n");
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_S390)
	disabled_रुको();
#पूर्ण_अगर
	pr_emerg("---[ end Kernel panic - not syncing: %s ]---\n", buf);

	/* Do not scroll important messages prपूर्णांकed above */
	suppress_prपूर्णांकk = 1;
	local_irq_enable();
	क्रम (i = 0; ; i += PANIC_TIMER_STEP) अणु
		touch_softlockup_watchकरोg();
		अगर (i >= i_next) अणु
			i += panic_blink(state ^= 1);
			i_next = i + 3600 / PANIC_BLINK_SPD;
		पूर्ण
		mdelay(PANIC_TIMER_STEP);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(panic);

/*
 * TAINT_FORCED_RMMOD could be a per-module flag but the module
 * is being हटाओd anyway.
 */
स्थिर काष्ठा taपूर्णांक_flag taपूर्णांक_flags[TAINT_FLAGS_COUNT] = अणु
	[ TAINT_PROPRIETARY_MODULE ]	= अणु 'P', 'G', true पूर्ण,
	[ TAINT_FORCED_MODULE ]		= अणु 'F', ' ', true पूर्ण,
	[ TAINT_CPU_OUT_OF_SPEC ]	= अणु 'S', ' ', false पूर्ण,
	[ TAINT_FORCED_RMMOD ]		= अणु 'R', ' ', false पूर्ण,
	[ TAINT_MACHINE_CHECK ]		= अणु 'M', ' ', false पूर्ण,
	[ TAINT_BAD_PAGE ]		= अणु 'B', ' ', false पूर्ण,
	[ TAINT_USER ]			= अणु 'U', ' ', false पूर्ण,
	[ TAINT_DIE ]			= अणु 'D', ' ', false पूर्ण,
	[ TAINT_OVERRIDDEN_ACPI_TABLE ]	= अणु 'A', ' ', false पूर्ण,
	[ TAINT_WARN ]			= अणु 'W', ' ', false पूर्ण,
	[ TAINT_CRAP ]			= अणु 'C', ' ', true पूर्ण,
	[ TAINT_FIRMWARE_WORKAROUND ]	= अणु 'I', ' ', false पूर्ण,
	[ TAINT_OOT_MODULE ]		= अणु 'O', ' ', true पूर्ण,
	[ TAINT_UNSIGNED_MODULE ]	= अणु 'E', ' ', true पूर्ण,
	[ TAINT_SOFTLOCKUP ]		= अणु 'L', ' ', false पूर्ण,
	[ TAINT_LIVEPATCH ]		= अणु 'K', ' ', true पूर्ण,
	[ TAINT_AUX ]			= अणु 'X', ' ', true पूर्ण,
	[ TAINT_RANDSTRUCT ]		= अणु 'T', ' ', true पूर्ण,
पूर्ण;

/**
 * prपूर्णांक_taपूर्णांकed - वापस a string to represent the kernel taपूर्णांक state.
 *
 * For inभागidual taपूर्णांक flag meanings, see Documentation/admin-guide/sysctl/kernel.rst
 *
 * The string is overwritten by the next call to prपूर्णांक_taपूर्णांकed(),
 * but is always शून्य terminated.
 */
स्थिर अक्षर *prपूर्णांक_taपूर्णांकed(व्योम)
अणु
	अटल अक्षर buf[TAINT_FLAGS_COUNT + माप("Tainted: ")];

	BUILD_BUG_ON(ARRAY_SIZE(taपूर्णांक_flags) != TAINT_FLAGS_COUNT);

	अगर (taपूर्णांकed_mask) अणु
		अक्षर *s;
		पूर्णांक i;

		s = buf + प्र_लिखो(buf, "Tainted: ");
		क्रम (i = 0; i < TAINT_FLAGS_COUNT; i++) अणु
			स्थिर काष्ठा taपूर्णांक_flag *t = &taपूर्णांक_flags[i];
			*s++ = test_bit(i, &taपूर्णांकed_mask) ?
					t->c_true : t->c_false;
		पूर्ण
		*s = 0;
	पूर्ण अन्यथा
		snम_लिखो(buf, माप(buf), "Not tainted");

	वापस buf;
पूर्ण

पूर्णांक test_taपूर्णांक(अचिन्हित flag)
अणु
	वापस test_bit(flag, &taपूर्णांकed_mask);
पूर्ण
EXPORT_SYMBOL(test_taपूर्णांक);

अचिन्हित दीर्घ get_taपूर्णांक(व्योम)
अणु
	वापस taपूर्णांकed_mask;
पूर्ण

/**
 * add_taपूर्णांक: add a taपूर्णांक flag अगर not alपढ़ोy set.
 * @flag: one of the TAINT_* स्थिरants.
 * @lockdep_ok: whether lock debugging is still OK.
 *
 * If something bad has gone wrong, you'll want @lockdebug_ok = false, but क्रम
 * some notewortht-but-not-corrupting हालs, it can be set to true.
 */
व्योम add_taपूर्णांक(अचिन्हित flag, क्रमागत lockdep_ok lockdep_ok)
अणु
	अगर (lockdep_ok == LOCKDEP_NOW_UNRELIABLE && __debug_locks_off())
		pr_warn("Disabling lock debugging due to kernel taint\n");

	set_bit(flag, &taपूर्णांकed_mask);

	अगर (taपूर्णांकed_mask & panic_on_taपूर्णांक) अणु
		panic_on_taपूर्णांक = 0;
		panic("panic_on_taint set ...");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(add_taपूर्णांक);

अटल व्योम spin_msec(पूर्णांक msecs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < msecs; i++) अणु
		touch_nmi_watchकरोg();
		mdelay(1);
	पूर्ण
पूर्ण

/*
 * It just happens that oops_enter() and oops_निकास() are identically
 * implemented...
 */
अटल व्योम करो_oops_enter_निकास(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अटल पूर्णांक spin_counter;

	अगर (!छोड़ो_on_oops)
		वापस;

	spin_lock_irqsave(&छोड़ो_on_oops_lock, flags);
	अगर (छोड़ो_on_oops_flag == 0) अणु
		/* This CPU may now prपूर्णांक the oops message */
		छोड़ो_on_oops_flag = 1;
	पूर्ण अन्यथा अणु
		/* We need to stall this CPU */
		अगर (!spin_counter) अणु
			/* This CPU माला_लो to करो the counting */
			spin_counter = छोड़ो_on_oops;
			करो अणु
				spin_unlock(&छोड़ो_on_oops_lock);
				spin_msec(MSEC_PER_SEC);
				spin_lock(&छोड़ो_on_oops_lock);
			पूर्ण जबतक (--spin_counter);
			छोड़ो_on_oops_flag = 0;
		पूर्ण अन्यथा अणु
			/* This CPU रुकोs क्रम a dअगरferent one */
			जबतक (spin_counter) अणु
				spin_unlock(&छोड़ो_on_oops_lock);
				spin_msec(1);
				spin_lock(&छोड़ो_on_oops_lock);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&छोड़ो_on_oops_lock, flags);
पूर्ण

/*
 * Return true अगर the calling CPU is allowed to prपूर्णांक oops-related info.
 * This is a bit racy..
 */
bool oops_may_prपूर्णांक(व्योम)
अणु
	वापस छोड़ो_on_oops_flag == 0;
पूर्ण

/*
 * Called when the architecture enters its oops handler, beक्रमe it prपूर्णांकs
 * anything.  If this is the first CPU to oops, and it's oopsing the first
 * समय then let it proceed.
 *
 * This is all enabled by the छोड़ो_on_oops kernel boot option.  We करो all
 * this to ensure that oopses करोn't scroll off the screen.  It has the
 * side-effect of preventing later-oopsing CPUs from mucking up the display,
 * too.
 *
 * It turns out that the CPU which is allowed to prपूर्णांक ends up pausing क्रम
 * the right duration, whereas all the other CPUs छोड़ो क्रम twice as दीर्घ:
 * once in oops_enter(), once in oops_निकास().
 */
व्योम oops_enter(व्योम)
अणु
	tracing_off();
	/* can't trust the पूर्णांकegrity of the kernel anymore: */
	debug_locks_off();
	करो_oops_enter_निकास();

	अगर (sysctl_oops_all_cpu_backtrace)
		trigger_all_cpu_backtrace();
पूर्ण

/*
 * 64-bit अक्रमom ID क्रम oopses:
 */
अटल u64 oops_id;

अटल पूर्णांक init_oops_id(व्योम)
अणु
	अगर (!oops_id)
		get_अक्रमom_bytes(&oops_id, माप(oops_id));
	अन्यथा
		oops_id++;

	वापस 0;
पूर्ण
late_initcall(init_oops_id);

अटल व्योम prपूर्णांक_oops_end_marker(व्योम)
अणु
	init_oops_id();
	pr_warn("---[ end trace %016llx ]---\n", (अचिन्हित दीर्घ दीर्घ)oops_id);
पूर्ण

/*
 * Called when the architecture निकासs its oops handler, after prपूर्णांकing
 * everything.
 */
व्योम oops_निकास(व्योम)
अणु
	करो_oops_enter_निकास();
	prपूर्णांक_oops_end_marker();
	kmsg_dump(KMSG_DUMP_OOPS);
पूर्ण

काष्ठा warn_args अणु
	स्थिर अक्षर *fmt;
	बहु_सूची args;
पूर्ण;

व्योम __warn(स्थिर अक्षर *file, पूर्णांक line, व्योम *caller, अचिन्हित taपूर्णांक,
	    काष्ठा pt_regs *regs, काष्ठा warn_args *args)
अणु
	disable_trace_on_warning();

	अगर (file)
		pr_warn("WARNING: CPU: %d PID: %d at %s:%d %pS\n",
			raw_smp_processor_id(), current->pid, file, line,
			caller);
	अन्यथा
		pr_warn("WARNING: CPU: %d PID: %d at %pS\n",
			raw_smp_processor_id(), current->pid, caller);

	अगर (args)
		vprपूर्णांकk(args->fmt, args->args);

	prपूर्णांक_modules();

	अगर (regs)
		show_regs(regs);

	अगर (panic_on_warn) अणु
		/*
		 * This thपढ़ो may hit another WARN() in the panic path.
		 * Resetting this prevents additional WARN() from panicking the
		 * प्रणाली on this thपढ़ो.  Other thपढ़ोs are blocked by the
		 * panic_mutex in panic().
		 */
		panic_on_warn = 0;
		panic("panic_on_warn set ...\n");
	पूर्ण

	अगर (!regs)
		dump_stack();

	prपूर्णांक_irqtrace_events(current);

	prपूर्णांक_oops_end_marker();

	/* Just a warning, करोn't समाप्त lockdep. */
	add_taपूर्णांक(taपूर्णांक, LOCKDEP_STILL_OK);
पूर्ण

#अगर_अघोषित __WARN_FLAGS
व्योम warn_slowpath_fmt(स्थिर अक्षर *file, पूर्णांक line, अचिन्हित taपूर्णांक,
		       स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा warn_args args;

	pr_warn(CUT_HERE);

	अगर (!fmt) अणु
		__warn(file, line, __builtin_वापस_address(0), taपूर्णांक,
		       शून्य, शून्य);
		वापस;
	पूर्ण

	args.fmt = fmt;
	बहु_शुरू(args.args, fmt);
	__warn(file, line, __builtin_वापस_address(0), taपूर्णांक, शून्य, &args);
	बहु_पूर्ण(args.args);
पूर्ण
EXPORT_SYMBOL(warn_slowpath_fmt);
#अन्यथा
व्योम __warn_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	pr_warn(CUT_HERE);

	बहु_शुरू(args, fmt);
	vprपूर्णांकk(fmt, args);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__warn_prपूर्णांकk);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BUG

/* Support resetting WARN*_ONCE state */

अटल पूर्णांक clear_warn_once_set(व्योम *data, u64 val)
अणु
	generic_bug_clear_once();
	स_रखो(__start_once, 0, __end_once - __start_once);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(clear_warn_once_fops, शून्य, clear_warn_once_set,
			 "%lld\n");

अटल __init पूर्णांक रेजिस्टर_warn_debugfs(व्योम)
अणु
	/* Don't care about failure */
	debugfs_create_file_unsafe("clear_warn_once", 0200, शून्य, शून्य,
				   &clear_warn_once_fops);
	वापस 0;
पूर्ण

device_initcall(रेजिस्टर_warn_debugfs);
#पूर्ण_अगर

#अगर_घोषित CONFIG_STACKPROTECTOR

/*
 * Called when gcc's -fstack-protector feature is used, and
 * gcc detects corruption of the on-stack canary value
 */
__visible noinstr व्योम __stack_chk_fail(व्योम)
अणु
	instrumentation_begin();
	panic("stack-protector: Kernel stack is corrupted in: %pB",
		__builtin_वापस_address(0));
	instrumentation_end();
पूर्ण
EXPORT_SYMBOL(__stack_chk_fail);

#पूर्ण_अगर

core_param(panic, panic_समयout, पूर्णांक, 0644);
core_param(panic_prपूर्णांक, panic_prपूर्णांक, uदीर्घ, 0644);
core_param(छोड़ो_on_oops, छोड़ो_on_oops, पूर्णांक, 0644);
core_param(panic_on_warn, panic_on_warn, पूर्णांक, 0644);
core_param(crash_kexec_post_notअगरiers, crash_kexec_post_notअगरiers, bool, 0644);

अटल पूर्णांक __init oops_setup(अक्षर *s)
अणु
	अगर (!s)
		वापस -EINVAL;
	अगर (!म_भेद(s, "panic"))
		panic_on_oops = 1;
	वापस 0;
पूर्ण
early_param("oops", oops_setup);

अटल पूर्णांक __init panic_on_taपूर्णांक_setup(अक्षर *s)
अणु
	अक्षर *taपूर्णांक_str;

	अगर (!s)
		वापस -EINVAL;

	taपूर्णांक_str = strsep(&s, ",");
	अगर (kम_से_अदीर्घ(taपूर्णांक_str, 16, &panic_on_taपूर्णांक))
		वापस -EINVAL;

	/* make sure panic_on_taपूर्णांक करोesn't hold out-of-range TAINT flags */
	panic_on_taपूर्णांक &= TAINT_FLAGS_MAX;

	अगर (!panic_on_taपूर्णांक)
		वापस -EINVAL;

	अगर (s && !म_भेद(s, "nousertaint"))
		panic_on_taपूर्णांक_nousertaपूर्णांक = true;

	pr_info("panic_on_taint: bitmask=0x%lx nousertaint_mode=%sabled\n",
		panic_on_taपूर्णांक, panic_on_taपूर्णांक_nousertaपूर्णांक ? "en" : "dis");

	वापस 0;
पूर्ण
early_param("panic_on_taint", panic_on_taपूर्णांक_setup);
