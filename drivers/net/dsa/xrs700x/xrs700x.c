<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 NovaTech LLC
 * George McCollister <george.mccollister@gmail.com>
 */

#समावेश <net/dsa.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/of_device.h>
#समावेश <linux/netdev_features.h>
#समावेश <linux/अगर_hsr.h>
#समावेश "xrs700x.h"
#समावेश "xrs700x_reg.h"

#घोषणा XRS700X_MIB_INTERVAL msecs_to_jअगरfies(3000)

#घोषणा XRS7000X_SUPPORTED_HSR_FEATURES \
	(NETIF_F_HW_HSR_TAG_INS | NETIF_F_HW_HSR_TAG_RM | \
	 NETIF_F_HW_HSR_FWD | NETIF_F_HW_HSR_DUP)

#घोषणा XRS7003E_ID	0x100
#घोषणा XRS7003F_ID	0x101
#घोषणा XRS7004E_ID	0x200
#घोषणा XRS7004F_ID	0x201

स्थिर काष्ठा xrs700x_info xrs7003e_info = अणुXRS7003E_ID, "XRS7003E", 3पूर्ण;
EXPORT_SYMBOL(xrs7003e_info);

स्थिर काष्ठा xrs700x_info xrs7003f_info = अणुXRS7003F_ID, "XRS7003F", 3पूर्ण;
EXPORT_SYMBOL(xrs7003f_info);

स्थिर काष्ठा xrs700x_info xrs7004e_info = अणुXRS7004E_ID, "XRS7004E", 4पूर्ण;
EXPORT_SYMBOL(xrs7004e_info);

स्थिर काष्ठा xrs700x_info xrs7004f_info = अणुXRS7004F_ID, "XRS7004F", 4पूर्ण;
EXPORT_SYMBOL(xrs7004f_info);

काष्ठा xrs700x_regfield अणु
	काष्ठा reg_field rf;
	काष्ठा regmap_field **rmf;
पूर्ण;

काष्ठा xrs700x_mib अणु
	अचिन्हित पूर्णांक offset;
	स्थिर अक्षर *name;
	पूर्णांक stats64_offset;
पूर्ण;

#घोषणा XRS700X_MIB_ETHTOOL_ONLY(o, n) अणुo, n, -1पूर्ण
#घोषणा XRS700X_MIB(o, n, m) अणुo, n, दुरत्व(काष्ठा rtnl_link_stats64, m)पूर्ण

अटल स्थिर काष्ठा xrs700x_mib xrs700x_mibs[] = अणु
	XRS700X_MIB(XRS_RX_GOOD_OCTETS_L, "rx_good_octets", rx_bytes),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_BAD_OCTETS_L, "rx_bad_octets"),
	XRS700X_MIB(XRS_RX_UNICAST_L, "rx_unicast", rx_packets),
	XRS700X_MIB(XRS_RX_BROADCAST_L, "rx_broadcast", rx_packets),
	XRS700X_MIB(XRS_RX_MULTICAST_L, "rx_multicast", multicast),
	XRS700X_MIB(XRS_RX_UNDERSIZE_L, "rx_undersize", rx_length_errors),
	XRS700X_MIB(XRS_RX_FRAGMENTS_L, "rx_fragments", rx_length_errors),
	XRS700X_MIB(XRS_RX_OVERSIZE_L, "rx_oversize", rx_length_errors),
	XRS700X_MIB(XRS_RX_JABBER_L, "rx_jabber", rx_length_errors),
	XRS700X_MIB(XRS_RX_ERR_L, "rx_err", rx_errors),
	XRS700X_MIB(XRS_RX_CRC_L, "rx_crc", rx_crc_errors),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_64_L, "rx_64"),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_65_127_L, "rx_65_127"),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_128_255_L, "rx_128_255"),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_256_511_L, "rx_256_511"),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_512_1023_L, "rx_512_1023"),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_1024_1536_L, "rx_1024_1536"),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_HSR_PRP_L, "rx_hsr_prp"),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_WRONGLAN_L, "rx_wronglan"),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_RX_DUPLICATE_L, "rx_duplicate"),
	XRS700X_MIB(XRS_TX_OCTETS_L, "tx_octets", tx_bytes),
	XRS700X_MIB(XRS_TX_UNICAST_L, "tx_unicast", tx_packets),
	XRS700X_MIB(XRS_TX_BROADCAST_L, "tx_broadcast", tx_packets),
	XRS700X_MIB(XRS_TX_MULTICAST_L, "tx_multicast", tx_packets),
	XRS700X_MIB_ETHTOOL_ONLY(XRS_TX_HSR_PRP_L, "tx_hsr_prp"),
	XRS700X_MIB(XRS_PRIQ_DROP_L, "priq_drop", tx_dropped),
	XRS700X_MIB(XRS_EARLY_DROP_L, "early_drop", tx_dropped),
