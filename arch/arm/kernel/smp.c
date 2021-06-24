<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/smp.c
 *
 *  Copyright (C) 2002 ARM Limited, All Rights Reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cache.h>
#समावेश <linux/profile.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/cpu.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/irq.h>
#समावेश <linux/nmi.h>
#समावेश <linux/percpu.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/completion.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/kernel_स्थिति.स>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/idmap.h>
#समावेश <यंत्र/topology.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/procinfo.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/virt.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mpu.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/ipi.h>

/*
 * as from 2.5, kernels no दीर्घer have an init_tasks काष्ठाure
 * so we need some other way of telling a new secondary core
 * where to place its SVC stack
 */
काष्ठा secondary_data secondary_data;

क्रमागत ipi_msg_type अणु
	IPI_WAKEUP,
	IPI_TIMER,
	IPI_RESCHEDULE,
	IPI_CALL_FUNC,
	IPI_CPU_STOP,
	IPI_IRQ_WORK,
	IPI_COMPLETION,
	NR_IPI,
	/*
	 * CPU_BACKTRACE is special and not included in NR_IPI
	 * or tracable with trace_ipi_*
	 */
	IPI_CPU_BACKTRACE = NR_IPI,
	/*
	 * SGI8-15 can be reserved by secure firmware, and thus may
	 * not be usable by the kernel. Please keep the above limited
	 * to at most 8 entries.
	 */
	MAX_IPI
पूर्ण;

अटल पूर्णांक ipi_irq_base __पढ़ो_mostly;
अटल पूर्णांक nr_ipi __पढ़ो_mostly = NR_IPI;
अटल काष्ठा irq_desc *ipi_desc[MAX_IPI] __पढ़ो_mostly;

अटल व्योम ipi_setup(पूर्णांक cpu);

अटल DECLARE_COMPLETION(cpu_running);

अटल काष्ठा smp_operations smp_ops __ro_after_init;

व्योम __init smp_set_ops(स्थिर काष्ठा smp_operations *ops)
अणु
	अगर (ops)
		smp_ops = *ops;
पूर्ण;

अटल अचिन्हित दीर्घ get_arch_pgd(pgd_t *pgd)
अणु
#अगर_घोषित CONFIG_ARM_LPAE
	वापस __phys_to_pfn(virt_to_phys(pgd));
#अन्यथा
	वापस virt_to_phys(pgd);
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_BIG_LITTLE) && defined(CONFIG_HARDEN_BRANCH_PREDICTOR)
अटल पूर्णांक secondary_biglittle_prepare(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!cpu_vtable[cpu])
		cpu_vtable[cpu] = kzalloc(माप(*cpu_vtable[cpu]), GFP_KERNEL);

	वापस cpu_vtable[cpu] ? 0 : -ENOMEM;
पूर्ण

अटल व्योम secondary_biglittle_init(व्योम)
अणु
	init_proc_vtable(lookup_processor(पढ़ो_cpuid_id())->proc);
