<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MediaTek PCIe host controller driver.
 *
 * Copyright (c) 2020 MediaTek Inc.
 * Author: Jianjun Wang <jianjun.wang@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश "../pci.h"

#घोषणा PCIE_SETTING_REG		0x80
#घोषणा PCIE_PCI_IDS_1			0x9c
#घोषणा PCI_CLASS(class)		(class << 8)
#घोषणा PCIE_RC_MODE			BIT(0)

#घोषणा PCIE_CFGNUM_REG			0x140
#घोषणा PCIE_CFG_DEVFN(devfn)		((devfn) & GENMASK(7, 0))
#घोषणा PCIE_CFG_BUS(bus)		(((bus) << 8) & GENMASK(15, 8))
#घोषणा PCIE_CFG_BYTE_EN(bytes)		(((bytes) << 16) & GENMASK(19, 16))
#घोषणा PCIE_CFG_FORCE_BYTE_EN		BIT(20)
#घोषणा PCIE_CFG_OFFSET_ADDR		0x1000
#घोषणा PCIE_CFG_HEADER(bus, devfn) \
	(PCIE_CFG_BUS(bus) | PCIE_CFG_DEVFN(devfn))

#घोषणा PCIE_RST_CTRL_REG		0x148
#घोषणा PCIE_MAC_RSTB			BIT(0)
#घोषणा PCIE_PHY_RSTB			BIT(1)
#घोषणा PCIE_BRG_RSTB			BIT(2)
#घोषणा PCIE_PE_RSTB			BIT(3)

#घोषणा PCIE_LTSSM_STATUS_REG		0x150
#घोषणा PCIE_LTSSM_STATE_MASK		GENMASK(28, 24)
#घोषणा PCIE_LTSSM_STATE(val)		((val & PCIE_LTSSM_STATE_MASK) >> 24)
#घोषणा PCIE_LTSSM_STATE_L2_IDLE	0x14

#घोषणा PCIE_LINK_STATUS_REG		0x154
#घोषणा PCIE_PORT_LINKUP		BIT(8)

#घोषणा PCIE_MSI_SET_NUM		8
#घोषणा PCIE_MSI_IRQS_PER_SET		32
#घोषणा PCIE_MSI_IRQS_NUM \
	(PCIE_MSI_IRQS_PER_SET * PCIE_MSI_SET_NUM)

#घोषणा PCIE_INT_ENABLE_REG		0x180
#घोषणा PCIE_MSI_ENABLE			GENMASK(PCIE_MSI_SET_NUM + 8 - 1, 8)
#घोषणा PCIE_MSI_SHIFT			8
#घोषणा PCIE_INTX_SHIFT			24
#घोषणा PCIE_INTX_ENABLE \
	GENMASK(PCIE_INTX_SHIFT + PCI_NUM_INTX - 1, PCIE_INTX_SHIFT)

#घोषणा PCIE_INT_STATUS_REG		0x184
#घोषणा PCIE_MSI_SET_ENABLE_REG		0x190
#घोषणा PCIE_MSI_SET_ENABLE		GENMASK(PCIE_MSI_SET_NUM - 1, 0)

#घोषणा PCIE_MSI_SET_BASE_REG		0xc00
#घोषणा PCIE_MSI_SET_OFFSET		0x10
#घोषणा PCIE_MSI_SET_STATUS_OFFSET	0x04
#घोषणा PCIE_MSI_SET_ENABLE_OFFSET	0x08

#घोषणा PCIE_MSI_SET_ADDR_HI_BASE	0xc80
#घोषणा PCIE_MSI_SET_ADDR_HI_OFFSET	0x04

#घोषणा PCIE_ICMD_PM_REG		0x198
#घोषणा PCIE_TURN_OFF_LINK		BIT(4)

#घोषणा PCIE_TRANS_TABLE_BASE_REG	0x800
#घोषणा PCIE_ATR_SRC_ADDR_MSB_OFFSET	0x4
#घोषणा PCIE_ATR_TRSL_ADDR_LSB_OFFSET	0x8
#घोषणा PCIE_ATR_TRSL_ADDR_MSB_OFFSET	0xc
#घोषणा PCIE_ATR_TRSL_PARAM_OFFSET	0x10
#घोषणा PCIE_ATR_TLB_SET_OFFSET		0x20

#घोषणा PCIE_MAX_TRANS_TABLES		8
#घोषणा PCIE_ATR_EN			BIT(0)
#घोषणा PCIE_ATR_SIZE(size) \
	(((((size) - 1) << 1) & GENMASK(6, 1)) | PCIE_ATR_EN)
#घोषणा PCIE_ATR_ID(id)			((id) & GENMASK(3, 0))
#घोषणा PCIE_ATR_TYPE_MEM		PCIE_ATR_ID(0)
#घोषणा PCIE_ATR_TYPE_IO		PCIE_ATR_ID(1)
#घोषणा PCIE_ATR_TLP_TYPE(type)		(((type) << 16) & GENMASK(18, 16))
#घोषणा PCIE_ATR_TLP_TYPE_MEM		PCIE_ATR_TLP_TYPE(0)
#घोषणा PCIE_ATR_TLP_TYPE_IO		PCIE_ATR_TLP_TYPE(2)

