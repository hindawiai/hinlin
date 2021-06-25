<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2016 NXP
 * Copyright 2020 NXP
 */

#समावेश <linux/net_tstamp.h>
#समावेश <linux/nospec.h>

#समावेश "dpni.h"	/* DPNI_LINK_OPT_* */
#समावेश "dpaa2-eth.h"

/* To be kept in sync with DPNI statistics */
अटल अक्षर dpaa2_ethtool_stats[][ETH_GSTRING_LEN] = अणु
	"[hw] rx frames",
	"[hw] rx bytes",
	"[hw] rx mcast frames",
	"[hw] rx mcast bytes",
	"[hw] rx bcast frames",
	"[hw] rx bcast bytes",
	"[hw] tx frames",
	"[hw] tx bytes",
	"[hw] tx mcast frames",
	"[hw] tx mcast bytes",
	"[hw] tx bcast frames",
	"[hw] tx bcast bytes",
	"[hw] rx filtered frames",
	"[hw] rx discarded frames",
	"[hw] rx nobuffer discards",
	"[hw] tx discarded frames",
	"[hw] tx confirmed frames",
	"[hw] tx dequeued bytes",
	"[hw] tx dequeued frames",
	"[hw] tx rejected bytes",
	"[hw] tx rejected frames",
	"[hw] tx pending frames",
पूर्ण;

#घोषणा DPAA2_ETH_NUM_STATS	ARRAY_SIZE(dpaa2_ethtool_stats)

अटल अक्षर dpaa2_ethtool_extras[][ETH_GSTRING_LEN] = अणु
	/* per-cpu stats */
	"[drv] tx conf frames",
	"[drv] tx conf bytes",
	"[drv] tx sg frames",
	"[drv] tx sg bytes",
	"[drv] rx sg frames",
	"[drv] rx sg bytes",
	"[drv] tx converted sg frames",
	"[drv] tx converted sg bytes",
	"[drv] enqueue portal busy",
	/* Channel stats */
	"[drv] dequeue portal busy",
	"[drv] channel pull errors",
	"[drv] cdan",
	"[drv] xdp drop",
	"[drv] xdp tx",
	"[drv] xdp tx errors",
	"[drv] xdp redirect",
	/* FQ stats */
	"[qbman] rx pending frames",
	"[qbman] rx pending bytes",
	"[qbman] tx conf pending frames",
	"[qbman] tx conf pending bytes",
	"[qbman] buffer count",
पूर्ण;

#घोषणा DPAA2_ETH_NUM_EXTRA_STATS	ARRAY_SIZE(dpaa2_ethtool_extras)

अटल व्योम dpaa2_eth_get_drvinfo(काष्ठा net_device *net_dev,
				  काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);

	strlcpy(drvinfo->driver, KBUILD_MODNAME, माप(drvinfo->driver));

	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%u.%u", priv->dpni_ver_major, priv->dpni_ver_minor);

	strlcpy(drvinfo->bus_info, dev_name(net_dev->dev.parent->parent),
		माप(drvinfo->bus_info));
पूर्ण

अटल पूर्णांक dpaa2_eth_nway_reset(काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);

	अगर (dpaa2_eth_is_type_phy(priv))
		वापस phylink_ethtool_nway_reset(priv->mac->phylink);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
dpaa2_eth_get_link_ksettings(काष्ठा net_device *net_dev,
			     काष्ठा ethtool_link_ksettings *link_settings)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);

	अगर (dpaa2_eth_is_type_phy(priv))
		वापस phylink_ethtool_ksettings_get(priv->mac->phylink,
						     link_settings);

	link_settings->base.स्वतःneg = AUTONEG_DISABLE;
	अगर (!(priv->link_state.options & DPNI_LINK_OPT_HALF_DUPLEX))
		link_settings->base.duplex = DUPLEX_FULL;
	link_settings->base.speed = priv->link_state.rate;

	वापस 0;
