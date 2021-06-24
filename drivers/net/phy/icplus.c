<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम ICPlus PHYs
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>
#समावेश <linux/property.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

MODULE_DESCRIPTION("ICPlus IP175C/IP101A/IP101G/IC1001 PHY drivers");
MODULE_AUTHOR("Michael Barkowski");
MODULE_LICENSE("GPL");

/* IP101A/G - IP1001 */
#घोषणा IP10XX_SPEC_CTRL_STATUS		16	/* Spec. Control Register */
#घोषणा IP1001_RXPHASE_SEL		BIT(0)	/* Add delay on RX_CLK */
#घोषणा IP1001_TXPHASE_SEL		BIT(1)	/* Add delay on TX_CLK */
#घोषणा IP1001_SPEC_CTRL_STATUS_2	20	/* IP1001 Spec. Control Reg 2 */
#घोषणा IP1001_APS_ON			11	/* IP1001 APS Mode  bit */
#घोषणा IP101A_G_APS_ON			BIT(1)	/* IP101A/G APS Mode bit */
#घोषणा IP101A_G_AUTO_MDIX_DIS		BIT(11)
#घोषणा IP101A_G_IRQ_CONF_STATUS	0x11	/* Conf Info IRQ & Status Reg */
#घोषणा	IP101A_G_IRQ_PIN_USED		BIT(15) /* INTR pin used */
#घोषणा IP101A_G_IRQ_ALL_MASK		BIT(11) /* IRQ's inactive */
#घोषणा IP101A_G_IRQ_SPEED_CHANGE	BIT(2)
#घोषणा IP101A_G_IRQ_DUPLEX_CHANGE	BIT(1)
#घोषणा IP101A_G_IRQ_LINK_CHANGE	BIT(0)
#घोषणा IP101A_G_PHY_STATUS		18
#घोषणा IP101A_G_MDIX			BIT(9)
#घोषणा IP101A_G_PHY_SPEC_CTRL		30
#घोषणा IP101A_G_FORCE_MDIX		BIT(3)

#घोषणा IP101G_PAGE_CONTROL				0x14
#घोषणा IP101G_PAGE_CONTROL_MASK			GENMASK(4, 0)
#घोषणा IP101G_DIGITAL_IO_SPEC_CTRL			0x1d
#घोषणा IP101G_DIGITAL_IO_SPEC_CTRL_SEL_INTR32		BIT(2)

#घोषणा IP101G_DEFAULT_PAGE			16

#घोषणा IP101G_P1_CNT_CTRL		17
#घोषणा CNT_CTRL_RX_EN			BIT(13)
#घोषणा IP101G_P8_CNT_CTRL		17
#घोषणा CNT_CTRL_RDCLR_EN		BIT(15)
#घोषणा IP101G_CNT_REG			18

#घोषणा IP175C_PHY_ID 0x02430d80
#घोषणा IP1001_PHY_ID 0x02430d90
#घोषणा IP101A_PHY_ID 0x02430c54

/* The 32-pin IP101GR package can re-configure the mode of the RXER/INTR_32 pin
 * (pin number 21). The hardware शेष is RXER (receive error) mode. But it
 * can be configured to पूर्णांकerrupt mode manually.
 */
क्रमागत ip101gr_sel_पूर्णांकr32 अणु
	IP101GR_SEL_INTR32_KEEP,
	IP101GR_SEL_INTR32_INTR,
	IP101GR_SEL_INTR32_RXER,
पूर्ण;

काष्ठा ip101g_hw_stat अणु
	स्थिर अक्षर *name;
	पूर्णांक page;
पूर्ण;

अटल काष्ठा ip101g_hw_stat ip101g_hw_stats[] = अणु
	अणु "phy_crc_errors", 1 पूर्ण,
	अणु "phy_symbol_errors", 11, पूर्ण,
पूर्ण;

काष्ठा ip101a_g_phy_priv अणु
	क्रमागत ip101gr_sel_पूर्णांकr32 sel_पूर्णांकr32;
	u64 stats[ARRAY_SIZE(ip101g_hw_stats)];
पूर्ण;

