<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

#समावेश "sxgbe_common.h"
#समावेश "sxgbe_reg.h"
#समावेश "sxgbe_dma.h"

काष्ठा sxgbe_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा SXGBE_STAT(m)						\
अणु								\
	#m,							\
	माप_field(काष्ठा sxgbe_extra_stats, m),		\
	दुरत्व(काष्ठा sxgbe_priv_data, xstats.m)		\
पूर्ण

अटल स्थिर काष्ठा sxgbe_stats sxgbe_gstrings_stats[] = अणु
	/* TX/RX IRQ events */
	SXGBE_STAT(tx_process_stopped_irq),
	SXGBE_STAT(tx_ctxt_desc_err),
	SXGBE_STAT(tx_threshold),
	SXGBE_STAT(rx_threshold),
	SXGBE_STAT(tx_pkt_n),
	SXGBE_STAT(rx_pkt_n),
	SXGBE_STAT(normal_irq_n),
	SXGBE_STAT(tx_normal_irq_n),
	SXGBE_STAT(rx_normal_irq_n),
	SXGBE_STAT(napi_poll),
	SXGBE_STAT(tx_clean),
	SXGBE_STAT(tx_reset_ic_bit),
	SXGBE_STAT(rx_process_stopped_irq),
	SXGBE_STAT(rx_underflow_irq),

	/* Bus access errors */
	SXGBE_STAT(fatal_bus_error_irq),
	SXGBE_STAT(tx_पढ़ो_transfer_err),
	SXGBE_STAT(tx_ग_लिखो_transfer_err),
	SXGBE_STAT(tx_desc_access_err),
	SXGBE_STAT(tx_buffer_access_err),
	SXGBE_STAT(tx_data_transfer_err),
	SXGBE_STAT(rx_पढ़ो_transfer_err),
	SXGBE_STAT(rx_ग_लिखो_transfer_err),
	SXGBE_STAT(rx_desc_access_err),
	SXGBE_STAT(rx_buffer_access_err),
	SXGBE_STAT(rx_data_transfer_err),

	/* EEE-LPI stats */
	SXGBE_STAT(tx_lpi_entry_n),
	SXGBE_STAT(tx_lpi_निकास_n),
	SXGBE_STAT(rx_lpi_entry_n),
	SXGBE_STAT(rx_lpi_निकास_n),
	SXGBE_STAT(eee_wakeup_error_n),

	/* RX specअगरic */
	/* L2 error */
	SXGBE_STAT(rx_code_gmii_err),
	SXGBE_STAT(rx_watchकरोg_err),
	SXGBE_STAT(rx_crc_err),
	SXGBE_STAT(rx_gaपूर्णांक_pkt_err),
	SXGBE_STAT(ip_hdr_err),
	SXGBE_STAT(ip_payload_err),
	SXGBE_STAT(overflow_error),

	/* L2 Pkt type */
	SXGBE_STAT(len_pkt),
	SXGBE_STAT(mac_ctl_pkt),
	SXGBE_STAT(dcb_ctl_pkt),
	SXGBE_STAT(arp_pkt),
	SXGBE_STAT(oam_pkt),
	SXGBE_STAT(untag_okt),
	SXGBE_STAT(other_pkt),
	SXGBE_STAT(svlan_tag_pkt),
	SXGBE_STAT(cvlan_tag_pkt),
	SXGBE_STAT(dvlan_ocvlan_icvlan_pkt),
	SXGBE_STAT(dvlan_osvlan_isvlan_pkt),
	SXGBE_STAT(dvlan_osvlan_icvlan_pkt),
	SXGBE_STAT(dvan_ocvlan_icvlan_pkt),

	/* L3/L4 Pkt type */
	SXGBE_STAT(not_ip_pkt),
	SXGBE_STAT(ip4_tcp_pkt),
	SXGBE_STAT(ip4_udp_pkt),
	SXGBE_STAT(ip4_icmp_pkt),
	SXGBE_STAT(ip4_unknown_pkt),
	SXGBE_STAT(ip6_tcp_pkt),
	SXGBE_STAT(ip6_udp_pkt),
	SXGBE_STAT(ip6_icmp_pkt),
	SXGBE_STAT(ip6_unknown_pkt),

	/* Filter specअगरic */
	SXGBE_STAT(vlan_filter_match),
	SXGBE_STAT(sa_filter_fail),
	SXGBE_STAT(da_filter_fail),
	SXGBE_STAT(hash_filter_pass),
	SXGBE_STAT(l3_filter_match),
	SXGBE_STAT(l4_filter_match),

	/* RX context specअगरic */
	SXGBE_STAT(बारtamp_dropped),
	SXGBE_STAT(rx_msg_type_no_ptp),
	SXGBE_STAT(rx_ptp_type_sync),
	SXGBE_STAT(rx_ptp_type_follow_up),
	SXGBE_STAT(rx_ptp_type_delay_req),
	SXGBE_STAT(rx_ptp_type_delay_resp),
	SXGBE_STAT(rx_ptp_type_pdelay_req),
	SXGBE_STAT(rx_ptp_type_pdelay_resp),
	SXGBE_STAT(rx_ptp_type_pdelay_follow_up),
	SXGBE_STAT(rx_ptp_announce),
	SXGBE_STAT(rx_ptp_mgmt),
	SXGBE_STAT(rx_ptp_संकेत),
	SXGBE_STAT(rx_ptp_resv_msg_type),
