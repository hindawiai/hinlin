<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support of MSI, HPET and DMAR पूर्णांकerrupts.
 *
 * Copyright (C) 1997, 1998, 1999, 2000, 2009 Ingo Molnar, Hajnalka Szabo
 *	Moved from arch/x86/kernel/apic/io_apic.c.
 * Jiang Liu <jiang.liu@linux.पूर्णांकel.com>
 *	Convert to hierarchical irqकरोमुख्य
 */
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/dmar.h>
#समावेश <linux/hpet.h>
#समावेश <linux/msi.h>
#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/irq_remapping.h>

काष्ठा irq_करोमुख्य *x86_pci_msi_शेष_करोमुख्य __ro_after_init;

अटल व्योम irq_msi_update_msg(काष्ठा irq_data *irqd, काष्ठा irq_cfg *cfg)
अणु
	काष्ठा msi_msg msg[2] = अणु [1] = अणु पूर्ण, पूर्ण;

	__irq_msi_compose_msg(cfg, msg, false);
	irq_data_get_irq_chip(irqd)->irq_ग_लिखो_msi_msg(irqd, msg);
पूर्ण

अटल पूर्णांक
msi_set_affinity(काष्ठा irq_data *irqd, स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा irq_cfg old_cfg, *cfg = irqd_cfg(irqd);
	काष्ठा irq_data *parent = irqd->parent_data;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret;

	/* Save the current configuration */
	cpu = cpumask_first(irq_data_get_effective_affinity_mask(irqd));
	old_cfg = *cfg;

	/* Allocate a new target vector */
	ret = parent->chip->irq_set_affinity(parent, mask, क्रमce);
	अगर (ret < 0 || ret == IRQ_SET_MASK_OK_DONE)
		वापस ret;

	/*
	 * For non-maskable and non-remapped MSI पूर्णांकerrupts the migration
	 * to a dअगरferent destination CPU and a dअगरferent vector has to be
	 * करोne careful to handle the possible stray पूर्णांकerrupt which can be
	 * caused by the non-atomic update of the address/data pair.
	 *
	 * Direct update is possible when:
	 * - The MSI is maskable (remapped MSI करोes not use this code path)).
	 *   The quirk bit is not set in this हाल.
	 * - The new vector is the same as the old vector
	 * - The old vector is MANAGED_IRQ_SHUTDOWN_VECTOR (पूर्णांकerrupt starts up)
	 * - The new destination CPU is the same as the old destination CPU
	 */
	अगर (!irqd_msi_nomask_quirk(irqd) ||
	    cfg->vector == old_cfg.vector ||
	    old_cfg.vector == MANAGED_IRQ_SHUTDOWN_VECTOR ||
	    cfg->dest_apicid == old_cfg.dest_apicid) अणु
		irq_msi_update_msg(irqd, cfg);
		वापस ret;
	पूर्ण

	/*
	 * Paranoia: Validate that the पूर्णांकerrupt target is the local
	 * CPU.
	 */
	अगर (WARN_ON_ONCE(cpu != smp_processor_id())) अणु
		irq_msi_update_msg(irqd, cfg);
		वापस ret;
	पूर्ण

	/*
	 * Redirect the पूर्णांकerrupt to the new vector on the current CPU
	 * first. This might cause a spurious पूर्णांकerrupt on this vector अगर
	 * the device उठाओs an पूर्णांकerrupt right between this update and the
	 * update to the final destination CPU.
	 *
	 * If the vector is in use then the installed device handler will
	 * denote it as spurious which is no harm as this is a rare event
	 * and पूर्णांकerrupt handlers have to cope with spurious पूर्णांकerrupts
	 * anyway. If the vector is unused, then it is marked so it won't
	 * trigger the 'No irq handler for vector' warning in
	 * common_पूर्णांकerrupt().
	 *
	 * This requires to hold vector lock to prevent concurrent updates to
	 * the affected vector.
	 */
	lock_vector_lock();

	/*
	 * Mark the new target vector on the local CPU अगर it is currently
	 * unused. Reuse the VECTOR_RETRIGGERED state which is also used in
	 * the CPU hotplug path क्रम a similar purpose. This cannot be
	 * unकरोne here as the current CPU has पूर्णांकerrupts disabled and
	 * cannot handle the पूर्णांकerrupt beक्रमe the whole set_affinity()
	 * section is करोne. In the CPU unplug हाल, the current CPU is
	 * about to vanish and will not handle any पूर्णांकerrupts anymore. The
	 * vector is cleaned up when the CPU comes online again.
	 */
	अगर (IS_ERR_OR_शून्य(this_cpu_पढ़ो(vector_irq[cfg->vector])))
		this_cpu_ग_लिखो(vector_irq[cfg->vector], VECTOR_RETRIGGERED);

	/* Redirect it to the new vector on the local CPU temporarily */
	old_cfg.vector = cfg->vector;
	irq_msi_update_msg(irqd, &old_cfg);

	/* Now transition it to the target CPU */
	irq_msi_update_msg(irqd, cfg);

	/*
	 * All पूर्णांकerrupts after this poपूर्णांक are now targeted at the new
	 * vector/CPU.
	 *
	 * Drop vector lock beक्रमe testing whether the temporary assignment
	 * to the local CPU was hit by an पूर्णांकerrupt उठाओd in the device,
	 * because the retrigger function acquires vector lock again.
	 */
	unlock_vector_lock();

	/*
	 * Check whether the transition raced with a device पूर्णांकerrupt and
	 * is pending in the local APICs IRR. It is safe to करो this outside
	 * of vector lock as the irq_desc::lock of this पूर्णांकerrupt is still
	 * held and पूर्णांकerrupts are disabled: The check is not accessing the
	 * underlying vector store. It's just checking the local APIC's
	 * IRR.
	 */
	अगर (lapic_vector_set_in_irr(cfg->vector))
		irq_data_get_irq_chip(irqd)->irq_retrigger(irqd);

	वापस ret;
पूर्ण

/*
 * IRQ Chip क्रम MSI PCI/PCI-X/PCI-Express Devices,
 * which implement the MSI or MSI-X Capability Structure.
 */
अटल काष्ठा irq_chip pci_msi_controller = अणु
	.name			= "PCI-MSI",
	.irq_unmask		= pci_msi_unmask_irq,
	.irq_mask		= pci_msi_mask_irq,
	.irq_ack		= irq_chip_ack_parent,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_set_affinity	= msi_set_affinity,
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

पूर्णांक pci_msi_prepare(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा device *dev, पूर्णांक nvec,
		    msi_alloc_info_t *arg)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा msi_desc *desc = first_pci_msi_entry(pdev);

	init_irq_alloc_info(arg, शून्य);
	अगर (desc->msi_attrib.is_msix) अणु
		arg->type = X86_IRQ_ALLOC_TYPE_PCI_MSIX;
	पूर्ण अन्यथा अणु
		arg->type = X86_IRQ_ALLOC_TYPE_PCI_MSI;
		arg->flags |= X86_IRQ_ALLOC_CONTIGUOUS_VECTORS;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_msi_prepare);