पूर्ण
#अन्यथा
अटल पूर्णांक secondary_biglittle_prepare(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

अटल व्योम secondary_biglittle_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret;

	अगर (!smp_ops.smp_boot_secondary)
		वापस -ENOSYS;

	ret = secondary_biglittle_prepare(cpu);
	अगर (ret)
		वापस ret;

	/*
	 * We need to tell the secondary core where to find
	 * its stack and the page tables.
	 */
	secondary_data.stack = task_stack_page(idle) + THREAD_START_SP;
#अगर_घोषित CONFIG_ARM_MPU
	secondary_data.mpu_rgn_info = &mpu_rgn_info;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
	secondary_data.pgdir = virt_to_phys(idmap_pgd);
	secondary_data.swapper_pg_dir = get_arch_pgd(swapper_pg_dir);
#पूर्ण_अगर
	sync_cache_w(&secondary_data);

	/*
	 * Now bring the CPU पूर्णांकo our world.
	 */
	ret = smp_ops.smp_boot_secondary(cpu, idle);
	अगर (ret == 0) अणु
		/*
		 * CPU was successfully started, रुको क्रम it
		 * to come online or समय out.
		 */
		रुको_क्रम_completion_समयout(&cpu_running,
						 msecs_to_jअगरfies(1000));

		अगर (!cpu_online(cpu)) अणु
			pr_crit("CPU%u: failed to come online\n", cpu);
			ret = -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("CPU%u: failed to boot: %d\n", cpu, ret);
	पूर्ण


	स_रखो(&secondary_data, 0, माप(secondary_data));
	वापस ret;
पूर्ण

/* platक्रमm specअगरic SMP operations */
व्योम __init smp_init_cpus(व्योम)
अणु
	अगर (smp_ops.smp_init_cpus)
		smp_ops.smp_init_cpus();
पूर्ण

पूर्णांक platक्रमm_can_secondary_boot(व्योम)
अणु
	वापस !!smp_ops.smp_boot_secondary;
पूर्ण

पूर्णांक platक्रमm_can_cpu_hotplug(व्योम)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	अगर (smp_ops.cpu_समाप्त)
		वापस 1;
#पूर्ण_अगर

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक platक्रमm_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	अगर (smp_ops.cpu_समाप्त)
		वापस smp_ops.cpu_समाप्त(cpu);
	वापस 1;
पूर्ण

अटल पूर्णांक platक्रमm_cpu_disable(अचिन्हित पूर्णांक cpu)
अणु
	अगर (smp_ops.cpu_disable)
		वापस smp_ops.cpu_disable(cpu);

	वापस 0;
पूर्ण

पूर्णांक platक्रमm_can_hotplug_cpu(अचिन्हित पूर्णांक cpu)
अणु
	/* cpu_die must be specअगरied to support hotplug */
	अगर (!smp_ops.cpu_die)
		वापस 0;

	अगर (smp_ops.cpu_can_disable)
		वापस smp_ops.cpu_can_disable(cpu);

	/*
	 * By शेष, allow disabling all CPUs except the first one,
	 * since this is special on a lot of platक्रमms, e.g. because
	 * of घड़ी tick पूर्णांकerrupts.
	 */
	वापस cpu != 0;
पूर्ण

अटल व्योम ipi_tearकरोwn(पूर्णांक cpu)
अणु
	पूर्णांक i;

	अगर (WARN_ON_ONCE(!ipi_irq_base))
		वापस;

	क्रम (i = 0; i < nr_ipi; i++)
		disable_percpu_irq(ipi_irq_base + i);
पूर्ण

/*
 * __cpu_disable runs on the processor to be shutकरोwn.
 */
पूर्णांक __cpu_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक ret;

	ret = platक्रमm_cpu_disable(cpu);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_GENERIC_ARCH_TOPOLOGY
	हटाओ_cpu_topology(cpu);
#पूर्ण_अगर

	/*
	 * Take this CPU offline.  Once we clear this, we can't वापस,
	 * and we must not schedule until we're पढ़ोy to give up the cpu.
	 */
	set_cpu_online(cpu, false);
	ipi_tearकरोwn(cpu);

	/*
	 * OK - migrate IRQs away from this CPU
	 */
	irq_migrate_all_off_this_cpu();

	/*
	 * Flush user cache and TLB mappings, and then हटाओ this CPU
	 * from the vm mask set of all processes.
	 *
	 * Caches are flushed to the Level of Unअगरication Inner Shareable
	 * to ग_लिखो-back dirty lines to unअगरied caches shared by all CPUs.
	 */
	flush_cache_louis();
	local_flush_tlb_all();

	वापस 0;
पूर्ण

/*
 * called on the thपढ़ो which is asking क्रम a CPU to be shutकरोwn -
 * रुकोs until shutकरोwn has completed, or it is समयd out.
 */
व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!cpu_रुको_death(cpu, 5)) अणु
		pr_err("CPU%u: cpu didn't die\n", cpu);
		वापस;
	पूर्ण
	pr_debug("CPU%u: shutdown\n", cpu);

	clear_tasks_mm_cpumask(cpu);
	/*
	 * platक्रमm_cpu_समाप्त() is generally expected to करो the घातering off
	 * and/or cutting of घड़ीs to the dying CPU.  Optionally, this may
	 * be करोne by the CPU which is dying in preference to supporting
	 * this call, but that means there is _no_ synchronisation between
	 * the requesting CPU and the dying CPU actually losing घातer.
	 */
	अगर (!platक्रमm_cpu_समाप्त(cpu))
		pr_err("CPU%u: unable to kill\n", cpu);
पूर्ण

