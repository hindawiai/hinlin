<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Mobiveil PCIe Host controller
 *
 * Copyright (c) 2018 Mobiveil Inc.
 * Copyright 2019-2020 NXP
 *
 * Author: Subrahmanya Lingappa <l.subrahmanya@mobiveil.co.in>
 *	   Hou Zhiqiang <Zhiqiang.Hou@nxp.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "pcie-mobiveil.h"

अटल bool mobiveil_pcie_valid_device(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn)
अणु
	/* Only one device करोwn on each root port */
	अगर (pci_is_root_bus(bus) && (devfn > 0))
		वापस false;

	/*
	 * Do not पढ़ो more than one device on the bus directly
	 * attached to RC
	 */
	अगर ((bus->primary == to_pci_host_bridge(bus->bridge)->busnr) && (PCI_SLOT(devfn) > 0))
		वापस false;

	वापस true;
पूर्ण

/*
 * mobiveil_pcie_map_bus - routine to get the configuration base of either
 * root port or endpoपूर्णांक
 */
अटल व्योम __iomem *mobiveil_pcie_map_bus(काष्ठा pci_bus *bus,
					   अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा mobiveil_pcie *pcie = bus->sysdata;
	काष्ठा mobiveil_root_port *rp = &pcie->rp;
	u32 value;

	अगर (!mobiveil_pcie_valid_device(bus, devfn))
		वापस शून्य;

	/* RC config access */
	अगर (pci_is_root_bus(bus))
		वापस pcie->csr_axi_slave_base + where;

	/*
	 * EP config access (in Config/APIO space)
	 * Program PEX Address base (31..16 bits) with appropriate value
	 * (BDF) in PAB_AXI_AMAP_PEX_WIN_L0 Register.
	 * Relies on pci_lock serialization
	 */
	value = bus->number << PAB_BUS_SHIFT |
		PCI_SLOT(devfn) << PAB_DEVICE_SHIFT |
		PCI_FUNC(devfn) << PAB_FUNCTION_SHIFT;

	mobiveil_csr_ग_लिखोl(pcie, value, PAB_AXI_AMAP_PEX_WIN_L(WIN_NUM_0));

	वापस rp->config_axi_slave_base + where;
पूर्ण

अटल काष्ठा pci_ops mobiveil_pcie_ops = अणु
	.map_bus = mobiveil_pcie_map_bus,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

अटल व्योम mobiveil_pcie_isr(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा mobiveil_pcie *pcie = irq_desc_get_handler_data(desc);
	काष्ठा device *dev = &pcie->pdev->dev;
	काष्ठा mobiveil_root_port *rp = &pcie->rp;
	काष्ठा mobiveil_msi *msi = &rp->msi;
	u32 msi_data, msi_addr_lo, msi_addr_hi;
	u32 पूर्णांकr_status, msi_status;
	अचिन्हित दीर्घ shअगरted_status;
	u32 bit, virq, val, mask;

	/*
	 * The core provides a single पूर्णांकerrupt क्रम both INTx/MSI messages.
	 * So we'll पढ़ो both INTx and MSI status
	 */

	chained_irq_enter(chip, desc);

	/* पढ़ो INTx status */
	val = mobiveil_csr_पढ़ोl(pcie, PAB_INTP_AMBA_MISC_STAT);
	mask = mobiveil_csr_पढ़ोl(pcie, PAB_INTP_AMBA_MISC_ENB);
	पूर्णांकr_status = val & mask;

	/* Handle INTx */
	अगर (पूर्णांकr_status & PAB_INTP_INTX_MASK) अणु
		shअगरted_status = mobiveil_csr_पढ़ोl(pcie,
						    PAB_INTP_AMBA_MISC_STAT);
		shअगरted_status &= PAB_INTP_INTX_MASK;
		shअगरted_status >>= PAB_INTX_START;
		करो अणु
			क्रम_each_set_bit(bit, &shअगरted_status, PCI_NUM_INTX) अणु
				virq = irq_find_mapping(rp->पूर्णांकx_करोमुख्य,
							bit + 1);
				अगर (virq)
					generic_handle_irq(virq);
				अन्यथा
					dev_err_ratelimited(dev, "unexpected IRQ, INT%d\n",
							    bit);

				/* clear पूर्णांकerrupt handled */
				mobiveil_csr_ग_लिखोl(pcie,
						    1 << (PAB_INTX_START + bit),
						    PAB_INTP_AMBA_MISC_STAT);
			पूर्ण

			shअगरted_status = mobiveil_csr_पढ़ोl(pcie,
							    PAB_INTP_AMBA_MISC_STAT);
			shअगरted_status &= PAB_INTP_INTX_MASK;
			shअगरted_status >>= PAB_INTX_START;
		पूर्ण जबतक (shअगरted_status != 0);
	पूर्ण

	/* पढ़ो extra MSI status रेजिस्टर */
	msi_status = पढ़ोl_relaxed(pcie->apb_csr_base + MSI_STATUS_OFFSET);

	/* handle MSI पूर्णांकerrupts */
	जबतक (msi_status & 1) अणु
		msi_data = पढ़ोl_relaxed(pcie->apb_csr_base + MSI_DATA_OFFSET);

		/*
		 * MSI_STATUS_OFFSET रेजिस्टर माला_लो updated to zero
		 * once we pop not only the MSI data but also address
		 * from MSI hardware FIFO. So keeping these following
		 * two dummy पढ़ोs.
		 */
		msi_addr_lo = पढ़ोl_relaxed(pcie->apb_csr_base +
					    MSI_ADDR_L_OFFSET);
		msi_addr_hi = पढ़ोl_relaxed(pcie->apb_csr_base +
					    MSI_ADDR_H_OFFSET);
		dev_dbg(dev, "MSI registers, data: %08x, addr: %08x:%08x\n",
			msi_data, msi_addr_hi, msi_addr_lo);

		virq = irq_find_mapping(msi->dev_करोमुख्य, msi_data);
		अगर (virq)
			generic_handle_irq(virq);

		msi_status = पढ़ोl_relaxed(pcie->apb_csr_base +
					   MSI_STATUS_OFFSET);
	पूर्ण

	/* Clear the पूर्णांकerrupt status */
	mobiveil_csr_ग_लिखोl(pcie, पूर्णांकr_status, PAB_INTP_AMBA_MISC_STAT);
	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक mobiveil_pcie_parse_dt(काष्ठा mobiveil_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	काष्ठा platक्रमm_device *pdev = pcie->pdev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा mobiveil_root_port *rp = &pcie->rp;
	काष्ठा resource *res;

	/* map config resource */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "config_axi_slave");
	rp->config_axi_slave_base = devm_pci_remap_cfg_resource(dev, res);
	अगर (IS_ERR(rp->config_axi_slave_base))
		वापस PTR_ERR(rp->config_axi_slave_base);
	rp->ob_io_res = res;

	/* map csr resource */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "csr_axi_slave");
	pcie->csr_axi_slave_base = devm_pci_remap_cfg_resource(dev, res);
	अगर (IS_ERR(pcie->csr_axi_slave_base))
		वापस PTR_ERR(pcie->csr_axi_slave_base);
	pcie->pcie_reg_base = res->start;

	/* पढ़ो the number of winकरोws requested */
	अगर (of_property_पढ़ो_u32(node, "apio-wins", &pcie->apio_wins))
		pcie->apio_wins = MAX_PIO_WINDOWS;

	अगर (of_property_पढ़ो_u32(node, "ppio-wins", &pcie->ppio_wins))
		pcie->ppio_wins = MAX_PIO_WINDOWS;

	वापस 0;
पूर्ण

अटल व्योम mobiveil_pcie_enable_msi(काष्ठा mobiveil_pcie *pcie)
अणु
	phys_addr_t msg_addr = pcie->pcie_reg_base;
	काष्ठा mobiveil_msi *msi = &pcie->rp.msi;

	msi->num_of_vectors = PCI_NUM_MSI;
	msi->msi_pages_phys = (phys_addr_t)msg_addr;

	ग_लिखोl_relaxed(lower_32_bits(msg_addr),
		       pcie->apb_csr_base + MSI_BASE_LO_OFFSET);
	ग_लिखोl_relaxed(upper_32_bits(msg_addr),
		       pcie->apb_csr_base + MSI_BASE_HI_OFFSET);
	ग_लिखोl_relaxed(4096, pcie->apb_csr_base + MSI_SIZE_OFFSET);
	ग_लिखोl_relaxed(1, pcie->apb_csr_base + MSI_ENABLE_OFFSET);
पूर्ण

पूर्णांक mobiveil_host_init(काष्ठा mobiveil_pcie *pcie, bool reinit)
अणु
	काष्ठा mobiveil_root_port *rp = &pcie->rp;
	काष्ठा pci_host_bridge *bridge = rp->bridge;
	u32 value, pab_ctrl, type;
	काष्ठा resource_entry *win;

	pcie->ib_wins_configured = 0;
	pcie->ob_wins_configured = 0;

	अगर (!reinit) अणु
		/* setup bus numbers */
		value = mobiveil_csr_पढ़ोl(pcie, PCI_PRIMARY_BUS);
		value &= 0xff000000;
		value |= 0x00ff0100;
		mobiveil_csr_ग_लिखोl(pcie, value, PCI_PRIMARY_BUS);
	पूर्ण

	/*
	 * program Bus Master Enable Bit in Command Register in PAB Config
	 * Space
	 */
	value = mobiveil_csr_पढ़ोl(pcie, PCI_COMMAND);
	value |= PCI_COMMAND_IO | PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER;
	mobiveil_csr_ग_लिखोl(pcie, value, PCI_COMMAND);

	/*
	 * program PIO Enable Bit to 1 (and PEX PIO Enable to 1) in PAB_CTRL
	 * रेजिस्टर
	 */
	pab_ctrl = mobiveil_csr_पढ़ोl(pcie, PAB_CTRL);
	pab_ctrl |= (1 << AMBA_PIO_ENABLE_SHIFT) | (1 << PEX_PIO_ENABLE_SHIFT);
	mobiveil_csr_ग_लिखोl(pcie, pab_ctrl, PAB_CTRL);

	/*
	 * program PIO Enable Bit to 1 and Config Winकरोw Enable Bit to 1 in
	 * PAB_AXI_PIO_CTRL Register
	 */
	value = mobiveil_csr_पढ़ोl(pcie, PAB_AXI_PIO_CTRL);
	value |= APIO_EN_MASK;
	mobiveil_csr_ग_लिखोl(pcie, value, PAB_AXI_PIO_CTRL);

	/* Enable PCIe PIO master */
	value = mobiveil_csr_पढ़ोl(pcie, PAB_PEX_PIO_CTRL);
	value |= 1 << PIO_ENABLE_SHIFT;
	mobiveil_csr_ग_लिखोl(pcie, value, PAB_PEX_PIO_CTRL);

	/*
	 * we'll program one outbound winकरोw क्रम config पढ़ोs and
	 * another शेष inbound winकरोw क्रम all the upstream traffic
	 * rest of the outbound winकरोws will be configured according to
	 * the "ranges" field defined in device tree
	 */

	/* config outbound translation winकरोw */
	program_ob_winकरोws(pcie, WIN_NUM_0, rp->ob_io_res->start, 0,
			   CFG_WINDOW_TYPE, resource_size(rp->ob_io_res));

	/* memory inbound translation winकरोw */
	program_ib_winकरोws(pcie, WIN_NUM_0, 0, 0, MEM_WINDOW_TYPE, IB_WIN_SIZE);

	/* Get the I/O and memory ranges from DT */
	resource_list_क्रम_each_entry(win, &bridge->winकरोws) अणु
		अगर (resource_type(win->res) == IORESOURCE_MEM)
			type = MEM_WINDOW_TYPE;
		अन्यथा अगर (resource_type(win->res) == IORESOURCE_IO)
			type = IO_WINDOW_TYPE;
		अन्यथा
			जारी;

		/* configure outbound translation winकरोw */
		program_ob_winकरोws(pcie, pcie->ob_wins_configured,
				   win->res->start,
				   win->res->start - win->offset,
				   type, resource_size(win->res));
	पूर्ण

	/* fixup क्रम PCIe class रेजिस्टर */
	value = mobiveil_csr_पढ़ोl(pcie, PAB_INTP_AXI_PIO_CLASS);
	value &= 0xff;
	value |= (PCI_CLASS_BRIDGE_PCI << 16);
	mobiveil_csr_ग_लिखोl(pcie, value, PAB_INTP_AXI_PIO_CLASS);

	वापस 0;
पूर्ण

अटल व्योम mobiveil_mask_पूर्णांकx_irq(काष्ठा irq_data *data)
अणु
	काष्ठा mobiveil_pcie *pcie = irq_data_get_irq_chip_data(data);
	काष्ठा mobiveil_root_port *rp;
	अचिन्हित दीर्घ flags;
	u32 mask, shअगरted_val;

	rp = &pcie->rp;
	mask = 1 << ((data->hwirq + PAB_INTX_START) - 1);
	raw_spin_lock_irqsave(&rp->पूर्णांकx_mask_lock, flags);
	shअगरted_val = mobiveil_csr_पढ़ोl(pcie, PAB_INTP_AMBA_MISC_ENB);
	shअगरted_val &= ~mask;
	mobiveil_csr_ग_लिखोl(pcie, shअगरted_val, PAB_INTP_AMBA_MISC_ENB);
	raw_spin_unlock_irqrestore(&rp->पूर्णांकx_mask_lock, flags);
पूर्ण

अटल व्योम mobiveil_unmask_पूर्णांकx_irq(काष्ठा irq_data *data)
अणु
	काष्ठा mobiveil_pcie *pcie = irq_data_get_irq_chip_data(data);
	काष्ठा mobiveil_root_port *rp;
	अचिन्हित दीर्घ flags;
	u32 shअगरted_val, mask;

	rp = &pcie->rp;
	mask = 1 << ((data->hwirq + PAB_INTX_START) - 1);
	raw_spin_lock_irqsave(&rp->पूर्णांकx_mask_lock, flags);
	shअगरted_val = mobiveil_csr_पढ़ोl(pcie, PAB_INTP_AMBA_MISC_ENB);
	shअगरted_val |= mask;
	mobiveil_csr_ग_लिखोl(pcie, shअगरted_val, PAB_INTP_AMBA_MISC_ENB);
	raw_spin_unlock_irqrestore(&rp->पूर्णांकx_mask_lock, flags);
पूर्ण

अटल काष्ठा irq_chip पूर्णांकx_irq_chip = अणु
	.name = "mobiveil_pcie:intx",
	.irq_enable = mobiveil_unmask_पूर्णांकx_irq,
	.irq_disable = mobiveil_mask_पूर्णांकx_irq,
	.irq_mask = mobiveil_mask_पूर्णांकx_irq,
	.irq_unmask = mobiveil_unmask_पूर्णांकx_irq,
पूर्ण;

/* routine to setup the INTx related data */
अटल पूर्णांक mobiveil_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
				  irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &पूर्णांकx_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

/* INTx करोमुख्य operations काष्ठाure */
अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकx_करोमुख्य_ops = अणु
	.map = mobiveil_pcie_पूर्णांकx_map,
पूर्ण;

अटल काष्ठा irq_chip mobiveil_msi_irq_chip = अणु
	.name = "Mobiveil PCIe MSI",
	.irq_mask = pci_msi_mask_irq,
	.irq_unmask = pci_msi_unmask_irq,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info mobiveil_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_PCI_MSIX),
	.chip	= &mobiveil_msi_irq_chip,
