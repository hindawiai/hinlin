<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_recv.c
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

#घोषणा _RTL871X_RECV_C_

#समावेश <linux/ip.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "recv_osdep.h"
#समावेश "mlme_osdep.h"
#समावेश "ethernet.h"
#समावेश "usb_ops.h"
#समावेश "wifi.h"

अटल स्थिर u8 SNAP_ETH_TYPE_IPX[2] = अणु0x81, 0x37पूर्ण;

/* Datagram Delivery Protocol */
अटल स्थिर u8 SNAP_ETH_TYPE_APPLETALK_AARP[2] = अणु0x80, 0xf3पूर्ण;

व्योम _r8712_init_sta_recv_priv(काष्ठा sta_recv_priv *psta_recvpriv)
अणु
	स_रखो((u8 *)psta_recvpriv, 0, माप(काष्ठा sta_recv_priv));
	spin_lock_init(&psta_recvpriv->lock);
	_init_queue(&psta_recvpriv->defrag_q);
पूर्ण

व्योम _r8712_init_recv_priv(काष्ठा recv_priv *precvpriv,
			   काष्ठा _adapter *padapter)
अणु
	sपूर्णांक i;
	जोड़ recv_frame *precvframe;

	स_रखो((अचिन्हित अक्षर *)precvpriv, 0, माप(काष्ठा  recv_priv));
	spin_lock_init(&precvpriv->lock);
	_init_queue(&precvpriv->मुक्त_recv_queue);
	_init_queue(&precvpriv->recv_pending_queue);
	precvpriv->adapter = padapter;
	precvpriv->मुक्त_recvframe_cnt = NR_RECVFRAME;
	precvpriv->pallocated_frame_buf = kzalloc(NR_RECVFRAME *
				माप(जोड़ recv_frame) + RXFRAME_ALIGN_SZ,
				GFP_ATOMIC);
	अगर (!precvpriv->pallocated_frame_buf)
		वापस;
	kmemleak_not_leak(precvpriv->pallocated_frame_buf);
	precvpriv->precv_frame_buf = precvpriv->pallocated_frame_buf +
				    RXFRAME_ALIGN_SZ -
				    ((addr_t)(precvpriv->pallocated_frame_buf) &
				    (RXFRAME_ALIGN_SZ - 1));
	precvframe = (जोड़ recv_frame *)precvpriv->precv_frame_buf;
	क्रम (i = 0; i < NR_RECVFRAME; i++) अणु
		INIT_LIST_HEAD(&(precvframe->u.list));
		list_add_tail(&(precvframe->u.list),
			      &(precvpriv->मुक्त_recv_queue.queue));
		r8712_os_recv_resource_alloc(padapter, precvframe);
		precvframe->u.hdr.adapter = padapter;
		precvframe++;
	पूर्ण
	precvpriv->rx_pending_cnt = 1;
	r8712_init_recv_priv(precvpriv, padapter);
पूर्ण

व्योम _r8712_मुक्त_recv_priv(काष्ठा recv_priv *precvpriv)
अणु
	kमुक्त(precvpriv->pallocated_frame_buf);
	r8712_मुक्त_recv_priv(precvpriv);
पूर्ण

जोड़ recv_frame *r8712_alloc_recvframe(काष्ठा __queue *pमुक्त_recv_queue)
अणु
	अचिन्हित दीर्घ irqL;
	जोड़ recv_frame  *precvframe;
	काष्ठा _adapter *padapter;
	काष्ठा recv_priv *precvpriv;

	spin_lock_irqsave(&pमुक्त_recv_queue->lock, irqL);
	precvframe = list_first_entry_or_null(&pमुक्त_recv_queue->queue,
					      जोड़ recv_frame, u.hdr.list);
	अगर (precvframe) अणु
		list_del_init(&precvframe->u.hdr.list);
		padapter = precvframe->u.hdr.adapter;
		अगर (padapter) अणु
			precvpriv = &padapter->recvpriv;
			अगर (pमुक्त_recv_queue == &precvpriv->मुक्त_recv_queue)
				precvpriv->मुक्त_recvframe_cnt--;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pमुक्त_recv_queue->lock, irqL);
	वापस precvframe;