पूर्ण;
#घोषणा SXGBE_STATS_LEN ARRAY_SIZE(sxgbe_gstrings_stats)

अटल पूर्णांक sxgbe_get_eee(काष्ठा net_device *dev,
			 काष्ठा ethtool_eee *edata)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);

	अगर (!priv->hw_cap.eee)
		वापस -EOPNOTSUPP;

	edata->eee_enabled = priv->eee_enabled;
	edata->eee_active = priv->eee_active;
	edata->tx_lpi_समयr = priv->tx_lpi_समयr;

	वापस phy_ethtool_get_eee(dev->phydev, edata);
पूर्ण

अटल पूर्णांक sxgbe_set_eee(काष्ठा net_device *dev,
			 काष्ठा ethtool_eee *edata)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);

	priv->eee_enabled = edata->eee_enabled;

	अगर (!priv->eee_enabled) अणु
		sxgbe_disable_eee_mode(priv);
	पूर्ण अन्यथा अणु
		/* We are asking क्रम enabling the EEE but it is safe
		 * to verअगरy all by invoking the eee_init function.
		 * In हाल of failure it will वापस an error.
		 */
		priv->eee_enabled = sxgbe_eee_init(priv);
		अगर (!priv->eee_enabled)
			वापस -EOPNOTSUPP;

		/* Do not change tx_lpi_समयr in हाल of failure */
		priv->tx_lpi_समयr = edata->tx_lpi_समयr;
	पूर्ण

	वापस phy_ethtool_set_eee(dev->phydev, edata);
पूर्ण

अटल व्योम sxgbe_getdrvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
पूर्ण

अटल u32 sxgbe_geपंचांगsglevel(काष्ठा net_device *dev)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	वापस priv->msg_enable;
पूर्ण

अटल व्योम sxgbe_seपंचांगsglevel(काष्ठा net_device *dev, u32 level)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	priv->msg_enable = level;
पूर्ण

