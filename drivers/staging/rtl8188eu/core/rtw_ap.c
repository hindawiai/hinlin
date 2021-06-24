<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_AP_C_

#समावेश <linux/ieee80211.h>

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <wअगरi.h>
#समावेश <ieee80211.h>
#समावेश <यंत्र/unaligned.h>

#अगर_घोषित CONFIG_88EU_AP_MODE

व्योम init_mlme_ap_info(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;

	spin_lock_init(&pmlmepriv->bcn_update_lock);

	/* क्रम ACL */
	_rtw_init_queue(&pacl_list->acl_node_q);

	start_ap_mode(padapter);
पूर्ण

व्योम मुक्त_mlme_ap_info(काष्ठा adapter *padapter)
अणु
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;

	pmlmepriv->update_bcn = false;
	pmlmeext->bstart_bss = false;

	rtw_sta_flush(padapter);

	pmlmeinfo->state = _HW_STATE_NOLINK_;

	/* मुक्त_assoc_sta_resources */
	rtw_मुक्त_all_stainfo(padapter);

	/* मुक्त bc/mc sta_info */
	psta = rtw_get_bcmc_stainfo(padapter);
	spin_lock_bh(&pstapriv->sta_hash_lock);
	rtw_मुक्त_stainfo(padapter, psta);
	spin_unlock_bh(&pstapriv->sta_hash_lock);
पूर्ण

अटल व्योम update_BCNTIM(काष्ठा adapter *padapter)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork_mlmeext = &pmlmeinfo->network;
	अचिन्हित अक्षर *pie = pnetwork_mlmeext->ies;
	u8 *p, *dst_ie, *preमुख्यder_ie = शून्य;
	u8 *pbackup_reमुख्यder_ie = शून्य;
	uपूर्णांक offset, पंचांगp_len, tim_ielen, tim_ie_offset, reमुख्यder_ielen;

	/* update TIM IE */
	p = rtw_get_ie(pie + _FIXED_IE_LENGTH_, WLAN_EID_TIM, &tim_ielen,
		       pnetwork_mlmeext->ie_length - _FIXED_IE_LENGTH_);
	अगर (p && tim_ielen > 0) अणु
		tim_ielen += 2;
		preमुख्यder_ie = p + tim_ielen;
		tim_ie_offset = (पूर्णांक)(p - pie);
		reमुख्यder_ielen = pnetwork_mlmeext->ie_length -
					tim_ie_offset - tim_ielen;
		/* append TIM IE from dst_ie offset */
		dst_ie = p;
	पूर्ण अन्यथा अणु
		tim_ielen = 0;

		/* calculate head_len */
		offset = _FIXED_IE_LENGTH_;
		offset += pnetwork_mlmeext->ssid.ssid_length + 2;

		/*  get supported rates len */
		p = rtw_get_ie(pie + _BEACON_IE_OFFSET_, WLAN_EID_SUPP_RATES,
			       &पंचांगp_len, (pnetwork_mlmeext->ie_length -
					  _BEACON_IE_OFFSET_));
		अगर (p)
			offset += पंचांगp_len + 2;

		/* DS Parameter Set IE, len = 3 */
		offset += 3;

		preमुख्यder_ie = pie + offset;

		reमुख्यder_ielen = pnetwork_mlmeext->ie_length -
					offset - tim_ielen;

		/* append TIM IE from offset */
		dst_ie = pie + offset;
	पूर्ण

	अगर (reमुख्यder_ielen > 0) अणु
		pbackup_reमुख्यder_ie = rtw_दो_स्मृति(reमुख्यder_ielen);
		अगर (pbackup_reमुख्यder_ie && preमुख्यder_ie)
			स_नकल(pbackup_reमुख्यder_ie, preमुख्यder_ie,
			       reमुख्यder_ielen);
	पूर्ण
	*dst_ie++ = WLAN_EID_TIM;

	अगर ((pstapriv->tim_biपंचांगap & 0xff00) && (pstapriv->tim_biपंचांगap & 0x00fc))
		tim_ielen = 5;
	अन्यथा
		tim_ielen = 4;

	*dst_ie++ = tim_ielen;

	*dst_ie++ = 0;/* DTIM count */
	*dst_ie++ = 1;/* DTIM period */

	अगर (pstapriv->tim_biपंचांगap & BIT(0))/* क्रम bc/mc frames */
		*dst_ie++ = BIT(0);/* biपंचांगap ctrl */
	अन्यथा
		*dst_ie++ = 0;

	अगर (tim_ielen == 4) अणु
		*dst_ie++ = pstapriv->tim_biपंचांगap & 0xff;
	पूर्ण अन्यथा अगर (tim_ielen == 5) अणु
		put_unaligned_le16(pstapriv->tim_biपंचांगap, dst_ie);
		dst_ie += 2;
	पूर्ण

	/* copy reमुख्यder IE */
	अगर (pbackup_reमुख्यder_ie) अणु
		स_नकल(dst_ie, pbackup_reमुख्यder_ie, reमुख्यder_ielen);

		kमुक्त(pbackup_reमुख्यder_ie);
	पूर्ण
	offset =  (uपूर्णांक)(dst_ie - pie);
	pnetwork_mlmeext->ie_length = offset + reमुख्यder_ielen;

	set_tx_beacon_cmd(padapter);
पूर्ण

अटल u8 chk_sta_is_alive(काष्ठा sta_info *psta)
अणु
	u8 ret = false;

	अगर ((psta->sta_stats.last_rx_data_pkts +
			psta->sta_stats.last_rx_ctrl_pkts) ==
			(psta->sta_stats.rx_data_pkts +
			psta->sta_stats.rx_ctrl_pkts))
		;
	अन्यथा
		ret = true;

	sta_update_last_rx_pkts(psta);

	वापस ret;
पूर्ण

व्योम expire_समयout_chk(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head *phead, *plist;
	u8 updated = 0;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 chk_alive_num = 0;
	अक्षर chk_alive_list[NUM_STA];
	पूर्णांक i;

	spin_lock_bh(&pstapriv->auth_list_lock);

	phead = &pstapriv->auth_list;
	plist = phead->next;

	/* check auth_queue */
	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, auth_list);
		plist = plist->next;

		अगर (psta->expire_to > 0) अणु
			psta->expire_to--;
			अगर (psta->expire_to == 0) अणु
				list_del_init(&psta->auth_list);
				pstapriv->auth_list_cnt--;

				DBG_88E("auth expire %6ph\n",
					psta->hwaddr);

				spin_unlock_bh(&pstapriv->auth_list_lock);

				spin_lock_bh(&pstapriv->sta_hash_lock);
				rtw_मुक्त_stainfo(padapter, psta);
				spin_unlock_bh(&pstapriv->sta_hash_lock);

				spin_lock_bh(&pstapriv->auth_list_lock);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pstapriv->auth_list_lock);

	psta = शून्य;

	spin_lock_bh(&pstapriv->asoc_list_lock);

	phead = &pstapriv->asoc_list;
	plist = phead->next;

	/* check asoc_queue */
	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, asoc_list);
		plist = plist->next;

		अगर (chk_sta_is_alive(psta) || !psta->expire_to) अणु
			psta->expire_to = pstapriv->expire_to;
			psta->keep_alive_trycnt = 0;
			psta->under_exist_checking = 0;
		पूर्ण अन्यथा अणु
			psta->expire_to--;
		पूर्ण

		अगर (psta->expire_to <= 0) अणु
			काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

			अगर (padapter->registrypriv.wअगरi_spec == 1) अणु
				psta->expire_to = pstapriv->expire_to;
				जारी;
			पूर्ण

			अगर (psta->state & WIFI_SLEEP_STATE) अणु
				अगर (!(psta->state & WIFI_STA_ALIVE_CHK_STATE)) अणु
					/* to check अगर alive by another methods
					 * अगर station is at ps mode.
					 */
					psta->expire_to = pstapriv->expire_to;
					psta->state |= WIFI_STA_ALIVE_CHK_STATE;

					/* to update bcn with tim_biपंचांगap
					 * क्रम this station
					 */
					pstapriv->tim_biपंचांगap |= BIT(psta->aid);
					update_beacon(padapter, WLAN_EID_TIM, शून्य,
						      false);

					अगर (!pmlmeext->active_keep_alive_check)
						जारी;
				पूर्ण
			पूर्ण
			अगर (pmlmeext->active_keep_alive_check) अणु
				पूर्णांक stainfo_offset;

				stainfo_offset =
					rtw_stainfo_offset(pstapriv, psta);
				अगर (stainfo_offset_valid(stainfo_offset))
					chk_alive_list[chk_alive_num++] =
						stainfo_offset;
				जारी;
			पूर्ण

			list_del_init(&psta->asoc_list);
			pstapriv->asoc_list_cnt--;

			DBG_88E("asoc expire %pM, state = 0x%x\n",
				(psta->hwaddr), psta->state);
			updated = ap_मुक्त_sta(padapter, psta, true,
					      WLAN_REASON_DEAUTH_LEAVING);
		पूर्ण अन्यथा अणु
			/* TODO: Aging mechanism to digest frames in sleep_q to aव्योम running out of xmitframe */
			अगर (psta->sleepq_len > (NR_XMITFRAME / pstapriv->asoc_list_cnt) &&
			    padapter->xmitpriv.मुक्त_xmitframe_cnt < (NR_XMITFRAME / pstapriv->asoc_list_cnt / 2)) अणु
				DBG_88E("%s sta:%pM, sleepq_len:%u, free_xmitframe_cnt:%u, asoc_list_cnt:%u, clear sleep_q\n", __func__,
					(psta->hwaddr), psta->sleepq_len,
					padapter->xmitpriv.मुक्त_xmitframe_cnt,
					pstapriv->asoc_list_cnt);
				wakeup_sta_to_xmit(padapter, psta);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&pstapriv->asoc_list_lock);

	अगर (chk_alive_num) अणु
		u8 backup_oper_channel = 0;
		काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
		/* चयन to correct channel of current network  beक्रमe issue keep-alive frames */
		अगर (rtw_get_oper_ch(padapter) != pmlmeext->cur_channel) अणु
			backup_oper_channel = rtw_get_oper_ch(padapter);
			SelectChannel(padapter, pmlmeext->cur_channel);
		पूर्ण

		/* issue null data to check sta alive*/
		क्रम (i = 0; i < chk_alive_num; i++) अणु
			पूर्णांक ret = _FAIL;

			psta = rtw_get_stainfo_by_offset(pstapriv,
							 chk_alive_list[i]);

			अगर (psta->state & WIFI_SLEEP_STATE) अणु
				ret = issue_nulldata(padapter, psta->hwaddr,
						     0, 1, 50);
			पूर्ण अन्यथा अणु
				ret = issue_nulldata(padapter, psta->hwaddr,
						     0, 3, 50);
			पूर्ण

			psta->keep_alive_trycnt++;
			अगर (ret == _SUCCESS) अणु
				DBG_88E("asoc check, sta(%pM) is alive\n",
					(psta->hwaddr));
				psta->expire_to = pstapriv->expire_to;
				psta->keep_alive_trycnt = 0;
				जारी;
			पूर्ण अन्यथा अगर (psta->keep_alive_trycnt <= 3) अणु
				DBG_88E("ack check for asoc expire, keep_alive_trycnt =%d\n", psta->keep_alive_trycnt);
				psta->expire_to = 1;
				जारी;
			पूर्ण

			psta->keep_alive_trycnt = 0;

			DBG_88E("asoc expire %pM, state = 0x%x\n",
				psta->hwaddr, psta->state);
			spin_lock_bh(&pstapriv->asoc_list_lock);
			list_del_init(&psta->asoc_list);
			pstapriv->asoc_list_cnt--;
			updated = ap_मुक्त_sta(padapter, psta, true,
					      WLAN_REASON_DEAUTH_LEAVING);
			spin_unlock_bh(&pstapriv->asoc_list_lock);
		पूर्ण

		अगर (backup_oper_channel > 0) /* back to the original operation channel */
			SelectChannel(padapter, backup_oper_channel);
	पूर्ण

	associated_clients_update(padapter, updated);
