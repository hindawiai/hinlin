<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/mii.h: definitions क्रम MII-compatible transceivers
 * Originally drivers/net/sunhme.h.
 *
 * Copyright (C) 1996, 1999, 2001 David S. Miller (davem@redhat.com)
 */
#अगर_अघोषित __LINUX_MII_H__
#घोषणा __LINUX_MII_H__


#समावेश <linux/अगर.h>
#समावेश <linux/linkmode.h>
#समावेश <uapi/linux/mii.h>

काष्ठा ethtool_cmd;

काष्ठा mii_अगर_info अणु
	पूर्णांक phy_id;
	पूर्णांक advertising;
	पूर्णांक phy_id_mask;
	पूर्णांक reg_num_mask;

	अचिन्हित पूर्णांक full_duplex : 1;	/* is full duplex? */
	अचिन्हित पूर्णांक क्रमce_media : 1;	/* is स्वतःneg. disabled? */
	अचिन्हित पूर्णांक supports_gmii : 1; /* are GMII रेजिस्टरs supported? */

	काष्ठा net_device *dev;
	पूर्णांक (*mdio_पढ़ो) (काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location);
	व्योम (*mdio_ग_लिखो) (काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक location, पूर्णांक val);
पूर्ण;

बाह्य पूर्णांक mii_link_ok (काष्ठा mii_अगर_info *mii);
बाह्य पूर्णांक mii_nway_restart (काष्ठा mii_अगर_info *mii);
बाह्य पूर्णांक mii_ethtool_gset(काष्ठा mii_अगर_info *mii, काष्ठा ethtool_cmd *ecmd);
बाह्य व्योम mii_ethtool_get_link_ksettings(
	काष्ठा mii_अगर_info *mii, काष्ठा ethtool_link_ksettings *cmd);
बाह्य पूर्णांक mii_ethtool_sset(काष्ठा mii_अगर_info *mii, काष्ठा ethtool_cmd *ecmd);
बाह्य पूर्णांक mii_ethtool_set_link_ksettings(
	काष्ठा mii_अगर_info *mii, स्थिर काष्ठा ethtool_link_ksettings *cmd);
बाह्य पूर्णांक mii_check_gmii_support(काष्ठा mii_अगर_info *mii);
बाह्य व्योम mii_check_link (काष्ठा mii_अगर_info *mii);
बाह्य अचिन्हित पूर्णांक mii_check_media (काष्ठा mii_अगर_info *mii,
				     अचिन्हित पूर्णांक ok_to_prपूर्णांक,
				     अचिन्हित पूर्णांक init_media);
बाह्य पूर्णांक generic_mii_ioctl(काष्ठा mii_अगर_info *mii_अगर,
			     काष्ठा mii_ioctl_data *mii_data, पूर्णांक cmd,
			     अचिन्हित पूर्णांक *duplex_changed);


अटल अंतरभूत काष्ठा mii_ioctl_data *अगर_mii(काष्ठा अगरreq *rq)
अणु
	वापस (काष्ठा mii_ioctl_data *) &rq->अगरr_अगरru;
पूर्ण

/**
 * mii_nway_result
 * @negotiated: value of MII ANAR and'd with ANLPAR
 *
 * Given a set of MII abilities, check each bit and वापसs the
 * currently supported media, in the priority order defined by
 * IEEE 802.3u.  We use LPA_xxx स्थिरants but note this is not the
 * value of LPA solely, as described above.
 *
 * The one exception to IEEE 802.3u is that 100baseT4 is placed
 * between 100T-full and 100T-half.  If your phy करोes not support
 * 100T4 this is fine.  If your phy places 100T4 अन्यथाwhere in the
 * priority order, you will need to roll your own function.
 */
अटल अंतरभूत अचिन्हित पूर्णांक mii_nway_result (अचिन्हित पूर्णांक negotiated)
अणु
	अचिन्हित पूर्णांक ret;

	अगर (negotiated & LPA_100FULL)
		ret = LPA_100FULL;
	अन्यथा अगर (negotiated & LPA_100BASE4)
		ret = LPA_100BASE4;
	अन्यथा अगर (negotiated & LPA_100HALF)
		ret = LPA_100HALF;
	अन्यथा अगर (negotiated & LPA_10FULL)
		ret = LPA_10FULL;
	अन्यथा
		ret = LPA_10HALF;

	वापस ret;
पूर्ण

/**
 * mii_duplex
 * @duplex_lock: Non-zero अगर duplex is locked at full
 * @negotiated: value of MII ANAR and'd with ANLPAR
 *
 * A small helper function क्रम a common हाल.  Returns one
 * अगर the media is operating or locked at full duplex, and
 * वापसs zero otherwise.
 */
