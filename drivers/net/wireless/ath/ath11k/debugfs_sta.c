<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/vदो_स्मृति.h>

#समावेश "debugfs_sta.h"
#समावेश "core.h"
#समावेश "peer.h"
#समावेश "debug.h"
#समावेश "dp_tx.h"
#समावेश "debugfs_htt_stats.h"

व्योम ath11k_debugfs_sta_add_tx_stats(काष्ठा ath11k_sta *arsta,
				     काष्ठा ath11k_per_peer_tx_stats *peer_stats,
				     u8 legacy_rate_idx)
अणु
	काष्ठा rate_info *txrate = &arsta->txrate;
	काष्ठा ath11k_htt_tx_stats *tx_stats;
	पूर्णांक gi, mcs, bw, nss;

	अगर (!arsta->tx_stats)
		वापस;

	tx_stats = arsta->tx_stats;
	gi = FIELD_GET(RATE_INFO_FLAGS_SHORT_GI, arsta->txrate.flags);
	mcs = txrate->mcs;
	bw = ath11k_mac_mac80211_bw_to_ath11k_bw(txrate->bw);
	nss = txrate->nss - 1;

#घोषणा STATS_OP_FMT(name) tx_stats->stats[ATH11K_STATS_TYPE_##name]

	अगर (txrate->flags & RATE_INFO_FLAGS_HE_MCS) अणु
		STATS_OP_FMT(SUCC).he[0][mcs] += peer_stats->succ_bytes;
		STATS_OP_FMT(SUCC).he[1][mcs] += peer_stats->succ_pkts;
		STATS_OP_FMT(FAIL).he[0][mcs] += peer_stats->failed_bytes;
		STATS_OP_FMT(FAIL).he[1][mcs] += peer_stats->failed_pkts;
		STATS_OP_FMT(RETRY).he[0][mcs] += peer_stats->retry_bytes;
		STATS_OP_FMT(RETRY).he[1][mcs] += peer_stats->retry_pkts;
	पूर्ण अन्यथा अगर (txrate->flags & RATE_INFO_FLAGS_VHT_MCS) अणु
		STATS_OP_FMT(SUCC).vht[0][mcs] += peer_stats->succ_bytes;
		STATS_OP_FMT(SUCC).vht[1][mcs] += peer_stats->succ_pkts;
		STATS_OP_FMT(FAIL).vht[0][mcs] += peer_stats->failed_bytes;
		STATS_OP_FMT(FAIL).vht[1][mcs] += peer_stats->failed_pkts;
		STATS_OP_FMT(RETRY).vht[0][mcs] += peer_stats->retry_bytes;
		STATS_OP_FMT(RETRY).vht[1][mcs] += peer_stats->retry_pkts;
	पूर्ण अन्यथा अगर (txrate->flags & RATE_INFO_FLAGS_MCS) अणु
		STATS_OP_FMT(SUCC).ht[0][mcs] += peer_stats->succ_bytes;
		STATS_OP_FMT(SUCC).ht[1][mcs] += peer_stats->succ_pkts;
		STATS_OP_FMT(FAIL).ht[0][mcs] += peer_stats->failed_bytes;
		STATS_OP_FMT(FAIL).ht[1][mcs] += peer_stats->failed_pkts;
		STATS_OP_FMT(RETRY).ht[0][mcs] += peer_stats->retry_bytes;
		STATS_OP_FMT(RETRY).ht[1][mcs] += peer_stats->retry_pkts;
	पूर्ण अन्यथा अणु
		mcs = legacy_rate_idx;

		STATS_OP_FMT(SUCC).legacy[0][mcs] += peer_stats->succ_bytes;
		STATS_OP_FMT(SUCC).legacy[1][mcs] += peer_stats->succ_pkts;
		STATS_OP_FMT(FAIL).legacy[0][mcs] += peer_stats->failed_bytes;
		STATS_OP_FMT(FAIL).legacy[1][mcs] += peer_stats->failed_pkts;
		STATS_OP_FMT(RETRY).legacy[0][mcs] += peer_stats->retry_bytes;
		STATS_OP_FMT(RETRY).legacy[1][mcs] += peer_stats->retry_pkts;
	पूर्ण

	अगर (peer_stats->is_ampdu) अणु
		tx_stats->ba_fails += peer_stats->ba_fails;

		अगर (txrate->flags & RATE_INFO_FLAGS_HE_MCS) अणु
			STATS_OP_FMT(AMPDU).he[0][mcs] +=
			peer_stats->succ_bytes + peer_stats->retry_bytes;
			STATS_OP_FMT(AMPDU).he[1][mcs] +=
			peer_stats->succ_pkts + peer_stats->retry_pkts;
		पूर्ण अन्यथा अगर (txrate->flags & RATE_INFO_FLAGS_MCS) अणु
			STATS_OP_FMT(AMPDU).ht[0][mcs] +=
			peer_stats->succ_bytes + peer_stats->retry_bytes;
			STATS_OP_FMT(AMPDU).ht[1][mcs] +=
			peer_stats->succ_pkts + peer_stats->retry_pkts;
		पूर्ण अन्यथा अणु
			STATS_OP_FMT(AMPDU).vht[0][mcs] +=
			peer_stats->succ_bytes + peer_stats->retry_bytes;
			STATS_OP_FMT(AMPDU).vht[1][mcs] +=
			peer_stats->succ_pkts + peer_stats->retry_pkts;
		पूर्ण
		STATS_OP_FMT(AMPDU).bw[0][bw] +=
			peer_stats->succ_bytes + peer_stats->retry_bytes;
		STATS_OP_FMT(AMPDU).nss[0][nss] +=
			peer_stats->succ_bytes + peer_stats->retry_bytes;
		STATS_OP_FMT(AMPDU).gi[0][gi] +=
			peer_stats->succ_bytes + peer_stats->retry_bytes;
		STATS_OP_FMT(AMPDU).bw[1][bw] +=
			peer_stats->succ_pkts + peer_stats->retry_pkts;
		STATS_OP_FMT(AMPDU).nss[1][nss] +=
			peer_stats->succ_pkts + peer_stats->retry_pkts;
		STATS_OP_FMT(AMPDU).gi[1][gi] +=
			peer_stats->succ_pkts + peer_stats->retry_pkts;
	पूर्ण अन्यथा अणु
		tx_stats->ack_fails += peer_stats->ba_fails;
	पूर्ण

	STATS_OP_FMT(SUCC).bw[0][bw] += peer_stats->succ_bytes;
	STATS_OP_FMT(SUCC).nss[0][nss] += peer_stats->succ_bytes;
	STATS_OP_FMT(SUCC).gi[0][gi] += peer_stats->succ_bytes;

	STATS_OP_FMT(SUCC).bw[1][bw] += peer_stats->succ_pkts;
	STATS_OP_FMT(SUCC).nss[1][nss] += peer_stats->succ_pkts;
	STATS_OP_FMT(SUCC).gi[1][gi] += peer_stats->succ_pkts;

	STATS_OP_FMT(FAIL).bw[0][bw] += peer_stats->failed_bytes;
	STATS_OP_FMT(FAIL).nss[0][nss] += peer_stats->failed_bytes;
	STATS_OP_FMT(FAIL).gi[0][gi] += peer_stats->failed_bytes;

	STATS_OP_FMT(FAIL).bw[1][bw] += peer_stats->failed_pkts;
	STATS_OP_FMT(FAIL).nss[1][nss] += peer_stats->failed_pkts;
	STATS_OP_FMT(FAIL).gi[1][gi] += peer_stats->failed_pkts;

	STATS_OP_FMT(RETRY).bw[0][bw] += peer_stats->retry_bytes;
	STATS_OP_FMT(RETRY).nss[0][nss] += peer_stats->retry_bytes;
	STATS_OP_FMT(RETRY).gi[0][gi] += peer_stats->retry_bytes;

	STATS_OP_FMT(RETRY).bw[1][bw] += peer_stats->retry_pkts;
	STATS_OP_FMT(RETRY).nss[1][nss] += peer_stats->retry_pkts;
	STATS_OP_FMT(RETRY).gi[1][gi] += peer_stats->retry_pkts;

	tx_stats->tx_duration += peer_stats->duration;
