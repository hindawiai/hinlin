<शैली गुरु>
/*
 * Kernel Debug Core
 *
 * Maपूर्णांकainer: Jason Wessel <jason.wessel@windriver.com>
 *
 * Copyright (C) 2000-2001 VERITAS Software Corporation.
 * Copyright (C) 2002-2004 Timesys Corporation
 * Copyright (C) 2003-2004 Amit S. Kale <amitkale@linsyssoft.com>
 * Copyright (C) 2004 Pavel Machek <pavel@ucw.cz>
 * Copyright (C) 2004-2006 Tom Rini <trini@kernel.crashing.org>
 * Copyright (C) 2004-2006 LinSysSoft Technologies Pvt. Ltd.
 * Copyright (C) 2005-2009 Wind River Systems, Inc.
 * Copyright (C) 2007 MontaVista Software, Inc.
 * Copyright (C) 2008 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * Contributors at various stages not listed above:
 *  Jason Wessel ( jason.wessel@windriver.com )
 *  George Anzinger <george@mvista.com>
 *  Anurekh Saxena (anurekh.saxena@बारys.com)
 *  Lake Stevens Instrument Division (Glenn Engel)
 *  Jim Kingकरोn, Cygnus Support.
 *
 * Original KGDB stub: David Grothe <dave@gcom.com>,
 * Tigran Aivazian <tigran@sco.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "KGDB: " fmt

#समावेश <linux/pid_namespace.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/console.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdb.h>
#समावेश <linux/nmi.h>
#समावेश <linux/pid.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/vmacache.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/atomic.h>

#समावेश "debug_core.h"

अटल पूर्णांक kgdb_अवरोध_asap;

काष्ठा debuggerinfo_काष्ठा kgdb_info[NR_CPUS];

/* kgdb_connected - Is a host GDB connected to us? */
पूर्णांक				kgdb_connected;
EXPORT_SYMBOL_GPL(kgdb_connected);

/* All the KGDB handlers are installed */
पूर्णांक			kgdb_io_module_रेजिस्टरed;

/* Guard क्रम recursive entry */
अटल पूर्णांक			exception_level;

काष्ठा kgdb_io		*dbg_io_ops;
अटल DEFINE_SPINLOCK(kgdb_registration_lock);

/* Action क्रम the reboot notअगरier, a global allow kdb to change it */
अटल पूर्णांक kgdbreboot;
/* kgdb console driver is loaded */
अटल पूर्णांक kgdb_con_रेजिस्टरed;
/* determine अगर kgdb console output should be used */
अटल पूर्णांक kgdb_use_con;
/* Flag क्रम alternate operations क्रम early debugging */
bool dbg_is_early = true;
/* Next cpu to become the master debug core */
पूर्णांक dbg_चयन_cpu;

/* Use kdb or gdbserver mode */
पूर्णांक dbg_kdb_mode = 1;

module_param(kgdb_use_con, पूर्णांक, 0644);
module_param(kgdbreboot, पूर्णांक, 0644);

/*
 * Holds inक्रमmation about अवरोधpoपूर्णांकs in a kernel. These अवरोधpoपूर्णांकs are
 * added and हटाओd by gdb.
 */
अटल काष्ठा kgdb_bkpt		kgdb_अवरोध[KGDB_MAX_BREAKPOINTS] = अणु
	[0 ... KGDB_MAX_BREAKPOINTS-1] = अणु .state = BP_UNDEFINED पूर्ण
पूर्ण;

/*
 * The CPU# of the active CPU, or -1 अगर none:
 */
atomic_t			kgdb_active = ATOMIC_INIT(-1);
EXPORT_SYMBOL_GPL(kgdb_active);
अटल DEFINE_RAW_SPINLOCK(dbg_master_lock);
अटल DEFINE_RAW_SPINLOCK(dbg_slave_lock);

/*
 * We use NR_CPUs not PERCPU, in हाल kgdb is used to debug early
 * bootup code (which might not have percpu set up yet):
 */
अटल atomic_t			masters_in_kgdb;
अटल atomic_t			slaves_in_kgdb;
atomic_t			kgdb_setting_अवरोधpoपूर्णांक;

काष्ठा task_काष्ठा		*kgdb_usethपढ़ो;
काष्ठा task_काष्ठा		*kgdb_contthपढ़ो;

पूर्णांक				kgdb_single_step;
अटल pid_t			kgdb_sstep_pid;

/* to keep track of the CPU which is करोing the single stepping*/
atomic_t			kgdb_cpu_करोing_single_step = ATOMIC_INIT(-1);

/*
 * If you are debugging a problem where roundup (the collection of
 * all other CPUs) is a problem [this should be extremely rare],
 * then use the nokgdbroundup option to aव्योम roundup. In that हाल
 * the other CPUs might पूर्णांकerfere with your debugging context, so
 * use this with care:
 */
अटल पूर्णांक kgdb_करो_roundup = 1;

अटल पूर्णांक __init opt_nokgdbroundup(अक्षर *str)
अणु
	kgdb_करो_roundup = 0;

	वापस 0;
पूर्ण

early_param("nokgdbroundup", opt_nokgdbroundup);

/*
 * Finally, some KGDB code :-)
 */

/*
 * Weak aliases क्रम अवरोधpoपूर्णांक management,
 * can be overridden by architectures when needed:
 */
पूर्णांक __weak kgdb_arch_set_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	पूर्णांक err;

	err = copy_from_kernel_nofault(bpt->saved_instr, (अक्षर *)bpt->bpt_addr,
				BREAK_INSTR_SIZE);
	अगर (err)
		वापस err;
	err = copy_to_kernel_nofault((अक्षर *)bpt->bpt_addr,
				 arch_kgdb_ops.gdb_bpt_instr, BREAK_INSTR_SIZE);
	वापस err;
