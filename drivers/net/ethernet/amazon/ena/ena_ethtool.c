<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>

#समावेश "ena_netdev.h"

काष्ठा ena_stats अणु
	अक्षर name[ETH_GSTRING_LEN];
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा ENA_STAT_ENA_COM_ENTRY(stat) अणु \
	.name = #stat, \
	.stat_offset = दुरत्व(काष्ठा ena_com_stats_admin, stat) / माप(u64) \
पूर्ण

#घोषणा ENA_STAT_ENTRY(stat, stat_type) अणु \
	.name = #stat, \
	.stat_offset = दुरत्व(काष्ठा ena_stats_##stat_type, stat) / माप(u64) \
पूर्ण

#घोषणा ENA_STAT_HW_ENTRY(stat, stat_type) अणु \
	.name = #stat, \
	.stat_offset = दुरत्व(काष्ठा ena_admin_##stat_type, stat) / माप(u64) \
पूर्ण

#घोषणा ENA_STAT_RX_ENTRY(stat) \
	ENA_STAT_ENTRY(stat, rx)

#घोषणा ENA_STAT_TX_ENTRY(stat) \
	ENA_STAT_ENTRY(stat, tx)

#घोषणा ENA_STAT_GLOBAL_ENTRY(stat) \
	ENA_STAT_ENTRY(stat, dev)

#घोषणा ENA_STAT_ENI_ENTRY(stat) \
	ENA_STAT_HW_ENTRY(stat, eni_stats)

अटल स्थिर काष्ठा ena_stats ena_stats_global_strings[] = अणु
	ENA_STAT_GLOBAL_ENTRY(tx_समयout),
	ENA_STAT_GLOBAL_ENTRY(suspend),
	ENA_STAT_GLOBAL_ENTRY(resume),
	ENA_STAT_GLOBAL_ENTRY(wd_expired),
	ENA_STAT_GLOBAL_ENTRY(पूर्णांकerface_up),
	ENA_STAT_GLOBAL_ENTRY(पूर्णांकerface_करोwn),
	ENA_STAT_GLOBAL_ENTRY(admin_q_छोड़ो),
पूर्ण;

अटल स्थिर काष्ठा ena_stats ena_stats_eni_strings[] = अणु
	ENA_STAT_ENI_ENTRY(bw_in_allowance_exceeded),
	ENA_STAT_ENI_ENTRY(bw_out_allowance_exceeded),
	ENA_STAT_ENI_ENTRY(pps_allowance_exceeded),
	ENA_STAT_ENI_ENTRY(conntrack_allowance_exceeded),
	ENA_STAT_ENI_ENTRY(linklocal_allowance_exceeded),
पूर्ण;

अटल स्थिर काष्ठा ena_stats ena_stats_tx_strings[] = अणु
	ENA_STAT_TX_ENTRY(cnt),
	ENA_STAT_TX_ENTRY(bytes),
	ENA_STAT_TX_ENTRY(queue_stop),
	ENA_STAT_TX_ENTRY(queue_wakeup),
	ENA_STAT_TX_ENTRY(dma_mapping_err),
	ENA_STAT_TX_ENTRY(linearize),
	ENA_STAT_TX_ENTRY(linearize_failed),
	ENA_STAT_TX_ENTRY(napi_comp),
	ENA_STAT_TX_ENTRY(tx_poll),
	ENA_STAT_TX_ENTRY(करोorbells),
	ENA_STAT_TX_ENTRY(prepare_ctx_err),
	ENA_STAT_TX_ENTRY(bad_req_id),
	ENA_STAT_TX_ENTRY(llq_buffer_copy),
	ENA_STAT_TX_ENTRY(missed_tx),
	ENA_STAT_TX_ENTRY(unmask_पूर्णांकerrupt),
पूर्ण;

अटल स्थिर काष्ठा ena_stats ena_stats_rx_strings[] = अणु
	ENA_STAT_RX_ENTRY(cnt),
	ENA_STAT_RX_ENTRY(bytes),
	ENA_STAT_RX_ENTRY(rx_copyअवरोध_pkt),
	ENA_STAT_RX_ENTRY(csum_good),
	ENA_STAT_RX_ENTRY(refil_partial),
	ENA_STAT_RX_ENTRY(bad_csum),
	ENA_STAT_RX_ENTRY(page_alloc_fail),
	ENA_STAT_RX_ENTRY(skb_alloc_fail),
	ENA_STAT_RX_ENTRY(dma_mapping_err),
	ENA_STAT_RX_ENTRY(bad_desc_num),
	ENA_STAT_RX_ENTRY(bad_req_id),
	ENA_STAT_RX_ENTRY(empty_rx_ring),
	ENA_STAT_RX_ENTRY(csum_unchecked),
	ENA_STAT_RX_ENTRY(xdp_पातed),
	ENA_STAT_RX_ENTRY(xdp_drop),
	ENA_STAT_RX_ENTRY(xdp_pass),
	ENA_STAT_RX_ENTRY(xdp_tx),
	ENA_STAT_RX_ENTRY(xdp_invalid),
	ENA_STAT_RX_ENTRY(xdp_redirect),
पूर्ण;

अटल स्थिर काष्ठा ena_stats ena_stats_ena_com_strings[] = अणु
	ENA_STAT_ENA_COM_ENTRY(पातed_cmd),
	ENA_STAT_ENA_COM_ENTRY(submitted_cmd),
	ENA_STAT_ENA_COM_ENTRY(completed_cmd),
	ENA_STAT_ENA_COM_ENTRY(out_of_space),
	ENA_STAT_ENA_COM_ENTRY(no_completion),
पूर्ण;

#घोषणा ENA_STATS_ARRAY_GLOBAL		ARRAY_SIZE(ena_stats_global_strings)
#घोषणा ENA_STATS_ARRAY_TX		ARRAY_SIZE(ena_stats_tx_strings)
#घोषणा ENA_STATS_ARRAY_RX		ARRAY_SIZE(ena_stats_rx_strings)
#घोषणा ENA_STATS_ARRAY_ENA_COM		ARRAY_SIZE(ena_stats_ena_com_strings)
#घोषणा ENA_STATS_ARRAY_ENI(adapter)	\
	(ARRAY_SIZE(ena_stats_eni_strings) * (adapter)->eni_stats_supported)

अटल व्योम ena_safe_update_stat(u64 *src, u64 *dst,
				 काष्ठा u64_stats_sync *syncp)
अणु
	अचिन्हित पूर्णांक start;

	करो अणु
		start = u64_stats_fetch_begin_irq(syncp);
		*(dst) = *src;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(syncp, start));
पूर्ण

अटल व्योम ena_queue_stats(काष्ठा ena_adapter *adapter, u64 **data)
अणु
	स्थिर काष्ठा ena_stats *ena_stats;
	काष्ठा ena_ring *ring;

	u64 *ptr;
	पूर्णांक i, j;

	क्रम (i = 0; i < adapter->num_io_queues + adapter->xdp_num_queues; i++) अणु
		/* Tx stats */
		ring = &adapter->tx_ring[i];

		क्रम (j = 0; j < ENA_STATS_ARRAY_TX; j++) अणु
			ena_stats = &ena_stats_tx_strings[j];

			ptr = (u64 *)&ring->tx_stats + ena_stats->stat_offset;

			ena_safe_update_stat(ptr, (*data)++, &ring->syncp);
		पूर्ण
		/* XDP TX queues करोn't have a RX queue counterpart */
		अगर (!ENA_IS_XDP_INDEX(adapter, i)) अणु
			/* Rx stats */
			ring = &adapter->rx_ring[i];

			क्रम (j = 0; j < ENA_STATS_ARRAY_RX; j++) अणु
				ena_stats = &ena_stats_rx_strings[j];

				ptr = (u64 *)&ring->rx_stats +
					ena_stats->stat_offset;

				ena_safe_update_stat(ptr, (*data)++, &ring->syncp);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ena_dev_admin_queue_stats(काष्ठा ena_adapter *adapter, u64 **data)
अणु
	स्थिर काष्ठा ena_stats *ena_stats;
	u64 *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < ENA_STATS_ARRAY_ENA_COM; i++) अणु
		ena_stats = &ena_stats_ena_com_strings[i];

		ptr = (u64 *)&adapter->ena_dev->admin_queue.stats +
			ena_stats->stat_offset;

		*(*data)++ = *ptr;
	पूर्ण
