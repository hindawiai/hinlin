<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_RECV_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <linux/jअगरfies.h>
#समावेश <rtw_recv.h>
#समावेश <net/cfg80211.h>
#समावेश <यंत्र/unaligned.h>

अटल u8 SNAP_ETH_TYPE_IPX[2] = अणु0x81, 0x37पूर्ण;
अटल u8 SNAP_ETH_TYPE_APPLETALK_AARP[2] = अणु0x80, 0xf3पूर्ण;

अटल व्योम rtw_संकेत_stat_समयr_hdl(काष्ठा समयr_list *t);

व्योम _rtw_init_sta_recv_priv(काष्ठा sta_recv_priv *psta_recvpriv)
अणु
	स_रखो((u8 *)psta_recvpriv, 0, माप(काष्ठा sta_recv_priv));

	spin_lock_init(&psta_recvpriv->lock);

	/* क्रम (i = 0; i<MAX_RX_NUMBLKS; i++) */
	/* _rtw_init_queue(&psta_recvpriv->blk_strms[i]); */

	_rtw_init_queue(&psta_recvpriv->defrag_q);
पूर्ण

चिन्हित पूर्णांक _rtw_init_recv_priv(काष्ठा recv_priv *precvpriv, काष्ठा adapter *padapter)
अणु
	चिन्हित पूर्णांक i;
	जोड़ recv_frame *precvframe;
	चिन्हित पूर्णांक	res = _SUCCESS;

	spin_lock_init(&precvpriv->lock);

	_rtw_init_queue(&precvpriv->मुक्त_recv_queue);
	_rtw_init_queue(&precvpriv->recv_pending_queue);
	_rtw_init_queue(&precvpriv->uc_swdec_pending_queue);

	precvpriv->adapter = padapter;

	precvpriv->मुक्त_recvframe_cnt = NR_RECVFRAME;

	precvpriv->pallocated_frame_buf = vzalloc(NR_RECVFRAME * माप(जोड़ recv_frame) + RXFRAME_ALIGN_SZ);

	अगर (!precvpriv->pallocated_frame_buf) अणु
		res = _FAIL;
		जाओ निकास;
	पूर्ण

	precvpriv->precv_frame_buf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(precvpriv->pallocated_frame_buf), RXFRAME_ALIGN_SZ);
	/* precvpriv->precv_frame_buf = precvpriv->pallocated_frame_buf + RXFRAME_ALIGN_SZ - */
	/* ((SIZE_PTR) (precvpriv->pallocated_frame_buf) &(RXFRAME_ALIGN_SZ-1)); */

	precvframe = (जोड़ recv_frame *) precvpriv->precv_frame_buf;


	क्रम (i = 0; i < NR_RECVFRAME; i++) अणु
		INIT_LIST_HEAD(&(precvframe->u.list));

		list_add_tail(&(precvframe->u.list), &(precvpriv->मुक्त_recv_queue.queue));

		rtw_os_recv_resource_alloc(padapter, precvframe);

		precvframe->u.hdr.len = 0;

		precvframe->u.hdr.adapter = padapter;
		precvframe++;

	पूर्ण

	res = rtw_hal_init_recv_priv(padapter);

	समयr_setup(&precvpriv->संकेत_stat_समयr, rtw_संकेत_stat_समयr_hdl,
		    0);

	precvpriv->संकेत_stat_sampling_पूर्णांकerval = 2000; /* ms */

	rtw_set_संकेत_stat_समयr(precvpriv);

निकास:
	वापस res;
पूर्ण

व्योम _rtw_मुक्त_recv_priv(काष्ठा recv_priv *precvpriv)
अणु
	काष्ठा adapter	*padapter = precvpriv->adapter;

	rtw_मुक्त_uc_swdec_pending_queue(padapter);

	rtw_os_recv_resource_मुक्त(precvpriv);

	vमुक्त(precvpriv->pallocated_frame_buf);

	rtw_hal_मुक्त_recv_priv(padapter);
पूर्ण

जोड़ recv_frame *_rtw_alloc_recvframe(काष्ठा __queue *pमुक्त_recv_queue)
अणु

	जोड़ recv_frame  *precvframe;
	काष्ठा list_head	*plist, *phead;
	काष्ठा adapter *padapter;
	काष्ठा recv_priv *precvpriv;

	अगर (list_empty(&pमुक्त_recv_queue->queue))
		precvframe = शून्य;
	अन्यथा अणु
		phead = get_list_head(pमुक्त_recv_queue);

		plist = get_next(phead);

		precvframe = (जोड़ recv_frame *)plist;

		list_del_init(&precvframe->u.hdr.list);
		padapter = precvframe->u.hdr.adapter;
		अगर (padapter) अणु
			precvpriv = &padapter->recvpriv;
			अगर (pमुक्त_recv_queue == &precvpriv->मुक्त_recv_queue)
				precvpriv->मुक्त_recvframe_cnt--;
		पूर्ण
	पूर्ण
	वापस precvframe;
पूर्ण

जोड़ recv_frame *rtw_alloc_recvframe(काष्ठा __queue *pमुक्त_recv_queue)
अणु
	जोड़ recv_frame  *precvframe;

	spin_lock_bh(&pमुक्त_recv_queue->lock);

	precvframe = _rtw_alloc_recvframe(pमुक्त_recv_queue);

	spin_unlock_bh(&pमुक्त_recv_queue->lock);

	वापस precvframe;
पूर्ण

पूर्णांक rtw_मुक्त_recvframe(जोड़ recv_frame *precvframe, काष्ठा __queue *pमुक्त_recv_queue)
अणु
	काष्ठा adapter *padapter = precvframe->u.hdr.adapter;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;

	rtw_os_मुक्त_recvframe(precvframe);


	spin_lock_bh(&pमुक्त_recv_queue->lock);

	list_del_init(&(precvframe->u.hdr.list));

	precvframe->u.hdr.len = 0;

	list_add_tail(&(precvframe->u.hdr.list), get_list_head(pमुक्त_recv_queue));

	अगर (padapter) अणु
		अगर (pमुक्त_recv_queue == &precvpriv->मुक्त_recv_queue)
				precvpriv->मुक्त_recvframe_cnt++;
	पूर्ण
	spin_unlock_bh(&pमुक्त_recv_queue->lock);
	वापस _SUCCESS;
पूर्ण




चिन्हित पूर्णांक _rtw_enqueue_recvframe(जोड़ recv_frame *precvframe, काष्ठा __queue *queue)
अणु

	काष्ठा adapter *padapter = precvframe->u.hdr.adapter;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;

	/* INIT_LIST_HEAD(&(precvframe->u.hdr.list)); */
	list_del_init(&(precvframe->u.hdr.list));


	list_add_tail(&(precvframe->u.hdr.list), get_list_head(queue));

	अगर (padapter)
		अगर (queue == &precvpriv->मुक्त_recv_queue)
			precvpriv->मुक्त_recvframe_cnt++;

	वापस _SUCCESS;
पूर्ण

चिन्हित पूर्णांक rtw_enqueue_recvframe(जोड़ recv_frame *precvframe, काष्ठा __queue *queue)
अणु
	चिन्हित पूर्णांक ret;

	/* _spinlock(&pमुक्त_recv_queue->lock); */
	spin_lock_bh(&queue->lock);
	ret = _rtw_enqueue_recvframe(precvframe, queue);
	/* spin_unlock(&pमुक्त_recv_queue->lock); */
	spin_unlock_bh(&queue->lock);

	वापस ret;
पूर्ण

/*
चिन्हित पूर्णांक	rtw_enqueue_recvframe(जोड़ recv_frame *precvframe, काष्ठा __queue *queue)
अणु
	वापस rtw_मुक्त_recvframe(precvframe, queue);
पूर्ण
*/




/*
caller : defrag ; recvframe_chk_defrag in recv_thपढ़ो  (passive)
pframequeue: defrag_queue : will be accessed in recv_thपढ़ो  (passive)

using spinlock to protect

*/

व्योम rtw_मुक्त_recvframe_queue(काष्ठा __queue *pframequeue,  काष्ठा __queue *pमुक्त_recv_queue)
अणु
	जोड़	recv_frame	*precvframe;
	काष्ठा list_head	*plist, *phead;

	spin_lock(&pframequeue->lock);

	phead = get_list_head(pframequeue);
	plist = get_next(phead);

	जबतक (phead != plist) अणु
		precvframe = (जोड़ recv_frame *)plist;

		plist = get_next(plist);

		rtw_मुक्त_recvframe(precvframe, pमुक्त_recv_queue);
	पूर्ण

	spin_unlock(&pframequeue->lock);
पूर्ण

u32 rtw_मुक्त_uc_swdec_pending_queue(काष्ठा adapter *adapter)
अणु
	u32 cnt = 0;
	जोड़ recv_frame *pending_frame;
	जबतक ((pending_frame = rtw_alloc_recvframe(&adapter->recvpriv.uc_swdec_pending_queue))) अणु
		rtw_मुक्त_recvframe(pending_frame, &adapter->recvpriv.मुक्त_recv_queue);
		cnt++;
	पूर्ण

	वापस cnt;
पूर्ण


चिन्हित पूर्णांक rtw_enqueue_recvbuf_to_head(काष्ठा recv_buf *precvbuf, काष्ठा __queue *queue)
अणु
	spin_lock_bh(&queue->lock);

	list_del_init(&precvbuf->list);
	list_add(&precvbuf->list, get_list_head(queue));

	spin_unlock_bh(&queue->lock);

	वापस _SUCCESS;
