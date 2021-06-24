<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_MLME_C_

#समावेश <linux/ieee80211.h>

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <recv_osdep.h>
#समावेश <xmit_osdep.h>
#समावेश <hal_पूर्णांकf.h>
#समावेश <mlme_osdep.h>
#समावेश <sta_info.h>
#समावेश <wअगरi.h>
#समावेश <wlan_bssdef.h>
#समावेश <rtw_ioctl_set.h>
#समावेश <linux/vदो_स्मृति.h>

बाह्य स्थिर u8 MCS_rate_1R[16];

पूर्णांक rtw_init_mlme_priv(काष्ठा adapter *padapter)
अणु
	पूर्णांक i;
	u8 *pbuf;
	काष्ठा wlan_network *pnetwork;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	पूर्णांक res = _SUCCESS;

	/*  We करोn't need to स_रखो padapter->XXX to zero, because adapter is allocated by vzalloc(). */

	pmlmepriv->nic_hdl = (u8 *)padapter;

	pmlmepriv->pscanned = शून्य;
	pmlmepriv->fw_state = 0;
	pmlmepriv->cur_network.network.Infraकाष्ठाureMode = Ndis802_11AutoUnknown;
	pmlmepriv->scan_mode = SCAN_ACTIVE;/*  1: active, 0: passive. Maybe someday we should नाम this variable to "active_mode" (Jeff) */

	spin_lock_init(&pmlmepriv->lock);
	_rtw_init_queue(&pmlmepriv->मुक्त_bss_pool);
	_rtw_init_queue(&pmlmepriv->scanned_queue);

	स_रखो(&pmlmepriv->assoc_ssid, 0, माप(काष्ठा ndis_802_11_ssid));

	pbuf = vzalloc(array_size(MAX_BSS_CNT, माप(काष्ठा wlan_network)));

	अगर (!pbuf) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	pmlmepriv->मुक्त_bss_buf = pbuf;

	pnetwork = (काष्ठा wlan_network *)pbuf;

	क्रम (i = 0; i < MAX_BSS_CNT; i++) अणु
		INIT_LIST_HEAD(&pnetwork->list);

		list_add_tail(&pnetwork->list, &pmlmepriv->मुक्त_bss_pool.queue);

		pnetwork++;
	पूर्ण

	/* allocate DMA-able/Non-Page memory क्रम cmd_buf and rsp_buf */

	rtw_clear_scan_deny(padapter);

	rtw_init_mlme_समयr(padapter);

निकास:
	वापस res;
पूर्ण

#अगर defined(CONFIG_88EU_AP_MODE)
अटल व्योम rtw_मुक्त_mlme_ie_data(u8 **ppie, u32 *plen)
अणु
	kमुक्त(*ppie);
	*plen = 0;
	*ppie = शून्य;
पूर्ण

व्योम rtw_मुक्त_mlme_priv_ie_data(काष्ठा mlme_priv *pmlmepriv)
अणु
	rtw_buf_मुक्त(&pmlmepriv->assoc_req, &pmlmepriv->assoc_req_len);
	rtw_buf_मुक्त(&pmlmepriv->assoc_rsp, &pmlmepriv->assoc_rsp_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->wps_beacon_ie, &pmlmepriv->wps_beacon_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->wps_probe_req_ie, &pmlmepriv->wps_probe_req_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->wps_probe_resp_ie, &pmlmepriv->wps_probe_resp_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->wps_assoc_resp_ie, &pmlmepriv->wps_assoc_resp_ie_len);
पूर्ण
#अन्यथा
व्योम rtw_मुक्त_mlme_priv_ie_data(काष्ठा mlme_priv *pmlmepriv)
अणु
पूर्ण
#पूर्ण_अगर

व्योम rtw_मुक्त_mlme_priv(काष्ठा mlme_priv *pmlmepriv)
अणु
	अगर (pmlmepriv) अणु
		rtw_मुक्त_mlme_priv_ie_data(pmlmepriv);
		vमुक्त(pmlmepriv->मुक्त_bss_buf);
	पूर्ण
पूर्ण

काष्ठा wlan_network *rtw_alloc_network(काष्ठा mlme_priv *pmlmepriv)
					/* _queue *मुक्त_queue) */
अणु
	काष्ठा wlan_network *pnetwork;
	काष्ठा __queue *मुक्त_queue = &pmlmepriv->मुक्त_bss_pool;

	spin_lock_bh(&मुक्त_queue->lock);
	pnetwork = list_first_entry_or_null(&मुक्त_queue->queue,
					    काष्ठा wlan_network, list);
	अगर (!pnetwork)
		जाओ निकास;

	list_del_init(&pnetwork->list);

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
		 ("rtw_alloc_network: ptr=%p\n", &pnetwork->list));
	pnetwork->network_type = 0;
	pnetwork->fixed = false;
	pnetwork->last_scanned = jअगरfies;
	pnetwork->aid = 0;
	pnetwork->join_res = 0;

निकास:
	spin_unlock_bh(&मुक्त_queue->lock);

	वापस pnetwork;
पूर्ण

अटल व्योम _rtw_मुक्त_network(काष्ठा mlme_priv *pmlmepriv, काष्ठा wlan_network *pnetwork, u8 isमुक्तall)
अणु
	अचिन्हित दीर्घ curr_समय;
	u32 delta_समय;
	u32 lअगरeसमय = SCANQUEUE_LIFETIME;
	काष्ठा __queue *मुक्त_queue = &pmlmepriv->मुक्त_bss_pool;

	अगर (!pnetwork)
		वापस;

	अगर (pnetwork->fixed)
		वापस;
	curr_समय = jअगरfies;
	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)))
		lअगरeसमय = 1;
	अगर (!isमुक्तall) अणु
		delta_समय = (curr_समय - pnetwork->last_scanned) / HZ;
		अगर (delta_समय < lअगरeसमय)/*  unit:sec */
			वापस;
	पूर्ण
	spin_lock_bh(&मुक्त_queue->lock);
	list_del_init(&pnetwork->list);
	list_add_tail(&pnetwork->list, &मुक्त_queue->queue);
	spin_unlock_bh(&मुक्त_queue->lock);
पूर्ण

अटल व्योम rtw_मुक्त_network_nolock(काष्ठा mlme_priv *pmlmepriv,
				    काष्ठा wlan_network *pnetwork)
अणु
	काष्ठा __queue *मुक्त_queue = &pmlmepriv->मुक्त_bss_pool;

	अगर (!pnetwork)
		वापस;
	अगर (pnetwork->fixed)
		वापस;
	list_del_init(&pnetwork->list);
	list_add_tail(&pnetwork->list, get_list_head(मुक्त_queue));
पूर्ण

/*
 * वापस the wlan_network with the matching addr
 *
 * Shall be called under atomic context... to aव्योम possible racing condition...
 */
काष्ठा wlan_network *rtw_find_network(काष्ठा __queue *scanned_queue, u8 *addr)
अणु
	काष्ठा list_head *phead, *plist;
	काष्ठा wlan_network *pnetwork = शून्य;
	u8 zero_addr[ETH_ALEN] = अणु0, 0, 0, 0, 0, 0पूर्ण;

	अगर (!स_भेद(zero_addr, addr, ETH_ALEN)) अणु
		pnetwork = शून्य;
		जाओ निकास;
	पूर्ण
	phead = get_list_head(scanned_queue);
	plist = phead->next;

	जबतक (plist != phead) अणु
		pnetwork = container_of(plist, काष्ठा wlan_network, list);
		अगर (!स_भेद(addr, pnetwork->network.MacAddress, ETH_ALEN))
			अवरोध;
		plist = plist->next;
	पूर्ण
	अगर (plist == phead)
		pnetwork = शून्य;
निकास:
	वापस pnetwork;
पूर्ण

व्योम rtw_मुक्त_network_queue(काष्ठा adapter *padapter, u8 isमुक्तall)
अणु
	काष्ठा list_head *phead, *plist;
	काष्ठा wlan_network *pnetwork;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा __queue *scanned_queue = &pmlmepriv->scanned_queue;

	spin_lock_bh(&scanned_queue->lock);

	phead = get_list_head(scanned_queue);
	plist = phead->next;

	जबतक (phead != plist) अणु
		pnetwork = container_of(plist, काष्ठा wlan_network, list);

		plist = plist->next;

		_rtw_मुक्त_network(pmlmepriv, pnetwork, isमुक्तall);
	पूर्ण
	spin_unlock_bh(&scanned_queue->lock);
पूर्ण

पूर्णांक rtw_अगर_up(काष्ठा adapter *padapter)
अणु
	पूर्णांक res;

	अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved ||
	    !check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
			 ("%s:bDriverStopped(%d) OR bSurpriseRemoved(%d)",
			  __func__, padapter->bDriverStopped,
			  padapter->bSurpriseRemoved));
		res = false;
	पूर्ण अन्यथा अणु
		res =  true;
	पूर्ण
	वापस res;
पूर्ण

व्योम rtw_generate_अक्रमom_ibss(u8 *pibss)
अणु
	अचिन्हित दीर्घ curसमय = jअगरfies;

	pibss[0] = 0x02;  /* in ad-hoc mode bit1 must set to 1 */
	pibss[1] = 0x11;
	pibss[2] = 0x87;
	pibss[3] = (u8)(curसमय & 0xff);/* p[0]; */
	pibss[4] = (u8)((curसमय >> 8) & 0xff);/* p[1]; */
	pibss[5] = (u8)((curसमय >> 16) & 0xff);/* p[2]; */
पूर्ण

u8 *rtw_get_capability_from_ie(u8 *ie)
अणु
	वापस ie + 8 + 2;
पूर्ण

u16 rtw_get_capability(काष्ठा wlan_bssid_ex *bss)
अणु
	__le16 val;

	स_नकल((u8 *)&val, rtw_get_capability_from_ie(bss->ies), 2);

	वापस le16_to_cpu(val);
पूर्ण

u8 *rtw_get_beacon_पूर्णांकerval_from_ie(u8 *ie)
अणु
	वापस ie + 8;
पूर्ण

पूर्णांक rtw_is_same_ibss(काष्ठा adapter *adapter, काष्ठा wlan_network *pnetwork)
अणु
	पूर्णांक ret = true;
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;

	अगर ((psecuritypriv->करोt11PrivacyAlgrthm != _NO_PRIVACY_) &&
	    (pnetwork->network.Privacy == 0))
		ret = false;
	अन्यथा अगर ((psecuritypriv->करोt11PrivacyAlgrthm == _NO_PRIVACY_) &&
		 (pnetwork->network.Privacy == 1))
		ret = false;
	अन्यथा
		ret = true;
	वापस ret;
पूर्ण

