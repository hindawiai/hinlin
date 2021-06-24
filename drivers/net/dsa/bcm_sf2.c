<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom Starfighter 2 DSA चयन driver
 *
 * Copyright (C) 2014, Broadcom Corporation
 */

#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/phylink.h>
#समावेश <linux/mii.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <net/dsa.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_data/b53.h>

#समावेश "bcm_sf2.h"
#समावेश "bcm_sf2_regs.h"
#समावेश "b53/b53_priv.h"
#समावेश "b53/b53_regs.h"

अटल u16 bcm_sf2_reg_rgmii_cntrl(काष्ठा bcm_sf2_priv *priv, पूर्णांक port)
अणु
	चयन (priv->type) अणु
	हाल BCM4908_DEVICE_ID:
		चयन (port) अणु
		हाल 7:
			वापस REG_RGMII_11_CNTRL;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		चयन (port) अणु
		हाल 0:
			वापस REG_RGMII_0_CNTRL;
		हाल 1:
			वापस REG_RGMII_1_CNTRL;
		हाल 2:
			वापस REG_RGMII_2_CNTRL;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	WARN_ONCE(1, "Unsupported port %d\n", port);

	/* RO fallback reg */
	वापस REG_SWITCH_STATUS;
पूर्ण

/* Return the number of active ports, not counting the IMP (CPU) port */
अटल अचिन्हित पूर्णांक bcm_sf2_num_active_ports(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	अचिन्हित पूर्णांक port, count = 0;

	क्रम (port = 0; port < ARRAY_SIZE(priv->port_sts); port++) अणु
		अगर (dsa_is_cpu_port(ds, port))
			जारी;
		अगर (priv->port_sts[port].enabled)
			count++;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम bcm_sf2_recalc_घड़ी(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	अचिन्हित दीर्घ new_rate;
	अचिन्हित पूर्णांक ports_active;
	/* Frequenty in Mhz */
	अटल स्थिर अचिन्हित दीर्घ rate_table[] = अणु
		59220000,
		60820000,
		62500000,
		62500000,
	पूर्ण;

	ports_active = bcm_sf2_num_active_ports(ds);
	अगर (ports_active == 0 || !priv->clk_mभाग)
		वापस;

	/* If we overflow our table, just use the recommended operational
	 * frequency
	 */
	अगर (ports_active > ARRAY_SIZE(rate_table))
		new_rate = 90000000;
	अन्यथा
		new_rate = rate_table[ports_active - 1];
	clk_set_rate(priv->clk_mभाग, new_rate);
पूर्ण

अटल व्योम bcm_sf2_imp_setup(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	अचिन्हित पूर्णांक i;
	u32 reg, offset;

	/* Enable the port memories */
	reg = core_पढ़ोl(priv, CORE_MEM_PSM_VDD_CTRL);
	reg &= ~P_TXQ_PSM_VDD(port);
	core_ग_लिखोl(priv, reg, CORE_MEM_PSM_VDD_CTRL);

	/* Enable क्रमwarding */
	core_ग_लिखोl(priv, SW_FWDG_EN, CORE_SWMODE);

	/* Enable IMP port in dumb mode */
	reg = core_पढ़ोl(priv, CORE_SWITCH_CTRL);
	reg |= MII_DUMB_FWDG_EN;
	core_ग_लिखोl(priv, reg, CORE_SWITCH_CTRL);

	/* Configure Traffic Class to QoS mapping, allow each priority to map
	 * to a dअगरferent queue number
	 */
	reg = core_पढ़ोl(priv, CORE_PORT_TC2_QOS_MAP_PORT(port));
	क्रम (i = 0; i < SF2_NUM_EGRESS_QUEUES; i++)
		reg |= i << (PRT_TO_QID_SHIFT * i);
	core_ग_लिखोl(priv, reg, CORE_PORT_TC2_QOS_MAP_PORT(port));

	b53_brcm_hdr_setup(ds, port);

	अगर (port == 8) अणु
		अगर (priv->type == BCM4908_DEVICE_ID ||
		    priv->type == BCM7445_DEVICE_ID)
			offset = CORE_STS_OVERRIDE_IMP;
		अन्यथा
			offset = CORE_STS_OVERRIDE_IMP2;

		/* Force link status क्रम IMP port */
		reg = core_पढ़ोl(priv, offset);
		reg |= (MII_SW_OR | LINK_STS);
		अगर (priv->type == BCM4908_DEVICE_ID)
			reg |= GMII_SPEED_UP_2G;
		अन्यथा
			reg &= ~GMII_SPEED_UP_2G;
		core_ग_लिखोl(priv, reg, offset);

		/* Enable Broadcast, Multicast, Unicast क्रमwarding to IMP port */
		reg = core_पढ़ोl(priv, CORE_IMP_CTL);
		reg |= (RX_BCST_EN | RX_MCST_EN | RX_UCST_EN);
		reg &= ~(RX_DIS | TX_DIS);
		core_ग_लिखोl(priv, reg, CORE_IMP_CTL);
	पूर्ण अन्यथा अणु
		reg = core_पढ़ोl(priv, CORE_G_PCTL_PORT(port));
		reg &= ~(RX_DIS | TX_DIS);
		core_ग_लिखोl(priv, reg, CORE_G_PCTL_PORT(port));
	पूर्ण

	priv->port_sts[port].enabled = true;
पूर्ण

अटल व्योम bcm_sf2_gphy_enable_set(काष्ठा dsa_चयन *ds, bool enable)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 reg;

	reg = reg_पढ़ोl(priv, REG_SPHY_CNTRL);
	अगर (enable) अणु
		reg |= PHY_RESET;
		reg &= ~(EXT_PWR_DOWN | IDDQ_BIAS | IDDQ_GLOBAL_PWR | CK25_DIS);
		reg_ग_लिखोl(priv, reg, REG_SPHY_CNTRL);
		udelay(21);
		reg = reg_पढ़ोl(priv, REG_SPHY_CNTRL);
		reg &= ~PHY_RESET;
	पूर्ण अन्यथा अणु
		reg |= EXT_PWR_DOWN | IDDQ_BIAS | PHY_RESET;
		reg_ग_लिखोl(priv, reg, REG_SPHY_CNTRL);
		mdelay(1);
		reg |= CK25_DIS;
	पूर्ण
	reg_ग_लिखोl(priv, reg, REG_SPHY_CNTRL);

	/* Use PHY-driven LED संकेतing */
	अगर (!enable) अणु
		reg = reg_पढ़ोl(priv, REG_LED_CNTRL(0));
		reg |= SPDLNK_SRC_SEL;
		reg_ग_लिखोl(priv, reg, REG_LED_CNTRL(0));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bcm_sf2_port_पूर्णांकr_enable(काष्ठा bcm_sf2_priv *priv,
					    पूर्णांक port)
अणु
	अचिन्हित पूर्णांक off;

	चयन (port) अणु
	हाल 7:
		off = P7_IRQ_OFF;
		अवरोध;
	हाल 0:
		/* Port 0 पूर्णांकerrupts are located on the first bank */
		पूर्णांकrl2_0_mask_clear(priv, P_IRQ_MASK(P0_IRQ_OFF));
		वापस;
	शेष:
		off = P_IRQ_OFF(port);
		अवरोध;
	पूर्ण

	पूर्णांकrl2_1_mask_clear(priv, P_IRQ_MASK(off));
पूर्ण

अटल अंतरभूत व्योम bcm_sf2_port_पूर्णांकr_disable(काष्ठा bcm_sf2_priv *priv,
					     पूर्णांक port)
अणु
	अचिन्हित पूर्णांक off;

	चयन (port) अणु
	हाल 7:
		off = P7_IRQ_OFF;
		अवरोध;
	हाल 0:
		/* Port 0 पूर्णांकerrupts are located on the first bank */
		पूर्णांकrl2_0_mask_set(priv, P_IRQ_MASK(P0_IRQ_OFF));
		पूर्णांकrl2_0_ग_लिखोl(priv, P_IRQ_MASK(P0_IRQ_OFF), INTRL2_CPU_CLEAR);
		वापस;
	शेष:
		off = P_IRQ_OFF(port);
		अवरोध;
	पूर्ण

	पूर्णांकrl2_1_mask_set(priv, P_IRQ_MASK(off));
	पूर्णांकrl2_1_ग_लिखोl(priv, P_IRQ_MASK(off), INTRL2_CPU_CLEAR);
पूर्ण

अटल पूर्णांक bcm_sf2_port_setup(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा phy_device *phy)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	अचिन्हित पूर्णांक i;
	u32 reg;

	अगर (!dsa_is_user_port(ds, port))
		वापस 0;

	priv->port_sts[port].enabled = true;

	bcm_sf2_recalc_घड़ी(ds);

	/* Clear the memory घातer करोwn */
	reg = core_पढ़ोl(priv, CORE_MEM_PSM_VDD_CTRL);
	reg &= ~P_TXQ_PSM_VDD(port);
	core_ग_लिखोl(priv, reg, CORE_MEM_PSM_VDD_CTRL);

	/* Enable Broadcom tags क्रम that port अगर requested */
	अगर (priv->brcm_tag_mask & BIT(port))
		b53_brcm_hdr_setup(ds, port);

	/* Configure Traffic Class to QoS mapping, allow each priority to map
	 * to a dअगरferent queue number
	 */
	reg = core_पढ़ोl(priv, CORE_PORT_TC2_QOS_MAP_PORT(port));
	क्रम (i = 0; i < SF2_NUM_EGRESS_QUEUES; i++)
		reg |= i << (PRT_TO_QID_SHIFT * i);
	core_ग_लिखोl(priv, reg, CORE_PORT_TC2_QOS_MAP_PORT(port));

	/* Re-enable the GPHY and re-apply workarounds */
	अगर (priv->पूर्णांक_phy_mask & 1 << port && priv->hw_params.num_gphy == 1) अणु
		bcm_sf2_gphy_enable_set(ds, true);
		अगर (phy) अणु
			/* अगर phy_stop() has been called beक्रमe, phy
			 * will be in halted state, and phy_start()
			 * will call resume.
			 *
			 * the resume path करोes not configure back
			 * स्वतःneg settings, and since we hard reset
			 * the phy manually here, we need to reset the
			 * state machine also.
			 */
			phy->state = PHY_READY;
			phy_init_hw(phy);
		पूर्ण
	पूर्ण

	/* Enable MoCA port पूर्णांकerrupts to get notअगरied */
	अगर (port == priv->moca_port)
		bcm_sf2_port_पूर्णांकr_enable(priv, port);

	/* Set per-queue छोड़ो threshold to 32 */
	core_ग_लिखोl(priv, 32, CORE_TXQ_THD_PAUSE_QN_PORT(port));

	/* Set ACB threshold to 24 */
	क्रम (i = 0; i < SF2_NUM_EGRESS_QUEUES; i++) अणु
		reg = acb_पढ़ोl(priv, ACB_QUEUE_CFG(port *
						    SF2_NUM_EGRESS_QUEUES + i));
		reg &= ~XOFF_THRESHOLD_MASK;
		reg |= 24;
		acb_ग_लिखोl(priv, reg, ACB_QUEUE_CFG(port *
						    SF2_NUM_EGRESS_QUEUES + i));
	पूर्ण

	वापस b53_enable_port(ds, port, phy);
पूर्ण

अटल व्योम bcm_sf2_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 reg;

	/* Disable learning जबतक in WoL mode */
	अगर (priv->wol_ports_mask & (1 << port)) अणु
		reg = core_पढ़ोl(priv, CORE_DIS_LEARN);
		reg |= BIT(port);
		core_ग_लिखोl(priv, reg, CORE_DIS_LEARN);
		वापस;
	पूर्ण

	अगर (port == priv->moca_port)
		bcm_sf2_port_पूर्णांकr_disable(priv, port);

	अगर (priv->पूर्णांक_phy_mask & 1 << port && priv->hw_params.num_gphy == 1)
		bcm_sf2_gphy_enable_set(ds, false);

	b53_disable_port(ds, port);

	/* Power करोwn the port memory */
	reg = core_पढ़ोl(priv, CORE_MEM_PSM_VDD_CTRL);
	reg |= P_TXQ_PSM_VDD(port);
	core_ग_लिखोl(priv, reg, CORE_MEM_PSM_VDD_CTRL);

	priv->port_sts[port].enabled = false;

	bcm_sf2_recalc_घड़ी(ds);
पूर्ण


अटल पूर्णांक bcm_sf2_sw_indir_rw(काष्ठा bcm_sf2_priv *priv, पूर्णांक op, पूर्णांक addr,
			       पूर्णांक regnum, u16 val)
अणु
	पूर्णांक ret = 0;
	u32 reg;

	reg = reg_पढ़ोl(priv, REG_SWITCH_CNTRL);
	reg |= MDIO_MASTER_SEL;
	reg_ग_लिखोl(priv, reg, REG_SWITCH_CNTRL);

	/* Page << 8 | offset */
	reg = 0x70;
	reg <<= 2;
	core_ग_लिखोl(priv, addr, reg);

	/* Page << 8 | offset */
	reg = 0x80 << 8 | regnum << 1;
	reg <<= 2;

	अगर (op)
		ret = core_पढ़ोl(priv, reg);
	अन्यथा
		core_ग_लिखोl(priv, val, reg);

	reg = reg_पढ़ोl(priv, REG_SWITCH_CNTRL);
	reg &= ~MDIO_MASTER_SEL;
	reg_ग_लिखोl(priv, reg, REG_SWITCH_CNTRL);

	वापस ret & 0xffff;
पूर्ण

अटल पूर्णांक bcm_sf2_sw_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum)
अणु
	काष्ठा bcm_sf2_priv *priv = bus->priv;

	/* Intercept पढ़ोs from Broadcom pseuकरो-PHY address, अन्यथा, send
	 * them to our master MDIO bus controller
	 */
	अगर (addr == BRCM_PSEUDO_PHY_ADDR && priv->indir_phy_mask & BIT(addr))
		वापस bcm_sf2_sw_indir_rw(priv, 1, addr, regnum, 0);
	अन्यथा
		वापस mdiobus_पढ़ो_nested(priv->master_mii_bus, addr, regnum);
पूर्ण

अटल पूर्णांक bcm_sf2_sw_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum,
				 u16 val)
अणु
	काष्ठा bcm_sf2_priv *priv = bus->priv;

	/* Intercept ग_लिखोs to the Broadcom pseuकरो-PHY address, अन्यथा,
	 * send them to our master MDIO bus controller
	 */
	अगर (addr == BRCM_PSEUDO_PHY_ADDR && priv->indir_phy_mask & BIT(addr))
		वापस bcm_sf2_sw_indir_rw(priv, 0, addr, regnum, val);
	अन्यथा
		वापस mdiobus_ग_लिखो_nested(priv->master_mii_bus, addr,
				regnum, val);
पूर्ण

अटल irqवापस_t bcm_sf2_चयन_0_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dsa_चयन *ds = dev_id;
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);

	priv->irq0_stat = पूर्णांकrl2_0_पढ़ोl(priv, INTRL2_CPU_STATUS) &
				~priv->irq0_mask;
	पूर्णांकrl2_0_ग_लिखोl(priv, priv->irq0_stat, INTRL2_CPU_CLEAR);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t bcm_sf2_चयन_1_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dsa_चयन *ds = dev_id;
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);

	priv->irq1_stat = पूर्णांकrl2_1_पढ़ोl(priv, INTRL2_CPU_STATUS) &
				~priv->irq1_mask;
	पूर्णांकrl2_1_ग_लिखोl(priv, priv->irq1_stat, INTRL2_CPU_CLEAR);

	अगर (priv->irq1_stat & P_LINK_UP_IRQ(P7_IRQ_OFF)) अणु
		priv->port_sts[7].link = true;
		dsa_port_phylink_mac_change(ds, 7, true);
	पूर्ण
	अगर (priv->irq1_stat & P_LINK_DOWN_IRQ(P7_IRQ_OFF)) अणु
		priv->port_sts[7].link = false;
		dsa_port_phylink_mac_change(ds, 7, false);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm_sf2_sw_rst(काष्ठा bcm_sf2_priv *priv)
