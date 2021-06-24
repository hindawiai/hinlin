<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * APM X-Gene MSI Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Tanmay Inamdar <tinamdar@apm.com>
 *	   Duc Dang <dhdang@apm.com>
 */
#समावेश <linux/cpu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_pci.h>

#घोषणा MSI_IR0			0x000000
#घोषणा MSI_INT0		0x800000
#घोषणा IDX_PER_GROUP		8
#घोषणा IRQS_PER_IDX		16
#घोषणा NR_HW_IRQS		16
#घोषणा NR_MSI_VEC		(IDX_PER_GROUP * IRQS_PER_IDX * NR_HW_IRQS)

काष्ठा xgene_msi_group अणु
	काष्ठा xgene_msi	*msi;
	पूर्णांक			gic_irq;
	u32			msi_grp;
पूर्ण;

काष्ठा xgene_msi अणु
	काष्ठा device_node	*node;
	काष्ठा irq_करोमुख्य	*inner_करोमुख्य;
	काष्ठा irq_करोमुख्य	*msi_करोमुख्य;
	u64			msi_addr;
	व्योम __iomem		*msi_regs;
	अचिन्हित दीर्घ		*biपंचांगap;
	काष्ठा mutex		biपंचांगap_lock;
	काष्ठा xgene_msi_group	*msi_groups;
	पूर्णांक			num_cpus;
पूर्ण;

/* Global data */
अटल काष्ठा xgene_msi xgene_msi_ctrl;

अटल काष्ठा irq_chip xgene_msi_top_irq_chip = अणु
	.name		= "X-Gene1 MSI",
	.irq_enable	= pci_msi_unmask_irq,
	.irq_disable	= pci_msi_mask_irq,
	.irq_mask	= pci_msi_mask_irq,
	.irq_unmask	= pci_msi_unmask_irq,
पूर्ण;

अटल काष्ठा  msi_करोमुख्य_info xgene_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		  MSI_FLAG_PCI_MSIX),
	.chip	= &xgene_msi_top_irq_chip,
पूर्ण;

/*
 * X-Gene v1 has 16 groups of MSI termination रेजिस्टरs MSInIRx, where
 * n is group number (0..F), x is index of रेजिस्टरs in each group (0..7)
 * The रेजिस्टर layout is as follows:
 * MSI0IR0			base_addr
 * MSI0IR1			base_addr +  0x10000
 * ...				...
 * MSI0IR6			base_addr +  0x60000
 * MSI0IR7			base_addr +  0x70000
 * MSI1IR0			base_addr +  0x80000
 * MSI1IR1			base_addr +  0x90000
 * ...				...
 * MSI1IR7			base_addr +  0xF0000
 * MSI2IR0			base_addr + 0x100000
 * ...				...
 * MSIFIR0			base_addr + 0x780000
 * MSIFIR1			base_addr + 0x790000
 * ...				...
 * MSIFIR7			base_addr + 0x7F0000
 * MSIINT0			base_addr + 0x800000
 * MSIINT1			base_addr + 0x810000
 * ...				...
 * MSIINTF			base_addr + 0x8F0000
 *
 * Each index रेजिस्टर supports 16 MSI vectors (0..15) to generate पूर्णांकerrupt.
 * There are total 16 GIC IRQs asचिन्हित क्रम these 16 groups of MSI termination
 * रेजिस्टरs.
 *
 * Each MSI termination group has 1 MSIINTn रेजिस्टर (n is 0..15) to indicate
 * the MSI pending status caused by 1 of its 8 index रेजिस्टरs.
 */

/* MSInIRx पढ़ो helper */
अटल u32 xgene_msi_ir_पढ़ो(काष्ठा xgene_msi *msi,
				    u32 msi_grp, u32 msir_idx)
अणु
	वापस पढ़ोl_relaxed(msi->msi_regs + MSI_IR0 +
			      (msi_grp << 19) + (msir_idx << 16));
पूर्ण

