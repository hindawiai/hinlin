<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_IOCTL_SET_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>

u8 rtw_validate_bssid(u8 *bssid)
अणु
	u8 ret = true;

	अगर (is_zero_mac_addr(bssid)
		|| is_broadcast_mac_addr(bssid)
		|| is_multicast_mac_addr(bssid)
	) अणु
		ret = false;
	पूर्ण

	वापस ret;
पूर्ण

u8 rtw_validate_ssid(काष्ठा ndis_802_11_ssid *ssid)
अणु
	u8 ret = true;

	अगर (ssid->SsidLength > 32) अणु
		ret = false;
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

u8 rtw_करो_join(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head	*plist, *phead;
	u8 *pibss = शून्य;
	काष्ठा	mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा __queue	*queue	= &(pmlmepriv->scanned_queue);
	u8 ret = _SUCCESS;

	spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
	phead = get_list_head(queue);
	plist = get_next(phead);

	pmlmepriv->cur_network.join_res = -2;

	set_fwstate(pmlmepriv, _FW_UNDER_LINKING);

	pmlmepriv->pscanned = plist;

	pmlmepriv->to_join = true;

	अगर (list_empty(&queue->queue)) अणु
		spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

		/* when set_ssid/set_bssid क्रम rtw_करो_join(), but scanning queue is empty */
		/* we try to issue sitesurvey firstly */

		अगर (pmlmepriv->LinkDetectInfo.bBusyTraffic == false
			|| rtw_to_roam(padapter) > 0
		) अणु
			/*  submit site_survey_cmd */
			ret = rtw_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid, 1, शून्य, 0);
			अगर (ret != _SUCCESS)
				pmlmepriv->to_join = false;

		पूर्ण अन्यथा अणु
			pmlmepriv->to_join = false;
			ret = _FAIL;
		पूर्ण

		जाओ निकास;
	पूर्ण अन्यथा अणु
		पूर्णांक select_ret;
		spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
		select_ret = rtw_select_and_join_from_scanned_queue(pmlmepriv);
		अगर (select_ret == _SUCCESS) अणु
			pmlmepriv->to_join = false;
			_set_समयr(&pmlmepriv->assoc_समयr, MAX_JOIN_TIMEOUT);
		पूर्ण अन्यथा अणु
			अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true) अणु
				/*  submit createbss_cmd to change to a ADHOC_MASTER */

				/* pmlmepriv->lock has been acquired by caller... */
				काष्ठा wlan_bssid_ex    *pdev_network = &(padapter->registrypriv.dev_network);

				pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;

				pibss = padapter->registrypriv.dev_network.MacAddress;

				स_नकल(&pdev_network->Ssid, &pmlmepriv->assoc_ssid, माप(काष्ठा ndis_802_11_ssid));

				rtw_update_registrypriv_dev_network(padapter);

				rtw_generate_अक्रमom_ibss(pibss);

				अगर (rtw_createbss_cmd(padapter) != _SUCCESS) अणु
					ret =  false;
					जाओ निकास;
				पूर्ण

				pmlmepriv->to_join = false;

			पूर्ण अन्यथा अणु
				/*  can't associate ; reset under-linking */
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

				/* when set_ssid/set_bssid क्रम rtw_करो_join(), but there are no desired bss in scanning queue */
				/* we try to issue sitesurvey firstly */
				अगर (pmlmepriv->LinkDetectInfo.bBusyTraffic == false
					|| rtw_to_roam(padapter) > 0
				) अणु
					ret = rtw_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid, 1, शून्य, 0);
					अगर (ret != _SUCCESS)
						pmlmepriv->to_join = false;

				पूर्ण अन्यथा अणु
					ret = _FAIL;
					pmlmepriv->to_join = false;
				पूर्ण
			पूर्ण

		पूर्ण

	पूर्ण

निकास:
	वापस ret;
पूर्ण