अणु
	अचिन्हित पूर्णांक समयout = 1000;
	u32 reg;
	पूर्णांक ret;

	/* The watchकरोg reset करोes not work on 7278, we need to hit the
	 * "external" reset line through the reset controller.
	 */
	अगर (priv->type == BCM7278_DEVICE_ID) अणु
		ret = reset_control_निश्चित(priv->rcdev);
		अगर (ret)
			वापस ret;

		वापस reset_control_deनिश्चित(priv->rcdev);
	पूर्ण

	reg = core_पढ़ोl(priv, CORE_WATCHDOG_CTRL);
	reg |= SOFTWARE_RESET | EN_CHIP_RST | EN_SW_RESET;
	core_ग_लिखोl(priv, reg, CORE_WATCHDOG_CTRL);

	करो अणु
		reg = core_पढ़ोl(priv, CORE_WATCHDOG_CTRL);
		अगर (!(reg & SOFTWARE_RESET))
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण जबतक (समयout-- > 0);

	अगर (समयout == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम bcm_sf2_crossbar_setup(काष्ठा bcm_sf2_priv *priv)
अणु
	काष्ठा device *dev = priv->dev->ds->dev;
	पूर्णांक shअगरt;
	u32 mask;
	u32 reg;
	पूर्णांक i;

	mask = BIT(priv->num_crossbar_पूर्णांक_ports) - 1;

	reg = reg_पढ़ोl(priv, REG_CROSSBAR);
	चयन (priv->type) अणु
	हाल BCM4908_DEVICE_ID:
		shअगरt = CROSSBAR_BCM4908_INT_P7 * priv->num_crossbar_पूर्णांक_ports;
		reg &= ~(mask << shअगरt);
		अगर (0) /* FIXME */
			reg |= CROSSBAR_BCM4908_EXT_SERDES << shअगरt;
		अन्यथा अगर (priv->पूर्णांक_phy_mask & BIT(7))
			reg |= CROSSBAR_BCM4908_EXT_GPHY4 << shअगरt;
		अन्यथा अगर (phy_पूर्णांकerface_mode_is_rgmii(priv->port_sts[7].mode))
			reg |= CROSSBAR_BCM4908_EXT_RGMII << shअगरt;
		अन्यथा अगर (WARN(1, "Invalid port mode\n"))
			वापस;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	reg_ग_लिखोl(priv, reg, REG_CROSSBAR);

	reg = reg_पढ़ोl(priv, REG_CROSSBAR);
	क्रम (i = 0; i < priv->num_crossbar_पूर्णांक_ports; i++) अणु
		shअगरt = i * priv->num_crossbar_पूर्णांक_ports;

		dev_dbg(dev, "crossbar int port #%d - ext port #%d\n", i,
			(reg >> shअगरt) & mask);
	पूर्ण
पूर्ण

अटल व्योम bcm_sf2_पूर्णांकr_disable(काष्ठा bcm_sf2_priv *priv)
अणु
	पूर्णांकrl2_0_mask_set(priv, 0xffffffff);
	पूर्णांकrl2_0_ग_लिखोl(priv, 0xffffffff, INTRL2_CPU_CLEAR);
	पूर्णांकrl2_1_mask_set(priv, 0xffffffff);
	पूर्णांकrl2_1_ग_लिखोl(priv, 0xffffffff, INTRL2_CPU_CLEAR);
पूर्ण

अटल व्योम bcm_sf2_identअगरy_ports(काष्ठा bcm_sf2_priv *priv,
				   काष्ठा device_node *dn)
अणु
	काष्ठा device *dev = priv->dev->ds->dev;
	काष्ठा bcm_sf2_port_status *port_st;
	काष्ठा device_node *port;
	अचिन्हित पूर्णांक port_num;
	काष्ठा property *prop;
	पूर्णांक err;

	priv->moca_port = -1;

	क्रम_each_available_child_of_node(dn, port) अणु
		अगर (of_property_पढ़ो_u32(port, "reg", &port_num))
			जारी;

		अगर (port_num >= DSA_MAX_PORTS) अणु
			dev_err(dev, "Invalid port number %d\n", port_num);
			जारी;
		पूर्ण

		port_st = &priv->port_sts[port_num];

		/* Internal PHYs get asचिन्हित a specअगरic 'phy-mode' property
		 * value: "internal" to help flag them beक्रमe MDIO probing
		 * has completed, since they might be turned off at that
		 * समय
		 */
		err = of_get_phy_mode(port, &port_st->mode);
		अगर (err)
			जारी;

		अगर (port_st->mode == PHY_INTERFACE_MODE_INTERNAL)
			priv->पूर्णांक_phy_mask |= 1 << port_num;

		अगर (port_st->mode == PHY_INTERFACE_MODE_MOCA)
			priv->moca_port = port_num;

		अगर (of_property_पढ़ो_bool(port, "brcm,use-bcm-hdr"))
			priv->brcm_tag_mask |= 1 << port_num;

		/* Ensure that port 5 is not picked up as a DSA CPU port
		 * flavour but a regular port instead. We should be using
		 * devlink to be able to set the port flavour.
		 */
		अगर (port_num == 5 && priv->type == BCM7278_DEVICE_ID) अणु
			prop = of_find_property(port, "ethernet", शून्य);
			अगर (prop)
				of_हटाओ_property(port, prop);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_sf2_mdio_रेजिस्टर(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	काष्ठा device_node *dn, *child;
	काष्ठा phy_device *phydev;
	काष्ठा property *prop;
	अटल पूर्णांक index;
	पूर्णांक err, reg;

	/* Find our पूर्णांकegrated MDIO bus node */
	dn = of_find_compatible_node(शून्य, शून्य, "brcm,unimac-mdio");
	priv->master_mii_bus = of_mdio_find_bus(dn);
	अगर (!priv->master_mii_bus) अणु
		of_node_put(dn);
		वापस -EPROBE_DEFER;
	पूर्ण

	get_device(&priv->master_mii_bus->dev);
	priv->master_mii_dn = dn;

	priv->slave_mii_bus = devm_mdiobus_alloc(ds->dev);
	अगर (!priv->slave_mii_bus) अणु
		of_node_put(dn);
		वापस -ENOMEM;
	पूर्ण

	priv->slave_mii_bus->priv = priv;
	priv->slave_mii_bus->name = "sf2 slave mii";
	priv->slave_mii_bus->पढ़ो = bcm_sf2_sw_mdio_पढ़ो;
	priv->slave_mii_bus->ग_लिखो = bcm_sf2_sw_mdio_ग_लिखो;
	snम_लिखो(priv->slave_mii_bus->id, MII_BUS_ID_SIZE, "sf2-%d",
		 index++);
	priv->slave_mii_bus->dev.of_node = dn;

	/* Include the pseuकरो-PHY address to भागert पढ़ोs towards our
	 * workaround. This is only required क्रम 7445D0, since 7445E0
	 * disconnects the पूर्णांकernal चयन pseuकरो-PHY such that we can use the
	 * regular SWITCH_MDIO master controller instead.
	 *
	 * Here we flag the pseuकरो PHY as needing special treaपंचांगent and would
	 * otherwise make all other PHY पढ़ो/ग_लिखोs go to the master MDIO bus
	 * controller that comes with this चयन backed by the "mdio-unimac"
	 * driver.
	 */
	अगर (of_machine_is_compatible("brcm,bcm7445d0"))
		priv->indir_phy_mask |= (1 << BRCM_PSEUDO_PHY_ADDR) | (1 << 0);
	अन्यथा
		priv->indir_phy_mask = 0;

	ds->phys_mii_mask = priv->indir_phy_mask;
	ds->slave_mii_bus = priv->slave_mii_bus;
	priv->slave_mii_bus->parent = ds->dev->parent;
	priv->slave_mii_bus->phy_mask = ~priv->indir_phy_mask;

	/* We need to make sure that of_phy_connect() will not work by
	 * removing the 'phandle' and 'linux,phandle' properties and
	 * unरेजिस्टर the existing PHY device that was alपढ़ोy रेजिस्टरed.
	 */
	क्रम_each_available_child_of_node(dn, child) अणु
		अगर (of_property_पढ़ो_u32(child, "reg", &reg) ||
		    reg >= PHY_MAX_ADDR)
			जारी;

		अगर (!(priv->indir_phy_mask & BIT(reg)))
			जारी;

		prop = of_find_property(child, "phandle", शून्य);
		अगर (prop)
			of_हटाओ_property(child, prop);

		prop = of_find_property(child, "linux,phandle", शून्य);
		अगर (prop)
			of_हटाओ_property(child, prop);

		phydev = of_phy_find_device(child);
		अगर (phydev)
			phy_device_हटाओ(phydev);
	पूर्ण

	err = mdiobus_रेजिस्टर(priv->slave_mii_bus);
	अगर (err && dn)
		of_node_put(dn);

	वापस err;
पूर्ण

अटल व्योम bcm_sf2_mdio_unरेजिस्टर(काष्ठा bcm_sf2_priv *priv)
अणु
	mdiobus_unरेजिस्टर(priv->slave_mii_bus);
	of_node_put(priv->master_mii_dn);
पूर्ण

अटल u32 bcm_sf2_sw_get_phy_flags(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);

	/* The BCM7xxx PHY driver expects to find the पूर्णांकegrated PHY revision
	 * in bits 15:8 and the patch level in bits 7:0 which is exactly what
	 * the REG_PHY_REVISION रेजिस्टर layout is.
	 */
	अगर (priv->पूर्णांक_phy_mask & BIT(port))
		वापस priv->hw_params.gphy_rev;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम bcm_sf2_sw_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
				अचिन्हित दीर्घ *supported,
				काष्ठा phylink_link_state *state)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	अगर (!phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface) &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_MII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_REVMII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_GMII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_INTERNAL &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_MOCA) अणु
		biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
		अगर (port != core_पढ़ोl(priv, CORE_IMP0_PRT_ID))
			dev_err(ds->dev,
				"Unsupported interface: %d for port %d\n",
				state->पूर्णांकerface, port);
		वापस;
	पूर्ण

	/* Allow all the expected bits */
	phylink_set(mask, Autoneg);
	phylink_set_port_modes(mask);
	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);

	/* With the exclusion of MII and Reverse MII, we support Gigabit,
	 * including Half duplex
	 */
	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_MII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_REVMII) अणु
		phylink_set(mask, 1000baseT_Full);
		phylink_set(mask, 1000baseT_Half);
	पूर्ण

	phylink_set(mask, 10baseT_Half);
	phylink_set(mask, 10baseT_Full);
	phylink_set(mask, 100baseT_Half);
	phylink_set(mask, 100baseT_Full);

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल व्योम bcm_sf2_sw_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  अचिन्हित पूर्णांक mode,
				  स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 id_mode_dis = 0, port_mode;
	u32 reg_rgmii_ctrl;
	u32 reg;

	अगर (port == core_पढ़ोl(priv, CORE_IMP0_PRT_ID))
		वापस;

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		id_mode_dis = 1;
		fallthrough;
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		port_mode = EXT_GPHY;
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
		port_mode = EXT_EPHY;
		अवरोध;
	हाल PHY_INTERFACE_MODE_REVMII:
		port_mode = EXT_REVMII;
		अवरोध;
	शेष:
		/* Nothing required क्रम all other PHYs: पूर्णांकernal and MoCA */
		वापस;
	पूर्ण

	reg_rgmii_ctrl = bcm_sf2_reg_rgmii_cntrl(priv, port);

	/* Clear id_mode_dis bit, and the existing port mode, let
	 * RGMII_MODE_EN bet set by mac_link_अणुup,करोwnपूर्ण
	 */
	reg = reg_पढ़ोl(priv, reg_rgmii_ctrl);
	reg &= ~ID_MODE_DIS;
	reg &= ~(PORT_MODE_MASK << PORT_MODE_SHIFT);

	reg |= port_mode;
	अगर (id_mode_dis)
		reg |= ID_MODE_DIS;

	reg_ग_लिखोl(priv, reg, reg_rgmii_ctrl);