पूर्ण

व्योम add_RATid(काष्ठा adapter *padapter, काष्ठा sta_info *psta, u8 rssi_level)
अणु
	पूर्णांक i;
	u32 init_rate = 0;
	अचिन्हित अक्षर sta_band = 0, raid, लघुGIrate = false;
	अचिन्हित पूर्णांक tx_ra_biपंचांगap = 0;
	काष्ठा ht_priv	*psta_ht = शून्य;

	अगर (psta)
		psta_ht = &psta->htpriv;
	अन्यथा
		वापस;

	अगर (!(psta->state & _FW_LINKED))
		वापस;

	/* b/g mode ra_biपंचांगap */
	क्रम (i = 0; i < माप(psta->bssrateset); i++) अणु
		अगर (psta->bssrateset[i])
			tx_ra_biपंचांगap |= rtw_get_bit_value_from_ieee_value(psta->bssrateset[i] & 0x7f);
	पूर्ण
	/* n mode ra_biपंचांगap */
	अगर (psta_ht->ht_option) अणु
		क्रम (i = 0; i < 8; i++)
			अगर (psta_ht->ht_cap.mcs.rx_mask[0] & BIT(i))
				tx_ra_biपंचांगap |= BIT(i + 12);

		/* max लघु GI rate */
		लघुGIrate = psta_ht->sgi;
	पूर्ण

	अगर (tx_ra_biपंचांगap & 0xffff000)
		sta_band |= WIRELESS_11_24N | WIRELESS_11G | WIRELESS_11B;
	अन्यथा अगर (tx_ra_biपंचांगap & 0xff0)
		sta_band |= WIRELESS_11G | WIRELESS_11B;
	अन्यथा
		sta_band |= WIRELESS_11B;

	psta->wireless_mode = sta_band;

	raid = networktype_to_raid(sta_band);
	init_rate = get_highest_rate_idx(tx_ra_biपंचांगap & 0x0fffffff) & 0x3f;

	अगर (psta->aid < NUM_STA) अणु
		u8 arg = 0;

		arg = psta->mac_id & 0x1f;

		arg |= BIT(7);/* support entry 2~31 */

		अगर (लघुGIrate)
			arg |= BIT(5);

		tx_ra_biपंचांगap |= ((raid << 28) & 0xf0000000);

		DBG_88E("%s => mac_id:%d , raid:%d , bitmap = 0x%x, arg = 0x%x\n",
			__func__, psta->mac_id, raid, tx_ra_biपंचांगap, arg);

		/* biपंचांगap[0:27] = tx_rate_biपंचांगap */
		/* biपंचांगap[28:31]= Rate Adaptive id */
		/* arg[0:4] = macid */
		/* arg[5] = Short GI */
		rtw_hal_add_ra_tid(padapter, tx_ra_biपंचांगap, arg, rssi_level);

		अगर (लघुGIrate)
			init_rate |= BIT(6);

		/* set ra_id, init_rate */
		psta->raid = raid;
		psta->init_rate = init_rate;

	पूर्ण अन्यथा अणु
		DBG_88E("station aid %d exceed the max number\n", psta->aid);
	पूर्ण
पूर्ण

अटल व्योम update_bmc_sta(काष्ठा adapter *padapter)
अणु
	u32 init_rate = 0;
	अचिन्हित अक्षर	network_type, raid;
	पूर्णांक i, supportRateNum = 0;
	अचिन्हित पूर्णांक tx_ra_biपंचांगap = 0;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pcur_network = &pmlmepriv->cur_network.network;
	काष्ठा sta_info *psta = rtw_get_bcmc_stainfo(padapter);

	अगर (psta) अणु
		psta->aid = 0;/* शेष set to 0 */
		psta->mac_id = psta->aid + 1;

		psta->qos_option = 0;
		psta->htpriv.ht_option = false;

		psta->ieee8021x_blocked = 0;

		स_रखो(&psta->sta_stats, 0, माप(काष्ठा stainfo_stats));

		/* prepare क्रम add_RATid */
		supportRateNum = rtw_get_rateset_len((u8 *)&pcur_network->SupportedRates);
		network_type = rtw_check_network_type((u8 *)&pcur_network->SupportedRates);

		स_नकल(psta->bssrateset, &pcur_network->SupportedRates,
		       supportRateNum);
		psta->bssratelen = supportRateNum;

		/* b/g mode ra_biपंचांगap */
		क्रम (i = 0; i < supportRateNum; i++) अणु
			अगर (psta->bssrateset[i])
				tx_ra_biपंचांगap |= rtw_get_bit_value_from_ieee_value(psta->bssrateset[i] & 0x7f);
		पूर्ण

		/* क्रमce to b mode */
		network_type = WIRELESS_11B;
		tx_ra_biपंचांगap = 0xf;

		raid = networktype_to_raid(network_type);
		init_rate = get_highest_rate_idx(tx_ra_biपंचांगap & 0x0fffffff) &
			    0x3f;

		/* ap mode */
		rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, psta, true);

		अणु
			u8 arg = 0;

			arg = psta->mac_id & 0x1f;
			arg |= BIT(7);
			tx_ra_biपंचांगap |= ((raid << 28) & 0xf0000000);
			DBG_88E("%s, mask = 0x%x, arg = 0x%x\n", __func__,
				tx_ra_biपंचांगap, arg);

			/* biपंचांगap[0:27] = tx_rate_biपंचांगap */
			/* biपंचांगap[28:31]= Rate Adaptive id */
			/* arg[0:4] = macid */
			/* arg[5] = Short GI */
			rtw_hal_add_ra_tid(padapter, tx_ra_biपंचांगap, arg, 0);
		पूर्ण
		/* set ra_id, init_rate */
		psta->raid = raid;
		psta->init_rate = init_rate;

		rtw_stassoc_hw_rpt(padapter, psta);

		spin_lock_bh(&psta->lock);
		psta->state = _FW_LINKED;
		spin_unlock_bh(&psta->lock);

	पूर्ण अन्यथा अणु
		DBG_88E("add_RATid_bmc_sta error!\n");
	पूर्ण
