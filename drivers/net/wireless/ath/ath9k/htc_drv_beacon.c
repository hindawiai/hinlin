<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "htc.h"

#घोषणा FUDGE 2

व्योम ath9k_htc_beaconq_config(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath9k_tx_queue_info qi, qi_be;

	स_रखो(&qi, 0, माप(काष्ठा ath9k_tx_queue_info));
	स_रखो(&qi_be, 0, माप(काष्ठा ath9k_tx_queue_info));

	ath9k_hw_get_txq_props(ah, priv->beacon.beaconq, &qi);

	अगर (priv->ah->opmode == NL80211_IFTYPE_AP ||
	    priv->ah->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		qi.tqi_aअगरs = 1;
		qi.tqi_cwmin = 0;
		qi.tqi_cwmax = 0;
	पूर्ण अन्यथा अगर (priv->ah->opmode == NL80211_IFTYPE_ADHOC) अणु
		पूर्णांक qnum = priv->hwq_map[IEEE80211_AC_BE];

		ath9k_hw_get_txq_props(ah, qnum, &qi_be);

		qi.tqi_aअगरs = qi_be.tqi_aअगरs;

		/*
		 * For WIFI Beacon Distribution
		 * Long slot समय  : 2x cwmin
		 * Short slot समय : 4x cwmin
		 */
		अगर (ah->slotसमय == 20)
			qi.tqi_cwmin = 2*qi_be.tqi_cwmin;
		अन्यथा
			qi.tqi_cwmin = 4*qi_be.tqi_cwmin;

		qi.tqi_cwmax = qi_be.tqi_cwmax;

	पूर्ण

	अगर (!ath9k_hw_set_txq_props(ah, priv->beacon.beaconq, &qi)) अणु
		ath_err(ath9k_hw_common(ah),
			"Unable to update beacon queue %u!\n", priv->beacon.beaconq);
	पूर्ण अन्यथा अणु
		ath9k_hw_resettxqueue(ah, priv->beacon.beaconq);
	पूर्ण
पूर्ण

/*
 * Both nexttbtt and पूर्णांकval have to be in usecs.
 */
अटल व्योम ath9k_htc_beacon_init(काष्ठा ath9k_htc_priv *priv,
				  काष्ठा ath_beacon_config *conf,
				  bool reset_tsf)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	पूर्णांक ret __attribute__ ((unused));
	__be32 htc_imask = 0;
	u8 cmd_rsp;

	अगर (conf->पूर्णांकval >= TU_TO_USEC(DEFAULT_SWBA_RESPONSE))
		ah->config.sw_beacon_response_समय = DEFAULT_SWBA_RESPONSE;
	अन्यथा
		ah->config.sw_beacon_response_समय = MIN_SWBA_RESPONSE;

	WMI_CMD(WMI_DISABLE_INTR_CMDID);
	अगर (reset_tsf)
		ath9k_hw_reset_tsf(ah);
	ath9k_htc_beaconq_config(priv);
	ath9k_hw_beaconinit(ah, conf->nexttbtt, conf->पूर्णांकval);
	priv->beacon.bmisscnt = 0;
	htc_imask = cpu_to_be32(ah->imask);
	WMI_CMD_BUF(WMI_ENABLE_INTR_CMDID, &htc_imask);
पूर्ण

अटल व्योम ath9k_htc_beacon_config_sta(काष्ठा ath9k_htc_priv *priv,
					काष्ठा ath_beacon_config *bss_conf)
अणु
	काष्ठा ath9k_beacon_state bs;
	क्रमागत ath9k_पूर्णांक imask = 0;
	__be32 htc_imask = 0;
	पूर्णांक ret __attribute__ ((unused));
	u8 cmd_rsp;

	अगर (ath9k_cmn_beacon_config_sta(priv->ah, bss_conf, &bs) == -EPERM)
		वापस;

	WMI_CMD(WMI_DISABLE_INTR_CMDID);
	ath9k_hw_set_sta_beacon_समयrs(priv->ah, &bs);
	imask |= ATH9K_INT_BMISS;
	htc_imask = cpu_to_be32(imask);
	WMI_CMD_BUF(WMI_ENABLE_INTR_CMDID, &htc_imask);
पूर्ण

अटल व्योम ath9k_htc_beacon_config_ap(काष्ठा ath9k_htc_priv *priv,
				       काष्ठा ath_beacon_config *conf)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	ah->imask = 0;

	ath9k_cmn_beacon_config_ap(ah, conf, ATH9K_HTC_MAX_BCN_VIF);
	ath9k_htc_beacon_init(priv, conf, false);
पूर्ण

अटल व्योम ath9k_htc_beacon_config_adhoc(काष्ठा ath9k_htc_priv *priv,
					  काष्ठा ath_beacon_config *conf)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	ah->imask = 0;

	ath9k_cmn_beacon_config_adhoc(ah, conf);
	ath9k_htc_beacon_init(priv, conf, conf->ibss_creator);
पूर्ण

व्योम ath9k_htc_beaconep(व्योम *drv_priv, काष्ठा sk_buff *skb,
			क्रमागत htc_endpoपूर्णांक_id ep_id, bool txok)
अणु
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल व्योम ath9k_htc_send_buffered(काष्ठा ath9k_htc_priv *priv,
				    पूर्णांक slot)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक padpos, padsize, ret, tx_slot;

	spin_lock_bh(&priv->beacon_lock);

	vअगर = priv->beacon.bslot[slot];

	skb = ieee80211_get_buffered_bc(priv->hw, vअगर);

	जबतक(skb) अणु
		hdr = (काष्ठा ieee80211_hdr *) skb->data;

		padpos = ieee80211_hdrlen(hdr->frame_control);
		padsize = padpos & 3;
		अगर (padsize && skb->len > padpos) अणु
			अगर (skb_headroom(skb) < padsize) अणु
				dev_kमुक्त_skb_any(skb);
				जाओ next;
			पूर्ण
			skb_push(skb, padsize);
			स_हटाओ(skb->data, skb->data + padsize, padpos);
		पूर्ण

		tx_slot = ath9k_htc_tx_get_slot(priv);
		अगर (tx_slot < 0) अणु
			ath_dbg(common, XMIT, "No free CAB slot\n");
			dev_kमुक्त_skb_any(skb);
			जाओ next;
		पूर्ण

		ret = ath9k_htc_tx_start(priv, शून्य, skb, tx_slot, true);
		अगर (ret != 0) अणु
			ath9k_htc_tx_clear_slot(priv, tx_slot);
			dev_kमुक्त_skb_any(skb);

			ath_dbg(common, XMIT, "Failed to send CAB frame\n");
		पूर्ण अन्यथा अणु
			spin_lock_bh(&priv->tx.tx_lock);
			priv->tx.queued_cnt++;
			spin_unlock_bh(&priv->tx.tx_lock);
		पूर्ण
	next:
		skb = ieee80211_get_buffered_bc(priv->hw, vअगर);
	पूर्ण

	spin_unlock_bh(&priv->beacon_lock);
पूर्ण

अटल व्योम ath9k_htc_send_beacon(काष्ठा ath9k_htc_priv *priv,
				  पूर्णांक slot)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ath9k_htc_vअगर *avp;
	काष्ठा tx_beacon_header beacon_hdr;
	काष्ठा ath9k_htc_tx_ctl *tx_ctl;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा sk_buff *beacon;
	u8 *tx_fhdr;
	पूर्णांक ret;

	स_रखो(&beacon_hdr, 0, माप(काष्ठा tx_beacon_header));

	spin_lock_bh(&priv->beacon_lock);

	vअगर = priv->beacon.bslot[slot];
	avp = (काष्ठा ath9k_htc_vअगर *)vअगर->drv_priv;

	अगर (unlikely(test_bit(ATH_OP_SCANNING, &common->op_flags))) अणु
		spin_unlock_bh(&priv->beacon_lock);
		वापस;
	पूर्ण

	/* Get a new beacon */
	beacon = ieee80211_beacon_get(priv->hw, vअगर);
	अगर (!beacon) अणु
		spin_unlock_bh(&priv->beacon_lock);
		वापस;
	पूर्ण

	/*
	 * Update the TSF adjust value here, the HW will
	 * add this value क्रम every beacon.
	 */
	mgmt = (काष्ठा ieee80211_mgmt *)beacon->data;
	mgmt->u.beacon.बारtamp = avp->tsfadjust;

	info = IEEE80211_SKB_CB(beacon);
	अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ) अणु
		काष्ठा ieee80211_hdr *hdr =
			(काष्ठा ieee80211_hdr *) beacon->data;
		avp->seq_no += 0x10;
		hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		hdr->seq_ctrl |= cpu_to_le16(avp->seq_no);
	पूर्ण

	tx_ctl = HTC_SKB_CB(beacon);
	स_रखो(tx_ctl, 0, माप(*tx_ctl));

	tx_ctl->type = ATH9K_HTC_BEACON;
	tx_ctl->epid = priv->beacon_ep;

	beacon_hdr.vअगर_index = avp->index;
	tx_fhdr = skb_push(beacon, माप(beacon_hdr));
	स_नकल(tx_fhdr, (u8 *) &beacon_hdr, माप(beacon_hdr));

	ret = htc_send(priv->htc, beacon);
	अगर (ret != 0) अणु
		अगर (ret == -ENOMEM) अणु
			ath_dbg(common, BSTUCK,
				"Failed to send beacon, no free TX buffer\n");
		पूर्ण
		dev_kमुक्त_skb_any(beacon);
	पूर्ण

	spin_unlock_bh(&priv->beacon_lock);

	ath9k_htc_csa_is_finished(priv);
पूर्ण

अटल पूर्णांक ath9k_htc_choose_bslot(काष्ठा ath9k_htc_priv *priv,
				  काष्ठा wmi_event_swba *swba)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	u64 tsf;
	u32 tsftu;
	u16 पूर्णांकval;
	पूर्णांक slot;

	पूर्णांकval = priv->cur_beacon_conf.beacon_पूर्णांकerval;

	tsf = be64_to_cpu(swba->tsf);
	tsftu = TSF_TO_TU(tsf >> 32, tsf);
	slot = ((tsftu % पूर्णांकval) * ATH9K_HTC_MAX_BCN_VIF) / पूर्णांकval;
	slot = ATH9K_HTC_MAX_BCN_VIF - slot - 1;

	ath_dbg(common, BEACON,
		"Choose slot: %d, tsf: %llu, tsftu: %u, intval: %u\n",
		slot, tsf, tsftu, पूर्णांकval);

	वापस slot;
पूर्ण

व्योम ath9k_htc_swba(काष्ठा ath9k_htc_priv *priv,
		    काष्ठा wmi_event_swba *swba)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	पूर्णांक slot;

	अगर (swba->beacon_pending != 0) अणु
		priv->beacon.bmisscnt++;
		अगर (priv->beacon.bmisscnt > BSTUCK_THRESHOLD) अणु
			ath_dbg(common, BSTUCK, "Beacon stuck, HW reset\n");
			ieee80211_queue_work(priv->hw,
					     &priv->fatal_work);
		पूर्ण
		वापस;
	पूर्ण

	अगर (priv->beacon.bmisscnt) अणु
		ath_dbg(common, BSTUCK,
			"Resuming beacon xmit after %u misses\n",
			priv->beacon.bmisscnt);
		priv->beacon.bmisscnt = 0;
	पूर्ण

	slot = ath9k_htc_choose_bslot(priv, swba);
	spin_lock_bh(&priv->beacon_lock);
	अगर (priv->beacon.bslot[slot] == शून्य) अणु
		spin_unlock_bh(&priv->beacon_lock);
		वापस;
	पूर्ण
	spin_unlock_bh(&priv->beacon_lock);

	ath9k_htc_send_buffered(priv, slot);
	ath9k_htc_send_beacon(priv, slot);
पूर्ण

व्योम ath9k_htc_assign_bslot(काष्ठा ath9k_htc_priv *priv,
			    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_vअगर *avp = (काष्ठा ath9k_htc_vअगर *)vअगर->drv_priv;
	पूर्णांक i = 0;

	spin_lock_bh(&priv->beacon_lock);
	क्रम (i = 0; i < ATH9K_HTC_MAX_BCN_VIF; i++) अणु
		अगर (priv->beacon.bslot[i] == शून्य) अणु
			avp->bslot = i;
			अवरोध;
		पूर्ण
	पूर्ण

	priv->beacon.bslot[avp->bslot] = vअगर;
	spin_unlock_bh(&priv->beacon_lock);

	ath_dbg(common, CONFIG, "Added interface at beacon slot: %d\n",
		avp->bslot);
पूर्ण

व्योम ath9k_htc_हटाओ_bslot(काष्ठा ath9k_htc_priv *priv,
			    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_vअगर *avp = (काष्ठा ath9k_htc_vअगर *)vअगर->drv_priv;

	spin_lock_bh(&priv->beacon_lock);
	priv->beacon.bslot[avp->bslot] = शून्य;
	spin_unlock_bh(&priv->beacon_lock);

	ath_dbg(common, CONFIG, "Removed interface at beacon slot: %d\n",
		avp->bslot);
पूर्ण

/*
 * Calculate the TSF adjusपंचांगent value क्रम all slots
 * other than zero.
 */
व्योम ath9k_htc_set_tsfadjust(काष्ठा ath9k_htc_priv *priv,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_vअगर *avp = (काष्ठा ath9k_htc_vअगर *)vअगर->drv_priv;
	काष्ठा ath_beacon_config *cur_conf = &priv->cur_beacon_conf;
	u64 tsfadjust;

	अगर (avp->bslot == 0)
		वापस;

	/*
	 * The beacon पूर्णांकerval cannot be dअगरferent क्रम multi-AP mode,
	 * and we reach here only क्रम VIF slots greater than zero,
	 * so beacon_पूर्णांकerval is guaranteed to be set in cur_conf.
	 */
	tsfadjust = cur_conf->beacon_पूर्णांकerval * avp->bslot / ATH9K_HTC_MAX_BCN_VIF;
	avp->tsfadjust = cpu_to_le64(TU_TO_USEC(tsfadjust));

	ath_dbg(common, CONFIG, "tsfadjust is: %llu for bslot: %d\n",
		(अचिन्हित दीर्घ दीर्घ)tsfadjust, avp->bslot);
पूर्ण

अटल व्योम ath9k_htc_beacon_iter(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	bool *beacon_configured = data;
	काष्ठा ath9k_htc_vअगर *avp = (काष्ठा ath9k_htc_vअगर *) vअगर->drv_priv;

	अगर (vअगर->type == NL80211_IFTYPE_STATION &&
	    avp->beacon_configured)
		*beacon_configured = true;
पूर्ण

अटल bool ath9k_htc_check_beacon_config(काष्ठा ath9k_htc_priv *priv,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath_beacon_config *cur_conf = &priv->cur_beacon_conf;
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;
	bool beacon_configured;

	/*
	 * Changing the beacon पूर्णांकerval when multiple AP पूर्णांकerfaces
	 * are configured will affect beacon transmission of all
	 * of them.
	 */
	अगर ((priv->ah->opmode == NL80211_IFTYPE_AP) &&
	    (priv->num_ap_vअगर > 1) &&
	    (vअगर->type == NL80211_IFTYPE_AP) &&
	    (cur_conf->beacon_पूर्णांकerval != bss_conf->beacon_पूर्णांक)) अणु
		ath_dbg(common, CONFIG,
			"Changing beacon interval of multiple AP interfaces !\n");
		वापस false;
	पूर्ण

	/*
	 * If the HW is operating in AP mode, any new station पूर्णांकerfaces that
	 * are added cannot change the beacon parameters.
	 */
	अगर (priv->num_ap_vअगर &&
	    (vअगर->type != NL80211_IFTYPE_AP)) अणु
		ath_dbg(common, CONFIG,
			"HW in AP mode, cannot set STA beacon parameters\n");
		वापस false;
	पूर्ण

	/*
	 * The beacon parameters are configured only क्रम the first
	 * station पूर्णांकerface.
	 */
	अगर ((priv->ah->opmode == NL80211_IFTYPE_STATION) &&
	    (priv->num_sta_vअगर > 1) &&
	    (vअगर->type == NL80211_IFTYPE_STATION)) अणु
		beacon_configured = false;
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			priv->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
			ath9k_htc_beacon_iter, &beacon_configured);

		अगर (beacon_configured) अणु
			ath_dbg(common, CONFIG,
				"Beacon already configured for a station interface\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

व्योम ath9k_htc_beacon_config(काष्ठा ath9k_htc_priv *priv,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath_beacon_config *cur_conf = &priv->cur_beacon_conf;
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;
	काष्ठा ath9k_htc_vअगर *avp = (काष्ठा ath9k_htc_vअगर *) vअगर->drv_priv;

	अगर (!ath9k_htc_check_beacon_config(priv, vअगर))
		वापस;

	cur_conf->beacon_पूर्णांकerval = bss_conf->beacon_पूर्णांक;
	अगर (cur_conf->beacon_पूर्णांकerval == 0)
		cur_conf->beacon_पूर्णांकerval = 100;

	cur_conf->dtim_period = bss_conf->dtim_period;
	cur_conf->bmiss_समयout =
		ATH_DEFAULT_BMISS_LIMIT * cur_conf->beacon_पूर्णांकerval;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		ath9k_htc_beacon_config_sta(priv, cur_conf);
		avp->beacon_configured = true;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ath9k_htc_beacon_config_adhoc(priv, cur_conf);
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		ath9k_htc_beacon_config_ap(priv, cur_conf);
		अवरोध;
	शेष:
		ath_dbg(common, CONFIG, "Unsupported beaconing mode\n");
		वापस;
	पूर्ण
पूर्ण

व्योम ath9k_htc_beacon_reconfig(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath_beacon_config *cur_conf = &priv->cur_beacon_conf;

	चयन (priv->ah->opmode) अणु
	हाल NL80211_IFTYPE_STATION:
		ath9k_htc_beacon_config_sta(priv, cur_conf);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ath9k_htc_beacon_config_adhoc(priv, cur_conf);
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		ath9k_htc_beacon_config_ap(priv, cur_conf);
		अवरोध;
	शेष:
		ath_dbg(common, CONFIG, "Unsupported beaconing mode\n");
		वापस;
	पूर्ण
पूर्ण

bool ath9k_htc_csa_is_finished(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ieee80211_vअगर *vअगर;

	vअगर = priv->csa_vअगर;
	अगर (!vअगर || !vअगर->csa_active)
		वापस false;

	अगर (!ieee80211_beacon_cntdwn_is_complete(vअगर))
		वापस false;

	ieee80211_csa_finish(vअगर);

	priv->csa_vअगर = शून्य;
	वापस true;
पूर्ण