अटल काष्ठा msi_करोमुख्य_ops pci_msi_करोमुख्य_ops = अणु
	.msi_prepare	= pci_msi_prepare,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info pci_msi_करोमुख्य_info = अणु
	.flags		= MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
			  MSI_FLAG_PCI_MSIX,
	.ops		= &pci_msi_करोमुख्य_ops,
	.chip		= &pci_msi_controller,
	.handler	= handle_edge_irq,
	.handler_name	= "edge",
पूर्ण;

काष्ठा irq_करोमुख्य * __init native_create_pci_msi_करोमुख्य(व्योम)
अणु
	काष्ठा fwnode_handle *fn;
	काष्ठा irq_करोमुख्य *d;

	अगर (disable_apic)
		वापस शून्य;

	fn = irq_करोमुख्य_alloc_named_fwnode("PCI-MSI");
	अगर (!fn)
		वापस शून्य;

	d = pci_msi_create_irq_करोमुख्य(fn, &pci_msi_करोमुख्य_info,
				      x86_vector_करोमुख्य);
	अगर (!d) अणु
		irq_करोमुख्य_मुक्त_fwnode(fn);
		pr_warn("Failed to initialize PCI-MSI irqdomain.\n");
	पूर्ण अन्यथा अणु
		d->flags |= IRQ_DOMAIN_MSI_NOMASK_QUIRK;
	पूर्ण
	वापस d;
पूर्ण

व्योम __init x86_create_pci_msi_करोमुख्य(व्योम)
अणु
	x86_pci_msi_शेष_करोमुख्य = x86_init.irqs.create_pci_msi_करोमुख्य();
पूर्ण

#अगर_घोषित CONFIG_IRQ_REMAP
अटल काष्ठा irq_chip pci_msi_ir_controller = अणु
	.name			= "IR-PCI-MSI",
	.irq_unmask		= pci_msi_unmask_irq,
	.irq_mask		= pci_msi_mask_irq,
	.irq_ack		= irq_chip_ack_parent,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info pci_msi_ir_करोमुख्य_info = अणु
	.flags		= MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
			  MSI_FLAG_MULTI_PCI_MSI | MSI_FLAG_PCI_MSIX,
	.ops		= &pci_msi_करोमुख्य_ops,
	.chip		= &pci_msi_ir_controller,
	.handler	= handle_edge_irq,
	.handler_name	= "edge",
