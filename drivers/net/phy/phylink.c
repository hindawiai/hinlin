<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * phylink models the MAC to optional PHY connection, supporting
 * technologies such as SFP cages where the PHY is hot-pluggable.
 *
 * Copyright (C) 2015 Russell King
 */
#समावेश <linux/ethtool.h>
#समावेश <linux/export.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/phylink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>

#समावेश "sfp.h"
#समावेश "swphy.h"

#घोषणा SUPPORTED_INTERFACES \
	(SUPPORTED_TP | SUPPORTED_MII | SUPPORTED_FIBRE | \
	 SUPPORTED_BNC | SUPPORTED_AUI | SUPPORTED_Backplane)
#घोषणा ADVERTISED_INTERFACES \
	(ADVERTISED_TP | ADVERTISED_MII | ADVERTISED_FIBRE | \
	 ADVERTISED_BNC | ADVERTISED_AUI | ADVERTISED_Backplane)

क्रमागत अणु
	PHYLINK_DISABLE_STOPPED,
	PHYLINK_DISABLE_LINK,
पूर्ण;

/**
 * काष्ठा phylink - पूर्णांकernal data type क्रम phylink
 */
काष्ठा phylink अणु
	/* निजी: */
	काष्ठा net_device *netdev;
	स्थिर काष्ठा phylink_mac_ops *mac_ops;
	स्थिर काष्ठा phylink_pcs_ops *pcs_ops;
	काष्ठा phylink_config *config;
	काष्ठा phylink_pcs *pcs;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक old_link_state:1;

	अचिन्हित दीर्घ phylink_disable_state; /* biपंचांगask of disables */
	काष्ठा phy_device *phydev;
	phy_पूर्णांकerface_t link_पूर्णांकerface;	/* PHY_INTERFACE_xxx */
	u8 cfg_link_an_mode;		/* MLO_AN_xxx */
	u8 cur_link_an_mode;
	u8 link_port;			/* The current non-phy ethtool port */
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);

	/* The link configuration settings */
	काष्ठा phylink_link_state link_config;

	/* The current settings */
	phy_पूर्णांकerface_t cur_पूर्णांकerface;

	काष्ठा gpio_desc *link_gpio;
	अचिन्हित पूर्णांक link_irq;
	काष्ठा समयr_list link_poll;
	व्योम (*get_fixed_state)(काष्ठा net_device *dev,
				काष्ठा phylink_link_state *s);

	काष्ठा mutex state_mutex;
	काष्ठा phylink_link_state phy_state;
	काष्ठा work_काष्ठा resolve;

	bool mac_link_dropped;

	काष्ठा sfp_bus *sfp_bus;
	bool sfp_may_have_phy;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(sfp_support);
	u8 sfp_port;
पूर्ण;

