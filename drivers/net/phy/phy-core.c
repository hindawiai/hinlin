<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Core PHY library, taken from phy.c
 */
#समावेश <linux/export.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>

/**
 * phy_speed_to_str - Return a string representing the PHY link speed
 *
 * @speed: Speed of the link
 */
स्थिर अक्षर *phy_speed_to_str(पूर्णांक speed)
अणु
	BUILD_BUG_ON_MSG(__ETHTOOL_LINK_MODE_MASK_NBITS != 92,
		"Enum ethtool_link_mode_bit_indices and phylib are out of sync. "
		"If a speed or mode has been added please update phy_speed_to_str "
		"and the PHY settings array.\n");

	चयन (speed) अणु
	हाल SPEED_10:
		वापस "10Mbps";
	हाल SPEED_100:
		वापस "100Mbps";
	हाल SPEED_1000:
		वापस "1Gbps";
	हाल SPEED_2500:
		वापस "2.5Gbps";
	हाल SPEED_5000:
		वापस "5Gbps";
	हाल SPEED_10000:
		वापस "10Gbps";
	हाल SPEED_14000:
		वापस "14Gbps";
	हाल SPEED_20000:
		वापस "20Gbps";
	हाल SPEED_25000:
		वापस "25Gbps";
	हाल SPEED_40000:
		वापस "40Gbps";
	हाल SPEED_50000:
		वापस "50Gbps";
	हाल SPEED_56000:
		वापस "56Gbps";
	हाल SPEED_100000:
		वापस "100Gbps";
	हाल SPEED_200000:
		वापस "200Gbps";
	हाल SPEED_400000:
		वापस "400Gbps";
	हाल SPEED_UNKNOWN:
		वापस "Unknown";
	शेष:
		वापस "Unsupported (update phy-core.c)";
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(phy_speed_to_str);

/**
 * phy_duplex_to_str - Return string describing the duplex
 *
 * @duplex: Duplex setting to describe
 */
स्थिर अक्षर *phy_duplex_to_str(अचिन्हित पूर्णांक duplex)
अणु
	अगर (duplex == DUPLEX_HALF)
		वापस "Half";
	अगर (duplex == DUPLEX_FULL)
		वापस "Full";
	अगर (duplex == DUPLEX_UNKNOWN)
		वापस "Unknown";
	वापस "Unsupported (update phy-core.c)";
पूर्ण
EXPORT_SYMBOL_GPL(phy_duplex_to_str);

/* A mapping of all SUPPORTED settings to speed/duplex.  This table
 * must be grouped by speed and sorted in descending match priority
 * - iow, descending speed. */

#घोषणा PHY_SETTING(s, d, b) अणु .speed = SPEED_ ## s, .duplex = DUPLEX_ ## d, \
			       .bit = ETHTOOL_LINK_MODE_ ## b ## _BITपूर्ण