पूर्ण

अटल व्योम bcm_sf2_sw_mac_link_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    phy_पूर्णांकerface_t पूर्णांकerface, bool link)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 reg_rgmii_ctrl;
	u32 reg;

	अगर (!phy_पूर्णांकerface_mode_is_rgmii(पूर्णांकerface) &&
	    पूर्णांकerface != PHY_INTERFACE_MODE_MII &&
	    पूर्णांकerface != PHY_INTERFACE_MODE_REVMII)
		वापस;

	reg_rgmii_ctrl = bcm_sf2_reg_rgmii_cntrl(priv, port);

	/* If the link is करोwn, just disable the पूर्णांकerface to conserve घातer */
	reg = reg_पढ़ोl(priv, reg_rgmii_ctrl);
	अगर (link)
		reg |= RGMII_MODE_EN;
	अन्यथा
		reg &= ~RGMII_MODE_EN;
	reg_ग_लिखोl(priv, reg, reg_rgmii_ctrl);
पूर्ण

अटल व्योम bcm_sf2_sw_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     अचिन्हित पूर्णांक mode,
				     phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 reg, offset;

	अगर (port != core_पढ़ोl(priv, CORE_IMP0_PRT_ID)) अणु
		अगर (priv->type == BCM4908_DEVICE_ID ||
		    priv->type == BCM7445_DEVICE_ID)
			offset = CORE_STS_OVERRIDE_GMIIP_PORT(port);
		अन्यथा
			offset = CORE_STS_OVERRIDE_GMIIP2_PORT(port);

		reg = core_पढ़ोl(priv, offset);
		reg &= ~LINK_STS;
		core_ग_लिखोl(priv, reg, offset);
	पूर्ण

	bcm_sf2_sw_mac_link_set(ds, port, पूर्णांकerface, false);
