<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/mdपन.स: definitions क्रम MDIO (clause 45) transceivers
 * Copyright 2006-2009 Solarflare Communications Inc.
 */
#अगर_अघोषित __LINUX_MDIO_H__
#घोषणा __LINUX_MDIO_H__

#समावेश <uapi/linux/mdपन.स>
#समावेश <linux/mod_devicetable.h>

/* Or MII_ADDR_C45 पूर्णांकo regnum क्रम पढ़ो/ग_लिखो on mii_bus to enable the 21 bit
 * IEEE 802.3ae clause 45 addressing mode used by 10GIGE phy chips.
 */
#घोषणा MII_ADDR_C45		(1<<30)
#घोषणा MII_DEVADDR_C45_SHIFT	16
#घोषणा MII_REGADDR_C45_MASK	GENMASK(15, 0)

काष्ठा gpio_desc;
काष्ठा mii_bus;
काष्ठा reset_control;

/* Multiple levels of nesting are possible. However typically this is
 * limited to nested DSA like layer, a MUX layer, and the normal
 * user. Instead of trying to handle the general हाल, just define
 * these हालs.
 */
क्रमागत mdio_mutex_lock_class अणु
	MDIO_MUTEX_NORMAL,
	MDIO_MUTEX_MUX,
	MDIO_MUTEX_NESTED,
पूर्ण;

काष्ठा mdio_device अणु
	काष्ठा device dev;

	काष्ठा mii_bus *bus;
	अक्षर modalias[MDIO_NAME_SIZE];

	पूर्णांक (*bus_match)(काष्ठा device *dev, काष्ठा device_driver *drv);
	व्योम (*device_मुक्त)(काष्ठा mdio_device *mdiodev);
	व्योम (*device_हटाओ)(काष्ठा mdio_device *mdiodev);

	/* Bus address of the MDIO device (0-31) */
	पूर्णांक addr;
	पूर्णांक flags;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा reset_control *reset_ctrl;
	अचिन्हित पूर्णांक reset_निश्चित_delay;
	अचिन्हित पूर्णांक reset_deनिश्चित_delay;
पूर्ण;

अटल अंतरभूत काष्ठा mdio_device *to_mdio_device(स्थिर काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा mdio_device, dev);
पूर्ण

/* काष्ठा mdio_driver_common: Common to all MDIO drivers */
काष्ठा mdio_driver_common अणु
	काष्ठा device_driver driver;
	पूर्णांक flags;
पूर्ण;
#घोषणा MDIO_DEVICE_FLAG_PHY		1

अटल अंतरभूत काष्ठा mdio_driver_common *
to_mdio_common_driver(स्थिर काष्ठा device_driver *driver)
अणु
	वापस container_of(driver, काष्ठा mdio_driver_common, driver);
पूर्ण

/* काष्ठा mdio_driver: Generic MDIO driver */
काष्ठा mdio_driver अणु
	काष्ठा mdio_driver_common mdiodrv;

	/*
	 * Called during discovery.  Used to set
	 * up device-specअगरic काष्ठाures, अगर any
	 */
	पूर्णांक (*probe)(काष्ठा mdio_device *mdiodev);

	/* Clears up any memory अगर needed */
	व्योम (*हटाओ)(काष्ठा mdio_device *mdiodev);
पूर्ण;

अटल अंतरभूत काष्ठा mdio_driver *
to_mdio_driver(स्थिर काष्ठा device_driver *driver)
अणु
	वापस container_of(to_mdio_common_driver(driver), काष्ठा mdio_driver,
			    mdiodrv);
पूर्ण

/* device driver data */
अटल अंतरभूत व्योम mdiodev_set_drvdata(काष्ठा mdio_device *mdio, व्योम *data)
अणु
	dev_set_drvdata(&mdio->dev, data);
पूर्ण

अटल अंतरभूत व्योम *mdiodev_get_drvdata(काष्ठा mdio_device *mdio)
अणु
	वापस dev_get_drvdata(&mdio->dev);
पूर्ण

व्योम mdio_device_मुक्त(काष्ठा mdio_device *mdiodev);
काष्ठा mdio_device *mdio_device_create(काष्ठा mii_bus *bus, पूर्णांक addr);
पूर्णांक mdio_device_रेजिस्टर(काष्ठा mdio_device *mdiodev);
व्योम mdio_device_हटाओ(काष्ठा mdio_device *mdiodev);
व्योम mdio_device_reset(काष्ठा mdio_device *mdiodev, पूर्णांक value);
पूर्णांक mdio_driver_रेजिस्टर(काष्ठा mdio_driver *drv);
व्योम mdio_driver_unरेजिस्टर(काष्ठा mdio_driver *drv);
पूर्णांक mdio_device_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv);

