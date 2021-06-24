<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_AP_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <यंत्र/unaligned.h>

व्योम init_mlme_ap_info(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;

	spin_lock_init(&pmlmepriv->bcn_update_lock);

	/* क्रम ACL */
	_rtw_init_queue(&pacl_list->acl_node_q);

	/* pmlmeext->bstart_bss = false; */

	start_ap_mode(padapter);
पूर्ण

व्योम मुक्त_mlme_ap_info(काष्ठा adapter *padapter)
अणु
	काष्ठा sta_info *psta = शून्य;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	/* stop_ap_mode(padapter); */

	pmlmepriv->update_bcn = false;
	pmlmeext->bstart_bss = false;

	rtw_sta_flush(padapter);

	pmlmeinfo->state = _HW_STATE_NOLINK_;

	/* मुक्त_assoc_sta_resources */
	rtw_मुक्त_all_stainfo(padapter);

	/* मुक्त bc/mc sta_info */
	psta = rtw_get_bcmc_stainfo(padapter);
	rtw_मुक्त_stainfo(padapter, psta);
पूर्ण

अटल व्योम update_BCNTIM(काष्ठा adapter *padapter)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex *pnetwork_mlmeext = &pmlmeinfo->network;
	अचिन्हित अक्षर *pie = pnetwork_mlmeext->IEs;

	/* update TIM IE */
	/* अगर (pstapriv->tim_biपंचांगap) */
	अगर (true) अणु
		u8 *p, *dst_ie, *preमुख्यder_ie = शून्य, *pbackup_reमुख्यder_ie = शून्य;
		__le16 tim_biपंचांगap_le;
		uपूर्णांक offset, पंचांगp_len, tim_ielen, tim_ie_offset, reमुख्यder_ielen;

		tim_biपंचांगap_le = cpu_to_le16(pstapriv->tim_biपंचांगap);

		p = rtw_get_ie(pie + _FIXED_IE_LENGTH_,
			       WLAN_EID_TIM,
			       &tim_ielen,
			       pnetwork_mlmeext->IELength - _FIXED_IE_LENGTH_
		);
		अगर (p && tim_ielen > 0) अणु
			tim_ielen += 2;

			preमुख्यder_ie = p + tim_ielen;

			tim_ie_offset = (चिन्हित पूर्णांक)(p - pie);

			reमुख्यder_ielen = pnetwork_mlmeext->IELength - tim_ie_offset - tim_ielen;

			/* append TIM IE from dst_ie offset */
			dst_ie = p;
		पूर्ण अन्यथा अणु
			tim_ielen = 0;

			/* calculate head_len */
			offset = _FIXED_IE_LENGTH_;

			/* get ssid_ie len */
			p = rtw_get_ie(pie + _BEACON_IE_OFFSET_,
				       WLAN_EID_SSID,
				       &पंचांगp_len,
				       (pnetwork_mlmeext->IELength - _BEACON_IE_OFFSET_)
			);
			अगर (p)
				offset += पंचांगp_len + 2;

			/*  get supported rates len */
			p = rtw_get_ie(pie + _BEACON_IE_OFFSET_,
				       WLAN_EID_SUPP_RATES, &पंचांगp_len,
				       (pnetwork_mlmeext->IELength - _BEACON_IE_OFFSET_)
			);
			अगर (p)
				offset += पंचांगp_len + 2;

			/* DS Parameter Set IE, len =3 */
			offset += 3;

			preमुख्यder_ie = pie + offset;

			reमुख्यder_ielen = pnetwork_mlmeext->IELength - offset - tim_ielen;

			/* append TIM IE from offset */
			dst_ie = pie + offset;
		पूर्ण

		अगर (reमुख्यder_ielen > 0) अणु
			pbackup_reमुख्यder_ie = rtw_दो_स्मृति(reमुख्यder_ielen);
			अगर (pbackup_reमुख्यder_ie && preमुख्यder_ie)
				स_नकल(pbackup_reमुख्यder_ie, preमुख्यder_ie, reमुख्यder_ielen);
		पूर्ण

		*dst_ie++ = WLAN_EID_TIM;

		अगर ((pstapriv->tim_biपंचांगap & 0xff00) && (pstapriv->tim_biपंचांगap & 0x00fe))
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
			__le16 pvb;

			अगर (pstapriv->tim_biपंचांगap & 0xff00)
				pvb = cpu_to_le16(pstapriv->tim_biपंचांगap >> 8);
			अन्यथा
				pvb = tim_biपंचांगap_le;

			*dst_ie++ = le16_to_cpu(pvb);

		पूर्ण अन्यथा अगर (tim_ielen == 5) अणु
			स_नकल(dst_ie, &tim_biपंचांगap_le, 2);
			dst_ie += 2;
		पूर्ण

		/* copy reमुख्यder IE */
		अगर (pbackup_reमुख्यder_ie) अणु
			स_नकल(dst_ie, pbackup_reमुख्यder_ie, reमुख्यder_ielen);

			kमुक्त(pbackup_reमुख्यder_ie);
		पूर्ण

		offset =  (uपूर्णांक)(dst_ie - pie);
		pnetwork_mlmeext->IELength = offset + reमुख्यder_ielen;
	पूर्ण
पूर्ण

u8 chk_sta_is_alive(काष्ठा sta_info *psta);
u8 chk_sta_is_alive(काष्ठा sta_info *psta)
अणु
	sta_update_last_rx_pkts(psta);

	वापस true;
पूर्ण

व्योम expire_समयout_chk(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head	*phead, *plist;
	u8 updated = false;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 chk_alive_num = 0;
	अक्षर chk_alive_list[NUM_STA];
	पूर्णांक i;

	spin_lock_bh(&pstapriv->auth_list_lock);

	phead = &pstapriv->auth_list;
	plist = get_next(phead);

	/* check auth_queue */
	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, auth_list);

		plist = get_next(plist);

		अगर (psta->expire_to > 0) अणु
			psta->expire_to--;
			अगर (psta->expire_to == 0) अणु
				list_del_init(&psta->auth_list);
				pstapriv->auth_list_cnt--;

				spin_unlock_bh(&pstapriv->auth_list_lock);

				rtw_मुक्त_stainfo(padapter, psta);

				spin_lock_bh(&pstapriv->auth_list_lock);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&pstapriv->auth_list_lock);
	psta = शून्य;

	spin_lock_bh(&pstapriv->asoc_list_lock);

	phead = &pstapriv->asoc_list;
	plist = get_next(phead);

	/* check asoc_queue */
	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, asoc_list);
		plist = get_next(plist);
		अगर (chk_sta_is_alive(psta) || !psta->expire_to) अणु
			psta->expire_to = pstapriv->expire_to;
			psta->keep_alive_trycnt = 0;
			psta->under_exist_checking = 0;
		पूर्ण अन्यथा अणु
			अगर (psta->expire_to > 0)
				psta->expire_to--;
		पूर्ण

		अगर (psta->expire_to == 0) अणु
			काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

			अगर (padapter->registrypriv.wअगरi_spec == 1) अणु
				psta->expire_to = pstapriv->expire_to;
				जारी;
			पूर्ण

			अगर (psta->state & WIFI_SLEEP_STATE) अणु
				अगर (!(psta->state & WIFI_STA_ALIVE_CHK_STATE)) अणु
					/* to check अगर alive by another methods */
					/* अगर station is at ps mode. */
					psta->expire_to = pstapriv->expire_to;
					psta->state |= WIFI_STA_ALIVE_CHK_STATE;

					/* to update bcn with tim_biपंचांगap क्रम this station */
					pstapriv->tim_biपंचांगap |= BIT(psta->aid);
					update_beacon(padapter, WLAN_EID_TIM, शून्य, true);

					अगर (!pmlmeext->active_keep_alive_check)
						जारी;
				पूर्ण
			पूर्ण
			अगर (pmlmeext->active_keep_alive_check) अणु
				पूर्णांक stainfo_offset;

				stainfo_offset = rtw_stainfo_offset(pstapriv, psta);
				अगर (stainfo_offset_valid(stainfo_offset))
					chk_alive_list[chk_alive_num++] = stainfo_offset;

				जारी;
			पूर्ण
			list_del_init(&psta->asoc_list);
			pstapriv->asoc_list_cnt--;
			updated = ap_मुक्त_sta(padapter, psta, false, WLAN_REASON_DEAUTH_LEAVING);
		पूर्ण अन्यथा अणु
			/* TODO: Aging mechanism to digest frames in sleep_q to */
			/* aव्योम running out of xmitframe */
			अगर (psta->sleepq_len > (NR_XMITFRAME / pstapriv->asoc_list_cnt)
				&& padapter->xmitpriv.मुक्त_xmitframe_cnt < ((
					NR_XMITFRAME / pstapriv->asoc_list_cnt
				) / 2)
			)
				wakeup_sta_to_xmit(padapter, psta);
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

			psta = rtw_get_stainfo_by_offset(pstapriv, chk_alive_list[i]);
			अगर (!(psta->state & _FW_LINKED))
				जारी;

			अगर (psta->state & WIFI_SLEEP_STATE)
				ret = issue_nulldata(padapter, psta->hwaddr, 0, 1, 50);
			अन्यथा
				ret = issue_nulldata(padapter, psta->hwaddr, 0, 3, 50);

			psta->keep_alive_trycnt++;
			अगर (ret == _SUCCESS) अणु
				psta->expire_to = pstapriv->expire_to;
				psta->keep_alive_trycnt = 0;
				जारी;
			पूर्ण अन्यथा अगर (psta->keep_alive_trycnt <= 3) अणु
				psta->expire_to = 1;
				जारी;
			पूर्ण

			psta->keep_alive_trycnt = 0;
			spin_lock_bh(&pstapriv->asoc_list_lock);
			अगर (list_empty(&psta->asoc_list) == false) अणु
				list_del_init(&psta->asoc_list);
				pstapriv->asoc_list_cnt--;
				updated = ap_मुक्त_sta(padapter, psta, false,
						      WLAN_REASON_DEAUTH_LEAVING);
			पूर्ण
			spin_unlock_bh(&pstapriv->asoc_list_lock);
		पूर्ण

		अगर (backup_oper_channel > 0) /* back to the original operation channel */
			SelectChannel(padapter, backup_oper_channel);
	पूर्ण

	associated_clients_update(padapter, updated);
