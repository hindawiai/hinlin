<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "regd.h"
#समावेश "fw.h"
#समावेश "ps.h"
#समावेश "sec.h"
#समावेश "mac.h"
#समावेश "coex.h"
#समावेश "phy.h"
#समावेश "reg.h"
#समावेश "efuse.h"
#समावेश "tx.h"
#समावेश "debug.h"
#समावेश "bf.h"

bool rtw_disable_lps_deep_mode;
EXPORT_SYMBOL(rtw_disable_lps_deep_mode);
bool rtw_bf_support = true;
अचिन्हित पूर्णांक rtw_debug_mask;
EXPORT_SYMBOL(rtw_debug_mask);

module_param_named(disable_lps_deep, rtw_disable_lps_deep_mode, bool, 0644);
module_param_named(support_bf, rtw_bf_support, bool, 0644);
module_param_named(debug_mask, rtw_debug_mask, uपूर्णांक, 0644);

MODULE_PARM_DESC(disable_lps_deep, "Set Y to disable Deep PS");
MODULE_PARM_DESC(support_bf, "Set Y to enable beamformee support");
MODULE_PARM_DESC(debug_mask, "Debugging mask");

अटल काष्ठा ieee80211_channel rtw_channeltable_2g[] = अणु
	अणु.center_freq = 2412, .hw_value = 1,पूर्ण,
	अणु.center_freq = 2417, .hw_value = 2,पूर्ण,
	अणु.center_freq = 2422, .hw_value = 3,पूर्ण,
	अणु.center_freq = 2427, .hw_value = 4,पूर्ण,
	अणु.center_freq = 2432, .hw_value = 5,पूर्ण,
	अणु.center_freq = 2437, .hw_value = 6,पूर्ण,
	अणु.center_freq = 2442, .hw_value = 7,पूर्ण,
	अणु.center_freq = 2447, .hw_value = 8,पूर्ण,
	अणु.center_freq = 2452, .hw_value = 9,पूर्ण,
	अणु.center_freq = 2457, .hw_value = 10,पूर्ण,
	अणु.center_freq = 2462, .hw_value = 11,पूर्ण,
	अणु.center_freq = 2467, .hw_value = 12,पूर्ण,
	अणु.center_freq = 2472, .hw_value = 13,पूर्ण,
	अणु.center_freq = 2484, .hw_value = 14,पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_channel rtw_channeltable_5g[] = अणु
	अणु.center_freq = 5180, .hw_value = 36,पूर्ण,
	अणु.center_freq = 5200, .hw_value = 40,पूर्ण,
	अणु.center_freq = 5220, .hw_value = 44,पूर्ण,
	अणु.center_freq = 5240, .hw_value = 48,पूर्ण,
	अणु.center_freq = 5260, .hw_value = 52,पूर्ण,
	अणु.center_freq = 5280, .hw_value = 56,पूर्ण,
	अणु.center_freq = 5300, .hw_value = 60,पूर्ण,
	अणु.center_freq = 5320, .hw_value = 64,पूर्ण,
	अणु.center_freq = 5500, .hw_value = 100,पूर्ण,
	अणु.center_freq = 5520, .hw_value = 104,पूर्ण,
	अणु.center_freq = 5540, .hw_value = 108,पूर्ण,
	अणु.center_freq = 5560, .hw_value = 112,पूर्ण,
	अणु.center_freq = 5580, .hw_value = 116,पूर्ण,
	अणु.center_freq = 5600, .hw_value = 120,पूर्ण,
	अणु.center_freq = 5620, .hw_value = 124,पूर्ण,
	अणु.center_freq = 5640, .hw_value = 128,पूर्ण,
	अणु.center_freq = 5660, .hw_value = 132,पूर्ण,
	अणु.center_freq = 5680, .hw_value = 136,पूर्ण,
	अणु.center_freq = 5700, .hw_value = 140,पूर्ण,
	अणु.center_freq = 5720, .hw_value = 144,पूर्ण,
	अणु.center_freq = 5745, .hw_value = 149,पूर्ण,
	अणु.center_freq = 5765, .hw_value = 153,पूर्ण,
	अणु.center_freq = 5785, .hw_value = 157,पूर्ण,
	अणु.center_freq = 5805, .hw_value = 161,पूर्ण,
	अणु.center_freq = 5825, .hw_value = 165,
	 .flags = IEEE80211_CHAN_NO_HT40MINUSपूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_rate rtw_ratetable[] = अणु
	अणु.bitrate = 10, .hw_value = 0x00,पूर्ण,
	अणु.bitrate = 20, .hw_value = 0x01,पूर्ण,
	अणु.bitrate = 55, .hw_value = 0x02,पूर्ण,
	अणु.bitrate = 110, .hw_value = 0x03,पूर्ण,
	अणु.bitrate = 60, .hw_value = 0x04,पूर्ण,
	अणु.bitrate = 90, .hw_value = 0x05,पूर्ण,
	अणु.bitrate = 120, .hw_value = 0x06,पूर्ण,
	अणु.bitrate = 180, .hw_value = 0x07,पूर्ण,
	अणु.bitrate = 240, .hw_value = 0x08,पूर्ण,
	अणु.bitrate = 360, .hw_value = 0x09,पूर्ण,
	अणु.bitrate = 480, .hw_value = 0x0a,पूर्ण,
	अणु.bitrate = 540, .hw_value = 0x0b,पूर्ण,
पूर्ण;

u16 rtw_desc_to_bitrate(u8 desc_rate)
अणु
	काष्ठा ieee80211_rate rate;

	अगर (WARN(desc_rate >= ARRAY_SIZE(rtw_ratetable), "invalid desc rate\n"))
		वापस 0;

	rate = rtw_ratetable[desc_rate];

	वापस rate.bitrate;
पूर्ण

अटल काष्ठा ieee80211_supported_band rtw_band_2ghz = अणु
	.band = NL80211_BAND_2GHZ,

	.channels = rtw_channeltable_2g,
	.n_channels = ARRAY_SIZE(rtw_channeltable_2g),

	.bitrates = rtw_ratetable,
	.n_bitrates = ARRAY_SIZE(rtw_ratetable),

	.ht_cap = अणु0पूर्ण,
	.vht_cap = अणु0पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_supported_band rtw_band_5ghz = अणु
	.band = NL80211_BAND_5GHZ,

	.channels = rtw_channeltable_5g,
	.n_channels = ARRAY_SIZE(rtw_channeltable_5g),

	/* 5G has no CCK rates */
	.bitrates = rtw_ratetable + 4,
	.n_bitrates = ARRAY_SIZE(rtw_ratetable) - 4,

	.ht_cap = अणु0पूर्ण,
	.vht_cap = अणु0पूर्ण,
पूर्ण;

काष्ठा rtw_watch_करोg_iter_data अणु
	काष्ठा rtw_dev *rtwdev;
	काष्ठा rtw_vअगर *rtwvअगर;
पूर्ण;

अटल व्योम rtw_dynamic_csi_rate(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *rtwvअगर)
अणु
	काष्ठा rtw_bf_info *bf_info = &rtwdev->bf_info;
	u8 fix_rate_enable = 0;
	u8 new_csi_rate_idx;

	अगर (rtwvअगर->bfee.role != RTW_BFEE_SU &&
	    rtwvअगर->bfee.role != RTW_BFEE_MU)
		वापस;

	rtw_chip_cfg_csi_rate(rtwdev, rtwdev->dm_info.min_rssi,
			      bf_info->cur_csi_rpt_rate,
			      fix_rate_enable, &new_csi_rate_idx);

	अगर (new_csi_rate_idx != bf_info->cur_csi_rpt_rate)
		bf_info->cur_csi_rpt_rate = new_csi_rate_idx;
पूर्ण

