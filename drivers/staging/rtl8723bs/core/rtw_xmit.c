<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_XMIT_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>

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
	चिन्हित पूर्णांक	res = _SUCCESS;

	spin_lock_init(&pxmitpriv->lock);
	spin_lock_init(&pxmitpriv->lock_sctx);
	init_completion(&pxmitpriv->xmit_comp);
	init_completion(&pxmitpriv->terminate_xmitthपढ़ो_comp);

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
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	pxmitpriv->pxmit_frame_buf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitpriv->pallocated_frame_buf), 4);

	pxframe = (काष्ठा xmit_frame *) pxmitpriv->pxmit_frame_buf;

	क्रम (i = 0; i < NR_XMITFRAME; i++) अणु
		INIT_LIST_HEAD(&pxframe->list);

		pxframe->padapter = padapter;
		pxframe->frame_tag = शून्य_FRAMETAG;

		pxframe->pkt = शून्य;

		pxframe->buf_addr = शून्य;
		pxframe->pxmitbuf = शून्य;

		list_add_tail(&pxframe->list,
			      &pxmitpriv->मुक्त_xmit_queue.queue);

		pxframe++;
	पूर्ण

	pxmitpriv->मुक्त_xmitframe_cnt = NR_XMITFRAME;

	pxmitpriv->frag_len = MAX_FRAG_THRESHOLD;

	/* init xmit_buf */
	_rtw_init_queue(&pxmitpriv->मुक्त_xmitbuf_queue);
	_rtw_init_queue(&pxmitpriv->pending_xmitbuf_queue);

	pxmitpriv->pallocated_xmitbuf = vzalloc(NR_XMITBUFF * माप(काष्ठा xmit_buf) + 4);

	अगर (!pxmitpriv->pallocated_xmitbuf) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pxmitpriv->pxmitbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitpriv->pallocated_xmitbuf), 4);

	pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmitbuf;

	क्रम (i = 0; i < NR_XMITBUFF; i++) अणु
		INIT_LIST_HEAD(&pxmitbuf->list);

		pxmitbuf->priv_data = शून्य;
		pxmitbuf->padapter = padapter;
		pxmitbuf->buf_tag = XMITBUF_DATA;

		/* Tx buf allocation may fail someबार, so sleep and retry. */
		res = rtw_os_xmit_resource_alloc(padapter, pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ), true);
		अगर (res == _FAIL) अणु
			msleep(10);
			res = rtw_os_xmit_resource_alloc(padapter, pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ), true);
			अगर (res == _FAIL)
				जाओ निकास;
		पूर्ण

		pxmitbuf->phead = pxmitbuf->pbuf;
		pxmitbuf->pend = pxmitbuf->pbuf + MAX_XMITBUF_SZ;
		pxmitbuf->len = 0;
		pxmitbuf->pdata = pxmitbuf->ptail = pxmitbuf->phead;

		pxmitbuf->flags = XMIT_VO_QUEUE;

		list_add_tail(&pxmitbuf->list,
			      &pxmitpriv->मुक्त_xmitbuf_queue.queue);
		#अगर_घोषित DBG_XMIT_BUF
		pxmitbuf->no = i;
		#पूर्ण_अगर

		pxmitbuf++;
	पूर्ण

	pxmitpriv->मुक्त_xmitbuf_cnt = NR_XMITBUFF;

	/* init xframe_ext queue,  the same count as extbuf  */
	_rtw_init_queue(&pxmitpriv->मुक्त_xframe_ext_queue);

	pxmitpriv->xframe_ext_alloc_addr = vzalloc(NR_XMIT_EXTBUFF * माप(काष्ठा xmit_frame) + 4);

	अगर (!pxmitpriv->xframe_ext_alloc_addr) अणु
		pxmitpriv->xframe_ext = शून्य;
		res = _FAIL;
		जाओ निकास;
	पूर्ण
	pxmitpriv->xframe_ext = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitpriv->xframe_ext_alloc_addr), 4);
	pxframe = (काष्ठा xmit_frame *)pxmitpriv->xframe_ext;

	क्रम (i = 0; i < NR_XMIT_EXTBUFF; i++) अणु
		INIT_LIST_HEAD(&pxframe->list);

		pxframe->padapter = padapter;
		pxframe->frame_tag = शून्य_FRAMETAG;

		pxframe->pkt = शून्य;

		pxframe->buf_addr = शून्य;
		pxframe->pxmitbuf = शून्य;

		pxframe->ext_tag = 1;

		list_add_tail(&pxframe->list,
			      &pxmitpriv->मुक्त_xframe_ext_queue.queue);

		pxframe++;
	पूर्ण
	pxmitpriv->मुक्त_xframe_ext_cnt = NR_XMIT_EXTBUFF;

	/*  Init xmit extension buff */
	_rtw_init_queue(&pxmitpriv->मुक्त_xmit_extbuf_queue);

	pxmitpriv->pallocated_xmit_extbuf = vzalloc(NR_XMIT_EXTBUFF * माप(काष्ठा xmit_buf) + 4);

	अगर (!pxmitpriv->pallocated_xmit_extbuf) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	pxmitpriv->pxmit_extbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitpriv->pallocated_xmit_extbuf), 4);

	pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmit_extbuf;

	क्रम (i = 0; i < NR_XMIT_EXTBUFF; i++) अणु
		INIT_LIST_HEAD(&pxmitbuf->list);

		pxmitbuf->priv_data = शून्य;
		pxmitbuf->padapter = padapter;
		pxmitbuf->buf_tag = XMITBUF_MGNT;

		res = rtw_os_xmit_resource_alloc(padapter, pxmitbuf, MAX_XMIT_EXTBUF_SZ + XMITBUF_ALIGN_SZ, true);
		अगर (res == _FAIL) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		pxmitbuf->phead = pxmitbuf->pbuf;
		pxmitbuf->pend = pxmitbuf->pbuf + MAX_XMIT_EXTBUF_SZ;
		pxmitbuf->len = 0;
		pxmitbuf->pdata = pxmitbuf->ptail = pxmitbuf->phead;

		list_add_tail(&pxmitbuf->list,
			      &pxmitpriv->मुक्त_xmit_extbuf_queue.queue);
		#अगर_घोषित DBG_XMIT_BUF_EXT
		pxmitbuf->no = i;
		#पूर्ण_अगर
		pxmitbuf++;
	पूर्ण

	pxmitpriv->मुक्त_xmit_extbuf_cnt = NR_XMIT_EXTBUFF;

	क्रम (i = 0; i < CMDBUF_MAX; i++) अणु
		pxmitbuf = &pxmitpriv->pcmd_xmitbuf[i];
		अगर (pxmitbuf) अणु
			INIT_LIST_HEAD(&pxmitbuf->list);

			pxmitbuf->priv_data = शून्य;
			pxmitbuf->padapter = padapter;
			pxmitbuf->buf_tag = XMITBUF_CMD;

			res = rtw_os_xmit_resource_alloc(padapter, pxmitbuf, MAX_CMDBUF_SZ+XMITBUF_ALIGN_SZ, true);
			अगर (res == _FAIL) अणु
				res = _FAIL;
				जाओ निकास;
			पूर्ण

			pxmitbuf->phead = pxmitbuf->pbuf;
			pxmitbuf->pend = pxmitbuf->pbuf + MAX_CMDBUF_SZ;
			pxmitbuf->len = 0;
			pxmitbuf->pdata = pxmitbuf->ptail = pxmitbuf->phead;
			pxmitbuf->alloc_sz = MAX_CMDBUF_SZ+XMITBUF_ALIGN_SZ;
		पूर्ण
	पूर्ण

	res = rtw_alloc_hwxmits(padapter);
	अगर (res == _FAIL)
		जाओ निकास;
	rtw_init_hwxmits(pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);

	क्रम (i = 0; i < 4; i++)
		pxmitpriv->wmm_para_seq[i] = i;

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
	काष्ठा xmit_frame	*pxmitframe = (काष्ठा xmit_frame *) pxmitpriv->pxmit_frame_buf;
	काष्ठा xmit_buf *pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmitbuf;

	rtw_hal_मुक्त_xmit_priv(padapter);

	अगर (!pxmitpriv->pxmit_frame_buf)
		वापस;

	क्रम (i = 0; i < NR_XMITFRAME; i++) अणु
		rtw_os_xmit_complete(padapter, pxmitframe);

		pxmitframe++;
	पूर्ण

	क्रम (i = 0; i < NR_XMITBUFF; i++) अणु
		rtw_os_xmit_resource_मुक्त(padapter, pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ), true);

		pxmitbuf++;
	पूर्ण

	vमुक्त(pxmitpriv->pallocated_frame_buf);
	vमुक्त(pxmitpriv->pallocated_xmitbuf);

	/* मुक्त xframe_ext queue,  the same count as extbuf  */
	pxmitframe = (काष्ठा xmit_frame *)pxmitpriv->xframe_ext;
	अगर (pxmitframe) अणु
		क्रम (i = 0; i < NR_XMIT_EXTBUFF; i++) अणु
			rtw_os_xmit_complete(padapter, pxmitframe);
			pxmitframe++;
		पूर्ण
	पूर्ण

	vमुक्त(pxmitpriv->xframe_ext_alloc_addr);

	/*  मुक्त xmit extension buff */
	pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmit_extbuf;
	क्रम (i = 0; i < NR_XMIT_EXTBUFF; i++) अणु
		rtw_os_xmit_resource_मुक्त(padapter, pxmitbuf, (MAX_XMIT_EXTBUF_SZ + XMITBUF_ALIGN_SZ), true);

		pxmitbuf++;
	पूर्ण

	vमुक्त(pxmitpriv->pallocated_xmit_extbuf);

	क्रम (i = 0; i < CMDBUF_MAX; i++) अणु
		pxmitbuf = &pxmitpriv->pcmd_xmitbuf[i];
		अगर (pxmitbuf)
			rtw_os_xmit_resource_मुक्त(padapter, pxmitbuf, MAX_CMDBUF_SZ+XMITBUF_ALIGN_SZ, true);
	पूर्ण

	rtw_मुक्त_hwxmits(padapter);

	mutex_destroy(&pxmitpriv->ack_tx_mutex);
पूर्ण

