<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_IOCTL_SET_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <rtw_ioctl_set.h>
#समावेश <hal_पूर्णांकf.h>

अटल स्थिर काष्ठा अणु
        पूर्णांक channel_plan;
        अक्षर *name;
पूर्ण channel_table[] = अणु अणु RT_CHANNEL_DOMAIN_FCC, "US" पूर्ण,
        अणु RT_CHANNEL_DOMAIN_ETSI, "EU" पूर्ण,
        अणु RT_CHANNEL_DOMAIN_MKK, "JP" पूर्ण,
        अणु RT_CHANNEL_DOMAIN_CHINA, "CN"पूर्ण पूर्ण;

बाह्य व्योम indicate_wx_scan_complete_event(काष्ठा adapter *padapter);

u8 rtw_करो_join(काष्ठा adapter *padapter)
अणु
	काष्ठा list_head *plist, *phead;
	u8 *pibss = शून्य;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा __queue *queue = &pmlmepriv->scanned_queue;
	u8 ret = _SUCCESS;

	spin_lock_bh(&pmlmepriv->scanned_queue.lock);
	phead = get_list_head(queue);
	plist = phead->next;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("\n %s: phead = %p; plist = %p\n\n\n", __func__, phead, plist));

	pmlmepriv->cur_network.join_res = -2;

	set_fwstate(pmlmepriv, _FW_UNDER_LINKING);

	pmlmepriv->pscanned = plist;

	pmlmepriv->to_join = true;

	अगर (list_empty(&queue->queue)) अणु
		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

		/* when set_ssid/set_bssid क्रम rtw_करो_join(), but scanning queue is empty */
		/* we try to issue sitesurvey firstly */

		अगर (!pmlmepriv->LinkDetectInfo.bBusyTraffic ||
		    pmlmepriv->to_roaming > 0) अणु
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("%s: site survey if scanned_queue is empty\n.", __func__));
			/*  submit site_survey_cmd */
			ret = rtw_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid, 1, शून्य, 0);
			अगर (ret != _SUCCESS) अणु
				pmlmepriv->to_join = false;
				RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("%s: site survey return error\n.", __func__));
			पूर्ण
		पूर्ण अन्यथा अणु
			pmlmepriv->to_join = false;
			ret = _FAIL;
		पूर्ण

		जाओ निकास;
	पूर्ण अन्यथा अणु
		पूर्णांक select_ret;

		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
		select_ret = rtw_select_and_join_from_scanned_queue(pmlmepriv);
		अगर (select_ret == _SUCCESS) अणु
			pmlmepriv->to_join = false;
			mod_समयr(&pmlmepriv->assoc_समयr,
				  jअगरfies + msecs_to_jअगरfies(MAX_JOIN_TIMEOUT));
		पूर्ण अन्यथा अणु
			अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
				/*  submit createbss_cmd to change to a ADHOC_MASTER */

				/* pmlmepriv->lock has been acquired by caller... */
				काष्ठा wlan_bssid_ex    *pdev_network = &padapter->registrypriv.dev_network;

				pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;

				pibss = padapter->registrypriv.dev_network.MacAddress;

				स_नकल(&pdev_network->ssid, &pmlmepriv->assoc_ssid, माप(काष्ठा ndis_802_11_ssid));

				rtw_update_registrypriv_dev_network(padapter);

				rtw_generate_अक्रमom_ibss(pibss);

				अगर (rtw_createbss_cmd(padapter) != _SUCCESS) अणु
					RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("***Error =>do_goin: rtw_createbss_cmd status FAIL***\n "));
					ret =  false;
					जाओ निकास;
				पूर्ण
				pmlmepriv->to_join = false;

				RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
					 ("***Error => rtw_select_and_join_from_scanned_queue FAIL under STA_Mode***\n "));
			पूर्ण अन्यथा अणु
				/*  can't associate ; reset under-linking */
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

				/* when set_ssid/set_bssid क्रम rtw_करो_join(), but there are no desired bss in scanning queue */
				/* we try to issue sitesurvey firstly */
				अगर (!pmlmepriv->LinkDetectInfo.bBusyTraffic ||
				    pmlmepriv->to_roaming > 0) अणु
					ret = rtw_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid, 1, शून्य, 0);
					अगर (ret != _SUCCESS) अणु
						pmlmepriv->to_join = false;
						RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("do_join(): site survey return error\n."));
					पूर्ण
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
	u32 cur_समय = 0;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	DBG_88E_LEVEL(_drv_info_, "set bssid:%pM\n", bssid);

	अगर ((bssid[0] == 0x00 && bssid[1] == 0x00 && bssid[2] == 0x00 &&
	     bssid[3] == 0x00 && bssid[4] == 0x00 && bssid[5] == 0x00) ||
	    (bssid[0] == 0xFF && bssid[1] == 0xFF && bssid[2] == 0xFF &&
	     bssid[3] == 0xFF && bssid[4] == 0xFF && bssid[5] == 0xFF)) अणु
		status = _FAIL;
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&pmlmepriv->lock);

	DBG_88E("Set BSSID under fw_state = 0x%08x\n", get_fwstate(pmlmepriv));
	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		जाओ handle_tkip_countermeasure;
	अन्यथा अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING))
		जाओ release_mlme_lock;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE)) अणु
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("set_bssid: _FW_LINKED||WIFI_ADHOC_MASTER_STATE\n"));

		अगर (!स_भेद(&pmlmepriv->cur_network.network.MacAddress, bssid, ETH_ALEN)) अणु
			अगर (!check_fwstate(pmlmepriv, WIFI_STATION_STATE))
				जाओ release_mlme_lock;/* it means driver is in WIFI_ADHOC_MASTER_STATE, we needn't create bss again. */
		पूर्ण अन्यथा अणु
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("Set BSSID not the same bssid\n"));
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("set_bssid =%pM\n", (bssid)));
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("cur_bssid =%pM\n", (pmlmepriv->cur_network.network.MacAddress)));

			rtw_disassoc_cmd(padapter, 0, true);

			अगर (check_fwstate(pmlmepriv, _FW_LINKED))
				rtw_indicate_disconnect(padapter);

			rtw_मुक्त_assoc_resources(padapter);

			अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
				_clr_fwstate_(pmlmepriv, WIFI_ADHOC_MASTER_STATE);
				set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			पूर्ण
		पूर्ण
	पूर्ण

