<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश <linux/etherdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/phy.h>
#समावेश <linux/sfp.h>

#समावेश "hns3_enet.h"

काष्ठा hns3_stats अणु
	अक्षर stats_string[ETH_GSTRING_LEN];
	पूर्णांक stats_offset;
पूर्ण;

काष्ठा hns3_sfp_type अणु
	u8 type;
	u8 ext_type;
पूर्ण;

काष्ठा hns3_pflag_desc अणु
	अक्षर name[ETH_GSTRING_LEN];
	व्योम (*handler)(काष्ठा net_device *netdev, bool enable);
पूर्ण;

/* tqp related stats */
#घोषणा HNS3_TQP_STAT(_string, _member)	अणु			\
	.stats_string = _string,				\
	.stats_offset = दुरत्व(काष्ठा hns3_enet_ring, stats) +\
			दुरत्व(काष्ठा ring_stats, _member),   \
पूर्ण

अटल स्थिर काष्ठा hns3_stats hns3_txq_stats[] = अणु
	/* Tx per-queue statistics */
	HNS3_TQP_STAT("dropped", sw_err_cnt),
	HNS3_TQP_STAT("seg_pkt_cnt", seg_pkt_cnt),
	HNS3_TQP_STAT("packets", tx_pkts),
	HNS3_TQP_STAT("bytes", tx_bytes),
	HNS3_TQP_STAT("more", tx_more),
	HNS3_TQP_STAT("wake", restart_queue),
	HNS3_TQP_STAT("busy", tx_busy),
	HNS3_TQP_STAT("copy", tx_copy),
	HNS3_TQP_STAT("vlan_err", tx_vlan_err),
	HNS3_TQP_STAT("l4_proto_err", tx_l4_proto_err),
	HNS3_TQP_STAT("l2l3l4_err", tx_l2l3l4_err),
	HNS3_TQP_STAT("tso_err", tx_tso_err),
	HNS3_TQP_STAT("over_max_recursion", over_max_recursion),
	HNS3_TQP_STAT("hw_limitation", hw_limitation),
पूर्ण;

#घोषणा HNS3_TXQ_STATS_COUNT ARRAY_SIZE(hns3_txq_stats)

अटल स्थिर काष्ठा hns3_stats hns3_rxq_stats[] = अणु
	/* Rx per-queue statistics */
	HNS3_TQP_STAT("dropped", sw_err_cnt),
	HNS3_TQP_STAT("seg_pkt_cnt", seg_pkt_cnt),
	HNS3_TQP_STAT("packets", rx_pkts),
	HNS3_TQP_STAT("bytes", rx_bytes),
	HNS3_TQP_STAT("errors", rx_err_cnt),
	HNS3_TQP_STAT("reuse_pg_cnt", reuse_pg_cnt),
	HNS3_TQP_STAT("err_pkt_len", err_pkt_len),
	HNS3_TQP_STAT("err_bd_num", err_bd_num),
	HNS3_TQP_STAT("l2_err", l2_err),
	HNS3_TQP_STAT("l3l4_csum_err", l3l4_csum_err),
	HNS3_TQP_STAT("csum_complete", csum_complete),
	HNS3_TQP_STAT("multicast", rx_multicast),
	HNS3_TQP_STAT("non_reuse_pg", non_reuse_pg),
पूर्ण;

#घोषणा HNS3_PRIV_FLAGS_LEN ARRAY_SIZE(hns3_priv_flags)

#घोषणा HNS3_RXQ_STATS_COUNT ARRAY_SIZE(hns3_rxq_stats)

#घोषणा HNS3_TQP_STATS_COUNT (HNS3_TXQ_STATS_COUNT + HNS3_RXQ_STATS_COUNT)

#घोषणा HNS3_SELF_TEST_TYPE_NUM         4
#घोषणा HNS3_NIC_LB_TEST_PKT_NUM	1
#घोषणा HNS3_NIC_LB_TEST_RING_ID	0
#घोषणा HNS3_NIC_LB_TEST_PACKET_SIZE	128
#घोषणा HNS3_NIC_LB_SETUP_USEC		10000

/* Nic loopback test err  */
#घोषणा HNS3_NIC_LB_TEST_NO_MEM_ERR	1
#घोषणा HNS3_NIC_LB_TEST_TX_CNT_ERR	2
#घोषणा HNS3_NIC_LB_TEST_RX_CNT_ERR	3

