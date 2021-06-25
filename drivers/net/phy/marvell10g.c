<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Marvell 10G 88x3310 PHY driver
 *
 * Based upon the ID रेजिस्टरs, this PHY appears to be a mixture of IPs
 * from two dअगरferent companies.
 *
 * There appears to be several dअगरferent data paths through the PHY which
 * are स्वतःmatically managed by the PHY.  The following has been determined
 * via observation and experimentation क्रम a setup using single-lane Serdes:
 *
 *       SGMII PHYXS -- BASE-T PCS -- 10G PMA -- AN -- Copper (क्रम <= 1G)
 *  10GBASE-KR PHYXS -- BASE-T PCS -- 10G PMA -- AN -- Copper (क्रम 10G)
 *  10GBASE-KR PHYXS -- BASE-R PCS -- Fiber
 *
 * With XAUI, observation shows:
 *
 *        XAUI PHYXS -- <appropriate PCS as above>
 *
 * and no चयनing of the host पूर्णांकerface mode occurs.
 *
 * If both the fiber and copper ports are connected, the first to gain
 * link takes priority and the other port is completely locked out.
 */
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/marvell_phy.h>
#समावेश <linux/phy.h>
#समावेश <linux/sfp.h>

#घोषणा MV_PHY_ALASKA_NBT_QUIRK_MASK	0xfffffffe
#घोषणा MV_PHY_ALASKA_NBT_QUIRK_REV	(MARVELL_PHY_ID_88X3310 | 0xa)

क्रमागत अणु
	MV_PMA_FW_VER0		= 0xc011,
	MV_PMA_FW_VER1		= 0xc012,
	MV_PMA_21X0_PORT_CTRL	= 0xc04a,
	MV_PMA_21X0_PORT_CTRL_SWRST				= BIT(15),
	MV_PMA_21X0_PORT_CTRL_MACTYPE_MASK			= 0x7,
	MV_PMA_21X0_PORT_CTRL_MACTYPE_USXGMII			= 0x0,
	MV_PMA_2180_PORT_CTRL_MACTYPE_DXGMII			= 0x1,
	MV_PMA_2180_PORT_CTRL_MACTYPE_QXGMII			= 0x2,
	MV_PMA_21X0_PORT_CTRL_MACTYPE_5GBASER			= 0x4,
	MV_PMA_21X0_PORT_CTRL_MACTYPE_5GBASER_NO_SGMII_AN	= 0x5,
	MV_PMA_21X0_PORT_CTRL_MACTYPE_10GBASER_RATE_MATCH	= 0x6,
	MV_PMA_BOOT		= 0xc050,
	MV_PMA_BOOT_FATAL	= BIT(0),

	MV_PCS_BASE_T		= 0x0000,
	MV_PCS_BASE_R		= 0x1000,
	MV_PCS_1000BASEX	= 0x2000,

	MV_PCS_CSCR1		= 0x8000,
	MV_PCS_CSCR1_ED_MASK	= 0x0300,
	MV_PCS_CSCR1_ED_OFF	= 0x0000,
	MV_PCS_CSCR1_ED_RX	= 0x0200,
	MV_PCS_CSCR1_ED_NLP	= 0x0300,
	MV_PCS_CSCR1_MDIX_MASK	= 0x0060,
	MV_PCS_CSCR1_MDIX_MDI	= 0x0000,
	MV_PCS_CSCR1_MDIX_MDIX	= 0x0020,
	MV_PCS_CSCR1_MDIX_AUTO	= 0x0060,

	MV_PCS_CSSR1		= 0x8008,
	MV_PCS_CSSR1_SPD1_MASK	= 0xc000,
	MV_PCS_CSSR1_SPD1_SPD2	= 0xc000,
	MV_PCS_CSSR1_SPD1_1000	= 0x8000,
	MV_PCS_CSSR1_SPD1_100	= 0x4000,
	MV_PCS_CSSR1_SPD1_10	= 0x0000,
	MV_PCS_CSSR1_DUPLEX_FULL= BIT(13),
	MV_PCS_CSSR1_RESOLVED	= BIT(11),
	MV_PCS_CSSR1_MDIX	= BIT(6),
	MV_PCS_CSSR1_SPD2_MASK	= 0x000c,
	MV_PCS_CSSR1_SPD2_5000	= 0x0008,
	MV_PCS_CSSR1_SPD2_2500	= 0x0004,
	MV_PCS_CSSR1_SPD2_10000	= 0x0000,

	/* Temperature पढ़ो रेजिस्टर (88E2110 only) */
	MV_PCS_TEMP		= 0x8042,

	/* These रेजिस्टरs appear at 0x800X and 0xa00X - the 0xa00X control
	 * रेजिस्टरs appear to set themselves to the 0x800X when AN is
	 * restarted, but status रेजिस्टरs appear पढ़ोable from either.
	 */
	MV_AN_CTRL1000		= 0x8000, /* 1000base-T control रेजिस्टर */
	MV_AN_STAT1000		= 0x8001, /* 1000base-T status रेजिस्टर */

	/* Venकरोr2 MMD रेजिस्टरs */
	MV_V2_PORT_CTRL		= 0xf001,
	MV_V2_PORT_CTRL_PWRDOWN					= BIT(11),
	MV_V2_33X0_PORT_CTRL_SWRST				= BIT(15),
	MV_V2_33X0_PORT_CTRL_MACTYPE_MASK			= 0x7,
	MV_V2_33X0_PORT_CTRL_MACTYPE_RXAUI			= 0x0,
	MV_V2_3310_PORT_CTRL_MACTYPE_XAUI_RATE_MATCH		= 0x1,
	MV_V2_3340_PORT_CTRL_MACTYPE_RXAUI_NO_SGMII_AN		= 0x1,
	MV_V2_33X0_PORT_CTRL_MACTYPE_RXAUI_RATE_MATCH		= 0x2,
	MV_V2_3310_PORT_CTRL_MACTYPE_XAUI			= 0x3,
	MV_V2_33X0_PORT_CTRL_MACTYPE_10GBASER			= 0x4,
	MV_V2_33X0_PORT_CTRL_MACTYPE_10GBASER_NO_SGMII_AN	= 0x5,
	MV_V2_33X0_PORT_CTRL_MACTYPE_10GBASER_RATE_MATCH	= 0x6,
	MV_V2_33X0_PORT_CTRL_MACTYPE_USXGMII			= 0x7,
	/* Temperature control/पढ़ो रेजिस्टरs (88X3310 only) */
	MV_V2_TEMP_CTRL		= 0xf08a,
	MV_V2_TEMP_CTRL_MASK	= 0xc000,
	MV_V2_TEMP_CTRL_SAMPLE	= 0x0000,
	MV_V2_TEMP_CTRL_DISABLE	= 0xc000,
	MV_V2_TEMP		= 0xf08c,
	MV_V2_TEMP_UNKNOWN	= 0x9600, /* unknown function */
