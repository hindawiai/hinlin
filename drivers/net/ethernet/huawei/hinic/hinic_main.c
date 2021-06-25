<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/workqueue.h>
#समावेश <net/ip.h>
#समावेश <net/devlink.h>
#समावेश <linux/bitops.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>

#समावेश "hinic_debugfs.h"
#समावेश "hinic_hw_qp.h"
#समावेश "hinic_hw_dev.h"
#समावेश "hinic_devlink.h"
#समावेश "hinic_port.h"
#समावेश "hinic_tx.h"
#समावेश "hinic_rx.h"
#समावेश "hinic_dev.h"
#समावेश "hinic_sriov.h"

MODULE_AUTHOR("Huawei Technologies CO., Ltd");
MODULE_DESCRIPTION("Huawei Intelligent NIC driver");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक tx_weight = 64;
module_param(tx_weight, uपूर्णांक, 0644);
MODULE_PARM_DESC(tx_weight, "Number Tx packets for NAPI budget (default=64)");

अटल अचिन्हित पूर्णांक rx_weight = 64;
module_param(rx_weight, uपूर्णांक, 0644);
MODULE_PARM_DESC(rx_weight, "Number Rx packets for NAPI budget (default=64)");

#घोषणा HINIC_DEV_ID_QUAD_PORT_25GE         0x1822
#घोषणा HINIC_DEV_ID_DUAL_PORT_100GE        0x0200
#घोषणा HINIC_DEV_ID_DUAL_PORT_100GE_MEZZ   0x0205
#घोषणा HINIC_DEV_ID_QUAD_PORT_25GE_MEZZ    0x0210
#घोषणा HINIC_DEV_ID_VF    0x375e

#घोषणा HINIC_WQ_NAME                   "hinic_dev"

#घोषणा MSG_ENABLE_DEFAULT              (NETIF_MSG_DRV | NETIF_MSG_PROBE | \
					 NETIF_MSG_IFUP |                  \
					 NETIF_MSG_TX_ERR | NETIF_MSG_RX_ERR)

#घोषणा HINIC_LRO_MAX_WQE_NUM_DEFAULT	8

#घोषणा HINIC_LRO_RX_TIMER_DEFAULT	16

#घोषणा VLAN_BITMAP_SIZE(nic_dev)       (ALIGN(VLAN_N_VID, 8) / 8)

#घोषणा work_to_rx_mode_work(work)      \
		container_of(work, काष्ठा hinic_rx_mode_work, work)

#घोषणा rx_mode_work_to_nic_dev(rx_mode_work) \
		container_of(rx_mode_work, काष्ठा hinic_dev, rx_mode_work)

#घोषणा HINIC_WAIT_SRIOV_CFG_TIMEOUT	15000

#घोषणा HINIC_DEAULT_TXRX_MSIX_PENDING_LIMIT		2
#घोषणा HINIC_DEAULT_TXRX_MSIX_COALESC_TIMER_CFG	32
#घोषणा HINIC_DEAULT_TXRX_MSIX_RESEND_TIMER_CFG		7

अटल पूर्णांक change_mac_addr(काष्ठा net_device *netdev, स्थिर u8 *addr);

अटल पूर्णांक set_features(काष्ठा hinic_dev *nic_dev,
			netdev_features_t pre_features,
			netdev_features_t features, bool क्रमce_change);

अटल व्योम update_rx_stats(काष्ठा hinic_dev *nic_dev, काष्ठा hinic_rxq *rxq)
अणु
	काष्ठा hinic_rxq_stats *nic_rx_stats = &nic_dev->rx_stats;
	काष्ठा hinic_rxq_stats rx_stats;

	u64_stats_init(&rx_stats.syncp);

	hinic_rxq_get_stats(rxq, &rx_stats);

	u64_stats_update_begin(&nic_rx_stats->syncp);
	nic_rx_stats->bytes += rx_stats.bytes;
	nic_rx_stats->pkts  += rx_stats.pkts;
	nic_rx_stats->errors += rx_stats.errors;
	nic_rx_stats->csum_errors += rx_stats.csum_errors;
	nic_rx_stats->other_errors += rx_stats.other_errors;
	u64_stats_update_end(&nic_rx_stats->syncp);

	hinic_rxq_clean_stats(rxq);
पूर्ण

अटल व्योम update_tx_stats(काष्ठा hinic_dev *nic_dev, काष्ठा hinic_txq *txq)
अणु
	काष्ठा hinic_txq_stats *nic_tx_stats = &nic_dev->tx_stats;
	काष्ठा hinic_txq_stats tx_stats;

	u64_stats_init(&tx_stats.syncp);

	hinic_txq_get_stats(txq, &tx_stats);

	u64_stats_update_begin(&nic_tx_stats->syncp);
	nic_tx_stats->bytes += tx_stats.bytes;
	nic_tx_stats->pkts += tx_stats.pkts;
	nic_tx_stats->tx_busy += tx_stats.tx_busy;
	nic_tx_stats->tx_wake += tx_stats.tx_wake;
	nic_tx_stats->tx_dropped += tx_stats.tx_dropped;
	nic_tx_stats->big_frags_pkts += tx_stats.big_frags_pkts;
	u64_stats_update_end(&nic_tx_stats->syncp);

	hinic_txq_clean_stats(txq);
पूर्ण

अटल व्योम update_nic_stats(काष्ठा hinic_dev *nic_dev)
अणु
	पूर्णांक i, num_qps = hinic_hwdev_num_qps(nic_dev->hwdev);

	क्रम (i = 0; i < num_qps; i++)
		update_rx_stats(nic_dev, &nic_dev->rxqs[i]);

	क्रम (i = 0; i < num_qps; i++)
		update_tx_stats(nic_dev, &nic_dev->txqs[i]);
पूर्ण

/**
 * create_txqs - Create the Logical Tx Queues of specअगरic NIC device
 * @nic_dev: the specअगरic NIC device
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक create_txqs(काष्ठा hinic_dev *nic_dev)
अणु
	पूर्णांक err, i, j, num_txqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	काष्ठा net_device *netdev = nic_dev->netdev;
	माप_प्रकार txq_size;

	अगर (nic_dev->txqs)
		वापस -EINVAL;

	txq_size = num_txqs * माप(*nic_dev->txqs);
	nic_dev->txqs = devm_kzalloc(&netdev->dev, txq_size, GFP_KERNEL);
	अगर (!nic_dev->txqs)
		वापस -ENOMEM;

	hinic_sq_dbgfs_init(nic_dev);

	क्रम (i = 0; i < num_txqs; i++) अणु
		काष्ठा hinic_sq *sq = hinic_hwdev_get_sq(nic_dev->hwdev, i);

		err = hinic_init_txq(&nic_dev->txqs[i], sq, netdev);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to init Txq\n");
			जाओ err_init_txq;
		पूर्ण

		err = hinic_sq_debug_add(nic_dev, i);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to add SQ%d debug\n", i);
			जाओ err_add_sq_dbg;
		पूर्ण

	पूर्ण

	वापस 0;

err_add_sq_dbg:
	hinic_clean_txq(&nic_dev->txqs[i]);
err_init_txq:
	क्रम (j = 0; j < i; j++) अणु
		hinic_sq_debug_rem(nic_dev->txqs[j].sq);
		hinic_clean_txq(&nic_dev->txqs[j]);
	पूर्ण

	hinic_sq_dbgfs_uninit(nic_dev);

	devm_kमुक्त(&netdev->dev, nic_dev->txqs);
	वापस err;
पूर्ण

अटल व्योम enable_txqs_napi(काष्ठा hinic_dev *nic_dev)
अणु
	पूर्णांक num_txqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	पूर्णांक i;

	क्रम (i = 0; i < num_txqs; i++)
		napi_enable(&nic_dev->txqs[i].napi);
पूर्ण

अटल व्योम disable_txqs_napi(काष्ठा hinic_dev *nic_dev)
अणु
	पूर्णांक num_txqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	पूर्णांक i;

	क्रम (i = 0; i < num_txqs; i++)
		napi_disable(&nic_dev->txqs[i].napi);
पूर्ण

/**
 * मुक्त_txqs - Free the Logical Tx Queues of specअगरic NIC device
 * @nic_dev: the specअगरic NIC device
 **/
