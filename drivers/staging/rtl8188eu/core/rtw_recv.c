<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_RECV_C_

#समावेश <linux/ieee80211.h>

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <recv_osdep.h>
#समावेश <mlme_osdep.h>
#समावेश <mon.h>
#समावेश <wअगरi.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/cfg80211.h>

#घोषणा ETHERNET_HEADER_SIZE	14	/*  Ethernet Header Length */
#घोषणा LLC_HEADER_SIZE			6	/*  LLC Header Length */

अटल u8 SNAP_ETH_TYPE_IPX[2] = अणु0x81, 0x37पूर्ण;
अटल u8 SNAP_ETH_TYPE_APPLETALK_AARP[2] = अणु0x80, 0xf3पूर्ण;

अटल व्योम rtw_संकेत_stat_समयr_hdl(काष्ठा समयr_list *t);

व्योम _rtw_init_sta_recv_priv(काष्ठा sta_recv_priv *psta_recvpriv)
अणु
	स_रखो((u8 *)psta_recvpriv, 0, माप(काष्ठा sta_recv_priv));

	spin_lock_init(&psta_recvpriv->lock);

	_rtw_init_queue(&psta_recvpriv->defrag_q);
पूर्ण

पूर्णांक _rtw_init_recv_priv(काष्ठा recv_priv *precvpriv, काष्ठा adapter *padapter)
अणु
	पूर्णांक i;

	काष्ठा recv_frame *precvframe;

	पूर्णांक	res = _SUCCESS;

	_rtw_init_queue(&precvpriv->मुक्त_recv_queue);
	_rtw_init_queue(&precvpriv->recv_pending_queue);
	_rtw_init_queue(&precvpriv->uc_swdec_pending_queue);

	precvpriv->adapter = padapter;

	precvpriv->pallocated_frame_buf = vzalloc(NR_RECVFRAME * माप(काष्ठा recv_frame) + RXFRAME_ALIGN_SZ);

	अगर (!precvpriv->pallocated_frame_buf)
		वापस _FAIL;

	precvframe = PTR_ALIGN(precvpriv->pallocated_frame_buf, RXFRAME_ALIGN_SZ);

	क्रम (i = 0; i < NR_RECVFRAME; i++) अणु
		INIT_LIST_HEAD(&precvframe->list);

		list_add_tail(&precvframe->list,
			      &precvpriv->मुक्त_recv_queue.queue);

		precvframe->pkt = शून्य;

		precvframe->adapter = padapter;
		precvframe++;
	पूर्ण
	res = rtw_hal_init_recv_priv(padapter);

	समयr_setup(&precvpriv->संकेत_stat_समयr, rtw_संकेत_stat_समयr_hdl,
		    0);

	precvpriv->संकेत_stat_sampling_पूर्णांकerval = 1000; /* ms */

	rtw_set_संकेत_stat_समयr(precvpriv);

	वापस res;
पूर्ण

व्योम _rtw_मुक्त_recv_priv(काष्ठा recv_priv *precvpriv)
अणु
	काष्ठा adapter	*padapter = precvpriv->adapter;

	rtw_मुक्त_uc_swdec_pending_queue(padapter);

	vमुक्त(precvpriv->pallocated_frame_buf);

	rtw_hal_मुक्त_recv_priv(padapter);
पूर्ण

काष्ठा recv_frame *_rtw_alloc_recvframe(काष्ठा __queue *pमुक्त_recv_queue)
अणु
	काष्ठा recv_frame *hdr;

	hdr = list_first_entry_or_null(&pमुक्त_recv_queue->queue,
				       काष्ठा recv_frame, list);
	अगर (hdr)
		list_del_init(&hdr->list);

	वापस hdr;
पूर्ण

काष्ठा recv_frame *rtw_alloc_recvframe(काष्ठा __queue *pमुक्त_recv_queue)
अणु
	काष्ठा recv_frame  *precvframe;

	spin_lock_bh(&pमुक्त_recv_queue->lock);

	precvframe = _rtw_alloc_recvframe(pमुक्त_recv_queue);

	spin_unlock_bh(&pमुक्त_recv_queue->lock);

	वापस precvframe;
पूर्ण

पूर्णांक rtw_मुक्त_recvframe(काष्ठा recv_frame *precvframe,
		       काष्ठा __queue *pमुक्त_recv_queue)
अणु
	अगर (!precvframe)
		वापस _FAIL;
	अगर (precvframe->pkt) अणु
		dev_kमुक्त_skb_any(precvframe->pkt);/* मुक्त skb by driver */
		precvframe->pkt = शून्य;
	पूर्ण

	spin_lock_bh(&pमुक्त_recv_queue->lock);

	list_del_init(&precvframe->list);

	list_add_tail(&precvframe->list, get_list_head(pमुक्त_recv_queue));

	spin_unlock_bh(&pमुक्त_recv_queue->lock);

	वापस _SUCCESS;
पूर्ण

पूर्णांक _rtw_enqueue_recvframe(काष्ठा recv_frame *precvframe, काष्ठा __queue *queue)
अणु
	list_del_init(&precvframe->list);
	list_add_tail(&precvframe->list, get_list_head(queue));

	वापस _SUCCESS;
पूर्ण

पूर्णांक rtw_enqueue_recvframe(काष्ठा recv_frame *precvframe, काष्ठा __queue *queue)
अणु
	पूर्णांक ret;

	spin_lock_bh(&queue->lock);
	ret = _rtw_enqueue_recvframe(precvframe, queue);
	spin_unlock_bh(&queue->lock);

	वापस ret;
पूर्ण

/*
 * caller : defrag ; recvframe_chk_defrag in recv_thपढ़ो  (passive)
 * pframequeue: defrag_queue : will be accessed in recv_thपढ़ो  (passive)
 *
 * using spinlock to protect
 *
 */

व्योम rtw_मुक्त_recvframe_queue(काष्ठा __queue *pframequeue,  काष्ठा __queue *pमुक्त_recv_queue)
अणु
	काष्ठा recv_frame *hdr;
	काष्ठा list_head *plist, *phead;

	spin_lock(&pframequeue->lock);

	phead = get_list_head(pframequeue);
	plist = phead->next;

	जबतक (phead != plist) अणु
		hdr = list_entry(plist, काष्ठा recv_frame, list);

		plist = plist->next;

		rtw_मुक्त_recvframe(hdr, pमुक्त_recv_queue);
	पूर्ण

	spin_unlock(&pframequeue->lock);
पूर्ण

u32 rtw_मुक्त_uc_swdec_pending_queue(काष्ठा adapter *adapter)
अणु
	u32 cnt = 0;
	काष्ठा recv_frame *pending_frame;

	जबतक ((pending_frame = rtw_alloc_recvframe(&adapter->recvpriv.uc_swdec_pending_queue))) अणु
		rtw_मुक्त_recvframe(pending_frame, &adapter->recvpriv.मुक्त_recv_queue);
		DBG_88E("%s: dequeue uc_swdec_pending_queue\n", __func__);
		cnt++;
	पूर्ण

	वापस cnt;
पूर्ण

अटल पूर्णांक recvframe_chkmic(काष्ठा adapter *adapter,
			    काष्ठा recv_frame *precvframe)
