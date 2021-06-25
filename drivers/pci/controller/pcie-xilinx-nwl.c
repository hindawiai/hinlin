<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCIe host controller driver क्रम NWL PCIe Bridge
 * Based on pcie-xilinx.c, pci-tegra.c
 *
 * (C) Copyright 2014 - 2015, Xilinx, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irqchip/chained_irq.h>

#समावेश "../pci.h"

/* Bridge core config रेजिस्टरs */
#घोषणा BRCFG_PCIE_RX0			0x00000000
#घोषणा BRCFG_PCIE_RX1			0x00000004
#घोषणा BRCFG_INTERRUPT			0x00000010
#घोषणा BRCFG_PCIE_RX_MSG_FILTER	0x00000020

/* Egress - Bridge translation रेजिस्टरs */
#घोषणा E_BREG_CAPABILITIES		0x00000200
#घोषणा E_BREG_CONTROL			0x00000208
#घोषणा E_BREG_BASE_LO			0x00000210
#घोषणा E_BREG_BASE_HI			0x00000214
#घोषणा E_ECAM_CAPABILITIES		0x00000220
#घोषणा E_ECAM_CONTROL			0x00000228
#घोषणा E_ECAM_BASE_LO			0x00000230
#घोषणा E_ECAM_BASE_HI			0x00000234

/* Ingress - address translations */
#घोषणा I_MSII_CAPABILITIES		0x00000300
#घोषणा I_MSII_CONTROL			0x00000308
#घोषणा I_MSII_BASE_LO			0x00000310
#घोषणा I_MSII_BASE_HI			0x00000314

#घोषणा I_ISUB_CONTROL			0x000003E8
#घोषणा SET_ISUB_CONTROL		BIT(0)
/* Rxed msg fअगरo  - Interrupt status रेजिस्टरs */
#घोषणा MSGF_MISC_STATUS		0x00000400
#घोषणा MSGF_MISC_MASK			0x00000404
#घोषणा MSGF_LEG_STATUS			0x00000420
#घोषणा MSGF_LEG_MASK			0x00000424
#घोषणा MSGF_MSI_STATUS_LO		0x00000440
#घोषणा MSGF_MSI_STATUS_HI		0x00000444
#घोषणा MSGF_MSI_MASK_LO		0x00000448
#घोषणा MSGF_MSI_MASK_HI		0x0000044C

/* Msg filter mask bits */
#घोषणा CFG_ENABLE_PM_MSG_FWD		BIT(1)
#घोषणा CFG_ENABLE_INT_MSG_FWD		BIT(2)
#घोषणा CFG_ENABLE_ERR_MSG_FWD		BIT(3)
#घोषणा CFG_ENABLE_MSG_FILTER_MASK	(CFG_ENABLE_PM_MSG_FWD | \
					CFG_ENABLE_INT_MSG_FWD | \
					CFG_ENABLE_ERR_MSG_FWD)

/* Misc पूर्णांकerrupt status mask bits */
#घोषणा MSGF_MISC_SR_RXMSG_AVAIL	BIT(0)
#घोषणा MSGF_MISC_SR_RXMSG_OVER		BIT(1)
#घोषणा MSGF_MISC_SR_SLAVE_ERR		BIT(4)
#घोषणा MSGF_MISC_SR_MASTER_ERR		BIT(5)
#घोषणा MSGF_MISC_SR_I_ADDR_ERR		BIT(6)
#घोषणा MSGF_MISC_SR_E_ADDR_ERR		BIT(7)
#घोषणा MSGF_MISC_SR_FATAL_AER		BIT(16)
#घोषणा MSGF_MISC_SR_NON_FATAL_AER	BIT(17)
#घोषणा MSGF_MISC_SR_CORR_AER		BIT(18)
#घोषणा MSGF_MISC_SR_UR_DETECT		BIT(20)
#घोषणा MSGF_MISC_SR_NON_FATAL_DEV	BIT(22)
#घोषणा MSGF_MISC_SR_FATAL_DEV		BIT(23)
#घोषणा MSGF_MISC_SR_LINK_DOWN		BIT(24)
#घोषणा MSGF_MSIC_SR_LINK_AUTO_BWIDTH	BIT(25)
#घोषणा MSGF_MSIC_SR_LINK_BWIDTH	BIT(26)