पूर्ण

अटल पूर्णांक
dpaa2_eth_set_link_ksettings(काष्ठा net_device *net_dev,
			     स्थिर काष्ठा ethtool_link_ksettings *link_settings)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);

	अगर (!dpaa2_eth_is_type_phy(priv))
		वापस -ENOTSUPP;

	वापस phylink_ethtool_ksettings_set(priv->mac->phylink, link_settings);
पूर्ण

अटल व्योम dpaa2_eth_get_छोड़ोparam(काष्ठा net_device *net_dev,
				     काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	u64 link_options = priv->link_state.options;

	अगर (dpaa2_eth_is_type_phy(priv)) अणु
		phylink_ethtool_get_छोड़ोparam(priv->mac->phylink, छोड़ो);
		वापस;
	पूर्ण

	छोड़ो->rx_छोड़ो = dpaa2_eth_rx_छोड़ो_enabled(link_options);
	छोड़ो->tx_छोड़ो = dpaa2_eth_tx_छोड़ो_enabled(link_options);
	छोड़ो->स्वतःneg = AUTONEG_DISABLE;
पूर्ण

अटल पूर्णांक dpaa2_eth_set_छोड़ोparam(काष्ठा net_device *net_dev,
				    काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा dpni_link_cfg cfg = अणु0पूर्ण;
	पूर्णांक err;

	अगर (!dpaa2_eth_has_छोड़ो_support(priv)) अणु
		netdev_info(net_dev, "No pause frame support for DPNI version < %d.%d\n",
			    DPNI_PAUSE_VER_MAJOR, DPNI_PAUSE_VER_MINOR);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (dpaa2_eth_is_type_phy(priv))
		वापस phylink_ethtool_set_छोड़ोparam(priv->mac->phylink,
						      छोड़ो);
	अगर (छोड़ो->स्वतःneg)
		वापस -EOPNOTSUPP;

	cfg.rate = priv->link_state.rate;
	cfg.options = priv->link_state.options;
	अगर (छोड़ो->rx_छोड़ो)
		cfg.options |= DPNI_LINK_OPT_PAUSE;
	अन्यथा
		cfg.options &= ~DPNI_LINK_OPT_PAUSE;
	अगर (!!छोड़ो->rx_छोड़ो ^ !!छोड़ो->tx_छोड़ो)
		cfg.options |= DPNI_LINK_OPT_ASYM_PAUSE;
	अन्यथा
		cfg.options &= ~DPNI_LINK_OPT_ASYM_PAUSE;

	अगर (cfg.options == priv->link_state.options)
		वापस 0;

	err = dpni_set_link_cfg(priv->mc_io, 0, priv->mc_token, &cfg);
	अगर (err) अणु
		netdev_err(net_dev, "dpni_set_link_state failed\n");
		वापस err;
	पूर्ण

	priv->link_state.options = cfg.options;

	वापस 0;
पूर्ण

अटल व्योम dpaa2_eth_get_strings(काष्ठा net_device *netdev, u32 stringset,
				  u8 *data)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(netdev);
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < DPAA2_ETH_NUM_STATS; i++) अणु
			strlcpy(p, dpaa2_ethtool_stats[i], ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < DPAA2_ETH_NUM_EXTRA_STATS; i++) अणु
			strlcpy(p, dpaa2_ethtool_extras[i], ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अगर (dpaa2_eth_has_mac(priv))
			dpaa2_mac_get_strings(p);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dpaa2_eth_get_sset_count(काष्ठा net_device *net_dev, पूर्णांक sset)
अणु
	पूर्णांक num_ss_stats = DPAA2_ETH_NUM_STATS + DPAA2_ETH_NUM_EXTRA_STATS;
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS: /* ethtool_get_stats(), ethtool_get_drvinfo() */
		अगर (dpaa2_eth_has_mac(priv))
			num_ss_stats += dpaa2_mac_get_sset_count();
		वापस num_ss_stats;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/** Fill in hardware counters, as वापसed by MC.
 */
अटल व्योम dpaa2_eth_get_ethtool_stats(काष्ठा net_device *net_dev,
					काष्ठा ethtool_stats *stats,
					u64 *data)
अणु
	पूर्णांक i = 0;
	पूर्णांक j, k, err;
	पूर्णांक num_cnt;
	जोड़ dpni_statistics dpni_stats;
	u32 fcnt, bcnt;
	u32 fcnt_rx_total = 0, fcnt_tx_total = 0;
	u32 bcnt_rx_total = 0, bcnt_tx_total = 0;
	u32 buf_cnt;
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा dpaa2_eth_drv_stats *extras;
	काष्ठा dpaa2_eth_ch_stats *ch_stats;
	पूर्णांक dpni_stats_page_size[DPNI_STATISTICS_CNT] = अणु
		माप(dpni_stats.page_0),
		माप(dpni_stats.page_1),
		माप(dpni_stats.page_2),
		माप(dpni_stats.page_3),
		माप(dpni_stats.page_4),
		माप(dpni_stats.page_5),
		माप(dpni_stats.page_6),
	पूर्ण;

	स_रखो(data, 0,
	       माप(u64) * (DPAA2_ETH_NUM_STATS + DPAA2_ETH_NUM_EXTRA_STATS));

	/* Prपूर्णांक standard counters, from DPNI statistics */
	क्रम (j = 0; j <= 6; j++) अणु
		/* We're not पूर्णांकerested in pages 4 & 5 क्रम now */
		अगर (j == 4 || j == 5)
			जारी;
		err = dpni_get_statistics(priv->mc_io, 0, priv->mc_token,
					  j, &dpni_stats);
		अगर (err == -EINVAL)
			/* Older firmware versions करोn't support all pages */
			स_रखो(&dpni_stats, 0, माप(dpni_stats));
		अन्यथा अगर (err)
			netdev_warn(net_dev, "dpni_get_stats(%d) failed\n", j);

		num_cnt = dpni_stats_page_size[j] / माप(u64);
		क्रम (k = 0; k < num_cnt; k++)
			*(data + i++) = dpni_stats.raw.counter[k];
	पूर्ण

	/* Prपूर्णांक per-cpu extra stats */
	क्रम_each_online_cpu(k) अणु
		extras = per_cpu_ptr(priv->percpu_extras, k);
		क्रम (j = 0; j < माप(*extras) / माप(__u64); j++)
			*((__u64 *)data + i + j) += *((__u64 *)extras + j);
	पूर्ण
	i += j;

	/* Per-channel stats */
	क्रम (k = 0; k < priv->num_channels; k++) अणु
		ch_stats = &priv->channel[k]->stats;
		क्रम (j = 0; j < माप(*ch_stats) / माप(__u64) - 1; j++)
			*((__u64 *)data + i + j) += *((__u64 *)ch_stats + j);
	पूर्ण
	i += j;

	क्रम (j = 0; j < priv->num_fqs; j++) अणु
		/* Prपूर्णांक FQ instantaneous counts */
		err = dpaa2_io_query_fq_count(शून्य, priv->fq[j].fqid,
					      &fcnt, &bcnt);
		अगर (err) अणु
			netdev_warn(net_dev, "FQ query error %d", err);
			वापस;
		पूर्ण

		अगर (priv->fq[j].type == DPAA2_TX_CONF_FQ) अणु
			fcnt_tx_total += fcnt;
			bcnt_tx_total += bcnt;
		पूर्ण अन्यथा अणु
			fcnt_rx_total += fcnt;
			bcnt_rx_total += bcnt;
		पूर्ण
	पूर्ण

	*(data + i++) = fcnt_rx_total;
	*(data + i++) = bcnt_rx_total;
	*(data + i++) = fcnt_tx_total;
	*(data + i++) = bcnt_tx_total;

	err = dpaa2_io_query_bp_count(शून्य, priv->bpid, &buf_cnt);
	अगर (err) अणु
		netdev_warn(net_dev, "Buffer count query error %d\n", err);
		वापस;
	पूर्ण
	*(data + i++) = buf_cnt;

	अगर (dpaa2_eth_has_mac(priv))
		dpaa2_mac_get_ethtool_stats(priv->mac, data + i);
पूर्ण

अटल पूर्णांक dpaa2_eth_prep_eth_rule(काष्ठा ethhdr *eth_value, काष्ठा ethhdr *eth_mask,
				   व्योम *key, व्योम *mask, u64 *fields)
अणु
	पूर्णांक off;

	अगर (eth_mask->h_proto) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_TYPE);
		*(__be16 *)(key + off) = eth_value->h_proto;
		*(__be16 *)(mask + off) = eth_mask->h_proto;
		*fields |= DPAA2_ETH_DIST_ETHTYPE;
	पूर्ण

	अगर (!is_zero_ether_addr(eth_mask->h_source)) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_SA);
		ether_addr_copy(key + off, eth_value->h_source);
		ether_addr_copy(mask + off, eth_mask->h_source);
		*fields |= DPAA2_ETH_DIST_ETHSRC;
	पूर्ण

	अगर (!is_zero_ether_addr(eth_mask->h_dest)) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_DA);
		ether_addr_copy(key + off, eth_value->h_dest);
		ether_addr_copy(mask + off, eth_mask->h_dest);
		*fields |= DPAA2_ETH_DIST_ETHDST;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_prep_uip_rule(काष्ठा ethtool_usrip4_spec *uip_value,
				   काष्ठा ethtool_usrip4_spec *uip_mask,
				   व्योम *key, व्योम *mask, u64 *fields)
