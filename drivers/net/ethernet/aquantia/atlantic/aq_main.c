<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_मुख्य.c: Main file क्रम aQuantia Linux driver. */

#समावेश "aq_main.h"
#समावेश "aq_nic.h"
#समावेश "aq_pci_func.h"
#समावेश "aq_ethtool.h"
#समावेश "aq_ptp.h"
#समावेश "aq_filters.h"
#समावेश "aq_hw_utils.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <net/pkt_cls.h>

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(AQ_CFG_DRV_AUTHOR);
MODULE_DESCRIPTION(AQ_CFG_DRV_DESC);

अटल स्थिर अक्षर aq_ndev_driver_name[] = AQ_CFG_DRV_NAME;

अटल स्थिर काष्ठा net_device_ops aq_ndev_ops;

अटल काष्ठा workqueue_काष्ठा *aq_ndev_wq;

व्योम aq_ndev_schedule_work(काष्ठा work_काष्ठा *work)
अणु
	queue_work(aq_ndev_wq, work);
पूर्ण

काष्ठा net_device *aq_ndev_alloc(व्योम)
अणु
	काष्ठा net_device *ndev = शून्य;
	काष्ठा aq_nic_s *aq_nic = शून्य;

	ndev = alloc_etherdev_mq(माप(काष्ठा aq_nic_s), AQ_HW_QUEUES_MAX);
	अगर (!ndev)
		वापस शून्य;

	aq_nic = netdev_priv(ndev);
	aq_nic->ndev = ndev;
	ndev->netdev_ops = &aq_ndev_ops;
	ndev->ethtool_ops = &aq_ethtool_ops;

	वापस ndev;
पूर्ण

अटल पूर्णांक aq_ndev_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	पूर्णांक err = 0;

	err = aq_nic_init(aq_nic);
	अगर (err < 0)
		जाओ err_निकास;

	err = aq_reapply_rxnfc_all_rules(aq_nic);
	अगर (err < 0)
		जाओ err_निकास;

	err = aq_filters_vlans_update(aq_nic);
	अगर (err < 0)
		जाओ err_निकास;

	err = aq_nic_start(aq_nic);
	अगर (err < 0) अणु
		aq_nic_stop(aq_nic);
		जाओ err_निकास;
	पूर्ण

err_निकास:
	अगर (err < 0)
		aq_nic_deinit(aq_nic, true);

	वापस err;
पूर्ण

अटल पूर्णांक aq_ndev_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	पूर्णांक err = 0;

	err = aq_nic_stop(aq_nic);
	अगर (err < 0)
		जाओ err_निकास;
	aq_nic_deinit(aq_nic, true);

err_निकास:
	वापस err;
पूर्ण

अटल netdev_tx_t aq_ndev_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
	अगर (unlikely(aq_utils_obj_test(&aq_nic->flags, AQ_NIC_PTP_DPATH_UP))) अणु
		/* Hardware adds the Timestamp क्रम PTPv2 802.AS1
		 * and PTPv2 IPv4 UDP.
		 * We have to push even general 320 port messages to the ptp
		 * queue explicitly. This is a limitation of current firmware
		 * and hardware PTP design of the chip. Otherwise ptp stream
		 * will fail to sync
		 */
		अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) ||
		    unlikely((ip_hdr(skb)->version == 4) &&
			     (ip_hdr(skb)->protocol == IPPROTO_UDP) &&
			     ((udp_hdr(skb)->dest == htons(319)) ||
			      (udp_hdr(skb)->dest == htons(320)))) ||
		    unlikely(eth_hdr(skb)->h_proto == htons(ETH_P_1588)))
			वापस aq_ptp_xmit(aq_nic, skb);
	पूर्ण
#पूर्ण_अगर

	skb_tx_बारtamp(skb);
	वापस aq_nic_xmit(aq_nic, skb);
पूर्ण

अटल पूर्णांक aq_ndev_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	पूर्णांक err;

	err = aq_nic_set_mtu(aq_nic, new_mtu + ETH_HLEN);

	अगर (err < 0)
		जाओ err_निकास;
	ndev->mtu = new_mtu;

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक aq_ndev_set_features(काष्ठा net_device *ndev,
				netdev_features_t features)
