<शैली गुरु>
/*
 * arch/arm64/kernel/topology.c
 *
 * Copyright (C) 2011,2013,2014 Linaro Limited.
 *
 * Based on the arm32 version written by Vincent Guittot in turn based on
 * arch/sh/kernel/topology.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/arch_topology.h>
#समावेश <linux/cacheinfo.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/topology.h>

व्योम store_cpu_topology(अचिन्हित पूर्णांक cpuid)
अणु
	काष्ठा cpu_topology *cpuid_topo = &cpu_topology[cpuid];
	u64 mpidr;

	अगर (cpuid_topo->package_id != -1)
		जाओ topology_populated;

	mpidr = पढ़ो_cpuid_mpidr();

	/* Uniprocessor प्रणालीs can rely on शेष topology values */
	अगर (mpidr & MPIDR_UP_BITMASK)
		वापस;

	/*
	 * This would be the place to create cpu topology based on MPIDR.
	 *
	 * However, it cannot be trusted to depict the actual topology; some
	 * pieces of the architecture enक्रमce an artअगरicial cap on Aff0 values
	 * (e.g. GICv3's ICC_SGI1R_EL1 limits it to 15), leading to an
	 * artअगरicial cycling of Aff1, Aff2 and Aff3 values. IOW, these end up
	 * having असलolutely no relationship to the actual underlying प्रणाली
	 * topology, and cannot be reasonably used as core / package ID.
	 *
	 * If the MT bit is set, Aff0 *could* be used to define a thपढ़ो ID, but
	 * we still wouldn't be able to obtain a sane core ID. This means we
	 * need to entirely ignore MPIDR क्रम any topology deduction.
	 */
	cpuid_topo->thपढ़ो_id  = -1;
	cpuid_topo->core_id    = cpuid;
	cpuid_topo->package_id = cpu_to_node(cpuid);

	pr_debug("CPU%u: cluster %d core %d thread %d mpidr %#016llx\n",
		 cpuid, cpuid_topo->package_id, cpuid_topo->core_id,
		 cpuid_topo->thपढ़ो_id, mpidr);

topology_populated:
	update_siblings_masks(cpuid);
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल bool __init acpi_cpu_is_thपढ़ोed(पूर्णांक cpu)
अणु
	पूर्णांक is_thपढ़ोed = acpi_pptt_cpu_is_thपढ़ो(cpu);

	/*
	 * अगर the PPTT करोesn't have thपढ़ो inक्रमmation, assume a homogeneous
	 * machine and वापस the current CPU's thपढ़ो state.
	 */
	अगर (is_thपढ़ोed < 0)
		is_thपढ़ोed = पढ़ो_cpuid_mpidr() & MPIDR_MT_BITMASK;

	वापस !!is_thपढ़ोed;
पूर्ण

/*
 * Propagate the topology inक्रमmation of the processor_topology_node tree to the
 * cpu_topology array.
 */
पूर्णांक __init parse_acpi_topology(व्योम)
अणु
	पूर्णांक cpu, topology_id;

	अगर (acpi_disabled)
		वापस 0;

	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक i, cache_id;

		topology_id = find_acpi_cpu_topology(cpu, 0);
		अगर (topology_id < 0)
			वापस topology_id;

		अगर (acpi_cpu_is_thपढ़ोed(cpu)) अणु
			cpu_topology[cpu].thपढ़ो_id = topology_id;
			topology_id = find_acpi_cpu_topology(cpu, 1);
			cpu_topology[cpu].core_id   = topology_id;
		पूर्ण अन्यथा अणु
			cpu_topology[cpu].thपढ़ो_id  = -1;
			cpu_topology[cpu].core_id    = topology_id;
		पूर्ण
		topology_id = find_acpi_cpu_topology_package(cpu);
		cpu_topology[cpu].package_id = topology_id;

		i = acpi_find_last_cache_level(cpu);

		अगर (i > 0) अणु
			/*
			 * this is the only part of cpu_topology that has
			 * a direct relationship with the cache topology
			 */
			cache_id = find_acpi_cpu_cache_topology(cpu, i);
			अगर (cache_id > 0)
				cpu_topology[cpu].llc_id = cache_id;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_AMU_EXTN
#घोषणा पढ़ो_corecnt()	पढ़ो_sysreg_s(SYS_AMEVCNTR0_CORE_EL0)
#घोषणा पढ़ो_स्थिरcnt()	पढ़ो_sysreg_s(SYS_AMEVCNTR0_CONST_EL0)
#अन्यथा
#घोषणा पढ़ो_corecnt()	(0UL)
#घोषणा पढ़ो_स्थिरcnt()	(0UL)
#पूर्ण_अगर

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "AMU: " fmt

