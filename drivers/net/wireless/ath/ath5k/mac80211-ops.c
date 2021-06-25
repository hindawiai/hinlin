<शैली गुरु>
/*-
 * Copyright (c) 2002-2005 Sam Leffler, Errno Consulting
 * Copyright (c) 2004-2005 Atheros Communications, Inc.
 * Copyright (c) 2006 Devicescape Software, Inc.
 * Copyright (c) 2007 Jiri Slaby <jirislaby@gmail.com>
 * Copyright (c) 2007 Luis R. Rodriguez <mcgrof@winlab.rutgers.edu>
 * Copyright (c) 2010 Bruno Ranकरोlf <br1@einfach.org>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    similar to the "NO WARRANTY" disclaimer below ("Disclaimer") and any
 *    redistribution must be conditioned upon including a substantially
 *    similar Disclaimer requirement क्रम further binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTIBILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <net/mac80211.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ath5k.h"
#समावेश "base.h"
#समावेश "reg.h"

/********************\
* Mac80211 functions *
\********************/

अटल व्योम
ath5k_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_tx_control *control,
	 काष्ठा sk_buff *skb)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	u16 qnum = skb_get_queue_mapping(skb);

	अगर (WARN_ON(qnum >= ah->ah_capabilities.cap_queues.q_tx_num)) अणु
		ieee80211_मुक्त_txskb(hw, skb);
		वापस;
	पूर्ण

	ath5k_tx_queue(hw, skb, &ah->txqs[qnum], control);
पूर्ण


अटल पूर्णांक
ath5k_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	पूर्णांक ret;
	काष्ठा ath5k_vअगर *avf = (व्योम *)vअगर->drv_priv;

	mutex_lock(&ah->lock);

	अगर ((vअगर->type == NL80211_IFTYPE_AP ||
	     vअगर->type == NL80211_IFTYPE_ADHOC)
	    && (ah->num_ap_vअगरs + ah->num_adhoc_vअगरs) >= ATH_BCBUF) अणु
		ret = -ELNRNG;
		जाओ end;
	पूर्ण

	/* Don't allow other पूर्णांकerfaces अगर one ad-hoc is configured.
	 * TODO: Fix the problems with ad-hoc and multiple other पूर्णांकerfaces.
	 * We would need to operate the HW in ad-hoc mode to allow TSF updates
	 * क्रम the IBSS, but this अवरोधs with additional AP or STA पूर्णांकerfaces
	 * at the moment. */
	अगर (ah->num_adhoc_vअगरs ||
	    (ah->nvअगरs && vअगर->type == NL80211_IFTYPE_ADHOC)) अणु
		ATH5K_ERR(ah, "Only one single ad-hoc interface is allowed.\n");
		ret = -ELNRNG;
		जाओ end;
	पूर्ण

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_MESH_POINT:
		avf->opmode = vअगर->type;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		जाओ end;
	पूर्ण

	ah->nvअगरs++;
	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "add interface mode %d\n", avf->opmode);

	/* Assign the vap/adhoc to a beacon xmit slot. */
	अगर ((avf->opmode == NL80211_IFTYPE_AP) ||
	    (avf->opmode == NL80211_IFTYPE_ADHOC) ||
	    (avf->opmode == NL80211_IFTYPE_MESH_POINT)) अणु
		पूर्णांक slot;

		WARN_ON(list_empty(&ah->bcbuf));
		avf->bbuf = list_first_entry(&ah->bcbuf, काष्ठा ath5k_buf,
					     list);
		list_del(&avf->bbuf->list);

		avf->bslot = 0;
		क्रम (slot = 0; slot < ATH_BCBUF; slot++) अणु
			अगर (!ah->bslot[slot]) अणु
				avf->bslot = slot;
				अवरोध;
			पूर्ण
		पूर्ण
		BUG_ON(ah->bslot[avf->bslot] != शून्य);
		ah->bslot[avf->bslot] = vअगर;
		अगर (avf->opmode == NL80211_IFTYPE_AP)
			ah->num_ap_vअगरs++;
		अन्यथा अगर (avf->opmode == NL80211_IFTYPE_ADHOC)
			ah->num_adhoc_vअगरs++;
		अन्यथा अगर (avf->opmode == NL80211_IFTYPE_MESH_POINT)
			ah->num_mesh_vअगरs++;
	पूर्ण

	/* Any MAC address is fine, all others are included through the
	 * filter.
	 */
	ath5k_hw_set_lladdr(ah, vअगर->addr);

	ath5k_update_bssid_mask_and_opmode(ah, vअगर);
	ret = 0;