पूर्ण;

काष्ठा mv3310_chip अणु
	व्योम (*init_supported_पूर्णांकerfaces)(अचिन्हित दीर्घ *mask);
	पूर्णांक (*get_mactype)(काष्ठा phy_device *phydev);
	पूर्णांक (*init_पूर्णांकerface)(काष्ठा phy_device *phydev, पूर्णांक mactype);

#अगर_घोषित CONFIG_HWMON
	पूर्णांक (*hwmon_पढ़ो_temp_reg)(काष्ठा phy_device *phydev);
#पूर्ण_अगर
पूर्ण;

काष्ठा mv3310_priv अणु
	DECLARE_BITMAP(supported_पूर्णांकerfaces, PHY_INTERFACE_MODE_MAX);

	u32 firmware_ver;
	bool rate_match;
	phy_पूर्णांकerface_t स्थिर_पूर्णांकerface;

	काष्ठा device *hwmon_dev;
	अक्षर *hwmon_name;
पूर्ण;

अटल स्थिर काष्ठा mv3310_chip *to_mv3310_chip(काष्ठा phy_device *phydev)
अणु
	वापस phydev->drv->driver_data;
पूर्ण

#अगर_घोषित CONFIG_HWMON
अटल umode_t mv3310_hwmon_is_visible(स्थिर व्योम *data,
				       क्रमागत hwmon_sensor_types type,
				       u32 attr, पूर्णांक channel)
अणु
	अगर (type == hwmon_chip && attr == hwmon_chip_update_पूर्णांकerval)
		वापस 0444;
	अगर (type == hwmon_temp && attr == hwmon_temp_input)
		वापस 0444;
	वापस 0;
पूर्ण

अटल पूर्णांक mv3310_hwmon_पढ़ो_temp_reg(काष्ठा phy_device *phydev)
अणु
	वापस phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND2, MV_V2_TEMP);
पूर्ण

अटल पूर्णांक mv2110_hwmon_पढ़ो_temp_reg(काष्ठा phy_device *phydev)
अणु
	वापस phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MV_PCS_TEMP);
पूर्ण

अटल पूर्णांक mv3310_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			     u32 attr, पूर्णांक channel, दीर्घ *value)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	स्थिर काष्ठा mv3310_chip *chip = to_mv3310_chip(phydev);
	पूर्णांक temp;

	अगर (type == hwmon_chip && attr == hwmon_chip_update_पूर्णांकerval) अणु
		*value = MSEC_PER_SEC;
		वापस 0;
	पूर्ण

	अगर (type == hwmon_temp && attr == hwmon_temp_input) अणु
		temp = chip->hwmon_पढ़ो_temp_reg(phydev);
		अगर (temp < 0)
			वापस temp;

		*value = ((temp & 0xff) - 75) * 1000;

		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops mv3310_hwmon_ops = अणु
	.is_visible = mv3310_hwmon_is_visible,
	.पढ़ो = mv3310_hwmon_पढ़ो,
पूर्ण;

अटल u32 mv3310_hwmon_chip_config[] = अणु
	HWMON_C_REGISTER_TZ | HWMON_C_UPDATE_INTERVAL,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info mv3310_hwmon_chip = अणु
	.type = hwmon_chip,
	.config = mv3310_hwmon_chip_config,
पूर्ण;

अटल u32 mv3310_hwmon_temp_config[] = अणु
	HWMON_T_INPUT,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info mv3310_hwmon_temp = अणु
	.type = hwmon_temp,
	.config = mv3310_hwmon_temp_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *mv3310_hwmon_info[] = अणु
	&mv3310_hwmon_chip,
	&mv3310_hwmon_temp,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info mv3310_hwmon_chip_info = अणु
	.ops = &mv3310_hwmon_ops,
	.info = mv3310_hwmon_info,
पूर्ण;