#घोषणा MSGF_MISC_SR_MASKALL		(MSGF_MISC_SR_RXMSG_AVAIL | \
					MSGF_MISC_SR_RXMSG_OVER | \
					MSGF_MISC_SR_SLAVE_ERR | \
					MSGF_MISC_SR_MASTER_ERR | \
					MSGF_MISC_SR_I_ADDR_ERR | \
					MSGF_MISC_SR_E_ADDR_ERR | \
					MSGF_MISC_SR_FATAL_AER | \
					MSGF_MISC_SR_NON_FATAL_AER | \
					MSGF_MISC_SR_CORR_AER | \
					MSGF_MISC_SR_UR_DETECT | \
					MSGF_MISC_SR_NON_FATAL_DEV | \
					MSGF_MISC_SR_FATAL_DEV | \
					MSGF_MISC_SR_LINK_DOWN | \
					MSGF_MSIC_SR_LINK_AUTO_BWIDTH | \
					MSGF_MSIC_SR_LINK_BWIDTH)

/* Legacy पूर्णांकerrupt status mask bits */
#घोषणा MSGF_LEG_SR_INTA		BIT(0)
#घोषणा MSGF_LEG_SR_INTB		BIT(1)
#घोषणा MSGF_LEG_SR_INTC		BIT(2)
#घोषणा MSGF_LEG_SR_INTD		BIT(3)
#घोषणा MSGF_LEG_SR_MASKALL		(MSGF_LEG_SR_INTA | MSGF_LEG_SR_INTB | \
					MSGF_LEG_SR_INTC | MSGF_LEG_SR_INTD)

/* MSI पूर्णांकerrupt status mask bits */
#घोषणा MSGF_MSI_SR_LO_MASK		GENMASK(31, 0)
#घोषणा MSGF_MSI_SR_HI_MASK		GENMASK(31, 0)

#घोषणा MSII_PRESENT			BIT(0)
#घोषणा MSII_ENABLE			BIT(0)
#घोषणा MSII_STATUS_ENABLE		BIT(15)

/* Bridge config पूर्णांकerrupt mask */
#घोषणा BRCFG_INTERRUPT_MASK		BIT(0)
#घोषणा BREG_PRESENT			BIT(0)
#घोषणा BREG_ENABLE			BIT(0)
#घोषणा BREG_ENABLE_FORCE		BIT(1)

/* E_ECAM status mask bits */
#घोषणा E_ECAM_PRESENT			BIT(0)
#घोषणा E_ECAM_CR_ENABLE		BIT(0)
#घोषणा E_ECAM_SIZE_LOC			GENMASK(20, 16)
#घोषणा E_ECAM_SIZE_SHIFT		16
#घोषणा NWL_ECAM_VALUE_DEFAULT		12

#घोषणा CFG_DMA_REG_BAR			GENMASK(2, 0)
#घोषणा CFG_PCIE_CACHE			GENMASK(7, 0)

#घोषणा INT_PCI_MSI_NR			(2 * 32)

/* Readin the PS_LINKUP */
#घोषणा PS_LINKUP_OFFSET		0x00000238
#घोषणा PCIE_PHY_LINKUP_BIT		BIT(0)
#घोषणा PHY_RDY_LINKUP_BIT		BIT(1)

/* Parameters क्रम the रुकोing क्रम link up routine */
#घोषणा LINK_WAIT_MAX_RETRIES          10
#घोषणा LINK_WAIT_USLEEP_MIN           90000
#घोषणा LINK_WAIT_USLEEP_MAX           100000

काष्ठा nwl_msi अणु			/* MSI inक्रमmation */
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	अचिन्हित दीर्घ *biपंचांगap;
	काष्ठा irq_करोमुख्य *dev_करोमुख्य;
	काष्ठा mutex lock;		/* protect biपंचांगap variable */
	पूर्णांक irq_msi0;
	पूर्णांक irq_msi1;
पूर्ण;

काष्ठा nwl_pcie अणु
	काष्ठा device *dev;
	व्योम __iomem *breg_base;
	व्योम __iomem *pcireg_base;
	व्योम __iomem *ecam_base;
	phys_addr_t phys_breg_base;	/* Physical Bridge Register Base */
	phys_addr_t phys_pcie_reg_base;	/* Physical PCIe Controller Base */
	phys_addr_t phys_ecam_base;	/* Physical Configuration Base */
	u32 breg_size;
	u32 pcie_reg_size;
	u32 ecam_size;
	पूर्णांक irq_पूर्णांकx;
	पूर्णांक irq_misc;
	u32 ecam_value;
	u8 last_busno;
	काष्ठा nwl_msi msi;
	काष्ठा irq_करोमुख्य *legacy_irq_करोमुख्य;
	raw_spinlock_t leg_mask_lock;
