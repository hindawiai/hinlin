<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_XMIT_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <mon.h>
#समावेश <wअगरi.h>
#समावेश <osdep_पूर्णांकf.h>
#समावेश <linux/vदो_स्मृति.h>

अटल u8 P802_1H_OUI[P80211_OUI_LEN] = अणु 0x00, 0x00, 0xf8 पूर्ण;
अटल u8 RFC1042_OUI[P80211_OUI_LEN] = अणु 0x00, 0x00, 0x00 पूर्ण;

अटल व्योम _init_txservq(काष्ठा tx_servq *ptxservq)
अणु
	INIT_LIST_HEAD(&ptxservq->tx_pending);
	_rtw_init_queue(&ptxservq->sta_pending);
	ptxservq->qcnt = 0;
पूर्ण

व्योम _rtw_init_sta_xmit_priv(काष्ठा sta_xmit_priv *psta_xmitpriv)
अणु
	स_रखो((अचिन्हित अक्षर *)psta_xmitpriv, 0, माप(काष्ठा sta_xmit_priv));
	spin_lock_init(&psta_xmitpriv->lock);
	_init_txservq(&psta_xmitpriv->be_q);
	_init_txservq(&psta_xmitpriv->bk_q);
	_init_txservq(&psta_xmitpriv->vi_q);
	_init_txservq(&psta_xmitpriv->vo_q);
	INIT_LIST_HEAD(&psta_xmitpriv->legacy_dz);
	INIT_LIST_HEAD(&psta_xmitpriv->apsd);
पूर्ण

s32 _rtw_init_xmit_priv(काष्ठा xmit_priv *pxmitpriv, काष्ठा adapter *padapter)
अणु
	पूर्णांक i;
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा xmit_frame *pxframe;
	पूर्णांक res = _SUCCESS;
	u32 max_xmit_extbuf_size = MAX_XMIT_EXTBUF_SZ;
	u32 num_xmit_extbuf = NR_XMIT_EXTBUFF;

	/*
	 * We करोn't need to स_रखो padapter->XXX to zero because adapter is
	 * allocated by alloc_etherdev_mq, which eventually calls kvzalloc.
	 */

	spin_lock_init(&pxmitpriv->lock);

	/*
	 * Please insert all the queue initializaiton using _rtw_init_queue below
	 */

	pxmitpriv->adapter = padapter;

	_rtw_init_queue(&pxmitpriv->be_pending);
	_rtw_init_queue(&pxmitpriv->bk_pending);
	_rtw_init_queue(&pxmitpriv->vi_pending);
	_rtw_init_queue(&pxmitpriv->vo_pending);
	_rtw_init_queue(&pxmitpriv->bm_pending);

	_rtw_init_queue(&pxmitpriv->मुक्त_xmit_queue);

	/*
	 * Please allocate memory with the sz = (काष्ठा xmit_frame) * NR_XMITFRAME,
	 * and initialize मुक्त_xmit_frame below.
	 * Please also apply  मुक्त_txobj to link_up all the xmit_frames...
	 */

	pxmitpriv->pallocated_frame_buf = vzalloc(NR_XMITFRAME * माप(काष्ठा xmit_frame) + 4);

	अगर (!pxmitpriv->pallocated_frame_buf) अणु
		pxmitpriv->pxmit_frame_buf = शून्य;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("alloc xmit_frame fail!\n"));
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	pxmitpriv->pxmit_frame_buf = PTR_ALIGN(pxmitpriv->pallocated_frame_buf, 4);

	pxframe = (काष्ठा xmit_frame *)pxmitpriv->pxmit_frame_buf;

	क्रम (i = 0; i < NR_XMITFRAME; i++) अणु
		INIT_LIST_HEAD(&pxframe->list);

		pxframe->padapter = padapter;
		pxframe->frame_tag = शून्य_FRAMETAG;

		pxframe->pkt = शून्य;

		pxframe->buf_addr = शून्य;
		pxframe->pxmitbuf = शून्य;

		list_add_tail(&pxframe->list, &pxmitpriv->मुक्त_xmit_queue.queue);

		pxframe++;
	पूर्ण

	pxmitpriv->मुक्त_xmitframe_cnt = NR_XMITFRAME;

	pxmitpriv->frag_len = MAX_FRAG_THRESHOLD;

	/* init xmit_buf */
	_rtw_init_queue(&pxmitpriv->मुक्त_xmitbuf_queue);
	_rtw_init_queue(&pxmitpriv->pending_xmitbuf_queue);

	pxmitpriv->pallocated_xmitbuf = vzalloc(NR_XMITBUFF * माप(काष्ठा xmit_buf) + 4);

	अगर (!pxmitpriv->pallocated_xmitbuf) अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("alloc xmit_buf fail!\n"));
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pxmitpriv->pxmitbuf = PTR_ALIGN(pxmitpriv->pallocated_xmitbuf, 4);

	pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmitbuf;

	क्रम (i = 0; i < NR_XMITBUFF; i++) अणु
		INIT_LIST_HEAD(&pxmitbuf->list);

		pxmitbuf->priv_data = शून्य;
		pxmitbuf->padapter = padapter;
		pxmitbuf->ext_tag = false;

		/* Tx buf allocation may fail someबार, so sleep and retry. */
		res = rtw_os_xmit_resource_alloc(pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ));
		अगर (res == _FAIL) अणु
			msleep(10);
			res = rtw_os_xmit_resource_alloc(pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ));
			अगर (res == _FAIL)
				जाओ निकास;
		पूर्ण

		pxmitbuf->flags = XMIT_VO_QUEUE;

		list_add_tail(&pxmitbuf->list, &pxmitpriv->मुक्त_xmitbuf_queue.queue);
		pxmitbuf++;
	पूर्ण

	pxmitpriv->मुक्त_xmitbuf_cnt = NR_XMITBUFF;

	/*  Init xmit extension buff */
	_rtw_init_queue(&pxmitpriv->मुक्त_xmit_extbuf_queue);

	pxmitpriv->pallocated_xmit_extbuf = vzalloc(num_xmit_extbuf * माप(काष्ठा xmit_buf) + 4);

	अगर (!pxmitpriv->pallocated_xmit_extbuf) अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("alloc xmit_extbuf fail!\n"));
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pxmitpriv->pxmit_extbuf = PTR_ALIGN(pxmitpriv->pallocated_xmit_extbuf, 4);

	pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmit_extbuf;

	क्रम (i = 0; i < num_xmit_extbuf; i++) अणु
		INIT_LIST_HEAD(&pxmitbuf->list);

		pxmitbuf->priv_data = शून्य;
		pxmitbuf->padapter = padapter;
		pxmitbuf->ext_tag = true;

		res = rtw_os_xmit_resource_alloc(pxmitbuf, max_xmit_extbuf_size + XMITBUF_ALIGN_SZ);
		अगर (res == _FAIL) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		list_add_tail(&pxmitbuf->list, &pxmitpriv->मुक्त_xmit_extbuf_queue.queue);
		pxmitbuf++;
	पूर्ण

	pxmitpriv->मुक्त_xmit_extbuf_cnt = num_xmit_extbuf;

	res = rtw_alloc_hwxmits(padapter);
	अगर (res == _FAIL)
		जाओ निकास;
	rtw_init_hwxmits(pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);

	क्रम (i = 0; i < 4; i++)
		pxmitpriv->wmm_para_seq[i] = i;

	pxmitpriv->txirp_cnt = 1;

	/* per AC pending irp */
	pxmitpriv->beq_cnt = 0;
	pxmitpriv->bkq_cnt = 0;
	pxmitpriv->viq_cnt = 0;
	pxmitpriv->voq_cnt = 0;

	pxmitpriv->ack_tx = false;
	mutex_init(&pxmitpriv->ack_tx_mutex);
	rtw_sctx_init(&pxmitpriv->ack_tx_ops, 0);

	rtw_hal_init_xmit_priv(padapter);

निकास:
	वापस res;
पूर्ण

व्योम _rtw_मुक्त_xmit_priv(काष्ठा xmit_priv *pxmitpriv)
अणु
	पूर्णांक i;
	काष्ठा adapter *padapter = pxmitpriv->adapter;
	काष्ठा xmit_frame *pxmitframe = (काष्ठा xmit_frame *)pxmitpriv->pxmit_frame_buf;
	काष्ठा xmit_buf *pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmitbuf;
	u32 num_xmit_extbuf = NR_XMIT_EXTBUFF;

	अगर (!pxmitpriv->pxmit_frame_buf)
		वापस;

	क्रम (i = 0; i < NR_XMITFRAME; i++) अणु
		rtw_os_xmit_complete(padapter, pxmitframe);

		pxmitframe++;
	पूर्ण

	क्रम (i = 0; i < NR_XMITBUFF; i++) अणु
		rtw_os_xmit_resource_मुक्त(pxmitbuf);
		pxmitbuf++;
	पूर्ण

	vमुक्त(pxmitpriv->pallocated_frame_buf);
	vमुक्त(pxmitpriv->pallocated_xmitbuf);

	/*  मुक्त xmit extension buff */
	pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmit_extbuf;
	क्रम (i = 0; i < num_xmit_extbuf; i++) अणु
		rtw_os_xmit_resource_मुक्त(pxmitbuf);
		pxmitbuf++;
	पूर्ण

	vमुक्त(pxmitpriv->pallocated_xmit_extbuf);

	rtw_मुक्त_hwxmits(padapter);

	mutex_destroy(&pxmitpriv->ack_tx_mutex);
पूर्ण

