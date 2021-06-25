<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2019 NXP */

#समावेश "dpaa2-eth.h"
#समावेश "dpaa2-mac.h"

#घोषणा phylink_to_dpaa2_mac(config) \
	container_of((config), काष्ठा dpaa2_mac, phylink_config)

अटल पूर्णांक phy_mode(क्रमागत dpmac_eth_अगर eth_अगर, phy_पूर्णांकerface_t *अगर_mode)
अणु
	*अगर_mode = PHY_INTERFACE_MODE_NA;

	चयन (eth_अगर) अणु
	हाल DPMAC_ETH_IF_RGMII:
		*अगर_mode = PHY_INTERFACE_MODE_RGMII;
		अवरोध;
	हाल DPMAC_ETH_IF_USXGMII:
		*अगर_mode = PHY_INTERFACE_MODE_USXGMII;
		अवरोध;
	हाल DPMAC_ETH_IF_QSGMII:
		*अगर_mode = PHY_INTERFACE_MODE_QSGMII;
		अवरोध;
	हाल DPMAC_ETH_IF_SGMII:
		*अगर_mode = PHY_INTERFACE_MODE_SGMII;
		अवरोध;
	हाल DPMAC_ETH_IF_XFI:
		*अगर_mode = PHY_INTERFACE_MODE_10GBASER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Caller must call of_node_put on the वापसed value */
अटल काष्ठा device_node *dpaa2_mac_get_node(u16 dpmac_id)
अणु
	काष्ठा device_node *dpmacs, *dpmac = शून्य;
	u32 id;
	पूर्णांक err;

	dpmacs = of_find_node_by_name(शून्य, "dpmacs");
	अगर (!dpmacs)
		वापस शून्य;

	जबतक ((dpmac = of_get_next_child(dpmacs, dpmac)) != शून्य) अणु
		err = of_property_पढ़ो_u32(dpmac, "reg", &id);
		अगर (err)
			जारी;
		अगर (id == dpmac_id)
			अवरोध;
	पूर्ण

	of_node_put(dpmacs);

	वापस dpmac;
पूर्ण

अटल पूर्णांक dpaa2_mac_get_अगर_mode(काष्ठा device_node *node,
				 काष्ठा dpmac_attr attr)
अणु
	phy_पूर्णांकerface_t अगर_mode;
	पूर्णांक err;

	err = of_get_phy_mode(node, &अगर_mode);
	अगर (!err)
		वापस अगर_mode;

	err = phy_mode(attr.eth_अगर, &अगर_mode);
	अगर (!err)
		वापस अगर_mode;

	वापस err;
पूर्ण

अटल bool dpaa2_mac_phy_mode_mismatch(काष्ठा dpaa2_mac *mac,
					phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	चयन (पूर्णांकerface) अणु
	/* We can चयन between SGMII and 1000BASE-X at runसमय with
	 * pcs-lynx
	 */
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
		अगर (mac->pcs &&
		    (mac->अगर_mode == PHY_INTERFACE_MODE_SGMII ||
		     mac->अगर_mode == PHY_INTERFACE_MODE_1000BASEX))
			वापस false;
		वापस पूर्णांकerface != mac->अगर_mode;

	हाल PHY_INTERFACE_MODE_10GBASER:
	हाल PHY_INTERFACE_MODE_USXGMII:
	हाल PHY_INTERFACE_MODE_QSGMII:
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		वापस (पूर्णांकerface != mac->अगर_mode);
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम dpaa2_mac_validate(काष्ठा phylink_config *config,
			       अचिन्हित दीर्घ *supported,
			       काष्ठा phylink_link_state *state)
अणु
	काष्ठा dpaa2_mac *mac = phylink_to_dpaa2_mac(config);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
	    dpaa2_mac_phy_mode_mismatch(mac, state->पूर्णांकerface)) अणु
		जाओ empty_set;
	पूर्ण

	phylink_set_port_modes(mask);
	phylink_set(mask, Autoneg);
	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_NA:
	हाल PHY_INTERFACE_MODE_10GBASER:
	हाल PHY_INTERFACE_MODE_USXGMII:
		phylink_set(mask, 10000baseT_Full);
		अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_10GBASER)
			अवरोध;
		phylink_set(mask, 5000baseT_Full);
		phylink_set(mask, 2500baseT_Full);
		fallthrough;
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_QSGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		phylink_set(mask, 1000baseX_Full);
		phylink_set(mask, 1000baseT_Full);
		अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_1000BASEX)
			अवरोध;
		phylink_set(mask, 100baseT_Full);
		phylink_set(mask, 10baseT_Full);
		अवरोध;
	शेष:
		जाओ empty_set;
	पूर्ण

	linkmode_and(supported, supported, mask);
	linkmode_and(state->advertising, state->advertising, mask);

	वापस;