u8 query_ra_लघु_GI(काष्ठा sta_info *psta)
अणु
	u8 sgi = false, sgi_20m = false, sgi_40m = false, sgi_80m = false;

	sgi_20m = psta->htpriv.sgi_20m;
	sgi_40m = psta->htpriv.sgi_40m;

	चयन (psta->bw_mode) अणु
	हाल CHANNEL_WIDTH_80:
		sgi = sgi_80m;
		अवरोध;
	हाल CHANNEL_WIDTH_40:
		sgi = sgi_40m;
		अवरोध;
	हाल CHANNEL_WIDTH_20:
	शेष:
		sgi = sgi_20m;
		अवरोध;
	पूर्ण

	वापस sgi;
पूर्ण

अटल व्योम update_attrib_vcs_info(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	u32 sz;
	काष्ठा pkt_attrib	*pattrib = &pxmitframe->attrib;
	/* काष्ठा sta_info *psta = pattrib->psta; */
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	अगर (pattrib->nr_frags != 1)
		sz = padapter->xmitpriv.frag_len;
	अन्यथा /* no frag */
		sz = pattrib->last_txcmdsz;

	/*  (1) RTS_Threshold is compared to the MPDU, not MSDU. */
	/*  (2) If there are more than one frag in  this MSDU, only the first frag uses protection frame. */
	/* Other fragments are रक्षित by previous fragment. */
	/* So we only need to check the length of first fragment. */
	अगर (pmlmeext->cur_wireless_mode < WIRELESS_11_24N  || padapter->registrypriv.wअगरi_spec) अणु
		अगर (sz > padapter->registrypriv.rts_thresh) अणु
			pattrib->vcs_mode = RTS_CTS;
		पूर्ण अन्यथा अणु
			अगर (pattrib->rtsen)
				pattrib->vcs_mode = RTS_CTS;
			अन्यथा अगर (pattrib->cts2self)
				pattrib->vcs_mode = CTS_TO_SELF;
			अन्यथा
				pattrib->vcs_mode = NONE_VCS;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (true) अणु
			/* IOT action */
			अगर ((pmlmeinfo->assoc_AP_venकरोr == HT_IOT_PEER_ATHEROS) && (pattrib->ampdu_en == true) &&
				(padapter->securitypriv.करोt11PrivacyAlgrthm == _AES_)) अणु
				pattrib->vcs_mode = CTS_TO_SELF;
				अवरोध;
			पूर्ण

			/* check ERP protection */
			अगर (pattrib->rtsen || pattrib->cts2self) अणु
				अगर (pattrib->rtsen)
					pattrib->vcs_mode = RTS_CTS;
				अन्यथा अगर (pattrib->cts2self)
					pattrib->vcs_mode = CTS_TO_SELF;

				अवरोध;
			पूर्ण

			/* check HT op mode */
			अगर (pattrib->ht_en) अणु
				u8 HTOpMode = pmlmeinfo->HT_protection;

				अगर ((pmlmeext->cur_bwmode && (HTOpMode == 2 || HTOpMode == 3)) ||
					(!pmlmeext->cur_bwmode && HTOpMode == 3)) अणु
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
			अगर (pattrib->ampdu_en == true) अणु
				pattrib->vcs_mode = RTS_CTS;
				अवरोध;
			पूर्ण

			pattrib->vcs_mode = NONE_VCS;
			अवरोध;
		पूर्ण
	पूर्ण

	/* क्रम debug : क्रमce driver control vrtl_carrier_sense. */
	अगर (padapter->driver_vcs_en == 1)
		pattrib->vcs_mode = padapter->driver_vcs_type;
पूर्ण

अटल व्योम update_attrib_phy_info(काष्ठा adapter *padapter, काष्ठा pkt_attrib *pattrib, काष्ठा sta_info *psta)
अणु
	काष्ठा mlme_ext_priv *mlmeext = &padapter->mlmeextpriv;

	pattrib->rtsen = psta->rtsen;
	pattrib->cts2self = psta->cts2self;

	pattrib->mdata = 0;
	pattrib->eosp = 0;
	pattrib->triggered = 0;
	pattrib->ampdu_spacing = 0;

	/* qos_en, ht_en, init rate, , bw, ch_offset, sgi */
	pattrib->qos_en = psta->qos_option;

	pattrib->raid = psta->raid;

	अगर (mlmeext->cur_bwmode < psta->bw_mode)
		pattrib->bwmode = mlmeext->cur_bwmode;
	अन्यथा
		pattrib->bwmode = psta->bw_mode;

	pattrib->sgi = query_ra_लघु_GI(psta);

	pattrib->ldpc = psta->ldpc;
	pattrib->stbc = psta->stbc;

	pattrib->ht_en = psta->htpriv.ht_option;
	pattrib->ch_offset = psta->htpriv.ch_offset;
	pattrib->ampdu_en = false;

	अगर (padapter->driver_ampdu_spacing != 0xFF) /* driver control AMPDU Density क्रम peer sta's rx */
		pattrib->ampdu_spacing = padapter->driver_ampdu_spacing;
	अन्यथा
		pattrib->ampdu_spacing = psta->htpriv.rx_ampdu_min_spacing;

	pattrib->retry_ctrl = false;
पूर्ण

अटल s32 update_attrib_sec_info(काष्ठा adapter *padapter, काष्ठा pkt_attrib *pattrib, काष्ठा sta_info *psta)
अणु
	चिन्हित पूर्णांक res = _SUCCESS;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	चिन्हित पूर्णांक bmcast = IS_MCAST(pattrib->ra);

	स_रखो(pattrib->करोt118021x_UncstKey.skey,  0, 16);
	स_रखो(pattrib->करोt11tkiptxmickey.skey,  0, 16);
	pattrib->mac_id = psta->mac_id;

	अगर (psta->ieee8021x_blocked == true) अणु
		pattrib->encrypt = 0;

		अगर ((pattrib->ether_type != 0x888e) && (check_fwstate(pmlmepriv, WIFI_MP_STATE) == false)) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt, bmcast);

		चयन (psecuritypriv->करोt11AuthAlgrthm) अणु
		हाल करोt11AuthAlgrthm_Open:
		हाल करोt11AuthAlgrthm_Shared:
		हाल करोt11AuthAlgrthm_Auto:
			pattrib->key_idx = (u8)psecuritypriv->करोt11PrivacyKeyIndex;
			अवरोध;
		हाल करोt11AuthAlgrthm_8021X:
			अगर (bmcast)
				pattrib->key_idx = (u8)psecuritypriv->करोt118021XGrpKeyid;
			अन्यथा
				pattrib->key_idx = 0;
			अवरोध;
		शेष:
			pattrib->key_idx = 0;
			अवरोध;
		पूर्ण

		/* For WPS 1.0 WEP, driver should not encrypt EAPOL Packet क्रम WPS handshake. */
		अगर (((pattrib->encrypt == _WEP40_) || (pattrib->encrypt == _WEP104_)) && (pattrib->ether_type == 0x888e))
			pattrib->encrypt = _NO_PRIVACY_;
	पूर्ण

	चयन (pattrib->encrypt) अणु
	हाल _WEP40_:
	हाल _WEP104_:
		pattrib->iv_len = 4;
		pattrib->icv_len = 4;
		WEP_IV(pattrib->iv, psta->करोt11txpn, pattrib->key_idx);
		अवरोध;

	हाल _TKIP_:
		pattrib->iv_len = 8;
		pattrib->icv_len = 4;

		अगर (psecuritypriv->busetkipkey == _FAIL) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण

		अगर (bmcast)
			TKIP_IV(pattrib->iv, psta->करोt11txpn, pattrib->key_idx);
		अन्यथा
			TKIP_IV(pattrib->iv, psta->करोt11txpn, 0);

		स_नकल(pattrib->करोt11tkiptxmickey.skey, psta->करोt11tkiptxmickey.skey, 16);

		अवरोध;

	हाल _AES_:

		pattrib->iv_len = 8;
		pattrib->icv_len = 8;

		अगर (bmcast)
			AES_IV(pattrib->iv, psta->करोt11txpn, pattrib->key_idx);
		अन्यथा
			AES_IV(pattrib->iv, psta->करोt11txpn, 0);

		अवरोध;

	शेष:
		pattrib->iv_len = 0;
		pattrib->icv_len = 0;
		अवरोध;
	पूर्ण

	अगर (pattrib->encrypt > 0)
		स_नकल(pattrib->करोt118021x_UncstKey.skey, psta->करोt118021x_UncstKey.skey, 16);

	अगर (pattrib->encrypt &&
		((padapter->securitypriv.sw_encrypt) || (!psecuritypriv->hw_decrypted)))
		pattrib->bswenc = true;
	अन्यथा
		pattrib->bswenc = false;

निकास:

	वापस res;
पूर्ण

u8 qos_acm(u8 acm_mask, u8 priority)
अणु
	चयन (priority) अणु
	हाल 0:
	हाल 3:
		अगर (acm_mask & BIT(1))
			priority = 1;
		अवरोध;
	हाल 1:
	हाल 2:
		अवरोध;
	हाल 4:
	हाल 5:
		अगर (acm_mask & BIT(2))
			priority = 0;
		अवरोध;
	हाल 6:
	हाल 7:
		अगर (acm_mask & BIT(3))
			priority = 5;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस priority;
पूर्ण

अटल व्योम set_qos(काष्ठा pkt_file *ppktfile, काष्ठा pkt_attrib *pattrib)
अणु
	काष्ठा ethhdr etherhdr;
	काष्ठा iphdr ip_hdr;
	s32 UserPriority = 0;

	_rtw_खोलो_pktfile(ppktfile->pkt, ppktfile);
	_rtw_pktfile_पढ़ो(ppktfile, (अचिन्हित अक्षर *)&etherhdr, ETH_HLEN);

	/*  get UserPriority from IP hdr */
	अगर (pattrib->ether_type == 0x0800) अणु
		_rtw_pktfile_पढ़ो(ppktfile, (u8 *)&ip_hdr, माप(ip_hdr));
		UserPriority = ip_hdr.tos >> 5;
	पूर्ण
	pattrib->priority = UserPriority;
	pattrib->hdrlen = WLAN_HDR_A3_QOS_LEN;
	pattrib->subtype = WIFI_QOS_DATA_TYPE;
पूर्ण

