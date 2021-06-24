<शैली गुरु>
/*
 * Driver क्रम (BCM4706)? GBit MAC core on BCMA bus.
 *
 * Copyright (C) 2012 Rafaध Miधecki <zajec5@gmail.com>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt

#समावेश <linux/bcma/bcma.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/of_net.h>
#समावेश "bgmac.h"

अटल अंतरभूत bool bgmac_is_bcm4707_family(काष्ठा bcma_device *core)
अणु
	चयन (core->bus->chipinfo.id) अणु
	हाल BCMA_CHIP_ID_BCM4707:
	हाल BCMA_CHIP_ID_BCM47094:
	हाल BCMA_CHIP_ID_BCM53018:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**************************************************
 * BCMA bus ops
 **************************************************/

अटल u32 bcma_bgmac_पढ़ो(काष्ठा bgmac *bgmac, u16 offset)
अणु
	वापस bcma_पढ़ो32(bgmac->bcma.core, offset);
पूर्ण

अटल व्योम bcma_bgmac_ग_लिखो(काष्ठा bgmac *bgmac, u16 offset, u32 value)
अणु
	bcma_ग_लिखो32(bgmac->bcma.core, offset, value);
पूर्ण

अटल u32 bcma_bgmac_idm_पढ़ो(काष्ठा bgmac *bgmac, u16 offset)
अणु
	वापस bcma_aपढ़ो32(bgmac->bcma.core, offset);
पूर्ण

अटल व्योम bcma_bgmac_idm_ग_लिखो(काष्ठा bgmac *bgmac, u16 offset, u32 value)
अणु
	वापस bcma_aग_लिखो32(bgmac->bcma.core, offset, value);
पूर्ण

अटल bool bcma_bgmac_clk_enabled(काष्ठा bgmac *bgmac)
अणु
	वापस bcma_core_is_enabled(bgmac->bcma.core);
पूर्ण

अटल व्योम bcma_bgmac_clk_enable(काष्ठा bgmac *bgmac, u32 flags)
अणु
	bcma_core_enable(bgmac->bcma.core, flags);
पूर्ण

अटल व्योम bcma_bgmac_cco_ctl_maskset(काष्ठा bgmac *bgmac, u32 offset,
				       u32 mask, u32 set)
अणु
	काष्ठा bcma_drv_cc *cc = &bgmac->bcma.core->bus->drv_cc;

	bcma_chipco_chipctl_maskset(cc, offset, mask, set);
पूर्ण

अटल u32 bcma_bgmac_get_bus_घड़ी(काष्ठा bgmac *bgmac)
अणु
	काष्ठा bcma_drv_cc *cc = &bgmac->bcma.core->bus->drv_cc;

	वापस bcma_pmu_get_bus_घड़ी(cc);
पूर्ण

अटल व्योम bcma_bgmac_cmn_maskset32(काष्ठा bgmac *bgmac, u16 offset, u32 mask,
				     u32 set)
अणु
	bcma_maskset32(bgmac->bcma.cmn, offset, mask, set);
पूर्ण

अटल पूर्णांक bcma_phy_connect(काष्ठा bgmac *bgmac)
अणु
	काष्ठा phy_device *phy_dev;
	अक्षर bus_id[MII_BUS_ID_SIZE + 3];

	/* Connect to the PHY */
	snम_लिखो(bus_id, माप(bus_id), PHY_ID_FMT, bgmac->mii_bus->id,
		 bgmac->phyaddr);
	phy_dev = phy_connect(bgmac->net_dev, bus_id, bgmac_adjust_link,
			      PHY_INTERFACE_MODE_MII);
	अगर (IS_ERR(phy_dev)) अणु
		dev_err(bgmac->dev, "PHY connection failed\n");
		वापस PTR_ERR(phy_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bcma_device_id bgmac_bcma_tbl[] = अणु
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_4706_MAC_GBIT,
		  BCMA_ANY_REV, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_MAC_GBIT, BCMA_ANY_REV,
		  BCMA_ANY_CLASS),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(bcma, bgmac_bcma_tbl);