अणु
	पूर्णांक	i, res = _SUCCESS;
	u32	datalen;
	u8	miccode[8];
	u8	bmic_err = false, brpt_micerror = true;
	u8	*pframe, *payload, *pframemic;
	u8	*mickey;
	काष्ठा	sta_info		*stainfo;
	काष्ठा	rx_pkt_attrib	*prxattrib = &precvframe->attrib;
	काष्ठा	security_priv	*psecuritypriv = &adapter->securitypriv;

	काष्ठा mlme_ext_priv	*pmlmeext = &adapter->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;

	stainfo = rtw_get_stainfo(&adapter->stapriv, &prxattrib->ta[0]);

	अगर (prxattrib->encrypt == _TKIP_) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
			 ("\n %s: prxattrib->encrypt==_TKIP_\n", __func__));
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
			 ("\n %s: da=0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\n",
			  __func__, prxattrib->ra[0], prxattrib->ra[1], prxattrib->ra[2],
			  prxattrib->ra[3], prxattrib->ra[4], prxattrib->ra[5]));

		/* calculate mic code */
		अगर (stainfo) अणु
			अगर (is_multicast_ether_addr(prxattrib->ra)) अणु
				अगर (!psecuritypriv) अणु
					res = _FAIL;
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
						 ("\n %s: didn't install group key!!!!!!!!!!\n", __func__));
					DBG_88E("\n %s: didn't install group key!!!!!!!!!!\n", __func__);
					जाओ निकास;
				पूर्ण
				mickey = &psecuritypriv->करोt118021XGrprxmickey[prxattrib->key_index].skey[0];

				RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
					 ("\n %s: bcmc key\n", __func__));
			पूर्ण अन्यथा अणु
				mickey = &stainfo->करोt11tkiprxmickey.skey[0];
				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
					 ("\n %s: unicast key\n", __func__));
			पूर्ण

			/* icv_len included the mic code */
			datalen = precvframe->pkt->len - prxattrib->hdrlen -
				  prxattrib->iv_len - prxattrib->icv_len - 8;
			pframe = precvframe->pkt->data;
			payload = pframe + prxattrib->hdrlen + prxattrib->iv_len;

			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\n prxattrib->iv_len=%d prxattrib->icv_len=%d\n", prxattrib->iv_len, prxattrib->icv_len));
			rtw_seccalctkipmic(mickey, pframe, payload, datalen, &miccode[0],
					   (अचिन्हित अक्षर)prxattrib->priority); /* care the length of the data */

			pframemic = payload + datalen;

			bmic_err = false;

			क्रम (i = 0; i < 8; i++) अणु
				अगर (miccode[i] != *(pframemic + i)) अणु
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
						 ("%s: miccode[%d](%02x)!=*(pframemic+%d)(%02x) ",
						  __func__, i, miccode[i], i, *(pframemic + i)));
					bmic_err = true;
				पूर्ण
			पूर्ण

			अगर (bmic_err) अणु
				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
					 ("\n *(pframemic-8)-*(pframemic-1)=0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\n",
					 *(pframemic - 8), *(pframemic - 7), *(pframemic - 6),
					 *(pframemic - 5), *(pframemic - 4), *(pframemic - 3),
					 *(pframemic - 2), *(pframemic - 1)));
				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
					 ("\n *(pframemic-16)-*(pframemic-9)=0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x\n",
					 *(pframemic - 16), *(pframemic - 15), *(pframemic - 14),
					 *(pframemic - 13), *(pframemic - 12), *(pframemic - 11),
					 *(pframemic - 10), *(pframemic - 9)));
				अणु
					uपूर्णांक i;

					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
						 ("\n ======demp packet (len=%d)======\n",
						 precvframe->pkt->len));
					क्रम (i = 0; i < precvframe->pkt->len; i += 8) अणु
						RT_TRACE(_module_rtl871x_recv_c_,
							 _drv_err_,
							 ("0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x:0x%02x",
							 *(precvframe->pkt->data + i),
							 *(precvframe->pkt->data + i + 1),
							 *(precvframe->pkt->data + i + 2),
							 *(precvframe->pkt->data + i + 3),
							 *(precvframe->pkt->data + i + 4),
							 *(precvframe->pkt->data + i + 5),
							 *(precvframe->pkt->data + i + 6),
							 *(precvframe->pkt->data + i + 7)));
					पूर्ण
					RT_TRACE(_module_rtl871x_recv_c_,
						 _drv_err_,
						 ("\n ====== demp packet end [len=%d]======\n",
						 precvframe->pkt->len));
					RT_TRACE(_module_rtl871x_recv_c_,
						 _drv_err_,
						 ("\n hrdlen=%d,\n",
						 prxattrib->hdrlen));
				पूर्ण

				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
					 ("ra=0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x psecuritypriv->binstallGrpkey=%d ",
					 prxattrib->ra[0], prxattrib->ra[1], prxattrib->ra[2],
					 prxattrib->ra[3], prxattrib->ra[4], prxattrib->ra[5], psecuritypriv->binstallGrpkey));

				/*  द्विगुन check key_index क्रम some timing issue , */
				/*  cannot compare with psecuritypriv->करोt118021XGrpKeyid also cause timing issue */
				अगर (is_multicast_ether_addr(prxattrib->ra) && prxattrib->key_index != pmlmeinfo->key_index)
					brpt_micerror = false;

				अगर ((prxattrib->bdecrypted) && (brpt_micerror)) अणु
					rtw_handle_tkip_mic_err(adapter, (u8)is_multicast_ether_addr(prxattrib->ra));
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" mic error :prxattrib->bdecrypted=%d ", prxattrib->bdecrypted));
					DBG_88E(" mic error :prxattrib->bdecrypted=%d\n", prxattrib->bdecrypted);
				पूर्ण अन्यथा अणु
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" mic error :prxattrib->bdecrypted=%d ", prxattrib->bdecrypted));
					DBG_88E(" mic error :prxattrib->bdecrypted=%d\n", prxattrib->bdecrypted);
				पूर्ण
				res = _FAIL;
			पूर्ण अन्यथा अणु
				/* mic checked ok */
				अगर (!psecuritypriv->bcheck_grpkey && is_multicast_ether_addr(prxattrib->ra)) अणु
					psecuritypriv->bcheck_grpkey = true;
					RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("psecuritypriv->bcheck_grpkey = true"));
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
				 ("%s: rtw_get_stainfo==NULL!!!\n", __func__));
		पूर्ण

		skb_trim(precvframe->pkt, precvframe->pkt->len - 8);
	पूर्ण

निकास:

	वापस res;
पूर्ण

/* decrypt and set the ivlen, icvlen of the recv_frame */
अटल काष्ठा recv_frame *decryptor(काष्ठा adapter *padapter,
				    काष्ठा recv_frame *precv_frame)
अणु
	काष्ठा rx_pkt_attrib *prxattrib = &precv_frame->attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा recv_frame *वापस_packet = precv_frame;
	u32	 res = _SUCCESS;

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("prxstat->decrypted=%x prxattrib->encrypt=0x%03x\n", prxattrib->bdecrypted, prxattrib->encrypt));

	अगर (prxattrib->encrypt > 0) अणु
		u8 *iv = precv_frame->pkt->data + prxattrib->hdrlen;

		prxattrib->key_index = (((iv[3]) >> 6) & 0x3);

		अगर (prxattrib->key_index > WEP_KEYS) अणु
			DBG_88E("prxattrib->key_index(%d)>WEP_KEYS\n", prxattrib->key_index);

			चयन (prxattrib->encrypt) अणु
			हाल _WEP40_:
			हाल _WEP104_:
				prxattrib->key_index = psecuritypriv->करोt11PrivacyKeyIndex;
				अवरोध;
			हाल _TKIP_:
			हाल _AES_:
			शेष:
				prxattrib->key_index = psecuritypriv->करोt118021XGrpKeyid;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((prxattrib->encrypt > 0) && (prxattrib->bdecrypted == 0)) अणु
		psecuritypriv->hw_decrypted = false;

		चयन (prxattrib->encrypt) अणु
		हाल _WEP40_:
		हाल _WEP104_:
			res = rtw_wep_decrypt(padapter, precv_frame);
			अवरोध;
		हाल _TKIP_:
			res = rtw_tkip_decrypt(padapter, precv_frame);
			अवरोध;
		हाल _AES_:
			res = rtw_aes_decrypt(padapter, precv_frame);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (prxattrib->bdecrypted == 1 && prxattrib->encrypt > 0 &&
		   (psecuritypriv->busetkipkey == 1 || prxattrib->encrypt != _TKIP_))
			psecuritypriv->hw_decrypted = true;

	अगर (res == _FAIL) अणु
		rtw_मुक्त_recvframe(वापस_packet, &padapter->recvpriv.मुक्त_recv_queue);
		वापस_packet = शून्य;
	पूर्ण

	वापस वापस_packet;
पूर्ण

/* set the security inक्रमmation in the recv_frame */
अटल काष्ठा recv_frame *portctrl(काष्ठा adapter *adapter,
				   काष्ठा recv_frame *precv_frame)
अणु
	u8   *psta_addr, *ptr;
	uपूर्णांक  auth_alg;
	काष्ठा recv_frame *pfhdr;
	काष्ठा sta_info *psta;
	काष्ठा sta_priv *pstapriv;
	काष्ठा recv_frame *prtnframe;
	u16	ether_type;
	u16  eapol_type = 0x888e;/* क्रम Funia BD's WPA issue */
	काष्ठा rx_pkt_attrib *pattrib;
	__be16 be_पंचांगp;

	pstapriv = &adapter->stapriv;

	auth_alg = adapter->securitypriv.करोt11AuthAlgrthm;

	ptr = precv_frame->pkt->data;
	pfhdr = precv_frame;
	pattrib = &pfhdr->attrib;
	psta_addr = pattrib->ta;
	psta = rtw_get_stainfo(pstapriv, psta_addr);

	prtnframe = शून्य;

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("########%s:adapter->securitypriv.dot11AuthAlgrthm=%d\n", __func__, adapter->securitypriv.करोt11AuthAlgrthm));

	अगर (auth_alg == 2) अणु
		/* get ether_type */
		ptr = ptr + pfhdr->attrib.hdrlen + LLC_HEADER_SIZE + pfhdr->attrib.iv_len;
		स_नकल(&be_पंचांगp, ptr, 2);
		ether_type = ntohs(be_पंचांगp);

		अगर (psta && (psta->ieee8021x_blocked)) अणु
			/* blocked */
			/* only accept EAPOL frame */
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("########%s:psta->ieee8021x_blocked==1\n", __func__));

			अगर (ether_type == eapol_type) अणु
				prtnframe = precv_frame;
			पूर्ण अन्यथा अणु
				/* मुक्त this frame */
				rtw_मुक्त_recvframe(precv_frame, &adapter->recvpriv.मुक्त_recv_queue);
				prtnframe = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* allowed */
			/* check decryption status, and decrypt the frame अगर needed */
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("########%s:psta->ieee8021x_blocked==0\n", __func__));
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
				 ("%s:precv_frame->hdr.attrib.privacy=%x\n",
				  __func__, precv_frame->attrib.privacy));

			अगर (pattrib->bdecrypted == 0)
				RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("%s:prxstat->decrypted=%x\n", __func__, pattrib->bdecrypted));

			prtnframe = precv_frame;
			/* check is the EAPOL frame or not (Rekey) */
			अगर (ether_type == eapol_type) अणु
				RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("########%s:ether_type==0x888e\n", __func__));
				/* check Rekey */

				prtnframe = precv_frame;
			पूर्ण अन्यथा अणु
				RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("########%s:ether_type=0x%04x\n", __func__, ether_type));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		prtnframe = precv_frame;
	पूर्ण

	वापस prtnframe;
पूर्ण

अटल पूर्णांक recv_decache(काष्ठा recv_frame *precv_frame, u8 bretry,
			काष्ठा stainfo_rxcache *prxcache)
अणु
	पूर्णांक tid = precv_frame->attrib.priority;

	u16 seq_ctrl = ((precv_frame->attrib.seq_num & 0xffff) << 4) |
		(precv_frame->attrib.frag_num & 0xf);

	अगर (tid > 15) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("%s, (tid>15)! seq_ctrl=0x%x, tid=0x%x\n", __func__, seq_ctrl, tid));

		वापस _FAIL;
	पूर्ण

	अगर (1) अणु/* अगर (bretry) */
		अगर (seq_ctrl == prxcache->tid_rxseq[tid]) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("%s, seq_ctrl=0x%x, tid=0x%x, tid_rxseq=0x%x\n", __func__, seq_ctrl, tid, prxcache->tid_rxseq[tid]));

			वापस _FAIL;
		पूर्ण
	पूर्ण

	prxcache->tid_rxseq[tid] = seq_ctrl;

	वापस _SUCCESS;
