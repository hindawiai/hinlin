<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Cavium, Inc.
 */

/* ETHTOOL Support क्रम VNIC_VF Device*/

#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>
#समावेश <linux/net_tstamp.h>

#समावेश "nic_reg.h"
#समावेश "nic.h"
#समावेश "nicvf_queues.h"
#समावेश "q_struct.h"
#समावेश "thunder_bgx.h"
#समावेश "../common/cavium_ptp.h"

#घोषणा DRV_NAME	"nicvf"

काष्ठा nicvf_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	अचिन्हित पूर्णांक index;
पूर्ण;

#घोषणा NICVF_HW_STAT(stat) अणु \
	.name = #stat, \
	.index = दुरत्व(काष्ठा nicvf_hw_stats, stat) / माप(u64), \
पूर्ण

#घोषणा NICVF_DRV_STAT(stat) अणु \
	.name = #stat, \
	.index = दुरत्व(काष्ठा nicvf_drv_stats, stat) / माप(u64), \
पूर्ण

अटल स्थिर काष्ठा nicvf_stat nicvf_hw_stats[] = अणु
	NICVF_HW_STAT(rx_bytes),
	NICVF_HW_STAT(rx_frames),
	NICVF_HW_STAT(rx_ucast_frames),
	NICVF_HW_STAT(rx_bcast_frames),
	NICVF_HW_STAT(rx_mcast_frames),
	NICVF_HW_STAT(rx_drops),
	NICVF_HW_STAT(rx_drop_red),
	NICVF_HW_STAT(rx_drop_red_bytes),
	NICVF_HW_STAT(rx_drop_overrun),
	NICVF_HW_STAT(rx_drop_overrun_bytes),
	NICVF_HW_STAT(rx_drop_bcast),
	NICVF_HW_STAT(rx_drop_mcast),
	NICVF_HW_STAT(rx_drop_l3_bcast),
	NICVF_HW_STAT(rx_drop_l3_mcast),
	NICVF_HW_STAT(rx_fcs_errors),
	NICVF_HW_STAT(rx_l2_errors),
	NICVF_HW_STAT(tx_bytes),
	NICVF_HW_STAT(tx_frames),
	NICVF_HW_STAT(tx_ucast_frames),
	NICVF_HW_STAT(tx_bcast_frames),
	NICVF_HW_STAT(tx_mcast_frames),
	NICVF_HW_STAT(tx_drops),
पूर्ण;

