<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SMP initialisation and IPI support
 * Based on arch/arm64/kernel/smp.c
 *
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#समावेश <linux/arch_topology.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/percpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/mm.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/alternative.h>

#समावेश "head.h"

अटल DECLARE_COMPLETION(cpu_running);

व्योम __init smp_prepare_boot_cpu(व्योम)
अणु
	init_cpu_topology();
#अगर_घोषित CONFIG_RISCV_ERRATA_ALTERNATIVE
	apply_boot_alternatives();
#पूर्ण_अगर
पूर्ण

व्योम __init smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक cpuid;
	पूर्णांक ret;
	अचिन्हित पूर्णांक curr_cpuid;

	curr_cpuid = smp_processor_id();
	numa_store_cpu_info(curr_cpuid);
	numa_add_cpu(curr_cpuid);

	/* This covers non-smp useहाल mandated by "nosmp" option */
	अगर (max_cpus == 0)
		वापस;

	क्रम_each_possible_cpu(cpuid) अणु
		अगर (cpuid == curr_cpuid)
			जारी;
		अगर (cpu_ops[cpuid]->cpu_prepare) अणु
			ret = cpu_ops[cpuid]->cpu_prepare(cpuid);
			अगर (ret)
				जारी;
		पूर्ण
		set_cpu_present(cpuid, true);
		numa_store_cpu_info(cpuid);
	पूर्ण
पूर्ण

व्योम __init setup_smp(व्योम)
अणु
	काष्ठा device_node *dn;
	पूर्णांक hart;
	bool found_boot_cpu = false;
	पूर्णांक cpuid = 1;

	cpu_set_ops(0);

	क्रम_each_of_cpu_node(dn) अणु
		hart = riscv_of_processor_hartid(dn);
		अगर (hart < 0)
			जारी;

		अगर (hart == cpuid_to_hartid_map(0)) अणु
			BUG_ON(found_boot_cpu);
			found_boot_cpu = 1;
			early_map_cpu_to_node(0, of_node_to_nid(dn));
			जारी;
		पूर्ण
		अगर (cpuid >= NR_CPUS) अणु
			pr_warn("Invalid cpuid [%d] for hartid [%d]\n",
				cpuid, hart);
			अवरोध;
		पूर्ण

		cpuid_to_hartid_map(cpuid) = hart;
		early_map_cpu_to_node(cpuid, of_node_to_nid(dn));
		cpuid++;
	पूर्ण

	BUG_ON(!found_boot_cpu);

	अगर (cpuid > nr_cpu_ids)
		pr_warn("Total number of cpus [%d] is greater than nr_cpus option value [%d]\n",
			cpuid, nr_cpu_ids);

	क्रम (cpuid = 1; cpuid < nr_cpu_ids; cpuid++) अणु
		अगर (cpuid_to_hartid_map(cpuid) != INVALID_HARTID) अणु
			cpu_set_ops(cpuid);
			set_cpu_possible(cpuid, true);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक start_secondary_cpu(पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	अगर (cpu_ops[cpu]->cpu_start)
		वापस cpu_ops[cpu]->cpu_start(cpu, tidle);

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	पूर्णांक ret = 0;
	tidle->thपढ़ो_info.cpu = cpu;

	ret = start_secondary_cpu(cpu, tidle);
	अगर (!ret) अणु
		रुको_क्रम_completion_समयout(&cpu_running,
					    msecs_to_jअगरfies(1000));

		अगर (!cpu_online(cpu)) अणु
			pr_crit("CPU%u: failed to come online\n", cpu);
			ret = -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_crit("CPU%u: failed to start\n", cpu);
	पूर्ण

	वापस ret;
पूर्ण

व्योम __init smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

/*
 * C entry poपूर्णांक क्रम a secondary processor.
 */
यंत्रlinkage __visible व्योम smp_callin(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = &init_mm;
	अचिन्हित पूर्णांक curr_cpuid = smp_processor_id();

	riscv_clear_ipi();

	/* All kernel thपढ़ोs share the same mm context.  */
	mmgrab(mm);
	current->active_mm = mm;

	notअगरy_cpu_starting(curr_cpuid);
	numa_add_cpu(curr_cpuid);
	update_siblings_masks(curr_cpuid);
	set_cpu_online(curr_cpuid, 1);

	/*
	 * Remote TLB flushes are ignored जबतक the CPU is offline, so emit
	 * a local TLB flush right now just in हाल.
	 */
	local_flush_tlb_all();
	complete(&cpu_running);
	/*
	 * Disable preemption beक्रमe enabling पूर्णांकerrupts, so we करोn't try to
	 * schedule a CPU that hasn't actually started yet.
	 */
	preempt_disable();
	local_irq_enable();
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
पूर्ण
