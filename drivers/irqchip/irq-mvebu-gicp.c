<शैली गुरु>
/*
 * Copyright (C) 2017 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/arm-gic.h>

#घोषणा GICP_SETSPI_NSR_OFFSET	0x0
#घोषणा GICP_CLRSPI_NSR_OFFSET	0x8

काष्ठा mvebu_gicp_spi_range अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा mvebu_gicp अणु
	काष्ठा mvebu_gicp_spi_range *spi_ranges;
	अचिन्हित पूर्णांक spi_ranges_cnt;
	अचिन्हित पूर्णांक spi_cnt;
	अचिन्हित दीर्घ *spi_biपंचांगap;
	spinlock_t spi_lock;
	काष्ठा resource *res;
	काष्ठा device *dev;
पूर्ण;

अटल पूर्णांक gicp_idx_to_spi(काष्ठा mvebu_gicp *gicp, पूर्णांक idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gicp->spi_ranges_cnt; i++) अणु
		काष्ठा mvebu_gicp_spi_range *r = &gicp->spi_ranges[i];

		अगर (idx < r->count)
			वापस r->start + idx;

		idx -= r->count;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम gicp_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा mvebu_gicp *gicp = data->chip_data;
	phys_addr_t setspi = gicp->res->start + GICP_SETSPI_NSR_OFFSET;
	phys_addr_t clrspi = gicp->res->start + GICP_CLRSPI_NSR_OFFSET;

	msg[0].data = data->hwirq;
	msg[0].address_lo = lower_32_bits(setspi);
	msg[0].address_hi = upper_32_bits(setspi);
	msg[1].data = data->hwirq;
	msg[1].address_lo = lower_32_bits(clrspi);
	msg[1].address_hi = upper_32_bits(clrspi);
पूर्ण

अटल काष्ठा irq_chip gicp_irq_chip = अणु
	.name			= "GICP",
	.irq_mask		= irq_chip_mask_parent,
	.irq_unmask		= irq_chip_unmask_parent,
	.irq_eoi		= irq_chip_eoi_parent,
	.irq_set_affinity	= irq_chip_set_affinity_parent,
	.irq_set_type		= irq_chip_set_type_parent,
	.irq_compose_msi_msg	= gicp_compose_msi_msg,
पूर्ण;

अटल पूर्णांक gicp_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा mvebu_gicp *gicp = करोमुख्य->host_data;
	काष्ठा irq_fwspec fwspec;
	अचिन्हित पूर्णांक hwirq;
	पूर्णांक ret;

	spin_lock(&gicp->spi_lock);
	hwirq = find_first_zero_bit(gicp->spi_biपंचांगap, gicp->spi_cnt);
	अगर (hwirq == gicp->spi_cnt) अणु
		spin_unlock(&gicp->spi_lock);
		वापस -ENOSPC;
	पूर्ण
	__set_bit(hwirq, gicp->spi_biपंचांगap);
	spin_unlock(&gicp->spi_lock);

	fwspec.fwnode = करोमुख्य->parent->fwnode;
	fwspec.param_count = 3;
	fwspec.param[0] = GIC_SPI;
	fwspec.param[1] = gicp_idx_to_spi(gicp, hwirq) - 32;
	/*
	 * Assume edge rising क्रम now, it will be properly set when
	 * ->set_type() is called
	 */
	fwspec.param[2] = IRQ_TYPE_EDGE_RISING;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, 1, &fwspec);
	अगर (ret) अणु
		dev_err(gicp->dev, "Cannot allocate parent IRQ\n");
		जाओ मुक्त_hwirq;
	पूर्ण

	ret = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq, hwirq,
					    &gicp_irq_chip, gicp);
	अगर (ret)
		जाओ मुक्त_irqs_parent;

	वापस 0;

मुक्त_irqs_parent:
	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
मुक्त_hwirq:
	spin_lock(&gicp->spi_lock);
	__clear_bit(hwirq, gicp->spi_biपंचांगap);
	spin_unlock(&gicp->spi_lock);
	वापस ret;
पूर्ण

