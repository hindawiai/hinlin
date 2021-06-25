<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Arch specअगरic cpu topology inक्रमmation
 *
 * Copyright (C) 2016, ARM Ltd.
 * Written by: Juri Lelli, ARM Ltd.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched/topology.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>

अटल DEFINE_PER_CPU(काष्ठा scale_freq_data *, sft_data);
अटल काष्ठा cpumask scale_freq_counters_mask;
अटल bool scale_freq_invariant;

अटल bool supports_scale_freq_counters(स्थिर काष्ठा cpumask *cpus)
अणु
	वापस cpumask_subset(cpus, &scale_freq_counters_mask);
पूर्ण

bool topology_scale_freq_invariant(व्योम)
अणु
	वापस cpufreq_supports_freq_invariance() ||
	       supports_scale_freq_counters(cpu_online_mask);
पूर्ण

अटल व्योम update_scale_freq_invariant(bool status)
अणु
	अगर (scale_freq_invariant == status)
		वापस;

	/*
	 * Task scheduler behavior depends on frequency invariance support,
	 * either cpufreq or counter driven. If the support status changes as
	 * a result of counter initialisation and use, retrigger the build of
	 * scheduling करोमुख्यs to ensure the inक्रमmation is propagated properly.
	 */
	अगर (topology_scale_freq_invariant() == status) अणु
		scale_freq_invariant = status;
		rebuild_sched_करोमुख्यs_energy();
	पूर्ण
पूर्ण

व्योम topology_set_scale_freq_source(काष्ठा scale_freq_data *data,
				    स्थिर काष्ठा cpumask *cpus)
अणु
	काष्ठा scale_freq_data *sfd;
	पूर्णांक cpu;

	/*
	 * Aव्योम calling rebuild_sched_करोमुख्यs() unnecessarily अगर FIE is
	 * supported by cpufreq.
	 */
	अगर (cpumask_empty(&scale_freq_counters_mask))
		scale_freq_invariant = topology_scale_freq_invariant();

	क्रम_each_cpu(cpu, cpus) अणु
		sfd = per_cpu(sft_data, cpu);

		/* Use ARCH provided counters whenever possible */
		अगर (!sfd || sfd->source != SCALE_FREQ_SOURCE_ARCH) अणु
			per_cpu(sft_data, cpu) = data;
			cpumask_set_cpu(cpu, &scale_freq_counters_mask);
		पूर्ण
	पूर्ण

	update_scale_freq_invariant(true);
पूर्ण
EXPORT_SYMBOL_GPL(topology_set_scale_freq_source);

व्योम topology_clear_scale_freq_source(क्रमागत scale_freq_source source,
				      स्थिर काष्ठा cpumask *cpus)
अणु
	काष्ठा scale_freq_data *sfd;
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, cpus) अणु
		sfd = per_cpu(sft_data, cpu);

		अगर (sfd && sfd->source == source) अणु
			per_cpu(sft_data, cpu) = शून्य;
			cpumask_clear_cpu(cpu, &scale_freq_counters_mask);
		पूर्ण
	पूर्ण

	update_scale_freq_invariant(false);
पूर्ण
EXPORT_SYMBOL_GPL(topology_clear_scale_freq_source);

व्योम topology_scale_freq_tick(व्योम)
अणु
	काष्ठा scale_freq_data *sfd = *this_cpu_ptr(&sft_data);

	अगर (sfd)
		sfd->set_freq_scale();
पूर्ण

DEFINE_PER_CPU(अचिन्हित दीर्घ, arch_freq_scale) = SCHED_CAPACITY_SCALE;
EXPORT_PER_CPU_SYMBOL_GPL(arch_freq_scale);

व्योम topology_set_freq_scale(स्थिर काष्ठा cpumask *cpus, अचिन्हित दीर्घ cur_freq,
			     अचिन्हित दीर्घ max_freq)
अणु
	अचिन्हित दीर्घ scale;
	पूर्णांक i;

	अगर (WARN_ON_ONCE(!cur_freq || !max_freq))
		वापस;

	/*
	 * If the use of counters क्रम FIE is enabled, just वापस as we करोn't
	 * want to update the scale factor with inक्रमmation from CPUFREQ.
	 * Instead the scale factor will be updated from arch_scale_freq_tick.
	 */
	अगर (supports_scale_freq_counters(cpus))
		वापस;

	scale = (cur_freq << SCHED_CAPACITY_SHIFT) / max_freq;

	क्रम_each_cpu(i, cpus)
		per_cpu(arch_freq_scale, i) = scale;
पूर्ण

