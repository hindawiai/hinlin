<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Ralink RT3662/RT3883 SoC PCI support
 *
 *  Copyright (C) 2011-2013 Gabor Juhos <juhosg@खोलोwrt.org>
 *
 *  Parts of this file are based on Ralink's 2.6.21 BSP
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-ralink/rt3883.h>
#समावेश <यंत्र/mach-ralink/ralink_regs.h>

#घोषणा RT3883_MEMORY_BASE		0x00000000
#घोषणा RT3883_MEMORY_SIZE		0x02000000

#घोषणा RT3883_PCI_REG_PCICFG		0x00
#घोषणा   RT3883_PCICFG_P2P_BR_DEVNUM_M 0xf
#घोषणा   RT3883_PCICFG_P2P_BR_DEVNUM_S 16
#घोषणा   RT3883_PCICFG_PCIRST		BIT(1)
#घोषणा RT3883_PCI_REG_PCIRAW		0x04
#घोषणा RT3883_PCI_REG_PCIINT		0x08
#घोषणा RT3883_PCI_REG_PCIENA		0x0c

#घोषणा RT3883_PCI_REG_CFGADDR		0x20
#घोषणा RT3883_PCI_REG_CFGDATA		0x24
#घोषणा RT3883_PCI_REG_MEMBASE		0x28
#घोषणा RT3883_PCI_REG_IOBASE		0x2c
#घोषणा RT3883_PCI_REG_ARBCTL		0x80

#घोषणा RT3883_PCI_REG_BASE(_x)		(0x1000 + (_x) * 0x1000)
#घोषणा RT3883_PCI_REG_BAR0SETUP(_x)	(RT3883_PCI_REG_BASE((_x)) + 0x10)
#घोषणा RT3883_PCI_REG_IMBASEBAR0(_x)	(RT3883_PCI_REG_BASE((_x)) + 0x18)
#घोषणा RT3883_PCI_REG_ID(_x)		(RT3883_PCI_REG_BASE((_x)) + 0x30)
#घोषणा RT3883_PCI_REG_CLASS(_x)	(RT3883_PCI_REG_BASE((_x)) + 0x34)
#घोषणा RT3883_PCI_REG_SUBID(_x)	(RT3883_PCI_REG_BASE((_x)) + 0x38)
#घोषणा RT3883_PCI_REG_STATUS(_x)	(RT3883_PCI_REG_BASE((_x)) + 0x50)

#घोषणा RT3883_PCI_MODE_NONE	0
#घोषणा RT3883_PCI_MODE_PCI	BIT(0)
#घोषणा RT3883_PCI_MODE_PCIE	BIT(1)
#घोषणा RT3883_PCI_MODE_BOTH	(RT3883_PCI_MODE_PCI | RT3883_PCI_MODE_PCIE)

#घोषणा RT3883_PCI_IRQ_COUNT	32

#घोषणा RT3883_P2P_BR_DEVNUM	1

काष्ठा rt3883_pci_controller अणु
	व्योम __iomem *base;

	काष्ठा device_node *पूर्णांकc_of_node;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;

	काष्ठा pci_controller pci_controller;
	काष्ठा resource io_res;
	काष्ठा resource mem_res;

	bool pcie_पढ़ोy;
पूर्ण;

