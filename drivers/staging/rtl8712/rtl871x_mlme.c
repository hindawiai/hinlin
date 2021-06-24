<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_mlme.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RTL871X_MLME_C_

#समावेश <linux/etherdevice.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "recv_osdep.h"
#समावेश "xmit_osdep.h"
#समावेश "mlme_osdep.h"
#समावेश "sta_info.h"
#समावेश "wifi.h"
#समावेश "wlan_bssdef.h"

अटल व्योम update_ht_cap(काष्ठा _adapter *padapter, u8 *pie, uपूर्णांक ie_len);

पूर्णांक r8712_init_mlme_priv(काष्ठा _adapter *padapter)
अणु
	sपूर्णांक	i;
	u8	*pbuf;
	काष्ठा wlan_network	*pnetwork;
	काष्ठा	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	स_रखो((u8 *)pmlmepriv, 0, माप(काष्ठा mlme_priv));
	pmlmepriv->nic_hdl = (u8 *)padapter;
	pmlmepriv->pscanned = शून्य;
	pmlmepriv->fw_state = 0;
	pmlmepriv->cur_network.network.Infraकाष्ठाureMode =
				 Ndis802_11AutoUnknown;
	/* Maybe someday we should नाम this variable to "active_mode"(Jeff)*/
	pmlmepriv->passive_mode = 1; /* 1: active, 0: passive. */
	spin_lock_init(&(pmlmepriv->lock));
	spin_lock_init(&(pmlmepriv->lock2));
	_init_queue(&(pmlmepriv->मुक्त_bss_pool));
	_init_queue(&(pmlmepriv->scanned_queue));
	set_scanned_network_val(pmlmepriv, 0);
	स_रखो(&pmlmepriv->assoc_ssid, 0, माप(काष्ठा ndis_802_11_ssid));
	pbuf = kदो_स्मृति_array(MAX_BSS_CNT, माप(काष्ठा wlan_network),
			     GFP_ATOMIC);
	अगर (!pbuf)
		वापस -ENOMEM;
	pmlmepriv->मुक्त_bss_buf = pbuf;
	pnetwork = (काष्ठा wlan_network *)pbuf;
	क्रम (i = 0; i < MAX_BSS_CNT; i++) अणु
		INIT_LIST_HEAD(&(pnetwork->list));
		list_add_tail(&(pnetwork->list),
				 &(pmlmepriv->मुक्त_bss_pool.queue));
		pnetwork++;
	पूर्ण
	pmlmepriv->sitesurveyctrl.last_rx_pkts = 0;
	pmlmepriv->sitesurveyctrl.last_tx_pkts = 0;
	pmlmepriv->sitesurveyctrl.traffic_busy = false;
	/* allocate DMA-able/Non-Page memory क्रम cmd_buf and rsp_buf */
	r8712_init_mlme_समयr(padapter);
	वापस 0;
पूर्ण

काष्ठा wlan_network *_r8712_alloc_network(काष्ठा mlme_priv *pmlmepriv)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा wlan_network *pnetwork;
	काष्ठा  __queue *मुक्त_queue = &pmlmepriv->मुक्त_bss_pool;

	spin_lock_irqsave(&मुक्त_queue->lock, irqL);
	pnetwork = list_first_entry_or_null(&मुक्त_queue->queue,
					    काष्ठा wlan_network, list);
	अगर (pnetwork) अणु
		list_del_init(&pnetwork->list);
		pnetwork->last_scanned = jअगरfies;
		pmlmepriv->num_of_scanned++;
	पूर्ण
	spin_unlock_irqrestore(&मुक्त_queue->lock, irqL);
	वापस pnetwork;
पूर्ण

अटल व्योम _मुक्त_network(काष्ठा mlme_priv *pmlmepriv,
			  काष्ठा wlan_network *pnetwork)
अणु
	u32 curr_समय, delta_समय;
	अचिन्हित दीर्घ irqL;
	काष्ठा  __queue *मुक्त_queue = &(pmlmepriv->मुक्त_bss_pool);

	अगर (!pnetwork)
		वापस;
	अगर (pnetwork->fixed)
		वापस;
	curr_समय = jअगरfies;
	delta_समय = (curr_समय - (u32)pnetwork->last_scanned) / HZ;
	अगर (delta_समय < SCANQUEUE_LIFETIME)
		वापस;
	spin_lock_irqsave(&मुक्त_queue->lock, irqL);
	list_del_init(&pnetwork->list);
	list_add_tail(&pnetwork->list, &मुक्त_queue->queue);
	pmlmepriv->num_of_scanned--;
	spin_unlock_irqrestore(&मुक्त_queue->lock, irqL);
पूर्ण

अटल व्योम मुक्त_network_nolock(काष्ठा mlme_priv *pmlmepriv,
			  काष्ठा wlan_network *pnetwork)
अणु
	काष्ठा  __queue *मुक्त_queue = &pmlmepriv->मुक्त_bss_pool;

	अगर (!pnetwork)
		वापस;
	अगर (pnetwork->fixed)
		वापस;
	list_del_init(&pnetwork->list);
	list_add_tail(&pnetwork->list, &मुक्त_queue->queue);
	pmlmepriv->num_of_scanned--;
पूर्ण

/* वापस the wlan_network with the matching addr
 * Shall be called under atomic context...
 * to aव्योम possible racing condition...
 */
अटल काष्ठा wlan_network *r8712_find_network(काष्ठा  __queue *scanned_queue,
					       u8 *addr)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा list_head *phead, *plist;
	काष्ठा wlan_network *pnetwork = शून्य;

	अगर (is_zero_ether_addr(addr))
		वापस शून्य;
	spin_lock_irqsave(&scanned_queue->lock, irqL);
	phead = &scanned_queue->queue;
	plist = phead->next;
	जबतक (plist != phead) अणु
		pnetwork = container_of(plist, काष्ठा wlan_network, list);
		plist = plist->next;
		अगर (!स_भेद(addr, pnetwork->network.MacAddress, ETH_ALEN))
			अवरोध;
	पूर्ण
	अगर (plist == phead)
		pnetwork = शून्य;
	spin_unlock_irqrestore(&scanned_queue->lock, irqL);
	वापस pnetwork;
पूर्ण

व्योम r8712_मुक्त_network_queue(काष्ठा _adapter *padapter)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा list_head *phead, *plist;
	काष्ठा wlan_network *pnetwork;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा  __queue *scanned_queue = &pmlmepriv->scanned_queue;

	spin_lock_irqsave(&scanned_queue->lock, irqL);
	phead = &scanned_queue->queue;
	plist = phead->next;
	जबतक (!end_of_queue_search(phead, plist)) अणु
		pnetwork = container_of(plist, काष्ठा wlan_network, list);
		plist = plist->next;
		_मुक्त_network(pmlmepriv, pnetwork);
	पूर्ण
	spin_unlock_irqrestore(&scanned_queue->lock, irqL);
पूर्ण

sपूर्णांक r8712_अगर_up(काष्ठा _adapter *padapter)
अणु
	sपूर्णांक res;

	अगर (padapter->driver_stopped || padapter->surprise_हटाओd ||
	    !check_fwstate(&padapter->mlmepriv, _FW_LINKED)) अणु
		res = false;
	पूर्ण अन्यथा अणु
		res = true;
	पूर्ण
	वापस res;
पूर्ण

व्योम r8712_generate_अक्रमom_ibss(u8 *pibss)
अणु
	u32 curसमय = jअगरfies;

	pibss[0] = 0x02; /*in ad-hoc mode bit1 must set to 1 */
	pibss[1] = 0x11;
	pibss[2] = 0x87;
	pibss[3] = (u8)(curसमय & 0xff);
	pibss[4] = (u8)((curसमय >> 8) & 0xff);
	pibss[5] = (u8)((curसमय >> 16) & 0xff);
पूर्ण

uपूर्णांक r8712_get_wlan_bssid_ex_sz(काष्ठा wlan_bssid_ex *bss)
अणु
	वापस माप(*bss) + bss->IELength - MAX_IE_SZ;
पूर्ण

u8 *r8712_get_capability_from_ie(u8 *ie)
अणु
	वापस ie + 8 + 2;
पूर्ण

व्योम r8712_मुक्त_mlme_priv(काष्ठा mlme_priv *pmlmepriv)
अणु
	kमुक्त(pmlmepriv->मुक्त_bss_buf);
पूर्ण

अटल काष्ठा	wlan_network *alloc_network(काष्ठा mlme_priv *pmlmepriv)
अणु
	वापस _r8712_alloc_network(pmlmepriv);
पूर्ण

पूर्णांक r8712_is_same_ibss(काष्ठा _adapter *adapter, काष्ठा wlan_network *pnetwork)
अणु
	पूर्णांक ret = true;
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;

	अगर ((psecuritypriv->PrivacyAlgrthm != _NO_PRIVACY_) &&
		    (pnetwork->network.Privacy == cpu_to_le32(0)))
		ret = false;
	अन्यथा अगर ((psecuritypriv->PrivacyAlgrthm == _NO_PRIVACY_) &&
		 (pnetwork->network.Privacy == cpu_to_le32(1)))
		ret = false;
	अन्यथा
		ret = true;
	वापस ret;

पूर्ण

अटल पूर्णांक is_same_network(काष्ठा wlan_bssid_ex *src,
			   काष्ठा wlan_bssid_ex *dst)
