<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 IBM Corporation.
 */
#समावेश <linux/types.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/firmware.h>

/* Globals common to all ICP/ICS implementations */
स्थिर काष्ठा icp_ops	*icp_ops;

अचिन्हित पूर्णांक xics_शेष_server		= 0xff;
अचिन्हित पूर्णांक xics_शेष_distrib_server	= 0;
अचिन्हित पूर्णांक xics_पूर्णांकerrupt_server_size		= 8;

DEFINE_PER_CPU(काष्ठा xics_cppr, xics_cppr);

काष्ठा irq_करोमुख्य *xics_host;

अटल LIST_HEAD(ics_list);

व्योम xics_update_irq_servers(व्योम)
अणु
	पूर्णांक i, j;
	काष्ठा device_node *np;
	u32 ilen;
	स्थिर __be32 *ireg;
	u32 hcpuid;

	/* Find the server numbers क्रम the boot cpu. */
	np = of_get_cpu_node(boot_cpuid, शून्य);
	BUG_ON(!np);

	hcpuid = get_hard_smp_processor_id(boot_cpuid);
	xics_शेष_server = xics_शेष_distrib_server = hcpuid;

	pr_devel("xics: xics_default_server = 0x%x\n", xics_शेष_server);

	ireg = of_get_property(np, "ibm,ppc-interrupt-gserver#s", &ilen);
	अगर (!ireg) अणु
		of_node_put(np);
		वापस;
	पूर्ण

	i = ilen / माप(पूर्णांक);

	/* Global पूर्णांकerrupt distribution server is specअगरied in the last
	 * entry of "ibm,ppc-interrupt-gserver#s" property. Get the last
	 * entry fom this property क्रम current boot cpu id and use it as
	 * शेष distribution server
	 */
	क्रम (j = 0; j < i; j += 2) अणु
		अगर (be32_to_cpu(ireg[j]) == hcpuid) अणु
			xics_शेष_distrib_server = be32_to_cpu(ireg[j+1]);
			अवरोध;
		पूर्ण
	पूर्ण
	pr_devel("xics: xics_default_distrib_server = 0x%x\n",
		 xics_शेष_distrib_server);
	of_node_put(np);
पूर्ण

/* GIQ stuff, currently only supported on RTAS setups, will have
 * to be sorted properly क्रम bare metal
 */
व्योम xics_set_cpu_giq(अचिन्हित पूर्णांक gserver, अचिन्हित पूर्णांक join)
अणु
#अगर_घोषित CONFIG_PPC_RTAS
	पूर्णांक index;
	पूर्णांक status;

	अगर (!rtas_indicator_present(GLOBAL_INTERRUPT_QUEUE, शून्य))
		वापस;

	index = (1UL << xics_पूर्णांकerrupt_server_size) - 1 - gserver;

	status = rtas_set_indicator_fast(GLOBAL_INTERRUPT_QUEUE, index, join);

	WARN(status < 0, "set-indicator(%d, %d, %u) returned %d\n",
	     GLOBAL_INTERRUPT_QUEUE, index, join, status);
#पूर्ण_अगर
पूर्ण

व्योम xics_setup_cpu(व्योम)
अणु
	icp_ops->set_priority(LOWEST_PRIORITY);

	xics_set_cpu_giq(xics_शेष_distrib_server, 1);
पूर्ण

व्योम xics_mask_unknown_vec(अचिन्हित पूर्णांक vec)
अणु
	काष्ठा ics *ics;

	pr_err("Interrupt 0x%x (real) is invalid, disabling it.\n", vec);

	list_क्रम_each_entry(ics, &ics_list, link)
		ics->mask_unknown(ics, vec);
पूर्ण


#अगर_घोषित CONFIG_SMP