handle_tkip_countermeasure:
	/* should we add something here...? */

	अगर (padapter->securitypriv.btkip_countermeasure) अणु
		cur_समय = jअगरfies;

		अगर (cur_समय - padapter->securitypriv.btkip_countermeasure_समय > 60 * HZ) अणु
			padapter->securitypriv.btkip_countermeasure = false;
			padapter->securitypriv.btkip_countermeasure_समय = 0;
		पूर्ण अन्यथा अणु
			status = _FAIL;
			जाओ release_mlme_lock;
		पूर्ण
	पूर्ण

	स_नकल(&pmlmepriv->assoc_bssid, bssid, ETH_ALEN);
	pmlmepriv->assoc_by_bssid = true;

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		pmlmepriv->to_join = true;
	अन्यथा
		status = rtw_करो_join(padapter);

release_mlme_lock:
	spin_unlock_bh(&pmlmepriv->lock);

निकास:
	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_,
		 ("%s: status=%d\n", __func__, status));

	वापस status;
पूर्ण

u8 rtw_set_802_11_ssid(काष्ठा adapter *padapter, काष्ठा ndis_802_11_ssid *ssid)
अणु
	u8 status = _SUCCESS;
	u32 cur_समय = 0;

	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network *pnetwork = &pmlmepriv->cur_network;

	DBG_88E_LEVEL(_drv_info_, "set ssid [%s] fw_state=0x%08x\n",
		      ssid->ssid, get_fwstate(pmlmepriv));

	अगर (!padapter->hw_init_completed) अणु
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_,
			 ("set_ssid: hw_init_completed == false =>exit!!!\n"));
		status = _FAIL;
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&pmlmepriv->lock);

	DBG_88E("Set SSID under fw_state = 0x%08x\n", get_fwstate(pmlmepriv));
	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		जाओ handle_tkip_countermeasure;
	अन्यथा अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING))
		जाओ release_mlme_lock;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED | WIFI_ADHOC_MASTER_STATE)) अणु
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
			 ("set_ssid: _FW_LINKED||WIFI_ADHOC_MASTER_STATE\n"));

		अगर (pmlmepriv->assoc_ssid.ssid_length == ssid->ssid_length &&
		    !स_भेद(&pmlmepriv->assoc_ssid.ssid, ssid->ssid, ssid->ssid_length)) अणु
			अगर (!check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
				RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_,
					 ("Set SSID is the same ssid, fw_state = 0x%08x\n",
					  get_fwstate(pmlmepriv)));

				अगर (!rtw_is_same_ibss(padapter, pnetwork)) अणु
					/* अगर in WIFI_ADHOC_MASTER_STATE | WIFI_ADHOC_STATE, create bss or rejoin again */
					rtw_disassoc_cmd(padapter, 0, true);

					अगर (check_fwstate(pmlmepriv, _FW_LINKED))
						rtw_indicate_disconnect(padapter);

					rtw_मुक्त_assoc_resources(padapter);

					अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
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
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("Set SSID not the same ssid\n"));
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("set_ssid =[%s] len = 0x%x\n", ssid->ssid, (अचिन्हित पूर्णांक)ssid->ssid_length));
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("assoc_ssid =[%s] len = 0x%x\n", pmlmepriv->assoc_ssid.ssid, (अचिन्हित पूर्णांक)pmlmepriv->assoc_ssid.ssid_length));

			rtw_disassoc_cmd(padapter, 0, true);

			अगर (check_fwstate(pmlmepriv, _FW_LINKED))
				rtw_indicate_disconnect(padapter);

			rtw_मुक्त_assoc_resources(padapter);

			अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
				_clr_fwstate_(pmlmepriv, WIFI_ADHOC_MASTER_STATE);
				set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			पूर्ण
		पूर्ण
	पूर्ण

