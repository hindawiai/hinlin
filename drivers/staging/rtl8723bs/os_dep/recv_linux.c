<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RECV_OSDEP_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <linux/jअगरfies.h>
#समावेश <net/cfg80211.h>
#समावेश <यंत्र/unaligned.h>

व्योम rtw_os_मुक्त_recvframe(जोड़ recv_frame *precvframe)
अणु
	अगर (precvframe->u.hdr.pkt) अणु
		dev_kमुक्त_skb_any(precvframe->u.hdr.pkt);/* मुक्त skb by driver */

		precvframe->u.hdr.pkt = शून्य;
	पूर्ण
पूर्ण

/* alloc os related resource in जोड़ recv_frame */
व्योम rtw_os_recv_resource_alloc(काष्ठा adapter *padapter, जोड़ recv_frame *precvframe)
अणु
	precvframe->u.hdr.pkt_newalloc = precvframe->u.hdr.pkt = शून्य;
पूर्ण

/* मुक्त os related resource in जोड़ recv_frame */
व्योम rtw_os_recv_resource_मुक्त(काष्ठा recv_priv *precvpriv)
अणु
	चिन्हित पूर्णांक i;
	जोड़ recv_frame *precvframe;

	precvframe = (जोड़ recv_frame *) precvpriv->precv_frame_buf;

	क्रम (i = 0; i < NR_RECVFRAME; i++) अणु
		अगर (precvframe->u.hdr.pkt) अणु
			/* मुक्त skb by driver */
			dev_kमुक्त_skb_any(precvframe->u.hdr.pkt);
			precvframe->u.hdr.pkt = शून्य;
		पूर्ण
		precvframe++;
	पूर्ण
पूर्ण

/* मुक्त os related resource in काष्ठा recv_buf */
व्योम rtw_os_recvbuf_resource_मुक्त(काष्ठा adapter *padapter, काष्ठा recv_buf *precvbuf)
अणु
	अगर (precvbuf->pskb) अणु
		dev_kमुक्त_skb_any(precvbuf->pskb);
	पूर्ण
पूर्ण

काष्ठा sk_buff *rtw_os_alloc_msdu_pkt(जोड़ recv_frame *prframe, u16 nSubframe_Length, u8 *pdata)
अणु
	u16 eth_type;
	काष्ठा sk_buff *sub_skb;
	काष्ठा rx_pkt_attrib *pattrib;

	pattrib = &prframe->u.hdr.attrib;

	sub_skb = rtw_skb_alloc(nSubframe_Length + 12);
	अगर (!sub_skb)
		वापस शून्य;

	skb_reserve(sub_skb, 12);
	skb_put_data(sub_skb, (pdata + ETH_HLEN), nSubframe_Length);

	eth_type = get_unaligned_be16(&sub_skb->data[6]);

	अगर (sub_skb->len >= 8 &&
		((!स_भेद(sub_skb->data, rfc1042_header, SNAP_SIZE) &&
		  eth_type != ETH_P_AARP && eth_type != ETH_P_IPX) ||
		 !स_भेद(sub_skb->data, bridge_tunnel_header, SNAP_SIZE))) अणु
		/*
		 * हटाओ RFC1042 or Bridge-Tunnel encapsulation and replace
		 * EtherType
		 */
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

	वापस sub_skb;
पूर्ण

व्योम rtw_os_recv_indicate_pkt(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt, काष्ठा rx_pkt_attrib *pattrib)
अणु
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	/* Indicate the packets to upper layer */
	अगर (pkt) अणु
		अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) अणु
			काष्ठा sk_buff *pskb2 = शून्य;
			काष्ठा sta_info *psta = शून्य;
			काष्ठा sta_priv *pstapriv = &padapter->stapriv;
			पूर्णांक bmcast = IS_MCAST(pattrib->dst);

			अगर (स_भेद(pattrib->dst, myid(&padapter->eeprompriv), ETH_ALEN)) अणु
				अगर (bmcast) अणु
					psta = rtw_get_bcmc_stainfo(padapter);
					pskb2 = skb_clone(pkt, GFP_ATOMIC);
				पूर्ण अन्यथा अणु
					psta = rtw_get_stainfo(pstapriv, pattrib->dst);
				पूर्ण

				अगर (psta) अणु
					काष्ठा net_device *pnetdev = (काष्ठा net_device *)padapter->pnetdev;
					/* skb->ip_summed = CHECKSUM_NONE; */
					pkt->dev = pnetdev;
					skb_set_queue_mapping(pkt, rtw_recv_select_queue(pkt));

					_rtw_xmit_entry(pkt, pnetdev);

					अगर (bmcast && pskb2)
						pkt = pskb2;
					अन्यथा
						वापस;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*  to APself */
			पूर्ण
		पूर्ण

		pkt->protocol = eth_type_trans(pkt, padapter->pnetdev);
		pkt->dev = padapter->pnetdev;

		pkt->ip_summed = CHECKSUM_NONE;

		rtw_netअगर_rx(padapter->pnetdev, pkt);
	पूर्ण