पूर्ण;

अटल अंतरभूत u32 nwl_bridge_पढ़ोl(काष्ठा nwl_pcie *pcie, u32 off)
अणु
	वापस पढ़ोl(pcie->breg_base + off);
पूर्ण

अटल अंतरभूत व्योम nwl_bridge_ग_लिखोl(काष्ठा nwl_pcie *pcie, u32 val, u32 off)
अणु
	ग_लिखोl(val, pcie->breg_base + off);
पूर्ण

अटल bool nwl_pcie_link_up(काष्ठा nwl_pcie *pcie)
अणु
	अगर (पढ़ोl(pcie->pcireg_base + PS_LINKUP_OFFSET) & PCIE_PHY_LINKUP_BIT)
		वापस true;
	वापस false;
पूर्ण

अटल bool nwl_phy_link_up(काष्ठा nwl_pcie *pcie)
अणु
	अगर (पढ़ोl(pcie->pcireg_base + PS_LINKUP_OFFSET) & PHY_RDY_LINKUP_BIT)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक nwl_रुको_क्रम_link(काष्ठा nwl_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	पूर्णांक retries;

	/* check अगर the link is up or not */
	क्रम (retries = 0; retries < LINK_WAIT_MAX_RETRIES; retries++) अणु
		अगर (nwl_phy_link_up(pcie))
			वापस 0;
		usleep_range(LINK_WAIT_USLEEP_MIN, LINK_WAIT_USLEEP_MAX);
	पूर्ण

	dev_err(dev, "PHY link never came up\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल bool nwl_pcie_valid_device(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा nwl_pcie *pcie = bus->sysdata;

	/* Check link beक्रमe accessing करोwnstream ports */
	अगर (!pci_is_root_bus(bus)) अणु
		अगर (!nwl_pcie_link_up(pcie))
			वापस false;
	पूर्ण अन्यथा अगर (devfn > 0)
		/* Only one device करोwn on each root port */
		वापस false;

	वापस true;
पूर्ण

/**
 * nwl_pcie_map_bus - Get configuration base
 *
 * @bus: Bus काष्ठाure of current bus
 * @devfn: Device/function
 * @where: Offset from base
 *
 * Return: Base address of the configuration space needed to be
 *	   accessed.
 */
अटल व्योम __iomem *nwl_pcie_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				      पूर्णांक where)
अणु
	काष्ठा nwl_pcie *pcie = bus->sysdata;

	अगर (!nwl_pcie_valid_device(bus, devfn))
		वापस शून्य;

	वापस pcie->ecam_base + PCIE_ECAM_OFFSET(bus->number, devfn, where);
पूर्ण

/* PCIe operations */
अटल काष्ठा pci_ops nwl_pcie_ops = अणु
	.map_bus = nwl_pcie_map_bus,
	.पढ़ो  = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

अटल irqवापस_t nwl_pcie_misc_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nwl_pcie *pcie = data;
	काष्ठा device *dev = pcie->dev;
	u32 misc_stat;

	/* Checking क्रम misc पूर्णांकerrupts */
	misc_stat = nwl_bridge_पढ़ोl(pcie, MSGF_MISC_STATUS) &
				     MSGF_MISC_SR_MASKALL;
	अगर (!misc_stat)
		वापस IRQ_NONE;

	अगर (misc_stat & MSGF_MISC_SR_RXMSG_OVER)
		dev_err(dev, "Received Message FIFO Overflow\n");

	अगर (misc_stat & MSGF_MISC_SR_SLAVE_ERR)
		dev_err(dev, "Slave error\n");

	अगर (misc_stat & MSGF_MISC_SR_MASTER_ERR)
		dev_err(dev, "Master error\n");

	अगर (misc_stat & MSGF_MISC_SR_I_ADDR_ERR)
		dev_err(dev, "In Misc Ingress address translation error\n");

	अगर (misc_stat & MSGF_MISC_SR_E_ADDR_ERR)
		dev_err(dev, "In Misc Egress address translation error\n");

	अगर (misc_stat & MSGF_MISC_SR_FATAL_AER)
		dev_err(dev, "Fatal Error in AER Capability\n");

	अगर (misc_stat & MSGF_MISC_SR_NON_FATAL_AER)
		dev_err(dev, "Non-Fatal Error in AER Capability\n");

	अगर (misc_stat & MSGF_MISC_SR_CORR_AER)
		dev_err(dev, "Correctable Error in AER Capability\n");

	अगर (misc_stat & MSGF_MISC_SR_UR_DETECT)
		dev_err(dev, "Unsupported request Detected\n");

	अगर (misc_stat & MSGF_MISC_SR_NON_FATAL_DEV)
		dev_err(dev, "Non-Fatal Error Detected\n");

	अगर (misc_stat & MSGF_MISC_SR_FATAL_DEV)
		dev_err(dev, "Fatal Error Detected\n");

	अगर (misc_stat & MSGF_MSIC_SR_LINK_AUTO_BWIDTH)
		dev_info(dev, "Link Autonomous Bandwidth Management Status bit set\n");

	अगर (misc_stat & MSGF_MSIC_SR_LINK_BWIDTH)
		dev_info(dev, "Link Bandwidth Management Status bit set\n");

	/* Clear misc पूर्णांकerrupt status */
	nwl_bridge_ग_लिखोl(pcie, misc_stat, MSGF_MISC_STATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम nwl_pcie_leg_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा nwl_pcie *pcie;
	अचिन्हित दीर्घ status;
	u32 bit;
	u32 virq;

	chained_irq_enter(chip, desc);
	pcie = irq_desc_get_handler_data(desc);

	जबतक ((status = nwl_bridge_पढ़ोl(pcie, MSGF_LEG_STATUS) &
				MSGF_LEG_SR_MASKALL) != 0) अणु
		क्रम_each_set_bit(bit, &status, PCI_NUM_INTX) अणु
			virq = irq_find_mapping(pcie->legacy_irq_करोमुख्य, bit);
			अगर (virq)
				generic_handle_irq(virq);
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम nwl_pcie_handle_msi_irq(काष्ठा nwl_pcie *pcie, u32 status_reg)
अणु
	काष्ठा nwl_msi *msi;
	अचिन्हित दीर्घ status;
	u32 bit;
	u32 virq;

	msi = &pcie->msi;

	जबतक ((status = nwl_bridge_पढ़ोl(pcie, status_reg)) != 0) अणु
		क्रम_each_set_bit(bit, &status, 32) अणु
			nwl_bridge_ग_लिखोl(pcie, 1 << bit, status_reg);
			virq = irq_find_mapping(msi->dev_करोमुख्य, bit);
			अगर (virq)
				generic_handle_irq(virq);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nwl_pcie_msi_handler_high(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा nwl_pcie *pcie = irq_desc_get_handler_data(desc);

	chained_irq_enter(chip, desc);
	nwl_pcie_handle_msi_irq(pcie, MSGF_MSI_STATUS_HI);
	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम nwl_pcie_msi_handler_low(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा nwl_pcie *pcie = irq_desc_get_handler_data(desc);

	chained_irq_enter(chip, desc);
	nwl_pcie_handle_msi_irq(pcie, MSGF_MSI_STATUS_LO);
	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम nwl_mask_leg_irq(काष्ठा irq_data *data)
अणु
	काष्ठा nwl_pcie *pcie = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ flags;
	u32 mask;
	u32 val;

	mask = 1 << (data->hwirq - 1);
	raw_spin_lock_irqsave(&pcie->leg_mask_lock, flags);
	val = nwl_bridge_पढ़ोl(pcie, MSGF_LEG_MASK);
	nwl_bridge_ग_लिखोl(pcie, (val & (~mask)), MSGF_LEG_MASK);
	raw_spin_unlock_irqrestore(&pcie->leg_mask_lock, flags);
पूर्ण

अटल व्योम nwl_unmask_leg_irq(काष्ठा irq_data *data)
अणु
	काष्ठा nwl_pcie *pcie = irq_data_get_irq_chip_data(data);
	अचिन्हित दीर्घ flags;
	u32 mask;
	u32 val;

	mask = 1 << (data->hwirq - 1);
	raw_spin_lock_irqsave(&pcie->leg_mask_lock, flags);
	val = nwl_bridge_पढ़ोl(pcie, MSGF_LEG_MASK);
	nwl_bridge_ग_लिखोl(pcie, (val | mask), MSGF_LEG_MASK);
	raw_spin_unlock_irqrestore(&pcie->leg_mask_lock, flags);
पूर्ण

अटल काष्ठा irq_chip nwl_leg_irq_chip = अणु
	.name = "nwl_pcie:legacy",
	.irq_enable = nwl_unmask_leg_irq,
	.irq_disable = nwl_mask_leg_irq,
	.irq_mask = nwl_mask_leg_irq,
	.irq_unmask = nwl_unmask_leg_irq,
पूर्ण;

अटल पूर्णांक nwl_legacy_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
			  irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &nwl_leg_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);
	irq_set_status_flags(irq, IRQ_LEVEL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops legacy_करोमुख्य_ops = अणु
	.map = nwl_legacy_map,
	.xlate = pci_irqd_पूर्णांकx_xlate,
पूर्ण;

#अगर_घोषित CONFIG_PCI_MSI
अटल काष्ठा irq_chip nwl_msi_irq_chip = अणु
	.name = "nwl_pcie:msi",
	.irq_enable = pci_msi_unmask_irq,
	.irq_disable = pci_msi_mask_irq,
	.irq_mask = pci_msi_mask_irq,
	.irq_unmask = pci_msi_unmask_irq,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info nwl_msi_करोमुख्य_info = अणु
	.flags = (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		  MSI_FLAG_MULTI_PCI_MSI),
	.chip = &nwl_msi_irq_chip,
पूर्ण;
#पूर्ण_अगर

अटल व्योम nwl_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा nwl_pcie *pcie = irq_data_get_irq_chip_data(data);
	phys_addr_t msi_addr = pcie->phys_pcie_reg_base;

	msg->address_lo = lower_32_bits(msi_addr);
	msg->address_hi = upper_32_bits(msi_addr);
	msg->data = data->hwirq;
पूर्ण

अटल पूर्णांक nwl_msi_set_affinity(काष्ठा irq_data *irq_data,
				स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल काष्ठा irq_chip nwl_irq_chip = अणु
	.name = "Xilinx MSI",
	.irq_compose_msi_msg = nwl_compose_msi_msg,
	.irq_set_affinity = nwl_msi_set_affinity,
पूर्ण;

अटल पूर्णांक nwl_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा nwl_pcie *pcie = करोमुख्य->host_data;
	काष्ठा nwl_msi *msi = &pcie->msi;
	पूर्णांक bit;
	पूर्णांक i;

	mutex_lock(&msi->lock);
	bit = biपंचांगap_find_मुक्त_region(msi->biपंचांगap, INT_PCI_MSI_NR,
				      get_count_order(nr_irqs));
	अगर (bit < 0) अणु
		mutex_unlock(&msi->lock);
		वापस -ENOSPC;
	पूर्ण

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, bit + i, &nwl_irq_chip,
				करोमुख्य->host_data, handle_simple_irq,
				शून्य, शून्य);
	पूर्ण
	mutex_unlock(&msi->lock);
	वापस 0;
पूर्ण

अटल व्योम nwl_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
					अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा nwl_pcie *pcie = irq_data_get_irq_chip_data(data);
	काष्ठा nwl_msi *msi = &pcie->msi;

	mutex_lock(&msi->lock);
	biपंचांगap_release_region(msi->biपंचांगap, data->hwirq,
			      get_count_order(nr_irqs));
	mutex_unlock(&msi->lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops dev_msi_करोमुख्य_ops = अणु
	.alloc  = nwl_irq_करोमुख्य_alloc,
	.मुक्त   = nwl_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल पूर्णांक nwl_pcie_init_msi_irq_करोमुख्य(काष्ठा nwl_pcie *pcie)
अणु
#अगर_घोषित CONFIG_PCI_MSI
	काष्ठा device *dev = pcie->dev;
	काष्ठा fwnode_handle *fwnode = of_node_to_fwnode(dev->of_node);
	काष्ठा nwl_msi *msi = &pcie->msi;

	msi->dev_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, INT_PCI_MSI_NR,
						&dev_msi_करोमुख्य_ops, pcie);
	अगर (!msi->dev_करोमुख्य) अणु
		dev_err(dev, "failed to create dev IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण
	msi->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode,
						    &nwl_msi_करोमुख्य_info,
						    msi->dev_करोमुख्य);
	अगर (!msi->msi_करोमुख्य) अणु
		dev_err(dev, "failed to create msi IRQ domain\n");
		irq_करोमुख्य_हटाओ(msi->dev_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक nwl_pcie_init_irq_करोमुख्य(काष्ठा nwl_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *legacy_पूर्णांकc_node;

	legacy_पूर्णांकc_node = of_get_next_child(node, शून्य);
	अगर (!legacy_पूर्णांकc_node) अणु
		dev_err(dev, "No legacy intc node found\n");
		वापस -EINVAL;
	पूर्ण

	pcie->legacy_irq_करोमुख्य = irq_करोमुख्य_add_linear(legacy_पूर्णांकc_node,
							PCI_NUM_INTX,
							&legacy_करोमुख्य_ops,
							pcie);
	of_node_put(legacy_पूर्णांकc_node);
	अगर (!pcie->legacy_irq_करोमुख्य) अणु
		dev_err(dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	raw_spin_lock_init(&pcie->leg_mask_lock);
	nwl_pcie_init_msi_irq_करोमुख्य(pcie);
	वापस 0;
पूर्ण

अटल पूर्णांक nwl_pcie_enable_msi(काष्ठा nwl_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा nwl_msi *msi = &pcie->msi;
	अचिन्हित दीर्घ base;
	पूर्णांक ret;
	पूर्णांक size = BITS_TO_LONGS(INT_PCI_MSI_NR) * माप(दीर्घ);

	mutex_init(&msi->lock);

	msi->biपंचांगap = kzalloc(size, GFP_KERNEL);
	अगर (!msi->biपंचांगap)
		वापस -ENOMEM;

	/* Get msi_1 IRQ number */
	msi->irq_msi1 = platक्रमm_get_irq_byname(pdev, "msi1");
	अगर (msi->irq_msi1 < 0) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	irq_set_chained_handler_and_data(msi->irq_msi1,
					 nwl_pcie_msi_handler_high, pcie);

	/* Get msi_0 IRQ number */
	msi->irq_msi0 = platक्रमm_get_irq_byname(pdev, "msi0");
	अगर (msi->irq_msi0 < 0) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	irq_set_chained_handler_and_data(msi->irq_msi0,
					 nwl_pcie_msi_handler_low, pcie);

	/* Check क्रम msii_present bit */
	ret = nwl_bridge_पढ़ोl(pcie, I_MSII_CAPABILITIES) & MSII_PRESENT;
	अगर (!ret) अणु
		dev_err(dev, "MSI not present\n");
		ret = -EIO;
		जाओ err;
	पूर्ण

	/* Enable MSII */
	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, I_MSII_CONTROL) |
			  MSII_ENABLE, I_MSII_CONTROL);

	/* Enable MSII status */
	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, I_MSII_CONTROL) |
			  MSII_STATUS_ENABLE, I_MSII_CONTROL);

	/* setup AFI/FPCI range */
	base = pcie->phys_pcie_reg_base;
	nwl_bridge_ग_लिखोl(pcie, lower_32_bits(base), I_MSII_BASE_LO);
	nwl_bridge_ग_लिखोl(pcie, upper_32_bits(base), I_MSII_BASE_HI);

	/*
	 * For high range MSI पूर्णांकerrupts: disable, clear any pending,
	 * and enable
	 */
	nwl_bridge_ग_लिखोl(pcie, 0, MSGF_MSI_MASK_HI);

	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie,  MSGF_MSI_STATUS_HI) &
			  MSGF_MSI_SR_HI_MASK, MSGF_MSI_STATUS_HI);

	nwl_bridge_ग_लिखोl(pcie, MSGF_MSI_SR_HI_MASK, MSGF_MSI_MASK_HI);

	/*
	 * For low range MSI पूर्णांकerrupts: disable, clear any pending,
	 * and enable
	 */
	nwl_bridge_ग_लिखोl(pcie, 0, MSGF_MSI_MASK_LO);

	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, MSGF_MSI_STATUS_LO) &
			  MSGF_MSI_SR_LO_MASK, MSGF_MSI_STATUS_LO);

	nwl_bridge_ग_लिखोl(pcie, MSGF_MSI_SR_LO_MASK, MSGF_MSI_MASK_LO);

	वापस 0;
