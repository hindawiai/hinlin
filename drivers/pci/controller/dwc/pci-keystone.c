<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Texas Instruments Keystone SoCs
 *
 * Copyright (C) 2013-2014 Texas Instruments., Ltd.
 *		https://www.ti.com
 *
 * Author: Murali Karicheri <m-karicheri2@ti.com>
 * Implementation based on pci-exynos.c and pcie-designware.c
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/resource.h>
#समावेश <linux/संकेत.स>

#समावेश "../../pci.h"
#समावेश "pcie-designware.h"

#घोषणा PCIE_VENDORID_MASK	0xffff
#घोषणा PCIE_DEVICEID_SHIFT	16

/* Application रेजिस्टरs */
#घोषणा CMD_STATUS			0x004
#घोषणा LTSSM_EN_VAL		        BIT(0)
#घोषणा OB_XLAT_EN_VAL		        BIT(1)
#घोषणा DBI_CS2				BIT(5)

#घोषणा CFG_SETUP			0x008
#घोषणा CFG_BUS(x)			(((x) & 0xff) << 16)
#घोषणा CFG_DEVICE(x)			(((x) & 0x1f) << 8)
#घोषणा CFG_FUNC(x)			((x) & 0x7)
#घोषणा CFG_TYPE1			BIT(24)

#घोषणा OB_SIZE				0x030
#घोषणा OB_OFFSET_INDEX(n)		(0x200 + (8 * (n)))
#घोषणा OB_OFFSET_HI(n)			(0x204 + (8 * (n)))
#घोषणा OB_ENABLEN			BIT(0)
#घोषणा OB_WIN_SIZE			8	/* 8MB */

#घोषणा PCIE_LEGACY_IRQ_ENABLE_SET(n)	(0x188 + (0x10 * ((n) - 1)))
#घोषणा PCIE_LEGACY_IRQ_ENABLE_CLR(n)	(0x18c + (0x10 * ((n) - 1)))
#घोषणा PCIE_EP_IRQ_SET			0x64
#घोषणा PCIE_EP_IRQ_CLR			0x68
#घोषणा INT_ENABLE			BIT(0)

/* IRQ रेजिस्टर defines */
#घोषणा IRQ_EOI				0x050

#घोषणा MSI_IRQ				0x054
#घोषणा MSI_IRQ_STATUS(n)		(0x104 + ((n) << 4))
#घोषणा MSI_IRQ_ENABLE_SET(n)		(0x108 + ((n) << 4))
#घोषणा MSI_IRQ_ENABLE_CLR(n)		(0x10c + ((n) << 4))
#घोषणा MSI_IRQ_OFFSET			4

#घोषणा IRQ_STATUS(n)			(0x184 + ((n) << 4))
#घोषणा IRQ_ENABLE_SET(n)		(0x188 + ((n) << 4))
#घोषणा INTx_EN				BIT(0)

#घोषणा ERR_IRQ_STATUS			0x1c4
#घोषणा ERR_IRQ_ENABLE_SET		0x1c8
#घोषणा ERR_AER				BIT(5)	/* ECRC error */
#घोषणा AM6_ERR_AER			BIT(4)	/* AM6 ECRC error */
#घोषणा ERR_AXI				BIT(4)	/* AXI tag lookup fatal error */
#घोषणा ERR_CORR			BIT(3)	/* Correctable error */
#घोषणा ERR_NONFATAL			BIT(2)	/* Non-fatal error */
#घोषणा ERR_FATAL			BIT(1)	/* Fatal error */
#घोषणा ERR_SYS				BIT(0)	/* System error */
#घोषणा ERR_IRQ_ALL			(ERR_AER | ERR_AXI | ERR_CORR | \
					 ERR_NONFATAL | ERR_FATAL | ERR_SYS)

/* PCIE controller device IDs */
#घोषणा PCIE_RC_K2HK			0xb008
#घोषणा PCIE_RC_K2E			0xb009
#घोषणा PCIE_RC_K2L			0xb00a
#घोषणा PCIE_RC_K2G			0xb00b

#घोषणा KS_PCIE_DEV_TYPE_MASK		(0x3 << 1)
#घोषणा KS_PCIE_DEV_TYPE(mode)		((mode) << 1)

#घोषणा EP				0x0
#घोषणा LEG_EP				0x1
#घोषणा RC				0x2

#घोषणा KS_PCIE_SYSCLOCKOUTEN		BIT(0)

#घोषणा AM654_PCIE_DEV_TYPE_MASK	0x3
#घोषणा AM654_WIN_SIZE			SZ_64K

#घोषणा APP_ADDR_SPACE_0		(16 * SZ_1K)

#घोषणा to_keystone_pcie(x)		dev_get_drvdata((x)->dev)

काष्ठा ks_pcie_of_data अणु
	क्रमागत dw_pcie_device_mode mode;
	स्थिर काष्ठा dw_pcie_host_ops *host_ops;
	स्थिर काष्ठा dw_pcie_ep_ops *ep_ops;
	अचिन्हित पूर्णांक version;
पूर्ण;

काष्ठा keystone_pcie अणु
	काष्ठा dw_pcie		*pci;
	/* PCI Device ID */
	u32			device_id;
	पूर्णांक			legacy_host_irqs[PCI_NUM_INTX];
	काष्ठा			device_node *legacy_पूर्णांकc_np;

	पूर्णांक			msi_host_irq;
	पूर्णांक			num_lanes;
	u32			num_viewport;
	काष्ठा phy		**phy;
	काष्ठा device_link	**link;
	काष्ठा			device_node *msi_पूर्णांकc_np;
	काष्ठा irq_करोमुख्य	*legacy_irq_करोमुख्य;
	काष्ठा device_node	*np;

	/* Application रेजिस्टर space */
	व्योम __iomem		*va_app_base;	/* DT 1st resource */
	काष्ठा resource		app;
	bool			is_am6;
पूर्ण;