अटल व्योम xics_request_ipi(व्योम)
अणु
	अचिन्हित पूर्णांक ipi;

	ipi = irq_create_mapping(xics_host, XICS_IPI);
	BUG_ON(!ipi);

	/*
	 * IPIs are marked IRQF_PERCPU. The handler was set in map.
	 */
	BUG_ON(request_irq(ipi, icp_ops->ipi_action,
			   IRQF_PERCPU | IRQF_NO_THREAD, "IPI", शून्य));
पूर्ण

व्योम __init xics_smp_probe(व्योम)
अणु
	/* Register all the IPIs */
	xics_request_ipi();

	/* Setup cause_ipi callback based on which ICP is used */
	smp_ops->cause_ipi = icp_ops->cause_ipi;
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

व्योम xics_tearकरोwn_cpu(व्योम)
अणु
	काष्ठा xics_cppr *os_cppr = this_cpu_ptr(&xics_cppr);

	/*
	 * we have to reset the cppr index to 0 because we're
	 * not going to वापस from the IPI
	 */
	os_cppr->index = 0;
	icp_ops->set_priority(0);
	icp_ops->tearकरोwn_cpu();
पूर्ण

व्योम xics_kexec_tearकरोwn_cpu(पूर्णांक secondary)
अणु
	xics_tearकरोwn_cpu();

	icp_ops->flush_ipi();

	/*
	 * Some machines need to have at least one cpu in the GIQ,
	 * so leave the master cpu in the group.
	 */
	अगर (secondary)
		xics_set_cpu_giq(xics_शेष_distrib_server, 0);
पूर्ण


#अगर_घोषित CONFIG_HOTPLUG_CPU

