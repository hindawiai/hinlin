<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Broadcom Corporation
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>

#समावेश "pcie-iproc.h"

#घोषणा IPROC_MSI_INTR_EN_SHIFT        11
#घोषणा IPROC_MSI_INTR_EN              BIT(IPROC_MSI_INTR_EN_SHIFT)
#घोषणा IPROC_MSI_INT_N_EVENT_SHIFT    1
#घोषणा IPROC_MSI_INT_N_EVENT          BIT(IPROC_MSI_INT_N_EVENT_SHIFT)
#घोषणा IPROC_MSI_EQ_EN_SHIFT          0
#घोषणा IPROC_MSI_EQ_EN                BIT(IPROC_MSI_EQ_EN_SHIFT)

#घोषणा IPROC_MSI_EQ_MASK              0x3f

/* Max number of GIC पूर्णांकerrupts */
#घोषणा NR_HW_IRQS                     6

/* Number of entries in each event queue */
#घोषणा EQ_LEN                         64

/* Size of each event queue memory region */
#घोषणा EQ_MEM_REGION_SIZE             SZ_4K

/* Size of each MSI address region */
#घोषणा MSI_MEM_REGION_SIZE            SZ_4K

क्रमागत iproc_msi_reg अणु
	IPROC_MSI_EQ_PAGE = 0,
	IPROC_MSI_EQ_PAGE_UPPER,
	IPROC_MSI_PAGE,
	IPROC_MSI_PAGE_UPPER,
	IPROC_MSI_CTRL,
	IPROC_MSI_EQ_HEAD,
	IPROC_MSI_EQ_TAIL,
	IPROC_MSI_INTS_EN,
	IPROC_MSI_REG_SIZE,
पूर्ण;

काष्ठा iproc_msi;

/**
 * iProc MSI group
 *
 * One MSI group is allocated per GIC पूर्णांकerrupt, serviced by one iProc MSI
 * event queue.
 *
 * @msi: poपूर्णांकer to iProc MSI data
 * @gic_irq: GIC पूर्णांकerrupt
 * @eq: Event queue number
 */
काष्ठा iproc_msi_grp अणु
	काष्ठा iproc_msi *msi;
	पूर्णांक gic_irq;
	अचिन्हित पूर्णांक eq;
पूर्ण;

/**
 * iProc event queue based MSI
 *
 * Only meant to be used on platक्रमms without MSI support पूर्णांकegrated पूर्णांकo the
 * GIC.
 *
 * @pcie: poपूर्णांकer to iProc PCIe data
 * @reg_offsets: MSI रेजिस्टर offsets
 * @grps: MSI groups
 * @nr_irqs: number of total पूर्णांकerrupts connected to GIC
 * @nr_cpus: number of toal CPUs
 * @has_पूर्णांकen_reg: indicates the MSI पूर्णांकerrupt enable रेजिस्टर needs to be
 * set explicitly (required क्रम some legacy platक्रमms)
 * @biपंचांगap: MSI vector biपंचांगap
 * @biपंचांगap_lock: lock to protect access to the MSI biपंचांगap
 * @nr_msi_vecs: total number of MSI vectors
 * @inner_करोमुख्य: inner IRQ करोमुख्य
 * @msi_करोमुख्य: MSI IRQ करोमुख्य
 * @nr_eq_region: required number of 4K aligned memory region क्रम MSI event
 * queues
 * @nr_msi_region: required number of 4K aligned address region क्रम MSI posted
 * ग_लिखोs
 * @eq_cpu: poपूर्णांकer to allocated memory region क्रम MSI event queues
 * @eq_dma: DMA address of MSI event queues
 * @msi_addr: MSI address
 */
