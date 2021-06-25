<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा pr_fmt(fmt) "mvebu-sei: " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/msi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

/* Cause रेजिस्टर */
#घोषणा GICP_SECR(idx)		(0x0  + ((idx) * 0x4))
/* Mask रेजिस्टर */
#घोषणा GICP_SEMR(idx)		(0x20 + ((idx) * 0x4))
#घोषणा GICP_SET_SEI_OFFSET	0x30

#घोषणा SEI_IRQ_COUNT_PER_REG	32
#घोषणा SEI_IRQ_REG_COUNT	2
#घोषणा SEI_IRQ_COUNT		(SEI_IRQ_COUNT_PER_REG * SEI_IRQ_REG_COUNT)
#घोषणा SEI_IRQ_REG_IDX(irq_id)	((irq_id) / SEI_IRQ_COUNT_PER_REG)
#घोषणा SEI_IRQ_REG_BIT(irq_id)	((irq_id) % SEI_IRQ_COUNT_PER_REG)

काष्ठा mvebu_sei_पूर्णांकerrupt_range अणु
	u32 first;
	u32 size;
पूर्ण;

काष्ठा mvebu_sei_caps अणु
	काष्ठा mvebu_sei_पूर्णांकerrupt_range ap_range;
	काष्ठा mvebu_sei_पूर्णांकerrupt_range cp_range;
पूर्ण;

काष्ठा mvebu_sei अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा resource *res;
	काष्ठा irq_करोमुख्य *sei_करोमुख्य;
	काष्ठा irq_करोमुख्य *ap_करोमुख्य;
	काष्ठा irq_करोमुख्य *cp_करोमुख्य;
	स्थिर काष्ठा mvebu_sei_caps *caps;

	/* Lock on MSI allocations/releases */
	काष्ठा mutex cp_msi_lock;
	DECLARE_BITMAP(cp_msi_biपंचांगap, SEI_IRQ_COUNT);

	/* Lock on IRQ masking रेजिस्टर */
	raw_spinlock_t mask_lock;
पूर्ण;

अटल व्योम mvebu_sei_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mvebu_sei *sei = irq_data_get_irq_chip_data(d);
	u32 reg_idx = SEI_IRQ_REG_IDX(d->hwirq);

	ग_लिखोl_relaxed(BIT(SEI_IRQ_REG_BIT(d->hwirq)),
		       sei->base + GICP_SECR(reg_idx));
पूर्ण

अटल व्योम mvebu_sei_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mvebu_sei *sei = irq_data_get_irq_chip_data(d);
	u32 reg, reg_idx = SEI_IRQ_REG_IDX(d->hwirq);
	अचिन्हित दीर्घ flags;

	/* 1 disables the पूर्णांकerrupt */
	raw_spin_lock_irqsave(&sei->mask_lock, flags);
	reg = पढ़ोl_relaxed(sei->base + GICP_SEMR(reg_idx));
	reg |= BIT(SEI_IRQ_REG_BIT(d->hwirq));
	ग_लिखोl_relaxed(reg, sei->base + GICP_SEMR(reg_idx));
	raw_spin_unlock_irqrestore(&sei->mask_lock, flags);
पूर्ण

अटल व्योम mvebu_sei_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा mvebu_sei *sei = irq_data_get_irq_chip_data(d);
	u32 reg, reg_idx = SEI_IRQ_REG_IDX(d->hwirq);
	अचिन्हित दीर्घ flags;

	/* 0 enables the पूर्णांकerrupt */
	raw_spin_lock_irqsave(&sei->mask_lock, flags);
	reg = पढ़ोl_relaxed(sei->base + GICP_SEMR(reg_idx));
	reg &= ~BIT(SEI_IRQ_REG_BIT(d->hwirq));
	ग_लिखोl_relaxed(reg, sei->base + GICP_SEMR(reg_idx));
	raw_spin_unlock_irqrestore(&sei->mask_lock, flags);
पूर्ण

