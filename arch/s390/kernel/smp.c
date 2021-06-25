<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  SMP related functions
 *
 *    Copyright IBM Corp. 1999, 2012
 *    Author(s): Denis Joseph Barrow,
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>,
 *
 *  based on other smp stuff by
 *    (c) 1995 Alan Cox, CymruNET Ltd  <alan@cymru.net>
 *    (c) 1998 Ingo Molnar
 *
 * The code outside of smp.c uses logical cpu numbers, only smp.c करोes
 * the translation of logical to physical cpu ids. All new code that
 * operates on physical cpu numbers needs to go पूर्णांकo smp.c.
 */

#घोषणा KMSG_COMPONENT "cpu"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/workqueue.h>
#समावेश <linux/memblock.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/cpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/kprobes.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/vसमयr.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/os_info.h>
#समावेश <यंत्र/sigp.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/topology.h>
#समावेश <यंत्र/vdso.h>
#समावेश "entry.h"

क्रमागत अणु
	ec_schedule = 0,
	ec_call_function_single,
	ec_stop_cpu,
	ec_mcck_pending,
	ec_irq_work,
पूर्ण;

क्रमागत अणु
	CPU_STATE_STANDBY,
	CPU_STATE_CONFIGURED,
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cpu *, cpu_device);

काष्ठा pcpu अणु
	काष्ठा lowcore *lowcore;	/* lowcore page(s) क्रम the cpu */
	अचिन्हित दीर्घ ec_mask;		/* bit mask क्रम ec_xxx functions */
	अचिन्हित दीर्घ ec_clk;		/* sigp बारtamp क्रम ec_xxx */
	चिन्हित अक्षर state;		/* physical cpu state */
	चिन्हित अक्षर polarization;	/* physical polarization */
	u16 address;			/* physical cpu address */
पूर्ण;

अटल u8 boot_core_type;
अटल काष्ठा pcpu pcpu_devices[NR_CPUS];

अचिन्हित पूर्णांक smp_cpu_mt_shअगरt;
EXPORT_SYMBOL(smp_cpu_mt_shअगरt);

अचिन्हित पूर्णांक smp_cpu_mtid;
EXPORT_SYMBOL(smp_cpu_mtid);

#अगर_घोषित CONFIG_CRASH_DUMP
__vector128 __initdata boot_cpu_vector_save_area[__NUM_VXRS];
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक smp_max_thपढ़ोs __initdata = -1U;

अटल पूर्णांक __init early_nosmt(अक्षर *s)
अणु
	smp_max_thपढ़ोs = 1;
	वापस 0;
पूर्ण
early_param("nosmt", early_nosmt);

अटल पूर्णांक __init early_smt(अक्षर *s)
अणु
	get_option(&s, &smp_max_thपढ़ोs);
	वापस 0;
पूर्ण
early_param("smt", early_smt);

/*
 * The smp_cpu_state_mutex must be held when changing the state or polarization
 * member of a pcpu data काष्ठाure within the pcpu_devices arreay.
 */
DEFINE_MUTEX(smp_cpu_state_mutex);

/*
 * Signal processor helper functions.
 */
अटल अंतरभूत पूर्णांक __pcpu_sigp_relax(u16 addr, u8 order, अचिन्हित दीर्घ parm)
अणु
	पूर्णांक cc;

	जबतक (1) अणु
		cc = __pcpu_sigp(addr, order, parm, शून्य);
		अगर (cc != SIGP_CC_BUSY)
			वापस cc;
		cpu_relax();
	पूर्ण
पूर्ण

अटल पूर्णांक pcpu_sigp_retry(काष्ठा pcpu *pcpu, u8 order, u32 parm)
अणु
	पूर्णांक cc, retry;

	क्रम (retry = 0; ; retry++) अणु
		cc = __pcpu_sigp(pcpu->address, order, parm, शून्य);
		अगर (cc != SIGP_CC_BUSY)
			अवरोध;
		अगर (retry >= 3)
			udelay(10);
	पूर्ण
	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक pcpu_stopped(काष्ठा pcpu *pcpu)
अणु
	u32 status;

	अगर (__pcpu_sigp(pcpu->address, SIGP_SENSE,
			0, &status) != SIGP_CC_STATUS_STORED)
		वापस 0;
	वापस !!(status & (SIGP_STATUS_CHECK_STOP|SIGP_STATUS_STOPPED));
पूर्ण

अटल अंतरभूत पूर्णांक pcpu_running(काष्ठा pcpu *pcpu)
अणु
	अगर (__pcpu_sigp(pcpu->address, SIGP_SENSE_RUNNING,
			0, शून्य) != SIGP_CC_STATUS_STORED)
		वापस 1;
	/* Status stored condition code is equivalent to cpu not running. */
	वापस 0;
पूर्ण

/*
 * Find काष्ठा pcpu by cpu address.
 */
अटल काष्ठा pcpu *pcpu_find_address(स्थिर काष्ठा cpumask *mask, u16 address)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		अगर (pcpu_devices[cpu].address == address)
			वापस pcpu_devices + cpu;
	वापस शून्य;
पूर्ण

अटल व्योम pcpu_ec_call(काष्ठा pcpu *pcpu, पूर्णांक ec_bit)
अणु
	पूर्णांक order;

	अगर (test_and_set_bit(ec_bit, &pcpu->ec_mask))
		वापस;
	order = pcpu_running(pcpu) ? SIGP_EXTERNAL_CALL : SIGP_EMERGENCY_SIGNAL;
	pcpu->ec_clk = get_tod_घड़ी_fast();
	pcpu_sigp_retry(pcpu, order, 0);
पूर्ण

