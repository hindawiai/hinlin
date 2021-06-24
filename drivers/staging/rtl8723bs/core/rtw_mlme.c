<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_MLME_C_

#समावेश <linux/etherdevice.h>
#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_btcoex.h>
#समावेश <linux/jअगरfies.h>

पूर्णांक	rtw_init_mlme_priv(काष्ठा adapter *padapter)
अणु
	पूर्णांक	i;
	u8 *pbuf;
	काष्ठा wlan_network	*pnetwork;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	पूर्णांक	res = _SUCCESS;

	pmlmepriv->nic_hdl = (u8 *)padapter;

	pmlmepriv->pscanned = शून्य;
	pmlmepriv->fw_state = WIFI_STATION_STATE; /*  Must sync with rtw_wdev_alloc() */
	/*  wdev->अगरtype = NL80211_IFTYPE_STATION */
	pmlmepriv->cur_network.network.Infraकाष्ठाureMode = Ndis802_11AutoUnknown;
	pmlmepriv->scan_mode = SCAN_ACTIVE;/*  1: active, 0: pasive. Maybe someday we should नाम this varable to "active_mode" (Jeff) */

	spin_lock_init(&pmlmepriv->lock);
	_rtw_init_queue(&pmlmepriv->मुक्त_bss_pool);
	_rtw_init_queue(&pmlmepriv->scanned_queue);

	set_scanned_network_val(pmlmepriv, 0);

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

	#घोषणा RTW_ROAM_SCAN_RESULT_EXP_MS 5000
	#घोषणा RTW_ROAM_RSSI_DIFF_TH 10
	#घोषणा RTW_ROAM_SCAN_INTERVAL_MS 10000

	pmlmepriv->roam_flags = 0
		| RTW_ROAM_ON_EXPIRED
		| RTW_ROAM_ON_RESUME
		;

	pmlmepriv->roam_scanr_exp_ms = RTW_ROAM_SCAN_RESULT_EXP_MS;
	pmlmepriv->roam_rssi_dअगरf_th = RTW_ROAM_RSSI_DIFF_TH;
	pmlmepriv->roam_scan_पूर्णांक_ms = RTW_ROAM_SCAN_INTERVAL_MS;

	rtw_init_mlme_समयr(padapter);

निकास:

	वापस res;
पूर्ण

अटल व्योम rtw_मुक्त_mlme_ie_data(u8 **ppie, u32 *plen)
अणु
	अगर (*ppie) अणु
		kमुक्त(*ppie);
		*plen = 0;
		*ppie = शून्य;
	पूर्ण
पूर्ण

व्योम rtw_मुक्त_mlme_priv_ie_data(काष्ठा mlme_priv *pmlmepriv)
अणु
	rtw_buf_मुक्त(&pmlmepriv->assoc_req, &pmlmepriv->assoc_req_len);
	rtw_buf_मुक्त(&pmlmepriv->assoc_rsp, &pmlmepriv->assoc_rsp_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->wps_beacon_ie, &pmlmepriv->wps_beacon_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->wps_probe_req_ie, &pmlmepriv->wps_probe_req_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->wps_probe_resp_ie, &pmlmepriv->wps_probe_resp_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->wps_assoc_resp_ie, &pmlmepriv->wps_assoc_resp_ie_len);

	rtw_मुक्त_mlme_ie_data(&pmlmepriv->p2p_beacon_ie, &pmlmepriv->p2p_beacon_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->p2p_probe_req_ie, &pmlmepriv->p2p_probe_req_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->p2p_probe_resp_ie, &pmlmepriv->p2p_probe_resp_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->p2p_go_probe_resp_ie, &pmlmepriv->p2p_go_probe_resp_ie_len);
	rtw_मुक्त_mlme_ie_data(&pmlmepriv->p2p_assoc_req_ie, &pmlmepriv->p2p_assoc_req_ie_len);
पूर्ण

व्योम _rtw_मुक्त_mlme_priv(काष्ठा mlme_priv *pmlmepriv)
अणु
	अगर (pmlmepriv) अणु
		rtw_मुक्त_mlme_priv_ie_data(pmlmepriv);
		vमुक्त(pmlmepriv->मुक्त_bss_buf);
	पूर्ण
पूर्ण

/*
काष्ठा	wlan_network *_rtw_dequeue_network(काष्ठा __queue *queue)
अणु
	_irqL irqL;

	काष्ठा wlan_network *pnetwork;

	spin_lock_bh(&queue->lock);

	अगर (list_empty(&queue->queue))

		pnetwork = शून्य;

	अन्यथा
	अणु
		pnetwork = container_of(get_next(&queue->queue), काष्ठा wlan_network, list);

		list_del_init(&(pnetwork->list));
	पूर्ण

	spin_unlock_bh(&queue->lock);

	वापस pnetwork;
पूर्ण
*/

काष्ठा	wlan_network *rtw_alloc_network(काष्ठा	mlme_priv *pmlmepriv)
अणु
	काष्ठा	wlan_network	*pnetwork;
	काष्ठा __queue *मुक्त_queue = &pmlmepriv->मुक्त_bss_pool;
	काष्ठा list_head *plist = शून्य;

	spin_lock_bh(&मुक्त_queue->lock);

	अगर (list_empty(&मुक्त_queue->queue)) अणु
		pnetwork = शून्य;
		जाओ निकास;
	पूर्ण
	plist = get_next(&(मुक्त_queue->queue));

	pnetwork = container_of(plist, काष्ठा wlan_network, list);

	list_del_init(&pnetwork->list);

	pnetwork->network_type = 0;
	pnetwork->fixed = false;
	pnetwork->last_scanned = jअगरfies;
	pnetwork->aid = 0;
	pnetwork->join_res = 0;

	pmlmepriv->num_of_scanned++;

निकास:
	spin_unlock_bh(&मुक्त_queue->lock);

	वापस pnetwork;
पूर्ण

व्योम _rtw_मुक्त_network(काष्ठा	mlme_priv *pmlmepriv, काष्ठा wlan_network *pnetwork, u8 isमुक्तall)
अणु
	अचिन्हित पूर्णांक delta_समय;
	u32 lअगरeसमय = SCANQUEUE_LIFETIME;
/* 	_irqL irqL; */
	काष्ठा __queue *मुक्त_queue = &(pmlmepriv->मुक्त_bss_pool);

	अगर (!pnetwork)
		वापस;

	अगर (pnetwork->fixed)
		वापस;

	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true))
		lअगरeसमय = 1;

	अगर (!isमुक्तall) अणु
		delta_समय = jअगरfies_to_msecs(jअगरfies - pnetwork->last_scanned);
		अगर (delta_समय < lअगरeसमय)/*  unit:msec */
			वापस;
	पूर्ण

	spin_lock_bh(&मुक्त_queue->lock);

	list_del_init(&(pnetwork->list));

	list_add_tail(&(pnetwork->list), &(मुक्त_queue->queue));

	pmlmepriv->num_of_scanned--;

	spin_unlock_bh(&मुक्त_queue->lock);
पूर्ण

व्योम _rtw_मुक्त_network_nolock(काष्ठा	mlme_priv *pmlmepriv, काष्ठा wlan_network *pnetwork)
अणु

	काष्ठा __queue *मुक्त_queue = &(pmlmepriv->मुक्त_bss_pool);

	अगर (!pnetwork)
		वापस;

	अगर (pnetwork->fixed)
		वापस;

	/* spin_lock_irqsave(&मुक्त_queue->lock, irqL); */

	list_del_init(&(pnetwork->list));

	list_add_tail(&(pnetwork->list), get_list_head(मुक्त_queue));

	pmlmepriv->num_of_scanned--;

	/* spin_unlock_irqrestore(&मुक्त_queue->lock, irqL); */
पूर्ण

/*
	वापस the wlan_network with the matching addr

	Shall be called under atomic context... to aव्योम possible racing condition...
*/
काष्ठा wlan_network *_rtw_find_network(काष्ठा __queue *scanned_queue, u8 *addr)
अणु
	काष्ठा list_head	*phead, *plist;
	काष्ठा	wlan_network *pnetwork = शून्य;
	u8 zero_addr[ETH_ALEN] = अणु0, 0, 0, 0, 0, 0पूर्ण;

	अगर (!स_भेद(zero_addr, addr, ETH_ALEN)) अणु
		pnetwork = शून्य;
		जाओ निकास;
	पूर्ण

	/* spin_lock_bh(&scanned_queue->lock); */

	phead = get_list_head(scanned_queue);
	plist = get_next(phead);

	जबतक (plist != phead) अणु
		pnetwork = container_of(plist, काष्ठा wlan_network, list);

		अगर (!स_भेद(addr, pnetwork->network.MacAddress, ETH_ALEN))
			अवरोध;

		plist = get_next(plist);
	पूर्ण

	अगर (plist == phead)
		pnetwork = शून्य;

	/* spin_unlock_bh(&scanned_queue->lock); */

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
	plist = get_next(phead);

	जबतक (phead != plist) अणु

		pnetwork = container_of(plist, काष्ठा wlan_network, list);

		plist = get_next(plist);

		_rtw_मुक्त_network(pmlmepriv, pnetwork, isमुक्तall);

	पूर्ण

	spin_unlock_bh(&scanned_queue->lock);
पूर्ण

चिन्हित पूर्णांक rtw_अगर_up(काष्ठा adapter *padapter)
अणु
	चिन्हित पूर्णांक res;

	अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved ||
		(check_fwstate(&padapter->mlmepriv, _FW_LINKED) == false))
		res = false;
	अन्यथा
		res =  true;

	वापस res;
पूर्ण

व्योम rtw_generate_अक्रमom_ibss(u8 *pibss)
अणु
	अचिन्हित दीर्घ curसमय = jअगरfies;

	pibss[0] = 0x02;  /* in ad-hoc mode bit1 must set to 1 */
	pibss[1] = 0x11;
	pibss[2] = 0x87;
	pibss[3] = (u8)(curसमय & 0xff) ;/* p[0]; */
	pibss[4] = (u8)((curसमय>>8) & 0xff) ;/* p[1]; */
	pibss[5] = (u8)((curसमय>>16) & 0xff) ;/* p[2]; */
पूर्ण

u8 *rtw_get_capability_from_ie(u8 *ie)
अणु
	वापस ie + 8 + 2;
पूर्ण

u16 rtw_get_capability(काष्ठा wlan_bssid_ex *bss)
अणु
	__le16	val;

	स_नकल((u8 *)&val, rtw_get_capability_from_ie(bss->IEs), 2);

	वापस le16_to_cpu(val);
पूर्ण

u8 *rtw_get_beacon_पूर्णांकerval_from_ie(u8 *ie)
अणु
	वापस ie + 8;
पूर्ण

व्योम rtw_मुक्त_mlme_priv(काष्ठा mlme_priv *pmlmepriv)
अणु
	_rtw_मुक्त_mlme_priv(pmlmepriv);
पूर्ण

/*
अटल काष्ठा	wlan_network *rtw_dequeue_network(काष्ठा __queue *queue)
अणु
	काष्ठा wlan_network *pnetwork;

	pnetwork = _rtw_dequeue_network(queue);
	वापस pnetwork;
पूर्ण
*/

व्योम rtw_मुक्त_network_nolock(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork);
व्योम rtw_मुक्त_network_nolock(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork)
अणु
	_rtw_मुक्त_network_nolock(&(padapter->mlmepriv), pnetwork);
	rtw_cfg80211_unlink_bss(padapter, pnetwork);
पूर्ण

/*
	वापस the wlan_network with the matching addr

	Shall be called under atomic context... to aव्योम possible racing condition...
*/
काष्ठा	wlan_network *rtw_find_network(काष्ठा __queue *scanned_queue, u8 *addr)
अणु
	काष्ठा	wlan_network *pnetwork = _rtw_find_network(scanned_queue, addr);

	वापस pnetwork;
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

अंतरभूत पूर्णांक is_same_ess(काष्ठा wlan_bssid_ex *a, काष्ठा wlan_bssid_ex *b)
अणु
	वापस (a->Ssid.SsidLength == b->Ssid.SsidLength)
		&&  !स_भेद(a->Ssid.Ssid, b->Ssid.Ssid, a->Ssid.SsidLength);
पूर्ण

