<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Irqकरोमुख्य क्रम Linux to run as the root partition on Microsoft Hypervisor.
 *
 * Authors:
 *  Sunil Muthuswamy <sunilmut@microsoft.com>
 *  Wei Liu <wei.liu@kernel.org>
 */

#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mshyperv.h>

अटल पूर्णांक hv_map_पूर्णांकerrupt(जोड़ hv_device_id device_id, bool level,
		पूर्णांक cpu, पूर्णांक vector, काष्ठा hv_पूर्णांकerrupt_entry *entry)
अणु
	काष्ठा hv_input_map_device_पूर्णांकerrupt *input;
	काष्ठा hv_output_map_device_पूर्णांकerrupt *output;
	काष्ठा hv_device_पूर्णांकerrupt_descriptor *पूर्णांकr_desc;
	अचिन्हित दीर्घ flags;
	u64 status;
	पूर्णांक nr_bank, var_size;

	local_irq_save(flags);

	input = *this_cpu_ptr(hyperv_pcpu_input_arg);
	output = *this_cpu_ptr(hyperv_pcpu_output_arg);

	पूर्णांकr_desc = &input->पूर्णांकerrupt_descriptor;
	स_रखो(input, 0, माप(*input));
	input->partition_id = hv_current_partition_id;
	input->device_id = device_id.as_uपूर्णांक64;
	पूर्णांकr_desc->पूर्णांकerrupt_type = HV_X64_INTERRUPT_TYPE_FIXED;
	पूर्णांकr_desc->vector_count = 1;
	पूर्णांकr_desc->target.vector = vector;

	अगर (level)
		पूर्णांकr_desc->trigger_mode = HV_INTERRUPT_TRIGGER_MODE_LEVEL;
	अन्यथा
		पूर्णांकr_desc->trigger_mode = HV_INTERRUPT_TRIGGER_MODE_EDGE;

	पूर्णांकr_desc->target.vp_set.valid_bank_mask = 0;
	पूर्णांकr_desc->target.vp_set.क्रमmat = HV_GENERIC_SET_SPARSE_4K;
	nr_bank = cpumask_to_vpset(&(पूर्णांकr_desc->target.vp_set), cpumask_of(cpu));
	अगर (nr_bank < 0) अणु
		local_irq_restore(flags);
		pr_err("%s: unable to generate VP set\n", __func__);
		वापस EINVAL;
	पूर्ण
	पूर्णांकr_desc->target.flags = HV_DEVICE_INTERRUPT_TARGET_PROCESSOR_SET;

	/*
	 * var-sized hypercall, var-size starts after vp_mask (thus
	 * vp_set.क्रमmat करोes not count, but vp_set.valid_bank_mask
	 * करोes).
	 */
	var_size = nr_bank + 1;

	status = hv_करो_rep_hypercall(HVCALL_MAP_DEVICE_INTERRUPT, 0, var_size,
			input, output);
	*entry = output->पूर्णांकerrupt_entry;

	local_irq_restore(flags);

	अगर (!hv_result_success(status))
		pr_err("%s: hypercall failed, status %lld\n", __func__, status);

	वापस hv_result(status);
पूर्ण

अटल पूर्णांक hv_unmap_पूर्णांकerrupt(u64 id, काष्ठा hv_पूर्णांकerrupt_entry *old_entry)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hv_input_unmap_device_पूर्णांकerrupt *input;
	काष्ठा hv_पूर्णांकerrupt_entry *पूर्णांकr_entry;
	u64 status;

	local_irq_save(flags);
	input = *this_cpu_ptr(hyperv_pcpu_input_arg);

	स_रखो(input, 0, माप(*input));
	पूर्णांकr_entry = &input->पूर्णांकerrupt_entry;
	input->partition_id = hv_current_partition_id;
	input->device_id = id;
	*पूर्णांकr_entry = *old_entry;

	status = hv_करो_hypercall(HVCALL_UNMAP_DEVICE_INTERRUPT, input, शून्य);
	local_irq_restore(flags);

	वापस hv_result(status);
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
काष्ठा rid_data अणु
	काष्ठा pci_dev *bridge;
	u32 rid;