अटल पूर्णांक mvebu_sei_set_affinity(काष्ठा irq_data *d,
				  स्थिर काष्ठा cpumask *mask_val,
				  bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mvebu_sei_set_irqchip_state(काष्ठा irq_data *d,
				       क्रमागत irqchip_irq_state which,
				       bool state)
अणु
	/* We can only clear the pending state by acking the पूर्णांकerrupt */
	अगर (which != IRQCHIP_STATE_PENDING || state)
		वापस -EINVAL;

	mvebu_sei_ack_irq(d);
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip mvebu_sei_irq_chip = अणु
	.name			= "SEI",
	.irq_ack		= mvebu_sei_ack_irq,
	.irq_mask		= mvebu_sei_mask_irq,
	.irq_unmask		= mvebu_sei_unmask_irq,
	.irq_set_affinity       = mvebu_sei_set_affinity,
	.irq_set_irqchip_state	= mvebu_sei_set_irqchip_state,
पूर्ण;

अटल पूर्णांक mvebu_sei_ap_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	अगर ((type & IRQ_TYPE_SENSE_MASK) != IRQ_TYPE_LEVEL_HIGH)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip mvebu_sei_ap_irq_chip = अणु
	.name			= "AP SEI",
	.irq_ack		= irq_chip_ack_parent,
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_set_affinity       = irq_chip_set_affinity_parent,
	.irq_set_type		= mvebu_sei_ap_set_type,
पूर्ण;

अटल व्योम mvebu_sei_cp_compose_msi_msg(काष्ठा irq_data *data,
					 काष्ठा msi_msg *msg)
अणु
	काष्ठा mvebu_sei *sei = data->chip_data;
	phys_addr_t set = sei->res->start + GICP_SET_SEI_OFFSET;

	msg->data = data->hwirq + sei->caps->cp_range.first;
	msg->address_lo = lower_32_bits(set);
	msg->address_hi = upper_32_bits(set);
पूर्ण

अटल पूर्णांक mvebu_sei_cp_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	अगर ((type & IRQ_TYPE_SENSE_MASK) != IRQ_TYPE_EDGE_RISING)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip mvebu_sei_cp_irq_chip = अणु
	.name			= "CP SEI",
	.irq_ack		= irq_chip_ack_parent,
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_set_affinity       = irq_chip_set_affinity_parent,
	.irq_set_type		= mvebu_sei_cp_set_type,
	.irq_compose_msi_msg	= mvebu_sei_cp_compose_msi_msg,
पूर्ण;

अटल पूर्णांक mvebu_sei_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा mvebu_sei *sei = करोमुख्य->host_data;
	काष्ठा irq_fwspec *fwspec = arg;

	/* Not much to करो, just setup the irqdata */
	irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, fwspec->param[0],
				      &mvebu_sei_irq_chip, sei);

	वापस 0;
पूर्ण

अटल व्योम mvebu_sei_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);
		irq_set_handler(virq + i, शून्य);
		irq_करोमुख्य_reset_irq_data(d);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mvebu_sei_करोमुख्य_ops = अणु
	.alloc	= mvebu_sei_करोमुख्य_alloc,
	.मुक्त	= mvebu_sei_करोमुख्य_मुक्त,
पूर्ण;

अटल पूर्णांक mvebu_sei_ap_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
				  काष्ठा irq_fwspec *fwspec,
				  अचिन्हित दीर्घ *hwirq,
				  अचिन्हित पूर्णांक *type)
अणु
	*hwirq = fwspec->param[0];
	*type  = IRQ_TYPE_LEVEL_HIGH;

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_sei_ap_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा mvebu_sei *sei = करोमुख्य->host_data;
	काष्ठा irq_fwspec fwspec;
	अचिन्हित दीर्घ hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक err;

	mvebu_sei_ap_translate(करोमुख्य, arg, &hwirq, &type);

	fwspec.fwnode = करोमुख्य->parent->fwnode;
	fwspec.param_count = 1;
	fwspec.param[0] = hwirq + sei->caps->ap_range.first;

	err = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
	अगर (err)
		वापस err;

	irq_करोमुख्य_set_info(करोमुख्य, virq, hwirq,
			    &mvebu_sei_ap_irq_chip, sei,
			    handle_level_irq, शून्य, शून्य);
	irq_set_probe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mvebu_sei_ap_करोमुख्य_ops = अणु
	.translate	= mvebu_sei_ap_translate,
	.alloc		= mvebu_sei_ap_alloc,
	.मुक्त		= irq_करोमुख्य_मुक्त_irqs_parent,
पूर्ण;

अटल व्योम mvebu_sei_cp_release_irq(काष्ठा mvebu_sei *sei, अचिन्हित दीर्घ hwirq)
अणु
	mutex_lock(&sei->cp_msi_lock);
	clear_bit(hwirq, sei->cp_msi_biपंचांगap);
	mutex_unlock(&sei->cp_msi_lock);
पूर्ण

