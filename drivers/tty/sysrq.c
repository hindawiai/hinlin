<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Linux Magic System Request Key Hacks
 *
 *	(c) 1997 Martin Mares <mj@atrey.karlin.mff.cuni.cz>
 *	based on ideas by Pavel Machek <pavel@atrey.karlin.mff.cuni.cz>
 *
 *	(c) 2000 Crutcher Dunnavant <crutcher+kernel@datastacks.com>
 *	overhauled to use key registration
 *	based upon discusions in irc://irc.खोलोprojects.net/#kernelnewbies
 *
 *	Copyright (c) 2010 Dmitry Torokhov
 *	Input handler conversion
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/kbd_kern.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/nmi.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/suspend.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/swap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/oom.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/of.h>
#समावेश <linux/rcupdate.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/irq_regs.h>

/* Whether we react on sysrq keys or just ignore them */
अटल पूर्णांक __पढ़ो_mostly sysrq_enabled = CONFIG_MAGIC_SYSRQ_DEFAULT_ENABLE;
अटल bool __पढ़ो_mostly sysrq_always_enabled;

अटल bool sysrq_on(व्योम)
अणु
	वापस sysrq_enabled || sysrq_always_enabled;
पूर्ण

/**
 * sysrq_mask - Getter क्रम sysrq_enabled mask.
 *
 * Return: 1 अगर sysrq is always enabled, enabled sysrq_key_op mask otherwise.
 */
पूर्णांक sysrq_mask(व्योम)
अणु
	अगर (sysrq_always_enabled)
		वापस 1;
	वापस sysrq_enabled;
पूर्ण
EXPORT_SYMBOL_GPL(sysrq_mask);

/*
 * A value of 1 means 'all', other nonzero values are an op mask:
 */
अटल bool sysrq_on_mask(पूर्णांक mask)
अणु
	वापस sysrq_always_enabled ||
	       sysrq_enabled == 1 ||
	       (sysrq_enabled & mask);
पूर्ण

अटल पूर्णांक __init sysrq_always_enabled_setup(अक्षर *str)
अणु
	sysrq_always_enabled = true;
	pr_info("sysrq always enabled.\n");

	वापस 1;
पूर्ण

__setup("sysrq_always_enabled", sysrq_always_enabled_setup);


अटल व्योम sysrq_handle_loglevel(पूर्णांक key)
अणु
	पूर्णांक i;

	i = key - '0';
	console_loglevel = CONSOLE_LOGLEVEL_DEFAULT;
	pr_info("Loglevel set to %d\n", i);
	console_loglevel = i;
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_loglevel_op = अणु
	.handler	= sysrq_handle_loglevel,
	.help_msg	= "loglevel(0-9)",
	.action_msg	= "Changing Loglevel",
	.enable_mask	= SYSRQ_ENABLE_LOG,
पूर्ण;

#अगर_घोषित CONFIG_VT
अटल व्योम sysrq_handle_SAK(पूर्णांक key)
अणु
	काष्ठा work_काष्ठा *SAK_work = &vc_cons[fg_console].SAK_work;

	schedule_work(SAK_work);
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_SAK_op = अणु
	.handler	= sysrq_handle_SAK,
	.help_msg	= "sak(k)",
	.action_msg	= "SAK",
	.enable_mask	= SYSRQ_ENABLE_KEYBOARD,
पूर्ण;
#अन्यथा
#घोषणा sysrq_SAK_op (*(स्थिर काष्ठा sysrq_key_op *)शून्य)
#पूर्ण_अगर

#अगर_घोषित CONFIG_VT
अटल व्योम sysrq_handle_unraw(पूर्णांक key)
अणु
	vt_reset_unicode(fg_console);
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sysrq_unraw_op = अणु
	.handler	= sysrq_handle_unraw,
	.help_msg	= "unraw(r)",
	.action_msg	= "Keyboard mode set to system default",
	.enable_mask	= SYSRQ_ENABLE_KEYBOARD,
पूर्ण;
#अन्यथा
#घोषणा sysrq_unraw_op (*(स्थिर काष्ठा sysrq_key_op *)शून्य)
#पूर्ण_अगर /* CONFIG_VT */

अटल व्योम sysrq_handle_crash(पूर्णांक key)
अणु
	/* release the RCU पढ़ो lock beक्रमe crashing */
	rcu_पढ़ो_unlock();

	panic("sysrq triggered crash\n");
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_crash_op = अणु
	.handler	= sysrq_handle_crash,
	.help_msg	= "crash(c)",
	.action_msg	= "Trigger a crash",
	.enable_mask	= SYSRQ_ENABLE_DUMP,
पूर्ण;

अटल व्योम sysrq_handle_reboot(पूर्णांक key)
अणु
	lockdep_off();
	local_irq_enable();
	emergency_restart();
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_reboot_op = अणु
	.handler	= sysrq_handle_reboot,
	.help_msg	= "reboot(b)",
	.action_msg	= "Resetting",
	.enable_mask	= SYSRQ_ENABLE_BOOT,
पूर्ण;

