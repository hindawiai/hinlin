<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Ethernet driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/pci.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/log2.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/linkmode.h>

#समावेश "otx2_common.h"
#समावेश "otx2_ptp.h"

#घोषणा DRV_NAME	"octeontx2-nicpf"
#घोषणा DRV_VF_NAME	"octeontx2-nicvf"

काष्ठा otx2_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	अचिन्हित पूर्णांक index;
पूर्ण;

/* HW device stats */
#घोषणा OTX2_DEV_STAT(stat) अणु \
	.name = #stat, \
	.index = दुरत्व(काष्ठा otx2_dev_stats, stat) / माप(u64), \
पूर्ण

/* Physical link config */
#घोषणा OTX2_ETHTOOL_SUPPORTED_MODES 0x638CCBF //110001110001100110010111111

क्रमागत link_mode अणु
	OTX2_MODE_SUPPORTED,
	OTX2_MODE_ADVERTISED
पूर्ण;

अटल स्थिर काष्ठा otx2_stat otx2_dev_stats[] = अणु
	OTX2_DEV_STAT(rx_ucast_frames),
	OTX2_DEV_STAT(rx_bcast_frames),
	OTX2_DEV_STAT(rx_mcast_frames),

	OTX2_DEV_STAT(tx_ucast_frames),
	OTX2_DEV_STAT(tx_bcast_frames),
	OTX2_DEV_STAT(tx_mcast_frames),
पूर्ण;

/* Driver level stats */
#घोषणा OTX2_DRV_STAT(stat) अणु \
	.name = #stat, \
	.index = दुरत्व(काष्ठा otx2_drv_stats, stat) / माप(atomic_t), \
पूर्ण

अटल स्थिर काष्ठा otx2_stat otx2_drv_stats[] = अणु
	OTX2_DRV_STAT(rx_fcs_errs),
	OTX2_DRV_STAT(rx_oversize_errs),
	OTX2_DRV_STAT(rx_undersize_errs),
	OTX2_DRV_STAT(rx_csum_errs),
	OTX2_DRV_STAT(rx_len_errs),
	OTX2_DRV_STAT(rx_other_errs),
पूर्ण;

अटल स्थिर काष्ठा otx2_stat otx2_queue_stats[] = अणु
	अणु "bytes", 0 पूर्ण,
	अणु "frames", 1 पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक otx2_n_dev_stats = ARRAY_SIZE(otx2_dev_stats);
अटल स्थिर अचिन्हित पूर्णांक otx2_n_drv_stats = ARRAY_SIZE(otx2_drv_stats);
अटल स्थिर अचिन्हित पूर्णांक otx2_n_queue_stats = ARRAY_SIZE(otx2_queue_stats);

अटल काष्ठा cgx_fw_data *otx2_get_fwdata(काष्ठा otx2_nic *pfvf);

अटल व्योम otx2_get_drvinfo(काष्ठा net_device *netdev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(pfvf->pdev), माप(info->bus_info));
पूर्ण

