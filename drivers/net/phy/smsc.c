<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/smsc.c
 *
 * Driver क्रम SMSC PHYs
 *
 * Author: Herbert Valerio Riedel
 *
 * Copyright (c) 2006 Herbert Valerio Riedel <hvr@gnu.org>
 *
 * Support added क्रम SMSC LAN8187 and LAN8700 by steve.glendinning@shawell.net
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/of.h>
#समावेश <linux/phy.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/smscphy.h>

/* Venकरोr-specअगरic PHY Definitions */
/* EDPD NLP / crossover समय configuration */
#घोषणा PHY_EDPD_CONFIG			16
#घोषणा PHY_EDPD_CONFIG_EXT_CROSSOVER_	0x0001

/* Control/Status Indication Register */
#घोषणा SPECIAL_CTRL_STS		27
#घोषणा SPECIAL_CTRL_STS_OVRRD_AMDIX_	0x8000
#घोषणा SPECIAL_CTRL_STS_AMDIX_ENABLE_	0x4000
#घोषणा SPECIAL_CTRL_STS_AMDIX_STATE_	0x2000

काष्ठा smsc_hw_stat अणु
	स्थिर अक्षर *string;
	u8 reg;
	u8 bits;
पूर्ण;

अटल काष्ठा smsc_hw_stat smsc_hw_stats[] = अणु
	अणु "phy_symbol_errors", 26, 16पूर्ण,
पूर्ण;

काष्ठा smsc_phy_priv अणु
	bool energy_enable;
	काष्ठा clk *refclk;
पूर्ण;

अटल पूर्णांक smsc_phy_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc = phy_पढ़ो(phydev, MII_LAN83C185_ISF);

	वापस rc < 0 ? rc : 0;
पूर्ण

अटल पूर्णांक smsc_phy_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	काष्ठा smsc_phy_priv *priv = phydev->priv;
	u16 पूर्णांकmask = 0;
	पूर्णांक rc;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		rc = smsc_phy_ack_पूर्णांकerrupt(phydev);
		अगर (rc)
			वापस rc;

		पूर्णांकmask = MII_LAN83C185_ISF_INT4 | MII_LAN83C185_ISF_INT6;
		अगर (priv->energy_enable)
			पूर्णांकmask |= MII_LAN83C185_ISF_INT7;
		rc = phy_ग_लिखो(phydev, MII_LAN83C185_IM, पूर्णांकmask);
	पूर्ण अन्यथा अणु
		rc = phy_ग_लिखो(phydev, MII_LAN83C185_IM, पूर्णांकmask);
		अगर (rc)
			वापस rc;

		rc = smsc_phy_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस rc < 0 ? rc : 0;
पूर्ण

अटल irqवापस_t smsc_phy_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status, irq_enabled;

	irq_enabled = phy_पढ़ो(phydev, MII_LAN83C185_IM);
	अगर (irq_enabled < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	irq_status = phy_पढ़ो(phydev, MII_LAN83C185_ISF);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & irq_enabled))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक smsc_phy_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा smsc_phy_priv *priv = phydev->priv;
	पूर्णांक rc;

	अगर (!priv->energy_enable)
		वापस 0;

	rc = phy_पढ़ो(phydev, MII_LAN83C185_CTRL_STATUS);

	अगर (rc < 0)
		वापस rc;

	/* Enable energy detect mode क्रम this SMSC Transceivers */
	rc = phy_ग_लिखो(phydev, MII_LAN83C185_CTRL_STATUS,
		       rc | MII_LAN83C185_EDPWRDOWN);
	अगर (rc < 0)
		वापस rc;

	वापस smsc_phy_ack_पूर्णांकerrupt(phydev);
पूर्ण