पूर्ण
NOKPROBE_SYMBOL(kgdb_arch_set_अवरोधpoपूर्णांक);

पूर्णांक __weak kgdb_arch_हटाओ_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	वापस copy_to_kernel_nofault((अक्षर *)bpt->bpt_addr,
				  (अक्षर *)bpt->saved_instr, BREAK_INSTR_SIZE);
पूर्ण
NOKPROBE_SYMBOL(kgdb_arch_हटाओ_अवरोधpoपूर्णांक);

पूर्णांक __weak kgdb_validate_अवरोध_address(अचिन्हित दीर्घ addr)
अणु
	काष्ठा kgdb_bkpt पंचांगp;
	पूर्णांक err;

	अगर (kgdb_within_blocklist(addr))
		वापस -EINVAL;

	/* Validate setting the अवरोधpoपूर्णांक and then removing it.  If the
	 * हटाओ fails, the kernel needs to emit a bad message because we
	 * are deep trouble not being able to put things back the way we
	 * found them.
	 */
	पंचांगp.bpt_addr = addr;
	err = kgdb_arch_set_अवरोधpoपूर्णांक(&पंचांगp);
	अगर (err)
		वापस err;
	err = kgdb_arch_हटाओ_अवरोधpoपूर्णांक(&पंचांगp);
	अगर (err)
		pr_err("Critical breakpoint error, kernel memory destroyed at: %lx\n",
		       addr);
	वापस err;
पूर्ण

अचिन्हित दीर्घ __weak kgdb_arch_pc(पूर्णांक exception, काष्ठा pt_regs *regs)
अणु
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण
NOKPROBE_SYMBOL(kgdb_arch_pc);