पूर्ण;

अटल व्योम xrs700x_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
				u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(xrs700x_mibs); i++) अणु
		strscpy(data, xrs700x_mibs[i].name, ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल पूर्णांक xrs700x_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	अगर (sset != ETH_SS_STATS)
		वापस -EOPNOTSUPP;

	वापस ARRAY_SIZE(xrs700x_mibs);
पूर्ण

अटल व्योम xrs700x_पढ़ो_port_counters(काष्ठा xrs700x *priv, पूर्णांक port)
अणु
	काष्ठा xrs700x_port *p = &priv->ports[port];
	काष्ठा rtnl_link_stats64 stats;
	पूर्णांक i;

	स_रखो(&stats, 0, माप(stats));

	mutex_lock(&p->mib_mutex);

	/* Capture counter values */
	regmap_ग_लिखो(priv->regmap, XRS_CNT_CTRL(port), 1);

	क्रम (i = 0; i < ARRAY_SIZE(xrs700x_mibs); i++) अणु
		अचिन्हित पूर्णांक high = 0, low = 0, reg;

		reg = xrs700x_mibs[i].offset + XRS_PORT_OFFSET * port;
		regmap_पढ़ो(priv->regmap, reg, &low);
		regmap_पढ़ो(priv->regmap, reg + 2, &high);

		p->mib_data[i] += (high << 16) | low;

		अगर (xrs700x_mibs[i].stats64_offset >= 0) अणु
			u8 *s = (u8 *)&stats + xrs700x_mibs[i].stats64_offset;
			*(u64 *)s += p->mib_data[i];
		पूर्ण
	पूर्ण

	/* multicast must be added to rx_packets (which alपढ़ोy includes
	 * unicast and broadcast)
	 */
	stats.rx_packets += stats.multicast;

	u64_stats_update_begin(&p->syncp);
	p->stats64 = stats;
	u64_stats_update_end(&p->syncp);

	mutex_unlock(&p->mib_mutex);
पूर्ण

अटल व्योम xrs700x_mib_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xrs700x *priv = container_of(work, काष्ठा xrs700x,
					    mib_work.work);
	पूर्णांक i;

	क्रम (i = 0; i < priv->ds->num_ports; i++)
		xrs700x_पढ़ो_port_counters(priv, i);

	schedule_delayed_work(&priv->mib_work, XRS700X_MIB_INTERVAL);
पूर्ण

अटल व्योम xrs700x_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      u64 *data)
अणु
	काष्ठा xrs700x *priv = ds->priv;
	काष्ठा xrs700x_port *p = &priv->ports[port];

	xrs700x_पढ़ो_port_counters(priv, port);

	mutex_lock(&p->mib_mutex);
	स_नकल(data, p->mib_data, माप(*data) * ARRAY_SIZE(xrs700x_mibs));
	mutex_unlock(&p->mib_mutex);
पूर्ण

अटल व्योम xrs700x_get_stats64(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा rtnl_link_stats64 *s)
अणु
	काष्ठा xrs700x *priv = ds->priv;
	काष्ठा xrs700x_port *p = &priv->ports[port];
	अचिन्हित पूर्णांक start;

	करो अणु
		start = u64_stats_fetch_begin(&p->syncp);
		*s = p->stats64;
	पूर्ण जबतक (u64_stats_fetch_retry(&p->syncp, start));
पूर्ण