अटल व्योम update_attrib_vcs_info(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	u32	sz;
	काष्ठा pkt_attrib	*pattrib = &pxmitframe->attrib;
	काष्ठा sta_info	*psta = pattrib->psta;
	काष्ठा mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (pattrib->nr_frags != 1)
		sz = padapter->xmitpriv.frag_len;
	अन्यथा /* no frag */
		sz = pattrib->last_txcmdsz;

	/* (1) RTS_Threshold is compared to the MPDU, not MSDU.
	 * (2) If there are more than one frag in this MSDU,
	 *     only the first frag uses protection frame.
	 * Other fragments are रक्षित by previous fragment.
	 * So we only need to check the length of first fragment.
	 */
	अगर (pmlmeext->cur_wireless_mode < WIRELESS_11_24N  || padapter->registrypriv.wअगरi_spec) अणु
		अगर (sz > padapter->registrypriv.rts_thresh) अणु
			pattrib->vcs_mode = RTS_CTS;
		पूर्ण अन्यथा अणु
			अगर (psta->rtsen)
				pattrib->vcs_mode = RTS_CTS;
			अन्यथा अगर (psta->cts2self)
				pattrib->vcs_mode = CTS_TO_SELF;
			अन्यथा
				pattrib->vcs_mode = NONE_VCS;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (true) अणु
			/* IOT action */
			अगर ((pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_ATHEROS) && pattrib->ampdu_en &&
			    (padapter->securitypriv.करोt11PrivacyAlgrthm == _AES_)) अणु
				pattrib->vcs_mode = CTS_TO_SELF;
				अवरोध;
			पूर्ण

			/* check ERP protection */
			अगर (psta->rtsen || psta->cts2self) अणु
				अगर (psta->rtsen)
					pattrib->vcs_mode = RTS_CTS;
				अन्यथा अगर (psta->cts2self)
					pattrib->vcs_mode = CTS_TO_SELF;

				अवरोध;
			पूर्ण

			/* check HT op mode */
			अगर (pattrib->ht_en) अणु
				u8 htopmode = pmlmeinfo->HT_protection;

				अगर ((pmlmeext->cur_bwmode && (htopmode == 2 || htopmode == 3)) ||
				    (!pmlmeext->cur_bwmode && htopmode == 3)) अणु
					pattrib->vcs_mode = RTS_CTS;
					अवरोध;
				पूर्ण
			पूर्ण

			/* check rts */
			अगर (sz > padapter->registrypriv.rts_thresh) अणु
				pattrib->vcs_mode = RTS_CTS;
				अवरोध;
			पूर्ण

			/* to करो list: check MIMO घातer save condition. */

			/* check AMPDU aggregation क्रम TXOP */
			अगर (pattrib->ampdu_en) अणु
				pattrib->vcs_mode = RTS_CTS;
				अवरोध;
			पूर्ण

			pattrib->vcs_mode = NONE_VCS;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम update_attrib_phy_info(काष्ठा pkt_attrib *pattrib, काष्ठा sta_info *psta)
अणु
	pattrib->mdata = 0;
	pattrib->eosp = 0;
	pattrib->triggered = 0;

	/* qos_en, ht_en, init rate, , bw, ch_offset, sgi */
	pattrib->qos_en = psta->qos_option;

	pattrib->raid = psta->raid;
	pattrib->ht_en = psta->htpriv.ht_option;
	pattrib->bwmode = psta->htpriv.bwmode;
	pattrib->ch_offset = psta->htpriv.ch_offset;
	pattrib->sgi = psta->htpriv.sgi;
	pattrib->ampdu_en = false;
	pattrib->retry_ctrl = false;
पूर्ण

u8 qos_acm(u8 acm_mask, u8 priority)
अणु
	u8 change_priority = priority;

	चयन (priority) अणु
	हाल 0:
	हाल 3:
		अगर (acm_mask & BIT(1))
			change_priority = 1;
		अवरोध;
	हाल 1:
	हाल 2:
		अवरोध;
	हाल 4:
	हाल 5:
		अगर (acm_mask & BIT(2))
			change_priority = 0;
		अवरोध;
	हाल 6:
	हाल 7:
		अगर (acm_mask & BIT(3))
			change_priority = 5;
		अवरोध;
	शेष:
		DBG_88E("%s(): invalid pattrib->priority: %d!!!\n",
			__func__, priority);
		अवरोध;
	पूर्ण

	वापस change_priority;
पूर्ण

अटल व्योम set_qos(काष्ठा sk_buff *skb, काष्ठा pkt_attrib *pattrib)
अणु
	अगर (pattrib->ether_type == 0x0800) अणु
		काष्ठा iphdr ip_hdr;

		skb_copy_bits(skb, ETH_HLEN, &ip_hdr, माप(ip_hdr));
		pattrib->priority = ip_hdr.tos >> 5;
	पूर्ण अन्यथा अगर (pattrib->ether_type == ETH_P_PAE) अणु
		/* When priority processing of data frames is supported,
		 * a STA's SME should send EAPOL-Key frames at the highest
		 * priority.
		 */
		pattrib->priority = 7;
	पूर्ण अन्यथा अणु
		pattrib->priority = 0;
	पूर्ण

	pattrib->hdrlen = WLAN_HDR_A3_QOS_LEN;
	pattrib->subtype = WIFI_QOS_DATA_TYPE;
पूर्ण

अटल s32 update_attrib(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt, काष्ठा pkt_attrib *pattrib)
अणु
	काष्ठा sta_info *psta = शून्य;
	काष्ठा ethhdr etherhdr;

	bool mcast;
	काष्ठा sta_priv		*pstapriv = &padapter->stapriv;
	काष्ठा security_priv	*psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv		*pqospriv = &pmlmepriv->qospriv;
	पूर्णांक res = _SUCCESS;

	skb_copy_bits(pkt, 0, &etherhdr, ETH_HLEN);

	pattrib->ether_type = ntohs(etherhdr.h_proto);

	स_नकल(pattrib->dst, &etherhdr.h_dest, ETH_ALEN);
	स_नकल(pattrib->src, &etherhdr.h_source, ETH_ALEN);

	pattrib->pctrl = 0;

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
		स_नकल(pattrib->ra, pattrib->dst, ETH_ALEN);
		स_नकल(pattrib->ta, pattrib->src, ETH_ALEN);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
		स_नकल(pattrib->ra, get_bssid(pmlmepriv), ETH_ALEN);
		स_नकल(pattrib->ta, pattrib->src, ETH_ALEN);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		स_नकल(pattrib->ra, pattrib->dst, ETH_ALEN);
		स_नकल(pattrib->ta, get_bssid(pmlmepriv), ETH_ALEN);
	पूर्ण

	pattrib->pktlen = pkt->len - ETH_HLEN;

	अगर (pattrib->ether_type == ETH_P_IP) अणु
		/* The following is क्रम DHCP and ARP packet, we use
		 * cck1M to tx these packets and let LPS awake some
		 * समय to prevent DHCP protocol fail.
		 */
		u8 पंचांगp[24];

		skb_copy_bits(pkt, ETH_HLEN, पंचांगp, 24);

		pattrib->dhcp_pkt = 0;
		अगर (pkt->len > ETH_HLEN + 24 + 282) अणु/* MINIMUM_DHCP_PACKET_SIZE) अणु */
			अगर (pattrib->ether_type == ETH_P_IP) अणु/*  IP header */
				अगर (((पंचांगp[21] == 68) && (पंचांगp[23] == 67)) ||
				    ((पंचांगp[21] == 67) && (पंचांगp[23] == 68))) अणु
					/*  68 : UDP BOOTP client */
					/*  67 : UDP BOOTP server */
					RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("====================== %s: get DHCP Packet\n", __func__));
					/*  Use low rate to send DHCP packet. */
					pattrib->dhcp_pkt = 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (pattrib->ether_type == ETH_P_PAE) अणु
		DBG_88E_LEVEL(_drv_info_, "send eapol packet\n");
	पूर्ण

	अगर ((pattrib->ether_type == ETH_P_PAE) || (pattrib->dhcp_pkt == 1))
		rtw_set_scan_deny(padapter, 3000);

	/*  If EAPOL , ARP , OR DHCP packet, driver must be in active mode. */
	अगर ((pattrib->ether_type == ETH_P_ARP) || (pattrib->ether_type == ETH_P_PAE) || (pattrib->dhcp_pkt == 1))
		rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_SPECIAL_PACKET, 1);

	mcast = is_multicast_ether_addr(pattrib->ra);

	/*  get sta_info */
	अगर (mcast) अणु
		psta = rtw_get_bcmc_stainfo(padapter);
	पूर्ण अन्यथा अणु
		psta = rtw_get_stainfo(pstapriv, pattrib->ra);
		अगर (!psta) अणु /*  अगर we cannot get psta => drrp the pkt */
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_alert_, ("\nupdate_attrib => get sta_info fail, ra: %pM\n", (pattrib->ra)));
			res = _FAIL;
			जाओ निकास;
		पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) &&
			   !(psta->state & _FW_LINKED)) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (psta) अणु
		pattrib->mac_id = psta->mac_id;
		/* DBG_88E("%s ==> mac_id(%d)\n", __func__, pattrib->mac_id); */
		pattrib->psta = psta;
	पूर्ण अन्यथा अणु
		/*  अगर we cannot get psta => drop the pkt */
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_alert_, ("\nupdate_attrib => get sta_info fail, ra:%pM\n", (pattrib->ra)));
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pattrib->ack_policy = 0;

	pattrib->hdrlen = WLAN_HDR_A3_LEN;
	pattrib->subtype = WIFI_DATA_TYPE;
	pattrib->priority = 0;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE |
			  WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE)) अणु
		अगर (psta->qos_option)
			set_qos(pkt, pattrib);
	पूर्ण अन्यथा अणु
		अगर (pqospriv->qos_option) अणु
			set_qos(pkt, pattrib);

			अगर (pmlmepriv->acm_mask != 0)
				pattrib->priority = qos_acm(pmlmepriv->acm_mask, pattrib->priority);
		पूर्ण
	पूर्ण

	अगर (psta->ieee8021x_blocked) अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("\n psta->ieee8021x_blocked == true\n"));

		pattrib->encrypt = 0;

		अगर (pattrib->ether_type != ETH_P_PAE) अणु
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("\npsta->ieee8021x_blocked == true,  pattrib->ether_type(%.4x) != ETH_P_PAE\n", pattrib->ether_type));
			res = _FAIL;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt, mcast);

		चयन (psecuritypriv->करोt11AuthAlgrthm) अणु
		हाल करोt11AuthAlgrthm_Open:
		हाल करोt11AuthAlgrthm_Shared:
		हाल करोt11AuthAlgrthm_Auto:
			pattrib->key_idx = (u8)psecuritypriv->करोt11PrivacyKeyIndex;
			अवरोध;
		हाल करोt11AuthAlgrthm_8021X:
			अगर (mcast)
				pattrib->key_idx = (u8)psecuritypriv->करोt118021XGrpKeyid;
			अन्यथा
				pattrib->key_idx = 0;
			अवरोध;
		शेष:
			pattrib->key_idx = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (pattrib->encrypt) अणु
	हाल _WEP40_:
	हाल _WEP104_:
		pattrib->iv_len = 4;
		pattrib->icv_len = 4;
		अवरोध;
	हाल _TKIP_:
		pattrib->iv_len = 8;
		pattrib->icv_len = 4;

		अगर (padapter->securitypriv.busetkipkey == _FAIL) अणु
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_,
				 ("\npadapter->securitypriv.busetkipkey(%d) == _FAIL drop packet\n",
				 padapter->securitypriv.busetkipkey));
			res = _FAIL;
			जाओ निकास;
		पूर्ण
		अवरोध;
	हाल _AES_:
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("pattrib->encrypt=%d (_AES_)\n", pattrib->encrypt));
		pattrib->iv_len = 8;
		pattrib->icv_len = 8;
		अवरोध;
	शेष:
		pattrib->iv_len = 0;
		pattrib->icv_len = 0;
		अवरोध;
	पूर्ण

	RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
		 ("%s: encrypt=%d\n", __func__, pattrib->encrypt));

	अगर (pattrib->encrypt && !psecuritypriv->hw_decrypted) अणु
		pattrib->bswenc = true;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_,
			 ("%s: encrypt=%d bswenc = true\n", __func__,
			  pattrib->encrypt));
	पूर्ण अन्यथा अणु
		pattrib->bswenc = false;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("%s: bswenc = false\n", __func__));
	पूर्ण

	update_attrib_phy_info(pattrib, psta);