काष्ठा iproc_msi अणु
	काष्ठा iproc_pcie *pcie;
	स्थिर u16 (*reg_offsets)[IPROC_MSI_REG_SIZE];
	काष्ठा iproc_msi_grp *grps;
	पूर्णांक nr_irqs;
	पूर्णांक nr_cpus;
	bool has_पूर्णांकen_reg;
	अचिन्हित दीर्घ *biपंचांगap;
	काष्ठा mutex biपंचांगap_lock;
	अचिन्हित पूर्णांक nr_msi_vecs;
	काष्ठा irq_करोमुख्य *inner_करोमुख्य;
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	अचिन्हित पूर्णांक nr_eq_region;
	अचिन्हित पूर्णांक nr_msi_region;
	व्योम *eq_cpu;
	dma_addr_t eq_dma;
	phys_addr_t msi_addr;
पूर्ण;

अटल स्थिर u16 iproc_msi_reg_paxb[NR_HW_IRQS][IPROC_MSI_REG_SIZE] = अणु
	अणु 0x200, 0x2c0, 0x204, 0x2c4, 0x210, 0x250, 0x254, 0x208 पूर्ण,
	अणु 0x200, 0x2c0, 0x204, 0x2c4, 0x214, 0x258, 0x25c, 0x208 पूर्ण,
	अणु 0x200, 0x2c0, 0x204, 0x2c4, 0x218, 0x260, 0x264, 0x208 पूर्ण,
	अणु 0x200, 0x2c0, 0x204, 0x2c4, 0x21c, 0x268, 0x26c, 0x208 पूर्ण,
	अणु 0x200, 0x2c0, 0x204, 0x2c4, 0x220, 0x270, 0x274, 0x208 पूर्ण,
	अणु 0x200, 0x2c0, 0x204, 0x2c4, 0x224, 0x278, 0x27c, 0x208 पूर्ण,
पूर्ण;

अटल स्थिर u16 iproc_msi_reg_paxc[NR_HW_IRQS][IPROC_MSI_REG_SIZE] = अणु
	अणु 0xc00, 0xc04, 0xc08, 0xc0c, 0xc40, 0xc50, 0xc60 पूर्ण,
	अणु 0xc10, 0xc14, 0xc18, 0xc1c, 0xc44, 0xc54, 0xc64 पूर्ण,
	अणु 0xc20, 0xc24, 0xc28, 0xc2c, 0xc48, 0xc58, 0xc68 पूर्ण,
	अणु 0xc30, 0xc34, 0xc38, 0xc3c, 0xc4c, 0xc5c, 0xc6c पूर्ण,
पूर्ण;

अटल अंतरभूत u32 iproc_msi_पढ़ो_reg(काष्ठा iproc_msi *msi,
				     क्रमागत iproc_msi_reg reg,
				     अचिन्हित पूर्णांक eq)
अणु
	काष्ठा iproc_pcie *pcie = msi->pcie;

	वापस पढ़ोl_relaxed(pcie->base + msi->reg_offsets[eq][reg]);
पूर्ण

अटल अंतरभूत व्योम iproc_msi_ग_लिखो_reg(काष्ठा iproc_msi *msi,
				       क्रमागत iproc_msi_reg reg,
				       पूर्णांक eq, u32 val)
अणु
	काष्ठा iproc_pcie *pcie = msi->pcie;

	ग_लिखोl_relaxed(val, pcie->base + msi->reg_offsets[eq][reg]);
पूर्ण

अटल अंतरभूत u32 hwirq_to_group(काष्ठा iproc_msi *msi, अचिन्हित दीर्घ hwirq)
अणु
	वापस (hwirq % msi->nr_irqs);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक iproc_msi_addr_offset(काष्ठा iproc_msi *msi,
						 अचिन्हित दीर्घ hwirq)
अणु
	अगर (msi->nr_msi_region > 1)
		वापस hwirq_to_group(msi, hwirq) * MSI_MEM_REGION_SIZE;
	अन्यथा
		वापस hwirq_to_group(msi, hwirq) * माप(u32);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक iproc_msi_eq_offset(काष्ठा iproc_msi *msi, u32 eq)
अणु
	अगर (msi->nr_eq_region > 1)
		वापस eq * EQ_MEM_REGION_SIZE;
	अन्यथा
		वापस eq * EQ_LEN * माप(u32);