अटल पूर्णांक mv3310_hwmon_config(काष्ठा phy_device *phydev, bool enable)
अणु
	u16 val;
	पूर्णांक ret;

	अगर (phydev->drv->phy_id != MARVELL_PHY_ID_88X3310)
		वापस 0;

	ret = phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, MV_V2_TEMP,
			    MV_V2_TEMP_UNKNOWN);
	अगर (ret < 0)
		वापस ret;

	val = enable ? MV_V2_TEMP_CTRL_SAMPLE : MV_V2_TEMP_CTRL_DISABLE;

	वापस phy_modअगरy_mmd(phydev, MDIO_MMD_VEND2, MV_V2_TEMP_CTRL,
			      MV_V2_TEMP_CTRL_MASK, val);
पूर्ण

अटल पूर्णांक mv3310_hwmon_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा mv3310_priv *priv = dev_get_drvdata(&phydev->mdio.dev);
	पूर्णांक i, j, ret;

	priv->hwmon_name = devm_kstrdup(dev, dev_name(dev), GFP_KERNEL);
	अगर (!priv->hwmon_name)
		वापस -ENODEV;

	क्रम (i = j = 0; priv->hwmon_name[i]; i++) अणु
		अगर (है_अक्षर_अंक(priv->hwmon_name[i])) अणु
			अगर (i != j)
				priv->hwmon_name[j] = priv->hwmon_name[i];
			j++;
		पूर्ण
	पूर्ण
	priv->hwmon_name[j] = '\0';

	ret = mv3310_hwmon_config(phydev, true);
	अगर (ret)
		वापस ret;

	priv->hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev,
				priv->hwmon_name, phydev,
				&mv3310_hwmon_chip_info, शून्य);

	वापस PTR_ERR_OR_ZERO(priv->hwmon_dev);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mv3310_hwmon_config(काष्ठा phy_device *phydev, bool enable)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mv3310_hwmon_probe(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mv3310_घातer_करोwn(काष्ठा phy_device *phydev)
अणु
	वापस phy_set_bits_mmd(phydev, MDIO_MMD_VEND2, MV_V2_PORT_CTRL,
				MV_V2_PORT_CTRL_PWRDOWN);
पूर्ण

अटल पूर्णांक mv3310_घातer_up(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv3310_priv *priv = dev_get_drvdata(&phydev->mdio.dev);
	पूर्णांक ret;

	ret = phy_clear_bits_mmd(phydev, MDIO_MMD_VEND2, MV_V2_PORT_CTRL,
				 MV_V2_PORT_CTRL_PWRDOWN);

	अगर (phydev->drv->phy_id != MARVELL_PHY_ID_88X3310 ||
	    priv->firmware_ver < 0x00030000)
		वापस ret;

	वापस phy_set_bits_mmd(phydev, MDIO_MMD_VEND2, MV_V2_PORT_CTRL,
				MV_V2_33X0_PORT_CTRL_SWRST);
पूर्ण

अटल पूर्णांक mv3310_reset(काष्ठा phy_device *phydev, u32 unit)
अणु
	पूर्णांक val, err;

	err = phy_modअगरy_mmd(phydev, MDIO_MMD_PCS, unit + MDIO_CTRL1,
			     MDIO_CTRL1_RESET, MDIO_CTRL1_RESET);
	अगर (err < 0)
		वापस err;

	वापस phy_पढ़ो_mmd_poll_समयout(phydev, MDIO_MMD_PCS,
					 unit + MDIO_CTRL1, val,
					 !(val & MDIO_CTRL1_RESET),
					 5000, 100000, true);
पूर्ण

अटल पूर्णांक mv3310_get_edpd(काष्ठा phy_device *phydev, u16 *edpd)
अणु
	पूर्णांक val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MV_PCS_CSCR1);
	अगर (val < 0)
		वापस val;

	चयन (val & MV_PCS_CSCR1_ED_MASK) अणु
	हाल MV_PCS_CSCR1_ED_NLP:
		*edpd = 1000;
		अवरोध;
	हाल MV_PCS_CSCR1_ED_RX:
		*edpd = ETHTOOL_PHY_EDPD_NO_TX;
		अवरोध;
	शेष:
		*edpd = ETHTOOL_PHY_EDPD_DISABLE;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mv3310_set_edpd(काष्ठा phy_device *phydev, u16 edpd)
अणु
	u16 val;
	पूर्णांक err;

	चयन (edpd) अणु
	हाल 1000:
	हाल ETHTOOL_PHY_EDPD_DFLT_TX_MSECS:
		val = MV_PCS_CSCR1_ED_NLP;
		अवरोध;

	हाल ETHTOOL_PHY_EDPD_NO_TX:
		val = MV_PCS_CSCR1_ED_RX;
		अवरोध;

	हाल ETHTOOL_PHY_EDPD_DISABLE:
		val = MV_PCS_CSCR1_ED_OFF;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	err = phy_modअगरy_mmd_changed(phydev, MDIO_MMD_PCS, MV_PCS_CSCR1,
				     MV_PCS_CSCR1_ED_MASK, val);
	अगर (err > 0)
		err = mv3310_reset(phydev, MV_PCS_BASE_T);

	वापस err;
पूर्ण

अटल पूर्णांक mv3310_sfp_insert(व्योम *upstream, स्थिर काष्ठा sfp_eeprom_id *id)
अणु
	काष्ठा phy_device *phydev = upstream;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(support) = अणु 0, पूर्ण;
	phy_पूर्णांकerface_t अगरace;

	sfp_parse_support(phydev->sfp_bus, id, support);
	अगरace = sfp_select_पूर्णांकerface(phydev->sfp_bus, support);

	अगर (अगरace != PHY_INTERFACE_MODE_10GBASER) अणु
		dev_err(&phydev->mdio.dev, "incompatible SFP module inserted\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sfp_upstream_ops mv3310_sfp_ops = अणु
	.attach = phy_sfp_attach,
	.detach = phy_sfp_detach,
	.module_insert = mv3310_sfp_insert,
पूर्ण;

अटल पूर्णांक mv3310_probe(काष्ठा phy_device *phydev)
अणु
	स्थिर काष्ठा mv3310_chip *chip = to_mv3310_chip(phydev);
	काष्ठा mv3310_priv *priv;
	u32 mmd_mask = MDIO_DEVS_PMAPMD | MDIO_DEVS_AN;
	पूर्णांक ret;

	अगर (!phydev->is_c45 ||
	    (phydev->c45_ids.devices_in_package & mmd_mask) != mmd_mask)
		वापस -ENODEV;

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MV_PMA_BOOT);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & MV_PMA_BOOT_FATAL) अणु
		dev_warn(&phydev->mdio.dev,
			 "PHY failed to boot firmware, status=%04x\n", ret);
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(&phydev->mdio.dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(&phydev->mdio.dev, priv);

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MV_PMA_FW_VER0);
	अगर (ret < 0)
		वापस ret;

	priv->firmware_ver = ret << 16;

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MV_PMA_FW_VER1);
	अगर (ret < 0)
		वापस ret;

	priv->firmware_ver |= ret;

	phydev_info(phydev, "Firmware version %u.%u.%u.%u\n",
		    priv->firmware_ver >> 24, (priv->firmware_ver >> 16) & 255,
		    (priv->firmware_ver >> 8) & 255, priv->firmware_ver & 255);

	/* Powering करोwn the port when not in use saves about 600mW */
	ret = mv3310_घातer_करोwn(phydev);
	अगर (ret)
		वापस ret;

	ret = mv3310_hwmon_probe(phydev);
	अगर (ret)
		वापस ret;

	chip->init_supported_पूर्णांकerfaces(priv->supported_पूर्णांकerfaces);

	वापस phy_sfp_probe(phydev, &mv3310_sfp_ops);