पूर्ण

चिन्हित पूर्णांक rtw_enqueue_recvbuf(काष्ठा recv_buf *precvbuf, काष्ठा __queue *queue)
अणु
	spin_lock_bh(&queue->lock);

	list_del_init(&precvbuf->list);

	list_add_tail(&precvbuf->list, get_list_head(queue));
	spin_unlock_bh(&queue->lock);
	वापस _SUCCESS;

पूर्ण

काष्ठा recv_buf *rtw_dequeue_recvbuf(काष्ठा __queue *queue)
अणु
	काष्ठा recv_buf *precvbuf;
	काष्ठा list_head	*plist, *phead;

	spin_lock_bh(&queue->lock);

	अगर (list_empty(&queue->queue))
		precvbuf = शून्य;
	अन्यथा अणु
		phead = get_list_head(queue);

		plist = get_next(phead);

		precvbuf = container_of(plist, काष्ठा recv_buf, list);

		list_del_init(&precvbuf->list);

	पूर्ण

	spin_unlock_bh(&queue->lock);

	वापस precvbuf;

पूर्ण

अटल चिन्हित पूर्णांक recvframe_chkmic(काष्ठा adapter *adapter,  जोड़ recv_frame *precvframe)
अणु

	चिन्हित पूर्णांक	i, res = _SUCCESS;
	u32 datalen;
	u8 miccode[8];
	u8 bmic_err = false, brpt_micerror = true;
	u8 *pframe, *payload, *pframemic;
	u8 *mickey;
	/* u8 *iv, rxdata_key_idx = 0; */
	काष्ठा sta_info *stainfo;
	काष्ठा rx_pkt_attrib *prxattrib = &precvframe->u.hdr.attrib;
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;

	काष्ठा mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	stainfo = rtw_get_stainfo(&adapter->stapriv, &prxattrib->ta[0]);

	अगर (prxattrib->encrypt == _TKIP_) अणु
		/* calculate mic code */
		अगर (stainfo) अणु
			अगर (IS_MCAST(prxattrib->ra)) अणु
				/* mickey =&psecuritypriv->करोt118021XGrprxmickey.skey[0]; */
				/* iv = precvframe->u.hdr.rx_data+prxattrib->hdrlen; */
				/* rxdata_key_idx =(((iv[3])>>6)&0x3) ; */
				mickey = &psecuritypriv->करोt118021XGrprxmickey[prxattrib->key_index].skey[0];

				/* psecuritypriv->करोt118021XGrpKeyid, pmlmeinfo->key_index, rxdata_key_idx); */

				अगर (psecuritypriv->binstallGrpkey == false) अणु
					res = _FAIL;
					जाओ निकास;
				पूर्ण
			पूर्ण अन्यथा अणु
				mickey = &stainfo->करोt11tkiprxmickey.skey[0];
			पूर्ण

			datalen = precvframe->u.hdr.len-prxattrib->hdrlen-prxattrib->iv_len-prxattrib->icv_len-8;/* icv_len included the mic code */
			pframe = precvframe->u.hdr.rx_data;
			payload = pframe+prxattrib->hdrlen+prxattrib->iv_len;

			rtw_seccalctkipmic(mickey, pframe, payload, datalen, &miccode[0], (अचिन्हित अक्षर)prxattrib->priority); /* care the length of the data */

			pframemic = payload+datalen;

			bmic_err = false;

			क्रम (i = 0; i < 8; i++) अणु
				अगर (miccode[i] != *(pframemic + i))
					bmic_err = true;
			पूर्ण


			अगर (bmic_err == true) अणु
				/*  द्विगुन check key_index क्रम some timing issue , */
				/*  cannot compare with psecuritypriv->करोt118021XGrpKeyid also cause timing issue */
				अगर ((IS_MCAST(prxattrib->ra) == true)  && (prxattrib->key_index != pmlmeinfo->key_index))
					brpt_micerror = false;

				अगर (prxattrib->bdecrypted && brpt_micerror)
					rtw_handle_tkip_mic_err(adapter, (u8)IS_MCAST(prxattrib->ra));

				res = _FAIL;

			पूर्ण अन्यथा अणु
				/* mic checked ok */
				अगर (!psecuritypriv->bcheck_grpkey &&
				    IS_MCAST(prxattrib->ra))
					psecuritypriv->bcheck_grpkey = true;
			पूर्ण
		पूर्ण

		recvframe_pull_tail(precvframe, 8);

	पूर्ण

निकास:
	वापस res;

पूर्ण