अटल u32 ks_pcie_app_पढ़ोl(काष्ठा keystone_pcie *ks_pcie, u32 offset)
अणु
	वापस पढ़ोl(ks_pcie->va_app_base + offset);
पूर्ण

अटल व्योम ks_pcie_app_ग_लिखोl(काष्ठा keystone_pcie *ks_pcie, u32 offset,
			       u32 val)
अणु
	ग_लिखोl(val, ks_pcie->va_app_base + offset);
पूर्ण

अटल व्योम ks_pcie_msi_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा pcie_port *pp  = irq_data_get_irq_chip_data(data);
	काष्ठा keystone_pcie *ks_pcie;
	u32 irq = data->hwirq;
	काष्ठा dw_pcie *pci;
	u32 reg_offset;
	u32 bit_pos;

	pci = to_dw_pcie_from_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	reg_offset = irq % 8;
	bit_pos = irq >> 3;

	ks_pcie_app_ग_लिखोl(ks_pcie, MSI_IRQ_STATUS(reg_offset),
			   BIT(bit_pos));
	ks_pcie_app_ग_लिखोl(ks_pcie, IRQ_EOI, reg_offset + MSI_IRQ_OFFSET);
पूर्ण

अटल व्योम ks_pcie_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा pcie_port *pp = irq_data_get_irq_chip_data(data);
	काष्ठा keystone_pcie *ks_pcie;
	काष्ठा dw_pcie *pci;
	u64 msi_target;

	pci = to_dw_pcie_from_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	msi_target = ks_pcie->app.start + MSI_IRQ;
	msg->address_lo = lower_32_bits(msi_target);
	msg->address_hi = upper_32_bits(msi_target);
	msg->data = data->hwirq;

	dev_dbg(pci->dev, "msi#%d address_hi %#x address_lo %#x\n",
		(पूर्णांक)data->hwirq, msg->address_hi, msg->address_lo);
पूर्ण