पूर्ण

अटल व्योम ena_get_stats(काष्ठा ena_adapter *adapter,
			  u64 *data,
			  bool eni_stats_needed)
अणु
	स्थिर काष्ठा ena_stats *ena_stats;
	u64 *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < ENA_STATS_ARRAY_GLOBAL; i++) अणु
		ena_stats = &ena_stats_global_strings[i];

		ptr = (u64 *)&adapter->dev_stats + ena_stats->stat_offset;

		ena_safe_update_stat(ptr, data++, &adapter->syncp);
	पूर्ण

	अगर (eni_stats_needed) अणु
		ena_update_hw_stats(adapter);
		क्रम (i = 0; i < ENA_STATS_ARRAY_ENI(adapter); i++) अणु
			ena_stats = &ena_stats_eni_strings[i];

			ptr = (u64 *)&adapter->eni_stats +
				ena_stats->stat_offset;

			ena_safe_update_stat(ptr, data++, &adapter->syncp);
		पूर्ण
	पूर्ण

	ena_queue_stats(adapter, &data);
	ena_dev_admin_queue_stats(adapter, &data);
पूर्ण

अटल व्योम ena_get_ethtool_stats(काष्ठा net_device *netdev,
				  काष्ठा ethtool_stats *stats,
				  u64 *data)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);

	ena_get_stats(adapter, data, adapter->eni_stats_supported);