/* decrypt and set the ivlen, icvlen of the recv_frame */
अटल जोड़ recv_frame *decryptor(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु

	काष्ठा rx_pkt_attrib *prxattrib = &precv_frame->u.hdr.attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	जोड़ recv_frame *वापस_packet = precv_frame;
	u32  res = _SUCCESS;

	अगर (prxattrib->encrypt > 0) अणु
		u8 *iv = precv_frame->u.hdr.rx_data+prxattrib->hdrlen;
		prxattrib->key_index = (((iv[3])>>6)&0x3);

		अगर (prxattrib->key_index > WEP_KEYS) अणु
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

	अगर ((prxattrib->encrypt > 0) && ((prxattrib->bdecrypted == 0) || (psecuritypriv->sw_decrypt == true))) अणु
		psecuritypriv->hw_decrypted = false;

		चयन (prxattrib->encrypt) अणु
		हाल _WEP40_:
		हाल _WEP104_:
			rtw_wep_decrypt(padapter, (u8 *)precv_frame);
			अवरोध;
		हाल _TKIP_:
			res = rtw_tkip_decrypt(padapter, (u8 *)precv_frame);
			अवरोध;
		हाल _AES_:
			res = rtw_aes_decrypt(padapter, (u8 *)precv_frame);
			अवरोध;
		शेष:
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (prxattrib->bdecrypted == 1 && prxattrib->encrypt > 0 &&
		   (psecuritypriv->busetkipkey == 1 || prxattrib->encrypt != _TKIP_)
		) अणु
		psecuritypriv->hw_decrypted = true;
	पूर्ण अन्यथा अणु
	पूर्ण

	अगर (res == _FAIL) अणु
		rtw_मुक्त_recvframe(वापस_packet, &padapter->recvpriv.मुक्त_recv_queue);
		वापस_packet = शून्य;
	पूर्ण अन्यथा
		prxattrib->bdecrypted = true;

	वापस वापस_packet;
पूर्ण

/* set the security inक्रमmation in the recv_frame */
अटल जोड़ recv_frame *portctrl(काष्ठा adapter *adapter, जोड़ recv_frame *precv_frame)
अणु
	u8 *psta_addr = शून्य;
	u8 *ptr;
	uपूर्णांक  auth_alg;
	काष्ठा recv_frame_hdr *pfhdr;
	काष्ठा sta_info *psta;
	काष्ठा sta_priv *pstapriv;
	जोड़ recv_frame *prtnframe;
	u16 ether_type = 0;
	u16  eapol_type = 0x888e;/* क्रम Funia BD's WPA issue */
	काष्ठा rx_pkt_attrib *pattrib;

	pstapriv = &adapter->stapriv;

	auth_alg = adapter->securitypriv.करोt11AuthAlgrthm;

	ptr = get_recvframe_data(precv_frame);
	pfhdr = &precv_frame->u.hdr;
	pattrib = &pfhdr->attrib;
	psta_addr = pattrib->ta;

	prtnframe = शून्य;

	psta = rtw_get_stainfo(pstapriv, psta_addr);

	अगर (auth_alg == 2) अणु
		अगर ((psta) && (psta->ieee8021x_blocked)) अणु
			__be16 be_पंचांगp;

			/* blocked */
			/* only accept EAPOL frame */

			prtnframe = precv_frame;

			/* get ether_type */
			ptr = ptr+pfhdr->attrib.hdrlen+pfhdr->attrib.iv_len+LLC_HEADER_SIZE;
			स_नकल(&be_पंचांगp, ptr, 2);
			ether_type = ntohs(be_पंचांगp);

			अगर (ether_type == eapol_type)
				prtnframe = precv_frame;
			अन्यथा अणु
				/* मुक्त this frame */
				rtw_मुक्त_recvframe(precv_frame, &adapter->recvpriv.मुक्त_recv_queue);
				prtnframe = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* allowed */
			/* check decryption status, and decrypt the frame अगर needed */

			prtnframe = precv_frame;
			/* check is the EAPOL frame or not (Rekey) */
			/* अगर (ether_type == eapol_type) अणु */
				/* check Rekey */

			/* prtnframe =precv_frame; */
			/*  */
			/* अन्यथा अणु */
			/*  */
		पूर्ण
	पूर्ण अन्यथा
		prtnframe = precv_frame;

	वापस prtnframe;
पूर्ण

अटल चिन्हित पूर्णांक recv_decache(जोड़ recv_frame *precv_frame, u8 bretry, काष्ठा stainfo_rxcache *prxcache)
अणु
	चिन्हित पूर्णांक tid = precv_frame->u.hdr.attrib.priority;

	u16 seq_ctrl = ((precv_frame->u.hdr.attrib.seq_num&0xffff) << 4) |
		(precv_frame->u.hdr.attrib.frag_num & 0xf);

	अगर (tid > 15)
		वापस _FAIL;

	अगर (1) अणु /* अगर (bretry) */
		अगर (seq_ctrl == prxcache->tid_rxseq[tid])
			वापस _FAIL;
	पूर्ण

	prxcache->tid_rxseq[tid] = seq_ctrl;

	वापस _SUCCESS;

पूर्ण

अटल व्योम process_pwrbit_data(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	अचिन्हित अक्षर pwrbit;
	u8 *ptr = precv_frame->u.hdr.rx_data;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *psta = शून्य;

	psta = rtw_get_stainfo(pstapriv, pattrib->src);

	pwrbit = GetPwrMgt(ptr);

	अगर (psta) अणु
		अगर (pwrbit) अणु
			अगर (!(psta->state & WIFI_SLEEP_STATE)) अणु
				/* psta->state |= WIFI_SLEEP_STATE; */
				/* pstapriv->sta_dz_biपंचांगap |= BIT(psta->aid); */

				stop_sta_xmit(padapter, psta);

			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (psta->state & WIFI_SLEEP_STATE) अणु
				/* psta->state ^= WIFI_SLEEP_STATE; */
				/* pstapriv->sta_dz_biपंचांगap &= ~BIT(psta->aid); */

				wakeup_sta_to_xmit(padapter, psta);
			पूर्ण
		पूर्ण

	पूर्ण
पूर्ण

अटल व्योम process_wmmps_data(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा sta_info *psta = शून्य;

	psta = rtw_get_stainfo(pstapriv, pattrib->src);

	अगर (!psta)
		वापस;

	अगर (!psta->qos_option)
		वापस;

	अगर (!(psta->qos_info&0xf))
		वापस;

	अगर (psta->state&WIFI_SLEEP_STATE) अणु
		u8 wmmps_ac = 0;

		चयन (pattrib->priority) अणु
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

		अगर (wmmps_ac) अणु
			अगर (psta->sleepq_ac_len > 0)
				/* process received triggered frame */
				xmit_delivery_enabled_frames(padapter, psta);
			अन्यथा
				/* issue one qos null frame with More data bit = 0 and the EOSP bit set (= 1) */
				issue_qos_nulldata(padapter, psta->hwaddr, (u16)pattrib->priority, 0, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम count_rx_stats(काष्ठा adapter *padapter, जोड़ recv_frame *prframe, काष्ठा sta_info *sta)
अणु
	पूर्णांक sz;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा stainfo_stats *pstats = शून्य;
	काष्ठा rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;

	sz = get_recvframe_len(prframe);
	precvpriv->rx_bytes += sz;

	padapter->mlmepriv.LinkDetectInfo.NumRxOkInPeriod++;

	अगर ((!MacAddr_isBcst(pattrib->dst)) && (!IS_MCAST(pattrib->dst)))
		padapter->mlmepriv.LinkDetectInfo.NumRxUnicastOkInPeriod++;

	अगर (sta)
		psta = sta;
	अन्यथा
		psta = prframe->u.hdr.psta;

	अगर (psta) अणु
		pstats = &psta->sta_stats;

		pstats->rx_data_pkts++;
		pstats->rx_bytes += sz;
	पूर्ण

	traffic_check_क्रम_leave_lps(padapter, false, 0);
पूर्ण

अटल चिन्हित पूर्णांक sta2sta_data_frame(काष्ठा adapter *adapter, जोड़ recv_frame *precv_frame,
			काष्ठा sta_info **psta)
अणु
	u8 *ptr = precv_frame->u.hdr.rx_data;
	चिन्हित पूर्णांक ret = _SUCCESS;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *mybssid  = get_bssid(pmlmepriv);
	u8 *myhwaddr = myid(&adapter->eeprompriv);
	u8 *sta_addr = शून्य;
	चिन्हित पूर्णांक bmcast = IS_MCAST(pattrib->dst);

	अगर ((check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)) अणु

		/*  filter packets that SA is myself or multicast or broadcast */
		अगर (!स_भेद(myhwaddr, pattrib->src, ETH_ALEN)) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		अगर ((स_भेद(myhwaddr, pattrib->dst, ETH_ALEN))	&& (!bmcast)) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		अगर (!स_भेद(pattrib->bssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		   !स_भेद(mybssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		   (स_भेद(pattrib->bssid, mybssid, ETH_ALEN))) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		sta_addr = pattrib->src;

	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true) अणु
		/*  For Station mode, sa and bssid should always be BSSID, and DA is my mac-address */
		अगर (स_भेद(pattrib->bssid, pattrib->src, ETH_ALEN)) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		sta_addr = pattrib->bssid;
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) अणु
		अगर (bmcast) अणु
			/*  For AP mode, अगर DA == MCAST, then BSSID should be also MCAST */
			अगर (!IS_MCAST(pattrib->bssid)) अणु
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

	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE) == true) अणु
		स_नकल(pattrib->dst, GetAddr1Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->src, GetAddr2Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->bssid, GetAddr3Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->ra, pattrib->dst, ETH_ALEN);
		स_नकल(pattrib->ta, pattrib->src, ETH_ALEN);

		sta_addr = mybssid;
	पूर्ण अन्यथा
		ret  = _FAIL;



	अगर (bmcast)
		*psta = rtw_get_bcmc_stainfo(adapter);
	अन्यथा
		*psta = rtw_get_stainfo(pstapriv, sta_addr); /*  get ap_info */

	अगर (!*psta) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल चिन्हित पूर्णांक ap2sta_data_frame(काष्ठा adapter *adapter, जोड़ recv_frame *precv_frame,
		       काष्ठा sta_info **psta)
अणु
	u8 *ptr = precv_frame->u.hdr.rx_data;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	चिन्हित पूर्णांक ret = _SUCCESS;
	काष्ठा sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *mybssid  = get_bssid(pmlmepriv);
	u8 *myhwaddr = myid(&adapter->eeprompriv);
	चिन्हित पूर्णांक bmcast = IS_MCAST(pattrib->dst);

	अगर ((check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true) &&
	    (check_fwstate(pmlmepriv, _FW_LINKED) == true ||
	     check_fwstate(pmlmepriv, _FW_UNDER_LINKING) == true)
		) अणु

		/*  filter packets that SA is myself or multicast or broadcast */
		अगर (!स_भेद(myhwaddr, pattrib->src, ETH_ALEN)) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		/*  da should be क्रम me */
		अगर ((स_भेद(myhwaddr, pattrib->dst, ETH_ALEN)) && (!bmcast)) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण


		/*  check BSSID */
		अगर (!स_भेद(pattrib->bssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		     !स_भेद(mybssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		     (स_भेद(pattrib->bssid, mybssid, ETH_ALEN))) अणु

			अगर (!bmcast)
				issue_deauth(adapter, pattrib->bssid, WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);

			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		अगर (bmcast)
			*psta = rtw_get_bcmc_stainfo(adapter);
		अन्यथा
			*psta = rtw_get_stainfo(pstapriv, pattrib->bssid); /*  get ap_info */

		अगर (!*psta) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		अगर (GetFrameSubType(ptr) & BIT(6)) अणु
			/* No data, will not indicate to upper layer, temporily count it here */
			count_rx_stats(adapter, precv_frame, *psta);
			ret = RTW_RX_HANDLED;
			जाओ निकास;
		पूर्ण

	पूर्ण अन्यथा अगर ((check_fwstate(pmlmepriv, WIFI_MP_STATE) == true) &&
		     (check_fwstate(pmlmepriv, _FW_LINKED) == true)) अणु
		स_नकल(pattrib->dst, GetAddr1Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->src, GetAddr2Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->bssid, GetAddr3Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->ra, pattrib->dst, ETH_ALEN);
		स_नकल(pattrib->ta, pattrib->src, ETH_ALEN);

		/*  */
		स_नकल(pattrib->bssid,  mybssid, ETH_ALEN);


		*psta = rtw_get_stainfo(pstapriv, pattrib->bssid); /*  get sta_info */
		अगर (!*psta) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण


	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) अणु
		/* Special हाल */
		ret = RTW_RX_HANDLED;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		अगर (!स_भेद(myhwaddr, pattrib->dst, ETH_ALEN) && (!bmcast)) अणु
			*psta = rtw_get_stainfo(pstapriv, pattrib->bssid); /*  get sta_info */
			अगर (!*psta) अणु

				/* क्रम AP multicast issue , modअगरy by yiwei */
				अटल अचिन्हित दीर्घ send_issue_deauth_समय;

				अगर (jअगरfies_to_msecs(jअगरfies - send_issue_deauth_समय) > 10000 || send_issue_deauth_समय == 0) अणु
					send_issue_deauth_समय = jअगरfies;

					issue_deauth(adapter, pattrib->bssid, WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);
				पूर्ण
			पूर्ण
		पूर्ण

		ret = _FAIL;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल चिन्हित पूर्णांक sta2ap_data_frame(काष्ठा adapter *adapter, जोड़ recv_frame *precv_frame,
		       काष्ठा sta_info **psta)
अणु
	u8 *ptr = precv_frame->u.hdr.rx_data;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	अचिन्हित अक्षर *mybssid  = get_bssid(pmlmepriv);
	चिन्हित पूर्णांक ret = _SUCCESS;

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) अणु
		/* For AP mode, RA =BSSID, TX =STA(SRC_ADDR), A3 =DST_ADDR */
		अगर (स_भेद(pattrib->bssid, mybssid, ETH_ALEN)) अणु
			ret = _FAIL;
			जाओ निकास;
		पूर्ण

		*psta = rtw_get_stainfo(pstapriv, pattrib->src);
		अगर (!*psta) अणु
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
		issue_deauth(adapter, pattrib->src, WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA);
		ret = RTW_RX_HANDLED;
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल चिन्हित पूर्णांक validate_recv_ctrl_frame(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	काष्ठा sta_info *psta = शून्य;
	/* uपूर्णांक len = precv_frame->u.hdr.len; */

	अगर (GetFrameType(pframe) != WIFI_CTRL_TYPE)
		वापस _FAIL;

	/* receive the frames that ra(a1) is my address */
	अगर (स_भेद(GetAddr1Ptr(pframe), myid(&padapter->eeprompriv), ETH_ALEN))
		वापस _FAIL;

	psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));
	अगर (!psta)
		वापस _FAIL;

	/* क्रम rx pkt statistics */
	psta->sta_stats.rx_ctrl_pkts++;

	/* only handle ps-poll */
	अगर (GetFrameSubType(pframe) == WIFI_PSPOLL) अणु
		u16 aid;
		u8 wmmps_ac = 0;

		aid = GetAid(pframe);
		अगर (psta->aid != aid)
			वापस _FAIL;

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
			वापस _FAIL;

		अगर (psta->state & WIFI_STA_ALIVE_CHK_STATE) अणु
			psta->expire_to = pstapriv->expire_to;
			psta->state ^= WIFI_STA_ALIVE_CHK_STATE;
		पूर्ण

		अगर ((psta->state&WIFI_SLEEP_STATE) && (pstapriv->sta_dz_biपंचांगap&BIT(psta->aid))) अणु
			काष्ठा list_head	*xmitframe_plist, *xmitframe_phead;
			काष्ठा xmit_frame *pxmitframe = शून्य;
			काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

			/* spin_lock_bh(&psta->sleep_q.lock); */
			spin_lock_bh(&pxmitpriv->lock);

			xmitframe_phead = get_list_head(&psta->sleep_q);
			xmitframe_plist = get_next(xmitframe_phead);

			अगर (xmitframe_phead != xmitframe_plist) अणु
				pxmitframe = container_of(xmitframe_plist, काष्ठा xmit_frame, list);

				xmitframe_plist = get_next(xmitframe_plist);

				list_del_init(&pxmitframe->list);

				psta->sleepq_len--;

				अगर (psta->sleepq_len > 0)
					pxmitframe->attrib.mdata = 1;
				अन्यथा
					pxmitframe->attrib.mdata = 0;

				pxmitframe->attrib.triggered = 1;

				rtw_hal_xmitframe_enqueue(padapter, pxmitframe);

				अगर (psta->sleepq_len == 0) अणु
					pstapriv->tim_biपंचांगap &= ~BIT(psta->aid);

					/* update BCN क्रम TIM IE */
					/* update_BCNTIM(padapter); */
					update_beacon(padapter, WLAN_EID_TIM, शून्य, true);
				पूर्ण

				/* spin_unlock_bh(&psta->sleep_q.lock); */
				spin_unlock_bh(&pxmitpriv->lock);

			पूर्ण अन्यथा अणु
				/* spin_unlock_bh(&psta->sleep_q.lock); */
				spin_unlock_bh(&pxmitpriv->lock);

				अगर (pstapriv->tim_biपंचांगap&BIT(psta->aid)) अणु
					अगर (psta->sleepq_len == 0) अणु
						/* issue nulldata with More data bit = 0 to indicate we have no buffered packets */
						issue_nulldata_in_पूर्णांकerrupt(padapter, psta->hwaddr);
					पूर्ण अन्यथा अणु
						psta->sleepq_len = 0;
					पूर्ण

					pstapriv->tim_biपंचांगap &= ~BIT(psta->aid);

					/* update BCN क्रम TIM IE */
					/* update_BCNTIM(padapter); */
					update_beacon(padapter, WLAN_EID_TIM, शून्य, true);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस _FAIL;

पूर्ण

/* perक्रमm defrag */
अटल जोड़ recv_frame *recvframe_defrag(काष्ठा adapter *adapter,
					  काष्ठा __queue *defrag_q)
अणु
	काष्ठा list_head	 *plist, *phead;
	u8  wlanhdr_offset;
	u8 curfragnum;
	काष्ठा recv_frame_hdr *pfhdr, *pnfhdr;
	जोड़ recv_frame *prframe, *pnextrframe;
	काष्ठा __queue	*pमुक्त_recv_queue;

	curfragnum = 0;
	pमुक्त_recv_queue = &adapter->recvpriv.मुक्त_recv_queue;

	phead = get_list_head(defrag_q);
	plist = get_next(phead);
	prframe = (जोड़ recv_frame *)plist;
	pfhdr = &prframe->u.hdr;
	list_del_init(&(prframe->u.list));

	अगर (curfragnum != pfhdr->attrib.frag_num) अणु
		/* the first fragment number must be 0 */
		/* मुक्त the whole queue */
		rtw_मुक्त_recvframe(prframe, pमुक्त_recv_queue);
		rtw_मुक्त_recvframe_queue(defrag_q, pमुक्त_recv_queue);

		वापस शून्य;
	पूर्ण

	curfragnum++;

	plist = get_list_head(defrag_q);

	plist = get_next(plist);

	जबतक (phead != plist) अणु
		pnextrframe = (जोड़ recv_frame *)plist;
		pnfhdr = &pnextrframe->u.hdr;


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

		recvframe_pull(pnextrframe, wlanhdr_offset);

		/* append  to first fragment frame's tail (अगर privacy frame, pull the ICV) */
		recvframe_pull_tail(prframe, pfhdr->attrib.icv_len);

		/* स_नकल */
		स_नकल(pfhdr->rx_tail, pnfhdr->rx_data, pnfhdr->len);

		recvframe_put(prframe, pnfhdr->len);

		pfhdr->attrib.icv_len = pnfhdr->attrib.icv_len;
		plist = get_next(plist);

	पूर्ण

	/* मुक्त the defrag_q queue and वापस the prframe */
	rtw_मुक्त_recvframe_queue(defrag_q, pमुक्त_recv_queue);

	वापस prframe;
पूर्ण

/* check अगर need to defrag, अगर needed queue the frame to defrag_q */
अटल जोड़ recv_frame *recvframe_chk_defrag(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	u8 ismfrag;
	u8 fragnum;
	u8 *psta_addr;
	काष्ठा recv_frame_hdr *pfhdr;
	काष्ठा sta_info *psta;
	काष्ठा sta_priv *pstapriv;
	काष्ठा list_head *phead;
	जोड़ recv_frame *prtnframe = शून्य;
	काष्ठा __queue *pमुक्त_recv_queue, *pdefrag_q;

	pstapriv = &padapter->stapriv;

	pfhdr = &precv_frame->u.hdr;

	pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;

	/* need to define काष्ठा of wlan header frame ctrl */
	ismfrag = pfhdr->attrib.mfrag;
	fragnum = pfhdr->attrib.frag_num;

	psta_addr = pfhdr->attrib.ta;
	psta = rtw_get_stainfo(pstapriv, psta_addr);
	अगर (!psta) अणु
		u8 type = GetFrameType(pfhdr->rx_data);
		अगर (type != WIFI_DATA_TYPE) अणु
			psta = rtw_get_bcmc_stainfo(padapter);
			pdefrag_q = &psta->sta_recvpriv.defrag_q;
		पूर्ण अन्यथा
			pdefrag_q = शून्य;
	पूर्ण अन्यथा
		pdefrag_q = &psta->sta_recvpriv.defrag_q;

	अगर ((ismfrag == 0) && (fragnum == 0))
		prtnframe = precv_frame;/* isn't a fragment frame */

	अगर (ismfrag == 1) अणु
		/* 0~(n-1) fragment frame */
		/* enqueue to defraf_g */
		अगर (pdefrag_q) अणु
			अगर (fragnum == 0)
				/* the first fragment */
				अगर (!list_empty(&pdefrag_q->queue))
					/* मुक्त current defrag_q */
					rtw_मुक्त_recvframe_queue(pdefrag_q, pमुक्त_recv_queue);


			/* Then enqueue the 0~(n-1) fragment पूर्णांकo the defrag_q */

			/* spin_lock(&pdefrag_q->lock); */
			phead = get_list_head(pdefrag_q);
			list_add_tail(&pfhdr->list, phead);
			/* spin_unlock(&pdefrag_q->lock); */

			prtnframe = शून्य;

		पूर्ण अन्यथा अणु
			/* can't find this ta's defrag_queue, so मुक्त this recv_frame */
			rtw_मुक्त_recvframe(precv_frame, pमुक्त_recv_queue);
			prtnframe = शून्य;
		पूर्ण

	पूर्ण

	अगर ((ismfrag == 0) && (fragnum != 0)) अणु
		/* the last fragment frame */
		/* enqueue the last fragment */
		अगर (pdefrag_q) अणु
			/* spin_lock(&pdefrag_q->lock); */
			phead = get_list_head(pdefrag_q);
			list_add_tail(&pfhdr->list, phead);
			/* spin_unlock(&pdefrag_q->lock); */

			/* call recvframe_defrag to defrag */
			precv_frame = recvframe_defrag(padapter, pdefrag_q);
			prtnframe = precv_frame;

		पूर्ण अन्यथा अणु
			/* can't find this ta's defrag_queue, so मुक्त this recv_frame */
			rtw_मुक्त_recvframe(precv_frame, pमुक्त_recv_queue);
			prtnframe = शून्य;
		पूर्ण

	पूर्ण


	अगर ((prtnframe) && (prtnframe->u.hdr.attrib.privacy)) अणु
		/* after defrag we must check tkip mic code */
		अगर (recvframe_chkmic(padapter,  prtnframe) == _FAIL) अणु
			rtw_मुक्त_recvframe(prtnframe, pमुक्त_recv_queue);
			prtnframe = शून्य;
		पूर्ण
	पूर्ण
	वापस prtnframe;
पूर्ण

अटल चिन्हित पूर्णांक validate_recv_mgnt_frame(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	/* काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv; */

	precv_frame = recvframe_chk_defrag(padapter, precv_frame);
	अगर (!precv_frame)
		वापस _SUCCESS;

	अणु
		/* क्रम rx pkt statistics */
		काष्ठा sta_info *psta = rtw_get_stainfo(&padapter->stapriv, GetAddr2Ptr(precv_frame->u.hdr.rx_data));
		अगर (psta) अणु
			psta->sta_stats.rx_mgnt_pkts++;
			अगर (GetFrameSubType(precv_frame->u.hdr.rx_data) == WIFI_BEACON)
				psta->sta_stats.rx_beacon_pkts++;
			अन्यथा अगर (GetFrameSubType(precv_frame->u.hdr.rx_data) == WIFI_PROBEREQ)
				psta->sta_stats.rx_probereq_pkts++;
			अन्यथा अगर (GetFrameSubType(precv_frame->u.hdr.rx_data) == WIFI_PROBERSP) अणु
				अगर (!स_भेद(padapter->eeprompriv.mac_addr, GetAddr1Ptr(precv_frame->u.hdr.rx_data), ETH_ALEN))
					psta->sta_stats.rx_probersp_pkts++;
				अन्यथा अगर (is_broadcast_mac_addr(GetAddr1Ptr(precv_frame->u.hdr.rx_data)) ||
					 is_multicast_mac_addr(GetAddr1Ptr(precv_frame->u.hdr.rx_data)))
					psta->sta_stats.rx_probersp_bm_pkts++;
				अन्यथा
					psta->sta_stats.rx_probersp_uo_pkts++;
			पूर्ण
		पूर्ण
	पूर्ण

	mgt_dispatcher(padapter, precv_frame);

	वापस _SUCCESS;

पूर्ण

अटल चिन्हित पूर्णांक validate_recv_data_frame(काष्ठा adapter *adapter, जोड़ recv_frame *precv_frame)
अणु
	u8 bretry;
	u8 *psa, *pda, *pbssid;
	काष्ठा sta_info *psta = शून्य;
	u8 *ptr = precv_frame->u.hdr.rx_data;
	काष्ठा rx_pkt_attrib	*pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;
	चिन्हित पूर्णांक ret = _SUCCESS;

	bretry = GetRetry(ptr);
	pda = get_da(ptr);
	psa = get_sa(ptr);
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
		अवरोध;

	शेष:
		ret = _FAIL;
		अवरोध;

	पूर्ण

	अगर (ret == _FAIL) अणु
		जाओ निकास;
	पूर्ण अन्यथा अगर (ret == RTW_RX_HANDLED) अणु
		जाओ निकास;
	पूर्ण


	अगर (!psta) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	/* psta->rssi = prxcmd->rssi; */
	/* psta->संकेत_quality = prxcmd->sq; */
	precv_frame->u.hdr.psta = psta;


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

	precv_frame->u.hdr.preorder_ctrl = &psta->recvreorder_ctrl[pattrib->priority];

	/*  decache, drop duplicate recv packets */
	अगर (recv_decache(precv_frame, bretry, &psta->sta_recvpriv.rxcache) == _FAIL) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (pattrib->privacy) अणु
		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt, IS_MCAST(pattrib->ra));

		SET_ICE_IV_LEN(pattrib->iv_len, pattrib->icv_len, pattrib->encrypt);
	पूर्ण अन्यथा अणु
		pattrib->encrypt = 0;
		pattrib->iv_len = pattrib->icv_len = 0;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल चिन्हित पूर्णांक validate_80211w_mgmt(काष्ठा adapter *adapter, जोड़ recv_frame *precv_frame)
अणु
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	u8 *ptr = precv_frame->u.hdr.rx_data;
	u8 subtype;

	subtype = GetFrameSubType(ptr); /* bit(7)~bit(2) */

	/* only support station mode */
	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) && check_fwstate(pmlmepriv, _FW_LINKED) &&
	    adapter->securitypriv.binstallBIPkey == true) अणु
		/* unicast management frame decrypt */
		अगर (pattrib->privacy && !(IS_MCAST(GetAddr1Ptr(ptr))) &&
			(subtype == WIFI_DEAUTH || subtype == WIFI_DISASSOC || subtype == WIFI_ACTION)) अणु
			u8 *mgmt_DATA;
			u32 data_len = 0;

			pattrib->bdecrypted = 0;
			pattrib->encrypt = _AES_;
			pattrib->hdrlen = माप(काष्ठा ieee80211_hdr_3addr);
			/* set iv and icv length */
			SET_ICE_IV_LEN(pattrib->iv_len, pattrib->icv_len, pattrib->encrypt);
			स_नकल(pattrib->ra, GetAddr1Ptr(ptr), ETH_ALEN);
			स_नकल(pattrib->ta, GetAddr2Ptr(ptr), ETH_ALEN);
			/* actual management data frame body */
			data_len = pattrib->pkt_len - pattrib->hdrlen - pattrib->iv_len - pattrib->icv_len;
			mgmt_DATA = rtw_zदो_स्मृति(data_len);
			अगर (!mgmt_DATA) अणु
				जाओ validate_80211w_fail;
			पूर्ण
			precv_frame = decryptor(adapter, precv_frame);
			/* save actual management data frame body */
			स_नकल(mgmt_DATA, ptr+pattrib->hdrlen+pattrib->iv_len, data_len);
			/* overग_लिखो the iv field */
			स_नकल(ptr+pattrib->hdrlen, mgmt_DATA, data_len);
			/* हटाओ the iv and icv length */
			pattrib->pkt_len = pattrib->pkt_len - pattrib->iv_len - pattrib->icv_len;
			kमुक्त(mgmt_DATA);
			अगर (!precv_frame) अणु
				जाओ validate_80211w_fail;
			पूर्ण
		पूर्ण अन्यथा अगर (IS_MCAST(GetAddr1Ptr(ptr)) &&
			(subtype == WIFI_DEAUTH || subtype == WIFI_DISASSOC)) अणु
			चिन्हित पूर्णांक BIP_ret = _SUCCESS;
			/* verअगरy BIP MME IE of broadcast/multicast de-auth/disassoc packet */
			BIP_ret = rtw_BIP_verअगरy(adapter, (u8 *)precv_frame);
			अगर (BIP_ret == _FAIL) अणु
				जाओ validate_80211w_fail;
			पूर्ण अन्यथा अगर (BIP_ret == RTW_RX_HANDLED) अणु
				/* issue sa query request */
				issue_action_SA_Query(adapter, शून्य, 0, 0);
				जाओ validate_80211w_fail;
			पूर्ण
		पूर्ण अन्यथा अणु /* 802.11w protect */
			अगर (subtype == WIFI_ACTION) अणु
				/* according 802.11-2012 standard, these five types are not robust types */
				अगर (ptr[WLAN_HDR_A3_LEN] != RTW_WLAN_CATEGORY_PUBLIC          &&
					ptr[WLAN_HDR_A3_LEN] != RTW_WLAN_CATEGORY_HT              &&
					ptr[WLAN_HDR_A3_LEN] != RTW_WLAN_CATEGORY_UNPROTECTED_WNM &&
					ptr[WLAN_HDR_A3_LEN] != RTW_WLAN_CATEGORY_SELF_PROTECTED  &&
					ptr[WLAN_HDR_A3_LEN] != RTW_WLAN_CATEGORY_P2P) अणु
					जाओ validate_80211w_fail;
				पूर्ण
			पूर्ण अन्यथा अगर (subtype == WIFI_DEAUTH || subtype == WIFI_DISASSOC) अणु
				/* issue sa query request */
				issue_action_SA_Query(adapter, शून्य, 0, 0);
				जाओ validate_80211w_fail;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस _SUCCESS;