अटल s32 update_attrib(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt, काष्ठा pkt_attrib *pattrib)
अणु
	काष्ठा pkt_file pktfile;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा ethhdr etherhdr;

	चिन्हित पूर्णांक bmcast;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv *pqospriv = &pmlmepriv->qospriv;
	चिन्हित पूर्णांक res = _SUCCESS;

	_rtw_खोलो_pktfile(pkt, &pktfile);
	_rtw_pktfile_पढ़ो(&pktfile, (u8 *)&etherhdr, ETH_HLEN);

	pattrib->ether_type = ntohs(etherhdr.h_proto);

	स_नकल(pattrib->dst, &etherhdr.h_dest, ETH_ALEN);
	स_नकल(pattrib->src, &etherhdr.h_source, ETH_ALEN);

	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)) अणु
		स_नकल(pattrib->ra, pattrib->dst, ETH_ALEN);
		स_नकल(pattrib->ta, pattrib->src, ETH_ALEN);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
		स_नकल(pattrib->ra, get_bssid(pmlmepriv), ETH_ALEN);
		स_नकल(pattrib->ta, pattrib->src, ETH_ALEN);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		स_नकल(pattrib->ra, pattrib->dst, ETH_ALEN);
		स_नकल(pattrib->ta, get_bssid(pmlmepriv), ETH_ALEN);
	पूर्ण

	pattrib->pktlen = pktfile.pkt_len;

	अगर (ETH_P_IP == pattrib->ether_type) अणु
		/*  The following is क्रम DHCP and ARP packet, we use cck1M to tx these packets and let LPS awake some समय */
		/*  to prevent DHCP protocol fail */

		u8 पंचांगp[24];

		_rtw_pktfile_पढ़ो(&pktfile, &पंचांगp[0], 24);

		pattrib->dhcp_pkt = 0;
		अगर (pktfile.pkt_len > 282) अणु/* MINIMUM_DHCP_PACKET_SIZE) अणु */
			अगर (ETH_P_IP == pattrib->ether_type) अणु/*  IP header */
				अगर (((पंचांगp[21] == 68) && (पंचांगp[23] == 67)) ||
					((पंचांगp[21] == 67) && (पंचांगp[23] == 68))) अणु
					/*  68 : UDP BOOTP client */
					/*  67 : UDP BOOTP server */
					pattrib->dhcp_pkt = 1;
				पूर्ण
			पूर्ण
		पूर्ण

		/* क्रम parsing ICMP pakcets */
		अणु
			काष्ठा iphdr *piphdr = (काष्ठा iphdr *)पंचांगp;

			pattrib->icmp_pkt = 0;
			अगर (piphdr->protocol == 0x1) /*  protocol type in ip header 0x1 is ICMP */
				pattrib->icmp_pkt = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (0x888e == pattrib->ether_type) अणु
		netdev_dbg(padapter->pnetdev, "send eapol packet\n");
	पूर्ण

	अगर ((pattrib->ether_type == 0x888e) || (pattrib->dhcp_pkt == 1))
		rtw_set_scan_deny(padapter, 3000);

	/*  If EAPOL , ARP , OR DHCP packet, driver must be in active mode. */
	अगर (pattrib->icmp_pkt == 1)
		rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_LEAVE, 1);
	अन्यथा अगर (pattrib->dhcp_pkt == 1)
		rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_SPECIAL_PACKET, 1);

	bmcast = IS_MCAST(pattrib->ra);

	/*  get sta_info */
	अगर (bmcast) अणु
		psta = rtw_get_bcmc_stainfo(padapter);
	पूर्ण अन्यथा अणु
		psta = rtw_get_stainfo(pstapriv, pattrib->ra);
		अगर (!psta)	अणु /*  अगर we cannot get psta => drop the pkt */
			res = _FAIL;
			जाओ निकास;
		पूर्ण अन्यथा अगर ((check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) && (!(psta->state & _FW_LINKED))) अणु
			res = _FAIL;
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (!psta) अणु
		/*  अगर we cannot get psta => drop the pkt */
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (!(psta->state & _FW_LINKED))
		वापस _FAIL;

	/* TODO:_lock */
	अगर (update_attrib_sec_info(padapter, pattrib, psta) == _FAIL) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	update_attrib_phy_info(padapter, pattrib, psta);

	pattrib->psta = psta;
	/* TODO:_unlock */

	pattrib->pctrl = 0;

	pattrib->ack_policy = 0;
	/*  get ether_hdr_len */
	pattrib->pkt_hdrlen = ETH_HLEN;/* pattrib->ether_type == 0x8100) ? (14 + 4): 14; vlan tag */

	pattrib->hdrlen = WLAN_HDR_A3_LEN;
	pattrib->subtype = WIFI_DATA_TYPE;
	pattrib->priority = 0;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE|WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE)) अणु
		अगर (pattrib->qos_en)
			set_qos(&pktfile, pattrib);
	पूर्ण अन्यथा अणु
		अगर (pqospriv->qos_option) अणु
			set_qos(&pktfile, pattrib);

			अगर (pmlmepriv->acm_mask != 0)
				pattrib->priority = qos_acm(pmlmepriv->acm_mask, pattrib->priority);
		पूर्ण
	पूर्ण

	/* pattrib->priority = 5; क्रमce to used VI queue, क्रम testing */

निकास:
	वापस res;
पूर्ण