पूर्ण

अटल पूर्णांक ena_get_sw_stats_count(काष्ठा ena_adapter *adapter)
अणु
	वापस adapter->num_io_queues * (ENA_STATS_ARRAY_TX + ENA_STATS_ARRAY_RX)
		+ adapter->xdp_num_queues * ENA_STATS_ARRAY_TX
		+ ENA_STATS_ARRAY_GLOBAL + ENA_STATS_ARRAY_ENA_COM;
पूर्ण

अटल पूर्णांक ena_get_hw_stats_count(काष्ठा ena_adapter *adapter)
अणु
	वापस ENA_STATS_ARRAY_ENI(adapter);
पूर्ण

पूर्णांक ena_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);

	अगर (sset != ETH_SS_STATS)
		वापस -EOPNOTSUPP;

	वापस ena_get_sw_stats_count(adapter) + ena_get_hw_stats_count(adapter);
पूर्ण

अटल व्योम ena_queue_strings(काष्ठा ena_adapter *adapter, u8 **data)
अणु
	स्थिर काष्ठा ena_stats *ena_stats;
	bool is_xdp;
	पूर्णांक i, j;

	क्रम (i = 0; i < adapter->num_io_queues + adapter->xdp_num_queues; i++) अणु
		is_xdp = ENA_IS_XDP_INDEX(adapter, i);
		/* Tx stats */
		क्रम (j = 0; j < ENA_STATS_ARRAY_TX; j++) अणु
			ena_stats = &ena_stats_tx_strings[j];

			ethtool_प्र_लिखो(data,
					"queue_%u_%s_%s", i,
					is_xdp ? "xdp_tx" : "tx",
					ena_stats->name);
		पूर्ण

		अगर (!is_xdp) अणु
			/* RX stats, in XDP there isn't a RX queue
			 * counterpart
			 */
			क्रम (j = 0; j < ENA_STATS_ARRAY_RX; j++) अणु
				ena_stats = &ena_stats_rx_strings[j];

				ethtool_प्र_लिखो(data,
						"queue_%u_rx_%s", i,
						ena_stats->name);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ena_com_dev_strings(u8 **data)
अणु
	स्थिर काष्ठा ena_stats *ena_stats;
	पूर्णांक i;

	क्रम (i = 0; i < ENA_STATS_ARRAY_ENA_COM; i++) अणु
		ena_stats = &ena_stats_ena_com_strings[i];

		ethtool_प्र_लिखो(data,
				"ena_admin_q_%s", ena_stats->name);
	पूर्ण
पूर्ण

अटल व्योम ena_get_strings(काष्ठा ena_adapter *adapter,
			    u8 *data,
			    bool eni_stats_needed)