अणु
	u16 s_cap, d_cap;

	स_नकल((u8 *)&s_cap, r8712_get_capability_from_ie(src->IEs), 2);
	स_नकल((u8 *)&d_cap, r8712_get_capability_from_ie(dst->IEs), 2);
	वापस (src->Ssid.SsidLength == dst->Ssid.SsidLength) &&
			(src->Configuration.DSConfig ==
			dst->Configuration.DSConfig) &&
			((!स_भेद(src->MacAddress, dst->MacAddress,
			ETH_ALEN))) &&
			((!स_भेद(src->Ssid.Ssid,
			  dst->Ssid.Ssid,
			  src->Ssid.SsidLength))) &&
			((s_cap & WLAN_CAPABILITY_IBSS) ==
			(d_cap & WLAN_CAPABILITY_IBSS)) &&
			((s_cap & WLAN_CAPABILITY_ESS) ==
			(d_cap & WLAN_CAPABILITY_ESS));

पूर्ण

काष्ठा	wlan_network *r8712_get_oldest_wlan_network(
				काष्ठा  __queue *scanned_queue)
अणु
	काष्ठा list_head *plist, *phead;
	काष्ठा	wlan_network	*pwlan = शून्य;
	काष्ठा	wlan_network	*oldest = शून्य;

	phead = &scanned_queue->queue;
	plist = phead->next;
	जबतक (1) अणु
		अगर (end_of_queue_search(phead, plist))
			अवरोध;
		pwlan = container_of(plist, काष्ठा wlan_network, list);
		अगर (!pwlan->fixed) अणु
			अगर (!oldest ||
			    समय_after((अचिन्हित दीर्घ)oldest->last_scanned,
				       (अचिन्हित दीर्घ)pwlan->last_scanned))
				oldest = pwlan;
		पूर्ण
		plist = plist->next;
	पूर्ण
	वापस oldest;
पूर्ण

अटल व्योम update_network(काष्ठा wlan_bssid_ex *dst,
			   काष्ठा wlan_bssid_ex *src,
			   काष्ठा _adapter *padapter)
अणु
	u32 last_evm = 0, पंचांगpVal;
	काष्ठा smooth_rssi_data *sqd = &padapter->recvpriv.संकेत_qual_data;

	अगर (check_fwstate(&padapter->mlmepriv, _FW_LINKED) &&
	    is_same_network(&(padapter->mlmepriv.cur_network.network), src)) अणु
		अगर (padapter->recvpriv.संकेत_qual_data.total_num++ >=
		    PHY_LINKQUALITY_SLID_WIN_MAX) अणु
			padapter->recvpriv.संकेत_qual_data.total_num =
				   PHY_LINKQUALITY_SLID_WIN_MAX;
			last_evm = sqd->elements[sqd->index];
			padapter->recvpriv.संकेत_qual_data.total_val -=
				 last_evm;
		पूर्ण
		padapter->recvpriv.संकेत_qual_data.total_val += src->Rssi;

		sqd->elements[sqd->index++] = src->Rssi;
		अगर (padapter->recvpriv.संकेत_qual_data.index >=
		    PHY_LINKQUALITY_SLID_WIN_MAX)
			padapter->recvpriv.संकेत_qual_data.index = 0;
		/* <1> Showed on UI क्रम user, in percentage. */
		पंचांगpVal = padapter->recvpriv.संकेत_qual_data.total_val /
			 padapter->recvpriv.संकेत_qual_data.total_num;
		padapter->recvpriv.संकेत = (u8)पंचांगpVal;

		src->Rssi = padapter->recvpriv.संकेत;
	पूर्ण अन्यथा अणु
		src->Rssi = (src->Rssi + dst->Rssi) / 2;
	पूर्ण
	स_नकल((u8 *)dst, (u8 *)src, r8712_get_wlan_bssid_ex_sz(src));
पूर्ण

अटल व्योम update_current_network(काष्ठा _adapter *adapter,
				   काष्ठा wlan_bssid_ex *pnetwork)
अणु
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	अगर (is_same_network(&(pmlmepriv->cur_network.network), pnetwork)) अणु
		update_network(&(pmlmepriv->cur_network.network),
			       pnetwork, adapter);
		r8712_update_protection(adapter,
			       (pmlmepriv->cur_network.network.IEs) +
			       माप(काष्ठा NDIS_802_11_FIXED_IEs),
			       pmlmepriv->cur_network.network.IELength);
	पूर्ण
पूर्ण

/* Caller must hold pmlmepriv->lock first */
अटल व्योम update_scanned_network(काष्ठा _adapter *adapter,
			    काष्ठा wlan_bssid_ex *target)
अणु
	काष्ठा list_head *plist, *phead;

	u32 bssid_ex_sz;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा  __queue *queue = &pmlmepriv->scanned_queue;
	काष्ठा wlan_network *pnetwork = शून्य;
	काष्ठा wlan_network *oldest = शून्य;

	phead = &queue->queue;
	plist = phead->next;

	जबतक (1) अणु
		अगर (end_of_queue_search(phead, plist))
			अवरोध;

		pnetwork = container_of(plist, काष्ठा wlan_network, list);
		अगर (is_same_network(&pnetwork->network, target))
			अवरोध;
		अगर ((oldest == ((काष्ठा wlan_network *)0)) ||
		    समय_after((अचिन्हित दीर्घ)oldest->last_scanned,
				(अचिन्हित दीर्घ)pnetwork->last_scanned))
			oldest = pnetwork;

		plist = plist->next;
	पूर्ण

	/* If we didn't find a match, then get a new network slot to initialize
	 * with this beacon's inक्रमmation
	 */
	अगर (end_of_queue_search(phead, plist)) अणु
		अगर (list_empty(&pmlmepriv->मुक्त_bss_pool.queue)) अणु
			/* If there are no more slots, expire the oldest */
			pnetwork = oldest;
			target->Rssi = (pnetwork->network.Rssi +
					target->Rssi) / 2;
			स_नकल(&pnetwork->network, target,
				r8712_get_wlan_bssid_ex_sz(target));
			pnetwork->last_scanned = jअगरfies;
		पूर्ण अन्यथा अणु
			/* Otherwise just pull from the मुक्त list */
			/* update scan_समय */
			pnetwork = alloc_network(pmlmepriv);
			अगर (!pnetwork)
				वापस;
			bssid_ex_sz = r8712_get_wlan_bssid_ex_sz(target);
			target->Length = bssid_ex_sz;
			स_नकल(&pnetwork->network, target, bssid_ex_sz);
			list_add_tail(&pnetwork->list, &queue->queue);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* we have an entry and we are going to update it. But
		 * this entry may be alपढ़ोy expired. In this हाल we
		 * करो the same as we found a new net and call the new_net
		 * handler
		 */
		update_network(&pnetwork->network, target, adapter);
		pnetwork->last_scanned = jअगरfies;
	पूर्ण
पूर्ण

अटल व्योम rtl8711_add_network(काष्ठा _adapter *adapter,
			 काष्ठा wlan_bssid_ex *pnetwork)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा mlme_priv *pmlmepriv = &(((काष्ठा _adapter *)adapter)->mlmepriv);
	काष्ठा  __queue *queue = &pmlmepriv->scanned_queue;

	spin_lock_irqsave(&queue->lock, irqL);
	update_current_network(adapter, pnetwork);
	update_scanned_network(adapter, pnetwork);
	spin_unlock_irqrestore(&queue->lock, irqL);
पूर्ण

/*select the desired network based on the capability of the (i)bss.
 * check items:		(1) security
 *			(2) network_type
 *			(3) WMM
 *			(4) HT
 *			(5) others
 */
अटल पूर्णांक is_desired_network(काष्ठा _adapter *adapter,
				काष्ठा wlan_network *pnetwork)
अणु
	u8 wps_ie[512];
	uपूर्णांक wps_ielen;
	पूर्णांक bselected = true;
	काष्ठा	security_priv *psecuritypriv = &adapter->securitypriv;

	अगर (psecuritypriv->wps_phase) अणु
		अगर (r8712_get_wps_ie(pnetwork->network.IEs,
		    pnetwork->network.IELength, wps_ie,
		    &wps_ielen))
			वापस true;
		वापस false;
	पूर्ण
	अगर ((psecuritypriv->PrivacyAlgrthm != _NO_PRIVACY_) &&
		    (pnetwork->network.Privacy == 0))
		bselected = false;
	अगर (check_fwstate(&adapter->mlmepriv, WIFI_ADHOC_STATE)) अणु
		अगर (pnetwork->network.Infraकाष्ठाureMode !=
			adapter->mlmepriv.cur_network.network.
			Infraकाष्ठाureMode)
			bselected = false;
	पूर्ण
	वापस bselected;
पूर्ण

/* TODO: Perry : For Power Management */
व्योम r8712_atimकरोne_event_callback(काष्ठा _adapter *adapter, u8 *pbuf)
अणु
पूर्ण

व्योम r8712_survey_event_callback(काष्ठा _adapter *adapter, u8 *pbuf)
अणु
	अचिन्हित दीर्घ flags;
	u32 len;
	काष्ठा wlan_bssid_ex *pnetwork;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	pnetwork = (काष्ठा wlan_bssid_ex *)pbuf;