पूर्ण

व्योम add_RATid(काष्ठा adapter *padapter, काष्ठा sta_info *psta, u8 rssi_level)
अणु
	अचिन्हित अक्षर sta_band = 0, लघुGIrate = false;
	अचिन्हित पूर्णांक tx_ra_biपंचांगap = 0;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा wlan_bssid_ex
		*pcur_network = (काष्ठा wlan_bssid_ex *)&pmlmepriv->cur_network.network;

	अगर (!psta)
		वापस;

	अगर (!(psta->state & _FW_LINKED))
		वापस;

	rtw_hal_update_sta_rate_mask(padapter, psta);
	tx_ra_biपंचांगap = psta->ra_mask;

	लघुGIrate = query_ra_लघु_GI(psta);

	अगर (pcur_network->Configuration.DSConfig > 14) अणु
		अगर (tx_ra_biपंचांगap & 0xffff000)
			sta_band |= WIRELESS_11_5N;

		अगर (tx_ra_biपंचांगap & 0xff0)
			sta_band |= WIRELESS_11A;
	पूर्ण अन्यथा अणु
		अगर (tx_ra_biपंचांगap & 0xffff000)
			sta_band |= WIRELESS_11_24N;

		अगर (tx_ra_biपंचांगap & 0xff0)
			sta_band |= WIRELESS_11G;

		अगर (tx_ra_biपंचांगap & 0x0f)
			sta_band |= WIRELESS_11B;
	पूर्ण

	psta->wireless_mode = sta_band;
	psta->raid = networktype_to_raid_ex(padapter, psta);

	अगर (psta->aid < NUM_STA) अणु
		u8 arg[4] = अणु0पूर्ण;

		arg[0] = psta->mac_id;
		arg[1] = psta->raid;
		arg[2] = लघुGIrate;
		arg[3] = psta->init_rate;

		rtw_hal_add_ra_tid(padapter, tx_ra_biपंचांगap, arg, rssi_level);
	पूर्ण
पूर्ण

व्योम update_bmc_sta(काष्ठा adapter *padapter)
अणु
	अचिन्हित अक्षर network_type;
	पूर्णांक supportRateNum = 0;
	अचिन्हित पूर्णांक tx_ra_biपंचांगap = 0;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex
		*pcur_network = (काष्ठा wlan_bssid_ex *)&pmlmepriv->cur_network.network;
	काष्ठा sta_info *psta = rtw_get_bcmc_stainfo(padapter);

	अगर (psta) अणु
		psta->aid = 0;/* शेष set to 0 */
		/* psta->mac_id = psta->aid+4; */
		psta->mac_id = psta->aid + 1;/* mac_id = 1 क्रम bc/mc stainfo */

		pmlmeinfo->FW_sta_info[psta->mac_id].psta = psta;

		psta->qos_option = 0;
		psta->htpriv.ht_option = false;

		psta->ieee8021x_blocked = 0;

		स_रखो((व्योम *)&psta->sta_stats, 0, माप(काष्ठा stainfo_stats));

		/* psta->करोt118021XPrivacy = _NO_PRIVACY_;//!!! हटाओ it, because it has been set beक्रमe this. */

		/* prepare क्रम add_RATid */
		supportRateNum = rtw_get_rateset_len((u8 *)&pcur_network->SupportedRates);
		network_type = rtw_check_network_type((u8 *)&pcur_network->SupportedRates,
						      supportRateNum,
						      pcur_network->Configuration.DSConfig
		);
		अगर (IsSupportedTxCCK(network_type)) अणु
			network_type = WIRELESS_11B;
		पूर्ण अन्यथा अगर (network_type == WIRELESS_INVALID) अणु /*  error handling */

			अगर (pcur_network->Configuration.DSConfig > 14)
				network_type = WIRELESS_11A;
			अन्यथा
				network_type = WIRELESS_11B;
		पूर्ण
		update_sta_basic_rate(psta, network_type);
		psta->wireless_mode = network_type;

		rtw_hal_update_sta_rate_mask(padapter, psta);
		tx_ra_biपंचांगap = psta->ra_mask;

		psta->raid = networktype_to_raid_ex(padapter, psta);

		/* ap mode */
		rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, psta, true);

		/* अगर (pHalData->fw_ractrl == true) */
		अणु
			u8 arg[4] = अणु0पूर्ण;

			arg[0] = psta->mac_id;
			arg[1] = psta->raid;
			arg[2] = 0;
			arg[3] = psta->init_rate;

			rtw_hal_add_ra_tid(padapter, tx_ra_biपंचांगap, arg, 0);
		पूर्ण

		rtw_sta_media_status_rpt(padapter, psta, 1);

		spin_lock_bh(&psta->lock);
		psta->state = _FW_LINKED;
		spin_unlock_bh(&psta->lock);

	पूर्ण
पूर्ण

/* notes: */
/* AID: 1~MAX क्रम sta and 0 क्रम bc/mc in ap/adhoc mode */
/* MAC_ID = AID+1 क्रम sta in ap/adhoc mode */
/* MAC_ID = 1 क्रम bc/mc क्रम sta/ap/adhoc */
/* MAC_ID = 0 क्रम bssid क्रम sta/ap/adhoc */
/* CAM_ID = 0~3 क्रम शेष key, cmd_id =macid + 3, macid =aid+1; */