अटल अंतरभूत अचिन्हित पूर्णांक mii_duplex (अचिन्हित पूर्णांक duplex_lock,
				       अचिन्हित पूर्णांक negotiated)
अणु
	अगर (duplex_lock)
		वापस 1;
	अगर (mii_nway_result(negotiated) & LPA_DUPLEX)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ethtool_adv_to_mii_adv_t
 * @ethadv: the ethtool advertisement settings
 *
 * A small helper function that translates ethtool advertisement
 * settings to phy स्वतःnegotiation advertisements क्रम the
 * MII_ADVERTISE रेजिस्टर.
 */
अटल अंतरभूत u32 ethtool_adv_to_mii_adv_t(u32 ethadv)
अणु
	u32 result = 0;

	अगर (ethadv & ADVERTISED_10baseT_Half)
		result |= ADVERTISE_10HALF;
	अगर (ethadv & ADVERTISED_10baseT_Full)
		result |= ADVERTISE_10FULL;
	अगर (ethadv & ADVERTISED_100baseT_Half)
		result |= ADVERTISE_100HALF;
	अगर (ethadv & ADVERTISED_100baseT_Full)
		result |= ADVERTISE_100FULL;
	अगर (ethadv & ADVERTISED_Pause)
		result |= ADVERTISE_PAUSE_CAP;
	अगर (ethadv & ADVERTISED_Asym_Pause)
		result |= ADVERTISE_PAUSE_ASYM;

	वापस result;
पूर्ण

/**
 * linkmode_adv_to_mii_adv_t
 * @advertising: the linkmode advertisement settings
 *
 * A small helper function that translates linkmode advertisement
 * settings to phy स्वतःnegotiation advertisements क्रम the
 * MII_ADVERTISE रेजिस्टर.
 */
अटल अंतरभूत u32 linkmode_adv_to_mii_adv_t(अचिन्हित दीर्घ *advertising)
अणु
	u32 result = 0;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT, advertising))
		result |= ADVERTISE_10HALF;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT, advertising))
		result |= ADVERTISE_10FULL;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT, advertising))
		result |= ADVERTISE_100HALF;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT, advertising))
		result |= ADVERTISE_100FULL;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT, advertising))
		result |= ADVERTISE_PAUSE_CAP;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, advertising))
		result |= ADVERTISE_PAUSE_ASYM;

	वापस result;
पूर्ण

/**
 * mii_adv_to_ethtool_adv_t
 * @adv: value of the MII_ADVERTISE रेजिस्टर
 *
 * A small helper function that translates MII_ADVERTISE bits
 * to ethtool advertisement settings.
 */
अटल अंतरभूत u32 mii_adv_to_ethtool_adv_t(u32 adv)
अणु
	u32 result = 0;

	अगर (adv & ADVERTISE_10HALF)
		result |= ADVERTISED_10baseT_Half;
	अगर (adv & ADVERTISE_10FULL)
		result |= ADVERTISED_10baseT_Full;
	अगर (adv & ADVERTISE_100HALF)
		result |= ADVERTISED_100baseT_Half;
	अगर (adv & ADVERTISE_100FULL)
		result |= ADVERTISED_100baseT_Full;
	अगर (adv & ADVERTISE_PAUSE_CAP)
		result |= ADVERTISED_Pause;
	अगर (adv & ADVERTISE_PAUSE_ASYM)
		result |= ADVERTISED_Asym_Pause;

	वापस result;
पूर्ण

/**
 * ethtool_adv_to_mii_ctrl1000_t
 * @ethadv: the ethtool advertisement settings
 *
 * A small helper function that translates ethtool advertisement
 * settings to phy स्वतःnegotiation advertisements क्रम the
 * MII_CTRL1000 रेजिस्टर when in 1000T mode.
 */
अटल अंतरभूत u32 ethtool_adv_to_mii_ctrl1000_t(u32 ethadv)
अणु
	u32 result = 0;

	अगर (ethadv & ADVERTISED_1000baseT_Half)
		result |= ADVERTISE_1000HALF;
	अगर (ethadv & ADVERTISED_1000baseT_Full)
		result |= ADVERTISE_1000FULL;

	वापस result;
पूर्ण

/**
 * linkmode_adv_to_mii_ctrl1000_t
 * @advertising: the linkmode advertisement settings
 *
 * A small helper function that translates linkmode advertisement
 * settings to phy स्वतःnegotiation advertisements क्रम the
 * MII_CTRL1000 रेजिस्टर when in 1000T mode.
 */