निकास:
	वापस res;
पूर्ण

अटल s32 xmitframe_addmic(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	पूर्णांक curfragnum, length;
	u8	*pframe, *payload, mic[8];
	काष्ठा	mic_data micdata;
	काष्ठा	sta_info *stainfo;
	काष्ठा	pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा	security_priv	*psecuritypriv = &padapter->securitypriv;
	काष्ठा	xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u8 priority[4] = अणुपूर्ण;
	u8 hw_hdr_offset = 0;

	अगर (pattrib->psta)
		stainfo = pattrib->psta;
	अन्यथा
		stainfo = rtw_get_stainfo(&padapter->stapriv, &pattrib->ra[0]);

	hw_hdr_offset = TXDESC_SIZE + (pxmitframe->pkt_offset * PACKET_OFFSET_SZ);

	अगर (pattrib->encrypt == _TKIP_) अणु
		/* encode mic code */
		अगर (stainfo) अणु
			u8 null_key[16] = अणुपूर्ण;

			pframe = pxmitframe->buf_addr + hw_hdr_offset;

			अगर (is_multicast_ether_addr(pattrib->ra)) अणु
				अगर (!स_भेद(psecuritypriv->करोt118021XGrptxmickey[psecuritypriv->करोt118021XGrpKeyid].skey, null_key, 16))
					वापस _FAIL;
				/* start to calculate the mic code */
				rtw_secmicsetkey(&micdata, psecuritypriv->करोt118021XGrptxmickey[psecuritypriv->करोt118021XGrpKeyid].skey);
			पूर्ण अन्यथा अणु
				अगर (!स_भेद(&stainfo->करोt11tkiptxmickey.skey[0], null_key, 16))
					वापस _FAIL;
				/* start to calculate the mic code */
				rtw_secmicsetkey(&micdata, &stainfo->करोt11tkiptxmickey.skey[0]);
			पूर्ण

			अगर (pframe[1] & 1) अणु   /* ToDS == 1 */
				rtw_secmicappend(&micdata, &pframe[16], 6);  /* DA */
				अगर (pframe[1] & 2)  /* From Ds == 1 */
					rtw_secmicappend(&micdata, &pframe[24], 6);
				अन्यथा
					rtw_secmicappend(&micdata, &pframe[10], 6);
			पूर्ण अन्यथा अणु	/* ToDS == 0 */
				rtw_secmicappend(&micdata, &pframe[4], 6);   /* DA */
				अगर (pframe[1] & 2)  /* From Ds == 1 */
					rtw_secmicappend(&micdata, &pframe[16], 6);
				अन्यथा
					rtw_secmicappend(&micdata, &pframe[10], 6);
			पूर्ण

			अगर (pattrib->qos_en)
				priority[0] = (u8)pxmitframe->attrib.priority;

			rtw_secmicappend(&micdata, &priority[0], 4);

			payload = pframe;

			क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) अणु
				payload = (u8 *)round_up((माप_प्रकार)(payload), 4);
				RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_,
					 ("=== curfragnum=%d, pframe = 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x,!!!\n",
					 curfragnum, *payload, *(payload + 1),
					 *(payload + 2), *(payload + 3),
					 *(payload + 4), *(payload + 5),
					 *(payload + 6), *(payload + 7)));

				payload += pattrib->hdrlen + pattrib->iv_len;
				RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_,
					 ("curfragnum=%d pattrib->hdrlen=%d pattrib->iv_len=%d",
					 curfragnum, pattrib->hdrlen, pattrib->iv_len));
				अगर (curfragnum + 1 == pattrib->nr_frags) अणु
					length = pattrib->last_txcmdsz -
						 pattrib->hdrlen -
						 pattrib->iv_len -
						 ((pattrib->bswenc) ?
						  pattrib->icv_len : 0);
					rtw_secmicappend(&micdata, payload, length);
					payload += length;
				पूर्ण अन्यथा अणु
					length = pxmitpriv->frag_len -
						 pattrib->hdrlen -
						 pattrib->iv_len -
						 ((pattrib->bswenc) ?
						  pattrib->icv_len : 0);
					rtw_secmicappend(&micdata, payload, length);
					payload += length + pattrib->icv_len;
					RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("curfragnum=%d length=%d pattrib->icv_len=%d", curfragnum, length, pattrib->icv_len));
				पूर्ण
			पूर्ण
			rtw_secgeपंचांगic(&micdata, &mic[0]);
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("%s: before add mic code!!!\n", __func__));
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("%s: pattrib->last_txcmdsz=%d!!!\n", __func__, pattrib->last_txcmdsz));
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("%s: mic[0]=0x%.2x , mic[1]=0x%.2x , mic[2]= 0x%.2x, mic[3]=0x%.2x\न\
  mic[4]= 0x%.2x , mic[5]= 0x%.2x , mic[6]= 0x%.2x , mic[7]= 0x%.2x !!!!\न",
				__func__, mic[0], mic[1], mic[2], mic[3], mic[4], mic[5], mic[6], mic[7]));
			/* add mic code  and add the mic code length in last_txcmdsz */

			स_नकल(payload, &mic[0], 8);
			pattrib->last_txcmdsz += 8;

			RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("\n ======== last pkt ========\n"));
			payload -= pattrib->last_txcmdsz + 8;
			क्रम (curfragnum = 0; curfragnum < pattrib->last_txcmdsz; curfragnum += 8)
				RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
					 (" %.2x,  %.2x,  %.2x,  %.2x,  %.2x,  %.2x,  %.2x,  %.2x ",
					 *(payload + curfragnum), *(payload + curfragnum + 1),
					 *(payload + curfragnum + 2), *(payload + curfragnum + 3),
					 *(payload + curfragnum + 4), *(payload + curfragnum + 5),
					 *(payload + curfragnum + 6), *(payload + curfragnum + 7)));
			पूर्ण अन्यथा अणु
				RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("%s: rtw_get_stainfo==NULL!!!\n", __func__));
			पूर्ण
	पूर्ण

	वापस _SUCCESS;
पूर्ण

अटल s32 xmitframe_swencrypt(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा	pkt_attrib	 *pattrib = &pxmitframe->attrib;

	अगर (pattrib->bswenc) अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_alert_, ("### %s\n", __func__));
		चयन (pattrib->encrypt) अणु
		हाल _WEP40_:
		हाल _WEP104_:
			rtw_wep_encrypt(padapter, pxmitframe);
			अवरोध;
		हाल _TKIP_:
			rtw_tkip_encrypt(padapter, pxmitframe);
			अवरोध;
		हाल _AES_:
			rtw_aes_encrypt(padapter, pxmitframe);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_notice_, ("### xmitframe_hwencrypt\n"));
	पूर्ण

	वापस _SUCCESS;
पूर्ण

