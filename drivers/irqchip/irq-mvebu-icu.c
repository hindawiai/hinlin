<शैली गुरु>
/*
 * Copyright (C) 2017 Marvell
 *
 * Hanna Hawa <hannah@marvell.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/mvebu-icu.h>

/* ICU रेजिस्टरs */
#घोषणा ICU_SETSPI_NSR_AL	0x10
#घोषणा ICU_SETSPI_NSR_AH	0x14
#घोषणा ICU_CLRSPI_NSR_AL	0x18
#घोषणा ICU_CLRSPI_NSR_AH	0x1c
#घोषणा ICU_SET_SEI_AL		0x50
#घोषणा ICU_SET_SEI_AH		0x54
#घोषणा ICU_CLR_SEI_AL		0x58
#घोषणा ICU_CLR_SEI_AH		0x5C
#घोषणा ICU_INT_CFG(x)          (0x100 + 4 * (x))
#घोषणा   ICU_INT_ENABLE	BIT(24)
#घोषणा   ICU_IS_EDGE		BIT(28)
#घोषणा   ICU_GROUP_SHIFT	29

/* ICU definitions */
#घोषणा ICU_MAX_IRQS		207
#घोषणा ICU_SATA0_ICU_ID	109
#घोषणा ICU_SATA1_ICU_ID	107

काष्ठा mvebu_icu_subset_data अणु
	अचिन्हित पूर्णांक icu_group;
	अचिन्हित पूर्णांक offset_set_ah;
	अचिन्हित पूर्णांक offset_set_al;
	अचिन्हित पूर्णांक offset_clr_ah;
	अचिन्हित पूर्णांक offset_clr_al;
पूर्ण;

काष्ठा mvebu_icu अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
पूर्ण;

काष्ठा mvebu_icu_msi_data अणु
	काष्ठा mvebu_icu *icu;
	atomic_t initialized;
	स्थिर काष्ठा mvebu_icu_subset_data *subset_data;
पूर्ण;

काष्ठा mvebu_icu_irq_data अणु
	काष्ठा mvebu_icu *icu;
	अचिन्हित पूर्णांक icu_group;
	अचिन्हित पूर्णांक type;
पूर्ण;

अटल DEFINE_STATIC_KEY_FALSE(legacy_bindings);

अटल व्योम mvebu_icu_init(काष्ठा mvebu_icu *icu,
			   काष्ठा mvebu_icu_msi_data *msi_data,
			   काष्ठा msi_msg *msg)
अणु
	स्थिर काष्ठा mvebu_icu_subset_data *subset = msi_data->subset_data;

	अगर (atomic_cmpxchg(&msi_data->initialized, false, true))
		वापस;

	/* Set 'SET' ICU SPI message address in AP */
	ग_लिखोl_relaxed(msg[0].address_hi, icu->base + subset->offset_set_ah);
	ग_लिखोl_relaxed(msg[0].address_lo, icu->base + subset->offset_set_al);

	अगर (subset->icu_group != ICU_GRP_NSR)
		वापस;

	/* Set 'CLEAR' ICU SPI message address in AP (level-MSI only) */
	ग_लिखोl_relaxed(msg[1].address_hi, icu->base + subset->offset_clr_ah);
	ग_लिखोl_relaxed(msg[1].address_lo, icu->base + subset->offset_clr_al);
पूर्ण