अटल स्थिर काष्ठा nicvf_stat nicvf_drv_stats[] = अणु
	NICVF_DRV_STAT(rx_bgx_truncated_pkts),
	NICVF_DRV_STAT(rx_jabber_errs),
	NICVF_DRV_STAT(rx_fcs_errs),
	NICVF_DRV_STAT(rx_bgx_errs),
	NICVF_DRV_STAT(rx_prel2_errs),
	NICVF_DRV_STAT(rx_l2_hdr_malक्रमmed),
	NICVF_DRV_STAT(rx_oversize),
	NICVF_DRV_STAT(rx_undersize),
	NICVF_DRV_STAT(rx_l2_len_mismatch),
	NICVF_DRV_STAT(rx_l2_pclp),
	NICVF_DRV_STAT(rx_ip_ver_errs),
	NICVF_DRV_STAT(rx_ip_csum_errs),
	NICVF_DRV_STAT(rx_ip_hdr_malक्रमmed),
	NICVF_DRV_STAT(rx_ip_payload_malक्रमmed),
	NICVF_DRV_STAT(rx_ip_ttl_errs),
	NICVF_DRV_STAT(rx_l3_pclp),
	NICVF_DRV_STAT(rx_l4_malक्रमmed),
	NICVF_DRV_STAT(rx_l4_csum_errs),
	NICVF_DRV_STAT(rx_udp_len_errs),
	NICVF_DRV_STAT(rx_l4_port_errs),
	NICVF_DRV_STAT(rx_tcp_flag_errs),
	NICVF_DRV_STAT(rx_tcp_offset_errs),
	NICVF_DRV_STAT(rx_l4_pclp),
	NICVF_DRV_STAT(rx_truncated_pkts),

	NICVF_DRV_STAT(tx_desc_fault),
	NICVF_DRV_STAT(tx_hdr_cons_err),
	NICVF_DRV_STAT(tx_subdesc_err),
	NICVF_DRV_STAT(tx_max_size_exceeded),
	NICVF_DRV_STAT(tx_imm_size_oflow),
	NICVF_DRV_STAT(tx_data_seq_err),
	NICVF_DRV_STAT(tx_mem_seq_err),
	NICVF_DRV_STAT(tx_lock_viol),
	NICVF_DRV_STAT(tx_data_fault),
	NICVF_DRV_STAT(tx_tsपंचांगp_conflict),
	NICVF_DRV_STAT(tx_tsपंचांगp_समयout),
	NICVF_DRV_STAT(tx_mem_fault),
	NICVF_DRV_STAT(tx_csum_overlap),
	NICVF_DRV_STAT(tx_csum_overflow),

	NICVF_DRV_STAT(tx_tso),
	NICVF_DRV_STAT(tx_समयout),
	NICVF_DRV_STAT(txq_stop),
	NICVF_DRV_STAT(txq_wake),
	NICVF_DRV_STAT(rcv_buffer_alloc_failures),
	NICVF_DRV_STAT(page_alloc),
पूर्ण;

अटल स्थिर काष्ठा nicvf_stat nicvf_queue_stats[] = अणु
	अणु "bytes", 0 पूर्ण,
	अणु "frames", 1 पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक nicvf_n_hw_stats = ARRAY_SIZE(nicvf_hw_stats);
अटल स्थिर अचिन्हित पूर्णांक nicvf_n_drv_stats = ARRAY_SIZE(nicvf_drv_stats);
अटल स्थिर अचिन्हित पूर्णांक nicvf_n_queue_stats = ARRAY_SIZE(nicvf_queue_stats);

अटल पूर्णांक nicvf_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	u32 supported, advertising;

	supported = 0;
	advertising = 0;

	अगर (!nic->link_up) अणु
		cmd->base.duplex = DUPLEX_UNKNOWN;
		cmd->base.speed = SPEED_UNKNOWN;
		वापस 0;
	पूर्ण

	चयन (nic->speed) अणु
	हाल SPEED_1000:
		cmd->base.port = PORT_MII | PORT_TP;
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
		supported |= SUPPORTED_MII | SUPPORTED_TP;
		supported |= SUPPORTED_1000baseT_Full |
				  SUPPORTED_1000baseT_Half |
				  SUPPORTED_100baseT_Full  |
				  SUPPORTED_100baseT_Half  |
				  SUPPORTED_10baseT_Full   |
				  SUPPORTED_10baseT_Half;
		supported |= SUPPORTED_Autoneg;
		advertising |= ADVERTISED_1000baseT_Full |
				    ADVERTISED_1000baseT_Half |
				    ADVERTISED_100baseT_Full  |
				    ADVERTISED_100baseT_Half  |
				    ADVERTISED_10baseT_Full   |
				    ADVERTISED_10baseT_Half;
		अवरोध;
	हाल SPEED_10000:
		अगर (nic->mac_type == BGX_MODE_RXAUI) अणु
			cmd->base.port = PORT_TP;
			supported |= SUPPORTED_TP;
		पूर्ण अन्यथा अणु
			cmd->base.port = PORT_FIBRE;
			supported |= SUPPORTED_FIBRE;
		पूर्ण
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
		supported |= SUPPORTED_10000baseT_Full;
		अवरोध;
	हाल SPEED_40000:
		cmd->base.port = PORT_FIBRE;
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
		supported |= SUPPORTED_FIBRE;
		supported |= SUPPORTED_40000baseCR4_Full;
		अवरोध;
	पूर्ण
	cmd->base.duplex = nic->duplex;
	cmd->base.speed = nic->speed;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल u32 nicvf_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);

	वापस nic->link_up;