/* http://bcm-v4.sipsolutions.net/mac-gbit/gmac/chipattach */
अटल पूर्णांक bgmac_probe(काष्ठा bcma_device *core)
अणु
	काष्ठा bcma_chipinfo *ci = &core->bus->chipinfo;
	काष्ठा ssb_sprom *sprom = &core->bus->sprom;
	काष्ठा mii_bus *mii_bus;
	काष्ठा bgmac *bgmac;
	स्थिर u8 *mac;
	पूर्णांक err;

	bgmac = bgmac_alloc(&core->dev);
	अगर (!bgmac)
		वापस -ENOMEM;

	bgmac->bcma.core = core;
	bgmac->dma_dev = core->dma_dev;
	bgmac->irq = core->irq;

	bcma_set_drvdata(core, bgmac);

	err = of_get_mac_address(bgmac->dev->of_node, bgmac->net_dev->dev_addr);

	/* If no MAC address asचिन्हित via device tree, check SPROM */
	अगर (err) अणु
		चयन (core->core_unit) अणु
		हाल 0:
			mac = sprom->et0mac;
			अवरोध;
		हाल 1:
			mac = sprom->et1mac;
			अवरोध;
		हाल 2:
			mac = sprom->et2mac;
			अवरोध;
		शेष:
			dev_err(bgmac->dev, "Unsupported core_unit %d\n",
				core->core_unit);
			err = -ENOTSUPP;
			जाओ err;
		पूर्ण
		ether_addr_copy(bgmac->net_dev->dev_addr, mac);
	पूर्ण

	/* On BCM4706 we need common core to access PHY */
	अगर (core->id.id == BCMA_CORE_4706_MAC_GBIT &&
	    !core->bus->drv_gmac_cmn.core) अणु
		dev_err(bgmac->dev, "GMAC CMN core not found (required for BCM4706)\n");
		err = -ENODEV;
		जाओ err;
	पूर्ण
	bgmac->bcma.cmn = core->bus->drv_gmac_cmn.core;

	चयन (core->core_unit) अणु
	हाल 0:
		bgmac->phyaddr = sprom->et0phyaddr;
		अवरोध;
	हाल 1:
		bgmac->phyaddr = sprom->et1phyaddr;
		अवरोध;
	हाल 2:
		bgmac->phyaddr = sprom->et2phyaddr;
		अवरोध;
	पूर्ण
	bgmac->phyaddr &= BGMAC_PHY_MASK;
	अगर (bgmac->phyaddr == BGMAC_PHY_MASK) अणु
		dev_err(bgmac->dev, "No PHY found\n");
		err = -ENODEV;
		जाओ err;
	पूर्ण
	dev_info(bgmac->dev, "Found PHY addr: %d%s\n", bgmac->phyaddr,
		 bgmac->phyaddr == BGMAC_PHY_NOREGS ? " (NOREGS)" : "");

	अगर (!bgmac_is_bcm4707_family(core) &&
	    !(ci->id == BCMA_CHIP_ID_BCM53573 && core->core_unit == 1)) अणु
		काष्ठा phy_device *phydev;

		mii_bus = bcma_mdio_mii_रेजिस्टर(bgmac);
		अगर (IS_ERR(mii_bus)) अणु
			err = PTR_ERR(mii_bus);
			जाओ err;
		पूर्ण
		bgmac->mii_bus = mii_bus;

		phydev = mdiobus_get_phy(bgmac->mii_bus, bgmac->phyaddr);
		अगर (ci->id == BCMA_CHIP_ID_BCM53573 && phydev &&
		    (phydev->drv->phy_id & phydev->drv->phy_id_mask) == PHY_ID_BCM54210E)
			phydev->dev_flags |= PHY_BRCM_EN_MASTER_MODE;
	पूर्ण

	अगर (core->bus->hosttype == BCMA_HOSTTYPE_PCI) अणु
		dev_err(bgmac->dev, "PCI setup not implemented\n");
		err = -ENOTSUPP;
		जाओ err1;
	पूर्ण

	bgmac->has_robosw = !!(sprom->boardflags_lo & BGMAC_BFL_ENETROBO);
	अगर (bgmac->has_robosw)
		dev_warn(bgmac->dev, "Support for Roboswitch not implemented\n");

	अगर (sprom->boardflags_lo & BGMAC_BFL_ENETADM)
		dev_warn(bgmac->dev, "Support for ADMtek ethernet switch not implemented\n");

	/* Feature Flags */
	चयन (ci->id) अणु
	/* BCM 471X/535X family */
	हाल BCMA_CHIP_ID_BCM4716:
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		fallthrough;
	हाल BCMA_CHIP_ID_BCM47162:
		bgmac->feature_flags |= BGMAC_FEAT_FLW_CTRL2;
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
		अवरोध;
	हाल BCMA_CHIP_ID_BCM5357:
	हाल BCMA_CHIP_ID_BCM53572:
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_FLW_CTRL1;
		bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_PHY;
		अगर (ci->pkg == BCMA_PKG_ID_BCM47188 ||
		    ci->pkg == BCMA_PKG_ID_BCM47186) अणु
			bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_RGMII;
			bgmac->feature_flags |= BGMAC_FEAT_IOST_ATTACHED;
		पूर्ण
		अगर (ci->pkg == BCMA_PKG_ID_BCM5358)
			bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_EPHYRMII;
		अवरोध;
	हाल BCMA_CHIP_ID_BCM53573:
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
		अगर (ci->pkg == BCMA_PKG_ID_BCM47189)
			bgmac->feature_flags |= BGMAC_FEAT_IOST_ATTACHED;
		अगर (core->core_unit == 0) अणु
			bgmac->feature_flags |= BGMAC_FEAT_CC4_IF_SW_TYPE;
			अगर (ci->pkg == BCMA_PKG_ID_BCM47189)
				bgmac->feature_flags |=
					BGMAC_FEAT_CC4_IF_SW_TYPE_RGMII;
		पूर्ण अन्यथा अगर (core->core_unit == 1) अणु
			bgmac->feature_flags |= BGMAC_FEAT_IRQ_ID_OOB_6;
			bgmac->feature_flags |= BGMAC_FEAT_CC7_IF_TYPE_RGMII;
		पूर्ण
		अवरोध;
	हाल BCMA_CHIP_ID_BCM4749:
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_FLW_CTRL1;
		bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_PHY;
		अगर (ci->pkg == 10) अणु
			bgmac->feature_flags |= BGMAC_FEAT_SW_TYPE_RGMII;
			bgmac->feature_flags |= BGMAC_FEAT_IOST_ATTACHED;
		पूर्ण
		अवरोध;
	/* bcm4707_family */
	हाल BCMA_CHIP_ID_BCM4707:
	हाल BCMA_CHIP_ID_BCM47094:
	हाल BCMA_CHIP_ID_BCM53018:
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_NO_RESET;
		bgmac->feature_flags |= BGMAC_FEAT_FORCE_SPEED_2500;
		अवरोध;
	शेष:
		bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
		bgmac->feature_flags |= BGMAC_FEAT_SET_RXQ_CLK;
	पूर्ण

	अगर (!bgmac_is_bcm4707_family(core) && core->id.rev > 2)
		bgmac->feature_flags |= BGMAC_FEAT_MISC_PLL_REQ;

	अगर (core->id.id == BCMA_CORE_4706_MAC_GBIT) अणु
		bgmac->feature_flags |= BGMAC_FEAT_CMN_PHY_CTL;
		bgmac->feature_flags |= BGMAC_FEAT_NO_CLR_MIB;
	पूर्ण

	अगर (core->id.rev >= 4) अणु
		bgmac->feature_flags |= BGMAC_FEAT_CMDCFG_SR_REV4;
		bgmac->feature_flags |= BGMAC_FEAT_TX_MASK_SETUP;
		bgmac->feature_flags |= BGMAC_FEAT_RX_MASK_SETUP;
	पूर्ण

	bgmac->पढ़ो = bcma_bgmac_पढ़ो;
	bgmac->ग_लिखो = bcma_bgmac_ग_लिखो;
	bgmac->idm_पढ़ो = bcma_bgmac_idm_पढ़ो;
	bgmac->idm_ग_लिखो = bcma_bgmac_idm_ग_लिखो;
	bgmac->clk_enabled = bcma_bgmac_clk_enabled;
	bgmac->clk_enable = bcma_bgmac_clk_enable;
	bgmac->cco_ctl_maskset = bcma_bgmac_cco_ctl_maskset;
	bgmac->get_bus_घड़ी = bcma_bgmac_get_bus_घड़ी;
	bgmac->cmn_maskset32 = bcma_bgmac_cmn_maskset32;
	अगर (bgmac->mii_bus)
		bgmac->phy_connect = bcma_phy_connect;
	अन्यथा
		bgmac->phy_connect = bgmac_phy_connect_direct;

	err = bgmac_enet_probe(bgmac);
	अगर (err)
		जाओ err1;

	वापस 0;