/**
 * काष्ठा mtk_msi_set - MSI inक्रमmation क्रम each set
 * @base: IO mapped रेजिस्टर base
 * @msg_addr: MSI message address
 * @saved_irq_state: IRQ enable state saved at suspend समय
 */
काष्ठा mtk_msi_set अणु
	व्योम __iomem *base;
	phys_addr_t msg_addr;
	u32 saved_irq_state;
पूर्ण;

/**
 * काष्ठा mtk_pcie_port - PCIe port inक्रमmation
 * @dev: poपूर्णांकer to PCIe device
 * @base: IO mapped रेजिस्टर base
 * @reg_base: physical रेजिस्टर base
 * @mac_reset: MAC reset control
 * @phy_reset: PHY reset control
 * @phy: PHY controller block
 * @clks: PCIe घड़ीs
 * @num_clks: PCIe घड़ीs count क्रम this port
 * @irq: PCIe controller पूर्णांकerrupt number
 * @saved_irq_state: IRQ enable state saved at suspend समय
 * @irq_lock: lock protecting IRQ रेजिस्टर access
 * @पूर्णांकx_करोमुख्य: legacy INTx IRQ करोमुख्य
 * @msi_करोमुख्य: MSI IRQ करोमुख्य
 * @msi_bottom_करोमुख्य: MSI IRQ bottom करोमुख्य
 * @msi_sets: MSI sets inक्रमmation
 * @lock: lock protecting IRQ bit map
 * @msi_irq_in_use: bit map क्रम asचिन्हित MSI IRQ
 */
काष्ठा mtk_pcie_port अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	phys_addr_t reg_base;
	काष्ठा reset_control *mac_reset;
	काष्ठा reset_control *phy_reset;
	काष्ठा phy *phy;
	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;

	पूर्णांक irq;
	u32 saved_irq_state;
	raw_spinlock_t irq_lock;
	काष्ठा irq_करोमुख्य *पूर्णांकx_करोमुख्य;
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	काष्ठा irq_करोमुख्य *msi_bottom_करोमुख्य;
	काष्ठा mtk_msi_set msi_sets[PCIE_MSI_SET_NUM];
	काष्ठा mutex lock;
	DECLARE_BITMAP(msi_irq_in_use, PCIE_MSI_IRQS_NUM);
पूर्ण;

/**
 * mtk_pcie_config_tlp_header() - Configure a configuration TLP header
 * @bus: PCI bus to query
 * @devfn: device/function number
 * @where: offset in config space
 * @size: data size in TLP header
 *
 * Set byte enable field and device inक्रमmation in configuration TLP header.
 */
अटल व्योम mtk_pcie_config_tlp_header(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
					पूर्णांक where, पूर्णांक size)
अणु
	काष्ठा mtk_pcie_port *port = bus->sysdata;
	पूर्णांक bytes;
	u32 val;

	bytes = (GENMASK(size - 1, 0) & 0xf) << (where & 0x3);

	val = PCIE_CFG_FORCE_BYTE_EN | PCIE_CFG_BYTE_EN(bytes) |
	      PCIE_CFG_HEADER(bus->number, devfn);

	ग_लिखोl_relaxed(val, port->base + PCIE_CFGNUM_REG);
पूर्ण

अटल व्योम __iomem *mtk_pcie_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				      पूर्णांक where)
अणु
	काष्ठा mtk_pcie_port *port = bus->sysdata;

	वापस port->base + PCIE_CFG_OFFSET_ADDR + where;
पूर्ण

अटल पूर्णांक mtk_pcie_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	mtk_pcie_config_tlp_header(bus, devfn, where, size);

	वापस pci_generic_config_पढ़ो32(bus, devfn, where, size, val);
पूर्ण

अटल पूर्णांक mtk_pcie_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				 पूर्णांक where, पूर्णांक size, u32 val)
अणु
	mtk_pcie_config_tlp_header(bus, devfn, where, size);

	अगर (size <= 2)
		val <<= (where & 0x3) * 8;

	वापस pci_generic_config_ग_लिखो32(bus, devfn, where, 4, val);
पूर्ण

अटल काष्ठा pci_ops mtk_pcie_ops = अणु
	.map_bus = mtk_pcie_map_bus,
	.पढ़ो  = mtk_pcie_config_पढ़ो,
	.ग_लिखो = mtk_pcie_config_ग_लिखो,
पूर्ण;

अटल पूर्णांक mtk_pcie_set_trans_table(काष्ठा mtk_pcie_port *port,
				    resource_माप_प्रकार cpu_addr,
				    resource_माप_प्रकार pci_addr,
				    resource_माप_प्रकार size,
				    अचिन्हित दीर्घ type, पूर्णांक num)
