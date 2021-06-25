<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qede NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/crash_dump.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/param.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdev_features.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>
#समावेश <net/udp_tunnel.h>
#समावेश <linux/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/tcp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/in.h>
#समावेश <linux/अक्रमom.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/bitops.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/aer.h>
#समावेश "qede.h"
#समावेश "qede_ptp.h"

अटल अक्षर version[] =
	"QLogic FastLinQ 4xxxx Ethernet Driver qede " DRV_MODULE_VERSION "\n";

MODULE_DESCRIPTION("QLogic FastLinQ 4xxxx Ethernet Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

अटल uपूर्णांक debug;
module_param(debug, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, " Default debug msglevel");

अटल स्थिर काष्ठा qed_eth_ops *qed_ops;

#घोषणा CHIP_NUM_57980S_40		0x1634
#घोषणा CHIP_NUM_57980S_10		0x1666
#घोषणा CHIP_NUM_57980S_MF		0x1636
#घोषणा CHIP_NUM_57980S_100		0x1644
#घोषणा CHIP_NUM_57980S_50		0x1654
#घोषणा CHIP_NUM_57980S_25		0x1656
#घोषणा CHIP_NUM_57980S_IOV		0x1664
#घोषणा CHIP_NUM_AH			0x8070
#घोषणा CHIP_NUM_AH_IOV			0x8090

#अगर_अघोषित PCI_DEVICE_ID_NX2_57980E
#घोषणा PCI_DEVICE_ID_57980S_40		CHIP_NUM_57980S_40
#घोषणा PCI_DEVICE_ID_57980S_10		CHIP_NUM_57980S_10
#घोषणा PCI_DEVICE_ID_57980S_MF		CHIP_NUM_57980S_MF
#घोषणा PCI_DEVICE_ID_57980S_100	CHIP_NUM_57980S_100
#घोषणा PCI_DEVICE_ID_57980S_50		CHIP_NUM_57980S_50
#घोषणा PCI_DEVICE_ID_57980S_25		CHIP_NUM_57980S_25
#घोषणा PCI_DEVICE_ID_57980S_IOV	CHIP_NUM_57980S_IOV
#घोषणा PCI_DEVICE_ID_AH		CHIP_NUM_AH
#घोषणा PCI_DEVICE_ID_AH_IOV		CHIP_NUM_AH_IOV

#पूर्ण_अगर

क्रमागत qede_pci_निजी अणु
	QEDE_PRIVATE_PF,
	QEDE_PRIVATE_VF
पूर्ण;

अटल स्थिर काष्ठा pci_device_id qede_pci_tbl[] = अणु
	अणुPCI_VDEVICE(QLOGIC, PCI_DEVICE_ID_57980S_40), QEDE_PRIVATE_PFपूर्ण,
	अणुPCI_VDEVICE(QLOGIC, PCI_DEVICE_ID_57980S_10), QEDE_PRIVATE_PFपूर्ण,
	अणुPCI_VDEVICE(QLOGIC, PCI_DEVICE_ID_57980S_MF), QEDE_PRIVATE_PFपूर्ण,
	अणुPCI_VDEVICE(QLOGIC, PCI_DEVICE_ID_57980S_100), QEDE_PRIVATE_PFपूर्ण,
	अणुPCI_VDEVICE(QLOGIC, PCI_DEVICE_ID_57980S_50), QEDE_PRIVATE_PFपूर्ण,
	अणुPCI_VDEVICE(QLOGIC, PCI_DEVICE_ID_57980S_25), QEDE_PRIVATE_PFपूर्ण,
#अगर_घोषित CONFIG_QED_SRIOV
	अणुPCI_VDEVICE(QLOGIC, PCI_DEVICE_ID_57980S_IOV), QEDE_PRIVATE_VFपूर्ण,
#पूर्ण_अगर
	अणुPCI_VDEVICE(QLOGIC, PCI_DEVICE_ID_AH), QEDE_PRIVATE_PFपूर्ण,
#अगर_घोषित CONFIG_QED_SRIOV
	अणुPCI_VDEVICE(QLOGIC, PCI_DEVICE_ID_AH_IOV), QEDE_PRIVATE_VFपूर्ण,
#पूर्ण_अगर
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, qede_pci_tbl);

अटल पूर्णांक qede_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id);
अटल pci_ers_result_t
qede_io_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state);

#घोषणा TX_TIMEOUT		(5 * HZ)

/* Utilize last protocol index क्रम XDP */
#घोषणा XDP_PI	11

अटल व्योम qede_हटाओ(काष्ठा pci_dev *pdev);
अटल व्योम qede_shutकरोwn(काष्ठा pci_dev *pdev);
अटल व्योम qede_link_update(व्योम *dev, काष्ठा qed_link_output *link);
अटल व्योम qede_schedule_recovery_handler(व्योम *dev);
अटल व्योम qede_recovery_handler(काष्ठा qede_dev *edev);
अटल व्योम qede_schedule_hw_err_handler(व्योम *dev,
					 क्रमागत qed_hw_err_type err_type);
अटल व्योम qede_get_eth_tlv_data(व्योम *edev, व्योम *data);
अटल व्योम qede_get_generic_tlv_data(व्योम *edev,
				      काष्ठा qed_generic_tlvs *data);
अटल व्योम qede_generic_hw_err_handler(काष्ठा qede_dev *edev);
#अगर_घोषित CONFIG_QED_SRIOV
अटल पूर्णांक qede_set_vf_vlan(काष्ठा net_device *ndev, पूर्णांक vf, u16 vlan, u8 qos,
			    __be16 vlan_proto)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);

	अगर (vlan > 4095) अणु
		DP_NOTICE(edev, "Illegal vlan value %d\n", vlan);
		वापस -EINVAL;
	पूर्ण

	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	DP_VERBOSE(edev, QED_MSG_IOV, "Setting Vlan 0x%04x to VF [%d]\n",
		   vlan, vf);

	वापस edev->ops->iov->set_vlan(edev->cdev, vlan, vf);
पूर्ण

अटल पूर्णांक qede_set_vf_mac(काष्ठा net_device *ndev, पूर्णांक vfidx, u8 *mac)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);

	DP_VERBOSE(edev, QED_MSG_IOV, "Setting MAC %pM to VF [%d]\n", mac, vfidx);

	अगर (!is_valid_ether_addr(mac)) अणु
		DP_VERBOSE(edev, QED_MSG_IOV, "MAC address isn't valid\n");
		वापस -EINVAL;
	पूर्ण

	वापस edev->ops->iov->set_mac(edev->cdev, mac, vfidx);
पूर्ण

अटल पूर्णांक qede_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs_param)
अणु
	काष्ठा qede_dev *edev = netdev_priv(pci_get_drvdata(pdev));
	काष्ठा qed_dev_info *qed_info = &edev->dev_info.common;
	काष्ठा qed_update_vport_params *vport_params;
	पूर्णांक rc;

	vport_params = vzalloc(माप(*vport_params));
	अगर (!vport_params)
		वापस -ENOMEM;
	DP_VERBOSE(edev, QED_MSG_IOV, "Requested %d VFs\n", num_vfs_param);

	rc = edev->ops->iov->configure(edev->cdev, num_vfs_param);

	/* Enable/Disable Tx चयनing क्रम PF */
	अगर ((rc == num_vfs_param) && netअगर_running(edev->ndev) &&
	    !qed_info->b_पूर्णांकer_pf_चयन && qed_info->tx_चयनing) अणु
		vport_params->vport_id = 0;
		vport_params->update_tx_चयनing_flg = 1;
		vport_params->tx_चयनing_flg = num_vfs_param ? 1 : 0;
		edev->ops->vport_update(edev->cdev, vport_params);
	पूर्ण

	vमुक्त(vport_params);
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_error_handlers qede_err_handler = अणु
	.error_detected = qede_io_error_detected,
पूर्ण;

अटल काष्ठा pci_driver qede_pci_driver = अणु
	.name = "qede",
	.id_table = qede_pci_tbl,
	.probe = qede_probe,
	.हटाओ = qede_हटाओ,
	.shutकरोwn = qede_shutकरोwn,
#अगर_घोषित CONFIG_QED_SRIOV
	.sriov_configure = qede_sriov_configure,
#पूर्ण_अगर
	.err_handler = &qede_err_handler,
पूर्ण;

अटल काष्ठा qed_eth_cb_ops qede_ll_ops = अणु
	अणु
#अगर_घोषित CONFIG_RFS_ACCEL
		.arfs_filter_op = qede_arfs_filter_op,
#पूर्ण_अगर
		.link_update = qede_link_update,
		.schedule_recovery_handler = qede_schedule_recovery_handler,
		.schedule_hw_err_handler = qede_schedule_hw_err_handler,
		.get_generic_tlv_data = qede_get_generic_tlv_data,
		.get_protocol_tlv_data = qede_get_eth_tlv_data,
	पूर्ण,
	.क्रमce_mac = qede_क्रमce_mac,
	.ports_update = qede_udp_ports_update,
पूर्ण;

अटल पूर्णांक qede_netdev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा ethtool_drvinfo drvinfo;
	काष्ठा qede_dev *edev;

	अगर (event != NETDEV_CHANGENAME && event != NETDEV_CHANGEADDR)
		जाओ करोne;

	/* Check whether this is a qede device */
	अगर (!ndev || !ndev->ethtool_ops || !ndev->ethtool_ops->get_drvinfo)
		जाओ करोne;

	स_रखो(&drvinfo, 0, माप(drvinfo));
	ndev->ethtool_ops->get_drvinfo(ndev, &drvinfo);
	अगर (म_भेद(drvinfo.driver, "qede"))
		जाओ करोne;
	edev = netdev_priv(ndev);

	चयन (event) अणु
	हाल NETDEV_CHANGENAME:
		/* Notअगरy qed of the name change */
		अगर (!edev->ops || !edev->ops->common)
			जाओ करोne;
		edev->ops->common->set_name(edev->cdev, edev->ndev->name);
		अवरोध;
	हाल NETDEV_CHANGEADDR:
		edev = netdev_priv(ndev);
		qede_rdma_event_changeaddr(edev);
		अवरोध;
	पूर्ण

करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block qede_netdev_notअगरier = अणु
	.notअगरier_call = qede_netdev_event,
पूर्ण;

अटल
पूर्णांक __init qede_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("qede_init: %s\n", version);

	qede_क्रमced_speed_maps_init();

	qed_ops = qed_get_eth_ops();
	अगर (!qed_ops) अणु
		pr_notice("Failed to get qed ethtool operations\n");
		वापस -EINVAL;
	पूर्ण

	/* Must रेजिस्टर notअगरier beक्रमe pci ops, since we might miss
	 * पूर्णांकerface नाम after pci probe and netdev registration.
	 */
	ret = रेजिस्टर_netdevice_notअगरier(&qede_netdev_notअगरier);
	अगर (ret) अणु
		pr_notice("Failed to register netdevice_notifier\n");
		qed_put_eth_ops();
		वापस -EINVAL;
	पूर्ण

	ret = pci_रेजिस्टर_driver(&qede_pci_driver);
	अगर (ret) अणु
		pr_notice("Failed to register driver\n");
		unरेजिस्टर_netdevice_notअगरier(&qede_netdev_notअगरier);
		qed_put_eth_ops();
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास qede_cleanup(व्योम)
अणु
	अगर (debug & QED_LOG_INFO_MASK)
		pr_info("qede_cleanup called\n");

	unरेजिस्टर_netdevice_notअगरier(&qede_netdev_notअगरier);
	pci_unरेजिस्टर_driver(&qede_pci_driver);
	qed_put_eth_ops();
पूर्ण

module_init(qede_init);
module_निकास(qede_cleanup);

अटल पूर्णांक qede_खोलो(काष्ठा net_device *ndev);
अटल पूर्णांक qede_बंद(काष्ठा net_device *ndev);

