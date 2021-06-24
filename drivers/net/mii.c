<शैली गुरु>
/*

	mii.c: MII पूर्णांकerface library

	Maपूर्णांकained by Jeff Garzik <jgarzik@pobox.com>
	Copyright 2001,2002 Jeff Garzik

	Various code came from myson803.c and other files by
	Donald Becker.  Copyright:

		Written 1998-2002 by Donald Becker.

		This software may be used and distributed according
		to the terms of the GNU General Public License (GPL),
		incorporated herein by reference.  Drivers based on
		or derived from this code fall under the GPL and must
		retain the authorship, copyright and license notice.
		This file is not a complete program and may only be
		used when the entire operating प्रणाली is licensed
		under the GPL.

		The author may be reached as becker@scyld.com, or C/O
		Scyld Computing Corporation
		410 Severn Ave., Suite 210
		Annapolis MD 21403


 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>

अटल u32 mii_get_an(काष्ठा mii_अगर_info *mii, u16 addr)
अणु
	पूर्णांक advert;

	advert = mii->mdio_पढ़ो(mii->dev, mii->phy_id, addr);

	वापस mii_lpa_to_ethtool_lpa_t(advert);
पूर्ण

/**
 * mii_ethtool_gset - get settings that are specअगरied in @ecmd
 * @mii: MII पूर्णांकerface
 * @ecmd: requested ethtool_cmd
 *
 * The @ecmd parameter is expected to have been cleared beक्रमe calling
 * mii_ethtool_gset().
 *
 * Returns 0 क्रम success, negative on error.
 */
पूर्णांक mii_ethtool_gset(काष्ठा mii_अगर_info *mii, काष्ठा ethtool_cmd *ecmd)
अणु
	काष्ठा net_device *dev = mii->dev;
	u16 bmcr, bmsr, ctrl1000 = 0, stat1000 = 0;
	u32 nego;

	ecmd->supported =
	    (SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
	     SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
	     SUPPORTED_Autoneg | SUPPORTED_TP | SUPPORTED_MII);
	अगर (mii->supports_gmii)
		ecmd->supported |= SUPPORTED_1000baseT_Half |
			SUPPORTED_1000baseT_Full;

	/* only supports twisted-pair */
	ecmd->port = PORT_MII;

	/* only supports पूर्णांकernal transceiver */
	ecmd->transceiver = XCVR_INTERNAL;

	/* this isn't fully supported at higher layers */
	ecmd->phy_address = mii->phy_id;
	ecmd->mdio_support = ETH_MDIO_SUPPORTS_C22;

	ecmd->advertising = ADVERTISED_TP | ADVERTISED_MII;

	bmcr = mii->mdio_पढ़ो(dev, mii->phy_id, MII_BMCR);
	bmsr = mii->mdio_पढ़ो(dev, mii->phy_id, MII_BMSR);
	अगर (mii->supports_gmii) अणु
 		ctrl1000 = mii->mdio_पढ़ो(dev, mii->phy_id, MII_CTRL1000);
		stat1000 = mii->mdio_पढ़ो(dev, mii->phy_id, MII_STAT1000);
	पूर्ण

	ecmd->advertising |= mii_get_an(mii, MII_ADVERTISE);
	अगर (mii->supports_gmii)
		ecmd->advertising |=
			mii_ctrl1000_to_ethtool_adv_t(ctrl1000);

	अगर (bmcr & BMCR_ANENABLE) अणु
		ecmd->advertising |= ADVERTISED_Autoneg;
		ecmd->स्वतःneg = AUTONEG_ENABLE;

		अगर (bmsr & BMSR_ANEGCOMPLETE) अणु
			ecmd->lp_advertising = mii_get_an(mii, MII_LPA);
			ecmd->lp_advertising |=
					mii_stat1000_to_ethtool_lpa_t(stat1000);
		पूर्ण अन्यथा अणु
			ecmd->lp_advertising = 0;
		पूर्ण

		nego = ecmd->advertising & ecmd->lp_advertising;

		अगर (nego & (ADVERTISED_1000baseT_Full |
			    ADVERTISED_1000baseT_Half)) अणु
			ethtool_cmd_speed_set(ecmd, SPEED_1000);
			ecmd->duplex = !!(nego & ADVERTISED_1000baseT_Full);
		पूर्ण अन्यथा अगर (nego & (ADVERTISED_100baseT_Full |
				   ADVERTISED_100baseT_Half)) अणु
			ethtool_cmd_speed_set(ecmd, SPEED_100);
			ecmd->duplex = !!(nego & ADVERTISED_100baseT_Full);
		पूर्ण अन्यथा अणु
			ethtool_cmd_speed_set(ecmd, SPEED_10);
			ecmd->duplex = !!(nego & ADVERTISED_10baseT_Full);
		पूर्ण
	पूर्ण अन्यथा अणु
		ecmd->स्वतःneg = AUTONEG_DISABLE;

		ethtool_cmd_speed_set(ecmd,
				      ((bmcr & BMCR_SPEED1000 &&
					(bmcr & BMCR_SPEED100) == 0) ?
				       SPEED_1000 :
				       ((bmcr & BMCR_SPEED100) ?
					SPEED_100 : SPEED_10)));
		ecmd->duplex = (bmcr & BMCR_FULLDPLX) ? DUPLEX_FULL : DUPLEX_HALF;
	पूर्ण

	mii->full_duplex = ecmd->duplex;

	/* ignore maxtxpkt, maxrxpkt क्रम now */

	वापस 0;