u8 rtw_set_802_11_bssid(काष्ठा adapter *padapter, u8 *bssid)
अणु
	u8 status = _SUCCESS;

	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	netdev_dbg(padapter->pnetdev, "set bssid:%pM\n", bssid);

	अगर ((bssid[0] == 0x00 && bssid[1] == 0x00 && bssid[2] == 0x00 && bssid[3] == 0x00 && bssid[4] == 0x00 && bssid[5] == 0x00) ||
	    (bssid[0] == 0xFF && bssid[1] == 0xFF && bssid[2] == 0xFF && bssid[3] == 0xFF && bssid[4] == 0xFF && bssid[5] == 0xFF)) अणु
		status = _FAIL;
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&pmlmepriv->lock);


	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY) == true)
		जाओ handle_tkip_countermeasure;
	अन्यथा अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING) == true)
		जाओ release_mlme_lock;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED|WIFI_ADHOC_MASTER_STATE) == true) अणु
		अगर (!स_भेद(&pmlmepriv->cur_network.network.MacAddress, bssid, ETH_ALEN)) अणु
			अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == false)
				जाओ release_mlme_lock;/* it means driver is in WIFI_ADHOC_MASTER_STATE, we needn't create bss again. */
		पूर्ण अन्यथा अणु
			rtw_disassoc_cmd(padapter, 0, true);

			अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true)
				rtw_indicate_disconnect(padapter);

			rtw_मुक्त_assoc_resources(padapter, 1);

			अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)) अणु
				_clr_fwstate_(pmlmepriv, WIFI_ADHOC_MASTER_STATE);
				set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			पूर्ण
		पूर्ण
	पूर्ण

handle_tkip_countermeasure:
	अगर (rtw_handle_tkip_countermeasure(padapter, __func__) == _FAIL) अणु
		status = _FAIL;
		जाओ release_mlme_lock;
	पूर्ण

	स_रखो(&pmlmepriv->assoc_ssid, 0, माप(काष्ठा ndis_802_11_ssid));
	स_नकल(&pmlmepriv->assoc_bssid, bssid, ETH_ALEN);
	pmlmepriv->assoc_by_bssid = true;

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY) == true)
		pmlmepriv->to_join = true;
	अन्यथा
		status = rtw_करो_join(padapter);

release_mlme_lock:
	spin_unlock_bh(&pmlmepriv->lock);

निकास:

	वापस status;
पूर्ण

u8 rtw_set_802_11_ssid(काष्ठा adapter *padapter, काष्ठा ndis_802_11_ssid *ssid)
अणु
	u8 status = _SUCCESS;

	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network *pnetwork = &pmlmepriv->cur_network;

	netdev_dbg(padapter->pnetdev, "set ssid [%s] fw_state = 0x%08x\n",
		   ssid->Ssid, get_fwstate(pmlmepriv));

	अगर (padapter->hw_init_completed == false) अणु
		status = _FAIL;
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&pmlmepriv->lock);

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY) == true)
		जाओ handle_tkip_countermeasure;
	अन्यथा अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING) == true)
		जाओ release_mlme_lock;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED|WIFI_ADHOC_MASTER_STATE) == true) अणु
		अगर ((pmlmepriv->assoc_ssid.SsidLength == ssid->SsidLength) &&
		    (!स_भेद(&pmlmepriv->assoc_ssid.Ssid, ssid->Ssid, ssid->SsidLength))) अणु
			अगर ((check_fwstate(pmlmepriv, WIFI_STATION_STATE) == false)) अणु
				अगर (rtw_is_same_ibss(padapter, pnetwork) == false) अणु
					/* अगर in WIFI_ADHOC_MASTER_STATE | WIFI_ADHOC_STATE, create bss or rejoin again */
					rtw_disassoc_cmd(padapter, 0, true);

					अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true)
						rtw_indicate_disconnect(padapter);

					rtw_मुक्त_assoc_resources(padapter, 1);

					अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true) अणु
						_clr_fwstate_(pmlmepriv, WIFI_ADHOC_MASTER_STATE);
						set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
					पूर्ण
				पूर्ण अन्यथा अणु
					जाओ release_mlme_lock;/* it means driver is in WIFI_ADHOC_MASTER_STATE, we needn't create bss again. */
				पूर्ण
			पूर्ण अन्यथा अणु
				rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_JOINBSS, 1);
			पूर्ण
		पूर्ण अन्यथा अणु
			rtw_disassoc_cmd(padapter, 0, true);

			अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true)
				rtw_indicate_disconnect(padapter);

			rtw_मुक्त_assoc_resources(padapter, 1);

			अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true) अणु
				_clr_fwstate_(pmlmepriv, WIFI_ADHOC_MASTER_STATE);
				set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			पूर्ण
		पूर्ण
	पूर्ण

