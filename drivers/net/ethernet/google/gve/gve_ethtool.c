<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Google भव Ethernet (gve) driver
 *
 * Copyright (C) 2015-2019 Google, Inc.
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/rtnetlink.h>
#समावेश "gve.h"
#समावेश "gve_adminq.h"

अटल व्योम gve_get_drvinfo(काष्ठा net_device *netdev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);

	strscpy(info->driver, "gve", माप(info->driver));
	strscpy(info->version, gve_version_str, माप(info->version));
	strscpy(info->bus_info, pci_name(priv->pdev), माप(info->bus_info));
पूर्ण

अटल व्योम gve_set_msglevel(काष्ठा net_device *netdev, u32 value)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);

	priv->msg_enable = value;
पूर्ण

अटल u32 gve_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);

	वापस priv->msg_enable;
पूर्ण

अटल स्थिर अक्षर gve_gstrings_मुख्य_stats[][ETH_GSTRING_LEN] = अणु
	"rx_packets", "tx_packets", "rx_bytes", "tx_bytes",
	"rx_dropped", "tx_dropped", "tx_timeouts",
	"rx_skb_alloc_fail", "rx_buf_alloc_fail", "rx_desc_err_dropped_pkt",
	"interface_up_cnt", "interface_down_cnt", "reset_cnt",
	"page_alloc_fail", "dma_mapping_error", "stats_report_trigger_cnt",
पूर्ण;

अटल स्थिर अक्षर gve_gstrings_rx_stats[][ETH_GSTRING_LEN] = अणु
	"rx_posted_desc[%u]", "rx_completed_desc[%u]", "rx_bytes[%u]",
	"rx_dropped_pkt[%u]", "rx_copybreak_pkt[%u]", "rx_copied_pkt[%u]",
	"rx_queue_drop_cnt[%u]", "rx_no_buffers_posted[%u]",
	"rx_drops_packet_over_mru[%u]", "rx_drops_invalid_checksum[%u]",
पूर्ण;

अटल स्थिर अक्षर gve_gstrings_tx_stats[][ETH_GSTRING_LEN] = अणु
	"tx_posted_desc[%u]", "tx_completed_desc[%u]", "tx_bytes[%u]",
	"tx_wake[%u]", "tx_stop[%u]", "tx_event_counter[%u]",
	"tx_dma_mapping_error[%u]",
पूर्ण;

अटल स्थिर अक्षर gve_gstrings_adminq_stats[][ETH_GSTRING_LEN] = अणु
	"adminq_prod_cnt", "adminq_cmd_fail", "adminq_timeouts",
	"adminq_describe_device_cnt", "adminq_cfg_device_resources_cnt",
	"adminq_register_page_list_cnt", "adminq_unregister_page_list_cnt",
	"adminq_create_tx_queue_cnt", "adminq_create_rx_queue_cnt",
	"adminq_destroy_tx_queue_cnt", "adminq_destroy_rx_queue_cnt",
	"adminq_dcfg_device_resources_cnt", "adminq_set_driver_parameter_cnt",
	"adminq_report_stats_cnt", "adminq_report_link_speed_cnt"
पूर्ण;

अटल स्थिर अक्षर gve_gstrings_priv_flags[][ETH_GSTRING_LEN] = अणु
	"report-stats",
पूर्ण;

#घोषणा GVE_MAIN_STATS_LEN  ARRAY_SIZE(gve_gstrings_मुख्य_stats)
#घोषणा GVE_ADMINQ_STATS_LEN  ARRAY_SIZE(gve_gstrings_adminq_stats)
#घोषणा NUM_GVE_TX_CNTS	ARRAY_SIZE(gve_gstrings_tx_stats)
#घोषणा NUM_GVE_RX_CNTS	ARRAY_SIZE(gve_gstrings_rx_stats)
#घोषणा GVE_PRIV_FLAGS_STR_LEN ARRAY_SIZE(gve_gstrings_priv_flags)

