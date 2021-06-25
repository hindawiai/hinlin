<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Synopsys DesignWare PCIe host controller driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		https://www.samsung.com
 *
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "../../pci.h"
#समावेश "pcie-designware.h"

अटल काष्ठा pci_ops dw_pcie_ops;
अटल काष्ठा pci_ops dw_child_pcie_ops;

अटल व्योम dw_msi_ack_irq(काष्ठा irq_data *d)
अणु
	irq_chip_ack_parent(d);
पूर्ण

अटल व्योम dw_msi_mask_irq(काष्ठा irq_data *d)
अणु
	pci_msi_mask_irq(d);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम dw_msi_unmask_irq(काष्ठा irq_data *d)
अणु
	pci_msi_unmask_irq(d);
	irq_chip_unmask_parent(d);
पूर्ण

अटल काष्ठा irq_chip dw_pcie_msi_irq_chip = अणु
	.name = "PCI-MSI",
	.irq_ack = dw_msi_ack_irq,
	.irq_mask = dw_msi_mask_irq,
	.irq_unmask = dw_msi_unmask_irq,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info dw_pcie_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_PCI_MSIX | MSI_FLAG_MULTI_PCI_MSI),
	.chip	= &dw_pcie_msi_irq_chip,
पूर्ण;

/* MSI पूर्णांक handler */
irqवापस_t dw_handle_msi_irq(काष्ठा pcie_port *pp)
अणु
	पूर्णांक i, pos, irq;
	अचिन्हित दीर्घ val;
	u32 status, num_ctrls;
	irqवापस_t ret = IRQ_NONE;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);

	num_ctrls = pp->num_vectors / MAX_MSI_IRQS_PER_CTRL;

	क्रम (i = 0; i < num_ctrls; i++) अणु
		status = dw_pcie_पढ़ोl_dbi(pci, PCIE_MSI_INTR0_STATUS +
					   (i * MSI_REG_CTRL_BLOCK_SIZE));
		अगर (!status)
			जारी;

		ret = IRQ_HANDLED;
		val = status;
		pos = 0;
		जबतक ((pos = find_next_bit(&val, MAX_MSI_IRQS_PER_CTRL,
					    pos)) != MAX_MSI_IRQS_PER_CTRL) अणु
			irq = irq_find_mapping(pp->irq_करोमुख्य,
					       (i * MAX_MSI_IRQS_PER_CTRL) +
					       pos);
			generic_handle_irq(irq);
			pos++;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* Chained MSI पूर्णांकerrupt service routine */
अटल व्योम dw_chained_msi_isr(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा pcie_port *pp;

	chained_irq_enter(chip, desc);

	pp = irq_desc_get_handler_data(desc);
	dw_handle_msi_irq(pp);

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम dw_pci_setup_msi_msg(काष्ठा irq_data *d, काष्ठा msi_msg *msg)
अणु
	काष्ठा pcie_port *pp = irq_data_get_irq_chip_data(d);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	u64 msi_target;

	msi_target = (u64)pp->msi_data;

	msg->address_lo = lower_32_bits(msi_target);
	msg->address_hi = upper_32_bits(msi_target);

	msg->data = d->hwirq;

	dev_dbg(pci->dev, "msi#%d address_hi %#x address_lo %#x\n",
		(पूर्णांक)d->hwirq, msg->address_hi, msg->address_lo);
पूर्ण

अटल पूर्णांक dw_pci_msi_set_affinity(काष्ठा irq_data *d,
				   स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम dw_pci_bottom_mask(काष्ठा irq_data *d)
अणु
	काष्ठा pcie_port *pp = irq_data_get_irq_chip_data(d);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	अचिन्हित पूर्णांक res, bit, ctrl;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pp->lock, flags);

	ctrl = d->hwirq / MAX_MSI_IRQS_PER_CTRL;
	res = ctrl * MSI_REG_CTRL_BLOCK_SIZE;
	bit = d->hwirq % MAX_MSI_IRQS_PER_CTRL;

	pp->irq_mask[ctrl] |= BIT(bit);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_MSI_INTR0_MASK + res, pp->irq_mask[ctrl]);

	raw_spin_unlock_irqrestore(&pp->lock, flags);
पूर्ण

