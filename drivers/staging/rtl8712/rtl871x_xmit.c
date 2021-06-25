<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl871x_xmit.c
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

#घोषणा _RTL871X_XMIT_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "osdep_intf.h"
#समावेश "usb_ops.h"

#समावेश <linux/ieee80211.h>

अटल स्थिर u8 P802_1H_OUI[P80211_OUI_LEN] = अणु0x00, 0x00, 0xf8पूर्ण;
अटल स्थिर u8 RFC1042_OUI[P80211_OUI_LEN] = अणु0x00, 0x00, 0x00पूर्ण;
अटल व्योम init_hwxmits(काष्ठा hw_xmit *phwxmit, sपूर्णांक entry);
अटल व्योम alloc_hwxmits(काष्ठा _adapter *padapter);
अटल व्योम मुक्त_hwxmits(काष्ठा _adapter *padapter);

अटल व्योम _init_txservq(काष्ठा tx_servq *ptxservq)
अणु
	INIT_LIST_HEAD(&ptxservq->tx_pending);
	_init_queue(&ptxservq->sta_pending);
	ptxservq->qcnt = 0;
पूर्ण

व्योम _r8712_init_sta_xmit_priv(काष्ठा sta_xmit_priv *psta_xmitpriv)
अणु
	स_रखो((अचिन्हित अक्षर *)psta_xmitpriv, 0,
		 माप(काष्ठा sta_xmit_priv));
	spin_lock_init(&psta_xmitpriv->lock);
	_init_txservq(&psta_xmitpriv->be_q);
	_init_txservq(&psta_xmitpriv->bk_q);
	_init_txservq(&psta_xmitpriv->vi_q);
	_init_txservq(&psta_xmitpriv->vo_q);
	INIT_LIST_HEAD(&psta_xmitpriv->legacy_dz);
	INIT_LIST_HEAD(&psta_xmitpriv->apsd);
पूर्ण

पूर्णांक _r8712_init_xmit_priv(काष्ठा xmit_priv *pxmitpriv,
			  काष्ठा _adapter *padapter)
अणु
	sपूर्णांक i;
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा xmit_frame *pxframe;

	स_रखो((अचिन्हित अक्षर *)pxmitpriv, 0, माप(काष्ठा xmit_priv));
	spin_lock_init(&pxmitpriv->lock);
	/*
	 *Please insert all the queue initialization using _init_queue below
	 */
	pxmitpriv->adapter = padapter;
	_init_queue(&pxmitpriv->be_pending);
	_init_queue(&pxmitpriv->bk_pending);
	_init_queue(&pxmitpriv->vi_pending);
	_init_queue(&pxmitpriv->vo_pending);
	_init_queue(&pxmitpriv->bm_pending);
	_init_queue(&pxmitpriv->legacy_dz_queue);
	_init_queue(&pxmitpriv->apsd_queue);
	_init_queue(&pxmitpriv->मुक्त_xmit_queue);
	/*
	 * Please allocate memory with sz = (काष्ठा xmit_frame) * NR_XMITFRAME,
	 * and initialize मुक्त_xmit_frame below.
	 * Please also apply  मुक्त_txobj to link_up all the xmit_frames...
	 */
	pxmitpriv->pallocated_frame_buf =
		kदो_स्मृति(NR_XMITFRAME * माप(काष्ठा xmit_frame) + 4,
			GFP_ATOMIC);
	अगर (!pxmitpriv->pallocated_frame_buf) अणु
		pxmitpriv->pxmit_frame_buf = शून्य;
		वापस -ENOMEM;
	पूर्ण
	pxmitpriv->pxmit_frame_buf = pxmitpriv->pallocated_frame_buf + 4 -
			((addr_t) (pxmitpriv->pallocated_frame_buf) & 3);
	pxframe = (काष्ठा xmit_frame *) pxmitpriv->pxmit_frame_buf;
	क्रम (i = 0; i < NR_XMITFRAME; i++) अणु
		INIT_LIST_HEAD(&(pxframe->list));
		pxframe->padapter = padapter;
		pxframe->frame_tag = DATA_FRAMETAG;
		pxframe->pkt = शून्य;
		pxframe->buf_addr = शून्य;
		pxframe->pxmitbuf = शून्य;
		list_add_tail(&(pxframe->list),
				 &(pxmitpriv->मुक्त_xmit_queue.queue));
		pxframe++;
	पूर्ण
	pxmitpriv->मुक्त_xmitframe_cnt = NR_XMITFRAME;
	/*
	 * init xmit hw_txqueue
	 */
	_r8712_init_hw_txqueue(&pxmitpriv->be_txqueue, BE_QUEUE_INX);
	_r8712_init_hw_txqueue(&pxmitpriv->bk_txqueue, BK_QUEUE_INX);
	_r8712_init_hw_txqueue(&pxmitpriv->vi_txqueue, VI_QUEUE_INX);
	_r8712_init_hw_txqueue(&pxmitpriv->vo_txqueue, VO_QUEUE_INX);
	_r8712_init_hw_txqueue(&pxmitpriv->bmc_txqueue, BMC_QUEUE_INX);
	pxmitpriv->frag_len = MAX_FRAG_THRESHOLD;
	pxmitpriv->txirp_cnt = 1;
	/*per AC pending irp*/
	pxmitpriv->beq_cnt = 0;
	pxmitpriv->bkq_cnt = 0;
	pxmitpriv->viq_cnt = 0;
	pxmitpriv->voq_cnt = 0;
	/*init xmit_buf*/
	_init_queue(&pxmitpriv->मुक्त_xmitbuf_queue);
	_init_queue(&pxmitpriv->pending_xmitbuf_queue);
	pxmitpriv->pallocated_xmitbuf =
		kदो_स्मृति(NR_XMITBUFF * माप(काष्ठा xmit_buf) + 4, GFP_ATOMIC);
	अगर (!pxmitpriv->pallocated_xmitbuf) अणु
		kमुक्त(pxmitpriv->pallocated_frame_buf);
		pxmitpriv->pallocated_frame_buf = शून्य;
		वापस -ENOMEM;
	पूर्ण
	pxmitpriv->pxmitbuf = pxmitpriv->pallocated_xmitbuf + 4 -
			      ((addr_t)(pxmitpriv->pallocated_xmitbuf) & 3);
	pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmitbuf;
	क्रम (i = 0; i < NR_XMITBUFF; i++) अणु
		INIT_LIST_HEAD(&pxmitbuf->list);
		pxmitbuf->pallocated_buf =
			kदो_स्मृति(MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ, GFP_ATOMIC);
		अगर (!pxmitbuf->pallocated_buf)
			वापस -ENOMEM;
		pxmitbuf->pbuf = pxmitbuf->pallocated_buf + XMITBUF_ALIGN_SZ -
				 ((addr_t) (pxmitbuf->pallocated_buf) &
				 (XMITBUF_ALIGN_SZ - 1));
		अगर (r8712_xmit_resource_alloc(padapter, pxmitbuf))
			वापस -ENOMEM;
		list_add_tail(&pxmitbuf->list,
				 &(pxmitpriv->मुक्त_xmitbuf_queue.queue));
		pxmitbuf++;
	पूर्ण
	pxmitpriv->मुक्त_xmitbuf_cnt = NR_XMITBUFF;
	INIT_WORK(&padapter->wk_filter_rx_ff0, r8712_SetFilter);
	alloc_hwxmits(padapter);
	init_hwxmits(pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);
	tasklet_setup(&pxmitpriv->xmit_tasklet, r8712_xmit_bh);
	वापस 0;