अटल व्योम मुक्त_txqs(काष्ठा hinic_dev *nic_dev)
अणु
	पूर्णांक i, num_txqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	काष्ठा net_device *netdev = nic_dev->netdev;

	अगर (!nic_dev->txqs)
		वापस;

	क्रम (i = 0; i < num_txqs; i++) अणु
		hinic_sq_debug_rem(nic_dev->txqs[i].sq);
		hinic_clean_txq(&nic_dev->txqs[i]);
	पूर्ण

	hinic_sq_dbgfs_uninit(nic_dev);

	devm_kमुक्त(&netdev->dev, nic_dev->txqs);
	nic_dev->txqs = शून्य;
पूर्ण

/**
 * create_txqs - Create the Logical Rx Queues of specअगरic NIC device
 * @nic_dev: the specअगरic NIC device
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक create_rxqs(काष्ठा hinic_dev *nic_dev)
अणु
	पूर्णांक err, i, j, num_rxqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	काष्ठा net_device *netdev = nic_dev->netdev;
	माप_प्रकार rxq_size;

	अगर (nic_dev->rxqs)
		वापस -EINVAL;

	rxq_size = num_rxqs * माप(*nic_dev->rxqs);
	nic_dev->rxqs = devm_kzalloc(&netdev->dev, rxq_size, GFP_KERNEL);
	अगर (!nic_dev->rxqs)
		वापस -ENOMEM;

	hinic_rq_dbgfs_init(nic_dev);

	क्रम (i = 0; i < num_rxqs; i++) अणु
		काष्ठा hinic_rq *rq = hinic_hwdev_get_rq(nic_dev->hwdev, i);

		err = hinic_init_rxq(&nic_dev->rxqs[i], rq, netdev);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to init rxq\n");
			जाओ err_init_rxq;
		पूर्ण

		err = hinic_rq_debug_add(nic_dev, i);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to add RQ%d debug\n", i);
			जाओ err_add_rq_dbg;
		पूर्ण
	पूर्ण

	वापस 0;

err_add_rq_dbg:
	hinic_clean_rxq(&nic_dev->rxqs[i]);
err_init_rxq:
	क्रम (j = 0; j < i; j++) अणु
		hinic_rq_debug_rem(nic_dev->rxqs[j].rq);
		hinic_clean_rxq(&nic_dev->rxqs[j]);
	पूर्ण

	hinic_rq_dbgfs_uninit(nic_dev);

	devm_kमुक्त(&netdev->dev, nic_dev->rxqs);
	वापस err;
पूर्ण

/**
 * मुक्त_txqs - Free the Logical Rx Queues of specअगरic NIC device
 * @nic_dev: the specअगरic NIC device
 **/
अटल व्योम मुक्त_rxqs(काष्ठा hinic_dev *nic_dev)
अणु
	पूर्णांक i, num_rxqs = hinic_hwdev_num_qps(nic_dev->hwdev);
	काष्ठा net_device *netdev = nic_dev->netdev;

	अगर (!nic_dev->rxqs)
		वापस;

	क्रम (i = 0; i < num_rxqs; i++) अणु
		hinic_rq_debug_rem(nic_dev->rxqs[i].rq);
		hinic_clean_rxq(&nic_dev->rxqs[i]);
	पूर्ण

	hinic_rq_dbgfs_uninit(nic_dev);

	devm_kमुक्त(&netdev->dev, nic_dev->rxqs);
	nic_dev->rxqs = शून्य;
पूर्ण

अटल पूर्णांक hinic_configure_max_qnum(काष्ठा hinic_dev *nic_dev)
अणु
	वापस hinic_set_max_qnum(nic_dev, nic_dev->hwdev->nic_cap.max_qps);
पूर्ण

अटल पूर्णांक hinic_rss_init(काष्ठा hinic_dev *nic_dev)
अणु
	u8 शेष_rss_key[HINIC_RSS_KEY_SIZE];
	u8 पंचांगpl_idx = nic_dev->rss_पंचांगpl_idx;
	u32 *indir_tbl;
	पूर्णांक err, i;

	indir_tbl = kसुस्मृति(HINIC_RSS_INसूची_SIZE, माप(u32), GFP_KERNEL);
	अगर (!indir_tbl)
		वापस -ENOMEM;

	netdev_rss_key_fill(शेष_rss_key, माप(शेष_rss_key));
	क्रम (i = 0; i < HINIC_RSS_INसूची_SIZE; i++)
		indir_tbl[i] = ethtool_rxfh_indir_शेष(i, nic_dev->num_rss);

	err = hinic_rss_set_ढाँचा_tbl(nic_dev, पंचांगpl_idx, शेष_rss_key);
	अगर (err)
		जाओ out;

	err = hinic_rss_set_indir_tbl(nic_dev, पंचांगpl_idx, indir_tbl);
	अगर (err)
		जाओ out;

	err = hinic_set_rss_type(nic_dev, पंचांगpl_idx, nic_dev->rss_type);
	अगर (err)
		जाओ out;

	err = hinic_rss_set_hash_engine(nic_dev, पंचांगpl_idx,
					nic_dev->rss_hash_engine);
	अगर (err)
		जाओ out;

	err = hinic_rss_cfg(nic_dev, 1, पंचांगpl_idx);
	अगर (err)
		जाओ out;

out:
	kमुक्त(indir_tbl);
	वापस err;
पूर्ण

अटल व्योम hinic_rss_deinit(काष्ठा hinic_dev *nic_dev)
अणु
	hinic_rss_cfg(nic_dev, 0, nic_dev->rss_पंचांगpl_idx);
पूर्ण