पूर्णांक is_same_network(काष्ठा wlan_bssid_ex *src, काष्ठा wlan_bssid_ex *dst, u8 feature)
अणु
	u16 s_cap, d_cap;
	__le16 पंचांगps, पंचांगpd;

	अगर (rtw_bug_check(dst, src, &s_cap, &d_cap) == false)
			वापस false;

	स_नकल((u8 *)&पंचांगps, rtw_get_capability_from_ie(src->IEs), 2);
	स_नकल((u8 *)&पंचांगpd, rtw_get_capability_from_ie(dst->IEs), 2);

	s_cap = le16_to_cpu(पंचांगps);
	d_cap = le16_to_cpu(पंचांगpd);

	वापस (src->Ssid.SsidLength == dst->Ssid.SsidLength) &&
		/* 	(src->Configuration.DSConfig == dst->Configuration.DSConfig) && */
			((!स_भेद(src->MacAddress, dst->MacAddress, ETH_ALEN))) &&
			((!स_भेद(src->Ssid.Ssid, dst->Ssid.Ssid, src->Ssid.SsidLength))) &&
			((s_cap & WLAN_CAPABILITY_IBSS) ==
			(d_cap & WLAN_CAPABILITY_IBSS)) &&
			((s_cap & WLAN_CAPABILITY_ESS) ==
			(d_cap & WLAN_CAPABILITY_ESS));

पूर्ण

काष्ठा wlan_network *_rtw_find_same_network(काष्ठा __queue *scanned_queue, काष्ठा wlan_network *network)
अणु
	काष्ठा list_head *phead, *plist;
	काष्ठा wlan_network *found = शून्य;

	phead = get_list_head(scanned_queue);
	plist = get_next(phead);

	जबतक (plist != phead) अणु
		found = container_of(plist, काष्ठा wlan_network, list);

		अगर (is_same_network(&network->network, &found->network, 0))
			अवरोध;

		plist = get_next(plist);
	पूर्ण

	अगर (plist == phead)
		found = शून्य;

	वापस found;
पूर्ण

काष्ठा	wlan_network	*rtw_get_oldest_wlan_network(काष्ठा __queue *scanned_queue)
अणु
	काष्ठा list_head	*plist, *phead;

	काष्ठा	wlan_network	*pwlan = शून्य;
	काष्ठा	wlan_network	*oldest = शून्य;

	phead = get_list_head(scanned_queue);

	plist = get_next(phead);

	जबतक (1) अणु

		अगर (phead == plist)
			अवरोध;

		pwlan = container_of(plist, काष्ठा wlan_network, list);

		अगर (!pwlan->fixed) अणु
			अगर (oldest == शून्य || समय_after(oldest->last_scanned, pwlan->last_scanned))
				oldest = pwlan;
		पूर्ण

		plist = get_next(plist);
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

	/* The rule below is 1/5 क्रम sample value, 4/5 क्रम history value */
	अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED) && is_same_network(&(padapter->mlmepriv.cur_network.network), src, 0)) अणु
		/* Take the recvpriv's value क्रम the connected AP*/
		ss_final = padapter->recvpriv.संकेत_strength;
		sq_final = padapter->recvpriv.संकेत_qual;
		/* the rssi value here is undecorated, and will be used क्रम antenna भागersity */
		अगर (sq_smp != 101) /* from the right channel */
			rssi_final = (src->Rssi+dst->Rssi*4)/5;
		अन्यथा
			rssi_final = rssi_ori;
	पूर्ण अन्यथा अणु
		अगर (sq_smp != 101) अणु /* from the right channel */
			ss_final = ((u32)(src->PhyInfo.SignalStrength)+(u32)(dst->PhyInfo.SignalStrength)*4)/5;
			sq_final = ((u32)(src->PhyInfo.SignalQuality)+(u32)(dst->PhyInfo.SignalQuality)*4)/5;
			rssi_final = (src->Rssi+dst->Rssi*4)/5;
		पूर्ण अन्यथा अणु
			/* bss info not receiving from the right channel, use the original RX संकेत infos */
			ss_final = dst->PhyInfo.SignalStrength;
			sq_final = dst->PhyInfo.SignalQuality;
			rssi_final = dst->Rssi;
		पूर्ण

	पूर्ण

	अगर (update_ie) अणु
		dst->Reserved[0] = src->Reserved[0];
		dst->Reserved[1] = src->Reserved[1];
		स_नकल((u8 *)dst, (u8 *)src, get_wlan_bssid_ex_sz(src));
	पूर्ण

	dst->PhyInfo.SignalStrength = ss_final;
	dst->PhyInfo.SignalQuality = sq_final;
	dst->Rssi = rssi_final;
पूर्ण

अटल व्योम update_current_network(काष्ठा adapter *adapter, काष्ठा wlan_bssid_ex *pnetwork)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &(adapter->mlmepriv);

	rtw_bug_check(&(pmlmepriv->cur_network.network),
		&(pmlmepriv->cur_network.network),
		&(pmlmepriv->cur_network.network),
		&(pmlmepriv->cur_network.network));

	अगर ((check_fwstate(pmlmepriv, _FW_LINKED) == true) && (is_same_network(&(pmlmepriv->cur_network.network), pnetwork, 0))) अणु
		/* अगर (pmlmepriv->cur_network.network.IELength<= pnetwork->IELength) */
		अणु
			update_network(&(pmlmepriv->cur_network.network), pnetwork, adapter, true);
			rtw_update_protection(adapter, (pmlmepriv->cur_network.network.IEs) + माप(काष्ठा ndis_802_11_fix_ie),
									pmlmepriv->cur_network.network.IELength);
		पूर्ण
	पूर्ण
पूर्ण

/*
Caller must hold pmlmepriv->lock first.
*/
व्योम rtw_update_scanned_network(काष्ठा adapter *adapter, काष्ठा wlan_bssid_ex *target)
अणु
	काष्ठा list_head	*plist, *phead;
	u32 bssid_ex_sz;
	काष्ठा mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	काष्ठा __queue	*queue	= &(pmlmepriv->scanned_queue);
	काष्ठा wlan_network	*pnetwork = शून्य;
	काष्ठा wlan_network	*oldest = शून्य;
	पूर्णांक target_find = 0;
	u8 feature = 0;

	spin_lock_bh(&queue->lock);
	phead = get_list_head(queue);
	plist = get_next(phead);

	जबतक (1) अणु
		अगर (phead == plist)
			अवरोध;

		pnetwork = container_of(plist, काष्ठा wlan_network, list);

		rtw_bug_check(pnetwork, pnetwork, pnetwork, pnetwork);

		अगर (is_same_network(&(pnetwork->network), target, feature)) अणु
			target_find = 1;
			अवरोध;
		पूर्ण

		अगर (rtw_roam_flags(adapter)) अणु
			/* TODO: करोn't select network in the same ess as oldest if it's new enough*/
		पूर्ण

		अगर (oldest == शून्य || समय_after(oldest->last_scanned, pnetwork->last_scanned))
			oldest = pnetwork;

		plist = get_next(plist);

	पूर्ण

	/* If we didn't find a match, then get a new network slot to initialize
	 * with this beacon's inक्रमmation */
	/* अगर (phead == plist) अणु */
	अगर (!target_find) अणु
		अगर (list_empty(&pmlmepriv->मुक्त_bss_pool.queue)) अणु
			/* If there are no more slots, expire the oldest */
			/* list_del_init(&oldest->list); */
			pnetwork = oldest;
			अगर (!pnetwork)
				जाओ निकास;

			स_नकल(&(pnetwork->network), target,  get_wlan_bssid_ex_sz(target));
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

			अगर (!pnetwork)
				जाओ निकास;

			bssid_ex_sz = get_wlan_bssid_ex_sz(target);
			target->Length = bssid_ex_sz;
			स_नकल(&(pnetwork->network), target, bssid_ex_sz);

			pnetwork->last_scanned = jअगरfies;

			/* bss info not receiving from the right channel */
			अगर (pnetwork->network.PhyInfo.SignalQuality == 101)
				pnetwork->network.PhyInfo.SignalQuality = 0;

			list_add_tail(&(pnetwork->list), &(queue->queue));

		पूर्ण
	पूर्ण अन्यथा अणु
		/* we have an entry and we are going to update it. But this entry may
		 * be alपढ़ोy expired. In this हाल we करो the same as we found a new
		 * net and call the new_net handler
		 */
		bool update_ie = true;

		pnetwork->last_scanned = jअगरfies;

		/* target.Reserved[0]== 1, means that scanned network is a bcn frame. */
		अगर ((pnetwork->network.IELength > target->IELength) && (target->Reserved[0] == 1))
			update_ie = false;

		/*  probe resp(3) > beacon(1) > probe req(2) */
		अगर ((target->Reserved[0] != 2) &&
			(target->Reserved[0] >= pnetwork->network.Reserved[0])
			) अणु
			update_ie = true;
		पूर्ण अन्यथा अणु
			update_ie = false;
		पूर्ण

		update_network(&(pnetwork->network), target, adapter, update_ie);
	पूर्ण

निकास:
	spin_unlock_bh(&queue->lock);
पूर्ण

व्योम rtw_add_network(काष्ठा adapter *adapter, काष्ठा wlan_bssid_ex *pnetwork);
व्योम rtw_add_network(काष्ठा adapter *adapter, काष्ठा wlan_bssid_ex *pnetwork)
अणु
	/* काष्ठा __queue	*queue	= &(pmlmepriv->scanned_queue); */

	/* spin_lock_bh(&queue->lock); */

	update_current_network(adapter, pnetwork);

	rtw_update_scanned_network(adapter, pnetwork);

	/* spin_unlock_bh(&queue->lock); */
पूर्ण

/* select the desired network based on the capability of the (i)bss. */
/*  check items: (1) security */
/* 			   (2) network_type */
/* 			   (3) WMM */
/* 			   (4) HT */
/*                      (5) others */
पूर्णांक rtw_is_desired_network(काष्ठा adapter *adapter, काष्ठा wlan_network *pnetwork);
पूर्णांक rtw_is_desired_network(काष्ठा adapter *adapter, काष्ठा wlan_network *pnetwork)
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
		अगर (rtw_get_wps_ie(pnetwork->network.IEs+_FIXED_IE_LENGTH_, pnetwork->network.IELength-_FIXED_IE_LENGTH_, शून्य, &wps_ielen))
			वापस true;
		अन्यथा
			वापस false;

	पूर्ण
	अगर (adapter->registrypriv.wअगरi_spec == 1) अणु /* क्रम  correct flow of 8021X  to करो.... */
		u8 *p = शून्य;
		uपूर्णांक ie_len = 0;

		अगर ((desired_encmode == Ndis802_11EncryptionDisabled) && (privacy != 0))
	    bselected = false;

		अगर (psecuritypriv->ndisauthtype == Ndis802_11AuthModeWPA2PSK) अणु
			p = rtw_get_ie(pnetwork->network.IEs + _BEACON_IE_OFFSET_, WLAN_EID_RSN, &ie_len, (pnetwork->network.IELength - _BEACON_IE_OFFSET_));
			अगर (p && ie_len > 0)
				bselected = true;
			अन्यथा
				bselected = false;
		पूर्ण
	पूर्ण

	अगर ((desired_encmode != Ndis802_11EncryptionDisabled) && (privacy == 0))
		bselected = false;

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true) अणु
		अगर (pnetwork->network.Infraकाष्ठाureMode != pmlmepriv->cur_network.network.Infraकाष्ठाureMode)
			bselected = false;
	पूर्ण

	वापस bselected;
पूर्ण

/* TODO: Perry : For Power Management */
व्योम rtw_atimकरोne_event_callback(काष्ठा adapter	*adapter, u8 *pbuf)
अणु
पूर्ण