व्योम update_sta_info_apmode(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा ht_priv *phtpriv_ap = &pmlmepriv->htpriv;
	काष्ठा ht_priv *phtpriv_sta = &psta->htpriv;
	u8 cur_ldpc_cap = 0, cur_stbc_cap = 0, cur_beamक्रमm_cap = 0;
	/* set पूर्णांकf_tag to अगर1 */
	/* psta->पूर्णांकf_tag = 0; */

	/* psta->mac_id = psta->aid+4; */
	/* psta->mac_id = psta->aid+1;//alloc macid when call rtw_alloc_stainfo(), */
	/* release macid when call rtw_मुक्त_stainfo() */

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

		phtpriv_sta->rx_ampdu_min_spacing = (
			phtpriv_sta->ht_cap.ampdu_params_info & IEEE80211_HT_CAP_AMPDU_DENSITY
		) >> 2;

		/*  bwmode */
		अगर ((
			phtpriv_sta->ht_cap.cap_info & phtpriv_ap->ht_cap.cap_info
		) & cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH))
			psta->bw_mode = CHANNEL_WIDTH_40;
		अन्यथा
			psta->bw_mode = CHANNEL_WIDTH_20;

		अगर (pmlmeext->cur_bwmode < psta->bw_mode)
			psta->bw_mode = pmlmeext->cur_bwmode;

		phtpriv_sta->ch_offset = pmlmeext->cur_ch_offset;

		/* check अगर sta support s Short GI 20M */
		अगर ((
			phtpriv_sta->ht_cap.cap_info & phtpriv_ap->ht_cap.cap_info
		) & cpu_to_le16(IEEE80211_HT_CAP_SGI_20))
			phtpriv_sta->sgi_20m = true;

		/* check अगर sta support s Short GI 40M */
		अगर ((
			phtpriv_sta->ht_cap.cap_info & phtpriv_ap->ht_cap.cap_info
		) & cpu_to_le16(IEEE80211_HT_CAP_SGI_40)) अणु
			अगर (psta->bw_mode == CHANNEL_WIDTH_40) /* according to psta->bw_mode */
				phtpriv_sta->sgi_40m = true;
			अन्यथा
				phtpriv_sta->sgi_40m = false;
		पूर्ण

		psta->qos_option = true;

		/*  B0 Config LDPC Coding Capability */
		अगर (TEST_FLAG(phtpriv_ap->ldpc_cap, LDPC_HT_ENABLE_TX) &&
			      GET_HT_CAPABILITY_ELE_LDPC_CAP((u8 *)(&phtpriv_sta->ht_cap)))
			SET_FLAG(cur_ldpc_cap, (LDPC_HT_ENABLE_TX | LDPC_HT_CAP_TX));

		/*  B7 B8 B9 Config STBC setting */
		अगर (TEST_FLAG(phtpriv_ap->stbc_cap, STBC_HT_ENABLE_TX) &&
			      GET_HT_CAPABILITY_ELE_RX_STBC((u8 *)(&phtpriv_sta->ht_cap)))
			SET_FLAG(cur_stbc_cap, (STBC_HT_ENABLE_TX | STBC_HT_CAP_TX));
	पूर्ण अन्यथा अणु
		phtpriv_sta->ampdu_enable = false;

		phtpriv_sta->sgi_20m = false;
		phtpriv_sta->sgi_40m = false;
		psta->bw_mode = CHANNEL_WIDTH_20;
		phtpriv_sta->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	पूर्ण

	phtpriv_sta->ldpc_cap = cur_ldpc_cap;
	phtpriv_sta->stbc_cap = cur_stbc_cap;
	phtpriv_sta->beamक्रमm_cap = cur_beamक्रमm_cap;

	/* Rx AMPDU */
	send_delba(padapter, 0, psta->hwaddr);/*  recipient */

	/* TX AMPDU */
	send_delba(padapter, 1, psta->hwaddr);/* originator */
	phtpriv_sta->agg_enable_biपंचांगap = 0x0;/* reset */
	phtpriv_sta->candidate_tid_biपंचांगap = 0x0;/* reset */

	update_ldpc_stbc_cap(psta);

	/* toकरो: init other variables */

	स_रखो((व्योम *)&psta->sta_stats, 0, माप(काष्ठा stainfo_stats));

	/* add ratid */
	/* add_RATid(padapter, psta);//move to ap_sta_info_defer_update() */

	spin_lock_bh(&psta->lock);
	psta->state |= _FW_LINKED;
	spin_unlock_bh(&psta->lock);
पूर्ण