अणु
	व्योम __iomem *table;
	u32 val;

	अगर (num >= PCIE_MAX_TRANS_TABLES) अणु
		dev_err(port->dev, "not enough translate table for addr: %#llx, limited to [%d]\n",
			(अचिन्हित दीर्घ दीर्घ)cpu_addr, PCIE_MAX_TRANS_TABLES);
		वापस -ENODEV;
	पूर्ण

	table = port->base + PCIE_TRANS_TABLE_BASE_REG +
		num * PCIE_ATR_TLB_SET_OFFSET;

	ग_लिखोl_relaxed(lower_32_bits(cpu_addr) | PCIE_ATR_SIZE(fls(size) - 1),
		       table);
	ग_लिखोl_relaxed(upper_32_bits(cpu_addr),
		       table + PCIE_ATR_SRC_ADDR_MSB_OFFSET);
	ग_लिखोl_relaxed(lower_32_bits(pci_addr),
		       table + PCIE_ATR_TRSL_ADDR_LSB_OFFSET);
	ग_लिखोl_relaxed(upper_32_bits(pci_addr),
		       table + PCIE_ATR_TRSL_ADDR_MSB_OFFSET);

	अगर (type == IORESOURCE_IO)
		val = PCIE_ATR_TYPE_IO | PCIE_ATR_TLP_TYPE_IO;
	अन्यथा
		val = PCIE_ATR_TYPE_MEM | PCIE_ATR_TLP_TYPE_MEM;

	ग_लिखोl_relaxed(val, table + PCIE_ATR_TRSL_PARAM_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम mtk_pcie_enable_msi(काष्ठा mtk_pcie_port *port)
अणु
	पूर्णांक i;
	u32 val;

	क्रम (i = 0; i < PCIE_MSI_SET_NUM; i++) अणु
		काष्ठा mtk_msi_set *msi_set = &port->msi_sets[i];

		msi_set->base = port->base + PCIE_MSI_SET_BASE_REG +
				i * PCIE_MSI_SET_OFFSET;
		msi_set->msg_addr = port->reg_base + PCIE_MSI_SET_BASE_REG +
				    i * PCIE_MSI_SET_OFFSET;

		/* Configure the MSI capture address */
		ग_लिखोl_relaxed(lower_32_bits(msi_set->msg_addr), msi_set->base);
		ग_लिखोl_relaxed(upper_32_bits(msi_set->msg_addr),
			       port->base + PCIE_MSI_SET_ADDR_HI_BASE +
			       i * PCIE_MSI_SET_ADDR_HI_OFFSET);
	पूर्ण

	val = पढ़ोl_relaxed(port->base + PCIE_MSI_SET_ENABLE_REG);
	val |= PCIE_MSI_SET_ENABLE;
	ग_लिखोl_relaxed(val, port->base + PCIE_MSI_SET_ENABLE_REG);

	val = पढ़ोl_relaxed(port->base + PCIE_INT_ENABLE_REG);
	val |= PCIE_MSI_ENABLE;
	ग_लिखोl_relaxed(val, port->base + PCIE_INT_ENABLE_REG);
पूर्ण

अटल पूर्णांक mtk_pcie_startup_port(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा resource_entry *entry;
	काष्ठा pci_host_bridge *host = pci_host_bridge_from_priv(port);
	अचिन्हित पूर्णांक table_index = 0;
	पूर्णांक err;
	u32 val;

	/* Set as RC mode */
	val = पढ़ोl_relaxed(port->base + PCIE_SETTING_REG);
	val |= PCIE_RC_MODE;
	ग_लिखोl_relaxed(val, port->base + PCIE_SETTING_REG);

	/* Set class code */
	val = पढ़ोl_relaxed(port->base + PCIE_PCI_IDS_1);
	val &= ~GENMASK(31, 8);
	val |= PCI_CLASS(PCI_CLASS_BRIDGE_PCI << 8);
	ग_लिखोl_relaxed(val, port->base + PCIE_PCI_IDS_1);

	/* Mask all INTx पूर्णांकerrupts */
	val = पढ़ोl_relaxed(port->base + PCIE_INT_ENABLE_REG);
	val &= ~PCIE_INTX_ENABLE;
	ग_लिखोl_relaxed(val, port->base + PCIE_INT_ENABLE_REG);

	/* Assert all reset संकेतs */
	val = पढ़ोl_relaxed(port->base + PCIE_RST_CTRL_REG);
	val |= PCIE_MAC_RSTB | PCIE_PHY_RSTB | PCIE_BRG_RSTB | PCIE_PE_RSTB;
	ग_लिखोl_relaxed(val, port->base + PCIE_RST_CTRL_REG);

	/*
	 * Described in PCIe CEM specअगरication setctions 2.2 (PERST# Signal)
	 * and 2.2.1 (Initial Power-Up (G3 to S0)).
	 * The deनिश्चितion of PERST# should be delayed 100ms (TPVPERL)
	 * क्रम the घातer and घड़ी to become stable.
	 */
	msleep(100);

	/* De-निश्चित reset संकेतs */
	val &= ~(PCIE_MAC_RSTB | PCIE_PHY_RSTB | PCIE_BRG_RSTB | PCIE_PE_RSTB);
	ग_लिखोl_relaxed(val, port->base + PCIE_RST_CTRL_REG);

	/* Check अगर the link is up or not */
	err = पढ़ोl_poll_समयout(port->base + PCIE_LINK_STATUS_REG, val,
				 !!(val & PCIE_PORT_LINKUP), 20,
				 PCI_PM_D3COLD_WAIT * USEC_PER_MSEC);
	अगर (err) अणु
		val = पढ़ोl_relaxed(port->base + PCIE_LTSSM_STATUS_REG);
		dev_err(port->dev, "PCIe link down, ltssm reg val: %#x\n", val);
		वापस err;
	पूर्ण

	mtk_pcie_enable_msi(port);

	/* Set PCIe translation winकरोws */
	resource_list_क्रम_each_entry(entry, &host->winकरोws) अणु
		काष्ठा resource *res = entry->res;
		अचिन्हित दीर्घ type = resource_type(res);
		resource_माप_प्रकार cpu_addr;
		resource_माप_प्रकार pci_addr;
		resource_माप_प्रकार size;
		स्थिर अक्षर *range_type;

		अगर (type == IORESOURCE_IO) अणु
			cpu_addr = pci_pio_to_address(res->start);
			range_type = "IO";
		पूर्ण अन्यथा अगर (type == IORESOURCE_MEM) अणु
			cpu_addr = res->start;
			range_type = "MEM";
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण

		pci_addr = res->start - entry->offset;
		size = resource_size(res);
		err = mtk_pcie_set_trans_table(port, cpu_addr, pci_addr, size,
					       type, table_index);
		अगर (err)
			वापस err;

		dev_dbg(port->dev, "set %s trans window[%d]: cpu_addr = %#llx, pci_addr = %#llx, size = %#llx\n",
			range_type, table_index, (अचिन्हित दीर्घ दीर्घ)cpu_addr,
			(अचिन्हित दीर्घ दीर्घ)pci_addr, (अचिन्हित दीर्घ दीर्घ)size);

		table_index++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcie_set_affinity(काष्ठा irq_data *data,
				 स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम mtk_pcie_msi_irq_mask(काष्ठा irq_data *data)
अणु
	pci_msi_mask_irq(data);
	irq_chip_mask_parent(data);
पूर्ण

अटल व्योम mtk_pcie_msi_irq_unmask(काष्ठा irq_data *data)
अणु
	pci_msi_unmask_irq(data);
	irq_chip_unmask_parent(data);
पूर्ण

अटल काष्ठा irq_chip mtk_msi_irq_chip = अणु
	.irq_ack = irq_chip_ack_parent,
	.irq_mask = mtk_pcie_msi_irq_mask,
	.irq_unmask = mtk_pcie_msi_irq_unmask,
	.name = "MSI",
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info mtk_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_PCI_MSIX | MSI_FLAG_MULTI_PCI_MSI),
	.chip	= &mtk_msi_irq_chip,
पूर्ण;

अटल व्योम mtk_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा mtk_msi_set *msi_set = irq_data_get_irq_chip_data(data);
	काष्ठा mtk_pcie_port *port = data->करोमुख्य->host_data;
	अचिन्हित दीर्घ hwirq;

	hwirq =	data->hwirq % PCIE_MSI_IRQS_PER_SET;

	msg->address_hi = upper_32_bits(msi_set->msg_addr);
	msg->address_lo = lower_32_bits(msi_set->msg_addr);
	msg->data = hwirq;
	dev_dbg(port->dev, "msi#%#lx address_hi %#x address_lo %#x data %d\n",
		hwirq, msg->address_hi, msg->address_lo, msg->data);
पूर्ण

अटल व्योम mtk_msi_bottom_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा mtk_msi_set *msi_set = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ hwirq;

	hwirq =	data->hwirq % PCIE_MSI_IRQS_PER_SET;

	ग_लिखोl_relaxed(BIT(hwirq), msi_set->base + PCIE_MSI_SET_STATUS_OFFSET);
पूर्ण

अटल व्योम mtk_msi_bottom_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा mtk_msi_set *msi_set = irq_data_get_irq_chip_data(data);
	काष्ठा mtk_pcie_port *port = data->करोमुख्य->host_data;
	अचिन्हित दीर्घ hwirq, flags;
	u32 val;

	hwirq =	data->hwirq % PCIE_MSI_IRQS_PER_SET;

	raw_spin_lock_irqsave(&port->irq_lock, flags);
	val = पढ़ोl_relaxed(msi_set->base + PCIE_MSI_SET_ENABLE_OFFSET);
	val &= ~BIT(hwirq);
	ग_लिखोl_relaxed(val, msi_set->base + PCIE_MSI_SET_ENABLE_OFFSET);
	raw_spin_unlock_irqrestore(&port->irq_lock, flags);
पूर्ण

अटल व्योम mtk_msi_bottom_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा mtk_msi_set *msi_set = irq_data_get_irq_chip_data(data);
	काष्ठा mtk_pcie_port *port = data->करोमुख्य->host_data;
	अचिन्हित दीर्घ hwirq, flags;
	u32 val;

	hwirq =	data->hwirq % PCIE_MSI_IRQS_PER_SET;

	raw_spin_lock_irqsave(&port->irq_lock, flags);
	val = पढ़ोl_relaxed(msi_set->base + PCIE_MSI_SET_ENABLE_OFFSET);
	val |= BIT(hwirq);
	ग_लिखोl_relaxed(val, msi_set->base + PCIE_MSI_SET_ENABLE_OFFSET);
	raw_spin_unlock_irqrestore(&port->irq_lock, flags);
पूर्ण

अटल काष्ठा irq_chip mtk_msi_bottom_irq_chip = अणु
	.irq_ack		= mtk_msi_bottom_irq_ack,
	.irq_mask		= mtk_msi_bottom_irq_mask,
	.irq_unmask		= mtk_msi_bottom_irq_unmask,
	.irq_compose_msi_msg	= mtk_compose_msi_msg,
	.irq_set_affinity	= mtk_pcie_set_affinity,
	.name			= "MSI",
पूर्ण;

अटल पूर्णांक mtk_msi_bottom_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				       अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
				       व्योम *arg)
अणु
	काष्ठा mtk_pcie_port *port = करोमुख्य->host_data;
	काष्ठा mtk_msi_set *msi_set;
	पूर्णांक i, hwirq, set_idx;

	mutex_lock(&port->lock);

	hwirq = biपंचांगap_find_मुक्त_region(port->msi_irq_in_use, PCIE_MSI_IRQS_NUM,
					order_base_2(nr_irqs));

	mutex_unlock(&port->lock);

	अगर (hwirq < 0)
		वापस -ENOSPC;

	set_idx = hwirq / PCIE_MSI_IRQS_PER_SET;
	msi_set = &port->msi_sets[set_idx];

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, hwirq + i,
				    &mtk_msi_bottom_irq_chip, msi_set,
				    handle_edge_irq, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल व्योम mtk_msi_bottom_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				       अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा mtk_pcie_port *port = करोमुख्य->host_data;
	काष्ठा irq_data *data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	mutex_lock(&port->lock);

	biपंचांगap_release_region(port->msi_irq_in_use, data->hwirq,
			      order_base_2(nr_irqs));

	mutex_unlock(&port->lock);

	irq_करोमुख्य_मुक्त_irqs_common(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mtk_msi_bottom_करोमुख्य_ops = अणु
	.alloc = mtk_msi_bottom_करोमुख्य_alloc,
	.मुक्त = mtk_msi_bottom_करोमुख्य_मुक्त,
पूर्ण;

अटल व्योम mtk_पूर्णांकx_mask(काष्ठा irq_data *data)
अणु
	काष्ठा mtk_pcie_port *port = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&port->irq_lock, flags);
	val = पढ़ोl_relaxed(port->base + PCIE_INT_ENABLE_REG);
	val &= ~BIT(data->hwirq + PCIE_INTX_SHIFT);
	ग_लिखोl_relaxed(val, port->base + PCIE_INT_ENABLE_REG);
	raw_spin_unlock_irqrestore(&port->irq_lock, flags);
पूर्ण

अटल व्योम mtk_पूर्णांकx_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा mtk_pcie_port *port = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&port->irq_lock, flags);
	val = पढ़ोl_relaxed(port->base + PCIE_INT_ENABLE_REG);
	val |= BIT(data->hwirq + PCIE_INTX_SHIFT);
	ग_लिखोl_relaxed(val, port->base + PCIE_INT_ENABLE_REG);
	raw_spin_unlock_irqrestore(&port->irq_lock, flags);