अटल पूर्णांक ip175c_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err, i;
	अटल पूर्णांक full_reset_perक्रमmed;

	अगर (full_reset_perक्रमmed == 0) अणु

		/* master reset */
		err = mdiobus_ग_लिखो(phydev->mdio.bus, 30, 0, 0x175c);
		अगर (err < 0)
			वापस err;

		/* ensure no bus delays overlap reset period */
		err = mdiobus_पढ़ो(phydev->mdio.bus, 30, 0);

		/* data sheet specअगरies reset period is 2 msec */
		mdelay(2);

		/* enable IP175C mode */
		err = mdiobus_ग_लिखो(phydev->mdio.bus, 29, 31, 0x175c);
		अगर (err < 0)
			वापस err;

		/* Set MII0 speed and duplex (in PHY mode) */
		err = mdiobus_ग_लिखो(phydev->mdio.bus, 29, 22, 0x420);
		अगर (err < 0)
			वापस err;

		/* reset चयन ports */
		क्रम (i = 0; i < 5; i++) अणु
			err = mdiobus_ग_लिखो(phydev->mdio.bus, i,
					    MII_BMCR, BMCR_RESET);
			अगर (err < 0)
				वापस err;
		पूर्ण

		क्रम (i = 0; i < 5; i++)
			err = mdiobus_पढ़ो(phydev->mdio.bus, i, MII_BMCR);

		mdelay(2);

		full_reset_perक्रमmed = 1;
	पूर्ण

	अगर (phydev->mdio.addr != 4) अणु
		phydev->state = PHY_RUNNING;
		phydev->speed = SPEED_100;
		phydev->duplex = DUPLEX_FULL;
		phydev->link = 1;
		netअगर_carrier_on(phydev->attached_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ip1001_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक c;

	/* Enable Auto Power Saving mode */
	c = phy_पढ़ो(phydev, IP1001_SPEC_CTRL_STATUS_2);
	अगर (c < 0)
		वापस c;
	c |= IP1001_APS_ON;
	c = phy_ग_लिखो(phydev, IP1001_SPEC_CTRL_STATUS_2, c);
	अगर (c < 0)
		वापस c;

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु

		c = phy_पढ़ो(phydev, IP10XX_SPEC_CTRL_STATUS);
		अगर (c < 0)
			वापस c;

		c &= ~(IP1001_RXPHASE_SEL | IP1001_TXPHASE_SEL);

		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID)
			c |= (IP1001_RXPHASE_SEL | IP1001_TXPHASE_SEL);
		अन्यथा अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID)
			c |= IP1001_RXPHASE_SEL;
		अन्यथा अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)
			c |= IP1001_TXPHASE_SEL;

		c = phy_ग_लिखो(phydev, IP10XX_SPEC_CTRL_STATUS, c);
		अगर (c < 0)
			वापस c;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ip175c_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->mdio.addr == 4) /* WAN port */
		genphy_पढ़ो_status(phydev);
	अन्यथा
		/* Don't need to पढ़ो status क्रम चयन ports */
		phydev->irq = PHY_MAC_INTERRUPT;

	वापस 0;
पूर्ण