अणु
	पूर्णांक off;
	u32 पंचांगp_value, पंचांगp_mask;

	अगर (uip_mask->tos || uip_mask->ip_ver)
		वापस -EOPNOTSUPP;

	अगर (uip_mask->ip4src) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_IP, NH_FLD_IP_SRC);
		*(__be32 *)(key + off) = uip_value->ip4src;
		*(__be32 *)(mask + off) = uip_mask->ip4src;
		*fields |= DPAA2_ETH_DIST_IPSRC;
	पूर्ण

	अगर (uip_mask->ip4dst) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_IP, NH_FLD_IP_DST);
		*(__be32 *)(key + off) = uip_value->ip4dst;
		*(__be32 *)(mask + off) = uip_mask->ip4dst;
		*fields |= DPAA2_ETH_DIST_IPDST;
	पूर्ण

	अगर (uip_mask->proto) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_IP, NH_FLD_IP_PROTO);
		*(u8 *)(key + off) = uip_value->proto;
		*(u8 *)(mask + off) = uip_mask->proto;
		*fields |= DPAA2_ETH_DIST_IPPROTO;
	पूर्ण

	अगर (uip_mask->l4_4_bytes) अणु
		पंचांगp_value = be32_to_cpu(uip_value->l4_4_bytes);
		पंचांगp_mask = be32_to_cpu(uip_mask->l4_4_bytes);

		off = dpaa2_eth_cls_fld_off(NET_PROT_UDP, NH_FLD_UDP_PORT_SRC);
		*(__be16 *)(key + off) = htons(पंचांगp_value >> 16);
		*(__be16 *)(mask + off) = htons(पंचांगp_mask >> 16);
		*fields |= DPAA2_ETH_DIST_L4SRC;

		off = dpaa2_eth_cls_fld_off(NET_PROT_UDP, NH_FLD_UDP_PORT_DST);
		*(__be16 *)(key + off) = htons(पंचांगp_value & 0xFFFF);
		*(__be16 *)(mask + off) = htons(पंचांगp_mask & 0xFFFF);
		*fields |= DPAA2_ETH_DIST_L4DST;
	पूर्ण

	/* Only apply the rule क्रम IPv4 frames */
	off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_TYPE);
	*(__be16 *)(key + off) = htons(ETH_P_IP);
	*(__be16 *)(mask + off) = htons(0xFFFF);
	*fields |= DPAA2_ETH_DIST_ETHTYPE;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_prep_l4_rule(काष्ठा ethtool_tcpip4_spec *l4_value,
				  काष्ठा ethtool_tcpip4_spec *l4_mask,
				  व्योम *key, व्योम *mask, u8 l4_proto, u64 *fields)