पूर्ण

/**
 * mtk_पूर्णांकx_eoi() - Clear INTx IRQ status at the end of पूर्णांकerrupt
 * @data: poपूर्णांकer to chip specअगरic data
 *
 * As an emulated level IRQ, its पूर्णांकerrupt status will reमुख्य
 * until the corresponding de-निश्चित message is received; hence that
 * the status can only be cleared when the पूर्णांकerrupt has been serviced.
 */
अटल व्योम mtk_पूर्णांकx_eoi(काष्ठा irq_data *data)
अणु
	काष्ठा mtk_pcie_port *port = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ hwirq;

	hwirq = data->hwirq + PCIE_INTX_SHIFT;
	ग_लिखोl_relaxed(BIT(hwirq), port->base + PCIE_INT_STATUS_REG);
पूर्ण

अटल काष्ठा irq_chip mtk_पूर्णांकx_irq_chip = अणु
	.irq_mask		= mtk_पूर्णांकx_mask,
	.irq_unmask		= mtk_पूर्णांकx_unmask,
	.irq_eoi		= mtk_पूर्णांकx_eoi,
	.irq_set_affinity	= mtk_pcie_set_affinity,
	.name			= "INTx",
पूर्ण;

अटल पूर्णांक mtk_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
			     irq_hw_number_t hwirq)