अटल पूर्णांक xrs700x_setup_regmap_range(काष्ठा xrs700x *priv)
अणु
	काष्ठा xrs700x_regfield regfields[] = अणु
		अणु
			.rf = REG_FIELD_ID(XRS_PORT_STATE(0), 0, 1,
					   priv->ds->num_ports,
					   XRS_PORT_OFFSET),
			.rmf = &priv->ps_क्रमward
		पूर्ण,
		अणु
			.rf = REG_FIELD_ID(XRS_PORT_STATE(0), 2, 3,
					   priv->ds->num_ports,
					   XRS_PORT_OFFSET),
			.rmf = &priv->ps_management
		पूर्ण,
		अणु
			.rf = REG_FIELD_ID(XRS_PORT_STATE(0), 4, 9,
					   priv->ds->num_ports,
					   XRS_PORT_OFFSET),
			.rmf = &priv->ps_sel_speed
		पूर्ण,
		अणु
			.rf = REG_FIELD_ID(XRS_PORT_STATE(0), 10, 11,
					   priv->ds->num_ports,
					   XRS_PORT_OFFSET),
			.rmf = &priv->ps_cur_speed
		पूर्ण
	पूर्ण;
	पूर्णांक i = 0;

	क्रम (; i < ARRAY_SIZE(regfields); i++) अणु
		*regfields[i].rmf = devm_regmap_field_alloc(priv->dev,
							    priv->regmap,
							    regfields[i].rf);
		अगर (IS_ERR(*regfields[i].rmf))
			वापस PTR_ERR(*regfields[i].rmf);
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत dsa_tag_protocol xrs700x_get_tag_protocol(काष्ठा dsa_चयन *ds,
						      पूर्णांक port,
						      क्रमागत dsa_tag_protocol m)
अणु
	वापस DSA_TAG_PROTO_XRS700X;
पूर्ण

अटल पूर्णांक xrs700x_reset(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा xrs700x *priv = ds->priv;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(priv->regmap, XRS_GENERAL, XRS_GENERAL_RESET);
	अगर (ret)
		जाओ error;

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, XRS_GENERAL,
				       val, !(val & XRS_GENERAL_RESET),
				       10, 1000);
error:
	अगर (ret) अणु
		dev_err_ratelimited(priv->dev, "error resetting switch: %d\n",
				    ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xrs700x_port_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       u8 state)
अणु
	काष्ठा xrs700x *priv = ds->priv;
	अचिन्हित पूर्णांक bpdus = 1;
	अचिन्हित पूर्णांक val;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		bpdus = 0;
		fallthrough;
	हाल BR_STATE_BLOCKING:
	हाल BR_STATE_LISTENING:
		val = XRS_PORT_DISABLED;
		अवरोध;
	हाल BR_STATE_LEARNING:
		val = XRS_PORT_LEARNING;
		अवरोध;
	हाल BR_STATE_FORWARDING:
		val = XRS_PORT_FORWARDING;
		अवरोध;
	शेष:
		dev_err(ds->dev, "invalid STP state: %d\n", state);
		वापस;
	पूर्ण

	regmap_fields_ग_लिखो(priv->ps_क्रमward, port, val);

	/* Enable/disable inbound policy added by xrs700x_port_add_bpdu_ipf()
	 * which allows BPDU क्रमwarding to the CPU port when the front facing
	 * port is in disabled/learning state.
	 */
	regmap_update_bits(priv->regmap, XRS_ETH_ADDR_CFG(port, 0), 1, bpdus);

	dev_dbg_ratelimited(priv->dev, "%s - port: %d, state: %u, val: 0x%x\n",
			    __func__, port, state, val);
पूर्ण

/* Add an inbound policy filter which matches the BPDU destination MAC
 * and क्रमwards to the CPU port. Leave the policy disabled, it will be
 * enabled as needed.
 */
