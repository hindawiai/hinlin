<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2008-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 */

#समावेश <linux/export.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/mac80211.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "ieee80211_i.h"
#समावेश "rate.h"
#समावेश "mesh.h"
#समावेश "led.h"
#समावेश "wme.h"


व्योम ieee80211_tx_status_irqsafe(काष्ठा ieee80211_hw *hw,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक पंचांगp;

	skb->pkt_type = IEEE80211_TX_STATUS_MSG;
	skb_queue_tail(info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS ?
		       &local->skb_queue : &local->skb_queue_unreliable, skb);
	पंचांगp = skb_queue_len(&local->skb_queue) +
		skb_queue_len(&local->skb_queue_unreliable);
	जबतक (पंचांगp > IEEE80211_IRQSAFE_QUEUE_LIMIT &&
	       (skb = skb_dequeue(&local->skb_queue_unreliable))) अणु
		ieee80211_मुक्त_txskb(hw, skb);
		पंचांगp--;
		I802_DEBUG_INC(local->tx_status_drop);
	पूर्ण
	tasklet_schedule(&local->tasklet);
पूर्ण
EXPORT_SYMBOL(ieee80211_tx_status_irqsafe);

अटल व्योम ieee80211_handle_filtered_frame(काष्ठा ieee80211_local *local,
					    काष्ठा sta_info *sta,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	पूर्णांक ac;

	अगर (info->flags & (IEEE80211_TX_CTL_NO_PS_BUFFER |
			   IEEE80211_TX_CTL_AMPDU |
			   IEEE80211_TX_CTL_HW_80211_ENCAP)) अणु
		ieee80211_मुक्त_txskb(&local->hw, skb);
		वापस;
	पूर्ण

	/*
	 * This skb 'survived' a round-trip through the driver, and
	 * hopefully the driver didn't mangle it too badly. However,
	 * we can definitely not rely on the control inक्रमmation
	 * being correct. Clear it so we करोn't get junk there, and
	 * indicate that it needs new processing, but must not be
	 * modअगरied/encrypted again.
	 */
	स_रखो(&info->control, 0, माप(info->control));

	info->control.jअगरfies = jअगरfies;
	info->control.vअगर = &sta->sdata->vअगर;
	info->control.flags |= IEEE80211_TX_INTCFL_NEED_TXPROCESSING;
	info->flags |= IEEE80211_TX_INTFL_RETRANSMISSION;
	info->flags &= ~IEEE80211_TX_TEMPORARY_FLAGS;

	sta->status_stats.filtered++;

	/*
	 * Clear more-data bit on filtered frames, it might be set
	 * but later frames might समय out so it might have to be
	 * clear again ... It's all rather unlikely (this frame
	 * should समय out first, right?) but let's not confuse
	 * peers unnecessarily.
	 */
	अगर (hdr->frame_control & cpu_to_le16(IEEE80211_FCTL_MOREDATA))
		hdr->frame_control &= ~cpu_to_le16(IEEE80211_FCTL_MOREDATA);

	अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
		u8 *p = ieee80211_get_qos_ctl(hdr);
		पूर्णांक tid = *p & IEEE80211_QOS_CTL_TID_MASK;

		/*
		 * Clear EOSP अगर set, this could happen e.g.
		 * अगर an असलence period (us being a P2P GO)
		 * लघुens the SP.
		 */
		अगर (*p & IEEE80211_QOS_CTL_EOSP)
			*p &= ~IEEE80211_QOS_CTL_EOSP;
		ac = ieee80211_ac_from_tid(tid);
	पूर्ण अन्यथा अणु
		ac = IEEE80211_AC_BE;
	पूर्ण

	/*
	 * Clear the TX filter mask क्रम this STA when sending the next
	 * packet. If the STA went to घातer save mode, this will happen
	 * when it wakes up क्रम the next समय.
	 */
	set_sta_flag(sta, WLAN_STA_CLEAR_PS_FILT);
	ieee80211_clear_fast_xmit(sta);

	/*
	 * This code races in the following way:
	 *
	 *  (1) STA sends frame indicating it will go to sleep and करोes so
	 *  (2) hardware/firmware adds STA to filter list, passes frame up
	 *  (3) hardware/firmware processes TX fअगरo and suppresses a frame
	 *  (4) we get TX status beक्रमe having processed the frame and
	 *	knowing that the STA has gone to sleep.
	 *
	 * This is actually quite unlikely even when both those events are
	 * processed from पूर्णांकerrupts coming in quickly after one another or
	 * even at the same समय because we queue both TX status events and
	 * RX frames to be processed by a tasklet and process them in the
	 * same order that they were received or TX status last. Hence, there
	 * is no race as दीर्घ as the frame RX is processed beक्रमe the next TX
	 * status, which drivers can ensure, see below.
	 *
	 * Note that this can only happen अगर the hardware or firmware can
	 * actually add STAs to the filter list, अगर this is करोne by the
	 * driver in response to set_tim() (which will only reduce the race
	 * this whole filtering tries to solve, not completely solve it)
	 * this situation cannot happen.
	 *
	 * To completely solve this race drivers need to make sure that they
	 *  (a) करोn't mix the irq-safe/not irq-safe TX status/RX processing
	 *	functions and
	 *  (b) always process RX events beक्रमe TX status events अगर ordering
	 *      can be unknown, क्रम example with dअगरferent पूर्णांकerrupt status
	 *	bits.
	 *  (c) अगर PS mode transitions are manual (i.e. the flag
	 *      %IEEE80211_HW_AP_LINK_PS is set), always process PS state
	 *      changes beक्रमe calling TX status events अगर ordering can be
	 *	unknown.
	 */
	अगर (test_sta_flag(sta, WLAN_STA_PS_STA) &&
	    skb_queue_len(&sta->tx_filtered[ac]) < STA_MAX_TX_BUFFER) अणु
		skb_queue_tail(&sta->tx_filtered[ac], skb);
		sta_info_recalc_tim(sta);

		अगर (!समयr_pending(&local->sta_cleanup))
			mod_समयr(&local->sta_cleanup,
				  round_jअगरfies(jअगरfies +
						STA_INFO_CLEANUP_INTERVAL));
		वापस;
	पूर्ण

	अगर (!test_sta_flag(sta, WLAN_STA_PS_STA) &&
	    !(info->flags & IEEE80211_TX_INTFL_RETRIED)) अणु
		/* Software retry the packet once */
		info->flags |= IEEE80211_TX_INTFL_RETRIED;
		ieee80211_add_pending_skb(local, skb);
		वापस;
	पूर्ण

	ps_dbg_ratelimited(sta->sdata,
			   "dropped TX filtered frame, queue_len=%d PS=%d @%lu\n",
			   skb_queue_len(&sta->tx_filtered[ac]),
			   !!test_sta_flag(sta, WLAN_STA_PS_STA), jअगरfies);
	ieee80211_मुक्त_txskb(&local->hw, skb);
पूर्ण

अटल व्योम ieee80211_check_pending_bar(काष्ठा sta_info *sta, u8 *addr, u8 tid)
अणु
	काष्ठा tid_ampdu_tx *tid_tx;

	tid_tx = rcu_dereference(sta->ampdu_mlme.tid_tx[tid]);
	अगर (!tid_tx || !tid_tx->bar_pending)
		वापस;

	tid_tx->bar_pending = false;
	ieee80211_send_bar(&sta->sdata->vअगर, addr, tid, tid_tx->failed_bar_ssn);
पूर्ण

अटल व्योम ieee80211_frame_acked(काष्ठा sta_info *sta, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *) skb->data;
	काष्ठा ieee80211_local *local = sta->local;
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;

	अगर (ieee80211_is_data_qos(mgmt->frame_control)) अणु
		काष्ठा ieee80211_hdr *hdr = (व्योम *) skb->data;
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		u16 tid = qc[0] & 0xf;

		ieee80211_check_pending_bar(sta, hdr->addr1, tid);
	पूर्ण

	अगर (ieee80211_is_action(mgmt->frame_control) &&
	    !ieee80211_has_रक्षित(mgmt->frame_control) &&
	    mgmt->u.action.category == WLAN_CATEGORY_HT &&
	    mgmt->u.action.u.ht_smps.action == WLAN_HT_ACTION_SMPS &&
	    ieee80211_sdata_running(sdata)) अणु
		क्रमागत ieee80211_smps_mode smps_mode;

		चयन (mgmt->u.action.u.ht_smps.smps_control) अणु
		हाल WLAN_HT_SMPS_CONTROL_DYNAMIC:
			smps_mode = IEEE80211_SMPS_DYNAMIC;
			अवरोध;
		हाल WLAN_HT_SMPS_CONTROL_STATIC:
			smps_mode = IEEE80211_SMPS_STATIC;
			अवरोध;
		हाल WLAN_HT_SMPS_CONTROL_DISABLED:
		शेष: /* shouldn't happen since we don't send that */
			smps_mode = IEEE80211_SMPS_OFF;
			अवरोध;
		पूर्ण

		अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION) अणु
			/*
			 * This update looks racy, but isn't -- अगर we come
			 * here we've definitely got a station that we're
			 * talking to, and on a managed पूर्णांकerface that can
			 * only be the AP. And the only other place updating
			 * this variable in managed mode is beक्रमe association.
			 */
			sdata->smps_mode = smps_mode;
			ieee80211_queue_work(&local->hw, &sdata->recalc_smps);
		पूर्ण अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_AP ||
			   sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
			sta->known_smps_mode = smps_mode;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ieee80211_set_bar_pending(काष्ठा sta_info *sta, u8 tid, u16 ssn)
अणु
	काष्ठा tid_ampdu_tx *tid_tx;

	tid_tx = rcu_dereference(sta->ampdu_mlme.tid_tx[tid]);
	अगर (!tid_tx)
		वापस;

	tid_tx->failed_bar_ssn = ssn;
	tid_tx->bar_pending = true;
पूर्ण

अटल पूर्णांक ieee80211_tx_radiotap_len(काष्ठा ieee80211_tx_info *info,
				     काष्ठा ieee80211_tx_status *status)
अणु
	पूर्णांक len = माप(काष्ठा ieee80211_radiotap_header);

	/* IEEE80211_RADIOTAP_RATE rate */
	अगर (status && status->rate && !(status->rate->flags &
					(RATE_INFO_FLAGS_MCS |
					 RATE_INFO_FLAGS_DMG |
					 RATE_INFO_FLAGS_EDMG |
					 RATE_INFO_FLAGS_VHT_MCS |
					 RATE_INFO_FLAGS_HE_MCS)))
		len += 2;
	अन्यथा अगर (info->status.rates[0].idx >= 0 &&
		 !(info->status.rates[0].flags &
		   (IEEE80211_TX_RC_MCS | IEEE80211_TX_RC_VHT_MCS)))
		len += 2;

	/* IEEE80211_RADIOTAP_TX_FLAGS */
	len += 2;

	/* IEEE80211_RADIOTAP_DATA_RETRIES */
	len += 1;

	/* IEEE80211_RADIOTAP_MCS
	 * IEEE80211_RADIOTAP_VHT */
	अगर (status && status->rate) अणु
		अगर (status->rate->flags & RATE_INFO_FLAGS_MCS)
			len += 3;
		अन्यथा अगर (status->rate->flags & RATE_INFO_FLAGS_VHT_MCS)
			len = ALIGN(len, 2) + 12;
		अन्यथा अगर (status->rate->flags & RATE_INFO_FLAGS_HE_MCS)
			len = ALIGN(len, 2) + 12;
	पूर्ण अन्यथा अगर (info->status.rates[0].idx >= 0) अणु
		अगर (info->status.rates[0].flags & IEEE80211_TX_RC_MCS)
			len += 3;
		अन्यथा अगर (info->status.rates[0].flags & IEEE80211_TX_RC_VHT_MCS)
			len = ALIGN(len, 2) + 12;
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम
ieee80211_add_tx_radiotap_header(काष्ठा ieee80211_local *local,
				 काष्ठा ieee80211_supported_band *sband,
				 काष्ठा sk_buff *skb, पूर्णांक retry_count,
				 पूर्णांक rtap_len, पूर्णांक shअगरt,
				 काष्ठा ieee80211_tx_status *status)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_radiotap_header *rthdr;
	अचिन्हित अक्षर *pos;
	u16 legacy_rate = 0;
	u16 txflags;

	rthdr = skb_push(skb, rtap_len);

	स_रखो(rthdr, 0, rtap_len);
	rthdr->it_len = cpu_to_le16(rtap_len);
	rthdr->it_present =
		cpu_to_le32((1 << IEEE80211_RADIOTAP_TX_FLAGS) |
			    (1 << IEEE80211_RADIOTAP_DATA_RETRIES));
	pos = (अचिन्हित अक्षर *)(rthdr + 1);

	/*
	 * XXX: Once radiotap माला_लो the biपंचांगap reset thing the venकरोr
	 *	extensions proposal contains, we can actually report
	 *	the whole set of tries we did.
	 */

	/* IEEE80211_RADIOTAP_RATE */

	अगर (status && status->rate) अणु
		अगर (!(status->rate->flags & (RATE_INFO_FLAGS_MCS |
					     RATE_INFO_FLAGS_DMG |
					     RATE_INFO_FLAGS_EDMG |
					     RATE_INFO_FLAGS_VHT_MCS |
					     RATE_INFO_FLAGS_HE_MCS)))
			legacy_rate = status->rate->legacy;
	पूर्ण अन्यथा अगर (info->status.rates[0].idx >= 0 &&
		 !(info->status.rates[0].flags & (IEEE80211_TX_RC_MCS |
						  IEEE80211_TX_RC_VHT_MCS)))
		legacy_rate =
			sband->bitrates[info->status.rates[0].idx].bitrate;

	अगर (legacy_rate) अणु
		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_RATE);
		*pos = DIV_ROUND_UP(legacy_rate, 5 * (1 << shअगरt));
		/* padding क्रम tx flags */
		pos += 2;
	पूर्ण

	/* IEEE80211_RADIOTAP_TX_FLAGS */
	txflags = 0;
	अगर (!(info->flags & IEEE80211_TX_STAT_ACK) &&
	    !is_multicast_ether_addr(hdr->addr1))
		txflags |= IEEE80211_RADIOTAP_F_TX_FAIL;

	अगर (info->status.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
		txflags |= IEEE80211_RADIOTAP_F_TX_CTS;
	अगर (info->status.rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS)
		txflags |= IEEE80211_RADIOTAP_F_TX_RTS;

	put_unaligned_le16(txflags, pos);
	pos += 2;

	/* IEEE80211_RADIOTAP_DATA_RETRIES */
	/* क्रम now report the total retry_count */
	*pos = retry_count;
	pos++;

	अगर (status && status->rate &&
	    (status->rate->flags & RATE_INFO_FLAGS_MCS)) अणु
		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_MCS);
		pos[0] = IEEE80211_RADIOTAP_MCS_HAVE_MCS |
			 IEEE80211_RADIOTAP_MCS_HAVE_GI |
			 IEEE80211_RADIOTAP_MCS_HAVE_BW;
		अगर (status->rate->flags & RATE_INFO_FLAGS_SHORT_GI)
			pos[1] |= IEEE80211_RADIOTAP_MCS_SGI;
		अगर (status->rate->bw == RATE_INFO_BW_40)
			pos[1] |= IEEE80211_RADIOTAP_MCS_BW_40;
		pos[2] = status->rate->mcs;
		pos += 3;
	पूर्ण अन्यथा अगर (status && status->rate &&
		   (status->rate->flags & RATE_INFO_FLAGS_VHT_MCS)) अणु
		u16 known = local->hw.radiotap_vht_details &
			(IEEE80211_RADIOTAP_VHT_KNOWN_GI |
			 IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH);

		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_VHT);

		/* required alignment from rthdr */
		pos = (u8 *)rthdr + ALIGN(pos - (u8 *)rthdr, 2);

		/* u16 known - IEEE80211_RADIOTAP_VHT_KNOWN_* */
		put_unaligned_le16(known, pos);
		pos += 2;

		/* u8 flags - IEEE80211_RADIOTAP_VHT_FLAG_* */
		अगर (status->rate->flags & RATE_INFO_FLAGS_SHORT_GI)
			*pos |= IEEE80211_RADIOTAP_VHT_FLAG_SGI;
		pos++;

		/* u8 bandwidth */
		चयन (status->rate->bw) अणु
		हाल RATE_INFO_BW_160:
			*pos = 11;
			अवरोध;
		हाल RATE_INFO_BW_80:
			*pos = 4;
			अवरोध;
		हाल RATE_INFO_BW_40:
			*pos = 1;
			अवरोध;
		शेष:
			*pos = 0;
			अवरोध;
		पूर्ण
		pos++;

		/* u8 mcs_nss[4] */
		*pos = (status->rate->mcs << 4) | status->rate->nss;
		pos += 4;

		/* u8 coding */
		pos++;
		/* u8 group_id */
		pos++;
		/* u16 partial_aid */
		pos += 2;
	पूर्ण अन्यथा अगर (status && status->rate &&
		   (status->rate->flags & RATE_INFO_FLAGS_HE_MCS)) अणु
		काष्ठा ieee80211_radiotap_he *he;

		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_HE);

		/* required alignment from rthdr */
		pos = (u8 *)rthdr + ALIGN(pos - (u8 *)rthdr, 2);
		he = (काष्ठा ieee80211_radiotap_he *)pos;

		he->data1 = cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_FORMAT_SU |
					IEEE80211_RADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
					IEEE80211_RADIOTAP_HE_DATA1_DATA_DCM_KNOWN |
					IEEE80211_RADIOTAP_HE_DATA1_BW_RU_ALLOC_KNOWN);

		he->data2 = cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA2_GI_KNOWN);