पूर्ण

/**
 * mii_ethtool_get_link_ksettings - get settings that are specअगरied in @cmd
 * @mii: MII पूर्णांकerface
 * @cmd: requested ethtool_link_ksettings
 *
 * The @cmd parameter is expected to have been cleared beक्रमe calling
 * mii_ethtool_get_link_ksettings().
 */
व्योम mii_ethtool_get_link_ksettings(काष्ठा mii_अगर_info *mii,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा net_device *dev = mii->dev;
	u16 bmcr, bmsr, ctrl1000 = 0, stat1000 = 0;
	u32 nego, supported, advertising, lp_advertising;

	supported = (SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
		     SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
		     SUPPORTED_Autoneg | SUPPORTED_TP | SUPPORTED_MII);
	अगर (mii->supports_gmii)
		supported |= SUPPORTED_1000baseT_Half |
			SUPPORTED_1000baseT_Full;

	/* only supports twisted-pair */
	cmd->base.port = PORT_MII;

	/* this isn't fully supported at higher layers */
	cmd->base.phy_address = mii->phy_id;
	cmd->base.mdio_support = ETH_MDIO_SUPPORTS_C22;

	advertising = ADVERTISED_TP | ADVERTISED_MII;

	bmcr = mii->mdio_पढ़ो(dev, mii->phy_id, MII_BMCR);
	bmsr = mii->mdio_पढ़ो(dev, mii->phy_id, MII_BMSR);
	अगर (mii->supports_gmii) अणु
		ctrl1000 = mii->mdio_पढ़ो(dev, mii->phy_id, MII_CTRL1000);
		stat1000 = mii->mdio_पढ़ो(dev, mii->phy_id, MII_STAT1000);
	पूर्ण

	advertising |= mii_get_an(mii, MII_ADVERTISE);
	अगर (mii->supports_gmii)
		advertising |= mii_ctrl1000_to_ethtool_adv_t(ctrl1000);

	अगर (bmcr & BMCR_ANENABLE) अणु
		advertising |= ADVERTISED_Autoneg;
		cmd->base.स्वतःneg = AUTONEG_ENABLE;

		अगर (bmsr & BMSR_ANEGCOMPLETE) अणु
			lp_advertising = mii_get_an(mii, MII_LPA);
			lp_advertising |=
					mii_stat1000_to_ethtool_lpa_t(stat1000);
		पूर्ण अन्यथा अणु
			lp_advertising = 0;
		पूर्ण

		nego = advertising & lp_advertising;

		अगर (nego & (ADVERTISED_1000baseT_Full |
			    ADVERTISED_1000baseT_Half)) अणु
			cmd->base.speed = SPEED_1000;
			cmd->base.duplex = !!(nego & ADVERTISED_1000baseT_Full);
		पूर्ण अन्यथा अगर (nego & (ADVERTISED_100baseT_Full |
				   ADVERTISED_100baseT_Half)) अणु
			cmd->base.speed = SPEED_100;
			cmd->base.duplex = !!(nego & ADVERTISED_100baseT_Full);
		पूर्ण अन्यथा अणु
			cmd->base.speed = SPEED_10;
			cmd->base.duplex = !!(nego & ADVERTISED_10baseT_Full);
		पूर्ण
	पूर्ण अन्यथा अणु
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

		cmd->base.speed = ((bmcr & BMCR_SPEED1000 &&
				    (bmcr & BMCR_SPEED100) == 0) ?
				   SPEED_1000 :
				   ((bmcr & BMCR_SPEED100) ?
				    SPEED_100 : SPEED_10));
		cmd->base.duplex = (bmcr & BMCR_FULLDPLX) ?
			DUPLEX_FULL : DUPLEX_HALF;

		lp_advertising = 0;
	पूर्ण

	mii->full_duplex = cmd->base.duplex;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.lp_advertising,
						lp_advertising);

	/* ignore maxtxpkt, maxrxpkt क्रम now */
