<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * BRIEF MODULE DESCRIPTION
 *     PCI init क्रम Ralink RT2880 solution
 *
 * Copyright 2007 Ralink Inc. (bruce_chang@ralinktech.com.tw)
 *
 * May 2007 Bruce Chang
 * Initial Release
 *
 * May 2009 Bruce Chang
 * support RT2880/RT3883 PCIe
 *
 * May 2011 Bruce Chang
 * support RT6855/MT7620 PCIe
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/sys_soc.h>
#समावेश <mt7621.h>
#समावेश <ralink_regs.h>

#समावेश "../../pci/pci.h"

/* sysctl */
#घोषणा MT7621_GPIO_MODE		0x60

/* MediaTek specअगरic configuration रेजिस्टरs */
#घोषणा PCIE_FTS_NUM			0x70c
#घोषणा PCIE_FTS_NUM_MASK		GENMASK(15, 8)
#घोषणा PCIE_FTS_NUM_L0(x)		(((x) & 0xff) << 8)

/* rt_sysc_membase relative रेजिस्टरs */
#घोषणा RALINK_CLKCFG1			0x30

/* Host-PCI bridge रेजिस्टरs */
#घोषणा RALINK_PCI_PCICFG_ADDR		0x0000
#घोषणा RALINK_PCI_PCIMSK_ADDR		0x000C
#घोषणा RALINK_PCI_CONFIG_ADDR		0x0020
#घोषणा RALINK_PCI_CONFIG_DATA		0x0024
#घोषणा RALINK_PCI_MEMBASE		0x0028
#घोषणा RALINK_PCI_IOBASE		0x002C

/* PCICFG भव bridges */
#घोषणा PCIE_P2P_CNT			3
#घोषणा PCIE_P2P_BR_DEVNUM_SHIFT(p)	(16 + (p) * 4)
#घोषणा PCIE_P2P_BR_DEVNUM0_SHIFT	PCIE_P2P_BR_DEVNUM_SHIFT(0)
#घोषणा PCIE_P2P_BR_DEVNUM1_SHIFT	PCIE_P2P_BR_DEVNUM_SHIFT(1)
#घोषणा PCIE_P2P_BR_DEVNUM2_SHIFT	PCIE_P2P_BR_DEVNUM_SHIFT(2)
#घोषणा PCIE_P2P_BR_DEVNUM_MASK		0xf
#घोषणा PCIE_P2P_BR_DEVNUM_MASK_FULL	(0xfff << PCIE_P2P_BR_DEVNUM0_SHIFT)

/* PCIe RC control रेजिस्टरs */
#घोषणा MT7621_PCIE_OFFSET		0x2000
#घोषणा MT7621_NEXT_PORT		0x1000

#घोषणा RALINK_PCI_BAR0SETUP_ADDR	0x0010
#घोषणा RALINK_PCI_ID			0x0030
#घोषणा RALINK_PCI_CLASS		0x0034
#घोषणा RALINK_PCI_SUBID		0x0038
#घोषणा RALINK_PCI_STATUS		0x0050

/* Some definition values */
#घोषणा PCIE_REVISION_ID		BIT(0)
#घोषणा PCIE_CLASS_CODE			(0x60400 << 8)
#घोषणा PCIE_BAR_MAP_MAX		GENMASK(30, 16)
#घोषणा PCIE_BAR_ENABLE			BIT(0)
#घोषणा PCIE_PORT_INT_EN(x)		BIT(20 + (x))
#घोषणा PCIE_PORT_CLK_EN(x)		BIT(24 + (x))
#घोषणा PCIE_PORT_LINKUP		BIT(0)

#घोषणा PERST_MODE_MASK			GENMASK(11, 10)
#घोषणा PERST_MODE_GPIO			BIT(10)
#घोषणा PERST_DELAY_MS			100