validate_80211w_fail:
	वापस _FAIL;

पूर्ण

अटल चिन्हित पूर्णांक validate_recv_frame(काष्ठा adapter *adapter, जोड़ recv_frame *precv_frame)
अणु
	/* shall check frame subtype, to / from ds, da, bssid */

	/* then call check अगर rx seq/frag. duplicated. */

	u8 type;
	u8 subtype;
	चिन्हित पूर्णांक retval = _SUCCESS;
	u8 bDumpRxPkt;

	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;

	u8 *ptr = precv_frame->u.hdr.rx_data;
	u8  ver = (अचिन्हित अक्षर) (*ptr)&0x3;

	/* add version chk */
	अगर (ver != 0) अणु
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
	rtw_hal_get_def_var(adapter, HAL_DEF_DBG_DUMP_RXPKT, &(bDumpRxPkt));

	चयन (type) अणु
	हाल WIFI_MGT_TYPE: /* mgnt */
		अगर (validate_80211w_mgmt(adapter, precv_frame) == _FAIL) अणु
			retval = _FAIL;
			अवरोध;
		पूर्ण

		retval = validate_recv_mgnt_frame(adapter, precv_frame);
		retval = _FAIL; /*  only data frame वापस _SUCCESS */
		अवरोध;
	हाल WIFI_CTRL_TYPE: /* ctrl */
		retval = validate_recv_ctrl_frame(adapter, precv_frame);
		retval = _FAIL; /*  only data frame वापस _SUCCESS */
		अवरोध;
	हाल WIFI_DATA_TYPE: /* data */
		pattrib->qos = (subtype & BIT(7)) ? 1:0;
		retval = validate_recv_data_frame(adapter, precv_frame);
		अगर (retval == _FAIL) अणु
			काष्ठा recv_priv *precvpriv = &adapter->recvpriv;
			precvpriv->rx_drop++;
		पूर्ण अन्यथा अगर (retval == _SUCCESS) अणु