अणु
	irq_set_chip_data(irq, करोमुख्य->host_data);
	irq_set_chip_and_handler_name(irq, &mtk_पूर्णांकx_irq_chip,
				      handle_fasteoi_irq, "INTx");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकx_करोमुख्य_ops = अणु
	.map = mtk_pcie_पूर्णांकx_map,
पूर्ण;

अटल पूर्णांक mtk_pcie_init_irq_करोमुख्यs(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा device_node *पूर्णांकc_node, *node = dev->of_node;
	पूर्णांक ret;

	raw_spin_lock_init(&port->irq_lock);

	/* Setup INTx */
	पूर्णांकc_node = of_get_child_by_name(node, "interrupt-controller");
	अगर (!पूर्णांकc_node) अणु
		dev_err(dev, "missing interrupt-controller node\n");
		वापस -ENODEV;
	पूर्ण

	port->पूर्णांकx_करोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc_node, PCI_NUM_INTX,
						  &पूर्णांकx_करोमुख्य_ops, port);
	अगर (!port->पूर्णांकx_करोमुख्य) अणु
		dev_err(dev, "failed to create INTx IRQ domain\n");
		वापस -ENODEV;
	पूर्ण

	/* Setup MSI */
	mutex_init(&port->lock);

	port->msi_bottom_करोमुख्य = irq_करोमुख्य_add_linear(node, PCIE_MSI_IRQS_NUM,
				  &mtk_msi_bottom_करोमुख्य_ops, port);
	अगर (!port->msi_bottom_करोमुख्य) अणु
		dev_err(dev, "failed to create MSI bottom domain\n");
		ret = -ENODEV;
		जाओ err_msi_bottom_करोमुख्य;
	पूर्ण

	port->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(dev->fwnode,
						     &mtk_msi_करोमुख्य_info,
						     port->msi_bottom_करोमुख्य);
	अगर (!port->msi_करोमुख्य) अणु
		dev_err(dev, "failed to create MSI domain\n");
		ret = -ENODEV;
		जाओ err_msi_करोमुख्य;
	पूर्ण

	वापस 0;