पूर्ण

व्योम _मुक्त_xmit_priv(काष्ठा xmit_priv *pxmitpriv)
अणु
	पूर्णांक i;
	काष्ठा _adapter *padapter = pxmitpriv->adapter;
	काष्ठा xmit_frame *pxmitframe = (काष्ठा xmit_frame *)
					pxmitpriv->pxmit_frame_buf;
	काष्ठा xmit_buf *pxmitbuf = (काष्ठा xmit_buf *)pxmitpriv->pxmitbuf;

	अगर (!pxmitpriv->pxmit_frame_buf)
		वापस;
	क्रम (i = 0; i < NR_XMITFRAME; i++) अणु
		r8712_xmit_complete(padapter, pxmitframe);
		pxmitframe++;
	पूर्ण
	क्रम (i = 0; i < NR_XMITBUFF; i++) अणु
		r8712_xmit_resource_मुक्त(padapter, pxmitbuf);
		kमुक्त(pxmitbuf->pallocated_buf);
		pxmitbuf++;
	पूर्ण
	kमुक्त(pxmitpriv->pallocated_frame_buf);
	kमुक्त(pxmitpriv->pallocated_xmitbuf);
	मुक्त_hwxmits(padapter);
पूर्ण

पूर्णांक r8712_update_attrib(काष्ठा _adapter *padapter, _pkt *pkt,
			काष्ठा pkt_attrib *pattrib)