अटल स्थिर काष्ठा phy_setting settings[] = अणु
	/* 400G */
	PHY_SETTING( 400000, FULL, 400000baseCR8_Full		),
	PHY_SETTING( 400000, FULL, 400000baseKR8_Full		),
	PHY_SETTING( 400000, FULL, 400000baseLR8_ER8_FR8_Full	),
	PHY_SETTING( 400000, FULL, 400000baseDR8_Full		),
	PHY_SETTING( 400000, FULL, 400000baseSR8_Full		),
	PHY_SETTING( 400000, FULL, 400000baseCR4_Full		),
	PHY_SETTING( 400000, FULL, 400000baseKR4_Full		),
	PHY_SETTING( 400000, FULL, 400000baseLR4_ER4_FR4_Full	),
	PHY_SETTING( 400000, FULL, 400000baseDR4_Full		),
	PHY_SETTING( 400000, FULL, 400000baseSR4_Full		),
	/* 200G */
	PHY_SETTING( 200000, FULL, 200000baseCR4_Full		),
	PHY_SETTING( 200000, FULL, 200000baseKR4_Full		),
	PHY_SETTING( 200000, FULL, 200000baseLR4_ER4_FR4_Full	),
	PHY_SETTING( 200000, FULL, 200000baseDR4_Full		),
	PHY_SETTING( 200000, FULL, 200000baseSR4_Full		),
	PHY_SETTING( 200000, FULL, 200000baseCR2_Full		),
	PHY_SETTING( 200000, FULL, 200000baseKR2_Full		),
	PHY_SETTING( 200000, FULL, 200000baseLR2_ER2_FR2_Full	),
	PHY_SETTING( 200000, FULL, 200000baseDR2_Full		),
	PHY_SETTING( 200000, FULL, 200000baseSR2_Full		),
	/* 100G */
	PHY_SETTING( 100000, FULL, 100000baseCR4_Full		),
	PHY_SETTING( 100000, FULL, 100000baseKR4_Full		),
	PHY_SETTING( 100000, FULL, 100000baseLR4_ER4_Full	),
	PHY_SETTING( 100000, FULL, 100000baseSR4_Full		),
	PHY_SETTING( 100000, FULL, 100000baseCR2_Full		),
	PHY_SETTING( 100000, FULL, 100000baseKR2_Full		),
	PHY_SETTING( 100000, FULL, 100000baseLR2_ER2_FR2_Full	),
	PHY_SETTING( 100000, FULL, 100000baseDR2_Full		),
	PHY_SETTING( 100000, FULL, 100000baseSR2_Full		),
	PHY_SETTING( 100000, FULL, 100000baseCR_Full		),
	PHY_SETTING( 100000, FULL, 100000baseKR_Full		),
	PHY_SETTING( 100000, FULL, 100000baseLR_ER_FR_Full	),
	PHY_SETTING( 100000, FULL, 100000baseDR_Full		),
	PHY_SETTING( 100000, FULL, 100000baseSR_Full		),
	/* 56G */
	PHY_SETTING(  56000, FULL,  56000baseCR4_Full	  	),
	PHY_SETTING(  56000, FULL,  56000baseKR4_Full	  	),
	PHY_SETTING(  56000, FULL,  56000baseLR4_Full	  	),
	PHY_SETTING(  56000, FULL,  56000baseSR4_Full	  	),
	/* 50G */
	PHY_SETTING(  50000, FULL,  50000baseCR2_Full		),
	PHY_SETTING(  50000, FULL,  50000baseKR2_Full		),
	PHY_SETTING(  50000, FULL,  50000baseSR2_Full		),
	PHY_SETTING(  50000, FULL,  50000baseCR_Full		),
	PHY_SETTING(  50000, FULL,  50000baseKR_Full		),
	PHY_SETTING(  50000, FULL,  50000baseLR_ER_FR_Full	),
	PHY_SETTING(  50000, FULL,  50000baseDR_Full		),
	PHY_SETTING(  50000, FULL,  50000baseSR_Full		),
	/* 40G */
	PHY_SETTING(  40000, FULL,  40000baseCR4_Full		),
	PHY_SETTING(  40000, FULL,  40000baseKR4_Full		),
	PHY_SETTING(  40000, FULL,  40000baseLR4_Full		),
	PHY_SETTING(  40000, FULL,  40000baseSR4_Full		),
	/* 25G */
	PHY_SETTING(  25000, FULL,  25000baseCR_Full		),
	PHY_SETTING(  25000, FULL,  25000baseKR_Full		),
	PHY_SETTING(  25000, FULL,  25000baseSR_Full		),
	/* 20G */
	PHY_SETTING(  20000, FULL,  20000baseKR2_Full		),
	PHY_SETTING(  20000, FULL,  20000baseMLD2_Full		),
	/* 10G */
	PHY_SETTING(  10000, FULL,  10000baseCR_Full		),
	PHY_SETTING(  10000, FULL,  10000baseER_Full		),
	PHY_SETTING(  10000, FULL,  10000baseKR_Full		),
	PHY_SETTING(  10000, FULL,  10000baseKX4_Full		),
	PHY_SETTING(  10000, FULL,  10000baseLR_Full		),
	PHY_SETTING(  10000, FULL,  10000baseLRM_Full		),
	PHY_SETTING(  10000, FULL,  10000baseR_FEC		),
	PHY_SETTING(  10000, FULL,  10000baseSR_Full		),
	PHY_SETTING(  10000, FULL,  10000baseT_Full		),
	/* 5G */
	PHY_SETTING(   5000, FULL,   5000baseT_Full		),
	/* 2.5G */
	PHY_SETTING(   2500, FULL,   2500baseT_Full		),
	PHY_SETTING(   2500, FULL,   2500baseX_Full		),
	/* 1G */
	PHY_SETTING(   1000, FULL,   1000baseKX_Full		),
	PHY_SETTING(   1000, FULL,   1000baseT_Full		),
	PHY_SETTING(   1000, HALF,   1000baseT_Half		),
	PHY_SETTING(   1000, FULL,   1000baseT1_Full		),
	PHY_SETTING(   1000, FULL,   1000baseX_Full		),
	/* 100M */
	PHY_SETTING(    100, FULL,    100baseT_Full		),
	PHY_SETTING(    100, FULL,    100baseT1_Full		),
	PHY_SETTING(    100, HALF,    100baseT_Half		),
	PHY_SETTING(    100, HALF,    100baseFX_Half		),
	PHY_SETTING(    100, FULL,    100baseFX_Full		),
	/* 10M */
	PHY_SETTING(     10, FULL,     10baseT_Full		),
	PHY_SETTING(     10, HALF,     10baseT_Half		),