#घोषणा HE_PREP(f, val) le16_encode_bits(val, IEEE80211_RADIOTAP_HE_##f)

		he->data6 |= HE_PREP(DATA6_NSTS, status->rate->nss);

#घोषणा CHECK_GI(s) \
	BUILD_BUG_ON(IEEE80211_RADIOTAP_HE_DATA5_GI_##s != \
	(पूर्णांक)NL80211_RATE_INFO_HE_GI_##s)

		CHECK_GI(0_8);
		CHECK_GI(1_6);
		CHECK_GI(3_2);

		he->data3 |= HE_PREP(DATA3_DATA_MCS, status->rate->mcs);
		he->data3 |= HE_PREP(DATA3_DATA_DCM, status->rate->he_dcm);

		he->data5 |= HE_PREP(DATA5_GI, status->rate->he_gi);

		चयन (status->rate->bw) अणु
		हाल RATE_INFO_BW_20:
			he->data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					     IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_20MHZ);
			अवरोध;
		हाल RATE_INFO_BW_40:
			he->data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					     IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_40MHZ);
			अवरोध;
		हाल RATE_INFO_BW_80:
			he->data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					     IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_80MHZ);
			अवरोध;
		हाल RATE_INFO_BW_160:
			he->data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					     IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_160MHZ);
			अवरोध;
		हाल RATE_INFO_BW_HE_RU:
#घोषणा CHECK_RU_ALLOC(s) \
	BUILD_BUG_ON(IEEE80211_RADIOTAP_HE_DATA5_DATA_BW_RU_ALLOC_##s##T != \
	NL80211_RATE_INFO_HE_RU_ALLOC_##s + 4)

			CHECK_RU_ALLOC(26);
			CHECK_RU_ALLOC(52);
			CHECK_RU_ALLOC(106);
			CHECK_RU_ALLOC(242);
			CHECK_RU_ALLOC(484);
			CHECK_RU_ALLOC(996);
			CHECK_RU_ALLOC(2x996);

			he->data5 |= HE_PREP(DATA5_DATA_BW_RU_ALLOC,
					     status->rate->he_ru_alloc + 4);
			अवरोध;
		शेष:
			WARN_ONCE(1, "Invalid SU BW %d\n", status->rate->bw);
		पूर्ण

		pos += माप(काष्ठा ieee80211_radiotap_he);
	पूर्ण

	अगर ((status && status->rate) || info->status.rates[0].idx < 0)
		वापस;

	/* IEEE80211_RADIOTAP_MCS
	 * IEEE80211_RADIOTAP_VHT */
	अगर (info->status.rates[0].flags & IEEE80211_TX_RC_MCS) अणु
		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_MCS);
		pos[0] = IEEE80211_RADIOTAP_MCS_HAVE_MCS |
			 IEEE80211_RADIOTAP_MCS_HAVE_GI |
			 IEEE80211_RADIOTAP_MCS_HAVE_BW;
		अगर (info->status.rates[0].flags & IEEE80211_TX_RC_SHORT_GI)
			pos[1] |= IEEE80211_RADIOTAP_MCS_SGI;
		अगर (info->status.rates[0].flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			pos[1] |= IEEE80211_RADIOTAP_MCS_BW_40;
		अगर (info->status.rates[0].flags & IEEE80211_TX_RC_GREEN_FIELD)
			pos[1] |= IEEE80211_RADIOTAP_MCS_FMT_GF;
		pos[2] = info->status.rates[0].idx;
		pos += 3;
	पूर्ण अन्यथा अगर (info->status.rates[0].flags & IEEE80211_TX_RC_VHT_MCS) अणु
		u16 known = local->hw.radiotap_vht_details &
			(IEEE80211_RADIOTAP_VHT_KNOWN_GI |
			 IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH);

		rthdr->it_present |= cpu_to_le32(1 << IEEE80211_RADIOTAP_VHT);

		/* required alignment from rthdr */
		pos = (u8 *)rthdr + ALIGN(pos - (u8 *)rthdr, 2);

		/* u16 known - IEEE80211_RADIOTAP_VHT_KNOWN_* */
		put_unaligned_le16(known, pos);
		pos += 2;

		/* u8 flags - IEEE80211_RADIOTAP_VHT_FLAG_* */
		अगर (info->status.rates[0].flags & IEEE80211_TX_RC_SHORT_GI)
			*pos |= IEEE80211_RADIOTAP_VHT_FLAG_SGI;
		pos++;

		/* u8 bandwidth */
		अगर (info->status.rates[0].flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			*pos = 1;
		अन्यथा अगर (info->status.rates[0].flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
			*pos = 4;
		अन्यथा अगर (info->status.rates[0].flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
			*pos = 11;
		अन्यथा /* IEEE80211_TX_RC_अणु20_MHZ_WIDTH,FIXME:DUP_DATAपूर्ण */
			*pos = 0;
		pos++;

		/* u8 mcs_nss[4] */
		*pos = (ieee80211_rate_get_vht_mcs(&info->status.rates[0]) << 4) |
			ieee80211_rate_get_vht_nss(&info->status.rates[0]);
		pos += 4;

		/* u8 coding */
		pos++;
		/* u8 group_id */
		pos++;
		/* u16 partial_aid */
		pos += 2;
	पूर्ण
पूर्ण

/*
 * Handles the tx क्रम TDLS tearकरोwn frames.
 * If the frame wasn't ACKed by the peer - it will be re-sent through the AP
 */
अटल व्योम ieee80211_tdls_td_tx_handle(काष्ठा ieee80211_local *local,
					काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा sk_buff *skb, u32 flags)
अणु
	काष्ठा sk_buff *tearकरोwn_skb;
	काष्ठा sk_buff *orig_tearकरोwn_skb;
	bool is_tearकरोwn = false;

	/* Get the tearकरोwn data we need and मुक्त the lock */
	spin_lock(&sdata->u.mgd.tearकरोwn_lock);
	tearकरोwn_skb = sdata->u.mgd.tearकरोwn_skb;
	orig_tearकरोwn_skb = sdata->u.mgd.orig_tearकरोwn_skb;
	अगर ((skb == orig_tearकरोwn_skb) && tearकरोwn_skb) अणु
		sdata->u.mgd.tearकरोwn_skb = शून्य;
		sdata->u.mgd.orig_tearकरोwn_skb = शून्य;
		is_tearकरोwn = true;
	पूर्ण
	spin_unlock(&sdata->u.mgd.tearकरोwn_lock);

	अगर (is_tearकरोwn) अणु
		/* This mechanism relies on being able to get ACKs */
		WARN_ON(!ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS));

		/* Check अगर peer has ACKed */
		अगर (flags & IEEE80211_TX_STAT_ACK) अणु
			dev_kमुक्त_skb_any(tearकरोwn_skb);
		पूर्ण अन्यथा अणु
			tdls_dbg(sdata,
				 "TDLS Resending teardown through AP\n");

			ieee80211_subअगर_start_xmit(tearकरोwn_skb, skb->dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा ieee80211_sub_अगर_data *
ieee80211_sdata_from_skb(काष्ठा ieee80211_local *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	अगर (skb->dev) अणु
		list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
			अगर (!sdata->dev)
				जारी;

			अगर (skb->dev == sdata->dev)
				वापस sdata;
		पूर्ण

		वापस शून्य;
	पूर्ण

	वापस rcu_dereference(local->p2p_sdata);
पूर्ण

अटल व्योम ieee80211_report_ack_skb(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_tx_info *info,
				     bool acked, bool dropped)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&local->ack_status_lock, flags);
	skb = idr_हटाओ(&local->ack_status_frames, info->ack_frame_id);
	spin_unlock_irqrestore(&local->ack_status_lock, flags);

	अगर (!skb)
		वापस;

	अगर (info->flags & IEEE80211_TX_INTFL_NL80211_FRAME_TX) अणु
		u64 cookie = IEEE80211_SKB_CB(skb)->ack.cookie;
		काष्ठा ieee80211_sub_अगर_data *sdata;
		काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;

		rcu_पढ़ो_lock();
		sdata = ieee80211_sdata_from_skb(local, skb);
		अगर (sdata) अणु
			अगर (skb->protocol == sdata->control_port_protocol ||
			    skb->protocol == cpu_to_be16(ETH_P_PREAUTH))
				cfg80211_control_port_tx_status(&sdata->wdev,
								cookie,
								skb->data,
								skb->len,
								acked,
								GFP_ATOMIC);
			अन्यथा अगर (ieee80211_is_any_nullfunc(hdr->frame_control))
				cfg80211_probe_status(sdata->dev, hdr->addr1,
						      cookie, acked,
						      info->status.ack_संकेत,
						      info->status.is_valid_ack_संकेत,
						      GFP_ATOMIC);
			अन्यथा अगर (ieee80211_is_mgmt(hdr->frame_control))
				cfg80211_mgmt_tx_status(&sdata->wdev, cookie,
							skb->data, skb->len,
							acked, GFP_ATOMIC);
			अन्यथा
				pr_warn("Unknown status report in ack skb\n");

		पूर्ण
		rcu_पढ़ो_unlock();

		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अगर (dropped) अणु
		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अणु
		/* consumes skb */
		skb_complete_wअगरi_ack(skb, acked);
	पूर्ण
पूर्ण

अटल व्योम ieee80211_report_used_skb(काष्ठा ieee80211_local *local,
				      काष्ठा sk_buff *skb, bool dropped)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u16 tx_समय_est = ieee80211_info_get_tx_समय_est(info);
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	bool acked = info->flags & IEEE80211_TX_STAT_ACK;

	अगर (dropped)
		acked = false;

	अगर (tx_समय_est) अणु
		काष्ठा sta_info *sta;

		rcu_पढ़ो_lock();

		sta = sta_info_get_by_addrs(local, hdr->addr1, hdr->addr2);
		ieee80211_sta_update_pending_airसमय(local, sta,
						     skb_get_queue_mapping(skb),
						     tx_समय_est,
						     true);
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (info->flags & IEEE80211_TX_INTFL_MLME_CONN_TX) अणु
		काष्ठा ieee80211_sub_अगर_data *sdata;

		rcu_पढ़ो_lock();

		sdata = ieee80211_sdata_from_skb(local, skb);

		अगर (!sdata) अणु
			skb->dev = शून्य;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक hdr_size =
				ieee80211_hdrlen(hdr->frame_control);

			/* Check to see अगर packet is a TDLS tearकरोwn packet */
			अगर (ieee80211_is_data(hdr->frame_control) &&
			    (ieee80211_get_tdls_action(skb, hdr_size) ==
			     WLAN_TDLS_TEARDOWN))
				ieee80211_tdls_td_tx_handle(local, sdata, skb,
							    info->flags);
			अन्यथा
				ieee80211_mgd_conn_tx_status(sdata,
							     hdr->frame_control,
							     acked);
		पूर्ण

		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अगर (info->ack_frame_id) अणु
		ieee80211_report_ack_skb(local, info, acked, dropped);
	पूर्ण

	अगर (!dropped && skb->deकाष्ठाor) अणु
		skb->wअगरi_acked_valid = 1;
		skb->wअगरi_acked = acked;
	पूर्ण

	ieee80211_led_tx(local);

	अगर (skb_has_frag_list(skb)) अणु
		kमुक्त_skb_list(skb_shinfo(skb)->frag_list);
		skb_shinfo(skb)->frag_list = शून्य;
	पूर्ण
पूर्ण

/*
 * Use a अटल threshold क्रम now, best value to be determined
 * by testing ...
 * Should it depend on:
 *  - on # of retransmissions
 *  - current throughput (higher value क्रम higher tpt)?
 */
#घोषणा STA_LOST_PKT_THRESHOLD	50
#घोषणा STA_LOST_PKT_TIME	HZ		/* 1 sec since last ACK */
#घोषणा STA_LOST_TDLS_PKT_THRESHOLD	10
#घोषणा STA_LOST_TDLS_PKT_TIME		(10*HZ) /* 10secs since last ACK */

अटल व्योम ieee80211_lost_packet(काष्ठा sta_info *sta,
				  काष्ठा ieee80211_tx_info *info)
अणु
	अचिन्हित दीर्घ pkt_समय = STA_LOST_PKT_TIME;
	अचिन्हित पूर्णांक pkt_thr = STA_LOST_PKT_THRESHOLD;

	/* If driver relies on its own algorithm क्रम station kickout, skip
	 * mac80211 packet loss mechanism.
	 */
	अगर (ieee80211_hw_check(&sta->local->hw, REPORTS_LOW_ACK))
		वापस;

	/* This packet was aggregated but करोesn't carry status info */
	अगर ((info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    !(info->flags & IEEE80211_TX_STAT_AMPDU))
		वापस;

	sta->status_stats.lost_packets++;
	अगर (sta->sta.tdls) अणु
		pkt_समय = STA_LOST_TDLS_PKT_TIME;
		pkt_thr = STA_LOST_PKT_THRESHOLD;
	पूर्ण

	/*
	 * If we're in TDLS mode, make sure that all STA_LOST_TDLS_PKT_THRESHOLD
	 * of the last packets were lost, and that no ACK was received in the
	 * last STA_LOST_TDLS_PKT_TIME ms, beक्रमe triggering the CQM packet-loss
	 * mechanism.
	 * For non-TDLS, use STA_LOST_PKT_THRESHOLD and STA_LOST_PKT_TIME
	 */
	अगर (sta->status_stats.lost_packets < pkt_thr ||
	    !समय_after(jअगरfies, sta->status_stats.last_pkt_समय + pkt_समय))
		वापस;

	cfg80211_cqm_pktloss_notअगरy(sta->sdata->dev, sta->sta.addr,
				    sta->status_stats.lost_packets, GFP_ATOMIC);
	sta->status_stats.lost_packets = 0;
पूर्ण

अटल पूर्णांक ieee80211_tx_get_rates(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_tx_info *info,
				  पूर्णांक *retry_count)
अणु
	पूर्णांक count = -1;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++) अणु
		अगर ((info->flags & IEEE80211_TX_CTL_AMPDU) &&
		    !(info->flags & IEEE80211_TX_STAT_AMPDU)) अणु
			/* just the first aggr frame carry status info */
			info->status.rates[i].idx = -1;
			info->status.rates[i].count = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (info->status.rates[i].idx < 0) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (i >= hw->max_report_rates) अणु
			/* the HW cannot have attempted that rate */
			info->status.rates[i].idx = -1;
			info->status.rates[i].count = 0;
			अवरोध;
		पूर्ण

		count += info->status.rates[i].count;
	पूर्ण

	अगर (count < 0)
		count = 0;

	*retry_count = count;
	वापस i - 1;
पूर्ण

व्योम ieee80211_tx_monitor(काष्ठा ieee80211_local *local, काष्ठा sk_buff *skb,
			  काष्ठा ieee80211_supported_band *sband,
			  पूर्णांक retry_count, पूर्णांक shअगरt, bool send_to_cooked,
			  काष्ठा ieee80211_tx_status *status)
अणु
	काष्ठा sk_buff *skb2;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा net_device *prev_dev = शून्य;
	पूर्णांक rtap_len;

	/* send frame to monitor पूर्णांकerfaces now */
	rtap_len = ieee80211_tx_radiotap_len(info, status);
	अगर (WARN_ON_ONCE(skb_headroom(skb) < rtap_len)) अणु
		pr_err("ieee80211_tx_status: headroom too small\n");
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण
	ieee80211_add_tx_radiotap_header(local, sband, skb, retry_count,
					 rtap_len, shअगरt, status);

	/* XXX: is this sufficient क्रम BPF? */
	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);
	स_रखो(skb->cb, 0, माप(skb->cb));

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (sdata->vअगर.type == NL80211_IFTYPE_MONITOR) अणु
			अगर (!ieee80211_sdata_running(sdata))
				जारी;

			अगर ((sdata->u.mntr.flags & MONITOR_FLAG_COOK_FRAMES) &&
			    !send_to_cooked)
				जारी;

			अगर (prev_dev) अणु
				skb2 = skb_clone(skb, GFP_ATOMIC);
				अगर (skb2) अणु
					skb2->dev = prev_dev;
					netअगर_rx(skb2);
				पूर्ण
			पूर्ण

			prev_dev = sdata->dev;
		पूर्ण
	पूर्ण
	अगर (prev_dev) अणु
		skb->dev = prev_dev;
		netअगर_rx(skb);
		skb = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम __ieee80211_tx_status(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_tx_status *status,
				  पूर्णांक rates_idx, पूर्णांक retry_count)
अणु
	काष्ठा sk_buff *skb = status->skb;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_tx_info *info = status->info;
	काष्ठा sta_info *sta;
	__le16 fc;
	काष्ठा ieee80211_supported_band *sband;
	bool send_to_cooked;
	bool acked;
	bool noack_success;
	काष्ठा ieee80211_bar *bar;
	पूर्णांक shअगरt = 0;
	पूर्णांक tid = IEEE80211_NUM_TIDS;

	sband = local->hw.wiphy->bands[info->band];
	fc = hdr->frame_control;

	अगर (status->sta) अणु
		sta = container_of(status->sta, काष्ठा sta_info, sta);
		shअगरt = ieee80211_vअगर_get_shअगरt(&sta->sdata->vअगर);

		अगर (info->flags & IEEE80211_TX_STATUS_EOSP)
			clear_sta_flag(sta, WLAN_STA_SP);

		acked = !!(info->flags & IEEE80211_TX_STAT_ACK);
		noack_success = !!(info->flags &
				   IEEE80211_TX_STAT_NOACK_TRANSMITTED);

		/* mesh Peer Service Period support */
		अगर (ieee80211_vअगर_is_mesh(&sta->sdata->vअगर) &&
		    ieee80211_is_data_qos(fc))
			ieee80211_mpsp_trigger_process(
				ieee80211_get_qos_ctl(hdr), sta, true, acked);

		अगर (ieee80211_hw_check(&local->hw, HAS_RATE_CONTROL) &&
		    (ieee80211_is_data(hdr->frame_control)) &&
		    (rates_idx != -1))
			sta->tx_stats.last_rate =
				info->status.rates[rates_idx];

		अगर ((info->flags & IEEE80211_TX_STAT_AMPDU_NO_BACK) &&
		    (ieee80211_is_data_qos(fc))) अणु
			u16 ssn;
			u8 *qc;

			qc = ieee80211_get_qos_ctl(hdr);
			tid = qc[0] & 0xf;
			ssn = ((le16_to_cpu(hdr->seq_ctrl) + 0x10)
						& IEEE80211_SCTL_SEQ);
			ieee80211_send_bar(&sta->sdata->vअगर, hdr->addr1,
					   tid, ssn);
		पूर्ण अन्यथा अगर (ieee80211_is_data_qos(fc)) अणु
			u8 *qc = ieee80211_get_qos_ctl(hdr);

			tid = qc[0] & 0xf;
		पूर्ण

		अगर (!acked && ieee80211_is_back_req(fc)) अणु
			u16 control;

			/*
			 * BAR failed, store the last SSN and retry sending
			 * the BAR when the next unicast transmission on the
			 * same TID succeeds.
			 */
			bar = (काष्ठा ieee80211_bar *) skb->data;
			control = le16_to_cpu(bar->control);
			अगर (!(control & IEEE80211_BAR_CTRL_MULTI_TID)) अणु
				u16 ssn = le16_to_cpu(bar->start_seq_num);

				tid = (control &
				       IEEE80211_BAR_CTRL_TID_INFO_MASK) >>
				      IEEE80211_BAR_CTRL_TID_INFO_SHIFT;

				ieee80211_set_bar_pending(sta, tid, ssn);
			पूर्ण
		पूर्ण

		अगर (info->flags & IEEE80211_TX_STAT_TX_FILTERED) अणु
			ieee80211_handle_filtered_frame(local, sta, skb);
			वापस;
		पूर्ण अन्यथा अगर (ieee80211_is_data_present(fc)) अणु
			अगर (!acked && !noack_success)
				sta->status_stats.msdu_failed[tid]++;

			sta->status_stats.msdu_retries[tid] +=
				retry_count;
		पूर्ण

		अगर (!(info->flags & IEEE80211_TX_CTL_INJECTED) && acked)
			ieee80211_frame_acked(sta, skb);

	पूर्ण

	/* SNMP counters
	 * Fragments are passed to low-level drivers as separate skbs, so these
	 * are actually fragments, not frames. Update frame counters only क्रम
	 * the first fragment of the frame. */
	अगर ((info->flags & IEEE80211_TX_STAT_ACK) ||
	    (info->flags & IEEE80211_TX_STAT_NOACK_TRANSMITTED)) अणु
		अगर (ieee80211_is_first_frag(hdr->seq_ctrl)) अणु
			I802_DEBUG_INC(local->करोt11TransmittedFrameCount);
			अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)))
				I802_DEBUG_INC(local->करोt11MulticastTransmittedFrameCount);
			अगर (retry_count > 0)
				I802_DEBUG_INC(local->करोt11RetryCount);
			अगर (retry_count > 1)
				I802_DEBUG_INC(local->करोt11MultipleRetryCount);
		पूर्ण

		/* This counter shall be incremented क्रम an acknowledged MPDU
		 * with an inभागidual address in the address 1 field or an MPDU
		 * with a multicast address in the address 1 field of type Data
		 * or Management. */
		अगर (!is_multicast_ether_addr(hdr->addr1) ||
		    ieee80211_is_data(fc) ||
		    ieee80211_is_mgmt(fc))
			I802_DEBUG_INC(local->करोt11TransmittedFragmentCount);
	पूर्ण अन्यथा अणु
		अगर (ieee80211_is_first_frag(hdr->seq_ctrl))
			I802_DEBUG_INC(local->करोt11FailedCount);
	पूर्ण

	अगर (ieee80211_is_any_nullfunc(fc) &&
	    ieee80211_has_pm(fc) &&
	    ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS) &&
	    !(info->flags & IEEE80211_TX_CTL_INJECTED) &&
	    local->ps_sdata && !(local->scanning)) अणु
		अगर (info->flags & IEEE80211_TX_STAT_ACK) अणु
			local->ps_sdata->u.mgd.flags |=
					IEEE80211_STA_शून्यFUNC_ACKED;
		पूर्ण अन्यथा
			mod_समयr(&local->dynamic_ps_समयr, jअगरfies +
					msecs_to_jअगरfies(10));
	पूर्ण

	ieee80211_report_used_skb(local, skb, false);

	/* this was a transmitted frame, but now we want to reuse it */
	skb_orphan(skb);

	/* Need to make a copy beक्रमe skb->cb माला_लो cleared */
	send_to_cooked = !!(info->flags & IEEE80211_TX_CTL_INJECTED) ||
			 !(ieee80211_is_data(fc));

	/*
	 * This is a bit racy but we can aव्योम a lot of work
	 * with this test...
	 */
	अगर (!local->monitors && (!send_to_cooked || !local->cooked_mntrs)) अणु
		अगर (status->मुक्त_list)
			list_add_tail(&skb->list, status->मुक्त_list);
		अन्यथा
			dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* send to monitor पूर्णांकerfaces */
	ieee80211_tx_monitor(local, skb, sband, retry_count, shअगरt,
			     send_to_cooked, status);