handle_tkip_countermeasure:
	अगर (rtw_handle_tkip_countermeasure(padapter, __func__) == _FAIL) अणु
		status = _FAIL;
		जाओ release_mlme_lock;
	पूर्ण

	अगर (rtw_validate_ssid(ssid) == false) अणु
		status = _FAIL;
		जाओ release_mlme_lock;
	पूर्ण

	स_नकल(&pmlmepriv->assoc_ssid, ssid, माप(काष्ठा ndis_802_11_ssid));
	pmlmepriv->assoc_by_bssid = false;

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY) == true)
		pmlmepriv->to_join = true;
	अन्यथा
		status = rtw_करो_join(padapter);

release_mlme_lock:
	spin_unlock_bh(&pmlmepriv->lock);

निकास:

	वापस status;
पूर्ण

u8 rtw_set_802_11_connect(काष्ठा adapter *padapter, u8 *bssid, काष्ठा ndis_802_11_ssid *ssid)
अणु
	u8 status = _SUCCESS;
	bool bssid_valid = true;
	bool ssid_valid = true;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (!ssid || rtw_validate_ssid(ssid) == false)
		ssid_valid = false;

	अगर (!bssid || rtw_validate_bssid(bssid) == false)
		bssid_valid = false;

	अगर (!ssid_valid && !bssid_valid) अणु
		status = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (padapter->hw_init_completed == false) अणु
		status = _FAIL;
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&pmlmepriv->lock);

	netdev_dbg(padapter->pnetdev, FUNC_ADPT_FMT "  fw_state = 0x%08x\n",
		   FUNC_ADPT_ARG(padapter), get_fwstate(pmlmepriv));

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY) == true)
		जाओ handle_tkip_countermeasure;
	अन्यथा अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING) == true)
		जाओ release_mlme_lock;

handle_tkip_countermeasure:
	अगर (rtw_handle_tkip_countermeasure(padapter, __func__) == _FAIL) अणु
		status = _FAIL;
		जाओ release_mlme_lock;
	पूर्ण

	अगर (ssid && ssid_valid)
		स_नकल(&pmlmepriv->assoc_ssid, ssid, माप(काष्ठा ndis_802_11_ssid));
	अन्यथा
		स_रखो(&pmlmepriv->assoc_ssid, 0, माप(काष्ठा ndis_802_11_ssid));

	अगर (bssid && bssid_valid) अणु
		स_नकल(&pmlmepriv->assoc_bssid, bssid, ETH_ALEN);
		pmlmepriv->assoc_by_bssid = true;
	पूर्ण अन्यथा अणु
		pmlmepriv->assoc_by_bssid = false;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY) == true)
		pmlmepriv->to_join = true;
	अन्यथा
		status = rtw_करो_join(padapter);

release_mlme_lock:
	spin_unlock_bh(&pmlmepriv->lock);

निकास:
	वापस status;
पूर्ण