/* Interrupts are disabled. */
व्योम xics_migrate_irqs_away(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id(), hw_cpu = hard_smp_processor_id();
	अचिन्हित पूर्णांक irq, virq;
	काष्ठा irq_desc *desc;

	/* If we used to be the शेष server, move to the new "boot_cpuid" */
	अगर (hw_cpu == xics_शेष_server)
		xics_update_irq_servers();

	/* Reject any पूर्णांकerrupt that was queued to us... */
	icp_ops->set_priority(0);

	/* Remove ourselves from the global पूर्णांकerrupt queue */
	xics_set_cpu_giq(xics_शेष_distrib_server, 0);

	क्रम_each_irq_desc(virq, desc) अणु
		काष्ठा irq_chip *chip;
		दीर्घ server;
		अचिन्हित दीर्घ flags;
		काष्ठा ics *ics;

		/* We can't set affinity on ISA पूर्णांकerrupts */
		अगर (virq < NUM_ISA_INTERRUPTS)
			जारी;
		/* We only need to migrate enabled IRQS */
		अगर (!desc->action)
			जारी;
		अगर (desc->irq_data.करोमुख्य != xics_host)
			जारी;
		irq = desc->irq_data.hwirq;
		/* We need to get IPIs still. */
		अगर (irq == XICS_IPI || irq == XICS_IRQ_SPURIOUS)
			जारी;
		chip = irq_desc_get_chip(desc);
		अगर (!chip || !chip->irq_set_affinity)
			जारी;

		raw_spin_lock_irqsave(&desc->lock, flags);

		/* Locate पूर्णांकerrupt server */
		server = -1;
		ics = irq_desc_get_chip_data(desc);
		अगर (ics)
			server = ics->get_server(ics, irq);
		अगर (server < 0) अणु
			prपूर्णांकk(KERN_ERR "%s: Can't find server for irq %d\n",
			       __func__, irq);
			जाओ unlock;
		पूर्ण

		/* We only support delivery to all cpus or to one cpu.
		 * The irq has to be migrated only in the single cpu
		 * हाल.
		 */
		अगर (server != hw_cpu)
			जाओ unlock;

		/* This is expected during cpu offline. */
		अगर (cpu_online(cpu))
			pr_warn("IRQ %u affinity broken off cpu %u\n",
				virq, cpu);

		/* Reset affinity to all cpus */
		raw_spin_unlock_irqrestore(&desc->lock, flags);
		irq_set_affinity(virq, cpu_all_mask);
		जारी;
unlock:
		raw_spin_unlock_irqrestore(&desc->lock, flags);
	पूर्ण

	/* Allow "sufficient" समय to drop any inflight IRQ's */
	mdelay(5);

	/*
	 * Allow IPIs again. This is करोne at the very end, after migrating all
	 * पूर्णांकerrupts, the expectation is that we'll only get woken up by an IPI
	 * पूर्णांकerrupt beyond this poपूर्णांक, but leave बाह्यals masked just to be
	 * safe. If we're using icp-opal this may actually allow all
	 * पूर्णांकerrupts anyway, but that should be OK.
	 */
	icp_ops->set_priority(DEFAULT_PRIORITY);

पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

#अगर_घोषित CONFIG_SMP
/*
 * For the moment we only implement delivery to all cpus or one cpu.
 *
 * If the requested affinity is cpu_all_mask, we set global affinity.
 * If not we set it to the first cpu in the mask, even अगर multiple cpus
 * are set. This is so things like irqbalance (which set core and package
 * wide affinities) करो the right thing.
 *
 * We need to fix this to implement support क्रम the links
 */
पूर्णांक xics_get_irq_server(अचिन्हित पूर्णांक virq, स्थिर काष्ठा cpumask *cpumask,
			अचिन्हित पूर्णांक strict_check)
अणु

	अगर (!distribute_irqs)
		वापस xics_शेष_server;

	अगर (!cpumask_subset(cpu_possible_mask, cpumask)) अणु
		पूर्णांक server = cpumask_first_and(cpu_online_mask, cpumask);

		अगर (server < nr_cpu_ids)
			वापस get_hard_smp_processor_id(server);

		अगर (strict_check)
			वापस -1;
	पूर्ण

	/*
	 * Workaround issue with some versions of JS20 firmware that
	 * deliver पूर्णांकerrupts to cpus which haven't been started. This
	 * happens when using the maxcpus= boot option.
	 */
	अगर (cpumask_equal(cpu_online_mask, cpu_present_mask))
		वापस xics_शेष_distrib_server;

	वापस xics_शेष_server;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल पूर्णांक xics_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
			   क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	काष्ठा ics *ics;

	list_क्रम_each_entry(ics, &ics_list, link)
		अगर (ics->host_match(ics, node))
			वापस 1;

	वापस 0;
पूर्ण

/* Dummies */
अटल व्योम xics_ipi_unmask(काष्ठा irq_data *d) अणु पूर्ण
अटल व्योम xics_ipi_mask(काष्ठा irq_data *d) अणु पूर्ण

अटल काष्ठा irq_chip xics_ipi_chip = अणु
	.name = "XICS",
	.irq_eoi = शून्य, /* Patched at init समय */
	.irq_mask = xics_ipi_mask,
	.irq_unmask = xics_ipi_unmask,
पूर्ण;

अटल पूर्णांक xics_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw)
अणु
	काष्ठा ics *ics;

	pr_devel("xics: map virq %d, hwirq 0x%lx\n", virq, hw);

	/*
	 * Mark पूर्णांकerrupts as edge sensitive by शेष so that resend
	 * actually works. The device-tree parsing will turn the LSIs
	 * back to level.
	 */
	irq_clear_status_flags(virq, IRQ_LEVEL);

	/* Don't call पूर्णांकo ICS क्रम IPIs */
	अगर (hw == XICS_IPI) अणु
		irq_set_chip_and_handler(virq, &xics_ipi_chip,
					 handle_percpu_irq);
		वापस 0;
	पूर्ण

	/* Let the ICS setup the chip data */
	list_क्रम_each_entry(ics, &ics_list, link)
		अगर (ics->map(ics, virq) == 0)
			वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक xics_host_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
			   स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			   irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)