स्थिर काष्ठा sysrq_key_op *__sysrq_reboot_op = &sysrq_reboot_op;

अटल व्योम sysrq_handle_sync(पूर्णांक key)
अणु
	emergency_sync();
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_sync_op = अणु
	.handler	= sysrq_handle_sync,
	.help_msg	= "sync(s)",
	.action_msg	= "Emergency Sync",
	.enable_mask	= SYSRQ_ENABLE_SYNC,
पूर्ण;

अटल व्योम sysrq_handle_show_समयrs(पूर्णांक key)
अणु
	sysrq_समयr_list_show();
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sysrq_show_समयrs_op = अणु
	.handler	= sysrq_handle_show_समयrs,
	.help_msg	= "show-all-timers(q)",
	.action_msg	= "Show clockevent devices & pending hrtimers (no others)",
पूर्ण;

अटल व्योम sysrq_handle_mountro(पूर्णांक key)
अणु
	emergency_remount();
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_mountro_op = अणु
	.handler	= sysrq_handle_mountro,
	.help_msg	= "unmount(u)",
	.action_msg	= "Emergency Remount R/O",
	.enable_mask	= SYSRQ_ENABLE_REMOUNT,
पूर्ण;

#अगर_घोषित CONFIG_LOCKDEP
अटल व्योम sysrq_handle_showlocks(पूर्णांक key)
अणु
	debug_show_all_locks();
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sysrq_showlocks_op = अणु
	.handler	= sysrq_handle_showlocks,
	.help_msg	= "show-all-locks(d)",
	.action_msg	= "Show Locks Held",
पूर्ण;
#अन्यथा
#घोषणा sysrq_showlocks_op (*(स्थिर काष्ठा sysrq_key_op *)शून्य)
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल DEFINE_RAW_SPINLOCK(show_lock);

अटल व्योम showacpu(व्योम *dummy)
अणु
	अचिन्हित दीर्घ flags;

	/* Idle CPUs have no पूर्णांकeresting backtrace. */
	अगर (idle_cpu(smp_processor_id()))
		वापस;

	raw_spin_lock_irqsave(&show_lock, flags);
	pr_info("CPU%d:\n", smp_processor_id());
	show_stack(शून्य, शून्य, KERN_INFO);
	raw_spin_unlock_irqrestore(&show_lock, flags);
पूर्ण

अटल व्योम sysrq_showregs_othercpus(काष्ठा work_काष्ठा *dummy)
अणु
	smp_call_function(showacpu, शून्य, 0);
पूर्ण

अटल DECLARE_WORK(sysrq_showallcpus, sysrq_showregs_othercpus);

अटल व्योम sysrq_handle_showallcpus(पूर्णांक key)
अणु
	/*
	 * Fall back to the workqueue based prपूर्णांकing अगर the
	 * backtrace prपूर्णांकing did not succeed or the
	 * architecture has no support क्रम it:
	 */
	अगर (!trigger_all_cpu_backtrace()) अणु
		काष्ठा pt_regs *regs = शून्य;

		अगर (in_irq())
			regs = get_irq_regs();
		अगर (regs) अणु
			pr_info("CPU%d:\n", smp_processor_id());
			show_regs(regs);
		पूर्ण
		schedule_work(&sysrq_showallcpus);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sysrq_showallcpus_op = अणु
	.handler	= sysrq_handle_showallcpus,
	.help_msg	= "show-backtrace-all-active-cpus(l)",
	.action_msg	= "Show backtrace of all active CPUs",
	.enable_mask	= SYSRQ_ENABLE_DUMP,
पूर्ण;
#पूर्ण_अगर

अटल व्योम sysrq_handle_showregs(पूर्णांक key)
अणु
	काष्ठा pt_regs *regs = शून्य;

	अगर (in_irq())
		regs = get_irq_regs();
	अगर (regs)
		show_regs(regs);
	perf_event_prपूर्णांक_debug();
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_showregs_op = अणु
	.handler	= sysrq_handle_showregs,
	.help_msg	= "show-registers(p)",
	.action_msg	= "Show Regs",
	.enable_mask	= SYSRQ_ENABLE_DUMP,
पूर्ण;

अटल व्योम sysrq_handle_showstate(पूर्णांक key)
अणु
	show_state();
	show_workqueue_state();
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_showstate_op = अणु
	.handler	= sysrq_handle_showstate,
	.help_msg	= "show-task-states(t)",
	.action_msg	= "Show State",
	.enable_mask	= SYSRQ_ENABLE_DUMP,
पूर्ण;

अटल व्योम sysrq_handle_showstate_blocked(पूर्णांक key)
अणु
	show_state_filter(TASK_UNINTERRUPTIBLE);
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_showstate_blocked_op = अणु
	.handler	= sysrq_handle_showstate_blocked,
	.help_msg	= "show-blocked-tasks(w)",
	.action_msg	= "Show Blocked State",
	.enable_mask	= SYSRQ_ENABLE_DUMP,
पूर्ण;

#अगर_घोषित CONFIG_TRACING
#समावेश <linux/ftrace.h>