अणु
	स्थिर काष्ठा ena_stats *ena_stats;
	पूर्णांक i;

	क्रम (i = 0; i < ENA_STATS_ARRAY_GLOBAL; i++) अणु
		ena_stats = &ena_stats_global_strings[i];
		ethtool_प्र_लिखो(&data, ena_stats->name);
	पूर्ण

	अगर (eni_stats_needed) अणु
		क्रम (i = 0; i < ENA_STATS_ARRAY_ENI(adapter); i++) अणु
			ena_stats = &ena_stats_eni_strings[i];
			ethtool_प्र_लिखो(&data, ena_stats->name);
		पूर्ण
	पूर्ण

	ena_queue_strings(adapter, &data);
	ena_com_dev_strings(&data);
पूर्ण

अटल व्योम ena_get_ethtool_strings(काष्ठा net_device *netdev,
				    u32 sset,
				    u8 *data)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);

	अगर (sset != ETH_SS_STATS)
		वापस;

	ena_get_strings(adapter, data, adapter->eni_stats_supported);
पूर्ण

अटल पूर्णांक ena_get_link_ksettings(काष्ठा net_device *netdev,
				  काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	काष्ठा ena_admin_get_feature_link_desc *link;
	काष्ठा ena_admin_get_feat_resp feat_resp;
	पूर्णांक rc;

	rc = ena_com_get_link_params(ena_dev, &feat_resp);
	अगर (rc)
		वापस rc;

	link = &feat_resp.u.link;
	link_ksettings->base.speed = link->speed;

	अगर (link->flags & ENA_ADMIN_GET_FEATURE_LINK_DESC_AUTONEG_MASK) अणु
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Autoneg);
	पूर्ण

	link_ksettings->base.स्वतःneg =
		(link->flags & ENA_ADMIN_GET_FEATURE_LINK_DESC_AUTONEG_MASK) ?
		AUTONEG_ENABLE : AUTONEG_DISABLE;

	link_ksettings->base.duplex = DUPLEX_FULL;

	वापस 0;
पूर्ण

अटल पूर्णांक ena_get_coalesce(काष्ठा net_device *net_dev,
			    काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(net_dev);
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;

	अगर (!ena_com_पूर्णांकerrupt_moderation_supported(ena_dev))
		वापस -EOPNOTSUPP;

	coalesce->tx_coalesce_usecs =
		ena_com_get_nonadaptive_moderation_पूर्णांकerval_tx(ena_dev) *
			ena_dev->पूर्णांकr_delay_resolution;

	coalesce->rx_coalesce_usecs =
		ena_com_get_nonadaptive_moderation_पूर्णांकerval_rx(ena_dev)
		* ena_dev->पूर्णांकr_delay_resolution;

	coalesce->use_adaptive_rx_coalesce =
		ena_com_get_adaptive_moderation_enabled(ena_dev);

	वापस 0;
पूर्ण

अटल व्योम ena_update_tx_rings_nonadaptive_पूर्णांकr_moderation(काष्ठा ena_adapter *adapter)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	val = ena_com_get_nonadaptive_moderation_पूर्णांकerval_tx(adapter->ena_dev);

	क्रम (i = 0; i < adapter->num_io_queues; i++)
		adapter->tx_ring[i].smoothed_पूर्णांकerval = val;
पूर्ण

अटल व्योम ena_update_rx_rings_nonadaptive_पूर्णांकr_moderation(काष्ठा ena_adapter *adapter)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	val = ena_com_get_nonadaptive_moderation_पूर्णांकerval_rx(adapter->ena_dev);

	क्रम (i = 0; i < adapter->num_io_queues; i++)
		adapter->rx_ring[i].smoothed_पूर्णांकerval = val;
पूर्ण

अटल पूर्णांक ena_set_coalesce(काष्ठा net_device *net_dev,
			    काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(net_dev);
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	पूर्णांक rc;

	अगर (!ena_com_पूर्णांकerrupt_moderation_supported(ena_dev))
		वापस -EOPNOTSUPP;

	rc = ena_com_update_nonadaptive_moderation_पूर्णांकerval_tx(ena_dev,
							       coalesce->tx_coalesce_usecs);
	अगर (rc)
		वापस rc;

	ena_update_tx_rings_nonadaptive_पूर्णांकr_moderation(adapter);

	rc = ena_com_update_nonadaptive_moderation_पूर्णांकerval_rx(ena_dev,
							       coalesce->rx_coalesce_usecs);
	अगर (rc)
		वापस rc;

	ena_update_rx_rings_nonadaptive_पूर्णांकr_moderation(adapter);

	अगर (coalesce->use_adaptive_rx_coalesce &&
	    !ena_com_get_adaptive_moderation_enabled(ena_dev))
		ena_com_enable_adaptive_moderation(ena_dev);

	अगर (!coalesce->use_adaptive_rx_coalesce &&
	    ena_com_get_adaptive_moderation_enabled(ena_dev))
		ena_com_disable_adaptive_moderation(ena_dev);

	वापस 0;
पूर्ण

अटल u32 ena_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);

	वापस adapter->msg_enable;
पूर्ण

अटल व्योम ena_set_msglevel(काष्ठा net_device *netdev, u32 value)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);

	adapter->msg_enable = value;