पूर्ण

अटल व्योम nicvf_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(nic->pdev), माप(info->bus_info));
पूर्ण

अटल u32 nicvf_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);

	वापस nic->msg_enable;
पूर्ण

अटल व्योम nicvf_set_msglevel(काष्ठा net_device *netdev, u32 lvl)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);

	nic->msg_enable = lvl;
पूर्ण

अटल व्योम nicvf_get_qset_strings(काष्ठा nicvf *nic, u8 **data, पूर्णांक qset)
अणु
	पूर्णांक stats, qidx;
	पूर्णांक start_qidx = qset * MAX_RCV_QUEUES_PER_QS;

	क्रम (qidx = 0; qidx < nic->qs->rq_cnt; qidx++) अणु
		क्रम (stats = 0; stats < nicvf_n_queue_stats; stats++) अणु
			प्र_लिखो(*data, "rxq%d: %s", qidx + start_qidx,
				nicvf_queue_stats[stats].name);
			*data += ETH_GSTRING_LEN;
		पूर्ण
	पूर्ण

	क्रम (qidx = 0; qidx < nic->qs->sq_cnt; qidx++) अणु
		क्रम (stats = 0; stats < nicvf_n_queue_stats; stats++) अणु
			प्र_लिखो(*data, "txq%d: %s", qidx + start_qidx,
				nicvf_queue_stats[stats].name);
			*data += ETH_GSTRING_LEN;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nicvf_get_strings(काष्ठा net_device *netdev, u32 sset, u8 *data)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	पूर्णांक stats;
	पूर्णांक sqs;

	अगर (sset != ETH_SS_STATS)
		वापस;

	क्रम (stats = 0; stats < nicvf_n_hw_stats; stats++) अणु
		स_नकल(data, nicvf_hw_stats[stats].name, ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (stats = 0; stats < nicvf_n_drv_stats; stats++) अणु
		स_नकल(data, nicvf_drv_stats[stats].name, ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण

	nicvf_get_qset_strings(nic, &data, 0);

	क्रम (sqs = 0; sqs < nic->sqs_count; sqs++) अणु
		अगर (!nic->snicvf[sqs])
			जारी;
		nicvf_get_qset_strings(nic->snicvf[sqs], &data, sqs + 1);
	पूर्ण

	क्रम (stats = 0; stats < BGX_RX_STATS_COUNT; stats++) अणु
		प्र_लिखो(data, "bgx_rxstat%d: ", stats);
		data += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (stats = 0; stats < BGX_TX_STATS_COUNT; stats++) अणु
		प्र_लिखो(data, "bgx_txstat%d: ", stats);
		data += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल पूर्णांक nicvf_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	पूर्णांक qstats_count;
	पूर्णांक sqs;

	अगर (sset != ETH_SS_STATS)
		वापस -EINVAL;

	qstats_count = nicvf_n_queue_stats *
		       (nic->qs->rq_cnt + nic->qs->sq_cnt);
	क्रम (sqs = 0; sqs < nic->sqs_count; sqs++) अणु
		काष्ठा nicvf *snic;

		snic = nic->snicvf[sqs];
		अगर (!snic)
			जारी;
		qstats_count += nicvf_n_queue_stats *
				(snic->qs->rq_cnt + snic->qs->sq_cnt);
	पूर्ण

	वापस nicvf_n_hw_stats + nicvf_n_drv_stats +
		qstats_count +
		BGX_RX_STATS_COUNT + BGX_TX_STATS_COUNT;
पूर्ण

अटल व्योम nicvf_get_qset_stats(काष्ठा nicvf *nic,
				 काष्ठा ethtool_stats *stats, u64 **data)
अणु
	पूर्णांक stat, qidx;

	अगर (!nic)
		वापस;

	क्रम (qidx = 0; qidx < nic->qs->rq_cnt; qidx++) अणु
		nicvf_update_rq_stats(nic, qidx);
		क्रम (stat = 0; stat < nicvf_n_queue_stats; stat++)
			*((*data)++) = ((u64 *)&nic->qs->rq[qidx].stats)
					[nicvf_queue_stats[stat].index];
	पूर्ण

	क्रम (qidx = 0; qidx < nic->qs->sq_cnt; qidx++) अणु
		nicvf_update_sq_stats(nic, qidx);
		क्रम (stat = 0; stat < nicvf_n_queue_stats; stat++)
			*((*data)++) = ((u64 *)&nic->qs->sq[qidx].stats)
					[nicvf_queue_stats[stat].index];
	पूर्ण
पूर्ण

अटल व्योम nicvf_get_ethtool_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	पूर्णांक stat, पंचांगp_stats;
	पूर्णांक sqs, cpu;

	nicvf_update_stats(nic);

	/* Update LMAC stats */
	nicvf_update_lmac_stats(nic);

	क्रम (stat = 0; stat < nicvf_n_hw_stats; stat++)
		*(data++) = ((u64 *)&nic->hw_stats)
				[nicvf_hw_stats[stat].index];
	क्रम (stat = 0; stat < nicvf_n_drv_stats; stat++) अणु
		पंचांगp_stats = 0;
		क्रम_each_possible_cpu(cpu)
			पंचांगp_stats += ((u64 *)per_cpu_ptr(nic->drv_stats, cpu))
				     [nicvf_drv_stats[stat].index];
		*(data++) = पंचांगp_stats;
	पूर्ण

	nicvf_get_qset_stats(nic, stats, &data);

	क्रम (sqs = 0; sqs < nic->sqs_count; sqs++) अणु
		अगर (!nic->snicvf[sqs])
			जारी;
		nicvf_get_qset_stats(nic->snicvf[sqs], stats, &data);
	पूर्ण

	क्रम (stat = 0; stat < BGX_RX_STATS_COUNT; stat++)
		*(data++) = nic->bgx_stats.rx_stats[stat];
	क्रम (stat = 0; stat < BGX_TX_STATS_COUNT; stat++)
		*(data++) = nic->bgx_stats.tx_stats[stat];
पूर्ण

अटल पूर्णांक nicvf_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस माप(u64) * NIC_VF_REG_COUNT;
पूर्ण

अटल व्योम nicvf_get_regs(काष्ठा net_device *dev,
			   काष्ठा ethtool_regs *regs, व्योम *reg)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);
	u64 *p = (u64 *)reg;
	u64 reg_offset;
	पूर्णांक mbox, key, stat, q;
	पूर्णांक i = 0;

	regs->version = 0;
	स_रखो(p, 0, NIC_VF_REG_COUNT);

	p[i++] = nicvf_reg_पढ़ो(nic, NIC_VNIC_CFG);
	/* Mailbox रेजिस्टरs */
	क्रम (mbox = 0; mbox < NIC_PF_VF_MAILBOX_SIZE; mbox++)
		p[i++] = nicvf_reg_पढ़ो(nic,
					NIC_VF_PF_MAILBOX_0_1 | (mbox << 3));

	p[i++] = nicvf_reg_पढ़ो(nic, NIC_VF_INT);
	p[i++] = nicvf_reg_पढ़ो(nic, NIC_VF_INT_W1S);
	p[i++] = nicvf_reg_पढ़ो(nic, NIC_VF_ENA_W1C);
	p[i++] = nicvf_reg_पढ़ो(nic, NIC_VF_ENA_W1S);
	p[i++] = nicvf_reg_पढ़ो(nic, NIC_VNIC_RSS_CFG);

	क्रम (key = 0; key < RSS_HASH_KEY_SIZE; key++)
		p[i++] = nicvf_reg_पढ़ो(nic, NIC_VNIC_RSS_KEY_0_4 | (key << 3));

	/* Tx/Rx statistics */
	क्रम (stat = 0; stat < TX_STATS_ENUM_LAST; stat++)
		p[i++] = nicvf_reg_पढ़ो(nic,
					NIC_VNIC_TX_STAT_0_4 | (stat << 3));

	क्रम (i = 0; i < RX_STATS_ENUM_LAST; i++)
		p[i++] = nicvf_reg_पढ़ो(nic,
					NIC_VNIC_RX_STAT_0_13 | (stat << 3));

	p[i++] = nicvf_reg_पढ़ो(nic, NIC_QSET_RQ_GEN_CFG);

	/* All completion queue's रेजिस्टरs */
	क्रम (q = 0; q < MAX_CMP_QUEUES_PER_QS; q++) अणु
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_CFG, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_CFG2, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_THRESH, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_BASE, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_HEAD, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_TAIL, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_DOOR, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_STATUS, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_STATUS2, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_CQ_0_7_DEBUG, q);
	पूर्ण

	/* All receive queue's रेजिस्टरs */
	क्रम (q = 0; q < MAX_RCV_QUEUES_PER_QS; q++) अणु
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RQ_0_7_CFG, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic,
						  NIC_QSET_RQ_0_7_STAT_0_1, q);
		reg_offset = NIC_QSET_RQ_0_7_STAT_0_1 | (1 << 3);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, reg_offset, q);
	पूर्ण

	क्रम (q = 0; q < MAX_SND_QUEUES_PER_QS; q++) अणु
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_CFG, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_THRESH, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_BASE, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_HEAD, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_TAIL, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_DOOR, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_STATUS, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_DEBUG, q);
		/* Padding, was NIC_QSET_SQ_0_7_CNM_CHG, which
		 * produces bus errors when पढ़ो
		 */
		p[i++] = 0;
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_SQ_0_7_STAT_0_1, q);
		reg_offset = NIC_QSET_SQ_0_7_STAT_0_1 | (1 << 3);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, reg_offset, q);
	पूर्ण

	क्रम (q = 0; q < MAX_RCV_BUF_DESC_RINGS_PER_QS; q++) अणु
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RBDR_0_1_CFG, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RBDR_0_1_THRESH, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RBDR_0_1_BASE, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RBDR_0_1_HEAD, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RBDR_0_1_TAIL, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic, NIC_QSET_RBDR_0_1_DOOR, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic,
					      NIC_QSET_RBDR_0_1_STATUS0, q);
		p[i++] = nicvf_queue_reg_पढ़ो(nic,
					      NIC_QSET_RBDR_0_1_STATUS1, q);
		reg_offset = NIC_QSET_RBDR_0_1_PREFETCH_STATUS;
		p[i++] = nicvf_queue_reg_पढ़ो(nic, reg_offset, q);
	पूर्ण
