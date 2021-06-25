<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SMP initialisation and IPI support
 * Based on arch/arm/kernel/smp.c
 *
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/arm_sdei.h>
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
#समावेश <linux/smp.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/arm-gic-v3.h>
#समावेश <linux/percpu.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/completion.h>
#समावेश <linux/of.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/kexec.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/atomic.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/virt.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/ipi.h>

DEFINE_PER_CPU_READ_MOSTLY(पूर्णांक, cpu_number);
EXPORT_PER_CPU_SYMBOL(cpu_number);

/*
 * as from 2.5, kernels no दीर्घer have an init_tasks काष्ठाure
 * so we need some other way of telling a new secondary core
 * where to place its SVC stack
 */
काष्ठा secondary_data secondary_data;
/* Number of CPUs which aren't online, but looping in kernel text. */
अटल पूर्णांक cpus_stuck_in_kernel;

क्रमागत ipi_msg_type अणु
	IPI_RESCHEDULE,
	IPI_CALL_FUNC,
	IPI_CPU_STOP,
	IPI_CPU_CRASH_STOP,
	IPI_TIMER,
	IPI_IRQ_WORK,
	IPI_WAKEUP,
	NR_IPI
पूर्ण;

अटल पूर्णांक ipi_irq_base __पढ़ो_mostly;
अटल पूर्णांक nr_ipi __पढ़ो_mostly = NR_IPI;
अटल काष्ठा irq_desc *ipi_desc[NR_IPI] __पढ़ो_mostly;