पूर्ण

अटल व्योम mv3310_हटाओ(काष्ठा phy_device *phydev)
अणु
	mv3310_hwmon_config(phydev, false);
पूर्ण

अटल पूर्णांक mv3310_suspend(काष्ठा phy_device *phydev)
अणु
	वापस mv3310_घातer_करोwn(phydev);
पूर्ण

अटल पूर्णांक mv3310_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = mv3310_घातer_up(phydev);
	अगर (ret)
		वापस ret;

	वापस mv3310_hwmon_config(phydev, true);
पूर्ण

/* Some PHYs in the Alaska family such as the 88X3310 and the 88E2010
 * करोn't set bit 14 in PMA Extended Abilities (1.11), although they करो
 * support 2.5GBASET and 5GBASET. For these models, we can still पढ़ो their
 * 2.5G/5G extended abilities रेजिस्टर (1.21). We detect these models based on
 * the PMA device identअगरier, with a mask matching models known to have this
 * issue
 */
अटल bool mv3310_has_pma_ngbaset_quirk(काष्ठा phy_device *phydev)
अणु
	अगर (!(phydev->c45_ids.devices_in_package & MDIO_DEVS_PMAPMD))
		वापस false;

	/* Only some revisions of the 88X3310 family PMA seem to be impacted */
	वापस (phydev->c45_ids.device_ids[MDIO_MMD_PMAPMD] &
		MV_PHY_ALASKA_NBT_QUIRK_MASK) == MV_PHY_ALASKA_NBT_QUIRK_REV;
पूर्ण

अटल पूर्णांक mv2110_get_mactype(काष्ठा phy_device *phydev)
अणु
	पूर्णांक mactype;

	mactype = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MV_PMA_21X0_PORT_CTRL);
	अगर (mactype < 0)
		वापस mactype;

	वापस mactype & MV_PMA_21X0_PORT_CTRL_MACTYPE_MASK;
पूर्ण

अटल पूर्णांक mv3310_get_mactype(काष्ठा phy_device *phydev)
अणु
	पूर्णांक mactype;

	mactype = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND2, MV_V2_PORT_CTRL);
	अगर (mactype < 0)
		वापस mactype;

	वापस mactype & MV_V2_33X0_PORT_CTRL_MACTYPE_MASK;
पूर्ण

अटल पूर्णांक mv2110_init_पूर्णांकerface(काष्ठा phy_device *phydev, पूर्णांक mactype)
अणु
	काष्ठा mv3310_priv *priv = dev_get_drvdata(&phydev->mdio.dev);

	priv->rate_match = false;

	अगर (mactype == MV_PMA_21X0_PORT_CTRL_MACTYPE_10GBASER_RATE_MATCH)
		priv->rate_match = true;

	अगर (mactype == MV_PMA_21X0_PORT_CTRL_MACTYPE_USXGMII)
		priv->स्थिर_पूर्णांकerface = PHY_INTERFACE_MODE_USXGMII;
	अन्यथा अगर (mactype == MV_PMA_21X0_PORT_CTRL_MACTYPE_10GBASER_RATE_MATCH)
		priv->स्थिर_पूर्णांकerface = PHY_INTERFACE_MODE_10GBASER;
	अन्यथा अगर (mactype == MV_PMA_21X0_PORT_CTRL_MACTYPE_5GBASER ||
		 mactype == MV_PMA_21X0_PORT_CTRL_MACTYPE_5GBASER_NO_SGMII_AN)
		priv->स्थिर_पूर्णांकerface = PHY_INTERFACE_MODE_NA;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक mv3310_init_पूर्णांकerface(काष्ठा phy_device *phydev, पूर्णांक mactype)