अटल व्योम sysrq_ftrace_dump(पूर्णांक key)
अणु
	ftrace_dump(DUMP_ALL);
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_ftrace_dump_op = अणु
	.handler	= sysrq_ftrace_dump,
	.help_msg	= "dump-ftrace-buffer(z)",
	.action_msg	= "Dump ftrace buffer",
	.enable_mask	= SYSRQ_ENABLE_DUMP,
पूर्ण;
#अन्यथा
#घोषणा sysrq_ftrace_dump_op (*(स्थिर काष्ठा sysrq_key_op *)शून्य)
#पूर्ण_अगर

अटल व्योम sysrq_handle_showmem(पूर्णांक key)
अणु
	show_mem(0, शून्य);
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_showmem_op = अणु
	.handler	= sysrq_handle_showmem,
	.help_msg	= "show-memory-usage(m)",
	.action_msg	= "Show Memory",
	.enable_mask	= SYSRQ_ENABLE_DUMP,
पूर्ण;

/*
 * Signal sysrq helper function.  Sends a संकेत to all user processes.
 */
अटल व्योम send_sig_all(पूर्णांक sig)
अणु
	काष्ठा task_काष्ठा *p;

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process(p) अणु
		अगर (p->flags & PF_KTHREAD)
			जारी;
		अगर (is_global_init(p))
			जारी;

		करो_send_sig_info(sig, SEND_SIG_PRIV, p, PIDTYPE_MAX);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

अटल व्योम sysrq_handle_term(पूर्णांक key)
अणु
	send_sig_all(संक_इति);
	console_loglevel = CONSOLE_LOGLEVEL_DEBUG;
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_term_op = अणु
	.handler	= sysrq_handle_term,
	.help_msg	= "terminate-all-tasks(e)",
	.action_msg	= "Terminate All Tasks",
	.enable_mask	= SYSRQ_ENABLE_SIGNAL,
पूर्ण;

अटल व्योम moom_callback(काष्ठा work_काष्ठा *ignored)
अणु
	स्थिर gfp_t gfp_mask = GFP_KERNEL;
	काष्ठा oom_control oc = अणु
		.zonelist = node_zonelist(first_memory_node, gfp_mask),
		.nodemask = शून्य,
		.memcg = शून्य,
		.gfp_mask = gfp_mask,
		.order = -1,
	पूर्ण;

	mutex_lock(&oom_lock);
	अगर (!out_of_memory(&oc))
		pr_info("OOM request ignored. No task eligible\n");
	mutex_unlock(&oom_lock);
पूर्ण

अटल DECLARE_WORK(moom_work, moom_callback);

अटल व्योम sysrq_handle_moom(पूर्णांक key)
अणु
	schedule_work(&moom_work);
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_moom_op = अणु
	.handler	= sysrq_handle_moom,
	.help_msg	= "memory-full-oom-kill(f)",
	.action_msg	= "Manual OOM execution",
	.enable_mask	= SYSRQ_ENABLE_SIGNAL,
पूर्ण;

अटल व्योम sysrq_handle_thaw(पूर्णांक key)
अणु
	emergency_thaw_all();
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_thaw_op = अणु
	.handler	= sysrq_handle_thaw,
	.help_msg	= "thaw-filesystems(j)",
	.action_msg	= "Emergency Thaw of all frozen filesystems",
	.enable_mask	= SYSRQ_ENABLE_SIGNAL,
पूर्ण;

अटल व्योम sysrq_handle_समाप्त(पूर्णांक key)
अणु
	send_sig_all(SIGKILL);
	console_loglevel = CONSOLE_LOGLEVEL_DEBUG;
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_समाप्त_op = अणु
	.handler	= sysrq_handle_समाप्त,
	.help_msg	= "kill-all-tasks(i)",
	.action_msg	= "Kill All Tasks",
	.enable_mask	= SYSRQ_ENABLE_SIGNAL,
पूर्ण;

अटल व्योम sysrq_handle_unrt(पूर्णांक key)
अणु
	normalize_rt_tasks();
पूर्ण
अटल स्थिर काष्ठा sysrq_key_op sysrq_unrt_op = अणु
	.handler	= sysrq_handle_unrt,
	.help_msg	= "nice-all-RT-tasks(n)",
	.action_msg	= "Nice All RT Tasks",
	.enable_mask	= SYSRQ_ENABLE_RTNICE,
पूर्ण;

/* Key Operations table and lock */
अटल DEFINE_SPINLOCK(sysrq_key_table_lock);

