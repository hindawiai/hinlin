<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom GENET MDIO routines
 *
 * Copyright (c) 2014-2017 Broadcom
 */

#समावेश <linux/acpi.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/bitops.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/platक्रमm_data/bcmgenet.h>
#समावेश <linux/platक्रमm_data/mdio-bcm-unimac.h>

#समावेश "bcmgenet.h"

/* setup netdev link state when PHY link status change and
 * update UMAC and RGMII block when link up
 */
व्योम bcmgenet_mii_setup(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	u32 reg, cmd_bits = 0;
	bool status_changed = false;

	अगर (priv->old_link != phydev->link) अणु
		status_changed = true;
		priv->old_link = phydev->link;
	पूर्ण

	अगर (phydev->link) अणु
		/* check speed/duplex/छोड़ो changes */
		अगर (priv->old_speed != phydev->speed) अणु
			status_changed = true;
			priv->old_speed = phydev->speed;
		पूर्ण

		अगर (priv->old_duplex != phydev->duplex) अणु
			status_changed = true;
			priv->old_duplex = phydev->duplex;
		पूर्ण

		अगर (priv->old_छोड़ो != phydev->छोड़ो) अणु
			status_changed = true;
			priv->old_छोड़ो = phydev->छोड़ो;
		पूर्ण

		/* करोne अगर nothing has changed */
		अगर (!status_changed)
			वापस;

		/* speed */
		अगर (phydev->speed == SPEED_1000)
			cmd_bits = CMD_SPEED_1000;
		अन्यथा अगर (phydev->speed == SPEED_100)
			cmd_bits = CMD_SPEED_100;
		अन्यथा
			cmd_bits = CMD_SPEED_10;
		cmd_bits <<= CMD_SPEED_SHIFT;

		/* duplex */
		अगर (phydev->duplex != DUPLEX_FULL)
			cmd_bits |= CMD_HD_EN;

		/* छोड़ो capability */
		अगर (!phydev->छोड़ो)
			cmd_bits |= CMD_RX_PAUSE_IGNORE | CMD_TX_PAUSE_IGNORE;

		/*
		 * Program UMAC and RGMII block based on established
		 * link speed, duplex, and छोड़ो. The speed set in
		 * umac->cmd tell RGMII block which घड़ी to use क्रम
		 * transmit -- 25MHz(100Mbps) or 125MHz(1Gbps).
		 * Receive घड़ी is provided by the PHY.
		 */
		reg = bcmgenet_ext_पढ़ोl(priv, EXT_RGMII_OOB_CTRL);
		reg &= ~OOB_DISABLE;
		reg |= RGMII_LINK;
		bcmgenet_ext_ग_लिखोl(priv, reg, EXT_RGMII_OOB_CTRL);

		reg = bcmgenet_umac_पढ़ोl(priv, UMAC_CMD);
		reg &= ~((CMD_SPEED_MASK << CMD_SPEED_SHIFT) |
			       CMD_HD_EN |
			       CMD_RX_PAUSE_IGNORE | CMD_TX_PAUSE_IGNORE);
		reg |= cmd_bits;
		अगर (reg & CMD_SW_RESET) अणु
			reg &= ~CMD_SW_RESET;
			bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_CMD);
			udelay(2);
			reg |= CMD_TX_EN | CMD_RX_EN;
		पूर्ण
		bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_CMD);
	पूर्ण अन्यथा अणु
		/* करोne अगर nothing has changed */
		अगर (!status_changed)
			वापस;

		/* needed क्रम MoCA fixed PHY to reflect correct link status */
		netअगर_carrier_off(dev);
	पूर्ण

	phy_prपूर्णांक_status(phydev);
पूर्ण


अटल पूर्णांक bcmgenet_fixed_phy_link_update(काष्ठा net_device *dev,
					  काष्ठा fixed_phy_status *status)
अणु
	काष्ठा bcmgenet_priv *priv;
	u32 reg;

	अगर (dev && dev->phydev && status) अणु
		priv = netdev_priv(dev);
		reg = bcmgenet_umac_पढ़ोl(priv, UMAC_MODE);
		status->link = !!(reg & MODE_LINK_STATUS);
	पूर्ण

	वापस 0;
पूर्ण