पूर्ण

अटल काष्ठा irq_chip iproc_msi_irq_chip = अणु
	.name = "iProc-MSI",
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info iproc_msi_करोमुख्य_info = अणु
	.flags = MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		MSI_FLAG_MULTI_PCI_MSI | MSI_FLAG_PCI_MSIX,
	.chip = &iproc_msi_irq_chip,
पूर्ण;

/*
 * In iProc PCIe core, each MSI group is serviced by a GIC पूर्णांकerrupt and a
 * dedicated event queue.  Each MSI group can support up to 64 MSI vectors.
 *
 * The number of MSI groups varies between dअगरferent iProc SoCs.  The total
 * number of CPU cores also varies.  To support MSI IRQ affinity, we
 * distribute GIC पूर्णांकerrupts across all available CPUs.  MSI vector is moved
 * from one GIC पूर्णांकerrupt to another to steer to the target CPU.
 *
 * Assuming:
 * - the number of MSI groups is M
 * - the number of CPU cores is N
 * - M is always a multiple of N
 *
 * Total number of raw MSI vectors = M * 64
 * Total number of supported MSI vectors = (M * 64) / N
 */
अटल अंतरभूत पूर्णांक hwirq_to_cpu(काष्ठा iproc_msi *msi, अचिन्हित दीर्घ hwirq)
अणु
	वापस (hwirq % msi->nr_cpus);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hwirq_to_canonical_hwirq(काष्ठा iproc_msi *msi,
						     अचिन्हित दीर्घ hwirq)
अणु
	वापस (hwirq - hwirq_to_cpu(msi, hwirq));
पूर्ण

अटल पूर्णांक iproc_msi_irq_set_affinity(काष्ठा irq_data *data,
				      स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा iproc_msi *msi = irq_data_get_irq_chip_data(data);
	पूर्णांक target_cpu = cpumask_first(mask);
	पूर्णांक curr_cpu;
	पूर्णांक ret;

	curr_cpu = hwirq_to_cpu(msi, data->hwirq);
	अगर (curr_cpu == target_cpu)
		ret = IRQ_SET_MASK_OK_DONE;
	अन्यथा अणु
		/* steer MSI to the target CPU */
		data->hwirq = hwirq_to_canonical_hwirq(msi, data->hwirq) + target_cpu;
		ret = IRQ_SET_MASK_OK;
	पूर्ण

	irq_data_update_effective_affinity(data, cpumask_of(target_cpu));

	वापस ret;
पूर्ण

अटल व्योम iproc_msi_irq_compose_msi_msg(काष्ठा irq_data *data,
					  काष्ठा msi_msg *msg)
अणु
	काष्ठा iproc_msi *msi = irq_data_get_irq_chip_data(data);
	dma_addr_t addr;

	addr = msi->msi_addr + iproc_msi_addr_offset(msi, data->hwirq);
	msg->address_lo = lower_32_bits(addr);
	msg->address_hi = upper_32_bits(addr);
	msg->data = data->hwirq << 5;
पूर्ण

अटल काष्ठा irq_chip iproc_msi_bottom_irq_chip = अणु
	.name = "MSI",
	.irq_set_affinity = iproc_msi_irq_set_affinity,
	.irq_compose_msi_msg = iproc_msi_irq_compose_msi_msg,
पूर्ण;

अटल पूर्णांक iproc_msi_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				      अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				      व्योम *args)
अणु
	काष्ठा iproc_msi *msi = करोमुख्य->host_data;
	पूर्णांक hwirq, i;

	mutex_lock(&msi->biपंचांगap_lock);

	/* Allocate 'nr_cpus' number of MSI vectors each समय */
	hwirq = biपंचांगap_find_next_zero_area(msi->biपंचांगap, msi->nr_msi_vecs, 0,
					   msi->nr_cpus, 0);
	अगर (hwirq < msi->nr_msi_vecs) अणु
		biपंचांगap_set(msi->biपंचांगap, hwirq, msi->nr_cpus);
	पूर्ण अन्यथा अणु
		mutex_unlock(&msi->biपंचांगap_lock);
		वापस -ENOSPC;
	पूर्ण

	mutex_unlock(&msi->biपंचांगap_lock);

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, hwirq + i,
				    &iproc_msi_bottom_irq_chip,
				    करोमुख्य->host_data, handle_simple_irq,
				    शून्य, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iproc_msi_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				      अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा iproc_msi *msi = irq_data_get_irq_chip_data(data);
	अचिन्हित पूर्णांक hwirq;

	mutex_lock(&msi->biपंचांगap_lock);

	hwirq = hwirq_to_canonical_hwirq(msi, data->hwirq);
	biपंचांगap_clear(msi->biपंचांगap, hwirq, msi->nr_cpus);

	mutex_unlock(&msi->biपंचांगap_lock);

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops msi_करोमुख्य_ops = अणु
	.alloc = iproc_msi_irq_करोमुख्य_alloc,
	.मुक्त = iproc_msi_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल अंतरभूत u32 decode_msi_hwirq(काष्ठा iproc_msi *msi, u32 eq, u32 head)
