<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 *
 * Transmit and frame generation functions.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>
#समावेश <net/codel.h>
#समावेश <net/codel_impl.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/fq_impl.h>

#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "led.h"
#समावेश "mesh.h"
#समावेश "wep.h"
#समावेश "wpa.h"
#समावेश "wme.h"
#समावेश "rate.h"

/* misc utils */

अटल __le16 ieee80211_duration(काष्ठा ieee80211_tx_data *tx,
				 काष्ठा sk_buff *skb, पूर्णांक group_addr,
				 पूर्णांक next_frag_len)
अणु
	पूर्णांक rate, mrate, erp, dur, i, shअगरt = 0;
	काष्ठा ieee80211_rate *txrate;
	काष्ठा ieee80211_local *local = tx->local;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	u32 rate_flags = 0;

	/* assume HW handles this */
	अगर (tx->rate.flags & (IEEE80211_TX_RC_MCS | IEEE80211_TX_RC_VHT_MCS))
		वापस 0;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(tx->sdata->vअगर.chanctx_conf);
	अगर (chanctx_conf) अणु
		shअगरt = ieee80211_chandef_get_shअगरt(&chanctx_conf->def);
		rate_flags = ieee80211_chandef_rate_flags(&chanctx_conf->def);
	पूर्ण
	rcu_पढ़ो_unlock();

	/* uh huh? */
	अगर (WARN_ON_ONCE(tx->rate.idx < 0))
		वापस 0;

	sband = local->hw.wiphy->bands[info->band];
	txrate = &sband->bitrates[tx->rate.idx];

	erp = txrate->flags & IEEE80211_RATE_ERP_G;

	/* device is expected to करो this */
	अगर (sband->band == NL80211_BAND_S1GHZ)
		वापस 0;

	/*
	 * data and mgmt (except PS Poll):
	 * - during CFP: 32768
	 * - during contention period:
	 *   अगर addr1 is group address: 0
	 *   अगर more fragments = 0 and addr1 is inभागidual address: समय to
	 *      transmit one ACK plus SIFS
	 *   अगर more fragments = 1 and addr1 is inभागidual address: समय to
	 *      transmit next fragment plus 2 x ACK plus 3 x SIFS
	 *
	 * IEEE 802.11, 9.6:
	 * - control response frame (CTS or ACK) shall be transmitted using the
	 *   same rate as the immediately previous frame in the frame exchange
	 *   sequence, अगर this rate beदीर्घs to the PHY mandatory rates, or अन्यथा
	 *   at the highest possible rate beदीर्घing to the PHY rates in the
	 *   BSSBasicRateSet
	 */
	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	अगर (ieee80211_is_ctl(hdr->frame_control)) अणु
		/* TODO: These control frames are not currently sent by
		 * mac80211, but should they be implemented, this function
		 * needs to be updated to support duration field calculation.
		 *
		 * RTS: समय needed to transmit pending data/mgmt frame plus
		 *    one CTS frame plus one ACK frame plus 3 x SIFS
		 * CTS: duration of immediately previous RTS minus समय
		 *    required to transmit CTS and its SIFS
		 * ACK: 0 अगर immediately previous directed data/mgmt had
		 *    more=0, with more=1 duration in ACK frame is duration
		 *    from previous frame minus समय needed to transmit ACK
		 *    and its SIFS
		 * PS Poll: BIT(15) | BIT(14) | aid
		 */
		वापस 0;
	पूर्ण

	/* data/mgmt */
	अगर (0 /* FIX: data/mgmt during CFP */)
		वापस cpu_to_le16(32768);

	अगर (group_addr) /* Group address as the destination - no ACK */
		वापस 0;

	/* Inभागidual destination address:
	 * IEEE 802.11, Ch. 9.6 (after IEEE 802.11g changes)
	 * CTS and ACK frames shall be transmitted using the highest rate in
	 * basic rate set that is less than or equal to the rate of the
	 * immediately previous frame and that is using the same modulation
	 * (CCK or OFDM). If no basic rate set matches with these requirements,
	 * the highest mandatory rate of the PHY that is less than or equal to
	 * the rate of the previous frame is used.
	 * Mandatory rates क्रम IEEE 802.11g PHY: 1, 2, 5.5, 11, 6, 12, 24 Mbps
	 */
	rate = -1;
	/* use lowest available अगर everything fails */
	mrate = sband->bitrates[0].bitrate;
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		काष्ठा ieee80211_rate *r = &sband->bitrates[i];

		अगर (r->bitrate > txrate->bitrate)
			अवरोध;

		अगर ((rate_flags & r->flags) != rate_flags)
			जारी;

		अगर (tx->sdata->vअगर.bss_conf.basic_rates & BIT(i))
			rate = DIV_ROUND_UP(r->bitrate, 1 << shअगरt);

		चयन (sband->band) अणु
		हाल NL80211_BAND_2GHZ: अणु
			u32 flag;
			अगर (tx->sdata->flags & IEEE80211_SDATA_OPERATING_GMODE)
				flag = IEEE80211_RATE_MANDATORY_G;
			अन्यथा
				flag = IEEE80211_RATE_MANDATORY_B;
			अगर (r->flags & flag)
				mrate = r->bitrate;
			अवरोध;
		पूर्ण
		हाल NL80211_BAND_5GHZ:
		हाल NL80211_BAND_6GHZ:
			अगर (r->flags & IEEE80211_RATE_MANDATORY_A)
				mrate = r->bitrate;
			अवरोध;
		हाल NL80211_BAND_S1GHZ:
		हाल NL80211_BAND_60GHZ:
			/* TODO, क्रम now fall through */
		हाल NUM_NL80211_BANDS:
			WARN_ON(1);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (rate == -1) अणु
		/* No matching basic rate found; use highest suitable mandatory
		 * PHY rate */
		rate = DIV_ROUND_UP(mrate, 1 << shअगरt);
	पूर्ण

	/* Don't calculate ACKs क्रम QoS Frames with NoAck Policy set */
	अगर (ieee80211_is_data_qos(hdr->frame_control) &&
	    *(ieee80211_get_qos_ctl(hdr)) & IEEE80211_QOS_CTL_ACK_POLICY_NOACK)
		dur = 0;
	अन्यथा
		/* Time needed to transmit ACK
		 * (10 bytes + 4-byte FCS = 112 bits) plus SIFS; rounded up
		 * to बंदst पूर्णांकeger */
		dur = ieee80211_frame_duration(sband->band, 10, rate, erp,
				tx->sdata->vअगर.bss_conf.use_लघु_preamble,
				shअगरt);

	अगर (next_frag_len) अणु
		/* Frame is fragmented: duration increases with समय needed to
		 * transmit next fragment plus ACK and 2 x SIFS. */
		dur *= 2; /* ACK + SIFS */
		/* next fragment */
		dur += ieee80211_frame_duration(sband->band, next_frag_len,
				txrate->bitrate, erp,
				tx->sdata->vअगर.bss_conf.use_लघु_preamble,
				shअगरt);
	पूर्ण

	वापस cpu_to_le16(dur);
पूर्ण

/* tx handlers */
अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_dynamic_ps(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा ieee80211_local *local = tx->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);

	/* driver करोesn't support घातer save */
	अगर (!ieee80211_hw_check(&local->hw, SUPPORTS_PS))
		वापस TX_CONTINUE;

	/* hardware करोes dynamic घातer save */
	अगर (ieee80211_hw_check(&local->hw, SUPPORTS_DYNAMIC_PS))
		वापस TX_CONTINUE;

	/* dynamic घातer save disabled */
	अगर (local->hw.conf.dynamic_ps_समयout <= 0)
		वापस TX_CONTINUE;

	/* we are scanning, करोn't enable घातer save */
	अगर (local->scanning)
		वापस TX_CONTINUE;

	अगर (!local->ps_sdata)
		वापस TX_CONTINUE;

	/* No poपूर्णांक अगर we're going to suspend */
	अगर (local->quiescing)
		वापस TX_CONTINUE;

	/* dynamic ps is supported only in managed mode */
	अगर (tx->sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस TX_CONTINUE;

	अगर (unlikely(info->flags & IEEE80211_TX_INTFL_OFFCHAN_TX_OK))
		वापस TX_CONTINUE;

	अगरmgd = &tx->sdata->u.mgd;

	/*
	 * Don't wakeup from घातer save अगर u-apsd is enabled, voip ac has
	 * u-apsd enabled and the frame is in voip class. This effectively
	 * means that even अगर all access categories have u-apsd enabled, in
	 * practise u-apsd is only used with the voip ac. This is a
	 * workaround क्रम the हाल when received voip class packets करो not
	 * have correct qos tag क्रम some reason, due the network or the
	 * peer application.
	 *
	 * Note: अगरmgd->uapsd_queues access is racy here. If the value is
	 * changed via debugfs, user needs to reassociate manually to have
	 * everything in sync.
	 */
	अगर ((अगरmgd->flags & IEEE80211_STA_UAPSD_ENABLED) &&
	    (अगरmgd->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO) &&
	    skb_get_queue_mapping(tx->skb) == IEEE80211_AC_VO)
		वापस TX_CONTINUE;

	अगर (local->hw.conf.flags & IEEE80211_CONF_PS) अणु
		ieee80211_stop_queues_by_reason(&local->hw,
						IEEE80211_MAX_QUEUE_MAP,
						IEEE80211_QUEUE_STOP_REASON_PS,
						false);
		अगरmgd->flags &= ~IEEE80211_STA_शून्यFUNC_ACKED;
		ieee80211_queue_work(&local->hw,
				     &local->dynamic_ps_disable_work);
	पूर्ण

	/* Don't restart the timer if we're not disassociated */
	अगर (!अगरmgd->associated)
		वापस TX_CONTINUE;

	mod_समयr(&local->dynamic_ps_समयr, jअगरfies +
		  msecs_to_jअगरfies(local->hw.conf.dynamic_ps_समयout));

	वापस TX_CONTINUE;
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_check_assoc(काष्ठा ieee80211_tx_data *tx)
अणु

	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)tx->skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	bool assoc = false;

	अगर (unlikely(info->flags & IEEE80211_TX_CTL_INJECTED))
		वापस TX_CONTINUE;

	अगर (unlikely(test_bit(SCAN_SW_SCANNING, &tx->local->scanning)) &&
	    test_bit(SDATA_STATE_OFFCHANNEL, &tx->sdata->state) &&
	    !ieee80211_is_probe_req(hdr->frame_control) &&
	    !ieee80211_is_any_nullfunc(hdr->frame_control))
		/*
		 * When software scanning only nullfunc frames (to notअगरy
		 * the sleep state to the AP) and probe requests (क्रम the
		 * active scan) are allowed, all other frames should not be
		 * sent and we should not get here, but अगर we करो
		 * nonetheless, drop them to aव्योम sending them
		 * off-channel. See the link below and
		 * ieee80211_start_scan() क्रम more.
		 *
		 * http://article.gmane.org/gmane.linux.kernel.wireless.general/30089
		 */
		वापस TX_DROP;

	अगर (tx->sdata->vअगर.type == NL80211_IFTYPE_OCB)
		वापस TX_CONTINUE;

	अगर (tx->flags & IEEE80211_TX_PS_BUFFERED)
		वापस TX_CONTINUE;

	अगर (tx->sta)
		assoc = test_sta_flag(tx->sta, WLAN_STA_ASSOC);

	अगर (likely(tx->flags & IEEE80211_TX_UNICAST)) अणु
		अगर (unlikely(!assoc &&
			     ieee80211_is_data(hdr->frame_control))) अणु
#अगर_घोषित CONFIG_MAC80211_VERBOSE_DEBUG
			sdata_info(tx->sdata,
				   "dropped data frame to not associated station %pM\n",
				   hdr->addr1);
#पूर्ण_अगर
			I802_DEBUG_INC(tx->local->tx_handlers_drop_not_assoc);
			वापस TX_DROP;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(ieee80211_is_data(hdr->frame_control) &&
			    ieee80211_vअगर_get_num_mcast_अगर(tx->sdata) == 0)) अणु
		/*
		 * No associated STAs - no need to send multicast
		 * frames.
		 */
		वापस TX_DROP;
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण

/* This function is called whenever the AP is about to exceed the maximum limit
 * of buffered frames क्रम घातer saving STAs. This situation should not really
 * happen often during normal operation, so dropping the oldest buffered packet
 * from each queue should be OK to make some room क्रम new frames. */
अटल व्योम purge_old_ps_buffers(काष्ठा ieee80211_local *local)
अणु
	पूर्णांक total = 0, purged = 0;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sta_info *sta;

	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		काष्ठा ps_data *ps;

		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
			ps = &sdata->u.ap.ps;
		अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
			ps = &sdata->u.mesh.ps;
		अन्यथा
			जारी;

		skb = skb_dequeue(&ps->bc_buf);
		अगर (skb) अणु
			purged++;
			ieee80211_मुक्त_txskb(&local->hw, skb);
		पूर्ण
		total += skb_queue_len(&ps->bc_buf);
	पूर्ण

	/*
	 * Drop one frame from each station from the lowest-priority
	 * AC that has frames at all.
	 */
	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		पूर्णांक ac;

		क्रम (ac = IEEE80211_AC_BK; ac >= IEEE80211_AC_VO; ac--) अणु
			skb = skb_dequeue(&sta->ps_tx_buf[ac]);
			total += skb_queue_len(&sta->ps_tx_buf[ac]);
			अगर (skb) अणु
				purged++;
				ieee80211_मुक्त_txskb(&local->hw, skb);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	local->total_ps_buffered = total;
	ps_dbg_hw(&local->hw, "PS buffers full - purged %d frames\n", purged);
पूर्ण

