<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2015-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश "mac.h"

#समावेश <net/mac80211.h>
#समावेश "hif.h"
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "wmi.h"
#समावेश "wmi-ops.h"

अटल स्थिर काष्ठा wiphy_wowlan_support ath10k_wowlan_support = अणु
	.flags = WIPHY_WOWLAN_DISCONNECT |
		 WIPHY_WOWLAN_MAGIC_PKT,
	.pattern_min_len = WOW_MIN_PATTERN_SIZE,
	.pattern_max_len = WOW_MAX_PATTERN_SIZE,
	.max_pkt_offset = WOW_MAX_PKT_OFFSET,
पूर्ण;

अटल पूर्णांक ath10k_wow_vअगर_cleanup(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	पूर्णांक i, ret;

	क्रम (i = 0; i < WOW_EVENT_MAX; i++) अणु
		ret = ath10k_wmi_wow_add_wakeup_event(ar, arvअगर->vdev_id, i, 0);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to issue wow wakeup for event %s on vdev %i: %d\n",
				    wow_wakeup_event(i), arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ar->wow.max_num_patterns; i++) अणु
		ret = ath10k_wmi_wow_del_pattern(ar, arvअगर->vdev_id, i);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to delete wow pattern %d for vdev %i: %d\n",
				    i, arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wow_cleanup(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		ret = ath10k_wow_vअगर_cleanup(arvअगर);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to clean wow wakeups on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Convert a 802.3 क्रमmat to a 802.11 क्रमmat.
 *         +------------+-----------+--------+----------------+
 * 802.3:  |dest mac(6B)|src mac(6B)|type(2B)|     body...    |
 *         +------------+-----------+--------+----------------+
 *                |__         |_______    |____________  |________
 *                   |                |                |          |
 *         +--+------------+----+-----------+---------------+-----------+
 * 802.11: |4B|dest mac(6B)| 6B |src mac(6B)|  8B  |type(2B)|  body...  |
 *         +--+------------+----+-----------+---------------+-----------+
 */
अटल व्योम ath10k_wow_convert_8023_to_80211(काष्ठा cfg80211_pkt_pattern *new,
					     स्थिर काष्ठा cfg80211_pkt_pattern *old)
अणु
	u8 hdr_8023_pattern[ETH_HLEN] = अणुपूर्ण;
	u8 hdr_8023_bit_mask[ETH_HLEN] = अणुपूर्ण;
	u8 hdr_80211_pattern[WOW_HDR_LEN] = अणुपूर्ण;
	u8 hdr_80211_bit_mask[WOW_HDR_LEN] = अणुपूर्ण;

	पूर्णांक total_len = old->pkt_offset + old->pattern_len;
	पूर्णांक hdr_80211_end_offset;

	काष्ठा ieee80211_hdr_3addr *new_hdr_pattern =
		(काष्ठा ieee80211_hdr_3addr *)hdr_80211_pattern;
	काष्ठा ieee80211_hdr_3addr *new_hdr_mask =
		(काष्ठा ieee80211_hdr_3addr *)hdr_80211_bit_mask;
	काष्ठा ethhdr *old_hdr_pattern = (काष्ठा ethhdr *)hdr_8023_pattern;
	काष्ठा ethhdr *old_hdr_mask = (काष्ठा ethhdr *)hdr_8023_bit_mask;
	पूर्णांक hdr_len = माप(*new_hdr_pattern);

	काष्ठा rfc1042_hdr *new_rfc_pattern =
		(काष्ठा rfc1042_hdr *)(hdr_80211_pattern + hdr_len);
	काष्ठा rfc1042_hdr *new_rfc_mask =
		(काष्ठा rfc1042_hdr *)(hdr_80211_bit_mask + hdr_len);
	पूर्णांक rfc_len = माप(*new_rfc_pattern);

	स_नकल(hdr_8023_pattern + old->pkt_offset,
	       old->pattern, ETH_HLEN - old->pkt_offset);
	स_नकल(hdr_8023_bit_mask + old->pkt_offset,
	       old->mask, ETH_HLEN - old->pkt_offset);

	/* Copy destination address */
	स_नकल(new_hdr_pattern->addr1, old_hdr_pattern->h_dest, ETH_ALEN);
	स_नकल(new_hdr_mask->addr1, old_hdr_mask->h_dest, ETH_ALEN);

	/* Copy source address */
	स_नकल(new_hdr_pattern->addr3, old_hdr_pattern->h_source, ETH_ALEN);
	स_नकल(new_hdr_mask->addr3, old_hdr_mask->h_source, ETH_ALEN);

	/* Copy logic link type */
	स_नकल(&new_rfc_pattern->snap_type,
	       &old_hdr_pattern->h_proto,
	       माप(old_hdr_pattern->h_proto));
	स_नकल(&new_rfc_mask->snap_type,
	       &old_hdr_mask->h_proto,
	       माप(old_hdr_mask->h_proto));

	/* Calculate new pkt_offset */
	अगर (old->pkt_offset < ETH_ALEN)
		new->pkt_offset = old->pkt_offset +
			दुरत्व(काष्ठा ieee80211_hdr_3addr, addr1);
	अन्यथा अगर (old->pkt_offset < दुरत्व(काष्ठा ethhdr, h_proto))
		new->pkt_offset = old->pkt_offset +
			दुरत्व(काष्ठा ieee80211_hdr_3addr, addr3) -
			दुरत्व(काष्ठा ethhdr, h_source);
	अन्यथा
		new->pkt_offset = old->pkt_offset + hdr_len + rfc_len - ETH_HLEN;

	/* Calculate new hdr end offset */
	अगर (total_len > ETH_HLEN)
		hdr_80211_end_offset = hdr_len + rfc_len;
	अन्यथा अगर (total_len > दुरत्व(काष्ठा ethhdr, h_proto))
		hdr_80211_end_offset = hdr_len + rfc_len + total_len - ETH_HLEN;
	अन्यथा अगर (total_len > ETH_ALEN)
		hdr_80211_end_offset = total_len - ETH_ALEN +
			दुरत्व(काष्ठा ieee80211_hdr_3addr, addr3);
	अन्यथा
		hdr_80211_end_offset = total_len +
			दुरत्व(काष्ठा ieee80211_hdr_3addr, addr1);

	new->pattern_len = hdr_80211_end_offset - new->pkt_offset;

	स_नकल((u8 *)new->pattern,
	       hdr_80211_pattern + new->pkt_offset,
	       new->pattern_len);
	स_नकल((u8 *)new->mask,
	       hdr_80211_bit_mask + new->pkt_offset,
	       new->pattern_len);

	अगर (total_len > ETH_HLEN) अणु
		/* Copy frame body */
		स_नकल((u8 *)new->pattern + new->pattern_len,
		       (व्योम *)old->pattern + ETH_HLEN - old->pkt_offset,
		       total_len - ETH_HLEN);
		स_नकल((u8 *)new->mask + new->pattern_len,
		       (व्योम *)old->mask + ETH_HLEN - old->pkt_offset,
		       total_len - ETH_HLEN);

		new->pattern_len += total_len - ETH_HLEN;
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_wmi_pno_check(काष्ठा ath10k *ar, u32 vdev_id,
				काष्ठा cfg80211_sched_scan_request *nd_config,
				काष्ठा wmi_pno_scan_req *pno)
अणु
	पूर्णांक i, j, ret = 0;
	u8 ssid_len;

	pno->enable = 1;
	pno->vdev_id = vdev_id;
	pno->uc_networks_count = nd_config->n_match_sets;

	अगर (!pno->uc_networks_count ||
	    pno->uc_networks_count > WMI_PNO_MAX_SUPP_NETWORKS)
		वापस -EINVAL;

	अगर (nd_config->n_channels > WMI_PNO_MAX_NETW_CHANNELS_EX)
		वापस -EINVAL;

	/* Filling per profile  params */
	क्रम (i = 0; i < pno->uc_networks_count; i++) अणु
		ssid_len = nd_config->match_sets[i].ssid.ssid_len;

		अगर (ssid_len == 0 || ssid_len > 32)
			वापस -EINVAL;

		pno->a_networks[i].ssid.ssid_len = __cpu_to_le32(ssid_len);

		स_नकल(pno->a_networks[i].ssid.ssid,
		       nd_config->match_sets[i].ssid.ssid,
		       nd_config->match_sets[i].ssid.ssid_len);
		pno->a_networks[i].authentication = 0;
		pno->a_networks[i].encryption     = 0;
		pno->a_networks[i].bcast_nw_type  = 0;

		/*Copying list of valid channel पूर्णांकo request */
		pno->a_networks[i].channel_count = nd_config->n_channels;
		pno->a_networks[i].rssi_threshold = nd_config->match_sets[i].rssi_thold;

		क्रम (j = 0; j < nd_config->n_channels; j++) अणु
			pno->a_networks[i].channels[j] =
					nd_config->channels[j]->center_freq;
		पूर्ण
	पूर्ण

	/* set scan to passive अगर no SSIDs are specअगरied in the request */
	अगर (nd_config->n_ssids == 0)
		pno->करो_passive_scan = true;
	अन्यथा
		pno->करो_passive_scan = false;

	क्रम (i = 0; i < nd_config->n_ssids; i++) अणु
		j = 0;
		जबतक (j < pno->uc_networks_count) अणु
			अगर (__le32_to_cpu(pno->a_networks[j].ssid.ssid_len) ==
				nd_config->ssids[i].ssid_len &&
			(स_भेद(pno->a_networks[j].ssid.ssid,
				nd_config->ssids[i].ssid,
				__le32_to_cpu(pno->a_networks[j].ssid.ssid_len)) == 0)) अणु
				pno->a_networks[j].bcast_nw_type = BCAST_HIDDEN;
				अवरोध;
			पूर्ण
			j++;
		पूर्ण
	पूर्ण

	अगर (nd_config->n_scan_plans == 2) अणु
		pno->fast_scan_period = nd_config->scan_plans[0].पूर्णांकerval * MSEC_PER_SEC;
		pno->fast_scan_max_cycles = nd_config->scan_plans[0].iterations;
		pno->slow_scan_period =
			nd_config->scan_plans[1].पूर्णांकerval * MSEC_PER_SEC;
	पूर्ण अन्यथा अगर (nd_config->n_scan_plans == 1) अणु
		pno->fast_scan_period = nd_config->scan_plans[0].पूर्णांकerval * MSEC_PER_SEC;
		pno->fast_scan_max_cycles = 1;
		pno->slow_scan_period = nd_config->scan_plans[0].पूर्णांकerval * MSEC_PER_SEC;
	पूर्ण अन्यथा अणु
		ath10k_warn(ar, "Invalid number of scan plans %d !!",
			    nd_config->n_scan_plans);
	पूर्ण

	अगर (nd_config->flags & NL80211_SCAN_FLAG_RANDOM_ADDR) अणु
		/* enable mac अक्रमomization */
		pno->enable_pno_scan_अक्रमomization = 1;
		स_नकल(pno->mac_addr, nd_config->mac_addr, ETH_ALEN);
		स_नकल(pno->mac_addr_mask, nd_config->mac_addr_mask, ETH_ALEN);
	पूर्ण

	pno->delay_start_समय = nd_config->delay;

	/* Current FW करोes not support min-max range क्रम dwell समय */
	pno->active_max_समय = WMI_ACTIVE_MAX_CHANNEL_TIME;
	pno->passive_max_समय = WMI_PASSIVE_MAX_CHANNEL_TIME;
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_vअगर_wow_set_wakeups(काष्ठा ath10k_vअगर *arvअगर,
				      काष्ठा cfg80211_wowlan *wowlan)
अणु
	पूर्णांक ret, i;
	अचिन्हित दीर्घ wow_mask = 0;
	काष्ठा ath10k *ar = arvअगर->ar;
	स्थिर काष्ठा cfg80211_pkt_pattern *patterns = wowlan->patterns;
	पूर्णांक pattern_id = 0;

	/* Setup requested WOW features */
	चयन (arvअगर->vdev_type) अणु
	हाल WMI_VDEV_TYPE_IBSS:
		__set_bit(WOW_BEACON_EVENT, &wow_mask);
		fallthrough;
	हाल WMI_VDEV_TYPE_AP:
		__set_bit(WOW_DEAUTH_RECVD_EVENT, &wow_mask);
		__set_bit(WOW_DISASSOC_RECVD_EVENT, &wow_mask);
		__set_bit(WOW_PROBE_REQ_WPS_IE_EVENT, &wow_mask);
		__set_bit(WOW_AUTH_REQ_EVENT, &wow_mask);
		__set_bit(WOW_ASSOC_REQ_EVENT, &wow_mask);
		__set_bit(WOW_HTT_EVENT, &wow_mask);
		__set_bit(WOW_RA_MATCH_EVENT, &wow_mask);
		अवरोध;
	हाल WMI_VDEV_TYPE_STA:
		अगर (wowlan->disconnect) अणु
			__set_bit(WOW_DEAUTH_RECVD_EVENT, &wow_mask);
			__set_bit(WOW_DISASSOC_RECVD_EVENT, &wow_mask);
			__set_bit(WOW_BMISS_EVENT, &wow_mask);
			__set_bit(WOW_CSA_IE_EVENT, &wow_mask);
		पूर्ण

		अगर (wowlan->magic_pkt)
			__set_bit(WOW_MAGIC_PKT_RECVD_EVENT, &wow_mask);

		अगर (wowlan->nd_config) अणु
			काष्ठा wmi_pno_scan_req *pno;
			पूर्णांक ret;

			pno = kzalloc(माप(*pno), GFP_KERNEL);
			अगर (!pno)
				वापस -ENOMEM;

			ar->nlo_enabled = true;

			ret = ath10k_wmi_pno_check(ar, arvअगर->vdev_id,
						   wowlan->nd_config, pno);
			अगर (!ret) अणु
				ath10k_wmi_wow_config_pno(ar, arvअगर->vdev_id, pno);
				__set_bit(WOW_NLO_DETECTED_EVENT, &wow_mask);
			पूर्ण

			kमुक्त(pno);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < wowlan->n_patterns; i++) अणु
		u8 biपंचांगask[WOW_MAX_PATTERN_SIZE] = अणुपूर्ण;
		u8 ath_pattern[WOW_MAX_PATTERN_SIZE] = अणुपूर्ण;
		u8 ath_biपंचांगask[WOW_MAX_PATTERN_SIZE] = अणुपूर्ण;
		काष्ठा cfg80211_pkt_pattern new_pattern = अणुपूर्ण;
		काष्ठा cfg80211_pkt_pattern old_pattern = patterns[i];
		पूर्णांक j;

		new_pattern.pattern = ath_pattern;
		new_pattern.mask = ath_biपंचांगask;
		अगर (patterns[i].pattern_len > WOW_MAX_PATTERN_SIZE)
			जारी;
		/* convert bytemask to biपंचांगask */
		क्रम (j = 0; j < patterns[i].pattern_len; j++)
			अगर (patterns[i].mask[j / 8] & BIT(j % 8))
				biपंचांगask[j] = 0xff;
		old_pattern.mask = biपंचांगask;
		new_pattern = old_pattern;

		अगर (ar->wmi.rx_decap_mode == ATH10K_HW_TXRX_NATIVE_WIFI) अणु
			अगर (patterns[i].pkt_offset < ETH_HLEN)
				ath10k_wow_convert_8023_to_80211(&new_pattern,
								 &old_pattern);
			अन्यथा
				new_pattern.pkt_offset += WOW_HDR_LEN - ETH_HLEN;
		पूर्ण

		अगर (WARN_ON(new_pattern.pattern_len > WOW_MAX_PATTERN_SIZE))
			वापस -EINVAL;

		ret = ath10k_wmi_wow_add_pattern(ar, arvअगर->vdev_id,
						 pattern_id,
						 new_pattern.pattern,
						 new_pattern.mask,
						 new_pattern.pattern_len,
						 new_pattern.pkt_offset);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to add pattern %i to vdev %i: %d\n",
				    pattern_id,
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण

		pattern_id++;
		__set_bit(WOW_PATTERN_MATCH_EVENT, &wow_mask);
	पूर्ण

	क्रम (i = 0; i < WOW_EVENT_MAX; i++) अणु
		अगर (!test_bit(i, &wow_mask))
			जारी;
		ret = ath10k_wmi_wow_add_wakeup_event(ar, arvअगर->vdev_id, i, 1);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to enable wakeup event %s on vdev %i: %d\n",
				    wow_wakeup_event(i), arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wow_set_wakeups(काष्ठा ath10k *ar,
				  काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		ret = ath10k_vअगर_wow_set_wakeups(arvअगर, wowlan);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set wow wakeups on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_vअगर_wow_clean_nlo(काष्ठा ath10k_vअगर *arvअगर)
अणु
	पूर्णांक ret = 0;
	काष्ठा ath10k *ar = arvअगर->ar;

	चयन (arvअगर->vdev_type) अणु
	हाल WMI_VDEV_TYPE_STA:
		अगर (ar->nlo_enabled) अणु
			काष्ठा wmi_pno_scan_req *pno;

			pno = kzalloc(माप(*pno), GFP_KERNEL);
			अगर (!pno)
				वापस -ENOMEM;

			pno->enable = 0;
			ar->nlo_enabled = false;
			ret = ath10k_wmi_wow_config_pno(ar, arvअगर->vdev_id, pno);
			kमुक्त(pno);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_wow_nlo_cleanup(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		ret = ath10k_vअगर_wow_clean_nlo(arvअगर);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to clean nlo settings on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wow_enable(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->target_suspend);

	ret = ath10k_wmi_wow_enable(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to issue wow enable: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&ar->target_suspend, 3 * HZ);
	अगर (ret == 0) अणु
		ath10k_warn(ar, "timed out while waiting for suspend completion\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wow_wakeup(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->wow.wakeup_completed);

	ret = ath10k_wmi_wow_host_wakeup_ind(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send wow wakeup indication: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&ar->wow.wakeup_completed, 3 * HZ);
	अगर (ret == 0) अणु
		ath10k_warn(ar, "timed out while waiting for wow wakeup completion\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_wow_op_suspend(काष्ठा ieee80211_hw *hw,
			  काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा ath10k *ar = hw->priv;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (WARN_ON(!test_bit(ATH10K_FW_FEATURE_WOWLAN_SUPPORT,
			      ar->running_fw->fw_file.fw_features))) अणु
		ret = 1;
		जाओ निकास;
	पूर्ण

	ret =  ath10k_wow_cleanup(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to clear wow wakeup events: %d\n",
			    ret);
		जाओ निकास;
	पूर्ण

	ret = ath10k_wow_set_wakeups(ar, wowlan);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set wow wakeup events: %d\n",
			    ret);
		जाओ cleanup;
	पूर्ण

	ath10k_mac_रुको_tx_complete(ar);

	ret = ath10k_wow_enable(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to start wow: %d\n", ret);
		जाओ cleanup;
	पूर्ण

	ret = ath10k_hअगर_suspend(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to suspend hif: %d\n", ret);
		जाओ wakeup;
	पूर्ण

	जाओ निकास;

wakeup:
	ath10k_wow_wakeup(ar);

cleanup:
	ath10k_wow_cleanup(ar);

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret ? 1 : 0;
पूर्ण

व्योम ath10k_wow_op_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled)
अणु
	काष्ठा ath10k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);
	अगर (test_bit(ATH10K_FW_FEATURE_WOWLAN_SUPPORT,
		     ar->running_fw->fw_file.fw_features)) अणु
		device_set_wakeup_enable(ar->dev, enabled);
	पूर्ण
	mutex_unlock(&ar->conf_mutex);
पूर्ण

पूर्णांक ath10k_wow_op_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath10k *ar = hw->priv;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (WARN_ON(!test_bit(ATH10K_FW_FEATURE_WOWLAN_SUPPORT,
			      ar->running_fw->fw_file.fw_features))) अणु
		ret = 1;
		जाओ निकास;
	पूर्ण

	ret = ath10k_hअगर_resume(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to resume hif: %d\n", ret);
		जाओ निकास;
	पूर्ण

	ret = ath10k_wow_wakeup(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to wakeup from wow: %d\n", ret);

	ret = ath10k_wow_nlo_cleanup(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to cleanup nlo: %d\n", ret);

निकास:
	अगर (ret) अणु
		चयन (ar->state) अणु
		हाल ATH10K_STATE_ON:
			ar->state = ATH10K_STATE_RESTARTING;
			ret = 1;
			अवरोध;
		हाल ATH10K_STATE_OFF:
		हाल ATH10K_STATE_RESTARTING:
		हाल ATH10K_STATE_RESTARTED:
		हाल ATH10K_STATE_UTF:
		हाल ATH10K_STATE_WEDGED:
			ath10k_warn(ar, "encountered unexpected device state %d on resume, cannot recover\n",
				    ar->state);
			ret = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

पूर्णांक ath10k_wow_init(काष्ठा ath10k *ar)
अणु
	अगर (!test_bit(ATH10K_FW_FEATURE_WOWLAN_SUPPORT,
		      ar->running_fw->fw_file.fw_features))
		वापस 0;

	अगर (WARN_ON(!test_bit(WMI_SERVICE_WOW, ar->wmi.svc_map)))
		वापस -EINVAL;

	ar->wow.wowlan_support = ath10k_wowlan_support;

	अगर (ar->wmi.rx_decap_mode == ATH10K_HW_TXRX_NATIVE_WIFI) अणु
		ar->wow.wowlan_support.pattern_max_len -= WOW_MAX_REDUCE;
		ar->wow.wowlan_support.max_pkt_offset -= WOW_MAX_REDUCE;
	पूर्ण

	अगर (test_bit(WMI_SERVICE_NLO, ar->wmi.svc_map)) अणु
		ar->wow.wowlan_support.flags |= WIPHY_WOWLAN_NET_DETECT;
		ar->wow.wowlan_support.max_nd_match_sets = WMI_PNO_MAX_SUPP_NETWORKS;
	पूर्ण

	ar->wow.wowlan_support.n_patterns = ar->wow.max_num_patterns;
	ar->hw->wiphy->wowlan = &ar->wow.wowlan_support;

	device_set_wakeup_capable(ar->dev, true);

	वापस 0;
पूर्ण