#अगर_घोषित DBG_RX_DUMP_EAP
			u8 bDumpRxPkt;
			u16 eth_type;

			/*  dump eapol */
			rtw_hal_get_def_var(adapter, HAL_DEF_DBG_DUMP_RXPKT, &(bDumpRxPkt));
			/*  get ether_type */
			स_नकल(&eth_type, ptr + pattrib->hdrlen + pattrib->iv_len + LLC_HEADER_SIZE, 2);
			eth_type = ntohs((अचिन्हित लघु) eth_type);
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	शेष:
		retval = _FAIL;
		अवरोध;
	पूर्ण

निकास:
	वापस retval;
पूर्ण

/* हटाओ the wlanhdr and add the eth_hdr */
अटल चिन्हित पूर्णांक wlanhdr_to_ethhdr(जोड़ recv_frame *precvframe)
अणु
	चिन्हित पूर्णांक	rmv_len;
	u16 eth_type, len;
	u8 bsnaphdr;
	u8 *psnap_type;
	काष्ठा ieee80211_snap_hdr	*psnap;
	__be16 be_पंचांगp;
	काष्ठा adapter			*adapter = precvframe->u.hdr.adapter;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *ptr = get_recvframe_data(precvframe) ; /*  poपूर्णांक to frame_ctrl field */
	काष्ठा rx_pkt_attrib *pattrib = &precvframe->u.hdr.attrib;

	अगर (pattrib->encrypt)
		recvframe_pull_tail(precvframe, pattrib->icv_len);

	psnap = (काष्ठा ieee80211_snap_hdr	*)(ptr+pattrib->hdrlen + pattrib->iv_len);
	psnap_type = ptr+pattrib->hdrlen + pattrib->iv_len+SNAP_SIZE;
	/* convert hdr + possible LLC headers पूर्णांकo Ethernet header */
	/* eth_type = (psnap_type[0] << 8) | psnap_type[1]; */
	अगर ((!स_भेद(psnap, rfc1042_header, SNAP_SIZE) &&
		(स_भेद(psnap_type, SNAP_ETH_TYPE_IPX, 2)) &&
		(स_भेद(psnap_type, SNAP_ETH_TYPE_APPLETALK_AARP, 2))) ||
		/* eth_type != ETH_P_AARP && eth_type != ETH_P_IPX) || */
		 !स_भेद(psnap, bridge_tunnel_header, SNAP_SIZE)) अणु
		/* हटाओ RFC1042 or Bridge-Tunnel encapsulation and replace EtherType */
		bsnaphdr = true;
	पूर्ण अन्यथा
		/* Leave Ethernet header part of hdr and full payload */
		bsnaphdr = false;

	rmv_len = pattrib->hdrlen + pattrib->iv_len + (bsnaphdr?SNAP_SIZE:0);
	len = precvframe->u.hdr.len - rmv_len;

	स_नकल(&be_पंचांगp, ptr+rmv_len, 2);
	eth_type = ntohs(be_पंचांगp); /* pattrib->ether_type */
	pattrib->eth_type = eth_type;

	अगर ((check_fwstate(pmlmepriv, WIFI_MP_STATE) == true)) अणु
		ptr += rmv_len;
		*ptr = 0x87;
		*(ptr+1) = 0x12;

		eth_type = 0x8712;
		/*  append rx status क्रम mp test packets */
		ptr = recvframe_pull(precvframe, (rmv_len-माप(काष्ठा ethhdr)+2)-24);
		स_नकल(ptr, get_rxmem(precvframe), 24);
		ptr += 24;
	पूर्ण अन्यथा
		ptr = recvframe_pull(precvframe, (rmv_len-माप(काष्ठा ethhdr) + (bsnaphdr?2:0)));

	स_नकल(ptr, pattrib->dst, ETH_ALEN);
	स_नकल(ptr+ETH_ALEN, pattrib->src, ETH_ALEN);

	अगर (!bsnaphdr) अणु
		be_पंचांगp = htons(len);
		स_नकल(ptr+12, &be_पंचांगp, 2);
	पूर्ण

	वापस _SUCCESS;
