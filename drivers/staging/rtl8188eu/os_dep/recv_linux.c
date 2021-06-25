<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#समावेश <wअगरi.h>
#समावेश <recv_osdep.h>

#समावेश <osdep_पूर्णांकf.h>
#समावेश <usb_ops_linux.h>

/* alloc os related resource in काष्ठा recv_buf */
पूर्णांक rtw_os_recvbuf_resource_alloc(काष्ठा recv_buf *precvbuf)
अणु
	precvbuf->pskb = शून्य;
	precvbuf->reuse = false;
	precvbuf->purb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!precvbuf->purb)
		वापस _FAIL;
	वापस _SUCCESS;
पूर्ण

व्योम rtw_handle_tkip_mic_err(काष्ठा adapter *padapter, u8 bgroup)
अणु
	जोड़ iwreq_data wrqu;
	काष्ठा iw_michaelmicfailure ev;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा security_priv *psecuritypriv = &padapter->securitypriv;
	u32 cur_समय = 0;

	अगर (psecuritypriv->last_mic_err_समय == 0) अणु
		psecuritypriv->last_mic_err_समय = jअगरfies;
	पूर्ण अन्यथा अणु
		cur_समय = jअगरfies;

		अगर (cur_समय - psecuritypriv->last_mic_err_समय < 60 * HZ) अणु
			psecuritypriv->btkip_countermeasure = true;
			psecuritypriv->last_mic_err_समय = 0;
			psecuritypriv->btkip_countermeasure_समय = cur_समय;
		पूर्ण अन्यथा अणु
			psecuritypriv->last_mic_err_समय = jअगरfies;
		पूर्ण
	पूर्ण

	स_रखो(&ev, 0x00, माप(ev));
	अगर (bgroup)
		ev.flags |= IW_MICFAILURE_GROUP;
	अन्यथा
		ev.flags |= IW_MICFAILURE_PAIRWISE;

	ev.src_addr.sa_family = ARPHRD_ETHER;
	स_नकल(ev.src_addr.sa_data, &pmlmepriv->assoc_bssid[0], ETH_ALEN);
	स_रखो(&wrqu, 0x00, माप(wrqu));
	wrqu.data.length = माप(ev);
	wireless_send_event(padapter->pnetdev, IWEVMICHAELMICFAILURE,
			    &wrqu, (अक्षर *)&ev);
पूर्ण

पूर्णांक rtw_recv_indicatepkt(काष्ठा adapter *padapter,
			 काष्ठा recv_frame *precv_frame)
अणु
	काष्ठा recv_priv *precvpriv;
	काष्ठा __queue *pमुक्त_recv_queue;
	काष्ठा sk_buff *skb;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;

	precvpriv = &padapter->recvpriv;
	pमुक्त_recv_queue = &precvpriv->मुक्त_recv_queue;

	skb = precv_frame->pkt;
	अगर (!skb) अणु
		RT_TRACE(_module_recv_osdep_c_, _drv_err_,
			 ("%s():skb == NULL something wrong!!!!\n", __func__));
		जाओ _recv_indicatepkt_drop;
	पूर्ण

	अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE)) अणु
		काष्ठा sk_buff *pskb2 = शून्य;
		काष्ठा sta_info *psta = शून्य;
		काष्ठा sta_priv *pstapriv = &padapter->stapriv;
		काष्ठा rx_pkt_attrib *pattrib = &precv_frame->attrib;
		bool mcast = is_multicast_ether_addr(pattrib->dst);

		अगर (स_भेद(pattrib->dst, myid(&padapter->eeprompriv),
			   ETH_ALEN)) अणु
			अगर (mcast) अणु
				psta = rtw_get_bcmc_stainfo(padapter);
				pskb2 = skb_clone(skb, GFP_ATOMIC);
			पूर्ण अन्यथा अणु
				psta = rtw_get_stainfo(pstapriv, pattrib->dst);
			पूर्ण

			अगर (psta) अणु
				काष्ठा net_device *pnetdev;

				pnetdev = (काष्ठा net_device *)padapter->pnetdev;
				skb->dev = pnetdev;
				skb_set_queue_mapping(skb, rtw_recv_select_queue(skb));

				rtw_xmit_entry(skb, pnetdev);

				अगर (mcast)
					skb = pskb2;
				अन्यथा
					जाओ _recv_indicatepkt_end;
			पूर्ण
		पूर्ण
	पूर्ण

	skb->ip_summed = CHECKSUM_NONE;
	skb->dev = padapter->pnetdev;
	skb->protocol = eth_type_trans(skb, padapter->pnetdev);

	netअगर_rx(skb);

_recv_indicatepkt_end:

	/*  poपूर्णांकers to शून्य beक्रमe rtw_मुक्त_recvframe() */
	precv_frame->pkt = शून्य;

	rtw_मुक्त_recvframe(precv_frame, pमुक्त_recv_queue);

	RT_TRACE(_module_recv_osdep_c_, _drv_info_,
		 ("\n %s :after netif_rx!!!!\n", __func__));

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