पूर्ण;
#अघोषित PHY_SETTING

/**
 * phy_lookup_setting - lookup a PHY setting
 * @speed: speed to match
 * @duplex: duplex to match
 * @mask: allowed link modes
 * @exact: an exact match is required
 *
 * Search the settings array क्रम a setting that matches the speed and
 * duplex, and which is supported.
 *
 * If @exact is unset, either an exact match or %शून्य क्रम no match will
 * be वापसed.
 *
 * If @exact is set, an exact match, the fastest supported setting at
 * or below the specअगरied speed, the slowest supported setting, or अगर
 * they all fail, %शून्य will be वापसed.
 */
स्थिर काष्ठा phy_setting *
phy_lookup_setting(पूर्णांक speed, पूर्णांक duplex, स्थिर अचिन्हित दीर्घ *mask, bool exact)
अणु
	स्थिर काष्ठा phy_setting *p, *match = शून्य, *last = शून्य;
	पूर्णांक i;

	क्रम (i = 0, p = settings; i < ARRAY_SIZE(settings); i++, p++) अणु
		अगर (p->bit < __ETHTOOL_LINK_MODE_MASK_NBITS &&
		    test_bit(p->bit, mask)) अणु
			last = p;
			अगर (p->speed == speed && p->duplex == duplex) अणु
				/* Exact match क्रम speed and duplex */
				match = p;
				अवरोध;
			पूर्ण अन्यथा अगर (!exact) अणु
				अगर (!match && p->speed <= speed)
					/* Candidate */
					match = p;

				अगर (p->speed < speed)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!match && !exact)
		match = last;

	वापस match;
पूर्ण
EXPORT_SYMBOL_GPL(phy_lookup_setting);

माप_प्रकार phy_speeds(अचिन्हित पूर्णांक *speeds, माप_प्रकार size,
		  अचिन्हित दीर्घ *mask)
अणु
	माप_प्रकार count;
	पूर्णांक i;

	क्रम (i = 0, count = 0; i < ARRAY_SIZE(settings) && count < size; i++)
		अगर (settings[i].bit < __ETHTOOL_LINK_MODE_MASK_NBITS &&
		    test_bit(settings[i].bit, mask) &&
		    (count == 0 || speeds[count - 1] != settings[i].speed))
			speeds[count++] = settings[i].speed;

	वापस count;
पूर्ण

अटल पूर्णांक __set_linkmode_max_speed(u32 max_speed, अचिन्हित दीर्घ *addr)
अणु
	स्थिर काष्ठा phy_setting *p;
	पूर्णांक i;

	क्रम (i = 0, p = settings; i < ARRAY_SIZE(settings); i++, p++) अणु
		अगर (p->speed > max_speed)
			linkmode_clear_bit(p->bit, addr);
		अन्यथा
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __set_phy_supported(काष्ठा phy_device *phydev, u32 max_speed)
अणु
	वापस __set_linkmode_max_speed(max_speed, phydev->supported);
पूर्ण

/**
 * phy_set_max_speed - Set the maximum speed the PHY should support
 *
 * @phydev: The phy_device काष्ठा
 * @max_speed: Maximum speed
 *
 * The PHY might be more capable than the MAC. For example a Fast Ethernet
 * is connected to a 1G PHY. This function allows the MAC to indicate its
 * maximum speed, and so limit what the PHY will advertise.
 */