#घोषणा phylink_prपूर्णांकk(level, pl, fmt, ...) \
	करो अणु \
		अगर ((pl)->config->type == PHYLINK_NETDEV) \
			netdev_prपूर्णांकk(level, (pl)->netdev, fmt, ##__VA_ARGS__); \
		अन्यथा अगर ((pl)->config->type == PHYLINK_DEV) \
			dev_prपूर्णांकk(level, (pl)->dev, fmt, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

#घोषणा phylink_err(pl, fmt, ...) \
	phylink_prपूर्णांकk(KERN_ERR, pl, fmt, ##__VA_ARGS__)
#घोषणा phylink_warn(pl, fmt, ...) \
	phylink_prपूर्णांकk(KERN_WARNING, pl, fmt, ##__VA_ARGS__)
#घोषणा phylink_info(pl, fmt, ...) \
	phylink_prपूर्णांकk(KERN_INFO, pl, fmt, ##__VA_ARGS__)
#अगर defined(CONFIG_DYNAMIC_DEBUG)
#घोषणा phylink_dbg(pl, fmt, ...) \
करो अणु									\
	अगर ((pl)->config->type == PHYLINK_NETDEV)			\
		netdev_dbg((pl)->netdev, fmt, ##__VA_ARGS__);		\
	अन्यथा अगर ((pl)->config->type == PHYLINK_DEV)			\
		dev_dbg((pl)->dev, fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)
#या_अगर defined(DEBUG)
#घोषणा phylink_dbg(pl, fmt, ...)					\
	phylink_prपूर्णांकk(KERN_DEBUG, pl, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा phylink_dbg(pl, fmt, ...)					\
(अणु									\
	अगर (0)								\
		phylink_prपूर्णांकk(KERN_DEBUG, pl, fmt, ##__VA_ARGS__);	\
पूर्ण)
#पूर्ण_अगर

/**
 * phylink_set_port_modes() - set the port type modes in the ethtool mask
 * @mask: ethtool link mode mask
 *
 * Sets all the port type modes in the ethtool mask.  MAC drivers should
 * use this in their 'validate' callback.
 */
व्योम phylink_set_port_modes(अचिन्हित दीर्घ *mask)
अणु
	phylink_set(mask, TP);
	phylink_set(mask, AUI);
	phylink_set(mask, MII);
	phylink_set(mask, FIBRE);
	phylink_set(mask, BNC);
	phylink_set(mask, Backplane);
पूर्ण
EXPORT_SYMBOL_GPL(phylink_set_port_modes);

अटल पूर्णांक phylink_is_empty_linkmode(स्थिर अचिन्हित दीर्घ *linkmode)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(पंचांगp) = अणु 0, पूर्ण;

	phylink_set_port_modes(पंचांगp);
	phylink_set(पंचांगp, Autoneg);
	phylink_set(पंचांगp, Pause);
	phylink_set(पंचांगp, Asym_Pause);

	वापस linkmode_subset(linkmode, पंचांगp);
पूर्ण

अटल स्थिर अक्षर *phylink_an_mode_str(अचिन्हित पूर्णांक mode)
अणु
	अटल स्थिर अक्षर *modestr[] = अणु
		[MLO_AN_PHY] = "phy",
		[MLO_AN_FIXED] = "fixed",
		[MLO_AN_INBAND] = "inband",
	पूर्ण;

	वापस mode < ARRAY_SIZE(modestr) ? modestr[mode] : "unknown";
पूर्ण

अटल पूर्णांक phylink_validate(काष्ठा phylink *pl, अचिन्हित दीर्घ *supported,
			    काष्ठा phylink_link_state *state)
अणु
	pl->mac_ops->validate(pl->config, supported, state);

	वापस phylink_is_empty_linkmode(supported) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक phylink_parse_fixedlink(काष्ठा phylink *pl,
				   काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *fixed_node;
	स्थिर काष्ठा phy_setting *s;
	काष्ठा gpio_desc *desc;
	u32 speed;
	पूर्णांक ret;

	fixed_node = fwnode_get_named_child_node(fwnode, "fixed-link");
	अगर (fixed_node) अणु
		ret = fwnode_property_पढ़ो_u32(fixed_node, "speed", &speed);

		pl->link_config.speed = speed;
		pl->link_config.duplex = DUPLEX_HALF;

		अगर (fwnode_property_पढ़ो_bool(fixed_node, "full-duplex"))
			pl->link_config.duplex = DUPLEX_FULL;

		/* We treat the "pause" and "asym-pause" terminology as
		 * defining the link partner's ability. */
		अगर (fwnode_property_पढ़ो_bool(fixed_node, "pause"))
			__set_bit(ETHTOOL_LINK_MODE_Pause_BIT,
				  pl->link_config.lp_advertising);
		अगर (fwnode_property_पढ़ो_bool(fixed_node, "asym-pause"))
			__set_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
				  pl->link_config.lp_advertising);

		अगर (ret == 0) अणु
			desc = fwnode_gpiod_get_index(fixed_node, "link", 0,
						      GPIOD_IN, "?");

			अगर (!IS_ERR(desc))
				pl->link_gpio = desc;
			अन्यथा अगर (desc == ERR_PTR(-EPROBE_DEFER))
				ret = -EPROBE_DEFER;
		पूर्ण
		fwnode_handle_put(fixed_node);

		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		u32 prop[5];

		ret = fwnode_property_पढ़ो_u32_array(fwnode, "fixed-link",
						     शून्य, 0);
		अगर (ret != ARRAY_SIZE(prop)) अणु
			phylink_err(pl, "broken fixed-link?\n");
			वापस -EINVAL;
		पूर्ण

		ret = fwnode_property_पढ़ो_u32_array(fwnode, "fixed-link",
						     prop, ARRAY_SIZE(prop));
		अगर (!ret) अणु
			pl->link_config.duplex = prop[1] ?
						DUPLEX_FULL : DUPLEX_HALF;
			pl->link_config.speed = prop[2];
			अगर (prop[3])
				__set_bit(ETHTOOL_LINK_MODE_Pause_BIT,
					  pl->link_config.lp_advertising);
			अगर (prop[4])
				__set_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
					  pl->link_config.lp_advertising);
		पूर्ण
	पूर्ण

	अगर (pl->link_config.speed > SPEED_1000 &&
	    pl->link_config.duplex != DUPLEX_FULL)
		phylink_warn(pl, "fixed link specifies half duplex for %dMbps link?\n",
			     pl->link_config.speed);

	biपंचांगap_fill(pl->supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
	linkmode_copy(pl->link_config.advertising, pl->supported);
	phylink_validate(pl, pl->supported, &pl->link_config);

	s = phy_lookup_setting(pl->link_config.speed, pl->link_config.duplex,
			       pl->supported, true);
	linkmode_zero(pl->supported);
	phylink_set(pl->supported, MII);
	phylink_set(pl->supported, Pause);
	phylink_set(pl->supported, Asym_Pause);
	phylink_set(pl->supported, Autoneg);
	अगर (s) अणु
		__set_bit(s->bit, pl->supported);
		__set_bit(s->bit, pl->link_config.lp_advertising);
	पूर्ण अन्यथा अणु
		phylink_warn(pl, "fixed link %s duplex %dMbps not recognised\n",
			     pl->link_config.duplex == DUPLEX_FULL ? "full" : "half",
			     pl->link_config.speed);
	पूर्ण

	linkmode_and(pl->link_config.advertising, pl->link_config.advertising,
		     pl->supported);

	pl->link_config.link = 1;
	pl->link_config.an_complete = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक phylink_parse_mode(काष्ठा phylink *pl, काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *dn;
	स्थिर अक्षर *managed;

	dn = fwnode_get_named_child_node(fwnode, "fixed-link");
	अगर (dn || fwnode_property_present(fwnode, "fixed-link"))
		pl->cfg_link_an_mode = MLO_AN_FIXED;
	fwnode_handle_put(dn);

	अगर ((fwnode_property_पढ़ो_string(fwnode, "managed", &managed) == 0 &&
	     म_भेद(managed, "in-band-status") == 0) ||
	    pl->config->ovr_an_inband) अणु
		अगर (pl->cfg_link_an_mode == MLO_AN_FIXED) अणु
			phylink_err(pl,
				    "can't use both fixed-link and in-band-status\n");
			वापस -EINVAL;
		पूर्ण

		linkmode_zero(pl->supported);
		phylink_set(pl->supported, MII);
		phylink_set(pl->supported, Autoneg);
		phylink_set(pl->supported, Asym_Pause);
		phylink_set(pl->supported, Pause);
		pl->link_config.an_enabled = true;
		pl->cfg_link_an_mode = MLO_AN_INBAND;

		चयन (pl->link_config.पूर्णांकerface) अणु
		हाल PHY_INTERFACE_MODE_SGMII:
		हाल PHY_INTERFACE_MODE_QSGMII:
			phylink_set(pl->supported, 10baseT_Half);
			phylink_set(pl->supported, 10baseT_Full);
			phylink_set(pl->supported, 100baseT_Half);
			phylink_set(pl->supported, 100baseT_Full);
			phylink_set(pl->supported, 1000baseT_Half);
			phylink_set(pl->supported, 1000baseT_Full);
			अवरोध;

		हाल PHY_INTERFACE_MODE_1000BASEX:
			phylink_set(pl->supported, 1000baseX_Full);
			अवरोध;

		हाल PHY_INTERFACE_MODE_2500BASEX:
			phylink_set(pl->supported, 2500baseX_Full);
			अवरोध;

		हाल PHY_INTERFACE_MODE_5GBASER:
			phylink_set(pl->supported, 5000baseT_Full);
			अवरोध;

		हाल PHY_INTERFACE_MODE_USXGMII:
		हाल PHY_INTERFACE_MODE_10GKR:
		हाल PHY_INTERFACE_MODE_10GBASER:
			phylink_set(pl->supported, 10baseT_Half);
			phylink_set(pl->supported, 10baseT_Full);
			phylink_set(pl->supported, 100baseT_Half);
			phylink_set(pl->supported, 100baseT_Full);
			phylink_set(pl->supported, 1000baseT_Half);
			phylink_set(pl->supported, 1000baseT_Full);
			phylink_set(pl->supported, 1000baseX_Full);
			phylink_set(pl->supported, 1000baseKX_Full);
			phylink_set(pl->supported, 2500baseT_Full);
			phylink_set(pl->supported, 2500baseX_Full);
			phylink_set(pl->supported, 5000baseT_Full);
			phylink_set(pl->supported, 10000baseT_Full);
			phylink_set(pl->supported, 10000baseKR_Full);
			phylink_set(pl->supported, 10000baseKX4_Full);
			phylink_set(pl->supported, 10000baseCR_Full);
			phylink_set(pl->supported, 10000baseSR_Full);
			phylink_set(pl->supported, 10000baseLR_Full);
			phylink_set(pl->supported, 10000baseLRM_Full);
			phylink_set(pl->supported, 10000baseER_Full);
			अवरोध;

		हाल PHY_INTERFACE_MODE_XLGMII:
			phylink_set(pl->supported, 25000baseCR_Full);
			phylink_set(pl->supported, 25000baseKR_Full);
			phylink_set(pl->supported, 25000baseSR_Full);
			phylink_set(pl->supported, 40000baseKR4_Full);
			phylink_set(pl->supported, 40000baseCR4_Full);
			phylink_set(pl->supported, 40000baseSR4_Full);
			phylink_set(pl->supported, 40000baseLR4_Full);
			phylink_set(pl->supported, 50000baseCR2_Full);
			phylink_set(pl->supported, 50000baseKR2_Full);
			phylink_set(pl->supported, 50000baseSR2_Full);
			phylink_set(pl->supported, 50000baseKR_Full);
			phylink_set(pl->supported, 50000baseSR_Full);
			phylink_set(pl->supported, 50000baseCR_Full);
			phylink_set(pl->supported, 50000baseLR_ER_FR_Full);
			phylink_set(pl->supported, 50000baseDR_Full);
			phylink_set(pl->supported, 100000baseKR4_Full);
			phylink_set(pl->supported, 100000baseSR4_Full);
			phylink_set(pl->supported, 100000baseCR4_Full);
			phylink_set(pl->supported, 100000baseLR4_ER4_Full);
			phylink_set(pl->supported, 100000baseKR2_Full);
			phylink_set(pl->supported, 100000baseSR2_Full);
			phylink_set(pl->supported, 100000baseCR2_Full);
			phylink_set(pl->supported, 100000baseLR2_ER2_FR2_Full);
			phylink_set(pl->supported, 100000baseDR2_Full);
			अवरोध;

		शेष:
			phylink_err(pl,
				    "incorrect link mode %s for in-band status\n",
				    phy_modes(pl->link_config.पूर्णांकerface));
			वापस -EINVAL;
		पूर्ण

		linkmode_copy(pl->link_config.advertising, pl->supported);

		अगर (phylink_validate(pl, pl->supported, &pl->link_config)) अणु
			phylink_err(pl,
				    "failed to validate link configuration for in-band status\n");
			वापस -EINVAL;
		पूर्ण

		/* Check अगर MAC/PCS also supports Autoneg. */
		pl->link_config.an_enabled = phylink_test(pl->supported, Autoneg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम phylink_apply_manual_flow(काष्ठा phylink *pl,
				      काष्ठा phylink_link_state *state)
अणु
	/* If स्वतःneg is disabled, छोड़ो AN is also disabled */
	अगर (!state->an_enabled)
		state->छोड़ो &= ~MLO_PAUSE_AN;

	/* Manual configuration of छोड़ो modes */
	अगर (!(pl->link_config.छोड़ो & MLO_PAUSE_AN))
		state->छोड़ो = pl->link_config.छोड़ो;
पूर्ण

अटल व्योम phylink_resolve_flow(काष्ठा phylink_link_state *state)
अणु
	bool tx_छोड़ो, rx_छोड़ो;

	state->छोड़ो = MLO_PAUSE_NONE;
	अगर (state->duplex == DUPLEX_FULL) अणु
		linkmode_resolve_छोड़ो(state->advertising,
				       state->lp_advertising,
				       &tx_छोड़ो, &rx_छोड़ो);
		अगर (tx_छोड़ो)
			state->छोड़ो |= MLO_PAUSE_TX;
		अगर (rx_छोड़ो)
			state->छोड़ो |= MLO_PAUSE_RX;
	पूर्ण
पूर्ण

अटल व्योम phylink_mac_config(काष्ठा phylink *pl,
			       स्थिर काष्ठा phylink_link_state *state)
अणु
	phylink_dbg(pl,
		    "%s: mode=%s/%s/%s/%s adv=%*pb pause=%02x link=%u an=%u\n",
		    __func__, phylink_an_mode_str(pl->cur_link_an_mode),
		    phy_modes(state->पूर्णांकerface),
		    phy_speed_to_str(state->speed),
		    phy_duplex_to_str(state->duplex),
		    __ETHTOOL_LINK_MODE_MASK_NBITS, state->advertising,
		    state->छोड़ो, state->link, state->an_enabled);

	pl->mac_ops->mac_config(pl->config, pl->cur_link_an_mode, state);
पूर्ण

अटल व्योम phylink_mac_pcs_an_restart(काष्ठा phylink *pl)
अणु
	अगर (pl->link_config.an_enabled &&
	    phy_पूर्णांकerface_mode_is_8023z(pl->link_config.पूर्णांकerface) &&
	    phylink_स्वतःneg_inband(pl->cur_link_an_mode)) अणु
		अगर (pl->pcs_ops)
			pl->pcs_ops->pcs_an_restart(pl->pcs);
		अन्यथा
			pl->mac_ops->mac_an_restart(pl->config);
	पूर्ण
पूर्ण

अटल व्योम phylink_major_config(काष्ठा phylink *pl, bool restart,
				  स्थिर काष्ठा phylink_link_state *state)
अणु
	पूर्णांक err;

	phylink_dbg(pl, "major config %s\n", phy_modes(state->पूर्णांकerface));

	अगर (pl->mac_ops->mac_prepare) अणु
		err = pl->mac_ops->mac_prepare(pl->config, pl->cur_link_an_mode,
					       state->पूर्णांकerface);
		अगर (err < 0) अणु
			phylink_err(pl, "mac_prepare failed: %pe\n",
				    ERR_PTR(err));
			वापस;
		पूर्ण
	पूर्ण

	phylink_mac_config(pl, state);

	अगर (pl->pcs_ops) अणु
		err = pl->pcs_ops->pcs_config(pl->pcs, pl->cur_link_an_mode,
					      state->पूर्णांकerface,
					      state->advertising,
					      !!(pl->link_config.छोड़ो &
						 MLO_PAUSE_AN));
		अगर (err < 0)
			phylink_err(pl, "pcs_config failed: %pe\n",
				    ERR_PTR(err));
		अगर (err > 0)
			restart = true;
	पूर्ण
	अगर (restart)
		phylink_mac_pcs_an_restart(pl);

	अगर (pl->mac_ops->mac_finish) अणु
		err = pl->mac_ops->mac_finish(pl->config, pl->cur_link_an_mode,
					      state->पूर्णांकerface);
		अगर (err < 0)
			phylink_err(pl, "mac_finish failed: %pe\n",
				    ERR_PTR(err));
	पूर्ण
पूर्ण

/*
 * Reconfigure क्रम a change of inband advertisement.
 * If we have a separate PCS, we only need to call its pcs_config() method,
 * and then restart AN अगर it indicates something changed. Otherwise, we करो
 * the full MAC reconfiguration.
 */
अटल पूर्णांक phylink_change_inband_advert(काष्ठा phylink *pl)
अणु
	पूर्णांक ret;

	अगर (test_bit(PHYLINK_DISABLE_STOPPED, &pl->phylink_disable_state))
		वापस 0;

	अगर (!pl->pcs_ops) अणु
		/* Legacy method */
		phylink_mac_config(pl, &pl->link_config);
		phylink_mac_pcs_an_restart(pl);
		वापस 0;
	पूर्ण

	phylink_dbg(pl, "%s: mode=%s/%s adv=%*pb pause=%02x\n", __func__,
		    phylink_an_mode_str(pl->cur_link_an_mode),
		    phy_modes(pl->link_config.पूर्णांकerface),
		    __ETHTOOL_LINK_MODE_MASK_NBITS, pl->link_config.advertising,
		    pl->link_config.छोड़ो);

	/* Modern PCS-based method; update the advert at the PCS, and
	 * restart negotiation अगर the pcs_config() helper indicates that
	 * the programmed advertisement has changed.
	 */
	ret = pl->pcs_ops->pcs_config(pl->pcs, pl->cur_link_an_mode,
				      pl->link_config.पूर्णांकerface,
				      pl->link_config.advertising,
				      !!(pl->link_config.छोड़ो & MLO_PAUSE_AN));
	अगर (ret < 0)
		वापस ret;

	अगर (ret > 0)
		phylink_mac_pcs_an_restart(pl);

	वापस 0;
पूर्ण

अटल व्योम phylink_mac_pcs_get_state(काष्ठा phylink *pl,
				      काष्ठा phylink_link_state *state)
अणु
	linkmode_copy(state->advertising, pl->link_config.advertising);
	linkmode_zero(state->lp_advertising);
	state->पूर्णांकerface = pl->link_config.पूर्णांकerface;
	state->an_enabled = pl->link_config.an_enabled;
	state->speed = SPEED_UNKNOWN;
	state->duplex = DUPLEX_UNKNOWN;
	state->छोड़ो = MLO_PAUSE_NONE;
	state->an_complete = 0;
	state->link = 1;

	अगर (pl->pcs_ops)
		pl->pcs_ops->pcs_get_state(pl->pcs, state);
	अन्यथा अगर (pl->mac_ops->mac_pcs_get_state)
		pl->mac_ops->mac_pcs_get_state(pl->config, state);
	अन्यथा
		state->link = 0;
पूर्ण

/* The fixed state is... fixed except क्रम the link state,
 * which may be determined by a GPIO or a callback.
 */
अटल व्योम phylink_get_fixed_state(काष्ठा phylink *pl,
				    काष्ठा phylink_link_state *state)
अणु
	*state = pl->link_config;
	अगर (pl->config->get_fixed_state)
		pl->config->get_fixed_state(pl->config, state);
	अन्यथा अगर (pl->link_gpio)
		state->link = !!gpiod_get_value_cansleep(pl->link_gpio);

	phylink_resolve_flow(state);
पूर्ण

अटल व्योम phylink_mac_initial_config(काष्ठा phylink *pl, bool क्रमce_restart)
अणु
	काष्ठा phylink_link_state link_state;

	चयन (pl->cur_link_an_mode) अणु
	हाल MLO_AN_PHY:
		link_state = pl->phy_state;
		अवरोध;

	हाल MLO_AN_FIXED:
		phylink_get_fixed_state(pl, &link_state);
		अवरोध;

	हाल MLO_AN_INBAND:
		link_state = pl->link_config;
		अगर (link_state.पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
			link_state.छोड़ो = MLO_PAUSE_NONE;
		अवरोध;

	शेष: /* can't happen */
		वापस;
	पूर्ण

	link_state.link = false;

	phylink_apply_manual_flow(pl, &link_state);
	phylink_major_config(pl, क्रमce_restart, &link_state);
पूर्ण

अटल स्थिर अक्षर *phylink_छोड़ो_to_str(पूर्णांक छोड़ो)
अणु
	चयन (छोड़ो & MLO_PAUSE_TXRX_MASK) अणु
	हाल MLO_PAUSE_TX | MLO_PAUSE_RX:
		वापस "rx/tx";
	हाल MLO_PAUSE_TX:
		वापस "tx";
	हाल MLO_PAUSE_RX:
		वापस "rx";
	शेष:
		वापस "off";
	पूर्ण
पूर्ण

अटल व्योम phylink_link_up(काष्ठा phylink *pl,
			    काष्ठा phylink_link_state link_state)
अणु
	काष्ठा net_device *ndev = pl->netdev;

	pl->cur_पूर्णांकerface = link_state.पूर्णांकerface;

	अगर (pl->pcs_ops && pl->pcs_ops->pcs_link_up)
		pl->pcs_ops->pcs_link_up(pl->pcs, pl->cur_link_an_mode,
					 pl->cur_पूर्णांकerface,
					 link_state.speed, link_state.duplex);

	pl->mac_ops->mac_link_up(pl->config, pl->phydev,
				 pl->cur_link_an_mode, pl->cur_पूर्णांकerface,
				 link_state.speed, link_state.duplex,
				 !!(link_state.छोड़ो & MLO_PAUSE_TX),
				 !!(link_state.छोड़ो & MLO_PAUSE_RX));

	अगर (ndev)
		netअगर_carrier_on(ndev);

	phylink_info(pl,
		     "Link is Up - %s/%s - flow control %s\n",
		     phy_speed_to_str(link_state.speed),
		     phy_duplex_to_str(link_state.duplex),
		     phylink_छोड़ो_to_str(link_state.छोड़ो));
पूर्ण

अटल व्योम phylink_link_करोwn(काष्ठा phylink *pl)
अणु
	काष्ठा net_device *ndev = pl->netdev;

	अगर (ndev)
		netअगर_carrier_off(ndev);
	pl->mac_ops->mac_link_करोwn(pl->config, pl->cur_link_an_mode,
				   pl->cur_पूर्णांकerface);
	phylink_info(pl, "Link is Down\n");
पूर्ण

अटल व्योम phylink_resolve(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा phylink *pl = container_of(w, काष्ठा phylink, resolve);
	काष्ठा phylink_link_state link_state;
	काष्ठा net_device *ndev = pl->netdev;
	bool mac_config = false;
	bool cur_link_state;

	mutex_lock(&pl->state_mutex);
	अगर (pl->netdev)
		cur_link_state = netअगर_carrier_ok(ndev);
	अन्यथा
		cur_link_state = pl->old_link_state;

	अगर (pl->phylink_disable_state) अणु
		pl->mac_link_dropped = false;
		link_state.link = false;
	पूर्ण अन्यथा अगर (pl->mac_link_dropped) अणु
		link_state.link = false;
	पूर्ण अन्यथा अणु
		चयन (pl->cur_link_an_mode) अणु
		हाल MLO_AN_PHY:
			link_state = pl->phy_state;
			phylink_apply_manual_flow(pl, &link_state);
			mac_config = link_state.link;
			अवरोध;

		हाल MLO_AN_FIXED:
			phylink_get_fixed_state(pl, &link_state);
			mac_config = link_state.link;
			अवरोध;

		हाल MLO_AN_INBAND:
			phylink_mac_pcs_get_state(pl, &link_state);

			/* If we have a phy, the "up" state is the जोड़ of
			 * both the PHY and the MAC */
			अगर (pl->phydev)
				link_state.link &= pl->phy_state.link;

			/* Only update अगर the PHY link is up */
			अगर (pl->phydev && pl->phy_state.link) अणु
				link_state.पूर्णांकerface = pl->phy_state.पूर्णांकerface;

				/* If we have a PHY, we need to update with
				 * the PHY flow control bits. */
				link_state.छोड़ो = pl->phy_state.छोड़ो;
				mac_config = true;
			पूर्ण
			phylink_apply_manual_flow(pl, &link_state);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mac_config) अणु
		अगर (link_state.पूर्णांकerface != pl->link_config.पूर्णांकerface) अणु
			/* The पूर्णांकerface has changed, क्रमce the link करोwn and
			 * then reconfigure.
			 */
			अगर (cur_link_state) अणु
				phylink_link_करोwn(pl);
				cur_link_state = false;
			पूर्ण
			phylink_major_config(pl, false, &link_state);
			pl->link_config.पूर्णांकerface = link_state.पूर्णांकerface;
		पूर्ण अन्यथा अगर (!pl->pcs_ops) अणु
			/* The पूर्णांकerface reमुख्यs unchanged, only the speed,
			 * duplex or छोड़ो settings have changed. Call the
			 * old mac_config() method to configure the MAC/PCS
			 * only अगर we करो not have a PCS installed (an
			 * unconverted user.)
			 */
			phylink_mac_config(pl, &link_state);
		पूर्ण
	पूर्ण

	अगर (link_state.link != cur_link_state) अणु
		pl->old_link_state = link_state.link;
		अगर (!link_state.link)
			phylink_link_करोwn(pl);
		अन्यथा
			phylink_link_up(pl, link_state);
	पूर्ण
	अगर (!link_state.link && pl->mac_link_dropped) अणु
		pl->mac_link_dropped = false;
		queue_work(प्रणाली_घातer_efficient_wq, &pl->resolve);
	पूर्ण
	mutex_unlock(&pl->state_mutex);
पूर्ण

अटल व्योम phylink_run_resolve(काष्ठा phylink *pl)
अणु
	अगर (!pl->phylink_disable_state)
		queue_work(प्रणाली_घातer_efficient_wq, &pl->resolve);
पूर्ण

अटल व्योम phylink_run_resolve_and_disable(काष्ठा phylink *pl, पूर्णांक bit)
अणु
	अचिन्हित दीर्घ state = pl->phylink_disable_state;

	set_bit(bit, &pl->phylink_disable_state);
	अगर (state == 0) अणु
		queue_work(प्रणाली_घातer_efficient_wq, &pl->resolve);
		flush_work(&pl->resolve);
	पूर्ण
पूर्ण

अटल व्योम phylink_fixed_poll(काष्ठा समयr_list *t)
अणु
	काष्ठा phylink *pl = container_of(t, काष्ठा phylink, link_poll);

	mod_समयr(t, jअगरfies + HZ);

	phylink_run_resolve(pl);
पूर्ण

अटल स्थिर काष्ठा sfp_upstream_ops sfp_phylink_ops;

अटल पूर्णांक phylink_रेजिस्टर_sfp(काष्ठा phylink *pl,
				काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा sfp_bus *bus;
	पूर्णांक ret;

	अगर (!fwnode)
		वापस 0;

	bus = sfp_bus_find_fwnode(fwnode);
	अगर (IS_ERR(bus)) अणु
		ret = PTR_ERR(bus);
		phylink_err(pl, "unable to attach SFP bus: %d\n", ret);
		वापस ret;
	पूर्ण

	pl->sfp_bus = bus;

	ret = sfp_bus_add_upstream(bus, pl, &sfp_phylink_ops);
	sfp_bus_put(bus);

	वापस ret;
पूर्ण

/**
 * phylink_create() - create a phylink instance
 * @config: a poपूर्णांकer to the target &काष्ठा phylink_config
 * @fwnode: a poपूर्णांकer to a &काष्ठा fwnode_handle describing the network
 *	पूर्णांकerface
 * @अगरace: the desired link mode defined by &प्रकार phy_पूर्णांकerface_t
 * @mac_ops: a poपूर्णांकer to a &काष्ठा phylink_mac_ops क्रम the MAC.
 *
 * Create a new phylink instance, and parse the link parameters found in @np.
 * This will parse in-band modes, fixed-link or SFP configuration.
 *
 * Note: the rtnl lock must not be held when calling this function.
 *
 * Returns a poपूर्णांकer to a &काष्ठा phylink, or an error-poपूर्णांकer value. Users
 * must use IS_ERR() to check क्रम errors from this function.
 */
काष्ठा phylink *phylink_create(काष्ठा phylink_config *config,
			       काष्ठा fwnode_handle *fwnode,
			       phy_पूर्णांकerface_t अगरace,
			       स्थिर काष्ठा phylink_mac_ops *mac_ops)
अणु
	काष्ठा phylink *pl;
	पूर्णांक ret;

	pl = kzalloc(माप(*pl), GFP_KERNEL);
	अगर (!pl)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&pl->state_mutex);
	INIT_WORK(&pl->resolve, phylink_resolve);

	pl->config = config;
	अगर (config->type == PHYLINK_NETDEV) अणु
		pl->netdev = to_net_dev(config->dev);
	पूर्ण अन्यथा अगर (config->type == PHYLINK_DEV) अणु
		pl->dev = config->dev;
	पूर्ण अन्यथा अणु
		kमुक्त(pl);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pl->phy_state.पूर्णांकerface = अगरace;
	pl->link_पूर्णांकerface = अगरace;
	अगर (अगरace == PHY_INTERFACE_MODE_MOCA)
		pl->link_port = PORT_BNC;
	अन्यथा
		pl->link_port = PORT_MII;
	pl->link_config.पूर्णांकerface = अगरace;
	pl->link_config.छोड़ो = MLO_PAUSE_AN;
	pl->link_config.speed = SPEED_UNKNOWN;
	pl->link_config.duplex = DUPLEX_UNKNOWN;
	pl->link_config.an_enabled = true;
	pl->mac_ops = mac_ops;
	__set_bit(PHYLINK_DISABLE_STOPPED, &pl->phylink_disable_state);
	समयr_setup(&pl->link_poll, phylink_fixed_poll, 0);

	biपंचांगap_fill(pl->supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
	linkmode_copy(pl->link_config.advertising, pl->supported);
	phylink_validate(pl, pl->supported, &pl->link_config);

	ret = phylink_parse_mode(pl, fwnode);
	अगर (ret < 0) अणु
		kमुक्त(pl);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (pl->cfg_link_an_mode == MLO_AN_FIXED) अणु
		ret = phylink_parse_fixedlink(pl, fwnode);
		अगर (ret < 0) अणु
			kमुक्त(pl);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	pl->cur_link_an_mode = pl->cfg_link_an_mode;

	ret = phylink_रेजिस्टर_sfp(pl, fwnode);
	अगर (ret < 0) अणु
		kमुक्त(pl);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस pl;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_create);

/**
 * phylink_set_pcs() - set the current PCS क्रम phylink to use
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @pcs: a poपूर्णांकer to the &काष्ठा phylink_pcs
 *
 * Bind the MAC PCS to phylink.  This may be called after phylink_create(),
 * in mac_prepare() or mac_config() methods अगर it is desired to dynamically
 * change the PCS.
 *
 * Please note that there are behavioural changes with the mac_config()
 * callback अगर a PCS is present (denoting a newer setup) so removing a PCS
 * is not supported, and अगर a PCS is going to be used, it must be रेजिस्टरed
 * by calling phylink_set_pcs() at the latest in the first mac_config() call.
 */
व्योम phylink_set_pcs(काष्ठा phylink *pl, काष्ठा phylink_pcs *pcs)
अणु
	pl->pcs = pcs;
	pl->pcs_ops = pcs->ops;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_set_pcs);

/**
 * phylink_destroy() - cleanup and destroy the phylink instance
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 *
 * Destroy a phylink instance. Any PHY that has been attached must have been
 * cleaned up via phylink_disconnect_phy() prior to calling this function.
 *
 * Note: the rtnl lock must not be held when calling this function.
 */
व्योम phylink_destroy(काष्ठा phylink *pl)
अणु
	sfp_bus_del_upstream(pl->sfp_bus);
	अगर (pl->link_gpio)
		gpiod_put(pl->link_gpio);

	cancel_work_sync(&pl->resolve);
	kमुक्त(pl);
पूर्ण
EXPORT_SYMBOL_GPL(phylink_destroy);

अटल व्योम phylink_phy_change(काष्ठा phy_device *phydev, bool up)
अणु
	काष्ठा phylink *pl = phydev->phylink;
	bool tx_छोड़ो, rx_छोड़ो;

	phy_get_छोड़ो(phydev, &tx_छोड़ो, &rx_छोड़ो);

	mutex_lock(&pl->state_mutex);
	pl->phy_state.speed = phydev->speed;
	pl->phy_state.duplex = phydev->duplex;
	pl->phy_state.छोड़ो = MLO_PAUSE_NONE;
	अगर (tx_छोड़ो)
		pl->phy_state.छोड़ो |= MLO_PAUSE_TX;
	अगर (rx_छोड़ो)
		pl->phy_state.छोड़ो |= MLO_PAUSE_RX;
	pl->phy_state.पूर्णांकerface = phydev->पूर्णांकerface;
	pl->phy_state.link = up;
	mutex_unlock(&pl->state_mutex);

	phylink_run_resolve(pl);

	phylink_dbg(pl, "phy link %s %s/%s/%s\n", up ? "up" : "down",
		    phy_modes(phydev->पूर्णांकerface),
		    phy_speed_to_str(phydev->speed),
		    phy_duplex_to_str(phydev->duplex));
पूर्ण

अटल पूर्णांक phylink_bringup_phy(काष्ठा phylink *pl, काष्ठा phy_device *phy,
			       phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा phylink_link_state config;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);
	अक्षर *irq_str;
	पूर्णांक ret;

	/*
	 * This is the new way of dealing with flow control क्रम PHYs,
	 * as described by Timur Tabi in commit 529ed1275263 ("net: phy:
	 * phy drivers should not set SUPPORTED_[Asym_]Pause") except
	 * using our validate call to the MAC, we rely upon the MAC
	 * clearing the bits from both supported and advertising fields.
	 */
	phy_support_asym_छोड़ो(phy);

	स_रखो(&config, 0, माप(config));
	linkmode_copy(supported, phy->supported);
	linkmode_copy(config.advertising, phy->advertising);

	/* Clause 45 PHYs चयन their Serdes lane between several dअगरferent
	 * modes, normally 10GBASE-R, SGMII. Some use 2500BASE-X क्रम 2.5G
	 * speeds. We really need to know which पूर्णांकerface modes the PHY and
	 * MAC supports to properly work out which linkmodes can be supported.
	 */
	अगर (phy->is_c45 &&
	    पूर्णांकerface != PHY_INTERFACE_MODE_RXAUI &&
	    पूर्णांकerface != PHY_INTERFACE_MODE_XAUI &&
	    पूर्णांकerface != PHY_INTERFACE_MODE_USXGMII)
		config.पूर्णांकerface = PHY_INTERFACE_MODE_NA;
	अन्यथा
		config.पूर्णांकerface = पूर्णांकerface;

	ret = phylink_validate(pl, supported, &config);
	अगर (ret) अणु
		phylink_warn(pl, "validation of %s with support %*pb and advertisement %*pb failed: %d\n",
			     phy_modes(config.पूर्णांकerface),
			     __ETHTOOL_LINK_MODE_MASK_NBITS, phy->supported,
			     __ETHTOOL_LINK_MODE_MASK_NBITS, config.advertising,
			     ret);
		वापस ret;
	पूर्ण

	phy->phylink = pl;
	phy->phy_link_change = phylink_phy_change;

	irq_str = phy_attached_info_irq(phy);
	phylink_info(pl,
		     "PHY [%s] driver [%s] (irq=%s)\n",
		     dev_name(&phy->mdio.dev), phy->drv->name, irq_str);
	kमुक्त(irq_str);

	mutex_lock(&phy->lock);
	mutex_lock(&pl->state_mutex);
	pl->phydev = phy;
	pl->phy_state.पूर्णांकerface = पूर्णांकerface;
	pl->phy_state.छोड़ो = MLO_PAUSE_NONE;
	pl->phy_state.speed = SPEED_UNKNOWN;
	pl->phy_state.duplex = DUPLEX_UNKNOWN;
	linkmode_copy(pl->supported, supported);
	linkmode_copy(pl->link_config.advertising, config.advertising);

	/* Restrict the phy advertisement according to the MAC support. */
	linkmode_copy(phy->advertising, config.advertising);
	mutex_unlock(&pl->state_mutex);
	mutex_unlock(&phy->lock);

	phylink_dbg(pl,
		    "phy: setting supported %*pb advertising %*pb\n",
		    __ETHTOOL_LINK_MODE_MASK_NBITS, pl->supported,
		    __ETHTOOL_LINK_MODE_MASK_NBITS, phy->advertising);

	अगर (phy_पूर्णांकerrupt_is_valid(phy))
		phy_request_पूर्णांकerrupt(phy);

	वापस 0;
पूर्ण

अटल पूर्णांक phylink_attach_phy(काष्ठा phylink *pl, काष्ठा phy_device *phy,
			      phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	अगर (WARN_ON(pl->cfg_link_an_mode == MLO_AN_FIXED ||
		    (pl->cfg_link_an_mode == MLO_AN_INBAND &&
		     phy_पूर्णांकerface_mode_is_8023z(पूर्णांकerface))))
		वापस -EINVAL;

	अगर (pl->phydev)
		वापस -EBUSY;

	वापस phy_attach_direct(pl->netdev, phy, 0, पूर्णांकerface);
पूर्ण

/**
 * phylink_connect_phy() - connect a PHY to the phylink instance
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @phy: a poपूर्णांकer to a &काष्ठा phy_device.
 *
 * Connect @phy to the phylink instance specअगरied by @pl by calling
 * phy_attach_direct(). Configure the @phy according to the MAC driver's
 * capabilities, start the PHYLIB state machine and enable any पूर्णांकerrupts
 * that the PHY supports.
 *
 * This updates the phylink's ethtool supported and advertising link mode
 * masks.
 *
 * Returns 0 on success or a negative त्रुटि_सं.
 */
पूर्णांक phylink_connect_phy(काष्ठा phylink *pl, काष्ठा phy_device *phy)
अणु
	पूर्णांक ret;

	/* Use PHY device/driver पूर्णांकerface */
	अगर (pl->link_पूर्णांकerface == PHY_INTERFACE_MODE_NA) अणु
		pl->link_पूर्णांकerface = phy->पूर्णांकerface;
		pl->link_config.पूर्णांकerface = pl->link_पूर्णांकerface;
	पूर्ण

	ret = phylink_attach_phy(pl, phy, pl->link_पूर्णांकerface);
	अगर (ret < 0)
		वापस ret;

	ret = phylink_bringup_phy(pl, phy, pl->link_config.पूर्णांकerface);
	अगर (ret)
		phy_detach(phy);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_connect_phy);

/**
 * phylink_of_phy_connect() - connect the PHY specअगरied in the DT mode.
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @dn: a poपूर्णांकer to a &काष्ठा device_node.
 * @flags: PHY-specअगरic flags to communicate to the PHY device driver
 *
 * Connect the phy specअगरied in the device node @dn to the phylink instance
 * specअगरied by @pl. Actions specअगरied in phylink_connect_phy() will be
 * perक्रमmed.
 *
 * Returns 0 on success or a negative त्रुटि_सं.
 */
पूर्णांक phylink_of_phy_connect(काष्ठा phylink *pl, काष्ठा device_node *dn,
			   u32 flags)
अणु
	काष्ठा device_node *phy_node;
	काष्ठा phy_device *phy_dev;
	पूर्णांक ret;

	/* Fixed links and 802.3z are handled without needing a PHY */
	अगर (pl->cfg_link_an_mode == MLO_AN_FIXED ||
	    (pl->cfg_link_an_mode == MLO_AN_INBAND &&
	     phy_पूर्णांकerface_mode_is_8023z(pl->link_पूर्णांकerface)))
		वापस 0;

	phy_node = of_parse_phandle(dn, "phy-handle", 0);
	अगर (!phy_node)
		phy_node = of_parse_phandle(dn, "phy", 0);
	अगर (!phy_node)
		phy_node = of_parse_phandle(dn, "phy-device", 0);

	अगर (!phy_node) अणु
		अगर (pl->cfg_link_an_mode == MLO_AN_PHY)
			वापस -ENODEV;
		वापस 0;
	पूर्ण

	phy_dev = of_phy_find_device(phy_node);
	/* We're करोne with the phy_node handle */
	of_node_put(phy_node);
	अगर (!phy_dev)
		वापस -ENODEV;

	ret = phy_attach_direct(pl->netdev, phy_dev, flags,
				pl->link_पूर्णांकerface);
	अगर (ret)
		वापस ret;

	ret = phylink_bringup_phy(pl, phy_dev, pl->link_config.पूर्णांकerface);
	अगर (ret)
		phy_detach(phy_dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_of_phy_connect);

/**
 * phylink_disconnect_phy() - disconnect any PHY attached to the phylink
 *   instance.
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 *
 * Disconnect any current PHY from the phylink instance described by @pl.
 */
व्योम phylink_disconnect_phy(काष्ठा phylink *pl)
अणु
	काष्ठा phy_device *phy;

	ASSERT_RTNL();

	phy = pl->phydev;
	अगर (phy) अणु
		mutex_lock(&phy->lock);
		mutex_lock(&pl->state_mutex);
		pl->phydev = शून्य;
		mutex_unlock(&pl->state_mutex);
		mutex_unlock(&phy->lock);
		flush_work(&pl->resolve);

		phy_disconnect(phy);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(phylink_disconnect_phy);

/**
 * phylink_mac_change() - notअगरy phylink of a change in MAC state
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @up: indicates whether the link is currently up.
 *
 * The MAC driver should call this driver when the state of its link
 * changes (eg, link failure, new negotiation results, etc.)
 */
व्योम phylink_mac_change(काष्ठा phylink *pl, bool up)
अणु
	अगर (!up)
		pl->mac_link_dropped = true;
	phylink_run_resolve(pl);
	phylink_dbg(pl, "mac link %s\n", up ? "up" : "down");
पूर्ण
EXPORT_SYMBOL_GPL(phylink_mac_change);

अटल irqवापस_t phylink_link_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा phylink *pl = data;

	phylink_run_resolve(pl);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * phylink_start() - start a phylink instance
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 *
 * Start the phylink instance specअगरied by @pl, configuring the MAC क्रम the
 * desired link mode(s) and negotiation style. This should be called from the
 * network device driver's &काष्ठा net_device_ops nकरो_खोलो() method.
 */
व्योम phylink_start(काष्ठा phylink *pl)
अणु
	bool poll = false;

	ASSERT_RTNL();

	phylink_info(pl, "configuring for %s/%s link mode\n",
		     phylink_an_mode_str(pl->cur_link_an_mode),
		     phy_modes(pl->link_config.पूर्णांकerface));

	/* Always set the carrier off */
	अगर (pl->netdev)
		netअगर_carrier_off(pl->netdev);

	/* Apply the link configuration to the MAC when starting. This allows
	 * a fixed-link to start with the correct parameters, and also
	 * ensures that we set the appropriate advertisement क्रम Serdes links.
	 *
	 * Restart स्वतःnegotiation अगर using 802.3z to ensure that the link
	 * parameters are properly negotiated.  This is necessary क्रम DSA
	 * चयनes using 802.3z negotiation to ensure they see our modes.
	 */
	phylink_mac_initial_config(pl, true);

	clear_bit(PHYLINK_DISABLE_STOPPED, &pl->phylink_disable_state);
	phylink_run_resolve(pl);

	अगर (pl->cfg_link_an_mode == MLO_AN_FIXED && pl->link_gpio) अणु
		पूर्णांक irq = gpiod_to_irq(pl->link_gpio);

		अगर (irq > 0) अणु
			अगर (!request_irq(irq, phylink_link_handler,
					 IRQF_TRIGGER_RISING |
					 IRQF_TRIGGER_FALLING,
					 "netdev link", pl))
				pl->link_irq = irq;
			अन्यथा
				irq = 0;
		पूर्ण
		अगर (irq <= 0)
			poll = true;
	पूर्ण

	चयन (pl->cfg_link_an_mode) अणु
	हाल MLO_AN_FIXED:
		poll |= pl->config->poll_fixed_state;
		अवरोध;
	हाल MLO_AN_INBAND:
		poll |= pl->config->pcs_poll;
		अगर (pl->pcs)
			poll |= pl->pcs->poll;
		अवरोध;
	पूर्ण
	अगर (poll)
		mod_समयr(&pl->link_poll, jअगरfies + HZ);
	अगर (pl->phydev)
		phy_start(pl->phydev);
	अगर (pl->sfp_bus)
		sfp_upstream_start(pl->sfp_bus);
पूर्ण
EXPORT_SYMBOL_GPL(phylink_start);

/**
 * phylink_stop() - stop a phylink instance
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 *
 * Stop the phylink instance specअगरied by @pl. This should be called from the
 * network device driver's &काष्ठा net_device_ops nकरो_stop() method.  The
 * network device's carrier state should not be changed prior to calling this
 * function.
 */
व्योम phylink_stop(काष्ठा phylink *pl)
अणु
	ASSERT_RTNL();

	अगर (pl->sfp_bus)
		sfp_upstream_stop(pl->sfp_bus);
	अगर (pl->phydev)
		phy_stop(pl->phydev);
	del_समयr_sync(&pl->link_poll);
	अगर (pl->link_irq) अणु
		मुक्त_irq(pl->link_irq, pl);
		pl->link_irq = 0;
	पूर्ण

	phylink_run_resolve_and_disable(pl, PHYLINK_DISABLE_STOPPED);
पूर्ण
EXPORT_SYMBOL_GPL(phylink_stop);

/**
 * phylink_ethtool_get_wol() - get the wake on lan parameters क्रम the PHY
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @wol: a poपूर्णांकer to &काष्ठा ethtool_wolinfo to hold the पढ़ो parameters
 *
 * Read the wake on lan parameters from the PHY attached to the phylink
 * instance specअगरied by @pl. If no PHY is currently attached, report no
 * support क्रम wake on lan.
 */
व्योम phylink_ethtool_get_wol(काष्ठा phylink *pl, काष्ठा ethtool_wolinfo *wol)
अणु
	ASSERT_RTNL();

	wol->supported = 0;
	wol->wolopts = 0;

	अगर (pl->phydev)
		phy_ethtool_get_wol(pl->phydev, wol);
पूर्ण
EXPORT_SYMBOL_GPL(phylink_ethtool_get_wol);

/**
 * phylink_ethtool_set_wol() - set wake on lan parameters
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @wol: a poपूर्णांकer to &काष्ठा ethtool_wolinfo क्रम the desired parameters
 *
 * Set the wake on lan parameters क्रम the PHY attached to the phylink
 * instance specअगरied by @pl. If no PHY is attached, वापसs %EOPNOTSUPP
 * error.
 *
 * Returns zero on success or negative त्रुटि_सं code.
 */
पूर्णांक phylink_ethtool_set_wol(काष्ठा phylink *pl, काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	ASSERT_RTNL();

	अगर (pl->phydev)
		ret = phy_ethtool_set_wol(pl->phydev, wol);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_ethtool_set_wol);

अटल व्योम phylink_merge_link_mode(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *b)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask);

	linkmode_zero(mask);
	phylink_set_port_modes(mask);

	linkmode_and(dst, dst, mask);
	linkmode_or(dst, dst, b);
पूर्ण

अटल व्योम phylink_get_ksettings(स्थिर काष्ठा phylink_link_state *state,
				  काष्ठा ethtool_link_ksettings *kset)
अणु
	phylink_merge_link_mode(kset->link_modes.advertising, state->advertising);
	linkmode_copy(kset->link_modes.lp_advertising, state->lp_advertising);
	kset->base.speed = state->speed;
	kset->base.duplex = state->duplex;
	kset->base.स्वतःneg = state->an_enabled ? AUTONEG_ENABLE :
				AUTONEG_DISABLE;
पूर्ण

/**
 * phylink_ethtool_ksettings_get() - get the current link settings
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @kset: a poपूर्णांकer to a &काष्ठा ethtool_link_ksettings to hold link settings
 *
 * Read the current link settings क्रम the phylink instance specअगरied by @pl.
 * This will be the link settings पढ़ो from the MAC, PHY or fixed link
 * settings depending on the current negotiation mode.
 */
पूर्णांक phylink_ethtool_ksettings_get(काष्ठा phylink *pl,
				  काष्ठा ethtool_link_ksettings *kset)
अणु
	काष्ठा phylink_link_state link_state;

	ASSERT_RTNL();

	अगर (pl->phydev) अणु
		phy_ethtool_ksettings_get(pl->phydev, kset);
	पूर्ण अन्यथा अणु
		kset->base.port = pl->link_port;
	पूर्ण

	linkmode_copy(kset->link_modes.supported, pl->supported);

	चयन (pl->cur_link_an_mode) अणु
	हाल MLO_AN_FIXED:
		/* We are using fixed settings. Report these as the
		 * current link settings - and note that these also
		 * represent the supported speeds/duplex/छोड़ो modes.
		 */
		phylink_get_fixed_state(pl, &link_state);
		phylink_get_ksettings(&link_state, kset);
		अवरोध;

	हाल MLO_AN_INBAND:
		/* If there is a phy attached, then use the reported
		 * settings from the phy with no modअगरication.
		 */
		अगर (pl->phydev)
			अवरोध;

		phylink_mac_pcs_get_state(pl, &link_state);

		/* The MAC is reporting the link results from its own PCS
		 * layer via in-band status. Report these as the current
		 * link settings.
		 */
		phylink_get_ksettings(&link_state, kset);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_ethtool_ksettings_get);

/**
 * phylink_ethtool_ksettings_set() - set the link settings
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @kset: a poपूर्णांकer to a &काष्ठा ethtool_link_ksettings क्रम the desired modes
 */
पूर्णांक phylink_ethtool_ksettings_set(काष्ठा phylink *pl,
				  स्थिर काष्ठा ethtool_link_ksettings *kset)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(support);
	काष्ठा phylink_link_state config;
	स्थिर काष्ठा phy_setting *s;

	ASSERT_RTNL();

	अगर (pl->phydev) अणु
		/* We can rely on phylib क्रम this update; we also करो not need
		 * to update the pl->link_config settings:
		 * - the configuration वापसed via ksettings_get() will come
		 *   from phylib whenever a PHY is present.
		 * - link_config.पूर्णांकerface will be updated by the PHY calling
		 *   back via phylink_phy_change() and a subsequent resolve.
		 * - initial link configuration क्रम PHY mode comes from the
		 *   last phy state updated via phylink_phy_change().
		 * - other configuration changes (e.g. छोड़ो modes) are
		 *   perक्रमmed directly via phylib.
		 * - अगर in in-band mode with a PHY, the link configuration
		 *   is passed on the link from the PHY, and all of
		 *   link_config.अणुspeed,duplex,an_enabled,छोड़ोपूर्ण are not used.
		 * - the only possible use would be link_config.advertising
		 *   छोड़ो modes when in 1000base-X mode with a PHY, but in
		 *   the presence of a PHY, this should not be changed as that
		 *   should be determined from the media side advertisement.
		 */
		वापस phy_ethtool_ksettings_set(pl->phydev, kset);
	पूर्ण

	linkmode_copy(support, pl->supported);
	config = pl->link_config;
	config.an_enabled = kset->base.स्वतःneg == AUTONEG_ENABLE;

	/* Mask out unsupported advertisements, and क्रमce the स्वतःneg bit */
	linkmode_and(config.advertising, kset->link_modes.advertising,
		     support);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, config.advertising,
			 config.an_enabled);

	/* FIXME: should we reject स्वतःneg अगर phy/mac करोes not support it? */
	चयन (kset->base.स्वतःneg) अणु
	हाल AUTONEG_DISABLE:
		/* Autonegotiation disabled, select a suitable speed and
		 * duplex.
		 */
		s = phy_lookup_setting(kset->base.speed, kset->base.duplex,
				       support, false);
		अगर (!s)
			वापस -EINVAL;

		/* If we have a fixed link, refuse to change link parameters.
		 * If the link parameters match, accept them but करो nothing.
		 */
		अगर (pl->cur_link_an_mode == MLO_AN_FIXED) अणु
			अगर (s->speed != pl->link_config.speed ||
			    s->duplex != pl->link_config.duplex)
				वापस -EINVAL;
			वापस 0;
		पूर्ण

		config.speed = s->speed;
		config.duplex = s->duplex;
		अवरोध;

	हाल AUTONEG_ENABLE:
		/* If we have a fixed link, allow स्वतःnegotiation (since that
		 * is our शेष हाल) but करो not allow the advertisement to
		 * be changed. If the advertisement matches, simply वापस.
		 */
		अगर (pl->cur_link_an_mode == MLO_AN_FIXED) अणु
			अगर (!linkmode_equal(config.advertising,
					    pl->link_config.advertising))
				वापस -EINVAL;
			वापस 0;
		पूर्ण

		config.speed = SPEED_UNKNOWN;
		config.duplex = DUPLEX_UNKNOWN;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* We have ruled out the हाल with a PHY attached, and the
	 * fixed-link हालs.  All that is left are in-band links.
	 */
	अगर (phylink_validate(pl, support, &config))
		वापस -EINVAL;

	/* If स्वतःnegotiation is enabled, we must have an advertisement */
	अगर (config.an_enabled && phylink_is_empty_linkmode(config.advertising))
		वापस -EINVAL;

	mutex_lock(&pl->state_mutex);
	pl->link_config.speed = config.speed;
	pl->link_config.duplex = config.duplex;
	pl->link_config.an_enabled = config.an_enabled;

	अगर (pl->link_config.पूर्णांकerface != config.पूर्णांकerface) अणु
		/* The पूर्णांकerface changed, e.g. 1000base-X <-> 2500base-X */
		/* We need to क्रमce the link करोwn, then change the पूर्णांकerface */
		अगर (pl->old_link_state) अणु
			phylink_link_करोwn(pl);
			pl->old_link_state = false;
		पूर्ण
		अगर (!test_bit(PHYLINK_DISABLE_STOPPED,
			      &pl->phylink_disable_state))
			phylink_major_config(pl, false, &config);
		pl->link_config.पूर्णांकerface = config.पूर्णांकerface;
		linkmode_copy(pl->link_config.advertising, config.advertising);
	पूर्ण अन्यथा अगर (!linkmode_equal(pl->link_config.advertising,
				   config.advertising)) अणु
		linkmode_copy(pl->link_config.advertising, config.advertising);
		phylink_change_inband_advert(pl);
	पूर्ण
	mutex_unlock(&pl->state_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_ethtool_ksettings_set);

/**
 * phylink_ethtool_nway_reset() - restart negotiation
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 *
 * Restart negotiation क्रम the phylink instance specअगरied by @pl. This will
 * cause any attached phy to restart negotiation with the link partner, and
 * अगर the MAC is in a BaseX mode, the MAC will also be requested to restart
 * negotiation.
 *
 * Returns zero on success, or negative error code.
 */
पूर्णांक phylink_ethtool_nway_reset(काष्ठा phylink *pl)
अणु
	पूर्णांक ret = 0;

	ASSERT_RTNL();

	अगर (pl->phydev)
		ret = phy_restart_aneg(pl->phydev);
	phylink_mac_pcs_an_restart(pl);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_ethtool_nway_reset);

/**
 * phylink_ethtool_get_छोड़ोparam() - get the current छोड़ो parameters
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @छोड़ो: a poपूर्णांकer to a &काष्ठा ethtool_छोड़ोparam
 */
व्योम phylink_ethtool_get_छोड़ोparam(काष्ठा phylink *pl,
				    काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	ASSERT_RTNL();

	छोड़ो->स्वतःneg = !!(pl->link_config.छोड़ो & MLO_PAUSE_AN);
	छोड़ो->rx_छोड़ो = !!(pl->link_config.छोड़ो & MLO_PAUSE_RX);
	छोड़ो->tx_छोड़ो = !!(pl->link_config.छोड़ो & MLO_PAUSE_TX);
पूर्ण
EXPORT_SYMBOL_GPL(phylink_ethtool_get_छोड़ोparam);

/**
 * phylink_ethtool_set_छोड़ोparam() - set the current छोड़ो parameters
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @छोड़ो: a poपूर्णांकer to a &काष्ठा ethtool_छोड़ोparam
 */
पूर्णांक phylink_ethtool_set_छोड़ोparam(काष्ठा phylink *pl,
				   काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा phylink_link_state *config = &pl->link_config;
	bool manual_changed;
	पूर्णांक छोड़ो_state;

	ASSERT_RTNL();

	अगर (pl->cur_link_an_mode == MLO_AN_FIXED)
		वापस -EOPNOTSUPP;

	अगर (!phylink_test(pl->supported, Pause) &&
	    !phylink_test(pl->supported, Asym_Pause))
		वापस -EOPNOTSUPP;

	अगर (!phylink_test(pl->supported, Asym_Pause) &&
	    !छोड़ो->स्वतःneg && छोड़ो->rx_छोड़ो != छोड़ो->tx_छोड़ो)
		वापस -EINVAL;

	छोड़ो_state = 0;
	अगर (छोड़ो->स्वतःneg)
		छोड़ो_state |= MLO_PAUSE_AN;
	अगर (छोड़ो->rx_छोड़ो)
		छोड़ो_state |= MLO_PAUSE_RX;
	अगर (छोड़ो->tx_छोड़ो)
		छोड़ो_state |= MLO_PAUSE_TX;

	mutex_lock(&pl->state_mutex);
	/*
	 * See the comments क्रम linkmode_set_छोड़ो(), wrt the deficiencies
	 * with the current implementation.  A solution to this issue would
	 * be:
	 * ethtool  Local device
	 *  rx  tx  Pause AsymDir
	 *  0   0   0     0
	 *  1   0   1     1
	 *  0   1   0     1
	 *  1   1   1     1
	 * and then use the ethtool rx/tx enablement status to mask the
	 * rx/tx छोड़ो resolution.
	 */
	linkmode_set_छोड़ो(config->advertising, छोड़ो->tx_छोड़ो,
			   छोड़ो->rx_छोड़ो);

	manual_changed = (config->छोड़ो ^ छोड़ो_state) & MLO_PAUSE_AN ||
			 (!(छोड़ो_state & MLO_PAUSE_AN) &&
			   (config->छोड़ो ^ छोड़ो_state) & MLO_PAUSE_TXRX_MASK);

	config->छोड़ो = छोड़ो_state;

	/* Update our in-band advertisement, triggering a renegotiation अगर
	 * the advertisement changed.
	 */
	अगर (!pl->phydev)
		phylink_change_inband_advert(pl);

	mutex_unlock(&pl->state_mutex);

	/* If we have a PHY, a change of the छोड़ो frame advertisement will
	 * cause phylib to renegotiate (अगर AN is enabled) which will in turn
	 * call our phylink_phy_change() and trigger a resolve.  Note that
	 * we can't hold our state mutex जबतक calling phy_set_asym_छोड़ो().
	 */
	अगर (pl->phydev)
		phy_set_asym_छोड़ो(pl->phydev, छोड़ो->rx_छोड़ो,
				   छोड़ो->tx_छोड़ो);

	/* If the manual छोड़ो settings changed, make sure we trigger a
	 * resolve to update their state; we can not guarantee that the
	 * link will cycle.
	 */
	अगर (manual_changed) अणु
		pl->mac_link_dropped = true;
		phylink_run_resolve(pl);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_ethtool_set_छोड़ोparam);

/**
 * phylink_get_eee_err() - पढ़ो the energy efficient ethernet error
 *   counter
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create().
 *
 * Read the Energy Efficient Ethernet error counter from the PHY associated
 * with the phylink instance specअगरied by @pl.
 *
 * Returns positive error counter value, or negative error code.
 */
पूर्णांक phylink_get_eee_err(काष्ठा phylink *pl)
अणु
	पूर्णांक ret = 0;

	ASSERT_RTNL();

	अगर (pl->phydev)
		ret = phy_get_eee_err(pl->phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_get_eee_err);

/**
 * phylink_init_eee() - init and check the EEE features
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @clk_stop_enable: allow PHY to stop receive घड़ी
 *
 * Must be called either with RTNL held or within mac_link_up()
 */
पूर्णांक phylink_init_eee(काष्ठा phylink *pl, bool clk_stop_enable)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (pl->phydev)
		ret = phy_init_eee(pl->phydev, clk_stop_enable);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_init_eee);

/**
 * phylink_ethtool_get_eee() - पढ़ो the energy efficient ethernet parameters
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @eee: a poपूर्णांकer to a &काष्ठा ethtool_eee क्रम the पढ़ो parameters
 */
पूर्णांक phylink_ethtool_get_eee(काष्ठा phylink *pl, काष्ठा ethtool_eee *eee)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	ASSERT_RTNL();

	अगर (pl->phydev)
		ret = phy_ethtool_get_eee(pl->phydev, eee);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_ethtool_get_eee);

/**
 * phylink_ethtool_set_eee() - set the energy efficient ethernet parameters
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @eee: a poपूर्णांकer to a &काष्ठा ethtool_eee क्रम the desired parameters
 */
पूर्णांक phylink_ethtool_set_eee(काष्ठा phylink *pl, काष्ठा ethtool_eee *eee)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	ASSERT_RTNL();

	अगर (pl->phydev)
		ret = phy_ethtool_set_eee(pl->phydev, eee);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_ethtool_set_eee);

/* This emulates MII रेजिस्टरs क्रम a fixed-mode phy operating as per the
 * passed in state. "aneg" defines अगर we report negotiation is possible.
 *
 * FIXME: should deal with negotiation state too.
 */
अटल पूर्णांक phylink_mii_emul_पढ़ो(अचिन्हित पूर्णांक reg,
				 काष्ठा phylink_link_state *state)
अणु
	काष्ठा fixed_phy_status fs;
	अचिन्हित दीर्घ *lpa = state->lp_advertising;
	पूर्णांक val;

	fs.link = state->link;
	fs.speed = state->speed;
	fs.duplex = state->duplex;
	fs.छोड़ो = test_bit(ETHTOOL_LINK_MODE_Pause_BIT, lpa);
	fs.asym_छोड़ो = test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, lpa);

	val = swphy_पढ़ो_reg(reg, &fs);
	अगर (reg == MII_BMSR) अणु
		अगर (!state->an_complete)
			val &= ~BMSR_ANEGCOMPLETE;
	पूर्ण
	वापस val;
पूर्ण

अटल पूर्णांक phylink_phy_पढ़ो(काष्ठा phylink *pl, अचिन्हित पूर्णांक phy_id,
			    अचिन्हित पूर्णांक reg)
अणु
	काष्ठा phy_device *phydev = pl->phydev;
	पूर्णांक prtad, devad;

	अगर (mdio_phy_id_is_c45(phy_id)) अणु
		prtad = mdio_phy_id_prtad(phy_id);
		devad = mdio_phy_id_devad(phy_id);
		devad = mdiobus_c45_addr(devad, reg);
	पूर्ण अन्यथा अगर (phydev->is_c45) अणु
		चयन (reg) अणु
		हाल MII_BMCR:
		हाल MII_BMSR:
		हाल MII_PHYSID1:
		हाल MII_PHYSID2:
			devad = __ffs(phydev->c45_ids.mmds_present);
			अवरोध;
		हाल MII_ADVERTISE:
		हाल MII_LPA:
			अगर (!(phydev->c45_ids.mmds_present & MDIO_DEVS_AN))
				वापस -EINVAL;
			devad = MDIO_MMD_AN;
			अगर (reg == MII_ADVERTISE)
				reg = MDIO_AN_ADVERTISE;
			अन्यथा
				reg = MDIO_AN_LPA;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		prtad = phy_id;
		devad = mdiobus_c45_addr(devad, reg);
	पूर्ण अन्यथा अणु
		prtad = phy_id;
		devad = reg;
	पूर्ण
	वापस mdiobus_पढ़ो(pl->phydev->mdio.bus, prtad, devad);
पूर्ण

अटल पूर्णांक phylink_phy_ग_लिखो(काष्ठा phylink *pl, अचिन्हित पूर्णांक phy_id,
			     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा phy_device *phydev = pl->phydev;
	पूर्णांक prtad, devad;

	अगर (mdio_phy_id_is_c45(phy_id)) अणु
		prtad = mdio_phy_id_prtad(phy_id);
		devad = mdio_phy_id_devad(phy_id);
		devad = mdiobus_c45_addr(devad, reg);
	पूर्ण अन्यथा अगर (phydev->is_c45) अणु
		चयन (reg) अणु
		हाल MII_BMCR:
		हाल MII_BMSR:
		हाल MII_PHYSID1:
		हाल MII_PHYSID2:
			devad = __ffs(phydev->c45_ids.mmds_present);
			अवरोध;
		हाल MII_ADVERTISE:
		हाल MII_LPA:
			अगर (!(phydev->c45_ids.mmds_present & MDIO_DEVS_AN))
				वापस -EINVAL;
			devad = MDIO_MMD_AN;
			अगर (reg == MII_ADVERTISE)
				reg = MDIO_AN_ADVERTISE;
			अन्यथा
				reg = MDIO_AN_LPA;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		prtad = phy_id;
		devad = mdiobus_c45_addr(devad, reg);
	पूर्ण अन्यथा अणु
		prtad = phy_id;
		devad = reg;
	पूर्ण

	वापस mdiobus_ग_लिखो(phydev->mdio.bus, prtad, devad, val);
पूर्ण

अटल पूर्णांक phylink_mii_पढ़ो(काष्ठा phylink *pl, अचिन्हित पूर्णांक phy_id,
			    अचिन्हित पूर्णांक reg)
अणु
	काष्ठा phylink_link_state state;
	पूर्णांक val = 0xffff;

	चयन (pl->cur_link_an_mode) अणु
	हाल MLO_AN_FIXED:
		अगर (phy_id == 0) अणु
			phylink_get_fixed_state(pl, &state);
			val = phylink_mii_emul_पढ़ो(reg, &state);
		पूर्ण
		अवरोध;

	हाल MLO_AN_PHY:
		वापस -EOPNOTSUPP;

	हाल MLO_AN_INBAND:
		अगर (phy_id == 0) अणु
			phylink_mac_pcs_get_state(pl, &state);
			val = phylink_mii_emul_पढ़ो(reg, &state);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस val & 0xffff;
पूर्ण

अटल पूर्णांक phylink_mii_ग_लिखो(काष्ठा phylink *pl, अचिन्हित पूर्णांक phy_id,
			     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	चयन (pl->cur_link_an_mode) अणु
	हाल MLO_AN_FIXED:
		अवरोध;

	हाल MLO_AN_PHY:
		वापस -EOPNOTSUPP;

	हाल MLO_AN_INBAND:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * phylink_mii_ioctl() - generic mii ioctl पूर्णांकerface
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @अगरr: a poपूर्णांकer to a &काष्ठा अगरreq क्रम socket ioctls
 * @cmd: ioctl cmd to execute
 *
 * Perक्रमm the specअगरied MII ioctl on the PHY attached to the phylink instance
 * specअगरied by @pl. If no PHY is attached, emulate the presence of the PHY.
 *
 * Returns: zero on success or negative error code.
 *
 * %SIOCGMIIPHY:
 *  पढ़ो रेजिस्टर from the current PHY.
 * %SIOCGMIIREG:
 *  पढ़ो रेजिस्टर from the specअगरied PHY.
 * %SIOCSMIIREG:
 *  set a रेजिस्टर on the specअगरied PHY.
 */
पूर्णांक phylink_mii_ioctl(काष्ठा phylink *pl, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *mii = अगर_mii(अगरr);
	पूर्णांक  ret;

	ASSERT_RTNL();

	अगर (pl->phydev) अणु
		/* PHYs only exist क्रम MLO_AN_PHY and SGMII */
		चयन (cmd) अणु
		हाल SIOCGMIIPHY:
			mii->phy_id = pl->phydev->mdio.addr;
			fallthrough;

		हाल SIOCGMIIREG:
			ret = phylink_phy_पढ़ो(pl, mii->phy_id, mii->reg_num);
			अगर (ret >= 0) अणु
				mii->val_out = ret;
				ret = 0;
			पूर्ण
			अवरोध;

		हाल SIOCSMIIREG:
			ret = phylink_phy_ग_लिखो(pl, mii->phy_id, mii->reg_num,
						mii->val_in);
			अवरोध;

		शेष:
			ret = phy_mii_ioctl(pl->phydev, अगरr, cmd);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cmd) अणु
		हाल SIOCGMIIPHY:
			mii->phy_id = 0;
			fallthrough;

		हाल SIOCGMIIREG:
			ret = phylink_mii_पढ़ो(pl, mii->phy_id, mii->reg_num);
			अगर (ret >= 0) अणु
				mii->val_out = ret;
				ret = 0;
			पूर्ण
			अवरोध;

		हाल SIOCSMIIREG:
			ret = phylink_mii_ग_लिखो(pl, mii->phy_id, mii->reg_num,
						mii->val_in);
			अवरोध;

		शेष:
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_mii_ioctl);

/**
 * phylink_speed_करोwn() - set the non-SFP PHY to lowest speed supported by both
 *   link partners
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 * @sync: perक्रमm action synchronously
 *
 * If we have a PHY that is not part of a SFP module, then set the speed
 * as described in the phy_speed_करोwn() function. Please see this function
 * क्रम a description of the @sync parameter.
 *
 * Returns zero अगर there is no PHY, otherwise as per phy_speed_करोwn().
 */
पूर्णांक phylink_speed_करोwn(काष्ठा phylink *pl, bool sync)
अणु
	पूर्णांक ret = 0;

	ASSERT_RTNL();

	अगर (!pl->sfp_bus && pl->phydev)
		ret = phy_speed_करोwn(pl->phydev, sync);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_speed_करोwn);

/**
 * phylink_speed_up() - restore the advertised speeds prior to the call to
 *   phylink_speed_करोwn()
 * @pl: a poपूर्णांकer to a &काष्ठा phylink वापसed from phylink_create()
 *
 * If we have a PHY that is not part of a SFP module, then restore the
 * PHY speeds as per phy_speed_up().
 *
 * Returns zero अगर there is no PHY, otherwise as per phy_speed_up().
 */
पूर्णांक phylink_speed_up(काष्ठा phylink *pl)
अणु
	पूर्णांक ret = 0;

	ASSERT_RTNL();

	अगर (!pl->sfp_bus && pl->phydev)
		ret = phy_speed_up(pl->phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_speed_up);

अटल व्योम phylink_sfp_attach(व्योम *upstream, काष्ठा sfp_bus *bus)
अणु
	काष्ठा phylink *pl = upstream;

	pl->netdev->sfp_bus = bus;
पूर्ण

अटल व्योम phylink_sfp_detach(व्योम *upstream, काष्ठा sfp_bus *bus)
अणु
	काष्ठा phylink *pl = upstream;

	pl->netdev->sfp_bus = शून्य;
पूर्ण

अटल पूर्णांक phylink_sfp_config(काष्ठा phylink *pl, u8 mode,
			      स्थिर अचिन्हित दीर्घ *supported,
			      स्थिर अचिन्हित दीर्घ *advertising)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(support1);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(support);
	काष्ठा phylink_link_state config;
	phy_पूर्णांकerface_t अगरace;
	bool changed;
	पूर्णांक ret;

	linkmode_copy(support, supported);

	स_रखो(&config, 0, माप(config));
	linkmode_copy(config.advertising, advertising);
	config.पूर्णांकerface = PHY_INTERFACE_MODE_NA;
	config.speed = SPEED_UNKNOWN;
	config.duplex = DUPLEX_UNKNOWN;
	config.छोड़ो = MLO_PAUSE_AN;
	config.an_enabled = pl->link_config.an_enabled;

	/* Ignore errors अगर we're expecting a PHY to attach later */
	ret = phylink_validate(pl, support, &config);
	अगर (ret) अणु
		phylink_err(pl, "validation with support %*pb failed: %d\n",
			    __ETHTOOL_LINK_MODE_MASK_NBITS, support, ret);
		वापस ret;
	पूर्ण

	अगरace = sfp_select_पूर्णांकerface(pl->sfp_bus, config.advertising);
	अगर (अगरace == PHY_INTERFACE_MODE_NA) अणु
		phylink_err(pl,
			    "selection of interface failed, advertisement %*pb\n",
			    __ETHTOOL_LINK_MODE_MASK_NBITS, config.advertising);
		वापस -EINVAL;
	पूर्ण

	config.पूर्णांकerface = अगरace;
	linkmode_copy(support1, support);
	ret = phylink_validate(pl, support1, &config);
	अगर (ret) अणु
		phylink_err(pl, "validation of %s/%s with support %*pb failed: %d\n",
			    phylink_an_mode_str(mode),
			    phy_modes(config.पूर्णांकerface),
			    __ETHTOOL_LINK_MODE_MASK_NBITS, support, ret);
		वापस ret;
	पूर्ण

	phylink_dbg(pl, "requesting link mode %s/%s with support %*pb\n",
		    phylink_an_mode_str(mode), phy_modes(config.पूर्णांकerface),
		    __ETHTOOL_LINK_MODE_MASK_NBITS, support);

	अगर (phy_पूर्णांकerface_mode_is_8023z(अगरace) && pl->phydev)
		वापस -EINVAL;

	changed = !linkmode_equal(pl->supported, support);
	अगर (changed) अणु
		linkmode_copy(pl->supported, support);
		linkmode_copy(pl->link_config.advertising, config.advertising);
	पूर्ण

	अगर (pl->cur_link_an_mode != mode ||
	    pl->link_config.पूर्णांकerface != config.पूर्णांकerface) अणु
		pl->link_config.पूर्णांकerface = config.पूर्णांकerface;
		pl->cur_link_an_mode = mode;

		changed = true;

		phylink_info(pl, "switched to %s/%s link mode\n",
			     phylink_an_mode_str(mode),
			     phy_modes(config.पूर्णांकerface));
	पूर्ण

	pl->link_port = pl->sfp_port;

	अगर (changed && !test_bit(PHYLINK_DISABLE_STOPPED,
				 &pl->phylink_disable_state))
		phylink_mac_initial_config(pl, false);

	वापस ret;
पूर्ण

अटल पूर्णांक phylink_sfp_module_insert(व्योम *upstream,
				     स्थिर काष्ठा sfp_eeprom_id *id)
अणु
	काष्ठा phylink *pl = upstream;
	अचिन्हित दीर्घ *support = pl->sfp_support;

	ASSERT_RTNL();

	linkmode_zero(support);
	sfp_parse_support(pl->sfp_bus, id, support);
	pl->sfp_port = sfp_parse_port(pl->sfp_bus, id, support);

	/* If this module may have a PHY connecting later, defer until later */
	pl->sfp_may_have_phy = sfp_may_have_phy(pl->sfp_bus, id);
	अगर (pl->sfp_may_have_phy)
		वापस 0;

	वापस phylink_sfp_config(pl, MLO_AN_INBAND, support, support);
पूर्ण

अटल पूर्णांक phylink_sfp_module_start(व्योम *upstream)
अणु
	काष्ठा phylink *pl = upstream;

	/* If this SFP module has a PHY, start the PHY now. */
	अगर (pl->phydev) अणु
		phy_start(pl->phydev);
		वापस 0;
	पूर्ण

	/* If the module may have a PHY but we didn't detect one we
	 * need to configure the MAC here.
	 */
	अगर (!pl->sfp_may_have_phy)
		वापस 0;

	वापस phylink_sfp_config(pl, MLO_AN_INBAND,
				  pl->sfp_support, pl->sfp_support);
पूर्ण

अटल व्योम phylink_sfp_module_stop(व्योम *upstream)
अणु
	काष्ठा phylink *pl = upstream;

	/* If this SFP module has a PHY, stop it. */
	अगर (pl->phydev)
		phy_stop(pl->phydev);
पूर्ण

अटल व्योम phylink_sfp_link_करोwn(व्योम *upstream)
अणु
	काष्ठा phylink *pl = upstream;

	ASSERT_RTNL();

	phylink_run_resolve_and_disable(pl, PHYLINK_DISABLE_LINK);
पूर्ण

अटल व्योम phylink_sfp_link_up(व्योम *upstream)
अणु
	काष्ठा phylink *pl = upstream;

	ASSERT_RTNL();

	clear_bit(PHYLINK_DISABLE_LINK, &pl->phylink_disable_state);
	phylink_run_resolve(pl);
पूर्ण

/* The Broadcom BCM84881 in the Methode DM7052 is unable to provide a SGMII
 * or 802.3z control word, so inband will not work.
 */
अटल bool phylink_phy_no_inband(काष्ठा phy_device *phy)
अणु
	वापस phy->is_c45 &&
		(phy->c45_ids.device_ids[1] & 0xfffffff0) == 0xae025150;
पूर्ण

अटल पूर्णांक phylink_sfp_connect_phy(व्योम *upstream, काष्ठा phy_device *phy)
अणु
	काष्ठा phylink *pl = upstream;
	phy_पूर्णांकerface_t पूर्णांकerface;
	u8 mode;
	पूर्णांक ret;

	/*
	 * This is the new way of dealing with flow control क्रम PHYs,
	 * as described by Timur Tabi in commit 529ed1275263 ("net: phy:
	 * phy drivers should not set SUPPORTED_[Asym_]Pause") except
	 * using our validate call to the MAC, we rely upon the MAC
	 * clearing the bits from both supported and advertising fields.
	 */
	phy_support_asym_छोड़ो(phy);

	अगर (phylink_phy_no_inband(phy))
		mode = MLO_AN_PHY;
	अन्यथा
		mode = MLO_AN_INBAND;

	/* Do the initial configuration */
	ret = phylink_sfp_config(pl, mode, phy->supported, phy->advertising);
	अगर (ret < 0)
		वापस ret;

	पूर्णांकerface = pl->link_config.पूर्णांकerface;
	ret = phylink_attach_phy(pl, phy, पूर्णांकerface);
	अगर (ret < 0)
		वापस ret;

	ret = phylink_bringup_phy(pl, phy, पूर्णांकerface);
	अगर (ret)
		phy_detach(phy);

	वापस ret;
पूर्ण

अटल व्योम phylink_sfp_disconnect_phy(व्योम *upstream)
अणु
	phylink_disconnect_phy(upstream);
पूर्ण

अटल स्थिर काष्ठा sfp_upstream_ops sfp_phylink_ops = अणु
	.attach = phylink_sfp_attach,
	.detach = phylink_sfp_detach,
	.module_insert = phylink_sfp_module_insert,
	.module_start = phylink_sfp_module_start,
	.module_stop = phylink_sfp_module_stop,
	.link_up = phylink_sfp_link_up,
	.link_करोwn = phylink_sfp_link_करोwn,
	.connect_phy = phylink_sfp_connect_phy,
	.disconnect_phy = phylink_sfp_disconnect_phy,
पूर्ण;

/* Helpers क्रम MAC drivers */

/**
 * phylink_helper_basex_speed() - 1000BaseX/2500BaseX helper
 * @state: a poपूर्णांकer to a &काष्ठा phylink_link_state
 *
 * Inspect the पूर्णांकerface mode, advertising mask or क्रमced speed and
 * decide whether to run at 2.5Gbit or 1Gbit appropriately, चयनing
 * the पूर्णांकerface mode to suit.  @state->पूर्णांकerface is appropriately
 * updated, and the advertising mask has the "other" baseX_Full flag
 * cleared.
 */
व्योम phylink_helper_basex_speed(काष्ठा phylink_link_state *state)
अणु
	अगर (phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface)) अणु
		bool want_2500 = state->an_enabled ?
			phylink_test(state->advertising, 2500baseX_Full) :
			state->speed == SPEED_2500;

		अगर (want_2500) अणु
			phylink_clear(state->advertising, 1000baseX_Full);
			state->पूर्णांकerface = PHY_INTERFACE_MODE_2500BASEX;
		पूर्ण अन्यथा अणु
			phylink_clear(state->advertising, 2500baseX_Full);
			state->पूर्णांकerface = PHY_INTERFACE_MODE_1000BASEX;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(phylink_helper_basex_speed);

अटल व्योम phylink_decode_c37_word(काष्ठा phylink_link_state *state,
				    uपूर्णांक16_t config_reg, पूर्णांक speed)
अणु
	bool tx_छोड़ो, rx_छोड़ो;
	पूर्णांक fd_bit;

	अगर (speed == SPEED_2500)
		fd_bit = ETHTOOL_LINK_MODE_2500baseX_Full_BIT;
	अन्यथा
		fd_bit = ETHTOOL_LINK_MODE_1000baseX_Full_BIT;

	mii_lpa_mod_linkmode_x(state->lp_advertising, config_reg, fd_bit);

	अगर (linkmode_test_bit(fd_bit, state->advertising) &&
	    linkmode_test_bit(fd_bit, state->lp_advertising)) अणु
		state->speed = speed;
		state->duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		/* negotiation failure */
		state->link = false;
	पूर्ण

	linkmode_resolve_छोड़ो(state->advertising, state->lp_advertising,
			       &tx_छोड़ो, &rx_छोड़ो);

	अगर (tx_छोड़ो)
		state->छोड़ो |= MLO_PAUSE_TX;
	अगर (rx_छोड़ो)
		state->छोड़ो |= MLO_PAUSE_RX;
पूर्ण

अटल व्योम phylink_decode_sgmii_word(काष्ठा phylink_link_state *state,
				      uपूर्णांक16_t config_reg)
अणु
	अगर (!(config_reg & LPA_SGMII_LINK)) अणु
		state->link = false;
		वापस;
	पूर्ण

	चयन (config_reg & LPA_SGMII_SPD_MASK) अणु
	हाल LPA_SGMII_10:
		state->speed = SPEED_10;
		अवरोध;
	हाल LPA_SGMII_100:
		state->speed = SPEED_100;
		अवरोध;
	हाल LPA_SGMII_1000:
		state->speed = SPEED_1000;
		अवरोध;
	शेष:
		state->link = false;
		वापस;
	पूर्ण
	अगर (config_reg & LPA_SGMII_FULL_DUPLEX)
		state->duplex = DUPLEX_FULL;
	अन्यथा
		state->duplex = DUPLEX_HALF;
पूर्ण

/**
 * phylink_decode_usxgmii_word() - decode the USXGMII word from a MAC PCS
 * @state: a poपूर्णांकer to a काष्ठा phylink_link_state.
 * @lpa: a 16 bit value which stores the USXGMII स्वतः-negotiation word
 *
 * Helper क्रम MAC PCS supporting the USXGMII protocol and the स्वतः-negotiation
 * code word.  Decode the USXGMII code word and populate the corresponding fields
 * (speed, duplex) पूर्णांकo the phylink_link_state काष्ठाure.
 */
व्योम phylink_decode_usxgmii_word(काष्ठा phylink_link_state *state,
				 uपूर्णांक16_t lpa)
अणु
	चयन (lpa & MDIO_USXGMII_SPD_MASK) अणु
	हाल MDIO_USXGMII_10:
		state->speed = SPEED_10;
		अवरोध;
	हाल MDIO_USXGMII_100:
		state->speed = SPEED_100;
		अवरोध;
	हाल MDIO_USXGMII_1000:
		state->speed = SPEED_1000;
		अवरोध;
	हाल MDIO_USXGMII_2500:
		state->speed = SPEED_2500;
		अवरोध;
	हाल MDIO_USXGMII_5000:
		state->speed = SPEED_5000;
		अवरोध;
	हाल MDIO_USXGMII_10G:
		state->speed = SPEED_10000;
		अवरोध;
	शेष:
		state->link = false;
		वापस;
	पूर्ण

	अगर (lpa & MDIO_USXGMII_FULL_DUPLEX)
		state->duplex = DUPLEX_FULL;
	अन्यथा
		state->duplex = DUPLEX_HALF;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_decode_usxgmii_word);

/**
 * phylink_mii_c22_pcs_get_state() - पढ़ो the MAC PCS state
 * @pcs: a poपूर्णांकer to a &काष्ठा mdio_device.
 * @state: a poपूर्णांकer to a &काष्ठा phylink_link_state.
 *
 * Helper क्रम MAC PCS supporting the 802.3 clause 22 रेजिस्टर set क्रम
 * clause 37 negotiation and/or SGMII control.
 *
 * Read the MAC PCS state from the MII device configured in @config and
 * parse the Clause 37 or Cisco SGMII link partner negotiation word पूर्णांकo
 * the phylink @state काष्ठाure. This is suitable to be directly plugged
 * पूर्णांकo the mac_pcs_get_state() member of the काष्ठा phylink_mac_ops
 * काष्ठाure.
 */
व्योम phylink_mii_c22_pcs_get_state(काष्ठा mdio_device *pcs,
				   काष्ठा phylink_link_state *state)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक addr = pcs->addr;
	पूर्णांक bmsr, lpa;

	bmsr = mdiobus_पढ़ो(bus, addr, MII_BMSR);
	lpa = mdiobus_पढ़ो(bus, addr, MII_LPA);
	अगर (bmsr < 0 || lpa < 0) अणु
		state->link = false;
		वापस;
	पूर्ण

	state->link = !!(bmsr & BMSR_LSTATUS);
	state->an_complete = !!(bmsr & BMSR_ANEGCOMPLETE);
	अगर (!state->link)
		वापस;

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_1000BASEX:
		phylink_decode_c37_word(state, lpa, SPEED_1000);
		अवरोध;

	हाल PHY_INTERFACE_MODE_2500BASEX:
		phylink_decode_c37_word(state, lpa, SPEED_2500);
		अवरोध;

	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_QSGMII:
		phylink_decode_sgmii_word(state, lpa);
		अवरोध;

	शेष:
		state->link = false;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(phylink_mii_c22_pcs_get_state);

/**
 * phylink_mii_c22_pcs_set_advertisement() - configure the clause 37 PCS
 *	advertisement
 * @pcs: a poपूर्णांकer to a &काष्ठा mdio_device.
 * @पूर्णांकerface: the PHY पूर्णांकerface mode being configured
 * @advertising: the ethtool advertisement mask
 *
 * Helper क्रम MAC PCS supporting the 802.3 clause 22 रेजिस्टर set क्रम
 * clause 37 negotiation and/or SGMII control.
 *
 * Configure the clause 37 PCS advertisement as specअगरied by @state. This
 * करोes not trigger a renegotiation; phylink will करो that via the
 * mac_an_restart() method of the काष्ठा phylink_mac_ops काष्ठाure.
 *
 * Returns negative error code on failure to configure the advertisement,
 * zero अगर no change has been made, or one अगर the advertisement has changed.
 */
पूर्णांक phylink_mii_c22_pcs_set_advertisement(काष्ठा mdio_device *pcs,
					  phy_पूर्णांकerface_t पूर्णांकerface,
					  स्थिर अचिन्हित दीर्घ *advertising)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक addr = pcs->addr;
	पूर्णांक val, ret;
	u16 adv;

	चयन (पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_2500BASEX:
		adv = ADVERTISE_1000XFULL;
		अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
				      advertising))
			adv |= ADVERTISE_1000XPAUSE;
		अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
				      advertising))
			adv |= ADVERTISE_1000XPSE_ASYM;

		val = mdiobus_पढ़ो(bus, addr, MII_ADVERTISE);
		अगर (val < 0)
			वापस val;

		अगर (val == adv)
			वापस 0;

		ret = mdiobus_ग_लिखो(bus, addr, MII_ADVERTISE, adv);
		अगर (ret < 0)
			वापस ret;

		वापस 1;

	हाल PHY_INTERFACE_MODE_SGMII:
		val = mdiobus_पढ़ो(bus, addr, MII_ADVERTISE);
		अगर (val < 0)
			वापस val;

		अगर (val == 0x0001)
			वापस 0;

		ret = mdiobus_ग_लिखो(bus, addr, MII_ADVERTISE, 0x0001);
		अगर (ret < 0)
			वापस ret;

		वापस 1;

	शेष:
		/* Nothing to करो क्रम other modes */
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(phylink_mii_c22_pcs_set_advertisement);