अटल व्योम gve_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);
	अक्षर *s = (अक्षर *)data;
	पूर्णांक i, j;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(s, *gve_gstrings_मुख्य_stats,
		       माप(gve_gstrings_मुख्य_stats));
		s += माप(gve_gstrings_मुख्य_stats);

		क्रम (i = 0; i < priv->rx_cfg.num_queues; i++) अणु
			क्रम (j = 0; j < NUM_GVE_RX_CNTS; j++) अणु
				snम_लिखो(s, ETH_GSTRING_LEN,
					 gve_gstrings_rx_stats[j], i);
				s += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < priv->tx_cfg.num_queues; i++) अणु
			क्रम (j = 0; j < NUM_GVE_TX_CNTS; j++) अणु
				snम_लिखो(s, ETH_GSTRING_LEN,
					 gve_gstrings_tx_stats[j], i);
				s += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण

		स_नकल(s, *gve_gstrings_adminq_stats,
		       माप(gve_gstrings_adminq_stats));
		s += माप(gve_gstrings_adminq_stats);
		अवरोध;

	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(s, *gve_gstrings_priv_flags,
		       माप(gve_gstrings_priv_flags));
		s += माप(gve_gstrings_priv_flags);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक gve_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस GVE_MAIN_STATS_LEN + GVE_ADMINQ_STATS_LEN +
		       (priv->rx_cfg.num_queues * NUM_GVE_RX_CNTS) +
		       (priv->tx_cfg.num_queues * NUM_GVE_TX_CNTS);
	हाल ETH_SS_PRIV_FLAGS:
		वापस GVE_PRIV_FLAGS_STR_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम
gve_get_ethtool_stats(काष्ठा net_device *netdev,
		      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	u64 पंचांगp_rx_pkts, पंचांगp_rx_bytes, पंचांगp_rx_skb_alloc_fail,	पंचांगp_rx_buf_alloc_fail,
		पंचांगp_rx_desc_err_dropped_pkt, पंचांगp_tx_pkts, पंचांगp_tx_bytes;
	u64 rx_buf_alloc_fail, rx_desc_err_dropped_pkt, rx_pkts,
		rx_skb_alloc_fail, rx_bytes, tx_pkts, tx_bytes;
	पूर्णांक stats_idx, base_stats_idx, max_stats_idx;
	काष्ठा stats *report_stats;
	पूर्णांक *rx_qid_to_stats_idx;
	पूर्णांक *tx_qid_to_stats_idx;
	काष्ठा gve_priv *priv;
	bool skip_nic_stats;
	अचिन्हित पूर्णांक start;
	पूर्णांक ring;
	पूर्णांक i, j;

	ASSERT_RTNL();

	priv = netdev_priv(netdev);
	report_stats = priv->stats_report->stats;
	rx_qid_to_stats_idx = kदो_स्मृति_array(priv->rx_cfg.num_queues,
					    माप(पूर्णांक), GFP_KERNEL);
	अगर (!rx_qid_to_stats_idx)
		वापस;
	tx_qid_to_stats_idx = kदो_स्मृति_array(priv->tx_cfg.num_queues,
					    माप(पूर्णांक), GFP_KERNEL);
	अगर (!tx_qid_to_stats_idx) अणु
		kमुक्त(rx_qid_to_stats_idx);
		वापस;
	पूर्ण
	क्रम (rx_pkts = 0, rx_bytes = 0, rx_skb_alloc_fail = 0,
	     rx_buf_alloc_fail = 0, rx_desc_err_dropped_pkt = 0, ring = 0;
	     ring < priv->rx_cfg.num_queues; ring++) अणु
		अगर (priv->rx) अणु
			करो अणु
				काष्ठा gve_rx_ring *rx = &priv->rx[ring];

				start =
				  u64_stats_fetch_begin(&priv->rx[ring].statss);
				पंचांगp_rx_pkts = rx->rpackets;
				पंचांगp_rx_bytes = rx->rbytes;
				पंचांगp_rx_skb_alloc_fail = rx->rx_skb_alloc_fail;
				पंचांगp_rx_buf_alloc_fail = rx->rx_buf_alloc_fail;
				पंचांगp_rx_desc_err_dropped_pkt =
					rx->rx_desc_err_dropped_pkt;
			पूर्ण जबतक (u64_stats_fetch_retry(&priv->rx[ring].statss,
						       start));
			rx_pkts += पंचांगp_rx_pkts;
			rx_bytes += पंचांगp_rx_bytes;
			rx_skb_alloc_fail += पंचांगp_rx_skb_alloc_fail;
			rx_buf_alloc_fail += पंचांगp_rx_buf_alloc_fail;
			rx_desc_err_dropped_pkt += पंचांगp_rx_desc_err_dropped_pkt;
		पूर्ण
	पूर्ण
	क्रम (tx_pkts = 0, tx_bytes = 0, ring = 0;
	     ring < priv->tx_cfg.num_queues; ring++) अणु
		अगर (priv->tx) अणु
			करो अणु
				start =
				  u64_stats_fetch_begin(&priv->tx[ring].statss);
				पंचांगp_tx_pkts = priv->tx[ring].pkt_करोne;
				पंचांगp_tx_bytes = priv->tx[ring].bytes_करोne;
			पूर्ण जबतक (u64_stats_fetch_retry(&priv->tx[ring].statss,
						       start));
			tx_pkts += पंचांगp_tx_pkts;
			tx_bytes += पंचांगp_tx_bytes;
		पूर्ण
	पूर्ण

	i = 0;
	data[i++] = rx_pkts;
	data[i++] = tx_pkts;
	data[i++] = rx_bytes;
	data[i++] = tx_bytes;
	/* total rx dropped packets */
	data[i++] = rx_skb_alloc_fail + rx_buf_alloc_fail +
		    rx_desc_err_dropped_pkt;
	/* Skip tx_dropped */
	i++;

	data[i++] = priv->tx_समयo_cnt;
	data[i++] = rx_skb_alloc_fail;
	data[i++] = rx_buf_alloc_fail;
	data[i++] = rx_desc_err_dropped_pkt;
	data[i++] = priv->पूर्णांकerface_up_cnt;
	data[i++] = priv->पूर्णांकerface_करोwn_cnt;
	data[i++] = priv->reset_cnt;
	data[i++] = priv->page_alloc_fail;
	data[i++] = priv->dma_mapping_error;
	data[i++] = priv->stats_report_trigger_cnt;
	i = GVE_MAIN_STATS_LEN;

	/* For rx cross-reporting stats, start from nic rx stats in report */
	base_stats_idx = GVE_TX_STATS_REPORT_NUM * priv->tx_cfg.num_queues +
		GVE_RX_STATS_REPORT_NUM * priv->rx_cfg.num_queues;
	max_stats_idx = NIC_RX_STATS_REPORT_NUM * priv->rx_cfg.num_queues +
		base_stats_idx;
	/* Preprocess the stats report क्रम rx, map queue id to start index */
	skip_nic_stats = false;
	क्रम (stats_idx = base_stats_idx; stats_idx < max_stats_idx;
		stats_idx += NIC_RX_STATS_REPORT_NUM) अणु
		u32 stat_name = be32_to_cpu(report_stats[stats_idx].stat_name);
		u32 queue_id = be32_to_cpu(report_stats[stats_idx].queue_id);

		अगर (stat_name == 0) अणु
			/* no stats written by NIC yet */
			skip_nic_stats = true;
			अवरोध;
		पूर्ण
		rx_qid_to_stats_idx[queue_id] = stats_idx;
	पूर्ण
	/* walk RX rings */
	अगर (priv->rx) अणु
		क्रम (ring = 0; ring < priv->rx_cfg.num_queues; ring++) अणु
			काष्ठा gve_rx_ring *rx = &priv->rx[ring];

			data[i++] = rx->fill_cnt;
			data[i++] = rx->cnt;
			करो अणु
				start =
				  u64_stats_fetch_begin(&priv->rx[ring].statss);
				पंचांगp_rx_bytes = rx->rbytes;
				पंचांगp_rx_skb_alloc_fail = rx->rx_skb_alloc_fail;
				पंचांगp_rx_buf_alloc_fail = rx->rx_buf_alloc_fail;
				पंचांगp_rx_desc_err_dropped_pkt =
					rx->rx_desc_err_dropped_pkt;
			पूर्ण जबतक (u64_stats_fetch_retry(&priv->rx[ring].statss,
						       start));
			data[i++] = पंचांगp_rx_bytes;
			/* rx dropped packets */
			data[i++] = पंचांगp_rx_skb_alloc_fail +
				पंचांगp_rx_buf_alloc_fail +
				पंचांगp_rx_desc_err_dropped_pkt;
			data[i++] = rx->rx_copyअवरोध_pkt;
			data[i++] = rx->rx_copied_pkt;
			/* stats from NIC */
			अगर (skip_nic_stats) अणु
				/* skip NIC rx stats */
				i += NIC_RX_STATS_REPORT_NUM;
				जारी;
			पूर्ण
			क्रम (j = 0; j < NIC_RX_STATS_REPORT_NUM; j++) अणु
				u64 value =
				be64_to_cpu(report_stats[rx_qid_to_stats_idx[ring] + j].value);

				data[i++] = value;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		i += priv->rx_cfg.num_queues * NUM_GVE_RX_CNTS;
	पूर्ण

	/* For tx cross-reporting stats, start from nic tx stats in report */
	base_stats_idx = max_stats_idx;
	max_stats_idx = NIC_TX_STATS_REPORT_NUM * priv->tx_cfg.num_queues +
		max_stats_idx;
	/* Preprocess the stats report क्रम tx, map queue id to start index */
	skip_nic_stats = false;
	क्रम (stats_idx = base_stats_idx; stats_idx < max_stats_idx;
		stats_idx += NIC_TX_STATS_REPORT_NUM) अणु
		u32 stat_name = be32_to_cpu(report_stats[stats_idx].stat_name);
		u32 queue_id = be32_to_cpu(report_stats[stats_idx].queue_id);

		अगर (stat_name == 0) अणु
			/* no stats written by NIC yet */
			skip_nic_stats = true;
			अवरोध;
		पूर्ण
		tx_qid_to_stats_idx[queue_id] = stats_idx;
	पूर्ण
	/* walk TX rings */
	अगर (priv->tx) अणु
		क्रम (ring = 0; ring < priv->tx_cfg.num_queues; ring++) अणु
			काष्ठा gve_tx_ring *tx = &priv->tx[ring];

			data[i++] = tx->req;
			data[i++] = tx->करोne;
			करो अणु
				start =
				  u64_stats_fetch_begin(&priv->tx[ring].statss);
				पंचांगp_tx_bytes = tx->bytes_करोne;
			पूर्ण जबतक (u64_stats_fetch_retry(&priv->tx[ring].statss,
						       start));
			data[i++] = पंचांगp_tx_bytes;
			data[i++] = tx->wake_queue;
			data[i++] = tx->stop_queue;
			data[i++] = be32_to_cpu(gve_tx_load_event_counter(priv,
									  tx));
			data[i++] = tx->dma_mapping_error;
			/* stats from NIC */
			अगर (skip_nic_stats) अणु
				/* skip NIC tx stats */
				i += NIC_TX_STATS_REPORT_NUM;
				जारी;
			पूर्ण
			क्रम (j = 0; j < NIC_TX_STATS_REPORT_NUM; j++) अणु
				u64 value =
				be64_to_cpu(report_stats[tx_qid_to_stats_idx[ring] + j].value);
				data[i++] = value;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		i += priv->tx_cfg.num_queues * NUM_GVE_TX_CNTS;
	पूर्ण

	kमुक्त(rx_qid_to_stats_idx);
	kमुक्त(tx_qid_to_stats_idx);
	/* AQ Stats */
	data[i++] = priv->adminq_prod_cnt;
	data[i++] = priv->adminq_cmd_fail;
	data[i++] = priv->adminq_समयouts;
	data[i++] = priv->adminq_describe_device_cnt;
	data[i++] = priv->adminq_cfg_device_resources_cnt;
	data[i++] = priv->adminq_रेजिस्टर_page_list_cnt;
	data[i++] = priv->adminq_unरेजिस्टर_page_list_cnt;
	data[i++] = priv->adminq_create_tx_queue_cnt;
	data[i++] = priv->adminq_create_rx_queue_cnt;
	data[i++] = priv->adminq_destroy_tx_queue_cnt;
	data[i++] = priv->adminq_destroy_rx_queue_cnt;
	data[i++] = priv->adminq_dcfg_device_resources_cnt;
	data[i++] = priv->adminq_set_driver_parameter_cnt;
	data[i++] = priv->adminq_report_stats_cnt;
	data[i++] = priv->adminq_report_link_speed_cnt;
पूर्ण

अटल व्योम gve_get_channels(काष्ठा net_device *netdev,
			     काष्ठा ethtool_channels *cmd)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);

	cmd->max_rx = priv->rx_cfg.max_queues;
	cmd->max_tx = priv->tx_cfg.max_queues;
	cmd->max_other = 0;
	cmd->max_combined = 0;
	cmd->rx_count = priv->rx_cfg.num_queues;
	cmd->tx_count = priv->tx_cfg.num_queues;
	cmd->other_count = 0;
	cmd->combined_count = 0;
