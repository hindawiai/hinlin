<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Cavium, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/log2.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/irq.h>
#समावेश <linux/iommu.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/filter.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/workqueue.h>

#समावेश "nic_reg.h"
#समावेश "nic.h"
#समावेश "nicvf_queues.h"
#समावेश "thunder_bgx.h"
#समावेश "../common/cavium_ptp.h"

#घोषणा DRV_NAME	"nicvf"
#घोषणा DRV_VERSION	"1.0"

/* NOTE: Packets bigger than 1530 are split across multiple pages and XDP needs
 * the buffer to be contiguous. Allow XDP to be set up only अगर we करोn't exceed
 * this value, keeping headroom क्रम the 14 byte Ethernet header and two
 * VLAN tags (क्रम QinQ)
 */
#घोषणा MAX_XDP_MTU	(1530 - ETH_HLEN - VLAN_HLEN * 2)

/* Supported devices */
अटल स्थिर काष्ठा pci_device_id nicvf_id_table[] = अणु
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM,
			 PCI_DEVICE_ID_THUNDER_NIC_VF,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_88XX_NIC_VF) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM,
			 PCI_DEVICE_ID_THUNDER_PASS1_NIC_VF,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_88XX_PASS1_NIC_VF) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM,
			 PCI_DEVICE_ID_THUNDER_NIC_VF,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_81XX_NIC_VF) पूर्ण,
	अणु PCI_DEVICE_SUB(PCI_VENDOR_ID_CAVIUM,
			 PCI_DEVICE_ID_THUNDER_NIC_VF,
			 PCI_VENDOR_ID_CAVIUM,
			 PCI_SUBSYS_DEVID_83XX_NIC_VF) पूर्ण,
	अणु 0, पूर्ण  /* end of table */
पूर्ण;

MODULE_AUTHOR("Sunil Goutham");
MODULE_DESCRIPTION("Cavium Thunder NIC Virtual Function Driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, nicvf_id_table);

अटल पूर्णांक debug = 0x00;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug message level bitmap");

अटल पूर्णांक cpi_alg = CPI_ALG_NONE;
module_param(cpi_alg, पूर्णांक, 0444);
MODULE_PARM_DESC(cpi_alg,
		 "PFC algorithm (0=none, 1=VLAN, 2=VLAN16, 3=IP Diffserv)");

अटल अंतरभूत u8 nicvf_netdev_qidx(काष्ठा nicvf *nic, u8 qidx)
अणु
	अगर (nic->sqs_mode)
		वापस qidx + ((nic->sqs_id + 1) * MAX_CMP_QUEUES_PER_QS);
	अन्यथा
		वापस qidx;
पूर्ण

/* The Cavium ThunderX network controller can *only* be found in SoCs
 * containing the ThunderX ARM64 CPU implementation.  All accesses to the device
 * रेजिस्टरs on this platक्रमm are implicitly strongly ordered with respect
 * to memory accesses. So ग_लिखोq_relaxed() and पढ़ोq_relaxed() are safe to use
 * with no memory barriers in this driver.  The पढ़ोq()/ग_लिखोq() functions add
 * explicit ordering operation which in this हाल are redundant, and only
 * add overhead.
 */

/* Register पढ़ो/ग_लिखो APIs */
व्योम nicvf_reg_ग_लिखो(काष्ठा nicvf *nic, u64 offset, u64 val)
अणु
	ग_लिखोq_relaxed(val, nic->reg_base + offset);
पूर्ण

u64 nicvf_reg_पढ़ो(काष्ठा nicvf *nic, u64 offset)
अणु
	वापस पढ़ोq_relaxed(nic->reg_base + offset);
पूर्ण

व्योम nicvf_queue_reg_ग_लिखो(काष्ठा nicvf *nic, u64 offset,
			   u64 qidx, u64 val)
अणु
	व्योम __iomem *addr = nic->reg_base + offset;

	ग_लिखोq_relaxed(val, addr + (qidx << NIC_Q_NUM_SHIFT));
पूर्ण

u64 nicvf_queue_reg_पढ़ो(काष्ठा nicvf *nic, u64 offset, u64 qidx)
अणु
	व्योम __iomem *addr = nic->reg_base + offset;

	वापस पढ़ोq_relaxed(addr + (qidx << NIC_Q_NUM_SHIFT));
पूर्ण

/* VF -> PF mailbox communication */
अटल व्योम nicvf_ग_लिखो_to_mbx(काष्ठा nicvf *nic, जोड़ nic_mbx *mbx)
अणु
	u64 *msg = (u64 *)mbx;

	nicvf_reg_ग_लिखो(nic, NIC_VF_PF_MAILBOX_0_1 + 0, msg[0]);
	nicvf_reg_ग_लिखो(nic, NIC_VF_PF_MAILBOX_0_1 + 8, msg[1]);
पूर्ण

पूर्णांक nicvf_send_msg_to_pf(काष्ठा nicvf *nic, जोड़ nic_mbx *mbx)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret = 0;

	mutex_lock(&nic->rx_mode_mtx);

	nic->pf_acked = false;
	nic->pf_nacked = false;

	nicvf_ग_लिखो_to_mbx(nic, mbx);

	समयout = jअगरfies + msecs_to_jअगरfies(NIC_MBOX_MSG_TIMEOUT);
	/* Wait क्रम previous message to be acked, समयout 2sec */
	जबतक (!nic->pf_acked) अणु
		अगर (nic->pf_nacked) अणु
			netdev_err(nic->netdev,
				   "PF NACK to mbox msg 0x%02x from VF%d\n",
				   (mbx->msg.msg & 0xFF), nic->vf_id);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		usleep_range(8000, 10000);
		अगर (nic->pf_acked)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			netdev_err(nic->netdev,
				   "PF didn't ACK to mbox msg 0x%02x from VF%d\n",
				   (mbx->msg.msg & 0xFF), nic->vf_id);
			ret = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&nic->rx_mode_mtx);
	वापस ret;
पूर्ण