पूर्ण

/* notes: */
/* AID: 1~MAX क्रम sta and 0 क्रम bc/mc in ap/adhoc mode */
/* MAC_ID = AID+1 क्रम sta in ap/adhoc mode */
/* MAC_ID = 1 क्रम bc/mc क्रम sta/ap/adhoc */
/* MAC_ID = 0 क्रम bssid क्रम sta/ap/adhoc */
/* CAM_ID = 0~3 क्रम शेष key, cmd_id = macid + 3, macid = aid+1; */

व्योम update_sta_info_apmode(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा ht_priv	*phtpriv_ap = &pmlmepriv->htpriv;
	काष्ठा ht_priv	*phtpriv_sta = &psta->htpriv;

	psta->mac_id = psta->aid + 1;

	/* ap mode */
	rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, psta, true);

	अगर (psecuritypriv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X)
		psta->ieee8021x_blocked = true;
	अन्यथा
		psta->ieee8021x_blocked = false;

	/* update sta's cap */

	/* ERP */
	VCS_update(padapter, psta);
	/* HT related cap */
	अगर (phtpriv_sta->ht_option) अणु
		/* check अगर sta supports rx ampdu */
		phtpriv_sta->ampdu_enable = phtpriv_ap->ampdu_enable;

		/* check अगर sta support s Short GI */
		अगर (le16_to_cpu(phtpriv_sta->ht_cap.cap_info &
				phtpriv_ap->ht_cap.cap_info) &
		    (IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40))
			phtpriv_sta->sgi = true;

		/*  bwmode */
		अगर (le16_to_cpu(phtpriv_sta->ht_cap.cap_info &
				phtpriv_ap->ht_cap.cap_info) &
		    IEEE80211_HT_CAP_SUP_WIDTH_20_40) अणु
			phtpriv_sta->bwmode = pmlmeext->cur_bwmode;
			phtpriv_sta->ch_offset = pmlmeext->cur_ch_offset;
		पूर्ण
		psta->qos_option = true;
	पूर्ण अन्यथा अणु
		phtpriv_sta->ampdu_enable = false;
		phtpriv_sta->sgi = false;
		phtpriv_sta->bwmode = HT_CHANNEL_WIDTH_20;
		phtpriv_sta->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	पूर्ण

	/* Rx AMPDU */
	send_delba(padapter, 0, psta->hwaddr);/*  recipient */

	/* TX AMPDU */
	send_delba(padapter, 1, psta->hwaddr);/* originator */
	phtpriv_sta->agg_enable_biपंचांगap = 0x0;/* reset */
	phtpriv_sta->candidate_tid_biपंचांगap = 0x0;/* reset */

	/* toकरो: init other variables */

	स_रखो(&psta->sta_stats, 0, माप(काष्ठा stainfo_stats));

	spin_lock_bh(&psta->lock);
	psta->state |= _FW_LINKED;
	spin_unlock_bh(&psta->lock);
पूर्ण

अटल व्योम update_hw_ht_param(काष्ठा adapter *padapter)
अणु
	u8 max_ampdu_len;
	u8 min_mpdu_spacing;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	/* handle A-MPDU parameter field
	 * ampdu_params_info [1:0]:Max AMPDU Len => 0:8k , 1:16k, 2:32k, 3:64k
	 * ampdu_params_info [4:2]:Min MPDU Start Spacing
	 */
	max_ampdu_len = pmlmeinfo->HT_caps.ampdu_params_info & 0x03;
	min_mpdu_spacing = (pmlmeinfo->HT_caps.ampdu_params_info & 0x1c) >> 2;

	rtw_hal_set_hwreg(padapter, HW_VAR_AMPDU_MIN_SPACE, &min_mpdu_spacing);
	rtw_hal_set_hwreg(padapter, HW_VAR_AMPDU_FACTOR, &max_ampdu_len);

	/* Config SM Power Save setting */
	pmlmeinfo->SM_PS = (le16_to_cpu(pmlmeinfo->HT_caps.cap_info) & 0x0C) >> 2;
	अगर (pmlmeinfo->SM_PS == WLAN_HT_CAP_SM_PS_STATIC)
		DBG_88E("%s(): WLAN_HT_CAP_SM_PS_STATIC\n", __func__);
पूर्ण

अटल व्योम start_bss_network(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	u8 *p;
	u8 val8, cur_channel, cur_bwmode, cur_ch_offset;
	u16 bcn_पूर्णांकerval;
	u32	acparm;
	uपूर्णांक	ie_len;
	काष्ठा registry_priv	 *pregpriv = &padapter->registrypriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmepriv->cur_network.network;
	काष्ठा mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork_mlmeext = &pmlmeinfo->network;
	काष्ठा HT_info_element *pht_info = शून्य;

	bcn_पूर्णांकerval = (u16)pnetwork->Configuration.BeaconPeriod;
	cur_channel = pnetwork->Configuration.DSConfig;
	cur_bwmode = HT_CHANNEL_WIDTH_20;
	cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	/* check अगर there is wps ie,
	 * अगर there is wpsie in beacon, the hostapd will update
	 * beacon twice when stating hostapd, and at first समय the
	 * security ie (RSN/WPA IE) will not include in beacon.
	 */
	अगर (!rtw_get_wps_ie(pnetwork->ies + _FIXED_IE_LENGTH_, pnetwork->ie_length - _FIXED_IE_LENGTH_, शून्य, शून्य))
		pmlmeext->bstart_bss = true;

	/* toकरो: update wmm, ht cap */
	अगर (pmlmepriv->qospriv.qos_option)
		pmlmeinfo->WMM_enable = true;
	अगर (pmlmepriv->htpriv.ht_option) अणु
		pmlmeinfo->WMM_enable = true;
		pmlmeinfo->HT_enable = true;

		update_hw_ht_param(padapter);
	पूर्ण

	/* setting only at  first समय */
	अगर (!pmlmepriv->cur_network.join_res) अणु
		/* WEP Key will be set beक्रमe this function, करो not
		 * clear CAM.
		 */
		अगर ((psecuritypriv->करोt11PrivacyAlgrthm != _WEP40_) &&
		    (psecuritypriv->करोt11PrivacyAlgrthm != _WEP104_))
			flush_all_cam_entry(padapter);	/* clear CAM */
	पूर्ण

	/* set MSR to AP_Mode */
	Set_MSR(padapter, _HW_STATE_AP_);

	/* Set BSSID REG */
	rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, pnetwork->MacAddress);

	/* Set EDCA param reg */
	acparm = 0x002F3217; /*  VO */
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VO, (u8 *)(&acparm));
	acparm = 0x005E4317; /*  VI */
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_VI, (u8 *)(&acparm));
	acparm = 0x005ea42b;
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BE, (u8 *)(&acparm));
	acparm = 0x0000A444; /*  BK */
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BK, (u8 *)(&acparm));

	/* Set Security */
	val8 = (psecuritypriv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X) ? 0xcc : 0xcf;
	rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

	/* Beacon Control related रेजिस्टर */
	rtw_hal_set_hwreg(padapter, HW_VAR_BEACON_INTERVAL,
			  (u8 *)(&bcn_पूर्णांकerval));

	UpdateBrateTbl(padapter, pnetwork->SupportedRates);
	rtw_hal_set_hwreg(padapter, HW_VAR_BASIC_RATE, pnetwork->SupportedRates);

	अगर (!pmlmepriv->cur_network.join_res) अणु /* setting only at  first समय */
		/* turn on all dynamic functions */
		Switch_DM_Func(padapter, DYNAMIC_ALL_FUNC_ENABLE, true);
	पूर्ण
	/* set channel, bwmode */
	p = rtw_get_ie(pnetwork->ies + माप(काष्ठा ndis_802_11_fixed_ie),
			WLAN_EID_HT_OPERATION, &ie_len,
		       pnetwork->ie_length -
		       माप(काष्ठा ndis_802_11_fixed_ie));
	अगर (p && ie_len) अणु
		pht_info = (काष्ठा HT_info_element *)(p + 2);

		अगर ((pregpriv->cbw40_enable) &&	 (pht_info->infos[0] & BIT(2))) अणु
			/* चयन to the 40M Hz mode */
			cur_bwmode = HT_CHANNEL_WIDTH_40;
			चयन (pht_info->infos[0] & 0x3) अणु
			हाल 1:
				cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
				अवरोध;
			हाल 3:
				cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
				अवरोध;
			शेष:
				cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/* TODO: need to judge the phy parameters on concurrent
	 * mode क्रम single phy
	 */
	set_channel_bwmode(padapter, cur_channel, cur_ch_offset, cur_bwmode);

	DBG_88E("CH =%d, BW =%d, offset =%d\n", cur_channel, cur_bwmode,
		cur_ch_offset);

	/*  */
	pmlmeext->cur_channel = cur_channel;
	pmlmeext->cur_bwmode = cur_bwmode;
	pmlmeext->cur_ch_offset = cur_ch_offset;
	pmlmeext->cur_wireless_mode = pmlmepriv->cur_network.network_type;

	/* update cur_wireless_mode */
	update_wireless_mode(padapter);

	/* update capability after cur_wireless_mode updated */
	update_capinfo(padapter, rtw_get_capability(pnetwork));

	/* let pnetwork_mlmeext == pnetwork_mlme. */
	स_नकल(pnetwork_mlmeext, pnetwork, pnetwork->Length);

	अगर (pmlmeext->bstart_bss) अणु
		update_beacon(padapter, WLAN_EID_TIM, शून्य, false);

		/* issue beacon frame */
		अगर (send_beacon(padapter) == _FAIL)
			DBG_88E("send_beacon, fail!\n");
	पूर्ण

	/* update bc/mc sta_info */
	update_bmc_sta(padapter);