पूर्णांक phy_set_max_speed(काष्ठा phy_device *phydev, u32 max_speed)
अणु
	पूर्णांक err;

	err = __set_phy_supported(phydev, max_speed);
	अगर (err)
		वापस err;

	phy_advertise_supported(phydev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(phy_set_max_speed);

व्योम of_set_phy_supported(काष्ठा phy_device *phydev)
अणु
	काष्ठा device_node *node = phydev->mdio.dev.of_node;
	u32 max_speed;

	अगर (!IS_ENABLED(CONFIG_OF_MDIO))
		वापस;

	अगर (!node)
		वापस;

	अगर (!of_property_पढ़ो_u32(node, "max-speed", &max_speed))
		__set_phy_supported(phydev, max_speed);
पूर्ण

व्योम of_set_phy_eee_broken(काष्ठा phy_device *phydev)
अणु
	काष्ठा device_node *node = phydev->mdio.dev.of_node;
	u32 broken = 0;

	अगर (!IS_ENABLED(CONFIG_OF_MDIO))
		वापस;

	अगर (!node)
		वापस;

	अगर (of_property_पढ़ो_bool(node, "eee-broken-100tx"))
		broken |= MDIO_EEE_100TX;
	अगर (of_property_पढ़ो_bool(node, "eee-broken-1000t"))
		broken |= MDIO_EEE_1000T;
	अगर (of_property_पढ़ो_bool(node, "eee-broken-10gt"))
		broken |= MDIO_EEE_10GT;
	अगर (of_property_पढ़ो_bool(node, "eee-broken-1000kx"))
		broken |= MDIO_EEE_1000KX;
	अगर (of_property_पढ़ो_bool(node, "eee-broken-10gkx4"))
		broken |= MDIO_EEE_10GKX4;
	अगर (of_property_पढ़ो_bool(node, "eee-broken-10gkr"))
		broken |= MDIO_EEE_10GKR;

	phydev->eee_broken_modes = broken;
पूर्ण

/**
 * phy_resolve_aneg_छोड़ो - Determine छोड़ो स्वतःneg results
 *
 * @phydev: The phy_device काष्ठा
 *
 * Once स्वतःneg has completed the local छोड़ो settings can be
 * resolved.  Determine अगर छोड़ो and asymmetric छोड़ो should be used
 * by the MAC.
 */

व्योम phy_resolve_aneg_छोड़ो(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->duplex == DUPLEX_FULL) अणु
		phydev->छोड़ो = linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
						  phydev->lp_advertising);
		phydev->asym_छोड़ो = linkmode_test_bit(
			ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			phydev->lp_advertising);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(phy_resolve_aneg_छोड़ो);

/**
 * phy_resolve_aneg_linkmode - resolve the advertisements पूर्णांकo PHY settings
 * @phydev: The phy_device काष्ठा
 *
 * Resolve our and the link partner advertisements पूर्णांकo their corresponding
 * speed and duplex. If full duplex was negotiated, extract the छोड़ो mode
 * from the link partner mask.
 */