/* Checks अगर VF is able to comminicate with PF
* and also माला_लो the VNIC number this VF is associated to.
*/
अटल पूर्णांक nicvf_check_pf_पढ़ोy(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.msg.msg = NIC_MBOX_MSG_READY;
	अगर (nicvf_send_msg_to_pf(nic, &mbx)) अणु
		netdev_err(nic->netdev,
			   "PF didn't respond to READY msg\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम nicvf_send_cfg_करोne(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.msg.msg = NIC_MBOX_MSG_CFG_DONE;
	अगर (nicvf_send_msg_to_pf(nic, &mbx)) अणु
		netdev_err(nic->netdev,
			   "PF didn't respond to CFG DONE msg\n");
	पूर्ण
पूर्ण

अटल व्योम nicvf_पढ़ो_bgx_stats(काष्ठा nicvf *nic, काष्ठा bgx_stats_msg *bgx)
अणु
	अगर (bgx->rx)
		nic->bgx_stats.rx_stats[bgx->idx] = bgx->stats;
	अन्यथा
		nic->bgx_stats.tx_stats[bgx->idx] = bgx->stats;
पूर्ण

अटल व्योम  nicvf_handle_mbx_पूर्णांकr(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	u64 *mbx_data;
	u64 mbx_addr;
	पूर्णांक i;

	mbx_addr = NIC_VF_PF_MAILBOX_0_1;
	mbx_data = (u64 *)&mbx;

	क्रम (i = 0; i < NIC_PF_VF_MAILBOX_SIZE; i++) अणु
		*mbx_data = nicvf_reg_पढ़ो(nic, mbx_addr);
		mbx_data++;
		mbx_addr += माप(u64);
	पूर्ण

	netdev_dbg(nic->netdev, "Mbox message: msg: 0x%x\n", mbx.msg.msg);
	चयन (mbx.msg.msg) अणु
	हाल NIC_MBOX_MSG_READY:
		nic->pf_acked = true;
		nic->vf_id = mbx.nic_cfg.vf_id & 0x7F;
		nic->tns_mode = mbx.nic_cfg.tns_mode & 0x7F;
		nic->node = mbx.nic_cfg.node_id;
		अगर (!nic->set_mac_pending)
			ether_addr_copy(nic->netdev->dev_addr,
					mbx.nic_cfg.mac_addr);
		nic->sqs_mode = mbx.nic_cfg.sqs_mode;
		nic->loopback_supported = mbx.nic_cfg.loopback_supported;
		nic->link_up = false;
		nic->duplex = 0;
		nic->speed = 0;
		अवरोध;
	हाल NIC_MBOX_MSG_ACK:
		nic->pf_acked = true;
		अवरोध;
	हाल NIC_MBOX_MSG_NACK:
		nic->pf_nacked = true;
		अवरोध;
	हाल NIC_MBOX_MSG_RSS_SIZE:
		nic->rss_info.rss_size = mbx.rss_size.ind_tbl_size;
		nic->pf_acked = true;
		अवरोध;
	हाल NIC_MBOX_MSG_BGX_STATS:
		nicvf_पढ़ो_bgx_stats(nic, &mbx.bgx_stats);
		nic->pf_acked = true;
		अवरोध;
	हाल NIC_MBOX_MSG_BGX_LINK_CHANGE:
		nic->pf_acked = true;
		अगर (nic->link_up != mbx.link_status.link_up) अणु
			nic->link_up = mbx.link_status.link_up;
			nic->duplex = mbx.link_status.duplex;
			nic->speed = mbx.link_status.speed;
			nic->mac_type = mbx.link_status.mac_type;
			अगर (nic->link_up) अणु
				netdev_info(nic->netdev,
					    "Link is Up %d Mbps %s duplex\n",
					    nic->speed,
					    nic->duplex == DUPLEX_FULL ?
					    "Full" : "Half");
				netअगर_carrier_on(nic->netdev);
				netअगर_tx_start_all_queues(nic->netdev);
			पूर्ण अन्यथा अणु
				netdev_info(nic->netdev, "Link is Down\n");
				netअगर_carrier_off(nic->netdev);
				netअगर_tx_stop_all_queues(nic->netdev);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NIC_MBOX_MSG_ALLOC_SQS:
		nic->sqs_count = mbx.sqs_alloc.qs_count;
		nic->pf_acked = true;
		अवरोध;
	हाल NIC_MBOX_MSG_SNICVF_PTR:
		/* Primary VF: make note of secondary VF's poपूर्णांकer
		 * to be used जबतक packet transmission.
		 */
		nic->snicvf[mbx.nicvf.sqs_id] =
			(काष्ठा nicvf *)mbx.nicvf.nicvf;
		nic->pf_acked = true;
		अवरोध;
	हाल NIC_MBOX_MSG_PNICVF_PTR:
		/* Secondary VF/Qset: make note of primary VF's poपूर्णांकer
		 * to be used जबतक packet reception, to hanकरोver packet
		 * to primary VF's netdev.
		 */
		nic->pnicvf = (काष्ठा nicvf *)mbx.nicvf.nicvf;
		nic->pf_acked = true;
		अवरोध;
	हाल NIC_MBOX_MSG_PFC:
		nic->pfc.स्वतःneg = mbx.pfc.स्वतःneg;
		nic->pfc.fc_rx = mbx.pfc.fc_rx;
		nic->pfc.fc_tx = mbx.pfc.fc_tx;
		nic->pf_acked = true;
		अवरोध;
	शेष:
		netdev_err(nic->netdev,
			   "Invalid message from PF, msg 0x%x\n", mbx.msg.msg);
		अवरोध;
	पूर्ण
	nicvf_clear_पूर्णांकr(nic, NICVF_INTR_MBOX, 0);
पूर्ण

अटल पूर्णांक nicvf_hw_set_mac_addr(काष्ठा nicvf *nic, काष्ठा net_device *netdev)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.mac.msg = NIC_MBOX_MSG_SET_MAC;
	mbx.mac.vf_id = nic->vf_id;
	ether_addr_copy(mbx.mac.mac_addr, netdev->dev_addr);

	वापस nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

अटल व्योम nicvf_config_cpi(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.cpi_cfg.msg = NIC_MBOX_MSG_CPI_CFG;
	mbx.cpi_cfg.vf_id = nic->vf_id;
	mbx.cpi_cfg.cpi_alg = nic->cpi_alg;
	mbx.cpi_cfg.rq_cnt = nic->qs->rq_cnt;

	nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

अटल व्योम nicvf_get_rss_size(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.rss_size.msg = NIC_MBOX_MSG_RSS_SIZE;
	mbx.rss_size.vf_id = nic->vf_id;
	nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

व्योम nicvf_config_rss(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	काष्ठा nicvf_rss_info *rss = &nic->rss_info;
	पूर्णांक ind_tbl_len = rss->rss_size;
	पूर्णांक i, nextq = 0;

	mbx.rss_cfg.vf_id = nic->vf_id;
	mbx.rss_cfg.hash_bits = rss->hash_bits;
	जबतक (ind_tbl_len) अणु
		mbx.rss_cfg.tbl_offset = nextq;
		mbx.rss_cfg.tbl_len = min(ind_tbl_len,
					       RSS_IND_TBL_LEN_PER_MBX_MSG);
		mbx.rss_cfg.msg = mbx.rss_cfg.tbl_offset ?
			  NIC_MBOX_MSG_RSS_CFG_CONT : NIC_MBOX_MSG_RSS_CFG;

		क्रम (i = 0; i < mbx.rss_cfg.tbl_len; i++)
			mbx.rss_cfg.ind_tbl[i] = rss->ind_tbl[nextq++];

		nicvf_send_msg_to_pf(nic, &mbx);

		ind_tbl_len -= mbx.rss_cfg.tbl_len;
	पूर्ण
पूर्ण

व्योम nicvf_set_rss_key(काष्ठा nicvf *nic)
अणु
	काष्ठा nicvf_rss_info *rss = &nic->rss_info;
	u64 key_addr = NIC_VNIC_RSS_KEY_0_4;
	पूर्णांक idx;

	क्रम (idx = 0; idx < RSS_HASH_KEY_SIZE; idx++) अणु
		nicvf_reg_ग_लिखो(nic, key_addr, rss->key[idx]);
		key_addr += माप(u64);
	पूर्ण
पूर्ण

अटल पूर्णांक nicvf_rss_init(काष्ठा nicvf *nic)
अणु
	काष्ठा nicvf_rss_info *rss = &nic->rss_info;
	पूर्णांक idx;

	nicvf_get_rss_size(nic);

	अगर (cpi_alg != CPI_ALG_NONE) अणु
		rss->enable = false;
		rss->hash_bits = 0;
		वापस 0;
	पूर्ण

	rss->enable = true;

	netdev_rss_key_fill(rss->key, RSS_HASH_KEY_SIZE * माप(u64));
	nicvf_set_rss_key(nic);

	rss->cfg = RSS_IP_HASH_ENA | RSS_TCP_HASH_ENA | RSS_UDP_HASH_ENA;
	nicvf_reg_ग_लिखो(nic, NIC_VNIC_RSS_CFG, rss->cfg);

	rss->hash_bits =  ilog2(roundकरोwn_घात_of_two(rss->rss_size));

	क्रम (idx = 0; idx < rss->rss_size; idx++)
		rss->ind_tbl[idx] = ethtool_rxfh_indir_शेष(idx,
							       nic->rx_queues);
	nicvf_config_rss(nic);
	वापस 1;
पूर्ण

/* Request PF to allocate additional Qsets */
अटल व्योम nicvf_request_sqs(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	पूर्णांक sqs;
	पूर्णांक sqs_count = nic->sqs_count;
	पूर्णांक rx_queues = 0, tx_queues = 0;

	/* Only primary VF should request */
	अगर (nic->sqs_mode ||  !nic->sqs_count)
		वापस;

	mbx.sqs_alloc.msg = NIC_MBOX_MSG_ALLOC_SQS;
	mbx.sqs_alloc.vf_id = nic->vf_id;
	mbx.sqs_alloc.qs_count = nic->sqs_count;
	अगर (nicvf_send_msg_to_pf(nic, &mbx)) अणु
		/* No response from PF */
		nic->sqs_count = 0;
		वापस;
	पूर्ण

	/* Return अगर no Secondary Qsets available */
	अगर (!nic->sqs_count)
		वापस;

	अगर (nic->rx_queues > MAX_RCV_QUEUES_PER_QS)
		rx_queues = nic->rx_queues - MAX_RCV_QUEUES_PER_QS;

	tx_queues = nic->tx_queues + nic->xdp_tx_queues;
	अगर (tx_queues > MAX_SND_QUEUES_PER_QS)
		tx_queues = tx_queues - MAX_SND_QUEUES_PER_QS;

	/* Set no of Rx/Tx queues in each of the SQsets */
	क्रम (sqs = 0; sqs < nic->sqs_count; sqs++) अणु
		mbx.nicvf.msg = NIC_MBOX_MSG_SNICVF_PTR;
		mbx.nicvf.vf_id = nic->vf_id;
		mbx.nicvf.sqs_id = sqs;
		nicvf_send_msg_to_pf(nic, &mbx);

		nic->snicvf[sqs]->sqs_id = sqs;
		अगर (rx_queues > MAX_RCV_QUEUES_PER_QS) अणु
			nic->snicvf[sqs]->qs->rq_cnt = MAX_RCV_QUEUES_PER_QS;
			rx_queues -= MAX_RCV_QUEUES_PER_QS;
		पूर्ण अन्यथा अणु
			nic->snicvf[sqs]->qs->rq_cnt = rx_queues;
			rx_queues = 0;
		पूर्ण

		अगर (tx_queues > MAX_SND_QUEUES_PER_QS) अणु
			nic->snicvf[sqs]->qs->sq_cnt = MAX_SND_QUEUES_PER_QS;
			tx_queues -= MAX_SND_QUEUES_PER_QS;
		पूर्ण अन्यथा अणु
			nic->snicvf[sqs]->qs->sq_cnt = tx_queues;
			tx_queues = 0;
		पूर्ण

		nic->snicvf[sqs]->qs->cq_cnt =
		max(nic->snicvf[sqs]->qs->rq_cnt, nic->snicvf[sqs]->qs->sq_cnt);

		/* Initialize secondary Qset's queues and its पूर्णांकerrupts */
		nicvf_खोलो(nic->snicvf[sqs]->netdev);
	पूर्ण

	/* Update stack with actual Rx/Tx queue count allocated */
	अगर (sqs_count != nic->sqs_count)
		nicvf_set_real_num_queues(nic->netdev,
					  nic->tx_queues, nic->rx_queues);
पूर्ण

/* Send this Qset's nicvf poपूर्णांकer to PF.
 * PF पूर्णांकurn sends primary VF's nicvf काष्ठा to secondary Qsets/VFs
 * so that packets received by these Qsets can use primary VF's netdev
 */
अटल व्योम nicvf_send_vf_काष्ठा(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.nicvf.msg = NIC_MBOX_MSG_NICVF_PTR;
	mbx.nicvf.sqs_mode = nic->sqs_mode;
	mbx.nicvf.nicvf = (u64)nic;
	nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

अटल व्योम nicvf_get_primary_vf_काष्ठा(काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.nicvf.msg = NIC_MBOX_MSG_PNICVF_PTR;
	nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

पूर्णांक nicvf_set_real_num_queues(काष्ठा net_device *netdev,
			      पूर्णांक tx_queues, पूर्णांक rx_queues)
अणु
	पूर्णांक err = 0;

	err = netअगर_set_real_num_tx_queues(netdev, tx_queues);
	अगर (err) अणु
		netdev_err(netdev,
			   "Failed to set no of Tx queues: %d\n", tx_queues);
		वापस err;
	पूर्ण

	err = netअगर_set_real_num_rx_queues(netdev, rx_queues);
	अगर (err)
		netdev_err(netdev,
			   "Failed to set no of Rx queues: %d\n", rx_queues);
	वापस err;
पूर्ण

अटल पूर्णांक nicvf_init_resources(काष्ठा nicvf *nic)
अणु
	पूर्णांक err;

	/* Enable Qset */
	nicvf_qset_config(nic, true);

	/* Initialize queues and HW क्रम data transfer */
	err = nicvf_config_data_transfer(nic, true);
	अगर (err) अणु
		netdev_err(nic->netdev,
			   "Failed to alloc/config VF's QSet resources\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool nicvf_xdp_rx(काष्ठा nicvf *nic, काष्ठा bpf_prog *prog,
				काष्ठा cqe_rx_t *cqe_rx, काष्ठा snd_queue *sq,
				काष्ठा rcv_queue *rq, काष्ठा sk_buff **skb)
अणु
	अचिन्हित अक्षर *hard_start, *data;
	काष्ठा xdp_buff xdp;
	काष्ठा page *page;
	u32 action;
	u16 len, offset = 0;
	u64 dma_addr, cpu_addr;
	व्योम *orig_data;

	/* Retrieve packet buffer's DMA address and length */
	len = *((u16 *)((व्योम *)cqe_rx + (3 * माप(u64))));
	dma_addr = *((u64 *)((व्योम *)cqe_rx + (7 * माप(u64))));

	cpu_addr = nicvf_iova_to_phys(nic, dma_addr);
	अगर (!cpu_addr)
		वापस false;
	cpu_addr = (u64)phys_to_virt(cpu_addr);
	page = virt_to_page((व्योम *)cpu_addr);

	xdp_init_buff(&xdp, RCV_FRAG_LEN + XDP_PACKET_HEADROOM,
		      &rq->xdp_rxq);
	hard_start = page_address(page);
	data = (अचिन्हित अक्षर *)cpu_addr;
	xdp_prepare_buff(&xdp, hard_start, data - hard_start, len, false);
	orig_data = xdp.data;

	rcu_पढ़ो_lock();
	action = bpf_prog_run_xdp(prog, &xdp);
	rcu_पढ़ो_unlock();

	len = xdp.data_end - xdp.data;
	/* Check अगर XDP program has changed headers */
	अगर (orig_data != xdp.data) अणु
		offset = orig_data - xdp.data;
		dma_addr -= offset;
	पूर्ण

	चयन (action) अणु
	हाल XDP_PASS:
		/* Check अगर it's a recycled page, अगर not
		 * unmap the DMA mapping.
		 *
		 * Recycled page holds an extra reference.
		 */
		अगर (page_ref_count(page) == 1) अणु
			dma_addr &= PAGE_MASK;
			dma_unmap_page_attrs(&nic->pdev->dev, dma_addr,
					     RCV_FRAG_LEN + XDP_PACKET_HEADROOM,
					     DMA_FROM_DEVICE,
					     DMA_ATTR_SKIP_CPU_SYNC);
		पूर्ण

		/* Build SKB and pass on packet to network stack */
		*skb = build_skb(xdp.data,
				 RCV_FRAG_LEN - cqe_rx->align_pad + offset);
		अगर (!*skb)
			put_page(page);
		अन्यथा
			skb_put(*skb, len);
		वापस false;
	हाल XDP_TX:
		nicvf_xdp_sq_append_pkt(nic, sq, (u64)xdp.data, dma_addr, len);
		वापस true;
	शेष:
		bpf_warn_invalid_xdp_action(action);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(nic->netdev, prog, action);
		fallthrough;
	हाल XDP_DROP:
		/* Check अगर it's a recycled page, अगर not
		 * unmap the DMA mapping.
		 *
		 * Recycled page holds an extra reference.
		 */
		अगर (page_ref_count(page) == 1) अणु
			dma_addr &= PAGE_MASK;
			dma_unmap_page_attrs(&nic->pdev->dev, dma_addr,
					     RCV_FRAG_LEN + XDP_PACKET_HEADROOM,
					     DMA_FROM_DEVICE,
					     DMA_ATTR_SKIP_CPU_SYNC);
		पूर्ण
		put_page(page);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम nicvf_snd_ptp_handler(काष्ठा net_device *netdev,
				  काष्ठा cqe_send_t *cqe_tx)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा skb_shared_hwtstamps ts;
	u64 ns;

	nic = nic->pnicvf;

	/* Sync क्रम 'ptp_skb' */
	smp_rmb();

	/* New बारtamp request can be queued now */
	atomic_set(&nic->tx_ptp_skbs, 0);

	/* Check क्रम बारtamp requested skb */
	अगर (!nic->ptp_skb)
		वापस;

	/* Check अगर बारtamping is समयकरोut, which is set to 10us */
	अगर (cqe_tx->send_status == CQ_TX_ERROP_TSTMP_TIMEOUT ||
	    cqe_tx->send_status == CQ_TX_ERROP_TSTMP_CONFLICT)
		जाओ no_tstamp;

	/* Get the बारtamp */
	स_रखो(&ts, 0, माप(ts));
	ns = cavium_ptp_tstamp2समय(nic->ptp_घड़ी, cqe_tx->ptp_बारtamp);
	ts.hwtstamp = ns_to_kसमय(ns);
	skb_tstamp_tx(nic->ptp_skb, &ts);

no_tstamp:
	/* Free the original skb */
	dev_kमुक्त_skb_any(nic->ptp_skb);
	nic->ptp_skb = शून्य;
	/* Sync 'ptp_skb' */
	smp_wmb();
पूर्ण

अटल व्योम nicvf_snd_pkt_handler(काष्ठा net_device *netdev,
				  काष्ठा cqe_send_t *cqe_tx,
				  पूर्णांक budget, पूर्णांक *subdesc_cnt,
				  अचिन्हित पूर्णांक *tx_pkts, अचिन्हित पूर्णांक *tx_bytes)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा page *page;
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा snd_queue *sq;
	काष्ठा sq_hdr_subdesc *hdr;
	काष्ठा sq_hdr_subdesc *tso_sqe;

	sq = &nic->qs->sq[cqe_tx->sq_idx];

	hdr = (काष्ठा sq_hdr_subdesc *)GET_SQ_DESC(sq, cqe_tx->sqe_ptr);
	अगर (hdr->subdesc_type != SQ_DESC_TYPE_HEADER)
		वापस;

	/* Check क्रम errors */
	अगर (cqe_tx->send_status)
		nicvf_check_cqe_tx_errs(nic->pnicvf, cqe_tx);

	/* Is this a XDP designated Tx queue */
	अगर (sq->is_xdp) अणु
		page = (काष्ठा page *)sq->xdp_page[cqe_tx->sqe_ptr];
		/* Check अगर it's recycled page or अन्यथा unmap DMA mapping */
		अगर (page && (page_ref_count(page) == 1))
			nicvf_unmap_sndq_buffers(nic, sq, cqe_tx->sqe_ptr,
						 hdr->subdesc_cnt);

		/* Release page reference क्रम recycling */
		अगर (page)
			put_page(page);
		sq->xdp_page[cqe_tx->sqe_ptr] = (u64)शून्य;
		*subdesc_cnt += hdr->subdesc_cnt + 1;
		वापस;
	पूर्ण

	skb = (काष्ठा sk_buff *)sq->skbuff[cqe_tx->sqe_ptr];
	अगर (skb) अणु
		/* Check क्रम dummy descriptor used क्रम HW TSO offload on 88xx */
		अगर (hdr->करोnt_send) अणु
			/* Get actual TSO descriptors and मुक्त them */
			tso_sqe =
			 (काष्ठा sq_hdr_subdesc *)GET_SQ_DESC(sq, hdr->rsvd2);
			nicvf_unmap_sndq_buffers(nic, sq, hdr->rsvd2,
						 tso_sqe->subdesc_cnt);
			*subdesc_cnt += tso_sqe->subdesc_cnt + 1;
		पूर्ण अन्यथा अणु
			nicvf_unmap_sndq_buffers(nic, sq, cqe_tx->sqe_ptr,
						 hdr->subdesc_cnt);
		पूर्ण
		*subdesc_cnt += hdr->subdesc_cnt + 1;
		prefetch(skb);
		(*tx_pkts)++;
		*tx_bytes += skb->len;
		/* If बारtamp is requested क्रम this skb, करोn't मुक्त it */
		अगर (skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS &&
		    !nic->pnicvf->ptp_skb)
			nic->pnicvf->ptp_skb = skb;
		अन्यथा
			napi_consume_skb(skb, budget);
		sq->skbuff[cqe_tx->sqe_ptr] = (u64)शून्य;
	पूर्ण अन्यथा अणु
		/* In हाल of SW TSO on 88xx, only last segment will have
		 * a SKB attached, so just मुक्त SQEs here.
		 */
		अगर (!nic->hw_tso)
			*subdesc_cnt += hdr->subdesc_cnt + 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम nicvf_set_rxhash(काष्ठा net_device *netdev,
				    काष्ठा cqe_rx_t *cqe_rx,
				    काष्ठा sk_buff *skb)
अणु
	u8 hash_type;
	u32 hash;

	अगर (!(netdev->features & NETIF_F_RXHASH))
		वापस;

	चयन (cqe_rx->rss_alg) अणु
	हाल RSS_ALG_TCP_IP:
	हाल RSS_ALG_UDP_IP:
		hash_type = PKT_HASH_TYPE_L4;
		hash = cqe_rx->rss_tag;
		अवरोध;
	हाल RSS_ALG_IP:
		hash_type = PKT_HASH_TYPE_L3;
		hash = cqe_rx->rss_tag;
		अवरोध;
	शेष:
		hash_type = PKT_HASH_TYPE_NONE;
		hash = 0;
	पूर्ण

	skb_set_hash(skb, hash, hash_type);
पूर्ण

अटल अंतरभूत व्योम nicvf_set_rxtstamp(काष्ठा nicvf *nic, काष्ठा sk_buff *skb)
अणु
	u64 ns;

	अगर (!nic->ptp_घड़ी || !nic->hw_rx_tstamp)
		वापस;

	/* The first 8 bytes is the बारtamp */
	ns = cavium_ptp_tstamp2समय(nic->ptp_घड़ी,
				    be64_to_cpu(*(__be64 *)skb->data));
	skb_hwtstamps(skb)->hwtstamp = ns_to_kसमय(ns);

	__skb_pull(skb, 8);
पूर्ण

अटल व्योम nicvf_rcv_pkt_handler(काष्ठा net_device *netdev,
				  काष्ठा napi_काष्ठा *napi,
				  काष्ठा cqe_rx_t *cqe_rx,
				  काष्ठा snd_queue *sq, काष्ठा rcv_queue *rq)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा nicvf *snic = nic;
	पूर्णांक err = 0;
	पूर्णांक rq_idx;

	rq_idx = nicvf_netdev_qidx(nic, cqe_rx->rq_idx);

	अगर (nic->sqs_mode) अणु
		/* Use primary VF's 'nicvf' काष्ठा */
		nic = nic->pnicvf;
		netdev = nic->netdev;
	पूर्ण

	/* Check क्रम errors */
	अगर (cqe_rx->err_level || cqe_rx->err_opcode) अणु
		err = nicvf_check_cqe_rx_errs(nic, cqe_rx);
		अगर (err && !cqe_rx->rb_cnt)
			वापस;
	पूर्ण

	/* For XDP, ignore pkts spanning multiple pages */
	अगर (nic->xdp_prog && (cqe_rx->rb_cnt == 1)) अणु
		/* Packet consumed by XDP */
		अगर (nicvf_xdp_rx(snic, nic->xdp_prog, cqe_rx, sq, rq, &skb))
			वापस;
	पूर्ण अन्यथा अणु
		skb = nicvf_get_rcv_skb(snic, cqe_rx,
					nic->xdp_prog ? true : false);
	पूर्ण

	अगर (!skb)
		वापस;

	अगर (netअगर_msg_pktdata(nic)) अणु
		netdev_info(nic->netdev, "skb 0x%p, len=%d\n", skb, skb->len);
		prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1,
			       skb->data, skb->len, true);
	पूर्ण

	/* If error packet, drop it here */
	अगर (err) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	nicvf_set_rxtstamp(nic, skb);
	nicvf_set_rxhash(netdev, cqe_rx, skb);

	skb_record_rx_queue(skb, rq_idx);
	अगर (netdev->hw_features & NETIF_F_RXCSUM) अणु
		/* HW by शेष verअगरies TCP/UDP/SCTP checksums */
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण अन्यथा अणु
		skb_checksum_none_निश्चित(skb);
	पूर्ण

	skb->protocol = eth_type_trans(skb, netdev);

	/* Check क्रम stripped VLAN */
	अगर (cqe_rx->vlan_found && cqe_rx->vlan_stripped)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       ntohs((__क्रमce __be16)cqe_rx->vlan_tci));

	अगर (napi && (netdev->features & NETIF_F_GRO))
		napi_gro_receive(napi, skb);
	अन्यथा
		netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक nicvf_cq_पूर्णांकr_handler(काष्ठा net_device *netdev, u8 cq_idx,
				 काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक processed_cqe, work_करोne = 0, tx_करोne = 0;
	पूर्णांक cqe_count, cqe_head;
	पूर्णांक subdesc_cnt = 0;
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा queue_set *qs = nic->qs;
	काष्ठा cmp_queue *cq = &qs->cq[cq_idx];
	काष्ठा cqe_rx_t *cq_desc;
	काष्ठा netdev_queue *txq;
	काष्ठा snd_queue *sq = &qs->sq[cq_idx];
	काष्ठा rcv_queue *rq = &qs->rq[cq_idx];
	अचिन्हित पूर्णांक tx_pkts = 0, tx_bytes = 0, txq_idx;

	spin_lock_bh(&cq->lock);
loop:
	processed_cqe = 0;
	/* Get no of valid CQ entries to process */
	cqe_count = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_STATUS, cq_idx);
	cqe_count &= CQ_CQE_COUNT;
	अगर (!cqe_count)
		जाओ करोne;

	/* Get head of the valid CQ entries */
	cqe_head = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_HEAD, cq_idx) >> 9;
	cqe_head &= 0xFFFF;

	जबतक (processed_cqe < cqe_count) अणु
		/* Get the CQ descriptor */
		cq_desc = (काष्ठा cqe_rx_t *)GET_CQ_DESC(cq, cqe_head);
		cqe_head++;
		cqe_head &= (cq->dmem.q_len - 1);
		/* Initiate prefetch क्रम next descriptor */
		prefetch((काष्ठा cqe_rx_t *)GET_CQ_DESC(cq, cqe_head));

		अगर ((work_करोne >= budget) && napi &&
		    (cq_desc->cqe_type != CQE_TYPE_SEND)) अणु
			अवरोध;
		पूर्ण

		चयन (cq_desc->cqe_type) अणु
		हाल CQE_TYPE_RX:
			nicvf_rcv_pkt_handler(netdev, napi, cq_desc, sq, rq);
			work_करोne++;
		अवरोध;
		हाल CQE_TYPE_SEND:
			nicvf_snd_pkt_handler(netdev, (व्योम *)cq_desc,
					      budget, &subdesc_cnt,
					      &tx_pkts, &tx_bytes);
			tx_करोne++;
		अवरोध;
		हाल CQE_TYPE_SEND_PTP:
			nicvf_snd_ptp_handler(netdev, (व्योम *)cq_desc);
		अवरोध;
		हाल CQE_TYPE_INVALID:
		हाल CQE_TYPE_RX_SPLIT:
		हाल CQE_TYPE_RX_TCP:
			/* Ignore क्रम now */
		अवरोध;
		पूर्ण
		processed_cqe++;
	पूर्ण

	/* Ring करोorbell to inक्रमm H/W to reuse processed CQEs */
	nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_DOOR,
			      cq_idx, processed_cqe);

	अगर ((work_करोne < budget) && napi)
		जाओ loop;

करोne:
	/* Update SQ's descriptor मुक्त count */
	अगर (subdesc_cnt)
		nicvf_put_sq_desc(sq, subdesc_cnt);

	txq_idx = nicvf_netdev_qidx(nic, cq_idx);
	/* Handle XDP TX queues */
	अगर (nic->pnicvf->xdp_prog) अणु
		अगर (txq_idx < nic->pnicvf->xdp_tx_queues) अणु
			nicvf_xdp_sq_करोorbell(nic, sq, cq_idx);
			जाओ out;
		पूर्ण
		nic = nic->pnicvf;
		txq_idx -= nic->pnicvf->xdp_tx_queues;
	पूर्ण

	/* Wakeup TXQ अगर its stopped earlier due to SQ full */
	अगर (tx_करोne ||
	    (atomic_पढ़ो(&sq->मुक्त_cnt) >= MIN_SQ_DESC_PER_PKT_XMIT)) अणु
		netdev = nic->pnicvf->netdev;
		txq = netdev_get_tx_queue(netdev, txq_idx);
		अगर (tx_pkts)
			netdev_tx_completed_queue(txq, tx_pkts, tx_bytes);

		/* To पढ़ो updated queue and carrier status */
		smp_mb();
		अगर (netअगर_tx_queue_stopped(txq) && netअगर_carrier_ok(netdev)) अणु
			netअगर_tx_wake_queue(txq);
			nic = nic->pnicvf;
			this_cpu_inc(nic->drv_stats->txq_wake);
			netअगर_warn(nic, tx_err, netdev,
				   "Transmit queue wakeup SQ%d\n", txq_idx);
		पूर्ण
	पूर्ण

out:
	spin_unlock_bh(&cq->lock);
	वापस work_करोne;
पूर्ण

अटल पूर्णांक nicvf_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	u64  cq_head;
	पूर्णांक  work_करोne = 0;
	काष्ठा net_device *netdev = napi->dev;
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा nicvf_cq_poll *cq;

	cq = container_of(napi, काष्ठा nicvf_cq_poll, napi);
	work_करोne = nicvf_cq_पूर्णांकr_handler(netdev, cq->cq_idx, napi, budget);

	अगर (work_करोne < budget) अणु
		/* Slow packet rate, निकास polling */
		napi_complete_करोne(napi, work_करोne);
		/* Re-enable पूर्णांकerrupts */
		cq_head = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_HEAD,
					       cq->cq_idx);
		nicvf_clear_पूर्णांकr(nic, NICVF_INTR_CQ, cq->cq_idx);
		nicvf_queue_reg_ग_लिखो(nic, NIC_QSET_CQ_0_7_HEAD,
				      cq->cq_idx, cq_head);
		nicvf_enable_पूर्णांकr(nic, NICVF_INTR_CQ, cq->cq_idx);
	पूर्ण
	वापस work_करोne;
पूर्ण

/* Qset error पूर्णांकerrupt handler
 *
 * As of now only CQ errors are handled
 */
अटल व्योम nicvf_handle_qs_err(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा nicvf *nic = from_tasklet(nic, t, qs_err_task);
	काष्ठा queue_set *qs = nic->qs;
	पूर्णांक qidx;
	u64 status;

	netअगर_tx_disable(nic->netdev);

	/* Check अगर it is CQ err */
	क्रम (qidx = 0; qidx < qs->cq_cnt; qidx++) अणु
		status = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_STATUS,
					      qidx);
		अगर (!(status & CQ_ERR_MASK))
			जारी;
		/* Process alपढ़ोy queued CQEs and reconfig CQ */
		nicvf_disable_पूर्णांकr(nic, NICVF_INTR_CQ, qidx);
		nicvf_sq_disable(nic, qidx);
		nicvf_cq_पूर्णांकr_handler(nic->netdev, qidx, शून्य, 0);
		nicvf_cmp_queue_config(nic, qs, qidx, true);
		nicvf_sq_मुक्त_used_descs(nic->netdev, &qs->sq[qidx], qidx);
		nicvf_sq_enable(nic, &qs->sq[qidx], qidx);

		nicvf_enable_पूर्णांकr(nic, NICVF_INTR_CQ, qidx);
	पूर्ण

	netअगर_tx_start_all_queues(nic->netdev);
	/* Re-enable Qset error पूर्णांकerrupt */
	nicvf_enable_पूर्णांकr(nic, NICVF_INTR_QS_ERR, 0);
पूर्ण

अटल व्योम nicvf_dump_पूर्णांकr_status(काष्ठा nicvf *nic)
अणु
	netअगर_info(nic, पूर्णांकr, nic->netdev, "interrupt status 0x%llx\n",
		   nicvf_reg_पढ़ो(nic, NIC_VF_INT));
पूर्ण

अटल irqवापस_t nicvf_misc_पूर्णांकr_handler(पूर्णांक irq, व्योम *nicvf_irq)
अणु
	काष्ठा nicvf *nic = (काष्ठा nicvf *)nicvf_irq;
	u64 पूर्णांकr;

	nicvf_dump_पूर्णांकr_status(nic);

	पूर्णांकr = nicvf_reg_पढ़ो(nic, NIC_VF_INT);
	/* Check क्रम spurious पूर्णांकerrupt */
	अगर (!(पूर्णांकr & NICVF_INTR_MBOX_MASK))
		वापस IRQ_HANDLED;

	nicvf_handle_mbx_पूर्णांकr(nic);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t nicvf_पूर्णांकr_handler(पूर्णांक irq, व्योम *cq_irq)
अणु
	काष्ठा nicvf_cq_poll *cq_poll = (काष्ठा nicvf_cq_poll *)cq_irq;
	काष्ठा nicvf *nic = cq_poll->nicvf;
	पूर्णांक qidx = cq_poll->cq_idx;

	nicvf_dump_पूर्णांकr_status(nic);

	/* Disable पूर्णांकerrupts */
	nicvf_disable_पूर्णांकr(nic, NICVF_INTR_CQ, qidx);

	/* Schedule NAPI */
	napi_schedule_irqoff(&cq_poll->napi);

	/* Clear पूर्णांकerrupt */
	nicvf_clear_पूर्णांकr(nic, NICVF_INTR_CQ, qidx);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t nicvf_rbdr_पूर्णांकr_handler(पूर्णांक irq, व्योम *nicvf_irq)
अणु
	काष्ठा nicvf *nic = (काष्ठा nicvf *)nicvf_irq;
	u8 qidx;


	nicvf_dump_पूर्णांकr_status(nic);

	/* Disable RBDR पूर्णांकerrupt and schedule softirq */
	क्रम (qidx = 0; qidx < nic->qs->rbdr_cnt; qidx++) अणु
		अगर (!nicvf_is_पूर्णांकr_enabled(nic, NICVF_INTR_RBDR, qidx))
			जारी;
		nicvf_disable_पूर्णांकr(nic, NICVF_INTR_RBDR, qidx);
		tasklet_hi_schedule(&nic->rbdr_task);
		/* Clear पूर्णांकerrupt */
		nicvf_clear_पूर्णांकr(nic, NICVF_INTR_RBDR, qidx);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t nicvf_qs_err_पूर्णांकr_handler(पूर्णांक irq, व्योम *nicvf_irq)
अणु
	काष्ठा nicvf *nic = (काष्ठा nicvf *)nicvf_irq;

	nicvf_dump_पूर्णांकr_status(nic);

	/* Disable Qset err पूर्णांकerrupt and schedule softirq */
	nicvf_disable_पूर्णांकr(nic, NICVF_INTR_QS_ERR, 0);
	tasklet_hi_schedule(&nic->qs_err_task);
	nicvf_clear_पूर्णांकr(nic, NICVF_INTR_QS_ERR, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम nicvf_set_irq_affinity(काष्ठा nicvf *nic)
अणु
	पूर्णांक vec, cpu;

	क्रम (vec = 0; vec < nic->num_vec; vec++) अणु
		अगर (!nic->irq_allocated[vec])
			जारी;

		अगर (!zalloc_cpumask_var(&nic->affinity_mask[vec], GFP_KERNEL))
			वापस;
		 /* CQ पूर्णांकerrupts */
		अगर (vec < NICVF_INTR_ID_SQ)
			/* Leave CPU0 क्रम RBDR and other पूर्णांकerrupts */
			cpu = nicvf_netdev_qidx(nic, vec) + 1;
		अन्यथा
			cpu = 0;

		cpumask_set_cpu(cpumask_local_spपढ़ो(cpu, nic->node),
				nic->affinity_mask[vec]);
		irq_set_affinity_hपूर्णांक(pci_irq_vector(nic->pdev, vec),
				      nic->affinity_mask[vec]);
	पूर्ण
पूर्ण

अटल पूर्णांक nicvf_रेजिस्टर_पूर्णांकerrupts(काष्ठा nicvf *nic)
अणु
	पूर्णांक irq, ret = 0;

	क्रम_each_cq_irq(irq)
		प्र_लिखो(nic->irq_name[irq], "%s-rxtx-%d",
			nic->pnicvf->netdev->name,
			nicvf_netdev_qidx(nic, irq));

	क्रम_each_sq_irq(irq)
		प्र_लिखो(nic->irq_name[irq], "%s-sq-%d",
			nic->pnicvf->netdev->name,
			nicvf_netdev_qidx(nic, irq - NICVF_INTR_ID_SQ));

	क्रम_each_rbdr_irq(irq)
		प्र_लिखो(nic->irq_name[irq], "%s-rbdr-%d",
			nic->pnicvf->netdev->name,
			nic->sqs_mode ? (nic->sqs_id + 1) : 0);

	/* Register CQ पूर्णांकerrupts */
	क्रम (irq = 0; irq < nic->qs->cq_cnt; irq++) अणु
		ret = request_irq(pci_irq_vector(nic->pdev, irq),
				  nicvf_पूर्णांकr_handler,
				  0, nic->irq_name[irq], nic->napi[irq]);
		अगर (ret)
			जाओ err;
		nic->irq_allocated[irq] = true;
	पूर्ण

	/* Register RBDR पूर्णांकerrupt */
	क्रम (irq = NICVF_INTR_ID_RBDR;
	     irq < (NICVF_INTR_ID_RBDR + nic->qs->rbdr_cnt); irq++) अणु
		ret = request_irq(pci_irq_vector(nic->pdev, irq),
				  nicvf_rbdr_पूर्णांकr_handler,
				  0, nic->irq_name[irq], nic);
		अगर (ret)
			जाओ err;
		nic->irq_allocated[irq] = true;
	पूर्ण

	/* Register QS error पूर्णांकerrupt */
	प्र_लिखो(nic->irq_name[NICVF_INTR_ID_QS_ERR], "%s-qset-err-%d",
		nic->pnicvf->netdev->name,
		nic->sqs_mode ? (nic->sqs_id + 1) : 0);
	irq = NICVF_INTR_ID_QS_ERR;
	ret = request_irq(pci_irq_vector(nic->pdev, irq),
			  nicvf_qs_err_पूर्णांकr_handler,
			  0, nic->irq_name[irq], nic);
	अगर (ret)
		जाओ err;

	nic->irq_allocated[irq] = true;

	/* Set IRQ affinities */
	nicvf_set_irq_affinity(nic);

err:
	अगर (ret)
		netdev_err(nic->netdev, "request_irq failed, vector %d\n", irq);

	वापस ret;
पूर्ण

अटल व्योम nicvf_unरेजिस्टर_पूर्णांकerrupts(काष्ठा nicvf *nic)
अणु
	काष्ठा pci_dev *pdev = nic->pdev;
	पूर्णांक irq;

	/* Free रेजिस्टरed पूर्णांकerrupts */
	क्रम (irq = 0; irq < nic->num_vec; irq++) अणु
		अगर (!nic->irq_allocated[irq])
			जारी;

		irq_set_affinity_hपूर्णांक(pci_irq_vector(pdev, irq), शून्य);
		मुक्त_cpumask_var(nic->affinity_mask[irq]);

		अगर (irq < NICVF_INTR_ID_SQ)
			मुक्त_irq(pci_irq_vector(pdev, irq), nic->napi[irq]);
		अन्यथा
			मुक्त_irq(pci_irq_vector(pdev, irq), nic);

		nic->irq_allocated[irq] = false;
	पूर्ण

	/* Disable MSI-X */
	pci_मुक्त_irq_vectors(pdev);
	nic->num_vec = 0;
पूर्ण

/* Initialize MSIX vectors and रेजिस्टर MISC पूर्णांकerrupt.
 * Send READY message to PF to check अगर its alive
 */
अटल पूर्णांक nicvf_रेजिस्टर_misc_पूर्णांकerrupt(काष्ठा nicvf *nic)
अणु
	पूर्णांक ret = 0;
	पूर्णांक irq = NICVF_INTR_ID_MISC;

	/* Return अगर mailbox पूर्णांकerrupt is alपढ़ोy रेजिस्टरed */
	अगर (nic->pdev->msix_enabled)
		वापस 0;

	/* Enable MSI-X */
	nic->num_vec = pci_msix_vec_count(nic->pdev);
	ret = pci_alloc_irq_vectors(nic->pdev, nic->num_vec, nic->num_vec,
				    PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		netdev_err(nic->netdev,
			   "Req for #%d msix vectors failed\n", nic->num_vec);
		वापस 1;
	पूर्ण

	प्र_लिखो(nic->irq_name[irq], "%s Mbox", "NICVF");
	/* Register Misc पूर्णांकerrupt */
	ret = request_irq(pci_irq_vector(nic->pdev, irq),
			  nicvf_misc_पूर्णांकr_handler, 0, nic->irq_name[irq], nic);

	अगर (ret)
		वापस ret;
	nic->irq_allocated[irq] = true;

	/* Enable mailbox पूर्णांकerrupt */
	nicvf_enable_पूर्णांकr(nic, NICVF_INTR_MBOX, 0);

	/* Check अगर VF is able to communicate with PF */
	अगर (!nicvf_check_pf_पढ़ोy(nic)) अणु
		nicvf_disable_पूर्णांकr(nic, NICVF_INTR_MBOX, 0);
		nicvf_unरेजिस्टर_पूर्णांकerrupts(nic);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_tx_t nicvf_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	पूर्णांक qid = skb_get_queue_mapping(skb);
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(netdev, qid);
	काष्ठा nicvf *snic;
	काष्ठा snd_queue *sq;
	पूर्णांक पंचांगp;

	/* Check क्रम minimum packet length */
	अगर (skb->len <= ETH_HLEN) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* In XDP हाल, initial HW tx queues are used क्रम XDP,
	 * but stack's queue mapping starts at '0', so skip the
	 * Tx queues attached to Rx queues क्रम XDP.
	 */
	अगर (nic->xdp_prog)
		qid += nic->xdp_tx_queues;

	snic = nic;
	/* Get secondary Qset's SQ काष्ठाure */
	अगर (qid >= MAX_SND_QUEUES_PER_QS) अणु
		पंचांगp = qid / MAX_SND_QUEUES_PER_QS;
		snic = (काष्ठा nicvf *)nic->snicvf[पंचांगp - 1];
		अगर (!snic) अणु
			netdev_warn(nic->netdev,
				    "Secondary Qset#%d's ptr not initialized\n",
				    पंचांगp - 1);
			dev_kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
		qid = qid % MAX_SND_QUEUES_PER_QS;
	पूर्ण

	sq = &snic->qs->sq[qid];
	अगर (!netअगर_tx_queue_stopped(txq) &&
	    !nicvf_sq_append_skb(snic, sq, skb, qid)) अणु
		netअगर_tx_stop_queue(txq);

		/* Barrier, so that stop_queue visible to other cpus */
		smp_mb();

		/* Check again, inहाल another cpu मुक्तd descriptors */
		अगर (atomic_पढ़ो(&sq->मुक्त_cnt) > MIN_SQ_DESC_PER_PKT_XMIT) अणु
			netअगर_tx_wake_queue(txq);
		पूर्ण अन्यथा अणु
			this_cpu_inc(nic->drv_stats->txq_stop);
			netअगर_warn(nic, tx_err, netdev,
				   "Transmit ring full, stopping SQ%d\n", qid);
		पूर्ण
		वापस NETDEV_TX_BUSY;
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल अंतरभूत व्योम nicvf_मुक्त_cq_poll(काष्ठा nicvf *nic)
अणु
	काष्ठा nicvf_cq_poll *cq_poll;
	पूर्णांक qidx;

	क्रम (qidx = 0; qidx < nic->qs->cq_cnt; qidx++) अणु
		cq_poll = nic->napi[qidx];
		अगर (!cq_poll)
			जारी;
		nic->napi[qidx] = शून्य;
		kमुक्त(cq_poll);
	पूर्ण
पूर्ण

पूर्णांक nicvf_stop(काष्ठा net_device *netdev)
अणु
	पूर्णांक irq, qidx;
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा queue_set *qs = nic->qs;
	काष्ठा nicvf_cq_poll *cq_poll = शून्य;
	जोड़ nic_mbx mbx = अणुपूर्ण;

	/* रुको till all queued set_rx_mode tasks completes */
	अगर (nic->nicvf_rx_mode_wq) अणु
		cancel_delayed_work_sync(&nic->link_change_work);
		drain_workqueue(nic->nicvf_rx_mode_wq);
	पूर्ण

	mbx.msg.msg = NIC_MBOX_MSG_SHUTDOWN;
	nicvf_send_msg_to_pf(nic, &mbx);

	netअगर_carrier_off(netdev);
	netअगर_tx_stop_all_queues(nic->netdev);
	nic->link_up = false;

	/* Tearकरोwn secondary qsets first */
	अगर (!nic->sqs_mode) अणु
		क्रम (qidx = 0; qidx < nic->sqs_count; qidx++) अणु
			अगर (!nic->snicvf[qidx])
				जारी;
			nicvf_stop(nic->snicvf[qidx]->netdev);
			nic->snicvf[qidx] = शून्य;
		पूर्ण
	पूर्ण

	/* Disable RBDR & QS error पूर्णांकerrupts */
	क्रम (qidx = 0; qidx < qs->rbdr_cnt; qidx++) अणु
		nicvf_disable_पूर्णांकr(nic, NICVF_INTR_RBDR, qidx);
		nicvf_clear_पूर्णांकr(nic, NICVF_INTR_RBDR, qidx);
	पूर्ण
	nicvf_disable_पूर्णांकr(nic, NICVF_INTR_QS_ERR, 0);
	nicvf_clear_पूर्णांकr(nic, NICVF_INTR_QS_ERR, 0);

	/* Wait क्रम pending IRQ handlers to finish */
	क्रम (irq = 0; irq < nic->num_vec; irq++)
		synchronize_irq(pci_irq_vector(nic->pdev, irq));

	tasklet_समाप्त(&nic->rbdr_task);
	tasklet_समाप्त(&nic->qs_err_task);
	अगर (nic->rb_work_scheduled)
		cancel_delayed_work_sync(&nic->rbdr_work);

	क्रम (qidx = 0; qidx < nic->qs->cq_cnt; qidx++) अणु
		cq_poll = nic->napi[qidx];
		अगर (!cq_poll)
			जारी;
		napi_synchronize(&cq_poll->napi);
		/* CQ पूर्णांकr is enabled जबतक napi_complete,
		 * so disable it now
		 */
		nicvf_disable_पूर्णांकr(nic, NICVF_INTR_CQ, qidx);
		nicvf_clear_पूर्णांकr(nic, NICVF_INTR_CQ, qidx);
		napi_disable(&cq_poll->napi);
		netअगर_napi_del(&cq_poll->napi);
	पूर्ण

	netअगर_tx_disable(netdev);

	क्रम (qidx = 0; qidx < netdev->num_tx_queues; qidx++)
		netdev_tx_reset_queue(netdev_get_tx_queue(netdev, qidx));

	/* Free resources */
	nicvf_config_data_transfer(nic, false);

	/* Disable HW Qset */
	nicvf_qset_config(nic, false);

	/* disable mailbox पूर्णांकerrupt */
	nicvf_disable_पूर्णांकr(nic, NICVF_INTR_MBOX, 0);

	nicvf_unरेजिस्टर_पूर्णांकerrupts(nic);

	nicvf_मुक्त_cq_poll(nic);

	/* Free any pending SKB saved to receive बारtamp */
	अगर (nic->ptp_skb) अणु
		dev_kमुक्त_skb_any(nic->ptp_skb);
		nic->ptp_skb = शून्य;
	पूर्ण

	/* Clear multiqset info */
	nic->pnicvf = nic;

	वापस 0;
पूर्ण

अटल पूर्णांक nicvf_config_hw_rx_tstamp(काष्ठा nicvf *nic, bool enable)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.ptp.msg = NIC_MBOX_MSG_PTP_CFG;
	mbx.ptp.enable = enable;

	वापस nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

अटल पूर्णांक nicvf_update_hw_max_frs(काष्ठा nicvf *nic, पूर्णांक mtu)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.frs.msg = NIC_MBOX_MSG_SET_MAX_FRS;
	mbx.frs.max_frs = mtu;
	mbx.frs.vf_id = nic->vf_id;

	वापस nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

अटल व्योम nicvf_link_status_check_task(काष्ठा work_काष्ठा *work_arg)
अणु
	काष्ठा nicvf *nic = container_of(work_arg,
					 काष्ठा nicvf,
					 link_change_work.work);
	जोड़ nic_mbx mbx = अणुपूर्ण;
	mbx.msg.msg = NIC_MBOX_MSG_BGX_LINK_CHANGE;
	nicvf_send_msg_to_pf(nic, &mbx);
	queue_delayed_work(nic->nicvf_rx_mode_wq,
			   &nic->link_change_work, 2 * HZ);
पूर्ण

पूर्णांक nicvf_खोलो(काष्ठा net_device *netdev)
अणु
	पूर्णांक cpu, err, qidx;
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा queue_set *qs = nic->qs;
	काष्ठा nicvf_cq_poll *cq_poll = शून्य;

	/* रुको till all queued set_rx_mode tasks completes अगर any */
	अगर (nic->nicvf_rx_mode_wq)
		drain_workqueue(nic->nicvf_rx_mode_wq);

	netअगर_carrier_off(netdev);

	err = nicvf_रेजिस्टर_misc_पूर्णांकerrupt(nic);
	अगर (err)
		वापस err;

	/* Register NAPI handler क्रम processing CQEs */
	क्रम (qidx = 0; qidx < qs->cq_cnt; qidx++) अणु
		cq_poll = kzalloc(माप(*cq_poll), GFP_KERNEL);
		अगर (!cq_poll) अणु
			err = -ENOMEM;
			जाओ napi_del;
		पूर्ण
		cq_poll->cq_idx = qidx;
		cq_poll->nicvf = nic;
		netअगर_napi_add(netdev, &cq_poll->napi, nicvf_poll,
			       NAPI_POLL_WEIGHT);
		napi_enable(&cq_poll->napi);
		nic->napi[qidx] = cq_poll;
	पूर्ण

	/* Check अगर we got MAC address from PF or अन्यथा generate a raकरोm MAC */
	अगर (!nic->sqs_mode && is_zero_ether_addr(netdev->dev_addr)) अणु
		eth_hw_addr_अक्रमom(netdev);
		nicvf_hw_set_mac_addr(nic, netdev);
	पूर्ण

	अगर (nic->set_mac_pending) अणु
		nic->set_mac_pending = false;
		nicvf_hw_set_mac_addr(nic, netdev);
	पूर्ण

	/* Init tasklet क्रम handling Qset err पूर्णांकerrupt */
	tasklet_setup(&nic->qs_err_task, nicvf_handle_qs_err);

	/* Init RBDR tasklet which will refill RBDR */
	tasklet_setup(&nic->rbdr_task, nicvf_rbdr_task);
	INIT_DELAYED_WORK(&nic->rbdr_work, nicvf_rbdr_work);

	/* Configure CPI alorithm */
	nic->cpi_alg = cpi_alg;
	अगर (!nic->sqs_mode)
		nicvf_config_cpi(nic);

	nicvf_request_sqs(nic);
	अगर (nic->sqs_mode)
		nicvf_get_primary_vf_काष्ठा(nic);

	/* Configure PTP बारtamp */
	अगर (nic->ptp_घड़ी)
		nicvf_config_hw_rx_tstamp(nic, nic->hw_rx_tstamp);
	atomic_set(&nic->tx_ptp_skbs, 0);
	nic->ptp_skb = शून्य;

	/* Configure receive side scaling and MTU */
	अगर (!nic->sqs_mode) अणु
		nicvf_rss_init(nic);
		err = nicvf_update_hw_max_frs(nic, netdev->mtu);
		अगर (err)
			जाओ cleanup;

		/* Clear percpu stats */
		क्रम_each_possible_cpu(cpu)
			स_रखो(per_cpu_ptr(nic->drv_stats, cpu), 0,
			       माप(काष्ठा nicvf_drv_stats));
	पूर्ण

	err = nicvf_रेजिस्टर_पूर्णांकerrupts(nic);
	अगर (err)
		जाओ cleanup;

	/* Initialize the queues */
	err = nicvf_init_resources(nic);
	अगर (err)
		जाओ cleanup;

	/* Make sure queue initialization is written */
	wmb();

	nicvf_reg_ग_लिखो(nic, NIC_VF_INT, -1);
	/* Enable Qset err पूर्णांकerrupt */
	nicvf_enable_पूर्णांकr(nic, NICVF_INTR_QS_ERR, 0);

	/* Enable completion queue पूर्णांकerrupt */
	क्रम (qidx = 0; qidx < qs->cq_cnt; qidx++)
		nicvf_enable_पूर्णांकr(nic, NICVF_INTR_CQ, qidx);

	/* Enable RBDR threshold पूर्णांकerrupt */
	क्रम (qidx = 0; qidx < qs->rbdr_cnt; qidx++)
		nicvf_enable_पूर्णांकr(nic, NICVF_INTR_RBDR, qidx);

	/* Send VF config करोne msg to PF */
	nicvf_send_cfg_करोne(nic);

	अगर (nic->nicvf_rx_mode_wq) अणु
		INIT_DELAYED_WORK(&nic->link_change_work,
				  nicvf_link_status_check_task);
		queue_delayed_work(nic->nicvf_rx_mode_wq,
				   &nic->link_change_work, 0);
	पूर्ण

	वापस 0;
cleanup:
	nicvf_disable_पूर्णांकr(nic, NICVF_INTR_MBOX, 0);
	nicvf_unरेजिस्टर_पूर्णांकerrupts(nic);
	tasklet_समाप्त(&nic->qs_err_task);
	tasklet_समाप्त(&nic->rbdr_task);
napi_del:
	क्रम (qidx = 0; qidx < qs->cq_cnt; qidx++) अणु
		cq_poll = nic->napi[qidx];
		अगर (!cq_poll)
			जारी;
		napi_disable(&cq_poll->napi);
		netअगर_napi_del(&cq_poll->napi);
	पूर्ण
	nicvf_मुक्त_cq_poll(nic);
	वापस err;
पूर्ण

अटल पूर्णांक nicvf_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	पूर्णांक orig_mtu = netdev->mtu;

	/* For now just support only the usual MTU sized frames,
	 * plus some headroom क्रम VLAN, QinQ.
	 */
	अगर (nic->xdp_prog && new_mtu > MAX_XDP_MTU) अणु
		netdev_warn(netdev, "Jumbo frames not yet supported with XDP, current MTU %d.\n",
			    netdev->mtu);
		वापस -EINVAL;
	पूर्ण

	netdev->mtu = new_mtu;

	अगर (!netअगर_running(netdev))
		वापस 0;

	अगर (nicvf_update_hw_max_frs(nic, new_mtu)) अणु
		netdev->mtu = orig_mtu;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nicvf_set_mac_address(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा nicvf *nic = netdev_priv(netdev);

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);

	अगर (nic->pdev->msix_enabled) अणु
		अगर (nicvf_hw_set_mac_addr(nic, netdev))
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		nic->set_mac_pending = true;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nicvf_update_lmac_stats(काष्ठा nicvf *nic)
अणु
	पूर्णांक stat = 0;
	जोड़ nic_mbx mbx = अणुपूर्ण;

	अगर (!netअगर_running(nic->netdev))
		वापस;

	mbx.bgx_stats.msg = NIC_MBOX_MSG_BGX_STATS;
	mbx.bgx_stats.vf_id = nic->vf_id;
	/* Rx stats */
	mbx.bgx_stats.rx = 1;
	जबतक (stat < BGX_RX_STATS_COUNT) अणु
		mbx.bgx_stats.idx = stat;
		अगर (nicvf_send_msg_to_pf(nic, &mbx))
			वापस;
		stat++;
	पूर्ण

	stat = 0;

	/* Tx stats */
	mbx.bgx_stats.rx = 0;
	जबतक (stat < BGX_TX_STATS_COUNT) अणु
		mbx.bgx_stats.idx = stat;
		अगर (nicvf_send_msg_to_pf(nic, &mbx))
			वापस;
		stat++;
	पूर्ण
पूर्ण

व्योम nicvf_update_stats(काष्ठा nicvf *nic)
अणु
	पूर्णांक qidx, cpu;
	u64 पंचांगp_stats = 0;
	काष्ठा nicvf_hw_stats *stats = &nic->hw_stats;
	काष्ठा nicvf_drv_stats *drv_stats;
	काष्ठा queue_set *qs = nic->qs;

#घोषणा GET_RX_STATS(reg) \
	nicvf_reg_पढ़ो(nic, NIC_VNIC_RX_STAT_0_13 | (reg << 3))
#घोषणा GET_TX_STATS(reg) \
	nicvf_reg_पढ़ो(nic, NIC_VNIC_TX_STAT_0_4 | (reg << 3))

	stats->rx_bytes = GET_RX_STATS(RX_OCTS);
	stats->rx_ucast_frames = GET_RX_STATS(RX_UCAST);
	stats->rx_bcast_frames = GET_RX_STATS(RX_BCAST);
	stats->rx_mcast_frames = GET_RX_STATS(RX_MCAST);
	stats->rx_fcs_errors = GET_RX_STATS(RX_FCS);
	stats->rx_l2_errors = GET_RX_STATS(RX_L2ERR);
	stats->rx_drop_red = GET_RX_STATS(RX_RED);
	stats->rx_drop_red_bytes = GET_RX_STATS(RX_RED_OCTS);
	stats->rx_drop_overrun = GET_RX_STATS(RX_ORUN);
	stats->rx_drop_overrun_bytes = GET_RX_STATS(RX_ORUN_OCTS);
	stats->rx_drop_bcast = GET_RX_STATS(RX_DRP_BCAST);
	stats->rx_drop_mcast = GET_RX_STATS(RX_DRP_MCAST);
	stats->rx_drop_l3_bcast = GET_RX_STATS(RX_DRP_L3BCAST);
	stats->rx_drop_l3_mcast = GET_RX_STATS(RX_DRP_L3MCAST);

	stats->tx_bytes = GET_TX_STATS(TX_OCTS);
	stats->tx_ucast_frames = GET_TX_STATS(TX_UCAST);
	stats->tx_bcast_frames = GET_TX_STATS(TX_BCAST);
	stats->tx_mcast_frames = GET_TX_STATS(TX_MCAST);
	stats->tx_drops = GET_TX_STATS(TX_DROP);

	/* On T88 pass 2.0, the dummy SQE added क्रम TSO notअगरication
	 * via CQE has 'dont_send' set. Hence HW drops the pkt poपूर्णांकed
	 * poपूर्णांकed by dummy SQE and results in tx_drops counter being
	 * incremented. Subtracting it from tx_tso counter will give
	 * exact tx_drops counter.
	 */
	अगर (nic->t88 && nic->hw_tso) अणु
		क्रम_each_possible_cpu(cpu) अणु
			drv_stats = per_cpu_ptr(nic->drv_stats, cpu);
			पंचांगp_stats += drv_stats->tx_tso;
		पूर्ण
		stats->tx_drops = पंचांगp_stats - stats->tx_drops;
	पूर्ण
	stats->tx_frames = stats->tx_ucast_frames +
			   stats->tx_bcast_frames +
			   stats->tx_mcast_frames;
	stats->rx_frames = stats->rx_ucast_frames +
			   stats->rx_bcast_frames +
			   stats->rx_mcast_frames;
	stats->rx_drops = stats->rx_drop_red +
			  stats->rx_drop_overrun;

	/* Update RQ and SQ stats */
	क्रम (qidx = 0; qidx < qs->rq_cnt; qidx++)
		nicvf_update_rq_stats(nic, qidx);
	क्रम (qidx = 0; qidx < qs->sq_cnt; qidx++)
		nicvf_update_sq_stats(nic, qidx);
पूर्ण

अटल व्योम nicvf_get_stats64(काष्ठा net_device *netdev,
			      काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा nicvf_hw_stats *hw_stats = &nic->hw_stats;

	nicvf_update_stats(nic);

	stats->rx_bytes = hw_stats->rx_bytes;
	stats->rx_packets = hw_stats->rx_frames;
	stats->rx_dropped = hw_stats->rx_drops;
	stats->multicast = hw_stats->rx_mcast_frames;

	stats->tx_bytes = hw_stats->tx_bytes;
	stats->tx_packets = hw_stats->tx_frames;
	stats->tx_dropped = hw_stats->tx_drops;

पूर्ण

अटल व्योम nicvf_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);

	netअगर_warn(nic, tx_err, dev, "Transmit timed out, resetting\n");

	this_cpu_inc(nic->drv_stats->tx_समयout);
	schedule_work(&nic->reset_task);
पूर्ण

अटल व्योम nicvf_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nicvf *nic;

	nic = container_of(work, काष्ठा nicvf, reset_task);

	अगर (!netअगर_running(nic->netdev))
		वापस;

	nicvf_stop(nic->netdev);
	nicvf_खोलो(nic->netdev);
	netअगर_trans_update(nic->netdev);
पूर्ण

अटल पूर्णांक nicvf_config_loopback(काष्ठा nicvf *nic,
				 netdev_features_t features)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;

	mbx.lbk.msg = NIC_MBOX_MSG_LOOPBACK;
	mbx.lbk.vf_id = nic->vf_id;
	mbx.lbk.enable = (features & NETIF_F_LOOPBACK) != 0;

	वापस nicvf_send_msg_to_pf(nic, &mbx);
पूर्ण

अटल netdev_features_t nicvf_fix_features(काष्ठा net_device *netdev,
					    netdev_features_t features)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);

	अगर ((features & NETIF_F_LOOPBACK) &&
	    netअगर_running(netdev) && !nic->loopback_supported)
		features &= ~NETIF_F_LOOPBACK;

	वापस features;
पूर्ण

अटल पूर्णांक nicvf_set_features(काष्ठा net_device *netdev,
			      netdev_features_t features)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		nicvf_config_vlan_stripping(nic, features);

	अगर ((changed & NETIF_F_LOOPBACK) && netअगर_running(netdev))
		वापस nicvf_config_loopback(nic, features);

	वापस 0;
पूर्ण

अटल व्योम nicvf_set_xdp_queues(काष्ठा nicvf *nic, bool bpf_attached)
अणु
	u8 cq_count, txq_count;

	/* Set XDP Tx queue count same as Rx queue count */
	अगर (!bpf_attached)
		nic->xdp_tx_queues = 0;
	अन्यथा
		nic->xdp_tx_queues = nic->rx_queues;

	/* If queue count > MAX_CMP_QUEUES_PER_QS, then additional qsets
	 * needs to be allocated, check how many.
	 */
	txq_count = nic->xdp_tx_queues + nic->tx_queues;
	cq_count = max(nic->rx_queues, txq_count);
	अगर (cq_count > MAX_CMP_QUEUES_PER_QS) अणु
		nic->sqs_count = roundup(cq_count, MAX_CMP_QUEUES_PER_QS);
		nic->sqs_count = (nic->sqs_count / MAX_CMP_QUEUES_PER_QS) - 1;
	पूर्ण अन्यथा अणु
		nic->sqs_count = 0;
	पूर्ण

	/* Set primary Qset's resources */
	nic->qs->rq_cnt = min_t(u8, nic->rx_queues, MAX_RCV_QUEUES_PER_QS);
	nic->qs->sq_cnt = min_t(u8, txq_count, MAX_SND_QUEUES_PER_QS);
	nic->qs->cq_cnt = max_t(u8, nic->qs->rq_cnt, nic->qs->sq_cnt);

	/* Update stack */
	nicvf_set_real_num_queues(nic->netdev, nic->tx_queues, nic->rx_queues);
पूर्ण

अटल पूर्णांक nicvf_xdp_setup(काष्ठा nicvf *nic, काष्ठा bpf_prog *prog)
अणु
	काष्ठा net_device *dev = nic->netdev;
	bool अगर_up = netअगर_running(nic->netdev);
	काष्ठा bpf_prog *old_prog;
	bool bpf_attached = false;
	पूर्णांक ret = 0;

	/* For now just support only the usual MTU sized frames,
	 * plus some headroom क्रम VLAN, QinQ.
	 */
	अगर (prog && dev->mtu > MAX_XDP_MTU) अणु
		netdev_warn(dev, "Jumbo frames not yet supported with XDP, current MTU %d.\n",
			    dev->mtu);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* ALL SQs attached to CQs i.e same as RQs, are treated as
	 * XDP Tx queues and more Tx queues are allocated क्रम
	 * network stack to send pkts out.
	 *
	 * No of Tx queues are either same as Rx queues or whatever
	 * is left in max no of queues possible.
	 */
	अगर ((nic->rx_queues + nic->tx_queues) > nic->max_queues) अणु
		netdev_warn(dev,
			    "Failed to attach BPF prog, RXQs + TXQs > Max %d\n",
			    nic->max_queues);
		वापस -ENOMEM;
	पूर्ण

	अगर (अगर_up)
		nicvf_stop(nic->netdev);

	old_prog = xchg(&nic->xdp_prog, prog);
	/* Detach old prog, अगर any */
	अगर (old_prog)
		bpf_prog_put(old_prog);

	अगर (nic->xdp_prog) अणु
		/* Attach BPF program */
		bpf_prog_add(nic->xdp_prog, nic->rx_queues - 1);
		bpf_attached = true;
	पूर्ण

	/* Calculate Tx queues needed क्रम XDP and network stack */
	nicvf_set_xdp_queues(nic, bpf_attached);

	अगर (अगर_up) अणु
		/* Reinitialize पूर्णांकerface, clean slate */
		nicvf_खोलो(nic->netdev);
		netअगर_trans_update(nic->netdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nicvf_xdp(काष्ठा net_device *netdev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);

	/* To aव्योम checks जबतक retrieving buffer address from CQE_RX,
	 * करो not support XDP क्रम T88 pass1.x silicons which are anyway
	 * not in use widely.
	 */
	अगर (pass1_silicon(nic->pdev))
		वापस -EOPNOTSUPP;

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस nicvf_xdp_setup(nic, xdp->prog);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nicvf_config_hwtstamp(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	काष्ठा nicvf *nic = netdev_priv(netdev);

	अगर (!nic->ptp_घड़ी)
		वापस -ENODEV;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (config.flags)
		वापस -EINVAL;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		nic->hw_rx_tstamp = false;
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		nic->hw_rx_tstamp = true;
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	अगर (netअगर_running(netdev))
		nicvf_config_hw_rx_tstamp(nic, nic->hw_rx_tstamp);

	अगर (copy_to_user(अगरr->अगरr_data, &config, माप(config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक nicvf_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस nicvf_config_hwtstamp(netdev, req);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम __nicvf_set_rx_mode_task(u8 mode, काष्ठा xcast_addr_list *mc_addrs,
				     काष्ठा nicvf *nic)
अणु
	जोड़ nic_mbx mbx = अणुपूर्ण;
	पूर्णांक idx;

	/* From the inside of VM code flow we have only 128 bits memory
	 * available to send message to host's PF, so send all mc addrs
	 * one by one, starting from flush command in हाल अगर kernel
	 * requests to configure specअगरic MAC filtering
	 */

	/* flush DMAC filters and reset RX mode */
	mbx.xcast.msg = NIC_MBOX_MSG_RESET_XCAST;
	अगर (nicvf_send_msg_to_pf(nic, &mbx) < 0)
		जाओ मुक्त_mc;

	अगर (mode & BGX_XCAST_MCAST_FILTER) अणु
		/* once enabling filtering, we need to संकेत to PF to add
		 * its' own LMAC to the filter to accept packets क्रम it.
		 */
		mbx.xcast.msg = NIC_MBOX_MSG_ADD_MCAST;
		mbx.xcast.mac = 0;
		अगर (nicvf_send_msg_to_pf(nic, &mbx) < 0)
			जाओ मुक्त_mc;
	पूर्ण

	/* check अगर we have any specअगरic MACs to be added to PF DMAC filter */
	अगर (mc_addrs) अणु
		/* now go through kernel list of MACs and add them one by one */
		क्रम (idx = 0; idx < mc_addrs->count; idx++) अणु
			mbx.xcast.msg = NIC_MBOX_MSG_ADD_MCAST;
			mbx.xcast.mac = mc_addrs->mc[idx];
			अगर (nicvf_send_msg_to_pf(nic, &mbx) < 0)
				जाओ मुक्त_mc;
		पूर्ण
	पूर्ण

	/* and finally set rx mode क्रम PF accordingly */
	mbx.xcast.msg = NIC_MBOX_MSG_SET_XCAST;
	mbx.xcast.mode = mode;

	nicvf_send_msg_to_pf(nic, &mbx);
मुक्त_mc:
	kमुक्त(mc_addrs);
पूर्ण

अटल व्योम nicvf_set_rx_mode_task(काष्ठा work_काष्ठा *work_arg)
अणु
	काष्ठा nicvf_work *vf_work = container_of(work_arg, काष्ठा nicvf_work,
						  work);
	काष्ठा nicvf *nic = container_of(vf_work, काष्ठा nicvf, rx_mode_work);
	u8 mode;
	काष्ठा xcast_addr_list *mc;

	अगर (!vf_work)
		वापस;

	/* Save message data locally to prevent them from
	 * being overwritten by next nकरो_set_rx_mode call().
	 */
	spin_lock_bh(&nic->rx_mode_wq_lock);
	mode = vf_work->mode;
	mc = vf_work->mc;
	vf_work->mc = शून्य;
	spin_unlock_bh(&nic->rx_mode_wq_lock);

	__nicvf_set_rx_mode_task(mode, mc, nic);
पूर्ण

अटल व्योम nicvf_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा netdev_hw_addr *ha;
	काष्ठा xcast_addr_list *mc_list = शून्य;
	u8 mode = 0;

	अगर (netdev->flags & IFF_PROMISC) अणु
		mode = BGX_XCAST_BCAST_ACCEPT | BGX_XCAST_MCAST_ACCEPT;
	पूर्ण अन्यथा अणु
		अगर (netdev->flags & IFF_BROADCAST)
			mode |= BGX_XCAST_BCAST_ACCEPT;

		अगर (netdev->flags & IFF_ALLMULTI) अणु
			mode |= BGX_XCAST_MCAST_ACCEPT;
		पूर्ण अन्यथा अगर (netdev->flags & IFF_MULTICAST) अणु
			mode |= BGX_XCAST_MCAST_FILTER;
			/* here we need to copy mc addrs */
			अगर (netdev_mc_count(netdev)) अणु
				mc_list = kदो_स्मृति(काष्ठा_size(mc_list, mc,
							      netdev_mc_count(netdev)),
						  GFP_ATOMIC);
				अगर (unlikely(!mc_list))
					वापस;
				mc_list->count = 0;
				netdev_hw_addr_list_क्रम_each(ha, &netdev->mc) अणु
					mc_list->mc[mc_list->count] =
						ether_addr_to_u64(ha->addr);
					mc_list->count++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	spin_lock(&nic->rx_mode_wq_lock);
	kमुक्त(nic->rx_mode_work.mc);
	nic->rx_mode_work.mc = mc_list;
	nic->rx_mode_work.mode = mode;
	queue_work(nic->nicvf_rx_mode_wq, &nic->rx_mode_work.work);
	spin_unlock(&nic->rx_mode_wq_lock);
पूर्ण

अटल स्थिर काष्ठा net_device_ops nicvf_netdev_ops = अणु
	.nकरो_खोलो		= nicvf_खोलो,
	.nकरो_stop		= nicvf_stop,
	.nकरो_start_xmit		= nicvf_xmit,
	.nकरो_change_mtu		= nicvf_change_mtu,
	.nकरो_set_mac_address	= nicvf_set_mac_address,
	.nकरो_get_stats64	= nicvf_get_stats64,
	.nकरो_tx_समयout         = nicvf_tx_समयout,
	.nकरो_fix_features       = nicvf_fix_features,
	.nकरो_set_features       = nicvf_set_features,
	.nकरो_bpf		= nicvf_xdp,
	.nकरो_करो_ioctl           = nicvf_ioctl,
	.nकरो_set_rx_mode        = nicvf_set_rx_mode,
पूर्ण;

अटल पूर्णांक nicvf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *netdev;
	काष्ठा nicvf *nic;
	पूर्णांक    err, qcount;
	u16    sdevid;
	काष्ठा cavium_ptp *ptp_घड़ी;

	ptp_घड़ी = cavium_ptp_get();
	अगर (IS_ERR(ptp_घड़ी)) अणु
		अगर (PTR_ERR(ptp_घड़ी) == -ENODEV)
			/* In भवized environment we proceed without ptp */
			ptp_घड़ी = शून्य;
		अन्यथा
			वापस PTR_ERR(ptp_घड़ी);
	पूर्ण

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(dev, "Failed to enable PCI device\n");
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		जाओ err_disable_device;
	पूर्ण

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "Unable to get usable DMA configuration\n");
		जाओ err_release_regions;
	पूर्ण

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(48));
	अगर (err) अणु
		dev_err(dev, "unable to get 48-bit DMA for consistent allocations\n");
		जाओ err_release_regions;
	पूर्ण

	qcount = netअगर_get_num_शेष_rss_queues();

	/* Restrict multiqset support only क्रम host bound VFs */
	अगर (pdev->is_virtfn) अणु
		/* Set max number of queues per VF */
		qcount = min_t(पूर्णांक, num_online_cpus(),
			       (MAX_SQS_PER_VF + 1) * MAX_CMP_QUEUES_PER_QS);
	पूर्ण

	netdev = alloc_etherdev_mqs(माप(काष्ठा nicvf), qcount, qcount);
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	pci_set_drvdata(pdev, netdev);

	SET_NETDEV_DEV(netdev, &pdev->dev);

	nic = netdev_priv(netdev);
	nic->netdev = netdev;
	nic->pdev = pdev;
	nic->pnicvf = nic;
	nic->max_queues = qcount;
	/* If no of CPUs are too low, there won't be any queues left
	 * क्रम XDP_TX, hence द्विगुन it.
	 */
	अगर (!nic->t88)
		nic->max_queues *= 2;
	nic->ptp_घड़ी = ptp_घड़ी;

	/* Initialize mutex that serializes usage of VF's mailbox */
	mutex_init(&nic->rx_mode_mtx);

	/* MAP VF's configuration रेजिस्टरs */
	nic->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	अगर (!nic->reg_base) अणु
		dev_err(dev, "Cannot map config register space, aborting\n");
		err = -ENOMEM;
		जाओ err_मुक्त_netdev;
	पूर्ण

	nic->drv_stats = netdev_alloc_pcpu_stats(काष्ठा nicvf_drv_stats);
	अगर (!nic->drv_stats) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_netdev;
	पूर्ण

	err = nicvf_set_qset_resources(nic);
	अगर (err)
		जाओ err_मुक्त_netdev;

	/* Check अगर PF is alive and get MAC address क्रम this VF */
	err = nicvf_रेजिस्टर_misc_पूर्णांकerrupt(nic);
	अगर (err)
		जाओ err_मुक्त_netdev;

	nicvf_send_vf_काष्ठा(nic);

	अगर (!pass1_silicon(nic->pdev))
		nic->hw_tso = true;

	/* Get iommu करोमुख्य क्रम iova to physical addr conversion */
	nic->iommu_करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);

	pci_पढ़ो_config_word(nic->pdev, PCI_SUBSYSTEM_ID, &sdevid);
	अगर (sdevid == 0xA134)
		nic->t88 = true;

	/* Check अगर this VF is in QS only mode */
	अगर (nic->sqs_mode)
		वापस 0;

	err = nicvf_set_real_num_queues(netdev, nic->tx_queues, nic->rx_queues);
	अगर (err)
		जाओ err_unरेजिस्टर_पूर्णांकerrupts;

	netdev->hw_features = (NETIF_F_RXCSUM | NETIF_F_SG |
			       NETIF_F_TSO | NETIF_F_GRO | NETIF_F_TSO6 |
			       NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			       NETIF_F_HW_VLAN_CTAG_RX);

	netdev->hw_features |= NETIF_F_RXHASH;

	netdev->features |= netdev->hw_features;
	netdev->hw_features |= NETIF_F_LOOPBACK;

	netdev->vlan_features = NETIF_F_SG | NETIF_F_IP_CSUM |
				NETIF_F_IPV6_CSUM | NETIF_F_TSO | NETIF_F_TSO6;

	netdev->netdev_ops = &nicvf_netdev_ops;
	netdev->watchकरोg_समयo = NICVF_TX_TIMEOUT;

	/* MTU range: 64 - 9200 */
	netdev->min_mtu = NIC_HW_MIN_FRS;
	netdev->max_mtu = NIC_HW_MAX_FRS;

	INIT_WORK(&nic->reset_task, nicvf_reset_task);

	nic->nicvf_rx_mode_wq = alloc_ordered_workqueue("nicvf_rx_mode_wq_VF%d",
							WQ_MEM_RECLAIM,
							nic->vf_id);
	अगर (!nic->nicvf_rx_mode_wq) अणु
		err = -ENOMEM;
		dev_err(dev, "Failed to allocate work queue\n");
		जाओ err_unरेजिस्टर_पूर्णांकerrupts;
	पूर्ण

	INIT_WORK(&nic->rx_mode_work.work, nicvf_set_rx_mode_task);
	spin_lock_init(&nic->rx_mode_wq_lock);

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(dev, "Failed to register netdevice\n");
		जाओ err_unरेजिस्टर_पूर्णांकerrupts;
	पूर्ण

	nic->msg_enable = debug;

	nicvf_set_ethtool_ops(netdev);

	वापस 0;

err_unरेजिस्टर_पूर्णांकerrupts:
	nicvf_unरेजिस्टर_पूर्णांकerrupts(nic);
err_मुक्त_netdev:
	pci_set_drvdata(pdev, शून्य);
	अगर (nic->drv_stats)
		मुक्त_percpu(nic->drv_stats);
	मुक्त_netdev(netdev);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

अटल व्योम nicvf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा nicvf *nic;
	काष्ठा net_device *pnetdev;

	अगर (!netdev)
		वापस;

	nic = netdev_priv(netdev);
	pnetdev = nic->pnicvf->netdev;

	/* Check अगर this Qset is asचिन्हित to dअगरferent VF.
	 * If yes, clean primary and all secondary Qsets.
	 */
	अगर (pnetdev && (pnetdev->reg_state == NETREG_REGISTERED))
		unरेजिस्टर_netdev(pnetdev);
	अगर (nic->nicvf_rx_mode_wq) अणु
		destroy_workqueue(nic->nicvf_rx_mode_wq);
		nic->nicvf_rx_mode_wq = शून्य;
	पूर्ण
	nicvf_unरेजिस्टर_पूर्णांकerrupts(nic);
	pci_set_drvdata(pdev, शून्य);
	अगर (nic->drv_stats)
		मुक्त_percpu(nic->drv_stats);
	cavium_ptp_put(nic->ptp_घड़ी);
	मुक्त_netdev(netdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल व्योम nicvf_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	nicvf_हटाओ(pdev);
पूर्ण

अटल काष्ठा pci_driver nicvf_driver = अणु
	.name = DRV_NAME,
	.id_table = nicvf_id_table,
	.probe = nicvf_probe,
	.हटाओ = nicvf_हटाओ,
	.shutकरोwn = nicvf_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init nicvf_init_module(व्योम)
अणु
	pr_info("%s, ver %s\n", DRV_NAME, DRV_VERSION);
	वापस pci_रेजिस्टर_driver(&nicvf_driver);
पूर्ण

अटल व्योम __निकास nicvf_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&nicvf_driver);
पूर्ण

module_init(nicvf_init_module);
module_निकास(nicvf_cleanup_module);