पूर्ण

व्योम ieee80211_tx_status(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_tx_status status = अणु
		.skb = skb,
		.info = IEEE80211_SKB_CB(skb),
	पूर्ण;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();

	sta = sta_info_get_by_addrs(local, hdr->addr1, hdr->addr2);
	अगर (sta)
		status.sta = &sta->sta;

	ieee80211_tx_status_ext(hw, &status);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee80211_tx_status);

व्योम ieee80211_tx_status_ext(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_tx_status *status)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_tx_info *info = status->info;
	काष्ठा ieee80211_sta *pubsta = status->sta;
	काष्ठा sk_buff *skb = status->skb;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा sta_info *sta = शून्य;
	पूर्णांक rates_idx, retry_count;
	bool acked, noack_success;
	u16 tx_समय_est;

	अगर (pubsta) अणु
		sta = container_of(pubsta, काष्ठा sta_info, sta);

		अगर (status->rate)
			sta->tx_stats.last_rate_info = *status->rate;
	पूर्ण

	अगर (skb && (tx_समय_est =
		    ieee80211_info_get_tx_समय_est(IEEE80211_SKB_CB(skb))) > 0) अणु
		/* Do this here to aव्योम the expensive lookup of the sta
		 * in ieee80211_report_used_skb().
		 */
		ieee80211_sta_update_pending_airसमय(local, sta,
						     skb_get_queue_mapping(skb),
						     tx_समय_est,
						     true);
		ieee80211_info_set_tx_समय_est(IEEE80211_SKB_CB(skb), 0);
	पूर्ण

	अगर (!status->info)
		जाओ मुक्त;

	rates_idx = ieee80211_tx_get_rates(hw, info, &retry_count);

	sband = hw->wiphy->bands[info->band];

	acked = !!(info->flags & IEEE80211_TX_STAT_ACK);
	noack_success = !!(info->flags & IEEE80211_TX_STAT_NOACK_TRANSMITTED);

	अगर (pubsta) अणु
		काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;

		अगर (!acked && !noack_success)
			sta->status_stats.retry_failed++;
		sta->status_stats.retry_count += retry_count;

		अगर (ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS)) अणु
			अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
			    skb && !(info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP))
				ieee80211_sta_tx_notअगरy(sdata, (व्योम *) skb->data,
							acked, info->status.tx_समय);

			अगर (acked) अणु
				sta->status_stats.last_ack = jअगरfies;

				अगर (sta->status_stats.lost_packets)
					sta->status_stats.lost_packets = 0;

				/* Track when last packet was ACKed */
				sta->status_stats.last_pkt_समय = jअगरfies;

				/* Reset connection monitor */
				अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
				    unlikely(sdata->u.mgd.probe_send_count > 0))
					sdata->u.mgd.probe_send_count = 0;

				अगर (info->status.is_valid_ack_संकेत) अणु
					sta->status_stats.last_ack_संकेत =
							 (s8)info->status.ack_संकेत;
					sta->status_stats.ack_संकेत_filled = true;
					ewma_avg_संकेत_add(&sta->status_stats.avg_ack_संकेत,
							    -info->status.ack_संकेत);
				पूर्ण
			पूर्ण अन्यथा अगर (test_sta_flag(sta, WLAN_STA_PS_STA)) अणु
				/*
				 * The STA is in घातer save mode, so assume
				 * that this TX packet failed because of that.
				 */
				अगर (skb)
					ieee80211_handle_filtered_frame(local, sta, skb);
				वापस;
			पूर्ण अन्यथा अगर (noack_success) अणु
				/* nothing to करो here, करो not account as lost */
			पूर्ण अन्यथा अणु
				ieee80211_lost_packet(sta, info);
			पूर्ण
		पूर्ण

		rate_control_tx_status(local, sband, status);
		अगर (ieee80211_vअगर_is_mesh(&sta->sdata->vअगर))
			ieee80211s_update_metric(local, sta, status);
	पूर्ण

	अगर (skb && !(info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP))
		वापस __ieee80211_tx_status(hw, status, rates_idx,
					     retry_count);

	अगर (acked || noack_success) अणु
		I802_DEBUG_INC(local->करोt11TransmittedFrameCount);
		अगर (!pubsta)
			I802_DEBUG_INC(local->करोt11MulticastTransmittedFrameCount);
		अगर (retry_count > 0)
			I802_DEBUG_INC(local->करोt11RetryCount);
		अगर (retry_count > 1)
			I802_DEBUG_INC(local->करोt11MultipleRetryCount);
	पूर्ण अन्यथा अणु
		I802_DEBUG_INC(local->करोt11FailedCount);
	पूर्ण