व्योम phy_resolve_aneg_linkmode(काष्ठा phy_device *phydev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(common);
	पूर्णांक i;

	linkmode_and(common, phydev->lp_advertising, phydev->advertising);

	क्रम (i = 0; i < ARRAY_SIZE(settings); i++)
		अगर (test_bit(settings[i].bit, common)) अणु
			phydev->speed = settings[i].speed;
			phydev->duplex = settings[i].duplex;
			अवरोध;
		पूर्ण

	phy_resolve_aneg_छोड़ो(phydev);
पूर्ण
EXPORT_SYMBOL_GPL(phy_resolve_aneg_linkmode);

/**
 * phy_check_करोwnshअगरt - check whether करोwnshअगरt occurred
 * @phydev: The phy_device काष्ठा
 *
 * Check whether a करोwnshअगरt to a lower speed occurred. If this should be the
 * हाल warn the user.
 * Prerequisite क्रम detecting करोwnshअगरt is that PHY driver implements the
 * पढ़ो_status callback and sets phydev->speed to the actual link speed.
 */
व्योम phy_check_करोwnshअगरt(काष्ठा phy_device *phydev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(common);
	पूर्णांक i, speed = SPEED_UNKNOWN;

	phydev->करोwnshअगरted_rate = 0;

	अगर (phydev->स्वतःneg == AUTONEG_DISABLE ||
	    phydev->speed == SPEED_UNKNOWN)
		वापस;

	linkmode_and(common, phydev->lp_advertising, phydev->advertising);

	क्रम (i = 0; i < ARRAY_SIZE(settings); i++)
		अगर (test_bit(settings[i].bit, common)) अणु
			speed = settings[i].speed;
			अवरोध;
		पूर्ण

	अगर (speed == SPEED_UNKNOWN || phydev->speed >= speed)
		वापस;

	phydev_warn(phydev, "Downshift occurred from negotiated speed %s to actual speed %s, check cabling!\n",
		    phy_speed_to_str(speed), phy_speed_to_str(phydev->speed));

	phydev->करोwnshअगरted_rate = 1;
पूर्ण
EXPORT_SYMBOL_GPL(phy_check_करोwnshअगरt);

अटल पूर्णांक phy_resolve_min_speed(काष्ठा phy_device *phydev, bool fdx_only)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(common);
	पूर्णांक i = ARRAY_SIZE(settings);

	linkmode_and(common, phydev->lp_advertising, phydev->advertising);

	जबतक (--i >= 0) अणु
		अगर (test_bit(settings[i].bit, common)) अणु
			अगर (fdx_only && settings[i].duplex != DUPLEX_FULL)
				जारी;
			वापस settings[i].speed;
		पूर्ण
	पूर्ण

	वापस SPEED_UNKNOWN;
पूर्ण

पूर्णांक phy_speed_करोwn_core(काष्ठा phy_device *phydev)
अणु
	पूर्णांक min_common_speed = phy_resolve_min_speed(phydev, true);

	अगर (min_common_speed == SPEED_UNKNOWN)
		वापस -EINVAL;

	वापस __set_linkmode_max_speed(min_common_speed, phydev->advertising);
पूर्ण

अटल व्योम mmd_phy_indirect(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक devad,
			     u16 regnum)
अणु
	/* Write the desired MMD Devad */
	__mdiobus_ग_लिखो(bus, phy_addr, MII_MMD_CTRL, devad);

	/* Write the desired MMD रेजिस्टर address */
	__mdiobus_ग_लिखो(bus, phy_addr, MII_MMD_DATA, regnum);

	/* Select the Function : DATA with no post increment */
	__mdiobus_ग_लिखो(bus, phy_addr, MII_MMD_CTRL,
			devad | MII_MMD_CTRL_NOINCR);
पूर्ण

/**
 * __phy_पढ़ो_mmd - Convenience function क्रम पढ़ोing a रेजिस्टर
 * from an MMD on a given PHY.
 * @phydev: The phy_device काष्ठा
 * @devad: The MMD to पढ़ो from (0..31)
 * @regnum: The रेजिस्टर on the MMD to पढ़ो (0..65535)
 *
 * Same rules as क्रम __phy_पढ़ो();
 */
पूर्णांक __phy_पढ़ो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum)
अणु
	पूर्णांक val;

	अगर (regnum > (u16)~0 || devad > 32)
		वापस -EINVAL;

	अगर (phydev->drv && phydev->drv->पढ़ो_mmd) अणु
		val = phydev->drv->पढ़ो_mmd(phydev, devad, regnum);
	पूर्ण अन्यथा अगर (phydev->is_c45) अणु
		val = __mdiobus_c45_पढ़ो(phydev->mdio.bus, phydev->mdio.addr,
					 devad, regnum);
	पूर्ण अन्यथा अणु
		काष्ठा mii_bus *bus = phydev->mdio.bus;
		पूर्णांक phy_addr = phydev->mdio.addr;

		mmd_phy_indirect(bus, phy_addr, devad, regnum);

		/* Read the content of the MMD's selected रेजिस्टर */
		val = __mdiobus_पढ़ो(bus, phy_addr, MII_MMD_DATA);
	पूर्ण
	वापस val;
पूर्ण
EXPORT_SYMBOL(__phy_पढ़ो_mmd);

/**
 * phy_पढ़ो_mmd - Convenience function क्रम पढ़ोing a रेजिस्टर
 * from an MMD on a given PHY.
 * @phydev: The phy_device काष्ठा
 * @devad: The MMD to पढ़ो from
 * @regnum: The रेजिस्टर on the MMD to पढ़ो
 *
 * Same rules as क्रम phy_पढ़ो();
 */
पूर्णांक phy_पढ़ो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __phy_पढ़ो_mmd(phydev, devad, regnum);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(phy_पढ़ो_mmd);

/**
 * __phy_ग_लिखो_mmd - Convenience function क्रम writing a रेजिस्टर
 * on an MMD on a given PHY.
 * @phydev: The phy_device काष्ठा
 * @devad: The MMD to पढ़ो from
 * @regnum: The रेजिस्टर on the MMD to पढ़ो
 * @val: value to ग_लिखो to @regnum
 *
 * Same rules as क्रम __phy_ग_लिखो();
 */
पूर्णांक __phy_ग_लिखो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum, u16 val)
अणु
	पूर्णांक ret;

	अगर (regnum > (u16)~0 || devad > 32)
		वापस -EINVAL;

	अगर (phydev->drv && phydev->drv->ग_लिखो_mmd) अणु
		ret = phydev->drv->ग_लिखो_mmd(phydev, devad, regnum, val);
	पूर्ण अन्यथा अगर (phydev->is_c45) अणु
		ret = __mdiobus_c45_ग_लिखो(phydev->mdio.bus, phydev->mdio.addr,
					  devad, regnum, val);
	पूर्ण अन्यथा अणु
		काष्ठा mii_bus *bus = phydev->mdio.bus;
		पूर्णांक phy_addr = phydev->mdio.addr;

		mmd_phy_indirect(bus, phy_addr, devad, regnum);

		/* Write the data पूर्णांकo MMD's selected रेजिस्टर */
		__mdiobus_ग_लिखो(bus, phy_addr, MII_MMD_DATA, val);

		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__phy_ग_लिखो_mmd);