व्योम rtw_survey_event_callback(काष्ठा adapter	*adapter, u8 *pbuf)
अणु
	u32 len;
	काष्ठा wlan_bssid_ex *pnetwork;
	काष्ठा	mlme_priv *pmlmepriv = &(adapter->mlmepriv);

	pnetwork = (काष्ठा wlan_bssid_ex *)pbuf;

	len = get_wlan_bssid_ex_sz(pnetwork);
	अगर (len > (माप(काष्ठा wlan_bssid_ex)))
		वापस;

	spin_lock_bh(&pmlmepriv->lock);

	/*  update IBSS_network 's बारtamp */
	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) == true) अणु
		अगर (!स_भेद(&(pmlmepriv->cur_network.network.MacAddress), pnetwork->MacAddress, ETH_ALEN)) अणु
			काष्ठा wlan_network *ibss_wlan = शून्य;

			स_नकल(pmlmepriv->cur_network.network.IEs, pnetwork->IEs, 8);
			spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
			ibss_wlan = rtw_find_network(&pmlmepriv->scanned_queue,  pnetwork->MacAddress);
			अगर (ibss_wlan) अणु
				स_नकल(ibss_wlan->network.IEs, pnetwork->IEs, 8);
				spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
				जाओ निकास;
			पूर्ण
			spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
		पूर्ण
	पूर्ण

	/*  lock pmlmepriv->lock when you accessing network_q */
	अगर ((check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) == false) अणु
		अगर (pnetwork->Ssid.Ssid[0] == 0)
			pnetwork->Ssid.SsidLength = 0;
		rtw_add_network(adapter, pnetwork);
	पूर्ण

निकास:

	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

व्योम rtw_surveyकरोne_event_callback(काष्ठा adapter	*adapter, u8 *pbuf)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &(adapter->mlmepriv);

	spin_lock_bh(&pmlmepriv->lock);
	अगर (pmlmepriv->wps_probe_req_ie) अणु
		pmlmepriv->wps_probe_req_ie_len = 0;
		kमुक्त(pmlmepriv->wps_probe_req_ie);
		pmlmepriv->wps_probe_req_ie = शून्य;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY)) अणु
		del_समयr_sync(&pmlmepriv->scan_to_समयr);
		_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	पूर्ण

	rtw_set_संकेत_stat_समयr(&adapter->recvpriv);

	अगर (pmlmepriv->to_join) अणु
		अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true)) अणु
			अगर (check_fwstate(pmlmepriv, _FW_LINKED) == false) अणु
				set_fwstate(pmlmepriv, _FW_UNDER_LINKING);

				अगर (rtw_select_and_join_from_scanned_queue(pmlmepriv) == _SUCCESS) अणु
					_set_समयr(&pmlmepriv->assoc_समयr, MAX_JOIN_TIMEOUT);
				पूर्ण अन्यथा अणु
					u8 ret = _SUCCESS;
					काष्ठा wlan_bssid_ex    *pdev_network = &(adapter->registrypriv.dev_network);
					u8 *pibss = adapter->registrypriv.dev_network.MacAddress;

					/* pmlmepriv->fw_state ^= _FW_UNDER_SURVEY;because करोn't set assoc_समयr */
					_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);

					स_नकल(&pdev_network->Ssid, &pmlmepriv->assoc_ssid, माप(काष्ठा ndis_802_11_ssid));

					rtw_update_registrypriv_dev_network(adapter);
					rtw_generate_अक्रमom_ibss(pibss);

					pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;

					pmlmepriv->to_join = false;

					ret = rtw_createbss_cmd(adapter);
					अगर (ret != _SUCCESS)
						जाओ unlock;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक s_ret;

			set_fwstate(pmlmepriv, _FW_UNDER_LINKING);
			pmlmepriv->to_join = false;
			s_ret = rtw_select_and_join_from_scanned_queue(pmlmepriv);
			अगर (_SUCCESS == s_ret) अणु
			     _set_समयr(&pmlmepriv->assoc_समयr, MAX_JOIN_TIMEOUT);
			पूर्ण अन्यथा अगर (s_ret == 2) अणु/* there is no need to रुको क्रम join */
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
				rtw_indicate_connect(adapter);
			पूर्ण अन्यथा अणु
				अगर (rtw_to_roam(adapter) != 0) अणु
					अगर (rtw_dec_to_roam(adapter) == 0
						|| _SUCCESS != rtw_sitesurvey_cmd(adapter, &pmlmepriv->assoc_ssid, 1, शून्य, 0)
					) अणु
						rtw_set_to_roam(adapter, 0);
						rtw_मुक्त_assoc_resources(adapter, 1);
						rtw_indicate_disconnect(adapter);
					पूर्ण अन्यथा अणु
						pmlmepriv->to_join = true;
					पूर्ण
				पूर्ण अन्यथा
					rtw_indicate_disconnect(adapter);

				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rtw_chk_roam_flags(adapter, RTW_ROAM_ACTIVE)) अणु
			अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)
				&& check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				अगर (rtw_select_roaming_candidate(pmlmepriv) == _SUCCESS) अणु
					receive_disconnect(adapter, pmlmepriv->cur_network.network.MacAddress
						, WLAN_REASON_ACTIVE_ROAM);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

unlock:
	spin_unlock_bh(&pmlmepriv->lock);

	rtw_os_xmit_schedule(adapter);

	rtw_cfg80211_surveyकरोne_event_callback(adapter);

	rtw_indicate_scan_करोne(adapter, false);
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
	काष्ठा list_head	*plist, *phead, *ptemp;

	spin_lock_bh(&scan_queue->lock);
	spin_lock_bh(&मुक्त_queue->lock);

	phead = get_list_head(scan_queue);
	plist = get_next(phead);

	जबतक (plist != phead) अणु
		ptemp = get_next(plist);
		list_del_init(plist);
		list_add_tail(plist, &मुक्त_queue->queue);
		plist = ptemp;
		pmlmepriv->num_of_scanned--;
	पूर्ण

	spin_unlock_bh(&मुक्त_queue->lock);
	spin_unlock_bh(&scan_queue->lock);
पूर्ण

अटल व्योम rtw_reset_rx_info(काष्ठा debug_priv *pdbgpriv)
अणु
	pdbgpriv->dbg_rx_ampdu_drop_count = 0;
	pdbgpriv->dbg_rx_ampdu_क्रमced_indicate_count = 0;
	pdbgpriv->dbg_rx_ampdu_loss_count = 0;
	pdbgpriv->dbg_rx_dup_mgt_frame_drop_count = 0;
	pdbgpriv->dbg_rx_ampdu_winकरोw_shअगरt_cnt = 0;
पूर्ण

अटल व्योम find_network(काष्ठा adapter *adapter)
अणु
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा wlan_network *tgt_network = &pmlmepriv->cur_network;

	pwlan = rtw_find_network(&pmlmepriv->scanned_queue, tgt_network->network.MacAddress);
	अगर (pwlan)
		pwlan->fixed = false;

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) &&
	    (adapter->stapriv.asoc_sta_count == 1))
		rtw_मुक्त_network_nolock(adapter, pwlan);
पूर्ण

/*
*rtw_मुक्त_assoc_resources: the caller has to lock pmlmepriv->lock
*/
व्योम rtw_मुक्त_assoc_resources(काष्ठा adapter *adapter, पूर्णांक lock_scanned_queue)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा wlan_network *tgt_network = &pmlmepriv->cur_network;
	काष्ठा	sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा dvobj_priv *psdpriv = adapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE|WIFI_AP_STATE)) अणु
		काष्ठा sta_info *psta;

		psta = rtw_get_stainfo(&adapter->stapriv, tgt_network->network.MacAddress);
		spin_lock_bh(&(pstapriv->sta_hash_lock));
		rtw_मुक्त_stainfo(adapter,  psta);

		spin_unlock_bh(&(pstapriv->sta_hash_lock));

	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE|WIFI_AP_STATE)) अणु
		काष्ठा sta_info *psta;

		rtw_मुक्त_all_stainfo(adapter);

		psta = rtw_get_bcmc_stainfo(adapter);
		rtw_मुक्त_stainfo(adapter, psta);

		rtw_init_bcmc_stainfo(adapter);
	पूर्ण

	find_network(adapter);

	अगर (lock_scanned_queue)
		adapter->securitypriv.key_mask = 0;

	rtw_reset_rx_info(pdbgpriv);
पूर्ण

/*
*rtw_indicate_connect: the caller has to lock pmlmepriv->lock
*/
व्योम rtw_indicate_connect(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	pmlmepriv->to_join = false;

	अगर (!check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु

		set_fwstate(pmlmepriv, _FW_LINKED);

		rtw_os_indicate_connect(padapter);
	पूर्ण

	rtw_set_to_roam(padapter, 0);
	rtw_set_scan_deny(padapter, 3000);

पूर्ण

/*
*rtw_indicate_disconnect: the caller has to lock pmlmepriv->lock
*/
व्योम rtw_indicate_disconnect(काष्ठा adapter *padapter)
अणु
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING|WIFI_UNDER_WPS);

	अगर (rtw_to_roam(padapter) > 0)
		_clr_fwstate_(pmlmepriv, _FW_LINKED);

	अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED)
		|| (rtw_to_roam(padapter) <= 0)
	) अणु
		rtw_os_indicate_disconnect(padapter);

		/* set ips_deny_समय to aव्योम enter IPS beक्रमe LPS leave */
		rtw_set_ips_deny(padapter, 3000);

		_clr_fwstate_(pmlmepriv, _FW_LINKED);

		rtw_clear_scan_deny(padapter);
	पूर्ण

	rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_DISCONNECT, 1);
पूर्ण

अंतरभूत व्योम rtw_indicate_scan_करोne(काष्ठा adapter *padapter, bool पातed)
अणु
	rtw_os_indicate_scan_करोne(padapter, पातed);

	अगर (is_primary_adapter(padapter) &&
	    (!adapter_to_pwrctl(padapter)->bInSuspend) &&
	    (!check_fwstate(&padapter->mlmepriv,
			    WIFI_ASOC_STATE|WIFI_UNDER_LINKING))) अणु
		rtw_set_ips_deny(padapter, 0);
		_set_समयr(&padapter->mlmepriv.dynamic_chk_समयr, 1);
	पूर्ण
पूर्ण

व्योम rtw_scan_पात(काष्ठा adapter *adapter)
अणु
	अचिन्हित दीर्घ start;
	काष्ठा mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	काष्ठा mlme_ext_priv *pmlmeext = &(adapter->mlmeextpriv);

	start = jअगरfies;
	pmlmeext->scan_पात = true;
	जबतक (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY)
		&& jअगरfies_to_msecs(start) <= 200) अणु

		अगर (adapter->bDriverStopped || adapter->bSurpriseRemoved)
			अवरोध;

		msleep(20);
	पूर्ण

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY))
		rtw_indicate_scan_करोne(adapter, true);

	pmlmeext->scan_पात = false;
पूर्ण

अटल काष्ठा sta_info *rtw_joinbss_update_stainfo(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork)
अणु
	पूर्णांक i;
	काष्ठा sta_info *bmc_sta, *psta = शून्य;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	psta = rtw_get_stainfo(pstapriv, pnetwork->network.MacAddress);
	अगर (!psta)
		psta = rtw_alloc_stainfo(pstapriv, pnetwork->network.MacAddress);

	अगर (psta) अणु /* update ptarget_sta */

		psta->aid  = pnetwork->join_res;

		update_sta_info(padapter, psta);

		/* update station supportRate */
		psta->bssratelen = rtw_get_rateset_len(pnetwork->network.SupportedRates);
		स_नकल(psta->bssrateset, pnetwork->network.SupportedRates, psta->bssratelen);
		rtw_hal_update_sta_rate_mask(padapter, psta);

		psta->wireless_mode = pmlmeext->cur_wireless_mode;
		psta->raid = networktype_to_raid_ex(padapter, psta);

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
			psta->करोt11txpn.val = psta->करोt11txpn.val + 1;
			स_रखो((u8 *)&psta->करोt11wtxpn, 0, माप(जोड़ pn48));
			स_रखो((u8 *)&psta->करोt11rxpn, 0, माप(जोड़ pn48));
		पूर्ण

		/* 	Commented by Albert 2012/07/21 */
		/* 	When करोing the WPS, the wps_ie_len won't equal to 0 */
		/* 	And the Wi-Fi driver shouldn't allow the data packet to be transmitted. */
		अगर (padapter->securitypriv.wps_ie_len != 0) अणु
			psta->ieee8021x_blocked = true;
			padapter->securitypriv.wps_ie_len = 0;
		पूर्ण

		/* क्रम A-MPDU Rx reordering buffer control क्रम bmc_sta & sta_info */
		/* अगर A-MPDU Rx is enabled, resetting  rx_ordering_ctrl wstart_b(indicate_seq) to शेष value = 0xffff */
		/* toकरो: check अगर AP can send A-MPDU packets */
		क्रम (i = 0; i < 16 ; i++) अणु
			/* preorder_ctrl = &precvpriv->recvreorder_ctrl[i]; */
			preorder_ctrl = &psta->recvreorder_ctrl[i];
			preorder_ctrl->enable = false;
			preorder_ctrl->indicate_seq = 0xffff;
			preorder_ctrl->wend_b = 0xffff;
			preorder_ctrl->wsize_b = 64;/* max_ampdu_sz;ex. 32(kbytes) -> wsize_b =32 */
		पूर्ण

		bmc_sta = rtw_get_bcmc_stainfo(padapter);
		अगर (bmc_sta) अणु
			क्रम (i = 0; i < 16 ; i++) अणु
				/* preorder_ctrl = &precvpriv->recvreorder_ctrl[i]; */
				preorder_ctrl = &bmc_sta->recvreorder_ctrl[i];
				preorder_ctrl->enable = false;
				preorder_ctrl->indicate_seq = 0xffff;
				preorder_ctrl->wend_b = 0xffff;
				preorder_ctrl->wsize_b = 64;/* max_ampdu_sz;ex. 32(kbytes) -> wsize_b =32 */
			पूर्ण
		पूर्ण
	पूर्ण

	वापस psta;

