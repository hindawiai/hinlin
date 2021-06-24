<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MSI hooks क्रम standard x86 apic
 */

#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <linux/dmar.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/msidef.h>

अटल काष्ठा irq_chip	ia64_msi_chip;

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक ia64_set_msi_irq_affinity(काष्ठा irq_data *idata,
				     स्थिर cpumask_t *cpu_mask, bool क्रमce)
अणु
	काष्ठा msi_msg msg;
	u32 addr, data;
	पूर्णांक cpu = cpumask_first_and(cpu_mask, cpu_online_mask);
	अचिन्हित पूर्णांक irq = idata->irq;

	अगर (irq_prepare_move(irq, cpu))
		वापस -1;

	__get_cached_msi_msg(irq_data_get_msi_desc(idata), &msg);

	addr = msg.address_lo;
	addr &= MSI_ADDR_DEST_ID_MASK;
	addr |= MSI_ADDR_DEST_ID_CPU(cpu_physical_id(cpu));
	msg.address_lo = addr;

	data = msg.data;
	data &= MSI_DATA_VECTOR_MASK;
	data |= MSI_DATA_VECTOR(irq_to_vector(irq));
	msg.data = data;

	pci_ग_लिखो_msi_msg(irq, &msg);
	cpumask_copy(irq_data_get_affinity_mask(idata), cpumask_of(cpu));

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

पूर्णांक arch_setup_msi_irq(काष्ठा pci_dev *pdev, काष्ठा msi_desc *desc)
अणु
	काष्ठा msi_msg	msg;
	अचिन्हित दीर्घ	dest_phys_id;
	पूर्णांक	irq, vector;

	irq = create_irq();
	अगर (irq < 0)
		वापस irq;

	irq_set_msi_desc(irq, desc);
	dest_phys_id = cpu_physical_id(cpumask_any_and(&(irq_to_करोमुख्य(irq)),
						       cpu_online_mask));
	vector = irq_to_vector(irq);

	msg.address_hi = 0;
	msg.address_lo =
		MSI_ADDR_HEADER |
		MSI_ADDR_DEST_MODE_PHYS |
		MSI_ADDR_REसूचीECTION_CPU |
		MSI_ADDR_DEST_ID_CPU(dest_phys_id);

	msg.data =
		MSI_DATA_TRIGGER_EDGE |
		MSI_DATA_LEVEL_ASSERT |
		MSI_DATA_DELIVERY_FIXED |
		MSI_DATA_VECTOR(vector);

	pci_ग_लिखो_msi_msg(irq, &msg);
	irq_set_chip_and_handler(irq, &ia64_msi_chip, handle_edge_irq);

	वापस 0;
पूर्ण

व्योम arch_tearकरोwn_msi_irq(अचिन्हित पूर्णांक irq)
अणु
	destroy_irq(irq);
पूर्ण

अटल व्योम ia64_ack_msi_irq(काष्ठा irq_data *data)
अणु
	irq_complete_move(data->irq);
	irq_move_irq(data);
	ia64_eoi();
पूर्ण

अटल पूर्णांक ia64_msi_retrigger_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक vector = irq_to_vector(data->irq);
	ia64_resend_irq(vector);

	वापस 1;
पूर्ण

/*
 * Generic ops used on most IA64 platक्रमms.
 */
अटल काष्ठा irq_chip ia64_msi_chip = अणु
	.name			= "PCI-MSI",
	.irq_mask		= pci_msi_mask_irq,
	.irq_unmask		= pci_msi_unmask_irq,
	.irq_ack		= ia64_ack_msi_irq,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	= ia64_set_msi_irq_affinity,
#पूर्ण_अगर
	.irq_retrigger		= ia64_msi_retrigger_irq,
पूर्ण;

#अगर_घोषित CONFIG_INTEL_IOMMU
#अगर_घोषित CONFIG_SMP
अटल पूर्णांक dmar_msi_set_affinity(काष्ठा irq_data *data,
				 स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	काष्ठा irq_cfg *cfg = irq_cfg + irq;
	काष्ठा msi_msg msg;
	पूर्णांक cpu = cpumask_first_and(mask, cpu_online_mask);

	अगर (irq_prepare_move(irq, cpu))
		वापस -1;

	dmar_msi_पढ़ो(irq, &msg);

	msg.data &= ~MSI_DATA_VECTOR_MASK;
	msg.data |= MSI_DATA_VECTOR(cfg->vector);
	msg.address_lo &= ~MSI_ADDR_DEST_ID_MASK;
	msg.address_lo |= MSI_ADDR_DEST_ID_CPU(cpu_physical_id(cpu));

	dmar_msi_ग_लिखो(irq, &msg);
	cpumask_copy(irq_data_get_affinity_mask(data), mask);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल काष्ठा irq_chip dmar_msi_type = अणु
	.name = "DMAR_MSI",
	.irq_unmask = dmar_msi_unmask,
	.irq_mask = dmar_msi_mask,
	.irq_ack = ia64_ack_msi_irq,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = dmar_msi_set_affinity,
#पूर्ण_अगर
	.irq_retrigger = ia64_msi_retrigger_irq,
पूर्ण;

अटल व्योम
msi_compose_msg(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक irq, काष्ठा msi_msg *msg)
अणु
	काष्ठा irq_cfg *cfg = irq_cfg + irq;
	अचिन्हित dest;

	dest = cpu_physical_id(cpumask_first_and(&(irq_to_करोमुख्य(irq)),
						 cpu_online_mask));

	msg->address_hi = 0;
	msg->address_lo =
		MSI_ADDR_HEADER |
		MSI_ADDR_DEST_MODE_PHYS |
		MSI_ADDR_REसूचीECTION_CPU |
		MSI_ADDR_DEST_ID_CPU(dest);

	msg->data =
		MSI_DATA_TRIGGER_EDGE |
		MSI_DATA_LEVEL_ASSERT |
		MSI_DATA_DELIVERY_FIXED |
		MSI_DATA_VECTOR(cfg->vector);
पूर्ण

पूर्णांक dmar_alloc_hwirq(पूर्णांक id, पूर्णांक node, व्योम *arg)
अणु
	पूर्णांक irq;
	काष्ठा msi_msg msg;

	irq = create_irq();
	अगर (irq > 0) अणु
		irq_set_handler_data(irq, arg);
		irq_set_chip_and_handler_name(irq, &dmar_msi_type,
					      handle_edge_irq, "edge");
		msi_compose_msg(शून्य, irq, &msg);
		dmar_msi_ग_लिखो(irq, &msg);
	पूर्ण

	वापस irq;
पूर्ण

व्योम dmar_मुक्त_hwirq(पूर्णांक irq)
अणु
	irq_set_handler_data(irq, शून्य);
	destroy_irq(irq);
पूर्ण
#पूर्ण_अगर /* CONFIG_INTEL_IOMMU */