अटल पूर्णांक pcpu_alloc_lowcore(काष्ठा pcpu *pcpu, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ async_stack, nodat_stack, mcck_stack;
	काष्ठा lowcore *lc;

	अगर (pcpu != &pcpu_devices[0]) अणु
		pcpu->lowcore =	(काष्ठा lowcore *)
			__get_मुक्त_pages(GFP_KERNEL | GFP_DMA, LC_ORDER);
		nodat_stack = __get_मुक्त_pages(GFP_KERNEL, THREAD_SIZE_ORDER);
		अगर (!pcpu->lowcore || !nodat_stack)
			जाओ out;
	पूर्ण अन्यथा अणु
		nodat_stack = pcpu->lowcore->nodat_stack - STACK_INIT_OFFSET;
	पूर्ण
	async_stack = stack_alloc();
	mcck_stack = stack_alloc();
	अगर (!async_stack || !mcck_stack)
		जाओ out_stack;
	lc = pcpu->lowcore;
	स_नकल(lc, &S390_lowcore, 512);
	स_रखो((अक्षर *) lc + 512, 0, माप(*lc) - 512);
	lc->async_stack = async_stack + STACK_INIT_OFFSET;
	lc->nodat_stack = nodat_stack + STACK_INIT_OFFSET;
	lc->mcck_stack = mcck_stack + STACK_INIT_OFFSET;
	lc->cpu_nr = cpu;
	lc->spinlock_lockval = arch_spin_lockval(cpu);
	lc->spinlock_index = 0;
	lc->br_r1_trampoline = 0x07f1;	/* br %r1 */
	lc->वापस_lpswe = gen_lpswe(__LC_RETURN_PSW);
	lc->वापस_mcck_lpswe = gen_lpswe(__LC_RETURN_MCCK_PSW);
	अगर (nmi_alloc_per_cpu(lc))
		जाओ out_stack;
	lowcore_ptr[cpu] = lc;
	pcpu_sigp_retry(pcpu, SIGP_SET_PREFIX, (u32)(अचिन्हित दीर्घ) lc);
	वापस 0;

out_stack:
	stack_मुक्त(mcck_stack);
	stack_मुक्त(async_stack);
out:
	अगर (pcpu != &pcpu_devices[0]) अणु
		मुक्त_pages(nodat_stack, THREAD_SIZE_ORDER);
		मुक्त_pages((अचिन्हित दीर्घ) pcpu->lowcore, LC_ORDER);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल व्योम pcpu_मुक्त_lowcore(काष्ठा pcpu *pcpu)
अणु
	अचिन्हित दीर्घ async_stack, nodat_stack, mcck_stack, lowcore;

	nodat_stack = pcpu->lowcore->nodat_stack - STACK_INIT_OFFSET;
	async_stack = pcpu->lowcore->async_stack - STACK_INIT_OFFSET;
	mcck_stack = pcpu->lowcore->mcck_stack - STACK_INIT_OFFSET;
	lowcore = (अचिन्हित दीर्घ) pcpu->lowcore;

	pcpu_sigp_retry(pcpu, SIGP_SET_PREFIX, 0);
	lowcore_ptr[pcpu - pcpu_devices] = शून्य;
	nmi_मुक्त_per_cpu(pcpu->lowcore);
	stack_मुक्त(async_stack);
	stack_मुक्त(mcck_stack);
	अगर (pcpu == &pcpu_devices[0])
		वापस;
	मुक्त_pages(nodat_stack, THREAD_SIZE_ORDER);
	मुक्त_pages(lowcore, LC_ORDER);
पूर्ण

अटल व्योम pcpu_prepare_secondary(काष्ठा pcpu *pcpu, पूर्णांक cpu)
अणु
	काष्ठा lowcore *lc = pcpu->lowcore;

	cpumask_set_cpu(cpu, &init_mm.context.cpu_attach_mask);
	cpumask_set_cpu(cpu, mm_cpumask(&init_mm));
	lc->cpu_nr = cpu;
	lc->spinlock_lockval = arch_spin_lockval(cpu);
	lc->spinlock_index = 0;
	lc->percpu_offset = __per_cpu_offset[cpu];
	lc->kernel_asce = S390_lowcore.kernel_asce;
	lc->user_asce = s390_invalid_asce;
	lc->machine_flags = S390_lowcore.machine_flags;
	lc->user_समयr = lc->प्रणाली_समयr =
		lc->steal_समयr = lc->avg_steal_समयr = 0;
	__ctl_store(lc->cregs_save_area, 0, 15);
	lc->cregs_save_area[1] = lc->kernel_asce;
	lc->cregs_save_area[7] = lc->user_asce;
	save_access_regs((अचिन्हित पूर्णांक *) lc->access_regs_save_area);
	स_नकल(lc->stfle_fac_list, S390_lowcore.stfle_fac_list,
	       माप(lc->stfle_fac_list));
	स_नकल(lc->alt_stfle_fac_list, S390_lowcore.alt_stfle_fac_list,
	       माप(lc->alt_stfle_fac_list));
	arch_spin_lock_setup(cpu);
पूर्ण

अटल व्योम pcpu_attach_task(काष्ठा pcpu *pcpu, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा lowcore *lc = pcpu->lowcore;

	lc->kernel_stack = (अचिन्हित दीर्घ) task_stack_page(tsk)
		+ THREAD_SIZE - STACK_FRAME_OVERHEAD - माप(काष्ठा pt_regs);
	lc->current_task = (अचिन्हित दीर्घ) tsk;
	lc->lpp = LPP_MAGIC;
	lc->current_pid = tsk->pid;
	lc->user_समयr = tsk->thपढ़ो.user_समयr;
	lc->guest_समयr = tsk->thपढ़ो.guest_समयr;
	lc->प्रणाली_समयr = tsk->thपढ़ो.प्रणाली_समयr;
	lc->hardirq_समयr = tsk->thपढ़ो.hardirq_समयr;
	lc->softirq_समयr = tsk->thपढ़ो.softirq_समयr;
	lc->steal_समयr = 0;
पूर्ण

अटल व्योम pcpu_start_fn(काष्ठा pcpu *pcpu, व्योम (*func)(व्योम *), व्योम *data)
अणु
	काष्ठा lowcore *lc = pcpu->lowcore;

	lc->restart_stack = lc->nodat_stack;
	lc->restart_fn = (अचिन्हित दीर्घ) func;
	lc->restart_data = (अचिन्हित दीर्घ) data;
	lc->restart_source = -1UL;
	pcpu_sigp_retry(pcpu, SIGP_RESTART, 0);
पूर्ण

/*
 * Call function via PSW restart on pcpu and stop the current cpu.
 */
अटल व्योम __pcpu_delegate(व्योम (*func)(व्योम*), व्योम *data)
अणु
	func(data);	/* should not वापस */
पूर्ण

अटल व्योम __no_sanitize_address pcpu_delegate(काष्ठा pcpu *pcpu,
						व्योम (*func)(व्योम *),
						व्योम *data, अचिन्हित दीर्घ stack)
अणु
	काष्ठा lowcore *lc = lowcore_ptr[pcpu - pcpu_devices];
	अचिन्हित दीर्घ source_cpu = stap();

	__load_psw_mask(PSW_KERNEL_BITS | PSW_MASK_DAT);
	अगर (pcpu->address == source_cpu)
		CALL_ON_STACK(__pcpu_delegate, stack, 2, func, data);
	/* Stop target cpu (अगर func वापसs this stops the current cpu). */
	pcpu_sigp_retry(pcpu, SIGP_STOP, 0);
	/* Restart func on the target cpu and stop the current cpu. */
	mem_assign_असलolute(lc->restart_stack, stack);
	mem_assign_असलolute(lc->restart_fn, (अचिन्हित दीर्घ) func);
	mem_assign_असलolute(lc->restart_data, (अचिन्हित दीर्घ) data);
	mem_assign_असलolute(lc->restart_source, source_cpu);
	__bpon();
	यंत्र अस्थिर(
		"0:	sigp	0,%0,%2	# sigp restart to target cpu\n"
		"	brc	2,0b	# busy, try again\n"
		"1:	sigp	0,%1,%3	# sigp stop to current cpu\n"
		"	brc	2,1b	# busy, try again\n"
		: : "d" (pcpu->address), "d" (source_cpu),
		    "K" (SIGP_RESTART), "K" (SIGP_STOP)
		: "0", "1", "cc");
	क्रम (;;) ;
पूर्ण

/*
 * Enable additional logical cpus क्रम multi-thपढ़ोing.
 */
अटल पूर्णांक pcpu_set_smt(अचिन्हित पूर्णांक mtid)
अणु
	पूर्णांक cc;

	अगर (smp_cpu_mtid == mtid)
		वापस 0;
	cc = __pcpu_sigp(0, SIGP_SET_MULTI_THREADING, mtid, शून्य);
	अगर (cc == 0) अणु
		smp_cpu_mtid = mtid;
		smp_cpu_mt_shअगरt = 0;
		जबतक (smp_cpu_mtid >= (1U << smp_cpu_mt_shअगरt))
			smp_cpu_mt_shअगरt++;
		pcpu_devices[0].address = stap();
	पूर्ण
	वापस cc;
पूर्ण

/*
 * Call function on an online CPU.
 */
व्योम smp_call_online_cpu(व्योम (*func)(व्योम *), व्योम *data)
अणु
	काष्ठा pcpu *pcpu;

	/* Use the current cpu अगर it is online. */
	pcpu = pcpu_find_address(cpu_online_mask, stap());
	अगर (!pcpu)
		/* Use the first online cpu. */
		pcpu = pcpu_devices + cpumask_first(cpu_online_mask);
	pcpu_delegate(pcpu, func, data, (अचिन्हित दीर्घ) restart_stack);
पूर्ण

/*
 * Call function on the ipl CPU.
 */
व्योम smp_call_ipl_cpu(व्योम (*func)(व्योम *), व्योम *data)
अणु
	काष्ठा lowcore *lc = pcpu_devices->lowcore;

	अगर (pcpu_devices[0].address == stap())
		lc = &S390_lowcore;

	pcpu_delegate(&pcpu_devices[0], func, data,
		      lc->nodat_stack);
पूर्ण

पूर्णांक smp_find_processor_id(u16 address)
अणु
	पूर्णांक cpu;

	क्रम_each_present_cpu(cpu)
		अगर (pcpu_devices[cpu].address == address)
			वापस cpu;
	वापस -1;
पूर्ण

व्योम schedule_mcck_handler(व्योम)
अणु
	pcpu_ec_call(pcpu_devices + smp_processor_id(), ec_mcck_pending);
पूर्ण

bool notrace arch_vcpu_is_preempted(पूर्णांक cpu)
अणु
	अगर (test_cpu_flag_of(CIF_ENABLED_WAIT, cpu))
		वापस false;
	अगर (pcpu_running(pcpu_devices + cpu))
		वापस false;
	वापस true;
पूर्ण
EXPORT_SYMBOL(arch_vcpu_is_preempted);

व्योम notrace smp_yield_cpu(पूर्णांक cpu)
अणु
	अगर (!MACHINE_HAS_DIAG9C)
		वापस;
	diag_stat_inc_norecursion(DIAG_STAT_X09C);
	यंत्र अस्थिर("diag %0,0,0x9c"
		     : : "d" (pcpu_devices[cpu].address));
पूर्ण
EXPORT_SYMBOL_GPL(smp_yield_cpu);

/*
 * Send cpus emergency shutकरोwn संकेत. This gives the cpus the
 * opportunity to complete outstanding पूर्णांकerrupts.
 */
व्योम notrace smp_emergency_stop(व्योम)
अणु
	अटल arch_spinlock_t lock = __ARCH_SPIN_LOCK_UNLOCKED;
	अटल cpumask_t cpumask;
	u64 end;
	पूर्णांक cpu;

	arch_spin_lock(&lock);
	cpumask_copy(&cpumask, cpu_online_mask);
	cpumask_clear_cpu(smp_processor_id(), &cpumask);

	end = get_tod_घड़ी() + (1000000UL << 12);
	क्रम_each_cpu(cpu, &cpumask) अणु
		काष्ठा pcpu *pcpu = pcpu_devices + cpu;
		set_bit(ec_stop_cpu, &pcpu->ec_mask);
		जबतक (__pcpu_sigp(pcpu->address, SIGP_EMERGENCY_SIGNAL,
				   0, शून्य) == SIGP_CC_BUSY &&
		       get_tod_घड़ी() < end)
			cpu_relax();
	पूर्ण
	जबतक (get_tod_घड़ी() < end) अणु
		क्रम_each_cpu(cpu, &cpumask)
			अगर (pcpu_stopped(pcpu_devices + cpu))
				cpumask_clear_cpu(cpu, &cpumask);
		अगर (cpumask_empty(&cpumask))
			अवरोध;
		cpu_relax();
	पूर्ण
	arch_spin_unlock(&lock);
पूर्ण
NOKPROBE_SYMBOL(smp_emergency_stop);

/*
 * Stop all cpus but the current one.
 */
व्योम smp_send_stop(व्योम)
अणु
	पूर्णांक cpu;

	/* Disable all पूर्णांकerrupts/machine checks */
	__load_psw_mask(PSW_KERNEL_BITS | PSW_MASK_DAT);
	trace_hardirqs_off();

	debug_set_critical();

	अगर (oops_in_progress)
		smp_emergency_stop();

	/* stop all processors */
	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu == smp_processor_id())
			जारी;
		pcpu_sigp_retry(pcpu_devices + cpu, SIGP_STOP, 0);
		जबतक (!pcpu_stopped(pcpu_devices + cpu))
			cpu_relax();
	पूर्ण
पूर्ण

/*
 * This is the मुख्य routine where commands issued by other
 * cpus are handled.
 */
अटल व्योम smp_handle_ext_call(व्योम)
अणु
	अचिन्हित दीर्घ bits;

	/* handle bit संकेत बाह्यal calls */
	bits = xchg(&pcpu_devices[smp_processor_id()].ec_mask, 0);
	अगर (test_bit(ec_stop_cpu, &bits))
		smp_stop_cpu();
	अगर (test_bit(ec_schedule, &bits))
		scheduler_ipi();
	अगर (test_bit(ec_call_function_single, &bits))
		generic_smp_call_function_single_पूर्णांकerrupt();
	अगर (test_bit(ec_mcck_pending, &bits))
		__s390_handle_mcck();
	अगर (test_bit(ec_irq_work, &bits))
		irq_work_run();
पूर्ण

अटल व्योम करो_ext_call_पूर्णांकerrupt(काष्ठा ext_code ext_code,
				  अचिन्हित पूर्णांक param32, अचिन्हित दीर्घ param64)
अणु
	inc_irq_stat(ext_code.code == 0x1202 ? IRQEXT_EXC : IRQEXT_EMS);
	smp_handle_ext_call();
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		pcpu_ec_call(pcpu_devices + cpu, ec_call_function_single);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	pcpu_ec_call(pcpu_devices + cpu, ec_call_function_single);
पूर्ण

/*
 * this function sends a 'reschedule' IPI to another CPU.
 * it goes straight through and wastes no समय serializing
 * anything. Worst हाल is that we lose a reschedule ...
 */
व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	pcpu_ec_call(pcpu_devices + cpu, ec_schedule);
पूर्ण

#अगर_घोषित CONFIG_IRQ_WORK
व्योम arch_irq_work_उठाओ(व्योम)
अणु
	pcpu_ec_call(pcpu_devices + smp_processor_id(), ec_irq_work);
पूर्ण
#पूर्ण_अगर

/*
 * parameter area क्रम the set/clear control bit callbacks
 */
काष्ठा ec_creg_mask_parms अणु
	अचिन्हित दीर्घ orval;
	अचिन्हित दीर्घ andval;
	पूर्णांक cr;
पूर्ण;

/*
 * callback क्रम setting/clearing control bits
 */
अटल व्योम smp_ctl_bit_callback(व्योम *info)
अणु
	काष्ठा ec_creg_mask_parms *pp = info;
	अचिन्हित दीर्घ cregs[16];

	__ctl_store(cregs, 0, 15);
	cregs[pp->cr] = (cregs[pp->cr] & pp->andval) | pp->orval;
	__ctl_load(cregs, 0, 15);
पूर्ण

/*
 * Set a bit in a control रेजिस्टर of all cpus
 */
व्योम smp_ctl_set_bit(पूर्णांक cr, पूर्णांक bit)
अणु
	काष्ठा ec_creg_mask_parms parms = अणु 1UL << bit, -1UL, cr पूर्ण;

	on_each_cpu(smp_ctl_bit_callback, &parms, 1);
पूर्ण
EXPORT_SYMBOL(smp_ctl_set_bit);

/*
 * Clear a bit in a control रेजिस्टर of all cpus
 */
व्योम smp_ctl_clear_bit(पूर्णांक cr, पूर्णांक bit)
अणु
	काष्ठा ec_creg_mask_parms parms = अणु 0, ~(1UL << bit), cr पूर्ण;

	on_each_cpu(smp_ctl_bit_callback, &parms, 1);
पूर्ण
EXPORT_SYMBOL(smp_ctl_clear_bit);

#अगर_घोषित CONFIG_CRASH_DUMP

पूर्णांक smp_store_status(पूर्णांक cpu)
अणु
	काष्ठा pcpu *pcpu = pcpu_devices + cpu;
	अचिन्हित दीर्घ pa;

	pa = __pa(&pcpu->lowcore->भग्नing_pt_save_area);
	अगर (__pcpu_sigp_relax(pcpu->address, SIGP_STORE_STATUS_AT_ADDRESS,
			      pa) != SIGP_CC_ORDER_CODE_ACCEPTED)
		वापस -EIO;
	अगर (!MACHINE_HAS_VX && !MACHINE_HAS_GS)
		वापस 0;
	pa = __pa(pcpu->lowcore->mcesad & MCESA_ORIGIN_MASK);
	अगर (MACHINE_HAS_GS)
		pa |= pcpu->lowcore->mcesad & MCESA_LC_MASK;
	अगर (__pcpu_sigp_relax(pcpu->address, SIGP_STORE_ADDITIONAL_STATUS,
			      pa) != SIGP_CC_ORDER_CODE_ACCEPTED)
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * Collect CPU state of the previous, crashed प्रणाली.
 * There are four हालs:
 * 1) standard zfcp/nvme dump
 *    condition: OLDMEM_BASE == शून्य && is_ipl_type_dump() == true
 *    The state क्रम all CPUs except the boot CPU needs to be collected
 *    with sigp stop-and-store-status. The boot CPU state is located in
 *    the असलolute lowcore of the memory stored in the HSA. The zcore code
 *    will copy the boot CPU state from the HSA.
 * 2) stand-alone kdump क्रम SCSI/NVMe (zfcp/nvme dump with swapped memory)
 *    condition: OLDMEM_BASE != शून्य && is_ipl_type_dump() == true
 *    The state क्रम all CPUs except the boot CPU needs to be collected
 *    with sigp stop-and-store-status. The firmware or the boot-loader
 *    stored the रेजिस्टरs of the boot CPU in the असलolute lowcore in the
 *    memory of the old प्रणाली.
 * 3) kdump and the old kernel did not store the CPU state,
 *    or stand-alone kdump क्रम DASD
 *    condition: OLDMEM_BASE != शून्य && !is_kdump_kernel()
 *    The state क्रम all CPUs except the boot CPU needs to be collected
 *    with sigp stop-and-store-status. The kexec code or the boot-loader
 *    stored the रेजिस्टरs of the boot CPU in the memory of the old प्रणाली.
 * 4) kdump and the old kernel stored the CPU state
 *    condition: OLDMEM_BASE != शून्य && is_kdump_kernel()
 *    This हाल करोes not exist क्रम s390 anymore, setup_arch explicitly
 *    deactivates the elfcorehdr= kernel parameter
 */