अणु
	काष्ठा pkt_file pktfile;
	काष्ठा sta_info *psta = शून्य;
	काष्ठा ethhdr etherhdr;

	काष्ठा tx_cmd txdesc;

	bool bmcast;
	काष्ठा sta_priv		*pstapriv = &padapter->stapriv;
	काष्ठा security_priv	*psecuritypriv = &padapter->securitypriv;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv		*pqospriv = &pmlmepriv->qospriv;

	_r8712_खोलो_pktfile(pkt, &pktfile);

	_r8712_pktfile_पढ़ो(&pktfile, (अचिन्हित अक्षर *)&etherhdr, ETH_HLEN);

	pattrib->ether_type = ntohs(etherhdr.h_proto);

	/*
	 * If driver xmit ARP packet, driver can set ps mode to initial
	 * setting. It stands क्रम getting DHCP or fix IP.
	 */
	अगर (pattrib->ether_type == 0x0806) अणु
		अगर (padapter->pwrctrlpriv.pwr_mode !=
		    padapter->registrypriv.घातer_mgnt) अणु
			del_समयr_sync(&pmlmepriv->dhcp_समयr);
			r8712_set_ps_mode(padapter,
					  padapter->registrypriv.घातer_mgnt,
					  padapter->registrypriv.smart_ps);
		पूर्ण
	पूर्ण

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
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE)) अणु
		/*firstly, filter packet not beदीर्घs to mp*/
		अगर (pattrib->ether_type != 0x8712)
			वापस -EINVAL;
		/* क्रम mp storing the txcmd per packet,
		 * according to the info of txcmd to update pattrib
		 */
		/*get MP_TXDESC_SIZE bytes txcmd per packet*/
		_r8712_pktfile_पढ़ो(&pktfile, (u8 *)&txdesc, TXDESC_SIZE);
		स_नकल(pattrib->ra, pattrib->dst, ETH_ALEN);
		स_नकल(pattrib->ta, pattrib->src, ETH_ALEN);
		pattrib->pctrl = 1;
	पूर्ण
	/* r8712_xmitframe_coalesce() overग_लिखो this!*/
	pattrib->pktlen = pktfile.pkt_len;
	अगर (pattrib->ether_type == ETH_P_IP) अणु
		/* The following is क्रम DHCP and ARP packet, we use cck1M to
		 * tx these packets and let LPS awake some समय
		 * to prevent DHCP protocol fail
		 */
		u8 पंचांगp[24];

		_r8712_pktfile_पढ़ो(&pktfile, &पंचांगp[0], 24);
		pattrib->dhcp_pkt = 0;
		अगर (pktfile.pkt_len > 282) अणु/*MINIMUM_DHCP_PACKET_SIZE)*/
			अगर (pattrib->ether_type == ETH_P_IP) अणु/* IP header*/
				अगर (((पंचांगp[21] == 68) && (पंचांगp[23] == 67)) ||
					((पंचांगp[21] == 67) && (पंचांगp[23] == 68))) अणु
					/* 68 : UDP BOOTP client
					 * 67 : UDP BOOTP server
					 * Use low rate to send DHCP packet.
					 */
					pattrib->dhcp_pkt = 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	bmcast = is_multicast_ether_addr(pattrib->ra);
	/* get sta_info*/
	अगर (bmcast) अणु
		psta = r8712_get_bcmc_stainfo(padapter);
		pattrib->mac_id = 4;
	पूर्ण अन्यथा अणु
		अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE)) अणु
			psta = r8712_get_stainfo(pstapriv,
						 get_bssid(pmlmepriv));
			pattrib->mac_id = 5;
		पूर्ण अन्यथा अणु
			psta = r8712_get_stainfo(pstapriv, pattrib->ra);
			अगर (!psta)  /* drop the pkt */
				वापस -ENOMEM;
			अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
				pattrib->mac_id = 5;
			अन्यथा
				pattrib->mac_id = psta->mac_id;
		पूर्ण
	पूर्ण

	अगर (psta) अणु
		pattrib->psta = psta;
	पूर्ण अन्यथा अणु
		/* अगर we cannot get psta => drrp the pkt */
		वापस -ENOMEM;
	पूर्ण

	pattrib->ack_policy = 0;
	/* get ether_hdr_len */
	pattrib->pkt_hdrlen = ETH_HLEN;

	अगर (pqospriv->qos_option) अणु
		r8712_set_qos(&pktfile, pattrib);
	पूर्ण अन्यथा अणु
		pattrib->hdrlen = WLAN_HDR_A3_LEN;
		pattrib->subtype = IEEE80211_FTYPE_DATA;
		pattrib->priority = 0;
	पूर्ण
	अगर (psta->ieee8021x_blocked) अणु
		pattrib->encrypt = 0;
		अगर ((pattrib->ether_type != 0x888e) &&
		    !check_fwstate(pmlmepriv, WIFI_MP_STATE))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt, bmcast);
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
		अगर (padapter->securitypriv.busetkipkey == _FAIL)
			वापस -EINVAL;
		अवरोध;
	हाल _AES_:
		pattrib->iv_len = 8;
		pattrib->icv_len = 8;
		अवरोध;
	शेष:
		pattrib->iv_len = 0;
		pattrib->icv_len = 0;
		अवरोध;
	पूर्ण

	अगर (pattrib->encrypt &&
	    (padapter->securitypriv.sw_encrypt ||
	    !psecuritypriv->hw_decrypted))
		pattrib->bswenc = true;
	अन्यथा
		pattrib->bswenc = false;
	/* अगर in MP_STATE, update pkt_attrib from mp_txcmd, and overग_लिखो
	 * some settings above.
	 */
	अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE))
		pattrib->priority =
		    (le32_to_cpu(txdesc.txdw1) >> QSEL_SHT) & 0x1f;
	वापस 0;
पूर्ण

अटल पूर्णांक xmitframe_addmic(काष्ठा _adapter *padapter,
			    काष्ठा xmit_frame *pxmitframe)