अटल व्योम update_ap_info(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा wlan_bssid_ex
		*pnetwork = (काष्ठा wlan_bssid_ex *)&pmlmepriv->cur_network.network;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा ht_priv *phtpriv_ap = &pmlmepriv->htpriv;

	psta->wireless_mode = pmlmeext->cur_wireless_mode;

	psta->bssratelen = rtw_get_rateset_len(pnetwork->SupportedRates);
	स_नकल(psta->bssrateset, pnetwork->SupportedRates, psta->bssratelen);

	/* HT related cap */
	अगर (phtpriv_ap->ht_option) अणु
		/* check अगर sta supports rx ampdu */
		/* phtpriv_ap->ampdu_enable = phtpriv_ap->ampdu_enable; */

		/* check अगर sta support s Short GI 20M */
		अगर ((phtpriv_ap->ht_cap.cap_info) & cpu_to_le16(IEEE80211_HT_CAP_SGI_20))
			phtpriv_ap->sgi_20m = true;

		/* check अगर sta support s Short GI 40M */
		अगर ((phtpriv_ap->ht_cap.cap_info) & cpu_to_le16(IEEE80211_HT_CAP_SGI_40))
			phtpriv_ap->sgi_40m = true;

		psta->qos_option = true;
	पूर्ण अन्यथा अणु
		phtpriv_ap->ampdu_enable = false;

		phtpriv_ap->sgi_20m = false;
		phtpriv_ap->sgi_40m = false;
	पूर्ण

	psta->bw_mode = pmlmeext->cur_bwmode;
	phtpriv_ap->ch_offset = pmlmeext->cur_ch_offset;

	phtpriv_ap->agg_enable_biपंचांगap = 0x0;/* reset */
	phtpriv_ap->candidate_tid_biपंचांगap = 0x0;/* reset */

	स_नकल(&psta->htpriv, &pmlmepriv->htpriv, माप(काष्ठा ht_priv));
पूर्ण

अटल व्योम update_hw_ht_param(काष्ठा adapter *padapter)
अणु
	अचिन्हित अक्षर max_AMPDU_len;
	अचिन्हित अक्षर min_MPDU_spacing;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	/* handle A-MPDU parameter field
	 *
	 *	AMPDU_para [1:0]:Max AMPDU Len => 0:8k , 1:16k, 2:32k, 3:64k
	 *	AMPDU_para [4:2]:Min MPDU Start Spacing
	 */
	max_AMPDU_len = pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x03;

	min_MPDU_spacing = (pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x1c) >> 2;

	rtw_hal_set_hwreg(padapter, HW_VAR_AMPDU_MIN_SPACE, (u8 *)(&min_MPDU_spacing));

	rtw_hal_set_hwreg(padapter, HW_VAR_AMPDU_FACTOR, (u8 *)(&max_AMPDU_len));

	/*  */
	/*  Config SM Power Save setting */
	/*  */
	pmlmeinfo->SM_PS = (le16_to_cpu(
		pmlmeinfo->HT_caps.u.HT_cap_element.HT_caps_info
	) & 0x0C) >> 2;

	/*  */
	/*  Config current HT Protection mode. */
	/*  */
	/* pmlmeinfo->HT_protection = pmlmeinfo->HT_info.infos[1] & 0x3; */
पूर्ण

व्योम start_bss_network(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	u8 *p;
	u8 val8, cur_channel, cur_bwmode, cur_ch_offset;
	u16 bcn_पूर्णांकerval;
	u32 acparm;
	पूर्णांक	ie_len;
	काष्ठा registry_priv  *pregpriv = &padapter->registrypriv;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा security_priv *psecuritypriv = &(padapter->securitypriv);
	काष्ठा wlan_bssid_ex
		*pnetwork = (काष्ठा wlan_bssid_ex *)&pmlmepriv->cur_network.network;
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex *pnetwork_mlmeext = &(pmlmeinfo->network);
	काष्ठा HT_info_element *pht_info = शून्य;
	u8 cbw40_enable = 0;

	bcn_पूर्णांकerval = (u16)pnetwork->Configuration.BeaconPeriod;
	cur_channel = pnetwork->Configuration.DSConfig;
	cur_bwmode = CHANNEL_WIDTH_20;
	cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	/* check अगर there is wps ie, */
	/* अगर there is wpsie in beacon, the hostapd will update beacon twice when stating hostapd, */
	/* and at first समय the security ie (RSN/WPA IE) will not include in beacon. */
	अगर (!rtw_get_wps_ie(pnetwork->IEs + _FIXED_IE_LENGTH_,
			    pnetwork->IELength - _FIXED_IE_LENGTH_, शून्य, शून्य))
		pmlmeext->bstart_bss = true;

	/* toकरो: update wmm, ht cap */
	/* pmlmeinfo->WMM_enable; */
	/* pmlmeinfo->HT_enable; */
	अगर (pmlmepriv->qospriv.qos_option)
		pmlmeinfo->WMM_enable = true;
	अगर (pmlmepriv->htpriv.ht_option) अणु
		pmlmeinfo->WMM_enable = true;
		pmlmeinfo->HT_enable = true;
		/* pmlmeinfo->HT_info_enable = true; */
		/* pmlmeinfo->HT_caps_enable = true; */

		update_hw_ht_param(padapter);
	पूर्ण

	अगर (!pmlmepriv->cur_network.join_res) अणु /* setting only at  first समय */

		/* WEP Key will be set beक्रमe this function, करो not clear CAM. */
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
	/* acparm = 0x00105320; // BE */
	acparm = 0x005ea42b;
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BE, (u8 *)(&acparm));
	acparm = 0x0000A444; /*  BK */
	rtw_hal_set_hwreg(padapter, HW_VAR_AC_PARAM_BK, (u8 *)(&acparm));

	/* Set Security */
	val8 = (
		psecuritypriv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X
	) ? 0xcc : 0xcf;
	rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

	/* Beacon Control related रेजिस्टर */
	rtw_hal_set_hwreg(padapter, HW_VAR_BEACON_INTERVAL, (u8 *)(&bcn_पूर्णांकerval));

	rtw_hal_set_hwreg(padapter, HW_VAR_DO_IQK, शून्य);

	अगर (!pmlmepriv->cur_network.join_res) अणु /* setting only at  first समय */
		/* u32 initialgain; */

		/* initialgain = 0x1e; */

		/* disable dynamic functions, such as high घातer, DIG */
		/* Save_DM_Func_Flag(padapter); */
		/* Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, false); */

		/* turn on all dynamic functions */
		Switch_DM_Func(padapter, DYNAMIC_ALL_FUNC_ENABLE, true);

		/* rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain)); */
	पूर्ण

	/* set channel, bwmode */
	p = rtw_get_ie((pnetwork->IEs + माप(काष्ठा ndis_802_11_fix_ie)),
		       WLAN_EID_HT_OPERATION,
		       &ie_len,
		       (pnetwork->IELength - माप(काष्ठा ndis_802_11_fix_ie))
	);
	अगर (p && ie_len) अणु
		pht_info = (काष्ठा HT_info_element *)(p + 2);

		अगर (cur_channel > 14) अणु
			अगर ((pregpriv->bw_mode & 0xf0) > 0)
				cbw40_enable = 1;
		पूर्ण अन्यथा अणु
			अगर ((pregpriv->bw_mode & 0x0f) > 0)
				cbw40_enable = 1;
		पूर्ण

		अगर ((cbw40_enable) &&	 (pht_info->infos[0] & BIT(2))) अणु
			/* चयन to the 40M Hz mode */
			/* pmlmeext->cur_bwmode = CHANNEL_WIDTH_40; */
			cur_bwmode = CHANNEL_WIDTH_40;
			चयन (pht_info->infos[0] & 0x3) अणु
			हाल 1:
				/* pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER; */
				cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
				अवरोध;

			हाल 3:
				/* pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER; */
				cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
				अवरोध;

			शेष:
				/* pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE; */
				cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	set_channel_bwmode(padapter, cur_channel, cur_ch_offset, cur_bwmode);
	pmlmeext->cur_channel = cur_channel;
	pmlmeext->cur_bwmode = cur_bwmode;
	pmlmeext->cur_ch_offset = cur_ch_offset;
	pmlmeext->cur_wireless_mode = pmlmepriv->cur_network.network_type;

	/* let pnetwork_mlmeext == pnetwork_mlme. */
	स_नकल(pnetwork_mlmeext, pnetwork, pnetwork->Length);

	/* update cur_wireless_mode */
	update_wireless_mode(padapter);

	/* update RRSR after set channel and bandwidth */
	UpdateBrateTbl(padapter, pnetwork->SupportedRates);
	rtw_hal_set_hwreg(padapter, HW_VAR_BASIC_RATE, pnetwork->SupportedRates);

	/* update capability after cur_wireless_mode updated */
	update_capinfo(
		padapter,
		rtw_get_capability((काष्ठा wlan_bssid_ex *)pnetwork)
	);

	अगर (pmlmeext->bstart_bss) अणु
		update_beacon(padapter, WLAN_EID_TIM, शून्य, true);

		/* issue beacon frame */
		send_beacon(padapter);
	पूर्ण

	/* update bc/mc sta_info */
	update_bmc_sta(padapter);

	/* pmlmeext->bstart_bss = true; */
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
	u8 channel, network_type, supportRate[NDIS_802_11_LENGTH_RATES_EX];
	पूर्णांक supportRateNum = 0;
	u8 OUI1[] = अणु0x00, 0x50, 0xf2, 0x01पूर्ण;
	u8 WMM_PARA_IE[] = अणु0x00, 0x50, 0xf2, 0x02, 0x01, 0x01पूर्ण;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा wlan_bssid_ex
		*pbss_network = (काष्ठा wlan_bssid_ex *)&pmlmepriv->cur_network.network;
	u8 *ie = pbss_network->IEs;

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस _FAIL;

	अगर (len < 0 || len > MAX_IE_SZ)
		वापस _FAIL;

	pbss_network->IELength = len;

	स_रखो(ie, 0, MAX_IE_SZ);

	स_नकल(ie, pbuf, pbss_network->IELength);

	अगर (pbss_network->Infraकाष्ठाureMode != Ndis802_11APMode)
		वापस _FAIL;

	pbss_network->Rssi = 0;

	स_नकल(pbss_network->MacAddress, myid(&(padapter->eeprompriv)), ETH_ALEN);

	/* beacon पूर्णांकerval */
	p = rtw_get_beacon_पूर्णांकerval_from_ie(ie);/* ie + 8;	8: TimeStamp, 2: Beacon Interval 2:Capability */
	/* pbss_network->Configuration.BeaconPeriod = le16_to_cpu(*(अचिन्हित लघु*)p); */
	pbss_network->Configuration.BeaconPeriod = get_unaligned_le16(p);

	/* capability */
	/* cap = *(अचिन्हित लघु *)rtw_get_capability_from_ie(ie); */
	/* cap = le16_to_cpu(cap); */
	cap = get_unaligned_le16(ie);

	/* SSID */
	p = rtw_get_ie(
		ie + _BEACON_IE_OFFSET_,
		WLAN_EID_SSID,
		&ie_len,
		(pbss_network->IELength - _BEACON_IE_OFFSET_)
	);
	अगर (p && ie_len > 0) अणु
		स_रखो(&pbss_network->Ssid, 0, माप(काष्ठा ndis_802_11_ssid));
		स_नकल(pbss_network->Ssid.Ssid, (p + 2), ie_len);
		pbss_network->Ssid.SsidLength = ie_len;
	पूर्ण

	/* channel */
	channel = 0;
	pbss_network->Configuration.Length = 0;
	p = rtw_get_ie(
		ie + _BEACON_IE_OFFSET_,
		WLAN_EID_DS_PARAMS, &ie_len,
		(pbss_network->IELength - _BEACON_IE_OFFSET_)
	);
	अगर (p && ie_len > 0)
		channel = *(p + 2);

	pbss_network->Configuration.DSConfig = channel;

	स_रखो(supportRate, 0, NDIS_802_11_LENGTH_RATES_EX);
	/*  get supported rates */
	p = rtw_get_ie(
		ie + _BEACON_IE_OFFSET_,
		WLAN_EID_SUPP_RATES,
		&ie_len,
		(pbss_network->IELength - _BEACON_IE_OFFSET_)
	);
	अगर (p !=  शून्य) अणु
		स_नकल(supportRate, p + 2, ie_len);
		supportRateNum = ie_len;
	पूर्ण

	/* get ext_supported rates */
	p = rtw_get_ie(
		ie + _BEACON_IE_OFFSET_,
		WLAN_EID_EXT_SUPP_RATES,
		&ie_len,
		pbss_network->IELength - _BEACON_IE_OFFSET_
	);
	अगर (p !=  शून्य) अणु
		स_नकल(supportRate + supportRateNum, p + 2, ie_len);
		supportRateNum += ie_len;
	पूर्ण

	network_type = rtw_check_network_type(supportRate, supportRateNum, channel);

	rtw_set_supported_rate(pbss_network->SupportedRates, network_type);

	/* parsing ERP_IE */
	p = rtw_get_ie(
		ie + _BEACON_IE_OFFSET_,
		WLAN_EID_ERP_INFO,
		&ie_len,
		(pbss_network->IELength - _BEACON_IE_OFFSET_)
	);
	अगर (p && ie_len > 0)
		ERP_IE_handler(padapter, (काष्ठा ndis_80211_var_ie *)p);

	/* update privacy/security */
	अगर (cap & BIT(4))
		pbss_network->Privacy = 1;
	अन्यथा
		pbss_network->Privacy = 0;

	psecuritypriv->wpa_psk = 0;

	/* wpa2 */
	group_cipher = 0; pairwise_cipher = 0;
	psecuritypriv->wpa2_group_cipher = _NO_PRIVACY_;
	psecuritypriv->wpa2_pairwise_cipher = _NO_PRIVACY_;
	p = rtw_get_ie(
		ie + _BEACON_IE_OFFSET_,
		WLAN_EID_RSN,
		&ie_len,
		(pbss_network->IELength - _BEACON_IE_OFFSET_)
	);
	अगर (p && ie_len > 0) अणु
		अगर (rtw_parse_wpa2_ie(
			p,
			ie_len + 2,
			&group_cipher,
			&pairwise_cipher,
			शून्य
		) == _SUCCESS) अणु
			psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;

			psecuritypriv->करोt8021xalg = 1;/* psk,  toकरो:802.1x */
			psecuritypriv->wpa_psk |= BIT(1);

			psecuritypriv->wpa2_group_cipher = group_cipher;
			psecuritypriv->wpa2_pairwise_cipher = pairwise_cipher;
		पूर्ण
	पूर्ण

	/* wpa */
	ie_len = 0;
	group_cipher = 0; pairwise_cipher = 0;
	psecuritypriv->wpa_group_cipher = _NO_PRIVACY_;
	psecuritypriv->wpa_pairwise_cipher = _NO_PRIVACY_;
	क्रम (p = ie + _BEACON_IE_OFFSET_; ; p += (ie_len + 2)) अणु
		p = rtw_get_ie(
			p,
			WLAN_EID_VENDOR_SPECIFIC,
			&ie_len,
			(pbss_network->IELength - _BEACON_IE_OFFSET_ - (ie_len + 2))
		);
		अगर ((p) && (!स_भेद(p + 2, OUI1, 4))) अणु
			अगर (rtw_parse_wpa_ie(
				p,
				ie_len + 2,
				&group_cipher,
				&pairwise_cipher,
				शून्य
			) == _SUCCESS) अणु
				psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;

				psecuritypriv->करोt8021xalg = 1;/* psk,  toकरो:802.1x */

				psecuritypriv->wpa_psk |= BIT(0);

				psecuritypriv->wpa_group_cipher = group_cipher;
				psecuritypriv->wpa_pairwise_cipher = pairwise_cipher;
			पूर्ण

			अवरोध;
		पूर्ण

		अगर ((p == शून्य) || (ie_len == 0))
			अवरोध;
	पूर्ण

	/* wmm */
	ie_len = 0;
	pmlmepriv->qospriv.qos_option = 0;
	अगर (pregistrypriv->wmm_enable) अणु
		क्रम (p = ie + _BEACON_IE_OFFSET_; ; p += (ie_len + 2)) अणु
			p = rtw_get_ie(
				p,
				WLAN_EID_VENDOR_SPECIFIC,
				&ie_len,
				(pbss_network->IELength - _BEACON_IE_OFFSET_ - (ie_len + 2))
			);
			अगर ((p) && !स_भेद(p + 2, WMM_PARA_IE, 6)) अणु
				pmlmepriv->qospriv.qos_option = 1;

				*(p + 8) |= BIT(7);/* QoS Info, support U-APSD */

				/* disable all ACM bits since the WMM admission */
				/* control is not supported */
				*(p + 10) &= ~BIT(4); /* BE */
				*(p + 14) &= ~BIT(4); /* BK */
				*(p + 18) &= ~BIT(4); /* VI */
				*(p + 22) &= ~BIT(4); /* VO */

				अवरोध;
			पूर्ण

			अगर ((p == शून्य) || (ie_len == 0))
				अवरोध;
		पूर्ण
	पूर्ण

	/* parsing HT_CAP_IE */
	p = rtw_get_ie(
		ie + _BEACON_IE_OFFSET_,
		WLAN_EID_HT_CAPABILITY,
		&ie_len,
		(pbss_network->IELength - _BEACON_IE_OFFSET_)
	);
	अगर (p && ie_len > 0) अणु
		u8 rf_type = 0;
		u8 max_rx_ampdu_factor = 0;
		काष्ठा ieee80211_ht_cap *pht_cap = (काष्ठा ieee80211_ht_cap *)(p + 2);

		pHT_caps_ie = p;

		ht_cap = true;
		network_type |= WIRELESS_11_24N;

		rtw_ht_use_शेष_setting(padapter);

		अगर (pmlmepriv->htpriv.sgi_20m == false)
			pht_cap->cap_info &= cpu_to_le16(~(IEEE80211_HT_CAP_SGI_20));

		अगर (pmlmepriv->htpriv.sgi_40m == false)
			pht_cap->cap_info &= cpu_to_le16(~(IEEE80211_HT_CAP_SGI_40));

		अगर (!TEST_FLAG(pmlmepriv->htpriv.ldpc_cap, LDPC_HT_ENABLE_RX))
			pht_cap->cap_info &= cpu_to_le16(~(IEEE80211_HT_CAP_LDPC_CODING));

		अगर (!TEST_FLAG(pmlmepriv->htpriv.stbc_cap, STBC_HT_ENABLE_TX))
			pht_cap->cap_info &= cpu_to_le16(~(IEEE80211_HT_CAP_TX_STBC));

		अगर (!TEST_FLAG(pmlmepriv->htpriv.stbc_cap, STBC_HT_ENABLE_RX))
			pht_cap->cap_info &= cpu_to_le16(~(IEEE80211_HT_CAP_RX_STBC_3R));

		pht_cap->ampdu_params_info &= ~(
			IEEE80211_HT_CAP_AMPDU_FACTOR | IEEE80211_HT_CAP_AMPDU_DENSITY
		);

		अगर ((psecuritypriv->wpa_pairwise_cipher & WPA_CIPHER_CCMP) ||
		     (psecuritypriv->wpa2_pairwise_cipher & WPA_CIPHER_CCMP)) अणु
			pht_cap->ampdu_params_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY & (0x07 << 2));
		पूर्ण अन्यथा अणु
			pht_cap->ampdu_params_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY & 0x00);
		पूर्ण

		rtw_hal_get_def_var(
			padapter,
			HW_VAR_MAX_RX_AMPDU_FACTOR,
			&max_rx_ampdu_factor
		);
		pht_cap->ampdu_params_info |= (
			IEEE80211_HT_CAP_AMPDU_FACTOR & max_rx_ampdu_factor
		); /* set  Max Rx AMPDU size  to 64K */

		rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));
		अगर (rf_type == RF_1T1R) अणु
			pht_cap->mcs.rx_mask[0] = 0xff;
			pht_cap->mcs.rx_mask[1] = 0x0;
		पूर्ण

		स_नकल(&pmlmepriv->htpriv.ht_cap, p + 2, ie_len);
	पूर्ण

	/* parsing HT_INFO_IE */
	p = rtw_get_ie(
		ie + _BEACON_IE_OFFSET_,
		WLAN_EID_HT_OPERATION,
		&ie_len,
		(pbss_network->IELength - _BEACON_IE_OFFSET_)
	);
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

		HT_caps_handler(padapter, (काष्ठा ndis_80211_var_ie *)pHT_caps_ie);

		HT_info_handler(padapter, (काष्ठा ndis_80211_var_ie *)pHT_info_ie);
	पूर्ण

	pbss_network->Length = get_wlan_bssid_ex_sz(
		(काष्ठा wlan_bssid_ex  *)pbss_network
	);

	/* issue beacon to start bss network */
	/* start_bss_network(padapter, (u8 *)pbss_network); */
	rtw_startbss_cmd(padapter, RTW_CMDF_WAIT_ACK);

	/* alloc sta_info क्रम ap itself */
	psta = rtw_get_stainfo(&padapter->stapriv, pbss_network->MacAddress);
	अगर (!psta) अणु
		psta = rtw_alloc_stainfo(&padapter->stapriv, pbss_network->MacAddress);
		अगर (psta == शून्य)
			वापस _FAIL;
	पूर्ण

	/*  update AP's sta info */
	update_ap_info(padapter, psta);

	psta->state |= WIFI_AP_STATE;		/* Aries, add, fix bug of flush_cam_entry at STOP AP mode , 0724 */
	rtw_indicate_connect(padapter);

	pmlmepriv->cur_network.join_res = true;/* क्रम check अगर alपढ़ोy set beacon */

	/* update bc/mc sta_info */
	/* update_bmc_sta(padapter); */

	वापस ret;