#अगर_घोषित __BIG_ENDIAN
	/* endian_convert */
	pnetwork->Length = le32_to_cpu(pnetwork->Length);
	pnetwork->Ssid.SsidLength = le32_to_cpu(pnetwork->Ssid.SsidLength);
	pnetwork->Privacy = le32_to_cpu(pnetwork->Privacy);
	pnetwork->Rssi = le32_to_cpu(pnetwork->Rssi);
	pnetwork->NetworkTypeInUse = le32_to_cpu(pnetwork->NetworkTypeInUse);
	pnetwork->Configuration.ATIMWinकरोw =
		 le32_to_cpu(pnetwork->Configuration.ATIMWinकरोw);
	pnetwork->Configuration.BeaconPeriod =
		 le32_to_cpu(pnetwork->Configuration.BeaconPeriod);
	pnetwork->Configuration.DSConfig =
		 le32_to_cpu(pnetwork->Configuration.DSConfig);
	pnetwork->Configuration.FHConfig.DwellTime =
		 le32_to_cpu(pnetwork->Configuration.FHConfig.DwellTime);
	pnetwork->Configuration.FHConfig.HopPattern =
		 le32_to_cpu(pnetwork->Configuration.FHConfig.HopPattern);
	pnetwork->Configuration.FHConfig.HopSet =
		 le32_to_cpu(pnetwork->Configuration.FHConfig.HopSet);
	pnetwork->Configuration.FHConfig.Length =
		 le32_to_cpu(pnetwork->Configuration.FHConfig.Length);
	pnetwork->Configuration.Length =
		 le32_to_cpu(pnetwork->Configuration.Length);
	pnetwork->Infraकाष्ठाureMode =
		 le32_to_cpu(pnetwork->Infraकाष्ठाureMode);
	pnetwork->IELength = le32_to_cpu(pnetwork->IELength);
#पूर्ण_अगर
	len = r8712_get_wlan_bssid_ex_sz(pnetwork);
	अगर (len > माप(काष्ठा wlan_bssid_ex))
		वापस;
	spin_lock_irqsave(&pmlmepriv->lock2, flags);
	/* update IBSS_network 's बारtamp */
	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
		अगर (!स_भेद(&(pmlmepriv->cur_network.network.MacAddress),
		    pnetwork->MacAddress, ETH_ALEN)) अणु
			काष्ठा wlan_network *ibss_wlan = शून्य;

			स_नकल(pmlmepriv->cur_network.network.IEs,
				pnetwork->IEs, 8);
			ibss_wlan = r8712_find_network(
						&pmlmepriv->scanned_queue,
						pnetwork->MacAddress);
			अगर (ibss_wlan) अणु
				स_नकल(ibss_wlan->network.IEs,
					pnetwork->IEs, 8);
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण
	/* lock pmlmepriv->lock when you accessing network_q */
	अगर (!check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) अणु
		अगर (pnetwork->Ssid.Ssid[0] != 0) अणु
			rtl8711_add_network(adapter, pnetwork);
		पूर्ण अन्यथा अणु
			pnetwork->Ssid.SsidLength = 8;
			स_नकल(pnetwork->Ssid.Ssid, "<hidden>", 8);
			rtl8711_add_network(adapter, pnetwork);
		पूर्ण
	पूर्ण
निकास:
	spin_unlock_irqrestore(&pmlmepriv->lock2, flags);
पूर्ण

व्योम r8712_surveyकरोne_event_callback(काष्ठा _adapter *adapter, u8 *pbuf)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);

	अगर (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY)) अणु
		del_समयr(&pmlmepriv->scan_to_समयr);

		_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	पूर्ण

	अगर (pmlmepriv->to_join) अणु
		अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
			अगर (!check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				set_fwstate(pmlmepriv, _FW_UNDER_LINKING);

				अगर (!r8712_select_and_join_from_scan(pmlmepriv)) अणु
					mod_समयr(&pmlmepriv->assoc_समयr, jअगरfies +
						  msecs_to_jअगरfies(MAX_JOIN_TIMEOUT));
				पूर्ण अन्यथा अणु
					काष्ठा wlan_bssid_ex *pdev_network =
					  &(adapter->registrypriv.dev_network);
					u8 *pibss =
						 adapter->registrypriv.
							dev_network.MacAddress;
					pmlmepriv->fw_state ^= _FW_UNDER_SURVEY;
					स_नकल(&pdev_network->Ssid,
						&pmlmepriv->assoc_ssid,
						माप(काष्ठा
							 ndis_802_11_ssid));
					r8712_update_registrypriv_dev_network
						(adapter);
					r8712_generate_अक्रमom_ibss(pibss);
					pmlmepriv->fw_state =
						 WIFI_ADHOC_MASTER_STATE;
					pmlmepriv->to_join = false;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			pmlmepriv->to_join = false;
			set_fwstate(pmlmepriv, _FW_UNDER_LINKING);
			अगर (!r8712_select_and_join_from_scan(pmlmepriv))
				mod_समयr(&pmlmepriv->assoc_समयr, jअगरfies +
					  msecs_to_jअगरfies(MAX_JOIN_TIMEOUT));
			अन्यथा
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
पूर्ण

/*
 *r8712_मुक्त_assoc_resources: the caller has to lock pmlmepriv->lock
 */
व्योम r8712_मुक्त_assoc_resources(काष्ठा _adapter *adapter)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा wlan_network *tgt_network = &pmlmepriv->cur_network;

	pwlan = r8712_find_network(&pmlmepriv->scanned_queue,
				   tgt_network->network.MacAddress);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_AP_STATE)) अणु
		काष्ठा sta_info *psta;

		psta = r8712_get_stainfo(&adapter->stapriv,
					 tgt_network->network.MacAddress);

		spin_lock_irqsave(&pstapriv->sta_hash_lock, irqL);
		r8712_मुक्त_stainfo(adapter,  psta);
		spin_unlock_irqrestore(&pstapriv->sta_hash_lock, irqL);
	पूर्ण

	अगर (check_fwstate(pmlmepriv,
	    WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE | WIFI_AP_STATE))
		r8712_मुक्त_all_stainfo(adapter);
	अगर (pwlan)
		pwlan->fixed = false;

	अगर (((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) &&
	     (adapter->stapriv.asoc_sta_count == 1)))
		मुक्त_network_nolock(pmlmepriv, pwlan);
पूर्ण

/*
 * r8712_indicate_connect: the caller has to lock pmlmepriv->lock
 */
व्योम r8712_indicate_connect(काष्ठा _adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	pmlmepriv->to_join = false;
	set_fwstate(pmlmepriv, _FW_LINKED);
	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_LINK);
	r8712_os_indicate_connect(padapter);
	अगर (padapter->registrypriv.घातer_mgnt > PS_MODE_ACTIVE)
		mod_समयr(&pmlmepriv->dhcp_समयr,
			  jअगरfies + msecs_to_jअगरfies(60000));
पूर्ण

/*
 * r8712_ind_disconnect: the caller has to lock pmlmepriv->lock
 */