अटल व्योम sxgbe_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	पूर्णांक i;
	u8 *p = data;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < SXGBE_STATS_LEN; i++) अणु
			स_नकल(p, sxgbe_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sxgbe_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	पूर्णांक len;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		len = SXGBE_STATS_LEN;
		वापस len;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम sxgbe_get_ethtool_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats *dummy, u64 *data)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	पूर्णांक i;
	अक्षर *p;

	अगर (priv->eee_enabled) अणु
		पूर्णांक val = phy_get_eee_err(dev->phydev);

		अगर (val)
			priv->xstats.eee_wakeup_error_n = val;
	पूर्ण

	क्रम (i = 0; i < SXGBE_STATS_LEN; i++) अणु
		p = (अक्षर *)priv + sxgbe_gstrings_stats[i].stat_offset;
		data[i] = (sxgbe_gstrings_stats[i].माप_stat == माप(u64))
			? (*(u64 *)p) : (*(u32 *)p);
	पूर्ण
पूर्ण

अटल व्योम sxgbe_get_channels(काष्ठा net_device *dev,
			       काष्ठा ethtool_channels *channel)
अणु
	channel->max_rx = SXGBE_MAX_RX_CHANNELS;
	channel->max_tx = SXGBE_MAX_TX_CHANNELS;
	channel->rx_count = SXGBE_RX_QUEUES;
	channel->tx_count = SXGBE_TX_QUEUES;
पूर्ण

अटल u32 sxgbe_riwt2usec(u32 riwt, काष्ठा sxgbe_priv_data *priv)
अणु
	अचिन्हित दीर्घ clk = clk_get_rate(priv->sxgbe_clk);

	अगर (!clk)
		वापस 0;

	वापस (riwt * 256) / (clk / 1000000);
पूर्ण

अटल u32 sxgbe_usec2riwt(u32 usec, काष्ठा sxgbe_priv_data *priv)
अणु
	अचिन्हित दीर्घ clk = clk_get_rate(priv->sxgbe_clk);

	अगर (!clk)
		वापस 0;

	वापस (usec * (clk / 1000000)) / 256;
पूर्ण