अटल पूर्णांक xrs700x_port_add_bpdu_ipf(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा xrs700x *priv = ds->priv;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक i = 0;
	पूर्णांक ret;

	/* Compare all 48 bits of the destination MAC address. */
	ret = regmap_ग_लिखो(priv->regmap, XRS_ETH_ADDR_CFG(port, 0), 48 << 2);
	अगर (ret)
		वापस ret;

	/* match BPDU destination 01:80:c2:00:00:00 */
	क्रम (i = 0; i < माप(eth_stp_addr); i += 2) अणु
		ret = regmap_ग_लिखो(priv->regmap, XRS_ETH_ADDR_0(port, 0) + i,
				   eth_stp_addr[i] |
				   (eth_stp_addr[i + 1] << 8));
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Mirror BPDU to CPU port */
	क्रम (i = 0; i < ds->num_ports; i++) अणु
		अगर (dsa_is_cpu_port(ds, i))
			val |= BIT(i);
	पूर्ण

	ret = regmap_ग_लिखो(priv->regmap, XRS_ETH_ADDR_FWD_MIRROR(port, 0), val);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(priv->regmap, XRS_ETH_ADDR_FWD_ALLOW(port, 0), 0);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक xrs700x_port_setup(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	bool cpu_port = dsa_is_cpu_port(ds, port);
	काष्ठा xrs700x *priv = ds->priv;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret, i;

	xrs700x_port_stp_state_set(ds, port, BR_STATE_DISABLED);

	/* Disable क्रमwarding to non-CPU ports */
	क्रम (i = 0; i < ds->num_ports; i++) अणु
		अगर (!dsa_is_cpu_port(ds, i))
			val |= BIT(i);
	पूर्ण

	/* 1 = Disable क्रमwarding to the port */
	ret = regmap_ग_लिखो(priv->regmap, XRS_PORT_FWD_MASK(port), val);
	अगर (ret)
		वापस ret;

	val = cpu_port ? XRS_PORT_MODE_MANAGEMENT : XRS_PORT_MODE_NORMAL;
	ret = regmap_fields_ग_लिखो(priv->ps_management, port, val);
	अगर (ret)
		वापस ret;

	अगर (!cpu_port) अणु
		ret = xrs700x_port_add_bpdu_ipf(ds, port);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xrs700x_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा xrs700x *priv = ds->priv;
	पूर्णांक ret, i;

	ret = xrs700x_reset(ds);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ds->num_ports; i++) अणु
		ret = xrs700x_port_setup(ds, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	schedule_delayed_work(&priv->mib_work, XRS700X_MIB_INTERVAL);

	वापस 0;
पूर्ण

अटल व्योम xrs700x_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा xrs700x *priv = ds->priv;

	cancel_delayed_work_sync(&priv->mib_work);
पूर्ण

अटल व्योम xrs700x_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     अचिन्हित दीर्घ *supported,
				     काष्ठा phylink_link_state *state)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	चयन (port) अणु
	हाल 0:
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 3:
		phylink_set(mask, 1000baseT_Full);
		अवरोध;
	शेष:
		biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
		dev_err(ds->dev, "Unsupported port: %i\n", port);
		वापस;
	पूर्ण

	phylink_set_port_modes(mask);

	/* The चयन only supports full duplex. */
	phylink_set(mask, 10baseT_Full);
	phylink_set(mask, 100baseT_Full);

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल व्योम xrs700x_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
				अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
				काष्ठा phy_device *phydev,
				पूर्णांक speed, पूर्णांक duplex,
				bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा xrs700x *priv = ds->priv;
	अचिन्हित पूर्णांक val;

	चयन (speed) अणु
	हाल SPEED_1000:
		val = XRS_PORT_SPEED_1000;
		अवरोध;
	हाल SPEED_100:
		val = XRS_PORT_SPEED_100;
		अवरोध;
	हाल SPEED_10:
		val = XRS_PORT_SPEED_10;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	regmap_fields_ग_लिखो(priv->ps_sel_speed, port, val);

	dev_dbg_ratelimited(priv->dev, "%s: port: %d mode: %u speed: %u\n",
			    __func__, port, mode, speed);
पूर्ण

अटल पूर्णांक xrs700x_bridge_common(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा net_device *bridge, bool join)
अणु
	अचिन्हित पूर्णांक i, cpu_mask = 0, mask = 0;
	काष्ठा xrs700x *priv = ds->priv;
	पूर्णांक ret;

	क्रम (i = 0; i < ds->num_ports; i++) अणु
		अगर (dsa_is_cpu_port(ds, i))
			जारी;

		cpu_mask |= BIT(i);

		अगर (dsa_to_port(ds, i)->bridge_dev == bridge)
			जारी;

		mask |= BIT(i);
	पूर्ण

	क्रम (i = 0; i < ds->num_ports; i++) अणु
		अगर (dsa_to_port(ds, i)->bridge_dev != bridge)
			जारी;

		/* 1 = Disable क्रमwarding to the port */
		ret = regmap_ग_लिखो(priv->regmap, XRS_PORT_FWD_MASK(i), mask);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!join) अणु
		ret = regmap_ग_लिखो(priv->regmap, XRS_PORT_FWD_MASK(port),
				   cpu_mask);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xrs700x_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा net_device *bridge)
अणु
	वापस xrs700x_bridge_common(ds, port, bridge, true);
पूर्ण

अटल व्योम xrs700x_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा net_device *bridge)
अणु
	xrs700x_bridge_common(ds, port, bridge, false);
पूर्ण