अणु
	काष्ठा mv3310_priv *priv = dev_get_drvdata(&phydev->mdio.dev);

	priv->rate_match = false;

	अगर (mactype == MV_V2_33X0_PORT_CTRL_MACTYPE_10GBASER_RATE_MATCH ||
	    mactype == MV_V2_33X0_PORT_CTRL_MACTYPE_RXAUI_RATE_MATCH ||
	    mactype == MV_V2_3310_PORT_CTRL_MACTYPE_XAUI_RATE_MATCH)
		priv->rate_match = true;

	अगर (mactype == MV_V2_33X0_PORT_CTRL_MACTYPE_USXGMII)
		priv->स्थिर_पूर्णांकerface = PHY_INTERFACE_MODE_USXGMII;
	अन्यथा अगर (mactype == MV_V2_33X0_PORT_CTRL_MACTYPE_10GBASER_RATE_MATCH ||
		 mactype == MV_V2_33X0_PORT_CTRL_MACTYPE_10GBASER_NO_SGMII_AN ||
		 mactype == MV_V2_33X0_PORT_CTRL_MACTYPE_10GBASER)
		priv->स्थिर_पूर्णांकerface = PHY_INTERFACE_MODE_10GBASER;
	अन्यथा अगर (mactype == MV_V2_33X0_PORT_CTRL_MACTYPE_RXAUI_RATE_MATCH ||
		 mactype == MV_V2_33X0_PORT_CTRL_MACTYPE_RXAUI)
		priv->स्थिर_पूर्णांकerface = PHY_INTERFACE_MODE_RXAUI;
	अन्यथा अगर (mactype == MV_V2_3310_PORT_CTRL_MACTYPE_XAUI_RATE_MATCH ||
		 mactype == MV_V2_3310_PORT_CTRL_MACTYPE_XAUI)
		priv->स्थिर_पूर्णांकerface = PHY_INTERFACE_MODE_XAUI;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक mv3340_init_पूर्णांकerface(काष्ठा phy_device *phydev, पूर्णांक mactype)
अणु
	काष्ठा mv3310_priv *priv = dev_get_drvdata(&phydev->mdio.dev);
	पूर्णांक err = 0;

	priv->rate_match = false;

	अगर (mactype == MV_V2_3340_PORT_CTRL_MACTYPE_RXAUI_NO_SGMII_AN)
		priv->स्थिर_पूर्णांकerface = PHY_INTERFACE_MODE_RXAUI;
	अन्यथा
		err = mv3310_init_पूर्णांकerface(phydev, mactype);

	वापस err;
पूर्ण

अटल पूर्णांक mv3310_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv3310_priv *priv = dev_get_drvdata(&phydev->mdio.dev);
	स्थिर काष्ठा mv3310_chip *chip = to_mv3310_chip(phydev);
	पूर्णांक err, mactype;

	/* Check that the PHY पूर्णांकerface type is compatible */
	अगर (!test_bit(phydev->पूर्णांकerface, priv->supported_पूर्णांकerfaces))
		वापस -ENODEV;

	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;

	/* Power up so reset works */
	err = mv3310_घातer_up(phydev);
	अगर (err)
		वापस err;

	mactype = chip->get_mactype(phydev);
	अगर (mactype < 0)
		वापस mactype;

	err = chip->init_पूर्णांकerface(phydev, mactype);
	अगर (err) अणु
		phydev_err(phydev, "MACTYPE configuration invalid\n");
		वापस err;
	पूर्ण

	/* Enable EDPD mode - saving 600mW */
	वापस mv3310_set_edpd(phydev, ETHTOOL_PHY_EDPD_DFLT_TX_MSECS);
पूर्ण