err_msi_करोमुख्य:
	irq_करोमुख्य_हटाओ(port->msi_bottom_करोमुख्य);
err_msi_bottom_करोमुख्य:
	irq_करोमुख्य_हटाओ(port->पूर्णांकx_करोमुख्य);

	वापस ret;
पूर्ण

अटल व्योम mtk_pcie_irq_tearकरोwn(काष्ठा mtk_pcie_port *port)
अणु
	irq_set_chained_handler_and_data(port->irq, शून्य, शून्य);

	अगर (port->पूर्णांकx_करोमुख्य)
		irq_करोमुख्य_हटाओ(port->पूर्णांकx_करोमुख्य);

	अगर (port->msi_करोमुख्य)
		irq_करोमुख्य_हटाओ(port->msi_करोमुख्य);

	अगर (port->msi_bottom_करोमुख्य)
		irq_करोमुख्य_हटाओ(port->msi_bottom_करोमुख्य);

	irq_dispose_mapping(port->irq);
पूर्ण

अटल व्योम mtk_pcie_msi_handler(काष्ठा mtk_pcie_port *port, पूर्णांक set_idx)
अणु
	काष्ठा mtk_msi_set *msi_set = &port->msi_sets[set_idx];
	अचिन्हित दीर्घ msi_enable, msi_status;
	अचिन्हित पूर्णांक virq;
	irq_hw_number_t bit, hwirq;

	msi_enable = पढ़ोl_relaxed(msi_set->base + PCIE_MSI_SET_ENABLE_OFFSET);

	करो अणु
		msi_status = पढ़ोl_relaxed(msi_set->base +
					   PCIE_MSI_SET_STATUS_OFFSET);
		msi_status &= msi_enable;
		अगर (!msi_status)
			अवरोध;

		क्रम_each_set_bit(bit, &msi_status, PCIE_MSI_IRQS_PER_SET) अणु
			hwirq = bit + set_idx * PCIE_MSI_IRQS_PER_SET;
			virq = irq_find_mapping(port->msi_bottom_करोमुख्य, hwirq);
			generic_handle_irq(virq);
		पूर्ण
	पूर्ण जबतक (true);
पूर्ण