अटल पूर्णांक xrs700x_hsr_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    काष्ठा net_device *hsr)
अणु
	अचिन्हित पूर्णांक val = XRS_HSR_CFG_HSR_PRP;
	काष्ठा dsa_port *partner = शून्य, *dp;
	काष्ठा xrs700x *priv = ds->priv;
	काष्ठा net_device *slave;
	पूर्णांक ret, i, hsr_pair[2];
	क्रमागत hsr_version ver;

	ret = hsr_get_version(hsr, &ver);
	अगर (ret)
		वापस ret;

	/* Only ports 1 and 2 can be HSR/PRP redundant ports. */
	अगर (port != 1 && port != 2)
		वापस -EOPNOTSUPP;

	अगर (ver == HSR_V1)
		val |= XRS_HSR_CFG_HSR;
	अन्यथा अगर (ver == PRP_V1)
		val |= XRS_HSR_CFG_PRP;
	अन्यथा
		वापस -EOPNOTSUPP;

	dsa_hsr_क्रमeach_port(dp, ds, hsr) अणु
		अगर (dp->index != port) अणु
			partner = dp;
			अवरोध;
		पूर्ण
	पूर्ण

	/* We can't enable redundancy on the चयन until both
	 * redundant ports have चिन्हित up.
	 */
	अगर (!partner)
		वापस 0;

	regmap_fields_ग_लिखो(priv->ps_क्रमward, partner->index,
			    XRS_PORT_DISABLED);
	regmap_fields_ग_लिखो(priv->ps_क्रमward, port, XRS_PORT_DISABLED);

	regmap_ग_लिखो(priv->regmap, XRS_HSR_CFG(partner->index),
		     val | XRS_HSR_CFG_LANID_A);
	regmap_ग_लिखो(priv->regmap, XRS_HSR_CFG(port),
		     val | XRS_HSR_CFG_LANID_B);

	/* Clear bits क्रम both redundant ports (HSR only) and the CPU port to
	 * enable क्रमwarding.
	 */
	val = GENMASK(ds->num_ports - 1, 0);
	अगर (ver == HSR_V1) अणु
		val &= ~BIT(partner->index);
		val &= ~BIT(port);
	पूर्ण
	val &= ~BIT(dsa_upstream_port(ds, port));
	regmap_ग_लिखो(priv->regmap, XRS_PORT_FWD_MASK(partner->index), val);
	regmap_ग_लिखो(priv->regmap, XRS_PORT_FWD_MASK(port), val);

	regmap_fields_ग_लिखो(priv->ps_क्रमward, partner->index,
			    XRS_PORT_FORWARDING);
	regmap_fields_ग_लिखो(priv->ps_क्रमward, port, XRS_PORT_FORWARDING);

	hsr_pair[0] = port;
	hsr_pair[1] = partner->index;
	क्रम (i = 0; i < ARRAY_SIZE(hsr_pair); i++) अणु
		slave = dsa_to_port(ds, hsr_pair[i])->slave;
		slave->features |= XRS7000X_SUPPORTED_HSR_FEATURES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xrs700x_hsr_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा net_device *hsr)
अणु
	काष्ठा dsa_port *partner = शून्य, *dp;
	काष्ठा xrs700x *priv = ds->priv;
	काष्ठा net_device *slave;
	पूर्णांक i, hsr_pair[2];
	अचिन्हित पूर्णांक val;

	dsa_hsr_क्रमeach_port(dp, ds, hsr) अणु
		अगर (dp->index != port) अणु
			partner = dp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!partner)
		वापस 0;

	regmap_fields_ग_लिखो(priv->ps_क्रमward, partner->index,
			    XRS_PORT_DISABLED);
	regmap_fields_ग_लिखो(priv->ps_क्रमward, port, XRS_PORT_DISABLED);

	regmap_ग_लिखो(priv->regmap, XRS_HSR_CFG(partner->index), 0);
	regmap_ग_लिखो(priv->regmap, XRS_HSR_CFG(port), 0);

	/* Clear bit क्रम the CPU port to enable क्रमwarding. */
	val = GENMASK(ds->num_ports - 1, 0);
	val &= ~BIT(dsa_upstream_port(ds, port));
	regmap_ग_लिखो(priv->regmap, XRS_PORT_FWD_MASK(partner->index), val);
	regmap_ग_लिखो(priv->regmap, XRS_PORT_FWD_MASK(port), val);

	regmap_fields_ग_लिखो(priv->ps_क्रमward, partner->index,
			    XRS_PORT_FORWARDING);
	regmap_fields_ग_लिखो(priv->ps_क्रमward, port, XRS_PORT_FORWARDING);

	hsr_pair[0] = port;
	hsr_pair[1] = partner->index;
	क्रम (i = 0; i < ARRAY_SIZE(hsr_pair); i++) अणु
		slave = dsa_to_port(ds, hsr_pair[i])->slave;
		slave->features &= ~XRS7000X_SUPPORTED_HSR_FEATURES;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops xrs700x_ops = अणु
	.get_tag_protocol	= xrs700x_get_tag_protocol,
	.setup			= xrs700x_setup,
	.tearकरोwn		= xrs700x_tearकरोwn,
	.port_stp_state_set	= xrs700x_port_stp_state_set,
	.phylink_validate	= xrs700x_phylink_validate,
	.phylink_mac_link_up	= xrs700x_mac_link_up,
	.get_strings		= xrs700x_get_strings,
	.get_sset_count		= xrs700x_get_sset_count,
	.get_ethtool_stats	= xrs700x_get_ethtool_stats,
	.get_stats64		= xrs700x_get_stats64,
	.port_bridge_join	= xrs700x_bridge_join,
	.port_bridge_leave	= xrs700x_bridge_leave,
	.port_hsr_join		= xrs700x_hsr_join,
	.port_hsr_leave		= xrs700x_hsr_leave,