अणु
	पूर्णांक off;

	अगर (l4_mask->tos)
		वापस -EOPNOTSUPP;

	अगर (l4_mask->ip4src) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_IP, NH_FLD_IP_SRC);
		*(__be32 *)(key + off) = l4_value->ip4src;
		*(__be32 *)(mask + off) = l4_mask->ip4src;
		*fields |= DPAA2_ETH_DIST_IPSRC;
	पूर्ण

	अगर (l4_mask->ip4dst) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_IP, NH_FLD_IP_DST);
		*(__be32 *)(key + off) = l4_value->ip4dst;
		*(__be32 *)(mask + off) = l4_mask->ip4dst;
		*fields |= DPAA2_ETH_DIST_IPDST;
	पूर्ण

	अगर (l4_mask->psrc) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_UDP, NH_FLD_UDP_PORT_SRC);
		*(__be16 *)(key + off) = l4_value->psrc;
		*(__be16 *)(mask + off) = l4_mask->psrc;
		*fields |= DPAA2_ETH_DIST_L4SRC;
	पूर्ण

	अगर (l4_mask->pdst) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_UDP, NH_FLD_UDP_PORT_DST);
		*(__be16 *)(key + off) = l4_value->pdst;
		*(__be16 *)(mask + off) = l4_mask->pdst;
		*fields |= DPAA2_ETH_DIST_L4DST;
	पूर्ण

	/* Only apply the rule क्रम IPv4 frames with the specअगरied L4 proto */
	off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_TYPE);
	*(__be16 *)(key + off) = htons(ETH_P_IP);
	*(__be16 *)(mask + off) = htons(0xFFFF);
	*fields |= DPAA2_ETH_DIST_ETHTYPE;

	off = dpaa2_eth_cls_fld_off(NET_PROT_IP, NH_FLD_IP_PROTO);
	*(u8 *)(key + off) = l4_proto;
	*(u8 *)(mask + off) = 0xFF;
	*fields |= DPAA2_ETH_DIST_IPPROTO;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_prep_ext_rule(काष्ठा ethtool_flow_ext *ext_value,
				   काष्ठा ethtool_flow_ext *ext_mask,
				   व्योम *key, व्योम *mask, u64 *fields)