अटल पूर्णांक is_same_ess(काष्ठा wlan_bssid_ex *a, काष्ठा wlan_bssid_ex *b)
अणु
	वापस (a->ssid.ssid_length == b->ssid.ssid_length) &&
	       !स_भेद(a->ssid.ssid, b->ssid.ssid, a->ssid.ssid_length);
पूर्ण

पूर्णांक is_same_network(काष्ठा wlan_bssid_ex *src, काष्ठा wlan_bssid_ex *dst)
अणु
	u16 s_cap, d_cap;
	__le16 le_scap, le_dcap;

	स_नकल((u8 *)&le_scap, rtw_get_capability_from_ie(src->ies), 2);
	स_नकल((u8 *)&le_dcap, rtw_get_capability_from_ie(dst->ies), 2);

	s_cap = le16_to_cpu(le_scap);
	d_cap = le16_to_cpu(le_dcap);

	वापस ((src->ssid.ssid_length == dst->ssid.ssid_length) &&
		(!स_भेद(src->MacAddress, dst->MacAddress, ETH_ALEN)) &&
		(!स_भेद(src->ssid.ssid, dst->ssid.ssid, src->ssid.ssid_length)) &&
		((s_cap & WLAN_CAPABILITY_IBSS) ==
		(d_cap & WLAN_CAPABILITY_IBSS)) &&
		((s_cap & WLAN_CAPABILITY_ESS) ==
		(d_cap & WLAN_CAPABILITY_ESS)));
पूर्ण

काष्ठा wlan_network *rtw_get_oldest_wlan_network(काष्ठा __queue *scanned_queue)
अणु
	काष्ठा list_head *plist, *phead;
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा wlan_network *oldest = शून्य;

	phead = get_list_head(scanned_queue);

	क्रम (plist = phead->next; plist != phead; plist = plist->next) अणु
		pwlan = container_of(plist, काष्ठा wlan_network, list);

		अगर (!pwlan->fixed) अणु
			अगर (!oldest || समय_after(oldest->last_scanned, pwlan->last_scanned))
				oldest = pwlan;
		पूर्ण
	पूर्ण
	वापस oldest;
पूर्ण

व्योम update_network(काष्ठा wlan_bssid_ex *dst, काष्ठा wlan_bssid_ex *src,
		    काष्ठा adapter *padapter, bool update_ie)
अणु
	दीर्घ rssi_ori = dst->Rssi;
	u8 sq_smp = src->PhyInfo.SignalQuality;
	u8 ss_final;
	u8 sq_final;
	दीर्घ rssi_final;

	rtw_hal_antभाग_rssi_compared(padapter, dst, src); /* this will update src.Rssi, need consider again */

	/* The rule below is 1/5 क्रम sample value, 4/5 क्रम history value */
	अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED) &&
	    is_same_network(&padapter->mlmepriv.cur_network.network, src)) अणु
		/* Take the recvpriv's value क्रम the connected AP*/
		ss_final = padapter->recvpriv.संकेत_strength;
		sq_final = padapter->recvpriv.संकेत_qual;
		/* the rssi value here is undecorated, and will be used क्रम antenna भागersity */
		अगर (sq_smp != 101) /* from the right channel */
			rssi_final = (src->Rssi + dst->Rssi * 4) / 5;
		अन्यथा
			rssi_final = rssi_ori;
	पूर्ण अन्यथा अणु
		अगर (sq_smp != 101) अणु /* from the right channel */
			ss_final = ((u32)(src->PhyInfo.SignalStrength) + (u32)(dst->PhyInfo.SignalStrength) * 4) / 5;
			sq_final = ((u32)(src->PhyInfo.SignalQuality) + (u32)(dst->PhyInfo.SignalQuality) * 4) / 5;
			rssi_final = (src->Rssi + dst->Rssi * 4) / 5;
		पूर्ण अन्यथा अणु
			/* bss info not receiving from the right channel, use the original RX संकेत infos */
			ss_final = dst->PhyInfo.SignalStrength;
			sq_final = dst->PhyInfo.SignalQuality;
			rssi_final = dst->Rssi;
		पूर्ण
	पूर्ण
	अगर (update_ie)
		स_नकल((u8 *)dst, (u8 *)src, get_wlan_bssid_ex_sz(src));
	dst->PhyInfo.SignalStrength = ss_final;
	dst->PhyInfo.SignalQuality = sq_final;
	dst->Rssi = rssi_final;
पूर्ण

अटल व्योम update_current_network(काष्ठा adapter *adapter, काष्ठा wlan_bssid_ex *pnetwork)
अणु
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED) &&
	    is_same_network(&pmlmepriv->cur_network.network, pnetwork)) अणु
		update_network(&pmlmepriv->cur_network.network, pnetwork, adapter, true);
		rtw_update_protection(adapter, (pmlmepriv->cur_network.network.ies) + माप(काष्ठा ndis_802_11_fixed_ie),
				      pmlmepriv->cur_network.network.ie_length);
	पूर्ण
पूर्ण

/*
 * Caller must hold pmlmepriv->lock first.
 */
व्योम rtw_update_scanned_network(काष्ठा adapter *adapter, काष्ठा wlan_bssid_ex *target)
अणु
	काष्ठा list_head *plist, *phead;
	u32 bssid_ex_sz;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा __queue *queue = &pmlmepriv->scanned_queue;
	काष्ठा wlan_network *pnetwork = शून्य;
	काष्ठा wlan_network *oldest = शून्य;

	spin_lock_bh(&queue->lock);
	phead = get_list_head(queue);
	plist = phead->next;

	जबतक (phead != plist) अणु
		pnetwork = container_of(plist, काष्ठा wlan_network, list);

		अगर (is_same_network(&pnetwork->network, target))
			अवरोध;
		अगर ((oldest == ((काष्ठा wlan_network *)0)) ||
		    समय_after(oldest->last_scanned, pnetwork->last_scanned))
			oldest = pnetwork;
		plist = plist->next;
	पूर्ण
	/* If we didn't find a match, then get a new network slot to initialize
	 * with this beacon's inक्रमmation
	 */
	अगर (phead == plist) अणु
		अगर (list_empty(&pmlmepriv->मुक्त_bss_pool.queue)) अणु
			/* If there are no more slots, expire the oldest */
			pnetwork = oldest;

			rtw_hal_get_def_var(adapter, HAL_DEF_CURRENT_ANTENNA,
					    &target->PhyInfo.Optimum_antenna);
			स_नकल(&pnetwork->network, target,
			       get_wlan_bssid_ex_sz(target));
			/*  variable initialize */
			pnetwork->fixed = false;
			pnetwork->last_scanned = jअगरfies;

			pnetwork->network_type = 0;
			pnetwork->aid = 0;
			pnetwork->join_res = 0;

			/* bss info not receiving from the right channel */
			अगर (pnetwork->network.PhyInfo.SignalQuality == 101)
				pnetwork->network.PhyInfo.SignalQuality = 0;
		पूर्ण अन्यथा अणु
			/* Otherwise just pull from the मुक्त list */

			pnetwork = rtw_alloc_network(pmlmepriv); /*  will update scan_समय */

			अगर (!pnetwork) अणु
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
					 ("\n\n\nsomething wrong here\n\n\n"));
				जाओ निकास;
			पूर्ण

			bssid_ex_sz = get_wlan_bssid_ex_sz(target);
			target->Length = bssid_ex_sz;
			rtw_hal_get_def_var(adapter, HAL_DEF_CURRENT_ANTENNA,
					    &target->PhyInfo.Optimum_antenna);
			स_नकल(&pnetwork->network, target, bssid_ex_sz);

			pnetwork->last_scanned = jअगरfies;

			/* bss info not receiving from the right channel */
			अगर (pnetwork->network.PhyInfo.SignalQuality == 101)
				pnetwork->network.PhyInfo.SignalQuality = 0;
			list_add_tail(&pnetwork->list, &queue->queue);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* we have an entry and we are going to update it. But this
		 * entry may be alपढ़ोy expired. In this हाल we करो the same
		 * as we found a new net and call the new_net handler
		 */
		bool update_ie = true;

		pnetwork->last_scanned = jअगरfies;

		/* target.Reserved[0]== 1, means that scanned network is a bcn frame. */
		अगर ((pnetwork->network.ie_length > target->ie_length) && (target->Reserved[0] == 1))
			update_ie = false;

		update_network(&pnetwork->network, target, adapter, update_ie);
	पूर्ण

निकास:
	spin_unlock_bh(&queue->lock);
पूर्ण

अटल व्योम rtw_add_network(काष्ठा adapter *adapter,
			    काष्ठा wlan_bssid_ex *pnetwork)
अणु
	update_current_network(adapter, pnetwork);
	rtw_update_scanned_network(adapter, pnetwork);
पूर्ण

/*
 * select the desired network based on the capability of the (i)bss.
 * check items:	(1) security
 *			(2) network_type
 *			(3) WMM
 *			(4) HT
 *			(5) others
 */
अटल पूर्णांक rtw_is_desired_network(काष्ठा adapter *adapter, काष्ठा wlan_network *pnetwork)
अणु
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u32 desired_encmode;
	u32 privacy;

	/* u8 wps_ie[512]; */
	uपूर्णांक wps_ielen;

	पूर्णांक bselected = true;

	desired_encmode = psecuritypriv->ndisencryptstatus;
	privacy = pnetwork->network.Privacy;

	अगर (check_fwstate(pmlmepriv, WIFI_UNDER_WPS)) अणु
		अगर (rtw_get_wps_ie(pnetwork->network.ies + _FIXED_IE_LENGTH_, pnetwork->network.ie_length - _FIXED_IE_LENGTH_, शून्य, &wps_ielen))
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
	अगर (adapter->registrypriv.wअगरi_spec == 1) अणु /* क्रम  correct flow of 8021X  to करो.... */
		अगर ((desired_encmode == Ndis802_11EncryptionDisabled) && (privacy != 0))
			bselected = false;
	पूर्ण

	अगर ((desired_encmode != Ndis802_11EncryptionDisabled) && (privacy == 0)) अणु
		DBG_88E("desired_encmode: %d, privacy: %d\n", desired_encmode, privacy);
		bselected = false;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
		अगर (pnetwork->network.Infraकाष्ठाureMode != pmlmepriv->cur_network.network.Infraकाष्ठाureMode)
			bselected = false;
	पूर्ण

	वापस bselected;
पूर्ण

/* TODO: Perry: For Power Management */
व्योम rtw_atimकरोne_event_callback(काष्ठा adapter *adapter, u8 *pbuf)
अणु
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("receive atimdone_event\n"));
पूर्ण