व्योम r8712_ind_disconnect(काष्ठा _adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		_clr_fwstate_(pmlmepriv, _FW_LINKED);
		padapter->ledpriv.LedControlHandler(padapter, LED_CTL_NO_LINK);
		r8712_os_indicate_disconnect(padapter);
	पूर्ण
	अगर (padapter->pwrctrlpriv.pwr_mode !=
	    padapter->registrypriv.घातer_mgnt) अणु
		del_समयr(&pmlmepriv->dhcp_समयr);
		r8712_set_ps_mode(padapter, padapter->registrypriv.घातer_mgnt,
				  padapter->registrypriv.smart_ps);
	पूर्ण
पूर्ण

/*Notes:
 *pnetwork : वापसs from r8712_joinbss_event_callback
 *ptarget_wlan: found from scanned_queue
 *अगर join_res > 0, क्रम (fw_state==WIFI_STATION_STATE), we check अगर
 *  "ptarget_sta" & "ptarget_wlan" exist.
 *अगर join_res > 0, क्रम (fw_state==WIFI_ADHOC_STATE), we only check
 * अगर "ptarget_wlan" exist.
 *अगर join_res > 0, update "cur_network->network" from
 * "pnetwork->network" अगर (ptarget_wlan !=शून्य).
 */
व्योम r8712_joinbss_event_callback(काष्ठा _adapter *adapter, u8 *pbuf)
अणु
	अचिन्हित दीर्घ irqL = 0, irqL2;
	काष्ठा sta_info	*ptarget_sta = शून्य, *pcur_sta = शून्य;
	काष्ठा sta_priv	*pstapriv = &adapter->stapriv;
	काष्ठा mlme_priv	*pmlmepriv = &adapter->mlmepriv;
	काष्ठा wlan_network	*cur_network = &pmlmepriv->cur_network;
	काष्ठा wlan_network	*pcur_wlan = शून्य, *ptarget_wlan = शून्य;
	अचिन्हित पूर्णांक		the_same_macaddr = false;
	काष्ठा wlan_network *pnetwork;

	अगर (माप(काष्ठा list_head) == 4 * माप(u32)) अणु
		pnetwork = kदो_स्मृति(माप(काष्ठा wlan_network), GFP_ATOMIC);
		अगर (!pnetwork)
			वापस;
		स_नकल((u8 *)pnetwork + 16, (u8 *)pbuf + 8,
		       माप(काष्ठा wlan_network) - 16);
	पूर्ण अन्यथा अणु
		pnetwork = (काष्ठा wlan_network *)pbuf;
	पूर्ण

#अगर_घोषित __BIG_ENDIAN
	/* endian_convert */
	pnetwork->join_res = le32_to_cpu(pnetwork->join_res);
	pnetwork->network_type = le32_to_cpu(pnetwork->network_type);
	pnetwork->network.Length = le32_to_cpu(pnetwork->network.Length);
	pnetwork->network.Ssid.SsidLength =
		 le32_to_cpu(pnetwork->network.Ssid.SsidLength);
	pnetwork->network.Privacy = le32_to_cpu(pnetwork->network.Privacy);
	pnetwork->network.Rssi = le32_to_cpu(pnetwork->network.Rssi);
	pnetwork->network.NetworkTypeInUse =
		 le32_to_cpu(pnetwork->network.NetworkTypeInUse);
	pnetwork->network.Configuration.ATIMWinकरोw =
		 le32_to_cpu(pnetwork->network.Configuration.ATIMWinकरोw);
	pnetwork->network.Configuration.BeaconPeriod =
		 le32_to_cpu(pnetwork->network.Configuration.BeaconPeriod);
	pnetwork->network.Configuration.DSConfig =
		 le32_to_cpu(pnetwork->network.Configuration.DSConfig);
	pnetwork->network.Configuration.FHConfig.DwellTime =
		 le32_to_cpu(pnetwork->network.Configuration.FHConfig.
			     DwellTime);
	pnetwork->network.Configuration.FHConfig.HopPattern =
		 le32_to_cpu(pnetwork->network.Configuration.
			     FHConfig.HopPattern);
	pnetwork->network.Configuration.FHConfig.HopSet =
		 le32_to_cpu(pnetwork->network.Configuration.FHConfig.HopSet);
	pnetwork->network.Configuration.FHConfig.Length =
		 le32_to_cpu(pnetwork->network.Configuration.FHConfig.Length);
	pnetwork->network.Configuration.Length =
		 le32_to_cpu(pnetwork->network.Configuration.Length);
	pnetwork->network.Infraकाष्ठाureMode =
		 le32_to_cpu(pnetwork->network.Infraकाष्ठाureMode);
	pnetwork->network.IELength = le32_to_cpu(pnetwork->network.IELength);
#पूर्ण_अगर

	the_same_macaddr = !स_भेद(pnetwork->network.MacAddress,
				   cur_network->network.MacAddress, ETH_ALEN);
	pnetwork->network.Length =
		 r8712_get_wlan_bssid_ex_sz(&pnetwork->network);
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर (pnetwork->network.Length > माप(काष्ठा wlan_bssid_ex))
		जाओ ignore_joinbss_callback;
	अगर (pnetwork->join_res > 0) अणु
		अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) अणु
			/*s1. find ptarget_wlan*/
			अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
				अगर (the_same_macaddr) अणु
					ptarget_wlan =
					    r8712_find_network(&pmlmepriv->
					    scanned_queue,
					    cur_network->network.MacAddress);
				पूर्ण अन्यथा अणु
					pcur_wlan =
					     r8712_find_network(&pmlmepriv->
					     scanned_queue,
					     cur_network->network.MacAddress);
					अगर (pcur_wlan)
						pcur_wlan->fixed = false;

					pcur_sta = r8712_get_stainfo(pstapriv,
					     cur_network->network.MacAddress);
					spin_lock_irqsave(&pstapriv->
						sta_hash_lock, irqL2);
					r8712_मुक्त_stainfo(adapter, pcur_sta);
					spin_unlock_irqrestore(&(pstapriv->
						sta_hash_lock), irqL2);

					ptarget_wlan =
						 r8712_find_network(&pmlmepriv->
						 scanned_queue,
						 pnetwork->network.
						 MacAddress);
					अगर (ptarget_wlan)
						ptarget_wlan->fixed = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				ptarget_wlan = r8712_find_network(&pmlmepriv->
						scanned_queue,
						pnetwork->network.MacAddress);
				अगर (ptarget_wlan)
					ptarget_wlan->fixed = true;
			पूर्ण

			अगर (!ptarget_wlan) अणु
				अगर (check_fwstate(pmlmepriv,
					_FW_UNDER_LINKING))
					pmlmepriv->fw_state ^=
						 _FW_UNDER_LINKING;
				जाओ ignore_joinbss_callback;
			पूर्ण

			/*s2. find ptarget_sta & update ptarget_sta*/
			अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
				अगर (the_same_macaddr) अणु
					ptarget_sta =
						 r8712_get_stainfo(pstapriv,
						 pnetwork->network.MacAddress);
					अगर (!ptarget_sta)
						ptarget_sta =
						 r8712_alloc_stainfo(pstapriv,
						 pnetwork->network.MacAddress);
				पूर्ण अन्यथा अणु
					ptarget_sta =
						 r8712_alloc_stainfo(pstapriv,
						 pnetwork->network.MacAddress);
				पूर्ण
				अगर (ptarget_sta) /*update ptarget_sta*/ अणु
					ptarget_sta->aid = pnetwork->join_res;
					ptarget_sta->qos_option = 1;
					ptarget_sta->mac_id = 5;
					अगर (adapter->securitypriv.
					    AuthAlgrthm == 2) अणु
						adapter->securitypriv.
							binstallGrpkey =
							 false;
						adapter->securitypriv.
							busetkipkey =
							 false;
						adapter->securitypriv.
							bgrpkey_handshake =
							 false;
						ptarget_sta->ieee8021x_blocked
							 = true;
						ptarget_sta->XPrivacy =
							 adapter->securitypriv.
							 PrivacyAlgrthm;
						स_रखो((u8 *)&ptarget_sta->
							 x_UncstKey,
							 0,
							 माप(जोड़ Keytype));
						स_रखो((u8 *)&ptarget_sta->
							 tkiprxmickey,
							 0,
							 माप(जोड़ Keytype));
						स_रखो((u8 *)&ptarget_sta->
							 tkiptxmickey,
							 0,
							 माप(जोड़ Keytype));
						स_रखो((u8 *)&ptarget_sta->
							 txpn, 0,
							 माप(जोड़ pn48));
						स_रखो((u8 *)&ptarget_sta->
							 rxpn, 0,
							 माप(जोड़ pn48));
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (check_fwstate(pmlmepriv,
					    _FW_UNDER_LINKING))
						pmlmepriv->fw_state ^=
							 _FW_UNDER_LINKING;
					जाओ ignore_joinbss_callback;
				पूर्ण
			पूर्ण

			/*s3. update cur_network & indicate connect*/
			स_नकल(&cur_network->network, &pnetwork->network,
				pnetwork->network.Length);
			cur_network->aid = pnetwork->join_res;
			/*update fw_state will clr _FW_UNDER_LINKING*/
			चयन (pnetwork->network.Infraकाष्ठाureMode) अणु
			हाल Ndis802_11Infraकाष्ठाure:
				pmlmepriv->fw_state = WIFI_STATION_STATE;
				अवरोध;
			हाल Ndis802_11IBSS:
				pmlmepriv->fw_state = WIFI_ADHOC_STATE;
				अवरोध;
			शेष:
				pmlmepriv->fw_state = WIFI_शून्य_STATE;
				अवरोध;
			पूर्ण
			r8712_update_protection(adapter,
					  (cur_network->network.IEs) +
					  माप(काष्ठा NDIS_802_11_FIXED_IEs),
					  (cur_network->network.IELength));
			/*TODO: update HT_Capability*/
			update_ht_cap(adapter, cur_network->network.IEs,
				      cur_network->network.IELength);
			/*indicate connect*/
			अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
				r8712_indicate_connect(adapter);
			del_समयr(&pmlmepriv->assoc_समयr);
		पूर्ण अन्यथा अणु
			जाओ ignore_joinbss_callback;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) अणु
			mod_समयr(&pmlmepriv->assoc_समयr,
				  jअगरfies + msecs_to_jअगरfies(1));
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
		पूर्ण
	पूर्ण
ignore_joinbss_callback:
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	अगर (माप(काष्ठा list_head) == 4 * माप(u32))
		kमुक्त(pnetwork);
पूर्ण

व्योम r8712_stassoc_event_callback(काष्ठा _adapter *adapter, u8 *pbuf)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा sta_info *psta;
	काष्ठा mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	काष्ठा stassoc_event *pstassoc	= (काष्ठा stassoc_event *)pbuf;

	/* to करो: */
	अगर (!r8712_access_ctrl(&adapter->acl_list, pstassoc->macaddr))
		वापस;
	psta = r8712_get_stainfo(&adapter->stapriv, pstassoc->macaddr);
	अगर (psta) अणु
		/*the sta have been in sta_info_queue => करो nothing
		 *(between drv has received this event beक्रमe and
		 * fw have not yet to set key to CAM_ENTRY)
		 */
		वापस;
	पूर्ण

	psta = r8712_alloc_stainfo(&adapter->stapriv, pstassoc->macaddr);
	अगर (!psta)
		वापस;
	/* to करो : init sta_info variable */
	psta->qos_option = 0;
	psta->mac_id = le32_to_cpu(pstassoc->cam_id);
	/* psta->aid = (uपूर्णांक)pstassoc->cam_id; */

	अगर (adapter->securitypriv.AuthAlgrthm == 2)
		psta->XPrivacy = adapter->securitypriv.PrivacyAlgrthm;
	psta->ieee8021x_blocked = false;
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
		अगर (adapter->stapriv.asoc_sta_count == 2) अणु
			/* a sta + bc/mc_stainfo (not Ibss_stainfo) */
			r8712_indicate_connect(adapter);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