अटल पूर्णांक mvebu_sei_cp_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				     व्योम *args)
अणु
	काष्ठा mvebu_sei *sei = करोमुख्य->host_data;
	काष्ठा irq_fwspec fwspec;
	अचिन्हित दीर्घ hwirq;
	पूर्णांक ret;

	/* The software only supports single allocations क्रम now */
	अगर (nr_irqs != 1)
		वापस -ENOTSUPP;

	mutex_lock(&sei->cp_msi_lock);
	hwirq = find_first_zero_bit(sei->cp_msi_biपंचांगap,
				    sei->caps->cp_range.size);
	अगर (hwirq < sei->caps->cp_range.size)
		set_bit(hwirq, sei->cp_msi_biपंचांगap);
	mutex_unlock(&sei->cp_msi_lock);

	अगर (hwirq == sei->caps->cp_range.size)
		वापस -ENOSPC;

	fwspec.fwnode = करोमुख्य->parent->fwnode;
	fwspec.param_count = 1;
	fwspec.param[0] = hwirq + sei->caps->cp_range.first;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
	अगर (ret)
		जाओ मुक्त_irq;

	irq_करोमुख्य_set_info(करोमुख्य, virq, hwirq,
			    &mvebu_sei_cp_irq_chip, sei,
			    handle_edge_irq, शून्य, शून्य);

	वापस 0;

मुक्त_irq:
	mvebu_sei_cp_release_irq(sei, hwirq);
	वापस ret;
पूर्ण

अटल व्योम mvebu_sei_cp_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा mvebu_sei *sei = करोमुख्य->host_data;
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	अगर (nr_irqs != 1 || d->hwirq >= sei->caps->cp_range.size) अणु
		dev_err(sei->dev, "Invalid hwirq %lu\n", d->hwirq);
		वापस;
	पूर्ण

	mvebu_sei_cp_release_irq(sei, d->hwirq);
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, 1);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mvebu_sei_cp_करोमुख्य_ops = अणु
	.alloc	= mvebu_sei_cp_करोमुख्य_alloc,
	.मुक्त	= mvebu_sei_cp_करोमुख्य_मुक्त,
पूर्ण;

अटल काष्ठा irq_chip mvebu_sei_msi_irq_chip = अणु
	.name		= "SEI pMSI",
	.irq_ack	= irq_chip_ack_parent,
	.irq_set_type	= irq_chip_set_type_parent,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_ops mvebu_sei_msi_ops = अणु
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info mvebu_sei_msi_करोमुख्य_info = अणु
	.flags	= MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS,
	.ops	= &mvebu_sei_msi_ops,
	.chip	= &mvebu_sei_msi_irq_chip,
पूर्ण;

अटल व्योम mvebu_sei_handle_cascade_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा mvebu_sei *sei = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	u32 idx;

	chained_irq_enter(chip, desc);

	क्रम (idx = 0; idx < SEI_IRQ_REG_COUNT; idx++) अणु
		अचिन्हित दीर्घ irqmap;
		पूर्णांक bit;

		irqmap = पढ़ोl_relaxed(sei->base + GICP_SECR(idx));
		क्रम_each_set_bit(bit, &irqmap, SEI_IRQ_COUNT_PER_REG) अणु
			अचिन्हित दीर्घ hwirq;
			अचिन्हित पूर्णांक virq;

			hwirq = idx * SEI_IRQ_COUNT_PER_REG + bit;
			virq = irq_find_mapping(sei->sei_करोमुख्य, hwirq);
			अगर (likely(virq)) अणु
				generic_handle_irq(virq);
				जारी;
			पूर्ण

			dev_warn(sei->dev,
				 "Spurious IRQ detected (hwirq %lu)\n", hwirq);
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम mvebu_sei_reset(काष्ठा mvebu_sei *sei)
अणु
	u32 reg_idx;

	/* Clear IRQ cause रेजिस्टरs, mask all पूर्णांकerrupts */
	क्रम (reg_idx = 0; reg_idx < SEI_IRQ_REG_COUNT; reg_idx++) अणु
		ग_लिखोl_relaxed(0xFFFFFFFF, sei->base + GICP_SECR(reg_idx));
		ग_लिखोl_relaxed(0xFFFFFFFF, sei->base + GICP_SEMR(reg_idx));
	पूर्ण
पूर्ण