पूर्ण

व्योम rtw_set_macaddr_acl(काष्ठा adapter *padapter, पूर्णांक mode)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;

	pacl_list->mode = mode;
पूर्ण

पूर्णांक rtw_acl_add_sta(काष्ठा adapter *padapter, u8 *addr)
अणु
	काष्ठा list_head	*plist, *phead;
	u8 added = false;
	पूर्णांक i, ret = 0;
	काष्ठा rtw_wlan_acl_node *paclnode;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	काष्ठा __queue	*pacl_node_q = &pacl_list->acl_node_q;

	अगर ((NUM_ACL - 1) < pacl_list->num)
		वापस (-1);

	spin_lock_bh(&(pacl_node_q->lock));

	phead = get_list_head(pacl_node_q);
	plist = get_next(phead);

	जबतक (phead != plist) अणु
		paclnode = container_of(plist, काष्ठा rtw_wlan_acl_node, list);
		plist = get_next(plist);

		अगर (!स_भेद(paclnode->addr, addr, ETH_ALEN)) अणु
			अगर (paclnode->valid == true) अणु
				added = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&(pacl_node_q->lock));

	अगर (added)
		वापस ret;

	spin_lock_bh(&(pacl_node_q->lock));

	क्रम (i = 0; i < NUM_ACL; i++) अणु
		paclnode = &pacl_list->aclnode[i];

		अगर (!paclnode->valid) अणु
			INIT_LIST_HEAD(&paclnode->list);

			स_नकल(paclnode->addr, addr, ETH_ALEN);

			paclnode->valid = true;

			list_add_tail(&paclnode->list, get_list_head(pacl_node_q));

			pacl_list->num++;

			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&(pacl_node_q->lock));

	वापस ret;