पूर्ण

/**
 * mii_ethtool_sset - set settings that are specअगरied in @ecmd
 * @mii: MII पूर्णांकerface
 * @ecmd: requested ethtool_cmd
 *
 * Returns 0 क्रम success, negative on error.
 */
पूर्णांक mii_ethtool_sset(काष्ठा mii_अगर_info *mii, काष्ठा ethtool_cmd *ecmd)
अणु
	काष्ठा net_device *dev = mii->dev;
	u32 speed = ethtool_cmd_speed(ecmd);

	अगर (speed != SPEED_10 &&
	    speed != SPEED_100 &&
	    speed != SPEED_1000)
		वापस -EINVAL;
	अगर (ecmd->duplex != DUPLEX_HALF && ecmd->duplex != DUPLEX_FULL)
		वापस -EINVAL;
	अगर (ecmd->port != PORT_MII)
		वापस -EINVAL;
	अगर (ecmd->transceiver != XCVR_INTERNAL)
		वापस -EINVAL;
	अगर (ecmd->phy_address != mii->phy_id)
		वापस -EINVAL;
	अगर (ecmd->स्वतःneg != AUTONEG_DISABLE && ecmd->स्वतःneg != AUTONEG_ENABLE)
		वापस -EINVAL;
	अगर ((speed == SPEED_1000) && (!mii->supports_gmii))
		वापस -EINVAL;

	/* ignore supported, maxtxpkt, maxrxpkt */

	अगर (ecmd->स्वतःneg == AUTONEG_ENABLE) अणु
		u32 bmcr, advert, पंचांगp;
		u32 advert2 = 0, पंचांगp2 = 0;

		अगर ((ecmd->advertising & (ADVERTISED_10baseT_Half |
					  ADVERTISED_10baseT_Full |
					  ADVERTISED_100baseT_Half |
					  ADVERTISED_100baseT_Full |
					  ADVERTISED_1000baseT_Half |
					  ADVERTISED_1000baseT_Full)) == 0)
			वापस -EINVAL;

		/* advertise only what has been requested */
		advert = mii->mdio_पढ़ो(dev, mii->phy_id, MII_ADVERTISE);
		पंचांगp = advert & ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
		अगर (mii->supports_gmii) अणु
			advert2 = mii->mdio_पढ़ो(dev, mii->phy_id, MII_CTRL1000);
			पंचांगp2 = advert2 & ~(ADVERTISE_1000HALF | ADVERTISE_1000FULL);
		पूर्ण
		पंचांगp |= ethtool_adv_to_mii_adv_t(ecmd->advertising);

		अगर (mii->supports_gmii)
			पंचांगp2 |=
			      ethtool_adv_to_mii_ctrl1000_t(ecmd->advertising);
		अगर (advert != पंचांगp) अणु
			mii->mdio_ग_लिखो(dev, mii->phy_id, MII_ADVERTISE, पंचांगp);
			mii->advertising = पंचांगp;
		पूर्ण
		अगर ((mii->supports_gmii) && (advert2 != पंचांगp2))
			mii->mdio_ग_लिखो(dev, mii->phy_id, MII_CTRL1000, पंचांगp2);

		/* turn on स्वतःnegotiation, and क्रमce a renegotiate */
		bmcr = mii->mdio_पढ़ो(dev, mii->phy_id, MII_BMCR);
		bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
		mii->mdio_ग_लिखो(dev, mii->phy_id, MII_BMCR, bmcr);

		mii->क्रमce_media = 0;
	पूर्ण अन्यथा अणु
		u32 bmcr, पंचांगp;

		/* turn off स्वतः negotiation, set speed and duplनिकासy */
		bmcr = mii->mdio_पढ़ो(dev, mii->phy_id, MII_BMCR);
		पंचांगp = bmcr & ~(BMCR_ANENABLE | BMCR_SPEED100 |
			       BMCR_SPEED1000 | BMCR_FULLDPLX);
		अगर (speed == SPEED_1000)
			पंचांगp |= BMCR_SPEED1000;
		अन्यथा अगर (speed == SPEED_100)
			पंचांगp |= BMCR_SPEED100;
		अगर (ecmd->duplex == DUPLEX_FULL) अणु
			पंचांगp |= BMCR_FULLDPLX;
			mii->full_duplex = 1;
		पूर्ण अन्यथा
			mii->full_duplex = 0;
		अगर (bmcr != पंचांगp)
			mii->mdio_ग_लिखो(dev, mii->phy_id, MII_BMCR, पंचांगp);

		mii->क्रमce_media = 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mii_ethtool_set_link_ksettings - set settings that are specअगरied in @cmd
 * @mii: MII पूर्णांकerfaces
 * @cmd: requested ethtool_link_ksettings
 *
 * Returns 0 क्रम success, negative on error.
 */
