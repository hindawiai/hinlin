<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Rockchip AXI PCIe host controller driver
 *
 * Copyright (c) 2016 Rockchip, Inc.
 *
 * Author: Shawn Lin <shawn.lin@rock-chips.com>
 *         Wenrui Li <wenrui.li@rock-chips.com>
 *
 * Bits taken from Synopsys DesignWare Host controller driver and
 * ARM PCI Host generic driver.
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/regmap.h>

#समावेश "../pci.h"
#समावेश "pcie-rockchip.h"

अटल व्योम rockchip_pcie_enable_bw_पूर्णांक(काष्ठा rockchip_pcie *rockchip)
अणु
	u32 status;

	status = rockchip_pcie_पढ़ो(rockchip, PCIE_RC_CONFIG_LCS);
	status |= (PCI_EXP_LNKCTL_LBMIE | PCI_EXP_LNKCTL_LABIE);
	rockchip_pcie_ग_लिखो(rockchip, status, PCIE_RC_CONFIG_LCS);
पूर्ण

अटल व्योम rockchip_pcie_clr_bw_पूर्णांक(काष्ठा rockchip_pcie *rockchip)
अणु
	u32 status;

	status = rockchip_pcie_पढ़ो(rockchip, PCIE_RC_CONFIG_LCS);
	status |= (PCI_EXP_LNKSTA_LBMS | PCI_EXP_LNKSTA_LABS) << 16;
	rockchip_pcie_ग_लिखो(rockchip, status, PCIE_RC_CONFIG_LCS);
पूर्ण

अटल व्योम rockchip_pcie_update_txcredit_mui(काष्ठा rockchip_pcie *rockchip)
अणु
	u32 val;

	/* Update Tx credit maximum update पूर्णांकerval */
	val = rockchip_pcie_पढ़ो(rockchip, PCIE_CORE_TXCREDIT_CFG1);
	val &= ~PCIE_CORE_TXCREDIT_CFG1_MUI_MASK;
	val |= PCIE_CORE_TXCREDIT_CFG1_MUI_ENCODE(24000);	/* ns */
	rockchip_pcie_ग_लिखो(rockchip, val, PCIE_CORE_TXCREDIT_CFG1);
पूर्ण

अटल पूर्णांक rockchip_pcie_valid_device(काष्ठा rockchip_pcie *rockchip,
				      काष्ठा pci_bus *bus, पूर्णांक dev)
अणु
	/*
	 * Access only one slot on each root port.
	 * Do not पढ़ो more than one device on the bus directly attached
	 * to RC's करोwnstream side.
	 */
	अगर (pci_is_root_bus(bus) || pci_is_root_bus(bus->parent))
		वापस dev == 0;

	वापस 1;
पूर्ण

अटल u8 rockchip_pcie_lane_map(काष्ठा rockchip_pcie *rockchip)
अणु
	u32 val;
	u8 map;

	अगर (rockchip->legacy_phy)
		वापस GENMASK(MAX_LANE_NUM - 1, 0);

	val = rockchip_pcie_पढ़ो(rockchip, PCIE_CORE_LANE_MAP);
	map = val & PCIE_CORE_LANE_MAP_MASK;

	/* The link may be using a reverse-indexed mapping. */
	अगर (val & PCIE_CORE_LANE_MAP_REVERSE)
		map = bitrev8(map) >> 4;

	वापस map;
पूर्ण