पूर्ण;

अटल पूर्णांक get_rid_cb(काष्ठा pci_dev *pdev, u16 alias, व्योम *data)
अणु
	काष्ठा rid_data *rd = data;
	u8 bus = PCI_BUS_NUM(rd->rid);

	अगर (pdev->bus->number != bus || PCI_BUS_NUM(alias) != bus) अणु
		rd->bridge = pdev;
		rd->rid = alias;
	पूर्ण

	वापस 0;
पूर्ण

अटल जोड़ hv_device_id hv_build_pci_dev_id(काष्ठा pci_dev *dev)
अणु
	जोड़ hv_device_id dev_id;
	काष्ठा rid_data data = अणु
		.bridge = शून्य,
		.rid = PCI_DEVID(dev->bus->number, dev->devfn)
	पूर्ण;

	pci_क्रम_each_dma_alias(dev, get_rid_cb, &data);

	dev_id.as_uपूर्णांक64 = 0;
	dev_id.device_type = HV_DEVICE_TYPE_PCI;
	dev_id.pci.segment = pci_करोमुख्य_nr(dev->bus);

	dev_id.pci.bdf.bus = PCI_BUS_NUM(data.rid);
	dev_id.pci.bdf.device = PCI_SLOT(data.rid);
	dev_id.pci.bdf.function = PCI_FUNC(data.rid);
	dev_id.pci.source_shaकरोw = HV_SOURCE_SHADOW_NONE;

	अगर (data.bridge) अणु
		पूर्णांक pos;

		/*
		 * Microsoft Hypervisor requires a bus range when the bridge is
		 * running in PCI-X mode.
		 *
		 * To distinguish conventional vs PCI-X bridge, we can check
		 * the bridge's PCI-X Secondary Status Register, Secondary Bus
		 * Mode and Frequency bits. See PCI Express to PCI/PCI-X Bridge
		 * Specअगरication Revision 1.0 5.2.2.1.3.
		 *
		 * Value zero means it is in conventional mode, otherwise it is
		 * in PCI-X mode.
		 */

		pos = pci_find_capability(data.bridge, PCI_CAP_ID_PCIX);
		अगर (pos) अणु
			u16 status;

			pci_पढ़ो_config_word(data.bridge, pos +
					PCI_X_BRIDGE_SSTATUS, &status);

			अगर (status & PCI_X_SSTATUS_FREQ) अणु
				/* Non-zero, PCI-X mode */
				u8 sec_bus, sub_bus;

				dev_id.pci.source_shaकरोw = HV_SOURCE_SHADOW_BRIDGE_BUS_RANGE;

				pci_पढ़ो_config_byte(data.bridge, PCI_SECONDARY_BUS, &sec_bus);
				dev_id.pci.shaकरोw_bus_range.secondary_bus = sec_bus;
				pci_पढ़ो_config_byte(data.bridge, PCI_SUBORDINATE_BUS, &sub_bus);
				dev_id.pci.shaकरोw_bus_range.subordinate_bus = sub_bus;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस dev_id;
पूर्ण

अटल पूर्णांक hv_map_msi_पूर्णांकerrupt(काष्ठा pci_dev *dev, पूर्णांक cpu, पूर्णांक vector,
				काष्ठा hv_पूर्णांकerrupt_entry *entry)
अणु
	जोड़ hv_device_id device_id = hv_build_pci_dev_id(dev);

	वापस hv_map_पूर्णांकerrupt(device_id, false, cpu, vector, entry);
पूर्ण

अटल अंतरभूत व्योम entry_to_msi_msg(काष्ठा hv_पूर्णांकerrupt_entry *entry, काष्ठा msi_msg *msg)
अणु
	/* High address is always 0 */
	msg->address_hi = 0;
	msg->address_lo = entry->msi_entry.address.as_uपूर्णांक32;
	msg->data = entry->msi_entry.data.as_uपूर्णांक32;