अटल ieee80211_tx_result
ieee80211_tx_h_multicast_ps_buf(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)tx->skb->data;
	काष्ठा ps_data *ps;

	/*
	 * broadcast/multicast frame
	 *
	 * If any of the associated/peer stations is in घातer save mode,
	 * the frame is buffered to be sent after DTIM beacon frame.
	 * This is करोne either by the hardware or us.
	 */

	/* घातersaving STAs currently only in AP/VLAN/mesh mode */
	अगर (tx->sdata->vअगर.type == NL80211_IFTYPE_AP ||
	    tx->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		अगर (!tx->sdata->bss)
			वापस TX_CONTINUE;

		ps = &tx->sdata->bss->ps;
	पूर्ण अन्यथा अगर (ieee80211_vअगर_is_mesh(&tx->sdata->vअगर)) अणु
		ps = &tx->sdata->u.mesh.ps;
	पूर्ण अन्यथा अणु
		वापस TX_CONTINUE;
	पूर्ण


	/* no buffering क्रम ordered frames */
	अगर (ieee80211_has_order(hdr->frame_control))
		वापस TX_CONTINUE;

	अगर (ieee80211_is_probe_req(hdr->frame_control))
		वापस TX_CONTINUE;

	अगर (ieee80211_hw_check(&tx->local->hw, QUEUE_CONTROL))
		info->hw_queue = tx->sdata->vअगर.cab_queue;

	/* no stations in PS mode and no buffered packets */
	अगर (!atomic_पढ़ो(&ps->num_sta_ps) && skb_queue_empty(&ps->bc_buf))
		वापस TX_CONTINUE;

	info->flags |= IEEE80211_TX_CTL_SEND_AFTER_DTIM;

	/* device releases frame after DTIM beacon */
	अगर (!ieee80211_hw_check(&tx->local->hw, HOST_BROADCAST_PS_BUFFERING))
		वापस TX_CONTINUE;

	/* buffered in mac80211 */
	अगर (tx->local->total_ps_buffered >= TOTAL_MAX_TX_BUFFER)
		purge_old_ps_buffers(tx->local);

	अगर (skb_queue_len(&ps->bc_buf) >= AP_MAX_BC_BUFFER) अणु
		ps_dbg(tx->sdata,
		       "BC TX buffer full - dropping the oldest frame\n");
		ieee80211_मुक्त_txskb(&tx->local->hw, skb_dequeue(&ps->bc_buf));
	पूर्ण अन्यथा
		tx->local->total_ps_buffered++;

	skb_queue_tail(&ps->bc_buf, tx->skb);

	वापस TX_QUEUED;
पूर्ण

अटल पूर्णांक ieee80211_use_mfp(__le16 fc, काष्ठा sta_info *sta,
			     काष्ठा sk_buff *skb)
अणु
	अगर (!ieee80211_is_mgmt(fc))
		वापस 0;

	अगर (sta == शून्य || !test_sta_flag(sta, WLAN_STA_MFP))
		वापस 0;

	अगर (!ieee80211_is_robust_mgmt_frame(skb))
		वापस 0;

	वापस 1;
पूर्ण

अटल ieee80211_tx_result
ieee80211_tx_h_unicast_ps_buf(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sta_info *sta = tx->sta;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)tx->skb->data;
	काष्ठा ieee80211_local *local = tx->local;

	अगर (unlikely(!sta))
		वापस TX_CONTINUE;

	अगर (unlikely((test_sta_flag(sta, WLAN_STA_PS_STA) ||
		      test_sta_flag(sta, WLAN_STA_PS_DRIVER) ||
		      test_sta_flag(sta, WLAN_STA_PS_DELIVER)) &&
		     !(info->flags & IEEE80211_TX_CTL_NO_PS_BUFFER))) अणु
		पूर्णांक ac = skb_get_queue_mapping(tx->skb);

		अगर (ieee80211_is_mgmt(hdr->frame_control) &&
		    !ieee80211_is_bufferable_mmpdu(hdr->frame_control)) अणु
			info->flags |= IEEE80211_TX_CTL_NO_PS_BUFFER;
			वापस TX_CONTINUE;
		पूर्ण

		ps_dbg(sta->sdata, "STA %pM aid %d: PS buffer for AC %d\n",
		       sta->sta.addr, sta->sta.aid, ac);
		अगर (tx->local->total_ps_buffered >= TOTAL_MAX_TX_BUFFER)
			purge_old_ps_buffers(tx->local);

		/* sync with ieee80211_sta_ps_deliver_wakeup */
		spin_lock(&sta->ps_lock);
		/*
		 * STA woke up the meanसमय and all the frames on ps_tx_buf have
		 * been queued to pending queue. No reordering can happen, go
		 * ahead and Tx the packet.
		 */
		अगर (!test_sta_flag(sta, WLAN_STA_PS_STA) &&
		    !test_sta_flag(sta, WLAN_STA_PS_DRIVER) &&
		    !test_sta_flag(sta, WLAN_STA_PS_DELIVER)) अणु
			spin_unlock(&sta->ps_lock);
			वापस TX_CONTINUE;
		पूर्ण

		अगर (skb_queue_len(&sta->ps_tx_buf[ac]) >= STA_MAX_TX_BUFFER) अणु
			काष्ठा sk_buff *old = skb_dequeue(&sta->ps_tx_buf[ac]);
			ps_dbg(tx->sdata,
			       "STA %pM TX buffer for AC %d full - dropping oldest frame\n",
			       sta->sta.addr, ac);
			ieee80211_मुक्त_txskb(&local->hw, old);
		पूर्ण अन्यथा
			tx->local->total_ps_buffered++;

		info->control.jअगरfies = jअगरfies;
		info->control.vअगर = &tx->sdata->vअगर;
		info->control.flags |= IEEE80211_TX_INTCFL_NEED_TXPROCESSING;
		info->flags &= ~IEEE80211_TX_TEMPORARY_FLAGS;
		skb_queue_tail(&sta->ps_tx_buf[ac], tx->skb);
		spin_unlock(&sta->ps_lock);

		अगर (!समयr_pending(&local->sta_cleanup))
			mod_समयr(&local->sta_cleanup,
				  round_jअगरfies(jअगरfies +
						STA_INFO_CLEANUP_INTERVAL));

		/*
		 * We queued up some frames, so the TIM bit might
		 * need to be set, recalculate it.
		 */
		sta_info_recalc_tim(sta);

		वापस TX_QUEUED;
	पूर्ण अन्यथा अगर (unlikely(test_sta_flag(sta, WLAN_STA_PS_STA))) अणु
		ps_dbg(tx->sdata,
		       "STA %pM in PS mode, but polling/in SP -> send frame\n",
		       sta->sta.addr);
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_ps_buf(काष्ठा ieee80211_tx_data *tx)
अणु
	अगर (unlikely(tx->flags & IEEE80211_TX_PS_BUFFERED))
		वापस TX_CONTINUE;

	अगर (tx->flags & IEEE80211_TX_UNICAST)
		वापस ieee80211_tx_h_unicast_ps_buf(tx);
	अन्यथा
		वापस ieee80211_tx_h_multicast_ps_buf(tx);
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_check_control_port_protocol(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);

	अगर (unlikely(tx->sdata->control_port_protocol == tx->skb->protocol)) अणु
		अगर (tx->sdata->control_port_no_encrypt)
			info->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;
		info->control.flags |= IEEE80211_TX_CTRL_PORT_CTRL_PROTO;
		info->flags |= IEEE80211_TX_CTL_USE_MINRATE;
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_select_key(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा ieee80211_key *key;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)tx->skb->data;

	अगर (unlikely(info->flags & IEEE80211_TX_INTFL_DONT_ENCRYPT)) अणु
		tx->key = शून्य;
		वापस TX_CONTINUE;
	पूर्ण

	अगर (tx->sta &&
	    (key = rcu_dereference(tx->sta->ptk[tx->sta->ptk_idx])))
		tx->key = key;
	अन्यथा अगर (ieee80211_is_group_privacy_action(tx->skb) &&
		(key = rcu_dereference(tx->sdata->शेष_multicast_key)))
		tx->key = key;
	अन्यथा अगर (ieee80211_is_mgmt(hdr->frame_control) &&
		 is_multicast_ether_addr(hdr->addr1) &&
		 ieee80211_is_robust_mgmt_frame(tx->skb) &&
		 (key = rcu_dereference(tx->sdata->शेष_mgmt_key)))
		tx->key = key;
	अन्यथा अगर (is_multicast_ether_addr(hdr->addr1) &&
		 (key = rcu_dereference(tx->sdata->शेष_multicast_key)))
		tx->key = key;
	अन्यथा अगर (!is_multicast_ether_addr(hdr->addr1) &&
		 (key = rcu_dereference(tx->sdata->शेष_unicast_key)))
		tx->key = key;
	अन्यथा
		tx->key = शून्य;

	अगर (tx->key) अणु
		bool skip_hw = false;

		/* TODO: add threshold stuff again */

		चयन (tx->key->conf.cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
		हाल WLAN_CIPHER_SUITE_TKIP:
			अगर (!ieee80211_is_data_present(hdr->frame_control))
				tx->key = शून्य;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
		हाल WLAN_CIPHER_SUITE_CCMP_256:
		हाल WLAN_CIPHER_SUITE_GCMP:
		हाल WLAN_CIPHER_SUITE_GCMP_256:
			अगर (!ieee80211_is_data_present(hdr->frame_control) &&
			    !ieee80211_use_mfp(hdr->frame_control, tx->sta,
					       tx->skb) &&
			    !ieee80211_is_group_privacy_action(tx->skb))
				tx->key = शून्य;
			अन्यथा
				skip_hw = (tx->key->conf.flags &
					   IEEE80211_KEY_FLAG_SW_MGMT_TX) &&
					ieee80211_is_mgmt(hdr->frame_control);
			अवरोध;
		हाल WLAN_CIPHER_SUITE_AES_CMAC:
		हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
			अगर (!ieee80211_is_mgmt(hdr->frame_control))
				tx->key = शून्य;
			अवरोध;
		पूर्ण

		अगर (unlikely(tx->key && tx->key->flags & KEY_FLAG_TAINTED &&
			     !ieee80211_is_deauth(hdr->frame_control)))
			वापस TX_DROP;

		अगर (!skip_hw && tx->key &&
		    tx->key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE)
			info->control.hw_key = &tx->key->conf;
	पूर्ण अन्यथा अगर (ieee80211_is_data_present(hdr->frame_control) && tx->sta &&
		   test_sta_flag(tx->sta, WLAN_STA_USES_ENCRYPTION)) अणु
		वापस TX_DROP;
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_rate_ctrl(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	काष्ठा ieee80211_hdr *hdr = (व्योम *)tx->skb->data;
	काष्ठा ieee80211_supported_band *sband;
	u32 len;
	काष्ठा ieee80211_tx_rate_control txrc;
	काष्ठा ieee80211_sta_rates *ratetbl = शून्य;
	bool assoc = false;

	स_रखो(&txrc, 0, माप(txrc));

	sband = tx->local->hw.wiphy->bands[info->band];

	len = min_t(u32, tx->skb->len + FCS_LEN,
			 tx->local->hw.wiphy->frag_threshold);

	/* set up the tx rate control काष्ठा we give the RC algo */
	txrc.hw = &tx->local->hw;
	txrc.sband = sband;
	txrc.bss_conf = &tx->sdata->vअगर.bss_conf;
	txrc.skb = tx->skb;
	txrc.reported_rate.idx = -1;
	txrc.rate_idx_mask = tx->sdata->rc_rateidx_mask[info->band];

	अगर (tx->sdata->rc_has_mcs_mask[info->band])
		txrc.rate_idx_mcs_mask =
			tx->sdata->rc_rateidx_mcs_mask[info->band];

	txrc.bss = (tx->sdata->vअगर.type == NL80211_IFTYPE_AP ||
		    tx->sdata->vअगर.type == NL80211_IFTYPE_MESH_POINT ||
		    tx->sdata->vअगर.type == NL80211_IFTYPE_ADHOC ||
		    tx->sdata->vअगर.type == NL80211_IFTYPE_OCB);

	/* set up RTS protection अगर desired */
	अगर (len > tx->local->hw.wiphy->rts_threshold) अणु
		txrc.rts = true;
	पूर्ण

	info->control.use_rts = txrc.rts;
	info->control.use_cts_prot = tx->sdata->vअगर.bss_conf.use_cts_prot;

	/*
	 * Use लघु preamble अगर the BSS can handle it, but not क्रम
	 * management frames unless we know the receiver can handle
	 * that -- the management frame might be to a station that
	 * just wants a probe response.
	 */
	अगर (tx->sdata->vअगर.bss_conf.use_लघु_preamble &&
	    (ieee80211_is_data(hdr->frame_control) ||
	     (tx->sta && test_sta_flag(tx->sta, WLAN_STA_SHORT_PREAMBLE))))
		txrc.लघु_preamble = true;

	info->control.लघु_preamble = txrc.लघु_preamble;

	/* करोn't ask rate control when rate alपढ़ोy injected via radiotap */
	अगर (info->control.flags & IEEE80211_TX_CTRL_RATE_INJECT)
		वापस TX_CONTINUE;

	अगर (tx->sta)
		assoc = test_sta_flag(tx->sta, WLAN_STA_ASSOC);

	/*
	 * Lets not bother rate control अगर we're associated and cannot
	 * talk to the sta. This should not happen.
	 */
	अगर (WARN(test_bit(SCAN_SW_SCANNING, &tx->local->scanning) && assoc &&
		 !rate_usable_index_exists(sband, &tx->sta->sta),
		 "%s: Dropped data frame as no usable bitrate found while "
		 "scanning and associated. Target station: "
		 "%pM on %d GHz band\n",
		 tx->sdata->name, hdr->addr1,
		 info->band ? 5 : 2))
		वापस TX_DROP;

	/*
	 * If we're associated with the sta at this poपूर्णांक we know we can at
	 * least send the frame at the lowest bit rate.
	 */
	rate_control_get_rate(tx->sdata, tx->sta, &txrc);

	अगर (tx->sta && !info->control.skip_table)
		ratetbl = rcu_dereference(tx->sta->sta.rates);

	अगर (unlikely(info->control.rates[0].idx < 0)) अणु
		अगर (ratetbl) अणु
			काष्ठा ieee80211_tx_rate rate = अणु
				.idx = ratetbl->rate[0].idx,
				.flags = ratetbl->rate[0].flags,
				.count = ratetbl->rate[0].count
			पूर्ण;

			अगर (ratetbl->rate[0].idx < 0)
				वापस TX_DROP;

			tx->rate = rate;
		पूर्ण अन्यथा अणु
			वापस TX_DROP;
		पूर्ण
	पूर्ण अन्यथा अणु
		tx->rate = info->control.rates[0];
	पूर्ण

	अगर (txrc.reported_rate.idx < 0) अणु
		txrc.reported_rate = tx->rate;
		अगर (tx->sta && ieee80211_is_data(hdr->frame_control))
			tx->sta->tx_stats.last_rate = txrc.reported_rate;
	पूर्ण अन्यथा अगर (tx->sta)
		tx->sta->tx_stats.last_rate = txrc.reported_rate;

	अगर (ratetbl)
		वापस TX_CONTINUE;

	अगर (unlikely(!info->control.rates[0].count))
		info->control.rates[0].count = 1;

	अगर (WARN_ON_ONCE((info->control.rates[0].count > 1) &&
			 (info->flags & IEEE80211_TX_CTL_NO_ACK)))
		info->control.rates[0].count = 1;

	वापस TX_CONTINUE;
पूर्ण

अटल __le16 ieee80211_tx_next_seq(काष्ठा sta_info *sta, पूर्णांक tid)
अणु
	u16 *seq = &sta->tid_seq[tid];
	__le16 ret = cpu_to_le16(*seq);

	/* Increase the sequence number. */
	*seq = (*seq + 0x10) & IEEE80211_SCTL_SEQ;

	वापस ret;
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_sequence(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)tx->skb->data;
	पूर्णांक tid;

	/*
	 * Packet injection may want to control the sequence
	 * number, अगर we have no matching पूर्णांकerface then we
	 * neither assign one ourselves nor ask the driver to.
	 */
	अगर (unlikely(info->control.vअगर->type == NL80211_IFTYPE_MONITOR))
		वापस TX_CONTINUE;

	अगर (unlikely(ieee80211_is_ctl(hdr->frame_control)))
		वापस TX_CONTINUE;

	अगर (ieee80211_hdrlen(hdr->frame_control) < 24)
		वापस TX_CONTINUE;

	अगर (ieee80211_is_qos_nullfunc(hdr->frame_control))
		वापस TX_CONTINUE;

	अगर (info->control.flags & IEEE80211_TX_CTRL_NO_SEQNO)
		वापस TX_CONTINUE;

	/*
	 * Anything but QoS data that has a sequence number field
	 * (is दीर्घ enough) माला_लो a sequence number from the global
	 * counter.  QoS data frames with a multicast destination
	 * also use the global counter (802.11-2012 9.3.2.10).
	 */
	अगर (!ieee80211_is_data_qos(hdr->frame_control) ||
	    is_multicast_ether_addr(hdr->addr1)) अणु
		/* driver should assign sequence number */
		info->flags |= IEEE80211_TX_CTL_ASSIGN_SEQ;
		/* क्रम pure STA mode without beacons, we can करो it */
		hdr->seq_ctrl = cpu_to_le16(tx->sdata->sequence_number);
		tx->sdata->sequence_number += 0x10;
		अगर (tx->sta)
			tx->sta->tx_stats.msdu[IEEE80211_NUM_TIDS]++;
		वापस TX_CONTINUE;
	पूर्ण

	/*
	 * This should be true क्रम injected/management frames only, क्रम
	 * management frames we have set the IEEE80211_TX_CTL_ASSIGN_SEQ
	 * above since they are not QoS-data frames.
	 */
	अगर (!tx->sta)
		वापस TX_CONTINUE;

	/* include per-STA, per-TID sequence counter */
	tid = ieee80211_get_tid(hdr);
	tx->sta->tx_stats.msdu[tid]++;

	hdr->seq_ctrl = ieee80211_tx_next_seq(tx->sta, tid);

	वापस TX_CONTINUE;
पूर्ण

अटल पूर्णांक ieee80211_fragment(काष्ठा ieee80211_tx_data *tx,
			      काष्ठा sk_buff *skb, पूर्णांक hdrlen,
			      पूर्णांक frag_threshold)
अणु
	काष्ठा ieee80211_local *local = tx->local;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *पंचांगp;
	पूर्णांक per_fragm = frag_threshold - hdrlen - FCS_LEN;
	पूर्णांक pos = hdrlen + per_fragm;
	पूर्णांक rem = skb->len - hdrlen - per_fragm;

	अगर (WARN_ON(rem < 0))
		वापस -EINVAL;

	/* first fragment was alपढ़ोy added to queue by caller */

	जबतक (rem) अणु
		पूर्णांक fraglen = per_fragm;

		अगर (fraglen > rem)
			fraglen = rem;
		rem -= fraglen;
		पंचांगp = dev_alloc_skb(local->tx_headroom +
				    frag_threshold +
				    tx->sdata->encrypt_headroom +
				    IEEE80211_ENCRYPT_TAILROOM);
		अगर (!पंचांगp)
			वापस -ENOMEM;

		__skb_queue_tail(&tx->skbs, पंचांगp);

		skb_reserve(पंचांगp,
			    local->tx_headroom + tx->sdata->encrypt_headroom);

		/* copy control inक्रमmation */
		स_नकल(पंचांगp->cb, skb->cb, माप(पंचांगp->cb));

		info = IEEE80211_SKB_CB(पंचांगp);
		info->flags &= ~(IEEE80211_TX_CTL_CLEAR_PS_FILT |
				 IEEE80211_TX_CTL_FIRST_FRAGMENT);

		अगर (rem)
			info->flags |= IEEE80211_TX_CTL_MORE_FRAMES;

		skb_copy_queue_mapping(पंचांगp, skb);
		पंचांगp->priority = skb->priority;
		पंचांगp->dev = skb->dev;

		/* copy header and data */
		skb_put_data(पंचांगp, skb->data, hdrlen);
		skb_put_data(पंचांगp, skb->data + pos, fraglen);

		pos += fraglen;
	पूर्ण

	/* adjust first fragment's length */
	skb_trim(skb, hdrlen + per_fragm);
	वापस 0;
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_fragment(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb = tx->skb;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	पूर्णांक frag_threshold = tx->local->hw.wiphy->frag_threshold;
	पूर्णांक hdrlen;
	पूर्णांक fragnum;

	/* no matter what happens, tx->skb moves to tx->skbs */
	__skb_queue_tail(&tx->skbs, skb);
	tx->skb = शून्य;

	अगर (info->flags & IEEE80211_TX_CTL_DONTFRAG)
		वापस TX_CONTINUE;

	अगर (ieee80211_hw_check(&tx->local->hw, SUPPORTS_TX_FRAG))
		वापस TX_CONTINUE;

	/*
	 * Warn when submitting a fragmented A-MPDU frame and drop it.
	 * This scenario is handled in ieee80211_tx_prepare but extra
	 * caution taken here as fragmented ampdu may cause Tx stop.
	 */
	अगर (WARN_ON(info->flags & IEEE80211_TX_CTL_AMPDU))
		वापस TX_DROP;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);

	/* पूर्णांकernal error, why isn't DONTFRAG set? */
	अगर (WARN_ON(skb->len + FCS_LEN <= frag_threshold))
		वापस TX_DROP;

	/*
	 * Now fragment the frame. This will allocate all the fragments and
	 * chain them (using skb as the first fragment) to skb->next.
	 * During transmission, we will हटाओ the successfully transmitted
	 * fragments from this list. When the low-level driver rejects one
	 * of the fragments then we will simply pretend to accept the skb
	 * but store it away as pending.
	 */
	अगर (ieee80211_fragment(tx, skb, hdrlen, frag_threshold))
		वापस TX_DROP;

	/* update duration/seq/flags of fragments */
	fragnum = 0;

	skb_queue_walk(&tx->skbs, skb) अणु
		स्थिर __le16 morefrags = cpu_to_le16(IEEE80211_FCTL_MOREFRAGS);

		hdr = (व्योम *)skb->data;
		info = IEEE80211_SKB_CB(skb);

		अगर (!skb_queue_is_last(&tx->skbs, skb)) अणु
			hdr->frame_control |= morefrags;
			/*
			 * No multi-rate retries क्रम fragmented frames, that
			 * would completely throw off the NAV at other STAs.
			 */
			info->control.rates[1].idx = -1;
			info->control.rates[2].idx = -1;
			info->control.rates[3].idx = -1;
			BUILD_BUG_ON(IEEE80211_TX_MAX_RATES != 4);
			info->flags &= ~IEEE80211_TX_CTL_RATE_CTRL_PROBE;
		पूर्ण अन्यथा अणु
			hdr->frame_control &= ~morefrags;
		पूर्ण
		hdr->seq_ctrl |= cpu_to_le16(fragnum & IEEE80211_SCTL_FRAG);
		fragnum++;
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_stats(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ac = -1;

	अगर (!tx->sta)
		वापस TX_CONTINUE;

	skb_queue_walk(&tx->skbs, skb) अणु
		ac = skb_get_queue_mapping(skb);
		tx->sta->tx_stats.bytes[ac] += skb->len;
	पूर्ण
	अगर (ac >= 0)
		tx->sta->tx_stats.packets[ac]++;

	वापस TX_CONTINUE;
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_encrypt(काष्ठा ieee80211_tx_data *tx)
अणु
	अगर (!tx->key)
		वापस TX_CONTINUE;

	चयन (tx->key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		वापस ieee80211_crypto_wep_encrypt(tx);
	हाल WLAN_CIPHER_SUITE_TKIP:
		वापस ieee80211_crypto_tkip_encrypt(tx);
	हाल WLAN_CIPHER_SUITE_CCMP:
		वापस ieee80211_crypto_ccmp_encrypt(
			tx, IEEE80211_CCMP_MIC_LEN);
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		वापस ieee80211_crypto_ccmp_encrypt(
			tx, IEEE80211_CCMP_256_MIC_LEN);
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		वापस ieee80211_crypto_aes_cmac_encrypt(tx);
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		वापस ieee80211_crypto_aes_cmac_256_encrypt(tx);
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		वापस ieee80211_crypto_aes_gmac_encrypt(tx);
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		वापस ieee80211_crypto_gcmp_encrypt(tx);
	शेष:
		वापस ieee80211_crypto_hw_encrypt(tx);
	पूर्ण

	वापस TX_DROP;
पूर्ण

अटल ieee80211_tx_result debug_noअंतरभूत
ieee80211_tx_h_calculate_duration(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक next_len;
	bool group_addr;

	skb_queue_walk(&tx->skbs, skb) अणु
		hdr = (व्योम *) skb->data;
		अगर (unlikely(ieee80211_is_pspoll(hdr->frame_control)))
			अवरोध; /* must not overग_लिखो AID */
		अगर (!skb_queue_is_last(&tx->skbs, skb)) अणु
			काष्ठा sk_buff *next = skb_queue_next(&tx->skbs, skb);
			next_len = next->len;
		पूर्ण अन्यथा
			next_len = 0;
		group_addr = is_multicast_ether_addr(hdr->addr1);

		hdr->duration_id =
			ieee80211_duration(tx, skb, group_addr, next_len);
	पूर्ण

	वापस TX_CONTINUE;
पूर्ण

/* actual transmit path */

अटल bool ieee80211_tx_prep_agg(काष्ठा ieee80211_tx_data *tx,
				  काष्ठा sk_buff *skb,
				  काष्ठा ieee80211_tx_info *info,
				  काष्ठा tid_ampdu_tx *tid_tx,
				  पूर्णांक tid)
अणु
	bool queued = false;
	bool reset_agg_समयr = false;
	काष्ठा sk_buff *purge_skb = शून्य;

	अगर (test_bit(HT_AGG_STATE_OPERATIONAL, &tid_tx->state)) अणु
		info->flags |= IEEE80211_TX_CTL_AMPDU;
		reset_agg_समयr = true;
	पूर्ण अन्यथा अगर (test_bit(HT_AGG_STATE_WANT_START, &tid_tx->state)) अणु
		/*
		 * nothing -- this aggregation session is being started
		 * but that might still fail with the driver
		 */
	पूर्ण अन्यथा अगर (!tx->sta->sta.txq[tid]) अणु
		spin_lock(&tx->sta->lock);
		/*
		 * Need to re-check now, because we may get here
		 *
		 *  1) in the winकरोw during which the setup is actually
		 *     alपढ़ोy करोne, but not marked yet because not all
		 *     packets are spliced over to the driver pending
		 *     queue yet -- अगर this happened we acquire the lock
		 *     either beक्रमe or after the splice happens, but
		 *     need to recheck which of these हालs happened.
		 *
		 *  2) during session tearकरोwn, अगर the OPERATIONAL bit
		 *     was cleared due to the tearकरोwn but the poपूर्णांकer
		 *     hasn't been asचिन्हित शून्य yet (or we loaded it
		 *     beक्रमe it was asचिन्हित) -- in this हाल it may
		 *     now be शून्य which means we should just let the
		 *     packet pass through because splicing the frames
		 *     back is alपढ़ोy करोne.
		 */
		tid_tx = rcu_dereference_रक्षित_tid_tx(tx->sta, tid);

		अगर (!tid_tx) अणु
			/* करो nothing, let packet pass through */
		पूर्ण अन्यथा अगर (test_bit(HT_AGG_STATE_OPERATIONAL, &tid_tx->state)) अणु
			info->flags |= IEEE80211_TX_CTL_AMPDU;
			reset_agg_समयr = true;
		पूर्ण अन्यथा अणु
			queued = true;
			अगर (info->flags & IEEE80211_TX_CTL_NO_PS_BUFFER) अणु
				clear_sta_flag(tx->sta, WLAN_STA_SP);
				ps_dbg(tx->sta->sdata,
				       "STA %pM aid %d: SP frame queued, close the SP w/o telling the peer\n",
				       tx->sta->sta.addr, tx->sta->sta.aid);
			पूर्ण
			info->control.vअगर = &tx->sdata->vअगर;
			info->control.flags |= IEEE80211_TX_INTCFL_NEED_TXPROCESSING;
			info->flags &= ~IEEE80211_TX_TEMPORARY_FLAGS;
			__skb_queue_tail(&tid_tx->pending, skb);
			अगर (skb_queue_len(&tid_tx->pending) > STA_MAX_TX_BUFFER)
				purge_skb = __skb_dequeue(&tid_tx->pending);
		पूर्ण
		spin_unlock(&tx->sta->lock);

		अगर (purge_skb)
			ieee80211_मुक्त_txskb(&tx->local->hw, purge_skb);
	पूर्ण

	/* reset session समयr */
	अगर (reset_agg_समयr)
		tid_tx->last_tx = jअगरfies;

	वापस queued;
पूर्ण

/*
 * initialises @tx
 * pass %शून्य क्रम the station अगर unknown, a valid poपूर्णांकer अगर known
 * or an ERR_PTR() अगर the station is known not to exist
 */
अटल ieee80211_tx_result
ieee80211_tx_prepare(काष्ठा ieee80211_sub_अगर_data *sdata,
		     काष्ठा ieee80211_tx_data *tx,
		     काष्ठा sta_info *sta, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक tid;

	स_रखो(tx, 0, माप(*tx));
	tx->skb = skb;
	tx->local = local;
	tx->sdata = sdata;
	__skb_queue_head_init(&tx->skbs);

	/*
	 * If this flag is set to true anywhere, and we get here,
	 * we are करोing the needed processing, so हटाओ the flag
	 * now.
	 */
	info->control.flags &= ~IEEE80211_TX_INTCFL_NEED_TXPROCESSING;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	अगर (likely(sta)) अणु
		अगर (!IS_ERR(sta))
			tx->sta = sta;
	पूर्ण अन्यथा अणु
		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
			tx->sta = rcu_dereference(sdata->u.vlan.sta);
			अगर (!tx->sta && sdata->wdev.use_4addr)
				वापस TX_DROP;
		पूर्ण अन्यथा अगर (tx->sdata->control_port_protocol == tx->skb->protocol) अणु
			tx->sta = sta_info_get_bss(sdata, hdr->addr1);
		पूर्ण
		अगर (!tx->sta && !is_multicast_ether_addr(hdr->addr1))
			tx->sta = sta_info_get(sdata, hdr->addr1);
	पूर्ण

	अगर (tx->sta && ieee80211_is_data_qos(hdr->frame_control) &&
	    !ieee80211_is_qos_nullfunc(hdr->frame_control) &&
	    ieee80211_hw_check(&local->hw, AMPDU_AGGREGATION) &&
	    !ieee80211_hw_check(&local->hw, TX_AMPDU_SETUP_IN_HW)) अणु
		काष्ठा tid_ampdu_tx *tid_tx;

		tid = ieee80211_get_tid(hdr);

		tid_tx = rcu_dereference(tx->sta->ampdu_mlme.tid_tx[tid]);
		अगर (tid_tx) अणु
			bool queued;

			queued = ieee80211_tx_prep_agg(tx, skb, info,
						       tid_tx, tid);

			अगर (unlikely(queued))
				वापस TX_QUEUED;
		पूर्ण
	पूर्ण

	अगर (is_multicast_ether_addr(hdr->addr1)) अणु
		tx->flags &= ~IEEE80211_TX_UNICAST;
		info->flags |= IEEE80211_TX_CTL_NO_ACK;
	पूर्ण अन्यथा
		tx->flags |= IEEE80211_TX_UNICAST;

	अगर (!(info->flags & IEEE80211_TX_CTL_DONTFRAG)) अणु
		अगर (!(tx->flags & IEEE80211_TX_UNICAST) ||
		    skb->len + FCS_LEN <= local->hw.wiphy->frag_threshold ||
		    info->flags & IEEE80211_TX_CTL_AMPDU)
			info->flags |= IEEE80211_TX_CTL_DONTFRAG;
	पूर्ण

	अगर (!tx->sta)
		info->flags |= IEEE80211_TX_CTL_CLEAR_PS_FILT;
	अन्यथा अगर (test_and_clear_sta_flag(tx->sta, WLAN_STA_CLEAR_PS_FILT)) अणु
		info->flags |= IEEE80211_TX_CTL_CLEAR_PS_FILT;
		ieee80211_check_fast_xmit(tx->sta);
	पूर्ण

	info->flags |= IEEE80211_TX_CTL_FIRST_FRAGMENT;

	वापस TX_CONTINUE;
पूर्ण

अटल काष्ठा txq_info *ieee80211_get_txq(काष्ठा ieee80211_local *local,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा sta_info *sta,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_txq *txq = शून्य;

	अगर ((info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) ||
	    (info->control.flags & IEEE80211_TX_CTRL_PS_RESPONSE))
		वापस शून्य;

	अगर (!(info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP) &&
	    unlikely(!ieee80211_is_data_present(hdr->frame_control))) अणु
		अगर ((!ieee80211_is_mgmt(hdr->frame_control) ||
		     ieee80211_is_bufferable_mmpdu(hdr->frame_control) ||
		     vअगर->type == NL80211_IFTYPE_STATION) &&
		    sta && sta->uploaded) अणु
			/*
			 * This will be शून्य अगर the driver didn't set the
			 * opt-in hardware flag.
			 */
			txq = sta->sta.txq[IEEE80211_NUM_TIDS];
		पूर्ण
	पूर्ण अन्यथा अगर (sta) अणु
		u8 tid = skb->priority & IEEE80211_QOS_CTL_TID_MASK;

		अगर (!sta->uploaded)
			वापस शून्य;

		txq = sta->sta.txq[tid];
	पूर्ण अन्यथा अगर (vअगर) अणु
		txq = vअगर->txq;
	पूर्ण

	अगर (!txq)
		वापस शून्य;

	वापस to_txq_info(txq);
पूर्ण

अटल व्योम ieee80211_set_skb_enqueue_समय(काष्ठा sk_buff *skb)
अणु
	IEEE80211_SKB_CB(skb)->control.enqueue_समय = codel_get_समय();
पूर्ण

अटल u32 codel_skb_len_func(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->len;
पूर्ण

अटल codel_समय_प्रकार codel_skb_समय_func(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ieee80211_tx_info *info;

	info = (स्थिर काष्ठा ieee80211_tx_info *)skb->cb;
	वापस info->control.enqueue_समय;
पूर्ण

अटल काष्ठा sk_buff *codel_dequeue_func(काष्ठा codel_vars *cvars,
					  व्योम *ctx)
अणु
	काष्ठा ieee80211_local *local;
	काष्ठा txq_info *txqi;
	काष्ठा fq *fq;
	काष्ठा fq_flow *flow;

	txqi = ctx;
	local = vअगर_to_sdata(txqi->txq.vअगर)->local;
	fq = &local->fq;

	अगर (cvars == &txqi->def_cvars)
		flow = &txqi->tin.शेष_flow;
	अन्यथा
		flow = &fq->flows[cvars - local->cvars];

	वापस fq_flow_dequeue(fq, flow);
पूर्ण

अटल व्योम codel_drop_func(काष्ठा sk_buff *skb,
			    व्योम *ctx)
अणु
	काष्ठा ieee80211_local *local;
	काष्ठा ieee80211_hw *hw;
	काष्ठा txq_info *txqi;

	txqi = ctx;
	local = vअगर_to_sdata(txqi->txq.vअगर)->local;
	hw = &local->hw;

	ieee80211_मुक्त_txskb(hw, skb);
पूर्ण

अटल काष्ठा sk_buff *fq_tin_dequeue_func(काष्ठा fq *fq,
					   काष्ठा fq_tin *tin,
					   काष्ठा fq_flow *flow)
अणु
	काष्ठा ieee80211_local *local;
	काष्ठा txq_info *txqi;
	काष्ठा codel_vars *cvars;
	काष्ठा codel_params *cparams;
	काष्ठा codel_stats *cstats;

	local = container_of(fq, काष्ठा ieee80211_local, fq);
	txqi = container_of(tin, काष्ठा txq_info, tin);
	cstats = &txqi->cstats;

	अगर (txqi->txq.sta) अणु
		काष्ठा sta_info *sta = container_of(txqi->txq.sta,
						    काष्ठा sta_info, sta);
		cparams = &sta->cparams;
	पूर्ण अन्यथा अणु
		cparams = &local->cparams;
	पूर्ण

	अगर (flow == &tin->शेष_flow)
		cvars = &txqi->def_cvars;
	अन्यथा
		cvars = &local->cvars[flow - fq->flows];

	वापस codel_dequeue(txqi,
			     &flow->backlog,
			     cparams,
			     cvars,
			     cstats,
			     codel_skb_len_func,
			     codel_skb_समय_func,
			     codel_drop_func,
			     codel_dequeue_func);
पूर्ण

अटल व्योम fq_skb_मुक्त_func(काष्ठा fq *fq,
			     काष्ठा fq_tin *tin,
			     काष्ठा fq_flow *flow,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local;

	local = container_of(fq, काष्ठा ieee80211_local, fq);
	ieee80211_मुक्त_txskb(&local->hw, skb);
पूर्ण

अटल व्योम ieee80211_txq_enqueue(काष्ठा ieee80211_local *local,
				  काष्ठा txq_info *txqi,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा fq *fq = &local->fq;
	काष्ठा fq_tin *tin = &txqi->tin;
	u32 flow_idx = fq_flow_idx(fq, skb);

	ieee80211_set_skb_enqueue_समय(skb);

	spin_lock_bh(&fq->lock);
	/*
	 * For management frames, करोn't really apply codel etc.,
	 * we करोn't want to apply any shaping or anything we just
	 * want to simplअगरy the driver API by having them on the
	 * txqi.
	 */
	अगर (unlikely(txqi->txq.tid == IEEE80211_NUM_TIDS)) अणु
		IEEE80211_SKB_CB(skb)->control.flags |=
			IEEE80211_TX_INTCFL_NEED_TXPROCESSING;
		__skb_queue_tail(&txqi->frags, skb);
	पूर्ण अन्यथा अणु
		fq_tin_enqueue(fq, tin, flow_idx, skb,
			       fq_skb_मुक्त_func);
	पूर्ण
	spin_unlock_bh(&fq->lock);
पूर्ण

अटल bool fq_vlan_filter_func(काष्ठा fq *fq, काष्ठा fq_tin *tin,
				काष्ठा fq_flow *flow, काष्ठा sk_buff *skb,
				व्योम *data)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	वापस info->control.vअगर == data;
पूर्ण

व्योम ieee80211_txq_हटाओ_vlan(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा fq *fq = &local->fq;
	काष्ठा txq_info *txqi;
	काष्ठा fq_tin *tin;
	काष्ठा ieee80211_sub_अगर_data *ap;

	अगर (WARN_ON(sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN))
		वापस;

	ap = container_of(sdata->bss, काष्ठा ieee80211_sub_अगर_data, u.ap);

	अगर (!ap->vअगर.txq)
		वापस;

	txqi = to_txq_info(ap->vअगर.txq);
	tin = &txqi->tin;

	spin_lock_bh(&fq->lock);
	fq_tin_filter(fq, tin, fq_vlan_filter_func, &sdata->vअगर,
		      fq_skb_मुक्त_func);
	spin_unlock_bh(&fq->lock);
पूर्ण

व्योम ieee80211_txq_init(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sta_info *sta,
			काष्ठा txq_info *txqi, पूर्णांक tid)
अणु
	fq_tin_init(&txqi->tin);
	codel_vars_init(&txqi->def_cvars);
	codel_stats_init(&txqi->cstats);
	__skb_queue_head_init(&txqi->frags);
	INIT_LIST_HEAD(&txqi->schedule_order);

	txqi->txq.vअगर = &sdata->vअगर;

	अगर (!sta) अणु
		sdata->vअगर.txq = &txqi->txq;
		txqi->txq.tid = 0;
		txqi->txq.ac = IEEE80211_AC_BE;

		वापस;
	पूर्ण

	अगर (tid == IEEE80211_NUM_TIDS) अणु
		अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION) अणु
			/* Drivers need to opt in to the management MPDU TXQ */
			अगर (!ieee80211_hw_check(&sdata->local->hw,
						STA_MMPDU_TXQ))
				वापस;
		पूर्ण अन्यथा अगर (!ieee80211_hw_check(&sdata->local->hw,
					       BUFF_MMPDU_TXQ)) अणु
			/* Drivers need to opt in to the bufferable MMPDU TXQ */
			वापस;
		पूर्ण
		txqi->txq.ac = IEEE80211_AC_VO;
	पूर्ण अन्यथा अणु
		txqi->txq.ac = ieee80211_ac_from_tid(tid);
	पूर्ण

	txqi->txq.sta = &sta->sta;
	txqi->txq.tid = tid;
	sta->sta.txq[tid] = &txqi->txq;
पूर्ण

व्योम ieee80211_txq_purge(काष्ठा ieee80211_local *local,
			 काष्ठा txq_info *txqi)
अणु
	काष्ठा fq *fq = &local->fq;
	काष्ठा fq_tin *tin = &txqi->tin;

	spin_lock_bh(&fq->lock);
	fq_tin_reset(fq, tin, fq_skb_मुक्त_func);
	ieee80211_purge_tx_queue(&local->hw, &txqi->frags);
	spin_unlock_bh(&fq->lock);

	spin_lock_bh(&local->active_txq_lock[txqi->txq.ac]);
	list_del_init(&txqi->schedule_order);
	spin_unlock_bh(&local->active_txq_lock[txqi->txq.ac]);
पूर्ण

व्योम ieee80211_txq_set_params(काष्ठा ieee80211_local *local)
अणु
	अगर (local->hw.wiphy->txq_limit)
		local->fq.limit = local->hw.wiphy->txq_limit;
	अन्यथा
		local->hw.wiphy->txq_limit = local->fq.limit;

	अगर (local->hw.wiphy->txq_memory_limit)
		local->fq.memory_limit = local->hw.wiphy->txq_memory_limit;
	अन्यथा
		local->hw.wiphy->txq_memory_limit = local->fq.memory_limit;

	अगर (local->hw.wiphy->txq_quantum)
		local->fq.quantum = local->hw.wiphy->txq_quantum;
	अन्यथा
		local->hw.wiphy->txq_quantum = local->fq.quantum;
पूर्ण

पूर्णांक ieee80211_txq_setup_flows(काष्ठा ieee80211_local *local)
अणु
	काष्ठा fq *fq = &local->fq;
	पूर्णांक ret;
	पूर्णांक i;
	bool supp_vht = false;
	क्रमागत nl80211_band band;

	अगर (!local->ops->wake_tx_queue)
		वापस 0;

	ret = fq_init(fq, 4096);
	अगर (ret)
		वापस ret;

	/*
	 * If the hardware करोesn't support VHT, it is safe to limit the maximum
	 * queue size. 4 Mbytes is 64 max-size aggregates in 802.11n.
	 */
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		काष्ठा ieee80211_supported_band *sband;

		sband = local->hw.wiphy->bands[band];
		अगर (!sband)
			जारी;

		supp_vht = supp_vht || sband->vht_cap.vht_supported;
	पूर्ण

	अगर (!supp_vht)
		fq->memory_limit = 4 << 20; /* 4 Mbytes */

	codel_params_init(&local->cparams);
	local->cparams.पूर्णांकerval = MS2TIME(100);
	local->cparams.target = MS2TIME(20);
	local->cparams.ecn = true;

	local->cvars = kसुस्मृति(fq->flows_cnt, माप(local->cvars[0]),
			       GFP_KERNEL);
	अगर (!local->cvars) अणु
		spin_lock_bh(&fq->lock);
		fq_reset(fq, fq_skb_मुक्त_func);
		spin_unlock_bh(&fq->lock);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < fq->flows_cnt; i++)
		codel_vars_init(&local->cvars[i]);

	ieee80211_txq_set_params(local);

	वापस 0;
पूर्ण

व्योम ieee80211_txq_tearकरोwn_flows(काष्ठा ieee80211_local *local)
अणु
	काष्ठा fq *fq = &local->fq;

	अगर (!local->ops->wake_tx_queue)
		वापस;

	kमुक्त(local->cvars);
	local->cvars = शून्य;

	spin_lock_bh(&fq->lock);
	fq_reset(fq, fq_skb_मुक्त_func);
	spin_unlock_bh(&fq->lock);
पूर्ण

अटल bool ieee80211_queue_skb(काष्ठा ieee80211_local *local,
				काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा sta_info *sta,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा txq_info *txqi;

	अगर (!local->ops->wake_tx_queue ||
	    sdata->vअगर.type == NL80211_IFTYPE_MONITOR)
		वापस false;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		sdata = container_of(sdata->bss,
				     काष्ठा ieee80211_sub_अगर_data, u.ap);

	vअगर = &sdata->vअगर;
	txqi = ieee80211_get_txq(local, vअगर, sta, skb);

	अगर (!txqi)
		वापस false;

	ieee80211_txq_enqueue(local, txqi, skb);

	schedule_and_wake_txq(local, txqi);

	वापस true;
पूर्ण

अटल bool ieee80211_tx_frags(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा sta_info *sta,
			       काष्ठा sk_buff_head *skbs,
			       bool txpending)
अणु
	काष्ठा ieee80211_tx_control control = अणुपूर्ण;
	काष्ठा sk_buff *skb, *पंचांगp;
	अचिन्हित दीर्घ flags;

	skb_queue_walk_safe(skbs, skb, पंचांगp) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		पूर्णांक q = info->hw_queue;

#अगर_घोषित CONFIG_MAC80211_VERBOSE_DEBUG
		अगर (WARN_ON_ONCE(q >= local->hw.queues)) अणु
			__skb_unlink(skb, skbs);
			ieee80211_मुक्त_txskb(&local->hw, skb);
			जारी;
		पूर्ण
#पूर्ण_अगर

		spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
		अगर (local->queue_stop_reasons[q] ||
		    (!txpending && !skb_queue_empty(&local->pending[q]))) अणु
			अगर (unlikely(info->flags &
				     IEEE80211_TX_INTFL_OFFCHAN_TX_OK)) अणु
				अगर (local->queue_stop_reasons[q] &
				    ~BIT(IEEE80211_QUEUE_STOP_REASON_OFFCHANNEL)) अणु
					/*
					 * Drop off-channel frames अगर queues
					 * are stopped क्रम any reason other
					 * than off-channel operation. Never
					 * queue them.
					 */
					spin_unlock_irqrestore(
						&local->queue_stop_reason_lock,
						flags);
					ieee80211_purge_tx_queue(&local->hw,
								 skbs);
					वापस true;
				पूर्ण
			पूर्ण अन्यथा अणु

				/*
				 * Since queue is stopped, queue up frames क्रम
				 * later transmission from the tx-pending
				 * tasklet when the queue is woken again.
				 */
				अगर (txpending)
					skb_queue_splice_init(skbs,
							      &local->pending[q]);
				अन्यथा
					skb_queue_splice_tail_init(skbs,
								   &local->pending[q]);

				spin_unlock_irqrestore(&local->queue_stop_reason_lock,
						       flags);
				वापस false;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);

		info->control.vअगर = vअगर;
		control.sta = sta ? &sta->sta : शून्य;

		__skb_unlink(skb, skbs);
		drv_tx(local, &control, skb);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Returns false अगर the frame couldn't be transmitted but was queued instead.
 */
अटल bool __ieee80211_tx(काष्ठा ieee80211_local *local,
			   काष्ठा sk_buff_head *skbs, पूर्णांक led_len,
			   काष्ठा sta_info *sta, bool txpending)
अणु
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा sk_buff *skb;
	bool result;
	__le16 fc;

	अगर (WARN_ON(skb_queue_empty(skbs)))
		वापस true;

	skb = skb_peek(skbs);
	fc = ((काष्ठा ieee80211_hdr *)skb->data)->frame_control;
	info = IEEE80211_SKB_CB(skb);
	sdata = vअगर_to_sdata(info->control.vअगर);
	अगर (sta && !sta->uploaded)
		sta = शून्य;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_MONITOR:
		अगर (sdata->u.mntr.flags & MONITOR_FLAG_ACTIVE) अणु
			vअगर = &sdata->vअगर;
			अवरोध;
		पूर्ण
		sdata = rcu_dereference(local->monitor_sdata);
		अगर (sdata) अणु
			vअगर = &sdata->vअगर;
			info->hw_queue =
				vअगर->hw_queue[skb_get_queue_mapping(skb)];
		पूर्ण अन्यथा अगर (ieee80211_hw_check(&local->hw, QUEUE_CONTROL)) अणु
			ieee80211_purge_tx_queue(&local->hw, skbs);
			वापस true;
		पूर्ण अन्यथा
			vअगर = शून्य;
		अवरोध;
	हाल NL80211_IFTYPE_AP_VLAN:
		sdata = container_of(sdata->bss,
				     काष्ठा ieee80211_sub_अगर_data, u.ap);
		fallthrough;
	शेष:
		vअगर = &sdata->vअगर;
		अवरोध;
	पूर्ण

	result = ieee80211_tx_frags(local, vअगर, sta, skbs, txpending);

	ieee80211_tpt_led_trig_tx(local, fc, led_len);

	WARN_ON_ONCE(!skb_queue_empty(skbs));

	वापस result;
पूर्ण

/*
 * Invoke TX handlers, वापस 0 on success and non-zero अगर the
 * frame was dropped or queued.
 *
 * The handlers are split पूर्णांकo an early and late part. The latter is everything
 * that can be sensitive to reordering, and will be deferred to after packets
 * are dequeued from the पूर्णांकermediate queues (when they are enabled).
 */
अटल पूर्णांक invoke_tx_handlers_early(काष्ठा ieee80211_tx_data *tx)
अणु
	ieee80211_tx_result res = TX_DROP;

#घोषणा CALL_TXH(txh) \
	करो अणु				\
		res = txh(tx);		\
		अगर (res != TX_CONTINUE)	\
			जाओ txh_करोne;	\
	पूर्ण जबतक (0)

	CALL_TXH(ieee80211_tx_h_dynamic_ps);
	CALL_TXH(ieee80211_tx_h_check_assoc);
	CALL_TXH(ieee80211_tx_h_ps_buf);
	CALL_TXH(ieee80211_tx_h_check_control_port_protocol);
	CALL_TXH(ieee80211_tx_h_select_key);
	अगर (!ieee80211_hw_check(&tx->local->hw, HAS_RATE_CONTROL))
		CALL_TXH(ieee80211_tx_h_rate_ctrl);

 txh_करोne:
	अगर (unlikely(res == TX_DROP)) अणु
		I802_DEBUG_INC(tx->local->tx_handlers_drop);
		अगर (tx->skb)
			ieee80211_मुक्त_txskb(&tx->local->hw, tx->skb);
		अन्यथा
			ieee80211_purge_tx_queue(&tx->local->hw, &tx->skbs);
		वापस -1;
	पूर्ण अन्यथा अगर (unlikely(res == TX_QUEUED)) अणु
		I802_DEBUG_INC(tx->local->tx_handlers_queued);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Late handlers can be called जबतक the sta lock is held. Handlers that can
 * cause packets to be generated will cause deadlock!
 */
अटल पूर्णांक invoke_tx_handlers_late(काष्ठा ieee80211_tx_data *tx)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	ieee80211_tx_result res = TX_CONTINUE;

	अगर (unlikely(info->flags & IEEE80211_TX_INTFL_RETRANSMISSION)) अणु
		__skb_queue_tail(&tx->skbs, tx->skb);
		tx->skb = शून्य;
		जाओ txh_करोne;
	पूर्ण

	CALL_TXH(ieee80211_tx_h_michael_mic_add);
	CALL_TXH(ieee80211_tx_h_sequence);
	CALL_TXH(ieee80211_tx_h_fragment);
	/* handlers after fragment must be aware of tx info fragmentation! */
	CALL_TXH(ieee80211_tx_h_stats);
	CALL_TXH(ieee80211_tx_h_encrypt);
	अगर (!ieee80211_hw_check(&tx->local->hw, HAS_RATE_CONTROL))
		CALL_TXH(ieee80211_tx_h_calculate_duration);
#अघोषित CALL_TXH

 txh_करोne:
	अगर (unlikely(res == TX_DROP)) अणु
		I802_DEBUG_INC(tx->local->tx_handlers_drop);
		अगर (tx->skb)
			ieee80211_मुक्त_txskb(&tx->local->hw, tx->skb);
		अन्यथा
			ieee80211_purge_tx_queue(&tx->local->hw, &tx->skbs);
		वापस -1;
	पूर्ण अन्यथा अगर (unlikely(res == TX_QUEUED)) अणु
		I802_DEBUG_INC(tx->local->tx_handlers_queued);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक invoke_tx_handlers(काष्ठा ieee80211_tx_data *tx)
अणु
	पूर्णांक r = invoke_tx_handlers_early(tx);

	अगर (r)
		वापस r;
	वापस invoke_tx_handlers_late(tx);
पूर्ण

bool ieee80211_tx_prepare_skb(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर, काष्ठा sk_buff *skb,
			      पूर्णांक band, काष्ठा ieee80211_sta **sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_data tx;
	काष्ठा sk_buff *skb2;

	अगर (ieee80211_tx_prepare(sdata, &tx, शून्य, skb) == TX_DROP)
		वापस false;

	info->band = band;
	info->control.vअगर = vअगर;
	info->hw_queue = vअगर->hw_queue[skb_get_queue_mapping(skb)];

	अगर (invoke_tx_handlers(&tx))
		वापस false;

	अगर (sta) अणु
		अगर (tx.sta)
			*sta = &tx.sta->sta;
		अन्यथा
			*sta = शून्य;
	पूर्ण

	/* this function isn't suitable क्रम fragmented data frames */
	skb2 = __skb_dequeue(&tx.skbs);
	अगर (WARN_ON(skb2 != skb || !skb_queue_empty(&tx.skbs))) अणु
		ieee80211_मुक्त_txskb(hw, skb2);
		ieee80211_purge_tx_queue(hw, &tx.skbs);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(ieee80211_tx_prepare_skb);

/*
 * Returns false अगर the frame couldn't be transmitted but was queued instead.
 */
अटल bool ieee80211_tx(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा sta_info *sta, काष्ठा sk_buff *skb,
			 bool txpending)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_tx_data tx;
	ieee80211_tx_result res_prepare;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	bool result = true;
	पूर्णांक led_len;

	अगर (unlikely(skb->len < 10)) अणु
		dev_kमुक्त_skb(skb);
		वापस true;
	पूर्ण

	/* initialises tx */
	led_len = skb->len;
	res_prepare = ieee80211_tx_prepare(sdata, &tx, sta, skb);

	अगर (unlikely(res_prepare == TX_DROP)) अणु
		ieee80211_मुक्त_txskb(&local->hw, skb);
		वापस true;
	पूर्ण अन्यथा अगर (unlikely(res_prepare == TX_QUEUED)) अणु
		वापस true;
	पूर्ण

	/* set up hw_queue value early */
	अगर (!(info->flags & IEEE80211_TX_CTL_TX_OFFCHAN) ||
	    !ieee80211_hw_check(&local->hw, QUEUE_CONTROL))
		info->hw_queue =
			sdata->vअगर.hw_queue[skb_get_queue_mapping(skb)];

	अगर (invoke_tx_handlers_early(&tx))
		वापस true;

	अगर (ieee80211_queue_skb(local, sdata, tx.sta, tx.skb))
		वापस true;

	अगर (!invoke_tx_handlers_late(&tx))
		result = __ieee80211_tx(local, &tx.skbs, led_len,
					tx.sta, txpending);

	वापस result;
पूर्ण

/* device xmit handlers */

क्रमागत ieee80211_encrypt अणु
	ENCRYPT_NO,
	ENCRYPT_MGMT,
	ENCRYPT_DATA,
पूर्ण;

अटल पूर्णांक ieee80211_skb_resize(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा sk_buff *skb,
				पूर्णांक head_need,
				क्रमागत ieee80211_encrypt encrypt)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	bool enc_tailroom;
	पूर्णांक tail_need = 0;

	enc_tailroom = encrypt == ENCRYPT_MGMT ||
		       (encrypt == ENCRYPT_DATA &&
			sdata->crypto_tx_tailroom_needed_cnt);

	अगर (enc_tailroom) अणु
		tail_need = IEEE80211_ENCRYPT_TAILROOM;
		tail_need -= skb_tailroom(skb);
		tail_need = max_t(पूर्णांक, tail_need, 0);
	पूर्ण

	अगर (skb_cloned(skb) &&
	    (!ieee80211_hw_check(&local->hw, SUPPORTS_CLONED_SKBS) ||
	     !skb_clone_writable(skb, ETH_HLEN) || enc_tailroom))
		I802_DEBUG_INC(local->tx_expand_skb_head_cloned);
	अन्यथा अगर (head_need || tail_need)
		I802_DEBUG_INC(local->tx_expand_skb_head);
	अन्यथा
		वापस 0;

	अगर (pskb_expand_head(skb, head_need, tail_need, GFP_ATOMIC)) अणु
		wiphy_debug(local->hw.wiphy,
			    "failed to reallocate TX buffer\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ieee80211_xmit(काष्ठा ieee80211_sub_अगर_data *sdata,
		    काष्ठा sta_info *sta, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	पूर्णांक headroom;
	क्रमागत ieee80211_encrypt encrypt;

	अगर (info->flags & IEEE80211_TX_INTFL_DONT_ENCRYPT)
		encrypt = ENCRYPT_NO;
	अन्यथा अगर (ieee80211_is_mgmt(hdr->frame_control))
		encrypt = ENCRYPT_MGMT;
	अन्यथा
		encrypt = ENCRYPT_DATA;

	headroom = local->tx_headroom;
	अगर (encrypt != ENCRYPT_NO)
		headroom += sdata->encrypt_headroom;
	headroom -= skb_headroom(skb);
	headroom = max_t(पूर्णांक, 0, headroom);

	अगर (ieee80211_skb_resize(sdata, skb, headroom, encrypt)) अणु
		ieee80211_मुक्त_txskb(&local->hw, skb);
		वापस;
	पूर्ण

	/* reload after potential resize */
	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	info->control.vअगर = &sdata->vअगर;

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		अगर (ieee80211_is_data(hdr->frame_control) &&
		    is_unicast_ether_addr(hdr->addr1)) अणु
			अगर (mesh_nexthop_resolve(sdata, skb))
				वापस; /* skb queued: करोn't मुक्त */
		पूर्ण अन्यथा अणु
			ieee80211_mps_set_frame_flags(sdata, शून्य, hdr);
		पूर्ण
	पूर्ण

	ieee80211_set_qos_hdr(sdata, skb);
	ieee80211_tx(sdata, sta, skb, false);
पूर्ण

अटल bool ieee80211_validate_radiotap_len(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_radiotap_header *rthdr =
		(काष्ठा ieee80211_radiotap_header *)skb->data;

	/* check क्रम not even having the fixed radiotap header part */
	अगर (unlikely(skb->len < माप(काष्ठा ieee80211_radiotap_header)))
		वापस false; /* too लघु to be possibly valid */

	/* is it a header version we can trust to find length from? */
	अगर (unlikely(rthdr->it_version))
		वापस false; /* only version 0 is supported */

	/* करोes the skb contain enough to deliver on the alleged length? */
	अगर (unlikely(skb->len < ieee80211_get_radiotap_len(skb->data)))
		वापस false; /* skb too लघु क्रम claimed rt header extent */

	वापस true;
पूर्ण

bool ieee80211_parse_tx_radiotap(काष्ठा sk_buff *skb,
				 काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_local *local = wdev_priv(dev->ieee80211_ptr);
	काष्ठा ieee80211_radiotap_iterator iterator;
	काष्ठा ieee80211_radiotap_header *rthdr =
		(काष्ठा ieee80211_radiotap_header *) skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक ret = ieee80211_radiotap_iterator_init(&iterator, rthdr, skb->len,
						   शून्य);
	u16 txflags;
	u16 rate = 0;
	bool rate_found = false;
	u8 rate_retries = 0;
	u16 rate_flags = 0;
	u8 mcs_known, mcs_flags, mcs_bw;
	u16 vht_known;
	u8 vht_mcs = 0, vht_nss = 0;
	पूर्णांक i;

	अगर (!ieee80211_validate_radiotap_len(skb))
		वापस false;

	info->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT |
		       IEEE80211_TX_CTL_DONTFRAG;

	/*
	 * क्रम every radiotap entry that is present
	 * (ieee80211_radiotap_iterator_next वापसs -ENOENT when no more
	 * entries present, or -EINVAL on error)
	 */

	जबतक (!ret) अणु
		ret = ieee80211_radiotap_iterator_next(&iterator);

		अगर (ret)
			जारी;

		/* see अगर this argument is something we can use */
		चयन (iterator.this_arg_index) अणु
		/*
		 * You must take care when dereferencing iterator.this_arg
		 * क्रम multibyte types... the poपूर्णांकer is not aligned.  Use
		 * get_unaligned((type *)iterator.this_arg) to dereference
		 * iterator.this_arg क्रम type "type" safely on all arches.
		*/
		हाल IEEE80211_RADIOTAP_FLAGS:
			अगर (*iterator.this_arg & IEEE80211_RADIOTAP_F_FCS) अणु
				/*
				 * this indicates that the skb we have been
				 * handed has the 32-bit FCS CRC at the end...
				 * we should react to that by snipping it off
				 * because it will be recomputed and added
				 * on transmission
				 */
				अगर (skb->len < (iterator._max_length + FCS_LEN))
					वापस false;

				skb_trim(skb, skb->len - FCS_LEN);
			पूर्ण
			अगर (*iterator.this_arg & IEEE80211_RADIOTAP_F_WEP)
				info->flags &= ~IEEE80211_TX_INTFL_DONT_ENCRYPT;
			अगर (*iterator.this_arg & IEEE80211_RADIOTAP_F_FRAG)
				info->flags &= ~IEEE80211_TX_CTL_DONTFRAG;
			अवरोध;

		हाल IEEE80211_RADIOTAP_TX_FLAGS:
			txflags = get_unaligned_le16(iterator.this_arg);
			अगर (txflags & IEEE80211_RADIOTAP_F_TX_NOACK)
				info->flags |= IEEE80211_TX_CTL_NO_ACK;
			अगर (txflags & IEEE80211_RADIOTAP_F_TX_NOSEQNO)
				info->control.flags |= IEEE80211_TX_CTRL_NO_SEQNO;
			अगर (txflags & IEEE80211_RADIOTAP_F_TX_ORDER)
				info->control.flags |=
					IEEE80211_TX_CTRL_DONT_REORDER;
			अवरोध;

		हाल IEEE80211_RADIOTAP_RATE:
			rate = *iterator.this_arg;
			rate_flags = 0;
			rate_found = true;
			अवरोध;

		हाल IEEE80211_RADIOTAP_DATA_RETRIES:
			rate_retries = *iterator.this_arg;
			अवरोध;

		हाल IEEE80211_RADIOTAP_MCS:
			mcs_known = iterator.this_arg[0];
			mcs_flags = iterator.this_arg[1];
			अगर (!(mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_MCS))
				अवरोध;

			rate_found = true;
			rate = iterator.this_arg[2];
			rate_flags = IEEE80211_TX_RC_MCS;

			अगर (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_GI &&
			    mcs_flags & IEEE80211_RADIOTAP_MCS_SGI)
				rate_flags |= IEEE80211_TX_RC_SHORT_GI;

			mcs_bw = mcs_flags & IEEE80211_RADIOTAP_MCS_BW_MASK;
			अगर (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_BW &&
			    mcs_bw == IEEE80211_RADIOTAP_MCS_BW_40)
				rate_flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;

			अगर (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_FEC &&
			    mcs_flags & IEEE80211_RADIOTAP_MCS_FEC_LDPC)
				info->flags |= IEEE80211_TX_CTL_LDPC;

			अगर (mcs_known & IEEE80211_RADIOTAP_MCS_HAVE_STBC) अणु
				u8 stbc = u8_get_bits(mcs_flags,
						      IEEE80211_RADIOTAP_MCS_STBC_MASK);

				info->flags |=
					u32_encode_bits(stbc,
							IEEE80211_TX_CTL_STBC);
			पूर्ण
			अवरोध;

		हाल IEEE80211_RADIOTAP_VHT:
			vht_known = get_unaligned_le16(iterator.this_arg);
			rate_found = true;

			rate_flags = IEEE80211_TX_RC_VHT_MCS;
			अगर ((vht_known & IEEE80211_RADIOTAP_VHT_KNOWN_GI) &&
			    (iterator.this_arg[2] &
			     IEEE80211_RADIOTAP_VHT_FLAG_SGI))
				rate_flags |= IEEE80211_TX_RC_SHORT_GI;
			अगर (vht_known &
			    IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH) अणु
				अगर (iterator.this_arg[3] == 1)
					rate_flags |=
						IEEE80211_TX_RC_40_MHZ_WIDTH;
				अन्यथा अगर (iterator.this_arg[3] == 4)
					rate_flags |=
						IEEE80211_TX_RC_80_MHZ_WIDTH;
				अन्यथा अगर (iterator.this_arg[3] == 11)
					rate_flags |=
						IEEE80211_TX_RC_160_MHZ_WIDTH;
			पूर्ण

			vht_mcs = iterator.this_arg[4] >> 4;
			vht_nss = iterator.this_arg[4] & 0xF;
			अवरोध;

		/*
		 * Please update the file
		 * Documentation/networking/mac80211-injection.rst
		 * when parsing new fields here.
		 */

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret != -ENOENT) /* ie, अगर we didn't simply run out of fields */
		वापस false;

	अगर (rate_found) अणु
		काष्ठा ieee80211_supported_band *sband =
			local->hw.wiphy->bands[info->band];

		info->control.flags |= IEEE80211_TX_CTRL_RATE_INJECT;

		क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++) अणु
			info->control.rates[i].idx = -1;
			info->control.rates[i].flags = 0;
			info->control.rates[i].count = 0;
		पूर्ण

		अगर (rate_flags & IEEE80211_TX_RC_MCS) अणु
			info->control.rates[0].idx = rate;
		पूर्ण अन्यथा अगर (rate_flags & IEEE80211_TX_RC_VHT_MCS) अणु
			ieee80211_rate_set_vht(info->control.rates, vht_mcs,
					       vht_nss);
		पूर्ण अन्यथा अगर (sband) अणु
			क्रम (i = 0; i < sband->n_bitrates; i++) अणु
				अगर (rate * 5 != sband->bitrates[i].bitrate)
					जारी;

				info->control.rates[0].idx = i;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (info->control.rates[0].idx < 0)
			info->control.flags &= ~IEEE80211_TX_CTRL_RATE_INJECT;

		info->control.rates[0].flags = rate_flags;
		info->control.rates[0].count = min_t(u8, rate_retries + 1,
						     local->hw.max_rate_tries);
	पूर्ण

	वापस true;
पूर्ण

netdev_tx_t ieee80211_monitor_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_local *local = wdev_priv(dev->ieee80211_ptr);
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_sub_अगर_data *पंचांगp_sdata, *sdata;
	काष्ठा cfg80211_chan_def *chandef;
	u16 len_rthdr;
	पूर्णांक hdrlen;

	स_रखो(info, 0, माप(*info));
	info->flags = IEEE80211_TX_CTL_REQ_TX_STATUS |
		      IEEE80211_TX_CTL_INJECTED;

	/* Sanity-check the length of the radiotap header */
	अगर (!ieee80211_validate_radiotap_len(skb))
		जाओ fail;

	/* we now know there is a radiotap header with a length we can use */
	len_rthdr = ieee80211_get_radiotap_len(skb->data);

	/*
	 * fix up the poपूर्णांकers accounting क्रम the radiotap
	 * header still being in there.  We are being given
	 * a precooked IEEE80211 header so no need क्रम
	 * normal processing
	 */
	skb_set_mac_header(skb, len_rthdr);
	/*
	 * these are just fixed to the end of the rt area since we
	 * करोn't have any better inक्रमmation and at this poपूर्णांक, nobody cares
	 */
	skb_set_network_header(skb, len_rthdr);
	skb_set_transport_header(skb, len_rthdr);

	अगर (skb->len < len_rthdr + 2)
		जाओ fail;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + len_rthdr);
	hdrlen = ieee80211_hdrlen(hdr->frame_control);

	अगर (skb->len < len_rthdr + hdrlen)
		जाओ fail;

	/*
	 * Initialize skb->protocol अगर the injected frame is a data frame
	 * carrying a rfc1042 header
	 */
	अगर (ieee80211_is_data(hdr->frame_control) &&
	    skb->len >= len_rthdr + hdrlen + माप(rfc1042_header) + 2) अणु
		u8 *payload = (u8 *)hdr + hdrlen;

		अगर (ether_addr_equal(payload, rfc1042_header))
			skb->protocol = cpu_to_be16((payload[6] << 8) |
						    payload[7]);
	पूर्ण

	rcu_पढ़ो_lock();

	/*
	 * We process outgoing injected frames that have a local address
	 * we handle as though they are non-injected frames.
	 * This code here isn't entirely correct, the local MAC address
	 * isn't always enough to find the पूर्णांकerface to use; क्रम proper
	 * VLAN support we have an nl80211-based mechanism.
	 *
	 * This is necessary, क्रम example, क्रम old hostapd versions that
	 * करोn't use nl80211-based management TX/RX.
	 */
	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	list_क्रम_each_entry_rcu(पंचांगp_sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(पंचांगp_sdata))
			जारी;
		अगर (पंचांगp_sdata->vअगर.type == NL80211_IFTYPE_MONITOR ||
		    पंचांगp_sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
			जारी;
		अगर (ether_addr_equal(पंचांगp_sdata->vअगर.addr, hdr->addr2)) अणु
			sdata = पंचांगp_sdata;
			अवरोध;
		पूर्ण
	पूर्ण

	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (!chanctx_conf) अणु
		पंचांगp_sdata = rcu_dereference(local->monitor_sdata);
		अगर (पंचांगp_sdata)
			chanctx_conf =
				rcu_dereference(पंचांगp_sdata->vअगर.chanctx_conf);
	पूर्ण

	अगर (chanctx_conf)
		chandef = &chanctx_conf->def;
	अन्यथा अगर (!local->use_chanctx)
		chandef = &local->_oper_chandef;
	अन्यथा
		जाओ fail_rcu;

	/*
	 * Frame injection is not allowed अगर beaconing is not allowed
	 * or अगर we need radar detection. Beaconing is usually not allowed when
	 * the mode or operation (Adhoc, AP, Mesh) करोes not support DFS.
	 * Passive scan is also used in world regulatory करोमुख्यs where
	 * your country is not known and as such it should be treated as
	 * NO TX unless the channel is explicitly allowed in which हाल
	 * your current regulatory करोमुख्य would not have the passive scan
	 * flag.
	 *
	 * Since AP mode uses monitor पूर्णांकerfaces to inject/TX management
	 * frames we can make AP mode the exception to this rule once it
	 * supports radar detection as its implementation can deal with
	 * radar detection by itself. We can करो that later by adding a
	 * monitor flag पूर्णांकerfaces used क्रम AP support.
	 */
	अगर (!cfg80211_reg_can_beacon(local->hw.wiphy, chandef,
				     sdata->vअगर.type))
		जाओ fail_rcu;

	info->band = chandef->chan->band;

	/* Initialize skb->priority according to frame type and TID class,
	 * with respect to the sub पूर्णांकerface that the frame will actually
	 * be transmitted on. If the DONT_REORDER flag is set, the original
	 * skb-priority is preserved to assure frames injected with this
	 * flag are not reordered relative to each other.
	 */
	ieee80211_select_queue_80211(sdata, skb, hdr);
	skb_set_queue_mapping(skb, ieee80211_ac_from_tid(skb->priority));

	/*
	 * Process the radiotap header. This will now take पूर्णांकo account the
	 * selected chandef above to accurately set injection rates and
	 * retransmissions.
	 */
	अगर (!ieee80211_parse_tx_radiotap(skb, dev))
		जाओ fail_rcu;

	/* हटाओ the injection radiotap header */
	skb_pull(skb, len_rthdr);

	ieee80211_xmit(sdata, शून्य, skb);
	rcu_पढ़ो_unlock();

	वापस NETDEV_TX_OK;

fail_rcu:
	rcu_पढ़ो_unlock();
fail:
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK; /* meaning, we dealt with the skb */
पूर्ण

अटल अंतरभूत bool ieee80211_is_tdls_setup(काष्ठा sk_buff *skb)
अणु
	u16 ethertype = (skb->data[12] << 8) | skb->data[13];

	वापस ethertype == ETH_P_TDLS &&
	       skb->len > 14 &&
	       skb->data[14] == WLAN_TDLS_SNAP_RFTYPE;
पूर्ण

पूर्णांक ieee80211_lookup_ra_sta(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा sk_buff *skb,
			    काष्ठा sta_info **sta_out)
अणु
	काष्ठा sta_info *sta;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP_VLAN:
		sta = rcu_dereference(sdata->u.vlan.sta);
		अगर (sta) अणु
			*sta_out = sta;
			वापस 0;
		पूर्ण अन्यथा अगर (sdata->wdev.use_4addr) अणु
			वापस -ENOLINK;
		पूर्ण
		fallthrough;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_OCB:
	हाल NL80211_IFTYPE_ADHOC:
		अगर (is_multicast_ether_addr(skb->data)) अणु
			*sta_out = ERR_PTR(-ENOENT);
			वापस 0;
		पूर्ण
		sta = sta_info_get_bss(sdata, skb->data);
		अवरोध;
#अगर_घोषित CONFIG_MAC80211_MESH
	हाल NL80211_IFTYPE_MESH_POINT:
		/* determined much later */
		*sta_out = शून्य;
		वापस 0;
#पूर्ण_अगर
	हाल NL80211_IFTYPE_STATION:
		अगर (sdata->wdev.wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS) अणु
			sta = sta_info_get(sdata, skb->data);
			अगर (sta && test_sta_flag(sta, WLAN_STA_TDLS_PEER)) अणु
				अगर (test_sta_flag(sta,
						  WLAN_STA_TDLS_PEER_AUTH)) अणु
					*sta_out = sta;
					वापस 0;
				पूर्ण

				/*
				 * TDLS link during setup - throw out frames to
				 * peer. Allow TDLS-setup frames to unauthorized
				 * peers क्रम the special हाल of a link tearकरोwn
				 * after a TDLS sta is हटाओd due to being
				 * unreachable.
				 */
				अगर (!ieee80211_is_tdls_setup(skb))
					वापस -EINVAL;
			पूर्ण

		पूर्ण

		sta = sta_info_get(sdata, sdata->u.mgd.bssid);
		अगर (!sta)
			वापस -ENOLINK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*sta_out = sta ?: ERR_PTR(-ENOENT);
	वापस 0;
पूर्ण

अटल u16 ieee80211_store_ack_skb(काष्ठा ieee80211_local *local,
				   काष्ठा sk_buff *skb,
				   u32 *info_flags,
				   u64 *cookie)
अणु
	काष्ठा sk_buff *ack_skb;
	u16 info_id = 0;

	अगर (skb->sk)
		ack_skb = skb_clone_sk(skb);
	अन्यथा
		ack_skb = skb_clone(skb, GFP_ATOMIC);

	अगर (ack_skb) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक id;

		spin_lock_irqsave(&local->ack_status_lock, flags);
		id = idr_alloc(&local->ack_status_frames, ack_skb,
			       1, 0x2000, GFP_ATOMIC);
		spin_unlock_irqrestore(&local->ack_status_lock, flags);

		अगर (id >= 0) अणु
			info_id = id;
			*info_flags |= IEEE80211_TX_CTL_REQ_TX_STATUS;
			अगर (cookie) अणु
				*cookie = ieee80211_mgmt_tx_cookie(local);
				IEEE80211_SKB_CB(ack_skb)->ack.cookie = *cookie;
			पूर्ण
		पूर्ण अन्यथा अणु
			kमुक्त_skb(ack_skb);
		पूर्ण
	पूर्ण

	वापस info_id;
पूर्ण

/**
 * ieee80211_build_hdr - build 802.11 header in the given frame
 * @sdata: भव पूर्णांकerface to build the header क्रम
 * @skb: the skb to build the header in
 * @info_flags: skb flags to set
 * @sta: the station poपूर्णांकer
 * @ctrl_flags: info control flags to set
 * @cookie: cookie poपूर्णांकer to fill (अगर not %शून्य)
 *
 * This function takes the skb with 802.3 header and reक्रमmats the header to
 * the appropriate IEEE 802.11 header based on which पूर्णांकerface the packet is
 * being transmitted on.
 *
 * Note that this function also takes care of the TX status request and
 * potential unsharing of the SKB - this needs to be पूर्णांकerleaved with the
 * header building.
 *
 * The function requires the पढ़ो-side RCU lock held
 *
 * Returns: the (possibly पुनः_स्मृतिated) skb or an ERR_PTR() code
 */
अटल काष्ठा sk_buff *ieee80211_build_hdr(काष्ठा ieee80211_sub_अगर_data *sdata,
					   काष्ठा sk_buff *skb, u32 info_flags,
					   काष्ठा sta_info *sta, u32 ctrl_flags,
					   u64 *cookie)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_tx_info *info;
	पूर्णांक head_need;
	u16 ethertype, hdrlen,  meshhdrlen = 0;
	__le16 fc;
	काष्ठा ieee80211_hdr hdr;
	काष्ठा ieee80211s_hdr mesh_hdr __maybe_unused;
	काष्ठा mesh_path __maybe_unused *mppath = शून्य, *mpath = शून्य;
	स्थिर u8 *encaps_data;
	पूर्णांक encaps_len, skip_header_bytes;
	bool wme_sta = false, authorized = false;
	bool tdls_peer;
	bool multicast;
	u16 info_id = 0;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_sub_अगर_data *ap_sdata;
	क्रमागत nl80211_band band;
	पूर्णांक ret;

	अगर (IS_ERR(sta))
		sta = शून्य;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	अगर (local->क्रमce_tx_status)
		info_flags |= IEEE80211_TX_CTL_REQ_TX_STATUS;
#पूर्ण_अगर

	/* convert Ethernet header to proper 802.11 header (based on
	 * operation mode) */
	ethertype = (skb->data[12] << 8) | skb->data[13];
	fc = cpu_to_le16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA);

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP_VLAN:
		अगर (sdata->wdev.use_4addr) अणु
			fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS);
			/* RA TA DA SA */
			स_नकल(hdr.addr1, sta->sta.addr, ETH_ALEN);
			स_नकल(hdr.addr2, sdata->vअगर.addr, ETH_ALEN);
			स_नकल(hdr.addr3, skb->data, ETH_ALEN);
			स_नकल(hdr.addr4, skb->data + ETH_ALEN, ETH_ALEN);
			hdrlen = 30;
			authorized = test_sta_flag(sta, WLAN_STA_AUTHORIZED);
			wme_sta = sta->sta.wme;
		पूर्ण
		ap_sdata = container_of(sdata->bss, काष्ठा ieee80211_sub_अगर_data,
					u.ap);
		chanctx_conf = rcu_dereference(ap_sdata->vअगर.chanctx_conf);
		अगर (!chanctx_conf) अणु
			ret = -ENOTCONN;
			जाओ मुक्त;
		पूर्ण
		band = chanctx_conf->def.chan->band;
		अगर (sdata->wdev.use_4addr)
			अवरोध;
		fallthrough;
	हाल NL80211_IFTYPE_AP:
		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
			chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
		अगर (!chanctx_conf) अणु
			ret = -ENOTCONN;
			जाओ मुक्त;
		पूर्ण
		fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS);
		/* DA BSSID SA */
		स_नकल(hdr.addr1, skb->data, ETH_ALEN);
		स_नकल(hdr.addr2, sdata->vअगर.addr, ETH_ALEN);
		स_नकल(hdr.addr3, skb->data + ETH_ALEN, ETH_ALEN);
		hdrlen = 24;
		band = chanctx_conf->def.chan->band;
		अवरोध;
#अगर_घोषित CONFIG_MAC80211_MESH
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (!is_multicast_ether_addr(skb->data)) अणु
			काष्ठा sta_info *next_hop;
			bool mpp_lookup = true;

			mpath = mesh_path_lookup(sdata, skb->data);
			अगर (mpath) अणु
				mpp_lookup = false;
				next_hop = rcu_dereference(mpath->next_hop);
				अगर (!next_hop ||
				    !(mpath->flags & (MESH_PATH_ACTIVE |
						      MESH_PATH_RESOLVING)))
					mpp_lookup = true;
			पूर्ण

			अगर (mpp_lookup) अणु
				mppath = mpp_path_lookup(sdata, skb->data);
				अगर (mppath)
					mppath->exp_समय = jअगरfies;
			पूर्ण

			अगर (mppath && mpath)
				mesh_path_del(sdata, mpath->dst);
		पूर्ण

		/*
		 * Use address extension अगर it is a packet from
		 * another पूर्णांकerface or अगर we know the destination
		 * is being proxied by a portal (i.e. portal address
		 * dअगरfers from proxied address)
		 */
		अगर (ether_addr_equal(sdata->vअगर.addr, skb->data + ETH_ALEN) &&
		    !(mppath && !ether_addr_equal(mppath->mpp, skb->data))) अणु
			hdrlen = ieee80211_fill_mesh_addresses(&hdr, &fc,
					skb->data, skb->data + ETH_ALEN);
			meshhdrlen = ieee80211_new_mesh_header(sdata, &mesh_hdr,
							       शून्य, शून्य);
		पूर्ण अन्यथा अणु
			/* DS -> MBSS (802.11-2012 13.11.3.3).
			 * For unicast with unknown क्रमwarding inक्रमmation,
			 * destination might be in the MBSS or अगर that fails
			 * क्रमwarded to another mesh gate. In either हाल
			 * resolution will be handled in ieee80211_xmit(), so
			 * leave the original DA. This also works क्रम mcast */
			स्थिर u8 *mesh_da = skb->data;

			अगर (mppath)
				mesh_da = mppath->mpp;
			अन्यथा अगर (mpath)
				mesh_da = mpath->dst;

			hdrlen = ieee80211_fill_mesh_addresses(&hdr, &fc,
					mesh_da, sdata->vअगर.addr);
			अगर (is_multicast_ether_addr(mesh_da))
				/* DA TA mSA AE:SA */
				meshhdrlen = ieee80211_new_mesh_header(
						sdata, &mesh_hdr,
						skb->data + ETH_ALEN, शून्य);
			अन्यथा
				/* RA TA mDA mSA AE:DA SA */
				meshhdrlen = ieee80211_new_mesh_header(
						sdata, &mesh_hdr, skb->data,
						skb->data + ETH_ALEN);

		पूर्ण
		chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
		अगर (!chanctx_conf) अणु
			ret = -ENOTCONN;
			जाओ मुक्त;
		पूर्ण
		band = chanctx_conf->def.chan->band;

		/* For injected frames, fill RA right away as nexthop lookup
		 * will be skipped.
		 */
		अगर ((ctrl_flags & IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP) &&
		    is_zero_ether_addr(hdr.addr1))
			स_नकल(hdr.addr1, skb->data, ETH_ALEN);
		अवरोध;
#पूर्ण_अगर
	हाल NL80211_IFTYPE_STATION:
		/* we alपढ़ोy did checks when looking up the RA STA */
		tdls_peer = test_sta_flag(sta, WLAN_STA_TDLS_PEER);

		अगर (tdls_peer) अणु
			/* DA SA BSSID */
			स_नकल(hdr.addr1, skb->data, ETH_ALEN);
			स_नकल(hdr.addr2, skb->data + ETH_ALEN, ETH_ALEN);
			स_नकल(hdr.addr3, sdata->u.mgd.bssid, ETH_ALEN);
			hdrlen = 24;
		पूर्ण  अन्यथा अगर (sdata->u.mgd.use_4addr &&
			    cpu_to_be16(ethertype) != sdata->control_port_protocol) अणु
			fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS |
					  IEEE80211_FCTL_TODS);
			/* RA TA DA SA */
			स_नकल(hdr.addr1, sdata->u.mgd.bssid, ETH_ALEN);
			स_नकल(hdr.addr2, sdata->vअगर.addr, ETH_ALEN);
			स_नकल(hdr.addr3, skb->data, ETH_ALEN);
			स_नकल(hdr.addr4, skb->data + ETH_ALEN, ETH_ALEN);
			hdrlen = 30;
		पूर्ण अन्यथा अणु
			fc |= cpu_to_le16(IEEE80211_FCTL_TODS);
			/* BSSID SA DA */
			स_नकल(hdr.addr1, sdata->u.mgd.bssid, ETH_ALEN);
			स_नकल(hdr.addr2, skb->data + ETH_ALEN, ETH_ALEN);
			स_नकल(hdr.addr3, skb->data, ETH_ALEN);
			hdrlen = 24;
		पूर्ण
		chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
		अगर (!chanctx_conf) अणु
			ret = -ENOTCONN;
			जाओ मुक्त;
		पूर्ण
		band = chanctx_conf->def.chan->band;
		अवरोध;
	हाल NL80211_IFTYPE_OCB:
		/* DA SA BSSID */
		स_नकल(hdr.addr1, skb->data, ETH_ALEN);
		स_नकल(hdr.addr2, skb->data + ETH_ALEN, ETH_ALEN);
		eth_broadcast_addr(hdr.addr3);
		hdrlen = 24;
		chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
		अगर (!chanctx_conf) अणु
			ret = -ENOTCONN;
			जाओ मुक्त;
		पूर्ण
		band = chanctx_conf->def.chan->band;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		/* DA SA BSSID */
		स_नकल(hdr.addr1, skb->data, ETH_ALEN);
		स_नकल(hdr.addr2, skb->data + ETH_ALEN, ETH_ALEN);
		स_नकल(hdr.addr3, sdata->u.ibss.bssid, ETH_ALEN);
		hdrlen = 24;
		chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
		अगर (!chanctx_conf) अणु
			ret = -ENOTCONN;
			जाओ मुक्त;
		पूर्ण
		band = chanctx_conf->def.chan->band;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	multicast = is_multicast_ether_addr(hdr.addr1);

	/* sta is always शून्य क्रम mesh */
	अगर (sta) अणु
		authorized = test_sta_flag(sta, WLAN_STA_AUTHORIZED);
		wme_sta = sta->sta.wme;
	पूर्ण अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		/* For mesh, the use of the QoS header is mandatory */
		wme_sta = true;
	पूर्ण

	/* receiver करोes QoS (which also means we करो) use it */
	अगर (wme_sta) अणु
		fc |= cpu_to_le16(IEEE80211_STYPE_QOS_DATA);
		hdrlen += 2;
	पूर्ण

	/*
	 * Drop unicast frames to unauthorised stations unless they are
	 * EAPOL frames from the local station.
	 */
	अगर (unlikely(!ieee80211_vअगर_is_mesh(&sdata->vअगर) &&
		     (sdata->vअगर.type != NL80211_IFTYPE_OCB) &&
		     !multicast && !authorized &&
		     (cpu_to_be16(ethertype) != sdata->control_port_protocol ||
		      !ether_addr_equal(sdata->vअगर.addr, skb->data + ETH_ALEN)))) अणु
#अगर_घोषित CONFIG_MAC80211_VERBOSE_DEBUG
		net_info_ratelimited("%s: dropped frame to %pM (unauthorized port)\n",
				    sdata->name, hdr.addr1);
#पूर्ण_अगर

		I802_DEBUG_INC(local->tx_handlers_drop_unauth_port);

		ret = -EPERM;
		जाओ मुक्त;
	पूर्ण

	अगर (unlikely(!multicast && ((skb->sk &&
		     skb_shinfo(skb)->tx_flags & SKBTX_WIFI_STATUS) ||
		     ctrl_flags & IEEE80211_TX_CTL_REQ_TX_STATUS)))
		info_id = ieee80211_store_ack_skb(local, skb, &info_flags,
						  cookie);

	/*
	 * If the skb is shared we need to obtain our own copy.
	 */
	अगर (skb_shared(skb)) अणु
		काष्ठा sk_buff *पंचांगp_skb = skb;

		/* can't happen -- skb is a clone अगर info_id != 0 */
		WARN_ON(info_id);

		skb = skb_clone(skb, GFP_ATOMIC);
		kमुक्त_skb(पंचांगp_skb);

		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	hdr.frame_control = fc;
	hdr.duration_id = 0;
	hdr.seq_ctrl = 0;

	skip_header_bytes = ETH_HLEN;
	अगर (ethertype == ETH_P_AARP || ethertype == ETH_P_IPX) अणु
		encaps_data = bridge_tunnel_header;
		encaps_len = माप(bridge_tunnel_header);
		skip_header_bytes -= 2;
	पूर्ण अन्यथा अगर (ethertype >= ETH_P_802_3_MIN) अणु
		encaps_data = rfc1042_header;
		encaps_len = माप(rfc1042_header);
		skip_header_bytes -= 2;
	पूर्ण अन्यथा अणु
		encaps_data = शून्य;
		encaps_len = 0;
	पूर्ण

	skb_pull(skb, skip_header_bytes);
	head_need = hdrlen + encaps_len + meshhdrlen - skb_headroom(skb);

	/*
	 * So we need to modअगरy the skb header and hence need a copy of
	 * that. The head_need variable above करोesn't, so far, include
	 * the needed header space that we करोn't need right away. If we
	 * can, then we करोn't पुनः_स्मृतिate right now but only after the
	 * frame arrives at the master device (अगर it करोes...)
	 *
	 * If we cannot, however, then we will पुनः_स्मृतिate to include all
	 * the ever needed space. Also, अगर we need to पुनः_स्मृतिate it anyway,
	 * make it big enough क्रम everything we may ever need.
	 */

	अगर (head_need > 0 || skb_cloned(skb)) अणु
		head_need += sdata->encrypt_headroom;
		head_need += local->tx_headroom;
		head_need = max_t(पूर्णांक, 0, head_need);
		अगर (ieee80211_skb_resize(sdata, skb, head_need, ENCRYPT_DATA)) अणु
			ieee80211_मुक्त_txskb(&local->hw, skb);
			skb = शून्य;
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	अगर (encaps_data)
		स_नकल(skb_push(skb, encaps_len), encaps_data, encaps_len);

#अगर_घोषित CONFIG_MAC80211_MESH
	अगर (meshhdrlen > 0)
		स_नकल(skb_push(skb, meshhdrlen), &mesh_hdr, meshhdrlen);
#पूर्ण_अगर

	अगर (ieee80211_is_data_qos(fc)) अणु
		__le16 *qos_control;

		qos_control = skb_push(skb, 2);
		स_नकल(skb_push(skb, hdrlen - 2), &hdr, hdrlen - 2);
		/*
		 * Maybe we could actually set some fields here, क्रम now just
		 * initialise to zero to indicate no special operation.
		 */
		*qos_control = 0;
	पूर्ण अन्यथा
		स_नकल(skb_push(skb, hdrlen), &hdr, hdrlen);

	skb_reset_mac_header(skb);

	info = IEEE80211_SKB_CB(skb);
	स_रखो(info, 0, माप(*info));

	info->flags = info_flags;
	info->ack_frame_id = info_id;
	info->band = band;
	info->control.flags = ctrl_flags;

	वापस skb;
 मुक्त:
	kमुक्त_skb(skb);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * fast-xmit overview
 *
 * The core idea of this fast-xmit is to हटाओ per-packet checks by checking
 * them out of band. ieee80211_check_fast_xmit() implements the out-of-band
 * checks that are needed to get the sta->fast_tx poपूर्णांकer asचिन्हित, after which
 * much less work can be करोne per packet. For example, fragmentation must be
 * disabled or the fast_tx poपूर्णांकer will not be set. All the conditions are seen
 * in the code here.
 *
 * Once asचिन्हित, the fast_tx data काष्ठाure also caches the per-packet 802.11
 * header and other data to aid packet processing in ieee80211_xmit_fast().
 *
 * The most dअगरficult part of this is that when any of these assumptions
 * change, an बाह्यal trigger (i.e. a call to ieee80211_clear_fast_xmit(),
 * ieee80211_check_fast_xmit() or मित्रs) is required to reset the data,
 * since the per-packet code no दीर्घer checks the conditions. This is reflected
 * by the calls to these functions throughout the rest of the code, and must be
 * मुख्यtained अगर any of the TX path checks change.
 */

व्योम ieee80211_check_fast_xmit(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_fast_tx build = अणुपूर्ण, *fast_tx = शून्य, *old;
	काष्ठा ieee80211_local *local = sta->local;
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)build.hdr;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	__le16 fc;

	अगर (!ieee80211_hw_check(&local->hw, SUPPORT_FAST_XMIT))
		वापस;

	/* Locking here protects both the poपूर्णांकer itself, and against concurrent
	 * invocations winning data access races to, e.g., the key poपूर्णांकer that
	 * is used.
	 * Without it, the invocation of this function right after the key
	 * poपूर्णांकer changes wouldn't be sufficient, as another CPU could access
	 * the poपूर्णांकer, then stall, and then करो the cache update after the CPU
	 * that invalidated the key.
	 * With the locking, such scenarios cannot happen as the check क्रम the
	 * key and the fast-tx assignment are करोne atomically, so the CPU that
	 * modअगरies the key will either रुको or other one will see the key
	 * cleared/changed alपढ़ोy.
	 */
	spin_lock_bh(&sta->lock);
	अगर (ieee80211_hw_check(&local->hw, SUPPORTS_PS) &&
	    !ieee80211_hw_check(&local->hw, SUPPORTS_DYNAMIC_PS) &&
	    sdata->vअगर.type == NL80211_IFTYPE_STATION)
		जाओ out;

	अगर (!test_sta_flag(sta, WLAN_STA_AUTHORIZED))
		जाओ out;

	अगर (test_sta_flag(sta, WLAN_STA_PS_STA) ||
	    test_sta_flag(sta, WLAN_STA_PS_DRIVER) ||
	    test_sta_flag(sta, WLAN_STA_PS_DELIVER) ||
	    test_sta_flag(sta, WLAN_STA_CLEAR_PS_FILT))
		जाओ out;

	अगर (sdata->noack_map)
		जाओ out;

	/* fast-xmit करोesn't handle fragmentation at all */
	अगर (local->hw.wiphy->frag_threshold != (u32)-1 &&
	    !ieee80211_hw_check(&local->hw, SUPPORTS_TX_FRAG))
		जाओ out;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (!chanctx_conf) अणु
		rcu_पढ़ो_unlock();
		जाओ out;
	पूर्ण
	build.band = chanctx_conf->def.chan->band;
	rcu_पढ़ो_unlock();

	fc = cpu_to_le16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA);

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_ADHOC:
		/* DA SA BSSID */
		build.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr1);
		build.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr2);
		स_नकल(hdr->addr3, sdata->u.ibss.bssid, ETH_ALEN);
		build.hdr_len = 24;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (test_sta_flag(sta, WLAN_STA_TDLS_PEER)) अणु
			/* DA SA BSSID */
			build.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr1);
			build.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr2);
			स_नकल(hdr->addr3, sdata->u.mgd.bssid, ETH_ALEN);
			build.hdr_len = 24;
			अवरोध;
		पूर्ण

		अगर (sdata->u.mgd.use_4addr) अणु
			/* non-regular ethertype cannot use the fastpath */
			fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS |
					  IEEE80211_FCTL_TODS);
			/* RA TA DA SA */
			स_नकल(hdr->addr1, sdata->u.mgd.bssid, ETH_ALEN);
			स_नकल(hdr->addr2, sdata->vअगर.addr, ETH_ALEN);
			build.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr3);
			build.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr4);
			build.hdr_len = 30;
			अवरोध;
		पूर्ण
		fc |= cpu_to_le16(IEEE80211_FCTL_TODS);
		/* BSSID SA DA */
		स_नकल(hdr->addr1, sdata->u.mgd.bssid, ETH_ALEN);
		build.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr3);
		build.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr2);
		build.hdr_len = 24;
		अवरोध;
	हाल NL80211_IFTYPE_AP_VLAN:
		अगर (sdata->wdev.use_4addr) अणु
			fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS |
					  IEEE80211_FCTL_TODS);
			/* RA TA DA SA */
			स_नकल(hdr->addr1, sta->sta.addr, ETH_ALEN);
			स_नकल(hdr->addr2, sdata->vअगर.addr, ETH_ALEN);
			build.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr3);
			build.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr4);
			build.hdr_len = 30;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल NL80211_IFTYPE_AP:
		fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS);
		/* DA BSSID SA */
		build.da_offs = दुरत्व(काष्ठा ieee80211_hdr, addr1);
		स_नकल(hdr->addr2, sdata->vअगर.addr, ETH_ALEN);
		build.sa_offs = दुरत्व(काष्ठा ieee80211_hdr, addr3);
		build.hdr_len = 24;
		अवरोध;
	शेष:
		/* not handled on fast-xmit */
		जाओ out;
	पूर्ण

	अगर (sta->sta.wme) अणु
		build.hdr_len += 2;
		fc |= cpu_to_le16(IEEE80211_STYPE_QOS_DATA);
	पूर्ण

	/* We store the key here so there's no poपूर्णांक in using rcu_dereference()
	 * but that's fine because the code that changes the poपूर्णांकers will call
	 * this function after करोing so. For a single CPU that would be enough,
	 * क्रम multiple see the comment above.
	 */
	build.key = rcu_access_poपूर्णांकer(sta->ptk[sta->ptk_idx]);
	अगर (!build.key)
		build.key = rcu_access_poपूर्णांकer(sdata->शेष_unicast_key);
	अगर (build.key) अणु
		bool gen_iv, iv_spc, mmic;

		gen_iv = build.key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_IV;
		iv_spc = build.key->conf.flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE;
		mmic = build.key->conf.flags &
			(IEEE80211_KEY_FLAG_GENERATE_MMIC |
			 IEEE80211_KEY_FLAG_PUT_MIC_SPACE);

		/* करोn't handle software crypto */
		अगर (!(build.key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE))
			जाओ out;

		/* Key is being हटाओd */
		अगर (build.key->flags & KEY_FLAG_TAINTED)
			जाओ out;

		चयन (build.key->conf.cipher) अणु
		हाल WLAN_CIPHER_SUITE_CCMP:
		हाल WLAN_CIPHER_SUITE_CCMP_256:
			अगर (gen_iv)
				build.pn_offs = build.hdr_len;
			अगर (gen_iv || iv_spc)
				build.hdr_len += IEEE80211_CCMP_HDR_LEN;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_GCMP:
		हाल WLAN_CIPHER_SUITE_GCMP_256:
			अगर (gen_iv)
				build.pn_offs = build.hdr_len;
			अगर (gen_iv || iv_spc)
				build.hdr_len += IEEE80211_GCMP_HDR_LEN;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			/* cannot handle MMIC or IV generation in xmit-fast */
			अगर (mmic || gen_iv)
				जाओ out;
			अगर (iv_spc)
				build.hdr_len += IEEE80211_TKIP_IV_LEN;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			/* cannot handle IV generation in fast-xmit */
			अगर (gen_iv)
				जाओ out;
			अगर (iv_spc)
				build.hdr_len += IEEE80211_WEP_IV_LEN;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_AES_CMAC:
		हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
			WARN(1,
			     "management cipher suite 0x%x enabled for data\n",
			     build.key->conf.cipher);
			जाओ out;
		शेष:
			/* we करोn't know how to generate IVs क्रम this at all */
			अगर (WARN_ON(gen_iv))
				जाओ out;
			/* pure hardware keys are OK, of course */
			अगर (!(build.key->flags & KEY_FLAG_CIPHER_SCHEME))
				अवरोध;
			/* cipher scheme might require space allocation */
			अगर (iv_spc &&
			    build.key->conf.iv_len > IEEE80211_FAST_XMIT_MAX_IV)
				जाओ out;
			अगर (iv_spc)
				build.hdr_len += build.key->conf.iv_len;
		पूर्ण

		fc |= cpu_to_le16(IEEE80211_FCTL_PROTECTED);
	पूर्ण

	hdr->frame_control = fc;

	स_नकल(build.hdr + build.hdr_len,
	       rfc1042_header,  माप(rfc1042_header));
	build.hdr_len += माप(rfc1042_header);

	fast_tx = kmemdup(&build, माप(build), GFP_ATOMIC);
	/* अगर the kmemdup fails, जारी w/o fast_tx */
	अगर (!fast_tx)
		जाओ out;

 out:
	/* we might have raced against another call to this function */
	old = rcu_dereference_रक्षित(sta->fast_tx,
					lockdep_is_held(&sta->lock));
	rcu_assign_poपूर्णांकer(sta->fast_tx, fast_tx);
	अगर (old)
		kमुक्त_rcu(old, rcu_head);
	spin_unlock_bh(&sta->lock);