पूर्ण

अटल पूर्णांक gve_set_channels(काष्ठा net_device *netdev,
			    काष्ठा ethtool_channels *cmd)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);
	काष्ठा gve_queue_config new_tx_cfg = priv->tx_cfg;
	काष्ठा gve_queue_config new_rx_cfg = priv->rx_cfg;
	काष्ठा ethtool_channels old_settings;
	पूर्णांक new_tx = cmd->tx_count;
	पूर्णांक new_rx = cmd->rx_count;

	gve_get_channels(netdev, &old_settings);

	/* Changing combined is not allowed */
	अगर (cmd->combined_count != old_settings.combined_count)
		वापस -EINVAL;

	अगर (!new_rx || !new_tx)
		वापस -EINVAL;

	अगर (!netअगर_carrier_ok(netdev)) अणु
		priv->tx_cfg.num_queues = new_tx;
		priv->rx_cfg.num_queues = new_rx;
		वापस 0;
	पूर्ण

	new_tx_cfg.num_queues = new_tx;
	new_rx_cfg.num_queues = new_rx;

	वापस gve_adjust_queues(priv, new_rx_cfg, new_tx_cfg);
पूर्ण

अटल व्योम gve_get_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *cmd)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);

	cmd->rx_max_pending = priv->rx_desc_cnt;
	cmd->tx_max_pending = priv->tx_desc_cnt;
	cmd->rx_pending = priv->rx_desc_cnt;
	cmd->tx_pending = priv->tx_desc_cnt;