अटल __init व्योम smp_save_cpu_vxrs(काष्ठा save_area *sa, u16 addr,
				     bool is_boot_cpu, अचिन्हित दीर्घ page)
अणु
	__vector128 *vxrs = (__vector128 *) page;

	अगर (is_boot_cpu)
		vxrs = boot_cpu_vector_save_area;
	अन्यथा
		__pcpu_sigp_relax(addr, SIGP_STORE_ADDITIONAL_STATUS, page);
	save_area_add_vxrs(sa, vxrs);
पूर्ण

अटल __init व्योम smp_save_cpu_regs(काष्ठा save_area *sa, u16 addr,
				     bool is_boot_cpu, अचिन्हित दीर्घ page)
अणु
	व्योम *regs = (व्योम *) page;

	अगर (is_boot_cpu)
		copy_oldmem_kernel(regs, (व्योम *) __LC_FPREGS_SAVE_AREA, 512);
	अन्यथा
		__pcpu_sigp_relax(addr, SIGP_STORE_STATUS_AT_ADDRESS, page);
	save_area_add_regs(sa, regs);
पूर्ण

व्योम __init smp_save_dump_cpus(व्योम)
अणु
	पूर्णांक addr, boot_cpu_addr, max_cpu_addr;
	काष्ठा save_area *sa;
	अचिन्हित दीर्घ page;
	bool is_boot_cpu;

	अगर (!(OLDMEM_BASE || is_ipl_type_dump()))
		/* No previous प्रणाली present, normal boot. */
		वापस;
	/* Allocate a page as dumping area क्रम the store status sigps */
	page = memblock_phys_alloc_range(PAGE_SIZE, PAGE_SIZE, 0, 1UL << 31);
	अगर (!page)
		panic("ERROR: Failed to allocate %lx bytes below %lx\n",
		      PAGE_SIZE, 1UL << 31);

	/* Set multi-thपढ़ोing state to the previous प्रणाली. */
	pcpu_set_smt(sclp.mtid_prev);
	boot_cpu_addr = stap();
	max_cpu_addr = SCLP_MAX_CORES << sclp.mtid_prev;
	क्रम (addr = 0; addr <= max_cpu_addr; addr++) अणु
		अगर (__pcpu_sigp_relax(addr, SIGP_SENSE, 0) ==
		    SIGP_CC_NOT_OPERATIONAL)
			जारी;
		is_boot_cpu = (addr == boot_cpu_addr);
		/* Allocate save area */
		sa = save_area_alloc(is_boot_cpu);
		अगर (!sa)
			panic("could not allocate memory for save area\n");
		अगर (MACHINE_HAS_VX)
			/* Get the vector रेजिस्टरs */
			smp_save_cpu_vxrs(sa, addr, is_boot_cpu, page);
		/*
		 * For a zfcp/nvme dump OLDMEM_BASE == शून्य and the रेजिस्टरs
		 * of the boot CPU are stored in the HSA. To retrieve
		 * these रेजिस्टरs an SCLP request is required which is
		 * करोne by drivers/s390/अक्षर/zcore.c:init_cpu_info()
		 */
		अगर (!is_boot_cpu || OLDMEM_BASE)
			/* Get the CPU रेजिस्टरs */
			smp_save_cpu_regs(sa, addr, is_boot_cpu, page);
	पूर्ण
	memblock_मुक्त(page, PAGE_SIZE);
	diag_dma_ops.diag308_reset();
	pcpu_set_smt(0);