पूर्ण

अटल व्योम process_pwrbit_data(काष्ठा adapter *padapter,
				काष्ठा recv_frame *precv_frame)
अणु
#अगर_घोषित CONFIG_88EU_AP_MODE
	अचिन्हित अक्षर pwrbit;
	u8 *ptr = precv_frame->pkt->data;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->attrib;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *psta = शून्य;

	psta = rtw_get_stainfo(pstapriv, pattrib->src);

	pwrbit = GetPwrMgt(ptr);

	अगर (psta) अणु
		अगर (pwrbit) अणु
			अगर (!(psta->state & WIFI_SLEEP_STATE))
				stop_sta_xmit(padapter, psta);
		पूर्ण अन्यथा अणु
			अगर (psta->state & WIFI_SLEEP_STATE)
				wakeup_sta_to_xmit(padapter, psta);
		पूर्ण
	पूर्ण

#पूर्ण_अगर
पूर्ण

अटल व्योम process_wmmps_data(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *precv_frame)
अणु
#अगर_घोषित CONFIG_88EU_AP_MODE
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->attrib;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *psta = शून्य;

	psta = rtw_get_stainfo(pstapriv, pattrib->src);

	अगर (!psta)
		वापस;

	अगर (!psta->qos_option)
		वापस;

	अगर (!(psta->qos_info & 0xf))
		वापस;

	अगर (psta->state & WIFI_SLEEP_STATE) अणु
		u8 wmmps_ac = 0;

		चयन (pattrib->priority) अणु
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

		अगर (wmmps_ac) अणु
			अगर (psta->sleepq_ac_len > 0) अणु
				/* process received triggered frame */
				xmit_delivery_enabled_frames(padapter, psta);
			पूर्ण अन्यथा अणु
				/* issue one qos null frame with More data bit = 0 and the EOSP bit set (= 1) */
				issue_qos_nulldata(padapter, psta->hwaddr, (u16)pattrib->priority, 0, 0);
			पूर्ण
		पूर्ण
	पूर्ण

#पूर्ण_अगर
पूर्ण

अटल व्योम count_rx_stats(काष्ठा adapter *padapter,
			   काष्ठा recv_frame *prframe,
			   काष्ठा sta_info *sta)
अणु
	पूर्णांक	sz;
	काष्ठा sta_info		*psta = शून्य;
	काष्ठा stainfo_stats	*pstats = शून्य;
	काष्ठा rx_pkt_attrib	*pattrib = &prframe->attrib;
	काष्ठा recv_priv	*precvpriv = &padapter->recvpriv;

	sz = prframe->pkt->len;
	precvpriv->rx_bytes += sz;

	padapter->mlmepriv.LinkDetectInfo.NumRxOkInPeriod++;

	अगर (!is_multicast_ether_addr(pattrib->dst))
		padapter->mlmepriv.LinkDetectInfo.NumRxUnicastOkInPeriod++;

	अगर (sta)
		psta = sta;
	अन्यथा
		psta = prframe->psta;

	अगर (psta) अणु
		pstats = &psta->sta_stats;

		pstats->rx_data_pkts++;
		pstats->rx_bytes += sz;
	पूर्ण
पूर्ण

अटल पूर्णांक sta2sta_data_frame(काष्ठा adapter *adapter,
			      काष्ठा recv_frame *precv_frame,
			      काष्ठा sta_info **psta)
अणु
	पूर्णांक ret = _SUCCESS;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->attrib;
	काष्ठा	sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *mybssid  = get_bssid(pmlmepriv);
	u8 *myhwaddr = myid(&adapter->eeprompriv);
	u8 *sta_addr = शून्य;
	bool mcast = is_multicast_ether_addr(pattrib->dst);

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
		/*  filter packets that SA is myself or multicast or broadcast */
		अगर (!स_भेद(myhwaddr, pattrib->src, ETH_ALEN)) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" SA==myself\n"));
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		अगर (स_भेद(myhwaddr, pattrib->dst, ETH_ALEN) && !mcast) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		अगर (!स_भेद(pattrib->bssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		    !स_भेद(mybssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		    स_भेद(pattrib->bssid, mybssid, ETH_ALEN)) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		sta_addr = pattrib->src;
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
		/*  For Station mode, sa and bssid should always be BSSID, and DA is my mac-address */
		अगर (स_भेद(pattrib->bssid, pattrib->src, ETH_ALEN)) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("bssid!=TA under STATION_MODE; drop pkt\n"));
			ret = _FAIL;
			जाओ निकास;
		पूर्ण
		sta_addr = pattrib->bssid;
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		अगर (mcast) अणु
			/*  For AP mode, अगर DA == MCAST, then BSSID should be also MCAST */
			अगर (!is_multicast_ether_addr(pattrib->bssid)) अणु
				ret = _FAIL;
				जाओ निकास;
			पूर्ण
		पूर्ण अन्यथा अणु /*  not mc-frame */
			/*  For AP mode, अगर DA is non-MCAST, then it must be BSSID, and bssid == BSSID */
			अगर (स_भेद(pattrib->bssid, pattrib->dst, ETH_ALEN)) अणु
				ret = _FAIL;
				जाओ निकास;
			पूर्ण

			sta_addr = pattrib->src;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret  = _FAIL;
	पूर्ण

	अगर (mcast)
		*psta = rtw_get_bcmc_stainfo(adapter);
	अन्यथा
		*psta = rtw_get_stainfo(pstapriv, sta_addr); /*  get ap_info */

	अगर (!*psta) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("can't get psta under %s ; drop pkt\n", __func__));
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक ap2sta_data_frame(काष्ठा adapter *adapter,
			     काष्ठा recv_frame *precv_frame,
			     काष्ठा sta_info **psta)
अणु
	u8 *ptr = precv_frame->pkt->data;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->attrib;
	पूर्णांक ret = _SUCCESS;
	काष्ठा	sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *mybssid  = get_bssid(pmlmepriv);
	u8 *myhwaddr = myid(&adapter->eeprompriv);
	bool mcast = is_multicast_ether_addr(pattrib->dst);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) &&
	    (check_fwstate(pmlmepriv, _FW_LINKED) ||
	     check_fwstate(pmlmepriv, _FW_UNDER_LINKING))) अणु
		/*  filter packets that SA is myself or multicast or broadcast */
		अगर (!स_भेद(myhwaddr, pattrib->src, ETH_ALEN)) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" SA==myself\n"));
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		/*  da should be क्रम me */
		अगर (स_भेद(myhwaddr, pattrib->dst, ETH_ALEN) && !mcast) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
				 (" %s:  compare DA fail; DA=%pM\n", __func__, (pattrib->dst)));
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		/*  check BSSID */
		अगर (!स_भेद(pattrib->bssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		    !स_भेद(mybssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		     (स_भेद(pattrib->bssid, mybssid, ETH_ALEN))) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
				 (" %s:  compare BSSID fail ; BSSID=%pM\n", __func__, (pattrib->bssid)));
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("mybssid=%pM\n", (mybssid)));

			अगर (!mcast) अणु
				DBG_88E("issue_deauth to the nonassociated ap=%pM for the reason(7)\n", (pattrib->bssid));
				issue_deauth(adapter, pattrib->bssid, WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);
			पूर्ण

			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		अगर (mcast)
			*psta = rtw_get_bcmc_stainfo(adapter);
		अन्यथा
			*psta = rtw_get_stainfo(pstapriv, pattrib->bssid); /*  get ap_info */

		अगर (!*psta) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("ap2sta: can't get psta under STATION_MODE ; drop pkt\n"));
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		/* अगर ((GetFrameSubType(ptr) & WIFI_QOS_DATA_TYPE) == WIFI_QOS_DATA_TYPE) अणु */
		/*  */

		अगर (GetFrameSubType(ptr) & BIT(6)) अणु
			/* No data, will not indicate to upper layer, temporily count it here */
			count_rx_stats(adapter, precv_frame, *psta);
			ret = RTW_RX_HANDLED;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		/* Special हाल */
		ret = RTW_RX_HANDLED;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		अगर (!स_भेद(myhwaddr, pattrib->dst, ETH_ALEN) && !mcast) अणु
			*psta = rtw_get_stainfo(pstapriv, pattrib->bssid); /*  get sta_info */
			अगर (!*psta) अणु
				DBG_88E("issue_deauth to the ap =%pM for the reason(7)\n", (pattrib->bssid));

				issue_deauth(adapter, pattrib->bssid, WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);
			पूर्ण
		पूर्ण

		ret = _FAIL;
	पूर्ण

निकास:

	वापस ret;
पूर्ण

अटल पूर्णांक sta2ap_data_frame(काष्ठा adapter *adapter,
			     काष्ठा recv_frame *precv_frame,
			     काष्ठा sta_info **psta)