पूर्ण

अटल पूर्णांक amsdu_to_msdu(काष्ठा adapter *padapter, जोड़ recv_frame *prframe)
अणु
	पूर्णांक	a_len, padding_len;
	u16 nSubframe_Length;
	u8 nr_subframes, i;
	u8 *pdata;
	काष्ठा sk_buff *sub_pkt, *subframes[MAX_SUBFRAME_COUNT];
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;
	काष्ठा __queue *pमुक्त_recv_queue = &(precvpriv->मुक्त_recv_queue);

	nr_subframes = 0;

	recvframe_pull(prframe, prframe->u.hdr.attrib.hdrlen);

	अगर (prframe->u.hdr.attrib.iv_len > 0)
		recvframe_pull(prframe, prframe->u.hdr.attrib.iv_len);

	a_len = prframe->u.hdr.len;

	pdata = prframe->u.hdr.rx_data;

	जबतक (a_len > ETH_HLEN) अणु

		/* Offset 12 denote 2 mac address */
		nSubframe_Length = get_unaligned_be16(pdata + 12);

		अगर (a_len < (ETHERNET_HEADER_SIZE + nSubframe_Length))
			अवरोध;

		sub_pkt = rtw_os_alloc_msdu_pkt(prframe, nSubframe_Length, pdata);
		अगर (!sub_pkt)
			अवरोध;

		/* move the data poपूर्णांक to data content */
		pdata += ETH_HLEN;
		a_len -= ETH_HLEN;

		subframes[nr_subframes++] = sub_pkt;

		अगर (nr_subframes >= MAX_SUBFRAME_COUNT)
			अवरोध;

		pdata += nSubframe_Length;
		a_len -= nSubframe_Length;
		अगर (a_len != 0) अणु
			padding_len = 4 - ((nSubframe_Length + ETH_HLEN) & (4-1));
			अगर (padding_len == 4)
				padding_len = 0;

			अगर (a_len < padding_len)
				अवरोध;

			pdata += padding_len;
			a_len -= padding_len;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nr_subframes; i++) अणु
		sub_pkt = subframes[i];

		/* Indicate the packets to upper layer */
		अगर (sub_pkt)
			rtw_os_recv_indicate_pkt(padapter, sub_pkt, &prframe->u.hdr.attrib);
	पूर्ण

	prframe->u.hdr.len = 0;
	rtw_मुक्त_recvframe(prframe, pमुक्त_recv_queue);/* मुक्त this recv_frame */

	वापस  _SUCCESS;
पूर्ण

अटल पूर्णांक check_indicate_seq(काष्ठा recv_reorder_ctrl *preorder_ctrl, u16 seq_num)
अणु
	काष्ठा adapter *padapter = preorder_ctrl->padapter;
	काष्ठा dvobj_priv *psdpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;
	u8 wsize = preorder_ctrl->wsize_b;
	u16 wend = (preorder_ctrl->indicate_seq + wsize - 1) & 0xFFF;/*  4096; */

	/*  Rx Reorder initialize condition. */
	अगर (preorder_ctrl->indicate_seq == 0xFFFF) अणु
		preorder_ctrl->indicate_seq = seq_num;

		/* DbgPrपूर्णांक("check_indicate_seq, 1st->indicate_seq =%d\n", precvpriv->indicate_seq); */
	पूर्ण

	/* DbgPrपूर्णांक("enter->check_indicate_seq(): IndicateSeq: %d, NewSeq: %d\n", precvpriv->indicate_seq, seq_num); */

	/*  Drop out the packet which SeqNum is smaller than WinStart */
	अगर (SN_LESS(seq_num, preorder_ctrl->indicate_seq)) अणु
		/* DbgPrपूर्णांक("CheckRxTsIndicateSeq(): Packet Drop! IndicateSeq: %d, NewSeq: %d\n", precvpriv->indicate_seq, seq_num); */

		वापस false;
	पूर्ण

	/*  */
	/*  Sliding winकरोw manipulation. Conditions includes: */
	/*  1. Incoming SeqNum is equal to WinStart =>Winकरोw shअगरt 1 */
	/*  2. Incoming SeqNum is larger than the WinEnd => Winकरोw shअगरt N */
	/*  */
	अगर (SN_EQUAL(seq_num, preorder_ctrl->indicate_seq)) अणु
		preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1) & 0xFFF;

	पूर्ण अन्यथा अगर (SN_LESS(wend, seq_num)) अणु
		/* DbgPrपूर्णांक("CheckRxTsIndicateSeq(): Window Shift! IndicateSeq: %d, NewSeq: %d\n", precvpriv->indicate_seq, seq_num); */

		/*  boundary situation, when seq_num cross 0xFFF */
		अगर (seq_num >= (wsize - 1))
			preorder_ctrl->indicate_seq = seq_num + 1 - wsize;
		अन्यथा
			preorder_ctrl->indicate_seq = 0xFFF - (wsize - (seq_num + 1)) + 1;
		pdbgpriv->dbg_rx_ampdu_winकरोw_shअगरt_cnt++;
	पूर्ण

	/* DbgPrपूर्णांक("exit->check_indicate_seq(): IndicateSeq: %d, NewSeq: %d\n", precvpriv->indicate_seq, seq_num); */

	वापस true;