अटल व्योम mvebu_icu_ग_लिखो_msg(काष्ठा msi_desc *desc, काष्ठा msi_msg *msg)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(desc->irq);
	काष्ठा mvebu_icu_msi_data *msi_data = platक्रमm_msi_get_host_data(d->करोमुख्य);
	काष्ठा mvebu_icu_irq_data *icu_irqd = d->chip_data;
	काष्ठा mvebu_icu *icu = icu_irqd->icu;
	अचिन्हित पूर्णांक icu_पूर्णांक;

	अगर (msg->address_lo || msg->address_hi) अणु
		/* One off initialization per करोमुख्य */
		mvebu_icu_init(icu, msi_data, msg);
		/* Configure the ICU with irq number & type */
		icu_पूर्णांक = msg->data | ICU_INT_ENABLE;
		अगर (icu_irqd->type & IRQ_TYPE_EDGE_RISING)
			icu_पूर्णांक |= ICU_IS_EDGE;
		icu_पूर्णांक |= icu_irqd->icu_group << ICU_GROUP_SHIFT;
	पूर्ण अन्यथा अणु
		/* De-configure the ICU */
		icu_पूर्णांक = 0;
	पूर्ण

	ग_लिखोl_relaxed(icu_पूर्णांक, icu->base + ICU_INT_CFG(d->hwirq));

	/*
	 * The SATA unit has 2 ports, and a dedicated ICU entry per
	 * port. The ahci sata driver supports only one irq पूर्णांकerrupt
	 * per SATA unit. To solve this conflict, we configure the 2
	 * SATA wired पूर्णांकerrupts in the south bridge पूर्णांकo 1 GIC
	 * पूर्णांकerrupt in the north bridge. Even अगर only a single port
	 * is enabled, अगर sata node is enabled, both पूर्णांकerrupts are
	 * configured (regardless of which port is actually in use).
	 */
	अगर (d->hwirq == ICU_SATA0_ICU_ID || d->hwirq == ICU_SATA1_ICU_ID) अणु
		ग_लिखोl_relaxed(icu_पूर्णांक,
			       icu->base + ICU_INT_CFG(ICU_SATA0_ICU_ID));
		ग_लिखोl_relaxed(icu_पूर्णांक,
			       icu->base + ICU_INT_CFG(ICU_SATA1_ICU_ID));
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip mvebu_icu_nsr_chip = अणु
	.name			= "ICU-NSR",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_type		= irq_chip_set_type_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
पूर्ण;

अटल काष्ठा irq_chip mvebu_icu_sei_chip = अणु
	.name			= "ICU-SEI",
	.irq_ack		= irq_chip_ack_parent,
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_set_type		= irq_chip_set_type_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
पूर्ण;

अटल पूर्णांक
mvebu_icu_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d, काष्ठा irq_fwspec *fwspec,
			       अचिन्हित दीर्घ *hwirq, अचिन्हित पूर्णांक *type)