अटल व्योम hinic_init_rss_parameters(काष्ठा hinic_dev *nic_dev)
अणु
	nic_dev->rss_hash_engine = HINIC_RSS_HASH_ENGINE_TYPE_XOR;
	nic_dev->rss_type.tcp_ipv6_ext = 1;
	nic_dev->rss_type.ipv6_ext = 1;
	nic_dev->rss_type.tcp_ipv6 = 1;
	nic_dev->rss_type.ipv6 = 1;
	nic_dev->rss_type.tcp_ipv4 = 1;
	nic_dev->rss_type.ipv4 = 1;
	nic_dev->rss_type.udp_ipv6 = 1;
	nic_dev->rss_type.udp_ipv4 = 1;
पूर्ण

अटल व्योम hinic_enable_rss(काष्ठा hinic_dev *nic_dev)
अणु
	काष्ठा net_device *netdev = nic_dev->netdev;
	काष्ठा hinic_hwdev *hwdev = nic_dev->hwdev;
	काष्ठा hinic_hwअगर *hwअगर = hwdev->hwअगर;
	काष्ठा pci_dev *pdev = hwअगर->pdev;
	पूर्णांक i, node, err = 0;
	u16 num_cpus = 0;

	अगर (nic_dev->max_qps <= 1) अणु
		nic_dev->flags &= ~HINIC_RSS_ENABLE;
		nic_dev->rss_limit = nic_dev->max_qps;
		nic_dev->num_qps = nic_dev->max_qps;
		nic_dev->num_rss = nic_dev->max_qps;

		वापस;
	पूर्ण

	err = hinic_rss_ढाँचा_alloc(nic_dev, &nic_dev->rss_पंचांगpl_idx);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Failed to alloc tmpl_idx for rss, can't enable rss for this function\n");
		nic_dev->flags &= ~HINIC_RSS_ENABLE;
		nic_dev->max_qps = 1;
		nic_dev->rss_limit = nic_dev->max_qps;
		nic_dev->num_qps = nic_dev->max_qps;
		nic_dev->num_rss = nic_dev->max_qps;

		वापस;
	पूर्ण

	nic_dev->flags |= HINIC_RSS_ENABLE;

	क्रम (i = 0; i < num_online_cpus(); i++) अणु
		node = cpu_to_node(i);
		अगर (node == dev_to_node(&pdev->dev))
			num_cpus++;
	पूर्ण

	अगर (!num_cpus)
		num_cpus = num_online_cpus();

	nic_dev->num_qps = hinic_hwdev_num_qps(hwdev);
	nic_dev->num_qps = min_t(u16, nic_dev->num_qps, num_cpus);

	nic_dev->rss_limit = nic_dev->num_qps;
	nic_dev->num_rss = nic_dev->num_qps;

	hinic_init_rss_parameters(nic_dev);
	err = hinic_rss_init(nic_dev);
	अगर (err)
		netअगर_err(nic_dev, drv, netdev, "Failed to init rss\n");
पूर्ण

पूर्णांक hinic_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	क्रमागत hinic_port_link_state link_state;
	पूर्णांक err, ret;

	अगर (!(nic_dev->flags & HINIC_INTF_UP)) अणु
		err = hinic_hwdev_अगरup(nic_dev->hwdev, nic_dev->sq_depth,
				       nic_dev->rq_depth);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed - HW interface up\n");
			वापस err;
		पूर्ण
	पूर्ण

	err = create_txqs(nic_dev);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Failed to create Tx queues\n");
		जाओ err_create_txqs;
	पूर्ण

	enable_txqs_napi(nic_dev);

	err = create_rxqs(nic_dev);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Failed to create Rx queues\n");
		जाओ err_create_rxqs;
	पूर्ण

	hinic_enable_rss(nic_dev);

	err = hinic_configure_max_qnum(nic_dev);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, nic_dev->netdev,
			  "Failed to configure the maximum number of queues\n");
		जाओ err_port_state;
	पूर्ण

	netअगर_set_real_num_tx_queues(netdev, nic_dev->num_qps);
	netअगर_set_real_num_rx_queues(netdev, nic_dev->num_qps);

	err = hinic_port_set_state(nic_dev, HINIC_PORT_ENABLE);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Failed to set port state\n");
		जाओ err_port_state;
	पूर्ण

	err = hinic_port_set_func_state(nic_dev, HINIC_FUNC_PORT_ENABLE);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev,
			  "Failed to set func port state\n");
		जाओ err_func_port_state;
	पूर्ण

	करोwn(&nic_dev->mgmt_lock);

	err = hinic_port_link_state(nic_dev, &link_state);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev, "Failed to get link state\n");
		जाओ err_port_link;
	पूर्ण

	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		hinic_notअगरy_all_vfs_link_changed(nic_dev->hwdev, link_state);

	अगर (link_state == HINIC_LINK_STATE_UP) अणु
		nic_dev->flags |= HINIC_LINK_UP;
		nic_dev->cable_unplugged = false;
		nic_dev->module_unrecognized = false;
	पूर्ण

	nic_dev->flags |= HINIC_INTF_UP;

	अगर ((nic_dev->flags & (HINIC_LINK_UP | HINIC_INTF_UP)) ==
	    (HINIC_LINK_UP | HINIC_INTF_UP)) अणु
		netअगर_info(nic_dev, drv, netdev, "link + intf UP\n");
		netअगर_carrier_on(netdev);
		netअगर_tx_wake_all_queues(netdev);
	पूर्ण

	up(&nic_dev->mgmt_lock);

	netअगर_info(nic_dev, drv, netdev, "HINIC_INTF is UP\n");
	वापस 0;

err_port_link:
	up(&nic_dev->mgmt_lock);
	ret = hinic_port_set_func_state(nic_dev, HINIC_FUNC_PORT_DISABLE);
	अगर (ret)
		netअगर_warn(nic_dev, drv, netdev,
			   "Failed to revert func port state\n");

err_func_port_state:
	ret = hinic_port_set_state(nic_dev, HINIC_PORT_DISABLE);
	अगर (ret)
		netअगर_warn(nic_dev, drv, netdev,
			   "Failed to revert port state\n");
err_port_state:
	मुक्त_rxqs(nic_dev);
	अगर (nic_dev->flags & HINIC_RSS_ENABLE) अणु
		hinic_rss_deinit(nic_dev);
		hinic_rss_ढाँचा_मुक्त(nic_dev, nic_dev->rss_पंचांगpl_idx);
	पूर्ण

err_create_rxqs:
	disable_txqs_napi(nic_dev);
	मुक्त_txqs(nic_dev);

err_create_txqs:
	अगर (!(nic_dev->flags & HINIC_INTF_UP))
		hinic_hwdev_अगरकरोwn(nic_dev->hwdev);
	वापस err;
पूर्ण