अटल स्थिर काष्ठा sysrq_key_op *sysrq_key_table[62] = अणु
	&sysrq_loglevel_op,		/* 0 */
	&sysrq_loglevel_op,		/* 1 */
	&sysrq_loglevel_op,		/* 2 */
	&sysrq_loglevel_op,		/* 3 */
	&sysrq_loglevel_op,		/* 4 */
	&sysrq_loglevel_op,		/* 5 */
	&sysrq_loglevel_op,		/* 6 */
	&sysrq_loglevel_op,		/* 7 */
	&sysrq_loglevel_op,		/* 8 */
	&sysrq_loglevel_op,		/* 9 */

	/*
	 * a: Don't use क्रम प्रणाली provided sysrqs, it is handled specially on
	 * sparc and will never arrive.
	 */
	शून्य,				/* a */
	&sysrq_reboot_op,		/* b */
	&sysrq_crash_op,		/* c */
	&sysrq_showlocks_op,		/* d */
	&sysrq_term_op,			/* e */
	&sysrq_moom_op,			/* f */
	/* g: May be रेजिस्टरed क्रम the kernel debugger */
	शून्य,				/* g */
	शून्य,				/* h - reserved क्रम help */
	&sysrq_समाप्त_op,			/* i */
#अगर_घोषित CONFIG_BLOCK
	&sysrq_thaw_op,			/* j */
#अन्यथा
	शून्य,				/* j */
#पूर्ण_अगर
	&sysrq_SAK_op,			/* k */
#अगर_घोषित CONFIG_SMP
	&sysrq_showallcpus_op,		/* l */
#अन्यथा
	शून्य,				/* l */
#पूर्ण_अगर
	&sysrq_showmem_op,		/* m */
	&sysrq_unrt_op,			/* n */
	/* o: This will often be रेजिस्टरed as 'Off' at init समय */
	शून्य,				/* o */
	&sysrq_showregs_op,		/* p */
	&sysrq_show_समयrs_op,		/* q */
	&sysrq_unraw_op,		/* r */
	&sysrq_sync_op,			/* s */
	&sysrq_showstate_op,		/* t */
	&sysrq_mountro_op,		/* u */
	/* v: May be रेजिस्टरed क्रम frame buffer console restore */
	शून्य,				/* v */
	&sysrq_showstate_blocked_op,	/* w */
	/* x: May be रेजिस्टरed on mips क्रम TLB dump */
	/* x: May be रेजिस्टरed on ppc/घातerpc क्रम xmon */
	/* x: May be रेजिस्टरed on sparc64 क्रम global PMU dump */
	शून्य,				/* x */
	/* y: May be रेजिस्टरed on sparc64 क्रम global रेजिस्टर dump */
	शून्य,				/* y */
	&sysrq_ftrace_dump_op,		/* z */
	शून्य,				/* A */
	शून्य,				/* B */
	शून्य,				/* C */
	शून्य,				/* D */
	शून्य,				/* E */
	शून्य,				/* F */
	शून्य,				/* G */
	शून्य,				/* H */
	शून्य,				/* I */
	शून्य,				/* J */
	शून्य,				/* K */
	शून्य,				/* L */
	शून्य,				/* M */
	शून्य,				/* N */
	शून्य,				/* O */
	शून्य,				/* P */
	शून्य,				/* Q */
	शून्य,				/* R */
	शून्य,				/* S */
	शून्य,				/* T */
	शून्य,				/* U */
	शून्य,				/* V */
	शून्य,				/* W */
	शून्य,				/* X */
	शून्य,				/* Y */
	शून्य,				/* Z */
पूर्ण;

/* key2index calculation, -1 on invalid index */
अटल पूर्णांक sysrq_key_table_key2index(पूर्णांक key)
अणु
	पूर्णांक retval;

	अगर ((key >= '0') && (key <= '9'))
		retval = key - '0';
	अन्यथा अगर ((key >= 'a') && (key <= 'z'))
		retval = key + 10 - 'a';
	अन्यथा अगर ((key >= 'A') && (key <= 'Z'))
		retval = key + 36 - 'A';
	अन्यथा
		retval = -1;
	वापस retval;
पूर्ण

/*
 * get and put functions क्रम the table, exposed to modules.
 */
अटल स्थिर काष्ठा sysrq_key_op *__sysrq_get_key_op(पूर्णांक key)
अणु
	स्थिर काष्ठा sysrq_key_op *op_p = शून्य;
	पूर्णांक i;

	i = sysrq_key_table_key2index(key);
	अगर (i != -1)
		op_p = sysrq_key_table[i];

	वापस op_p;
पूर्ण

अटल व्योम __sysrq_put_key_op(पूर्णांक key, स्थिर काष्ठा sysrq_key_op *op_p)
अणु
	पूर्णांक i = sysrq_key_table_key2index(key);

	अगर (i != -1)
		sysrq_key_table[i] = op_p;
पूर्ण