अटल व्योम dw_pci_bottom_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा pcie_port *pp = irq_data_get_irq_chip_data(d);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	अचिन्हित पूर्णांक res, bit, ctrl;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pp->lock, flags);

	ctrl = d->hwirq / MAX_MSI_IRQS_PER_CTRL;
	res = ctrl * MSI_REG_CTRL_BLOCK_SIZE;
	bit = d->hwirq % MAX_MSI_IRQS_PER_CTRL;

	pp->irq_mask[ctrl] &= ~BIT(bit);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_MSI_INTR0_MASK + res, pp->irq_mask[ctrl]);

	raw_spin_unlock_irqrestore(&pp->lock, flags);
पूर्ण

अटल व्योम dw_pci_bottom_ack(काष्ठा irq_data *d)
अणु
	काष्ठा pcie_port *pp  = irq_data_get_irq_chip_data(d);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	अचिन्हित पूर्णांक res, bit, ctrl;

	ctrl = d->hwirq / MAX_MSI_IRQS_PER_CTRL;
	res = ctrl * MSI_REG_CTRL_BLOCK_SIZE;
	bit = d->hwirq % MAX_MSI_IRQS_PER_CTRL;

	dw_pcie_ग_लिखोl_dbi(pci, PCIE_MSI_INTR0_STATUS + res, BIT(bit));
पूर्ण

अटल काष्ठा irq_chip dw_pci_msi_bottom_irq_chip = अणु
	.name = "DWPCI-MSI",
	.irq_ack = dw_pci_bottom_ack,
	.irq_compose_msi_msg = dw_pci_setup_msi_msg,
	.irq_set_affinity = dw_pci_msi_set_affinity,
	.irq_mask = dw_pci_bottom_mask,
	.irq_unmask = dw_pci_bottom_unmask,
पूर्ण;

अटल पूर्णांक dw_pcie_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				    व्योम *args)
अणु
	काष्ठा pcie_port *pp = करोमुख्य->host_data;
	अचिन्हित दीर्घ flags;
	u32 i;
	पूर्णांक bit;

	raw_spin_lock_irqsave(&pp->lock, flags);

	bit = biपंचांगap_find_मुक्त_region(pp->msi_irq_in_use, pp->num_vectors,
				      order_base_2(nr_irqs));

	raw_spin_unlock_irqrestore(&pp->lock, flags);

	अगर (bit < 0)
		वापस -ENOSPC;

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, bit + i,
				    pp->msi_irq_chip,
				    pp, handle_edge_irq,
				    शून्य, शून्य);

	वापस 0;
पूर्ण

अटल व्योम dw_pcie_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				    अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा pcie_port *pp = करोमुख्य->host_data;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pp->lock, flags);

	biपंचांगap_release_region(pp->msi_irq_in_use, d->hwirq,
			      order_base_2(nr_irqs));

	raw_spin_unlock_irqrestore(&pp->lock, flags);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops dw_pcie_msi_करोमुख्य_ops = अणु
	.alloc	= dw_pcie_irq_करोमुख्य_alloc,
	.मुक्त	= dw_pcie_irq_करोमुख्य_मुक्त,
पूर्ण;

पूर्णांक dw_pcie_allocate_करोमुख्यs(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा fwnode_handle *fwnode = of_node_to_fwnode(pci->dev->of_node);

	pp->irq_करोमुख्य = irq_करोमुख्य_create_linear(fwnode, pp->num_vectors,
					       &dw_pcie_msi_करोमुख्य_ops, pp);
	अगर (!pp->irq_करोमुख्य) अणु
		dev_err(pci->dev, "Failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	irq_करोमुख्य_update_bus_token(pp->irq_करोमुख्य, DOMAIN_BUS_NEXUS);

	pp->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode,
						   &dw_pcie_msi_करोमुख्य_info,
						   pp->irq_करोमुख्य);
	अगर (!pp->msi_करोमुख्य) अणु
		dev_err(pci->dev, "Failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(pp->irq_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_pcie_मुक्त_msi(काष्ठा pcie_port *pp)
अणु
	अगर (pp->msi_irq)
		irq_set_chained_handler_and_data(pp->msi_irq, शून्य, शून्य);

	irq_करोमुख्य_हटाओ(pp->msi_करोमुख्य);
	irq_करोमुख्य_हटाओ(pp->irq_करोमुख्य);

	अगर (pp->msi_data) अणु
		काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
		काष्ठा device *dev = pci->dev;

		dma_unmap_single_attrs(dev, pp->msi_data, माप(pp->msi_msg),
				       DMA_FROM_DEVICE, DMA_ATTR_SKIP_CPU_SYNC);
	पूर्ण
पूर्ण

अटल व्योम dw_pcie_msi_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	u64 msi_target = (u64)pp->msi_data;

	अगर (!pci_msi_enabled() || !pp->has_msi_ctrl)
		वापस;

	/* Program the msi_data */
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_MSI_ADDR_LO, lower_32_bits(msi_target));
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_MSI_ADDR_HI, upper_32_bits(msi_target));
पूर्ण