end:
	mutex_unlock(&ah->lock);
	वापस ret;
पूर्ण


अटल व्योम
ath5k_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
		       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ath5k_vअगर *avf = (व्योम *)vअगर->drv_priv;
	अचिन्हित पूर्णांक i;

	mutex_lock(&ah->lock);
	ah->nvअगरs--;

	अगर (avf->bbuf) अणु
		ath5k_txbuf_मुक्त_skb(ah, avf->bbuf);
		list_add_tail(&avf->bbuf->list, &ah->bcbuf);
		क्रम (i = 0; i < ATH_BCBUF; i++) अणु
			अगर (ah->bslot[i] == vअगर) अणु
				ah->bslot[i] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		avf->bbuf = शून्य;
	पूर्ण
	अगर (avf->opmode == NL80211_IFTYPE_AP)
		ah->num_ap_vअगरs--;
	अन्यथा अगर (avf->opmode == NL80211_IFTYPE_ADHOC)
		ah->num_adhoc_vअगरs--;
	अन्यथा अगर (avf->opmode == NL80211_IFTYPE_MESH_POINT)
		ah->num_mesh_vअगरs--;

	ath5k_update_bssid_mask_and_opmode(ah, शून्य);
	mutex_unlock(&ah->lock);
पूर्ण


/*
 * TODO: Phy disable/भागersity etc
 */
अटल पूर्णांक
ath5k_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&ah->lock);

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		ret = ath5k_chan_set(ah, &conf->chandef);
		अगर (ret < 0)
			जाओ unlock;
	पूर्ण

	अगर ((changed & IEEE80211_CONF_CHANGE_POWER) &&
	(ah->ah_txघातer.txp_requested != conf->घातer_level)) अणु
		ah->ah_txघातer.txp_requested = conf->घातer_level;

		/* Half dB steps */
		ath5k_hw_set_txघातer_limit(ah, (conf->घातer_level * 2));
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS) अणु
		ah->ah_retry_दीर्घ = conf->दीर्घ_frame_max_tx_count;
		ah->ah_retry_लघु = conf->लघु_frame_max_tx_count;

		क्रम (i = 0; i < ah->ah_capabilities.cap_queues.q_tx_num; i++)
			ath5k_hw_set_tx_retry_limits(ah, i);
	पूर्ण

	/* TODO:
	 * 1) Move this on config_पूर्णांकerface and handle each हाल
	 * separately eg. when we have only one STA vअगर, use
	 * AR5K_ANTMODE_SINGLE_AP
	 *
	 * 2) Allow the user to change antenna mode eg. when only
	 * one antenna is present
	 *
	 * 3) Allow the user to set शेष/tx antenna when possible
	 *
	 * 4) Default mode should handle 90% of the हालs, together
	 * with fixed a/b and single AP modes we should be able to
	 * handle 99%. Sectored modes are extreme हालs and i still
	 * haven't found a usage क्रम them. If we decide to support them,
	 * then we must allow the user to set how many tx antennas we
	 * have available
	 */
	ath5k_hw_set_antenna_mode(ah, ah->ah_ant_mode);

unlock:
	mutex_unlock(&ah->lock);
	वापस ret;
पूर्ण


