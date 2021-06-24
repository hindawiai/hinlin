<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश "core.h"
#समावेश "wmi-ops.h"
#समावेश "txrx.h"
#समावेश "debug.h"

अटल व्योम ath10k_rx_stats_update_amsdu_subfrm(काष्ठा ath10k *ar,
						काष्ठा ath10k_sta_tid_stats *stats,
						u32 msdu_count)
अणु
	अगर (msdu_count == 1)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_1]++;
	अन्यथा अगर (msdu_count == 2)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_2]++;
	अन्यथा अगर (msdu_count == 3)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_3]++;
	अन्यथा अगर (msdu_count == 4)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_4]++;
	अन्यथा अगर (msdu_count > 4)
		stats->rx_pkt_amsdu[ATH10K_AMSDU_SUBFRM_NUM_MORE]++;
पूर्ण

अटल व्योम ath10k_rx_stats_update_ampdu_subfrm(काष्ठा ath10k *ar,
						काष्ठा ath10k_sta_tid_stats *stats,
						u32 mpdu_count)
अणु
	अगर (mpdu_count <= 10)
		stats->rx_pkt_ampdu[ATH10K_AMPDU_SUBFRM_NUM_10]++;
	अन्यथा अगर (mpdu_count <= 20)
		stats->rx_pkt_ampdu[ATH10K_AMPDU_SUBFRM_NUM_20]++;
	अन्यथा अगर (mpdu_count <= 30)
		stats->rx_pkt_ampdu[ATH10K_AMPDU_SUBFRM_NUM_30]++;
	अन्यथा अगर (mpdu_count <= 40)
		stats->rx_pkt_ampdu[ATH10K_AMPDU_SUBFRM_NUM_40]++;
	अन्यथा अगर (mpdu_count <= 50)
		stats->rx_pkt_ampdu[ATH10K_AMPDU_SUBFRM_NUM_50]++;
	अन्यथा अगर (mpdu_count <= 60)
		stats->rx_pkt_ampdu[ATH10K_AMPDU_SUBFRM_NUM_60]++;
	अन्यथा अगर (mpdu_count > 60)
		stats->rx_pkt_ampdu[ATH10K_AMPDU_SUBFRM_NUM_MORE]++;
पूर्ण

व्योम ath10k_sta_update_rx_tid_stats_ampdu(काष्ठा ath10k *ar, u16 peer_id, u8 tid,
					  काष्ठा htt_rx_indication_mpdu_range *ranges,
					  पूर्णांक num_ranges)
अणु
	काष्ठा ath10k_sta *arsta;
	काष्ठा ath10k_peer *peer;
	पूर्णांक i;

	अगर (tid > IEEE80211_NUM_TIDS || !(ar->sta_tid_stats_mask & BIT(tid)))
		वापस;

	rcu_पढ़ो_lock();
	spin_lock_bh(&ar->data_lock);

	peer = ath10k_peer_find_by_id(ar, peer_id);
	अगर (!peer || !peer->sta)
		जाओ out;

	arsta = (काष्ठा ath10k_sta *)peer->sta->drv_priv;

	क्रम (i = 0; i < num_ranges; i++)
		ath10k_rx_stats_update_ampdu_subfrm(ar,
						    &arsta->tid_stats[tid],
						    ranges[i].mpdu_count);