पूर्ण

/*
 * caller : defrag; recvframe_chk_defrag in recv_thपढ़ो  (passive)
 * pframequeue: defrag_queue : will be accessed in recv_thपढ़ो  (passive)
 * using spin_lock to protect
 */
व्योम r8712_मुक्त_recvframe_queue(काष्ठा  __queue *pframequeue,
				काष्ठा  __queue *pमुक्त_recv_queue)
अणु
	जोड़	recv_frame *precvframe;
	काष्ठा list_head *plist, *phead;

	spin_lock(&pframequeue->lock);
	phead = &pframequeue->queue;
	plist = phead->next;
	जबतक (!end_of_queue_search(phead, plist)) अणु
		precvframe = container_of(plist, जोड़ recv_frame, u.list);
		plist = plist->next;
		r8712_मुक्त_recvframe(precvframe, pमुक्त_recv_queue);
	पूर्ण
	spin_unlock(&pframequeue->lock);
पूर्ण

sपूर्णांक r8712_recvframe_chkmic(काष्ठा _adapter *adapter,
			    जोड़ recv_frame *precvframe)
अणु
	sपूर्णांक i, res = _SUCCESS;
	u32	datalen;
	u8 miccode[8];
	u8 bmic_err = false;
	u8 *pframe, *payload, *pframemic;
	u8   *mickey, idx, *iv;
	काष्ठा	sta_info *stainfo;
	काष्ठा	rx_pkt_attrib *prxattrib = &precvframe->u.hdr.attrib;
	काष्ठा	security_priv *psecuritypriv = &adapter->securitypriv;

	stainfo = r8712_get_stainfo(&adapter->stapriv, &prxattrib->ta[0]);
	अगर (prxattrib->encrypt == _TKIP_) अणु
		/* calculate mic code */
		अगर (stainfo) अणु
			अगर (is_multicast_ether_addr(prxattrib->ra)) अणु
				iv = precvframe->u.hdr.rx_data +
				     prxattrib->hdrlen;
				idx = iv[3];
				mickey = &psecuritypriv->XGrprxmickey[(((idx >>
					 6) & 0x3)) - 1].skey[0];
				अगर (!psecuritypriv->binstallGrpkey)
					वापस _FAIL;
			पूर्ण अन्यथा अणु
				mickey = &stainfo->tkiprxmickey.skey[0];
			पूर्ण
			/*icv_len included the mic code*/
			datalen = precvframe->u.hdr.len - prxattrib->hdrlen -
				  prxattrib->iv_len - prxattrib->icv_len - 8;
			pframe = precvframe->u.hdr.rx_data;
			payload = pframe + prxattrib->hdrlen +
				  prxattrib->iv_len;
			seccalctkipmic(mickey, pframe, payload, datalen,
				       &miccode[0],
				       (अचिन्हित अक्षर)prxattrib->priority);
			pframemic = payload + datalen;
			bmic_err = false;
			क्रम (i = 0; i < 8; i++) अणु
				अगर (miccode[i] != *(pframemic + i))
					bmic_err = true;
			पूर्ण
			अगर (bmic_err) अणु
				अगर (prxattrib->bdecrypted)
					r8712_handle_tkip_mic_err(adapter,
								  (u8)is_multicast_ether_addr(prxattrib->ra));
				res = _FAIL;
			पूर्ण अन्यथा अणु
				/* mic checked ok */
				अगर (!psecuritypriv->bcheck_grpkey &&
				    is_multicast_ether_addr(prxattrib->ra))
					psecuritypriv->bcheck_grpkey = true;
			पूर्ण
			recvframe_pull_tail(precvframe, 8);
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

/* decrypt and set the ivlen,icvlen of the recv_frame */
जोड़ recv_frame *r8712_decryptor(काष्ठा _adapter *padapter,
				  जोड़ recv_frame *precv_frame)
