<शैली गुरु>
/*
 * Marvell Armada 370 and Armada XP SoC IRQ handling
 *
 * Copyright (C) 2012 Marvell
 *
 * Lior Amsalem <alior@marvell.com>
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 * Ben Dooks <ben.करोoks@codethink.co.uk>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/cpu.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/msi.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/mach/irq.h>

/*
 * Overall diagram of the Armada XP पूर्णांकerrupt controller:
 *
 *    To CPU 0                 To CPU 1
 *
 *       /\                       /\
 *       ||                       ||
 * +---------------+     +---------------+
 * |               |	 |               |
 * |    per-CPU    |	 |    per-CPU    |
 * |  mask/unmask  |	 |  mask/unmask  |
 * |     CPU0      |	 |     CPU1      |
 * |               |	 |               |
 * +---------------+	 +---------------+
 *        /\                       /\
 *        ||                       ||
 *        \\_______________________//
 *                     ||
 *            +-------------------+
 *            |                   |
 *            | Global पूर्णांकerrupt  |
 *            |    mask/unmask    |
 *            |                   |
 *            +-------------------+
 *                     /\
 *                     ||
 *               पूर्णांकerrupt from
 *                   device
 *
 * The "global interrupt mask/unmask" is modअगरied using the
 * ARMADA_370_XP_INT_SET_ENABLE_OFFS and
 * ARMADA_370_XP_INT_CLEAR_ENABLE_OFFS रेजिस्टरs, which are relative
 * to "main_int_base".
 *
 * The "per-CPU mask/unmask" is modअगरied using the
 * ARMADA_370_XP_INT_SET_MASK_OFFS and
 * ARMADA_370_XP_INT_CLEAR_MASK_OFFS रेजिस्टरs, which are relative to
 * "per_cpu_int_base". This base address poपूर्णांकs to a special address,
 * which स्वतःmatically accesses the रेजिस्टरs of the current CPU.
 *
 * The per-CPU mask/unmask can also be adjusted using the global
 * per-पूर्णांकerrupt ARMADA_370_XP_INT_SOURCE_CTL रेजिस्टर, which we use
 * to configure पूर्णांकerrupt affinity.
 *
 * Due to this model, all पूर्णांकerrupts need to be mask/unmasked at two
 * dअगरferent levels: at the global level and at the per-CPU level.
 *
 * This driver takes the following approach to deal with this:
 *
 *  - For global पूर्णांकerrupts:
 *
 *    At ->map() समय, a global पूर्णांकerrupt is unmasked at the per-CPU
 *    mask/unmask level. It is thereक्रमe unmasked at this level क्रम
 *    the current CPU, running the ->map() code. This allows to have
 *    the पूर्णांकerrupt unmasked at this level in non-SMP
 *    configurations. In SMP configurations, the ->set_affinity()
 *    callback is called, which using the
 *    ARMADA_370_XP_INT_SOURCE_CTL() पढ़ोjusts the per-CPU mask/unmask
 *    क्रम the पूर्णांकerrupt.
 *
 *    The ->mask() and ->unmask() operations only mask/unmask the
 *    पूर्णांकerrupt at the "global" level.
 *
 *    So, a global पूर्णांकerrupt is enabled at the per-CPU level as soon
 *    as it is mapped. At run समय, the masking/unmasking takes place
 *    at the global level.
 *
 *  - For per-CPU पूर्णांकerrupts
 *
 *    At ->map() समय, a per-CPU पूर्णांकerrupt is unmasked at the global
 *    mask/unmask level.
 *
 *    The ->mask() and ->unmask() operations mask/unmask the पूर्णांकerrupt
 *    at the per-CPU level.
 *
 *    So, a per-CPU पूर्णांकerrupt is enabled at the global level as soon
 *    as it is mapped. At run समय, the masking/unmasking takes place
 *    at the per-CPU level.
 */