पूर्ण

पूर्णांक rtw_check_beacon_data(काष्ठा adapter *padapter, u8 *pbuf,  पूर्णांक len)
अणु
	पूर्णांक ret = _SUCCESS;
	u8 *p;
	u8 *pHT_caps_ie = शून्य;
	u8 *pHT_info_ie = शून्य;
	काष्ठा sta_info *psta = शून्य;
	u16 cap, ht_cap = false;
	uपूर्णांक ie_len = 0;
	पूर्णांक group_cipher, pairwise_cipher;
	u8	channel, network_type, supportRate[NDIS_802_11_LENGTH_RATES_EX];
	पूर्णांक supportRateNum = 0;
	u8 OUI1[] = अणु0x00, 0x50, 0xf2, 0x01पूर्ण;
	u8 WMM_PARA_IE[] = अणु0x00, 0x50, 0xf2, 0x02, 0x01, 0x01पूर्ण;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pbss_network = &pmlmepriv->cur_network.network;
	u8 *ie = pbss_network->ies;

	/* SSID */
	/* Supported rates */
	/* DS Params */
	/* WLAN_EID_COUNTRY */
	/* ERP Inक्रमmation element */
	/* Extended supported rates */
	/* WPA/WPA2 */
	/* Wi-Fi Wireless Mulसमयdia Extensions */
	/* ht_capab, ht_oper */
	/* WPS IE */

	DBG_88E("%s, len =%d\n", __func__, len);

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस _FAIL;

	अगर (len < 0 || len > MAX_IE_SZ)
		वापस _FAIL;

	pbss_network->ie_length = len;

	स_रखो(ie, 0, MAX_IE_SZ);

	स_नकल(ie, pbuf, pbss_network->ie_length);

	अगर (pbss_network->Infraकाष्ठाureMode != Ndis802_11APMode)
		वापस _FAIL;

	pbss_network->Rssi = 0;

	ether_addr_copy(pbss_network->MacAddress, myid(&padapter->eeprompriv));

	/* beacon पूर्णांकerval */
	p = rtw_get_beacon_पूर्णांकerval_from_ie(ie);/* 8: TimeStamp, 2: Beacon Interval 2:Capability */
	pbss_network->Configuration.BeaconPeriod = get_unaligned_le16(p);

	/* capability */
	cap = get_unaligned_le16(ie);

	/* SSID */
	p = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_SSID, &ie_len,
		       pbss_network->ie_length - _BEACON_IE_OFFSET_);
	अगर (p && ie_len > 0) अणु
		ie_len = min_t(पूर्णांक, ie_len, माप(pbss_network->ssid.ssid));
		स_रखो(&pbss_network->ssid, 0, माप(काष्ठा ndis_802_11_ssid));
		स_नकल(pbss_network->ssid.ssid, p + 2, ie_len);
		pbss_network->ssid.ssid_length = ie_len;
	पूर्ण

	/* channel */
	channel = 0;
	pbss_network->Configuration.Length = 0;
	p = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_DS_PARAMS, &ie_len,
		       (pbss_network->ie_length - _BEACON_IE_OFFSET_));
	अगर (p && ie_len > 0)
		channel = *(p + 2);

	pbss_network->Configuration.DSConfig = channel;

	स_रखो(supportRate, 0, NDIS_802_11_LENGTH_RATES_EX);
	/*  get supported rates */
	p = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_SUPP_RATES, &ie_len,
		       pbss_network->ie_length - _BEACON_IE_OFFSET_);
	अगर (p) अणु
		ie_len = min_t(पूर्णांक, ie_len, NDIS_802_11_LENGTH_RATES_EX);
		स_नकल(supportRate, p + 2, ie_len);
		supportRateNum = ie_len;
	पूर्ण

	/* get ext_supported rates */
	p = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_EXT_SUPP_RATES,
		       &ie_len, pbss_network->ie_length - _BEACON_IE_OFFSET_);
	अगर (p) अणु
		ie_len = min_t(पूर्णांक, ie_len,
			       NDIS_802_11_LENGTH_RATES_EX - supportRateNum);
		स_नकल(supportRate + supportRateNum, p + 2, ie_len);
		supportRateNum += ie_len;
	पूर्ण

	network_type = rtw_check_network_type(supportRate);

	rtw_set_supported_rate(pbss_network->SupportedRates, network_type);

	/* parsing ERP_IE */
	p = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_ERP_INFO, &ie_len,
		       pbss_network->ie_length - _BEACON_IE_OFFSET_);
	अगर (p && ie_len > 0)
		ERP_IE_handler(padapter, (काष्ठा ndis_802_11_var_ie *)p);

	/* update privacy/security */
	अगर (cap & BIT(4))
		pbss_network->Privacy = 1;
	अन्यथा
		pbss_network->Privacy = 0;

	psecuritypriv->wpa_psk = 0;

	/* wpa2 */
	group_cipher = 0;
	pairwise_cipher = 0;
	psecuritypriv->wpa2_group_cipher = _NO_PRIVACY_;
	psecuritypriv->wpa2_pairwise_cipher = _NO_PRIVACY_;
	p = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_RSN, &ie_len,
		       pbss_network->ie_length - _BEACON_IE_OFFSET_);
	अगर (p && ie_len > 0) अणु
		अगर (rtw_parse_wpa2_ie(p, ie_len + 2, &group_cipher, &pairwise_cipher, शून्य) == _SUCCESS) अणु
			psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;

			psecuritypriv->करोt8021xalg = 1;/* psk,  toकरो:802.1x */
			psecuritypriv->wpa_psk |= BIT(1);

			psecuritypriv->wpa2_group_cipher = group_cipher;
			psecuritypriv->wpa2_pairwise_cipher = pairwise_cipher;
		पूर्ण
	पूर्ण
	/* wpa */
	ie_len = 0;
	group_cipher = 0;
	pairwise_cipher = 0;
	psecuritypriv->wpa_group_cipher = _NO_PRIVACY_;
	psecuritypriv->wpa_pairwise_cipher = _NO_PRIVACY_;
	क्रम (p = ie + _BEACON_IE_OFFSET_;; p += (ie_len + 2)) अणु
		p = rtw_get_ie(p, WLAN_EID_VENDOR_SPECIFIC, &ie_len,
			       pbss_network->ie_length - _BEACON_IE_OFFSET_ - (ie_len + 2));
		अगर ((p) && (!स_भेद(p + 2, OUI1, 4))) अणु
			अगर (rtw_parse_wpa_ie(p, ie_len + 2, &group_cipher,
					     &pairwise_cipher, शून्य) == _SUCCESS) अणु
				psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;

				psecuritypriv->करोt8021xalg = 1;/* psk,  toकरो:802.1x */

				psecuritypriv->wpa_psk |= BIT(0);

				psecuritypriv->wpa_group_cipher = group_cipher;
				psecuritypriv->wpa_pairwise_cipher = pairwise_cipher;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर ((!p) || (ie_len == 0))
			अवरोध;
	पूर्ण

	/* wmm */
	ie_len = 0;
	pmlmepriv->qospriv.qos_option = 0;
	अगर (pregistrypriv->wmm_enable) अणु
		क्रम (p = ie + _BEACON_IE_OFFSET_;; p += (ie_len + 2)) अणु
			p = rtw_get_ie(p, WLAN_EID_VENDOR_SPECIFIC, &ie_len,
				       pbss_network->ie_length - _BEACON_IE_OFFSET_ - (ie_len + 2));
			अगर ((p) && !स_भेद(p + 2, WMM_PARA_IE, 6)) अणु
				pmlmepriv->qospriv.qos_option = 1;

				/* QoS Info, support U-APSD */
				*(p + 8) |= BIT(7);

				/* disable all ACM bits since the WMM
				 * admission control is not supported
				 */
				*(p + 10) &= ~BIT(4); /* BE */
				*(p + 14) &= ~BIT(4); /* BK */
				*(p + 18) &= ~BIT(4); /* VI */
				*(p + 22) &= ~BIT(4); /* VO */
				अवरोध;
			पूर्ण

			अगर ((!p) || (ie_len == 0))
				अवरोध;
		पूर्ण
	पूर्ण
	/* parsing HT_CAP_IE */
	p = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_HT_CAPABILITY, &ie_len,
		       pbss_network->ie_length - _BEACON_IE_OFFSET_);
	अगर (p && ie_len > 0) अणु
		काष्ठा ieee80211_ht_cap *pht_cap = (काष्ठा ieee80211_ht_cap *)(p + 2);

		pHT_caps_ie = p;
		ht_cap = true;
		network_type |= WIRELESS_11_24N;

		अगर ((psecuritypriv->wpa_pairwise_cipher & WPA_CIPHER_CCMP) ||
		    (psecuritypriv->wpa2_pairwise_cipher & WPA_CIPHER_CCMP))
			pht_cap->ampdu_params_info |= (IEEE80211_HT_AMPDU_PARM_DENSITY & (0x07 << 2));
		अन्यथा
			pht_cap->ampdu_params_info |= (IEEE80211_HT_AMPDU_PARM_DENSITY & 0x00);

		/* set  Max Rx AMPDU size  to 64K */
		pht_cap->ampdu_params_info |= (IEEE80211_HT_AMPDU_PARM_FACTOR & 0x03);

		pht_cap->mcs.rx_mask[0] = 0xff;
		pht_cap->mcs.rx_mask[1] = 0x0;
		ie_len = min_t(पूर्णांक, ie_len, माप(pmlmepriv->htpriv.ht_cap));
		स_नकल(&pmlmepriv->htpriv.ht_cap, p + 2, ie_len);
	पूर्ण

	/* parsing HT_INFO_IE */
	p = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_HT_OPERATION, &ie_len,
		       pbss_network->ie_length - _BEACON_IE_OFFSET_);
	अगर (p && ie_len > 0)
		pHT_info_ie = p;
	चयन (network_type) अणु
	हाल WIRELESS_11B:
		pbss_network->NetworkTypeInUse = Ndis802_11DS;
		अवरोध;
	हाल WIRELESS_11G:
	हाल WIRELESS_11BG:
	हाल WIRELESS_11G_24N:
	हाल WIRELESS_11BG_24N:
		pbss_network->NetworkTypeInUse = Ndis802_11OFDM24;
		अवरोध;
	हाल WIRELESS_11A:
		pbss_network->NetworkTypeInUse = Ndis802_11OFDM5;
		अवरोध;
	शेष:
		pbss_network->NetworkTypeInUse = Ndis802_11OFDM24;
		अवरोध;
	पूर्ण

	pmlmepriv->cur_network.network_type = network_type;

	pmlmepriv->htpriv.ht_option = false;

	अगर ((psecuritypriv->wpa2_pairwise_cipher & WPA_CIPHER_TKIP) ||
	    (psecuritypriv->wpa_pairwise_cipher & WPA_CIPHER_TKIP)) अणु
		/* toकरो: */
		/* ht_cap = false; */
	पूर्ण

	/* ht_cap */
	अगर (pregistrypriv->ht_enable && ht_cap) अणु
		pmlmepriv->htpriv.ht_option = true;
		pmlmepriv->qospriv.qos_option = 1;

		अगर (pregistrypriv->ampdu_enable == 1)
			pmlmepriv->htpriv.ampdu_enable = true;
		HT_caps_handler(padapter, (काष्ठा ndis_802_11_var_ie *)pHT_caps_ie);

		HT_info_handler(padapter, (काष्ठा ndis_802_11_var_ie *)pHT_info_ie);
	पूर्ण

	pbss_network->Length = get_wlan_bssid_ex_sz(pbss_network);

	/* issue beacon to start bss network */
	start_bss_network(padapter, (u8 *)pbss_network);

	/* alloc sta_info क्रम ap itself */
	psta = rtw_get_stainfo(&padapter->stapriv, pbss_network->MacAddress);
	अगर (!psta) अणु
		psta = rtw_alloc_stainfo(&padapter->stapriv, pbss_network->MacAddress);
		अगर (!psta)
			वापस _FAIL;
	पूर्ण

	/* fix bug of flush_cam_entry at STOP AP mode */
	psta->state |= WIFI_AP_STATE;
	rtw_indicate_connect(padapter);
	pmlmepriv->cur_network.join_res = true;/* क्रम check अगर alपढ़ोy set beacon */
	वापस ret;