/**
 * phy_ग_लिखो_mmd - Convenience function क्रम writing a रेजिस्टर
 * on an MMD on a given PHY.
 * @phydev: The phy_device काष्ठा
 * @devad: The MMD to पढ़ो from
 * @regnum: The रेजिस्टर on the MMD to पढ़ो
 * @val: value to ग_लिखो to @regnum
 *
 * Same rules as क्रम phy_ग_लिखो();
 */
पूर्णांक phy_ग_लिखो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum, u16 val)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __phy_ग_लिखो_mmd(phydev, devad, regnum, val);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(phy_ग_लिखो_mmd);

/**
 * phy_modअगरy_changed - Function क्रम modअगरying a PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to modअगरy
 * @mask: bit mask of bits to clear
 * @set: new value of bits set in mask to ग_लिखो to @regnum
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 *
 * Returns negative त्रुटि_सं, 0 अगर there was no change, and 1 in हाल of change
 */
पूर्णांक phy_modअगरy_changed(काष्ठा phy_device *phydev, u32 regnum, u16 mask, u16 set)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __phy_modअगरy_changed(phydev, regnum, mask, set);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_modअगरy_changed);

/**
 * __phy_modअगरy - Convenience function क्रम modअगरying a PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to modअगरy
 * @mask: bit mask of bits to clear
 * @set: new value of bits set in mask to ग_लिखो to @regnum
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
पूर्णांक __phy_modअगरy(काष्ठा phy_device *phydev, u32 regnum, u16 mask, u16 set)
अणु
	पूर्णांक ret;

	ret = __phy_modअगरy_changed(phydev, regnum, mask, set);

	वापस ret < 0 ? ret : 0;
पूर्ण
EXPORT_SYMBOL_GPL(__phy_modअगरy);

/**
 * phy_modअगरy - Convenience function क्रम modअगरying a given PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to ग_लिखो
 * @mask: bit mask of bits to clear
 * @set: new value of bits set in mask to ग_लिखो to @regnum
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
पूर्णांक phy_modअगरy(काष्ठा phy_device *phydev, u32 regnum, u16 mask, u16 set)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __phy_modअगरy(phydev, regnum, mask, set);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_modअगरy);

/**
 * __phy_modअगरy_mmd_changed - Function क्रम modअगरying a रेजिस्टर on MMD
 * @phydev: the phy_device काष्ठा
 * @devad: the MMD containing रेजिस्टर to modअगरy
 * @regnum: रेजिस्टर number to modअगरy
 * @mask: bit mask of bits to clear
 * @set: new value of bits set in mask to ग_लिखो to @regnum
 *
 * Unlocked helper function which allows a MMD रेजिस्टर to be modअगरied as
 * new रेजिस्टर value = (old रेजिस्टर value & ~mask) | set
 *
 * Returns negative त्रुटि_सं, 0 अगर there was no change, and 1 in हाल of change
 */
पूर्णांक __phy_modअगरy_mmd_changed(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum,
			     u16 mask, u16 set)
अणु
	पूर्णांक new, ret;

	ret = __phy_पढ़ो_mmd(phydev, devad, regnum);
	अगर (ret < 0)
		वापस ret;

	new = (ret & ~mask) | set;
	अगर (new == ret)
		वापस 0;

	ret = __phy_ग_लिखो_mmd(phydev, devad, regnum, new);

	वापस ret < 0 ? ret : 1;
पूर्ण
EXPORT_SYMBOL_GPL(__phy_modअगरy_mmd_changed);