पूर्ण

अटल पूर्णांक enqueue_reorder_recvframe(काष्ठा recv_reorder_ctrl *preorder_ctrl, जोड़ recv_frame *prframe)
अणु
	काष्ठा rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	काष्ठा __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;
	काष्ठा list_head	*phead, *plist;
	जोड़ recv_frame *pnextrframe;
	काष्ठा rx_pkt_attrib *pnextattrib;

	/* DbgPrपूर्णांक("+enqueue_reorder_recvframe()\n"); */

	/* spin_lock_irqsave(&ppending_recvframe_queue->lock, irql); */
	/* spin_lock(&ppending_recvframe_queue->lock); */


	phead = get_list_head(ppending_recvframe_queue);
	plist = get_next(phead);

	जबतक (phead != plist) अणु
		pnextrframe = (जोड़ recv_frame *)plist;
		pnextattrib = &pnextrframe->u.hdr.attrib;

		अगर (SN_LESS(pnextattrib->seq_num, pattrib->seq_num))
			plist = get_next(plist);
		अन्यथा अगर (SN_EQUAL(pnextattrib->seq_num, pattrib->seq_num))
			/* Duplicate entry is found!! Do not insert current entry. */
			/* spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */
			वापस false;
		अन्यथा
			अवरोध;

		/* DbgPrपूर्णांक("enqueue_reorder_recvframe():while\n"); */

	पूर्ण


	/* spin_lock_irqsave(&ppending_recvframe_queue->lock, irql); */
	/* spin_lock(&ppending_recvframe_queue->lock); */

	list_del_init(&(prframe->u.hdr.list));

	list_add_tail(&(prframe->u.hdr.list), plist);

	/* spin_unlock(&ppending_recvframe_queue->lock); */
	/* spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */

	वापस true;

पूर्ण

अटल व्योम recv_indicatepkts_pkt_loss_cnt(काष्ठा debug_priv *pdbgpriv, u64 prev_seq, u64 current_seq)
अणु
	अगर (current_seq < prev_seq)
		pdbgpriv->dbg_rx_ampdu_loss_count += (4096 + current_seq - prev_seq);
	अन्यथा
		pdbgpriv->dbg_rx_ampdu_loss_count += (current_seq - prev_seq);

पूर्ण

अटल पूर्णांक recv_indicatepkts_in_order(काष्ठा adapter *padapter, काष्ठा recv_reorder_ctrl *preorder_ctrl, पूर्णांक bक्रमced)
अणु
	काष्ठा list_head	*phead, *plist;
	जोड़ recv_frame *prframe;
	काष्ठा rx_pkt_attrib *pattrib;
	/* u8 index = 0; */
	पूर्णांक bPktInBuf = false;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;
	काष्ठा __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;
	काष्ठा dvobj_priv *psdpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	/* DbgPrपूर्णांक("+recv_indicatepkts_in_order\n"); */

	/* spin_lock_irqsave(&ppending_recvframe_queue->lock, irql); */
	/* spin_lock(&ppending_recvframe_queue->lock); */

	phead =		get_list_head(ppending_recvframe_queue);
	plist = get_next(phead);

	/*  Handling some condition क्रम क्रमced indicate हाल. */
	अगर (bक्रमced == true) अणु
		pdbgpriv->dbg_rx_ampdu_क्रमced_indicate_count++;
		अगर (list_empty(phead)) अणु
			/*  spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */
			/* spin_unlock(&ppending_recvframe_queue->lock); */
			वापस true;
		पूर्ण

		prframe = (जोड़ recv_frame *)plist;
		pattrib = &prframe->u.hdr.attrib;

		recv_indicatepkts_pkt_loss_cnt(pdbgpriv, preorder_ctrl->indicate_seq, pattrib->seq_num);
		preorder_ctrl->indicate_seq = pattrib->seq_num;

	पूर्ण

	/*  Prepare indication list and indication. */
	/*  Check अगर there is any packet need indicate. */
	जबतक (!list_empty(phead)) अणु

		prframe = (जोड़ recv_frame *)plist;
		pattrib = &prframe->u.hdr.attrib;

		अगर (!SN_LESS(preorder_ctrl->indicate_seq, pattrib->seq_num)) अणु
			plist = get_next(plist);
			list_del_init(&(prframe->u.hdr.list));

			अगर (SN_EQUAL(preorder_ctrl->indicate_seq, pattrib->seq_num))
				preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1) & 0xFFF;

			/* Set this as a lock to make sure that only one thपढ़ो is indicating packet. */
			/* pTS->RxIndicateState = RXTS_INDICATE_PROCESSING; */

			/*  Indicate packets */
			/* RT_ASSERT((index<=REORDER_WIN_SIZE), ("RxReorderIndicatePacket(): Rx Reorder buffer full!!\n")); */


			/* indicate this recv_frame */
			/* DbgPrपूर्णांक("recv_indicatepkts_in_order, indicate_seq =%d, seq_num =%d\n", precvpriv->indicate_seq, pattrib->seq_num); */
			अगर (!pattrib->amsdu) अणु
				अगर ((padapter->bDriverStopped == false) &&
				    (padapter->bSurpriseRemoved == false))
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

		/* DbgPrपूर्णांक("recv_indicatepkts_in_order():while\n"); */

	पूर्ण

	/* spin_unlock(&ppending_recvframe_queue->lock); */
	/* spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */

	वापस bPktInBuf;
पूर्ण

अटल पूर्णांक recv_indicatepkt_reorder(काष्ठा adapter *padapter, जोड़ recv_frame *prframe)
अणु
	पूर्णांक retval = _SUCCESS;
	काष्ठा rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	काष्ठा recv_reorder_ctrl *preorder_ctrl = prframe->u.hdr.preorder_ctrl;
	काष्ठा __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;
	काष्ठा dvobj_priv *psdpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	अगर (!pattrib->amsdu) अणु
		/* s1. */
		wlanhdr_to_ethhdr(prframe);

		अगर (pattrib->qos != 1) अणु
			अगर ((padapter->bDriverStopped == false) &&
			    (padapter->bSurpriseRemoved == false)) अणु
				rtw_recv_indicatepkt(padapter, prframe);
				वापस _SUCCESS;

			पूर्ण

			वापस _FAIL;

		पूर्ण

		अगर (preorder_ctrl->enable == false) अणु
			/* indicate this recv_frame */
			preorder_ctrl->indicate_seq = pattrib->seq_num;

			rtw_recv_indicatepkt(padapter, prframe);

			preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1)%4096;

			वापस _SUCCESS;
		पूर्ण
	पूर्ण अन्यथा अगर (pattrib->amsdu == 1) अणु /* temp filter -> means didn't support A-MSDUs in a A-MPDU */
		अगर (preorder_ctrl->enable == false) अणु
			preorder_ctrl->indicate_seq = pattrib->seq_num;

			retval = amsdu_to_msdu(padapter, prframe);

			preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq + 1)%4096;

			अगर (retval != _SUCCESS) अणु
			पूर्ण

			वापस retval;
		पूर्ण
	पूर्ण

	spin_lock_bh(&ppending_recvframe_queue->lock);

	/* s2. check अगर winstart_b(indicate_seq) needs to been updated */
	अगर (!check_indicate_seq(preorder_ctrl, pattrib->seq_num)) अणु
		pdbgpriv->dbg_rx_ampdu_drop_count++;
		जाओ _err_निकास;
	पूर्ण


	/* s3. Insert all packet पूर्णांकo Reorder Queue to मुख्यtain its ordering. */
	अगर (!enqueue_reorder_recvframe(preorder_ctrl, prframe)) अणु
		/* DbgPrपूर्णांक("recv_indicatepkt_reorder, enqueue_reorder_recvframe fail!\n"); */
		/* spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql); */
		/* वापस _FAIL; */
		जाओ _err_निकास;
	पूर्ण


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
	अगर (recv_indicatepkts_in_order(padapter, preorder_ctrl, false) == true) अणु
		_set_समयr(&preorder_ctrl->reordering_ctrl_समयr, REORDER_WAIT_TIME);
		spin_unlock_bh(&ppending_recvframe_queue->lock);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&ppending_recvframe_queue->lock);
		del_समयr_sync(&preorder_ctrl->reordering_ctrl_समयr);
	पूर्ण

	वापस _SUCCESS;

_err_निकास:
	spin_unlock_bh(&ppending_recvframe_queue->lock);

	वापस _FAIL;
पूर्ण


व्योम rtw_reordering_ctrl_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा recv_reorder_ctrl *preorder_ctrl =
		from_समयr(preorder_ctrl, t, reordering_ctrl_समयr);
	काष्ठा adapter *padapter = preorder_ctrl->padapter;
	काष्ठा __queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;


	अगर (padapter->bDriverStopped || padapter->bSurpriseRemoved)
		वापस;

	spin_lock_bh(&ppending_recvframe_queue->lock);

	अगर (recv_indicatepkts_in_order(padapter, preorder_ctrl, true) == true)
		_set_समयr(&preorder_ctrl->reordering_ctrl_समयr, REORDER_WAIT_TIME);

	spin_unlock_bh(&ppending_recvframe_queue->lock);