पूर्णांक __weak kgdb_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक __weak kgdb_skipexception(पूर्णांक exception, काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(kgdb_skipexception);

#अगर_घोषित CONFIG_SMP

/*
 * Default (weak) implementation क्रम kgdb_roundup_cpus
 */

व्योम __weak kgdb_call_nmi_hook(व्योम *ignored)
अणु
	/*
	 * NOTE: get_irq_regs() is supposed to get the रेजिस्टरs from
	 * beक्रमe the IPI पूर्णांकerrupt happened and so is supposed to
	 * show where the processor was.  In some situations it's
	 * possible we might be called without an IPI, so it might be
	 * safer to figure out how to make kgdb_अवरोधpoपूर्णांक() work
	 * properly here.
	 */
	kgdb_nmicallback(raw_smp_processor_id(), get_irq_regs());
पूर्ण
NOKPROBE_SYMBOL(kgdb_call_nmi_hook);

अटल DEFINE_PER_CPU(call_single_data_t, kgdb_roundup_csd) =
	CSD_INIT(kgdb_call_nmi_hook, शून्य);

व्योम __weak kgdb_roundup_cpus(व्योम)
अणु
	call_single_data_t *csd;
	पूर्णांक this_cpu = raw_smp_processor_id();
	पूर्णांक cpu;
	पूर्णांक ret;

	क्रम_each_online_cpu(cpu) अणु
		/* No need to roundup ourselves */
		अगर (cpu == this_cpu)
			जारी;

		csd = &per_cpu(kgdb_roundup_csd, cpu);

		/*
		 * If it didn't round up last time, don't try again
		 * since smp_call_function_single_async() will block.
		 *
		 * If rounding_up is false then we know that the
		 * previous call must have at least started and that
		 * means smp_call_function_single_async() won't block.
		 */
		अगर (kgdb_info[cpu].rounding_up)
			जारी;
		kgdb_info[cpu].rounding_up = true;

		ret = smp_call_function_single_async(cpu, csd);
		अगर (ret)
			kgdb_info[cpu].rounding_up = false;
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(kgdb_roundup_cpus);

#पूर्ण_अगर

/*
 * Some architectures need cache flushes when we set/clear a
 * अवरोधpoपूर्णांक:
 */
अटल व्योम kgdb_flush_swअवरोध_addr(अचिन्हित दीर्घ addr)
अणु
	अगर (!CACHE_FLUSH_IS_SAFE)
		वापस;

	अगर (current->mm) अणु
		पूर्णांक i;

		क्रम (i = 0; i < VMACACHE_SIZE; i++) अणु
			अगर (!current->vmacache.vmas[i])
				जारी;
			flush_cache_range(current->vmacache.vmas[i],
					  addr, addr + BREAK_INSTR_SIZE);
		पूर्ण
	पूर्ण

	/* Force flush inकाष्ठाion cache अगर it was outside the mm */
	flush_icache_range(addr, addr + BREAK_INSTR_SIZE);
पूर्ण
NOKPROBE_SYMBOL(kgdb_flush_swअवरोध_addr);

/*
 * SW अवरोधpoपूर्णांक management:
 */
पूर्णांक dbg_activate_sw_अवरोधpoपूर्णांकs(व्योम)
अणु
	पूर्णांक error;
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
		अगर (kgdb_अवरोध[i].state != BP_SET)
			जारी;

		error = kgdb_arch_set_अवरोधpoपूर्णांक(&kgdb_अवरोध[i]);
		अगर (error) अणु
			ret = error;
			pr_info("BP install failed: %lx\n",
				kgdb_अवरोध[i].bpt_addr);
			जारी;
		पूर्ण

		kgdb_flush_swअवरोध_addr(kgdb_अवरोध[i].bpt_addr);
		kgdb_अवरोध[i].state = BP_ACTIVE;
	पूर्ण
	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(dbg_activate_sw_अवरोधpoपूर्णांकs);

पूर्णांक dbg_set_sw_अवरोध(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक err = kgdb_validate_अवरोध_address(addr);
	पूर्णांक अवरोधno = -1;
	पूर्णांक i;

	अगर (err)
		वापस err;

	क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
		अगर ((kgdb_अवरोध[i].state == BP_SET) &&
					(kgdb_अवरोध[i].bpt_addr == addr))
			वापस -EEXIST;
	पूर्ण
	क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
		अगर (kgdb_अवरोध[i].state == BP_REMOVED &&
					kgdb_अवरोध[i].bpt_addr == addr) अणु
			अवरोधno = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (अवरोधno == -1) अणु
		क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
			अगर (kgdb_अवरोध[i].state == BP_UNDEFINED) अणु
				अवरोधno = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (अवरोधno == -1)
		वापस -E2BIG;

	kgdb_अवरोध[अवरोधno].state = BP_SET;
	kgdb_अवरोध[अवरोधno].type = BP_BREAKPOINT;
	kgdb_अवरोध[अवरोधno].bpt_addr = addr;

	वापस 0;
पूर्ण

पूर्णांक dbg_deactivate_sw_अवरोधpoपूर्णांकs(व्योम)
अणु
	पूर्णांक error;
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
		अगर (kgdb_अवरोध[i].state != BP_ACTIVE)
			जारी;
		error = kgdb_arch_हटाओ_अवरोधpoपूर्णांक(&kgdb_अवरोध[i]);
		अगर (error) अणु
			pr_info("BP remove failed: %lx\n",
				kgdb_अवरोध[i].bpt_addr);
			ret = error;
		पूर्ण

		kgdb_flush_swअवरोध_addr(kgdb_अवरोध[i].bpt_addr);
		kgdb_अवरोध[i].state = BP_SET;
	पूर्ण
	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(dbg_deactivate_sw_अवरोधpoपूर्णांकs);

पूर्णांक dbg_हटाओ_sw_अवरोध(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
		अगर ((kgdb_अवरोध[i].state == BP_SET) &&
				(kgdb_अवरोध[i].bpt_addr == addr)) अणु
			kgdb_अवरोध[i].state = BP_REMOVED;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

पूर्णांक kgdb_isहटाओdअवरोध(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
		अगर ((kgdb_अवरोध[i].state == BP_REMOVED) &&
					(kgdb_अवरोध[i].bpt_addr == addr))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक kgdb_has_hit_अवरोध(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
		अगर (kgdb_अवरोध[i].state == BP_ACTIVE &&
		    kgdb_अवरोध[i].bpt_addr == addr)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक dbg_हटाओ_all_अवरोध(व्योम)
अणु
	पूर्णांक error;
	पूर्णांक i;

	/* Clear memory अवरोधpoपूर्णांकs. */
	क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
		अगर (kgdb_अवरोध[i].state != BP_ACTIVE)
			जाओ setundefined;
		error = kgdb_arch_हटाओ_अवरोधpoपूर्णांक(&kgdb_अवरोध[i]);
		अगर (error)
			pr_err("breakpoint remove failed: %lx\n",
			       kgdb_अवरोध[i].bpt_addr);
setundefined:
		kgdb_अवरोध[i].state = BP_UNDEFINED;
	पूर्ण

	/* Clear hardware अवरोधpoपूर्णांकs. */
	अगर (arch_kgdb_ops.हटाओ_all_hw_अवरोध)
		arch_kgdb_ops.हटाओ_all_hw_अवरोध();

	वापस 0;
पूर्ण

व्योम kgdb_मुक्त_init_mem(व्योम)
अणु
	पूर्णांक i;

	/* Clear init memory अवरोधpoपूर्णांकs. */
	क्रम (i = 0; i < KGDB_MAX_BREAKPOINTS; i++) अणु
		अगर (init_section_contains((व्योम *)kgdb_अवरोध[i].bpt_addr, 0))
			kgdb_अवरोध[i].state = BP_UNDEFINED;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_KGDB_KDB
व्योम kdb_dump_stack_on_cpu(पूर्णांक cpu)
अणु
	अगर (cpu == raw_smp_processor_id() || !IS_ENABLED(CONFIG_SMP)) अणु
		dump_stack();
		वापस;
	पूर्ण

	अगर (!(kgdb_info[cpu].exception_state & DCPU_IS_SLAVE)) अणु
		kdb_म_लिखो("ERROR: Task on cpu %d didn't stop in the debugger\n",
			   cpu);
		वापस;
	पूर्ण

	/*
	 * In general, architectures करोn't support dumping the stack of a
	 * "running" process that's not the current one.  From the poपूर्णांक of
	 * view of the Linux, kernel processes that are looping in the kgdb
	 * slave loop are still "running".  There's also no API (that actually
	 * works across all architectures) that can करो a stack crawl based
	 * on रेजिस्टरs passed as a parameter.
	 *
	 * Solve this conundrum by asking slave CPUs to करो the backtrace
	 * themselves.
	 */
	kgdb_info[cpu].exception_state |= DCPU_WANT_BT;
	जबतक (kgdb_info[cpu].exception_state & DCPU_WANT_BT)
		cpu_relax();
पूर्ण
#पूर्ण_अगर

/*
 * Return true अगर there is a valid kgdb I/O module.  Also अगर no
 * debugger is attached a message can be prपूर्णांकed to the console about
 * रुकोing क्रम the debugger to attach.
 *
 * The prपूर्णांक_रुको argument is only to be true when called from inside
 * the core kgdb_handle_exception, because it will रुको क्रम the
 * debugger to attach.
 */
अटल पूर्णांक kgdb_io_पढ़ोy(पूर्णांक prपूर्णांक_रुको)
अणु
	अगर (!dbg_io_ops)
		वापस 0;
	अगर (kgdb_connected)
		वापस 1;
	अगर (atomic_पढ़ो(&kgdb_setting_अवरोधpoपूर्णांक))
		वापस 1;
	अगर (prपूर्णांक_रुको) अणु
#अगर_घोषित CONFIG_KGDB_KDB
		अगर (!dbg_kdb_mode)
			pr_crit("waiting... or $3#33 for KDB\n");
#अन्यथा
		pr_crit("Waiting for remote debugger\n");
#पूर्ण_अगर
	पूर्ण
	वापस 1;
पूर्ण
NOKPROBE_SYMBOL(kgdb_io_पढ़ोy);

अटल पूर्णांक kgdb_reenter_check(काष्ठा kgdb_state *ks)
अणु
	अचिन्हित दीर्घ addr;

	अगर (atomic_पढ़ो(&kgdb_active) != raw_smp_processor_id())
		वापस 0;

	/* Panic on recursive debugger calls: */
	exception_level++;
	addr = kgdb_arch_pc(ks->ex_vector, ks->linux_regs);
	dbg_deactivate_sw_अवरोधpoपूर्णांकs();

	/*
	 * If the अवरोध poपूर्णांक हटाओd ok at the place exception
	 * occurred, try to recover and prपूर्णांक a warning to the end
	 * user because the user planted a अवरोधpoपूर्णांक in a place that
	 * KGDB needs in order to function.
	 */
	अगर (dbg_हटाओ_sw_अवरोध(addr) == 0) अणु
		exception_level = 0;
		kgdb_skipexception(ks->ex_vector, ks->linux_regs);
		dbg_activate_sw_अवरोधpoपूर्णांकs();
		pr_crit("re-enter error: breakpoint removed %lx\n", addr);
		WARN_ON_ONCE(1);

		वापस 1;
	पूर्ण
	dbg_हटाओ_all_अवरोध();
	kgdb_skipexception(ks->ex_vector, ks->linux_regs);

	अगर (exception_level > 1) अणु
		dump_stack();
		kgdb_io_module_रेजिस्टरed = false;
		panic("Recursive entry to debugger");
	पूर्ण

	pr_crit("re-enter exception: ALL breakpoints killed\n");
#अगर_घोषित CONFIG_KGDB_KDB
	/* Allow kdb to debug itself one level */
	वापस 0;
#पूर्ण_अगर
	dump_stack();
	panic("Recursive entry to debugger");

	वापस 1;
पूर्ण
NOKPROBE_SYMBOL(kgdb_reenter_check);

अटल व्योम dbg_touch_watchकरोgs(व्योम)
अणु
	touch_softlockup_watchकरोg_sync();
	घड़ीsource_touch_watchकरोg();
	rcu_cpu_stall_reset();
पूर्ण
NOKPROBE_SYMBOL(dbg_touch_watchकरोgs);

अटल पूर्णांक kgdb_cpu_enter(काष्ठा kgdb_state *ks, काष्ठा pt_regs *regs,
		पूर्णांक exception_state)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक sstep_tries = 100;
	पूर्णांक error;
	पूर्णांक cpu;
	पूर्णांक trace_on = 0;
	पूर्णांक online_cpus = num_online_cpus();
	u64 समय_left;

	kgdb_info[ks->cpu].enter_kgdb++;
	kgdb_info[ks->cpu].exception_state |= exception_state;

	अगर (exception_state == DCPU_WANT_MASTER)
		atomic_inc(&masters_in_kgdb);
	अन्यथा
		atomic_inc(&slaves_in_kgdb);

	अगर (arch_kgdb_ops.disable_hw_अवरोध)
		arch_kgdb_ops.disable_hw_अवरोध(regs);

acquirelock:
	rcu_पढ़ो_lock();
	/*
	 * Interrupts will be restored by the 'trap return' code, except when
	 * single stepping.
	 */
	local_irq_save(flags);

	cpu = ks->cpu;
	kgdb_info[cpu].debuggerinfo = regs;
	kgdb_info[cpu].task = current;
	kgdb_info[cpu].ret_state = 0;
	kgdb_info[cpu].irq_depth = hardirq_count() >> HARसूचीQ_SHIFT;

	/* Make sure the above info reaches the primary CPU */
	smp_mb();

	अगर (exception_level == 1) अणु
		अगर (raw_spin_trylock(&dbg_master_lock))
			atomic_xchg(&kgdb_active, cpu);
		जाओ cpu_master_loop;
	पूर्ण

	/*
	 * CPU will loop अगर it is a slave or request to become a kgdb
	 * master cpu and acquire the kgdb_active lock:
	 */
	जबतक (1) अणु
cpu_loop:
		अगर (kgdb_info[cpu].exception_state & DCPU_NEXT_MASTER) अणु
			kgdb_info[cpu].exception_state &= ~DCPU_NEXT_MASTER;
			जाओ cpu_master_loop;
		पूर्ण अन्यथा अगर (kgdb_info[cpu].exception_state & DCPU_WANT_MASTER) अणु
			अगर (raw_spin_trylock(&dbg_master_lock)) अणु
				atomic_xchg(&kgdb_active, cpu);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (kgdb_info[cpu].exception_state & DCPU_WANT_BT) अणु
			dump_stack();
			kgdb_info[cpu].exception_state &= ~DCPU_WANT_BT;
		पूर्ण अन्यथा अगर (kgdb_info[cpu].exception_state & DCPU_IS_SLAVE) अणु
			अगर (!raw_spin_is_locked(&dbg_slave_lock))
				जाओ वापस_normal;
		पूर्ण अन्यथा अणु
वापस_normal:
			/* Return to normal operation by executing any
			 * hw अवरोधpoपूर्णांक fixup.
			 */
			अगर (arch_kgdb_ops.correct_hw_अवरोध)
				arch_kgdb_ops.correct_hw_अवरोध();
			अगर (trace_on)
				tracing_on();
			kgdb_info[cpu].debuggerinfo = शून्य;
			kgdb_info[cpu].task = शून्य;
			kgdb_info[cpu].exception_state &=
				~(DCPU_WANT_MASTER | DCPU_IS_SLAVE);
			kgdb_info[cpu].enter_kgdb--;
			smp_mb__beक्रमe_atomic();
			atomic_dec(&slaves_in_kgdb);
			dbg_touch_watchकरोgs();
			local_irq_restore(flags);
			rcu_पढ़ो_unlock();
			वापस 0;
		पूर्ण
		cpu_relax();
	पूर्ण

	/*
	 * For single stepping, try to only enter on the processor
	 * that was single stepping.  To guard against a deadlock, the
	 * kernel will only try क्रम the value of sstep_tries beक्रमe
	 * giving up and continuing on.
	 */
	अगर (atomic_पढ़ो(&kgdb_cpu_करोing_single_step) != -1 &&
	    (kgdb_info[cpu].task &&
	     kgdb_info[cpu].task->pid != kgdb_sstep_pid) && --sstep_tries) अणु
		atomic_set(&kgdb_active, -1);
		raw_spin_unlock(&dbg_master_lock);
		dbg_touch_watchकरोgs();
		local_irq_restore(flags);
		rcu_पढ़ो_unlock();

		जाओ acquirelock;
	पूर्ण

	अगर (!kgdb_io_पढ़ोy(1)) अणु
		kgdb_info[cpu].ret_state = 1;
		जाओ kgdb_restore; /* No I/O connection, resume the प्रणाली */
	पूर्ण

	/*
	 * Don't enter अगर we have hit a हटाओd अवरोधpoपूर्णांक.
	 */
	अगर (kgdb_skipexception(ks->ex_vector, ks->linux_regs))
		जाओ kgdb_restore;

	atomic_inc(&ignore_console_lock_warning);

	/* Call the I/O driver's pre_exception routine */
	अगर (dbg_io_ops->pre_exception)
		dbg_io_ops->pre_exception();

	/*
	 * Get the passive CPU lock which will hold all the non-primary
	 * CPU in a spin state जबतक the debugger is active
	 */
	अगर (!kgdb_single_step)
		raw_spin_lock(&dbg_slave_lock);

#अगर_घोषित CONFIG_SMP
	/* If send_पढ़ोy set, slaves are alपढ़ोy रुकोing */
	अगर (ks->send_पढ़ोy)
		atomic_set(ks->send_पढ़ोy, 1);

	/* Signal the other CPUs to enter kgdb_रुको() */
	अन्यथा अगर ((!kgdb_single_step) && kgdb_करो_roundup)
		kgdb_roundup_cpus();
#पूर्ण_अगर

	/*
	 * Wait क्रम the other CPUs to be notअगरied and be रुकोing क्रम us:
	 */
	समय_left = MSEC_PER_SEC;
	जबतक (kgdb_करो_roundup && --समय_left &&
	       (atomic_पढ़ो(&masters_in_kgdb) + atomic_पढ़ो(&slaves_in_kgdb)) !=
		   online_cpus)
		udelay(1000);
	अगर (!समय_left)
		pr_crit("Timed out waiting for secondary CPUs.\n");

	/*
	 * At this poपूर्णांक the primary processor is completely
	 * in the debugger and all secondary CPUs are quiescent
	 */
	dbg_deactivate_sw_अवरोधpoपूर्णांकs();
	kgdb_single_step = 0;
	kgdb_contthपढ़ो = current;
	exception_level = 0;
	trace_on = tracing_is_on();
	अगर (trace_on)
		tracing_off();

	जबतक (1) अणु
cpu_master_loop:
		अगर (dbg_kdb_mode) अणु
			kgdb_connected = 1;
			error = kdb_stub(ks);
			अगर (error == -1)
				जारी;
			kgdb_connected = 0;
		पूर्ण अन्यथा अणु
			error = gdb_serial_stub(ks);
		पूर्ण

		अगर (error == DBG_PASS_EVENT) अणु
			dbg_kdb_mode = !dbg_kdb_mode;
		पूर्ण अन्यथा अगर (error == DBG_SWITCH_CPU_EVENT) अणु
			kgdb_info[dbg_चयन_cpu].exception_state |=
				DCPU_NEXT_MASTER;
			जाओ cpu_loop;
		पूर्ण अन्यथा अणु
			kgdb_info[cpu].ret_state = error;
			अवरोध;
		पूर्ण
	पूर्ण

	dbg_activate_sw_अवरोधpoपूर्णांकs();

	/* Call the I/O driver's post_exception routine */
	अगर (dbg_io_ops->post_exception)
		dbg_io_ops->post_exception();

	atomic_dec(&ignore_console_lock_warning);

	अगर (!kgdb_single_step) अणु
		raw_spin_unlock(&dbg_slave_lock);
		/* Wait till all the CPUs have quit from the debugger. */
		जबतक (kgdb_करो_roundup && atomic_पढ़ो(&slaves_in_kgdb))
			cpu_relax();
	पूर्ण

kgdb_restore:
	अगर (atomic_पढ़ो(&kgdb_cpu_करोing_single_step) != -1) अणु
		पूर्णांक sstep_cpu = atomic_पढ़ो(&kgdb_cpu_करोing_single_step);
		अगर (kgdb_info[sstep_cpu].task)
			kgdb_sstep_pid = kgdb_info[sstep_cpu].task->pid;
		अन्यथा
			kgdb_sstep_pid = 0;
	पूर्ण
	अगर (arch_kgdb_ops.correct_hw_अवरोध)
		arch_kgdb_ops.correct_hw_अवरोध();
	अगर (trace_on)
		tracing_on();

	kgdb_info[cpu].debuggerinfo = शून्य;
	kgdb_info[cpu].task = शून्य;
	kgdb_info[cpu].exception_state &=
		~(DCPU_WANT_MASTER | DCPU_IS_SLAVE);
	kgdb_info[cpu].enter_kgdb--;
	smp_mb__beक्रमe_atomic();
	atomic_dec(&masters_in_kgdb);
	/* Free kgdb_active */
	atomic_set(&kgdb_active, -1);
	raw_spin_unlock(&dbg_master_lock);
	dbg_touch_watchकरोgs();
	local_irq_restore(flags);
	rcu_पढ़ो_unlock();

	वापस kgdb_info[cpu].ret_state;
पूर्ण
NOKPROBE_SYMBOL(kgdb_cpu_enter);

/*
 * kgdb_handle_exception() - मुख्य entry poपूर्णांक from a kernel exception
 *
 * Locking hierarchy:
 *	पूर्णांकerface locks, अगर any (begin_session)
 *	kgdb lock (kgdb_active)
 */
पूर्णांक
kgdb_handle_exception(पूर्णांक evector, पूर्णांक signo, पूर्णांक ecode, काष्ठा pt_regs *regs)
अणु
	काष्ठा kgdb_state kgdb_var;
	काष्ठा kgdb_state *ks = &kgdb_var;
	पूर्णांक ret = 0;

	अगर (arch_kgdb_ops.enable_nmi)
		arch_kgdb_ops.enable_nmi(0);
	/*
	 * Aव्योम entering the debugger अगर we were triggered due to an oops
	 * but panic_समयout indicates the प्रणाली should स्वतःmatically
	 * reboot on panic. We करोn't want to get stuck रुकोing क्रम input
	 * on such प्रणालीs, especially अगर its "just" an oops.
	 */
	अगर (signo != SIGTRAP && panic_समयout)
		वापस 1;

	स_रखो(ks, 0, माप(काष्ठा kgdb_state));
	ks->cpu			= raw_smp_processor_id();
	ks->ex_vector		= evector;
	ks->signo		= signo;
	ks->err_code		= ecode;
	ks->linux_regs		= regs;

	अगर (kgdb_reenter_check(ks))
		जाओ out; /* Ouch, द्विगुन exception ! */
	अगर (kgdb_info[ks->cpu].enter_kgdb != 0)
		जाओ out;

	ret = kgdb_cpu_enter(ks, regs, DCPU_WANT_MASTER);
out:
	अगर (arch_kgdb_ops.enable_nmi)
		arch_kgdb_ops.enable_nmi(1);
	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(kgdb_handle_exception);

/*
 * GDB places a अवरोधpoपूर्णांक at this function to know dynamically loaded objects.
 */
अटल पूर्णांक module_event(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val,
	व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block dbg_module_load_nb = अणु
	.notअगरier_call	= module_event,
पूर्ण;

पूर्णांक kgdb_nmicallback(पूर्णांक cpu, व्योम *regs)
अणु
#अगर_घोषित CONFIG_SMP
	काष्ठा kgdb_state kgdb_var;
	काष्ठा kgdb_state *ks = &kgdb_var;

	kgdb_info[cpu].rounding_up = false;

	स_रखो(ks, 0, माप(काष्ठा kgdb_state));
	ks->cpu			= cpu;
	ks->linux_regs		= regs;

	अगर (kgdb_info[ks->cpu].enter_kgdb == 0 &&
			raw_spin_is_locked(&dbg_master_lock)) अणु
		kgdb_cpu_enter(ks, regs, DCPU_IS_SLAVE);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	वापस 1;
पूर्ण
NOKPROBE_SYMBOL(kgdb_nmicallback);

पूर्णांक kgdb_nmicallin(पूर्णांक cpu, पूर्णांक trapnr, व्योम *regs, पूर्णांक err_code,
							atomic_t *send_पढ़ोy)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (!kgdb_io_पढ़ोy(0) || !send_पढ़ोy)
		वापस 1;

	अगर (kgdb_info[cpu].enter_kgdb == 0) अणु
		काष्ठा kgdb_state kgdb_var;
		काष्ठा kgdb_state *ks = &kgdb_var;

		स_रखो(ks, 0, माप(काष्ठा kgdb_state));
		ks->cpu			= cpu;
		ks->ex_vector		= trapnr;
		ks->signo		= SIGTRAP;
		ks->err_code		= err_code;
		ks->linux_regs		= regs;
		ks->send_पढ़ोy		= send_पढ़ोy;
		kgdb_cpu_enter(ks, regs, DCPU_WANT_MASTER);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	वापस 1;
पूर्ण
NOKPROBE_SYMBOL(kgdb_nmicallin);

अटल व्योम kgdb_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
   अचिन्हित count)
अणु
	अचिन्हित दीर्घ flags;

	/* If we're debugging, or KGDB has not connected, don't try
	 * and prपूर्णांक. */
	अगर (!kgdb_connected || atomic_पढ़ो(&kgdb_active) != -1 || dbg_kdb_mode)
		वापस;

	local_irq_save(flags);
	gdbstub_msg_ग_लिखो(s, count);
	local_irq_restore(flags);
पूर्ण

अटल काष्ठा console kgdbcons = अणु
	.name		= "kgdb",
	.ग_लिखो		= kgdb_console_ग_लिखो,
	.flags		= CON_PRINTBUFFER | CON_ENABLED,
	.index		= -1,
पूर्ण;

अटल पूर्णांक __init opt_kgdb_con(अक्षर *str)
अणु
	kgdb_use_con = 1;

	अगर (kgdb_io_module_रेजिस्टरed && !kgdb_con_रेजिस्टरed) अणु
		रेजिस्टर_console(&kgdbcons);
		kgdb_con_रेजिस्टरed = 1;
	पूर्ण

	वापस 0;
पूर्ण

early_param("kgdbcon", opt_kgdb_con);

#अगर_घोषित CONFIG_MAGIC_SYSRQ
अटल व्योम sysrq_handle_dbg(पूर्णांक key)
अणु
	अगर (!dbg_io_ops) अणु
		pr_crit("ERROR: No KGDB I/O module available\n");
		वापस;
	पूर्ण
	अगर (!kgdb_connected) अणु
#अगर_घोषित CONFIG_KGDB_KDB
		अगर (!dbg_kdb_mode)
			pr_crit("KGDB or $3#33 for KDB\n");
#अन्यथा
		pr_crit("Entering KGDB\n");
#पूर्ण_अगर
	पूर्ण

	kgdb_अवरोधpoपूर्णांक();
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op sysrq_dbg_op = अणु
	.handler	= sysrq_handle_dbg,
	.help_msg	= "debug(g)",
	.action_msg	= "DEBUG",
पूर्ण;
#पूर्ण_अगर

व्योम kgdb_panic(स्थिर अक्षर *msg)
अणु
	अगर (!kgdb_io_module_रेजिस्टरed)
		वापस;

	/*
	 * We करोn't want to get stuck रुकोing क्रम input from user अगर
	 * "panic_timeout" indicates the प्रणाली should स्वतःmatically
	 * reboot on panic.
	 */
	अगर (panic_समयout)
		वापस;

	अगर (dbg_kdb_mode)
		kdb_म_लिखो("PANIC: %s\n", msg);

	kgdb_अवरोधpoपूर्णांक();
पूर्ण

अटल व्योम kgdb_initial_अवरोधpoपूर्णांक(व्योम)
अणु
	kgdb_अवरोध_asap = 0;

	pr_crit("Waiting for connection from remote gdb...\n");
	kgdb_अवरोधpoपूर्णांक();
पूर्ण

व्योम __weak kgdb_arch_late(व्योम)
अणु
पूर्ण

व्योम __init dbg_late_init(व्योम)
अणु
	dbg_is_early = false;
	अगर (kgdb_io_module_रेजिस्टरed)
		kgdb_arch_late();
	kdb_init(KDB_INIT_FULL);

	अगर (kgdb_io_module_रेजिस्टरed && kgdb_अवरोध_asap)
		kgdb_initial_अवरोधpoपूर्णांक();
पूर्ण

अटल पूर्णांक
dbg_notअगरy_reboot(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code, व्योम *x)
अणु
	/*
	 * Take the following action on reboot notअगरy depending on value:
	 *    1 == Enter debugger
	 *    0 == [the शेष] detatch debug client
	 *   -1 == Do nothing... and use this until the board resets
	 */
	चयन (kgdbreboot) अणु
	हाल 1:
		kgdb_अवरोधpoपूर्णांक();
	हाल -1:
		जाओ करोne;
	पूर्ण
	अगर (!dbg_kdb_mode)
		gdbstub_निकास(code);
करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block dbg_reboot_notअगरier = अणु
	.notअगरier_call		= dbg_notअगरy_reboot,
	.next			= शून्य,
	.priority		= पूर्णांक_उच्च,
पूर्ण;

अटल व्योम kgdb_रेजिस्टर_callbacks(व्योम)
अणु
	अगर (!kgdb_io_module_रेजिस्टरed) अणु
		kgdb_io_module_रेजिस्टरed = 1;
		kgdb_arch_init();
		अगर (!dbg_is_early)
			kgdb_arch_late();
		रेजिस्टर_module_notअगरier(&dbg_module_load_nb);
		रेजिस्टर_reboot_notअगरier(&dbg_reboot_notअगरier);
#अगर_घोषित CONFIG_MAGIC_SYSRQ
		रेजिस्टर_sysrq_key('g', &sysrq_dbg_op);
#पूर्ण_अगर
		अगर (kgdb_use_con && !kgdb_con_रेजिस्टरed) अणु
			रेजिस्टर_console(&kgdbcons);
			kgdb_con_रेजिस्टरed = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम kgdb_unरेजिस्टर_callbacks(व्योम)
अणु
	/*
	 * When this routine is called KGDB should unरेजिस्टर from
	 * handlers and clean up, making sure it is not handling any
	 * अवरोध exceptions at the समय.
	 */
	अगर (kgdb_io_module_रेजिस्टरed) अणु
		kgdb_io_module_रेजिस्टरed = 0;
		unरेजिस्टर_reboot_notअगरier(&dbg_reboot_notअगरier);
		unरेजिस्टर_module_notअगरier(&dbg_module_load_nb);
		kgdb_arch_निकास();
#अगर_घोषित CONFIG_MAGIC_SYSRQ
		unरेजिस्टर_sysrq_key('g', &sysrq_dbg_op);
#पूर्ण_अगर
		अगर (kgdb_con_रेजिस्टरed) अणु
			unरेजिस्टर_console(&kgdbcons);
			kgdb_con_रेजिस्टरed = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	kgdb_रेजिस्टर_io_module - रेजिस्टर KGDB IO module
 *	@new_dbg_io_ops: the io ops vector
 *
 *	Register it with the KGDB core.
 */
पूर्णांक kgdb_रेजिस्टर_io_module(काष्ठा kgdb_io *new_dbg_io_ops)
अणु
	काष्ठा kgdb_io *old_dbg_io_ops;
	पूर्णांक err;

	spin_lock(&kgdb_registration_lock);

	old_dbg_io_ops = dbg_io_ops;
	अगर (old_dbg_io_ops) अणु
		अगर (!old_dbg_io_ops->deinit) अणु
			spin_unlock(&kgdb_registration_lock);

			pr_err("KGDB I/O driver %s can't replace %s.\n",
				new_dbg_io_ops->name, old_dbg_io_ops->name);
			वापस -EBUSY;
		पूर्ण
		pr_info("Replacing I/O driver %s with %s\n",
			old_dbg_io_ops->name, new_dbg_io_ops->name);
	पूर्ण

	अगर (new_dbg_io_ops->init) अणु
		err = new_dbg_io_ops->init();
		अगर (err) अणु
			spin_unlock(&kgdb_registration_lock);
			वापस err;
		पूर्ण
	पूर्ण

	dbg_io_ops = new_dbg_io_ops;

	spin_unlock(&kgdb_registration_lock);

	अगर (old_dbg_io_ops) अणु
		old_dbg_io_ops->deinit();
		वापस 0;
	पूर्ण

	pr_info("Registered I/O driver %s\n", new_dbg_io_ops->name);

	/* Arm KGDB now. */
	kgdb_रेजिस्टर_callbacks();

	अगर (kgdb_अवरोध_asap &&
	    (!dbg_is_early || IS_ENABLED(CONFIG_ARCH_HAS_EARLY_DEBUG)))
		kgdb_initial_अवरोधpoपूर्णांक();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kgdb_रेजिस्टर_io_module);

/**
 *	kgdb_unरेजिस्टर_io_module - unरेजिस्टर KGDB IO module
 *	@old_dbg_io_ops: the io ops vector
 *
 *	Unरेजिस्टर it with the KGDB core.
 */
व्योम kgdb_unरेजिस्टर_io_module(काष्ठा kgdb_io *old_dbg_io_ops)
अणु
	BUG_ON(kgdb_connected);

	/*
	 * KGDB is no दीर्घer able to communicate out, so
	 * unरेजिस्टर our callbacks and reset state.
	 */
	kgdb_unरेजिस्टर_callbacks();

	spin_lock(&kgdb_registration_lock);

	WARN_ON_ONCE(dbg_io_ops != old_dbg_io_ops);
	dbg_io_ops = शून्य;

	spin_unlock(&kgdb_registration_lock);

	अगर (old_dbg_io_ops->deinit)
		old_dbg_io_ops->deinit();

	pr_info("Unregistered I/O driver %s, debugger disabled\n",
		old_dbg_io_ops->name);
पूर्ण
EXPORT_SYMBOL_GPL(kgdb_unरेजिस्टर_io_module);

पूर्णांक dbg_io_get_अक्षर(व्योम)
अणु
	पूर्णांक ret = dbg_io_ops->पढ़ो_अक्षर();
	अगर (ret == NO_POLL_CHAR)
		वापस -1;
	अगर (!dbg_kdb_mode)
		वापस ret;
	अगर (ret == 127)
		वापस 8;
	वापस ret;
पूर्ण

/**
 * kgdb_अवरोधpoपूर्णांक - generate अवरोधpoपूर्णांक exception
 *
 * This function will generate a अवरोधpoपूर्णांक exception.  It is used at the
 * beginning of a program to sync up with a debugger and can be used
 * otherwise as a quick means to stop program execution and "break" पूर्णांकo
 * the debugger.
 */
noअंतरभूत व्योम kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	atomic_inc(&kgdb_setting_अवरोधpoपूर्णांक);
	wmb(); /* Sync poपूर्णांक beक्रमe अवरोधpoपूर्णांक */
	arch_kgdb_अवरोधpoपूर्णांक();
	wmb(); /* Sync poपूर्णांक after अवरोधpoपूर्णांक */
	atomic_dec(&kgdb_setting_अवरोधpoपूर्णांक);
पूर्ण
EXPORT_SYMBOL_GPL(kgdb_अवरोधpoपूर्णांक);

अटल पूर्णांक __init opt_kgdb_रुको(अक्षर *str)
अणु
	kgdb_अवरोध_asap = 1;

	kdb_init(KDB_INIT_EARLY);
	अगर (kgdb_io_module_रेजिस्टरed &&
	    IS_ENABLED(CONFIG_ARCH_HAS_EARLY_DEBUG))
		kgdb_initial_अवरोधpoपूर्णांक();

	वापस 0;
पूर्ण

early_param("kgdbwait", opt_kgdb_रुको);