अटल पूर्णांक ip175c_config_aneg(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->mdio.addr == 4) /* WAN port */
		genphy_config_aneg(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक ip101a_g_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा ip101a_g_phy_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Both functions (RX error and पूर्णांकerrupt status) are sharing the same
	 * pin on the 32-pin IP101GR, so this is an exclusive choice.
	 */
	अगर (device_property_पढ़ो_bool(dev, "icplus,select-rx-error") &&
	    device_property_पढ़ो_bool(dev, "icplus,select-interrupt")) अणु
		dev_err(dev,
			"RXER and INTR mode cannot be selected together\n");
		वापस -EINVAL;
	पूर्ण

	अगर (device_property_पढ़ो_bool(dev, "icplus,select-rx-error"))
		priv->sel_पूर्णांकr32 = IP101GR_SEL_INTR32_RXER;
	अन्यथा अगर (device_property_पढ़ो_bool(dev, "icplus,select-interrupt"))
		priv->sel_पूर्णांकr32 = IP101GR_SEL_INTR32_INTR;
	अन्यथा
		priv->sel_पूर्णांकr32 = IP101GR_SEL_INTR32_KEEP;

	phydev->priv = priv;

	वापस 0;
पूर्ण

अटल पूर्णांक ip101a_g_config_पूर्णांकr_pin(काष्ठा phy_device *phydev)
अणु
	काष्ठा ip101a_g_phy_priv *priv = phydev->priv;
	पूर्णांक oldpage, err = 0;

	oldpage = phy_select_page(phydev, IP101G_DEFAULT_PAGE);
	अगर (oldpage < 0)
		जाओ out;

	/* configure the RXER/INTR_32 pin of the 32-pin IP101GR अगर needed: */
	चयन (priv->sel_पूर्णांकr32) अणु
	हाल IP101GR_SEL_INTR32_RXER:
		err = __phy_modअगरy(phydev, IP101G_DIGITAL_IO_SPEC_CTRL,
				   IP101G_DIGITAL_IO_SPEC_CTRL_SEL_INTR32, 0);
		अगर (err < 0)
			जाओ out;
		अवरोध;

	हाल IP101GR_SEL_INTR32_INTR:
		err = __phy_modअगरy(phydev, IP101G_DIGITAL_IO_SPEC_CTRL,
				   IP101G_DIGITAL_IO_SPEC_CTRL_SEL_INTR32,
				   IP101G_DIGITAL_IO_SPEC_CTRL_SEL_INTR32);
		अगर (err < 0)
			जाओ out;
		अवरोध;

	शेष:
		/* Don't touch IP101G_DIGITAL_IO_SPEC_CTRL because it's not
		 * करोcumented on IP101A and it's not clear whether this would
		 * cause problems.
		 * For the 32-pin IP101GR we simply keep the SEL_INTR32
		 * configuration as set by the bootloader when not configured
		 * to one of the special functions.
		 */
		अवरोध;
	पूर्ण

out:
	वापस phy_restore_page(phydev, oldpage, err);
पूर्ण

अटल पूर्णांक ip101a_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Enable Auto Power Saving mode */
	ret = phy_set_bits(phydev, IP10XX_SPEC_CTRL_STATUS, IP101A_G_APS_ON);
	अगर (ret)
		वापस ret;

	वापस ip101a_g_config_पूर्णांकr_pin(phydev);
पूर्ण

अटल पूर्णांक ip101g_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Enable the PHY counters */
	ret = phy_modअगरy_paged(phydev, 1, IP101G_P1_CNT_CTRL,
			       CNT_CTRL_RX_EN, CNT_CTRL_RX_EN);
	अगर (ret)
		वापस ret;

	/* Clear error counters on पढ़ो */
	ret = phy_modअगरy_paged(phydev, 8, IP101G_P8_CNT_CTRL,
			       CNT_CTRL_RDCLR_EN, CNT_CTRL_RDCLR_EN);
	अगर (ret)
		वापस ret;

	वापस ip101a_g_config_पूर्णांकr_pin(phydev);
पूर्ण

अटल पूर्णांक ip101a_g_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक oldpage, ret, stat1, stat2;

	ret = genphy_पढ़ो_status(phydev);
	अगर (ret)
		वापस ret;

	oldpage = phy_select_page(phydev, IP101G_DEFAULT_PAGE);
	अगर (oldpage < 0)
		जाओ out;

	ret = __phy_पढ़ो(phydev, IP10XX_SPEC_CTRL_STATUS);
	अगर (ret < 0)
		जाओ out;
	stat1 = ret;

	ret = __phy_पढ़ो(phydev, IP101A_G_PHY_SPEC_CTRL);
	अगर (ret < 0)
		जाओ out;
	stat2 = ret;

	अगर (stat1 & IP101A_G_AUTO_MDIX_DIS) अणु
		अगर (stat2 & IP101A_G_FORCE_MDIX)
			phydev->mdix_ctrl = ETH_TP_MDI_X;
		अन्यथा
			phydev->mdix_ctrl = ETH_TP_MDI;
	पूर्ण अन्यथा अणु
		phydev->mdix_ctrl = ETH_TP_MDI_AUTO;
	पूर्ण

	अगर (stat2 & IP101A_G_MDIX)
		phydev->mdix = ETH_TP_MDI_X;
	अन्यथा
		phydev->mdix = ETH_TP_MDI;

	ret = 0;

out:
	वापस phy_restore_page(phydev, oldpage, ret);
पूर्ण

अटल पूर्णांक ip101a_g_config_mdix(काष्ठा phy_device *phydev)
अणु
	u16 ctrl = 0, ctrl2 = 0;
	पूर्णांक oldpage;
	पूर्णांक ret = 0;

	चयन (phydev->mdix_ctrl) अणु
	हाल ETH_TP_MDI:
		ctrl = IP101A_G_AUTO_MDIX_DIS;
		अवरोध;
	हाल ETH_TP_MDI_X:
		ctrl = IP101A_G_AUTO_MDIX_DIS;
		ctrl2 = IP101A_G_FORCE_MDIX;
		अवरोध;
	हाल ETH_TP_MDI_AUTO:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	oldpage = phy_select_page(phydev, IP101G_DEFAULT_PAGE);
	अगर (oldpage < 0)
		जाओ out;

	ret = __phy_modअगरy(phydev, IP10XX_SPEC_CTRL_STATUS,
			   IP101A_G_AUTO_MDIX_DIS, ctrl);
	अगर (ret)
		जाओ out;

	ret = __phy_modअगरy(phydev, IP101A_G_PHY_SPEC_CTRL,
			   IP101A_G_FORCE_MDIX, ctrl2);

out:
	वापस phy_restore_page(phydev, oldpage, ret);
पूर्ण

अटल पूर्णांक ip101a_g_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = ip101a_g_config_mdix(phydev);
	अगर (ret)
		वापस ret;

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक ip101a_g_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_पढ़ो_paged(phydev, IP101G_DEFAULT_PAGE,
			     IP101A_G_IRQ_CONF_STATUS);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ip101a_g_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	u16 val;
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = ip101a_g_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		/* INTR pin used: Speed/link/duplex will cause an पूर्णांकerrupt */
		val = IP101A_G_IRQ_PIN_USED;
		err = phy_ग_लिखो_paged(phydev, IP101G_DEFAULT_PAGE,
				      IP101A_G_IRQ_CONF_STATUS, val);
	पूर्ण अन्यथा अणु
		val = IP101A_G_IRQ_ALL_MASK;
		err = phy_ग_लिखो_paged(phydev, IP101G_DEFAULT_PAGE,
				      IP101A_G_IRQ_CONF_STATUS, val);
		अगर (err)
			वापस err;

		err = ip101a_g_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t ip101a_g_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो_paged(phydev, IP101G_DEFAULT_PAGE,
				    IP101A_G_IRQ_CONF_STATUS);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & (IP101A_G_IRQ_SPEED_CHANGE |
			    IP101A_G_IRQ_DUPLEX_CHANGE |
			    IP101A_G_IRQ_LINK_CHANGE)))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

