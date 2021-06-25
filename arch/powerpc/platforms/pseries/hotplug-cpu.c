<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pseries CPU Hotplug infraकाष्ठाure.
 *
 * Split out from arch/घातerpc/platक्रमms/pseries/setup.c
 *  arch/घातerpc/kernel/rtas.c, and arch/घातerpc/platक्रमms/pseries/smp.c
 *
 * Peter Bergner, IBM	March 2001.
 * Copyright (C) 2001 IBM.
 * Dave Engebretsen, Peter Bergner, and
 * Mike Corrigan अणुengebret|bergner|mikecपूर्ण@us.ibm.com
 * Plus various changes from other IBM teams...
 *
 * Copyright (C) 2006 Michael Ellerman, IBM Corporation
 */

#घोषणा pr_fmt(fmt)     "pseries-hotplug-cpu: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>	/* क्रम idle_task_निकास */
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/plpar_wrappers.h>
#समावेश <यंत्र/topology.h>

#समावेश "pseries.h"

/* This version can't take the spinlock, because it never वापसs */
अटल पूर्णांक rtas_stop_self_token = RTAS_UNKNOWN_SERVICE;

अटल व्योम rtas_stop_self(व्योम)
अणु
	अटल काष्ठा rtas_args args;

	local_irq_disable();

	BUG_ON(rtas_stop_self_token == RTAS_UNKNOWN_SERVICE);

	rtas_call_unlocked(&args, rtas_stop_self_token, 0, 1, शून्य);

	panic("Alas, I survived.\n");
पूर्ण

अटल व्योम pseries_cpu_offline_self(व्योम)
अणु
	अचिन्हित पूर्णांक hwcpu = hard_smp_processor_id();

	local_irq_disable();
	idle_task_निकास();
	अगर (xive_enabled())
		xive_tearकरोwn_cpu();
	अन्यथा
		xics_tearकरोwn_cpu();

	unरेजिस्टर_slb_shaकरोw(hwcpu);
	rtas_stop_self();

	/* Should never get here... */
	BUG();
	क्रम(;;);
पूर्ण