DEFINE_PER_CPU(अचिन्हित दीर्घ, cpu_scale) = SCHED_CAPACITY_SCALE;

व्योम topology_set_cpu_scale(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ capacity)
अणु
	per_cpu(cpu_scale, cpu) = capacity;
पूर्ण

DEFINE_PER_CPU(अचिन्हित दीर्घ, thermal_pressure);

व्योम topology_set_thermal_pressure(स्थिर काष्ठा cpumask *cpus,
			       अचिन्हित दीर्घ th_pressure)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, cpus)
		WRITE_ONCE(per_cpu(thermal_pressure, cpu), th_pressure);
पूर्ण

अटल sमाप_प्रकार cpu_capacity_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा cpu *cpu = container_of(dev, काष्ठा cpu, dev);

	वापस sysfs_emit(buf, "%lu\n", topology_get_cpu_scale(cpu->dev.id));
पूर्ण

अटल व्योम update_topology_flags_workfn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(update_topology_flags_work, update_topology_flags_workfn);

अटल DEVICE_ATTR_RO(cpu_capacity);

अटल पूर्णांक रेजिस्टर_cpu_capacity_sysctl(व्योम)
अणु
	पूर्णांक i;
	काष्ठा device *cpu;

	क्रम_each_possible_cpu(i) अणु
		cpu = get_cpu_device(i);
		अगर (!cpu) अणु
			pr_err("%s: too early to get CPU%d device!\n",
			       __func__, i);
			जारी;
		पूर्ण
		device_create_file(cpu, &dev_attr_cpu_capacity);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(रेजिस्टर_cpu_capacity_sysctl);

अटल पूर्णांक update_topology;

पूर्णांक topology_update_cpu_topology(व्योम)
अणु
	वापस update_topology;
पूर्ण

/*
 * Updating the sched_करोमुख्यs can't be करोne directly from cpufreq callbacks
 * due to locking, so queue the work क्रम later.
 */
अटल व्योम update_topology_flags_workfn(काष्ठा work_काष्ठा *work)
अणु
	update_topology = 1;
	rebuild_sched_करोमुख्यs();
	pr_debug("sched_domain hierarchy rebuilt, flags updated\n");
	update_topology = 0;
पूर्ण

अटल DEFINE_PER_CPU(u32, freq_factor) = 1;
अटल u32 *raw_capacity;

अटल पूर्णांक मुक्त_raw_capacity(व्योम)
अणु
	kमुक्त(raw_capacity);
	raw_capacity = शून्य;

	वापस 0;
पूर्ण

व्योम topology_normalize_cpu_scale(व्योम)
अणु
	u64 capacity;
	u64 capacity_scale;
	पूर्णांक cpu;

	अगर (!raw_capacity)
		वापस;

	capacity_scale = 1;
	क्रम_each_possible_cpu(cpu) अणु
		capacity = raw_capacity[cpu] * per_cpu(freq_factor, cpu);
		capacity_scale = max(capacity, capacity_scale);
	पूर्ण

	pr_debug("cpu_capacity: capacity_scale=%llu\n", capacity_scale);
	क्रम_each_possible_cpu(cpu) अणु
		capacity = raw_capacity[cpu] * per_cpu(freq_factor, cpu);
		capacity = भाग64_u64(capacity << SCHED_CAPACITY_SHIFT,
			capacity_scale);
		topology_set_cpu_scale(cpu, capacity);
		pr_debug("cpu_capacity: CPU%d cpu_capacity=%lu\n",
			cpu, topology_get_cpu_scale(cpu));
	पूर्ण
पूर्ण

bool __init topology_parse_cpu_capacity(काष्ठा device_node *cpu_node, पूर्णांक cpu)
अणु
	काष्ठा clk *cpu_clk;
	अटल bool cap_parsing_failed;
	पूर्णांक ret;
	u32 cpu_capacity;

	अगर (cap_parsing_failed)
		वापस false;

	ret = of_property_पढ़ो_u32(cpu_node, "capacity-dmips-mhz",
				   &cpu_capacity);
	अगर (!ret) अणु
		अगर (!raw_capacity) अणु
			raw_capacity = kसुस्मृति(num_possible_cpus(),
					       माप(*raw_capacity),
					       GFP_KERNEL);
			अगर (!raw_capacity) अणु
				cap_parsing_failed = true;
				वापस false;
			पूर्ण
		पूर्ण
		raw_capacity[cpu] = cpu_capacity;
		pr_debug("cpu_capacity: %pOF cpu_capacity=%u (raw)\n",
			cpu_node, raw_capacity[cpu]);

		/*
		 * Update freq_factor क्रम calculating early boot cpu capacities.
		 * For non-clk CPU DVFS mechanism, there's no way to get the
		 * frequency value now, assuming they are running at the same
		 * frequency (by keeping the initial freq_factor value).
		 */
		cpu_clk = of_clk_get(cpu_node, 0);
		अगर (!PTR_ERR_OR_ZERO(cpu_clk)) अणु
			per_cpu(freq_factor, cpu) =
				clk_get_rate(cpu_clk) / 1000;
			clk_put(cpu_clk);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (raw_capacity) अणु
			pr_err("cpu_capacity: missing %pOF raw capacity\n",
				cpu_node);
			pr_err("cpu_capacity: partial information: fallback to 1024 for all CPUs\n");
		पूर्ण
		cap_parsing_failed = true;
		मुक्त_raw_capacity();
	पूर्ण

	वापस !ret;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