पूर्ण

व्योम ieee80211_check_fast_xmit_all(काष्ठा ieee80211_local *local)
अणु
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &local->sta_list, list)
		ieee80211_check_fast_xmit(sta);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम ieee80211_check_fast_xmit_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अगर (sdata != sta->sdata &&
		    (!sta->sdata->bss || sta->sdata->bss != sdata->bss))
			जारी;
		ieee80211_check_fast_xmit(sta);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

व्योम ieee80211_clear_fast_xmit(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_fast_tx *fast_tx;

	spin_lock_bh(&sta->lock);
	fast_tx = rcu_dereference_रक्षित(sta->fast_tx,
					    lockdep_is_held(&sta->lock));
	RCU_INIT_POINTER(sta->fast_tx, शून्य);
	spin_unlock_bh(&sta->lock);

	अगर (fast_tx)
		kमुक्त_rcu(fast_tx, rcu_head);
पूर्ण

अटल bool ieee80211_amsdu_पुनः_स्मृति_pad(काष्ठा ieee80211_local *local,
					काष्ठा sk_buff *skb, पूर्णांक headroom)
अणु
	अगर (skb_headroom(skb) < headroom) अणु
		I802_DEBUG_INC(local->tx_expand_skb_head);

		अगर (pskb_expand_head(skb, headroom, 0, GFP_ATOMIC)) अणु
			wiphy_debug(local->hw.wiphy,
				    "failed to reallocate TX buffer\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool ieee80211_amsdu_prepare_head(काष्ठा ieee80211_sub_अगर_data *sdata,
					 काष्ठा ieee80211_fast_tx *fast_tx,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ethhdr *amsdu_hdr;
	पूर्णांक hdr_len = fast_tx->hdr_len - माप(rfc1042_header);
	पूर्णांक subframe_len = skb->len - hdr_len;
	व्योम *data;
	u8 *qc, *h_80211_src, *h_80211_dst;
	स्थिर u8 *bssid;

	अगर (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)
		वापस false;

	अगर (info->control.flags & IEEE80211_TX_CTRL_AMSDU)
		वापस true;

	अगर (!ieee80211_amsdu_पुनः_स्मृति_pad(local, skb, माप(*amsdu_hdr)))
		वापस false;

	data = skb_push(skb, माप(*amsdu_hdr));
	स_हटाओ(data, data + माप(*amsdu_hdr), hdr_len);
	hdr = data;
	amsdu_hdr = data + hdr_len;
	/* h_80211_src/dst is addr* field within hdr */
	h_80211_src = data + fast_tx->sa_offs;
	h_80211_dst = data + fast_tx->da_offs;

	amsdu_hdr->h_proto = cpu_to_be16(subframe_len);
	ether_addr_copy(amsdu_hdr->h_source, h_80211_src);
	ether_addr_copy(amsdu_hdr->h_dest, h_80211_dst);

	/* according to IEEE 802.11-2012 8.3.2 table 8-19, the outer SA/DA
	 * fields needs to be changed to BSSID क्रम A-MSDU frames depending
	 * on FromDS/ToDS values.
	 */
	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_STATION:
		bssid = sdata->u.mgd.bssid;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
		bssid = sdata->vअगर.addr;
		अवरोध;
	शेष:
		bssid = शून्य;
	पूर्ण

	अगर (bssid && ieee80211_has_fromds(hdr->frame_control))
		ether_addr_copy(h_80211_src, bssid);

	अगर (bssid && ieee80211_has_tods(hdr->frame_control))
		ether_addr_copy(h_80211_dst, bssid);

	qc = ieee80211_get_qos_ctl(hdr);
	*qc |= IEEE80211_QOS_CTL_A_MSDU_PRESENT;

	info->control.flags |= IEEE80211_TX_CTRL_AMSDU;

	वापस true;
पूर्ण

अटल bool ieee80211_amsdu_aggregate(काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा sta_info *sta,
				      काष्ठा ieee80211_fast_tx *fast_tx,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा fq *fq = &local->fq;
	काष्ठा fq_tin *tin;
	काष्ठा fq_flow *flow;
	u8 tid = skb->priority & IEEE80211_QOS_CTL_TAG1D_MASK;
	काष्ठा ieee80211_txq *txq = sta->sta.txq[tid];
	काष्ठा txq_info *txqi;
	काष्ठा sk_buff **frag_tail, *head;
	पूर्णांक subframe_len = skb->len - ETH_ALEN;
	u8 max_subframes = sta->sta.max_amsdu_subframes;
	पूर्णांक max_frags = local->hw.max_tx_fragments;
	पूर्णांक max_amsdu_len = sta->sta.max_amsdu_len;
	पूर्णांक orig_truesize;
	u32 flow_idx;
	__be16 len;
	व्योम *data;
	bool ret = false;
	अचिन्हित पूर्णांक orig_len;
	पूर्णांक n = 2, nfrags, pad = 0;
	u16 hdrlen;

	अगर (!ieee80211_hw_check(&local->hw, TX_AMSDU))
		वापस false;

	अगर (skb_is_gso(skb))
		वापस false;

	अगर (!txq)
		वापस false;

	txqi = to_txq_info(txq);
	अगर (test_bit(IEEE80211_TXQ_NO_AMSDU, &txqi->flags))
		वापस false;

	अगर (sta->sta.max_rc_amsdu_len)
		max_amsdu_len = min_t(पूर्णांक, max_amsdu_len,
				      sta->sta.max_rc_amsdu_len);

	अगर (sta->sta.max_tid_amsdu_len[tid])
		max_amsdu_len = min_t(पूर्णांक, max_amsdu_len,
				      sta->sta.max_tid_amsdu_len[tid]);

	flow_idx = fq_flow_idx(fq, skb);

	spin_lock_bh(&fq->lock);

	/* TODO: Ideally aggregation should be करोne on dequeue to reमुख्य
	 * responsive to environment changes.
	 */

	tin = &txqi->tin;
	flow = fq_flow_classअगरy(fq, tin, flow_idx, skb);
	head = skb_peek_tail(&flow->queue);
	अगर (!head || skb_is_gso(head))
		जाओ out;

	orig_truesize = head->truesize;
	orig_len = head->len;

	अगर (skb->len + head->len > max_amsdu_len)
		जाओ out;

	nfrags = 1 + skb_shinfo(skb)->nr_frags;
	nfrags += 1 + skb_shinfo(head)->nr_frags;
	frag_tail = &skb_shinfo(head)->frag_list;
	जबतक (*frag_tail) अणु
		nfrags += 1 + skb_shinfo(*frag_tail)->nr_frags;
		frag_tail = &(*frag_tail)->next;
		n++;
	पूर्ण

	अगर (max_subframes && n > max_subframes)
		जाओ out;

	अगर (max_frags && nfrags > max_frags)
		जाओ out;

	अगर (!drv_can_aggregate_in_amsdu(local, head, skb))
		जाओ out;

	अगर (!ieee80211_amsdu_prepare_head(sdata, fast_tx, head))
		जाओ out;

	/*
	 * Pad out the previous subframe to a multiple of 4 by adding the
	 * padding to the next one, that's being added. Note that head->len
	 * is the length of the full A-MSDU, but that works since each समय
	 * we add a new subframe we pad out the previous one to a multiple
	 * of 4 and thus it no दीर्घer matters in the next round.
	 */
	hdrlen = fast_tx->hdr_len - माप(rfc1042_header);
	अगर ((head->len - hdrlen) & 3)
		pad = 4 - ((head->len - hdrlen) & 3);

	अगर (!ieee80211_amsdu_पुनः_स्मृति_pad(local, skb, माप(rfc1042_header) +
						     2 + pad))
		जाओ out_recalc;

	ret = true;
	data = skb_push(skb, ETH_ALEN + 2);
	स_हटाओ(data, data + ETH_ALEN + 2, 2 * ETH_ALEN);

	data += 2 * ETH_ALEN;
	len = cpu_to_be16(subframe_len);
	स_नकल(data, &len, 2);
	स_नकल(data + 2, rfc1042_header, माप(rfc1042_header));

	स_रखो(skb_push(skb, pad), 0, pad);

	head->len += skb->len;
	head->data_len += skb->len;
	*frag_tail = skb;

out_recalc:
	fq->memory_usage += head->truesize - orig_truesize;
	अगर (head->len != orig_len) अणु
		flow->backlog += head->len - orig_len;
		tin->backlog_bytes += head->len - orig_len;
	पूर्ण
out:
	spin_unlock_bh(&fq->lock);

	वापस ret;
पूर्ण

/*
 * Can be called जबतक the sta lock is held. Anything that can cause packets to
 * be generated will cause deadlock!
 */
अटल व्योम ieee80211_xmit_fast_finish(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा sta_info *sta, u8 pn_offs,
				       काष्ठा ieee80211_key *key,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	u8 tid = IEEE80211_NUM_TIDS;

	अगर (key)
		info->control.hw_key = &key->conf;

	dev_sw_netstats_tx_add(skb->dev, 1, skb->len);

	अगर (hdr->frame_control & cpu_to_le16(IEEE80211_STYPE_QOS_DATA)) अणु
		tid = skb->priority & IEEE80211_QOS_CTL_TAG1D_MASK;
		hdr->seq_ctrl = ieee80211_tx_next_seq(sta, tid);
	पूर्ण अन्यथा अणु
		info->flags |= IEEE80211_TX_CTL_ASSIGN_SEQ;
		hdr->seq_ctrl = cpu_to_le16(sdata->sequence_number);
		sdata->sequence_number += 0x10;
	पूर्ण

	अगर (skb_shinfo(skb)->gso_size)
		sta->tx_stats.msdu[tid] +=
			DIV_ROUND_UP(skb->len, skb_shinfo(skb)->gso_size);
	अन्यथा
		sta->tx_stats.msdu[tid]++;

	info->hw_queue = sdata->vअगर.hw_queue[skb_get_queue_mapping(skb)];

	/* statistics normally करोne by ieee80211_tx_h_stats (but that
	 * has to consider fragmentation, so is more complex)
	 */
	sta->tx_stats.bytes[skb_get_queue_mapping(skb)] += skb->len;
	sta->tx_stats.packets[skb_get_queue_mapping(skb)]++;

	अगर (pn_offs) अणु
		u64 pn;
		u8 *crypto_hdr = skb->data + pn_offs;

		चयन (key->conf.cipher) अणु
		हाल WLAN_CIPHER_SUITE_CCMP:
		हाल WLAN_CIPHER_SUITE_CCMP_256:
		हाल WLAN_CIPHER_SUITE_GCMP:
		हाल WLAN_CIPHER_SUITE_GCMP_256:
			pn = atomic64_inc_वापस(&key->conf.tx_pn);
			crypto_hdr[0] = pn;
			crypto_hdr[1] = pn >> 8;
			crypto_hdr[3] = 0x20 | (key->conf.keyidx << 6);
			crypto_hdr[4] = pn >> 16;
			crypto_hdr[5] = pn >> 24;
			crypto_hdr[6] = pn >> 32;
			crypto_hdr[7] = pn >> 40;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool ieee80211_xmit_fast(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा sta_info *sta,
				काष्ठा ieee80211_fast_tx *fast_tx,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	u16 ethertype = (skb->data[12] << 8) | skb->data[13];
	पूर्णांक extra_head = fast_tx->hdr_len - (ETH_HLEN - 2);
	पूर्णांक hw_headroom = sdata->local->hw.extra_tx_headroom;
	काष्ठा ethhdr eth;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)fast_tx->hdr;
	काष्ठा ieee80211_tx_data tx;
	ieee80211_tx_result r;
	काष्ठा tid_ampdu_tx *tid_tx = शून्य;
	u8 tid = IEEE80211_NUM_TIDS;

	/* control port protocol needs a lot of special handling */
	अगर (cpu_to_be16(ethertype) == sdata->control_port_protocol)
		वापस false;

	/* only RFC 1042 SNAP */
	अगर (ethertype < ETH_P_802_3_MIN)
		वापस false;

	/* करोn't handle TX status request here either */
	अगर (skb->sk && skb_shinfo(skb)->tx_flags & SKBTX_WIFI_STATUS)
		वापस false;

	अगर (hdr->frame_control & cpu_to_le16(IEEE80211_STYPE_QOS_DATA)) अणु
		tid = skb->priority & IEEE80211_QOS_CTL_TAG1D_MASK;
		tid_tx = rcu_dereference(sta->ampdu_mlme.tid_tx[tid]);
		अगर (tid_tx) अणु
			अगर (!test_bit(HT_AGG_STATE_OPERATIONAL, &tid_tx->state))
				वापस false;
			अगर (tid_tx->समयout)
				tid_tx->last_tx = jअगरfies;
		पूर्ण
	पूर्ण

	/* after this poपूर्णांक (skb is modअगरied) we cannot वापस false */

	अगर (skb_shared(skb)) अणु
		काष्ठा sk_buff *पंचांगp_skb = skb;

		skb = skb_clone(skb, GFP_ATOMIC);
		kमुक्त_skb(पंचांगp_skb);

		अगर (!skb)
			वापस true;
	पूर्ण

	अगर ((hdr->frame_control & cpu_to_le16(IEEE80211_STYPE_QOS_DATA)) &&
	    ieee80211_amsdu_aggregate(sdata, sta, fast_tx, skb))
		वापस true;

	/* will not be crypto-handled beyond what we करो here, so use false
	 * as the may-encrypt argument क्रम the resize to not account क्रम
	 * more room than we alपढ़ोy have in 'extra_head'
	 */
	अगर (unlikely(ieee80211_skb_resize(sdata, skb,
					  max_t(पूर्णांक, extra_head + hw_headroom -
						     skb_headroom(skb), 0),
					  ENCRYPT_NO))) अणु
		kमुक्त_skb(skb);
		वापस true;
	पूर्ण

	स_नकल(&eth, skb->data, ETH_HLEN - 2);
	hdr = skb_push(skb, extra_head);
	स_नकल(skb->data, fast_tx->hdr, fast_tx->hdr_len);
	स_नकल(skb->data + fast_tx->da_offs, eth.h_dest, ETH_ALEN);
	स_नकल(skb->data + fast_tx->sa_offs, eth.h_source, ETH_ALEN);

	info = IEEE80211_SKB_CB(skb);
	स_रखो(info, 0, माप(*info));
	info->band = fast_tx->band;
	info->control.vअगर = &sdata->vअगर;
	info->flags = IEEE80211_TX_CTL_FIRST_FRAGMENT |
		      IEEE80211_TX_CTL_DONTFRAG |
		      (tid_tx ? IEEE80211_TX_CTL_AMPDU : 0);
	info->control.flags = IEEE80211_TX_CTRL_FAST_XMIT;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	अगर (local->क्रमce_tx_status)
		info->flags |= IEEE80211_TX_CTL_REQ_TX_STATUS;
#पूर्ण_अगर

	अगर (hdr->frame_control & cpu_to_le16(IEEE80211_STYPE_QOS_DATA)) अणु
		tid = skb->priority & IEEE80211_QOS_CTL_TAG1D_MASK;
		*ieee80211_get_qos_ctl(hdr) = tid;
	पूर्ण

	__skb_queue_head_init(&tx.skbs);

	tx.flags = IEEE80211_TX_UNICAST;
	tx.local = local;
	tx.sdata = sdata;
	tx.sta = sta;
	tx.key = fast_tx->key;

	अगर (!ieee80211_hw_check(&local->hw, HAS_RATE_CONTROL)) अणु
		tx.skb = skb;
		r = ieee80211_tx_h_rate_ctrl(&tx);
		skb = tx.skb;
		tx.skb = शून्य;

		अगर (r != TX_CONTINUE) अणु
			अगर (r != TX_QUEUED)
				kमुक्त_skb(skb);
			वापस true;
		पूर्ण
	पूर्ण

	अगर (ieee80211_queue_skb(local, sdata, sta, skb))
		वापस true;

	ieee80211_xmit_fast_finish(sdata, sta, fast_tx->pn_offs,
				   fast_tx->key, skb);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		sdata = container_of(sdata->bss,
				     काष्ठा ieee80211_sub_अगर_data, u.ap);

	__skb_queue_tail(&tx.skbs, skb);
	ieee80211_tx_frags(local, &sdata->vअगर, sta, &tx.skbs, false);
	वापस true;
पूर्ण

काष्ठा sk_buff *ieee80211_tx_dequeue(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा txq_info *txqi = container_of(txq, काष्ठा txq_info, txq);
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा fq *fq = &local->fq;
	काष्ठा fq_tin *tin = &txqi->tin;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_tx_data tx;
	ieee80211_tx_result r;
	काष्ठा ieee80211_vअगर *vअगर = txq->vअगर;

	WARN_ON_ONCE(softirq_count() == 0);

	अगर (!ieee80211_txq_airसमय_check(hw, txq))
		वापस शून्य;

begin:
	spin_lock_bh(&fq->lock);

	अगर (test_bit(IEEE80211_TXQ_STOP, &txqi->flags) ||
	    test_bit(IEEE80211_TXQ_STOP_NETIF_TX, &txqi->flags))
		जाओ out;

	अगर (vअगर->txqs_stopped[txq->ac]) अणु
		set_bit(IEEE80211_TXQ_STOP_NETIF_TX, &txqi->flags);
		जाओ out;
	पूर्ण

	/* Make sure fragments stay together. */
	skb = __skb_dequeue(&txqi->frags);
	अगर (unlikely(skb)) अणु
		अगर (!(IEEE80211_SKB_CB(skb)->control.flags &
				IEEE80211_TX_INTCFL_NEED_TXPROCESSING))
			जाओ out;
		IEEE80211_SKB_CB(skb)->control.flags &=
			~IEEE80211_TX_INTCFL_NEED_TXPROCESSING;
	पूर्ण अन्यथा अणु
		skb = fq_tin_dequeue(fq, tin, fq_tin_dequeue_func);
	पूर्ण

	अगर (!skb)
		जाओ out;

	spin_unlock_bh(&fq->lock);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	info = IEEE80211_SKB_CB(skb);

	स_रखो(&tx, 0, माप(tx));
	__skb_queue_head_init(&tx.skbs);
	tx.local = local;
	tx.skb = skb;
	tx.sdata = vअगर_to_sdata(info->control.vअगर);

	अगर (txq->sta) अणु
		tx.sta = container_of(txq->sta, काष्ठा sta_info, sta);
		/*
		 * Drop unicast frames to unauthorised stations unless they are
		 * injected frames or EAPOL frames from the local station.
		 */
		अगर (unlikely(!(info->flags & IEEE80211_TX_CTL_INJECTED) &&
			     ieee80211_is_data(hdr->frame_control) &&
			     !ieee80211_vअगर_is_mesh(&tx.sdata->vअगर) &&
			     tx.sdata->vअगर.type != NL80211_IFTYPE_OCB &&
			     !is_multicast_ether_addr(hdr->addr1) &&
			     !test_sta_flag(tx.sta, WLAN_STA_AUTHORIZED) &&
			     (!(info->control.flags &
				IEEE80211_TX_CTRL_PORT_CTRL_PROTO) ||
			      !ether_addr_equal(tx.sdata->vअगर.addr,
						hdr->addr2)))) अणु
			I802_DEBUG_INC(local->tx_handlers_drop_unauth_port);
			ieee80211_मुक्त_txskb(&local->hw, skb);
			जाओ begin;
		पूर्ण
	पूर्ण

	/*
	 * The key can be हटाओd जबतक the packet was queued, so need to call
	 * this here to get the current key.
	 */
	r = ieee80211_tx_h_select_key(&tx);
	अगर (r != TX_CONTINUE) अणु
		ieee80211_मुक्त_txskb(&local->hw, skb);
		जाओ begin;
	पूर्ण

	अगर (test_bit(IEEE80211_TXQ_AMPDU, &txqi->flags))
		info->flags |= IEEE80211_TX_CTL_AMPDU;
	अन्यथा
		info->flags &= ~IEEE80211_TX_CTL_AMPDU;

	अगर (info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP)
		जाओ encap_out;

	अगर (info->control.flags & IEEE80211_TX_CTRL_FAST_XMIT) अणु
		काष्ठा sta_info *sta = container_of(txq->sta, काष्ठा sta_info,
						    sta);
		u8 pn_offs = 0;

		अगर (tx.key &&
		    (tx.key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_IV))
			pn_offs = ieee80211_hdrlen(hdr->frame_control);

		ieee80211_xmit_fast_finish(sta->sdata, sta, pn_offs,
					   tx.key, skb);
	पूर्ण अन्यथा अणु
		अगर (invoke_tx_handlers_late(&tx))
			जाओ begin;

		skb = __skb_dequeue(&tx.skbs);

		अगर (!skb_queue_empty(&tx.skbs)) अणु
			spin_lock_bh(&fq->lock);
			skb_queue_splice_tail(&tx.skbs, &txqi->frags);
			spin_unlock_bh(&fq->lock);
		पूर्ण
	पूर्ण

	अगर (skb_has_frag_list(skb) &&
	    !ieee80211_hw_check(&local->hw, TX_FRAG_LIST)) अणु
		अगर (skb_linearize(skb)) अणु
			ieee80211_मुक्त_txskb(&local->hw, skb);
			जाओ begin;
		पूर्ण
	पूर्ण

	चयन (tx.sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_MONITOR:
		अगर (tx.sdata->u.mntr.flags & MONITOR_FLAG_ACTIVE) अणु
			vअगर = &tx.sdata->vअगर;
			अवरोध;
		पूर्ण
		tx.sdata = rcu_dereference(local->monitor_sdata);
		अगर (tx.sdata) अणु
			vअगर = &tx.sdata->vअगर;
			info->hw_queue =
				vअगर->hw_queue[skb_get_queue_mapping(skb)];
		पूर्ण अन्यथा अगर (ieee80211_hw_check(&local->hw, QUEUE_CONTROL)) अणु
			ieee80211_मुक्त_txskb(&local->hw, skb);
			जाओ begin;
		पूर्ण अन्यथा अणु
			vअगर = शून्य;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_AP_VLAN:
		tx.sdata = container_of(tx.sdata->bss,
					काष्ठा ieee80211_sub_अगर_data, u.ap);
		fallthrough;
	शेष:
		vअगर = &tx.sdata->vअगर;
		अवरोध;
	पूर्ण

encap_out:
	IEEE80211_SKB_CB(skb)->control.vअगर = vअगर;

	अगर (vअगर &&
	    wiphy_ext_feature_isset(local->hw.wiphy, NL80211_EXT_FEATURE_AQL)) अणु
		bool ampdu = txq->ac != IEEE80211_AC_VO;
		u32 airसमय;

		airसमय = ieee80211_calc_expected_tx_airसमय(hw, vअगर, txq->sta,
							     skb->len, ampdu);
		अगर (airसमय) अणु
			airसमय = ieee80211_info_set_tx_समय_est(info, airसमय);
			ieee80211_sta_update_pending_airसमय(local, tx.sta,
							     txq->ac,
							     airसमय,
							     false);
		पूर्ण
	पूर्ण

	वापस skb;

out:
	spin_unlock_bh(&fq->lock);

	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_tx_dequeue);

काष्ठा ieee80211_txq *ieee80211_next_txq(काष्ठा ieee80211_hw *hw, u8 ac)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_txq *ret = शून्य;
	काष्ठा txq_info *txqi = शून्य, *head = शून्य;
	bool found_eligible_txq = false;

	spin_lock_bh(&local->active_txq_lock[ac]);

 begin:
	txqi = list_first_entry_or_null(&local->active_txqs[ac],
					काष्ठा txq_info,
					schedule_order);
	अगर (!txqi)
		जाओ out;

	अगर (txqi == head) अणु
		अगर (!found_eligible_txq)
			जाओ out;
		अन्यथा
			found_eligible_txq = false;
	पूर्ण

	अगर (!head)
		head = txqi;

	अगर (txqi->txq.sta) अणु
		काष्ठा sta_info *sta = container_of(txqi->txq.sta,
						    काष्ठा sta_info, sta);
		bool aql_check = ieee80211_txq_airसमय_check(hw, &txqi->txq);
		s64 deficit = sta->airसमय[txqi->txq.ac].deficit;

		अगर (aql_check)
			found_eligible_txq = true;

		अगर (deficit < 0)
			sta->airसमय[txqi->txq.ac].deficit +=
				sta->airसमय_weight;

		अगर (deficit < 0 || !aql_check) अणु
			list_move_tail(&txqi->schedule_order,
				       &local->active_txqs[txqi->txq.ac]);
			जाओ begin;
		पूर्ण
	पूर्ण


	अगर (txqi->schedule_round == local->schedule_round[ac])
		जाओ out;

	list_del_init(&txqi->schedule_order);
	txqi->schedule_round = local->schedule_round[ac];
	ret = &txqi->txq;

out:
	spin_unlock_bh(&local->active_txq_lock[ac]);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ieee80211_next_txq);

व्योम __ieee80211_schedule_txq(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_txq *txq,
			      bool क्रमce)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा txq_info *txqi = to_txq_info(txq);

	spin_lock_bh(&local->active_txq_lock[txq->ac]);

	अगर (list_empty(&txqi->schedule_order) &&
	    (क्रमce || !skb_queue_empty(&txqi->frags) ||
	     txqi->tin.backlog_packets)) अणु
		/* If airसमय accounting is active, always enqueue STAs at the
		 * head of the list to ensure that they only get moved to the
		 * back by the airसमय DRR scheduler once they have a negative
		 * deficit. A station that alपढ़ोy has a negative deficit will
		 * get immediately moved to the back of the list on the next
		 * call to ieee80211_next_txq().
		 */
		अगर (txqi->txq.sta && local->airसमय_flags &&
		    wiphy_ext_feature_isset(local->hw.wiphy,
					    NL80211_EXT_FEATURE_AIRTIME_FAIRNESS))
			list_add(&txqi->schedule_order,
				 &local->active_txqs[txq->ac]);
		अन्यथा
			list_add_tail(&txqi->schedule_order,
				      &local->active_txqs[txq->ac]);
	पूर्ण

	spin_unlock_bh(&local->active_txq_lock[txq->ac]);
पूर्ण
EXPORT_SYMBOL(__ieee80211_schedule_txq);

DEFINE_STATIC_KEY_FALSE(aql_disable);

bool ieee80211_txq_airसमय_check(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	अगर (!wiphy_ext_feature_isset(local->hw.wiphy, NL80211_EXT_FEATURE_AQL))
		वापस true;

	अगर (अटल_branch_unlikely(&aql_disable))
		वापस true;

	अगर (!txq->sta)
		वापस true;

	अगर (unlikely(txq->tid == IEEE80211_NUM_TIDS))
		वापस true;

	sta = container_of(txq->sta, काष्ठा sta_info, sta);
	अगर (atomic_पढ़ो(&sta->airसमय[txq->ac].aql_tx_pending) <
	    sta->airसमय[txq->ac].aql_limit_low)
		वापस true;

	अगर (atomic_पढ़ो(&local->aql_total_pending_airसमय) <
	    local->aql_threshold &&
	    atomic_पढ़ो(&sta->airसमय[txq->ac].aql_tx_pending) <
	    sta->airसमय[txq->ac].aql_limit_high)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(ieee80211_txq_airसमय_check);

bool ieee80211_txq_may_transmit(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा txq_info *iter, *पंचांगp, *txqi = to_txq_info(txq);
	काष्ठा sta_info *sta;
	u8 ac = txq->ac;

	spin_lock_bh(&local->active_txq_lock[ac]);

	अगर (!txqi->txq.sta)
		जाओ out;

	अगर (list_empty(&txqi->schedule_order))
		जाओ out;

	list_क्रम_each_entry_safe(iter, पंचांगp, &local->active_txqs[ac],
				 schedule_order) अणु
		अगर (iter == txqi)
			अवरोध;

		अगर (!iter->txq.sta) अणु
			list_move_tail(&iter->schedule_order,
				       &local->active_txqs[ac]);
			जारी;
		पूर्ण
		sta = container_of(iter->txq.sta, काष्ठा sta_info, sta);
		अगर (sta->airसमय[ac].deficit < 0)
			sta->airसमय[ac].deficit += sta->airसमय_weight;
		list_move_tail(&iter->schedule_order, &local->active_txqs[ac]);
	पूर्ण

	sta = container_of(txqi->txq.sta, काष्ठा sta_info, sta);
	अगर (sta->airसमय[ac].deficit >= 0)
		जाओ out;

	sta->airसमय[ac].deficit += sta->airसमय_weight;
	list_move_tail(&txqi->schedule_order, &local->active_txqs[ac]);
	spin_unlock_bh(&local->active_txq_lock[ac]);

	वापस false;
out:
	अगर (!list_empty(&txqi->schedule_order))
		list_del_init(&txqi->schedule_order);
	spin_unlock_bh(&local->active_txq_lock[ac]);

	वापस true;
पूर्ण
EXPORT_SYMBOL(ieee80211_txq_may_transmit);

व्योम ieee80211_txq_schedule_start(काष्ठा ieee80211_hw *hw, u8 ac)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	spin_lock_bh(&local->active_txq_lock[ac]);
	local->schedule_round[ac]++;
	spin_unlock_bh(&local->active_txq_lock[ac]);
पूर्ण
EXPORT_SYMBOL(ieee80211_txq_schedule_start);

व्योम __ieee80211_subअगर_start_xmit(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev,
				  u32 info_flags,
				  u32 ctrl_flags,
				  u64 *cookie)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	काष्ठा sk_buff *next;

	अगर (unlikely(skb->len < ETH_HLEN)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();

	अगर (ieee80211_lookup_ra_sta(sdata, skb, &sta))
		जाओ out_मुक्त;

	अगर (IS_ERR(sta))
		sta = शून्य;

	अगर (local->ops->wake_tx_queue) अणु
		u16 queue = __ieee80211_select_queue(sdata, sta, skb);
		skb_set_queue_mapping(skb, queue);
		skb_get_hash(skb);
	पूर्ण

	अगर (sta) अणु
		काष्ठा ieee80211_fast_tx *fast_tx;

		sk_pacing_shअगरt_update(skb->sk, sdata->local->hw.tx_sk_pacing_shअगरt);

		fast_tx = rcu_dereference(sta->fast_tx);

		अगर (fast_tx &&
		    ieee80211_xmit_fast(sdata, sta, fast_tx, skb))
			जाओ out;
	पूर्ण

	अगर (skb_is_gso(skb)) अणु
		काष्ठा sk_buff *segs;

		segs = skb_gso_segment(skb, 0);
		अगर (IS_ERR(segs)) अणु
			जाओ out_मुक्त;
		पूर्ण अन्यथा अगर (segs) अणु
			consume_skb(skb);
			skb = segs;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* we cannot process non-linear frames on this path */
		अगर (skb_linearize(skb)) अणु
			kमुक्त_skb(skb);
			जाओ out;
		पूर्ण

		/* the frame could be fragmented, software-encrypted, and other
		 * things so we cannot really handle checksum offload with it -
		 * fix it up in software beक्रमe we handle anything अन्यथा.
		 */
		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			skb_set_transport_header(skb,
						 skb_checksum_start_offset(skb));
			अगर (skb_checksum_help(skb))
				जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	skb_list_walk_safe(skb, skb, next) अणु
		skb_mark_not_on_list(skb);

		अगर (skb->protocol == sdata->control_port_protocol)
			ctrl_flags |= IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP;

		skb = ieee80211_build_hdr(sdata, skb, info_flags,
					  sta, ctrl_flags, cookie);
		अगर (IS_ERR(skb)) अणु
			kमुक्त_skb_list(next);
			जाओ out;
		पूर्ण

		dev_sw_netstats_tx_add(dev, 1, skb->len);

		ieee80211_xmit(sdata, sta, skb);
	पूर्ण
	जाओ out;
 out_मुक्त:
	kमुक्त_skb(skb);
 out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक ieee80211_change_da(काष्ठा sk_buff *skb, काष्ठा sta_info *sta)
अणु
	काष्ठा ethhdr *eth;
	पूर्णांक err;

	err = skb_ensure_writable(skb, ETH_HLEN);
	अगर (unlikely(err))
		वापस err;

	eth = (व्योम *)skb->data;
	ether_addr_copy(eth->h_dest, sta->sta.addr);

	वापस 0;
पूर्ण

अटल bool ieee80211_multicast_to_unicast(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	स्थिर काष्ठा ethhdr *eth = (व्योम *)skb->data;
	स्थिर काष्ठा vlan_ethhdr *ethvlan = (व्योम *)skb->data;
	__be16 ethertype;

	अगर (likely(!is_multicast_ether_addr(eth->h_dest)))
		वापस false;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP_VLAN:
		अगर (sdata->u.vlan.sta)
			वापस false;
		अगर (sdata->wdev.use_4addr)
			वापस false;
		fallthrough;
	हाल NL80211_IFTYPE_AP:
		/* check runसमय toggle क्रम this bss */
		अगर (!sdata->bss->multicast_to_unicast)
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	/* multicast to unicast conversion only क्रम some payload */
	ethertype = eth->h_proto;
	अगर (ethertype == htons(ETH_P_8021Q) && skb->len >= VLAN_ETH_HLEN)
		ethertype = ethvlan->h_vlan_encapsulated_proto;
	चयन (ethertype) अणु
	हाल htons(ETH_P_ARP):
	हाल htons(ETH_P_IP):
	हाल htons(ETH_P_IPV6):
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
ieee80211_convert_to_unicast(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			     काष्ठा sk_buff_head *queue)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	स्थिर काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb->data;
	काष्ठा sta_info *sta, *first = शून्य;
	काष्ठा sk_buff *cloned_skb;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अगर (sdata != sta->sdata)
			/* AP-VLAN mismatch */
			जारी;
		अगर (unlikely(ether_addr_equal(eth->h_source, sta->sta.addr)))
			/* करो not send back to source */
			जारी;
		अगर (!first) अणु
			first = sta;
			जारी;
		पूर्ण
		cloned_skb = skb_clone(skb, GFP_ATOMIC);
		अगर (!cloned_skb)
			जाओ multicast;
		अगर (unlikely(ieee80211_change_da(cloned_skb, sta))) अणु
			dev_kमुक्त_skb(cloned_skb);
			जाओ multicast;
		पूर्ण
		__skb_queue_tail(queue, cloned_skb);
	पूर्ण

	अगर (likely(first)) अणु
		अगर (unlikely(ieee80211_change_da(skb, first)))
			जाओ multicast;
		__skb_queue_tail(queue, skb);
	पूर्ण अन्यथा अणु
		/* no STA connected, drop */
		kमुक्त_skb(skb);
		skb = शून्य;
	पूर्ण

	जाओ out;
multicast:
	__skb_queue_purge(queue);
	__skb_queue_tail(queue, skb);
out:
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * ieee80211_subअगर_start_xmit - netअगर start_xmit function क्रम 802.3 vअगरs
 * @skb: packet to be sent
 * @dev: incoming पूर्णांकerface
 *
 * On failure skb will be मुक्तd.
 */
netdev_tx_t ieee80211_subअगर_start_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev)
अणु
	अगर (unlikely(ieee80211_multicast_to_unicast(skb, dev))) अणु
		काष्ठा sk_buff_head queue;

		__skb_queue_head_init(&queue);
		ieee80211_convert_to_unicast(skb, dev, &queue);
		जबतक ((skb = __skb_dequeue(&queue)))
			__ieee80211_subअगर_start_xmit(skb, dev, 0, 0, शून्य);
	पूर्ण अन्यथा अणु
		__ieee80211_subअगर_start_xmit(skb, dev, 0, 0, शून्य);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल bool ieee80211_tx_8023(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा sk_buff *skb, पूर्णांक led_len,
			      काष्ठा sta_info *sta,
			      bool txpending)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_tx_control control = अणुपूर्ण;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_sta *pubsta = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक q = info->hw_queue;

	अगर (sta)
		sk_pacing_shअगरt_update(skb->sk, local->hw.tx_sk_pacing_shअगरt);

	अगर (ieee80211_queue_skb(local, sdata, sta, skb))
		वापस true;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);

	अगर (local->queue_stop_reasons[q] ||
	    (!txpending && !skb_queue_empty(&local->pending[q]))) अणु
		अगर (txpending)
			skb_queue_head(&local->pending[q], skb);
		अन्यथा
			skb_queue_tail(&local->pending[q], skb);

		spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);

		वापस false;
	पूर्ण

	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);

	अगर (sta && sta->uploaded)
		pubsta = &sta->sta;

	control.sta = pubsta;

	drv_tx(local, &control, skb);

	वापस true;
पूर्ण

अटल व्योम ieee80211_8023_xmit(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा net_device *dev, काष्ठा sta_info *sta,
				काष्ठा ieee80211_key *key, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा tid_ampdu_tx *tid_tx;
	u8 tid;

	अगर (local->ops->wake_tx_queue) अणु
		u16 queue = __ieee80211_select_queue(sdata, sta, skb);
		skb_set_queue_mapping(skb, queue);
		skb_get_hash(skb);
	पूर्ण

	अगर (unlikely(test_bit(SCAN_SW_SCANNING, &local->scanning)) &&
	    test_bit(SDATA_STATE_OFFCHANNEL, &sdata->state))
		जाओ out_मुक्त;

	स_रखो(info, 0, माप(*info));

	tid = skb->priority & IEEE80211_QOS_CTL_TAG1D_MASK;
	tid_tx = rcu_dereference(sta->ampdu_mlme.tid_tx[tid]);
	अगर (tid_tx) अणु
		अगर (!test_bit(HT_AGG_STATE_OPERATIONAL, &tid_tx->state)) अणु
			/* fall back to non-offload slow path */
			__ieee80211_subअगर_start_xmit(skb, dev, 0, 0, शून्य);
			वापस;
		पूर्ण

		info->flags |= IEEE80211_TX_CTL_AMPDU;
		अगर (tid_tx->समयout)
			tid_tx->last_tx = jअगरfies;
	पूर्ण

	अगर (unlikely(skb->sk &&
		     skb_shinfo(skb)->tx_flags & SKBTX_WIFI_STATUS))
		info->ack_frame_id = ieee80211_store_ack_skb(local, skb,
							     &info->flags, शून्य);

	info->hw_queue = sdata->vअगर.hw_queue[skb_get_queue_mapping(skb)];

	dev_sw_netstats_tx_add(dev, 1, skb->len);

	sta->tx_stats.bytes[skb_get_queue_mapping(skb)] += skb->len;
	sta->tx_stats.packets[skb_get_queue_mapping(skb)]++;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		sdata = container_of(sdata->bss,
				     काष्ठा ieee80211_sub_अगर_data, u.ap);

	info->flags |= IEEE80211_TX_CTL_HW_80211_ENCAP;
	info->control.vअगर = &sdata->vअगर;

	अगर (key)
		info->control.hw_key = &key->conf;

	ieee80211_tx_8023(sdata, skb, skb->len, sta, false);

	वापस;

out_मुक्त:
	kमुक्त_skb(skb);
पूर्ण

netdev_tx_t ieee80211_subअगर_start_xmit_8023(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ethhdr *ehdr = (काष्ठा ethhdr *)skb->data;
	काष्ठा ieee80211_key *key;
	काष्ठा sta_info *sta;

	अगर (unlikely(skb->len < ETH_HLEN)) अणु
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	rcu_पढ़ो_lock();

	अगर (ieee80211_lookup_ra_sta(sdata, skb, &sta)) अणु
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	अगर (unlikely(IS_ERR_OR_शून्य(sta) || !sta->uploaded ||
	    !test_sta_flag(sta, WLAN_STA_AUTHORIZED) ||
	    sdata->control_port_protocol == ehdr->h_proto))
		जाओ skip_offload;

	key = rcu_dereference(sta->ptk[sta->ptk_idx]);
	अगर (!key)
		key = rcu_dereference(sdata->शेष_unicast_key);

	अगर (key && (!(key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE) ||
		    key->conf.cipher == WLAN_CIPHER_SUITE_TKIP))
		जाओ skip_offload;

	ieee80211_8023_xmit(sdata, dev, sta, key, skb);
	जाओ out;

skip_offload:
	ieee80211_subअगर_start_xmit(skb, dev);
out:
	rcu_पढ़ो_unlock();

	वापस NETDEV_TX_OK;
पूर्ण

काष्ठा sk_buff *
ieee80211_build_data_ढाँचा(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा sk_buff *skb, u32 info_flags)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_tx_data tx = अणु
		.local = sdata->local,
		.sdata = sdata,
	पूर्ण;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();

	अगर (ieee80211_lookup_ra_sta(sdata, skb, &sta)) अणु
		kमुक्त_skb(skb);
		skb = ERR_PTR(-EINVAL);
		जाओ out;
	पूर्ण

	skb = ieee80211_build_hdr(sdata, skb, info_flags, sta, 0, शून्य);
	अगर (IS_ERR(skb))
		जाओ out;

	hdr = (व्योम *)skb->data;
	tx.sta = sta_info_get(sdata, hdr->addr1);
	tx.skb = skb;

	अगर (ieee80211_tx_h_select_key(&tx) != TX_CONTINUE) अणु
		rcu_पढ़ो_unlock();
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस skb;
पूर्ण

/*
 * ieee80211_clear_tx_pending may not be called in a context where
 * it is possible that it packets could come in again.
 */
व्योम ieee80211_clear_tx_pending(काष्ठा ieee80211_local *local)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < local->hw.queues; i++) अणु
		जबतक ((skb = skb_dequeue(&local->pending[i])) != शून्य)
			ieee80211_मुक्त_txskb(&local->hw, skb);
	पूर्ण
पूर्ण

/*
 * Returns false अगर the frame couldn't be transmitted but was queued instead,
 * which in this हाल means re-queued -- take as an indication to stop sending
 * more pending frames.
 */
अटल bool ieee80211_tx_pending_skb(काष्ठा ieee80211_local *local,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_hdr *hdr;
	bool result;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;

	sdata = vअगर_to_sdata(info->control.vअगर);

	अगर (info->control.flags & IEEE80211_TX_INTCFL_NEED_TXPROCESSING) अणु
		chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
		अगर (unlikely(!chanctx_conf)) अणु
			dev_kमुक्त_skb(skb);
			वापस true;
		पूर्ण
		info->band = chanctx_conf->def.chan->band;
		result = ieee80211_tx(sdata, शून्य, skb, true);
	पूर्ण अन्यथा अगर (info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP) अणु
		अगर (ieee80211_lookup_ra_sta(sdata, skb, &sta)) अणु
			dev_kमुक्त_skb(skb);
			वापस true;
		पूर्ण

		अगर (IS_ERR(sta) || (sta && !sta->uploaded))
			sta = शून्य;

		result = ieee80211_tx_8023(sdata, skb, skb->len, sta, true);
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff_head skbs;

		__skb_queue_head_init(&skbs);
		__skb_queue_tail(&skbs, skb);

		hdr = (काष्ठा ieee80211_hdr *)skb->data;
		sta = sta_info_get(sdata, hdr->addr1);

		result = __ieee80211_tx(local, &skbs, skb->len, sta, true);
	पूर्ण

	वापस result;
पूर्ण

/*
 * Transmit all pending packets. Called from tasklet.
 */
व्योम ieee80211_tx_pending(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ieee80211_local *local = from_tasklet(local, t,
						     tx_pending_tasklet);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	bool txok;

	rcu_पढ़ो_lock();

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	क्रम (i = 0; i < local->hw.queues; i++) अणु
		/*
		 * If queue is stopped by something other than due to pending
		 * frames, or we have no pending frames, proceed to next queue.
		 */
		अगर (local->queue_stop_reasons[i] ||
		    skb_queue_empty(&local->pending[i]))
			जारी;

		जबतक (!skb_queue_empty(&local->pending[i])) अणु
			काष्ठा sk_buff *skb = __skb_dequeue(&local->pending[i]);
			काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

			अगर (WARN_ON(!info->control.vअगर)) अणु
				ieee80211_मुक्त_txskb(&local->hw, skb);
				जारी;
			पूर्ण

			spin_unlock_irqrestore(&local->queue_stop_reason_lock,
						flags);

			txok = ieee80211_tx_pending_skb(local, skb);
			spin_lock_irqsave(&local->queue_stop_reason_lock,
					  flags);
			अगर (!txok)
				अवरोध;
		पूर्ण

		अगर (skb_queue_empty(&local->pending[i]))
			ieee80211_propagate_queue_wake(local, i);
	पूर्ण
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);

	rcu_पढ़ो_unlock();
पूर्ण

/* functions क्रम drivers to get certain frames */

अटल व्योम __ieee80211_beacon_add_tim(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ps_data *ps, काष्ठा sk_buff *skb,
				       bool is_ढाँचा)
अणु
	u8 *pos, *tim;
	पूर्णांक aid0 = 0;
	पूर्णांक i, have_bits = 0, n1, n2;

	/* Generate biपंचांगap क्रम TIM only अगर there are any STAs in घातer save
	 * mode. */
	अगर (atomic_पढ़ो(&ps->num_sta_ps) > 0)
		/* in the hope that this is faster than
		 * checking byte-क्रम-byte */
		have_bits = !biपंचांगap_empty((अचिन्हित दीर्घ *)ps->tim,
					  IEEE80211_MAX_AID+1);
	अगर (!is_ढाँचा) अणु
		अगर (ps->dtim_count == 0)
			ps->dtim_count = sdata->vअगर.bss_conf.dtim_period - 1;
		अन्यथा
			ps->dtim_count--;
	पूर्ण

	tim = pos = skb_put(skb, 6);
	*pos++ = WLAN_EID_TIM;
	*pos++ = 4;
	*pos++ = ps->dtim_count;
	*pos++ = sdata->vअगर.bss_conf.dtim_period;

	अगर (ps->dtim_count == 0 && !skb_queue_empty(&ps->bc_buf))
		aid0 = 1;

	ps->dtim_bc_mc = aid0 == 1;

	अगर (have_bits) अणु
		/* Find largest even number N1 so that bits numbered 1 through
		 * (N1 x 8) - 1 in the biपंचांगap are 0 and number N2 so that bits
		 * (N2 + 1) x 8 through 2007 are 0. */
		n1 = 0;
		क्रम (i = 0; i < IEEE80211_MAX_TIM_LEN; i++) अणु
			अगर (ps->tim[i]) अणु
				n1 = i & 0xfe;
				अवरोध;
			पूर्ण
		पूर्ण
		n2 = n1;
		क्रम (i = IEEE80211_MAX_TIM_LEN - 1; i >= n1; i--) अणु
			अगर (ps->tim[i]) अणु
				n2 = i;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Biपंचांगap control */
		*pos++ = n1 | aid0;
		/* Part Virt Biपंचांगap */
		skb_put(skb, n2 - n1);
		स_नकल(pos, ps->tim + n1, n2 - n1 + 1);

		tim[1] = n2 - n1 + 4;
	पूर्ण अन्यथा अणु
		*pos++ = aid0; /* Biपंचांगap control */
		*pos++ = 0; /* Part Virt Biपंचांगap */
	पूर्ण
पूर्ण

अटल पूर्णांक ieee80211_beacon_add_tim(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ps_data *ps, काष्ठा sk_buff *skb,
				    bool is_ढाँचा)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	/*
	 * Not very nice, but we want to allow the driver to call
	 * ieee80211_beacon_get() as a response to the set_tim()
	 * callback. That, however, is alपढ़ोy invoked under the
	 * sta_lock to guarantee consistent and race-मुक्त update
	 * of the tim biपंचांगap in mac80211 and the driver.
	 */
	अगर (local->tim_in_locked_section) अणु
		__ieee80211_beacon_add_tim(sdata, ps, skb, is_ढाँचा);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&local->tim_lock);
		__ieee80211_beacon_add_tim(sdata, ps, skb, is_ढाँचा);
		spin_unlock_bh(&local->tim_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ieee80211_set_beacon_cntdwn(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा beacon_data *beacon)
अणु
	काष्ठा probe_resp *resp;
	u8 *beacon_data;
	माप_प्रकार beacon_data_len;
	पूर्णांक i;
	u8 count = beacon->cntdwn_current_counter;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP:
		beacon_data = beacon->tail;
		beacon_data_len = beacon->tail_len;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		beacon_data = beacon->head;
		beacon_data_len = beacon->head_len;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		beacon_data = beacon->head;
		beacon_data_len = beacon->head_len;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < IEEE80211_MAX_CNTDWN_COUNTERS_NUM; ++i) अणु
		resp = rcu_dereference(sdata->u.ap.probe_resp);

		अगर (beacon->cntdwn_counter_offsets[i]) अणु
			अगर (WARN_ON_ONCE(beacon->cntdwn_counter_offsets[i] >=
					 beacon_data_len)) अणु
				rcu_पढ़ो_unlock();
				वापस;
			पूर्ण

			beacon_data[beacon->cntdwn_counter_offsets[i]] = count;
		पूर्ण

		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP && resp)
			resp->data[resp->cntdwn_counter_offsets[i]] = count;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल u8 __ieee80211_beacon_update_cntdwn(काष्ठा beacon_data *beacon)
अणु
	beacon->cntdwn_current_counter--;

	/* the counter should never reach 0 */
	WARN_ON_ONCE(!beacon->cntdwn_current_counter);

	वापस beacon->cntdwn_current_counter;
पूर्ण

u8 ieee80211_beacon_update_cntdwn(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा beacon_data *beacon = शून्य;
	u8 count = 0;

	rcu_पढ़ो_lock();

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		beacon = rcu_dereference(sdata->u.ap.beacon);
	अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_ADHOC)
		beacon = rcu_dereference(sdata->u.ibss.presp);
	अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
		beacon = rcu_dereference(sdata->u.mesh.beacon);

	अगर (!beacon)
		जाओ unlock;

	count = __ieee80211_beacon_update_cntdwn(beacon);

unlock:
	rcu_पढ़ो_unlock();
	वापस count;
पूर्ण
EXPORT_SYMBOL(ieee80211_beacon_update_cntdwn);

व्योम ieee80211_beacon_set_cntdwn(काष्ठा ieee80211_vअगर *vअगर, u8 counter)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा beacon_data *beacon = शून्य;

	rcu_पढ़ो_lock();

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		beacon = rcu_dereference(sdata->u.ap.beacon);
	अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_ADHOC)
		beacon = rcu_dereference(sdata->u.ibss.presp);
	अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
		beacon = rcu_dereference(sdata->u.mesh.beacon);

	अगर (!beacon)
		जाओ unlock;

	अगर (counter < beacon->cntdwn_current_counter)
		beacon->cntdwn_current_counter = counter;

unlock:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee80211_beacon_set_cntdwn);

bool ieee80211_beacon_cntdwn_is_complete(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा beacon_data *beacon = शून्य;
	u8 *beacon_data;
	माप_प्रकार beacon_data_len;
	पूर्णांक ret = false;

	अगर (!ieee80211_sdata_running(sdata))
		वापस false;

	rcu_पढ़ो_lock();
	अगर (vअगर->type == NL80211_IFTYPE_AP) अणु
		काष्ठा ieee80211_अगर_ap *ap = &sdata->u.ap;

		beacon = rcu_dereference(ap->beacon);
		अगर (WARN_ON(!beacon || !beacon->tail))
			जाओ out;
		beacon_data = beacon->tail;
		beacon_data_len = beacon->tail_len;
	पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_ADHOC) अणु
		काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;

		beacon = rcu_dereference(अगरibss->presp);
		अगर (!beacon)
			जाओ out;

		beacon_data = beacon->head;
		beacon_data_len = beacon->head_len;
	पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_MESH_POINT) अणु
		काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;

		beacon = rcu_dereference(अगरmsh->beacon);
		अगर (!beacon)
			जाओ out;

		beacon_data = beacon->head;
		beacon_data_len = beacon->head_len;
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		जाओ out;
	पूर्ण

	अगर (!beacon->cntdwn_counter_offsets[0])
		जाओ out;

	अगर (WARN_ON_ONCE(beacon->cntdwn_counter_offsets[0] > beacon_data_len))
		जाओ out;

	अगर (beacon_data[beacon->cntdwn_counter_offsets[0]] == 1)
		ret = true;

 out:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ieee80211_beacon_cntdwn_is_complete);