out:
	spin_unlock_bh(&ar->data_lock);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम ath10k_sta_update_rx_tid_stats(काष्ठा ath10k *ar, u8 *first_hdr,
				    अचिन्हित दीर्घ num_msdus,
				    क्रमागत ath10k_pkt_rx_err err,
				    अचिन्हित दीर्घ unchain_cnt,
				    अचिन्हित दीर्घ drop_cnt,
				    अचिन्हित दीर्घ drop_cnt_filter,
				    अचिन्हित दीर्घ queued_msdus)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath10k_sta *arsta;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ath10k_sta_tid_stats *stats;
	u8 tid = IEEE80211_NUM_TIDS;
	bool non_data_frm = false;

	hdr = (काष्ठा ieee80211_hdr *)first_hdr;
	अगर (!ieee80211_is_data(hdr->frame_control))
		non_data_frm = true;

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		tid = *ieee80211_get_qos_ctl(hdr) & IEEE80211_QOS_CTL_TID_MASK;

	अगर (!(ar->sta_tid_stats_mask & BIT(tid)) || non_data_frm)
		वापस;

	rcu_पढ़ो_lock();

	sta = ieee80211_find_sta_by_अगरaddr(ar->hw, hdr->addr2, शून्य);
	अगर (!sta)
		जाओ निकास;

	arsta = (काष्ठा ath10k_sta *)sta->drv_priv;

	spin_lock_bh(&ar->data_lock);
	stats = &arsta->tid_stats[tid];
	stats->rx_pkt_from_fw += num_msdus;
	stats->rx_pkt_unchained += unchain_cnt;
	stats->rx_pkt_drop_chained += drop_cnt;
	stats->rx_pkt_drop_filter += drop_cnt_filter;
	अगर (err != ATH10K_PKT_RX_ERR_MAX)
		stats->rx_pkt_err[err] += queued_msdus;
	stats->rx_pkt_queued_क्रम_mac += queued_msdus;
	ath10k_rx_stats_update_amsdu_subfrm(ar, &arsta->tid_stats[tid],
					    num_msdus);
	spin_unlock_bh(&ar->data_lock);

निकास:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath10k_sta_update_extd_stats_rx_duration(काष्ठा ath10k *ar,
						     काष्ठा ath10k_fw_stats *stats)
अणु
	काष्ठा ath10k_fw_extd_stats_peer *peer;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath10k_sta *arsta;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry(peer, &stats->peers_extd, list) अणु
		sta = ieee80211_find_sta_by_अगरaddr(ar->hw, peer->peer_macaddr,
						   शून्य);
		अगर (!sta)
			जारी;
		arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
		arsta->rx_duration += (u64)peer->rx_duration;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath10k_sta_update_stats_rx_duration(काष्ठा ath10k *ar,
						काष्ठा ath10k_fw_stats *stats)
अणु
	काष्ठा ath10k_fw_stats_peer *peer;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath10k_sta *arsta;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry(peer, &stats->peers, list) अणु
		sta = ieee80211_find_sta_by_अगरaddr(ar->hw, peer->peer_macaddr,
						   शून्य);
		अगर (!sta)
			जारी;
		arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
		arsta->rx_duration += (u64)peer->rx_duration;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम ath10k_sta_update_rx_duration(काष्ठा ath10k *ar,
				   काष्ठा ath10k_fw_stats *stats)
अणु
	अगर (stats->extended)
		ath10k_sta_update_extd_stats_rx_duration(ar, stats);
	अन्यथा
		ath10k_sta_update_stats_rx_duration(ar, stats);
पूर्ण