अटल पूर्णांक mvebu_sei_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा irq_करोमुख्य *plat_करोमुख्य;
	काष्ठा mvebu_sei *sei;
	u32 parent_irq;
	पूर्णांक ret;

	sei = devm_kzalloc(&pdev->dev, माप(*sei), GFP_KERNEL);
	अगर (!sei)
		वापस -ENOMEM;

	sei->dev = &pdev->dev;

	mutex_init(&sei->cp_msi_lock);
	raw_spin_lock_init(&sei->mask_lock);

	sei->res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sei->base = devm_ioremap_resource(sei->dev, sei->res);
	अगर (IS_ERR(sei->base))
		वापस PTR_ERR(sei->base);

	/* Retrieve the SEI capabilities with the पूर्णांकerrupt ranges */
	sei->caps = of_device_get_match_data(&pdev->dev);
	अगर (!sei->caps) अणु
		dev_err(sei->dev,
			"Could not retrieve controller capabilities\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Reserve the single (top-level) parent SPI IRQ from which all the
	 * पूर्णांकerrupts handled by this driver will be संकेतed.
	 */
	parent_irq = irq_of_parse_and_map(node, 0);
	अगर (parent_irq <= 0) अणु
		dev_err(sei->dev, "Failed to retrieve top-level SPI IRQ\n");
		वापस -ENODEV;
	पूर्ण

	/* Create the root SEI करोमुख्य */
	sei->sei_करोमुख्य = irq_करोमुख्य_create_linear(of_node_to_fwnode(node),
						   (sei->caps->ap_range.size +
						    sei->caps->cp_range.size),
						   &mvebu_sei_करोमुख्य_ops,
						   sei);
	अगर (!sei->sei_करोमुख्य) अणु
		dev_err(sei->dev, "Failed to create SEI IRQ domain\n");
		ret = -ENOMEM;
		जाओ dispose_irq;
	पूर्ण

	irq_करोमुख्य_update_bus_token(sei->sei_करोमुख्य, DOMAIN_BUS_NEXUS);

	/* Create the 'wired' करोमुख्य */
	sei->ap_करोमुख्य = irq_करोमुख्य_create_hierarchy(sei->sei_करोमुख्य, 0,
						     sei->caps->ap_range.size,
						     of_node_to_fwnode(node),
						     &mvebu_sei_ap_करोमुख्य_ops,
						     sei);
	अगर (!sei->ap_करोमुख्य) अणु
		dev_err(sei->dev, "Failed to create AP IRQ domain\n");
		ret = -ENOMEM;
		जाओ हटाओ_sei_करोमुख्य;
	पूर्ण

	irq_करोमुख्य_update_bus_token(sei->ap_करोमुख्य, DOMAIN_BUS_WIRED);

	/* Create the 'MSI' करोमुख्य */
	sei->cp_करोमुख्य = irq_करोमुख्य_create_hierarchy(sei->sei_करोमुख्य, 0,
						     sei->caps->cp_range.size,
						     of_node_to_fwnode(node),
						     &mvebu_sei_cp_करोमुख्य_ops,
						     sei);
	अगर (!sei->cp_करोमुख्य) अणु
		pr_err("Failed to create CPs IRQ domain\n");
		ret = -ENOMEM;
		जाओ हटाओ_ap_करोमुख्य;
	पूर्ण

	irq_करोमुख्य_update_bus_token(sei->cp_करोमुख्य, DOMAIN_BUS_GENERIC_MSI);

	plat_करोमुख्य = platक्रमm_msi_create_irq_करोमुख्य(of_node_to_fwnode(node),
						     &mvebu_sei_msi_करोमुख्य_info,
						     sei->cp_करोमुख्य);
	अगर (!plat_करोमुख्य) अणु
		pr_err("Failed to create CPs MSI domain\n");
		ret = -ENOMEM;
		जाओ हटाओ_cp_करोमुख्य;
	पूर्ण

	mvebu_sei_reset(sei);

	irq_set_chained_handler_and_data(parent_irq,
					 mvebu_sei_handle_cascade_irq,
					 sei);

	वापस 0;

हटाओ_cp_करोमुख्य:
	irq_करोमुख्य_हटाओ(sei->cp_करोमुख्य);
हटाओ_ap_करोमुख्य:
	irq_करोमुख्य_हटाओ(sei->ap_करोमुख्य);
हटाओ_sei_करोमुख्य:
	irq_करोमुख्य_हटाओ(sei->sei_करोमुख्य);
dispose_irq:
	irq_dispose_mapping(parent_irq);

	वापस ret;
पूर्ण

अटल काष्ठा mvebu_sei_caps mvebu_sei_ap806_caps = अणु
	.ap_range = अणु
		.first = 0,
		.size = 21,
	पूर्ण,
	.cp_range = अणु
		.first = 21,
		.size = 43,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mvebu_sei_of_match[] = अणु
	अणु
		.compatible = "marvell,ap806-sei",
		.data = &mvebu_sei_ap806_caps,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mvebu_sei_driver = अणु
	.probe  = mvebu_sei_probe,
	.driver = अणु
		.name = "mvebu-sei",
		.of_match_table = mvebu_sei_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(mvebu_sei_driver);
