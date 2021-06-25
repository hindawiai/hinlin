<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/apic.h>

#समावेश "local.h"

काष्ठा cluster_mask अणु
	अचिन्हित पूर्णांक	clusterid;
	पूर्णांक		node;
	काष्ठा cpumask	mask;
पूर्ण;

अटल DEFINE_PER_CPU(u32, x86_cpu_to_logical_apicid);
अटल DEFINE_PER_CPU(cpumask_var_t, ipi_mask);
अटल DEFINE_PER_CPU(काष्ठा cluster_mask *, cluster_masks);
अटल काष्ठा cluster_mask *cluster_hotplug_mask;

अटल पूर्णांक x2apic_acpi_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
	वापस x2apic_enabled();
पूर्ण

अटल व्योम x2apic_send_IPI(पूर्णांक cpu, पूर्णांक vector)
अणु
	u32 dest = per_cpu(x86_cpu_to_logical_apicid, cpu);

	/* x2apic MSRs are special and need a special fence: */
	weak_wrmsr_fence();
	__x2apic_send_IPI_dest(dest, vector, APIC_DEST_LOGICAL);
पूर्ण

अटल व्योम
__x2apic_send_IPI_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector, पूर्णांक apic_dest)
अणु
	अचिन्हित पूर्णांक cpu, clustercpu;
	काष्ठा cpumask *पंचांगpmsk;
	अचिन्हित दीर्घ flags;
	u32 dest;

	/* x2apic MSRs are special and need a special fence: */
	weak_wrmsr_fence();
	local_irq_save(flags);

	पंचांगpmsk = this_cpu_cpumask_var_ptr(ipi_mask);
	cpumask_copy(पंचांगpmsk, mask);
	/* If IPI should not be sent to self, clear current CPU */
	अगर (apic_dest != APIC_DEST_ALLINC)
		__cpumask_clear_cpu(smp_processor_id(), पंचांगpmsk);

	/* Collapse cpus in a cluster so a single IPI per cluster is sent */
	क्रम_each_cpu(cpu, पंचांगpmsk) अणु
		काष्ठा cluster_mask *cmsk = per_cpu(cluster_masks, cpu);

		dest = 0;
		क्रम_each_cpu_and(clustercpu, पंचांगpmsk, &cmsk->mask)
			dest |= per_cpu(x86_cpu_to_logical_apicid, clustercpu);

		अगर (!dest)
			जारी;

		__x2apic_send_IPI_dest(dest, vector, APIC_DEST_LOGICAL);
		/* Remove cluster CPUs from पंचांगpmask */
		cpumask_andnot(पंचांगpmsk, पंचांगpmsk, &cmsk->mask);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल व्योम x2apic_send_IPI_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	__x2apic_send_IPI_mask(mask, vector, APIC_DEST_ALLINC);
पूर्ण