पूर्ण

व्योम r8712_stadel_event_callback(काष्ठा _adapter *adapter, u8 *pbuf)
अणु
	अचिन्हित दीर्घ irqL, irqL2;
	काष्ठा sta_info *psta;
	काष्ठा wlan_network *pwlan = शून्य;
	काष्ठा wlan_bssid_ex *pdev_network = शून्य;
	u8 *pibss = शून्य;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा stadel_event *pstadel = (काष्ठा stadel_event *)pbuf;
	काष्ठा sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा wlan_network *tgt_network = &pmlmepriv->cur_network;

	spin_lock_irqsave(&pmlmepriv->lock, irqL2);
	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
		r8712_ind_disconnect(adapter);
		r8712_मुक्त_assoc_resources(adapter);
	पूर्ण
	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE |
	    WIFI_ADHOC_STATE)) अणु
		psta = r8712_get_stainfo(&adapter->stapriv, pstadel->macaddr);
		spin_lock_irqsave(&pstapriv->sta_hash_lock, irqL);
		r8712_मुक्त_stainfo(adapter, psta);
		spin_unlock_irqrestore(&pstapriv->sta_hash_lock, irqL);
		अगर (adapter->stapriv.asoc_sta_count == 1) अणु
			/*a sta + bc/mc_stainfo (not Ibss_stainfo) */
			pwlan = r8712_find_network(&pmlmepriv->scanned_queue,
				tgt_network->network.MacAddress);
			अगर (pwlan) अणु
				pwlan->fixed = false;
				मुक्त_network_nolock(pmlmepriv, pwlan);
			पूर्ण
			/*re-create ibss*/
			pdev_network = &(adapter->registrypriv.dev_network);
			pibss = adapter->registrypriv.dev_network.MacAddress;
			स_नकल(pdev_network, &tgt_network->network,
				r8712_get_wlan_bssid_ex_sz(&tgt_network->
							network));
			स_नकल(&pdev_network->Ssid,
				&pmlmepriv->assoc_ssid,
				माप(काष्ठा ndis_802_11_ssid));
			r8712_update_registrypriv_dev_network(adapter);
			r8712_generate_अक्रमom_ibss(pibss);
			अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) अणु
				_clr_fwstate_(pmlmepriv, WIFI_ADHOC_STATE);
				set_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL2);
पूर्ण

व्योम r8712_cpwm_event_callback(काष्ठा _adapter *adapter, u8 *pbuf)
अणु
	काष्ठा reportpwrstate_parm *preportpwrstate =
			 (काष्ठा reportpwrstate_parm *)pbuf;

	preportpwrstate->state |= (u8)(adapter->pwrctrlpriv.cpwm_tog + 0x80);
	r8712_cpwm_पूर्णांक_hdl(adapter, preportpwrstate);
पूर्ण

/*	When the Netgear 3500 AP is with WPA2PSK-AES mode, it will send
 *	 the ADDBA req frame with start seq control = 0 to wअगरi client after
 *	 the WPA handshake and the seqence number of following data packet
 *	will be 0. In this हाल, the Rx reorder sequence is not दीर्घer than 0
 *	 and the WiFi client will drop the data with seq number 0.
 *	So, the 8712 firmware has to inक्रमm driver with receiving the
 *	 ADDBA-Req frame so that the driver can reset the
 *	sequence value of Rx reorder control.
 */
व्योम r8712_got_addbareq_event_callback(काष्ठा _adapter *adapter, u8 *pbuf)
अणु
	काष्ठा	ADDBA_Req_Report_parm *pAddbareq_pram =
			 (काष्ठा ADDBA_Req_Report_parm *)pbuf;
	काष्ठा	sta_info *psta;
	काष्ठा	sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा	recv_reorder_ctrl *precvreorder_ctrl = शून्य;

	psta = r8712_get_stainfo(pstapriv, pAddbareq_pram->MacAddress);
	अगर (psta) अणु
		precvreorder_ctrl =
			 &psta->recvreorder_ctrl[pAddbareq_pram->tid];
		/* set the indicate_seq to 0xffff so that the rx reorder
		 * can store any following data packet.
		 */
		precvreorder_ctrl->indicate_seq = 0xffff;
	पूर्ण
पूर्ण

व्योम r8712_wpspbc_event_callback(काष्ठा _adapter *adapter, u8 *pbuf)
अणु
	अगर (!adapter->securitypriv.wps_hw_pbc_pressed)
		adapter->securitypriv.wps_hw_pbc_pressed = true;
पूर्ण

व्योम _r8712_sitesurvey_ctrl_handler(काष्ठा _adapter *adapter)
अणु
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा sitesurvey_ctrl	*psitesurveyctrl = &pmlmepriv->sitesurveyctrl;
	काष्ठा registry_priv	*pregistrypriv = &adapter->registrypriv;
	u64 current_tx_pkts;
	uपूर्णांक current_rx_pkts;

	current_tx_pkts = (adapter->xmitpriv.tx_pkts) -
			  (psitesurveyctrl->last_tx_pkts);
	current_rx_pkts = (adapter->recvpriv.rx_pkts) -
			  (psitesurveyctrl->last_rx_pkts);
	psitesurveyctrl->last_tx_pkts = adapter->xmitpriv.tx_pkts;
	psitesurveyctrl->last_rx_pkts = adapter->recvpriv.rx_pkts;
	अगर ((current_tx_pkts > pregistrypriv->busy_thresh) ||
	    (current_rx_pkts > pregistrypriv->busy_thresh))
		psitesurveyctrl->traffic_busy = true;
	अन्यथा
		psitesurveyctrl->traffic_busy = false;
पूर्ण

व्योम _r8712_join_समयout_handler(काष्ठा _adapter *adapter)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	अगर (adapter->driver_stopped || adapter->surprise_हटाओd)
		वापस;
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
	pmlmepriv->to_join = false;
	अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		r8712_os_indicate_disconnect(adapter);
		_clr_fwstate_(pmlmepriv, _FW_LINKED);
	पूर्ण
	अगर (adapter->pwrctrlpriv.pwr_mode != adapter->registrypriv.घातer_mgnt) अणु
		r8712_set_ps_mode(adapter, adapter->registrypriv.घातer_mgnt,
				  adapter->registrypriv.smart_ps);
	पूर्ण
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
पूर्ण

व्योम r8712_scan_समयout_handler (काष्ठा _adapter *adapter)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	pmlmepriv->to_join = false;	/* scan fail, so clear to_join flag */
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
पूर्ण

व्योम _r8712_dhcp_समयout_handler (काष्ठा _adapter *adapter)
अणु
	अगर (adapter->driver_stopped || adapter->surprise_हटाओd)
		वापस;
	अगर (adapter->pwrctrlpriv.pwr_mode != adapter->registrypriv.घातer_mgnt)
		r8712_set_ps_mode(adapter, adapter->registrypriv.घातer_mgnt,
			    adapter->registrypriv.smart_ps);
पूर्ण

पूर्णांक r8712_select_and_join_from_scan(काष्ठा mlme_priv *pmlmepriv)
अणु
	काष्ठा list_head *phead;
	अचिन्हित अक्षर *dst_ssid, *src_ssid;
	काष्ठा _adapter *adapter;
	काष्ठा  __queue *queue = शून्य;
	काष्ठा wlan_network *pnetwork = शून्य;
	काष्ठा wlan_network *pnetwork_max_rssi = शून्य;

	adapter = (काष्ठा _adapter *)pmlmepriv->nic_hdl;
	queue = &pmlmepriv->scanned_queue;
	phead = &queue->queue;
	pmlmepriv->pscanned = phead->next;
	जबतक (1) अणु
		अगर (end_of_queue_search(phead, pmlmepriv->pscanned)) अणु
			अगर (pmlmepriv->assoc_by_rssi && pnetwork_max_rssi) अणु
				pnetwork = pnetwork_max_rssi;
				जाओ ask_क्रम_joinbss;
			पूर्ण
			वापस -EINVAL;
		पूर्ण
		pnetwork = container_of(pmlmepriv->pscanned,
					काष्ठा wlan_network, list);
		pmlmepriv->pscanned = pmlmepriv->pscanned->next;
		अगर (pmlmepriv->assoc_by_bssid) अणु
			dst_ssid = pnetwork->network.MacAddress;
			src_ssid = pmlmepriv->assoc_bssid;
			अगर (!स_भेद(dst_ssid, src_ssid, ETH_ALEN)) अणु
				अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
					अगर (is_same_network(&pmlmepriv->
					    cur_network.network,
					    &pnetwork->network)) अणु
						_clr_fwstate_(pmlmepriv,
							_FW_UNDER_LINKING);
						/*r8712_indicate_connect again*/
						r8712_indicate_connect(adapter);
						वापस 2;
					पूर्ण
					r8712_disassoc_cmd(adapter);
					r8712_ind_disconnect(adapter);
					r8712_मुक्त_assoc_resources(adapter);
				पूर्ण
				जाओ ask_क्रम_joinbss;
			पूर्ण
		पूर्ण अन्यथा अगर (pmlmepriv->assoc_ssid.SsidLength == 0) अणु
			जाओ ask_क्रम_joinbss;
		पूर्ण
		dst_ssid = pnetwork->network.Ssid.Ssid;
		src_ssid = pmlmepriv->assoc_ssid.Ssid;
		अगर ((pnetwork->network.Ssid.SsidLength ==
		    pmlmepriv->assoc_ssid.SsidLength) &&
		    (!स_भेद(dst_ssid, src_ssid,
		     pmlmepriv->assoc_ssid.SsidLength))) अणु
			अगर (pmlmepriv->assoc_by_rssi) अणु
				/* अगर the ssid is the same, select the bss
				 * which has the max rssi
				 */
				अगर (pnetwork_max_rssi) अणु
					अगर (pnetwork->network.Rssi >
					    pnetwork_max_rssi->network.Rssi)
						pnetwork_max_rssi = pnetwork;
				पूर्ण अन्यथा अणु
					pnetwork_max_rssi = pnetwork;
				पूर्ण
			पूर्ण अन्यथा अगर (is_desired_network(adapter, pnetwork)) अणु
				अगर (check_fwstate(pmlmepriv, _FW_LINKED)) अणु
					r8712_disassoc_cmd(adapter);
					r8712_मुक्त_assoc_resources(adapter);
				पूर्ण
				जाओ ask_क्रम_joinbss;
			पूर्ण
		पूर्ण
	पूर्ण

