<शैली गुरु>
/*
 * Copyright 2013 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/net_tstamp.h>

#समावेश "enic_res.h"
#समावेश "enic.h"
#समावेश "enic_dev.h"
#समावेश "enic_clsf.h"
#समावेश "vnic_rss.h"
#समावेश "vnic_stats.h"

काष्ठा enic_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	अचिन्हित पूर्णांक index;
पूर्ण;

#घोषणा ENIC_TX_STAT(stat) अणु \
	.name = #stat, \
	.index = दुरत्व(काष्ठा vnic_tx_stats, stat) / माप(u64) \
पूर्ण

#घोषणा ENIC_RX_STAT(stat) अणु \
	.name = #stat, \
	.index = दुरत्व(काष्ठा vnic_rx_stats, stat) / माप(u64) \
पूर्ण

#घोषणा ENIC_GEN_STAT(stat) अणु \
	.name = #stat, \
	.index = दुरत्व(काष्ठा vnic_gen_stats, stat) / माप(u64)\
पूर्ण

अटल स्थिर काष्ठा enic_stat enic_tx_stats[] = अणु
	ENIC_TX_STAT(tx_frames_ok),
	ENIC_TX_STAT(tx_unicast_frames_ok),
	ENIC_TX_STAT(tx_multicast_frames_ok),
	ENIC_TX_STAT(tx_broadcast_frames_ok),
	ENIC_TX_STAT(tx_bytes_ok),
	ENIC_TX_STAT(tx_unicast_bytes_ok),
	ENIC_TX_STAT(tx_multicast_bytes_ok),
	ENIC_TX_STAT(tx_broadcast_bytes_ok),
	ENIC_TX_STAT(tx_drops),
	ENIC_TX_STAT(tx_errors),
	ENIC_TX_STAT(tx_tso),
पूर्ण;

अटल स्थिर काष्ठा enic_stat enic_rx_stats[] = अणु
	ENIC_RX_STAT(rx_frames_ok),
	ENIC_RX_STAT(rx_frames_total),
	ENIC_RX_STAT(rx_unicast_frames_ok),
	ENIC_RX_STAT(rx_multicast_frames_ok),
	ENIC_RX_STAT(rx_broadcast_frames_ok),
	ENIC_RX_STAT(rx_bytes_ok),
	ENIC_RX_STAT(rx_unicast_bytes_ok),
	ENIC_RX_STAT(rx_multicast_bytes_ok),
	ENIC_RX_STAT(rx_broadcast_bytes_ok),
	ENIC_RX_STAT(rx_drop),
	ENIC_RX_STAT(rx_no_bufs),
	ENIC_RX_STAT(rx_errors),
	ENIC_RX_STAT(rx_rss),
	ENIC_RX_STAT(rx_crc_errors),
	ENIC_RX_STAT(rx_frames_64),
	ENIC_RX_STAT(rx_frames_127),
	ENIC_RX_STAT(rx_frames_255),
	ENIC_RX_STAT(rx_frames_511),
	ENIC_RX_STAT(rx_frames_1023),
	ENIC_RX_STAT(rx_frames_1518),
	ENIC_RX_STAT(rx_frames_to_max),
पूर्ण;

अटल स्थिर काष्ठा enic_stat enic_gen_stats[] = अणु
	ENIC_GEN_STAT(dma_map_error),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक enic_n_tx_stats = ARRAY_SIZE(enic_tx_stats);
अटल स्थिर अचिन्हित पूर्णांक enic_n_rx_stats = ARRAY_SIZE(enic_rx_stats);
अटल स्थिर अचिन्हित पूर्णांक enic_n_gen_stats = ARRAY_SIZE(enic_gen_stats);

अटल व्योम enic_पूर्णांकr_coal_set_rx(काष्ठा enic *enic, u32 समयr)
अणु
	पूर्णांक i;
	पूर्णांक पूर्णांकr;

	क्रम (i = 0; i < enic->rq_count; i++) अणु
		पूर्णांकr = enic_msix_rq_पूर्णांकr(enic, i);
		vnic_पूर्णांकr_coalescing_समयr_set(&enic->पूर्णांकr[पूर्णांकr], समयr);
	पूर्ण
पूर्ण

अटल पूर्णांक enic_get_ksettings(काष्ठा net_device *netdev,
			      काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा ethtool_link_settings *base = &ecmd->base;

	ethtool_link_ksettings_add_link_mode(ecmd, supported,
					     10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(ecmd, supported, FIBRE);
	ethtool_link_ksettings_add_link_mode(ecmd, advertising,
					     10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(ecmd, advertising, FIBRE);
	base->port = PORT_FIBRE;

	अगर (netअगर_carrier_ok(netdev)) अणु
		base->speed = vnic_dev_port_speed(enic->vdev);
		base->duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		base->speed = SPEED_UNKNOWN;
		base->duplex = DUPLEX_UNKNOWN;
	पूर्ण

	base->स्वतःneg = AUTONEG_DISABLE;

	वापस 0;
पूर्ण

अटल व्योम enic_get_drvinfo(काष्ठा net_device *netdev,
	काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा vnic_devcmd_fw_info *fw_info;
	पूर्णांक err;

	err = enic_dev_fw_info(enic, &fw_info);
	/* वापस only when pci_zalloc_consistent fails in vnic_dev_fw_info
	 * For other failures, like devcmd failure, we वापस previously
	 * recorded info.
	 */
	अगर (err == -ENOMEM)
		वापस;

	strlcpy(drvinfo->driver, DRV_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->fw_version, fw_info->fw_version,
		माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(enic->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम enic_get_strings(काष्ठा net_device *netdev, u32 stringset,
	u8 *data)
अणु
	अचिन्हित पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < enic_n_tx_stats; i++) अणु
			स_नकल(data, enic_tx_stats[i].name, ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < enic_n_rx_stats; i++) अणु
			स_नकल(data, enic_rx_stats[i].name, ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < enic_n_gen_stats; i++) अणु
			स_नकल(data, enic_gen_stats[i].name, ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम enic_get_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा vnic_enet_config *c = &enic->config;

	ring->rx_max_pending = ENIC_MAX_RQ_DESCS;
	ring->rx_pending = c->rq_desc_count;
	ring->tx_max_pending = ENIC_MAX_WQ_DESCS;
	ring->tx_pending = c->wq_desc_count;
पूर्ण

अटल पूर्णांक enic_set_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा vnic_enet_config *c = &enic->config;
	पूर्णांक running = netअगर_running(netdev);
	अचिन्हित पूर्णांक rx_pending;
	अचिन्हित पूर्णांक tx_pending;
	पूर्णांक err = 0;

	अगर (ring->rx_mini_max_pending || ring->rx_mini_pending) अणु
		netdev_info(netdev,
			    "modifying mini ring params is not supported");
		वापस -EINVAL;
	पूर्ण
	अगर (ring->rx_jumbo_max_pending || ring->rx_jumbo_pending) अणु
		netdev_info(netdev,
			    "modifying jumbo ring params is not supported");
		वापस -EINVAL;
	पूर्ण
	rx_pending = c->rq_desc_count;
	tx_pending = c->wq_desc_count;
	अगर (ring->rx_pending > ENIC_MAX_RQ_DESCS ||
	    ring->rx_pending < ENIC_MIN_RQ_DESCS) अणु
		netdev_info(netdev, "rx pending (%u) not in range [%u,%u]",
			    ring->rx_pending, ENIC_MIN_RQ_DESCS,
			    ENIC_MAX_RQ_DESCS);
		वापस -EINVAL;
	पूर्ण
	अगर (ring->tx_pending > ENIC_MAX_WQ_DESCS ||
	    ring->tx_pending < ENIC_MIN_WQ_DESCS) अणु
		netdev_info(netdev, "tx pending (%u) not in range [%u,%u]",
			    ring->tx_pending, ENIC_MIN_WQ_DESCS,
			    ENIC_MAX_WQ_DESCS);
		वापस -EINVAL;
	पूर्ण
	अगर (running)
		dev_बंद(netdev);
	c->rq_desc_count =
		ring->rx_pending & 0xffffffe0; /* must be aligned to groups of 32 */
	c->wq_desc_count =
		ring->tx_pending & 0xffffffe0; /* must be aligned to groups of 32 */
	enic_मुक्त_vnic_resources(enic);
	err = enic_alloc_vnic_resources(enic);
	अगर (err) अणु
		netdev_err(netdev,
			   "Failed to alloc vNIC resources, aborting\n");
		enic_मुक्त_vnic_resources(enic);
		जाओ err_out;
	पूर्ण
	enic_init_vnic_resources(enic);
	अगर (running) अणु
		err = dev_खोलो(netdev, शून्य);
		अगर (err)
			जाओ err_out;
	पूर्ण
	वापस 0;
err_out:
	c->rq_desc_count = rx_pending;
	c->wq_desc_count = tx_pending;
	वापस err;
पूर्ण

अटल पूर्णांक enic_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस enic_n_tx_stats + enic_n_rx_stats + enic_n_gen_stats;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम enic_get_ethtool_stats(काष्ठा net_device *netdev,
	काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा vnic_stats *vstats;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = enic_dev_stats_dump(enic, &vstats);
	/* वापस only when pci_zalloc_consistent fails in vnic_dev_stats_dump
	 * For other failures, like devcmd failure, we वापस previously
	 * recorded stats.
	 */
	अगर (err == -ENOMEM)
		वापस;

	क्रम (i = 0; i < enic_n_tx_stats; i++)
		*(data++) = ((u64 *)&vstats->tx)[enic_tx_stats[i].index];
	क्रम (i = 0; i < enic_n_rx_stats; i++)
		*(data++) = ((u64 *)&vstats->rx)[enic_rx_stats[i].index];
	क्रम (i = 0; i < enic_n_gen_stats; i++)
		*(data++) = ((u64 *)&enic->gen_stats)[enic_gen_stats[i].index];
पूर्ण

अटल u32 enic_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	वापस enic->msg_enable;
पूर्ण

अटल व्योम enic_set_msglevel(काष्ठा net_device *netdev, u32 value)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	enic->msg_enable = value;
पूर्ण

अटल पूर्णांक enic_get_coalesce(काष्ठा net_device *netdev,
	काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	काष्ठा enic_rx_coal *rxcoal = &enic->rx_coalesce_setting;

	अगर (vnic_dev_get_पूर्णांकr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX)
		ecmd->tx_coalesce_usecs = enic->tx_coalesce_usecs;
	ecmd->rx_coalesce_usecs = enic->rx_coalesce_usecs;
	अगर (rxcoal->use_adaptive_rx_coalesce)
		ecmd->use_adaptive_rx_coalesce = 1;
	ecmd->rx_coalesce_usecs_low = rxcoal->small_pkt_range_start;
	ecmd->rx_coalesce_usecs_high = rxcoal->range_end;

	वापस 0;
पूर्ण

अटल पूर्णांक enic_coalesce_valid(काष्ठा enic *enic,
			       काष्ठा ethtool_coalesce *ec)
अणु
	u32 coalesce_usecs_max = vnic_dev_get_पूर्णांकr_coal_समयr_max(enic->vdev);
	u32 rx_coalesce_usecs_high = min_t(u32, coalesce_usecs_max,
					   ec->rx_coalesce_usecs_high);
	u32 rx_coalesce_usecs_low = min_t(u32, coalesce_usecs_max,
					  ec->rx_coalesce_usecs_low);

	अगर ((vnic_dev_get_पूर्णांकr_mode(enic->vdev) != VNIC_DEV_INTR_MODE_MSIX) &&
	    ec->tx_coalesce_usecs)
		वापस -EINVAL;

	अगर ((ec->tx_coalesce_usecs > coalesce_usecs_max)	||
	    (ec->rx_coalesce_usecs > coalesce_usecs_max)	||
	    (ec->rx_coalesce_usecs_low > coalesce_usecs_max)	||
	    (ec->rx_coalesce_usecs_high > coalesce_usecs_max))
		netdev_info(enic->netdev, "ethtool_set_coalesce: adaptor supports max coalesce value of %d. Setting max value.\n",
			    coalesce_usecs_max);

	अगर (ec->rx_coalesce_usecs_high &&
	    (rx_coalesce_usecs_high <
	     rx_coalesce_usecs_low + ENIC_AIC_LARGE_PKT_DIFF))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक enic_set_coalesce(काष्ठा net_device *netdev,
	काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);
	u32 tx_coalesce_usecs;
	u32 rx_coalesce_usecs;
	u32 rx_coalesce_usecs_low;
	u32 rx_coalesce_usecs_high;
	u32 coalesce_usecs_max;
	अचिन्हित पूर्णांक i, पूर्णांकr;
	पूर्णांक ret;
	काष्ठा enic_rx_coal *rxcoal = &enic->rx_coalesce_setting;

	ret = enic_coalesce_valid(enic, ecmd);
	अगर (ret)
		वापस ret;
	coalesce_usecs_max = vnic_dev_get_पूर्णांकr_coal_समयr_max(enic->vdev);
	tx_coalesce_usecs = min_t(u32, ecmd->tx_coalesce_usecs,
				  coalesce_usecs_max);
	rx_coalesce_usecs = min_t(u32, ecmd->rx_coalesce_usecs,
				  coalesce_usecs_max);

	rx_coalesce_usecs_low = min_t(u32, ecmd->rx_coalesce_usecs_low,
				      coalesce_usecs_max);
	rx_coalesce_usecs_high = min_t(u32, ecmd->rx_coalesce_usecs_high,
				       coalesce_usecs_max);

	अगर (vnic_dev_get_पूर्णांकr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX) अणु
		क्रम (i = 0; i < enic->wq_count; i++) अणु
			पूर्णांकr = enic_msix_wq_पूर्णांकr(enic, i);
			vnic_पूर्णांकr_coalescing_समयr_set(&enic->पूर्णांकr[पूर्णांकr],
						       tx_coalesce_usecs);
		पूर्ण
		enic->tx_coalesce_usecs = tx_coalesce_usecs;
	पूर्ण
	rxcoal->use_adaptive_rx_coalesce = !!ecmd->use_adaptive_rx_coalesce;
	अगर (!rxcoal->use_adaptive_rx_coalesce)
		enic_पूर्णांकr_coal_set_rx(enic, rx_coalesce_usecs);
	अगर (ecmd->rx_coalesce_usecs_high) अणु
		rxcoal->range_end = rx_coalesce_usecs_high;
		rxcoal->small_pkt_range_start = rx_coalesce_usecs_low;
		rxcoal->large_pkt_range_start = rx_coalesce_usecs_low +
						ENIC_AIC_LARGE_PKT_DIFF;
	पूर्ण

	enic->rx_coalesce_usecs = rx_coalesce_usecs;

	वापस 0;
पूर्ण

अटल पूर्णांक enic_grxclsrlall(काष्ठा enic *enic, काष्ठा ethtool_rxnfc *cmd,
			    u32 *rule_locs)
अणु
	पूर्णांक j, ret = 0, cnt = 0;

	cmd->data = enic->rfs_h.max - enic->rfs_h.मुक्त;
	क्रम (j = 0; j < (1 << ENIC_RFS_FLW_BITSHIFT); j++) अणु
		काष्ठा hlist_head *hhead;
		काष्ठा hlist_node *पंचांगp;
		काष्ठा enic_rfs_fltr_node *n;

		hhead = &enic->rfs_h.ht_head[j];
		hlist_क्रम_each_entry_safe(n, पंचांगp, hhead, node) अणु
			अगर (cnt == cmd->rule_cnt)
				वापस -EMSGSIZE;
			rule_locs[cnt] = n->fltr_id;
			cnt++;
		पूर्ण
	पूर्ण
	cmd->rule_cnt = cnt;

	वापस ret;
पूर्ण

अटल पूर्णांक enic_grxclsrule(काष्ठा enic *enic, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
				(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा enic_rfs_fltr_node *n;

	n = htbl_fltr_search(enic, (u16)fsp->location);
	अगर (!n)
		वापस -EINVAL;
	चयन (n->keys.basic.ip_proto) अणु
	हाल IPPROTO_TCP:
		fsp->flow_type = TCP_V4_FLOW;
		अवरोध;
	हाल IPPROTO_UDP:
		fsp->flow_type = UDP_V4_FLOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	fsp->h_u.tcp_ip4_spec.ip4src = flow_get_u32_src(&n->keys);
	fsp->m_u.tcp_ip4_spec.ip4src = (__u32)~0;

	fsp->h_u.tcp_ip4_spec.ip4dst = flow_get_u32_dst(&n->keys);
	fsp->m_u.tcp_ip4_spec.ip4dst = (__u32)~0;

	fsp->h_u.tcp_ip4_spec.psrc = n->keys.ports.src;
	fsp->m_u.tcp_ip4_spec.psrc = (__u16)~0;

	fsp->h_u.tcp_ip4_spec.pdst = n->keys.ports.dst;
	fsp->m_u.tcp_ip4_spec.pdst = (__u16)~0;

	fsp->ring_cookie = n->rq_id;

	वापस 0;
पूर्ण

अटल पूर्णांक enic_get_rx_flow_hash(काष्ठा enic *enic, काष्ठा ethtool_rxnfc *cmd)
अणु
	u8 rss_hash_type = 0;
	cmd->data = 0;

	spin_lock_bh(&enic->devcmd_lock);
	(व्योम)vnic_dev_capable_rss_hash_type(enic->vdev, &rss_hash_type);
	spin_unlock_bh(&enic->devcmd_lock);
	चयन (cmd->flow_type) अणु
	हाल TCP_V6_FLOW:
	हाल TCP_V4_FLOW:
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3 |
			     RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल UDP_V6_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अगर (rss_hash_type & NIC_CFG_RSS_HASH_TYPE_UDP_IPV6)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल UDP_V4_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अगर (rss_hash_type & NIC_CFG_RSS_HASH_TYPE_UDP_IPV4)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enic_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			  u32 *rule_locs)
अणु
	काष्ठा enic *enic = netdev_priv(dev);
	पूर्णांक ret = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = enic->rq_count;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		spin_lock_bh(&enic->rfs_h.lock);
		cmd->rule_cnt = enic->rfs_h.max - enic->rfs_h.मुक्त;
		cmd->data = enic->rfs_h.max;
		spin_unlock_bh(&enic->rfs_h.lock);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		spin_lock_bh(&enic->rfs_h.lock);
		ret = enic_grxclsrlall(enic, cmd, rule_locs);
		spin_unlock_bh(&enic->rfs_h.lock);
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		spin_lock_bh(&enic->rfs_h.lock);
		ret = enic_grxclsrule(enic, cmd);
		spin_unlock_bh(&enic->rfs_h.lock);
		अवरोध;
	हाल ETHTOOL_GRXFH:
		ret = enic_get_rx_flow_hash(enic, cmd);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक enic_get_tunable(काष्ठा net_device *dev,
			    स्थिर काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	काष्ठा enic *enic = netdev_priv(dev);
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = enic->rx_copyअवरोध;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक enic_set_tunable(काष्ठा net_device *dev,
			    स्थिर काष्ठा ethtool_tunable *tuna,
			    स्थिर व्योम *data)
अणु
	काष्ठा enic *enic = netdev_priv(dev);
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		enic->rx_copyअवरोध = *(u32 *)data;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 enic_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस ENIC_RSS_LEN;
पूर्ण

अटल पूर्णांक enic_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *hkey,
			 u8 *hfunc)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);

	अगर (hkey)
		स_नकल(hkey, enic->rss_key, ENIC_RSS_LEN);

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	वापस 0;
पूर्ण

अटल पूर्णांक enic_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			 स्थिर u8 *hkey, स्थिर u8 hfunc)
अणु
	काष्ठा enic *enic = netdev_priv(netdev);

	अगर ((hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP) ||
	    indir)
		वापस -EINVAL;

	अगर (hkey)
		स_नकल(enic->rss_key, hkey, ENIC_RSS_LEN);

	वापस __enic_set_rsskey(enic);
पूर्ण

अटल पूर्णांक enic_get_ts_info(काष्ठा net_device *netdev,
			    काष्ठा ethtool_ts_info *info)
अणु
	info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops enic_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX |
				     ETHTOOL_COALESCE_RX_USECS_LOW |
				     ETHTOOL_COALESCE_RX_USECS_HIGH,
	.get_drvinfo = enic_get_drvinfo,
	.get_msglevel = enic_get_msglevel,
	.set_msglevel = enic_set_msglevel,
	.get_link = ethtool_op_get_link,
	.get_strings = enic_get_strings,
	.get_ringparam = enic_get_ringparam,
	.set_ringparam = enic_set_ringparam,
	.get_sset_count = enic_get_sset_count,
	.get_ethtool_stats = enic_get_ethtool_stats,
	.get_coalesce = enic_get_coalesce,
	.set_coalesce = enic_set_coalesce,
	.get_rxnfc = enic_get_rxnfc,
	.get_tunable = enic_get_tunable,
	.set_tunable = enic_set_tunable,
	.get_rxfh_key_size = enic_get_rxfh_key_size,
	.get_rxfh = enic_get_rxfh,
	.set_rxfh = enic_set_rxfh,
	.get_link_ksettings = enic_get_ksettings,
	.get_ts_info = enic_get_ts_info,
पूर्ण;

व्योम enic_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &enic_ethtool_ops;
पूर्ण