पूर्ण

अटल व्योम ena_get_drvinfo(काष्ठा net_device *dev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(dev);

	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(adapter->pdev),
		माप(info->bus_info));
पूर्ण

अटल व्योम ena_get_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);

	ring->tx_max_pending = adapter->max_tx_ring_size;
	ring->rx_max_pending = adapter->max_rx_ring_size;
	ring->tx_pending = adapter->tx_ring[0].ring_size;
	ring->rx_pending = adapter->rx_ring[0].ring_size;
पूर्ण

अटल पूर्णांक ena_set_ringparam(काष्ठा net_device *netdev,
			     काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	u32 new_tx_size, new_rx_size;

	new_tx_size = ring->tx_pending < ENA_MIN_RING_SIZE ?
			ENA_MIN_RING_SIZE : ring->tx_pending;
	new_tx_size = roundकरोwn_घात_of_two(new_tx_size);

	new_rx_size = ring->rx_pending < ENA_MIN_RING_SIZE ?
			ENA_MIN_RING_SIZE : ring->rx_pending;
	new_rx_size = roundकरोwn_घात_of_two(new_rx_size);

	अगर (new_tx_size == adapter->requested_tx_ring_size &&
	    new_rx_size == adapter->requested_rx_ring_size)
		वापस 0;

	वापस ena_update_queue_sizes(adapter, new_tx_size, new_rx_size);
पूर्ण

अटल u32 ena_flow_hash_to_flow_type(u16 hash_fields)
अणु
	u32 data = 0;

	अगर (hash_fields & ENA_ADMIN_RSS_L2_DA)
		data |= RXH_L2DA;

	अगर (hash_fields & ENA_ADMIN_RSS_L3_DA)
		data |= RXH_IP_DST;

	अगर (hash_fields & ENA_ADMIN_RSS_L3_SA)
		data |= RXH_IP_SRC;

	अगर (hash_fields & ENA_ADMIN_RSS_L4_DP)
		data |= RXH_L4_B_2_3;

	अगर (hash_fields & ENA_ADMIN_RSS_L4_SP)
		data |= RXH_L4_B_0_1;

	वापस data;
पूर्ण

अटल u16 ena_flow_data_to_flow_hash(u32 hash_fields)
अणु
	u16 data = 0;

	अगर (hash_fields & RXH_L2DA)
		data |= ENA_ADMIN_RSS_L2_DA;

	अगर (hash_fields & RXH_IP_DST)
		data |= ENA_ADMIN_RSS_L3_DA;

	अगर (hash_fields & RXH_IP_SRC)
		data |= ENA_ADMIN_RSS_L3_SA;

	अगर (hash_fields & RXH_L4_B_2_3)
		data |= ENA_ADMIN_RSS_L4_DP;

	अगर (hash_fields & RXH_L4_B_0_1)
		data |= ENA_ADMIN_RSS_L4_SP;

	वापस data;
पूर्ण

अटल पूर्णांक ena_get_rss_hash(काष्ठा ena_com_dev *ena_dev,
			    काष्ठा ethtool_rxnfc *cmd)
अणु
	क्रमागत ena_admin_flow_hash_proto proto;
	u16 hash_fields;
	पूर्णांक rc;

	cmd->data = 0;

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		proto = ENA_ADMIN_RSS_TCP4;
		अवरोध;
	हाल UDP_V4_FLOW:
		proto = ENA_ADMIN_RSS_UDP4;
		अवरोध;
	हाल TCP_V6_FLOW:
		proto = ENA_ADMIN_RSS_TCP6;
		अवरोध;
	हाल UDP_V6_FLOW:
		proto = ENA_ADMIN_RSS_UDP6;
		अवरोध;
	हाल IPV4_FLOW:
		proto = ENA_ADMIN_RSS_IP4;
		अवरोध;
	हाल IPV6_FLOW:
		proto = ENA_ADMIN_RSS_IP6;
		अवरोध;
	हाल ETHER_FLOW:
		proto = ENA_ADMIN_RSS_NOT_IP;
		अवरोध;
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rc = ena_com_get_hash_ctrl(ena_dev, proto, &hash_fields);
	अगर (rc)
		वापस rc;

	cmd->data = ena_flow_hash_to_flow_type(hash_fields);

	वापस 0;
पूर्ण

अटल पूर्णांक ena_set_rss_hash(काष्ठा ena_com_dev *ena_dev,
			    काष्ठा ethtool_rxnfc *cmd)
अणु
	क्रमागत ena_admin_flow_hash_proto proto;
	u16 hash_fields;

	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		proto = ENA_ADMIN_RSS_TCP4;
		अवरोध;
	हाल UDP_V4_FLOW:
		proto = ENA_ADMIN_RSS_UDP4;
		अवरोध;
	हाल TCP_V6_FLOW:
		proto = ENA_ADMIN_RSS_TCP6;
		अवरोध;
	हाल UDP_V6_FLOW:
		proto = ENA_ADMIN_RSS_UDP6;
		अवरोध;
	हाल IPV4_FLOW:
		proto = ENA_ADMIN_RSS_IP4;
		अवरोध;
	हाल IPV6_FLOW:
		proto = ENA_ADMIN_RSS_IP6;
		अवरोध;
	हाल ETHER_FLOW:
		proto = ENA_ADMIN_RSS_NOT_IP;
		अवरोध;
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EINVAL;
	पूर्ण

	hash_fields = ena_flow_data_to_flow_hash(cmd->data);

	वापस ena_com_fill_hash_ctrl(ena_dev, proto, hash_fields);
पूर्ण

अटल पूर्णांक ena_set_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc = 0;

	चयन (info->cmd) अणु
	हाल ETHTOOL_SRXFH:
		rc = ena_set_rss_hash(adapter->ena_dev, info);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
	हाल ETHTOOL_SRXCLSRLINS:
	शेष:
		netअगर_err(adapter, drv, netdev,
			  "Command parameter %d is not supported\n", info->cmd);
		rc = -EOPNOTSUPP;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक ena_get_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *info,
			 u32 *rules)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc = 0;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = adapter->num_io_queues;
		rc = 0;
		अवरोध;
	हाल ETHTOOL_GRXFH:
		rc = ena_get_rss_hash(adapter->ena_dev, info);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
	हाल ETHTOOL_GRXCLSRULE:
	हाल ETHTOOL_GRXCLSRLALL:
	शेष:
		netअगर_err(adapter, drv, netdev,
			  "Command parameter %d is not supported\n", info->cmd);
		rc = -EOPNOTSUPP;
	पूर्ण

	वापस rc;