अटल अंतरभूत bool mdio_phy_id_is_c45(पूर्णांक phy_id)
अणु
	वापस (phy_id & MDIO_PHY_ID_C45) && !(phy_id & ~MDIO_PHY_ID_C45_MASK);
पूर्ण

अटल अंतरभूत __u16 mdio_phy_id_prtad(पूर्णांक phy_id)
अणु
	वापस (phy_id & MDIO_PHY_ID_PRTAD) >> 5;
पूर्ण

अटल अंतरभूत __u16 mdio_phy_id_devad(पूर्णांक phy_id)
अणु
	वापस phy_id & MDIO_PHY_ID_DEVAD;
पूर्ण

/**
 * काष्ठा mdio_अगर_info - Ethernet controller MDIO पूर्णांकerface
 * @prtad: PRTAD of the PHY (%MDIO_PRTAD_NONE अगर not present/unknown)
 * @mmds: Mask of MMDs expected to be present in the PHY.  This must be
 *	non-zero unless @prtad = %MDIO_PRTAD_NONE.
 * @mode_support: MDIO modes supported.  If %MDIO_SUPPORTS_C22 is set then
 *	MII रेजिस्टर access will be passed through with @devad =
 *	%MDIO_DEVAD_NONE.  If %MDIO_EMULATE_C22 is set then access to
 *	commonly used clause 22 रेजिस्टरs will be translated पूर्णांकo
 *	clause 45 रेजिस्टरs.
 * @dev: Net device काष्ठाure
 * @mdio_पढ़ो: Register पढ़ो function; वापसs value or negative error code
 * @mdio_ग_लिखो: Register ग_लिखो function; वापसs 0 or negative error code
 */
काष्ठा mdio_अगर_info अणु
	पूर्णांक prtad;
	u32 mmds;
	अचिन्हित mode_support;

	काष्ठा net_device *dev;
	पूर्णांक (*mdio_पढ़ो)(काष्ठा net_device *dev, पूर्णांक prtad, पूर्णांक devad,
			 u16 addr);
	पूर्णांक (*mdio_ग_लिखो)(काष्ठा net_device *dev, पूर्णांक prtad, पूर्णांक devad,
			  u16 addr, u16 val);
पूर्ण;

#घोषणा MDIO_PRTAD_NONE			(-1)
#घोषणा MDIO_DEVAD_NONE			(-1)
#घोषणा MDIO_SUPPORTS_C22		1
#घोषणा MDIO_SUPPORTS_C45		2
#घोषणा MDIO_EMULATE_C22		4

काष्ठा ethtool_cmd;
काष्ठा ethtool_छोड़ोparam;
बाह्य पूर्णांक mdio45_probe(काष्ठा mdio_अगर_info *mdio, पूर्णांक prtad);
बाह्य पूर्णांक mdio_set_flag(स्थिर काष्ठा mdio_अगर_info *mdio,
			 पूर्णांक prtad, पूर्णांक devad, u16 addr, पूर्णांक mask,
			 bool sense);
बाह्य पूर्णांक mdio45_links_ok(स्थिर काष्ठा mdio_अगर_info *mdio, u32 mmds);
बाह्य पूर्णांक mdio45_nway_restart(स्थिर काष्ठा mdio_अगर_info *mdio);
बाह्य व्योम mdio45_ethtool_gset_npage(स्थिर काष्ठा mdio_अगर_info *mdio,
				      काष्ठा ethtool_cmd *ecmd,
				      u32 npage_adv, u32 npage_lpa);
बाह्य व्योम
mdio45_ethtool_ksettings_get_npage(स्थिर काष्ठा mdio_अगर_info *mdio,
				   काष्ठा ethtool_link_ksettings *cmd,
				   u32 npage_adv, u32 npage_lpa);

/**
 * mdio45_ethtool_gset - get settings क्रम ETHTOOL_GSET
 * @mdio: MDIO पूर्णांकerface
 * @ecmd: Ethtool request काष्ठाure
 *
 * Since the CSRs क्रम स्वतः-negotiation using next pages are not fully
 * standardised, this function करोes not attempt to decode them.  Use
 * mdio45_ethtool_gset_npage() to specअगरy advertisement bits from next
 * pages.
 */
अटल अंतरभूत व्योम mdio45_ethtool_gset(स्थिर काष्ठा mdio_अगर_info *mdio,
				       काष्ठा ethtool_cmd *ecmd)
अणु
	mdio45_ethtool_gset_npage(mdio, ecmd, 0, 0);
पूर्ण

/**
 * mdio45_ethtool_ksettings_get - get settings क्रम ETHTOOL_GLINKSETTINGS
 * @mdio: MDIO पूर्णांकerface
 * @cmd: Ethtool request काष्ठाure
 *
 * Since the CSRs क्रम स्वतः-negotiation using next pages are not fully
 * standardised, this function करोes not attempt to decode them.  Use
 * mdio45_ethtool_ksettings_get_npage() to specअगरy advertisement bits
 * from next pages.
 */