पूर्ण

व्योम ath11k_debugfs_sta_update_txcompl(काष्ठा ath11k *ar,
				       काष्ठा sk_buff *msdu,
				       काष्ठा hal_tx_status *ts)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_per_peer_tx_stats *peer_stats = &ar->cached_stats;
	क्रमागत hal_tx_rate_stats_pkt_type pkt_type;
	क्रमागत hal_tx_rate_stats_sgi sgi;
	क्रमागत hal_tx_rate_stats_bw bw;
	काष्ठा ath11k_peer *peer;
	काष्ठा ath11k_sta *arsta;
	काष्ठा ieee80211_sta *sta;
	u16 rate;
	u8 rate_idx = 0;
	पूर्णांक ret;
	u8 mcs;

	rcu_पढ़ो_lock();
	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find_by_id(ab, ts->peer_id);
	अगर (!peer || !peer->sta) अणु
		ath11k_warn(ab, "failed to find the peer\n");
		spin_unlock_bh(&ab->base_lock);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	sta = peer->sta;
	arsta = (काष्ठा ath11k_sta *)sta->drv_priv;

	स_रखो(&arsta->txrate, 0, माप(arsta->txrate));
	pkt_type = FIELD_GET(HAL_TX_RATE_STATS_INFO0_PKT_TYPE,
			     ts->rate_stats);
	mcs = FIELD_GET(HAL_TX_RATE_STATS_INFO0_MCS,
			ts->rate_stats);
	sgi = FIELD_GET(HAL_TX_RATE_STATS_INFO0_SGI,
			ts->rate_stats);
	bw = FIELD_GET(HAL_TX_RATE_STATS_INFO0_BW, ts->rate_stats);

	अगर (pkt_type == HAL_TX_RATE_STATS_PKT_TYPE_11A ||
	    pkt_type == HAL_TX_RATE_STATS_PKT_TYPE_11B) अणु
		ret = ath11k_mac_hw_ratecode_to_legacy_rate(mcs,
							    pkt_type,
							    &rate_idx,
							    &rate);
		अगर (ret < 0)
			जाओ err_out;
		arsta->txrate.legacy = rate;
	पूर्ण अन्यथा अगर (pkt_type == HAL_TX_RATE_STATS_PKT_TYPE_11N) अणु
		अगर (mcs > 7) अणु
			ath11k_warn(ab, "Invalid HT mcs index %d\n", mcs);
			जाओ err_out;
		पूर्ण

		arsta->txrate.mcs = mcs + 8 * (arsta->last_txrate.nss - 1);
		arsta->txrate.flags = RATE_INFO_FLAGS_MCS;
		अगर (sgi)
			arsta->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;
	पूर्ण अन्यथा अगर (pkt_type == HAL_TX_RATE_STATS_PKT_TYPE_11AC) अणु
		अगर (mcs > 9) अणु
			ath11k_warn(ab, "Invalid VHT mcs index %d\n", mcs);
			जाओ err_out;
		पूर्ण

		arsta->txrate.mcs = mcs;
		arsta->txrate.flags = RATE_INFO_FLAGS_VHT_MCS;
		अगर (sgi)
			arsta->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;
	पूर्ण अन्यथा अगर (pkt_type == HAL_TX_RATE_STATS_PKT_TYPE_11AX) अणु
		/* TODO */
	पूर्ण

	arsta->txrate.nss = arsta->last_txrate.nss;
	arsta->txrate.bw = ath11k_mac_bw_to_mac80211_bw(bw);

	ath11k_debugfs_sta_add_tx_stats(arsta, peer_stats, rate_idx);