अटल पूर्णांक ieee80211_beacon_protect(काष्ठा sk_buff *skb,
				    काष्ठा ieee80211_local *local,
				    काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	ieee80211_tx_result res;
	काष्ठा ieee80211_tx_data tx;
	काष्ठा sk_buff *check_skb;

	स_रखो(&tx, 0, माप(tx));
	tx.key = rcu_dereference(sdata->शेष_beacon_key);
	अगर (!tx.key)
		वापस 0;
	tx.local = local;
	tx.sdata = sdata;
	__skb_queue_head_init(&tx.skbs);
	__skb_queue_tail(&tx.skbs, skb);
	res = ieee80211_tx_h_encrypt(&tx);
	check_skb = __skb_dequeue(&tx.skbs);
	/* we may crash after this, but it'd be a bug in crypto */
	WARN_ON(check_skb != skb);
	अगर (WARN_ON_ONCE(res != TX_CONTINUE))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *
__ieee80211_beacon_get(काष्ठा ieee80211_hw *hw,
		       काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_mutable_offsets *offs,
		       bool is_ढाँचा)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा beacon_data *beacon = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_sub_अगर_data *sdata = शून्य;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_tx_rate_control txrc;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	पूर्णांक csa_off_base = 0;

	rcu_पढ़ो_lock();

	sdata = vअगर_to_sdata(vअगर);
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);

	अगर (!ieee80211_sdata_running(sdata) || !chanctx_conf)
		जाओ out;

	अगर (offs)
		स_रखो(offs, 0, माप(*offs));

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
		काष्ठा ieee80211_अगर_ap *ap = &sdata->u.ap;

		beacon = rcu_dereference(ap->beacon);
		अगर (beacon) अणु
			अगर (beacon->cntdwn_counter_offsets[0]) अणु
				अगर (!is_ढाँचा)
					ieee80211_beacon_update_cntdwn(vअगर);

				ieee80211_set_beacon_cntdwn(sdata, beacon);
			पूर्ण

			/*
			 * headroom, head length,
			 * tail length and maximum TIM length
			 */
			skb = dev_alloc_skb(local->tx_headroom +
					    beacon->head_len +
					    beacon->tail_len + 256 +
					    local->hw.extra_beacon_tailroom);
			अगर (!skb)
				जाओ out;

			skb_reserve(skb, local->tx_headroom);
			skb_put_data(skb, beacon->head, beacon->head_len);

			ieee80211_beacon_add_tim(sdata, &ap->ps, skb,
						 is_ढाँचा);

			अगर (offs) अणु
				offs->tim_offset = beacon->head_len;
				offs->tim_length = skb->len - beacon->head_len;

				/* क्रम AP the csa offsets are from tail */
				csa_off_base = skb->len;
			पूर्ण

			अगर (beacon->tail)
				skb_put_data(skb, beacon->tail,
					     beacon->tail_len);

			अगर (ieee80211_beacon_protect(skb, local, sdata) < 0)
				जाओ out;
		पूर्ण अन्यथा
			जाओ out;
	पूर्ण अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_ADHOC) अणु
		काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
		काष्ठा ieee80211_hdr *hdr;

		beacon = rcu_dereference(अगरibss->presp);
		अगर (!beacon)
			जाओ out;

		अगर (beacon->cntdwn_counter_offsets[0]) अणु
			अगर (!is_ढाँचा)
				__ieee80211_beacon_update_cntdwn(beacon);

			ieee80211_set_beacon_cntdwn(sdata, beacon);
		पूर्ण

		skb = dev_alloc_skb(local->tx_headroom + beacon->head_len +
				    local->hw.extra_beacon_tailroom);
		अगर (!skb)
			जाओ out;
		skb_reserve(skb, local->tx_headroom);
		skb_put_data(skb, beacon->head, beacon->head_len);

		hdr = (काष्ठा ieee80211_hdr *) skb->data;
		hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						 IEEE80211_STYPE_BEACON);
	पूर्ण अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;

		beacon = rcu_dereference(अगरmsh->beacon);
		अगर (!beacon)
			जाओ out;

		अगर (beacon->cntdwn_counter_offsets[0]) अणु
			अगर (!is_ढाँचा)
				/* TODO: For mesh csa_counter is in TU, so
				 * decrementing it by one isn't correct, but
				 * क्रम now we leave it consistent with overall
				 * mac80211's behavior.
				 */
				__ieee80211_beacon_update_cntdwn(beacon);

			ieee80211_set_beacon_cntdwn(sdata, beacon);
		पूर्ण

		अगर (अगरmsh->sync_ops)
			अगरmsh->sync_ops->adjust_tsf(sdata, beacon);

		skb = dev_alloc_skb(local->tx_headroom +
				    beacon->head_len +
				    256 + /* TIM IE */
				    beacon->tail_len +
				    local->hw.extra_beacon_tailroom);
		अगर (!skb)
			जाओ out;
		skb_reserve(skb, local->tx_headroom);
		skb_put_data(skb, beacon->head, beacon->head_len);
		ieee80211_beacon_add_tim(sdata, &अगरmsh->ps, skb, is_ढाँचा);

		अगर (offs) अणु
			offs->tim_offset = beacon->head_len;
			offs->tim_length = skb->len - beacon->head_len;
		पूर्ण

		skb_put_data(skb, beacon->tail, beacon->tail_len);
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		जाओ out;
	पूर्ण

	/* CSA offsets */
	अगर (offs && beacon) अणु
		पूर्णांक i;

		क्रम (i = 0; i < IEEE80211_MAX_CNTDWN_COUNTERS_NUM; i++) अणु
			u16 csa_off = beacon->cntdwn_counter_offsets[i];

			अगर (!csa_off)
				जारी;

			offs->cntdwn_counter_offs[i] = csa_off_base + csa_off;
		पूर्ण
	पूर्ण

	band = chanctx_conf->def.chan->band;

	info = IEEE80211_SKB_CB(skb);

	info->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;
	info->flags |= IEEE80211_TX_CTL_NO_ACK;
	info->band = band;

	स_रखो(&txrc, 0, माप(txrc));
	txrc.hw = hw;
	txrc.sband = local->hw.wiphy->bands[band];
	txrc.bss_conf = &sdata->vअगर.bss_conf;
	txrc.skb = skb;
	txrc.reported_rate.idx = -1;
	अगर (sdata->beacon_rate_set && sdata->beacon_rateidx_mask[band])
		txrc.rate_idx_mask = sdata->beacon_rateidx_mask[band];
	अन्यथा
		txrc.rate_idx_mask = sdata->rc_rateidx_mask[band];
	txrc.bss = true;
	rate_control_get_rate(sdata, शून्य, &txrc);

	info->control.vअगर = vअगर;

	info->flags |= IEEE80211_TX_CTL_CLEAR_PS_FILT |
			IEEE80211_TX_CTL_ASSIGN_SEQ |
			IEEE80211_TX_CTL_FIRST_FRAGMENT;
 out:
	rcu_पढ़ो_unlock();
	वापस skb;