अटल व्योम ipi_setup(पूर्णांक cpu);

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम ipi_tearकरोwn(पूर्णांक cpu);
अटल पूर्णांक op_cpu_समाप्त(अचिन्हित पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत पूर्णांक op_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर


/*
 * Boot a secondary CPU, and assign it the specअगरied idle task.
 * This also gives us the initial stack to use क्रम this CPU.
 */
अटल पूर्णांक boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	स्थिर काष्ठा cpu_operations *ops = get_cpu_ops(cpu);

	अगर (ops->cpu_boot)
		वापस ops->cpu_boot(cpu);

	वापस -EOPNOTSUPP;
पूर्ण

अटल DECLARE_COMPLETION(cpu_running);

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret;
	दीर्घ status;

	/*
	 * We need to tell the secondary core where to find its stack and the
	 * page tables.
	 */
	secondary_data.task = idle;
	secondary_data.stack = task_stack_page(idle) + THREAD_SIZE;
	update_cpu_boot_status(CPU_MMU_OFF);
	__flush_dcache_area(&secondary_data, माप(secondary_data));

	/* Now bring the CPU पूर्णांकo our world */
	ret = boot_secondary(cpu, idle);
	अगर (ret) अणु
		pr_err("CPU%u: failed to boot: %d\n", cpu, ret);
		वापस ret;
	पूर्ण

	/*
	 * CPU was successfully started, रुको क्रम it to come online or
	 * समय out.
	 */
	रुको_क्रम_completion_समयout(&cpu_running,
				    msecs_to_jअगरfies(5000));
	अगर (cpu_online(cpu))
		वापस 0;

	pr_crit("CPU%u: failed to come online\n", cpu);
	secondary_data.task = शून्य;
	secondary_data.stack = शून्य;
	__flush_dcache_area(&secondary_data, माप(secondary_data));
	status = READ_ONCE(secondary_data.status);
	अगर (status == CPU_MMU_OFF)
		status = READ_ONCE(__early_cpu_boot_status);

	चयन (status & CPU_BOOT_STATUS_MASK) अणु
	शेष:
		pr_err("CPU%u: failed in unknown state : 0x%lx\n",
		       cpu, status);
		cpus_stuck_in_kernel++;
		अवरोध;
	हाल CPU_KILL_ME:
		अगर (!op_cpu_समाप्त(cpu)) अणु
			pr_crit("CPU%u: died during early boot\n", cpu);
			अवरोध;
		पूर्ण
		pr_crit("CPU%u: may not have shut down cleanly\n", cpu);
		fallthrough;
	हाल CPU_STUCK_IN_KERNEL:
		pr_crit("CPU%u: is stuck in kernel\n", cpu);
		अगर (status & CPU_STUCK_REASON_52_BIT_VA)
			pr_crit("CPU%u: does not support 52-bit VAs\n", cpu);
		अगर (status & CPU_STUCK_REASON_NO_GRAN) अणु
			pr_crit("CPU%u: does not support %luK granule\n",
				cpu, PAGE_SIZE / SZ_1K);
		पूर्ण
		cpus_stuck_in_kernel++;
		अवरोध;
	हाल CPU_PANIC_KERNEL:
		panic("CPU%u detected unsupported configuration\n", cpu);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल व्योम init_gic_priority_masking(व्योम)
अणु
	u32 cpuflags;

	अगर (WARN_ON(!gic_enable_sre()))
		वापस;

	cpuflags = पढ़ो_sysreg(daअगर);

	WARN_ON(!(cpuflags & PSR_I_BIT));
	WARN_ON(!(cpuflags & PSR_F_BIT));

	gic_ग_लिखो_pmr(GIC_PRIO_IRQON | GIC_PRIO_PSR_I_SET);
पूर्ण

/*
 * This is the secondary CPU boot entry.  We're using this CPUs
 * idle thपढ़ो stack, but a set of temporary page tables.
 */
यंत्रlinkage notrace व्योम secondary_start_kernel(व्योम)
अणु
	u64 mpidr = पढ़ो_cpuid_mpidr() & MPIDR_HWID_BITMASK;
	काष्ठा mm_काष्ठा *mm = &init_mm;
	स्थिर काष्ठा cpu_operations *ops;
	अचिन्हित पूर्णांक cpu;

	cpu = task_cpu(current);
	set_my_cpu_offset(per_cpu_offset(cpu));

	/*
	 * All kernel thपढ़ोs share the same mm context; grab a
	 * reference and चयन to it.
	 */
	mmgrab(mm);
	current->active_mm = mm;

	/*
	 * TTBR0 is only used क्रम the identity mapping at this stage. Make it
	 * poपूर्णांक to zero page to aव्योम speculatively fetching new entries.
	 */
	cpu_uninstall_idmap();

	अगर (प्रणाली_uses_irq_prio_masking())
		init_gic_priority_masking();

	rcu_cpu_starting(cpu);
	preempt_disable();
	trace_hardirqs_off();

	/*
	 * If the प्रणाली has established the capabilities, make sure
	 * this CPU ticks all of those. If it करोesn't, the CPU will
	 * fail to come online.
	 */
	check_local_cpu_capabilities();

	ops = get_cpu_ops(cpu);
	अगर (ops->cpu_postboot)
		ops->cpu_postboot();

	/*
	 * Log the CPU info beक्रमe it is marked online and might get पढ़ो.
	 */
	cpuinfo_store_cpu();

	/*
	 * Enable GIC and समयrs.
	 */
	notअगरy_cpu_starting(cpu);

	ipi_setup(cpu);

	store_cpu_topology(cpu);
	numa_add_cpu(cpu);

	/*
	 * OK, now it's safe to let the boot CPU जारी.  Wait क्रम
	 * the CPU migration code to notice that the CPU is online
	 * beक्रमe we जारी.
	 */
	pr_info("CPU%u: Booted secondary processor 0x%010lx [0x%08x]\n",
					 cpu, (अचिन्हित दीर्घ)mpidr,
					 पढ़ो_cpuid_id());
	update_cpu_boot_status(CPU_BOOT_SUCCESS);
	set_cpu_online(cpu, true);
	complete(&cpu_running);

	local_daअगर_restore(DAIF_PROCCTX);

	/*
	 * OK, it's off to the idle thपढ़ो क्रम us
	 */
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक op_cpu_disable(अचिन्हित पूर्णांक cpu)
अणु
	स्थिर काष्ठा cpu_operations *ops = get_cpu_ops(cpu);

	/*
	 * If we करोn't have a cpu_die method, पात beक्रमe we reach the poपूर्णांक
	 * of no वापस. CPU0 may not have an cpu_ops, so test क्रम it.
	 */
	अगर (!ops || !ops->cpu_die)
		वापस -EOPNOTSUPP;

	/*
	 * We may need to पात a hot unplug क्रम some other mechanism-specअगरic
	 * reason.
	 */
	अगर (ops->cpu_disable)
		वापस ops->cpu_disable(cpu);

	वापस 0;
पूर्ण

/*
 * __cpu_disable runs on the processor to be shutकरोwn.
 */
पूर्णांक __cpu_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक ret;

	ret = op_cpu_disable(cpu);
	अगर (ret)
		वापस ret;

	हटाओ_cpu_topology(cpu);
	numa_हटाओ_cpu(cpu);

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

	वापस 0;
पूर्ण

अटल पूर्णांक op_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	स्थिर काष्ठा cpu_operations *ops = get_cpu_ops(cpu);

	/*
	 * If we have no means of synchronising with the dying CPU, then assume
	 * that it is really dead. We can only रुको क्रम an arbitrary length of
	 * समय and hope that it's dead, so let's skip the रुको and just hope.
	 */
	अगर (!ops->cpu_समाप्त)
		वापस 0;

	वापस ops->cpu_समाप्त(cpu);
पूर्ण

/*
 * called on the thपढ़ो which is asking क्रम a CPU to be shutकरोwn -
 * रुकोs until shutकरोwn has completed, or it is समयd out.
 */
व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक err;

	अगर (!cpu_रुको_death(cpu, 5)) अणु
		pr_crit("CPU%u: cpu didn't die\n", cpu);
		वापस;
	पूर्ण
	pr_notice("CPU%u: shutdown\n", cpu);

	/*
	 * Now that the dying CPU is beyond the poपूर्णांक of no वापस w.r.t.
	 * in-kernel synchronisation, try to get the firwmare to help us to
	 * verअगरy that it has really left the kernel beक्रमe we consider
	 * clobbering anything it might still be using.
	 */
	err = op_cpu_समाप्त(cpu);
	अगर (err)
		pr_warn("CPU%d may not have shut down cleanly: %d\n", cpu, err);
पूर्ण

/*
 * Called from the idle thपढ़ो क्रम the CPU which has been shutकरोwn.
 *
 */
व्योम cpu_die(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	स्थिर काष्ठा cpu_operations *ops = get_cpu_ops(cpu);

	idle_task_निकास();

	local_daअगर_mask();

	/* Tell __cpu_die() that this CPU is now safe to dispose of */
	(व्योम)cpu_report_death();

	/*
	 * Actually shutकरोwn the CPU. This must never fail. The specअगरic hotplug
	 * mechanism must perक्रमm all required cache मुख्यtenance to ensure that
	 * no dirty lines are lost in the process of shutting करोwn the CPU.
	 */
	ops->cpu_die(cpu);

	BUG();
पूर्ण
#पूर्ण_अगर

अटल व्योम __cpu_try_die(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	स्थिर काष्ठा cpu_operations *ops = get_cpu_ops(cpu);

	अगर (ops && ops->cpu_die)
		ops->cpu_die(cpu);
#पूर्ण_अगर
पूर्ण

/*
 * Kill the calling secondary CPU, early in bringup beक्रमe it is turned
 * online.
 */
व्योम cpu_die_early(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	pr_crit("CPU%d: will not boot\n", cpu);

	/* Mark this CPU असलent */
	set_cpu_present(cpu, 0);
	rcu_report_dead(cpu);

	अगर (IS_ENABLED(CONFIG_HOTPLUG_CPU)) अणु
		update_cpu_boot_status(CPU_KILL_ME);
		__cpu_try_die(cpu);
	पूर्ण

	update_cpu_boot_status(CPU_STUCK_IN_KERNEL);

	cpu_park_loop();
पूर्ण

अटल व्योम __init hyp_mode_check(व्योम)
अणु
	अगर (is_hyp_mode_available())
		pr_info("CPU: All CPU(s) started at EL2\n");
	अन्यथा अगर (is_hyp_mode_mismatched())
		WARN_TAINT(1, TAINT_CPU_OUT_OF_SPEC,
			   "CPU: CPUs started in inconsistent modes");
	अन्यथा
		pr_info("CPU: All CPU(s) started at EL1\n");
	अगर (IS_ENABLED(CONFIG_KVM) && !is_kernel_in_hyp_mode()) अणु
		kvm_compute_layout();
		kvm_apply_hyp_relocations();
	पूर्ण
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
	pr_info("SMP: Total of %d processors activated.\n", num_online_cpus());
	setup_cpu_features();
	hyp_mode_check();
	apply_alternatives_all();
	mark_linear_text_alias_ro();
पूर्ण

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
	set_my_cpu_offset(per_cpu_offset(smp_processor_id()));
	cpuinfo_store_boot_cpu();

	/*
	 * We now know enough about the boot CPU to apply the
	 * alternatives that cannot रुको until पूर्णांकerrupt handling
	 * and/or scheduling is enabled.
	 */
	apply_boot_alternatives();

	/* Conditionally चयन to GIC PMR क्रम पूर्णांकerrupt masking */
	अगर (प्रणाली_uses_irq_prio_masking())
		init_gic_priority_masking();

	kasan_init_hw_tags();
पूर्ण

अटल u64 __init of_get_cpu_mpidr(काष्ठा device_node *dn)
अणु
	स्थिर __be32 *cell;
	u64 hwid;

	/*
	 * A cpu node with missing "reg" property is
	 * considered invalid to build a cpu_logical_map
	 * entry.
	 */
	cell = of_get_property(dn, "reg", शून्य);
	अगर (!cell) अणु
		pr_err("%pOF: missing reg property\n", dn);
		वापस INVALID_HWID;
	पूर्ण

	hwid = of_पढ़ो_number(cell, of_n_addr_cells(dn));
	/*
	 * Non affinity bits must be set to 0 in the DT
	 */
	अगर (hwid & ~MPIDR_HWID_BITMASK) अणु
		pr_err("%pOF: invalid reg property\n", dn);
		वापस INVALID_HWID;
	पूर्ण
	वापस hwid;
पूर्ण

/*
 * Duplicate MPIDRs are a recipe क्रम disaster. Scan all initialized
 * entries and check क्रम duplicates. If any is found just ignore the
 * cpu. cpu_logical_map was initialized to INVALID_HWID to aव्योम
 * matching valid MPIDR values.
 */
अटल bool __init is_mpidr_duplicate(अचिन्हित पूर्णांक cpu, u64 hwid)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; (i < cpu) && (i < NR_CPUS); i++)
		अगर (cpu_logical_map(i) == hwid)
			वापस true;
	वापस false;
पूर्ण

/*
 * Initialize cpu operations क्रम a logical cpu and
 * set it in the possible mask on success
 */
अटल पूर्णांक __init smp_cpu_setup(पूर्णांक cpu)
अणु
	स्थिर काष्ठा cpu_operations *ops;

	अगर (init_cpu_ops(cpu))
		वापस -ENODEV;

	ops = get_cpu_ops(cpu);
	अगर (ops->cpu_init(cpu))
		वापस -ENODEV;

	set_cpu_possible(cpu, true);

	वापस 0;
पूर्ण

अटल bool bootcpu_valid __initdata;
अटल अचिन्हित पूर्णांक cpu_count = 1;

#अगर_घोषित CONFIG_ACPI
अटल काष्ठा acpi_madt_generic_पूर्णांकerrupt cpu_madt_gicc[NR_CPUS];

काष्ठा acpi_madt_generic_पूर्णांकerrupt *acpi_cpu_get_madt_gicc(पूर्णांक cpu)
अणु
	वापस &cpu_madt_gicc[cpu];
पूर्ण

/*
 * acpi_map_gic_cpu_पूर्णांकerface - parse processor MADT entry
 *
 * Carry out sanity checks on MADT processor entry and initialize
 * cpu_logical_map on success
 */
अटल व्योम __init
acpi_map_gic_cpu_पूर्णांकerface(काष्ठा acpi_madt_generic_पूर्णांकerrupt *processor)
अणु
	u64 hwid = processor->arm_mpidr;

	अगर (!(processor->flags & ACPI_MADT_ENABLED)) अणु
		pr_debug("skipping disabled CPU entry with 0x%llx MPIDR\n", hwid);
		वापस;
	पूर्ण

	अगर (hwid & ~MPIDR_HWID_BITMASK || hwid == INVALID_HWID) अणु
		pr_err("skipping CPU entry with invalid MPIDR 0x%llx\n", hwid);
		वापस;
	पूर्ण

	अगर (is_mpidr_duplicate(cpu_count, hwid)) अणु
		pr_err("duplicate CPU MPIDR 0x%llx in MADT\n", hwid);
		वापस;
	पूर्ण

	/* Check अगर GICC काष्ठाure of boot CPU is available in the MADT */
	अगर (cpu_logical_map(0) == hwid) अणु
		अगर (bootcpu_valid) अणु
			pr_err("duplicate boot CPU MPIDR: 0x%llx in MADT\n",
			       hwid);
			वापस;
		पूर्ण
		bootcpu_valid = true;
		cpu_madt_gicc[0] = *processor;
		वापस;
	पूर्ण

	अगर (cpu_count >= NR_CPUS)
		वापस;

	/* map the logical cpu id to cpu MPIDR */
	set_cpu_logical_map(cpu_count, hwid);

	cpu_madt_gicc[cpu_count] = *processor;

	/*
	 * Set-up the ACPI parking protocol cpu entries
	 * जबतक initializing the cpu_logical_map to
	 * aव्योम parsing MADT entries multiple बार क्रम
	 * nothing (ie a valid cpu_logical_map entry should
	 * contain a valid parking protocol data set to
	 * initialize the cpu अगर the parking protocol is
	 * the only available enable method).
	 */
	acpi_set_mailbox_entry(cpu_count, processor);

	cpu_count++;
पूर्ण

अटल पूर्णांक __init
acpi_parse_gic_cpu_पूर्णांकerface(जोड़ acpi_subtable_headers *header,
			     स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_पूर्णांकerrupt *processor;

	processor = (काष्ठा acpi_madt_generic_पूर्णांकerrupt *)header;
	अगर (BAD_MADT_GICC_ENTRY(processor, end))
		वापस -EINVAL;

	acpi_table_prपूर्णांक_madt_entry(&header->common);

	acpi_map_gic_cpu_पूर्णांकerface(processor);

	वापस 0;
पूर्ण

अटल व्योम __init acpi_parse_and_init_cpus(व्योम)
अणु
	पूर्णांक i;

	/*
	 * करो a walk of MADT to determine how many CPUs
	 * we have including disabled CPUs, and get inक्रमmation
	 * we need क्रम SMP init.
	 */
	acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_INTERRUPT,
				      acpi_parse_gic_cpu_पूर्णांकerface, 0);

	/*
	 * In ACPI, SMP and CPU NUMA inक्रमmation is provided in separate
	 * अटल tables, namely the MADT and the SRAT.
	 *
	 * Thus, it is simpler to first create the cpu logical map through
	 * an MADT walk and then map the logical cpus to their node ids
	 * as separate steps.
	 */
	acpi_map_cpus_to_nodes();

	क्रम (i = 0; i < nr_cpu_ids; i++)
		early_map_cpu_to_node(i, acpi_numa_get_nid(i));
पूर्ण
#अन्यथा
#घोषणा acpi_parse_and_init_cpus(...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Enumerate the possible CPU set from the device tree and build the
 * cpu logical map array containing MPIDR values related to logical
 * cpus. Assumes that cpu_logical_map(0) has alपढ़ोy been initialized.
 */
अटल व्योम __init of_parse_and_init_cpus(व्योम)
अणु
	काष्ठा device_node *dn;

	क्रम_each_of_cpu_node(dn) अणु
		u64 hwid = of_get_cpu_mpidr(dn);

		अगर (hwid == INVALID_HWID)
			जाओ next;

		अगर (is_mpidr_duplicate(cpu_count, hwid)) अणु
			pr_err("%pOF: duplicate cpu reg properties in the DT\n",
				dn);
			जाओ next;
		पूर्ण

		/*
		 * The numbering scheme requires that the boot CPU
		 * must be asचिन्हित logical id 0. Record it so that
		 * the logical map built from DT is validated and can
		 * be used.
		 */
		अगर (hwid == cpu_logical_map(0)) अणु
			अगर (bootcpu_valid) अणु
				pr_err("%pOF: duplicate boot cpu reg property in DT\n",
					dn);
				जाओ next;
			पूर्ण

			bootcpu_valid = true;
			early_map_cpu_to_node(0, of_node_to_nid(dn));

			/*
			 * cpu_logical_map has alपढ़ोy been
			 * initialized and the boot cpu करोesn't need
			 * the enable-method so जारी without
			 * incrementing cpu.
			 */
			जारी;
		पूर्ण

		अगर (cpu_count >= NR_CPUS)
			जाओ next;

		pr_debug("cpu logical map 0x%llx\n", hwid);
		set_cpu_logical_map(cpu_count, hwid);

		early_map_cpu_to_node(cpu_count, of_node_to_nid(dn));
next:
		cpu_count++;
	पूर्ण
पूर्ण

/*
 * Enumerate the possible CPU set from the device tree or ACPI and build the
 * cpu logical map array containing MPIDR values related to logical
 * cpus. Assumes that cpu_logical_map(0) has alपढ़ोy been initialized.
 */
व्योम __init smp_init_cpus(व्योम)
अणु
	पूर्णांक i;

	अगर (acpi_disabled)
		of_parse_and_init_cpus();
	अन्यथा
		acpi_parse_and_init_cpus();

	अगर (cpu_count > nr_cpu_ids)
		pr_warn("Number of cores (%d) exceeds configured maximum of %u - clipping\n",
			cpu_count, nr_cpu_ids);

	अगर (!bootcpu_valid) अणु
		pr_err("missing boot CPU MPIDR, not enabling secondaries\n");
		वापस;
	पूर्ण

	/*
	 * We need to set the cpu_logical_map entries beक्रमe enabling
	 * the cpus so that cpu processor description entries (DT cpu nodes
	 * and ACPI MADT entries) can be retrieved by matching the cpu hwid
	 * with entries in cpu_logical_map जबतक initializing the cpus.
	 * If the cpu set-up fails, invalidate the cpu_logical_map entry.
	 */
	क्रम (i = 1; i < nr_cpu_ids; i++) अणु
		अगर (cpu_logical_map(i) != INVALID_HWID) अणु
			अगर (smp_cpu_setup(i))
				set_cpu_logical_map(i, INVALID_HWID);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	स्थिर काष्ठा cpu_operations *ops;
	पूर्णांक err;
	अचिन्हित पूर्णांक cpu;
	अचिन्हित पूर्णांक this_cpu;

	init_cpu_topology();

	this_cpu = smp_processor_id();
	store_cpu_topology(this_cpu);
	numa_store_cpu_info(this_cpu);
	numa_add_cpu(this_cpu);

	/*
	 * If UP is mandated by "nosmp" (which implies "maxcpus=0"), करोn't set
	 * secondary CPUs present.
	 */
	अगर (max_cpus == 0)
		वापस;

	/*
	 * Initialise the present map (which describes the set of CPUs
	 * actually populated at the present समय) and release the
	 * secondaries from the bootloader.
	 */
	क्रम_each_possible_cpu(cpu) अणु

		per_cpu(cpu_number, cpu) = cpu;

		अगर (cpu == smp_processor_id())
			जारी;

		ops = get_cpu_ops(cpu);
		अगर (!ops)
			जारी;

		err = ops->cpu_prepare(cpu);
		अगर (err)
			जारी;

		set_cpu_present(cpu, true);
		numa_store_cpu_info(cpu);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *ipi_types[NR_IPI] __tracepoपूर्णांक_string = अणु
	[IPI_RESCHEDULE]	= "Rescheduling interrupts",
	[IPI_CALL_FUNC]		= "Function call interrupts",
	[IPI_CPU_STOP]		= "CPU stop interrupts",
	[IPI_CPU_CRASH_STOP]	= "CPU stop (for crash dump) interrupts",
	[IPI_TIMER]		= "Timer broadcast interrupts",
	[IPI_IRQ_WORK]		= "IRQ work interrupts",
	[IPI_WAKEUP]		= "CPU wake-up interrupts",
पूर्ण;

अटल व्योम smp_cross_call(स्थिर काष्ठा cpumask *target, अचिन्हित पूर्णांक ipinr);

अचिन्हित दीर्घ irq_err_count;

पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	अचिन्हित पूर्णांक cpu, i;

	क्रम (i = 0; i < NR_IPI; i++) अणु
		seq_म_लिखो(p, "%*s%u:%s", prec - 1, "IPI", i,
			   prec >= 4 ? " " : "");
		क्रम_each_online_cpu(cpu)
			seq_म_लिखो(p, "%10u ", irq_desc_kstat_cpu(ipi_desc[i], cpu));
		seq_म_लिखो(p, "      %s\n", ipi_types[i]);
	पूर्ण

	seq_म_लिखो(p, "%*s: %10lu\n", prec, "Err", irq_err_count);
	वापस 0;
पूर्ण

व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	smp_cross_call(mask, IPI_CALL_FUNC);
पूर्ण

व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	smp_cross_call(cpumask_of(cpu), IPI_CALL_FUNC);
पूर्ण

#अगर_घोषित CONFIG_ARM64_ACPI_PARKING_PROTOCOL
व्योम arch_send_wakeup_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	smp_cross_call(mask, IPI_WAKEUP);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IRQ_WORK
व्योम arch_irq_work_उठाओ(व्योम)
अणु
	smp_cross_call(cpumask_of(smp_processor_id()), IPI_IRQ_WORK);
पूर्ण
#पूर्ण_अगर

अटल व्योम local_cpu_stop(व्योम)
अणु
	set_cpu_online(smp_processor_id(), false);

	local_daअगर_mask();
	sdei_mask_local_cpu();
	cpu_park_loop();
पूर्ण

/*
 * We need to implement panic_smp_self_stop() क्रम parallel panic() calls, so
 * that cpu_online_mask माला_लो correctly updated and smp_send_stop() can skip
 * CPUs that have alपढ़ोy stopped themselves.
 */
व्योम panic_smp_self_stop(व्योम)
अणु
	local_cpu_stop();
पूर्ण

#अगर_घोषित CONFIG_KEXEC_CORE
अटल atomic_t रुकोing_क्रम_crash_ipi = ATOMIC_INIT(0);
#पूर्ण_अगर

अटल व्योम ipi_cpu_crash_stop(अचिन्हित पूर्णांक cpu, काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_KEXEC_CORE
	crash_save_cpu(regs, cpu);

	atomic_dec(&रुकोing_क्रम_crash_ipi);

	local_irq_disable();
	sdei_mask_local_cpu();

	अगर (IS_ENABLED(CONFIG_HOTPLUG_CPU))
		__cpu_try_die(cpu);

	/* just in हाल */
	cpu_park_loop();
#पूर्ण_अगर
पूर्ण

/*
 * Main handler क्रम पूर्णांकer-processor पूर्णांकerrupts
 */
अटल व्योम करो_handle_IPI(पूर्णांक ipinr)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर ((अचिन्हित)ipinr < NR_IPI)
		trace_ipi_entry_rcuidle(ipi_types[ipinr]);

	चयन (ipinr) अणु
	हाल IPI_RESCHEDULE:
		scheduler_ipi();
		अवरोध;

	हाल IPI_CALL_FUNC:
		generic_smp_call_function_पूर्णांकerrupt();
		अवरोध;

	हाल IPI_CPU_STOP:
		local_cpu_stop();
		अवरोध;

	हाल IPI_CPU_CRASH_STOP:
		अगर (IS_ENABLED(CONFIG_KEXEC_CORE)) अणु
			ipi_cpu_crash_stop(cpu, get_irq_regs());

			unreachable();
		पूर्ण
		अवरोध;

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
	हाल IPI_TIMER:
		tick_receive_broadcast();
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IRQ_WORK
	हाल IPI_IRQ_WORK:
		irq_work_run();
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_ACPI_PARKING_PROTOCOL
	हाल IPI_WAKEUP:
		WARN_ONCE(!acpi_parking_protocol_valid(cpu),
			  "CPU%u: Wake-up IPI outside the ACPI parking protocol\n",
			  cpu);
		अवरोध;
#पूर्ण_अगर

	शेष:
		pr_crit("CPU%u: Unknown IPI message 0x%x\n", cpu, ipinr);
		अवरोध;
	पूर्ण

	अगर ((अचिन्हित)ipinr < NR_IPI)
		trace_ipi_निकास_rcuidle(ipi_types[ipinr]);
पूर्ण

अटल irqवापस_t ipi_handler(पूर्णांक irq, व्योम *data)
अणु
	करो_handle_IPI(irq - ipi_irq_base);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम smp_cross_call(स्थिर काष्ठा cpumask *target, अचिन्हित पूर्णांक ipinr)
अणु
	trace_ipi_उठाओ(target, ipi_types[ipinr]);
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

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम ipi_tearकरोwn(पूर्णांक cpu)
अणु
	पूर्णांक i;

	अगर (WARN_ON_ONCE(!ipi_irq_base))
		वापस;

	क्रम (i = 0; i < nr_ipi; i++)
		disable_percpu_irq(ipi_irq_base + i);
पूर्ण
#पूर्ण_अगर

व्योम __init set_smp_ipi_range(पूर्णांक ipi_base, पूर्णांक n)
अणु
	पूर्णांक i;

	WARN_ON(n < NR_IPI);
	nr_ipi = min(n, NR_IPI);

	क्रम (i = 0; i < nr_ipi; i++) अणु
		पूर्णांक err;

		err = request_percpu_irq(ipi_base + i, ipi_handler,
					 "IPI", &cpu_number);
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

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
व्योम tick_broadcast(स्थिर काष्ठा cpumask *mask)
अणु
	smp_cross_call(mask, IPI_TIMER);
पूर्ण
#पूर्ण_अगर

/*
 * The number of CPUs online, not counting this CPU (which may not be
 * fully online and so not counted in num_online_cpus()).
 */
अटल अंतरभूत अचिन्हित पूर्णांक num_other_online_cpus(व्योम)
अणु
	अचिन्हित पूर्णांक this_cpu_online = cpu_online(smp_processor_id());

	वापस num_online_cpus() - this_cpu_online;
पूर्ण

व्योम smp_send_stop(व्योम)
अणु
	अचिन्हित दीर्घ समयout;

	अगर (num_other_online_cpus()) अणु
		cpumask_t mask;

		cpumask_copy(&mask, cpu_online_mask);
		cpumask_clear_cpu(smp_processor_id(), &mask);

		अगर (प्रणाली_state <= SYSTEM_RUNNING)
			pr_crit("SMP: stopping secondary CPUs\n");
		smp_cross_call(&mask, IPI_CPU_STOP);
	पूर्ण

	/* Wait up to one second क्रम other CPUs to stop */
	समयout = USEC_PER_SEC;
	जबतक (num_other_online_cpus() && समयout--)
		udelay(1);

	अगर (num_other_online_cpus())
		pr_warn("SMP: failed to stop secondary CPUs %*pbl\n",
			cpumask_pr_args(cpu_online_mask));

	sdei_mask_local_cpu();
पूर्ण

#अगर_घोषित CONFIG_KEXEC_CORE
व्योम crash_smp_send_stop(व्योम)
अणु
	अटल पूर्णांक cpus_stopped;
	cpumask_t mask;
	अचिन्हित दीर्घ समयout;

	/*
	 * This function can be called twice in panic path, but obviously
	 * we execute this only once.
	 */
	अगर (cpus_stopped)
		वापस;

	cpus_stopped = 1;

	/*
	 * If this cpu is the only one alive at this poपूर्णांक in समय, online or
	 * not, there are no stop messages to be sent around, so just back out.
	 */
	अगर (num_other_online_cpus() == 0) अणु
		sdei_mask_local_cpu();
		वापस;
	पूर्ण

	cpumask_copy(&mask, cpu_online_mask);
	cpumask_clear_cpu(smp_processor_id(), &mask);

	atomic_set(&रुकोing_क्रम_crash_ipi, num_other_online_cpus());

	pr_crit("SMP: stopping secondary CPUs\n");
	smp_cross_call(&mask, IPI_CPU_CRASH_STOP);

	/* Wait up to one second क्रम other CPUs to stop */
	समयout = USEC_PER_SEC;
	जबतक ((atomic_पढ़ो(&रुकोing_क्रम_crash_ipi) > 0) && समयout--)
		udelay(1);

	अगर (atomic_पढ़ो(&रुकोing_क्रम_crash_ipi) > 0)
		pr_warn("SMP: failed to stop secondary CPUs %*pbl\n",
			cpumask_pr_args(&mask));

	sdei_mask_local_cpu();
पूर्ण

bool smp_crash_stop_failed(व्योम)
अणु
	वापस (atomic_पढ़ो(&रुकोing_क्रम_crash_ipi) > 0);
पूर्ण
#पूर्ण_अगर

/*
 * not supported here
 */
पूर्णांक setup_profiling_समयr(अचिन्हित पूर्णांक multiplier)
अणु
	वापस -EINVAL;
पूर्ण

अटल bool have_cpu_die(व्योम)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	पूर्णांक any_cpu = raw_smp_processor_id();
	स्थिर काष्ठा cpu_operations *ops = get_cpu_ops(any_cpu);

	अगर (ops && ops->cpu_die)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

bool cpus_are_stuck_in_kernel(व्योम)
अणु
	bool smp_spin_tables = (num_possible_cpus() > 1 && !have_cpu_die());

	वापस !!cpus_stuck_in_kernel || smp_spin_tables;
पूर्ण