अटल व्योम mtk_pcie_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा mtk_pcie_port *port = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *irqchip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ status;
	अचिन्हित पूर्णांक virq;
	irq_hw_number_t irq_bit = PCIE_INTX_SHIFT;

	chained_irq_enter(irqchip, desc);

	status = पढ़ोl_relaxed(port->base + PCIE_INT_STATUS_REG);
	क्रम_each_set_bit_from(irq_bit, &status, PCI_NUM_INTX +
			      PCIE_INTX_SHIFT) अणु
		virq = irq_find_mapping(port->पूर्णांकx_करोमुख्य,
					irq_bit - PCIE_INTX_SHIFT);
		generic_handle_irq(virq);
	पूर्ण

	irq_bit = PCIE_MSI_SHIFT;
	क्रम_each_set_bit_from(irq_bit, &status, PCIE_MSI_SET_NUM +
			      PCIE_MSI_SHIFT) अणु
		mtk_pcie_msi_handler(port, irq_bit - PCIE_MSI_SHIFT);

		ग_लिखोl_relaxed(BIT(irq_bit), port->base + PCIE_INT_STATUS_REG);
	पूर्ण

	chained_irq_निकास(irqchip, desc);
पूर्ण

अटल पूर्णांक mtk_pcie_setup_irq(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक err;

	err = mtk_pcie_init_irq_करोमुख्यs(port);
	अगर (err)
		वापस err;

	port->irq = platक्रमm_get_irq(pdev, 0);
	अगर (port->irq < 0)
		वापस port->irq;

	irq_set_chained_handler_and_data(port->irq, mtk_pcie_irq_handler, port);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcie_parse_port(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *regs;
	पूर्णांक ret;

	regs = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pcie-mac");
	अगर (!regs)
		वापस -EINVAL;
	port->base = devm_ioremap_resource(dev, regs);
	अगर (IS_ERR(port->base)) अणु
		dev_err(dev, "failed to map register base\n");
		वापस PTR_ERR(port->base);
	पूर्ण

	port->reg_base = regs->start;

	port->phy_reset = devm_reset_control_get_optional_exclusive(dev, "phy");
	अगर (IS_ERR(port->phy_reset)) अणु
		ret = PTR_ERR(port->phy_reset);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get PHY reset\n");

		वापस ret;
	पूर्ण

	port->mac_reset = devm_reset_control_get_optional_exclusive(dev, "mac");
	अगर (IS_ERR(port->mac_reset)) अणु
		ret = PTR_ERR(port->mac_reset);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get MAC reset\n");

		वापस ret;
	पूर्ण

	port->phy = devm_phy_optional_get(dev, "pcie-phy");
	अगर (IS_ERR(port->phy)) अणु
		ret = PTR_ERR(port->phy);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get PHY\n");

		वापस ret;
	पूर्ण

	port->num_clks = devm_clk_bulk_get_all(dev, &port->clks);
	अगर (port->num_clks < 0) अणु
		dev_err(dev, "failed to get clocks\n");
		वापस port->num_clks;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcie_घातer_up(काष्ठा mtk_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	पूर्णांक err;

	/* PHY घातer on and enable pipe घड़ी */
	reset_control_deनिश्चित(port->phy_reset);

	err = phy_init(port->phy);
	अगर (err) अणु
		dev_err(dev, "failed to initialize PHY\n");
		जाओ err_phy_init;
	पूर्ण

	err = phy_घातer_on(port->phy);
	अगर (err) अणु
		dev_err(dev, "failed to power on PHY\n");
		जाओ err_phy_on;
	पूर्ण

	/* MAC घातer on and enable transaction layer घड़ीs */
	reset_control_deनिश्चित(port->mac_reset);

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	err = clk_bulk_prepare_enable(port->num_clks, port->clks);
	अगर (err) अणु
		dev_err(dev, "failed to enable clocks\n");
		जाओ err_clk_init;
	पूर्ण

	वापस 0;

err_clk_init:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	reset_control_निश्चित(port->mac_reset);
	phy_घातer_off(port->phy);
err_phy_on:
	phy_निकास(port->phy);
err_phy_init:
	reset_control_निश्चित(port->phy_reset);

	वापस err;
पूर्ण

अटल व्योम mtk_pcie_घातer_करोwn(काष्ठा mtk_pcie_port *port)
अणु
	clk_bulk_disable_unprepare(port->num_clks, port->clks);

	pm_runसमय_put_sync(port->dev);
	pm_runसमय_disable(port->dev);
	reset_control_निश्चित(port->mac_reset);

	phy_घातer_off(port->phy);
	phy_निकास(port->phy);
	reset_control_निश्चित(port->phy_reset);
पूर्ण

अटल पूर्णांक mtk_pcie_setup(काष्ठा mtk_pcie_port *port)
अणु
	पूर्णांक err;

	err = mtk_pcie_parse_port(port);
	अगर (err)
		वापस err;

	/* Don't touch the hardware रेजिस्टरs beक्रमe घातer up */
	err = mtk_pcie_घातer_up(port);
	अगर (err)
		वापस err;

	/* Try link up */
	err = mtk_pcie_startup_port(port);
	अगर (err)
		जाओ err_setup;

	err = mtk_pcie_setup_irq(port);
	अगर (err)
		जाओ err_setup;

	वापस 0;

err_setup:
	mtk_pcie_घातer_करोwn(port);

	वापस err;
पूर्ण

अटल पूर्णांक mtk_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_pcie_port *port;
	काष्ठा pci_host_bridge *host;
	पूर्णांक err;

	host = devm_pci_alloc_host_bridge(dev, माप(*port));
	अगर (!host)
		वापस -ENOMEM;

	port = pci_host_bridge_priv(host);

	port->dev = dev;
	platक्रमm_set_drvdata(pdev, port);

	err = mtk_pcie_setup(port);
	अगर (err)
		वापस err;

	host->ops = &mtk_pcie_ops;
	host->sysdata = port;

	err = pci_host_probe(host);
	अगर (err) अणु
		mtk_pcie_irq_tearकरोwn(port);
		mtk_pcie_घातer_करोwn(port);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_pcie_port *port = platक्रमm_get_drvdata(pdev);
	काष्ठा pci_host_bridge *host = pci_host_bridge_from_priv(port);

	pci_lock_rescan_हटाओ();
	pci_stop_root_bus(host->bus);
	pci_हटाओ_root_bus(host->bus);
	pci_unlock_rescan_हटाओ();

	mtk_pcie_irq_tearकरोwn(port);
	mtk_pcie_घातer_करोwn(port);

	वापस 0;
पूर्ण

अटल व्योम __maybe_unused mtk_pcie_irq_save(काष्ठा mtk_pcie_port *port)
अणु
	पूर्णांक i;

	raw_spin_lock(&port->irq_lock);

	port->saved_irq_state = पढ़ोl_relaxed(port->base + PCIE_INT_ENABLE_REG);

	क्रम (i = 0; i < PCIE_MSI_SET_NUM; i++) अणु
		काष्ठा mtk_msi_set *msi_set = &port->msi_sets[i];

		msi_set->saved_irq_state = पढ़ोl_relaxed(msi_set->base +
					   PCIE_MSI_SET_ENABLE_OFFSET);
	पूर्ण

	raw_spin_unlock(&port->irq_lock);
पूर्ण

अटल व्योम __maybe_unused mtk_pcie_irq_restore(काष्ठा mtk_pcie_port *port)
अणु
	पूर्णांक i;

	raw_spin_lock(&port->irq_lock);

	ग_लिखोl_relaxed(port->saved_irq_state, port->base + PCIE_INT_ENABLE_REG);

	क्रम (i = 0; i < PCIE_MSI_SET_NUM; i++) अणु
		काष्ठा mtk_msi_set *msi_set = &port->msi_sets[i];

		ग_लिखोl_relaxed(msi_set->saved_irq_state,
			       msi_set->base + PCIE_MSI_SET_ENABLE_OFFSET);
	पूर्ण

	raw_spin_unlock(&port->irq_lock);
पूर्ण

अटल पूर्णांक __maybe_unused mtk_pcie_turn_off_link(काष्ठा mtk_pcie_port *port)
अणु
	u32 val;

	val = पढ़ोl_relaxed(port->base + PCIE_ICMD_PM_REG);
	val |= PCIE_TURN_OFF_LINK;
	ग_लिखोl_relaxed(val, port->base + PCIE_ICMD_PM_REG);

	/* Check the link is L2 */
	वापस पढ़ोl_poll_समयout(port->base + PCIE_LTSSM_STATUS_REG, val,
				  (PCIE_LTSSM_STATE(val) ==
				   PCIE_LTSSM_STATE_L2_IDLE), 20,
				   50 * USEC_PER_MSEC);
पूर्ण

अटल पूर्णांक __maybe_unused mtk_pcie_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा mtk_pcie_port *port = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 val;

	/* Trigger link to L2 state */
	err = mtk_pcie_turn_off_link(port);
	अगर (err) अणु
		dev_err(port->dev, "cannot enter L2 state\n");
		वापस err;
	पूर्ण

	/* Pull करोwn the PERST# pin */
	val = पढ़ोl_relaxed(port->base + PCIE_RST_CTRL_REG);
	val |= PCIE_PE_RSTB;
	ग_लिखोl_relaxed(val, port->base + PCIE_RST_CTRL_REG);

	dev_dbg(port->dev, "entered L2 states successfully");

	mtk_pcie_irq_save(port);
	mtk_pcie_घातer_करोwn(port);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mtk_pcie_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा mtk_pcie_port *port = dev_get_drvdata(dev);
	पूर्णांक err;

	err = mtk_pcie_घातer_up(port);
	अगर (err)
		वापस err;

	err = mtk_pcie_startup_port(port);
	अगर (err) अणु
		mtk_pcie_घातer_करोwn(port);
		वापस err;
	पूर्ण

	mtk_pcie_irq_restore(port);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mtk_pcie_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(mtk_pcie_suspend_noirq,
				      mtk_pcie_resume_noirq)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_pcie_of_match[] = अणु
	अणु .compatible = "mediatek,mt8192-pcie" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_pcie_driver = अणु
	.probe = mtk_pcie_probe,
	.हटाओ = mtk_pcie_हटाओ,
	.driver = अणु
		.name = "mtk-pcie",
		.of_match_table = mtk_pcie_of_match,
		.pm = &mtk_pcie_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_pcie_driver);
MODULE_LICENSE("GPL v2");