पूर्ण

व्योम rtw_acl_हटाओ_sta(काष्ठा adapter *padapter, u8 *addr)
अणु
	काष्ठा list_head	*plist, *phead;
	काष्ठा rtw_wlan_acl_node *paclnode;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	काष्ठा __queue	*pacl_node_q = &pacl_list->acl_node_q;
	u8 baddr[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;	/* Baddr is used क्रम clearing acl_list */

	spin_lock_bh(&(pacl_node_q->lock));

	phead = get_list_head(pacl_node_q);
	plist = get_next(phead);

	जबतक (phead != plist) अणु
		paclnode = container_of(plist, काष्ठा rtw_wlan_acl_node, list);
		plist = get_next(plist);

		अगर (
			!स_भेद(paclnode->addr, addr, ETH_ALEN) ||
			!स_भेद(baddr, addr, ETH_ALEN)
		) अणु
			अगर (paclnode->valid) अणु
				paclnode->valid = false;

				list_del_init(&paclnode->list);

				pacl_list->num--;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&(pacl_node_q->lock));

पूर्ण

u8 rtw_ap_set_pairwise_key(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा cmd_obj *ph2c;
	काष्ठा set_stakey_parm	*psetstakey_para;
	काष्ठा cmd_priv *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	ph2c = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (!ph2c) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	psetstakey_para = rtw_zदो_स्मृति(माप(काष्ठा set_stakey_parm));
	अगर (psetstakey_para == शून्य) अणु
		kमुक्त(ph2c);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);

	psetstakey_para->algorithm = (u8)psta->करोt118021XPrivacy;

	स_नकल(psetstakey_para->addr, psta->hwaddr, ETH_ALEN);

	स_नकल(psetstakey_para->key, &psta->करोt118021x_UncstKey, 16);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

निकास:

	वापस res;
पूर्ण

अटल पूर्णांक rtw_ap_set_key(
	काष्ठा adapter *padapter,
	u8 *key,
	u8 alg,
	पूर्णांक keyid,
	u8 set_tx
)
अणु
	u8 keylen;
	काष्ठा cmd_obj *pcmd;
	काष्ठा setkey_parm *psetkeyparm;
	काष्ठा cmd_priv *pcmdpriv = &(padapter->cmdpriv);
	पूर्णांक res = _SUCCESS;

	pcmd = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (pcmd == शून्य) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	psetkeyparm = rtw_zदो_स्मृति(माप(काष्ठा setkey_parm));
	अगर (psetkeyparm == शून्य) अणु
		kमुक्त(pcmd);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	psetkeyparm->keyid = (u8)keyid;
	अगर (is_wep_enc(alg))
		padapter->securitypriv.key_mask |= BIT(psetkeyparm->keyid);

	psetkeyparm->algorithm = alg;

	psetkeyparm->set_tx = set_tx;

	चयन (alg) अणु
	हाल _WEP40_:
		keylen = 5;
		अवरोध;
	हाल _WEP104_:
		keylen = 13;
		अवरोध;
	हाल _TKIP_:
	हाल _TKIP_WTMIC_:
	हाल _AES_:
	शेष:
		keylen = 16;
	पूर्ण

	स_नकल(&(psetkeyparm->key[0]), key, keylen);

	pcmd->cmdcode = _SetKey_CMD_;
	pcmd->parmbuf = (u8 *)psetkeyparm;
	pcmd->cmdsz =  (माप(काष्ठा setkey_parm));
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;

	INIT_LIST_HEAD(&pcmd->list);

	res = rtw_enqueue_cmd(pcmdpriv, pcmd);

निकास:

	वापस res;
पूर्ण

पूर्णांक rtw_ap_set_group_key(काष्ठा adapter *padapter, u8 *key, u8 alg, पूर्णांक keyid)
अणु
	वापस rtw_ap_set_key(padapter, key, alg, keyid, 1);
पूर्ण

पूर्णांक rtw_ap_set_wep_key(
	काष्ठा adapter *padapter,
	u8 *key,
	u8 keylen,
	पूर्णांक keyid,
	u8 set_tx
)
अणु
	u8 alg;

	चयन (keylen) अणु
	हाल 5:
		alg = _WEP40_;
		अवरोध;
	हाल 13:
		alg = _WEP104_;
		अवरोध;
	शेष:
		alg = _NO_PRIVACY_;
	पूर्ण

	वापस rtw_ap_set_key(padapter, key, alg, keyid, set_tx);
पूर्ण

अटल व्योम update_bcn_fixed_ie(काष्ठा adapter *padapter)
अणु
पूर्ण