/**
 * काष्ठा mt7621_pcie_port - PCIe port inक्रमmation
 * @base: I/O mapped रेजिस्टर base
 * @list: port list
 * @pcie: poपूर्णांकer to PCIe host info
 * @phy: poपूर्णांकer to PHY control block
 * @pcie_rst: poपूर्णांकer to port reset control
 * @gpio_rst: gpio reset
 * @slot: port slot
 * @irq: GIC irq
 * @enabled: indicates अगर port is enabled
 */
काष्ठा mt7621_pcie_port अणु
	व्योम __iomem *base;
	काष्ठा list_head list;
	काष्ठा mt7621_pcie *pcie;
	काष्ठा phy *phy;
	काष्ठा reset_control *pcie_rst;
	काष्ठा gpio_desc *gpio_rst;
	u32 slot;
	पूर्णांक irq;
	bool enabled;
पूर्ण;

/**
 * काष्ठा mt7621_pcie - PCIe host inक्रमmation
 * @base: IO Mapped Register Base
 * @io: IO resource
 * @mem: poपूर्णांकer to non-prefetchable memory resource
 * @dev: Poपूर्णांकer to PCIe device
 * @io_map_base: भव memory base address क्रम io
 * @ports: poपूर्णांकer to PCIe port inक्रमmation
 * @irq_map: irq mapping info according pcie link status
 * @resets_inverted: depends on chip revision
 * reset lines are inverted.
 */
काष्ठा mt7621_pcie अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा resource io;
	काष्ठा resource *mem;
	अचिन्हित दीर्घ io_map_base;
	काष्ठा list_head ports;
	पूर्णांक irq_map[PCIE_P2P_CNT];
	bool resets_inverted;
पूर्ण;

अटल अंतरभूत u32 pcie_पढ़ो(काष्ठा mt7621_pcie *pcie, u32 reg)
अणु
	वापस पढ़ोl(pcie->base + reg);
पूर्ण

अटल अंतरभूत व्योम pcie_ग_लिखो(काष्ठा mt7621_pcie *pcie, u32 val, u32 reg)
अणु
	ग_लिखोl(val, pcie->base + reg);
पूर्ण

अटल अंतरभूत व्योम pcie_rmw(काष्ठा mt7621_pcie *pcie, u32 reg, u32 clr, u32 set)
अणु
	u32 val = पढ़ोl(pcie->base + reg);

	val &= ~clr;
	val |= set;
	ग_लिखोl(val, pcie->base + reg);
पूर्ण

अटल अंतरभूत u32 pcie_port_पढ़ो(काष्ठा mt7621_pcie_port *port, u32 reg)
अणु
	वापस पढ़ोl(port->base + reg);
पूर्ण

अटल अंतरभूत व्योम pcie_port_ग_लिखो(काष्ठा mt7621_pcie_port *port,
				   u32 val, u32 reg)
अणु
	ग_लिखोl(val, port->base + reg);
पूर्ण

अटल अंतरभूत u32 mt7621_pci_get_cfgaddr(अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक slot,
					 अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक where)
अणु
	वापस (((where & 0xF00) >> 8) << 24) | (bus << 16) | (slot << 11) |
		(func << 8) | (where & 0xfc) | 0x80000000;
पूर्ण