/* MSIINTn पढ़ो helper */
अटल u32 xgene_msi_पूर्णांक_पढ़ो(काष्ठा xgene_msi *msi, u32 msi_grp)
अणु
	वापस पढ़ोl_relaxed(msi->msi_regs + MSI_INT0 + (msi_grp << 16));
पूर्ण

/*
 * With 2048 MSI vectors supported, the MSI message can be स्थिरructed using
 * following scheme:
 * - Divide पूर्णांकo 8 256-vector groups
 *		Group 0: 0-255
 *		Group 1: 256-511
 *		Group 2: 512-767
 *		...
 *		Group 7: 1792-2047
 * - Each 256-vector group is भागided पूर्णांकo 16 16-vector groups
 *	As an example: 16 16-vector groups क्रम 256-vector group 0-255 is
 *		Group 0: 0-15
 *		Group 1: 16-32
 *		...
 *		Group 15: 240-255
 * - The termination address of MSI vector in 256-vector group n and 16-vector
 *   group x is the address of MSIxIRn
 * - The data क्रम MSI vector in 16-vector group x is x
 */
अटल u32 hwirq_to_reg_set(अचिन्हित दीर्घ hwirq)
अणु
	वापस (hwirq / (NR_HW_IRQS * IRQS_PER_IDX));
पूर्ण

अटल u32 hwirq_to_group(अचिन्हित दीर्घ hwirq)
अणु
	वापस (hwirq % NR_HW_IRQS);
पूर्ण

अटल u32 hwirq_to_msi_data(अचिन्हित दीर्घ hwirq)
अणु
	वापस ((hwirq / NR_HW_IRQS) % IRQS_PER_IDX);
पूर्ण

अटल व्योम xgene_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा xgene_msi *msi = irq_data_get_irq_chip_data(data);
	u32 reg_set = hwirq_to_reg_set(data->hwirq);
	u32 group = hwirq_to_group(data->hwirq);
	u64 target_addr = msi->msi_addr + (((8 * group) + reg_set) << 16);

	msg->address_hi = upper_32_bits(target_addr);
	msg->address_lo = lower_32_bits(target_addr);
	msg->data = hwirq_to_msi_data(data->hwirq);
पूर्ण

/*
 * X-Gene v1 only has 16 MSI GIC IRQs क्रम 2048 MSI vectors.  To मुख्यtain
 * the expected behaviour of .set_affinity क्रम each MSI पूर्णांकerrupt, the 16
 * MSI GIC IRQs are अटलally allocated to 8 X-Gene v1 cores (2 GIC IRQs
 * क्रम each core).  The MSI vector is moved fom 1 MSI GIC IRQ to another
 * MSI GIC IRQ to steer its MSI पूर्णांकerrupt to correct X-Gene v1 core.  As a
 * consequence, the total MSI vectors that X-Gene v1 supports will be
 * reduced to 256 (2048/8) vectors.
 */
अटल पूर्णांक hwirq_to_cpu(अचिन्हित दीर्घ hwirq)
अणु
	वापस (hwirq % xgene_msi_ctrl.num_cpus);
पूर्ण

अटल अचिन्हित दीर्घ hwirq_to_canonical_hwirq(अचिन्हित दीर्घ hwirq)
अणु
	वापस (hwirq - hwirq_to_cpu(hwirq));
पूर्ण