अटल पूर्णांक ks_pcie_msi_set_affinity(काष्ठा irq_data *irq_data,
				    स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम ks_pcie_msi_mask(काष्ठा irq_data *data)
अणु
	काष्ठा pcie_port *pp = irq_data_get_irq_chip_data(data);
	काष्ठा keystone_pcie *ks_pcie;
	u32 irq = data->hwirq;
	काष्ठा dw_pcie *pci;
	अचिन्हित दीर्घ flags;
	u32 reg_offset;
	u32 bit_pos;

	raw_spin_lock_irqsave(&pp->lock, flags);

	pci = to_dw_pcie_from_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	reg_offset = irq % 8;
	bit_pos = irq >> 3;

	ks_pcie_app_ग_लिखोl(ks_pcie, MSI_IRQ_ENABLE_CLR(reg_offset),
			   BIT(bit_pos));

	raw_spin_unlock_irqrestore(&pp->lock, flags);
पूर्ण

अटल व्योम ks_pcie_msi_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा pcie_port *pp = irq_data_get_irq_chip_data(data);
	काष्ठा keystone_pcie *ks_pcie;
	u32 irq = data->hwirq;
	काष्ठा dw_pcie *pci;
	अचिन्हित दीर्घ flags;
	u32 reg_offset;
	u32 bit_pos;

	raw_spin_lock_irqsave(&pp->lock, flags);

	pci = to_dw_pcie_from_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	reg_offset = irq % 8;
	bit_pos = irq >> 3;

	ks_pcie_app_ग_लिखोl(ks_pcie, MSI_IRQ_ENABLE_SET(reg_offset),
			   BIT(bit_pos));

	raw_spin_unlock_irqrestore(&pp->lock, flags);
पूर्ण

अटल काष्ठा irq_chip ks_pcie_msi_irq_chip = अणु
	.name = "KEYSTONE-PCI-MSI",
	.irq_ack = ks_pcie_msi_irq_ack,
	.irq_compose_msi_msg = ks_pcie_compose_msi_msg,
	.irq_set_affinity = ks_pcie_msi_set_affinity,
	.irq_mask = ks_pcie_msi_mask,
	.irq_unmask = ks_pcie_msi_unmask,
पूर्ण;

अटल पूर्णांक ks_pcie_msi_host_init(काष्ठा pcie_port *pp)
अणु
	pp->msi_irq_chip = &ks_pcie_msi_irq_chip;
	वापस dw_pcie_allocate_करोमुख्यs(pp);
पूर्ण

अटल व्योम ks_pcie_handle_legacy_irq(काष्ठा keystone_pcie *ks_pcie,
				      पूर्णांक offset)
अणु
	काष्ठा dw_pcie *pci = ks_pcie->pci;
	काष्ठा device *dev = pci->dev;
	u32 pending;
	पूर्णांक virq;

	pending = ks_pcie_app_पढ़ोl(ks_pcie, IRQ_STATUS(offset));

	अगर (BIT(0) & pending) अणु
		virq = irq_linear_revmap(ks_pcie->legacy_irq_करोमुख्य, offset);
		dev_dbg(dev, ": irq: irq_offset %d, virq %d\n", offset, virq);
		generic_handle_irq(virq);
	पूर्ण

	/* EOI the INTx पूर्णांकerrupt */
	ks_pcie_app_ग_लिखोl(ks_pcie, IRQ_EOI, offset);
पूर्ण

अटल व्योम ks_pcie_enable_error_irq(काष्ठा keystone_pcie *ks_pcie)
अणु
	ks_pcie_app_ग_लिखोl(ks_pcie, ERR_IRQ_ENABLE_SET, ERR_IRQ_ALL);
पूर्ण

अटल irqवापस_t ks_pcie_handle_error_irq(काष्ठा keystone_pcie *ks_pcie)
अणु
	u32 reg;
	काष्ठा device *dev = ks_pcie->pci->dev;

	reg = ks_pcie_app_पढ़ोl(ks_pcie, ERR_IRQ_STATUS);
	अगर (!reg)
		वापस IRQ_NONE;

	अगर (reg & ERR_SYS)
		dev_err(dev, "System Error\n");

	अगर (reg & ERR_FATAL)
		dev_err(dev, "Fatal Error\n");

	अगर (reg & ERR_NONFATAL)
		dev_dbg(dev, "Non Fatal Error\n");

	अगर (reg & ERR_CORR)
		dev_dbg(dev, "Correctable Error\n");

	अगर (!ks_pcie->is_am6 && (reg & ERR_AXI))
		dev_err(dev, "AXI tag lookup fatal Error\n");

	अगर (reg & ERR_AER || (ks_pcie->is_am6 && (reg & AM6_ERR_AER)))
		dev_err(dev, "ECRC Error\n");

	ks_pcie_app_ग_लिखोl(ks_pcie, ERR_IRQ_STATUS, reg);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ks_pcie_ack_legacy_irq(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम ks_pcie_mask_legacy_irq(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम ks_pcie_unmask_legacy_irq(काष्ठा irq_data *d)
अणु
पूर्ण

अटल काष्ठा irq_chip ks_pcie_legacy_irq_chip = अणु
	.name = "Keystone-PCI-Legacy-IRQ",
	.irq_ack = ks_pcie_ack_legacy_irq,
	.irq_mask = ks_pcie_mask_legacy_irq,
	.irq_unmask = ks_pcie_unmask_legacy_irq,
पूर्ण;

अटल पूर्णांक ks_pcie_init_legacy_irq_map(काष्ठा irq_करोमुख्य *d,
				       अचिन्हित पूर्णांक irq,
				       irq_hw_number_t hw_irq)
अणु
	irq_set_chip_and_handler(irq, &ks_pcie_legacy_irq_chip,
				 handle_level_irq);
	irq_set_chip_data(irq, d->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ks_pcie_legacy_irq_करोमुख्य_ops = अणु
	.map = ks_pcie_init_legacy_irq_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

/**
 * ks_pcie_set_dbi_mode() - Set DBI mode to access overlaid BAR mask रेजिस्टरs
 * @ks_pcie: A poपूर्णांकer to the keystone_pcie काष्ठाure which holds the KeyStone
 *	     PCIe host controller driver inक्रमmation.
 *
 * Since modअगरication of dbi_cs2 involves dअगरferent घड़ी करोमुख्य, पढ़ो the
 * status back to ensure the transition is complete.
 */
अटल व्योम ks_pcie_set_dbi_mode(काष्ठा keystone_pcie *ks_pcie)
अणु
	u32 val;

	val = ks_pcie_app_पढ़ोl(ks_pcie, CMD_STATUS);
	val |= DBI_CS2;
	ks_pcie_app_ग_लिखोl(ks_pcie, CMD_STATUS, val);

	करो अणु
		val = ks_pcie_app_पढ़ोl(ks_pcie, CMD_STATUS);
	पूर्ण जबतक (!(val & DBI_CS2));
पूर्ण

/**
 * ks_pcie_clear_dbi_mode() - Disable DBI mode
 * @ks_pcie: A poपूर्णांकer to the keystone_pcie काष्ठाure which holds the KeyStone
 *	     PCIe host controller driver inक्रमmation.
 *
 * Since modअगरication of dbi_cs2 involves dअगरferent घड़ी करोमुख्य, पढ़ो the
 * status back to ensure the transition is complete.
 */
अटल व्योम ks_pcie_clear_dbi_mode(काष्ठा keystone_pcie *ks_pcie)
अणु
	u32 val;

	val = ks_pcie_app_पढ़ोl(ks_pcie, CMD_STATUS);
	val &= ~DBI_CS2;
	ks_pcie_app_ग_लिखोl(ks_pcie, CMD_STATUS, val);

	करो अणु
		val = ks_pcie_app_पढ़ोl(ks_pcie, CMD_STATUS);
	पूर्ण जबतक (val & DBI_CS2);
पूर्ण

अटल व्योम ks_pcie_setup_rc_app_regs(काष्ठा keystone_pcie *ks_pcie)
अणु
	u32 val;
	u32 num_viewport = ks_pcie->num_viewport;
	काष्ठा dw_pcie *pci = ks_pcie->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	u64 start, end;
	काष्ठा resource *mem;
	पूर्णांक i;

	mem = resource_list_first_type(&pp->bridge->winकरोws, IORESOURCE_MEM)->res;
	start = mem->start;
	end = mem->end;

	/* Disable BARs क्रम inbound access */
	ks_pcie_set_dbi_mode(ks_pcie);
	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_0, 0);
	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_1, 0);
	ks_pcie_clear_dbi_mode(ks_pcie);

	अगर (ks_pcie->is_am6)
		वापस;

	val = ilog2(OB_WIN_SIZE);
	ks_pcie_app_ग_लिखोl(ks_pcie, OB_SIZE, val);

	/* Using Direct 1:1 mapping of RC <-> PCI memory space */
	क्रम (i = 0; i < num_viewport && (start < end); i++) अणु
		ks_pcie_app_ग_लिखोl(ks_pcie, OB_OFFSET_INDEX(i),
				   lower_32_bits(start) | OB_ENABLEN);
		ks_pcie_app_ग_लिखोl(ks_pcie, OB_OFFSET_HI(i),
				   upper_32_bits(start));
		start += OB_WIN_SIZE * SZ_1M;
	पूर्ण

	val = ks_pcie_app_पढ़ोl(ks_pcie, CMD_STATUS);
	val |= OB_XLAT_EN_VAL;
	ks_pcie_app_ग_लिखोl(ks_pcie, CMD_STATUS, val);
पूर्ण

अटल व्योम __iomem *ks_pcie_other_map_bus(काष्ठा pci_bus *bus,
					   अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा pcie_port *pp = bus->sysdata;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा keystone_pcie *ks_pcie = to_keystone_pcie(pci);
	u32 reg;

	reg = CFG_BUS(bus->number) | CFG_DEVICE(PCI_SLOT(devfn)) |
		CFG_FUNC(PCI_FUNC(devfn));
	अगर (!pci_is_root_bus(bus->parent))
		reg |= CFG_TYPE1;
	ks_pcie_app_ग_लिखोl(ks_pcie, CFG_SETUP, reg);

	वापस pp->va_cfg0_base + where;
पूर्ण

अटल काष्ठा pci_ops ks_child_pcie_ops = अणु
	.map_bus = ks_pcie_other_map_bus,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

/**
 * ks_pcie_v3_65_add_bus() - keystone add_bus post initialization
 * @bus: A poपूर्णांकer to the PCI bus काष्ठाure.
 *
 * This sets BAR0 to enable inbound access क्रम MSI_IRQ रेजिस्टर
 */
अटल पूर्णांक ks_pcie_v3_65_add_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pcie_port *pp = bus->sysdata;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा keystone_pcie *ks_pcie = to_keystone_pcie(pci);

	अगर (!pci_is_root_bus(bus))
		वापस 0;

	/* Configure and set up BAR0 */
	ks_pcie_set_dbi_mode(ks_pcie);

	/* Enable BAR0 */
	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_0, 1);
	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_0, SZ_4K - 1);

	ks_pcie_clear_dbi_mode(ks_pcie);

	 /*
	  * For BAR0, just setting bus address क्रम inbound ग_लिखोs (MSI) should
	  * be sufficient.  Use physical address to aव्योम any conflicts.
	  */
	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_0, ks_pcie->app.start);

	वापस 0;