अणु
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->attrib;
	काष्ठा	sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *ptr = precv_frame->pkt->data;
	अचिन्हित अक्षर *mybssid  = get_bssid(pmlmepriv);
	पूर्णांक ret = _SUCCESS;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		/* For AP mode, RA = BSSID, TX = STA(SRC_ADDR), A3 = DST_ADDR */
		अगर (स_भेद(pattrib->bssid, mybssid, ETH_ALEN)) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		*psta = rtw_get_stainfo(pstapriv, pattrib->src);
		अगर (!*psta) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("can't get psta under AP_MODE; drop pkt\n"));
			DBG_88E("issue_deauth to sta=%pM for the reason(7)\n", (pattrib->src));

			issue_deauth(adapter, pattrib->src, WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);

			ret = RTW_RX_HANDLED;
			जाओ निकास;
		पूर्ण

		process_pwrbit_data(adapter, precv_frame);

		अगर ((GetFrameSubType(ptr) & WIFI_QOS_DATA_TYPE) == WIFI_QOS_DATA_TYPE)
			process_wmmps_data(adapter, precv_frame);

		अगर (GetFrameSubType(ptr) & BIT(6)) अणु
			/* No data, will not indicate to upper layer, temporily count it here */
			count_rx_stats(adapter, precv_frame, *psta);
			ret = RTW_RX_HANDLED;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		u8 *myhwaddr = myid(&adapter->eeprompriv);

		अगर (स_भेद(pattrib->ra, myhwaddr, ETH_ALEN)) अणु
			ret = RTW_RX_HANDLED;
			जाओ निकास;
		पूर्ण
		DBG_88E("issue_deauth to sta=%pM for the reason(7)\n", (pattrib->src));
		issue_deauth(adapter, pattrib->src, WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);
		ret = RTW_RX_HANDLED;
		जाओ निकास;
	पूर्ण

निकास:

	वापस ret;
पूर्ण

अटल पूर्णांक validate_recv_ctrl_frame(काष्ठा adapter *padapter,
				    काष्ठा recv_frame *precv_frame)
अणु
#अगर_घोषित CONFIG_88EU_AP_MODE
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->attrib;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->pkt->data;

	अगर (GetFrameType(pframe) != WIFI_CTRL_TYPE)
		वापस _FAIL;

	/* receive the frames that ra(a1) is my address */
	अगर (स_भेद(GetAddr1Ptr(pframe), myid(&padapter->eeprompriv), ETH_ALEN))
		वापस _FAIL;

	/* only handle ps-poll */
	अगर (GetFrameSubType(pframe) == WIFI_PSPOLL) अणु
		u16 aid;
		u8 wmmps_ac = 0;
		काष्ठा sta_info *psta = शून्य;

		aid = GetAid(pframe);
		psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));

		अगर ((!psta) || (psta->aid != aid))
			वापस _FAIL;

		/* क्रम rx pkt statistics */
		psta->sta_stats.rx_ctrl_pkts++;

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
			वापस _FAIL;

		अगर (psta->state & WIFI_STA_ALIVE_CHK_STATE) अणु
			DBG_88E("%s alive check-rx ps-poll\n", __func__);
			psta->expire_to = pstapriv->expire_to;
			psta->state ^= WIFI_STA_ALIVE_CHK_STATE;
		पूर्ण

		अगर ((psta->state & WIFI_SLEEP_STATE) && (pstapriv->sta_dz_biपंचांगap & BIT(psta->aid))) अणु
			काष्ठा list_head *xmitframe_plist, *xmitframe_phead;
			काष्ठा xmit_frame *pxmitframe = शून्य;

			spin_lock_bh(&psta->sleep_q.lock);

			xmitframe_phead = get_list_head(&psta->sleep_q);
			xmitframe_plist = xmitframe_phead->next;

			अगर (xmitframe_phead != xmitframe_plist) अणु
				pxmitframe = list_entry(xmitframe_plist, काष्ठा xmit_frame, list);

				xmitframe_plist = xmitframe_plist->next;

				list_del_init(&pxmitframe->list);

				psta->sleepq_len--;

				अगर (psta->sleepq_len > 0)
					pxmitframe->attrib.mdata = 1;
				अन्यथा
					pxmitframe->attrib.mdata = 0;

				pxmitframe->attrib.triggered = 1;

				spin_unlock_bh(&psta->sleep_q.lock);
				अगर (rtw_hal_xmit(padapter, pxmitframe))
					rtw_os_xmit_complete(padapter, pxmitframe);
				spin_lock_bh(&psta->sleep_q.lock);

				अगर (psta->sleepq_len == 0) अणु
					pstapriv->tim_biपंचांगap &= ~BIT(psta->aid);

					/* update BCN क्रम TIM IE */
					/* update_BCNTIM(padapter); */
					update_beacon(padapter, WLAN_EID_TIM, शून्य, false);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (pstapriv->tim_biपंचांगap & BIT(psta->aid)) अणु
					अगर (psta->sleepq_len == 0) अणु
						DBG_88E("no buffered packets to xmit\n");

						/* issue nulldata with More data bit = 0 to indicate we have no buffered packets */
						issue_nulldata(padapter, psta->hwaddr, 0, 0, 0);
					पूर्ण अन्यथा अणु
						DBG_88E("error!psta->sleepq_len=%d\n", psta->sleepq_len);
						psta->sleepq_len = 0;
					पूर्ण

					pstapriv->tim_biपंचांगap &= ~BIT(psta->aid);

					/* update BCN क्रम TIM IE */
					/* update_BCNTIM(padapter); */
					update_beacon(padapter, WLAN_EID_TIM, शून्य, false);
				पूर्ण
			पूर्ण

			spin_unlock_bh(&psta->sleep_q.lock);
		पूर्ण
	पूर्ण

#पूर्ण_अगर

	वापस _FAIL;
पूर्ण

काष्ठा recv_frame *recvframe_chk_defrag(काष्ठा adapter *padapter,
					काष्ठा recv_frame *precv_frame);

अटल पूर्णांक validate_recv_mgnt_frame(काष्ठा adapter *padapter,
				    काष्ठा recv_frame *precv_frame)
अणु
	काष्ठा sta_info *psta;

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("+%s\n", __func__));

	precv_frame = recvframe_chk_defrag(padapter, precv_frame);
	अगर (!precv_frame) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_,
			 ("%s: fragment packet\n", __func__));
		वापस _SUCCESS;
	पूर्ण

	/* क्रम rx pkt statistics */
	psta = rtw_get_stainfo(&padapter->stapriv,
			       GetAddr2Ptr(precv_frame->pkt->data));
	अगर (psta) अणु
		psta->sta_stats.rx_mgnt_pkts++;
		अगर (GetFrameSubType(precv_frame->pkt->data) == WIFI_BEACON) अणु
			psta->sta_stats.rx_beacon_pkts++;
		पूर्ण अन्यथा अगर (GetFrameSubType(precv_frame->pkt->data) == WIFI_PROBEREQ) अणु
			psta->sta_stats.rx_probereq_pkts++;
		पूर्ण अन्यथा अगर (GetFrameSubType(precv_frame->pkt->data) == WIFI_PROBERSP) अणु
			अगर (!स_भेद(padapter->eeprompriv.mac_addr,
				    GetAddr1Ptr(precv_frame->pkt->data), ETH_ALEN))
				psta->sta_stats.rx_probersp_pkts++;
			अन्यथा अगर (is_multicast_ether_addr(GetAddr1Ptr(precv_frame->pkt->data)))
				psta->sta_stats.rx_probersp_bm_pkts++;
			अन्यथा
				psta->sta_stats.rx_probersp_uo_pkts++;
		पूर्ण
	पूर्ण

	mgt_dispatcher(padapter, precv_frame);

	वापस _SUCCESS;
पूर्ण

अटल पूर्णांक validate_recv_data_frame(काष्ठा adapter *adapter,
				    काष्ठा recv_frame *precv_frame)
अणु
	u8 bretry;
	u8 *psa, *pda, *pbssid;
	काष्ठा sta_info *psta = शून्य;
	u8 *ptr = precv_frame->pkt->data;
	काष्ठा rx_pkt_attrib	*pattrib = &precv_frame->attrib;
	काष्ठा security_priv	*psecuritypriv = &adapter->securitypriv;
	पूर्णांक ret = _SUCCESS;

	bretry = GetRetry(ptr);
	pda = ieee80211_get_DA((काष्ठा ieee80211_hdr *)ptr);
	psa = ieee80211_get_SA((काष्ठा ieee80211_hdr *)ptr);
	pbssid = get_hdr_bssid(ptr);

	अगर (!pbssid) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	स_नकल(pattrib->dst, pda, ETH_ALEN);
	स_नकल(pattrib->src, psa, ETH_ALEN);

	स_नकल(pattrib->bssid, pbssid, ETH_ALEN);

	चयन (pattrib->to_fr_ds) अणु
	हाल 0:
		स_नकल(pattrib->ra, pda, ETH_ALEN);
		स_नकल(pattrib->ta, psa, ETH_ALEN);
		ret = sta2sta_data_frame(adapter, precv_frame, &psta);
		अवरोध;
	हाल 1:
		स_नकल(pattrib->ra, pda, ETH_ALEN);
		स_नकल(pattrib->ta, pbssid, ETH_ALEN);
		ret = ap2sta_data_frame(adapter, precv_frame, &psta);
		अवरोध;
	हाल 2:
		स_नकल(pattrib->ra, pbssid, ETH_ALEN);
		स_नकल(pattrib->ta, psa, ETH_ALEN);
		ret = sta2ap_data_frame(adapter, precv_frame, &psta);
		अवरोध;
	हाल 3:
		स_नकल(pattrib->ra, GetAddr1Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->ta, GetAddr2Ptr(ptr), ETH_ALEN);
		ret = _FAIL;
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" case 3\n"));
		अवरोध;
	शेष:
		ret = _FAIL;
		अवरोध;
	पूर्ण

	अगर (ret == _FAIL)
		जाओ निकास;
	अन्यथा अगर (ret == RTW_RX_HANDLED)
		जाओ निकास;

	अगर (!psta) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, (" after to_fr_ds_chk; psta==NULL\n"));
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	/* psta->rssi = prxcmd->rssi; */
	/* psta->संकेत_quality = prxcmd->sq; */
	precv_frame->psta = psta;

	pattrib->amsdu = 0;
	pattrib->ack_policy = 0;
	/* parsing QC field */
	अगर (pattrib->qos == 1) अणु
		pattrib->priority = GetPriority((ptr + 24));
		pattrib->ack_policy = GetAckpolicy((ptr + 24));
		pattrib->amsdu = GetAMsdu((ptr + 24));
		pattrib->hdrlen = pattrib->to_fr_ds == 3 ? 32 : 26;

		अगर (pattrib->priority != 0 && pattrib->priority != 3)
			adapter->recvpriv.bIsAnyNonBEPkts = true;
	पूर्ण अन्यथा अणु
		pattrib->priority = 0;
		pattrib->hdrlen = pattrib->to_fr_ds == 3 ? 30 : 24;
	पूर्ण

	अगर (pattrib->order)/* HT-CTRL 11n */
		pattrib->hdrlen += 4;

	precv_frame->preorder_ctrl = &psta->recvreorder_ctrl[pattrib->priority];

	/*  decache, drop duplicate recv packets */
	अगर (recv_decache(precv_frame, bretry, &psta->sta_recvpriv.rxcache) == _FAIL) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("decache : drop pkt\n"));
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (pattrib->privacy) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("%s:pattrib->privacy=%x\n", __func__, pattrib->privacy));
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\न ^^^^^^^^^^^is_multicast_ether_addr(pattrib->ra(0x%02x))=%d^^^^^^^^^^^^^^^6\न", pattrib->ra[0], is_multicast_ether_addr(pattrib->ra)));

		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt, is_multicast_ether_addr(pattrib->ra));

		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("\n pattrib->encrypt=%d\n", pattrib->encrypt));

		SET_ICE_IV_LEN(pattrib->iv_len, pattrib->icv_len, pattrib->encrypt);
	पूर्ण अन्यथा अणु
		pattrib->encrypt = 0;
		pattrib->iv_len = 0;
		pattrib->icv_len = 0;
	पूर्ण

