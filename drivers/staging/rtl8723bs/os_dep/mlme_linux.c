<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/


#घोषणा _MLME_OSDEP_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>

अटल व्योम _dynamic_check_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter =
		from_समयr(adapter, t, mlmepriv.dynamic_chk_समयr);

	rtw_dynamic_check_समयr_handler(adapter);

	_set_समयr(&adapter->mlmepriv.dynamic_chk_समयr, 2000);
पूर्ण

अटल व्योम _rtw_set_scan_deny_समयr_hdl(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter =
		from_समयr(adapter, t, mlmepriv.set_scan_deny_समयr);

	rtw_clear_scan_deny(adapter);
पूर्ण

व्योम rtw_init_mlme_समयr(काष्ठा adapter *padapter)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	समयr_setup(&pmlmepriv->assoc_समयr, _rtw_join_समयout_handler, 0);
	समयr_setup(&pmlmepriv->scan_to_समयr, rtw_scan_समयout_handler, 0);
	समयr_setup(&pmlmepriv->dynamic_chk_समयr,
		    _dynamic_check_समयr_handler, 0);
	समयr_setup(&pmlmepriv->set_scan_deny_समयr,
		    _rtw_set_scan_deny_समयr_hdl, 0);
पूर्ण

व्योम rtw_os_indicate_connect(काष्ठा adapter *adapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &(adapter->mlmepriv);

	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true)) अणु
		rtw_cfg80211_ibss_indicate_connect(adapter);
	पूर्ण अन्यथा अणु
		rtw_cfg80211_indicate_connect(adapter);
	पूर्ण

	rtw_indicate_wx_assoc_event(adapter);
	netअगर_carrier_on(adapter->pnetdev);

	अगर (adapter->pid[2] != 0)
		rtw_संकेत_process(adapter->pid[2], SIGALRM);
पूर्ण

व्योम rtw_os_indicate_scan_करोne(काष्ठा adapter *padapter, bool पातed)
अणु
	rtw_cfg80211_indicate_scan_करोne(padapter, पातed);
	indicate_wx_scan_complete_event(padapter);
पूर्ण

अटल काष्ठा rt_pmkid_list   backupPMKIDList[NUM_PMKID_CACHE];
व्योम rtw_reset_securitypriv(काष्ठा adapter *adapter)
अणु
	u8 backupPMKIDIndex = 0;
	u8 backupTKIPCountermeasure = 0x00;
	u32 backupTKIPcountermeasure_समय = 0;
	/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
	काष्ठा mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;

	spin_lock_bh(&adapter->security_key_mutex);

	अगर (adapter->securitypriv.करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X) अणु
		/* 802.1x */
		/*  Added by Albert 2009/02/18 */
		/*  We have to backup the PMK inक्रमmation क्रम WiFi PMK Caching test item. */
		/*  */
		/*  Backup the btkip_countermeasure inक्रमmation. */
		/*  When the countermeasure is trigger, the driver have to disconnect with AP क्रम 60 seconds. */

		स_नकल(&backupPMKIDList[0], &adapter->securitypriv.PMKIDList[0], माप(काष्ठा rt_pmkid_list) * NUM_PMKID_CACHE);
		backupPMKIDIndex = adapter->securitypriv.PMKIDIndex;
		backupTKIPCountermeasure = adapter->securitypriv.btkip_countermeasure;
		backupTKIPcountermeasure_समय = adapter->securitypriv.btkip_countermeasure_समय;

		/* reset RX BIP packet number */
		pmlmeext->mgnt_80211w_IPN_rx = 0;

		स_रखो((अचिन्हित अक्षर *)&adapter->securitypriv, 0, माप(काष्ठा security_priv));

		/*  Added by Albert 2009/02/18 */
		/*  Restore the PMK inक्रमmation to securitypriv काष्ठाure क्रम the following connection. */
		स_नकल(&adapter->securitypriv.PMKIDList[0], &backupPMKIDList[0], माप(काष्ठा rt_pmkid_list) * NUM_PMKID_CACHE);
		adapter->securitypriv.PMKIDIndex = backupPMKIDIndex;
		adapter->securitypriv.btkip_countermeasure = backupTKIPCountermeasure;
		adapter->securitypriv.btkip_countermeasure_समय = backupTKIPcountermeasure_समय;

		adapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
		adapter->securitypriv.ndisencryptstatus = Ndis802_11WEPDisabled;

	पूर्ण अन्यथा अणु
		/* reset values in securitypriv */
		/* अगर (adapter->mlmepriv.fw_state & WIFI_STATION_STATE) */
		/*  */
		काष्ठा security_priv *psec_priv = &adapter->securitypriv;

		psec_priv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;  /* खोलो प्रणाली */
		psec_priv->करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		psec_priv->करोt11PrivacyKeyIndex = 0;

		psec_priv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
		psec_priv->करोt118021XGrpKeyid = 1;

		psec_priv->ndisauthtype = Ndis802_11AuthModeOpen;
		psec_priv->ndisencryptstatus = Ndis802_11WEPDisabled;
		/*  */
	पूर्ण
	/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
	spin_unlock_bh(&adapter->security_key_mutex);