अटल व्योम rtw_vअगर_watch_करोg_iter(व्योम *data, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_watch_करोg_iter_data *iter_data = data;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;

	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		अगर (vअगर->bss_conf.assoc)
			iter_data->rtwvअगर = rtwvअगर;

	rtw_dynamic_csi_rate(iter_data->rtwdev, rtwvअगर);

	rtwvअगर->stats.tx_unicast = 0;
	rtwvअगर->stats.rx_unicast = 0;
	rtwvअगर->stats.tx_cnt = 0;
	rtwvअगर->stats.rx_cnt = 0;
पूर्ण

/* process TX/RX statistics periodically क्रम hardware,
 * the inक्रमmation helps hardware to enhance perक्रमmance
 */
अटल व्योम rtw_watch_करोg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
					      watch_करोg_work.work);
	काष्ठा rtw_traffic_stats *stats = &rtwdev->stats;
	काष्ठा rtw_watch_करोg_iter_data data = अणुपूर्ण;
	bool busy_traffic = test_bit(RTW_FLAG_BUSY_TRAFFIC, rtwdev->flags);
	bool ps_active;

	mutex_lock(&rtwdev->mutex);

	अगर (!test_bit(RTW_FLAG_RUNNING, rtwdev->flags))
		जाओ unlock;

	ieee80211_queue_delayed_work(rtwdev->hw, &rtwdev->watch_करोg_work,
				     RTW_WATCH_DOG_DELAY_TIME);

	अगर (rtwdev->stats.tx_cnt > 100 || rtwdev->stats.rx_cnt > 100)
		set_bit(RTW_FLAG_BUSY_TRAFFIC, rtwdev->flags);
	अन्यथा
		clear_bit(RTW_FLAG_BUSY_TRAFFIC, rtwdev->flags);

	अगर (busy_traffic != test_bit(RTW_FLAG_BUSY_TRAFFIC, rtwdev->flags))
		rtw_coex_wl_status_change_notअगरy(rtwdev, 0);

	अगर (stats->tx_cnt > RTW_LPS_THRESHOLD ||
	    stats->rx_cnt > RTW_LPS_THRESHOLD)
		ps_active = true;
	अन्यथा
		ps_active = false;

	ewma_tp_add(&stats->tx_ewma_tp,
		    (u32)(stats->tx_unicast >> RTW_TP_SHIFT));
	ewma_tp_add(&stats->rx_ewma_tp,
		    (u32)(stats->rx_unicast >> RTW_TP_SHIFT));
	stats->tx_throughput = ewma_tp_पढ़ो(&stats->tx_ewma_tp);
	stats->rx_throughput = ewma_tp_पढ़ो(&stats->rx_ewma_tp);

	/* reset tx/rx अटलtics */
	stats->tx_unicast = 0;
	stats->rx_unicast = 0;
	stats->tx_cnt = 0;
	stats->rx_cnt = 0;

	अगर (test_bit(RTW_FLAG_SCANNING, rtwdev->flags))
		जाओ unlock;

	/* make sure BB/RF is working क्रम dynamic mech */
	rtw_leave_lps(rtwdev);

	rtw_phy_dynamic_mechanism(rtwdev);

	data.rtwdev = rtwdev;
	/* use atomic version to aव्योम taking local->अगरlist_mtx mutex */
	rtw_iterate_vअगरs_atomic(rtwdev, rtw_vअगर_watch_करोg_iter, &data);

	/* fw supports only one station associated to enter lps, अगर there are
	 * more than two stations associated to the AP, then we can not enter
	 * lps, because fw करोes not handle the overlapped beacon पूर्णांकerval
	 *
	 * mac80211 should iterate vअगरs and determine अगर driver can enter
	 * ps by passing IEEE80211_CONF_PS to us, all we need to करो is to
	 * get that vअगर and check अगर device is having traffic more than the
	 * threshold.
	 */
	अगर (rtwdev->ps_enabled && data.rtwvअगर && !ps_active)
		rtw_enter_lps(rtwdev, data.rtwvअगर->port);

	rtwdev->watch_करोg_cnt++;

unlock:
	mutex_unlock(&rtwdev->mutex);
पूर्ण

अटल व्योम rtw_c2h_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev, c2h_work);
	काष्ठा sk_buff *skb, *पंचांगp;

	skb_queue_walk_safe(&rtwdev->c2h_queue, skb, पंचांगp) अणु
		skb_unlink(skb, &rtwdev->c2h_queue);
		rtw_fw_c2h_cmd_handle(rtwdev, skb);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल u8 rtw_acquire_macid(काष्ठा rtw_dev *rtwdev)
अणु
	अचिन्हित दीर्घ mac_id;

	mac_id = find_first_zero_bit(rtwdev->mac_id_map, RTW_MAX_MAC_ID_NUM);
	अगर (mac_id < RTW_MAX_MAC_ID_NUM)
		set_bit(mac_id, rtwdev->mac_id_map);

	वापस mac_id;
पूर्ण

पूर्णांक rtw_sta_add(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_sta *sta,
		काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;
	पूर्णांक i;

	si->mac_id = rtw_acquire_macid(rtwdev);
	अगर (si->mac_id >= RTW_MAX_MAC_ID_NUM)
		वापस -ENOSPC;

	si->sta = sta;
	si->vअगर = vअगर;
	si->init_ra_lv = 1;
	ewma_rssi_init(&si->avg_rssi);
	क्रम (i = 0; i < ARRAY_SIZE(sta->txq); i++)
		rtw_txq_init(rtwdev, sta->txq[i]);

	rtw_update_sta_info(rtwdev, si);
	rtw_fw_media_status_report(rtwdev, si->mac_id, true);

	rtwdev->sta_cnt++;
	rtw_info(rtwdev, "sta %pM joined with macid %d\n",
		 sta->addr, si->mac_id);

	वापस 0;
पूर्ण

व्योम rtw_sta_हटाओ(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_sta *sta,
		    bool fw_exist)
अणु
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;
	पूर्णांक i;

	rtw_release_macid(rtwdev, si->mac_id);
	अगर (fw_exist)
		rtw_fw_media_status_report(rtwdev, si->mac_id, false);

	क्रम (i = 0; i < ARRAY_SIZE(sta->txq); i++)
		rtw_txq_cleanup(rtwdev, sta->txq[i]);

	kमुक्त(si->mask);

	rtwdev->sta_cnt--;
	rtw_info(rtwdev, "sta %pM with macid %d left\n",
		 sta->addr, si->mac_id);
पूर्ण

अटल bool rtw_fw_dump_crash_log(काष्ठा rtw_dev *rtwdev)
अणु
	u32 size = rtwdev->chip->fw_rxff_size;
	u32 *buf;
	u8 seq;
	bool ret = true;

	buf = vदो_स्मृति(size);
	अगर (!buf)
		जाओ निकास;

	अगर (rtw_fw_dump_fअगरo(rtwdev, RTW_FW_FIFO_SEL_RXBUF_FW, 0, size, buf)) अणु
		rtw_dbg(rtwdev, RTW_DBG_FW, "dump fw fifo fail\n");
		जाओ मुक्त_buf;
	पूर्ण

	अगर (GET_FW_DUMP_LEN(buf) == 0) अणु
		rtw_dbg(rtwdev, RTW_DBG_FW, "fw crash dump's length is 0\n");
		जाओ मुक्त_buf;
	पूर्ण

	seq = GET_FW_DUMP_SEQ(buf);
	अगर (seq > 0 && seq != (rtwdev->fw.prev_dump_seq + 1)) अणु
		rtw_dbg(rtwdev, RTW_DBG_FW,
			"fw crash dump's seq is wrong: %d\n", seq);
		जाओ मुक्त_buf;
	पूर्ण

	prपूर्णांक_hex_dump(KERN_ERR, "rtw88 fw dump: ", DUMP_PREFIX_OFFSET, 16, 1,
		       buf, size, true);

	अगर (GET_FW_DUMP_MORE(buf) == 1) अणु
		rtwdev->fw.prev_dump_seq = seq;
		ret = false;
	पूर्ण

मुक्त_buf:
	vमुक्त(buf);
निकास:
	rtw_ग_लिखो8(rtwdev, REG_MCU_TST_CFG, 0);

	वापस ret;
पूर्ण

पूर्णांक rtw_dump_fw(काष्ठा rtw_dev *rtwdev, स्थिर u32 ocp_src, u32 size,
		स्थिर अक्षर *prefix_str)
अणु
	u32 rxff = rtwdev->chip->fw_rxff_size;
	u32 dump_size, करोne_size = 0;
	u8 *buf;
	पूर्णांक ret;

	buf = vzalloc(size);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक (size) अणु
		dump_size = size > rxff ? rxff : size;

		ret = rtw_ddma_to_fw_fअगरo(rtwdev, ocp_src + करोne_size,
					  dump_size);
		अगर (ret) अणु
			rtw_err(rtwdev,
				"ddma fw 0x%x [+0x%x] to fw fifo fail\n",
				ocp_src, करोne_size);
			जाओ निकास;
		पूर्ण

		ret = rtw_fw_dump_fअगरo(rtwdev, RTW_FW_FIFO_SEL_RXBUF_FW, 0,
				       dump_size, (u32 *)(buf + करोne_size));
		अगर (ret) अणु
			rtw_err(rtwdev,
				"dump fw 0x%x [+0x%x] from fw fifo fail\n",
				ocp_src, करोne_size);
			जाओ निकास;
		पूर्ण

		size -= dump_size;
		करोne_size += dump_size;
	पूर्ण

	prपूर्णांक_hex_dump(KERN_ERR, prefix_str, DUMP_PREFIX_OFFSET, 16, 1,
		       buf, करोne_size, true);

निकास:
	vमुक्त(buf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rtw_dump_fw);

पूर्णांक rtw_dump_reg(काष्ठा rtw_dev *rtwdev, स्थिर u32 addr, स्थिर u32 size,
		 स्थिर अक्षर *prefix_str)
अणु
	u8 *buf;
	u32 i;

	अगर (addr & 0x3) अणु
		WARN(1, "should be 4-byte aligned, addr = 0x%08x\n", addr);
		वापस -EINVAL;
	पूर्ण

	buf = vzalloc(size);
	अगर (!buf)
		वापस -ENOMEM;

	क्रम (i = 0; i < size; i += 4)
		*(u32 *)(buf + i) = rtw_पढ़ो32(rtwdev, addr + i);

	prपूर्णांक_hex_dump(KERN_ERR, prefix_str, DUMP_PREFIX_OFFSET, 16, 4, buf,
		       size, true);

	vमुक्त(buf);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtw_dump_reg);

व्योम rtw_vअगर_assoc_changed(काष्ठा rtw_vअगर *rtwvअगर,
			   काष्ठा ieee80211_bss_conf *conf)
अणु
	अगर (conf && conf->assoc) अणु
		rtwvअगर->aid = conf->aid;
		rtwvअगर->net_type = RTW_NET_MGD_LINKED;
	पूर्ण अन्यथा अणु
		rtwvअगर->aid = 0;
		rtwvअगर->net_type = RTW_NET_NO_LINK;
	पूर्ण
पूर्ण

अटल व्योम rtw_reset_key_iter(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta,
			       काष्ठा ieee80211_key_conf *key,
			       व्योम *data)
अणु
	काष्ठा rtw_dev *rtwdev = (काष्ठा rtw_dev *)data;
	काष्ठा rtw_sec_desc *sec = &rtwdev->sec;

	rtw_sec_clear_cam(rtwdev, sec, key->hw_key_idx);