err_out:
	spin_unlock_bh(&ab->base_lock);
	rcu_पढ़ो_unlock();
पूर्ण

अटल sमाप_प्रकार ath11k_dbg_sta_dump_tx_stats(काष्ठा file *file,
					    अक्षर __user *user_buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	काष्ठा ath11k_htt_data_stats *stats;
	अटल स्थिर अक्षर *str_name[ATH11K_STATS_TYPE_MAX] = अणु"succ", "fail",
							      "retry", "ampdu"पूर्ण;
	अटल स्थिर अक्षर *str[ATH11K_COUNTER_TYPE_MAX] = अणु"bytes", "packets"पूर्ण;
	पूर्णांक len = 0, i, j, k, retval = 0;
	स्थिर पूर्णांक size = 2 * 4096;
	अक्षर *buf;

	अगर (!arsta->tx_stats)
		वापस -ENOENT;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	क्रम (k = 0; k < ATH11K_STATS_TYPE_MAX; k++) अणु
		क्रम (j = 0; j < ATH11K_COUNTER_TYPE_MAX; j++) अणु
			stats = &arsta->tx_stats->stats[k];
			len += scnम_लिखो(buf + len, size - len, "%s_%s\n",
					 str_name[k],
					 str[j]);
			len += scnम_लिखो(buf + len, size - len,
					 " HE MCS %s\n",
					 str[j]);
			क्रम (i = 0; i < ATH11K_HE_MCS_NUM; i++)
				len += scnम_लिखो(buf + len, size - len,
						 "  %llu ",
						 stats->he[j][i]);
			len += scnम_लिखो(buf + len, size - len, "\n");
			len += scnम_लिखो(buf + len, size - len,
					 " VHT MCS %s\n",
					 str[j]);
			क्रम (i = 0; i < ATH11K_VHT_MCS_NUM; i++)
				len += scnम_लिखो(buf + len, size - len,
						 "  %llu ",
						 stats->vht[j][i]);
			len += scnम_लिखो(buf + len, size - len, "\n");
			len += scnम_लिखो(buf + len, size - len, " HT MCS %s\n",
					 str[j]);
			क्रम (i = 0; i < ATH11K_HT_MCS_NUM; i++)
				len += scnम_लिखो(buf + len, size - len,
						 "  %llu ", stats->ht[j][i]);
			len += scnम_लिखो(buf + len, size - len, "\n");
			len += scnम_लिखो(buf + len, size - len,
					" BW %s (20,40,80,160 MHz)\n", str[j]);
			len += scnम_लिखो(buf + len, size - len,
					 "  %llu %llu %llu %llu\n",
					 stats->bw[j][0], stats->bw[j][1],
					 stats->bw[j][2], stats->bw[j][3]);
			len += scnम_लिखो(buf + len, size - len,
					 " NSS %s (1x1,2x2,3x3,4x4)\n", str[j]);
			len += scnम_लिखो(buf + len, size - len,
					 "  %llu %llu %llu %llu\n",
					 stats->nss[j][0], stats->nss[j][1],
					 stats->nss[j][2], stats->nss[j][3]);
			len += scnम_लिखो(buf + len, size - len,
					 " GI %s (0.4us,0.8us,1.6us,3.2us)\n",
					 str[j]);
			len += scnम_लिखो(buf + len, size - len,
					 "  %llu %llu %llu %llu\n",
					 stats->gi[j][0], stats->gi[j][1],
					 stats->gi[j][2], stats->gi[j][3]);
			len += scnम_लिखो(buf + len, size - len,
					 " legacy rate %s (1,2 ... Mbps)\n  ",
					 str[j]);
			क्रम (i = 0; i < ATH11K_LEGACY_NUM; i++)
				len += scnम_लिखो(buf + len, size - len, "%llu ",
						 stats->legacy[j][i]);
			len += scnम_लिखो(buf + len, size - len, "\n");
		पूर्ण
	पूर्ण

	len += scnम_लिखो(buf + len, size - len,
			 "\nTX duration\n %llu usecs\n",
			 arsta->tx_stats->tx_duration);
	len += scnम_लिखो(buf + len, size - len,
			"BA fails\n %llu\n", arsta->tx_stats->ba_fails);
	len += scnम_लिखो(buf + len, size - len,
			"ack fails\n %llu\n", arsta->tx_stats->ack_fails);
	spin_unlock_bh(&ar->data_lock);

	अगर (len > size)
		len = size;
	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	mutex_unlock(&ar->conf_mutex);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tx_stats = अणु
	.पढ़ो = ath11k_dbg_sta_dump_tx_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_dbg_sta_dump_rx_stats(काष्ठा file *file,
					    अक्षर __user *user_buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	काष्ठा ath11k_rx_peer_stats *rx_stats = arsta->rx_stats;
	पूर्णांक len = 0, i, retval = 0;
	स्थिर पूर्णांक size = 4096;
	अक्षर *buf;

	अगर (!rx_stats)
		वापस -ENOENT;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&ar->conf_mutex);
	spin_lock_bh(&ar->ab->base_lock);

	len += scnम_लिखो(buf + len, size - len, "RX peer stats:\n");
	len += scnम_लिखो(buf + len, size - len, "Num of MSDUs: %llu\n",
			 rx_stats->num_msdu);
	len += scnम_लिखो(buf + len, size - len, "Num of MSDUs with TCP L4: %llu\n",
			 rx_stats->tcp_msdu_count);
	len += scnम_लिखो(buf + len, size - len, "Num of MSDUs with UDP L4: %llu\n",
			 rx_stats->udp_msdu_count);
	len += scnम_लिखो(buf + len, size - len, "Num of MSDUs part of AMPDU: %llu\n",
			 rx_stats->ampdu_msdu_count);
	len += scnम_लिखो(buf + len, size - len, "Num of MSDUs not part of AMPDU: %llu\n",
			 rx_stats->non_ampdu_msdu_count);
	len += scnम_लिखो(buf + len, size - len, "Num of MSDUs using STBC: %llu\n",
			 rx_stats->stbc_count);
	len += scnम_लिखो(buf + len, size - len, "Num of MSDUs beamformed: %llu\n",
			 rx_stats->beamक्रमmed_count);
	len += scnम_लिखो(buf + len, size - len, "Num of MPDUs with FCS ok: %llu\n",
			 rx_stats->num_mpdu_fcs_ok);
	len += scnम_लिखो(buf + len, size - len, "Num of MPDUs with FCS error: %llu\n",
			 rx_stats->num_mpdu_fcs_err);
	len += scnम_लिखो(buf + len, size - len,
			 "GI: 0.8us %llu 0.4us %llu 1.6us %llu 3.2us %llu\n",
			 rx_stats->gi_count[0], rx_stats->gi_count[1],
			 rx_stats->gi_count[2], rx_stats->gi_count[3]);
	len += scnम_लिखो(buf + len, size - len,
			 "BW: 20Mhz %llu 40Mhz %llu 80Mhz %llu 160Mhz %llu\n",
			 rx_stats->bw_count[0], rx_stats->bw_count[1],
			 rx_stats->bw_count[2], rx_stats->bw_count[3]);
	len += scnम_लिखो(buf + len, size - len, "BCC %llu LDPC %llu\n",
			 rx_stats->coding_count[0], rx_stats->coding_count[1]);
	len += scnम_लिखो(buf + len, size - len,
			 "preamble: 11A %llu 11B %llu 11N %llu 11AC %llu 11AX %llu\n",
			 rx_stats->pream_cnt[0], rx_stats->pream_cnt[1],
			 rx_stats->pream_cnt[2], rx_stats->pream_cnt[3],
			 rx_stats->pream_cnt[4]);
	len += scnम_लिखो(buf + len, size - len,
			 "reception type: SU %llu MU_MIMO %llu MU_OFDMA %llu MU_OFDMA_MIMO %llu\n",
			 rx_stats->reception_type[0], rx_stats->reception_type[1],
			 rx_stats->reception_type[2], rx_stats->reception_type[3]);
	len += scnम_लिखो(buf + len, size - len, "TID(0-15) Legacy TID(16):");
	क्रम (i = 0; i <= IEEE80211_NUM_TIDS; i++)
		len += scnम_लिखो(buf + len, size - len, "%llu ", rx_stats->tid_count[i]);
	len += scnम_लिखो(buf + len, size - len, "\nMCS(0-11) Legacy MCS(12):");
	क्रम (i = 0; i < HAL_RX_MAX_MCS + 1; i++)
		len += scnम_लिखो(buf + len, size - len, "%llu ", rx_stats->mcs_count[i]);
	len += scnम_लिखो(buf + len, size - len, "\nNSS(1-8):");
	क्रम (i = 0; i < HAL_RX_MAX_NSS; i++)
		len += scnम_लिखो(buf + len, size - len, "%llu ", rx_stats->nss_count[i]);
	len += scnम_लिखो(buf + len, size - len, "\nRX Duration:%llu ",
			 rx_stats->rx_duration);
	len += scnम_लिखो(buf + len, size - len,
			 "\nDCM: %llu\nRU: 26 %llu 52: %llu 106: %llu 242: %llu 484: %llu 996: %llu\n",
			 rx_stats->dcm_count, rx_stats->ru_alloc_cnt[0],
			 rx_stats->ru_alloc_cnt[1], rx_stats->ru_alloc_cnt[2],
			 rx_stats->ru_alloc_cnt[3], rx_stats->ru_alloc_cnt[4],
			 rx_stats->ru_alloc_cnt[5]);

	len += scnम_लिखो(buf + len, size - len, "\n");

	spin_unlock_bh(&ar->ab->base_lock);

	अगर (len > size)
		len = size;
	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	mutex_unlock(&ar->conf_mutex);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_rx_stats = अणु
	.पढ़ो = ath11k_dbg_sta_dump_rx_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक
ath11k_dbg_sta_खोलो_htt_peer_stats(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ieee80211_sta *sta = inode->i_निजी;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	काष्ठा debug_htt_stats_req *stats_req;
	पूर्णांक ret;

	stats_req = vzalloc(माप(*stats_req) + ATH11K_HTT_STATS_BUF_SIZE);
	अगर (!stats_req)
		वापस -ENOMEM;

	mutex_lock(&ar->conf_mutex);
	ar->debug.htt_stats.stats_req = stats_req;
	stats_req->type = ATH11K_DBG_HTT_EXT_STATS_PEER_INFO;
	स_नकल(stats_req->peer_addr, sta->addr, ETH_ALEN);
	ret = ath11k_debugfs_htt_stats_req(ar);
	mutex_unlock(&ar->conf_mutex);
	अगर (ret < 0)
		जाओ out;

	file->निजी_data = stats_req;
	वापस 0;
out:
	vमुक्त(stats_req);
	ar->debug.htt_stats.stats_req = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक
ath11k_dbg_sta_release_htt_peer_stats(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ieee80211_sta *sta = inode->i_निजी;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;

	mutex_lock(&ar->conf_mutex);
	vमुक्त(file->निजी_data);
	ar->debug.htt_stats.stats_req = शून्य;
	mutex_unlock(&ar->conf_mutex);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath11k_dbg_sta_पढ़ो_htt_peer_stats(काष्ठा file *file,
						  अक्षर __user *user_buf,
						  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा debug_htt_stats_req *stats_req = file->निजी_data;
	अक्षर *buf;
	u32 length = 0;

	buf = stats_req->buf;
	length = min_t(u32, stats_req->buf_len, ATH11K_HTT_STATS_BUF_SIZE);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, length);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_htt_peer_stats = अणु
	.खोलो = ath11k_dbg_sta_खोलो_htt_peer_stats,
	.release = ath11k_dbg_sta_release_htt_peer_stats,
	.पढ़ो = ath11k_dbg_sta_पढ़ो_htt_peer_stats,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_dbg_sta_ग_लिखो_peer_pktlog(काष्ठा file *file,
						स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	पूर्णांक ret, enable;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH11K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ out;
	पूर्ण

	ret = kstrtoपूर्णांक_from_user(buf, count, 0, &enable);
	अगर (ret)
		जाओ out;

	ar->debug.pktlog_peer_valid = enable;
	स_नकल(ar->debug.pktlog_peer_addr, sta->addr, ETH_ALEN);

	/* Send peer based pktlog enable/disable */
	ret = ath11k_wmi_pdev_peer_pktlog_filter(ar, sta->addr, enable);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set peer pktlog filter %pM: %d\n",
			    sta->addr, ret);
		जाओ out;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI, "peer pktlog filter set to %d\n",
		   enable);
	ret = count;

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath11k_dbg_sta_पढ़ो_peer_pktlog(काष्ठा file *file,
					       अक्षर __user *ubuf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	अक्षर buf[32] = अणु0पूर्ण;
	पूर्णांक len;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf), "%08x %pM\n",
			ar->debug.pktlog_peer_valid,
			ar->debug.pktlog_peer_addr);
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_peer_pktlog = अणु
	.ग_लिखो = ath11k_dbg_sta_ग_लिखो_peer_pktlog,
	.पढ़ो = ath11k_dbg_sta_पढ़ो_peer_pktlog,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_dbg_sta_ग_लिखो_delba(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	u32 tid, initiator, reason;
	पूर्णांक ret;
	अक्षर buf[64] = अणु0पूर्ण;

	ret = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos,
				     user_buf, count);
	अगर (ret <= 0)
		वापस ret;

	ret = माला_पूछो(buf, "%u %u %u", &tid, &initiator, &reason);
	अगर (ret != 3)
		वापस -EINVAL;

	/* Valid TID values are 0 through 15 */
	अगर (tid > HAL_DESC_REO_NON_QOS_TID - 1)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	अगर (ar->state != ATH11K_STATE_ON ||
	    arsta->aggr_mode != ATH11K_DBG_AGGR_MODE_MANUAL) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ret = ath11k_wmi_delba_send(ar, arsta->arvअगर->vdev_id, sta->addr,
				    tid, initiator, reason);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send delba: vdev_id %u peer %pM tid %u initiator %u reason %u\n",
			    arsta->arvअगर->vdev_id, sta->addr, tid, initiator,
			    reason);
	पूर्ण
	ret = count;