s32 rtw_make_wlanhdr(काष्ठा adapter *padapter, u8 *hdr, काष्ठा pkt_attrib *pattrib)
अणु
	u16 *qc;

	काष्ठा ieee80211_hdr *pwlanhdr = (काष्ठा ieee80211_hdr *)hdr;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv *pqospriv = &pmlmepriv->qospriv;
	u8 qos_option = false;

	पूर्णांक res = _SUCCESS;
	__le16 *fctrl = &pwlanhdr->frame_control;

	काष्ठा sta_info *psta;

	अगर (pattrib->psta) अणु
		psta = pattrib->psta;
	पूर्ण अन्यथा अणु
		अगर (is_multicast_ether_addr(pattrib->ra))
			psta = rtw_get_bcmc_stainfo(padapter);
		अन्यथा
			psta = rtw_get_stainfo(&padapter->stapriv, pattrib->ra);
	पूर्ण

	स_रखो(hdr, 0, WLANHDR_OFFSET);

	SetFrameSubType(fctrl, pattrib->subtype);

	अगर (pattrib->subtype & WIFI_DATA_TYPE) अणु
		अगर (check_fwstate(pmlmepriv,  WIFI_STATION_STATE)) अणु
			/* to_ds = 1, fr_ds = 0; */
			/* Data transfer to AP */
			SetToDs(fctrl);
			स_नकल(pwlanhdr->addr1, get_bssid(pmlmepriv), ETH_ALEN);
			स_नकल(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
			स_नकल(pwlanhdr->addr3, pattrib->dst, ETH_ALEN);

			अगर (pqospriv->qos_option)
				qos_option = true;
		पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv,  WIFI_AP_STATE)) अणु
			/* to_ds = 0, fr_ds = 1; */
			SetFrDs(fctrl);
			स_नकल(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
			स_नकल(pwlanhdr->addr2, get_bssid(pmlmepriv), ETH_ALEN);
			स_नकल(pwlanhdr->addr3, pattrib->src, ETH_ALEN);

			अगर (psta && psta->qos_option)
				qos_option = true;
		पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) ||
			   check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
			स_नकल(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
			स_नकल(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
			स_नकल(pwlanhdr->addr3, get_bssid(pmlmepriv), ETH_ALEN);

			अगर (psta && psta->qos_option)
				qos_option = true;
		पूर्ण अन्यथा अणु
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("fw_state:%x is not allowed to xmit frame\n", get_fwstate(pmlmepriv)));
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		अगर (pattrib->mdata)
			SetMData(fctrl);

		अगर (pattrib->encrypt)
			SetPrivacy(fctrl);

		अगर (qos_option) अणु
			qc = (अचिन्हित लघु *)(hdr + pattrib->hdrlen - 2);

			अगर (pattrib->priority)
				SetPriority(qc, pattrib->priority);

			SetEOSP(qc, pattrib->eosp);

			SetAckpolicy(qc, pattrib->ack_policy);
		पूर्ण

		/* TODO: fill HT Control Field */

		/* Update Seq Num will be handled by f/w */
		अगर (psta) अणु
			psta->sta_xmitpriv.txseq_tid[pattrib->priority]++;
			psta->sta_xmitpriv.txseq_tid[pattrib->priority] &= 0xFFF;

			pattrib->seqnum = psta->sta_xmitpriv.txseq_tid[pattrib->priority];

			SetSeqNum(hdr, pattrib->seqnum);

			/* check अगर enable ampdu */
			अगर (pattrib->ht_en && psta->htpriv.ampdu_enable) अणु
				अगर (psta->htpriv.agg_enable_biपंचांगap & BIT(pattrib->priority))
					pattrib->ampdu_en = true;
			पूर्ण

			/* re-check अगर enable ampdu by BA_starting_seqctrl */
			अगर (pattrib->ampdu_en) अणु
				u16 tx_seq;

				tx_seq = psta->BA_starting_seqctrl[pattrib->priority & 0x0f];

				/* check BA_starting_seqctrl */
				अगर (SN_LESS(pattrib->seqnum, tx_seq)) अणु
					pattrib->ampdu_en = false;/* AGG BK */
				पूर्ण अन्यथा अगर (SN_EQUAL(pattrib->seqnum, tx_seq)) अणु
					psta->BA_starting_seqctrl[pattrib->priority & 0x0f] = (tx_seq + 1) & 0xfff;

					pattrib->ampdu_en = true;/* AGG EN */
				पूर्ण अन्यथा अणु
					psta->BA_starting_seqctrl[pattrib->priority & 0x0f] = (pattrib->seqnum + 1) & 0xfff;
					pattrib->ampdu_en = true;/* AGG EN */
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
निकास:

	वापस res;
पूर्ण

s32 rtw_txframes_pending(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	वापस (!list_empty(&pxmitpriv->be_pending.queue) ||
		!list_empty(&pxmitpriv->bk_pending.queue) ||
		!list_empty(&pxmitpriv->vi_pending.queue) ||
		!list_empty(&pxmitpriv->vo_pending.queue));
पूर्ण

s32 rtw_txframes_sta_ac_pending(काष्ठा adapter *padapter, काष्ठा pkt_attrib *pattrib)
अणु
	काष्ठा sta_info *psta;
	काष्ठा tx_servq *ptxservq;
	पूर्णांक priority = pattrib->priority;

	psta = pattrib->psta;

	चयन (priority) अणु
	हाल 1:
	हाल 2:
		ptxservq = &psta->sta_xmitpriv.bk_q;
		अवरोध;
	हाल 4:
	हाल 5:
		ptxservq = &psta->sta_xmitpriv.vi_q;
		अवरोध;
	हाल 6:
	हाल 7:
		ptxservq = &psta->sta_xmitpriv.vo_q;
		अवरोध;
	हाल 0:
	हाल 3:
	शेष:
		ptxservq = &psta->sta_xmitpriv.be_q;
		अवरोध;
	पूर्ण

	वापस ptxservq->qcnt;
पूर्ण

/*
 *
 * This sub-routine will perक्रमm all the following:
 *
 * 1. हटाओ 802.3 header.
 * 2. create wlan_header, based on the info in pxmitframe
 * 3. append sta's iv/ext-iv
 * 4. append LLC
 * 5. move frag chunk from pframe to pxmitframe->mem
 * 6. apply sw-encrypt, अगर necessary.
 *
 */
s32 rtw_xmitframe_coalesce(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt, काष्ठा xmit_frame *pxmitframe)
अणु
	s32 frg_inx, frg_len, mpdu_len, llc_sz, mem_sz;
	माप_प्रकार addr;
	u8 *pframe, *mem_start;
	u8 hw_hdr_offset;
	काष्ठा sta_info		*psta;
	काष्ठा xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	काष्ठा pkt_attrib	*pattrib = &pxmitframe->attrib;
	u8 *pbuf_start;
	bool mcast = is_multicast_ether_addr(pattrib->ra);
	s32 res = _SUCCESS;
	माप_प्रकार reमुख्यder = pkt->len - ETH_HLEN;

	psta = rtw_get_stainfo(&padapter->stapriv, pattrib->ra);

	अगर (!psta)
		वापस _FAIL;

	अगर (!pxmitframe->buf_addr) अणु
		DBG_88E("==> %s buf_addr == NULL\n", __func__);
		वापस _FAIL;
	पूर्ण

	pbuf_start = pxmitframe->buf_addr;

	hw_hdr_offset =  TXDESC_SIZE + (pxmitframe->pkt_offset * PACKET_OFFSET_SZ);

	mem_start = pbuf_start +	hw_hdr_offset;

	अगर (rtw_make_wlanhdr(padapter, mem_start, pattrib) == _FAIL) अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("%s: rtw_make_wlanhdr fail; drop pkt\n", __func__));
		DBG_88E("%s: rtw_make_wlanhdr fail; drop pkt\n", __func__);
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	frg_inx = 0;
	frg_len = pxmitpriv->frag_len - 4;/* 2346-4 = 2342 */

	जबतक (1) अणु
		llc_sz = 0;

		mpdu_len = frg_len;

		pframe = mem_start;

		SetMFrag(mem_start);

		pframe += pattrib->hdrlen;
		mpdu_len -= pattrib->hdrlen;

		/* adding icv, अगर necessary... */
		अगर (pattrib->iv_len) अणु
			चयन (pattrib->encrypt) अणु
			हाल _WEP40_:
			हाल _WEP104_:
				WEP_IV(pattrib->iv, psta->करोt11txpn, pattrib->key_idx);
				अवरोध;
			हाल _TKIP_:
				अगर (mcast)
					TKIP_IV(pattrib->iv, psta->करोt11txpn, pattrib->key_idx);
				अन्यथा
					TKIP_IV(pattrib->iv, psta->करोt11txpn, 0);
				अवरोध;
			हाल _AES_:
				अगर (mcast)
					AES_IV(pattrib->iv, psta->करोt11txpn, pattrib->key_idx);
				अन्यथा
					AES_IV(pattrib->iv, psta->करोt11txpn, 0);
				अवरोध;
			पूर्ण

			स_नकल(pframe, pattrib->iv, pattrib->iv_len);

			RT_TRACE(_module_rtl871x_xmit_c_, _drv_notice_,
				 ("%s: keyid=%d pattrib->iv[3]=%.2x pframe=%.2x %.2x %.2x %.2x\n",
				  __func__,
				  padapter->securitypriv.करोt11PrivacyKeyIndex,
				  pattrib->iv[3], *pframe, *(pframe + 1),
				  *(pframe + 2), *(pframe + 3)));

			pframe += pattrib->iv_len;

			mpdu_len -= pattrib->iv_len;
		पूर्ण

		अगर (frg_inx == 0) अणु
			llc_sz = rtw_put_snap(pframe, pattrib->ether_type);
			pframe += llc_sz;
			mpdu_len -= llc_sz;
		पूर्ण

		अगर ((pattrib->icv_len > 0) && (pattrib->bswenc))
			mpdu_len -= pattrib->icv_len;

		mem_sz = min_t(माप_प्रकार, mcast ? pattrib->pktlen : mpdu_len, reमुख्यder);
		skb_copy_bits(pkt, pkt->len - reमुख्यder, pframe, mem_sz);
		reमुख्यder -= mem_sz;

		pframe += mem_sz;

		अगर ((pattrib->icv_len > 0) && (pattrib->bswenc)) अणु
			स_नकल(pframe, pattrib->icv, pattrib->icv_len);
			pframe += pattrib->icv_len;
		पूर्ण

		frg_inx++;

		अगर (mcast || reमुख्यder == 0) अणु
			pattrib->nr_frags = frg_inx;

			pattrib->last_txcmdsz = pattrib->hdrlen + pattrib->iv_len + ((pattrib->nr_frags == 1) ? llc_sz : 0) +
						((pattrib->bswenc) ? pattrib->icv_len : 0) + mem_sz;

			ClearMFrag(mem_start);

			अवरोध;
		पूर्ण

		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("%s: There're still something in packet!\n", __func__));

		addr = (माप_प्रकार)(pframe);

		mem_start = (अचिन्हित अक्षर *)round_up(addr, 4) + hw_hdr_offset;
		स_नकल(mem_start, pbuf_start + hw_hdr_offset, pattrib->hdrlen);
	पूर्ण

	/* Frame is about to be encrypted. Forward it to the monitor first. */
	rtl88eu_mon_xmit_hook(padapter->pmondev, pxmitframe, frg_len);

	अगर (xmitframe_addmic(padapter, pxmitframe) == _FAIL) अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("xmitframe_addmic(padapter, pxmitframe) == _FAIL\n"));
		DBG_88E("xmitframe_addmic(padapter, pxmitframe) == _FAIL\n");
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	xmitframe_swencrypt(padapter, pxmitframe);

	अगर (!mcast)
		update_attrib_vcs_info(padapter, pxmitframe);
	अन्यथा
		pattrib->vcs_mode = NONE_VCS;