पूर्णांक mii_ethtool_set_link_ksettings(काष्ठा mii_अगर_info *mii,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा net_device *dev = mii->dev;
	u32 speed = cmd->base.speed;

	अगर (speed != SPEED_10 &&
	    speed != SPEED_100 &&
	    speed != SPEED_1000)
		वापस -EINVAL;
	अगर (cmd->base.duplex != DUPLEX_HALF && cmd->base.duplex != DUPLEX_FULL)
		वापस -EINVAL;
	अगर (cmd->base.port != PORT_MII)
		वापस -EINVAL;
	अगर (cmd->base.phy_address != mii->phy_id)
		वापस -EINVAL;
	अगर (cmd->base.स्वतःneg != AUTONEG_DISABLE &&
	    cmd->base.स्वतःneg != AUTONEG_ENABLE)
		वापस -EINVAL;
	अगर ((speed == SPEED_1000) && (!mii->supports_gmii))
		वापस -EINVAL;

	/* ignore supported, maxtxpkt, maxrxpkt */

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		u32 bmcr, advert, पंचांगp;
		u32 advert2 = 0, पंचांगp2 = 0;
		u32 advertising;

		ethtool_convert_link_mode_to_legacy_u32(
			&advertising, cmd->link_modes.advertising);

		अगर ((advertising & (ADVERTISED_10baseT_Half |
				    ADVERTISED_10baseT_Full |
				    ADVERTISED_100baseT_Half |
				    ADVERTISED_100baseT_Full |
				    ADVERTISED_1000baseT_Half |
				    ADVERTISED_1000baseT_Full)) == 0)
			वापस -EINVAL;

		/* advertise only what has been requested */
		advert = mii->mdio_पढ़ो(dev, mii->phy_id, MII_ADVERTISE);
		पंचांगp = advert & ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
		अगर (mii->supports_gmii) अणु
			advert2 = mii->mdio_पढ़ो(dev, mii->phy_id,
						 MII_CTRL1000);
			पंचांगp2 = advert2 &
				~(ADVERTISE_1000HALF | ADVERTISE_1000FULL);
		पूर्ण
		पंचांगp |= ethtool_adv_to_mii_adv_t(advertising);

		अगर (mii->supports_gmii)
			पंचांगp2 |= ethtool_adv_to_mii_ctrl1000_t(advertising);
		अगर (advert != पंचांगp) अणु
			mii->mdio_ग_लिखो(dev, mii->phy_id, MII_ADVERTISE, पंचांगp);
			mii->advertising = पंचांगp;
		पूर्ण
		अगर ((mii->supports_gmii) && (advert2 != पंचांगp2))
			mii->mdio_ग_लिखो(dev, mii->phy_id, MII_CTRL1000, पंचांगp2);

		/* turn on स्वतःnegotiation, and क्रमce a renegotiate */
		bmcr = mii->mdio_पढ़ो(dev, mii->phy_id, MII_BMCR);
		bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
		mii->mdio_ग_लिखो(dev, mii->phy_id, MII_BMCR, bmcr);

		mii->क्रमce_media = 0;
	पूर्ण अन्यथा अणु
		u32 bmcr, पंचांगp;

		/* turn off स्वतः negotiation, set speed and duplनिकासy */
		bmcr = mii->mdio_पढ़ो(dev, mii->phy_id, MII_BMCR);
		पंचांगp = bmcr & ~(BMCR_ANENABLE | BMCR_SPEED100 |
			       BMCR_SPEED1000 | BMCR_FULLDPLX);
		अगर (speed == SPEED_1000)
			पंचांगp |= BMCR_SPEED1000;
		अन्यथा अगर (speed == SPEED_100)
			पंचांगp |= BMCR_SPEED100;
		अगर (cmd->base.duplex == DUPLEX_FULL) अणु
			पंचांगp |= BMCR_FULLDPLX;
			mii->full_duplex = 1;
		पूर्ण अन्यथा अणु
			mii->full_duplex = 0;
		पूर्ण
		अगर (bmcr != पंचांगp)
			mii->mdio_ग_लिखो(dev, mii->phy_id, MII_BMCR, पंचांगp);

		mii->क्रमce_media = 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mii_check_gmii_support - check अगर the MII supports Gb पूर्णांकerfaces
 * @mii: the MII पूर्णांकerface
 */
पूर्णांक mii_check_gmii_support(काष्ठा mii_अगर_info *mii)
अणु
	पूर्णांक reg;

	reg = mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_BMSR);
	अगर (reg & BMSR_ESTATEN) अणु
		reg = mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_ESTATUS);
		अगर (reg & (ESTATUS_1000_TFULL | ESTATUS_1000_THALF))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mii_link_ok - is link status up/ok
 * @mii: the MII पूर्णांकerface
 *
 * Returns 1 अगर the MII reports link status up/ok, 0 otherwise.
 */