व्योम bcmgenet_phy_घातer_set(काष्ठा net_device *dev, bool enable)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	u32 reg = 0;

	/* EXT_GPHY_CTRL is only valid क्रम GENETv4 and onward */
	अगर (GENET_IS_V4(priv)) अणु
		reg = bcmgenet_ext_पढ़ोl(priv, EXT_GPHY_CTRL);
		अगर (enable) अणु
			reg &= ~EXT_CK25_DIS;
			bcmgenet_ext_ग_लिखोl(priv, reg, EXT_GPHY_CTRL);
			mdelay(1);

			reg &= ~(EXT_CFG_IDDQ_BIAS | EXT_CFG_PWR_DOWN);
			reg |= EXT_GPHY_RESET;
			bcmgenet_ext_ग_लिखोl(priv, reg, EXT_GPHY_CTRL);
			mdelay(1);

			reg &= ~EXT_GPHY_RESET;
		पूर्ण अन्यथा अणु
			reg |= EXT_CFG_IDDQ_BIAS | EXT_CFG_PWR_DOWN |
			       EXT_GPHY_RESET;
			bcmgenet_ext_ग_लिखोl(priv, reg, EXT_GPHY_CTRL);
			mdelay(1);
			reg |= EXT_CK25_DIS;
		पूर्ण
		bcmgenet_ext_ग_लिखोl(priv, reg, EXT_GPHY_CTRL);
		udelay(60);
	पूर्ण अन्यथा अणु
		mdelay(1);
	पूर्ण
पूर्ण

अटल व्योम bcmgenet_moca_phy_setup(काष्ठा bcmgenet_priv *priv)
अणु
	u32 reg;

	अगर (!GENET_IS_V5(priv)) अणु
		/* Speed settings are set in bcmgenet_mii_setup() */
		reg = bcmgenet_sys_पढ़ोl(priv, SYS_PORT_CTRL);
		reg |= LED_ACT_SOURCE_MAC;
		bcmgenet_sys_ग_लिखोl(priv, reg, SYS_PORT_CTRL);
	पूर्ण

	अगर (priv->hw_params->flags & GENET_HAS_MOCA_LINK_DET)
		fixed_phy_set_link_update(priv->dev->phydev,
					  bcmgenet_fixed_phy_link_update);
पूर्ण