अणु
	*out_hwirq = पूर्णांकspec[0];

	/*
	 * If पूर्णांकsize is at least 2, we look क्रम the type in the second cell,
	 * we assume the LSB indicates a level पूर्णांकerrupt.
	 */
	अगर (पूर्णांकsize > 1) अणु
		अगर (पूर्णांकspec[1] & 1)
			*out_flags = IRQ_TYPE_LEVEL_LOW;
		अन्यथा
			*out_flags = IRQ_TYPE_EDGE_RISING;
	पूर्ण अन्यथा
		*out_flags = IRQ_TYPE_LEVEL_LOW;

	वापस 0;
पूर्ण

पूर्णांक xics_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	/*
	 * We only support these. This has really no effect other than setting
	 * the corresponding descriptor bits mind you but those will in turn
	 * affect the resend function when re-enabling an edge पूर्णांकerrupt.
	 *
	 * Set set the शेष to edge as explained in map().
	 */
	अगर (flow_type == IRQ_TYPE_DEFAULT || flow_type == IRQ_TYPE_NONE)
		flow_type = IRQ_TYPE_EDGE_RISING;

	अगर (flow_type != IRQ_TYPE_EDGE_RISING &&
	    flow_type != IRQ_TYPE_LEVEL_LOW)
		वापस -EINVAL;

	irqd_set_trigger_type(d, flow_type);

	वापस IRQ_SET_MASK_OK_NOCOPY;
पूर्ण

पूर्णांक xics_retrigger(काष्ठा irq_data *data)
अणु
	/*
	 * We need to push a dummy CPPR when retriggering, since the subsequent
	 * EOI will try to pop it. Passing 0 works, as the function hard codes
	 * the priority value anyway.
	 */
	xics_push_cppr(0);

	/* Tell the core to करो a soft retrigger */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops xics_host_ops = अणु
	.match = xics_host_match,
	.map = xics_host_map,
	.xlate = xics_host_xlate,
पूर्ण;

अटल व्योम __init xics_init_host(व्योम)
अणु
	xics_host = irq_करोमुख्य_add_tree(शून्य, &xics_host_ops, शून्य);
	BUG_ON(xics_host == शून्य);
	irq_set_शेष_host(xics_host);
पूर्ण

व्योम __init xics_रेजिस्टर_ics(काष्ठा ics *ics)
अणु
	list_add(&ics->link, &ics_list);
पूर्ण

अटल व्योम __init xics_get_server_size(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर __be32 *isize;

	/* We fetch the पूर्णांकerrupt server size from the first ICS node
	 * we find अगर any
	 */
	np = of_find_compatible_node(शून्य, शून्य, "ibm,ppc-xics");
	अगर (!np)
		वापस;

	isize = of_get_property(np, "ibm,interrupt-server#-size", शून्य);
	अगर (isize)
		xics_पूर्णांकerrupt_server_size = be32_to_cpu(*isize);

	of_node_put(np);
पूर्ण

व्योम __init xics_init(व्योम)
अणु
	पूर्णांक rc = -1;

	/* Fist locate ICP */
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		rc = icp_hv_init();
	अगर (rc < 0) अणु
		rc = icp_native_init();
		अगर (rc == -ENODEV)
		    rc = icp_opal_init();
	पूर्ण
	अगर (rc < 0) अणु
		pr_warn("XICS: Cannot find a Presentation Controller !\n");
		वापस;
	पूर्ण

	/* Copy get_irq callback over to ppc_md */
	ppc_md.get_irq = icp_ops->get_irq;

	/* Patch up IPI chip EOI */
	xics_ipi_chip.irq_eoi = icp_ops->eoi;

	/* Now locate ICS */
	rc = ics_rtas_init();
	अगर (rc < 0)
		rc = ics_opal_init();
	अगर (rc < 0)
		pr_warn("XICS: Cannot find a Source Controller !\n");

	/* Initialize common bits */
	xics_get_server_size();
	xics_update_irq_servers();
	xics_init_host();
	xics_setup_cpu();
पूर्ण