ask_क्रम_joinbss:
	वापस r8712_joinbss_cmd(adapter, pnetwork);
पूर्ण

पूर्णांक r8712_set_auth(काष्ठा _adapter *adapter,
		   काष्ठा security_priv *psecuritypriv)
अणु
	काष्ठा cmd_priv	*pcmdpriv = &adapter->cmdpriv;
	काष्ठा cmd_obj *pcmd;
	काष्ठा setauth_parm *psetauthparm;

	pcmd = kदो_स्मृति(माप(*pcmd), GFP_ATOMIC);
	अगर (!pcmd)
		वापस -ENOMEM;

	psetauthparm = kzalloc(माप(*psetauthparm), GFP_ATOMIC);
	अगर (!psetauthparm) अणु
		kमुक्त(pcmd);
		वापस -ENOMEM;
	पूर्ण
	psetauthparm->mode = (u8)psecuritypriv->AuthAlgrthm;
	pcmd->cmdcode = _SetAuth_CMD_;
	pcmd->parmbuf = (अचिन्हित अक्षर *)psetauthparm;
	pcmd->cmdsz = माप(काष्ठा setauth_parm);
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;
	INIT_LIST_HEAD(&pcmd->list);
	r8712_enqueue_cmd(pcmdpriv, pcmd);
	वापस 0;
पूर्ण

पूर्णांक r8712_set_key(काष्ठा _adapter *adapter,
		  काष्ठा security_priv *psecuritypriv,
		  sपूर्णांक keyid)
अणु
	काष्ठा cmd_priv *pcmdpriv = &adapter->cmdpriv;
	काष्ठा cmd_obj *pcmd;
	काष्ठा setkey_parm *psetkeyparm;
	u8 keylen;
	पूर्णांक ret;

	pcmd = kदो_स्मृति(माप(*pcmd), GFP_ATOMIC);
	अगर (!pcmd)
		वापस -ENOMEM;
	psetkeyparm = kzalloc(माप(*psetkeyparm), GFP_ATOMIC);
	अगर (!psetkeyparm) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_cmd;
	पूर्ण
	अगर (psecuritypriv->AuthAlgrthm == 2) अणु /* 802.1X */
		psetkeyparm->algorithm =
			 (u8)psecuritypriv->XGrpPrivacy;
	पूर्ण अन्यथा अणु /* WEP */
		psetkeyparm->algorithm =
			 (u8)psecuritypriv->PrivacyAlgrthm;
	पूर्ण
	psetkeyparm->keyid = (u8)keyid;

	चयन (psetkeyparm->algorithm) अणु
	हाल _WEP40_:
		keylen = 5;
		स_नकल(psetkeyparm->key,
			psecuritypriv->DefKey[keyid].skey, keylen);
		अवरोध;
	हाल _WEP104_:
		keylen = 13;
		स_नकल(psetkeyparm->key,
			psecuritypriv->DefKey[keyid].skey, keylen);
		अवरोध;
	हाल _TKIP_:
		अगर (keyid < 1 || keyid > 2) अणु
			ret = -EINVAL;
			जाओ err_मुक्त_parm;
		पूर्ण
		keylen = 16;
		स_नकल(psetkeyparm->key,
			&psecuritypriv->XGrpKey[keyid - 1], keylen);
		psetkeyparm->grpkey = 1;
		अवरोध;
	हाल _AES_:
		अगर (keyid < 1 || keyid > 2) अणु
			ret = -EINVAL;
			जाओ err_मुक्त_parm;
		पूर्ण
		keylen = 16;
		स_नकल(psetkeyparm->key,
			&psecuritypriv->XGrpKey[keyid - 1], keylen);
		psetkeyparm->grpkey = 1;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err_मुक्त_parm;
	पूर्ण
	pcmd->cmdcode = _SetKey_CMD_;
	pcmd->parmbuf = (u8 *)psetkeyparm;
	pcmd->cmdsz =  (माप(काष्ठा setkey_parm));
	pcmd->rsp = शून्य;
	pcmd->rspsz = 0;
	INIT_LIST_HEAD(&pcmd->list);
	r8712_enqueue_cmd(pcmdpriv, pcmd);
	वापस 0;

err_मुक्त_parm:
	kमुक्त(psetkeyparm);
err_मुक्त_cmd:
	kमुक्त(pcmd);
	वापस ret;
पूर्ण

/* adjust IEs क्रम r8712_joinbss_cmd in WMM */
पूर्णांक r8712_reकाष्ठा_wmm_ie(काष्ठा _adapter *adapter, u8 *in_ie, u8 *out_ie,
		    uपूर्णांक in_len, uपूर्णांक initial_out_len)
अणु
	अचिन्हित पूर्णांक ielength = 0;
	अचिन्हित पूर्णांक i, j;

	i = 12; /* after the fixed IE */
	जबतक (i < in_len) अणु
		ielength = initial_out_len;
		अगर (in_ie[i] == 0xDD && in_ie[i + 2] == 0x00 &&
		    in_ie[i + 3] == 0x50 && in_ie[i + 4] == 0xF2 &&
		    in_ie[i + 5] == 0x02 && i + 5 < in_len) अणु
			/*WMM element ID and OUI*/
			क्रम (j = i; j < i + 9; j++) अणु
				out_ie[ielength] = in_ie[j];
				ielength++;
			पूर्ण
			out_ie[initial_out_len + 1] = 0x07;
			out_ie[initial_out_len + 6] = 0x00;
			out_ie[initial_out_len + 8] = 0x00;
			अवरोध;
		पूर्ण
		i += (in_ie[i + 1] + 2); /* to the next IE element */
	पूर्ण
	वापस ielength;
पूर्ण

/*
 * Ported from 8185: IsInPreAuthKeyList().
 *
 * Search by BSSID,
 * Return Value:
 *	-1		:अगर there is no pre-auth key in the  table
 *	>=0		:अगर there is pre-auth key, and   वापस the entry id
 */
अटल पूर्णांक SecIsInPMKIDList(काष्ठा _adapter *Adapter, u8 *bssid)
अणु
	काष्ठा security_priv *psecuritypriv = &Adapter->securitypriv;
	पूर्णांक i = 0;

	करो अणु
		अगर (psecuritypriv->PMKIDList[i].bUsed &&
		   (!स_भेद(psecuritypriv->PMKIDList[i].Bssid,
			    bssid, ETH_ALEN)))
			अवरोध;
		i++;

	पूर्ण जबतक (i < NUM_PMKID_CACHE);

	अगर (i == NUM_PMKID_CACHE) अणु
		i = -1; /* Could not find. */
	पूर्ण अन्यथा अणु
		; /* There is one Pre-Authentication Key क्रम the
		   * specअगरic BSSID.
		   */
	पूर्ण
	वापस i;
पूर्ण

sपूर्णांक r8712_reकाष्ठा_sec_ie(काष्ठा _adapter *adapter, u8 *in_ie,
		     u8 *out_ie, uपूर्णांक in_len)