पूर्ण

/* pnetwork : वापसs from rtw_joinbss_event_callback */
/* ptarget_wlan: found from scanned_queue */
अटल व्योम rtw_joinbss_update_network(काष्ठा adapter *padapter, काष्ठा wlan_network *ptarget_wlan, काष्ठा wlan_network  *pnetwork)
अणु
	काष्ठा mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	काष्ठा wlan_network  *cur_network = &(pmlmepriv->cur_network);

	/*  why not use ptarget_wlan?? */
	स_नकल(&cur_network->network, &pnetwork->network, pnetwork->network.Length);
	/*  some IEs in pnetwork is wrong, so we should use ptarget_wlan IEs */
	cur_network->network.IELength = ptarget_wlan->network.IELength;
	स_नकल(&cur_network->network.IEs[0], &ptarget_wlan->network.IEs[0], MAX_IE_SZ);

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

			अगर (pmlmepriv->fw_state&WIFI_UNDER_WPS)
				pmlmepriv->fw_state = WIFI_STATION_STATE|WIFI_UNDER_WPS;
			अन्यथा
				pmlmepriv->fw_state = WIFI_STATION_STATE;

			अवरोध;
	हाल Ndis802_11IBSS:
			pmlmepriv->fw_state = WIFI_ADHOC_STATE;
			अवरोध;
	शेष:
			pmlmepriv->fw_state = WIFI_शून्य_STATE;
			अवरोध;
	पूर्ण

	rtw_update_protection(padapter, (cur_network->network.IEs) + माप(काष्ठा ndis_802_11_fix_ie),
									(cur_network->network.IELength));

	rtw_update_ht_cap(padapter, cur_network->network.IEs, cur_network->network.IELength, (u8) cur_network->network.Configuration.DSConfig);
पूर्ण

/* Notes: the function could be > passive_level (the same context as Rx tasklet) */
/* pnetwork : वापसs from rtw_joinbss_event_callback */
/* ptarget_wlan: found from scanned_queue */
/* अगर join_res > 0, क्रम (fw_state ==WIFI_STATION_STATE), we check अगर  "ptarget_sta" & "ptarget_wlan" exist. */
/* अगर join_res > 0, क्रम (fw_state ==WIFI_ADHOC_STATE), we only check अगर "ptarget_wlan" exist. */
/* अगर join_res > 0, update "cur_network->network" from "pnetwork->network" अगर (ptarget_wlan != शून्य). */
/*  */
/* define REJOIN */
व्योम rtw_joinbss_event_prehandle(काष्ठा adapter *adapter, u8 *pbuf)
अणु
	अटल u8 retry;
	काष्ठा sta_info *ptarget_sta = शून्य, *pcur_sta = शून्य;
	काष्ठा	sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा	mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	काष्ठा wlan_network	*pnetwork	= (काष्ठा wlan_network *)pbuf;
	काष्ठा wlan_network	*cur_network = &(pmlmepriv->cur_network);
	काष्ठा wlan_network	*pcur_wlan = शून्य, *ptarget_wlan = शून्य;
	अचिन्हित पूर्णांक		the_same_macaddr = false;

	rtw_get_encrypt_decrypt_from_registrypriv(adapter);

	the_same_macaddr = !स_भेद(pnetwork->network.MacAddress, cur_network->network.MacAddress, ETH_ALEN);

	pnetwork->network.Length = get_wlan_bssid_ex_sz(&pnetwork->network);
	अगर (pnetwork->network.Length > माप(काष्ठा wlan_bssid_ex))
		वापस;

	spin_lock_bh(&pmlmepriv->lock);

	pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 0;
	pmlmepriv->LinkDetectInfo.LowPowerTransitionCount = 0;

	अगर (pnetwork->join_res > 0) अणु
		spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
		retry = 0;
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
					अगर (pcur_sta)
						rtw_मुक्त_stainfo(adapter,  pcur_sta);

					ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, pnetwork->network.MacAddress);
					अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true) अणु
						अगर (ptarget_wlan)
							ptarget_wlan->fixed = true;
					पूर्ण
				पूर्ण

			पूर्ण अन्यथा अणु
				ptarget_wlan = _rtw_find_same_network(&pmlmepriv->scanned_queue, pnetwork);
				अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true) अणु
					अगर (ptarget_wlan)
						ptarget_wlan->fixed = true;
				पूर्ण
			पूर्ण

			/* s2. update cur_network */
			अगर (ptarget_wlan) अणु
				rtw_joinbss_update_network(adapter, ptarget_wlan, pnetwork);
			पूर्ण अन्यथा अणु
				netdev_dbg(adapter->pnetdev,
					   "Can't find ptarget_wlan when joinbss_event callback\n");
				spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
				जाओ ignore_joinbss_callback;
			पूर्ण

			/* s3. find ptarget_sta & update ptarget_sta after update cur_network only क्रम station mode */
			अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true) अणु
				ptarget_sta = rtw_joinbss_update_stainfo(adapter, pnetwork);
				अगर (!ptarget_sta) अणु
					spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
					जाओ ignore_joinbss_callback;
				पूर्ण
			पूर्ण

			/* s4. indicate connect */
			अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true) अणु
				pmlmepriv->cur_network_scanned = ptarget_wlan;
				rtw_indicate_connect(adapter);
			पूर्ण

			/* s5. Cancel assoc_समयr */
			del_समयr_sync(&pmlmepriv->assoc_समयr);

		पूर्ण अन्यथा अणु
			spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
			जाओ ignore_joinbss_callback;
		पूर्ण

		spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));

	पूर्ण अन्यथा अगर (pnetwork->join_res == -4) अणु
		rtw_reset_securitypriv(adapter);
		_set_समयr(&pmlmepriv->assoc_समयr, 1);

		/* rtw_मुक्त_assoc_resources(adapter, 1); */

		अगर ((check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) == true)
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

	पूर्ण अन्यथा अणु/* अगर join_res < 0 (join fails), then try again */

		#अगर_घोषित REJOIN
		res = _FAIL;
		अगर (retry < 2)
			res = rtw_select_and_join_from_scanned_queue(pmlmepriv);

		अगर (res == _SUCCESS) अणु
			/* extend समय of assoc_समयr */
			_set_समयr(&pmlmepriv->assoc_समयr, MAX_JOIN_TIMEOUT);
			retry++;
		पूर्ण अन्यथा अगर (res == 2) अणु/* there is no need to रुको क्रम join */
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
			rtw_indicate_connect(adapter);
		पूर्ण अन्यथा अणु
		#पूर्ण_अगर

			_set_समयr(&pmlmepriv->assoc_समयr, 1);
			/* rtw_मुक्त_assoc_resources(adapter, 1); */
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

		#अगर_घोषित REJOIN
			retry = 0;
		पूर्ण
		#पूर्ण_अगर
	पूर्ण

ignore_joinbss_callback:

	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

व्योम rtw_joinbss_event_callback(काष्ठा adapter *adapter, u8 *pbuf)
अणु
	काष्ठा wlan_network	*pnetwork	= (काष्ठा wlan_network *)pbuf;

	mlmeext_joinbss_event_callback(adapter, pnetwork->join_res);

	rtw_os_xmit_schedule(adapter);
पूर्ण

/* FOR STA, AP , AD-HOC mode */
व्योम rtw_sta_media_status_rpt(काष्ठा adapter *adapter, काष्ठा sta_info *psta, u32 mstatus)
अणु
	u16 media_status_rpt;

	अगर (!psta)
		वापस;

	media_status_rpt = (u16)((psta->mac_id<<8)|mstatus); /*   MACID|OPMODE:1 connect */
	rtw_hal_set_hwreg(adapter, HW_VAR_H2C_MEDIA_STATUS_RPT, (u8 *)&media_status_rpt);
पूर्ण

व्योम rtw_stassoc_event_callback(काष्ठा adapter *adapter, u8 *pbuf)
अणु
	काष्ठा sta_info *psta;
	काष्ठा mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	काष्ठा stassoc_event	*pstassoc	= (काष्ठा stassoc_event *)pbuf;
	काष्ठा wlan_network	*cur_network = &(pmlmepriv->cur_network);
	काष्ठा wlan_network	*ptarget_wlan = शून्य;

	अगर (rtw_access_ctrl(adapter, pstassoc->macaddr) == false)
		वापस;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		psta = rtw_get_stainfo(&adapter->stapriv, pstassoc->macaddr);
		अगर (psta) अणु
			u8 *passoc_req = शून्य;
			u32 assoc_req_len = 0;

			rtw_sta_media_status_rpt(adapter, psta, 1);

			ap_sta_info_defer_update(adapter, psta);

			/* report to upper layer */
			spin_lock_bh(&psta->lock);
			अगर (psta->passoc_req && psta->assoc_req_len > 0) अणु
				passoc_req = rtw_zदो_स्मृति(psta->assoc_req_len);
				अगर (passoc_req) अणु
					assoc_req_len = psta->assoc_req_len;
					स_नकल(passoc_req, psta->passoc_req, assoc_req_len);

					kमुक्त(psta->passoc_req);
					psta->passoc_req = शून्य;
					psta->assoc_req_len = 0;
				पूर्ण
			पूर्ण
			spin_unlock_bh(&psta->lock);

			अगर (passoc_req && assoc_req_len > 0) अणु
				rtw_cfg80211_indicate_sta_assoc(adapter, passoc_req, assoc_req_len);

				kमुक्त(passoc_req);
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	/* क्रम AD-HOC mode */
	psta = rtw_get_stainfo(&adapter->stapriv, pstassoc->macaddr);
	अगर (psta) अणु
		/* the sta have been in sta_info_queue => करो nothing */

		वापस; /* between drv has received this event beक्रमe and  fw have not yet to set key to CAM_ENTRY) */
	पूर्ण

	psta = rtw_alloc_stainfo(&adapter->stapriv, pstassoc->macaddr);
	अगर (!psta)
		वापस;

	/* to करो : init sta_info variable */
	psta->qos_option = 0;
	psta->mac_id = (uपूर्णांक)pstassoc->cam_id;
	/* psta->aid = (uपूर्णांक)pstassoc->cam_id; */

	/* क्रम ad-hoc mode */
	rtw_hal_set_odm_var(adapter, HAL_ODM_STA_INFO, psta, true);

	rtw_sta_media_status_rpt(adapter, psta, 1);

	अगर (adapter->securitypriv.करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X)
		psta->करोt118021XPrivacy = adapter->securitypriv.करोt11PrivacyAlgrthm;

	psta->ieee8021x_blocked = false;

	spin_lock_bh(&pmlmepriv->lock);

	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true)) अणु
		अगर (adapter->stapriv.asoc_sta_count == 2) अणु
			spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
			ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, cur_network->network.MacAddress);
			pmlmepriv->cur_network_scanned = ptarget_wlan;
			अगर (ptarget_wlan)
				ptarget_wlan->fixed = true;
			spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
			/*  a sta + bc/mc_stainfo (not Ibss_stainfo) */
			rtw_indicate_connect(adapter);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&pmlmepriv->lock);

	mlmeext_sta_add_event_callback(adapter, psta);
पूर्ण