व्योम rtw_survey_event_callback(काष्ठा adapter	*adapter, u8 *pbuf)
अणु
	u32 len;
	काष्ठा wlan_bssid_ex *pnetwork;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	pnetwork = (काष्ठा wlan_bssid_ex *)pbuf;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
		 ("%s, ssid=%s\n", __func__, pnetwork->ssid.ssid));

	len = get_wlan_bssid_ex_sz(pnetwork);
	अगर (len > (माप(काष्ठा wlan_bssid_ex))) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
			 ("\n****%s: return a wrong bss ***\n", __func__));
		वापस;
	पूर्ण
	spin_lock_bh(&pmlmepriv->lock);

	/*  update IBSS_network 's बारtamp */
	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
		अगर (!स_भेद(&pmlmepriv->cur_network.network.MacAddress, pnetwork->MacAddress, ETH_ALEN)) अणु
			काष्ठा wlan_network *ibss_wlan = शून्य;

			स_नकल(pmlmepriv->cur_network.network.ies, pnetwork->ies, 8);
			spin_lock_bh(&pmlmepriv->scanned_queue.lock);
			ibss_wlan = rtw_find_network(&pmlmepriv->scanned_queue,  pnetwork->MacAddress);
			अगर (ibss_wlan) अणु
				स_नकल(ibss_wlan->network.ies, pnetwork->ies, 8);
				spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
				जाओ निकास;
			पूर्ण
			spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
		पूर्ण
	पूर्ण

	/*  lock pmlmepriv->lock when you accessing network_q */
	अगर (!check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) अणु
		अगर (pnetwork->ssid.ssid[0] == 0)
			pnetwork->ssid.ssid_length = 0;
		rtw_add_network(adapter, pnetwork);
	पूर्ण

निकास:
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

व्योम rtw_surveyकरोne_event_callback(काष्ठा adapter	*adapter, u8 *pbuf)
अणु
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	spin_lock_bh(&pmlmepriv->lock);

	अगर (pmlmepriv->wps_probe_req_ie) अणु
		pmlmepriv->wps_probe_req_ie_len = 0;
		kमुक्त(pmlmepriv->wps_probe_req_ie);
		pmlmepriv->wps_probe_req_ie = शून्य;
	पूर्ण

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
		 ("%s: fw_state:%x\n\n", __func__, get_fwstate(pmlmepriv)));

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY)) अणु
		del_समयr_sync(&pmlmepriv->scan_to_समयr);
		_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	पूर्ण अन्यथा अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("nic status=%x, survey done event comes too late!\n", get_fwstate(pmlmepriv)));
	पूर्ण

	rtw_set_संकेत_stat_समयr(&adapter->recvpriv);

	अगर (pmlmepriv->to_join) अणु
		अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
			अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				set_fwstate(pmlmepriv, _FW_UNDER_LINKING);

				अगर (rtw_select_and_join_from_scanned_queue(pmlmepriv) == _SUCCESS) अणु
					mod_समयr(&pmlmepriv->assoc_समयr,
						  jअगरfies + msecs_to_jअगरfies(MAX_JOIN_TIMEOUT));
				पूर्ण अन्यथा अणु
					काष्ठा wlan_bssid_ex *pdev_network = &adapter->registrypriv.dev_network;
					u8 *pibss = adapter->registrypriv.dev_network.MacAddress;

					_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);

					RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("switching to adhoc master\n"));

					स_नकल(&pdev_network->ssid, &pmlmepriv->assoc_ssid, माप(काष्ठा ndis_802_11_ssid));

					rtw_update_registrypriv_dev_network(adapter);
					rtw_generate_अक्रमom_ibss(pibss);

					pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;

					अगर (rtw_createbss_cmd(adapter) != _SUCCESS)
						RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("Error=>rtw_createbss_cmd status FAIL\n"));
					pmlmepriv->to_join = false;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक s_ret;

			set_fwstate(pmlmepriv, _FW_UNDER_LINKING);
			pmlmepriv->to_join = false;
			s_ret = rtw_select_and_join_from_scanned_queue(pmlmepriv);
			अगर (s_ret == _SUCCESS) अणु
				mod_समयr(&pmlmepriv->assoc_समयr,
					  jअगरfies + msecs_to_jअगरfies(MAX_JOIN_TIMEOUT));
			पूर्ण अन्यथा अगर (s_ret == 2) अणु /* there is no need to रुको क्रम join */
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
				rtw_indicate_connect(adapter);
			पूर्ण अन्यथा अणु
				DBG_88E("try_to_join, but select scanning queue fail, to_roaming:%d\n", pmlmepriv->to_roaming);
				अगर (pmlmepriv->to_roaming != 0) अणु
					अगर (--pmlmepriv->to_roaming == 0 ||
					    rtw_sitesurvey_cmd(adapter, &pmlmepriv->assoc_ssid, 1, शून्य, 0) != _SUCCESS) अणु
						pmlmepriv->to_roaming = 0;
						rtw_मुक्त_assoc_resources(adapter);
						rtw_indicate_disconnect(adapter);
					पूर्ण अन्यथा अणु
						pmlmepriv->to_join = true;
					पूर्ण
				पूर्ण
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
			पूर्ण
		पूर्ण
	पूर्ण

	indicate_wx_scan_complete_event(adapter);

	spin_unlock_bh(&pmlmepriv->lock);

	rtw_os_xmit_schedule(adapter);
पूर्ण

व्योम rtw_dummy_event_callback(काष्ठा adapter *adapter, u8 *pbuf)
अणु
पूर्ण

व्योम rtw_fwdbg_event_callback(काष्ठा adapter *adapter, u8 *pbuf)
अणु
पूर्ण

अटल व्योम मुक्त_scanqueue(काष्ठा	mlme_priv *pmlmepriv)
अणु
	काष्ठा __queue *मुक्त_queue = &pmlmepriv->मुक्त_bss_pool;
	काष्ठा __queue *scan_queue = &pmlmepriv->scanned_queue;
	काष्ठा list_head *plist, *phead, *ptemp;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_, ("+%s\n", __func__));
	spin_lock_bh(&scan_queue->lock);
	spin_lock_bh(&मुक्त_queue->lock);

	phead = get_list_head(scan_queue);
	plist = phead->next;

	जबतक (plist != phead) अणु
		ptemp = plist->next;
		list_del_init(plist);
		list_add_tail(plist, &मुक्त_queue->queue);
		plist = ptemp;
	पूर्ण

	spin_unlock_bh(&मुक्त_queue->lock);
	spin_unlock_bh(&scan_queue->lock);
पूर्ण

/*
 * rtw_मुक्त_assoc_resources: the caller has to lock pmlmepriv->lock
 */
व्योम rtw_मुक्त_assoc_resources(काष्ठा adapter *adapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	spin_lock_bh(&pmlmepriv->scanned_queue.lock);
	rtw_मुक्त_assoc_resources_locked(adapter);
	spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
पूर्ण

/*
 * rtw_मुक्त_assoc_resources_locked: the caller has to lock pmlmepriv->lock
 */
व्योम rtw_मुक्त_assoc_resources_locked(काष्ठा adapter *adapter)
अणु
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा wlan_network *tgt_network = &pmlmepriv->cur_network;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_, ("+rtw_free_assoc_resources\n"));
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
		 ("tgt_network->network.MacAddress=%pM ssid=%s\n",
		 tgt_network->network.MacAddress, tgt_network->network.ssid.ssid));

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_AP_STATE)) अणु
		काष्ठा sta_info *psta;

		psta = rtw_get_stainfo(&adapter->stapriv, tgt_network->network.MacAddress);

		spin_lock_bh(&pstapriv->sta_hash_lock);
		rtw_मुक्त_stainfo(adapter,  psta);
		spin_unlock_bh(&pstapriv->sta_hash_lock);
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE | WIFI_AP_STATE)) अणु
		काष्ठा sta_info *psta;

		rtw_मुक्त_all_stainfo(adapter);

		psta = rtw_get_bcmc_stainfo(adapter);
		spin_lock_bh(&pstapriv->sta_hash_lock);
		rtw_मुक्त_stainfo(adapter, psta);
		spin_unlock_bh(&pstapriv->sta_hash_lock);

		rtw_init_bcmc_stainfo(adapter);
	पूर्ण

	pwlan = rtw_find_network(&pmlmepriv->scanned_queue, tgt_network->network.MacAddress);
	अगर (pwlan)
		pwlan->fixed = false;
	अन्यथा
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("rtw_free_assoc_resources:pwlan==NULL\n\n"));

	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) && (adapter->stapriv.asoc_sta_count == 1)))
		rtw_मुक्त_network_nolock(pmlmepriv, pwlan);

	pmlmepriv->key_mask = 0;
पूर्ण

/*
 * rtw_indicate_connect: the caller has to lock pmlmepriv->lock
 */
व्योम rtw_indicate_connect(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("+%s\n", __func__));

	pmlmepriv->to_join = false;

	अगर (!check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु
		set_fwstate(pmlmepriv, _FW_LINKED);

		led_control_8188eu(padapter, LED_CTL_LINK);

		rtw_os_indicate_connect(padapter);
	पूर्ण

	pmlmepriv->to_roaming = 0;

	rtw_set_scan_deny(padapter, 3000);

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("-%s: fw_state=0x%08x\n", __func__, get_fwstate(pmlmepriv)));
पूर्ण

/*
 * rtw_indicate_disconnect: the caller has to lock pmlmepriv->lock
 */
व्योम rtw_indicate_disconnect(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("+%s\n", __func__));

	_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING | WIFI_UNDER_WPS);

	अगर (pmlmepriv->to_roaming > 0)
		_clr_fwstate_(pmlmepriv, _FW_LINKED);

	अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED) ||
	    (pmlmepriv->to_roaming <= 0)) अणु
		rtw_os_indicate_disconnect(padapter);

		_clr_fwstate_(pmlmepriv, _FW_LINKED);
		led_control_8188eu(padapter, LED_CTL_NO_LINK);
		rtw_clear_scan_deny(padapter);
	पूर्ण

	rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_DISCONNECT, 1);
पूर्ण

अंतरभूत व्योम rtw_indicate_scan_करोne(काष्ठा adapter *padapter, bool पातed)
अणु
	indicate_wx_scan_complete_event(padapter);
पूर्ण