अटल अंतरभूत u32 linkmode_adv_to_mii_ctrl1000_t(अचिन्हित दीर्घ *advertising)
अणु
	u32 result = 0;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
			      advertising))
		result |= ADVERTISE_1000HALF;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
			      advertising))
		result |= ADVERTISE_1000FULL;

	वापस result;
पूर्ण

/**
 * mii_ctrl1000_to_ethtool_adv_t
 * @adv: value of the MII_CTRL1000 रेजिस्टर
 *
 * A small helper function that translates MII_CTRL1000
 * bits, when in 1000Base-T mode, to ethtool
 * advertisement settings.
 */
अटल अंतरभूत u32 mii_ctrl1000_to_ethtool_adv_t(u32 adv)
अणु
	u32 result = 0;

	अगर (adv & ADVERTISE_1000HALF)
		result |= ADVERTISED_1000baseT_Half;
	अगर (adv & ADVERTISE_1000FULL)
		result |= ADVERTISED_1000baseT_Full;

	वापस result;
पूर्ण

/**
 * mii_lpa_to_ethtool_lpa_t
 * @adv: value of the MII_LPA रेजिस्टर
 *
 * A small helper function that translates MII_LPA
 * bits, when in 1000Base-T mode, to ethtool
 * LP advertisement settings.
 */
अटल अंतरभूत u32 mii_lpa_to_ethtool_lpa_t(u32 lpa)
अणु
	u32 result = 0;

	अगर (lpa & LPA_LPACK)
		result |= ADVERTISED_Autoneg;

	वापस result | mii_adv_to_ethtool_adv_t(lpa);
पूर्ण

/**
 * mii_stat1000_to_ethtool_lpa_t
 * @adv: value of the MII_STAT1000 रेजिस्टर
 *
 * A small helper function that translates MII_STAT1000
 * bits, when in 1000Base-T mode, to ethtool
 * advertisement settings.
 */
अटल अंतरभूत u32 mii_stat1000_to_ethtool_lpa_t(u32 lpa)
अणु
	u32 result = 0;

	अगर (lpa & LPA_1000HALF)
		result |= ADVERTISED_1000baseT_Half;
	अगर (lpa & LPA_1000FULL)
		result |= ADVERTISED_1000baseT_Full;

	वापस result;
पूर्ण

/**
 * mii_stat1000_mod_linkmode_lpa_t
 * @advertising: target the linkmode advertisement settings
 * @adv: value of the MII_STAT1000 रेजिस्टर
 *
 * A small helper function that translates MII_STAT1000 bits, when in
 * 1000Base-T mode, to linkmode advertisement settings. Other bits in
 * advertising are not changes.
 */
अटल अंतरभूत व्योम mii_stat1000_mod_linkmode_lpa_t(अचिन्हित दीर्घ *advertising,
						   u32 lpa)
अणु
	linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
			 advertising, lpa & LPA_1000HALF);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
			 advertising, lpa & LPA_1000FULL);
पूर्ण

/**
 * ethtool_adv_to_mii_adv_x
 * @ethadv: the ethtool advertisement settings
 *
 * A small helper function that translates ethtool advertisement
 * settings to phy स्वतःnegotiation advertisements क्रम the
 * MII_CTRL1000 रेजिस्टर when in 1000Base-X mode.
 */
अटल अंतरभूत u32 ethtool_adv_to_mii_adv_x(u32 ethadv)
अणु
	u32 result = 0;

	अगर (ethadv & ADVERTISED_1000baseT_Half)
		result |= ADVERTISE_1000XHALF;
	अगर (ethadv & ADVERTISED_1000baseT_Full)
		result |= ADVERTISE_1000XFULL;
	अगर (ethadv & ADVERTISED_Pause)
		result |= ADVERTISE_1000XPAUSE;
	अगर (ethadv & ADVERTISED_Asym_Pause)
		result |= ADVERTISE_1000XPSE_ASYM;

	वापस result;
पूर्ण

/**
 * mii_adv_to_ethtool_adv_x
 * @adv: value of the MII_CTRL1000 रेजिस्टर
 *
 * A small helper function that translates MII_CTRL1000
 * bits, when in 1000Base-X mode, to ethtool
 * advertisement settings.
 */
अटल अंतरभूत u32 mii_adv_to_ethtool_adv_x(u32 adv)
अणु
	u32 result = 0;

	अगर (adv & ADVERTISE_1000XHALF)
		result |= ADVERTISED_1000baseT_Half;
	अगर (adv & ADVERTISE_1000XFULL)
		result |= ADVERTISED_1000baseT_Full;
	अगर (adv & ADVERTISE_1000XPAUSE)
		result |= ADVERTISED_Pause;
	अगर (adv & ADVERTISE_1000XPSE_ASYM)
		result |= ADVERTISED_Asym_Pause;

	वापस result;
