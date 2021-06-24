<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MediaTek PCIe host controller driver.
 *
 * Copyright (c) 2017 MediaTek Inc.
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 *	   Honghui Zhang <honghui.zhang@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/msi.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश "../pci.h"

/* PCIe shared रेजिस्टरs */
#घोषणा PCIE_SYS_CFG		0x00
#घोषणा PCIE_INT_ENABLE		0x0c
#घोषणा PCIE_CFG_ADDR		0x20
#घोषणा PCIE_CFG_DATA		0x24

/* PCIe per port रेजिस्टरs */
#घोषणा PCIE_BAR0_SETUP		0x10
#घोषणा PCIE_CLASS		0x34
#घोषणा PCIE_LINK_STATUS	0x50

#घोषणा PCIE_PORT_INT_EN(x)	BIT(20 + (x))
#घोषणा PCIE_PORT_PERST(x)	BIT(1 + (x))
#घोषणा PCIE_PORT_LINKUP	BIT(0)
#घोषणा PCIE_BAR_MAP_MAX	GENMASK(31, 16)

#घोषणा PCIE_BAR_ENABLE		BIT(0)
#घोषणा PCIE_REVISION_ID	BIT(0)
#घोषणा PCIE_CLASS_CODE		(0x60400 << 8)
#घोषणा PCIE_CONF_REG(regn)	(((regn) & GENMASK(7, 2)) | \
				((((regn) >> 8) & GENMASK(3, 0)) << 24))
#घोषणा PCIE_CONF_FUN(fun)	(((fun) << 8) & GENMASK(10, 8))
#घोषणा PCIE_CONF_DEV(dev)	(((dev) << 11) & GENMASK(15, 11))
#घोषणा PCIE_CONF_BUS(bus)	(((bus) << 16) & GENMASK(23, 16))
#घोषणा PCIE_CONF_ADDR(regn, fun, dev, bus) \
	(PCIE_CONF_REG(regn) | PCIE_CONF_FUN(fun) | \
	 PCIE_CONF_DEV(dev) | PCIE_CONF_BUS(bus))

/* MediaTek specअगरic configuration रेजिस्टरs */
#घोषणा PCIE_FTS_NUM		0x70c
#घोषणा PCIE_FTS_NUM_MASK	GENMASK(15, 8)
#घोषणा PCIE_FTS_NUM_L0(x)	((x) & 0xff << 8)

#घोषणा PCIE_FC_CREDIT		0x73c
#घोषणा PCIE_FC_CREDIT_MASK	(GENMASK(31, 31) | GENMASK(28, 16))
#घोषणा PCIE_FC_CREDIT_VAL(x)	((x) << 16)

/* PCIe V2 share रेजिस्टरs */
#घोषणा PCIE_SYS_CFG_V2		0x0
#घोषणा PCIE_CSR_LTSSM_EN(x)	BIT(0 + (x) * 8)
#घोषणा PCIE_CSR_ASPM_L1_EN(x)	BIT(1 + (x) * 8)

/* PCIe V2 per-port रेजिस्टरs */
#घोषणा PCIE_MSI_VECTOR		0x0c0

#घोषणा PCIE_CONF_VEND_ID	0x100
#घोषणा PCIE_CONF_DEVICE_ID	0x102
#घोषणा PCIE_CONF_CLASS_ID	0x106

#घोषणा PCIE_INT_MASK		0x420
#घोषणा INTX_MASK		GENMASK(19, 16)
#घोषणा INTX_SHIFT		16
#घोषणा PCIE_INT_STATUS		0x424
#घोषणा MSI_STATUS		BIT(23)
#घोषणा PCIE_IMSI_STATUS	0x42c
#घोषणा PCIE_IMSI_ADDR		0x430
#घोषणा MSI_MASK		BIT(23)
#घोषणा MTK_MSI_IRQS_NUM	32

#घोषणा PCIE_AHB_TRANS_BASE0_L	0x438
#घोषणा PCIE_AHB_TRANS_BASE0_H	0x43c
#घोषणा AHB2PCIE_SIZE(x)	((x) & GENMASK(4, 0))
#घोषणा PCIE_AXI_WINDOW0	0x448
#घोषणा WIN_ENABLE		BIT(7)
/*
 * Define PCIe to AHB winकरोw size as 2^33 to support max 8GB address space
 * translate, support least 4GB DRAM size access from EP DMA(physical DRAM
 * start from 0x40000000).
 */
#घोषणा PCIE2AHB_SIZE	0x21

/* PCIe V2 configuration transaction header */
#घोषणा PCIE_CFG_HEADER0	0x460
#घोषणा PCIE_CFG_HEADER1	0x464
#घोषणा PCIE_CFG_HEADER2	0x468
#घोषणा PCIE_CFG_WDATA		0x470
#घोषणा PCIE_APP_TLP_REQ	0x488
#घोषणा PCIE_CFG_RDATA		0x48c
#घोषणा APP_CFG_REQ		BIT(0)
#घोषणा APP_CPL_STATUS		GENMASK(7, 5)

#घोषणा CFG_WRRD_TYPE_0		4
#घोषणा CFG_WR_FMT		2
#घोषणा CFG_RD_FMT		0

#घोषणा CFG_DW0_LENGTH(length)	((length) & GENMASK(9, 0))
#घोषणा CFG_DW0_TYPE(type)	(((type) << 24) & GENMASK(28, 24))
#घोषणा CFG_DW0_FMT(fmt)	(((fmt) << 29) & GENMASK(31, 29))
#घोषणा CFG_DW2_REGN(regn)	((regn) & GENMASK(11, 2))
#घोषणा CFG_DW2_FUN(fun)	(((fun) << 16) & GENMASK(18, 16))
#घोषणा CFG_DW2_DEV(dev)	(((dev) << 19) & GENMASK(23, 19))
#घोषणा CFG_DW2_BUS(bus)	(((bus) << 24) & GENMASK(31, 24))
#घोषणा CFG_HEADER_DW0(type, fmt) \
	(CFG_DW0_LENGTH(1) | CFG_DW0_TYPE(type) | CFG_DW0_FMT(fmt))