पूर्ण

अटल काष्ठा pci_ops ks_pcie_ops = अणु
	.map_bus = dw_pcie_own_conf_map_bus,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
	.add_bus = ks_pcie_v3_65_add_bus,
पूर्ण;

/**
 * ks_pcie_link_up() - Check अगर link up
 * @pci: A poपूर्णांकer to the dw_pcie काष्ठाure which holds the DesignWare PCIe host
 *	 controller driver inक्रमmation.
 */
अटल पूर्णांक ks_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	u32 val;

	val = dw_pcie_पढ़ोl_dbi(pci, PCIE_PORT_DEBUG0);
	val &= PORT_LOGIC_LTSSM_STATE_MASK;
	वापस (val == PORT_LOGIC_LTSSM_STATE_L0);
पूर्ण

अटल व्योम ks_pcie_stop_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा keystone_pcie *ks_pcie = to_keystone_pcie(pci);
	u32 val;

	/* Disable Link training */
	val = ks_pcie_app_पढ़ोl(ks_pcie, CMD_STATUS);
	val &= ~LTSSM_EN_VAL;
	ks_pcie_app_ग_लिखोl(ks_pcie, CMD_STATUS, val);
पूर्ण

अटल पूर्णांक ks_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा keystone_pcie *ks_pcie = to_keystone_pcie(pci);
	u32 val;

	/* Initiate Link Training */
	val = ks_pcie_app_पढ़ोl(ks_pcie, CMD_STATUS);
	ks_pcie_app_ग_लिखोl(ks_pcie, CMD_STATUS, LTSSM_EN_VAL | val);

	वापस 0;
पूर्ण