पूर्ण
#पूर्ण_अगर /* CONFIG_CRASH_DUMP */

व्योम smp_cpu_set_polarization(पूर्णांक cpu, पूर्णांक val)
अणु
	pcpu_devices[cpu].polarization = val;
पूर्ण

पूर्णांक smp_cpu_get_polarization(पूर्णांक cpu)
अणु
	वापस pcpu_devices[cpu].polarization;
पूर्ण

पूर्णांक smp_cpu_get_cpu_address(पूर्णांक cpu)
अणु
	वापस pcpu_devices[cpu].address;
पूर्ण

अटल व्योम __ref smp_get_core_info(काष्ठा sclp_core_info *info, पूर्णांक early)
अणु
	अटल पूर्णांक use_sigp_detection;
	पूर्णांक address;

	अगर (use_sigp_detection || sclp_get_core_info(info, early)) अणु
		use_sigp_detection = 1;
		क्रम (address = 0;
		     address < (SCLP_MAX_CORES << smp_cpu_mt_shअगरt);
		     address += (1U << smp_cpu_mt_shअगरt)) अणु
			अगर (__pcpu_sigp_relax(address, SIGP_SENSE, 0) ==
			    SIGP_CC_NOT_OPERATIONAL)
				जारी;
			info->core[info->configured].core_id =
				address >> smp_cpu_mt_shअगरt;
			info->configured++;
		पूर्ण
		info->combined = info->configured;
	पूर्ण