पूर्णांक dw_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा device *dev = pci->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource_entry *win;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा resource *cfg_res;
	पूर्णांक ret;

	raw_spin_lock_init(&pci->pp.lock);

	cfg_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "config");
	अगर (cfg_res) अणु
		pp->cfg0_size = resource_size(cfg_res);
		pp->cfg0_base = cfg_res->start;

		pp->va_cfg0_base = devm_pci_remap_cfg_resource(dev, cfg_res);
		अगर (IS_ERR(pp->va_cfg0_base))
			वापस PTR_ERR(pp->va_cfg0_base);
	पूर्ण अन्यथा अणु
		dev_err(dev, "Missing *config* reg space\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!pci->dbi_base) अणु
		काष्ठा resource *dbi_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
		pci->dbi_base = devm_pci_remap_cfg_resource(dev, dbi_res);
		अगर (IS_ERR(pci->dbi_base))
			वापस PTR_ERR(pci->dbi_base);
	पूर्ण

	bridge = devm_pci_alloc_host_bridge(dev, 0);
	अगर (!bridge)
		वापस -ENOMEM;

	pp->bridge = bridge;

	/* Get the I/O range from DT */
	win = resource_list_first_type(&bridge->winकरोws, IORESOURCE_IO);
	अगर (win) अणु
		pp->io_size = resource_size(win->res);
		pp->io_bus_addr = win->res->start - win->offset;
		pp->io_base = pci_pio_to_address(win->res->start);
	पूर्ण

	अगर (pci->link_gen < 1)
		pci->link_gen = of_pci_get_max_link_speed(np);

	अगर (pci_msi_enabled()) अणु
		pp->has_msi_ctrl = !(pp->ops->msi_host_init ||
				     of_property_पढ़ो_bool(np, "msi-parent") ||
				     of_property_पढ़ो_bool(np, "msi-map"));

		अगर (!pp->num_vectors) अणु
			pp->num_vectors = MSI_DEF_NUM_VECTORS;
		पूर्ण अन्यथा अगर (pp->num_vectors > MAX_MSI_IRQS) अणु
			dev_err(dev, "Invalid number of vectors\n");
			वापस -EINVAL;
		पूर्ण

		अगर (pp->ops->msi_host_init) अणु
			ret = pp->ops->msi_host_init(pp);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अगर (pp->has_msi_ctrl) अणु
			अगर (!pp->msi_irq) अणु
				pp->msi_irq = platक्रमm_get_irq_byname_optional(pdev, "msi");
				अगर (pp->msi_irq < 0) अणु
					pp->msi_irq = platक्रमm_get_irq(pdev, 0);
					अगर (pp->msi_irq < 0)
						वापस pp->msi_irq;
				पूर्ण
			पूर्ण

			pp->msi_irq_chip = &dw_pci_msi_bottom_irq_chip;

			ret = dw_pcie_allocate_करोमुख्यs(pp);
			अगर (ret)
				वापस ret;

			अगर (pp->msi_irq > 0)
				irq_set_chained_handler_and_data(pp->msi_irq,
							    dw_chained_msi_isr,
							    pp);

			ret = dma_set_mask(pci->dev, DMA_BIT_MASK(32));
			अगर (ret)
				dev_warn(pci->dev, "Failed to set DMA mask to 32-bit. Devices with only 32-bit MSI support may not work properly\n");

			pp->msi_data = dma_map_single_attrs(pci->dev, &pp->msi_msg,
						      माप(pp->msi_msg),
						      DMA_FROM_DEVICE,
						      DMA_ATTR_SKIP_CPU_SYNC);
			अगर (dma_mapping_error(pci->dev, pp->msi_data)) अणु
				dev_err(pci->dev, "Failed to map MSI data\n");
				pp->msi_data = 0;
				जाओ err_मुक्त_msi;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Set शेष bus ops */
	bridge->ops = &dw_pcie_ops;
	bridge->child_ops = &dw_child_pcie_ops;

	अगर (pp->ops->host_init) अणु
		ret = pp->ops->host_init(pp);
		अगर (ret)
			जाओ err_मुक्त_msi;
	पूर्ण
	dw_pcie_iatu_detect(pci);

	dw_pcie_setup_rc(pp);

	अगर (!dw_pcie_link_up(pci) && pci->ops && pci->ops->start_link) अणु
		ret = pci->ops->start_link(pci);
		अगर (ret)
			जाओ err_मुक्त_msi;
	पूर्ण

	/* Ignore errors, the link may come up later */
	dw_pcie_रुको_क्रम_link(pci);

	bridge->sysdata = pp;

	ret = pci_host_probe(bridge);
	अगर (!ret)
		वापस 0;

err_मुक्त_msi:
	अगर (pp->has_msi_ctrl)
		dw_pcie_मुक्त_msi(pp);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_host_init);