व्योम rtw_stadel_event_callback(काष्ठा adapter *adapter, u8 *pbuf)
अणु
	पूर्णांक mac_id = (-1);
	काष्ठा sta_info *psta;
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा wlan_bssid_ex    *pdev_network = शून्य;
	u8 *pibss = शून्य;
	काष्ठा	mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	काष्ठा	stadel_event *pstadel	= (काष्ठा stadel_event *)pbuf;
	काष्ठा wlan_network *tgt_network = &(pmlmepriv->cur_network);
	काष्ठा mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	psta = rtw_get_stainfo(&adapter->stapriv, pstadel->macaddr);
	अगर (psta)
		mac_id = psta->mac_id;
	अन्यथा
		mac_id = pstadel->mac_id;

	अगर (mac_id >= 0) अणु
		u16 media_status;

		media_status = (mac_id<<8)|0; /*   MACID|OPMODE:0 means disconnect */
		/* क्रम STA, AP, ADHOC mode, report disconnect stauts to FW */
		rtw_hal_set_hwreg(adapter, HW_VAR_H2C_MEDIA_STATUS_RPT, (u8 *)&media_status);
	पूर्ण

	/* अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) */
	अगर ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)
		वापस;

	mlmeext_sta_del_event_callback(adapter);

	spin_lock_bh(&pmlmepriv->lock);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
		u16 reason = *((अचिन्हित लघु *)(pstadel->rsvd));
		bool roam = false;
		काष्ठा wlan_network *roam_target = शून्य;

		अगर (adapter->registrypriv.wअगरi_spec == 1) अणु
			roam = false;
		पूर्ण अन्यथा अगर (reason == WLAN_REASON_EXPIRATION_CHK && rtw_chk_roam_flags(adapter, RTW_ROAM_ON_EXPIRED)) अणु
			roam = true;
		पूर्ण अन्यथा अगर (reason == WLAN_REASON_ACTIVE_ROAM && rtw_chk_roam_flags(adapter, RTW_ROAM_ACTIVE)) अणु
			roam = true;
			roam_target = pmlmepriv->roam_network;
		पूर्ण

		अगर (roam) अणु
			अगर (rtw_to_roam(adapter) > 0)
				rtw_dec_to_roam(adapter); /* this stadel_event is caused by roaming, decrease to_roam */
			अन्यथा अगर (rtw_to_roam(adapter) == 0)
				rtw_set_to_roam(adapter, adapter->registrypriv.max_roaming_बार);
		पूर्ण अन्यथा अणु
			rtw_set_to_roam(adapter, 0);
		पूर्ण

		rtw_मुक्त_uc_swdec_pending_queue(adapter);

		rtw_मुक्त_assoc_resources(adapter, 1);
		rtw_indicate_disconnect(adapter);

		spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
		/*  हटाओ the network entry in scanned_queue */
		pwlan = rtw_find_network(&pmlmepriv->scanned_queue, tgt_network->network.MacAddress);
		अगर (pwlan) अणु
			pwlan->fixed = false;
			rtw_मुक्त_network_nolock(adapter, pwlan);
		पूर्ण
		spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));

		_rtw_roaming(adapter, roam_target);
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) ||
	      check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु

		rtw_मुक्त_stainfo(adapter,  psta);

		अगर (adapter->stapriv.asoc_sta_count == 1) अणु/* a sta + bc/mc_stainfo (not Ibss_stainfo) */
			u8 ret = _SUCCESS;
			/* rtw_indicate_disconnect(adapter);हटाओd@20091105 */
			spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
			/* मुक्त old ibss network */
			/* pwlan = rtw_find_network(&pmlmepriv->scanned_queue, pstadel->macaddr); */
			pwlan = rtw_find_network(&pmlmepriv->scanned_queue, tgt_network->network.MacAddress);
			अगर (pwlan) अणु
				pwlan->fixed = false;
				rtw_मुक्त_network_nolock(adapter, pwlan);
			पूर्ण
			spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
			/* re-create ibss */
			pdev_network = &(adapter->registrypriv.dev_network);
			pibss = adapter->registrypriv.dev_network.MacAddress;

			स_नकल(pdev_network, &tgt_network->network, get_wlan_bssid_ex_sz(&tgt_network->network));

			स_नकल(&pdev_network->Ssid, &pmlmepriv->assoc_ssid, माप(काष्ठा ndis_802_11_ssid));

			rtw_update_registrypriv_dev_network(adapter);

			rtw_generate_अक्रमom_ibss(pibss);

			अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
				set_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE);
				_clr_fwstate_(pmlmepriv, WIFI_ADHOC_STATE);
			पूर्ण

			ret = rtw_createbss_cmd(adapter);
			अगर (ret != _SUCCESS)
				जाओ unlock;
		पूर्ण

	पूर्ण

unlock:
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

व्योम rtw_cpwm_event_callback(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	काष्ठा reportpwrstate_parm *preportpwrstate;

	preportpwrstate = (काष्ठा reportpwrstate_parm *)pbuf;
	preportpwrstate->state |= (u8)(adapter_to_pwrctl(padapter)->cpwm_tog + 0x80);
	cpwm_पूर्णांक_hdl(padapter, preportpwrstate);
पूर्ण

व्योम rtw_wmm_event_callback(काष्ठा adapter *padapter, u8 *pbuf)
अणु
	WMMOnAssocRsp(padapter);
पूर्ण

/*
* _rtw_join_समयout_handler - Timeout/failure handler क्रम CMD JoinBss
* @adapter: poपूर्णांकer to काष्ठा adapter काष्ठाure
*/
व्योम _rtw_join_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter = from_समयr(adapter, t,
						  mlmepriv.assoc_समयr);
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;

	अगर (adapter->bDriverStopped || adapter->bSurpriseRemoved)
		वापस;

	spin_lock_bh(&pmlmepriv->lock);

	अगर (rtw_to_roam(adapter) > 0) अणु /* join समयout caused by roaming */
		जबतक (1) अणु
			rtw_dec_to_roam(adapter);
			अगर (rtw_to_roam(adapter) != 0) अणु /* try another */
				पूर्णांक करो_join_r;

				करो_join_r = rtw_करो_join(adapter);
				अगर (_SUCCESS != करो_join_r) अणु
					जारी;
				पूर्ण
				अवरोध;
			पूर्ण अन्यथा अणु
				rtw_indicate_disconnect(adapter);
				अवरोध;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		rtw_indicate_disconnect(adapter);
		मुक्त_scanqueue(pmlmepriv);/*  */

		/* indicate disconnect क्रम the हाल that join_समयout and check_fwstate != FW_LINKED */
		rtw_cfg80211_indicate_disconnect(adapter);

	पूर्ण

	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

/*
* rtw_scan_समयout_handler - Timeout/Failure handler क्रम CMD SiteSurvey
* @adapter: poपूर्णांकer to काष्ठा adapter काष्ठाure
*/
व्योम rtw_scan_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter = from_समयr(adapter, t,
						  mlmepriv.scan_to_समयr);
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;

	spin_lock_bh(&pmlmepriv->lock);

	_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);

	spin_unlock_bh(&pmlmepriv->lock);

	rtw_indicate_scan_करोne(adapter, true);
पूर्ण

व्योम rtw_mlme_reset_स्वतः_scan_पूर्णांक(काष्ठा adapter *adapter)
अणु
	काष्ठा mlme_priv *mlme = &adapter->mlmepriv;
	काष्ठा mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर (pmlmeinfo->VHT_enable) /* disable स्वतः scan when connect to 11AC AP */
		mlme->स्वतः_scan_पूर्णांक_ms = 0;
	अन्यथा अगर (adapter->registrypriv.wअगरi_spec && is_client_associated_to_ap(adapter) == true)
		mlme->स्वतः_scan_पूर्णांक_ms = 60*1000;
	अन्यथा अगर (rtw_chk_roam_flags(adapter, RTW_ROAM_ACTIVE)) अणु
		अगर (check_fwstate(mlme, WIFI_STATION_STATE) && check_fwstate(mlme, _FW_LINKED))
			mlme->स्वतः_scan_पूर्णांक_ms = mlme->roam_scan_पूर्णांक_ms;
	पूर्ण अन्यथा
		mlme->स्वतः_scan_पूर्णांक_ms = 0; /* disabled */
पूर्ण

अटल व्योम rtw_स्वतः_scan_handler(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	rtw_mlme_reset_स्वतः_scan_पूर्णांक(padapter);

	अगर (pmlmepriv->स्वतः_scan_पूर्णांक_ms != 0
		&& jअगरfies_to_msecs(jअगरfies - pmlmepriv->scan_start_समय) > pmlmepriv->स्वतः_scan_पूर्णांक_ms) अणु

		अगर (!padapter->registrypriv.wअगरi_spec) अणु
			अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING) == true)
				जाओ निकास;

			अगर (pmlmepriv->LinkDetectInfo.bBusyTraffic)
				जाओ निकास;
		पूर्ण

		rtw_set_802_11_bssid_list_scan(padapter, शून्य, 0);
	पूर्ण

निकास:
	वापस;
पूर्ण

व्योम rtw_dynamic_check_समयr_handler(काष्ठा adapter *adapter)
अणु
	अगर (!adapter)
		वापस;

	अगर (!adapter->hw_init_completed)
		वापस;

	अगर (adapter->bDriverStopped || adapter->bSurpriseRemoved)
		वापस;

	अगर (adapter->net_बंदd)
		वापस;

	अगर ((adapter_to_pwrctl(adapter)->fw_current_in_ps_mode)
		&& !(hal_btcoex_IsBtControlLps(adapter))
		) अणु
		u8 bEnterPS;

		linked_status_chk(adapter);

		bEnterPS = traffic_status_watchकरोg(adapter, 1);
		अगर (bEnterPS) अणु
			/* rtw_lps_ctrl_wk_cmd(adapter, LPS_CTRL_ENTER, 1); */
			rtw_hal_dm_watchकरोg_in_lps(adapter);
		पूर्ण अन्यथा अणु
			/* call rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_LEAVE, 1) in traffic_status_watchकरोg() */
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (is_primary_adapter(adapter))
			rtw_dynamic_chk_wk_cmd(adapter);
	पूर्ण

	/* स्वतः site survey */
	rtw_स्वतः_scan_handler(adapter);
पूर्ण

अंतरभूत bool rtw_is_scan_deny(काष्ठा adapter *adapter)
अणु
	काष्ठा mlme_priv *mlmepriv = &adapter->mlmepriv;

	वापस (atomic_पढ़ो(&mlmepriv->set_scan_deny) != 0) ? true : false;
पूर्ण

अंतरभूत व्योम rtw_clear_scan_deny(काष्ठा adapter *adapter)
अणु
	काष्ठा mlme_priv *mlmepriv = &adapter->mlmepriv;

	atomic_set(&mlmepriv->set_scan_deny, 0);
पूर्ण

व्योम rtw_set_scan_deny(काष्ठा adapter *adapter, u32 ms)
अणु
	काष्ठा mlme_priv *mlmepriv = &adapter->mlmepriv;

	atomic_set(&mlmepriv->set_scan_deny, 1);
	_set_समयr(&mlmepriv->set_scan_deny_समयr, ms);
पूर्ण

/*
* Select a new roaming candidate from the original @param candidate and @param competitor
* @वापस true: candidate is updated
* @वापस false: candidate is not updated
*/
अटल पूर्णांक rtw_check_roaming_candidate(काष्ठा mlme_priv *mlme
	, काष्ठा wlan_network **candidate, काष्ठा wlan_network *competitor)
अणु
	पूर्णांक updated = false;
	काष्ठा adapter *adapter = container_of(mlme, काष्ठा adapter, mlmepriv);

	अगर (is_same_ess(&competitor->network, &mlme->cur_network.network) == false)
		जाओ निकास;

	अगर (rtw_is_desired_network(adapter, competitor) == false)
		जाओ निकास;

	/* got specअगरic addr to roam */
	अगर (!is_zero_mac_addr(mlme->roam_tgt_addr)) अणु
		अगर (!स_भेद(mlme->roam_tgt_addr, competitor->network.MacAddress, ETH_ALEN))
			जाओ update;
		अन्यथा
			जाओ निकास;
	पूर्ण
	अगर (jअगरfies_to_msecs(jअगरfies - competitor->last_scanned) >= mlme->roam_scanr_exp_ms)
		जाओ निकास;

	अगर (competitor->network.Rssi - mlme->cur_network_scanned->network.Rssi < mlme->roam_rssi_dअगरf_th)
		जाओ निकास;

	अगर (*candidate && (*candidate)->network.Rssi >= competitor->network.Rssi)
		जाओ निकास;