अटल पूर्णांक mv3310_get_features(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret, val;

	ret = genphy_c45_pma_पढ़ो_abilities(phydev);
	अगर (ret)
		वापस ret;

	अगर (mv3310_has_pma_ngbaset_quirk(phydev)) अणु
		val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD,
				   MDIO_PMA_NG_EXTABLE);
		अगर (val < 0)
			वापस val;

		linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_NG_EXTABLE_2_5GBT);

		linkmode_mod_bit(ETHTOOL_LINK_MODE_5000baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_NG_EXTABLE_5GBT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv3310_config_mdix(काष्ठा phy_device *phydev)
अणु
	u16 val;
	पूर्णांक err;

	चयन (phydev->mdix_ctrl) अणु
	हाल ETH_TP_MDI_AUTO:
		val = MV_PCS_CSCR1_MDIX_AUTO;
		अवरोध;
	हाल ETH_TP_MDI_X:
		val = MV_PCS_CSCR1_MDIX_MDIX;
		अवरोध;
	हाल ETH_TP_MDI:
		val = MV_PCS_CSCR1_MDIX_MDI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = phy_modअगरy_mmd_changed(phydev, MDIO_MMD_PCS, MV_PCS_CSCR1,
				     MV_PCS_CSCR1_MDIX_MASK, val);
	अगर (err > 0)
		err = mv3310_reset(phydev, MV_PCS_BASE_T);

	वापस err;
पूर्ण

अटल पूर्णांक mv3310_config_aneg(काष्ठा phy_device *phydev)
अणु
	bool changed = false;
	u16 reg;
	पूर्णांक ret;

	ret = mv3310_config_mdix(phydev);
	अगर (ret < 0)
		वापस ret;

	अगर (phydev->स्वतःneg == AUTONEG_DISABLE)
		वापस genphy_c45_pma_setup_क्रमced(phydev);

	ret = genphy_c45_an_config_aneg(phydev);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		changed = true;

	/* Clause 45 has no standardized support क्रम 1000BaseT, thereक्रमe
	 * use venकरोr रेजिस्टरs क्रम this mode.
	 */
	reg = linkmode_adv_to_mii_ctrl1000_t(phydev->advertising);
	ret = phy_modअगरy_mmd_changed(phydev, MDIO_MMD_AN, MV_AN_CTRL1000,
			     ADVERTISE_1000FULL | ADVERTISE_1000HALF, reg);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		changed = true;

	वापस genphy_c45_check_and_restart_aneg(phydev, changed);
पूर्ण

अटल पूर्णांक mv3310_aneg_करोne(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MV_PCS_BASE_R + MDIO_STAT1);
	अगर (val < 0)
		वापस val;

	अगर (val & MDIO_STAT1_LSTATUS)
		वापस 1;

	वापस genphy_c45_aneg_करोne(phydev);
पूर्ण

अटल व्योम mv3310_update_पूर्णांकerface(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv3310_priv *priv = dev_get_drvdata(&phydev->mdio.dev);

	अगर (!phydev->link)
		वापस;

	/* In all of the "* with Rate Matching" modes the PHY पूर्णांकerface is fixed
	 * at 10Gb. The PHY adapts the rate to actual wire speed with help of
	 * पूर्णांकernal 16KB buffer.
	 *
	 * In USXGMII mode the PHY पूर्णांकerface mode is also fixed.
	 */
	अगर (priv->rate_match ||
	    priv->स्थिर_पूर्णांकerface == PHY_INTERFACE_MODE_USXGMII) अणु
		phydev->पूर्णांकerface = priv->स्थिर_पूर्णांकerface;
		वापस;
	पूर्ण

	/* The PHY स्वतःmatically चयनes its serdes पूर्णांकerface (and active PHYXS
	 * instance) between Cisco SGMII, 2500BaseX, 5GBase-R and 10GBase-R /
	 * xaui / rxaui modes according to the speed.
	 * Florian suggests setting phydev->पूर्णांकerface to communicate this to the
	 * MAC. Only करो this अगर we are alपढ़ोy in one of the above modes.
	 */
	चयन (phydev->speed) अणु
	हाल SPEED_10000:
		phydev->पूर्णांकerface = priv->स्थिर_पूर्णांकerface;
		अवरोध;
	हाल SPEED_5000:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_5GBASER;
		अवरोध;
	हाल SPEED_2500:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_2500BASEX;
		अवरोध;
	हाल SPEED_1000:
	हाल SPEED_100:
	हाल SPEED_10:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* 10GBASE-ER,LR,LRM,SR करो not support स्वतःnegotiation. */
अटल पूर्णांक mv3310_पढ़ो_status_10gbaser(काष्ठा phy_device *phydev)
अणु
	phydev->link = 1;
	phydev->speed = SPEED_10000;
	phydev->duplex = DUPLEX_FULL;
	phydev->port = PORT_FIBRE;

	वापस 0;
पूर्ण

अटल पूर्णांक mv3310_पढ़ो_status_copper(काष्ठा phy_device *phydev)
अणु
	पूर्णांक cssr1, speed, val;

	val = genphy_c45_पढ़ो_link(phydev);
	अगर (val < 0)
		वापस val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	अगर (val < 0)
		वापस val;

	cssr1 = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MV_PCS_CSSR1);
	अगर (cssr1 < 0)
		वापस val;

	/* If the link settings are not resolved, mark the link करोwn */
	अगर (!(cssr1 & MV_PCS_CSSR1_RESOLVED)) अणु
		phydev->link = 0;
		वापस 0;
	पूर्ण

	/* Read the copper link settings */
	speed = cssr1 & MV_PCS_CSSR1_SPD1_MASK;
	अगर (speed == MV_PCS_CSSR1_SPD1_SPD2)
		speed |= cssr1 & MV_PCS_CSSR1_SPD2_MASK;

	चयन (speed) अणु
	हाल MV_PCS_CSSR1_SPD1_SPD2 | MV_PCS_CSSR1_SPD2_10000:
		phydev->speed = SPEED_10000;
		अवरोध;

	हाल MV_PCS_CSSR1_SPD1_SPD2 | MV_PCS_CSSR1_SPD2_5000:
		phydev->speed = SPEED_5000;
		अवरोध;

	हाल MV_PCS_CSSR1_SPD1_SPD2 | MV_PCS_CSSR1_SPD2_2500:
		phydev->speed = SPEED_2500;
		अवरोध;

	हाल MV_PCS_CSSR1_SPD1_1000:
		phydev->speed = SPEED_1000;
		अवरोध;

	हाल MV_PCS_CSSR1_SPD1_100:
		phydev->speed = SPEED_100;
		अवरोध;

	हाल MV_PCS_CSSR1_SPD1_10:
		phydev->speed = SPEED_10;
		अवरोध;
	पूर्ण

	phydev->duplex = cssr1 & MV_PCS_CSSR1_DUPLEX_FULL ?
			 DUPLEX_FULL : DUPLEX_HALF;
	phydev->port = PORT_TP;
	phydev->mdix = cssr1 & MV_PCS_CSSR1_MDIX ?
		       ETH_TP_MDI_X : ETH_TP_MDI;

	अगर (val & MDIO_AN_STAT1_COMPLETE) अणु
		val = genphy_c45_पढ़ो_lpa(phydev);
		अगर (val < 0)
			वापस val;

		/* Read the link partner's 1G advertisement */
		val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MV_AN_STAT1000);
		अगर (val < 0)
			वापस val;

		mii_stat1000_mod_linkmode_lpa_t(phydev->lp_advertising, val);

		/* Update the छोड़ो status */
		phy_resolve_aneg_छोड़ो(phydev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv3310_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err, val;

	phydev->speed = SPEED_UNKNOWN;
	phydev->duplex = DUPLEX_UNKNOWN;
	linkmode_zero(phydev->lp_advertising);
	phydev->link = 0;
	phydev->छोड़ो = 0;
	phydev->asym_छोड़ो = 0;
	phydev->mdix = ETH_TP_MDI_INVALID;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MV_PCS_BASE_R + MDIO_STAT1);
	अगर (val < 0)
		वापस val;

	अगर (val & MDIO_STAT1_LSTATUS)
		err = mv3310_पढ़ो_status_10gbaser(phydev);
	अन्यथा
		err = mv3310_पढ़ो_status_copper(phydev);
	अगर (err < 0)
		वापस err;

	अगर (phydev->link)
		mv3310_update_पूर्णांकerface(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक mv3310_get_tunable(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_EDPD:
		वापस mv3310_get_edpd(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mv3310_set_tunable(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_EDPD:
		वापस mv3310_set_edpd(phydev, *(u16 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम mv3310_init_supported_पूर्णांकerfaces(अचिन्हित दीर्घ *mask)
अणु
	__set_bit(PHY_INTERFACE_MODE_SGMII, mask);
	__set_bit(PHY_INTERFACE_MODE_2500BASEX, mask);
	__set_bit(PHY_INTERFACE_MODE_5GBASER, mask);
	__set_bit(PHY_INTERFACE_MODE_XAUI, mask);
	__set_bit(PHY_INTERFACE_MODE_RXAUI, mask);
	__set_bit(PHY_INTERFACE_MODE_10GBASER, mask);
	__set_bit(PHY_INTERFACE_MODE_USXGMII, mask);
पूर्ण

अटल व्योम mv3340_init_supported_पूर्णांकerfaces(अचिन्हित दीर्घ *mask)
अणु
	__set_bit(PHY_INTERFACE_MODE_SGMII, mask);
	__set_bit(PHY_INTERFACE_MODE_2500BASEX, mask);
	__set_bit(PHY_INTERFACE_MODE_5GBASER, mask);
	__set_bit(PHY_INTERFACE_MODE_RXAUI, mask);
	__set_bit(PHY_INTERFACE_MODE_10GBASER, mask);
	__set_bit(PHY_INTERFACE_MODE_USXGMII, mask);
पूर्ण

अटल व्योम mv2110_init_supported_पूर्णांकerfaces(अचिन्हित दीर्घ *mask)
अणु
	__set_bit(PHY_INTERFACE_MODE_SGMII, mask);
	__set_bit(PHY_INTERFACE_MODE_2500BASEX, mask);
	__set_bit(PHY_INTERFACE_MODE_5GBASER, mask);
	__set_bit(PHY_INTERFACE_MODE_10GBASER, mask);
	__set_bit(PHY_INTERFACE_MODE_USXGMII, mask);
पूर्ण

अटल व्योम mv2111_init_supported_पूर्णांकerfaces(अचिन्हित दीर्घ *mask)
अणु
	__set_bit(PHY_INTERFACE_MODE_SGMII, mask);
	__set_bit(PHY_INTERFACE_MODE_2500BASEX, mask);
	__set_bit(PHY_INTERFACE_MODE_10GBASER, mask);
	__set_bit(PHY_INTERFACE_MODE_USXGMII, mask);
पूर्ण

अटल स्थिर काष्ठा mv3310_chip mv3310_type = अणु
	.init_supported_पूर्णांकerfaces = mv3310_init_supported_पूर्णांकerfaces,
	.get_mactype = mv3310_get_mactype,
	.init_पूर्णांकerface = mv3310_init_पूर्णांकerface,

#अगर_घोषित CONFIG_HWMON
	.hwmon_पढ़ो_temp_reg = mv3310_hwmon_पढ़ो_temp_reg,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा mv3310_chip mv3340_type = अणु
	.init_supported_पूर्णांकerfaces = mv3340_init_supported_पूर्णांकerfaces,
	.get_mactype = mv3310_get_mactype,
	.init_पूर्णांकerface = mv3340_init_पूर्णांकerface,

#अगर_घोषित CONFIG_HWMON
	.hwmon_पढ़ो_temp_reg = mv3310_hwmon_पढ़ो_temp_reg,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा mv3310_chip mv2110_type = अणु
	.init_supported_पूर्णांकerfaces = mv2110_init_supported_पूर्णांकerfaces,
	.get_mactype = mv2110_get_mactype,
	.init_पूर्णांकerface = mv2110_init_पूर्णांकerface,

#अगर_घोषित CONFIG_HWMON
	.hwmon_पढ़ो_temp_reg = mv2110_hwmon_पढ़ो_temp_reg,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा mv3310_chip mv2111_type = अणु
	.init_supported_पूर्णांकerfaces = mv2111_init_supported_पूर्णांकerfaces,
	.get_mactype = mv2110_get_mactype,
	.init_पूर्णांकerface = mv2110_init_पूर्णांकerface,

#अगर_घोषित CONFIG_HWMON
	.hwmon_पढ़ो_temp_reg = mv2110_hwmon_पढ़ो_temp_reg,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mv211x_match_phy_device(काष्ठा phy_device *phydev, bool has_5g)
अणु
	पूर्णांक val;

	अगर ((phydev->c45_ids.device_ids[MDIO_MMD_PMAPMD] &
	     MARVELL_PHY_ID_MASK) != MARVELL_PHY_ID_88E2110)
		वापस 0;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MDIO_SPEED);
	अगर (val < 0)
		वापस val;

	वापस !!(val & MDIO_PCS_SPEED_5G) == has_5g;
पूर्ण

अटल पूर्णांक mv2110_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस mv211x_match_phy_device(phydev, true);
पूर्ण

अटल पूर्णांक mv2111_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस mv211x_match_phy_device(phydev, false);
पूर्ण

अटल काष्ठा phy_driver mv3310_drivers[] = अणु
	अणु
		.phy_id		= MARVELL_PHY_ID_88X3310,
		.phy_id_mask	= MARVELL_PHY_ID_88X33X0_MASK,
		.name		= "mv88x3310",
		.driver_data	= &mv3310_type,
		.get_features	= mv3310_get_features,
		.config_init	= mv3310_config_init,
		.probe		= mv3310_probe,
		.suspend	= mv3310_suspend,
		.resume		= mv3310_resume,
		.config_aneg	= mv3310_config_aneg,
		.aneg_करोne	= mv3310_aneg_करोne,
		.पढ़ो_status	= mv3310_पढ़ो_status,
		.get_tunable	= mv3310_get_tunable,
		.set_tunable	= mv3310_set_tunable,
		.हटाओ		= mv3310_हटाओ,
		.set_loopback	= genphy_c45_loopback,
	पूर्ण,
	अणु
		.phy_id		= MARVELL_PHY_ID_88X3340,
		.phy_id_mask	= MARVELL_PHY_ID_88X33X0_MASK,
		.name		= "mv88x3340",
		.driver_data	= &mv3340_type,
		.get_features	= mv3310_get_features,
		.config_init	= mv3310_config_init,
		.probe		= mv3310_probe,
		.suspend	= mv3310_suspend,
		.resume		= mv3310_resume,
		.config_aneg	= mv3310_config_aneg,
		.aneg_करोne	= mv3310_aneg_करोne,
		.पढ़ो_status	= mv3310_पढ़ो_status,
		.get_tunable	= mv3310_get_tunable,
		.set_tunable	= mv3310_set_tunable,
		.हटाओ		= mv3310_हटाओ,
		.set_loopback	= genphy_c45_loopback,
	पूर्ण,
	अणु
		.phy_id		= MARVELL_PHY_ID_88E2110,
		.phy_id_mask	= MARVELL_PHY_ID_MASK,
		.match_phy_device = mv2110_match_phy_device,
		.name		= "mv88e2110",
		.driver_data	= &mv2110_type,
		.probe		= mv3310_probe,
		.suspend	= mv3310_suspend,
		.resume		= mv3310_resume,
		.config_init	= mv3310_config_init,
		.config_aneg	= mv3310_config_aneg,
		.aneg_करोne	= mv3310_aneg_करोne,
		.पढ़ो_status	= mv3310_पढ़ो_status,
		.get_tunable	= mv3310_get_tunable,
		.set_tunable	= mv3310_set_tunable,
		.हटाओ		= mv3310_हटाओ,
		.set_loopback	= genphy_c45_loopback,
	पूर्ण,
	अणु
		.phy_id		= MARVELL_PHY_ID_88E2110,
		.phy_id_mask	= MARVELL_PHY_ID_MASK,
		.match_phy_device = mv2111_match_phy_device,
		.name		= "mv88e2111",
		.driver_data	= &mv2111_type,
		.probe		= mv3310_probe,
		.suspend	= mv3310_suspend,
		.resume		= mv3310_resume,
		.config_init	= mv3310_config_init,
		.config_aneg	= mv3310_config_aneg,
		.aneg_करोne	= mv3310_aneg_करोne,
		.पढ़ो_status	= mv3310_पढ़ो_status,
		.get_tunable	= mv3310_get_tunable,
		.set_tunable	= mv3310_set_tunable,
		.हटाओ		= mv3310_हटाओ,
		.set_loopback	= genphy_c45_loopback,
	पूर्ण,
पूर्ण;

module_phy_driver(mv3310_drivers);

अटल काष्ठा mdio_device_id __maybe_unused mv3310_tbl[] = अणु
	अणु MARVELL_PHY_ID_88X3310, MARVELL_PHY_ID_88X33X0_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88X3340, MARVELL_PHY_ID_88X33X0_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E2110, MARVELL_PHY_ID_MASK पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(mdio, mv3310_tbl);
MODULE_DESCRIPTION("Marvell Alaska X/M multi-gigabit Ethernet PHY driver");
MODULE_LICENSE("GPL");