व्योम qede_fill_by_demand_stats(काष्ठा qede_dev *edev)
अणु
	काष्ठा qede_stats_common *p_common = &edev->stats.common;
	काष्ठा qed_eth_stats stats;

	edev->ops->get_vport_stats(edev->cdev, &stats);

	p_common->no_buff_discards = stats.common.no_buff_discards;
	p_common->packet_too_big_discard = stats.common.packet_too_big_discard;
	p_common->ttl0_discard = stats.common.ttl0_discard;
	p_common->rx_ucast_bytes = stats.common.rx_ucast_bytes;
	p_common->rx_mcast_bytes = stats.common.rx_mcast_bytes;
	p_common->rx_bcast_bytes = stats.common.rx_bcast_bytes;
	p_common->rx_ucast_pkts = stats.common.rx_ucast_pkts;
	p_common->rx_mcast_pkts = stats.common.rx_mcast_pkts;
	p_common->rx_bcast_pkts = stats.common.rx_bcast_pkts;
	p_common->mftag_filter_discards = stats.common.mftag_filter_discards;
	p_common->mac_filter_discards = stats.common.mac_filter_discards;
	p_common->gft_filter_drop = stats.common.gft_filter_drop;

	p_common->tx_ucast_bytes = stats.common.tx_ucast_bytes;
	p_common->tx_mcast_bytes = stats.common.tx_mcast_bytes;
	p_common->tx_bcast_bytes = stats.common.tx_bcast_bytes;
	p_common->tx_ucast_pkts = stats.common.tx_ucast_pkts;
	p_common->tx_mcast_pkts = stats.common.tx_mcast_pkts;
	p_common->tx_bcast_pkts = stats.common.tx_bcast_pkts;
	p_common->tx_err_drop_pkts = stats.common.tx_err_drop_pkts;
	p_common->coalesced_pkts = stats.common.tpa_coalesced_pkts;
	p_common->coalesced_events = stats.common.tpa_coalesced_events;
	p_common->coalesced_पातs_num = stats.common.tpa_पातs_num;
	p_common->non_coalesced_pkts = stats.common.tpa_not_coalesced_pkts;
	p_common->coalesced_bytes = stats.common.tpa_coalesced_bytes;

	p_common->rx_64_byte_packets = stats.common.rx_64_byte_packets;
	p_common->rx_65_to_127_byte_packets =
	    stats.common.rx_65_to_127_byte_packets;
	p_common->rx_128_to_255_byte_packets =
	    stats.common.rx_128_to_255_byte_packets;
	p_common->rx_256_to_511_byte_packets =
	    stats.common.rx_256_to_511_byte_packets;
	p_common->rx_512_to_1023_byte_packets =
	    stats.common.rx_512_to_1023_byte_packets;
	p_common->rx_1024_to_1518_byte_packets =
	    stats.common.rx_1024_to_1518_byte_packets;
	p_common->rx_crc_errors = stats.common.rx_crc_errors;
	p_common->rx_mac_crtl_frames = stats.common.rx_mac_crtl_frames;
	p_common->rx_छोड़ो_frames = stats.common.rx_छोड़ो_frames;
	p_common->rx_pfc_frames = stats.common.rx_pfc_frames;
	p_common->rx_align_errors = stats.common.rx_align_errors;
	p_common->rx_carrier_errors = stats.common.rx_carrier_errors;
	p_common->rx_oversize_packets = stats.common.rx_oversize_packets;
	p_common->rx_jabbers = stats.common.rx_jabbers;
	p_common->rx_undersize_packets = stats.common.rx_undersize_packets;
	p_common->rx_fragments = stats.common.rx_fragments;
	p_common->tx_64_byte_packets = stats.common.tx_64_byte_packets;
	p_common->tx_65_to_127_byte_packets =
	    stats.common.tx_65_to_127_byte_packets;
	p_common->tx_128_to_255_byte_packets =
	    stats.common.tx_128_to_255_byte_packets;
	p_common->tx_256_to_511_byte_packets =
	    stats.common.tx_256_to_511_byte_packets;
	p_common->tx_512_to_1023_byte_packets =
	    stats.common.tx_512_to_1023_byte_packets;
	p_common->tx_1024_to_1518_byte_packets =
	    stats.common.tx_1024_to_1518_byte_packets;
	p_common->tx_छोड़ो_frames = stats.common.tx_छोड़ो_frames;
	p_common->tx_pfc_frames = stats.common.tx_pfc_frames;
	p_common->brb_truncates = stats.common.brb_truncates;
	p_common->brb_discards = stats.common.brb_discards;
	p_common->tx_mac_ctrl_frames = stats.common.tx_mac_ctrl_frames;
	p_common->link_change_count = stats.common.link_change_count;
	p_common->ptp_skip_txts = edev->ptp_skip_txts;

	अगर (QEDE_IS_BB(edev)) अणु
		काष्ठा qede_stats_bb *p_bb = &edev->stats.bb;

		p_bb->rx_1519_to_1522_byte_packets =
		    stats.bb.rx_1519_to_1522_byte_packets;
		p_bb->rx_1519_to_2047_byte_packets =
		    stats.bb.rx_1519_to_2047_byte_packets;
		p_bb->rx_2048_to_4095_byte_packets =
		    stats.bb.rx_2048_to_4095_byte_packets;
		p_bb->rx_4096_to_9216_byte_packets =
		    stats.bb.rx_4096_to_9216_byte_packets;
		p_bb->rx_9217_to_16383_byte_packets =
		    stats.bb.rx_9217_to_16383_byte_packets;
		p_bb->tx_1519_to_2047_byte_packets =
		    stats.bb.tx_1519_to_2047_byte_packets;
		p_bb->tx_2048_to_4095_byte_packets =
		    stats.bb.tx_2048_to_4095_byte_packets;
		p_bb->tx_4096_to_9216_byte_packets =
		    stats.bb.tx_4096_to_9216_byte_packets;
		p_bb->tx_9217_to_16383_byte_packets =
		    stats.bb.tx_9217_to_16383_byte_packets;
		p_bb->tx_lpi_entry_count = stats.bb.tx_lpi_entry_count;
		p_bb->tx_total_collisions = stats.bb.tx_total_collisions;
	पूर्ण अन्यथा अणु
		काष्ठा qede_stats_ah *p_ah = &edev->stats.ah;

		p_ah->rx_1519_to_max_byte_packets =
		    stats.ah.rx_1519_to_max_byte_packets;
		p_ah->tx_1519_to_max_byte_packets =
		    stats.ah.tx_1519_to_max_byte_packets;
	पूर्ण
पूर्ण