पूर्णांक hinic_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	अचिन्हित पूर्णांक flags;

	/* Disable txq napi firstly to aviod rewaking txq in मुक्त_tx_poll */
	disable_txqs_napi(nic_dev);

	करोwn(&nic_dev->mgmt_lock);

	flags = nic_dev->flags;
	nic_dev->flags &= ~HINIC_INTF_UP;

	netअगर_carrier_off(netdev);
	netअगर_tx_disable(netdev);

	update_nic_stats(nic_dev);

	up(&nic_dev->mgmt_lock);

	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		hinic_notअगरy_all_vfs_link_changed(nic_dev->hwdev, 0);

	hinic_port_set_state(nic_dev, HINIC_PORT_DISABLE);

	hinic_port_set_func_state(nic_dev, HINIC_FUNC_PORT_DISABLE);

	अगर (nic_dev->flags & HINIC_RSS_ENABLE) अणु
		hinic_rss_deinit(nic_dev);
		hinic_rss_ढाँचा_मुक्त(nic_dev, nic_dev->rss_पंचांगpl_idx);
	पूर्ण

	मुक्त_rxqs(nic_dev);
	मुक्त_txqs(nic_dev);

	अगर (flags & HINIC_INTF_UP)
		hinic_hwdev_अगरकरोwn(nic_dev->hwdev);

	netअगर_info(nic_dev, drv, netdev, "HINIC_INTF is DOWN\n");
	वापस 0;
पूर्ण

अटल पूर्णांक hinic_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	पूर्णांक err;

	netअगर_info(nic_dev, drv, netdev, "set_mtu = %d\n", new_mtu);

	err = hinic_port_set_mtu(nic_dev, new_mtu);
	अगर (err)
		netअगर_err(nic_dev, drv, netdev, "Failed to set port mtu\n");
	अन्यथा
		netdev->mtu = new_mtu;

	वापस err;
पूर्ण

/**
 * change_mac_addr - change the मुख्य mac address of network device
 * @netdev: network device
 * @addr: mac address to set
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक change_mac_addr(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u16 vid = 0;
	पूर्णांक err;

	अगर (!is_valid_ether_addr(addr))
		वापस -EADDRNOTAVAIL;

	netअगर_info(nic_dev, drv, netdev, "change mac addr = %02x %02x %02x %02x %02x %02x\n",
		   addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

	करोwn(&nic_dev->mgmt_lock);

	करो अणु
		err = hinic_port_del_mac(nic_dev, netdev->dev_addr, vid);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to delete mac\n");
			अवरोध;
		पूर्ण

		err = hinic_port_add_mac(nic_dev, addr, vid);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev, "Failed to add mac\n");
			अवरोध;
		पूर्ण

		vid = find_next_bit(nic_dev->vlan_biपंचांगap, VLAN_N_VID, vid + 1);
	पूर्ण जबतक (vid != VLAN_N_VID);

	up(&nic_dev->mgmt_lock);
	वापस err;
पूर्ण

अटल पूर्णांक hinic_set_mac_addr(काष्ठा net_device *netdev, व्योम *addr)
अणु
	अचिन्हित अक्षर new_mac[ETH_ALEN];
	काष्ठा sockaddr *saddr = addr;
	पूर्णांक err;

	स_नकल(new_mac, saddr->sa_data, ETH_ALEN);

	err = change_mac_addr(netdev, new_mac);
	अगर (!err)
		स_नकल(netdev->dev_addr, new_mac, ETH_ALEN);

	वापस err;
पूर्ण

/**
 * add_mac_addr - add mac address to network device
 * @netdev: network device
 * @addr: mac address to add
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक add_mac_addr(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u16 vid = 0;
	पूर्णांक err;

	netअगर_info(nic_dev, drv, netdev, "set mac addr = %02x %02x %02x %02x %02x %02x\n",
		   addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

	करोwn(&nic_dev->mgmt_lock);

	करो अणु
		err = hinic_port_add_mac(nic_dev, addr, vid);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev, "Failed to add mac\n");
			अवरोध;
		पूर्ण

		vid = find_next_bit(nic_dev->vlan_biपंचांगap, VLAN_N_VID, vid + 1);
	पूर्ण जबतक (vid != VLAN_N_VID);

	up(&nic_dev->mgmt_lock);
	वापस err;
पूर्ण

/**
 * हटाओ_mac_addr - हटाओ mac address from network device
 * @netdev: network device
 * @addr: mac address to हटाओ
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक हटाओ_mac_addr(काष्ठा net_device *netdev, स्थिर u8 *addr)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u16 vid = 0;
	पूर्णांक err;

	अगर (!is_valid_ether_addr(addr))
		वापस -EADDRNOTAVAIL;

	netअगर_info(nic_dev, drv, netdev, "remove mac addr = %02x %02x %02x %02x %02x %02x\n",
		   addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

	करोwn(&nic_dev->mgmt_lock);

	करो अणु
		err = hinic_port_del_mac(nic_dev, addr, vid);
		अगर (err) अणु
			netअगर_err(nic_dev, drv, netdev,
				  "Failed to delete mac\n");
			अवरोध;
		पूर्ण

		vid = find_next_bit(nic_dev->vlan_biपंचांगap, VLAN_N_VID, vid + 1);
	पूर्ण जबतक (vid != VLAN_N_VID);

	up(&nic_dev->mgmt_lock);
	वापस err;
पूर्ण

अटल पूर्णांक hinic_vlan_rx_add_vid(काष्ठा net_device *netdev,
				 __always_unused __be16 proto, u16 vid)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	पूर्णांक ret, err;

	netअगर_info(nic_dev, drv, netdev, "add vid = %d\n", vid);

	करोwn(&nic_dev->mgmt_lock);

	err = hinic_port_add_vlan(nic_dev, vid);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev, "Failed to add vlan\n");
		जाओ err_vlan_add;
	पूर्ण

	err = hinic_port_add_mac(nic_dev, netdev->dev_addr, vid);
	अगर (err && err != HINIC_PF_SET_VF_ALREADY) अणु
		netअगर_err(nic_dev, drv, netdev, "Failed to set mac\n");
		जाओ err_add_mac;
	पूर्ण

	biपंचांगap_set(nic_dev->vlan_biपंचांगap, vid, 1);

	up(&nic_dev->mgmt_lock);
	वापस 0;

err_add_mac:
	ret = hinic_port_del_vlan(nic_dev, vid);
	अगर (ret)
		netअगर_err(nic_dev, drv, netdev,
			  "Failed to revert by removing vlan\n");

err_vlan_add:
	up(&nic_dev->mgmt_lock);
	वापस err;
पूर्ण

अटल पूर्णांक hinic_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				  __always_unused __be16 proto, u16 vid)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	पूर्णांक err;

	netअगर_info(nic_dev, drv, netdev, "remove vid = %d\n", vid);

	करोwn(&nic_dev->mgmt_lock);

	err = hinic_port_del_vlan(nic_dev, vid);
	अगर (err) अणु
		netअगर_err(nic_dev, drv, netdev, "Failed to delete vlan\n");
		जाओ err_del_vlan;
	पूर्ण

	biपंचांगap_clear(nic_dev->vlan_biपंचांगap, vid, 1);

	up(&nic_dev->mgmt_lock);
	वापस 0;

err_del_vlan:
	up(&nic_dev->mgmt_lock);
	वापस err;
पूर्ण

अटल व्योम set_rx_mode(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hinic_rx_mode_work *rx_mode_work = work_to_rx_mode_work(work);
	काष्ठा hinic_dev *nic_dev = rx_mode_work_to_nic_dev(rx_mode_work);

	hinic_port_set_rx_mode(nic_dev, rx_mode_work->rx_mode);

	__dev_uc_sync(nic_dev->netdev, add_mac_addr, हटाओ_mac_addr);
	__dev_mc_sync(nic_dev->netdev, add_mac_addr, हटाओ_mac_addr);
पूर्ण

अटल व्योम hinic_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_rx_mode_work *rx_mode_work;
	u32 rx_mode;

	rx_mode_work = &nic_dev->rx_mode_work;

	rx_mode = HINIC_RX_MODE_UC |
		  HINIC_RX_MODE_MC |
		  HINIC_RX_MODE_BC;

	अगर (netdev->flags & IFF_PROMISC) अणु
		अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
			rx_mode |= HINIC_RX_MODE_PROMISC;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_ALLMULTI) अणु
		rx_mode |= HINIC_RX_MODE_MC_ALL;
	पूर्ण

	rx_mode_work->rx_mode = rx_mode;

	queue_work(nic_dev->workq, &rx_mode_work->work);
पूर्ण

अटल व्योम hinic_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	u16 sw_pi, hw_ci, sw_ci;
	काष्ठा hinic_sq *sq;
	u16 num_sqs, q_id;

	num_sqs = hinic_hwdev_num_qps(nic_dev->hwdev);

	netअगर_err(nic_dev, drv, netdev, "Tx timeout\n");

	क्रम (q_id = 0; q_id < num_sqs; q_id++) अणु
		अगर (!netअगर_xmit_stopped(netdev_get_tx_queue(netdev, q_id)))
			जारी;

		sq = hinic_hwdev_get_sq(nic_dev->hwdev, q_id);
		sw_pi = atomic_पढ़ो(&sq->wq->prod_idx) & sq->wq->mask;
		hw_ci = be16_to_cpu(*(u16 *)(sq->hw_ci_addr)) & sq->wq->mask;
		sw_ci = atomic_पढ़ो(&sq->wq->cons_idx) & sq->wq->mask;
		netअगर_err(nic_dev, drv, netdev, "Txq%d: sw_pi: %d, hw_ci: %d, sw_ci: %d, napi->state: 0x%lx\n",
			  q_id, sw_pi, hw_ci, sw_ci,
			  nic_dev->txqs[q_id].napi.state);
	पूर्ण
पूर्ण

अटल व्योम hinic_get_stats64(काष्ठा net_device *netdev,
			      काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा hinic_rxq_stats *nic_rx_stats;
	काष्ठा hinic_txq_stats *nic_tx_stats;

	nic_rx_stats = &nic_dev->rx_stats;
	nic_tx_stats = &nic_dev->tx_stats;

	करोwn(&nic_dev->mgmt_lock);

	अगर (nic_dev->flags & HINIC_INTF_UP)
		update_nic_stats(nic_dev);

	up(&nic_dev->mgmt_lock);

	stats->rx_bytes   = nic_rx_stats->bytes;
	stats->rx_packets = nic_rx_stats->pkts;
	stats->rx_errors  = nic_rx_stats->errors;

	stats->tx_bytes   = nic_tx_stats->bytes;
	stats->tx_packets = nic_tx_stats->pkts;
	stats->tx_errors  = nic_tx_stats->tx_dropped;
पूर्ण

अटल पूर्णांक hinic_set_features(काष्ठा net_device *netdev,
			      netdev_features_t features)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);

	वापस set_features(nic_dev, nic_dev->netdev->features,
			    features, false);
पूर्ण

अटल netdev_features_t hinic_fix_features(काष्ठा net_device *netdev,
					    netdev_features_t features)
अणु
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);

	/* If Rx checksum is disabled, then LRO should also be disabled */
	अगर (!(features & NETIF_F_RXCSUM)) अणु
		netअगर_info(nic_dev, drv, netdev, "disabling LRO as RXCSUM is off\n");
		features &= ~NETIF_F_LRO;
	पूर्ण

	वापस features;