out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_delba = अणु
	.ग_लिखो = ath11k_dbg_sta_ग_लिखो_delba,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_dbg_sta_ग_लिखो_addba_resp(काष्ठा file *file,
					       स्थिर अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	u32 tid, status;
	पूर्णांक ret;
	अक्षर buf[64] = अणु0पूर्ण;

	ret = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos,
				     user_buf, count);
	अगर (ret <= 0)
		वापस ret;

	ret = माला_पूछो(buf, "%u %u", &tid, &status);
	अगर (ret != 2)
		वापस -EINVAL;

	/* Valid TID values are 0 through 15 */
	अगर (tid > HAL_DESC_REO_NON_QOS_TID - 1)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	अगर (ar->state != ATH11K_STATE_ON ||
	    arsta->aggr_mode != ATH11K_DBG_AGGR_MODE_MANUAL) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ret = ath11k_wmi_addba_set_resp(ar, arsta->arvअगर->vdev_id, sta->addr,
					tid, status);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send addba response: vdev_id %u peer %pM tid %u status%u\n",
			    arsta->arvअगर->vdev_id, sta->addr, tid, status);
	पूर्ण
	ret = count;
out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_addba_resp = अणु
	.ग_लिखो = ath11k_dbg_sta_ग_लिखो_addba_resp,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_dbg_sta_ग_लिखो_addba(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	u32 tid, buf_size;
	पूर्णांक ret;
	अक्षर buf[64] = अणु0पूर्ण;

	ret = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos,
				     user_buf, count);
	अगर (ret <= 0)
		वापस ret;

	ret = माला_पूछो(buf, "%u %u", &tid, &buf_size);
	अगर (ret != 2)
		वापस -EINVAL;

	/* Valid TID values are 0 through 15 */
	अगर (tid > HAL_DESC_REO_NON_QOS_TID - 1)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	अगर (ar->state != ATH11K_STATE_ON ||
	    arsta->aggr_mode != ATH11K_DBG_AGGR_MODE_MANUAL) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ret = ath11k_wmi_addba_send(ar, arsta->arvअगर->vdev_id, sta->addr,
				    tid, buf_size);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send addba request: vdev_id %u peer %pM tid %u buf_size %u\n",
			    arsta->arvअगर->vdev_id, sta->addr, tid, buf_size);
	पूर्ण

	ret = count;