पूर्ण

काष्ठा sk_buff *
ieee80211_beacon_get_ढाँचा(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_mutable_offsets *offs)
अणु
	वापस __ieee80211_beacon_get(hw, vअगर, offs, true);
पूर्ण
EXPORT_SYMBOL(ieee80211_beacon_get_ढाँचा);

काष्ठा sk_buff *ieee80211_beacon_get_tim(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर,
					 u16 *tim_offset, u16 *tim_length)
अणु
	काष्ठा ieee80211_mutable_offsets offs = अणुपूर्ण;
	काष्ठा sk_buff *bcn = __ieee80211_beacon_get(hw, vअगर, &offs, false);
	काष्ठा sk_buff *copy;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक shअगरt;

	अगर (!bcn)
		वापस bcn;

	अगर (tim_offset)
		*tim_offset = offs.tim_offset;

	अगर (tim_length)
		*tim_length = offs.tim_length;

	अगर (ieee80211_hw_check(hw, BEACON_TX_STATUS) ||
	    !hw_to_local(hw)->monitors)
		वापस bcn;

	/* send a copy to monitor पूर्णांकerfaces */
	copy = skb_copy(bcn, GFP_ATOMIC);
	अगर (!copy)
		वापस bcn;

	shअगरt = ieee80211_vअगर_get_shअगरt(vअगर);
	sband = ieee80211_get_sband(vअगर_to_sdata(vअगर));
	अगर (!sband)
		वापस bcn;

	ieee80211_tx_monitor(hw_to_local(hw), copy, sband, 1, shअगरt, false,
			     शून्य);

	वापस bcn;