handle_tkip_countermeasure:

	अगर (padapter->securitypriv.btkip_countermeasure) अणु
		cur_समय = jअगरfies;

		अगर (cur_समय - padapter->securitypriv.btkip_countermeasure_समय > 60 * HZ) अणु
			padapter->securitypriv.btkip_countermeasure = false;
			padapter->securitypriv.btkip_countermeasure_समय = 0;
		पूर्ण अन्यथा अणु
			status = _FAIL;
			जाओ release_mlme_lock;
		पूर्ण
	पूर्ण

	स_नकल(&pmlmepriv->assoc_ssid, ssid, माप(काष्ठा ndis_802_11_ssid));
	pmlmepriv->assoc_by_bssid = false;

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		pmlmepriv->to_join = true;
	अन्यथा
		status = rtw_करो_join(padapter);

release_mlme_lock:
	spin_unlock_bh(&pmlmepriv->lock);

निकास:
	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_,
		 ("-%s: status =%d\n", __func__, status));
	वापस status;
पूर्ण

u8 rtw_set_802_11_infraकाष्ठाure_mode(काष्ठा adapter *padapter,
				      क्रमागत ndis_802_11_network_infra networktype)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network *cur_network = &pmlmepriv->cur_network;
	क्रमागत ndis_802_11_network_infra *pold_state = &cur_network->network.Infraकाष्ठाureMode;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_notice_,
		 ("+%s: old =%d new =%d fw_state = 0x%08x\n", __func__,
		  *pold_state, networktype, get_fwstate(pmlmepriv)));

	अगर (*pold_state != networktype) अणु
		spin_lock_bh(&pmlmepriv->lock);

		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, (" change mode!"));
		/* DBG_88E("change mode, old_mode =%d, new_mode =%d, fw_state = 0x%x\n", *pold_state, networktype, get_fwstate(pmlmepriv)); */

		अगर (*pold_state == Ndis802_11APMode) अणु
			/* change to other mode from Ndis802_11APMode */
			cur_network->join_res = -1;

#अगर_घोषित CONFIG_88EU_AP_MODE
			stop_ap_mode(padapter);
#पूर्ण_अगर
		पूर्ण

		अगर (check_fwstate(pmlmepriv, _FW_LINKED) ||
		    *pold_state == Ndis802_11IBSS)
			rtw_disassoc_cmd(padapter, 0, true);

		अगर (check_fwstate(pmlmepriv, _FW_LINKED) ||
		    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE))
			rtw_मुक्त_assoc_resources(padapter);

		अगर (*pold_state == Ndis802_11Infraकाष्ठाure ||
		    *pold_state == Ndis802_11IBSS) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED))
				rtw_indicate_disconnect(padapter); /* will clr Linked_state; beक्रमe this function, we must have checked whether  issue dis-assoc_cmd or not */
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
#अगर_घोषित CONFIG_88EU_AP_MODE
			start_ap_mode(padapter);