पूर्ण

/**
 * mii_lpa_mod_linkmode_adv_sgmii
 * @lp_advertising: poपूर्णांकer to destination link mode.
 * @lpa: value of the MII_LPA रेजिस्टर
 *
 * A small helper function that translates MII_LPA bits to
 * linkmode advertisement settings क्रम SGMII.
 * Leaves other bits unchanged.
 */
अटल अंतरभूत व्योम
mii_lpa_mod_linkmode_lpa_sgmii(अचिन्हित दीर्घ *lp_advertising, u32 lpa)
अणु
	u32 speed_duplex = lpa & LPA_SGMII_DPX_SPD_MASK;

	linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT, lp_advertising,
			 speed_duplex == LPA_SGMII_1000HALF);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT, lp_advertising,
			 speed_duplex == LPA_SGMII_1000FULL);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT, lp_advertising,
			 speed_duplex == LPA_SGMII_100HALF);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT, lp_advertising,
			 speed_duplex == LPA_SGMII_100FULL);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT, lp_advertising,
			 speed_duplex == LPA_SGMII_10HALF);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT, lp_advertising,
			 speed_duplex == LPA_SGMII_10FULL);
पूर्ण

/**
 * mii_lpa_to_linkmode_adv_sgmii
 * @advertising: poपूर्णांकer to destination link mode.
 * @lpa: value of the MII_LPA रेजिस्टर
 *
 * A small helper function that translates MII_ADVERTISE bits
 * to linkmode advertisement settings when in SGMII mode.
 * Clears the old value of advertising.
 */
अटल अंतरभूत व्योम mii_lpa_to_linkmode_lpa_sgmii(अचिन्हित दीर्घ *lp_advertising,
						 u32 lpa)
अणु
	linkmode_zero(lp_advertising);

	mii_lpa_mod_linkmode_lpa_sgmii(lp_advertising, lpa);
पूर्ण

/**
 * mii_adv_mod_linkmode_adv_t
 * @advertising:poपूर्णांकer to destination link mode.
 * @adv: value of the MII_ADVERTISE रेजिस्टर
 *
 * A small helper function that translates MII_ADVERTISE bits to
 * linkmode advertisement settings. Leaves other bits unchanged.
 */
अटल अंतरभूत व्योम mii_adv_mod_linkmode_adv_t(अचिन्हित दीर्घ *advertising,
					      u32 adv)
अणु
	linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
			 advertising, adv & ADVERTISE_10HALF);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
			 advertising, adv & ADVERTISE_10FULL);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
			 advertising, adv & ADVERTISE_100HALF);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
			 advertising, adv & ADVERTISE_100FULL);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_Pause_BIT, advertising,
			 adv & ADVERTISE_PAUSE_CAP);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			 advertising, adv & ADVERTISE_PAUSE_ASYM);
पूर्ण

/**
 * mii_adv_to_linkmode_adv_t
 * @advertising:poपूर्णांकer to destination link mode.
 * @adv: value of the MII_ADVERTISE रेजिस्टर
 *
 * A small helper function that translates MII_ADVERTISE bits
 * to linkmode advertisement settings. Clears the old value
 * of advertising.
 */
अटल अंतरभूत व्योम mii_adv_to_linkmode_adv_t(अचिन्हित दीर्घ *advertising,
					     u32 adv)
अणु
	linkmode_zero(advertising);

	mii_adv_mod_linkmode_adv_t(advertising, adv);
पूर्ण

/**
 * mii_lpa_to_linkmode_lpa_t
 * @adv: value of the MII_LPA रेजिस्टर
 *
 * A small helper function that translates MII_LPA bits, when in
 * 1000Base-T mode, to linkmode LP advertisement settings. Clears the
 * old value of advertising
 */
अटल अंतरभूत व्योम mii_lpa_to_linkmode_lpa_t(अचिन्हित दीर्घ *lp_advertising,
					     u32 lpa)
अणु
	mii_adv_to_linkmode_adv_t(lp_advertising, lpa);

	अगर (lpa & LPA_LPACK)
		linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				 lp_advertising);

पूर्ण

/**
 * mii_lpa_mod_linkmode_lpa_t
 * @adv: value of the MII_LPA रेजिस्टर
 *
 * A small helper function that translates MII_LPA bits, when in
 * 1000Base-T mode, to linkmode LP advertisement settings. Leaves
 * other bits unchanged.
 */