out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_addba = अणु
	.ग_लिखो = ath11k_dbg_sta_ग_लिखो_addba,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath11k_dbg_sta_पढ़ो_aggr_mode(काष्ठा file *file,
					     अक्षर __user *user_buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	अक्षर buf[64];
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len,
			"aggregation mode: %s\n\n%s\n%s\n",
			(arsta->aggr_mode == ATH11K_DBG_AGGR_MODE_AUTO) ?
			"auto" : "manual", "auto = 0", "manual = 1");
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath11k_dbg_sta_ग_लिखो_aggr_mode(काष्ठा file *file,
					      स्थिर अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	u32 aggr_mode;
	पूर्णांक ret;

	अगर (kstrtouपूर्णांक_from_user(user_buf, count, 0, &aggr_mode))
		वापस -EINVAL;

	अगर (aggr_mode >= ATH11K_DBG_AGGR_MODE_MAX)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	अगर (ar->state != ATH11K_STATE_ON ||
	    aggr_mode == arsta->aggr_mode) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ret = ath11k_wmi_addba_clear_resp(ar, arsta->arvअगर->vdev_id, sta->addr);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to clear addba session ret: %d\n",
			    ret);
		जाओ out;
	पूर्ण

	arsta->aggr_mode = aggr_mode;