पूर्ण

व्योम rtw_set_macaddr_acl(काष्ठा adapter *padapter, पूर्णांक mode)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;

	DBG_88E("%s, mode =%d\n", __func__, mode);

	pacl_list->mode = mode;
पूर्ण

पूर्णांक rtw_acl_add_sta(काष्ठा adapter *padapter, u8 *addr)
अणु
	काष्ठा list_head *plist, *phead;
	u8 added = false;
	पूर्णांक i, ret = 0;
	काष्ठा rtw_wlan_acl_node *paclnode;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	काष्ठा __queue *pacl_node_q = &pacl_list->acl_node_q;

	DBG_88E("%s(acl_num =%d) =%pM\n", __func__, pacl_list->num, (addr));

	अगर ((NUM_ACL - 1) < pacl_list->num)
		वापस -1;

	spin_lock_bh(&pacl_node_q->lock);

	phead = get_list_head(pacl_node_q);
	plist = phead->next;

	जबतक (phead != plist) अणु
		paclnode = container_of(plist, काष्ठा rtw_wlan_acl_node, list);
		plist = plist->next;

		अगर (!स_भेद(paclnode->addr, addr, ETH_ALEN)) अणु
			अगर (paclnode->valid) अणु
				added = true;
				DBG_88E("%s, sta has been added\n", __func__);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&pacl_node_q->lock);

	अगर (added)
		वापस ret;

	spin_lock_bh(&pacl_node_q->lock);

	क्रम (i = 0; i < NUM_ACL; i++) अणु
		paclnode = &pacl_list->aclnode[i];

		अगर (!paclnode->valid) अणु
			INIT_LIST_HEAD(&paclnode->list);

			ether_addr_copy(paclnode->addr, addr);

			paclnode->valid = true;

			list_add_tail(&paclnode->list, get_list_head(pacl_node_q));

			pacl_list->num++;

			अवरोध;
		पूर्ण
	पूर्ण

	DBG_88E("%s, acl_num =%d\n", __func__, pacl_list->num);

	spin_unlock_bh(&pacl_node_q->lock);

	वापस ret;
पूर्ण