err:
	kमुक्त(msi->biपंचांगap);
	msi->biपंचांगap = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक nwl_pcie_bridge_init(काष्ठा nwl_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	u32 breg_val, ecam_val, first_busno = 0;
	पूर्णांक err;

	breg_val = nwl_bridge_पढ़ोl(pcie, E_BREG_CAPABILITIES) & BREG_PRESENT;
	अगर (!breg_val) अणु
		dev_err(dev, "BREG is not present\n");
		वापस breg_val;
	पूर्ण

	/* Write bridge_off to breg base */
	nwl_bridge_ग_लिखोl(pcie, lower_32_bits(pcie->phys_breg_base),
			  E_BREG_BASE_LO);
	nwl_bridge_ग_लिखोl(pcie, upper_32_bits(pcie->phys_breg_base),
			  E_BREG_BASE_HI);

	/* Enable BREG */
	nwl_bridge_ग_लिखोl(pcie, ~BREG_ENABLE_FORCE & BREG_ENABLE,
			  E_BREG_CONTROL);

	/* Disable DMA channel रेजिस्टरs */
	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, BRCFG_PCIE_RX0) |
			  CFG_DMA_REG_BAR, BRCFG_PCIE_RX0);

	/* Enable Ingress subtractive decode translation */
	nwl_bridge_ग_लिखोl(pcie, SET_ISUB_CONTROL, I_ISUB_CONTROL);

	/* Enable msg filtering details */
	nwl_bridge_ग_लिखोl(pcie, CFG_ENABLE_MSG_FILTER_MASK,
			  BRCFG_PCIE_RX_MSG_FILTER);

	/* This routes the PCIe DMA traffic to go through CCI path */
	अगर (of_dma_is_coherent(dev->of_node))
		nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, BRCFG_PCIE_RX1) |
				  CFG_PCIE_CACHE, BRCFG_PCIE_RX1);

	err = nwl_रुको_क्रम_link(pcie);
	अगर (err)
		वापस err;

	ecam_val = nwl_bridge_पढ़ोl(pcie, E_ECAM_CAPABILITIES) & E_ECAM_PRESENT;
	अगर (!ecam_val) अणु
		dev_err(dev, "ECAM is not present\n");
		वापस ecam_val;
	पूर्ण

	/* Enable ECAM */
	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, E_ECAM_CONTROL) |
			  E_ECAM_CR_ENABLE, E_ECAM_CONTROL);

	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, E_ECAM_CONTROL) |
			  (pcie->ecam_value << E_ECAM_SIZE_SHIFT),
			  E_ECAM_CONTROL);

	nwl_bridge_ग_लिखोl(pcie, lower_32_bits(pcie->phys_ecam_base),
			  E_ECAM_BASE_LO);
	nwl_bridge_ग_लिखोl(pcie, upper_32_bits(pcie->phys_ecam_base),
			  E_ECAM_BASE_HI);

	/* Get bus range */
	ecam_val = nwl_bridge_पढ़ोl(pcie, E_ECAM_CONTROL);
	pcie->last_busno = (ecam_val & E_ECAM_SIZE_LOC) >> E_ECAM_SIZE_SHIFT;
	/* Write primary, secondary and subordinate bus numbers */
	ecam_val = first_busno;
	ecam_val |= (first_busno + 1) << 8;
	ecam_val |= (pcie->last_busno << E_ECAM_SIZE_SHIFT);
	ग_लिखोl(ecam_val, (pcie->ecam_base + PCI_PRIMARY_BUS));

	अगर (nwl_pcie_link_up(pcie))
		dev_info(dev, "Link is UP\n");
	अन्यथा
		dev_info(dev, "Link is DOWN\n");

	/* Get misc IRQ number */
	pcie->irq_misc = platक्रमm_get_irq_byname(pdev, "misc");
	अगर (pcie->irq_misc < 0)
		वापस -EINVAL;

	err = devm_request_irq(dev, pcie->irq_misc,
			       nwl_pcie_misc_handler, IRQF_SHARED,
			       "nwl_pcie:misc", pcie);
	अगर (err) अणु
		dev_err(dev, "fail to register misc IRQ#%d\n",
			pcie->irq_misc);
		वापस err;
	पूर्ण

	/* Disable all misc पूर्णांकerrupts */
	nwl_bridge_ग_लिखोl(pcie, (u32)~MSGF_MISC_SR_MASKALL, MSGF_MISC_MASK);

	/* Clear pending misc पूर्णांकerrupts */
	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, MSGF_MISC_STATUS) &
			  MSGF_MISC_SR_MASKALL, MSGF_MISC_STATUS);

	/* Enable all misc पूर्णांकerrupts */
	nwl_bridge_ग_लिखोl(pcie, MSGF_MISC_SR_MASKALL, MSGF_MISC_MASK);


	/* Disable all legacy पूर्णांकerrupts */
	nwl_bridge_ग_लिखोl(pcie, (u32)~MSGF_LEG_SR_MASKALL, MSGF_LEG_MASK);

	/* Clear pending legacy पूर्णांकerrupts */
	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, MSGF_LEG_STATUS) &
			  MSGF_LEG_SR_MASKALL, MSGF_LEG_STATUS);

	/* Enable all legacy पूर्णांकerrupts */
	nwl_bridge_ग_लिखोl(pcie, MSGF_LEG_SR_MASKALL, MSGF_LEG_MASK);

	/* Enable the bridge config पूर्णांकerrupt */
	nwl_bridge_ग_लिखोl(pcie, nwl_bridge_पढ़ोl(pcie, BRCFG_INTERRUPT) |
			  BRCFG_INTERRUPT_MASK, BRCFG_INTERRUPT);

	वापस 0;