#पूर्ण_अगर
			अवरोध;
		हाल Ndis802_11AutoUnknown:
		हाल Ndis802_11Infraकाष्ठाureMax:
			अवरोध;
		पूर्ण
		spin_unlock_bh(&pmlmepriv->lock);
	पूर्ण

	वापस true;
पूर्ण

u8 rtw_set_802_11_disassociate(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	spin_lock_bh(&pmlmepriv->lock);

	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
			 ("MgntActrtw_set_802_11_disassociate: rtw_indicate_disconnect\n"));

		rtw_disassoc_cmd(padapter, 0, true);
		rtw_indicate_disconnect(padapter);
		rtw_मुक्त_assoc_resources(padapter);
		rtw_pwr_wakeup(padapter);
	पूर्ण

	spin_unlock_bh(&pmlmepriv->lock);

	वापस true;
पूर्ण

u8 rtw_set_802_11_bssid_list_scan(काष्ठा adapter *padapter, काष्ठा ndis_802_11_ssid *pssid, पूर्णांक ssid_max_num)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 res = true;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("+%s(), fw_state =%x\n", __func__, get_fwstate(pmlmepriv)));

	अगर (!padapter) अणु
		res = false;
		जाओ निकास;
	पूर्ण
	अगर (!padapter->hw_init_completed) अणु
		res = false;
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("\n === %s:hw_init_completed == false ===\n", __func__));
		जाओ निकास;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING) ||
	    pmlmepriv->LinkDetectInfo.bBusyTraffic) अणु
		/*  Scan or linking is in progress, करो nothing. */
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("%s fail since fw_state = %x\n", __func__, get_fwstate(pmlmepriv)));
		res = true;

		अगर (check_fwstate(pmlmepriv,
				  _FW_UNDER_SURVEY | _FW_UNDER_LINKING))
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("\n###_FW_UNDER_SURVEY|_FW_UNDER_LINKING\n\n"));
		अन्यथा
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("\n###pmlmepriv->sitesurveyctrl.traffic_busy == true\n\n"));

	पूर्ण अन्यथा अणु
		अगर (rtw_is_scan_deny(padapter)) अणु
			DBG_88E(FUNC_ADPT_FMT": scan deny\n", FUNC_ADPT_ARG(padapter));
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

u8 rtw_set_802_11_authentication_mode(काष्ठा adapter *padapter, क्रमागत ndis_802_11_auth_mode authmode)
अणु
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	पूर्णांक res;
	u8 ret;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
		 ("set_802_11_auth.mode(): mode =%x\n", authmode));

	psecuritypriv->ndisauthtype = authmode;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
		 ("%s:psecuritypriv->ndisauthtype=%d", __func__,
		 psecuritypriv->ndisauthtype));

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
	पूर्णांक keyid, res;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	u8 ret = _SUCCESS;

	keyid = wep->KeyIndex & 0x3fffffff;

	अगर (keyid >= 4) अणु
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("MgntActrtw_set_802_11_add_wep:keyid>4 =>fail\n"));
		ret = false;
		जाओ निकास;
	पूर्ण

	चयन (wep->KeyLength) अणु
	हाल 5:
		psecuritypriv->करोt11PrivacyAlgrthm = _WEP40_;
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("MgntActrtw_set_802_11_add_wep:wep->KeyLength = 5\n"));
		अवरोध;
	हाल 13:
		psecuritypriv->करोt11PrivacyAlgrthm = _WEP104_;
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("MgntActrtw_set_802_11_add_wep:wep->KeyLength = 13\n"));
		अवरोध;
	शेष:
		psecuritypriv->करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("MgntActrtw_set_802_11_add_wep:wep->KeyLength!= 5 or 13\n"));
		अवरोध;
	पूर्ण
	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
		 ("%s:before memcpy, wep->KeyLength = 0x%x wep->KeyIndex = 0x%x  keyid =%x\n", __func__,
		 wep->KeyLength, wep->KeyIndex, keyid));

	स_नकल(&psecuritypriv->करोt11DefKey[keyid].skey[0],
	       &wep->KeyMaterial, wep->KeyLength);

	psecuritypriv->करोt11DefKeylen[keyid] = wep->KeyLength;

	psecuritypriv->करोt11PrivacyKeyIndex = keyid;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
		 ("%s:security key material : %x %x %x %x %x %x %x %x %x %x %x %x %x\n", __func__,
		 psecuritypriv->करोt11DefKey[keyid].skey[0],
		 psecuritypriv->करोt11DefKey[keyid].skey[1],
		 psecuritypriv->करोt11DefKey[keyid].skey[2],
		 psecuritypriv->करोt11DefKey[keyid].skey[3],
		 psecuritypriv->करोt11DefKey[keyid].skey[4],
		 psecuritypriv->करोt11DefKey[keyid].skey[5],
		 psecuritypriv->करोt11DefKey[keyid].skey[6],
		 psecuritypriv->करोt11DefKey[keyid].skey[7],
		 psecuritypriv->करोt11DefKey[keyid].skey[8],
		 psecuritypriv->करोt11DefKey[keyid].skey[9],
		 psecuritypriv->करोt11DefKey[keyid].skey[10],
		 psecuritypriv->करोt11DefKey[keyid].skey[11],
		 psecuritypriv->करोt11DefKey[keyid].skey[12]));

	res = rtw_set_key(padapter, psecuritypriv, keyid, 1);

	अगर (res == _FAIL)
		ret = false;