पूर्ण

अटल व्योम rtw_reset_sta_iter(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_dev *rtwdev = (काष्ठा rtw_dev *)data;

	अगर (rtwdev->sta_cnt == 0) अणु
		rtw_warn(rtwdev, "sta count before reset should not be 0\n");
		वापस;
	पूर्ण
	rtw_sta_हटाओ(rtwdev, sta, false);
पूर्ण

अटल व्योम rtw_reset_vअगर_iter(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_dev *rtwdev = (काष्ठा rtw_dev *)data;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;

	rtw_bf_disassoc(rtwdev, vअगर, शून्य);
	rtw_vअगर_assoc_changed(rtwvअगर, शून्य);
	rtw_txq_cleanup(rtwdev, vअगर->txq);
पूर्ण

व्योम rtw_fw_recovery(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (!test_bit(RTW_FLAG_RESTARTING, rtwdev->flags))
		ieee80211_queue_work(rtwdev->hw, &rtwdev->fw_recovery_work);
पूर्ण

अटल व्योम __fw_recovery_work(काष्ठा rtw_dev *rtwdev)
अणु

	/* rtw_fw_dump_crash_log() वापसs false indicates that there are
	 * still more log to dump. Driver set 0x1cf[7:0] = 0x1 to tell firmware
	 * to dump the reमुख्यing part of the log, and firmware will trigger an
	 * IMR_C2HCMD पूर्णांकerrupt to inक्रमm driver the log is पढ़ोy.
	 */
	अगर (!rtw_fw_dump_crash_log(rtwdev)) अणु
		rtw_ग_लिखो8(rtwdev, REG_HRCV_MSG, 1);
		वापस;
	पूर्ण
	rtwdev->fw.prev_dump_seq = 0;

	set_bit(RTW_FLAG_RESTARTING, rtwdev->flags);
	rtw_chip_dump_fw_crash(rtwdev);

	WARN(1, "firmware crash, start reset and recover\n");

	rcu_पढ़ो_lock();
	rtw_iterate_keys_rcu(rtwdev, शून्य, rtw_reset_key_iter, rtwdev);
	rcu_पढ़ो_unlock();
	rtw_iterate_stas_atomic(rtwdev, rtw_reset_sta_iter, rtwdev);
	rtw_iterate_vअगरs_atomic(rtwdev, rtw_reset_vअगर_iter, rtwdev);
	rtw_enter_ips(rtwdev);
पूर्ण

अटल व्योम rtw_fw_recovery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev,
					      fw_recovery_work);

	mutex_lock(&rtwdev->mutex);
	__fw_recovery_work(rtwdev);
	mutex_unlock(&rtwdev->mutex);

	ieee80211_restart_hw(rtwdev->hw);
पूर्ण

काष्ठा rtw_txq_ba_iter_data अणु
पूर्ण;

अटल व्योम rtw_txq_ba_iter(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;
	पूर्णांक ret;
	u8 tid;

	tid = find_first_bit(si->tid_ba, IEEE80211_NUM_TIDS);
	जबतक (tid != IEEE80211_NUM_TIDS) अणु
		clear_bit(tid, si->tid_ba);
		ret = ieee80211_start_tx_ba_session(sta, tid, 0);
		अगर (ret == -EINVAL) अणु
			काष्ठा ieee80211_txq *txq;
			काष्ठा rtw_txq *rtwtxq;

			txq = sta->txq[tid];
			rtwtxq = (काष्ठा rtw_txq *)txq->drv_priv;
			set_bit(RTW_TXQ_BLOCK_BA, &rtwtxq->flags);
		पूर्ण

		tid = find_first_bit(si->tid_ba, IEEE80211_NUM_TIDS);
	पूर्ण
पूर्ण

अटल व्योम rtw_txq_ba_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(work, काष्ठा rtw_dev, ba_work);
	काष्ठा rtw_txq_ba_iter_data data;

	rtw_iterate_stas_atomic(rtwdev, rtw_txq_ba_iter, &data);
पूर्ण

व्योम rtw_get_channel_params(काष्ठा cfg80211_chan_def *chandef,
			    काष्ठा rtw_channel_params *chan_params)
अणु
	काष्ठा ieee80211_channel *channel = chandef->chan;
	क्रमागत nl80211_chan_width width = chandef->width;
	u8 *cch_by_bw = chan_params->cch_by_bw;
	u32 primary_freq, center_freq;
	u8 center_chan;
	u8 bandwidth = RTW_CHANNEL_WIDTH_20;
	u8 primary_chan_idx = 0;
	u8 i;

	center_chan = channel->hw_value;
	primary_freq = channel->center_freq;
	center_freq = chandef->center_freq1;

	/* assign the center channel used जबतक 20M bw is selected */
	cch_by_bw[RTW_CHANNEL_WIDTH_20] = channel->hw_value;

	चयन (width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
		bandwidth = RTW_CHANNEL_WIDTH_20;
		primary_chan_idx = RTW_SC_DONT_CARE;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		bandwidth = RTW_CHANNEL_WIDTH_40;
		अगर (primary_freq > center_freq) अणु
			primary_chan_idx = RTW_SC_20_UPPER;
			center_chan -= 2;
		पूर्ण अन्यथा अणु
			primary_chan_idx = RTW_SC_20_LOWER;
			center_chan += 2;
		पूर्ण
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		bandwidth = RTW_CHANNEL_WIDTH_80;
		अगर (primary_freq > center_freq) अणु
			अगर (primary_freq - center_freq == 10) अणु
				primary_chan_idx = RTW_SC_20_UPPER;
				center_chan -= 2;
			पूर्ण अन्यथा अणु
				primary_chan_idx = RTW_SC_20_UPMOST;
				center_chan -= 6;
			पूर्ण
			/* assign the center channel used
			 * जबतक 40M bw is selected
			 */
			cch_by_bw[RTW_CHANNEL_WIDTH_40] = center_chan + 4;
		पूर्ण अन्यथा अणु
			अगर (center_freq - primary_freq == 10) अणु
				primary_chan_idx = RTW_SC_20_LOWER;
				center_chan += 2;
			पूर्ण अन्यथा अणु
				primary_chan_idx = RTW_SC_20_LOWEST;
				center_chan += 6;
			पूर्ण
			/* assign the center channel used
			 * जबतक 40M bw is selected
			 */
			cch_by_bw[RTW_CHANNEL_WIDTH_40] = center_chan - 4;
		पूर्ण
		अवरोध;
	शेष:
		center_chan = 0;
		अवरोध;
	पूर्ण

	chan_params->center_chan = center_chan;
	chan_params->bandwidth = bandwidth;
	chan_params->primary_chan_idx = primary_chan_idx;

	/* assign the center channel used जबतक current bw is selected */
	cch_by_bw[bandwidth] = center_chan;

	क्रम (i = bandwidth + 1; i <= RTW_MAX_CHANNEL_WIDTH; i++)
		cch_by_bw[i] = 0;
पूर्ण

व्योम rtw_set_channel(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा ieee80211_hw *hw = rtwdev->hw;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_channel_params ch_param;
	u8 center_chan, bandwidth, primary_chan_idx;
	u8 i;

	rtw_get_channel_params(&hw->conf.chandef, &ch_param);
	अगर (WARN(ch_param.center_chan == 0, "Invalid channel\n"))
		वापस;

	center_chan = ch_param.center_chan;
	bandwidth = ch_param.bandwidth;
	primary_chan_idx = ch_param.primary_chan_idx;

	hal->current_band_width = bandwidth;
	hal->current_channel = center_chan;
	hal->current_band_type = center_chan > 14 ? RTW_BAND_5G : RTW_BAND_2G;

	क्रम (i = RTW_CHANNEL_WIDTH_20; i <= RTW_MAX_CHANNEL_WIDTH; i++)
		hal->cch_by_bw[i] = ch_param.cch_by_bw[i];

	chip->ops->set_channel(rtwdev, center_chan, bandwidth, primary_chan_idx);

	अगर (hal->current_band_type == RTW_BAND_5G) अणु
		rtw_coex_चयनband_notअगरy(rtwdev, COEX_SWITCH_TO_5G);
	पूर्ण अन्यथा अणु
		अगर (test_bit(RTW_FLAG_SCANNING, rtwdev->flags))
			rtw_coex_चयनband_notअगरy(rtwdev, COEX_SWITCH_TO_24G);
		अन्यथा
			rtw_coex_चयनband_notअगरy(rtwdev, COEX_SWITCH_TO_24G_NOFORSCAN);
	पूर्ण

	rtw_phy_set_tx_घातer_level(rtwdev, center_chan);

	/* अगर the channel isn't set क्रम scanning, we will करो RF calibration
	 * in ieee80211_ops::mgd_prepare_tx(). Perक्रमming the calibration
	 * during scanning on each channel takes too दीर्घ.
	 */
	अगर (!test_bit(RTW_FLAG_SCANNING, rtwdev->flags))
		rtwdev->need_rfk = true;
पूर्ण

व्योम rtw_chip_prepare_tx(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	अगर (rtwdev->need_rfk) अणु
		rtwdev->need_rfk = false;
		chip->ops->phy_calibration(rtwdev);
	पूर्ण
पूर्ण

अटल व्योम rtw_vअगर_ग_लिखो_addr(काष्ठा rtw_dev *rtwdev, u32 start, u8 *addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		rtw_ग_लिखो8(rtwdev, start + i, addr[i]);
पूर्ण

व्योम rtw_vअगर_port_config(काष्ठा rtw_dev *rtwdev,
			 काष्ठा rtw_vअगर *rtwvअगर,
			 u32 config)
अणु
	u32 addr, mask;

	अगर (config & PORT_SET_MAC_ADDR) अणु
		addr = rtwvअगर->conf->mac_addr.addr;
		rtw_vअगर_ग_लिखो_addr(rtwdev, addr, rtwvअगर->mac_addr);
	पूर्ण
	अगर (config & PORT_SET_BSSID) अणु
		addr = rtwvअगर->conf->bssid.addr;
		rtw_vअगर_ग_लिखो_addr(rtwdev, addr, rtwvअगर->bssid);
	पूर्ण
	अगर (config & PORT_SET_NET_TYPE) अणु
		addr = rtwvअगर->conf->net_type.addr;
		mask = rtwvअगर->conf->net_type.mask;
		rtw_ग_लिखो32_mask(rtwdev, addr, mask, rtwvअगर->net_type);
	पूर्ण
	अगर (config & PORT_SET_AID) अणु
		addr = rtwvअगर->conf->aid.addr;
		mask = rtwvअगर->conf->aid.mask;
		rtw_ग_लिखो32_mask(rtwdev, addr, mask, rtwvअगर->aid);
	पूर्ण
	अगर (config & PORT_SET_BCN_CTRL) अणु
		addr = rtwvअगर->conf->bcn_ctrl.addr;
		mask = rtwvअगर->conf->bcn_ctrl.mask;
		rtw_ग_लिखो8_mask(rtwdev, addr, mask, rtwvअगर->bcn_ctrl);
	पूर्ण
पूर्ण

अटल u8 hw_bw_cap_to_bitamp(u8 bw_cap)
अणु
	u8 bw = 0;

	चयन (bw_cap) अणु
	हाल EFUSE_HW_CAP_IGNORE:
	हाल EFUSE_HW_CAP_SUPP_BW80:
		bw |= BIT(RTW_CHANNEL_WIDTH_80);
		fallthrough;
	हाल EFUSE_HW_CAP_SUPP_BW40:
		bw |= BIT(RTW_CHANNEL_WIDTH_40);
		fallthrough;
	शेष:
		bw |= BIT(RTW_CHANNEL_WIDTH_20);
		अवरोध;
	पूर्ण

	वापस bw;
पूर्ण

अटल व्योम rtw_hw_config_rf_ant_num(काष्ठा rtw_dev *rtwdev, u8 hw_ant_num)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	अगर (hw_ant_num == EFUSE_HW_CAP_IGNORE ||
	    hw_ant_num >= hal->rf_path_num)
		वापस;

	चयन (hw_ant_num) अणु
	हाल 1:
		hal->rf_type = RF_1T1R;
		hal->rf_path_num = 1;
		अगर (!chip->fix_rf_phy_num)
			hal->rf_phy_num = hal->rf_path_num;
		hal->antenna_tx = BB_PATH_A;
		hal->antenna_rx = BB_PATH_A;
		अवरोध;
	शेष:
		WARN(1, "invalid hw configuration from efuse\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल u64 get_vht_ra_mask(काष्ठा ieee80211_sta *sta)
अणु
	u64 ra_mask = 0;
	u16 mcs_map = le16_to_cpu(sta->vht_cap.vht_mcs.rx_mcs_map);
	u8 vht_mcs_cap;
	पूर्णांक i, nss;

	/* 4SS, every two bits क्रम MCS7/8/9 */
	क्रम (i = 0, nss = 12; i < 4; i++, mcs_map >>= 2, nss += 10) अणु
		vht_mcs_cap = mcs_map & 0x3;
		चयन (vht_mcs_cap) अणु
		हाल 2: /* MCS9 */
			ra_mask |= 0x3ffULL << nss;
			अवरोध;
		हाल 1: /* MCS8 */
			ra_mask |= 0x1ffULL << nss;
			अवरोध;
		हाल 0: /* MCS7 */
			ra_mask |= 0x0ffULL << nss;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ra_mask;
पूर्ण

अटल u8 get_rate_id(u8 wireless_set, क्रमागत rtw_bandwidth bw_mode, u8 tx_num)
अणु
	u8 rate_id = 0;

	चयन (wireless_set) अणु
	हाल WIRELESS_CCK:
		rate_id = RTW_RATEID_B_20M;
		अवरोध;
	हाल WIRELESS_OFDM:
		rate_id = RTW_RATEID_G;
		अवरोध;
	हाल WIRELESS_CCK | WIRELESS_OFDM:
		rate_id = RTW_RATEID_BG;
		अवरोध;
	हाल WIRELESS_OFDM | WIRELESS_HT:
		अगर (tx_num == 1)
			rate_id = RTW_RATEID_GN_N1SS;
		अन्यथा अगर (tx_num == 2)
			rate_id = RTW_RATEID_GN_N2SS;
		अन्यथा अगर (tx_num == 3)
			rate_id = RTW_RATEID_ARFR5_N_3SS;
		अवरोध;
	हाल WIRELESS_CCK | WIRELESS_OFDM | WIRELESS_HT:
		अगर (bw_mode == RTW_CHANNEL_WIDTH_40) अणु
			अगर (tx_num == 1)
				rate_id = RTW_RATEID_BGN_40M_1SS;
			अन्यथा अगर (tx_num == 2)
				rate_id = RTW_RATEID_BGN_40M_2SS;
			अन्यथा अगर (tx_num == 3)
				rate_id = RTW_RATEID_ARFR5_N_3SS;
			अन्यथा अगर (tx_num == 4)
				rate_id = RTW_RATEID_ARFR7_N_4SS;
		पूर्ण अन्यथा अणु
			अगर (tx_num == 1)
				rate_id = RTW_RATEID_BGN_20M_1SS;
			अन्यथा अगर (tx_num == 2)
				rate_id = RTW_RATEID_BGN_20M_2SS;
			अन्यथा अगर (tx_num == 3)
				rate_id = RTW_RATEID_ARFR5_N_3SS;
			अन्यथा अगर (tx_num == 4)
				rate_id = RTW_RATEID_ARFR7_N_4SS;
		पूर्ण
		अवरोध;
	हाल WIRELESS_OFDM | WIRELESS_VHT:
		अगर (tx_num == 1)
			rate_id = RTW_RATEID_ARFR1_AC_1SS;
		अन्यथा अगर (tx_num == 2)
			rate_id = RTW_RATEID_ARFR0_AC_2SS;
		अन्यथा अगर (tx_num == 3)
			rate_id = RTW_RATEID_ARFR4_AC_3SS;
		अन्यथा अगर (tx_num == 4)
			rate_id = RTW_RATEID_ARFR6_AC_4SS;
		अवरोध;
	हाल WIRELESS_CCK | WIRELESS_OFDM | WIRELESS_VHT:
		अगर (bw_mode >= RTW_CHANNEL_WIDTH_80) अणु
			अगर (tx_num == 1)
				rate_id = RTW_RATEID_ARFR1_AC_1SS;
			अन्यथा अगर (tx_num == 2)
				rate_id = RTW_RATEID_ARFR0_AC_2SS;
			अन्यथा अगर (tx_num == 3)
				rate_id = RTW_RATEID_ARFR4_AC_3SS;
			अन्यथा अगर (tx_num == 4)
				rate_id = RTW_RATEID_ARFR6_AC_4SS;
		पूर्ण अन्यथा अणु
			अगर (tx_num == 1)
				rate_id = RTW_RATEID_ARFR2_AC_2G_1SS;
			अन्यथा अगर (tx_num == 2)
				rate_id = RTW_RATEID_ARFR3_AC_2G_2SS;
			अन्यथा अगर (tx_num == 3)
				rate_id = RTW_RATEID_ARFR4_AC_3SS;
			अन्यथा अगर (tx_num == 4)
				rate_id = RTW_RATEID_ARFR6_AC_4SS;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rate_id;
पूर्ण

#घोषणा RA_MASK_CCK_RATES	0x0000f
#घोषणा RA_MASK_OFDM_RATES	0x00ff0
#घोषणा RA_MASK_HT_RATES_1SS	(0xff000ULL << 0)
#घोषणा RA_MASK_HT_RATES_2SS	(0xff000ULL << 8)
#घोषणा RA_MASK_HT_RATES_3SS	(0xff000ULL << 16)
#घोषणा RA_MASK_HT_RATES	(RA_MASK_HT_RATES_1SS | \
				 RA_MASK_HT_RATES_2SS | \
				 RA_MASK_HT_RATES_3SS)
#घोषणा RA_MASK_VHT_RATES_1SS	(0x3ff000ULL << 0)
#घोषणा RA_MASK_VHT_RATES_2SS	(0x3ff000ULL << 10)
#घोषणा RA_MASK_VHT_RATES_3SS	(0x3ff000ULL << 20)
#घोषणा RA_MASK_VHT_RATES	(RA_MASK_VHT_RATES_1SS | \
				 RA_MASK_VHT_RATES_2SS | \
				 RA_MASK_VHT_RATES_3SS)
#घोषणा RA_MASK_CCK_IN_HT	0x00005
#घोषणा RA_MASK_CCK_IN_VHT	0x00005
#घोषणा RA_MASK_OFDM_IN_VHT	0x00010
#घोषणा RA_MASK_OFDM_IN_HT_2G	0x00010
#घोषणा RA_MASK_OFDM_IN_HT_5G	0x00030

अटल u64 rtw_update_rate_mask(काष्ठा rtw_dev *rtwdev,
				काष्ठा rtw_sta_info *si,
				u64 ra_mask, bool is_vht_enable,
				u8 wireless_set)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	स्थिर काष्ठा cfg80211_bitrate_mask *mask = si->mask;
	u64 cfg_mask = GENMASK_ULL(63, 0);
	u8 rssi_level, band;

	अगर (wireless_set != WIRELESS_CCK) अणु
		rssi_level = si->rssi_level;
		अगर (rssi_level == 0)
			ra_mask &= 0xffffffffffffffffULL;
		अन्यथा अगर (rssi_level == 1)
			ra_mask &= 0xfffffffffffffff0ULL;
		अन्यथा अगर (rssi_level == 2)
			ra_mask &= 0xffffffffffffefe0ULL;
		अन्यथा अगर (rssi_level == 3)
			ra_mask &= 0xffffffffffffcfc0ULL;
		अन्यथा अगर (rssi_level == 4)
			ra_mask &= 0xffffffffffff8f80ULL;
		अन्यथा अगर (rssi_level >= 5)
			ra_mask &= 0xffffffffffff0f00ULL;
	पूर्ण

	अगर (!si->use_cfg_mask)
		वापस ra_mask;

	band = hal->current_band_type;
	अगर (band == RTW_BAND_2G) अणु
		band = NL80211_BAND_2GHZ;
		cfg_mask = mask->control[band].legacy;
	पूर्ण अन्यथा अगर (band == RTW_BAND_5G) अणु
		band = NL80211_BAND_5GHZ;
		cfg_mask = u64_encode_bits(mask->control[band].legacy,
					   RA_MASK_OFDM_RATES);
	पूर्ण

	अगर (!is_vht_enable) अणु
		अगर (ra_mask & RA_MASK_HT_RATES_1SS)
			cfg_mask |= u64_encode_bits(mask->control[band].ht_mcs[0],
						    RA_MASK_HT_RATES_1SS);
		अगर (ra_mask & RA_MASK_HT_RATES_2SS)
			cfg_mask |= u64_encode_bits(mask->control[band].ht_mcs[1],
						    RA_MASK_HT_RATES_2SS);
	पूर्ण अन्यथा अणु
		अगर (ra_mask & RA_MASK_VHT_RATES_1SS)
			cfg_mask |= u64_encode_bits(mask->control[band].vht_mcs[0],
						    RA_MASK_VHT_RATES_1SS);
		अगर (ra_mask & RA_MASK_VHT_RATES_2SS)
			cfg_mask |= u64_encode_bits(mask->control[band].vht_mcs[1],
						    RA_MASK_VHT_RATES_2SS);
	पूर्ण

	ra_mask &= cfg_mask;

	वापस ra_mask;
पूर्ण

व्योम rtw_update_sta_info(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_sta_info *si)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा ieee80211_sta *sta = si->sta;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 wireless_set;
	u8 bw_mode;
	u8 rate_id;
	u8 rf_type = RF_1T1R;
	u8 stbc_en = 0;
	u8 ldpc_en = 0;
	u8 tx_num = 1;
	u64 ra_mask = 0;
	bool is_vht_enable = false;
	bool is_support_sgi = false;

	अगर (sta->vht_cap.vht_supported) अणु
		is_vht_enable = true;
		ra_mask |= get_vht_ra_mask(sta);
		अगर (sta->vht_cap.cap & IEEE80211_VHT_CAP_RXSTBC_MASK)
			stbc_en = VHT_STBC_EN;
		अगर (sta->vht_cap.cap & IEEE80211_VHT_CAP_RXLDPC)
			ldpc_en = VHT_LDPC_EN;
	पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported) अणु
		ra_mask |= (sta->ht_cap.mcs.rx_mask[1] << 20) |
			   (sta->ht_cap.mcs.rx_mask[0] << 12);
		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_RX_STBC)
			stbc_en = HT_STBC_EN;
		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_LDPC_CODING)
			ldpc_en = HT_LDPC_EN;
	पूर्ण

	अगर (efuse->hw_cap.nss == 1)
		ra_mask &= RA_MASK_VHT_RATES_1SS | RA_MASK_HT_RATES_1SS;

	अगर (hal->current_band_type == RTW_BAND_5G) अणु
		ra_mask |= (u64)sta->supp_rates[NL80211_BAND_5GHZ] << 4;
		अगर (sta->vht_cap.vht_supported) अणु
			ra_mask &= RA_MASK_VHT_RATES | RA_MASK_OFDM_IN_VHT;
			wireless_set = WIRELESS_OFDM | WIRELESS_VHT;
		पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported) अणु
			ra_mask &= RA_MASK_HT_RATES | RA_MASK_OFDM_IN_HT_5G;
			wireless_set = WIRELESS_OFDM | WIRELESS_HT;
		पूर्ण अन्यथा अणु
			wireless_set = WIRELESS_OFDM;
		पूर्ण
		dm_info->rrsr_val_init = RRSR_INIT_5G;
	पूर्ण अन्यथा अगर (hal->current_band_type == RTW_BAND_2G) अणु
		ra_mask |= sta->supp_rates[NL80211_BAND_2GHZ];
		अगर (sta->vht_cap.vht_supported) अणु
			ra_mask &= RA_MASK_VHT_RATES | RA_MASK_CCK_IN_VHT |
				   RA_MASK_OFDM_IN_VHT;
			wireless_set = WIRELESS_CCK | WIRELESS_OFDM |
				       WIRELESS_HT | WIRELESS_VHT;
		पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported) अणु
			ra_mask &= RA_MASK_HT_RATES | RA_MASK_CCK_IN_HT |
				   RA_MASK_OFDM_IN_HT_2G;
			wireless_set = WIRELESS_CCK | WIRELESS_OFDM |
				       WIRELESS_HT;
		पूर्ण अन्यथा अगर (sta->supp_rates[0] <= 0xf) अणु
			wireless_set = WIRELESS_CCK;
		पूर्ण अन्यथा अणु
			wireless_set = WIRELESS_CCK | WIRELESS_OFDM;
		पूर्ण
		dm_info->rrsr_val_init = RRSR_INIT_2G;
	पूर्ण अन्यथा अणु
		rtw_err(rtwdev, "Unknown band type\n");
		wireless_set = 0;
	पूर्ण

	चयन (sta->bandwidth) अणु
	हाल IEEE80211_STA_RX_BW_80:
		bw_mode = RTW_CHANNEL_WIDTH_80;
		is_support_sgi = sta->vht_cap.vht_supported &&
				 (sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_80);
		अवरोध;
	हाल IEEE80211_STA_RX_BW_40:
		bw_mode = RTW_CHANNEL_WIDTH_40;
		is_support_sgi = sta->ht_cap.ht_supported &&
				 (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40);
		अवरोध;
	शेष:
		bw_mode = RTW_CHANNEL_WIDTH_20;
		is_support_sgi = sta->ht_cap.ht_supported &&
				 (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20);
		अवरोध;
	पूर्ण

	अगर (sta->vht_cap.vht_supported && ra_mask & 0xffc00000) अणु
		tx_num = 2;
		rf_type = RF_2T2R;
	पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported && ra_mask & 0xfff00000) अणु
		tx_num = 2;
		rf_type = RF_2T2R;
	पूर्ण

	rate_id = get_rate_id(wireless_set, bw_mode, tx_num);

	ra_mask = rtw_update_rate_mask(rtwdev, si, ra_mask, is_vht_enable,
				       wireless_set);

	si->bw_mode = bw_mode;
	si->stbc_en = stbc_en;
	si->ldpc_en = ldpc_en;
	si->rf_type = rf_type;
	si->wireless_set = wireless_set;
	si->sgi_enable = is_support_sgi;
	si->vht_enable = is_vht_enable;
	si->ra_mask = ra_mask;
	si->rate_id = rate_id;

	rtw_fw_send_ra_info(rtwdev, si);