पूर्ण

अटल पूर्णांक smp_add_present_cpu(पूर्णांक cpu);

अटल पूर्णांक smp_add_core(काष्ठा sclp_core_entry *core, cpumask_t *avail,
			bool configured, bool early)
अणु
	काष्ठा pcpu *pcpu;
	पूर्णांक cpu, nr, i;
	u16 address;

	nr = 0;
	अगर (sclp.has_core_type && core->type != boot_core_type)
		वापस nr;
	cpu = cpumask_first(avail);
	address = core->core_id << smp_cpu_mt_shअगरt;
	क्रम (i = 0; (i <= smp_cpu_mtid) && (cpu < nr_cpu_ids); i++) अणु
		अगर (pcpu_find_address(cpu_present_mask, address + i))
			जारी;
		pcpu = pcpu_devices + cpu;
		pcpu->address = address + i;
		अगर (configured)
			pcpu->state = CPU_STATE_CONFIGURED;
		अन्यथा
			pcpu->state = CPU_STATE_STANDBY;
		smp_cpu_set_polarization(cpu, POLARIZATION_UNKNOWN);
		set_cpu_present(cpu, true);
		अगर (!early && smp_add_present_cpu(cpu) != 0)
			set_cpu_present(cpu, false);
		अन्यथा
			nr++;
		cpumask_clear_cpu(cpu, avail);
		cpu = cpumask_next(cpu, avail);
	पूर्ण
	वापस nr;