पूर्ण

अटल स्थिर काष्ठा net_device_ops hinic_netdev_ops = अणु
	.nकरो_खोलो = hinic_खोलो,
	.nकरो_stop = hinic_बंद,
	.nकरो_change_mtu = hinic_change_mtu,
	.nकरो_set_mac_address = hinic_set_mac_addr,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_vlan_rx_add_vid = hinic_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = hinic_vlan_rx_समाप्त_vid,
	.nकरो_set_rx_mode = hinic_set_rx_mode,
	.nकरो_start_xmit = hinic_xmit_frame,
	.nकरो_tx_समयout = hinic_tx_समयout,
	.nकरो_get_stats64 = hinic_get_stats64,
	.nकरो_fix_features = hinic_fix_features,
	.nकरो_set_features = hinic_set_features,
	.nकरो_set_vf_mac	= hinic_nकरो_set_vf_mac,
	.nकरो_set_vf_vlan = hinic_nकरो_set_vf_vlan,
	.nकरो_get_vf_config = hinic_nकरो_get_vf_config,
	.nकरो_set_vf_trust = hinic_nकरो_set_vf_trust,
	.nकरो_set_vf_rate = hinic_nकरो_set_vf_bw,
	.nकरो_set_vf_spoofchk = hinic_nकरो_set_vf_spoofchk,
	.nकरो_set_vf_link_state = hinic_nकरो_set_vf_link_state,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops hinicvf_netdev_ops = अणु
	.nकरो_खोलो = hinic_खोलो,
	.nकरो_stop = hinic_बंद,
	.nकरो_change_mtu = hinic_change_mtu,
	.nकरो_set_mac_address = hinic_set_mac_addr,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_vlan_rx_add_vid = hinic_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = hinic_vlan_rx_समाप्त_vid,
	.nकरो_set_rx_mode = hinic_set_rx_mode,
	.nकरो_start_xmit = hinic_xmit_frame,
	.nकरो_tx_समयout = hinic_tx_समयout,
	.nकरो_get_stats64 = hinic_get_stats64,
	.nकरो_fix_features = hinic_fix_features,
	.nकरो_set_features = hinic_set_features,
पूर्ण;

अटल व्योम netdev_features_init(काष्ठा net_device *netdev)
अणु
	netdev->hw_features = NETIF_F_SG | NETIF_F_HIGHDMA | NETIF_F_IP_CSUM |
			      NETIF_F_IPV6_CSUM | NETIF_F_TSO | NETIF_F_TSO6 |
			      NETIF_F_RXCSUM | NETIF_F_LRO |
			      NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
			      NETIF_F_GSO_UDP_TUNNEL | NETIF_F_GSO_UDP_TUNNEL_CSUM;

	netdev->vlan_features = netdev->hw_features;

	netdev->features = netdev->hw_features | NETIF_F_HW_VLAN_CTAG_FILTER;

	netdev->hw_enc_features = NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_SCTP_CRC |
				  NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_TSO_ECN |
				  NETIF_F_GSO_UDP_TUNNEL_CSUM | NETIF_F_GSO_UDP_TUNNEL;
