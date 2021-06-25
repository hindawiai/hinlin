<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Hyper-V stub IOMMU driver.
 *
 * Copyright (C) 2019, Microsoft, Inc.
 *
 * Author : Lan Tianyu <Tianyu.Lan@microsoft.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/mshyperv.h>

#समावेश "irq_remapping.h"

#अगर_घोषित CONFIG_IRQ_REMAP

/*
 * According 82093AA IO-APIC spec , IO APIC has a 24-entry Interrupt
 * Redirection Table. Hyper-V exposes one single IO-APIC and so define
 * 24 IO APIC remmapping entries.
 */
#घोषणा IOAPIC_REMAPPING_ENTRY 24

अटल cpumask_t ioapic_max_cpumask = अणु CPU_BITS_NONE पूर्ण;
अटल काष्ठा irq_करोमुख्य *ioapic_ir_करोमुख्य;

अटल पूर्णांक hyperv_ir_set_affinity(काष्ठा irq_data *data,
		स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा irq_data *parent = data->parent_data;
	काष्ठा irq_cfg *cfg = irqd_cfg(data);
	पूर्णांक ret;

	/* Return error If new irq affinity is out of ioapic_max_cpumask. */
	अगर (!cpumask_subset(mask, &ioapic_max_cpumask))
		वापस -EINVAL;

	ret = parent->chip->irq_set_affinity(parent, mask, क्रमce);
	अगर (ret < 0 || ret == IRQ_SET_MASK_OK_DONE)
		वापस ret;

	send_cleanup_vector(cfg);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip hyperv_ir_chip = अणु
	.name			= "HYPERV-IR",
	.irq_ack		= apic_ack_irq,
	.irq_set_affinity	= hyperv_ir_set_affinity,
पूर्ण;

अटल पूर्णांक hyperv_irq_remapping_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				     व्योम *arg)
अणु
	काष्ठा irq_alloc_info *info = arg;
	काष्ठा irq_data *irq_data;
	काष्ठा irq_desc *desc;
	पूर्णांक ret = 0;

	अगर (!info || info->type != X86_IRQ_ALLOC_TYPE_IOAPIC || nr_irqs > 1)
		वापस -EINVAL;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, arg);
	अगर (ret < 0)
		वापस ret;

	irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	अगर (!irq_data) अणु
		irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
		वापस -EINVAL;
	पूर्ण

	irq_data->chip = &hyperv_ir_chip;

	/*
	 * Hypver-V IO APIC irq affinity should be in the scope of
	 * ioapic_max_cpumask because no irq remapping support.
	 */
	desc = irq_data_to_desc(irq_data);
	cpumask_copy(desc->irq_common_data.affinity, &ioapic_max_cpumask);

	वापस 0;
पूर्ण

