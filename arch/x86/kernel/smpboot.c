<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /*
 *	x86 SMP booting functions
 *
 *	(c) 1995 Alan Cox, Building #3 <alan@lxorguk.ukuu.org.uk>
 *	(c) 1998, 1999, 2000, 2009 Ingo Molnar <mingo@redhat.com>
 *	Copyright 2001 Andi Kleen, SuSE Lअसल.
 *
 *	Much of the core SMP work is based on previous work by Thomas Radke, to
 *	whom a great many thanks are extended.
 *
 *	Thanks to Intel क्रम making available several dअगरferent Pentium,
 *	Pentium Pro and Pentium-II/Xeon MP machines.
 *	Original development of Linux SMP code supported by Caldera.
 *
 *	Fixes
 *		Felix Koop	:	NR_CPUS used properly
 *		Jose Renau	:	Handle single CPU हाल.
 *		Alan Cox	:	By repeated request 8) - Total BogoMIPS report.
 *		Greg Wright	:	Fix क्रम kernel stacks panic.
 *		Erich Boleyn	:	MP v1.4 and additional changes.
 *	Matthias Sattler	:	Changes क्रम 2.1 kernel map.
 *	Michel Lespinasse	:	Changes क्रम 2.1 kernel map.
 *	Michael Chastain	:	Change trampoline.S to gnu as.
 *		Alan Cox	:	Dumb bug: 'B' step PPro's are fine
 *		Ingo Molnar	:	Added APIC समयrs, based on code
 *					from Jose Renau
 *		Ingo Molnar	:	various cleanups and reग_लिखोs
 *		Tigran Aivazian	:	fixed "0.00 in /proc/uptime on SMP" bug.
 *	Maciej W. Rozycki	:	Bits क्रम genuine 82489DX APICs
 *	Andi Kleen		:	Changed क्रम SMP boot पूर्णांकo दीर्घ mode.
 *		Martin J. Bligh	: 	Added support क्रम multi-quad प्रणालीs
 *		Dave Jones	:	Report invalid combinations of Athlon CPUs.
 *		Rusty Russell	:	Hacked पूर्णांकo shape क्रम new "hotplug" boot process.
 *      Andi Kleen              :       Converted to new state machine.
 *	Ashok Raj		: 	CPU hotplug support
 *	Glauber Costa		:	i386 and x86_64 पूर्णांकegration
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/topology.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/percpu.h>
#समावेश <linux/memblock.h>
#समावेश <linux/err.h>
#समावेश <linux/nmi.h>
#समावेश <linux/tboot.h>
#समावेश <linux/gfp.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/numa.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/overflow.h>
#समावेश <linux/syscore_ops.h>

#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/mरुको.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/uv/uv.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/misc.h>
#समावेश <यंत्र/qspinlock.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/spec-ctrl.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/stackprotector.h>

#अगर_घोषित CONFIG_ACPI_CPPC_LIB
#समावेश <acpi/cppc_acpi.h>
#पूर्ण_अगर

/* representing HT siblings of each logical CPU */
DEFINE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_sibling_map);
EXPORT_PER_CPU_SYMBOL(cpu_sibling_map);

/* representing HT and core siblings of each logical CPU */
DEFINE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_core_map);
EXPORT_PER_CPU_SYMBOL(cpu_core_map);

/* representing HT, core, and die siblings of each logical CPU */
DEFINE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_die_map);
EXPORT_PER_CPU_SYMBOL(cpu_die_map);

DEFINE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_llc_shared_map);

/* Per CPU bogomips and other parameters */
DEFINE_PER_CPU_READ_MOSTLY(काष्ठा cpuinfo_x86, cpu_info);
EXPORT_PER_CPU_SYMBOL(cpu_info);

/* Logical package management. We might want to allocate that dynamically */
अचिन्हित पूर्णांक __max_logical_packages __पढ़ो_mostly;
EXPORT_SYMBOL(__max_logical_packages);
अटल अचिन्हित पूर्णांक logical_packages __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक logical_die __पढ़ो_mostly;

/* Maximum number of SMT thपढ़ोs on any online core */
पूर्णांक __पढ़ो_mostly __max_smt_thपढ़ोs = 1;

/* Flag to indicate अगर a complete sched करोमुख्य rebuild is required */
bool x86_topology_update;

पूर्णांक arch_update_cpu_topology(व्योम)
अणु
	पूर्णांक retval = x86_topology_update;

	x86_topology_update = false;
	वापस retval;
पूर्ण

अटल अंतरभूत व्योम smpboot_setup_warm_reset_vector(अचिन्हित दीर्घ start_eip)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc_lock, flags);
	CMOS_WRITE(0xa, 0xf);
	spin_unlock_irqrestore(&rtc_lock, flags);
	*((अस्थिर अचिन्हित लघु *)phys_to_virt(TRAMPOLINE_PHYS_HIGH)) =
							start_eip >> 4;
	*((अस्थिर अचिन्हित लघु *)phys_to_virt(TRAMPOLINE_PHYS_LOW)) =
							start_eip & 0xf;
पूर्ण