पूर्ण

अटल व्योम hinic_refresh_nic_cfg(काष्ठा hinic_dev *nic_dev)
अणु
	काष्ठा hinic_nic_cfg *nic_cfg = &nic_dev->hwdev->func_to_io.nic_cfg;
	काष्ठा hinic_छोड़ो_config छोड़ो_info = अणु0पूर्ण;
	काष्ठा hinic_port_cap port_cap = अणु0पूर्ण;

	अगर (hinic_port_get_cap(nic_dev, &port_cap))
		वापस;

	mutex_lock(&nic_cfg->cfg_mutex);
	अगर (nic_cfg->छोड़ो_set || !port_cap.स्वतःneg_state) अणु
		nic_cfg->स्वतः_neg = port_cap.स्वतःneg_state;
		छोड़ो_info.स्वतः_neg = nic_cfg->स्वतः_neg;
		छोड़ो_info.rx_छोड़ो = nic_cfg->rx_छोड़ो;
		छोड़ो_info.tx_छोड़ो = nic_cfg->tx_छोड़ो;
		hinic_set_hw_छोड़ो_info(nic_dev->hwdev, &छोड़ो_info);
	पूर्ण
	mutex_unlock(&nic_cfg->cfg_mutex);
पूर्ण

/**
 * link_status_event_handler - link event handler
 * @handle: nic device क्रम the handler
 * @buf_in: input buffer
 * @in_size: input size
 * @buf_out: output buffer
 * @out_size: वापसed output size
 *
 * Return 0 - Success, negative - Failure
 **/
अटल व्योम link_status_event_handler(व्योम *handle, व्योम *buf_in, u16 in_size,
				      व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_port_link_status *link_status, *ret_link_status;
	काष्ठा hinic_dev *nic_dev = handle;

	link_status = buf_in;

	अगर (link_status->link == HINIC_LINK_STATE_UP) अणु
		करोwn(&nic_dev->mgmt_lock);

		nic_dev->flags |= HINIC_LINK_UP;
		nic_dev->cable_unplugged = false;
		nic_dev->module_unrecognized = false;

		अगर ((nic_dev->flags & (HINIC_LINK_UP | HINIC_INTF_UP)) ==
		    (HINIC_LINK_UP | HINIC_INTF_UP)) अणु
			netअगर_carrier_on(nic_dev->netdev);
			netअगर_tx_wake_all_queues(nic_dev->netdev);
		पूर्ण

		up(&nic_dev->mgmt_lock);

		अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
			hinic_refresh_nic_cfg(nic_dev);

		netअगर_info(nic_dev, drv, nic_dev->netdev, "HINIC_Link is UP\n");
	पूर्ण अन्यथा अणु
		करोwn(&nic_dev->mgmt_lock);

		nic_dev->flags &= ~HINIC_LINK_UP;

		netअगर_carrier_off(nic_dev->netdev);
		netअगर_tx_disable(nic_dev->netdev);

		up(&nic_dev->mgmt_lock);

		netअगर_info(nic_dev, drv, nic_dev->netdev, "HINIC_Link is DOWN\n");
	पूर्ण

	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर))
		hinic_notअगरy_all_vfs_link_changed(nic_dev->hwdev,
						  link_status->link);

	ret_link_status = buf_out;
	ret_link_status->status = 0;

	*out_size = माप(*ret_link_status);
पूर्ण

अटल व्योम cable_plug_event(व्योम *handle,
			     व्योम *buf_in, u16 in_size,
			     व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_cable_plug_event *plug_event = buf_in;
	काष्ठा hinic_dev *nic_dev = handle;

	nic_dev->cable_unplugged = plug_event->plugged ? false : true;

	*out_size = माप(*plug_event);
	plug_event = buf_out;
	plug_event->status = 0;
पूर्ण

अटल व्योम link_err_event(व्योम *handle,
			   व्योम *buf_in, u16 in_size,
			   व्योम *buf_out, u16 *out_size)
अणु
	काष्ठा hinic_link_err_event *link_err = buf_in;
	काष्ठा hinic_dev *nic_dev = handle;

	अगर (link_err->err_type >= LINK_ERR_NUM)
		netअगर_info(nic_dev, link, nic_dev->netdev,
			   "Link failed, Unknown error type: 0x%x\n",
			   link_err->err_type);
	अन्यथा
		nic_dev->module_unrecognized = true;

	*out_size = माप(*link_err);
	link_err = buf_out;
	link_err->status = 0;
पूर्ण

अटल पूर्णांक set_features(काष्ठा hinic_dev *nic_dev,
			netdev_features_t pre_features,
			netdev_features_t features, bool क्रमce_change)
अणु
	netdev_features_t changed = क्रमce_change ? ~0 : pre_features ^ features;
	u32 csum_en = HINIC_RX_CSUM_OFFLOAD_EN;
	netdev_features_t failed_features = 0;
	पूर्णांक ret = 0;
	पूर्णांक err = 0;

	अगर (changed & NETIF_F_TSO) अणु
		ret = hinic_port_set_tso(nic_dev, (features & NETIF_F_TSO) ?
					 HINIC_TSO_ENABLE : HINIC_TSO_DISABLE);
		अगर (ret) अणु
			err = ret;
			failed_features |= NETIF_F_TSO;
		पूर्ण
	पूर्ण

	अगर (changed & NETIF_F_RXCSUM) अणु
		ret = hinic_set_rx_csum_offload(nic_dev, csum_en);
		अगर (ret) अणु
			err = ret;
			failed_features |= NETIF_F_RXCSUM;
		पूर्ण
	पूर्ण

	अगर (changed & NETIF_F_LRO) अणु
		ret = hinic_set_rx_lro_state(nic_dev,
					     !!(features & NETIF_F_LRO),
					     HINIC_LRO_RX_TIMER_DEFAULT,
					     HINIC_LRO_MAX_WQE_NUM_DEFAULT);
		अगर (ret) अणु
			err = ret;
			failed_features |= NETIF_F_LRO;
		पूर्ण
	पूर्ण

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX) अणु
		ret = hinic_set_rx_vlan_offload(nic_dev,
						!!(features &
						   NETIF_F_HW_VLAN_CTAG_RX));
		अगर (ret) अणु
			err = ret;
			failed_features |= NETIF_F_HW_VLAN_CTAG_RX;
		पूर्ण
	पूर्ण

	अगर (err) अणु
		nic_dev->netdev->features = features ^ failed_features;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hinic_init_पूर्णांकr_coalesce(काष्ठा hinic_dev *nic_dev)