पूर्ण;

अटल व्योम mobiveil_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा mobiveil_pcie *pcie = irq_data_get_irq_chip_data(data);
	phys_addr_t addr = pcie->pcie_reg_base + (data->hwirq * माप(पूर्णांक));

	msg->address_lo = lower_32_bits(addr);
	msg->address_hi = upper_32_bits(addr);
	msg->data = data->hwirq;

	dev_dbg(&pcie->pdev->dev, "msi#%d address_hi %#x address_lo %#x\n",
		(पूर्णांक)data->hwirq, msg->address_hi, msg->address_lo);
पूर्ण

अटल पूर्णांक mobiveil_msi_set_affinity(काष्ठा irq_data *irq_data,
				     स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल काष्ठा irq_chip mobiveil_msi_bottom_irq_chip = अणु
	.name			= "Mobiveil MSI",
	.irq_compose_msi_msg	= mobiveil_compose_msi_msg,
	.irq_set_affinity	= mobiveil_msi_set_affinity,
पूर्ण;

अटल पूर्णांक mobiveil_irq_msi_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					 अचिन्हित पूर्णांक virq,
					 अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा mobiveil_pcie *pcie = करोमुख्य->host_data;
	काष्ठा mobiveil_msi *msi = &pcie->rp.msi;
	अचिन्हित दीर्घ bit;

	WARN_ON(nr_irqs != 1);
	mutex_lock(&msi->lock);

	bit = find_first_zero_bit(msi->msi_irq_in_use, msi->num_of_vectors);
	अगर (bit >= msi->num_of_vectors) अणु
		mutex_unlock(&msi->lock);
		वापस -ENOSPC;
	पूर्ण

	set_bit(bit, msi->msi_irq_in_use);

	mutex_unlock(&msi->lock);

	irq_करोमुख्य_set_info(करोमुख्य, virq, bit, &mobiveil_msi_bottom_irq_chip,
			    करोमुख्य->host_data, handle_level_irq, शून्य, शून्य);
	वापस 0;
पूर्ण

अटल व्योम mobiveil_irq_msi_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
					 अचिन्हित पूर्णांक virq,
					 अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा mobiveil_pcie *pcie = irq_data_get_irq_chip_data(d);
	काष्ठा mobiveil_msi *msi = &pcie->rp.msi;

	mutex_lock(&msi->lock);

	अगर (!test_bit(d->hwirq, msi->msi_irq_in_use))
		dev_err(&pcie->pdev->dev, "trying to free unused MSI#%lu\n",
			d->hwirq);
	अन्यथा
		__clear_bit(d->hwirq, msi->msi_irq_in_use);

	mutex_unlock(&msi->lock);
पूर्ण
अटल स्थिर काष्ठा irq_करोमुख्य_ops msi_करोमुख्य_ops = अणु
	.alloc	= mobiveil_irq_msi_करोमुख्य_alloc,
	.मुक्त	= mobiveil_irq_msi_करोमुख्य_मुक्त,
पूर्ण;

अटल पूर्णांक mobiveil_allocate_msi_करोमुख्यs(काष्ठा mobiveil_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	काष्ठा fwnode_handle *fwnode = of_node_to_fwnode(dev->of_node);
	काष्ठा mobiveil_msi *msi = &pcie->rp.msi;

	mutex_init(&msi->lock);
	msi->dev_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, msi->num_of_vectors,
						&msi_करोमुख्य_ops, pcie);
	अगर (!msi->dev_करोमुख्य) अणु
		dev_err(dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	msi->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode,
						    &mobiveil_msi_करोमुख्य_info,
						    msi->dev_करोमुख्य);
	अगर (!msi->msi_करोमुख्य) अणु
		dev_err(dev, "failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(msi->dev_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mobiveil_pcie_init_irq_करोमुख्य(काष्ठा mobiveil_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा mobiveil_root_port *rp = &pcie->rp;

	/* setup INTx */
	rp->पूर्णांकx_करोमुख्य = irq_करोमुख्य_add_linear(node, PCI_NUM_INTX,
						&पूर्णांकx_करोमुख्य_ops, pcie);

	अगर (!rp->पूर्णांकx_करोमुख्य) अणु
		dev_err(dev, "Failed to get a INTx IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	raw_spin_lock_init(&rp->पूर्णांकx_mask_lock);

	/* setup MSI */
	वापस mobiveil_allocate_msi_करोमुख्यs(pcie);
पूर्ण

अटल पूर्णांक mobiveil_pcie_पूर्णांकegrated_पूर्णांकerrupt_init(काष्ठा mobiveil_pcie *pcie)
अणु
	काष्ठा platक्रमm_device *pdev = pcie->pdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mobiveil_root_port *rp = &pcie->rp;
	काष्ठा resource *res;
	पूर्णांक ret;

	/* map MSI config resource */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "apb_csr");
	pcie->apb_csr_base = devm_pci_remap_cfg_resource(dev, res);
	अगर (IS_ERR(pcie->apb_csr_base))
		वापस PTR_ERR(pcie->apb_csr_base);

	/* setup MSI hardware रेजिस्टरs */
	mobiveil_pcie_enable_msi(pcie);

	rp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (rp->irq < 0)
		वापस rp->irq;

	/* initialize the IRQ करोमुख्यs */
	ret = mobiveil_pcie_init_irq_करोमुख्य(pcie);
	अगर (ret) अणु
		dev_err(dev, "Failed creating IRQ Domain\n");
		वापस ret;
	पूर्ण

	irq_set_chained_handler_and_data(rp->irq, mobiveil_pcie_isr, pcie);

	/* Enable पूर्णांकerrupts */
	mobiveil_csr_ग_लिखोl(pcie, (PAB_INTP_INTX_MASK | PAB_INTP_MSI_MASK),
			    PAB_INTP_AMBA_MISC_ENB);


	वापस 0;
पूर्ण

अटल पूर्णांक mobiveil_pcie_पूर्णांकerrupt_init(काष्ठा mobiveil_pcie *pcie)
अणु
	काष्ठा mobiveil_root_port *rp = &pcie->rp;

	अगर (rp->ops->पूर्णांकerrupt_init)
		वापस rp->ops->पूर्णांकerrupt_init(pcie);

	वापस mobiveil_pcie_पूर्णांकegrated_पूर्णांकerrupt_init(pcie);
पूर्ण

अटल bool mobiveil_pcie_is_bridge(काष्ठा mobiveil_pcie *pcie)
अणु
	u32 header_type;

	header_type = mobiveil_csr_पढ़ोb(pcie, PCI_HEADER_TYPE);
	header_type &= 0x7f;

	वापस header_type == PCI_HEADER_TYPE_BRIDGE;
पूर्ण

पूर्णांक mobiveil_pcie_host_probe(काष्ठा mobiveil_pcie *pcie)
अणु
	काष्ठा mobiveil_root_port *rp = &pcie->rp;
	काष्ठा pci_host_bridge *bridge = rp->bridge;
	काष्ठा device *dev = &pcie->pdev->dev;
	पूर्णांक ret;

	ret = mobiveil_pcie_parse_dt(pcie);
	अगर (ret) अणु
		dev_err(dev, "Parsing DT failed, ret: %x\n", ret);
		वापस ret;
	पूर्ण

	अगर (!mobiveil_pcie_is_bridge(pcie))
		वापस -ENODEV;

	/*
	 * configure all inbound and outbound winकरोws and prepare the RC क्रम
	 * config access
	 */
	ret = mobiveil_host_init(pcie, false);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize host\n");
		वापस ret;
	पूर्ण

	ret = mobiveil_pcie_पूर्णांकerrupt_init(pcie);
	अगर (ret) अणु
		dev_err(dev, "Interrupt init failed\n");
		वापस ret;
	पूर्ण

	/* Initialize bridge */
	bridge->sysdata = pcie;
	bridge->ops = &mobiveil_pcie_ops;

	ret = mobiveil_bringup_link(pcie);
	अगर (ret) अणु
		dev_info(dev, "link bring-up failed\n");
		वापस ret;
	पूर्ण

	वापस pci_host_probe(bridge);
पूर्ण