अणु
	काष्ठा rx_pkt_attrib *prxattrib = &precv_frame->u.hdr.attrib;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	जोड़ recv_frame *वापस_packet = precv_frame;

	अगर ((prxattrib->encrypt > 0) && ((prxattrib->bdecrypted == 0) ||
					 psecuritypriv->sw_decrypt)) अणु
		psecuritypriv->hw_decrypted = false;
		चयन (prxattrib->encrypt) अणु
		हाल _WEP40_:
		हाल _WEP104_:
			r8712_wep_decrypt(padapter, (u8 *)precv_frame);
			अवरोध;
		हाल _TKIP_:
			r8712_tkip_decrypt(padapter, (u8 *)precv_frame);
			अवरोध;
		हाल _AES_:
			r8712_aes_decrypt(padapter, (u8 *)precv_frame);
			अवरोध;
		शेष:
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (prxattrib->bdecrypted == 1) अणु
		psecuritypriv->hw_decrypted = true;
	पूर्ण
	वापस वापस_packet;
पूर्ण

/*###set the security inक्रमmation in the recv_frame */
जोड़ recv_frame *r8712_portctrl(काष्ठा _adapter *adapter,
				 जोड़ recv_frame *precv_frame)
अणु
	u8 *psta_addr, *ptr;
	uपूर्णांक auth_alg;
	काष्ठा recv_frame_hdr *pfhdr;
	काष्ठा sta_info *psta;
	काष्ठा	sta_priv *pstapriv;
	जोड़ recv_frame *prtnframe;
	u16 ether_type;

	pstapriv = &adapter->stapriv;
	ptr = get_recvframe_data(precv_frame);
	pfhdr = &precv_frame->u.hdr;
	psta_addr = pfhdr->attrib.ta;
	psta = r8712_get_stainfo(pstapriv, psta_addr);
	auth_alg = adapter->securitypriv.AuthAlgrthm;
	अगर (auth_alg == 2) अणु
		/* get ether_type */
		ptr = ptr + pfhdr->attrib.hdrlen + LLC_HEADER_SIZE;
		ether_type = get_unaligned_be16(ptr);

		अगर (psta && psta->ieee8021x_blocked) अणु
			/* blocked
			 * only accept EAPOL frame
			 */
			अगर (ether_type == 0x888e) अणु
				prtnframe = precv_frame;
			पूर्ण अन्यथा अणु
				/*मुक्त this frame*/
				r8712_मुक्त_recvframe(precv_frame,
						     &adapter->recvpriv.मुक्त_recv_queue);
				prtnframe = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* allowed
			 * check decryption status, and decrypt the
			 * frame अगर needed
			 */
			prtnframe = precv_frame;
			/* check is the EAPOL frame or not (Rekey) */
			अगर (ether_type == 0x888e) अणु
				/* check Rekey */
				prtnframe = precv_frame;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		prtnframe = precv_frame;
	पूर्ण
	वापस prtnframe;
पूर्ण

अटल sपूर्णांक recv_decache(जोड़ recv_frame *precv_frame, u8 bretry,
			 काष्ठा stainfo_rxcache *prxcache)
अणु
	sपूर्णांक tid = precv_frame->u.hdr.attrib.priority;
	u16 seq_ctrl = ((precv_frame->u.hdr.attrib.seq_num & 0xffff) << 4) |
			(precv_frame->u.hdr.attrib.frag_num & 0xf);

	अगर (tid > 15)
		वापस _FAIL;
	अगर (seq_ctrl == prxcache->tid_rxseq[tid])
		वापस _FAIL;
	prxcache->tid_rxseq[tid] = seq_ctrl;
	वापस _SUCCESS;
पूर्ण

अटल sपूर्णांक sta2sta_data_frame(काष्ठा _adapter *adapter,
			       जोड़ recv_frame *precv_frame,
			       काष्ठा sta_info **psta)