पूर्णांक mii_link_ok (काष्ठा mii_अगर_info *mii)
अणु
	/* first, a dummy पढ़ो, needed to latch some MII phys */
	mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_BMSR);
	अगर (mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_BMSR) & BMSR_LSTATUS)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * mii_nway_restart - restart NWay (स्वतःnegotiation) क्रम this पूर्णांकerface
 * @mii: the MII पूर्णांकerface
 *
 * Returns 0 on success, negative on error.
 */
पूर्णांक mii_nway_restart (काष्ठा mii_अगर_info *mii)
अणु
	पूर्णांक bmcr;
	पूर्णांक r = -EINVAL;

	/* अगर स्वतःneg is off, it's an error */
	bmcr = mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_BMCR);

	अगर (bmcr & BMCR_ANENABLE) अणु
		bmcr |= BMCR_ANRESTART;
		mii->mdio_ग_लिखो(mii->dev, mii->phy_id, MII_BMCR, bmcr);
		r = 0;
	पूर्ण

	वापस r;
पूर्ण

/**
 * mii_check_link - check MII link status
 * @mii: MII पूर्णांकerface
 *
 * If the link status changed (previous != current), call
 * netअगर_carrier_on() अगर current link status is Up or call
 * netअगर_carrier_off() अगर current link status is Down.
 */