अणु
	u32 __iomem *msg;
	u32 hwirq;
	अचिन्हित पूर्णांक offs;

	offs = iproc_msi_eq_offset(msi, eq) + head * माप(u32);
	msg = (u32 __iomem *)(msi->eq_cpu + offs);
	hwirq = पढ़ोl(msg);
	hwirq = (hwirq >> 5) + (hwirq & 0x1f);

	/*
	 * Since we have multiple hwirq mapped to a single MSI vector,
	 * now we need to derive the hwirq at CPU0.  It can then be used to
	 * mapped back to virq.
	 */
	वापस hwirq_to_canonical_hwirq(msi, hwirq);
पूर्ण

अटल व्योम iproc_msi_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा iproc_msi_grp *grp;
	काष्ठा iproc_msi *msi;
	u32 eq, head, tail, nr_events;
	अचिन्हित दीर्घ hwirq;
	पूर्णांक virq;

	chained_irq_enter(chip, desc);

	grp = irq_desc_get_handler_data(desc);
	msi = grp->msi;
	eq = grp->eq;

	/*
	 * iProc MSI event queue is tracked by head and tail poपूर्णांकers.  Head
	 * poपूर्णांकer indicates the next entry (MSI data) to be consumed by SW in
	 * the queue and needs to be updated by SW.  iProc MSI core uses the
	 * tail poपूर्णांकer as the next data insertion poपूर्णांक.
	 *
	 * Entries between head and tail poपूर्णांकers contain valid MSI data.  MSI
	 * data is guaranteed to be in the event queue memory beक्रमe the tail
	 * poपूर्णांकer is updated by the iProc MSI core.
	 */
	head = iproc_msi_पढ़ो_reg(msi, IPROC_MSI_EQ_HEAD,
				  eq) & IPROC_MSI_EQ_MASK;
	करो अणु
		tail = iproc_msi_पढ़ो_reg(msi, IPROC_MSI_EQ_TAIL,
					  eq) & IPROC_MSI_EQ_MASK;

		/*
		 * Figure out total number of events (MSI data) to be
		 * processed.
		 */
		nr_events = (tail < head) ?
			(EQ_LEN - (head - tail)) : (tail - head);
		अगर (!nr_events)
			अवरोध;

		/* process all outstanding events */
		जबतक (nr_events--) अणु
			hwirq = decode_msi_hwirq(msi, eq, head);
			virq = irq_find_mapping(msi->inner_करोमुख्य, hwirq);
			generic_handle_irq(virq);

			head++;
			head %= EQ_LEN;
		पूर्ण

		/*
		 * Now all outstanding events have been processed.  Update the
		 * head poपूर्णांकer.
		 */
		iproc_msi_ग_लिखो_reg(msi, IPROC_MSI_EQ_HEAD, eq, head);

		/*
		 * Now go पढ़ो the tail poपूर्णांकer again to see अगर there are new
		 * outstanding events that came in during the above winकरोw.
		 */
	पूर्ण जबतक (true);

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम iproc_msi_enable(काष्ठा iproc_msi *msi)
अणु
	पूर्णांक i, eq;
	u32 val;

	/* Program memory region क्रम each event queue */
	क्रम (i = 0; i < msi->nr_eq_region; i++) अणु
		dma_addr_t addr = msi->eq_dma + (i * EQ_MEM_REGION_SIZE);

		iproc_msi_ग_लिखो_reg(msi, IPROC_MSI_EQ_PAGE, i,
				    lower_32_bits(addr));
		iproc_msi_ग_लिखो_reg(msi, IPROC_MSI_EQ_PAGE_UPPER, i,
				    upper_32_bits(addr));
	पूर्ण

	/* Program address region क्रम MSI posted ग_लिखोs */
	क्रम (i = 0; i < msi->nr_msi_region; i++) अणु
		phys_addr_t addr = msi->msi_addr + (i * MSI_MEM_REGION_SIZE);

		iproc_msi_ग_लिखो_reg(msi, IPROC_MSI_PAGE, i,
				    lower_32_bits(addr));
		iproc_msi_ग_लिखो_reg(msi, IPROC_MSI_PAGE_UPPER, i,
				    upper_32_bits(addr));
	पूर्ण

	क्रम (eq = 0; eq < msi->nr_irqs; eq++) अणु
		/* Enable MSI event queue */
		val = IPROC_MSI_INTR_EN | IPROC_MSI_INT_N_EVENT |
			IPROC_MSI_EQ_EN;
		iproc_msi_ग_लिखो_reg(msi, IPROC_MSI_CTRL, eq, val);

		/*
		 * Some legacy platक्रमms require the MSI पूर्णांकerrupt enable
		 * रेजिस्टर to be set explicitly.
		 */
		अगर (msi->has_पूर्णांकen_reg) अणु
			val = iproc_msi_पढ़ो_reg(msi, IPROC_MSI_INTS_EN, eq);
			val |= BIT(eq);
			iproc_msi_ग_लिखो_reg(msi, IPROC_MSI_INTS_EN, eq, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम iproc_msi_disable(काष्ठा iproc_msi *msi)
अणु
	u32 eq, val;

	क्रम (eq = 0; eq < msi->nr_irqs; eq++) अणु
		अगर (msi->has_पूर्णांकen_reg) अणु
			val = iproc_msi_पढ़ो_reg(msi, IPROC_MSI_INTS_EN, eq);
			val &= ~BIT(eq);
			iproc_msi_ग_लिखो_reg(msi, IPROC_MSI_INTS_EN, eq, val);
		पूर्ण

		val = iproc_msi_पढ़ो_reg(msi, IPROC_MSI_CTRL, eq);
		val &= ~(IPROC_MSI_INTR_EN | IPROC_MSI_INT_N_EVENT |
			 IPROC_MSI_EQ_EN);
		iproc_msi_ग_लिखो_reg(msi, IPROC_MSI_CTRL, eq, val);
	पूर्ण
पूर्ण

अटल पूर्णांक iproc_msi_alloc_करोमुख्यs(काष्ठा device_node *node,
				   काष्ठा iproc_msi *msi)
अणु
	msi->inner_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, msi->nr_msi_vecs,
						  &msi_करोमुख्य_ops, msi);
	अगर (!msi->inner_करोमुख्य)
		वापस -ENOMEM;

	msi->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(of_node_to_fwnode(node),
						    &iproc_msi_करोमुख्य_info,
						    msi->inner_करोमुख्य);
	अगर (!msi->msi_करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(msi->inner_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iproc_msi_मुक्त_करोमुख्यs(काष्ठा iproc_msi *msi)
अणु
	अगर (msi->msi_करोमुख्य)
		irq_करोमुख्य_हटाओ(msi->msi_करोमुख्य);

	अगर (msi->inner_करोमुख्य)
		irq_करोमुख्य_हटाओ(msi->inner_करोमुख्य);
पूर्ण

अटल व्योम iproc_msi_irq_मुक्त(काष्ठा iproc_msi *msi, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम (i = cpu; i < msi->nr_irqs; i += msi->nr_cpus) अणु
		irq_set_chained_handler_and_data(msi->grps[i].gic_irq,
						 शून्य, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक iproc_msi_irq_setup(काष्ठा iproc_msi *msi, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i, ret;
	cpumask_var_t mask;
	काष्ठा iproc_pcie *pcie = msi->pcie;

	क्रम (i = cpu; i < msi->nr_irqs; i += msi->nr_cpus) अणु
		irq_set_chained_handler_and_data(msi->grps[i].gic_irq,
						 iproc_msi_handler,
						 &msi->grps[i]);
		/* Dedicate GIC पूर्णांकerrupt to each CPU core */
		अगर (alloc_cpumask_var(&mask, GFP_KERNEL)) अणु
			cpumask_clear(mask);
			cpumask_set_cpu(cpu, mask);
			ret = irq_set_affinity(msi->grps[i].gic_irq, mask);
			अगर (ret)
				dev_err(pcie->dev,
					"failed to set affinity for IRQ%d\n",
					msi->grps[i].gic_irq);
			मुक्त_cpumask_var(mask);
		पूर्ण अन्यथा अणु
			dev_err(pcie->dev, "failed to alloc CPU mask\n");
			ret = -EINVAL;
		पूर्ण

		अगर (ret) अणु
			/* Free all configured/unconfigured IRQs */
			iproc_msi_irq_मुक्त(msi, cpu);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iproc_msi_init(काष्ठा iproc_pcie *pcie, काष्ठा device_node *node)
अणु
	काष्ठा iproc_msi *msi;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक cpu;

	अगर (!of_device_is_compatible(node, "brcm,iproc-msi"))
		वापस -ENODEV;

	अगर (!of_find_property(node, "msi-controller", शून्य))
		वापस -ENODEV;

	अगर (pcie->msi)
		वापस -EBUSY;

	msi = devm_kzalloc(pcie->dev, माप(*msi), GFP_KERNEL);
	अगर (!msi)
		वापस -ENOMEM;

	msi->pcie = pcie;
	pcie->msi = msi;
	msi->msi_addr = pcie->base_addr;
	mutex_init(&msi->biपंचांगap_lock);
	msi->nr_cpus = num_possible_cpus();

	msi->nr_irqs = of_irq_count(node);
	अगर (!msi->nr_irqs) अणु
		dev_err(pcie->dev, "found no MSI GIC interrupt\n");
		वापस -ENODEV;
	पूर्ण

	अगर (msi->nr_irqs > NR_HW_IRQS) अणु
		dev_warn(pcie->dev, "too many MSI GIC interrupts defined %d\n",
			 msi->nr_irqs);
		msi->nr_irqs = NR_HW_IRQS;
	पूर्ण

	अगर (msi->nr_irqs < msi->nr_cpus) अणु
		dev_err(pcie->dev,
			"not enough GIC interrupts for MSI affinity\n");
		वापस -EINVAL;
	पूर्ण

	अगर (msi->nr_irqs % msi->nr_cpus != 0) अणु
		msi->nr_irqs -= msi->nr_irqs % msi->nr_cpus;
		dev_warn(pcie->dev, "Reducing number of interrupts to %d\n",
			 msi->nr_irqs);
	पूर्ण

	चयन (pcie->type) अणु
	हाल IPROC_PCIE_PAXB_BCMA:
	हाल IPROC_PCIE_PAXB:
		msi->reg_offsets = iproc_msi_reg_paxb;
		msi->nr_eq_region = 1;
		msi->nr_msi_region = 1;
		अवरोध;
	हाल IPROC_PCIE_PAXC:
		msi->reg_offsets = iproc_msi_reg_paxc;
		msi->nr_eq_region = msi->nr_irqs;
		msi->nr_msi_region = msi->nr_irqs;
		अवरोध;
	शेष:
		dev_err(pcie->dev, "incompatible iProc PCIe interface\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_find_property(node, "brcm,pcie-msi-inten", शून्य))
		msi->has_पूर्णांकen_reg = true;

	msi->nr_msi_vecs = msi->nr_irqs * EQ_LEN;
	msi->biपंचांगap = devm_kसुस्मृति(pcie->dev, BITS_TO_LONGS(msi->nr_msi_vecs),
				   माप(*msi->biपंचांगap), GFP_KERNEL);
	अगर (!msi->biपंचांगap)
		वापस -ENOMEM;

	msi->grps = devm_kसुस्मृति(pcie->dev, msi->nr_irqs, माप(*msi->grps),
				 GFP_KERNEL);
	अगर (!msi->grps)
		वापस -ENOMEM;

	क्रम (i = 0; i < msi->nr_irqs; i++) अणु
		अचिन्हित पूर्णांक irq = irq_of_parse_and_map(node, i);

		अगर (!irq) अणु
			dev_err(pcie->dev, "unable to parse/map interrupt\n");
			ret = -ENODEV;
			जाओ मुक्त_irqs;
		पूर्ण
		msi->grps[i].gic_irq = irq;
		msi->grps[i].msi = msi;
		msi->grps[i].eq = i;
	पूर्ण

	/* Reserve memory क्रम event queue and make sure memories are zeroed */
	msi->eq_cpu = dma_alloc_coherent(pcie->dev,
					 msi->nr_eq_region * EQ_MEM_REGION_SIZE,
					 &msi->eq_dma, GFP_KERNEL);
	अगर (!msi->eq_cpu) अणु
		ret = -ENOMEM;
		जाओ मुक्त_irqs;
	पूर्ण

	ret = iproc_msi_alloc_करोमुख्यs(node, msi);
	अगर (ret) अणु
		dev_err(pcie->dev, "failed to create MSI domains\n");
		जाओ मुक्त_eq_dma;
	पूर्ण

	क्रम_each_online_cpu(cpu) अणु
		ret = iproc_msi_irq_setup(msi, cpu);
		अगर (ret)
			जाओ मुक्त_msi_irq;
	पूर्ण

	iproc_msi_enable(msi);

	वापस 0;

मुक्त_msi_irq:
	क्रम_each_online_cpu(cpu)
		iproc_msi_irq_मुक्त(msi, cpu);
	iproc_msi_मुक्त_करोमुख्यs(msi);

मुक्त_eq_dma:
	dma_मुक्त_coherent(pcie->dev, msi->nr_eq_region * EQ_MEM_REGION_SIZE,
			  msi->eq_cpu, msi->eq_dma);

मुक्त_irqs:
	क्रम (i = 0; i < msi->nr_irqs; i++) अणु
		अगर (msi->grps[i].gic_irq)
			irq_dispose_mapping(msi->grps[i].gic_irq);
	पूर्ण
	pcie->msi = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(iproc_msi_init);

व्योम iproc_msi_निकास(काष्ठा iproc_pcie *pcie)
अणु
	काष्ठा iproc_msi *msi = pcie->msi;
	अचिन्हित पूर्णांक i, cpu;

	अगर (!msi)
		वापस;

	iproc_msi_disable(msi);

	क्रम_each_online_cpu(cpu)
		iproc_msi_irq_मुक्त(msi, cpu);

	iproc_msi_मुक्त_करोमुख्यs(msi);

	dma_मुक्त_coherent(pcie->dev, msi->nr_eq_region * EQ_MEM_REGION_SIZE,
			  msi->eq_cpu, msi->eq_dma);

	क्रम (i = 0; i < msi->nr_irqs; i++) अणु
		अगर (msi->grps[i].gic_irq)
			irq_dispose_mapping(msi->grps[i].gic_irq);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(iproc_msi_निकास);