पूर्ण

अटल पूर्णांक hv_unmap_msi_पूर्णांकerrupt(काष्ठा pci_dev *dev, काष्ठा hv_पूर्णांकerrupt_entry *old_entry);
अटल व्योम hv_irq_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा msi_desc *msidesc;
	काष्ठा pci_dev *dev;
	काष्ठा hv_पूर्णांकerrupt_entry out_entry, *stored_entry;
	काष्ठा irq_cfg *cfg = irqd_cfg(data);
	cpumask_t *affinity;
	पूर्णांक cpu;
	u64 status;

	msidesc = irq_data_get_msi_desc(data);
	dev = msi_desc_to_pci_dev(msidesc);

	अगर (!cfg) अणु
		pr_debug("%s: cfg is NULL", __func__);
		वापस;
	पूर्ण

	affinity = irq_data_get_effective_affinity_mask(data);
	cpu = cpumask_first_and(affinity, cpu_online_mask);

	अगर (data->chip_data) अणु
		/*
		 * This पूर्णांकerrupt is alपढ़ोy mapped. Let's unmap first.
		 *
		 * We करोn't use retarget पूर्णांकerrupt hypercalls here because
		 * Microsoft Hypervisor करोens't allow root to change the vector
		 * or specअगरy VPs outside of the set that is initially used
		 * during mapping.
		 */
		stored_entry = data->chip_data;
		data->chip_data = शून्य;

		status = hv_unmap_msi_पूर्णांकerrupt(dev, stored_entry);

		kमुक्त(stored_entry);

		अगर (status != HV_STATUS_SUCCESS) अणु
			pr_debug("%s: failed to unmap, status %lld", __func__, status);
			वापस;
		पूर्ण
	पूर्ण

	stored_entry = kzalloc(माप(*stored_entry), GFP_ATOMIC);
	अगर (!stored_entry) अणु
		pr_debug("%s: failed to allocate chip data\n", __func__);
		वापस;
	पूर्ण

	status = hv_map_msi_पूर्णांकerrupt(dev, cpu, cfg->vector, &out_entry);
	अगर (status != HV_STATUS_SUCCESS) अणु
		kमुक्त(stored_entry);
		वापस;
	पूर्ण

	*stored_entry = out_entry;
	data->chip_data = stored_entry;
	entry_to_msi_msg(&out_entry, msg);

	वापस;
पूर्ण

अटल पूर्णांक hv_unmap_msi_पूर्णांकerrupt(काष्ठा pci_dev *dev, काष्ठा hv_पूर्णांकerrupt_entry *old_entry)
अणु
	वापस hv_unmap_पूर्णांकerrupt(hv_build_pci_dev_id(dev).as_uपूर्णांक64, old_entry);
पूर्ण