/*
 * Called from the idle thपढ़ो क्रम the CPU which has been shutकरोwn.
 *
 * Note that we disable IRQs here, but करो not re-enable them
 * beक्रमe वापसing to the caller. This is also the behaviour
 * of the other hotplug-cpu capable cores, so presumably coming
 * out of idle fixes this.
 */
व्योम arch_cpu_idle_dead(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	idle_task_निकास();

	local_irq_disable();

	/*
	 * Flush the data out of the L1 cache क्रम this CPU.  This must be
	 * beक्रमe the completion to ensure that data is safely written out
	 * beक्रमe platक्रमm_cpu_समाप्त() माला_लो called - which may disable
	 * *this* CPU and घातer करोwn its cache.
	 */
	flush_cache_louis();

	/*
	 * Tell __cpu_die() that this CPU is now safe to dispose of.  Once
	 * this वापसs, घातer and/or घड़ीs can be हटाओd at any poपूर्णांक
	 * from this CPU and its cache by platक्रमm_cpu_समाप्त().
	 */
	(व्योम)cpu_report_death();

	/*
	 * Ensure that the cache lines associated with that completion are
	 * written out.  This covers the हाल where _this_ CPU is करोing the
	 * घातering करोwn, to ensure that the completion is visible to the
	 * CPU रुकोing क्रम this one.
	 */
	flush_cache_louis();

	/*
	 * The actual CPU shutकरोwn procedure is at least platक्रमm (अगर not
	 * CPU) specअगरic.  This may हटाओ घातer, or it may simply spin.
	 *
	 * Platक्रमms are generally expected *NOT* to वापस from this call,
	 * although there are some which करो because they have no way to
	 * घातer करोwn the CPU.  These platक्रमms are the _only_ reason we
	 * have a वापस path which uses the fragment of assembly below.
	 *
	 * The वापस path should not be used क्रम platक्रमms which can
	 * घातer off the CPU.
	 */
	अगर (smp_ops.cpu_die)
		smp_ops.cpu_die(cpu);

	pr_warn("CPU%u: smp_ops.cpu_die() returned, trying to resuscitate\n",
		cpu);

	/*
	 * Do not वापस to the idle loop - jump back to the secondary
	 * cpu initialisation.  There's some initialisation which needs
	 * to be repeated to unकरो the effects of taking the CPU offline.
	 */
	__यंत्र__("mov	sp, %0\n"
	"	mov	fp, #0\n"
	"	b	secondary_start_kernel"
		:
		: "r" (task_stack_page(current) + THREAD_SIZE - 8));
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

/*
 * Called by both boot and secondaries to move global data पूर्णांकo
 * per-processor storage.
 */
अटल व्योम smp_store_cpu_info(अचिन्हित पूर्णांक cpuid)
अणु
	काष्ठा cpuinfo_arm *cpu_info = &per_cpu(cpu_data, cpuid);

	cpu_info->loops_per_jअगरfy = loops_per_jअगरfy;
	cpu_info->cpuid = पढ़ो_cpuid_id();

	store_cpu_topology(cpuid);
	check_cpu_icache_size(cpuid);
पूर्ण

/*
 * This is the secondary CPU boot entry.  We're using this CPUs
 * idle thपढ़ो stack, but a set of temporary page tables.
 */
यंत्रlinkage व्योम secondary_start_kernel(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = &init_mm;
	अचिन्हित पूर्णांक cpu;

	secondary_biglittle_init();

	/*
	 * The identity mapping is uncached (strongly ordered), so
	 * चयन away from it beक्रमe attempting any exclusive accesses.
	 */
	cpu_चयन_mm(mm->pgd, mm);
	local_flush_bp_all();
	enter_lazy_tlb(mm, current);
	local_flush_tlb_all();

	/*
	 * All kernel thपढ़ोs share the same mm context; grab a
	 * reference and चयन to it.
	 */
	cpu = smp_processor_id();
	mmgrab(mm);
	current->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	cpu_init();

#अगर_अघोषित CONFIG_MMU
	setup_vectors_base();
#पूर्ण_अगर
	pr_debug("CPU%u: Booted secondary processor\n", cpu);

	preempt_disable();
	trace_hardirqs_off();

	/*
	 * Give the platक्रमm a chance to करो its own initialisation.
	 */
	अगर (smp_ops.smp_secondary_init)
		smp_ops.smp_secondary_init(cpu);

	notअगरy_cpu_starting(cpu);

	ipi_setup(cpu);

	calibrate_delay();

	smp_store_cpu_info(cpu);

	/*
	 * OK, now it's safe to let the boot CPU जारी.  Wait क्रम
	 * the CPU migration code to notice that the CPU is online
	 * beक्रमe we जारी - which happens after __cpu_up वापसs.
	 */
	set_cpu_online(cpu, true);

	check_other_bugs();

	complete(&cpu_running);

	local_irq_enable();
	local_fiq_enable();
	local_abt_enable();

	/*
	 * OK, it's off to the idle thपढ़ो क्रम us
	 */
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ bogosum = 0;

	क्रम_each_online_cpu(cpu)
		bogosum += per_cpu(cpu_data, cpu).loops_per_jअगरfy;

	prपूर्णांकk(KERN_INFO "SMP: Total of %d processors activated "
	       "(%lu.%02lu BogoMIPS).\n",
	       num_online_cpus(),
	       bogosum / (500000/HZ),
	       (bogosum / (5000/HZ)) % 100);

	hyp_mode_check();
पूर्ण

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
	set_my_cpu_offset(per_cpu_offset(smp_processor_id()));
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित पूर्णांक ncores = num_possible_cpus();

	init_cpu_topology();

	smp_store_cpu_info(smp_processor_id());

	/*
	 * are we trying to boot more cores than exist?
	 */
	अगर (max_cpus > ncores)
		max_cpus = ncores;
	अगर (ncores > 1 && max_cpus) अणु
		/*
		 * Initialise the present map, which describes the set of CPUs
		 * actually populated at the present समय. A platक्रमm should
		 * re-initialize the map in the platक्रमms smp_prepare_cpus()
		 * अगर present != possible (e.g. physical hotplug).
		 */
		init_cpu_present(cpu_possible_mask);

		/*
		 * Initialise the SCU अगर there are more than one CPU
		 * and let them know where to start.
		 */
		अगर (smp_ops.smp_prepare_cpus)
			smp_ops.smp_prepare_cpus(max_cpus);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *ipi_types[NR_IPI] __tracepoपूर्णांक_string = अणु
	[IPI_WAKEUP]		= "CPU wakeup interrupts",
	[IPI_TIMER]		= "Timer broadcast interrupts",
	[IPI_RESCHEDULE]	= "Rescheduling interrupts",
	[IPI_CALL_FUNC]		= "Function call interrupts",
	[IPI_CPU_STOP]		= "CPU stop interrupts",
	[IPI_IRQ_WORK]		= "IRQ work interrupts",
	[IPI_COMPLETION]	= "completion interrupts",
पूर्ण;

अटल व्योम smp_cross_call(स्थिर काष्ठा cpumask *target, अचिन्हित पूर्णांक ipinr);

व्योम show_ipi_list(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	अचिन्हित पूर्णांक cpu, i;

	क्रम (i = 0; i < NR_IPI; i++) अणु
		अगर (!ipi_desc[i])
			जारी;

		seq_म_लिखो(p, "%*s%u: ", prec - 1, "IPI", i);

		क्रम_each_online_cpu(cpu)
			seq_म_लिखो(p, "%10u ", irq_desc_kstat_cpu(ipi_desc[i], cpu));

		seq_म_लिखो(p, " %s\n", ipi_types[i]);
	पूर्ण
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	smp_cross_call(mask, IPI_CALL_FUNC);
पूर्ण

व्योम arch_send_wakeup_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	smp_cross_call(mask, IPI_WAKEUP);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	smp_cross_call(cpumask_of(cpu), IPI_CALL_FUNC);
पूर्ण

#अगर_घोषित CONFIG_IRQ_WORK
व्योम arch_irq_work_उठाओ(व्योम)
अणु
	अगर (arch_irq_work_has_पूर्णांकerrupt())
		smp_cross_call(cpumask_of(smp_processor_id()), IPI_IRQ_WORK);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
व्योम tick_broadcast(स्थिर काष्ठा cpumask *mask)
अणु
	smp_cross_call(mask, IPI_TIMER);
पूर्ण
#पूर्ण_अगर

अटल DEFINE_RAW_SPINLOCK(stop_lock);

/*
 * ipi_cpu_stop - handle IPI from smp_send_stop()
 */
अटल व्योम ipi_cpu_stop(अचिन्हित पूर्णांक cpu)
अणु
	अगर (प्रणाली_state <= SYSTEM_RUNNING) अणु
		raw_spin_lock(&stop_lock);
		pr_crit("CPU%u: stopping\n", cpu);
		dump_stack();
		raw_spin_unlock(&stop_lock);
	पूर्ण

	set_cpu_online(cpu, false);

	local_fiq_disable();
	local_irq_disable();

	जबतक (1) अणु
		cpu_relax();
		wfe();
	पूर्ण
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा completion *, cpu_completion);

पूर्णांक रेजिस्टर_ipi_completion(काष्ठा completion *completion, पूर्णांक cpu)
अणु
	per_cpu(cpu_completion, cpu) = completion;
	वापस IPI_COMPLETION;
पूर्ण

अटल व्योम ipi_complete(अचिन्हित पूर्णांक cpu)
अणु
	complete(per_cpu(cpu_completion, cpu));
पूर्ण

/*
 * Main handler क्रम पूर्णांकer-processor पूर्णांकerrupts
 */
यंत्रlinkage व्योम __exception_irq_entry करो_IPI(पूर्णांक ipinr, काष्ठा pt_regs *regs)
अणु
	handle_IPI(ipinr, regs);
पूर्ण

अटल व्योम करो_handle_IPI(पूर्णांक ipinr)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर ((अचिन्हित)ipinr < NR_IPI)
		trace_ipi_entry_rcuidle(ipi_types[ipinr]);

	चयन (ipinr) अणु
	हाल IPI_WAKEUP:
		अवरोध;

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
	हाल IPI_TIMER:
		tick_receive_broadcast();
		अवरोध;
#पूर्ण_अगर

	हाल IPI_RESCHEDULE:
		scheduler_ipi();
		अवरोध;

	हाल IPI_CALL_FUNC:
		generic_smp_call_function_पूर्णांकerrupt();
		अवरोध;

	हाल IPI_CPU_STOP:
		ipi_cpu_stop(cpu);
		अवरोध;

#अगर_घोषित CONFIG_IRQ_WORK
	हाल IPI_IRQ_WORK:
		irq_work_run();
		अवरोध;
#पूर्ण_अगर

	हाल IPI_COMPLETION:
		ipi_complete(cpu);
		अवरोध;

	हाल IPI_CPU_BACKTRACE:
		prपूर्णांकk_nmi_enter();
		nmi_cpu_backtrace(get_irq_regs());
		prपूर्णांकk_nmi_निकास();
		अवरोध;

	शेष:
		pr_crit("CPU%u: Unknown IPI message 0x%x\n",
		        cpu, ipinr);
		अवरोध;
	पूर्ण

	अगर ((अचिन्हित)ipinr < NR_IPI)
		trace_ipi_निकास_rcuidle(ipi_types[ipinr]);
पूर्ण

/* Legacy version, should go away once all irqchips have been converted */
व्योम handle_IPI(पूर्णांक ipinr, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	irq_enter();
	करो_handle_IPI(ipinr);
	irq_निकास();

	set_irq_regs(old_regs);
पूर्ण

अटल irqवापस_t ipi_handler(पूर्णांक irq, व्योम *data)
अणु
	करो_handle_IPI(irq - ipi_irq_base);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम smp_cross_call(स्थिर काष्ठा cpumask *target, अचिन्हित पूर्णांक ipinr)
अणु
	trace_ipi_उठाओ_rcuidle(target, ipi_types[ipinr]);
	__ipi_send_mask(ipi_desc[ipinr], target);
पूर्ण

अटल व्योम ipi_setup(पूर्णांक cpu)
अणु
	पूर्णांक i;

	अगर (WARN_ON_ONCE(!ipi_irq_base))
		वापस;

	क्रम (i = 0; i < nr_ipi; i++)
		enable_percpu_irq(ipi_irq_base + i, 0);
पूर्ण

व्योम __init set_smp_ipi_range(पूर्णांक ipi_base, पूर्णांक n)
अणु
	पूर्णांक i;

	WARN_ON(n < MAX_IPI);
	nr_ipi = min(n, MAX_IPI);

	क्रम (i = 0; i < nr_ipi; i++) अणु
		पूर्णांक err;

		err = request_percpu_irq(ipi_base + i, ipi_handler,
					 "IPI", &irq_stat);
		WARN_ON(err);

		ipi_desc[i] = irq_to_desc(ipi_base + i);
		irq_set_status_flags(ipi_base + i, IRQ_HIDDEN);
	पूर्ण

	ipi_irq_base = ipi_base;

	/* Setup the boot CPU immediately */
	ipi_setup(smp_processor_id());
पूर्ण

व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	smp_cross_call(cpumask_of(cpu), IPI_RESCHEDULE);
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	अचिन्हित दीर्घ समयout;
	काष्ठा cpumask mask;

	cpumask_copy(&mask, cpu_online_mask);
	cpumask_clear_cpu(smp_processor_id(), &mask);
	अगर (!cpumask_empty(&mask))
		smp_cross_call(&mask, IPI_CPU_STOP);

	/* Wait up to one second क्रम other CPUs to stop */
	समयout = USEC_PER_SEC;
	जबतक (num_online_cpus() > 1 && समयout--)
		udelay(1);

	अगर (num_online_cpus() > 1)
		pr_warn("SMP: failed to stop secondary CPUs\n");
पूर्ण

/* In हाल panic() and panic() called at the same समय on CPU1 and CPU2,
 * and CPU 1 calls panic_smp_self_stop() beक्रमe crash_smp_send_stop()
 * CPU1 can't receive the ipi irqs from CPU2, CPU1 will be always online,
 * kdump fails. So split out the panic_smp_self_stop() and add
 * set_cpu_online(smp_processor_id(), false).
 */
व्योम panic_smp_self_stop(व्योम)
अणु
	pr_debug("CPU %u will stop doing anything useful since another CPU has paniced\n",
	         smp_processor_id());
	set_cpu_online(smp_processor_id(), false);
	जबतक (1)
		cpu_relax();
पूर्ण

/*
 * not supported here
 */
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, l_p_j_ref);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, l_p_j_ref_freq);
अटल अचिन्हित दीर्घ global_l_p_j_ref;
अटल अचिन्हित दीर्घ global_l_p_j_ref_freq;

अटल पूर्णांक cpufreq_callback(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा cpufreq_freqs *freq = data;
	काष्ठा cpumask *cpus = freq->policy->cpus;
	पूर्णांक cpu, first = cpumask_first(cpus);
	अचिन्हित पूर्णांक lpj;

	अगर (freq->flags & CPUFREQ_CONST_LOOPS)
		वापस NOTIFY_OK;

	अगर (!per_cpu(l_p_j_ref, first)) अणु
		क्रम_each_cpu(cpu, cpus) अणु
			per_cpu(l_p_j_ref, cpu) =
				per_cpu(cpu_data, cpu).loops_per_jअगरfy;
			per_cpu(l_p_j_ref_freq, cpu) = freq->old;
		पूर्ण

		अगर (!global_l_p_j_ref) अणु
			global_l_p_j_ref = loops_per_jअगरfy;
			global_l_p_j_ref_freq = freq->old;
		पूर्ण
	पूर्ण

	अगर ((val == CPUFREQ_PRECHANGE  && freq->old < freq->new) ||
	    (val == CPUFREQ_POSTCHANGE && freq->old > freq->new)) अणु
		loops_per_jअगरfy = cpufreq_scale(global_l_p_j_ref,
						global_l_p_j_ref_freq,
						freq->new);

		lpj = cpufreq_scale(per_cpu(l_p_j_ref, first),
				    per_cpu(l_p_j_ref_freq, first), freq->new);
		क्रम_each_cpu(cpu, cpus)
			per_cpu(cpu_data, cpu).loops_per_jअगरfy = lpj;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block cpufreq_notअगरier = अणु
	.notअगरier_call  = cpufreq_callback,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_cpufreq_notअगरier(व्योम)
अणु
	वापस cpufreq_रेजिस्टर_notअगरier(&cpufreq_notअगरier,
						CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण
core_initcall(रेजिस्टर_cpufreq_notअगरier);

#पूर्ण_अगर

अटल व्योम उठाओ_nmi(cpumask_t *mask)
अणु
	__ipi_send_mask(ipi_desc[IPI_CPU_BACKTRACE], mask);
पूर्ण

व्योम arch_trigger_cpumask_backtrace(स्थिर cpumask_t *mask, bool exclude_self)
अणु
	nmi_trigger_cpumask_backtrace(mask, exclude_self, उठाओ_nmi);
पूर्ण