अटल s32 xmitframe_addmic(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	चिन्हित पूर्णांक			curfragnum, length;
	u8 *pframe, *payload, mic[8];
	काष्ठा mic_data micdata;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u8 priority[4] = अणु0x0, 0x0, 0x0, 0x0पूर्ण;
	u8 hw_hdr_offset = 0;
	चिन्हित पूर्णांक bmcst = IS_MCAST(pattrib->ra);

	hw_hdr_offset = TXDESC_OFFSET;

	अगर (pattrib->encrypt == _TKIP_) अणु
		/* encode mic code */
		अणु
			u8 null_key[16] = अणु0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0पूर्ण;

			pframe = pxmitframe->buf_addr + hw_hdr_offset;

			अगर (bmcst) अणु
				अगर (!स_भेद(psecuritypriv->करोt118021XGrptxmickey[psecuritypriv->करोt118021XGrpKeyid].skey, null_key, 16))
					वापस _FAIL;
				/* start to calculate the mic code */
				rtw_secmicsetkey(&micdata, psecuritypriv->करोt118021XGrptxmickey[psecuritypriv->करोt118021XGrpKeyid].skey);
			पूर्ण अन्यथा अणु
				अगर (!स_भेद(&pattrib->करोt11tkiptxmickey.skey[0], null_key, 16))
					वापस _FAIL;
				/* start to calculate the mic code */
				rtw_secmicsetkey(&micdata, &pattrib->करोt11tkiptxmickey.skey[0]);
			पूर्ण

			अगर (pframe[1]&1) अणु   /* ToDS == 1 */
				rtw_secmicappend(&micdata, &pframe[16], 6);  /* DA */
				अगर (pframe[1]&2)  /* From Ds == 1 */
					rtw_secmicappend(&micdata, &pframe[24], 6);
				अन्यथा
					rtw_secmicappend(&micdata, &pframe[10], 6);
			पूर्ण अन्यथा अणु	/* ToDS == 0 */
				rtw_secmicappend(&micdata, &pframe[4], 6);   /* DA */
				अगर (pframe[1]&2)  /* From Ds == 1 */
					rtw_secmicappend(&micdata, &pframe[16], 6);
				अन्यथा
					rtw_secmicappend(&micdata, &pframe[10], 6);
			पूर्ण

			अगर (pattrib->qos_en)
				priority[0] = (u8)pxmitframe->attrib.priority;

			rtw_secmicappend(&micdata, &priority[0], 4);

			payload = pframe;

			क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags; curfragnum++) अणु
				payload = (u8 *)round_up((SIZE_PTR)(payload), 4);
				payload = payload+pattrib->hdrlen+pattrib->iv_len;

				अगर ((curfragnum+1) == pattrib->nr_frags) अणु
					length = pattrib->last_txcmdsz-pattrib->hdrlen-pattrib->iv_len-((pattrib->bswenc) ? pattrib->icv_len : 0);
					rtw_secmicappend(&micdata, payload, length);
					payload = payload+length;
				पूर्ण अन्यथा अणु
					length = pxmitpriv->frag_len-pattrib->hdrlen-pattrib->iv_len-((pattrib->bswenc) ? pattrib->icv_len : 0);
					rtw_secmicappend(&micdata, payload, length);
					payload = payload+length+pattrib->icv_len;
				पूर्ण
			पूर्ण
			rtw_secgeपंचांगic(&micdata, &mic[0]);
			/* add mic code  and add the mic code length in last_txcmdsz */

			स_नकल(payload, &mic[0], 8);
			pattrib->last_txcmdsz += 8;
			पूर्ण
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अटल s32 xmitframe_swencrypt(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा	pkt_attrib	 *pattrib = &pxmitframe->attrib;

	अगर (pattrib->bswenc) अणु
		चयन (pattrib->encrypt) अणु
		हाल _WEP40_:
		हाल _WEP104_:
			rtw_wep_encrypt(padapter, (u8 *)pxmitframe);
			अवरोध;
		हाल _TKIP_:
			rtw_tkip_encrypt(padapter, (u8 *)pxmitframe);
			अवरोध;
		हाल _AES_:
			rtw_aes_encrypt(padapter, (u8 *)pxmitframe);
			अवरोध;
		शेष:
				अवरोध;
		पूर्ण
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
	चिन्हित पूर्णांक res = _SUCCESS;
	__le16 *fctrl = &pwlanhdr->frame_control;

	स_रखो(hdr, 0, WLANHDR_OFFSET);

	SetFrameSubType(fctrl, pattrib->subtype);

	अगर (pattrib->subtype & WIFI_DATA_TYPE) अणु
		अगर (check_fwstate(pmlmepriv,  WIFI_STATION_STATE) == true) अणु
			/* to_ds = 1, fr_ds = 0; */

			अणु
				/*  1.Data transfer to AP */
				/*  2.Arp pkt will relayed by AP */
				SetToDs(fctrl);
				स_नकल(pwlanhdr->addr1, get_bssid(pmlmepriv), ETH_ALEN);
				स_नकल(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
				स_नकल(pwlanhdr->addr3, pattrib->dst, ETH_ALEN);
			पूर्ण

			अगर (pqospriv->qos_option)
				qos_option = true;
		पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv,  WIFI_AP_STATE) == true) अणु
			/* to_ds = 0, fr_ds = 1; */
			SetFrDs(fctrl);
			स_नकल(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
			स_नकल(pwlanhdr->addr2, get_bssid(pmlmepriv), ETH_ALEN);
			स_नकल(pwlanhdr->addr3, pattrib->src, ETH_ALEN);

			अगर (pattrib->qos_en)
				qos_option = true;
		पूर्ण अन्यथा अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)) अणु
			स_नकल(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
			स_नकल(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
			स_नकल(pwlanhdr->addr3, get_bssid(pmlmepriv), ETH_ALEN);

			अगर (pattrib->qos_en)
				qos_option = true;
		पूर्ण अन्यथा अणु
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
		अणु
			काष्ठा sta_info *psta;

			psta = rtw_get_stainfo(&padapter->stapriv, pattrib->ra);
			अगर (pattrib->psta != psta)
				वापस _FAIL;

			अगर (!psta)
				वापस _FAIL;

			अगर (!(psta->state & _FW_LINKED))
				वापस _FAIL;

			अगर (psta) अणु
				psta->sta_xmitpriv.txseq_tid[pattrib->priority]++;
				psta->sta_xmitpriv.txseq_tid[pattrib->priority] &= 0xFFF;
				pattrib->seqnum = psta->sta_xmitpriv.txseq_tid[pattrib->priority];

				SetSeqNum(hdr, pattrib->seqnum);

				/* check अगर enable ampdu */
				अगर (pattrib->ht_en && psta->htpriv.ampdu_enable)
					अगर (psta->htpriv.agg_enable_biपंचांगap & BIT(pattrib->priority))
						pattrib->ampdu_en = true;

				/* re-check अगर enable ampdu by BA_starting_seqctrl */
				अगर (pattrib->ampdu_en == true) अणु
					u16 tx_seq;

					tx_seq = psta->BA_starting_seqctrl[pattrib->priority & 0x0f];

					/* check BA_starting_seqctrl */
					अगर (SN_LESS(pattrib->seqnum, tx_seq)) अणु
						pattrib->ampdu_en = false;/* AGG BK */
					पूर्ण अन्यथा अगर (SN_EQUAL(pattrib->seqnum, tx_seq)) अणु
						psta->BA_starting_seqctrl[pattrib->priority & 0x0f] = (tx_seq+1)&0xfff;

						pattrib->ampdu_en = true;/* AGG EN */
					पूर्ण अन्यथा अणु
						psta->BA_starting_seqctrl[pattrib->priority & 0x0f] = (pattrib->seqnum+1)&0xfff;
						pattrib->ampdu_en = true;/* AGG EN */
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
	पूर्ण

निकास:
	वापस res;
पूर्ण

s32 rtw_txframes_pending(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	वापस ((!list_empty(&pxmitpriv->be_pending.queue)) ||
			 (!list_empty(&pxmitpriv->bk_pending.queue)) ||
			 (!list_empty(&pxmitpriv->vi_pending.queue)) ||
			 (!list_empty(&pxmitpriv->vo_pending.queue)));
पूर्ण

/*
 * Calculate wlan 802.11 packet MAX size from pkt_attrib
 * This function करोesn't consider fragment हाल
 */
u32 rtw_calculate_wlan_pkt_size_by_attribue(काष्ठा pkt_attrib *pattrib)
अणु
	u32 len = 0;

	len = pattrib->hdrlen + pattrib->iv_len; /*  WLAN Header and IV */
	len += SNAP_SIZE + माप(u16); /*  LLC */
	len += pattrib->pktlen;
	अगर (pattrib->encrypt == _TKIP_)
		len += 8; /*  MIC */
	len += ((pattrib->bswenc) ? pattrib->icv_len : 0); /*  ICV */

	वापस len;
पूर्ण

/*
 * This sub-routine will perक्रमm all the following:
 * 1. हटाओ 802.3 header.
 * 2. create wlan_header, based on the info in pxmitframe
 * 3. append sta's iv/ext-iv
 * 4. append LLC
 * 5. move frag chunk from pframe to pxmitframe->mem
 * 6. apply sw-encrypt, अगर necessary.
 */
s32 rtw_xmitframe_coalesce(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt, काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा pkt_file pktfile;

	s32 frg_inx, frg_len, mpdu_len, llc_sz, mem_sz;

	SIZE_PTR addr;

	u8 *pframe, *mem_start;
	u8 hw_hdr_offset;

	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	काष्ठा pkt_attrib	*pattrib = &pxmitframe->attrib;

	u8 *pbuf_start;

	s32 bmcst = IS_MCAST(pattrib->ra);
	s32 res = _SUCCESS;

	अगर (!pxmitframe->buf_addr)
		वापस _FAIL;

	pbuf_start = pxmitframe->buf_addr;

	hw_hdr_offset = TXDESC_OFFSET;
	mem_start = pbuf_start +	hw_hdr_offset;

	अगर (rtw_make_wlanhdr(padapter, mem_start, pattrib) == _FAIL) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	_rtw_खोलो_pktfile(pkt, &pktfile);
	_rtw_pktfile_पढ़ो(&pktfile, शून्य, pattrib->pkt_hdrlen);

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
			स_नकल(pframe, pattrib->iv, pattrib->iv_len);

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

		अगर (bmcst) अणु
			/*  करोn't करो fragment to broadcast/multicast packets */
			mem_sz = _rtw_pktfile_पढ़ो(&pktfile, pframe, pattrib->pktlen);
		पूर्ण अन्यथा अणु
			mem_sz = _rtw_pktfile_पढ़ो(&pktfile, pframe, mpdu_len);
		पूर्ण

		pframe += mem_sz;

		अगर ((pattrib->icv_len > 0) && (pattrib->bswenc)) अणु
			स_नकल(pframe, pattrib->icv, pattrib->icv_len);
			pframe += pattrib->icv_len;
		पूर्ण

		frg_inx++;

		अगर (bmcst || (rtw_enकरोfpktfile(&pktfile) == true)) अणु
			pattrib->nr_frags = frg_inx;

			pattrib->last_txcmdsz = pattrib->hdrlen + pattrib->iv_len + ((pattrib->nr_frags == 1) ? llc_sz:0) +
					((pattrib->bswenc) ? pattrib->icv_len : 0) + mem_sz;

			ClearMFrag(mem_start);

			अवरोध;
		पूर्ण

		addr = (SIZE_PTR)(pframe);

		mem_start = (अचिन्हित अक्षर *)round_up(addr, 4) + hw_hdr_offset;
		स_नकल(mem_start, pbuf_start + hw_hdr_offset, pattrib->hdrlen);
	पूर्ण

	अगर (xmitframe_addmic(padapter, pxmitframe) == _FAIL) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	xmitframe_swencrypt(padapter, pxmitframe);

	अगर (bmcst == false)
		update_attrib_vcs_info(padapter, pxmitframe);
	अन्यथा
		pattrib->vcs_mode = NONE_VCS;

निकास:
	वापस res;
पूर्ण

/* broadcast or multicast management pkt use BIP, unicast management pkt use CCMP encryption */
s32 rtw_mgmt_xmitframe_coalesce(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt, काष्ठा xmit_frame *pxmitframe)
अणु
	u8 *pframe, *mem_start = शून्य, *पंचांगp_buf = शून्य;
	u8 subtype;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	s32 bmcst = IS_MCAST(pattrib->ra);
	u8 *BIP_AAD = शून्य;
	u8 *MGMT_body = शून्य;

	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ieee80211_hdr	*pwlanhdr;
	u8 MME[_MME_IE_LENGTH_];
	u32 ori_len;

	mem_start = pframe = (u8 *)(pxmitframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (काष्ठा ieee80211_hdr *)pframe;

	ori_len = BIP_AAD_SIZE+pattrib->pktlen;
	पंचांगp_buf = BIP_AAD = rtw_zदो_स्मृति(ori_len);
	subtype = GetFrameSubType(pframe); /* bit(7)~bit(2) */

	अगर (!BIP_AAD)
		वापस _FAIL;

	spin_lock_bh(&padapter->security_key_mutex);

	/* only support station mode */
	अगर (!check_fwstate(pmlmepriv, WIFI_STATION_STATE) || !check_fwstate(pmlmepriv, _FW_LINKED))
		जाओ xmitframe_coalesce_success;

	/* IGTK key is not install, it may not support 802.11w */
	अगर (!padapter->securitypriv.binstallBIPkey)
		जाओ xmitframe_coalesce_success;

	/* station mode करोesn't need TX BIP, just पढ़ोy the code */
	अगर (bmcst) अणु
		पूर्णांक frame_body_len;
		u8 mic[16];

		स_रखो(MME, 0, 18);

		/* other types करोesn't need the BIP */
		अगर (GetFrameSubType(pframe) != WIFI_DEAUTH && GetFrameSubType(pframe) != WIFI_DISASSOC)
			जाओ xmitframe_coalesce_fail;

		MGMT_body = pframe + माप(काष्ठा ieee80211_hdr_3addr);
		pframe += pattrib->pktlen;

		/* octent 0 and 1 is key index , BIP keyid is 4 or 5, LSB only need octent 0 */
		MME[0] = padapter->securitypriv.करोt11wBIPKeyid;
		/* copy packet number */
		स_नकल(&MME[2], &pmlmeext->mgnt_80211w_IPN, 6);
		/* increase the packet number */
		pmlmeext->mgnt_80211w_IPN++;

		/* add MME IE with MIC all zero, MME string करोesn't include element id and length */
		pframe = rtw_set_ie(pframe, WLAN_EID_MMIE, 16,
				    MME, &pattrib->pktlen);
		pattrib->last_txcmdsz = pattrib->pktlen;
		/*  total frame length - header length */
		frame_body_len = pattrib->pktlen - माप(काष्ठा ieee80211_hdr_3addr);

		/* conscruct AAD, copy frame control field */
		स_नकल(BIP_AAD, &pwlanhdr->frame_control, 2);
		ClearRetry(BIP_AAD);
		ClearPwrMgt(BIP_AAD);
		ClearMData(BIP_AAD);
		/* conscruct AAD, copy address 1 to address 3 */
		स_नकल(BIP_AAD+2, pwlanhdr->addr1, 18);
		/* copy management fram body */
		स_नकल(BIP_AAD+BIP_AAD_SIZE, MGMT_body, frame_body_len);
		/* calculate mic */
		अगर (omac1_aes_128(padapter->securitypriv.करोt11wBIPKey[padapter->securitypriv.करोt11wBIPKeyid].skey
			, BIP_AAD, BIP_AAD_SIZE+frame_body_len, mic))
			जाओ xmitframe_coalesce_fail;

		/* copy right BIP mic value, total is 128bits, we use the 0~63 bits */
		स_नकल(pframe-8, mic, 8);
	पूर्ण अन्यथा अणु /* unicast mgmt frame TX */
		/* start to encrypt mgmt frame */
		अगर (subtype == WIFI_DEAUTH || subtype == WIFI_DISASSOC ||
			subtype == WIFI_REASSOCREQ || subtype == WIFI_ACTION) अणु
			अगर (pattrib->psta)
				psta = pattrib->psta;
			अन्यथा
				psta = rtw_get_stainfo(&padapter->stapriv, pattrib->ra);

			अगर (!psta)
				जाओ xmitframe_coalesce_fail;

			अगर (!(psta->state & _FW_LINKED) || !pxmitframe->buf_addr)
				जाओ xmitframe_coalesce_fail;

			/* according 802.11-2012 standard, these five types are not robust types */
			अगर (subtype == WIFI_ACTION &&
			(pframe[WLAN_HDR_A3_LEN] == RTW_WLAN_CATEGORY_PUBLIC ||
			pframe[WLAN_HDR_A3_LEN] == RTW_WLAN_CATEGORY_HT ||
			pframe[WLAN_HDR_A3_LEN] == RTW_WLAN_CATEGORY_UNPROTECTED_WNM ||
			pframe[WLAN_HDR_A3_LEN] == RTW_WLAN_CATEGORY_SELF_PROTECTED  ||
			pframe[WLAN_HDR_A3_LEN] == RTW_WLAN_CATEGORY_P2P))
				जाओ xmitframe_coalesce_fail;
			/* beक्रमe encrypt dump the management packet content */
			अगर (pattrib->encrypt > 0)
				स_नकल(pattrib->करोt118021x_UncstKey.skey, psta->करोt118021x_UncstKey.skey, 16);
			/* bakeup original management packet */
			स_नकल(पंचांगp_buf, pframe, pattrib->pktlen);
			/* move to data portion */
			pframe += pattrib->hdrlen;

			/* 802.11w unicast management packet must be _AES_ */
			pattrib->iv_len = 8;
			/* it's MIC of AES */
			pattrib->icv_len = 8;

			चयन (pattrib->encrypt) अणु
			हाल _AES_:
					/* set AES IV header */
					AES_IV(pattrib->iv, psta->करोt11wtxpn, 0);
				अवरोध;
			शेष:
				जाओ xmitframe_coalesce_fail;
			पूर्ण
			/* insert iv header पूर्णांकo management frame */
			स_नकल(pframe, pattrib->iv, pattrib->iv_len);
			pframe += pattrib->iv_len;
			/* copy mgmt data portion after CCMP header */
			स_नकल(pframe, पंचांगp_buf+pattrib->hdrlen, pattrib->pktlen-pattrib->hdrlen);
			/* move pframe to end of mgmt pkt */
			pframe += pattrib->pktlen-pattrib->hdrlen;
			/* add 8 bytes CCMP IV header to length */
			pattrib->pktlen += pattrib->iv_len;
			अगर ((pattrib->icv_len > 0) && (pattrib->bswenc)) अणु
				स_नकल(pframe, pattrib->icv, pattrib->icv_len);
				pframe += pattrib->icv_len;
			पूर्ण
			/* add 8 bytes MIC */
			pattrib->pktlen += pattrib->icv_len;
			/* set final tx command size */
			pattrib->last_txcmdsz = pattrib->pktlen;

			/* set रक्षित bit must be beofre SW encrypt */
			SetPrivacy(mem_start);
			/* software encrypt */
			xmitframe_swencrypt(padapter, pxmitframe);
		पूर्ण
	पूर्ण

xmitframe_coalesce_success:
	spin_unlock_bh(&padapter->security_key_mutex);
	kमुक्त(BIP_AAD);
	वापस _SUCCESS;

xmitframe_coalesce_fail:
	spin_unlock_bh(&padapter->security_key_mutex);
	kमुक्त(BIP_AAD);
	वापस _FAIL;
पूर्ण

/* Logical Link Control(LLC) SubNetwork Attachment Poपूर्णांक(SNAP) header
 * IEEE LLC/SNAP header contains 8 octets
 * First 3 octets comprise the LLC portion
 * SNAP portion, 5 octets, is भागided पूर्णांकo two fields:
 *Organizationally Unique Identअगरier(OUI), 3 octets,
 *type, defined by that organization, 2 octets.
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
	uपूर्णांक	protection;
	u8 *perp;
	चिन्हित पूर्णांक	 erp_len;
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
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	u8 pkt_num = 1;

	अगर ((pxmitframe->frame_tag&0x0f) == DATA_FRAMETAG) अणु
		pkt_num = pxmitframe->agg_num;

		pmlmepriv->LinkDetectInfo.NumTxOkInPeriod += pkt_num;

		pxmitpriv->tx_pkts += pkt_num;

		pxmitpriv->tx_bytes += sz;

		psta = pxmitframe->attrib.psta;
		अगर (psta) अणु
			pstats = &psta->sta_stats;

			pstats->tx_pkts += pkt_num;

			pstats->tx_bytes += sz;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा xmit_buf *__rtw_alloc_cmd_xmitbuf(काष्ठा xmit_priv *pxmitpriv,
		क्रमागत cmdbuf_type buf_type)
अणु
	काष्ठा xmit_buf *pxmitbuf =  शून्य;

	pxmitbuf = &pxmitpriv->pcmd_xmitbuf[buf_type];
	अगर (pxmitbuf) अणु
		pxmitbuf->priv_data = शून्य;

		pxmitbuf->len = 0;
		pxmitbuf->pdata = pxmitbuf->ptail = pxmitbuf->phead;
		pxmitbuf->agg_num = 0;
		pxmitbuf->pg_num = 0;

		अगर (pxmitbuf->sctx)
			rtw_sctx_करोne_err(&pxmitbuf->sctx, RTW_SCTX_DONE_BUF_ALLOC);
	पूर्ण

	वापस pxmitbuf;
पूर्ण

काष्ठा xmit_frame *__rtw_alloc_cmdxmitframe(काष्ठा xmit_priv *pxmitpriv,
		क्रमागत cmdbuf_type buf_type)
अणु
	काष्ठा xmit_frame		*pcmdframe;
	काष्ठा xmit_buf		*pxmitbuf;

	pcmdframe = rtw_alloc_xmitframe(pxmitpriv);
	अगर (!pcmdframe)
		वापस शून्य;

	pxmitbuf = __rtw_alloc_cmd_xmitbuf(pxmitpriv, buf_type);
	अगर (!pxmitbuf) अणु
		rtw_मुक्त_xmitframe(pxmitpriv, pcmdframe);
		वापस शून्य;
	पूर्ण

	pcmdframe->frame_tag = MGNT_FRAMETAG;

	pcmdframe->pxmitbuf = pxmitbuf;

	pcmdframe->buf_addr = pxmitbuf->pbuf;

	pxmitbuf->priv_data = pcmdframe;

	वापस pcmdframe;
पूर्ण

काष्ठा xmit_buf *rtw_alloc_xmitbuf_ext(काष्ठा xmit_priv *pxmitpriv)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा xmit_buf *pxmitbuf =  शून्य;
	काष्ठा list_head *plist, *phead;
	काष्ठा __queue *pमुक्त_queue = &pxmitpriv->मुक्त_xmit_extbuf_queue;

	spin_lock_irqsave(&pमुक्त_queue->lock, irqL);

	अगर (list_empty(&pमुक्त_queue->queue)) अणु
		pxmitbuf = शून्य;
	पूर्ण अन्यथा अणु
		phead = get_list_head(pमुक्त_queue);

		plist = get_next(phead);

		pxmitbuf = container_of(plist, काष्ठा xmit_buf, list);

		list_del_init(&pxmitbuf->list);
	पूर्ण

	अगर (pxmitbuf) अणु
		pxmitpriv->मुक्त_xmit_extbuf_cnt--;

		pxmitbuf->priv_data = शून्य;

		pxmitbuf->len = 0;
		pxmitbuf->pdata = pxmitbuf->ptail = pxmitbuf->phead;
		pxmitbuf->agg_num = 1;

		अगर (pxmitbuf->sctx)
			rtw_sctx_करोne_err(&pxmitbuf->sctx, RTW_SCTX_DONE_BUF_ALLOC);
	पूर्ण

	spin_unlock_irqrestore(&pमुक्त_queue->lock, irqL);

	वापस pxmitbuf;
पूर्ण

s32 rtw_मुक्त_xmitbuf_ext(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा __queue *pमुक्त_queue = &pxmitpriv->मुक्त_xmit_extbuf_queue;

	अगर (!pxmitbuf)
		वापस _FAIL;

	spin_lock_irqsave(&pमुक्त_queue->lock, irqL);

	list_del_init(&pxmitbuf->list);

	list_add_tail(&pxmitbuf->list, get_list_head(pमुक्त_queue));
	pxmitpriv->मुक्त_xmit_extbuf_cnt++;

	spin_unlock_irqrestore(&pमुक्त_queue->lock, irqL);

	वापस _SUCCESS;
पूर्ण

काष्ठा xmit_buf *rtw_alloc_xmitbuf(काष्ठा xmit_priv *pxmitpriv)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा xmit_buf *pxmitbuf =  शून्य;
	काष्ठा list_head *plist, *phead;
	काष्ठा __queue *pमुक्त_xmitbuf_queue = &pxmitpriv->मुक्त_xmitbuf_queue;

	spin_lock_irqsave(&pमुक्त_xmitbuf_queue->lock, irqL);

	अगर (list_empty(&pमुक्त_xmitbuf_queue->queue)) अणु
		pxmitbuf = शून्य;
	पूर्ण अन्यथा अणु
		phead = get_list_head(pमुक्त_xmitbuf_queue);

		plist = get_next(phead);

		pxmitbuf = container_of(plist, काष्ठा xmit_buf, list);

		list_del_init(&pxmitbuf->list);
	पूर्ण

	अगर (pxmitbuf) अणु
		pxmitpriv->मुक्त_xmitbuf_cnt--;

		pxmitbuf->priv_data = शून्य;

		pxmitbuf->len = 0;
		pxmitbuf->pdata = pxmitbuf->ptail = pxmitbuf->phead;
		pxmitbuf->agg_num = 0;
		pxmitbuf->pg_num = 0;

		अगर (pxmitbuf->sctx)
			rtw_sctx_करोne_err(&pxmitbuf->sctx, RTW_SCTX_DONE_BUF_ALLOC);
	पूर्ण

	spin_unlock_irqrestore(&pमुक्त_xmitbuf_queue->lock, irqL);

	वापस pxmitbuf;
पूर्ण

s32 rtw_मुक्त_xmitbuf(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा __queue *pमुक्त_xmitbuf_queue = &pxmitpriv->मुक्त_xmitbuf_queue;

	अगर (!pxmitbuf)
		वापस _FAIL;

	अगर (pxmitbuf->sctx)
		rtw_sctx_करोne_err(&pxmitbuf->sctx, RTW_SCTX_DONE_BUF_FREE);

	अगर (pxmitbuf->buf_tag == XMITBUF_CMD) अणु
	पूर्ण अन्यथा अगर (pxmitbuf->buf_tag == XMITBUF_MGNT) अणु
		rtw_मुक्त_xmitbuf_ext(pxmitpriv, pxmitbuf);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&pमुक्त_xmitbuf_queue->lock, irqL);

		list_del_init(&pxmitbuf->list);

		list_add_tail(&pxmitbuf->list,
			      get_list_head(pमुक्त_xmitbuf_queue));

		pxmitpriv->मुक्त_xmitbuf_cnt++;
		spin_unlock_irqrestore(&pमुक्त_xmitbuf_queue->lock, irqL);
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अटल व्योम rtw_init_xmitframe(काष्ठा xmit_frame *pxframe)
अणु
	अगर (pxframe) अणु /* शेष value setting */
		pxframe->buf_addr = शून्य;
		pxframe->pxmitbuf = शून्य;

		स_रखो(&pxframe->attrib, 0, माप(काष्ठा pkt_attrib));

		pxframe->frame_tag = DATA_FRAMETAG;

		pxframe->pg_num = 1;
		pxframe->agg_num = 1;
		pxframe->ack_report = 0;
	पूर्ण
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
 */
काष्ठा xmit_frame *rtw_alloc_xmitframe(काष्ठा xmit_priv *pxmitpriv)/* _queue *pमुक्त_xmit_queue) */
अणु
	/*
	 *	Please remember to use all the osdep_service api,
	 *	and lock/unlock or _enter/_निकास critical to protect
	 *	pमुक्त_xmit_queue
	 */

	काष्ठा xmit_frame *pxframe = शून्य;
	काष्ठा list_head *plist, *phead;
	काष्ठा __queue *pमुक्त_xmit_queue = &pxmitpriv->मुक्त_xmit_queue;

	spin_lock_bh(&pमुक्त_xmit_queue->lock);

	अगर (list_empty(&pमुक्त_xmit_queue->queue)) अणु
		pxframe =  शून्य;
	पूर्ण अन्यथा अणु
		phead = get_list_head(pमुक्त_xmit_queue);

		plist = get_next(phead);

		pxframe = container_of(plist, काष्ठा xmit_frame, list);

		list_del_init(&pxframe->list);
		pxmitpriv->मुक्त_xmitframe_cnt--;
	पूर्ण

	spin_unlock_bh(&pमुक्त_xmit_queue->lock);

	rtw_init_xmitframe(pxframe);
	वापस pxframe;
पूर्ण

काष्ठा xmit_frame *rtw_alloc_xmitframe_ext(काष्ठा xmit_priv *pxmitpriv)
अणु
	काष्ठा xmit_frame *pxframe = शून्य;
	काष्ठा list_head *plist, *phead;
	काष्ठा __queue *queue = &pxmitpriv->मुक्त_xframe_ext_queue;

	spin_lock_bh(&queue->lock);

	अगर (list_empty(&queue->queue)) अणु
		pxframe =  शून्य;
	पूर्ण अन्यथा अणु
		phead = get_list_head(queue);
		plist = get_next(phead);
		pxframe = container_of(plist, काष्ठा xmit_frame, list);

		list_del_init(&pxframe->list);
		pxmitpriv->मुक्त_xframe_ext_cnt--;
	पूर्ण

	spin_unlock_bh(&queue->lock);

	rtw_init_xmitframe(pxframe);

	वापस pxframe;
पूर्ण

काष्ठा xmit_frame *rtw_alloc_xmitframe_once(काष्ठा xmit_priv *pxmitpriv)
अणु
	काष्ठा xmit_frame *pxframe = शून्य;
	u8 *alloc_addr;

	alloc_addr = rtw_zदो_स्मृति(माप(काष्ठा xmit_frame) + 4);

	अगर (!alloc_addr)
		जाओ निकास;

	pxframe = (काष्ठा xmit_frame *)N_BYTE_ALIGMENT((SIZE_PTR)(alloc_addr), 4);
	pxframe->alloc_addr = alloc_addr;

	pxframe->padapter = pxmitpriv->adapter;
	pxframe->frame_tag = शून्य_FRAMETAG;

	pxframe->pkt = शून्य;

	pxframe->buf_addr = शून्य;
	pxframe->pxmitbuf = शून्य;

	rtw_init_xmitframe(pxframe);

निकास:
	वापस pxframe;
पूर्ण

s32 rtw_मुक्त_xmitframe(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा __queue *queue = शून्य;
	काष्ठा adapter *padapter = pxmitpriv->adapter;
	काष्ठा sk_buff *pndis_pkt = शून्य;

	अगर (!pxmitframe)
		जाओ निकास;

	अगर (pxmitframe->pkt) अणु
		pndis_pkt = pxmitframe->pkt;
		pxmitframe->pkt = शून्य;
	पूर्ण

	अगर (pxmitframe->alloc_addr) अणु
		kमुक्त(pxmitframe->alloc_addr);
		जाओ check_pkt_complete;
	पूर्ण

	अगर (pxmitframe->ext_tag == 0)
		queue = &pxmitpriv->मुक्त_xmit_queue;
	अन्यथा अगर (pxmitframe->ext_tag == 1)
		queue = &pxmitpriv->मुक्त_xframe_ext_queue;
	अन्यथा अणु
	पूर्ण

	spin_lock_bh(&queue->lock);

	list_del_init(&pxmitframe->list);
	list_add_tail(&pxmitframe->list, get_list_head(queue));
	अगर (pxmitframe->ext_tag == 0)
		pxmitpriv->मुक्त_xmitframe_cnt++;
	अन्यथा अगर (pxmitframe->ext_tag == 1)
		pxmitpriv->मुक्त_xframe_ext_cnt++;

	spin_unlock_bh(&queue->lock);

check_pkt_complete:

	अगर (pndis_pkt)
		rtw_os_pkt_complete(padapter, pndis_pkt);

निकास:
	वापस _SUCCESS;
पूर्ण

व्योम rtw_मुक्त_xmitframe_queue(काष्ठा xmit_priv *pxmitpriv, काष्ठा __queue *pframequeue)
अणु
	काष्ठा list_head	*plist, *phead;
	काष्ठा	xmit_frame	*pxmitframe;

	spin_lock_bh(&pframequeue->lock);

	phead = get_list_head(pframequeue);
	plist = get_next(phead);

	जबतक (phead != plist) अणु
		pxmitframe = container_of(plist, काष्ठा xmit_frame, list);

		plist = get_next(plist);

		rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);
	पूर्ण
	spin_unlock_bh(&pframequeue->lock);
पूर्ण

s32 rtw_xmitframe_enqueue(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	अगर (rtw_xmit_classअगरier(padapter, pxmitframe) == _FAIL)
		वापस _FAIL;

	वापस _SUCCESS;
पूर्ण

काष्ठा tx_servq *rtw_get_sta_pending(काष्ठा adapter *padapter, काष्ठा sta_info *psta, चिन्हित पूर्णांक up, u8 *ac)
अणु
	काष्ठा tx_servq *ptxservq = शून्य;

	चयन (up) अणु
	हाल 1:
	हाल 2:
		ptxservq = &psta->sta_xmitpriv.bk_q;
		*(ac) = 3;
		अवरोध;

	हाल 4:
	हाल 5:
		ptxservq = &psta->sta_xmitpriv.vi_q;
		*(ac) = 1;
		अवरोध;

	हाल 6:
	हाल 7:
		ptxservq = &psta->sta_xmitpriv.vo_q;
		*(ac) = 0;
		अवरोध;

	हाल 0:
	हाल 3:
	शेष:
		ptxservq = &psta->sta_xmitpriv.be_q;
		*(ac) = 2;
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
	u8 ac_index;
	काष्ठा sta_info *psta;
	काष्ठा tx_servq	*ptxservq;
	काष्ठा pkt_attrib	*pattrib = &pxmitframe->attrib;
	काष्ठा hw_xmit	*phwxmits =  padapter->xmitpriv.hwxmits;
	चिन्हित पूर्णांक res = _SUCCESS;

	psta = rtw_get_stainfo(&padapter->stapriv, pattrib->ra);
	अगर (pattrib->psta != psta)
		वापस _FAIL;

	अगर (!psta) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (!(psta->state & _FW_LINKED))
		वापस _FAIL;

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

	pxmitpriv->hwxmits = शून्य;

	pxmitpriv->hwxmits = rtw_zदो_स्मृति(माप(काष्ठा hw_xmit) * pxmitpriv->hwxmit_entry);

	अगर (!pxmitpriv->hwxmits)
		वापस _FAIL;

	hwxmits = pxmitpriv->hwxmits;

	अगर (pxmitpriv->hwxmit_entry == 5) अणु
		hwxmits[0] .sta_queue = &pxmitpriv->bm_pending;

		hwxmits[1] .sta_queue = &pxmitpriv->vo_pending;

		hwxmits[2] .sta_queue = &pxmitpriv->vi_pending;

		hwxmits[3] .sta_queue = &pxmitpriv->bk_pending;

		hwxmits[4] .sta_queue = &pxmitpriv->be_pending;
	पूर्ण अन्यथा अगर (pxmitpriv->hwxmit_entry == 4) अणु
		hwxmits[0] .sta_queue = &pxmitpriv->vo_pending;

		hwxmits[1] .sta_queue = &pxmitpriv->vi_pending;

		hwxmits[2] .sta_queue = &pxmitpriv->be_pending;

		hwxmits[3] .sta_queue = &pxmitpriv->bk_pending;
	पूर्ण अन्यथा अणु
	पूर्ण

	वापस _SUCCESS;
पूर्ण

व्योम rtw_मुक्त_hwxmits(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	kमुक्त(pxmitpriv->hwxmits);
पूर्ण

व्योम rtw_init_hwxmits(काष्ठा hw_xmit *phwxmit, चिन्हित पूर्णांक entry)
अणु
	चिन्हित पूर्णांक i;

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

अटल व्योम करो_queue_select(काष्ठा adapter	*padapter, काष्ठा pkt_attrib *pattrib)
अणु
	u8 qsel;

	qsel = pattrib->priority;

	pattrib->qsel = qsel;
पूर्ण

/*
 * The मुख्य transmit(tx) entry
 *
 * Return
 *1	enqueue
 *0	success, hardware will handle this xmit frame(packet)
 *<0	fail
 */
s32 rtw_xmit(काष्ठा adapter *padapter, काष्ठा sk_buff **ppkt)
अणु
	अटल अचिन्हित दीर्घ start;
	अटल u32 drop_cnt;

	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा xmit_frame *pxmitframe = शून्य;

	s32 res;

	अगर (start == 0)
		start = jअगरfies;

	pxmitframe = rtw_alloc_xmitframe(pxmitpriv);

	अगर (jअगरfies_to_msecs(jअगरfies - start) > 2000) अणु
		start = jअगरfies;
		drop_cnt = 0;
	पूर्ण

	अगर (!pxmitframe) अणु
		drop_cnt++;
		वापस -1;
	पूर्ण

	res = update_attrib(padapter, *ppkt, &pxmitframe->attrib);

	अगर (res == _FAIL) अणु
		rtw_मुक्त_xmitframe(pxmitpriv, pxmitframe);
		वापस -1;
	पूर्ण
	pxmitframe->pkt = *ppkt;

	करो_queue_select(padapter, &pxmitframe->attrib);

	spin_lock_bh(&pxmitpriv->lock);
	अगर (xmitframe_enqueue_क्रम_sleeping_sta(padapter, pxmitframe) == true) अणु
		spin_unlock_bh(&pxmitpriv->lock);
		वापस 1;
	पूर्ण
	spin_unlock_bh(&pxmitpriv->lock);

	/* pre_xmitframe */
	अगर (rtw_hal_xmit(padapter, pxmitframe) == false)
		वापस 1;

	वापस 0;
पूर्ण

#घोषणा RTW_HIQ_FILTER_ALLOW_ALL 0
#घोषणा RTW_HIQ_FILTER_ALLOW_SPECIAL 1
#घोषणा RTW_HIQ_FILTER_DENY_ALL 2

अंतरभूत bool xmitframe_hiq_filter(काष्ठा xmit_frame *xmitframe)
अणु
	bool allow = false;
	काष्ठा adapter *adapter = xmitframe->padapter;
	काष्ठा registry_priv *registry = &adapter->registrypriv;

	अगर (registry->hiq_filter == RTW_HIQ_FILTER_ALLOW_SPECIAL) अणु
		काष्ठा pkt_attrib *attrib = &xmitframe->attrib;

		अगर (attrib->ether_type == 0x0806 ||
		    attrib->ether_type == 0x888e ||
		    attrib->dhcp_pkt
		)
			allow = true;

	पूर्ण अन्यथा अगर (registry->hiq_filter == RTW_HIQ_FILTER_ALLOW_ALL)
		allow = true;
	अन्यथा अगर (registry->hiq_filter == RTW_HIQ_FILTER_DENY_ALL) अणु
	पूर्ण अन्यथा
		rtw_warn_on(1);

	वापस allow;
पूर्ण

चिन्हित पूर्णांक xmitframe_enqueue_क्रम_sleeping_sta(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	चिन्हित पूर्णांक ret = false;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	चिन्हित पूर्णांक bmcst = IS_MCAST(pattrib->ra);
	bool update_tim = false;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == false)
		वापस ret;
	psta = rtw_get_stainfo(&padapter->stapriv, pattrib->ra);
	अगर (pattrib->psta != psta)
		वापस false;

	अगर (!psta)
		वापस false;

	अगर (!(psta->state & _FW_LINKED))
		वापस false;

	अगर (pattrib->triggered == 1) अणु
		अगर (bmcst && xmitframe_hiq_filter(pxmitframe))
			pattrib->qsel = 0x11;/* HIQ */

		वापस ret;
	पूर्ण

	अगर (bmcst) अणु
		spin_lock_bh(&psta->sleep_q.lock);

		अगर (pstapriv->sta_dz_biपंचांगap) अणु /* अगर anyone sta is in ps mode */
			/* pattrib->qsel = 0x11;HIQ */

			list_del_init(&pxmitframe->list);

			list_add_tail(&pxmitframe->list, get_list_head(&psta->sleep_q));

			psta->sleepq_len++;

			अगर (!(pstapriv->tim_biपंचांगap & BIT(0)))
				update_tim = true;

			pstapriv->tim_biपंचांगap |= BIT(0);
			pstapriv->sta_dz_biपंचांगap |= BIT(0);

			अगर (update_tim)
				update_beacon(padapter, WLAN_EID_TIM, शून्य, true);
			अन्यथा
				chk_bmc_sleepq_cmd(padapter);

			ret = true;
		पूर्ण

		spin_unlock_bh(&psta->sleep_q.lock);

		वापस ret;
	पूर्ण

	spin_lock_bh(&psta->sleep_q.lock);

	अगर (psta->state&WIFI_SLEEP_STATE) अणु
		u8 wmmps_ac = 0;

		अगर (pstapriv->sta_dz_biपंचांगap & BIT(psta->aid)) अणु
			list_del_init(&pxmitframe->list);

			list_add_tail(&pxmitframe->list, get_list_head(&psta->sleep_q));

			psta->sleepq_len++;

			चयन (pattrib->priority) अणु
			हाल 1:
			हाल 2:
				wmmps_ac = psta->uapsd_bk&BIT(0);
				अवरोध;
			हाल 4:
			हाल 5:
				wmmps_ac = psta->uapsd_vi&BIT(0);
				अवरोध;
			हाल 6:
			हाल 7:
				wmmps_ac = psta->uapsd_vo&BIT(0);
				अवरोध;
			हाल 0:
			हाल 3:
			शेष:
				wmmps_ac = psta->uapsd_be&BIT(0);
				अवरोध;
			पूर्ण

			अगर (wmmps_ac)
				psta->sleepq_ac_len++;

			अगर (((psta->has_legacy_ac) && (!wmmps_ac)) || ((!psta->has_legacy_ac) && (wmmps_ac))) अणु
				अगर (!(pstapriv->tim_biपंचांगap & BIT(psta->aid)))
					update_tim = true;

				pstapriv->tim_biपंचांगap |= BIT(psta->aid);

				अगर (update_tim)
					/* update BCN क्रम TIM IE */
					update_beacon(padapter, WLAN_EID_TIM, शून्य, true);
			पूर्ण

			ret = true;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&psta->sleep_q.lock);

	वापस ret;
पूर्ण

अटल व्योम dequeue_xmitframes_to_sleeping_queue(काष्ठा adapter *padapter, काष्ठा sta_info *psta, काष्ठा __queue *pframequeue)
अणु
	चिन्हित पूर्णांक ret;
	काष्ठा list_head	*plist, *phead;
	u8 ac_index;
	काष्ठा tx_servq	*ptxservq;
	काष्ठा pkt_attrib	*pattrib;
	काष्ठा xmit_frame	*pxmitframe;
	काष्ठा hw_xmit *phwxmits =  padapter->xmitpriv.hwxmits;

	phead = get_list_head(pframequeue);
	plist = get_next(phead);

	जबतक (phead != plist) अणु
		pxmitframe = container_of(plist, काष्ठा xmit_frame, list);

		plist = get_next(plist);

		pattrib = &pxmitframe->attrib;

		pattrib->triggered = 0;

		ret = xmitframe_enqueue_क्रम_sleeping_sta(padapter, pxmitframe);

		अगर (true == ret) अणु
			ptxservq = rtw_get_sta_pending(padapter, psta, pattrib->priority, (u8 *)(&ac_index));

			ptxservq->qcnt--;
			phwxmits[ac_index].accnt--;
		पूर्ण अन्यथा अणु
		पूर्ण
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

	dequeue_xmitframes_to_sleeping_queue(padapter, psta, &pstaxmitpriv->vo_q.sta_pending);
	list_del_init(&pstaxmitpriv->vo_q.tx_pending);

	dequeue_xmitframes_to_sleeping_queue(padapter, psta, &pstaxmitpriv->vi_q.sta_pending);
	list_del_init(&pstaxmitpriv->vi_q.tx_pending);

	dequeue_xmitframes_to_sleeping_queue(padapter, psta, &pstaxmitpriv->be_q.sta_pending);
	list_del_init(&pstaxmitpriv->be_q.tx_pending);

	dequeue_xmitframes_to_sleeping_queue(padapter, psta, &pstaxmitpriv->bk_q.sta_pending);
	list_del_init(&pstaxmitpriv->bk_q.tx_pending);

	/* क्रम BC/MC Frames */
	pstaxmitpriv = &psta_bmc->sta_xmitpriv;
	dequeue_xmitframes_to_sleeping_queue(padapter, psta_bmc, &pstaxmitpriv->be_q.sta_pending);
	list_del_init(&pstaxmitpriv->be_q.tx_pending);

	spin_unlock_bh(&pxmitpriv->lock);
पूर्ण

व्योम wakeup_sta_to_xmit(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 update_mask = 0, wmmps_ac = 0;
	काष्ठा sta_info *psta_bmc;
	काष्ठा list_head	*xmitframe_plist, *xmitframe_phead;
	काष्ठा xmit_frame *pxmitframe = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	psta_bmc = rtw_get_bcmc_stainfo(padapter);

	spin_lock_bh(&pxmitpriv->lock);

	xmitframe_phead = get_list_head(&psta->sleep_q);
	xmitframe_plist = get_next(xmitframe_phead);

	जबतक (xmitframe_phead != xmitframe_plist) अणु
		pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

		xmitframe_plist = get_next(xmitframe_plist);

		list_del_init(&pxmitframe->list);

		चयन (pxmitframe->attrib.priority) अणु
		हाल 1:
		हाल 2:
			wmmps_ac = psta->uapsd_bk&BIT(1);
			अवरोध;
		हाल 4:
		हाल 5:
			wmmps_ac = psta->uapsd_vi&BIT(1);
			अवरोध;
		हाल 6:
		हाल 7:
			wmmps_ac = psta->uapsd_vo&BIT(1);
			अवरोध;
		हाल 0:
		हाल 3:
		शेष:
			wmmps_ac = psta->uapsd_be&BIT(1);
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

		rtw_hal_xmitframe_enqueue(padapter, pxmitframe);
	पूर्ण

	अगर (psta->sleepq_len == 0) अणु
		अगर (pstapriv->tim_biपंचांगap & BIT(psta->aid))
			update_mask = BIT(0);

		pstapriv->tim_biपंचांगap &= ~BIT(psta->aid);

		अगर (psta->state&WIFI_SLEEP_STATE)
			psta->state ^= WIFI_SLEEP_STATE;

		अगर (psta->state & WIFI_STA_ALIVE_CHK_STATE) अणु
			psta->expire_to = pstapriv->expire_to;
			psta->state ^= WIFI_STA_ALIVE_CHK_STATE;
		पूर्ण

		pstapriv->sta_dz_biपंचांगap &= ~BIT(psta->aid);
	पूर्ण

	/* क्रम BC/MC Frames */
	अगर (!psta_bmc)
		जाओ _निकास;

	अगर ((pstapriv->sta_dz_biपंचांगap&0xfffe) == 0x0) अणु /* no any sta in ps mode */
		xmitframe_phead = get_list_head(&psta_bmc->sleep_q);
		xmitframe_plist = get_next(xmitframe_phead);

		जबतक (xmitframe_phead != xmitframe_plist) अणु
			pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

			xmitframe_plist = get_next(xmitframe_plist);

			list_del_init(&pxmitframe->list);

			psta_bmc->sleepq_len--;
			अगर (psta_bmc->sleepq_len > 0)
				pxmitframe->attrib.mdata = 1;
			अन्यथा
				pxmitframe->attrib.mdata = 0;

			pxmitframe->attrib.triggered = 1;
			rtw_hal_xmitframe_enqueue(padapter, pxmitframe);
		पूर्ण

		अगर (psta_bmc->sleepq_len == 0) अणु
			अगर (pstapriv->tim_biपंचांगap & BIT(0))
				update_mask |= BIT(1);

			pstapriv->tim_biपंचांगap &= ~BIT(0);
			pstapriv->sta_dz_biपंचांगap &= ~BIT(0);
		पूर्ण
	पूर्ण

_निकास:

	spin_unlock_bh(&pxmitpriv->lock);

	अगर (update_mask)
		update_beacon(padapter, WLAN_EID_TIM, शून्य, true);
पूर्ण

व्योम xmit_delivery_enabled_frames(काष्ठा adapter *padapter, काष्ठा sta_info *psta)
अणु
	u8 wmmps_ac = 0;
	काष्ठा list_head	*xmitframe_plist, *xmitframe_phead;
	काष्ठा xmit_frame *pxmitframe = शून्य;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	spin_lock_bh(&pxmitpriv->lock);

	xmitframe_phead = get_list_head(&psta->sleep_q);
	xmitframe_plist = get_next(xmitframe_phead);

	जबतक (xmitframe_phead != xmitframe_plist) अणु
		pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

		xmitframe_plist = get_next(xmitframe_plist);

		चयन (pxmitframe->attrib.priority) अणु
		हाल 1:
		हाल 2:
			wmmps_ac = psta->uapsd_bk&BIT(1);
			अवरोध;
		हाल 4:
		हाल 5:
			wmmps_ac = psta->uapsd_vi&BIT(1);
			अवरोध;
		हाल 6:
		हाल 7:
			wmmps_ac = psta->uapsd_vo&BIT(1);
			अवरोध;
		हाल 0:
		हाल 3:
		शेष:
			wmmps_ac = psta->uapsd_be&BIT(1);
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
		rtw_hal_xmitframe_enqueue(padapter, pxmitframe);

		अगर ((psta->sleepq_ac_len == 0) && (!psta->has_legacy_ac) && (wmmps_ac)) अणु
			pstapriv->tim_biपंचांगap &= ~BIT(psta->aid);

			update_beacon(padapter, WLAN_EID_TIM, शून्य, true);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&pxmitpriv->lock);
पूर्ण

व्योम enqueue_pending_xmitbuf(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf)
अणु
	काष्ठा __queue *pqueue;
	काष्ठा adapter *pri_adapter = pxmitpriv->adapter;

	pqueue = &pxmitpriv->pending_xmitbuf_queue;

	spin_lock_bh(&pqueue->lock);
	list_del_init(&pxmitbuf->list);
	list_add_tail(&pxmitbuf->list, get_list_head(pqueue));
	spin_unlock_bh(&pqueue->lock);

	complete(&pri_adapter->xmitpriv.xmit_comp);
पूर्ण

व्योम enqueue_pending_xmitbuf_to_head(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf)
अणु
	काष्ठा __queue *pqueue;

	pqueue = &pxmitpriv->pending_xmitbuf_queue;

	spin_lock_bh(&pqueue->lock);
	list_del_init(&pxmitbuf->list);
	list_add(&pxmitbuf->list, get_list_head(pqueue));
	spin_unlock_bh(&pqueue->lock);
पूर्ण

काष्ठा xmit_buf *dequeue_pending_xmitbuf(काष्ठा xmit_priv *pxmitpriv)
अणु
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा __queue *pqueue;

	pxmitbuf = शून्य;
	pqueue = &pxmitpriv->pending_xmitbuf_queue;

	spin_lock_bh(&pqueue->lock);

	अगर (!list_empty(&pqueue->queue)) अणु
		काष्ठा list_head *plist, *phead;

		phead = get_list_head(pqueue);
		plist = get_next(phead);
		pxmitbuf = container_of(plist, काष्ठा xmit_buf, list);
		list_del_init(&pxmitbuf->list);
	पूर्ण

	spin_unlock_bh(&pqueue->lock);

	वापस pxmitbuf;
पूर्ण

काष्ठा xmit_buf *dequeue_pending_xmitbuf_under_survey(काष्ठा xmit_priv *pxmitpriv)
अणु
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा __queue *pqueue;

	pxmitbuf = शून्य;
	pqueue = &pxmitpriv->pending_xmitbuf_queue;

	spin_lock_bh(&pqueue->lock);

	अगर (!list_empty(&pqueue->queue)) अणु
		काष्ठा list_head *plist, *phead;
		u8 type;

		phead = get_list_head(pqueue);
		plist = phead;
		करो अणु
			plist = get_next(plist);
			अगर (plist == phead)
				अवरोध;

			pxmitbuf = container_of(plist, काष्ठा xmit_buf, list);

			type = GetFrameSubType(pxmitbuf->pbuf + TXDESC_OFFSET);

			अगर ((type == WIFI_PROBEREQ) ||
				(type == WIFI_DATA_शून्य) ||
				(type == WIFI_QOS_DATA_शून्य)) अणु
				list_del_init(&pxmitbuf->list);
				अवरोध;
			पूर्ण
			pxmitbuf = शून्य;
		पूर्ण जबतक (1);
	पूर्ण

	spin_unlock_bh(&pqueue->lock);

	वापस pxmitbuf;
पूर्ण

चिन्हित पूर्णांक check_pending_xmitbuf(काष्ठा xmit_priv *pxmitpriv)
अणु
	काष्ठा __queue *pqueue;
	चिन्हित पूर्णांक	ret = false;

	pqueue = &pxmitpriv->pending_xmitbuf_queue;

	spin_lock_bh(&pqueue->lock);

	अगर (!list_empty(&pqueue->queue))
		ret = true;

	spin_unlock_bh(&pqueue->lock);

	वापस ret;
पूर्ण

पूर्णांक rtw_xmit_thपढ़ो(व्योम *context)
अणु
	s32 err;
	काष्ठा adapter *padapter;

	err = _SUCCESS;
	padapter = context;

	thपढ़ो_enter("RTW_XMIT_THREAD");

	करो अणु
		err = rtw_hal_xmit_thपढ़ो_handler(padapter);
		flush_संकेतs_thपढ़ो();
	पूर्ण जबतक (err == _SUCCESS);

	complete(&padapter->xmitpriv.terminate_xmitthपढ़ो_comp);

	thपढ़ो_निकास();
पूर्ण

व्योम rtw_sctx_init(काष्ठा submit_ctx *sctx, पूर्णांक समयout_ms)
अणु
	sctx->समयout_ms = समयout_ms;
	sctx->submit_समय = jअगरfies;
	init_completion(&sctx->करोne);
	sctx->status = RTW_SCTX_SUBMITTED;
पूर्ण

पूर्णांक rtw_sctx_रुको(काष्ठा submit_ctx *sctx, स्थिर अक्षर *msg)
अणु
	पूर्णांक ret = _FAIL;
	अचिन्हित दीर्घ expire;
	पूर्णांक status = 0;

	expire = sctx->समयout_ms ? msecs_to_jअगरfies(sctx->समयout_ms) : MAX_SCHEDULE_TIMEOUT;
	अगर (!रुको_क्रम_completion_समयout(&sctx->करोne, expire))
		/* समयout, करो something?? */
		status = RTW_SCTX_DONE_TIMEOUT;
	अन्यथा
		status = sctx->status;

	अगर (status == RTW_SCTX_DONE_SUCCESS)
		ret = _SUCCESS;

	वापस ret;
पूर्ण

व्योम rtw_sctx_करोne_err(काष्ठा submit_ctx **sctx, पूर्णांक status)
अणु
	अगर (*sctx) अणु
		(*sctx)->status = status;
		complete(&((*sctx)->करोne));
		*sctx = शून्य;
	पूर्ण
पूर्ण

व्योम rtw_sctx_करोne(काष्ठा submit_ctx **sctx)
अणु
	rtw_sctx_करोne_err(sctx, RTW_SCTX_DONE_SUCCESS);
पूर्ण

पूर्णांक rtw_ack_tx_रुको(काष्ठा xmit_priv *pxmitpriv, u32 समयout_ms)
अणु
	काष्ठा submit_ctx *pack_tx_ops = &pxmitpriv->ack_tx_ops;

	pack_tx_ops->submit_समय = jअगरfies;
	pack_tx_ops->समयout_ms = समयout_ms;
	pack_tx_ops->status = RTW_SCTX_SUBMITTED;

	वापस rtw_sctx_रुको(pack_tx_ops, __func__);
पूर्ण

व्योम rtw_ack_tx_करोne(काष्ठा xmit_priv *pxmitpriv, पूर्णांक status)
अणु
	काष्ठा submit_ctx *pack_tx_ops = &pxmitpriv->ack_tx_ops;

	अगर (pxmitpriv->ack_tx)
		rtw_sctx_करोne_err(&pack_tx_ops, status);
पूर्ण