अणु
	काष्ठा mvebu_icu_msi_data *msi_data = platक्रमm_msi_get_host_data(d);
	काष्ठा mvebu_icu *icu = platक्रमm_msi_get_host_data(d);
	अचिन्हित पूर्णांक param_count = अटल_branch_unlikely(&legacy_bindings) ? 3 : 2;

	/* Check the count of the parameters in dt */
	अगर (WARN_ON(fwspec->param_count != param_count)) अणु
		dev_err(icu->dev, "wrong ICU parameter count %d\n",
			fwspec->param_count);
		वापस -EINVAL;
	पूर्ण

	अगर (अटल_branch_unlikely(&legacy_bindings)) अणु
		*hwirq = fwspec->param[1];
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
		अगर (fwspec->param[0] != ICU_GRP_NSR) अणु
			dev_err(icu->dev, "wrong ICU group type %x\n",
				fwspec->param[0]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		*hwirq = fwspec->param[0];
		*type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;

		/*
		 * The ICU receives level पूर्णांकerrupts. While the NSR are also
		 * level पूर्णांकerrupts, SEI are edge पूर्णांकerrupts. Force the type
		 * here in this हाल. Please note that this makes the पूर्णांकerrupt
		 * handling unreliable.
		 */
		अगर (msi_data->subset_data->icu_group == ICU_GRP_SEI)
			*type = IRQ_TYPE_EDGE_RISING;
	पूर्ण

	अगर (*hwirq >= ICU_MAX_IRQS) अणु
		dev_err(icu->dev, "invalid interrupt number %ld\n", *hwirq);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mvebu_icu_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			   अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ hwirq;
	काष्ठा irq_fwspec *fwspec = args;
	काष्ठा mvebu_icu_msi_data *msi_data = platक्रमm_msi_get_host_data(करोमुख्य);
	काष्ठा mvebu_icu *icu = msi_data->icu;
	काष्ठा mvebu_icu_irq_data *icu_irqd;
	काष्ठा irq_chip *chip = &mvebu_icu_nsr_chip;

	icu_irqd = kदो_स्मृति(माप(*icu_irqd), GFP_KERNEL);
	अगर (!icu_irqd)
		वापस -ENOMEM;

	err = mvebu_icu_irq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq,
					     &icu_irqd->type);
	अगर (err) अणु
		dev_err(icu->dev, "failed to translate ICU parameters\n");
		जाओ मुक्त_irqd;
	पूर्ण

	अगर (अटल_branch_unlikely(&legacy_bindings))
		icu_irqd->icu_group = fwspec->param[0];
	अन्यथा
		icu_irqd->icu_group = msi_data->subset_data->icu_group;
	icu_irqd->icu = icu;

	err = platक्रमm_msi_करोमुख्य_alloc(करोमुख्य, virq, nr_irqs);
	अगर (err) अणु
		dev_err(icu->dev, "failed to allocate ICU interrupt in parent domain\n");
		जाओ मुक्त_irqd;
	पूर्ण

	/* Make sure there is no पूर्णांकerrupt left pending by the firmware */
	err = irq_set_irqchip_state(virq, IRQCHIP_STATE_PENDING, false);
	अगर (err)
		जाओ मुक्त_msi;

	अगर (icu_irqd->icu_group == ICU_GRP_SEI)
		chip = &mvebu_icu_sei_chip;

	err = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
					    chip, icu_irqd);
	अगर (err) अणु
		dev_err(icu->dev, "failed to set the data to IRQ domain\n");
		जाओ मुक्त_msi;
	पूर्ण

	वापस 0;

मुक्त_msi:
	platक्रमm_msi_करोमुख्य_मुक्त(करोमुख्य, virq, nr_irqs);
मुक्त_irqd:
	kमुक्त(icu_irqd);
	वापस err;
पूर्ण