पूर्ण

अटल पूर्णांक nicvf_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *cmd)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);

	cmd->rx_coalesce_usecs = nic->cq_coalesce_usecs;
	वापस 0;
पूर्ण

अटल व्योम nicvf_get_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा queue_set *qs = nic->qs;

	ring->rx_max_pending = MAX_CMP_QUEUE_LEN;
	ring->rx_pending = qs->cq_len;
	ring->tx_max_pending = MAX_SND_QUEUE_LEN;
	ring->tx_pending = qs->sq_len;
पूर्ण

अटल पूर्णांक nicvf_set_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);
	काष्ठा queue_set *qs = nic->qs;
	u32 rx_count, tx_count;

	/* Due to HW errata this is not supported on T88 pass 1.x silicon */
	अगर (pass1_silicon(nic->pdev))
		वापस -EINVAL;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	tx_count = clamp_t(u32, ring->tx_pending,
			   MIN_SND_QUEUE_LEN, MAX_SND_QUEUE_LEN);
	rx_count = clamp_t(u32, ring->rx_pending,
			   MIN_CMP_QUEUE_LEN, MAX_CMP_QUEUE_LEN);

	अगर ((tx_count == qs->sq_len) && (rx_count == qs->cq_len))
		वापस 0;

	/* Permitted lengths are 1K, 2K, 4K, 8K, 16K, 32K, 64K */
	qs->sq_len = roundकरोwn_घात_of_two(tx_count);
	qs->cq_len = roundकरोwn_घात_of_two(rx_count);

	अगर (netअगर_running(netdev)) अणु
		nicvf_stop(netdev);
		nicvf_खोलो(netdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nicvf_get_rss_hash_opts(काष्ठा nicvf *nic,
				   काष्ठा ethtool_rxnfc *info)
अणु
	info->data = 0;

	चयन (info->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
		info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		info->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nicvf_get_rxnfc(काष्ठा net_device *dev,
			   काष्ठा ethtool_rxnfc *info, u32 *rules)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = nic->rx_queues;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXFH:
		वापस nicvf_get_rss_hash_opts(nic, info);
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nicvf_set_rss_hash_opts(काष्ठा nicvf *nic,
				   काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा nicvf_rss_info *rss = &nic->rss_info;
	u64 rss_cfg = nicvf_reg_पढ़ो(nic, NIC_VNIC_RSS_CFG);

	अगर (!rss->enable)
		netdev_err(nic->netdev,
			   "RSS is disabled, hash cannot be set\n");

	netdev_info(nic->netdev, "Set RSS flow type = %d, data = %lld\n",
		    info->flow_type, info->data);

	अगर (!(info->data & RXH_IP_SRC) || !(info->data & RXH_IP_DST))
		वापस -EINVAL;

	चयन (info->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		चयन (info->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
		हाल 0:
			rss_cfg &= ~(1ULL << RSS_HASH_TCP);
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			rss_cfg |= (1ULL << RSS_HASH_TCP);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		चयन (info->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
		हाल 0:
			rss_cfg &= ~(1ULL << RSS_HASH_UDP);
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			rss_cfg |= (1ULL << RSS_HASH_UDP);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
		चयन (info->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
		हाल 0:
			rss_cfg &= ~(1ULL << RSS_HASH_L4ETC);
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			rss_cfg |= (1ULL << RSS_HASH_L4ETC);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		rss_cfg = RSS_HASH_IP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nicvf_reg_ग_लिखो(nic, NIC_VNIC_RSS_CFG, rss_cfg);
	वापस 0;
पूर्ण

अटल पूर्णांक nicvf_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);

	चयन (info->cmd) अणु
	हाल ETHTOOL_SRXFH:
		वापस nicvf_set_rss_hash_opts(nic, info);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल u32 nicvf_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस RSS_HASH_KEY_SIZE * माप(u64);
पूर्ण

अटल u32 nicvf_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);

	वापस nic->rss_info.rss_size;
पूर्ण

अटल पूर्णांक nicvf_get_rxfh(काष्ठा net_device *dev, u32 *indir, u8 *hkey,
			  u8 *hfunc)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);
	काष्ठा nicvf_rss_info *rss = &nic->rss_info;
	पूर्णांक idx;

	अगर (indir) अणु
		क्रम (idx = 0; idx < rss->rss_size; idx++)
			indir[idx] = rss->ind_tbl[idx];
	पूर्ण

	अगर (hkey)
		स_नकल(hkey, rss->key, RSS_HASH_KEY_SIZE * माप(u64));

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	वापस 0;
पूर्ण

अटल पूर्णांक nicvf_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
			  स्थिर u8 *hkey, स्थिर u8 hfunc)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);
	काष्ठा nicvf_rss_info *rss = &nic->rss_info;
	पूर्णांक idx;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	अगर (!rss->enable) अणु
		netdev_err(nic->netdev,
			   "RSS is disabled, cannot change settings\n");
		वापस -EIO;
	पूर्ण

	अगर (indir) अणु
		क्रम (idx = 0; idx < rss->rss_size; idx++)
			rss->ind_tbl[idx] = indir[idx];
	पूर्ण

	अगर (hkey) अणु
		स_नकल(rss->key, hkey, RSS_HASH_KEY_SIZE * माप(u64));
		nicvf_set_rss_key(nic);
	पूर्ण

	nicvf_config_rss(nic);
	वापस 0;
पूर्ण

/* Get no of queues device supports and current queue count */
अटल व्योम nicvf_get_channels(काष्ठा net_device *dev,
			       काष्ठा ethtool_channels *channel)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);

	स_रखो(channel, 0, माप(*channel));

	channel->max_rx = nic->max_queues;
	channel->max_tx = nic->max_queues;

	channel->rx_count = nic->rx_queues;
	channel->tx_count = nic->tx_queues;
पूर्ण

/* Set no of Tx, Rx queues to be used */
अटल पूर्णांक nicvf_set_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *channel)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);
	पूर्णांक err = 0;
	bool अगर_up = netअगर_running(dev);
	u8 cqcount, txq_count;

	अगर (!channel->rx_count || !channel->tx_count)
		वापस -EINVAL;
	अगर (channel->rx_count > nic->max_queues)
		वापस -EINVAL;
	अगर (channel->tx_count > nic->max_queues)
		वापस -EINVAL;

	अगर (nic->xdp_prog &&
	    ((channel->tx_count + channel->rx_count) > nic->max_queues)) अणु
		netdev_err(nic->netdev,
			   "XDP mode, RXQs + TXQs > Max %d\n",
			   nic->max_queues);
		वापस -EINVAL;
	पूर्ण

	अगर (अगर_up)
		nicvf_stop(dev);

	nic->rx_queues = channel->rx_count;
	nic->tx_queues = channel->tx_count;
	अगर (!nic->xdp_prog)
		nic->xdp_tx_queues = 0;
	अन्यथा
		nic->xdp_tx_queues = channel->rx_count;

	txq_count = nic->xdp_tx_queues + nic->tx_queues;
	cqcount = max(nic->rx_queues, txq_count);

	अगर (cqcount > MAX_CMP_QUEUES_PER_QS) अणु
		nic->sqs_count = roundup(cqcount, MAX_CMP_QUEUES_PER_QS);
		nic->sqs_count = (nic->sqs_count / MAX_CMP_QUEUES_PER_QS) - 1;
	पूर्ण अन्यथा अणु
		nic->sqs_count = 0;
	पूर्ण

	nic->qs->rq_cnt = min_t(u8, nic->rx_queues, MAX_RCV_QUEUES_PER_QS);
	nic->qs->sq_cnt = min_t(u8, txq_count, MAX_SND_QUEUES_PER_QS);
	nic->qs->cq_cnt = max(nic->qs->rq_cnt, nic->qs->sq_cnt);

	err = nicvf_set_real_num_queues(dev, nic->tx_queues, nic->rx_queues);
	अगर (err)
		वापस err;

	अगर (अगर_up)
		nicvf_खोलो(dev);

	netdev_info(dev, "Setting num Tx rings to %d, Rx rings to %d success\n",
		    nic->tx_queues, nic->rx_queues);

	वापस err;