अटल काष्ठा sta_info *rtw_joinbss_update_stainfo(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork)
अणु
	पूर्णांक i;
	काष्ठा sta_info *bmc_sta, *psta = शून्य;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	psta = rtw_get_stainfo(pstapriv, pnetwork->network.MacAddress);
	अगर (!psta)
		psta = rtw_alloc_stainfo(pstapriv, pnetwork->network.MacAddress);

	अगर (psta) अणु /* update ptarget_sta */
		DBG_88E("%s\n", __func__);
		psta->aid  = pnetwork->join_res;
		psta->mac_id = 0;
		/* sta mode */
		rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, psta, true);
		/* security related */
		अगर (padapter->securitypriv.करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X) अणु
			padapter->securitypriv.binstallGrpkey = false;
			padapter->securitypriv.busetkipkey = false;
			padapter->securitypriv.bgrpkey_handshake = false;
			psta->ieee8021x_blocked = true;
			psta->करोt118021XPrivacy = padapter->securitypriv.करोt11PrivacyAlgrthm;
			स_रखो((u8 *)&psta->करोt118021x_UncstKey, 0, माप(जोड़ Keytype));
			स_रखो((u8 *)&psta->करोt11tkiprxmickey, 0, माप(जोड़ Keytype));
			स_रखो((u8 *)&psta->करोt11tkiptxmickey, 0, माप(जोड़ Keytype));
			स_रखो((u8 *)&psta->करोt11txpn, 0, माप(जोड़ pn48));
			स_रखो((u8 *)&psta->करोt11rxpn, 0, माप(जोड़ pn48));
		पूर्ण
		/*
		 * Commented by Albert 2012/07/21
		 * When करोing the WPS, the wps_ie_len won't equal to 0
		 * And the Wi-Fi driver shouldn't allow the data
		 * packet to be transmitted.
		 */
		अगर (padapter->securitypriv.wps_ie_len != 0) अणु
			psta->ieee8021x_blocked = true;
			padapter->securitypriv.wps_ie_len = 0;
		पूर्ण
		/* क्रम A-MPDU Rx reordering buffer control क्रम bmc_sta & sta_info */
		/* अगर A-MPDU Rx is enabled, resetting  rx_ordering_ctrl wstart_b(indicate_seq) to शेष value = 0xffff */
		/* toकरो: check अगर AP can send A-MPDU packets */
		क्रम (i = 0; i < 16; i++) अणु
			/* preorder_ctrl = &precvpriv->recvreorder_ctrl[i]; */
			preorder_ctrl = &psta->recvreorder_ctrl[i];
			preorder_ctrl->enable = false;
			preorder_ctrl->indicate_seq = 0xffff;
			preorder_ctrl->wend_b = 0xffff;
			preorder_ctrl->wsize_b = 64;/* max_ampdu_sz; ex. 32(kbytes) -> wsize_b = 32 */
		पूर्ण
		bmc_sta = rtw_get_bcmc_stainfo(padapter);
		अगर (bmc_sta) अणु
			क्रम (i = 0; i < 16; i++) अणु
				/* preorder_ctrl = &precvpriv->recvreorder_ctrl[i]; */
				preorder_ctrl = &bmc_sta->recvreorder_ctrl[i];
				preorder_ctrl->enable = false;
				preorder_ctrl->indicate_seq = 0xffff;
				preorder_ctrl->wend_b = 0xffff;
				preorder_ctrl->wsize_b = 64;/* max_ampdu_sz; ex. 32(kbytes) -> wsize_b = 32 */
			पूर्ण
		पूर्ण
		/* misc. */
		update_sta_info(padapter, psta);
	पूर्ण
	वापस psta;
पूर्ण

/* pnetwork: वापसs from rtw_joinbss_event_callback */
/* ptarget_wlan: found from scanned_queue */
अटल व्योम rtw_joinbss_update_network(काष्ठा adapter *padapter, काष्ठा wlan_network *ptarget_wlan, काष्ठा wlan_network  *pnetwork)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा wlan_network *cur_network = &pmlmepriv->cur_network;

	DBG_88E("%s\n", __func__);

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
		 ("\nfw_state:%x, BSSID:%pM\n",
		 get_fwstate(pmlmepriv), pnetwork->network.MacAddress));

	/*  why not use ptarget_wlan?? */
	स_नकल(&cur_network->network, &pnetwork->network, pnetwork->network.Length);
	/*  some ies in pnetwork is wrong, so we should use ptarget_wlan ies */
	cur_network->network.ie_length = ptarget_wlan->network.ie_length;
	स_नकल(&cur_network->network.ies[0], &ptarget_wlan->network.ies[0], MAX_IE_SZ);

	cur_network->aid = pnetwork->join_res;

	rtw_set_संकेत_stat_समयr(&padapter->recvpriv);
	padapter->recvpriv.संकेत_strength = ptarget_wlan->network.PhyInfo.SignalStrength;
	padapter->recvpriv.संकेत_qual = ptarget_wlan->network.PhyInfo.SignalQuality;
	/* the ptarget_wlan->network.Rssi is raw data, we use ptarget_wlan->network.PhyInfo.SignalStrength instead (has scaled) */
	padapter->recvpriv.rssi = translate_percentage_to_dbm(ptarget_wlan->network.PhyInfo.SignalStrength);
	rtw_set_संकेत_stat_समयr(&padapter->recvpriv);

	/* update fw_state will clr _FW_UNDER_LINKING here indirectly */
	चयन (pnetwork->network.Infraकाष्ठाureMode) अणु
	हाल Ndis802_11Infraकाष्ठाure:
		अगर (pmlmepriv->fw_state & WIFI_UNDER_WPS)
			pmlmepriv->fw_state = WIFI_STATION_STATE | WIFI_UNDER_WPS;
		अन्यथा
			pmlmepriv->fw_state = WIFI_STATION_STATE;
		अवरोध;
	हाल Ndis802_11IBSS:
		pmlmepriv->fw_state = WIFI_ADHOC_STATE;
		अवरोध;
	शेष:
		pmlmepriv->fw_state = WIFI_शून्य_STATE;
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("Invalid network_mode\n"));
		अवरोध;
	पूर्ण

	rtw_update_protection(padapter, (cur_network->network.ies) +
			      माप(काष्ठा ndis_802_11_fixed_ie),
			      (cur_network->network.ie_length));
	rtw_update_ht_cap(padapter, cur_network->network.ies, cur_network->network.ie_length);
पूर्ण

/* Notes: the function could be > passive_level (the same context as Rx tasklet) */
/* pnetwork: वापसs from rtw_joinbss_event_callback */
/* ptarget_wlan: found from scanned_queue */
/* अगर join_res > 0, क्रम (fw_state == WIFI_STATION_STATE), we check अगर  "ptarget_sta" & "ptarget_wlan" exist. */
/* अगर join_res > 0, क्रम (fw_state == WIFI_ADHOC_STATE), we only check अगर "ptarget_wlan" exist. */
/* अगर join_res > 0, update "cur_network->network" from "pnetwork->network" अगर (ptarget_wlan != शून्य). */

व्योम rtw_joinbss_event_prehandle(काष्ठा adapter *adapter, u8 *pbuf)
अणु
	काष्ठा sta_info *ptarget_sta = शून्य, *pcur_sta = शून्य;
	काष्ठा sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा wlan_network *pnetwork = (काष्ठा wlan_network *)pbuf;
	काष्ठा wlan_network *cur_network = &pmlmepriv->cur_network;
	काष्ठा wlan_network *pcur_wlan = शून्य, *ptarget_wlan = शून्य;
	अचिन्हित पूर्णांक the_same_macaddr = false;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("joinbss event call back received with res=%d\n", pnetwork->join_res));

	rtw_get_encrypt_decrypt_from_registrypriv(adapter);

	अगर (pmlmepriv->assoc_ssid.ssid_length == 0)
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("@@@@@   joinbss event call back  for Any SSid\n"));
	अन्यथा
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("@@@@@   rtw_joinbss_event_callback for SSid:%s\n", pmlmepriv->assoc_ssid.ssid));

	the_same_macaddr = !स_भेद(pnetwork->network.MacAddress, cur_network->network.MacAddress, ETH_ALEN);

	pnetwork->network.Length = get_wlan_bssid_ex_sz(&pnetwork->network);
	अगर (pnetwork->network.Length > माप(काष्ठा wlan_bssid_ex)) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("\n\n ***joinbss_evt_callback return a wrong bss ***\n\n"));
		वापस;
	पूर्ण

	spin_lock_bh(&pmlmepriv->lock);

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("\nrtw_joinbss_event_callback!! _enter_critical\n"));

	अगर (pnetwork->join_res > 0) अणु
		spin_lock_bh(&pmlmepriv->scanned_queue.lock);
		अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) अणु
			/* s1. find ptarget_wlan */
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				अगर (the_same_macaddr) अणु
					ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, cur_network->network.MacAddress);
				पूर्ण अन्यथा अणु
					pcur_wlan = rtw_find_network(&pmlmepriv->scanned_queue, cur_network->network.MacAddress);
					अगर (pcur_wlan)
						pcur_wlan->fixed = false;

					pcur_sta = rtw_get_stainfo(pstapriv, cur_network->network.MacAddress);
					अगर (pcur_sta) अणु
						spin_lock_bh(&pstapriv->sta_hash_lock);
						rtw_मुक्त_stainfo(adapter,  pcur_sta);
						spin_unlock_bh(&pstapriv->sta_hash_lock);
					पूर्ण

					ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, pnetwork->network.MacAddress);
					अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
						अगर (ptarget_wlan)
							ptarget_wlan->fixed = true;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, pnetwork->network.MacAddress);
				अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
					अगर (ptarget_wlan)
						ptarget_wlan->fixed = true;
				पूर्ण
			पूर्ण

			/* s2. update cur_network */
			अगर (ptarget_wlan) अणु
				rtw_joinbss_update_network(adapter, ptarget_wlan, pnetwork);
			पूर्ण अन्यथा अणु
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("Can't find ptarget_wlan when joinbss_event callback\n"));
				spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
				जाओ ignore_joinbss_callback;
			पूर्ण

			/* s3. find ptarget_sta & update ptarget_sta after update cur_network only क्रम station mode */
			अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
				ptarget_sta = rtw_joinbss_update_stainfo(adapter, pnetwork);
				अगर (!ptarget_sta) अणु
					RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("Can't update stainfo when joinbss_event callback\n"));
					spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
					जाओ ignore_joinbss_callback;
				पूर्ण
			पूर्ण

			/* s4. indicate connect */
			अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
				rtw_indicate_connect(adapter);
			पूर्ण अन्यथा अणु
				/* adhoc mode will rtw_indicate_connect when rtw_stassoc_event_callback */
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("adhoc mode, fw_state:%x", get_fwstate(pmlmepriv)));
			पूर्ण

			/* s5. Cancel assoc_समयr */
			del_समयr_sync(&pmlmepriv->assoc_समयr);

			RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("Cancel assoc_timer\n"));

		पूर्ण अन्यथा अणु
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("rtw_joinbss_event_callback err: fw_state:%x", get_fwstate(pmlmepriv)));
			spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
			जाओ ignore_joinbss_callback;
		पूर्ण

		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);

	पूर्ण अन्यथा अगर (pnetwork->join_res == -4) अणु
		rtw_reset_securitypriv(adapter);
		mod_समयr(&pmlmepriv->assoc_समयr,
			  jअगरfies + msecs_to_jअगरfies(1));

		अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) अणु
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("fail! clear _FW_UNDER_LINKING ^^^fw_state=%x\न", get_fwstate(pmlmepriv)));
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
		पूर्ण
	पूर्ण अन्यथा अणु /* अगर join_res < 0 (join fails), then try again */
		mod_समयr(&pmlmepriv->assoc_समयr,
			  jअगरfies + msecs_to_jअगरfies(1));
		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
	पूर्ण