अटल व्योम __iomem *mt7621_pcie_map_bus(काष्ठा pci_bus *bus,
					 अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा mt7621_pcie *pcie = bus->sysdata;
	u32 address = mt7621_pci_get_cfgaddr(bus->number, PCI_SLOT(devfn),
					     PCI_FUNC(devfn), where);

	ग_लिखोl(address, pcie->base + RALINK_PCI_CONFIG_ADDR);

	वापस pcie->base + RALINK_PCI_CONFIG_DATA + (where & 3);
पूर्ण

काष्ठा pci_ops mt7621_pci_ops = अणु
	.map_bus	= mt7621_pcie_map_bus,
	.पढ़ो		= pci_generic_config_पढ़ो,
	.ग_लिखो		= pci_generic_config_ग_लिखो,
पूर्ण;

अटल u32 पढ़ो_config(काष्ठा mt7621_pcie *pcie, अचिन्हित पूर्णांक dev, u32 reg)
अणु
	u32 address = mt7621_pci_get_cfgaddr(0, dev, 0, reg);

	pcie_ग_लिखो(pcie, address, RALINK_PCI_CONFIG_ADDR);
	वापस pcie_पढ़ो(pcie, RALINK_PCI_CONFIG_DATA);
पूर्ण

अटल व्योम ग_लिखो_config(काष्ठा mt7621_pcie *pcie, अचिन्हित पूर्णांक dev,
			 u32 reg, u32 val)
अणु
	u32 address = mt7621_pci_get_cfgaddr(0, dev, 0, reg);

	pcie_ग_लिखो(pcie, address, RALINK_PCI_CONFIG_ADDR);
	pcie_ग_लिखो(pcie, val, RALINK_PCI_CONFIG_DATA);
पूर्ण

अटल अंतरभूत व्योम mt7621_rst_gpio_pcie_निश्चित(काष्ठा mt7621_pcie_port *port)
अणु
	अगर (port->gpio_rst)
		gpiod_set_value(port->gpio_rst, 1);
पूर्ण

अटल अंतरभूत व्योम mt7621_rst_gpio_pcie_deनिश्चित(काष्ठा mt7621_pcie_port *port)
अणु
	अगर (port->gpio_rst)
		gpiod_set_value(port->gpio_rst, 0);
पूर्ण

अटल अंतरभूत bool mt7621_pcie_port_is_linkup(काष्ठा mt7621_pcie_port *port)
अणु
	वापस (pcie_port_पढ़ो(port, RALINK_PCI_STATUS) & PCIE_PORT_LINKUP) != 0;
पूर्ण

अटल अंतरभूत व्योम mt7621_pcie_port_clk_enable(काष्ठा mt7621_pcie_port *port)
अणु
	rt_sysc_m32(0, PCIE_PORT_CLK_EN(port->slot), RALINK_CLKCFG1);
पूर्ण

अटल अंतरभूत व्योम mt7621_pcie_port_clk_disable(काष्ठा mt7621_pcie_port *port)
अणु
	rt_sysc_m32(PCIE_PORT_CLK_EN(port->slot), 0, RALINK_CLKCFG1);
पूर्ण

अटल अंतरभूत व्योम mt7621_control_निश्चित(काष्ठा mt7621_pcie_port *port)
अणु
	काष्ठा mt7621_pcie *pcie = port->pcie;

	अगर (pcie->resets_inverted)
		reset_control_निश्चित(port->pcie_rst);
	अन्यथा
		reset_control_deनिश्चित(port->pcie_rst);
पूर्ण

अटल अंतरभूत व्योम mt7621_control_deनिश्चित(काष्ठा mt7621_pcie_port *port)
अणु
	काष्ठा mt7621_pcie *pcie = port->pcie;

	अगर (pcie->resets_inverted)
		reset_control_deनिश्चित(port->pcie_rst);
	अन्यथा
		reset_control_निश्चित(port->pcie_rst);
पूर्ण

अटल व्योम setup_cm_memory_region(काष्ठा mt7621_pcie *pcie)
अणु
	काष्ठा resource *mem_resource = pcie->mem;
	काष्ठा device *dev = pcie->dev;
	resource_माप_प्रकार mask;

	अगर (mips_cps_numiocu(0)) अणु
		/*
		 * FIXME: hardware करोesn't accept mask values with 1s after
		 * 0s (e.g. 0xffef), so it would be great to warn अगर that's
		 * about to happen
		 */
		mask = ~(mem_resource->end - mem_resource->start);

		ग_लिखो_gcr_reg1_base(mem_resource->start);
		ग_लिखो_gcr_reg1_mask(mask | CM_GCR_REGn_MASK_CMTGT_IOCU0);
		dev_info(dev, "PCI coherence region base: 0x%08llx, mask/settings: 0x%08llx\n",
			 (अचिन्हित दीर्घ दीर्घ)पढ़ो_gcr_reg1_base(),
			 (अचिन्हित दीर्घ दीर्घ)पढ़ो_gcr_reg1_mask());
	पूर्ण
पूर्ण

अटल पूर्णांक mt7621_map_irq(स्थिर काष्ठा pci_dev *pdev, u8 slot, u8 pin)
अणु
	काष्ठा mt7621_pcie *pcie = pdev->bus->sysdata;
	काष्ठा device *dev = pcie->dev;
	पूर्णांक irq = pcie->irq_map[slot];

	dev_info(dev, "bus=%d slot=%d irq=%d\n", pdev->bus->number, slot, irq);
	वापस irq;
पूर्ण

अटल पूर्णांक mt7621_pci_parse_request_of_pci_ranges(काष्ठा pci_host_bridge *host)
अणु
	काष्ठा mt7621_pcie *pcie = pci_host_bridge_priv(host);
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा of_pci_range_parser parser;
	काष्ठा resource_entry *entry;
	काष्ठा of_pci_range range;
	LIST_HEAD(res);

	अगर (of_pci_range_parser_init(&parser, node)) अणु
		dev_err(dev, "missing \"ranges\" property\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * IO_SPACE_LIMIT क्रम MIPS is 0xffff but this platक्रमm uses IO at
	 * upper address 0x001e160000. of_pci_range_to_resource करोes not work
	 * well क्रम MIPS platक्रमms that करोn't define PCI_IOBASE, so set the IO
	 * resource manually instead.
	 */
	pcie->io.name = node->full_name;
	pcie->io.parent = pcie->io.child = pcie->io.sibling = शून्य;
	क्रम_each_of_pci_range(&parser, &range) अणु
		चयन (range.flags & IORESOURCE_TYPE_BITS) अणु
		हाल IORESOURCE_IO:
			pcie->io_map_base =
				(अचिन्हित दीर्घ)ioremap(range.cpu_addr,
						       range.size);
			pcie->io.flags = range.flags;
			pcie->io.start = range.cpu_addr;
			pcie->io.end = range.cpu_addr + range.size - 1;
			set_io_port_base(pcie->io_map_base);
			अवरोध;
		पूर्ण
	पूर्ण

	entry = resource_list_first_type(&host->winकरोws, IORESOURCE_MEM);
	अगर (!entry) अणु
		dev_err(dev, "Cannot get memory resource");
		वापस -EINVAL;
	पूर्ण

	pcie->mem = entry->res;
	pci_add_resource(&res, &pcie->io);
	pci_add_resource(&res, entry->res);
	list_splice_init(&res, &host->winकरोws);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_pcie_parse_port(काष्ठा mt7621_pcie *pcie,
				  पूर्णांक slot)
अणु
	काष्ठा mt7621_pcie_port *port;
	काष्ठा device *dev = pcie->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	अक्षर name[10];

	port = devm_kzalloc(dev, माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	port->base = devm_platक्रमm_ioremap_resource(pdev, slot + 1);
	अगर (IS_ERR(port->base))
		वापस PTR_ERR(port->base);

	snम_लिखो(name, माप(name), "pcie%d", slot);
	port->pcie_rst = devm_reset_control_get_exclusive(dev, name);
	अगर (PTR_ERR(port->pcie_rst) == -EPROBE_DEFER) अणु
		dev_err(dev, "failed to get pcie%d reset control\n", slot);
		वापस PTR_ERR(port->pcie_rst);
	पूर्ण

	snम_लिखो(name, माप(name), "pcie-phy%d", slot);
	port->phy = devm_phy_get(dev, name);
	अगर (IS_ERR(port->phy) && slot != 1)
		वापस PTR_ERR(port->phy);

	port->gpio_rst = devm_gpiod_get_index_optional(dev, "reset", slot,
						       GPIOD_OUT_LOW);
	अगर (IS_ERR(port->gpio_rst)) अणु
		dev_err(dev, "Failed to get GPIO for PCIe%d\n", slot);
		वापस PTR_ERR(port->gpio_rst);
	पूर्ण

	port->slot = slot;
	port->pcie = pcie;

	port->irq = platक्रमm_get_irq(pdev, slot);
	अगर (port->irq < 0) अणु
		dev_err(dev, "Failed to get IRQ for PCIe%d\n", slot);
		वापस -ENXIO;
	पूर्ण

	INIT_LIST_HEAD(&port->list);
	list_add_tail(&port->list, &pcie->ports);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_pcie_parse_dt(काष्ठा mt7621_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *node = dev->of_node, *child;
	पूर्णांक err;

	pcie->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pcie->base))
		वापस PTR_ERR(pcie->base);

	क्रम_each_available_child_of_node(node, child) अणु
		पूर्णांक slot;

		err = of_pci_get_devfn(child);
		अगर (err < 0) अणु
			of_node_put(child);
			dev_err(dev, "failed to parse devfn: %d\n", err);
			वापस err;
		पूर्ण

		slot = PCI_SLOT(err);

		err = mt7621_pcie_parse_port(pcie, slot);
		अगर (err) अणु
			of_node_put(child);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_pcie_init_port(काष्ठा mt7621_pcie_port *port)
अणु
	काष्ठा mt7621_pcie *pcie = port->pcie;
	काष्ठा device *dev = pcie->dev;
	u32 slot = port->slot;
	पूर्णांक err;

	err = phy_init(port->phy);
	अगर (err) अणु
		dev_err(dev, "failed to initialize port%d phy\n", slot);
		वापस err;
	पूर्ण

	err = phy_घातer_on(port->phy);
	अगर (err) अणु
		dev_err(dev, "failed to power on port%d phy\n", slot);
		phy_निकास(port->phy);
		वापस err;
	पूर्ण

	port->enabled = true;

	वापस 0;
पूर्ण

अटल व्योम mt7621_pcie_reset_निश्चित(काष्ठा mt7621_pcie *pcie)
अणु
	काष्ठा mt7621_pcie_port *port;

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		/* PCIe RC reset निश्चित */
		mt7621_control_निश्चित(port);

		/* PCIe EP reset निश्चित */
		mt7621_rst_gpio_pcie_निश्चित(port);
	पूर्ण

	mdelay(PERST_DELAY_MS);
पूर्ण

अटल व्योम mt7621_pcie_reset_rc_deनिश्चित(काष्ठा mt7621_pcie *pcie)
अणु
	काष्ठा mt7621_pcie_port *port;

	list_क्रम_each_entry(port, &pcie->ports, list)
		mt7621_control_deनिश्चित(port);
पूर्ण

अटल व्योम mt7621_pcie_reset_ep_deनिश्चित(काष्ठा mt7621_pcie *pcie)
अणु
	काष्ठा mt7621_pcie_port *port;

	list_क्रम_each_entry(port, &pcie->ports, list)
		mt7621_rst_gpio_pcie_deनिश्चित(port);

	mdelay(PERST_DELAY_MS);
पूर्ण

अटल व्योम mt7621_pcie_init_ports(काष्ठा mt7621_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा mt7621_pcie_port *port, *पंचांगp;
	पूर्णांक err;

	rt_sysc_m32(PERST_MODE_MASK, PERST_MODE_GPIO, MT7621_GPIO_MODE);

	mt7621_pcie_reset_निश्चित(pcie);
	mt7621_pcie_reset_rc_deनिश्चित(pcie);

	list_क्रम_each_entry_safe(port, पंचांगp, &pcie->ports, list) अणु
		u32 slot = port->slot;

		अगर (slot == 1) अणु
			port->enabled = true;
			जारी;
		पूर्ण

		err = mt7621_pcie_init_port(port);
		अगर (err) अणु
			dev_err(dev, "Initiating port %d failed\n", slot);
			list_del(&port->list);
		पूर्ण
	पूर्ण

	mt7621_pcie_reset_ep_deनिश्चित(pcie);

	पंचांगp = शून्य;
	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		u32 slot = port->slot;

		अगर (!mt7621_pcie_port_is_linkup(port)) अणु
			dev_err(dev, "pcie%d no card, disable it (RST & CLK)\n",
				slot);
			mt7621_control_निश्चित(port);
			mt7621_pcie_port_clk_disable(port);
			port->enabled = false;

			अगर (slot == 0) अणु
				पंचांगp = port;
				जारी;
			पूर्ण

			अगर (slot == 1 && पंचांगp && !पंचांगp->enabled)
				phy_घातer_off(पंचांगp->phy);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mt7621_pcie_enable_port(काष्ठा mt7621_pcie_port *port)
अणु
	काष्ठा mt7621_pcie *pcie = port->pcie;
	u32 slot = port->slot;
	u32 offset = MT7621_PCIE_OFFSET + (slot * MT7621_NEXT_PORT);
	u32 val;

	/* enable pcie पूर्णांकerrupt */
	val = pcie_पढ़ो(pcie, RALINK_PCI_PCIMSK_ADDR);
	val |= PCIE_PORT_INT_EN(slot);
	pcie_ग_लिखो(pcie, val, RALINK_PCI_PCIMSK_ADDR);

	/* map 2G DDR region */
	pcie_ग_लिखो(pcie, PCIE_BAR_MAP_MAX | PCIE_BAR_ENABLE,
		   offset + RALINK_PCI_BAR0SETUP_ADDR);

	/* configure class code and revision ID */
	pcie_ग_लिखो(pcie, PCIE_CLASS_CODE | PCIE_REVISION_ID,
		   offset + RALINK_PCI_CLASS);
पूर्ण

अटल व्योम mt7621_pcie_enable_ports(काष्ठा mt7621_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा mt7621_pcie_port *port;
	u8 num_slots_enabled = 0;
	u32 slot;
	u32 val;

	/* Setup MEMWIN and IOWIN */
	pcie_ग_लिखो(pcie, 0xffffffff, RALINK_PCI_MEMBASE);
	pcie_ग_लिखो(pcie, pcie->io.start, RALINK_PCI_IOBASE);

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		अगर (port->enabled) अणु
			mt7621_pcie_port_clk_enable(port);
			mt7621_pcie_enable_port(port);
			dev_info(dev, "PCIE%d enabled\n", port->slot);
			num_slots_enabled++;
		पूर्ण
	पूर्ण

	क्रम (slot = 0; slot < num_slots_enabled; slot++) अणु
		val = पढ़ो_config(pcie, slot, PCI_COMMAND);
		val |= PCI_COMMAND_MASTER;
		ग_लिखो_config(pcie, slot, PCI_COMMAND, val);
		/* configure RC FTS number to 250 when it leaves L0s */
		val = पढ़ो_config(pcie, slot, PCIE_FTS_NUM);
		val &= ~PCIE_FTS_NUM_MASK;
		val |= PCIE_FTS_NUM_L0(0x50);
		ग_लिखो_config(pcie, slot, PCIE_FTS_NUM, val);
	पूर्ण
पूर्ण

अटल पूर्णांक mt7621_pcie_init_भव_bridges(काष्ठा mt7621_pcie *pcie)
अणु
	u32 pcie_link_status = 0;
	u32 n = 0;
	पूर्णांक i = 0;
	u32 p2p_br_devnum[PCIE_P2P_CNT];
	पूर्णांक irqs[PCIE_P2P_CNT];
	काष्ठा mt7621_pcie_port *port;

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		u32 slot = port->slot;

		irqs[i++] = port->irq;
		अगर (port->enabled)
			pcie_link_status |= BIT(slot);
	पूर्ण

	अगर (pcie_link_status == 0)
		वापस -1;

	/*
	 * Assign device numbers from zero to the enabled ports,
	 * then assigning reमुख्यing device numbers to any disabled
	 * ports.
	 */
	क्रम (i = 0; i < PCIE_P2P_CNT; i++)
		अगर (pcie_link_status & BIT(i))
			p2p_br_devnum[i] = n++;

	क्रम (i = 0; i < PCIE_P2P_CNT; i++)
		अगर ((pcie_link_status & BIT(i)) == 0)
			p2p_br_devnum[i] = n++;

	pcie_rmw(pcie, RALINK_PCI_PCICFG_ADDR,
		 PCIE_P2P_BR_DEVNUM_MASK_FULL,
		 (p2p_br_devnum[0] << PCIE_P2P_BR_DEVNUM0_SHIFT) |
		 (p2p_br_devnum[1] << PCIE_P2P_BR_DEVNUM1_SHIFT) |
		 (p2p_br_devnum[2] << PCIE_P2P_BR_DEVNUM2_SHIFT));

	/* Assign IRQs */
	n = 0;
	क्रम (i = 0; i < PCIE_P2P_CNT; i++)
		अगर (pcie_link_status & BIT(i))
			pcie->irq_map[n++] = irqs[i];

	क्रम (i = n; i < PCIE_P2P_CNT; i++)
		pcie->irq_map[i] = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_pcie_रेजिस्टर_host(काष्ठा pci_host_bridge *host)
अणु
	काष्ठा mt7621_pcie *pcie = pci_host_bridge_priv(host);

	host->ops = &mt7621_pci_ops;
	host->map_irq = mt7621_map_irq;
	host->sysdata = pcie;

	वापस pci_host_probe(host);
पूर्ण

अटल स्थिर काष्ठा soc_device_attribute mt7621_pci_quirks_match[] = अणु
	अणु .soc_id = "mt7621", .revision = "E2" पूर्ण
पूर्ण;

अटल पूर्णांक mt7621_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा soc_device_attribute *attr;
	काष्ठा mt7621_pcie *pcie;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक err;

	अगर (!dev->of_node)
		वापस -ENODEV;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*pcie));
	अगर (!bridge)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);
	pcie->dev = dev;
	platक्रमm_set_drvdata(pdev, pcie);
	INIT_LIST_HEAD(&pcie->ports);

	attr = soc_device_match(mt7621_pci_quirks_match);
	अगर (attr)
		pcie->resets_inverted = true;

	err = mt7621_pcie_parse_dt(pcie);
	अगर (err) अणु
		dev_err(dev, "Parsing DT failed\n");
		वापस err;
	पूर्ण

	err = mt7621_pci_parse_request_of_pci_ranges(bridge);
	अगर (err) अणु
		dev_err(dev, "Error requesting pci resources from ranges");
		वापस err;
	पूर्ण

	/* set resources limits */
	ioport_resource.start = pcie->io.start;
	ioport_resource.end = pcie->io.end;

	mt7621_pcie_init_ports(pcie);

	err = mt7621_pcie_init_भव_bridges(pcie);
	अगर (err) अणु
		dev_err(dev, "Nothing is connected in virtual bridges. Exiting...");
		वापस 0;
	पूर्ण

	mt7621_pcie_enable_ports(pcie);

	setup_cm_memory_region(pcie);

	err = mt7621_pcie_रेजिस्टर_host(bridge);
	अगर (err) अणु
		dev_err(dev, "Error registering host\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt7621_pci_ids[] = अणु
	अणु .compatible = "mediatek,mt7621-pci" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt7621_pci_ids);

अटल काष्ठा platक्रमm_driver mt7621_pci_driver = अणु
	.probe = mt7621_pci_probe,
	.driver = अणु
		.name = "mt7621-pci",
		.of_match_table = of_match_ptr(mt7621_pci_ids),
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(mt7621_pci_driver);
