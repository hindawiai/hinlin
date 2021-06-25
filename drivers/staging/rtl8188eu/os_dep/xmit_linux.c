<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _XMIT_OSDEP_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#समावेश <wअगरi.h>
#समावेश <mlme_osdep.h>
#समावेश <xmit_osdep.h>
#समावेश <osdep_पूर्णांकf.h>

पूर्णांक rtw_os_xmit_resource_alloc(काष्ठा xmit_buf *pxmitbuf, u32 alloc_sz)
अणु
	पूर्णांक i;

	pxmitbuf->pallocated_buf = kzalloc(alloc_sz, GFP_KERNEL);
	अगर (!pxmitbuf->pallocated_buf)
		वापस _FAIL;

	pxmitbuf->pbuf = PTR_ALIGN(pxmitbuf->pallocated_buf, XMITBUF_ALIGN_SZ);

	क्रम (i = 0; i < 8; i++) अणु
		pxmitbuf->pxmit_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!pxmitbuf->pxmit_urb[i]) अणु
			DBG_88E("pxmitbuf->pxmit_urb[i]==NULL");
			वापस _FAIL;
		पूर्ण
	पूर्ण
	वापस _SUCCESS;
पूर्ण

व्योम rtw_os_xmit_resource_मुक्त(काष्ठा xmit_buf *pxmitbuf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		usb_मुक्त_urb(pxmitbuf->pxmit_urb[i]);

	kमुक्त(pxmitbuf->pallocated_buf);
पूर्ण

#घोषणा WMM_XMIT_THRESHOLD	(NR_XMITFRAME * 2 / 5)

व्योम rtw_os_pkt_complete(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt)
अणु
	u16 queue;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	queue = skb_get_queue_mapping(pkt);
	अगर (padapter->registrypriv.wअगरi_spec) अणु
		अगर (__netअगर_subqueue_stopped(padapter->pnetdev, queue) &&
		    (pxmitpriv->hwxmits[queue].accnt < WMM_XMIT_THRESHOLD))
			netअगर_wake_subqueue(padapter->pnetdev, queue);
	पूर्ण अन्यथा अणु
		अगर (__netअगर_subqueue_stopped(padapter->pnetdev, queue))
			netअगर_wake_subqueue(padapter->pnetdev, queue);
	पूर्ण

	dev_kमुक्त_skb_any(pkt);
पूर्ण

व्योम rtw_os_xmit_complete(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxframe)
अणु
	अगर (pxframe->pkt)
		rtw_os_pkt_complete(padapter, pxframe->pkt);
	pxframe->pkt = शून्य;
पूर्ण

व्योम rtw_os_xmit_schedule(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *pxmitpriv;

	अगर (!padapter)
		वापस;

	pxmitpriv = &padapter->xmitpriv;

	spin_lock_bh(&pxmitpriv->lock);

	अगर (rtw_txframes_pending(padapter))
		tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);

	spin_unlock_bh(&pxmitpriv->lock);
पूर्ण

अटल व्योम rtw_check_xmit_resource(काष्ठा adapter *padapter,
				    काष्ठा sk_buff *pkt)
अणु
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	u16 queue;

	queue = skb_get_queue_mapping(pkt);
	अगर (padapter->registrypriv.wअगरi_spec) अणु
		/* No मुक्त space क्रम Tx, tx_worker is too slow */
		अगर (pxmitpriv->hwxmits[queue].accnt > WMM_XMIT_THRESHOLD)
			netअगर_stop_subqueue(padapter->pnetdev, queue);
	पूर्ण अन्यथा अणु
		अगर (pxmitpriv->मुक्त_xmitframe_cnt <= 4) अणु
			अगर (!netअगर_tx_queue_stopped(netdev_get_tx_queue(padapter->pnetdev, queue)))
				netअगर_stop_subqueue(padapter->pnetdev, queue);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rtw_mlcst2unicst(काष्ठा adapter *padapter, काष्ठा sk_buff *skb)
अणु
	काष्ठा sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा list_head *phead, *plist;
	काष्ठा sk_buff *newskb;
	काष्ठा sta_info *psta = शून्य;
	s32 res;

	spin_lock_bh(&pstapriv->asoc_list_lock);
	phead = &pstapriv->asoc_list;
	plist = phead->next;

	/* मुक्त sta asoc_queue */
	जबतक (phead != plist) अणु
		psta = container_of(plist, काष्ठा sta_info, asoc_list);

		plist = plist->next;

		/* aव्योम come from STA1 and send back STA1 */
		अगर (!स_भेद(psta->hwaddr, &skb->data[6], 6))
			जारी;

		newskb = skb_copy(skb, GFP_ATOMIC);

		अगर (newskb) अणु
			स_नकल(newskb->data, psta->hwaddr, 6);
			res = rtw_xmit(padapter, &newskb);
			अगर (res < 0) अणु
				DBG_88E("%s()-%d: rtw_xmit() return error!\n",
					__func__, __LINE__);
				pxmitpriv->tx_drop++;
				dev_kमुक्त_skb_any(newskb);
			पूर्ण अन्यथा अणु
				pxmitpriv->tx_pkts++;
			पूर्ण
		पूर्ण अन्यथा अणु
			DBG_88E("%s-%d: skb_copy() failed!\n",
				__func__, __LINE__);
			pxmitpriv->tx_drop++;

			spin_unlock_bh(&pstapriv->asoc_list_lock);

			/* Caller shall tx this multicast frame
			 * via normal way.
			 */
			वापस false;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&pstapriv->asoc_list_lock);
	dev_kमुक्त_skb_any(skb);
	वापस true;
पूर्ण

पूर्णांक rtw_xmit_entry(काष्ठा sk_buff *pkt, काष्ठा net_device *pnetdev)
अणु
	काष्ठा adapter *padapter = netdev_priv(pnetdev);
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	s32 res = 0;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("+xmit_enry\n"));

	अगर (!rtw_अगर_up(padapter)) अणु
		RT_TRACE(_module_xmit_osdep_c_, _drv_err_,
			 ("%s: rtw_if_up fail\n", __func__));
		जाओ drop_packet;
	पूर्ण

	rtw_check_xmit_resource(padapter, pkt);

	अगर (!rtw_mc2u_disable && check_fwstate(pmlmepriv, WIFI_AP_STATE) &&
	    (IP_MCAST_MAC(pkt->data) || ICMPV6_MCAST_MAC(pkt->data)) &&
	    (padapter->registrypriv.wअगरi_spec == 0)) अणु
		अगर (pxmitpriv->मुक्त_xmitframe_cnt > NR_XMITFRAME / 4) अणु
			res = rtw_mlcst2unicst(padapter, pkt);
			अगर (res)
				जाओ निकास;
		पूर्ण
	पूर्ण

	res = rtw_xmit(padapter, &pkt);
	अगर (res < 0)
		जाओ drop_packet;

	pxmitpriv->tx_pkts++;
	RT_TRACE(_module_xmit_osdep_c_, _drv_info_,
		 ("%s: tx_pkts=%d\n", __func__, (u32)pxmitpriv->tx_pkts));
	जाओ निकास;

drop_packet:
	pxmitpriv->tx_drop++;
	dev_kमुक्त_skb_any(pkt);
	RT_TRACE(_module_xmit_osdep_c_, _drv_notice_,
		 ("%s: drop, tx_drop=%d\n", __func__, (u32)pxmitpriv->tx_drop));

निकास:
	वापस NETDEV_TX_OK;
पूर्ण