अटल पूर्णांक rockchip_pcie_rd_own_conf(काष्ठा rockchip_pcie *rockchip,
				     पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	व्योम __iomem *addr;

	addr = rockchip->apb_base + PCIE_RC_CONFIG_NORMAL_BASE + where;

	अगर (!IS_ALIGNED((uपूर्णांकptr_t)addr, size)) अणु
		*val = 0;
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	अगर (size == 4) अणु
		*val = पढ़ोl(addr);
	पूर्ण अन्यथा अगर (size == 2) अणु
		*val = पढ़ोw(addr);
	पूर्ण अन्यथा अगर (size == 1) अणु
		*val = पढ़ोb(addr);
	पूर्ण अन्यथा अणु
		*val = 0;
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rockchip_pcie_wr_own_conf(काष्ठा rockchip_pcie *rockchip,
				     पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 mask, पंचांगp, offset;
	व्योम __iomem *addr;

	offset = where & ~0x3;
	addr = rockchip->apb_base + PCIE_RC_CONFIG_NORMAL_BASE + offset;

	अगर (size == 4) अणु
		ग_लिखोl(val, addr);
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	mask = ~(((1 << (size * 8)) - 1) << ((where & 0x3) * 8));

	/*
	 * N.B. This पढ़ो/modअगरy/ग_लिखो isn't safe in general because it can
	 * corrupt RW1C bits in adjacent रेजिस्टरs.  But the hardware
	 * करोesn't support smaller ग_लिखोs.
	 */
	पंचांगp = पढ़ोl(addr) & mask;
	पंचांगp |= val << ((where & 0x3) * 8);
	ग_लिखोl(पंचांगp, addr);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rockchip_pcie_rd_other_conf(काष्ठा rockchip_pcie *rockchip,
				       काष्ठा pci_bus *bus, u32 devfn,
				       पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	व्योम __iomem *addr;

	addr = rockchip->reg_base + PCIE_ECAM_OFFSET(bus->number, devfn, where);

	अगर (!IS_ALIGNED((uपूर्णांकptr_t)addr, size)) अणु
		*val = 0;
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	अगर (pci_is_root_bus(bus->parent))
		rockchip_pcie_cfg_configuration_accesses(rockchip,
						AXI_WRAPPER_TYPE0_CFG);
	अन्यथा
		rockchip_pcie_cfg_configuration_accesses(rockchip,
						AXI_WRAPPER_TYPE1_CFG);

	अगर (size == 4) अणु
		*val = पढ़ोl(addr);
	पूर्ण अन्यथा अगर (size == 2) अणु
		*val = पढ़ोw(addr);
	पूर्ण अन्यथा अगर (size == 1) अणु
		*val = पढ़ोb(addr);
	पूर्ण अन्यथा अणु
		*val = 0;
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rockchip_pcie_wr_other_conf(काष्ठा rockchip_pcie *rockchip,
				       काष्ठा pci_bus *bus, u32 devfn,
				       पूर्णांक where, पूर्णांक size, u32 val)
अणु
	व्योम __iomem *addr;

	addr = rockchip->reg_base + PCIE_ECAM_OFFSET(bus->number, devfn, where);

	अगर (!IS_ALIGNED((uपूर्णांकptr_t)addr, size))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (pci_is_root_bus(bus->parent))
		rockchip_pcie_cfg_configuration_accesses(rockchip,
						AXI_WRAPPER_TYPE0_CFG);
	अन्यथा
		rockchip_pcie_cfg_configuration_accesses(rockchip,
						AXI_WRAPPER_TYPE1_CFG);

	अगर (size == 4)
		ग_लिखोl(val, addr);
	अन्यथा अगर (size == 2)
		ग_लिखोw(val, addr);
	अन्यथा अगर (size == 1)
		ग_लिखोb(val, addr);
	अन्यथा
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rockchip_pcie_rd_conf(काष्ठा pci_bus *bus, u32 devfn, पूर्णांक where,
				 पूर्णांक size, u32 *val)
अणु
	काष्ठा rockchip_pcie *rockchip = bus->sysdata;

	अगर (!rockchip_pcie_valid_device(rockchip, bus, PCI_SLOT(devfn))) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	अगर (pci_is_root_bus(bus))
		वापस rockchip_pcie_rd_own_conf(rockchip, where, size, val);

	वापस rockchip_pcie_rd_other_conf(rockchip, bus, devfn, where, size,
					   val);
पूर्ण

अटल पूर्णांक rockchip_pcie_wr_conf(काष्ठा pci_bus *bus, u32 devfn,
				 पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा rockchip_pcie *rockchip = bus->sysdata;

	अगर (!rockchip_pcie_valid_device(rockchip, bus, PCI_SLOT(devfn)))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (pci_is_root_bus(bus))
		वापस rockchip_pcie_wr_own_conf(rockchip, where, size, val);

	वापस rockchip_pcie_wr_other_conf(rockchip, bus, devfn, where, size,
					   val);
पूर्ण

अटल काष्ठा pci_ops rockchip_pcie_ops = अणु
	.पढ़ो = rockchip_pcie_rd_conf,
	.ग_लिखो = rockchip_pcie_wr_conf,
पूर्ण;

अटल व्योम rockchip_pcie_set_घातer_limit(काष्ठा rockchip_pcie *rockchip)
अणु
	पूर्णांक curr;
	u32 status, scale, घातer;

	अगर (IS_ERR(rockchip->vpcie3v3))
		वापस;

	/*
	 * Set RC's captured slot घातer limit and scale अगर
	 * vpcie3v3 available. The शेष values are both zero
	 * which means the software should set these two according
	 * to the actual घातer supply.
	 */
	curr = regulator_get_current_limit(rockchip->vpcie3v3);
	अगर (curr <= 0)
		वापस;

	scale = 3; /* 0.001x */
	curr = curr / 1000; /* convert to mA */
	घातer = (curr * 3300) / 1000; /* milliwatt */
	जबतक (घातer > PCIE_RC_CONFIG_DCR_CSPL_LIMIT) अणु
		अगर (!scale) अणु
			dev_warn(rockchip->dev, "invalid power supply\n");
			वापस;
		पूर्ण
		scale--;
		घातer = घातer / 10;
	पूर्ण

	status = rockchip_pcie_पढ़ो(rockchip, PCIE_RC_CONFIG_DCR);
	status |= (घातer << PCIE_RC_CONFIG_DCR_CSPL_SHIFT) |
		  (scale << PCIE_RC_CONFIG_DCR_CPLS_SHIFT);
	rockchip_pcie_ग_लिखो(rockchip, status, PCIE_RC_CONFIG_DCR);
पूर्ण

/**
 * rockchip_pcie_host_init_port - Initialize hardware
 * @rockchip: PCIe port inक्रमmation
 */
अटल पूर्णांक rockchip_pcie_host_init_port(काष्ठा rockchip_pcie *rockchip)
अणु
	काष्ठा device *dev = rockchip->dev;
	पूर्णांक err, i = MAX_LANE_NUM;
	u32 status;

	gpiod_set_value_cansleep(rockchip->ep_gpio, 0);

	err = rockchip_pcie_init_port(rockchip);
	अगर (err)
		वापस err;

	/* Fix the transmitted FTS count desired to निकास from L0s. */
	status = rockchip_pcie_पढ़ो(rockchip, PCIE_CORE_CTRL_PLC1);
	status = (status & ~PCIE_CORE_CTRL_PLC1_FTS_MASK) |
		 (PCIE_CORE_CTRL_PLC1_FTS_CNT << PCIE_CORE_CTRL_PLC1_FTS_SHIFT);
	rockchip_pcie_ग_लिखो(rockchip, status, PCIE_CORE_CTRL_PLC1);

	rockchip_pcie_set_घातer_limit(rockchip);

	/* Set RC's घड़ी architecture as common घड़ी */
	status = rockchip_pcie_पढ़ो(rockchip, PCIE_RC_CONFIG_LCS);
	status |= PCI_EXP_LNKSTA_SLC << 16;
	rockchip_pcie_ग_लिखो(rockchip, status, PCIE_RC_CONFIG_LCS);

	/* Set RC's RCB to 128 */
	status = rockchip_pcie_पढ़ो(rockchip, PCIE_RC_CONFIG_LCS);
	status |= PCI_EXP_LNKCTL_RCB;
	rockchip_pcie_ग_लिखो(rockchip, status, PCIE_RC_CONFIG_LCS);

	/* Enable Gen1 training */
	rockchip_pcie_ग_लिखो(rockchip, PCIE_CLIENT_LINK_TRAIN_ENABLE,
			    PCIE_CLIENT_CONFIG);

	gpiod_set_value_cansleep(rockchip->ep_gpio, 1);

	/* 500ms समयout value should be enough क्रम Gen1/2 training */
	err = पढ़ोl_poll_समयout(rockchip->apb_base + PCIE_CLIENT_BASIC_STATUS1,
				 status, PCIE_LINK_UP(status), 20,
				 500 * USEC_PER_MSEC);
	अगर (err) अणु
		dev_err(dev, "PCIe link training gen1 timeout!\n");
		जाओ err_घातer_off_phy;
	पूर्ण

	अगर (rockchip->link_gen == 2) अणु
		/*
		 * Enable retrain क्रम gen2. This should be configured only after
		 * gen1 finished.
		 */
		status = rockchip_pcie_पढ़ो(rockchip, PCIE_RC_CONFIG_LCS);
		status |= PCI_EXP_LNKCTL_RL;
		rockchip_pcie_ग_लिखो(rockchip, status, PCIE_RC_CONFIG_LCS);

		err = पढ़ोl_poll_समयout(rockchip->apb_base + PCIE_CORE_CTRL,
					 status, PCIE_LINK_IS_GEN2(status), 20,
					 500 * USEC_PER_MSEC);
		अगर (err)
			dev_dbg(dev, "PCIe link training gen2 timeout, fall back to gen1!\n");
	पूर्ण

	/* Check the final link width from negotiated lane counter from MGMT */
	status = rockchip_pcie_पढ़ो(rockchip, PCIE_CORE_CTRL);
	status = 0x1 << ((status & PCIE_CORE_PL_CONF_LANE_MASK) >>
			  PCIE_CORE_PL_CONF_LANE_SHIFT);
	dev_dbg(dev, "current link width is x%d\n", status);

	/* Power off unused lane(s) */
	rockchip->lanes_map = rockchip_pcie_lane_map(rockchip);
	क्रम (i = 0; i < MAX_LANE_NUM; i++) अणु
		अगर (!(rockchip->lanes_map & BIT(i))) अणु
			dev_dbg(dev, "idling lane %d\n", i);
			phy_घातer_off(rockchip->phys[i]);
		पूर्ण
	पूर्ण

	rockchip_pcie_ग_लिखो(rockchip, ROCKCHIP_VENDOR_ID,
			    PCIE_CORE_CONFIG_VENDOR);
	rockchip_pcie_ग_लिखो(rockchip,
			    PCI_CLASS_BRIDGE_PCI << PCIE_RC_CONFIG_SCC_SHIFT,
			    PCIE_RC_CONFIG_RID_CCR);

	/* Clear THP cap's next cap poपूर्णांकer to हटाओ L1 substate cap */
	status = rockchip_pcie_पढ़ो(rockchip, PCIE_RC_CONFIG_THP_CAP);
	status &= ~PCIE_RC_CONFIG_THP_CAP_NEXT_MASK;
	rockchip_pcie_ग_लिखो(rockchip, status, PCIE_RC_CONFIG_THP_CAP);

	/* Clear L0s from RC's link cap */
	अगर (of_property_पढ़ो_bool(dev->of_node, "aspm-no-l0s")) अणु
		status = rockchip_pcie_पढ़ो(rockchip, PCIE_RC_CONFIG_LINK_CAP);
		status &= ~PCIE_RC_CONFIG_LINK_CAP_L0S;
		rockchip_pcie_ग_लिखो(rockchip, status, PCIE_RC_CONFIG_LINK_CAP);
	पूर्ण

	status = rockchip_pcie_पढ़ो(rockchip, PCIE_RC_CONFIG_DCSR);
	status &= ~PCIE_RC_CONFIG_DCSR_MPS_MASK;
	status |= PCIE_RC_CONFIG_DCSR_MPS_256;
	rockchip_pcie_ग_लिखो(rockchip, status, PCIE_RC_CONFIG_DCSR);

	वापस 0;
err_घातer_off_phy:
	जबतक (i--)
		phy_घातer_off(rockchip->phys[i]);
	i = MAX_LANE_NUM;
	जबतक (i--)
		phy_निकास(rockchip->phys[i]);
	वापस err;
पूर्ण

अटल irqवापस_t rockchip_pcie_subsys_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा rockchip_pcie *rockchip = arg;
	काष्ठा device *dev = rockchip->dev;
	u32 reg;
	u32 sub_reg;

	reg = rockchip_pcie_पढ़ो(rockchip, PCIE_CLIENT_INT_STATUS);
	अगर (reg & PCIE_CLIENT_INT_LOCAL) अणु
		dev_dbg(dev, "local interrupt received\n");
		sub_reg = rockchip_pcie_पढ़ो(rockchip, PCIE_CORE_INT_STATUS);
		अगर (sub_reg & PCIE_CORE_INT_PRFPE)
			dev_dbg(dev, "parity error detected while reading from the PNP receive FIFO RAM\n");

		अगर (sub_reg & PCIE_CORE_INT_CRFPE)
			dev_dbg(dev, "parity error detected while reading from the Completion Receive FIFO RAM\n");

		अगर (sub_reg & PCIE_CORE_INT_RRPE)
			dev_dbg(dev, "parity error detected while reading from replay buffer RAM\n");

		अगर (sub_reg & PCIE_CORE_INT_PRFO)
			dev_dbg(dev, "overflow occurred in the PNP receive FIFO\n");

		अगर (sub_reg & PCIE_CORE_INT_CRFO)
			dev_dbg(dev, "overflow occurred in the completion receive FIFO\n");

		अगर (sub_reg & PCIE_CORE_INT_RT)
			dev_dbg(dev, "replay timer timed out\n");

		अगर (sub_reg & PCIE_CORE_INT_RTR)
			dev_dbg(dev, "replay timer rolled over after 4 transmissions of the same TLP\n");

		अगर (sub_reg & PCIE_CORE_INT_PE)
			dev_dbg(dev, "phy error detected on receive side\n");

		अगर (sub_reg & PCIE_CORE_INT_MTR)
			dev_dbg(dev, "malformed TLP received from the link\n");

		अगर (sub_reg & PCIE_CORE_INT_UCR)
			dev_dbg(dev, "malformed TLP received from the link\n");

		अगर (sub_reg & PCIE_CORE_INT_FCE)
			dev_dbg(dev, "an error was observed in the flow control advertisements from the other side\n");

		अगर (sub_reg & PCIE_CORE_INT_CT)
			dev_dbg(dev, "a request timed out waiting for completion\n");

		अगर (sub_reg & PCIE_CORE_INT_UTC)
			dev_dbg(dev, "unmapped TC error\n");

		अगर (sub_reg & PCIE_CORE_INT_MMVC)
			dev_dbg(dev, "MSI mask register changes\n");

		rockchip_pcie_ग_लिखो(rockchip, sub_reg, PCIE_CORE_INT_STATUS);
	पूर्ण अन्यथा अगर (reg & PCIE_CLIENT_INT_PHY) अणु
		dev_dbg(dev, "phy link changes\n");
		rockchip_pcie_update_txcredit_mui(rockchip);
		rockchip_pcie_clr_bw_पूर्णांक(rockchip);
	पूर्ण

	rockchip_pcie_ग_लिखो(rockchip, reg & PCIE_CLIENT_INT_LOCAL,
			    PCIE_CLIENT_INT_STATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rockchip_pcie_client_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा rockchip_pcie *rockchip = arg;
	काष्ठा device *dev = rockchip->dev;
	u32 reg;

	reg = rockchip_pcie_पढ़ो(rockchip, PCIE_CLIENT_INT_STATUS);
	अगर (reg & PCIE_CLIENT_INT_LEGACY_DONE)
		dev_dbg(dev, "legacy done interrupt received\n");

	अगर (reg & PCIE_CLIENT_INT_MSG)
		dev_dbg(dev, "message done interrupt received\n");

	अगर (reg & PCIE_CLIENT_INT_HOT_RST)
		dev_dbg(dev, "hot reset interrupt received\n");

	अगर (reg & PCIE_CLIENT_INT_DPA)
		dev_dbg(dev, "dpa interrupt received\n");

	अगर (reg & PCIE_CLIENT_INT_FATAL_ERR)
		dev_dbg(dev, "fatal error interrupt received\n");

	अगर (reg & PCIE_CLIENT_INT_NFATAL_ERR)
		dev_dbg(dev, "no fatal error interrupt received\n");

	अगर (reg & PCIE_CLIENT_INT_CORR_ERR)
		dev_dbg(dev, "correctable error interrupt received\n");

	अगर (reg & PCIE_CLIENT_INT_PHY)
		dev_dbg(dev, "phy interrupt received\n");

	rockchip_pcie_ग_लिखो(rockchip, reg & (PCIE_CLIENT_INT_LEGACY_DONE |
			      PCIE_CLIENT_INT_MSG | PCIE_CLIENT_INT_HOT_RST |
			      PCIE_CLIENT_INT_DPA | PCIE_CLIENT_INT_FATAL_ERR |
			      PCIE_CLIENT_INT_NFATAL_ERR |
			      PCIE_CLIENT_INT_CORR_ERR |
			      PCIE_CLIENT_INT_PHY),
		   PCIE_CLIENT_INT_STATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rockchip_pcie_legacy_पूर्णांक_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा rockchip_pcie *rockchip = irq_desc_get_handler_data(desc);
	काष्ठा device *dev = rockchip->dev;
	u32 reg;
	u32 hwirq;
	u32 virq;

	chained_irq_enter(chip, desc);

	reg = rockchip_pcie_पढ़ो(rockchip, PCIE_CLIENT_INT_STATUS);
	reg = (reg & PCIE_CLIENT_INTR_MASK) >> PCIE_CLIENT_INTR_SHIFT;

	जबतक (reg) अणु
		hwirq = ffs(reg) - 1;
		reg &= ~BIT(hwirq);

		virq = irq_find_mapping(rockchip->irq_करोमुख्य, hwirq);
		अगर (virq)
			generic_handle_irq(virq);
		अन्यथा
			dev_err(dev, "unexpected IRQ, INT%d\n", hwirq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक rockchip_pcie_setup_irq(काष्ठा rockchip_pcie *rockchip)
अणु
	पूर्णांक irq, err;
	काष्ठा device *dev = rockchip->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	irq = platक्रमm_get_irq_byname(pdev, "sys");
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(dev, irq, rockchip_pcie_subsys_irq_handler,
			       IRQF_SHARED, "pcie-sys", rockchip);
	अगर (err) अणु
		dev_err(dev, "failed to request PCIe subsystem IRQ\n");
		वापस err;
	पूर्ण

	irq = platक्रमm_get_irq_byname(pdev, "legacy");
	अगर (irq < 0)
		वापस irq;

	irq_set_chained_handler_and_data(irq,
					 rockchip_pcie_legacy_पूर्णांक_handler,
					 rockchip);

	irq = platक्रमm_get_irq_byname(pdev, "client");
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(dev, irq, rockchip_pcie_client_irq_handler,
			       IRQF_SHARED, "pcie-client", rockchip);
	अगर (err) अणु
		dev_err(dev, "failed to request PCIe client IRQ\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rockchip_pcie_parse_host_dt - Parse Device Tree
 * @rockchip: PCIe port inक्रमmation
 *
 * Return: '0' on success and error value on failure
 */
अटल पूर्णांक rockchip_pcie_parse_host_dt(काष्ठा rockchip_pcie *rockchip)
अणु
	काष्ठा device *dev = rockchip->dev;
	पूर्णांक err;

	err = rockchip_pcie_parse_dt(rockchip);
	अगर (err)
		वापस err;

	err = rockchip_pcie_setup_irq(rockchip);
	अगर (err)
		वापस err;

	rockchip->vpcie12v = devm_regulator_get_optional(dev, "vpcie12v");
	अगर (IS_ERR(rockchip->vpcie12v)) अणु
		अगर (PTR_ERR(rockchip->vpcie12v) != -ENODEV)
			वापस PTR_ERR(rockchip->vpcie12v);
		dev_info(dev, "no vpcie12v regulator found\n");
	पूर्ण

	rockchip->vpcie3v3 = devm_regulator_get_optional(dev, "vpcie3v3");
	अगर (IS_ERR(rockchip->vpcie3v3)) अणु
		अगर (PTR_ERR(rockchip->vpcie3v3) != -ENODEV)
			वापस PTR_ERR(rockchip->vpcie3v3);
		dev_info(dev, "no vpcie3v3 regulator found\n");
	पूर्ण

	rockchip->vpcie1v8 = devm_regulator_get(dev, "vpcie1v8");
	अगर (IS_ERR(rockchip->vpcie1v8))
		वापस PTR_ERR(rockchip->vpcie1v8);

	rockchip->vpcie0v9 = devm_regulator_get(dev, "vpcie0v9");
	अगर (IS_ERR(rockchip->vpcie0v9))
		वापस PTR_ERR(rockchip->vpcie0v9);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pcie_set_vpcie(काष्ठा rockchip_pcie *rockchip)
अणु
	काष्ठा device *dev = rockchip->dev;
	पूर्णांक err;

	अगर (!IS_ERR(rockchip->vpcie12v)) अणु
		err = regulator_enable(rockchip->vpcie12v);
		अगर (err) अणु
			dev_err(dev, "fail to enable vpcie12v regulator\n");
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(rockchip->vpcie3v3)) अणु
		err = regulator_enable(rockchip->vpcie3v3);
		अगर (err) अणु
			dev_err(dev, "fail to enable vpcie3v3 regulator\n");
			जाओ err_disable_12v;
		पूर्ण
	पूर्ण

	err = regulator_enable(rockchip->vpcie1v8);
	अगर (err) अणु
		dev_err(dev, "fail to enable vpcie1v8 regulator\n");
		जाओ err_disable_3v3;
	पूर्ण

	err = regulator_enable(rockchip->vpcie0v9);
	अगर (err) अणु
		dev_err(dev, "fail to enable vpcie0v9 regulator\n");
		जाओ err_disable_1v8;
	पूर्ण

	वापस 0;

err_disable_1v8:
	regulator_disable(rockchip->vpcie1v8);
err_disable_3v3:
	अगर (!IS_ERR(rockchip->vpcie3v3))
		regulator_disable(rockchip->vpcie3v3);
err_disable_12v:
	अगर (!IS_ERR(rockchip->vpcie12v))
		regulator_disable(rockchip->vpcie12v);
err_out:
	वापस err;
पूर्ण

अटल व्योम rockchip_pcie_enable_पूर्णांकerrupts(काष्ठा rockchip_pcie *rockchip)
अणु
	rockchip_pcie_ग_लिखो(rockchip, (PCIE_CLIENT_INT_CLI << 16) &
			    (~PCIE_CLIENT_INT_CLI), PCIE_CLIENT_INT_MASK);
	rockchip_pcie_ग_लिखो(rockchip, (u32)(~PCIE_CORE_INT),
			    PCIE_CORE_INT_MASK);

	rockchip_pcie_enable_bw_पूर्णांक(rockchip);
पूर्ण

अटल पूर्णांक rockchip_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
				  irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &dummy_irq_chip, handle_simple_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकx_करोमुख्य_ops = अणु
	.map = rockchip_pcie_पूर्णांकx_map,
पूर्ण;

अटल पूर्णांक rockchip_pcie_init_irq_करोमुख्य(काष्ठा rockchip_pcie *rockchip)
अणु
	काष्ठा device *dev = rockchip->dev;
	काष्ठा device_node *पूर्णांकc = of_get_next_child(dev->of_node, शून्य);

	अगर (!पूर्णांकc) अणु
		dev_err(dev, "missing child interrupt-controller node\n");
		वापस -EINVAL;
	पूर्ण

	rockchip->irq_करोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc, PCI_NUM_INTX,
						    &पूर्णांकx_करोमुख्य_ops, rockchip);
	of_node_put(पूर्णांकc);
	अगर (!rockchip->irq_करोमुख्य) अणु
		dev_err(dev, "failed to get a INTx IRQ domain\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pcie_prog_ob_atu(काष्ठा rockchip_pcie *rockchip,
				     पूर्णांक region_no, पूर्णांक type, u8 num_pass_bits,
				     u32 lower_addr, u32 upper_addr)
अणु
	u32 ob_addr_0;
	u32 ob_addr_1;
	u32 ob_desc_0;
	u32 aw_offset;

	अगर (region_no >= MAX_AXI_WRAPPER_REGION_NUM)
		वापस -EINVAL;
	अगर (num_pass_bits + 1 < 8)
		वापस -EINVAL;
	अगर (num_pass_bits > 63)
		वापस -EINVAL;
	अगर (region_no == 0) अणु
		अगर (AXI_REGION_0_SIZE < (2ULL << num_pass_bits))
			वापस -EINVAL;
	पूर्ण
	अगर (region_no != 0) अणु
		अगर (AXI_REGION_SIZE < (2ULL << num_pass_bits))
			वापस -EINVAL;
	पूर्ण

	aw_offset = (region_no << OB_REG_SIZE_SHIFT);

	ob_addr_0 = num_pass_bits & PCIE_CORE_OB_REGION_ADDR0_NUM_BITS;
	ob_addr_0 |= lower_addr & PCIE_CORE_OB_REGION_ADDR0_LO_ADDR;
	ob_addr_1 = upper_addr;
	ob_desc_0 = (1 << 23 | type);

	rockchip_pcie_ग_लिखो(rockchip, ob_addr_0,
			    PCIE_CORE_OB_REGION_ADDR0 + aw_offset);
	rockchip_pcie_ग_लिखो(rockchip, ob_addr_1,
			    PCIE_CORE_OB_REGION_ADDR1 + aw_offset);
	rockchip_pcie_ग_लिखो(rockchip, ob_desc_0,
			    PCIE_CORE_OB_REGION_DESC0 + aw_offset);
	rockchip_pcie_ग_लिखो(rockchip, 0,
			    PCIE_CORE_OB_REGION_DESC1 + aw_offset);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pcie_prog_ib_atu(काष्ठा rockchip_pcie *rockchip,
				     पूर्णांक region_no, u8 num_pass_bits,
				     u32 lower_addr, u32 upper_addr)
अणु
	u32 ib_addr_0;
	u32 ib_addr_1;
	u32 aw_offset;

	अगर (region_no > MAX_AXI_IB_ROOTPORT_REGION_NUM)
		वापस -EINVAL;
	अगर (num_pass_bits + 1 < MIN_AXI_ADDR_BITS_PASSED)
		वापस -EINVAL;
	अगर (num_pass_bits > 63)
		वापस -EINVAL;

	aw_offset = (region_no << IB_ROOT_PORT_REG_SIZE_SHIFT);

	ib_addr_0 = num_pass_bits & PCIE_CORE_IB_REGION_ADDR0_NUM_BITS;
	ib_addr_0 |= (lower_addr << 8) & PCIE_CORE_IB_REGION_ADDR0_LO_ADDR;
	ib_addr_1 = upper_addr;

	rockchip_pcie_ग_लिखो(rockchip, ib_addr_0, PCIE_RP_IB_ADDR0 + aw_offset);
	rockchip_pcie_ग_लिखो(rockchip, ib_addr_1, PCIE_RP_IB_ADDR1 + aw_offset);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pcie_cfg_atu(काष्ठा rockchip_pcie *rockchip)
अणु
	काष्ठा device *dev = rockchip->dev;
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(rockchip);
	काष्ठा resource_entry *entry;
	u64 pci_addr, size;
	पूर्णांक offset;
	पूर्णांक err;
	पूर्णांक reg_no;

	rockchip_pcie_cfg_configuration_accesses(rockchip,
						 AXI_WRAPPER_TYPE0_CFG);
	entry = resource_list_first_type(&bridge->winकरोws, IORESOURCE_MEM);
	अगर (!entry)
		वापस -ENODEV;

	size = resource_size(entry->res);
	pci_addr = entry->res->start - entry->offset;
	rockchip->msg_bus_addr = pci_addr;

	क्रम (reg_no = 0; reg_no < (size >> 20); reg_no++) अणु
		err = rockchip_pcie_prog_ob_atu(rockchip, reg_no + 1,
						AXI_WRAPPER_MEM_WRITE,
						20 - 1,
						pci_addr + (reg_no << 20),
						0);
		अगर (err) अणु
			dev_err(dev, "program RC mem outbound ATU failed\n");
			वापस err;
		पूर्ण
	पूर्ण

	err = rockchip_pcie_prog_ib_atu(rockchip, 2, 32 - 1, 0x0, 0);
	अगर (err) अणु
		dev_err(dev, "program RC mem inbound ATU failed\n");
		वापस err;
	पूर्ण

	entry = resource_list_first_type(&bridge->winकरोws, IORESOURCE_IO);
	अगर (!entry)
		वापस -ENODEV;

	/* store the रेजिस्टर number offset to program RC io outbound ATU */
	offset = size >> 20;

	size = resource_size(entry->res);
	pci_addr = entry->res->start - entry->offset;

	क्रम (reg_no = 0; reg_no < (size >> 20); reg_no++) अणु
		err = rockchip_pcie_prog_ob_atu(rockchip,
						reg_no + 1 + offset,
						AXI_WRAPPER_IO_WRITE,
						20 - 1,
						pci_addr + (reg_no << 20),
						0);
		अगर (err) अणु
			dev_err(dev, "program RC io outbound ATU failed\n");
			वापस err;
		पूर्ण
	पूर्ण

	/* assign message regions */
	rockchip_pcie_prog_ob_atu(rockchip, reg_no + 1 + offset,
				  AXI_WRAPPER_NOR_MSG,
				  20 - 1, 0, 0);

	rockchip->msg_bus_addr += ((reg_no + offset) << 20);
	वापस err;
पूर्ण

अटल पूर्णांक rockchip_pcie_रुको_l2(काष्ठा rockchip_pcie *rockchip)
अणु
	u32 value;
	पूर्णांक err;

	/* send PME_TURN_OFF message */
	ग_लिखोl(0x0, rockchip->msg_region + PCIE_RC_SEND_PME_OFF);

	/* पढ़ो LTSSM and रुको क्रम falling पूर्णांकo L2 link state */
	err = पढ़ोl_poll_समयout(rockchip->apb_base + PCIE_CLIENT_DEBUG_OUT_0,
				 value, PCIE_LINK_IS_L2(value), 20,
				 jअगरfies_to_usecs(5 * HZ));
	अगर (err) अणु
		dev_err(rockchip->dev, "PCIe link enter L2 timeout!\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rockchip_pcie_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा rockchip_pcie *rockchip = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* disable core and cli पूर्णांक since we करोn't need to ack PME_ACK */
	rockchip_pcie_ग_लिखो(rockchip, (PCIE_CLIENT_INT_CLI << 16) |
			    PCIE_CLIENT_INT_CLI, PCIE_CLIENT_INT_MASK);
	rockchip_pcie_ग_लिखो(rockchip, (u32)PCIE_CORE_INT, PCIE_CORE_INT_MASK);

	ret = rockchip_pcie_रुको_l2(rockchip);
	अगर (ret) अणु
		rockchip_pcie_enable_पूर्णांकerrupts(rockchip);
		वापस ret;
	पूर्ण

	rockchip_pcie_deinit_phys(rockchip);

	rockchip_pcie_disable_घड़ीs(rockchip);

	regulator_disable(rockchip->vpcie0v9);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused rockchip_pcie_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा rockchip_pcie *rockchip = dev_get_drvdata(dev);
	पूर्णांक err;

	err = regulator_enable(rockchip->vpcie0v9);
	अगर (err) अणु
		dev_err(dev, "fail to enable vpcie0v9 regulator\n");
		वापस err;
	पूर्ण

	err = rockchip_pcie_enable_घड़ीs(rockchip);
	अगर (err)
		जाओ err_disable_0v9;

	err = rockchip_pcie_host_init_port(rockchip);
	अगर (err)
		जाओ err_pcie_resume;

	err = rockchip_pcie_cfg_atu(rockchip);
	अगर (err)
		जाओ err_err_deinit_port;

	/* Need this to enter L1 again */
	rockchip_pcie_update_txcredit_mui(rockchip);
	rockchip_pcie_enable_पूर्णांकerrupts(rockchip);

	वापस 0;

err_err_deinit_port:
	rockchip_pcie_deinit_phys(rockchip);
err_pcie_resume:
	rockchip_pcie_disable_घड़ीs(rockchip);
err_disable_0v9:
	regulator_disable(rockchip->vpcie0v9);
	वापस err;
पूर्ण

अटल पूर्णांक rockchip_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_pcie *rockchip;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक err;

	अगर (!dev->of_node)
		वापस -ENODEV;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*rockchip));
	अगर (!bridge)
		वापस -ENOMEM;

	rockchip = pci_host_bridge_priv(bridge);

	platक्रमm_set_drvdata(pdev, rockchip);
	rockchip->dev = dev;
	rockchip->is_rc = true;

	err = rockchip_pcie_parse_host_dt(rockchip);
	अगर (err)
		वापस err;

	err = rockchip_pcie_enable_घड़ीs(rockchip);
	अगर (err)
		वापस err;

	err = rockchip_pcie_set_vpcie(rockchip);
	अगर (err) अणु
		dev_err(dev, "failed to set vpcie regulator\n");
		जाओ err_set_vpcie;
	पूर्ण

	err = rockchip_pcie_host_init_port(rockchip);
	अगर (err)
		जाओ err_vpcie;

	rockchip_pcie_enable_पूर्णांकerrupts(rockchip);

	err = rockchip_pcie_init_irq_करोमुख्य(rockchip);
	अगर (err < 0)
		जाओ err_deinit_port;

	err = rockchip_pcie_cfg_atu(rockchip);
	अगर (err)
		जाओ err_हटाओ_irq_करोमुख्य;

	rockchip->msg_region = devm_ioremap(dev, rockchip->msg_bus_addr, SZ_1M);
	अगर (!rockchip->msg_region) अणु
		err = -ENOMEM;
		जाओ err_हटाओ_irq_करोमुख्य;
	पूर्ण

	bridge->sysdata = rockchip;
	bridge->ops = &rockchip_pcie_ops;

	err = pci_host_probe(bridge);
	अगर (err < 0)
		जाओ err_हटाओ_irq_करोमुख्य;

	वापस 0;

err_हटाओ_irq_करोमुख्य:
	irq_करोमुख्य_हटाओ(rockchip->irq_करोमुख्य);
err_deinit_port:
	rockchip_pcie_deinit_phys(rockchip);
err_vpcie:
	अगर (!IS_ERR(rockchip->vpcie12v))
		regulator_disable(rockchip->vpcie12v);
	अगर (!IS_ERR(rockchip->vpcie3v3))
		regulator_disable(rockchip->vpcie3v3);
	regulator_disable(rockchip->vpcie1v8);
	regulator_disable(rockchip->vpcie0v9);
err_set_vpcie:
	rockchip_pcie_disable_घड़ीs(rockchip);
	वापस err;
पूर्ण

अटल पूर्णांक rockchip_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rockchip_pcie *rockchip = dev_get_drvdata(dev);
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(rockchip);

	pci_stop_root_bus(bridge->bus);
	pci_हटाओ_root_bus(bridge->bus);
	irq_करोमुख्य_हटाओ(rockchip->irq_करोमुख्य);

	rockchip_pcie_deinit_phys(rockchip);

	rockchip_pcie_disable_घड़ीs(rockchip);

	अगर (!IS_ERR(rockchip->vpcie12v))
		regulator_disable(rockchip->vpcie12v);
	अगर (!IS_ERR(rockchip->vpcie3v3))
		regulator_disable(rockchip->vpcie3v3);
	regulator_disable(rockchip->vpcie1v8);
	regulator_disable(rockchip->vpcie0v9);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rockchip_pcie_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(rockchip_pcie_suspend_noirq,
				      rockchip_pcie_resume_noirq)
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_pcie_of_match[] = अणु
	अणु .compatible = "rockchip,rk3399-pcie", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_pcie_of_match);

अटल काष्ठा platक्रमm_driver rockchip_pcie_driver = अणु
	.driver = अणु
		.name = "rockchip-pcie",
		.of_match_table = rockchip_pcie_of_match,
		.pm = &rockchip_pcie_pm_ops,
	पूर्ण,
	.probe = rockchip_pcie_probe,
	.हटाओ = rockchip_pcie_हटाओ,
पूर्ण;
module_platक्रमm_driver(rockchip_pcie_driver);

MODULE_AUTHOR("Rockchip Inc");
MODULE_DESCRIPTION("Rockchip AXI PCIe driver");
MODULE_LICENSE("GPL v2");