पूर्ण

अटल व्योम bcm_sf2_sw_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   अचिन्हित पूर्णांक mode,
				   phy_पूर्णांकerface_t पूर्णांकerface,
				   काष्ठा phy_device *phydev,
				   पूर्णांक speed, पूर्णांक duplex,
				   bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	काष्ठा ethtool_eee *p = &priv->dev->ports[port].eee;

	bcm_sf2_sw_mac_link_set(ds, port, पूर्णांकerface, true);

	अगर (port != core_पढ़ोl(priv, CORE_IMP0_PRT_ID)) अणु
		u32 reg_rgmii_ctrl = 0;
		u32 reg, offset;

		अगर (priv->type == BCM4908_DEVICE_ID ||
		    priv->type == BCM7445_DEVICE_ID)
			offset = CORE_STS_OVERRIDE_GMIIP_PORT(port);
		अन्यथा
			offset = CORE_STS_OVERRIDE_GMIIP2_PORT(port);

		अगर (पूर्णांकerface == PHY_INTERFACE_MODE_RGMII ||
		    पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID ||
		    पूर्णांकerface == PHY_INTERFACE_MODE_MII ||
		    पूर्णांकerface == PHY_INTERFACE_MODE_REVMII) अणु
			reg_rgmii_ctrl = bcm_sf2_reg_rgmii_cntrl(priv, port);
			reg = reg_पढ़ोl(priv, reg_rgmii_ctrl);
			reg &= ~(RX_PAUSE_EN | TX_PAUSE_EN);

			अगर (tx_छोड़ो)
				reg |= TX_PAUSE_EN;
			अगर (rx_छोड़ो)
				reg |= RX_PAUSE_EN;

			reg_ग_लिखोl(priv, reg, reg_rgmii_ctrl);
		पूर्ण

		reg = SW_OVERRIDE | LINK_STS;
		चयन (speed) अणु
		हाल SPEED_1000:
			reg |= SPDSTS_1000 << SPEED_SHIFT;
			अवरोध;
		हाल SPEED_100:
			reg |= SPDSTS_100 << SPEED_SHIFT;
			अवरोध;
		पूर्ण

		अगर (duplex == DUPLEX_FULL)
			reg |= DUPLX_MODE;

		core_ग_लिखोl(priv, reg, offset);
	पूर्ण

	अगर (mode == MLO_AN_PHY && phydev)
		p->eee_enabled = b53_eee_init(ds, port, phydev);