अणु
	पूर्णांक off;

	अगर (ext_mask->vlan_etype)
		वापस -EOPNOTSUPP;

	अगर (ext_mask->vlan_tci) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_VLAN, NH_FLD_VLAN_TCI);
		*(__be16 *)(key + off) = ext_value->vlan_tci;
		*(__be16 *)(mask + off) = ext_mask->vlan_tci;
		*fields |= DPAA2_ETH_DIST_VLAN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_prep_mac_ext_rule(काष्ठा ethtool_flow_ext *ext_value,
				       काष्ठा ethtool_flow_ext *ext_mask,
				       व्योम *key, व्योम *mask, u64 *fields)
अणु
	पूर्णांक off;

	अगर (!is_zero_ether_addr(ext_mask->h_dest)) अणु
		off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_DA);
		ether_addr_copy(key + off, ext_value->h_dest);
		ether_addr_copy(mask + off, ext_mask->h_dest);
		*fields |= DPAA2_ETH_DIST_ETHDST;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_prep_cls_rule(काष्ठा ethtool_rx_flow_spec *fs, व्योम *key,
				   व्योम *mask, u64 *fields)
अणु
	पूर्णांक err;

	चयन (fs->flow_type & 0xFF) अणु
	हाल ETHER_FLOW:
		err = dpaa2_eth_prep_eth_rule(&fs->h_u.ether_spec, &fs->m_u.ether_spec,
					      key, mask, fields);
		अवरोध;
	हाल IP_USER_FLOW:
		err = dpaa2_eth_prep_uip_rule(&fs->h_u.usr_ip4_spec,
					      &fs->m_u.usr_ip4_spec, key, mask, fields);
		अवरोध;
	हाल TCP_V4_FLOW:
		err = dpaa2_eth_prep_l4_rule(&fs->h_u.tcp_ip4_spec, &fs->m_u.tcp_ip4_spec,
					     key, mask, IPPROTO_TCP, fields);
		अवरोध;
	हाल UDP_V4_FLOW:
		err = dpaa2_eth_prep_l4_rule(&fs->h_u.udp_ip4_spec, &fs->m_u.udp_ip4_spec,
					     key, mask, IPPROTO_UDP, fields);
		अवरोध;
	हाल SCTP_V4_FLOW:
		err = dpaa2_eth_prep_l4_rule(&fs->h_u.sctp_ip4_spec,
					     &fs->m_u.sctp_ip4_spec, key, mask,
					     IPPROTO_SCTP, fields);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (err)
		वापस err;

	अगर (fs->flow_type & FLOW_EXT) अणु
		err = dpaa2_eth_prep_ext_rule(&fs->h_ext, &fs->m_ext, key, mask, fields);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (fs->flow_type & FLOW_MAC_EXT) अणु
		err = dpaa2_eth_prep_mac_ext_rule(&fs->h_ext, &fs->m_ext, key,
						  mask, fields);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_करो_cls_rule(काष्ठा net_device *net_dev,
				 काष्ठा ethtool_rx_flow_spec *fs,
				 bool add)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा device *dev = net_dev->dev.parent;
	काष्ठा dpni_rule_cfg rule_cfg = अणु 0 पूर्ण;
	काष्ठा dpni_fs_action_cfg fs_act = अणु 0 पूर्ण;
	dma_addr_t key_iova;
	u64 fields = 0;
	व्योम *key_buf;
	पूर्णांक i, err;

	अगर (fs->ring_cookie != RX_CLS_FLOW_DISC &&
	    fs->ring_cookie >= dpaa2_eth_queue_count(priv))
		वापस -EINVAL;

	rule_cfg.key_size = dpaa2_eth_cls_key_size(DPAA2_ETH_DIST_ALL);

	/* allocate twice the key size, क्रम the actual key and क्रम mask */
	key_buf = kzalloc(rule_cfg.key_size * 2, GFP_KERNEL);
	अगर (!key_buf)
		वापस -ENOMEM;

	/* Fill the key and mask memory areas */
	err = dpaa2_eth_prep_cls_rule(fs, key_buf, key_buf + rule_cfg.key_size, &fields);
	अगर (err)
		जाओ मुक्त_mem;

	अगर (!dpaa2_eth_fs_mask_enabled(priv)) अणु
		/* Masking allows us to configure a maximal key during init and
		 * use it क्रम all flow steering rules. Without it, we include
		 * in the key only the fields actually used, so we need to
		 * extract the others from the final key buffer.
		 *
		 * Program the FS key अगर needed, or वापस error अगर previously
		 * set key can't be used क्रम the current rule. User needs to
		 * delete existing rules in this हाल to allow क्रम the new one.
		 */
		अगर (!priv->rx_cls_fields) अणु
			err = dpaa2_eth_set_cls(net_dev, fields);
			अगर (err)
				जाओ मुक्त_mem;

			priv->rx_cls_fields = fields;
		पूर्ण अन्यथा अगर (priv->rx_cls_fields != fields) अणु
			netdev_err(net_dev, "No support for multiple FS keys, need to delete existing rules\n");
			err = -EOPNOTSUPP;
			जाओ मुक्त_mem;
		पूर्ण

		dpaa2_eth_cls_trim_rule(key_buf, fields);
		rule_cfg.key_size = dpaa2_eth_cls_key_size(fields);
	पूर्ण

	key_iova = dma_map_single(dev, key_buf, rule_cfg.key_size * 2,
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, key_iova)) अणु
		err = -ENOMEM;
		जाओ मुक्त_mem;
	पूर्ण

	rule_cfg.key_iova = key_iova;
	अगर (dpaa2_eth_fs_mask_enabled(priv))
		rule_cfg.mask_iova = key_iova + rule_cfg.key_size;

	अगर (add) अणु
		अगर (fs->ring_cookie == RX_CLS_FLOW_DISC)
			fs_act.options |= DPNI_FS_OPT_DISCARD;
		अन्यथा
			fs_act.flow_id = fs->ring_cookie;
	पूर्ण
	क्रम (i = 0; i < dpaa2_eth_tc_count(priv); i++) अणु
		अगर (add)
			err = dpni_add_fs_entry(priv->mc_io, 0, priv->mc_token,
						i, fs->location, &rule_cfg,
						&fs_act);
		अन्यथा
			err = dpni_हटाओ_fs_entry(priv->mc_io, 0,
						   priv->mc_token, i,
						   &rule_cfg);
		अगर (err || priv->dpni_attrs.options & DPNI_OPT_SHARED_FS)
			अवरोध;
	पूर्ण

	dma_unmap_single(dev, key_iova, rule_cfg.key_size * 2, DMA_TO_DEVICE);