अटल DEFINE_PER_CPU_READ_MOSTLY(अचिन्हित दीर्घ, arch_max_freq_scale);
अटल DEFINE_PER_CPU(u64, arch_स्थिर_cycles_prev);
अटल DEFINE_PER_CPU(u64, arch_core_cycles_prev);
अटल cpumask_var_t amu_fie_cpus;

व्योम update_freq_counters_refs(व्योम)
अणु
	this_cpu_ग_लिखो(arch_core_cycles_prev, पढ़ो_corecnt());
	this_cpu_ग_लिखो(arch_स्थिर_cycles_prev, पढ़ो_स्थिरcnt());
पूर्ण

अटल अंतरभूत bool freq_counters_valid(पूर्णांक cpu)
अणु
	अगर ((cpu >= nr_cpu_ids) || !cpumask_test_cpu(cpu, cpu_present_mask))
		वापस false;

	अगर (!cpu_has_amu_feat(cpu)) अणु
		pr_debug("CPU%d: counters are not supported.\n", cpu);
		वापस false;
	पूर्ण

	अगर (unlikely(!per_cpu(arch_स्थिर_cycles_prev, cpu) ||
		     !per_cpu(arch_core_cycles_prev, cpu))) अणु
		pr_debug("CPU%d: cycle counters are not enabled.\n", cpu);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक freq_inv_set_max_ratio(पूर्णांक cpu, u64 max_rate, u64 ref_rate)
अणु
	u64 ratio;

	अगर (unlikely(!max_rate || !ref_rate)) अणु
		pr_debug("CPU%d: invalid maximum or reference frequency.\n",
			 cpu);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Pre-compute the fixed ratio between the frequency of the स्थिरant
	 * reference counter and the maximum frequency of the CPU.
	 *
	 *			    ref_rate
	 * arch_max_freq_scale =   ---------- * SCHED_CAPACITY_SCALEतऑ
	 *			    max_rate
	 *
	 * We use a factor of 2 * SCHED_CAPACITY_SHIFT -> SCHED_CAPACITY_SCALEतऑ
	 * in order to ensure a good resolution क्रम arch_max_freq_scale क्रम
	 * very low reference frequencies (करोwn to the KHz range which should
	 * be unlikely).
	 */
	ratio = ref_rate << (2 * SCHED_CAPACITY_SHIFT);
	ratio = भाग64_u64(ratio, max_rate);
	अगर (!ratio) अणु
		WARN_ONCE(1, "Reference frequency too low.\n");
		वापस -EINVAL;
	पूर्ण

	per_cpu(arch_max_freq_scale, cpu) = (अचिन्हित दीर्घ)ratio;

	वापस 0;
पूर्ण

अटल व्योम amu_scale_freq_tick(व्योम)
अणु
	u64 prev_core_cnt, prev_स्थिर_cnt;
	u64 core_cnt, स्थिर_cnt, scale;

	prev_स्थिर_cnt = this_cpu_पढ़ो(arch_स्थिर_cycles_prev);
	prev_core_cnt = this_cpu_पढ़ो(arch_core_cycles_prev);

	update_freq_counters_refs();

	स्थिर_cnt = this_cpu_पढ़ो(arch_स्थिर_cycles_prev);
	core_cnt = this_cpu_पढ़ो(arch_core_cycles_prev);

	अगर (unlikely(core_cnt <= prev_core_cnt ||
		     स्थिर_cnt <= prev_स्थिर_cnt))
		वापस;

	/*
	 *	    /\core    arch_max_freq_scale
	 * scale =  ------- * --------------------
	 *	    /\स्थिर   SCHED_CAPACITY_SCALE
	 *
	 * See validate_cpu_freq_invariance_counters() क्रम details on
	 * arch_max_freq_scale and the use of SCHED_CAPACITY_SHIFT.
	 */
	scale = core_cnt - prev_core_cnt;
	scale *= this_cpu_पढ़ो(arch_max_freq_scale);
	scale = भाग64_u64(scale >> SCHED_CAPACITY_SHIFT,
			  स्थिर_cnt - prev_स्थिर_cnt);

	scale = min_t(अचिन्हित दीर्घ, scale, SCHED_CAPACITY_SCALE);
	this_cpu_ग_लिखो(arch_freq_scale, (अचिन्हित दीर्घ)scale);
पूर्ण

अटल काष्ठा scale_freq_data amu_sfd = अणु
	.source = SCALE_FREQ_SOURCE_ARCH,
	.set_freq_scale = amu_scale_freq_tick,