अटल अंतरभूत व्योम mii_lpa_mod_linkmode_lpa_t(अचिन्हित दीर्घ *lp_advertising,
					      u32 lpa)
अणु
	mii_adv_mod_linkmode_adv_t(lp_advertising, lpa);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
			 lp_advertising, lpa & LPA_LPACK);
पूर्ण

अटल अंतरभूत व्योम mii_ctrl1000_mod_linkmode_adv_t(अचिन्हित दीर्घ *advertising,
						   u32 ctrl1000)
अणु
	linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT, advertising,
			 ctrl1000 & ADVERTISE_1000HALF);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT, advertising,
			 ctrl1000 & ADVERTISE_1000FULL);
पूर्ण

/**
 * linkmode_adv_to_lcl_adv_t
 * @advertising:poपूर्णांकer to linkmode advertising
 *
 * A small helper function that translates linkmode advertising to LVL
 * छोड़ो capabilities.
 */
अटल अंतरभूत u32 linkmode_adv_to_lcl_adv_t(अचिन्हित दीर्घ *advertising)
अणु
	u32 lcl_adv = 0;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
			      advertising))
		lcl_adv |= ADVERTISE_PAUSE_CAP;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			      advertising))
		lcl_adv |= ADVERTISE_PAUSE_ASYM;

	वापस lcl_adv;
पूर्ण

/**
 * mii_lpa_mod_linkmode_x - decode the link partner's config_reg to linkmodes
 * @linkmodes: link modes array
 * @lpa: config_reg word from link partner
 * @fd_bit: link mode क्रम 1000XFULL bit
 */
अटल अंतरभूत व्योम mii_lpa_mod_linkmode_x(अचिन्हित दीर्घ *linkmodes, u16 lpa,
					 पूर्णांक fd_bit)
अणु
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, linkmodes,
			 lpa & LPA_LPACK);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Pause_BIT, linkmodes,
			 lpa & LPA_1000XPAUSE);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, linkmodes,
			 lpa & LPA_1000XPAUSE_ASYM);
	linkmode_mod_bit(fd_bit, linkmodes,
			 lpa & LPA_1000XFULL);
पूर्ण

/**
 * linkmode_adv_to_mii_adv_x - encode a linkmode to config_reg
 * @linkmodes: linkmodes
 * @fd_bit: full duplex bit
 */
अटल अंतरभूत u16 linkmode_adv_to_mii_adv_x(स्थिर अचिन्हित दीर्घ *linkmodes,
					    पूर्णांक fd_bit)
अणु
	u16 adv = 0;

	अगर (linkmode_test_bit(fd_bit, linkmodes))
		adv |= ADVERTISE_1000XFULL;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT, linkmodes))
		adv |= ADVERTISE_1000XPAUSE;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, linkmodes))
		adv |= ADVERTISE_1000XPSE_ASYM;

	वापस adv;
पूर्ण

/**
 * mii_advertise_flowctrl - get flow control advertisement flags
 * @cap: Flow control capabilities (FLOW_CTRL_RX, FLOW_CTRL_TX or both)
 */
अटल अंतरभूत u16 mii_advertise_flowctrl(पूर्णांक cap)
अणु
	u16 adv = 0;

	अगर (cap & FLOW_CTRL_RX)
		adv = ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
	अगर (cap & FLOW_CTRL_TX)
		adv ^= ADVERTISE_PAUSE_ASYM;

	वापस adv;
पूर्ण

/**
 * mii_resolve_flowctrl_fdx
 * @lcladv: value of MII ADVERTISE रेजिस्टर
 * @rmtadv: value of MII LPA रेजिस्टर
 *
 * Resolve full duplex flow control as per IEEE 802.3-2005 table 28B-3
 */
अटल अंतरभूत u8 mii_resolve_flowctrl_fdx(u16 lcladv, u16 rmtadv)
अणु
	u8 cap = 0;

	अगर (lcladv & rmtadv & ADVERTISE_PAUSE_CAP) अणु
		cap = FLOW_CTRL_TX | FLOW_CTRL_RX;
	पूर्ण अन्यथा अगर (lcladv & rmtadv & ADVERTISE_PAUSE_ASYM) अणु
		अगर (lcladv & ADVERTISE_PAUSE_CAP)
			cap = FLOW_CTRL_RX;
		अन्यथा अगर (rmtadv & ADVERTISE_PAUSE_CAP)
			cap = FLOW_CTRL_TX;
	पूर्ण

	वापस cap;
पूर्ण

#पूर्ण_अगर /* __LINUX_MII_H__ */