empty_set:
	linkmode_zero(supported);
पूर्ण

अटल व्योम dpaa2_mac_config(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			     स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा dpaa2_mac *mac = phylink_to_dpaa2_mac(config);
	काष्ठा dpmac_link_state *dpmac_state = &mac->state;
	पूर्णांक err;

	अगर (state->an_enabled)
		dpmac_state->options |= DPMAC_LINK_OPT_AUTONEG;
	अन्यथा
		dpmac_state->options &= ~DPMAC_LINK_OPT_AUTONEG;

	err = dpmac_set_link_state(mac->mc_io, 0,
				   mac->mc_dev->mc_handle, dpmac_state);
	अगर (err)
		netdev_err(mac->net_dev, "%s: dpmac_set_link_state() = %d\n",
			   __func__, err);
पूर्ण

अटल व्योम dpaa2_mac_link_up(काष्ठा phylink_config *config,
			      काष्ठा phy_device *phy,
			      अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
			      पूर्णांक speed, पूर्णांक duplex,
			      bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा dpaa2_mac *mac = phylink_to_dpaa2_mac(config);
	काष्ठा dpmac_link_state *dpmac_state = &mac->state;
	पूर्णांक err;

	dpmac_state->up = 1;

	dpmac_state->rate = speed;

	अगर (duplex == DUPLEX_HALF)
		dpmac_state->options |= DPMAC_LINK_OPT_HALF_DUPLEX;
	अन्यथा अगर (duplex == DUPLEX_FULL)
		dpmac_state->options &= ~DPMAC_LINK_OPT_HALF_DUPLEX;

	अगर (rx_छोड़ो)
		dpmac_state->options |= DPMAC_LINK_OPT_PAUSE;
	अन्यथा
		dpmac_state->options &= ~DPMAC_LINK_OPT_PAUSE;

	अगर (rx_छोड़ो ^ tx_छोड़ो)
		dpmac_state->options |= DPMAC_LINK_OPT_ASYM_PAUSE;
	अन्यथा
		dpmac_state->options &= ~DPMAC_LINK_OPT_ASYM_PAUSE;

	err = dpmac_set_link_state(mac->mc_io, 0,
				   mac->mc_dev->mc_handle, dpmac_state);
	अगर (err)
		netdev_err(mac->net_dev, "%s: dpmac_set_link_state() = %d\n",
			   __func__, err);
पूर्ण

अटल व्योम dpaa2_mac_link_करोwn(काष्ठा phylink_config *config,
				अचिन्हित पूर्णांक mode,
				phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा dpaa2_mac *mac = phylink_to_dpaa2_mac(config);
	काष्ठा dpmac_link_state *dpmac_state = &mac->state;
	पूर्णांक err;

	dpmac_state->up = 0;
	err = dpmac_set_link_state(mac->mc_io, 0,
				   mac->mc_dev->mc_handle, dpmac_state);
	अगर (err)
		netdev_err(mac->net_dev, "dpmac_set_link_state() = %d\n", err);
पूर्ण

अटल स्थिर काष्ठा phylink_mac_ops dpaa2_mac_phylink_ops = अणु
	.validate = dpaa2_mac_validate,
	.mac_config = dpaa2_mac_config,
	.mac_link_up = dpaa2_mac_link_up,
	.mac_link_करोwn = dpaa2_mac_link_करोwn,
पूर्ण;

अटल पूर्णांक dpaa2_pcs_create(काष्ठा dpaa2_mac *mac,
			    काष्ठा device_node *dpmac_node, पूर्णांक id)
अणु
	काष्ठा mdio_device *mdiodev;
	काष्ठा device_node *node;

	node = of_parse_phandle(dpmac_node, "pcs-handle", 0);
	अगर (!node) अणु
		/* करो not error out on old DTS files */
		netdev_warn(mac->net_dev, "pcs-handle node not found\n");
		वापस 0;
	पूर्ण

	अगर (!of_device_is_available(node)) अणु
		netdev_err(mac->net_dev, "pcs-handle node not available\n");
		of_node_put(node);
		वापस -ENODEV;
	पूर्ण

	mdiodev = of_mdio_find_device(node);
	of_node_put(node);
	अगर (!mdiodev)
		वापस -EPROBE_DEFER;

	mac->pcs = lynx_pcs_create(mdiodev);
	अगर (!mac->pcs) अणु
		netdev_err(mac->net_dev, "lynx_pcs_create() failed\n");
		put_device(&mdiodev->dev);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpaa2_pcs_destroy(काष्ठा dpaa2_mac *mac)
अणु
	काष्ठा lynx_pcs *pcs = mac->pcs;

	अगर (pcs) अणु
		काष्ठा device *dev = &pcs->mdio->dev;
		lynx_pcs_destroy(pcs);
		put_device(dev);
		mac->pcs = शून्य;
	पूर्ण
पूर्ण

पूर्णांक dpaa2_mac_connect(काष्ठा dpaa2_mac *mac)
अणु
	काष्ठा net_device *net_dev = mac->net_dev;
	काष्ठा device_node *dpmac_node;
	काष्ठा phylink *phylink;
	पूर्णांक err;

	mac->अगर_link_type = mac->attr.link_type;

	dpmac_node = dpaa2_mac_get_node(mac->attr.id);
	अगर (!dpmac_node) अणु
		netdev_err(net_dev, "No dpmac@%d node found.\n", mac->attr.id);
		वापस -ENODEV;
	पूर्ण

	err = dpaa2_mac_get_अगर_mode(dpmac_node, mac->attr);
	अगर (err < 0) अणु
		err = -EINVAL;
		जाओ err_put_node;
	पूर्ण
	mac->अगर_mode = err;

	/* The MAC करोes not have the capability to add RGMII delays so
	 * error out अगर the पूर्णांकerface mode requests them and there is no PHY
	 * to act upon them
	 */
	अगर (of_phy_is_fixed_link(dpmac_node) &&
	    (mac->अगर_mode == PHY_INTERFACE_MODE_RGMII_ID ||
	     mac->अगर_mode == PHY_INTERFACE_MODE_RGMII_RXID ||
	     mac->अगर_mode == PHY_INTERFACE_MODE_RGMII_TXID)) अणु
		netdev_err(net_dev, "RGMII delay not supported\n");
		err = -EINVAL;
		जाओ err_put_node;
	पूर्ण

	अगर ((mac->attr.link_type == DPMAC_LINK_TYPE_PHY &&
	     mac->attr.eth_अगर != DPMAC_ETH_IF_RGMII) ||
	    mac->attr.link_type == DPMAC_LINK_TYPE_BACKPLANE) अणु
		err = dpaa2_pcs_create(mac, dpmac_node, mac->attr.id);
		अगर (err)
			जाओ err_put_node;
	पूर्ण

	mac->phylink_config.dev = &net_dev->dev;
	mac->phylink_config.type = PHYLINK_NETDEV;

	phylink = phylink_create(&mac->phylink_config,
				 of_fwnode_handle(dpmac_node), mac->अगर_mode,
				 &dpaa2_mac_phylink_ops);
	अगर (IS_ERR(phylink)) अणु
		err = PTR_ERR(phylink);
		जाओ err_pcs_destroy;
	पूर्ण
	mac->phylink = phylink;

	अगर (mac->pcs)
		phylink_set_pcs(mac->phylink, &mac->pcs->pcs);

	err = phylink_of_phy_connect(mac->phylink, dpmac_node, 0);
	अगर (err) अणु
		netdev_err(net_dev, "phylink_of_phy_connect() = %d\n", err);
		जाओ err_phylink_destroy;
	पूर्ण

	of_node_put(dpmac_node);

	वापस 0;

err_phylink_destroy:
	phylink_destroy(mac->phylink);
err_pcs_destroy:
	dpaa2_pcs_destroy(mac);
err_put_node:
	of_node_put(dpmac_node);

	वापस err;
पूर्ण

व्योम dpaa2_mac_disconnect(काष्ठा dpaa2_mac *mac)
अणु
	अगर (!mac->phylink)
		वापस;

	phylink_disconnect_phy(mac->phylink);
	phylink_destroy(mac->phylink);
	dpaa2_pcs_destroy(mac);
पूर्ण

पूर्णांक dpaa2_mac_खोलो(काष्ठा dpaa2_mac *mac)
अणु
	काष्ठा fsl_mc_device *dpmac_dev = mac->mc_dev;
	काष्ठा net_device *net_dev = mac->net_dev;
	पूर्णांक err;

	err = dpmac_खोलो(mac->mc_io, 0, dpmac_dev->obj_desc.id,
			 &dpmac_dev->mc_handle);
	अगर (err || !dpmac_dev->mc_handle) अणु
		netdev_err(net_dev, "dpmac_open() = %d\n", err);
		वापस -ENODEV;
	पूर्ण

	err = dpmac_get_attributes(mac->mc_io, 0, dpmac_dev->mc_handle,
				   &mac->attr);
	अगर (err) अणु
		netdev_err(net_dev, "dpmac_get_attributes() = %d\n", err);
		जाओ err_बंद_dpmac;
	पूर्ण

	वापस 0;

err_बंद_dpmac:
	dpmac_बंद(mac->mc_io, 0, dpmac_dev->mc_handle);
	वापस err;
पूर्ण

व्योम dpaa2_mac_बंद(काष्ठा dpaa2_mac *mac)
अणु
	काष्ठा fsl_mc_device *dpmac_dev = mac->mc_dev;

	dpmac_बंद(mac->mc_io, 0, dpmac_dev->mc_handle);
पूर्ण

अटल अक्षर dpaa2_mac_ethtool_stats[][ETH_GSTRING_LEN] = अणु
	[DPMAC_CNT_ING_ALL_FRAME]		= "[mac] rx all frames",
	[DPMAC_CNT_ING_GOOD_FRAME]		= "[mac] rx frames ok",
	[DPMAC_CNT_ING_ERR_FRAME]		= "[mac] rx frame errors",
	[DPMAC_CNT_ING_FRAME_DISCARD]		= "[mac] rx frame discards",
	[DPMAC_CNT_ING_UCAST_FRAME]		= "[mac] rx u-cast",
	[DPMAC_CNT_ING_BCAST_FRAME]		= "[mac] rx b-cast",
	[DPMAC_CNT_ING_MCAST_FRAME]		= "[mac] rx m-cast",
	[DPMAC_CNT_ING_FRAME_64]		= "[mac] rx 64 bytes",
	[DPMAC_CNT_ING_FRAME_127]		= "[mac] rx 65-127 bytes",
	[DPMAC_CNT_ING_FRAME_255]		= "[mac] rx 128-255 bytes",
	[DPMAC_CNT_ING_FRAME_511]		= "[mac] rx 256-511 bytes",
	[DPMAC_CNT_ING_FRAME_1023]		= "[mac] rx 512-1023 bytes",
	[DPMAC_CNT_ING_FRAME_1518]		= "[mac] rx 1024-1518 bytes",
	[DPMAC_CNT_ING_FRAME_1519_MAX]		= "[mac] rx 1519-max bytes",
	[DPMAC_CNT_ING_FRAG]			= "[mac] rx frags",
	[DPMAC_CNT_ING_JABBER]			= "[mac] rx jabber",
	[DPMAC_CNT_ING_ALIGN_ERR]		= "[mac] rx align errors",
	[DPMAC_CNT_ING_OVERSIZED]		= "[mac] rx oversized",
	[DPMAC_CNT_ING_VALID_PAUSE_FRAME]	= "[mac] rx pause",
	[DPMAC_CNT_ING_BYTE]			= "[mac] rx bytes",
	[DPMAC_CNT_EGR_GOOD_FRAME]		= "[mac] tx frames ok",
	[DPMAC_CNT_EGR_UCAST_FRAME]		= "[mac] tx u-cast",
	[DPMAC_CNT_EGR_MCAST_FRAME]		= "[mac] tx m-cast",
	[DPMAC_CNT_EGR_BCAST_FRAME]		= "[mac] tx b-cast",
	[DPMAC_CNT_EGR_ERR_FRAME]		= "[mac] tx frame errors",
	[DPMAC_CNT_EGR_UNDERSIZED]		= "[mac] tx undersized",
	[DPMAC_CNT_EGR_VALID_PAUSE_FRAME]	= "[mac] tx b-pause",
	[DPMAC_CNT_EGR_BYTE]			= "[mac] tx bytes",
पूर्ण;

#घोषणा DPAA2_MAC_NUM_STATS	ARRAY_SIZE(dpaa2_mac_ethtool_stats)

पूर्णांक dpaa2_mac_get_sset_count(व्योम)
अणु
	वापस DPAA2_MAC_NUM_STATS;
पूर्ण

व्योम dpaa2_mac_get_strings(u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	क्रम (i = 0; i < DPAA2_MAC_NUM_STATS; i++) अणु
		strlcpy(p, dpaa2_mac_ethtool_stats[i], ETH_GSTRING_LEN);
		p += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

व्योम dpaa2_mac_get_ethtool_stats(काष्ठा dpaa2_mac *mac, u64 *data)
अणु
	काष्ठा fsl_mc_device *dpmac_dev = mac->mc_dev;
	पूर्णांक i, err;
	u64 value;

	क्रम (i = 0; i < DPAA2_MAC_NUM_STATS; i++) अणु
		err = dpmac_get_counter(mac->mc_io, 0, dpmac_dev->mc_handle,
					i, &value);
		अगर (err) अणु
			netdev_err_once(mac->net_dev,
					"dpmac_get_counter error %d\n", err);
			*(data + i) = U64_MAX;
			जारी;
		पूर्ण
		*(data + i) = value;
	पूर्ण
पूर्ण