/* Registers relative to मुख्य_पूर्णांक_base */
#घोषणा ARMADA_370_XP_INT_CONTROL		(0x00)
#घोषणा ARMADA_370_XP_SW_TRIG_INT_OFFS		(0x04)
#घोषणा ARMADA_370_XP_INT_SET_ENABLE_OFFS	(0x30)
#घोषणा ARMADA_370_XP_INT_CLEAR_ENABLE_OFFS	(0x34)
#घोषणा ARMADA_370_XP_INT_SOURCE_CTL(irq)	(0x100 + irq*4)
#घोषणा ARMADA_370_XP_INT_SOURCE_CPU_MASK	0xF
#घोषणा ARMADA_370_XP_INT_IRQ_FIQ_MASK(cpuid)	((BIT(0) | BIT(8)) << cpuid)

/* Registers relative to per_cpu_पूर्णांक_base */
#घोषणा ARMADA_370_XP_IN_DRBEL_CAUSE_OFFS	(0x08)
#घोषणा ARMADA_370_XP_IN_DRBEL_MSK_OFFS		(0x0c)
#घोषणा ARMADA_375_PPI_CAUSE			(0x10)
#घोषणा ARMADA_370_XP_CPU_INTACK_OFFS		(0x44)
#घोषणा ARMADA_370_XP_INT_SET_MASK_OFFS		(0x48)
#घोषणा ARMADA_370_XP_INT_CLEAR_MASK_OFFS	(0x4C)
#घोषणा ARMADA_370_XP_INT_FABRIC_MASK_OFFS	(0x54)
#घोषणा ARMADA_370_XP_INT_CAUSE_PERF(cpu)	(1 << cpu)

#घोषणा ARMADA_370_XP_MAX_PER_CPU_IRQS		(28)

#घोषणा IPI_DOORBELL_START                      (0)
#घोषणा IPI_DOORBELL_END                        (8)
#घोषणा IPI_DOORBELL_MASK                       0xFF
#घोषणा PCI_MSI_DOORBELL_START                  (16)
#घोषणा PCI_MSI_DOORBELL_NR                     (16)
#घोषणा PCI_MSI_DOORBELL_END                    (32)
#घोषणा PCI_MSI_DOORBELL_MASK                   0xFFFF0000

अटल व्योम __iomem *per_cpu_पूर्णांक_base;
अटल व्योम __iomem *मुख्य_पूर्णांक_base;
अटल काष्ठा irq_करोमुख्य *armada_370_xp_mpic_करोमुख्य;
अटल u32 करोorbell_mask_reg;
अटल पूर्णांक parent_irq;
#अगर_घोषित CONFIG_PCI_MSI
अटल काष्ठा irq_करोमुख्य *armada_370_xp_msi_करोमुख्य;
अटल काष्ठा irq_करोमुख्य *armada_370_xp_msi_inner_करोमुख्य;
अटल DECLARE_BITMAP(msi_used, PCI_MSI_DOORBELL_NR);
अटल DEFINE_MUTEX(msi_used_lock);
अटल phys_addr_t msi_करोorbell_addr;
#पूर्ण_अगर

अटल अंतरभूत bool is_percpu_irq(irq_hw_number_t irq)
अणु
	अगर (irq <= ARMADA_370_XP_MAX_PER_CPU_IRQS)
		वापस true;

	वापस false;
पूर्ण

/*
 * In SMP mode:
 * For shared global पूर्णांकerrupts, mask/unmask global enable bit
 * For CPU पूर्णांकerrupts, mask/unmask the calling CPU's bit
 */
अटल व्योम armada_370_xp_irq_mask(काष्ठा irq_data *d)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	अगर (!is_percpu_irq(hwirq))
		ग_लिखोl(hwirq, मुख्य_पूर्णांक_base +
				ARMADA_370_XP_INT_CLEAR_ENABLE_OFFS);
	अन्यथा
		ग_लिखोl(hwirq, per_cpu_पूर्णांक_base +
				ARMADA_370_XP_INT_SET_MASK_OFFS);
पूर्ण

अटल व्योम armada_370_xp_irq_unmask(काष्ठा irq_data *d)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	अगर (!is_percpu_irq(hwirq))
		ग_लिखोl(hwirq, मुख्य_पूर्णांक_base +
				ARMADA_370_XP_INT_SET_ENABLE_OFFS);
	अन्यथा
		ग_लिखोl(hwirq, per_cpu_पूर्णांक_base +
				ARMADA_370_XP_INT_CLEAR_MASK_OFFS);
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI

अटल काष्ठा irq_chip armada_370_xp_msi_irq_chip = अणु
	.name = "MPIC MSI",
	.irq_mask = pci_msi_mask_irq,
	.irq_unmask = pci_msi_unmask_irq,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info armada_370_xp_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_MULTI_PCI_MSI | MSI_FLAG_PCI_MSIX),
	.chip	= &armada_370_xp_msi_irq_chip,
पूर्ण;

अटल व्योम armada_370_xp_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	msg->address_lo = lower_32_bits(msi_करोorbell_addr);
	msg->address_hi = upper_32_bits(msi_करोorbell_addr);
	msg->data = 0xf00 | (data->hwirq + PCI_MSI_DOORBELL_START);
पूर्ण

अटल पूर्णांक armada_370_xp_msi_set_affinity(काष्ठा irq_data *irq_data,
					  स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	 वापस -EINVAL;
पूर्ण

अटल काष्ठा irq_chip armada_370_xp_msi_bottom_irq_chip = अणु
	.name			= "MPIC MSI",
	.irq_compose_msi_msg	= armada_370_xp_compose_msi_msg,
	.irq_set_affinity	= armada_370_xp_msi_set_affinity,
पूर्ण;

अटल पूर्णांक armada_370_xp_msi_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	पूर्णांक hwirq, i;

	mutex_lock(&msi_used_lock);

	hwirq = biपंचांगap_find_next_zero_area(msi_used, PCI_MSI_DOORBELL_NR,
					   0, nr_irqs, 0);
	अगर (hwirq >= PCI_MSI_DOORBELL_NR) अणु
		mutex_unlock(&msi_used_lock);
		वापस -ENOSPC;
	पूर्ण

	biपंचांगap_set(msi_used, hwirq, nr_irqs);
	mutex_unlock(&msi_used_lock);

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, hwirq + i,
				    &armada_370_xp_msi_bottom_irq_chip,
				    करोमुख्य->host_data, handle_simple_irq,
				    शून्य, शून्य);
	पूर्ण

	वापस hwirq;
पूर्ण