अटल व्योम hyperv_irq_remapping_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल पूर्णांक hyperv_irq_remapping_select(काष्ठा irq_करोमुख्य *d,
				       काष्ठा irq_fwspec *fwspec,
				       क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	/* Claim the only I/O APIC emulated by Hyper-V */
	वापस x86_fwspec_is_ioapic(fwspec);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops hyperv_ir_करोमुख्य_ops = अणु
	.select = hyperv_irq_remapping_select,
	.alloc = hyperv_irq_remapping_alloc,
	.मुक्त = hyperv_irq_remapping_मुक्त,
पूर्ण;

अटल स्थिर काष्ठा irq_करोमुख्य_ops hyperv_root_ir_करोमुख्य_ops;
अटल पूर्णांक __init hyperv_prepare_irq_remapping(व्योम)
अणु
	काष्ठा fwnode_handle *fn;
	पूर्णांक i;
	स्थिर अक्षर *name;
	स्थिर काष्ठा irq_करोमुख्य_ops *ops;

	अगर (!hypervisor_is_type(X86_HYPER_MS_HYPERV) ||
	    x86_init.hyper.msi_ext_dest_id() ||
	    !x2apic_supported())
		वापस -ENODEV;

	अगर (hv_root_partition) अणु
		name = "HYPERV-ROOT-IR";
		ops = &hyperv_root_ir_करोमुख्य_ops;
	पूर्ण अन्यथा अणु
		name = "HYPERV-IR";
		ops = &hyperv_ir_करोमुख्य_ops;
	पूर्ण

	fn = irq_करोमुख्य_alloc_named_id_fwnode(name, 0);
	अगर (!fn)
		वापस -ENOMEM;

	ioapic_ir_करोमुख्य =
		irq_करोमुख्य_create_hierarchy(arch_get_ir_parent_करोमुख्य(),
				0, IOAPIC_REMAPPING_ENTRY, fn, ops, शून्य);

	अगर (!ioapic_ir_करोमुख्य) अणु
		irq_करोमुख्य_मुक्त_fwnode(fn);
		वापस -ENOMEM;
	पूर्ण

	अगर (hv_root_partition)
		वापस 0; /* The rest is only relevant to guests */

	/*
	 * Hyper-V करोesn't provide irq remapping function क्रम
	 * IO-APIC and so IO-APIC only accepts 8-bit APIC ID.
	 * Cpu's APIC ID is पढ़ो from ACPI MADT table and APIC IDs
	 * in the MADT table on Hyper-v are sorted monotonic increasingly.
	 * APIC ID reflects cpu topology. There maybe some APIC ID
	 * gaps when cpu number in a socket is not घातer of two. Prepare
	 * max cpu affinity क्रम IOAPIC irqs. Scan cpu 0-255 and set cpu
	 * पूर्णांकo ioapic_max_cpumask अगर its APIC ID is less than 256.
	 */
	क्रम (i = min_t(अचिन्हित पूर्णांक, num_possible_cpus() - 1, 255); i >= 0; i--)
		अगर (cpu_physical_id(i) < 256)
			cpumask_set_cpu(i, &ioapic_max_cpumask);

	वापस 0;
पूर्ण

अटल पूर्णांक __init hyperv_enable_irq_remapping(व्योम)
अणु
	वापस IRQ_REMAP_X2APIC_MODE;
पूर्ण

काष्ठा irq_remap_ops hyperv_irq_remap_ops = अणु
	.prepare		= hyperv_prepare_irq_remapping,
	.enable			= hyperv_enable_irq_remapping,
पूर्ण;

/* IRQ remapping करोमुख्य when Linux runs as the root partition */
काष्ठा hyperv_root_ir_data अणु
	u8 ioapic_id;
	bool is_level;
	काष्ठा hv_पूर्णांकerrupt_entry entry;
पूर्ण;

अटल व्योम
hyperv_root_ir_compose_msi_msg(काष्ठा irq_data *irq_data, काष्ठा msi_msg *msg)
अणु
	u64 status;
	u32 vector;
	काष्ठा irq_cfg *cfg;
	पूर्णांक ioapic_id;
	काष्ठा cpumask *affinity;
	पूर्णांक cpu;
	काष्ठा hv_पूर्णांकerrupt_entry entry;
	काष्ठा hyperv_root_ir_data *data = irq_data->chip_data;
	काष्ठा IO_APIC_route_entry e;

	cfg = irqd_cfg(irq_data);
	affinity = irq_data_get_effective_affinity_mask(irq_data);
	cpu = cpumask_first_and(affinity, cpu_online_mask);

	vector = cfg->vector;
	ioapic_id = data->ioapic_id;

	अगर (data->entry.source == HV_DEVICE_TYPE_IOAPIC
	    && data->entry.ioapic_rte.as_uपूर्णांक64) अणु
		entry = data->entry;

		status = hv_unmap_ioapic_पूर्णांकerrupt(ioapic_id, &entry);

		अगर (status != HV_STATUS_SUCCESS)
			pr_debug("%s: unexpected unmap status %lld\n", __func__, status);

		data->entry.ioapic_rte.as_uपूर्णांक64 = 0;
		data->entry.source = 0; /* Invalid source */
	पूर्ण


	status = hv_map_ioapic_पूर्णांकerrupt(ioapic_id, data->is_level, cpu,
					vector, &entry);

	अगर (status != HV_STATUS_SUCCESS) अणु
		pr_err("%s: map hypercall failed, status %lld\n", __func__, status);
		वापस;
	पूर्ण

	data->entry = entry;

	/* Turn it पूर्णांकo an IO_APIC_route_entry, and generate MSI MSG. */
	e.w1 = entry.ioapic_rte.low_uपूर्णांक32;
	e.w2 = entry.ioapic_rte.high_uपूर्णांक32;

	स_रखो(msg, 0, माप(*msg));
	msg->arch_data.vector = e.vector;
	msg->arch_data.delivery_mode = e.delivery_mode;
	msg->arch_addr_lo.dest_mode_logical = e.dest_mode_logical;
	msg->arch_addr_lo.dmar_क्रमmat = e.ir_क्रमmat;
	msg->arch_addr_lo.dmar_index_0_14 = e.ir_index_0_14;
पूर्ण

अटल पूर्णांक hyperv_root_ir_set_affinity(काष्ठा irq_data *data,
		स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा irq_data *parent = data->parent_data;
	काष्ठा irq_cfg *cfg = irqd_cfg(data);
	पूर्णांक ret;

	ret = parent->chip->irq_set_affinity(parent, mask, क्रमce);
	अगर (ret < 0 || ret == IRQ_SET_MASK_OK_DONE)
		वापस ret;

	send_cleanup_vector(cfg);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip hyperv_root_ir_chip = अणु
	.name			= "HYPERV-ROOT-IR",
	.irq_ack		= apic_ack_irq,
	.irq_set_affinity	= hyperv_root_ir_set_affinity,
	.irq_compose_msi_msg	= hyperv_root_ir_compose_msi_msg,
पूर्ण;

अटल पूर्णांक hyperv_root_irq_remapping_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				     व्योम *arg)
अणु
	काष्ठा irq_alloc_info *info = arg;
	काष्ठा irq_data *irq_data;
	काष्ठा hyperv_root_ir_data *data;
	पूर्णांक ret = 0;

	अगर (!info || info->type != X86_IRQ_ALLOC_TYPE_IOAPIC || nr_irqs > 1)
		वापस -EINVAL;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, arg);
	अगर (ret < 0)
		वापस ret;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
		वापस -ENOMEM;
	पूर्ण

	irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	अगर (!irq_data) अणु
		kमुक्त(data);
		irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
		वापस -EINVAL;
	पूर्ण

	data->ioapic_id = info->devid;
	data->is_level = info->ioapic.is_level;

	irq_data->chip = &hyperv_root_ir_chip;
	irq_data->chip_data = data;

	वापस 0;
पूर्ण

अटल व्योम hyperv_root_irq_remapping_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irq_data;
	काष्ठा hyperv_root_ir_data *data;
	काष्ठा hv_पूर्णांकerrupt_entry *e;
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);

		अगर (irq_data && irq_data->chip_data) अणु
			data = irq_data->chip_data;
			e = &data->entry;

			अगर (e->source == HV_DEVICE_TYPE_IOAPIC
			      && e->ioapic_rte.as_uपूर्णांक64)
				hv_unmap_ioapic_पूर्णांकerrupt(data->ioapic_id,
							&data->entry);

			kमुक्त(data);
		पूर्ण
	पूर्ण

	irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops hyperv_root_ir_करोमुख्य_ops = अणु
	.select = hyperv_irq_remapping_select,
	.alloc = hyperv_root_irq_remapping_alloc,
	.मुक्त = hyperv_root_irq_remapping_मुक्त,
पूर्ण;

#पूर्ण_अगर