अटल व्योम
x2apic_send_IPI_mask_allbutself(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	__x2apic_send_IPI_mask(mask, vector, APIC_DEST_ALLBUT);
पूर्ण

अटल व्योम x2apic_send_IPI_allbutself(पूर्णांक vector)
अणु
	__x2apic_send_IPI_लघुhand(vector, APIC_DEST_ALLBUT);
पूर्ण

अटल व्योम x2apic_send_IPI_all(पूर्णांक vector)
अणु
	__x2apic_send_IPI_लघुhand(vector, APIC_DEST_ALLINC);
पूर्ण

अटल u32 x2apic_calc_apicid(अचिन्हित पूर्णांक cpu)
अणु
	वापस per_cpu(x86_cpu_to_logical_apicid, cpu);
पूर्ण

अटल व्योम init_x2apic_ldr(व्योम)
अणु
	काष्ठा cluster_mask *cmsk = this_cpu_पढ़ो(cluster_masks);
	u32 cluster, apicid = apic_पढ़ो(APIC_LDR);
	अचिन्हित पूर्णांक cpu;

	this_cpu_ग_लिखो(x86_cpu_to_logical_apicid, apicid);

	अगर (cmsk)
		जाओ update;

	cluster = apicid >> 16;
	क्रम_each_online_cpu(cpu) अणु
		cmsk = per_cpu(cluster_masks, cpu);
		/* Matching cluster found. Link and update it. */
		अगर (cmsk && cmsk->clusterid == cluster)
			जाओ update;
	पूर्ण
	cmsk = cluster_hotplug_mask;
	cmsk->clusterid = cluster;
	cluster_hotplug_mask = शून्य;
update:
	this_cpu_ग_लिखो(cluster_masks, cmsk);
	cpumask_set_cpu(smp_processor_id(), &cmsk->mask);
पूर्ण

अटल पूर्णांक alloc_clustermask(अचिन्हित पूर्णांक cpu, पूर्णांक node)
अणु
	अगर (per_cpu(cluster_masks, cpu))
		वापस 0;
	/*
	 * If a hotplug spare mask exists, check whether it's on the right
	 * node. If not, मुक्त it and allocate a new one.
	 */
	अगर (cluster_hotplug_mask) अणु
		अगर (cluster_hotplug_mask->node == node)
			वापस 0;
		kमुक्त(cluster_hotplug_mask);
	पूर्ण

	cluster_hotplug_mask = kzalloc_node(माप(*cluster_hotplug_mask),
					    GFP_KERNEL, node);
	अगर (!cluster_hotplug_mask)
		वापस -ENOMEM;
	cluster_hotplug_mask->node = node;
	वापस 0;
पूर्ण

अटल पूर्णांक x2apic_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (alloc_clustermask(cpu, cpu_to_node(cpu)) < 0)
		वापस -ENOMEM;
	अगर (!zalloc_cpumask_var(&per_cpu(ipi_mask, cpu), GFP_KERNEL))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक x2apic_dead_cpu(अचिन्हित पूर्णांक dead_cpu)
अणु
	काष्ठा cluster_mask *cmsk = per_cpu(cluster_masks, dead_cpu);

	अगर (cmsk)
		cpumask_clear_cpu(dead_cpu, &cmsk->mask);
	मुक्त_cpumask_var(per_cpu(ipi_mask, dead_cpu));
	वापस 0;
पूर्ण

अटल पूर्णांक x2apic_cluster_probe(व्योम)
अणु
	अगर (!x2apic_mode)
		वापस 0;

	अगर (cpuhp_setup_state(CPUHP_X2APIC_PREPARE, "x86/x2apic:prepare",
			      x2apic_prepare_cpu, x2apic_dead_cpu) < 0) अणु
		pr_err("Failed to register X2APIC_PREPARE\n");
		वापस 0;
	पूर्ण
	init_x2apic_ldr();
	वापस 1;
पूर्ण

अटल काष्ठा apic apic_x2apic_cluster __ro_after_init = अणु

	.name				= "cluster x2apic",
	.probe				= x2apic_cluster_probe,
	.acpi_madt_oem_check		= x2apic_acpi_madt_oem_check,
	.apic_id_valid			= x2apic_apic_id_valid,
	.apic_id_रेजिस्टरed		= x2apic_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= true,

	.disable_esr			= 0,

	.check_apicid_used		= शून्य,
	.init_apic_ldr			= init_x2apic_ldr,
	.ioapic_phys_id_map		= शून्य,
	.setup_apic_routing		= शून्य,
	.cpu_present_to_apicid		= शेष_cpu_present_to_apicid,
	.apicid_to_cpu_present		= शून्य,
	.check_phys_apicid_present	= शेष_check_phys_apicid_present,
	.phys_pkg_id			= x2apic_phys_pkg_id,

	.get_apic_id			= x2apic_get_apic_id,
	.set_apic_id			= x2apic_set_apic_id,

	.calc_dest_apicid		= x2apic_calc_apicid,

	.send_IPI			= x2apic_send_IPI,
	.send_IPI_mask			= x2apic_send_IPI_mask,
	.send_IPI_mask_allbutself	= x2apic_send_IPI_mask_allbutself,
	.send_IPI_allbutself		= x2apic_send_IPI_allbutself,
	.send_IPI_all			= x2apic_send_IPI_all,
	.send_IPI_self			= x2apic_send_IPI_self,

	.inquire_remote_apic		= शून्य,

	.पढ़ो				= native_apic_msr_पढ़ो,
	.ग_लिखो				= native_apic_msr_ग_लिखो,
	.eoi_ग_लिखो			= native_apic_msr_eoi_ग_लिखो,
	.icr_पढ़ो			= native_x2apic_icr_पढ़ो,
	.icr_ग_लिखो			= native_x2apic_icr_ग_लिखो,
	.रुको_icr_idle			= native_x2apic_रुको_icr_idle,
	.safe_रुको_icr_idle		= native_safe_x2apic_रुको_icr_idle,
पूर्ण;

apic_driver(apic_x2apic_cluster);