/* The IP101A करोesn't really have a page रेजिस्टर. We just pretend to have one
 * so we can use the paged versions of the callbacks of the IP101G.
 */
अटल पूर्णांक ip101a_पढ़ो_page(काष्ठा phy_device *phydev)
अणु
	वापस IP101G_DEFAULT_PAGE;
पूर्ण

अटल पूर्णांक ip101a_ग_लिखो_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	WARN_ONCE(page != IP101G_DEFAULT_PAGE, "wrong page selected\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ip101g_पढ़ो_page(काष्ठा phy_device *phydev)
अणु
	वापस __phy_पढ़ो(phydev, IP101G_PAGE_CONTROL);
पूर्ण

अटल पूर्णांक ip101g_ग_लिखो_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	वापस __phy_ग_लिखो(phydev, IP101G_PAGE_CONTROL, page);
पूर्ण

अटल पूर्णांक ip101a_g_has_page_रेजिस्टर(काष्ठा phy_device *phydev)
अणु
	पूर्णांक oldval, val, ret;

	oldval = phy_पढ़ो(phydev, IP101G_PAGE_CONTROL);
	अगर (oldval < 0)
		वापस oldval;

	ret = phy_ग_लिखो(phydev, IP101G_PAGE_CONTROL, 0xffff);
	अगर (ret)
		वापस ret;

	val = phy_पढ़ो(phydev, IP101G_PAGE_CONTROL);
	अगर (val < 0)
		वापस val;

	ret = phy_ग_लिखो(phydev, IP101G_PAGE_CONTROL, oldval);
	अगर (ret)
		वापस ret;

	वापस val == IP101G_PAGE_CONTROL_MASK;
पूर्ण

अटल पूर्णांक ip101a_g_match_phy_device(काष्ठा phy_device *phydev, bool ip101a)
अणु
	पूर्णांक ret;

	अगर (phydev->phy_id != IP101A_PHY_ID)
		वापस 0;

	/* The IP101A and the IP101G share the same PHY identअगरier.The IP101G
	 * seems to be a successor of the IP101A and implements more functions.
	 * Amongst other things there is a page select रेजिस्टर, which is not
	 * available on the IP101A. Use this to distinguish these two.
	 */
	ret = ip101a_g_has_page_रेजिस्टर(phydev);
	अगर (ret < 0)
		वापस ret;

	वापस ip101a == !ret;
पूर्ण

अटल पूर्णांक ip101a_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस ip101a_g_match_phy_device(phydev, true);
पूर्ण

अटल पूर्णांक ip101g_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस ip101a_g_match_phy_device(phydev, false);
पूर्ण

अटल पूर्णांक ip101g_get_sset_count(काष्ठा phy_device *phydev)
अणु
	वापस ARRAY_SIZE(ip101g_hw_stats);
पूर्ण

अटल व्योम ip101g_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ip101g_hw_stats); i++)
		strscpy(data + i * ETH_GSTRING_LEN,
			ip101g_hw_stats[i].name, ETH_GSTRING_LEN);