पूर्ण

अटल व्योम bcm_sf2_sw_fixed_state(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   काष्ठा phylink_link_state *status)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);

	status->link = false;

	/* MoCA port is special as we करो not get link status from CORE_LNKSTS,
	 * which means that we need to क्रमce the link at the port override
	 * level to get the data to flow. We करो use what the पूर्णांकerrupt handler
	 * did determine beक्रमe.
	 *
	 * For the other ports, we just क्रमce the link status, since this is
	 * a fixed PHY device.
	 */
	अगर (port == priv->moca_port) अणु
		status->link = priv->port_sts[port].link;
		/* For MoCA पूर्णांकerfaces, also क्रमce a link करोwn notअगरication
		 * since some version of the user-space daemon (mocad) use
		 * cmd->स्वतःneg to क्रमce the link, which messes up the PHY
		 * state machine and make it go in PHY_FORCING state instead.
		 */
		अगर (!status->link)
			netअगर_carrier_off(dsa_to_port(ds, port)->slave);
		status->duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		status->link = true;
	पूर्ण
पूर्ण

अटल व्योम bcm_sf2_enable_acb(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 reg;

	/* Enable ACB globally */
	reg = acb_पढ़ोl(priv, ACB_CONTROL);
	reg |= (ACB_FLUSH_MASK << ACB_FLUSH_SHIFT);
	acb_ग_लिखोl(priv, reg, ACB_CONTROL);
	reg &= ~(ACB_FLUSH_MASK << ACB_FLUSH_SHIFT);
	reg |= ACB_EN | ACB_ALGORITHM;
	acb_ग_लिखोl(priv, reg, ACB_CONTROL);
पूर्ण

अटल पूर्णांक bcm_sf2_sw_suspend(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	अचिन्हित पूर्णांक port;

	bcm_sf2_पूर्णांकr_disable(priv);

	/* Disable all ports physically present including the IMP
	 * port, the other ones have alपढ़ोy been disabled during
	 * bcm_sf2_sw_setup
	 */
	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_is_user_port(ds, port) || dsa_is_cpu_port(ds, port))
			bcm_sf2_port_disable(ds, port);
	पूर्ण

	अगर (!priv->wol_ports_mask)
		clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sf2_sw_resume(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	पूर्णांक ret;

	अगर (!priv->wol_ports_mask)
		clk_prepare_enable(priv->clk);

	ret = bcm_sf2_sw_rst(priv);
	अगर (ret) अणु
		pr_err("%s: failed to software reset switch\n", __func__);
		वापस ret;
	पूर्ण

	bcm_sf2_crossbar_setup(priv);

	ret = bcm_sf2_cfp_resume(ds);
	अगर (ret)
		वापस ret;

	अगर (priv->hw_params.num_gphy == 1)
		bcm_sf2_gphy_enable_set(ds, true);

	ds->ops->setup(ds);

	वापस 0;
पूर्ण

अटल व्योम bcm_sf2_sw_get_wol(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा net_device *p = dsa_to_port(ds, port)->cpu_dp->master;
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	काष्ठा ethtool_wolinfo pwol = अणु पूर्ण;

	/* Get the parent device WoL settings */
	अगर (p->ethtool_ops->get_wol)
		p->ethtool_ops->get_wol(p, &pwol);

	/* Advertise the parent device supported settings */
	wol->supported = pwol.supported;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));

	अगर (pwol.wolopts & WAKE_MAGICSECURE)
		स_नकल(&wol->sopass, pwol.sopass, माप(wol->sopass));

	अगर (priv->wol_ports_mask & (1 << port))
		wol->wolopts = pwol.wolopts;
	अन्यथा
		wol->wolopts = 0;
पूर्ण

अटल पूर्णांक bcm_sf2_sw_set_wol(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा net_device *p = dsa_to_port(ds, port)->cpu_dp->master;
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	s8 cpu_port = dsa_to_port(ds, port)->cpu_dp->index;
	काष्ठा ethtool_wolinfo pwol =  अणु पूर्ण;

	अगर (p->ethtool_ops->get_wol)
		p->ethtool_ops->get_wol(p, &pwol);
	अगर (wol->wolopts & ~pwol.supported)
		वापस -EINVAL;

	अगर (wol->wolopts)
		priv->wol_ports_mask |= (1 << port);
	अन्यथा
		priv->wol_ports_mask &= ~(1 << port);

	/* If we have at least one port enabled, make sure the CPU port
	 * is also enabled. If the CPU port is the last one enabled, we disable
	 * it since this configuration करोes not make sense.
	 */
	अगर (priv->wol_ports_mask && priv->wol_ports_mask != (1 << cpu_port))
		priv->wol_ports_mask |= (1 << cpu_port);
	अन्यथा
		priv->wol_ports_mask &= ~(1 << cpu_port);

	वापस p->ethtool_ops->set_wol(p, wol);
पूर्ण

अटल पूर्णांक bcm_sf2_sw_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	अचिन्हित पूर्णांक port;

	/* Enable all valid ports and disable those unused */
	क्रम (port = 0; port < priv->hw_params.num_ports; port++) अणु
		/* IMP port receives special treaपंचांगent */
		अगर (dsa_is_user_port(ds, port))
			bcm_sf2_port_setup(ds, port, शून्य);
		अन्यथा अगर (dsa_is_cpu_port(ds, port))
			bcm_sf2_imp_setup(ds, port);
		अन्यथा
			bcm_sf2_port_disable(ds, port);
	पूर्ण

	b53_configure_vlan(ds);
	bcm_sf2_enable_acb(ds);

	वापस b53_setup_devlink_resources(ds);
पूर्ण

अटल व्योम bcm_sf2_sw_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	dsa_devlink_resources_unरेजिस्टर(ds);
पूर्ण

/* The SWITCH_CORE रेजिस्टर space is managed by b53 but operates on a page +
 * रेजिस्टर basis so we need to translate that पूर्णांकo an address that the
 * bus-glue understands.
 */
#घोषणा SF2_PAGE_REG_MKADDR(page, reg)	((page) << 10 | (reg) << 2)

अटल पूर्णांक bcm_sf2_core_पढ़ो8(काष्ठा b53_device *dev, u8 page, u8 reg,
			      u8 *val)
अणु
	काष्ठा bcm_sf2_priv *priv = dev->priv;

	*val = core_पढ़ोl(priv, SF2_PAGE_REG_MKADDR(page, reg));

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sf2_core_पढ़ो16(काष्ठा b53_device *dev, u8 page, u8 reg,
			       u16 *val)
अणु
	काष्ठा bcm_sf2_priv *priv = dev->priv;

	*val = core_पढ़ोl(priv, SF2_PAGE_REG_MKADDR(page, reg));

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sf2_core_पढ़ो32(काष्ठा b53_device *dev, u8 page, u8 reg,
			       u32 *val)
अणु
	काष्ठा bcm_sf2_priv *priv = dev->priv;

	*val = core_पढ़ोl(priv, SF2_PAGE_REG_MKADDR(page, reg));

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sf2_core_पढ़ो64(काष्ठा b53_device *dev, u8 page, u8 reg,
			       u64 *val)
अणु
	काष्ठा bcm_sf2_priv *priv = dev->priv;

	*val = core_पढ़ोq(priv, SF2_PAGE_REG_MKADDR(page, reg));

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sf2_core_ग_लिखो8(काष्ठा b53_device *dev, u8 page, u8 reg,
			       u8 value)
अणु
	काष्ठा bcm_sf2_priv *priv = dev->priv;

	core_ग_लिखोl(priv, value, SF2_PAGE_REG_MKADDR(page, reg));

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sf2_core_ग_लिखो16(काष्ठा b53_device *dev, u8 page, u8 reg,
				u16 value)
अणु
	काष्ठा bcm_sf2_priv *priv = dev->priv;

	core_ग_लिखोl(priv, value, SF2_PAGE_REG_MKADDR(page, reg));

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sf2_core_ग_लिखो32(काष्ठा b53_device *dev, u8 page, u8 reg,
				u32 value)
अणु
	काष्ठा bcm_sf2_priv *priv = dev->priv;

	core_ग_लिखोl(priv, value, SF2_PAGE_REG_MKADDR(page, reg));

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sf2_core_ग_लिखो64(काष्ठा b53_device *dev, u8 page, u8 reg,
				u64 value)
अणु
	काष्ठा bcm_sf2_priv *priv = dev->priv;

	core_ग_लिखोq(priv, value, SF2_PAGE_REG_MKADDR(page, reg));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा b53_io_ops bcm_sf2_io_ops = अणु
	.पढ़ो8	= bcm_sf2_core_पढ़ो8,
	.पढ़ो16	= bcm_sf2_core_पढ़ो16,
	.पढ़ो32	= bcm_sf2_core_पढ़ो32,
	.पढ़ो48	= bcm_sf2_core_पढ़ो64,
	.पढ़ो64	= bcm_sf2_core_पढ़ो64,
	.ग_लिखो8	= bcm_sf2_core_ग_लिखो8,
	.ग_लिखो16 = bcm_sf2_core_ग_लिखो16,
	.ग_लिखो32 = bcm_sf2_core_ग_लिखो32,
	.ग_लिखो48 = bcm_sf2_core_ग_लिखो64,
	.ग_लिखो64 = bcm_sf2_core_ग_लिखो64,
पूर्ण;

अटल व्योम bcm_sf2_sw_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   u32 stringset, uपूर्णांक8_t *data)
अणु
	पूर्णांक cnt = b53_get_sset_count(ds, port, stringset);

	b53_get_strings(ds, port, stringset, data);
	bcm_sf2_cfp_get_strings(ds, port, stringset,
				data + cnt * ETH_GSTRING_LEN);
पूर्ण

अटल व्योम bcm_sf2_sw_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 uपूर्णांक64_t *data)
अणु
	पूर्णांक cnt = b53_get_sset_count(ds, port, ETH_SS_STATS);

	b53_get_ethtool_stats(ds, port, data);
	bcm_sf2_cfp_get_ethtool_stats(ds, port, data + cnt);