ignore_joinbss_callback:
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

व्योम rtw_joinbss_event_callback(काष्ठा adapter *adapter, u8 *pbuf)
अणु
	काष्ठा wlan_network *pnetwork = (काष्ठा wlan_network *)pbuf;

	mlmeext_joinbss_event_callback(adapter, pnetwork->join_res);

	rtw_os_xmit_schedule(adapter);
पूर्ण

अटल u8 search_max_mac_id(काष्ठा adapter *padapter)
अणु
	u8 mac_id;
#अगर defined(CONFIG_88EU_AP_MODE)
	u8 aid;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
#पूर्ण_अगर
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

#अगर defined(CONFIG_88EU_AP_MODE)
	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		क्रम (aid = pstapriv->max_num_sta; aid > 0; aid--) अणु
			अगर (pstapriv->sta_aid[aid - 1])
				अवरोध;
		पूर्ण
		mac_id = aid + 1;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु/* adhoc  id =  31~2 */
		क्रम (mac_id = NUM_STA - 1; mac_id >= IBSS_START_MAC_ID; mac_id--) अणु
			अगर (pmlmeinfo->FW_sta_info[mac_id].status == 1)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस mac_id;
पूर्ण

/* FOR AP , AD-HOC mode */
व्योम rtw_stassoc_hw_rpt(काष्ठा adapter *adapter, काष्ठा sta_info *psta)
अणु
	u16 media_status;
	u8 macid;

	अगर (!psta)
		वापस;

	macid = search_max_mac_id(adapter);
	rtw_hal_set_hwreg(adapter, HW_VAR_TX_RPT_MAX_MACID, (u8 *)&macid);
	media_status = (psta->mac_id << 8) | 1; /*   MACID|OPMODE:1 connect */
	rtw_hal_set_hwreg(adapter, HW_VAR_H2C_MEDIA_STATUS_RPT, (u8 *)&media_status);
पूर्ण

व्योम rtw_stassoc_event_callback(काष्ठा adapter *adapter, u8 *pbuf)
अणु
	काष्ठा sta_info *psta;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा stassoc_event *pstassoc = (काष्ठा stassoc_event *)pbuf;
	काष्ठा wlan_network *cur_network = &pmlmepriv->cur_network;
	काष्ठा wlan_network *ptarget_wlan = शून्य;

	अगर (!rtw_access_ctrl(adapter, pstassoc->macaddr))
		वापस;

#अगर defined(CONFIG_88EU_AP_MODE)
	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		psta = rtw_get_stainfo(&adapter->stapriv, pstassoc->macaddr);
		अगर (psta) अणु
			ap_sta_info_defer_update(adapter, psta);
			rtw_stassoc_hw_rpt(adapter, psta);
		पूर्ण
		वापस;
	पूर्ण
#पूर्ण_अगर
	/* क्रम AD-HOC mode */
	psta = rtw_get_stainfo(&adapter->stapriv, pstassoc->macaddr);
	अगर (psta) अणु
		/* the sta have been in sta_info_queue => करो nothing */
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
			 ("Error: %s: sta has been in sta_hash_queue\n",
			  __func__));
		वापस; /* between drv has received this event beक्रमe and  fw have not yet to set key to CAM_ENTRY) */
	पूर्ण
	psta = rtw_alloc_stainfo(&adapter->stapriv, pstassoc->macaddr);
	अगर (!psta) अणु
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
			 ("Can't alloc sta_info when %s\n", __func__));
		वापस;
	पूर्ण
	/* to करो: init sta_info variable */
	psta->qos_option = 0;
	psta->mac_id = (uपूर्णांक)pstassoc->cam_id;
	DBG_88E("%s\n", __func__);
	/* क्रम ad-hoc mode */
	rtw_hal_set_odm_var(adapter, HAL_ODM_STA_INFO, psta, true);
	rtw_stassoc_hw_rpt(adapter, psta);
	अगर (adapter->securitypriv.करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X)
		psta->करोt118021XPrivacy = adapter->securitypriv.करोt11PrivacyAlgrthm;
	psta->ieee8021x_blocked = false;
	spin_lock_bh(&pmlmepriv->lock);
	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE))) अणु
		अगर (adapter->stapriv.asoc_sta_count == 2) अणु
			spin_lock_bh(&pmlmepriv->scanned_queue.lock);
			ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, cur_network->network.MacAddress);
			अगर (ptarget_wlan)
				ptarget_wlan->fixed = true;
			spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
			/*  a sta + bc/mc_stainfo (not Ibss_stainfo) */
			rtw_indicate_connect(adapter);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pmlmepriv->lock);
	mlmeext_sta_add_event_callback(adapter, psta);
पूर्ण

व्योम rtw_stadel_event_callback(काष्ठा adapter *adapter, u8 *pbuf)
अणु
	पूर्णांक mac_id = -1;
	काष्ठा sta_info *psta;
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा wlan_bssid_ex *pdev_network = शून्य;
	u8 *pibss = शून्य;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा stadel_event *pstadel = (काष्ठा stadel_event *)pbuf;
	काष्ठा sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा wlan_network *tgt_network = &pmlmepriv->cur_network;

	psta = rtw_get_stainfo(&adapter->stapriv, pstadel->macaddr);
	अगर (psta)
		mac_id = psta->mac_id;
	अन्यथा
		mac_id = pstadel->mac_id;

	DBG_88E("%s(mac_id=%d)=%pM\n", __func__, mac_id, pstadel->macaddr);

	अगर (mac_id >= 0) अणु
		u16 media_status;

		media_status = (mac_id << 8) | 0; /*   MACID|OPMODE:0 means disconnect */
		/* क्रम STA, AP, ADHOC mode, report disconnect stauts to FW */
		rtw_hal_set_hwreg(adapter, HW_VAR_H2C_MEDIA_STATUS_RPT, (u8 *)&media_status);
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस;

	mlmeext_sta_del_event_callback(adapter);

	spin_lock_bh(&pmlmepriv->lock);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
		अगर (pmlmepriv->to_roaming > 0)
			pmlmepriv->to_roaming--; /*  this stadel_event is caused by roaming, decrease to_roaming */
		अन्यथा अगर (pmlmepriv->to_roaming == 0)
			pmlmepriv->to_roaming = adapter->registrypriv.max_roaming_बार;

		अगर (*((अचिन्हित लघु *)(pstadel->rsvd)) != WLAN_REASON_EXPIRATION_CHK)
			pmlmepriv->to_roaming = 0; /*  करोn't roam */

		rtw_मुक्त_uc_swdec_pending_queue(adapter);

		rtw_मुक्त_assoc_resources(adapter);
		rtw_indicate_disconnect(adapter);
		spin_lock_bh(&pmlmepriv->scanned_queue.lock);
		/*  हटाओ the network entry in scanned_queue */
		pwlan = rtw_find_network(&pmlmepriv->scanned_queue, tgt_network->network.MacAddress);
		अगर (pwlan) अणु
			pwlan->fixed = false;
			rtw_मुक्त_network_nolock(pmlmepriv, pwlan);
		पूर्ण
		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
		_rtw_roaming(adapter, tgt_network);
	पूर्ण
	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
		spin_lock_bh(&pstapriv->sta_hash_lock);
		rtw_मुक्त_stainfo(adapter,  psta);
		spin_unlock_bh(&pstapriv->sta_hash_lock);

		अगर (adapter->stapriv.asoc_sta_count == 1) अणु /* a sta + bc/mc_stainfo (not Ibss_stainfo) */
			spin_lock_bh(&pmlmepriv->scanned_queue.lock);
			/* मुक्त old ibss network */
			pwlan = rtw_find_network(&pmlmepriv->scanned_queue, tgt_network->network.MacAddress);
			अगर (pwlan) अणु
				pwlan->fixed = false;
				rtw_मुक्त_network_nolock(pmlmepriv, pwlan);
			पूर्ण
			spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
			/* re-create ibss */
			pdev_network = &adapter->registrypriv.dev_network;
			pibss = adapter->registrypriv.dev_network.MacAddress;

			स_नकल(pdev_network, &tgt_network->network, get_wlan_bssid_ex_sz(&tgt_network->network));

			स_नकल(&pdev_network->ssid, &pmlmepriv->assoc_ssid, माप(काष्ठा ndis_802_11_ssid));

			rtw_update_registrypriv_dev_network(adapter);

			rtw_generate_अक्रमom_ibss(pibss);

			अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
				set_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE);
				_clr_fwstate_(pmlmepriv, WIFI_ADHOC_STATE);
			पूर्ण

			अगर (rtw_createbss_cmd(adapter) != _SUCCESS)
				RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("***Error=>stadel_event_callback: rtw_createbss_cmd status FAIL***\n "));
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

व्योम rtw_cpwm_event_callback(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("+%s !!!\n", __func__));
पूर्ण

/*
 * _rtw_join_समयout_handler - Timeout/failure handler क्रम CMD JoinBss
 * @adapter: poपूर्णांकer to काष्ठा adapter काष्ठाure
 */
