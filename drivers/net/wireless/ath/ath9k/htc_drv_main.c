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

/*************/
/* Utilities */
/*************/

/* HACK Alert: Use 11NG क्रम 2.4, use 11NA क्रम 5 */
अटल क्रमागत htc_phymode ath9k_htc_get_curmode(काष्ठा ath9k_htc_priv *priv,
					      काष्ठा ath9k_channel *ichan)
अणु
	अगर (IS_CHAN_5GHZ(ichan))
		वापस HTC_MODE_11NA;

	वापस HTC_MODE_11NG;
पूर्ण

bool ath9k_htc_setघातer(काष्ठा ath9k_htc_priv *priv,
			क्रमागत ath9k_घातer_mode mode)
अणु
	bool ret;

	mutex_lock(&priv->htc_pm_lock);
	ret = ath9k_hw_setघातer(priv->ah, mode);
	mutex_unlock(&priv->htc_pm_lock);

	वापस ret;
पूर्ण

व्योम ath9k_htc_ps_wakeup(काष्ठा ath9k_htc_priv *priv)
अणु
	mutex_lock(&priv->htc_pm_lock);
	अगर (++priv->ps_usecount != 1)
		जाओ unlock;
	ath9k_hw_setघातer(priv->ah, ATH9K_PM_AWAKE);

unlock:
	mutex_unlock(&priv->htc_pm_lock);
पूर्ण

व्योम ath9k_htc_ps_restore(काष्ठा ath9k_htc_priv *priv)
अणु
	bool reset;

	mutex_lock(&priv->htc_pm_lock);
	अगर (--priv->ps_usecount != 0)
		जाओ unlock;

	अगर (priv->ps_idle) अणु
		ath9k_hw_setrxपात(priv->ah, true);
		ath9k_hw_stopdmarecv(priv->ah, &reset);
		ath9k_hw_setघातer(priv->ah, ATH9K_PM_FULL_SLEEP);
	पूर्ण अन्यथा अगर (priv->ps_enabled) अणु
		ath9k_hw_setघातer(priv->ah, ATH9K_PM_NETWORK_SLEEP);
	पूर्ण

unlock:
	mutex_unlock(&priv->htc_pm_lock);
पूर्ण

व्योम ath9k_ps_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath9k_htc_priv *priv =
		container_of(work, काष्ठा ath9k_htc_priv,
			     ps_work);
	ath9k_htc_setघातer(priv, ATH9K_PM_AWAKE);

	/* The chip wakes up after receiving the first beacon
	   जबतक network sleep is enabled. For the driver to
	   be in sync with the hw, set the chip to awake and
	   only then set it to sleep.
	 */
	ath9k_htc_setघातer(priv, ATH9K_PM_NETWORK_SLEEP);
पूर्ण

अटल व्योम ath9k_htc_vअगर_iter(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath9k_htc_priv *priv = data;
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;

	अगर ((vअगर->type == NL80211_IFTYPE_AP ||
	     vअगर->type == NL80211_IFTYPE_MESH_POINT) &&
	    bss_conf->enable_beacon) अणु
		priv->reconfig_beacon = true;
		priv->rearm_ani = true;
	पूर्ण

	अगर (bss_conf->assoc) अणु
		priv->rearm_ani = true;
		priv->reconfig_beacon = true;
	पूर्ण
पूर्ण

अटल व्योम ath9k_htc_vअगर_reconfig(काष्ठा ath9k_htc_priv *priv)
अणु
	priv->rearm_ani = false;
	priv->reconfig_beacon = false;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		priv->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		ath9k_htc_vअगर_iter, priv);
	अगर (priv->rearm_ani)
		ath9k_htc_start_ani(priv);

	अगर (priv->reconfig_beacon) अणु
		ath9k_htc_ps_wakeup(priv);
		ath9k_htc_beacon_reconfig(priv);
		ath9k_htc_ps_restore(priv);
	पूर्ण
पूर्ण