निकास:
	वापस res;
पूर्ण

/* Logical Link Control(LLC) SubNetwork Attachment Poपूर्णांक(SNAP) header
 * IEEE LLC/SNAP header contains 8 octets
 * First 3 octets comprise the LLC portion
 * SNAP portion, 5 octets, is भागided पूर्णांकo two fields:
 *	Organizationally Unique Identअगरier(OUI), 3 octets,
 *	type, defined by that organization, 2 octets.
 */
s32 rtw_put_snap(u8 *data, u16 h_proto)
अणु
	काष्ठा ieee80211_snap_hdr *snap;
	u8 *oui;

	snap = (काष्ठा ieee80211_snap_hdr *)data;
	snap->dsap = 0xaa;
	snap->ssap = 0xaa;
	snap->ctrl = 0x03;

	अगर (h_proto == 0x8137 || h_proto == 0x80f3)
		oui = P802_1H_OUI;
	अन्यथा
		oui = RFC1042_OUI;

	snap->oui[0] = oui[0];
	snap->oui[1] = oui[1];
	snap->oui[2] = oui[2];

	*(__be16 *)(data + SNAP_SIZE) = htons(h_proto);

	वापस SNAP_SIZE + माप(u16);
पूर्ण

व्योम rtw_update_protection(काष्ठा adapter *padapter, u8 *ie, uपूर्णांक ie_len)
अणु
	uपूर्णांक	protection, erp_len;
	u8	*perp;
	काष्ठा	xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा	registry_priv *pregistrypriv = &padapter->registrypriv;

	चयन (pxmitpriv->vcs_setting) अणु
	हाल DISABLE_VCS:
		pxmitpriv->vcs = NONE_VCS;
		अवरोध;
	हाल ENABLE_VCS:
		अवरोध;
	हाल AUTO_VCS:
	शेष:
		perp = rtw_get_ie(ie, WLAN_EID_ERP_INFO, &erp_len, ie_len);
		अगर (!perp) अणु
			pxmitpriv->vcs = NONE_VCS;
		पूर्ण अन्यथा अणु
			protection = (*(perp + 2)) & BIT(1);
			अगर (protection) अणु
				अगर (pregistrypriv->vcs_type == RTS_CTS)
					pxmitpriv->vcs = RTS_CTS;
				अन्यथा
					pxmitpriv->vcs = CTS_TO_SELF;
			पूर्ण अन्यथा अणु
				pxmitpriv->vcs = NONE_VCS;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtw_count_tx_stats(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe, पूर्णांक sz)
अणु
	काष्ठा sta_info *psta = शून्य;
	काष्ठा stainfo_stats *pstats = शून्य;
	काष्ठा xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;

	अगर ((pxmitframe->frame_tag & 0x0f) == DATA_FRAMETAG) अणु
		pxmitpriv->tx_bytes += sz;
		pmlmepriv->LinkDetectInfo.NumTxOkInPeriod += pxmitframe->agg_num;

		psta = pxmitframe->attrib.psta;
		अगर (psta) अणु
			pstats = &psta->sta_stats;
			pstats->tx_pkts += pxmitframe->agg_num;
			pstats->tx_bytes += sz;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा xmit_buf *rtw_alloc_xmitbuf_ext(काष्ठा xmit_priv *pxmitpriv)
अणु
	अचिन्हित दीर्घ irql;
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा __queue *pमुक्त_queue = &pxmitpriv->मुक्त_xmit_extbuf_queue;

	spin_lock_irqsave(&pमुक्त_queue->lock, irql);
	pxmitbuf = list_first_entry_or_null(&pमुक्त_queue->queue,
					    काष्ठा xmit_buf, list);
	अगर (pxmitbuf) अणु
		list_del_init(&pxmitbuf->list);
		pxmitpriv->मुक्त_xmit_extbuf_cnt--;
		pxmitbuf->priv_data = शून्य;
		अगर (pxmitbuf->sctx) अणु
			DBG_88E("%s pxmitbuf->sctx is not NULL\n", __func__);
			rtw_sctx_करोne_err(&pxmitbuf->sctx, RTW_SCTX_DONE_BUF_ALLOC);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pमुक्त_queue->lock, irql);

	वापस pxmitbuf;
पूर्ण

s32 rtw_मुक्त_xmitbuf_ext(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf)
अणु
	अचिन्हित दीर्घ irql;
	काष्ठा __queue *pमुक्त_queue = &pxmitpriv->मुक्त_xmit_extbuf_queue;

	अगर (!pxmitbuf)
		वापस _FAIL;

	spin_lock_irqsave(&pमुक्त_queue->lock, irql);

	list_del_init(&pxmitbuf->list);

	list_add_tail(&pxmitbuf->list, get_list_head(pमुक्त_queue));
	pxmitpriv->मुक्त_xmit_extbuf_cnt++;

	spin_unlock_irqrestore(&pमुक्त_queue->lock, irql);

	वापस _SUCCESS;
पूर्ण

काष्ठा xmit_buf *rtw_alloc_xmitbuf(काष्ठा xmit_priv *pxmitpriv)
अणु
	अचिन्हित दीर्घ irql;
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा __queue *pमुक्त_xmitbuf_queue = &pxmitpriv->मुक्त_xmitbuf_queue;

	spin_lock_irqsave(&pमुक्त_xmitbuf_queue->lock, irql);
	pxmitbuf = list_first_entry_or_null(&pमुक्त_xmitbuf_queue->queue,
					    काष्ठा xmit_buf, list);
	अगर (pxmitbuf) अणु
		list_del_init(&pxmitbuf->list);
		pxmitpriv->मुक्त_xmitbuf_cnt--;
		pxmitbuf->priv_data = शून्य;
		अगर (pxmitbuf->sctx) अणु
			DBG_88E("%s pxmitbuf->sctx is not NULL\n", __func__);
			rtw_sctx_करोne_err(&pxmitbuf->sctx, RTW_SCTX_DONE_BUF_ALLOC);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pमुक्त_xmitbuf_queue->lock, irql);

	वापस pxmitbuf;
पूर्ण

s32 rtw_मुक्त_xmitbuf(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf)
अणु
	अचिन्हित दीर्घ irql;
	काष्ठा __queue *pमुक्त_xmitbuf_queue = &pxmitpriv->मुक्त_xmitbuf_queue;

	अगर (!pxmitbuf)
		वापस _FAIL;

	अगर (pxmitbuf->sctx) अणु
		DBG_88E("%s pxmitbuf->sctx is not NULL\n", __func__);
		rtw_sctx_करोne_err(&pxmitbuf->sctx, RTW_SCTX_DONE_BUF_FREE);
	पूर्ण

	अगर (pxmitbuf->ext_tag) अणु
		rtw_मुक्त_xmitbuf_ext(pxmitpriv, pxmitbuf);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&pमुक्त_xmitbuf_queue->lock, irql);

		list_del_init(&pxmitbuf->list);

		list_add_tail(&pxmitbuf->list, get_list_head(pमुक्त_xmitbuf_queue));

		pxmitpriv->मुक्त_xmitbuf_cnt++;
		spin_unlock_irqrestore(&pमुक्त_xmitbuf_queue->lock, irql);
	पूर्ण

	वापस _SUCCESS;
पूर्ण

/*
 * Calling context:
 * 1. OS_TXENTRY
 * 2. RXENTRY (rx_thपढ़ो or RX_ISR/RX_CallBack)
 *
 * If we turn on USE_RXTHREAD, then, no need क्रम critical section.
 * Otherwise, we must use _enter/_निकास critical to protect मुक्त_xmit_queue...
 *
 * Must be very, very cautious...
 *
 */

काष्ठा xmit_frame *rtw_alloc_xmitframe(काष्ठा xmit_priv *pxmitpriv)
				/* _queue *pमुक्त_xmit_queue) */