out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_aggr_mode = अणु
	.पढ़ो = ath11k_dbg_sta_पढ़ो_aggr_mode,
	.ग_लिखो = ath11k_dbg_sta_ग_लिखो_aggr_mode,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार
ath11k_ग_लिखो_htt_peer_stats_reset(काष्ठा file *file,
				  स्थिर अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arsta->arvअगर->ar;
	काष्ठा htt_ext_stats_cfg_params cfg_params = अणु 0 पूर्ण;
	पूर्णांक ret;
	u8 type;

	ret = kstrtou8_from_user(user_buf, count, 0, &type);
	अगर (ret)
		वापस ret;

	अगर (!type)
		वापस ret;

	mutex_lock(&ar->conf_mutex);
	cfg_params.cfg0 = HTT_STAT_PEER_INFO_MAC_ADDR;
	cfg_params.cfg0 |= FIELD_PREP(GENMASK(15, 1),
				HTT_PEER_STATS_REQ_MODE_FLUSH_TQM);

	cfg_params.cfg1 = HTT_STAT_DEFAULT_PEER_REQ_TYPE;

	cfg_params.cfg2 |= FIELD_PREP(GENMASK(7, 0), sta->addr[0]);
	cfg_params.cfg2 |= FIELD_PREP(GENMASK(15, 8), sta->addr[1]);
	cfg_params.cfg2 |= FIELD_PREP(GENMASK(23, 16), sta->addr[2]);
	cfg_params.cfg2 |= FIELD_PREP(GENMASK(31, 24), sta->addr[3]);

	cfg_params.cfg3 |= FIELD_PREP(GENMASK(7, 0), sta->addr[4]);
	cfg_params.cfg3 |= FIELD_PREP(GENMASK(15, 8), sta->addr[5]);

	cfg_params.cfg3 |= ATH11K_HTT_PEER_STATS_RESET;

	ret = ath11k_dp_tx_htt_h2t_ext_stats_req(ar,
						 ATH11K_DBG_HTT_EXT_STATS_PEER_INFO,
						 &cfg_params,
						 0ULL);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send htt peer stats request: %d\n", ret);
		mutex_unlock(&ar->conf_mutex);
		वापस ret;
	पूर्ण

	mutex_unlock(&ar->conf_mutex);

	ret = count;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_htt_peer_stats_reset = अणु
	.ग_लिखो = ath11k_ग_लिखो_htt_peer_stats_reset,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath11k_debugfs_sta_op_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta, काष्ठा dentry *dir)