पूर्ण

व्योम rtw_os_indicate_disconnect(काष्ठा adapter *adapter)
अणु
	/* काष्ठा rt_pmkid_list   backupPMKIDList[ NUM_PMKID_CACHE ]; */

	netअगर_carrier_off(adapter->pnetdev); /*  Do it first क्रम tx broadcast pkt after disconnection issue! */

	rtw_cfg80211_indicate_disconnect(adapter);

	rtw_indicate_wx_disassoc_event(adapter);

	/* modअगरy क्रम CONFIG_IEEE80211W, none 11w also can use the same command */
	rtw_reset_securitypriv_cmd(adapter);
पूर्ण

व्योम rtw_report_sec_ie(काष्ठा adapter *adapter, u8 authmode, u8 *sec_ie)
अणु
	uपूर्णांक	len;
	u8 *buff, *p, i;
	जोड़ iwreq_data wrqu;

	buff = शून्य;
	अगर (authmode == WLAN_EID_VENDOR_SPECIFIC) अणु
		buff = rtw_zदो_स्मृति(IW_CUSTOM_MAX);
		अगर (!buff)
			वापस;

		p = buff;

		p += scnम_लिखो(p, IW_CUSTOM_MAX - (p - buff), "ASSOCINFO(ReqIEs =");

		len = sec_ie[1] + 2;
		len = (len < IW_CUSTOM_MAX) ? len : IW_CUSTOM_MAX;

		क्रम (i = 0; i < len; i++)
			p += scnम_लिखो(p, IW_CUSTOM_MAX - (p - buff), "%02x", sec_ie[i]);

		p += scnम_लिखो(p, IW_CUSTOM_MAX - (p - buff), ")");

		स_रखो(&wrqu, 0, माप(wrqu));

		wrqu.data.length = p - buff;

		wrqu.data.length = (wrqu.data.length < IW_CUSTOM_MAX) ? wrqu.data.length : IW_CUSTOM_MAX;

		kमुक्त(buff);
	पूर्ण
पूर्ण

व्योम init_addba_retry_समयr(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	समयr_setup(&psta->addba_retry_समयr, addba_समयr_hdl, 0);
पूर्ण

व्योम init_mlme_ext_समयr(काष्ठा adapter *padapter)
अणु
	काष्ठा	mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	समयr_setup(&pmlmeext->survey_समयr, survey_समयr_hdl, 0);
	समयr_setup(&pmlmeext->link_समयr, link_समयr_hdl, 0);
	समयr_setup(&pmlmeext->sa_query_समयr, sa_query_समयr_hdl, 0);
पूर्ण