update:
	*candidate = competitor;
	updated = true;

निकास:
	वापस updated;
पूर्ण

पूर्णांक rtw_select_roaming_candidate(काष्ठा mlme_priv *mlme)
अणु
	पूर्णांक ret = _FAIL;
	काष्ठा list_head	*phead;
	काष्ठा __queue	*queue	= &(mlme->scanned_queue);
	काष्ठा	wlan_network	*pnetwork = शून्य;
	काष्ठा	wlan_network	*candidate = शून्य;

	अगर (!mlme->cur_network_scanned) अणु
		rtw_warn_on(1);
		वापस ret;
	पूर्ण

	spin_lock_bh(&(mlme->scanned_queue.lock));
	phead = get_list_head(queue);

	mlme->pscanned = get_next(phead);

	जबतक (phead != mlme->pscanned) अणु

		pnetwork = container_of(mlme->pscanned, काष्ठा wlan_network, list);
		अगर (!pnetwork) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		mlme->pscanned = get_next(mlme->pscanned);

		rtw_check_roaming_candidate(mlme, &candidate, pnetwork);

	पूर्ण

	अगर (!candidate) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		mlme->roam_network = candidate;

		अगर (!स_भेद(candidate->network.MacAddress, mlme->roam_tgt_addr, ETH_ALEN))
			eth_zero_addr(mlme->roam_tgt_addr);
	पूर्ण

	ret = _SUCCESS;
निकास:
	spin_unlock_bh(&(mlme->scanned_queue.lock));

	वापस ret;
पूर्ण

/*
* Select a new join candidate from the original @param candidate and @param competitor
* @वापस true: candidate is updated
* @वापस false: candidate is not updated
*/
अटल पूर्णांक rtw_check_join_candidate(काष्ठा mlme_priv *mlme
	, काष्ठा wlan_network **candidate, काष्ठा wlan_network *competitor)
अणु
	पूर्णांक updated = false;
	काष्ठा adapter *adapter = container_of(mlme, काष्ठा adapter, mlmepriv);

	/* check bssid, अगर needed */
	अगर (mlme->assoc_by_bssid) अणु
		अगर (स_भेद(competitor->network.MacAddress, mlme->assoc_bssid, ETH_ALEN))
			जाओ निकास;
	पूर्ण

	/* check ssid, अगर needed */
	अगर (mlme->assoc_ssid.Ssid[0] && mlme->assoc_ssid.SsidLength) अणु
		अगर (competitor->network.Ssid.SsidLength != mlme->assoc_ssid.SsidLength
			|| स_भेद(competitor->network.Ssid.Ssid, mlme->assoc_ssid.Ssid, mlme->assoc_ssid.SsidLength)
		)
			जाओ निकास;
	पूर्ण

	अगर (rtw_is_desired_network(adapter, competitor)  == false)
		जाओ निकास;

	अगर (rtw_to_roam(adapter) > 0) अणु
		अगर (jअगरfies_to_msecs(jअगरfies - competitor->last_scanned) >= mlme->roam_scanr_exp_ms
			|| is_same_ess(&competitor->network, &mlme->cur_network.network) == false
		)
			जाओ निकास;
	पूर्ण

	अगर (*candidate == शून्य || (*candidate)->network.Rssi < competitor->network.Rssi) अणु
		*candidate = competitor;
		updated = true;
	पूर्ण

निकास:
	वापस updated;
पूर्ण

/*
Calling context:
The caller of the sub-routine will be in critical section...
The caller must hold the following spinlock
pmlmepriv->lock
*/

पूर्णांक rtw_select_and_join_from_scanned_queue(काष्ठा mlme_priv *pmlmepriv)
अणु
	पूर्णांक ret;
	काष्ठा list_head	*phead;
	काष्ठा adapter *adapter;
	काष्ठा __queue	*queue	= &(pmlmepriv->scanned_queue);
	काष्ठा	wlan_network	*pnetwork = शून्य;
	काष्ठा	wlan_network	*candidate = शून्य;

	adapter = (काष्ठा adapter *)pmlmepriv->nic_hdl;

	spin_lock_bh(&(pmlmepriv->scanned_queue.lock));

	अगर (pmlmepriv->roam_network) अणु
		candidate = pmlmepriv->roam_network;
		pmlmepriv->roam_network = शून्य;
		जाओ candidate_exist;
	पूर्ण

	phead = get_list_head(queue);
	pmlmepriv->pscanned = get_next(phead);

	जबतक (phead != pmlmepriv->pscanned) अणु

		pnetwork = container_of(pmlmepriv->pscanned, काष्ठा wlan_network, list);
		अगर (!pnetwork) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		pmlmepriv->pscanned = get_next(pmlmepriv->pscanned);

		rtw_check_join_candidate(pmlmepriv, &candidate, pnetwork);

	पूर्ण

	अगर (!candidate) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		जाओ candidate_exist;
	पूर्ण

candidate_exist:

	/*  check क्रम situation of  _FW_LINKED */
	अगर (check_fwstate(pmlmepriv, _FW_LINKED) == true) अणु
		rtw_disassoc_cmd(adapter, 0, true);
		rtw_indicate_disconnect(adapter);
		rtw_मुक्त_assoc_resources(adapter, 0);
	पूर्ण

	set_fwstate(pmlmepriv, _FW_UNDER_LINKING);
	ret = rtw_joinbss_cmd(adapter, candidate);

निकास:
	spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
	वापस ret;
पूर्ण

चिन्हित पूर्णांक rtw_set_auth(काष्ठा adapter *adapter, काष्ठा security_priv *psecuritypriv)
अणु
	काष्ठा	cmd_obj *pcmd;
	काष्ठा	setauth_parm *psetauthparm;
	काष्ठा	cmd_priv *pcmdpriv = &(adapter->cmdpriv);
	चिन्हित पूर्णांक		res = _SUCCESS;

	pcmd = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
	अगर (!pcmd) अणु
		res = _FAIL;  /* try again */
		जाओ निकास;
	पूर्ण

	psetauthparm = rtw_zदो_स्मृति(माप(काष्ठा setauth_parm));
	अगर (!psetauthparm) अणु
		kमुक्त(pcmd);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	psetauthparm->mode = (अचिन्हित अक्षर)psecuritypriv->करोt11AuthAlgrthm;

	pcmd->cmdcode = _SetAuth_CMD_;
	pcmd->parmbuf = (अचिन्हित अक्षर *)psetauthparm;
	pcmd->cmdsz =  (माप(काष्ठा setauth_parm));
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;

	INIT_LIST_HEAD(&pcmd->list);

	res = rtw_enqueue_cmd(pcmdpriv, pcmd);

निकास:
	वापस res;
पूर्ण

चिन्हित पूर्णांक rtw_set_key(काष्ठा adapter *adapter, काष्ठा security_priv *psecuritypriv, चिन्हित पूर्णांक keyid, u8 set_tx, bool enqueue)
अणु
	u8 keylen;
	काष्ठा cmd_obj		*pcmd;
	काष्ठा setkey_parm	*psetkeyparm;
	काष्ठा cmd_priv 	*pcmdpriv = &(adapter->cmdpriv);
	चिन्हित पूर्णांक	res = _SUCCESS;

	psetkeyparm = rtw_zदो_स्मृति(माप(काष्ठा setkey_parm));
	अगर (!psetkeyparm) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (psecuritypriv->करोt11AuthAlgrthm == करोt11AuthAlgrthm_8021X)
		psetkeyparm->algorithm = (अचिन्हित अक्षर)psecuritypriv->करोt118021XGrpPrivacy;
	अन्यथा
		psetkeyparm->algorithm = (u8)psecuritypriv->करोt11PrivacyAlgrthm;

	psetkeyparm->keyid = (u8)keyid;/* 0~3 */
	psetkeyparm->set_tx = set_tx;
	अगर (is_wep_enc(psetkeyparm->algorithm))
		adapter->securitypriv.key_mask |= BIT(psetkeyparm->keyid);

	चयन (psetkeyparm->algorithm) अणु

	हाल _WEP40_:
		keylen = 5;
		स_नकल(&(psetkeyparm->key[0]), &(psecuritypriv->करोt11DefKey[keyid].skey[0]), keylen);
		अवरोध;
	हाल _WEP104_:
		keylen = 13;
		स_नकल(&(psetkeyparm->key[0]), &(psecuritypriv->करोt11DefKey[keyid].skey[0]), keylen);
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
		res = _FAIL;
		kमुक्त(psetkeyparm);
		जाओ निकास;
	पूर्ण

	अगर (enqueue) अणु
		pcmd = rtw_zदो_स्मृति(माप(काष्ठा cmd_obj));
		अगर (!pcmd) अणु
			kमुक्त(psetkeyparm);
			res = _FAIL;  /* try again */
			जाओ निकास;
		पूर्ण

		pcmd->cmdcode = _SetKey_CMD_;
		pcmd->parmbuf = (u8 *)psetkeyparm;
		pcmd->cmdsz =  (माप(काष्ठा setkey_parm));
		pcmd->rsp = शून्य;
		pcmd->rspsz = 0;

		INIT_LIST_HEAD(&pcmd->list);

		res = rtw_enqueue_cmd(pcmdpriv, pcmd);
	पूर्ण अन्यथा अणु
		setkey_hdl(adapter, (u8 *)psetkeyparm);
		kमुक्त(psetkeyparm);
	पूर्ण
निकास:
	वापस res;
पूर्ण

/* adjust IEs क्रम rtw_joinbss_cmd in WMM */
पूर्णांक rtw_reकाष्ठा_wmm_ie(काष्ठा adapter *adapter, u8 *in_ie, u8 *out_ie, uपूर्णांक in_len, uपूर्णांक initial_out_len)
अणु
	अचिन्हित	पूर्णांक ielength = 0;
	अचिन्हित पूर्णांक i, j;

	i = 12; /* after the fixed IE */
	जबतक (i < in_len) अणु
		ielength = initial_out_len;

		अगर (in_ie[i] == 0xDD && in_ie[i+2] == 0x00 && in_ie[i+3] == 0x50  && in_ie[i+4] == 0xF2 && in_ie[i+5] == 0x02 && i+5 < in_len) अणु /* WMM element ID and OUI */
			क्रम (j = i; j < i + 9; j++) अणु
					out_ie[ielength] = in_ie[j];
					ielength++;
			पूर्ण
			out_ie[initial_out_len + 1] = 0x07;
			out_ie[initial_out_len + 6] = 0x00;
			out_ie[initial_out_len + 8] = 0x00;

			अवरोध;
		पूर्ण

		i += (in_ie[i+1]+2); /*  to the next IE element */
	पूर्ण

	वापस ielength;

पूर्ण

/*  */
/*  Ported from 8185: IsInPreAuthKeyList(). (Renamed from SecIsInPreAuthKeyList(), 2006-10-13.) */
/*  Added by Annie, 2006-05-07. */
/*  */
/*  Search by BSSID, */
/*  Return Value: */
/* 		-1		:अगर there is no pre-auth key in the  table */
/* 		>= 0		:अगर there is pre-auth key, and   वापस the entry id */
/*  */
/*  */

अटल पूर्णांक SecIsInPMKIDList(काष्ठा adapter *Adapter, u8 *bssid)
अणु
	काष्ठा security_priv *psecuritypriv = &Adapter->securitypriv;
	पूर्णांक i = 0;

	करो अणु
		अगर ((psecuritypriv->PMKIDList[i].bUsed) &&
				(!स_भेद(psecuritypriv->PMKIDList[i].Bssid, bssid, ETH_ALEN))) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			i++;
			/* जारी; */
		पूर्ण

	पूर्ण जबतक (i < NUM_PMKID_CACHE);

	अगर (i == NUM_PMKID_CACHE) अणु
		i = -1;/*  Could not find. */
	पूर्ण अन्यथा अणु
		/*  There is one Pre-Authentication Key क्रम the specअगरic BSSID. */
	पूर्ण

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