पूर्ण
EXPORT_SYMBOL(ieee80211_beacon_get_tim);

काष्ठा sk_buff *ieee80211_proberesp_get(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_अगर_ap *ap = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा probe_resp *presp = शून्य;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	अगर (sdata->vअगर.type != NL80211_IFTYPE_AP)
		वापस शून्य;

	rcu_पढ़ो_lock();

	ap = &sdata->u.ap;
	presp = rcu_dereference(ap->probe_resp);
	अगर (!presp)
		जाओ out;

	skb = dev_alloc_skb(presp->len);
	अगर (!skb)
		जाओ out;

	skb_put_data(skb, presp->data, presp->len);

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	स_रखो(hdr->addr1, 0, माप(hdr->addr1));

out:
	rcu_पढ़ो_unlock();
	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_proberesp_get);

काष्ठा sk_buff *ieee80211_get_fils_discovery_पंचांगpl(काष्ठा ieee80211_hw *hw,
						  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा fils_discovery_data *पंचांगpl = शून्य;
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	अगर (sdata->vअगर.type != NL80211_IFTYPE_AP)
		वापस शून्य;

	rcu_पढ़ो_lock();
	पंचांगpl = rcu_dereference(sdata->u.ap.fils_discovery);
	अगर (!पंचांगpl) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण

	skb = dev_alloc_skb(sdata->local->hw.extra_tx_headroom + पंचांगpl->len);
	अगर (skb) अणु
		skb_reserve(skb, sdata->local->hw.extra_tx_headroom);
		skb_put_data(skb, पंचांगpl->data, पंचांगpl->len);
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_fils_discovery_पंचांगpl);