पूर्ण

अटल u32 ena_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	वापस ENA_RX_RSS_TABLE_SIZE;
पूर्ण

अटल u32 ena_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस ENA_HASH_KEY_SIZE;
पूर्ण

अटल पूर्णांक ena_indirection_table_set(काष्ठा ena_adapter *adapter,
				     स्थिर u32 *indir)
अणु
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	पूर्णांक i, rc;

	क्रम (i = 0; i < ENA_RX_RSS_TABLE_SIZE; i++) अणु
		rc = ena_com_indirect_table_fill_entry(ena_dev,
						       i,
						       ENA_IO_RXQ_IDX(indir[i]));
		अगर (unlikely(rc)) अणु
			netअगर_err(adapter, drv, adapter->netdev,
				  "Cannot fill indirect table (index is too large)\n");
			वापस rc;
		पूर्ण
	पूर्ण

	rc = ena_com_indirect_table_set(ena_dev);
	अगर (rc) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "Cannot set indirect table\n");
		वापस rc == -EPERM ? -EOPNOTSUPP : rc;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक ena_indirection_table_get(काष्ठा ena_adapter *adapter, u32 *indir)
अणु
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	पूर्णांक i, rc;

	अगर (!indir)
		वापस 0;

	rc = ena_com_indirect_table_get(ena_dev, indir);
	अगर (rc)
		वापस rc;

	/* Our पूर्णांकernal representation of the indices is: even indices
	 * क्रम Tx and uneven indices क्रम Rx. We need to convert the Rx
	 * indices to be consecutive
	 */
	क्रम (i = 0; i < ENA_RX_RSS_TABLE_SIZE; i++)
		indir[i] = ENA_IO_RXQ_IDX_TO_COMBINED_IDX(indir[i]);

	वापस rc;