अटल पूर्णांक sxgbe_get_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);

	अगर (priv->use_riwt)
		ec->rx_coalesce_usecs = sxgbe_riwt2usec(priv->rx_riwt, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक sxgbe_set_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक rx_riwt;

	अगर (!ec->rx_coalesce_usecs)
		वापस -EINVAL;

	rx_riwt = sxgbe_usec2riwt(ec->rx_coalesce_usecs, priv);

	अगर ((rx_riwt > SXGBE_MAX_DMA_RIWT) || (rx_riwt < SXGBE_MIN_DMA_RIWT))
		वापस -EINVAL;
	अन्यथा अगर (!priv->use_riwt)
		वापस -EOPNOTSUPP;

	priv->rx_riwt = rx_riwt;
	priv->hw->dma->rx_watchकरोg(priv->ioaddr, priv->rx_riwt);

	वापस 0;
पूर्ण

अटल पूर्णांक sxgbe_get_rss_hash_opts(काष्ठा sxgbe_priv_data *priv,
				   काष्ठा ethtool_rxnfc *cmd)
अणु
	cmd->data = 0;

	/* Report शेष options क्रम RSS on sxgbe */
	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल IPV4_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल IPV6_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sxgbe_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			   u32 *rule_locs)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXFH:
		ret = sxgbe_get_rss_hash_opts(priv, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sxgbe_set_rss_hash_opt(काष्ठा sxgbe_priv_data *priv,
				  काष्ठा ethtool_rxnfc *cmd)
अणु
	u32 reg_val = 0;

	/* RSS करोes not support anything other than hashing
	 * to queues on src and dst IPs and ports
	 */
	अगर (cmd->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		वापस -EINVAL;

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		अगर (!(cmd->data & RXH_IP_SRC) ||
		    !(cmd->data & RXH_IP_DST) ||
		    !(cmd->data & RXH_L4_B_0_1) ||
		    !(cmd->data & RXH_L4_B_2_3))
			वापस -EINVAL;
		reg_val = SXGBE_CORE_RSS_CTL_TCP4TE;
		अवरोध;
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		अगर (!(cmd->data & RXH_IP_SRC) ||
		    !(cmd->data & RXH_IP_DST) ||
		    !(cmd->data & RXH_L4_B_0_1) ||
		    !(cmd->data & RXH_L4_B_2_3))
			वापस -EINVAL;
		reg_val = SXGBE_CORE_RSS_CTL_UDP4TE;
		अवरोध;
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल SCTP_V6_FLOW:
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		अगर (!(cmd->data & RXH_IP_SRC) ||
		    !(cmd->data & RXH_IP_DST) ||
		    (cmd->data & RXH_L4_B_0_1) ||
		    (cmd->data & RXH_L4_B_2_3))
			वापस -EINVAL;
		reg_val = SXGBE_CORE_RSS_CTL_IP2TE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Read SXGBE RSS control रेजिस्टर and update */
	reg_val |= पढ़ोl(priv->ioaddr + SXGBE_CORE_RSS_CTL_REG);
	ग_लिखोl(reg_val, priv->ioaddr + SXGBE_CORE_RSS_CTL_REG);
	पढ़ोl(priv->ioaddr + SXGBE_CORE_RSS_CTL_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक sxgbe_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = sxgbe_set_rss_hash_opt(priv, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sxgbe_get_regs(काष्ठा net_device *dev,
			   काष्ठा ethtool_regs *regs, व्योम *space)
अणु
	काष्ठा sxgbe_priv_data *priv = netdev_priv(dev);
	u32 *reg_space = (u32 *)space;
	पूर्णांक reg_offset;
	पूर्णांक reg_ix = 0;
	व्योम __iomem *ioaddr = priv->ioaddr;

	स_रखो(reg_space, 0x0, REG_SPACE_SIZE);

	/* MAC रेजिस्टरs */
	क्रम (reg_offset = START_MAC_REG_OFFSET;
	     reg_offset <= MAX_MAC_REG_OFFSET; reg_offset += 4) अणु
		reg_space[reg_ix] = पढ़ोl(ioaddr + reg_offset);
		reg_ix++;
	पूर्ण

	/* MTL रेजिस्टरs */
	क्रम (reg_offset = START_MTL_REG_OFFSET;
	     reg_offset <= MAX_MTL_REG_OFFSET; reg_offset += 4) अणु
		reg_space[reg_ix] = पढ़ोl(ioaddr + reg_offset);
		reg_ix++;
	पूर्ण

	/* DMA रेजिस्टरs */
	क्रम (reg_offset = START_DMA_REG_OFFSET;
	     reg_offset <= MAX_DMA_REG_OFFSET; reg_offset += 4) अणु
		reg_space[reg_ix] = पढ़ोl(ioaddr + reg_offset);
		reg_ix++;
	पूर्ण

	BUG_ON(reg_ix * 4 > REG_SPACE_SIZE);
पूर्ण

अटल पूर्णांक sxgbe_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस REG_SPACE_SIZE;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sxgbe_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS,
	.get_drvinfo = sxgbe_getdrvinfo,
	.get_msglevel = sxgbe_geपंचांगsglevel,
	.set_msglevel = sxgbe_seपंचांगsglevel,
	.get_link = ethtool_op_get_link,
	.get_strings = sxgbe_get_strings,
	.get_ethtool_stats = sxgbe_get_ethtool_stats,
	.get_sset_count = sxgbe_get_sset_count,
	.get_channels = sxgbe_get_channels,
	.get_coalesce = sxgbe_get_coalesce,
	.set_coalesce = sxgbe_set_coalesce,
	.get_rxnfc = sxgbe_get_rxnfc,
	.set_rxnfc = sxgbe_set_rxnfc,
	.get_regs = sxgbe_get_regs,
	.get_regs_len = sxgbe_get_regs_len,
	.get_eee = sxgbe_get_eee,
	.set_eee = sxgbe_set_eee,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

व्योम sxgbe_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &sxgbe_ethtool_ops;
पूर्ण