अणु
	u8 authmode = 0, match;
	u8 sec_ie[IW_CUSTOM_MAX], uncst_oui[4], bkup_ie[255];
	u8 wpa_oui[4] = अणु0x0, 0x50, 0xf2, 0x01पूर्ण;
	uपूर्णांक ielength, cnt, हटाओ_cnt;
	पूर्णांक iEntry;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;
	uपूर्णांक ndisauthmode = psecuritypriv->ndisauthtype;
	uपूर्णांक ndissecuritytype = psecuritypriv->ndisencryptstatus;

	अगर ((ndisauthmode == Ndis802_11AuthModeWPA) ||
	    (ndisauthmode == Ndis802_11AuthModeWPAPSK)) अणु
		authmode = _WPA_IE_ID_;
		uncst_oui[0] = 0x0;
		uncst_oui[1] = 0x50;
		uncst_oui[2] = 0xf2;
	पूर्ण
	अगर ((ndisauthmode == Ndis802_11AuthModeWPA2) ||
	    (ndisauthmode == Ndis802_11AuthModeWPA2PSK)) अणु
		authmode = _WPA2_IE_ID_;
		uncst_oui[0] = 0x0;
		uncst_oui[1] = 0x0f;
		uncst_oui[2] = 0xac;
	पूर्ण
	चयन (ndissecuritytype) अणु
	हाल Ndis802_11Encryption1Enabled:
	हाल Ndis802_11Encryption1KeyAbsent:
		uncst_oui[3] = 0x1;
		अवरोध;
	हाल Ndis802_11Encryption2Enabled:
	हाल Ndis802_11Encryption2KeyAbsent:
		uncst_oui[3] = 0x2;
		अवरोध;
	हाल Ndis802_11Encryption3Enabled:
	हाल Ndis802_11Encryption3KeyAbsent:
		uncst_oui[3] = 0x4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/*Search required WPA or WPA2 IE and copy to sec_ie[] */
	cnt = 12;
	match = false;
	जबतक (cnt < in_len) अणु
		अगर (in_ie[cnt] == authmode) अणु
			अगर ((authmode == _WPA_IE_ID_) &&
			    (!स_भेद(&in_ie[cnt + 2], &wpa_oui[0], 4))) अणु
				स_नकल(&sec_ie[0], &in_ie[cnt],
					in_ie[cnt + 1] + 2);
				match = true;
				अवरोध;
			पूर्ण
			अगर (authmode == _WPA2_IE_ID_) अणु
				स_नकल(&sec_ie[0], &in_ie[cnt],
					in_ie[cnt + 1] + 2);
				match = true;
				अवरोध;
			पूर्ण
			अगर (((authmode == _WPA_IE_ID_) &&
			     (!स_भेद(&in_ie[cnt + 2], &wpa_oui[0], 4))) ||
			     (authmode == _WPA2_IE_ID_))
				स_नकल(&bkup_ie[0], &in_ie[cnt],
					in_ie[cnt + 1] + 2);
		पूर्ण
		cnt += in_ie[cnt + 1] + 2; /*get next*/
	पूर्ण
	/*reकाष्ठा WPA IE or WPA2 IE in sec_ie[] */
	अगर (match) अणु
		अगर (sec_ie[0] == _WPA_IE_ID_) अणु
			/* parsing SSN IE to select required encryption
			 * algorithm, and set the bc/mc encryption algorithm
			 */
			जबतक (true) अणु
				/*check wpa_oui tag*/
				अगर (स_भेद(&sec_ie[2], &wpa_oui[0], 4)) अणु
					match = false;
					अवरोध;
				पूर्ण
				अगर ((sec_ie[6] != 0x01) || (sec_ie[7] != 0x0)) अणु
					/*IE Ver error*/
					match = false;
					अवरोध;
				पूर्ण
				अगर (!स_भेद(&sec_ie[8], &wpa_oui[0], 3)) अणु
					/* get bc/mc encryption type (group
					 * key type)
					 */
					चयन (sec_ie[11]) अणु
					हाल 0x0: /*none*/
						psecuritypriv->XGrpPrivacy =
								_NO_PRIVACY_;
						अवरोध;
					हाल 0x1: /*WEP_40*/
						psecuritypriv->XGrpPrivacy =
								_WEP40_;
						अवरोध;
					हाल 0x2: /*TKIP*/
						psecuritypriv->XGrpPrivacy =
								_TKIP_;
						अवरोध;
					हाल 0x3: /*AESCCMP*/
					हाल 0x4:
						psecuritypriv->XGrpPrivacy =
								_AES_;
						अवरोध;
					हाल 0x5: /*WEP_104*/
						psecuritypriv->XGrpPrivacy =
								_WEP104_;
						अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					match = false;
					अवरोध;
				पूर्ण
				अगर (sec_ie[12] == 0x01) अणु
					/*check the unicast encryption type*/
					अगर (स_भेद(&sec_ie[14],
					    &uncst_oui[0], 4)) अणु
						match = false;
						अवरोध;

					पूर्ण /*अन्यथा the uncst_oui is match*/
				पूर्ण अन्यथा अणु /*mixed mode, unicast_enc_type > 1*/
					/*select the uncst_oui and हटाओ
					 * the other uncst_oui
					 */
					cnt = sec_ie[12];
					हटाओ_cnt = (cnt - 1) * 4;
					sec_ie[12] = 0x01;
					स_नकल(&sec_ie[14], &uncst_oui[0], 4);
					/*हटाओ the other unicast suit*/
					स_नकल(&sec_ie[18],
						&sec_ie[18 + हटाओ_cnt],
						sec_ie[1] - 18 + 2 -
						हटाओ_cnt);
					sec_ie[1] = sec_ie[1] - हटाओ_cnt;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (authmode == _WPA2_IE_ID_) अणु
			/* parsing RSN IE to select required encryption
			 * algorithm, and set the bc/mc encryption algorithm
			 */
			जबतक (true) अणु
				अगर ((sec_ie[2] != 0x01) || (sec_ie[3] != 0x0)) अणु
					/*IE Ver error*/
					match = false;
					अवरोध;
				पूर्ण
				अगर (!स_भेद(&sec_ie[4], &uncst_oui[0], 3)) अणु
					/*get bc/mc encryption type*/
					चयन (sec_ie[7]) अणु
					हाल 0x1: /*WEP_40*/
						psecuritypriv->XGrpPrivacy =
								_WEP40_;
						अवरोध;
					हाल 0x2: /*TKIP*/
						psecuritypriv->XGrpPrivacy =
								_TKIP_;
						अवरोध;
					हाल 0x4: /*AESWRAP*/
						psecuritypriv->XGrpPrivacy =
								_AES_;
						अवरोध;
					हाल 0x5: /*WEP_104*/
						psecuritypriv->XGrpPrivacy =
								_WEP104_;
						अवरोध;
					शेष: /*one*/
						psecuritypriv->XGrpPrivacy =
								_NO_PRIVACY_;
						अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					match = false;
					अवरोध;
				पूर्ण
				अगर (sec_ie[8] == 0x01) अणु
					/*check the unicast encryption type*/
					अगर (स_भेद(&sec_ie[10],
						     &uncst_oui[0], 4)) अणु
						match = false;
						अवरोध;
					पूर्ण /*अन्यथा the uncst_oui is match*/
				पूर्ण अन्यथा अणु /*mixed mode, unicast_enc_type > 1*/
					/*select the uncst_oui and हटाओ the
					 * other uncst_oui
					 */
					cnt = sec_ie[8];
					हटाओ_cnt = (cnt - 1) * 4;
					sec_ie[8] = 0x01;
					स_नकल(&sec_ie[10], &uncst_oui[0], 4);
					/*हटाओ the other unicast suit*/
					स_नकल(&sec_ie[14],
						&sec_ie[14 + हटाओ_cnt],
						(sec_ie[1] - 14 + 2 -
						हटाओ_cnt));
					sec_ie[1] = sec_ie[1] - हटाओ_cnt;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((authmode == _WPA_IE_ID_) || (authmode == _WPA2_IE_ID_)) अणु
		/*copy fixed ie*/
		स_नकल(out_ie, in_ie, 12);
		ielength = 12;
		/*copy RSN or SSN*/
		अगर (match) अणु
			स_नकल(&out_ie[ielength], &sec_ie[0], sec_ie[1] + 2);
			ielength += sec_ie[1] + 2;
			अगर (authmode == _WPA2_IE_ID_) अणु
				/*the Pre-Authentication bit should be zero*/
				out_ie[ielength - 1] = 0;
				out_ie[ielength - 2] = 0;
			पूर्ण
			r8712_report_sec_ie(adapter, authmode, sec_ie);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*copy fixed ie only*/
		स_नकल(out_ie, in_ie, 12);
		ielength = 12;
		अगर (psecuritypriv->wps_phase) अणु
			स_नकल(out_ie + ielength, psecuritypriv->wps_ie,
			       psecuritypriv->wps_ie_len);
			ielength += psecuritypriv->wps_ie_len;
		पूर्ण
	पूर्ण
	iEntry = SecIsInPMKIDList(adapter, pmlmepriv->assoc_bssid);
	अगर (iEntry < 0)
		वापस ielength;
	अगर (authmode == _WPA2_IE_ID_) अणु
		out_ie[ielength] = 1;
		ielength++;
		out_ie[ielength] = 0;	/*PMKID count = 0x0100*/
		ielength++;
		स_नकल(&out_ie[ielength],
			&psecuritypriv->PMKIDList[iEntry].PMKID, 16);
		ielength += 16;
		out_ie[13] += 18;/*PMKID length = 2+16*/
	पूर्ण
	वापस ielength;
पूर्ण