अटल cpumask_var_t cpus_to_visit;
अटल व्योम parsing_करोne_workfn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(parsing_करोne_work, parsing_करोne_workfn);

अटल पूर्णांक
init_cpu_capacity_callback(काष्ठा notअगरier_block *nb,
			   अचिन्हित दीर्घ val,
			   व्योम *data)
अणु
	काष्ठा cpufreq_policy *policy = data;
	पूर्णांक cpu;

	अगर (!raw_capacity)
		वापस 0;

	अगर (val != CPUFREQ_CREATE_POLICY)
		वापस 0;

	pr_debug("cpu_capacity: init cpu capacity for CPUs [%*pbl] (to_visit=%*pbl)\n",
		 cpumask_pr_args(policy->related_cpus),
		 cpumask_pr_args(cpus_to_visit));

	cpumask_andnot(cpus_to_visit, cpus_to_visit, policy->related_cpus);

	क्रम_each_cpu(cpu, policy->related_cpus)
		per_cpu(freq_factor, cpu) = policy->cpuinfo.max_freq / 1000;

	अगर (cpumask_empty(cpus_to_visit)) अणु
		topology_normalize_cpu_scale();
		schedule_work(&update_topology_flags_work);
		मुक्त_raw_capacity();
		pr_debug("cpu_capacity: parsing done\n");
		schedule_work(&parsing_करोne_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block init_cpu_capacity_notअगरier = अणु
	.notअगरier_call = init_cpu_capacity_callback,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_cpufreq_notअगरier(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * on ACPI-based प्रणालीs we need to use the शेष cpu capacity
	 * until we have the necessary code to parse the cpu capacity, so
	 * skip रेजिस्टरing cpufreq notअगरier.
	 */
	अगर (!acpi_disabled || !raw_capacity)
		वापस -EINVAL;

	अगर (!alloc_cpumask_var(&cpus_to_visit, GFP_KERNEL))
		वापस -ENOMEM;

	cpumask_copy(cpus_to_visit, cpu_possible_mask);

	ret = cpufreq_रेजिस्टर_notअगरier(&init_cpu_capacity_notअगरier,
					CPUFREQ_POLICY_NOTIFIER);

	अगर (ret)
		मुक्त_cpumask_var(cpus_to_visit);

	वापस ret;
पूर्ण
core_initcall(रेजिस्टर_cpufreq_notअगरier);

अटल व्योम parsing_करोne_workfn(काष्ठा work_काष्ठा *work)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&init_cpu_capacity_notअगरier,
					 CPUFREQ_POLICY_NOTIFIER);
	मुक्त_cpumask_var(cpus_to_visit);
पूर्ण

#अन्यथा
core_initcall(मुक्त_raw_capacity);
#पूर्ण_अगर

#अगर defined(CONFIG_ARM64) || defined(CONFIG_RISCV)
/*
 * This function वापसs the logic cpu number of the node.
 * There are basically three kinds of वापस values:
 * (1) logic cpu number which is > 0.
 * (2) -ENODEV when the device tree(DT) node is valid and found in the DT but
 * there is no possible logical CPU in the kernel to match. This happens
 * when CONFIG_NR_CPUS is configure to be smaller than the number of
 * CPU nodes in DT. We need to just ignore this हाल.
 * (3) -1 अगर the node करोes not exist in the device tree
 */
अटल पूर्णांक __init get_cpu_क्रम_node(काष्ठा device_node *node)
अणु
	काष्ठा device_node *cpu_node;
	पूर्णांक cpu;

	cpu_node = of_parse_phandle(node, "cpu", 0);
	अगर (!cpu_node)
		वापस -1;

	cpu = of_cpu_node_to_id(cpu_node);
	अगर (cpu >= 0)
		topology_parse_cpu_capacity(cpu_node, cpu);
	अन्यथा
		pr_info("CPU node for %pOF exist but the possible cpu range is :%*pbl\n",
			cpu_node, cpumask_pr_args(cpu_possible_mask));

	of_node_put(cpu_node);
	वापस cpu;
पूर्ण

अटल पूर्णांक __init parse_core(काष्ठा device_node *core, पूर्णांक package_id,
			     पूर्णांक core_id)
अणु
	अक्षर name[20];
	bool leaf = true;
	पूर्णांक i = 0;
	पूर्णांक cpu;
	काष्ठा device_node *t;

	करो अणु
		snम_लिखो(name, माप(name), "thread%d", i);
		t = of_get_child_by_name(core, name);
		अगर (t) अणु
			leaf = false;
			cpu = get_cpu_क्रम_node(t);
			अगर (cpu >= 0) अणु
				cpu_topology[cpu].package_id = package_id;
				cpu_topology[cpu].core_id = core_id;
				cpu_topology[cpu].thपढ़ो_id = i;
			पूर्ण अन्यथा अगर (cpu != -ENODEV) अणु
				pr_err("%pOF: Can't get CPU for thread\n", t);
				of_node_put(t);
				वापस -EINVAL;
			पूर्ण
			of_node_put(t);
		पूर्ण
		i++;
	पूर्ण जबतक (t);

	cpu = get_cpu_क्रम_node(core);
	अगर (cpu >= 0) अणु
		अगर (!leaf) अणु
			pr_err("%pOF: Core has both threads and CPU\n",
			       core);
			वापस -EINVAL;
		पूर्ण

		cpu_topology[cpu].package_id = package_id;
		cpu_topology[cpu].core_id = core_id;
	पूर्ण अन्यथा अगर (leaf && cpu != -ENODEV) अणु
		pr_err("%pOF: Can't get CPU for leaf core\n", core);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init parse_cluster(काष्ठा device_node *cluster, पूर्णांक depth)
अणु
	अक्षर name[20];
	bool leaf = true;
	bool has_cores = false;
	काष्ठा device_node *c;
	अटल पूर्णांक package_id __initdata;
	पूर्णांक core_id = 0;
	पूर्णांक i, ret;

	/*
	 * First check क्रम child clusters; we currently ignore any
	 * inक्रमmation about the nesting of clusters and present the
	 * scheduler with a flat list of them.
	 */
	i = 0;
	करो अणु
		snम_लिखो(name, माप(name), "cluster%d", i);
		c = of_get_child_by_name(cluster, name);
		अगर (c) अणु
			leaf = false;
			ret = parse_cluster(c, depth + 1);
			of_node_put(c);
			अगर (ret != 0)
				वापस ret;
		पूर्ण
		i++;
	पूर्ण जबतक (c);

	/* Now check क्रम cores */
	i = 0;
	करो अणु
		snम_लिखो(name, माप(name), "core%d", i);
		c = of_get_child_by_name(cluster, name);
		अगर (c) अणु
			has_cores = true;

			अगर (depth == 0) अणु
				pr_err("%pOF: cpu-map children should be clusters\n",
				       c);
				of_node_put(c);
				वापस -EINVAL;
			पूर्ण

			अगर (leaf) अणु
				ret = parse_core(c, package_id, core_id++);
			पूर्ण अन्यथा अणु
				pr_err("%pOF: Non-leaf cluster with core %s\n",
				       cluster, name);
				ret = -EINVAL;
			पूर्ण

			of_node_put(c);
			अगर (ret != 0)
				वापस ret;
		पूर्ण
		i++;
	पूर्ण जबतक (c);

	अगर (leaf && !has_cores)
		pr_warn("%pOF: empty cluster\n", cluster);

	अगर (leaf)
		package_id++;

	वापस 0;
पूर्ण

अटल पूर्णांक __init parse_dt_topology(व्योम)
अणु
	काष्ठा device_node *cn, *map;
	पूर्णांक ret = 0;
	पूर्णांक cpu;

	cn = of_find_node_by_path("/cpus");
	अगर (!cn) अणु
		pr_err("No CPU information found in DT\n");
		वापस 0;
	पूर्ण

	/*
	 * When topology is provided cpu-map is essentially a root
	 * cluster with restricted subnodes.
	 */
	map = of_get_child_by_name(cn, "cpu-map");
	अगर (!map)
		जाओ out;

	ret = parse_cluster(map, 0);
	अगर (ret != 0)
		जाओ out_map;

	topology_normalize_cpu_scale();

	/*
	 * Check that all cores are in the topology; the SMP code will
	 * only mark cores described in the DT as possible.
	 */
	क्रम_each_possible_cpu(cpu)
		अगर (cpu_topology[cpu].package_id == -1)
			ret = -EINVAL;

out_map:
	of_node_put(map);
out:
	of_node_put(cn);
	वापस ret;
पूर्ण
#पूर्ण_अगर

/*
 * cpu topology table
 */
काष्ठा cpu_topology cpu_topology[NR_CPUS];
EXPORT_SYMBOL_GPL(cpu_topology);

स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu)
अणु
	स्थिर cpumask_t *core_mask = cpumask_of_node(cpu_to_node(cpu));

	/* Find the smaller of NUMA, core or LLC siblings */
	अगर (cpumask_subset(&cpu_topology[cpu].core_sibling, core_mask)) अणु
		/* not numa in package, lets use the package siblings */
		core_mask = &cpu_topology[cpu].core_sibling;
	पूर्ण
	अगर (cpu_topology[cpu].llc_id != -1) अणु
		अगर (cpumask_subset(&cpu_topology[cpu].llc_sibling, core_mask))
			core_mask = &cpu_topology[cpu].llc_sibling;
	पूर्ण

	वापस core_mask;