पूर्ण

अटल पूर्णांक gve_user_reset(काष्ठा net_device *netdev, u32 *flags)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);

	अगर (*flags == ETH_RESET_ALL) अणु
		*flags = 0;
		वापस gve_reset(priv, true);
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक gve_get_tunable(काष्ठा net_device *netdev,
			   स्थिर काष्ठा ethtool_tunable *etuna, व्योम *value)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);

	चयन (etuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)value = priv->rx_copyअवरोध;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक gve_set_tunable(काष्ठा net_device *netdev,
			   स्थिर काष्ठा ethtool_tunable *etuna,
			   स्थिर व्योम *value)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);
	u32 len;

	चयन (etuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		len = *(u32 *)value;
		अगर (len > PAGE_SIZE / 2)
			वापस -EINVAL;
		priv->rx_copyअवरोध = len;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32 gve_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);
	u32 ret_flags = 0;

	/* Only 1 flag exists currently: report-stats (BIT(O)), so set that flag. */
	अगर (priv->ethtool_flags & BIT(0))
		ret_flags |= BIT(0);
	वापस ret_flags;
पूर्ण

अटल पूर्णांक gve_set_priv_flags(काष्ठा net_device *netdev, u32 flags)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);
	u64 ori_flags, new_flags;

	ori_flags = READ_ONCE(priv->ethtool_flags);
	new_flags = ori_flags;

	/* Only one priv flag exists: report-stats (BIT(0))*/
	अगर (flags & BIT(0))
		new_flags |= BIT(0);
	अन्यथा
		new_flags &= ~(BIT(0));
	priv->ethtool_flags = new_flags;
	/* start report-stats समयr when user turns report stats on. */
	अगर (flags & BIT(0)) अणु
		mod_समयr(&priv->stats_report_समयr,
			  round_jअगरfies(jअगरfies +
					msecs_to_jअगरfies(priv->stats_report_समयr_period)));
	पूर्ण
	/* Zero off gve stats when report-stats turned off and */
	/* delete report stats समयr. */
	अगर (!(flags & BIT(0)) && (ori_flags & BIT(0))) अणु
		पूर्णांक tx_stats_num = GVE_TX_STATS_REPORT_NUM *
			priv->tx_cfg.num_queues;
		पूर्णांक rx_stats_num = GVE_RX_STATS_REPORT_NUM *
			priv->rx_cfg.num_queues;

		स_रखो(priv->stats_report->stats, 0, (tx_stats_num + rx_stats_num) *
				   माप(काष्ठा stats));
		del_समयr_sync(&priv->stats_report_समयr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gve_get_link_ksettings(काष्ठा net_device *netdev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा gve_priv *priv = netdev_priv(netdev);
	पूर्णांक err = gve_adminq_report_link_speed(priv);

	cmd->base.speed = priv->link_speed;
	वापस err;
पूर्ण

स्थिर काष्ठा ethtool_ops gve_ethtool_ops = अणु
	.get_drvinfo = gve_get_drvinfo,
	.get_strings = gve_get_strings,
	.get_sset_count = gve_get_sset_count,
	.get_ethtool_stats = gve_get_ethtool_stats,
	.set_msglevel = gve_set_msglevel,
	.get_msglevel = gve_get_msglevel,
	.set_channels = gve_set_channels,
	.get_channels = gve_get_channels,
	.get_link = ethtool_op_get_link,
	.get_ringparam = gve_get_ringparam,
	.reset = gve_user_reset,
	.get_tunable = gve_get_tunable,
	.set_tunable = gve_set_tunable,
	.get_priv_flags = gve_get_priv_flags,
	.set_priv_flags = gve_set_priv_flags,
	.get_link_ksettings = gve_get_link_ksettings
पूर्ण;