अटल अंतरभूत व्योम smpboot_restore_warm_reset_vector(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Paranoid:  Set warm reset code and vector here back
	 * to शेष values.
	 */
	spin_lock_irqsave(&rtc_lock, flags);
	CMOS_WRITE(0, 0xf);
	spin_unlock_irqrestore(&rtc_lock, flags);

	*((अस्थिर u32 *)phys_to_virt(TRAMPOLINE_PHYS_LOW)) = 0;
पूर्ण

अटल व्योम init_freq_invariance(bool secondary, bool cppc_पढ़ोy);

/*
 * Report back to the Boot Processor during boot समय or to the caller processor
 * during CPU online.
 */
अटल व्योम smp_callin(व्योम)
अणु
	पूर्णांक cpuid;

	/*
	 * If waken up by an INIT in an 82489DX configuration
	 * cpu_callout_mask guarantees we करोn't get here beक्रमe
	 * an INIT_deनिश्चित IPI reaches our local APIC, so it is
	 * now safe to touch our local APIC.
	 */
	cpuid = smp_processor_id();

	/*
	 * the boot CPU has finished the init stage and is spinning
	 * on callin_map until we finish. We are मुक्त to set up this
	 * CPU, first the APIC. (this is probably redundant on most
	 * boards)
	 */
	apic_ap_setup();

	/*
	 * Save our processor parameters. Note: this inक्रमmation
	 * is needed क्रम घड़ी calibration.
	 */
	smp_store_cpu_info(cpuid);

	/*
	 * The topology inक्रमmation must be up to date beक्रमe
	 * calibrate_delay() and notअगरy_cpu_starting().
	 */
	set_cpu_sibling_map(raw_smp_processor_id());

	init_freq_invariance(true, false);

	/*
	 * Get our bogomips.
	 * Update loops_per_jअगरfy in cpu_data. Previous call to
	 * smp_store_cpu_info() stored a value that is बंद but not as
	 * accurate as the value just calculated.
	 */
	calibrate_delay();
	cpu_data(cpuid).loops_per_jअगरfy = loops_per_jअगरfy;
	pr_debug("Stack at about %p\n", &cpuid);

	wmb();

	notअगरy_cpu_starting(cpuid);

	/*
	 * Allow the master to जारी.
	 */
	cpumask_set_cpu(cpuid, cpu_callin_mask);
पूर्ण

अटल पूर्णांक cpu0_logical_apicid;
अटल पूर्णांक enable_start_cpu0;
/*
 * Activate a secondary processor.
 */
अटल व्योम notrace start_secondary(व्योम *unused)
अणु
	/*
	 * Don't put *anything* except direct CPU state initialization
	 * beक्रमe cpu_init(), SMP booting is too fragile that we want to
	 * limit the things करोne here to the most necessary things.
	 */
	cr4_init();

#अगर_घोषित CONFIG_X86_32
	/* चयन away from the initial page table */
	load_cr3(swapper_pg_dir);
	__flush_tlb_all();
#पूर्ण_अगर
	cpu_init_exception_handling();
	cpu_init();
	rcu_cpu_starting(raw_smp_processor_id());
	x86_cpuinit.early_percpu_घड़ी_init();
	preempt_disable();
	smp_callin();

	enable_start_cpu0 = 0;

	/* otherwise gcc will move up smp_processor_id beक्रमe the cpu_init */
	barrier();
	/*
	 * Check TSC synchronization with the boot CPU:
	 */
	check_tsc_sync_target();

	speculative_store_bypass_ht_init();

	/*
	 * Lock vector_lock, set CPU online and bring the vector
	 * allocator online. Online must be set with vector_lock held
	 * to prevent a concurrent irq setup/tearकरोwn from seeing a
	 * half valid vector space.
	 */
	lock_vector_lock();
	set_cpu_online(smp_processor_id(), true);
	lapic_online();
	unlock_vector_lock();
	cpu_set_state_online(smp_processor_id());
	x86_platक्रमm.nmi_init();

	/* enable local पूर्णांकerrupts */
	local_irq_enable();

	x86_cpuinit.setup_percpu_घड़ीev();

	wmb();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण

/**
 * topology_is_primary_thपढ़ो - Check whether CPU is the primary SMT thपढ़ो
 * @cpu:	CPU to check
 */
bool topology_is_primary_thपढ़ो(अचिन्हित पूर्णांक cpu)
अणु
	वापस apic_id_is_primary_thपढ़ो(per_cpu(x86_cpu_to_apicid, cpu));
पूर्ण

/**
 * topology_smt_supported - Check whether SMT is supported by the CPUs
 */
bool topology_smt_supported(व्योम)
अणु
	वापस smp_num_siblings > 1;
पूर्ण

/**
 * topology_phys_to_logical_pkg - Map a physical package id to a logical
 *
 * Returns logical package id or -1 अगर not found
 */
पूर्णांक topology_phys_to_logical_pkg(अचिन्हित पूर्णांक phys_pkg)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

		अगर (c->initialized && c->phys_proc_id == phys_pkg)
			वापस c->logical_proc_id;
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL(topology_phys_to_logical_pkg);
/**
 * topology_phys_to_logical_die - Map a physical die id to logical
 *
 * Returns logical die id or -1 अगर not found
 */
पूर्णांक topology_phys_to_logical_die(अचिन्हित पूर्णांक die_id, अचिन्हित पूर्णांक cur_cpu)
अणु
	पूर्णांक cpu;
	पूर्णांक proc_id = cpu_data(cur_cpu).phys_proc_id;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

		अगर (c->initialized && c->cpu_die_id == die_id &&
		    c->phys_proc_id == proc_id)
			वापस c->logical_die_id;
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL(topology_phys_to_logical_die);

/**
 * topology_update_package_map - Update the physical to logical package map
 * @pkg:	The physical package id as retrieved via CPUID
 * @cpu:	The cpu क्रम which this is updated
 */
पूर्णांक topology_update_package_map(अचिन्हित पूर्णांक pkg, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक new;

	/* Alपढ़ोy available somewhere? */
	new = topology_phys_to_logical_pkg(pkg);
	अगर (new >= 0)
		जाओ found;

	new = logical_packages++;
	अगर (new != pkg) अणु
		pr_info("CPU %u Converting physical %u to logical package %u\n",
			cpu, pkg, new);
	पूर्ण
found:
	cpu_data(cpu).logical_proc_id = new;
	वापस 0;
पूर्ण
/**
 * topology_update_die_map - Update the physical to logical die map
 * @die:	The die id as retrieved via CPUID
 * @cpu:	The cpu क्रम which this is updated
 */
पूर्णांक topology_update_die_map(अचिन्हित पूर्णांक die, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक new;

	/* Alपढ़ोy available somewhere? */
	new = topology_phys_to_logical_die(die, cpu);
	अगर (new >= 0)
		जाओ found;

	new = logical_die++;
	अगर (new != die) अणु
		pr_info("CPU %u Converting physical %u to logical die %u\n",
			cpu, die, new);
	पूर्ण
found:
	cpu_data(cpu).logical_die_id = new;
	वापस 0;
पूर्ण

व्योम __init smp_store_boot_cpu_info(व्योम)
अणु
	पूर्णांक id = 0; /* CPU 0 */
	काष्ठा cpuinfo_x86 *c = &cpu_data(id);

	*c = boot_cpu_data;
	c->cpu_index = id;
	topology_update_package_map(c->phys_proc_id, id);
	topology_update_die_map(c->cpu_die_id, id);
	c->initialized = true;
पूर्ण

/*
 * The bootstrap kernel entry code has set these up. Save them क्रम
 * a given CPU
 */
व्योम smp_store_cpu_info(पूर्णांक id)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(id);

	/* Copy boot_cpu_data only on the first bringup */
	अगर (!c->initialized)
		*c = boot_cpu_data;
	c->cpu_index = id;
	/*
	 * During boot समय, CPU0 has this setup alपढ़ोy. Save the info when
	 * bringing up AP or offlined CPU0.
	 */
	identअगरy_secondary_cpu(c);
	c->initialized = true;
पूर्ण

अटल bool
topology_same_node(काष्ठा cpuinfo_x86 *c, काष्ठा cpuinfo_x86 *o)
अणु
	पूर्णांक cpu1 = c->cpu_index, cpu2 = o->cpu_index;

	वापस (cpu_to_node(cpu1) == cpu_to_node(cpu2));
पूर्ण

अटल bool
topology_sane(काष्ठा cpuinfo_x86 *c, काष्ठा cpuinfo_x86 *o, स्थिर अक्षर *name)
अणु
	पूर्णांक cpu1 = c->cpu_index, cpu2 = o->cpu_index;

	वापस !WARN_ONCE(!topology_same_node(c, o),
		"sched: CPU #%d's %s-sibling CPU #%d is not on the same node! "
		"[node: %d != %d]. Ignoring dependency.\n",
		cpu1, name, cpu2, cpu_to_node(cpu1), cpu_to_node(cpu2));
पूर्ण

#घोषणा link_mask(mfunc, c1, c2)					\
करो अणु									\
	cpumask_set_cpu((c1), mfunc(c2));				\
	cpumask_set_cpu((c2), mfunc(c1));				\
पूर्ण जबतक (0)

अटल bool match_smt(काष्ठा cpuinfo_x86 *c, काष्ठा cpuinfo_x86 *o)
अणु
	अगर (boot_cpu_has(X86_FEATURE_TOPOEXT)) अणु
		पूर्णांक cpu1 = c->cpu_index, cpu2 = o->cpu_index;

		अगर (c->phys_proc_id == o->phys_proc_id &&
		    c->cpu_die_id == o->cpu_die_id &&
		    per_cpu(cpu_llc_id, cpu1) == per_cpu(cpu_llc_id, cpu2)) अणु
			अगर (c->cpu_core_id == o->cpu_core_id)
				वापस topology_sane(c, o, "smt");

			अगर ((c->cu_id != 0xff) &&
			    (o->cu_id != 0xff) &&
			    (c->cu_id == o->cu_id))
				वापस topology_sane(c, o, "smt");
		पूर्ण

	पूर्ण अन्यथा अगर (c->phys_proc_id == o->phys_proc_id &&
		   c->cpu_die_id == o->cpu_die_id &&
		   c->cpu_core_id == o->cpu_core_id) अणु
		वापस topology_sane(c, o, "smt");
	पूर्ण

	वापस false;
पूर्ण

अटल bool match_die(काष्ठा cpuinfo_x86 *c, काष्ठा cpuinfo_x86 *o)
अणु
	अगर (c->phys_proc_id == o->phys_proc_id &&
	    c->cpu_die_id == o->cpu_die_id)
		वापस true;
	वापस false;
पूर्ण

/*
 * Unlike the other levels, we करो not enक्रमce keeping a
 * multicore group inside a NUMA node.  If this happens, we will
 * discard the MC level of the topology later.
 */
अटल bool match_pkg(काष्ठा cpuinfo_x86 *c, काष्ठा cpuinfo_x86 *o)
अणु
	अगर (c->phys_proc_id == o->phys_proc_id)
		वापस true;
	वापस false;
पूर्ण

/*
 * Define पूर्णांकel_cod_cpu[] क्रम Intel COD (Cluster-on-Die) CPUs.
 *
 * Any Intel CPU that has multiple nodes per package and करोes not
 * match पूर्णांकel_cod_cpu[] has the SNC (Sub-NUMA Cluster) topology.
 *
 * When in SNC mode, these CPUs क्रमागतerate an LLC that is shared
 * by multiple NUMA nodes. The LLC is shared क्रम off-package data
 * access but निजी to the NUMA node (half of the package) क्रम
 * on-package access. CPUID (the source of the inक्रमmation about
 * the LLC) can only क्रमागतerate the cache as shared or unshared,
 * but not this particular configuration.
 */

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_cod_cpu[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_X, 0),	/* COD */
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_X, 0),	/* COD */
	X86_MATCH_INTEL_FAM6_MODEL(ANY, 1),		/* SNC */
	अणुपूर्ण
पूर्ण;

अटल bool match_llc(काष्ठा cpuinfo_x86 *c, काष्ठा cpuinfo_x86 *o)
अणु
	स्थिर काष्ठा x86_cpu_id *id = x86_match_cpu(पूर्णांकel_cod_cpu);
	पूर्णांक cpu1 = c->cpu_index, cpu2 = o->cpu_index;
	bool पूर्णांकel_snc = id && id->driver_data;

	/* Do not match अगर we करो not have a valid APICID क्रम cpu: */
	अगर (per_cpu(cpu_llc_id, cpu1) == BAD_APICID)
		वापस false;

	/* Do not match अगर LLC id करोes not match: */
	अगर (per_cpu(cpu_llc_id, cpu1) != per_cpu(cpu_llc_id, cpu2))
		वापस false;

	/*
	 * Allow the SNC topology without warning. Return of false
	 * means 'c' does not share the LLC of 'o'. This will be
	 * reflected to userspace.
	 */
	अगर (match_pkg(c, o) && !topology_same_node(c, o) && पूर्णांकel_snc)
		वापस false;

	वापस topology_sane(c, o, "llc");
पूर्ण


#अगर defined(CONFIG_SCHED_SMT) || defined(CONFIG_SCHED_MC)
अटल अंतरभूत पूर्णांक x86_sched_iपंचांगt_flags(व्योम)
अणु
	वापस sysctl_sched_iपंचांगt_enabled ? SD_ASYM_PACKING : 0;
पूर्ण

#अगर_घोषित CONFIG_SCHED_MC
अटल पूर्णांक x86_core_flags(व्योम)
अणु
	वापस cpu_core_flags() | x86_sched_iपंचांगt_flags();
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_SMT
अटल पूर्णांक x86_smt_flags(व्योम)
अणु
	वापस cpu_smt_flags() | x86_sched_iपंचांगt_flags();
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

अटल काष्ठा sched_करोमुख्य_topology_level x86_numa_in_package_topology[] = अणु
#अगर_घोषित CONFIG_SCHED_SMT
	अणु cpu_smt_mask, x86_smt_flags, SD_INIT_NAME(SMT) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_MC
	अणु cpu_coregroup_mask, x86_core_flags, SD_INIT_NAME(MC) पूर्ण,
#पूर्ण_अगर
	अणु शून्य, पूर्ण,
पूर्ण;

अटल काष्ठा sched_करोमुख्य_topology_level x86_topology[] = अणु
#अगर_घोषित CONFIG_SCHED_SMT
	अणु cpu_smt_mask, x86_smt_flags, SD_INIT_NAME(SMT) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_MC
	अणु cpu_coregroup_mask, x86_core_flags, SD_INIT_NAME(MC) पूर्ण,
#पूर्ण_अगर
	अणु cpu_cpu_mask, SD_INIT_NAME(DIE) पूर्ण,
	अणु शून्य, पूर्ण,
पूर्ण;

/*
 * Set अगर a package/die has multiple NUMA nodes inside.
 * AMD Magny-Cours, Intel Cluster-on-Die, and Intel
 * Sub-NUMA Clustering have this.
 */
अटल bool x86_has_numa_in_package;

व्योम set_cpu_sibling_map(पूर्णांक cpu)
अणु
	bool has_smt = smp_num_siblings > 1;
	bool has_mp = has_smt || boot_cpu_data.x86_max_cores > 1;
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);
	काष्ठा cpuinfo_x86 *o;
	पूर्णांक i, thपढ़ोs;

	cpumask_set_cpu(cpu, cpu_sibling_setup_mask);

	अगर (!has_mp) अणु
		cpumask_set_cpu(cpu, topology_sibling_cpumask(cpu));
		cpumask_set_cpu(cpu, cpu_llc_shared_mask(cpu));
		cpumask_set_cpu(cpu, topology_core_cpumask(cpu));
		cpumask_set_cpu(cpu, topology_die_cpumask(cpu));
		c->booted_cores = 1;
		वापस;
	पूर्ण

	क्रम_each_cpu(i, cpu_sibling_setup_mask) अणु
		o = &cpu_data(i);

		अगर (match_pkg(c, o) && !topology_same_node(c, o))
			x86_has_numa_in_package = true;

		अगर ((i == cpu) || (has_smt && match_smt(c, o)))
			link_mask(topology_sibling_cpumask, cpu, i);

		अगर ((i == cpu) || (has_mp && match_llc(c, o)))
			link_mask(cpu_llc_shared_mask, cpu, i);

		अगर ((i == cpu) || (has_mp && match_die(c, o)))
			link_mask(topology_die_cpumask, cpu, i);
	पूर्ण

	thपढ़ोs = cpumask_weight(topology_sibling_cpumask(cpu));
	अगर (thपढ़ोs > __max_smt_thपढ़ोs)
		__max_smt_thपढ़ोs = thपढ़ोs;

	/*
	 * This needs a separate iteration over the cpus because we rely on all
	 * topology_sibling_cpumask links to be set-up.
	 */
	क्रम_each_cpu(i, cpu_sibling_setup_mask) अणु
		o = &cpu_data(i);

		अगर ((i == cpu) || (has_mp && match_pkg(c, o))) अणु
			link_mask(topology_core_cpumask, cpu, i);

			/*
			 *  Does this new cpu bringup a new core?
			 */
			अगर (thपढ़ोs == 1) अणु
				/*
				 * क्रम each core in package, increment
				 * the booted_cores क्रम this new cpu
				 */
				अगर (cpumask_first(
				    topology_sibling_cpumask(i)) == i)
					c->booted_cores++;
				/*
				 * increment the core count क्रम all
				 * the other cpus in this package
				 */
				अगर (i != cpu)
					cpu_data(i).booted_cores++;
			पूर्ण अन्यथा अगर (i != cpu && !c->booted_cores)
				c->booted_cores = cpu_data(i).booted_cores;
		पूर्ण
	पूर्ण
पूर्ण

/* maps the cpu to the sched करोमुख्य representing multi-core */
स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu)
अणु
	वापस cpu_llc_shared_mask(cpu);