अटल sमाप_प्रकार ath10k_dbg_sta_पढ़ो_aggr_mode(काष्ठा file *file,
					     अक्षर __user *user_buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
	अक्षर buf[32];
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "aggregation mode: %s\n",
			(arsta->aggr_mode == ATH10K_DBG_AGGR_MODE_AUTO) ?
			"auto" : "manual");
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath10k_dbg_sta_ग_लिखो_aggr_mode(काष्ठा file *file,
					      स्थिर अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
	u32 aggr_mode;
	पूर्णांक ret;

	अगर (kstrtouपूर्णांक_from_user(user_buf, count, 0, &aggr_mode))
		वापस -EINVAL;

	अगर (aggr_mode >= ATH10K_DBG_AGGR_MODE_MAX)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	अगर ((ar->state != ATH10K_STATE_ON) ||
	    (aggr_mode == arsta->aggr_mode)) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ret = ath10k_wmi_addba_clear_resp(ar, arsta->arvअगर->vdev_id, sta->addr);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to clear addba session ret: %d\n", ret);
		जाओ out;
	पूर्ण

	arsta->aggr_mode = aggr_mode;
out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_aggr_mode = अणु
	.पढ़ो = ath10k_dbg_sta_पढ़ो_aggr_mode,
	.ग_लिखो = ath10k_dbg_sta_ग_लिखो_aggr_mode,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_dbg_sta_ग_लिखो_addba(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
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
	अगर (tid > HTT_DATA_TX_EXT_TID_MGMT - 2)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	अगर ((ar->state != ATH10K_STATE_ON) ||
	    (arsta->aggr_mode != ATH10K_DBG_AGGR_MODE_MANUAL)) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ret = ath10k_wmi_addba_send(ar, arsta->arvअगर->vdev_id, sta->addr,
				    tid, buf_size);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send addba request: vdev_id %u peer %pM tid %u buf_size %u\n",
			    arsta->arvअगर->vdev_id, sta->addr, tid, buf_size);
	पूर्ण

	ret = count;
out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_addba = अणु
	.ग_लिखो = ath10k_dbg_sta_ग_लिखो_addba,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_dbg_sta_ग_लिखो_addba_resp(काष्ठा file *file,
					       स्थिर अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
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
	अगर (tid > HTT_DATA_TX_EXT_TID_MGMT - 2)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	अगर ((ar->state != ATH10K_STATE_ON) ||
	    (arsta->aggr_mode != ATH10K_DBG_AGGR_MODE_MANUAL)) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ret = ath10k_wmi_addba_set_resp(ar, arsta->arvअगर->vdev_id, sta->addr,
					tid, status);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send addba response: vdev_id %u peer %pM tid %u status%u\n",
			    arsta->arvअगर->vdev_id, sta->addr, tid, status);
	पूर्ण
	ret = count;
out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_addba_resp = अणु
	.ग_लिखो = ath10k_dbg_sta_ग_लिखो_addba_resp,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_dbg_sta_ग_लिखो_delba(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
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
	अगर (tid > HTT_DATA_TX_EXT_TID_MGMT - 2)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);
	अगर ((ar->state != ATH10K_STATE_ON) ||
	    (arsta->aggr_mode != ATH10K_DBG_AGGR_MODE_MANUAL)) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ret = ath10k_wmi_delba_send(ar, arsta->arvअगर->vdev_id, sta->addr,
				    tid, initiator, reason);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send delba: vdev_id %u peer %pM tid %u initiator %u reason %u\n",
			    arsta->arvअगर->vdev_id, sta->addr, tid, initiator,
			    reason);
	पूर्ण
	ret = count;