व्योम _rtw_join_समयout_handler (काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter = from_समयr(adapter, t, mlmepriv.assoc_समयr);
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	पूर्णांक करो_join_r;

	DBG_88E("%s, fw_state=%x\n", __func__, get_fwstate(pmlmepriv));

	अगर (adapter->bDriverStopped || adapter->bSurpriseRemoved)
		वापस;

	spin_lock_bh(&pmlmepriv->lock);

	अगर (pmlmepriv->to_roaming > 0) अणु /*  join समयout caused by roaming */
		जबतक (1) अणु
			pmlmepriv->to_roaming--;
			अगर (pmlmepriv->to_roaming != 0) अणु /* try another , */
				DBG_88E("%s try another roaming\n", __func__);
				करो_join_r = rtw_करो_join(adapter);
				अगर (करो_join_r != _SUCCESS) अणु
					DBG_88E("%s roaming do_join return %d\n", __func__, करो_join_r);
					जारी;
				पूर्ण
				अवरोध;
			पूर्ण
			DBG_88E("%s We've try roaming but fail\n", __func__);
			rtw_indicate_disconnect(adapter);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtw_indicate_disconnect(adapter);
		मुक्त_scanqueue(pmlmepriv);/*  */
	पूर्ण
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

/*
 * rtw_scan_समयout_handler - Timeout/Failure handler क्रम CMD SiteSurvey
 * @adapter: poपूर्णांकer to काष्ठा adapter काष्ठाure
 */
व्योम rtw_scan_समयout_handler (काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter = from_समयr(adapter, t,
					     mlmepriv.scan_to_समयr);
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	DBG_88E(FUNC_ADPT_FMT" fw_state=%x\n", FUNC_ADPT_ARG(adapter), get_fwstate(pmlmepriv));
	spin_lock_bh(&pmlmepriv->lock);
	_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	spin_unlock_bh(&pmlmepriv->lock);
	rtw_indicate_scan_करोne(adapter, true);
पूर्ण

अटल व्योम rtw_स्वतः_scan_handler(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	/* स्वतः site survey per 60sec */
	अगर (pmlmepriv->scan_पूर्णांकerval > 0) अणु
		pmlmepriv->scan_पूर्णांकerval--;
		अगर (pmlmepriv->scan_पूर्णांकerval == 0) अणु
			DBG_88E("%s\n", __func__);
			rtw_set_802_11_bssid_list_scan(padapter, शून्य, 0);
			pmlmepriv->scan_पूर्णांकerval = SCAN_INTERVAL;/*  30*2 sec = 60sec */
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtw_dynamic_check_समयr_handlder(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter = from_समयr(adapter, t,
					     mlmepriv.dynamic_chk_समयr);
	काष्ठा registry_priv *pregistrypriv = &adapter->registrypriv;

	अगर (!adapter)
		वापस;
	अगर (!adapter->hw_init_completed)
		जाओ निकास;
	अगर ((adapter->bDriverStopped) || (adapter->bSurpriseRemoved))
		जाओ निकास;
	अगर (adapter->net_बंदd)
		जाओ निकास;
	rtw_dynamic_chk_wk_cmd(adapter);

	अगर (pregistrypriv->wअगरi_spec == 1) अणु
		/* स्वतः site survey */
		rtw_स्वतः_scan_handler(adapter);
	पूर्ण
निकास:
	mod_समयr(&adapter->mlmepriv.dynamic_chk_समयr,
		  jअगरfies + msecs_to_jअगरfies(2000));
पूर्ण

#घोषणा RTW_SCAN_RESULT_EXPIRE 2000

/*
 * Select a new join candidate from the original @param candidate and @param competitor
 * @वापस true: candidate is updated
 * @वापस false: candidate is not updated
 */
अटल पूर्णांक rtw_check_join_candidate(काष्ठा mlme_priv *pmlmepriv
	, काष्ठा wlan_network **candidate, काष्ठा wlan_network *competitor)
अणु
	पूर्णांक updated = false;
	अचिन्हित दीर्घ since_scan;
	काष्ठा adapter *adapter = container_of(pmlmepriv, काष्ठा adapter,
					       mlmepriv);

	/* check bssid, अगर needed */
	अगर (pmlmepriv->assoc_by_bssid) अणु
		अगर (स_भेद(competitor->network.MacAddress, pmlmepriv->assoc_bssid, ETH_ALEN))
			जाओ निकास;
	पूर्ण

	/* check ssid, अगर needed */
	अगर (pmlmepriv->assoc_ssid.ssid_length) अणु
		अगर (competitor->network.ssid.ssid_length != pmlmepriv->assoc_ssid.ssid_length ||
		    स_भेद(competitor->network.ssid.ssid, pmlmepriv->assoc_ssid.ssid, pmlmepriv->assoc_ssid.ssid_length))
			जाओ निकास;
	पूर्ण

	अगर (!rtw_is_desired_network(adapter, competitor))
		जाओ निकास;

	अगर (pmlmepriv->to_roaming) अणु
		since_scan = jअगरfies - competitor->last_scanned;
		अगर (jअगरfies_to_msecs(since_scan) >= RTW_SCAN_RESULT_EXPIRE ||
		    !is_same_ess(&competitor->network, &pmlmepriv->cur_network.network))
			जाओ निकास;
	पूर्ण

	अगर (!*candidate || (*candidate)->network.Rssi < competitor->network.Rssi) अणु
		*candidate = competitor;
		updated = true;
	पूर्ण
	अगर (updated) अणु
		DBG_88E("[by_bssid:%u][assoc_ssid:%s]new candidate: %s(%pM rssi:%d\n",
			pmlmepriv->assoc_by_bssid,
			pmlmepriv->assoc_ssid.ssid,
			(*candidate)->network.ssid.ssid,
			(*candidate)->network.MacAddress,
			(पूर्णांक)(*candidate)->network.Rssi);
		DBG_88E("[to_roaming:%u]\n", pmlmepriv->to_roaming);
	पूर्ण

निकास:
	वापस updated;
पूर्ण

/*
 * Calling context:
 * The caller of the sub-routine will be in critical section...
 * The caller must hold the following spinlock
 * pmlmepriv->lock
 */

पूर्णांक rtw_select_and_join_from_scanned_queue(काष्ठा mlme_priv *pmlmepriv)
अणु
	पूर्णांक ret;
	काष्ठा list_head *phead;
	काष्ठा adapter *adapter;
	काष्ठा __queue *queue = &pmlmepriv->scanned_queue;
	काष्ठा wlan_network *pnetwork = शून्य;
	काष्ठा wlan_network *candidate = शून्य;
	u8 supp_ant_भाग = false;

	spin_lock_bh(&pmlmepriv->scanned_queue.lock);
	phead = get_list_head(queue);
	adapter = (काष्ठा adapter *)pmlmepriv->nic_hdl;
	pmlmepriv->pscanned = phead->next;
	जबतक (phead != pmlmepriv->pscanned) अणु
		pnetwork = container_of(pmlmepriv->pscanned, काष्ठा wlan_network, list);
		अगर (!pnetwork) अणु
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("%s return _FAIL:(pnetwork==NULL)\n", __func__));
			ret = _FAIL;
			जाओ निकास;
		पूर्ण
		pmlmepriv->pscanned = pmlmepriv->pscanned->next;
		rtw_check_join_candidate(pmlmepriv, &candidate, pnetwork);
	पूर्ण
	अगर (!candidate) अणु
		DBG_88E("%s: return _FAIL(candidate==NULL)\n", __func__);
		ret = _FAIL;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		DBG_88E("%s: candidate: %s(%pM ch:%u)\n", __func__,
			candidate->network.ssid.ssid, candidate->network.MacAddress,
			candidate->network.Configuration.DSConfig);
	पूर्ण

	/*  check क्रम situation of  _FW_LINKED */
	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		DBG_88E("%s: _FW_LINKED while ask_for_joinbss!!!\n", __func__);

		rtw_disassoc_cmd(adapter, 0, true);
		rtw_indicate_disconnect(adapter);
		rtw_मुक्त_assoc_resources_locked(adapter);
	पूर्ण

	rtw_hal_get_def_var(adapter, HAL_DEF_IS_SUPPORT_ANT_DIV, &(supp_ant_भाग));
	अगर (supp_ant_भाग) अणु
		u8 cur_ant;

		rtw_hal_get_def_var(adapter, HAL_DEF_CURRENT_ANTENNA, &(cur_ant));
		DBG_88E("#### Opt_Ant_(%s), cur_Ant(%s)\n",
			(candidate->network.PhyInfo.Optimum_antenna == 2) ? "A" : "B",
			(cur_ant == 2) ? "A" : "B"
		);
	पूर्ण

	ret = rtw_joinbss_cmd(adapter, candidate);

निकास:
	spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
	वापस ret;
पूर्ण

पूर्णांक rtw_set_auth(काष्ठा adapter *adapter, काष्ठा security_priv *psecuritypriv)
अणु
	काष्ठा cmd_obj *pcmd;
	काष्ठा setauth_parm *psetauthparm;
	काष्ठा cmd_priv *pcmdpriv = &adapter->cmdpriv;
	पूर्णांक res = _SUCCESS;

	pcmd = kzalloc(माप(काष्ठा cmd_obj), GFP_KERNEL);
	अगर (!pcmd) अणु
		res = _FAIL;  /* try again */
		जाओ निकास;
	पूर्ण

	psetauthparm = kzalloc(माप(काष्ठा setauth_parm), GFP_KERNEL);
	अगर (!psetauthparm) अणु
		kमुक्त(pcmd);
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	psetauthparm->mode = (अचिन्हित अक्षर)psecuritypriv->करोt11AuthAlgrthm;
	pcmd->cmdcode = _SetAuth_CMD_;
	pcmd->parmbuf = (अचिन्हित अक्षर *)psetauthparm;
	pcmd->cmdsz =  माप(काष्ठा setauth_parm);
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;
	INIT_LIST_HEAD(&pcmd->list);
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
		 ("after enqueue set_auth_cmd, auth_mode=%x\n",
		 psecuritypriv->करोt11AuthAlgrthm));
	res = rtw_enqueue_cmd(pcmdpriv, pcmd);
निकास:
	वापस res;
पूर्ण

पूर्णांक rtw_set_key(काष्ठा adapter *adapter, काष्ठा security_priv *psecuritypriv, पूर्णांक keyid, u8 set_tx)
अणु
	u8 keylen;
	काष्ठा cmd_obj *pcmd;
	काष्ठा setkey_parm *psetkeyparm;
	काष्ठा cmd_priv *pcmdpriv = &adapter->cmdpriv;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	पूर्णांक res = _SUCCESS;

	pcmd = kzalloc(माप(काष्ठा cmd_obj), GFP_KERNEL);
	अगर (!pcmd)
		वापस _FAIL;  /* try again */

	psetkeyparm = kzalloc(माप(काष्ठा setkey_parm), GFP_KERNEL);
	अगर (!psetkeyparm) अणु
		res = _FAIL;
		जाओ err_मुक्त_cmd;
	पूर्ण

	अगर (psecuritypriv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X) अणु
		psetkeyparm->algorithm = (अचिन्हित अक्षर)psecuritypriv->करोt118021XGrpPrivacy;
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
			 ("\n %s: psetkeyparm->algorithm=(unsigned char)psecuritypriv->dot118021XGrpPrivacy=%d\n",
			  __func__, psetkeyparm->algorithm));
	पूर्ण अन्यथा अणु
		psetkeyparm->algorithm = (u8)psecuritypriv->करोt11PrivacyAlgrthm;
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
			 ("\n %s: psetkeyparm->algorithm=(u8)psecuritypriv->dot11PrivacyAlgrthm=%d\n",
			  __func__, psetkeyparm->algorithm));
	पूर्ण
	psetkeyparm->keyid = (u8)keyid;/* 0~3 */
	psetkeyparm->set_tx = set_tx;
	pmlmepriv->key_mask |= BIT(psetkeyparm->keyid);
	DBG_88E("==> %s algorithm(%x), keyid(%x), key_mask(%x)\n",
		__func__, psetkeyparm->algorithm, psetkeyparm->keyid,
		pmlmepriv->key_mask);
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
		 ("\n %s: psetkeyparm->algorithm=%d psetkeyparm->keyid=(u8)keyid=%d\n",
		  __func__, psetkeyparm->algorithm, keyid));

	चयन (psetkeyparm->algorithm) अणु
	हाल _WEP40_:
		keylen = 5;
		स_नकल(&psetkeyparm->key[0],
		       &psecuritypriv->करोt11DefKey[keyid].skey[0], keylen);
		अवरोध;
	हाल _WEP104_:
		keylen = 13;
		स_नकल(&psetkeyparm->key[0],
		       &psecuritypriv->करोt11DefKey[keyid].skey[0], keylen);
		अवरोध;
	हाल _TKIP_:
		keylen = 16;
		स_नकल(&psetkeyparm->key, &psecuritypriv->करोt118021XGrpKey[keyid], keylen);
		psetkeyparm->grpkey = 1;
		अवरोध;
	हाल _AES_:
		keylen = 16;
		स_नकल(&psetkeyparm->key, &psecuritypriv->करोt118021XGrpKey[keyid], keylen);
		psetkeyparm->grpkey = 1;
		अवरोध;
	शेष:
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_,
			 ("\n %s:psecuritypriv->dot11PrivacyAlgrthm=%x (must be 1 or 2 or 4 or 5)\n",
			  __func__, psecuritypriv->करोt11PrivacyAlgrthm));
		res = _FAIL;
		जाओ err_मुक्त_parm;
	पूर्ण
	pcmd->cmdcode = _SetKey_CMD_;
	pcmd->parmbuf = (u8 *)psetkeyparm;
	pcmd->cmdsz =  माप(काष्ठा setkey_parm);
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;
	INIT_LIST_HEAD(&pcmd->list);
	वापस rtw_enqueue_cmd(pcmdpriv, pcmd);