अणु
	/*
	 *	Please remember to use all the osdep_service api,
	 *	and lock/unlock or _enter/_निकास critical to protect
	 *	pमुक्त_xmit_queue
	 */
	काष्ठा xmit_frame *pxframe;
	काष्ठा __queue *pमुक्त_xmit_queue = &pxmitpriv->मुक्त_xmit_queue;

	spin_lock_bh(&pमुक्त_xmit_queue->lock);
	pxframe = list_first_entry_or_null(&pमुक्त_xmit_queue->queue,
					   काष्ठा xmit_frame, list);
	अगर (!pxframe) अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
			 ("rtw_alloc_xmitframe:%d\n",
			 pxmitpriv->मुक्त_xmitframe_cnt));
	पूर्ण अन्यथा अणु
		list_del_init(&pxframe->list);

		/* शेष value setting */
		pxmitpriv->मुक्त_xmitframe_cnt--;

		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
			 ("rtw_alloc_xmitframe():free_xmitframe_cnt=%d\n",
			 pxmitpriv->मुक्त_xmitframe_cnt));

		pxframe->buf_addr = शून्य;
		pxframe->pxmitbuf = शून्य;

		स_रखो(&pxframe->attrib, 0, माप(काष्ठा pkt_attrib));

		pxframe->frame_tag = DATA_FRAMETAG;

		pxframe->pkt = शून्य;
		pxframe->pkt_offset = 1;/* शेष use pkt_offset to fill tx desc */

		pxframe->agg_num = 1;
		pxframe->ack_report = 0;
	पूर्ण
	spin_unlock_bh(&pमुक्त_xmit_queue->lock);

	वापस pxframe;
पूर्ण

s32 rtw_मुक्त_xmitframe(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा __queue *pमुक्त_xmit_queue = &pxmitpriv->मुक्त_xmit_queue;
	काष्ठा adapter *padapter = pxmitpriv->adapter;
	काष्ठा sk_buff *pndis_pkt = शून्य;

	अगर (!pxmitframe) अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("====== %s:pxmitframe == NULL!!!!!!!!!!\n", __func__));
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&pमुक्त_xmit_queue->lock);

	list_del_init(&pxmitframe->list);

	अगर (pxmitframe->pkt) अणु
		pndis_pkt = pxmitframe->pkt;
		pxmitframe->pkt = शून्य;
	पूर्ण

	list_add_tail(&pxmitframe->list, get_list_head(pमुक्त_xmit_queue));

	pxmitpriv->मुक्त_xmitframe_cnt++;
	RT_TRACE(_module_rtl871x_xmit_c_, _drv_debug_, ("%s:free_xmitframe_cnt=%d\n", __func__, pxmitpriv->मुक्त_xmitframe_cnt));

	spin_unlock_bh(&pमुक्त_xmit_queue->lock);

	अगर (pndis_pkt)
		rtw_os_pkt_complete(padapter, pndis_pkt);

निकास:
	वापस _SUCCESS;
पूर्ण

व्योम rtw_मुक्त_xmitframe_queue(काष्ठा xmit_priv *pxmitpriv, काष्ठा __queue *pframequeue)
अणु
	काष्ठा list_head *plist, *phead;
	काष्ठा	xmit_frame	*pxmitframe;

	spin_lock_bh(&pframequeue->lock);

	phead = get_list_head(pframequeue);
	plist = phead->next;

	जबतक (phead != plist) अणु
		pxmitframe = container_of(plist, काष्ठा xmit_frame, list);

		plist = plist->next;

		rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);
	पूर्ण
	spin_unlock_bh(&pframequeue->lock);
पूर्ण

s32 rtw_xmitframe_enqueue(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	अगर (rtw_xmit_classअगरier(padapter, pxmitframe) == _FAIL) अणु
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_,
			 ("%s: drop xmit pkt for classifier fail\n", __func__));
		वापस _FAIL;
	पूर्ण

	वापस _SUCCESS;
पूर्ण

अटल काष्ठा xmit_frame *dequeue_one_xmitframe(काष्ठा xmit_priv *pxmitpriv, काष्ठा hw_xmit *phwxmit, काष्ठा tx_servq *ptxservq, काष्ठा __queue *pframe_queue)
अणु
	काष्ठा list_head *xmitframe_plist, *xmitframe_phead;
	काष्ठा	xmit_frame	*pxmitframe = शून्य;

	xmitframe_phead = get_list_head(pframe_queue);
	xmitframe_plist = xmitframe_phead->next;

	अगर (xmitframe_phead != xmitframe_plist) अणु
		pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

		xmitframe_plist = xmitframe_plist->next;

		list_del_init(&pxmitframe->list);

		ptxservq->qcnt--;
	पूर्ण
	वापस pxmitframe;
पूर्ण

काष्ठा xmit_frame *rtw_dequeue_xframe(काष्ठा xmit_priv *pxmitpriv, काष्ठा hw_xmit *phwxmit_i, पूर्णांक entry)
अणु
	काष्ठा list_head *sta_plist, *sta_phead;
	काष्ठा hw_xmit *phwxmit;
	काष्ठा tx_servq *ptxservq = शून्य;
	काष्ठा __queue *pframe_queue = शून्य;
	काष्ठा xmit_frame *pxmitframe = शून्य;
	काष्ठा adapter *padapter = pxmitpriv->adapter;
	काष्ठा registry_priv	*pregpriv = &padapter->registrypriv;
	पूर्णांक i, inx[4];

	inx[0] = 0; inx[1] = 1; inx[2] = 2; inx[3] = 3;

	अगर (pregpriv->wअगरi_spec == 1) अणु
		पूर्णांक j;

		क्रम (j = 0; j < 4; j++)
			inx[j] = pxmitpriv->wmm_para_seq[j];
	पूर्ण

	spin_lock_bh(&pxmitpriv->lock);

	क्रम (i = 0; i < entry; i++) अणु
		phwxmit = phwxmit_i + inx[i];

		sta_phead = get_list_head(phwxmit->sta_queue);
		sta_plist = sta_phead->next;

		जबतक (sta_phead != sta_plist) अणु
			ptxservq = container_of(sta_plist, काष्ठा tx_servq, tx_pending);

			pframe_queue = &ptxservq->sta_pending;

			pxmitframe = dequeue_one_xmitframe(pxmitpriv, phwxmit, ptxservq, pframe_queue);

			अगर (pxmitframe) अणु
				phwxmit->accnt--;

				/* Remove sta node when there are no pending packets. */
				अगर (list_empty(&pframe_queue->queue)) /* must be करोne after get_next and beक्रमe अवरोध */
					list_del_init(&ptxservq->tx_pending);
				जाओ निकास;
			पूर्ण

			sta_plist = sta_plist->next;
		पूर्ण
	पूर्ण
निकास:
	spin_unlock_bh(&pxmitpriv->lock);
	वापस pxmitframe;
पूर्ण

काष्ठा tx_servq *rtw_get_sta_pending(काष्ठा adapter *padapter,
				     काष्ठा sta_info *psta, पूर्णांक up, u8 *ac)
अणु
	काष्ठा tx_servq *ptxservq;

	चयन (up) अणु
	हाल 1:
	हाल 2:
		ptxservq = &psta->sta_xmitpriv.bk_q;
		*(ac) = 3;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
			 ("%s : BK\n", __func__));
		अवरोध;
	हाल 4:
	हाल 5:
		ptxservq = &psta->sta_xmitpriv.vi_q;
		*(ac) = 1;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
			 ("%s : VI\n", __func__));
		अवरोध;
	हाल 6:
	हाल 7:
		ptxservq = &psta->sta_xmitpriv.vo_q;
		*(ac) = 0;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
			 ("%s : VO\n", __func__));
		अवरोध;
	हाल 0:
	हाल 3:
	शेष:
		ptxservq = &psta->sta_xmitpriv.be_q;
		*(ac) = 2;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
			 ("%s : BE\n", __func__));
	अवरोध;
	पूर्ण

	वापस ptxservq;
पूर्ण

/*
 * Will enqueue pxmitframe to the proper queue,
 * and indicate it to xx_pending list.....
 */
s32 rtw_xmit_classअगरier(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	u8	ac_index;
	काष्ठा sta_info	*psta;
	काष्ठा tx_servq	*ptxservq;
	काष्ठा pkt_attrib	*pattrib = &pxmitframe->attrib;
	काष्ठा sta_priv	*pstapriv = &padapter->stapriv;
	काष्ठा hw_xmit	*phwxmits =  padapter->xmitpriv.hwxmits;
	पूर्णांक res = _SUCCESS;

	अगर (pattrib->psta)
		psta = pattrib->psta;
	अन्यथा
		psta = rtw_get_stainfo(pstapriv, pattrib->ra);

	अगर (!psta) अणु
		res = _FAIL;
		DBG_88E("%s: psta == NULL\n", __func__);
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("%s: psta == NULL\n", __func__));
		जाओ निकास;
	पूर्ण

	ptxservq = rtw_get_sta_pending(padapter, psta, pattrib->priority, (u8 *)(&ac_index));

	अगर (list_empty(&ptxservq->tx_pending))
		list_add_tail(&ptxservq->tx_pending, get_list_head(phwxmits[ac_index].sta_queue));

	list_add_tail(&pxmitframe->list, get_list_head(&ptxservq->sta_pending));
	ptxservq->qcnt++;
	phwxmits[ac_index].accnt++;
निकास:
	वापस res;
पूर्ण