निकास:

	वापस ret;
पूर्ण

अटल पूर्णांक validate_recv_frame(काष्ठा adapter *adapter,
			       काष्ठा recv_frame *precv_frame)
अणु
	/* shall check frame subtype, to / from ds, da, bssid */

	/* then call check अगर rx seq/frag. duplicated. */

	u8 type;
	u8 subtype;
	पूर्णांक retval = _SUCCESS;
	u8 bDumpRxPkt;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->attrib;
	u8 *ptr = precv_frame->pkt->data;
	u8  ver = (अचिन्हित अक्षर)(*ptr) & 0x3;
	काष्ठा mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;

	अगर (pmlmeext->sitesurvey_res.state == SCAN_PROCESS) अणु
		पूर्णांक ch_set_idx = rtw_ch_set_search_ch(pmlmeext->channel_set, rtw_get_oper_ch(adapter));

		अगर (ch_set_idx >= 0)
			pmlmeext->channel_set[ch_set_idx].rx_count++;
	पूर्ण

	/* add version chk */
	अगर (ver != 0) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("validate_recv_data_frame fail! (ver!=0)\n"));
		retval = _FAIL;
		जाओ निकास;
	पूर्ण

	type =  GetFrameType(ptr);
	subtype = GetFrameSubType(ptr); /* bit(7)~bit(2) */

	pattrib->to_fr_ds = get_tofr_ds(ptr);

	pattrib->frag_num = GetFragNum(ptr);
	pattrib->seq_num = GetSequence(ptr);

	pattrib->pw_save = GetPwrMgt(ptr);
	pattrib->mfrag = GetMFrag(ptr);
	pattrib->mdata = GetMData(ptr);
	pattrib->privacy = GetPrivacy(ptr);
	pattrib->order = GetOrder(ptr);

	/* Dump rx packets */
	rtw_hal_get_def_var(adapter, HAL_DEF_DBG_DUMP_RXPKT, &(bDumpRxPkt));
	अगर (bDumpRxPkt == 1) अणु/* dump all rx packets */
		अगर (_drv_err_ <= GlobalDebugLevel) अणु
			pr_info(DRIVER_PREFIX "#############################\n");
			prपूर्णांक_hex_dump(KERN_INFO, DRIVER_PREFIX, DUMP_PREFIX_NONE,
				       16, 1, ptr, 64, false);
			pr_info(DRIVER_PREFIX "#############################\n");
		पूर्ण
	पूर्ण अन्यथा अगर (bDumpRxPkt == 2) अणु
		अगर ((_drv_err_ <= GlobalDebugLevel) && (type == WIFI_MGT_TYPE)) अणु
			pr_info(DRIVER_PREFIX "#############################\n");
			prपूर्णांक_hex_dump(KERN_INFO, DRIVER_PREFIX, DUMP_PREFIX_NONE,
				       16, 1, ptr, 64, false);
			pr_info(DRIVER_PREFIX "#############################\n");
		पूर्ण
	पूर्ण अन्यथा अगर (bDumpRxPkt == 3) अणु
		अगर ((_drv_err_ <= GlobalDebugLevel) && (type == WIFI_DATA_TYPE)) अणु
			pr_info(DRIVER_PREFIX "#############################\n");
			prपूर्णांक_hex_dump(KERN_INFO, DRIVER_PREFIX, DUMP_PREFIX_NONE,
				       16, 1, ptr, 64, false);
			pr_info(DRIVER_PREFIX "#############################\n");
		पूर्ण
	पूर्ण
	चयन (type) अणु
	हाल WIFI_MGT_TYPE: /* mgnt */
		retval = validate_recv_mgnt_frame(adapter, precv_frame);
		अगर (retval == _FAIL)
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("validate_recv_mgnt_frame fail\n"));
		retval = _FAIL; /*  only data frame वापस _SUCCESS */
		अवरोध;
	हाल WIFI_CTRL_TYPE: /* ctrl */
		retval = validate_recv_ctrl_frame(adapter, precv_frame);
		अगर (retval == _FAIL)
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("validate_recv_ctrl_frame fail\n"));
		retval = _FAIL; /*  only data frame वापस _SUCCESS */
		अवरोध;
	हाल WIFI_DATA_TYPE: /* data */
		led_control_8188eu(adapter, LED_CTL_RX);
		pattrib->qos = (subtype & BIT(7)) ? 1 : 0;
		retval = validate_recv_data_frame(adapter, precv_frame);
		अगर (retval == _FAIL) अणु
			काष्ठा recv_priv *precvpriv = &adapter->recvpriv;

			precvpriv->rx_drop++;
		पूर्ण
		अवरोध;
	शेष:
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("validate_recv_data_frame fail! type= 0x%x\n", type));
		retval = _FAIL;
		अवरोध;
	पूर्ण

	/*
	 * This is the last moment beक्रमe management and control frames get
	 * discarded. So we need to क्रमward them to the monitor now or never.
	 *
	 * At the same समय data frames can still be encrypted अगर software
	 * decryption is in use. However, decryption can occur not until later
	 * (see recv_func()).
	 *
	 * Hence क्रमward the frame to the monitor anyway to preserve the order
	 * in which frames were received.
	 */
	rtl88eu_mon_recv_hook(adapter->pmondev, precv_frame);

निकास:

	वापस retval;
पूर्ण

/* हटाओ the wlanhdr and add the eth_hdr */

अटल पूर्णांक wlanhdr_to_ethhdr(काष्ठा recv_frame *precvframe)
अणु
	पूर्णांक	rmv_len;
	u16	eth_type, len;
	__be16 be_पंचांगp;
	u8	bsnaphdr;
	u8	*psnap_type;
	काष्ठा ieee80211_snap_hdr	*psnap;

	u8 *ptr = precvframe->pkt->data;
	काष्ठा rx_pkt_attrib *pattrib = &precvframe->attrib;

	अगर (pattrib->encrypt)
		skb_trim(precvframe->pkt, precvframe->pkt->len - pattrib->icv_len);

	psnap = (काष्ठा ieee80211_snap_hdr *)(ptr + pattrib->hdrlen + pattrib->iv_len);
	psnap_type = ptr + pattrib->hdrlen + pattrib->iv_len + SNAP_SIZE;
	/* convert hdr + possible LLC headers पूर्णांकo Ethernet header */
	अगर ((!स_भेद(psnap, rfc1042_header, SNAP_SIZE) &&
	     स_भेद(psnap_type, SNAP_ETH_TYPE_IPX, 2) &&
	     स_भेद(psnap_type, SNAP_ETH_TYPE_APPLETALK_AARP, 2)) ||
	     !स_भेद(psnap, bridge_tunnel_header, SNAP_SIZE)) अणु
		/* हटाओ RFC1042 or Bridge-Tunnel encapsulation and replace EtherType */
		bsnaphdr = true;
	पूर्ण अन्यथा अणु
		/* Leave Ethernet header part of hdr and full payload */
		bsnaphdr = false;
	पूर्ण

	rmv_len = pattrib->hdrlen + pattrib->iv_len + (bsnaphdr ? SNAP_SIZE : 0);
	len = precvframe->pkt->len - rmv_len;

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
		 ("\n===pattrib->hdrlen: %x,  pattrib->iv_len:%x===\n\n", pattrib->hdrlen,  pattrib->iv_len));

	स_नकल(&be_पंचांगp, ptr + rmv_len, 2);
	eth_type = ntohs(be_पंचांगp); /* pattrib->ether_type */
	pattrib->eth_type = eth_type;

	ptr = skb_pull(precvframe->pkt, rmv_len - माप(काष्ठा ethhdr) + (bsnaphdr ? 2 : 0));
	अगर (!ptr)
		वापस _FAIL;

	स_नकल(ptr, pattrib->dst, ETH_ALEN);
	स_नकल(ptr + ETH_ALEN, pattrib->src, ETH_ALEN);

	अगर (!bsnaphdr) अणु
		be_पंचांगp = htons(len);
		स_नकल(ptr + 12, &be_पंचांगp, 2);
	पूर्ण

	वापस _SUCCESS;
