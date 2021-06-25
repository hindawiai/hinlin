<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "rx.h"
#समावेश "ps.h"
#समावेश "debug.h"

व्योम rtw_rx_stats(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा rtw_vअगर *rtwvअगर;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस;

	अगर (!is_broadcast_ether_addr(hdr->addr1) &&
	    !is_multicast_ether_addr(hdr->addr1)) अणु
		rtwdev->stats.rx_unicast += skb->len;
		rtwdev->stats.rx_cnt++;
		अगर (vअगर) अणु
			rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
			rtwvअगर->stats.rx_unicast += skb->len;
			rtwvअगर->stats.rx_cnt++;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_rx_stats);

काष्ठा rtw_rx_addr_match_data अणु
	काष्ठा rtw_dev *rtwdev;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा rtw_rx_pkt_stat *pkt_stat;
	u8 *bssid;
पूर्ण;

अटल व्योम rtw_rx_phy_stat(काष्ठा rtw_dev *rtwdev,
			    काष्ठा rtw_rx_pkt_stat *pkt_stat,
			    काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_pkt_count *cur_pkt_cnt = &dm_info->cur_pkt_count;
	u8 rate_ss, rate_ss_evm, evm_id;
	u8 i, idx;

	dm_info->curr_rx_rate = pkt_stat->rate;

	अगर (ieee80211_is_beacon(hdr->frame_control))
		cur_pkt_cnt->num_bcn_pkt++;

	चयन (pkt_stat->rate) अणु
	हाल DESC_RATE1M...DESC_RATE11M:
		जाओ pkt_num;
	हाल DESC_RATE6M...DESC_RATE54M:
		rate_ss = 0;
		rate_ss_evm = 1;
		evm_id = RTW_EVM_OFDM;
		अवरोध;
	हाल DESC_RATEMCS0...DESC_RATEMCS7:
	हाल DESC_RATEVHT1SS_MCS0...DESC_RATEVHT1SS_MCS9:
		rate_ss = 1;
		rate_ss_evm = 1;
		evm_id = RTW_EVM_1SS;
		अवरोध;
	हाल DESC_RATEMCS8...DESC_RATEMCS15:
	हाल DESC_RATEVHT2SS_MCS0...DESC_RATEVHT2SS_MCS9:
		rate_ss = 2;
		rate_ss_evm = 2;
		evm_id = RTW_EVM_2SS_A;
		अवरोध;
	शेष:
		rtw_warn(rtwdev, "unknown pkt rate = %d\n", pkt_stat->rate);
		वापस;
	पूर्ण

	क्रम (i = 0; i < rate_ss_evm; i++) अणु
		idx = evm_id + i;
		ewma_evm_add(&dm_info->ewma_evm[idx],
			     dm_info->rx_evm_dbm[i]);
	पूर्ण

	क्रम (i = 0; i < rtwdev->hal.rf_path_num; i++) अणु
		idx = RTW_SNR_OFDM_A + 4 * rate_ss + i;
		ewma_snr_add(&dm_info->ewma_snr[idx],
			     dm_info->rx_snr[i]);
	पूर्ण
pkt_num:
	cur_pkt_cnt->num_qry_pkt[pkt_stat->rate]++;
पूर्ण

अटल व्योम rtw_rx_addr_match_iter(व्योम *data, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_rx_addr_match_data *iter_data = data;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_hdr *hdr = iter_data->hdr;
	काष्ठा rtw_dev *rtwdev = iter_data->rtwdev;
	काष्ठा rtw_sta_info *si;
	काष्ठा rtw_rx_pkt_stat *pkt_stat = iter_data->pkt_stat;
	u8 *bssid = iter_data->bssid;

	अगर (!ether_addr_equal(vअगर->bss_conf.bssid, bssid))
		वापस;

	अगर (!(ether_addr_equal(vअगर->addr, hdr->addr1) ||
	      ieee80211_is_beacon(hdr->frame_control)))
		वापस;

	rtw_rx_phy_stat(rtwdev, pkt_stat, hdr);
	sta = ieee80211_find_sta_by_अगरaddr(rtwdev->hw, hdr->addr2,
					   vअगर->addr);
	अगर (!sta)
		वापस;

	si = (काष्ठा rtw_sta_info *)sta->drv_priv;
	ewma_rssi_add(&si->avg_rssi, pkt_stat->rssi);
पूर्ण

अटल व्योम rtw_rx_addr_match(काष्ठा rtw_dev *rtwdev,
			      काष्ठा rtw_rx_pkt_stat *pkt_stat,
			      काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा rtw_rx_addr_match_data data = अणुपूर्ण;

	अगर (pkt_stat->crc_err || pkt_stat->icv_err || !pkt_stat->phy_status ||
	    ieee80211_is_ctl(hdr->frame_control))
		वापस;

	data.rtwdev = rtwdev;
	data.hdr = hdr;
	data.pkt_stat = pkt_stat;
	data.bssid = get_hdr_bssid(hdr);

	rtw_iterate_vअगरs_atomic(rtwdev, rtw_rx_addr_match_iter, &data);
पूर्ण

व्योम rtw_rx_fill_rx_status(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_rx_pkt_stat *pkt_stat,
			   काष्ठा ieee80211_hdr *hdr,
			   काष्ठा ieee80211_rx_status *rx_status,
			   u8 *phy_status)
अणु
	काष्ठा ieee80211_hw *hw = rtwdev->hw;
	u8 path;

	स_रखो(rx_status, 0, माप(*rx_status));
	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;
	अगर (pkt_stat->crc_err)
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	अगर (pkt_stat->decrypted)
		rx_status->flag |= RX_FLAG_DECRYPTED;

	अगर (pkt_stat->rate >= DESC_RATEVHT1SS_MCS0)
		rx_status->encoding = RX_ENC_VHT;
	अन्यथा अगर (pkt_stat->rate >= DESC_RATEMCS0)
		rx_status->encoding = RX_ENC_HT;

	अगर (rx_status->band == NL80211_BAND_5GHZ &&
	    pkt_stat->rate >= DESC_RATE6M &&
	    pkt_stat->rate <= DESC_RATE54M) अणु
		rx_status->rate_idx = pkt_stat->rate - DESC_RATE6M;
	पूर्ण अन्यथा अगर (rx_status->band == NL80211_BAND_2GHZ &&
		   pkt_stat->rate >= DESC_RATE1M &&
		   pkt_stat->rate <= DESC_RATE54M) अणु
		rx_status->rate_idx = pkt_stat->rate - DESC_RATE1M;
	पूर्ण अन्यथा अगर (pkt_stat->rate >= DESC_RATEMCS0) अणु
		rtw_desc_to_mcsrate(pkt_stat->rate, &rx_status->rate_idx,
				    &rx_status->nss);
	पूर्ण

	rx_status->flag |= RX_FLAG_MACTIME_START;
	rx_status->maस_समय = pkt_stat->tsf_low;

	अगर (pkt_stat->bw == RTW_CHANNEL_WIDTH_80)
		rx_status->bw = RATE_INFO_BW_80;
	अन्यथा अगर (pkt_stat->bw == RTW_CHANNEL_WIDTH_40)
		rx_status->bw = RATE_INFO_BW_40;
	अन्यथा
		rx_status->bw = RATE_INFO_BW_20;

	rx_status->संकेत = pkt_stat->संकेत_घातer;
	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		rx_status->chains |= BIT(path);
		rx_status->chain_संकेत[path] = pkt_stat->rx_घातer[path];
	पूर्ण

	rtw_rx_addr_match(rtwdev, pkt_stat, hdr);
पूर्ण
EXPORT_SYMBOL(rtw_rx_fill_rx_status);