पूर्ण

अटल पूर्णांक rtw_रुको_firmware_completion(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_fw_state *fw;

	fw = &rtwdev->fw;
	रुको_क्रम_completion(&fw->completion);
	अगर (!fw->firmware)
		वापस -EINVAL;

	अगर (chip->wow_fw_name) अणु
		fw = &rtwdev->wow_fw;
		रुको_क्रम_completion(&fw->completion);
		अगर (!fw->firmware)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत rtw_lps_deep_mode rtw_update_lps_deep_mode(काष्ठा rtw_dev *rtwdev,
						       काष्ठा rtw_fw_state *fw)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	अगर (rtw_disable_lps_deep_mode || !chip->lps_deep_mode_supported ||
	    !fw->feature)
		वापस LPS_DEEP_MODE_NONE;

	अगर ((chip->lps_deep_mode_supported & BIT(LPS_DEEP_MODE_PG)) &&
	    (fw->feature & FW_FEATURE_PG))
		वापस LPS_DEEP_MODE_PG;

	अगर ((chip->lps_deep_mode_supported & BIT(LPS_DEEP_MODE_LCLK)) &&
	    (fw->feature & FW_FEATURE_LCLK))
		वापस LPS_DEEP_MODE_LCLK;

	वापस LPS_DEEP_MODE_NONE;
पूर्ण

अटल पूर्णांक rtw_घातer_on(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_fw_state *fw = &rtwdev->fw;
	bool wअगरi_only;
	पूर्णांक ret;

	ret = rtw_hci_setup(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to setup hci\n");
		जाओ err;
	पूर्ण

	/* घातer on MAC beक्रमe firmware करोwnloaded */
	ret = rtw_mac_घातer_on(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to power on mac\n");
		जाओ err;
	पूर्ण

	ret = rtw_रुको_firmware_completion(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to wait firmware completion\n");
		जाओ err_off;
	पूर्ण

	ret = rtw_करोwnload_firmware(rtwdev, fw);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to download firmware\n");
		जाओ err_off;
	पूर्ण

	/* config mac after firmware करोwnloaded */
	ret = rtw_mac_init(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to configure mac\n");
		जाओ err_off;
	पूर्ण

	chip->ops->phy_set_param(rtwdev);

	ret = rtw_hci_start(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to start hci\n");
		जाओ err_off;
	पूर्ण

	/* send H2C after HCI has started */
	rtw_fw_send_general_info(rtwdev);
	rtw_fw_send_phydm_info(rtwdev);

	wअगरi_only = !rtwdev->efuse.btcoex;
	rtw_coex_घातer_on_setting(rtwdev);
	rtw_coex_init_hw_config(rtwdev, wअगरi_only);

	वापस 0;

err_off:
	rtw_mac_घातer_off(rtwdev);

err:
	वापस ret;
पूर्ण

पूर्णांक rtw_core_start(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret;

	ret = rtw_घातer_on(rtwdev);
	अगर (ret)
		वापस ret;

	rtw_sec_enable_sec_engine(rtwdev);

	rtwdev->lps_conf.deep_mode = rtw_update_lps_deep_mode(rtwdev, &rtwdev->fw);
	rtwdev->lps_conf.wow_deep_mode = rtw_update_lps_deep_mode(rtwdev, &rtwdev->wow_fw);

	/* rcr reset after घातered on */
	rtw_ग_लिखो32(rtwdev, REG_RCR, rtwdev->hal.rcr);

	ieee80211_queue_delayed_work(rtwdev->hw, &rtwdev->watch_करोg_work,
				     RTW_WATCH_DOG_DELAY_TIME);

	set_bit(RTW_FLAG_RUNNING, rtwdev->flags);

	वापस 0;
पूर्ण

अटल व्योम rtw_घातer_off(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_hci_stop(rtwdev);
	rtw_coex_घातer_off_setting(rtwdev);
	rtw_mac_घातer_off(rtwdev);
पूर्ण

व्योम rtw_core_stop(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;

	clear_bit(RTW_FLAG_RUNNING, rtwdev->flags);
	clear_bit(RTW_FLAG_FW_RUNNING, rtwdev->flags);

	mutex_unlock(&rtwdev->mutex);

	cancel_work_sync(&rtwdev->c2h_work);
	cancel_delayed_work_sync(&rtwdev->watch_करोg_work);
	cancel_delayed_work_sync(&coex->bt_relink_work);
	cancel_delayed_work_sync(&coex->bt_reenable_work);
	cancel_delayed_work_sync(&coex->deमुक्तze_work);
	cancel_delayed_work_sync(&coex->wl_reमुख्य_work);
	cancel_delayed_work_sync(&coex->bt_reमुख्य_work);
	cancel_delayed_work_sync(&coex->wl_connecting_work);
	cancel_delayed_work_sync(&coex->bt_multi_link_reमुख्य_work);
	cancel_delayed_work_sync(&coex->wl_ccklock_work);

	mutex_lock(&rtwdev->mutex);

	rtw_घातer_off(rtwdev);
पूर्ण

अटल व्योम rtw_init_ht_cap(काष्ठा rtw_dev *rtwdev,
			    काष्ठा ieee80211_sta_ht_cap *ht_cap)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;

	ht_cap->ht_supported = true;
	ht_cap->cap = 0;
	ht_cap->cap |= IEEE80211_HT_CAP_SGI_20 |
			IEEE80211_HT_CAP_MAX_AMSDU |
			(1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);

	अगर (rtw_chip_has_rx_ldpc(rtwdev))
		ht_cap->cap |= IEEE80211_HT_CAP_LDPC_CODING;

	अगर (efuse->hw_cap.bw & BIT(RTW_CHANNEL_WIDTH_40))
		ht_cap->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
				IEEE80211_HT_CAP_DSSSCCK40 |
				IEEE80211_HT_CAP_SGI_40;
	ht_cap->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_cap->ampdu_density = IEEE80211_HT_MPDU_DENSITY_16;
	ht_cap->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	अगर (efuse->hw_cap.nss > 1) अणु
		ht_cap->mcs.rx_mask[0] = 0xFF;
		ht_cap->mcs.rx_mask[1] = 0xFF;
		ht_cap->mcs.rx_mask[4] = 0x01;
		ht_cap->mcs.rx_highest = cpu_to_le16(300);
	पूर्ण अन्यथा अणु
		ht_cap->mcs.rx_mask[0] = 0xFF;
		ht_cap->mcs.rx_mask[1] = 0x00;
		ht_cap->mcs.rx_mask[4] = 0x01;
		ht_cap->mcs.rx_highest = cpu_to_le16(150);
	पूर्ण
पूर्ण

अटल व्योम rtw_init_vht_cap(काष्ठा rtw_dev *rtwdev,
			     काष्ठा ieee80211_sta_vht_cap *vht_cap)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u16 mcs_map;
	__le16 highest;

	अगर (efuse->hw_cap.ptcl != EFUSE_HW_CAP_IGNORE &&
	    efuse->hw_cap.ptcl != EFUSE_HW_CAP_PTCL_VHT)
		वापस;

	vht_cap->vht_supported = true;
	vht_cap->cap = IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 |
		       IEEE80211_VHT_CAP_SHORT_GI_80 |
		       IEEE80211_VHT_CAP_RXSTBC_1 |
		       IEEE80211_VHT_CAP_HTC_VHT |
		       IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK |
		       0;
	अगर (rtwdev->hal.rf_path_num > 1)
		vht_cap->cap |= IEEE80211_VHT_CAP_TXSTBC;
	vht_cap->cap |= IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE |
			IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE;
	vht_cap->cap |= (rtwdev->hal.bfee_sts_cap <<
			IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT);

	अगर (rtw_chip_has_rx_ldpc(rtwdev))
		vht_cap->cap |= IEEE80211_VHT_CAP_RXLDPC;

	mcs_map = IEEE80211_VHT_MCS_SUPPORT_0_9 << 0 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 4 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 6 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 8 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 10 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 12 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 14;
	अगर (efuse->hw_cap.nss > 1) अणु
		highest = cpu_to_le16(780);
		mcs_map |= IEEE80211_VHT_MCS_SUPPORT_0_9 << 2;
	पूर्ण अन्यथा अणु
		highest = cpu_to_le16(390);
		mcs_map |= IEEE80211_VHT_MCS_NOT_SUPPORTED << 2;
	पूर्ण

	vht_cap->vht_mcs.rx_mcs_map = cpu_to_le16(mcs_map);
	vht_cap->vht_mcs.tx_mcs_map = cpu_to_le16(mcs_map);
	vht_cap->vht_mcs.rx_highest = highest;
	vht_cap->vht_mcs.tx_highest = highest;
पूर्ण

अटल व्योम rtw_set_supported_band(काष्ठा ieee80211_hw *hw,
				   काष्ठा rtw_chip_info *chip)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा ieee80211_supported_band *sband;

	अगर (chip->band & RTW_BAND_2G) अणु
		sband = kmemdup(&rtw_band_2ghz, माप(*sband), GFP_KERNEL);
		अगर (!sband)
			जाओ err_out;
		अगर (chip->ht_supported)
			rtw_init_ht_cap(rtwdev, &sband->ht_cap);
		hw->wiphy->bands[NL80211_BAND_2GHZ] = sband;
	पूर्ण

	अगर (chip->band & RTW_BAND_5G) अणु
		sband = kmemdup(&rtw_band_5ghz, माप(*sband), GFP_KERNEL);
		अगर (!sband)
			जाओ err_out;
		अगर (chip->ht_supported)
			rtw_init_ht_cap(rtwdev, &sband->ht_cap);
		अगर (chip->vht_supported)
			rtw_init_vht_cap(rtwdev, &sband->vht_cap);
		hw->wiphy->bands[NL80211_BAND_5GHZ] = sband;
	पूर्ण

	वापस;

err_out:
	rtw_err(rtwdev, "failed to set supported band\n");
पूर्ण

अटल व्योम rtw_unset_supported_band(काष्ठा ieee80211_hw *hw,
				     काष्ठा rtw_chip_info *chip)
अणु
	kमुक्त(hw->wiphy->bands[NL80211_BAND_2GHZ]);
	kमुक्त(hw->wiphy->bands[NL80211_BAND_5GHZ]);
पूर्ण

अटल व्योम __update_firmware_feature(काष्ठा rtw_dev *rtwdev,
				      काष्ठा rtw_fw_state *fw)
अणु
	u32 feature;
	स्थिर काष्ठा rtw_fw_hdr *fw_hdr =
				(स्थिर काष्ठा rtw_fw_hdr *)fw->firmware->data;

	feature = le32_to_cpu(fw_hdr->feature);
	fw->feature = feature & FW_FEATURE_SIG ? feature : 0;
पूर्ण

अटल व्योम __update_firmware_info(काष्ठा rtw_dev *rtwdev,
				   काष्ठा rtw_fw_state *fw)
अणु
	स्थिर काष्ठा rtw_fw_hdr *fw_hdr =
				(स्थिर काष्ठा rtw_fw_hdr *)fw->firmware->data;

	fw->h2c_version = le16_to_cpu(fw_hdr->h2c_fmt_ver);
	fw->version = le16_to_cpu(fw_hdr->version);
	fw->sub_version = fw_hdr->subversion;
	fw->sub_index = fw_hdr->subindex;

	__update_firmware_feature(rtwdev, fw);
पूर्ण

अटल व्योम __update_firmware_info_legacy(काष्ठा rtw_dev *rtwdev,
					  काष्ठा rtw_fw_state *fw)
अणु
	काष्ठा rtw_fw_hdr_legacy *legacy =
				(काष्ठा rtw_fw_hdr_legacy *)fw->firmware->data;

	fw->h2c_version = 0;
	fw->version = le16_to_cpu(legacy->version);
	fw->sub_version = legacy->subversion1;
	fw->sub_index = legacy->subversion2;
पूर्ण

अटल व्योम update_firmware_info(काष्ठा rtw_dev *rtwdev,
				 काष्ठा rtw_fw_state *fw)
अणु
	अगर (rtw_chip_wcpu_11n(rtwdev))
		__update_firmware_info_legacy(rtwdev, fw);
	अन्यथा
		__update_firmware_info(rtwdev, fw);
पूर्ण

अटल व्योम rtw_load_firmware_cb(स्थिर काष्ठा firmware *firmware, व्योम *context)
अणु
	काष्ठा rtw_fw_state *fw = context;
	काष्ठा rtw_dev *rtwdev = fw->rtwdev;

	अगर (!firmware || !firmware->data) अणु
		rtw_err(rtwdev, "failed to request firmware\n");
		complete_all(&fw->completion);
		वापस;
	पूर्ण

	fw->firmware = firmware;
	update_firmware_info(rtwdev, fw);
	complete_all(&fw->completion);

	rtw_info(rtwdev, "Firmware version %u.%u.%u, H2C version %u\n",
		 fw->version, fw->sub_version, fw->sub_index, fw->h2c_version);
पूर्ण

अटल पूर्णांक rtw_load_firmware(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_fw_type type)
अणु
	स्थिर अक्षर *fw_name;
	काष्ठा rtw_fw_state *fw;
	पूर्णांक ret;

	चयन (type) अणु
	हाल RTW_WOWLAN_FW:
		fw = &rtwdev->wow_fw;
		fw_name = rtwdev->chip->wow_fw_name;
		अवरोध;

	हाल RTW_NORMAL_FW:
		fw = &rtwdev->fw;
		fw_name = rtwdev->chip->fw_name;
		अवरोध;

	शेष:
		rtw_warn(rtwdev, "unsupported firmware type\n");
		वापस -ENOENT;
	पूर्ण

	fw->rtwdev = rtwdev;
	init_completion(&fw->completion);

	ret = request_firmware_noरुको(THIS_MODULE, true, fw_name, rtwdev->dev,
				      GFP_KERNEL, fw, rtw_load_firmware_cb);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to async firmware request\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_chip_parameter_setup(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;

	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
		rtwdev->hci.rpwm_addr = 0x03d9;
		rtwdev->hci.cpwm_addr = 0x03da;
		अवरोध;
	शेष:
		rtw_err(rtwdev, "unsupported hci type\n");
		वापस -EINVAL;
	पूर्ण

	hal->chip_version = rtw_पढ़ो32(rtwdev, REG_SYS_CFG1);
	hal->cut_version = BIT_GET_CHIP_VER(hal->chip_version);
	hal->mp_chip = (hal->chip_version & BIT_RTL_ID) ? 0 : 1;
	अगर (hal->chip_version & BIT_RF_TYPE_ID) अणु
		hal->rf_type = RF_2T2R;
		hal->rf_path_num = 2;
		hal->antenna_tx = BB_PATH_AB;
		hal->antenna_rx = BB_PATH_AB;
	पूर्ण अन्यथा अणु
		hal->rf_type = RF_1T1R;
		hal->rf_path_num = 1;
		hal->antenna_tx = BB_PATH_A;
		hal->antenna_rx = BB_PATH_A;
	पूर्ण
	hal->rf_phy_num = chip->fix_rf_phy_num ? chip->fix_rf_phy_num :
			  hal->rf_path_num;

	efuse->physical_size = chip->phy_efuse_size;
	efuse->logical_size = chip->log_efuse_size;
	efuse->protect_size = chip->ptct_efuse_size;

	/* शेष use ack */
	rtwdev->hal.rcr |= BIT_VHT_DACK;

	hal->bfee_sts_cap = 3;

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_chip_efuse_enable(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_fw_state *fw = &rtwdev->fw;
	पूर्णांक ret;

	ret = rtw_hci_setup(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to setup hci\n");
		जाओ err;
	पूर्ण

	ret = rtw_mac_घातer_on(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to power on mac\n");
		जाओ err;
	पूर्ण

	rtw_ग_लिखो8(rtwdev, REG_C2HEVT, C2H_HW_FEATURE_DUMP);

	रुको_क्रम_completion(&fw->completion);
	अगर (!fw->firmware) अणु
		ret = -EINVAL;
		rtw_err(rtwdev, "failed to load firmware\n");
		जाओ err;
	पूर्ण

	ret = rtw_करोwnload_firmware(rtwdev, fw);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to download firmware\n");
		जाओ err_off;
	पूर्ण

	वापस 0;

err_off:
	rtw_mac_घातer_off(rtwdev);

err:
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_dump_hw_feature(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u8 hw_feature[HW_FEATURE_LEN];
	u8 id;
	u8 bw;
	पूर्णांक i;

	id = rtw_पढ़ो8(rtwdev, REG_C2HEVT);
	अगर (id != C2H_HW_FEATURE_REPORT) अणु
		rtw_err(rtwdev, "failed to read hw feature report\n");
		वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < HW_FEATURE_LEN; i++)
		hw_feature[i] = rtw_पढ़ो8(rtwdev, REG_C2HEVT + 2 + i);

	rtw_ग_लिखो8(rtwdev, REG_C2HEVT, 0);

	bw = GET_EFUSE_HW_CAP_BW(hw_feature);
	efuse->hw_cap.bw = hw_bw_cap_to_bitamp(bw);
	efuse->hw_cap.hci = GET_EFUSE_HW_CAP_HCI(hw_feature);
	efuse->hw_cap.nss = GET_EFUSE_HW_CAP_NSS(hw_feature);
	efuse->hw_cap.ptcl = GET_EFUSE_HW_CAP_PTCL(hw_feature);
	efuse->hw_cap.ant_num = GET_EFUSE_HW_CAP_ANT_NUM(hw_feature);

	rtw_hw_config_rf_ant_num(rtwdev, efuse->hw_cap.ant_num);

	अगर (efuse->hw_cap.nss == EFUSE_HW_CAP_IGNORE ||
	    efuse->hw_cap.nss > rtwdev->hal.rf_path_num)
		efuse->hw_cap.nss = rtwdev->hal.rf_path_num;

	rtw_dbg(rtwdev, RTW_DBG_EFUSE,
		"hw cap: hci=0x%02x, bw=0x%02x, ptcl=0x%02x, ant_num=%d, nss=%d\n",
		efuse->hw_cap.hci, efuse->hw_cap.bw, efuse->hw_cap.ptcl,
		efuse->hw_cap.ant_num, efuse->hw_cap.nss);

	वापस 0;
पूर्ण

अटल व्योम rtw_chip_efuse_disable(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_hci_stop(rtwdev);
	rtw_mac_घातer_off(rtwdev);
पूर्ण

अटल पूर्णांक rtw_chip_efuse_info_setup(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	पूर्णांक ret;

	mutex_lock(&rtwdev->mutex);

	/* घातer on mac to पढ़ो efuse */
	ret = rtw_chip_efuse_enable(rtwdev);
	अगर (ret)
		जाओ out_unlock;

	ret = rtw_parse_efuse_map(rtwdev);
	अगर (ret)
		जाओ out_disable;

	ret = rtw_dump_hw_feature(rtwdev);
	अगर (ret)
		जाओ out_disable;

	ret = rtw_check_supported_rfe(rtwdev);
	अगर (ret)
		जाओ out_disable;

	अगर (efuse->crystal_cap == 0xff)
		efuse->crystal_cap = 0;
	अगर (efuse->pa_type_2g == 0xff)
		efuse->pa_type_2g = 0;
	अगर (efuse->pa_type_5g == 0xff)
		efuse->pa_type_5g = 0;
	अगर (efuse->lna_type_2g == 0xff)
		efuse->lna_type_2g = 0;
	अगर (efuse->lna_type_5g == 0xff)
		efuse->lna_type_5g = 0;
	अगर (efuse->channel_plan == 0xff)
		efuse->channel_plan = 0x7f;
	अगर (efuse->rf_board_option == 0xff)
		efuse->rf_board_option = 0;
	अगर (efuse->bt_setting & BIT(0))
		efuse->share_ant = true;
	अगर (efuse->regd == 0xff)
		efuse->regd = 0;
	अगर (efuse->tx_bb_swing_setting_2g == 0xff)
		efuse->tx_bb_swing_setting_2g = 0;
	अगर (efuse->tx_bb_swing_setting_5g == 0xff)
		efuse->tx_bb_swing_setting_5g = 0;

	efuse->btcoex = (efuse->rf_board_option & 0xe0) == 0x20;
	efuse->ext_pa_2g = efuse->pa_type_2g & BIT(4) ? 1 : 0;
	efuse->ext_lna_2g = efuse->lna_type_2g & BIT(3) ? 1 : 0;
	efuse->ext_pa_5g = efuse->pa_type_5g & BIT(0) ? 1 : 0;
	efuse->ext_lna_2g = efuse->lna_type_5g & BIT(3) ? 1 : 0;

out_disable:
	rtw_chip_efuse_disable(rtwdev);

out_unlock:
	mutex_unlock(&rtwdev->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_chip_board_info_setup(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	स्थिर काष्ठा rtw_rfe_def *rfe_def = rtw_get_rfe_def(rtwdev);

	अगर (!rfe_def)
		वापस -ENODEV;

	rtw_phy_setup_phy_cond(rtwdev, 0);

	rtw_phy_init_tx_घातer(rtwdev);
	अगर (rfe_def->agc_btg_tbl)
		rtw_load_table(rtwdev, rfe_def->agc_btg_tbl);
	rtw_load_table(rtwdev, rfe_def->phy_pg_tbl);
	rtw_load_table(rtwdev, rfe_def->txpwr_lmt_tbl);
	rtw_phy_tx_घातer_by_rate_config(hal);
	rtw_phy_tx_घातer_limit_config(hal);

	वापस 0;
पूर्ण

पूर्णांक rtw_chip_info_setup(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret;

	ret = rtw_chip_parameter_setup(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to setup chip parameters\n");
		जाओ err_out;
	पूर्ण

	ret = rtw_chip_efuse_info_setup(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to setup chip efuse info\n");
		जाओ err_out;
	पूर्ण

	ret = rtw_chip_board_info_setup(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to setup chip board info\n");
		जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rtw_chip_info_setup);

अटल व्योम rtw_stats_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_traffic_stats *stats = &rtwdev->stats;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	पूर्णांक i;

	ewma_tp_init(&stats->tx_ewma_tp);
	ewma_tp_init(&stats->rx_ewma_tp);

	क्रम (i = 0; i < RTW_EVM_NUM; i++)
		ewma_evm_init(&dm_info->ewma_evm[i]);
	क्रम (i = 0; i < RTW_SNR_NUM; i++)
		ewma_snr_init(&dm_info->ewma_snr[i]);
पूर्ण

पूर्णांक rtw_core_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	पूर्णांक ret;

	INIT_LIST_HEAD(&rtwdev->rsvd_page_list);
	INIT_LIST_HEAD(&rtwdev->txqs);

	समयr_setup(&rtwdev->tx_report.purge_समयr,
		    rtw_tx_report_purge_समयr, 0);
	rtwdev->tx_wq = alloc_workqueue("rtw_tx_wq", WQ_UNBOUND | WQ_HIGHPRI, 0);

	INIT_DELAYED_WORK(&rtwdev->watch_करोg_work, rtw_watch_करोg_work);
	INIT_DELAYED_WORK(&coex->bt_relink_work, rtw_coex_bt_relink_work);
	INIT_DELAYED_WORK(&coex->bt_reenable_work, rtw_coex_bt_reenable_work);
	INIT_DELAYED_WORK(&coex->deमुक्तze_work, rtw_coex_deमुक्तze_work);
	INIT_DELAYED_WORK(&coex->wl_reमुख्य_work, rtw_coex_wl_reमुख्य_work);
	INIT_DELAYED_WORK(&coex->bt_reमुख्य_work, rtw_coex_bt_reमुख्य_work);
	INIT_DELAYED_WORK(&coex->wl_connecting_work, rtw_coex_wl_connecting_work);
	INIT_DELAYED_WORK(&coex->bt_multi_link_reमुख्य_work,
			  rtw_coex_bt_multi_link_reमुख्य_work);
	INIT_DELAYED_WORK(&coex->wl_ccklock_work, rtw_coex_wl_ccklock_work);
	INIT_WORK(&rtwdev->tx_work, rtw_tx_work);
	INIT_WORK(&rtwdev->c2h_work, rtw_c2h_work);
	INIT_WORK(&rtwdev->fw_recovery_work, rtw_fw_recovery_work);
	INIT_WORK(&rtwdev->ba_work, rtw_txq_ba_work);
	skb_queue_head_init(&rtwdev->c2h_queue);
	skb_queue_head_init(&rtwdev->coex.queue);
	skb_queue_head_init(&rtwdev->tx_report.queue);

	spin_lock_init(&rtwdev->rf_lock);
	spin_lock_init(&rtwdev->h2c.lock);
	spin_lock_init(&rtwdev->txq_lock);
	spin_lock_init(&rtwdev->tx_report.q_lock);

	mutex_init(&rtwdev->mutex);
	mutex_init(&rtwdev->coex.mutex);
	mutex_init(&rtwdev->hal.tx_घातer_mutex);

	init_रुकोqueue_head(&rtwdev->coex.रुको);
	init_completion(&rtwdev->lps_leave_check);

	rtwdev->sec.total_cam_num = 32;
	rtwdev->hal.current_channel = 1;
	set_bit(RTW_BC_MC_MACID, rtwdev->mac_id_map);

	rtw_stats_init(rtwdev);

	/* शेष rx filter setting */
	rtwdev->hal.rcr = BIT_APP_FCS | BIT_APP_MIC | BIT_APP_ICV |
			  BIT_HTC_LOC_CTRL | BIT_APP_PHYSTS |
			  BIT_AB | BIT_AM | BIT_APM;

	ret = rtw_load_firmware(rtwdev, RTW_NORMAL_FW);
	अगर (ret) अणु
		rtw_warn(rtwdev, "no firmware loaded\n");
		वापस ret;
	पूर्ण

	अगर (chip->wow_fw_name) अणु
		ret = rtw_load_firmware(rtwdev, RTW_WOWLAN_FW);
		अगर (ret) अणु
			rtw_warn(rtwdev, "no wow firmware loaded\n");
			रुको_क्रम_completion(&rtwdev->fw.completion);
			अगर (rtwdev->fw.firmware)
				release_firmware(rtwdev->fw.firmware);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtw_core_init);

व्योम rtw_core_deinit(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_fw_state *fw = &rtwdev->fw;
	काष्ठा rtw_fw_state *wow_fw = &rtwdev->wow_fw;
	काष्ठा rtw_rsvd_page *rsvd_pkt, *पंचांगp;
	अचिन्हित दीर्घ flags;

	rtw_रुको_firmware_completion(rtwdev);

	अगर (fw->firmware)
		release_firmware(fw->firmware);

	अगर (wow_fw->firmware)
		release_firmware(wow_fw->firmware);

	destroy_workqueue(rtwdev->tx_wq);
	spin_lock_irqsave(&rtwdev->tx_report.q_lock, flags);
	skb_queue_purge(&rtwdev->tx_report.queue);
	spin_unlock_irqrestore(&rtwdev->tx_report.q_lock, flags);

	list_क्रम_each_entry_safe(rsvd_pkt, पंचांगp, &rtwdev->rsvd_page_list,
				 build_list) अणु
		list_del(&rsvd_pkt->build_list);
		kमुक्त(rsvd_pkt);
	पूर्ण

	mutex_destroy(&rtwdev->mutex);
	mutex_destroy(&rtwdev->coex.mutex);
	mutex_destroy(&rtwdev->hal.tx_घातer_mutex);
पूर्ण
EXPORT_SYMBOL(rtw_core_deinit);

पूर्णांक rtw_रेजिस्टर_hw(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	पूर्णांक max_tx_headroom = 0;
	पूर्णांक ret;

	/* TODO: USB & SDIO may need extra room? */
	max_tx_headroom = rtwdev->chip->tx_pkt_desc_sz;

	hw->extra_tx_headroom = max_tx_headroom;
	hw->queues = IEEE80211_NUM_ACS;
	hw->txq_data_size = माप(काष्ठा rtw_txq);
	hw->sta_data_size = माप(काष्ठा rtw_sta_info);
	hw->vअगर_data_size = माप(काष्ठा rtw_vअगर);

	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPORTS_AMSDU_IN_AMPDU);
	ieee80211_hw_set(hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(hw, TX_AMSDU);

	hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				     BIT(NL80211_IFTYPE_AP) |
				     BIT(NL80211_IFTYPE_ADHOC) |
				     BIT(NL80211_IFTYPE_MESH_POINT);
	hw->wiphy->available_antennas_tx = hal->antenna_tx;
	hw->wiphy->available_antennas_rx = hal->antenna_rx;

	hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS |
			    WIPHY_FLAG_TDLS_EXTERNAL_SETUP;

	hw->wiphy->features |= NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR;

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CAN_REPLACE_PTK0);

#अगर_घोषित CONFIG_PM
	hw->wiphy->wowlan = rtwdev->chip->wowlan_stub;
	hw->wiphy->max_sched_scan_ssids = rtwdev->chip->max_sched_scan_ssids;
#पूर्ण_अगर
	rtw_set_supported_band(hw, rtwdev->chip);
	SET_IEEE80211_PERM_ADDR(hw, rtwdev->efuse.addr);

	rtw_regd_init(rtwdev, rtw_regd_notअगरier);

	ret = ieee80211_रेजिस्टर_hw(hw);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to register hw\n");
		वापस ret;
	पूर्ण

	अगर (regulatory_hपूर्णांक(hw->wiphy, rtwdev->regd.alpha2))
		rtw_err(rtwdev, "regulatory_hint fail\n");

	rtw_debugfs_init(rtwdev);

	rtwdev->bf_info.bfer_mu_cnt = 0;
	rtwdev->bf_info.bfer_su_cnt = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtw_रेजिस्टर_hw);

व्योम rtw_unरेजिस्टर_hw(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	ieee80211_unरेजिस्टर_hw(hw);
	rtw_unset_supported_band(hw, chip);
पूर्ण
EXPORT_SYMBOL(rtw_unरेजिस्टर_hw);

MODULE_AUTHOR("Realtek Corporation");
MODULE_DESCRIPTION("Realtek 802.11ac wireless core module");
MODULE_LICENSE("Dual BSD/GPL");