पूर्ण

व्योम update_siblings_masks(अचिन्हित पूर्णांक cpuid)
अणु
	काष्ठा cpu_topology *cpu_topo, *cpuid_topo = &cpu_topology[cpuid];
	पूर्णांक cpu;

	/* update core and thपढ़ो sibling masks */
	क्रम_each_online_cpu(cpu) अणु
		cpu_topo = &cpu_topology[cpu];

		अगर (cpuid_topo->llc_id == cpu_topo->llc_id) अणु
			cpumask_set_cpu(cpu, &cpuid_topo->llc_sibling);
			cpumask_set_cpu(cpuid, &cpu_topo->llc_sibling);
		पूर्ण

		अगर (cpuid_topo->package_id != cpu_topo->package_id)
			जारी;

		cpumask_set_cpu(cpuid, &cpu_topo->core_sibling);
		cpumask_set_cpu(cpu, &cpuid_topo->core_sibling);

		अगर (cpuid_topo->core_id != cpu_topo->core_id)
			जारी;

		cpumask_set_cpu(cpuid, &cpu_topo->thपढ़ो_sibling);
		cpumask_set_cpu(cpu, &cpuid_topo->thपढ़ो_sibling);
	पूर्ण
पूर्ण

अटल व्योम clear_cpu_topology(पूर्णांक cpu)
अणु
	काष्ठा cpu_topology *cpu_topo = &cpu_topology[cpu];

	cpumask_clear(&cpu_topo->llc_sibling);
	cpumask_set_cpu(cpu, &cpu_topo->llc_sibling);

	cpumask_clear(&cpu_topo->core_sibling);
	cpumask_set_cpu(cpu, &cpu_topo->core_sibling);
	cpumask_clear(&cpu_topo->thपढ़ो_sibling);
	cpumask_set_cpu(cpu, &cpu_topo->thपढ़ो_sibling);