पूर्ण

अटल व्योम impress_मित्रs(व्योम)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ bogosum = 0;
	/*
	 * Allow the user to impress मित्रs.
	 */
	pr_debug("Before bogomips\n");
	क्रम_each_possible_cpu(cpu)
		अगर (cpumask_test_cpu(cpu, cpu_callout_mask))
			bogosum += cpu_data(cpu).loops_per_jअगरfy;
	pr_info("Total of %d processors activated (%lu.%02lu BogoMIPS)\n",
		num_online_cpus(),
		bogosum/(500000/HZ),
		(bogosum/(5000/HZ))%100);

	pr_debug("Before bogocount - setting activated=1\n");
पूर्ण

व्योम __inquire_remote_apic(पूर्णांक apicid)
अणु
	अचिन्हित i, regs[] = अणु APIC_ID >> 4, APIC_LVR >> 4, APIC_SPIV >> 4 पूर्ण;
	स्थिर अक्षर * स्थिर names[] = अणु "ID", "VERSION", "SPIV" पूर्ण;
	पूर्णांक समयout;
	u32 status;

	pr_info("Inquiring remote APIC 0x%x...\n", apicid);

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		pr_info("... APIC 0x%x %s: ", apicid, names[i]);

		/*
		 * Wait क्रम idle.
		 */
		status = safe_apic_रुको_icr_idle();
		अगर (status)
			pr_cont("a previous APIC delivery may have failed\n");

		apic_icr_ग_लिखो(APIC_DM_REMRD | regs[i], apicid);

		समयout = 0;
		करो अणु
			udelay(100);
			status = apic_पढ़ो(APIC_ICR) & APIC_ICR_RR_MASK;
		पूर्ण जबतक (status == APIC_ICR_RR_INPROG && समयout++ < 1000);

		चयन (status) अणु
		हाल APIC_ICR_RR_VALID:
			status = apic_पढ़ो(APIC_RRR);
			pr_cont("%08x\n", status);
			अवरोध;
		शेष:
			pr_cont("failed\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * The Multiprocessor Specअगरication 1.4 (1997) example code suggests
 * that there should be a 10ms delay between the BSP निश्चितing INIT
 * and de-निश्चितing INIT, when starting a remote processor.
 * But that slows boot and resume on modern processors, which include
 * many cores and करोn't require that delay.
 *
 * Cmdline "init_cpu_udelay=" is available to over-ride this delay.
 * Modern processor families are quirked to हटाओ the delay entirely.
 */
#घोषणा UDELAY_10MS_DEFAULT 10000

अटल अचिन्हित पूर्णांक init_udelay = अच_पूर्णांक_उच्च;

अटल पूर्णांक __init cpu_init_udelay(अक्षर *str)
अणु
	get_option(&str, &init_udelay);

	वापस 0;
पूर्ण
early_param("cpu_init_udelay", cpu_init_udelay);

अटल व्योम __init smp_quirk_init_udelay(व्योम)
अणु
	/* अगर cmdline changed it from शेष, leave it alone */
	अगर (init_udelay != अच_पूर्णांक_उच्च)
		वापस;

	/* अगर modern processor, use no delay */
	अगर (((boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL) && (boot_cpu_data.x86 == 6)) ||
	    ((boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON) && (boot_cpu_data.x86 >= 0x18)) ||
	    ((boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD) && (boot_cpu_data.x86 >= 0xF))) अणु
		init_udelay = 0;
		वापस;
	पूर्ण
	/* अन्यथा, use legacy delay */
	init_udelay = UDELAY_10MS_DEFAULT;
पूर्ण

/*
 * Poke the other CPU in the eye via NMI to wake it up. Remember that the normal
 * INIT, INIT, STARTUP sequence will reset the chip hard क्रम us, and this
 * won't ... remember to clear करोwn the APIC, etc later.
 */
पूर्णांक
wakeup_secondary_cpu_via_nmi(पूर्णांक apicid, अचिन्हित दीर्घ start_eip)
अणु
	u32 dm = apic->dest_mode_logical ? APIC_DEST_LOGICAL : APIC_DEST_PHYSICAL;
	अचिन्हित दीर्घ send_status, accept_status = 0;
	पूर्णांक maxlvt;

	/* Target chip */
	/* Boot on the stack */
	/* Kick the second */
	apic_icr_ग_लिखो(APIC_DM_NMI | dm, apicid);

	pr_debug("Waiting for send to finish...\n");
	send_status = safe_apic_रुको_icr_idle();

	/*
	 * Give the other CPU some समय to accept the IPI.
	 */
	udelay(200);
	अगर (APIC_INTEGRATED(boot_cpu_apic_version)) अणु
		maxlvt = lapic_get_maxlvt();
		अगर (maxlvt > 3)			/* Due to the Pentium erratum 3AP.  */
			apic_ग_लिखो(APIC_ESR, 0);
		accept_status = (apic_पढ़ो(APIC_ESR) & 0xEF);
	पूर्ण
	pr_debug("NMI sent\n");

	अगर (send_status)
		pr_err("APIC never delivered???\n");
	अगर (accept_status)
		pr_err("APIC delivery error (%lx)\n", accept_status);

	वापस (send_status | accept_status);
पूर्ण

अटल पूर्णांक
wakeup_secondary_cpu_via_init(पूर्णांक phys_apicid, अचिन्हित दीर्घ start_eip)
अणु
	अचिन्हित दीर्घ send_status = 0, accept_status = 0;
	पूर्णांक maxlvt, num_starts, j;

	maxlvt = lapic_get_maxlvt();

	/*
	 * Be paranoid about clearing APIC errors.
	 */
	अगर (APIC_INTEGRATED(boot_cpu_apic_version)) अणु
		अगर (maxlvt > 3)		/* Due to the Pentium erratum 3AP.  */
			apic_ग_लिखो(APIC_ESR, 0);
		apic_पढ़ो(APIC_ESR);
	पूर्ण

	pr_debug("Asserting INIT\n");

	/*
	 * Turn INIT on target chip
	 */
	/*
	 * Send IPI
	 */
	apic_icr_ग_लिखो(APIC_INT_LEVELTRIG | APIC_INT_ASSERT | APIC_DM_INIT,
		       phys_apicid);

	pr_debug("Waiting for send to finish...\n");
	send_status = safe_apic_रुको_icr_idle();

	udelay(init_udelay);

	pr_debug("Deasserting INIT\n");

	/* Target chip */
	/* Send IPI */
	apic_icr_ग_लिखो(APIC_INT_LEVELTRIG | APIC_DM_INIT, phys_apicid);

	pr_debug("Waiting for send to finish...\n");
	send_status = safe_apic_रुको_icr_idle();

	mb();

	/*
	 * Should we send STARTUP IPIs ?
	 *
	 * Determine this based on the APIC version.
	 * If we करोn't have an integrated APIC, don't send the STARTUP IPIs.
	 */
	अगर (APIC_INTEGRATED(boot_cpu_apic_version))
		num_starts = 2;
	अन्यथा
		num_starts = 0;

	/*
	 * Run STARTUP IPI loop.
	 */
	pr_debug("#startup loops: %d\n", num_starts);

	क्रम (j = 1; j <= num_starts; j++) अणु
		pr_debug("Sending STARTUP #%d\n", j);
		अगर (maxlvt > 3)		/* Due to the Pentium erratum 3AP.  */
			apic_ग_लिखो(APIC_ESR, 0);
		apic_पढ़ो(APIC_ESR);
		pr_debug("After apic_write\n");

		/*
		 * STARTUP IPI
		 */

		/* Target chip */
		/* Boot on the stack */
		/* Kick the second */
		apic_icr_ग_लिखो(APIC_DM_STARTUP | (start_eip >> 12),
			       phys_apicid);

		/*
		 * Give the other CPU some समय to accept the IPI.
		 */
		अगर (init_udelay == 0)
			udelay(10);
		अन्यथा
			udelay(300);

		pr_debug("Startup point 1\n");

		pr_debug("Waiting for send to finish...\n");
		send_status = safe_apic_रुको_icr_idle();

		/*
		 * Give the other CPU some समय to accept the IPI.
		 */
		अगर (init_udelay == 0)
			udelay(10);
		अन्यथा
			udelay(200);

		अगर (maxlvt > 3)		/* Due to the Pentium erratum 3AP.  */
			apic_ग_लिखो(APIC_ESR, 0);
		accept_status = (apic_पढ़ो(APIC_ESR) & 0xEF);
		अगर (send_status || accept_status)
			अवरोध;
	पूर्ण
	pr_debug("After Startup\n");

	अगर (send_status)
		pr_err("APIC never delivered???\n");
	अगर (accept_status)
		pr_err("APIC delivery error (%lx)\n", accept_status);

	वापस (send_status | accept_status);
पूर्ण

/* reduce the number of lines prपूर्णांकed when booting a large cpu count प्रणाली */
अटल व्योम announce_cpu(पूर्णांक cpu, पूर्णांक apicid)
अणु
	अटल पूर्णांक current_node = NUMA_NO_NODE;
	पूर्णांक node = early_cpu_to_node(cpu);
	अटल पूर्णांक width, node_width;

	अगर (!width)
		width = num_digits(num_possible_cpus()) + 1; /* + '#' sign */

	अगर (!node_width)
		node_width = num_digits(num_possible_nodes()) + 1; /* + '#' */

	अगर (cpu == 1)
		prपूर्णांकk(KERN_INFO "x86: Booting SMP configuration:\n");

	अगर (प्रणाली_state < SYSTEM_RUNNING) अणु
		अगर (node != current_node) अणु
			अगर (current_node > (-1))
				pr_cont("\n");
			current_node = node;

			prपूर्णांकk(KERN_INFO ".... node %*s#%d, CPUs:  ",
			       node_width - num_digits(node), " ", node);
		पूर्ण

		/* Add padding क्रम the BSP */
		अगर (cpu == 1)
			pr_cont("%*s", width + 1, " ");

		pr_cont("%*s#%d", width - num_digits(cpu), " ", cpu);

	पूर्ण अन्यथा
		pr_info("Booting Node %d Processor %d APIC 0x%x\n",
			node, cpu, apicid);
पूर्ण

अटल पूर्णांक wakeup_cpu0_nmi(अचिन्हित पूर्णांक cmd, काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu;

	cpu = smp_processor_id();
	अगर (cpu == 0 && !cpu_online(cpu) && enable_start_cpu0)
		वापस NMI_HANDLED;

	वापस NMI_DONE;
पूर्ण

/*
 * Wake up AP by INIT, INIT, STARTUP sequence.
 *
 * Instead of रुकोing क्रम STARTUP after INITs, BSP will execute the BIOS
 * boot-strap code which is not a desired behavior क्रम waking up BSP. To
 * व्योम the boot-strap code, wake up CPU0 by NMI instead.
 *
 * This works to wake up soft offlined CPU0 only. If CPU0 is hard offlined
 * (i.e. physically hot हटाओd and then hot added), NMI won't wake it up.
 * We'll change this code in the future to wake up hard offlined CPU0 अगर
 * real platक्रमm and request are available.
 */
अटल पूर्णांक
wakeup_cpu_via_init_nmi(पूर्णांक cpu, अचिन्हित दीर्घ start_ip, पूर्णांक apicid,
	       पूर्णांक *cpu0_nmi_रेजिस्टरed)
अणु
	पूर्णांक id;
	पूर्णांक boot_error;

	preempt_disable();

	/*
	 * Wake up AP by INIT, INIT, STARTUP sequence.
	 */
	अगर (cpu) अणु
		boot_error = wakeup_secondary_cpu_via_init(apicid, start_ip);
		जाओ out;
	पूर्ण

	/*
	 * Wake up BSP by nmi.
	 *
	 * Register a NMI handler to help wake up CPU0.
	 */
	boot_error = रेजिस्टर_nmi_handler(NMI_LOCAL,
					  wakeup_cpu0_nmi, 0, "wake_cpu0");

	अगर (!boot_error) अणु
		enable_start_cpu0 = 1;
		*cpu0_nmi_रेजिस्टरed = 1;
		id = apic->dest_mode_logical ? cpu0_logical_apicid : apicid;
		boot_error = wakeup_secondary_cpu_via_nmi(id, start_ip);
	पूर्ण

out:
	preempt_enable();

	वापस boot_error;
पूर्ण

पूर्णांक common_cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret;

	/* Just in हाल we booted with a single CPU. */
	alternatives_enable_smp();

	per_cpu(current_task, cpu) = idle;
	cpu_init_stack_canary(cpu, idle);

	/* Initialize the पूर्णांकerrupt stack(s) */
	ret = irq_init_percpu_irqstack(cpu);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_X86_32
	/* Stack क्रम startup_32 can be just as क्रम start_secondary onwards */
	per_cpu(cpu_current_top_of_stack, cpu) = task_top_of_stack(idle);
#अन्यथा
	initial_gs = per_cpu_offset(cpu);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * NOTE - on most प्रणालीs this is a PHYSICAL apic ID, but on multiquad
 * (ie clustered apic addressing mode), this is a LOGICAL apic ID.
 * Returns zero अगर CPU booted OK, अन्यथा error code from
 * ->wakeup_secondary_cpu.
 */
अटल पूर्णांक करो_boot_cpu(पूर्णांक apicid, पूर्णांक cpu, काष्ठा task_काष्ठा *idle,
		       पूर्णांक *cpu0_nmi_रेजिस्टरed)
अणु
	/* start_ip had better be page-aligned! */
	अचिन्हित दीर्घ start_ip = real_mode_header->trampoline_start;

	अचिन्हित दीर्घ boot_error = 0;
	अचिन्हित दीर्घ समयout;

	idle->thपढ़ो.sp = (अचिन्हित दीर्घ)task_pt_regs(idle);
	early_gdt_descr.address = (अचिन्हित दीर्घ)get_cpu_gdt_rw(cpu);
	initial_code = (अचिन्हित दीर्घ)start_secondary;
	initial_stack  = idle->thपढ़ो.sp;

	/* Enable the espfix hack क्रम this CPU */
	init_espfix_ap(cpu);

	/* So we see what's up */
	announce_cpu(cpu, apicid);

	/*
	 * This grunge runs the startup process क्रम
	 * the targeted processor.
	 */

	अगर (x86_platक्रमm.legacy.warm_reset) अणु

		pr_debug("Setting warm reset code and vector.\n");

		smpboot_setup_warm_reset_vector(start_ip);
		/*
		 * Be paranoid about clearing APIC errors.
		*/
		अगर (APIC_INTEGRATED(boot_cpu_apic_version)) अणु
			apic_ग_लिखो(APIC_ESR, 0);
			apic_पढ़ो(APIC_ESR);
		पूर्ण
	पूर्ण

	/*
	 * AP might रुको on cpu_callout_mask in cpu_init() with
	 * cpu_initialized_mask set अगर previous attempt to online
	 * it समयd-out. Clear cpu_initialized_mask so that after
	 * INIT/SIPI it could start with a clean state.
	 */
	cpumask_clear_cpu(cpu, cpu_initialized_mask);
	smp_mb();

	/*
	 * Wake up a CPU in dअगरference हालs:
	 * - Use the method in the APIC driver अगर it's defined
	 * Otherwise,
	 * - Use an INIT boot APIC message क्रम APs or NMI क्रम BSP.
	 */
	अगर (apic->wakeup_secondary_cpu)
		boot_error = apic->wakeup_secondary_cpu(apicid, start_ip);
	अन्यथा
		boot_error = wakeup_cpu_via_init_nmi(cpu, start_ip, apicid,
						     cpu0_nmi_रेजिस्टरed);

	अगर (!boot_error) अणु
		/*
		 * Wait 10s total क्रम first sign of lअगरe from AP
		 */
		boot_error = -1;
		समयout = jअगरfies + 10*HZ;
		जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
			अगर (cpumask_test_cpu(cpu, cpu_initialized_mask)) अणु
				/*
				 * Tell AP to proceed with initialization
				 */
				cpumask_set_cpu(cpu, cpu_callout_mask);
				boot_error = 0;
				अवरोध;
			पूर्ण
			schedule();
		पूर्ण
	पूर्ण

	अगर (!boot_error) अणु
		/*
		 * Wait till AP completes initial initialization
		 */
		जबतक (!cpumask_test_cpu(cpu, cpu_callin_mask)) अणु
			/*
			 * Allow other tasks to run जबतक we रुको क्रम the
			 * AP to come online. This also gives a chance
			 * क्रम the MTRR work(triggered by the AP coming online)
			 * to be completed in the stop machine context.
			 */
			schedule();
		पूर्ण
	पूर्ण

	अगर (x86_platक्रमm.legacy.warm_reset) अणु
		/*
		 * Cleanup possible dangling ends...
		 */
		smpboot_restore_warm_reset_vector();
	पूर्ण

	वापस boot_error;
पूर्ण

पूर्णांक native_cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	पूर्णांक apicid = apic->cpu_present_to_apicid(cpu);
	पूर्णांक cpu0_nmi_रेजिस्टरed = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक err, ret = 0;

	lockdep_निश्चित_irqs_enabled();

	pr_debug("++++++++++++++++++++=_---CPU UP  %u\n", cpu);

	अगर (apicid == BAD_APICID ||
	    !physid_isset(apicid, phys_cpu_present_map) ||
	    !apic->apic_id_valid(apicid)) अणु
		pr_err("%s: bad cpu %d\n", __func__, cpu);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Alपढ़ोy booted CPU?
	 */
	अगर (cpumask_test_cpu(cpu, cpu_callin_mask)) अणु
		pr_debug("do_boot_cpu %d Already started\n", cpu);
		वापस -ENOSYS;
	पूर्ण

	/*
	 * Save current MTRR state in हाल it was changed since early boot
	 * (e.g. by the ACPI SMI) to initialize new CPUs with MTRRs in sync:
	 */
	mtrr_save_state();

	/* x86 CPUs take themselves offline, so delayed offline is OK. */
	err = cpu_check_up_prepare(cpu);
	अगर (err && err != -EBUSY)
		वापस err;

	/* the FPU context is blank, nobody can own it */
	per_cpu(fpu_fpregs_owner_ctx, cpu) = शून्य;

	err = common_cpu_up(cpu, tidle);
	अगर (err)
		वापस err;

	err = करो_boot_cpu(apicid, cpu, tidle, &cpu0_nmi_रेजिस्टरed);
	अगर (err) अणु
		pr_err("do_boot_cpu failed(%d) to wakeup CPU#%u\n", err, cpu);
		ret = -EIO;
		जाओ unreg_nmi;
	पूर्ण

	/*
	 * Check TSC synchronization with the AP (keep irqs disabled
	 * जबतक करोing so):
	 */
	local_irq_save(flags);
	check_tsc_sync_source(cpu);
	local_irq_restore(flags);

	जबतक (!cpu_online(cpu)) अणु
		cpu_relax();
		touch_nmi_watchकरोg();
	पूर्ण

unreg_nmi:
	/*
	 * Clean up the nmi handler. Do this after the callin and callout sync
	 * to aव्योम impact of possible दीर्घ unरेजिस्टर समय.
	 */
	अगर (cpu0_nmi_रेजिस्टरed)
		unरेजिस्टर_nmi_handler(NMI_LOCAL, "wake_cpu0");

	वापस ret;
पूर्ण

/**
 * arch_disable_smp_support() - disables SMP support क्रम x86 at runसमय
 */
व्योम arch_disable_smp_support(व्योम)
अणु
	disable_ioapic_support();
पूर्ण

/*
 * Fall back to non SMP mode after errors.
 *
 * RED-PEN audit/test this more. I bet there is more state messed up here.
 */
अटल __init व्योम disable_smp(व्योम)
अणु
	pr_info("SMP disabled\n");

	disable_ioapic_support();

	init_cpu_present(cpumask_of(0));
	init_cpu_possible(cpumask_of(0));

	अगर (smp_found_config)
		physid_set_mask_of_physid(boot_cpu_physical_apicid, &phys_cpu_present_map);
	अन्यथा
		physid_set_mask_of_physid(0, &phys_cpu_present_map);
	cpumask_set_cpu(0, topology_sibling_cpumask(0));
	cpumask_set_cpu(0, topology_core_cpumask(0));
	cpumask_set_cpu(0, topology_die_cpumask(0));
पूर्ण

/*
 * Various sanity checks.
 */
अटल व्योम __init smp_sanity_check(व्योम)
अणु
	preempt_disable();

#अगर !defined(CONFIG_X86_BIGSMP) && defined(CONFIG_X86_32)
	अगर (def_to_bigsmp && nr_cpu_ids > 8) अणु
		अचिन्हित पूर्णांक cpu;
		अचिन्हित nr;

		pr_warn("More than 8 CPUs detected - skipping them\n"
			"Use CONFIG_X86_BIGSMP\n");

		nr = 0;
		क्रम_each_present_cpu(cpu) अणु
			अगर (nr >= 8)
				set_cpu_present(cpu, false);
			nr++;
		पूर्ण

		nr = 0;
		क्रम_each_possible_cpu(cpu) अणु
			अगर (nr >= 8)
				set_cpu_possible(cpu, false);
			nr++;
		पूर्ण

		nr_cpu_ids = 8;
	पूर्ण
#पूर्ण_अगर

	अगर (!physid_isset(hard_smp_processor_id(), phys_cpu_present_map)) अणु
		pr_warn("weird, boot CPU (#%d) not listed by the BIOS\n",
			hard_smp_processor_id());

		physid_set(hard_smp_processor_id(), phys_cpu_present_map);
	पूर्ण

	/*
	 * Should not be necessary because the MP table should list the boot
	 * CPU too, but we करो it क्रम the sake of robustness anyway.
	 */
	अगर (!apic->check_phys_apicid_present(boot_cpu_physical_apicid)) अणु
		pr_notice("weird, boot CPU (#%d) not listed by the BIOS\n",
			  boot_cpu_physical_apicid);
		physid_set(hard_smp_processor_id(), phys_cpu_present_map);
	पूर्ण
	preempt_enable();
पूर्ण

अटल व्योम __init smp_cpu_index_शेष(व्योम)
अणु
	पूर्णांक i;
	काष्ठा cpuinfo_x86 *c;

	क्रम_each_possible_cpu(i) अणु
		c = &cpu_data(i);
		/* mark all to hotplug */
		c->cpu_index = nr_cpu_ids;
	पूर्ण
पूर्ण

अटल व्योम __init smp_get_logical_apicid(व्योम)
अणु
	अगर (x2apic_mode)
		cpu0_logical_apicid = apic_पढ़ो(APIC_LDR);
	अन्यथा
		cpu0_logical_apicid = GET_APIC_LOGICAL_ID(apic_पढ़ो(APIC_LDR));
पूर्ण

/*
 * Prepare क्रम SMP bootup.
 * @max_cpus: configured maximum number of CPUs, It is a legacy parameter
 *            क्रम common पूर्णांकerface support.
 */
व्योम __init native_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	अचिन्हित पूर्णांक i;

	smp_cpu_index_शेष();

	/*
	 * Setup boot CPU inक्रमmation
	 */
	smp_store_boot_cpu_info(); /* Final full version of the data */
	cpumask_copy(cpu_callin_mask, cpumask_of(0));
	mb();

	क्रम_each_possible_cpu(i) अणु
		zalloc_cpumask_var(&per_cpu(cpu_sibling_map, i), GFP_KERNEL);
		zalloc_cpumask_var(&per_cpu(cpu_core_map, i), GFP_KERNEL);
		zalloc_cpumask_var(&per_cpu(cpu_die_map, i), GFP_KERNEL);
		zalloc_cpumask_var(&per_cpu(cpu_llc_shared_map, i), GFP_KERNEL);
	पूर्ण

	/*
	 * Set 'default' x86 topology, this matches शेष_topology() in that
	 * it has NUMA nodes as a topology level. See also
	 * native_smp_cpus_करोne().
	 *
	 * Must be करोne beक्रमe set_cpus_sibling_map() is ran.
	 */
	set_sched_topology(x86_topology);

	set_cpu_sibling_map(0);
	init_freq_invariance(false, false);
	smp_sanity_check();

	चयन (apic_पूर्णांकr_mode) अणु
	हाल APIC_PIC:
	हाल APIC_VIRTUAL_WIRE_NO_CONFIG:
		disable_smp();
		वापस;
	हाल APIC_SYMMETRIC_IO_NO_ROUTING:
		disable_smp();
		/* Setup local समयr */
		x86_init.समयrs.setup_percpu_घड़ीev();
		वापस;
	हाल APIC_VIRTUAL_WIRE:
	हाल APIC_SYMMETRIC_IO:
		अवरोध;
	पूर्ण

	/* Setup local समयr */
	x86_init.समयrs.setup_percpu_घड़ीev();

	smp_get_logical_apicid();

	pr_info("CPU0: ");
	prपूर्णांक_cpu_info(&cpu_data(0));

	uv_प्रणाली_init();

	set_mtrr_aps_delayed_init();

	smp_quirk_init_udelay();

	speculative_store_bypass_ht_init();
पूर्ण

व्योम arch_thaw_secondary_cpus_begin(व्योम)
अणु
	set_mtrr_aps_delayed_init();
पूर्ण

व्योम arch_thaw_secondary_cpus_end(व्योम)
अणु
	mtrr_aps_init();
पूर्ण

/*
 * Early setup to make prपूर्णांकk work.
 */
व्योम __init native_smp_prepare_boot_cpu(व्योम)
अणु
	पूर्णांक me = smp_processor_id();
	चयन_to_new_gdt(me);
	/* alपढ़ोy set me in cpu_online_mask in boot_cpu_init() */
	cpumask_set_cpu(me, cpu_callout_mask);
	cpu_set_state_online(me);
	native_pv_lock_init();
पूर्ण

व्योम __init calculate_max_logical_packages(व्योम)
अणु
	पूर्णांक ncpus;

	/*
	 * Today neither Intel nor AMD support heterogeneous प्रणालीs so
	 * extrapolate the boot cpu's data to all packages.
	 */
	ncpus = cpu_data(0).booted_cores * topology_max_smt_thपढ़ोs();
	__max_logical_packages = DIV_ROUND_UP(total_cpus, ncpus);
	pr_info("Max logical packages: %u\n", __max_logical_packages);
पूर्ण

व्योम __init native_smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
	pr_debug("Boot done\n");

	calculate_max_logical_packages();

	अगर (x86_has_numa_in_package)
		set_sched_topology(x86_numa_in_package_topology);

	nmi_selftest();
	impress_मित्रs();
	mtrr_aps_init();
पूर्ण

अटल पूर्णांक __initdata setup_possible_cpus = -1;
अटल पूर्णांक __init _setup_possible_cpus(अक्षर *str)
अणु
	get_option(&str, &setup_possible_cpus);
	वापस 0;
पूर्ण
early_param("possible_cpus", _setup_possible_cpus);


/*
 * cpu_possible_mask should be अटल, it cannot change as cpu's
 * are onlined, or offlined. The reason is per-cpu data-काष्ठाures
 * are allocated by some modules at init समय, and करोn't expect to
 * करो this dynamically on cpu arrival/departure.
 * cpu_present_mask on the other hand can change dynamically.
 * In हाल when cpu_hotplug is not compiled, then we resort to current
 * behaviour, which is cpu_possible == cpu_present.
 * - Ashok Raj
 *
 * Three ways to find out the number of additional hotplug CPUs:
 * - If the BIOS specअगरied disabled CPUs in ACPI/mptables use that.
 * - The user can overग_लिखो it with possible_cpus=NUM
 * - Otherwise करोn't reserve additional CPUs.
 * We करो this because additional CPUs waste a lot of memory.
 * -AK
 */
__init व्योम prefill_possible_map(व्योम)
अणु
	पूर्णांक i, possible;

	/* No boot processor was found in mptable or ACPI MADT */
	अगर (!num_processors) अणु
		अगर (boot_cpu_has(X86_FEATURE_APIC)) अणु
			पूर्णांक apicid = boot_cpu_physical_apicid;
			पूर्णांक cpu = hard_smp_processor_id();

			pr_warn("Boot CPU (id %d) not listed by BIOS\n", cpu);

			/* Make sure boot cpu is क्रमागतerated */
			अगर (apic->cpu_present_to_apicid(0) == BAD_APICID &&
			    apic->apic_id_valid(apicid))
				generic_processor_info(apicid, boot_cpu_apic_version);
		पूर्ण

		अगर (!num_processors)
			num_processors = 1;
	पूर्ण

	i = setup_max_cpus ?: 1;
	अगर (setup_possible_cpus == -1) अणु
		possible = num_processors;
#अगर_घोषित CONFIG_HOTPLUG_CPU
		अगर (setup_max_cpus)
			possible += disabled_cpus;
#अन्यथा
		अगर (possible > i)
			possible = i;
#पूर्ण_अगर
	पूर्ण अन्यथा
		possible = setup_possible_cpus;

	total_cpus = max_t(पूर्णांक, possible, num_processors + disabled_cpus);

	/* nr_cpu_ids could be reduced via nr_cpus= */
	अगर (possible > nr_cpu_ids) अणु
		pr_warn("%d Processors exceeds NR_CPUS limit of %u\n",
			possible, nr_cpu_ids);
		possible = nr_cpu_ids;
	पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
	अगर (!setup_max_cpus)
#पूर्ण_अगर
	अगर (possible > i) अणु
		pr_warn("%d Processors exceeds max_cpus limit of %u\n",
			possible, setup_max_cpus);
		possible = i;
	पूर्ण

	nr_cpu_ids = possible;

	pr_info("Allowing %d CPUs, %d hotplug CPUs\n",
		possible, max_t(पूर्णांक, possible - num_processors, 0));

	reset_cpu_possible_mask();

	क्रम (i = 0; i < possible; i++)
		set_cpu_possible(i, true);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

/* Recompute SMT state क्रम all CPUs on offline */
अटल व्योम recompute_smt_state(व्योम)
अणु
	पूर्णांक max_thपढ़ोs, cpu;

	max_thपढ़ोs = 0;
	क्रम_each_online_cpu (cpu) अणु
		पूर्णांक thपढ़ोs = cpumask_weight(topology_sibling_cpumask(cpu));

		अगर (thपढ़ोs > max_thपढ़ोs)
			max_thपढ़ोs = thपढ़ोs;
	पूर्ण
	__max_smt_thपढ़ोs = max_thपढ़ोs;
पूर्ण

अटल व्योम हटाओ_siblinginfo(पूर्णांक cpu)
अणु
	पूर्णांक sibling;
	काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

	क्रम_each_cpu(sibling, topology_core_cpumask(cpu)) अणु
		cpumask_clear_cpu(cpu, topology_core_cpumask(sibling));
		/*/
		 * last thपढ़ो sibling in this cpu core going करोwn
		 */
		अगर (cpumask_weight(topology_sibling_cpumask(cpu)) == 1)
			cpu_data(sibling).booted_cores--;
	पूर्ण

	क्रम_each_cpu(sibling, topology_die_cpumask(cpu))
		cpumask_clear_cpu(cpu, topology_die_cpumask(sibling));
	क्रम_each_cpu(sibling, topology_sibling_cpumask(cpu))
		cpumask_clear_cpu(cpu, topology_sibling_cpumask(sibling));
	क्रम_each_cpu(sibling, cpu_llc_shared_mask(cpu))
		cpumask_clear_cpu(cpu, cpu_llc_shared_mask(sibling));
	cpumask_clear(cpu_llc_shared_mask(cpu));
	cpumask_clear(topology_sibling_cpumask(cpu));
	cpumask_clear(topology_core_cpumask(cpu));
	cpumask_clear(topology_die_cpumask(cpu));
	c->cpu_core_id = 0;
	c->booted_cores = 0;
	cpumask_clear_cpu(cpu, cpu_sibling_setup_mask);
	recompute_smt_state();
पूर्ण

अटल व्योम हटाओ_cpu_from_maps(पूर्णांक cpu)
अणु
	set_cpu_online(cpu, false);
	cpumask_clear_cpu(cpu, cpu_callout_mask);
	cpumask_clear_cpu(cpu, cpu_callin_mask);
	/* was set by cpu_init() */
	cpumask_clear_cpu(cpu, cpu_initialized_mask);
	numa_हटाओ_cpu(cpu);
पूर्ण

व्योम cpu_disable_common(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	हटाओ_siblinginfo(cpu);

	/* It's now safe to हटाओ this processor from the online map */
	lock_vector_lock();
	हटाओ_cpu_from_maps(cpu);
	unlock_vector_lock();
	fixup_irqs();
	lapic_offline();
पूर्ण

पूर्णांक native_cpu_disable(व्योम)
अणु
	पूर्णांक ret;

	ret = lapic_can_unplug_cpu();
	अगर (ret)
		वापस ret;

	cpu_disable_common();

        /*
         * Disable the local APIC. Otherwise IPI broadcasts will reach
         * it. It still responds normally to INIT, NMI, SMI, and SIPI
         * messages.
         *
         * Disabling the APIC must happen after cpu_disable_common()
         * which invokes fixup_irqs().
         *
         * Disabling the APIC preserves alपढ़ोy set bits in IRR, but
         * an पूर्णांकerrupt arriving after disabling the local APIC करोes not
         * set the corresponding IRR bit.
         *
         * fixup_irqs() scans IRR क्रम set bits so it can उठाओ a not
         * yet handled पूर्णांकerrupt on the new destination CPU via an IPI
         * but obviously it can't करो so क्रम IRR bits which are not set.
         * IOW, पूर्णांकerrupts arriving after disabling the local APIC will
         * be lost.
         */
	apic_soft_disable();

	वापस 0;
पूर्ण

पूर्णांक common_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret = 0;

	/* We करोn't करो anything here: idle task is faking death itself. */

	/* They ack this in play_dead() by setting CPU_DEAD */
	अगर (cpu_रुको_death(cpu, 5)) अणु
		अगर (प्रणाली_state == SYSTEM_RUNNING)
			pr_info("CPU %u is now offline\n", cpu);
	पूर्ण अन्यथा अणु
		pr_err("CPU %u didn't die...\n", cpu);
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण

व्योम native_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	common_cpu_die(cpu);
पूर्ण

व्योम play_dead_common(व्योम)
अणु
	idle_task_निकास();

	/* Ack it */
	(व्योम)cpu_report_death();

	/*
	 * With physical CPU hotplug, we should halt the cpu
	 */
	local_irq_disable();
पूर्ण

/**
 * cond_wakeup_cpu0 - Wake up CPU0 अगर needed.
 *
 * If NMI wants to wake up CPU0, start CPU0.
 */
व्योम cond_wakeup_cpu0(व्योम)
अणु
	अगर (smp_processor_id() == 0 && enable_start_cpu0)
		start_cpu0();
पूर्ण
EXPORT_SYMBOL_GPL(cond_wakeup_cpu0);

/*
 * We need to flush the caches beक्रमe going to sleep, lest we have
 * dirty data in our caches when we come back up.
 */
अटल अंतरभूत व्योम mरुको_play_dead(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	अचिन्हित पूर्णांक highest_cstate = 0;
	अचिन्हित पूर्णांक highest_subcstate = 0;
	व्योम *mरुको_ptr;
	पूर्णांक i;

	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD ||
	    boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON)
		वापस;
	अगर (!this_cpu_has(X86_FEATURE_MWAIT))
		वापस;
	अगर (!this_cpu_has(X86_FEATURE_CLFLUSH))
		वापस;
	अगर (__this_cpu_पढ़ो(cpu_info.cpuid_level) < CPUID_MWAIT_LEAF)
		वापस;

	eax = CPUID_MWAIT_LEAF;
	ecx = 0;
	native_cpuid(&eax, &ebx, &ecx, &edx);

	/*
	 * eax will be 0 अगर EDX क्रमागतeration is not valid.
	 * Initialized below to cstate, sub_cstate value when EDX is valid.
	 */
	अगर (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPORTED)) अणु
		eax = 0;
	पूर्ण अन्यथा अणु
		edx >>= MWAIT_SUBSTATE_SIZE;
		क्रम (i = 0; i < 7 && edx; i++, edx >>= MWAIT_SUBSTATE_SIZE) अणु
			अगर (edx & MWAIT_SUBSTATE_MASK) अणु
				highest_cstate = i;
				highest_subcstate = edx & MWAIT_SUBSTATE_MASK;
			पूर्ण
		पूर्ण
		eax = (highest_cstate << MWAIT_SUBSTATE_SIZE) |
			(highest_subcstate - 1);
	पूर्ण

	/*
	 * This should be a memory location in a cache line which is
	 * unlikely to be touched by other processors.  The actual
	 * content is immaterial as it is not actually modअगरied in any way.
	 */
	mरुको_ptr = &current_thपढ़ो_info()->flags;

	wbinvd();

	जबतक (1) अणु
		/*
		 * The CLFLUSH is a workaround क्रम erratum AAI65 क्रम
		 * the Xeon 7400 series.  It's not clear it is actually
		 * needed, but it should be harmless in either हाल.
		 * The WBINVD is insufficient due to the spurious-wakeup
		 * हाल where we वापस around the loop.
		 */
		mb();
		clflush(mरुको_ptr);
		mb();
		__monitor(mरुको_ptr, 0, 0);
		mb();
		__mरुको(eax, 0);

		cond_wakeup_cpu0();
	पूर्ण
पूर्ण

व्योम hlt_play_dead(व्योम)
अणु
	अगर (__this_cpu_पढ़ो(cpu_info.x86) >= 4)
		wbinvd();

	जबतक (1) अणु
		native_halt();

		cond_wakeup_cpu0();
	पूर्ण
पूर्ण

व्योम native_play_dead(व्योम)
अणु
	play_dead_common();
	tboot_shutकरोwn(TB_SHUTDOWN_WFS);

	mरुको_play_dead();	/* Only वापसs on failure */
	अगर (cpuidle_play_dead())
		hlt_play_dead();
पूर्ण

#अन्यथा /* ... !CONFIG_HOTPLUG_CPU */
पूर्णांक native_cpu_disable(व्योम)
अणु
	वापस -ENOSYS;
पूर्ण

व्योम native_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	/* We said "no" in __cpu_disable */
	BUG();
पूर्ण

व्योम native_play_dead(व्योम)
अणु
	BUG();
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
/*
 * APERF/MPERF frequency ratio computation.
 *
 * The scheduler wants to करो frequency invariant accounting and needs a <1
 * ratio to account क्रम the 'current' frequency, corresponding to
 * freq_curr / freq_max.
 *
 * Since the frequency freq_curr on x86 is controlled by micro-controller and
 * our P-state setting is little more than a request/hपूर्णांक, we need to observe
 * the effective frequency 'BusyMHz', i.e. the average frequency over a समय
 * पूर्णांकerval after discarding idle समय. This is given by:
 *
 *   BusyMHz = delta_APERF / delta_MPERF * freq_base
 *
 * where freq_base is the max non-turbo P-state.
 *
 * The freq_max term has to be set to a somewhat arbitrary value, because we
 * can't know which turbo states will be available at a given poपूर्णांक in समय:
 * it all depends on the thermal headroom of the entire package. We set it to
 * the turbo level with 4 cores active.
 *
 * Benchmarks show that's a good compromise between the 1C turbo ratio
 * (freq_curr/freq_max would rarely reach 1) and something बंद to freq_base,
 * which would ignore the entire turbo range (a conspicuous part, making
 * freq_curr/freq_max always maxed out).
 *
 * An exception to the heuristic above is the Atom uarch, where we choose the
 * highest turbo level क्रम freq_max since Atom's are generally oriented towards
 * घातer efficiency.
 *
 * Setting freq_max to anything less than the 1C turbo ratio makes the ratio
 * freq_curr / freq_max to eventually grow >1, in which हाल we clip it to 1.
 */

DEFINE_STATIC_KEY_FALSE(arch_scale_freq_key);

अटल DEFINE_PER_CPU(u64, arch_prev_aperf);
अटल DEFINE_PER_CPU(u64, arch_prev_mperf);
अटल u64 arch_turbo_freq_ratio = SCHED_CAPACITY_SCALE;
अटल u64 arch_max_freq_ratio = SCHED_CAPACITY_SCALE;

व्योम arch_set_max_freq_ratio(bool turbo_disabled)
अणु
	arch_max_freq_ratio = turbo_disabled ? SCHED_CAPACITY_SCALE :
					arch_turbo_freq_ratio;
पूर्ण
EXPORT_SYMBOL_GPL(arch_set_max_freq_ratio);

अटल bool turbo_disabled(व्योम)
अणु
	u64 misc_en;
	पूर्णांक err;

	err = rdmsrl_safe(MSR_IA32_MISC_ENABLE, &misc_en);
	अगर (err)
		वापस false;

	वापस (misc_en & MSR_IA32_MISC_ENABLE_TURBO_DISABLE);
पूर्ण

अटल bool slv_set_max_freq_ratio(u64 *base_freq, u64 *turbo_freq)
अणु
	पूर्णांक err;

	err = rdmsrl_safe(MSR_ATOM_CORE_RATIOS, base_freq);
	अगर (err)
		वापस false;

	err = rdmsrl_safe(MSR_ATOM_CORE_TURBO_RATIOS, turbo_freq);
	अगर (err)
		वापस false;

	*base_freq = (*base_freq >> 16) & 0x3F;     /* max P state */
	*turbo_freq = *turbo_freq & 0x3F;           /* 1C turbo    */

	वापस true;
पूर्ण

#घोषणा X86_MATCH(model)					\
	X86_MATCH_VENDOR_FAM_MODEL_FEATURE(INTEL, 6,		\
		INTEL_FAM6_##model, X86_FEATURE_APERFMPERF, शून्य)

अटल स्थिर काष्ठा x86_cpu_id has_knl_turbo_ratio_limits[] = अणु
	X86_MATCH(XEON_PHI_KNL),
	X86_MATCH(XEON_PHI_KNM),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id has_skx_turbo_ratio_limits[] = अणु
	X86_MATCH(SKYLAKE_X),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id has_glm_turbo_ratio_limits[] = अणु
	X86_MATCH(ATOM_GOLDMONT),
	X86_MATCH(ATOM_GOLDMONT_D),
	X86_MATCH(ATOM_GOLDMONT_PLUS),
	अणुपूर्ण
पूर्ण;

अटल bool knl_set_max_freq_ratio(u64 *base_freq, u64 *turbo_freq,
				पूर्णांक num_delta_fratio)
अणु
	पूर्णांक fratio, delta_fratio, found;
	पूर्णांक err, i;
	u64 msr;

	err = rdmsrl_safe(MSR_PLATFORM_INFO, base_freq);
	अगर (err)
		वापस false;

	*base_freq = (*base_freq >> 8) & 0xFF;	    /* max P state */

	err = rdmsrl_safe(MSR_TURBO_RATIO_LIMIT, &msr);
	अगर (err)
		वापस false;

	fratio = (msr >> 8) & 0xFF;
	i = 16;
	found = 0;
	करो अणु
		अगर (found >= num_delta_fratio) अणु
			*turbo_freq = fratio;
			वापस true;
		पूर्ण

		delta_fratio = (msr >> (i + 5)) & 0x7;

		अगर (delta_fratio) अणु
			found += 1;
			fratio -= delta_fratio;
		पूर्ण

		i += 8;
	पूर्ण जबतक (i < 64);

	वापस true;
पूर्ण

अटल bool skx_set_max_freq_ratio(u64 *base_freq, u64 *turbo_freq, पूर्णांक size)
अणु
	u64 ratios, counts;
	u32 group_size;
	पूर्णांक err, i;

	err = rdmsrl_safe(MSR_PLATFORM_INFO, base_freq);
	अगर (err)
		वापस false;

	*base_freq = (*base_freq >> 8) & 0xFF;      /* max P state */

	err = rdmsrl_safe(MSR_TURBO_RATIO_LIMIT, &ratios);
	अगर (err)
		वापस false;

	err = rdmsrl_safe(MSR_TURBO_RATIO_LIMIT1, &counts);
	अगर (err)
		वापस false;

	क्रम (i = 0; i < 64; i += 8) अणु
		group_size = (counts >> i) & 0xFF;
		अगर (group_size >= size) अणु
			*turbo_freq = (ratios >> i) & 0xFF;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool core_set_max_freq_ratio(u64 *base_freq, u64 *turbo_freq)
अणु
	u64 msr;
	पूर्णांक err;

	err = rdmsrl_safe(MSR_PLATFORM_INFO, base_freq);
	अगर (err)
		वापस false;

	err = rdmsrl_safe(MSR_TURBO_RATIO_LIMIT, &msr);
	अगर (err)
		वापस false;

	*base_freq = (*base_freq >> 8) & 0xFF;    /* max P state */
	*turbo_freq = (msr >> 24) & 0xFF;         /* 4C turbo    */

	/* The CPU may have less than 4 cores */
	अगर (!*turbo_freq)
		*turbo_freq = msr & 0xFF;         /* 1C turbo    */

	वापस true;
पूर्ण

अटल bool पूर्णांकel_set_max_freq_ratio(व्योम)
अणु
	u64 base_freq, turbo_freq;
	u64 turbo_ratio;

	अगर (slv_set_max_freq_ratio(&base_freq, &turbo_freq))
		जाओ out;

	अगर (x86_match_cpu(has_glm_turbo_ratio_limits) &&
	    skx_set_max_freq_ratio(&base_freq, &turbo_freq, 1))
		जाओ out;

	अगर (x86_match_cpu(has_knl_turbo_ratio_limits) &&
	    knl_set_max_freq_ratio(&base_freq, &turbo_freq, 1))
		जाओ out;

	अगर (x86_match_cpu(has_skx_turbo_ratio_limits) &&
	    skx_set_max_freq_ratio(&base_freq, &turbo_freq, 4))
		जाओ out;

	अगर (core_set_max_freq_ratio(&base_freq, &turbo_freq))
		जाओ out;

	वापस false;

out:
	/*
	 * Some hypervisors advertise X86_FEATURE_APERFMPERF
	 * but then fill all MSR's with zeroes.
	 * Some CPUs have turbo boost but करोn't declare any turbo ratio
	 * in MSR_TURBO_RATIO_LIMIT.
	 */
	अगर (!base_freq || !turbo_freq) अणु
		pr_debug("Couldn't determine cpu base or turbo frequency, necessary for scale-invariant accounting.\n");
		वापस false;
	पूर्ण

	turbo_ratio = भाग_u64(turbo_freq * SCHED_CAPACITY_SCALE, base_freq);
	अगर (!turbo_ratio) अणु
		pr_debug("Non-zero turbo and base frequencies led to a 0 ratio.\n");
		वापस false;
	पूर्ण

	arch_turbo_freq_ratio = turbo_ratio;
	arch_set_max_freq_ratio(turbo_disabled());

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_ACPI_CPPC_LIB
अटल bool amd_set_max_freq_ratio(व्योम)
अणु
	काष्ठा cppc_perf_caps perf_caps;
	u64 highest_perf, nominal_perf;
	u64 perf_ratio;
	पूर्णांक rc;

	rc = cppc_get_perf_caps(0, &perf_caps);
	अगर (rc) अणु
		pr_debug("Could not retrieve perf counters (%d)\n", rc);
		वापस false;
	पूर्ण

	highest_perf = amd_get_highest_perf();
	nominal_perf = perf_caps.nominal_perf;

	अगर (!highest_perf || !nominal_perf) अणु
		pr_debug("Could not retrieve highest or nominal performance\n");
		वापस false;
	पूर्ण

	perf_ratio = भाग_u64(highest_perf * SCHED_CAPACITY_SCALE, nominal_perf);
	/* midpoपूर्णांक between max_boost and max_P */
	perf_ratio = (perf_ratio + SCHED_CAPACITY_SCALE) >> 1;
	अगर (!perf_ratio) अणु
		pr_debug("Non-zero highest/nominal perf values led to a 0 ratio\n");
		वापस false;
	पूर्ण

	arch_turbo_freq_ratio = perf_ratio;
	arch_set_max_freq_ratio(false);

	वापस true;
पूर्ण
#अन्यथा
अटल bool amd_set_max_freq_ratio(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल व्योम init_counter_refs(व्योम)
अणु
	u64 aperf, mperf;

	rdmsrl(MSR_IA32_APERF, aperf);
	rdmsrl(MSR_IA32_MPERF, mperf);

	this_cpu_ग_लिखो(arch_prev_aperf, aperf);
	this_cpu_ग_लिखो(arch_prev_mperf, mperf);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल काष्ठा syscore_ops freq_invariance_syscore_ops = अणु
	.resume = init_counter_refs,
पूर्ण;

अटल व्योम रेजिस्टर_freq_invariance_syscore_ops(व्योम)
अणु
	/* Bail out अगर रेजिस्टरed alपढ़ोy. */
	अगर (freq_invariance_syscore_ops.node.prev)
		वापस;

	रेजिस्टर_syscore_ops(&freq_invariance_syscore_ops);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम रेजिस्टर_freq_invariance_syscore_ops(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम init_freq_invariance(bool secondary, bool cppc_पढ़ोy)
अणु
	bool ret = false;

	अगर (!boot_cpu_has(X86_FEATURE_APERFMPERF))
		वापस;

	अगर (secondary) अणु
		अगर (अटल_branch_likely(&arch_scale_freq_key)) अणु
			init_counter_refs();
		पूर्ण
		वापस;
	पूर्ण

	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL)
		ret = पूर्णांकel_set_max_freq_ratio();
	अन्यथा अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD) अणु
		अगर (!cppc_पढ़ोy) अणु
			वापस;
		पूर्ण
		ret = amd_set_max_freq_ratio();
	पूर्ण

	अगर (ret) अणु
		init_counter_refs();
		अटल_branch_enable(&arch_scale_freq_key);
		रेजिस्टर_freq_invariance_syscore_ops();
		pr_info("Estimated ratio of average max frequency by base frequency (times 1024): %llu\n", arch_max_freq_ratio);
	पूर्ण अन्यथा अणु
		pr_debug("Couldn't determine max cpu frequency, necessary for scale-invariant accounting.\n");
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ACPI_CPPC_LIB
अटल DEFINE_MUTEX(freq_invariance_lock);

व्योम init_freq_invariance_cppc(व्योम)
अणु
	अटल bool secondary;

	mutex_lock(&freq_invariance_lock);

	init_freq_invariance(secondary, true);
	secondary = true;

	mutex_unlock(&freq_invariance_lock);
पूर्ण
#पूर्ण_अगर

अटल व्योम disable_freq_invariance_workfn(काष्ठा work_काष्ठा *work)
अणु
	अटल_branch_disable(&arch_scale_freq_key);
पूर्ण

अटल DECLARE_WORK(disable_freq_invariance_work,
		    disable_freq_invariance_workfn);

DEFINE_PER_CPU(अचिन्हित दीर्घ, arch_freq_scale) = SCHED_CAPACITY_SCALE;

व्योम arch_scale_freq_tick(व्योम)
अणु
	u64 freq_scale = SCHED_CAPACITY_SCALE;
	u64 aperf, mperf;
	u64 acnt, mcnt;

	अगर (!arch_scale_freq_invariant())
		वापस;

	rdmsrl(MSR_IA32_APERF, aperf);
	rdmsrl(MSR_IA32_MPERF, mperf);

	acnt = aperf - this_cpu_पढ़ो(arch_prev_aperf);
	mcnt = mperf - this_cpu_पढ़ो(arch_prev_mperf);

	this_cpu_ग_लिखो(arch_prev_aperf, aperf);
	this_cpu_ग_लिखो(arch_prev_mperf, mperf);

	अगर (check_shl_overflow(acnt, 2*SCHED_CAPACITY_SHIFT, &acnt))
		जाओ error;

	अगर (check_mul_overflow(mcnt, arch_max_freq_ratio, &mcnt) || !mcnt)
		जाओ error;

	freq_scale = भाग64_u64(acnt, mcnt);
	अगर (!freq_scale)
		जाओ error;

	अगर (freq_scale > SCHED_CAPACITY_SCALE)
		freq_scale = SCHED_CAPACITY_SCALE;

	this_cpu_ग_लिखो(arch_freq_scale, freq_scale);
	वापस;

error:
	pr_warn("Scheduler frequency invariance went wobbly, disabling!\n");
	schedule_work(&disable_freq_invariance_work);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम init_freq_invariance(bool secondary, bool cppc_पढ़ोy)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_64 */