मुक्त:
	अगर (!skb)
		वापस;

	ieee80211_report_used_skb(local, skb, false);
	अगर (status->मुक्त_list)
		list_add_tail(&skb->list, status->मुक्त_list);
	अन्यथा
		dev_kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(ieee80211_tx_status_ext);

व्योम ieee80211_tx_rate_update(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_sta *pubsta,
			      काष्ठा ieee80211_tx_info *info)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_supported_band *sband = hw->wiphy->bands[info->band];
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	काष्ठा ieee80211_tx_status status = अणु
		.info = info,
		.sta = pubsta,
	पूर्ण;

	rate_control_tx_status(local, sband, &status);

	अगर (ieee80211_hw_check(&local->hw, HAS_RATE_CONTROL))
		sta->tx_stats.last_rate = info->status.rates[0];
पूर्ण
EXPORT_SYMBOL(ieee80211_tx_rate_update);

व्योम ieee80211_tx_status_8023(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_tx_status status = अणु
		.skb = skb,
		.info = IEEE80211_SKB_CB(skb),
	पूर्ण;
	काष्ठा sta_info *sta;

	sdata = vअगर_to_sdata(vअगर);

	rcu_पढ़ो_lock();

	अगर (!ieee80211_lookup_ra_sta(sdata, skb, &sta) && !IS_ERR(sta))
		status.sta = &sta->sta;

	ieee80211_tx_status_ext(hw, &status);

	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee80211_tx_status_8023);

व्योम ieee80211_report_low_ack(काष्ठा ieee80211_sta *pubsta, u32 num_packets)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	cfg80211_cqm_pktloss_notअगरy(sta->sdata->dev, sta->sta.addr,
				    num_packets, GFP_ATOMIC);
पूर्ण
EXPORT_SYMBOL(ieee80211_report_low_ack);

व्योम ieee80211_मुक्त_txskb(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	ieee80211_report_used_skb(local, skb, true);
	dev_kमुक्त_skb_any(skb);
पूर्ण
EXPORT_SYMBOL(ieee80211_मुक्त_txskb);

व्योम ieee80211_purge_tx_queue(काष्ठा ieee80211_hw *hw,
			      काष्ठा sk_buff_head *skbs)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(skbs)))
		ieee80211_मुक्त_txskb(hw, skb);
पूर्ण