/**
 * phy_modअगरy_mmd_changed - Function क्रम modअगरying a रेजिस्टर on MMD
 * @phydev: the phy_device काष्ठा
 * @devad: the MMD containing रेजिस्टर to modअगरy
 * @regnum: रेजिस्टर number to modअगरy
 * @mask: bit mask of bits to clear
 * @set: new value of bits set in mask to ग_लिखो to @regnum
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 *
 * Returns negative त्रुटि_सं, 0 अगर there was no change, and 1 in हाल of change
 */
पूर्णांक phy_modअगरy_mmd_changed(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum,
			   u16 mask, u16 set)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __phy_modअगरy_mmd_changed(phydev, devad, regnum, mask, set);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_modअगरy_mmd_changed);

/**
 * __phy_modअगरy_mmd - Convenience function क्रम modअगरying a रेजिस्टर on MMD
 * @phydev: the phy_device काष्ठा
 * @devad: the MMD containing रेजिस्टर to modअगरy
 * @regnum: रेजिस्टर number to modअगरy
 * @mask: bit mask of bits to clear
 * @set: new value of bits set in mask to ग_लिखो to @regnum
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
पूर्णांक __phy_modअगरy_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum,
		     u16 mask, u16 set)
अणु
	पूर्णांक ret;

	ret = __phy_modअगरy_mmd_changed(phydev, devad, regnum, mask, set);

	वापस ret < 0 ? ret : 0;
पूर्ण
EXPORT_SYMBOL_GPL(__phy_modअगरy_mmd);

/**
 * phy_modअगरy_mmd - Convenience function क्रम modअगरying a रेजिस्टर on MMD
 * @phydev: the phy_device काष्ठा
 * @devad: the MMD containing रेजिस्टर to modअगरy
 * @regnum: रेजिस्टर number to modअगरy
 * @mask: bit mask of bits to clear
 * @set: new value of bits set in mask to ग_लिखो to @regnum
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
पूर्णांक phy_modअगरy_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum,
		   u16 mask, u16 set)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __phy_modअगरy_mmd(phydev, devad, regnum, mask, set);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_modअगरy_mmd);

अटल पूर्णांक __phy_पढ़ो_page(काष्ठा phy_device *phydev)
अणु
	अगर (WARN_ONCE(!phydev->drv->पढ़ो_page, "read_page callback not available, PHY driver not loaded?\n"))
		वापस -EOPNOTSUPP;

	वापस phydev->drv->पढ़ो_page(phydev);
पूर्ण

अटल पूर्णांक __phy_ग_लिखो_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	अगर (WARN_ONCE(!phydev->drv->ग_लिखो_page, "write_page callback not available, PHY driver not loaded?\n"))
		वापस -EOPNOTSUPP;

	वापस phydev->drv->ग_लिखो_page(phydev, page);
पूर्ण

/**
 * phy_save_page() - take the bus lock and save the current page
 * @phydev: a poपूर्णांकer to a &काष्ठा phy_device
 *
 * Take the MDIO bus lock, and वापस the current page number. On error,
 * वापसs a negative त्रुटि_सं. phy_restore_page() must always be called
 * after this, irrespective of success or failure of this call.
 */
पूर्णांक phy_save_page(काष्ठा phy_device *phydev)
अणु
	phy_lock_mdio_bus(phydev);
	वापस __phy_पढ़ो_page(phydev);
पूर्ण
EXPORT_SYMBOL_GPL(phy_save_page);

/**
 * phy_select_page() - take the bus lock, save the current page, and set a page
 * @phydev: a poपूर्णांकer to a &काष्ठा phy_device
 * @page: desired page
 *
 * Take the MDIO bus lock to protect against concurrent access, save the
 * current PHY page, and set the current page.  On error, वापसs a
 * negative त्रुटि_सं, otherwise वापसs the previous page number.
 * phy_restore_page() must always be called after this, irrespective
 * of success or failure of this call.
 */
पूर्णांक phy_select_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	पूर्णांक ret, oldpage;

	oldpage = ret = phy_save_page(phydev);
	अगर (ret < 0)
		वापस ret;

	अगर (oldpage != page) अणु
		ret = __phy_ग_लिखो_page(phydev, page);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस oldpage;
पूर्ण
EXPORT_SYMBOL_GPL(phy_select_page);

/**
 * phy_restore_page() - restore the page रेजिस्टर and release the bus lock
 * @phydev: a poपूर्णांकer to a &काष्ठा phy_device
 * @oldpage: the old page, वापस value from phy_save_page() or phy_select_page()
 * @ret: operation's वापस code
 *
 * Release the MDIO bus lock, restoring @oldpage अगर it is a valid page.
 * This function propagates the earliest error code from the group of
 * operations.
 *
 * Returns:
 *   @oldpage अगर it was a negative value, otherwise
 *   @ret अगर it was a negative त्रुटि_सं value, otherwise
 *   phy_ग_लिखो_page()'s negative value अगर it were in error, otherwise
 *   @ret.
 */