पूर्ण

अटल पूर्णांक bcm_sf2_sw_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     पूर्णांक sset)
अणु
	पूर्णांक cnt = b53_get_sset_count(ds, port, sset);

	अगर (cnt < 0)
		वापस cnt;

	cnt += bcm_sf2_cfp_get_sset_count(ds, port, sset);

	वापस cnt;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops bcm_sf2_ops = अणु
	.get_tag_protocol	= b53_get_tag_protocol,
	.setup			= bcm_sf2_sw_setup,
	.tearकरोwn		= bcm_sf2_sw_tearकरोwn,
	.get_strings		= bcm_sf2_sw_get_strings,
	.get_ethtool_stats	= bcm_sf2_sw_get_ethtool_stats,
	.get_sset_count		= bcm_sf2_sw_get_sset_count,
	.get_ethtool_phy_stats	= b53_get_ethtool_phy_stats,
	.get_phy_flags		= bcm_sf2_sw_get_phy_flags,
	.phylink_validate	= bcm_sf2_sw_validate,
	.phylink_mac_config	= bcm_sf2_sw_mac_config,
	.phylink_mac_link_करोwn	= bcm_sf2_sw_mac_link_करोwn,
	.phylink_mac_link_up	= bcm_sf2_sw_mac_link_up,
	.phylink_fixed_state	= bcm_sf2_sw_fixed_state,
	.suspend		= bcm_sf2_sw_suspend,
	.resume			= bcm_sf2_sw_resume,
	.get_wol		= bcm_sf2_sw_get_wol,
	.set_wol		= bcm_sf2_sw_set_wol,
	.port_enable		= bcm_sf2_port_setup,
	.port_disable		= bcm_sf2_port_disable,
	.get_mac_eee		= b53_get_mac_eee,
	.set_mac_eee		= b53_set_mac_eee,
	.port_bridge_join	= b53_br_join,
	.port_bridge_leave	= b53_br_leave,
	.port_pre_bridge_flags	= b53_br_flags_pre,
	.port_bridge_flags	= b53_br_flags,
	.port_stp_state_set	= b53_br_set_stp_state,
	.port_set_mrouter	= b53_set_mrouter,
	.port_fast_age		= b53_br_fast_age,
	.port_vlan_filtering	= b53_vlan_filtering,
	.port_vlan_add		= b53_vlan_add,
	.port_vlan_del		= b53_vlan_del,
	.port_fdb_dump		= b53_fdb_dump,
	.port_fdb_add		= b53_fdb_add,
	.port_fdb_del		= b53_fdb_del,
	.get_rxnfc		= bcm_sf2_get_rxnfc,
	.set_rxnfc		= bcm_sf2_set_rxnfc,
	.port_mirror_add	= b53_mirror_add,
	.port_mirror_del	= b53_mirror_del,
	.port_mdb_add		= b53_mdb_add,
	.port_mdb_del		= b53_mdb_del,