अटल व्योम
ath5k_bss_info_changed(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_bss_conf *bss_conf, u32 changes)
अणु
	काष्ठा ath5k_vअगर *avf = (व्योम *)vअगर->drv_priv;
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ath_common *common = ath5k_hw_common(ah);

	mutex_lock(&ah->lock);

	अगर (changes & BSS_CHANGED_BSSID) अणु
		/* Cache क्रम later use during resets */
		स_नकल(common->curbssid, bss_conf->bssid, ETH_ALEN);
		common->curaid = 0;
		ath5k_hw_set_bssid(ah);
	पूर्ण

	अगर (changes & BSS_CHANGED_BEACON_INT)
		ah->bपूर्णांकval = bss_conf->beacon_पूर्णांक;

	अगर (changes & BSS_CHANGED_ERP_SLOT) अणु
		पूर्णांक slot_समय;

		ah->ah_लघु_slot = bss_conf->use_लघु_slot;
		slot_समय = ath5k_hw_get_शेष_slotसमय(ah) +
			    3 * ah->ah_coverage_class;
		ath5k_hw_set_अगरs_पूर्णांकervals(ah, slot_समय);
	पूर्ण

	अगर (changes & BSS_CHANGED_ASSOC) अणु
		avf->assoc = bss_conf->assoc;
		अगर (bss_conf->assoc)
			ah->assoc = bss_conf->assoc;
		अन्यथा
			ah->assoc = ath5k_any_vअगर_assoc(ah);

		अगर (ah->opmode == NL80211_IFTYPE_STATION)
			ath5k_set_beacon_filter(hw, ah->assoc);
		ath5k_hw_set_ledstate(ah, ah->assoc ?
			AR5K_LED_ASSOC : AR5K_LED_INIT);
		अगर (bss_conf->assoc) अणु
			ATH5K_DBG(ah, ATH5K_DEBUG_ANY,
				  "Bss Info ASSOC %d, bssid: %pM\n",
				  bss_conf->aid, common->curbssid);
			common->curaid = bss_conf->aid;
			ath5k_hw_set_bssid(ah);
			/* Once ANI is available you would start it here */
		पूर्ण
	पूर्ण

	अगर (changes & BSS_CHANGED_BEACON) अणु
		spin_lock_bh(&ah->block);
		ath5k_beacon_update(hw, vअगर);
		spin_unlock_bh(&ah->block);
	पूर्ण

	अगर (changes & BSS_CHANGED_BEACON_ENABLED)
		ah->enable_beacon = bss_conf->enable_beacon;

	अगर (changes & (BSS_CHANGED_BEACON | BSS_CHANGED_BEACON_ENABLED |
		       BSS_CHANGED_BEACON_INT))
		ath5k_beacon_config(ah);

	mutex_unlock(&ah->lock);
पूर्ण


अटल u64
ath5k_prepare_multicast(काष्ठा ieee80211_hw *hw,
			काष्ठा netdev_hw_addr_list *mc_list)
अणु
	u32 mfilt[2], val;
	u8 pos;
	काष्ठा netdev_hw_addr *ha;

	mfilt[0] = 0;
	mfilt[1] = 0;

	netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
		/* calculate XOR of eight 6-bit values */
		val = get_unaligned_le32(ha->addr + 0);
		pos = (val >> 18) ^ (val >> 12) ^ (val >> 6) ^ val;
		val = get_unaligned_le32(ha->addr + 3);
		pos ^= (val >> 18) ^ (val >> 12) ^ (val >> 6) ^ val;
		pos &= 0x3f;
		mfilt[pos / 32] |= (1 << (pos % 32));
		/* XXX: we might be able to just करो this instead,
		* but not sure, needs testing, अगर we करो use this we'd
		* need to inक्रमm below not to reset the mcast */
		/* ath5k_hw_set_mcast_filterindex(ah,
		 *      ha->addr[5]); */
	पूर्ण

	वापस ((u64)(mfilt[1]) << 32) | mfilt[0];
पूर्ण