अटल व्योम gicp_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा mvebu_gicp *gicp = करोमुख्य->host_data;
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	अगर (d->hwirq >= gicp->spi_cnt) अणु
		dev_err(gicp->dev, "Invalid hwirq %lu\n", d->hwirq);
		वापस;
	पूर्ण

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);

	spin_lock(&gicp->spi_lock);
	__clear_bit(d->hwirq, gicp->spi_biपंचांगap);
	spin_unlock(&gicp->spi_lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops gicp_करोमुख्य_ops = अणु
	.alloc	= gicp_irq_करोमुख्य_alloc,
	.मुक्त	= gicp_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल काष्ठा irq_chip gicp_msi_irq_chip = अणु
	.name		= "GICP",
	.irq_set_type	= irq_chip_set_type_parent,
	.flags		= IRQCHIP_SUPPORTS_LEVEL_MSI,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_ops gicp_msi_ops = अणु
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info gicp_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_LEVEL_CAPABLE),
	.ops	= &gicp_msi_ops,
	.chip	= &gicp_msi_irq_chip,
पूर्ण;

अटल पूर्णांक mvebu_gicp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvebu_gicp *gicp;
	काष्ठा irq_करोमुख्य *inner_करोमुख्य, *plat_करोमुख्य, *parent_करोमुख्य;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *irq_parent_dn;
	पूर्णांक ret, i;

	gicp = devm_kzalloc(&pdev->dev, माप(*gicp), GFP_KERNEL);
	अगर (!gicp)
		वापस -ENOMEM;

	gicp->dev = &pdev->dev;
	spin_lock_init(&gicp->spi_lock);

	gicp->res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!gicp->res)
		वापस -ENODEV;

	ret = of_property_count_u32_elems(node, "marvell,spi-ranges");
	अगर (ret < 0)
		वापस ret;

	gicp->spi_ranges_cnt = ret / 2;

	gicp->spi_ranges =
		devm_kसुस्मृति(&pdev->dev,
			     gicp->spi_ranges_cnt,
			     माप(काष्ठा mvebu_gicp_spi_range),
			     GFP_KERNEL);
	अगर (!gicp->spi_ranges)
		वापस -ENOMEM;

	क्रम (i = 0; i < gicp->spi_ranges_cnt; i++) अणु
		of_property_पढ़ो_u32_index(node, "marvell,spi-ranges",
					   i * 2,
					   &gicp->spi_ranges[i].start);

		of_property_पढ़ो_u32_index(node, "marvell,spi-ranges",
					   i * 2 + 1,
					   &gicp->spi_ranges[i].count);

		gicp->spi_cnt += gicp->spi_ranges[i].count;
	पूर्ण

	gicp->spi_biपंचांगap = devm_kसुस्मृति(&pdev->dev,
				BITS_TO_LONGS(gicp->spi_cnt), माप(दीर्घ),
				GFP_KERNEL);
	अगर (!gicp->spi_biपंचांगap)
		वापस -ENOMEM;

	irq_parent_dn = of_irq_find_parent(node);
	अगर (!irq_parent_dn) अणु
		dev_err(&pdev->dev, "failed to find parent IRQ node\n");
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(irq_parent_dn);
	अगर (!parent_करोमुख्य) अणु
		dev_err(&pdev->dev, "failed to find parent IRQ domain\n");
		वापस -ENODEV;
	पूर्ण

	inner_करोमुख्य = irq_करोमुख्य_create_hierarchy(parent_करोमुख्य, 0,
						   gicp->spi_cnt,
						   of_node_to_fwnode(node),
						   &gicp_करोमुख्य_ops, gicp);
	अगर (!inner_करोमुख्य)
		वापस -ENOMEM;


	plat_करोमुख्य = platक्रमm_msi_create_irq_करोमुख्य(of_node_to_fwnode(node),
						     &gicp_msi_करोमुख्य_info,
						     inner_करोमुख्य);
	अगर (!plat_करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(inner_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gicp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mvebu_gicp_of_match[] = अणु
	अणु .compatible = "marvell,ap806-gicp", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mvebu_gicp_driver = अणु
	.probe  = mvebu_gicp_probe,
	.driver = अणु
		.name = "mvebu-gicp",
		.of_match_table = mvebu_gicp_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(mvebu_gicp_driver);