अणु
	u8 *ptr = precv_frame->u.hdr.rx_data;
	sपूर्णांक ret = _SUCCESS;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा	sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *mybssid  = get_bssid(pmlmepriv);
	u8 *myhwaddr = myid(&adapter->eeprompriv);
	u8 *sta_addr = शून्य;
	bool bmcast = is_multicast_ether_addr(pattrib->dst);

	अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) ||
	    check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
		/* filter packets that SA is myself or multicast or broadcast */
		अगर (!स_भेद(myhwaddr, pattrib->src, ETH_ALEN))
			वापस _FAIL;
		अगर ((स_भेद(myhwaddr, pattrib->dst, ETH_ALEN)) && (!bmcast))
			वापस _FAIL;
		अगर (is_zero_ether_addr(pattrib->bssid) ||
		    is_zero_ether_addr(mybssid) ||
		    (स_भेद(pattrib->bssid, mybssid, ETH_ALEN)))
			वापस _FAIL;
		sta_addr = pattrib->src;
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) अणु
		/* For Station mode, sa and bssid should always be BSSID,
		 * and DA is my mac-address
		 */
		अगर (स_भेद(pattrib->bssid, pattrib->src, ETH_ALEN))
			वापस _FAIL;
		sta_addr = pattrib->bssid;
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		अगर (bmcast) अणु
			/* For AP mode, अगर DA == MCAST, then BSSID should
			 * be also MCAST
			 */
			अगर (!is_multicast_ether_addr(pattrib->bssid))
				वापस _FAIL;
		पूर्ण अन्यथा अणु /* not mc-frame */
			/* For AP mode, अगर DA is non-MCAST, then it must be
			 * BSSID, and bssid == BSSID
			 */
			अगर (स_भेद(pattrib->bssid, pattrib->dst, ETH_ALEN))
				वापस _FAIL;
			sta_addr = pattrib->src;
		पूर्ण
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE)) अणु
		स_नकल(pattrib->dst, GetAddr1Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->src, GetAddr2Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->bssid, GetAddr3Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->ra, pattrib->dst, ETH_ALEN);
		स_नकल(pattrib->ta, pattrib->src, ETH_ALEN);
		sta_addr = mybssid;
	पूर्ण अन्यथा अणु
		ret  = _FAIL;
	पूर्ण
	अगर (bmcast)
		*psta = r8712_get_bcmc_stainfo(adapter);
	अन्यथा
		*psta = r8712_get_stainfo(pstapriv, sta_addr); /* get ap_info */
	अगर (!*psta) अणु
		अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE))
			adapter->mppriv.rx_pktloss++;
		वापस _FAIL;
	पूर्ण
	वापस ret;
पूर्ण

अटल sपूर्णांक ap2sta_data_frame(काष्ठा _adapter *adapter,
			      जोड़ recv_frame *precv_frame,
			      काष्ठा sta_info **psta)
अणु
	u8 *ptr = precv_frame->u.hdr.rx_data;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा	sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	u8 *mybssid  = get_bssid(pmlmepriv);
	u8 *myhwaddr = myid(&adapter->eeprompriv);
	bool bmcast = is_multicast_ether_addr(pattrib->dst);

	अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) &&
	    check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		/* अगर शून्य-frame, drop packet */
		अगर ((GetFrameSubType(ptr)) == IEEE80211_STYPE_शून्यFUNC)
			वापस _FAIL;
		/* drop QoS-SubType Data, including QoS शून्य,
		 * excluding QoS-Data
		 */
		अगर ((GetFrameSubType(ptr) & WIFI_QOS_DATA_TYPE) ==
		     WIFI_QOS_DATA_TYPE) अणु
			अगर (GetFrameSubType(ptr) & (BIT(4) | BIT(5) | BIT(6)))
				वापस _FAIL;
		पूर्ण

		/* filter packets that SA is myself or multicast or broadcast */
		अगर (!स_भेद(myhwaddr, pattrib->src, ETH_ALEN))
			वापस _FAIL;

		/* da should be क्रम me */
		अगर ((स_भेद(myhwaddr, pattrib->dst, ETH_ALEN)) && (!bmcast))
			वापस _FAIL;
		/* check BSSID */
		अगर (is_zero_ether_addr(pattrib->bssid) ||
		    is_zero_ether_addr(mybssid) ||
		     (स_भेद(pattrib->bssid, mybssid, ETH_ALEN)))
			वापस _FAIL;
		अगर (bmcast)
			*psta = r8712_get_bcmc_stainfo(adapter);
		अन्यथा
			*psta = r8712_get_stainfo(pstapriv, pattrib->bssid);
		अगर (!*psta)
			वापस _FAIL;
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE) &&
		   check_fwstate(pmlmepriv, _FW_LINKED)) अणु
		स_नकल(pattrib->dst, GetAddr1Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->src, GetAddr2Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->bssid, GetAddr3Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->ra, pattrib->dst, ETH_ALEN);
		स_नकल(pattrib->ta, pattrib->src, ETH_ALEN);
		स_नकल(pattrib->bssid,  mybssid, ETH_ALEN);
		*psta = r8712_get_stainfo(pstapriv, pattrib->bssid);
		अगर (!*psta)
			वापस _FAIL;
	पूर्ण अन्यथा अणु
		वापस _FAIL;
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अटल sपूर्णांक sta2ap_data_frame(काष्ठा _adapter *adapter,
			      जोड़ recv_frame *precv_frame,
			      काष्ठा sta_info **psta)