out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_delba = अणु
	.ग_लिखो = ath10k_dbg_sta_ग_लिखो_delba,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_dbg_sta_पढ़ो_peer_debug_trigger(काष्ठा file *file,
						      अक्षर __user *user_buf,
						      माप_प्रकार count,
						      loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
	अक्षर buf[8];
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len,
			"Write 1 to once trigger the debug logs\n");
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार
ath10k_dbg_sta_ग_लिखो_peer_debug_trigger(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
	u8 peer_debug_trigger;
	पूर्णांक ret;

	अगर (kstrtou8_from_user(user_buf, count, 0, &peer_debug_trigger))
		वापस -EINVAL;

	अगर (peer_debug_trigger != 1)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ out;
	पूर्ण

	ret = ath10k_wmi_peer_set_param(ar, arsta->arvअगर->vdev_id, sta->addr,
					ar->wmi.peer_param->debug, peer_debug_trigger);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set param to trigger peer tid logs for station ret: %d\n",
			    ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&ar->conf_mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_peer_debug_trigger = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = ath10k_dbg_sta_पढ़ो_peer_debug_trigger,
	.ग_लिखो = ath10k_dbg_sta_ग_लिखो_peer_debug_trigger,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_dbg_sta_पढ़ो_peer_ps_state(काष्ठा file *file,
						 अक्षर __user *user_buf,
						 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
	अक्षर buf[20];
	पूर्णांक len = 0;

	spin_lock_bh(&ar->data_lock);

	len = scnम_लिखो(buf, माप(buf) - len, "%d\n",
			arsta->peer_ps_state);

	spin_unlock_bh(&ar->data_lock);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_peer_ps_state = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = ath10k_dbg_sta_पढ़ो_peer_ps_state,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल अक्षर *get_err_str(क्रमागत ath10k_pkt_rx_err i)
अणु
	चयन (i) अणु
	हाल ATH10K_PKT_RX_ERR_FCS:
		वापस "fcs_err";
	हाल ATH10K_PKT_RX_ERR_TKIP:
		वापस "tkip_err";
	हाल ATH10K_PKT_RX_ERR_CRYPT:
		वापस "crypt_err";
	हाल ATH10K_PKT_RX_ERR_PEER_IDX_INVAL:
		वापस "peer_idx_inval";
	हाल ATH10K_PKT_RX_ERR_MAX:
		वापस "unknown";
	पूर्ण

	वापस "unknown";
पूर्ण

अटल अक्षर *get_num_ampdu_subfrm_str(क्रमागत ath10k_ampdu_subfrm_num i)
अणु
	चयन (i) अणु
	हाल ATH10K_AMPDU_SUBFRM_NUM_10:
		वापस "upto 10";
	हाल ATH10K_AMPDU_SUBFRM_NUM_20:
		वापस "11-20";
	हाल ATH10K_AMPDU_SUBFRM_NUM_30:
		वापस "21-30";
	हाल ATH10K_AMPDU_SUBFRM_NUM_40:
		वापस "31-40";
	हाल ATH10K_AMPDU_SUBFRM_NUM_50:
		वापस "41-50";
	हाल ATH10K_AMPDU_SUBFRM_NUM_60:
		वापस "51-60";
	हाल ATH10K_AMPDU_SUBFRM_NUM_MORE:
		वापस ">60";
	हाल ATH10K_AMPDU_SUBFRM_NUM_MAX:
		वापस "0";
	पूर्ण

	वापस "0";
पूर्ण

अटल अक्षर *get_num_amsdu_subfrm_str(क्रमागत ath10k_amsdu_subfrm_num i)
अणु
	चयन (i) अणु
	हाल ATH10K_AMSDU_SUBFRM_NUM_1:
		वापस "1";
	हाल ATH10K_AMSDU_SUBFRM_NUM_2:
		वापस "2";
	हाल ATH10K_AMSDU_SUBFRM_NUM_3:
		वापस "3";
	हाल ATH10K_AMSDU_SUBFRM_NUM_4:
		वापस "4";
	हाल ATH10K_AMSDU_SUBFRM_NUM_MORE:
		वापस ">4";
	हाल ATH10K_AMSDU_SUBFRM_NUM_MAX:
		वापस "0";
	पूर्ण

	वापस "0";
पूर्ण

#घोषणा PRINT_TID_STATS(_field, _tअसल) \
	करो अणु \
		पूर्णांक k = 0; \
		क्रम (j = 0; j <= IEEE80211_NUM_TIDS; j++) अणु \
			अगर (ar->sta_tid_stats_mask & BIT(j))  अणु \
				len += scnम_लिखो(buf + len, buf_len - len, \
						 "[%02d] %-10lu  ", \
						 j, stats[j]._field); \
				k++; \
				अगर (k % 8 == 0)  अणु \
					len += scnम_लिखो(buf + len, \
							 buf_len - len, "\n"); \
					len += scnम_लिखो(buf + len, \
							 buf_len - len, \
							 _tअसल); \
				पूर्ण \
			पूर्ण \
		पूर्ण \
		len += scnम_लिखो(buf + len, buf_len - len, "\n"); \
	पूर्ण जबतक (0)

अटल sमाप_प्रकार ath10k_dbg_sta_पढ़ो_tid_stats(काष्ठा file *file,
					     अक्षर __user *user_buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
	काष्ठा ath10k_sta_tid_stats *stats = arsta->tid_stats;
	माप_प्रकार len = 0, buf_len = 1048 * IEEE80211_NUM_TIDS;
	अक्षर *buf;
	पूर्णांक i, j;
	sमाप_प्रकार ret;

	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);

	len += scnम_लिखो(buf + len, buf_len - len,
			 "\n\t\tDriver Rx pkt stats per tid, ([tid] count)\n");
	len += scnम_लिखो(buf + len, buf_len - len,
			 "\t\t------------------------------------------\n");
	len += scnम_लिखो(buf + len, buf_len - len, "MSDUs from FW\t\t\t");
	PRINT_TID_STATS(rx_pkt_from_fw, "\t\t\t\t");

	len += scnम_लिखो(buf + len, buf_len - len, "MSDUs unchained\t\t\t");
	PRINT_TID_STATS(rx_pkt_unchained, "\t\t\t\t");

	len += scnम_लिखो(buf + len, buf_len - len,
			 "MSDUs locally dropped:chained\t");
	PRINT_TID_STATS(rx_pkt_drop_chained, "\t\t\t\t");

	len += scnम_लिखो(buf + len, buf_len - len,
			 "MSDUs locally dropped:filtered\t");
	PRINT_TID_STATS(rx_pkt_drop_filter, "\t\t\t\t");

	len += scnम_लिखो(buf + len, buf_len - len,
			 "MSDUs queued for mac80211\t");
	PRINT_TID_STATS(rx_pkt_queued_क्रम_mac, "\t\t\t\t");

	क्रम (i = 0; i < ATH10K_PKT_RX_ERR_MAX; i++) अणु
		len += scnम_लिखो(buf + len, buf_len - len,
				 "MSDUs with error:%s\t", get_err_str(i));
		PRINT_TID_STATS(rx_pkt_err[i], "\t\t\t\t");
	पूर्ण

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	क्रम (i = 0; i < ATH10K_AMPDU_SUBFRM_NUM_MAX; i++) अणु
		len += scnम_लिखो(buf + len, buf_len - len,
				 "A-MPDU num subframes %s\t",
				 get_num_ampdu_subfrm_str(i));
		PRINT_TID_STATS(rx_pkt_ampdu[i], "\t\t\t\t");
	पूर्ण

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	क्रम (i = 0; i < ATH10K_AMSDU_SUBFRM_NUM_MAX; i++) अणु
		len += scnम_लिखो(buf + len, buf_len - len,
				 "A-MSDU num subframes %s\t\t",
				 get_num_amsdu_subfrm_str(i));
		PRINT_TID_STATS(rx_pkt_amsdu[i], "\t\t\t\t");
	पूर्ण

	spin_unlock_bh(&ar->data_lock);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

	kमुक्त(buf);

	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tid_stats_dump = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = ath10k_dbg_sta_पढ़ो_tid_stats,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_dbg_sta_dump_tx_stats(काष्ठा file *file,
					    अक्षर __user *user_buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;
	काष्ठा ath10k_htt_data_stats *stats;
	स्थिर अक्षर *str_name[ATH10K_STATS_TYPE_MAX] = अणु"succ", "fail",
						       "retry", "ampdu"पूर्ण;
	स्थिर अक्षर *str[ATH10K_COUNTER_TYPE_MAX] = अणु"bytes", "packets"पूर्ण;
	पूर्णांक len = 0, i, j, k, retval = 0;
	स्थिर पूर्णांक size = 16 * 4096;
	अक्षर *buf;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&ar->conf_mutex);

	अगर (!arsta->tx_stats) अणु
		ath10k_warn(ar, "failed to get tx stats");
		mutex_unlock(&ar->conf_mutex);
		kमुक्त(buf);
		वापस 0;
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	क्रम (k = 0; k < ATH10K_STATS_TYPE_MAX; k++) अणु
		क्रम (j = 0; j < ATH10K_COUNTER_TYPE_MAX; j++) अणु
			stats = &arsta->tx_stats->stats[k];
			len += scnम_लिखो(buf + len, size - len, "%s_%s\n",
					 str_name[k],
					 str[j]);
			len += scnम_लिखो(buf + len, size - len,
					 " VHT MCS %s\n",
					 str[j]);
			क्रम (i = 0; i < ATH10K_VHT_MCS_NUM; i++)
				len += scnम_लिखो(buf + len, size - len,
						 "  %llu ",
						 stats->vht[j][i]);
			len += scnम_लिखो(buf + len, size - len, "\n");
			len += scnम_लिखो(buf + len, size - len, " HT MCS %s\n",
					 str[j]);
			क्रम (i = 0; i < ATH10K_HT_MCS_NUM; i++)
				len += scnम_लिखो(buf + len, size - len,
						 "  %llu ", stats->ht[j][i]);
			len += scnम_लिखो(buf + len, size - len, "\n");
			len += scnम_लिखो(buf + len, size - len,
					" BW %s (20,5,10,40,80,160 MHz)\n", str[j]);
			len += scnम_लिखो(buf + len, size - len,
					 "  %llu %llu %llu %llu %llu %llu\n",
					 stats->bw[j][0], stats->bw[j][1],
					 stats->bw[j][2], stats->bw[j][3],
					 stats->bw[j][4], stats->bw[j][5]);
			len += scnम_लिखो(buf + len, size - len,
					 " NSS %s (1x1,2x2,3x3,4x4)\n", str[j]);
			len += scnम_लिखो(buf + len, size - len,
					 "  %llu %llu %llu %llu\n",
					 stats->nss[j][0], stats->nss[j][1],
					 stats->nss[j][2], stats->nss[j][3]);
			len += scnम_लिखो(buf + len, size - len,
					 " GI %s (LGI,SGI)\n",
					 str[j]);
			len += scnम_लिखो(buf + len, size - len, "  %llu %llu\n",
					 stats->gi[j][0], stats->gi[j][1]);
			len += scnम_लिखो(buf + len, size - len,
					 " legacy rate %s (1,2 ... Mbps)\n  ",
					 str[j]);
			क्रम (i = 0; i < ATH10K_LEGACY_NUM; i++)
				len += scnम_लिखो(buf + len, size - len, "%llu ",
						 stats->legacy[j][i]);
			len += scnम_लिखो(buf + len, size - len, "\n");
			len += scnम_लिखो(buf + len, size - len,
					 " Rate table %s (1,2 ... Mbps)\n  ",
					 str[j]);
			क्रम (i = 0; i < ATH10K_RATE_TABLE_NUM; i++) अणु
				len += scnम_लिखो(buf + len, size - len, "%llu ",
						 stats->rate_table[j][i]);
				अगर (!((i + 1) % 8))
					len +=
					scnम_लिखो(buf + len, size - len, "\n  ");
			पूर्ण
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
	.पढ़ो = ath10k_dbg_sta_dump_tx_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath10k_sta_add_debugfs(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, काष्ठा dentry *dir)
अणु
	काष्ठा ath10k *ar = hw->priv;

	debugfs_create_file("aggr_mode", 0644, dir, sta, &fops_aggr_mode);
	debugfs_create_file("addba", 0200, dir, sta, &fops_addba);
	debugfs_create_file("addba_resp", 0200, dir, sta, &fops_addba_resp);
	debugfs_create_file("delba", 0200, dir, sta, &fops_delba);
	debugfs_create_file("peer_debug_trigger", 0600, dir, sta,
			    &fops_peer_debug_trigger);
	debugfs_create_file("dump_tid_stats", 0400, dir, sta,
			    &fops_tid_stats_dump);

	अगर (ath10k_peer_stats_enabled(ar) &&
	    ath10k_debug_is_extd_tx_stats_enabled(ar))
		debugfs_create_file("tx_stats", 0400, dir, sta,
				    &fops_tx_stats);
	debugfs_create_file("peer_ps_state", 0400, dir, sta,
			    &fops_peer_ps_state);
पूर्ण