पूर्ण

व्योम __init reset_cpu_topology(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cpu_topology *cpu_topo = &cpu_topology[cpu];

		cpu_topo->thपढ़ो_id = -1;
		cpu_topo->core_id = -1;
		cpu_topo->package_id = -1;
		cpu_topo->llc_id = -1;

		clear_cpu_topology(cpu);
	पूर्ण
पूर्ण

व्योम हटाओ_cpu_topology(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक sibling;

	क्रम_each_cpu(sibling, topology_core_cpumask(cpu))
		cpumask_clear_cpu(cpu, topology_core_cpumask(sibling));
	क्रम_each_cpu(sibling, topology_sibling_cpumask(cpu))
		cpumask_clear_cpu(cpu, topology_sibling_cpumask(sibling));
	क्रम_each_cpu(sibling, topology_llc_cpumask(cpu))
		cpumask_clear_cpu(cpu, topology_llc_cpumask(sibling));

	clear_cpu_topology(cpu);
पूर्ण

__weak पूर्णांक __init parse_acpi_topology(व्योम)
अणु
	वापस 0;
पूर्ण

#अगर defined(CONFIG_ARM64) || defined(CONFIG_RISCV)
व्योम __init init_cpu_topology(व्योम)
अणु
	reset_cpu_topology();

	/*
	 * Discard anything that was parsed अगर we hit an error so we
	 * करोn't use partial inक्रमmation.
	 */
	अगर (parse_acpi_topology())
		reset_cpu_topology();
	अन्यथा अगर (of_have_populated_dt() && parse_dt_topology())
		reset_cpu_topology();
पूर्ण
#पूर्ण_अगर
