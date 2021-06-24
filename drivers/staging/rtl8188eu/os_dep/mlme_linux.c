<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#घोषणा _MLME_OSDEP_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <mlme_osdep.h>

व्योम rtw_init_mlme_समयr(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	समयr_setup(&pmlmepriv->assoc_समयr, _rtw_join_समयout_handler, 0);
	समयr_setup(&pmlmepriv->scan_to_समयr, rtw_scan_समयout_handler, 0);
	समयr_setup(&pmlmepriv->dynamic_chk_समयr,
		    rtw_dynamic_check_समयr_handlder, 0);
पूर्ण

व्योम rtw_os_indicate_connect(काष्ठा adapter *adapter)
अणु
	rtw_indicate_wx_assoc_event(adapter);
	netअगर_carrier_on(adapter->pnetdev);
पूर्ण

अटल काष्ठा rt_pmkid_list backup_pmkid[NUM_PMKID_CACHE];

व्योम rtw_reset_securitypriv(काष्ठा adapter *adapter)
अणु
	u8 backup_index;
	u8 backup_counter;
	u32 backup_समय;
	काष्ठा security_priv *psec_priv = &adapter->securitypriv;

	अगर (psec_priv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X) अणु
		/* 802.1x
		 * We have to backup the PMK inक्रमmation क्रम WiFi PMK Caching
		 * test item. Backup the btkip_countermeasure inक्रमmation. When
		 * the countermeasure is trigger, the driver have to disconnect
		 * with AP क्रम 60 seconds.
		 */
		स_नकल(backup_pmkid, psec_priv->PMKIDList,
		       माप(काष्ठा rt_pmkid_list) * NUM_PMKID_CACHE);
		backup_index = psec_priv->PMKIDIndex;
		backup_counter = psec_priv->btkip_countermeasure;
		backup_समय = psec_priv->btkip_countermeasure_समय;

		स_रखो(psec_priv, 0, माप(*psec_priv));

		/* Restore the PMK inक्रमmation to securitypriv काष्ठाure
		 * क्रम the following connection.
		 */
		स_नकल(psec_priv->PMKIDList, backup_pmkid,
		       माप(काष्ठा rt_pmkid_list) * NUM_PMKID_CACHE);
		psec_priv->PMKIDIndex = backup_index;
		psec_priv->btkip_countermeasure = backup_counter;
		psec_priv->btkip_countermeasure_समय = backup_समय;
		psec_priv->ndisauthtype = Ndis802_11AuthModeOpen;
		psec_priv->ndisencryptstatus = Ndis802_11WEPDisabled;
	पूर्ण अन्यथा अणु
		/* reset values in securitypriv */
		psec_priv->करोt11AuthAlgrthm = करोt11AuthAlgrthm_Open;
		psec_priv->करोt11PrivacyAlgrthm = _NO_PRIVACY_;
		psec_priv->करोt11PrivacyKeyIndex = 0;
		psec_priv->करोt118021XGrpPrivacy = _NO_PRIVACY_;
		psec_priv->करोt118021XGrpKeyid = 1;
		psec_priv->ndisauthtype = Ndis802_11AuthModeOpen;
		psec_priv->ndisencryptstatus = Ndis802_11WEPDisabled;
	पूर्ण
पूर्ण

व्योम rtw_os_indicate_disconnect(काष्ठा adapter *adapter)
अणु
	/* Do it first क्रम tx broadcast pkt after disconnection issue! */
	netअगर_carrier_off(adapter->pnetdev);
	rtw_indicate_wx_disassoc_event(adapter);
	rtw_reset_securitypriv(adapter);
पूर्ण

व्योम rtw_report_sec_ie(काष्ठा adapter *adapter, u8 authmode, u8 *sec_ie)
अणु
	uपूर्णांक len;
	u8 *buff, *p, i;
	जोड़ iwreq_data wrqu;

	RT_TRACE(_module_mlme_osdep_c_, _drv_info_,
		 ("+%s, authmode=%d\n", __func__, authmode));
	buff = शून्य;
	अगर (authmode == WLAN_EID_VENDOR_SPECIFIC) अणु
		RT_TRACE(_module_mlme_osdep_c_, _drv_info_,
			 ("%s, authmode=%d\n", __func__, authmode));
		buff = rtw_दो_स्मृति(IW_CUSTOM_MAX);
		अगर (!buff)
			वापस;
		स_रखो(buff, 0, IW_CUSTOM_MAX);
		p = buff;
		p += प्र_लिखो(p, "ASSOCINFO(ReqIEs =");
		len = sec_ie[1] + 2;
		len =  min_t(uपूर्णांक, len, IW_CUSTOM_MAX);
		क्रम (i = 0; i < len; i++)
			p += प्र_लिखो(p, "%02x", sec_ie[i]);
		p += प्र_लिखो(p, ")");
		स_रखो(&wrqu, 0, माप(wrqu));
		wrqu.data.length = min_t(__u16, p - buff, IW_CUSTOM_MAX);
		wireless_send_event(adapter->pnetdev, IWEVCUSTOM, &wrqu, buff);
		kमुक्त(buff);
	पूर्ण
पूर्ण

व्योम init_addba_retry_समयr(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	समयr_setup(&psta->addba_retry_समयr, addba_समयr_hdl, 0);
पूर्ण

व्योम init_mlme_ext_समयr(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	समयr_setup(&pmlmeext->survey_समयr, survey_समयr_hdl, 0);
	समयr_setup(&pmlmeext->link_समयr, link_समयr_hdl, 0);
पूर्ण

#अगर_घोषित CONFIG_88EU_AP_MODE

व्योम rtw_indicate_sta_assoc_event(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	जोड़ iwreq_data wrqu;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	अगर (!psta)
		वापस;

	अगर (psta->aid > NUM_STA)
		वापस;

	अगर (pstapriv->sta_aid[psta->aid - 1] != psta)
		वापस;

	wrqu.addr.sa_family = ARPHRD_ETHER;

	स_नकल(wrqu.addr.sa_data, psta->hwaddr, ETH_ALEN);

	DBG_88E("+%s\n", __func__);

	wireless_send_event(padapter->pnetdev, IWEVREGISTERED, &wrqu, शून्य);
पूर्ण

व्योम rtw_indicate_sta_disassoc_event(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	जोड़ iwreq_data wrqu;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	अगर (!psta)
		वापस;

	अगर (psta->aid > NUM_STA)
		वापस;

	अगर (pstapriv->sta_aid[psta->aid - 1] != psta)
		वापस;

	wrqu.addr.sa_family = ARPHRD_ETHER;

	स_नकल(wrqu.addr.sa_data, psta->hwaddr, ETH_ALEN);

	DBG_88E("+%s\n", __func__);

	wireless_send_event(padapter->pnetdev, IWEVEXPIRED, &wrqu, शून्य);
पूर्ण

#पूर्ण_अगर