काष्ठा sk_buff *
ieee80211_get_unsol_bcast_probe_resp_पंचांगpl(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा unsol_bcast_probe_resp_data *पंचांगpl = शून्य;
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	अगर (sdata->vअगर.type != NL80211_IFTYPE_AP)
		वापस शून्य;

	rcu_पढ़ो_lock();
	पंचांगpl = rcu_dereference(sdata->u.ap.unsol_bcast_probe_resp);
	अगर (!पंचांगpl) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण

	skb = dev_alloc_skb(sdata->local->hw.extra_tx_headroom + पंचांगpl->len);
	अगर (skb) अणु
		skb_reserve(skb, sdata->local->hw.extra_tx_headroom);
		skb_put_data(skb, पंचांगpl->data, पंचांगpl->len);
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_unsol_bcast_probe_resp_पंचांगpl);

काष्ठा sk_buff *ieee80211_pspoll_get(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_अगर_managed *अगरmgd;
	काष्ठा ieee80211_pspoll *pspoll;
	काष्ठा ieee80211_local *local;
	काष्ठा sk_buff *skb;

	अगर (WARN_ON(vअगर->type != NL80211_IFTYPE_STATION))
		वापस शून्य;

	sdata = vअगर_to_sdata(vअगर);
	अगरmgd = &sdata->u.mgd;
	local = sdata->local;

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + माप(*pspoll));
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	pspoll = skb_put_zero(skb, माप(*pspoll));
	pspoll->frame_control = cpu_to_le16(IEEE80211_FTYPE_CTL |
					    IEEE80211_STYPE_PSPOLL);
	pspoll->aid = cpu_to_le16(sdata->vअगर.bss_conf.aid);

	/* aid in PS-Poll has its two MSBs each set to 1 */
	pspoll->aid |= cpu_to_le16(1 << 15 | 1 << 14);

	स_नकल(pspoll->bssid, अगरmgd->bssid, ETH_ALEN);
	स_नकल(pspoll->ta, vअगर->addr, ETH_ALEN);

	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_pspoll_get);