अणु
	u32	curfragnum, length;
	u8	*pframe, *payload, mic[8];
	काष्ठा	mic_data micdata;
	काष्ठा	sta_info *stainfo;
	काष्ठा	qos_priv *pqospriv = &(padapter->mlmepriv.qospriv);
	काष्ठा	pkt_attrib  *pattrib = &pxmitframe->attrib;
	काष्ठा	security_priv *psecpriv = &padapter->securitypriv;
	काष्ठा	xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u8 priority[4] = अणुपूर्ण;
	bool bmcst = is_multicast_ether_addr(pattrib->ra);

	अगर (pattrib->psta)
		stainfo = pattrib->psta;
	अन्यथा
		stainfo = r8712_get_stainfo(&padapter->stapriv,
					    &pattrib->ra[0]);
	अगर (pattrib->encrypt == _TKIP_) अणु
		/*encode mic code*/
		अगर (stainfo) अणु
			u8 null_key[16] = अणुपूर्ण;

			pframe = pxmitframe->buf_addr + TXDESC_OFFSET;
			अगर (bmcst) अणु
				अगर (!स_भेद(psecpriv->XGrptxmickey
				   [psecpriv->XGrpKeyid].skey,
				   null_key, 16))
					वापस -ENOMEM;
				/*start to calculate the mic code*/
				r8712_secmicsetkey(&micdata,
					psecpriv->XGrptxmickey
					[psecpriv->XGrpKeyid].skey);
			पूर्ण अन्यथा अणु
				अगर (!स_भेद(&stainfo->tkiptxmickey.skey[0],
					    null_key, 16))
					वापस -ENOMEM;
				/* start to calculate the mic code */
				r8712_secmicsetkey(&micdata,
					     &stainfo->tkiptxmickey.skey[0]);
			पूर्ण
			अगर (pframe[1] & 1) अणु   /* ToDS==1 */
				r8712_secmicappend(&micdata,
						   &pframe[16], 6); /*DA*/
				अगर (pframe[1] & 2)  /* From Ds==1 */
					r8712_secmicappend(&micdata,
							   &pframe[24], 6);
				अन्यथा
					r8712_secmicappend(&micdata,
							   &pframe[10], 6);
			पूर्ण अन्यथा अणु	/* ToDS==0 */
				r8712_secmicappend(&micdata,
						   &pframe[4], 6); /* DA */
				अगर (pframe[1] & 2)  /* From Ds==1 */
					r8712_secmicappend(&micdata,
							   &pframe[16], 6);
				अन्यथा
					r8712_secmicappend(&micdata,
							   &pframe[10], 6);
			पूर्ण
			अगर (pqospriv->qos_option == 1)
				priority[0] = (u8)pxmitframe->attrib.priority;
			r8712_secmicappend(&micdata, &priority[0], 4);
			payload = pframe;
			क्रम (curfragnum = 0; curfragnum < pattrib->nr_frags;
			     curfragnum++) अणु
				payload = (u8 *)RND4((addr_t)(payload));
				payload += pattrib->hdrlen + pattrib->iv_len;
				अगर ((curfragnum + 1) == pattrib->nr_frags) अणु
					length = pattrib->last_txcmdsz -
						  pattrib->hdrlen -
						  pattrib->iv_len -
						  ((psecpriv->sw_encrypt)
						  ? pattrib->icv_len : 0);
					r8712_secmicappend(&micdata, payload,
							   length);
					payload = payload + length;
				पूर्ण अन्यथा अणु
					length = pxmitpriv->frag_len -
					    pattrib->hdrlen - pattrib->iv_len -
					    ((psecpriv->sw_encrypt) ?
					    pattrib->icv_len : 0);
					r8712_secmicappend(&micdata, payload,
							   length);
					payload = payload + length +
						  pattrib->icv_len;
				पूर्ण
			पूर्ण
			r8712_secgeपंचांगic(&micdata, &(mic[0]));
			/* add mic code  and add the mic code length in
			 * last_txcmdsz
			 */
			स_नकल(payload, &(mic[0]), 8);
			pattrib->last_txcmdsz += 8;
			payload = payload - pattrib->last_txcmdsz + 8;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल sपूर्णांक xmitframe_swencrypt(काष्ठा _adapter *padapter,
				काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा pkt_attrib	*pattrib = &pxmitframe->attrib;

	अगर (pattrib->bswenc) अणु
		चयन (pattrib->encrypt) अणु
		हाल _WEP40_:
		हाल _WEP104_:
			r8712_wep_encrypt(padapter, (u8 *)pxmitframe);
			अवरोध;
		हाल _TKIP_:
			r8712_tkip_encrypt(padapter, (u8 *)pxmitframe);
			अवरोध;
		हाल _AES_:
			r8712_aes_encrypt(padapter, (u8 *)pxmitframe);
			अवरोध;
		शेष:
				अवरोध;
		पूर्ण
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अटल पूर्णांक make_wlanhdr(काष्ठा _adapter *padapter, u8 *hdr,
			काष्ठा pkt_attrib *pattrib)
अणु
	u16 *qc;

	काष्ठा ieee80211_hdr *pwlanhdr = (काष्ठा ieee80211_hdr *)hdr;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा qos_priv *pqospriv = &pmlmepriv->qospriv;
	__le16 *fctrl = &pwlanhdr->frame_control;
	u8 *bssid;

	स_रखो(hdr, 0, WLANHDR_OFFSET);
	SetFrameSubType(fctrl, pattrib->subtype);
	अगर (!(pattrib->subtype & IEEE80211_FTYPE_DATA))
		वापस 0;

	bssid = get_bssid(pmlmepriv);

	अगर (check_fwstate(pmlmepriv,  WIFI_STATION_STATE)) अणु
		/* to_ds = 1, fr_ds = 0; */
		SetToDs(fctrl);
		ether_addr_copy(pwlanhdr->addr1, bssid);
		ether_addr_copy(pwlanhdr->addr2, pattrib->src);
		ether_addr_copy(pwlanhdr->addr3, pattrib->dst);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		/* to_ds = 0, fr_ds = 1; */
		SetFrDs(fctrl);
		ether_addr_copy(pwlanhdr->addr1, pattrib->dst);
		ether_addr_copy(pwlanhdr->addr2, bssid);
		ether_addr_copy(pwlanhdr->addr3, pattrib->src);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) ||
		   check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) अणु
		ether_addr_copy(pwlanhdr->addr1, pattrib->dst);
		ether_addr_copy(pwlanhdr->addr2, pattrib->src);
		ether_addr_copy(pwlanhdr->addr3, bssid);
	पूर्ण अन्यथा अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE)) अणु
		ether_addr_copy(pwlanhdr->addr1, pattrib->dst);
		ether_addr_copy(pwlanhdr->addr2, pattrib->src);
		ether_addr_copy(pwlanhdr->addr3, bssid);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (pattrib->encrypt)
		SetPrivacy(fctrl);
	अगर (pqospriv->qos_option) अणु
		qc = (अचिन्हित लघु *)(hdr + pattrib->hdrlen - 2);
		अगर (pattrib->priority)
			SetPriority(qc, pattrib->priority);
		SetAckpolicy(qc, pattrib->ack_policy);
	पूर्ण
	/* TODO: fill HT Control Field */
	/* Update Seq Num will be handled by f/w */
	अणु
		काष्ठा sta_info *psta;
		bool bmcst = is_multicast_ether_addr(pattrib->ra);

		अगर (pattrib->psta)
			psta = pattrib->psta;
		अन्यथा अगर (bmcst)
			psta = r8712_get_bcmc_stainfo(padapter);
		अन्यथा
			psta = r8712_get_stainfo(&padapter->stapriv,
						 pattrib->ra);

		अगर (psta) अणु
			u16 *txtid = psta->sta_xmitpriv.txseq_tid;

			txtid[pattrib->priority]++;
			txtid[pattrib->priority] &= 0xFFF;
			pattrib->seqnum = txtid[pattrib->priority];
			SetSeqNum(hdr, pattrib->seqnum);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sपूर्णांक r8712_put_snap(u8 *data, u16 h_proto)