अटल व्योम
mvebu_icu_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			  अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(virq);
	काष्ठा mvebu_icu_irq_data *icu_irqd = d->chip_data;

	kमुक्त(icu_irqd);

	platक्रमm_msi_करोमुख्य_मुक्त(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mvebu_icu_करोमुख्य_ops = अणु
	.translate = mvebu_icu_irq_करोमुख्य_translate,
	.alloc     = mvebu_icu_irq_करोमुख्य_alloc,
	.मुक्त      = mvebu_icu_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल स्थिर काष्ठा mvebu_icu_subset_data mvebu_icu_nsr_subset_data = अणु
	.icu_group = ICU_GRP_NSR,
	.offset_set_ah = ICU_SETSPI_NSR_AH,
	.offset_set_al = ICU_SETSPI_NSR_AL,
	.offset_clr_ah = ICU_CLRSPI_NSR_AH,
	.offset_clr_al = ICU_CLRSPI_NSR_AL,
पूर्ण;

अटल स्थिर काष्ठा mvebu_icu_subset_data mvebu_icu_sei_subset_data = अणु
	.icu_group = ICU_GRP_SEI,
	.offset_set_ah = ICU_SET_SEI_AH,
	.offset_set_al = ICU_SET_SEI_AL,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mvebu_icu_subset_of_match[] = अणु
	अणु
		.compatible = "marvell,cp110-icu-nsr",
		.data = &mvebu_icu_nsr_subset_data,
	पूर्ण,
	अणु
		.compatible = "marvell,cp110-icu-sei",
		.data = &mvebu_icu_sei_subset_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक mvebu_icu_subset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_icu_msi_data *msi_data;
	काष्ठा device_node *msi_parent_dn;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;

	msi_data = devm_kzalloc(dev, माप(*msi_data), GFP_KERNEL);
	अगर (!msi_data)
		वापस -ENOMEM;

	अगर (अटल_branch_unlikely(&legacy_bindings)) अणु
		msi_data->icu = dev_get_drvdata(dev);
		msi_data->subset_data = &mvebu_icu_nsr_subset_data;
	पूर्ण अन्यथा अणु
		msi_data->icu = dev_get_drvdata(dev->parent);
		msi_data->subset_data = of_device_get_match_data(dev);
	पूर्ण

	dev->msi_करोमुख्य = of_msi_get_करोमुख्य(dev, dev->of_node,
					    DOMAIN_BUS_PLATFORM_MSI);
	अगर (!dev->msi_करोमुख्य)
		वापस -EPROBE_DEFER;

	msi_parent_dn = irq_करोमुख्य_get_of_node(dev->msi_करोमुख्य);
	अगर (!msi_parent_dn)
		वापस -ENODEV;

	irq_करोमुख्य = platक्रमm_msi_create_device_tree_करोमुख्य(dev, ICU_MAX_IRQS,
							    mvebu_icu_ग_लिखो_msg,
							    &mvebu_icu_करोमुख्य_ops,
							    msi_data);
	अगर (!irq_करोमुख्य) अणु
		dev_err(dev, "Failed to create ICU MSI domain\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mvebu_icu_subset_driver = अणु
	.probe  = mvebu_icu_subset_probe,
	.driver = अणु
		.name = "mvebu-icu-subset",
		.of_match_table = mvebu_icu_subset_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(mvebu_icu_subset_driver);

अटल पूर्णांक mvebu_icu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_icu *icu;
	काष्ठा resource *res;
	पूर्णांक i;

	icu = devm_kzalloc(&pdev->dev, माप(काष्ठा mvebu_icu),
			   GFP_KERNEL);
	अगर (!icu)
		वापस -ENOMEM;

	icu->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	icu->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(icu->base))
		वापस PTR_ERR(icu->base);

	/*
	 * Legacy bindings: ICU is one node with one MSI parent: क्रमce manually
	 *                  the probe of the NSR पूर्णांकerrupts side.
	 * New bindings: ICU node has children, one per पूर्णांकerrupt controller
	 *               having its own MSI parent: call platक्रमm_populate().
	 * All ICU instances should use the same bindings.
	 */
	अगर (!of_get_child_count(pdev->dev.of_node))
		अटल_branch_enable(&legacy_bindings);

	/*
	 * Clean all ICU पूर्णांकerrupts of type NSR and SEI, required to
	 * aव्योम unpredictable SPI assignments करोne by firmware.
	 */
	क्रम (i = 0 ; i < ICU_MAX_IRQS ; i++) अणु
		u32 icu_पूर्णांक, icu_grp;

		icu_पूर्णांक = पढ़ोl_relaxed(icu->base + ICU_INT_CFG(i));
		icu_grp = icu_पूर्णांक >> ICU_GROUP_SHIFT;

		अगर (icu_grp == ICU_GRP_NSR ||
		    (icu_grp == ICU_GRP_SEI &&
		     !अटल_branch_unlikely(&legacy_bindings)))
			ग_लिखोl_relaxed(0x0, icu->base + ICU_INT_CFG(i));
	पूर्ण

	platक्रमm_set_drvdata(pdev, icu);

	अगर (अटल_branch_unlikely(&legacy_bindings))
		वापस mvebu_icu_subset_probe(pdev);
	अन्यथा
		वापस devm_of_platक्रमm_populate(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id mvebu_icu_of_match[] = अणु
	अणु .compatible = "marvell,cp110-icu", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mvebu_icu_driver = अणु
	.probe  = mvebu_icu_probe,
	.driver = अणु
		.name = "mvebu-icu",
		.of_match_table = mvebu_icu_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(mvebu_icu_driver);