err_मुक्त_parm:
	kमुक्त(psetkeyparm);
err_मुक्त_cmd:
	kमुक्त(pcmd);
	वापस res;
पूर्ण

/* adjust ies क्रम rtw_joinbss_cmd in WMM */
पूर्णांक rtw_reकाष्ठा_wmm_ie(काष्ठा adapter *adapter, u8 *in_ie, u8 *out_ie, uपूर्णांक in_len, uपूर्णांक initial_out_len)
अणु
	अचिन्हित पूर्णांक ielength = 0;
	अचिन्हित पूर्णांक i, j;

	/* i = 12; after the fixed IE */
	क्रम (i = 12; i < in_len; i += (in_ie[i + 1] + 2) /* to the next IE element */) अणु
		ielength = initial_out_len;

		अगर (in_ie[i] == 0xDD && in_ie[i + 2] == 0x00 && in_ie[i + 3] == 0x50  && in_ie[i + 4] == 0xF2 && in_ie[i + 5] == 0x02 && i + 5 < in_len) अणु
			/* WMM element ID and OUI */
			/* Append WMM IE to the last index of out_ie */

			क्रम (j = i; j < i + 9; j++) अणु
				out_ie[ielength] = in_ie[j];
				ielength++;
			पूर्ण
			out_ie[initial_out_len + 1] = 0x07;
			out_ie[initial_out_len + 6] = 0x00;
			out_ie[initial_out_len + 8] = 0x00;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ielength;
पूर्ण

/*
 * Ported from 8185: IsInPreAuthKeyList().
 * (Renamed from SecIsInPreAuthKeyList(), 2006-10-13.)
 * Added by Annie, 2006-05-07.
 * Search by BSSID,
 * Return Value:
 *		-1	:अगर there is no pre-auth key in the table
 *		>= 0	:अगर there is pre-auth key, and वापस the entry id
 */
अटल पूर्णांक SecIsInPMKIDList(काष्ठा adapter *Adapter, u8 *bssid)
अणु
	काष्ठा security_priv *psecuritypriv = &Adapter->securitypriv;
	पूर्णांक i = 0;

	करो अणु
		अगर ((psecuritypriv->PMKIDList[i].used) &&
		    (!स_भेद(psecuritypriv->PMKIDList[i].bssid, bssid, ETH_ALEN)))
			अवरोध;
	पूर्ण जबतक (++i < NUM_PMKID_CACHE);

	अगर (i == NUM_PMKID_CACHE)
		i = -1;/*  Could not find. */

	वापस i;
पूर्ण

/*  */
/*  Check the RSN IE length */
/*  If the RSN IE length <= 20, the RSN IE didn't include the PMKID inक्रमmation */
/*  0-11th element in the array are the fixed IE */
/*  12th element in the array is the IE */
/*  13th element in the array is the IE length */
/*  */

अटल पूर्णांक rtw_append_pmkid(काष्ठा adapter *Adapter, पूर्णांक iEntry, u8 *ie, uपूर्णांक ie_len)
अणु
	काष्ठा security_priv *psecuritypriv = &Adapter->securitypriv;

	अगर (ie[13] <= 20) अणु
		/*  The RSN IE didn't include the PMK ID, append the PMK inक्रमmation */
		ie[ie_len] = 1;
		ie_len++;
		ie[ie_len] = 0;	/* PMKID count = 0x0100 */
		ie_len++;
		स_नकल(&ie[ie_len], &psecuritypriv->PMKIDList[iEntry].PMKID, 16);

		ie_len += 16;
		ie[13] += 18;/* PMKID length = 2+16 */
	पूर्ण
	वापस ie_len;
पूर्ण

पूर्णांक rtw_reकाष्ठा_sec_ie(काष्ठा adapter *adapter, u8 *in_ie, u8 *out_ie, uपूर्णांक in_len)
अणु
	u8 authmode;
	uपूर्णांक ielength;
	पूर्णांक iEntry;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;
	uपूर्णांक ndisauthmode = psecuritypriv->ndisauthtype;
	uपूर्णांक ndissecuritytype = psecuritypriv->ndisencryptstatus;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_,
		 ("+%s: ndisauthmode=%d ndissecuritytype=%d\n", __func__,
		  ndisauthmode, ndissecuritytype));

	/* copy fixed ie only */
	स_नकल(out_ie, in_ie, 12);
	ielength = 12;
	अगर ((ndisauthmode == Ndis802_11AuthModeWPA) ||
	    (ndisauthmode == Ndis802_11AuthModeWPAPSK))
		authmode = WLAN_EID_VENDOR_SPECIFIC;
	अन्यथा अगर ((ndisauthmode == Ndis802_11AuthModeWPA2) ||
		 (ndisauthmode == Ndis802_11AuthModeWPA2PSK))
		authmode = WLAN_EID_RSN;
	अन्यथा
		authmode = 0x0;

	अगर (check_fwstate(pmlmepriv, WIFI_UNDER_WPS)) अणु
		स_नकल(out_ie + ielength, psecuritypriv->wps_ie, psecuritypriv->wps_ie_len);

		ielength += psecuritypriv->wps_ie_len;
	पूर्ण अन्यथा अगर ((authmode == WLAN_EID_VENDOR_SPECIFIC) || (authmode == WLAN_EID_RSN)) अणु
		/* copy RSN or SSN */
		स_नकल(&out_ie[ielength], &psecuritypriv->supplicant_ie[0], psecuritypriv->supplicant_ie[1] + 2);
		ielength += psecuritypriv->supplicant_ie[1] + 2;
		rtw_report_sec_ie(adapter, authmode, psecuritypriv->supplicant_ie);
	पूर्ण

	iEntry = SecIsInPMKIDList(adapter, pmlmepriv->assoc_bssid);
	अगर (iEntry >= 0 && authmode == WLAN_EID_RSN)
		ielength = rtw_append_pmkid(adapter, iEntry, out_ie, ielength);

	वापस ielength;
पूर्ण

व्योम rtw_init_registrypriv_dev_network(काष्ठा adapter *adapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &adapter->registrypriv;
	काष्ठा eeprom_priv *peepriv = &adapter->eeprompriv;
	काष्ठा wlan_bssid_ex *pdev_network = &pregistrypriv->dev_network;
	u8 *myhwaddr = myid(peepriv);

	स_नकल(pdev_network->MacAddress, myhwaddr, ETH_ALEN);

	स_नकल(&pdev_network->ssid, &pregistrypriv->ssid, माप(काष्ठा ndis_802_11_ssid));

	pdev_network->Configuration.Length = माप(काष्ठा ndis_802_11_config);
	pdev_network->Configuration.BeaconPeriod = 100;
	pdev_network->Configuration.FHConfig.Length = 0;
	pdev_network->Configuration.FHConfig.HopPattern = 0;
	pdev_network->Configuration.FHConfig.HopSet = 0;
	pdev_network->Configuration.FHConfig.DwellTime = 0;
पूर्ण

व्योम rtw_update_registrypriv_dev_network(काष्ठा adapter *adapter)
अणु
	पूर्णांक sz = 0;
	काष्ठा registry_priv *pregistrypriv = &adapter->registrypriv;
	काष्ठा wlan_bssid_ex *pdev_network = &pregistrypriv->dev_network;
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;
	काष्ठा wlan_network *cur_network = &adapter->mlmepriv.cur_network;

	pdev_network->Privacy = psecuritypriv->करोt11PrivacyAlgrthm > 0 ? 1 : 0; /*  adhoc no 802.1x */

	pdev_network->Rssi = 0;

	चयन (pregistrypriv->wireless_mode) अणु
	हाल WIRELESS_11B:
		pdev_network->NetworkTypeInUse = Ndis802_11DS;
		अवरोध;
	हाल WIRELESS_11G:
	हाल WIRELESS_11BG:
	हाल WIRELESS_11_24N:
	हाल WIRELESS_11G_24N:
	हाल WIRELESS_11BG_24N:
		pdev_network->NetworkTypeInUse = Ndis802_11OFDM24;
		अवरोध;
	शेष:
		pdev_network->NetworkTypeInUse = Ndis802_11OFDM24;
		अवरोध;
	पूर्ण

	pdev_network->Configuration.DSConfig = pregistrypriv->channel;
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
		 ("pregistrypriv->channel=%d, pdev_network->Configuration.DSConfig=0x%x\n",
		 pregistrypriv->channel, pdev_network->Configuration.DSConfig));

	अगर (cur_network->network.Infraकाष्ठाureMode == Ndis802_11IBSS)
		pdev_network->Configuration.ATIMWinकरोw = 0;

	pdev_network->Infraकाष्ठाureMode = cur_network->network.Infraकाष्ठाureMode;

	/*  1. Supported rates */
	/*  2. IE */

	sz = rtw_generate_ie(pregistrypriv);
	pdev_network->ie_length = sz;
	pdev_network->Length = get_wlan_bssid_ex_sz(pdev_network);

	/* notes: translate ie_length & Length after assign the Length to cmdsz in createbss_cmd(); */
	/* pdev_network->ie_length = cpu_to_le32(sz); */