व्योम __handle_sysrq(पूर्णांक key, bool check_mask)
अणु
	स्थिर काष्ठा sysrq_key_op *op_p;
	पूर्णांक orig_log_level;
	पूर्णांक orig_suppress_prपूर्णांकk;
	पूर्णांक i;

	orig_suppress_prपूर्णांकk = suppress_prपूर्णांकk;
	suppress_prपूर्णांकk = 0;

	rcu_sysrq_start();
	rcu_पढ़ो_lock();
	/*
	 * Raise the apparent loglevel to maximum so that the sysrq header
	 * is shown to provide the user with positive feedback.  We करो not
	 * simply emit this at KERN_EMERG as that would change message
	 * routing in the consumers of /proc/kmsg.
	 */
	orig_log_level = console_loglevel;
	console_loglevel = CONSOLE_LOGLEVEL_DEFAULT;

	op_p = __sysrq_get_key_op(key);
	अगर (op_p) अणु
		/*
		 * Should we check क्रम enabled operations (/proc/sysrq-trigger
		 * should not) and is the invoked operation enabled?
		 */
		अगर (!check_mask || sysrq_on_mask(op_p->enable_mask)) अणु
			pr_info("%s\n", op_p->action_msg);
			console_loglevel = orig_log_level;
			op_p->handler(key);
		पूर्ण अन्यथा अणु
			pr_info("This sysrq operation is disabled.\n");
			console_loglevel = orig_log_level;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("HELP : ");
		/* Only prपूर्णांक the help msg once per handler */
		क्रम (i = 0; i < ARRAY_SIZE(sysrq_key_table); i++) अणु
			अगर (sysrq_key_table[i]) अणु
				पूर्णांक j;

				क्रम (j = 0; sysrq_key_table[i] !=
						sysrq_key_table[j]; j++)
					;
				अगर (j != i)
					जारी;
				pr_cont("%s ", sysrq_key_table[i]->help_msg);
			पूर्ण
		पूर्ण
		pr_cont("\n");
		console_loglevel = orig_log_level;
	पूर्ण
	rcu_पढ़ो_unlock();
	rcu_sysrq_end();

	suppress_prपूर्णांकk = orig_suppress_prपूर्णांकk;
पूर्ण

व्योम handle_sysrq(पूर्णांक key)
अणु
	अगर (sysrq_on())
		__handle_sysrq(key, true);
पूर्ण
EXPORT_SYMBOL(handle_sysrq);

#अगर_घोषित CONFIG_INPUT
अटल पूर्णांक sysrq_reset_करोwnसमय_ms;

/* Simple translation table क्रम the SysRq keys */
अटल स्थिर अचिन्हित अक्षर sysrq_xlate[KEY_CNT] =
	"\000\0331234567890-=\177\t"                    /* 0x00 - 0x0f */
	"qwertyuiop[]\r\000as"                          /* 0x10 - 0x1f */
	"dfghjkl;'`\000\\zxcv"                          /* 0x20 - 0x2f */
	"bnm,./\000*\000 \000\201\202\203\204\205"      /* 0x30 - 0x3f */
	"\206\207\210\211\212\000\000789-456+1"         /* 0x40 - 0x4f */
	"230\177\000\000\213\214\000\000\000\000\000\000\000\000\000\000" /* 0x50 - 0x5f */
	"\r\000/";                                      /* 0x60 - 0x6f */

काष्ठा sysrq_state अणु
	काष्ठा input_handle handle;
	काष्ठा work_काष्ठा reinject_work;
	अचिन्हित दीर्घ key_करोwn[BITS_TO_LONGS(KEY_CNT)];
	अचिन्हित पूर्णांक alt;
	अचिन्हित पूर्णांक alt_use;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक shअगरt_use;
	bool active;
	bool need_reinject;
	bool reinjecting;

	/* reset sequence handling */
	bool reset_canceled;
	bool reset_requested;
	अचिन्हित दीर्घ reset_keybit[BITS_TO_LONGS(KEY_CNT)];
	पूर्णांक reset_seq_len;
	पूर्णांक reset_seq_cnt;
	पूर्णांक reset_seq_version;
	काष्ठा समयr_list keyreset_समयr;
पूर्ण;

#घोषणा SYSRQ_KEY_RESET_MAX	20 /* Should be plenty */
अटल अचिन्हित लघु sysrq_reset_seq[SYSRQ_KEY_RESET_MAX];
अटल अचिन्हित पूर्णांक sysrq_reset_seq_len;
अटल अचिन्हित पूर्णांक sysrq_reset_seq_version = 1;

अटल व्योम sysrq_parse_reset_sequence(काष्ठा sysrq_state *state)
अणु
	पूर्णांक i;
	अचिन्हित लघु key;

	state->reset_seq_cnt = 0;

	क्रम (i = 0; i < sysrq_reset_seq_len; i++) अणु
		key = sysrq_reset_seq[i];

		अगर (key == KEY_RESERVED || key > KEY_MAX)
			अवरोध;

		__set_bit(key, state->reset_keybit);
		state->reset_seq_len++;

		अगर (test_bit(key, state->key_करोwn))
			state->reset_seq_cnt++;
	पूर्ण

	/* Disable reset until old keys are not released */
	state->reset_canceled = state->reset_seq_cnt != 0;

	state->reset_seq_version = sysrq_reset_seq_version;
पूर्ण

अटल व्योम sysrq_करो_reset(काष्ठा समयr_list *t)
अणु
	काष्ठा sysrq_state *state = from_समयr(state, t, keyreset_समयr);

	state->reset_requested = true;

	orderly_reboot();
पूर्ण