अणु
	काष्ठा ieee80211_snap_hdr *snap;
	स्थिर u8 *oui;

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

/*
 * This sub-routine will perक्रमm all the following:
 * 1. हटाओ 802.3 header.
 * 2. create wlan_header, based on the info in pxmitframe
 * 3. append sta's iv/ext-iv
 * 4. append LLC
 * 5. move frag chunk from pframe to pxmitframe->mem
 * 6. apply sw-encrypt, अगर necessary.
 */
sपूर्णांक r8712_xmitframe_coalesce(काष्ठा _adapter *padapter, _pkt *pkt,
			काष्ठा xmit_frame *pxmitframe)
अणु
	काष्ठा pkt_file pktfile;

	sपूर्णांक	frg_len, mpdu_len, llc_sz;
	u32	mem_sz;
	u8	frg_inx;
	addr_t addr;
	u8 *pframe, *mem_start, *ptxdesc;
	काष्ठा sta_info		*psta;
	काष्ठा security_priv	*psecpriv = &padapter->securitypriv;
	काष्ठा mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	काष्ठा xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	काष्ठा pkt_attrib	*pattrib = &pxmitframe->attrib;
	u8 *pbuf_start;
	bool bmcst = is_multicast_ether_addr(pattrib->ra);

	अगर (!pattrib->psta)
		वापस _FAIL;
	psta = pattrib->psta;
	अगर (!pxmitframe->buf_addr)
		वापस _FAIL;
	pbuf_start = pxmitframe->buf_addr;
	ptxdesc = pbuf_start;
	mem_start = pbuf_start + TXDESC_OFFSET;
	अगर (make_wlanhdr(padapter, mem_start, pattrib))
		वापस _FAIL;
	_r8712_खोलो_pktfile(pkt, &pktfile);
	_r8712_pktfile_पढ़ो(&pktfile, शून्य, (uपूर्णांक) pattrib->pkt_hdrlen);
	अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE)) अणु
		/* truncate TXDESC_SIZE bytes txcmd अगर at mp mode क्रम 871x */
		अगर (pattrib->ether_type == 0x8712) अणु
			/* take care -  update_txdesc overग_लिखो this */
			_r8712_pktfile_पढ़ो(&pktfile, ptxdesc, TXDESC_SIZE);
		पूर्ण
	पूर्ण
	pattrib->pktlen = pktfile.pkt_len;
	frg_inx = 0;
	frg_len = pxmitpriv->frag_len - 4;
	जबतक (1) अणु
		llc_sz = 0;
		mpdu_len = frg_len;
		pframe = mem_start;
		SetMFrag(mem_start);
		pframe += pattrib->hdrlen;
		mpdu_len -= pattrib->hdrlen;
		/* adding icv, अगर necessary...*/
		अगर (pattrib->iv_len) अणु
			अगर (psta) अणु
				चयन (pattrib->encrypt) अणु
				हाल _WEP40_:
				हाल _WEP104_:
					WEP_IV(pattrib->iv, psta->txpn,
					       (u8)psecpriv->PrivacyKeyIndex);
					अवरोध;
				हाल _TKIP_:
					अगर (bmcst)
						TKIP_IV(pattrib->iv,
						    psta->txpn,
						    (u8)psecpriv->XGrpKeyid);
					अन्यथा
						TKIP_IV(pattrib->iv, psta->txpn,
							0);
					अवरोध;
				हाल _AES_:
					अगर (bmcst)
						AES_IV(pattrib->iv, psta->txpn,
						    (u8)psecpriv->XGrpKeyid);
					अन्यथा
						AES_IV(pattrib->iv, psta->txpn,
						       0);
					अवरोध;
				पूर्ण
			पूर्ण
			स_नकल(pframe, pattrib->iv, pattrib->iv_len);
			pframe += pattrib->iv_len;
			mpdu_len -= pattrib->iv_len;
		पूर्ण
		अगर (frg_inx == 0) अणु
			llc_sz = r8712_put_snap(pframe, pattrib->ether_type);
			pframe += llc_sz;
			mpdu_len -= llc_sz;
		पूर्ण
		अगर ((pattrib->icv_len > 0) && (pattrib->bswenc))
			mpdu_len -= pattrib->icv_len;
		अगर (bmcst)
			mem_sz = _r8712_pktfile_पढ़ो(&pktfile, pframe,
				 pattrib->pktlen);
		अन्यथा
			mem_sz = _r8712_pktfile_पढ़ो(&pktfile, pframe,
				 mpdu_len);
		pframe += mem_sz;
		अगर ((pattrib->icv_len > 0) && (pattrib->bswenc)) अणु
			स_नकल(pframe, pattrib->icv, pattrib->icv_len);
			pframe += pattrib->icv_len;
		पूर्ण
		frg_inx++;
		अगर (bmcst || r8712_enकरोfpktfile(&pktfile)) अणु
			pattrib->nr_frags = frg_inx;
			pattrib->last_txcmdsz = pattrib->hdrlen +
						pattrib->iv_len +
						((pattrib->nr_frags == 1) ?
						llc_sz : 0) +
						((pattrib->bswenc) ?
						pattrib->icv_len : 0) + mem_sz;
			ClearMFrag(mem_start);
			अवरोध;
		पूर्ण
		addr = (addr_t)(pframe);
		mem_start = (अचिन्हित अक्षर *)RND4(addr) + TXDESC_OFFSET;
		स_नकल(mem_start, pbuf_start + TXDESC_OFFSET, pattrib->hdrlen);
	पूर्ण

	अगर (xmitframe_addmic(padapter, pxmitframe))
		वापस _FAIL;
	xmitframe_swencrypt(padapter, pxmitframe);
	वापस _SUCCESS;