व्योम dw_pcie_host_deinit(काष्ठा pcie_port *pp)
अणु
	pci_stop_root_bus(pp->bridge->bus);
	pci_हटाओ_root_bus(pp->bridge->bus);
	अगर (pp->has_msi_ctrl)
		dw_pcie_मुक्त_msi(pp);
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_host_deinit);

अटल व्योम __iomem *dw_pcie_other_conf_map_bus(काष्ठा pci_bus *bus,
						अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	पूर्णांक type;
	u32 busdev;
	काष्ठा pcie_port *pp = bus->sysdata;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);

	/*
	 * Checking whether the link is up here is a last line of defense
	 * against platक्रमms that क्रमward errors on the प्रणाली bus as
	 * SError upon PCI configuration transactions issued when the link
	 * is करोwn. This check is racy by definition and करोes not stop
	 * the प्रणाली from triggering an SError अगर the link goes करोwn
	 * after this check is perक्रमmed.
	 */
	अगर (!dw_pcie_link_up(pci))
		वापस शून्य;

	busdev = PCIE_ATU_BUS(bus->number) | PCIE_ATU_DEV(PCI_SLOT(devfn)) |
		 PCIE_ATU_FUNC(PCI_FUNC(devfn));

	अगर (pci_is_root_bus(bus->parent))
		type = PCIE_ATU_TYPE_CFG0;
	अन्यथा
		type = PCIE_ATU_TYPE_CFG1;


	dw_pcie_prog_outbound_atu(pci, 0, type, pp->cfg0_base, busdev, pp->cfg0_size);

	वापस pp->va_cfg0_base + where;
पूर्ण

अटल पूर्णांक dw_pcie_rd_other_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				 पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	पूर्णांक ret;
	काष्ठा pcie_port *pp = bus->sysdata;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);

	ret = pci_generic_config_पढ़ो(bus, devfn, where, size, val);

	अगर (!ret && pci->io_cfg_atu_shared)
		dw_pcie_prog_outbound_atu(pci, 0, PCIE_ATU_TYPE_IO, pp->io_base,
					  pp->io_bus_addr, pp->io_size);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_pcie_wr_other_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				 पूर्णांक where, पूर्णांक size, u32 val)
अणु
	पूर्णांक ret;
	काष्ठा pcie_port *pp = bus->sysdata;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);

	ret = pci_generic_config_ग_लिखो(bus, devfn, where, size, val);

	अगर (!ret && pci->io_cfg_atu_shared)
		dw_pcie_prog_outbound_atu(pci, 0, PCIE_ATU_TYPE_IO, pp->io_base,
					  pp->io_bus_addr, pp->io_size);

	वापस ret;
पूर्ण

अटल काष्ठा pci_ops dw_child_pcie_ops = अणु
	.map_bus = dw_pcie_other_conf_map_bus,
	.पढ़ो = dw_pcie_rd_other_conf,
	.ग_लिखो = dw_pcie_wr_other_conf,
पूर्ण;

व्योम __iomem *dw_pcie_own_conf_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा pcie_port *pp = bus->sysdata;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);

	अगर (PCI_SLOT(devfn) > 0)
		वापस शून्य;

	वापस pci->dbi_base + where;
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_own_conf_map_bus);

अटल काष्ठा pci_ops dw_pcie_ops = अणु
	.map_bus = dw_pcie_own_conf_map_bus,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