अटल पूर्णांक smsc_phy_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc = phy_पढ़ो(phydev, MII_LAN83C185_SPECIAL_MODES);
	अगर (rc < 0)
		वापस rc;

	/* If the SMSC PHY is in घातer करोwn mode, then set it
	 * in all capable mode beक्रमe using it.
	 */
	अगर ((rc & MII_LAN83C185_MODE_MASK) == MII_LAN83C185_MODE_POWERDOWN) अणु
		/* set "all capable" mode */
		rc |= MII_LAN83C185_MODE_ALL;
		phy_ग_लिखो(phydev, MII_LAN83C185_SPECIAL_MODES, rc);
	पूर्ण

	/* reset the phy */
	वापस genphy_soft_reset(phydev);
पूर्ण

अटल पूर्णांक lan911x_config_init(काष्ठा phy_device *phydev)
अणु
	वापस smsc_phy_ack_पूर्णांकerrupt(phydev);
पूर्ण

अटल पूर्णांक lan87xx_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;
	पूर्णांक val;

	चयन (phydev->mdix_ctrl) अणु
	हाल ETH_TP_MDI:
		val = SPECIAL_CTRL_STS_OVRRD_AMDIX_;
		अवरोध;
	हाल ETH_TP_MDI_X:
		val = SPECIAL_CTRL_STS_OVRRD_AMDIX_ |
			SPECIAL_CTRL_STS_AMDIX_STATE_;
		अवरोध;
	हाल ETH_TP_MDI_AUTO:
		val = SPECIAL_CTRL_STS_AMDIX_ENABLE_;
		अवरोध;
	शेष:
		वापस genphy_config_aneg(phydev);
	पूर्ण

	rc = phy_पढ़ो(phydev, SPECIAL_CTRL_STS);
	अगर (rc < 0)
		वापस rc;

	rc &= ~(SPECIAL_CTRL_STS_OVRRD_AMDIX_ |
		SPECIAL_CTRL_STS_AMDIX_ENABLE_ |
		SPECIAL_CTRL_STS_AMDIX_STATE_);
	rc |= val;
	phy_ग_लिखो(phydev, SPECIAL_CTRL_STS, rc);

	phydev->mdix = phydev->mdix_ctrl;
	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक lan95xx_config_aneg_ext(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	अगर (phydev->phy_id != 0x0007c0f0) /* not (LAN9500A or LAN9505A) */
		वापस lan87xx_config_aneg(phydev);

	/* Extend Manual AutoMDIX समयr */
	rc = phy_पढ़ो(phydev, PHY_EDPD_CONFIG);
	अगर (rc < 0)
		वापस rc;

	rc |= PHY_EDPD_CONFIG_EXT_CROSSOVER_;
	phy_ग_लिखो(phydev, PHY_EDPD_CONFIG, rc);
	वापस lan87xx_config_aneg(phydev);
पूर्ण

/*
 * The LAN87xx suffers from rare असलence of the ENERGYON-bit when Ethernet cable
 * plugs in जबतक LAN87xx is in Energy Detect Power-Down mode. This leads to
 * unstable detection of plugging in Ethernet cable.
 * This workaround disables Energy Detect Power-Down mode and रुकोing क्रम
 * response on link pulses to detect presence of plugged Ethernet cable.
 * The Energy Detect Power-Down mode is enabled again in the end of procedure to
 * save approximately 220 mW of घातer अगर cable is unplugged.
 */
अटल पूर्णांक lan87xx_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	काष्ठा smsc_phy_priv *priv = phydev->priv;

	पूर्णांक err = genphy_पढ़ो_status(phydev);

	अगर (!phydev->link && priv->energy_enable) अणु
		/* Disable EDPD to wake up PHY */
		पूर्णांक rc = phy_पढ़ो(phydev, MII_LAN83C185_CTRL_STATUS);
		अगर (rc < 0)
			वापस rc;

		rc = phy_ग_लिखो(phydev, MII_LAN83C185_CTRL_STATUS,
			       rc & ~MII_LAN83C185_EDPWRDOWN);
		अगर (rc < 0)
			वापस rc;

		/* Wait max 640 ms to detect energy and the समयout is not
		 * an actual error.
		 */
		पढ़ो_poll_समयout(phy_पढ़ो, rc,
				  rc & MII_LAN83C185_ENERGYON || rc < 0,
				  10000, 640000, true, phydev,
				  MII_LAN83C185_CTRL_STATUS);
		अगर (rc < 0)
			वापस rc;

		/* Re-enable EDPD */
		rc = phy_पढ़ो(phydev, MII_LAN83C185_CTRL_STATUS);
		अगर (rc < 0)
			वापस rc;

		rc = phy_ग_लिखो(phydev, MII_LAN83C185_CTRL_STATUS,
			       rc | MII_LAN83C185_EDPWRDOWN);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक smsc_get_sset_count(काष्ठा phy_device *phydev)
अणु
	वापस ARRAY_SIZE(smsc_hw_stats);
पूर्ण

अटल व्योम smsc_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(smsc_hw_stats); i++) अणु
		म_नकलन(data + i * ETH_GSTRING_LEN,
		       smsc_hw_stats[i].string, ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल u64 smsc_get_stat(काष्ठा phy_device *phydev, पूर्णांक i)
अणु
	काष्ठा smsc_hw_stat stat = smsc_hw_stats[i];
	पूर्णांक val;
	u64 ret;

	val = phy_पढ़ो(phydev, stat.reg);
	अगर (val < 0)
		ret = U64_MAX;
	अन्यथा
		ret = val;

	वापस ret;
पूर्ण

अटल व्योम smsc_get_stats(काष्ठा phy_device *phydev,
			   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(smsc_hw_stats); i++)
		data[i] = smsc_get_stat(phydev, i);
पूर्ण

अटल व्योम smsc_phy_हटाओ(काष्ठा phy_device *phydev)
अणु
	काष्ठा smsc_phy_priv *priv = phydev->priv;

	clk_disable_unprepare(priv->refclk);
	clk_put(priv->refclk);
पूर्ण

अटल पूर्णांक smsc_phy_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा device_node *of_node = dev->of_node;
	काष्ठा smsc_phy_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->energy_enable = true;

	अगर (of_property_पढ़ो_bool(of_node, "smsc,disable-energy-detect"))
		priv->energy_enable = false;

	phydev->priv = priv;

	/* Make clk optional to keep DTB backward compatibility. */
	priv->refclk = clk_get_optional(dev, शून्य);
	अगर (IS_ERR(priv->refclk))
		वापस dev_err_probe(dev, PTR_ERR(priv->refclk),
				     "Failed to request clock\n");

	ret = clk_prepare_enable(priv->refclk);
	अगर (ret)
		वापस ret;

	ret = clk_set_rate(priv->refclk, 50 * 1000 * 1000);
	अगर (ret) अणु
		clk_disable_unprepare(priv->refclk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा phy_driver smsc_phy_driver[] = अणु
अणु
	.phy_id		= 0x0007c0a0, /* OUI=0x00800f, Model#=0x0a */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC LAN83C185",

	/* PHY_BASIC_FEATURES */

	.probe		= smsc_phy_probe,

	/* basic functions */
	.config_init	= smsc_phy_config_init,
	.soft_reset	= smsc_phy_reset,

	/* IRQ related */
	.config_पूर्णांकr	= smsc_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = smsc_phy_handle_पूर्णांकerrupt,

	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= 0x0007c0b0, /* OUI=0x00800f, Model#=0x0b */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC LAN8187",

	/* PHY_BASIC_FEATURES */

	.probe		= smsc_phy_probe,

	/* basic functions */
	.config_init	= smsc_phy_config_init,
	.soft_reset	= smsc_phy_reset,

	/* IRQ related */
	.config_पूर्णांकr	= smsc_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = smsc_phy_handle_पूर्णांकerrupt,

	/* Statistics */
	.get_sset_count = smsc_get_sset_count,
	.get_strings	= smsc_get_strings,
	.get_stats	= smsc_get_stats,

	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	/* This covers पूर्णांकernal PHY (phy_id: 0x0007C0C3) क्रम
	 * LAN9500 (PID: 0x9500), LAN9514 (PID: 0xec00), LAN9505 (PID: 0x9505)
	 */
	.phy_id		= 0x0007c0c0, /* OUI=0x00800f, Model#=0x0c */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC LAN8700",

	/* PHY_BASIC_FEATURES */

	.probe		= smsc_phy_probe,

	/* basic functions */
	.पढ़ो_status	= lan87xx_पढ़ो_status,
	.config_init	= smsc_phy_config_init,
	.soft_reset	= smsc_phy_reset,
	.config_aneg	= lan87xx_config_aneg,

	/* IRQ related */
	.config_पूर्णांकr	= smsc_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = smsc_phy_handle_पूर्णांकerrupt,

	/* Statistics */
	.get_sset_count = smsc_get_sset_count,
	.get_strings	= smsc_get_strings,
	.get_stats	= smsc_get_stats,

	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= 0x0007c0d0, /* OUI=0x00800f, Model#=0x0d */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC LAN911x Internal PHY",

	/* PHY_BASIC_FEATURES */

	.probe		= smsc_phy_probe,

	/* basic functions */
	.config_init	= lan911x_config_init,

	/* IRQ related */
	.config_पूर्णांकr	= smsc_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = smsc_phy_handle_पूर्णांकerrupt,

	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	/* This covers पूर्णांकernal PHY (phy_id: 0x0007C0F0) क्रम
	 * LAN9500A (PID: 0x9E00), LAN9505A (PID: 0x9E01)
	 */
	.phy_id		= 0x0007c0f0, /* OUI=0x00800f, Model#=0x0f */
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC LAN8710/LAN8720",

	/* PHY_BASIC_FEATURES */

	.probe		= smsc_phy_probe,
	.हटाओ		= smsc_phy_हटाओ,

	/* basic functions */
	.पढ़ो_status	= lan87xx_पढ़ो_status,
	.config_init	= smsc_phy_config_init,
	.soft_reset	= smsc_phy_reset,
	.config_aneg	= lan95xx_config_aneg_ext,

	/* IRQ related */
	.config_पूर्णांकr	= smsc_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = smsc_phy_handle_पूर्णांकerrupt,

	/* Statistics */
	.get_sset_count = smsc_get_sset_count,
	.get_strings	= smsc_get_strings,
	.get_stats	= smsc_get_stats,

	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= 0x0007c110,
	.phy_id_mask	= 0xfffffff0,
	.name		= "SMSC LAN8740",

	/* PHY_BASIC_FEATURES */
	.flags		= PHY_RST_AFTER_CLK_EN,

	.probe		= smsc_phy_probe,

	/* basic functions */
	.पढ़ो_status	= lan87xx_पढ़ो_status,
	.config_init	= smsc_phy_config_init,
	.soft_reset	= smsc_phy_reset,

	/* IRQ related */
	.config_पूर्णांकr	= smsc_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = smsc_phy_handle_पूर्णांकerrupt,

	/* Statistics */
	.get_sset_count = smsc_get_sset_count,
	.get_strings	= smsc_get_strings,
	.get_stats	= smsc_get_stats,

	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण पूर्ण;

module_phy_driver(smsc_phy_driver);

MODULE_DESCRIPTION("SMSC PHY driver");
MODULE_AUTHOR("Herbert Valerio Riedel");
MODULE_LICENSE("GPL");

अटल काष्ठा mdio_device_id __maybe_unused smsc_tbl[] = अणु
	अणु 0x0007c0a0, 0xfffffff0 पूर्ण,
	अणु 0x0007c0b0, 0xfffffff0 पूर्ण,
	अणु 0x0007c0c0, 0xfffffff0 पूर्ण,
	अणु 0x0007c0d0, 0xfffffff0 पूर्ण,
	अणु 0x0007c0f0, 0xfffffff0 पूर्ण,
	अणु 0x0007c110, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, smsc_tbl);