पूर्ण

व्योम rtw_handle_tkip_mic_err(काष्ठा adapter *padapter, u8 bgroup)
अणु
	क्रमागत nl80211_key_type key_type = 0;
	जोड़ iwreq_data wrqu;
	काष्ठा iw_michaelmicfailure    ev;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	अचिन्हित दीर्घ cur_समय = 0;

	अगर (psecuritypriv->last_mic_err_समय == 0) अणु
		psecuritypriv->last_mic_err_समय = jअगरfies;
	पूर्ण अन्यथा अणु
		cur_समय = jअगरfies;

		अगर (cur_समय - psecuritypriv->last_mic_err_समय < 60*HZ) अणु
			psecuritypriv->btkip_countermeasure = true;
			psecuritypriv->last_mic_err_समय = 0;
			psecuritypriv->btkip_countermeasure_समय = cur_समय;
		पूर्ण अन्यथा अणु
			psecuritypriv->last_mic_err_समय = jअगरfies;
		पूर्ण
	पूर्ण

	अगर (bgroup) अणु
		key_type |= NL80211_KEYTYPE_GROUP;
	पूर्ण अन्यथा अणु
		key_type |= NL80211_KEYTYPE_PAIRWISE;
	पूर्ण

	cfg80211_michael_mic_failure(padapter->pnetdev, (u8 *)&pmlmepriv->assoc_bssid[0], key_type, -1,
		शून्य, GFP_ATOMIC);

	स_रखो(&ev, 0x00, माप(ev));
	अगर (bgroup) अणु
		ev.flags |= IW_MICFAILURE_GROUP;
	पूर्ण अन्यथा अणु
		ev.flags |= IW_MICFAILURE_PAIRWISE;
	पूर्ण

	ev.src_addr.sa_family = ARPHRD_ETHER;
	स_नकल(ev.src_addr.sa_data, &pmlmepriv->assoc_bssid[0], ETH_ALEN);

	स_रखो(&wrqu, 0x00, माप(wrqu));
	wrqu.data.length = माप(ev);
पूर्ण

पूर्णांक rtw_recv_indicatepkt(काष्ठा adapter *padapter, जोड़ recv_frame *precv_frame)
अणु
	काष्ठा recv_priv *precvpriv;
	काष्ठा __queue	*pमुक्त_recv_queue;
	काष्ठा sk_buff *skb;
	काष्ठा rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;

	precvpriv = &(padapter->recvpriv);
	pमुक्त_recv_queue = &(precvpriv->मुक्त_recv_queue);

	skb = precv_frame->u.hdr.pkt;
	अगर (!skb)
		जाओ _recv_indicatepkt_drop;

	skb->data = precv_frame->u.hdr.rx_data;

	skb_set_tail_poपूर्णांकer(skb, precv_frame->u.hdr.len);

	skb->len = precv_frame->u.hdr.len;

	rtw_os_recv_indicate_pkt(padapter, skb, pattrib);

	/* poपूर्णांकers to शून्य beक्रमe rtw_मुक्त_recvframe() */
	precv_frame->u.hdr.pkt = शून्य;

	rtw_मुक्त_recvframe(precv_frame, pमुक्त_recv_queue);

	वापस _SUCCESS;

_recv_indicatepkt_drop:

	/* enqueue back to मुक्त_recv_queue */
	rtw_मुक्त_recvframe(precv_frame, pमुक्त_recv_queue);

	वापस _FAIL;
पूर्ण

व्योम rtw_init_recv_समयr(काष्ठा recv_reorder_ctrl *preorder_ctrl)
अणु
	समयr_setup(&preorder_ctrl->reordering_ctrl_समयr,
		    rtw_reordering_ctrl_समयout_handler, 0);

पूर्ण