/*
 * o always accept unicast, broadcast, and multicast traffic
 * o multicast traffic क्रम all BSSIDs will be enabled अगर mac80211
 *   says it should be
 * o मुख्यtain current state of phy ofdm or phy cck error reception.
 *   If the hardware detects any of these type of errors then
 *   ath5k_hw_get_rx_filter() will pass to us the respective
 *   hardware filters to be able to receive these type of frames.
 * o probe request frames are accepted only when operating in
 *   hostap, adhoc, or monitor modes
 * o enable promiscuous mode according to the पूर्णांकerface state
 * o accept beacons:
 *   - when operating in adhoc mode so the 802.11 layer creates
 *     node table entries क्रम peers,
 *   - when operating in station mode क्रम collecting rssi data when
 *     the station is otherwise quiet, or
 *   - when scanning
 */
अटल व्योम
ath5k_configure_filter(काष्ठा ieee80211_hw *hw, अचिन्हित पूर्णांक changed_flags,
		       अचिन्हित पूर्णांक *new_flags, u64 multicast)
अणु
#घोषणा SUPPORTED_FIF_FLAGS \
	(FIF_ALLMULTI | FIF_FCSFAIL | \
	FIF_PLCPFAIL | FIF_CONTROL | FIF_OTHER_BSS | \
	FIF_BCN_PRBRESP_PROMISC)

	काष्ठा ath5k_hw *ah = hw->priv;
	u32 mfilt[2], rfilt;
	काष्ठा ath5k_vअगर_iter_data iter_data; /* to count STA पूर्णांकerfaces */

	mutex_lock(&ah->lock);

	mfilt[0] = multicast;
	mfilt[1] = multicast >> 32;

	/* Only deal with supported flags */
	changed_flags &= SUPPORTED_FIF_FLAGS;
	*new_flags &= SUPPORTED_FIF_FLAGS;

	/* If HW detects any phy or radar errors, leave those filters on.
	 * Also, always enable Unicast, Broadcasts and Multicast
	 * XXX: move unicast, bssid broadcasts and multicast to mac80211 */
	rfilt = (ath5k_hw_get_rx_filter(ah) & (AR5K_RX_FILTER_PHYERR)) |
		(AR5K_RX_FILTER_UCAST | AR5K_RX_FILTER_BCAST |
		AR5K_RX_FILTER_MCAST);

	/* Note, AR5K_RX_FILTER_MCAST is alपढ़ोy enabled */
	अगर (*new_flags & FIF_ALLMULTI) अणु
		mfilt[0] =  ~0;
		mfilt[1] =  ~0;
	पूर्ण

	/* This is the best we can करो */
	अगर (*new_flags & (FIF_FCSFAIL | FIF_PLCPFAIL))
		rfilt |= AR5K_RX_FILTER_PHYERR;

	/* FIF_BCN_PRBRESP_PROMISC really means to enable beacons
	* and probes क्रम any BSSID */
	अगर ((*new_flags & FIF_BCN_PRBRESP_PROMISC) || (ah->nvअगरs > 1))
		rfilt |= AR5K_RX_FILTER_BEACON;

	/* FIF_CONTROL करोc says we should only pass on control frames क्रम this
	 * station. This needs testing. I believe right now this
	 * enables *all* control frames, which is OK.. but
	 * but we should see अगर we can improve on granularity */
	अगर (*new_flags & FIF_CONTROL)
		rfilt |= AR5K_RX_FILTER_CONTROL;

	/* Additional settings per mode -- this is per ath5k */

	/* XXX move these to mac80211, and add a beacon IFF flag to mac80211 */

	चयन (ah->opmode) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
		rfilt |= AR5K_RX_FILTER_CONTROL |
			 AR5K_RX_FILTER_BEACON |
			 AR5K_RX_FILTER_PROBEREQ |
			 AR5K_RX_FILTER_PROM;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_ADHOC:
		rfilt |= AR5K_RX_FILTER_PROBEREQ |
			 AR5K_RX_FILTER_BEACON;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (ah->assoc)
			rfilt |= AR5K_RX_FILTER_BEACON;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	iter_data.hw_macaddr = शून्य;
	iter_data.n_stas = 0;
	iter_data.need_set_hw_addr = false;
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		ah->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		ath5k_vअगर_iter, &iter_data);

	/* Set up RX Filter */
	अगर (iter_data.n_stas > 1) अणु
		/* If you have multiple STA पूर्णांकerfaces connected to
		 * dअगरferent APs, ARPs are not received (most of the समय?)
		 * Enabling PROMISC appears to fix that problem.
		 */
		rfilt |= AR5K_RX_FILTER_PROM;
	पूर्ण

	/* Set filters */
	ath5k_hw_set_rx_filter(ah, rfilt);

	/* Set multicast bits */
	ath5k_hw_set_mcast_filter(ah, mfilt[0], mfilt[1]);
	/* Set the cached hw filter flags, this will later actually
	 * be set in HW */
	ah->filter_flags = rfilt;
	/* Store current FIF filter flags */
	ah->fअगर_filter_flags = *new_flags;

	mutex_unlock(&ah->lock);