चिन्हित पूर्णांक rtw_reकाष्ठा_sec_ie(काष्ठा adapter *adapter, u8 *in_ie, u8 *out_ie, uपूर्णांक in_len)
अणु
	u8 authmode = 0x0;
	uपूर्णांक	ielength;
	पूर्णांक iEntry;

	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;
	uपूर्णांक	ndisauthmode = psecuritypriv->ndisauthtype;

	/* copy fixed ie only */
	स_नकल(out_ie, in_ie, 12);
	ielength = 12;
	अगर ((ndisauthmode == Ndis802_11AuthModeWPA) || (ndisauthmode == Ndis802_11AuthModeWPAPSK))
			authmode = WLAN_EID_VENDOR_SPECIFIC;
	अगर ((ndisauthmode == Ndis802_11AuthModeWPA2) || (ndisauthmode == Ndis802_11AuthModeWPA2PSK))
			authmode = WLAN_EID_RSN;

	अगर (check_fwstate(pmlmepriv, WIFI_UNDER_WPS)) अणु
		स_नकल(out_ie+ielength, psecuritypriv->wps_ie, psecuritypriv->wps_ie_len);

		ielength += psecuritypriv->wps_ie_len;
	पूर्ण अन्यथा अगर ((authmode == WLAN_EID_VENDOR_SPECIFIC) || (authmode == WLAN_EID_RSN)) अणु
		/* copy RSN or SSN */
		स_नकल(&out_ie[ielength], &psecuritypriv->supplicant_ie[0], psecuritypriv->supplicant_ie[1]+2);
		/* debug क्रम CONFIG_IEEE80211W
		अणु
			पूर्णांक jj;
			prपूर्णांकk("supplicant_ie_length =%d &&&&&&&&&&&&&&&&&&&\n", psecuritypriv->supplicant_ie[1]+2);
			क्रम (jj = 0; jj < psecuritypriv->supplicant_ie[1]+2; jj++)
				prपूर्णांकk(" %02x ", psecuritypriv->supplicant_ie[jj]);
			prपूर्णांकk("\n");
		पूर्ण*/
		ielength += psecuritypriv->supplicant_ie[1]+2;
		rtw_report_sec_ie(adapter, authmode, psecuritypriv->supplicant_ie);
	पूर्ण

	iEntry = SecIsInPMKIDList(adapter, pmlmepriv->assoc_bssid);
	अगर (iEntry < 0) अणु
		वापस ielength;
	पूर्ण अन्यथा अणु
		अगर (authmode == WLAN_EID_RSN)
			ielength = rtw_append_pmkid(adapter, iEntry, out_ie, ielength);
	पूर्ण
	वापस ielength;
पूर्ण

व्योम rtw_init_registrypriv_dev_network(काष्ठा adapter *adapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &adapter->registrypriv;
	काष्ठा eeprom_priv *peepriv = &adapter->eeprompriv;
	काष्ठा wlan_bssid_ex    *pdev_network = &pregistrypriv->dev_network;
	u8 *myhwaddr = myid(peepriv);

	स_नकल(pdev_network->MacAddress, myhwaddr, ETH_ALEN);

	स_नकल(&pdev_network->Ssid, &pregistrypriv->ssid, माप(काष्ठा ndis_802_11_ssid));

	pdev_network->Configuration.Length = माप(काष्ठा ndis_802_11_conf);
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
	काष्ठा wlan_bssid_ex    *pdev_network = &pregistrypriv->dev_network;
	काष्ठा	security_priv *psecuritypriv = &adapter->securitypriv;
	काष्ठा	wlan_network	*cur_network = &adapter->mlmepriv.cur_network;
	/* काष्ठा	xmit_priv *pxmitpriv = &adapter->xmitpriv; */

	pdev_network->Privacy = (psecuritypriv->करोt11PrivacyAlgrthm > 0 ? 1 : 0) ; /*  adhoc no 802.1x */

	pdev_network->Rssi = 0;

	चयन (pregistrypriv->wireless_mode) अणु
	हाल WIRELESS_11B:
		pdev_network->NetworkTypeInUse = (Ndis802_11DS);
		अवरोध;
	हाल WIRELESS_11G:
	हाल WIRELESS_11BG:
	हाल WIRELESS_11_24N:
	हाल WIRELESS_11G_24N:
	हाल WIRELESS_11BG_24N:
		pdev_network->NetworkTypeInUse = (Ndis802_11OFDM24);
		अवरोध;
	हाल WIRELESS_11A:
	हाल WIRELESS_11A_5N:
		pdev_network->NetworkTypeInUse = (Ndis802_11OFDM5);
		अवरोध;
	हाल WIRELESS_11ABGN:
		अगर (pregistrypriv->channel > 14)
			pdev_network->NetworkTypeInUse = (Ndis802_11OFDM5);
		अन्यथा
			pdev_network->NetworkTypeInUse = (Ndis802_11OFDM24);
		अवरोध;
	शेष:
		/*  TODO */
		अवरोध;
	पूर्ण

	pdev_network->Configuration.DSConfig = (pregistrypriv->channel);

	अगर (cur_network->network.Infraकाष्ठाureMode == Ndis802_11IBSS)
		pdev_network->Configuration.ATIMWinकरोw = (0);

	pdev_network->Infraकाष्ठाureMode = (cur_network->network.Infraकाष्ठाureMode);

	/*  1. Supported rates */
	/*  2. IE */

	/* rtw_set_supported_rate(pdev_network->SupportedRates, pregistrypriv->wireless_mode) ;  will be called in rtw_generate_ie */
	sz = rtw_generate_ie(pregistrypriv);

	pdev_network->IELength = sz;

	pdev_network->Length = get_wlan_bssid_ex_sz((काष्ठा wlan_bssid_ex  *)pdev_network);

	/* notes: translate IELength & Length after assign the Length to cmdsz in createbss_cmd(); */
	/* pdev_network->IELength = cpu_to_le32(sz); */
पूर्ण

व्योम rtw_get_encrypt_decrypt_from_registrypriv(काष्ठा adapter *adapter)
अणु
पूर्ण

/* the function is at passive_level */
व्योम rtw_joinbss_reset(काष्ठा adapter *padapter)
अणु
	u8 threshold;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	काष्ठा ht_priv 	*phtpriv = &pmlmepriv->htpriv;

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

व्योम rtw_ht_use_शेष_setting(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv 	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv 	*phtpriv = &pmlmepriv->htpriv;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	bool		bHwLDPCSupport = false, bHwSTBCSupport = false;
	bool		bHwSupportBeamक्रमmer = false, bHwSupportBeamक्रमmee = false;

	अगर (pregistrypriv->wअगरi_spec)
		phtpriv->bss_coexist = 1;
	अन्यथा
		phtpriv->bss_coexist = 0;

	phtpriv->sgi_40m = TEST_FLAG(pregistrypriv->लघु_gi, BIT1) ? true : false;
	phtpriv->sgi_20m = TEST_FLAG(pregistrypriv->लघु_gi, BIT0) ? true : false;

	/*  LDPC support */
	rtw_hal_get_def_var(padapter, HAL_DEF_RX_LDPC, (u8 *)&bHwLDPCSupport);
	CLEAR_FLAGS(phtpriv->ldpc_cap);
	अगर (bHwLDPCSupport) अणु
		अगर (TEST_FLAG(pregistrypriv->ldpc_cap, BIT4))
			SET_FLAG(phtpriv->ldpc_cap, LDPC_HT_ENABLE_RX);
	पूर्ण
	rtw_hal_get_def_var(padapter, HAL_DEF_TX_LDPC, (u8 *)&bHwLDPCSupport);
	अगर (bHwLDPCSupport) अणु
		अगर (TEST_FLAG(pregistrypriv->ldpc_cap, BIT5))
			SET_FLAG(phtpriv->ldpc_cap, LDPC_HT_ENABLE_TX);
	पूर्ण

	/*  STBC */
	rtw_hal_get_def_var(padapter, HAL_DEF_TX_STBC, (u8 *)&bHwSTBCSupport);
	CLEAR_FLAGS(phtpriv->stbc_cap);
	अगर (bHwSTBCSupport) अणु
		अगर (TEST_FLAG(pregistrypriv->stbc_cap, BIT5))
			SET_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_TX);
	पूर्ण
	rtw_hal_get_def_var(padapter, HAL_DEF_RX_STBC, (u8 *)&bHwSTBCSupport);
	अगर (bHwSTBCSupport) अणु
		अगर (TEST_FLAG(pregistrypriv->stbc_cap, BIT4))
			SET_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_RX);
	पूर्ण

	/*  Beamक्रमming setting */
	rtw_hal_get_def_var(padapter, HAL_DEF_EXPLICIT_BEAMFORMER, (u8 *)&bHwSupportBeamक्रमmer);
	rtw_hal_get_def_var(padapter, HAL_DEF_EXPLICIT_BEAMFORMEE, (u8 *)&bHwSupportBeamक्रमmee);
	CLEAR_FLAGS(phtpriv->beamक्रमm_cap);
	अगर (TEST_FLAG(pregistrypriv->beamक्रमm_cap, BIT4) && bHwSupportBeamक्रमmer)
		SET_FLAG(phtpriv->beamक्रमm_cap, BEAMFORMING_HT_BEAMFORMER_ENABLE);

	अगर (TEST_FLAG(pregistrypriv->beamक्रमm_cap, BIT5) && bHwSupportBeamक्रमmee)
		SET_FLAG(phtpriv->beamक्रमm_cap, BEAMFORMING_HT_BEAMFORMEE_ENABLE);
पूर्ण

व्योम rtw_build_wmm_ie_ht(काष्ठा adapter *padapter, u8 *out_ie, uपूर्णांक *pout_len)
अणु
	अचिन्हित अक्षर WMM_IE[] = अणु0x00, 0x50, 0xf2, 0x02, 0x00, 0x01, 0x00पूर्ण;
	पूर्णांक out_len;
	u8 *pframe;

	अगर (padapter->mlmepriv.qospriv.qos_option == 0) अणु
		out_len = *pout_len;
		pframe = rtw_set_ie(out_ie+out_len, WLAN_EID_VENDOR_SPECIFIC,
							_WMM_IE_Length_, WMM_IE, pout_len);

		padapter->mlmepriv.qospriv.qos_option = 1;
	पूर्ण
पूर्ण