अटल व्योम armada_370_xp_msi_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				   अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	mutex_lock(&msi_used_lock);
	biपंचांगap_clear(msi_used, d->hwirq, nr_irqs);
	mutex_unlock(&msi_used_lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops armada_370_xp_msi_करोमुख्य_ops = अणु
	.alloc	= armada_370_xp_msi_alloc,
	.मुक्त	= armada_370_xp_msi_मुक्त,
पूर्ण;

अटल पूर्णांक armada_370_xp_msi_init(काष्ठा device_node *node,
				  phys_addr_t मुख्य_पूर्णांक_phys_base)
अणु
	u32 reg;

	msi_करोorbell_addr = मुख्य_पूर्णांक_phys_base +
		ARMADA_370_XP_SW_TRIG_INT_OFFS;

	armada_370_xp_msi_inner_करोमुख्य =
		irq_करोमुख्य_add_linear(शून्य, PCI_MSI_DOORBELL_NR,
				      &armada_370_xp_msi_करोमुख्य_ops, शून्य);
	अगर (!armada_370_xp_msi_inner_करोमुख्य)
		वापस -ENOMEM;

	armada_370_xp_msi_करोमुख्य =
		pci_msi_create_irq_करोमुख्य(of_node_to_fwnode(node),
					  &armada_370_xp_msi_करोमुख्य_info,
					  armada_370_xp_msi_inner_करोमुख्य);
	अगर (!armada_370_xp_msi_करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(armada_370_xp_msi_inner_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	reg = पढ़ोl(per_cpu_पूर्णांक_base + ARMADA_370_XP_IN_DRBEL_MSK_OFFS)
		| PCI_MSI_DOORBELL_MASK;

	ग_लिखोl(reg, per_cpu_पूर्णांक_base +
	       ARMADA_370_XP_IN_DRBEL_MSK_OFFS);

	/* Unmask IPI पूर्णांकerrupt */
	ग_लिखोl(1, per_cpu_पूर्णांक_base + ARMADA_370_XP_INT_CLEAR_MASK_OFFS);

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक armada_370_xp_msi_init(काष्ठा device_node *node,
					 phys_addr_t मुख्य_पूर्णांक_phys_base)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम armada_xp_mpic_perf_init(व्योम)
अणु
	अचिन्हित दीर्घ cpuid = cpu_logical_map(smp_processor_id());

	/* Enable Perक्रमmance Counter Overflow पूर्णांकerrupts */
	ग_लिखोl(ARMADA_370_XP_INT_CAUSE_PERF(cpuid),
	       per_cpu_पूर्णांक_base + ARMADA_370_XP_INT_FABRIC_MASK_OFFS);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल काष्ठा irq_करोमुख्य *ipi_करोमुख्य;

अटल व्योम armada_370_xp_ipi_mask(काष्ठा irq_data *d)
अणु
	u32 reg;
	reg = पढ़ोl(per_cpu_पूर्णांक_base + ARMADA_370_XP_IN_DRBEL_MSK_OFFS);
	reg &= ~BIT(d->hwirq);
	ग_लिखोl(reg, per_cpu_पूर्णांक_base + ARMADA_370_XP_IN_DRBEL_MSK_OFFS);
पूर्ण

अटल व्योम armada_370_xp_ipi_unmask(काष्ठा irq_data *d)
अणु
	u32 reg;
	reg = पढ़ोl(per_cpu_पूर्णांक_base + ARMADA_370_XP_IN_DRBEL_MSK_OFFS);
	reg |= BIT(d->hwirq);
	ग_लिखोl(reg, per_cpu_पूर्णांक_base + ARMADA_370_XP_IN_DRBEL_MSK_OFFS);
पूर्ण

अटल व्योम armada_370_xp_ipi_send_mask(काष्ठा irq_data *d,
					स्थिर काष्ठा cpumask *mask)
अणु
	अचिन्हित दीर्घ map = 0;
	पूर्णांक cpu;

	/* Convert our logical CPU mask पूर्णांकo a physical one. */
	क्रम_each_cpu(cpu, mask)
		map |= 1 << cpu_logical_map(cpu);

	/*
	 * Ensure that stores to Normal memory are visible to the
	 * other CPUs beक्रमe issuing the IPI.
	 */
	dsb();

	/* submit softirq */
	ग_लिखोl((map << 8) | d->hwirq, मुख्य_पूर्णांक_base +
		ARMADA_370_XP_SW_TRIG_INT_OFFS);
पूर्ण

अटल व्योम armada_370_xp_ipi_eoi(काष्ठा irq_data *d)
अणु
	ग_लिखोl(~BIT(d->hwirq), per_cpu_पूर्णांक_base + ARMADA_370_XP_IN_DRBEL_CAUSE_OFFS);
पूर्ण

अटल काष्ठा irq_chip ipi_irqchip = अणु
	.name		= "IPI",
	.irq_mask	= armada_370_xp_ipi_mask,
	.irq_unmask	= armada_370_xp_ipi_unmask,
	.irq_eoi	= armada_370_xp_ipi_eoi,
	.ipi_send_mask	= armada_370_xp_ipi_send_mask,
पूर्ण;

अटल पूर्णांक armada_370_xp_ipi_alloc(काष्ठा irq_करोमुख्य *d,
					 अचिन्हित पूर्णांक virq,
					 अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_set_percpu_devid(virq + i);
		irq_करोमुख्य_set_info(d, virq + i, i, &ipi_irqchip,
				    d->host_data,
				    handle_percpu_devid_irq,
				    शून्य, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम armada_370_xp_ipi_मुक्त(काष्ठा irq_करोमुख्य *d,
					 अचिन्हित पूर्णांक virq,
					 अचिन्हित पूर्णांक nr_irqs)
अणु
	/* Not मुक्तing IPIs */
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ipi_करोमुख्य_ops = अणु
	.alloc	= armada_370_xp_ipi_alloc,
	.मुक्त	= armada_370_xp_ipi_मुक्त,
पूर्ण;

अटल व्योम ipi_resume(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IPI_DOORBELL_END; i++) अणु
		पूर्णांक irq;

		irq = irq_find_mapping(ipi_करोमुख्य, i);
		अगर (irq <= 0)
			जारी;
		अगर (irq_percpu_is_enabled(irq)) अणु
			काष्ठा irq_data *d;
			d = irq_करोमुख्य_get_irq_data(ipi_करोमुख्य, irq);
			armada_370_xp_ipi_unmask(d);
		पूर्ण
	पूर्ण
पूर्ण

अटल __init व्योम armada_xp_ipi_init(काष्ठा device_node *node)
अणु
	पूर्णांक base_ipi;

	ipi_करोमुख्य = irq_करोमुख्य_create_linear(of_node_to_fwnode(node),
					      IPI_DOORBELL_END,
					      &ipi_करोमुख्य_ops, शून्य);
	अगर (WARN_ON(!ipi_करोमुख्य))
		वापस;

	irq_करोमुख्य_update_bus_token(ipi_करोमुख्य, DOMAIN_BUS_IPI);
	base_ipi = __irq_करोमुख्य_alloc_irqs(ipi_करोमुख्य, -1, IPI_DOORBELL_END,
					   NUMA_NO_NODE, शून्य, false, शून्य);
	अगर (WARN_ON(!base_ipi))
		वापस;

	set_smp_ipi_range(base_ipi, IPI_DOORBELL_END);
पूर्ण

अटल DEFINE_RAW_SPINLOCK(irq_controller_lock);

अटल पूर्णांक armada_xp_set_affinity(काष्ठा irq_data *d,
				  स्थिर काष्ठा cpumask *mask_val, bool क्रमce)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	अचिन्हित दीर्घ reg, mask;
	पूर्णांक cpu;

	/* Select a single core from the affinity mask which is online */
	cpu = cpumask_any_and(mask_val, cpu_online_mask);
	mask = 1UL << cpu_logical_map(cpu);

	raw_spin_lock(&irq_controller_lock);
	reg = पढ़ोl(मुख्य_पूर्णांक_base + ARMADA_370_XP_INT_SOURCE_CTL(hwirq));
	reg = (reg & (~ARMADA_370_XP_INT_SOURCE_CPU_MASK)) | mask;
	ग_लिखोl(reg, मुख्य_पूर्णांक_base + ARMADA_370_XP_INT_SOURCE_CTL(hwirq));
	raw_spin_unlock(&irq_controller_lock);

	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल व्योम armada_xp_mpic_smp_cpu_init(व्योम)
अणु
	u32 control;
	पूर्णांक nr_irqs, i;

	control = पढ़ोl(मुख्य_पूर्णांक_base + ARMADA_370_XP_INT_CONTROL);
	nr_irqs = (control >> 2) & 0x3ff;

	क्रम (i = 0; i < nr_irqs; i++)
		ग_लिखोl(i, per_cpu_पूर्णांक_base + ARMADA_370_XP_INT_SET_MASK_OFFS);

	/* Disable all IPIs */
	ग_लिखोl(0, per_cpu_पूर्णांक_base + ARMADA_370_XP_IN_DRBEL_MSK_OFFS);

	/* Clear pending IPIs */
	ग_लिखोl(0, per_cpu_पूर्णांक_base + ARMADA_370_XP_IN_DRBEL_CAUSE_OFFS);

	/* Unmask IPI पूर्णांकerrupt */
	ग_लिखोl(0, per_cpu_पूर्णांक_base + ARMADA_370_XP_INT_CLEAR_MASK_OFFS);
पूर्ण

अटल व्योम armada_xp_mpic_reenable_percpu(व्योम)
अणु
	अचिन्हित पूर्णांक irq;

	/* Re-enable per-CPU पूर्णांकerrupts that were enabled beक्रमe suspend */
	क्रम (irq = 0; irq < ARMADA_370_XP_MAX_PER_CPU_IRQS; irq++) अणु
		काष्ठा irq_data *data;
		पूर्णांक virq;

		virq = irq_linear_revmap(armada_370_xp_mpic_करोमुख्य, irq);
		अगर (virq == 0)
			जारी;

		data = irq_get_irq_data(virq);

		अगर (!irq_percpu_is_enabled(virq))
			जारी;

		armada_370_xp_irq_unmask(data);
	पूर्ण

	ipi_resume();
पूर्ण

अटल पूर्णांक armada_xp_mpic_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	armada_xp_mpic_perf_init();
	armada_xp_mpic_smp_cpu_init();
	armada_xp_mpic_reenable_percpu();
	वापस 0;
पूर्ण

अटल पूर्णांक mpic_cascaded_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	armada_xp_mpic_perf_init();
	armada_xp_mpic_reenable_percpu();
	enable_percpu_irq(parent_irq, IRQ_TYPE_NONE);
	वापस 0;
पूर्ण
#अन्यथा
अटल व्योम armada_xp_mpic_smp_cpu_init(व्योम) अणुपूर्ण
अटल व्योम ipi_resume(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip armada_370_xp_irq_chip = अणु
	.name		= "MPIC",
	.irq_mask       = armada_370_xp_irq_mask,
	.irq_mask_ack   = armada_370_xp_irq_mask,
	.irq_unmask     = armada_370_xp_irq_unmask,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity = armada_xp_set_affinity,
#पूर्ण_अगर
	.flags		= IRQCHIP_SKIP_SET_WAKE | IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल पूर्णांक armada_370_xp_mpic_irq_map(काष्ठा irq_करोमुख्य *h,
				      अचिन्हित पूर्णांक virq, irq_hw_number_t hw)
अणु
	armada_370_xp_irq_mask(irq_get_irq_data(virq));
	अगर (!is_percpu_irq(hw))
		ग_लिखोl(hw, per_cpu_पूर्णांक_base +
			ARMADA_370_XP_INT_CLEAR_MASK_OFFS);
	अन्यथा
		ग_लिखोl(hw, मुख्य_पूर्णांक_base + ARMADA_370_XP_INT_SET_ENABLE_OFFS);
	irq_set_status_flags(virq, IRQ_LEVEL);

	अगर (is_percpu_irq(hw)) अणु
		irq_set_percpu_devid(virq);
		irq_set_chip_and_handler(virq, &armada_370_xp_irq_chip,
					handle_percpu_devid_irq);
	पूर्ण अन्यथा अणु
		irq_set_chip_and_handler(virq, &armada_370_xp_irq_chip,
					handle_level_irq);
		irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(virq)));
	पूर्ण
	irq_set_probe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops armada_370_xp_mpic_irq_ops = अणु
	.map = armada_370_xp_mpic_irq_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

#अगर_घोषित CONFIG_PCI_MSI
अटल व्योम armada_370_xp_handle_msi_irq(काष्ठा pt_regs *regs, bool is_chained)
अणु
	u32 msimask, msinr;

	msimask = पढ़ोl_relaxed(per_cpu_पूर्णांक_base +
				ARMADA_370_XP_IN_DRBEL_CAUSE_OFFS)
		& PCI_MSI_DOORBELL_MASK;

	ग_लिखोl(~msimask, per_cpu_पूर्णांक_base +
	       ARMADA_370_XP_IN_DRBEL_CAUSE_OFFS);

	क्रम (msinr = PCI_MSI_DOORBELL_START;
	     msinr < PCI_MSI_DOORBELL_END; msinr++) अणु
		पूर्णांक irq;

		अगर (!(msimask & BIT(msinr)))
			जारी;

		अगर (is_chained) अणु
			irq = irq_find_mapping(armada_370_xp_msi_inner_करोमुख्य,
					       msinr - PCI_MSI_DOORBELL_START);
			generic_handle_irq(irq);
		पूर्ण अन्यथा अणु
			irq = msinr - PCI_MSI_DOORBELL_START;
			handle_करोमुख्य_irq(armada_370_xp_msi_inner_करोमुख्य,
					  irq, regs);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम armada_370_xp_handle_msi_irq(काष्ठा pt_regs *r, bool b) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम armada_370_xp_mpic_handle_cascade_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ irqmap, irqn, irqsrc, cpuid;
	अचिन्हित पूर्णांक cascade_irq;

	chained_irq_enter(chip, desc);

	irqmap = पढ़ोl_relaxed(per_cpu_पूर्णांक_base + ARMADA_375_PPI_CAUSE);
	cpuid = cpu_logical_map(smp_processor_id());

	क्रम_each_set_bit(irqn, &irqmap, BITS_PER_LONG) अणु
		irqsrc = पढ़ोl_relaxed(मुख्य_पूर्णांक_base +
				       ARMADA_370_XP_INT_SOURCE_CTL(irqn));

		/* Check अगर the पूर्णांकerrupt is not masked on current CPU.
		 * Test IRQ (0-1) and FIQ (8-9) mask bits.
		 */
		अगर (!(irqsrc & ARMADA_370_XP_INT_IRQ_FIQ_MASK(cpuid)))
			जारी;

		अगर (irqn == 1) अणु
			armada_370_xp_handle_msi_irq(शून्य, true);
			जारी;
		पूर्ण

		cascade_irq = irq_find_mapping(armada_370_xp_mpic_करोमुख्य, irqn);
		generic_handle_irq(cascade_irq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम __exception_irq_entry
armada_370_xp_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 irqstat, irqnr;

	करो अणु
		irqstat = पढ़ोl_relaxed(per_cpu_पूर्णांक_base +
					ARMADA_370_XP_CPU_INTACK_OFFS);
		irqnr = irqstat & 0x3FF;

		अगर (irqnr > 1022)
			अवरोध;

		अगर (irqnr > 1) अणु
			handle_करोमुख्य_irq(armada_370_xp_mpic_करोमुख्य,
					  irqnr, regs);
			जारी;
		पूर्ण

		/* MSI handling */
		अगर (irqnr == 1)
			armada_370_xp_handle_msi_irq(regs, false);

#अगर_घोषित CONFIG_SMP
		/* IPI Handling */
		अगर (irqnr == 0) अणु
			अचिन्हित दीर्घ ipimask;
			पूर्णांक ipi;

			ipimask = पढ़ोl_relaxed(per_cpu_पूर्णांक_base +
						ARMADA_370_XP_IN_DRBEL_CAUSE_OFFS)
				& IPI_DOORBELL_MASK;

			क्रम_each_set_bit(ipi, &ipimask, IPI_DOORBELL_END)
				handle_करोमुख्य_irq(ipi_करोमुख्य, ipi, regs);
		पूर्ण
#पूर्ण_अगर

	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक armada_370_xp_mpic_suspend(व्योम)
अणु
	करोorbell_mask_reg = पढ़ोl(per_cpu_पूर्णांक_base +
				  ARMADA_370_XP_IN_DRBEL_MSK_OFFS);
	वापस 0;
पूर्ण

अटल व्योम armada_370_xp_mpic_resume(व्योम)
अणु
	पूर्णांक nirqs;
	irq_hw_number_t irq;

	/* Re-enable पूर्णांकerrupts */
	nirqs = (पढ़ोl(मुख्य_पूर्णांक_base + ARMADA_370_XP_INT_CONTROL) >> 2) & 0x3ff;
	क्रम (irq = 0; irq < nirqs; irq++) अणु
		काष्ठा irq_data *data;
		पूर्णांक virq;

		virq = irq_linear_revmap(armada_370_xp_mpic_करोमुख्य, irq);
		अगर (virq == 0)
			जारी;

		data = irq_get_irq_data(virq);

		अगर (!is_percpu_irq(irq)) अणु
			/* Non per-CPU पूर्णांकerrupts */
			ग_लिखोl(irq, per_cpu_पूर्णांक_base +
			       ARMADA_370_XP_INT_CLEAR_MASK_OFFS);
			अगर (!irqd_irq_disabled(data))
				armada_370_xp_irq_unmask(data);
		पूर्ण अन्यथा अणु
			/* Per-CPU पूर्णांकerrupts */
			ग_लिखोl(irq, मुख्य_पूर्णांक_base +
			       ARMADA_370_XP_INT_SET_ENABLE_OFFS);

			/*
			 * Re-enable on the current CPU,
			 * armada_xp_mpic_reenable_percpu() will take
			 * care of secondary CPUs when they come up.
			 */
			अगर (irq_percpu_is_enabled(virq))
				armada_370_xp_irq_unmask(data);
		पूर्ण
	पूर्ण

	/* Reconfigure करोorbells क्रम IPIs and MSIs */
	ग_लिखोl(करोorbell_mask_reg,
	       per_cpu_पूर्णांक_base + ARMADA_370_XP_IN_DRBEL_MSK_OFFS);
	अगर (करोorbell_mask_reg & IPI_DOORBELL_MASK)
		ग_लिखोl(0, per_cpu_पूर्णांक_base + ARMADA_370_XP_INT_CLEAR_MASK_OFFS);
	अगर (करोorbell_mask_reg & PCI_MSI_DOORBELL_MASK)
		ग_लिखोl(1, per_cpu_पूर्णांक_base + ARMADA_370_XP_INT_CLEAR_MASK_OFFS);

	ipi_resume();
पूर्ण

अटल काष्ठा syscore_ops armada_370_xp_mpic_syscore_ops = अणु
	.suspend	= armada_370_xp_mpic_suspend,
	.resume		= armada_370_xp_mpic_resume,
पूर्ण;

अटल पूर्णांक __init armada_370_xp_mpic_of_init(काष्ठा device_node *node,
					     काष्ठा device_node *parent)
अणु
	काष्ठा resource मुख्य_पूर्णांक_res, per_cpu_पूर्णांक_res;
	पूर्णांक nr_irqs, i;
	u32 control;

	BUG_ON(of_address_to_resource(node, 0, &मुख्य_पूर्णांक_res));
	BUG_ON(of_address_to_resource(node, 1, &per_cpu_पूर्णांक_res));

	BUG_ON(!request_mem_region(मुख्य_पूर्णांक_res.start,
				   resource_size(&मुख्य_पूर्णांक_res),
				   node->full_name));
	BUG_ON(!request_mem_region(per_cpu_पूर्णांक_res.start,
				   resource_size(&per_cpu_पूर्णांक_res),
				   node->full_name));

	मुख्य_पूर्णांक_base = ioremap(मुख्य_पूर्णांक_res.start,
				resource_size(&मुख्य_पूर्णांक_res));
	BUG_ON(!मुख्य_पूर्णांक_base);

	per_cpu_पूर्णांक_base = ioremap(per_cpu_पूर्णांक_res.start,
				   resource_size(&per_cpu_पूर्णांक_res));
	BUG_ON(!per_cpu_पूर्णांक_base);

	control = पढ़ोl(मुख्य_पूर्णांक_base + ARMADA_370_XP_INT_CONTROL);
	nr_irqs = (control >> 2) & 0x3ff;

	क्रम (i = 0; i < nr_irqs; i++)
		ग_लिखोl(i, मुख्य_पूर्णांक_base + ARMADA_370_XP_INT_CLEAR_ENABLE_OFFS);

	armada_370_xp_mpic_करोमुख्य =
		irq_करोमुख्य_add_linear(node, nr_irqs,
				&armada_370_xp_mpic_irq_ops, शून्य);
	BUG_ON(!armada_370_xp_mpic_करोमुख्य);
	irq_करोमुख्य_update_bus_token(armada_370_xp_mpic_करोमुख्य, DOMAIN_BUS_WIRED);

	/* Setup क्रम the boot CPU */
	armada_xp_mpic_perf_init();
	armada_xp_mpic_smp_cpu_init();

	armada_370_xp_msi_init(node, मुख्य_पूर्णांक_res.start);

	parent_irq = irq_of_parse_and_map(node, 0);
	अगर (parent_irq <= 0) अणु
		irq_set_शेष_host(armada_370_xp_mpic_करोमुख्य);
		set_handle_irq(armada_370_xp_handle_irq);
#अगर_घोषित CONFIG_SMP
		armada_xp_ipi_init(node);
		cpuhp_setup_state_nocalls(CPUHP_AP_IRQ_ARMADA_XP_STARTING,
					  "irqchip/armada/ipi:starting",
					  armada_xp_mpic_starting_cpu, शून्य);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_SMP
		cpuhp_setup_state_nocalls(CPUHP_AP_IRQ_ARMADA_XP_STARTING,
					  "irqchip/armada/cascade:starting",
					  mpic_cascaded_starting_cpu, शून्य);
#पूर्ण_अगर
		irq_set_chained_handler(parent_irq,
					armada_370_xp_mpic_handle_cascade_irq);
	पूर्ण

	रेजिस्टर_syscore_ops(&armada_370_xp_mpic_syscore_ops);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(armada_370_xp_mpic, "marvell,mpic", armada_370_xp_mpic_of_init);