पूर्ण;

काष्ठा irq_करोमुख्य *arch_create_remap_msi_irq_करोमुख्य(काष्ठा irq_करोमुख्य *parent,
						    स्थिर अक्षर *name, पूर्णांक id)
अणु
	काष्ठा fwnode_handle *fn;
	काष्ठा irq_करोमुख्य *d;

	fn = irq_करोमुख्य_alloc_named_id_fwnode(name, id);
	अगर (!fn)
		वापस शून्य;
	d = pci_msi_create_irq_करोमुख्य(fn, &pci_msi_ir_करोमुख्य_info, parent);
	अगर (!d)
		irq_करोमुख्य_मुक्त_fwnode(fn);
	वापस d;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DMAR_TABLE
/*
 * The Intel IOMMU (ab)uses the high bits of the MSI address to contain the
 * high bits of the destination APIC ID. This can't be करोne in the general
 * हाल क्रम MSIs as it would be targeting real memory above 4GiB not the
 * APIC.
 */
अटल व्योम dmar_msi_compose_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	__irq_msi_compose_msg(irqd_cfg(data), msg, true);
पूर्ण

अटल व्योम dmar_msi_ग_लिखो_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	dmar_msi_ग_लिखो(data->irq, msg);
पूर्ण

अटल काष्ठा irq_chip dmar_msi_controller = अणु
	.name			= "DMAR-MSI",
	.irq_unmask		= dmar_msi_unmask,
	.irq_mask		= dmar_msi_mask,
	.irq_ack		= irq_chip_ack_parent,
	.irq_set_affinity	= msi_करोमुख्य_set_affinity,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_compose_msi_msg	= dmar_msi_compose_msg,
	.irq_ग_लिखो_msi_msg	= dmar_msi_ग_लिखो_msg,
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल पूर्णांक dmar_msi_init(काष्ठा irq_करोमुख्य *करोमुख्य,
			 काष्ठा msi_करोमुख्य_info *info, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hwirq, msi_alloc_info_t *arg)
अणु
	irq_करोमुख्य_set_info(करोमुख्य, virq, arg->devid, info->chip, शून्य,
			    handle_edge_irq, arg->data, "edge");

	वापस 0;
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops dmar_msi_करोमुख्य_ops = अणु
	.msi_init	= dmar_msi_init,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info dmar_msi_करोमुख्य_info = अणु
	.ops		= &dmar_msi_करोमुख्य_ops,
	.chip		= &dmar_msi_controller,
	.flags		= MSI_FLAG_USE_DEF_DOM_OPS,
पूर्ण;

अटल काष्ठा irq_करोमुख्य *dmar_get_irq_करोमुख्य(व्योम)
अणु
	अटल काष्ठा irq_करोमुख्य *dmar_करोमुख्य;
	अटल DEFINE_MUTEX(dmar_lock);
	काष्ठा fwnode_handle *fn;

	mutex_lock(&dmar_lock);
	अगर (dmar_करोमुख्य)
		जाओ out;

	fn = irq_करोमुख्य_alloc_named_fwnode("DMAR-MSI");
	अगर (fn) अणु
		dmar_करोमुख्य = msi_create_irq_करोमुख्य(fn, &dmar_msi_करोमुख्य_info,
						    x86_vector_करोमुख्य);
		अगर (!dmar_करोमुख्य)
			irq_करोमुख्य_मुक्त_fwnode(fn);
	पूर्ण
out:
	mutex_unlock(&dmar_lock);
	वापस dmar_करोमुख्य;
पूर्ण

पूर्णांक dmar_alloc_hwirq(पूर्णांक id, पूर्णांक node, व्योम *arg)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = dmar_get_irq_करोमुख्य();
	काष्ठा irq_alloc_info info;

	अगर (!करोमुख्य)
		वापस -1;

	init_irq_alloc_info(&info, शून्य);
	info.type = X86_IRQ_ALLOC_TYPE_DMAR;
	info.devid = id;
	info.hwirq = id;
	info.data = arg;

	वापस irq_करोमुख्य_alloc_irqs(करोमुख्य, 1, node, &info);
पूर्ण

व्योम dmar_मुक्त_hwirq(पूर्णांक irq)
अणु
	irq_करोमुख्य_मुक्त_irqs(irq, 1);
पूर्ण
#पूर्ण_अगर