पूर्णांक bcmgenet_mii_config(काष्ठा net_device *dev, bool init)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phydev = dev->phydev;
	काष्ठा device *kdev = &priv->pdev->dev;
	स्थिर अक्षर *phy_name = शून्य;
	u32 id_mode_dis = 0;
	u32 port_ctrl;
	u32 reg;

	चयन (priv->phy_पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_INTERNAL:
		phy_name = "internal PHY";
		fallthrough;
	हाल PHY_INTERFACE_MODE_MOCA:
		/* Irrespective of the actually configured PHY speed (100 or
		 * 1000) GENETv4 only has an पूर्णांकernal GPHY so we will just end
		 * up masking the Gigabit features from what we support, not
		 * चयनing to the EPHY
		 */
		अगर (GENET_IS_V4(priv))
			port_ctrl = PORT_MODE_INT_GPHY;
		अन्यथा
			port_ctrl = PORT_MODE_INT_EPHY;

		अगर (!phy_name) अणु
			phy_name = "MoCA";
			bcmgenet_moca_phy_setup(priv);
		पूर्ण
		अवरोध;

	हाल PHY_INTERFACE_MODE_MII:
		phy_name = "external MII";
		phy_set_max_speed(phydev, SPEED_100);
		port_ctrl = PORT_MODE_EXT_EPHY;
		अवरोध;

	हाल PHY_INTERFACE_MODE_REVMII:
		phy_name = "external RvMII";
		/* of_mdiobus_रेजिस्टर took care of पढ़ोing the 'max-speed'
		 * PHY property क्रम us, effectively limiting the PHY supported
		 * capabilities, use that knowledge to also configure the
		 * Reverse MII पूर्णांकerface correctly.
		 */
		अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				      dev->phydev->supported))
			port_ctrl = PORT_MODE_EXT_RVMII_50;
		अन्यथा
			port_ctrl = PORT_MODE_EXT_RVMII_25;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII:
		/* RGMII_NO_ID: TXC transitions at the same समय as TXD
		 *		(requires PCB or receiver-side delay)
		 *
		 * ID is implicitly disabled क्रम 100Mbps (RG)MII operation.
		 */
		phy_name = "external RGMII (no delay)";
		id_mode_dis = BIT(16);
		port_ctrl = PORT_MODE_EXT_GPHY;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		/* RGMII_TXID:	Add 2ns delay on TXC (90 degree shअगरt) */
		phy_name = "external RGMII (TX delay)";
		port_ctrl = PORT_MODE_EXT_GPHY;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		phy_name = "external RGMII (RX delay)";
		port_ctrl = PORT_MODE_EXT_GPHY;
		अवरोध;
	शेष:
		dev_err(kdev, "unknown phy mode: %d\n", priv->phy_पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण

	bcmgenet_sys_ग_लिखोl(priv, port_ctrl, SYS_PORT_CTRL);

	priv->ext_phy = !priv->पूर्णांकernal_phy &&
			(priv->phy_पूर्णांकerface != PHY_INTERFACE_MODE_MOCA);

	/* This is an बाह्यal PHY (xMII), so we need to enable the RGMII
	 * block क्रम the पूर्णांकerface to work
	 */
	अगर (priv->ext_phy) अणु
		reg = bcmgenet_ext_पढ़ोl(priv, EXT_RGMII_OOB_CTRL);
		reg &= ~ID_MODE_DIS;
		reg |= id_mode_dis;
		अगर (GENET_IS_V1(priv) || GENET_IS_V2(priv) || GENET_IS_V3(priv))
			reg |= RGMII_MODE_EN_V123;
		अन्यथा
			reg |= RGMII_MODE_EN;
		bcmgenet_ext_ग_लिखोl(priv, reg, EXT_RGMII_OOB_CTRL);
	पूर्ण

	अगर (init)
		dev_info(kdev, "configuring instance for %s\n", phy_name);

	वापस 0;
पूर्ण

पूर्णांक bcmgenet_mii_probe(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा device *kdev = &priv->pdev->dev;
	काष्ठा device_node *dn = kdev->of_node;
	काष्ठा phy_device *phydev;
	u32 phy_flags = 0;
	पूर्णांक ret;

	/* Communicate the पूर्णांकegrated PHY revision */
	अगर (priv->पूर्णांकernal_phy)
		phy_flags = priv->gphy_rev;

	/* Initialize link state variables that bcmgenet_mii_setup() uses */
	priv->old_link = -1;
	priv->old_speed = -1;
	priv->old_duplex = -1;
	priv->old_छोड़ो = -1;

	अगर (dn) अणु
		phydev = of_phy_connect(dev, priv->phy_dn, bcmgenet_mii_setup,
					phy_flags, priv->phy_पूर्णांकerface);
		अगर (!phydev) अणु
			pr_err("could not attach to PHY\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (has_acpi_companion(kdev)) अणु
			अक्षर mdio_bus_id[MII_BUS_ID_SIZE];
			काष्ठा mii_bus *unimacbus;

			snम_लिखो(mdio_bus_id, MII_BUS_ID_SIZE, "%s-%d",
				 UNIMAC_MDIO_DRV_NAME, priv->pdev->id);

			unimacbus = mdio_find_bus(mdio_bus_id);
			अगर (!unimacbus) अणु
				pr_err("Unable to find mii\n");
				वापस -ENODEV;
			पूर्ण
			phydev = phy_find_first(unimacbus);
			put_device(&unimacbus->dev);
			अगर (!phydev) अणु
				pr_err("Unable to find PHY\n");
				वापस -ENODEV;
			पूर्ण
		पूर्ण अन्यथा अणु
			phydev = dev->phydev;
		पूर्ण
		phydev->dev_flags = phy_flags;

		ret = phy_connect_direct(dev, phydev, bcmgenet_mii_setup,
					 priv->phy_पूर्णांकerface);
		अगर (ret) अणु
			pr_err("could not attach to PHY\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Configure port multiplexer based on what the probed PHY device since
	 * पढ़ोing the 'max-speed' property determines the maximum supported
	 * PHY speed which is needed क्रम bcmgenet_mii_config() to configure
	 * things appropriately.
	 */
	ret = bcmgenet_mii_config(dev, true);
	अगर (ret) अणु
		phy_disconnect(dev->phydev);
		वापस ret;
	पूर्ण

	linkmode_copy(phydev->advertising, phydev->supported);

	/* The पूर्णांकernal PHY has its link पूर्णांकerrupts routed to the
	 * Ethernet MAC ISRs. On GENETv5 there is a hardware issue
	 * that prevents the संकेतing of link UP पूर्णांकerrupts when
	 * the link operates at 10Mbps, so fallback to polling क्रम
	 * those versions of GENET.
	 */
	अगर (priv->पूर्णांकernal_phy && !GENET_IS_V5(priv))
		dev->phydev->irq = PHY_MAC_INTERRUPT;

	वापस 0;
पूर्ण

अटल काष्ठा device_node *bcmgenet_mii_of_find_mdio(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा device_node *dn = priv->pdev->dev.of_node;
	काष्ठा device *kdev = &priv->pdev->dev;
	अक्षर *compat;

	compat = kaप्र_लिखो(GFP_KERNEL, "brcm,genet-mdio-v%d", priv->version);
	अगर (!compat)
		वापस शून्य;

	priv->mdio_dn = of_get_compatible_child(dn, compat);
	kमुक्त(compat);
	अगर (!priv->mdio_dn) अणु
		dev_err(kdev, "unable to find MDIO bus node\n");
		वापस शून्य;
	पूर्ण

	वापस priv->mdio_dn;
पूर्ण

अटल व्योम bcmgenet_mii_pdata_init(काष्ठा bcmgenet_priv *priv,
				    काष्ठा unimac_mdio_pdata *ppd)
अणु
	काष्ठा device *kdev = &priv->pdev->dev;
	काष्ठा bcmgenet_platक्रमm_data *pd = kdev->platक्रमm_data;

	अगर (pd->phy_पूर्णांकerface != PHY_INTERFACE_MODE_MOCA && pd->mdio_enabled) अणु
		/*
		 * Internal or बाह्यal PHY with MDIO access
		 */
		अगर (pd->phy_address >= 0 && pd->phy_address < PHY_MAX_ADDR)
			ppd->phy_mask = 1 << pd->phy_address;
		अन्यथा
			ppd->phy_mask = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक bcmgenet_mii_रुको(व्योम *रुको_func_data)
अणु
	काष्ठा bcmgenet_priv *priv = रुको_func_data;

	रुको_event_समयout(priv->wq,
			   !(bcmgenet_umac_पढ़ोl(priv, UMAC_MDIO_CMD)
			   & MDIO_START_BUSY),
			   HZ / 100);
	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_mii_रेजिस्टर(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा platक्रमm_device *pdev = priv->pdev;
	काष्ठा bcmgenet_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा device_node *dn = pdev->dev.of_node;
	काष्ठा unimac_mdio_pdata ppd;
	काष्ठा platक्रमm_device *ppdev;
	काष्ठा resource *pres, res;
	पूर्णांक id, ret;

	pres = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	स_रखो(&res, 0, माप(res));
	स_रखो(&ppd, 0, माप(ppd));

	ppd.रुको_func = bcmgenet_mii_रुको;
	ppd.रुको_func_data = priv;
	ppd.bus_name = "bcmgenet MII bus";

	/* Unimac MDIO bus controller starts at UniMAC offset + MDIO_CMD
	 * and is 2 * 32-bits word दीर्घ, 8 bytes total.
	 */
	res.start = pres->start + GENET_UMAC_OFF + UMAC_MDIO_CMD;
	res.end = res.start + 8;
	res.flags = IORESOURCE_MEM;

	अगर (dn)
		id = of_alias_get_id(dn, "eth");
	अन्यथा
		id = pdev->id;

	ppdev = platक्रमm_device_alloc(UNIMAC_MDIO_DRV_NAME, id);
	अगर (!ppdev)
		वापस -ENOMEM;

	/* Retain this platक्रमm_device poपूर्णांकer क्रम later cleanup */
	priv->mii_pdev = ppdev;
	ppdev->dev.parent = &pdev->dev;
	अगर (dn)
		ppdev->dev.of_node = bcmgenet_mii_of_find_mdio(priv);
	अन्यथा अगर (pdata)
		bcmgenet_mii_pdata_init(priv, &ppd);
	अन्यथा
		ppd.phy_mask = ~0;

	ret = platक्रमm_device_add_resources(ppdev, &res, 1);
	अगर (ret)
		जाओ out;

	ret = platक्रमm_device_add_data(ppdev, &ppd, माप(ppd));
	अगर (ret)
		जाओ out;

	ret = platक्रमm_device_add(ppdev);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	platक्रमm_device_put(ppdev);
	वापस ret;
पूर्ण

अटल पूर्णांक bcmgenet_phy_पूर्णांकerface_init(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा device *kdev = &priv->pdev->dev;
	पूर्णांक phy_mode = device_get_phy_mode(kdev);

	अगर (phy_mode < 0) अणु
		dev_err(kdev, "invalid PHY mode property\n");
		वापस phy_mode;
	पूर्ण

	priv->phy_पूर्णांकerface = phy_mode;

	/* We need to specअगरically look up whether this PHY पूर्णांकerface is
	 * पूर्णांकernal or not *beक्रमe* we even try to probe the PHY driver
	 * over MDIO as we may have shut करोwn the पूर्णांकernal PHY क्रम घातer
	 * saving purposes.
	 */
	अगर (priv->phy_पूर्णांकerface == PHY_INTERFACE_MODE_INTERNAL)
		priv->पूर्णांकernal_phy = true;

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_mii_of_init(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा device_node *dn = priv->pdev->dev.of_node;
	काष्ठा phy_device *phydev;
	पूर्णांक ret;

	/* Fetch the PHY phandle */
	priv->phy_dn = of_parse_phandle(dn, "phy-handle", 0);

	/* In the हाल of a fixed PHY, the DT node associated
	 * to the PHY is the Ethernet MAC DT node.
	 */
	अगर (!priv->phy_dn && of_phy_is_fixed_link(dn)) अणु
		ret = of_phy_रेजिस्टर_fixed_link(dn);
		अगर (ret)
			वापस ret;

		priv->phy_dn = of_node_get(dn);
	पूर्ण

	/* Get the link mode */
	ret = bcmgenet_phy_पूर्णांकerface_init(priv);
	अगर (ret)
		वापस ret;

	/* Make sure we initialize MoCA PHYs with a link करोwn */
	अगर (priv->phy_पूर्णांकerface == PHY_INTERFACE_MODE_MOCA) अणु
		phydev = of_phy_find_device(dn);
		अगर (phydev) अणु
			phydev->link = 0;
			put_device(&phydev->mdio.dev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_mii_pd_init(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा device *kdev = &priv->pdev->dev;
	काष्ठा bcmgenet_platक्रमm_data *pd = kdev->platक्रमm_data;
	अक्षर phy_name[MII_BUS_ID_SIZE + 3];
	अक्षर mdio_bus_id[MII_BUS_ID_SIZE];
	काष्ठा phy_device *phydev;

	snम_लिखो(mdio_bus_id, MII_BUS_ID_SIZE, "%s-%d",
		 UNIMAC_MDIO_DRV_NAME, priv->pdev->id);

	अगर (pd->phy_पूर्णांकerface != PHY_INTERFACE_MODE_MOCA && pd->mdio_enabled) अणु
		snम_लिखो(phy_name, MII_BUS_ID_SIZE, PHY_ID_FMT,
			 mdio_bus_id, pd->phy_address);

		/*
		 * Internal or बाह्यal PHY with MDIO access
		 */
		phydev = phy_attach(priv->dev, phy_name, pd->phy_पूर्णांकerface);
		अगर (!phydev) अणु
			dev_err(kdev, "failed to register PHY device\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * MoCA port or no MDIO access.
		 * Use fixed PHY to represent the link layer.
		 */
		काष्ठा fixed_phy_status fphy_status = अणु
			.link = 1,
			.speed = pd->phy_speed,
			.duplex = pd->phy_duplex,
			.छोड़ो = 0,
			.asym_छोड़ो = 0,
		पूर्ण;

		phydev = fixed_phy_रेजिस्टर(PHY_POLL, &fphy_status, शून्य);
		अगर (!phydev || IS_ERR(phydev)) अणु
			dev_err(kdev, "failed to register fixed PHY device\n");
			वापस -ENODEV;
		पूर्ण

		/* Make sure we initialize MoCA PHYs with a link करोwn */
		phydev->link = 0;

	पूर्ण

	priv->phy_पूर्णांकerface = pd->phy_पूर्णांकerface;

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_mii_bus_init(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा device *kdev = &priv->pdev->dev;
	काष्ठा device_node *dn = kdev->of_node;

	अगर (dn)
		वापस bcmgenet_mii_of_init(priv);
	अन्यथा अगर (has_acpi_companion(kdev))
		वापस bcmgenet_phy_पूर्णांकerface_init(priv);
	अन्यथा
		वापस bcmgenet_mii_pd_init(priv);
पूर्ण

पूर्णांक bcmgenet_mii_init(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	पूर्णांक ret;

	ret = bcmgenet_mii_रेजिस्टर(priv);
	अगर (ret)
		वापस ret;

	ret = bcmgenet_mii_bus_init(priv);
	अगर (ret)
		जाओ out;

	वापस 0;

out:
	bcmgenet_mii_निकास(dev);
	वापस ret;
पूर्ण

व्योम bcmgenet_mii_निकास(काष्ठा net_device *dev)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा device_node *dn = priv->pdev->dev.of_node;

	अगर (of_phy_is_fixed_link(dn))
		of_phy_deरेजिस्टर_fixed_link(dn);
	of_node_put(priv->phy_dn);
	platक्रमm_device_unरेजिस्टर(priv->mii_pdev);
पूर्ण