अणु
	u64 size;
	u16 i;

	size = माप(काष्ठा hinic_पूर्णांकr_coal_info) * nic_dev->max_qps;
	nic_dev->rx_पूर्णांकr_coalesce = kzalloc(size, GFP_KERNEL);
	अगर (!nic_dev->rx_पूर्णांकr_coalesce)
		वापस -ENOMEM;
	nic_dev->tx_पूर्णांकr_coalesce = kzalloc(size, GFP_KERNEL);
	अगर (!nic_dev->tx_पूर्णांकr_coalesce) अणु
		kमुक्त(nic_dev->rx_पूर्णांकr_coalesce);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < nic_dev->max_qps; i++) अणु
		nic_dev->rx_पूर्णांकr_coalesce[i].pending_limt =
			HINIC_DEAULT_TXRX_MSIX_PENDING_LIMIT;
		nic_dev->rx_पूर्णांकr_coalesce[i].coalesce_समयr_cfg =
			HINIC_DEAULT_TXRX_MSIX_COALESC_TIMER_CFG;
		nic_dev->rx_पूर्णांकr_coalesce[i].resend_समयr_cfg =
			HINIC_DEAULT_TXRX_MSIX_RESEND_TIMER_CFG;
		nic_dev->tx_पूर्णांकr_coalesce[i].pending_limt =
			HINIC_DEAULT_TXRX_MSIX_PENDING_LIMIT;
		nic_dev->tx_पूर्णांकr_coalesce[i].coalesce_समयr_cfg =
			HINIC_DEAULT_TXRX_MSIX_COALESC_TIMER_CFG;
		nic_dev->tx_पूर्णांकr_coalesce[i].resend_समयr_cfg =
			HINIC_DEAULT_TXRX_MSIX_RESEND_TIMER_CFG;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hinic_मुक्त_पूर्णांकr_coalesce(काष्ठा hinic_dev *nic_dev)
अणु
	kमुक्त(nic_dev->tx_पूर्णांकr_coalesce);
	kमुक्त(nic_dev->rx_पूर्णांकr_coalesce);
पूर्ण

/**
 * nic_dev_init - Initialize the NIC device
 * @pdev: the NIC pci device
 *
 * Return 0 - Success, negative - Failure
 **/