पूर्ण

व्योम rtw_get_encrypt_decrypt_from_registrypriv(काष्ठा adapter *adapter)
अणु
पूर्ण

/* the function is at passive_level */
व्योम rtw_joinbss_reset(काष्ठा adapter *padapter)
अणु
	u8 threshold;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;

	/* toकरो: अगर you want to करो something io/reg/hw setting beक्रमe join_bss, please add code here */
	pmlmepriv->num_FortyMHzIntolerant = 0;

	pmlmepriv->num_sta_no_ht = 0;

	phtpriv->ampdu_enable = false;/* reset to disabled */

	/*  TH = 1 => means that invalidate usb rx aggregation */
	/*  TH = 0 => means that validate usb rx aggregation, use init value. */
	अगर (phtpriv->ht_option) अणु
		अगर (padapter->registrypriv.wअगरi_spec == 1)
			threshold = 1;
		अन्यथा
			threshold = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_RXDMA_AGG_PG_TH, (u8 *)(&threshold));
	पूर्ण अन्यथा अणु
		threshold = 1;
		rtw_hal_set_hwreg(padapter, HW_VAR_RXDMA_AGG_PG_TH, (u8 *)(&threshold));
	पूर्ण
पूर्ण

/* the function is >= passive_level */
अचिन्हित पूर्णांक rtw_reकाष्ठाure_ht_ie(काष्ठा adapter *padapter, u8 *in_ie, u8 *out_ie, uपूर्णांक in_len, uपूर्णांक *pout_len)
अणु
	u32 ielen, out_len;
	क्रमागत ht_cap_ampdu_factor max_rx_ampdu_factor;
	अचिन्हित अक्षर *p;
	अचिन्हित अक्षर WMM_IE[] = अणु0x00, 0x50, 0xf2, 0x02, 0x00, 0x01, 0x00पूर्ण;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv *pqospriv = &pmlmepriv->qospriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;
	u32 rx_packet_offset, max_recvbuf_sz;

	phtpriv->ht_option = false;

	p = rtw_get_ie(in_ie + 12, WLAN_EID_HT_CAPABILITY, &ielen, in_len - 12);

	अगर (p && ielen > 0) अणु
		काष्ठा ieee80211_ht_cap ht_cap;

		अगर (pqospriv->qos_option == 0) अणु
			out_len = *pout_len;
			rtw_set_ie(out_ie + out_len, WLAN_EID_VENDOR_SPECIFIC,
				   _WMM_IE_Length_, WMM_IE, pout_len);

			pqospriv->qos_option = 1;
		पूर्ण

		out_len = *pout_len;

		स_रखो(&ht_cap, 0, माप(काष्ठा ieee80211_ht_cap));

		ht_cap.cap_info = cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
					      IEEE80211_HT_CAP_SGI_20 |
					      IEEE80211_HT_CAP_SGI_40 |
					      IEEE80211_HT_CAP_TX_STBC |
					      IEEE80211_HT_CAP_DSSSCCK40);

		rtw_hal_get_def_var(padapter, HAL_DEF_RX_PACKET_OFFSET, &rx_packet_offset);
		rtw_hal_get_def_var(padapter, HAL_DEF_MAX_RECVBUF_SZ, &max_recvbuf_sz);

		/*
		 * ampdu_params_info [1:0]:Max AMPDU Len => 0:8k , 1:16k, 2:32k, 3:64k
		 * ampdu_params_info [4:2]:Min MPDU Start Spacing
		 */

		rtw_hal_get_def_var(padapter, HW_VAR_MAX_RX_AMPDU_FACTOR, &max_rx_ampdu_factor);
		ht_cap.ampdu_params_info = max_rx_ampdu_factor & 0x03;

		अगर (padapter->securitypriv.करोt11PrivacyAlgrthm == _AES_)
			ht_cap.ampdu_params_info |= IEEE80211_HT_AMPDU_PARM_DENSITY & (0x07 << 2);
		अन्यथा
			ht_cap.ampdu_params_info |= IEEE80211_HT_AMPDU_PARM_DENSITY & 0x00;

		rtw_set_ie(out_ie + out_len, WLAN_EID_HT_CAPABILITY,
			   माप(काष्ठा ieee80211_ht_cap),
			   (अचिन्हित अक्षर *)&ht_cap, pout_len);

		phtpriv->ht_option = true;

		p = rtw_get_ie(in_ie + 12, WLAN_EID_HT_OPERATION, &ielen, in_len - 12);
		अगर (p && (ielen == माप(काष्ठा ieee80211_ht_addt_info))) अणु
			out_len = *pout_len;
			rtw_set_ie(out_ie + out_len, WLAN_EID_HT_OPERATION, ielen, p + 2, pout_len);
		पूर्ण
	पूर्ण
	वापस phtpriv->ht_option;
पूर्ण

/* the function is > passive_level (in critical_section) */
व्योम rtw_update_ht_cap(काष्ठा adapter *padapter, u8 *pie, uपूर्णांक ie_len)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (!phtpriv->ht_option)
		वापस;

	अगर ((!pmlmeinfo->HT_info_enable) || (!pmlmeinfo->HT_caps_enable))
		वापस;

	DBG_88E("+%s()\n", __func__);

	/* maybe needs check अगर ap supports rx ampdu. */
	अगर ((!phtpriv->ampdu_enable) && (pregistrypriv->ampdu_enable == 1)) अणु
		अगर (pregistrypriv->wअगरi_spec == 1)
			phtpriv->ampdu_enable = false;
		अन्यथा
			phtpriv->ampdu_enable = true;
	पूर्ण अन्यथा अगर (pregistrypriv->ampdu_enable == 2) अणु
		phtpriv->ampdu_enable = true;
	पूर्ण

	/* update cur_bwmode & cur_ch_offset */
	अगर ((pregistrypriv->cbw40_enable) &&
	    (le16_to_cpu(pmlmeinfo->HT_caps.cap_info) & BIT(1)) &&
	    (pmlmeinfo->HT_info.infos[0] & BIT(2))) अणु
		पूर्णांक i;

		/* update the MCS rates */
		क्रम (i = 0; i < 16; i++)
			((u8 *)&pmlmeinfo->HT_caps.mcs)[i] &= MCS_rate_1R[i];
		/* चयन to the 40M Hz mode according to the AP */
		pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_40;
		चयन ((pmlmeinfo->HT_info.infos[0] & 0x3)) अणु
		हाल HT_EXTCHNL_OFFSET_UPPER:
			pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
			अवरोध;
		हाल HT_EXTCHNL_OFFSET_LOWER:
			pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
			अवरोध;
		शेष:
			pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			अवरोध;
		पूर्ण
	पूर्ण

	/*  Config SM Power Save setting */
	pmlmeinfo->SM_PS = (le16_to_cpu(pmlmeinfo->HT_caps.cap_info) & 0x0C) >> 2;
	अगर (pmlmeinfo->SM_PS == WLAN_HT_CAP_SM_PS_STATIC)
		DBG_88E("%s(): WLAN_HT_CAP_SM_PS_STATIC\n", __func__);

	/*  Config current HT Protection mode. */
	pmlmeinfo->HT_protection = pmlmeinfo->HT_info.infos[1] & 0x3;
पूर्ण

व्योम rtw_issue_addbareq_cmd(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	u8 issued;
	पूर्णांक priority;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा ht_priv *phtpriv;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;

	अगर (is_multicast_ether_addr(pattrib->ra) ||
	    padapter->mlmepriv.LinkDetectInfo.NumTxOkInPeriod < 100)
		वापस;

	priority = pattrib->priority;

	अगर (pattrib->psta)
		psta = pattrib->psta;
	अन्यथा
		psta = rtw_get_stainfo(&padapter->stapriv, pattrib->ra);

	अगर (!psta)
		वापस;

	phtpriv = &psta->htpriv;

	अगर ((phtpriv->ht_option) && (phtpriv->ampdu_enable)) अणु
		issued = (phtpriv->agg_enable_biपंचांगap >> priority) & 0x1;
		issued |= (phtpriv->candidate_tid_biपंचांगap >> priority) & 0x1;

		अगर (issued == 0) अणु
			DBG_88E("%s, p=%d\n", __func__, priority);
			psta->htpriv.candidate_tid_biपंचांगap |= BIT((u8)priority);
			rtw_addbareq_cmd(padapter, (u8)priority, pattrib->ra);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtw_roaming(काष्ठा adapter *padapter, काष्ठा wlan_network *tgt_network)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	spin_lock_bh(&pmlmepriv->lock);
	_rtw_roaming(padapter, tgt_network);
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

व्योम _rtw_roaming(काष्ठा adapter *padapter, काष्ठा wlan_network *tgt_network)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	पूर्णांक करो_join_r;
	काष्ठा wlan_network *pnetwork;

	अगर (tgt_network)
		pnetwork = tgt_network;
	अन्यथा
		pnetwork = &pmlmepriv->cur_network;

	अगर (pmlmepriv->to_roaming > 0) अणु
		DBG_88E("roaming from %s(%pM length:%d\n",
			pnetwork->network.ssid.ssid, pnetwork->network.MacAddress,
			pnetwork->network.ssid.ssid_length);
		स_नकल(&pmlmepriv->assoc_ssid, &pnetwork->network.ssid, माप(काष्ठा ndis_802_11_ssid));

		pmlmepriv->assoc_by_bssid = false;

		जबतक (1) अणु
			करो_join_r = rtw_करो_join(padapter);
			अगर (करो_join_r == _SUCCESS)
				अवरोध;

			DBG_88E("roaming do_join return %d\n", करो_join_r);
			pmlmepriv->to_roaming--;

			अगर (pmlmepriv->to_roaming > 0) अणु
				जारी;
			पूर्ण अन्यथा अणु
				DBG_88E("%s(%d) -to roaming fail, indicate_disconnect\n", __func__, __LINE__);
				rtw_indicate_disconnect(padapter);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