u8 rtw_set_802_11_infraकाष्ठाure_mode(काष्ठा adapter *padapter,
	क्रमागत ndis_802_11_network_infraकाष्ठाure networktype)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा	wlan_network	*cur_network = &pmlmepriv->cur_network;
	क्रमागत ndis_802_11_network_infraकाष्ठाure *pold_state = &(cur_network->network.Infraकाष्ठाureMode);

	अगर (*pold_state != networktype) अणु
		अगर (*pold_state == Ndis802_11APMode) अणु
			/* change to other mode from Ndis802_11APMode */
			cur_network->join_res = -1;

			stop_ap_mode(padapter);
		पूर्ण

		spin_lock_bh(&pmlmepriv->lock);

		अगर ((check_fwstate(pmlmepriv, _FW_LINKED) == true) || (*pold_state == Ndis802_11IBSS))
			rtw_disassoc_cmd(padapter, 0, true);

		अगर ((check_fwstate(pmlmepriv, _FW_LINKED) == true) ||
			(check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true))
			rtw_मुक्त_assoc_resources(padapter, 1);

		अगर ((*pold_state == Ndis802_11Infraकाष्ठाure) || (*pold_state == Ndis802_11IBSS)) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true)
				rtw_indicate_disconnect(padapter); /* will clr Linked_state; beक्रमe this function, we must have checked whether issue dis-assoc_cmd or not */
	       पूर्ण

		*pold_state = networktype;

		_clr_fwstate_(pmlmepriv, ~WIFI_शून्य_STATE);

		चयन (networktype) अणु
		हाल Ndis802_11IBSS:
			set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			अवरोध;

		हाल Ndis802_11Infraकाष्ठाure:
			set_fwstate(pmlmepriv, WIFI_STATION_STATE);
			अवरोध;

		हाल Ndis802_11APMode:
			set_fwstate(pmlmepriv, WIFI_AP_STATE);
			start_ap_mode(padapter);
			/* rtw_indicate_connect(padapter); */

			अवरोध;

		हाल Ndis802_11AutoUnknown:
		हाल Ndis802_11Infraकाष्ठाureMax:
			अवरोध;
		पूर्ण

		/* SecClearAllKeys(adapter); */

		spin_unlock_bh(&pmlmepriv->lock);
	पूर्ण
	वापस true;
पूर्ण


u8 rtw_set_802_11_disassociate(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	spin_lock_bh(&pmlmepriv->lock);

	अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true) अणु
		rtw_disassoc_cmd(padapter, 0, true);
		rtw_indicate_disconnect(padapter);
		/* modअगरy क्रम CONFIG_IEEE80211W, none 11w can use it */
		rtw_मुक्त_assoc_resources_cmd(padapter);
		rtw_pwr_wakeup(padapter);
	पूर्ण

	spin_unlock_bh(&pmlmepriv->lock);

	वापस true;
पूर्ण

u8 rtw_set_802_11_bssid_list_scan(काष्ठा adapter *padapter, काष्ठा ndis_802_11_ssid *pssid, पूर्णांक ssid_max_num)
अणु
	काष्ठा	mlme_priv 	*pmlmepriv = &padapter->mlmepriv;
	u8 res = true;

	अगर (padapter == शून्य) अणु
		res = false;
		जाओ निकास;
	पूर्ण
	अगर (padapter->hw_init_completed == false) अणु
		res = false;
		जाओ निकास;
	पूर्ण

	अगर ((check_fwstate(pmlmepriv, _FW_UNDER_SURVEY|_FW_UNDER_LINKING) == true) ||
		(pmlmepriv->LinkDetectInfo.bBusyTraffic == true)) अणु
		/*  Scan or linking is in progress, करो nothing. */
		res = true;

	पूर्ण अन्यथा अणु
		अगर (rtw_is_scan_deny(padapter)) अणु
			indicate_wx_scan_complete_event(padapter);
			वापस _SUCCESS;
		पूर्ण

		spin_lock_bh(&pmlmepriv->lock);

		res = rtw_sitesurvey_cmd(padapter, pssid, ssid_max_num, शून्य, 0);

		spin_unlock_bh(&pmlmepriv->lock);
	पूर्ण