व्योम mii_check_link (काष्ठा mii_अगर_info *mii)
अणु
	पूर्णांक cur_link = mii_link_ok(mii);
	पूर्णांक prev_link = netअगर_carrier_ok(mii->dev);

	अगर (cur_link && !prev_link)
		netअगर_carrier_on(mii->dev);
	अन्यथा अगर (prev_link && !cur_link)
		netअगर_carrier_off(mii->dev);
पूर्ण

/**
 * mii_check_media - check the MII पूर्णांकerface क्रम a carrier/speed/duplex change
 * @mii: the MII पूर्णांकerface
 * @ok_to_prपूर्णांक: OK to prपूर्णांक link up/करोwn messages
 * @init_media: OK to save duplex mode in @mii
 *
 * Returns 1 अगर the duplex mode changed, 0 अगर not.
 * If the media type is क्रमced, always वापसs 0.
 */
अचिन्हित पूर्णांक mii_check_media (काष्ठा mii_अगर_info *mii,
			      अचिन्हित पूर्णांक ok_to_prपूर्णांक,
			      अचिन्हित पूर्णांक init_media)
अणु
	अचिन्हित पूर्णांक old_carrier, new_carrier;
	पूर्णांक advertise, lpa, media, duplex;
	पूर्णांक lpa2 = 0;

	/* check current and old link status */
	old_carrier = netअगर_carrier_ok(mii->dev) ? 1 : 0;
	new_carrier = (अचिन्हित पूर्णांक) mii_link_ok(mii);

	/* अगर carrier state did not change, this is a "bounce",
	 * just निकास as everything is alपढ़ोy set correctly
	 */
	अगर ((!init_media) && (old_carrier == new_carrier))
		वापस 0; /* duplex did not change */

	/* no carrier, nothing much to करो */
	अगर (!new_carrier) अणु
		netअगर_carrier_off(mii->dev);
		अगर (ok_to_prपूर्णांक)
			netdev_info(mii->dev, "link down\n");
		वापस 0; /* duplex did not change */
	पूर्ण

	/*
	 * we have carrier, see who's on the other end
	 */
	netअगर_carrier_on(mii->dev);

	अगर (mii->क्रमce_media) अणु
		अगर (ok_to_prपूर्णांक)
			netdev_info(mii->dev, "link up\n");
		वापस 0; /* duplex did not change */
	पूर्ण

	/* get MII advertise and LPA values */
	अगर ((!init_media) && (mii->advertising))
		advertise = mii->advertising;
	अन्यथा अणु
		advertise = mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_ADVERTISE);
		mii->advertising = advertise;
	पूर्ण
	lpa = mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_LPA);
	अगर (mii->supports_gmii)
		lpa2 = mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_STAT1000);

	/* figure out media and duplex from advertise and LPA values */
	media = mii_nway_result(lpa & advertise);
	duplex = (media & ADVERTISE_FULL) ? 1 : 0;
	अगर (lpa2 & LPA_1000FULL)
		duplex = 1;

	अगर (ok_to_prपूर्णांक)
		netdev_info(mii->dev, "link up, %uMbps, %s-duplex, lpa 0x%04X\n",
			    lpa2 & (LPA_1000FULL | LPA_1000HALF) ? 1000 :
			    media & (ADVERTISE_100FULL | ADVERTISE_100HALF) ?
			    100 : 10,
			    duplex ? "full" : "half",
			    lpa);

	अगर ((init_media) || (mii->full_duplex != duplex)) अणु
		mii->full_duplex = duplex;
		वापस 1; /* duplex changed */
	पूर्ण

	वापस 0; /* duplex did not change */