अटल अंतरभूत काष्ठा rt3883_pci_controller *
pci_bus_to_rt3883_controller(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose;

	hose = (काष्ठा pci_controller *) bus->sysdata;
	वापस container_of(hose, काष्ठा rt3883_pci_controller, pci_controller);
पूर्ण

अटल अंतरभूत u32 rt3883_pci_r32(काष्ठा rt3883_pci_controller *rpc,
				 अचिन्हित reg)
अणु
	वापस ioपढ़ो32(rpc->base + reg);
पूर्ण

अटल अंतरभूत व्योम rt3883_pci_w32(काष्ठा rt3883_pci_controller *rpc,
				  u32 val, अचिन्हित reg)
अणु
	ioग_लिखो32(val, rpc->base + reg);
पूर्ण

अटल अंतरभूत u32 rt3883_pci_get_cfgaddr(अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक slot,
					 अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक where)
अणु
	वापस (bus << 16) | (slot << 11) | (func << 8) | (where & 0xfc) |
	       0x80000000;
पूर्ण

अटल u32 rt3883_pci_पढ़ो_cfg32(काष्ठा rt3883_pci_controller *rpc,
			       अचिन्हित bus, अचिन्हित slot,
			       अचिन्हित func, अचिन्हित reg)
अणु
	u32 address;
	u32 ret;

	address = rt3883_pci_get_cfgaddr(bus, slot, func, reg);

	rt3883_pci_w32(rpc, address, RT3883_PCI_REG_CFGADDR);
	ret = rt3883_pci_r32(rpc, RT3883_PCI_REG_CFGDATA);

	वापस ret;
पूर्ण

अटल व्योम rt3883_pci_ग_लिखो_cfg32(काष्ठा rt3883_pci_controller *rpc,
				 अचिन्हित bus, अचिन्हित slot,
				 अचिन्हित func, अचिन्हित reg, u32 val)
अणु
	u32 address;

	address = rt3883_pci_get_cfgaddr(bus, slot, func, reg);

	rt3883_pci_w32(rpc, address, RT3883_PCI_REG_CFGADDR);
	rt3883_pci_w32(rpc, val, RT3883_PCI_REG_CFGDATA);
पूर्ण

अटल व्योम rt3883_pci_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा rt3883_pci_controller *rpc;
	u32 pending;

	rpc = irq_desc_get_handler_data(desc);

	pending = rt3883_pci_r32(rpc, RT3883_PCI_REG_PCIINT) &
		  rt3883_pci_r32(rpc, RT3883_PCI_REG_PCIENA);

	अगर (!pending) अणु
		spurious_पूर्णांकerrupt();
		वापस;
	पूर्ण

	जबतक (pending) अणु
		अचिन्हित irq, bit = __ffs(pending);

		irq = irq_find_mapping(rpc->irq_करोमुख्य, bit);
		generic_handle_irq(irq);

		pending &= ~BIT(bit);
	पूर्ण
पूर्ण

अटल व्योम rt3883_pci_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा rt3883_pci_controller *rpc;
	u32 t;

	rpc = irq_data_get_irq_chip_data(d);

	t = rt3883_pci_r32(rpc, RT3883_PCI_REG_PCIENA);
	rt3883_pci_w32(rpc, t | BIT(d->hwirq), RT3883_PCI_REG_PCIENA);
	/* flush ग_लिखो */
	rt3883_pci_r32(rpc, RT3883_PCI_REG_PCIENA);
पूर्ण

अटल व्योम rt3883_pci_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा rt3883_pci_controller *rpc;
	u32 t;

	rpc = irq_data_get_irq_chip_data(d);

	t = rt3883_pci_r32(rpc, RT3883_PCI_REG_PCIENA);
	rt3883_pci_w32(rpc, t & ~BIT(d->hwirq), RT3883_PCI_REG_PCIENA);
	/* flush ग_लिखो */
	rt3883_pci_r32(rpc, RT3883_PCI_REG_PCIENA);
पूर्ण

अटल काष्ठा irq_chip rt3883_pci_irq_chip = अणु
	.name		= "RT3883 PCI",
	.irq_mask	= rt3883_pci_irq_mask,
	.irq_unmask	= rt3883_pci_irq_unmask,
	.irq_mask_ack	= rt3883_pci_irq_mask,
पूर्ण;

अटल पूर्णांक rt3883_pci_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			      irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(irq, &rt3883_pci_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, d->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops rt3883_pci_irq_करोमुख्य_ops = अणु
	.map = rt3883_pci_irq_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक rt3883_pci_irq_init(काष्ठा device *dev,
			       काष्ठा rt3883_pci_controller *rpc)
अणु
	पूर्णांक irq;

	irq = irq_of_parse_and_map(rpc->पूर्णांकc_of_node, 0);
	अगर (irq == 0) अणु
		dev_err(dev, "%pOF has no IRQ", rpc->पूर्णांकc_of_node);
		वापस -EINVAL;
	पूर्ण

	/* disable all पूर्णांकerrupts */
	rt3883_pci_w32(rpc, 0, RT3883_PCI_REG_PCIENA);

	rpc->irq_करोमुख्य =
		irq_करोमुख्य_add_linear(rpc->पूर्णांकc_of_node, RT3883_PCI_IRQ_COUNT,
				      &rt3883_pci_irq_करोमुख्य_ops,
				      rpc);
	अगर (!rpc->irq_करोमुख्य) अणु
		dev_err(dev, "unable to add IRQ domain\n");
		वापस -ENODEV;
	पूर्ण

	irq_set_chained_handler_and_data(irq, rt3883_pci_irq_handler, rpc);

	वापस 0;
पूर्ण

अटल पूर्णांक rt3883_pci_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा rt3883_pci_controller *rpc;
	u32 address;
	u32 data;

	rpc = pci_bus_to_rt3883_controller(bus);

	अगर (!rpc->pcie_पढ़ोy && bus->number == 1)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	address = rt3883_pci_get_cfgaddr(bus->number, PCI_SLOT(devfn),
					 PCI_FUNC(devfn), where);

	rt3883_pci_w32(rpc, address, RT3883_PCI_REG_CFGADDR);
	data = rt3883_pci_r32(rpc, RT3883_PCI_REG_CFGDATA);

	चयन (size) अणु
	हाल 1:
		*val = (data >> ((where & 3) << 3)) & 0xff;
		अवरोध;
	हाल 2:
		*val = (data >> ((where & 3) << 3)) & 0xffff;
		अवरोध;
	हाल 4:
		*val = data;
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rt3883_pci_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा rt3883_pci_controller *rpc;
	u32 address;
	u32 data;

	rpc = pci_bus_to_rt3883_controller(bus);

	अगर (!rpc->pcie_पढ़ोy && bus->number == 1)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	address = rt3883_pci_get_cfgaddr(bus->number, PCI_SLOT(devfn),
					 PCI_FUNC(devfn), where);

	rt3883_pci_w32(rpc, address, RT3883_PCI_REG_CFGADDR);
	data = rt3883_pci_r32(rpc, RT3883_PCI_REG_CFGDATA);

	चयन (size) अणु
	हाल 1:
		data = (data & ~(0xff << ((where & 3) << 3))) |
		       (val << ((where & 3) << 3));
		अवरोध;
	हाल 2:
		data = (data & ~(0xffff << ((where & 3) << 3))) |
		       (val << ((where & 3) << 3));
		अवरोध;
	हाल 4:
		data = val;
		अवरोध;
	पूर्ण

	rt3883_pci_w32(rpc, data, RT3883_PCI_REG_CFGDATA);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops rt3883_pci_ops = अणु
	.पढ़ो	= rt3883_pci_config_पढ़ो,
	.ग_लिखो	= rt3883_pci_config_ग_लिखो,
पूर्ण;

अटल व्योम rt3883_pci_preinit(काष्ठा rt3883_pci_controller *rpc, अचिन्हित mode)
अणु
	u32 syscfg1;
	u32 rstctrl;
	u32 clkcfg1;
	u32 t;

	rstctrl = rt_sysc_r32(RT3883_SYSC_REG_RSTCTRL);
	syscfg1 = rt_sysc_r32(RT3883_SYSC_REG_SYSCFG1);
	clkcfg1 = rt_sysc_r32(RT3883_SYSC_REG_CLKCFG1);

	अगर (mode & RT3883_PCI_MODE_PCIE) अणु
		rstctrl |= RT3883_RSTCTRL_PCIE;
		rt_sysc_w32(rstctrl, RT3883_SYSC_REG_RSTCTRL);

		/* setup PCI PAD drive mode */
		syscfg1 &= ~(0x30);
		syscfg1 |= (2 << 4);
		rt_sysc_w32(syscfg1, RT3883_SYSC_REG_SYSCFG1);

		t = rt_sysc_r32(RT3883_SYSC_REG_PCIE_CLK_GEN0);
		t &= ~BIT(31);
		rt_sysc_w32(t, RT3883_SYSC_REG_PCIE_CLK_GEN0);

		t = rt_sysc_r32(RT3883_SYSC_REG_PCIE_CLK_GEN1);
		t &= 0x80ffffff;
		rt_sysc_w32(t, RT3883_SYSC_REG_PCIE_CLK_GEN1);

		t = rt_sysc_r32(RT3883_SYSC_REG_PCIE_CLK_GEN1);
		t |= 0xa << 24;
		rt_sysc_w32(t, RT3883_SYSC_REG_PCIE_CLK_GEN1);

		t = rt_sysc_r32(RT3883_SYSC_REG_PCIE_CLK_GEN0);
		t |= BIT(31);
		rt_sysc_w32(t, RT3883_SYSC_REG_PCIE_CLK_GEN0);

		msleep(50);

		rstctrl &= ~RT3883_RSTCTRL_PCIE;
		rt_sysc_w32(rstctrl, RT3883_SYSC_REG_RSTCTRL);
	पूर्ण

	syscfg1 |= (RT3883_SYSCFG1_PCIE_RC_MODE | RT3883_SYSCFG1_PCI_HOST_MODE);

	clkcfg1 &= ~(RT3883_CLKCFG1_PCI_CLK_EN | RT3883_CLKCFG1_PCIE_CLK_EN);

	अगर (mode & RT3883_PCI_MODE_PCI) अणु
		clkcfg1 |= RT3883_CLKCFG1_PCI_CLK_EN;
		rstctrl &= ~RT3883_RSTCTRL_PCI;
	पूर्ण

	अगर (mode & RT3883_PCI_MODE_PCIE) अणु
		clkcfg1 |= RT3883_CLKCFG1_PCIE_CLK_EN;
		rstctrl &= ~RT3883_RSTCTRL_PCIE;
	पूर्ण

	rt_sysc_w32(syscfg1, RT3883_SYSC_REG_SYSCFG1);
	rt_sysc_w32(rstctrl, RT3883_SYSC_REG_RSTCTRL);
	rt_sysc_w32(clkcfg1, RT3883_SYSC_REG_CLKCFG1);

	msleep(500);

	/*
	 * setup the device number of the P2P bridge
	 * and de-निश्चित the reset line
	 */
	t = (RT3883_P2P_BR_DEVNUM << RT3883_PCICFG_P2P_BR_DEVNUM_S);
	rt3883_pci_w32(rpc, t, RT3883_PCI_REG_PCICFG);

	/* flush ग_लिखो */
	rt3883_pci_r32(rpc, RT3883_PCI_REG_PCICFG);
	msleep(500);

	अगर (mode & RT3883_PCI_MODE_PCIE) अणु
		msleep(500);

		t = rt3883_pci_r32(rpc, RT3883_PCI_REG_STATUS(1));

		rpc->pcie_पढ़ोy = t & BIT(0);

		अगर (!rpc->pcie_पढ़ोy) अणु
			/* reset the PCIe block */
			t = rt_sysc_r32(RT3883_SYSC_REG_RSTCTRL);
			t |= RT3883_RSTCTRL_PCIE;
			rt_sysc_w32(t, RT3883_SYSC_REG_RSTCTRL);
			t &= ~RT3883_RSTCTRL_PCIE;
			rt_sysc_w32(t, RT3883_SYSC_REG_RSTCTRL);

			/* turn off PCIe घड़ी */
			t = rt_sysc_r32(RT3883_SYSC_REG_CLKCFG1);
			t &= ~RT3883_CLKCFG1_PCIE_CLK_EN;
			rt_sysc_w32(t, RT3883_SYSC_REG_CLKCFG1);

			t = rt_sysc_r32(RT3883_SYSC_REG_PCIE_CLK_GEN0);
			t &= ~0xf000c080;
			rt_sysc_w32(t, RT3883_SYSC_REG_PCIE_CLK_GEN0);
		पूर्ण
	पूर्ण

	/* enable PCI arbiter */
	rt3883_pci_w32(rpc, 0x79, RT3883_PCI_REG_ARBCTL);
पूर्ण

अटल पूर्णांक rt3883_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rt3883_pci_controller *rpc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *res;
	काष्ठा device_node *child;
	u32 val;
	पूर्णांक err;
	पूर्णांक mode;

	rpc = devm_kzalloc(dev, माप(*rpc), GFP_KERNEL);
	अगर (!rpc)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rpc->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(rpc->base))
		वापस PTR_ERR(rpc->base);

	/* find the पूर्णांकerrupt controller child node */
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_get_property(child, "interrupt-controller", शून्य)) अणु
			rpc->पूर्णांकc_of_node = child;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rpc->पूर्णांकc_of_node) अणु
		dev_err(dev, "%pOF has no %s child node",
			np, "interrupt controller");
		वापस -EINVAL;
	पूर्ण

	/* find the PCI host bridge child node */
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_node_is_type(child, "pci")) अणु
			rpc->pci_controller.of_node = child;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rpc->pci_controller.of_node) अणु
		dev_err(dev, "%pOF has no %s child node",
			np, "PCI host bridge");
		err = -EINVAL;
		जाओ err_put_पूर्णांकc_node;
	पूर्ण

	mode = RT3883_PCI_MODE_NONE;
	क्रम_each_available_child_of_node(rpc->pci_controller.of_node, child) अणु
		पूर्णांक devfn;

		अगर (!of_node_is_type(child, "pci"))
			जारी;

		devfn = of_pci_get_devfn(child);
		अगर (devfn < 0)
			जारी;

		चयन (PCI_SLOT(devfn)) अणु
		हाल 1:
			mode |= RT3883_PCI_MODE_PCIE;
			अवरोध;

		हाल 17:
		हाल 18:
			mode |= RT3883_PCI_MODE_PCI;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mode == RT3883_PCI_MODE_NONE) अणु
		dev_err(dev, "unable to determine PCI mode\n");
		err = -EINVAL;
		जाओ err_put_hb_node;
	पूर्ण

	dev_info(dev, "mode:%s%s\n",
		 (mode & RT3883_PCI_MODE_PCI) ? " PCI" : "",
		 (mode & RT3883_PCI_MODE_PCIE) ? " PCIe" : "");

	rt3883_pci_preinit(rpc, mode);

	rpc->pci_controller.pci_ops = &rt3883_pci_ops;
	rpc->pci_controller.io_resource = &rpc->io_res;
	rpc->pci_controller.mem_resource = &rpc->mem_res;

	/* Load PCI I/O and memory resources from DT */
	pci_load_of_ranges(&rpc->pci_controller,
			   rpc->pci_controller.of_node);

	rt3883_pci_w32(rpc, rpc->mem_res.start, RT3883_PCI_REG_MEMBASE);
	rt3883_pci_w32(rpc, rpc->io_res.start, RT3883_PCI_REG_IOBASE);

	ioport_resource.start = rpc->io_res.start;
	ioport_resource.end = rpc->io_res.end;

	/* PCI */
	rt3883_pci_w32(rpc, 0x03ff0000, RT3883_PCI_REG_BAR0SETUP(0));
	rt3883_pci_w32(rpc, RT3883_MEMORY_BASE, RT3883_PCI_REG_IMBASEBAR0(0));
	rt3883_pci_w32(rpc, 0x08021814, RT3883_PCI_REG_ID(0));
	rt3883_pci_w32(rpc, 0x00800001, RT3883_PCI_REG_CLASS(0));
	rt3883_pci_w32(rpc, 0x28801814, RT3883_PCI_REG_SUBID(0));

	/* PCIe */
	rt3883_pci_w32(rpc, 0x03ff0000, RT3883_PCI_REG_BAR0SETUP(1));
	rt3883_pci_w32(rpc, RT3883_MEMORY_BASE, RT3883_PCI_REG_IMBASEBAR0(1));
	rt3883_pci_w32(rpc, 0x08021814, RT3883_PCI_REG_ID(1));
	rt3883_pci_w32(rpc, 0x06040001, RT3883_PCI_REG_CLASS(1));
	rt3883_pci_w32(rpc, 0x28801814, RT3883_PCI_REG_SUBID(1));

	err = rt3883_pci_irq_init(dev, rpc);
	अगर (err)
		जाओ err_put_hb_node;

	/* PCIe */
	val = rt3883_pci_पढ़ो_cfg32(rpc, 0, 0x01, 0, PCI_COMMAND);
	val |= PCI_COMMAND_IO | PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER;
	rt3883_pci_ग_लिखो_cfg32(rpc, 0, 0x01, 0, PCI_COMMAND, val);

	/* PCI */
	val = rt3883_pci_पढ़ो_cfg32(rpc, 0, 0x00, 0, PCI_COMMAND);
	val |= PCI_COMMAND_IO | PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER;
	rt3883_pci_ग_लिखो_cfg32(rpc, 0, 0x00, 0, PCI_COMMAND, val);

	अगर (mode == RT3883_PCI_MODE_PCIE) अणु
		rt3883_pci_w32(rpc, 0x03ff0001, RT3883_PCI_REG_BAR0SETUP(0));
		rt3883_pci_w32(rpc, 0x03ff0001, RT3883_PCI_REG_BAR0SETUP(1));

		rt3883_pci_ग_लिखो_cfg32(rpc, 0, RT3883_P2P_BR_DEVNUM, 0,
				       PCI_BASE_ADDRESS_0,
				       RT3883_MEMORY_BASE);
		/* flush ग_लिखो */
		rt3883_pci_पढ़ो_cfg32(rpc, 0, RT3883_P2P_BR_DEVNUM, 0,
				      PCI_BASE_ADDRESS_0);
	पूर्ण अन्यथा अणु
		rt3883_pci_ग_लिखो_cfg32(rpc, 0, RT3883_P2P_BR_DEVNUM, 0,
				       PCI_IO_BASE, 0x00000101);
	पूर्ण

	रेजिस्टर_pci_controller(&rpc->pci_controller);

	वापस 0;

err_put_hb_node:
	of_node_put(rpc->pci_controller.of_node);
err_put_पूर्णांकc_node:
	of_node_put(rpc->पूर्णांकc_of_node);
	वापस err;
पूर्ण

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	वापस of_irq_parse_and_map_pci(dev, slot, pin);
पूर्ण

पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rt3883_pci_ids[] = अणु
	अणु .compatible = "ralink,rt3883-pci" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rt3883_pci_driver = अणु
	.probe = rt3883_pci_probe,
	.driver = अणु
		.name = "rt3883-pci",
		.of_match_table = of_match_ptr(rt3883_pci_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rt3883_pci_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rt3883_pci_driver);
पूर्ण

postcore_initcall(rt3883_pci_init);