अणु
	bool is_vlan_tx_insert = !!(features & NETIF_F_HW_VLAN_CTAG_TX);
	bool is_vlan_rx_strip = !!(features & NETIF_F_HW_VLAN_CTAG_RX);
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	bool need_ndev_restart = false;
	काष्ठा aq_nic_cfg_s *aq_cfg;
	bool is_lro = false;
	पूर्णांक err = 0;

	aq_cfg = aq_nic_get_cfg(aq_nic);

	अगर (!(features & NETIF_F_NTUPLE)) अणु
		अगर (aq_nic->ndev->features & NETIF_F_NTUPLE) अणु
			err = aq_clear_rxnfc_all_rules(aq_nic);
			अगर (unlikely(err))
				जाओ err_निकास;
		पूर्ण
	पूर्ण
	अगर (!(features & NETIF_F_HW_VLAN_CTAG_FILTER)) अणु
		अगर (aq_nic->ndev->features & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
			err = aq_filters_vlan_offload_off(aq_nic);
			अगर (unlikely(err))
				जाओ err_निकास;
		पूर्ण
	पूर्ण

	aq_cfg->features = features;

	अगर (aq_cfg->aq_hw_caps->hw_features & NETIF_F_LRO) अणु
		is_lro = features & NETIF_F_LRO;

		अगर (aq_cfg->is_lro != is_lro) अणु
			aq_cfg->is_lro = is_lro;
			need_ndev_restart = true;
		पूर्ण
	पूर्ण

	अगर ((aq_nic->ndev->features ^ features) & NETIF_F_RXCSUM) अणु
		err = aq_nic->aq_hw_ops->hw_set_offload(aq_nic->aq_hw,
							aq_cfg);

		अगर (unlikely(err))
			जाओ err_निकास;
	पूर्ण

	अगर (aq_cfg->is_vlan_rx_strip != is_vlan_rx_strip) अणु
		aq_cfg->is_vlan_rx_strip = is_vlan_rx_strip;
		need_ndev_restart = true;
	पूर्ण
	अगर (aq_cfg->is_vlan_tx_insert != is_vlan_tx_insert) अणु
		aq_cfg->is_vlan_tx_insert = is_vlan_tx_insert;
		need_ndev_restart = true;
	पूर्ण

	अगर (need_ndev_restart && netअगर_running(ndev)) अणु
		aq_ndev_बंद(ndev);
		aq_ndev_खोलो(ndev);
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक aq_ndev_set_mac_address(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	पूर्णांक err = 0;

	err = eth_mac_addr(ndev, addr);
	अगर (err < 0)
		जाओ err_निकास;
	err = aq_nic_set_mac(aq_nic, ndev);
	अगर (err < 0)
		जाओ err_निकास;

err_निकास:
	वापस err;
पूर्ण

अटल व्योम aq_ndev_set_multicast_settings(काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	(व्योम)aq_nic_set_multicast_list(aq_nic, ndev);
पूर्ण

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
अटल पूर्णांक aq_ndev_config_hwtstamp(काष्ठा aq_nic_s *aq_nic,
				   काष्ठा hwtstamp_config *config)
अणु
	अगर (config->flags)
		वापस -EINVAL;

	चयन (config->tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config->rx_filter) अणु
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_NONE:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	वापस aq_ptp_hwtstamp_config_set(aq_nic->aq_ptp, config);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक aq_ndev_hwtstamp_set(काष्ठा aq_nic_s *aq_nic, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
	पूर्णांक ret_val;
#पूर्ण_अगर

	अगर (!aq_nic->aq_ptp)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;
#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
	ret_val = aq_ndev_config_hwtstamp(aq_nic, &config);
	अगर (ret_val)
		वापस ret_val;
#पूर्ण_अगर

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
	       -EFAULT : 0;
पूर्ण

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
अटल पूर्णांक aq_ndev_hwtstamp_get(काष्ठा aq_nic_s *aq_nic, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;

	अगर (!aq_nic->aq_ptp)
		वापस -EOPNOTSUPP;

	aq_ptp_hwtstamp_config_get(aq_nic->aq_ptp, &config);
	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
	       -EFAULT : 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक aq_ndev_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(netdev);

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस aq_ndev_hwtstamp_set(aq_nic, अगरr);

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
	हाल SIOCGHWTSTAMP:
		वापस aq_ndev_hwtstamp_get(aq_nic, अगरr);
#पूर्ण_अगर
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक aq_nकरो_vlan_rx_add_vid(काष्ठा net_device *ndev, __be16 proto,
				  u16 vid)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	अगर (!aq_nic->aq_hw_ops->hw_filter_vlan_set)
		वापस -EOPNOTSUPP;

	set_bit(vid, aq_nic->active_vlans);

	वापस aq_filters_vlans_update(aq_nic);
पूर्ण

अटल पूर्णांक aq_nकरो_vlan_rx_समाप्त_vid(काष्ठा net_device *ndev, __be16 proto,
				   u16 vid)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	अगर (!aq_nic->aq_hw_ops->hw_filter_vlan_set)
		वापस -EOPNOTSUPP;

	clear_bit(vid, aq_nic->active_vlans);

	अगर (-ENOENT == aq_del_fvlan_by_vlan(aq_nic, vid))
		वापस aq_filters_vlans_update(aq_nic);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_validate_mqprio_opt(काष्ठा aq_nic_s *self,
				  काष्ठा tc_mqprio_qopt_offload *mqprio,
				  स्थिर अचिन्हित पूर्णांक num_tc)
अणु
	स्थिर bool has_min_rate = !!(mqprio->flags & TC_MQPRIO_F_MIN_RATE);
	काष्ठा aq_nic_cfg_s *aq_nic_cfg = aq_nic_get_cfg(self);
	स्थिर अचिन्हित पूर्णांक tcs_max = min_t(u8, aq_nic_cfg->aq_hw_caps->tcs_max,
					   AQ_CFG_TCS_MAX);

	अगर (num_tc > tcs_max) अणु
		netdev_err(self->ndev, "Too many TCs requested\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (num_tc != 0 && !is_घातer_of_2(num_tc)) अणु
		netdev_err(self->ndev, "TC count should be power of 2\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (has_min_rate && !ATL_HW_IS_CHIP_FEATURE(self->aq_hw, ANTIGUA)) अणु
		netdev_err(self->ndev, "Min tx rate is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aq_nकरो_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			   व्योम *type_data)
अणु
	काष्ठा tc_mqprio_qopt_offload *mqprio = type_data;
	काष्ठा aq_nic_s *aq_nic = netdev_priv(dev);
	bool has_min_rate;
	bool has_max_rate;
	पूर्णांक err;
	पूर्णांक i;

	अगर (type != TC_SETUP_QDISC_MQPRIO)
		वापस -EOPNOTSUPP;

	has_min_rate = !!(mqprio->flags & TC_MQPRIO_F_MIN_RATE);
	has_max_rate = !!(mqprio->flags & TC_MQPRIO_F_MAX_RATE);

	err = aq_validate_mqprio_opt(aq_nic, mqprio, mqprio->qopt.num_tc);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < mqprio->qopt.num_tc; i++) अणु
		अगर (has_max_rate) अणु
			u64 max_rate = mqprio->max_rate[i];

			करो_भाग(max_rate, AQ_MBPS_DIVISOR);
			aq_nic_setup_tc_max_rate(aq_nic, i, (u32)max_rate);
		पूर्ण

		अगर (has_min_rate) अणु
			u64 min_rate = mqprio->min_rate[i];

			करो_भाग(min_rate, AQ_MBPS_DIVISOR);
			aq_nic_setup_tc_min_rate(aq_nic, i, (u32)min_rate);
		पूर्ण
	पूर्ण

	वापस aq_nic_setup_tc_mqprio(aq_nic, mqprio->qopt.num_tc,
				      mqprio->qopt.prio_tc_map);
पूर्ण

अटल स्थिर काष्ठा net_device_ops aq_ndev_ops = अणु
	.nकरो_खोलो = aq_ndev_खोलो,
	.nकरो_stop = aq_ndev_बंद,
	.nकरो_start_xmit = aq_ndev_start_xmit,
	.nकरो_set_rx_mode = aq_ndev_set_multicast_settings,
	.nकरो_change_mtu = aq_ndev_change_mtu,
	.nकरो_set_mac_address = aq_ndev_set_mac_address,
	.nकरो_set_features = aq_ndev_set_features,
	.nकरो_करो_ioctl = aq_ndev_ioctl,
	.nकरो_vlan_rx_add_vid = aq_nकरो_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = aq_nकरो_vlan_rx_समाप्त_vid,
	.nकरो_setup_tc = aq_nकरो_setup_tc,
पूर्ण;

अटल पूर्णांक __init aq_ndev_init_module(व्योम)
अणु
	पूर्णांक ret;

	aq_ndev_wq = create_singlethपढ़ो_workqueue(aq_ndev_driver_name);
	अगर (!aq_ndev_wq) अणु
		pr_err("Failed to create workqueue\n");
		वापस -ENOMEM;
	पूर्ण

	ret = aq_pci_func_रेजिस्टर_driver();
	अगर (ret) अणु
		destroy_workqueue(aq_ndev_wq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास aq_ndev_निकास_module(व्योम)
अणु
	aq_pci_func_unरेजिस्टर_driver();

	अगर (aq_ndev_wq) अणु
		destroy_workqueue(aq_ndev_wq);
		aq_ndev_wq = शून्य;
	पूर्ण
पूर्ण

module_init(aq_ndev_init_module);
module_निकास(aq_ndev_निकास_module);