अटल व्योम hv_tearकरोwn_msi_irq_common(काष्ठा pci_dev *dev, काष्ठा msi_desc *msidesc, पूर्णांक irq)
अणु
	u64 status;
	काष्ठा hv_पूर्णांकerrupt_entry old_entry;
	काष्ठा irq_desc *desc;
	काष्ठा irq_data *data;
	काष्ठा msi_msg msg;

	desc = irq_to_desc(irq);
	अगर (!desc) अणु
		pr_debug("%s: no irq desc\n", __func__);
		वापस;
	पूर्ण

	data = &desc->irq_data;
	अगर (!data) अणु
		pr_debug("%s: no irq data\n", __func__);
		वापस;
	पूर्ण

	अगर (!data->chip_data) अणु
		pr_debug("%s: no chip data\n!", __func__);
		वापस;
	पूर्ण

	old_entry = *(काष्ठा hv_पूर्णांकerrupt_entry *)data->chip_data;
	entry_to_msi_msg(&old_entry, &msg);

	kमुक्त(data->chip_data);
	data->chip_data = शून्य;

	status = hv_unmap_msi_पूर्णांकerrupt(dev, &old_entry);

	अगर (status != HV_STATUS_SUCCESS) अणु
		pr_err("%s: hypercall failed, status %lld\n", __func__, status);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम hv_msi_करोमुख्य_मुक्त_irqs(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा msi_desc *entry;
	काष्ठा pci_dev *pdev;

	अगर (WARN_ON_ONCE(!dev_is_pci(dev)))
		वापस;

	pdev = to_pci_dev(dev);

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		अगर (entry->irq) अणु
			क्रम (i = 0; i < entry->nvec_used; i++) अणु
				hv_tearकरोwn_msi_irq_common(pdev, entry, entry->irq + i);
				irq_करोमुख्य_मुक्त_irqs(entry->irq + i, 1);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * IRQ Chip क्रम MSI PCI/PCI-X/PCI-Express Devices,
 * which implement the MSI or MSI-X Capability Structure.
 */
अटल काष्ठा irq_chip hv_pci_msi_controller = अणु
	.name			= "HV-PCI-MSI",
	.irq_unmask		= pci_msi_unmask_irq,
	.irq_mask		= pci_msi_mask_irq,
	.irq_ack		= irq_chip_ack_parent,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_compose_msi_msg	= hv_irq_compose_msi_msg,
	.irq_set_affinity	= msi_करोमुख्य_set_affinity,
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_ops pci_msi_करोमुख्य_ops = अणु
	.करोमुख्य_मुक्त_irqs	= hv_msi_करोमुख्य_मुक्त_irqs,
	.msi_prepare		= pci_msi_prepare,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info hv_pci_msi_करोमुख्य_info = अणु
	.flags		= MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
			  MSI_FLAG_PCI_MSIX,
	.ops		= &pci_msi_करोमुख्य_ops,
	.chip		= &hv_pci_msi_controller,
	.handler	= handle_edge_irq,
	.handler_name	= "edge",
पूर्ण;

काष्ठा irq_करोमुख्य * __init hv_create_pci_msi_करोमुख्य(व्योम)
अणु
	काष्ठा irq_करोमुख्य *d = शून्य;
	काष्ठा fwnode_handle *fn;

	fn = irq_करोमुख्य_alloc_named_fwnode("HV-PCI-MSI");
	अगर (fn)
		d = pci_msi_create_irq_करोमुख्य(fn, &hv_pci_msi_करोमुख्य_info, x86_vector_करोमुख्य);

	/* No poपूर्णांक in going further अगर we can't get an irq करोमुख्य */
	BUG_ON(!d);

	वापस d;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI_MSI */

पूर्णांक hv_unmap_ioapic_पूर्णांकerrupt(पूर्णांक ioapic_id, काष्ठा hv_पूर्णांकerrupt_entry *entry)
अणु
	जोड़ hv_device_id device_id;

	device_id.as_uपूर्णांक64 = 0;
	device_id.device_type = HV_DEVICE_TYPE_IOAPIC;
	device_id.ioapic.ioapic_id = (u8)ioapic_id;

	वापस hv_unmap_पूर्णांकerrupt(device_id.as_uपूर्णांक64, entry);
पूर्ण
EXPORT_SYMBOL_GPL(hv_unmap_ioapic_पूर्णांकerrupt);

पूर्णांक hv_map_ioapic_पूर्णांकerrupt(पूर्णांक ioapic_id, bool level, पूर्णांक cpu, पूर्णांक vector,
		काष्ठा hv_पूर्णांकerrupt_entry *entry)
अणु
	जोड़ hv_device_id device_id;

	device_id.as_uपूर्णांक64 = 0;
	device_id.device_type = HV_DEVICE_TYPE_IOAPIC;
	device_id.ioapic.ioapic_id = (u8)ioapic_id;

	वापस hv_map_पूर्णांकerrupt(device_id, level, cpu, vector, entry);
पूर्ण
EXPORT_SYMBOL_GPL(hv_map_ioapic_पूर्णांकerrupt);