अणु
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा	sta_priv *pstapriv = &adapter->stapriv;
	काष्ठा	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	अचिन्हित अक्षर *mybssid  = get_bssid(pmlmepriv);

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		/* For AP mode, अगर DA is non-MCAST, then it must be BSSID,
		 * and bssid == BSSID
		 * For AP mode, RA=BSSID, TX=STA(SRC_ADDR), A3=DST_ADDR
		 */
		अगर (स_भेद(pattrib->bssid, mybssid, ETH_ALEN))
			वापस _FAIL;
		*psta = r8712_get_stainfo(pstapriv, pattrib->src);
		अगर (!*psta)
			वापस _FAIL;
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अटल sपूर्णांक validate_recv_ctrl_frame(काष्ठा _adapter *adapter,
				     जोड़ recv_frame *precv_frame)
अणु
	वापस _FAIL;
पूर्ण

अटल sपूर्णांक validate_recv_mgnt_frame(काष्ठा _adapter *adapter,
				     जोड़ recv_frame *precv_frame)
अणु
	वापस _FAIL;
पूर्ण


अटल sपूर्णांक validate_recv_data_frame(काष्ठा _adapter *adapter,
				     जोड़ recv_frame *precv_frame)
अणु
	पूर्णांक res;
	u8 bretry;
	u8 *psa, *pda, *pbssid;
	काष्ठा sta_info *psta = शून्य;
	u8 *ptr = precv_frame->u.hdr.rx_data;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	काष्ठा security_priv *psecuritypriv = &adapter->securitypriv;

	bretry = GetRetry(ptr);
	pda = ieee80211_get_DA((काष्ठा ieee80211_hdr *)ptr);
	psa = ieee80211_get_SA((काष्ठा ieee80211_hdr *)ptr);
	pbssid = get_hdr_bssid(ptr);
	अगर (!pbssid)
		वापस _FAIL;
	स_नकल(pattrib->dst, pda, ETH_ALEN);
	स_नकल(pattrib->src, psa, ETH_ALEN);
	स_नकल(pattrib->bssid, pbssid, ETH_ALEN);
	चयन (pattrib->to_fr_ds) अणु
	हाल 0:
		स_नकल(pattrib->ra, pda, ETH_ALEN);
		स_नकल(pattrib->ta, psa, ETH_ALEN);
		res = sta2sta_data_frame(adapter, precv_frame, &psta);
		अवरोध;
	हाल 1:
		स_नकल(pattrib->ra, pda, ETH_ALEN);
		स_नकल(pattrib->ta, pbssid, ETH_ALEN);
		res = ap2sta_data_frame(adapter, precv_frame, &psta);
		अवरोध;
	हाल 2:
		स_नकल(pattrib->ra, pbssid, ETH_ALEN);
		स_नकल(pattrib->ta, psa, ETH_ALEN);
		res = sta2ap_data_frame(adapter, precv_frame, &psta);
		अवरोध;
	हाल 3:
		स_नकल(pattrib->ra, GetAddr1Ptr(ptr), ETH_ALEN);
		स_नकल(pattrib->ta, GetAddr2Ptr(ptr), ETH_ALEN);
		वापस _FAIL;
	शेष:
		वापस _FAIL;
	पूर्ण
	अगर (res == _FAIL)
		वापस _FAIL;
	अगर (!psta)
		वापस _FAIL;
	precv_frame->u.hdr.psta = psta;
	pattrib->amsdu = 0;
	/* parsing QC field */
	अगर (pattrib->qos == 1) अणु
		pattrib->priority = GetPriority((ptr + 24));
		pattrib->ack_policy = GetAckpolicy((ptr + 24));
		pattrib->amsdu = GetAMsdu((ptr + 24));
		pattrib->hdrlen = pattrib->to_fr_ds == 3 ? 32 : 26;
	पूर्ण अन्यथा अणु
		pattrib->priority = 0;
		pattrib->hdrlen = (pattrib->to_fr_ds == 3) ? 30 : 24;
	पूर्ण

	अगर (pattrib->order)/*HT-CTRL 11n*/
		pattrib->hdrlen += 4;
	precv_frame->u.hdr.preorder_ctrl =
			 &psta->recvreorder_ctrl[pattrib->priority];

	/* decache, drop duplicate recv packets */
	अगर (recv_decache(precv_frame, bretry, &psta->sta_recvpriv.rxcache) ==
	    _FAIL)
		वापस _FAIL;

	अगर (pattrib->privacy) अणु
		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt,
			       is_multicast_ether_addr(pattrib->ra));
		SET_ICE_IV_LEN(pattrib->iv_len, pattrib->icv_len,
			       pattrib->encrypt);
	पूर्ण अन्यथा अणु
		pattrib->encrypt = 0;
		pattrib->iv_len = pattrib->icv_len = 0;
	पूर्ण
	वापस _SUCCESS;