पूर्ण

अटल पूर्णांक __smp_rescan_cpus(काष्ठा sclp_core_info *info, bool early)
अणु
	काष्ठा sclp_core_entry *core;
	अटल cpumask_t avail;
	bool configured;
	u16 core_id;
	पूर्णांक nr, i;

	get_online_cpus();
	mutex_lock(&smp_cpu_state_mutex);
	nr = 0;
	cpumask_xor(&avail, cpu_possible_mask, cpu_present_mask);
	/*
	 * Add IPL core first (which got logical CPU number 0) to make sure
	 * that all SMT thपढ़ोs get subsequent logical CPU numbers.
	 */
	अगर (early) अणु
		core_id = pcpu_devices[0].address >> smp_cpu_mt_shअगरt;
		क्रम (i = 0; i < info->configured; i++) अणु
			core = &info->core[i];
			अगर (core->core_id == core_id) अणु
				nr += smp_add_core(core, &avail, true, early);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < info->combined; i++) अणु
		configured = i < info->configured;
		nr += smp_add_core(&info->core[i], &avail, configured, early);
	पूर्ण
	mutex_unlock(&smp_cpu_state_mutex);
	put_online_cpus();
	वापस nr;
पूर्ण

व्योम __init smp_detect_cpus(व्योम)
अणु
	अचिन्हित पूर्णांक cpu, mtid, c_cpus, s_cpus;
	काष्ठा sclp_core_info *info;
	u16 address;

	/* Get CPU inक्रमmation */
	info = memblock_alloc(माप(*info), 8);
	अगर (!info)
		panic("%s: Failed to allocate %zu bytes align=0x%x\n",
		      __func__, माप(*info), 8);
	smp_get_core_info(info, 1);
	/* Find boot CPU type */
	अगर (sclp.has_core_type) अणु
		address = stap();
		क्रम (cpu = 0; cpu < info->combined; cpu++)
			अगर (info->core[cpu].core_id == address) अणु
				/* The boot cpu dictates the cpu type. */
				boot_core_type = info->core[cpu].type;
				अवरोध;
			पूर्ण
		अगर (cpu >= info->combined)
			panic("Could not find boot CPU type");
	पूर्ण

	/* Set multi-thपढ़ोing state क्रम the current प्रणाली */
	mtid = boot_core_type ? sclp.mtid : sclp.mtid_cp;
	mtid = (mtid < smp_max_thपढ़ोs) ? mtid : smp_max_thपढ़ोs - 1;
	pcpu_set_smt(mtid);

	/* Prपूर्णांक number of CPUs */
	c_cpus = s_cpus = 0;
	क्रम (cpu = 0; cpu < info->combined; cpu++) अणु
		अगर (sclp.has_core_type &&
		    info->core[cpu].type != boot_core_type)
			जारी;
		अगर (cpu < info->configured)
			c_cpus += smp_cpu_mtid + 1;
		अन्यथा
			s_cpus += smp_cpu_mtid + 1;
	पूर्ण
	pr_info("%d configured CPUs, %d standby CPUs\n", c_cpus, s_cpus);

	/* Add CPUs present at boot */
	__smp_rescan_cpus(info, true);
	memblock_मुक्त_early((अचिन्हित दीर्घ)info, माप(*info));
पूर्ण

अटल व्योम smp_init_secondary(व्योम)
अणु
	पूर्णांक cpu = raw_smp_processor_id();

	S390_lowcore.last_update_घड़ी = get_tod_घड़ी();
	restore_access_regs(S390_lowcore.access_regs_save_area);
	cpu_init();
	rcu_cpu_starting(cpu);
	preempt_disable();
	init_cpu_समयr();
	vसमय_init();
	vdso_अ_लोpu_init();
	pfault_init();
	notअगरy_cpu_starting(cpu);
	अगर (topology_cpu_dedicated(cpu))
		set_cpu_flag(CIF_DEDICATED_CPU);
	अन्यथा
		clear_cpu_flag(CIF_DEDICATED_CPU);
	set_cpu_online(cpu, true);
	update_cpu_masks();
	inc_irq_stat(CPU_RST);
	local_irq_enable();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