पूर्ण

व्योम r8712_update_protection(काष्ठा _adapter *padapter, u8 *ie, uपूर्णांक ie_len)
अणु
	uपूर्णांक	protection;
	u8	*perp;
	uपूर्णांक	erp_len;
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
		perp = r8712_get_ie(ie, WLAN_EID_ERP_INFO, &erp_len, ie_len);
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

काष्ठा xmit_buf *r8712_alloc_xmitbuf(काष्ठा xmit_priv *pxmitpriv)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा xmit_buf *pxmitbuf;
	काष्ठा  __queue *pमुक्त_xmitbuf_queue = &pxmitpriv->मुक्त_xmitbuf_queue;

	spin_lock_irqsave(&pमुक्त_xmitbuf_queue->lock, irqL);
	pxmitbuf = list_first_entry_or_null(&pमुक्त_xmitbuf_queue->queue,
					    काष्ठा xmit_buf, list);
	अगर (pxmitbuf) अणु
		list_del_init(&pxmitbuf->list);
		pxmitpriv->मुक्त_xmitbuf_cnt--;
	पूर्ण
	spin_unlock_irqrestore(&pमुक्त_xmitbuf_queue->lock, irqL);
	वापस pxmitbuf;
पूर्ण

व्योम r8712_मुक्त_xmitbuf(काष्ठा xmit_priv *pxmitpriv, काष्ठा xmit_buf *pxmitbuf)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा  __queue *pमुक्त_xmitbuf_queue = &pxmitpriv->मुक्त_xmitbuf_queue;

	अगर (!pxmitbuf)
		वापस;
	spin_lock_irqsave(&pमुक्त_xmitbuf_queue->lock, irqL);
	list_del_init(&pxmitbuf->list);
	list_add_tail(&(pxmitbuf->list), &pमुक्त_xmitbuf_queue->queue);
	pxmitpriv->मुक्त_xmitbuf_cnt++;
	spin_unlock_irqrestore(&pमुक्त_xmitbuf_queue->lock, irqL);
पूर्ण

/*
 * Calling context:
 * 1. OS_TXENTRY
 * 2. RXENTRY (rx_thपढ़ो or RX_ISR/RX_CallBack)
 *
 * If we turn on USE_RXTHREAD, then, no need क्रम critical section.
 * Otherwise, we must use _enter/_निकास critical to protect मुक्त_xmit_queue...
 *
 * Must be very very cautious...
 *
 */
काष्ठा xmit_frame *r8712_alloc_xmitframe(काष्ठा xmit_priv *pxmitpriv)
अणु
	/*
	 * Please remember to use all the osdep_service api,
	 * and lock/unlock or _enter/_निकास critical to protect
	 * pमुक्त_xmit_queue
	 */
	अचिन्हित दीर्घ irqL;
	काष्ठा xmit_frame *pxframe;
	काष्ठा  __queue *pमुक्त_xmit_queue = &pxmitpriv->मुक्त_xmit_queue;

	spin_lock_irqsave(&pमुक्त_xmit_queue->lock, irqL);
	pxframe = list_first_entry_or_null(&pमुक्त_xmit_queue->queue,
					   काष्ठा xmit_frame, list);
	अगर (pxframe) अणु
		list_del_init(&pxframe->list);
		pxmitpriv->मुक्त_xmitframe_cnt--;
		pxframe->buf_addr = शून्य;
		pxframe->pxmitbuf = शून्य;
		pxframe->attrib.psta = शून्य;
		pxframe->pkt = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&pमुक्त_xmit_queue->lock, irqL);
	वापस pxframe;
पूर्ण