अटल व्योम update_bcn_erpinfo_ie(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex *pnetwork = &(pmlmeinfo->network);
	अचिन्हित अक्षर *p, *ie = pnetwork->IEs;
	u32 len = 0;

	अगर (!pmlmeinfo->ERP_enable)
		वापस;

	/* parsing ERP_IE */
	p = rtw_get_ie(
		ie + _BEACON_IE_OFFSET_,
		WLAN_EID_ERP_INFO,
		&len,
		(pnetwork->IELength - _BEACON_IE_OFFSET_)
	);
	अगर (p && len > 0) अणु
		काष्ठा ndis_80211_var_ie *pIE = (काष्ठा ndis_80211_var_ie *)p;

		अगर (pmlmepriv->num_sta_non_erp == 1)
			pIE->data[0] |= RTW_ERP_INFO_NON_ERP_PRESENT | RTW_ERP_INFO_USE_PROTECTION;
		अन्यथा
			pIE->data[0] &= ~(
				RTW_ERP_INFO_NON_ERP_PRESENT | RTW_ERP_INFO_USE_PROTECTION
			);

		अगर (pmlmepriv->num_sta_no_लघु_preamble > 0)
			pIE->data[0] |= RTW_ERP_INFO_BARKER_PREAMBLE_MODE;
		अन्यथा
			pIE->data[0] &= ~(RTW_ERP_INFO_BARKER_PREAMBLE_MODE);

		ERP_IE_handler(padapter, pIE);
	पूर्ण
पूर्ण

अटल व्योम update_bcn_htcap_ie(काष्ठा adapter *padapter)
अणु
पूर्ण

अटल व्योम update_bcn_htinfo_ie(काष्ठा adapter *padapter)
अणु
पूर्ण

अटल व्योम update_bcn_rsn_ie(काष्ठा adapter *padapter)
अणु
पूर्ण

अटल व्योम update_bcn_wpa_ie(काष्ठा adapter *padapter)
अणु
पूर्ण

अटल व्योम update_bcn_wmm_ie(काष्ठा adapter *padapter)
अणु
पूर्ण

अटल व्योम update_bcn_wps_ie(काष्ठा adapter *padapter)
अणु
	u8 *pwps_ie = शून्य;
	u8 *pwps_ie_src;
	u8 *preमुख्यder_ie;
	u8 *pbackup_reमुख्यder_ie = शून्य;

	uपूर्णांक wps_ielen = 0, wps_offset, reमुख्यder_ielen;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	काष्ठा wlan_bssid_ex *pnetwork = &(pmlmeinfo->network);
	अचिन्हित अक्षर *ie = pnetwork->IEs;
	u32 ielen = pnetwork->IELength;

	pwps_ie = rtw_get_wps_ie(
		ie + _FIXED_IE_LENGTH_,
		ielen - _FIXED_IE_LENGTH_,
		शून्य,
		&wps_ielen
	);

	अगर (pwps_ie == शून्य || wps_ielen == 0)
		वापस;

	pwps_ie_src = pmlmepriv->wps_beacon_ie;
	अगर (pwps_ie_src == शून्य)
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
	अगर ((wps_offset + wps_ielen + 2 + reमुख्यder_ielen) <= MAX_IE_SZ) अणु
		स_नकल(pwps_ie, pwps_ie_src, wps_ielen + 2);
		pwps_ie += (wps_ielen+2);

		अगर (pbackup_reमुख्यder_ie)
			स_नकल(pwps_ie, pbackup_reमुख्यder_ie, reमुख्यder_ielen);

		/* update IELength */
		pnetwork->IELength = wps_offset + (wps_ielen + 2) + reमुख्यder_ielen;
	पूर्ण

	kमुक्त(pbackup_reमुख्यder_ie);
पूर्ण

अटल व्योम update_bcn_p2p_ie(काष्ठा adapter *padapter)
अणु
पूर्ण

अटल व्योम update_bcn_venकरोr_spec_ie(काष्ठा adapter *padapter, u8 *oui)
अणु
	अगर (!स_भेद(RTW_WPA_OUI, oui, 4))
		update_bcn_wpa_ie(padapter);

	अन्यथा अगर (!स_भेद(WMM_OUI, oui, 4))
		update_bcn_wmm_ie(padapter);

	अन्यथा अगर (!स_भेद(WPS_OUI, oui, 4))
		update_bcn_wps_ie(padapter);

	अन्यथा अगर (!स_भेद(P2P_OUI, oui, 4))
		update_bcn_p2p_ie(padapter);
पूर्ण

व्योम update_beacon(काष्ठा adapter *padapter, u8 ie_id, u8 *oui, u8 tx)
अणु
	काष्ठा mlme_priv *pmlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext;
	/* काष्ठा mlme_ext_info *pmlmeinfo; */

	अगर (!padapter)
		वापस;

	pmlmepriv = &(padapter->mlmepriv);
	pmlmeext = &(padapter->mlmeextpriv);
	/* pmlmeinfo = &(pmlmeext->mlmext_info); */

	अगर (!pmlmeext->bstart_bss)
		वापस;

	spin_lock_bh(&pmlmepriv->bcn_update_lock);

	चयन (ie_id) अणु
	हाल 0xFF:

		update_bcn_fixed_ie(padapter);/* 8: TimeStamp, 2: Beacon Interval 2:Capability */

		अवरोध;

	हाल WLAN_EID_TIM:

		update_BCNTIM(padapter);

		अवरोध;

	हाल WLAN_EID_ERP_INFO:

		update_bcn_erpinfo_ie(padapter);

		अवरोध;

	हाल WLAN_EID_HT_CAPABILITY:

		update_bcn_htcap_ie(padapter);

		अवरोध;

	हाल WLAN_EID_RSN:

		update_bcn_rsn_ie(padapter);

		अवरोध;

	हाल WLAN_EID_HT_OPERATION:

		update_bcn_htinfo_ie(padapter);

		अवरोध;

	हाल WLAN_EID_VENDOR_SPECIFIC:

		update_bcn_venकरोr_spec_ie(padapter, oui);

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	pmlmepriv->update_bcn = true;

	spin_unlock_bh(&pmlmepriv->bcn_update_lock);

	अगर (tx) अणु
		/* send_beacon(padapter);//send_beacon must execute on TSR level */
		set_tx_beacon_cmd(padapter);
	पूर्ण
पूर्ण

/*
 * op_mode
 * Set to 0 (HT pure) under the following conditions
 *	  - all STAs in the BSS are 20/40 MHz HT in 20/40 MHz BSS or
 *	  - all STAs in the BSS are 20 MHz HT in 20 MHz BSS
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
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा ht_priv *phtpriv_ap = &pmlmepriv->htpriv;

	अगर (pmlmepriv->htpriv.ht_option)
		वापस 0;

	अगर (!(pmlmepriv->ht_op_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT)
	    && pmlmepriv->num_sta_ht_no_gf) अणु
		pmlmepriv->ht_op_mode |=
			IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT;
		op_mode_changes++;
	पूर्ण अन्यथा अगर ((pmlmepriv->ht_op_mode &
		    IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT) &&
		   pmlmepriv->num_sta_ht_no_gf == 0) अणु
		pmlmepriv->ht_op_mode &=
			~IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT;
		op_mode_changes++;
	पूर्ण

	अगर (!(pmlmepriv->ht_op_mode & IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT) &&
	    (pmlmepriv->num_sta_no_ht || pmlmepriv->olbc_ht)) अणु
		pmlmepriv->ht_op_mode |= IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT;
		op_mode_changes++;
	पूर्ण अन्यथा अगर ((pmlmepriv->ht_op_mode &
		    IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT) &&
		   (pmlmepriv->num_sta_no_ht == 0 && !pmlmepriv->olbc_ht)) अणु
		pmlmepriv->ht_op_mode &=
			~IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT;
		op_mode_changes++;
	पूर्ण

	/* Note: currently we चयन to the MIXED op mode अगर HT non-greenfield
	 * station is associated. Probably it's a theoretical हाल, since
	 * it looks like all known HT STAs support greenfield.
	 */
	new_op_mode = 0;
	अगर (pmlmepriv->num_sta_no_ht ||
	    (pmlmepriv->ht_op_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT))
		new_op_mode = IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED;
	अन्यथा अगर (
		(le16_to_cpu(phtpriv_ap->ht_cap.cap_info) & IEEE80211_HT_CAP_SUP_WIDTH)
		&& pmlmepriv->num_sta_ht_20mhz)
		new_op_mode = IEEE80211_HT_OP_MODE_PROTECTION_20MHZ;
	अन्यथा अगर (pmlmepriv->olbc_ht)
		new_op_mode = IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER;
	अन्यथा
		new_op_mode = IEEE80211_HT_OP_MODE_PROTECTION_NONE;

	cur_op_mode = pmlmepriv->ht_op_mode & IEEE80211_HT_OP_MODE_PROTECTION;
	अगर (cur_op_mode != new_op_mode) अणु
		pmlmepriv->ht_op_mode &= ~IEEE80211_HT_OP_MODE_PROTECTION;
		pmlmepriv->ht_op_mode |= new_op_mode;
		op_mode_changes++;
	पूर्ण

	वापस op_mode_changes;
पूर्ण

व्योम associated_clients_update(काष्ठा adapter *padapter, u8 updated)
अणु
	/* update associated stations cap. */
	अगर (updated) अणु
		काष्ठा list_head	*phead, *plist;
		काष्ठा sta_info *psta = शून्य;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;

		spin_lock_bh(&pstapriv->asoc_list_lock);

		phead = &pstapriv->asoc_list;
		plist = get_next(phead);

		/* check asoc_queue */
		जबतक (phead != plist) अणु
			psta = container_of(plist, काष्ठा sta_info, asoc_list);

			plist = get_next(plist);

			VCS_update(padapter, psta);
		पूर्ण

		spin_unlock_bh(&pstapriv->asoc_list_lock);
	पूर्ण
पूर्ण

/* called > TSR LEVEL क्रम USB or SDIO Interface*/
व्योम bss_cap_update_on_sta_join(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 beacon_updated = false;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);

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

		अगर (psta->no_ht_set) अणु
			psta->no_ht_set = 0;
			pmlmepriv->num_sta_no_ht--;
		पूर्ण

		अगर ((ht_capab & IEEE80211_HT_CAP_GRN_FLD) == 0) अणु
			अगर (!psta->no_ht_gf_set) अणु
				psta->no_ht_gf_set = 1;
				pmlmepriv->num_sta_ht_no_gf++;
			पूर्ण
		पूर्ण

		अगर ((ht_capab & IEEE80211_HT_CAP_SUP_WIDTH) == 0) अणु
			अगर (!psta->ht_20mhz_set) अणु
				psta->ht_20mhz_set = 1;
				pmlmepriv->num_sta_ht_20mhz++;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (!psta->no_ht_set) अणु
			psta->no_ht_set = 1;
			pmlmepriv->num_sta_no_ht++;
		पूर्ण
	पूर्ण

	अगर (rtw_ht_operation_update(padapter) > 0) अणु
		update_beacon(padapter, WLAN_EID_HT_CAPABILITY, शून्य, false);
		update_beacon(padapter, WLAN_EID_HT_OPERATION, शून्य, true);
	पूर्ण

	/* update associated stations cap. */
	associated_clients_update(padapter,  beacon_updated);
पूर्ण

u8 bss_cap_update_on_sta_leave(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 beacon_updated = false;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);

	अगर (!psta)
		वापस beacon_updated;

	अगर (psta->no_लघु_preamble_set) अणु
		psta->no_लघु_preamble_set = 0;
		pmlmepriv->num_sta_no_लघु_preamble--;
		अगर (pmlmeext->cur_wireless_mode > WIRELESS_11B
		    && pmlmepriv->num_sta_no_लघु_preamble == 0)अणु
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
		अगर (pmlmeext->cur_wireless_mode > WIRELESS_11B
		    && pmlmepriv->num_sta_no_लघु_slot_समय == 0)अणु
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

	वापस beacon_updated;
पूर्ण

u8 ap_मुक्त_sta(
	काष्ठा adapter *padapter,
	काष्ठा sta_info *psta,
	bool active,
	u16 reason
)
अणु
	u8 beacon_updated = false;

	अगर (!psta)
		वापस beacon_updated;

	अगर (active) अणु
		/* tear करोwn Rx AMPDU */
		send_delba(padapter, 0, psta->hwaddr);/*  recipient */

		/* tear करोwn TX AMPDU */
		send_delba(padapter, 1, psta->hwaddr);/*  // originator */

		issue_deauth(padapter, psta->hwaddr, reason);
	पूर्ण

	psta->htpriv.agg_enable_biपंचांगap = 0x0;/* reset */
	psta->htpriv.candidate_tid_biपंचांगap = 0x0;/* reset */

	/* report_del_sta_event(padapter, psta->hwaddr, reason); */

	/* clear cam entry / key */
	rtw_clearstakey_cmd(padapter, psta, true);

	spin_lock_bh(&psta->lock);
	psta->state &= ~_FW_LINKED;
	spin_unlock_bh(&psta->lock);

	rtw_cfg80211_indicate_sta_disassoc(padapter, psta->hwaddr, reason);

	report_del_sta_event(padapter, psta->hwaddr, reason);

	beacon_updated = bss_cap_update_on_sta_leave(padapter, psta);

	rtw_मुक्त_stainfo(padapter, psta);

	वापस beacon_updated;
पूर्ण

व्योम rtw_sta_flush(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head	*phead, *plist;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 bc_addr[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;

	अगर ((pmlmeinfo->state & 0x03) != WIFI_FW_AP_STATE)
		वापस;

	spin_lock_bh(&pstapriv->asoc_list_lock);
	phead = &pstapriv->asoc_list;
	plist = get_next(phead);

	/* मुक्त sta asoc_queue */
	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, asoc_list);

		plist = get_next(plist);

		list_del_init(&psta->asoc_list);
		pstapriv->asoc_list_cnt--;

		/* spin_unlock_bh(&pstapriv->asoc_list_lock); */
		ap_मुक्त_sta(padapter, psta, true, WLAN_REASON_DEAUTH_LEAVING);
		/* spin_lock_bh(&pstapriv->asoc_list_lock); */
	पूर्ण
	spin_unlock_bh(&pstapriv->asoc_list_lock);

	issue_deauth(padapter, bc_addr, WLAN_REASON_DEAUTH_LEAVING);

	associated_clients_update(padapter, true);
पूर्ण

/* called > TSR LEVEL क्रम USB or SDIO Interface*/
व्योम sta_info_update(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	पूर्णांक flags = psta->flags;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);

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
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर (psta->state & _FW_LINKED) अणु
		pmlmeinfo->FW_sta_info[psta->mac_id].psta = psta;

		/* add ratid */
		add_RATid(padapter, psta, 0);/* DM_RATR_STA_INIT */
	पूर्ण
पूर्ण
/* restore hw setting from sw data काष्ठाures */
व्योम rtw_ap_restore_network(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *mlmepriv = &padapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *psta;
	काष्ठा security_priv *psecuritypriv = &(padapter->securitypriv);
	काष्ठा list_head	*phead, *plist;
	u8 chk_alive_num = 0;
	अक्षर chk_alive_list[NUM_STA];
	पूर्णांक i;

	rtw_setopmode_cmd(padapter, Ndis802_11APMode, false);

	set_channel_bwmode(
		padapter,
		pmlmeext->cur_channel,
		pmlmeext->cur_ch_offset,
		pmlmeext->cur_bwmode
	);

	start_bss_network(padapter, (u8 *)&mlmepriv->cur_network.network);

	अगर ((padapter->securitypriv.करोt11PrivacyAlgrthm == _TKIP_) ||
		(padapter->securitypriv.करोt11PrivacyAlgrthm == _AES_)) अणु
		/* restore group key, WEP keys is restored in ips_leave() */
		rtw_set_key(
			padapter,
			psecuritypriv,
			psecuritypriv->करोt118021XGrpKeyid,
			0,
			false
		);
	पूर्ण

	spin_lock_bh(&pstapriv->asoc_list_lock);

	phead = &pstapriv->asoc_list;
	plist = get_next(phead);

	जबतक (phead != plist) अणु
		पूर्णांक stainfo_offset;

		psta = container_of(plist, काष्ठा sta_info, asoc_list);
		plist = get_next(plist);

		stainfo_offset = rtw_stainfo_offset(pstapriv, psta);
		अगर (stainfo_offset_valid(stainfo_offset))
			chk_alive_list[chk_alive_num++] = stainfo_offset;
	पूर्ण

	spin_unlock_bh(&pstapriv->asoc_list_lock);

	क्रम (i = 0; i < chk_alive_num; i++) अणु
		psta = rtw_get_stainfo_by_offset(pstapriv, chk_alive_list[i]);

		अगर (!psta)
			जारी;

		अगर (psta->state & _FW_LINKED) अणु
			rtw_sta_media_status_rpt(padapter, psta, 1);
			Update_RA_Entry(padapter, psta);
			/* pairwise key */
			/* per sta pairwise key and settings */
			अगर ((psecuritypriv->करोt11PrivacyAlgrthm == _TKIP_) ||
				(psecuritypriv->करोt11PrivacyAlgrthm == _AES_)) अणु
				rtw_setstakey_cmd(padapter, psta, true, false);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम start_ap_mode(काष्ठा adapter *padapter)
अणु
	पूर्णांक i;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;

	pmlmepriv->update_bcn = false;

	/* init_mlme_ap_info(padapter); */
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

	pmlmepriv->p2p_beacon_ie = शून्य;
	pmlmepriv->p2p_probe_resp_ie = शून्य;

	/* क्रम ACL */
	INIT_LIST_HEAD(&(pacl_list->acl_node_q.queue));
	pacl_list->num = 0;
	pacl_list->mode = 0;
	क्रम (i = 0; i < NUM_ACL; i++) अणु
		INIT_LIST_HEAD(&pacl_list->aclnode[i].list);
		pacl_list->aclnode[i].valid = false;
	पूर्ण
पूर्ण

व्योम stop_ap_mode(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head	*phead, *plist;
	काष्ठा rtw_wlan_acl_node *paclnode;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	काष्ठा __queue	*pacl_node_q = &pacl_list->acl_node_q;

	pmlmepriv->update_bcn = false;
	pmlmeext->bstart_bss = false;

	/* reset and init security priv , this can refine with rtw_reset_securitypriv */
	स_रखो(
		(अचिन्हित अक्षर *)&padapter->securitypriv,
		0,
		माप(काष्ठा security_priv)
	);
	padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
	padapter->securitypriv.ndisencryptstatus = Ndis802_11WEPDisabled;

	/* क्रम ACL */
	spin_lock_bh(&(pacl_node_q->lock));
	phead = get_list_head(pacl_node_q);
	plist = get_next(phead);
	जबतक (phead != plist) अणु
		paclnode = container_of(plist, काष्ठा rtw_wlan_acl_node, list);
		plist = get_next(plist);

		अगर (paclnode->valid) अणु
			paclnode->valid = false;

			list_del_init(&paclnode->list);

			pacl_list->num--;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&(pacl_node_q->lock));

	rtw_sta_flush(padapter);

	/* मुक्त_assoc_sta_resources */
	rtw_मुक्त_all_stainfo(padapter);

	psta = rtw_get_bcmc_stainfo(padapter);
	rtw_मुक्त_stainfo(padapter, psta);

	rtw_init_bcmc_stainfo(padapter);

	rtw_मुक्त_mlme_priv_ie_data(pmlmepriv);

	rtw_btcoex_MediaStatusNotअगरy(padapter, 0); /* disconnect */
पूर्ण