पूर्ण

अटल व्योम nicvf_get_छोड़ोparam(काष्ठा net_device *dev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);
	जोड़ nic_mbx mbx = अणुपूर्ण;

	/* Supported only क्रम 10G/40G पूर्णांकerfaces */
	अगर ((nic->mac_type == BGX_MODE_SGMII) ||
	    (nic->mac_type == BGX_MODE_QSGMII) ||
	    (nic->mac_type == BGX_MODE_RGMII))
		वापस;

	mbx.pfc.msg = NIC_MBOX_MSG_PFC;
	mbx.pfc.get = 1;
	अगर (!nicvf_send_msg_to_pf(nic, &mbx)) अणु
		छोड़ो->स्वतःneg = nic->pfc.स्वतःneg;
		छोड़ो->rx_छोड़ो = nic->pfc.fc_rx;
		छोड़ो->tx_छोड़ो = nic->pfc.fc_tx;
	पूर्ण
पूर्ण

अटल पूर्णांक nicvf_set_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा nicvf *nic = netdev_priv(dev);
	जोड़ nic_mbx mbx = अणुपूर्ण;

	/* Supported only क्रम 10G/40G पूर्णांकerfaces */
	अगर ((nic->mac_type == BGX_MODE_SGMII) ||
	    (nic->mac_type == BGX_MODE_QSGMII) ||
	    (nic->mac_type == BGX_MODE_RGMII))
		वापस -EOPNOTSUPP;

	अगर (छोड़ो->स्वतःneg)
		वापस -EOPNOTSUPP;

	mbx.pfc.msg = NIC_MBOX_MSG_PFC;
	mbx.pfc.get = 0;
	mbx.pfc.fc_rx = छोड़ो->rx_छोड़ो;
	mbx.pfc.fc_tx = छोड़ो->tx_छोड़ो;
	अगर (nicvf_send_msg_to_pf(nic, &mbx))
		वापस -EAGAIN;

	nic->pfc.fc_rx = छोड़ो->rx_छोड़ो;
	nic->pfc.fc_tx = छोड़ो->tx_छोड़ो;

	वापस 0;