/*
 *	Activate a secondary processor.
 */
अटल व्योम __no_sanitize_address smp_start_secondary(व्योम *cpuव्योम)
अणु
	S390_lowcore.restart_stack = (अचिन्हित दीर्घ) restart_stack;
	S390_lowcore.restart_fn = (अचिन्हित दीर्घ) करो_restart;
	S390_lowcore.restart_data = 0;
	S390_lowcore.restart_source = -1UL;
	__ctl_load(S390_lowcore.cregs_save_area, 0, 15);
	__load_psw_mask(PSW_KERNEL_BITS | PSW_MASK_DAT);
	CALL_ON_STACK_NORETURN(smp_init_secondary, S390_lowcore.kernel_stack);
पूर्ण

/* Upping and करोwning of CPUs */
पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	काष्ठा pcpu *pcpu = pcpu_devices + cpu;
	पूर्णांक rc;

	अगर (pcpu->state != CPU_STATE_CONFIGURED)
		वापस -EIO;
	अगर (pcpu_sigp_retry(pcpu, SIGP_INITIAL_CPU_RESET, 0) !=
	    SIGP_CC_ORDER_CODE_ACCEPTED)
		वापस -EIO;

	rc = pcpu_alloc_lowcore(pcpu, cpu);
	अगर (rc)
		वापस rc;
	pcpu_prepare_secondary(pcpu, cpu);
	pcpu_attach_task(pcpu, tidle);
	pcpu_start_fn(pcpu, smp_start_secondary, शून्य);
	/* Wait until cpu माला_दो itself in the online & active maps */
	जबतक (!cpu_online(cpu))
		cpu_relax();
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक setup_possible_cpus __initdata;

अटल पूर्णांक __init _setup_possible_cpus(अक्षर *s)
अणु
	get_option(&s, &setup_possible_cpus);
	वापस 0;
पूर्ण
early_param("possible_cpus", _setup_possible_cpus);

पूर्णांक __cpu_disable(व्योम)
अणु
	अचिन्हित दीर्घ cregs[16];

	/* Handle possible pending IPIs */
	smp_handle_ext_call();
	set_cpu_online(smp_processor_id(), false);
	update_cpu_masks();
	/* Disable pseuकरो page faults on this cpu. */
	pfault_fini();
	/* Disable पूर्णांकerrupt sources via control रेजिस्टर. */
	__ctl_store(cregs, 0, 15);
	cregs[0]  &= ~0x0000ee70UL;	/* disable all बाह्यal पूर्णांकerrupts */
	cregs[6]  &= ~0xff000000UL;	/* disable all I/O पूर्णांकerrupts */
	cregs[14] &= ~0x1f000000UL;	/* disable most machine checks */
	__ctl_load(cregs, 0, 15);
	clear_cpu_flag(CIF_NOHZ_DELAY);
	वापस 0;
पूर्ण

व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा pcpu *pcpu;

	/* Wait until target cpu is करोwn */
	pcpu = pcpu_devices + cpu;
	जबतक (!pcpu_stopped(pcpu))
		cpu_relax();
	pcpu_मुक्त_lowcore(pcpu);
	cpumask_clear_cpu(cpu, mm_cpumask(&init_mm));
	cpumask_clear_cpu(cpu, &init_mm.context.cpu_attach_mask);
पूर्ण

व्योम __noवापस cpu_die(व्योम)
अणु
	idle_task_निकास();
	__bpon();
	pcpu_sigp_retry(pcpu_devices + smp_processor_id(), SIGP_STOP, 0);
	क्रम (;;) ;
पूर्ण

व्योम __init smp_fill_possible_mask(व्योम)
अणु
	अचिन्हित पूर्णांक possible, sclp_max, cpu;

	sclp_max = max(sclp.mtid, sclp.mtid_cp) + 1;
	sclp_max = min(smp_max_thपढ़ोs, sclp_max);
	sclp_max = (sclp.max_cores * sclp_max) ?: nr_cpu_ids;
	possible = setup_possible_cpus ?: nr_cpu_ids;
	possible = min(possible, sclp_max);
	क्रम (cpu = 0; cpu < possible && cpu < nr_cpu_ids; cpu++)
		set_cpu_possible(cpu, true);
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	/* request the 0x1201 emergency संकेत बाह्यal पूर्णांकerrupt */
	अगर (रेजिस्टर_बाह्यal_irq(EXT_IRQ_EMERGENCY_SIG, करो_ext_call_पूर्णांकerrupt))
		panic("Couldn't request external interrupt 0x1201");
	/* request the 0x1202 बाह्यal call बाह्यal पूर्णांकerrupt */
	अगर (रेजिस्टर_बाह्यal_irq(EXT_IRQ_EXTERNAL_CALL, करो_ext_call_पूर्णांकerrupt))
		panic("Couldn't request external interrupt 0x1202");
पूर्ण

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
	काष्ठा pcpu *pcpu = pcpu_devices;

	WARN_ON(!cpu_present(0) || !cpu_online(0));
	pcpu->state = CPU_STATE_CONFIGURED;
	pcpu->lowcore = (काष्ठा lowcore *)(अचिन्हित दीर्घ) store_prefix();
	S390_lowcore.percpu_offset = __per_cpu_offset[0];
	smp_cpu_set_polarization(0, POLARIZATION_UNKNOWN);
पूर्ण

व्योम __init smp_setup_processor_id(व्योम)
अणु
	pcpu_devices[0].address = stap();
	S390_lowcore.cpu_nr = 0;
	S390_lowcore.spinlock_lockval = arch_spin_lockval(0);
	S390_lowcore.spinlock_index = 0;
पूर्ण