व्योम r8712_मुक्त_xmitframe(काष्ठा xmit_priv *pxmitpriv,
			  काष्ठा xmit_frame *pxmitframe)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा  __queue *pमुक्त_xmit_queue = &pxmitpriv->मुक्त_xmit_queue;
	काष्ठा _adapter *padapter = pxmitpriv->adapter;

	अगर (!pxmitframe)
		वापस;
	spin_lock_irqsave(&pमुक्त_xmit_queue->lock, irqL);
	list_del_init(&pxmitframe->list);
	अगर (pxmitframe->pkt)
		pxmitframe->pkt = शून्य;
	list_add_tail(&pxmitframe->list, &pमुक्त_xmit_queue->queue);
	pxmitpriv->मुक्त_xmitframe_cnt++;
	spin_unlock_irqrestore(&pमुक्त_xmit_queue->lock, irqL);
	अगर (netअगर_queue_stopped(padapter->pnetdev))
		netअगर_wake_queue(padapter->pnetdev);
पूर्ण

व्योम r8712_मुक्त_xmitframe_ex(काष्ठा xmit_priv *pxmitpriv,
		      काष्ठा xmit_frame *pxmitframe)
अणु
	अगर (!pxmitframe)
		वापस;
	अगर (pxmitframe->frame_tag == DATA_FRAMETAG)
		r8712_मुक्त_xmitframe(pxmitpriv, pxmitframe);
पूर्ण

व्योम r8712_मुक्त_xmitframe_queue(काष्ठा xmit_priv *pxmitpriv,
				काष्ठा  __queue *pframequeue)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा list_head *plist, *phead;
	काष्ठा	xmit_frame	*pxmitframe;

	spin_lock_irqsave(&(pframequeue->lock), irqL);
	phead = &pframequeue->queue;
	plist = phead->next;
	जबतक (!end_of_queue_search(phead, plist)) अणु
		pxmitframe = container_of(plist, काष्ठा xmit_frame, list);
		plist = plist->next;
		r8712_मुक्त_xmitframe(pxmitpriv, pxmitframe);
	पूर्ण
	spin_unlock_irqrestore(&(pframequeue->lock), irqL);
पूर्ण

अटल अंतरभूत काष्ठा tx_servq *get_sta_pending(काष्ठा _adapter *padapter,
					       काष्ठा  __queue **ppstapending,
					       काष्ठा sta_info *psta, sपूर्णांक up)
अणु

	काष्ठा tx_servq *ptxservq;
	काष्ठा hw_xmit *phwxmits =  padapter->xmitpriv.hwxmits;

	चयन (up) अणु
	हाल 1:
	हाल 2:
		ptxservq = &(psta->sta_xmitpriv.bk_q);
		*ppstapending = &padapter->xmitpriv.bk_pending;
		(phwxmits + 3)->accnt++;
		अवरोध;
	हाल 4:
	हाल 5:
		ptxservq = &(psta->sta_xmitpriv.vi_q);
		*ppstapending = &padapter->xmitpriv.vi_pending;
		(phwxmits + 1)->accnt++;
		अवरोध;
	हाल 6:
	हाल 7:
		ptxservq = &(psta->sta_xmitpriv.vo_q);
		*ppstapending = &padapter->xmitpriv.vo_pending;
		(phwxmits + 0)->accnt++;
		अवरोध;
	हाल 0:
	हाल 3:
	शेष:
		ptxservq = &(psta->sta_xmitpriv.be_q);
		*ppstapending = &padapter->xmitpriv.be_pending;
		(phwxmits + 2)->accnt++;
		अवरोध;
	पूर्ण
	वापस ptxservq;
पूर्ण

/*
 * Will enqueue pxmitframe to the proper queue, and indicate it
 * to xx_pending list.....
 */
पूर्णांक r8712_xmit_classअगरier(काष्ठा _adapter *padapter,
			  काष्ठा xmit_frame *pxmitframe)
अणु
	अचिन्हित दीर्घ irqL0;
	काष्ठा  __queue *pstapending;
	काष्ठा sta_info	*psta;
	काष्ठा tx_servq	*ptxservq;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	bool bmcst = is_multicast_ether_addr(pattrib->ra);

	अगर (pattrib->psta) अणु
		psta = pattrib->psta;
	पूर्ण अन्यथा अणु
		अगर (bmcst) अणु
			psta = r8712_get_bcmc_stainfo(padapter);
		पूर्ण अन्यथा अणु
			अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE))
				psta = r8712_get_stainfo(pstapriv,
				       get_bssid(pmlmepriv));
			अन्यथा
				psta = r8712_get_stainfo(pstapriv, pattrib->ra);
		पूर्ण
	पूर्ण
	अगर (!psta)
		वापस -EINVAL;
	ptxservq = get_sta_pending(padapter, &pstapending,
		   psta, pattrib->priority);
	spin_lock_irqsave(&pstapending->lock, irqL0);
	अगर (list_empty(&ptxservq->tx_pending))
		list_add_tail(&ptxservq->tx_pending, &pstapending->queue);
	list_add_tail(&pxmitframe->list, &ptxservq->sta_pending.queue);
	ptxservq->qcnt++;
	spin_unlock_irqrestore(&pstapending->lock, irqL0);
	वापस 0;
पूर्ण

