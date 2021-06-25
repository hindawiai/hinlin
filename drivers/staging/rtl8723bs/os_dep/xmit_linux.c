<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _XMIT_OSDEP_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>


uपूर्णांक rtw_reमुख्यder_len(काष्ठा pkt_file *pfile)
अणु
	वापस (pfile->buf_len - ((SIZE_PTR)(pfile->cur_addr) - (SIZE_PTR)(pfile->buf_start)));
पूर्ण

व्योम _rtw_खोलो_pktfile(काष्ठा sk_buff *pktptr, काष्ठा pkt_file *pfile)
अणु
	pfile->pkt = pktptr;
	pfile->cur_addr = pfile->buf_start = pktptr->data;
	pfile->pkt_len = pfile->buf_len = pktptr->len;

	pfile->cur_buffer = pfile->buf_start;
पूर्ण

uपूर्णांक _rtw_pktfile_पढ़ो(काष्ठा pkt_file *pfile, u8 *rmem, uपूर्णांक rlen)
अणु
	uपूर्णांक	len = 0;

	len =  rtw_reमुख्यder_len(pfile);
	len = (rlen > len) ? len : rlen;

	अगर (rmem)
		skb_copy_bits(pfile->pkt, pfile->buf_len - pfile->pkt_len, rmem, len);

	pfile->cur_addr += len;
	pfile->pkt_len -= len;
	वापस len;
पूर्ण

चिन्हित पूर्णांक rtw_enकरोfpktfile(काष्ठा pkt_file *pfile)
अणु
	अगर (pfile->pkt_len == 0)
		वापस true;
	वापस false;
पूर्ण

पूर्णांक rtw_os_xmit_resource_alloc(काष्ठा adapter *padapter, काष्ठा xmit_buf *pxmitbuf, u32 alloc_sz, u8 flag)
अणु
	अगर (alloc_sz > 0) अणु
		pxmitbuf->pallocated_buf = rtw_zदो_स्मृति(alloc_sz);
		अगर (!pxmitbuf->pallocated_buf)
			वापस _FAIL;

		pxmitbuf->pbuf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(pxmitbuf->pallocated_buf), XMITBUF_ALIGN_SZ);
	पूर्ण

	वापस _SUCCESS;
पूर्ण

व्योम rtw_os_xmit_resource_मुक्त(काष्ठा adapter *padapter, काष्ठा xmit_buf *pxmitbuf, u32 मुक्त_sz, u8 flag)
अणु
	अगर (मुक्त_sz > 0)
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
	काष्ठा adapter *pri_adapter = padapter;

	अगर (!padapter)
		वापस;

	अगर (!list_empty(&padapter->xmitpriv.pending_xmitbuf_queue.queue))
		complete(&pri_adapter->xmitpriv.xmit_comp);
पूर्ण

अटल व्योम rtw_check_xmit_resource(काष्ठा adapter *padapter, काष्ठा sk_buff *pkt)
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
	काष्ठा	sta_priv *pstapriv = &padapter->stapriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा list_head	*phead, *plist;
	काष्ठा sk_buff *newskb;
	काष्ठा sta_info *psta = शून्य;
	u8 chk_alive_num = 0;
	अक्षर chk_alive_list[NUM_STA];
	u8 bc_addr[6] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	u8 null_addr[6] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;

	पूर्णांक i;
	s32	res;

	spin_lock_bh(&pstapriv->asoc_list_lock);
	phead = &pstapriv->asoc_list;
	plist = get_next(phead);

	/* मुक्त sta asoc_queue */
	जबतक (phead != plist) अणु
		पूर्णांक stainfo_offset;
		psta = container_of(plist, काष्ठा sta_info, asoc_list);
		plist = get_next(plist);

		stainfo_offset = rtw_stainfo_offset(pstapriv, psta);
		अगर (stainfo_offset_valid(stainfo_offset)) अणु
			chk_alive_list[chk_alive_num++] = stainfo_offset;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&pstapriv->asoc_list_lock);

	क्रम (i = 0; i < chk_alive_num; i++) अणु
		psta = rtw_get_stainfo_by_offset(pstapriv, chk_alive_list[i]);
		अगर (!(psta->state & _FW_LINKED))
			जारी;

		/* aव्योम come from STA1 and send back STA1 */
		अगर (!स_भेद(psta->hwaddr, &skb->data[6], 6) ||
		    !स_भेद(psta->hwaddr, null_addr, 6) ||
		    !स_भेद(psta->hwaddr, bc_addr, 6))
			जारी;

		newskb = rtw_skb_copy(skb);

		अगर (newskb) अणु
			स_नकल(newskb->data, psta->hwaddr, 6);
			res = rtw_xmit(padapter, &newskb);
			अगर (res < 0) अणु
				pxmitpriv->tx_drop++;
				dev_kमुक्त_skb_any(newskb);
			पूर्ण
		पूर्ण अन्यथा अणु
			pxmitpriv->tx_drop++;
			/* dev_kमुक्त_skb_any(skb); */
			वापस false;	/*  Caller shall tx this multicast frame via normal way. */
		पूर्ण
	पूर्ण

	dev_kमुक्त_skb_any(skb);
	वापस true;
पूर्ण

पूर्णांक _rtw_xmit_entry(काष्ठा sk_buff *pkt, काष्ठा net_device *pnetdev)
अणु
	काष्ठा adapter *padapter = rtw_netdev_priv(pnetdev);
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	s32 res = 0;

	अगर (rtw_अगर_up(padapter) == false)
		जाओ drop_packet;

	rtw_check_xmit_resource(padapter, pkt);

	अगर (!rtw_mc2u_disable
		&& check_fwstate(pmlmepriv, WIFI_AP_STATE) == true
		&& (IP_MCAST_MAC(pkt->data)
			|| ICMPV6_MCAST_MAC(pkt->data)
			)
		&& padapter->registrypriv.wअगरi_spec == 0) अणु
		अगर (pxmitpriv->मुक्त_xmitframe_cnt > (NR_XMITFRAME / 4)) अणु
			res = rtw_mlcst2unicst(padapter, pkt);
			अगर (res)
				जाओ निकास;
		पूर्ण
	पूर्ण

	res = rtw_xmit(padapter, &pkt);
	अगर (res < 0)
		जाओ drop_packet;

	जाओ निकास;

drop_packet:
	pxmitpriv->tx_drop++;
	dev_kमुक्त_skb_any(pkt);

निकास:
	वापस 0;
पूर्ण

पूर्णांक rtw_xmit_entry(काष्ठा sk_buff *pkt, काष्ठा net_device *pnetdev)
अणु
	पूर्णांक ret = 0;

	अगर (pkt)
		ret = _rtw_xmit_entry(pkt, pnetdev);

	वापस ret;
पूर्ण