अटल अंतरभूत व्योम
mdio45_ethtool_ksettings_get(स्थिर काष्ठा mdio_अगर_info *mdio,
			     काष्ठा ethtool_link_ksettings *cmd)
अणु
	mdio45_ethtool_ksettings_get_npage(mdio, cmd, 0, 0);
पूर्ण

बाह्य पूर्णांक mdio_mii_ioctl(स्थिर काष्ठा mdio_अगर_info *mdio,
			  काष्ठा mii_ioctl_data *mii_data, पूर्णांक cmd);

/**
 * mmd_eee_cap_to_ethtool_sup_t
 * @eee_cap: value of the MMD EEE Capability रेजिस्टर
 *
 * A small helper function that translates MMD EEE Capability (3.20) bits
 * to ethtool supported settings.
 */
अटल अंतरभूत u32 mmd_eee_cap_to_ethtool_sup_t(u16 eee_cap)
अणु
	u32 supported = 0;

	अगर (eee_cap & MDIO_EEE_100TX)
		supported |= SUPPORTED_100baseT_Full;
	अगर (eee_cap & MDIO_EEE_1000T)
		supported |= SUPPORTED_1000baseT_Full;
	अगर (eee_cap & MDIO_EEE_10GT)
		supported |= SUPPORTED_10000baseT_Full;
	अगर (eee_cap & MDIO_EEE_1000KX)
		supported |= SUPPORTED_1000baseKX_Full;
	अगर (eee_cap & MDIO_EEE_10GKX4)
		supported |= SUPPORTED_10000baseKX4_Full;
	अगर (eee_cap & MDIO_EEE_10GKR)
		supported |= SUPPORTED_10000baseKR_Full;

	वापस supported;
पूर्ण

/**
 * mmd_eee_adv_to_ethtool_adv_t
 * @eee_adv: value of the MMD EEE Advertisement/Link Partner Ability रेजिस्टरs
 *
 * A small helper function that translates the MMD EEE Advertisment (7.60)
 * and MMD EEE Link Partner Ability (7.61) bits to ethtool advertisement
 * settings.
 */
अटल अंतरभूत u32 mmd_eee_adv_to_ethtool_adv_t(u16 eee_adv)
अणु
	u32 adv = 0;

	अगर (eee_adv & MDIO_EEE_100TX)
		adv |= ADVERTISED_100baseT_Full;
	अगर (eee_adv & MDIO_EEE_1000T)
		adv |= ADVERTISED_1000baseT_Full;
	अगर (eee_adv & MDIO_EEE_10GT)
		adv |= ADVERTISED_10000baseT_Full;
	अगर (eee_adv & MDIO_EEE_1000KX)
		adv |= ADVERTISED_1000baseKX_Full;
	अगर (eee_adv & MDIO_EEE_10GKX4)
		adv |= ADVERTISED_10000baseKX4_Full;
	अगर (eee_adv & MDIO_EEE_10GKR)
		adv |= ADVERTISED_10000baseKR_Full;

	वापस adv;
पूर्ण

/**
 * ethtool_adv_to_mmd_eee_adv_t
 * @adv: the ethtool advertisement settings
 *
 * A small helper function that translates ethtool advertisement settings
 * to EEE advertisements क्रम the MMD EEE Advertisement (7.60) and
 * MMD EEE Link Partner Ability (7.61) रेजिस्टरs.
 */
अटल अंतरभूत u16 ethtool_adv_to_mmd_eee_adv_t(u32 adv)
अणु
	u16 reg = 0;

	अगर (adv & ADVERTISED_100baseT_Full)
		reg |= MDIO_EEE_100TX;
	अगर (adv & ADVERTISED_1000baseT_Full)
		reg |= MDIO_EEE_1000T;
	अगर (adv & ADVERTISED_10000baseT_Full)
		reg |= MDIO_EEE_10GT;
	अगर (adv & ADVERTISED_1000baseKX_Full)
		reg |= MDIO_EEE_1000KX;
	अगर (adv & ADVERTISED_10000baseKX4_Full)
		reg |= MDIO_EEE_10GKX4;
	अगर (adv & ADVERTISED_10000baseKR_Full)
		reg |= MDIO_EEE_10GKR;

	वापस reg;
पूर्ण

/**
 * linkmode_adv_to_mii_10gbt_adv_t
 * @advertising: the linkmode advertisement settings
 *
 * A small helper function that translates linkmode advertisement
 * settings to phy स्वतःnegotiation advertisements क्रम the C45
 * 10GBASE-T AN CONTROL (7.32) रेजिस्टर.
 */
