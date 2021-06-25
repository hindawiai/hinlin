<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "tx.h"
#समावेश "fw.h"
#समावेश "ps.h"
#समावेश "debug.h"

अटल
व्योम rtw_tx_stats(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा rtw_vअगर *rtwvअगर;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस;

	अगर (!is_broadcast_ether_addr(hdr->addr1) &&
	    !is_multicast_ether_addr(hdr->addr1)) अणु
		rtwdev->stats.tx_unicast += skb->len;
		rtwdev->stats.tx_cnt++;
		अगर (vअगर) अणु
			rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
			rtwvअगर->stats.tx_unicast += skb->len;
			rtwvअगर->stats.tx_cnt++;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtw_tx_fill_tx_desc(काष्ठा rtw_tx_pkt_info *pkt_info, काष्ठा sk_buff *skb)
अणु
	__le32 *txdesc = (__le32 *)skb->data;

	SET_TX_DESC_TXPKTSIZE(txdesc,  pkt_info->tx_pkt_size);
	SET_TX_DESC_OFFSET(txdesc, pkt_info->offset);
	SET_TX_DESC_PKT_OFFSET(txdesc, pkt_info->pkt_offset);
	SET_TX_DESC_QSEL(txdesc, pkt_info->qsel);
	SET_TX_DESC_BMC(txdesc, pkt_info->bmc);
	SET_TX_DESC_RATE_ID(txdesc, pkt_info->rate_id);
	SET_TX_DESC_DATARATE(txdesc, pkt_info->rate);
	SET_TX_DESC_DISDATAFB(txdesc, pkt_info->dis_rate_fallback);
	SET_TX_DESC_USE_RATE(txdesc, pkt_info->use_rate);
	SET_TX_DESC_SEC_TYPE(txdesc, pkt_info->sec_type);
	SET_TX_DESC_DATA_BW(txdesc, pkt_info->bw);
	SET_TX_DESC_SW_SEQ(txdesc, pkt_info->seq);
	SET_TX_DESC_MAX_AGG_NUM(txdesc, pkt_info->ampdu_factor);
	SET_TX_DESC_AMPDU_DENSITY(txdesc, pkt_info->ampdu_density);
	SET_TX_DESC_DATA_STBC(txdesc, pkt_info->stbc);
	SET_TX_DESC_DATA_LDPC(txdesc, pkt_info->ldpc);
	SET_TX_DESC_AGG_EN(txdesc, pkt_info->ampdu_en);
	SET_TX_DESC_LS(txdesc, pkt_info->ls);
	SET_TX_DESC_DATA_SHORT(txdesc, pkt_info->लघु_gi);
	SET_TX_DESC_SPE_RPT(txdesc, pkt_info->report);
	SET_TX_DESC_SW_DEFINE(txdesc, pkt_info->sn);
	SET_TX_DESC_USE_RTS(txdesc, pkt_info->rts);
	अगर (pkt_info->rts) अणु
		SET_TX_DESC_RTSRATE(txdesc, DESC_RATE24M);
		SET_TX_DESC_DATA_RTS_SHORT(txdesc, 1);
	पूर्ण
	SET_TX_DESC_DISQSELSEQ(txdesc, pkt_info->dis_qsअन्यथाq);
	SET_TX_DESC_EN_HWSEQ(txdesc, pkt_info->en_hwseq);
	SET_TX_DESC_HW_SSN_SEL(txdesc, pkt_info->hw_ssn_sel);
	SET_TX_DESC_NAVUSEHDR(txdesc, pkt_info->nav_use_hdr);
	SET_TX_DESC_BT_शून्य(txdesc, pkt_info->bt_null);
पूर्ण
EXPORT_SYMBOL(rtw_tx_fill_tx_desc);

अटल u8 get_tx_ampdu_factor(काष्ठा ieee80211_sta *sta)
अणु
	u8 exp = sta->ht_cap.ampdu_factor;

	/* the least ampdu factor is 8K, and the value in the tx desc is the
	 * max aggregation num, which represents val * 2 packets can be
	 * aggregated in an AMPDU, so here we should use 8/2=4 as the base
	 */
	वापस (BIT(2) << exp) - 1;
पूर्ण

अटल u8 get_tx_ampdu_density(काष्ठा ieee80211_sta *sta)
अणु
	वापस sta->ht_cap.ampdu_density;
पूर्ण

अटल u8 get_highest_ht_tx_rate(काष्ठा rtw_dev *rtwdev,
				 काष्ठा ieee80211_sta *sta)
अणु
	u8 rate;

	अगर (rtwdev->hal.rf_type == RF_2T2R && sta->ht_cap.mcs.rx_mask[1] != 0)
		rate = DESC_RATEMCS15;
	अन्यथा
		rate = DESC_RATEMCS7;

	वापस rate;
पूर्ण

अटल u8 get_highest_vht_tx_rate(काष्ठा rtw_dev *rtwdev,
				  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u8 rate;
	u16 tx_mcs_map;

	tx_mcs_map = le16_to_cpu(sta->vht_cap.vht_mcs.tx_mcs_map);
	अगर (efuse->hw_cap.nss == 1) अणु
		चयन (tx_mcs_map & 0x3) अणु
		हाल IEEE80211_VHT_MCS_SUPPORT_0_7:
			rate = DESC_RATEVHT1SS_MCS7;
			अवरोध;
		हाल IEEE80211_VHT_MCS_SUPPORT_0_8:
			rate = DESC_RATEVHT1SS_MCS8;
			अवरोध;
		शेष:
		हाल IEEE80211_VHT_MCS_SUPPORT_0_9:
			rate = DESC_RATEVHT1SS_MCS9;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (efuse->hw_cap.nss >= 2) अणु
		चयन ((tx_mcs_map & 0xc) >> 2) अणु
		हाल IEEE80211_VHT_MCS_SUPPORT_0_7:
			rate = DESC_RATEVHT2SS_MCS7;
			अवरोध;
		हाल IEEE80211_VHT_MCS_SUPPORT_0_8:
			rate = DESC_RATEVHT2SS_MCS8;
			अवरोध;
		शेष:
		हाल IEEE80211_VHT_MCS_SUPPORT_0_9:
			rate = DESC_RATEVHT2SS_MCS9;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rate = DESC_RATEVHT1SS_MCS9;
	पूर्ण

	वापस rate;
पूर्ण

अटल व्योम rtw_tx_report_enable(काष्ठा rtw_dev *rtwdev,
				 काष्ठा rtw_tx_pkt_info *pkt_info)
अणु
	काष्ठा rtw_tx_report *tx_report = &rtwdev->tx_report;

	/* [11:8], reserved, fills with zero
	 * [7:2],  tx report sequence number
	 * [1:0],  firmware use, fills with zero
	 */
	pkt_info->sn = (atomic_inc_वापस(&tx_report->sn) << 2) & 0xfc;
	pkt_info->report = true;
पूर्ण

व्योम rtw_tx_report_purge_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा rtw_dev *rtwdev = from_समयr(rtwdev, t, tx_report.purge_समयr);
	काष्ठा rtw_tx_report *tx_report = &rtwdev->tx_report;
	अचिन्हित दीर्घ flags;

	अगर (skb_queue_len(&tx_report->queue) == 0)
		वापस;

	rtw_dbg(rtwdev, RTW_DBG_TX, "purge skb(s) not reported by firmware\n");

	spin_lock_irqsave(&tx_report->q_lock, flags);
	skb_queue_purge(&tx_report->queue);
	spin_unlock_irqrestore(&tx_report->q_lock, flags);
पूर्ण

व्योम rtw_tx_report_enqueue(काष्ठा rtw_dev *rtwdev, काष्ठा sk_buff *skb, u8 sn)
अणु
	काष्ठा rtw_tx_report *tx_report = &rtwdev->tx_report;
	अचिन्हित दीर्घ flags;
	u8 *drv_data;

	/* pass sn to tx report handler through driver data */
	drv_data = (u8 *)IEEE80211_SKB_CB(skb)->status.status_driver_data;
	*drv_data = sn;

	spin_lock_irqsave(&tx_report->q_lock, flags);
	__skb_queue_tail(&tx_report->queue, skb);
	spin_unlock_irqrestore(&tx_report->q_lock, flags);

	mod_समयr(&tx_report->purge_समयr, jअगरfies + RTW_TX_PROBE_TIMEOUT);
पूर्ण
EXPORT_SYMBOL(rtw_tx_report_enqueue);

अटल व्योम rtw_tx_report_tx_status(काष्ठा rtw_dev *rtwdev,
				    काष्ठा sk_buff *skb, bool acked)
अणु
	काष्ठा ieee80211_tx_info *info;

	info = IEEE80211_SKB_CB(skb);
	ieee80211_tx_info_clear_status(info);
	अगर (acked)
		info->flags |= IEEE80211_TX_STAT_ACK;
	अन्यथा
		info->flags &= ~IEEE80211_TX_STAT_ACK;

	ieee80211_tx_status_irqsafe(rtwdev->hw, skb);
पूर्ण

व्योम rtw_tx_report_handle(काष्ठा rtw_dev *rtwdev, काष्ठा sk_buff *skb, पूर्णांक src)
अणु
	काष्ठा rtw_tx_report *tx_report = &rtwdev->tx_report;
	काष्ठा rtw_c2h_cmd *c2h;
	काष्ठा sk_buff *cur, *पंचांगp;
	अचिन्हित दीर्घ flags;
	u8 sn, st;
	u8 *n;

	c2h = get_c2h_from_skb(skb);

	अगर (src == C2H_CCX_TX_RPT) अणु
		sn = GET_CCX_REPORT_SEQNUM_V0(c2h->payload);
		st = GET_CCX_REPORT_STATUS_V0(c2h->payload);
	पूर्ण अन्यथा अणु
		sn = GET_CCX_REPORT_SEQNUM_V1(c2h->payload);
		st = GET_CCX_REPORT_STATUS_V1(c2h->payload);
	पूर्ण

	spin_lock_irqsave(&tx_report->q_lock, flags);
	skb_queue_walk_safe(&tx_report->queue, cur, पंचांगp) अणु
		n = (u8 *)IEEE80211_SKB_CB(cur)->status.status_driver_data;
		अगर (*n == sn) अणु
			__skb_unlink(cur, &tx_report->queue);
			rtw_tx_report_tx_status(rtwdev, cur, st == 0);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&tx_report->q_lock, flags);
पूर्ण

अटल व्योम rtw_tx_pkt_info_update_rate(काष्ठा rtw_dev *rtwdev,
					काष्ठा rtw_tx_pkt_info *pkt_info,
					काष्ठा sk_buff *skb)
अणु
	अगर (rtwdev->hal.current_band_type == RTW_BAND_2G) अणु
		pkt_info->rate_id = RTW_RATEID_B_20M;
		pkt_info->rate = DESC_RATE1M;
	पूर्ण अन्यथा अणु
		pkt_info->rate_id = RTW_RATEID_G;
		pkt_info->rate = DESC_RATE6M;
	पूर्ण
	pkt_info->use_rate = true;
	pkt_info->dis_rate_fallback = true;
पूर्ण

अटल व्योम rtw_tx_pkt_info_update_sec(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_tx_pkt_info *pkt_info,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 sec_type = 0;

	अगर (info && info->control.hw_key) अणु
		काष्ठा ieee80211_key_conf *key = info->control.hw_key;

		चयन (key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
		हाल WLAN_CIPHER_SUITE_TKIP:
			sec_type = 0x01;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			sec_type = 0x03;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	pkt_info->sec_type = sec_type;
पूर्ण

अटल व्योम rtw_tx_mgmt_pkt_info_update(काष्ठा rtw_dev *rtwdev,
					काष्ठा rtw_tx_pkt_info *pkt_info,
					काष्ठा ieee80211_sta *sta,
					काष्ठा sk_buff *skb)
अणु
	rtw_tx_pkt_info_update_rate(rtwdev, pkt_info, skb);
	pkt_info->dis_qsअन्यथाq = true;
	pkt_info->en_hwseq = true;
	pkt_info->hw_ssn_sel = 0;
	/* TODO: need to change hw port and hw ssn sel क्रम multiple vअगरs */
पूर्ण

अटल व्योम rtw_tx_data_pkt_info_update(काष्ठा rtw_dev *rtwdev,
					काष्ठा rtw_tx_pkt_info *pkt_info,
					काष्ठा ieee80211_sta *sta,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hw *hw = rtwdev->hw;
	काष्ठा rtw_sta_info *si;
	u16 seq;
	u8 ampdu_factor = 0;
	u8 ampdu_density = 0;
	bool ampdu_en = false;
	u8 rate = DESC_RATE6M;
	u8 rate_id = 6;
	u8 bw = RTW_CHANNEL_WIDTH_20;
	bool stbc = false;
	bool ldpc = false;

	seq = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;

	/* क्रम broadcast/multicast, use शेष values */
	अगर (!sta)
		जाओ out;

	अगर (info->flags & IEEE80211_TX_CTL_AMPDU) अणु
		ampdu_en = true;
		ampdu_factor = get_tx_ampdu_factor(sta);
		ampdu_density = get_tx_ampdu_density(sta);
	पूर्ण

	अगर (info->control.use_rts || skb->len > hw->wiphy->rts_threshold)
		pkt_info->rts = true;

	अगर (sta->vht_cap.vht_supported)
		rate = get_highest_vht_tx_rate(rtwdev, sta);
	अन्यथा अगर (sta->ht_cap.ht_supported)
		rate = get_highest_ht_tx_rate(rtwdev, sta);
	अन्यथा अगर (sta->supp_rates[0] <= 0xf)
		rate = DESC_RATE11M;
	अन्यथा
		rate = DESC_RATE54M;

	si = (काष्ठा rtw_sta_info *)sta->drv_priv;

	bw = si->bw_mode;
	rate_id = si->rate_id;
	stbc = si->stbc_en;
	ldpc = si->ldpc_en;

out:
	pkt_info->seq = seq;
	pkt_info->ampdu_factor = ampdu_factor;
	pkt_info->ampdu_density = ampdu_density;
	pkt_info->ampdu_en = ampdu_en;
	pkt_info->rate = rate;
	pkt_info->rate_id = rate_id;
	pkt_info->bw = bw;
	pkt_info->stbc = stbc;
	pkt_info->ldpc = ldpc;
पूर्ण

व्योम rtw_tx_pkt_info_update(काष्ठा rtw_dev *rtwdev,
			    काष्ठा rtw_tx_pkt_info *pkt_info,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा rtw_sta_info *si;
	काष्ठा ieee80211_vअगर *vअगर = शून्य;
	__le16 fc = hdr->frame_control;
	bool bmc;

	अगर (sta) अणु
		si = (काष्ठा rtw_sta_info *)sta->drv_priv;
		vअगर = si->vअगर;
	पूर्ण

	अगर (ieee80211_is_mgmt(fc) || ieee80211_is_nullfunc(fc))
		rtw_tx_mgmt_pkt_info_update(rtwdev, pkt_info, sta, skb);
	अन्यथा अगर (ieee80211_is_data(fc))
		rtw_tx_data_pkt_info_update(rtwdev, pkt_info, sta, skb);

	bmc = is_broadcast_ether_addr(hdr->addr1) ||
	      is_multicast_ether_addr(hdr->addr1);

	अगर (info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS)
		rtw_tx_report_enable(rtwdev, pkt_info);

	pkt_info->bmc = bmc;
	rtw_tx_pkt_info_update_sec(rtwdev, pkt_info, skb);
	pkt_info->tx_pkt_size = skb->len;
	pkt_info->offset = chip->tx_pkt_desc_sz;
	pkt_info->qsel = skb->priority;
	pkt_info->ls = true;

	/* maybe merge with tx status ? */
	rtw_tx_stats(rtwdev, vअगर, skb);
पूर्ण

व्योम rtw_tx_rsvd_page_pkt_info_update(काष्ठा rtw_dev *rtwdev,
				      काष्ठा rtw_tx_pkt_info *pkt_info,
				      काष्ठा sk_buff *skb,
				      क्रमागत rtw_rsvd_packet_type type)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	bool bmc;

	/* A beacon or dummy reserved page packet indicates that it is the first
	 * reserved page, and the qsel of it will be set in each hci.
	 */
	अगर (type != RSVD_BEACON && type != RSVD_DUMMY)
		pkt_info->qsel = TX_DESC_QSEL_MGMT;

	rtw_tx_pkt_info_update_rate(rtwdev, pkt_info, skb);

	bmc = is_broadcast_ether_addr(hdr->addr1) ||
	      is_multicast_ether_addr(hdr->addr1);
	pkt_info->bmc = bmc;
	pkt_info->tx_pkt_size = skb->len;
	pkt_info->offset = chip->tx_pkt_desc_sz;
	pkt_info->ls = true;
	अगर (type == RSVD_PS_POLL) अणु
		pkt_info->nav_use_hdr = true;
	पूर्ण अन्यथा अणु
		pkt_info->dis_qsअन्यथाq = true;
		pkt_info->en_hwseq = true;
		pkt_info->hw_ssn_sel = 0;
	पूर्ण
	अगर (type == RSVD_QOS_शून्य)
		pkt_info->bt_null = true;

	rtw_tx_pkt_info_update_sec(rtwdev, pkt_info, skb);

	/* TODO: need to change hw port and hw ssn sel क्रम multiple vअगरs */
पूर्ण

काष्ठा sk_buff *
rtw_tx_ग_लिखो_data_rsvd_page_get(काष्ठा rtw_dev *rtwdev,
				काष्ठा rtw_tx_pkt_info *pkt_info,
				u8 *buf, u32 size)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा sk_buff *skb;
	u32 tx_pkt_desc_sz;
	u32 length;

	tx_pkt_desc_sz = chip->tx_pkt_desc_sz;
	length = size + tx_pkt_desc_sz;
	skb = dev_alloc_skb(length);
	अगर (!skb) अणु
		rtw_err(rtwdev, "failed to alloc write data rsvd page skb\n");
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, tx_pkt_desc_sz);
	skb_put_data(skb, buf, size);
	rtw_tx_rsvd_page_pkt_info_update(rtwdev, pkt_info, skb, RSVD_BEACON);

	वापस skb;
पूर्ण
EXPORT_SYMBOL(rtw_tx_ग_लिखो_data_rsvd_page_get);

काष्ठा sk_buff *
rtw_tx_ग_लिखो_data_h2c_get(काष्ठा rtw_dev *rtwdev,
			  काष्ठा rtw_tx_pkt_info *pkt_info,
			  u8 *buf, u32 size)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा sk_buff *skb;
	u32 tx_pkt_desc_sz;
	u32 length;

	tx_pkt_desc_sz = chip->tx_pkt_desc_sz;
	length = size + tx_pkt_desc_sz;
	skb = dev_alloc_skb(length);
	अगर (!skb) अणु
		rtw_err(rtwdev, "failed to alloc write data h2c skb\n");
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, tx_pkt_desc_sz);
	skb_put_data(skb, buf, size);
	pkt_info->tx_pkt_size = size;

	वापस skb;
पूर्ण
EXPORT_SYMBOL(rtw_tx_ग_लिखो_data_h2c_get);

व्योम rtw_tx(काष्ठा rtw_dev *rtwdev,
	    काष्ठा ieee80211_tx_control *control,
	    काष्ठा sk_buff *skb)
अणु
	काष्ठा rtw_tx_pkt_info pkt_info = अणु0पूर्ण;
	पूर्णांक ret;

	rtw_tx_pkt_info_update(rtwdev, &pkt_info, control->sta, skb);
	ret = rtw_hci_tx_ग_लिखो(rtwdev, &pkt_info, skb);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to write TX skb to HCI\n");
		जाओ out;
	पूर्ण

	rtw_hci_tx_kick_off(rtwdev);

	वापस;

out:
	ieee80211_मुक्त_txskb(rtwdev->hw, skb);
पूर्ण

अटल व्योम rtw_txq_check_agg(काष्ठा rtw_dev *rtwdev,
			      काष्ठा rtw_txq *rtwtxq,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_txq *txq = rtwtxq_to_txq(rtwtxq);
	काष्ठा ieee80211_tx_info *info;
	काष्ठा rtw_sta_info *si;

	अगर (test_bit(RTW_TXQ_AMPDU, &rtwtxq->flags)) अणु
		info = IEEE80211_SKB_CB(skb);
		info->flags |= IEEE80211_TX_CTL_AMPDU;
		वापस;
	पूर्ण

	अगर (skb_get_queue_mapping(skb) == IEEE80211_AC_VO)
		वापस;

	अगर (test_bit(RTW_TXQ_BLOCK_BA, &rtwtxq->flags))
		वापस;

	अगर (unlikely(skb->protocol == cpu_to_be16(ETH_P_PAE)))
		वापस;

	अगर (!txq->sta)
		वापस;

	si = (काष्ठा rtw_sta_info *)txq->sta->drv_priv;
	set_bit(txq->tid, si->tid_ba);

	ieee80211_queue_work(rtwdev->hw, &rtwdev->ba_work);
पूर्ण

अटल पूर्णांक rtw_txq_push_skb(काष्ठा rtw_dev *rtwdev,
			    काष्ठा rtw_txq *rtwtxq,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_txq *txq = rtwtxq_to_txq(rtwtxq);
	काष्ठा rtw_tx_pkt_info pkt_info = अणु0पूर्ण;
	पूर्णांक ret;

	rtw_txq_check_agg(rtwdev, rtwtxq, skb);

	rtw_tx_pkt_info_update(rtwdev, &pkt_info, txq->sta, skb);
	ret = rtw_hci_tx_ग_लिखो(rtwdev, &pkt_info, skb);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to write TX skb to HCI\n");
		वापस ret;
	पूर्ण
	rtwtxq->last_push = jअगरfies;

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *rtw_txq_dequeue(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_txq *rtwtxq)
अणु
	काष्ठा ieee80211_txq *txq = rtwtxq_to_txq(rtwtxq);
	काष्ठा sk_buff *skb;

	skb = ieee80211_tx_dequeue(rtwdev->hw, txq);
	अगर (!skb)
		वापस शून्य;

	वापस skb;
पूर्ण

अटल व्योम rtw_txq_push(काष्ठा rtw_dev *rtwdev,
			 काष्ठा rtw_txq *rtwtxq,
			 अचिन्हित दीर्घ frames)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;
	पूर्णांक i;

	rcu_पढ़ो_lock();

	क्रम (i = 0; i < frames; i++) अणु
		skb = rtw_txq_dequeue(rtwdev, rtwtxq);
		अगर (!skb)
			अवरोध;

		ret = rtw_txq_push_skb(rtwdev, rtwtxq, skb);
		अगर (ret) अणु
			rtw_err(rtwdev, "failed to pusk skb, ret %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

व्योम rtw_tx_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा rtw_dev *rtwdev = container_of(w, काष्ठा rtw_dev, tx_work);
	काष्ठा rtw_txq *rtwtxq, *पंचांगp;

	spin_lock_bh(&rtwdev->txq_lock);

	list_क्रम_each_entry_safe(rtwtxq, पंचांगp, &rtwdev->txqs, list) अणु
		काष्ठा ieee80211_txq *txq = rtwtxq_to_txq(rtwtxq);
		अचिन्हित दीर्घ frame_cnt;
		अचिन्हित दीर्घ byte_cnt;

		ieee80211_txq_get_depth(txq, &frame_cnt, &byte_cnt);
		rtw_txq_push(rtwdev, rtwtxq, frame_cnt);

		list_del_init(&rtwtxq->list);
	पूर्ण

	rtw_hci_tx_kick_off(rtwdev);

	spin_unlock_bh(&rtwdev->txq_lock);
पूर्ण

व्योम rtw_txq_init(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा rtw_txq *rtwtxq;

	अगर (!txq)
		वापस;

	rtwtxq = (काष्ठा rtw_txq *)txq->drv_priv;
	INIT_LIST_HEAD(&rtwtxq->list);
पूर्ण

व्योम rtw_txq_cleanup(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा rtw_txq *rtwtxq;

	अगर (!txq)
		वापस;

	rtwtxq = (काष्ठा rtw_txq *)txq->drv_priv;
	spin_lock_bh(&rtwdev->txq_lock);
	अगर (!list_empty(&rtwtxq->list))
		list_del_init(&rtwtxq->list);
	spin_unlock_bh(&rtwdev->txq_lock);
पूर्ण