पूर्ण;

अटल व्योम amu_fie_setup(स्थिर काष्ठा cpumask *cpus)
अणु
	पूर्णांक cpu;

	/* We are alपढ़ोy set since the last insmod of cpufreq driver */
	अगर (unlikely(cpumask_subset(cpus, amu_fie_cpus)))
		वापस;

	क्रम_each_cpu(cpu, cpus) अणु
		अगर (!freq_counters_valid(cpu) ||
		    freq_inv_set_max_ratio(cpu,
					   cpufreq_get_hw_max_freq(cpu) * 1000,
					   arch_समयr_get_rate()))
			वापस;
	पूर्ण

	cpumask_or(amu_fie_cpus, amu_fie_cpus, cpus);

	topology_set_scale_freq_source(&amu_sfd, amu_fie_cpus);

	pr_debug("CPUs[%*pbl]: counters will be used for FIE.",
		 cpumask_pr_args(cpus));
पूर्ण

अटल पूर्णांक init_amu_fie_callback(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				 व्योम *data)
अणु
	काष्ठा cpufreq_policy *policy = data;

	अगर (val == CPUFREQ_CREATE_POLICY)
		amu_fie_setup(policy->related_cpus);

	/*
	 * We करोn't need to handle CPUFREQ_REMOVE_POLICY event as the AMU
	 * counters करोn't have any dependency on cpufreq driver once we have
	 * initialized AMU support and enabled invariance. The AMU counters will
	 * keep on working just fine in the असलence of the cpufreq driver, and
	 * क्रम the CPUs क्रम which there are no counters available, the last set
	 * value of arch_freq_scale will reमुख्य valid as that is the frequency
	 * those CPUs are running at.
	 */

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block init_amu_fie_notअगरier = अणु
	.notअगरier_call = init_amu_fie_callback,
पूर्ण;

अटल पूर्णांक __init init_amu_fie(व्योम)
अणु
	पूर्णांक ret;

	अगर (!zalloc_cpumask_var(&amu_fie_cpus, GFP_KERNEL))
		वापस -ENOMEM;

	ret = cpufreq_रेजिस्टर_notअगरier(&init_amu_fie_notअगरier,
					CPUFREQ_POLICY_NOTIFIER);
	अगर (ret)
		मुक्त_cpumask_var(amu_fie_cpus);

	वापस ret;
पूर्ण
core_initcall(init_amu_fie);

#अगर_घोषित CONFIG_ACPI_CPPC_LIB
#समावेश <acpi/cppc_acpi.h>

अटल व्योम cpu_पढ़ो_corecnt(व्योम *val)
अणु
	*(u64 *)val = पढ़ो_corecnt();
पूर्ण

अटल व्योम cpu_पढ़ो_स्थिरcnt(व्योम *val)
अणु
	*(u64 *)val = पढ़ो_स्थिरcnt();
पूर्ण

अटल अंतरभूत
पूर्णांक counters_पढ़ो_on_cpu(पूर्णांक cpu, smp_call_func_t func, u64 *val)
अणु
	/*
	 * Abort call on counterless CPU or when पूर्णांकerrupts are
	 * disabled - can lead to deadlock in smp sync call.
	 */
	अगर (!cpu_has_amu_feat(cpu))
		वापस -EOPNOTSUPP;

	अगर (WARN_ON_ONCE(irqs_disabled()))
		वापस -EPERM;

	smp_call_function_single(cpu, func, val, 1);

	वापस 0;
पूर्ण

/*
 * Refer to drivers/acpi/cppc_acpi.c क्रम the description of the functions
 * below.
 */
bool cpc_ffh_supported(व्योम)
अणु
	वापस freq_counters_valid(get_cpu_with_amu_feat());
पूर्ण

पूर्णांक cpc_पढ़ो_ffh(पूर्णांक cpu, काष्ठा cpc_reg *reg, u64 *val)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	चयन ((u64)reg->address) अणु
	हाल 0x0:
		ret = counters_पढ़ो_on_cpu(cpu, cpu_पढ़ो_corecnt, val);
		अवरोध;
	हाल 0x1:
		ret = counters_पढ़ो_on_cpu(cpu, cpu_पढ़ो_स्थिरcnt, val);
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		*val &= GENMASK_ULL(reg->bit_offset + reg->bit_width - 1,
				    reg->bit_offset);
		*val >>= reg->bit_offset;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cpc_ग_लिखो_ffh(पूर्णांक cpunum, काष्ठा cpc_reg *reg, u64 val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_CPPC_LIB */