पूर्ण


अटल पूर्णांक
ath5k_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
	      काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
	      काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	पूर्णांक ret = 0;

	अगर (ath5k_modparam_nohwcrypt)
		वापस -EOPNOTSUPP;

	अगर (key->flags & IEEE80211_KEY_FLAG_RX_MGMT)
		वापस -EOPNOTSUPP;

	अगर (vअगर->type == NL80211_IFTYPE_ADHOC &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		/* करोn't program group keys when using IBSS_RSN */
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
	हाल WLAN_CIPHER_SUITE_TKIP:
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		अगर (common->crypt_caps & ATH_CRYPT_CAP_CIPHER_AESCCM)
			अवरोध;
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&ah->lock);

	चयन (cmd) अणु
	हाल SET_KEY:
		ret = ath_key_config(common, vअगर, sta, key);
		अगर (ret >= 0) अणु
			key->hw_key_idx = ret;
			/* push IV and Michael MIC generation to stack */
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP)
				key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
			अगर (key->cipher == WLAN_CIPHER_SUITE_CCMP)
				key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
			ret = 0;
		पूर्ण
		अवरोध;
	हाल DISABLE_KEY:
		ath_key_delete(common, key->hw_key_idx);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&ah->lock);
	वापस ret;
पूर्ण


अटल व्योम
ath5k_sw_scan_start(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_vअगर *vअगर,
		    स्थिर u8 *mac_addr)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	अगर (!ah->assoc)
		ath5k_hw_set_ledstate(ah, AR5K_LED_SCAN);
पूर्ण