पूर्ण

/**
 * generic_mii_ioctl - मुख्य MII ioctl पूर्णांकerface
 * @mii_अगर: the MII पूर्णांकerface
 * @mii_data: MII ioctl data काष्ठाure
 * @cmd: MII ioctl command
 * @duplex_chg_out: poपूर्णांकer to @duplex_changed status अगर there was no
 *	ioctl error
 *
 * Returns 0 on success, negative on error.
 */
पूर्णांक generic_mii_ioctl(काष्ठा mii_अगर_info *mii_अगर,
		      काष्ठा mii_ioctl_data *mii_data, पूर्णांक cmd,
		      अचिन्हित पूर्णांक *duplex_chg_out)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक duplex_changed = 0;

	अगर (duplex_chg_out)
		*duplex_chg_out = 0;

	mii_data->phy_id &= mii_अगर->phy_id_mask;
	mii_data->reg_num &= mii_अगर->reg_num_mask;

	चयन(cmd) अणु
	हाल SIOCGMIIPHY:
		mii_data->phy_id = mii_अगर->phy_id;
		fallthrough;

	हाल SIOCGMIIREG:
		mii_data->val_out =
			mii_अगर->mdio_पढ़ो(mii_अगर->dev, mii_data->phy_id,
					  mii_data->reg_num);
		अवरोध;

	हाल SIOCSMIIREG: अणु
		u16 val = mii_data->val_in;

		अगर (mii_data->phy_id == mii_अगर->phy_id) अणु
			चयन(mii_data->reg_num) अणु
			हाल MII_BMCR: अणु
				अचिन्हित पूर्णांक new_duplex = 0;
				अगर (val & (BMCR_RESET|BMCR_ANENABLE))
					mii_अगर->क्रमce_media = 0;
				अन्यथा
					mii_अगर->क्रमce_media = 1;
				अगर (mii_अगर->क्रमce_media &&
				    (val & BMCR_FULLDPLX))
					new_duplex = 1;
				अगर (mii_अगर->full_duplex != new_duplex) अणु
					duplex_changed = 1;
					mii_अगर->full_duplex = new_duplex;
				पूर्ण
				अवरोध;
			पूर्ण
			हाल MII_ADVERTISE:
				mii_अगर->advertising = val;
				अवरोध;
			शेष:
				/* करो nothing */
				अवरोध;
			पूर्ण
		पूर्ण

		mii_अगर->mdio_ग_लिखो(mii_अगर->dev, mii_data->phy_id,
				   mii_data->reg_num, val);
		अवरोध;
	पूर्ण

	शेष:
		rc = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	अगर ((rc == 0) && (duplex_chg_out) && (duplex_changed))
		*duplex_chg_out = 1;

	वापस rc;
पूर्ण

MODULE_AUTHOR ("Jeff Garzik <jgarzik@pobox.com>");
MODULE_DESCRIPTION ("MII hardware support library");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(mii_link_ok);
EXPORT_SYMBOL(mii_nway_restart);
EXPORT_SYMBOL(mii_ethtool_gset);
EXPORT_SYMBOL(mii_ethtool_get_link_ksettings);
EXPORT_SYMBOL(mii_ethtool_sset);
EXPORT_SYMBOL(mii_ethtool_set_link_ksettings);
EXPORT_SYMBOL(mii_check_link);
EXPORT_SYMBOL(mii_check_media);
EXPORT_SYMBOL(mii_check_gmii_support);
EXPORT_SYMBOL(generic_mii_ioctl);