अटल व्योम ath9k_htc_bssid_iter(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath9k_vअगर_iter_data *iter_data = data;
	पूर्णांक i;

	अगर (iter_data->hw_macaddr != शून्य) अणु
		क्रम (i = 0; i < ETH_ALEN; i++)
			iter_data->mask[i] &= ~(iter_data->hw_macaddr[i] ^ mac[i]);
	पूर्ण अन्यथा अणु
		iter_data->hw_macaddr = mac;
	पूर्ण
पूर्ण

अटल व्योम ath9k_htc_set_mac_bssid_mask(काष्ठा ath9k_htc_priv *priv,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_vअगर_iter_data iter_data;

	/*
	 * Pick the MAC address of the first पूर्णांकerface as the new hardware
	 * MAC address. The hardware will use it together with the BSSID mask
	 * when matching addresses.
	 */
	iter_data.hw_macaddr = शून्य;
	eth_broadcast_addr(iter_data.mask);

	अगर (vअगर)
		ath9k_htc_bssid_iter(&iter_data, vअगर->addr, vअगर);

	/* Get list of all active MAC addresses */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		priv->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		ath9k_htc_bssid_iter, &iter_data);

	स_नकल(common->bssidmask, iter_data.mask, ETH_ALEN);

	अगर (iter_data.hw_macaddr)
		स_नकल(common->macaddr, iter_data.hw_macaddr, ETH_ALEN);

	ath_hw_setbssidmask(common);
पूर्ण

अटल व्योम ath9k_htc_set_opmode(काष्ठा ath9k_htc_priv *priv)
अणु
	अगर (priv->num_ibss_vअगर)
		priv->ah->opmode = NL80211_IFTYPE_ADHOC;
	अन्यथा अगर (priv->num_ap_vअगर)
		priv->ah->opmode = NL80211_IFTYPE_AP;
	अन्यथा अगर (priv->num_mbss_vअगर)
		priv->ah->opmode = NL80211_IFTYPE_MESH_POINT;
	अन्यथा
		priv->ah->opmode = NL80211_IFTYPE_STATION;

	ath9k_hw_setopmode(priv->ah);
पूर्ण

व्योम ath9k_htc_reset(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_channel *channel = priv->hw->conf.chandef.chan;
	काष्ठा ath9k_hw_cal_data *caldata = शून्य;
	क्रमागत htc_phymode mode;
	__be16 htc_mode;
	u8 cmd_rsp;
	पूर्णांक ret;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	ath9k_htc_stop_ani(priv);
	ieee80211_stop_queues(priv->hw);

	del_समयr_sync(&priv->tx.cleanup_समयr);
	ath9k_htc_tx_drain(priv);

	WMI_CMD(WMI_DISABLE_INTR_CMDID);
	WMI_CMD(WMI_DRAIN_TXQ_ALL_CMDID);
	WMI_CMD(WMI_STOP_RECV_CMDID);

	ath9k_wmi_event_drain(priv);

	caldata = &priv->caldata;
	ret = ath9k_hw_reset(ah, ah->curchan, caldata, false);
	अगर (ret) अणु
		ath_err(common,
			"Unable to reset device (%u Mhz) reset status %d\n",
			channel->center_freq, ret);
	पूर्ण

	ath9k_cmn_update_txघात(ah, priv->curtxघात, priv->txघातlimit,
			       &priv->curtxघात);

	WMI_CMD(WMI_START_RECV_CMDID);
	ath9k_host_rx_init(priv);

	mode = ath9k_htc_get_curmode(priv, ah->curchan);
	htc_mode = cpu_to_be16(mode);
	WMI_CMD_BUF(WMI_SET_MODE_CMDID, &htc_mode);

	WMI_CMD(WMI_ENABLE_INTR_CMDID);
	htc_start(priv->htc);
	ath9k_htc_vअगर_reconfig(priv);
	ieee80211_wake_queues(priv->hw);

	mod_समयr(&priv->tx.cleanup_समयr,
		  jअगरfies + msecs_to_jअगरfies(ATH9K_HTC_TX_CLEANUP_INTERVAL));

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ath9k_htc_set_channel(काष्ठा ath9k_htc_priv *priv,
				 काष्ठा ieee80211_hw *hw,
				 काष्ठा ath9k_channel *hchan)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_conf *conf = &common->hw->conf;
	bool fastcc;
	काष्ठा ieee80211_channel *channel = hw->conf.chandef.chan;
	काष्ठा ath9k_hw_cal_data *caldata;
	क्रमागत htc_phymode mode;
	__be16 htc_mode;
	u8 cmd_rsp;
	पूर्णांक ret;

	अगर (test_bit(ATH_OP_INVALID, &common->op_flags))
		वापस -EIO;

	fastcc = !!(hw->conf.flags & IEEE80211_CONF_OFFCHANNEL);

	ath9k_htc_ps_wakeup(priv);

	ath9k_htc_stop_ani(priv);
	del_समयr_sync(&priv->tx.cleanup_समयr);
	ath9k_htc_tx_drain(priv);

	WMI_CMD(WMI_DISABLE_INTR_CMDID);
	WMI_CMD(WMI_DRAIN_TXQ_ALL_CMDID);
	WMI_CMD(WMI_STOP_RECV_CMDID);

	ath9k_wmi_event_drain(priv);

	ath_dbg(common, CONFIG,
		"(%u MHz) -> (%u MHz), HT: %d, HT40: %d fastcc: %d\n",
		priv->ah->curchan->channel,
		channel->center_freq, conf_is_ht(conf), conf_is_ht40(conf),
		fastcc);
	caldata = fastcc ? शून्य : &priv->caldata;
	ret = ath9k_hw_reset(ah, hchan, caldata, fastcc);
	अगर (ret) अणु
		ath_err(common,
			"Unable to reset channel (%u Mhz) reset status %d\n",
			channel->center_freq, ret);
		जाओ err;
	पूर्ण

	ath9k_cmn_update_txघात(ah, priv->curtxघात, priv->txघातlimit,
			       &priv->curtxघात);

	WMI_CMD(WMI_START_RECV_CMDID);
	अगर (ret)
		जाओ err;

	ath9k_host_rx_init(priv);

	mode = ath9k_htc_get_curmode(priv, hchan);
	htc_mode = cpu_to_be16(mode);
	WMI_CMD_BUF(WMI_SET_MODE_CMDID, &htc_mode);
	अगर (ret)
		जाओ err;

	WMI_CMD(WMI_ENABLE_INTR_CMDID);
	अगर (ret)
		जाओ err;

	htc_start(priv->htc);

	अगर (!test_bit(ATH_OP_SCANNING, &common->op_flags) &&
	    !(hw->conf.flags & IEEE80211_CONF_OFFCHANNEL))
		ath9k_htc_vअगर_reconfig(priv);

	mod_समयr(&priv->tx.cleanup_समयr,
		  jअगरfies + msecs_to_jअगरfies(ATH9K_HTC_TX_CLEANUP_INTERVAL));

	/* perक्रमm spectral scan अगर requested. */
	अगर (test_bit(ATH_OP_SCANNING, &common->op_flags) &&
		     priv->spec_priv.spectral_mode == SPECTRAL_CHANSCAN)
		ath9k_cmn_spectral_scan_trigger(common, &priv->spec_priv);
err:
	ath9k_htc_ps_restore(priv);
	वापस ret;
पूर्ण

/*
 * Monitor mode handling is a tad complicated because the firmware requires
 * an पूर्णांकerface to be created exclusively, जबतक mac80211 करोesn't associate
 * an पूर्णांकerface with the mode.
 *
 * So, क्रम now, only one monitor पूर्णांकerface can be configured.
 */
अटल व्योम __ath9k_htc_हटाओ_monitor_पूर्णांकerface(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_target_vअगर hvअगर;
	पूर्णांक ret = 0;
	u8 cmd_rsp;

	स_रखो(&hvअगर, 0, माप(काष्ठा ath9k_htc_target_vअगर));
	स_नकल(&hvअगर.myaddr, common->macaddr, ETH_ALEN);
	hvअगर.index = priv->mon_vअगर_idx;
	WMI_CMD_BUF(WMI_VAP_REMOVE_CMDID, &hvअगर);
	अगर (ret) अणु
		ath_err(common, "Unable to remove monitor interface at idx: %d\n",
			priv->mon_vअगर_idx);
	पूर्ण

	priv->nvअगरs--;
	priv->vअगर_slot &= ~(1 << priv->mon_vअगर_idx);
पूर्ण

अटल पूर्णांक ath9k_htc_add_monitor_पूर्णांकerface(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_target_vअगर hvअगर;
	काष्ठा ath9k_htc_target_sta tsta;
	पूर्णांक ret = 0, sta_idx;
	u8 cmd_rsp;

	अगर ((priv->nvअगरs >= ATH9K_HTC_MAX_VIF) ||
	    (priv->nstations >= ATH9K_HTC_MAX_STA)) अणु
		ret = -ENOBUFS;
		जाओ err_vअगर;
	पूर्ण

	sta_idx = ffz(priv->sta_slot);
	अगर ((sta_idx < 0) || (sta_idx > ATH9K_HTC_MAX_STA)) अणु
		ret = -ENOBUFS;
		जाओ err_vअगर;
	पूर्ण

	/*
	 * Add an पूर्णांकerface.
	 */
	स_रखो(&hvअगर, 0, माप(काष्ठा ath9k_htc_target_vअगर));
	स_नकल(&hvअगर.myaddr, common->macaddr, ETH_ALEN);

	hvअगर.opmode = HTC_M_MONITOR;
	hvअगर.index = ffz(priv->vअगर_slot);

	WMI_CMD_BUF(WMI_VAP_CREATE_CMDID, &hvअगर);
	अगर (ret)
		जाओ err_vअगर;

	/*
	 * Assign the monitor पूर्णांकerface index as a special हाल here.
	 * This is needed when the पूर्णांकerface is brought करोwn.
	 */
	priv->mon_vअगर_idx = hvअगर.index;
	priv->vअगर_slot |= (1 << hvअगर.index);

	/*
	 * Set the hardware mode to monitor only अगर there are no
	 * other पूर्णांकerfaces.
	 */
	अगर (!priv->nvअगरs)
		priv->ah->opmode = NL80211_IFTYPE_MONITOR;

	priv->nvअगरs++;

	/*
	 * Associate a station with the पूर्णांकerface क्रम packet injection.
	 */
	स_रखो(&tsta, 0, माप(काष्ठा ath9k_htc_target_sta));

	स_नकल(&tsta.macaddr, common->macaddr, ETH_ALEN);

	tsta.is_vअगर_sta = 1;
	tsta.sta_index = sta_idx;
	tsta.vअगर_index = hvअगर.index;
	tsta.maxampdu = cpu_to_be16(0xffff);

	WMI_CMD_BUF(WMI_NODE_CREATE_CMDID, &tsta);
	अगर (ret) अणु
		ath_err(common, "Unable to add station entry for monitor mode\n");
		जाओ err_sta;
	पूर्ण

	priv->sta_slot |= (1 << sta_idx);
	priv->nstations++;
	priv->vअगर_sta_pos[priv->mon_vअगर_idx] = sta_idx;
	priv->ah->is_monitoring = true;

	ath_dbg(common, CONFIG,
		"Attached a monitor interface at idx: %d, sta idx: %d\n",
		priv->mon_vअगर_idx, sta_idx);

	वापस 0;

err_sta:
	/*
	 * Remove the पूर्णांकerface from the target.
	 */
	__ath9k_htc_हटाओ_monitor_पूर्णांकerface(priv);
err_vअगर:
	ath_dbg(common, FATAL, "Unable to attach a monitor interface\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ath9k_htc_हटाओ_monitor_पूर्णांकerface(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	पूर्णांक ret = 0;
	u8 cmd_rsp, sta_idx;

	__ath9k_htc_हटाओ_monitor_पूर्णांकerface(priv);

	sta_idx = priv->vअगर_sta_pos[priv->mon_vअगर_idx];

	WMI_CMD_BUF(WMI_NODE_REMOVE_CMDID, &sta_idx);
	अगर (ret) अणु
		ath_err(common, "Unable to remove station entry for monitor mode\n");
		वापस ret;
	पूर्ण

	priv->sta_slot &= ~(1 << sta_idx);
	priv->nstations--;
	priv->ah->is_monitoring = false;

	ath_dbg(common, CONFIG,
		"Removed a monitor interface at idx: %d, sta idx: %d\n",
		priv->mon_vअगर_idx, sta_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_htc_add_station(काष्ठा ath9k_htc_priv *priv,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_target_sta tsta;
	काष्ठा ath9k_htc_vअगर *avp = (काष्ठा ath9k_htc_vअगर *) vअगर->drv_priv;
	काष्ठा ath9k_htc_sta *ista;
	पूर्णांक ret, sta_idx;
	u8 cmd_rsp;
	u16 maxampdu;

	अगर (priv->nstations >= ATH9K_HTC_MAX_STA)
		वापस -ENOBUFS;

	sta_idx = ffz(priv->sta_slot);
	अगर ((sta_idx < 0) || (sta_idx > ATH9K_HTC_MAX_STA))
		वापस -ENOBUFS;

	स_रखो(&tsta, 0, माप(काष्ठा ath9k_htc_target_sta));

	अगर (sta) अणु
		ista = (काष्ठा ath9k_htc_sta *) sta->drv_priv;
		स_नकल(&tsta.macaddr, sta->addr, ETH_ALEN);
		स_नकल(&tsta.bssid, common->curbssid, ETH_ALEN);
		ista->index = sta_idx;
		tsta.is_vअगर_sta = 0;
		maxampdu = 1 << (IEEE80211_HT_MAX_AMPDU_FACTOR +
				 sta->ht_cap.ampdu_factor);
		tsta.maxampdu = cpu_to_be16(maxampdu);
	पूर्ण अन्यथा अणु
		स_नकल(&tsta.macaddr, vअगर->addr, ETH_ALEN);
		tsta.is_vअगर_sta = 1;
		tsta.maxampdu = cpu_to_be16(0xffff);
	पूर्ण

	tsta.sta_index = sta_idx;
	tsta.vअगर_index = avp->index;

	WMI_CMD_BUF(WMI_NODE_CREATE_CMDID, &tsta);
	अगर (ret) अणु
		अगर (sta)
			ath_err(common,
				"Unable to add station entry for: %pM\n",
				sta->addr);
		वापस ret;
	पूर्ण

	अगर (sta) अणु
		ath_dbg(common, CONFIG,
			"Added a station entry for: %pM (idx: %d)\n",
			sta->addr, tsta.sta_index);
	पूर्ण अन्यथा अणु
		ath_dbg(common, CONFIG,
			"Added a station entry for VIF %d (idx: %d)\n",
			avp->index, tsta.sta_index);
	पूर्ण

	priv->sta_slot |= (1 << sta_idx);
	priv->nstations++;
	अगर (!sta)
		priv->vअगर_sta_pos[avp->index] = sta_idx;

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_htc_हटाओ_station(काष्ठा ath9k_htc_priv *priv,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_vअगर *avp = (काष्ठा ath9k_htc_vअगर *) vअगर->drv_priv;
	काष्ठा ath9k_htc_sta *ista;
	पूर्णांक ret;
	u8 cmd_rsp, sta_idx;

	अगर (sta) अणु
		ista = (काष्ठा ath9k_htc_sta *) sta->drv_priv;
		sta_idx = ista->index;
	पूर्ण अन्यथा अणु
		sta_idx = priv->vअगर_sta_pos[avp->index];
	पूर्ण

	WMI_CMD_BUF(WMI_NODE_REMOVE_CMDID, &sta_idx);
	अगर (ret) अणु
		अगर (sta)
			ath_err(common,
				"Unable to remove station entry for: %pM\n",
				sta->addr);
		वापस ret;
	पूर्ण

	अगर (sta) अणु
		ath_dbg(common, CONFIG,
			"Removed a station entry for: %pM (idx: %d)\n",
			sta->addr, sta_idx);
	पूर्ण अन्यथा अणु
		ath_dbg(common, CONFIG,
			"Removed a station entry for VIF %d (idx: %d)\n",
			avp->index, sta_idx);
	पूर्ण

	priv->sta_slot &= ~(1 << sta_idx);
	priv->nstations--;

	वापस 0;
पूर्ण

पूर्णांक ath9k_htc_update_cap_target(काष्ठा ath9k_htc_priv *priv,
				u8 enable_coex)
अणु
	काष्ठा ath9k_htc_cap_target tcap;
	पूर्णांक ret;
	u8 cmd_rsp;

	स_रखो(&tcap, 0, माप(काष्ठा ath9k_htc_cap_target));

	tcap.ampdu_limit = cpu_to_be32(0xffff);
	tcap.ampdu_subframes = 0xff;
	tcap.enable_coex = enable_coex;
	tcap.tx_chainmask = priv->ah->caps.tx_chainmask;

	WMI_CMD_BUF(WMI_TARGET_IC_UPDATE_CMDID, &tcap);

	वापस ret;
पूर्ण

अटल व्योम ath9k_htc_setup_rate(काष्ठा ath9k_htc_priv *priv,
				 काष्ठा ieee80211_sta *sta,
				 काष्ठा ath9k_htc_target_rate *trate)
अणु
	काष्ठा ath9k_htc_sta *ista = (काष्ठा ath9k_htc_sta *) sta->drv_priv;
	काष्ठा ieee80211_supported_band *sband;
	u32 caps = 0;
	पूर्णांक i, j;

	sband = priv->hw->wiphy->bands[priv->hw->conf.chandef.chan->band];

	क्रम (i = 0, j = 0; i < sband->n_bitrates; i++) अणु
		अगर (sta->supp_rates[sband->band] & BIT(i)) अणु
			trate->rates.legacy_rates.rs_rates[j]
				= (sband->bitrates[i].bitrate * 2) / 10;
			j++;
		पूर्ण
	पूर्ण
	trate->rates.legacy_rates.rs_nrates = j;

	अगर (sta->ht_cap.ht_supported) अणु
		क्रम (i = 0, j = 0; i < 77; i++) अणु
			अगर (sta->ht_cap.mcs.rx_mask[i/8] & (1<<(i%8)))
				trate->rates.ht_rates.rs_rates[j++] = i;
			अगर (j == ATH_HTC_RATE_MAX)
				अवरोध;
		पूर्ण
		trate->rates.ht_rates.rs_nrates = j;

		caps = WLAN_RC_HT_FLAG;
		अगर (sta->ht_cap.cap & IEEE80211_HT_CAP_RX_STBC)
			caps |= ATH_RC_TX_STBC_FLAG;
		अगर (sta->ht_cap.mcs.rx_mask[1])
			caps |= WLAN_RC_DS_FLAG;
		अगर ((sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) &&
		     (conf_is_ht40(&priv->hw->conf)))
			caps |= WLAN_RC_40_FLAG;
		अगर (conf_is_ht40(&priv->hw->conf) &&
		    (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40))
			caps |= WLAN_RC_SGI_FLAG;
		अन्यथा अगर (conf_is_ht20(&priv->hw->conf) &&
			 (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20))
			caps |= WLAN_RC_SGI_FLAG;
	पूर्ण

	trate->sta_index = ista->index;
	trate->isnew = 1;
	trate->capflags = cpu_to_be32(caps);
पूर्ण

अटल पूर्णांक ath9k_htc_send_rate_cmd(काष्ठा ath9k_htc_priv *priv,
				    काष्ठा ath9k_htc_target_rate *trate)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	पूर्णांक ret;
	u8 cmd_rsp;

	WMI_CMD_BUF(WMI_RC_RATE_UPDATE_CMDID, trate);
	अगर (ret) अणु
		ath_err(common,
			"Unable to initialize Rate information on target\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ath9k_htc_init_rate(काष्ठा ath9k_htc_priv *priv,
				काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_target_rate trate;
	पूर्णांक ret;

	स_रखो(&trate, 0, माप(काष्ठा ath9k_htc_target_rate));
	ath9k_htc_setup_rate(priv, sta, &trate);
	ret = ath9k_htc_send_rate_cmd(priv, &trate);
	अगर (!ret)
		ath_dbg(common, CONFIG,
			"Updated target sta: %pM, rate caps: 0x%X\n",
			sta->addr, be32_to_cpu(trate.capflags));
पूर्ण

अटल व्योम ath9k_htc_update_rate(काष्ठा ath9k_htc_priv *priv,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_bss_conf *bss_conf)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_target_rate trate;
	काष्ठा ieee80211_sta *sta;
	पूर्णांक ret;

	स_रखो(&trate, 0, माप(काष्ठा ath9k_htc_target_rate));

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(vअगर, bss_conf->bssid);
	अगर (!sta) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	ath9k_htc_setup_rate(priv, sta, &trate);
	rcu_पढ़ो_unlock();

	ret = ath9k_htc_send_rate_cmd(priv, &trate);
	अगर (!ret)
		ath_dbg(common, CONFIG,
			"Updated target sta: %pM, rate caps: 0x%X\n",
			bss_conf->bssid, be32_to_cpu(trate.capflags));
पूर्ण

अटल पूर्णांक ath9k_htc_tx_aggr_oper(काष्ठा ath9k_htc_priv *priv,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_sta *sta,
				  क्रमागत ieee80211_ampdu_mlme_action action,
				  u16 tid)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_target_aggr aggr;
	काष्ठा ath9k_htc_sta *ista;
	पूर्णांक ret = 0;
	u8 cmd_rsp;

	अगर (tid >= ATH9K_HTC_MAX_TID)
		वापस -EINVAL;

	स_रखो(&aggr, 0, माप(काष्ठा ath9k_htc_target_aggr));
	ista = (काष्ठा ath9k_htc_sta *) sta->drv_priv;

	aggr.sta_index = ista->index;
	aggr.tidno = tid & 0xf;
	aggr.aggr_enable = (action == IEEE80211_AMPDU_TX_START) ? true : false;

	WMI_CMD_BUF(WMI_TX_AGGR_ENABLE_CMDID, &aggr);
	अगर (ret)
		ath_dbg(common, CONFIG,
			"Unable to %s TX aggregation for (%pM, %d)\n",
			(aggr.aggr_enable) ? "start" : "stop", sta->addr, tid);
	अन्यथा
		ath_dbg(common, CONFIG,
			"%s TX aggregation for (%pM, %d)\n",
			(aggr.aggr_enable) ? "Starting" : "Stopping",
			sta->addr, tid);

	spin_lock_bh(&priv->tx.tx_lock);
	ista->tid_state[tid] = (aggr.aggr_enable && !ret) ? AGGR_START : AGGR_STOP;
	spin_unlock_bh(&priv->tx.tx_lock);

	वापस ret;
पूर्ण

/*******/
/* ANI */
/*******/

व्योम ath9k_htc_start_ani(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	अचिन्हित दीर्घ बारtamp = jअगरfies_to_msecs(jअगरfies);

	common->ani.दीर्घcal_समयr = बारtamp;
	common->ani.लघुcal_समयr = बारtamp;
	common->ani.checkani_समयr = बारtamp;

	set_bit(ATH_OP_ANI_RUN, &common->op_flags);

	ieee80211_queue_delayed_work(common->hw, &priv->ani_work,
				     msecs_to_jअगरfies(ATH_ANI_POLLINTERVAL));
पूर्ण

व्योम ath9k_htc_stop_ani(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	cancel_delayed_work_sync(&priv->ani_work);
	clear_bit(ATH_OP_ANI_RUN, &common->op_flags);
पूर्ण

व्योम ath9k_htc_ani_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath9k_htc_priv *priv =
		container_of(work, काष्ठा ath9k_htc_priv, ani_work.work);
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	bool दीर्घcal = false;
	bool लघुcal = false;
	bool anअगरlag = false;
	अचिन्हित पूर्णांक बारtamp = jअगरfies_to_msecs(jअगरfies);
	u32 cal_पूर्णांकerval, लघु_cal_पूर्णांकerval;

	लघु_cal_पूर्णांकerval = (ah->opmode == NL80211_IFTYPE_AP) ?
		ATH_AP_SHORT_CALINTERVAL : ATH_STA_SHORT_CALINTERVAL;

	/* Only calibrate अगर awake */
	अगर (ah->घातer_mode != ATH9K_PM_AWAKE)
		जाओ set_समयr;

	/* Long calibration runs independently of लघु calibration. */
	अगर ((बारtamp - common->ani.दीर्घcal_समयr) >= ATH_LONG_CALINTERVAL) अणु
		दीर्घcal = true;
		ath_dbg(common, ANI, "longcal @%lu\n", jअगरfies);
		common->ani.दीर्घcal_समयr = बारtamp;
	पूर्ण

	/*
	 * Short calibration applies only जबतक calकरोne
	 * is false or -ETIMEDOUT
	 */
	अगर (common->ani.calकरोne <= 0) अणु
		अगर ((बारtamp - common->ani.लघुcal_समयr) >=
		    लघु_cal_पूर्णांकerval) अणु
			लघुcal = true;
			ath_dbg(common, ANI, "shortcal @%lu\n", jअगरfies);
			common->ani.लघुcal_समयr = बारtamp;
			common->ani.resetcal_समयr = बारtamp;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((बारtamp - common->ani.resetcal_समयr) >=
		    ATH_RESTART_CALINTERVAL) अणु
			common->ani.calकरोne = ath9k_hw_reset_calvalid(ah);
			अगर (common->ani.calकरोne)
				common->ani.resetcal_समयr = बारtamp;
		पूर्ण
	पूर्ण

	/* Verअगरy whether we must check ANI */
	अगर ((बारtamp - common->ani.checkani_समयr) >= ATH_ANI_POLLINTERVAL) अणु
		anअगरlag = true;
		common->ani.checkani_समयr = बारtamp;
	पूर्ण

	/* Skip all processing अगर there's nothing to करो. */
	अगर (दीर्घcal || लघुcal || anअगरlag) अणु

		ath9k_htc_ps_wakeup(priv);

		/* Call ANI routine अगर necessary */
		अगर (anअगरlag)
			ath9k_hw_ani_monitor(ah, ah->curchan);

		/* Perक्रमm calibration अगर necessary */
		अगर (दीर्घcal || लघुcal)
			common->ani.calकरोne =
				ath9k_hw_calibrate(ah, ah->curchan,
						ah->rxchainmask, दीर्घcal) > 0;

		ath9k_htc_ps_restore(priv);
	पूर्ण

set_समयr:
	/*
	* Set समयr पूर्णांकerval based on previous results.
	* The पूर्णांकerval must be the लघुest necessary to satisfy ANI,
	* लघु calibration and दीर्घ calibration.
	*/
	cal_पूर्णांकerval = ATH_LONG_CALINTERVAL;
	cal_पूर्णांकerval = min(cal_पूर्णांकerval, (u32)ATH_ANI_POLLINTERVAL);
	/*
	 * Short calibration applies only जबतक calकरोne
	 * is false or -ETIMEDOUT
	 */
	अगर (common->ani.calकरोne <= 0)
		cal_पूर्णांकerval = min(cal_पूर्णांकerval, (u32)लघु_cal_पूर्णांकerval);

	ieee80211_queue_delayed_work(common->hw, &priv->ani_work,
				     msecs_to_jअगरfies(cal_पूर्णांकerval));
पूर्ण

/**********************/
/* mac80211 Callbacks */
/**********************/

अटल व्योम ath9k_htc_tx(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_tx_control *control,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	पूर्णांक padpos, padsize, ret, slot;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;

	/* Add the padding after the header अगर this is not alपढ़ोy करोne */
	padpos = ieee80211_hdrlen(hdr->frame_control);
	padsize = padpos & 3;
	अगर (padsize && skb->len > padpos) अणु
		अगर (skb_headroom(skb) < padsize) अणु
			ath_dbg(common, XMIT, "No room for padding\n");
			जाओ fail_tx;
		पूर्ण
		skb_push(skb, padsize);
		स_हटाओ(skb->data, skb->data + padsize, padpos);
	पूर्ण

	slot = ath9k_htc_tx_get_slot(priv);
	अगर (slot < 0) अणु
		ath_dbg(common, XMIT, "No free TX slot\n");
		जाओ fail_tx;
	पूर्ण

	ret = ath9k_htc_tx_start(priv, control->sta, skb, slot, false);
	अगर (ret != 0) अणु
		ath_dbg(common, XMIT, "Tx failed\n");
		जाओ clear_slot;
	पूर्ण

	ath9k_htc_check_stop_queues(priv);

	वापस;

clear_slot:
	ath9k_htc_tx_clear_slot(priv, slot);
fail_tx:
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल पूर्णांक ath9k_htc_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_channel *curchan = hw->conf.chandef.chan;
	काष्ठा ath9k_channel *init_channel;
	पूर्णांक ret = 0;
	क्रमागत htc_phymode mode;
	__be16 htc_mode;
	u8 cmd_rsp;

	mutex_lock(&priv->mutex);

	ath_dbg(common, CONFIG,
		"Starting driver with initial channel: %d MHz\n",
		curchan->center_freq);

	/* Ensure that HW is awake beक्रमe flushing RX */
	ath9k_htc_setघातer(priv, ATH9K_PM_AWAKE);
	WMI_CMD(WMI_FLUSH_RECV_CMDID);

	/* setup initial channel */
	init_channel = ath9k_cmn_get_channel(hw, ah, &hw->conf.chandef);

	ret = ath9k_hw_reset(ah, init_channel, ah->caldata, false);
	अगर (ret) अणु
		ath_err(common,
			"Unable to reset hardware; reset status %d (freq %u MHz)\n",
			ret, curchan->center_freq);
		mutex_unlock(&priv->mutex);
		वापस ret;
	पूर्ण

	ath9k_cmn_update_txघात(ah, priv->curtxघात, priv->txघातlimit,
			       &priv->curtxघात);

	mode = ath9k_htc_get_curmode(priv, init_channel);
	htc_mode = cpu_to_be16(mode);
	WMI_CMD_BUF(WMI_SET_MODE_CMDID, &htc_mode);
	WMI_CMD(WMI_ATH_INIT_CMDID);
	WMI_CMD(WMI_START_RECV_CMDID);

	ath9k_host_rx_init(priv);

	ret = ath9k_htc_update_cap_target(priv, 0);
	अगर (ret)
		ath_dbg(common, CONFIG,
			"Failed to update capability in target\n");

	clear_bit(ATH_OP_INVALID, &common->op_flags);
	htc_start(priv->htc);

	spin_lock_bh(&priv->tx.tx_lock);
	priv->tx.flags &= ~ATH9K_HTC_OP_TX_QUEUES_STOP;
	spin_unlock_bh(&priv->tx.tx_lock);

	ieee80211_wake_queues(hw);

	mod_समयr(&priv->tx.cleanup_समयr,
		  jअगरfies + msecs_to_jअगरfies(ATH9K_HTC_TX_CLEANUP_INTERVAL));

	ath9k_htc_start_btcoex(priv);

	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल व्योम ath9k_htc_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक ret __attribute__ ((unused));
	u8 cmd_rsp;

	mutex_lock(&priv->mutex);

	अगर (test_bit(ATH_OP_INVALID, &common->op_flags)) अणु
		ath_dbg(common, ANY, "Device not present\n");
		mutex_unlock(&priv->mutex);
		वापस;
	पूर्ण

	ath9k_htc_ps_wakeup(priv);

	WMI_CMD(WMI_DISABLE_INTR_CMDID);
	WMI_CMD(WMI_DRAIN_TXQ_ALL_CMDID);
	WMI_CMD(WMI_STOP_RECV_CMDID);

	tasklet_समाप्त(&priv->rx_tasklet);

	del_समयr_sync(&priv->tx.cleanup_समयr);
	ath9k_htc_tx_drain(priv);
	ath9k_wmi_event_drain(priv);

	mutex_unlock(&priv->mutex);

	/* Cancel all the running समयrs/work .. */
	cancel_work_sync(&priv->fatal_work);
	cancel_work_sync(&priv->ps_work);

#अगर_घोषित CONFIG_MAC80211_LEDS
	cancel_work_sync(&priv->led_work);
#पूर्ण_अगर
	ath9k_htc_stop_ani(priv);

	mutex_lock(&priv->mutex);

	ath9k_htc_stop_btcoex(priv);

	/* Remove a monitor पूर्णांकerface अगर it's present. */
	अगर (priv->ah->is_monitoring)
		ath9k_htc_हटाओ_monitor_पूर्णांकerface(priv);

	ath9k_hw_phy_disable(ah);
	ath9k_hw_disable(ah);
	ath9k_htc_ps_restore(priv);
	ath9k_htc_setघातer(priv, ATH9K_PM_FULL_SLEEP);

	set_bit(ATH_OP_INVALID, &common->op_flags);

	ath_dbg(common, CONFIG, "Driver halt\n");
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ath9k_htc_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath9k_htc_vअगर *avp = (व्योम *)vअगर->drv_priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_target_vअगर hvअगर;
	पूर्णांक ret = 0;
	u8 cmd_rsp;

	mutex_lock(&priv->mutex);

	ath9k_htc_ps_wakeup(priv);
	स_रखो(&hvअगर, 0, माप(काष्ठा ath9k_htc_target_vअगर));
	स_नकल(&hvअगर.myaddr, vअगर->addr, ETH_ALEN);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		hvअगर.opmode = HTC_M_STA;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		hvअगर.opmode = HTC_M_IBSS;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		hvअगर.opmode = HTC_M_HOSTAP;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		hvअगर.opmode = HTC_M_WDS;	/* बंद enough */
		अवरोध;
	शेष:
		ath_err(common,
			"Interface type %d not yet supported\n", vअगर->type);
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* Index starts from zero on the target */
	avp->index = hvअगर.index = ffz(priv->vअगर_slot);
	hvअगर.rtsthreshold = cpu_to_be16(2304);
	WMI_CMD_BUF(WMI_VAP_CREATE_CMDID, &hvअगर);
	अगर (ret)
		जाओ out;

	/*
	 * We need a node in target to tx mgmt frames
	 * beक्रमe association.
	 */
	ret = ath9k_htc_add_station(priv, vअगर, शून्य);
	अगर (ret) अणु
		WMI_CMD_BUF(WMI_VAP_REMOVE_CMDID, &hvअगर);
		जाओ out;
	पूर्ण

	ath9k_htc_set_mac_bssid_mask(priv, vअगर);

	priv->vअगर_slot |= (1 << avp->index);
	priv->nvअगरs++;

	INC_VIF(priv, vअगर->type);

	अगर ((vअगर->type == NL80211_IFTYPE_AP) ||
	    (vअगर->type == NL80211_IFTYPE_MESH_POINT) ||
	    (vअगर->type == NL80211_IFTYPE_ADHOC))
		ath9k_htc_assign_bslot(priv, vअगर);

	ath9k_htc_set_opmode(priv);

	अगर ((priv->ah->opmode == NL80211_IFTYPE_AP) &&
	    !test_bit(ATH_OP_ANI_RUN, &common->op_flags)) अणु
		ath9k_hw_set_tsfadjust(priv->ah, true);
		ath9k_htc_start_ani(priv);
	पूर्ण

	ath_dbg(common, CONFIG, "Attach a VIF of type: %d at idx: %d\n",
		vअगर->type, avp->index);

out:
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल व्योम ath9k_htc_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_vअगर *avp = (व्योम *)vअगर->drv_priv;
	काष्ठा ath9k_htc_target_vअगर hvअगर;
	पूर्णांक ret = 0;
	u8 cmd_rsp;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	स_रखो(&hvअगर, 0, माप(काष्ठा ath9k_htc_target_vअगर));
	स_नकल(&hvअगर.myaddr, vअगर->addr, ETH_ALEN);
	hvअगर.index = avp->index;
	WMI_CMD_BUF(WMI_VAP_REMOVE_CMDID, &hvअगर);
	अगर (ret) अणु
		ath_err(common, "Unable to remove interface at idx: %d\n",
			avp->index);
	पूर्ण
	priv->nvअगरs--;
	priv->vअगर_slot &= ~(1 << avp->index);

	अगर (priv->csa_vअगर == vअगर)
		priv->csa_vअगर = शून्य;

	ath9k_htc_हटाओ_station(priv, vअगर, शून्य);

	DEC_VIF(priv, vअगर->type);

	अगर ((vअगर->type == NL80211_IFTYPE_AP) ||
	     vअगर->type == NL80211_IFTYPE_MESH_POINT ||
	    (vअगर->type == NL80211_IFTYPE_ADHOC))
		ath9k_htc_हटाओ_bslot(priv, vअगर);

	ath9k_htc_set_opmode(priv);

	ath9k_htc_set_mac_bssid_mask(priv, vअगर);

	/*
	 * Stop ANI only अगर there are no associated station पूर्णांकerfaces.
	 */
	अगर ((vअगर->type == NL80211_IFTYPE_AP) && (priv->num_ap_vअगर == 0)) अणु
		priv->rearm_ani = false;
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			priv->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
			ath9k_htc_vअगर_iter, priv);
		अगर (!priv->rearm_ani)
			ath9k_htc_stop_ani(priv);
	पूर्ण

	ath_dbg(common, CONFIG, "Detach Interface at idx: %d\n", avp->index);

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ath9k_htc_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ieee80211_conf *conf = &hw->conf;
	bool chip_reset = false;
	पूर्णांक ret = 0;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	अगर (changed & IEEE80211_CONF_CHANGE_IDLE) अणु
		mutex_lock(&priv->htc_pm_lock);

		priv->ps_idle = !!(conf->flags & IEEE80211_CONF_IDLE);
		अगर (!priv->ps_idle)
			chip_reset = true;

		mutex_unlock(&priv->htc_pm_lock);
	पूर्ण

	/*
	 * Monitor पूर्णांकerface should be added beक्रमe
	 * IEEE80211_CONF_CHANGE_CHANNEL is handled.
	 */
	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		अगर ((conf->flags & IEEE80211_CONF_MONITOR) &&
		    !priv->ah->is_monitoring)
			ath9k_htc_add_monitor_पूर्णांकerface(priv);
		अन्यथा अगर (priv->ah->is_monitoring)
			ath9k_htc_हटाओ_monitor_पूर्णांकerface(priv);
	पूर्ण

	अगर ((changed & IEEE80211_CONF_CHANGE_CHANNEL) || chip_reset) अणु
		काष्ठा ieee80211_channel *curchan = hw->conf.chandef.chan;
		पूर्णांक pos = curchan->hw_value;

		ath_dbg(common, CONFIG, "Set channel: %d MHz\n",
			curchan->center_freq);

		ath9k_cmn_get_channel(hw, priv->ah, &hw->conf.chandef);
		अगर (ath9k_htc_set_channel(priv, hw, &priv->ah->channels[pos]) < 0) अणु
			ath_err(common, "Unable to set channel\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_PS) अणु
		अगर (conf->flags & IEEE80211_CONF_PS) अणु
			ath9k_htc_setघातer(priv, ATH9K_PM_NETWORK_SLEEP);
			priv->ps_enabled = true;
		पूर्ण अन्यथा अणु
			priv->ps_enabled = false;
			cancel_work_sync(&priv->ps_work);
			ath9k_htc_setघातer(priv, ATH9K_PM_AWAKE);
		पूर्ण
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		priv->txघातlimit = 2 * conf->घातer_level;
		ath9k_cmn_update_txघात(priv->ah, priv->curtxघात,
				       priv->txघातlimit, &priv->curtxघात);
	पूर्ण

out:
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
	वापस ret;
पूर्ण

#घोषणा SUPPORTED_FILTERS			\
	(FIF_ALLMULTI |				\
	FIF_CONTROL |				\
	FIF_PSPOLL |				\
	FIF_OTHER_BSS |				\
	FIF_BCN_PRBRESP_PROMISC |		\
	FIF_PROBE_REQ |				\
	FIF_MCAST_ACTION |			\
	FIF_FCSFAIL)

अटल व्योम ath9k_htc_configure_filter(काष्ठा ieee80211_hw *hw,
				       अचिन्हित पूर्णांक changed_flags,
				       अचिन्हित पूर्णांक *total_flags,
				       u64 multicast)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	u32 rfilt;

	mutex_lock(&priv->mutex);
	changed_flags &= SUPPORTED_FILTERS;
	*total_flags &= SUPPORTED_FILTERS;

	अगर (test_bit(ATH_OP_INVALID, &common->op_flags)) अणु
		ath_dbg(ath9k_hw_common(priv->ah), ANY,
			"Unable to configure filter on invalid state\n");
		mutex_unlock(&priv->mutex);
		वापस;
	पूर्ण
	ath9k_htc_ps_wakeup(priv);

	priv->rxfilter = *total_flags;
	rfilt = ath9k_htc_calcrxfilter(priv);
	ath9k_hw_setrxfilter(priv->ah, rfilt);

	ath_dbg(ath9k_hw_common(priv->ah), CONFIG, "Set HW RX filter: 0x%x\n",
		rfilt);

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ath9k_htc_sta_rc_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath9k_htc_sta *ista =
	    container_of(work, काष्ठा ath9k_htc_sta, rc_update_work);
	काष्ठा ieee80211_sta *sta =
	    container_of((व्योम *)ista, काष्ठा ieee80211_sta, drv_priv);
	काष्ठा ath9k_htc_priv *priv = ista->htc_priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_target_rate trate;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	स_रखो(&trate, 0, माप(काष्ठा ath9k_htc_target_rate));
	ath9k_htc_setup_rate(priv, sta, &trate);
	अगर (!ath9k_htc_send_rate_cmd(priv, &trate))
		ath_dbg(common, CONFIG,
			"Supported rates for sta: %pM updated, rate caps: 0x%X\n",
			sta->addr, be32_to_cpu(trate.capflags));
	अन्यथा
		ath_dbg(common, CONFIG,
			"Unable to update supported rates for sta: %pM\n",
			sta->addr);

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ath9k_htc_sta_add(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath9k_htc_sta *ista = (काष्ठा ath9k_htc_sta *) sta->drv_priv;
	पूर्णांक ret;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);
	ret = ath9k_htc_add_station(priv, vअगर, sta);
	अगर (!ret) अणु
		INIT_WORK(&ista->rc_update_work, ath9k_htc_sta_rc_update_work);
		ista->htc_priv = priv;
		ath9k_htc_init_rate(priv, sta);
	पूर्ण
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath9k_htc_sta_हटाओ(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath9k_htc_sta *ista = (काष्ठा ath9k_htc_sta *) sta->drv_priv;
	पूर्णांक ret;

	cancel_work_sync(&ista->rc_update_work);

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);
	htc_sta_drain(priv->htc, ista->index);
	ret = ath9k_htc_हटाओ_station(priv, vअगर, sta);
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल व्योम ath9k_htc_sta_rc_update(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta, u32 changed)
अणु
	काष्ठा ath9k_htc_sta *ista = (काष्ठा ath9k_htc_sta *) sta->drv_priv;

	अगर (!(changed & IEEE80211_RC_SUPP_RATES_CHANGED))
		वापस;

	schedule_work(&ista->rc_update_work);
पूर्ण

अटल पूर्णांक ath9k_htc_conf_tx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			     स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_tx_queue_info qi;
	पूर्णांक ret = 0, qnum;

	अगर (queue >= IEEE80211_NUM_ACS)
		वापस 0;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	स_रखो(&qi, 0, माप(काष्ठा ath9k_tx_queue_info));

	qi.tqi_aअगरs = params->aअगरs;
	qi.tqi_cwmin = params->cw_min;
	qi.tqi_cwmax = params->cw_max;
	qi.tqi_burstTime = params->txop * 32;

	qnum = get_hw_qnum(queue, priv->hwq_map);

	ath_dbg(common, CONFIG,
		"Configure tx [queue/hwq] [%d/%d],  aifs: %d, cw_min: %d, cw_max: %d, txop: %d\n",
		queue, qnum, params->aअगरs, params->cw_min,
		params->cw_max, params->txop);

	ret = ath_htc_txq_update(priv, qnum, &qi);
	अगर (ret) अणु
		ath_err(common, "TXQ Update failed\n");
		जाओ out;
	पूर्ण

	अगर ((priv->ah->opmode == NL80211_IFTYPE_ADHOC) &&
	    (qnum == priv->hwq_map[IEEE80211_AC_BE]))
		    ath9k_htc_beaconq_config(priv);
out:
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath9k_htc_set_key(काष्ठा ieee80211_hw *hw,
			     क्रमागत set_key_cmd cmd,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	पूर्णांक ret = 0;

	अगर (htc_modparam_nohwcrypt)
		वापस -ENOSPC;

	अगर ((vअगर->type == NL80211_IFTYPE_ADHOC ||
	     vअगर->type == NL80211_IFTYPE_MESH_POINT) &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		/*
		 * For now, disable hw crypto क्रम the RSN IBSS group keys. This
		 * could be optimized in the future to use a modअगरied key cache
		 * design to support per-STA RX GTK, but until that माला_लो
		 * implemented, use of software crypto क्रम group addressed
		 * frames is a acceptable to allow RSN IBSS to be used.
		 */
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&priv->mutex);
	ath_dbg(common, CONFIG, "Set HW Key\n");
	ath9k_htc_ps_wakeup(priv);

	चयन (cmd) अणु
	हाल SET_KEY:
		ret = ath_key_config(common, vअगर, sta, key);
		अगर (ret >= 0) अणु
			key->hw_key_idx = ret;
			/* push IV and Michael MIC generation to stack */
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP)
				key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
			अगर (priv->ah->sw_mgmt_crypto_tx &&
			    key->cipher == WLAN_CIPHER_SUITE_CCMP)
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

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल व्योम ath9k_htc_set_bssid(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);

	ath9k_hw_ग_लिखो_associd(priv->ah);
	ath_dbg(common, CONFIG, "BSSID: %pM aid: 0x%x\n",
		common->curbssid, common->curaid);
पूर्ण

अटल व्योम ath9k_htc_bss_iter(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath9k_htc_priv *priv = data;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;

	अगर ((vअगर->type == NL80211_IFTYPE_STATION) && bss_conf->assoc) अणु
		common->curaid = bss_conf->aid;
		common->last_rssi = ATH_RSSI_DUMMY_MARKER;
		स_नकल(common->curbssid, bss_conf->bssid, ETH_ALEN);
		set_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags);
	पूर्ण
पूर्ण

अटल व्योम ath9k_htc_choose_set_bssid(काष्ठा ath9k_htc_priv *priv)
अणु
	अगर (priv->num_sta_assoc_vअगर == 1) अणु
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			priv->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
			ath9k_htc_bss_iter, priv);
		ath9k_htc_set_bssid(priv);
	पूर्ण
पूर्ण

अटल व्योम ath9k_htc_bss_info_changed(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_bss_conf *bss_conf,
				       u32 changed)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक slotसमय;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		ath_dbg(common, CONFIG, "BSS Changed ASSOC %d\n",
			bss_conf->assoc);

		bss_conf->assoc ?
			priv->num_sta_assoc_vअगर++ : priv->num_sta_assoc_vअगर--;

		अगर (!bss_conf->assoc)
			clear_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags);

		अगर (priv->ah->opmode == NL80211_IFTYPE_STATION) अणु
			ath9k_htc_choose_set_bssid(priv);
			अगर (bss_conf->assoc && (priv->num_sta_assoc_vअगर == 1))
				ath9k_htc_start_ani(priv);
			अन्यथा अगर (priv->num_sta_assoc_vअगर == 0)
				ath9k_htc_stop_ani(priv);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_IBSS) अणु
		अगर (priv->ah->opmode == NL80211_IFTYPE_ADHOC) अणु
			common->curaid = bss_conf->aid;
			स_नकल(common->curbssid, bss_conf->bssid, ETH_ALEN);
			ath9k_htc_set_bssid(priv);
		पूर्ण
	पूर्ण

	अगर ((changed & BSS_CHANGED_BEACON_ENABLED) && bss_conf->enable_beacon) अणु
		ath_dbg(common, CONFIG, "Beacon enabled for BSS: %pM\n",
			bss_conf->bssid);
		ath9k_htc_set_tsfadjust(priv, vअगर);
		priv->cur_beacon_conf.enable_beacon = 1;
		ath9k_htc_beacon_config(priv, vअगर);
	पूर्ण

	अगर ((changed & BSS_CHANGED_BEACON_ENABLED) && !bss_conf->enable_beacon) अणु
		/*
		 * Disable SWBA पूर्णांकerrupt only अगर there are no
		 * concurrent AP/mesh or IBSS पूर्णांकerfaces.
		 */
		अगर ((priv->num_ap_vअगर + priv->num_mbss_vअगर <= 1) ||
		     priv->num_ibss_vअगर) अणु
			ath_dbg(common, CONFIG,
				"Beacon disabled for BSS: %pM\n",
				bss_conf->bssid);
			priv->cur_beacon_conf.enable_beacon = 0;
			ath9k_htc_beacon_config(priv, vअगर);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		/*
		 * Reset the HW TSF क्रम the first AP or mesh पूर्णांकerface.
		 */
		अगर (priv->nvअगरs == 1 &&
		    ((priv->ah->opmode == NL80211_IFTYPE_AP &&
		      vअगर->type == NL80211_IFTYPE_AP &&
		      priv->num_ap_vअगर == 1) ||
		    (priv->ah->opmode == NL80211_IFTYPE_MESH_POINT &&
		      vअगर->type == NL80211_IFTYPE_MESH_POINT &&
		      priv->num_mbss_vअगर == 1))) अणु
			set_bit(OP_TSF_RESET, &priv->op_flags);
		पूर्ण
		ath_dbg(common, CONFIG,
			"Beacon interval changed for BSS: %pM\n",
			bss_conf->bssid);
		ath9k_htc_beacon_config(priv, vअगर);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		अगर (bss_conf->use_लघु_slot)
			slotसमय = 9;
		अन्यथा
			slotसमय = 20;
		अगर (vअगर->type == NL80211_IFTYPE_AP) अणु
			/*
			 * Defer update, so that connected stations can adjust
			 * their settings at the same समय.
			 * See beacon.c क्रम more details
			 */
			priv->beacon.slotसमय = slotसमय;
			priv->beacon.updateslot = UPDATE;
		पूर्ण अन्यथा अणु
			ah->slotसमय = slotसमय;
			ath9k_hw_init_global_settings(ah);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_HT)
		ath9k_htc_update_rate(priv, vअगर, bss_conf);

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल u64 ath9k_htc_get_tsf(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	u64 tsf;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);
	tsf = ath9k_hw_gettsf64(priv->ah);
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	वापस tsf;
पूर्ण

अटल व्योम ath9k_htc_set_tsf(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर, u64 tsf)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);
	ath9k_hw_settsf64(priv->ah, tsf);
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ath9k_htc_reset_tsf(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);
	ath9k_hw_reset_tsf(priv->ah);
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ath9k_htc_ampdu_action(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath9k_htc_sta *ista;
	पूर्णांक ret = 0;
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		ret = ath9k_htc_tx_aggr_oper(priv, vअगर, sta, action, tid);
		अगर (!ret)
			ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		ath9k_htc_tx_aggr_oper(priv, vअगर, sta, action, tid);
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		अगर (tid >= ATH9K_HTC_MAX_TID) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ista = (काष्ठा ath9k_htc_sta *) sta->drv_priv;
		spin_lock_bh(&priv->tx.tx_lock);
		ista->tid_state[tid] = AGGR_OPERATIONAL;
		spin_unlock_bh(&priv->tx.tx_lock);
		अवरोध;
	शेष:
		ath_err(ath9k_hw_common(priv->ah), "Unknown AMPDU action\n");
	पूर्ण

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल व्योम ath9k_htc_sw_scan_start(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    स्थिर u8 *mac_addr)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);

	mutex_lock(&priv->mutex);
	spin_lock_bh(&priv->beacon_lock);
	set_bit(ATH_OP_SCANNING, &common->op_flags);
	spin_unlock_bh(&priv->beacon_lock);
	cancel_work_sync(&priv->ps_work);
	ath9k_htc_stop_ani(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम ath9k_htc_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);

	mutex_lock(&priv->mutex);
	spin_lock_bh(&priv->beacon_lock);
	clear_bit(ATH_OP_SCANNING, &common->op_flags);
	spin_unlock_bh(&priv->beacon_lock);
	ath9k_htc_ps_wakeup(priv);
	ath9k_htc_vअगर_reconfig(priv);
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक ath9k_htc_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	वापस 0;
पूर्ण

अटल व्योम ath9k_htc_set_coverage_class(काष्ठा ieee80211_hw *hw,
					 s16 coverage_class)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);
	priv->ah->coverage_class = coverage_class;
	ath9k_hw_init_global_settings(priv->ah);
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

/*
 * Currently, this is used only क्रम selecting the minimum rate
 * क्रम management frames, rate selection क्रम data frames reमुख्य
 * unaffected.
 */
अटल पूर्णांक ath9k_htc_set_bitrate_mask(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा ath9k_htc_target_rate_mask पंचांगask;
	काष्ठा ath9k_htc_vअगर *avp = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret = 0;
	u8 cmd_rsp;

	स_रखो(&पंचांगask, 0, माप(काष्ठा ath9k_htc_target_rate_mask));

	पंचांगask.vअगर_index = avp->index;
	पंचांगask.band = NL80211_BAND_2GHZ;
	पंचांगask.mask = cpu_to_be32(mask->control[NL80211_BAND_2GHZ].legacy);

	WMI_CMD_BUF(WMI_BITRATE_MASK_CMDID, &पंचांगask);
	अगर (ret) अणु
		ath_err(common,
			"Unable to set 2G rate mask for "
			"interface at idx: %d\n", avp->index);
		जाओ out;
	पूर्ण

	पंचांगask.band = NL80211_BAND_5GHZ;
	पंचांगask.mask = cpu_to_be32(mask->control[NL80211_BAND_5GHZ].legacy);

	WMI_CMD_BUF(WMI_BITRATE_MASK_CMDID, &पंचांगask);
	अगर (ret) अणु
		ath_err(common,
			"Unable to set 5G rate mask for "
			"interface at idx: %d\n", avp->index);
		जाओ out;
	पूर्ण

	ath_dbg(common, CONFIG, "Set bitrate masks: 0x%x, 0x%x\n",
		mask->control[NL80211_BAND_2GHZ].legacy,
		mask->control[NL80211_BAND_5GHZ].legacy);
out:
	वापस ret;
पूर्ण


अटल पूर्णांक ath9k_htc_get_stats(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath9k_mib_stats *mib_stats = &ah->ah_mibStats;

	stats->करोt11ACKFailureCount = mib_stats->ackrcv_bad;
	stats->करोt11RTSFailureCount = mib_stats->rts_bad;
	stats->करोt11FCSErrorCount = mib_stats->fcs_bad;
	stats->करोt11RTSSuccessCount = mib_stats->rts_good;

	वापस 0;
पूर्ण

काष्ठा base_eep_header *ath9k_htc_get_eeprom_base(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा base_eep_header *pBase = शून्य;
	/*
	 * This can be करोne since all the 3 EEPROM families have the
	 * same base header upto a certain poपूर्णांक, and we are पूर्णांकerested in
	 * the data only upto that poपूर्णांक.
	 */

	अगर (AR_SREV_9271(priv->ah))
		pBase = (काष्ठा base_eep_header *)
			&priv->ah->eeprom.map4k.baseEepHeader;
	अन्यथा अगर (priv->ah->hw_version.usbdev == AR9280_USB)
		pBase = (काष्ठा base_eep_header *)
			&priv->ah->eeprom.def.baseEepHeader;
	अन्यथा अगर (priv->ah->hw_version.usbdev == AR9287_USB)
		pBase = (काष्ठा base_eep_header *)
			&priv->ah->eeprom.map9287.baseEepHeader;
	वापस pBase;
पूर्ण


अटल पूर्णांक ath9k_htc_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant,
				 u32 *rx_ant)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	काष्ठा base_eep_header *pBase = ath9k_htc_get_eeprom_base(priv);
	अगर (pBase) अणु
		*tx_ant = pBase->txMask;
		*rx_ant = pBase->rxMask;
	पूर्ण अन्यथा अणु
		*tx_ant = 0;
		*rx_ant = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ath9k_htc_channel_चयन_beacon(काष्ठा ieee80211_hw *hw,
					    काष्ठा ieee80211_vअगर *vअगर,
					    काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;

	/* mac80211 करोes not support CSA in multi-अगर हालs (yet) */
	अगर (WARN_ON(priv->csa_vअगर))
		वापस;

	priv->csa_vअगर = vअगर;
पूर्ण

काष्ठा ieee80211_ops ath9k_htc_ops = अणु
	.tx                 = ath9k_htc_tx,
	.start              = ath9k_htc_start,
	.stop               = ath9k_htc_stop,
	.add_पूर्णांकerface      = ath9k_htc_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface   = ath9k_htc_हटाओ_पूर्णांकerface,
	.config             = ath9k_htc_config,
	.configure_filter   = ath9k_htc_configure_filter,
	.sta_add            = ath9k_htc_sta_add,
	.sta_हटाओ         = ath9k_htc_sta_हटाओ,
	.conf_tx            = ath9k_htc_conf_tx,
	.sta_rc_update      = ath9k_htc_sta_rc_update,
	.bss_info_changed   = ath9k_htc_bss_info_changed,
	.set_key            = ath9k_htc_set_key,
	.get_tsf            = ath9k_htc_get_tsf,
	.set_tsf            = ath9k_htc_set_tsf,
	.reset_tsf          = ath9k_htc_reset_tsf,
	.ampdu_action       = ath9k_htc_ampdu_action,
	.sw_scan_start      = ath9k_htc_sw_scan_start,
	.sw_scan_complete   = ath9k_htc_sw_scan_complete,
	.set_rts_threshold  = ath9k_htc_set_rts_threshold,
	.rfसमाप्त_poll        = ath9k_htc_rfसमाप्त_poll_state,
	.set_coverage_class = ath9k_htc_set_coverage_class,
	.set_bitrate_mask   = ath9k_htc_set_bitrate_mask,
	.get_stats	    = ath9k_htc_get_stats,
	.get_antenna	    = ath9k_htc_get_antenna,
	.channel_चयन_beacon	= ath9k_htc_channel_चयन_beacon,

#अगर_घोषित CONFIG_ATH9K_HTC_DEBUGFS
	.get_et_sset_count  = ath9k_htc_get_et_sset_count,
	.get_et_stats       = ath9k_htc_get_et_stats,
	.get_et_strings     = ath9k_htc_get_et_strings,
#पूर्ण_अगर
पूर्ण;