अटल व्योम otx2_get_qset_strings(काष्ठा otx2_nic *pfvf, u8 **data, पूर्णांक qset)
अणु
	पूर्णांक start_qidx = qset * pfvf->hw.rx_queues;
	पूर्णांक qidx, stats;

	क्रम (qidx = 0; qidx < pfvf->hw.rx_queues; qidx++) अणु
		क्रम (stats = 0; stats < otx2_n_queue_stats; stats++) अणु
			प्र_लिखो(*data, "rxq%d: %s", qidx + start_qidx,
				otx2_queue_stats[stats].name);
			*data += ETH_GSTRING_LEN;
		पूर्ण
	पूर्ण
	क्रम (qidx = 0; qidx < pfvf->hw.tx_queues; qidx++) अणु
		क्रम (stats = 0; stats < otx2_n_queue_stats; stats++) अणु
			प्र_लिखो(*data, "txq%d: %s", qidx + start_qidx,
				otx2_queue_stats[stats].name);
			*data += ETH_GSTRING_LEN;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम otx2_get_strings(काष्ठा net_device *netdev, u32 sset, u8 *data)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	पूर्णांक stats;

	अगर (sset != ETH_SS_STATS)
		वापस;

	क्रम (stats = 0; stats < otx2_n_dev_stats; stats++) अणु
		स_नकल(data, otx2_dev_stats[stats].name, ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (stats = 0; stats < otx2_n_drv_stats; stats++) अणु
		स_नकल(data, otx2_drv_stats[stats].name, ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण

	otx2_get_qset_strings(pfvf, &data, 0);

	क्रम (stats = 0; stats < CGX_RX_STATS_COUNT; stats++) अणु
		प्र_लिखो(data, "cgx_rxstat%d: ", stats);
		data += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (stats = 0; stats < CGX_TX_STATS_COUNT; stats++) अणु
		प्र_लिखो(data, "cgx_txstat%d: ", stats);
		data += ETH_GSTRING_LEN;
	पूर्ण

	म_नकल(data, "reset_count");
	data += ETH_GSTRING_LEN;
	प्र_लिखो(data, "Fec Corrected Errors: ");
	data += ETH_GSTRING_LEN;
	प्र_लिखो(data, "Fec Uncorrected Errors: ");
	data += ETH_GSTRING_LEN;
पूर्ण

अटल व्योम otx2_get_qset_stats(काष्ठा otx2_nic *pfvf,
				काष्ठा ethtool_stats *stats, u64 **data)
अणु
	पूर्णांक stat, qidx;

	अगर (!pfvf)
		वापस;
	क्रम (qidx = 0; qidx < pfvf->hw.rx_queues; qidx++) अणु
		अगर (!otx2_update_rq_stats(pfvf, qidx)) अणु
			क्रम (stat = 0; stat < otx2_n_queue_stats; stat++)
				*((*data)++) = 0;
			जारी;
		पूर्ण
		क्रम (stat = 0; stat < otx2_n_queue_stats; stat++)
			*((*data)++) = ((u64 *)&pfvf->qset.rq[qidx].stats)
				[otx2_queue_stats[stat].index];
	पूर्ण

	क्रम (qidx = 0; qidx < pfvf->hw.tx_queues; qidx++) अणु
		अगर (!otx2_update_sq_stats(pfvf, qidx)) अणु
			क्रम (stat = 0; stat < otx2_n_queue_stats; stat++)
				*((*data)++) = 0;
			जारी;
		पूर्ण
		क्रम (stat = 0; stat < otx2_n_queue_stats; stat++)
			*((*data)++) = ((u64 *)&pfvf->qset.sq[qidx].stats)
				[otx2_queue_stats[stat].index];
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_get_phy_fec_stats(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा msg_req *req;
	पूर्णांक rc = -ENOMEM;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_cgx_get_phy_fec_stats(&pfvf->mbox);
	अगर (!req)
		जाओ end;

	अगर (!otx2_sync_mbox_msg(&pfvf->mbox))
		rc = 0;
end:
	mutex_unlock(&pfvf->mbox.lock);
	वापस rc;
पूर्ण

/* Get device and per queue statistics */
अटल व्योम otx2_get_ethtool_stats(काष्ठा net_device *netdev,
				   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	u64 fec_corr_blks, fec_uncorr_blks;
	काष्ठा cgx_fw_data *rsp;
	पूर्णांक stat;

	otx2_get_dev_stats(pfvf);
	क्रम (stat = 0; stat < otx2_n_dev_stats; stat++)
		*(data++) = ((u64 *)&pfvf->hw.dev_stats)
				[otx2_dev_stats[stat].index];

	क्रम (stat = 0; stat < otx2_n_drv_stats; stat++)
		*(data++) = atomic_पढ़ो(&((atomic_t *)&pfvf->hw.drv_stats)
						[otx2_drv_stats[stat].index]);

	otx2_get_qset_stats(pfvf, stats, &data);
	otx2_update_lmac_stats(pfvf);
	क्रम (stat = 0; stat < CGX_RX_STATS_COUNT; stat++)
		*(data++) = pfvf->hw.cgx_rx_stats[stat];
	क्रम (stat = 0; stat < CGX_TX_STATS_COUNT; stat++)
		*(data++) = pfvf->hw.cgx_tx_stats[stat];
	*(data++) = pfvf->reset_count;

	fec_corr_blks = pfvf->hw.cgx_fec_corr_blks;
	fec_uncorr_blks = pfvf->hw.cgx_fec_uncorr_blks;

	rsp = otx2_get_fwdata(pfvf);
	अगर (!IS_ERR(rsp) && rsp->fwdata.phy.misc.has_fec_stats &&
	    !otx2_get_phy_fec_stats(pfvf)) अणु
		/* Fetch fwdata again because it's been recently populated with
		 * latest PHY FEC stats.
		 */
		rsp = otx2_get_fwdata(pfvf);
		अगर (!IS_ERR(rsp)) अणु
			काष्ठा fec_stats_s *p = &rsp->fwdata.phy.fec_stats;

			अगर (pfvf->linfo.fec == OTX2_FEC_BASER) अणु
				fec_corr_blks   = p->brfec_corr_blks;
				fec_uncorr_blks = p->brfec_uncorr_blks;
			पूर्ण अन्यथा अणु
				fec_corr_blks   = p->rsfec_corr_cws;
				fec_uncorr_blks = p->rsfec_uncorr_cws;
			पूर्ण
		पूर्ण
	पूर्ण

	*(data++) = fec_corr_blks;
	*(data++) = fec_uncorr_blks;
पूर्ण

अटल पूर्णांक otx2_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	पूर्णांक qstats_count;

	अगर (sset != ETH_SS_STATS)
		वापस -EINVAL;

	qstats_count = otx2_n_queue_stats *
		       (pfvf->hw.rx_queues + pfvf->hw.tx_queues);
	otx2_update_lmac_fec_stats(pfvf);

	वापस otx2_n_dev_stats + otx2_n_drv_stats + qstats_count +
	       CGX_RX_STATS_COUNT + CGX_TX_STATS_COUNT + OTX2_FEC_STATS_CNT
	       + 1;
पूर्ण

/* Get no of queues device supports and current queue count */
अटल व्योम otx2_get_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *channel)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(dev);

	channel->max_rx = pfvf->hw.max_queues;
	channel->max_tx = pfvf->hw.max_queues;

	channel->rx_count = pfvf->hw.rx_queues;
	channel->tx_count = pfvf->hw.tx_queues;
पूर्ण

/* Set no of Tx, Rx queues to be used */
अटल पूर्णांक otx2_set_channels(काष्ठा net_device *dev,
			     काष्ठा ethtool_channels *channel)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(dev);
	bool अगर_up = netअगर_running(dev);
	पूर्णांक err = 0;

	अगर (!channel->rx_count || !channel->tx_count)
		वापस -EINVAL;

	अगर (अगर_up)
		dev->netdev_ops->nकरो_stop(dev);

	err = otx2_set_real_num_queues(dev, channel->tx_count,
				       channel->rx_count);
	अगर (err)
		जाओ fail;

	pfvf->hw.rx_queues = channel->rx_count;
	pfvf->hw.tx_queues = channel->tx_count;
	pfvf->qset.cq_cnt = pfvf->hw.tx_queues +  pfvf->hw.rx_queues;

fail:
	अगर (अगर_up)
		dev->netdev_ops->nकरो_खोलो(dev);

	netdev_info(dev, "Setting num Tx rings to %d, Rx rings to %d success\n",
		    pfvf->hw.tx_queues, pfvf->hw.rx_queues);

	वापस err;
पूर्ण

अटल व्योम otx2_get_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा cgx_छोड़ो_frm_cfg *req, *rsp;

	अगर (is_otx2_lbkvf(pfvf->pdev))
		वापस;

	req = otx2_mbox_alloc_msg_cgx_cfg_छोड़ो_frm(&pfvf->mbox);
	अगर (!req)
		वापस;

	अगर (!otx2_sync_mbox_msg(&pfvf->mbox)) अणु
		rsp = (काष्ठा cgx_छोड़ो_frm_cfg *)
		       otx2_mbox_get_rsp(&pfvf->mbox.mbox, 0, &req->hdr);
		छोड़ो->rx_छोड़ो = rsp->rx_छोड़ो;
		छोड़ो->tx_छोड़ो = rsp->tx_छोड़ो;
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_set_छोड़ोparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);

	अगर (छोड़ो->स्वतःneg)
		वापस -EOPNOTSUPP;

	अगर (is_otx2_lbkvf(pfvf->pdev))
		वापस -EOPNOTSUPP;

	अगर (छोड़ो->rx_छोड़ो)
		pfvf->flags |= OTX2_FLAG_RX_PAUSE_ENABLED;
	अन्यथा
		pfvf->flags &= ~OTX2_FLAG_RX_PAUSE_ENABLED;

	अगर (छोड़ो->tx_छोड़ो)
		pfvf->flags |= OTX2_FLAG_TX_PAUSE_ENABLED;
	अन्यथा
		pfvf->flags &= ~OTX2_FLAG_TX_PAUSE_ENABLED;

	वापस otx2_config_छोड़ो_frm(pfvf);
पूर्ण

अटल व्योम otx2_get_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा otx2_qset *qs = &pfvf->qset;

	ring->rx_max_pending = Q_COUNT(Q_SIZE_MAX);
	ring->rx_pending = qs->rqe_cnt ? qs->rqe_cnt : Q_COUNT(Q_SIZE_256);
	ring->tx_max_pending = Q_COUNT(Q_SIZE_MAX);
	ring->tx_pending = qs->sqe_cnt ? qs->sqe_cnt : Q_COUNT(Q_SIZE_4K);
पूर्ण

अटल पूर्णांक otx2_set_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	bool अगर_up = netअगर_running(netdev);
	काष्ठा otx2_qset *qs = &pfvf->qset;
	u32 rx_count, tx_count;

	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending)
		वापस -EINVAL;

	/* Permitted lengths are 16 64 256 1K 4K 16K 64K 256K 1M  */
	rx_count = ring->rx_pending;
	/* On some silicon variants a skid or reserved CQEs are
	 * needed to aव्योम CQ overflow.
	 */
	अगर (rx_count < pfvf->hw.rq_skid)
		rx_count =  pfvf->hw.rq_skid;
	rx_count = Q_COUNT(Q_SIZE(rx_count, 3));

	/* Due pipelining impact minimum 2000 unused SQ CQE's
	 * need to be मुख्यtained to aव्योम CQ overflow, hence the
	 * minimum 4K size.
	 */
	tx_count = clamp_t(u32, ring->tx_pending,
			   Q_COUNT(Q_SIZE_4K), Q_COUNT(Q_SIZE_MAX));
	tx_count = Q_COUNT(Q_SIZE(tx_count, 3));

	अगर (tx_count == qs->sqe_cnt && rx_count == qs->rqe_cnt)
		वापस 0;

	अगर (अगर_up)
		netdev->netdev_ops->nकरो_stop(netdev);

	/* Asचिन्हित to the nearest possible exponent. */
	qs->sqe_cnt = tx_count;
	qs->rqe_cnt = rx_count;

	अगर (अगर_up)
		netdev->netdev_ops->nकरो_खोलो(netdev);

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_get_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *cmd)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा otx2_hw *hw = &pfvf->hw;

	cmd->rx_coalesce_usecs = hw->cq_समय_रुको;
	cmd->rx_max_coalesced_frames = hw->cq_ecount_रुको;
	cmd->tx_coalesce_usecs = hw->cq_समय_रुको;
	cmd->tx_max_coalesced_frames = hw->cq_ecount_रुको;

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_set_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा otx2_hw *hw = &pfvf->hw;
	पूर्णांक qidx;

	अगर (!ec->rx_max_coalesced_frames || !ec->tx_max_coalesced_frames)
		वापस 0;

	/* 'cq_time_wait' is 8bit and is in multiple of 100ns,
	 * so clamp the user given value to the range of 1 to 25usec.
	 */
	ec->rx_coalesce_usecs = clamp_t(u32, ec->rx_coalesce_usecs,
					1, CQ_TIMER_THRESH_MAX);
	ec->tx_coalesce_usecs = clamp_t(u32, ec->tx_coalesce_usecs,
					1, CQ_TIMER_THRESH_MAX);

	/* Rx and Tx are mapped to same CQ, check which one
	 * is changed, अगर both then choose the min.
	 */
	अगर (hw->cq_समय_रुको == ec->rx_coalesce_usecs)
		hw->cq_समय_रुको = ec->tx_coalesce_usecs;
	अन्यथा अगर (hw->cq_समय_रुको == ec->tx_coalesce_usecs)
		hw->cq_समय_रुको = ec->rx_coalesce_usecs;
	अन्यथा
		hw->cq_समय_रुको = min_t(u8, ec->rx_coalesce_usecs,
					 ec->tx_coalesce_usecs);

	/* Max ecount_रुको supported is 16bit,
	 * so clamp the user given value to the range of 1 to 64k.
	 */
	ec->rx_max_coalesced_frames = clamp_t(u32, ec->rx_max_coalesced_frames,
					      1, U16_MAX);
	ec->tx_max_coalesced_frames = clamp_t(u32, ec->tx_max_coalesced_frames,
					      1, U16_MAX);

	/* Rx and Tx are mapped to same CQ, check which one
	 * is changed, अगर both then choose the min.
	 */
	अगर (hw->cq_ecount_रुको == ec->rx_max_coalesced_frames)
		hw->cq_ecount_रुको = ec->tx_max_coalesced_frames;
	अन्यथा अगर (hw->cq_ecount_रुको == ec->tx_max_coalesced_frames)
		hw->cq_ecount_रुको = ec->rx_max_coalesced_frames;
	अन्यथा
		hw->cq_ecount_रुको = min_t(u16, ec->rx_max_coalesced_frames,
					   ec->tx_max_coalesced_frames);

	अगर (netअगर_running(netdev)) अणु
		क्रम (qidx = 0; qidx < pfvf->hw.cपूर्णांक_cnt; qidx++)
			otx2_config_irq_coalescing(pfvf, qidx);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_get_rss_hash_opts(काष्ठा otx2_nic *pfvf,
				  काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा otx2_rss_info *rss = &pfvf->hw.rss_info;

	अगर (!(rss->flowkey_cfg &
	    (NIX_FLOW_KEY_TYPE_IPV4 | NIX_FLOW_KEY_TYPE_IPV6)))
		वापस 0;

	/* Mimimum is IPv4 and IPv6, SIP/DIP */
	nfc->data = RXH_IP_SRC | RXH_IP_DST;
	अगर (rss->flowkey_cfg & NIX_FLOW_KEY_TYPE_VLAN)
		nfc->data |= RXH_VLAN;

	चयन (nfc->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		अगर (rss->flowkey_cfg & NIX_FLOW_KEY_TYPE_TCP)
			nfc->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		अगर (rss->flowkey_cfg & NIX_FLOW_KEY_TYPE_UDP)
			nfc->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
		अगर (rss->flowkey_cfg & NIX_FLOW_KEY_TYPE_SCTP)
			nfc->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल AH_ESP_V4_FLOW:
	हाल AH_ESP_V6_FLOW:
		अगर (rss->flowkey_cfg & NIX_FLOW_KEY_TYPE_ESP)
			nfc->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल IPV4_FLOW:
		अवरोध;
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल IPV6_FLOW:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_set_rss_hash_opts(काष्ठा otx2_nic *pfvf,
				  काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा otx2_rss_info *rss = &pfvf->hw.rss_info;
	u32 rxh_l4 = RXH_L4_B_0_1 | RXH_L4_B_2_3;
	u32 rss_cfg = rss->flowkey_cfg;

	अगर (!rss->enable) अणु
		netdev_err(pfvf->netdev,
			   "RSS is disabled, cannot change settings\n");
		वापस -EIO;
	पूर्ण

	/* Mimimum is IPv4 and IPv6, SIP/DIP */
	अगर (!(nfc->data & RXH_IP_SRC) || !(nfc->data & RXH_IP_DST))
		वापस -EINVAL;

	अगर (nfc->data & RXH_VLAN)
		rss_cfg |=  NIX_FLOW_KEY_TYPE_VLAN;
	अन्यथा
		rss_cfg &= ~NIX_FLOW_KEY_TYPE_VLAN;

	चयन (nfc->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		/* Dअगरferent config क्रम v4 and v6 is not supported.
		 * Both of them have to be either 4-tuple or 2-tuple.
		 */
		चयन (nfc->data & rxh_l4) अणु
		हाल 0:
			rss_cfg &= ~NIX_FLOW_KEY_TYPE_TCP;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			rss_cfg |= NIX_FLOW_KEY_TYPE_TCP;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		चयन (nfc->data & rxh_l4) अणु
		हाल 0:
			rss_cfg &= ~NIX_FLOW_KEY_TYPE_UDP;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			rss_cfg |= NIX_FLOW_KEY_TYPE_UDP;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
		चयन (nfc->data & rxh_l4) अणु
		हाल 0:
			rss_cfg &= ~NIX_FLOW_KEY_TYPE_SCTP;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			rss_cfg |= NIX_FLOW_KEY_TYPE_SCTP;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल AH_ESP_V4_FLOW:
	हाल AH_ESP_V6_FLOW:
		चयन (nfc->data & rxh_l4) अणु
		हाल 0:
			rss_cfg &= ~(NIX_FLOW_KEY_TYPE_ESP |
				     NIX_FLOW_KEY_TYPE_AH);
			rss_cfg |= NIX_FLOW_KEY_TYPE_VLAN |
				   NIX_FLOW_KEY_TYPE_IPV4_PROTO;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			/* If VLAN hashing is also requested क्रम ESP then करो not
			 * allow because of hardware 40 bytes flow key limit.
			 */
			अगर (rss_cfg & NIX_FLOW_KEY_TYPE_VLAN) अणु
				netdev_err(pfvf->netdev,
					   "RSS hash of ESP or AH with VLAN is not supported\n");
				वापस -EOPNOTSUPP;
			पूर्ण

			rss_cfg |= NIX_FLOW_KEY_TYPE_ESP | NIX_FLOW_KEY_TYPE_AH;
			/* Disable IPv4 proto hashing since IPv6 SA+DA(32 bytes)
			 * and ESP SPI+sequence(8 bytes) uses hardware maximum
			 * limit of 40 byte flow key.
			 */
			rss_cfg &= ~NIX_FLOW_KEY_TYPE_IPV4_PROTO;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		rss_cfg = NIX_FLOW_KEY_TYPE_IPV4 | NIX_FLOW_KEY_TYPE_IPV6;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rss->flowkey_cfg = rss_cfg;
	otx2_set_flowkey_cfg(pfvf);
	वापस 0;
पूर्ण

अटल पूर्णांक otx2_get_rxnfc(काष्ठा net_device *dev,
			  काष्ठा ethtool_rxnfc *nfc, u32 *rules)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (nfc->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		nfc->data = pfvf->hw.rx_queues;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		nfc->rule_cnt = pfvf->flow_cfg->nr_flows;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = otx2_get_flow(pfvf, nfc,  nfc->fs.location);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		ret = otx2_get_all_flows(pfvf, nfc, rules);
		अवरोध;
	हाल ETHTOOL_GRXFH:
		वापस otx2_get_rss_hash_opts(pfvf, nfc);
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक otx2_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *nfc)
अणु
	bool ntuple = !!(dev->features & NETIF_F_NTUPLE);
	काष्ठा otx2_nic *pfvf = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (nfc->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = otx2_set_rss_hash_opts(pfvf, nfc);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLINS:
		अगर (netअगर_running(dev) && ntuple)
			ret = otx2_add_flow(pfvf, nfc);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		अगर (netअगर_running(dev) && ntuple)
			ret = otx2_हटाओ_flow(pfvf, nfc->fs.location);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक otx2vf_get_rxnfc(काष्ठा net_device *dev,
			    काष्ठा ethtool_rxnfc *nfc, u32 *rules)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (nfc->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		nfc->data = pfvf->hw.rx_queues;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXFH:
		वापस otx2_get_rss_hash_opts(pfvf, nfc);
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक otx2vf_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (nfc->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = otx2_set_rss_hash_opts(pfvf, nfc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 otx2_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा otx2_rss_info *rss;

	rss = &pfvf->hw.rss_info;

	वापस माप(rss->key);
पूर्ण

अटल u32 otx2_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	वापस  MAX_RSS_INसूची_TBL_SIZE;
पूर्ण

अटल पूर्णांक otx2_rss_ctx_delete(काष्ठा otx2_nic *pfvf, पूर्णांक ctx_id)
अणु
	काष्ठा otx2_rss_info *rss = &pfvf->hw.rss_info;

	otx2_rss_ctx_flow_del(pfvf, ctx_id);
	kमुक्त(rss->rss_ctx[ctx_id]);
	rss->rss_ctx[ctx_id] = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_rss_ctx_create(काष्ठा otx2_nic *pfvf,
			       u32 *rss_context)
अणु
	काष्ठा otx2_rss_info *rss = &pfvf->hw.rss_info;
	u8 ctx;

	क्रम (ctx = 0; ctx < MAX_RSS_GROUPS; ctx++) अणु
		अगर (!rss->rss_ctx[ctx])
			अवरोध;
	पूर्ण
	अगर (ctx == MAX_RSS_GROUPS)
		वापस -EINVAL;

	rss->rss_ctx[ctx] = kzalloc(माप(*rss->rss_ctx[ctx]), GFP_KERNEL);
	अगर (!rss->rss_ctx[ctx])
		वापस -ENOMEM;
	*rss_context = ctx;

	वापस 0;
पूर्ण

/* RSS context configuration */
अटल पूर्णांक otx2_set_rxfh_context(काष्ठा net_device *dev, स्थिर u32 *indir,
				 स्थिर u8 *hkey, स्थिर u8 hfunc,
				 u32 *rss_context, bool delete)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(dev);
	काष्ठा otx2_rss_ctx *rss_ctx;
	काष्ठा otx2_rss_info *rss;
	पूर्णांक ret, idx;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	अगर (*rss_context != ETH_RXFH_CONTEXT_ALLOC &&
	    *rss_context >= MAX_RSS_GROUPS)
		वापस -EINVAL;

	rss = &pfvf->hw.rss_info;

	अगर (!rss->enable) अणु
		netdev_err(dev, "RSS is disabled, cannot change settings\n");
		वापस -EIO;
	पूर्ण

	अगर (hkey) अणु
		स_नकल(rss->key, hkey, माप(rss->key));
		otx2_set_rss_key(pfvf);
	पूर्ण
	अगर (delete)
		वापस otx2_rss_ctx_delete(pfvf, *rss_context);

	अगर (*rss_context == ETH_RXFH_CONTEXT_ALLOC) अणु
		ret = otx2_rss_ctx_create(pfvf, rss_context);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (indir) अणु
		rss_ctx = rss->rss_ctx[*rss_context];
		क्रम (idx = 0; idx < rss->rss_size; idx++)
			rss_ctx->ind_tbl[idx] = indir[idx];
	पूर्ण
	otx2_set_rss_table(pfvf, *rss_context);

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_get_rxfh_context(काष्ठा net_device *dev, u32 *indir,
				 u8 *hkey, u8 *hfunc, u32 rss_context)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(dev);
	काष्ठा otx2_rss_ctx *rss_ctx;
	काष्ठा otx2_rss_info *rss;
	पूर्णांक idx, rx_queues;

	rss = &pfvf->hw.rss_info;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	अगर (!indir)
		वापस 0;

	अगर (!rss->enable && rss_context == DEFAULT_RSS_CONTEXT_GROUP) अणु
		rx_queues = pfvf->hw.rx_queues;
		क्रम (idx = 0; idx < MAX_RSS_INसूची_TBL_SIZE; idx++)
			indir[idx] = ethtool_rxfh_indir_शेष(idx, rx_queues);
		वापस 0;
	पूर्ण
	अगर (rss_context >= MAX_RSS_GROUPS)
		वापस -ENOENT;

	rss_ctx = rss->rss_ctx[rss_context];
	अगर (!rss_ctx)
		वापस -ENOENT;

	अगर (indir) अणु
		क्रम (idx = 0; idx < rss->rss_size; idx++)
			indir[idx] = rss_ctx->ind_tbl[idx];
	पूर्ण
	अगर (hkey)
		स_नकल(hkey, rss->key, माप(rss->key));

	वापस 0;
पूर्ण

/* Get RSS configuration */
अटल पूर्णांक otx2_get_rxfh(काष्ठा net_device *dev, u32 *indir,
			 u8 *hkey, u8 *hfunc)
अणु
	वापस otx2_get_rxfh_context(dev, indir, hkey, hfunc,
				     DEFAULT_RSS_CONTEXT_GROUP);
पूर्ण

/* Configure RSS table and hash key */
अटल पूर्णांक otx2_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
			 स्थिर u8 *hkey, स्थिर u8 hfunc)
अणु

	u32 rss_context = DEFAULT_RSS_CONTEXT_GROUP;

	वापस otx2_set_rxfh_context(dev, indir, hkey, hfunc, &rss_context, 0);
पूर्ण

अटल u32 otx2_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);

	वापस pfvf->msg_enable;
पूर्ण

अटल व्योम otx2_set_msglevel(काष्ठा net_device *netdev, u32 val)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);

	pfvf->msg_enable = val;
पूर्ण

अटल u32 otx2_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);

	/* LBK link is पूर्णांकernal and always UP */
	अगर (is_otx2_lbkvf(pfvf->pdev))
		वापस 1;
	वापस pfvf->linfo.link_up;
पूर्ण

अटल पूर्णांक otx2_get_ts_info(काष्ठा net_device *netdev,
			    काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);

	अगर (!pfvf->ptp)
		वापस ethtool_op_get_ts_info(netdev, info);

	info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE |
				SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	info->phc_index = otx2_ptp_घड़ी_index(pfvf);

	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);

	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_ALL);

	वापस 0;
पूर्ण

अटल काष्ठा cgx_fw_data *otx2_get_fwdata(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा cgx_fw_data *rsp = शून्य;
	काष्ठा msg_req *req;
	पूर्णांक err = 0;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_cgx_get_aux_link_info(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (!err) अणु
		rsp = (काष्ठा cgx_fw_data *)
			otx2_mbox_get_rsp(&pfvf->mbox.mbox, 0, &req->hdr);
	पूर्ण अन्यथा अणु
		rsp = ERR_PTR(err);
	पूर्ण

	mutex_unlock(&pfvf->mbox.lock);
	वापस rsp;
पूर्ण

अटल पूर्णांक otx2_get_fecparam(काष्ठा net_device *netdev,
			     काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा cgx_fw_data *rsp;
	स्थिर पूर्णांक fec[] = अणु
		ETHTOOL_FEC_OFF,
		ETHTOOL_FEC_BASER,
		ETHTOOL_FEC_RS,
		ETHTOOL_FEC_BASER | ETHTOOL_FEC_RSपूर्ण;
#घोषणा FEC_MAX_INDEX 4
	अगर (pfvf->linfo.fec < FEC_MAX_INDEX)
		fecparam->active_fec = fec[pfvf->linfo.fec];

	rsp = otx2_get_fwdata(pfvf);
	अगर (IS_ERR(rsp))
		वापस PTR_ERR(rsp);

	अगर (rsp->fwdata.supported_fec < FEC_MAX_INDEX) अणु
		अगर (!rsp->fwdata.supported_fec)
			fecparam->fec = ETHTOOL_FEC_NONE;
		अन्यथा
			fecparam->fec = fec[rsp->fwdata.supported_fec];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक otx2_set_fecparam(काष्ठा net_device *netdev,
			     काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा mbox *mbox = &pfvf->mbox;
	काष्ठा fec_mode *req, *rsp;
	पूर्णांक err = 0, fec = 0;

	चयन (fecparam->fec) अणु
	/* Firmware करोes not support AUTO mode consider it as FEC_OFF */
	हाल ETHTOOL_FEC_OFF:
	हाल ETHTOOL_FEC_AUTO:
		fec = OTX2_FEC_OFF;
		अवरोध;
	हाल ETHTOOL_FEC_RS:
		fec = OTX2_FEC_RS;
		अवरोध;
	हाल ETHTOOL_FEC_BASER:
		fec = OTX2_FEC_BASER;
		अवरोध;
	शेष:
		netdev_warn(pfvf->netdev, "Unsupported FEC mode: %d",
			    fecparam->fec);
		वापस -EINVAL;
	पूर्ण

	अगर (fec == pfvf->linfo.fec)
		वापस 0;

	mutex_lock(&mbox->lock);
	req = otx2_mbox_alloc_msg_cgx_set_fec_param(&pfvf->mbox);
	अगर (!req) अणु
		err = -ENOMEM;
		जाओ end;
	पूर्ण
	req->fec = fec;
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err)
		जाओ end;

	rsp = (काष्ठा fec_mode *)otx2_mbox_get_rsp(&pfvf->mbox.mbox,
						   0, &req->hdr);
	अगर (rsp->fec >= 0)
		pfvf->linfo.fec = rsp->fec;
	अन्यथा
		err = rsp->fec;
end:
	mutex_unlock(&mbox->lock);
	वापस err;
पूर्ण

अटल व्योम otx2_get_fec_info(u64 index, पूर्णांक req_mode,
			      काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(otx2_fec_modes) = अणु 0, पूर्ण;

	चयन (index) अणु
	हाल OTX2_FEC_NONE:
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_NONE_BIT,
				 otx2_fec_modes);
		अवरोध;
	हाल OTX2_FEC_BASER:
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_BASER_BIT,
				 otx2_fec_modes);
		अवरोध;
	हाल OTX2_FEC_RS:
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_RS_BIT,
				 otx2_fec_modes);
		अवरोध;
	हाल OTX2_FEC_BASER | OTX2_FEC_RS:
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_BASER_BIT,
				 otx2_fec_modes);
		linkmode_set_bit(ETHTOOL_LINK_MODE_FEC_RS_BIT,
				 otx2_fec_modes);
		अवरोध;
	पूर्ण

	/* Add fec modes to existing modes */
	अगर (req_mode == OTX2_MODE_ADVERTISED)
		linkmode_or(link_ksettings->link_modes.advertising,
			    link_ksettings->link_modes.advertising,
			    otx2_fec_modes);
	अन्यथा
		linkmode_or(link_ksettings->link_modes.supported,
			    link_ksettings->link_modes.supported,
			    otx2_fec_modes);
पूर्ण

अटल व्योम otx2_get_link_mode_info(u64 link_mode_bmap,
				    bool req_mode,
				    काष्ठा ethtool_link_ksettings
				    *link_ksettings)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(otx2_link_modes) = अणु 0, पूर्ण;
	स्थिर पूर्णांक otx2_sgmii_features[6] = अणु
		ETHTOOL_LINK_MODE_10baseT_Half_BIT,
		ETHTOOL_LINK_MODE_10baseT_Full_BIT,
		ETHTOOL_LINK_MODE_100baseT_Half_BIT,
		ETHTOOL_LINK_MODE_100baseT_Full_BIT,
		ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
		ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
	पूर्ण;
	/* CGX link modes to Ethtool link mode mapping */
	स्थिर पूर्णांक cgx_link_mode[27] = अणु
		0, /* SGMII  Mode */
		ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
		ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
		ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
		ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
		ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
		0,
		ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
		0,
		0,
		ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
		ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
		ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
		ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT,
		ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
		ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
		0,
		ETHTOOL_LINK_MODE_50000baseSR_Full_BIT,
		0,
		ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT,
		ETHTOOL_LINK_MODE_50000baseCR_Full_BIT,
		ETHTOOL_LINK_MODE_50000baseKR_Full_BIT,
		0,
		ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
		ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT,
		ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
		ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT
	पूर्ण;
	u8 bit;

	link_mode_bmap = link_mode_bmap & OTX2_ETHTOOL_SUPPORTED_MODES;

	क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&link_mode_bmap, 27) अणु
		/* SGMII mode is set */
		अगर (bit == 0)
			linkmode_set_bit_array(otx2_sgmii_features,
					       ARRAY_SIZE(otx2_sgmii_features),
					       otx2_link_modes);
		अन्यथा
			linkmode_set_bit(cgx_link_mode[bit], otx2_link_modes);
	पूर्ण

	अगर (req_mode == OTX2_MODE_ADVERTISED)
		linkmode_copy(link_ksettings->link_modes.advertising,
			      otx2_link_modes);
	अन्यथा
		linkmode_copy(link_ksettings->link_modes.supported,
			      otx2_link_modes);
पूर्ण

अटल पूर्णांक otx2_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा cgx_fw_data *rsp = शून्य;

	cmd->base.duplex  = pfvf->linfo.full_duplex;
	cmd->base.speed   = pfvf->linfo.speed;
	cmd->base.स्वतःneg = pfvf->linfo.an;

	rsp = otx2_get_fwdata(pfvf);
	अगर (IS_ERR(rsp))
		वापस PTR_ERR(rsp);

	अगर (rsp->fwdata.supported_an)
		ethtool_link_ksettings_add_link_mode(cmd,
						     supported,
						     Autoneg);

	otx2_get_link_mode_info(rsp->fwdata.advertised_link_modes,
				OTX2_MODE_ADVERTISED, cmd);
	otx2_get_fec_info(rsp->fwdata.advertised_fec,
			  OTX2_MODE_ADVERTISED, cmd);
	otx2_get_link_mode_info(rsp->fwdata.supported_link_modes,
				OTX2_MODE_SUPPORTED, cmd);
	otx2_get_fec_info(rsp->fwdata.supported_fec,
			  OTX2_MODE_SUPPORTED, cmd);
	वापस 0;
पूर्ण

अटल व्योम otx2_get_advertised_mode(स्थिर काष्ठा ethtool_link_ksettings *cmd,
				     u64 *mode)
अणु
	u32 bit_pos;

	/* Firmware करोes not support requesting multiple advertised modes
	 * वापस first set bit
	 */
	bit_pos = find_first_bit(cmd->link_modes.advertising,
				 __ETHTOOL_LINK_MODE_MASK_NBITS);
	अगर (bit_pos != __ETHTOOL_LINK_MODE_MASK_NBITS)
		*mode = bit_pos;
पूर्ण

अटल पूर्णांक otx2_set_link_ksettings(काष्ठा net_device *netdev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा otx2_nic *pf = netdev_priv(netdev);
	काष्ठा ethtool_link_ksettings cur_ks;
	काष्ठा cgx_set_link_mode_req *req;
	काष्ठा mbox *mbox = &pf->mbox;
	पूर्णांक err = 0;

	स_रखो(&cur_ks, 0, माप(काष्ठा ethtool_link_ksettings));

	अगर (!ethtool_validate_speed(cmd->base.speed) ||
	    !ethtool_validate_duplex(cmd->base.duplex))
		वापस -EINVAL;

	अगर (cmd->base.स्वतःneg != AUTONEG_ENABLE &&
	    cmd->base.स्वतःneg != AUTONEG_DISABLE)
		वापस -EINVAL;

	otx2_get_link_ksettings(netdev, &cur_ks);

	/* Check requested modes against supported modes by hardware */
	अगर (!biपंचांगap_subset(cmd->link_modes.advertising,
			   cur_ks.link_modes.supported,
			   __ETHTOOL_LINK_MODE_MASK_NBITS))
		वापस -EINVAL;

	mutex_lock(&mbox->lock);
	req = otx2_mbox_alloc_msg_cgx_set_link_mode(&pf->mbox);
	अगर (!req) अणु
		err = -ENOMEM;
		जाओ end;
	पूर्ण

	req->args.speed = cmd->base.speed;
	/* firmware expects 1 क्रम half duplex and 0 क्रम full duplex
	 * hence inverting
	 */
	req->args.duplex = cmd->base.duplex ^ 0x1;
	req->args.an = cmd->base.स्वतःneg;
	otx2_get_advertised_mode(cmd, &req->args.mode);

	err = otx2_sync_mbox_msg(&pf->mbox);
end:
	mutex_unlock(&mbox->lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops otx2_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_link		= otx2_get_link,
	.get_drvinfo		= otx2_get_drvinfo,
	.get_strings		= otx2_get_strings,
	.get_ethtool_stats	= otx2_get_ethtool_stats,
	.get_sset_count		= otx2_get_sset_count,
	.set_channels		= otx2_set_channels,
	.get_channels		= otx2_get_channels,
	.get_ringparam		= otx2_get_ringparam,
	.set_ringparam		= otx2_set_ringparam,
	.get_coalesce		= otx2_get_coalesce,
	.set_coalesce		= otx2_set_coalesce,
	.get_rxnfc		= otx2_get_rxnfc,
	.set_rxnfc              = otx2_set_rxnfc,
	.get_rxfh_key_size	= otx2_get_rxfh_key_size,
	.get_rxfh_indir_size	= otx2_get_rxfh_indir_size,
	.get_rxfh		= otx2_get_rxfh,
	.set_rxfh		= otx2_set_rxfh,
	.get_rxfh_context	= otx2_get_rxfh_context,
	.set_rxfh_context	= otx2_set_rxfh_context,
	.get_msglevel		= otx2_get_msglevel,
	.set_msglevel		= otx2_set_msglevel,
	.get_छोड़ोparam		= otx2_get_छोड़ोparam,
	.set_छोड़ोparam		= otx2_set_छोड़ोparam,
	.get_ts_info		= otx2_get_ts_info,
	.get_fecparam		= otx2_get_fecparam,
	.set_fecparam		= otx2_set_fecparam,
	.get_link_ksettings     = otx2_get_link_ksettings,
	.set_link_ksettings     = otx2_set_link_ksettings,
पूर्ण;

व्योम otx2_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &otx2_ethtool_ops;
पूर्ण

/* VF's ethtool APIs */
अटल व्योम otx2vf_get_drvinfo(काष्ठा net_device *netdev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा otx2_nic *vf = netdev_priv(netdev);

	strlcpy(info->driver, DRV_VF_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(vf->pdev), माप(info->bus_info));
पूर्ण

अटल व्योम otx2vf_get_strings(काष्ठा net_device *netdev, u32 sset, u8 *data)
अणु
	काष्ठा otx2_nic *vf = netdev_priv(netdev);
	पूर्णांक stats;

	अगर (sset != ETH_SS_STATS)
		वापस;

	क्रम (stats = 0; stats < otx2_n_dev_stats; stats++) अणु
		स_नकल(data, otx2_dev_stats[stats].name, ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (stats = 0; stats < otx2_n_drv_stats; stats++) अणु
		स_नकल(data, otx2_drv_stats[stats].name, ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण

	otx2_get_qset_strings(vf, &data, 0);

	म_नकल(data, "reset_count");
	data += ETH_GSTRING_LEN;
पूर्ण

अटल व्योम otx2vf_get_ethtool_stats(काष्ठा net_device *netdev,
				     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा otx2_nic *vf = netdev_priv(netdev);
	पूर्णांक stat;

	otx2_get_dev_stats(vf);
	क्रम (stat = 0; stat < otx2_n_dev_stats; stat++)
		*(data++) = ((u64 *)&vf->hw.dev_stats)
				[otx2_dev_stats[stat].index];

	क्रम (stat = 0; stat < otx2_n_drv_stats; stat++)
		*(data++) = atomic_पढ़ो(&((atomic_t *)&vf->hw.drv_stats)
						[otx2_drv_stats[stat].index]);

	otx2_get_qset_stats(vf, stats, &data);
	*(data++) = vf->reset_count;
पूर्ण

अटल पूर्णांक otx2vf_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा otx2_nic *vf = netdev_priv(netdev);
	पूर्णांक qstats_count;

	अगर (sset != ETH_SS_STATS)
		वापस -EINVAL;

	qstats_count = otx2_n_queue_stats *
		       (vf->hw.rx_queues + vf->hw.tx_queues);

	वापस otx2_n_dev_stats + otx2_n_drv_stats + qstats_count + 1;
पूर्ण

अटल पूर्णांक otx2vf_get_link_ksettings(काष्ठा net_device *netdev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);

	अगर (is_otx2_lbkvf(pfvf->pdev)) अणु
		cmd->base.duplex = DUPLEX_FULL;
		cmd->base.speed = SPEED_100000;
	पूर्ण अन्यथा अणु
		वापस otx2_get_link_ksettings(netdev, cmd);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops otx2vf_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_link		= otx2_get_link,
	.get_drvinfo		= otx2vf_get_drvinfo,
	.get_strings		= otx2vf_get_strings,
	.get_ethtool_stats	= otx2vf_get_ethtool_stats,
	.get_sset_count		= otx2vf_get_sset_count,
	.set_channels		= otx2_set_channels,
	.get_channels		= otx2_get_channels,
	.get_rxnfc		= otx2vf_get_rxnfc,
	.set_rxnfc              = otx2vf_set_rxnfc,
	.get_rxfh_key_size	= otx2_get_rxfh_key_size,
	.get_rxfh_indir_size	= otx2_get_rxfh_indir_size,
	.get_rxfh		= otx2_get_rxfh,
	.set_rxfh		= otx2_set_rxfh,
	.get_rxfh_context	= otx2_get_rxfh_context,
	.set_rxfh_context	= otx2_set_rxfh_context,
	.get_ringparam		= otx2_get_ringparam,
	.set_ringparam		= otx2_set_ringparam,
	.get_coalesce		= otx2_get_coalesce,
	.set_coalesce		= otx2_set_coalesce,
	.get_msglevel		= otx2_get_msglevel,
	.set_msglevel		= otx2_set_msglevel,
	.get_छोड़ोparam		= otx2_get_छोड़ोparam,
	.set_छोड़ोparam		= otx2_set_छोड़ोparam,
	.get_link_ksettings     = otx2vf_get_link_ksettings,
पूर्ण;

व्योम otx2vf_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &otx2vf_ethtool_ops;
पूर्ण
EXPORT_SYMBOL(otx2vf_set_ethtool_ops);