पूर्णांक phy_restore_page(काष्ठा phy_device *phydev, पूर्णांक oldpage, पूर्णांक ret)
अणु
	पूर्णांक r;

	अगर (oldpage >= 0) अणु
		r = __phy_ग_लिखो_page(phydev, oldpage);

		/* Propagate the operation वापस code अगर the page ग_लिखो
		 * was successful.
		 */
		अगर (ret >= 0 && r < 0)
			ret = r;
	पूर्ण अन्यथा अणु
		/* Propagate the phy page selection error code */
		ret = oldpage;
	पूर्ण

	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_restore_page);

/**
 * phy_पढ़ो_paged() - Convenience function क्रम पढ़ोing a paged रेजिस्टर
 * @phydev: a poपूर्णांकer to a &काष्ठा phy_device
 * @page: the page क्रम the phy
 * @regnum: रेजिस्टर number
 *
 * Same rules as क्रम phy_पढ़ो().
 */
पूर्णांक phy_पढ़ो_paged(काष्ठा phy_device *phydev, पूर्णांक page, u32 regnum)
अणु
	पूर्णांक ret = 0, oldpage;

	oldpage = phy_select_page(phydev, page);
	अगर (oldpage >= 0)
		ret = __phy_पढ़ो(phydev, regnum);

	वापस phy_restore_page(phydev, oldpage, ret);
पूर्ण
EXPORT_SYMBOL(phy_पढ़ो_paged);

/**
 * phy_ग_लिखो_paged() - Convenience function क्रम writing a paged रेजिस्टर
 * @phydev: a poपूर्णांकer to a &काष्ठा phy_device
 * @page: the page क्रम the phy
 * @regnum: रेजिस्टर number
 * @val: value to ग_लिखो
 *
 * Same rules as क्रम phy_ग_लिखो().
 */
पूर्णांक phy_ग_लिखो_paged(काष्ठा phy_device *phydev, पूर्णांक page, u32 regnum, u16 val)
अणु
	पूर्णांक ret = 0, oldpage;

	oldpage = phy_select_page(phydev, page);
	अगर (oldpage >= 0)
		ret = __phy_ग_लिखो(phydev, regnum, val);

	वापस phy_restore_page(phydev, oldpage, ret);
पूर्ण
EXPORT_SYMBOL(phy_ग_लिखो_paged);

/**
 * phy_modअगरy_paged_changed() - Function क्रम modअगरying a paged रेजिस्टर
 * @phydev: a poपूर्णांकer to a &काष्ठा phy_device
 * @page: the page क्रम the phy
 * @regnum: रेजिस्टर number
 * @mask: bit mask of bits to clear
 * @set: bit mask of bits to set
 *
 * Returns negative त्रुटि_सं, 0 अगर there was no change, and 1 in हाल of change
 */
पूर्णांक phy_modअगरy_paged_changed(काष्ठा phy_device *phydev, पूर्णांक page, u32 regnum,
			     u16 mask, u16 set)
अणु
	पूर्णांक ret = 0, oldpage;

	oldpage = phy_select_page(phydev, page);
	अगर (oldpage >= 0)
		ret = __phy_modअगरy_changed(phydev, regnum, mask, set);

	वापस phy_restore_page(phydev, oldpage, ret);
पूर्ण
EXPORT_SYMBOL(phy_modअगरy_paged_changed);

/**
 * phy_modअगरy_paged() - Convenience function क्रम modअगरying a paged रेजिस्टर
 * @phydev: a poपूर्णांकer to a &काष्ठा phy_device
 * @page: the page क्रम the phy
 * @regnum: रेजिस्टर number
 * @mask: bit mask of bits to clear
 * @set: bit mask of bits to set
 *
 * Same rules as क्रम phy_पढ़ो() and phy_ग_लिखो().
 */
पूर्णांक phy_modअगरy_paged(काष्ठा phy_device *phydev, पूर्णांक page, u32 regnum,
		     u16 mask, u16 set)
अणु
	पूर्णांक ret = phy_modअगरy_paged_changed(phydev, page, regnum, mask, set);

	वापस ret < 0 ? ret : 0;
पूर्ण
EXPORT_SYMBOL(phy_modअगरy_paged);