पूर्ण

अटल पूर्णांक nwl_pcie_parse_dt(काष्ठा nwl_pcie *pcie,
			     काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा resource *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "breg");
	pcie->breg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(pcie->breg_base))
		वापस PTR_ERR(pcie->breg_base);
	pcie->phys_breg_base = res->start;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pcireg");
	pcie->pcireg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(pcie->pcireg_base))
		वापस PTR_ERR(pcie->pcireg_base);
	pcie->phys_pcie_reg_base = res->start;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cfg");
	pcie->ecam_base = devm_pci_remap_cfg_resource(dev, res);
	अगर (IS_ERR(pcie->ecam_base))
		वापस PTR_ERR(pcie->ecam_base);
	pcie->phys_ecam_base = res->start;

	/* Get पूर्णांकx IRQ number */
	pcie->irq_पूर्णांकx = platक्रमm_get_irq_byname(pdev, "intx");
	अगर (pcie->irq_पूर्णांकx < 0)
		वापस pcie->irq_पूर्णांकx;

	irq_set_chained_handler_and_data(pcie->irq_पूर्णांकx,
					 nwl_pcie_leg_handler, pcie);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nwl_pcie_of_match[] = अणु
	अणु .compatible = "xlnx,nwl-pcie-2.11", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक nwl_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा nwl_pcie *pcie;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक err;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*pcie));
	अगर (!bridge)
		वापस -ENODEV;

	pcie = pci_host_bridge_priv(bridge);

	pcie->dev = dev;
	pcie->ecam_value = NWL_ECAM_VALUE_DEFAULT;

	err = nwl_pcie_parse_dt(pcie, pdev);
	अगर (err) अणु
		dev_err(dev, "Parsing DT failed\n");
		वापस err;
	पूर्ण

	err = nwl_pcie_bridge_init(pcie);
	अगर (err) अणु
		dev_err(dev, "HW Initialization failed\n");
		वापस err;
	पूर्ण

	err = nwl_pcie_init_irq_करोमुख्य(pcie);
	अगर (err) अणु
		dev_err(dev, "Failed creating IRQ Domain\n");
		वापस err;
	पूर्ण

	bridge->sysdata = pcie;
	bridge->ops = &nwl_pcie_ops;

	अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
		err = nwl_pcie_enable_msi(pcie);
		अगर (err < 0) अणु
			dev_err(dev, "failed to enable MSI support: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस pci_host_probe(bridge);
पूर्ण

अटल काष्ठा platक्रमm_driver nwl_pcie_driver = अणु
	.driver = अणु
		.name = "nwl-pcie",
		.suppress_bind_attrs = true,
		.of_match_table = nwl_pcie_of_match,
	पूर्ण,
	.probe = nwl_pcie_probe,
पूर्ण;
builtin_platक्रमm_driver(nwl_pcie_driver);