पूर्ण;

काष्ठा bcm_sf2_of_data अणु
	u32 type;
	स्थिर u16 *reg_offsets;
	अचिन्हित पूर्णांक core_reg_align;
	अचिन्हित पूर्णांक num_cfp_rules;
	अचिन्हित पूर्णांक num_crossbar_पूर्णांक_ports;
पूर्ण;

अटल स्थिर u16 bcm_sf2_4908_reg_offsets[] = अणु
	[REG_SWITCH_CNTRL]	= 0x00,
	[REG_SWITCH_STATUS]	= 0x04,
	[REG_सूची_DATA_WRITE]	= 0x08,
	[REG_सूची_DATA_READ]	= 0x0c,
	[REG_SWITCH_REVISION]	= 0x10,
	[REG_PHY_REVISION]	= 0x14,
	[REG_SPHY_CNTRL]	= 0x24,
	[REG_CROSSBAR]		= 0xc8,
	[REG_RGMII_11_CNTRL]	= 0x014c,
	[REG_LED_0_CNTRL]	= 0x40,
	[REG_LED_1_CNTRL]	= 0x4c,
	[REG_LED_2_CNTRL]	= 0x58,
पूर्ण;

अटल स्थिर काष्ठा bcm_sf2_of_data bcm_sf2_4908_data = अणु
	.type		= BCM4908_DEVICE_ID,
	.core_reg_align	= 0,
	.reg_offsets	= bcm_sf2_4908_reg_offsets,
	.num_cfp_rules	= 256,
	.num_crossbar_पूर्णांक_ports = 2,
पूर्ण;

/* Register offsets क्रम the SWITCH_REG_* block */
अटल स्थिर u16 bcm_sf2_7445_reg_offsets[] = अणु
	[REG_SWITCH_CNTRL]	= 0x00,
	[REG_SWITCH_STATUS]	= 0x04,
	[REG_सूची_DATA_WRITE]	= 0x08,
	[REG_सूची_DATA_READ]	= 0x0C,
	[REG_SWITCH_REVISION]	= 0x18,
	[REG_PHY_REVISION]	= 0x1C,
	[REG_SPHY_CNTRL]	= 0x2C,
	[REG_RGMII_0_CNTRL]	= 0x34,
	[REG_RGMII_1_CNTRL]	= 0x40,
	[REG_RGMII_2_CNTRL]	= 0x4c,
	[REG_LED_0_CNTRL]	= 0x90,
	[REG_LED_1_CNTRL]	= 0x94,
	[REG_LED_2_CNTRL]	= 0x98,
पूर्ण;

अटल स्थिर काष्ठा bcm_sf2_of_data bcm_sf2_7445_data = अणु
	.type		= BCM7445_DEVICE_ID,
	.core_reg_align	= 0,
	.reg_offsets	= bcm_sf2_7445_reg_offsets,
	.num_cfp_rules	= 256,
पूर्ण;

अटल स्थिर u16 bcm_sf2_7278_reg_offsets[] = अणु
	[REG_SWITCH_CNTRL]	= 0x00,
	[REG_SWITCH_STATUS]	= 0x04,
	[REG_सूची_DATA_WRITE]	= 0x08,
	[REG_सूची_DATA_READ]	= 0x0c,
	[REG_SWITCH_REVISION]	= 0x10,
	[REG_PHY_REVISION]	= 0x14,
	[REG_SPHY_CNTRL]	= 0x24,
	[REG_RGMII_0_CNTRL]	= 0xe0,
	[REG_RGMII_1_CNTRL]	= 0xec,
	[REG_RGMII_2_CNTRL]	= 0xf8,
	[REG_LED_0_CNTRL]	= 0x40,
	[REG_LED_1_CNTRL]	= 0x4c,
	[REG_LED_2_CNTRL]	= 0x58,
पूर्ण;

अटल स्थिर काष्ठा bcm_sf2_of_data bcm_sf2_7278_data = अणु
	.type		= BCM7278_DEVICE_ID,
	.core_reg_align	= 1,
	.reg_offsets	= bcm_sf2_7278_reg_offsets,
	.num_cfp_rules	= 128,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm_sf2_of_match[] = अणु
	अणु .compatible = "brcm,bcm4908-switch",
	  .data = &bcm_sf2_4908_data
	पूर्ण,
	अणु .compatible = "brcm,bcm7445-switch-v4.0",
	  .data = &bcm_sf2_7445_data
	पूर्ण,
	अणु .compatible = "brcm,bcm7278-switch-v4.0",
	  .data = &bcm_sf2_7278_data
	पूर्ण,
	अणु .compatible = "brcm,bcm7278-switch-v4.8",
	  .data = &bcm_sf2_7278_data
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_sf2_of_match);