अटल व्योम ks_pcie_quirk(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus = dev->bus;
	काष्ठा pci_dev *bridge;
	अटल स्थिर काष्ठा pci_device_id rc_pci_devids[] = अणु
		अणु PCI_DEVICE(PCI_VENDOR_ID_TI, PCIE_RC_K2HK),
		 .class = PCI_CLASS_BRIDGE_PCI << 8, .class_mask = ~0, पूर्ण,
		अणु PCI_DEVICE(PCI_VENDOR_ID_TI, PCIE_RC_K2E),
		 .class = PCI_CLASS_BRIDGE_PCI << 8, .class_mask = ~0, पूर्ण,
		अणु PCI_DEVICE(PCI_VENDOR_ID_TI, PCIE_RC_K2L),
		 .class = PCI_CLASS_BRIDGE_PCI << 8, .class_mask = ~0, पूर्ण,
		अणु PCI_DEVICE(PCI_VENDOR_ID_TI, PCIE_RC_K2G),
		 .class = PCI_CLASS_BRIDGE_PCI << 8, .class_mask = ~0, पूर्ण,
		अणु 0, पूर्ण,
	पूर्ण;

	अगर (pci_is_root_bus(bus))
		bridge = dev;

	/* look क्रम the host bridge */
	जबतक (!pci_is_root_bus(bus)) अणु
		bridge = bus->self;
		bus = bus->parent;
	पूर्ण

	अगर (!bridge)
		वापस;

	/*
	 * Keystone PCI controller has a h/w limitation of
	 * 256 bytes maximum पढ़ो request size.  It can't handle
	 * anything higher than this.  So क्रमce this limit on
	 * all करोwnstream devices.
	 */
	अगर (pci_match_id(rc_pci_devids, bridge)) अणु
		अगर (pcie_get_पढ़ोrq(dev) > 256) अणु
			dev_info(&dev->dev, "limiting MRRS to 256\n");
			pcie_set_पढ़ोrq(dev, 256);
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_ENABLE(PCI_ANY_ID, PCI_ANY_ID, ks_pcie_quirk);

अटल व्योम ks_pcie_msi_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = desc->irq_data.hwirq;
	काष्ठा keystone_pcie *ks_pcie = irq_desc_get_handler_data(desc);
	u32 offset = irq - ks_pcie->msi_host_irq;
	काष्ठा dw_pcie *pci = ks_pcie->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	काष्ठा device *dev = pci->dev;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	u32 vector, virq, reg, pos;

	dev_dbg(dev, "%s, irq %d\n", __func__, irq);

	/*
	 * The chained irq handler installation would have replaced normal
	 * पूर्णांकerrupt driver handler so we need to take care of mask/unmask and
	 * ack operation.
	 */
	chained_irq_enter(chip, desc);

	reg = ks_pcie_app_पढ़ोl(ks_pcie, MSI_IRQ_STATUS(offset));
	/*
	 * MSI0 status bit 0-3 shows vectors 0, 8, 16, 24, MSI1 status bit
	 * shows 1, 9, 17, 25 and so क्रमth
	 */
	क्रम (pos = 0; pos < 4; pos++) अणु
		अगर (!(reg & BIT(pos)))
			जारी;

		vector = offset + (pos << 3);
		virq = irq_linear_revmap(pp->irq_करोमुख्य, vector);
		dev_dbg(dev, "irq: bit %d, vector %d, virq %d\n", pos, vector,
			virq);
		generic_handle_irq(virq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

/**
 * ks_pcie_legacy_irq_handler() - Handle legacy पूर्णांकerrupt
 * @desc: Poपूर्णांकer to irq descriptor
 *
 * Traverse through pending legacy पूर्णांकerrupts and invoke handler क्रम each. Also
 * takes care of पूर्णांकerrupt controller level mask/ack operation.
 */
अटल व्योम ks_pcie_legacy_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा keystone_pcie *ks_pcie = irq_desc_get_handler_data(desc);
	काष्ठा dw_pcie *pci = ks_pcie->pci;
	काष्ठा device *dev = pci->dev;
	u32 irq_offset = irq - ks_pcie->legacy_host_irqs[0];
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	dev_dbg(dev, ": Handling legacy irq %d\n", irq);

	/*
	 * The chained irq handler installation would have replaced normal
	 * पूर्णांकerrupt driver handler so we need to take care of mask/unmask and
	 * ack operation.
	 */
	chained_irq_enter(chip, desc);
	ks_pcie_handle_legacy_irq(ks_pcie, irq_offset);
	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक ks_pcie_config_msi_irq(काष्ठा keystone_pcie *ks_pcie)
अणु
	काष्ठा device *dev = ks_pcie->pci->dev;
	काष्ठा device_node *np = ks_pcie->np;
	काष्ठा device_node *पूर्णांकc_np;
	काष्ठा irq_data *irq_data;
	पूर्णांक irq_count, irq, ret, i;

	अगर (!IS_ENABLED(CONFIG_PCI_MSI))
		वापस 0;

	पूर्णांकc_np = of_get_child_by_name(np, "msi-interrupt-controller");
	अगर (!पूर्णांकc_np) अणु
		अगर (ks_pcie->is_am6)
			वापस 0;
		dev_warn(dev, "msi-interrupt-controller node is absent\n");
		वापस -EINVAL;
	पूर्ण

	irq_count = of_irq_count(पूर्णांकc_np);
	अगर (!irq_count) अणु
		dev_err(dev, "No IRQ entries in msi-interrupt-controller\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < irq_count; i++) अणु
		irq = irq_of_parse_and_map(पूर्णांकc_np, i);
		अगर (!irq) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (!ks_pcie->msi_host_irq) अणु
			irq_data = irq_get_irq_data(irq);
			अगर (!irq_data) अणु
				ret = -EINVAL;
				जाओ err;
			पूर्ण
			ks_pcie->msi_host_irq = irq_data->hwirq;
		पूर्ण

		irq_set_chained_handler_and_data(irq, ks_pcie_msi_irq_handler,
						 ks_pcie);
	पूर्ण

	of_node_put(पूर्णांकc_np);
	वापस 0;

err:
	of_node_put(पूर्णांकc_np);
	वापस ret;
पूर्ण

अटल पूर्णांक ks_pcie_config_legacy_irq(काष्ठा keystone_pcie *ks_pcie)
अणु
	काष्ठा device *dev = ks_pcie->pci->dev;
	काष्ठा irq_करोमुख्य *legacy_irq_करोमुख्य;
	काष्ठा device_node *np = ks_pcie->np;
	काष्ठा device_node *पूर्णांकc_np;
	पूर्णांक irq_count, irq, ret = 0, i;

	पूर्णांकc_np = of_get_child_by_name(np, "legacy-interrupt-controller");
	अगर (!पूर्णांकc_np) अणु
		/*
		 * Since legacy पूर्णांकerrupts are modeled as edge-पूर्णांकerrupts in
		 * AM6, keep it disabled क्रम now.
		 */
		अगर (ks_pcie->is_am6)
			वापस 0;
		dev_warn(dev, "legacy-interrupt-controller node is absent\n");
		वापस -EINVAL;
	पूर्ण

	irq_count = of_irq_count(पूर्णांकc_np);
	अगर (!irq_count) अणु
		dev_err(dev, "No IRQ entries in legacy-interrupt-controller\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < irq_count; i++) अणु
		irq = irq_of_parse_and_map(पूर्णांकc_np, i);
		अगर (!irq) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		ks_pcie->legacy_host_irqs[i] = irq;

		irq_set_chained_handler_and_data(irq,
						 ks_pcie_legacy_irq_handler,
						 ks_pcie);
	पूर्ण

	legacy_irq_करोमुख्य =
		irq_करोमुख्य_add_linear(पूर्णांकc_np, PCI_NUM_INTX,
				      &ks_pcie_legacy_irq_करोमुख्य_ops, शून्य);
	अगर (!legacy_irq_करोमुख्य) अणु
		dev_err(dev, "Failed to add irq domain for legacy irqs\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	ks_pcie->legacy_irq_करोमुख्य = legacy_irq_करोमुख्य;

	क्रम (i = 0; i < PCI_NUM_INTX; i++)
		ks_pcie_app_ग_लिखोl(ks_pcie, IRQ_ENABLE_SET(i), INTx_EN);

err:
	of_node_put(पूर्णांकc_np);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ARM
/*
 * When a PCI device करोes not exist during config cycles, keystone host माला_लो a
 * bus error instead of वापसing 0xffffffff. This handler always वापसs 0
 * क्रम this kind of faults.
 */
अटल पूर्णांक ks_pcie_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
			 काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ instr = *(अचिन्हित दीर्घ *) inकाष्ठाion_poपूर्णांकer(regs);

	अगर ((instr & 0x0e100090) == 0x00100090) अणु
		पूर्णांक reg = (instr >> 12) & 15;

		regs->uregs[reg] = -1;
		regs->ARM_pc += 4;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init ks_pcie_init_id(काष्ठा keystone_pcie *ks_pcie)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक id;
	काष्ठा regmap *devctrl_regs;
	काष्ठा dw_pcie *pci = ks_pcie->pci;
	काष्ठा device *dev = pci->dev;
	काष्ठा device_node *np = dev->of_node;

	devctrl_regs = syscon_regmap_lookup_by_phandle(np, "ti,syscon-pcie-id");
	अगर (IS_ERR(devctrl_regs))
		वापस PTR_ERR(devctrl_regs);

	ret = regmap_पढ़ो(devctrl_regs, 0, &id);
	अगर (ret)
		वापस ret;

	dw_pcie_dbi_ro_wr_en(pci);
	dw_pcie_ग_लिखोw_dbi(pci, PCI_VENDOR_ID, id & PCIE_VENDORID_MASK);
	dw_pcie_ग_लिखोw_dbi(pci, PCI_DEVICE_ID, id >> PCIE_DEVICEID_SHIFT);
	dw_pcie_dbi_ro_wr_dis(pci);

	वापस 0;
पूर्ण

अटल पूर्णांक __init ks_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा keystone_pcie *ks_pcie = to_keystone_pcie(pci);
	पूर्णांक ret;

	pp->bridge->ops = &ks_pcie_ops;
	अगर (!ks_pcie->is_am6)
		pp->bridge->child_ops = &ks_child_pcie_ops;

	ret = ks_pcie_config_legacy_irq(ks_pcie);
	अगर (ret)
		वापस ret;

	ret = ks_pcie_config_msi_irq(ks_pcie);
	अगर (ret)
		वापस ret;

	ks_pcie_stop_link(pci);
	ks_pcie_setup_rc_app_regs(ks_pcie);
	ग_लिखोw(PCI_IO_RANGE_TYPE_32 | (PCI_IO_RANGE_TYPE_32 << 8),
			pci->dbi_base + PCI_IO_BASE);

	ret = ks_pcie_init_id(ks_pcie);
	अगर (ret < 0)
		वापस ret;

#अगर_घोषित CONFIG_ARM
	/*
	 * PCIe access errors that result पूर्णांकo OCP errors are caught by ARM as
	 * "External aborts"
	 */
	hook_fault_code(17, ks_pcie_fault, SIGBUS, 0,
			"Asynchronous external abort");
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops ks_pcie_host_ops = अणु
	.host_init = ks_pcie_host_init,
	.msi_host_init = ks_pcie_msi_host_init,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_host_ops ks_pcie_am654_host_ops = अणु
	.host_init = ks_pcie_host_init,
पूर्ण;

अटल irqवापस_t ks_pcie_err_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा keystone_pcie *ks_pcie = priv;

	वापस ks_pcie_handle_error_irq(ks_pcie);
पूर्ण

अटल व्योम ks_pcie_am654_ग_लिखो_dbi2(काष्ठा dw_pcie *pci, व्योम __iomem *base,
				     u32 reg, माप_प्रकार size, u32 val)
अणु
	काष्ठा keystone_pcie *ks_pcie = to_keystone_pcie(pci);

	ks_pcie_set_dbi_mode(ks_pcie);
	dw_pcie_ग_लिखो(base + reg, size, val);
	ks_pcie_clear_dbi_mode(ks_pcie);
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops ks_pcie_dw_pcie_ops = अणु
	.start_link = ks_pcie_start_link,
	.stop_link = ks_pcie_stop_link,
	.link_up = ks_pcie_link_up,
	.ग_लिखो_dbi2 = ks_pcie_am654_ग_लिखो_dbi2,
पूर्ण;

अटल व्योम ks_pcie_am654_ep_init(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	पूर्णांक flags;

	ep->page_size = AM654_WIN_SIZE;
	flags = PCI_BASE_ADDRESS_SPACE_MEMORY | PCI_BASE_ADDRESS_MEM_TYPE_32;
	dw_pcie_ग_लिखोl_dbi2(pci, PCI_BASE_ADDRESS_0, APP_ADDR_SPACE_0 - 1);
	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_0, flags);
पूर्ण

अटल व्योम ks_pcie_am654_उठाओ_legacy_irq(काष्ठा keystone_pcie *ks_pcie)
अणु
	काष्ठा dw_pcie *pci = ks_pcie->pci;
	u8 पूर्णांक_pin;

	पूर्णांक_pin = dw_pcie_पढ़ोb_dbi(pci, PCI_INTERRUPT_PIN);
	अगर (पूर्णांक_pin == 0 || पूर्णांक_pin > 4)
		वापस;

	ks_pcie_app_ग_लिखोl(ks_pcie, PCIE_LEGACY_IRQ_ENABLE_SET(पूर्णांक_pin),
			   INT_ENABLE);
	ks_pcie_app_ग_लिखोl(ks_pcie, PCIE_EP_IRQ_SET, INT_ENABLE);
	mdelay(1);
	ks_pcie_app_ग_लिखोl(ks_pcie, PCIE_EP_IRQ_CLR, INT_ENABLE);
	ks_pcie_app_ग_लिखोl(ks_pcie, PCIE_LEGACY_IRQ_ENABLE_CLR(पूर्णांक_pin),
			   INT_ENABLE);
पूर्ण

अटल पूर्णांक ks_pcie_am654_उठाओ_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
				   क्रमागत pci_epc_irq_type type,
				   u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा keystone_pcie *ks_pcie = to_keystone_pcie(pci);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		ks_pcie_am654_उठाओ_legacy_irq(ks_pcie);
		अवरोध;
	हाल PCI_EPC_IRQ_MSI:
		dw_pcie_ep_उठाओ_msi_irq(ep, func_no, पूर्णांकerrupt_num);
		अवरोध;
	हाल PCI_EPC_IRQ_MSIX:
		dw_pcie_ep_उठाओ_msix_irq(ep, func_no, पूर्णांकerrupt_num);
		अवरोध;
	शेष:
		dev_err(pci->dev, "UNKNOWN IRQ type\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_epc_features ks_pcie_am654_epc_features = अणु
	.linkup_notअगरier = false,
	.msi_capable = true,
	.msix_capable = true,
	.reserved_bar = 1 << BAR_0 | 1 << BAR_1,
	.bar_fixed_64bit = 1 << BAR_0,
	.bar_fixed_size[2] = SZ_1M,
	.bar_fixed_size[3] = SZ_64K,
	.bar_fixed_size[4] = 256,
	.bar_fixed_size[5] = SZ_1M,
	.align = SZ_1M,
पूर्ण;

अटल स्थिर काष्ठा pci_epc_features*
ks_pcie_am654_get_features(काष्ठा dw_pcie_ep *ep)
अणु
	वापस &ks_pcie_am654_epc_features;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ep_ops ks_pcie_am654_ep_ops = अणु
	.ep_init = ks_pcie_am654_ep_init,
	.उठाओ_irq = ks_pcie_am654_उठाओ_irq,
	.get_features = &ks_pcie_am654_get_features,
पूर्ण;

अटल व्योम ks_pcie_disable_phy(काष्ठा keystone_pcie *ks_pcie)
अणु
	पूर्णांक num_lanes = ks_pcie->num_lanes;

	जबतक (num_lanes--) अणु
		phy_घातer_off(ks_pcie->phy[num_lanes]);
		phy_निकास(ks_pcie->phy[num_lanes]);
	पूर्ण
पूर्ण

अटल पूर्णांक ks_pcie_enable_phy(काष्ठा keystone_pcie *ks_pcie)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक num_lanes = ks_pcie->num_lanes;

	क्रम (i = 0; i < num_lanes; i++) अणु
		ret = phy_reset(ks_pcie->phy[i]);
		अगर (ret < 0)
			जाओ err_phy;

		ret = phy_init(ks_pcie->phy[i]);
		अगर (ret < 0)
			जाओ err_phy;

		ret = phy_घातer_on(ks_pcie->phy[i]);
		अगर (ret < 0) अणु
			phy_निकास(ks_pcie->phy[i]);
			जाओ err_phy;
		पूर्ण
	पूर्ण

	वापस 0;

err_phy:
	जबतक (--i >= 0) अणु
		phy_घातer_off(ks_pcie->phy[i]);
		phy_निकास(ks_pcie->phy[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ks_pcie_set_mode(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *syscon;
	u32 val;
	u32 mask;
	पूर्णांक ret = 0;

	syscon = syscon_regmap_lookup_by_phandle(np, "ti,syscon-pcie-mode");
	अगर (IS_ERR(syscon))
		वापस 0;

	mask = KS_PCIE_DEV_TYPE_MASK | KS_PCIE_SYSCLOCKOUTEN;
	val = KS_PCIE_DEV_TYPE(RC) | KS_PCIE_SYSCLOCKOUTEN;

	ret = regmap_update_bits(syscon, 0, mask, val);
	अगर (ret) अणु
		dev_err(dev, "failed to set pcie mode\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ks_pcie_am654_set_mode(काष्ठा device *dev,
				  क्रमागत dw_pcie_device_mode mode)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *syscon;
	u32 val;
	u32 mask;
	पूर्णांक ret = 0;

	syscon = syscon_regmap_lookup_by_phandle(np, "ti,syscon-pcie-mode");
	अगर (IS_ERR(syscon))
		वापस 0;

	mask = AM654_PCIE_DEV_TYPE_MASK;

	चयन (mode) अणु
	हाल DW_PCIE_RC_TYPE:
		val = RC;
		अवरोध;
	हाल DW_PCIE_EP_TYPE:
		val = EP;
		अवरोध;
	शेष:
		dev_err(dev, "INVALID device type %d\n", mode);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(syscon, 0, mask, val);
	अगर (ret) अणु
		dev_err(dev, "failed to set pcie mode\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ks_pcie_of_data ks_pcie_rc_of_data = अणु
	.host_ops = &ks_pcie_host_ops,
	.version = 0x365A,
पूर्ण;

अटल स्थिर काष्ठा ks_pcie_of_data ks_pcie_am654_rc_of_data = अणु
	.host_ops = &ks_pcie_am654_host_ops,
	.mode = DW_PCIE_RC_TYPE,
	.version = 0x490A,
पूर्ण;

अटल स्थिर काष्ठा ks_pcie_of_data ks_pcie_am654_ep_of_data = अणु
	.ep_ops = &ks_pcie_am654_ep_ops,
	.mode = DW_PCIE_EP_TYPE,
	.version = 0x490A,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ks_pcie_of_match[] = अणु
	अणु
		.type = "pci",
		.data = &ks_pcie_rc_of_data,
		.compatible = "ti,keystone-pcie",
	पूर्ण,
	अणु
		.data = &ks_pcie_am654_rc_of_data,
		.compatible = "ti,am654-pcie-rc",
	पूर्ण,
	अणु
		.data = &ks_pcie_am654_ep_of_data,
		.compatible = "ti,am654-pcie-ep",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __init ks_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा dw_pcie_host_ops *host_ops;
	स्थिर काष्ठा dw_pcie_ep_ops *ep_ops;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा ks_pcie_of_data *data;
	स्थिर काष्ठा of_device_id *match;
	क्रमागत dw_pcie_device_mode mode;
	काष्ठा dw_pcie *pci;
	काष्ठा keystone_pcie *ks_pcie;
	काष्ठा device_link **link;
	काष्ठा gpio_desc *gpiod;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक version;
	व्योम __iomem *base;
	u32 num_viewport;
	काष्ठा phy **phy;
	u32 num_lanes;
	अक्षर name[10];
	पूर्णांक ret;
	पूर्णांक irq;
	पूर्णांक i;

	match = of_match_device(of_match_ptr(ks_pcie_of_match), dev);
	data = (काष्ठा ks_pcie_of_data *)match->data;
	अगर (!data)
		वापस -EINVAL;

	version = data->version;
	host_ops = data->host_ops;
	ep_ops = data->ep_ops;
	mode = data->mode;

	ks_pcie = devm_kzalloc(dev, माप(*ks_pcie), GFP_KERNEL);
	अगर (!ks_pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "app");
	ks_pcie->va_app_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ks_pcie->va_app_base))
		वापस PTR_ERR(ks_pcie->va_app_base);

	ks_pcie->app = *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dbics");
	base = devm_pci_remap_cfg_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	अगर (of_device_is_compatible(np, "ti,am654-pcie-rc"))
		ks_pcie->is_am6 = true;

	pci->dbi_base = base;
	pci->dbi_base2 = base;
	pci->dev = dev;
	pci->ops = &ks_pcie_dw_pcie_ops;
	pci->version = version;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = request_irq(irq, ks_pcie_err_irq_handler, IRQF_SHARED,
			  "ks-pcie-error-irq", ks_pcie);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request error IRQ %d\n",
			irq);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "num-lanes", &num_lanes);
	अगर (ret)
		num_lanes = 1;

	phy = devm_kzalloc(dev, माप(*phy) * num_lanes, GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	link = devm_kzalloc(dev, माप(*link) * num_lanes, GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_lanes; i++) अणु
		snम_लिखो(name, माप(name), "pcie-phy%d", i);
		phy[i] = devm_phy_optional_get(dev, name);
		अगर (IS_ERR(phy[i])) अणु
			ret = PTR_ERR(phy[i]);
			जाओ err_link;
		पूर्ण

		अगर (!phy[i])
			जारी;

		link[i] = device_link_add(dev, &phy[i]->dev, DL_FLAG_STATELESS);
		अगर (!link[i]) अणु
			ret = -EINVAL;
			जाओ err_link;
		पूर्ण
	पूर्ण

	ks_pcie->np = np;
	ks_pcie->pci = pci;
	ks_pcie->link = link;
	ks_pcie->num_lanes = num_lanes;
	ks_pcie->phy = phy;

	gpiod = devm_gpiod_get_optional(dev, "reset",
					GPIOD_OUT_LOW);
	अगर (IS_ERR(gpiod)) अणु
		ret = PTR_ERR(gpiod);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get reset GPIO\n");
		जाओ err_link;
	पूर्ण

	ret = ks_pcie_enable_phy(ks_pcie);
	अगर (ret) अणु
		dev_err(dev, "failed to enable phy\n");
		जाओ err_link;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ks_pcie);
	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed\n");
		जाओ err_get_sync;
	पूर्ण

	अगर (pci->version >= 0x480A)
		ret = ks_pcie_am654_set_mode(dev, mode);
	अन्यथा
		ret = ks_pcie_set_mode(dev);
	अगर (ret < 0)
		जाओ err_get_sync;

	चयन (mode) अणु
	हाल DW_PCIE_RC_TYPE:
		अगर (!IS_ENABLED(CONFIG_PCI_KEYSTONE_HOST)) अणु
			ret = -ENODEV;
			जाओ err_get_sync;
		पूर्ण

		ret = of_property_पढ़ो_u32(np, "num-viewport", &num_viewport);
		अगर (ret < 0) अणु
			dev_err(dev, "unable to read *num-viewport* property\n");
			जाओ err_get_sync;
		पूर्ण

		/*
		 * "Power Sequencing and Reset Signal Timings" table in
		 * PCI EXPRESS CARD ELECTROMECHANICAL SPECIFICATION, REV. 2.0
		 * indicates PERST# should be deनिश्चितed after minimum of 100us
		 * once REFCLK is stable. The REFCLK to the connector in RC
		 * mode is selected जबतक enabling the PHY. So deनिश्चित PERST#
		 * after 100 us.
		 */
		अगर (gpiod) अणु
			usleep_range(100, 200);
			gpiod_set_value_cansleep(gpiod, 1);
		पूर्ण

		ks_pcie->num_viewport = num_viewport;
		pci->pp.ops = host_ops;
		ret = dw_pcie_host_init(&pci->pp);
		अगर (ret < 0)
			जाओ err_get_sync;
		अवरोध;
	हाल DW_PCIE_EP_TYPE:
		अगर (!IS_ENABLED(CONFIG_PCI_KEYSTONE_EP)) अणु
			ret = -ENODEV;
			जाओ err_get_sync;
		पूर्ण

		pci->ep.ops = ep_ops;
		ret = dw_pcie_ep_init(&pci->ep);
		अगर (ret < 0)
			जाओ err_get_sync;
		अवरोध;
	शेष:
		dev_err(dev, "INVALID device type %d\n", mode);
	पूर्ण

	ks_pcie_enable_error_irq(ks_pcie);

	वापस 0;

err_get_sync:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);
	ks_pcie_disable_phy(ks_pcie);

err_link:
	जबतक (--i >= 0 && link[i])
		device_link_del(link[i]);

	वापस ret;
पूर्ण

अटल पूर्णांक __निकास ks_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा keystone_pcie *ks_pcie = platक्रमm_get_drvdata(pdev);
	काष्ठा device_link **link = ks_pcie->link;
	पूर्णांक num_lanes = ks_pcie->num_lanes;
	काष्ठा device *dev = &pdev->dev;

	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);
	ks_pcie_disable_phy(ks_pcie);
	जबतक (num_lanes--)
		device_link_del(link[num_lanes]);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ks_pcie_driver __refdata = अणु
	.probe  = ks_pcie_probe,
	.हटाओ = __निकास_p(ks_pcie_हटाओ),
	.driver = अणु
		.name	= "keystone-pcie",
		.of_match_table = of_match_ptr(ks_pcie_of_match),
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ks_pcie_driver);