पूर्ण

अटल पूर्णांक ena_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			u8 *hfunc)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	क्रमागत ena_admin_hash_functions ena_func;
	u8 func;
	पूर्णांक rc;

	rc = ena_indirection_table_get(adapter, indir);
	अगर (rc)
		वापस rc;

	/* We call this function in order to check अगर the device
	 * supports getting/setting the hash function.
	 */
	rc = ena_com_get_hash_function(adapter->ena_dev, &ena_func);
	अगर (rc) अणु
		अगर (rc == -EOPNOTSUPP)
			rc = 0;

		वापस rc;
	पूर्ण

	rc = ena_com_get_hash_key(adapter->ena_dev, key);
	अगर (rc)
		वापस rc;

	चयन (ena_func) अणु
	हाल ENA_ADMIN_TOEPLITZ:
		func = ETH_RSS_HASH_TOP;
		अवरोध;
	हाल ENA_ADMIN_CRC32:
		func = ETH_RSS_HASH_CRC32;
		अवरोध;
	शेष:
		netअगर_err(adapter, drv, netdev,
			  "Command parameter is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (hfunc)
		*hfunc = func;

	वापस 0;
पूर्ण

अटल पूर्णांक ena_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	क्रमागत ena_admin_hash_functions func = 0;
	पूर्णांक rc;

	अगर (indir) अणु
		rc = ena_indirection_table_set(adapter, indir);
		अगर (rc)
			वापस rc;
	पूर्ण

	चयन (hfunc) अणु
	हाल ETH_RSS_HASH_NO_CHANGE:
		func = ena_com_get_current_hash_function(ena_dev);
		अवरोध;
	हाल ETH_RSS_HASH_TOP:
		func = ENA_ADMIN_TOEPLITZ;
		अवरोध;
	हाल ETH_RSS_HASH_CRC32:
		func = ENA_ADMIN_CRC32;
		अवरोध;
	शेष:
		netअगर_err(adapter, drv, netdev, "Unsupported hfunc %d\n",
			  hfunc);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (key || func) अणु
		rc = ena_com_fill_hash_function(ena_dev, func, key,
						ENA_HASH_KEY_SIZE,
						0xFFFFFFFF);
		अगर (unlikely(rc)) अणु
			netअगर_err(adapter, drv, netdev, "Cannot fill key\n");
			वापस rc == -EPERM ? -EOPNOTSUPP : rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ena_get_channels(काष्ठा net_device *netdev,
			     काष्ठा ethtool_channels *channels)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);

	channels->max_combined = adapter->max_num_io_queues;
	channels->combined_count = adapter->num_io_queues;
पूर्ण

अटल पूर्णांक ena_set_channels(काष्ठा net_device *netdev,
			    काष्ठा ethtool_channels *channels)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	u32 count = channels->combined_count;
	/* The check क्रम max value is alपढ़ोy करोne in ethtool */
	अगर (count < ENA_MIN_NUM_IO_QUEUES ||
	    (ena_xdp_present(adapter) &&
	    !ena_xdp_legal_queue_count(adapter, count)))
		वापस -EINVAL;

	वापस ena_update_queue_count(adapter, count);
पूर्ण