अटल पूर्णांक xgene_msi_set_affinity(काष्ठा irq_data *irqdata,
				  स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	पूर्णांक target_cpu = cpumask_first(mask);
	पूर्णांक curr_cpu;

	curr_cpu = hwirq_to_cpu(irqdata->hwirq);
	अगर (curr_cpu == target_cpu)
		वापस IRQ_SET_MASK_OK_DONE;

	/* Update MSI number to target the new CPU */
	irqdata->hwirq = hwirq_to_canonical_hwirq(irqdata->hwirq) + target_cpu;

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल काष्ठा irq_chip xgene_msi_bottom_irq_chip = अणु
	.name			= "MSI",
	.irq_set_affinity       = xgene_msi_set_affinity,
	.irq_compose_msi_msg	= xgene_compose_msi_msg,
पूर्ण;

अटल पूर्णांक xgene_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा xgene_msi *msi = करोमुख्य->host_data;
	पूर्णांक msi_irq;

	mutex_lock(&msi->biपंचांगap_lock);

	msi_irq = biपंचांगap_find_next_zero_area(msi->biपंचांगap, NR_MSI_VEC, 0,
					     msi->num_cpus, 0);
	अगर (msi_irq < NR_MSI_VEC)
		biपंचांगap_set(msi->biपंचांगap, msi_irq, msi->num_cpus);
	अन्यथा
		msi_irq = -ENOSPC;

	mutex_unlock(&msi->biपंचांगap_lock);

	अगर (msi_irq < 0)
		वापस msi_irq;

	irq_करोमुख्य_set_info(करोमुख्य, virq, msi_irq,
			    &xgene_msi_bottom_irq_chip, करोमुख्य->host_data,
			    handle_simple_irq, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल व्योम xgene_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				  अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा xgene_msi *msi = irq_data_get_irq_chip_data(d);
	u32 hwirq;

	mutex_lock(&msi->biपंचांगap_lock);

	hwirq = hwirq_to_canonical_hwirq(d->hwirq);
	biपंचांगap_clear(msi->biपंचांगap, hwirq, msi->num_cpus);

	mutex_unlock(&msi->biपंचांगap_lock);

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops msi_करोमुख्य_ops = अणु
	.alloc  = xgene_irq_करोमुख्य_alloc,
	.मुक्त   = xgene_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल पूर्णांक xgene_allocate_करोमुख्यs(काष्ठा xgene_msi *msi)
अणु
	msi->inner_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, NR_MSI_VEC,
						  &msi_करोमुख्य_ops, msi);
	अगर (!msi->inner_करोमुख्य)
		वापस -ENOMEM;

	msi->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(of_node_to_fwnode(msi->node),
						    &xgene_msi_करोमुख्य_info,
						    msi->inner_करोमुख्य);

	अगर (!msi->msi_करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(msi->inner_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgene_मुक्त_करोमुख्यs(काष्ठा xgene_msi *msi)
अणु
	अगर (msi->msi_करोमुख्य)
		irq_करोमुख्य_हटाओ(msi->msi_करोमुख्य);
	अगर (msi->inner_करोमुख्य)
		irq_करोमुख्य_हटाओ(msi->inner_करोमुख्य);
पूर्ण

अटल पूर्णांक xgene_msi_init_allocator(काष्ठा xgene_msi *xgene_msi)
अणु
	पूर्णांक size = BITS_TO_LONGS(NR_MSI_VEC) * माप(दीर्घ);

	xgene_msi->biपंचांगap = kzalloc(size, GFP_KERNEL);
	अगर (!xgene_msi->biपंचांगap)
		वापस -ENOMEM;

	mutex_init(&xgene_msi->biपंचांगap_lock);

	xgene_msi->msi_groups = kसुस्मृति(NR_HW_IRQS,
					माप(काष्ठा xgene_msi_group),
					GFP_KERNEL);
	अगर (!xgene_msi->msi_groups)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम xgene_msi_isr(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा xgene_msi_group *msi_groups;
	काष्ठा xgene_msi *xgene_msi;
	अचिन्हित पूर्णांक virq;
	पूर्णांक msir_index, msir_val, hw_irq;
	u32 पूर्णांकr_index, grp_select, msi_grp;

	chained_irq_enter(chip, desc);

	msi_groups = irq_desc_get_handler_data(desc);
	xgene_msi = msi_groups->msi;
	msi_grp = msi_groups->msi_grp;

	/*
	 * MSIINTn (n is 0..F) indicates अगर there is a pending MSI पूर्णांकerrupt
	 * If bit x of this रेजिस्टर is set (x is 0..7), one or more पूर्णांकerupts
	 * corresponding to MSInIRx is set.
	 */
	grp_select = xgene_msi_पूर्णांक_पढ़ो(xgene_msi, msi_grp);
	जबतक (grp_select) अणु
		msir_index = ffs(grp_select) - 1;
		/*
		 * Calculate MSInIRx address to पढ़ो to check क्रम पूर्णांकerrupts
		 * (refer to termination address and data assignment
		 * described in xgene_compose_msi_msg() )
		 */
		msir_val = xgene_msi_ir_पढ़ो(xgene_msi, msi_grp, msir_index);
		जबतक (msir_val) अणु
			पूर्णांकr_index = ffs(msir_val) - 1;
			/*
			 * Calculate MSI vector number (refer to the termination
			 * address and data assignment described in
			 * xgene_compose_msi_msg function)
			 */
			hw_irq = (((msir_index * IRQS_PER_IDX) + पूर्णांकr_index) *
				 NR_HW_IRQS) + msi_grp;
			/*
			 * As we have multiple hw_irq that maps to single MSI,
			 * always look up the virq using the hw_irq as seen from
			 * CPU0
			 */
			hw_irq = hwirq_to_canonical_hwirq(hw_irq);
			virq = irq_find_mapping(xgene_msi->inner_करोमुख्य, hw_irq);
			WARN_ON(!virq);
			अगर (virq != 0)
				generic_handle_irq(virq);
			msir_val &= ~(1 << पूर्णांकr_index);
		पूर्ण
		grp_select &= ~(1 << msir_index);

		अगर (!grp_select) अणु
			/*
			 * We handled all पूर्णांकerrupts happened in this group,
			 * resample this group MSI_INTx रेजिस्टर in हाल
			 * something अन्यथा has been made pending in the meanसमय
			 */
			grp_select = xgene_msi_पूर्णांक_पढ़ो(xgene_msi, msi_grp);
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल क्रमागत cpuhp_state pci_xgene_online;

अटल पूर्णांक xgene_msi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_msi *msi = platक्रमm_get_drvdata(pdev);

	अगर (pci_xgene_online)
		cpuhp_हटाओ_state(pci_xgene_online);
	cpuhp_हटाओ_state(CPUHP_PCI_XGENE_DEAD);

	kमुक्त(msi->msi_groups);

	kमुक्त(msi->biपंचांगap);
	msi->biपंचांगap = शून्य;

	xgene_मुक्त_करोमुख्यs(msi);

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_msi_hwirq_alloc(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा xgene_msi *msi = &xgene_msi_ctrl;
	काष्ठा xgene_msi_group *msi_group;
	cpumask_var_t mask;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = cpu; i < NR_HW_IRQS; i += msi->num_cpus) अणु
		msi_group = &msi->msi_groups[i];
		अगर (!msi_group->gic_irq)
			जारी;

		irq_set_chained_handler_and_data(msi_group->gic_irq,
			xgene_msi_isr, msi_group);

		/*
		 * Statically allocate MSI GIC IRQs to each CPU core.
		 * With 8-core X-Gene v1, 2 MSI GIC IRQs are allocated
		 * to each core.
		 */
		अगर (alloc_cpumask_var(&mask, GFP_KERNEL)) अणु
			cpumask_clear(mask);
			cpumask_set_cpu(cpu, mask);
			err = irq_set_affinity(msi_group->gic_irq, mask);
			अगर (err)
				pr_err("failed to set affinity for GIC IRQ");
			मुक्त_cpumask_var(mask);
		पूर्ण अन्यथा अणु
			pr_err("failed to alloc CPU mask for affinity\n");
			err = -EINVAL;
		पूर्ण

		अगर (err) अणु
			irq_set_chained_handler_and_data(msi_group->gic_irq,
							 शून्य, शून्य);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_msi_hwirq_मुक्त(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा xgene_msi *msi = &xgene_msi_ctrl;
	काष्ठा xgene_msi_group *msi_group;
	पूर्णांक i;

	क्रम (i = cpu; i < NR_HW_IRQS; i += msi->num_cpus) अणु
		msi_group = &msi->msi_groups[i];
		अगर (!msi_group->gic_irq)
			जारी;

		irq_set_chained_handler_and_data(msi_group->gic_irq, शून्य,
						 शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_msi_match_table[] = अणु
	अणु.compatible = "apm,xgene1-msi"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक xgene_msi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक rc, irq_index;
	काष्ठा xgene_msi *xgene_msi;
	पूर्णांक virt_msir;
	u32 msi_val, msi_idx;

	xgene_msi = &xgene_msi_ctrl;

	platक्रमm_set_drvdata(pdev, xgene_msi);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	xgene_msi->msi_regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(xgene_msi->msi_regs)) अणु
		dev_err(&pdev->dev, "no reg space\n");
		rc = PTR_ERR(xgene_msi->msi_regs);
		जाओ error;
	पूर्ण
	xgene_msi->msi_addr = res->start;
	xgene_msi->node = pdev->dev.of_node;
	xgene_msi->num_cpus = num_possible_cpus();

	rc = xgene_msi_init_allocator(xgene_msi);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Error allocating MSI bitmap\n");
		जाओ error;
	पूर्ण

	rc = xgene_allocate_करोमुख्यs(xgene_msi);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Failed to allocate MSI domain\n");
		जाओ error;
	पूर्ण

	क्रम (irq_index = 0; irq_index < NR_HW_IRQS; irq_index++) अणु
		virt_msir = platक्रमm_get_irq(pdev, irq_index);
		अगर (virt_msir < 0) अणु
			rc = virt_msir;
			जाओ error;
		पूर्ण
		xgene_msi->msi_groups[irq_index].gic_irq = virt_msir;
		xgene_msi->msi_groups[irq_index].msi_grp = irq_index;
		xgene_msi->msi_groups[irq_index].msi = xgene_msi;
	पूर्ण

	/*
	 * MSInIRx रेजिस्टरs are पढ़ो-to-clear; beक्रमe रेजिस्टरing
	 * पूर्णांकerrupt handlers, पढ़ो all of them to clear spurious
	 * पूर्णांकerrupts that may occur beक्रमe the driver is probed.
	 */
	क्रम (irq_index = 0; irq_index < NR_HW_IRQS; irq_index++) अणु
		क्रम (msi_idx = 0; msi_idx < IDX_PER_GROUP; msi_idx++)
			xgene_msi_ir_पढ़ो(xgene_msi, irq_index, msi_idx);

		/* Read MSIINTn to confirm */
		msi_val = xgene_msi_पूर्णांक_पढ़ो(xgene_msi, irq_index);
		अगर (msi_val) अणु
			dev_err(&pdev->dev, "Failed to clear spurious IRQ\n");
			rc = -EINVAL;
			जाओ error;
		पूर्ण
	पूर्ण

	rc = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "pci/xgene:online",
			       xgene_msi_hwirq_alloc, शून्य);
	अगर (rc < 0)
		जाओ err_cpuhp;
	pci_xgene_online = rc;
	rc = cpuhp_setup_state(CPUHP_PCI_XGENE_DEAD, "pci/xgene:dead", शून्य,
			       xgene_msi_hwirq_मुक्त);
	अगर (rc)
		जाओ err_cpuhp;

	dev_info(&pdev->dev, "APM X-Gene PCIe MSI driver loaded\n");

	वापस 0;

err_cpuhp:
	dev_err(&pdev->dev, "failed to add CPU MSI notifier\n");
error:
	xgene_msi_हटाओ(pdev);
	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver xgene_msi_driver = अणु
	.driver = अणु
		.name = "xgene-msi",
		.of_match_table = xgene_msi_match_table,
	पूर्ण,
	.probe = xgene_msi_probe,
	.हटाओ = xgene_msi_हटाओ,
पूर्ण;

अटल पूर्णांक __init xgene_pcie_msi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&xgene_msi_driver);
पूर्ण
subsys_initcall(xgene_pcie_msi_init);