अटल व्योम sysrq_handle_reset_request(काष्ठा sysrq_state *state)
अणु
	अगर (state->reset_requested)
		__handle_sysrq(sysrq_xlate[KEY_B], false);

	अगर (sysrq_reset_करोwnसमय_ms)
		mod_समयr(&state->keyreset_समयr,
			jअगरfies + msecs_to_jअगरfies(sysrq_reset_करोwnसमय_ms));
	अन्यथा
		sysrq_करो_reset(&state->keyreset_समयr);
पूर्ण

अटल व्योम sysrq_detect_reset_sequence(काष्ठा sysrq_state *state,
					अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	अगर (!test_bit(code, state->reset_keybit)) अणु
		/*
		 * Pressing any key _not_ in reset sequence cancels
		 * the reset sequence.  Also cancelling the समयr in
		 * हाल additional keys were pressed after a reset
		 * has been requested.
		 */
		अगर (value && state->reset_seq_cnt) अणु
			state->reset_canceled = true;
			del_समयr(&state->keyreset_समयr);
		पूर्ण
	पूर्ण अन्यथा अगर (value == 0) अणु
		/*
		 * Key release - all keys in the reset sequence need
		 * to be pressed and held क्रम the reset समयout
		 * to hold.
		 */
		del_समयr(&state->keyreset_समयr);

		अगर (--state->reset_seq_cnt == 0)
			state->reset_canceled = false;
	पूर्ण अन्यथा अगर (value == 1) अणु
		/* key press, not स्वतःrepeat */
		अगर (++state->reset_seq_cnt == state->reset_seq_len &&
		    !state->reset_canceled) अणु
			sysrq_handle_reset_request(state);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_OF
अटल व्योम sysrq_of_get_keyreset_config(व्योम)
अणु
	u32 key;
	काष्ठा device_node *np;
	काष्ठा property *prop;
	स्थिर __be32 *p;

	np = of_find_node_by_path("/chosen/linux,sysrq-reset-seq");
	अगर (!np) अणु
		pr_debug("No sysrq node found");
		वापस;
	पूर्ण

	/* Reset in हाल a __weak definition was present */
	sysrq_reset_seq_len = 0;

	of_property_क्रम_each_u32(np, "keyset", prop, p, key) अणु
		अगर (key == KEY_RESERVED || key > KEY_MAX ||
		    sysrq_reset_seq_len == SYSRQ_KEY_RESET_MAX)
			अवरोध;

		sysrq_reset_seq[sysrq_reset_seq_len++] = (अचिन्हित लघु)key;
	पूर्ण

	/* Get reset समयout अगर any. */
	of_property_पढ़ो_u32(np, "timeout-ms", &sysrq_reset_करोwnसमय_ms);

	of_node_put(np);
पूर्ण
#अन्यथा
अटल व्योम sysrq_of_get_keyreset_config(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम sysrq_reinject_alt_sysrq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sysrq_state *sysrq =
			container_of(work, काष्ठा sysrq_state, reinject_work);
	काष्ठा input_handle *handle = &sysrq->handle;
	अचिन्हित पूर्णांक alt_code = sysrq->alt_use;

	अगर (sysrq->need_reinject) अणु
		/* we करो not want the assignment to be reordered */
		sysrq->reinjecting = true;
		mb();

		/* Simulate press and release of Alt + SysRq */
		input_inject_event(handle, EV_KEY, alt_code, 1);
		input_inject_event(handle, EV_KEY, KEY_SYSRQ, 1);
		input_inject_event(handle, EV_SYN, SYN_REPORT, 1);

		input_inject_event(handle, EV_KEY, KEY_SYSRQ, 0);
		input_inject_event(handle, EV_KEY, alt_code, 0);
		input_inject_event(handle, EV_SYN, SYN_REPORT, 1);

		mb();
		sysrq->reinjecting = false;
	पूर्ण
पूर्ण

अटल bool sysrq_handle_keypress(काष्ठा sysrq_state *sysrq,
				  अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	bool was_active = sysrq->active;
	bool suppress;

	चयन (code) अणु

	हाल KEY_LEFTALT:
	हाल KEY_RIGHTALT:
		अगर (!value) अणु
			/* One of ALTs is being released */
			अगर (sysrq->active && code == sysrq->alt_use)
				sysrq->active = false;

			sysrq->alt = KEY_RESERVED;

		पूर्ण अन्यथा अगर (value != 2) अणु
			sysrq->alt = code;
			sysrq->need_reinject = false;
		पूर्ण
		अवरोध;

	हाल KEY_LEFTSHIFT:
	हाल KEY_RIGHTSHIFT:
		अगर (!value)
			sysrq->shअगरt = KEY_RESERVED;
		अन्यथा अगर (value != 2)
			sysrq->shअगरt = code;
		अवरोध;

	हाल KEY_SYSRQ:
		अगर (value == 1 && sysrq->alt != KEY_RESERVED) अणु
			sysrq->active = true;
			sysrq->alt_use = sysrq->alt;
			/* either RESERVED (क्रम released) or actual code */
			sysrq->shअगरt_use = sysrq->shअगरt;
			/*
			 * If nothing अन्यथा will be pressed we'll need
			 * to re-inject Alt-SysRq keysroke.
			 */
			sysrq->need_reinject = true;
		पूर्ण

		/*
		 * Pretend that sysrq was never pressed at all. This
		 * is needed to properly handle KGDB which will try
		 * to release all keys after निकासing debugger. If we
		 * करो not clear key bit it KGDB will end up sending
		 * release events क्रम Alt and SysRq, potentially
		 * triggering prपूर्णांक screen function.
		 */
		अगर (sysrq->active)
			clear_bit(KEY_SYSRQ, sysrq->handle.dev->key);

		अवरोध;

	शेष:
		अगर (sysrq->active && value && value != 2) अणु
			अचिन्हित अक्षर c = sysrq_xlate[code];

			sysrq->need_reinject = false;
			अगर (sysrq->shअगरt_use != KEY_RESERVED)
				c = बड़े(c);
			__handle_sysrq(c, true);
		पूर्ण
		अवरोध;
	पूर्ण

	suppress = sysrq->active;

	अगर (!sysrq->active) अणु

		/*
		 * See अगर reset sequence has changed since the last समय.
		 */
		अगर (sysrq->reset_seq_version != sysrq_reset_seq_version)
			sysrq_parse_reset_sequence(sysrq);

		/*
		 * If we are not suppressing key presses keep track of
		 * keyboard state so we can release keys that have been
		 * pressed beक्रमe entering SysRq mode.
		 */
		अगर (value)
			set_bit(code, sysrq->key_करोwn);
		अन्यथा
			clear_bit(code, sysrq->key_करोwn);

		अगर (was_active)
			schedule_work(&sysrq->reinject_work);

		/* Check क्रम reset sequence */
		sysrq_detect_reset_sequence(sysrq, code, value);

	पूर्ण अन्यथा अगर (value == 0 && test_and_clear_bit(code, sysrq->key_करोwn)) अणु
		/*
		 * Pass on release events क्रम keys that was pressed beक्रमe
		 * entering SysRq mode.
		 */
		suppress = false;
	पूर्ण

	वापस suppress;
पूर्ण

अटल bool sysrq_filter(काष्ठा input_handle *handle,
			 अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा sysrq_state *sysrq = handle->निजी;
	bool suppress;

	/*
	 * Do not filter anything अगर we are in the process of re-injecting
	 * Alt+SysRq combination.
	 */
	अगर (sysrq->reinjecting)
		वापस false;

	चयन (type) अणु

	हाल EV_SYN:
		suppress = false;
		अवरोध;

	हाल EV_KEY:
		suppress = sysrq_handle_keypress(sysrq, code, value);
		अवरोध;

	शेष:
		suppress = sysrq->active;
		अवरोध;
	पूर्ण

	वापस suppress;
पूर्ण

अटल पूर्णांक sysrq_connect(काष्ठा input_handler *handler,
			 काष्ठा input_dev *dev,
			 स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा sysrq_state *sysrq;
	पूर्णांक error;

	sysrq = kzalloc(माप(काष्ठा sysrq_state), GFP_KERNEL);
	अगर (!sysrq)
		वापस -ENOMEM;

	INIT_WORK(&sysrq->reinject_work, sysrq_reinject_alt_sysrq);

	sysrq->handle.dev = dev;
	sysrq->handle.handler = handler;
	sysrq->handle.name = "sysrq";
	sysrq->handle.निजी = sysrq;
	समयr_setup(&sysrq->keyreset_समयr, sysrq_करो_reset, 0);

	error = input_रेजिस्टर_handle(&sysrq->handle);
	अगर (error) अणु
		pr_err("Failed to register input sysrq handler, error %d\n",
			error);
		जाओ err_मुक्त;
	पूर्ण

	error = input_खोलो_device(&sysrq->handle);
	अगर (error) अणु
		pr_err("Failed to open input device, error %d\n", error);
		जाओ err_unरेजिस्टर;
	पूर्ण

	वापस 0;

 err_unरेजिस्टर:
	input_unरेजिस्टर_handle(&sysrq->handle);
 err_मुक्त:
	kमुक्त(sysrq);
	वापस error;
पूर्ण

अटल व्योम sysrq_disconnect(काष्ठा input_handle *handle)
अणु
	काष्ठा sysrq_state *sysrq = handle->निजी;

	input_बंद_device(handle);
	cancel_work_sync(&sysrq->reinject_work);
	del_समयr_sync(&sysrq->keyreset_समयr);
	input_unरेजिस्टर_handle(handle);
	kमुक्त(sysrq);
पूर्ण

/*
 * We are matching on KEY_LEFTALT instead of KEY_SYSRQ because not all
 * keyboards have SysRq key predefined and so user may add it to keymap
 * later, but we expect all such keyboards to have left alt.
 */
अटल स्थिर काष्ठा input_device_id sysrq_ids[] = अणु
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = अणु [BIT_WORD(EV_KEY)] = BIT_MASK(EV_KEY) पूर्ण,
		.keybit = अणु [BIT_WORD(KEY_LEFTALT)] = BIT_MASK(KEY_LEFTALT) पूर्ण,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा input_handler sysrq_handler = अणु
	.filter		= sysrq_filter,
	.connect	= sysrq_connect,
	.disconnect	= sysrq_disconnect,
	.name		= "sysrq",
	.id_table	= sysrq_ids,
पूर्ण;

अटल अंतरभूत व्योम sysrq_रेजिस्टर_handler(व्योम)
अणु
	पूर्णांक error;

	sysrq_of_get_keyreset_config();

	error = input_रेजिस्टर_handler(&sysrq_handler);
	अगर (error)
		pr_err("Failed to register input handler, error %d", error);
पूर्ण

अटल अंतरभूत व्योम sysrq_unरेजिस्टर_handler(व्योम)
अणु
	input_unरेजिस्टर_handler(&sysrq_handler);
पूर्ण

अटल पूर्णांक sysrq_reset_seq_param_set(स्थिर अक्षर *buffer,
				     स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक error;

	error = kम_से_अदीर्घ(buffer, 0, &val);
	अगर (error < 0)
		वापस error;

	अगर (val > KEY_MAX)
		वापस -EINVAL;

	*((अचिन्हित लघु *)kp->arg) = val;
	sysrq_reset_seq_version++;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_sysrq_reset_seq = अणु
	.get	= param_get_uलघु,
	.set	= sysrq_reset_seq_param_set,
पूर्ण;

#घोषणा param_check_sysrq_reset_seq(name, p)	\
	__param_check(name, p, अचिन्हित लघु)

/*
 * not really modular, but the easiest way to keep compat with existing
 * bootargs behaviour is to जारी using module_param here.
 */
module_param_array_named(reset_seq, sysrq_reset_seq, sysrq_reset_seq,
			 &sysrq_reset_seq_len, 0644);

module_param_named(sysrq_करोwnसमय_ms, sysrq_reset_करोwnसमय_ms, पूर्णांक, 0644);

#अन्यथा

अटल अंतरभूत व्योम sysrq_रेजिस्टर_handler(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम sysrq_unरेजिस्टर_handler(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_INPUT */

पूर्णांक sysrq_toggle_support(पूर्णांक enable_mask)
अणु
	bool was_enabled = sysrq_on();

	sysrq_enabled = enable_mask;

	अगर (was_enabled != sysrq_on()) अणु
		अगर (sysrq_on())
			sysrq_रेजिस्टर_handler();
		अन्यथा
			sysrq_unरेजिस्टर_handler();
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sysrq_toggle_support);

अटल पूर्णांक __sysrq_swap_key_ops(पूर्णांक key, स्थिर काष्ठा sysrq_key_op *insert_op_p,
				स्थिर काष्ठा sysrq_key_op *हटाओ_op_p)
अणु
	पूर्णांक retval;

	spin_lock(&sysrq_key_table_lock);
	अगर (__sysrq_get_key_op(key) == हटाओ_op_p) अणु
		__sysrq_put_key_op(key, insert_op_p);
		retval = 0;
	पूर्ण अन्यथा अणु
		retval = -1;
	पूर्ण
	spin_unlock(&sysrq_key_table_lock);

	/*
	 * A concurrent __handle_sysrq either got the old op or the new op.
	 * Wait क्रम it to go away beक्रमe वापसing, so the code क्रम an old
	 * op is not मुक्तd (eg. on module unload) जबतक it is in use.
	 */
	synchronize_rcu();

	वापस retval;
पूर्ण

पूर्णांक रेजिस्टर_sysrq_key(पूर्णांक key, स्थिर काष्ठा sysrq_key_op *op_p)
अणु
	वापस __sysrq_swap_key_ops(key, op_p, शून्य);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_sysrq_key);

पूर्णांक unरेजिस्टर_sysrq_key(पूर्णांक key, स्थिर काष्ठा sysrq_key_op *op_p)
अणु
	वापस __sysrq_swap_key_ops(key, शून्य, op_p);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_sysrq_key);

#अगर_घोषित CONFIG_PROC_FS
/*
 * writing 'C' to /proc/sysrq-trigger is like sysrq-C
 */
अटल sमाप_प्रकार ग_लिखो_sysrq_trigger(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count) अणु
		अक्षर c;

		अगर (get_user(c, buf))
			वापस -EFAULT;
		__handle_sysrq(c, false);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops sysrq_trigger_proc_ops = अणु
	.proc_ग_लिखो	= ग_लिखो_sysrq_trigger,
	.proc_lseek	= noop_llseek,
पूर्ण;

अटल व्योम sysrq_init_procfs(व्योम)
अणु
	अगर (!proc_create("sysrq-trigger", S_IWUSR, शून्य,
			 &sysrq_trigger_proc_ops))
		pr_err("Failed to register proc interface\n");
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम sysrq_init_procfs(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल पूर्णांक __init sysrq_init(व्योम)
अणु
	sysrq_init_procfs();

	अगर (sysrq_on())
		sysrq_रेजिस्टर_handler();

	वापस 0;
पूर्ण
device_initcall(sysrq_init);