/* the function is >= passive_level */
अचिन्हित पूर्णांक rtw_reकाष्ठाure_ht_ie(काष्ठा adapter *padapter, u8 *in_ie, u8 *out_ie, uपूर्णांक in_len, uपूर्णांक *pout_len, u8 channel)
अणु
	u32 ielen, out_len;
	क्रमागत ieee80211_max_ampdu_length_exp max_rx_ampdu_factor;
	अचिन्हित अक्षर *p, *pframe;
	काष्ठा ieee80211_ht_cap ht_capie;
	u8 cbw40_enable = 0, stbc_rx_enable = 0, rf_type = 0, operation_bw = 0;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv 	*phtpriv = &pmlmepriv->htpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	phtpriv->ht_option = false;

	out_len = *pout_len;

	स_रखो(&ht_capie, 0, माप(काष्ठा ieee80211_ht_cap));

	ht_capie.cap_info = cpu_to_le16(IEEE80211_HT_CAP_DSSSCCK40);

	अगर (phtpriv->sgi_20m)
		ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_SGI_20);

	/* Get HT BW */
	अगर (!in_ie) अणु
		/* TDLS: TODO 20/40 issue */
		अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
			operation_bw = padapter->mlmeextpriv.cur_bwmode;
			अगर (operation_bw > CHANNEL_WIDTH_40)
				operation_bw = CHANNEL_WIDTH_40;
		पूर्ण अन्यथा
			/* TDLS: TODO 40? */
			operation_bw = CHANNEL_WIDTH_40;
	पूर्ण अन्यथा अणु
		p = rtw_get_ie(in_ie, WLAN_EID_HT_OPERATION, &ielen, in_len);
		अगर (p && (ielen == माप(काष्ठा ieee80211_ht_addt_info))) अणु
			काष्ठा HT_info_element *pht_info = (काष्ठा HT_info_element *)(p+2);

			अगर (pht_info->infos[0] & BIT(2)) अणु
				चयन (pht_info->infos[0] & 0x3) अणु
				हाल 1:
				हाल 3:
					operation_bw = CHANNEL_WIDTH_40;
					अवरोध;
				शेष:
					operation_bw = CHANNEL_WIDTH_20;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				operation_bw = CHANNEL_WIDTH_20;
			पूर्ण
		पूर्ण
	पूर्ण

	/* to disable 40M Hz support जबतक gd_bw_40MHz_en = 0 */
	अगर (channel > 14) अणु
		अगर ((pregistrypriv->bw_mode & 0xf0) > 0)
			cbw40_enable = 1;
	पूर्ण अन्यथा अणु
		अगर ((pregistrypriv->bw_mode & 0x0f) > 0)
			cbw40_enable = 1;
	पूर्ण

	अगर ((cbw40_enable == 1) && (operation_bw == CHANNEL_WIDTH_40)) अणु
		ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH);
		अगर (phtpriv->sgi_40m)
			ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_SGI_40);
	पूर्ण

	अगर (TEST_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_TX))
		ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_TX_STBC);

	/* toकरो: disable SM घातer save mode */
	ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_SM_PS);

	अगर (TEST_FLAG(phtpriv->stbc_cap, STBC_HT_ENABLE_RX)) अणु
		अगर ((channel <= 14 && pregistrypriv->rx_stbc == 0x1) ||	/* enable क्रम 2.4GHz */
			(pregistrypriv->wअगरi_spec == 1))
			stbc_rx_enable = 1;
	पूर्ण

	/* fill शेष supported_mcs_set */
	स_नकल(ht_capie.mcs.rx_mask, pmlmeext->शेष_supported_mcs_set, 16);

	/* update शेष supported_mcs_set */
	rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));

	चयन (rf_type) अणु
	हाल RF_1T1R:
		अगर (stbc_rx_enable)
			ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_RX_STBC_1R);/* RX STBC One spatial stream */

		set_mcs_rate_by_mask(ht_capie.mcs.rx_mask, MCS_RATE_1R);
		अवरोध;

	हाल RF_2T2R:
	हाल RF_1T2R:
	शेष:
		अगर (stbc_rx_enable)
			ht_capie.cap_info |= cpu_to_le16(IEEE80211_HT_CAP_RX_STBC_2R);/* RX STBC two spatial stream */

		set_mcs_rate_by_mask(ht_capie.mcs.rx_mask, MCS_RATE_2R);
		अवरोध;
	पूर्ण

	अणु
		u32 rx_packet_offset, max_recvbuf_sz;

		rtw_hal_get_def_var(padapter, HAL_DEF_RX_PACKET_OFFSET, &rx_packet_offset);
		rtw_hal_get_def_var(padapter, HAL_DEF_MAX_RECVBUF_SZ, &max_recvbuf_sz);
	पूर्ण

	अगर (padapter->driver_rx_ampdu_factor != 0xFF)
		max_rx_ampdu_factor =
		  (क्रमागत ieee80211_max_ampdu_length_exp)padapter->driver_rx_ampdu_factor;
	अन्यथा
		rtw_hal_get_def_var(padapter, HW_VAR_MAX_RX_AMPDU_FACTOR,
				    &max_rx_ampdu_factor);

	/* rtw_hal_get_def_var(padapter, HW_VAR_MAX_RX_AMPDU_FACTOR, &max_rx_ampdu_factor); */
	ht_capie.ampdu_params_info = (max_rx_ampdu_factor&0x03);

	अगर (padapter->securitypriv.करोt11PrivacyAlgrthm == _AES_)
		ht_capie.ampdu_params_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY&(0x07<<2));
	अन्यथा
		ht_capie.ampdu_params_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY&0x00);

	pframe = rtw_set_ie(out_ie+out_len, WLAN_EID_HT_CAPABILITY,
						माप(काष्ठा ieee80211_ht_cap), (अचिन्हित अक्षर *)&ht_capie, pout_len);

	phtpriv->ht_option = true;

	अगर (in_ie) अणु
		p = rtw_get_ie(in_ie, WLAN_EID_HT_OPERATION, &ielen, in_len);
		अगर (p && (ielen == माप(काष्ठा ieee80211_ht_addt_info))) अणु
			out_len = *pout_len;
			pframe = rtw_set_ie(out_ie+out_len, WLAN_EID_HT_OPERATION, ielen, p+2, pout_len);
		पूर्ण
	पूर्ण

	वापस phtpriv->ht_option;

पूर्ण

/* the function is > passive_level (in critical_section) */
व्योम rtw_update_ht_cap(काष्ठा adapter *padapter, u8 *pie, uपूर्णांक ie_len, u8 channel)
अणु
	u8 *p, max_ampdu_sz;
	पूर्णांक len;
	/* काष्ठा sta_info *bmc_sta, *psta; */
	काष्ठा ieee80211_ht_cap *pht_capie;
	काष्ठा ieee80211_ht_addt_info *pht_addtinfo;
	/* काष्ठा recv_reorder_ctrl *preorder_ctrl; */
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv 	*phtpriv = &pmlmepriv->htpriv;
	/* काष्ठा recv_priv *precvpriv = &padapter->recvpriv; */
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	/* काष्ठा wlan_network *pcur_network = &(pmlmepriv->cur_network);; */
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 cbw40_enable = 0;

	अगर (!phtpriv->ht_option)
		वापस;

	अगर ((!pmlmeinfo->HT_info_enable) || (!pmlmeinfo->HT_caps_enable))
		वापस;

	/* maybe needs check अगर ap supports rx ampdu. */
	अगर (!(phtpriv->ampdu_enable) && pregistrypriv->ampdu_enable == 1) अणु
		phtpriv->ampdu_enable = true;
	पूर्ण

	/* check Max Rx A-MPDU Size */
	len = 0;
	p = rtw_get_ie(pie+माप(काष्ठा ndis_802_11_fix_ie), WLAN_EID_HT_CAPABILITY, &len, ie_len-माप(काष्ठा ndis_802_11_fix_ie));
	अगर (p && len > 0) अणु
		pht_capie = (काष्ठा ieee80211_ht_cap *)(p+2);
		max_ampdu_sz = (pht_capie->ampdu_params_info & IEEE80211_HT_CAP_AMPDU_FACTOR);
		max_ampdu_sz = 1 << (max_ampdu_sz+3); /*  max_ampdu_sz (kbytes); */

		phtpriv->rx_ampdu_maxlen = max_ampdu_sz;

	पूर्ण

	len = 0;
	p = rtw_get_ie(pie+माप(काष्ठा ndis_802_11_fix_ie), WLAN_EID_HT_OPERATION, &len, ie_len-माप(काष्ठा ndis_802_11_fix_ie));
	अगर (p && len > 0) अणु
		pht_addtinfo = (काष्ठा ieee80211_ht_addt_info *)(p+2);
		/* toकरो: */
	पूर्ण

	अगर (channel > 14) अणु
		अगर ((pregistrypriv->bw_mode & 0xf0) > 0)
			cbw40_enable = 1;
	पूर्ण अन्यथा अणु
		अगर ((pregistrypriv->bw_mode & 0x0f) > 0)
			cbw40_enable = 1;
	पूर्ण

	/* update cur_bwmode & cur_ch_offset */
	अगर ((cbw40_enable) &&
	    (le16_to_cpu(pmlmeinfo->HT_caps.u.HT_cap_element.HT_caps_info) &
	      BIT(1)) && (pmlmeinfo->HT_info.infos[0] & BIT(2))) अणु
		पूर्णांक i;
		u8 rf_type;

		rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));

		/* update the MCS set */
		क्रम (i = 0; i < 16; i++)
			pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate[i] &= pmlmeext->शेष_supported_mcs_set[i];

		/* update the MCS rates */
		चयन (rf_type) अणु
		हाल RF_1T1R:
		हाल RF_1T2R:
			set_mcs_rate_by_mask(pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate, MCS_RATE_1R);
			अवरोध;
		हाल RF_2T2R:
		शेष:
			set_mcs_rate_by_mask(pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate, MCS_RATE_2R);
		पूर्ण

		/* चयन to the 40M Hz mode according to the AP */
		/* pmlmeext->cur_bwmode = CHANNEL_WIDTH_40; */
		चयन ((pmlmeinfo->HT_info.infos[0] & 0x3)) अणु
		हाल EXTCHNL_OFFSET_UPPER:
			pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
			अवरोध;

		हाल EXTCHNL_OFFSET_LOWER:
			pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
			अवरोध;

		शेष:
			pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			अवरोध;
		पूर्ण
	पूर्ण

	/*  */
	/*  Config SM Power Save setting */
	/*  */
	pmlmeinfo->SM_PS =
		(le16_to_cpu(pmlmeinfo->HT_caps.u.HT_cap_element.HT_caps_info) &
		 0x0C) >> 2;

	/*  */
	/*  Config current HT Protection mode. */
	/*  */
	pmlmeinfo->HT_protection = pmlmeinfo->HT_info.infos[1] & 0x3;
पूर्ण

व्योम rtw_issue_addbareq_cmd(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	u8 issued;
	पूर्णांक priority;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा ht_priv *phtpriv;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	s32 bmcst = IS_MCAST(pattrib->ra);

	/* अगर (bmcst || (padapter->mlmepriv.LinkDetectInfo.bTxBusyTraffic == false)) */
	अगर (bmcst || (padapter->mlmepriv.LinkDetectInfo.NumTxOkInPeriod < 100))
		वापस;

	priority = pattrib->priority;

	psta = rtw_get_stainfo(&padapter->stapriv, pattrib->ra);
	अगर (pattrib->psta != psta)
		वापस;

	अगर (!psta)
		वापस;

	अगर (!(psta->state & _FW_LINKED))
		वापस;

	phtpriv = &psta->htpriv;

	अगर (phtpriv->ht_option && phtpriv->ampdu_enable) अणु
		issued = (phtpriv->agg_enable_biपंचांगap>>priority)&0x1;
		issued |= (phtpriv->candidate_tid_biपंचांगap>>priority)&0x1;

		अगर (0 == issued) अणु
			psta->htpriv.candidate_tid_biपंचांगap |= BIT((u8)priority);
			rtw_addbareq_cmd(padapter, (u8) priority, pattrib->ra);
		पूर्ण
	पूर्ण

पूर्ण

व्योम rtw_append_exented_cap(काष्ठा adapter *padapter, u8 *out_ie, uपूर्णांक *pout_len)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv 	*phtpriv = &pmlmepriv->htpriv;
	u8 cap_content[8] = अणु0पूर्ण;

	अगर (phtpriv->bss_coexist)
		SET_EXT_CAPABILITY_ELE_BSS_COEXIST(cap_content, 1);

	rtw_set_ie(out_ie + *pout_len, WLAN_EID_EXT_CAPABILITY, 8, cap_content, pout_len);
पूर्ण

अंतरभूत व्योम rtw_set_to_roam(काष्ठा adapter *adapter, u8 to_roam)
अणु
	अगर (to_roam == 0)
		adapter->mlmepriv.to_join = false;
	adapter->mlmepriv.to_roam = to_roam;
पूर्ण

अंतरभूत u8 rtw_dec_to_roam(काष्ठा adapter *adapter)
अणु
	adapter->mlmepriv.to_roam--;
	वापस adapter->mlmepriv.to_roam;
पूर्ण

अंतरभूत u8 rtw_to_roam(काष्ठा adapter *adapter)
अणु
	वापस adapter->mlmepriv.to_roam;
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
	काष्ठा wlan_network *cur_network = &pmlmepriv->cur_network;
	पूर्णांक करो_join_r;

	अगर (0 < rtw_to_roam(padapter)) अणु
		स_नकल(&pmlmepriv->assoc_ssid, &cur_network->network.Ssid, माप(काष्ठा ndis_802_11_ssid));

		pmlmepriv->assoc_by_bssid = false;

		जबतक (1) अणु
			करो_join_r = rtw_करो_join(padapter);
			अगर (_SUCCESS == करो_join_r) अणु
				अवरोध;
			पूर्ण अन्यथा अणु
				rtw_dec_to_roam(padapter);

				अगर (rtw_to_roam(padapter) > 0) अणु
					जारी;
				पूर्ण अन्यथा अणु
					rtw_indicate_disconnect(padapter);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

पूर्ण

चिन्हित पूर्णांक rtw_linked_check(काष्ठा adapter *padapter)
अणु
	अगर ((check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == true) ||
			(check_fwstate(&padapter->mlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE) == true)) अणु
		अगर (padapter->stapriv.asoc_sta_count > 2)
			वापस true;
	पूर्ण अन्यथा अणु	/* Station mode */
		अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED) == true)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