पूर्ण

अटल पूर्णांक process_recv_indicatepkts(काष्ठा adapter *padapter, जोड़ recv_frame *prframe)
अणु
	पूर्णांक retval = _SUCCESS;
	/* काष्ठा recv_priv *precvpriv = &padapter->recvpriv; */
	/* काष्ठा rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib; */
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv *phtpriv = &pmlmepriv->htpriv;

	अगर (phtpriv->ht_option == true) अणु /* B/G/N Mode */
		/* prframe->u.hdr.preorder_ctrl = &precvpriv->recvreorder_ctrl[pattrib->priority]; */

		अगर (recv_indicatepkt_reorder(padapter, prframe) != _SUCCESS) अणु /*  including perक्रमm A-MPDU Rx Ordering Buffer Control */

			अगर ((padapter->bDriverStopped == false) &&
			    (padapter->bSurpriseRemoved == false)) अणु
				retval = _FAIL;
				वापस retval;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु /* B/G mode */
		retval = wlanhdr_to_ethhdr(prframe);
		अगर (retval != _SUCCESS)
			वापस retval;

		अगर ((padapter->bDriverStopped == false) && (padapter->bSurpriseRemoved == false)) अणु
			/* indicate this recv_frame */
			rtw_recv_indicatepkt(padapter, prframe);
		पूर्ण अन्यथा अणु
			retval = _FAIL;
			वापस retval;
		पूर्ण

	पूर्ण

	वापस retval;

पूर्ण

अटल पूर्णांक recv_func_prehandle(काष्ठा adapter *padapter, जोड़ recv_frame *rframe)
अणु
	पूर्णांक ret = _SUCCESS;
	काष्ठा __queue *pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;

	/* check the frame crtl field and decache */
	ret = validate_recv_frame(padapter, rframe);
	अगर (ret != _SUCCESS) अणु
		rtw_मुक्त_recvframe(rframe, pमुक्त_recv_queue);/* मुक्त this recv_frame */
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक recv_func_posthandle(काष्ठा adapter *padapter, जोड़ recv_frame *prframe)
अणु
	पूर्णांक ret = _SUCCESS;
	जोड़ recv_frame *orig_prframe = prframe;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;
	काष्ठा __queue *pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;

	prframe = decryptor(padapter, prframe);
	अगर (!prframe) अणु
		ret = _FAIL;
		जाओ _recv_data_drop;
	पूर्ण

	prframe = recvframe_chk_defrag(padapter, prframe);
	अगर (!prframe)
		जाओ _recv_data_drop;

	prframe = portctrl(padapter, prframe);
	अगर (!prframe) अणु
		ret = _FAIL;
		जाओ _recv_data_drop;
	पूर्ण

	count_rx_stats(padapter, prframe, शून्य);

	ret = process_recv_indicatepkts(padapter, prframe);
	अगर (ret != _SUCCESS) अणु
		rtw_मुक्त_recvframe(orig_prframe, pमुक्त_recv_queue);/* मुक्त this recv_frame */
		जाओ _recv_data_drop;
	पूर्ण

_recv_data_drop:
	precvpriv->rx_drop++;
	वापस ret;
पूर्ण

अटल पूर्णांक recv_func(काष्ठा adapter *padapter, जोड़ recv_frame *rframe)
अणु
	पूर्णांक ret;
	काष्ठा rx_pkt_attrib *prxattrib = &rframe->u.hdr.attrib;
	काष्ठा recv_priv *recvpriv = &padapter->recvpriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_priv *mlmepriv = &padapter->mlmepriv;

	/* check अगर need to handle uc_swdec_pending_queue*/
	अगर (check_fwstate(mlmepriv, WIFI_STATION_STATE) && psecuritypriv->busetkipkey) अणु
		जोड़ recv_frame *pending_frame;
		पूर्णांक cnt = 0;

		जबतक ((pending_frame = rtw_alloc_recvframe(&padapter->recvpriv.uc_swdec_pending_queue))) अणु
			cnt++;
			recv_func_posthandle(padapter, pending_frame);
		पूर्ण
	पूर्ण

	ret = recv_func_prehandle(padapter, rframe);

	अगर (ret == _SUCCESS) अणु

		/* check अगर need to enqueue पूर्णांकo uc_swdec_pending_queue*/
		अगर (check_fwstate(mlmepriv, WIFI_STATION_STATE) &&
			!IS_MCAST(prxattrib->ra) && prxattrib->encrypt > 0 &&
			(prxattrib->bdecrypted == 0 || psecuritypriv->sw_decrypt == true) &&
			psecuritypriv->ndisauthtype == Ndis802_11AuthModeWPAPSK &&
			!psecuritypriv->busetkipkey) अणु
			rtw_enqueue_recvframe(rframe, &padapter->recvpriv.uc_swdec_pending_queue);

			अगर (recvpriv->मुक्त_recvframe_cnt < NR_RECVFRAME/4) अणु
				/* to prevent from recvframe starvation, get recvframe from uc_swdec_pending_queue to मुक्त_recvframe_cnt  */
				rframe = rtw_alloc_recvframe(&padapter->recvpriv.uc_swdec_pending_queue);
				अगर (rframe)
					जाओ करो_posthandle;
			पूर्ण
			जाओ निकास;
		पूर्ण

करो_posthandle:
		ret = recv_func_posthandle(padapter, rframe);
	पूर्ण

निकास:
	वापस ret;
पूर्ण


s32 rtw_recv_entry(जोड़ recv_frame *precvframe)
अणु
	काष्ठा adapter *padapter;
	काष्ठा recv_priv *precvpriv;
	s32 ret = _SUCCESS;

	padapter = precvframe->u.hdr.adapter;

	precvpriv = &padapter->recvpriv;

	ret = recv_func(padapter, precvframe);
	अगर (ret == _FAIL) अणु
		जाओ _recv_entry_drop;
	पूर्ण


	precvpriv->rx_pkts++;

	वापस ret;

_recv_entry_drop:

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
	u32 num_संकेत_strength = 0;
	u32 num_संकेत_qual = 0;
	u8 _alpha = 5; /*  this value is based on converging_स्थिरant = 5000 and sampling_पूर्णांकerval = 1000 */

	अगर (adapter->recvpriv.is_संकेत_dbg) अणु
		/* update the user specअगरic value, संकेत_strength_dbg, to संकेत_strength, rssi */
		adapter->recvpriv.संकेत_strength = adapter->recvpriv.संकेत_strength_dbg;
		adapter->recvpriv.rssi = (s8)translate_percentage_to_dbm((u8)adapter->recvpriv.संकेत_strength_dbg);
	पूर्ण अन्यथा अणु

		अगर (recvpriv->संकेत_strength_data.update_req == 0) अणु/*  update_req is clear, means we got rx */
			avg_संकेत_strength = recvpriv->संकेत_strength_data.avg_val;
			num_संकेत_strength = recvpriv->संकेत_strength_data.total_num;
			/*  after avg_vals are acquired, we can re-stat the संकेत values */
			recvpriv->संकेत_strength_data.update_req = 1;
		पूर्ण

		अगर (recvpriv->संकेत_qual_data.update_req == 0) अणु/*  update_req is clear, means we got rx */
			avg_संकेत_qual = recvpriv->संकेत_qual_data.avg_val;
			num_संकेत_qual = recvpriv->संकेत_qual_data.total_num;
			/*  after avg_vals are acquired, we can re-stat the संकेत values */
			recvpriv->संकेत_qual_data.update_req = 1;
		पूर्ण

		अगर (num_संकेत_strength == 0) अणु
			अगर (rtw_get_on_cur_ch_समय(adapter) == 0 ||
			    jअगरfies_to_msecs(jअगरfies - rtw_get_on_cur_ch_समय(adapter)) < 2 * adapter->mlmeextpriv.mlmext_info.bcn_पूर्णांकerval
			) अणु
				जाओ set_समयr;
			पूर्ण
		पूर्ण

		अगर (check_fwstate(&adapter->mlmepriv, _FW_UNDER_SURVEY) == true ||
		    check_fwstate(&adapter->mlmepriv, _FW_LINKED) == false
		) अणु
			जाओ set_समयr;
		पूर्ण

		/* update value of संकेत_strength, rssi, संकेत_qual */
		पंचांगp_s = (avg_संकेत_strength+(_alpha-1)*recvpriv->संकेत_strength);
		अगर (पंचांगp_s % _alpha)
			पंचांगp_s = पंचांगp_s/_alpha + 1;
		अन्यथा
			पंचांगp_s = पंचांगp_s/_alpha;
		अगर (पंचांगp_s > 100)
			पंचांगp_s = 100;

		पंचांगp_q = (avg_संकेत_qual+(_alpha-1)*recvpriv->संकेत_qual);
		अगर (पंचांगp_q % _alpha)
			पंचांगp_q = पंचांगp_q/_alpha + 1;
		अन्यथा
			पंचांगp_q = पंचांगp_q/_alpha;
		अगर (पंचांगp_q > 100)
			पंचांगp_q = 100;

		recvpriv->संकेत_strength = पंचांगp_s;
		recvpriv->rssi = (s8)translate_percentage_to_dbm(पंचांगp_s);
		recvpriv->संकेत_qual = पंचांगp_q;
	पूर्ण

set_समयr:
	rtw_set_संकेत_stat_समयr(recvpriv);

पूर्ण