व्योम dw_pcie_setup_rc(काष्ठा pcie_port *pp)
अणु
	पूर्णांक i;
	u32 val, ctrl, num_ctrls;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);

	/*
	 * Enable DBI पढ़ो-only रेजिस्टरs क्रम writing/updating configuration.
	 * Write permission माला_लो disabled towards the end of this function.
	 */
	dw_pcie_dbi_ro_wr_en(pci);

	dw_pcie_setup(pci);

	अगर (pp->has_msi_ctrl) अणु
		num_ctrls = pp->num_vectors / MAX_MSI_IRQS_PER_CTRL;

		/* Initialize IRQ Status array */
		क्रम (ctrl = 0; ctrl < num_ctrls; ctrl++) अणु
			pp->irq_mask[ctrl] = ~0;
			dw_pcie_ग_लिखोl_dbi(pci, PCIE_MSI_INTR0_MASK +
					    (ctrl * MSI_REG_CTRL_BLOCK_SIZE),
					    pp->irq_mask[ctrl]);
			dw_pcie_ग_लिखोl_dbi(pci, PCIE_MSI_INTR0_ENABLE +
					    (ctrl * MSI_REG_CTRL_BLOCK_SIZE),
					    ~0);
		पूर्ण
	पूर्ण

	dw_pcie_msi_init(pp);

	/* Setup RC BARs */
	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_0, 0x00000004);
	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_1, 0x00000000);

	/* Setup पूर्णांकerrupt pins */
	val = dw_pcie_पढ़ोl_dbi(pci, PCI_INTERRUPT_LINE);
	val &= 0xffff00ff;
	val |= 0x00000100;
	dw_pcie_ग_लिखोl_dbi(pci, PCI_INTERRUPT_LINE, val);

	/* Setup bus numbers */
	val = dw_pcie_पढ़ोl_dbi(pci, PCI_PRIMARY_BUS);
	val &= 0xff000000;
	val |= 0x00ff0100;
	dw_pcie_ग_लिखोl_dbi(pci, PCI_PRIMARY_BUS, val);

	/* Setup command रेजिस्टर */
	val = dw_pcie_पढ़ोl_dbi(pci, PCI_COMMAND);
	val &= 0xffff0000;
	val |= PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
		PCI_COMMAND_MASTER | PCI_COMMAND_SERR;
	dw_pcie_ग_लिखोl_dbi(pci, PCI_COMMAND, val);

	/* Ensure all outbound winकरोws are disabled so there are multiple matches */
	क्रम (i = 0; i < pci->num_ob_winकरोws; i++)
		dw_pcie_disable_atu(pci, i, DW_PCIE_REGION_OUTBOUND);

	/*
	 * If the platक्रमm provides its own child bus config accesses, it means
	 * the platक्रमm uses its own address translation component rather than
	 * ATU, so we should not program the ATU here.
	 */
	अगर (pp->bridge->child_ops == &dw_child_pcie_ops) अणु
		पूर्णांक atu_idx = 0;
		काष्ठा resource_entry *entry;

		/* Get last memory resource entry */
		resource_list_क्रम_each_entry(entry, &pp->bridge->winकरोws) अणु
			अगर (resource_type(entry->res) != IORESOURCE_MEM)
				जारी;

			अगर (pci->num_ob_winकरोws <= ++atu_idx)
				अवरोध;

			dw_pcie_prog_outbound_atu(pci, atu_idx,
						  PCIE_ATU_TYPE_MEM, entry->res->start,
						  entry->res->start - entry->offset,
						  resource_size(entry->res));
		पूर्ण

		अगर (pp->io_size) अणु
			अगर (pci->num_ob_winकरोws > ++atu_idx)
				dw_pcie_prog_outbound_atu(pci, atu_idx,
							  PCIE_ATU_TYPE_IO, pp->io_base,
							  pp->io_bus_addr, pp->io_size);
			अन्यथा
				pci->io_cfg_atu_shared = true;
		पूर्ण

		अगर (pci->num_ob_winकरोws <= atu_idx)
			dev_warn(pci->dev, "Resources exceed number of ATU entries (%d)",
				 pci->num_ob_winकरोws);
	पूर्ण

	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_0, 0);

	/* Program correct class क्रम RC */
	dw_pcie_ग_लिखोw_dbi(pci, PCI_CLASS_DEVICE, PCI_CLASS_BRIDGE_PCI);

	val = dw_pcie_पढ़ोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
	val |= PORT_LOGIC_SPEED_CHANGE;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);

	dw_pcie_dbi_ro_wr_dis(pci);
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_setup_rc);