अटल व्योम qede_get_stats64(काष्ठा net_device *dev,
			     काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qede_stats_common *p_common;

	qede_fill_by_demand_stats(edev);
	p_common = &edev->stats.common;

	stats->rx_packets = p_common->rx_ucast_pkts + p_common->rx_mcast_pkts +
			    p_common->rx_bcast_pkts;
	stats->tx_packets = p_common->tx_ucast_pkts + p_common->tx_mcast_pkts +
			    p_common->tx_bcast_pkts;

	stats->rx_bytes = p_common->rx_ucast_bytes + p_common->rx_mcast_bytes +
			  p_common->rx_bcast_bytes;
	stats->tx_bytes = p_common->tx_ucast_bytes + p_common->tx_mcast_bytes +
			  p_common->tx_bcast_bytes;

	stats->tx_errors = p_common->tx_err_drop_pkts;
	stats->multicast = p_common->rx_mcast_pkts + p_common->rx_bcast_pkts;

	stats->rx_fअगरo_errors = p_common->no_buff_discards;

	अगर (QEDE_IS_BB(edev))
		stats->collisions = edev->stats.bb.tx_total_collisions;
	stats->rx_crc_errors = p_common->rx_crc_errors;
	stats->rx_frame_errors = p_common->rx_align_errors;
पूर्ण

#अगर_घोषित CONFIG_QED_SRIOV
अटल पूर्णांक qede_get_vf_config(काष्ठा net_device *dev, पूर्णांक vfidx,
			      काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	अगर (!edev->ops)
		वापस -EINVAL;

	वापस edev->ops->iov->get_config(edev->cdev, vfidx, ivi);
पूर्ण

अटल पूर्णांक qede_set_vf_rate(काष्ठा net_device *dev, पूर्णांक vfidx,
			    पूर्णांक min_tx_rate, पूर्णांक max_tx_rate)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	वापस edev->ops->iov->set_rate(edev->cdev, vfidx, min_tx_rate,
					max_tx_rate);
पूर्ण

अटल पूर्णांक qede_set_vf_spoofchk(काष्ठा net_device *dev, पूर्णांक vfidx, bool val)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	अगर (!edev->ops)
		वापस -EINVAL;

	वापस edev->ops->iov->set_spoof(edev->cdev, vfidx, val);
पूर्ण

अटल पूर्णांक qede_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक vfidx,
				  पूर्णांक link_state)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	अगर (!edev->ops)
		वापस -EINVAL;

	वापस edev->ops->iov->set_link_state(edev->cdev, vfidx, link_state);
पूर्ण

अटल पूर्णांक qede_set_vf_trust(काष्ठा net_device *dev, पूर्णांक vfidx, bool setting)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	अगर (!edev->ops)
		वापस -EINVAL;

	वापस edev->ops->iov->set_trust(edev->cdev, vfidx, setting);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक qede_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस -EAGAIN;

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस qede_ptp_hw_ts(edev, अगरr);
	शेष:
		DP_VERBOSE(edev, QED_MSG_DEBUG,
			   "default IOCTL cmd 0x%x\n", cmd);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qede_tx_log_prपूर्णांक(काष्ठा qede_dev *edev, काष्ठा qede_tx_queue *txq)
अणु
	DP_NOTICE(edev,
		  "Txq[%d]: FW cons [host] %04x, SW cons %04x, SW prod %04x [Jiffies %lu]\n",
		  txq->index, le16_to_cpu(*txq->hw_cons_ptr),
		  qed_chain_get_cons_idx(&txq->tx_pbl),
		  qed_chain_get_prod_idx(&txq->tx_pbl),
		  jअगरfies);
पूर्ण

अटल व्योम qede_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा qede_tx_queue *txq;
	पूर्णांक cos;

	netअगर_carrier_off(dev);
	DP_NOTICE(edev, "TX timeout on queue %u!\n", txqueue);

	अगर (!(edev->fp_array[txqueue].type & QEDE_FASTPATH_TX))
		वापस;

	क्रम_each_cos_in_txq(edev, cos) अणु
		txq = &edev->fp_array[txqueue].txq[cos];

		अगर (qed_chain_get_cons_idx(&txq->tx_pbl) !=
		    qed_chain_get_prod_idx(&txq->tx_pbl))
			qede_tx_log_prपूर्णांक(edev, txq);
	पूर्ण

	अगर (IS_VF(edev))
		वापस;

	अगर (test_and_set_bit(QEDE_ERR_IS_HANDLED, &edev->err_flags) ||
	    edev->state == QEDE_STATE_RECOVERY) अणु
		DP_INFO(edev,
			"Avoid handling a Tx timeout while another HW error is being handled\n");
		वापस;
	पूर्ण

	set_bit(QEDE_ERR_GET_DBG_INFO, &edev->err_flags);
	set_bit(QEDE_SP_HW_ERR, &edev->sp_flags);
	schedule_delayed_work(&edev->sp_task, 0);
पूर्ण

अटल पूर्णांक qede_setup_tc(काष्ठा net_device *ndev, u8 num_tc)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	पूर्णांक cos, count, offset;

	अगर (num_tc > edev->dev_info.num_tc)
		वापस -EINVAL;

	netdev_reset_tc(ndev);
	netdev_set_num_tc(ndev, num_tc);

	क्रम_each_cos_in_txq(edev, cos) अणु
		count = QEDE_TSS_COUNT(edev);
		offset = cos * QEDE_TSS_COUNT(edev);
		netdev_set_tc_queue(ndev, cos, count, offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qede_set_flower(काष्ठा qede_dev *edev, काष्ठा flow_cls_offload *f,
		__be16 proto)
अणु
	चयन (f->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस qede_add_tc_flower_fltr(edev, proto, f);
	हाल FLOW_CLS_DESTROY:
		वापस qede_delete_flow_filter(edev, f->cookie);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक qede_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				  व्योम *cb_priv)
अणु
	काष्ठा flow_cls_offload *f;
	काष्ठा qede_dev *edev = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(edev->ndev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		f = type_data;
		वापस qede_set_flower(edev, f, f->common.protocol);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(qede_block_cb_list);

अटल पूर्णांक
qede_setup_tc_offload(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
		      व्योम *type_data)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा tc_mqprio_qopt *mqprio;

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &qede_block_cb_list,
						  qede_setup_tc_block_cb,
						  edev, edev, true);
	हाल TC_SETUP_QDISC_MQPRIO:
		mqprio = type_data;

		mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
		वापस qede_setup_tc(dev, mqprio->num_tc);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops qede_netdev_ops = अणु
	.nकरो_खोलो		= qede_खोलो,
	.nकरो_stop		= qede_बंद,
	.nकरो_start_xmit		= qede_start_xmit,
	.nकरो_select_queue	= qede_select_queue,
	.nकरो_set_rx_mode	= qede_set_rx_mode,
	.nकरो_set_mac_address	= qede_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= qede_change_mtu,
	.nकरो_करो_ioctl		= qede_ioctl,
	.nकरो_tx_समयout		= qede_tx_समयout,
#अगर_घोषित CONFIG_QED_SRIOV
	.nकरो_set_vf_mac		= qede_set_vf_mac,
	.nकरो_set_vf_vlan	= qede_set_vf_vlan,
	.nकरो_set_vf_trust	= qede_set_vf_trust,
#पूर्ण_अगर
	.nकरो_vlan_rx_add_vid	= qede_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= qede_vlan_rx_समाप्त_vid,
	.nकरो_fix_features	= qede_fix_features,
	.nकरो_set_features	= qede_set_features,
	.nकरो_get_stats64	= qede_get_stats64,
#अगर_घोषित CONFIG_QED_SRIOV
	.nकरो_set_vf_link_state	= qede_set_vf_link_state,
	.nकरो_set_vf_spoofchk	= qede_set_vf_spoofchk,
	.nकरो_get_vf_config	= qede_get_vf_config,
	.nकरो_set_vf_rate	= qede_set_vf_rate,
#पूर्ण_अगर
	.nकरो_features_check	= qede_features_check,
	.nकरो_bpf		= qede_xdp,
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer	= qede_rx_flow_steer,
#पूर्ण_अगर
	.nकरो_xdp_xmit		= qede_xdp_transmit,
	.nकरो_setup_tc		= qede_setup_tc_offload,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops qede_netdev_vf_ops = अणु
	.nकरो_खोलो		= qede_खोलो,
	.nकरो_stop		= qede_बंद,
	.nकरो_start_xmit		= qede_start_xmit,
	.nकरो_select_queue	= qede_select_queue,
	.nकरो_set_rx_mode	= qede_set_rx_mode,
	.nकरो_set_mac_address	= qede_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= qede_change_mtu,
	.nकरो_vlan_rx_add_vid	= qede_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= qede_vlan_rx_समाप्त_vid,
	.nकरो_fix_features	= qede_fix_features,
	.nकरो_set_features	= qede_set_features,
	.nकरो_get_stats64	= qede_get_stats64,
	.nकरो_features_check	= qede_features_check,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops qede_netdev_vf_xdp_ops = अणु
	.nकरो_खोलो		= qede_खोलो,
	.nकरो_stop		= qede_बंद,
	.nकरो_start_xmit		= qede_start_xmit,
	.nकरो_select_queue	= qede_select_queue,
	.nकरो_set_rx_mode	= qede_set_rx_mode,
	.nकरो_set_mac_address	= qede_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= qede_change_mtu,
	.nकरो_vlan_rx_add_vid	= qede_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= qede_vlan_rx_समाप्त_vid,
	.nकरो_fix_features	= qede_fix_features,
	.nकरो_set_features	= qede_set_features,
	.nकरो_get_stats64	= qede_get_stats64,
	.nकरो_features_check	= qede_features_check,
	.nकरो_bpf		= qede_xdp,
	.nकरो_xdp_xmit		= qede_xdp_transmit,
पूर्ण;

/* -------------------------------------------------------------------------
 * START OF PROBE / REMOVE
 * -------------------------------------------------------------------------
 */

अटल काष्ठा qede_dev *qede_alloc_etherdev(काष्ठा qed_dev *cdev,
					    काष्ठा pci_dev *pdev,
					    काष्ठा qed_dev_eth_info *info,
					    u32 dp_module, u8 dp_level)
अणु
	काष्ठा net_device *ndev;
	काष्ठा qede_dev *edev;

	ndev = alloc_etherdev_mqs(माप(*edev),
				  info->num_queues * info->num_tc,
				  info->num_queues);
	अगर (!ndev) अणु
		pr_err("etherdev allocation failed\n");
		वापस शून्य;
	पूर्ण

	edev = netdev_priv(ndev);
	edev->ndev = ndev;
	edev->cdev = cdev;
	edev->pdev = pdev;
	edev->dp_module = dp_module;
	edev->dp_level = dp_level;
	edev->ops = qed_ops;

	अगर (is_kdump_kernel()) अणु
		edev->q_num_rx_buffers = NUM_RX_BDS_KDUMP_MIN;
		edev->q_num_tx_buffers = NUM_TX_BDS_KDUMP_MIN;
	पूर्ण अन्यथा अणु
		edev->q_num_rx_buffers = NUM_RX_BDS_DEF;
		edev->q_num_tx_buffers = NUM_TX_BDS_DEF;
	पूर्ण

	DP_INFO(edev, "Allocated netdev with %d tx queues and %d rx queues\n",
		info->num_queues, info->num_queues);

	SET_NETDEV_DEV(ndev, &pdev->dev);

	स_रखो(&edev->stats, 0, माप(edev->stats));
	स_नकल(&edev->dev_info, info, माप(*info));

	/* As ethtool करोesn't have the ability to show WoL behavior as
	 * 'default', if device supports it declare it's enabled.
	 */
	अगर (edev->dev_info.common.wol_support)
		edev->wol_enabled = true;

	INIT_LIST_HEAD(&edev->vlan_list);

	वापस edev;
पूर्ण

अटल व्योम qede_init_ndev(काष्ठा qede_dev *edev)
अणु
	काष्ठा net_device *ndev = edev->ndev;
	काष्ठा pci_dev *pdev = edev->pdev;
	bool udp_tunnel_enable = false;
	netdev_features_t hw_features;

	pci_set_drvdata(pdev, ndev);

	ndev->mem_start = edev->dev_info.common.pci_mem_start;
	ndev->base_addr = ndev->mem_start;
	ndev->mem_end = edev->dev_info.common.pci_mem_end;
	ndev->irq = edev->dev_info.common.pci_irq;

	ndev->watchकरोg_समयo = TX_TIMEOUT;

	अगर (IS_VF(edev)) अणु
		अगर (edev->dev_info.xdp_supported)
			ndev->netdev_ops = &qede_netdev_vf_xdp_ops;
		अन्यथा
			ndev->netdev_ops = &qede_netdev_vf_ops;
	पूर्ण अन्यथा अणु
		ndev->netdev_ops = &qede_netdev_ops;
	पूर्ण

	qede_set_ethtool_ops(ndev);

	ndev->priv_flags |= IFF_UNICAST_FLT;

	/* user-changeble features */
	hw_features = NETIF_F_GRO | NETIF_F_GRO_HW | NETIF_F_SG |
		      NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		      NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_HW_TC;

	अगर (edev->dev_info.common.b_arfs_capable)
		hw_features |= NETIF_F_NTUPLE;

	अगर (edev->dev_info.common.vxlan_enable ||
	    edev->dev_info.common.geneve_enable)
		udp_tunnel_enable = true;

	अगर (udp_tunnel_enable || edev->dev_info.common.gre_enable) अणु
		hw_features |= NETIF_F_TSO_ECN;
		ndev->hw_enc_features = NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
					NETIF_F_SG | NETIF_F_TSO |
					NETIF_F_TSO_ECN | NETIF_F_TSO6 |
					NETIF_F_RXCSUM;
	पूर्ण

	अगर (udp_tunnel_enable) अणु
		hw_features |= (NETIF_F_GSO_UDP_TUNNEL |
				NETIF_F_GSO_UDP_TUNNEL_CSUM);
		ndev->hw_enc_features |= (NETIF_F_GSO_UDP_TUNNEL |
					  NETIF_F_GSO_UDP_TUNNEL_CSUM);

		qede_set_udp_tunnels(edev);
	पूर्ण

	अगर (edev->dev_info.common.gre_enable) अणु
		hw_features |= (NETIF_F_GSO_GRE | NETIF_F_GSO_GRE_CSUM);
		ndev->hw_enc_features |= (NETIF_F_GSO_GRE |
					  NETIF_F_GSO_GRE_CSUM);
	पूर्ण

	ndev->vlan_features = hw_features | NETIF_F_RXHASH | NETIF_F_RXCSUM |
			      NETIF_F_HIGHDMA;
	ndev->features = hw_features | NETIF_F_RXHASH | NETIF_F_RXCSUM |
			 NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HIGHDMA |
			 NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_HW_VLAN_CTAG_TX;

	ndev->hw_features = hw_features;

	/* MTU range: 46 - 9600 */
	ndev->min_mtu = ETH_ZLEN - ETH_HLEN;
	ndev->max_mtu = QEDE_MAX_JUMBO_PACKET_SIZE;

	/* Set network device HW mac */
	ether_addr_copy(edev->ndev->dev_addr, edev->dev_info.common.hw_mac);

	ndev->mtu = edev->dev_info.common.mtu;
पूर्ण

/* This function converts from 32b param to two params of level and module
 * Input 32b decoding:
 * b31 - enable all NOTICE prपूर्णांकs. NOTICE prपूर्णांकs are क्रम deviation from the
 * 'happy' flow, e.g. memory allocation failed.
 * b30 - enable all INFO prपूर्णांकs. INFO prपूर्णांकs are क्रम major steps in the flow
 * and provide important parameters.
 * b29-b0 - per-module biपंचांगap, where each bit enables VERBOSE prपूर्णांकs of that
 * module. VERBOSE prपूर्णांकs are क्रम tracking the specअगरic flow in low level.
 *
 * Notice that the level should be that of the lowest required logs.
 */
व्योम qede_config_debug(uपूर्णांक debug, u32 *p_dp_module, u8 *p_dp_level)
अणु
	*p_dp_level = QED_LEVEL_NOTICE;
	*p_dp_module = 0;

	अगर (debug & QED_LOG_VERBOSE_MASK) अणु
		*p_dp_level = QED_LEVEL_VERBOSE;
		*p_dp_module = (debug & 0x3FFFFFFF);
	पूर्ण अन्यथा अगर (debug & QED_LOG_INFO_MASK) अणु
		*p_dp_level = QED_LEVEL_INFO;
	पूर्ण अन्यथा अगर (debug & QED_LOG_NOTICE_MASK) अणु
		*p_dp_level = QED_LEVEL_NOTICE;
	पूर्ण
पूर्ण

अटल व्योम qede_मुक्त_fp_array(काष्ठा qede_dev *edev)
अणु
	अगर (edev->fp_array) अणु
		काष्ठा qede_fastpath *fp;
		पूर्णांक i;

		क्रम_each_queue(i) अणु
			fp = &edev->fp_array[i];

			kमुक्त(fp->sb_info);
			/* Handle mem alloc failure हाल where qede_init_fp
			 * didn't रेजिस्टर xdp_rxq_info yet.
			 * Implicit only (fp->type & QEDE_FASTPATH_RX)
			 */
			अगर (fp->rxq && xdp_rxq_info_is_reg(&fp->rxq->xdp_rxq))
				xdp_rxq_info_unreg(&fp->rxq->xdp_rxq);
			kमुक्त(fp->rxq);
			kमुक्त(fp->xdp_tx);
			kमुक्त(fp->txq);
		पूर्ण
		kमुक्त(edev->fp_array);
	पूर्ण

	edev->num_queues = 0;
	edev->fp_num_tx = 0;
	edev->fp_num_rx = 0;
पूर्ण

अटल पूर्णांक qede_alloc_fp_array(काष्ठा qede_dev *edev)
अणु
	u8 fp_combined, fp_rx = edev->fp_num_rx;
	काष्ठा qede_fastpath *fp;
	व्योम *mem;
	पूर्णांक i;

	edev->fp_array = kसुस्मृति(QEDE_QUEUE_CNT(edev),
				 माप(*edev->fp_array), GFP_KERNEL);
	अगर (!edev->fp_array) अणु
		DP_NOTICE(edev, "fp array allocation failed\n");
		जाओ err;
	पूर्ण

	mem = kपुनः_स्मृति(edev->coal_entry, QEDE_QUEUE_CNT(edev) *
		       माप(*edev->coal_entry), GFP_KERNEL);
	अगर (!mem) अणु
		DP_ERR(edev, "coalesce entry allocation failed\n");
		kमुक्त(edev->coal_entry);
		जाओ err;
	पूर्ण
	edev->coal_entry = mem;

	fp_combined = QEDE_QUEUE_CNT(edev) - fp_rx - edev->fp_num_tx;

	/* Allocate the FP elements क्रम Rx queues followed by combined and then
	 * the Tx. This ordering should be मुख्यtained so that the respective
	 * queues (Rx or Tx) will be together in the fastpath array and the
	 * associated ids will be sequential.
	 */
	क्रम_each_queue(i) अणु
		fp = &edev->fp_array[i];

		fp->sb_info = kzalloc(माप(*fp->sb_info), GFP_KERNEL);
		अगर (!fp->sb_info) अणु
			DP_NOTICE(edev, "sb info struct allocation failed\n");
			जाओ err;
		पूर्ण

		अगर (fp_rx) अणु
			fp->type = QEDE_FASTPATH_RX;
			fp_rx--;
		पूर्ण अन्यथा अगर (fp_combined) अणु
			fp->type = QEDE_FASTPATH_COMBINED;
			fp_combined--;
		पूर्ण अन्यथा अणु
			fp->type = QEDE_FASTPATH_TX;
		पूर्ण

		अगर (fp->type & QEDE_FASTPATH_TX) अणु
			fp->txq = kसुस्मृति(edev->dev_info.num_tc,
					  माप(*fp->txq), GFP_KERNEL);
			अगर (!fp->txq)
				जाओ err;
		पूर्ण

		अगर (fp->type & QEDE_FASTPATH_RX) अणु
			fp->rxq = kzalloc(माप(*fp->rxq), GFP_KERNEL);
			अगर (!fp->rxq)
				जाओ err;

			अगर (edev->xdp_prog) अणु
				fp->xdp_tx = kzalloc(माप(*fp->xdp_tx),
						     GFP_KERNEL);
				अगर (!fp->xdp_tx)
					जाओ err;
				fp->type |= QEDE_FASTPATH_XDP;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
err:
	qede_मुक्त_fp_array(edev);
	वापस -ENOMEM;
पूर्ण

/* The qede lock is used to protect driver state change and driver flows that
 * are not reentrant.
 */
व्योम __qede_lock(काष्ठा qede_dev *edev)
अणु
	mutex_lock(&edev->qede_lock);
पूर्ण

व्योम __qede_unlock(काष्ठा qede_dev *edev)
अणु
	mutex_unlock(&edev->qede_lock);
पूर्ण

/* This version of the lock should be used when acquiring the RTNL lock is also
 * needed in addition to the पूर्णांकernal qede lock.
 */
अटल व्योम qede_lock(काष्ठा qede_dev *edev)
अणु
	rtnl_lock();
	__qede_lock(edev);
पूर्ण

अटल व्योम qede_unlock(काष्ठा qede_dev *edev)
अणु
	__qede_unlock(edev);
	rtnl_unlock();
पूर्ण

अटल व्योम qede_sp_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qede_dev *edev = container_of(work, काष्ठा qede_dev,
					     sp_task.work);

	/* The locking scheme depends on the specअगरic flag:
	 * In हाल of QEDE_SP_RECOVERY, acquiring the RTNL lock is required to
	 * ensure that ongoing flows are ended and new ones are not started.
	 * In other हालs - only the पूर्णांकernal qede lock should be acquired.
	 */

	अगर (test_and_clear_bit(QEDE_SP_RECOVERY, &edev->sp_flags)) अणु
#अगर_घोषित CONFIG_QED_SRIOV
		/* SRIOV must be disabled outside the lock to aव्योम a deadlock.
		 * The recovery of the active VFs is currently not supported.
		 */
		अगर (pci_num_vf(edev->pdev))
			qede_sriov_configure(edev->pdev, 0);
#पूर्ण_अगर
		qede_lock(edev);
		qede_recovery_handler(edev);
		qede_unlock(edev);
	पूर्ण

	__qede_lock(edev);

	अगर (test_and_clear_bit(QEDE_SP_RX_MODE, &edev->sp_flags))
		अगर (edev->state == QEDE_STATE_OPEN)
			qede_config_rx_mode(edev->ndev);

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर (test_and_clear_bit(QEDE_SP_ARFS_CONFIG, &edev->sp_flags)) अणु
		अगर (edev->state == QEDE_STATE_OPEN)
			qede_process_arfs_filters(edev, false);
	पूर्ण
#पूर्ण_अगर
	अगर (test_and_clear_bit(QEDE_SP_HW_ERR, &edev->sp_flags))
		qede_generic_hw_err_handler(edev);
	__qede_unlock(edev);

	अगर (test_and_clear_bit(QEDE_SP_AER, &edev->sp_flags)) अणु
#अगर_घोषित CONFIG_QED_SRIOV
		/* SRIOV must be disabled outside the lock to aव्योम a deadlock.
		 * The recovery of the active VFs is currently not supported.
		 */
		अगर (pci_num_vf(edev->pdev))
			qede_sriov_configure(edev->pdev, 0);
#पूर्ण_अगर
		edev->ops->common->recovery_process(edev->cdev);
	पूर्ण
पूर्ण

अटल व्योम qede_update_pf_params(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_pf_params pf_params;
	u16 num_cons;

	/* 64 rx + 64 tx + 64 XDP */
	स_रखो(&pf_params, 0, माप(काष्ठा qed_pf_params));

	/* 1 rx + 1 xdp + max tx cos */
	num_cons = QED_MIN_L2_CONS;

	pf_params.eth_pf_params.num_cons = (MAX_SB_PER_PF_MIMD - 1) * num_cons;

	/* Same क्रम VFs - make sure they'll have sufficient connections
	 * to support XDP Tx queues.
	 */
	pf_params.eth_pf_params.num_vf_cons = 48;

	pf_params.eth_pf_params.num_arfs_filters = QEDE_RFS_MAX_FLTR;
	qed_ops->common->update_pf_params(cdev, &pf_params);
पूर्ण

#घोषणा QEDE_FW_VER_STR_SIZE	80

अटल व्योम qede_log_probe(काष्ठा qede_dev *edev)
अणु
	काष्ठा qed_dev_info *p_dev_info = &edev->dev_info.common;
	u8 buf[QEDE_FW_VER_STR_SIZE];
	माप_प्रकार left_size;

	snम_लिखो(buf, QEDE_FW_VER_STR_SIZE,
		 "Storm FW %d.%d.%d.%d, Management FW %d.%d.%d.%d",
		 p_dev_info->fw_major, p_dev_info->fw_minor, p_dev_info->fw_rev,
		 p_dev_info->fw_eng,
		 (p_dev_info->mfw_rev & QED_MFW_VERSION_3_MASK) >>
		 QED_MFW_VERSION_3_OFFSET,
		 (p_dev_info->mfw_rev & QED_MFW_VERSION_2_MASK) >>
		 QED_MFW_VERSION_2_OFFSET,
		 (p_dev_info->mfw_rev & QED_MFW_VERSION_1_MASK) >>
		 QED_MFW_VERSION_1_OFFSET,
		 (p_dev_info->mfw_rev & QED_MFW_VERSION_0_MASK) >>
		 QED_MFW_VERSION_0_OFFSET);

	left_size = QEDE_FW_VER_STR_SIZE - म_माप(buf);
	अगर (p_dev_info->mbi_version && left_size)
		snम_लिखो(buf + म_माप(buf), left_size,
			 " [MBI %d.%d.%d]",
			 (p_dev_info->mbi_version & QED_MBI_VERSION_2_MASK) >>
			 QED_MBI_VERSION_2_OFFSET,
			 (p_dev_info->mbi_version & QED_MBI_VERSION_1_MASK) >>
			 QED_MBI_VERSION_1_OFFSET,
			 (p_dev_info->mbi_version & QED_MBI_VERSION_0_MASK) >>
			 QED_MBI_VERSION_0_OFFSET);

	pr_info("qede %02x:%02x.%02x: %s [%s]\n", edev->pdev->bus->number,
		PCI_SLOT(edev->pdev->devfn), PCI_FUNC(edev->pdev->devfn),
		buf, edev->ndev->name);
पूर्ण

क्रमागत qede_probe_mode अणु
	QEDE_PROBE_NORMAL,
	QEDE_PROBE_RECOVERY,
पूर्ण;

अटल पूर्णांक __qede_probe(काष्ठा pci_dev *pdev, u32 dp_module, u8 dp_level,
			bool is_vf, क्रमागत qede_probe_mode mode)
अणु
	काष्ठा qed_probe_params probe_params;
	काष्ठा qed_slowpath_params sp_params;
	काष्ठा qed_dev_eth_info dev_info;
	काष्ठा qede_dev *edev;
	काष्ठा qed_dev *cdev;
	पूर्णांक rc;

	अगर (unlikely(dp_level & QED_LEVEL_INFO))
		pr_notice("Starting qede probe\n");

	स_रखो(&probe_params, 0, माप(probe_params));
	probe_params.protocol = QED_PROTOCOL_ETH;
	probe_params.dp_module = dp_module;
	probe_params.dp_level = dp_level;
	probe_params.is_vf = is_vf;
	probe_params.recov_in_prog = (mode == QEDE_PROBE_RECOVERY);
	cdev = qed_ops->common->probe(pdev, &probe_params);
	अगर (!cdev) अणु
		rc = -ENODEV;
		जाओ err0;
	पूर्ण

	qede_update_pf_params(cdev);

	/* Start the Slowpath-process */
	स_रखो(&sp_params, 0, माप(sp_params));
	sp_params.पूर्णांक_mode = QED_INT_MODE_MSIX;
	sp_params.drv_major = QEDE_MAJOR_VERSION;
	sp_params.drv_minor = QEDE_MINOR_VERSION;
	sp_params.drv_rev = QEDE_REVISION_VERSION;
	sp_params.drv_eng = QEDE_ENGINEERING_VERSION;
	strlcpy(sp_params.name, "qede LAN", QED_DRV_VER_STR_SIZE);
	rc = qed_ops->common->slowpath_start(cdev, &sp_params);
	अगर (rc) अणु
		pr_notice("Cannot start slowpath\n");
		जाओ err1;
	पूर्ण

	/* Learn inक्रमmation crucial क्रम qede to progress */
	rc = qed_ops->fill_dev_info(cdev, &dev_info);
	अगर (rc)
		जाओ err2;

	अगर (mode != QEDE_PROBE_RECOVERY) अणु
		edev = qede_alloc_etherdev(cdev, pdev, &dev_info, dp_module,
					   dp_level);
		अगर (!edev) अणु
			rc = -ENOMEM;
			जाओ err2;
		पूर्ण

		edev->devlink = qed_ops->common->devlink_रेजिस्टर(cdev);
		अगर (IS_ERR(edev->devlink)) अणु
			DP_NOTICE(edev, "Cannot register devlink\n");
			edev->devlink = शून्य;
			/* Go on, we can live without devlink */
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा net_device *ndev = pci_get_drvdata(pdev);

		edev = netdev_priv(ndev);

		अगर (edev->devlink) अणु
			काष्ठा qed_devlink *qdl = devlink_priv(edev->devlink);

			qdl->cdev = cdev;
		पूर्ण
		edev->cdev = cdev;
		स_रखो(&edev->stats, 0, माप(edev->stats));
		स_नकल(&edev->dev_info, &dev_info, माप(dev_info));
	पूर्ण

	अगर (is_vf)
		set_bit(QEDE_FLAGS_IS_VF, &edev->flags);

	qede_init_ndev(edev);

	rc = qede_rdma_dev_add(edev, (mode == QEDE_PROBE_RECOVERY));
	अगर (rc)
		जाओ err3;

	अगर (mode != QEDE_PROBE_RECOVERY) अणु
		/* Prepare the lock prior to the registration of the netdev,
		 * as once it's रेजिस्टरed we might reach flows requiring it
		 * [it's even possible to reach a flow needing it directly
		 * from there, although it's unlikely].
		 */
		INIT_DELAYED_WORK(&edev->sp_task, qede_sp_task);
		mutex_init(&edev->qede_lock);

		rc = रेजिस्टर_netdev(edev->ndev);
		अगर (rc) अणु
			DP_NOTICE(edev, "Cannot register net-device\n");
			जाओ err4;
		पूर्ण
	पूर्ण

	edev->ops->common->set_name(cdev, edev->ndev->name);

	/* PTP not supported on VFs */
	अगर (!is_vf)
		qede_ptp_enable(edev);

	edev->ops->रेजिस्टर_ops(cdev, &qede_ll_ops, edev);

#अगर_घोषित CONFIG_DCB
	अगर (!IS_VF(edev))
		qede_set_dcbnl_ops(edev->ndev);
#पूर्ण_अगर

	edev->rx_copyअवरोध = QEDE_RX_HDR_SIZE;

	qede_log_probe(edev);
	वापस 0;

err4:
	qede_rdma_dev_हटाओ(edev, (mode == QEDE_PROBE_RECOVERY));
err3:
	अगर (mode != QEDE_PROBE_RECOVERY)
		मुक्त_netdev(edev->ndev);
	अन्यथा
		edev->cdev = शून्य;
err2:
	qed_ops->common->slowpath_stop(cdev);
err1:
	qed_ops->common->हटाओ(cdev);
err0:
	वापस rc;
पूर्ण

अटल पूर्णांक qede_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	bool is_vf = false;
	u32 dp_module = 0;
	u8 dp_level = 0;

	चयन ((क्रमागत qede_pci_निजी)id->driver_data) अणु
	हाल QEDE_PRIVATE_VF:
		अगर (debug & QED_LOG_VERBOSE_MASK)
			dev_err(&pdev->dev, "Probing a VF\n");
		is_vf = true;
		अवरोध;
	शेष:
		अगर (debug & QED_LOG_VERBOSE_MASK)
			dev_err(&pdev->dev, "Probing a PF\n");
	पूर्ण

	qede_config_debug(debug, &dp_module, &dp_level);

	वापस __qede_probe(pdev, dp_module, dp_level, is_vf,
			    QEDE_PROBE_NORMAL);
पूर्ण

क्रमागत qede_हटाओ_mode अणु
	QEDE_REMOVE_NORMAL,
	QEDE_REMOVE_RECOVERY,
पूर्ण;

अटल व्योम __qede_हटाओ(काष्ठा pci_dev *pdev, क्रमागत qede_हटाओ_mode mode)
अणु
	काष्ठा net_device *ndev = pci_get_drvdata(pdev);
	काष्ठा qede_dev *edev;
	काष्ठा qed_dev *cdev;

	अगर (!ndev) अणु
		dev_info(&pdev->dev, "Device has already been removed\n");
		वापस;
	पूर्ण

	edev = netdev_priv(ndev);
	cdev = edev->cdev;

	DP_INFO(edev, "Starting qede_remove\n");

	qede_rdma_dev_हटाओ(edev, (mode == QEDE_REMOVE_RECOVERY));

	अगर (mode != QEDE_REMOVE_RECOVERY) अणु
		unरेजिस्टर_netdev(ndev);

		cancel_delayed_work_sync(&edev->sp_task);

		edev->ops->common->set_घातer_state(cdev, PCI_D0);

		pci_set_drvdata(pdev, शून्य);
	पूर्ण

	qede_ptp_disable(edev);

	/* Use global ops since we've मुक्तd edev */
	qed_ops->common->slowpath_stop(cdev);
	अगर (प्रणाली_state == SYSTEM_POWER_OFF)
		वापस;

	अगर (mode != QEDE_REMOVE_RECOVERY && edev->devlink) अणु
		qed_ops->common->devlink_unरेजिस्टर(edev->devlink);
		edev->devlink = शून्य;
	पूर्ण
	qed_ops->common->हटाओ(cdev);
	edev->cdev = शून्य;

	/* Since this can happen out-of-sync with other flows,
	 * करोn't release the netdevice until after slowpath stop
	 * has been called to guarantee various other contexts
	 * [e.g., QED रेजिस्टर callbacks] won't अवरोध anything when
	 * accessing the netdevice.
	 */
	अगर (mode != QEDE_REMOVE_RECOVERY) अणु
		kमुक्त(edev->coal_entry);
		मुक्त_netdev(ndev);
	पूर्ण

	dev_info(&pdev->dev, "Ending qede_remove successfully\n");
पूर्ण

अटल व्योम qede_हटाओ(काष्ठा pci_dev *pdev)
अणु
	__qede_हटाओ(pdev, QEDE_REMOVE_NORMAL);
पूर्ण

अटल व्योम qede_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	__qede_हटाओ(pdev, QEDE_REMOVE_NORMAL);
पूर्ण

/* -------------------------------------------------------------------------
 * START OF LOAD / UNLOAD
 * -------------------------------------------------------------------------
 */

अटल पूर्णांक qede_set_num_queues(काष्ठा qede_dev *edev)
अणु
	पूर्णांक rc;
	u16 rss_num;

	/* Setup queues according to possible resources*/
	अगर (edev->req_queues)
		rss_num = edev->req_queues;
	अन्यथा
		rss_num = netअगर_get_num_शेष_rss_queues() *
			  edev->dev_info.common.num_hwfns;

	rss_num = min_t(u16, QEDE_MAX_RSS_CNT(edev), rss_num);

	rc = edev->ops->common->set_fp_पूर्णांक(edev->cdev, rss_num);
	अगर (rc > 0) अणु
		/* Managed to request पूर्णांकerrupts क्रम our queues */
		edev->num_queues = rc;
		DP_INFO(edev, "Managed %d [of %d] RSS queues\n",
			QEDE_QUEUE_CNT(edev), rss_num);
		rc = 0;
	पूर्ण

	edev->fp_num_tx = edev->req_num_tx;
	edev->fp_num_rx = edev->req_num_rx;

	वापस rc;
पूर्ण

अटल व्योम qede_मुक्त_mem_sb(काष्ठा qede_dev *edev, काष्ठा qed_sb_info *sb_info,
			     u16 sb_id)
अणु
	अगर (sb_info->sb_virt) अणु
		edev->ops->common->sb_release(edev->cdev, sb_info, sb_id,
					      QED_SB_TYPE_L2_QUEUE);
		dma_मुक्त_coherent(&edev->pdev->dev, माप(*sb_info->sb_virt),
				  (व्योम *)sb_info->sb_virt, sb_info->sb_phys);
		स_रखो(sb_info, 0, माप(*sb_info));
	पूर्ण
पूर्ण

/* This function allocates fast-path status block memory */
अटल पूर्णांक qede_alloc_mem_sb(काष्ठा qede_dev *edev,
			     काष्ठा qed_sb_info *sb_info, u16 sb_id)
अणु
	काष्ठा status_block_e4 *sb_virt;
	dma_addr_t sb_phys;
	पूर्णांक rc;

	sb_virt = dma_alloc_coherent(&edev->pdev->dev,
				     माप(*sb_virt), &sb_phys, GFP_KERNEL);
	अगर (!sb_virt) अणु
		DP_ERR(edev, "Status block allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	rc = edev->ops->common->sb_init(edev->cdev, sb_info,
					sb_virt, sb_phys, sb_id,
					QED_SB_TYPE_L2_QUEUE);
	अगर (rc) अणु
		DP_ERR(edev, "Status block initialization failed\n");
		dma_मुक्त_coherent(&edev->pdev->dev, माप(*sb_virt),
				  sb_virt, sb_phys);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qede_मुक्त_rx_buffers(काष्ठा qede_dev *edev,
				 काष्ठा qede_rx_queue *rxq)
अणु
	u16 i;

	क्रम (i = rxq->sw_rx_cons; i != rxq->sw_rx_prod; i++) अणु
		काष्ठा sw_rx_data *rx_buf;
		काष्ठा page *data;

		rx_buf = &rxq->sw_rx_ring[i & NUM_RX_BDS_MAX];
		data = rx_buf->data;

		dma_unmap_page(&edev->pdev->dev,
			       rx_buf->mapping, PAGE_SIZE, rxq->data_direction);

		rx_buf->data = शून्य;
		__मुक्त_page(data);
	पूर्ण
पूर्ण

अटल व्योम qede_मुक्त_mem_rxq(काष्ठा qede_dev *edev, काष्ठा qede_rx_queue *rxq)
अणु
	/* Free rx buffers */
	qede_मुक्त_rx_buffers(edev, rxq);

	/* Free the parallel SW ring */
	kमुक्त(rxq->sw_rx_ring);

	/* Free the real RQ ring used by FW */
	edev->ops->common->chain_मुक्त(edev->cdev, &rxq->rx_bd_ring);
	edev->ops->common->chain_मुक्त(edev->cdev, &rxq->rx_comp_ring);
पूर्ण

अटल व्योम qede_set_tpa_param(काष्ठा qede_rx_queue *rxq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ETH_TPA_MAX_AGGS_NUM; i++) अणु
		काष्ठा qede_agg_info *tpa_info = &rxq->tpa_info[i];

		tpa_info->state = QEDE_AGG_STATE_NONE;
	पूर्ण
पूर्ण

/* This function allocates all memory needed per Rx queue */
अटल पूर्णांक qede_alloc_mem_rxq(काष्ठा qede_dev *edev, काष्ठा qede_rx_queue *rxq)
अणु
	काष्ठा qed_chain_init_params params = अणु
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
		.num_elems	= RX_RING_SIZE,
	पूर्ण;
	काष्ठा qed_dev *cdev = edev->cdev;
	पूर्णांक i, rc, size;

	rxq->num_rx_buffers = edev->q_num_rx_buffers;

	rxq->rx_buf_size = NET_IP_ALIGN + ETH_OVERHEAD + edev->ndev->mtu;

	rxq->rx_headroom = edev->xdp_prog ? XDP_PACKET_HEADROOM : NET_SKB_PAD;
	size = rxq->rx_headroom +
	       SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	/* Make sure that the headroom and  payload fit in a single page */
	अगर (rxq->rx_buf_size + size > PAGE_SIZE)
		rxq->rx_buf_size = PAGE_SIZE - size;

	/* Segment size to split a page in multiple equal parts,
	 * unless XDP is used in which हाल we'd use the entire page.
	 */
	अगर (!edev->xdp_prog) अणु
		size = size + rxq->rx_buf_size;
		rxq->rx_buf_seg_size = roundup_घात_of_two(size);
	पूर्ण अन्यथा अणु
		rxq->rx_buf_seg_size = PAGE_SIZE;
		edev->ndev->features &= ~NETIF_F_GRO_HW;
	पूर्ण

	/* Allocate the parallel driver ring क्रम Rx buffers */
	size = माप(*rxq->sw_rx_ring) * RX_RING_SIZE;
	rxq->sw_rx_ring = kzalloc(size, GFP_KERNEL);
	अगर (!rxq->sw_rx_ring) अणु
		DP_ERR(edev, "Rx buffers ring allocation failed\n");
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	/* Allocate FW Rx ring  */
	params.mode = QED_CHAIN_MODE_NEXT_PTR;
	params.पूर्णांकended_use = QED_CHAIN_USE_TO_CONSUME_PRODUCE;
	params.elem_size = माप(काष्ठा eth_rx_bd);

	rc = edev->ops->common->chain_alloc(cdev, &rxq->rx_bd_ring, &params);
	अगर (rc)
		जाओ err;

	/* Allocate FW completion ring */
	params.mode = QED_CHAIN_MODE_PBL;
	params.पूर्णांकended_use = QED_CHAIN_USE_TO_CONSUME;
	params.elem_size = माप(जोड़ eth_rx_cqe);

	rc = edev->ops->common->chain_alloc(cdev, &rxq->rx_comp_ring, &params);
	अगर (rc)
		जाओ err;

	/* Allocate buffers क्रम the Rx ring */
	rxq->filled_buffers = 0;
	क्रम (i = 0; i < rxq->num_rx_buffers; i++) अणु
		rc = qede_alloc_rx_buffer(rxq, false);
		अगर (rc) अणु
			DP_ERR(edev,
			       "Rx buffers allocation failed at index %d\n", i);
			जाओ err;
		पूर्ण
	पूर्ण

	edev->gro_disable = !(edev->ndev->features & NETIF_F_GRO_HW);
	अगर (!edev->gro_disable)
		qede_set_tpa_param(rxq);
err:
	वापस rc;
पूर्ण

अटल व्योम qede_मुक्त_mem_txq(काष्ठा qede_dev *edev, काष्ठा qede_tx_queue *txq)
अणु
	/* Free the parallel SW ring */
	अगर (txq->is_xdp)
		kमुक्त(txq->sw_tx_ring.xdp);
	अन्यथा
		kमुक्त(txq->sw_tx_ring.skbs);

	/* Free the real RQ ring used by FW */
	edev->ops->common->chain_मुक्त(edev->cdev, &txq->tx_pbl);
पूर्ण

/* This function allocates all memory needed per Tx queue */
अटल पूर्णांक qede_alloc_mem_txq(काष्ठा qede_dev *edev, काष्ठा qede_tx_queue *txq)
अणु
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_CONSUME_PRODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
		.num_elems	= edev->q_num_tx_buffers,
		.elem_size	= माप(जोड़ eth_tx_bd_types),
	पूर्ण;
	पूर्णांक size, rc;

	txq->num_tx_buffers = edev->q_num_tx_buffers;

	/* Allocate the parallel driver ring क्रम Tx buffers */
	अगर (txq->is_xdp) अणु
		size = माप(*txq->sw_tx_ring.xdp) * txq->num_tx_buffers;
		txq->sw_tx_ring.xdp = kzalloc(size, GFP_KERNEL);
		अगर (!txq->sw_tx_ring.xdp)
			जाओ err;
	पूर्ण अन्यथा अणु
		size = माप(*txq->sw_tx_ring.skbs) * txq->num_tx_buffers;
		txq->sw_tx_ring.skbs = kzalloc(size, GFP_KERNEL);
		अगर (!txq->sw_tx_ring.skbs)
			जाओ err;
	पूर्ण

	rc = edev->ops->common->chain_alloc(edev->cdev, &txq->tx_pbl, &params);
	अगर (rc)
		जाओ err;

	वापस 0;

err:
	qede_मुक्त_mem_txq(edev, txq);
	वापस -ENOMEM;
पूर्ण

/* This function मुक्तs all memory of a single fp */
अटल व्योम qede_मुक्त_mem_fp(काष्ठा qede_dev *edev, काष्ठा qede_fastpath *fp)
अणु
	qede_मुक्त_mem_sb(edev, fp->sb_info, fp->id);

	अगर (fp->type & QEDE_FASTPATH_RX)
		qede_मुक्त_mem_rxq(edev, fp->rxq);

	अगर (fp->type & QEDE_FASTPATH_XDP)
		qede_मुक्त_mem_txq(edev, fp->xdp_tx);

	अगर (fp->type & QEDE_FASTPATH_TX) अणु
		पूर्णांक cos;

		क्रम_each_cos_in_txq(edev, cos)
			qede_मुक्त_mem_txq(edev, &fp->txq[cos]);
	पूर्ण
पूर्ण

/* This function allocates all memory needed क्रम a single fp (i.e. an entity
 * which contains status block, one rx queue and/or multiple per-TC tx queues.
 */
अटल पूर्णांक qede_alloc_mem_fp(काष्ठा qede_dev *edev, काष्ठा qede_fastpath *fp)
अणु
	पूर्णांक rc = 0;

	rc = qede_alloc_mem_sb(edev, fp->sb_info, fp->id);
	अगर (rc)
		जाओ out;

	अगर (fp->type & QEDE_FASTPATH_RX) अणु
		rc = qede_alloc_mem_rxq(edev, fp->rxq);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (fp->type & QEDE_FASTPATH_XDP) अणु
		rc = qede_alloc_mem_txq(edev, fp->xdp_tx);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (fp->type & QEDE_FASTPATH_TX) अणु
		पूर्णांक cos;

		क्रम_each_cos_in_txq(edev, cos) अणु
			rc = qede_alloc_mem_txq(edev, &fp->txq[cos]);
			अगर (rc)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस rc;
पूर्ण

अटल व्योम qede_मुक्त_mem_load(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i;

	क्रम_each_queue(i) अणु
		काष्ठा qede_fastpath *fp = &edev->fp_array[i];

		qede_मुक्त_mem_fp(edev, fp);
	पूर्ण
पूर्ण

/* This function allocates all qede memory at NIC load. */
अटल पूर्णांक qede_alloc_mem_load(काष्ठा qede_dev *edev)
अणु
	पूर्णांक rc = 0, queue_id;

	क्रम (queue_id = 0; queue_id < QEDE_QUEUE_CNT(edev); queue_id++) अणु
		काष्ठा qede_fastpath *fp = &edev->fp_array[queue_id];

		rc = qede_alloc_mem_fp(edev, fp);
		अगर (rc) अणु
			DP_ERR(edev,
			       "Failed to allocate memory for fastpath - rss id = %d\n",
			       queue_id);
			qede_मुक्त_mem_load(edev);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qede_empty_tx_queue(काष्ठा qede_dev *edev,
				काष्ठा qede_tx_queue *txq)
अणु
	अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;
	काष्ठा netdev_queue *netdev_txq;
	पूर्णांक rc, len = 0;

	netdev_txq = netdev_get_tx_queue(edev->ndev, txq->ndev_txq_id);

	जबतक (qed_chain_get_cons_idx(&txq->tx_pbl) !=
	       qed_chain_get_prod_idx(&txq->tx_pbl)) अणु
		DP_VERBOSE(edev, NETIF_MSG_IFDOWN,
			   "Freeing a packet on tx queue[%d]: chain_cons 0x%x, chain_prod 0x%x\n",
			   txq->index, qed_chain_get_cons_idx(&txq->tx_pbl),
			   qed_chain_get_prod_idx(&txq->tx_pbl));

		rc = qede_मुक्त_tx_pkt(edev, txq, &len);
		अगर (rc) अणु
			DP_NOTICE(edev,
				  "Failed to free a packet on tx queue[%d]: chain_cons 0x%x, chain_prod 0x%x\n",
				  txq->index,
				  qed_chain_get_cons_idx(&txq->tx_pbl),
				  qed_chain_get_prod_idx(&txq->tx_pbl));
			अवरोध;
		पूर्ण

		bytes_compl += len;
		pkts_compl++;
		txq->sw_tx_cons++;
	पूर्ण

	netdev_tx_completed_queue(netdev_txq, pkts_compl, bytes_compl);
पूर्ण

अटल व्योम qede_empty_tx_queues(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i;

	क्रम_each_queue(i)
		अगर (edev->fp_array[i].type & QEDE_FASTPATH_TX) अणु
			पूर्णांक cos;

			क्रम_each_cos_in_txq(edev, cos) अणु
				काष्ठा qede_fastpath *fp;

				fp = &edev->fp_array[i];
				qede_empty_tx_queue(edev,
						    &fp->txq[cos]);
			पूर्ण
		पूर्ण
पूर्ण

/* This function inits fp content and resets the SB, RXQ and TXQ काष्ठाures */
अटल व्योम qede_init_fp(काष्ठा qede_dev *edev)
अणु
	पूर्णांक queue_id, rxq_index = 0, txq_index = 0;
	काष्ठा qede_fastpath *fp;
	bool init_xdp = false;

	क्रम_each_queue(queue_id) अणु
		fp = &edev->fp_array[queue_id];

		fp->edev = edev;
		fp->id = queue_id;

		अगर (fp->type & QEDE_FASTPATH_XDP) अणु
			fp->xdp_tx->index = QEDE_TXQ_IDX_TO_XDP(edev,
								rxq_index);
			fp->xdp_tx->is_xdp = 1;

			spin_lock_init(&fp->xdp_tx->xdp_tx_lock);
			init_xdp = true;
		पूर्ण

		अगर (fp->type & QEDE_FASTPATH_RX) अणु
			fp->rxq->rxq_id = rxq_index++;

			/* Determine how to map buffers क्रम this queue */
			अगर (fp->type & QEDE_FASTPATH_XDP)
				fp->rxq->data_direction = DMA_BIसूचीECTIONAL;
			अन्यथा
				fp->rxq->data_direction = DMA_FROM_DEVICE;
			fp->rxq->dev = &edev->pdev->dev;

			/* Driver have no error path from here */
			WARN_ON(xdp_rxq_info_reg(&fp->rxq->xdp_rxq, edev->ndev,
						 fp->rxq->rxq_id, 0) < 0);

			अगर (xdp_rxq_info_reg_mem_model(&fp->rxq->xdp_rxq,
						       MEM_TYPE_PAGE_ORDER0,
						       शून्य)) अणु
				DP_NOTICE(edev,
					  "Failed to register XDP memory model\n");
			पूर्ण
		पूर्ण

		अगर (fp->type & QEDE_FASTPATH_TX) अणु
			पूर्णांक cos;

			क्रम_each_cos_in_txq(edev, cos) अणु
				काष्ठा qede_tx_queue *txq = &fp->txq[cos];
				u16 ndev_tx_id;

				txq->cos = cos;
				txq->index = txq_index;
				ndev_tx_id = QEDE_TXQ_TO_NDEV_TXQ_ID(edev, txq);
				txq->ndev_txq_id = ndev_tx_id;

				अगर (edev->dev_info.is_legacy)
					txq->is_legacy = true;
				txq->dev = &edev->pdev->dev;
			पूर्ण

			txq_index++;
		पूर्ण

		snम_लिखो(fp->name, माप(fp->name), "%s-fp-%d",
			 edev->ndev->name, queue_id);
	पूर्ण

	अगर (init_xdp) अणु
		edev->total_xdp_queues = QEDE_RSS_COUNT(edev);
		DP_INFO(edev, "Total XDP queues: %u\n", edev->total_xdp_queues);
	पूर्ण
पूर्ण

अटल पूर्णांक qede_set_real_num_queues(काष्ठा qede_dev *edev)
अणु
	पूर्णांक rc = 0;

	rc = netअगर_set_real_num_tx_queues(edev->ndev,
					  QEDE_TSS_COUNT(edev) *
					  edev->dev_info.num_tc);
	अगर (rc) अणु
		DP_NOTICE(edev, "Failed to set real number of Tx queues\n");
		वापस rc;
	पूर्ण

	rc = netअगर_set_real_num_rx_queues(edev->ndev, QEDE_RSS_COUNT(edev));
	अगर (rc) अणु
		DP_NOTICE(edev, "Failed to set real number of Rx queues\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qede_napi_disable_हटाओ(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i;

	क्रम_each_queue(i) अणु
		napi_disable(&edev->fp_array[i].napi);

		netअगर_napi_del(&edev->fp_array[i].napi);
	पूर्ण
पूर्ण

अटल व्योम qede_napi_add_enable(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i;

	/* Add NAPI objects */
	क्रम_each_queue(i) अणु
		netअगर_napi_add(edev->ndev, &edev->fp_array[i].napi,
			       qede_poll, NAPI_POLL_WEIGHT);
		napi_enable(&edev->fp_array[i].napi);
	पूर्ण
पूर्ण

अटल व्योम qede_sync_मुक्त_irqs(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < edev->पूर्णांक_info.used_cnt; i++) अणु
		अगर (edev->पूर्णांक_info.msix_cnt) अणु
			synchronize_irq(edev->पूर्णांक_info.msix[i].vector);
			मुक्त_irq(edev->पूर्णांक_info.msix[i].vector,
				 &edev->fp_array[i]);
		पूर्ण अन्यथा अणु
			edev->ops->common->simd_handler_clean(edev->cdev, i);
		पूर्ण
	पूर्ण

	edev->पूर्णांक_info.used_cnt = 0;
पूर्ण

अटल पूर्णांक qede_req_msix_irqs(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i, rc;

	/* Sanitize number of पूर्णांकerrupts == number of prepared RSS queues */
	अगर (QEDE_QUEUE_CNT(edev) > edev->पूर्णांक_info.msix_cnt) अणु
		DP_ERR(edev,
		       "Interrupt mismatch: %d RSS queues > %d MSI-x vectors\n",
		       QEDE_QUEUE_CNT(edev), edev->पूर्णांक_info.msix_cnt);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < QEDE_QUEUE_CNT(edev); i++) अणु
#अगर_घोषित CONFIG_RFS_ACCEL
		काष्ठा qede_fastpath *fp = &edev->fp_array[i];

		अगर (edev->ndev->rx_cpu_rmap && (fp->type & QEDE_FASTPATH_RX)) अणु
			rc = irq_cpu_rmap_add(edev->ndev->rx_cpu_rmap,
					      edev->पूर्णांक_info.msix[i].vector);
			अगर (rc) अणु
				DP_ERR(edev, "Failed to add CPU rmap\n");
				qede_मुक्त_arfs(edev);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		rc = request_irq(edev->पूर्णांक_info.msix[i].vector,
				 qede_msix_fp_पूर्णांक, 0, edev->fp_array[i].name,
				 &edev->fp_array[i]);
		अगर (rc) अणु
			DP_ERR(edev, "Request fp %d irq failed\n", i);
			qede_sync_मुक्त_irqs(edev);
			वापस rc;
		पूर्ण
		DP_VERBOSE(edev, NETIF_MSG_INTR,
			   "Requested fp irq for %s [entry %d]. Cookie is at %p\n",
			   edev->fp_array[i].name, i,
			   &edev->fp_array[i]);
		edev->पूर्णांक_info.used_cnt++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qede_simd_fp_handler(व्योम *cookie)
अणु
	काष्ठा qede_fastpath *fp = (काष्ठा qede_fastpath *)cookie;

	napi_schedule_irqoff(&fp->napi);
पूर्ण

अटल पूर्णांक qede_setup_irqs(काष्ठा qede_dev *edev)
अणु
	पूर्णांक i, rc = 0;

	/* Learn Interrupt configuration */
	rc = edev->ops->common->get_fp_पूर्णांक(edev->cdev, &edev->पूर्णांक_info);
	अगर (rc)
		वापस rc;

	अगर (edev->पूर्णांक_info.msix_cnt) अणु
		rc = qede_req_msix_irqs(edev);
		अगर (rc)
			वापस rc;
		edev->ndev->irq = edev->पूर्णांक_info.msix[0].vector;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा qed_common_ops *ops;

		/* qed should learn receive the RSS ids and callbacks */
		ops = edev->ops->common;
		क्रम (i = 0; i < QEDE_QUEUE_CNT(edev); i++)
			ops->simd_handler_config(edev->cdev,
						 &edev->fp_array[i], i,
						 qede_simd_fp_handler);
		edev->पूर्णांक_info.used_cnt = QEDE_QUEUE_CNT(edev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qede_drain_txq(काष्ठा qede_dev *edev,
			  काष्ठा qede_tx_queue *txq, bool allow_drain)
अणु
	पूर्णांक rc, cnt = 1000;

	जबतक (txq->sw_tx_cons != txq->sw_tx_prod) अणु
		अगर (!cnt) अणु
			अगर (allow_drain) अणु
				DP_NOTICE(edev,
					  "Tx queue[%d] is stuck, requesting MCP to drain\n",
					  txq->index);
				rc = edev->ops->common->drain(edev->cdev);
				अगर (rc)
					वापस rc;
				वापस qede_drain_txq(edev, txq, false);
			पूर्ण
			DP_NOTICE(edev,
				  "Timeout waiting for tx queue[%d]: PROD=%d, CONS=%d\n",
				  txq->index, txq->sw_tx_prod,
				  txq->sw_tx_cons);
			वापस -ENODEV;
		पूर्ण
		cnt--;
		usleep_range(1000, 2000);
		barrier();
	पूर्ण

	/* FW finished processing, रुको क्रम HW to transmit all tx packets */
	usleep_range(1000, 2000);

	वापस 0;
पूर्ण

अटल पूर्णांक qede_stop_txq(काष्ठा qede_dev *edev,
			 काष्ठा qede_tx_queue *txq, पूर्णांक rss_id)
अणु
	/* delete करोorbell from करोorbell recovery mechanism */
	edev->ops->common->db_recovery_del(edev->cdev, txq->करोorbell_addr,
					   &txq->tx_db);

	वापस edev->ops->q_tx_stop(edev->cdev, rss_id, txq->handle);
पूर्ण

अटल पूर्णांक qede_stop_queues(काष्ठा qede_dev *edev)
अणु
	काष्ठा qed_update_vport_params *vport_update_params;
	काष्ठा qed_dev *cdev = edev->cdev;
	काष्ठा qede_fastpath *fp;
	पूर्णांक rc, i;

	/* Disable the vport */
	vport_update_params = vzalloc(माप(*vport_update_params));
	अगर (!vport_update_params)
		वापस -ENOMEM;

	vport_update_params->vport_id = 0;
	vport_update_params->update_vport_active_flg = 1;
	vport_update_params->vport_active_flg = 0;
	vport_update_params->update_rss_flg = 0;

	rc = edev->ops->vport_update(cdev, vport_update_params);
	vमुक्त(vport_update_params);

	अगर (rc) अणु
		DP_ERR(edev, "Failed to update vport\n");
		वापस rc;
	पूर्ण

	/* Flush Tx queues. If needed, request drain from MCP */
	क्रम_each_queue(i) अणु
		fp = &edev->fp_array[i];

		अगर (fp->type & QEDE_FASTPATH_TX) अणु
			पूर्णांक cos;

			क्रम_each_cos_in_txq(edev, cos) अणु
				rc = qede_drain_txq(edev, &fp->txq[cos], true);
				अगर (rc)
					वापस rc;
			पूर्ण
		पूर्ण

		अगर (fp->type & QEDE_FASTPATH_XDP) अणु
			rc = qede_drain_txq(edev, fp->xdp_tx, true);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	/* Stop all Queues in reverse order */
	क्रम (i = QEDE_QUEUE_CNT(edev) - 1; i >= 0; i--) अणु
		fp = &edev->fp_array[i];

		/* Stop the Tx Queue(s) */
		अगर (fp->type & QEDE_FASTPATH_TX) अणु
			पूर्णांक cos;

			क्रम_each_cos_in_txq(edev, cos) अणु
				rc = qede_stop_txq(edev, &fp->txq[cos], i);
				अगर (rc)
					वापस rc;
			पूर्ण
		पूर्ण

		/* Stop the Rx Queue */
		अगर (fp->type & QEDE_FASTPATH_RX) अणु
			rc = edev->ops->q_rx_stop(cdev, i, fp->rxq->handle);
			अगर (rc) अणु
				DP_ERR(edev, "Failed to stop RXQ #%d\n", i);
				वापस rc;
			पूर्ण
		पूर्ण

		/* Stop the XDP क्रमwarding queue */
		अगर (fp->type & QEDE_FASTPATH_XDP) अणु
			rc = qede_stop_txq(edev, fp->xdp_tx, i);
			अगर (rc)
				वापस rc;

			bpf_prog_put(fp->rxq->xdp_prog);
		पूर्ण
	पूर्ण

	/* Stop the vport */
	rc = edev->ops->vport_stop(cdev, 0);
	अगर (rc)
		DP_ERR(edev, "Failed to stop VPORT\n");

	वापस rc;
पूर्ण

अटल पूर्णांक qede_start_txq(काष्ठा qede_dev *edev,
			  काष्ठा qede_fastpath *fp,
			  काष्ठा qede_tx_queue *txq, u8 rss_id, u16 sb_idx)
अणु
	dma_addr_t phys_table = qed_chain_get_pbl_phys(&txq->tx_pbl);
	u32 page_cnt = qed_chain_get_page_cnt(&txq->tx_pbl);
	काष्ठा qed_queue_start_common_params params;
	काष्ठा qed_txq_start_ret_params ret_params;
	पूर्णांक rc;

	स_रखो(&params, 0, माप(params));
	स_रखो(&ret_params, 0, माप(ret_params));

	/* Let the XDP queue share the queue-zone with one of the regular txq.
	 * We करोn't really care about its coalescing.
	 */
	अगर (txq->is_xdp)
		params.queue_id = QEDE_TXQ_XDP_TO_IDX(edev, txq);
	अन्यथा
		params.queue_id = txq->index;

	params.p_sb = fp->sb_info;
	params.sb_idx = sb_idx;
	params.tc = txq->cos;

	rc = edev->ops->q_tx_start(edev->cdev, rss_id, &params, phys_table,
				   page_cnt, &ret_params);
	अगर (rc) अणु
		DP_ERR(edev, "Start TXQ #%d failed %d\n", txq->index, rc);
		वापस rc;
	पूर्ण

	txq->करोorbell_addr = ret_params.p_करोorbell;
	txq->handle = ret_params.p_handle;

	/* Determine the FW consumer address associated */
	txq->hw_cons_ptr = &fp->sb_info->sb_virt->pi_array[sb_idx];

	/* Prepare the करोorbell parameters */
	SET_FIELD(txq->tx_db.data.params, ETH_DB_DATA_DEST, DB_DEST_XCM);
	SET_FIELD(txq->tx_db.data.params, ETH_DB_DATA_AGG_CMD, DB_AGG_CMD_SET);
	SET_FIELD(txq->tx_db.data.params, ETH_DB_DATA_AGG_VAL_SEL,
		  DQ_XCM_ETH_TX_BD_PROD_CMD);
	txq->tx_db.data.agg_flags = DQ_XCM_ETH_DQ_CF_CMD;

	/* रेजिस्टर करोorbell with करोorbell recovery mechanism */
	rc = edev->ops->common->db_recovery_add(edev->cdev, txq->करोorbell_addr,
						&txq->tx_db, DB_REC_WIDTH_32B,
						DB_REC_KERNEL);

	वापस rc;
पूर्ण

अटल पूर्णांक qede_start_queues(काष्ठा qede_dev *edev, bool clear_stats)
अणु
	पूर्णांक vlan_removal_en = 1;
	काष्ठा qed_dev *cdev = edev->cdev;
	काष्ठा qed_dev_info *qed_info = &edev->dev_info.common;
	काष्ठा qed_update_vport_params *vport_update_params;
	काष्ठा qed_queue_start_common_params q_params;
	काष्ठा qed_start_vport_params start = अणु0पूर्ण;
	पूर्णांक rc, i;

	अगर (!edev->num_queues) अणु
		DP_ERR(edev,
		       "Cannot update V-VPORT as active as there are no Rx queues\n");
		वापस -EINVAL;
	पूर्ण

	vport_update_params = vzalloc(माप(*vport_update_params));
	अगर (!vport_update_params)
		वापस -ENOMEM;

	start.handle_ptp_pkts = !!(edev->ptp);
	start.gro_enable = !edev->gro_disable;
	start.mtu = edev->ndev->mtu;
	start.vport_id = 0;
	start.drop_ttl0 = true;
	start.हटाओ_inner_vlan = vlan_removal_en;
	start.clear_stats = clear_stats;

	rc = edev->ops->vport_start(cdev, &start);

	अगर (rc) अणु
		DP_ERR(edev, "Start V-PORT failed %d\n", rc);
		जाओ out;
	पूर्ण

	DP_VERBOSE(edev, NETIF_MSG_IFUP,
		   "Start vport ramrod passed, vport_id = %d, MTU = %d, vlan_removal_en = %d\n",
		   start.vport_id, edev->ndev->mtu + 0xe, vlan_removal_en);

	क्रम_each_queue(i) अणु
		काष्ठा qede_fastpath *fp = &edev->fp_array[i];
		dma_addr_t p_phys_table;
		u32 page_cnt;

		अगर (fp->type & QEDE_FASTPATH_RX) अणु
			काष्ठा qed_rxq_start_ret_params ret_params;
			काष्ठा qede_rx_queue *rxq = fp->rxq;
			__le16 *val;

			स_रखो(&ret_params, 0, माप(ret_params));
			स_रखो(&q_params, 0, माप(q_params));
			q_params.queue_id = rxq->rxq_id;
			q_params.vport_id = 0;
			q_params.p_sb = fp->sb_info;
			q_params.sb_idx = RX_PI;

			p_phys_table =
			    qed_chain_get_pbl_phys(&rxq->rx_comp_ring);
			page_cnt = qed_chain_get_page_cnt(&rxq->rx_comp_ring);

			rc = edev->ops->q_rx_start(cdev, i, &q_params,
						   rxq->rx_buf_size,
						   rxq->rx_bd_ring.p_phys_addr,
						   p_phys_table,
						   page_cnt, &ret_params);
			अगर (rc) अणु
				DP_ERR(edev, "Start RXQ #%d failed %d\n", i,
				       rc);
				जाओ out;
			पूर्ण

			/* Use the वापस parameters */
			rxq->hw_rxq_prod_addr = ret_params.p_prod;
			rxq->handle = ret_params.p_handle;

			val = &fp->sb_info->sb_virt->pi_array[RX_PI];
			rxq->hw_cons_ptr = val;

			qede_update_rx_prod(edev, rxq);
		पूर्ण

		अगर (fp->type & QEDE_FASTPATH_XDP) अणु
			rc = qede_start_txq(edev, fp, fp->xdp_tx, i, XDP_PI);
			अगर (rc)
				जाओ out;

			bpf_prog_add(edev->xdp_prog, 1);
			fp->rxq->xdp_prog = edev->xdp_prog;
		पूर्ण

		अगर (fp->type & QEDE_FASTPATH_TX) अणु
			पूर्णांक cos;

			क्रम_each_cos_in_txq(edev, cos) अणु
				rc = qede_start_txq(edev, fp, &fp->txq[cos], i,
						    TX_PI(cos));
				अगर (rc)
					जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Prepare and send the vport enable */
	vport_update_params->vport_id = start.vport_id;
	vport_update_params->update_vport_active_flg = 1;
	vport_update_params->vport_active_flg = 1;

	अगर ((qed_info->b_पूर्णांकer_pf_चयन || pci_num_vf(edev->pdev)) &&
	    qed_info->tx_चयनing) अणु
		vport_update_params->update_tx_चयनing_flg = 1;
		vport_update_params->tx_चयनing_flg = 1;
	पूर्ण

	qede_fill_rss_params(edev, &vport_update_params->rss_params,
			     &vport_update_params->update_rss_flg);

	rc = edev->ops->vport_update(cdev, vport_update_params);
	अगर (rc)
		DP_ERR(edev, "Update V-PORT failed %d\n", rc);

out:
	vमुक्त(vport_update_params);
	वापस rc;
पूर्ण

क्रमागत qede_unload_mode अणु
	QEDE_UNLOAD_NORMAL,
	QEDE_UNLOAD_RECOVERY,
पूर्ण;

अटल व्योम qede_unload(काष्ठा qede_dev *edev, क्रमागत qede_unload_mode mode,
			bool is_locked)
अणु
	काष्ठा qed_link_params link_params;
	पूर्णांक rc;

	DP_INFO(edev, "Starting qede unload\n");

	अगर (!is_locked)
		__qede_lock(edev);

	clear_bit(QEDE_FLAGS_LINK_REQUESTED, &edev->flags);

	अगर (mode != QEDE_UNLOAD_RECOVERY)
		edev->state = QEDE_STATE_CLOSED;

	qede_rdma_dev_event_बंद(edev);

	/* Close OS Tx */
	netअगर_tx_disable(edev->ndev);
	netअगर_carrier_off(edev->ndev);

	अगर (mode != QEDE_UNLOAD_RECOVERY) अणु
		/* Reset the link */
		स_रखो(&link_params, 0, माप(link_params));
		link_params.link_up = false;
		edev->ops->common->set_link(edev->cdev, &link_params);

		rc = qede_stop_queues(edev);
		अगर (rc) अणु
			qede_sync_मुक्त_irqs(edev);
			जाओ out;
		पूर्ण

		DP_INFO(edev, "Stopped Queues\n");
	पूर्ण

	qede_vlan_mark_nonconfigured(edev);
	edev->ops->fastpath_stop(edev->cdev);

	अगर (edev->dev_info.common.b_arfs_capable) अणु
		qede_poll_क्रम_मुक्तing_arfs_filters(edev);
		qede_मुक्त_arfs(edev);
	पूर्ण

	/* Release the पूर्णांकerrupts */
	qede_sync_मुक्त_irqs(edev);
	edev->ops->common->set_fp_पूर्णांक(edev->cdev, 0);

	qede_napi_disable_हटाओ(edev);

	अगर (mode == QEDE_UNLOAD_RECOVERY)
		qede_empty_tx_queues(edev);

	qede_मुक्त_mem_load(edev);
	qede_मुक्त_fp_array(edev);

out:
	अगर (!is_locked)
		__qede_unlock(edev);

	अगर (mode != QEDE_UNLOAD_RECOVERY)
		DP_NOTICE(edev, "Link is down\n");

	edev->ptp_skip_txts = 0;

	DP_INFO(edev, "Ending qede unload\n");
पूर्ण

क्रमागत qede_load_mode अणु
	QEDE_LOAD_NORMAL,
	QEDE_LOAD_RELOAD,
	QEDE_LOAD_RECOVERY,
पूर्ण;

अटल पूर्णांक qede_load(काष्ठा qede_dev *edev, क्रमागत qede_load_mode mode,
		     bool is_locked)
अणु
	काष्ठा qed_link_params link_params;
	काष्ठा ethtool_coalesce coal = अणुपूर्ण;
	u8 num_tc;
	पूर्णांक rc, i;

	DP_INFO(edev, "Starting qede load\n");

	अगर (!is_locked)
		__qede_lock(edev);

	rc = qede_set_num_queues(edev);
	अगर (rc)
		जाओ out;

	rc = qede_alloc_fp_array(edev);
	अगर (rc)
		जाओ out;

	qede_init_fp(edev);

	rc = qede_alloc_mem_load(edev);
	अगर (rc)
		जाओ err1;
	DP_INFO(edev, "Allocated %d Rx, %d Tx queues\n",
		QEDE_RSS_COUNT(edev), QEDE_TSS_COUNT(edev));

	rc = qede_set_real_num_queues(edev);
	अगर (rc)
		जाओ err2;

	अगर (qede_alloc_arfs(edev)) अणु
		edev->ndev->features &= ~NETIF_F_NTUPLE;
		edev->dev_info.common.b_arfs_capable = false;
	पूर्ण

	qede_napi_add_enable(edev);
	DP_INFO(edev, "Napi added and enabled\n");

	rc = qede_setup_irqs(edev);
	अगर (rc)
		जाओ err3;
	DP_INFO(edev, "Setup IRQs succeeded\n");

	rc = qede_start_queues(edev, mode != QEDE_LOAD_RELOAD);
	अगर (rc)
		जाओ err4;
	DP_INFO(edev, "Start VPORT, RXQ and TXQ succeeded\n");

	num_tc = netdev_get_num_tc(edev->ndev);
	num_tc = num_tc ? num_tc : edev->dev_info.num_tc;
	qede_setup_tc(edev->ndev, num_tc);

	/* Program un-configured VLANs */
	qede_configure_vlan_filters(edev);

	set_bit(QEDE_FLAGS_LINK_REQUESTED, &edev->flags);

	/* Ask क्रम link-up using current configuration */
	स_रखो(&link_params, 0, माप(link_params));
	link_params.link_up = true;
	edev->ops->common->set_link(edev->cdev, &link_params);

	edev->state = QEDE_STATE_OPEN;

	coal.rx_coalesce_usecs = QED_DEFAULT_RX_USECS;
	coal.tx_coalesce_usecs = QED_DEFAULT_TX_USECS;

	क्रम_each_queue(i) अणु
		अगर (edev->coal_entry[i].isvalid) अणु
			coal.rx_coalesce_usecs = edev->coal_entry[i].rxc;
			coal.tx_coalesce_usecs = edev->coal_entry[i].txc;
		पूर्ण
		__qede_unlock(edev);
		qede_set_per_coalesce(edev->ndev, i, &coal);
		__qede_lock(edev);
	पूर्ण
	DP_INFO(edev, "Ending successfully qede load\n");

	जाओ out;
err4:
	qede_sync_मुक्त_irqs(edev);
	स_रखो(&edev->पूर्णांक_info.msix_cnt, 0, माप(काष्ठा qed_पूर्णांक_info));
err3:
	qede_napi_disable_हटाओ(edev);
err2:
	qede_मुक्त_mem_load(edev);
err1:
	edev->ops->common->set_fp_पूर्णांक(edev->cdev, 0);
	qede_मुक्त_fp_array(edev);
	edev->num_queues = 0;
	edev->fp_num_tx = 0;
	edev->fp_num_rx = 0;
out:
	अगर (!is_locked)
		__qede_unlock(edev);

	वापस rc;
पूर्ण

/* 'func' should be able to run between unload and reload assuming पूर्णांकerface
 * is actually running, or afterwards in हाल it's currently DOWN.
 */
व्योम qede_reload(काष्ठा qede_dev *edev,
		 काष्ठा qede_reload_args *args, bool is_locked)
अणु
	अगर (!is_locked)
		__qede_lock(edev);

	/* Since qede_lock is held, पूर्णांकernal state wouldn't change even
	 * अगर netdev state would start transitioning. Check whether current
	 * पूर्णांकernal configuration indicates device is up, then reload.
	 */
	अगर (edev->state == QEDE_STATE_OPEN) अणु
		qede_unload(edev, QEDE_UNLOAD_NORMAL, true);
		अगर (args)
			args->func(edev, args);
		qede_load(edev, QEDE_LOAD_RELOAD, true);

		/* Since no one is going to करो it क्रम us, re-configure */
		qede_config_rx_mode(edev->ndev);
	पूर्ण अन्यथा अगर (args) अणु
		args->func(edev, args);
	पूर्ण

	अगर (!is_locked)
		__qede_unlock(edev);
पूर्ण

/* called with rtnl_lock */
अटल पूर्णांक qede_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	पूर्णांक rc;

	netअगर_carrier_off(ndev);

	edev->ops->common->set_घातer_state(edev->cdev, PCI_D0);

	rc = qede_load(edev, QEDE_LOAD_NORMAL, false);
	अगर (rc)
		वापस rc;

	udp_tunnel_nic_reset_ntf(ndev);

	edev->ops->common->update_drv_state(edev->cdev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक qede_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);

	qede_unload(edev, QEDE_UNLOAD_NORMAL, false);

	अगर (edev->cdev)
		edev->ops->common->update_drv_state(edev->cdev, false);

	वापस 0;
पूर्ण

अटल व्योम qede_link_update(व्योम *dev, काष्ठा qed_link_output *link)
अणु
	काष्ठा qede_dev *edev = dev;

	अगर (!test_bit(QEDE_FLAGS_LINK_REQUESTED, &edev->flags)) अणु
		DP_VERBOSE(edev, NETIF_MSG_LINK, "Interface is not ready\n");
		वापस;
	पूर्ण

	अगर (link->link_up) अणु
		अगर (!netअगर_carrier_ok(edev->ndev)) अणु
			DP_NOTICE(edev, "Link is up\n");
			netअगर_tx_start_all_queues(edev->ndev);
			netअगर_carrier_on(edev->ndev);
			qede_rdma_dev_event_खोलो(edev);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(edev->ndev)) अणु
			DP_NOTICE(edev, "Link is down\n");
			netअगर_tx_disable(edev->ndev);
			netअगर_carrier_off(edev->ndev);
			qede_rdma_dev_event_बंद(edev);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qede_schedule_recovery_handler(व्योम *dev)
अणु
	काष्ठा qede_dev *edev = dev;

	अगर (edev->state == QEDE_STATE_RECOVERY) अणु
		DP_NOTICE(edev,
			  "Avoid scheduling a recovery handling since already in recovery state\n");
		वापस;
	पूर्ण

	set_bit(QEDE_SP_RECOVERY, &edev->sp_flags);
	schedule_delayed_work(&edev->sp_task, 0);

	DP_INFO(edev, "Scheduled a recovery handler\n");
पूर्ण

अटल व्योम qede_recovery_failed(काष्ठा qede_dev *edev)
अणु
	netdev_err(edev->ndev, "Recovery handling has failed. Power cycle is needed.\n");

	netअगर_device_detach(edev->ndev);

	अगर (edev->cdev)
		edev->ops->common->set_घातer_state(edev->cdev, PCI_D3hot);
पूर्ण

अटल व्योम qede_recovery_handler(काष्ठा qede_dev *edev)
अणु
	u32 curr_state = edev->state;
	पूर्णांक rc;

	DP_NOTICE(edev, "Starting a recovery process\n");

	/* No need to acquire first the qede_lock since is करोne by qede_sp_task
	 * beक्रमe calling this function.
	 */
	edev->state = QEDE_STATE_RECOVERY;

	edev->ops->common->recovery_prolog(edev->cdev);

	अगर (curr_state == QEDE_STATE_OPEN)
		qede_unload(edev, QEDE_UNLOAD_RECOVERY, true);

	__qede_हटाओ(edev->pdev, QEDE_REMOVE_RECOVERY);

	rc = __qede_probe(edev->pdev, edev->dp_module, edev->dp_level,
			  IS_VF(edev), QEDE_PROBE_RECOVERY);
	अगर (rc) अणु
		edev->cdev = शून्य;
		जाओ err;
	पूर्ण

	अगर (curr_state == QEDE_STATE_OPEN) अणु
		rc = qede_load(edev, QEDE_LOAD_RECOVERY, true);
		अगर (rc)
			जाओ err;

		qede_config_rx_mode(edev->ndev);
		udp_tunnel_nic_reset_ntf(edev->ndev);
	पूर्ण

	edev->state = curr_state;

	DP_NOTICE(edev, "Recovery handling is done\n");

	वापस;

err:
	qede_recovery_failed(edev);
पूर्ण

अटल व्योम qede_atomic_hw_err_handler(काष्ठा qede_dev *edev)
अणु
	काष्ठा qed_dev *cdev = edev->cdev;

	DP_NOTICE(edev,
		  "Generic non-sleepable HW error handling started - err_flags 0x%lx\n",
		  edev->err_flags);

	/* Get a call trace of the flow that led to the error */
	WARN_ON(test_bit(QEDE_ERR_WARN, &edev->err_flags));

	/* Prevent HW attentions from being reनिश्चितed */
	अगर (test_bit(QEDE_ERR_ATTN_CLR_EN, &edev->err_flags))
		edev->ops->common->attn_clr_enable(cdev, true);

	DP_NOTICE(edev, "Generic non-sleepable HW error handling is done\n");
पूर्ण

अटल व्योम qede_generic_hw_err_handler(काष्ठा qede_dev *edev)
अणु
	DP_NOTICE(edev,
		  "Generic sleepable HW error handling started - err_flags 0x%lx\n",
		  edev->err_flags);

	अगर (edev->devlink)
		edev->ops->common->report_fatal_error(edev->devlink, edev->last_err_type);

	clear_bit(QEDE_ERR_IS_HANDLED, &edev->err_flags);

	DP_NOTICE(edev, "Generic sleepable HW error handling is done\n");
पूर्ण

अटल व्योम qede_set_hw_err_flags(काष्ठा qede_dev *edev,
				  क्रमागत qed_hw_err_type err_type)
अणु
	अचिन्हित दीर्घ err_flags = 0;

	चयन (err_type) अणु
	हाल QED_HW_ERR_DMAE_FAIL:
		set_bit(QEDE_ERR_WARN, &err_flags);
		fallthrough;
	हाल QED_HW_ERR_MFW_RESP_FAIL:
	हाल QED_HW_ERR_HW_ATTN:
	हाल QED_HW_ERR_RAMROD_FAIL:
	हाल QED_HW_ERR_FW_ASSERT:
		set_bit(QEDE_ERR_ATTN_CLR_EN, &err_flags);
		set_bit(QEDE_ERR_GET_DBG_INFO, &err_flags);
		अवरोध;

	शेष:
		DP_NOTICE(edev, "Unexpected HW error [%d]\n", err_type);
		अवरोध;
	पूर्ण

	edev->err_flags |= err_flags;
पूर्ण

अटल व्योम qede_schedule_hw_err_handler(व्योम *dev,
					 क्रमागत qed_hw_err_type err_type)
अणु
	काष्ठा qede_dev *edev = dev;

	/* Fan failure cannot be masked by handling of another HW error or by a
	 * concurrent recovery process.
	 */
	अगर ((test_and_set_bit(QEDE_ERR_IS_HANDLED, &edev->err_flags) ||
	     edev->state == QEDE_STATE_RECOVERY) &&
	     err_type != QED_HW_ERR_FAN_FAIL) अणु
		DP_INFO(edev,
			"Avoid scheduling an error handling while another HW error is being handled\n");
		वापस;
	पूर्ण

	अगर (err_type >= QED_HW_ERR_LAST) अणु
		DP_NOTICE(edev, "Unknown HW error [%d]\n", err_type);
		clear_bit(QEDE_ERR_IS_HANDLED, &edev->err_flags);
		वापस;
	पूर्ण

	edev->last_err_type = err_type;
	qede_set_hw_err_flags(edev, err_type);
	qede_atomic_hw_err_handler(edev);
	set_bit(QEDE_SP_HW_ERR, &edev->sp_flags);
	schedule_delayed_work(&edev->sp_task, 0);

	DP_INFO(edev, "Scheduled a error handler [err_type %d]\n", err_type);
पूर्ण

अटल bool qede_is_txq_full(काष्ठा qede_dev *edev, काष्ठा qede_tx_queue *txq)
अणु
	काष्ठा netdev_queue *netdev_txq;

	netdev_txq = netdev_get_tx_queue(edev->ndev, txq->ndev_txq_id);
	अगर (netअगर_xmit_stopped(netdev_txq))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम qede_get_generic_tlv_data(व्योम *dev, काष्ठा qed_generic_tlvs *data)
अणु
	काष्ठा qede_dev *edev = dev;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;

	अगर (edev->ndev->features & NETIF_F_IP_CSUM)
		data->feat_flags |= QED_TLV_IP_CSUM;
	अगर (edev->ndev->features & NETIF_F_TSO)
		data->feat_flags |= QED_TLV_LSO;

	ether_addr_copy(data->mac[0], edev->ndev->dev_addr);
	eth_zero_addr(data->mac[1]);
	eth_zero_addr(data->mac[2]);
	/* Copy the first two UC macs */
	netअगर_addr_lock_bh(edev->ndev);
	i = 1;
	netdev_क्रम_each_uc_addr(ha, edev->ndev) अणु
		ether_addr_copy(data->mac[i++], ha->addr);
		अगर (i == QED_TLV_MAC_COUNT)
			अवरोध;
	पूर्ण

	netअगर_addr_unlock_bh(edev->ndev);
पूर्ण

अटल व्योम qede_get_eth_tlv_data(व्योम *dev, व्योम *data)
अणु
	काष्ठा qed_mfw_tlv_eth *etlv = data;
	काष्ठा qede_dev *edev = dev;
	काष्ठा qede_fastpath *fp;
	पूर्णांक i;

	etlv->lso_maxoff_size = 0XFFFF;
	etlv->lso_maxoff_size_set = true;
	etlv->lso_minseg_size = (u16)ETH_TX_LSO_WINDOW_MIN_LEN;
	etlv->lso_minseg_size_set = true;
	etlv->prom_mode = !!(edev->ndev->flags & IFF_PROMISC);
	etlv->prom_mode_set = true;
	etlv->tx_descr_size = QEDE_TSS_COUNT(edev);
	etlv->tx_descr_size_set = true;
	etlv->rx_descr_size = QEDE_RSS_COUNT(edev);
	etlv->rx_descr_size_set = true;
	etlv->iov_offload = QED_MFW_TLV_IOV_OFFLOAD_VEB;
	etlv->iov_offload_set = true;

	/* Fill inक्रमmation regarding queues; Should be करोne under the qede
	 * lock to guarantee those करोn't change beneath our feet.
	 */
	etlv->txqs_empty = true;
	etlv->rxqs_empty = true;
	etlv->num_txqs_full = 0;
	etlv->num_rxqs_full = 0;

	__qede_lock(edev);
	क्रम_each_queue(i) अणु
		fp = &edev->fp_array[i];
		अगर (fp->type & QEDE_FASTPATH_TX) अणु
			काष्ठा qede_tx_queue *txq = QEDE_FP_TC0_TXQ(fp);

			अगर (txq->sw_tx_cons != txq->sw_tx_prod)
				etlv->txqs_empty = false;
			अगर (qede_is_txq_full(edev, txq))
				etlv->num_txqs_full++;
		पूर्ण
		अगर (fp->type & QEDE_FASTPATH_RX) अणु
			अगर (qede_has_rx_work(fp->rxq))
				etlv->rxqs_empty = false;

			/* This one is a bit tricky; Firmware might stop
			 * placing packets अगर ring is not yet full.
			 * Give an approximation.
			 */
			अगर (le16_to_cpu(*fp->rxq->hw_cons_ptr) -
			    qed_chain_get_cons_idx(&fp->rxq->rx_comp_ring) >
			    RX_RING_SIZE - 100)
				etlv->num_rxqs_full++;
		पूर्ण
	पूर्ण
	__qede_unlock(edev);

	etlv->txqs_empty_set = true;
	etlv->rxqs_empty_set = true;
	etlv->num_txqs_full_set = true;
	etlv->num_rxqs_full_set = true;
पूर्ण

/**
 * qede_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t
qede_io_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा qede_dev *edev = netdev_priv(dev);

	अगर (!edev)
		वापस PCI_ERS_RESULT_NONE;

	DP_NOTICE(edev, "IO error detected [%d]\n", state);

	__qede_lock(edev);
	अगर (edev->state == QEDE_STATE_RECOVERY) अणु
		DP_NOTICE(edev, "Device already in the recovery state\n");
		__qede_unlock(edev);
		वापस PCI_ERS_RESULT_NONE;
	पूर्ण

	/* PF handles the recovery of its VFs */
	अगर (IS_VF(edev)) अणु
		DP_VERBOSE(edev, QED_MSG_IOV,
			   "VF recovery is handled by its PF\n");
		__qede_unlock(edev);
		वापस PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	/* Close OS Tx */
	netअगर_tx_disable(edev->ndev);
	netअगर_carrier_off(edev->ndev);

	set_bit(QEDE_SP_AER, &edev->sp_flags);
	schedule_delayed_work(&edev->sp_task, 0);

	__qede_unlock(edev);

	वापस PCI_ERS_RESULT_CAN_RECOVER;
पूर्ण