अटल पूर्णांक bcm_sf2_sw_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *reg_names[BCM_SF2_REGS_NUM] = BCM_SF2_REGS_NAME;
	काष्ठा device_node *dn = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id = शून्य;
	स्थिर काष्ठा bcm_sf2_of_data *data;
	काष्ठा b53_platक्रमm_data *pdata;
	काष्ठा dsa_चयन_ops *ops;
	काष्ठा device_node *ports;
	काष्ठा bcm_sf2_priv *priv;
	काष्ठा b53_device *dev;
	काष्ठा dsa_चयन *ds;
	व्योम __iomem **base;
	अचिन्हित पूर्णांक i;
	u32 reg, rev;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ops = devm_kzalloc(&pdev->dev, माप(*ops), GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	dev = b53_चयन_alloc(&pdev->dev, &bcm_sf2_io_ops, priv);
	अगर (!dev)
		वापस -ENOMEM;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	of_id = of_match_node(bcm_sf2_of_match, dn);
	अगर (!of_id || !of_id->data)
		वापस -EINVAL;

	data = of_id->data;

	/* Set SWITCH_REG रेजिस्टर offsets and SWITCH_CORE align factor */
	priv->type = data->type;
	priv->reg_offsets = data->reg_offsets;
	priv->core_reg_align = data->core_reg_align;
	priv->num_cfp_rules = data->num_cfp_rules;
	priv->num_crossbar_पूर्णांक_ports = data->num_crossbar_पूर्णांक_ports;

	priv->rcdev = devm_reset_control_get_optional_exclusive(&pdev->dev,
								"switch");
	अगर (IS_ERR(priv->rcdev))
		वापस PTR_ERR(priv->rcdev);

	/* Auto-detection using standard रेजिस्टरs will not work, so
	 * provide an indication of what kind of device we are क्रम
	 * b53_common to work with
	 */
	pdata->chip_id = priv->type;
	dev->pdata = pdata;

	priv->dev = dev;
	ds = dev->ds;
	ds->ops = &bcm_sf2_ops;

	/* Advertise the 8 egress queues */
	ds->num_tx_queues = SF2_NUM_EGRESS_QUEUES;

	dev_set_drvdata(&pdev->dev, priv);

	spin_lock_init(&priv->indir_lock);
	mutex_init(&priv->cfp.lock);
	INIT_LIST_HEAD(&priv->cfp.rules_list);

	/* CFP rule #0 cannot be used क्रम specअगरic classअगरications, flag it as
	 * permanently used
	 */
	set_bit(0, priv->cfp.used);
	set_bit(0, priv->cfp.unique);

	/* Balance of_node_put() करोne by of_find_node_by_name() */
	of_node_get(dn);
	ports = of_find_node_by_name(dn, "ports");
	अगर (ports) अणु
		bcm_sf2_identअगरy_ports(priv, ports);
		of_node_put(ports);
	पूर्ण

	priv->irq0 = irq_of_parse_and_map(dn, 0);
	priv->irq1 = irq_of_parse_and_map(dn, 1);

	base = &priv->core;
	क्रम (i = 0; i < BCM_SF2_REGS_NUM; i++) अणु
		*base = devm_platक्रमm_ioremap_resource(pdev, i);
		अगर (IS_ERR(*base)) अणु
			pr_err("unable to find register: %s\n", reg_names[i]);
			वापस PTR_ERR(*base);
		पूर्ण
		base++;
	पूर्ण

	priv->clk = devm_clk_get_optional(&pdev->dev, "sw_switch");
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	clk_prepare_enable(priv->clk);

	priv->clk_mभाग = devm_clk_get_optional(&pdev->dev, "sw_switch_mdiv");
	अगर (IS_ERR(priv->clk_mभाग)) अणु
		ret = PTR_ERR(priv->clk_mभाग);
		जाओ out_clk;
	पूर्ण

	clk_prepare_enable(priv->clk_mभाग);

	ret = bcm_sf2_sw_rst(priv);
	अगर (ret) अणु
		pr_err("unable to software reset switch: %d\n", ret);
		जाओ out_clk_mभाग;
	पूर्ण

	bcm_sf2_crossbar_setup(priv);

	bcm_sf2_gphy_enable_set(priv->dev->ds, true);

	ret = bcm_sf2_mdio_रेजिस्टर(ds);
	अगर (ret) अणु
		pr_err("failed to register MDIO bus\n");
		जाओ out_clk_mभाग;
	पूर्ण

	bcm_sf2_gphy_enable_set(priv->dev->ds, false);

	ret = bcm_sf2_cfp_rst(priv);
	अगर (ret) अणु
		pr_err("failed to reset CFP\n");
		जाओ out_mdio;
	पूर्ण

	/* Disable all पूर्णांकerrupts and request them */
	bcm_sf2_पूर्णांकr_disable(priv);

	ret = devm_request_irq(&pdev->dev, priv->irq0, bcm_sf2_चयन_0_isr, 0,
			       "switch_0", ds);
	अगर (ret < 0) अणु
		pr_err("failed to request switch_0 IRQ\n");
		जाओ out_mdio;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, priv->irq1, bcm_sf2_चयन_1_isr, 0,
			       "switch_1", ds);
	अगर (ret < 0) अणु
		pr_err("failed to request switch_1 IRQ\n");
		जाओ out_mdio;
	पूर्ण

	/* Reset the MIB counters */
	reg = core_पढ़ोl(priv, CORE_GMNCFGCFG);
	reg |= RST_MIB_CNT;
	core_ग_लिखोl(priv, reg, CORE_GMNCFGCFG);
	reg &= ~RST_MIB_CNT;
	core_ग_लिखोl(priv, reg, CORE_GMNCFGCFG);

	/* Get the maximum number of ports क्रम this चयन */
	priv->hw_params.num_ports = core_पढ़ोl(priv, CORE_IMP0_PRT_ID) + 1;
	अगर (priv->hw_params.num_ports > DSA_MAX_PORTS)
		priv->hw_params.num_ports = DSA_MAX_PORTS;

	/* Assume a single GPHY setup अगर we can't पढ़ो that property */
	अगर (of_property_पढ़ो_u32(dn, "brcm,num-gphy",
				 &priv->hw_params.num_gphy))
		priv->hw_params.num_gphy = 1;

	rev = reg_पढ़ोl(priv, REG_SWITCH_REVISION);
	priv->hw_params.top_rev = (rev >> SWITCH_TOP_REV_SHIFT) &
					SWITCH_TOP_REV_MASK;
	priv->hw_params.core_rev = (rev & SF2_REV_MASK);

	rev = reg_पढ़ोl(priv, REG_PHY_REVISION);
	priv->hw_params.gphy_rev = rev & PHY_REVISION_MASK;

	ret = b53_चयन_रेजिस्टर(dev);
	अगर (ret)
		जाओ out_mdio;

	dev_info(&pdev->dev,
		 "Starfighter 2 top: %x.%02x, core: %x.%02x, IRQs: %d, %d\n",
		 priv->hw_params.top_rev >> 8, priv->hw_params.top_rev & 0xff,
		 priv->hw_params.core_rev >> 8, priv->hw_params.core_rev & 0xff,
		 priv->irq0, priv->irq1);

	वापस 0;

out_mdio:
	bcm_sf2_mdio_unरेजिस्टर(priv);
out_clk_mभाग:
	clk_disable_unprepare(priv->clk_mभाग);
out_clk:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm_sf2_sw_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_sf2_priv *priv = platक्रमm_get_drvdata(pdev);

	priv->wol_ports_mask = 0;
	/* Disable पूर्णांकerrupts */
	bcm_sf2_पूर्णांकr_disable(priv);
	dsa_unरेजिस्टर_चयन(priv->dev->ds);
	bcm_sf2_cfp_निकास(priv->dev->ds);
	bcm_sf2_mdio_unरेजिस्टर(priv);
	clk_disable_unprepare(priv->clk_mभाग);
	clk_disable_unprepare(priv->clk);
	अगर (priv->type == BCM7278_DEVICE_ID)
		reset_control_निश्चित(priv->rcdev);

	वापस 0;
पूर्ण

अटल व्योम bcm_sf2_sw_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_sf2_priv *priv = platक्रमm_get_drvdata(pdev);

	/* For a kernel about to be kexec'd we want to keep the GPHY on क्रम a
	 * successful MDIO bus scan to occur. If we did turn off the GPHY
	 * beक्रमe (e.g: port_disable), this will also घातer it back on.
	 *
	 * Do not rely on kexec_in_progress, just घातer the PHY on.
	 */
	अगर (priv->hw_params.num_gphy == 1)
		bcm_sf2_gphy_enable_set(priv->dev->ds, true);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bcm_sf2_suspend(काष्ठा device *dev)
अणु
	काष्ठा bcm_sf2_priv *priv = dev_get_drvdata(dev);

	वापस dsa_चयन_suspend(priv->dev->ds);
पूर्ण

अटल पूर्णांक bcm_sf2_resume(काष्ठा device *dev)
अणु
	काष्ठा bcm_sf2_priv *priv = dev_get_drvdata(dev);

	वापस dsa_चयन_resume(priv->dev->ds);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(bcm_sf2_pm_ops,
			 bcm_sf2_suspend, bcm_sf2_resume);


अटल काष्ठा platक्रमm_driver bcm_sf2_driver = अणु
	.probe	= bcm_sf2_sw_probe,
	.हटाओ	= bcm_sf2_sw_हटाओ,
	.shutकरोwn = bcm_sf2_sw_shutकरोwn,
	.driver = अणु
		.name = "brcm-sf2",
		.of_match_table = bcm_sf2_of_match,
		.pm = &bcm_sf2_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm_sf2_driver);

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("Driver for Broadcom Starfighter 2 ethernet switch chip");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:brcm-sf2");