पूर्ण

अटल u64 ip101g_get_stat(काष्ठा phy_device *phydev, पूर्णांक i)
अणु
	काष्ठा ip101g_hw_stat stat = ip101g_hw_stats[i];
	काष्ठा ip101a_g_phy_priv *priv = phydev->priv;
	पूर्णांक val;
	u64 ret;

	val = phy_पढ़ो_paged(phydev, stat.page, IP101G_CNT_REG);
	अगर (val < 0) अणु
		ret = U64_MAX;
	पूर्ण अन्यथा अणु
		priv->stats[i] += val;
		ret = priv->stats[i];
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ip101g_get_stats(काष्ठा phy_device *phydev,
			     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ip101g_hw_stats); i++)
		data[i] = ip101g_get_stat(phydev, i);
पूर्ण

अटल काष्ठा phy_driver icplus_driver[] = अणु
अणु
	PHY_ID_MATCH_MODEL(IP175C_PHY_ID),
	.name		= "ICPlus IP175C",
	/* PHY_BASIC_FEATURES */
	.config_init	= ip175c_config_init,
	.config_aneg	= ip175c_config_aneg,
	.पढ़ो_status	= ip175c_पढ़ो_status,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	PHY_ID_MATCH_MODEL(IP1001_PHY_ID),
	.name		= "ICPlus IP1001",
	/* PHY_GBIT_FEATURES */
	.config_init	= ip1001_config_init,
	.soft_reset	= genphy_soft_reset,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.name		= "ICPlus IP101A",
	.match_phy_device = ip101a_match_phy_device,
	.probe		= ip101a_g_probe,
	.पढ़ो_page	= ip101a_पढ़ो_page,
	.ग_लिखो_page	= ip101a_ग_लिखो_page,
	.config_पूर्णांकr	= ip101a_g_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = ip101a_g_handle_पूर्णांकerrupt,
	.config_init	= ip101a_config_init,
	.config_aneg	= ip101a_g_config_aneg,
	.पढ़ो_status	= ip101a_g_पढ़ो_status,
	.soft_reset	= genphy_soft_reset,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.name		= "ICPlus IP101G",
	.match_phy_device = ip101g_match_phy_device,
	.probe		= ip101a_g_probe,
	.पढ़ो_page	= ip101g_पढ़ो_page,
	.ग_लिखो_page	= ip101g_ग_लिखो_page,
	.config_पूर्णांकr	= ip101a_g_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = ip101a_g_handle_पूर्णांकerrupt,
	.config_init	= ip101g_config_init,
	.config_aneg	= ip101a_g_config_aneg,
	.पढ़ो_status	= ip101a_g_पढ़ो_status,
	.soft_reset	= genphy_soft_reset,
	.get_sset_count = ip101g_get_sset_count,
	.get_strings	= ip101g_get_strings,
	.get_stats	= ip101g_get_stats,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण पूर्ण;

module_phy_driver(icplus_driver);

अटल काष्ठा mdio_device_id __maybe_unused icplus_tbl[] = अणु
	अणु PHY_ID_MATCH_MODEL(IP175C_PHY_ID) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(IP1001_PHY_ID) पूर्ण,
	अणु PHY_ID_MATCH_EXACT(IP101A_PHY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, icplus_tbl);