err1:
	bcma_mdio_mii_unरेजिस्टर(bgmac->mii_bus);
err:
	bcma_set_drvdata(core, शून्य);

	वापस err;
पूर्ण

अटल व्योम bgmac_हटाओ(काष्ठा bcma_device *core)
अणु
	काष्ठा bgmac *bgmac = bcma_get_drvdata(core);

	bcma_mdio_mii_unरेजिस्टर(bgmac->mii_bus);
	bgmac_enet_हटाओ(bgmac);
	bcma_set_drvdata(core, शून्य);
	kमुक्त(bgmac);
पूर्ण

अटल काष्ठा bcma_driver bgmac_bcma_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= bgmac_bcma_tbl,
	.probe		= bgmac_probe,
	.हटाओ		= bgmac_हटाओ,
पूर्ण;

अटल पूर्णांक __init bgmac_init(व्योम)
अणु
	पूर्णांक err;

	err = bcma_driver_रेजिस्टर(&bgmac_bcma_driver);
	अगर (err)
		वापस err;
	pr_info("Broadcom 47xx GBit MAC driver loaded\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास bgmac_निकास(व्योम)
अणु
	bcma_driver_unरेजिस्टर(&bgmac_bcma_driver);
पूर्ण

module_init(bgmac_init)
module_निकास(bgmac_निकास)

MODULE_AUTHOR("Rafaध Miधecki");
MODULE_LICENSE("GPL");