#घोषणा CFG_HEADER_DW1(where, size) \
	(GENMASK(((size) - 1), 0) << ((where) & 0x3))
#घोषणा CFG_HEADER_DW2(regn, fun, dev, bus) \
	(CFG_DW2_REGN(regn) | CFG_DW2_FUN(fun) | \
	CFG_DW2_DEV(dev) | CFG_DW2_BUS(bus))

#घोषणा PCIE_RST_CTRL		0x510
#घोषणा PCIE_PHY_RSTB		BIT(0)
#घोषणा PCIE_PIPE_SRSTB		BIT(1)
#घोषणा PCIE_MAC_SRSTB		BIT(2)
#घोषणा PCIE_CRSTB		BIT(3)
#घोषणा PCIE_PERSTB		BIT(8)
#घोषणा PCIE_LINKDOWN_RST_EN	GENMASK(15, 13)
#घोषणा PCIE_LINK_STATUS_V2	0x804
#घोषणा PCIE_PORT_LINKUP_V2	BIT(10)

काष्ठा mtk_pcie_port;

/**
 * काष्ठा mtk_pcie_soc - dअगरferentiate between host generations
 * @need_fix_class_id: whether this host's class ID needed to be fixed or not
 * @need_fix_device_id: whether this host's device ID needed to be fixed or not
 * @no_msi: Bridge has no MSI support, and relies on an बाह्यal block
 * @device_id: device ID which this host need to be fixed
 * @ops: poपूर्णांकer to configuration access functions
 * @startup: poपूर्णांकer to controller setting functions
 * @setup_irq: poपूर्णांकer to initialize IRQ functions
 */
काष्ठा mtk_pcie_soc अणु
	bool need_fix_class_id;
	bool need_fix_device_id;
	bool no_msi;
	अचिन्हित पूर्णांक device_id;
	काष्ठा pci_ops *ops;
	पूर्णांक (*startup)(काष्ठा mtk_pcie_port *port);
	पूर्णांक (*setup_irq)(काष्ठा mtk_pcie_port *port, काष्ठा device_node *node);
पूर्ण;

/**
 * काष्ठा mtk_pcie_port - PCIe port inक्रमmation
 * @base: IO mapped रेजिस्टर base
 * @list: port list
 * @pcie: poपूर्णांकer to PCIe host info
 * @reset: poपूर्णांकer to port reset control
 * @sys_ck: poपूर्णांकer to transaction/data link layer घड़ी
 * @ahb_ck: poपूर्णांकer to AHB slave पूर्णांकerface operating घड़ी क्रम CSR access
 *          and RC initiated MMIO access
 * @axi_ck: poपूर्णांकer to application layer MMIO channel operating घड़ी
 * @aux_ck: poपूर्णांकer to pe2_mac_bridge and pe2_mac_core operating घड़ी
 *          when pcie_mac_ck/pcie_pipe_ck is turned off
 * @obff_ck: poपूर्णांकer to OBFF functional block operating घड़ी
 * @pipe_ck: poपूर्णांकer to LTSSM and PHY/MAC layer operating घड़ी
 * @phy: poपूर्णांकer to PHY control block
 * @slot: port slot
 * @irq: GIC irq
 * @irq_करोमुख्य: legacy INTx IRQ करोमुख्य
 * @inner_करोमुख्य: inner IRQ करोमुख्य
 * @msi_करोमुख्य: MSI IRQ करोमुख्य
 * @lock: protect the msi_irq_in_use biपंचांगap
 * @msi_irq_in_use: bit map क्रम asचिन्हित MSI IRQ
 */
काष्ठा mtk_pcie_port अणु
	व्योम __iomem *base;
	काष्ठा list_head list;
	काष्ठा mtk_pcie *pcie;
	काष्ठा reset_control *reset;
	काष्ठा clk *sys_ck;
	काष्ठा clk *ahb_ck;
	काष्ठा clk *axi_ck;
	काष्ठा clk *aux_ck;
	काष्ठा clk *obff_ck;
	काष्ठा clk *pipe_ck;
	काष्ठा phy *phy;
	u32 slot;
	पूर्णांक irq;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा irq_करोमुख्य *inner_करोमुख्य;
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	काष्ठा mutex lock;
	DECLARE_BITMAP(msi_irq_in_use, MTK_MSI_IRQS_NUM);
पूर्ण;

/**
 * काष्ठा mtk_pcie - PCIe host inक्रमmation
 * @dev: poपूर्णांकer to PCIe device
 * @base: IO mapped रेजिस्टर base
 * @मुक्त_ck: मुक्त-run reference घड़ी
 * @mem: non-prefetchable memory resource
 * @ports: poपूर्णांकer to PCIe port inक्रमmation
 * @soc: poपूर्णांकer to SoC-dependent operations
 */
काष्ठा mtk_pcie अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *मुक्त_ck;

	काष्ठा list_head ports;
	स्थिर काष्ठा mtk_pcie_soc *soc;
पूर्ण;