/**
 * phylink_mii_c22_pcs_config() - configure clause 22 PCS
 * @pcs: a poपूर्णांकer to a &काष्ठा mdio_device.
 * @mode: link स्वतःnegotiation mode
 * @पूर्णांकerface: the PHY पूर्णांकerface mode being configured
 * @advertising: the ethtool advertisement mask
 *
 * Configure a Clause 22 PCS PHY with the appropriate negotiation
 * parameters क्रम the @mode, @पूर्णांकerface and @advertising parameters.
 * Returns negative error number on failure, zero अगर the advertisement
 * has not changed, or positive अगर there is a change.
 */
पूर्णांक phylink_mii_c22_pcs_config(काष्ठा mdio_device *pcs, अचिन्हित पूर्णांक mode,
			       phy_पूर्णांकerface_t पूर्णांकerface,
			       स्थिर अचिन्हित दीर्घ *advertising)
अणु
	bool changed;
	u16 bmcr;
	पूर्णांक ret;

	ret = phylink_mii_c22_pcs_set_advertisement(pcs, पूर्णांकerface,
						    advertising);
	अगर (ret < 0)
		वापस ret;

	changed = ret > 0;

	/* Ensure ISOLATE bit is disabled */
	bmcr = mode == MLO_AN_INBAND ? BMCR_ANENABLE : 0;
	ret = mdiobus_modअगरy(pcs->bus, pcs->addr, MII_BMCR,
			     BMCR_ANENABLE | BMCR_ISOLATE, bmcr);
	अगर (ret < 0)
		वापस ret;

	वापस changed ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(phylink_mii_c22_pcs_config);