अणु
	काष्ठा ath11k *ar = hw->priv;

	अगर (ath11k_debugfs_is_extd_tx_stats_enabled(ar))
		debugfs_create_file("tx_stats", 0400, dir, sta,
				    &fops_tx_stats);
	अगर (ath11k_debugfs_is_extd_rx_stats_enabled(ar))
		debugfs_create_file("rx_stats", 0400, dir, sta,
				    &fops_rx_stats);

	debugfs_create_file("htt_peer_stats", 0400, dir, sta,
			    &fops_htt_peer_stats);

	debugfs_create_file("peer_pktlog", 0644, dir, sta,
			    &fops_peer_pktlog);

	debugfs_create_file("aggr_mode", 0644, dir, sta, &fops_aggr_mode);
	debugfs_create_file("addba", 0200, dir, sta, &fops_addba);
	debugfs_create_file("addba_resp", 0200, dir, sta, &fops_addba_resp);
	debugfs_create_file("delba", 0200, dir, sta, &fops_delba);

	अगर (test_bit(WMI_TLV_SERVICE_PER_PEER_HTT_STATS_RESET,
		     ar->ab->wmi_ab.svc_map))
		debugfs_create_file("htt_peer_stats_reset", 0600, dir, sta,
				    &fops_htt_peer_stats_reset);
पूर्ण