मुक्त_mem:
	kमुक्त(key_buf);

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_eth_num_cls_rules(काष्ठा dpaa2_eth_priv *priv)
अणु
	पूर्णांक i, rules = 0;

	क्रम (i = 0; i < dpaa2_eth_fs_count(priv); i++)
		अगर (priv->cls_rules[i].in_use)
			rules++;

	वापस rules;
पूर्ण

अटल पूर्णांक dpaa2_eth_update_cls_rule(काष्ठा net_device *net_dev,
				     काष्ठा ethtool_rx_flow_spec *new_fs,
				     अचिन्हित पूर्णांक location)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा dpaa2_eth_cls_rule *rule;
	पूर्णांक err = -EINVAL;

	अगर (!priv->rx_cls_enabled)
		वापस -EOPNOTSUPP;

	अगर (location >= dpaa2_eth_fs_count(priv))
		वापस -EINVAL;

	rule = &priv->cls_rules[location];

	/* If a rule is present at the specअगरied location, delete it. */
	अगर (rule->in_use) अणु
		err = dpaa2_eth_करो_cls_rule(net_dev, &rule->fs, false);
		अगर (err)
			वापस err;

		rule->in_use = 0;

		अगर (!dpaa2_eth_fs_mask_enabled(priv) &&
		    !dpaa2_eth_num_cls_rules(priv))
			priv->rx_cls_fields = 0;
	पूर्ण

	/* If no new entry to add, वापस here */
	अगर (!new_fs)
		वापस err;

	err = dpaa2_eth_करो_cls_rule(net_dev, new_fs, true);
	अगर (err)
		वापस err;

	rule->in_use = 1;
	rule->fs = *new_fs;

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_get_rxnfc(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_rxnfc *rxnfc, u32 *rule_locs)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	पूर्णांक max_rules = dpaa2_eth_fs_count(priv);
	पूर्णांक i, j = 0;

	चयन (rxnfc->cmd) अणु
	हाल ETHTOOL_GRXFH:
		/* we purposely ignore cmd->flow_type क्रम now, because the
		 * classअगरier only supports a single set of fields क्रम all
		 * protocols
		 */
		rxnfc->data = priv->rx_hash_fields;
		अवरोध;
	हाल ETHTOOL_GRXRINGS:
		rxnfc->data = dpaa2_eth_queue_count(priv);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		rxnfc->rule_cnt = 0;
		rxnfc->rule_cnt = dpaa2_eth_num_cls_rules(priv);
		rxnfc->data = max_rules;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		अगर (rxnfc->fs.location >= max_rules)
			वापस -EINVAL;
		rxnfc->fs.location = array_index_nospec(rxnfc->fs.location,
							max_rules);
		अगर (!priv->cls_rules[rxnfc->fs.location].in_use)
			वापस -EINVAL;
		rxnfc->fs = priv->cls_rules[rxnfc->fs.location].fs;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		क्रम (i = 0; i < max_rules; i++) अणु
			अगर (!priv->cls_rules[i].in_use)
				जारी;
			अगर (j == rxnfc->rule_cnt)
				वापस -EMSGSIZE;
			rule_locs[j++] = i;
		पूर्ण
		rxnfc->rule_cnt = j;
		rxnfc->data = max_rules;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_set_rxnfc(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_rxnfc *rxnfc)