अटल पूर्णांक ena_get_tunable(काष्ठा net_device *netdev,
			   स्थिर काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = adapter->rx_copyअवरोध;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ena_set_tunable(काष्ठा net_device *netdev,
			   स्थिर काष्ठा ethtool_tunable *tuna,
			   स्थिर व्योम *data)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret = 0;
	u32 len;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		len = *(u32 *)data;
		अगर (len > adapter->netdev->mtu) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		adapter->rx_copyअवरोध = len;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ena_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_link_ksettings	= ena_get_link_ksettings,
	.get_drvinfo		= ena_get_drvinfo,
	.get_msglevel		= ena_get_msglevel,
	.set_msglevel		= ena_set_msglevel,
	.get_link		= ethtool_op_get_link,
	.get_coalesce		= ena_get_coalesce,
	.set_coalesce		= ena_set_coalesce,
	.get_ringparam		= ena_get_ringparam,
	.set_ringparam		= ena_set_ringparam,
	.get_sset_count         = ena_get_sset_count,
	.get_strings		= ena_get_ethtool_strings,
	.get_ethtool_stats      = ena_get_ethtool_stats,
	.get_rxnfc		= ena_get_rxnfc,
	.set_rxnfc		= ena_set_rxnfc,
	.get_rxfh_indir_size    = ena_get_rxfh_indir_size,
	.get_rxfh_key_size	= ena_get_rxfh_key_size,
	.get_rxfh		= ena_get_rxfh,
	.set_rxfh		= ena_set_rxfh,
	.get_channels		= ena_get_channels,
	.set_channels		= ena_set_channels,
	.get_tunable		= ena_get_tunable,
	.set_tunable		= ena_set_tunable,
	.get_ts_info            = ethtool_op_get_ts_info,
पूर्ण;

व्योम ena_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &ena_ethtool_ops;
पूर्ण

अटल व्योम ena_dump_stats_ex(काष्ठा ena_adapter *adapter, u8 *buf)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u8 *strings_buf;
	u64 *data_buf;
	पूर्णांक strings_num;
	पूर्णांक i, rc;

	strings_num = ena_get_sw_stats_count(adapter);
	अगर (strings_num <= 0) अणु
		netअगर_err(adapter, drv, netdev, "Can't get stats num\n");
		वापस;
	पूर्ण

	strings_buf = devm_kसुस्मृति(&adapter->pdev->dev,
				   ETH_GSTRING_LEN, strings_num,
				   GFP_ATOMIC);
	अगर (!strings_buf) अणु
		netअगर_err(adapter, drv, netdev,
			  "Failed to allocate strings_buf\n");
		वापस;
	पूर्ण

	data_buf = devm_kसुस्मृति(&adapter->pdev->dev,
				strings_num, माप(u64),
				GFP_ATOMIC);
	अगर (!data_buf) अणु
		netअगर_err(adapter, drv, netdev,
			  "Failed to allocate data buf\n");
		devm_kमुक्त(&adapter->pdev->dev, strings_buf);
		वापस;
	पूर्ण

	ena_get_strings(adapter, strings_buf, false);
	ena_get_stats(adapter, data_buf, false);

	/* If there is a buffer, dump stats, otherwise prपूर्णांक them to dmesg */
	अगर (buf)
		क्रम (i = 0; i < strings_num; i++) अणु
			rc = snम_लिखो(buf, ETH_GSTRING_LEN + माप(u64),
				      "%s %llu\n",
				      strings_buf + i * ETH_GSTRING_LEN,
				      data_buf[i]);
			buf += rc;
		पूर्ण
	अन्यथा
		क्रम (i = 0; i < strings_num; i++)
			netअगर_err(adapter, drv, netdev, "%s: %llu\n",
				  strings_buf + i * ETH_GSTRING_LEN,
				  data_buf[i]);

	devm_kमुक्त(&adapter->pdev->dev, strings_buf);
	devm_kमुक्त(&adapter->pdev->dev, data_buf);
पूर्ण

व्योम ena_dump_stats_to_buf(काष्ठा ena_adapter *adapter, u8 *buf)
अणु
	अगर (!buf)
		वापस;

	ena_dump_stats_ex(adapter, buf);
पूर्ण

व्योम ena_dump_stats_to_dmesg(काष्ठा ena_adapter *adapter)
अणु
	ena_dump_stats_ex(adapter, शून्य);
पूर्ण