अटल पूर्णांक hns3_lp_setup(काष्ठा net_device *ndev, क्रमागत hnae3_loop loop, bool en)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);
	bool vlan_filter_enable;
	पूर्णांक ret;

	अगर (!h->ae_algo->ops->set_loopback ||
	    !h->ae_algo->ops->set_promisc_mode)
		वापस -EOPNOTSUPP;

	चयन (loop) अणु
	हाल HNAE3_LOOP_SERIAL_SERDES:
	हाल HNAE3_LOOP_PARALLEL_SERDES:
	हाल HNAE3_LOOP_APP:
	हाल HNAE3_LOOP_PHY:
		ret = h->ae_algo->ops->set_loopback(h, loop, en);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		अवरोध;
	पूर्ण

	अगर (ret || ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2)
		वापस ret;

	अगर (en) अणु
		h->ae_algo->ops->set_promisc_mode(h, true, true);
	पूर्ण अन्यथा अणु
		/* recover promisc mode beक्रमe loopback test */
		hns3_request_update_promisc_mode(h);
		vlan_filter_enable = ndev->flags & IFF_PROMISC ? false : true;
		hns3_enable_vlan_filter(ndev, vlan_filter_enable);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_lp_up(काष्ठा net_device *ndev, क्रमागत hnae3_loop loop_mode)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);
	पूर्णांक ret;

	ret = hns3_nic_reset_all_ring(h);
	अगर (ret)
		वापस ret;

	ret = hns3_lp_setup(ndev, loop_mode, true);
	usleep_range(HNS3_NIC_LB_SETUP_USEC, HNS3_NIC_LB_SETUP_USEC * 2);

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_lp_करोwn(काष्ठा net_device *ndev, क्रमागत hnae3_loop loop_mode)
अणु
	पूर्णांक ret;

	ret = hns3_lp_setup(ndev, loop_mode, false);
	अगर (ret) अणु
		netdev_err(ndev, "lb_setup return error: %d\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(HNS3_NIC_LB_SETUP_USEC, HNS3_NIC_LB_SETUP_USEC * 2);

	वापस 0;
पूर्ण

अटल व्योम hns3_lp_setup_skb(काष्ठा sk_buff *skb)
अणु
#घोषणा	HNS3_NIC_LB_DST_MAC_ADDR	0x1f

	काष्ठा net_device *ndev = skb->dev;
	काष्ठा hnae3_handle *handle;
	काष्ठा hnae3_ae_dev *ae_dev;
	अचिन्हित अक्षर *packet;
	काष्ठा ethhdr *ethh;
	अचिन्हित पूर्णांक i;

	skb_reserve(skb, NET_IP_ALIGN);
	ethh = skb_put(skb, माप(काष्ठा ethhdr));
	packet = skb_put(skb, HNS3_NIC_LB_TEST_PACKET_SIZE);

	स_नकल(ethh->h_dest, ndev->dev_addr, ETH_ALEN);

	/* The dst mac addr of loopback packet is the same as the host'
	 * mac addr, the SSU component may loop back the packet to host
	 * beक्रमe the packet reaches mac or serdes, which will defect
	 * the purpose of mac or serdes selftest.
	 */
	handle = hns3_get_handle(ndev);
	ae_dev = pci_get_drvdata(handle->pdev);
	अगर (ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		ethh->h_dest[5] += HNS3_NIC_LB_DST_MAC_ADDR;
	eth_zero_addr(ethh->h_source);
	ethh->h_proto = htons(ETH_P_ARP);
	skb_reset_mac_header(skb);

	क्रम (i = 0; i < HNS3_NIC_LB_TEST_PACKET_SIZE; i++)
		packet[i] = (अचिन्हित अक्षर)(i & 0xff);
पूर्ण

अटल व्योम hns3_lb_check_skb_data(काष्ठा hns3_enet_ring *ring,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा hns3_enet_tqp_vector *tqp_vector = ring->tqp_vector;
	अचिन्हित अक्षर *packet = skb->data;
	u32 len = skb_headlen(skb);
	u32 i;

	len = min_t(u32, len, HNS3_NIC_LB_TEST_PACKET_SIZE);

	क्रम (i = 0; i < len; i++)
		अगर (packet[i] != (अचिन्हित अक्षर)(i & 0xff))
			अवरोध;

	/* The packet is correctly received */
	अगर (i == HNS3_NIC_LB_TEST_PACKET_SIZE)
		tqp_vector->rx_group.total_packets++;
	अन्यथा
		prपूर्णांक_hex_dump(KERN_ERR, "selftest:", DUMP_PREFIX_OFFSET, 16, 1,
			       skb->data, len, true);

	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल u32 hns3_lb_check_rx_ring(काष्ठा hns3_nic_priv *priv, u32 budget)
अणु
	काष्ठा hnae3_handle *h = priv->ae_handle;
	काष्ठा hnae3_knic_निजी_info *kinfo;
	u32 i, rcv_good_pkt_total = 0;

	kinfo = &h->kinfo;
	क्रम (i = kinfo->num_tqps; i < kinfo->num_tqps * 2; i++) अणु
		काष्ठा hns3_enet_ring *ring = &priv->ring[i];
		काष्ठा hns3_enet_ring_group *rx_group;
		u64 pre_rx_pkt;

		rx_group = &ring->tqp_vector->rx_group;
		pre_rx_pkt = rx_group->total_packets;

		preempt_disable();
		hns3_clean_rx_ring(ring, budget, hns3_lb_check_skb_data);
		preempt_enable();

		rcv_good_pkt_total += (rx_group->total_packets - pre_rx_pkt);
		rx_group->total_packets = pre_rx_pkt;
	पूर्ण
	वापस rcv_good_pkt_total;
पूर्ण

अटल व्योम hns3_lb_clear_tx_ring(काष्ठा hns3_nic_priv *priv, u32 start_ringid,
				  u32 end_ringid, u32 budget)
अणु
	u32 i;

	क्रम (i = start_ringid; i <= end_ringid; i++) अणु
		काष्ठा hns3_enet_ring *ring = &priv->ring[i];

		hns3_clean_tx_ring(ring, 0);
	पूर्ण
पूर्ण

/**
 * hns3_lp_run_test -  run loopback test
 * @ndev: net device
 * @mode: loopback type
 */
अटल पूर्णांक hns3_lp_run_test(काष्ठा net_device *ndev, क्रमागत hnae3_loop mode)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	u32 i, good_cnt;
	पूर्णांक ret_val = 0;

	skb = alloc_skb(HNS3_NIC_LB_TEST_PACKET_SIZE + ETH_HLEN + NET_IP_ALIGN,
			GFP_KERNEL);
	अगर (!skb)
		वापस HNS3_NIC_LB_TEST_NO_MEM_ERR;

	skb->dev = ndev;
	hns3_lp_setup_skb(skb);
	skb->queue_mapping = HNS3_NIC_LB_TEST_RING_ID;

	good_cnt = 0;
	क्रम (i = 0; i < HNS3_NIC_LB_TEST_PKT_NUM; i++) अणु
		netdev_tx_t tx_ret;

		skb_get(skb);
		tx_ret = hns3_nic_net_xmit(skb, ndev);
		अगर (tx_ret == NETDEV_TX_OK) अणु
			good_cnt++;
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
			netdev_err(ndev, "hns3_lb_run_test xmit failed: %d\n",
				   tx_ret);
		पूर्ण
	पूर्ण
	अगर (good_cnt != HNS3_NIC_LB_TEST_PKT_NUM) अणु
		ret_val = HNS3_NIC_LB_TEST_TX_CNT_ERR;
		netdev_err(ndev, "mode %d sent fail, cnt=0x%x, budget=0x%x\n",
			   mode, good_cnt, HNS3_NIC_LB_TEST_PKT_NUM);
		जाओ out;
	पूर्ण

	/* Allow 200 milliseconds क्रम packets to go from Tx to Rx */
	msleep(200);

	good_cnt = hns3_lb_check_rx_ring(priv, HNS3_NIC_LB_TEST_PKT_NUM);
	अगर (good_cnt != HNS3_NIC_LB_TEST_PKT_NUM) अणु
		ret_val = HNS3_NIC_LB_TEST_RX_CNT_ERR;
		netdev_err(ndev, "mode %d recv fail, cnt=0x%x, budget=0x%x\n",
			   mode, good_cnt, HNS3_NIC_LB_TEST_PKT_NUM);
	पूर्ण

out:
	hns3_lb_clear_tx_ring(priv, HNS3_NIC_LB_TEST_RING_ID,
			      HNS3_NIC_LB_TEST_RING_ID,
			      HNS3_NIC_LB_TEST_PKT_NUM);

	kमुक्त_skb(skb);
	वापस ret_val;
पूर्ण

/**
 * hns3_self_test - self test
 * @ndev: net device
 * @eth_test: test cmd
 * @data: test result
 */
अटल व्योम hns3_self_test(काष्ठा net_device *ndev,
			   काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae3_handle *h = priv->ae_handle;
	पूर्णांक st_param[HNS3_SELF_TEST_TYPE_NUM][2];
	bool अगर_running = netअगर_running(ndev);
	पूर्णांक test_index = 0;
	u32 i;

	अगर (hns3_nic_resetting(ndev)) अणु
		netdev_err(ndev, "dev resetting!");
		वापस;
	पूर्ण

	/* Only करो offline selftest, or pass by शेष */
	अगर (eth_test->flags != ETH_TEST_FL_OFFLINE)
		वापस;

	netअगर_dbg(h, drv, ndev, "self test start");

	st_param[HNAE3_LOOP_APP][0] = HNAE3_LOOP_APP;
	st_param[HNAE3_LOOP_APP][1] =
			h->flags & HNAE3_SUPPORT_APP_LOOPBACK;

	st_param[HNAE3_LOOP_SERIAL_SERDES][0] = HNAE3_LOOP_SERIAL_SERDES;
	st_param[HNAE3_LOOP_SERIAL_SERDES][1] =
			h->flags & HNAE3_SUPPORT_SERDES_SERIAL_LOOPBACK;

	st_param[HNAE3_LOOP_PARALLEL_SERDES][0] =
			HNAE3_LOOP_PARALLEL_SERDES;
	st_param[HNAE3_LOOP_PARALLEL_SERDES][1] =
			h->flags & HNAE3_SUPPORT_SERDES_PARALLEL_LOOPBACK;

	st_param[HNAE3_LOOP_PHY][0] = HNAE3_LOOP_PHY;
	st_param[HNAE3_LOOP_PHY][1] =
			h->flags & HNAE3_SUPPORT_PHY_LOOPBACK;

	अगर (अगर_running)
		ndev->netdev_ops->nकरो_stop(ndev);

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
	/* Disable the vlan filter क्रम selftest करोes not support it */
	अगर (h->ae_algo->ops->enable_vlan_filter)
		h->ae_algo->ops->enable_vlan_filter(h, false);
#पूर्ण_अगर

	/* Tell firmware to stop mac स्वतःneg beक्रमe loopback test start,
	 * otherwise loopback test may be failed when the port is still
	 * negotiating.
	 */
	अगर (h->ae_algo->ops->halt_स्वतःneg)
		h->ae_algo->ops->halt_स्वतःneg(h, true);

	set_bit(HNS3_NIC_STATE_TESTING, &priv->state);

	क्रम (i = 0; i < HNS3_SELF_TEST_TYPE_NUM; i++) अणु
		क्रमागत hnae3_loop loop_type = (क्रमागत hnae3_loop)st_param[i][0];

		अगर (!st_param[i][1])
			जारी;

		data[test_index] = hns3_lp_up(ndev, loop_type);
		अगर (!data[test_index])
			data[test_index] = hns3_lp_run_test(ndev, loop_type);

		hns3_lp_करोwn(ndev, loop_type);

		अगर (data[test_index])
			eth_test->flags |= ETH_TEST_FL_FAILED;

		test_index++;
	पूर्ण

	clear_bit(HNS3_NIC_STATE_TESTING, &priv->state);

	अगर (h->ae_algo->ops->halt_स्वतःneg)
		h->ae_algo->ops->halt_स्वतःneg(h, false);

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
	अगर (h->ae_algo->ops->enable_vlan_filter)
		h->ae_algo->ops->enable_vlan_filter(h, true);
#पूर्ण_अगर

	अगर (अगर_running)
		ndev->netdev_ops->nकरो_खोलो(ndev);

	netअगर_dbg(h, drv, ndev, "self test end\n");
पूर्ण

अटल व्योम hns3_update_limit_promisc_mode(काष्ठा net_device *netdev,
					   bool enable)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);

	अगर (enable)
		set_bit(HNAE3_PFLAG_LIMIT_PROMISC, &handle->priv_flags);
	अन्यथा
		clear_bit(HNAE3_PFLAG_LIMIT_PROMISC, &handle->priv_flags);

	hns3_request_update_promisc_mode(handle);
पूर्ण

अटल स्थिर काष्ठा hns3_pflag_desc hns3_priv_flags[HNAE3_PFLAG_MAX] = अणु
	अणु "limit_promisc",	hns3_update_limit_promisc_mode पूर्ण
पूर्ण;

अटल पूर्णांक hns3_get_sset_count(काष्ठा net_device *netdev, पूर्णांक stringset)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	स्थिर काष्ठा hnae3_ae_ops *ops = h->ae_algo->ops;

	अगर (!ops->get_sset_count)
		वापस -EOPNOTSUPP;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		वापस ((HNS3_TQP_STATS_COUNT * h->kinfo.num_tqps) +
			ops->get_sset_count(h, stringset));

	हाल ETH_SS_TEST:
		वापस ops->get_sset_count(h, stringset);

	हाल ETH_SS_PRIV_FLAGS:
		वापस HNAE3_PFLAG_MAX;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम *hns3_update_strings(u8 *data, स्थिर काष्ठा hns3_stats *stats,
		u32 stat_count, u32 num_tqps, स्थिर अक्षर *prefix)
अणु
#घोषणा MAX_PREFIX_SIZE (6 + 4)
	u32 size_left;
	u32 i, j;
	u32 n1;

	क्रम (i = 0; i < num_tqps; i++) अणु
		क्रम (j = 0; j < stat_count; j++) अणु
			data[ETH_GSTRING_LEN - 1] = '\0';

			/* first, prepend the prefix string */
			n1 = scnम_लिखो(data, MAX_PREFIX_SIZE, "%s%u_",
				       prefix, i);
			size_left = (ETH_GSTRING_LEN - 1) - n1;

			/* now, concatenate the stats string to it */
			म_जोड़न(data, stats[j].stats_string, size_left);
			data += ETH_GSTRING_LEN;
		पूर्ण
	पूर्ण

	वापस data;
पूर्ण

अटल u8 *hns3_get_strings_tqps(काष्ठा hnae3_handle *handle, u8 *data)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	स्थिर अक्षर tx_prefix[] = "txq";
	स्थिर अक्षर rx_prefix[] = "rxq";

	/* get strings क्रम Tx */
	data = hns3_update_strings(data, hns3_txq_stats, HNS3_TXQ_STATS_COUNT,
				   kinfo->num_tqps, tx_prefix);

	/* get strings क्रम Rx */
	data = hns3_update_strings(data, hns3_rxq_stats, HNS3_RXQ_STATS_COUNT,
				   kinfo->num_tqps, rx_prefix);

	वापस data;
पूर्ण

अटल व्योम hns3_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	स्थिर काष्ठा hnae3_ae_ops *ops = h->ae_algo->ops;
	अक्षर *buff = (अक्षर *)data;
	पूर्णांक i;

	अगर (!ops->get_strings)
		वापस;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		buff = hns3_get_strings_tqps(h, buff);
		ops->get_strings(h, stringset, (u8 *)buff);
		अवरोध;
	हाल ETH_SS_TEST:
		ops->get_strings(h, stringset, data);
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		क्रम (i = 0; i < HNS3_PRIV_FLAGS_LEN; i++) अणु
			snम_लिखो(buff, ETH_GSTRING_LEN, "%s",
				 hns3_priv_flags[i].name);
			buff += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल u64 *hns3_get_stats_tqps(काष्ठा hnae3_handle *handle, u64 *data)
अणु
	काष्ठा hns3_nic_priv *nic_priv = (काष्ठा hns3_nic_priv *)handle->priv;
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hns3_enet_ring *ring;
	u8 *stat;
	पूर्णांक i, j;

	/* get stats क्रम Tx */
	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		ring = &nic_priv->ring[i];
		क्रम (j = 0; j < HNS3_TXQ_STATS_COUNT; j++) अणु
			stat = (u8 *)ring + hns3_txq_stats[j].stats_offset;
			*data++ = *(u64 *)stat;
		पूर्ण
	पूर्ण

	/* get stats क्रम Rx */
	क्रम (i = 0; i < kinfo->num_tqps; i++) अणु
		ring = &nic_priv->ring[i + kinfo->num_tqps];
		क्रम (j = 0; j < HNS3_RXQ_STATS_COUNT; j++) अणु
			stat = (u8 *)ring + hns3_rxq_stats[j].stats_offset;
			*data++ = *(u64 *)stat;
		पूर्ण
	पूर्ण

	वापस data;
पूर्ण

/* hns3_get_stats - get detail statistics.
 * @netdev: net device
 * @stats: statistics info.
 * @data: statistics data.
 */
अटल व्योम hns3_get_stats(काष्ठा net_device *netdev,
			   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	u64 *p = data;

	अगर (hns3_nic_resetting(netdev)) अणु
		netdev_err(netdev, "dev resetting, could not get stats\n");
		वापस;
	पूर्ण

	अगर (!h->ae_algo->ops->get_stats || !h->ae_algo->ops->update_stats) अणु
		netdev_err(netdev, "could not get any statistics\n");
		वापस;
	पूर्ण

	h->ae_algo->ops->update_stats(h, &netdev->stats);

	/* get per-queue stats */
	p = hns3_get_stats_tqps(h, p);

	/* get MAC & other misc hardware stats */
	h->ae_algo->ops->get_stats(h, p);
पूर्ण

अटल व्योम hns3_get_drvinfo(काष्ठा net_device *netdev,
			     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = priv->ae_handle;
	u32 fw_version;

	अगर (!h->ae_algo->ops->get_fw_version) अणु
		netdev_err(netdev, "could not get fw version!\n");
		वापस;
	पूर्ण

	म_नकलन(drvinfo->driver, h->pdev->driver->name,
		माप(drvinfo->driver));
	drvinfo->driver[माप(drvinfo->driver) - 1] = '\0';

	म_नकलन(drvinfo->bus_info, pci_name(h->pdev),
		माप(drvinfo->bus_info));
	drvinfo->bus_info[ETHTOOL_BUSINFO_LEN - 1] = '\0';

	fw_version = priv->ae_handle->ae_algo->ops->get_fw_version(h);

	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%lu.%lu.%lu.%lu",
		 hnae3_get_field(fw_version, HNAE3_FW_VERSION_BYTE3_MASK,
				 HNAE3_FW_VERSION_BYTE3_SHIFT),
		 hnae3_get_field(fw_version, HNAE3_FW_VERSION_BYTE2_MASK,
				 HNAE3_FW_VERSION_BYTE2_SHIFT),
		 hnae3_get_field(fw_version, HNAE3_FW_VERSION_BYTE1_MASK,
				 HNAE3_FW_VERSION_BYTE1_SHIFT),
		 hnae3_get_field(fw_version, HNAE3_FW_VERSION_BYTE0_MASK,
				 HNAE3_FW_VERSION_BYTE0_SHIFT));
पूर्ण

अटल u32 hns3_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (h->ae_algo->ops->get_status)
		वापस h->ae_algo->ops->get_status(h);
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम hns3_get_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = priv->ae_handle;
	पूर्णांक queue_num = h->kinfo.num_tqps;

	अगर (hns3_nic_resetting(netdev)) अणु
		netdev_err(netdev, "dev resetting!");
		वापस;
	पूर्ण

	param->tx_max_pending = HNS3_RING_MAX_PENDING;
	param->rx_max_pending = HNS3_RING_MAX_PENDING;

	param->tx_pending = priv->ring[0].desc_num;
	param->rx_pending = priv->ring[queue_num].desc_num;
पूर्ण

अटल व्योम hns3_get_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *param)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);

	अगर (!test_bit(HNAE3_DEV_SUPPORT_PAUSE_B, ae_dev->caps))
		वापस;

	अगर (h->ae_algo->ops->get_छोड़ोparam)
		h->ae_algo->ops->get_छोड़ोparam(h, &param->स्वतःneg,
			&param->rx_छोड़ो, &param->tx_छोड़ो);
पूर्ण

अटल पूर्णांक hns3_set_छोड़ोparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_छोड़ोparam *param)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);

	अगर (!test_bit(HNAE3_DEV_SUPPORT_PAUSE_B, ae_dev->caps))
		वापस -EOPNOTSUPP;

	netअगर_dbg(h, drv, netdev,
		  "set pauseparam: autoneg=%u, rx:%u, tx:%u\n",
		  param->स्वतःneg, param->rx_छोड़ो, param->tx_छोड़ो);

	अगर (h->ae_algo->ops->set_छोड़ोparam)
		वापस h->ae_algo->ops->set_छोड़ोparam(h, param->स्वतःneg,
						       param->rx_छोड़ो,
						       param->tx_छोड़ो);
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम hns3_get_ksettings(काष्ठा hnae3_handle *h,
			       काष्ठा ethtool_link_ksettings *cmd)