पूर्ण

अटल पूर्णांक nicvf_get_ts_info(काष्ठा net_device *netdev,
			     काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा nicvf *nic = netdev_priv(netdev);

	अगर (!nic->ptp_घड़ी)
		वापस ethtool_op_get_ts_info(netdev, info);

	info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE |
				SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	info->phc_index = cavium_ptp_घड़ी_index(nic->ptp_घड़ी);

	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);

	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_ALL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops nicvf_ethtool_ops = अणु
	.get_link		= nicvf_get_link,
	.get_drvinfo		= nicvf_get_drvinfo,
	.get_msglevel		= nicvf_get_msglevel,
	.set_msglevel		= nicvf_set_msglevel,
	.get_strings		= nicvf_get_strings,
	.get_sset_count		= nicvf_get_sset_count,
	.get_ethtool_stats	= nicvf_get_ethtool_stats,
	.get_regs_len		= nicvf_get_regs_len,
	.get_regs		= nicvf_get_regs,
	.get_coalesce		= nicvf_get_coalesce,
	.get_ringparam		= nicvf_get_ringparam,
	.set_ringparam		= nicvf_set_ringparam,
	.get_rxnfc		= nicvf_get_rxnfc,
	.set_rxnfc		= nicvf_set_rxnfc,
	.get_rxfh_key_size	= nicvf_get_rxfh_key_size,
	.get_rxfh_indir_size	= nicvf_get_rxfh_indir_size,
	.get_rxfh		= nicvf_get_rxfh,
	.set_rxfh		= nicvf_set_rxfh,
	.get_channels		= nicvf_get_channels,
	.set_channels		= nicvf_set_channels,
	.get_छोड़ोparam         = nicvf_get_छोड़ोparam,
	.set_छोड़ोparam         = nicvf_set_छोड़ोparam,
	.get_ts_info		= nicvf_get_ts_info,
	.get_link_ksettings	= nicvf_get_link_ksettings,
पूर्ण;

व्योम nicvf_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &nicvf_ethtool_ops;
पूर्ण