पूर्ण

sपूर्णांक r8712_validate_recv_frame(काष्ठा _adapter *adapter,
			       जोड़ recv_frame *precv_frame)
अणु
	/*shall check frame subtype, to / from ds, da, bssid */
	/*then call check अगर rx seq/frag. duplicated.*/

	u8 type;
	u8 subtype;
	sपूर्णांक retval = _SUCCESS;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;

	u8 *ptr = precv_frame->u.hdr.rx_data;
	u8  ver = (अचिन्हित अक्षर)(*ptr) & 0x3;

	/*add version chk*/
	अगर (ver != 0)
		वापस _FAIL;
	type =  GetFrameType(ptr);
	subtype = GetFrameSubType(ptr); /*bit(7)~bit(2)*/
	pattrib->to_fr_ds = get_tofr_ds(ptr);
	pattrib->frag_num = GetFragNum(ptr);
	pattrib->seq_num = GetSequence(ptr);
	pattrib->pw_save = GetPwrMgt(ptr);
	pattrib->mfrag = GetMFrag(ptr);
	pattrib->mdata = GetMData(ptr);
	pattrib->privacy =  GetPrivacy(ptr);
	pattrib->order = GetOrder(ptr);
	चयन (type) अणु
	हाल IEEE80211_FTYPE_MGMT:
		retval = validate_recv_mgnt_frame(adapter, precv_frame);
		अवरोध;
	हाल IEEE80211_FTYPE_CTL:
		retval = validate_recv_ctrl_frame(adapter, precv_frame);
		अवरोध;
	हाल IEEE80211_FTYPE_DATA:
		pattrib->qos = (subtype & BIT(7)) ? 1 : 0;
		retval = validate_recv_data_frame(adapter, precv_frame);
		अवरोध;
	शेष:
		वापस _FAIL;
	पूर्ण
	वापस retval;
पूर्ण