अटल पूर्णांक nic_dev_init(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hinic_rx_mode_work *rx_mode_work;
	काष्ठा hinic_txq_stats *tx_stats;
	काष्ठा hinic_rxq_stats *rx_stats;
	काष्ठा hinic_dev *nic_dev;
	काष्ठा net_device *netdev;
	काष्ठा hinic_hwdev *hwdev;
	काष्ठा devlink *devlink;
	पूर्णांक err, num_qps;

	devlink = hinic_devlink_alloc();
	अगर (!devlink) अणु
		dev_err(&pdev->dev, "Hinic devlink alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	hwdev = hinic_init_hwdev(pdev, devlink);
	अगर (IS_ERR(hwdev)) अणु
		dev_err(&pdev->dev, "Failed to initialize HW device\n");
		hinic_devlink_मुक्त(devlink);
		वापस PTR_ERR(hwdev);
	पूर्ण

	num_qps = hinic_hwdev_num_qps(hwdev);
	अगर (num_qps <= 0) अणु
		dev_err(&pdev->dev, "Invalid number of QPS\n");
		err = -EINVAL;
		जाओ err_num_qps;
	पूर्ण

	netdev = alloc_etherdev_mq(माप(*nic_dev), num_qps);
	अगर (!netdev) अणु
		dev_err(&pdev->dev, "Failed to allocate Ethernet device\n");
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	अगर (!HINIC_IS_VF(hwdev->hwअगर))
		netdev->netdev_ops = &hinic_netdev_ops;
	अन्यथा
		netdev->netdev_ops = &hinicvf_netdev_ops;

	netdev->max_mtu = ETH_MAX_MTU;

	nic_dev = netdev_priv(netdev);
	nic_dev->netdev = netdev;
	nic_dev->hwdev  = hwdev;
	nic_dev->msg_enable = MSG_ENABLE_DEFAULT;
	nic_dev->flags = 0;
	nic_dev->txqs = शून्य;
	nic_dev->rxqs = शून्य;
	nic_dev->tx_weight = tx_weight;
	nic_dev->rx_weight = rx_weight;
	nic_dev->sq_depth = HINIC_SQ_DEPTH;
	nic_dev->rq_depth = HINIC_RQ_DEPTH;
	nic_dev->sriov_info.hwdev = hwdev;
	nic_dev->sriov_info.pdev = pdev;
	nic_dev->max_qps = num_qps;
	nic_dev->devlink = devlink;

	hinic_set_ethtool_ops(netdev);

	sema_init(&nic_dev->mgmt_lock, 1);

	tx_stats = &nic_dev->tx_stats;
	rx_stats = &nic_dev->rx_stats;

	u64_stats_init(&tx_stats->syncp);
	u64_stats_init(&rx_stats->syncp);

	nic_dev->vlan_biपंचांगap = devm_kzalloc(&pdev->dev,
					    VLAN_BITMAP_SIZE(nic_dev),
					    GFP_KERNEL);
	अगर (!nic_dev->vlan_biपंचांगap) अणु
		err = -ENOMEM;
		जाओ err_vlan_biपंचांगap;
	पूर्ण

	nic_dev->workq = create_singlethपढ़ो_workqueue(HINIC_WQ_NAME);
	अगर (!nic_dev->workq) अणु
		err = -ENOMEM;
		जाओ err_workq;
	पूर्ण

	pci_set_drvdata(pdev, netdev);

	err = hinic_port_get_mac(nic_dev, netdev->dev_addr);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to get mac address\n");
		जाओ err_get_mac;
	पूर्ण

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर)) अणु
			dev_err(&pdev->dev, "Invalid MAC address\n");
			err = -EIO;
			जाओ err_add_mac;
		पूर्ण

		dev_info(&pdev->dev, "Invalid MAC address %pM, using random\n",
			 netdev->dev_addr);
		eth_hw_addr_अक्रमom(netdev);
	पूर्ण

	err = hinic_port_add_mac(nic_dev, netdev->dev_addr, 0);
	अगर (err && err != HINIC_PF_SET_VF_ALREADY) अणु
		dev_err(&pdev->dev, "Failed to add mac\n");
		जाओ err_add_mac;
	पूर्ण

	err = hinic_port_set_mtu(nic_dev, netdev->mtu);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to set mtu\n");
		जाओ err_set_mtu;
	पूर्ण

	rx_mode_work = &nic_dev->rx_mode_work;
	INIT_WORK(&rx_mode_work->work, set_rx_mode);

	netdev_features_init(netdev);

	netअगर_carrier_off(netdev);

	hinic_hwdev_cb_रेजिस्टर(nic_dev->hwdev, HINIC_MGMT_MSG_CMD_LINK_STATUS,
				nic_dev, link_status_event_handler);
	hinic_hwdev_cb_रेजिस्टर(nic_dev->hwdev,
				HINIC_MGMT_MSG_CMD_CABLE_PLUG_EVENT,
				nic_dev, cable_plug_event);
	hinic_hwdev_cb_रेजिस्टर(nic_dev->hwdev,
				HINIC_MGMT_MSG_CMD_LINK_ERR_EVENT,
				nic_dev, link_err_event);

	err = set_features(nic_dev, 0, nic_dev->netdev->features, true);
	अगर (err)
		जाओ err_set_features;

	/* enable छोड़ो and disable pfc by शेष */
	err = hinic_dcb_set_pfc(nic_dev->hwdev, 0, 0);
	अगर (err)
		जाओ err_set_pfc;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	err = hinic_init_पूर्णांकr_coalesce(nic_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to init_intr_coalesce\n");
		जाओ err_init_पूर्णांकr;
	पूर्ण

	hinic_dbg_init(nic_dev);

	hinic_func_tbl_dbgfs_init(nic_dev);

	err = hinic_func_table_debug_add(nic_dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to add func_table debug\n");
		जाओ err_add_func_table_dbg;
	पूर्ण

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register netdev\n");
		जाओ err_reg_netdev;
	पूर्ण

	वापस 0;

err_reg_netdev:
	hinic_func_table_debug_rem(nic_dev);
err_add_func_table_dbg:
	hinic_func_tbl_dbgfs_uninit(nic_dev);
	hinic_dbg_uninit(nic_dev);
	hinic_मुक्त_पूर्णांकr_coalesce(nic_dev);
err_init_पूर्णांकr:
err_set_pfc:
err_set_features:
	hinic_hwdev_cb_unरेजिस्टर(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_LINK_ERR_EVENT);
	hinic_hwdev_cb_unरेजिस्टर(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_CABLE_PLUG_EVENT);
	hinic_hwdev_cb_unरेजिस्टर(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_LINK_STATUS);
	cancel_work_sync(&rx_mode_work->work);

err_set_mtu:
	hinic_port_del_mac(nic_dev, netdev->dev_addr, 0);
err_add_mac:
err_get_mac:
	pci_set_drvdata(pdev, शून्य);
	destroy_workqueue(nic_dev->workq);
err_workq:
err_vlan_biपंचांगap:
	मुक्त_netdev(netdev);

err_alloc_etherdev:
err_num_qps:
	hinic_मुक्त_hwdev(hwdev);
	hinic_devlink_मुक्त(devlink);
	वापस err;
पूर्ण

अटल पूर्णांक hinic_probe(काष्ठा pci_dev *pdev,
		       स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err = pci_enable_device(pdev);

	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to enable PCI device\n");
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, HINIC_DRV_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request PCI regions\n");
		जाओ err_pci_regions;
	पूर्ण

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_warn(&pdev->dev, "Couldn't set 64-bit DMA mask\n");
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to set DMA mask\n");
			जाओ err_dma_mask;
		पूर्ण
	पूर्ण

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_warn(&pdev->dev,
			 "Couldn't set 64-bit consistent DMA mask\n");
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Failed to set consistent DMA mask\n");
			जाओ err_dma_consistent_mask;
		पूर्ण
	पूर्ण

	err = nic_dev_init(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to initialize NIC device\n");
		जाओ err_nic_dev_init;
	पूर्ण

	dev_info(&pdev->dev, "HiNIC driver - probed\n");
	वापस 0;

err_nic_dev_init:
err_dma_consistent_mask:
err_dma_mask:
	pci_release_regions(pdev);

err_pci_regions:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

#घोषणा HINIC_WAIT_SRIOV_CFG_TIMEOUT	15000

अटल व्योम रुको_sriov_cfg_complete(काष्ठा hinic_dev *nic_dev)
अणु
	काष्ठा hinic_sriov_info *sriov_info = &nic_dev->sriov_info;
	u32 loop_cnt = 0;

	set_bit(HINIC_FUNC_REMOVE, &sriov_info->state);
	usleep_range(9900, 10000);

	जबतक (loop_cnt < HINIC_WAIT_SRIOV_CFG_TIMEOUT) अणु
		अगर (!test_bit(HINIC_SRIOV_ENABLE, &sriov_info->state) &&
		    !test_bit(HINIC_SRIOV_DISABLE, &sriov_info->state))
			वापस;

		usleep_range(9900, 10000);
		loop_cnt++;
	पूर्ण
पूर्ण

अटल व्योम hinic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा hinic_dev *nic_dev = netdev_priv(netdev);
	काष्ठा devlink *devlink = nic_dev->devlink;
	काष्ठा hinic_rx_mode_work *rx_mode_work;

	अगर (!HINIC_IS_VF(nic_dev->hwdev->hwअगर)) अणु
		रुको_sriov_cfg_complete(nic_dev);
		hinic_pci_sriov_disable(pdev);
	पूर्ण

	unरेजिस्टर_netdev(netdev);

	hinic_func_table_debug_rem(nic_dev);

	hinic_func_tbl_dbgfs_uninit(nic_dev);

	hinic_dbg_uninit(nic_dev);

	hinic_मुक्त_पूर्णांकr_coalesce(nic_dev);

	hinic_port_del_mac(nic_dev, netdev->dev_addr, 0);

	hinic_hwdev_cb_unरेजिस्टर(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_LINK_ERR_EVENT);
	hinic_hwdev_cb_unरेजिस्टर(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_CABLE_PLUG_EVENT);
	hinic_hwdev_cb_unरेजिस्टर(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_LINK_STATUS);

	rx_mode_work = &nic_dev->rx_mode_work;
	cancel_work_sync(&rx_mode_work->work);

	pci_set_drvdata(pdev, शून्य);

	destroy_workqueue(nic_dev->workq);

	hinic_मुक्त_hwdev(nic_dev->hwdev);

	मुक्त_netdev(netdev);

	hinic_devlink_मुक्त(devlink);

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	dev_info(&pdev->dev, "HiNIC driver - removed\n");
पूर्ण

अटल व्योम hinic_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id hinic_pci_table[] = अणु
	अणु PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_QUAD_PORT_25GE), 0पूर्ण,
	अणु PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_DUAL_PORT_100GE), 0पूर्ण,
	अणु PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_DUAL_PORT_100GE_MEZZ), 0पूर्ण,
	अणु PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_QUAD_PORT_25GE_MEZZ), 0पूर्ण,
	अणु PCI_VDEVICE(HUAWEI, HINIC_DEV_ID_VF), 0पूर्ण,
	अणु 0, 0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, hinic_pci_table);

अटल काष्ठा pci_driver hinic_driver = अणु
	.name           = HINIC_DRV_NAME,
	.id_table       = hinic_pci_table,
	.probe          = hinic_probe,
	.हटाओ         = hinic_हटाओ,
	.shutकरोwn       = hinic_shutकरोwn,
	.sriov_configure = hinic_pci_sriov_configure,
पूर्ण;

अटल पूर्णांक __init hinic_module_init(व्योम)
अणु
	hinic_dbg_रेजिस्टर_debugfs(HINIC_DRV_NAME);
	वापस pci_रेजिस्टर_driver(&hinic_driver);
पूर्ण

अटल व्योम __निकास hinic_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hinic_driver);
	hinic_dbg_unरेजिस्टर_debugfs();
पूर्ण

module_init(hinic_module_init);
module_निकास(hinic_module_निकास);