व्योम r8712_init_registrypriv_dev_network(काष्ठा _adapter *adapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &adapter->registrypriv;
	काष्ठा eeprom_priv *peepriv = &adapter->eeprompriv;
	काष्ठा wlan_bssid_ex *pdev_network = &pregistrypriv->dev_network;
	u8 *myhwaddr = myid(peepriv);

	स_नकल(pdev_network->MacAddress, myhwaddr, ETH_ALEN);
	स_नकल(&pdev_network->Ssid, &pregistrypriv->ssid,
		माप(काष्ठा ndis_802_11_ssid));
	pdev_network->Configuration.Length =
			 माप(काष्ठा NDIS_802_11_CONFIGURATION);
	pdev_network->Configuration.BeaconPeriod = 100;
	pdev_network->Configuration.FHConfig.Length = 0;
	pdev_network->Configuration.FHConfig.HopPattern = 0;
	pdev_network->Configuration.FHConfig.HopSet = 0;
	pdev_network->Configuration.FHConfig.DwellTime = 0;
पूर्ण

व्योम r8712_update_registrypriv_dev_network(काष्ठा _adapter *adapter)
अणु
	पूर्णांक sz = 0;
	काष्ठा registry_priv	*pregistrypriv = &adapter->registrypriv;
	काष्ठा wlan_bssid_ex	*pdev_network = &pregistrypriv->dev_network;
	काष्ठा security_priv	*psecuritypriv = &adapter->securitypriv;
	काष्ठा wlan_network	*cur_network = &adapter->mlmepriv.cur_network;

	pdev_network->Privacy = cpu_to_le32(psecuritypriv->PrivacyAlgrthm
					    > 0 ? 1 : 0); /* adhoc no 802.1x */
	pdev_network->Rssi = 0;
	चयन (pregistrypriv->wireless_mode) अणु
	हाल WIRELESS_11B:
		pdev_network->NetworkTypeInUse = Ndis802_11DS;
		अवरोध;
	हाल WIRELESS_11G:
	हाल WIRELESS_11BG:
		pdev_network->NetworkTypeInUse = Ndis802_11OFDM24;
		अवरोध;
	हाल WIRELESS_11A:
		pdev_network->NetworkTypeInUse = Ndis802_11OFDM5;
		अवरोध;
	शेष:
		/* TODO */
		अवरोध;
	पूर्ण
	pdev_network->Configuration.DSConfig = pregistrypriv->channel;
	अगर (cur_network->network.Infraकाष्ठाureMode == Ndis802_11IBSS)
		pdev_network->Configuration.ATIMWinकरोw = 3;
	pdev_network->Infraकाष्ठाureMode = cur_network->network.Infraकाष्ठाureMode;
	/* 1. Supported rates
	 * 2. IE
	 */
	sz = r8712_generate_ie(pregistrypriv);
	pdev_network->IELength = sz;
	pdev_network->Length = r8712_get_wlan_bssid_ex_sz(pdev_network);
पूर्ण

/*the function is at passive_level*/
व्योम r8712_joinbss_reset(काष्ठा _adapter *padapter)
अणु
	पूर्णांक i;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv		*phtpriv = &pmlmepriv->htpriv;

	/* toकरो: अगर you want to करो something io/reg/hw setting beक्रमe join_bss,
	 * please add code here
	 */
	phtpriv->ampdu_enable = false;/*reset to disabled*/
	क्रम (i = 0; i < 16; i++)
		phtpriv->baddbareq_issued[i] = false;/*reset it*/
	अगर (phtpriv->ht_option) अणु
		/* validate  usb rx aggregation */
		r8712_ग_लिखो8(padapter, 0x102500D9, 48);/*TH = 48 pages, 6k*/
	पूर्ण अन्यथा अणु
		/* invalidate  usb rx aggregation */
		/* TH=1 => means that invalidate usb rx aggregation */
		r8712_ग_लिखो8(padapter, 0x102500D9, 1);
	पूर्ण
पूर्ण

/*the function is >= passive_level*/
अचिन्हित पूर्णांक r8712_reकाष्ठाure_ht_ie(काष्ठा _adapter *padapter, u8 *in_ie,
				     u8 *out_ie, uपूर्णांक in_len, uपूर्णांक *pout_len)
अणु
	u32 ielen, out_len;
	अचिन्हित अक्षर *p;
	काष्ठा ieee80211_ht_cap ht_capie;
	अचिन्हित अक्षर WMM_IE[] = अणु0x00, 0x50, 0xf2, 0x02, 0x00, 0x01, 0x00पूर्ण;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv *pqospriv = &pmlmepriv->qospriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;

	phtpriv->ht_option = 0;
	p = r8712_get_ie(in_ie + 12, WLAN_EID_HT_CAPABILITY, &ielen, in_len - 12);
	अगर (p && (ielen > 0)) अणु
		अगर (pqospriv->qos_option == 0) अणु
			out_len = *pout_len;
			r8712_set_ie(out_ie + out_len, WLAN_EID_VENDOR_SPECIFIC,
				     _WMM_IE_Length_, WMM_IE, pout_len);
			pqospriv->qos_option = 1;
		पूर्ण
		out_len = *pout_len;
		स_रखो(&ht_capie, 0, माप(काष्ठा ieee80211_ht_cap));
		ht_capie.cap_info = cpu_to_le16(IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
				    IEEE80211_HT_CAP_SGI_20 |
				    IEEE80211_HT_CAP_SGI_40 |
				    IEEE80211_HT_CAP_TX_STBC |
				    IEEE80211_HT_CAP_MAX_AMSDU |
				    IEEE80211_HT_CAP_DSSSCCK40);
		ht_capie.ampdu_params_info = (IEEE80211_HT_AMPDU_PARM_FACTOR &
				0x03) | (IEEE80211_HT_AMPDU_PARM_DENSITY & 0x00);
		r8712_set_ie(out_ie + out_len, WLAN_EID_HT_CAPABILITY,
			     माप(काष्ठा ieee80211_ht_cap),
			     (अचिन्हित अक्षर *)&ht_capie, pout_len);
		phtpriv->ht_option = 1;
	पूर्ण
	वापस phtpriv->ht_option;
पूर्ण

/* the function is > passive_level (in critical_section) */
अटल व्योम update_ht_cap(काष्ठा _adapter *padapter, u8 *pie, uपूर्णांक ie_len)
अणु
	u8 *p, max_ampdu_sz;
	पूर्णांक i;
	uपूर्णांक len;
	काष्ठा sta_info *bmc_sta, *psta;
	काष्ठा ieee80211_ht_cap *pht_capie;
	काष्ठा recv_reorder_ctrl *preorder_ctrl;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	काष्ठा wlan_network *pcur_network = &(pmlmepriv->cur_network);

	अगर (!phtpriv->ht_option)
		वापस;
	/* maybe needs check अगर ap supports rx ampdu. */
	अगर (!phtpriv->ampdu_enable &&
	    (pregistrypriv->ampdu_enable == 1))
		phtpriv->ampdu_enable = true;
	/*check Max Rx A-MPDU Size*/
	len = 0;
	p = r8712_get_ie(pie + माप(काष्ठा NDIS_802_11_FIXED_IEs),
				WLAN_EID_HT_CAPABILITY,
				&len, ie_len -
				माप(काष्ठा NDIS_802_11_FIXED_IEs));
	अगर (p && len > 0) अणु
		pht_capie = (काष्ठा ieee80211_ht_cap *)(p + 2);
		max_ampdu_sz = (pht_capie->ampdu_params_info &
				IEEE80211_HT_AMPDU_PARM_FACTOR);
		/* max_ampdu_sz (kbytes); */
		max_ampdu_sz = 1 << (max_ampdu_sz + 3);
		phtpriv->rx_ampdu_maxlen = max_ampdu_sz;
	पूर्ण
	/* क्रम A-MPDU Rx reordering buffer control क्रम bmc_sta & sta_info
	 * अगर A-MPDU Rx is enabled, resetting rx_ordering_ctrl
	 * wstart_b(indicate_seq) to शेष value=0xffff
	 * toकरो: check अगर AP can send A-MPDU packets
	 */
	bmc_sta = r8712_get_bcmc_stainfo(padapter);
	अगर (bmc_sta) अणु
		क्रम (i = 0; i < 16; i++) अणु
			preorder_ctrl = &bmc_sta->recvreorder_ctrl[i];
			preorder_ctrl->indicate_seq = 0xffff;
			preorder_ctrl->wend_b = 0xffff;
		पूर्ण
	पूर्ण
	psta = r8712_get_stainfo(&padapter->stapriv,
				 pcur_network->network.MacAddress);
	अगर (psta) अणु
		क्रम (i = 0; i < 16; i++) अणु
			preorder_ctrl = &psta->recvreorder_ctrl[i];
			preorder_ctrl->indicate_seq = 0xffff;
			preorder_ctrl->wend_b = 0xffff;
		पूर्ण
	पूर्ण
	len = 0;
	p = r8712_get_ie(pie + माप(काष्ठा NDIS_802_11_FIXED_IEs),
		   WLAN_EID_HT_OPERATION, &len,
		   ie_len - माप(काष्ठा NDIS_802_11_FIXED_IEs));
पूर्ण

व्योम r8712_issue_addbareq_cmd(काष्ठा _adapter *padapter, पूर्णांक priority)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv	 *phtpriv = &pmlmepriv->htpriv;

	अगर ((phtpriv->ht_option == 1) && (phtpriv->ampdu_enable)) अणु
		अगर (!phtpriv->baddbareq_issued[priority]) अणु
			r8712_addbareq_cmd(padapter, (u8)priority);
			phtpriv->baddbareq_issued[priority] = true;
		पूर्ण
	पूर्ण
पूर्ण