अटल पूर्णांक pseries_cpu_disable(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	set_cpu_online(cpu, false);
	vdso_data->processorCount--;

	/*fix boot_cpuid here*/
	अगर (cpu == boot_cpuid)
		boot_cpuid = cpumask_any(cpu_online_mask);

	/* FIXME: असलtract this to not be platक्रमm specअगरic later on */
	अगर (xive_enabled())
		xive_smp_disable_cpu();
	अन्यथा
		xics_migrate_irqs_away();

	cleanup_cpu_mmu_context();

	वापस 0;
पूर्ण

/*
 * pseries_cpu_die: Wait क्रम the cpu to die.
 * @cpu: logical processor id of the CPU whose death we're aरुकोing.
 *
 * This function is called from the context of the thपढ़ो which is perक्रमming
 * the cpu-offline. Here we रुको क्रम दीर्घ enough to allow the cpu in question
 * to self-destroy so that the cpu-offline thपढ़ो can send the CPU_DEAD
 * notअगरications.
 *
 * OTOH, pseries_cpu_offline_self() is called by the @cpu when it wants to
 * self-deकाष्ठा.
 */
अटल व्योम pseries_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक cpu_status = 1;
	अचिन्हित पूर्णांक pcpu = get_hard_smp_processor_id(cpu);
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(120000);

	जबतक (true) अणु
		cpu_status = smp_query_cpu_stopped(pcpu);
		अगर (cpu_status == QCSS_STOPPED ||
		    cpu_status == QCSS_HARDWARE_ERROR)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			pr_warn("CPU %i (hwid %i) didn't die after 120 seconds\n",
				cpu, pcpu);
			समयout = jअगरfies + msecs_to_jअगरfies(120000);
		पूर्ण

		cond_resched();
	पूर्ण

	अगर (cpu_status == QCSS_HARDWARE_ERROR) अणु
		pr_warn("CPU %i (hwid %i) reported error while dying\n",
			cpu, pcpu);
	पूर्ण

	/* Isolation and deallocation are definitely करोne by
	 * drslot_chrp_cpu.  If they were not they would be
	 * करोne here.  Change isolate state to Isolate and
	 * change allocation-state to Unusable.
	 */
	paca_ptrs[cpu]->cpu_start = 0;
पूर्ण

/*
 * Update cpu_present_mask and paca(s) क्रम a new cpu node.  The wrinkle
 * here is that a cpu device node may represent up to two logical cpus
 * in the SMT हाल.  We must honor the assumption in other code that
 * the logical ids क्रम sibling SMT thपढ़ोs x and y are adjacent, such
 * that x^1 == y and y^1 == x.
 */
अटल पूर्णांक pseries_add_processor(काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक cpu;
	cpumask_var_t candidate_mask, पंचांगp;
	पूर्णांक err = -ENOSPC, len, nthपढ़ोs, i;
	स्थिर __be32 *पूर्णांकserv;

	पूर्णांकserv = of_get_property(np, "ibm,ppc-interrupt-server#s", &len);
	अगर (!पूर्णांकserv)
		वापस 0;

	zalloc_cpumask_var(&candidate_mask, GFP_KERNEL);
	zalloc_cpumask_var(&पंचांगp, GFP_KERNEL);

	nthपढ़ोs = len / माप(u32);
	क्रम (i = 0; i < nthपढ़ोs; i++)
		cpumask_set_cpu(i, पंचांगp);

	cpu_maps_update_begin();

	BUG_ON(!cpumask_subset(cpu_present_mask, cpu_possible_mask));

	/* Get a biपंचांगap of unoccupied slots. */
	cpumask_xor(candidate_mask, cpu_possible_mask, cpu_present_mask);
	अगर (cpumask_empty(candidate_mask)) अणु
		/* If we get here, it most likely means that NR_CPUS is
		 * less than the partition's max processors setting.
		 */
		prपूर्णांकk(KERN_ERR "Cannot add cpu %pOF; this system configuration"
		       " supports %d logical cpus.\n", np,
		       num_possible_cpus());
		जाओ out_unlock;
	पूर्ण

	जबतक (!cpumask_empty(पंचांगp))
		अगर (cpumask_subset(पंचांगp, candidate_mask))
			/* Found a range where we can insert the new cpu(s) */
			अवरोध;
		अन्यथा
			cpumask_shअगरt_left(पंचांगp, पंचांगp, nthपढ़ोs);

	अगर (cpumask_empty(पंचांगp)) अणु
		prपूर्णांकk(KERN_ERR "Unable to find space in cpu_present_mask for"
		       " processor %pOFn with %d thread(s)\n", np,
		       nthपढ़ोs);
		जाओ out_unlock;
	पूर्ण

	क्रम_each_cpu(cpu, पंचांगp) अणु
		BUG_ON(cpu_present(cpu));
		set_cpu_present(cpu, true);
		set_hard_smp_processor_id(cpu, be32_to_cpu(*पूर्णांकserv++));
	पूर्ण
	err = 0;
out_unlock:
	cpu_maps_update_करोne();
	मुक्त_cpumask_var(candidate_mask);
	मुक्त_cpumask_var(पंचांगp);
	वापस err;
पूर्ण

/*
 * Update the present map क्रम a cpu node which is going away, and set
 * the hard id in the paca(s) to -1 to be consistent with boot समय
 * convention क्रम non-present cpus.
 */
अटल व्योम pseries_हटाओ_processor(काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक cpu;
	पूर्णांक len, nthपढ़ोs, i;
	स्थिर __be32 *पूर्णांकserv;
	u32 thपढ़ो;

	पूर्णांकserv = of_get_property(np, "ibm,ppc-interrupt-server#s", &len);
	अगर (!पूर्णांकserv)
		वापस;

	nthपढ़ोs = len / माप(u32);

	cpu_maps_update_begin();
	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		thपढ़ो = be32_to_cpu(पूर्णांकserv[i]);
		क्रम_each_present_cpu(cpu) अणु
			अगर (get_hard_smp_processor_id(cpu) != thपढ़ो)
				जारी;
			BUG_ON(cpu_online(cpu));
			set_cpu_present(cpu, false);
			set_hard_smp_processor_id(cpu, -1);
			update_numa_cpu_lookup_table(cpu, -1);
			अवरोध;
		पूर्ण
		अगर (cpu >= nr_cpu_ids)
			prपूर्णांकk(KERN_WARNING "Could not find cpu to remove "
			       "with physical id 0x%x\n", thपढ़ो);
	पूर्ण
	cpu_maps_update_करोne();
पूर्ण

अटल पूर्णांक dlpar_offline_cpu(काष्ठा device_node *dn)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक len, nthपढ़ोs, i;
	स्थिर __be32 *पूर्णांकserv;
	u32 thपढ़ो;

	पूर्णांकserv = of_get_property(dn, "ibm,ppc-interrupt-server#s", &len);
	अगर (!पूर्णांकserv)
		वापस -EINVAL;

	nthपढ़ोs = len / माप(u32);

	cpu_maps_update_begin();
	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		thपढ़ो = be32_to_cpu(पूर्णांकserv[i]);
		क्रम_each_present_cpu(cpu) अणु
			अगर (get_hard_smp_processor_id(cpu) != thपढ़ो)
				जारी;

			अगर (!cpu_online(cpu))
				अवरोध;

			/*
			 * device_offline() will वापस -EBUSY (via cpu_करोwn()) अगर there
			 * is only one CPU left. Check it here to fail earlier and with a
			 * more inक्रमmative error message, जबतक also retaining the
			 * cpu_add_हटाओ_lock to be sure that no CPUs are being
			 * online/offlined during this check.
			 */
			अगर (num_online_cpus() == 1) अणु
				pr_warn("Unable to remove last online CPU %pOFn\n", dn);
				rc = -EBUSY;
				जाओ out_unlock;
			पूर्ण

			cpu_maps_update_करोne();
			rc = device_offline(get_cpu_device(cpu));
			अगर (rc)
				जाओ out;
			cpu_maps_update_begin();
			अवरोध;
		पूर्ण
		अगर (cpu == num_possible_cpus()) अणु
			pr_warn("Could not find cpu to offline with physical id 0x%x\n",
				thपढ़ो);
		पूर्ण
	पूर्ण
out_unlock:
	cpu_maps_update_करोne();

out:
	वापस rc;
पूर्ण

अटल पूर्णांक dlpar_online_cpu(काष्ठा device_node *dn)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक len, nthपढ़ोs, i;
	स्थिर __be32 *पूर्णांकserv;
	u32 thपढ़ो;

	पूर्णांकserv = of_get_property(dn, "ibm,ppc-interrupt-server#s", &len);
	अगर (!पूर्णांकserv)
		वापस -EINVAL;

	nthपढ़ोs = len / माप(u32);

	cpu_maps_update_begin();
	क्रम (i = 0; i < nthपढ़ोs; i++) अणु
		thपढ़ो = be32_to_cpu(पूर्णांकserv[i]);
		क्रम_each_present_cpu(cpu) अणु
			अगर (get_hard_smp_processor_id(cpu) != thपढ़ो)
				जारी;
			cpu_maps_update_करोne();
			find_and_online_cpu_nid(cpu);
			rc = device_online(get_cpu_device(cpu));
			अगर (rc) अणु
				dlpar_offline_cpu(dn);
				जाओ out;
			पूर्ण
			cpu_maps_update_begin();

			अवरोध;
		पूर्ण
		अगर (cpu == num_possible_cpus())
			prपूर्णांकk(KERN_WARNING "Could not find cpu to online "
			       "with physical id 0x%x\n", thपढ़ो);
	पूर्ण
	cpu_maps_update_करोne();

out:
	वापस rc;

पूर्ण

अटल bool dlpar_cpu_exists(काष्ठा device_node *parent, u32 drc_index)
अणु
	काष्ठा device_node *child = शून्य;
	u32 my_drc_index;
	bool found;
	पूर्णांक rc;

	/* Assume cpu करोesn't exist */
	found = false;

	क्रम_each_child_of_node(parent, child) अणु
		rc = of_property_पढ़ो_u32(child, "ibm,my-drc-index",
					  &my_drc_index);
		अगर (rc)
			जारी;

		अगर (my_drc_index == drc_index) अणु
			of_node_put(child);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल bool drc_info_valid_index(काष्ठा device_node *parent, u32 drc_index)
अणु
	काष्ठा property *info;
	काष्ठा of_drc_info drc;
	स्थिर __be32 *value;
	u32 index;
	पूर्णांक count, i, j;

	info = of_find_property(parent, "ibm,drc-info", शून्य);
	अगर (!info)
		वापस false;

	value = of_prop_next_u32(info, शून्य, &count);

	/* First value of ibm,drc-info is number of drc-info records */
	अगर (value)
		value++;
	अन्यथा
		वापस false;

	क्रम (i = 0; i < count; i++) अणु
		अगर (of_पढ़ो_drc_info_cell(&info, &value, &drc))
			वापस false;

		अगर (म_भेदन(drc.drc_type, "CPU", 3))
			अवरोध;

		अगर (drc_index > drc.last_drc_index)
			जारी;

		index = drc.drc_index_start;
		क्रम (j = 0; j < drc.num_sequential_elems; j++) अणु
			अगर (drc_index == index)
				वापस true;

			index += drc.sequential_inc;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool valid_cpu_drc_index(काष्ठा device_node *parent, u32 drc_index)
अणु
	bool found = false;
	पूर्णांक rc, index;

	अगर (of_find_property(parent, "ibm,drc-info", शून्य))
		वापस drc_info_valid_index(parent, drc_index);

	/* Note that the क्रमmat of the ibm,drc-indexes array is
	 * the number of entries in the array followed by the array
	 * of drc values so we start looking at index = 1.
	 */
	index = 1;
	जबतक (!found) अणु
		u32 drc;

		rc = of_property_पढ़ो_u32_index(parent, "ibm,drc-indexes",
						index++, &drc);

		अगर (rc)
			अवरोध;

		अगर (drc == drc_index)
			found = true;
	पूर्ण

	वापस found;
पूर्ण

अटल sमाप_प्रकार dlpar_cpu_add(u32 drc_index)
अणु
	काष्ठा device_node *dn, *parent;
	पूर्णांक rc, saved_rc;

	pr_debug("Attempting to add CPU, drc index: %x\n", drc_index);

	parent = of_find_node_by_path("/cpus");
	अगर (!parent) अणु
		pr_warn("Failed to find CPU root node \"/cpus\"\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dlpar_cpu_exists(parent, drc_index)) अणु
		of_node_put(parent);
		pr_warn("CPU with drc index %x already exists\n", drc_index);
		वापस -EINVAL;
	पूर्ण

	अगर (!valid_cpu_drc_index(parent, drc_index)) अणु
		of_node_put(parent);
		pr_warn("Cannot find CPU (drc index %x) to add.\n", drc_index);
		वापस -EINVAL;
	पूर्ण

	rc = dlpar_acquire_drc(drc_index);
	अगर (rc) अणु
		pr_warn("Failed to acquire DRC, rc: %d, drc index: %x\n",
			rc, drc_index);
		of_node_put(parent);
		वापस -EINVAL;
	पूर्ण

	dn = dlpar_configure_connector(cpu_to_be32(drc_index), parent);
	अगर (!dn) अणु
		pr_warn("Failed call to configure-connector, drc index: %x\n",
			drc_index);
		dlpar_release_drc(drc_index);
		of_node_put(parent);
		वापस -EINVAL;
	पूर्ण

	rc = dlpar_attach_node(dn, parent);

	/* Regardless we are करोne with parent now */
	of_node_put(parent);

	अगर (rc) अणु
		saved_rc = rc;
		pr_warn("Failed to attach node %pOFn, rc: %d, drc index: %x\n",
			dn, rc, drc_index);

		rc = dlpar_release_drc(drc_index);
		अगर (!rc)
			dlpar_मुक्त_cc_nodes(dn);

		वापस saved_rc;
	पूर्ण

	rc = dlpar_online_cpu(dn);
	अगर (rc) अणु
		saved_rc = rc;
		pr_warn("Failed to online cpu %pOFn, rc: %d, drc index: %x\n",
			dn, rc, drc_index);

		rc = dlpar_detach_node(dn);
		अगर (!rc)
			dlpar_release_drc(drc_index);

		वापस saved_rc;
	पूर्ण

	pr_debug("Successfully added CPU %pOFn, drc index: %x\n", dn,
		 drc_index);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार dlpar_cpu_हटाओ(काष्ठा device_node *dn, u32 drc_index)
अणु
	पूर्णांक rc;

	pr_debug("Attempting to remove CPU %pOFn, drc index: %x\n",
		 dn, drc_index);

	rc = dlpar_offline_cpu(dn);
	अगर (rc) अणु
		pr_warn("Failed to offline CPU %pOFn, rc: %d\n", dn, rc);
		वापस -EINVAL;
	पूर्ण

	rc = dlpar_release_drc(drc_index);
	अगर (rc) अणु
		pr_warn("Failed to release drc (%x) for CPU %pOFn, rc: %d\n",
			drc_index, dn, rc);
		dlpar_online_cpu(dn);
		वापस rc;
	पूर्ण

	rc = dlpar_detach_node(dn);
	अगर (rc) अणु
		पूर्णांक saved_rc = rc;

		pr_warn("Failed to detach CPU %pOFn, rc: %d", dn, rc);

		rc = dlpar_acquire_drc(drc_index);
		अगर (!rc)
			dlpar_online_cpu(dn);

		वापस saved_rc;
	पूर्ण

	pr_debug("Successfully removed CPU, drc index: %x\n", drc_index);
	वापस 0;
पूर्ण

अटल काष्ठा device_node *cpu_drc_index_to_dn(u32 drc_index)
अणु
	काष्ठा device_node *dn;
	u32 my_index;
	पूर्णांक rc;

	क्रम_each_node_by_type(dn, "cpu") अणु
		rc = of_property_पढ़ो_u32(dn, "ibm,my-drc-index", &my_index);
		अगर (rc)
			जारी;

		अगर (my_index == drc_index)
			अवरोध;
	पूर्ण

	वापस dn;
पूर्ण

अटल पूर्णांक dlpar_cpu_हटाओ_by_index(u32 drc_index)
अणु
	काष्ठा device_node *dn;
	पूर्णांक rc;

	dn = cpu_drc_index_to_dn(drc_index);
	अगर (!dn) अणु
		pr_warn("Cannot find CPU (drc index %x) to remove\n",
			drc_index);
		वापस -ENODEV;
	पूर्ण

	rc = dlpar_cpu_हटाओ(dn, drc_index);
	of_node_put(dn);
	वापस rc;
पूर्ण

अटल पूर्णांक find_dlpar_cpus_to_हटाओ(u32 *cpu_drcs, पूर्णांक cpus_to_हटाओ)
अणु
	काष्ठा device_node *dn;
	पूर्णांक cpus_found = 0;
	पूर्णांक rc;

	/* We want to find cpus_to_हटाओ + 1 CPUs to ensure we करो not
	 * हटाओ the last CPU.
	 */
	क्रम_each_node_by_type(dn, "cpu") अणु
		cpus_found++;

		अगर (cpus_found > cpus_to_हटाओ) अणु
			of_node_put(dn);
			अवरोध;
		पूर्ण

		/* Note that cpus_found is always 1 ahead of the index
		 * पूर्णांकo the cpu_drcs array, so we use cpus_found - 1
		 */
		rc = of_property_पढ़ो_u32(dn, "ibm,my-drc-index",
					  &cpu_drcs[cpus_found - 1]);
		अगर (rc) अणु
			pr_warn("Error occurred getting drc-index for %pOFn\n",
				dn);
			of_node_put(dn);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (cpus_found < cpus_to_हटाओ) अणु
		pr_warn("Failed to find enough CPUs (%d of %d) to remove\n",
			cpus_found, cpus_to_हटाओ);
	पूर्ण अन्यथा अगर (cpus_found == cpus_to_हटाओ) अणु
		pr_warn("Cannot remove all CPUs\n");
	पूर्ण

	वापस cpus_found;
पूर्ण

अटल पूर्णांक dlpar_cpu_हटाओ_by_count(u32 cpus_to_हटाओ)
अणु
	u32 *cpu_drcs;
	पूर्णांक cpus_found;
	पूर्णांक cpus_हटाओd = 0;
	पूर्णांक i, rc;

	pr_debug("Attempting to hot-remove %d CPUs\n", cpus_to_हटाओ);

	cpu_drcs = kसुस्मृति(cpus_to_हटाओ, माप(*cpu_drcs), GFP_KERNEL);
	अगर (!cpu_drcs)
		वापस -EINVAL;

	cpus_found = find_dlpar_cpus_to_हटाओ(cpu_drcs, cpus_to_हटाओ);
	अगर (cpus_found <= cpus_to_हटाओ) अणु
		kमुक्त(cpu_drcs);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < cpus_to_हटाओ; i++) अणु
		rc = dlpar_cpu_हटाओ_by_index(cpu_drcs[i]);
		अगर (rc)
			अवरोध;

		cpus_हटाओd++;
	पूर्ण

	अगर (cpus_हटाओd != cpus_to_हटाओ) अणु
		pr_warn("CPU hot-remove failed, adding back removed CPUs\n");

		क्रम (i = 0; i < cpus_हटाओd; i++)
			dlpar_cpu_add(cpu_drcs[i]);

		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		rc = 0;
	पूर्ण

	kमुक्त(cpu_drcs);
	वापस rc;
पूर्ण

अटल पूर्णांक find_drc_info_cpus_to_add(काष्ठा device_node *cpus,
				     काष्ठा property *info,
				     u32 *cpu_drcs, u32 cpus_to_add)
अणु
	काष्ठा of_drc_info drc;
	स्थिर __be32 *value;
	u32 count, drc_index;
	पूर्णांक cpus_found = 0;
	पूर्णांक i, j;

	अगर (!info)
		वापस -1;

	value = of_prop_next_u32(info, शून्य, &count);
	अगर (value)
		value++;

	क्रम (i = 0; i < count; i++) अणु
		of_पढ़ो_drc_info_cell(&info, &value, &drc);
		अगर (म_भेदन(drc.drc_type, "CPU", 3))
			अवरोध;

		drc_index = drc.drc_index_start;
		क्रम (j = 0; j < drc.num_sequential_elems; j++) अणु
			अगर (dlpar_cpu_exists(cpus, drc_index))
				जारी;

			cpu_drcs[cpus_found++] = drc_index;

			अगर (cpus_found == cpus_to_add)
				वापस cpus_found;

			drc_index += drc.sequential_inc;
		पूर्ण
	पूर्ण

	वापस cpus_found;
पूर्ण

अटल पूर्णांक find_drc_index_cpus_to_add(काष्ठा device_node *cpus,
				      u32 *cpu_drcs, u32 cpus_to_add)
अणु
	पूर्णांक cpus_found = 0;
	पूर्णांक index, rc;
	u32 drc_index;

	/* Search the ibm,drc-indexes array क्रम possible CPU drcs to
	 * add. Note that the क्रमmat of the ibm,drc-indexes array is
	 * the number of entries in the array followed by the array
	 * of drc values so we start looking at index = 1.
	 */
	index = 1;
	जबतक (cpus_found < cpus_to_add) अणु
		rc = of_property_पढ़ो_u32_index(cpus, "ibm,drc-indexes",
						index++, &drc_index);

		अगर (rc)
			अवरोध;

		अगर (dlpar_cpu_exists(cpus, drc_index))
			जारी;

		cpu_drcs[cpus_found++] = drc_index;
	पूर्ण

	वापस cpus_found;
पूर्ण

अटल पूर्णांक dlpar_cpu_add_by_count(u32 cpus_to_add)
अणु
	काष्ठा device_node *parent;
	काष्ठा property *info;
	u32 *cpu_drcs;
	पूर्णांक cpus_added = 0;
	पूर्णांक cpus_found;
	पूर्णांक i, rc;

	pr_debug("Attempting to hot-add %d CPUs\n", cpus_to_add);

	cpu_drcs = kसुस्मृति(cpus_to_add, माप(*cpu_drcs), GFP_KERNEL);
	अगर (!cpu_drcs)
		वापस -EINVAL;

	parent = of_find_node_by_path("/cpus");
	अगर (!parent) अणु
		pr_warn("Could not find CPU root node in device tree\n");
		kमुक्त(cpu_drcs);
		वापस -1;
	पूर्ण

	info = of_find_property(parent, "ibm,drc-info", शून्य);
	अगर (info)
		cpus_found = find_drc_info_cpus_to_add(parent, info, cpu_drcs, cpus_to_add);
	अन्यथा
		cpus_found = find_drc_index_cpus_to_add(parent, cpu_drcs, cpus_to_add);

	of_node_put(parent);

	अगर (cpus_found < cpus_to_add) अणु
		pr_warn("Failed to find enough CPUs (%d of %d) to add\n",
			cpus_found, cpus_to_add);
		kमुक्त(cpu_drcs);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < cpus_to_add; i++) अणु
		rc = dlpar_cpu_add(cpu_drcs[i]);
		अगर (rc)
			अवरोध;

		cpus_added++;
	पूर्ण

	अगर (cpus_added < cpus_to_add) अणु
		pr_warn("CPU hot-add failed, removing any added CPUs\n");

		क्रम (i = 0; i < cpus_added; i++)
			dlpar_cpu_हटाओ_by_index(cpu_drcs[i]);

		rc = -EINVAL;
	पूर्ण अन्यथा अणु
		rc = 0;
	पूर्ण

	kमुक्त(cpu_drcs);
	वापस rc;
पूर्ण

पूर्णांक dlpar_cpu(काष्ठा pseries_hp_errorlog *hp_elog)
अणु
	u32 count, drc_index;
	पूर्णांक rc;

	count = hp_elog->_drc_u.drc_count;
	drc_index = hp_elog->_drc_u.drc_index;

	lock_device_hotplug();

	चयन (hp_elog->action) अणु
	हाल PSERIES_HP_ELOG_ACTION_REMOVE:
		अगर (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_COUNT)
			rc = dlpar_cpu_हटाओ_by_count(count);
		अन्यथा अगर (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_INDEX) अणु
			rc = dlpar_cpu_हटाओ_by_index(drc_index);
			/*
			 * Setting the isolation state of an UNISOLATED/CONFIGURED
			 * device to UNISOLATE is a no-op, but the hypervisor can
			 * use it as a hपूर्णांक that the CPU removal failed.
			 */
			अगर (rc)
				dlpar_unisolate_drc(drc_index);
		पूर्ण
		अन्यथा
			rc = -EINVAL;
		अवरोध;
	हाल PSERIES_HP_ELOG_ACTION_ADD:
		अगर (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_COUNT)
			rc = dlpar_cpu_add_by_count(count);
		अन्यथा अगर (hp_elog->id_type == PSERIES_HP_ELOG_ID_DRC_INDEX)
			rc = dlpar_cpu_add(drc_index);
		अन्यथा
			rc = -EINVAL;
		अवरोध;
	शेष:
		pr_err("Invalid action (%d) specified\n", hp_elog->action);
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	unlock_device_hotplug();
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_ARCH_CPU_PROBE_RELEASE

अटल sमाप_प्रकार dlpar_cpu_probe(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 drc_index;
	पूर्णांक rc;

	rc = kstrtou32(buf, 0, &drc_index);
	अगर (rc)
		वापस -EINVAL;

	rc = dlpar_cpu_add(drc_index);

	वापस rc ? rc : count;
पूर्ण

अटल sमाप_प्रकार dlpar_cpu_release(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा device_node *dn;
	u32 drc_index;
	पूर्णांक rc;

	dn = of_find_node_by_path(buf);
	अगर (!dn)
		वापस -EINVAL;

	rc = of_property_पढ़ो_u32(dn, "ibm,my-drc-index", &drc_index);
	अगर (rc) अणु
		of_node_put(dn);
		वापस -EINVAL;
	पूर्ण

	rc = dlpar_cpu_हटाओ(dn, drc_index);
	of_node_put(dn);

	वापस rc ? rc : count;
पूर्ण

#पूर्ण_अगर /* CONFIG_ARCH_CPU_PROBE_RELEASE */

अटल पूर्णांक pseries_smp_notअगरier(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा of_reconfig_data *rd = data;
	पूर्णांक err = 0;

	चयन (action) अणु
	हाल OF_RECONFIG_ATTACH_NODE:
		err = pseries_add_processor(rd->dn);
		अवरोध;
	हाल OF_RECONFIG_DETACH_NODE:
		pseries_हटाओ_processor(rd->dn);
		अवरोध;
	पूर्ण
	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल काष्ठा notअगरier_block pseries_smp_nb = अणु
	.notअगरier_call = pseries_smp_notअगरier,
पूर्ण;

अटल पूर्णांक __init pseries_cpu_hotplug_init(व्योम)
अणु
	पूर्णांक qcss_tok;

#अगर_घोषित CONFIG_ARCH_CPU_PROBE_RELEASE
	ppc_md.cpu_probe = dlpar_cpu_probe;
	ppc_md.cpu_release = dlpar_cpu_release;
#पूर्ण_अगर /* CONFIG_ARCH_CPU_PROBE_RELEASE */

	rtas_stop_self_token = rtas_token("stop-self");
	qcss_tok = rtas_token("query-cpu-stopped-state");

	अगर (rtas_stop_self_token == RTAS_UNKNOWN_SERVICE ||
			qcss_tok == RTAS_UNKNOWN_SERVICE) अणु
		prपूर्णांकk(KERN_INFO "CPU Hotplug not supported by firmware "
				"- disabling.\n");
		वापस 0;
	पूर्ण

	smp_ops->cpu_offline_self = pseries_cpu_offline_self;
	smp_ops->cpu_disable = pseries_cpu_disable;
	smp_ops->cpu_die = pseries_cpu_die;

	/* Processors can be added/हटाओd only on LPAR */
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		of_reconfig_notअगरier_रेजिस्टर(&pseries_smp_nb);

	वापस 0;
पूर्ण
machine_arch_initcall(pseries, pseries_cpu_hotplug_init);