निकास:
	वापस ret;
पूर्ण

/* Return 0 or 100Kbps */
u16 rtw_get_cur_max_rate(काष्ठा adapter *adapter)
अणु
	पूर्णांक i = 0;
	u8 *p;
	u16 rate = 0, max_rate = 0;
	काष्ठा mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा registry_priv *pregistrypriv = &adapter->registrypriv;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा wlan_bssid_ex *pcur_bss = &pmlmepriv->cur_network.network;
	u8 bw_40MHz = 0, लघु_GI_20 = 0, लघु_GI_40 = 0;
	u32 ht_ielen = 0;

	अगर (!check_fwstate(pmlmepriv, _FW_LINKED) &&
	    !check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE))
		वापस 0;

	अगर (pmlmeext->cur_wireless_mode & (WIRELESS_11_24N | WIRELESS_11_5N)) अणु
		p = rtw_get_ie(&pcur_bss->ies[12], WLAN_EID_HT_CAPABILITY,
			       &ht_ielen, pcur_bss->ie_length - 12);
		अगर (p && ht_ielen > 0) अणु
			/* cur_bwmod is updated by beacon, pmlmeinfo is updated by association response */
			bw_40MHz = (pmlmeext->cur_bwmode && (HT_INFO_HT_PARAM_REC_TRANS_CHNL_WIDTH & pmlmeinfo->HT_info.infos[0])) ? 1 : 0;

			लघु_GI_20 = (le16_to_cpu(pmlmeinfo->HT_caps.cap_info) & IEEE80211_HT_CAP_SGI_20) ? 1 : 0;
			लघु_GI_40 = (le16_to_cpu(pmlmeinfo->HT_caps.cap_info) & IEEE80211_HT_CAP_SGI_40) ? 1 : 0;

			max_rate = rtw_mcs_rate(
				RF_1T1R,
				bw_40MHz & pregistrypriv->cbw40_enable,
				लघु_GI_20,
				लघु_GI_40,
				pmlmeinfo->HT_caps.mcs.rx_mask
			);
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (pcur_bss->SupportedRates[i] != 0 &&
		       pcur_bss->SupportedRates[i] != 0xFF) अणु
			rate = pcur_bss->SupportedRates[i] & 0x7F;
			अगर (rate > max_rate)
				max_rate = rate;
			i++;
		पूर्ण

		max_rate *= 5;
	पूर्ण

	वापस max_rate;
पूर्ण

/* Return _SUCCESS or _FAIL */
पूर्णांक rtw_set_country(काष्ठा adapter *adapter, स्थिर अक्षर *country_code)
अणु
	पूर्णांक i;
	पूर्णांक channel_plan = RT_CHANNEL_DOMAIN_WORLD_WIDE_5G;

	DBG_88E("%s country_code:%s\n", __func__, country_code);
	क्रम (i = 0; i < ARRAY_SIZE(channel_table); i++) अणु
		अगर (म_भेद(channel_table[i].name, country_code) == 0) अणु
			channel_plan = channel_table[i].channel_plan;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(channel_table))
		DBG_88E("%s unknown country_code:%s\n", __func__, country_code);

	वापस rtw_set_chplan_cmd(adapter, channel_plan, 1);
पूर्ण