अटल व्योम alloc_hwxmits(काष्ठा _adapter *padapter)
अणु
	काष्ठा hw_xmit *hwxmits;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	pxmitpriv->hwxmit_entry = HWXMIT_ENTRY;
	pxmitpriv->hwxmits = kदो_स्मृति_array(pxmitpriv->hwxmit_entry,
				माप(काष्ठा hw_xmit), GFP_ATOMIC);
	अगर (!pxmitpriv->hwxmits)
		वापस;
	hwxmits = pxmitpriv->hwxmits;
	अगर (pxmitpriv->hwxmit_entry == 5) अणु
		pxmitpriv->bmc_txqueue.head = 0;
		hwxmits[0] .phwtxqueue = &pxmitpriv->bmc_txqueue;
		hwxmits[0] .sta_queue = &pxmitpriv->bm_pending;
		pxmitpriv->vo_txqueue.head = 0;
		hwxmits[1] .phwtxqueue = &pxmitpriv->vo_txqueue;
		hwxmits[1] .sta_queue = &pxmitpriv->vo_pending;
		pxmitpriv->vi_txqueue.head = 0;
		hwxmits[2] .phwtxqueue = &pxmitpriv->vi_txqueue;
		hwxmits[2] .sta_queue = &pxmitpriv->vi_pending;
		pxmitpriv->bk_txqueue.head = 0;
		hwxmits[3] .phwtxqueue = &pxmitpriv->bk_txqueue;
		hwxmits[3] .sta_queue = &pxmitpriv->bk_pending;
		pxmitpriv->be_txqueue.head = 0;
		hwxmits[4] .phwtxqueue = &pxmitpriv->be_txqueue;
		hwxmits[4] .sta_queue = &pxmitpriv->be_pending;
	पूर्ण अन्यथा अगर (pxmitpriv->hwxmit_entry == 4) अणु
		pxmitpriv->vo_txqueue.head = 0;
		hwxmits[0] .phwtxqueue = &pxmitpriv->vo_txqueue;
		hwxmits[0] .sta_queue = &pxmitpriv->vo_pending;
		pxmitpriv->vi_txqueue.head = 0;
		hwxmits[1] .phwtxqueue = &pxmitpriv->vi_txqueue;
		hwxmits[1] .sta_queue = &pxmitpriv->vi_pending;
		pxmitpriv->be_txqueue.head = 0;
		hwxmits[2] .phwtxqueue = &pxmitpriv->be_txqueue;
		hwxmits[2] .sta_queue = &pxmitpriv->be_pending;
		pxmitpriv->bk_txqueue.head = 0;
		hwxmits[3] .phwtxqueue = &pxmitpriv->bk_txqueue;
		hwxmits[3] .sta_queue = &pxmitpriv->bk_pending;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_hwxmits(काष्ठा _adapter *padapter)
अणु
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	kमुक्त(pxmitpriv->hwxmits);
पूर्ण

अटल व्योम init_hwxmits(काष्ठा hw_xmit *phwxmit, sपूर्णांक entry)
अणु
	sपूर्णांक i;

	क्रम (i = 0; i < entry; i++, phwxmit++) अणु
		spin_lock_init(&phwxmit->xmit_lock);
		INIT_LIST_HEAD(&phwxmit->pending);
		phwxmit->txcmdcnt = 0;
		phwxmit->accnt = 0;
	पूर्ण
पूर्ण

व्योम xmitframe_xmitbuf_attach(काष्ठा xmit_frame *pxmitframe,
			काष्ठा xmit_buf *pxmitbuf)
अणु
	/* pxmitbuf attach to pxmitframe */
	pxmitframe->pxmitbuf = pxmitbuf;
	/* urb and irp connection */
	pxmitframe->pxmit_urb[0] = pxmitbuf->pxmit_urb[0];
	/* buffer addr assoc */
	pxmitframe->buf_addr = pxmitbuf->pbuf;
	/* pxmitframe attach to pxmitbuf */
	pxmitbuf->priv_data = pxmitframe;
पूर्ण

/*
 * tx_action == 0 == no frames to transmit
 * tx_action > 0 ==> we have frames to transmit
 * tx_action < 0 ==> we have frames to transmit, but TXFF is not even enough
 *						 to transmit 1 frame.
 */

पूर्णांक r8712_pre_xmit(काष्ठा _adapter *padapter, काष्ठा xmit_frame *pxmitframe)
अणु
	अचिन्हित दीर्घ irqL;
	पूर्णांक ret;
	काष्ठा xmit_buf *pxmitbuf = शून्य;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;

	r8712_करो_queue_select(padapter, pattrib);
	spin_lock_irqsave(&pxmitpriv->lock, irqL);
	अगर (r8712_txframes_sta_ac_pending(padapter, pattrib) > 0) अणु
		ret = false;
		r8712_xmit_enqueue(padapter, pxmitframe);
		spin_unlock_irqrestore(&pxmitpriv->lock, irqL);
		वापस ret;
	पूर्ण
	pxmitbuf = r8712_alloc_xmitbuf(pxmitpriv);
	अगर (!pxmitbuf) अणु /*enqueue packet*/
		ret = false;
		r8712_xmit_enqueue(padapter, pxmitframe);
		spin_unlock_irqrestore(&pxmitpriv->lock, irqL);
	पूर्ण अन्यथा अणु /*dump packet directly*/
		spin_unlock_irqrestore(&pxmitpriv->lock, irqL);
		ret = true;
		xmitframe_xmitbuf_attach(pxmitframe, pxmitbuf);
		r8712_xmit_direct(padapter, pxmitframe);
	पूर्ण
	वापस ret;
पूर्ण