पूर्ण

/* perक्रमm defrag */
अटल काष्ठा recv_frame *recvframe_defrag(काष्ठा adapter *adapter,
					   काष्ठा __queue *defrag_q)
अणु
	काष्ठा list_head *plist, *phead;
	u8 wlanhdr_offset;
	u8	curfragnum;
	काष्ठा recv_frame *pnfhdr;
	काष्ठा recv_frame *prframe, *pnextrframe;
	काष्ठा __queue *pमुक्त_recv_queue;

	curfragnum = 0;
	pमुक्त_recv_queue = &adapter->recvpriv.मुक्त_recv_queue;

	phead = get_list_head(defrag_q);
	plist = phead->next;
	prframe = list_entry(plist, काष्ठा recv_frame, list);
	list_del_init(&prframe->list);

	अगर (curfragnum != prframe->attrib.frag_num) अणु
		/* the first fragment number must be 0 */
		/* मुक्त the whole queue */
		rtw_मुक्त_recvframe(prframe, pमुक्त_recv_queue);
		rtw_मुक्त_recvframe_queue(defrag_q, pमुक्त_recv_queue);

		वापस शून्य;
	पूर्ण

	curfragnum++;

	plist = get_list_head(defrag_q);

	plist = plist->next;

	जबतक (phead != plist) अणु
		pnfhdr = list_entry(plist, काष्ठा recv_frame, list);
		pnextrframe = pnfhdr;

		/* check the fragment sequence  (2nd ~n fragment frame) */

		अगर (curfragnum != pnfhdr->attrib.frag_num) अणु
			/* the fragment number must be increasing  (after decache) */
			/* release the defrag_q & prframe */
			rtw_मुक्त_recvframe(prframe, pमुक्त_recv_queue);
			rtw_मुक्त_recvframe_queue(defrag_q, pमुक्त_recv_queue);
			वापस शून्य;
		पूर्ण

		curfragnum++;

		/* copy the 2nd~n fragment frame's payload to the first fragment */
		/* get the 2nd~last fragment frame's payload */

		wlanhdr_offset = pnfhdr->attrib.hdrlen + pnfhdr->attrib.iv_len;

		skb_pull(pnextrframe->pkt, wlanhdr_offset);

		/* append  to first fragment frame's tail (अगर privacy frame, pull the ICV) */
		skb_trim(prframe->pkt, prframe->pkt->len - prframe->attrib.icv_len);

		skb_put_data(prframe->pkt, pnfhdr->pkt->data, pnfhdr->pkt->len);

		prframe->attrib.icv_len = pnfhdr->attrib.icv_len;
		plist = plist->next;
	पूर्ण

	/* मुक्त the defrag_q queue and वापस the prframe */
	rtw_मुक्त_recvframe_queue(defrag_q, pमुक्त_recv_queue);

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("Performance defrag!!!!!\n"));

	वापस prframe;
पूर्ण

/* check अगर need to defrag, अगर needed queue the frame to defrag_q */
काष्ठा recv_frame *recvframe_chk_defrag(काष्ठा adapter *padapter,
					काष्ठा recv_frame *precv_frame)
अणु
	u8	ismfrag;
	u8	fragnum;
	u8	*psta_addr;
	काष्ठा recv_frame *pfhdr;
	काष्ठा sta_info *psta;
	काष्ठा sta_priv *pstapriv;
	काष्ठा list_head *phead;
	काष्ठा recv_frame *prtnframe = शून्य;
	काष्ठा __queue *pमुक्त_recv_queue, *pdefrag_q;

	pstapriv = &padapter->stapriv;

	pfhdr = precv_frame;

	pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;

	/* need to define काष्ठा of wlan header frame ctrl */
	ismfrag = pfhdr->attrib.mfrag;
	fragnum = pfhdr->attrib.frag_num;

	psta_addr = pfhdr->attrib.ta;
	psta = rtw_get_stainfo(pstapriv, psta_addr);
	अगर (!psta) अणु
		u8 type = GetFrameType(pfhdr->pkt->data);

		अगर (type != WIFI_DATA_TYPE) अणु
			psta = rtw_get_bcmc_stainfo(padapter);
			pdefrag_q = &psta->sta_recvpriv.defrag_q;
		पूर्ण अन्यथा अणु
			pdefrag_q = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		pdefrag_q = &psta->sta_recvpriv.defrag_q;
	पूर्ण

	अगर ((ismfrag == 0) && (fragnum == 0))
		prtnframe = precv_frame;/* isn't a fragment frame */

	अगर (ismfrag == 1) अणु
		/* 0~(n-1) fragment frame */
		/* enqueue to defraf_g */
		अगर (pdefrag_q) अणु
			अगर (fragnum == 0) अणु
				/* the first fragment */
				अगर (!list_empty(&pdefrag_q->queue))
					/* मुक्त current defrag_q */
					rtw_मुक्त_recvframe_queue(pdefrag_q, pमुक्त_recv_queue);
			पूर्ण

			/* Then enqueue the 0~(n-1) fragment पूर्णांकo the defrag_q */

			phead = get_list_head(pdefrag_q);
			list_add_tail(&pfhdr->list, phead);

			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("Enqueuq: ismfrag=%d, fragnum=%d\n", ismfrag, fragnum));

			prtnframe = शून्य;
		पूर्ण अन्यथा अणु
			/* can't find this ta's defrag_queue, so मुक्त this recv_frame */
			rtw_मुक्त_recvframe(precv_frame, pमुक्त_recv_queue);
			prtnframe = शून्य;
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("Free because pdefrag_q==NULL: ismfrag=%d, fragnum=%d\n", ismfrag, fragnum));
		पूर्ण
	पूर्ण

	अगर ((ismfrag == 0) && (fragnum != 0)) अणु
		/* the last fragment frame */
		/* enqueue the last fragment */
		अगर (pdefrag_q) अणु
			phead = get_list_head(pdefrag_q);
			list_add_tail(&pfhdr->list, phead);

			/* call recvframe_defrag to defrag */
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("defrag: ismfrag=%d, fragnum=%d\n", ismfrag, fragnum));
			precv_frame = recvframe_defrag(padapter, pdefrag_q);
			prtnframe = precv_frame;
		पूर्ण अन्यथा अणु
			/* can't find this ta's defrag_queue, so मुक्त this recv_frame */
			rtw_मुक्त_recvframe(precv_frame, pमुक्त_recv_queue);
			prtnframe = शून्य;
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("Free because pdefrag_q==NULL: ismfrag=%d, fragnum=%d\n", ismfrag, fragnum));
		पूर्ण
	पूर्ण

	अगर (prtnframe && (prtnframe->attrib.privacy)) अणु
		/* after defrag we must check tkip mic code */
		अगर (recvframe_chkmic(padapter,  prtnframe) == _FAIL) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("recvframe_chkmic(padapter,  prtnframe)==_FAIL\n"));
			rtw_मुक्त_recvframe(prtnframe, pमुक्त_recv_queue);
			prtnframe = शून्य;
		पूर्ण
	पूर्ण

	वापस prtnframe;
पूर्ण

अटल पूर्णांक amsdu_to_msdu(काष्ठा adapter *padapter, काष्ठा recv_frame *prframe)
अणु
	पूर्णांक	a_len, padding_len;
	u16	eth_type, nSubframe_Length;
	u8	nr_subframes, i;
	अचिन्हित अक्षर *pdata;
	काष्ठा rx_pkt_attrib *pattrib;
	काष्ठा sk_buff *sub_skb, *subframes[MAX_SUBFRAME_COUNT];
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;
	काष्ठा __queue *pमुक्त_recv_queue = &precvpriv->मुक्त_recv_queue;

	nr_subframes = 0;
	pattrib = &prframe->attrib;

	skb_pull(prframe->pkt, prframe->attrib.hdrlen);

	अगर (prframe->attrib.iv_len > 0)
		skb_pull(prframe->pkt, prframe->attrib.iv_len);

	a_len = prframe->pkt->len;

	pdata = prframe->pkt->data;

	जबतक (a_len > ETH_HLEN) अणु
		/* Offset 12 denote 2 mac address */
		nSubframe_Length = get_unaligned_be16(pdata + 12);

		अगर (a_len < (ETHERNET_HEADER_SIZE + nSubframe_Length)) अणु
			DBG_88E("nRemain_Length is %d and nSubframe_Length is : %d\n", a_len, nSubframe_Length);
			जाओ निकास;
		पूर्ण

		/* move the data poपूर्णांक to data content */
		pdata += ETH_HLEN;
		a_len -= ETH_HLEN;

		/* Allocate new skb क्रम releasing to upper layer */
		sub_skb = dev_alloc_skb(nSubframe_Length + 12);
		अगर (!sub_skb) अणु
			DBG_88E("dev_alloc_skb() Fail!!! , nr_subframes=%d\n", nr_subframes);
			अवरोध;
		पूर्ण

		skb_reserve(sub_skb, 12);
		skb_put_data(sub_skb, pdata, nSubframe_Length);

		subframes[nr_subframes++] = sub_skb;

		अगर (nr_subframes >= MAX_SUBFRAME_COUNT) अणु
			DBG_88E("ParseSubframe(): Too many Subframes! Packets dropped!\n");
			अवरोध;
		पूर्ण

		pdata += nSubframe_Length;
		a_len -= nSubframe_Length;
		अगर (a_len != 0) अणु
			padding_len = 4 - ((nSubframe_Length + ETH_HLEN) & (4 - 1));
			अगर (padding_len == 4)
				padding_len = 0;

			अगर (a_len < padding_len)
				जाओ निकास;

			pdata += padding_len;
			a_len -= padding_len;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nr_subframes; i++) अणु
		sub_skb = subframes[i];
		/* convert hdr + possible LLC headers पूर्णांकo Ethernet header */
		eth_type = get_unaligned_be16(&sub_skb->data[6]);
		अगर (sub_skb->len >= 8 &&
		    ((!स_भेद(sub_skb->data, rfc1042_header, SNAP_SIZE) &&
			  eth_type != ETH_P_AARP && eth_type != ETH_P_IPX) ||
			 !स_भेद(sub_skb->data, bridge_tunnel_header, SNAP_SIZE))) अणु
			/* हटाओ RFC1042 or Bridge-Tunnel encapsulation and replace EtherType */
			skb_pull(sub_skb, SNAP_SIZE);
			स_नकल(skb_push(sub_skb, ETH_ALEN), pattrib->src, ETH_ALEN);
			स_नकल(skb_push(sub_skb, ETH_ALEN), pattrib->dst, ETH_ALEN);
		पूर्ण अन्यथा अणु
			__be16 len;
			/* Leave Ethernet header part of hdr and full payload */
			len = htons(sub_skb->len);
			स_नकल(skb_push(sub_skb, 2), &len, 2);
			स_नकल(skb_push(sub_skb, ETH_ALEN), pattrib->src, ETH_ALEN);
			स_नकल(skb_push(sub_skb, ETH_ALEN), pattrib->dst, ETH_ALEN);
		पूर्ण

		/* Indicate the packets to upper layer */
		/*  Insert NAT2.5 RX here! */
		sub_skb->protocol = eth_type_trans(sub_skb, padapter->pnetdev);
		sub_skb->dev = padapter->pnetdev;

		sub_skb->ip_summed = CHECKSUM_NONE;

		netअगर_rx(sub_skb);
	पूर्ण