अणु
	पूर्णांक err = 0;

	चयन (rxnfc->cmd) अणु
	हाल ETHTOOL_SRXFH:
		अगर ((rxnfc->data & DPAA2_RXH_SUPPORTED) != rxnfc->data)
			वापस -EOPNOTSUPP;
		err = dpaa2_eth_set_hash(net_dev, rxnfc->data);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLINS:
		err = dpaa2_eth_update_cls_rule(net_dev, &rxnfc->fs, rxnfc->fs.location);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		err = dpaa2_eth_update_cls_rule(net_dev, शून्य, rxnfc->fs.location);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक dpaa2_phc_index = -1;
EXPORT_SYMBOL(dpaa2_phc_index);

अटल पूर्णांक dpaa2_eth_get_ts_info(काष्ठा net_device *dev,
				 काष्ठा ethtool_ts_info *info)
अणु
	अगर (!dpaa2_ptp)
		वापस ethtool_op_get_ts_info(dev, info);

	info->so_बारtamping = SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	info->phc_index = dpaa2_phc_index;

	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON) |
			 (1 << HWTSTAMP_TX_ONESTEP_SYNC);

	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_ALL);
	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_get_tunable(काष्ठा net_device *net_dev,
				 स्थिर काष्ठा ethtool_tunable *tuna,
				 व्योम *data)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	पूर्णांक err = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = priv->rx_copyअवरोध;
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_eth_set_tunable(काष्ठा net_device *net_dev,
				 स्थिर काष्ठा ethtool_tunable *tuna,
				 स्थिर व्योम *data)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	पूर्णांक err = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		priv->rx_copyअवरोध = *(u32 *)data;
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

स्थिर काष्ठा ethtool_ops dpaa2_ethtool_ops = अणु
	.get_drvinfo = dpaa2_eth_get_drvinfo,
	.nway_reset = dpaa2_eth_nway_reset,
	.get_link = ethtool_op_get_link,
	.get_link_ksettings = dpaa2_eth_get_link_ksettings,
	.set_link_ksettings = dpaa2_eth_set_link_ksettings,
	.get_छोड़ोparam = dpaa2_eth_get_छोड़ोparam,
	.set_छोड़ोparam = dpaa2_eth_set_छोड़ोparam,
	.get_sset_count = dpaa2_eth_get_sset_count,
	.get_ethtool_stats = dpaa2_eth_get_ethtool_stats,
	.get_strings = dpaa2_eth_get_strings,
	.get_rxnfc = dpaa2_eth_get_rxnfc,
	.set_rxnfc = dpaa2_eth_set_rxnfc,
	.get_ts_info = dpaa2_eth_get_ts_info,
	.get_tunable = dpaa2_eth_get_tunable,
	.set_tunable = dpaa2_eth_set_tunable,
पूर्ण;