अटल व्योम
ath5k_sw_scan_complete(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	ath5k_hw_set_ledstate(ah, ah->assoc ?
		AR5K_LED_ASSOC : AR5K_LED_INIT);
पूर्ण


अटल पूर्णांक
ath5k_get_stats(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;

	/* Force update */
	ath5k_hw_update_mib_counters(ah);

	stats->करोt11ACKFailureCount = ah->stats.ack_fail;
	stats->करोt11RTSFailureCount = ah->stats.rts_fail;
	stats->करोt11RTSSuccessCount = ah->stats.rts_ok;
	stats->करोt11FCSErrorCount = ah->stats.fcs_error;

	वापस 0;
पूर्ण


अटल पूर्णांक
ath5k_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर, u16 queue,
	      स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ath5k_txq_info qi;
	पूर्णांक ret = 0;

	अगर (queue >= ah->ah_capabilities.cap_queues.q_tx_num)
		वापस 0;

	mutex_lock(&ah->lock);

	ath5k_hw_get_tx_queueprops(ah, queue, &qi);

	qi.tqi_aअगरs = params->aअगरs;
	qi.tqi_cw_min = params->cw_min;
	qi.tqi_cw_max = params->cw_max;
	qi.tqi_burst_समय = params->txop * 32;

	ATH5K_DBG(ah, ATH5K_DEBUG_ANY,
		  "Configure tx [queue %d],  "
		  "aifs: %d, cw_min: %d, cw_max: %d, txop: %d\n",
		  queue, params->aअगरs, params->cw_min,
		  params->cw_max, params->txop);

	अगर (ath5k_hw_set_tx_queueprops(ah, queue, &qi)) अणु
		ATH5K_ERR(ah,
			  "Unable to update hardware queue %u!\n", queue);
		ret = -EIO;
	पूर्ण अन्यथा
		ath5k_hw_reset_tx_queue(ah, queue);

	mutex_unlock(&ah->lock);

	वापस ret;
पूर्ण


अटल u64
ath5k_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;

	वापस ath5k_hw_get_tsf64(ah);
पूर्ण


अटल व्योम
ath5k_set_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर, u64 tsf)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;

	ath5k_hw_set_tsf64(ah, tsf);
पूर्ण


अटल व्योम
ath5k_reset_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;

	/*
	 * in IBSS mode we need to update the beacon समयrs too.
	 * this will also reset the TSF अगर we call it with 0
	 */
	अगर (ah->opmode == NL80211_IFTYPE_ADHOC)
		ath5k_beacon_update_समयrs(ah, 0);
	अन्यथा
		ath5k_hw_reset_tsf(ah);
पूर्ण


अटल पूर्णांक
ath5k_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx, काष्ठा survey_info *survey)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	काष्ठा ath_cycle_counters *cc = &common->cc_survey;
	अचिन्हित पूर्णांक भाग = common->घड़ीrate * 1000;

	अगर (idx != 0)
		वापस -ENOENT;

	spin_lock_bh(&common->cc_lock);
	ath_hw_cycle_counters_update(common);
	अगर (cc->cycles > 0) अणु
		ah->survey.समय += cc->cycles / भाग;
		ah->survey.समय_busy += cc->rx_busy / भाग;
		ah->survey.समय_rx += cc->rx_frame / भाग;
		ah->survey.समय_प्रकारx += cc->tx_frame / भाग;
	पूर्ण
	स_रखो(cc, 0, माप(*cc));
	spin_unlock_bh(&common->cc_lock);

	स_नकल(survey, &ah->survey, माप(*survey));

	survey->channel = conf->chandef.chan;
	survey->noise = ah->ah_noise_न्यूनमान;
	survey->filled = SURVEY_INFO_NOISE_DBM |
			SURVEY_INFO_IN_USE |
			SURVEY_INFO_TIME |
			SURVEY_INFO_TIME_BUSY |
			SURVEY_INFO_TIME_RX |
			SURVEY_INFO_TIME_TX;

	वापस 0;
पूर्ण


/**
 * ath5k_set_coverage_class - Set IEEE 802.11 coverage class
 *
 * @hw: काष्ठा ieee80211_hw poपूर्णांकer
 * @coverage_class: IEEE 802.11 coverage class number
 *
 * Mac80211 callback. Sets slot समय, ACK समयout and CTS समयout क्रम given
 * coverage class. The values are persistent, they are restored after device
 * reset.
 */
अटल व्योम
ath5k_set_coverage_class(काष्ठा ieee80211_hw *hw, s16 coverage_class)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;

	mutex_lock(&ah->lock);
	ath5k_hw_set_coverage_class(ah, coverage_class);
	mutex_unlock(&ah->lock);
पूर्ण


अटल पूर्णांक
ath5k_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;

	अगर (tx_ant == 1 && rx_ant == 1)
		ath5k_hw_set_antenna_mode(ah, AR5K_ANTMODE_FIXED_A);
	अन्यथा अगर (tx_ant == 2 && rx_ant == 2)
		ath5k_hw_set_antenna_mode(ah, AR5K_ANTMODE_FIXED_B);
	अन्यथा अगर ((tx_ant & 3) == 3 && (rx_ant & 3) == 3)
		ath5k_hw_set_antenna_mode(ah, AR5K_ANTMODE_DEFAULT);
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण


अटल पूर्णांक
ath5k_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;

	चयन (ah->ah_ant_mode) अणु
	हाल AR5K_ANTMODE_FIXED_A:
		*tx_ant = 1; *rx_ant = 1; अवरोध;
	हाल AR5K_ANTMODE_FIXED_B:
		*tx_ant = 2; *rx_ant = 2; अवरोध;
	हाल AR5K_ANTMODE_DEFAULT:
		*tx_ant = 3; *rx_ant = 3; अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम ath5k_get_ringparam(काष्ठा ieee80211_hw *hw,
				u32 *tx, u32 *tx_max, u32 *rx, u32 *rx_max)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;

	*tx = ah->txqs[AR5K_TX_QUEUE_ID_DATA_MIN].txq_max;

	*tx_max = ATH5K_TXQ_LEN_MAX;
	*rx = *rx_max = ATH_RXBUF;
पूर्ण


अटल पूर्णांक ath5k_set_ringparam(काष्ठा ieee80211_hw *hw, u32 tx, u32 rx)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	u16 qnum;

	/* only support setting tx ring size क्रम now */
	अगर (rx != ATH_RXBUF)
		वापस -EINVAL;

	/* restrict tx ring size min/max */
	अगर (!tx || tx > ATH5K_TXQ_LEN_MAX)
		वापस -EINVAL;

	क्रम (qnum = 0; qnum < ARRAY_SIZE(ah->txqs); qnum++) अणु
		अगर (!ah->txqs[qnum].setup)
			जारी;
		अगर (ah->txqs[qnum].qnum < AR5K_TX_QUEUE_ID_DATA_MIN ||
		    ah->txqs[qnum].qnum > AR5K_TX_QUEUE_ID_DATA_MAX)
			जारी;

		ah->txqs[qnum].txq_max = tx;
		अगर (ah->txqs[qnum].txq_len >= ah->txqs[qnum].txq_max)
			ieee80211_stop_queue(hw, ah->txqs[qnum].qnum);
	पूर्ण

	वापस 0;
पूर्ण


स्थिर काष्ठा ieee80211_ops ath5k_hw_ops = अणु
	.tx			= ath5k_tx,
	.start			= ath5k_start,
	.stop			= ath5k_stop,
	.add_पूर्णांकerface		= ath5k_add_पूर्णांकerface,
	/* .change_पूर्णांकerface	= not implemented */
	.हटाओ_पूर्णांकerface	= ath5k_हटाओ_पूर्णांकerface,
	.config			= ath5k_config,
	.bss_info_changed	= ath5k_bss_info_changed,
	.prepare_multicast	= ath5k_prepare_multicast,
	.configure_filter	= ath5k_configure_filter,
	/* .set_tim		= not implemented */
	.set_key		= ath5k_set_key,
	/* .update_tkip_key	= not implemented */
	/* .hw_scan		= not implemented */
	.sw_scan_start		= ath5k_sw_scan_start,
	.sw_scan_complete	= ath5k_sw_scan_complete,
	.get_stats		= ath5k_get_stats,
	/* .set_frag_threshold	= not implemented */
	/* .set_rts_threshold	= not implemented */
	/* .sta_add		= not implemented */
	/* .sta_हटाओ		= not implemented */
	/* .sta_notअगरy		= not implemented */
	.conf_tx		= ath5k_conf_tx,
	.get_tsf		= ath5k_get_tsf,
	.set_tsf		= ath5k_set_tsf,
	.reset_tsf		= ath5k_reset_tsf,
	/* .tx_last_beacon	= not implemented */
	/* .ampdu_action	= not needed */
	.get_survey		= ath5k_get_survey,
	.set_coverage_class	= ath5k_set_coverage_class,
	/* .rfसमाप्त_poll		= not implemented */
	/* .flush		= not implemented */
	/* .channel_चयन	= not implemented */
	/* .napi_poll		= not implemented */
	.set_antenna		= ath5k_set_antenna,
	.get_antenna		= ath5k_get_antenna,
	.set_ringparam		= ath5k_set_ringparam,
	.get_ringparam		= ath5k_get_ringparam,
पूर्ण;