अणु
	स्थिर काष्ठा hnae3_ae_ops *ops = h->ae_algo->ops;

	/* 1.स्वतः_neg & speed & duplex from cmd */
	अगर (ops->get_ksettings_an_result)
		ops->get_ksettings_an_result(h,
					     &cmd->base.स्वतःneg,
					     &cmd->base.speed,
					     &cmd->base.duplex);

	/* 2.get link mode */
	अगर (ops->get_link_mode)
		ops->get_link_mode(h,
				   cmd->link_modes.supported,
				   cmd->link_modes.advertising);

	/* 3.mdix_ctrl&mdix get from phy reg */
	अगर (ops->get_mdix_mode)
		ops->get_mdix_mode(h, &cmd->base.eth_tp_mdix_ctrl,
				   &cmd->base.eth_tp_mdix);
पूर्ण

अटल पूर्णांक hns3_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);
	स्थिर काष्ठा hnae3_ae_ops *ops;
	u8 module_type;
	u8 media_type;
	u8 link_stat;

	ops = h->ae_algo->ops;
	अगर (ops->get_media_type)
		ops->get_media_type(h, &media_type, &module_type);
	अन्यथा
		वापस -EOPNOTSUPP;

	चयन (media_type) अणु
	हाल HNAE3_MEDIA_TYPE_NONE:
		cmd->base.port = PORT_NONE;
		hns3_get_ksettings(h, cmd);
		अवरोध;
	हाल HNAE3_MEDIA_TYPE_FIBER:
		अगर (module_type == HNAE3_MODULE_TYPE_CR)
			cmd->base.port = PORT_DA;
		अन्यथा
			cmd->base.port = PORT_FIBRE;

		hns3_get_ksettings(h, cmd);
		अवरोध;
	हाल HNAE3_MEDIA_TYPE_BACKPLANE:
		cmd->base.port = PORT_NONE;
		hns3_get_ksettings(h, cmd);
		अवरोध;
	हाल HNAE3_MEDIA_TYPE_COPPER:
		cmd->base.port = PORT_TP;
		अगर (test_bit(HNAE3_DEV_SUPPORT_PHY_IMP_B, ae_dev->caps) &&
		    ops->get_phy_link_ksettings)
			ops->get_phy_link_ksettings(h, cmd);
		अन्यथा अगर (!netdev->phydev)
			hns3_get_ksettings(h, cmd);
		अन्यथा
			phy_ethtool_ksettings_get(netdev->phydev, cmd);
		अवरोध;
	शेष:

		netdev_warn(netdev, "Unknown media type");
		वापस 0;
	पूर्ण

	/* mdio_support */
	cmd->base.mdio_support = ETH_MDIO_SUPPORTS_C22;

	link_stat = hns3_get_link(netdev);
	अगर (!link_stat) अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_check_ksettings_param(स्थिर काष्ठा net_device *netdev,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	u8 module_type = HNAE3_MODULE_TYPE_UNKNOWN;
	u8 media_type = HNAE3_MEDIA_TYPE_UNKNOWN;
	u8 स्वतःneg;
	u32 speed;
	u8 duplex;
	पूर्णांक ret;

	/* hw करोesn't support use specअगरied speed and duplex to negotiate,
	 * unnecessary to check them when स्वतःneg on.
	 */
	अगर (cmd->base.स्वतःneg)
		वापस 0;

	अगर (ops->get_ksettings_an_result) अणु
		ops->get_ksettings_an_result(handle, &स्वतःneg, &speed, &duplex);
		अगर (cmd->base.स्वतःneg == स्वतःneg && cmd->base.speed == speed &&
		    cmd->base.duplex == duplex)
			वापस 0;
	पूर्ण

	अगर (ops->get_media_type)
		ops->get_media_type(handle, &media_type, &module_type);

	अगर (cmd->base.duplex == DUPLEX_HALF &&
	    media_type != HNAE3_MEDIA_TYPE_COPPER) अणु
		netdev_err(netdev,
			   "only copper port supports half duplex!");
		वापस -EINVAL;
	पूर्ण

	अगर (ops->check_port_speed) अणु
		ret = ops->check_port_speed(handle, cmd->base.speed);
		अगर (ret) अणु
			netdev_err(netdev, "unsupported speed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_set_link_ksettings(काष्ठा net_device *netdev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	पूर्णांक ret;

	/* Chip करोn't support this mode. */
	अगर (cmd->base.speed == SPEED_1000 && cmd->base.duplex == DUPLEX_HALF)
		वापस -EINVAL;

	netअगर_dbg(handle, drv, netdev,
		  "set link(%s): autoneg=%u, speed=%u, duplex=%u\n",
		  netdev->phydev ? "phy" : "mac",
		  cmd->base.स्वतःneg, cmd->base.speed, cmd->base.duplex);

	/* Only support ksettings_set क्रम netdev with phy attached क्रम now */
	अगर (netdev->phydev) अणु
		अगर (cmd->base.speed == SPEED_1000 &&
		    cmd->base.स्वतःneg == AUTONEG_DISABLE)
			वापस -EINVAL;

		वापस phy_ethtool_ksettings_set(netdev->phydev, cmd);
	पूर्ण अन्यथा अगर (test_bit(HNAE3_DEV_SUPPORT_PHY_IMP_B, ae_dev->caps) &&
		   ops->set_phy_link_ksettings) अणु
		वापस ops->set_phy_link_ksettings(handle, cmd);
	पूर्ण

	अगर (ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)
		वापस -EOPNOTSUPP;

	ret = hns3_check_ksettings_param(netdev, cmd);
	अगर (ret)
		वापस ret;

	अगर (ops->set_स्वतःneg) अणु
		ret = ops->set_स्वतःneg(handle, cmd->base.स्वतःneg);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* hw करोesn't support use specअगरied speed and duplex to negotiate,
	 * ignore them when स्वतःneg on.
	 */
	अगर (cmd->base.स्वतःneg) अणु
		netdev_info(netdev,
			    "autoneg is on, ignore the speed and duplex\n");
		वापस 0;
	पूर्ण

	अगर (ops->cfg_mac_speed_dup_h)
		ret = ops->cfg_mac_speed_dup_h(handle, cmd->base.speed,
					       cmd->base.duplex);

	वापस ret;
पूर्ण

अटल u32 hns3_get_rss_key_size(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (!h->ae_algo->ops->get_rss_key_size)
		वापस 0;

	वापस h->ae_algo->ops->get_rss_key_size(h);
पूर्ण

अटल u32 hns3_get_rss_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);

	वापस ae_dev->dev_specs.rss_ind_tbl_size;
पूर्ण

अटल पूर्णांक hns3_get_rss(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			u8 *hfunc)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (!h->ae_algo->ops->get_rss)
		वापस -EOPNOTSUPP;

	वापस h->ae_algo->ops->get_rss(h, indir, key, hfunc);
पूर्ण

अटल पूर्णांक hns3_set_rss(काष्ठा net_device *netdev, स्थिर u32 *indir,
			स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);

	अगर (!h->ae_algo->ops->set_rss)
		वापस -EOPNOTSUPP;

	अगर ((ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2 &&
	     hfunc != ETH_RSS_HASH_TOP) || (hfunc != ETH_RSS_HASH_NO_CHANGE &&
	     hfunc != ETH_RSS_HASH_TOP && hfunc != ETH_RSS_HASH_XOR)) अणु
		netdev_err(netdev, "hash func not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!indir) अणु
		netdev_err(netdev,
			   "set rss failed for indir is empty\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस h->ae_algo->ops->set_rss(h, indir, key, hfunc);
पूर्ण

अटल पूर्णांक hns3_get_rxnfc(काष्ठा net_device *netdev,
			  काष्ठा ethtool_rxnfc *cmd,
			  u32 *rule_locs)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = h->kinfo.num_tqps;
		वापस 0;
	हाल ETHTOOL_GRXFH:
		अगर (h->ae_algo->ops->get_rss_tuple)
			वापस h->ae_algo->ops->get_rss_tuple(h, cmd);
		वापस -EOPNOTSUPP;
	हाल ETHTOOL_GRXCLSRLCNT:
		अगर (h->ae_algo->ops->get_fd_rule_cnt)
			वापस h->ae_algo->ops->get_fd_rule_cnt(h, cmd);
		वापस -EOPNOTSUPP;
	हाल ETHTOOL_GRXCLSRULE:
		अगर (h->ae_algo->ops->get_fd_rule_info)
			वापस h->ae_algo->ops->get_fd_rule_info(h, cmd);
		वापस -EOPNOTSUPP;
	हाल ETHTOOL_GRXCLSRLALL:
		अगर (h->ae_algo->ops->get_fd_all_rules)
			वापस h->ae_algo->ops->get_fd_all_rules(h, cmd,
								 rule_locs);
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम hns3_change_all_ring_bd_num(काष्ठा hns3_nic_priv *priv,
					u32 tx_desc_num, u32 rx_desc_num)
अणु
	काष्ठा hnae3_handle *h = priv->ae_handle;
	पूर्णांक i;

	h->kinfo.num_tx_desc = tx_desc_num;
	h->kinfo.num_rx_desc = rx_desc_num;

	क्रम (i = 0; i < h->kinfo.num_tqps; i++) अणु
		priv->ring[i].desc_num = tx_desc_num;
		priv->ring[i + h->kinfo.num_tqps].desc_num = rx_desc_num;
	पूर्ण
पूर्ण

अटल काष्ठा hns3_enet_ring *hns3_backup_ringparam(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_handle *handle = priv->ae_handle;
	काष्ठा hns3_enet_ring *पंचांगp_rings;
	पूर्णांक i;

	पंचांगp_rings = kसुस्मृति(handle->kinfo.num_tqps * 2,
			    माप(काष्ठा hns3_enet_ring), GFP_KERNEL);
	अगर (!पंचांगp_rings)
		वापस शून्य;

	क्रम (i = 0; i < handle->kinfo.num_tqps * 2; i++) अणु
		स_नकल(&पंचांगp_rings[i], &priv->ring[i],
		       माप(काष्ठा hns3_enet_ring));
		पंचांगp_rings[i].skb = शून्य;
	पूर्ण

	वापस पंचांगp_rings;
पूर्ण

अटल पूर्णांक hns3_check_ringparam(काष्ठा net_device *ndev,
				काष्ठा ethtool_ringparam *param)
अणु
	अगर (hns3_nic_resetting(ndev))
		वापस -EBUSY;

	अगर (param->rx_mini_pending || param->rx_jumbo_pending)
		वापस -EINVAL;

	अगर (param->tx_pending > HNS3_RING_MAX_PENDING ||
	    param->tx_pending < HNS3_RING_MIN_PENDING ||
	    param->rx_pending > HNS3_RING_MAX_PENDING ||
	    param->rx_pending < HNS3_RING_MIN_PENDING) अणु
		netdev_err(ndev, "Queue depth out of range [%d-%d]\n",
			   HNS3_RING_MIN_PENDING, HNS3_RING_MAX_PENDING);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_set_ringparam(काष्ठा net_device *ndev,
			      काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae3_handle *h = priv->ae_handle;
	काष्ठा hns3_enet_ring *पंचांगp_rings;
	bool अगर_running = netअगर_running(ndev);
	u32 old_tx_desc_num, new_tx_desc_num;
	u32 old_rx_desc_num, new_rx_desc_num;
	u16 queue_num = h->kinfo.num_tqps;
	पूर्णांक ret, i;

	ret = hns3_check_ringparam(ndev, param);
	अगर (ret)
		वापस ret;

	/* Hardware requires that its descriptors must be multiple of eight */
	new_tx_desc_num = ALIGN(param->tx_pending, HNS3_RING_BD_MULTIPLE);
	new_rx_desc_num = ALIGN(param->rx_pending, HNS3_RING_BD_MULTIPLE);
	old_tx_desc_num = priv->ring[0].desc_num;
	old_rx_desc_num = priv->ring[queue_num].desc_num;
	अगर (old_tx_desc_num == new_tx_desc_num &&
	    old_rx_desc_num == new_rx_desc_num)
		वापस 0;

	पंचांगp_rings = hns3_backup_ringparam(priv);
	अगर (!पंचांगp_rings) अणु
		netdev_err(ndev,
			   "backup ring param failed by allocating memory fail\n");
		वापस -ENOMEM;
	पूर्ण

	netdev_info(ndev,
		    "Changing Tx/Rx ring depth from %u/%u to %u/%u\n",
		    old_tx_desc_num, old_rx_desc_num,
		    new_tx_desc_num, new_rx_desc_num);

	अगर (अगर_running)
		ndev->netdev_ops->nकरो_stop(ndev);

	hns3_change_all_ring_bd_num(priv, new_tx_desc_num, new_rx_desc_num);
	ret = hns3_init_all_ring(priv);
	अगर (ret) अणु
		netdev_err(ndev, "Change bd num fail, revert to old value(%d)\n",
			   ret);

		hns3_change_all_ring_bd_num(priv, old_tx_desc_num,
					    old_rx_desc_num);
		क्रम (i = 0; i < h->kinfo.num_tqps * 2; i++)
			स_नकल(&priv->ring[i], &पंचांगp_rings[i],
			       माप(काष्ठा hns3_enet_ring));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < h->kinfo.num_tqps * 2; i++)
			hns3_fini_ring(&पंचांगp_rings[i]);
	पूर्ण

	kमुक्त(पंचांगp_rings);

	अगर (अगर_running)
		ret = ndev->netdev_ops->nकरो_खोलो(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_set_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		अगर (h->ae_algo->ops->set_rss_tuple)
			वापस h->ae_algo->ops->set_rss_tuple(h, cmd);
		वापस -EOPNOTSUPP;
	हाल ETHTOOL_SRXCLSRLINS:
		अगर (h->ae_algo->ops->add_fd_entry)
			वापस h->ae_algo->ops->add_fd_entry(h, cmd);
		वापस -EOPNOTSUPP;
	हाल ETHTOOL_SRXCLSRLDEL:
		अगर (h->ae_algo->ops->del_fd_entry)
			वापस h->ae_algo->ops->del_fd_entry(h, cmd);
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	काष्ठा phy_device *phy = netdev->phydev;
	पूर्णांक स्वतःneg;

	अगर (!netअगर_running(netdev))
		वापस 0;

	अगर (hns3_nic_resetting(netdev)) अणु
		netdev_err(netdev, "dev resetting!");
		वापस -EBUSY;
	पूर्ण

	अगर (!ops->get_स्वतःneg || !ops->restart_स्वतःneg)
		वापस -EOPNOTSUPP;

	स्वतःneg = ops->get_स्वतःneg(handle);
	अगर (स्वतःneg != AUTONEG_ENABLE) अणु
		netdev_err(netdev,
			   "Autoneg is off, don't support to restart it\n");
		वापस -EINVAL;
	पूर्ण

	netअगर_dbg(handle, drv, netdev,
		  "nway reset (using %s)\n", phy ? "phy" : "mac");

	अगर (phy)
		वापस genphy_restart_aneg(phy);

	वापस ops->restart_स्वतःneg(handle);
पूर्ण

अटल व्योम hns3_get_channels(काष्ठा net_device *netdev,
			      काष्ठा ethtool_channels *ch)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (h->ae_algo->ops->get_channels)
		h->ae_algo->ops->get_channels(h, ch);
पूर्ण

अटल पूर्णांक hns3_get_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *cmd)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hns3_enet_coalesce *tx_coal = &priv->tx_coal;
	काष्ठा hns3_enet_coalesce *rx_coal = &priv->rx_coal;
	काष्ठा hnae3_handle *h = priv->ae_handle;

	अगर (hns3_nic_resetting(netdev))
		वापस -EBUSY;

	cmd->use_adaptive_tx_coalesce = tx_coal->adapt_enable;
	cmd->use_adaptive_rx_coalesce = rx_coal->adapt_enable;

	cmd->tx_coalesce_usecs = tx_coal->पूर्णांक_gl;
	cmd->rx_coalesce_usecs = rx_coal->पूर्णांक_gl;

	cmd->tx_coalesce_usecs_high = h->kinfo.पूर्णांक_rl_setting;
	cmd->rx_coalesce_usecs_high = h->kinfo.पूर्णांक_rl_setting;

	cmd->tx_max_coalesced_frames = tx_coal->पूर्णांक_ql;
	cmd->rx_max_coalesced_frames = rx_coal->पूर्णांक_ql;

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_check_gl_coalesce_para(काष्ठा net_device *netdev,
				       काष्ठा ethtool_coalesce *cmd)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	u32 rx_gl, tx_gl;

	अगर (cmd->rx_coalesce_usecs > ae_dev->dev_specs.max_पूर्णांक_gl) अणु
		netdev_err(netdev,
			   "invalid rx-usecs value, rx-usecs range is 0-%u\n",
			   ae_dev->dev_specs.max_पूर्णांक_gl);
		वापस -EINVAL;
	पूर्ण

	अगर (cmd->tx_coalesce_usecs > ae_dev->dev_specs.max_पूर्णांक_gl) अणु
		netdev_err(netdev,
			   "invalid tx-usecs value, tx-usecs range is 0-%u\n",
			   ae_dev->dev_specs.max_पूर्णांक_gl);
		वापस -EINVAL;
	पूर्ण

	/* device version above V3(include V3), GL uses 1us unit,
	 * so the round करोwn is not needed.
	 */
	अगर (ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V3)
		वापस 0;

	rx_gl = hns3_gl_round_करोwn(cmd->rx_coalesce_usecs);
	अगर (rx_gl != cmd->rx_coalesce_usecs) अणु
		netdev_info(netdev,
			    "rx_usecs(%u) rounded down to %u, because it must be multiple of 2.\n",
			    cmd->rx_coalesce_usecs, rx_gl);
	पूर्ण

	tx_gl = hns3_gl_round_करोwn(cmd->tx_coalesce_usecs);
	अगर (tx_gl != cmd->tx_coalesce_usecs) अणु
		netdev_info(netdev,
			    "tx_usecs(%u) rounded down to %u, because it must be multiple of 2.\n",
			    cmd->tx_coalesce_usecs, tx_gl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_check_rl_coalesce_para(काष्ठा net_device *netdev,
				       काष्ठा ethtool_coalesce *cmd)
अणु
	u32 rl;

	अगर (cmd->tx_coalesce_usecs_high != cmd->rx_coalesce_usecs_high) अणु
		netdev_err(netdev,
			   "tx_usecs_high must be same as rx_usecs_high.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cmd->rx_coalesce_usecs_high > HNS3_INT_RL_MAX) अणु
		netdev_err(netdev,
			   "Invalid usecs_high value, usecs_high range is 0-%d\n",
			   HNS3_INT_RL_MAX);
		वापस -EINVAL;
	पूर्ण

	rl = hns3_rl_round_करोwn(cmd->rx_coalesce_usecs_high);
	अगर (rl != cmd->rx_coalesce_usecs_high) अणु
		netdev_info(netdev,
			    "usecs_high(%u) rounded down to %u, because it must be multiple of 4.\n",
			    cmd->rx_coalesce_usecs_high, rl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_check_ql_coalesce_param(काष्ठा net_device *netdev,
					काष्ठा ethtool_coalesce *cmd)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);

	अगर ((cmd->tx_max_coalesced_frames || cmd->rx_max_coalesced_frames) &&
	    !ae_dev->dev_specs.पूर्णांक_ql_max) अणु
		netdev_err(netdev, "coalesced frames is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (cmd->tx_max_coalesced_frames > ae_dev->dev_specs.पूर्णांक_ql_max ||
	    cmd->rx_max_coalesced_frames > ae_dev->dev_specs.पूर्णांक_ql_max) अणु
		netdev_err(netdev,
			   "invalid coalesced_frames value, range is 0-%u\n",
			   ae_dev->dev_specs.पूर्णांक_ql_max);
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_check_coalesce_para(काष्ठा net_device *netdev,
				    काष्ठा ethtool_coalesce *cmd)
अणु
	पूर्णांक ret;

	ret = hns3_check_gl_coalesce_para(netdev, cmd);
	अगर (ret) अणु
		netdev_err(netdev,
			   "Check gl coalesce param fail. ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hns3_check_rl_coalesce_para(netdev, cmd);
	अगर (ret) अणु
		netdev_err(netdev,
			   "Check rl coalesce param fail. ret = %d\n", ret);
		वापस ret;
	पूर्ण

	वापस hns3_check_ql_coalesce_param(netdev, cmd);
पूर्ण

अटल व्योम hns3_set_coalesce_per_queue(काष्ठा net_device *netdev,
					काष्ठा ethtool_coalesce *cmd,
					u32 queue)
अणु
	काष्ठा hns3_enet_tqp_vector *tx_vector, *rx_vector;
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = priv->ae_handle;
	पूर्णांक queue_num = h->kinfo.num_tqps;

	tx_vector = priv->ring[queue].tqp_vector;
	rx_vector = priv->ring[queue_num + queue].tqp_vector;

	tx_vector->tx_group.coal.adapt_enable =
				cmd->use_adaptive_tx_coalesce;
	rx_vector->rx_group.coal.adapt_enable =
				cmd->use_adaptive_rx_coalesce;

	tx_vector->tx_group.coal.पूर्णांक_gl = cmd->tx_coalesce_usecs;
	rx_vector->rx_group.coal.पूर्णांक_gl = cmd->rx_coalesce_usecs;

	tx_vector->tx_group.coal.पूर्णांक_ql = cmd->tx_max_coalesced_frames;
	rx_vector->rx_group.coal.पूर्णांक_ql = cmd->rx_max_coalesced_frames;

	hns3_set_vector_coalesce_tx_gl(tx_vector,
				       tx_vector->tx_group.coal.पूर्णांक_gl);
	hns3_set_vector_coalesce_rx_gl(rx_vector,
				       rx_vector->rx_group.coal.पूर्णांक_gl);

	hns3_set_vector_coalesce_rl(tx_vector, h->kinfo.पूर्णांक_rl_setting);
	hns3_set_vector_coalesce_rl(rx_vector, h->kinfo.पूर्णांक_rl_setting);

	अगर (tx_vector->tx_group.coal.ql_enable)
		hns3_set_vector_coalesce_tx_ql(tx_vector,
					       tx_vector->tx_group.coal.पूर्णांक_ql);
	अगर (rx_vector->rx_group.coal.ql_enable)
		hns3_set_vector_coalesce_rx_ql(rx_vector,
					       rx_vector->rx_group.coal.पूर्णांक_ql);
पूर्ण

अटल पूर्णांक hns3_set_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *cmd)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hns3_enet_coalesce *tx_coal = &priv->tx_coal;
	काष्ठा hns3_enet_coalesce *rx_coal = &priv->rx_coal;
	u16 queue_num = h->kinfo.num_tqps;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (hns3_nic_resetting(netdev))
		वापस -EBUSY;

	ret = hns3_check_coalesce_para(netdev, cmd);
	अगर (ret)
		वापस ret;

	h->kinfo.पूर्णांक_rl_setting =
		hns3_rl_round_करोwn(cmd->rx_coalesce_usecs_high);

	tx_coal->adapt_enable = cmd->use_adaptive_tx_coalesce;
	rx_coal->adapt_enable = cmd->use_adaptive_rx_coalesce;

	tx_coal->पूर्णांक_gl = cmd->tx_coalesce_usecs;
	rx_coal->पूर्णांक_gl = cmd->rx_coalesce_usecs;

	tx_coal->पूर्णांक_ql = cmd->tx_max_coalesced_frames;
	rx_coal->पूर्णांक_ql = cmd->rx_max_coalesced_frames;

	क्रम (i = 0; i < queue_num; i++)
		hns3_set_coalesce_per_queue(netdev, cmd, i);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_get_regs_len(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (!h->ae_algo->ops->get_regs_len)
		वापस -EOPNOTSUPP;

	वापस h->ae_algo->ops->get_regs_len(h);
पूर्ण

अटल व्योम hns3_get_regs(काष्ठा net_device *netdev,
			  काष्ठा ethtool_regs *cmd, व्योम *data)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (!h->ae_algo->ops->get_regs)
		वापस;

	h->ae_algo->ops->get_regs(h, &cmd->version, data);
पूर्ण

अटल पूर्णांक hns3_set_phys_id(काष्ठा net_device *netdev,
			    क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (!h->ae_algo->ops->set_led_id)
		वापस -EOPNOTSUPP;

	वापस h->ae_algo->ops->set_led_id(h, state);
पूर्ण

अटल u32 hns3_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	वापस h->msg_enable;
पूर्ण

अटल व्योम hns3_set_msglevel(काष्ठा net_device *netdev, u32 msg_level)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	h->msg_enable = msg_level;
पूर्ण

/* Translate local fec value पूर्णांकo ethtool value. */
अटल अचिन्हित पूर्णांक loc_to_eth_fec(u8 loc_fec)
अणु
	u32 eth_fec = 0;

	अगर (loc_fec & BIT(HNAE3_FEC_AUTO))
		eth_fec |= ETHTOOL_FEC_AUTO;
	अगर (loc_fec & BIT(HNAE3_FEC_RS))
		eth_fec |= ETHTOOL_FEC_RS;
	अगर (loc_fec & BIT(HNAE3_FEC_BASER))
		eth_fec |= ETHTOOL_FEC_BASER;

	/* अगर nothing is set, then FEC is off */
	अगर (!eth_fec)
		eth_fec = ETHTOOL_FEC_OFF;

	वापस eth_fec;
पूर्ण

/* Translate ethtool fec value पूर्णांकo local value. */
अटल अचिन्हित पूर्णांक eth_to_loc_fec(अचिन्हित पूर्णांक eth_fec)
अणु
	u32 loc_fec = 0;

	अगर (eth_fec & ETHTOOL_FEC_OFF)
		वापस loc_fec;

	अगर (eth_fec & ETHTOOL_FEC_AUTO)
		loc_fec |= BIT(HNAE3_FEC_AUTO);
	अगर (eth_fec & ETHTOOL_FEC_RS)
		loc_fec |= BIT(HNAE3_FEC_RS);
	अगर (eth_fec & ETHTOOL_FEC_BASER)
		loc_fec |= BIT(HNAE3_FEC_BASER);

	वापस loc_fec;
पूर्ण

अटल पूर्णांक hns3_get_fecparam(काष्ठा net_device *netdev,
			     काष्ठा ethtool_fecparam *fec)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	u8 fec_ability;
	u8 fec_mode;

	अगर (!test_bit(HNAE3_DEV_SUPPORT_FEC_B, ae_dev->caps))
		वापस -EOPNOTSUPP;

	अगर (!ops->get_fec)
		वापस -EOPNOTSUPP;

	ops->get_fec(handle, &fec_ability, &fec_mode);

	fec->fec = loc_to_eth_fec(fec_ability);
	fec->active_fec = loc_to_eth_fec(fec_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_set_fecparam(काष्ठा net_device *netdev,
			     काष्ठा ethtool_fecparam *fec)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	u32 fec_mode;

	अगर (!test_bit(HNAE3_DEV_SUPPORT_FEC_B, ae_dev->caps))
		वापस -EOPNOTSUPP;

	अगर (!ops->set_fec)
		वापस -EOPNOTSUPP;
	fec_mode = eth_to_loc_fec(fec->fec);

	netअगर_dbg(handle, drv, netdev, "set fecparam: mode=%u\n", fec_mode);

	वापस ops->set_fec(handle, fec_mode);
पूर्ण

अटल पूर्णांक hns3_get_module_info(काष्ठा net_device *netdev,
				काष्ठा ethtool_modinfo *modinfo)
अणु
#घोषणा HNS3_SFF_8636_V1_3 0x03

	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	काष्ठा hns3_sfp_type sfp_type;
	पूर्णांक ret;

	अगर (ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2 ||
	    !ops->get_module_eeprom)
		वापस -EOPNOTSUPP;

	स_रखो(&sfp_type, 0, माप(sfp_type));
	ret = ops->get_module_eeprom(handle, 0, माप(sfp_type) / माप(u8),
				     (u8 *)&sfp_type);
	अगर (ret)
		वापस ret;

	चयन (sfp_type.type) अणु
	हाल SFF8024_ID_SFP:
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		अवरोध;
	हाल SFF8024_ID_QSFP_8438:
		modinfo->type = ETH_MODULE_SFF_8436;
		modinfo->eeprom_len = ETH_MODULE_SFF_8436_MAX_LEN;
		अवरोध;
	हाल SFF8024_ID_QSFP_8436_8636:
		अगर (sfp_type.ext_type < HNS3_SFF_8636_V1_3) अणु
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_MAX_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_MAX_LEN;
		पूर्ण
		अवरोध;
	हाल SFF8024_ID_QSFP28_8636:
		modinfo->type = ETH_MODULE_SFF_8636;
		modinfo->eeprom_len = ETH_MODULE_SFF_8636_MAX_LEN;
		अवरोध;
	शेष:
		netdev_err(netdev, "Optical module unknown: %#x\n",
			   sfp_type.type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_get_module_eeprom(काष्ठा net_device *netdev,
				  काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;

	अगर (ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2 ||
	    !ops->get_module_eeprom)
		वापस -EOPNOTSUPP;

	अगर (!ee->len)
		वापस -EINVAL;

	स_रखो(data, 0, ee->len);

	वापस ops->get_module_eeprom(handle, ee->offset, ee->len, data);
पूर्ण

अटल u32 hns3_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);

	वापस handle->priv_flags;
पूर्ण

अटल पूर्णांक hns3_check_priv_flags(काष्ठा hnae3_handle *h, u32 changed)
अणु
	u32 i;

	क्रम (i = 0; i < HNAE3_PFLAG_MAX; i++)
		अगर ((changed & BIT(i)) && !test_bit(i, &h->supported_pflags)) अणु
			netdev_err(h->netdev, "%s is unsupported\n",
				   hns3_priv_flags[i].name);
			वापस -EOPNOTSUPP;
		पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_set_priv_flags(काष्ठा net_device *netdev, u32 pflags)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);
	u32 changed = pflags ^ handle->priv_flags;
	पूर्णांक ret;
	u32 i;

	ret = hns3_check_priv_flags(handle, changed);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < HNAE3_PFLAG_MAX; i++) अणु
		अगर (changed & BIT(i)) अणु
			bool enable = !(handle->priv_flags & BIT(i));

			अगर (enable)
				handle->priv_flags |= BIT(i);
			अन्यथा
				handle->priv_flags &= ~BIT(i);
			hns3_priv_flags[i].handler(netdev, enable);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा HNS3_ETHTOOL_COALESCE	(ETHTOOL_COALESCE_USECS |		\
				 ETHTOOL_COALESCE_USE_ADAPTIVE |	\
				 ETHTOOL_COALESCE_RX_USECS_HIGH |	\
				 ETHTOOL_COALESCE_TX_USECS_HIGH |	\
				 ETHTOOL_COALESCE_MAX_FRAMES)

अटल स्थिर काष्ठा ethtool_ops hns3vf_ethtool_ops = अणु
	.supported_coalesce_params = HNS3_ETHTOOL_COALESCE,
	.get_drvinfo = hns3_get_drvinfo,
	.get_ringparam = hns3_get_ringparam,
	.set_ringparam = hns3_set_ringparam,
	.get_strings = hns3_get_strings,
	.get_ethtool_stats = hns3_get_stats,
	.get_sset_count = hns3_get_sset_count,
	.get_rxnfc = hns3_get_rxnfc,
	.set_rxnfc = hns3_set_rxnfc,
	.get_rxfh_key_size = hns3_get_rss_key_size,
	.get_rxfh_indir_size = hns3_get_rss_indir_size,
	.get_rxfh = hns3_get_rss,
	.set_rxfh = hns3_set_rss,
	.get_link_ksettings = hns3_get_link_ksettings,
	.get_channels = hns3_get_channels,
	.set_channels = hns3_set_channels,
	.get_coalesce = hns3_get_coalesce,
	.set_coalesce = hns3_set_coalesce,
	.get_regs_len = hns3_get_regs_len,
	.get_regs = hns3_get_regs,
	.get_link = hns3_get_link,
	.get_msglevel = hns3_get_msglevel,
	.set_msglevel = hns3_set_msglevel,
	.get_priv_flags = hns3_get_priv_flags,
	.set_priv_flags = hns3_set_priv_flags,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops hns3_ethtool_ops = अणु
	.supported_coalesce_params = HNS3_ETHTOOL_COALESCE,
	.self_test = hns3_self_test,
	.get_drvinfo = hns3_get_drvinfo,
	.get_link = hns3_get_link,
	.get_ringparam = hns3_get_ringparam,
	.set_ringparam = hns3_set_ringparam,
	.get_छोड़ोparam = hns3_get_छोड़ोparam,
	.set_छोड़ोparam = hns3_set_छोड़ोparam,
	.get_strings = hns3_get_strings,
	.get_ethtool_stats = hns3_get_stats,
	.get_sset_count = hns3_get_sset_count,
	.get_rxnfc = hns3_get_rxnfc,
	.set_rxnfc = hns3_set_rxnfc,
	.get_rxfh_key_size = hns3_get_rss_key_size,
	.get_rxfh_indir_size = hns3_get_rss_indir_size,
	.get_rxfh = hns3_get_rss,
	.set_rxfh = hns3_set_rss,
	.get_link_ksettings = hns3_get_link_ksettings,
	.set_link_ksettings = hns3_set_link_ksettings,
	.nway_reset = hns3_nway_reset,
	.get_channels = hns3_get_channels,
	.set_channels = hns3_set_channels,
	.get_coalesce = hns3_get_coalesce,
	.set_coalesce = hns3_set_coalesce,
	.get_regs_len = hns3_get_regs_len,
	.get_regs = hns3_get_regs,
	.set_phys_id = hns3_set_phys_id,
	.get_msglevel = hns3_get_msglevel,
	.set_msglevel = hns3_set_msglevel,
	.get_fecparam = hns3_get_fecparam,
	.set_fecparam = hns3_set_fecparam,
	.get_module_info = hns3_get_module_info,
	.get_module_eeprom = hns3_get_module_eeprom,
	.get_priv_flags = hns3_get_priv_flags,
	.set_priv_flags = hns3_set_priv_flags,
पूर्ण;

व्योम hns3_ethtool_set_ops(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (h->flags & HNAE3_SUPPORT_VF)
		netdev->ethtool_ops = &hns3vf_ethtool_ops;
	अन्यथा
		netdev->ethtool_ops = &hns3_ethtool_ops;
पूर्ण