पूर्णांक rtw_acl_हटाओ_sta(काष्ठा adapter *padapter, u8 *addr)
अणु
	काष्ठा list_head *plist, *phead;
	काष्ठा rtw_wlan_acl_node *paclnode;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	काष्ठा __queue *pacl_node_q = &pacl_list->acl_node_q;

	DBG_88E("%s(acl_num =%d) =%pM\n", __func__, pacl_list->num, (addr));

	spin_lock_bh(&pacl_node_q->lock);

	phead = get_list_head(pacl_node_q);
	plist = phead->next;

	जबतक (phead != plist) अणु
		paclnode = container_of(plist, काष्ठा rtw_wlan_acl_node, list);
		plist = plist->next;

		अगर (!स_भेद(paclnode->addr, addr, ETH_ALEN)) अणु
			अगर (paclnode->valid) अणु
				paclnode->valid = false;

				list_del_init(&paclnode->list);

				pacl_list->num--;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&pacl_node_q->lock);

	DBG_88E("%s, acl_num =%d\n", __func__, pacl_list->num);
	वापस 0;
पूर्ण

अटल व्योम update_bcn_erpinfo_ie(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	अचिन्हित अक्षर *p, *ie = pnetwork->ies;
	u32 len = 0;

	DBG_88E("%s, ERP_enable =%d\n", __func__, pmlmeinfo->ERP_enable);

	अगर (!pmlmeinfo->ERP_enable)
		वापस;

	/* parsing ERP_IE */
	p = rtw_get_ie(ie + _BEACON_IE_OFFSET_, WLAN_EID_ERP_INFO, &len,
		       (pnetwork->ie_length - _BEACON_IE_OFFSET_));
	अगर (p && len > 0) अणु
		काष्ठा ndis_802_11_var_ie *pIE = (काष्ठा ndis_802_11_var_ie *)p;

		अगर (pmlmepriv->num_sta_non_erp == 1)
			pIE->data[0] |= RTW_ERP_INFO_NON_ERP_PRESENT |
					RTW_ERP_INFO_USE_PROTECTION;
		अन्यथा
			pIE->data[0] &= ~(RTW_ERP_INFO_NON_ERP_PRESENT |
					  RTW_ERP_INFO_USE_PROTECTION);

		अगर (pmlmepriv->num_sta_no_लघु_preamble > 0)
			pIE->data[0] |= RTW_ERP_INFO_BARKER_PREAMBLE_MODE;
		अन्यथा
			pIE->data[0] &= ~(RTW_ERP_INFO_BARKER_PREAMBLE_MODE);

		ERP_IE_handler(padapter, pIE);
	पूर्ण
पूर्ण

अटल व्योम update_bcn_wps_ie(काष्ठा adapter *padapter)
अणु
	u8 *pwps_ie = शून्य, *pwps_ie_src;
	u8 *preमुख्यder_ie, *pbackup_reमुख्यder_ie = शून्य;
	uपूर्णांक wps_ielen = 0, wps_offset, reमुख्यder_ielen;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork = &pmlmeinfo->network;
	अचिन्हित अक्षर *ie = pnetwork->ies;
	u32 ielen = pnetwork->ie_length;

	pwps_ie_src = pmlmepriv->wps_beacon_ie;
	अगर (!pwps_ie_src)
		वापस;

	pwps_ie = rtw_get_wps_ie(ie + _FIXED_IE_LENGTH_,
				 ielen - _FIXED_IE_LENGTH_, शून्य, &wps_ielen);

	अगर (!pwps_ie || wps_ielen == 0)
		वापस;

	wps_offset = (uपूर्णांक)(pwps_ie - ie);

	preमुख्यder_ie = pwps_ie + wps_ielen;

	reमुख्यder_ielen = ielen - wps_offset - wps_ielen;

	अगर (reमुख्यder_ielen > 0) अणु
		pbackup_reमुख्यder_ie = rtw_दो_स्मृति(reमुख्यder_ielen);
		अगर (pbackup_reमुख्यder_ie)
			स_नकल(pbackup_reमुख्यder_ie, preमुख्यder_ie, reमुख्यder_ielen);
	पूर्ण

	wps_ielen = (uपूर्णांक)pwps_ie_src[1];/* to get ie data len */
	अगर (wps_offset + wps_ielen + 2 + reमुख्यder_ielen <= MAX_IE_SZ) अणु
		स_नकल(pwps_ie, pwps_ie_src, wps_ielen + 2);
		pwps_ie += wps_ielen + 2;

		अगर (pbackup_reमुख्यder_ie)
			स_नकल(pwps_ie, pbackup_reमुख्यder_ie, reमुख्यder_ielen);

		/* update ie_length */
		pnetwork->ie_length = wps_offset + wps_ielen + 2 + reमुख्यder_ielen;
	पूर्ण

	kमुक्त(pbackup_reमुख्यder_ie);
पूर्ण

अटल व्योम update_bcn_venकरोr_spec_ie(काष्ठा adapter *padapter, u8 *oui)
अणु

	अगर (!स_भेद(WPS_OUI, oui, 4))
		update_bcn_wps_ie(padapter);
	अन्यथा
		DBG_88E("unknown OUI type!\n");
पूर्ण

व्योम update_beacon(काष्ठा adapter *padapter, u8 ie_id, u8 *oui, u8 tx)
अणु
	काष्ठा mlme_priv *pmlmepriv;
	काष्ठा mlme_ext_priv	*pmlmeext;

	अगर (!padapter)
		वापस;

	pmlmepriv = &padapter->mlmepriv;
	pmlmeext = &padapter->mlmeextpriv;

	अगर (!pmlmeext->bstart_bss)
		वापस;

	spin_lock_bh(&pmlmepriv->bcn_update_lock);

	चयन (ie_id) अणु
	हाल WLAN_EID_TIM:
		update_BCNTIM(padapter);
		अवरोध;
	हाल WLAN_EID_ERP_INFO:
		update_bcn_erpinfo_ie(padapter);
		अवरोध;
	हाल WLAN_EID_VENDOR_SPECIFIC:
		update_bcn_venकरोr_spec_ie(padapter, oui);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	pmlmepriv->update_bcn = true;

	spin_unlock_bh(&pmlmepriv->bcn_update_lock);

	अगर (tx)
		set_tx_beacon_cmd(padapter);
पूर्ण

/*
 * op_mode
 * Set to 0 (HT pure) under the following conditions
 *	- all STAs in the BSS are 20/40 MHz HT in 20/40 MHz BSS or
 *	- all STAs in the BSS are 20 MHz HT in 20 MHz BSS
 * Set to 1 (HT non-member protection) अगर there may be non-HT STAs
 *	  in both the primary and the secondary channel
 * Set to 2 अगर only HT STAs are associated in BSS,
 *	  however and at least one 20 MHz HT STA is associated
 * Set to 3 (HT mixed mode) when one or more non-HT STAs are associated
 *	  (currently non-GF HT station is considered as non-HT STA also)
 */
अटल पूर्णांक rtw_ht_operation_update(काष्ठा adapter *padapter)
अणु
	u16 cur_op_mode, new_op_mode;
	पूर्णांक op_mode_changes = 0;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv	*phtpriv_ap = &pmlmepriv->htpriv;

	अगर (pmlmepriv->htpriv.ht_option)
		वापस 0;

	DBG_88E("%s current operation mode = 0x%X\n",
		__func__, pmlmepriv->ht_op_mode);

	अगर (!(pmlmepriv->ht_op_mode & HT_INFO_OPERATION_MODE_NON_GF_DEVS_PRESENT) &&
	    pmlmepriv->num_sta_ht_no_gf) अणु
		pmlmepriv->ht_op_mode |=
			HT_INFO_OPERATION_MODE_NON_GF_DEVS_PRESENT;
		op_mode_changes++;
	पूर्ण अन्यथा अगर ((pmlmepriv->ht_op_mode &
		   HT_INFO_OPERATION_MODE_NON_GF_DEVS_PRESENT) &&
		   pmlmepriv->num_sta_ht_no_gf == 0) अणु
		pmlmepriv->ht_op_mode &=
			~HT_INFO_OPERATION_MODE_NON_GF_DEVS_PRESENT;
		op_mode_changes++;
	पूर्ण

	अगर (!(pmlmepriv->ht_op_mode & HT_INFO_OPERATION_MODE_NON_HT_STA_PRESENT) &&
	    (pmlmepriv->num_sta_no_ht || pmlmepriv->olbc_ht)) अणु
		pmlmepriv->ht_op_mode |= HT_INFO_OPERATION_MODE_NON_HT_STA_PRESENT;
		op_mode_changes++;
	पूर्ण अन्यथा अगर ((pmlmepriv->ht_op_mode &
		    HT_INFO_OPERATION_MODE_NON_HT_STA_PRESENT) &&
		   (pmlmepriv->num_sta_no_ht == 0 && !pmlmepriv->olbc_ht)) अणु
		pmlmepriv->ht_op_mode &=
			~HT_INFO_OPERATION_MODE_NON_HT_STA_PRESENT;
		op_mode_changes++;
	पूर्ण

	/* Note: currently we चयन to the MIXED op mode अगर HT non-greenfield
	 * station is associated. Probably it's a theoretical हाल, since
	 * it looks like all known HT STAs support greenfield.
	 */
	new_op_mode = 0;
	अगर (pmlmepriv->num_sta_no_ht ||
	    (pmlmepriv->ht_op_mode & HT_INFO_OPERATION_MODE_NON_GF_DEVS_PRESENT))
		new_op_mode = OP_MODE_MIXED;
	अन्यथा अगर ((le16_to_cpu(phtpriv_ap->ht_cap.cap_info) &
		  IEEE80211_HT_CAP_SUP_WIDTH_20_40) &&
		 pmlmepriv->num_sta_ht_20mhz)
		new_op_mode = OP_MODE_20MHZ_HT_STA_ASSOCED;
	अन्यथा अगर (pmlmepriv->olbc_ht)
		new_op_mode = OP_MODE_MAY_BE_LEGACY_STAS;
	अन्यथा
		new_op_mode = OP_MODE_PURE;

	cur_op_mode = pmlmepriv->ht_op_mode & HT_INFO_OPERATION_MODE_OP_MODE_MASK;
	अगर (cur_op_mode != new_op_mode) अणु
		pmlmepriv->ht_op_mode &= ~HT_INFO_OPERATION_MODE_OP_MODE_MASK;
		pmlmepriv->ht_op_mode |= new_op_mode;
		op_mode_changes++;
	पूर्ण

	DBG_88E("%s new operation mode = 0x%X changes =%d\n",
		__func__, pmlmepriv->ht_op_mode, op_mode_changes);

	वापस op_mode_changes;
पूर्ण

व्योम associated_clients_update(काष्ठा adapter *padapter, u8 updated)
अणु
	/* update associated stations cap. */
	अगर (updated) अणु
		काष्ठा list_head *phead, *plist;
		काष्ठा sta_info *psta = शून्य;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		spin_lock_bh(&pstapriv->asoc_list_lock);

		phead = &pstapriv->asoc_list;
		plist = phead->next;

		/* check asoc_queue */
		जबतक (phead != plist) अणु
			psta = container_of(plist, काष्ठा sta_info, asoc_list);

			plist = plist->next;

			VCS_update(padapter, psta);
		पूर्ण
		spin_unlock_bh(&pstapriv->asoc_list_lock);
	पूर्ण
पूर्ण

/* called > TSR LEVEL क्रम USB or SDIO Interface*/
व्योम bss_cap_update_on_sta_join(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 beacon_updated = false;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	अगर (!(psta->flags & WLAN_STA_SHORT_PREAMBLE)) अणु
		अगर (!psta->no_लघु_preamble_set) अणु
			psta->no_लघु_preamble_set = 1;

			pmlmepriv->num_sta_no_लघु_preamble++;

			अगर ((pmlmeext->cur_wireless_mode > WIRELESS_11B) &&
			    (pmlmepriv->num_sta_no_लघु_preamble == 1)) अणु
				beacon_updated = true;
				update_beacon(padapter, 0xFF, शून्य, true);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (psta->no_लघु_preamble_set) अणु
			psta->no_लघु_preamble_set = 0;

			pmlmepriv->num_sta_no_लघु_preamble--;

			अगर ((pmlmeext->cur_wireless_mode > WIRELESS_11B) &&
			    (pmlmepriv->num_sta_no_लघु_preamble == 0)) अणु
				beacon_updated = true;
				update_beacon(padapter, 0xFF, शून्य, true);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (psta->flags & WLAN_STA_NONERP) अणु
		अगर (!psta->nonerp_set) अणु
			psta->nonerp_set = 1;

			pmlmepriv->num_sta_non_erp++;

			अगर (pmlmepriv->num_sta_non_erp == 1) अणु
				beacon_updated = true;
				update_beacon(padapter, WLAN_EID_ERP_INFO, शून्य, true);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (psta->nonerp_set) अणु
			psta->nonerp_set = 0;

			pmlmepriv->num_sta_non_erp--;

			अगर (pmlmepriv->num_sta_non_erp == 0) अणु
				beacon_updated = true;
				update_beacon(padapter, WLAN_EID_ERP_INFO, शून्य, true);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!(psta->capability & WLAN_CAPABILITY_SHORT_SLOT_TIME)) अणु
		अगर (!psta->no_लघु_slot_समय_set) अणु
			psta->no_लघु_slot_समय_set = 1;

			pmlmepriv->num_sta_no_लघु_slot_समय++;

			अगर ((pmlmeext->cur_wireless_mode > WIRELESS_11B) &&
			    (pmlmepriv->num_sta_no_लघु_slot_समय == 1)) अणु
				beacon_updated = true;
				update_beacon(padapter, 0xFF, शून्य, true);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (psta->no_लघु_slot_समय_set) अणु
			psta->no_लघु_slot_समय_set = 0;

			pmlmepriv->num_sta_no_लघु_slot_समय--;

			अगर ((pmlmeext->cur_wireless_mode > WIRELESS_11B) &&
			    (pmlmepriv->num_sta_no_लघु_slot_समय == 0)) अणु
				beacon_updated = true;
				update_beacon(padapter, 0xFF, शून्य, true);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (psta->flags & WLAN_STA_HT) अणु
		u16 ht_capab = le16_to_cpu(psta->htpriv.ht_cap.cap_info);

		DBG_88E("HT: STA %pM HT Capabilities Info: 0x%04x\n",
			(psta->hwaddr), ht_capab);

		अगर (psta->no_ht_set) अणु
			psta->no_ht_set = 0;
			pmlmepriv->num_sta_no_ht--;
		पूर्ण

		अगर ((ht_capab & IEEE80211_HT_CAP_GRN_FLD) == 0) अणु
			अगर (!psta->no_ht_gf_set) अणु
				psta->no_ht_gf_set = 1;
				pmlmepriv->num_sta_ht_no_gf++;
			पूर्ण
			DBG_88E("%s STA %pM - no greenfield, num of non-gf stations %d\n",
				__func__, (psta->hwaddr),
				pmlmepriv->num_sta_ht_no_gf);
		पूर्ण

		अगर ((ht_capab & IEEE80211_HT_CAP_SUP_WIDTH_20_40) == 0) अणु
			अगर (!psta->ht_20mhz_set) अणु
				psta->ht_20mhz_set = 1;
				pmlmepriv->num_sta_ht_20mhz++;
			पूर्ण
			DBG_88E("%s STA %pM - 20 MHz HT, num of 20MHz HT STAs %d\n",
				__func__, (psta->hwaddr),
				pmlmepriv->num_sta_ht_20mhz);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!psta->no_ht_set) अणु
			psta->no_ht_set = 1;
			pmlmepriv->num_sta_no_ht++;
		पूर्ण
		अगर (pmlmepriv->htpriv.ht_option) अणु
			DBG_88E("%s STA %pM - no HT, num of non-HT stations %d\n",
				__func__, (psta->hwaddr),
				pmlmepriv->num_sta_no_ht);
		पूर्ण
	पूर्ण

	अगर (rtw_ht_operation_update(padapter) > 0) अणु
		update_beacon(padapter, WLAN_EID_HT_CAPABILITY, शून्य, false);
		update_beacon(padapter, WLAN_EID_HT_OPERATION, शून्य, true);
	पूर्ण

	/* update associated stations cap. */
	associated_clients_update(padapter,  beacon_updated);

	DBG_88E("%s, updated =%d\n", __func__, beacon_updated);