निकास:
	rtw_मुक्त_recvframe(prframe, pमुक्त_recv_queue);/* मुक्त this recv_frame */

	वापस _SUCCESS;
पूर्ण

अटल पूर्णांक check_indicate_seq(काष्ठा recv_reorder_ctrl *preorder_ctrl, u16 seq_num)
अणु
	u8	wsize = preorder_ctrl->wsize_b;
	u16	wend = (preorder_ctrl->indicate_seq + wsize - 1) & 0xFFF;/*  4096; */

	/*  Rx Reorder initialize condition. */
	अगर (preorder_ctrl->indicate_seq == 0xFFFF)
		preorder_ctrl->indicate_seq = seq_num;

	/*  Drop out the packet which SeqNum is smaller than WinStart */
	अगर (SN_LESS(seq_num, preorder_ctrl->indicate_seq))
		वापस false;

	/*  */
	/*  Sliding winकरोw manipulation. Conditions includes: */
	/*  1. Incoming SeqNum is equal to WinStart =>Winकरोw shअगरt 1 */
	/*  2. Incoming SeqNum is larger than the WinEnd => Winकरोw shअगरt N */
	/*  */
	अगर (SN_EQUAL(seq_num, preorder_ctrl->indicate_seq)) अणु
		preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1) & 0xFFF;
	पूर्ण अन्यथा अगर (SN_LESS(wend, seq_num)) अणु
		अगर (seq_num >= (wsize - 1))
			preorder_ctrl->indicate_seq = seq_num + 1 - wsize;
		अन्यथा
			preorder_ctrl->indicate_seq = 0xFFF - (wsize - (seq_num + 1)) + 1;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक enqueue_reorder_recvframe(काष्ठा recv_reorder_ctrl *preorder_ctrl,
				     काष्ठा recv_frame *prframe)
अणु
	काष्ठा rx_pkt_attrib *pattrib = &prframe->attrib;
	काष्ठा __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;
	काष्ठा list_head *phead, *plist;
	काष्ठा recv_frame *hdr;
	काष्ठा rx_pkt_attrib *pnextattrib;

	phead = get_list_head(ppending_recvframe_queue);
	plist = phead->next;

	जबतक (phead != plist) अणु
		hdr = list_entry(plist, काष्ठा recv_frame, list);
		pnextattrib = &hdr->attrib;

		अगर (SN_LESS(pnextattrib->seq_num, pattrib->seq_num))
			plist = plist->next;
		अन्यथा अगर (SN_EQUAL(pnextattrib->seq_num, pattrib->seq_num))
			वापस false;
		अन्यथा
			अवरोध;
	पूर्ण

	list_del_init(&prframe->list);

	list_add_tail(&prframe->list, plist);
	वापस true;
पूर्ण

अटल पूर्णांक recv_indicatepkts_in_order(काष्ठा adapter *padapter, काष्ठा recv_reorder_ctrl *preorder_ctrl, पूर्णांक bक्रमced)
अणु
	काष्ठा list_head *phead, *plist;
	काष्ठा recv_frame *prframe;
	काष्ठा recv_frame *prhdr;
	काष्ठा rx_pkt_attrib *pattrib;
	पूर्णांक bPktInBuf = false;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;
	काष्ठा __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;

	phead =		get_list_head(ppending_recvframe_queue);
	plist = phead->next;

	/*  Handling some condition क्रम क्रमced indicate हाल. */
	अगर (bक्रमced) अणु
		अगर (list_empty(phead))
			वापस true;

		prhdr = list_entry(plist, काष्ठा recv_frame, list);
		pattrib = &prhdr->attrib;
		preorder_ctrl->indicate_seq = pattrib->seq_num;
	पूर्ण

	/*  Prepare indication list and indication. */
	/*  Check अगर there is any packet need indicate. */
	जबतक (!list_empty(phead)) अणु
		prhdr = list_entry(plist, काष्ठा recv_frame, list);
		prframe = prhdr;
		pattrib = &prframe->attrib;

		अगर (!SN_LESS(preorder_ctrl->indicate_seq, pattrib->seq_num)) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_,
				 ("%s: indicate=%d seq=%d amsdu=%d\n",
				  __func__, preorder_ctrl->indicate_seq, pattrib->seq_num, pattrib->amsdu));
			plist = plist->next;
			list_del_init(&prframe->list);

			अगर (SN_EQUAL(preorder_ctrl->indicate_seq, pattrib->seq_num))
				preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1) & 0xFFF;

			/* Set this as a lock to make sure that only one thपढ़ो is indicating packet. */

			/* indicate this recv_frame */
			अगर (!pattrib->amsdu) अणु
				अगर ((!padapter->bDriverStopped) &&
				    (!padapter->bSurpriseRemoved))
					rtw_recv_indicatepkt(padapter, prframe);/* indicate this recv_frame */
			पूर्ण अन्यथा अगर (pattrib->amsdu == 1) अणु
				अगर (amsdu_to_msdu(padapter, prframe) != _SUCCESS)
					rtw_मुक्त_recvframe(prframe, &precvpriv->मुक्त_recv_queue);
			पूर्ण अन्यथा अणु
				/* error condition; */
			पूर्ण

			/* Update local variables. */
			bPktInBuf = false;
		पूर्ण अन्यथा अणु
			bPktInBuf = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस bPktInBuf;
पूर्ण

अटल पूर्णांक recv_indicatepkt_reorder(काष्ठा adapter *padapter,
				    काष्ठा recv_frame *prframe)
अणु
	पूर्णांक retval = _SUCCESS;
	काष्ठा rx_pkt_attrib *pattrib = &prframe->attrib;
	काष्ठा recv_reorder_ctrl *preorder_ctrl = prframe->preorder_ctrl;
	काष्ठा __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;

	अगर (!pattrib->amsdu) अणु
		/* s1. */
		wlanhdr_to_ethhdr(prframe);

		अगर ((pattrib->qos != 1) || (pattrib->eth_type == 0x0806) ||
		    (pattrib->ack_policy != 0)) अणु
			अगर ((!padapter->bDriverStopped) &&
			    (!padapter->bSurpriseRemoved)) अणु
				RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("@@@@  %s -recv_func recv_indicatepkt\n", __func__));

				rtw_recv_indicatepkt(padapter, prframe);
				वापस _SUCCESS;
			पूर्ण

			वापस _FAIL;
		पूर्ण

		अगर (!preorder_ctrl->enable) अणु
			/* indicate this recv_frame */
			preorder_ctrl->indicate_seq = pattrib->seq_num;
			rtw_recv_indicatepkt(padapter, prframe);

			preorder_ctrl->indicate_seq =
				(preorder_ctrl->indicate_seq + 1) % 4096;
			वापस _SUCCESS;
		पूर्ण
	पूर्ण अन्यथा अगर (pattrib->amsdu == 1) अणु /* temp filter -> means didn't support A-MSDUs in a A-MPDU */
		अगर (!preorder_ctrl->enable) अणु
			preorder_ctrl->indicate_seq = pattrib->seq_num;
			retval = amsdu_to_msdu(padapter, prframe);

			preorder_ctrl->indicate_seq =
				(preorder_ctrl->indicate_seq + 1) % 4096;
			वापस retval;
		पूर्ण
	पूर्ण

	spin_lock_bh(&ppending_recvframe_queue->lock);

	RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_,
		 ("%s: indicate=%d seq=%d\n", __func__,
		  preorder_ctrl->indicate_seq, pattrib->seq_num));

	/* s2. check अगर winstart_b(indicate_seq) needs to been updated */
	अगर (!check_indicate_seq(preorder_ctrl, pattrib->seq_num)) अणु
		rtw_recv_indicatepkt(padapter, prframe);

		spin_unlock_bh(&ppending_recvframe_queue->lock);

		जाओ _success_निकास;
	पूर्ण

	/* s3. Insert all packet पूर्णांकo Reorder Queue to मुख्यtain its ordering. */
	अगर (!enqueue_reorder_recvframe(preorder_ctrl, prframe))
		जाओ _err_निकास;

	/* s4. */
	/*  Indication process. */
	/*  After Packet dropping and Sliding Winकरोw shअगरting as above, we can now just indicate the packets */
	/*  with the SeqNum smaller than latest WinStart and buffer other packets. */
	/*  */
	/*  For Rx Reorder condition: */
	/*  1. All packets with SeqNum smaller than WinStart => Indicate */
	/*  2. All packets with SeqNum larger than or equal to WinStart => Buffer it. */
	/*  */

	/* recv_indicatepkts_in_order(padapter, preorder_ctrl, true); */
	अगर (recv_indicatepkts_in_order(padapter, preorder_ctrl, false)) अणु
		mod_समयr(&preorder_ctrl->reordering_ctrl_समयr,
			  jअगरfies + msecs_to_jअगरfies(REORDER_WAIT_TIME));
		spin_unlock_bh(&ppending_recvframe_queue->lock);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&ppending_recvframe_queue->lock);
		del_समयr_sync(&preorder_ctrl->reordering_ctrl_समयr);
	पूर्ण