पूर्णांक r8712_wlanhdr_to_ethhdr(जोड़ recv_frame *precvframe)
अणु
	/*हटाओ the wlanhdr and add the eth_hdr*/
	sपूर्णांक	rmv_len;
	u16	len;
	u8	bsnaphdr;
	u8	*psnap_type;
	काष्ठा ieee80211_snap_hdr *psnap;
	काष्ठा _adapter	*adapter = precvframe->u.hdr.adapter;
	काष्ठा mlme_priv *pmlmepriv = &adapter->mlmepriv;

	u8 *ptr = get_recvframe_data(precvframe); /*poपूर्णांक to frame_ctrl field*/
	काष्ठा rx_pkt_attrib *pattrib = &precvframe->u.hdr.attrib;

	अगर (pattrib->encrypt)
		recvframe_pull_tail(precvframe, pattrib->icv_len);
	psnap = (काष्ठा ieee80211_snap_hdr *)(ptr + pattrib->hdrlen +
		 pattrib->iv_len);
	psnap_type = ptr + pattrib->hdrlen + pattrib->iv_len + SNAP_SIZE;
	/* convert hdr + possible LLC headers पूर्णांकo Ethernet header */
	अगर ((!स_भेद(psnap, (व्योम *)rfc1042_header, SNAP_SIZE) &&
	     (स_भेद(psnap_type, (व्योम *)SNAP_ETH_TYPE_IPX, 2)) &&
	    (स_भेद(psnap_type, (व्योम *)SNAP_ETH_TYPE_APPLETALK_AARP, 2))) ||
	     !स_भेद(psnap, (व्योम *)bridge_tunnel_header, SNAP_SIZE)) अणु
		/* हटाओ RFC1042 or Bridge-Tunnel encapsulation and
		 * replace EtherType
		 */
		bsnaphdr = true;
	पूर्ण अन्यथा अणु
		/* Leave Ethernet header part of hdr and full payload */
		bsnaphdr = false;
	पूर्ण
	rmv_len = pattrib->hdrlen + pattrib->iv_len +
		  (bsnaphdr ? SNAP_SIZE : 0);
	len = precvframe->u.hdr.len - rmv_len;
	अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE)) अणु
		ptr += rmv_len;
		*ptr = 0x87;
		*(ptr + 1) = 0x12;
		/* append rx status क्रम mp test packets */
		ptr = recvframe_pull(precvframe, (rmv_len -
		      माप(काष्ठा ethhdr) + 2) - 24);
		अगर (!ptr)
			वापस -ENOMEM;
		स_नकल(ptr, get_rxmem(precvframe), 24);
		ptr += 24;
	पूर्ण अन्यथा अणु
		ptr = recvframe_pull(precvframe, (rmv_len -
		      माप(काष्ठा ethhdr) + (bsnaphdr ? 2 : 0)));
		अगर (!ptr)
			वापस -ENOMEM;
	पूर्ण

	स_नकल(ptr, pattrib->dst, ETH_ALEN);
	स_नकल(ptr + ETH_ALEN, pattrib->src, ETH_ALEN);
	अगर (!bsnaphdr) अणु
		__be16 be_पंचांगp = htons(len);

		स_नकल(ptr + 12, &be_पंचांगp, 2);
	पूर्ण
	वापस 0;
पूर्ण

व्योम r8712_recv_entry(जोड़ recv_frame *precvframe)
अणु
	काष्ठा _adapter *padapter;
	काष्ठा recv_priv *precvpriv;

	s32 ret = _SUCCESS;

	padapter = precvframe->u.hdr.adapter;
	precvpriv = &(padapter->recvpriv);

	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_RX);

	ret = recv_func(padapter, precvframe);
	अगर (ret == _FAIL)
		जाओ _recv_entry_drop;
	precvpriv->rx_pkts++;
	precvpriv->rx_bytes += (uपूर्णांक)(precvframe->u.hdr.rx_tail -
				precvframe->u.hdr.rx_data);
	वापस;
_recv_entry_drop:
	precvpriv->rx_drop++;
	padapter->mppriv.rx_pktloss = precvpriv->rx_drop;
पूर्ण