अटल अंतरभूत u32 linkmode_adv_to_mii_10gbt_adv_t(अचिन्हित दीर्घ *advertising)
अणु
	u32 result = 0;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
			      advertising))
		result |= MDIO_AN_10GBT_CTRL_ADV2_5G;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_5000baseT_Full_BIT,
			      advertising))
		result |= MDIO_AN_10GBT_CTRL_ADV5G;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
			      advertising))
		result |= MDIO_AN_10GBT_CTRL_ADV10G;

	वापस result;
पूर्ण

/**
 * mii_10gbt_stat_mod_linkmode_lpa_t
 * @advertising: target the linkmode advertisement settings
 * @lpa: value of the C45 10GBASE-T AN STATUS रेजिस्टर
 *
 * A small helper function that translates C45 10GBASE-T AN STATUS रेजिस्टर bits
 * to linkmode advertisement settings. Other bits in advertising aren't changed.
 */
अटल अंतरभूत व्योम mii_10gbt_stat_mod_linkmode_lpa_t(अचिन्हित दीर्घ *advertising,
						     u32 lpa)
अणु
	linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
			 advertising, lpa & MDIO_AN_10GBT_STAT_LP2_5G);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_5000baseT_Full_BIT,
			 advertising, lpa & MDIO_AN_10GBT_STAT_LP5G);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
			 advertising, lpa & MDIO_AN_10GBT_STAT_LP10G);
पूर्ण

पूर्णांक __mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum);
पूर्णांक __mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum, u16 val);
पूर्णांक __mdiobus_modअगरy_changed(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum,
			     u16 mask, u16 set);

पूर्णांक mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum);
पूर्णांक mdiobus_पढ़ो_nested(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum);
पूर्णांक mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum, u16 val);
पूर्णांक mdiobus_ग_लिखो_nested(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum, u16 val);
पूर्णांक mdiobus_modअगरy(काष्ठा mii_bus *bus, पूर्णांक addr, u32 regnum, u16 mask,
		   u16 set);

अटल अंतरभूत u32 mdiobus_c45_addr(पूर्णांक devad, u16 regnum)
अणु
	वापस MII_ADDR_C45 | devad << MII_DEVADDR_C45_SHIFT | regnum;
पूर्ण

अटल अंतरभूत पूर्णांक __mdiobus_c45_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक prtad, पूर्णांक devad,
				     u16 regnum)
अणु
	वापस __mdiobus_पढ़ो(bus, prtad, mdiobus_c45_addr(devad, regnum));
पूर्ण

अटल अंतरभूत पूर्णांक __mdiobus_c45_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक prtad, पूर्णांक devad,
				      u16 regnum, u16 val)
अणु
	वापस __mdiobus_ग_लिखो(bus, prtad, mdiobus_c45_addr(devad, regnum),
			       val);
पूर्ण

अटल अंतरभूत पूर्णांक mdiobus_c45_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक prtad, पूर्णांक devad,
				   u16 regnum)
अणु
	वापस mdiobus_पढ़ो(bus, prtad, mdiobus_c45_addr(devad, regnum));
पूर्ण

अटल अंतरभूत पूर्णांक mdiobus_c45_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक prtad, पूर्णांक devad,
				    u16 regnum, u16 val)
अणु
	वापस mdiobus_ग_लिखो(bus, prtad, mdiobus_c45_addr(devad, regnum), val);
पूर्ण

पूर्णांक mdiobus_रेजिस्टर_device(काष्ठा mdio_device *mdiodev);
पूर्णांक mdiobus_unरेजिस्टर_device(काष्ठा mdio_device *mdiodev);
bool mdiobus_is_रेजिस्टरed_device(काष्ठा mii_bus *bus, पूर्णांक addr);
काष्ठा phy_device *mdiobus_get_phy(काष्ठा mii_bus *bus, पूर्णांक addr);

/**
 * mdio_module_driver() - Helper macro क्रम रेजिस्टरing mdio drivers
 * @_mdio_driver: driver to रेजिस्टर
 *
 * Helper macro क्रम MDIO drivers which करो not करो anything special in module
 * init/निकास. Each module may only use this macro once, and calling it
 * replaces module_init() and module_निकास().
 */
#घोषणा mdio_module_driver(_mdio_driver)				\
अटल पूर्णांक __init mdio_module_init(व्योम)				\
अणु									\
	वापस mdio_driver_रेजिस्टर(&_mdio_driver);			\
पूर्ण									\
module_init(mdio_module_init);						\
अटल व्योम __निकास mdio_module_निकास(व्योम)				\
अणु									\
	mdio_driver_unरेजिस्टर(&_mdio_driver);				\
पूर्ण									\
module_निकास(mdio_module_निकास)

#पूर्ण_अगर /* __LINUX_MDIO_H__ */