पूर्ण;

अटल पूर्णांक xrs700x_detect(काष्ठा xrs700x *priv)
अणु
	स्थिर काष्ठा xrs700x_info *info;
	अचिन्हित पूर्णांक id;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->regmap, XRS_DEV_ID0, &id);
	अगर (ret) अणु
		dev_err(priv->dev, "error %d while reading switch id.\n",
			ret);
		वापस ret;
	पूर्ण

	info = of_device_get_match_data(priv->dev);
	अगर (!info)
		वापस -EINVAL;

	अगर (info->id == id) अणु
		priv->ds->num_ports = info->num_ports;
		dev_info(priv->dev, "%s detected.\n", info->name);
		वापस 0;
	पूर्ण

	dev_err(priv->dev, "expected switch id 0x%x but found 0x%x.\n",
		info->id, id);

	वापस -ENODEV;
पूर्ण

काष्ठा xrs700x *xrs700x_चयन_alloc(काष्ठा device *base, व्योम *devpriv)
अणु
	काष्ठा dsa_चयन *ds;
	काष्ठा xrs700x *priv;

	ds = devm_kzalloc(base, माप(*ds), GFP_KERNEL);
	अगर (!ds)
		वापस शून्य;

	ds->dev = base;

	priv = devm_kzalloc(base, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;

	INIT_DELAYED_WORK(&priv->mib_work, xrs700x_mib_work);

	ds->ops = &xrs700x_ops;
	ds->priv = priv;
	priv->dev = base;

	priv->ds = ds;
	priv->priv = devpriv;

	वापस priv;
पूर्ण
EXPORT_SYMBOL(xrs700x_चयन_alloc);

अटल पूर्णांक xrs700x_alloc_port_mib(काष्ठा xrs700x *priv, पूर्णांक port)
अणु
	काष्ठा xrs700x_port *p = &priv->ports[port];

	p->mib_data = devm_kसुस्मृति(priv->dev, ARRAY_SIZE(xrs700x_mibs),
				   माप(*p->mib_data), GFP_KERNEL);
	अगर (!p->mib_data)
		वापस -ENOMEM;

	mutex_init(&p->mib_mutex);
	u64_stats_init(&p->syncp);

	वापस 0;
पूर्ण

पूर्णांक xrs700x_चयन_रेजिस्टर(काष्ठा xrs700x *priv)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	ret = xrs700x_detect(priv);
	अगर (ret)
		वापस ret;

	ret = xrs700x_setup_regmap_range(priv);
	अगर (ret)
		वापस ret;

	priv->ports = devm_kसुस्मृति(priv->dev, priv->ds->num_ports,
				   माप(*priv->ports), GFP_KERNEL);
	अगर (!priv->ports)
		वापस -ENOMEM;

	क्रम (i = 0; i < priv->ds->num_ports; i++) अणु
		ret = xrs700x_alloc_port_mib(priv, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस dsa_रेजिस्टर_चयन(priv->ds);
पूर्ण
EXPORT_SYMBOL(xrs700x_चयन_रेजिस्टर);

व्योम xrs700x_चयन_हटाओ(काष्ठा xrs700x *priv)
अणु
	dsa_unरेजिस्टर_चयन(priv->ds);
पूर्ण
EXPORT_SYMBOL(xrs700x_चयन_हटाओ);

MODULE_AUTHOR("George McCollister <george.mccollister@gmail.com>");
MODULE_DESCRIPTION("Arrow SpeedChips XRS700x DSA driver");
MODULE_LICENSE("GPL v2");