पूर्ण

u8 bss_cap_update_on_sta_leave(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 beacon_updated = false;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	अगर (!psta)
		वापस beacon_updated;

	अगर (psta->no_लघु_preamble_set) अणु
		psta->no_लघु_preamble_set = 0;
		pmlmepriv->num_sta_no_लघु_preamble--;
		अगर (pmlmeext->cur_wireless_mode > WIRELESS_11B &&
		    pmlmepriv->num_sta_no_लघु_preamble == 0) अणु
			beacon_updated = true;
			update_beacon(padapter, 0xFF, शून्य, true);
		पूर्ण
	पूर्ण

	अगर (psta->nonerp_set) अणु
		psta->nonerp_set = 0;
		pmlmepriv->num_sta_non_erp--;
		अगर (pmlmepriv->num_sta_non_erp == 0) अणु
			beacon_updated = true;
			update_beacon(padapter, WLAN_EID_ERP_INFO, शून्य, true);
		पूर्ण
	पूर्ण

	अगर (psta->no_लघु_slot_समय_set) अणु
		psta->no_लघु_slot_समय_set = 0;
		pmlmepriv->num_sta_no_लघु_slot_समय--;
		अगर (pmlmeext->cur_wireless_mode > WIRELESS_11B &&
		    pmlmepriv->num_sta_no_लघु_slot_समय == 0) अणु
			beacon_updated = true;
			update_beacon(padapter, 0xFF, शून्य, true);
		पूर्ण
	पूर्ण

	अगर (psta->no_ht_gf_set) अणु
		psta->no_ht_gf_set = 0;
		pmlmepriv->num_sta_ht_no_gf--;
	पूर्ण

	अगर (psta->no_ht_set) अणु
		psta->no_ht_set = 0;
		pmlmepriv->num_sta_no_ht--;
	पूर्ण

	अगर (psta->ht_20mhz_set) अणु
		psta->ht_20mhz_set = 0;
		pmlmepriv->num_sta_ht_20mhz--;
	पूर्ण

	अगर (rtw_ht_operation_update(padapter) > 0) अणु
		update_beacon(padapter, WLAN_EID_HT_CAPABILITY, शून्य, false);
		update_beacon(padapter, WLAN_EID_HT_OPERATION, शून्य, true);
	पूर्ण

	/* update associated stations cap. */

	DBG_88E("%s, updated =%d\n", __func__, beacon_updated);

	वापस beacon_updated;
पूर्ण

u8 ap_मुक्त_sta(काष्ठा adapter *padapter, काष्ठा sta_info *psta,
	       bool active, u16 reason)
अणु
	u8 beacon_updated = false;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	अगर (!psta)
		वापस beacon_updated;

	/* tear करोwn Rx AMPDU */
	send_delba(padapter, 0, psta->hwaddr);/*  recipient */

	/* tear करोwn TX AMPDU */
	send_delba(padapter, 1, psta->hwaddr);/*  originator */
	psta->htpriv.agg_enable_biपंचांगap = 0x0;/* reset */
	psta->htpriv.candidate_tid_biपंचांगap = 0x0;/* reset */

	अगर (active)
		issue_deauth(padapter, psta->hwaddr, reason);

	/* clear cam entry / key */
	rtw_clearstakey_cmd(padapter, (u8 *)psta, (u8)(psta->mac_id + 3), true);

	spin_lock_bh(&psta->lock);
	psta->state &= ~_FW_LINKED;
	spin_unlock_bh(&psta->lock);

	rtw_indicate_sta_disassoc_event(padapter, psta);

	report_del_sta_event(padapter, psta->hwaddr, reason);

	beacon_updated = bss_cap_update_on_sta_leave(padapter, psta);

	spin_lock_bh(&pstapriv->sta_hash_lock);
	rtw_मुक्त_stainfo(padapter, psta);
	spin_unlock_bh(&pstapriv->sta_hash_lock);

	वापस beacon_updated;
पूर्ण

पूर्णांक rtw_sta_flush(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head *phead, *plist;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	DBG_88E(FUNC_NDEV_FMT"\n", FUNC_NDEV_ARG(padapter->pnetdev));

	अगर ((pmlmeinfo->state & 0x03) != WIFI_FW_AP_STATE)
		वापस 0;

	spin_lock_bh(&pstapriv->asoc_list_lock);
	phead = &pstapriv->asoc_list;
	plist = phead->next;

	/* मुक्त sta asoc_queue */
	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, asoc_list);

		plist = plist->next;

		list_del_init(&psta->asoc_list);
		pstapriv->asoc_list_cnt--;

		ap_मुक्त_sta(padapter, psta, true, WLAN_REASON_DEAUTH_LEAVING);
	पूर्ण
	spin_unlock_bh(&pstapriv->asoc_list_lock);

	issue_deauth(padapter, bc_addr, WLAN_REASON_DEAUTH_LEAVING);

	associated_clients_update(padapter, true);

	वापस 0;
पूर्ण

/* called > TSR LEVEL क्रम USB or SDIO Interface*/
व्योम sta_info_update(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	पूर्णांक flags = psta->flags;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	/* update wmm cap. */
	अगर (WLAN_STA_WME & flags)
		psta->qos_option = 1;
	अन्यथा
		psta->qos_option = 0;

	अगर (pmlmepriv->qospriv.qos_option == 0)
		psta->qos_option = 0;

	/* update 802.11n ht cap. */
	अगर (WLAN_STA_HT & flags) अणु
		psta->htpriv.ht_option = true;
		psta->qos_option = 1;
	पूर्ण अन्यथा अणु
		psta->htpriv.ht_option = false;
	पूर्ण

	अगर (!pmlmepriv->htpriv.ht_option)
		psta->htpriv.ht_option = false;

	update_sta_info_apmode(padapter, psta);
पूर्ण

/* called >= TSR LEVEL क्रम USB or SDIO Interface*/
व्योम ap_sta_info_defer_update(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	अगर (psta->state & _FW_LINKED) अणु
		/* add ratid */
		add_RATid(padapter, psta, 0);/* DM_RATR_STA_INIT */
	पूर्ण
पूर्ण

व्योम start_ap_mode(काष्ठा adapter *padapter)
अणु
	पूर्णांक i;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;

	pmlmepriv->update_bcn = false;

	pmlmeext->bstart_bss = false;

	pmlmepriv->num_sta_non_erp = 0;

	pmlmepriv->num_sta_no_लघु_slot_समय = 0;

	pmlmepriv->num_sta_no_लघु_preamble = 0;

	pmlmepriv->num_sta_ht_no_gf = 0;
	pmlmepriv->num_sta_no_ht = 0;
	pmlmepriv->num_sta_ht_20mhz = 0;

	pmlmepriv->olbc = false;

	pmlmepriv->olbc_ht = false;

	pmlmepriv->ht_op_mode = 0;

	क्रम (i = 0; i < NUM_STA; i++)
		pstapriv->sta_aid[i] = शून्य;

	pmlmepriv->wps_beacon_ie = शून्य;
	pmlmepriv->wps_probe_resp_ie = शून्य;
	pmlmepriv->wps_assoc_resp_ie = शून्य;

	/* क्रम ACL */
	INIT_LIST_HEAD(&pacl_list->acl_node_q.queue);
	pacl_list->num = 0;
	pacl_list->mode = 0;
	क्रम (i = 0; i < NUM_ACL; i++) अणु
		INIT_LIST_HEAD(&pacl_list->aclnode[i].list);
		pacl_list->aclnode[i].valid = false;
	पूर्ण
पूर्ण

व्योम stop_ap_mode(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head *phead, *plist;
	काष्ठा rtw_wlan_acl_node *paclnode;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	काष्ठा __queue *pacl_node_q = &pacl_list->acl_node_q;

	pmlmepriv->update_bcn = false;
	pmlmeext->bstart_bss = false;

	/* reset and init security priv , this can refine with
	 * rtw_reset_securitypriv
	 */
	स_रखो((अचिन्हित अक्षर *)&padapter->securitypriv, 0, माप(काष्ठा security_priv));
	padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
	padapter->securitypriv.ndisencryptstatus = Ndis802_11WEPDisabled;

	/* क्रम ACL */
	spin_lock_bh(&pacl_node_q->lock);
	phead = get_list_head(pacl_node_q);
	plist = phead->next;
	जबतक (phead != plist) अणु
		paclnode = container_of(plist, काष्ठा rtw_wlan_acl_node, list);
		plist = plist->next;

		अगर (paclnode->valid) अणु
			paclnode->valid = false;

			list_del_init(&paclnode->list);

			pacl_list->num--;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pacl_node_q->lock);

	DBG_88E("%s, free acl_node_queue, num =%d\n", __func__, pacl_list->num);

	rtw_sta_flush(padapter);

	/* मुक्त_assoc_sta_resources */
	rtw_मुक्त_all_stainfo(padapter);

	psta = rtw_get_bcmc_stainfo(padapter);
	spin_lock_bh(&pstapriv->sta_hash_lock);
	rtw_मुक्त_stainfo(padapter, psta);
	spin_unlock_bh(&pstapriv->sta_hash_lock);

	rtw_init_bcmc_stainfo(padapter);

	rtw_मुक्त_mlme_priv_ie_data(pmlmepriv);
पूर्ण

#पूर्ण_अगर /* CONFIG_88EU_AP_MODE */