s32 rtw_alloc_hwxmits(काष्ठा adapter *padapter)
अणु
	काष्ठा hw_xmit *hwxmits;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	pxmitpriv->hwxmit_entry = HWXMIT_ENTRY;

	pxmitpriv->hwxmits = kसुस्मृति(pxmitpriv->hwxmit_entry,
				     माप(काष्ठा hw_xmit), GFP_KERNEL);
	अगर (!pxmitpriv->hwxmits)
		वापस _FAIL;

	hwxmits = pxmitpriv->hwxmits;

	hwxmits[0] .sta_queue = &pxmitpriv->vo_pending;
	hwxmits[1] .sta_queue = &pxmitpriv->vi_pending;
	hwxmits[2] .sta_queue = &pxmitpriv->be_pending;
	hwxmits[3] .sta_queue = &pxmitpriv->bk_pending;
	वापस _SUCCESS;
पूर्ण

व्योम rtw_मुक्त_hwxmits(काष्ठा adapter *padapter)
अणु
	काष्ठा hw_xmit *hwxmits;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	hwxmits = pxmitpriv->hwxmits;
	kमुक्त(hwxmits);
पूर्ण

व्योम rtw_init_hwxmits(काष्ठा hw_xmit *phwxmit, पूर्णांक entry)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < entry; i++, phwxmit++)
		phwxmit->accnt = 0;
पूर्ण

u32 rtw_get_ff_hwaddr(काष्ठा xmit_frame *pxmitframe)
अणु
	u32 addr;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;

	चयन (pattrib->qsel) अणु
	हाल 0:
	हाल 3:
		addr = BE_QUEUE_INX;
		अवरोध;
	हाल 1:
	हाल 2:
		addr = BK_QUEUE_INX;
		अवरोध;
	हाल 4:
	हाल 5:
		addr = VI_QUEUE_INX;
		अवरोध;
	हाल 6:
	हाल 7:
		addr = VO_QUEUE_INX;
		अवरोध;
	हाल 0x10:
		addr = BCN_QUEUE_INX;
		अवरोध;
	हाल 0x11:/* BC/MC in PS (HIQ) */
		addr = HIGH_QUEUE_INX;
		अवरोध;
	हाल 0x12:
	शेष:
		addr = MGT_QUEUE_INX;
		अवरोध;
	पूर्ण

	वापस addr;
पूर्ण

/*
 * The मुख्य transmit(tx) entry
 *
 * Return
 *	1	enqueue
 *	0	success, hardware will handle this xmit frame(packet)
 *	<0	fail
 */
s32 rtw_xmit(काष्ठा adapter *padapter, काष्ठा sk_buff **ppkt)
अणु
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा xmit_frame *pxmitframe = शून्य;
	s32 res;

	pxmitframe = rtw_alloc_xmitframe(pxmitpriv);
	अगर (!pxmitframe) अणु
		RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("%s: no more pxmitframe\n", __func__));
		DBG_88E("DBG_TX_DROP_FRAME %s no more pxmitframe\n", __func__);
		वापस -1;
	पूर्ण

	res = update_attrib(padapter, *ppkt, &pxmitframe->attrib);

	अगर (res == _FAIL) अणु
		RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("%s: update attrib fail\n", __func__));
		rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);
		वापस -1;
	पूर्ण
	pxmitframe->pkt = *ppkt;

	led_control_8188eu(padapter, LED_CTL_TX);

	pxmitframe->attrib.qsel = pxmitframe->attrib.priority;

#अगर_घोषित CONFIG_88EU_AP_MODE
	spin_lock_bh(&pxmitpriv->lock);
	अगर (xmitframe_enqueue_क्रम_sleeping_sta(padapter, pxmitframe)) अणु
		spin_unlock_bh(&pxmitpriv->lock);
		वापस 1;
	पूर्ण
	spin_unlock_bh(&pxmitpriv->lock);
#पूर्ण_अगर

	अगर (!rtw_hal_xmit(padapter, pxmitframe))
		वापस 1;

	वापस 0;
पूर्ण

#अगर defined(CONFIG_88EU_AP_MODE)

पूर्णांक xmitframe_enqueue_क्रम_sleeping_sta(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	पूर्णांक ret = false;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	bool mcast = is_multicast_ether_addr(pattrib->ra);

	अगर (!check_fwstate(pmlmepriv, WIFI_AP_STATE))
		वापस ret;

	अगर (pattrib->psta)
		psta = pattrib->psta;
	अन्यथा
		psta = rtw_get_stainfo(pstapriv, pattrib->ra);

	अगर (!psta)
		वापस ret;

	अगर (pattrib->triggered == 1) अणु
		अगर (mcast)
			pattrib->qsel = 0x11;/* HIQ */
		वापस ret;
	पूर्ण

	अगर (mcast) अणु
		spin_lock_bh(&psta->sleep_q.lock);

		अगर (pstapriv->sta_dz_biपंचांगap) अणु/* अगर any one sta is in ps mode */
			list_del_init(&pxmitframe->list);

			list_add_tail(&pxmitframe->list, get_list_head(&psta->sleep_q));

			psta->sleepq_len++;

			pstapriv->tim_biपंचांगap |= BIT(0);/*  */
			pstapriv->sta_dz_biपंचांगap |= BIT(0);

			update_beacon(padapter, WLAN_EID_TIM, शून्य, false);/* tx bc/mc packets after update bcn */

			ret = true;
		पूर्ण

		spin_unlock_bh(&psta->sleep_q.lock);

		वापस ret;
	पूर्ण

	spin_lock_bh(&psta->sleep_q.lock);

	अगर (psta->state & WIFI_SLEEP_STATE) अणु
		u8 wmmps_ac = 0;

		अगर (pstapriv->sta_dz_biपंचांगap & BIT(psta->aid)) अणु
			list_del_init(&pxmitframe->list);

			list_add_tail(&pxmitframe->list, get_list_head(&psta->sleep_q));

			psta->sleepq_len++;

			चयन (pattrib->priority) अणु
			हाल 1:
			हाल 2:
				wmmps_ac = psta->uapsd_bk & BIT(0);
				अवरोध;
			हाल 4:
			हाल 5:
				wmmps_ac = psta->uapsd_vi & BIT(0);
				अवरोध;
			हाल 6:
			हाल 7:
				wmmps_ac = psta->uapsd_vo & BIT(0);
				अवरोध;
			हाल 0:
			हाल 3:
			शेष:
				wmmps_ac = psta->uapsd_be & BIT(0);
				अवरोध;
			पूर्ण

			अगर (wmmps_ac)
				psta->sleepq_ac_len++;

			अगर (((psta->has_legacy_ac) && (!wmmps_ac)) ||
			    ((!psta->has_legacy_ac) && (wmmps_ac))) अणु
				pstapriv->tim_biपंचांगap |= BIT(psta->aid);

				अगर (psta->sleepq_len == 1) अणु
					/* update BCN क्रम TIM IE */
					update_beacon(padapter, WLAN_EID_TIM, शून्य, false);
				पूर्ण
			पूर्ण
			ret = true;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&psta->sleep_q.lock);

	वापस ret;
पूर्ण

अटल व्योम dequeue_xmitframes_to_sleeping_queue(काष्ठा adapter *padapter, काष्ठा sta_info *psta, काष्ठा __queue *pframequeue)
अणु
	काष्ठा list_head *plist, *phead;
	u8	ac_index;
	काष्ठा tx_servq	*ptxservq;
	काष्ठा pkt_attrib	*pattrib;
	काष्ठा xmit_frame	*pxmitframe;
	काष्ठा hw_xmit *phwxmits =  padapter->xmitpriv.hwxmits;

	phead = get_list_head(pframequeue);
	plist = phead->next;

	जबतक (phead != plist) अणु
		pxmitframe = container_of(plist, काष्ठा xmit_frame, list);

		plist = plist->next;

		xmitframe_enqueue_क्रम_sleeping_sta(padapter, pxmitframe);

		pattrib = &pxmitframe->attrib;

		ptxservq = rtw_get_sta_pending(padapter, psta, pattrib->priority, (u8 *)(&ac_index));

		ptxservq->qcnt--;
		phwxmits[ac_index].accnt--;
	पूर्ण
पूर्ण