/**
 * phylink_mii_c22_pcs_an_restart() - restart 802.3z स्वतःnegotiation
 * @pcs: a poपूर्णांकer to a &काष्ठा mdio_device.
 *
 * Helper क्रम MAC PCS supporting the 802.3 clause 22 रेजिस्टर set क्रम
 * clause 37 negotiation.
 *
 * Restart the clause 37 negotiation with the link partner. This is
 * suitable to be directly plugged पूर्णांकo the mac_pcs_get_state() member
 * of the काष्ठा phylink_mac_ops काष्ठाure.
 */
व्योम phylink_mii_c22_pcs_an_restart(काष्ठा mdio_device *pcs)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक val, addr = pcs->addr;

	val = mdiobus_पढ़ो(bus, addr, MII_BMCR);
	अगर (val >= 0) अणु
		val |= BMCR_ANRESTART;

		mdiobus_ग_लिखो(bus, addr, MII_BMCR, val);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(phylink_mii_c22_pcs_an_restart);

व्योम phylink_mii_c45_pcs_get_state(काष्ठा mdio_device *pcs,
				   काष्ठा phylink_link_state *state)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक addr = pcs->addr;
	पूर्णांक stat;

	stat = mdiobus_c45_पढ़ो(bus, addr, MDIO_MMD_PCS, MDIO_STAT1);
	अगर (stat < 0) अणु
		state->link = false;
		वापस;
	पूर्ण

	state->link = !!(stat & MDIO_STAT1_LSTATUS);
	अगर (!state->link)
		वापस;

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_10GBASER:
		state->speed = SPEED_10000;
		state->duplex = DUPLEX_FULL;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(phylink_mii_c45_pcs_get_state);

MODULE_LICENSE("GPL v2");