/*
 * the frequency of the profiling समयr can be changed
 * by writing a multiplier value पूर्णांकo /proc/profile.
 *
 * usually you want to run this on all CPUs ;)
 */
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार cpu_configure_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार count;

	mutex_lock(&smp_cpu_state_mutex);
	count = प्र_लिखो(buf, "%d\n", pcpu_devices[dev->id].state);
	mutex_unlock(&smp_cpu_state_mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार cpu_configure_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcpu *pcpu;
	पूर्णांक cpu, val, rc, i;
	अक्षर delim;

	अगर (माला_पूछो(buf, "%d %c", &val, &delim) != 1)
		वापस -EINVAL;
	अगर (val != 0 && val != 1)
		वापस -EINVAL;
	get_online_cpus();
	mutex_lock(&smp_cpu_state_mutex);
	rc = -EBUSY;
	/* disallow configuration changes of online cpus and cpu 0 */
	cpu = dev->id;
	cpu = smp_get_base_cpu(cpu);
	अगर (cpu == 0)
		जाओ out;
	क्रम (i = 0; i <= smp_cpu_mtid; i++)
		अगर (cpu_online(cpu + i))
			जाओ out;
	pcpu = pcpu_devices + cpu;
	rc = 0;
	चयन (val) अणु
	हाल 0:
		अगर (pcpu->state != CPU_STATE_CONFIGURED)
			अवरोध;
		rc = sclp_core_deconfigure(pcpu->address >> smp_cpu_mt_shअगरt);
		अगर (rc)
			अवरोध;
		क्रम (i = 0; i <= smp_cpu_mtid; i++) अणु
			अगर (cpu + i >= nr_cpu_ids || !cpu_present(cpu + i))
				जारी;
			pcpu[i].state = CPU_STATE_STANDBY;
			smp_cpu_set_polarization(cpu + i,
						 POLARIZATION_UNKNOWN);
		पूर्ण
		topology_expect_change();
		अवरोध;
	हाल 1:
		अगर (pcpu->state != CPU_STATE_STANDBY)
			अवरोध;
		rc = sclp_core_configure(pcpu->address >> smp_cpu_mt_shअगरt);
		अगर (rc)
			अवरोध;
		क्रम (i = 0; i <= smp_cpu_mtid; i++) अणु
			अगर (cpu + i >= nr_cpu_ids || !cpu_present(cpu + i))
				जारी;
			pcpu[i].state = CPU_STATE_CONFIGURED;
			smp_cpu_set_polarization(cpu + i,
						 POLARIZATION_UNKNOWN);
		पूर्ण
		topology_expect_change();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
out:
	mutex_unlock(&smp_cpu_state_mutex);
	put_online_cpus();
	वापस rc ? rc : count;
पूर्ण
अटल DEVICE_ATTR(configure, 0644, cpu_configure_show, cpu_configure_store);

अटल sमाप_प्रकार show_cpu_address(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", pcpu_devices[dev->id].address);
पूर्ण
अटल DEVICE_ATTR(address, 0444, show_cpu_address, शून्य);

अटल काष्ठा attribute *cpu_common_attrs[] = अणु
	&dev_attr_configure.attr,
	&dev_attr_address.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cpu_common_attr_group = अणु
	.attrs = cpu_common_attrs,
पूर्ण;

अटल काष्ठा attribute *cpu_online_attrs[] = अणु
	&dev_attr_idle_count.attr,
	&dev_attr_idle_समय_us.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cpu_online_attr_group = अणु
	.attrs = cpu_online_attrs,
पूर्ण;

अटल पूर्णांक smp_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *s = &per_cpu(cpu_device, cpu)->dev;

	वापस sysfs_create_group(&s->kobj, &cpu_online_attr_group);
पूर्ण

अटल पूर्णांक smp_cpu_pre_करोwn(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *s = &per_cpu(cpu_device, cpu)->dev;

	sysfs_हटाओ_group(&s->kobj, &cpu_online_attr_group);
	वापस 0;
पूर्ण

अटल पूर्णांक smp_add_present_cpu(पूर्णांक cpu)
अणु
	काष्ठा device *s;
	काष्ठा cpu *c;
	पूर्णांक rc;

	c = kzalloc(माप(*c), GFP_KERNEL);
	अगर (!c)
		वापस -ENOMEM;
	per_cpu(cpu_device, cpu) = c;
	s = &c->dev;
	c->hotpluggable = 1;
	rc = रेजिस्टर_cpu(c, cpu);
	अगर (rc)
		जाओ out;
	rc = sysfs_create_group(&s->kobj, &cpu_common_attr_group);
	अगर (rc)
		जाओ out_cpu;
	rc = topology_cpu_init(c);
	अगर (rc)
		जाओ out_topology;
	वापस 0;

out_topology:
	sysfs_हटाओ_group(&s->kobj, &cpu_common_attr_group);
out_cpu:
	unरेजिस्टर_cpu(c);
out:
	वापस rc;
पूर्ण

पूर्णांक __ref smp_rescan_cpus(व्योम)
अणु
	काष्ठा sclp_core_info *info;
	पूर्णांक nr;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	smp_get_core_info(info, 0);
	nr = __smp_rescan_cpus(info, false);
	kमुक्त(info);
	अगर (nr)
		topology_schedule_update();
	वापस 0;
पूर्ण

अटल sमाप_प्रकार __ref rescan_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf,
				  माप_प्रकार count)
अणु
	पूर्णांक rc;

	rc = lock_device_hotplug_sysfs();
	अगर (rc)
		वापस rc;
	rc = smp_rescan_cpus();
	unlock_device_hotplug();
	वापस rc ? rc : count;
पूर्ण
अटल DEVICE_ATTR_WO(rescan);

अटल पूर्णांक __init s390_smp_init(व्योम)
अणु
	पूर्णांक cpu, rc = 0;

	rc = device_create_file(cpu_subsys.dev_root, &dev_attr_rescan);
	अगर (rc)
		वापस rc;
	क्रम_each_present_cpu(cpu) अणु
		rc = smp_add_present_cpu(cpu);
		अगर (rc)
			जाओ out;
	पूर्ण

	rc = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "s390/smp:online",
			       smp_cpu_online, smp_cpu_pre_करोwn);
	rc = rc <= 0 ? rc : 0;
out:
	वापस rc;
पूर्ण
subsys_initcall(s390_smp_init);