_success_निकास:

	वापस _SUCCESS;

_err_निकास:

	spin_unlock_bh(&ppending_recvframe_queue->lock);

	वापस _FAIL;
पूर्ण

व्योम rtw_reordering_ctrl_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा recv_reorder_ctrl *preorder_ctrl = from_समयr(preorder_ctrl, t,
							   reordering_ctrl_समयr);
	काष्ठा adapter *padapter = preorder_ctrl->padapter;
	काष्ठा __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;

	अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
		वापस;

	spin_lock_bh(&ppending_recvframe_queue->lock);

	अगर (recv_indicatepkts_in_order(padapter, preorder_ctrl, true))
		mod_समयr(&preorder_ctrl->reordering_ctrl_समयr,
			  jअगरfies + msecs_to_jअगरfies(REORDER_WAIT_TIME));

	spin_unlock_bh(&ppending_recvframe_queue->lock);
पूर्ण

अटल पूर्णांक process_recv_indicatepkts(काष्ठा adapter *padapter,
				     काष्ठा recv_frame *prframe)
अणु
	पूर्णांक retval = _SUCCESS;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv	*phtpriv = &pmlmepriv->htpriv;

	अगर (phtpriv->ht_option) अणु  /* B/G/N Mode */
		अगर (recv_indicatepkt_reorder(padapter, prframe) != _SUCCESS) अणु
			/*  including perक्रमm A-MPDU Rx Ordering Buffer Control */
			अगर ((!padapter->bDriverStopped) &&
			    (!padapter->bSurpriseRemoved)) अणु
				वापस _FAIL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु /* B/G mode */
		retval = wlanhdr_to_ethhdr(prframe);
		अगर (retval != _SUCCESS) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("wlanhdr_to_ethhdr: drop pkt\n"));
			वापस retval;
		पूर्ण

		अगर ((!padapter->bDriverStopped) &&
		    (!padapter->bSurpriseRemoved)) अणु
			/* indicate this recv_frame */
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("@@@@ %s- recv_func recv_indicatepkt\n", __func__));
			rtw_recv_indicatepkt(padapter, prframe);
		पूर्ण अन्यथा अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("@@@@ %s- recv_func free_indicatepkt\n", __func__));

			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("recv_func:bDriverStopped(%d) OR bSurpriseRemoved(%d)", padapter->bDriverStopped, padapter->bSurpriseRemoved));
			वापस _FAIL;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक recv_func_prehandle(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *rframe)
अणु
	पूर्णांक ret = _SUCCESS;
	काष्ठा __queue *pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;

	/* check the frame crtl field and decache */
	ret = validate_recv_frame(padapter, rframe);
	अगर (ret != _SUCCESS) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("recv_func: validate_recv_frame fail! drop pkt\n"));
		rtw_मुक्त_recvframe(rframe, pमुक्त_recv_queue);/* मुक्त this recv_frame */
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक recv_func_posthandle(काष्ठा adapter *padapter,
				काष्ठा recv_frame *prframe)
अणु
	पूर्णांक ret = _SUCCESS;
	काष्ठा recv_frame *orig_prframe = prframe;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;
	काष्ठा __queue *pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;

	/*  DATA FRAME */
	led_control_8188eu(padapter, LED_CTL_RX);

	prframe = decryptor(padapter, prframe);
	अगर (!prframe) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("decryptor: drop pkt\n"));
		ret = _FAIL;
		जाओ _recv_data_drop;
	पूर्ण

	prframe = recvframe_chk_defrag(padapter, prframe);
	अगर (!prframe) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("recvframe_chk_defrag: drop pkt\n"));
		जाओ _recv_data_drop;
	पूर्ण

	prframe = portctrl(padapter, prframe);
	अगर (!prframe) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("portctrl: drop pkt\n"));
		ret = _FAIL;
		जाओ _recv_data_drop;
	पूर्ण

	count_rx_stats(padapter, prframe, शून्य);

	ret = process_recv_indicatepkts(padapter, prframe);
	अगर (ret != _SUCCESS) अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("recv_func: process_recv_indicatepkts fail!\n"));
		rtw_मुक्त_recvframe(orig_prframe, pमुक्त_recv_queue);/* मुक्त this recv_frame */
		जाओ _recv_data_drop;
	पूर्ण
	वापस ret;

_recv_data_drop:
	precvpriv->rx_drop++;
	वापस ret;
पूर्ण

अटल पूर्णांक recv_func(काष्ठा adapter *padapter, काष्ठा recv_frame *rframe)
अणु
	पूर्णांक ret;
	काष्ठा rx_pkt_attrib *prxattrib = &rframe->attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_priv *mlmepriv = &padapter->mlmepriv;

	/* check अगर need to handle uc_swdec_pending_queue*/
	अगर (check_fwstate(mlmepriv, WIFI_STATION_STATE) && psecuritypriv->busetkipkey) अणु
		काष्ठा recv_frame *pending_frame;

		जबतक ((pending_frame = rtw_alloc_recvframe(&padapter->recvpriv.uc_swdec_pending_queue))) अणु
			अगर (recv_func_posthandle(padapter, pending_frame) == _SUCCESS)
				DBG_88E("%s: dequeue uc_swdec_pending_queue\n", __func__);
		पूर्ण
	पूर्ण

	ret = recv_func_prehandle(padapter, rframe);

	अगर (ret == _SUCCESS) अणु
		/* check अगर need to enqueue पूर्णांकo uc_swdec_pending_queue*/
		अगर (check_fwstate(mlmepriv, WIFI_STATION_STATE) &&
		    !is_multicast_ether_addr(prxattrib->ra) &&
		    prxattrib->encrypt > 0 &&
		    prxattrib->bdecrypted == 0 &&
		    !is_wep_enc(psecuritypriv->करोt11PrivacyAlgrthm) &&
		    !psecuritypriv->busetkipkey) अणु
			rtw_enqueue_recvframe(rframe, &padapter->recvpriv.uc_swdec_pending_queue);
			DBG_88E("%s: no key, enqueue uc_swdec_pending_queue\n", __func__);
			जाओ निकास;
		पूर्ण

		ret = recv_func_posthandle(padapter, rframe);
	पूर्ण

निकास:
	वापस ret;
पूर्ण

पूर्णांक rtw_recv_entry(काष्ठा recv_frame *precvframe)
अणु
	काष्ठा adapter *padapter = precvframe->adapter;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;
	पूर्णांक ret;

	ret = recv_func(padapter, precvframe);
	अगर (ret == _SUCCESS)
		precvpriv->rx_pkts++;
	अन्यथा
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("%s: recv_func return fail!!!\n", __func__));

	वापस ret;
पूर्ण

अटल व्योम rtw_संकेत_stat_समयr_hdl(काष्ठा समयr_list *t)
अणु
	काष्ठा adapter *adapter =
		from_समयr(adapter, t, recvpriv.संकेत_stat_समयr);
	काष्ठा recv_priv *recvpriv = &adapter->recvpriv;

	u32 पंचांगp_s, पंचांगp_q;
	u8 avg_संकेत_strength = 0;
	u8 avg_संकेत_qual = 0;
	u8 _alpha = 3; /*  this value is based on converging_स्थिरant = 5000 and sampling_पूर्णांकerval = 1000 */

	अगर (recvpriv->संकेत_strength_data.update_req == 0) अणु
		/* update_req is clear, means we got rx */
		avg_संकेत_strength = recvpriv->संकेत_strength_data.avg_val;
		/* after avg_vals are acquired, we can re-stat the संकेत
		 * values
		 */
		recvpriv->संकेत_strength_data.update_req = 1;
	पूर्ण

	अगर (recvpriv->संकेत_qual_data.update_req == 0) अणु
		/* update_req is clear, means we got rx */
		avg_संकेत_qual = recvpriv->संकेत_qual_data.avg_val;
		/* after avg_vals are acquired, we can re-stat the संकेत
		 * values
		 */
		recvpriv->संकेत_qual_data.update_req = 1;
	पूर्ण

	/* update value of संकेत_strength, rssi, संकेत_qual */
	अगर (!check_fwstate(&adapter->mlmepriv, _FW_UNDER_SURVEY)) अणु
		पंचांगp_s = avg_संकेत_strength +
			(_alpha - 1) * recvpriv->संकेत_strength;
		पंचांगp_s = DIV_ROUND_UP(पंचांगp_s, _alpha);
		अगर (पंचांगp_s > 100)
			पंचांगp_s = 100;

		पंचांगp_q = avg_संकेत_qual +
			(_alpha - 1) * recvpriv->संकेत_qual;
		पंचांगp_q = DIV_ROUND_UP(पंचांगp_q, _alpha);
		अगर (पंचांगp_q > 100)
			पंचांगp_q = 100;

		recvpriv->संकेत_strength = पंचांगp_s;
		recvpriv->rssi = (s8)translate_percentage_to_dbm(पंचांगp_s);
		recvpriv->संकेत_qual = पंचांगp_q;
	पूर्ण

	rtw_set_संकेत_stat_समयr(recvpriv);
पूर्ण