अटल व्योम mtk_pcie_subsys_घातerकरोwn(काष्ठा mtk_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;

	clk_disable_unprepare(pcie->मुक्त_ck);

	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
पूर्ण

अटल व्योम mtk_pcie_port_मुक्त(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा mtk_pcie *pcie = port->pcie;
	काष्ठा device *dev = pcie->dev;

	devm_iounmap(dev, port->base);
	list_del(&port->list);
	devm_kमुक्त(dev, port);
पूर्ण

अटल व्योम mtk_pcie_put_resources(काष्ठा mtk_pcie *pcie)
अणु
	काष्ठा mtk_pcie_port *port, *पंचांगp;

	list_क्रम_each_entry_safe(port, पंचांगp, &pcie->ports, list) अणु
		phy_घातer_off(port->phy);
		phy_निकास(port->phy);
		clk_disable_unprepare(port->pipe_ck);
		clk_disable_unprepare(port->obff_ck);
		clk_disable_unprepare(port->axi_ck);
		clk_disable_unprepare(port->aux_ck);
		clk_disable_unprepare(port->ahb_ck);
		clk_disable_unprepare(port->sys_ck);
		mtk_pcie_port_मुक्त(port);
	पूर्ण

	mtk_pcie_subsys_घातerकरोwn(pcie);
पूर्ण

अटल पूर्णांक mtk_pcie_check_cfg_cpld(काष्ठा mtk_pcie_port *port)
अणु
	u32 val;
	पूर्णांक err;

	err = पढ़ोl_poll_समयout_atomic(port->base + PCIE_APP_TLP_REQ, val,
					!(val & APP_CFG_REQ), 10,
					100 * USEC_PER_MSEC);
	अगर (err)
		वापस PCIBIOS_SET_FAILED;

	अगर (पढ़ोl(port->base + PCIE_APP_TLP_REQ) & APP_CPL_STATUS)
		वापस PCIBIOS_SET_FAILED;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक mtk_pcie_hw_rd_cfg(काष्ठा mtk_pcie_port *port, u32 bus, u32 devfn,
			      पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	u32 पंचांगp;

	/* Write PCIe configuration transaction header क्रम Cfgrd */
	ग_लिखोl(CFG_HEADER_DW0(CFG_WRRD_TYPE_0, CFG_RD_FMT),
	       port->base + PCIE_CFG_HEADER0);
	ग_लिखोl(CFG_HEADER_DW1(where, size), port->base + PCIE_CFG_HEADER1);
	ग_लिखोl(CFG_HEADER_DW2(where, PCI_FUNC(devfn), PCI_SLOT(devfn), bus),
	       port->base + PCIE_CFG_HEADER2);

	/* Trigger h/w to transmit Cfgrd TLP */
	पंचांगp = पढ़ोl(port->base + PCIE_APP_TLP_REQ);
	पंचांगp |= APP_CFG_REQ;
	ग_लिखोl(पंचांगp, port->base + PCIE_APP_TLP_REQ);

	/* Check completion status */
	अगर (mtk_pcie_check_cfg_cpld(port))
		वापस PCIBIOS_SET_FAILED;

	/* Read cpld payload of Cfgrd */
	*val = पढ़ोl(port->base + PCIE_CFG_RDATA);

	अगर (size == 1)
		*val = (*val >> (8 * (where & 3))) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (*val >> (8 * (where & 3))) & 0xffff;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक mtk_pcie_hw_wr_cfg(काष्ठा mtk_pcie_port *port, u32 bus, u32 devfn,
			      पूर्णांक where, पूर्णांक size, u32 val)
अणु
	/* Write PCIe configuration transaction header क्रम Cfgwr */
	ग_लिखोl(CFG_HEADER_DW0(CFG_WRRD_TYPE_0, CFG_WR_FMT),
	       port->base + PCIE_CFG_HEADER0);
	ग_लिखोl(CFG_HEADER_DW1(where, size), port->base + PCIE_CFG_HEADER1);
	ग_लिखोl(CFG_HEADER_DW2(where, PCI_FUNC(devfn), PCI_SLOT(devfn), bus),
	       port->base + PCIE_CFG_HEADER2);

	/* Write Cfgwr data */
	val = val << 8 * (where & 3);
	ग_लिखोl(val, port->base + PCIE_CFG_WDATA);

	/* Trigger h/w to transmit Cfgwr TLP */
	val = पढ़ोl(port->base + PCIE_APP_TLP_REQ);
	val |= APP_CFG_REQ;
	ग_लिखोl(val, port->base + PCIE_APP_TLP_REQ);

	/* Check completion status */
	वापस mtk_pcie_check_cfg_cpld(port);
पूर्ण

अटल काष्ठा mtk_pcie_port *mtk_pcie_find_port(काष्ठा pci_bus *bus,
						अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा mtk_pcie *pcie = bus->sysdata;
	काष्ठा mtk_pcie_port *port;
	काष्ठा pci_dev *dev = शून्य;

	/*
	 * Walk the bus hierarchy to get the devfn value
	 * of the port in the root bus.
	 */
	जबतक (bus && bus->number) अणु
		dev = bus->self;
		bus = dev->bus;
		devfn = dev->devfn;
	पूर्ण

	list_क्रम_each_entry(port, &pcie->ports, list)
		अगर (port->slot == PCI_SLOT(devfn))
			वापस port;

	वापस शून्य;
पूर्ण

अटल पूर्णांक mtk_pcie_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा mtk_pcie_port *port;
	u32 bn = bus->number;
	पूर्णांक ret;

	port = mtk_pcie_find_port(bus, devfn);
	अगर (!port) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	ret = mtk_pcie_hw_rd_cfg(port, bn, devfn, where, size, val);
	अगर (ret)
		*val = ~0;

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_pcie_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				 पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा mtk_pcie_port *port;
	u32 bn = bus->number;

	port = mtk_pcie_find_port(bus, devfn);
	अगर (!port)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस mtk_pcie_hw_wr_cfg(port, bn, devfn, where, size, val);
पूर्ण

अटल काष्ठा pci_ops mtk_pcie_ops_v2 = अणु
	.पढ़ो  = mtk_pcie_config_पढ़ो,
	.ग_लिखो = mtk_pcie_config_ग_लिखो,
पूर्ण;

अटल व्योम mtk_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा mtk_pcie_port *port = irq_data_get_irq_chip_data(data);
	phys_addr_t addr;

	/* MT2712/MT7622 only support 32-bit MSI addresses */
	addr = virt_to_phys(port->base + PCIE_MSI_VECTOR);
	msg->address_hi = 0;
	msg->address_lo = lower_32_bits(addr);

	msg->data = data->hwirq;

	dev_dbg(port->pcie->dev, "msi#%d address_hi %#x address_lo %#x\n",
		(पूर्णांक)data->hwirq, msg->address_hi, msg->address_lo);
पूर्ण

अटल पूर्णांक mtk_msi_set_affinity(काष्ठा irq_data *irq_data,
				स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	 वापस -EINVAL;
पूर्ण

अटल व्योम mtk_msi_ack_irq(काष्ठा irq_data *data)
अणु
	काष्ठा mtk_pcie_port *port = irq_data_get_irq_chip_data(data);
	u32 hwirq = data->hwirq;

	ग_लिखोl(1 << hwirq, port->base + PCIE_IMSI_STATUS);
पूर्ण

अटल काष्ठा irq_chip mtk_msi_bottom_irq_chip = अणु
	.name			= "MTK MSI",
	.irq_compose_msi_msg	= mtk_compose_msi_msg,
	.irq_set_affinity	= mtk_msi_set_affinity,
	.irq_ack		= mtk_msi_ack_irq,
पूर्ण;

अटल पूर्णांक mtk_pcie_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				     अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा mtk_pcie_port *port = करोमुख्य->host_data;
	अचिन्हित दीर्घ bit;

	WARN_ON(nr_irqs != 1);
	mutex_lock(&port->lock);

	bit = find_first_zero_bit(port->msi_irq_in_use, MTK_MSI_IRQS_NUM);
	अगर (bit >= MTK_MSI_IRQS_NUM) अणु
		mutex_unlock(&port->lock);
		वापस -ENOSPC;
	पूर्ण

	__set_bit(bit, port->msi_irq_in_use);

	mutex_unlock(&port->lock);

	irq_करोमुख्य_set_info(करोमुख्य, virq, bit, &mtk_msi_bottom_irq_chip,
			    करोमुख्य->host_data, handle_edge_irq,
			    शून्य, शून्य);

	वापस 0;
पूर्ण

अटल व्योम mtk_pcie_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा mtk_pcie_port *port = irq_data_get_irq_chip_data(d);

	mutex_lock(&port->lock);

	अगर (!test_bit(d->hwirq, port->msi_irq_in_use))
		dev_err(port->pcie->dev, "trying to free unused MSI#%lu\n",
			d->hwirq);
	अन्यथा
		__clear_bit(d->hwirq, port->msi_irq_in_use);

	mutex_unlock(&port->lock);

	irq_करोमुख्य_मुक्त_irqs_parent(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops msi_करोमुख्य_ops = अणु
	.alloc	= mtk_pcie_irq_करोमुख्य_alloc,
	.मुक्त	= mtk_pcie_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल काष्ठा irq_chip mtk_msi_irq_chip = अणु
	.name		= "MTK PCIe MSI",
	.irq_ack	= irq_chip_ack_parent,
	.irq_mask	= pci_msi_mask_irq,
	.irq_unmask	= pci_msi_unmask_irq,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info mtk_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_PCI_MSIX),
	.chip	= &mtk_msi_irq_chip,
पूर्ण;

अटल पूर्णांक mtk_pcie_allocate_msi_करोमुख्यs(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा fwnode_handle *fwnode = of_node_to_fwnode(port->pcie->dev->of_node);

	mutex_init(&port->lock);

	port->inner_करोमुख्य = irq_करोमुख्य_create_linear(fwnode, MTK_MSI_IRQS_NUM,
						      &msi_करोमुख्य_ops, port);
	अगर (!port->inner_करोमुख्य) अणु
		dev_err(port->pcie->dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	port->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode, &mtk_msi_करोमुख्य_info,
						     port->inner_करोमुख्य);
	अगर (!port->msi_करोमुख्य) अणु
		dev_err(port->pcie->dev, "failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(port->inner_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_pcie_enable_msi(काष्ठा mtk_pcie_port *port)
अणु
	u32 val;
	phys_addr_t msg_addr;

	msg_addr = virt_to_phys(port->base + PCIE_MSI_VECTOR);
	val = lower_32_bits(msg_addr);
	ग_लिखोl(val, port->base + PCIE_IMSI_ADDR);

	val = पढ़ोl(port->base + PCIE_INT_MASK);
	val &= ~MSI_MASK;
	ग_लिखोl(val, port->base + PCIE_INT_MASK);
पूर्ण

अटल व्योम mtk_pcie_irq_tearकरोwn(काष्ठा mtk_pcie *pcie)
अणु
	काष्ठा mtk_pcie_port *port, *पंचांगp;

	list_क्रम_each_entry_safe(port, पंचांगp, &pcie->ports, list) अणु
		irq_set_chained_handler_and_data(port->irq, शून्य, शून्य);

		अगर (port->irq_करोमुख्य)
			irq_करोमुख्य_हटाओ(port->irq_करोमुख्य);

		अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
			अगर (port->msi_करोमुख्य)
				irq_करोमुख्य_हटाओ(port->msi_करोमुख्य);
			अगर (port->inner_करोमुख्य)
				irq_करोमुख्य_हटाओ(port->inner_करोमुख्य);
		पूर्ण

		irq_dispose_mapping(port->irq);
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
			     irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &dummy_irq_chip, handle_simple_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकx_करोमुख्य_ops = अणु
	.map = mtk_pcie_पूर्णांकx_map,
पूर्ण;

अटल पूर्णांक mtk_pcie_init_irq_करोमुख्य(काष्ठा mtk_pcie_port *port,
				    काष्ठा device_node *node)
अणु
	काष्ठा device *dev = port->pcie->dev;
	काष्ठा device_node *pcie_पूर्णांकc_node;
	पूर्णांक ret;

	/* Setup INTx */
	pcie_पूर्णांकc_node = of_get_next_child(node, शून्य);
	अगर (!pcie_पूर्णांकc_node) अणु
		dev_err(dev, "no PCIe Intc node found\n");
		वापस -ENODEV;
	पूर्ण

	port->irq_करोमुख्य = irq_करोमुख्य_add_linear(pcie_पूर्णांकc_node, PCI_NUM_INTX,
						 &पूर्णांकx_करोमुख्य_ops, port);
	of_node_put(pcie_पूर्णांकc_node);
	अगर (!port->irq_करोमुख्य) अणु
		dev_err(dev, "failed to get INTx IRQ domain\n");
		वापस -ENODEV;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
		ret = mtk_pcie_allocate_msi_करोमुख्यs(port);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_pcie_पूर्णांकr_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा mtk_pcie_port *port = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ status;
	u32 virq;
	u32 bit = INTX_SHIFT;

	chained_irq_enter(irqchip, desc);

	status = पढ़ोl(port->base + PCIE_INT_STATUS);
	अगर (status & INTX_MASK) अणु
		क्रम_each_set_bit_from(bit, &status, PCI_NUM_INTX + INTX_SHIFT) अणु
			/* Clear the INTx */
			ग_लिखोl(1 << bit, port->base + PCIE_INT_STATUS);
			virq = irq_find_mapping(port->irq_करोमुख्य,
						bit - INTX_SHIFT);
			generic_handle_irq(virq);
		पूर्ण
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
		अगर (status & MSI_STATUS)अणु
			अचिन्हित दीर्घ imsi_status;

			जबतक ((imsi_status = पढ़ोl(port->base + PCIE_IMSI_STATUS))) अणु
				क्रम_each_set_bit(bit, &imsi_status, MTK_MSI_IRQS_NUM) अणु
					virq = irq_find_mapping(port->inner_करोमुख्य, bit);
					generic_handle_irq(virq);
				पूर्ण
			पूर्ण
			/* Clear MSI पूर्णांकerrupt status */
			ग_लिखोl(MSI_STATUS, port->base + PCIE_INT_STATUS);
		पूर्ण
	पूर्ण

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल पूर्णांक mtk_pcie_setup_irq(काष्ठा mtk_pcie_port *port,
			      काष्ठा device_node *node)
अणु
	काष्ठा mtk_pcie *pcie = port->pcie;
	काष्ठा device *dev = pcie->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक err;

	err = mtk_pcie_init_irq_करोमुख्य(port, node);
	अगर (err) अणु
		dev_err(dev, "failed to init PCIe IRQ domain\n");
		वापस err;
	पूर्ण

	port->irq = platक्रमm_get_irq(pdev, port->slot);
	अगर (port->irq < 0)
		वापस port->irq;

	irq_set_chained_handler_and_data(port->irq,
					 mtk_pcie_पूर्णांकr_handler, port);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcie_startup_port_v2(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा mtk_pcie *pcie = port->pcie;
	काष्ठा pci_host_bridge *host = pci_host_bridge_from_priv(pcie);
	काष्ठा resource *mem = शून्य;
	काष्ठा resource_entry *entry;
	स्थिर काष्ठा mtk_pcie_soc *soc = port->pcie->soc;
	u32 val;
	पूर्णांक err;

	entry = resource_list_first_type(&host->winकरोws, IORESOURCE_MEM);
	अगर (entry)
		mem = entry->res;
	अगर (!mem)
		वापस -EINVAL;

	/* MT7622 platक्रमms need to enable LTSSM and ASPM from PCIe subsys */
	अगर (pcie->base) अणु
		val = पढ़ोl(pcie->base + PCIE_SYS_CFG_V2);
		val |= PCIE_CSR_LTSSM_EN(port->slot) |
		       PCIE_CSR_ASPM_L1_EN(port->slot);
		ग_लिखोl(val, pcie->base + PCIE_SYS_CFG_V2);
	पूर्ण

	/* Assert all reset संकेतs */
	ग_लिखोl(0, port->base + PCIE_RST_CTRL);

	/*
	 * Enable PCIe link करोwn reset, अगर link status changed from link up to
	 * link करोwn, this will reset MAC control रेजिस्टरs and configuration
	 * space.
	 */
	ग_लिखोl(PCIE_LINKDOWN_RST_EN, port->base + PCIE_RST_CTRL);

	/* De-निश्चित PHY, PE, PIPE, MAC and configuration reset	*/
	val = पढ़ोl(port->base + PCIE_RST_CTRL);
	val |= PCIE_PHY_RSTB | PCIE_PERSTB | PCIE_PIPE_SRSTB |
	       PCIE_MAC_SRSTB | PCIE_CRSTB;
	ग_लिखोl(val, port->base + PCIE_RST_CTRL);

	/* Set up venकरोr ID and class code */
	अगर (soc->need_fix_class_id) अणु
		val = PCI_VENDOR_ID_MEDIATEK;
		ग_लिखोw(val, port->base + PCIE_CONF_VEND_ID);

		val = PCI_CLASS_BRIDGE_PCI;
		ग_लिखोw(val, port->base + PCIE_CONF_CLASS_ID);
	पूर्ण

	अगर (soc->need_fix_device_id)
		ग_लिखोw(soc->device_id, port->base + PCIE_CONF_DEVICE_ID);

	/* 100ms समयout value should be enough क्रम Gen1/2 training */
	err = पढ़ोl_poll_समयout(port->base + PCIE_LINK_STATUS_V2, val,
				 !!(val & PCIE_PORT_LINKUP_V2), 20,
				 100 * USEC_PER_MSEC);
	अगर (err)
		वापस -ETIMEDOUT;

	/* Set INTx mask */
	val = पढ़ोl(port->base + PCIE_INT_MASK);
	val &= ~INTX_MASK;
	ग_लिखोl(val, port->base + PCIE_INT_MASK);

	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		mtk_pcie_enable_msi(port);

	/* Set AHB to PCIe translation winकरोws */
	val = lower_32_bits(mem->start) |
	      AHB2PCIE_SIZE(fls(resource_size(mem)));
	ग_लिखोl(val, port->base + PCIE_AHB_TRANS_BASE0_L);

	val = upper_32_bits(mem->start);
	ग_लिखोl(val, port->base + PCIE_AHB_TRANS_BASE0_H);

	/* Set PCIe to AXI translation memory space.*/
	val = PCIE2AHB_SIZE | WIN_ENABLE;
	ग_लिखोl(val, port->base + PCIE_AXI_WINDOW0);

	वापस 0;
पूर्ण

अटल व्योम __iomem *mtk_pcie_map_bus(काष्ठा pci_bus *bus,
				      अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा mtk_pcie *pcie = bus->sysdata;

	ग_लिखोl(PCIE_CONF_ADDR(where, PCI_FUNC(devfn), PCI_SLOT(devfn),
			      bus->number), pcie->base + PCIE_CFG_ADDR);

	वापस pcie->base + PCIE_CFG_DATA + (where & 3);
पूर्ण

अटल काष्ठा pci_ops mtk_pcie_ops = अणु
	.map_bus = mtk_pcie_map_bus,
	.पढ़ो  = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

अटल पूर्णांक mtk_pcie_startup_port(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा mtk_pcie *pcie = port->pcie;
	u32 func = PCI_FUNC(port->slot);
	u32 slot = PCI_SLOT(port->slot << 3);
	u32 val;
	पूर्णांक err;

	/* निश्चित port PERST_N */
	val = पढ़ोl(pcie->base + PCIE_SYS_CFG);
	val |= PCIE_PORT_PERST(port->slot);
	ग_लिखोl(val, pcie->base + PCIE_SYS_CFG);

	/* de-निश्चित port PERST_N */
	val = पढ़ोl(pcie->base + PCIE_SYS_CFG);
	val &= ~PCIE_PORT_PERST(port->slot);
	ग_लिखोl(val, pcie->base + PCIE_SYS_CFG);

	/* 100ms समयout value should be enough क्रम Gen1/2 training */
	err = पढ़ोl_poll_समयout(port->base + PCIE_LINK_STATUS, val,
				 !!(val & PCIE_PORT_LINKUP), 20,
				 100 * USEC_PER_MSEC);
	अगर (err)
		वापस -ETIMEDOUT;

	/* enable पूर्णांकerrupt */
	val = पढ़ोl(pcie->base + PCIE_INT_ENABLE);
	val |= PCIE_PORT_INT_EN(port->slot);
	ग_लिखोl(val, pcie->base + PCIE_INT_ENABLE);

	/* map to all DDR region. We need to set it beक्रमe cfg operation. */
	ग_लिखोl(PCIE_BAR_MAP_MAX | PCIE_BAR_ENABLE,
	       port->base + PCIE_BAR0_SETUP);

	/* configure class code and revision ID */
	ग_लिखोl(PCIE_CLASS_CODE | PCIE_REVISION_ID, port->base + PCIE_CLASS);

	/* configure FC credit */
	ग_लिखोl(PCIE_CONF_ADDR(PCIE_FC_CREDIT, func, slot, 0),
	       pcie->base + PCIE_CFG_ADDR);
	val = पढ़ोl(pcie->base + PCIE_CFG_DATA);
	val &= ~PCIE_FC_CREDIT_MASK;
	val |= PCIE_FC_CREDIT_VAL(0x806c);
	ग_लिखोl(PCIE_CONF_ADDR(PCIE_FC_CREDIT, func, slot, 0),
	       pcie->base + PCIE_CFG_ADDR);
	ग_लिखोl(val, pcie->base + PCIE_CFG_DATA);

	/* configure RC FTS number to 250 when it leaves L0s */
	ग_लिखोl(PCIE_CONF_ADDR(PCIE_FTS_NUM, func, slot, 0),
	       pcie->base + PCIE_CFG_ADDR);
	val = पढ़ोl(pcie->base + PCIE_CFG_DATA);
	val &= ~PCIE_FTS_NUM_MASK;
	val |= PCIE_FTS_NUM_L0(0x50);
	ग_लिखोl(PCIE_CONF_ADDR(PCIE_FTS_NUM, func, slot, 0),
	       pcie->base + PCIE_CFG_ADDR);
	ग_लिखोl(val, pcie->base + PCIE_CFG_DATA);

	वापस 0;
पूर्ण

अटल व्योम mtk_pcie_enable_port(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा mtk_pcie *pcie = port->pcie;
	काष्ठा device *dev = pcie->dev;
	पूर्णांक err;

	err = clk_prepare_enable(port->sys_ck);
	अगर (err) अणु
		dev_err(dev, "failed to enable sys_ck%d clock\n", port->slot);
		जाओ err_sys_clk;
	पूर्ण

	err = clk_prepare_enable(port->ahb_ck);
	अगर (err) अणु
		dev_err(dev, "failed to enable ahb_ck%d\n", port->slot);
		जाओ err_ahb_clk;
	पूर्ण

	err = clk_prepare_enable(port->aux_ck);
	अगर (err) अणु
		dev_err(dev, "failed to enable aux_ck%d\n", port->slot);
		जाओ err_aux_clk;
	पूर्ण

	err = clk_prepare_enable(port->axi_ck);
	अगर (err) अणु
		dev_err(dev, "failed to enable axi_ck%d\n", port->slot);
		जाओ err_axi_clk;
	पूर्ण

	err = clk_prepare_enable(port->obff_ck);
	अगर (err) अणु
		dev_err(dev, "failed to enable obff_ck%d\n", port->slot);
		जाओ err_obff_clk;
	पूर्ण

	err = clk_prepare_enable(port->pipe_ck);
	अगर (err) अणु
		dev_err(dev, "failed to enable pipe_ck%d\n", port->slot);
		जाओ err_pipe_clk;
	पूर्ण

	reset_control_निश्चित(port->reset);
	reset_control_deनिश्चित(port->reset);

	err = phy_init(port->phy);
	अगर (err) अणु
		dev_err(dev, "failed to initialize port%d phy\n", port->slot);
		जाओ err_phy_init;
	पूर्ण

	err = phy_घातer_on(port->phy);
	अगर (err) अणु
		dev_err(dev, "failed to power on port%d phy\n", port->slot);
		जाओ err_phy_on;
	पूर्ण

	अगर (!pcie->soc->startup(port))
		वापस;

	dev_info(dev, "Port%d link down\n", port->slot);

	phy_घातer_off(port->phy);
err_phy_on:
	phy_निकास(port->phy);
err_phy_init:
	clk_disable_unprepare(port->pipe_ck);
err_pipe_clk:
	clk_disable_unprepare(port->obff_ck);
err_obff_clk:
	clk_disable_unprepare(port->axi_ck);
err_axi_clk:
	clk_disable_unprepare(port->aux_ck);
err_aux_clk:
	clk_disable_unprepare(port->ahb_ck);
err_ahb_clk:
	clk_disable_unprepare(port->sys_ck);
err_sys_clk:
	mtk_pcie_port_मुक्त(port);
पूर्ण

अटल पूर्णांक mtk_pcie_parse_port(काष्ठा mtk_pcie *pcie,
			       काष्ठा device_node *node,
			       पूर्णांक slot)
अणु
	काष्ठा mtk_pcie_port *port;
	काष्ठा device *dev = pcie->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	अक्षर name[10];
	पूर्णांक err;

	port = devm_kzalloc(dev, माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	snम_लिखो(name, माप(name), "port%d", slot);
	port->base = devm_platक्रमm_ioremap_resource_byname(pdev, name);
	अगर (IS_ERR(port->base)) अणु
		dev_err(dev, "failed to map port%d base\n", slot);
		वापस PTR_ERR(port->base);
	पूर्ण

	snम_लिखो(name, माप(name), "sys_ck%d", slot);
	port->sys_ck = devm_clk_get(dev, name);
	अगर (IS_ERR(port->sys_ck)) अणु
		dev_err(dev, "failed to get sys_ck%d clock\n", slot);
		वापस PTR_ERR(port->sys_ck);
	पूर्ण

	/* sys_ck might be भागided पूर्णांकo the following parts in some chips */
	snम_लिखो(name, माप(name), "ahb_ck%d", slot);
	port->ahb_ck = devm_clk_get_optional(dev, name);
	अगर (IS_ERR(port->ahb_ck))
		वापस PTR_ERR(port->ahb_ck);

	snम_लिखो(name, माप(name), "axi_ck%d", slot);
	port->axi_ck = devm_clk_get_optional(dev, name);
	अगर (IS_ERR(port->axi_ck))
		वापस PTR_ERR(port->axi_ck);

	snम_लिखो(name, माप(name), "aux_ck%d", slot);
	port->aux_ck = devm_clk_get_optional(dev, name);
	अगर (IS_ERR(port->aux_ck))
		वापस PTR_ERR(port->aux_ck);

	snम_लिखो(name, माप(name), "obff_ck%d", slot);
	port->obff_ck = devm_clk_get_optional(dev, name);
	अगर (IS_ERR(port->obff_ck))
		वापस PTR_ERR(port->obff_ck);

	snम_लिखो(name, माप(name), "pipe_ck%d", slot);
	port->pipe_ck = devm_clk_get_optional(dev, name);
	अगर (IS_ERR(port->pipe_ck))
		वापस PTR_ERR(port->pipe_ck);

	snम_लिखो(name, माप(name), "pcie-rst%d", slot);
	port->reset = devm_reset_control_get_optional_exclusive(dev, name);
	अगर (PTR_ERR(port->reset) == -EPROBE_DEFER)
		वापस PTR_ERR(port->reset);

	/* some platक्रमms may use शेष PHY setting */
	snम_लिखो(name, माप(name), "pcie-phy%d", slot);
	port->phy = devm_phy_optional_get(dev, name);
	अगर (IS_ERR(port->phy))
		वापस PTR_ERR(port->phy);

	port->slot = slot;
	port->pcie = pcie;

	अगर (pcie->soc->setup_irq) अणु
		err = pcie->soc->setup_irq(port, node);
		अगर (err)
			वापस err;
	पूर्ण

	INIT_LIST_HEAD(&port->list);
	list_add_tail(&port->list, &pcie->ports);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcie_subsys_घातerup(काष्ठा mtk_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *regs;
	पूर्णांक err;

	/* get shared रेजिस्टरs, which are optional */
	regs = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "subsys");
	अगर (regs) अणु
		pcie->base = devm_ioremap_resource(dev, regs);
		अगर (IS_ERR(pcie->base)) अणु
			dev_err(dev, "failed to map shared register\n");
			वापस PTR_ERR(pcie->base);
		पूर्ण
	पूर्ण

	pcie->मुक्त_ck = devm_clk_get(dev, "free_ck");
	अगर (IS_ERR(pcie->मुक्त_ck)) अणु
		अगर (PTR_ERR(pcie->मुक्त_ck) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		pcie->मुक्त_ck = शून्य;
	पूर्ण

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	/* enable top level घड़ी */
	err = clk_prepare_enable(pcie->मुक्त_ck);
	अगर (err) अणु
		dev_err(dev, "failed to enable free_ck\n");
		जाओ err_मुक्त_ck;
	पूर्ण

	वापस 0;

err_मुक्त_ck:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	वापस err;
पूर्ण

अटल पूर्णांक mtk_pcie_setup(काष्ठा mtk_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *node = dev->of_node, *child;
	काष्ठा mtk_pcie_port *port, *पंचांगp;
	पूर्णांक err;

	क्रम_each_available_child_of_node(node, child) अणु
		पूर्णांक slot;

		err = of_pci_get_devfn(child);
		अगर (err < 0) अणु
			dev_err(dev, "failed to parse devfn: %d\n", err);
			जाओ error_put_node;
		पूर्ण

		slot = PCI_SLOT(err);

		err = mtk_pcie_parse_port(pcie, child, slot);
		अगर (err)
			जाओ error_put_node;
	पूर्ण

	err = mtk_pcie_subsys_घातerup(pcie);
	अगर (err)
		वापस err;

	/* enable each port, and then check link status */
	list_क्रम_each_entry_safe(port, पंचांगp, &pcie->ports, list)
		mtk_pcie_enable_port(port);

	/* घातer करोwn PCIe subsys अगर slots are all empty (link करोwn) */
	अगर (list_empty(&pcie->ports))
		mtk_pcie_subsys_घातerकरोwn(pcie);

	वापस 0;
error_put_node:
	of_node_put(child);
	वापस err;
पूर्ण

अटल पूर्णांक mtk_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_pcie *pcie;
	काष्ठा pci_host_bridge *host;
	पूर्णांक err;

	host = devm_pci_alloc_host_bridge(dev, माप(*pcie));
	अगर (!host)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(host);

	pcie->dev = dev;
	pcie->soc = of_device_get_match_data(dev);
	platक्रमm_set_drvdata(pdev, pcie);
	INIT_LIST_HEAD(&pcie->ports);

	err = mtk_pcie_setup(pcie);
	अगर (err)
		वापस err;

	host->ops = pcie->soc->ops;
	host->sysdata = pcie;
	host->msi_करोमुख्य = pcie->soc->no_msi;

	err = pci_host_probe(host);
	अगर (err)
		जाओ put_resources;

	वापस 0;

put_resources:
	अगर (!list_empty(&pcie->ports))
		mtk_pcie_put_resources(pcie);

	वापस err;
पूर्ण


अटल व्योम mtk_pcie_मुक्त_resources(काष्ठा mtk_pcie *pcie)
अणु
	काष्ठा pci_host_bridge *host = pci_host_bridge_from_priv(pcie);
	काष्ठा list_head *winकरोws = &host->winकरोws;

	pci_मुक्त_resource_list(winकरोws);
पूर्ण

अटल पूर्णांक mtk_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_pcie *pcie = platक्रमm_get_drvdata(pdev);
	काष्ठा pci_host_bridge *host = pci_host_bridge_from_priv(pcie);

	pci_stop_root_bus(host->bus);
	pci_हटाओ_root_bus(host->bus);
	mtk_pcie_मुक्त_resources(pcie);

	mtk_pcie_irq_tearकरोwn(pcie);

	mtk_pcie_put_resources(pcie);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_pcie_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा mtk_pcie *pcie = dev_get_drvdata(dev);
	काष्ठा mtk_pcie_port *port;

	अगर (list_empty(&pcie->ports))
		वापस 0;

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		clk_disable_unprepare(port->pipe_ck);
		clk_disable_unprepare(port->obff_ck);
		clk_disable_unprepare(port->axi_ck);
		clk_disable_unprepare(port->aux_ck);
		clk_disable_unprepare(port->ahb_ck);
		clk_disable_unprepare(port->sys_ck);
		phy_घातer_off(port->phy);
		phy_निकास(port->phy);
	पूर्ण

	clk_disable_unprepare(pcie->मुक्त_ck);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_pcie_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा mtk_pcie *pcie = dev_get_drvdata(dev);
	काष्ठा mtk_pcie_port *port, *पंचांगp;

	अगर (list_empty(&pcie->ports))
		वापस 0;

	clk_prepare_enable(pcie->मुक्त_ck);

	list_क्रम_each_entry_safe(port, पंचांगp, &pcie->ports, list)
		mtk_pcie_enable_port(port);

	/* In हाल of EP was हटाओd जबतक प्रणाली suspend. */
	अगर (list_empty(&pcie->ports))
		clk_disable_unprepare(pcie->मुक्त_ck);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtk_pcie_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(mtk_pcie_suspend_noirq,
				      mtk_pcie_resume_noirq)
पूर्ण;

अटल स्थिर काष्ठा mtk_pcie_soc mtk_pcie_soc_v1 = अणु
	.no_msi = true,
	.ops = &mtk_pcie_ops,
	.startup = mtk_pcie_startup_port,
पूर्ण;

अटल स्थिर काष्ठा mtk_pcie_soc mtk_pcie_soc_mt2712 = अणु
	.ops = &mtk_pcie_ops_v2,
	.startup = mtk_pcie_startup_port_v2,
	.setup_irq = mtk_pcie_setup_irq,
पूर्ण;

अटल स्थिर काष्ठा mtk_pcie_soc mtk_pcie_soc_mt7622 = अणु
	.need_fix_class_id = true,
	.ops = &mtk_pcie_ops_v2,
	.startup = mtk_pcie_startup_port_v2,
	.setup_irq = mtk_pcie_setup_irq,
पूर्ण;

अटल स्थिर काष्ठा mtk_pcie_soc mtk_pcie_soc_mt7629 = अणु
	.need_fix_class_id = true,
	.need_fix_device_id = true,
	.device_id = PCI_DEVICE_ID_MEDIATEK_7629,
	.ops = &mtk_pcie_ops_v2,
	.startup = mtk_pcie_startup_port_v2,
	.setup_irq = mtk_pcie_setup_irq,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_pcie_ids[] = अणु
	अणु .compatible = "mediatek,mt2701-pcie", .data = &mtk_pcie_soc_v1 पूर्ण,
	अणु .compatible = "mediatek,mt7623-pcie", .data = &mtk_pcie_soc_v1 पूर्ण,
	अणु .compatible = "mediatek,mt2712-pcie", .data = &mtk_pcie_soc_mt2712 पूर्ण,
	अणु .compatible = "mediatek,mt7622-pcie", .data = &mtk_pcie_soc_mt7622 पूर्ण,
	अणु .compatible = "mediatek,mt7629-pcie", .data = &mtk_pcie_soc_mt7629 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_pcie_ids);

अटल काष्ठा platक्रमm_driver mtk_pcie_driver = अणु
	.probe = mtk_pcie_probe,
	.हटाओ = mtk_pcie_हटाओ,
	.driver = अणु
		.name = "mtk-pcie",
		.of_match_table = mtk_pcie_ids,
		.suppress_bind_attrs = true,
		.pm = &mtk_pcie_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mtk_pcie_driver);
MODULE_LICENSE("GPL v2");