निकास:

	वापस res;
पूर्ण

u8 rtw_set_802_11_authentication_mode(काष्ठा adapter *padapter, क्रमागत ndis_802_11_authentication_mode authmode)
अणु
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	पूर्णांक res;
	u8 ret;

	psecuritypriv->ndisauthtype = authmode;

	अगर (psecuritypriv->ndisauthtype > 3)
		psecuritypriv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_8021X;

	res = rtw_set_auth(padapter, psecuritypriv);

	अगर (res == _SUCCESS)
		ret = true;
	अन्यथा
		ret = false;

	वापस ret;
पूर्ण

u8 rtw_set_802_11_add_wep(काष्ठा adapter *padapter, काष्ठा ndis_802_11_wep *wep)
अणु

	चिन्हित पूर्णांक		keyid, res;
	काष्ठा security_priv *psecuritypriv = &(padapter->securitypriv);
	u8 ret = _SUCCESS;

	keyid = wep->KeyIndex & 0x3fffffff;

	अगर (keyid >= 4) अणु
		ret = false;
		जाओ निकास;
	पूर्ण

	चयन (wep->KeyLength) अणु
	हाल 5:
		psecuritypriv->करोt11PrivacyAlgrthm = _WEP40_;
		अवरोध;
	हाल 13:
		psecuritypriv->करोt11PrivacyAlgrthm = _WEP104_;
		अवरोध;
	शेष:
		psecuritypriv->करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		अवरोध;
	पूर्ण

	स_नकल(&(psecuritypriv->करोt11DefKey[keyid].skey[0]), &(wep->KeyMaterial), wep->KeyLength);

	psecuritypriv->करोt11DefKeylen[keyid] = wep->KeyLength;

	psecuritypriv->करोt11PrivacyKeyIndex = keyid;

	res = rtw_set_key(padapter, psecuritypriv, keyid, 1, true);

	अगर (res == _FAIL)
		ret = false;
निकास:

	वापस ret;
पूर्ण

/*
* rtw_get_cur_max_rate -
* @adapter: poपूर्णांकer to काष्ठा adapter काष्ठाure
*
* Return 0 or 100Kbps
*/
u16 rtw_get_cur_max_rate(काष्ठा adapter *adapter)
अणु
	पूर्णांक	i = 0;
	u16 rate = 0, max_rate = 0;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा wlan_bssid_ex	*pcur_bss = &pmlmepriv->cur_network.network;
	काष्ठा sta_info *psta = शून्य;
	u8 लघु_GI = 0;
	u8 rf_type = 0;

	अगर ((check_fwstate(pmlmepriv, _FW_LINKED) != true)
		&& (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) != true))
		वापस 0;

	psta = rtw_get_stainfo(&adapter->stapriv, get_bssid(pmlmepriv));
	अगर (psta == शून्य)
		वापस 0;

	लघु_GI = query_ra_लघु_GI(psta);

	अगर (IsSupportedHT(psta->wireless_mode)) अणु
		rtw_hal_get_hwreg(adapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));

		max_rate = rtw_mcs_rate(rf_type,
					((psta->bw_mode == CHANNEL_WIDTH_40)?1:0),
					लघु_GI,
					psta->htpriv.ht_cap.mcs.rx_mask);
	पूर्ण अन्यथा अणु
		जबतक ((pcur_bss->SupportedRates[i] != 0) && (pcur_bss->SupportedRates[i] != 0xFF)) अणु
			rate = pcur_bss->SupportedRates[i]&0x7F;
			अगर (rate > max_rate)
				max_rate = rate;
			i++;
		पूर्ण

		max_rate = max_rate*10/2;
	पूर्ण

	वापस max_rate;
पूर्ण