काष्ठा sk_buff *ieee80211_nullfunc_get(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       bool qos_ok)
अणु
	काष्ठा ieee80211_hdr_3addr *nullfunc;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_अगर_managed *अगरmgd;
	काष्ठा ieee80211_local *local;
	काष्ठा sk_buff *skb;
	bool qos = false;

	अगर (WARN_ON(vअगर->type != NL80211_IFTYPE_STATION))
		वापस शून्य;

	sdata = vअगर_to_sdata(vअगर);
	अगरmgd = &sdata->u.mgd;
	local = sdata->local;

	अगर (qos_ok) अणु
		काष्ठा sta_info *sta;

		rcu_पढ़ो_lock();
		sta = sta_info_get(sdata, अगरmgd->bssid);
		qos = sta && sta->sta.wme;
		rcu_पढ़ो_unlock();
	पूर्ण

	skb = dev_alloc_skb(local->hw.extra_tx_headroom +
			    माप(*nullfunc) + 2);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	nullfunc = skb_put_zero(skb, माप(*nullfunc));
	nullfunc->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					      IEEE80211_STYPE_शून्यFUNC |
					      IEEE80211_FCTL_TODS);
	अगर (qos) अणु
		__le16 qoshdr = cpu_to_le16(7);

		BUILD_BUG_ON((IEEE80211_STYPE_QOS_शून्यFUNC |
			      IEEE80211_STYPE_शून्यFUNC) !=
			     IEEE80211_STYPE_QOS_शून्यFUNC);
		nullfunc->frame_control |=
			cpu_to_le16(IEEE80211_STYPE_QOS_शून्यFUNC);
		skb->priority = 7;
		skb_set_queue_mapping(skb, IEEE80211_AC_VO);
		skb_put_data(skb, &qoshdr, माप(qoshdr));
	पूर्ण

	स_नकल(nullfunc->addr1, अगरmgd->bssid, ETH_ALEN);
	स_नकल(nullfunc->addr2, vअगर->addr, ETH_ALEN);
	स_नकल(nullfunc->addr3, अगरmgd->bssid, ETH_ALEN);

	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_nullfunc_get);

काष्ठा sk_buff *ieee80211_probereq_get(काष्ठा ieee80211_hw *hw,
				       स्थिर u8 *src_addr,
				       स्थिर u8 *ssid, माप_प्रकार ssid_len,
				       माप_प्रकार tailroom)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_hdr_3addr *hdr;
	काष्ठा sk_buff *skb;
	माप_प्रकार ie_ssid_len;
	u8 *pos;

	ie_ssid_len = 2 + ssid_len;

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + माप(*hdr) +
			    ie_ssid_len + tailroom);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	hdr = skb_put_zero(skb, माप(*hdr));
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					 IEEE80211_STYPE_PROBE_REQ);
	eth_broadcast_addr(hdr->addr1);
	स_नकल(hdr->addr2, src_addr, ETH_ALEN);
	eth_broadcast_addr(hdr->addr3);

	pos = skb_put(skb, ie_ssid_len);
	*pos++ = WLAN_EID_SSID;
	*pos++ = ssid_len;
	अगर (ssid_len)
		स_नकल(pos, ssid, ssid_len);
	pos += ssid_len;

	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_probereq_get);

व्योम ieee80211_rts_get(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		       स्थिर व्योम *frame, माप_प्रकार frame_len,
		       स्थिर काष्ठा ieee80211_tx_info *frame_txctl,
		       काष्ठा ieee80211_rts *rts)
अणु
	स्थिर काष्ठा ieee80211_hdr *hdr = frame;

	rts->frame_control =
	    cpu_to_le16(IEEE80211_FTYPE_CTL | IEEE80211_STYPE_RTS);
	rts->duration = ieee80211_rts_duration(hw, vअगर, frame_len,
					       frame_txctl);
	स_नकल(rts->ra, hdr->addr1, माप(rts->ra));
	स_नकल(rts->ta, hdr->addr2, माप(rts->ta));
पूर्ण
EXPORT_SYMBOL(ieee80211_rts_get);

व्योम ieee80211_ctstoself_get(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			     स्थिर व्योम *frame, माप_प्रकार frame_len,
			     स्थिर काष्ठा ieee80211_tx_info *frame_txctl,
			     काष्ठा ieee80211_cts *cts)
अणु
	स्थिर काष्ठा ieee80211_hdr *hdr = frame;

	cts->frame_control =
	    cpu_to_le16(IEEE80211_FTYPE_CTL | IEEE80211_STYPE_CTS);
	cts->duration = ieee80211_ctstoself_duration(hw, vअगर,
						     frame_len, frame_txctl);
	स_नकल(cts->ra, hdr->addr1, माप(cts->ra));
पूर्ण
EXPORT_SYMBOL(ieee80211_ctstoself_get);

काष्ठा sk_buff *
ieee80211_get_buffered_bc(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा ieee80211_tx_data tx;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ps_data *ps;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;

	sdata = vअगर_to_sdata(vअगर);

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);

	अगर (!chanctx_conf)
		जाओ out;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
		काष्ठा beacon_data *beacon =
				rcu_dereference(sdata->u.ap.beacon);

		अगर (!beacon || !beacon->head)
			जाओ out;

		ps = &sdata->u.ap.ps;
	पूर्ण अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		ps = &sdata->u.mesh.ps;
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण

	अगर (ps->dtim_count != 0 || !ps->dtim_bc_mc)
		जाओ out; /* send buffered bc/mc only after DTIM beacon */

	जबतक (1) अणु
		skb = skb_dequeue(&ps->bc_buf);
		अगर (!skb)
			जाओ out;
		local->total_ps_buffered--;

		अगर (!skb_queue_empty(&ps->bc_buf) && skb->len >= 2) अणु
			काष्ठा ieee80211_hdr *hdr =
				(काष्ठा ieee80211_hdr *) skb->data;
			/* more buffered multicast/broadcast frames ==> set
			 * MoreData flag in IEEE 802.11 header to inक्रमm PS
			 * STAs */
			hdr->frame_control |=
				cpu_to_le16(IEEE80211_FCTL_MOREDATA);
		पूर्ण

		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
			sdata = IEEE80211_DEV_TO_SUB_IF(skb->dev);
		अगर (!ieee80211_tx_prepare(sdata, &tx, शून्य, skb))
			अवरोध;
		ieee80211_मुक्त_txskb(hw, skb);
	पूर्ण

	info = IEEE80211_SKB_CB(skb);

	tx.flags |= IEEE80211_TX_PS_BUFFERED;
	info->band = chanctx_conf->def.chan->band;

	अगर (invoke_tx_handlers(&tx))
		skb = शून्य;
 out:
	rcu_पढ़ो_unlock();

	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_get_buffered_bc);

पूर्णांक ieee80211_reserve_tid(काष्ठा ieee80211_sta *pubsta, u8 tid)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक ret;
	u32 queues;

	lockdep_निश्चित_held(&local->sta_mtx);

	/* only some हालs are supported right now */
	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (WARN_ON(tid >= IEEE80211_NUM_UPS))
		वापस -EINVAL;

	अगर (sta->reserved_tid == tid) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (sta->reserved_tid != IEEE80211_TID_UNRESERVED) अणु
		sdata_err(sdata, "TID reservation already active\n");
		ret = -EALREADY;
		जाओ out;
	पूर्ण

	ieee80211_stop_vअगर_queues(sdata->local, sdata,
				  IEEE80211_QUEUE_STOP_REASON_RESERVE_TID);

	synchronize_net();

	/* Tear करोwn BA sessions so we stop aggregating on this TID */
	अगर (ieee80211_hw_check(&local->hw, AMPDU_AGGREGATION)) अणु
		set_sta_flag(sta, WLAN_STA_BLOCK_BA);
		__ieee80211_stop_tx_ba_session(sta, tid,
					       AGG_STOP_LOCAL_REQUEST);
	पूर्ण

	queues = BIT(sdata->vअगर.hw_queue[ieee802_1d_to_ac[tid]]);
	__ieee80211_flush_queues(local, sdata, queues, false);

	sta->reserved_tid = tid;

	ieee80211_wake_vअगर_queues(local, sdata,
				  IEEE80211_QUEUE_STOP_REASON_RESERVE_TID);

	अगर (ieee80211_hw_check(&local->hw, AMPDU_AGGREGATION))
		clear_sta_flag(sta, WLAN_STA_BLOCK_BA);

	ret = 0;
 out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ieee80211_reserve_tid);

व्योम ieee80211_unreserve_tid(काष्ठा ieee80211_sta *pubsta, u8 tid)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;

	lockdep_निश्चित_held(&sdata->local->sta_mtx);

	/* only some हालs are supported right now */
	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (tid != sta->reserved_tid) अणु
		sdata_err(sdata, "TID to unreserve (%d) isn't reserved\n", tid);
		वापस;
	पूर्ण

	sta->reserved_tid = IEEE80211_TID_UNRESERVED;
पूर्ण
EXPORT_SYMBOL(ieee80211_unreserve_tid);

व्योम __ieee80211_tx_skb_tid_band(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb, पूर्णांक tid,
				 क्रमागत nl80211_band band)
अणु
	पूर्णांक ac = ieee80211_ac_from_tid(tid);

	skb_reset_mac_header(skb);
	skb_set_queue_mapping(skb, ac);
	skb->priority = tid;

	skb->dev = sdata->dev;

	/*
	 * The other path calling ieee80211_xmit is from the tasklet,
	 * and जबतक we can handle concurrent transmissions locking
	 * requirements are that we करो not come पूर्णांकo tx with bhs on.
	 */
	local_bh_disable();
	IEEE80211_SKB_CB(skb)->band = band;
	ieee80211_xmit(sdata, शून्य, skb);
	local_bh_enable();
पूर्ण

पूर्णांक ieee80211_tx_control_port(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      स्थिर u8 *buf, माप_प्रकार len,
			      स्थिर u8 *dest, __be16 proto, bool unencrypted,
			      u64 *cookie)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	काष्ठा sk_buff *skb;
	काष्ठा ethhdr *ehdr;
	u32 ctrl_flags = 0;
	u32 flags = 0;

	/* Only accept CONTROL_PORT_PROTOCOL configured in CONNECT/ASSOCIATE
	 * or Pre-Authentication
	 */
	अगर (proto != sdata->control_port_protocol &&
	    proto != cpu_to_be16(ETH_P_PREAUTH))
		वापस -EINVAL;

	अगर (proto == sdata->control_port_protocol)
		ctrl_flags |= IEEE80211_TX_CTRL_PORT_CTRL_PROTO |
			      IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP;

	अगर (unencrypted)
		flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;

	अगर (cookie)
		ctrl_flags |= IEEE80211_TX_CTL_REQ_TX_STATUS;

	flags |= IEEE80211_TX_INTFL_NL80211_FRAME_TX;

	skb = dev_alloc_skb(local->hw.extra_tx_headroom +
			    माप(काष्ठा ethhdr) + len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, local->hw.extra_tx_headroom + माप(काष्ठा ethhdr));

	skb_put_data(skb, buf, len);

	ehdr = skb_push(skb, माप(काष्ठा ethhdr));
	स_नकल(ehdr->h_dest, dest, ETH_ALEN);
	स_नकल(ehdr->h_source, sdata->vअगर.addr, ETH_ALEN);
	ehdr->h_proto = proto;

	skb->dev = dev;
	skb->protocol = proto;
	skb_reset_network_header(skb);
	skb_reset_mac_header(skb);

	/* update QoS header to prioritize control port frames अगर possible,
	 * priorization also happens क्रम control port frames send over
	 * AF_PACKET
	 */
	rcu_पढ़ो_lock();

	अगर (ieee80211_lookup_ra_sta(sdata, skb, &sta) == 0 && !IS_ERR(sta)) अणु
		u16 queue = __ieee80211_select_queue(sdata, sta, skb);

		skb_set_queue_mapping(skb, queue);
		skb_get_hash(skb);
	पूर्ण

	rcu_पढ़ो_unlock();

	/* mutex lock is only needed क्रम incrementing the cookie counter */
	mutex_lock(&local->mtx);

	local_bh_disable();
	__ieee80211_subअगर_start_xmit(skb, skb->dev, flags, ctrl_flags, cookie);
	local_bh_enable();

	mutex_unlock(&local->mtx);

	वापस 0;
पूर्ण

पूर्णांक ieee80211_probe_mesh_link(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + len +
			    30 + /* header size */
			    18); /* 11s header size */
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	skb_put_data(skb, buf, len);

	skb->dev = dev;
	skb->protocol = htons(ETH_P_802_3);
	skb_reset_network_header(skb);
	skb_reset_mac_header(skb);

	local_bh_disable();
	__ieee80211_subअगर_start_xmit(skb, skb->dev, 0,
				     IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP,
				     शून्य);
	local_bh_enable();

	वापस 0;
पूर्ण