व्योम stop_sta_xmit(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	काष्ठा sta_info *psta_bmc;
	काष्ठा sta_xmit_priv *pstaxmitpriv;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	pstaxmitpriv = &psta->sta_xmitpriv;

	/* क्रम BC/MC Frames */
	psta_bmc = rtw_get_bcmc_stainfo(padapter);

	spin_lock_bh(&pxmitpriv->lock);

	psta->state |= WIFI_SLEEP_STATE;

	pstapriv->sta_dz_biपंचांगap |= BIT(psta->aid);

	dequeue_xmitframes_to_sleeping_queue(padapter, psta,
					     &pstaxmitpriv->vo_q.sta_pending);
	list_del_init(&pstaxmitpriv->vo_q.tx_pending);

	dequeue_xmitframes_to_sleeping_queue(padapter, psta,
					     &pstaxmitpriv->vi_q.sta_pending);
	list_del_init(&pstaxmitpriv->vi_q.tx_pending);

	dequeue_xmitframes_to_sleeping_queue(padapter, psta,
					     &pstaxmitpriv->be_q.sta_pending);
	list_del_init(&pstaxmitpriv->be_q.tx_pending);

	dequeue_xmitframes_to_sleeping_queue(padapter, psta,
					     &pstaxmitpriv->bk_q.sta_pending);
	list_del_init(&pstaxmitpriv->bk_q.tx_pending);

	/* क्रम BC/MC Frames */
	pstaxmitpriv = &psta_bmc->sta_xmitpriv;
	dequeue_xmitframes_to_sleeping_queue(padapter, psta_bmc,
					     &pstaxmitpriv->be_q.sta_pending);
	list_del_init(&pstaxmitpriv->be_q.tx_pending);

	spin_unlock_bh(&pxmitpriv->lock);
पूर्ण

व्योम wakeup_sta_to_xmit(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 update_mask = 0, wmmps_ac = 0;
	काष्ठा sta_info *psta_bmc;
	काष्ठा list_head *xmitframe_plist, *xmitframe_phead;
	काष्ठा xmit_frame *pxmitframe = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	spin_lock_bh(&psta->sleep_q.lock);

	xmitframe_phead = get_list_head(&psta->sleep_q);
	xmitframe_plist = xmitframe_phead->next;

	जबतक (xmitframe_phead != xmitframe_plist) अणु
		pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

		xmitframe_plist = xmitframe_plist->next;

		list_del_init(&pxmitframe->list);

		चयन (pxmitframe->attrib.priority) अणु
		हाल 1:
		हाल 2:
			wmmps_ac = psta->uapsd_bk & BIT(1);
			अवरोध;
		हाल 4:
		हाल 5:
			wmmps_ac = psta->uapsd_vi & BIT(1);
			अवरोध;
		हाल 6:
		हाल 7:
			wmmps_ac = psta->uapsd_vo & BIT(1);
			अवरोध;
		हाल 0:
		हाल 3:
		शेष:
			wmmps_ac = psta->uapsd_be & BIT(1);
			अवरोध;
		पूर्ण

		psta->sleepq_len--;
		अगर (psta->sleepq_len > 0)
			pxmitframe->attrib.mdata = 1;
		अन्यथा
			pxmitframe->attrib.mdata = 0;

		अगर (wmmps_ac) अणु
			psta->sleepq_ac_len--;
			अगर (psta->sleepq_ac_len > 0) अणु
				pxmitframe->attrib.mdata = 1;
				pxmitframe->attrib.eosp = 0;
			पूर्ण अन्यथा अणु
				pxmitframe->attrib.mdata = 0;
				pxmitframe->attrib.eosp = 1;
			पूर्ण
		पूर्ण

		pxmitframe->attrib.triggered = 1;

		spin_unlock_bh(&psta->sleep_q.lock);
		अगर (rtw_hal_xmit(padapter, pxmitframe))
			rtw_os_xmit_complete(padapter, pxmitframe);
		spin_lock_bh(&psta->sleep_q.lock);
	पूर्ण

	अगर (psta->sleepq_len == 0) अणु
		pstapriv->tim_biपंचांगap &= ~BIT(psta->aid);

		update_mask = BIT(0);

		अगर (psta->state & WIFI_SLEEP_STATE)
			psta->state ^= WIFI_SLEEP_STATE;

		अगर (psta->state & WIFI_STA_ALIVE_CHK_STATE) अणु
			psta->expire_to = pstapriv->expire_to;
			psta->state ^= WIFI_STA_ALIVE_CHK_STATE;
		पूर्ण

		pstapriv->sta_dz_biपंचांगap &= ~BIT(psta->aid);
	पूर्ण

	spin_unlock_bh(&psta->sleep_q.lock);

	/* क्रम BC/MC Frames */
	psta_bmc = rtw_get_bcmc_stainfo(padapter);
	अगर (!psta_bmc)
		वापस;

	अगर ((pstapriv->sta_dz_biपंचांगap & 0xfffe) == 0x0) अणु /* no any sta in ps mode */
		spin_lock_bh(&psta_bmc->sleep_q.lock);

		xmitframe_phead = get_list_head(&psta_bmc->sleep_q);
		xmitframe_plist = xmitframe_phead->next;

		जबतक (xmitframe_phead != xmitframe_plist) अणु
			pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

			xmitframe_plist = xmitframe_plist->next;

			list_del_init(&pxmitframe->list);

			psta_bmc->sleepq_len--;
			अगर (psta_bmc->sleepq_len > 0)
				pxmitframe->attrib.mdata = 1;
			अन्यथा
				pxmitframe->attrib.mdata = 0;

			pxmitframe->attrib.triggered = 1;

			spin_unlock_bh(&psta_bmc->sleep_q.lock);
			अगर (rtw_hal_xmit(padapter, pxmitframe))
				rtw_os_xmit_complete(padapter, pxmitframe);
			spin_lock_bh(&psta_bmc->sleep_q.lock);
		पूर्ण

		अगर (psta_bmc->sleepq_len == 0) अणु
			pstapriv->tim_biपंचांगap &= ~BIT(0);
			pstapriv->sta_dz_biपंचांगap &= ~BIT(0);

			update_mask |= BIT(1);
		पूर्ण

		spin_unlock_bh(&psta_bmc->sleep_q.lock);
	पूर्ण

	अगर (update_mask)
		update_beacon(padapter, WLAN_EID_TIM, शून्य, false);
पूर्ण

व्योम xmit_delivery_enabled_frames(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 wmmps_ac = 0;
	काष्ठा list_head *xmitframe_plist, *xmitframe_phead;
	काष्ठा xmit_frame *pxmitframe = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;

	spin_lock_bh(&psta->sleep_q.lock);

	xmitframe_phead = get_list_head(&psta->sleep_q);
	xmitframe_plist = xmitframe_phead->next;

	जबतक (xmitframe_phead != xmitframe_plist) अणु
		pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

		xmitframe_plist = xmitframe_plist->next;

		चयन (pxmitframe->attrib.priority) अणु
		हाल 1:
		हाल 2:
			wmmps_ac = psta->uapsd_bk & BIT(1);
			अवरोध;
		हाल 4:
		हाल 5:
			wmmps_ac = psta->uapsd_vi & BIT(1);
			अवरोध;
		हाल 6:
		हाल 7:
			wmmps_ac = psta->uapsd_vo & BIT(1);
			अवरोध;
		हाल 0:
		हाल 3:
		शेष:
			wmmps_ac = psta->uapsd_be & BIT(1);
			अवरोध;
		पूर्ण

		अगर (!wmmps_ac)
			जारी;

		list_del_init(&pxmitframe->list);

		psta->sleepq_len--;
		psta->sleepq_ac_len--;

		अगर (psta->sleepq_ac_len > 0) अणु
			pxmitframe->attrib.mdata = 1;
			pxmitframe->attrib.eosp = 0;
		पूर्ण अन्यथा अणु
			pxmitframe->attrib.mdata = 0;
			pxmitframe->attrib.eosp = 1;
		पूर्ण

		pxmitframe->attrib.triggered = 1;

		अगर (rtw_hal_xmit(padapter, pxmitframe))
			rtw_os_xmit_complete(padapter, pxmitframe);

		अगर ((psta->sleepq_ac_len == 0) && (!psta->has_legacy_ac) && (wmmps_ac)) अणु
			pstapriv->tim_biपंचांगap &= ~BIT(psta->aid);

			/* update BCN क्रम TIM IE */
			update_beacon(padapter, WLAN_EID_TIM, शून्य, false);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&psta->sleep_q.lock);
पूर्ण

#पूर्ण_अगर

व्योम rtw_sctx_init(काष्ठा submit_ctx *sctx, पूर्णांक समयout_ms)
अणु
	sctx->समयout_ms = समयout_ms;
	sctx->submit_समय = jअगरfies;
	init_completion(&sctx->करोne);
	sctx->status = RTW_SCTX_SUBMITTED;
पूर्ण

पूर्णांक rtw_sctx_रुको(काष्ठा submit_ctx *sctx)
अणु
	पूर्णांक ret = _FAIL;
	अचिन्हित दीर्घ expire;
	पूर्णांक status = 0;

	expire = sctx->समयout_ms ? msecs_to_jअगरfies(sctx->समयout_ms) : MAX_SCHEDULE_TIMEOUT;
	अगर (!रुको_क्रम_completion_समयout(&sctx->करोne, expire)) अणु
		/* समयout, करो something?? */
		status = RTW_SCTX_DONE_TIMEOUT;
		DBG_88E("%s timeout\n", __func__);
	पूर्ण अन्यथा अणु
		status = sctx->status;
	पूर्ण

	अगर (status == RTW_SCTX_DONE_SUCCESS)
		ret = _SUCCESS;

	वापस ret;
पूर्ण

अटल bool rtw_sctx_chk_warning_status(पूर्णांक status)
अणु
	चयन (status) अणु
	हाल RTW_SCTX_DONE_UNKNOWN:
	हाल RTW_SCTX_DONE_BUF_ALLOC:
	हाल RTW_SCTX_DONE_BUF_FREE:

	हाल RTW_SCTX_DONE_DRV_STOP:
	हाल RTW_SCTX_DONE_DEV_REMOVE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

व्योम rtw_sctx_करोne_err(काष्ठा submit_ctx **sctx, पूर्णांक status)
अणु
	अगर (*sctx) अणु
		अगर (rtw_sctx_chk_warning_status(status))
			DBG_88E("%s status:%d\n", __func__, status);
		(*sctx)->status = status;
		complete(&((*sctx)->करोne));
		*sctx = शून्य;
	पूर्ण
पूर्ण

पूर्णांक rtw_ack_tx_रुको(काष्ठा xmit_priv *pxmitpriv, u32 समयout_ms)
अणु
	काष्ठा submit_ctx *pack_tx_ops = &pxmitpriv->ack_tx_ops;

	pack_tx_ops->submit_समय = jअगरfies;
	pack_tx_ops->समयout_ms = समयout_ms;
	pack_tx_ops->status = RTW_SCTX_SUBMITTED;

	वापस rtw_sctx_रुको(pack_tx_ops);
पूर्ण

व्योम rtw_ack_tx_करोne(काष्ठा xmit_priv *pxmitpriv, पूर्णांक status)
अणु
	काष्ठा submit_ctx *pack_tx_ops = &pxmitpriv->ack_tx_ops;

	अगर (pxmitpriv->ack_tx)
		rtw_sctx_करोne_err(&pack_tx_ops, status);
	अन्यथा
		DBG_88E("%s ack_tx not set\n", __func__);
पूर्ण
