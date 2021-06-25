<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * rtl8712_recv.c
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

#घोषणा _RTL8712_RECV_C_

#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <net/cfg80211.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "recv_osdep.h"
#समावेश "mlme_osdep.h"
#समावेश "ethernet.h"
#समावेश "usb_ops.h"
#समावेश "wifi.h"

अटल व्योम recv_tasklet(काष्ठा tasklet_काष्ठा *t);

व्योम r8712_init_recv_priv(काष्ठा recv_priv *precvpriv,
			  काष्ठा _adapter *padapter)
अणु
	पूर्णांक i;
	काष्ठा recv_buf *precvbuf;
	addr_t पंचांगpaddr = 0;
	पूर्णांक alignment = 0;
	काष्ठा sk_buff *pskb = शून्य;

	/*init recv_buf*/
	_init_queue(&precvpriv->मुक्त_recv_buf_queue);
	precvpriv->pallocated_recv_buf =
		kzalloc(NR_RECVBUFF * माप(काष्ठा recv_buf) + 4, GFP_ATOMIC);
	अगर (!precvpriv->pallocated_recv_buf)
		वापस;
	precvpriv->precv_buf = precvpriv->pallocated_recv_buf + 4 -
			      ((addr_t)(precvpriv->pallocated_recv_buf) & 3);
	precvbuf = (काष्ठा recv_buf *)precvpriv->precv_buf;
	क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
		INIT_LIST_HEAD(&precvbuf->list);
		spin_lock_init(&precvbuf->recvbuf_lock);
		अगर (r8712_os_recvbuf_resource_alloc(padapter, precvbuf))
			अवरोध;
		precvbuf->ref_cnt = 0;
		precvbuf->adapter = padapter;
		list_add_tail(&precvbuf->list,
			      &(precvpriv->मुक्त_recv_buf_queue.queue));
		precvbuf++;
	पूर्ण
	precvpriv->मुक्त_recv_buf_queue_cnt = NR_RECVBUFF;
	tasklet_setup(&precvpriv->recv_tasklet, recv_tasklet);
	skb_queue_head_init(&precvpriv->rx_skb_queue);

	skb_queue_head_init(&precvpriv->मुक्त_recv_skb_queue);
	क्रम (i = 0; i < NR_PREALLOC_RECV_SKB; i++) अणु
		pskb = netdev_alloc_skb(padapter->pnetdev, MAX_RECVBUF_SZ +
		       RECVBUFF_ALIGN_SZ);
		अगर (pskb) अणु
			पंचांगpaddr = (addr_t)pskb->data;
			alignment = पंचांगpaddr & (RECVBUFF_ALIGN_SZ - 1);
			skb_reserve(pskb, (RECVBUFF_ALIGN_SZ - alignment));
			skb_queue_tail(&precvpriv->मुक्त_recv_skb_queue, pskb);
		पूर्ण
		pskb = शून्य;
	पूर्ण
पूर्ण

व्योम r8712_मुक्त_recv_priv(काष्ठा recv_priv *precvpriv)
अणु
	पूर्णांक i;
	काष्ठा recv_buf *precvbuf;
	काष्ठा _adapter *padapter = precvpriv->adapter;

	precvbuf = (काष्ठा recv_buf *)precvpriv->precv_buf;
	क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
		r8712_os_recvbuf_resource_मुक्त(padapter, precvbuf);
		precvbuf++;
	पूर्ण
	kमुक्त(precvpriv->pallocated_recv_buf);
	skb_queue_purge(&precvpriv->rx_skb_queue);
	अगर (skb_queue_len(&precvpriv->rx_skb_queue))
		netdev_warn(padapter->pnetdev, "r8712u: rx_skb_queue not empty\n");
	skb_queue_purge(&precvpriv->मुक्त_recv_skb_queue);
	अगर (skb_queue_len(&precvpriv->मुक्त_recv_skb_queue))
		netdev_warn(padapter->pnetdev, "r8712u: free_recv_skb_queue not empty %d\n",
			    skb_queue_len(&precvpriv->मुक्त_recv_skb_queue));
पूर्ण

व्योम r8712_init_recvbuf(काष्ठा _adapter *padapter, काष्ठा recv_buf *precvbuf)
अणु
	precvbuf->transfer_len = 0;
	precvbuf->len = 0;
	precvbuf->ref_cnt = 0;
	अगर (precvbuf->pbuf) अणु
		precvbuf->pdata = precvbuf->pbuf;
		precvbuf->phead = precvbuf->pbuf;
		precvbuf->ptail = precvbuf->pbuf;
		precvbuf->pend = precvbuf->pdata + MAX_RECVBUF_SZ;
	पूर्ण
पूर्ण

व्योम r8712_मुक्त_recvframe(जोड़ recv_frame *precvframe,
			  काष्ठा  __queue *pमुक्त_recv_queue)
अणु
	अचिन्हित दीर्घ irqL;
	काष्ठा _adapter *padapter = precvframe->u.hdr.adapter;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;

	अगर (precvframe->u.hdr.pkt) अणु
		dev_kमुक्त_skb_any(precvframe->u.hdr.pkt);/*मुक्त skb by driver*/
		precvframe->u.hdr.pkt = शून्य;
	पूर्ण
	spin_lock_irqsave(&pमुक्त_recv_queue->lock, irqL);
	list_del_init(&(precvframe->u.hdr.list));
	list_add_tail(&(precvframe->u.hdr.list), &pमुक्त_recv_queue->queue);
	अगर (padapter) अणु
		अगर (pमुक्त_recv_queue == &precvpriv->मुक्त_recv_queue)
			precvpriv->मुक्त_recvframe_cnt++;
	पूर्ण
	spin_unlock_irqrestore(&pमुक्त_recv_queue->lock, irqL);
पूर्ण

अटल व्योम update_recvframe_attrib_from_recvstat(काष्ठा rx_pkt_attrib *pattrib,
						  काष्ठा recv_stat *prxstat)
अणु
	u16 drvinfo_sz;

	drvinfo_sz = (le32_to_cpu(prxstat->rxdw0) & 0x000f0000) >> 16;
	drvinfo_sz <<= 3;
	/*TODO:
	 * Offset 0
	 */
	pattrib->bdecrypted = (le32_to_cpu(prxstat->rxdw0) & BIT(27)) == 0;
	pattrib->crc_err = (le32_to_cpu(prxstat->rxdw0) & BIT(14)) != 0;
	/*Offset 4*/
	/*Offset 8*/
	/*Offset 12*/
	अगर (le32_to_cpu(prxstat->rxdw3) & BIT(13)) अणु
		pattrib->tcpchk_valid = 1; /* valid */
		अगर (le32_to_cpu(prxstat->rxdw3) & BIT(11))
			pattrib->tcp_chkrpt = 1; /* correct */
		अन्यथा
			pattrib->tcp_chkrpt = 0; /* incorrect */
		अगर (le32_to_cpu(prxstat->rxdw3) & BIT(12))
			pattrib->ip_chkrpt = 1; /* correct */
		अन्यथा
			pattrib->ip_chkrpt = 0; /* incorrect */
	पूर्ण अन्यथा अणु
		pattrib->tcpchk_valid = 0; /* invalid */
	पूर्ण
	pattrib->mcs_rate = (u8)((le32_to_cpu(prxstat->rxdw3)) & 0x3f);
	pattrib->htc = (u8)((le32_to_cpu(prxstat->rxdw3) >> 14) & 0x1);
	/*Offset 16*/
	/*Offset 20*/
	/*phy_info*/
पूर्ण

/*perक्रमm defrag*/
अटल जोड़ recv_frame *recvframe_defrag(काष्ठा _adapter *adapter,
					  काष्ठा  __queue *defrag_q)
अणु
	काष्ठा list_head *plist, *phead;
	u8 wlanhdr_offset;
	u8	curfragnum;
	काष्ठा recv_frame_hdr *pfhdr, *pnfhdr;
	जोड़ recv_frame *prframe, *pnextrframe;
	काष्ठा  __queue	*pमुक्त_recv_queue;

	pमुक्त_recv_queue = &adapter->recvpriv.मुक्त_recv_queue;
	phead = &defrag_q->queue;
	plist = phead->next;
	prframe = container_of(plist, जोड़ recv_frame, u.list);
	list_del_init(&prframe->u.list);
	pfhdr = &prframe->u.hdr;
	curfragnum = 0;
	अगर (curfragnum != pfhdr->attrib.frag_num) अणु
		/*the first fragment number must be 0
		 *मुक्त the whole queue
		 */
		r8712_मुक्त_recvframe(prframe, pमुक्त_recv_queue);
		r8712_मुक्त_recvframe_queue(defrag_q, pमुक्त_recv_queue);
		वापस शून्य;
	पूर्ण
	curfragnum++;
	plist = &defrag_q->queue;
	plist = plist->next;
	जबतक (!end_of_queue_search(phead, plist)) अणु
		pnextrframe = container_of(plist, जोड़ recv_frame, u.list);
		pnfhdr = &pnextrframe->u.hdr;
		/*check the fragment sequence  (2nd ~n fragment frame) */
		अगर (curfragnum != pnfhdr->attrib.frag_num) अणु
			/* the fragment number must increase  (after decache)
			 * release the defrag_q & prframe
			 */
			r8712_मुक्त_recvframe(prframe, pमुक्त_recv_queue);
			r8712_मुक्त_recvframe_queue(defrag_q, pमुक्त_recv_queue);
			वापस शून्य;
		पूर्ण
		curfragnum++;
		/* copy the 2nd~n fragment frame's payload to the first fragment
		 * get the 2nd~last fragment frame's payload
		 */
		wlanhdr_offset = pnfhdr->attrib.hdrlen + pnfhdr->attrib.iv_len;
		recvframe_pull(pnextrframe, wlanhdr_offset);
		/* append  to first fragment frame's tail (अगर privacy frame,
		 * pull the ICV)
		 */
		recvframe_pull_tail(prframe, pfhdr->attrib.icv_len);
		स_नकल(pfhdr->rx_tail, pnfhdr->rx_data, pnfhdr->len);
		recvframe_put(prframe, pnfhdr->len);
		pfhdr->attrib.icv_len = pnfhdr->attrib.icv_len;
		plist = plist->next;
	पूर्ण
	/* मुक्त the defrag_q queue and वापस the prframe */
	r8712_मुक्त_recvframe_queue(defrag_q, pमुक्त_recv_queue);
	वापस prframe;
पूर्ण

/* check अगर need to defrag, अगर needed queue the frame to defrag_q */
जोड़ recv_frame *r8712_recvframe_chk_defrag(काष्ठा _adapter *padapter,
					     जोड़ recv_frame *precv_frame)
अणु
	u8	ismfrag;
	u8	fragnum;
	u8   *psta_addr;
	काष्ठा recv_frame_hdr *pfhdr;
	काष्ठा sta_info *psta;
	काष्ठा	sta_priv *pstapriv;
	काष्ठा list_head *phead;
	जोड़ recv_frame *prtnframe = शून्य;
	काष्ठा  __queue *pमुक्त_recv_queue, *pdefrag_q;

	pstapriv = &padapter->stapriv;
	pfhdr = &precv_frame->u.hdr;
	pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;
	/* need to define काष्ठा of wlan header frame ctrl */
	ismfrag = pfhdr->attrib.mfrag;
	fragnum = pfhdr->attrib.frag_num;
	psta_addr = pfhdr->attrib.ta;
	psta = r8712_get_stainfo(pstapriv, psta_addr);
	अगर (!psta)
		pdefrag_q = शून्य;
	अन्यथा
		pdefrag_q = &psta->sta_recvpriv.defrag_q;

	अगर ((ismfrag == 0) && (fragnum == 0))
		prtnframe = precv_frame;/*isn't a fragment frame*/
	अगर (ismfrag == 1) अणु
		/* 0~(n-1) fragment frame
		 * enqueue to defraf_g
		 */
		अगर (pdefrag_q) अणु
			अगर (fragnum == 0) अणु
				/*the first fragment*/
				अगर (!list_empty(&pdefrag_q->queue)) अणु
					/*मुक्त current defrag_q */
					r8712_मुक्त_recvframe_queue(pdefrag_q,
							     pमुक्त_recv_queue);
				पूर्ण
			पूर्ण
			/* Then enqueue the 0~(n-1) fragment to the defrag_q */
			phead = &pdefrag_q->queue;
			list_add_tail(&pfhdr->list, phead);
			prtnframe = शून्य;
		पूर्ण अन्यथा अणु
			/* can't find this ta's defrag_queue, so मुक्त this
			 * recv_frame
			 */
			r8712_मुक्त_recvframe(precv_frame, pमुक्त_recv_queue);
			prtnframe = शून्य;
		पूर्ण
	पूर्ण
	अगर ((ismfrag == 0) && (fragnum != 0)) अणु
		/* the last fragment frame
		 * enqueue the last fragment
		 */
		अगर (pdefrag_q) अणु
			phead = &pdefrag_q->queue;
			list_add_tail(&pfhdr->list, phead);
			/*call recvframe_defrag to defrag*/
			precv_frame = recvframe_defrag(padapter, pdefrag_q);
			prtnframe = precv_frame;
		पूर्ण अन्यथा अणु
			/* can't find this ta's defrag_queue, so मुक्त this
			 *  recv_frame
			 */
			r8712_मुक्त_recvframe(precv_frame, pमुक्त_recv_queue);
			prtnframe = शून्य;
		पूर्ण
	पूर्ण
	अगर (prtnframe && (prtnframe->u.hdr.attrib.privacy)) अणु
		/* after defrag we must check tkip mic code */
		अगर (r8712_recvframe_chkmic(padapter, prtnframe) == _FAIL) अणु
			r8712_मुक्त_recvframe(prtnframe, pमुक्त_recv_queue);
			prtnframe = शून्य;
		पूर्ण
	पूर्ण
	वापस prtnframe;
पूर्ण

अटल व्योम amsdu_to_msdu(काष्ठा _adapter *padapter, जोड़ recv_frame *prframe)
अणु
	पूर्णांक	a_len, padding_len;
	u16	eth_type, nSubframe_Length;
	u8	nr_subframes, i;
	अचिन्हित अक्षर *pdata;
	काष्ठा rx_pkt_attrib *pattrib;
	_pkt *sub_skb, *subframes[MAX_SUBFRAME_COUNT];
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;
	काष्ठा  __queue *pमुक्त_recv_queue = &(precvpriv->मुक्त_recv_queue);

	nr_subframes = 0;
	pattrib = &prframe->u.hdr.attrib;
	recvframe_pull(prframe, prframe->u.hdr.attrib.hdrlen);
	अगर (prframe->u.hdr.attrib.iv_len > 0)
		recvframe_pull(prframe, prframe->u.hdr.attrib.iv_len);
	a_len = prframe->u.hdr.len;
	pdata = prframe->u.hdr.rx_data;
	जबतक (a_len > ETH_HLEN) अणु
		/* Offset 12 denote 2 mac address */
		nSubframe_Length = *((u16 *)(pdata + 12));
		/*==m==>change the length order*/
		nSubframe_Length = (nSubframe_Length >> 8) +
				   (nSubframe_Length << 8);
		अगर (a_len < (ETHERNET_HEADER_SIZE + nSubframe_Length)) अणु
			netdev_warn(padapter->pnetdev, "r8712u: nRemain_Length is %d and nSubframe_Length is: %d\n",
				    a_len, nSubframe_Length);
			जाओ निकास;
		पूर्ण
		/* move the data poपूर्णांक to data content */
		pdata += ETH_HLEN;
		a_len -= ETH_HLEN;
		/* Allocate new skb क्रम releasing to upper layer */
		sub_skb = dev_alloc_skb(nSubframe_Length + 12);
		अगर (!sub_skb)
			अवरोध;
		skb_reserve(sub_skb, 12);
		skb_put_data(sub_skb, pdata, nSubframe_Length);
		subframes[nr_subframes++] = sub_skb;
		अगर (nr_subframes >= MAX_SUBFRAME_COUNT) अणु
			netdev_warn(padapter->pnetdev, "r8712u: ParseSubframe(): Too many Subframes! Packets dropped!\n");
			अवरोध;
		पूर्ण
		pdata += nSubframe_Length;
		a_len -= nSubframe_Length;
		अगर (a_len != 0) अणु
			padding_len = 4 - ((nSubframe_Length + ETH_HLEN) & 3);
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
		eth_type = (sub_skb->data[6] << 8) | sub_skb->data[7];
		अगर (sub_skb->len >= 8 &&
		    ((!स_भेद(sub_skb->data, rfc1042_header, SNAP_SIZE) &&
		      eth_type != ETH_P_AARP && eth_type != ETH_P_IPX) ||
		     !स_भेद(sub_skb->data, bridge_tunnel_header, SNAP_SIZE))) अणु
			/* हटाओ RFC1042 or Bridge-Tunnel encapsulation and
			 * replace EtherType
			 */
			skb_pull(sub_skb, SNAP_SIZE);
			स_नकल(skb_push(sub_skb, ETH_ALEN), pattrib->src,
			       ETH_ALEN);
			स_नकल(skb_push(sub_skb, ETH_ALEN), pattrib->dst,
			       ETH_ALEN);
		पूर्ण अन्यथा अणु
			__be16 len;
			/* Leave Ethernet header part of hdr and full payload */
			len = htons(sub_skb->len);
			स_नकल(skb_push(sub_skb, 2), &len, 2);
			स_नकल(skb_push(sub_skb, ETH_ALEN), pattrib->src,
			       ETH_ALEN);
			स_नकल(skb_push(sub_skb, ETH_ALEN), pattrib->dst,
			       ETH_ALEN);
		पूर्ण
		/* Indicate the packets to upper layer */
		अगर (sub_skb) अणु
			sub_skb->protocol =
				 eth_type_trans(sub_skb, padapter->pnetdev);
			sub_skb->dev = padapter->pnetdev;
			अगर ((pattrib->tcpchk_valid == 1) &&
			    (pattrib->tcp_chkrpt == 1)) अणु
				sub_skb->ip_summed = CHECKSUM_UNNECESSARY;
			पूर्ण अन्यथा अणु
				sub_skb->ip_summed = CHECKSUM_NONE;
			पूर्ण
			netअगर_rx(sub_skb);
		पूर्ण
	पूर्ण
निकास:
	prframe->u.hdr.len = 0;
	r8712_मुक्त_recvframe(prframe, pमुक्त_recv_queue);
पूर्ण

व्योम r8712_rxcmd_event_hdl(काष्ठा _adapter *padapter, व्योम *prxcmdbuf)
अणु
	__le32 voffset;
	u8 *poffset;
	u16 cmd_len, drvinfo_sz;
	काष्ठा recv_stat *prxstat;

	poffset = prxcmdbuf;
	voffset = *(__le32 *)poffset;
	prxstat = prxcmdbuf;
	drvinfo_sz = (le32_to_cpu(prxstat->rxdw0) & 0x000f0000) >> 16;
	drvinfo_sz <<= 3;
	poffset += RXDESC_SIZE + drvinfo_sz;
	करो अणु
		voffset  = *(__le32 *)poffset;
		cmd_len = (u16)(le32_to_cpu(voffset) & 0xffff);
		r8712_event_handle(padapter, (__le32 *)poffset);
		poffset += (cmd_len + 8);/*8 bytes alignment*/
	पूर्ण जबतक (le32_to_cpu(voffset) & BIT(31));
पूर्ण

अटल पूर्णांक check_indicate_seq(काष्ठा recv_reorder_ctrl *preorder_ctrl,
			      u16 seq_num)
अणु
	u8 wsize = preorder_ctrl->wsize_b;
	u16 wend = (preorder_ctrl->indicate_seq + wsize - 1) % 4096;

	/* Rx Reorder initialize condition.*/
	अगर (preorder_ctrl->indicate_seq == 0xffff)
		preorder_ctrl->indicate_seq = seq_num;
	/* Drop out the packet which SeqNum is smaller than WinStart */
	अगर (SN_LESS(seq_num, preorder_ctrl->indicate_seq))
		वापस false;
	/*
	 * Sliding winकरोw manipulation. Conditions includes:
	 * 1. Incoming SeqNum is equal to WinStart =>Winकरोw shअगरt 1
	 * 2. Incoming SeqNum is larger than the WinEnd => Winकरोw shअगरt N
	 */
	अगर (SN_EQUAL(seq_num, preorder_ctrl->indicate_seq))
		preorder_ctrl->indicate_seq = (preorder_ctrl->indicate_seq +
					      1) % 4096;
	अन्यथा अगर (SN_LESS(wend, seq_num)) अणु
		अगर (seq_num >= (wsize - 1))
			preorder_ctrl->indicate_seq = seq_num + 1 - wsize;
		अन्यथा
			preorder_ctrl->indicate_seq = 4095 - (wsize -
						      (seq_num + 1)) + 1;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक enqueue_reorder_recvframe(काष्ठा recv_reorder_ctrl *preorder_ctrl,
				     जोड़ recv_frame *prframe)
अणु
	काष्ठा list_head *phead, *plist;
	जोड़ recv_frame *pnextrframe;
	काष्ठा rx_pkt_attrib *pnextattrib;
	काष्ठा  __queue *ppending_recvframe_queue =
					&preorder_ctrl->pending_recvframe_queue;
	काष्ठा rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;

	phead = &ppending_recvframe_queue->queue;
	plist = phead->next;
	जबतक (!end_of_queue_search(phead, plist)) अणु
		pnextrframe = container_of(plist, जोड़ recv_frame, u.list);
		pnextattrib = &pnextrframe->u.hdr.attrib;

		अगर (SN_EQUAL(pnextattrib->seq_num, pattrib->seq_num))
			वापस false;

		अगर (SN_LESS(pnextattrib->seq_num, pattrib->seq_num))
			plist = plist->next;
		अन्यथा
			अवरोध;
	पूर्ण
	list_del_init(&(prframe->u.hdr.list));
	list_add_tail(&(prframe->u.hdr.list), plist);
	वापस true;
पूर्ण

पूर्णांक r8712_recv_indicatepkts_in_order(काष्ठा _adapter *padapter,
				     काष्ठा recv_reorder_ctrl *preorder_ctrl,
				     पूर्णांक bक्रमced)
अणु
	काष्ठा list_head *phead, *plist;
	जोड़ recv_frame *prframe;
	काष्ठा rx_pkt_attrib *pattrib;
	पूर्णांक bPktInBuf = false;
	काष्ठा  __queue *ppending_recvframe_queue =
			 &preorder_ctrl->pending_recvframe_queue;

	phead = &ppending_recvframe_queue->queue;
	plist = phead->next;
	/* Handling some condition क्रम क्रमced indicate हाल.*/
	अगर (bक्रमced) अणु
		अगर (list_empty(phead))
			वापस true;

		prframe = container_of(plist, जोड़ recv_frame, u.list);
		pattrib = &prframe->u.hdr.attrib;
		preorder_ctrl->indicate_seq = pattrib->seq_num;
	पूर्ण
	/* Prepare indication list and indication.
	 * Check अगर there is any packet need indicate.
	 */
	जबतक (!list_empty(phead)) अणु
		prframe = container_of(plist, जोड़ recv_frame, u.list);
		pattrib = &prframe->u.hdr.attrib;
		अगर (!SN_LESS(preorder_ctrl->indicate_seq, pattrib->seq_num)) अणु
			plist = plist->next;
			list_del_init(&(prframe->u.hdr.list));
			अगर (SN_EQUAL(preorder_ctrl->indicate_seq,
				     pattrib->seq_num))
				preorder_ctrl->indicate_seq =
				  (preorder_ctrl->indicate_seq + 1) % 4096;
			/*indicate this recv_frame*/
			अगर (!pattrib->amsdu) अणु
				अगर (!padapter->driver_stopped &&
				    !padapter->surprise_हटाओd) अणु
					/* indicate this recv_frame */
					r8712_recv_indicatepkt(padapter,
							       prframe);
				पूर्ण
			पूर्ण अन्यथा अगर (pattrib->amsdu == 1) अणु
				amsdu_to_msdu(padapter, prframe);
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

अटल पूर्णांक recv_indicatepkt_reorder(काष्ठा _adapter *padapter,
				    जोड़ recv_frame *prframe)
अणु
	अचिन्हित दीर्घ irql;
	काष्ठा rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	काष्ठा recv_reorder_ctrl *preorder_ctrl = prframe->u.hdr.preorder_ctrl;
	काष्ठा  __queue *ppending_recvframe_queue =
			 &preorder_ctrl->pending_recvframe_queue;

	अगर (!pattrib->amsdu) अणु
		/* s1. */
		r8712_wlanhdr_to_ethhdr(prframe);
		अगर (pattrib->qos != 1) अणु
			अगर (!padapter->driver_stopped &&
			    !padapter->surprise_हटाओd) अणु
				r8712_recv_indicatepkt(padapter, prframe);
				वापस 0;
			पूर्ण अन्यथा अणु
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_lock_irqsave(&ppending_recvframe_queue->lock, irql);
	/*s2. check अगर winstart_b(indicate_seq) needs to be updated*/
	अगर (!check_indicate_seq(preorder_ctrl, pattrib->seq_num))
		जाओ _err_निकास;
	/*s3. Insert all packet पूर्णांकo Reorder Queue to मुख्यtain its ordering.*/
	अगर (!enqueue_reorder_recvframe(preorder_ctrl, prframe))
		जाओ _err_निकास;
	/*s4.
	 * Indication process.
	 * After Packet dropping and Sliding Winकरोw shअगरting as above, we can
	 * now just indicate the packets with the SeqNum smaller than latest
	 * WinStart and buffer other packets.
	 *
	 * For Rx Reorder condition:
	 * 1. All packets with SeqNum smaller than WinStart => Indicate
	 * 2. All packets with SeqNum larger than or equal to
	 * WinStart => Buffer it.
	 */
	अगर (r8712_recv_indicatepkts_in_order(padapter, preorder_ctrl, false)) अणु
		mod_समयr(&preorder_ctrl->reordering_ctrl_समयr,
			  jअगरfies + msecs_to_jअगरfies(REORDER_WAIT_TIME));
		spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql);
		del_समयr(&preorder_ctrl->reordering_ctrl_समयr);
	पूर्ण
	वापस 0;
_err_निकास:
	spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql);
	वापस -ENOMEM;
पूर्ण

व्योम r8712_reordering_ctrl_समयout_handler(व्योम *pcontext)
अणु
	अचिन्हित दीर्घ irql;
	काष्ठा recv_reorder_ctrl *preorder_ctrl = pcontext;
	काष्ठा _adapter *padapter = preorder_ctrl->padapter;
	काष्ठा  __queue *ppending_recvframe_queue =
				 &preorder_ctrl->pending_recvframe_queue;

	अगर (padapter->driver_stopped || padapter->surprise_हटाओd)
		वापस;
	spin_lock_irqsave(&ppending_recvframe_queue->lock, irql);
	r8712_recv_indicatepkts_in_order(padapter, preorder_ctrl, true);
	spin_unlock_irqrestore(&ppending_recvframe_queue->lock, irql);
पूर्ण

अटल पूर्णांक r8712_process_recv_indicatepkts(काष्ठा _adapter *padapter,
					   जोड़ recv_frame *prframe)
अणु
	पूर्णांक retval = _SUCCESS;
	काष्ठा mlme_priv *pmlmepriv = &padapter->mlmepriv;
	काष्ठा ht_priv	*phtpriv = &pmlmepriv->htpriv;

	अगर (phtpriv->ht_option == 1) अणु /*B/G/N Mode*/
		अगर (recv_indicatepkt_reorder(padapter, prframe)) अणु
			/* including perक्रमm A-MPDU Rx Ordering Buffer Control*/
			अगर (!padapter->driver_stopped &&
			    !padapter->surprise_हटाओd)
				वापस _FAIL;
		पूर्ण
	पूर्ण अन्यथा अणु /*B/G mode*/
		retval = r8712_wlanhdr_to_ethhdr(prframe);
		अगर (retval)
			वापस _FAIL;
		अगर (!padapter->driver_stopped && !padapter->surprise_हटाओd) अणु
			/* indicate this recv_frame */
			r8712_recv_indicatepkt(padapter, prframe);
		पूर्ण अन्यथा अणु
			वापस _FAIL;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

अटल u8 query_rx_pwr_percentage(s8 antघातer)
अणु
	अगर ((antघातer <= -100) || (antघातer >= 20))
		वापस	0;
	अन्यथा अगर (antघातer >= 0)
		वापस	100;
	अन्यथा
		वापस 100 + antघातer;
पूर्ण

अटल u8 evm_db2percentage(s8 value)
अणु
	/*
	 * -33dB~0dB to 0%~99%
	 */
	s8 ret_val = clamp(-value, 0, 33) * 3;

	अगर (ret_val == 99)
		ret_val = 100;

	वापस ret_val;
पूर्ण

s32 r8712_संकेत_scale_mapping(s32 cur_sig)
अणु
	s32 ret_sig;

	अगर (cur_sig >= 51 && cur_sig <= 100)
		ret_sig = 100;
	अन्यथा अगर (cur_sig >= 41 && cur_sig <= 50)
		ret_sig = 80 + ((cur_sig - 40) * 2);
	अन्यथा अगर (cur_sig >= 31 && cur_sig <= 40)
		ret_sig = 66 + (cur_sig - 30);
	अन्यथा अगर (cur_sig >= 21 && cur_sig <= 30)
		ret_sig = 54 + (cur_sig - 20);
	अन्यथा अगर (cur_sig >= 10 && cur_sig <= 20)
		ret_sig = 42 + (((cur_sig - 10) * 2) / 3);
	अन्यथा अगर (cur_sig >= 5 && cur_sig <= 9)
		ret_sig = 22 + (((cur_sig - 5) * 3) / 2);
	अन्यथा अगर (cur_sig >= 1 && cur_sig <= 4)
		ret_sig = 6 + (((cur_sig - 1) * 3) / 2);
	अन्यथा
		ret_sig = cur_sig;
	वापस ret_sig;
पूर्ण

अटल s32  translate2dbm(काष्ठा _adapter *padapter, u8 संकेत_strength_idx)
अणु
	s32 संकेत_घातer; /* in dBm.*/
	/* Translate to dBm (x=0.5y-95).*/
	संकेत_घातer = (s32)((संकेत_strength_idx + 1) >> 1);
	संकेत_घातer -= 95;
	वापस संकेत_घातer;
पूर्ण

अटल व्योम query_rx_phy_status(काष्ठा _adapter *padapter,
				जोड़ recv_frame *prframe)
अणु
	u8 i, max_spatial_stream, evm;
	काष्ठा recv_stat *prxstat = (काष्ठा recv_stat *)prframe->u.hdr.rx_head;
	काष्ठा phy_stat *pphy_stat = (काष्ठा phy_stat *)(prxstat + 1);
	u8 *pphy_head = (u8 *)(prxstat + 1);
	s8 rx_pwr[4], rx_pwr_all;
	u8 pwdb_all;
	u32 rssi, total_rssi = 0;
	u8 bcck_rate = 0, rf_rx_num = 0, cck_highpwr = 0;
	काष्ठा phy_cck_rx_status *pcck_buf;
	u8 sq;

	/* Record it क्रम next packet processing*/
	bcck_rate = (prframe->u.hdr.attrib.mcs_rate <= 3 ? 1 : 0);
	अगर (bcck_rate) अणु
		u8 report;

		/* CCK Driver info Structure is not the same as OFDM packet.*/
		pcck_buf = (काष्ठा phy_cck_rx_status *)pphy_stat;
		/* (1)Hardware करोes not provide RSSI क्रम CCK
		 * (2)PWDB, Average PWDB calculated by hardware
		 * (क्रम rate adaptive)
		 */
		अगर (!cck_highpwr) अणु
			report = pcck_buf->cck_agc_rpt & 0xc0;
			report >>= 6;
			चयन (report) अणु
			/* Modअगरy the RF RNA gain value to -40, -20,
			 * -2, 14 by Jenyu's suggestion
			 * Note: dअगरferent RF with the dअगरferent
			 * RNA gain.
			 */
			हाल 0x3:
				rx_pwr_all = -40 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -20 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -2 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 14 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			report = ((u8)(le32_to_cpu(pphy_stat->phydw1) >> 8)) &
				 0x60;
			report >>= 5;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -40 - ((pcck_buf->cck_agc_rpt &
					     0x1f) << 1);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -20 - ((pcck_buf->cck_agc_rpt &
					     0x1f) << 1);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -2 - ((pcck_buf->cck_agc_rpt &
					     0x1f) << 1);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 14 - ((pcck_buf->cck_agc_rpt &
					     0x1f) << 1);
				अवरोध;
			पूर्ण
		पूर्ण
		pwdb_all = query_rx_pwr_percentage(rx_pwr_all);
		/* CCK gain is smaller than OFDM/MCS gain,*/
		/* so we add gain dअगरf by experiences, the val is 6 */
		pwdb_all += 6;
		अगर (pwdb_all > 100)
			pwdb_all = 100;
		/* modअगरy the offset to make the same gain index with OFDM.*/
		अगर (pwdb_all > 34 && pwdb_all <= 42)
			pwdb_all -= 2;
		अन्यथा अगर (pwdb_all > 26 && pwdb_all <= 34)
			pwdb_all -= 6;
		अन्यथा अगर (pwdb_all > 14 && pwdb_all <= 26)
			pwdb_all -= 8;
		अन्यथा अगर (pwdb_all > 4 && pwdb_all <= 14)
			pwdb_all -= 4;
		/*
		 * (3) Get Signal Quality (EVM)
		 */
		अगर (pwdb_all > 40) अणु
			sq = 100;
		पूर्ण अन्यथा अणु
			sq = pcck_buf->sq_rpt;
			अगर (pcck_buf->sq_rpt > 64)
				sq = 0;
			अन्यथा अगर (pcck_buf->sq_rpt < 20)
				sq = 100;
			अन्यथा
				sq = ((64 - sq) * 100) / 44;
		पूर्ण
		prframe->u.hdr.attrib.संकेत_qual = sq;
		prframe->u.hdr.attrib.rx_mimo_संकेत_qual[0] = sq;
		prframe->u.hdr.attrib.rx_mimo_संकेत_qual[1] = -1;
	पूर्ण अन्यथा अणु
		/* (1)Get RSSI क्रम HT rate */
		क्रम (i = 0; i < ((padapter->registrypriv.rf_config) &
			    0x0f); i++) अणु
			rf_rx_num++;
			rx_pwr[i] = ((pphy_head[PHY_STAT_GAIN_TRSW_SHT + i]
				    & 0x3F) * 2) - 110;
			/* Translate DBM to percentage. */
			rssi = query_rx_pwr_percentage(rx_pwr[i]);
			total_rssi += rssi;
		पूर्ण
		/* (2)PWDB, Average PWDB calculated by hardware (क्रम
		 * rate adaptive)
		 */
		rx_pwr_all = (((pphy_head[PHY_STAT_PWDB_ALL_SHT]) >> 1) & 0x7f)
			     - 106;
		pwdb_all = query_rx_pwr_percentage(rx_pwr_all);

		अणु
			/* (3)EVM of HT rate */
			अगर (prframe->u.hdr.attrib.htc &&
			    prframe->u.hdr.attrib.mcs_rate >= 20 &&
			    prframe->u.hdr.attrib.mcs_rate <= 27) अणु
				/* both spatial stream make sense */
				max_spatial_stream = 2;
			पूर्ण अन्यथा अणु
				/* only spatial stream 1 makes sense */
				max_spatial_stream = 1;
			पूर्ण
			क्रम (i = 0; i < max_spatial_stream; i++) अणु
				evm = evm_db2percentage((pphy_head
				      [PHY_STAT_RXEVM_SHT + i]));/*dbm*/
				prframe->u.hdr.attrib.संकेत_qual =
					 (u8)(evm & 0xff);
				prframe->u.hdr.attrib.rx_mimo_संकेत_qual[i] =
					 (u8)(evm & 0xff);
			पूर्ण
		पूर्ण
	पूर्ण
	/* UI BSS List संकेत strength(in percentage), make it good looking,
	 * from 0~100. It is asचिन्हित to the BSS List in
	 * GetValueFromBeaconOrProbeRsp().
	 */
	अगर (bcck_rate) अणु
		prframe->u.hdr.attrib.संकेत_strength =
			 (u8)r8712_संकेत_scale_mapping(pwdb_all);
	पूर्ण अन्यथा अणु
		अगर (rf_rx_num != 0)
			prframe->u.hdr.attrib.संकेत_strength =
				 (u8)(r8712_संकेत_scale_mapping(total_rssi /=
				 rf_rx_num));
	पूर्ण
पूर्ण

अटल व्योम process_link_qual(काष्ठा _adapter *padapter,
			      जोड़ recv_frame *prframe)
अणु
	u32	last_evm = 0, पंचांगpVal;
	काष्ठा rx_pkt_attrib *pattrib;
	काष्ठा smooth_rssi_data *sqd = &padapter->recvpriv.संकेत_qual_data;

	अगर (!prframe || !padapter)
		वापस;
	pattrib = &prframe->u.hdr.attrib;
	अगर (pattrib->संकेत_qual != 0) अणु
		/*
		 * 1. Record the general EVM to the sliding winकरोw.
		 */
		अगर (sqd->total_num++ >= PHY_LINKQUALITY_SLID_WIN_MAX) अणु
			sqd->total_num = PHY_LINKQUALITY_SLID_WIN_MAX;
			last_evm = sqd->elements[sqd->index];
			sqd->total_val -= last_evm;
		पूर्ण
		sqd->total_val += pattrib->संकेत_qual;
		sqd->elements[sqd->index++] = pattrib->संकेत_qual;
		अगर (sqd->index >= PHY_LINKQUALITY_SLID_WIN_MAX)
			sqd->index = 0;

		/* <1> Showed on UI क्रम user, in percentage. */
		पंचांगpVal = sqd->total_val / sqd->total_num;
		padapter->recvpriv.संकेत = (u8)पंचांगpVal;
	पूर्ण
पूर्ण

अटल व्योम process_rssi(काष्ठा _adapter *padapter, जोड़ recv_frame *prframe)
अणु
	u32 last_rssi, पंचांगp_val;
	काष्ठा rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	काष्ठा smooth_rssi_data *ssd = &padapter->recvpriv.संकेत_strength_data;

	अगर (ssd->total_num++ >= PHY_RSSI_SLID_WIN_MAX) अणु
		ssd->total_num = PHY_RSSI_SLID_WIN_MAX;
		last_rssi = ssd->elements[ssd->index];
		ssd->total_val -= last_rssi;
	पूर्ण
	ssd->total_val += pattrib->संकेत_strength;
	ssd->elements[ssd->index++] = pattrib->संकेत_strength;
	अगर (ssd->index >= PHY_RSSI_SLID_WIN_MAX)
		ssd->index = 0;
	पंचांगp_val = ssd->total_val / ssd->total_num;
	padapter->recvpriv.rssi = (s8)translate2dbm(padapter, (u8)पंचांगp_val);
पूर्ण

अटल व्योम process_phy_info(काष्ठा _adapter *padapter,
			     जोड़ recv_frame *prframe)
अणु
	query_rx_phy_status(padapter, prframe);
	process_rssi(padapter, prframe);
	process_link_qual(padapter,  prframe);
पूर्ण

पूर्णांक recv_func(काष्ठा _adapter *padapter, व्योम *pcontext)
अणु
	काष्ठा rx_pkt_attrib *pattrib;
	जोड़ recv_frame *prframe, *orig_prframe;
	पूर्णांक retval = _SUCCESS;
	काष्ठा  __queue *pमुक्त_recv_queue = &padapter->recvpriv.मुक्त_recv_queue;
	काष्ठा	mlme_priv	*pmlmepriv = &padapter->mlmepriv;

	prframe = pcontext;
	orig_prframe = prframe;
	pattrib = &prframe->u.hdr.attrib;
	अगर (check_fwstate(pmlmepriv, WIFI_MP_STATE)) अणु
		अगर (pattrib->crc_err == 1)
			padapter->mppriv.rx_crcerrpktcount++;
		अन्यथा
			padapter->mppriv.rx_pktcount++;
		अगर (!check_fwstate(pmlmepriv, WIFI_MP_LPBK_STATE)) अणु
			/* मुक्त this recv_frame */
			r8712_मुक्त_recvframe(orig_prframe, pमुक्त_recv_queue);
			जाओ _निकास_recv_func;
		पूर्ण
	पूर्ण
	/* check the frame crtl field and decache */
	retval = r8712_validate_recv_frame(padapter, prframe);
	अगर (retval != _SUCCESS) अणु
		/* मुक्त this recv_frame */
		r8712_मुक्त_recvframe(orig_prframe, pमुक्त_recv_queue);
		जाओ _निकास_recv_func;
	पूर्ण
	process_phy_info(padapter, prframe);
	prframe = r8712_decryptor(padapter, prframe);
	अगर (!prframe) अणु
		retval = _FAIL;
		जाओ _निकास_recv_func;
	पूर्ण
	prframe = r8712_recvframe_chk_defrag(padapter, prframe);
	अगर (!prframe)
		जाओ _निकास_recv_func;
	prframe = r8712_portctrl(padapter, prframe);
	अगर (!prframe) अणु
		retval = _FAIL;
		जाओ _निकास_recv_func;
	पूर्ण
	retval = r8712_process_recv_indicatepkts(padapter, prframe);
	अगर (retval != _SUCCESS) अणु
		r8712_मुक्त_recvframe(orig_prframe, pमुक्त_recv_queue);
		जाओ _निकास_recv_func;
	पूर्ण
_निकास_recv_func:
	वापस retval;
पूर्ण

अटल व्योम recvbuf2recvframe(काष्ठा _adapter *padapter, काष्ठा sk_buff *pskb)
अणु
	u8 *pbuf, shअगरt_sz = 0;
	u8	frag, mf;
	uपूर्णांक	pkt_len;
	u32 transfer_len;
	काष्ठा recv_stat *prxstat;
	u16	pkt_cnt, drvinfo_sz, pkt_offset, पंचांगp_len, alloc_sz;
	काष्ठा  __queue *pमुक्त_recv_queue;
	_pkt  *pkt_copy = शून्य;
	जोड़ recv_frame *precvframe = शून्य;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;

	pमुक्त_recv_queue = &(precvpriv->मुक्त_recv_queue);
	pbuf = pskb->data;
	prxstat = (काष्ठा recv_stat *)pbuf;
	pkt_cnt = (le32_to_cpu(prxstat->rxdw2) >> 16) & 0xff;
	pkt_len =  le32_to_cpu(prxstat->rxdw0) & 0x00003fff;
	transfer_len = pskb->len;
	/* Test throughput with Netgear 3700 (No security) with Chariot 3T3R
	 * pairs. The packet count will be a big number so that the containing
	 * packet will effect the Rx reordering.
	 */
	अगर (transfer_len < pkt_len) अणु
		/* In this हाल, it means the MAX_RECVBUF_SZ is too small to
		 * get the data from 8712u.
		 */
		वापस;
	पूर्ण
	करो अणु
		prxstat = (काष्ठा recv_stat *)pbuf;
		pkt_len =  le32_to_cpu(prxstat->rxdw0) & 0x00003fff;
		/* more fragment bit */
		mf = (le32_to_cpu(prxstat->rxdw1) >> 27) & 0x1;
		/* ragmentation number */
		frag = (le32_to_cpu(prxstat->rxdw2) >> 12) & 0xf;
		/* uपूर्णांक 2^3 = 8 bytes */
		drvinfo_sz = (le32_to_cpu(prxstat->rxdw0) & 0x000f0000) >> 16;
		drvinfo_sz <<= 3;
		अगर (pkt_len <= 0)
			वापस;
		/* Qos data, wireless lan header length is 26 */
		अगर ((le32_to_cpu(prxstat->rxdw0) >> 23) & 0x01)
			shअगरt_sz = 2;
		precvframe = r8712_alloc_recvframe(pमुक्त_recv_queue);
		अगर (!precvframe)
			वापस;
		INIT_LIST_HEAD(&precvframe->u.hdr.list);
		precvframe->u.hdr.precvbuf = शून्य; /*can't access the precvbuf*/
		precvframe->u.hdr.len = 0;
		पंचांगp_len = pkt_len + drvinfo_sz + RXDESC_SIZE;
		pkt_offset = (u16)round_up(पंचांगp_len, 128);
		/* क्रम first fragment packet, driver need allocate 1536 +
		 * drvinfo_sz + RXDESC_SIZE to defrag packet.
		 */
		अगर ((mf == 1) && (frag == 0))
			/*1658+6=1664, 1664 is 128 alignment.*/
			alloc_sz = max_t(u16, पंचांगp_len, 1658);
		अन्यथा
			alloc_sz = पंचांगp_len;
		/* 2 is क्रम IP header 4 bytes alignment in QoS packet हाल.
		 * 4 is क्रम skb->data 4 bytes alignment.
		 */
		alloc_sz += 6;
		pkt_copy = netdev_alloc_skb(padapter->pnetdev, alloc_sz);
		अगर (!pkt_copy)
			वापस;

		precvframe->u.hdr.pkt = pkt_copy;
		skb_reserve(pkt_copy, 4 - ((addr_t)(pkt_copy->data) % 4));
		skb_reserve(pkt_copy, shअगरt_sz);
		स_नकल(pkt_copy->data, pbuf, पंचांगp_len);
		precvframe->u.hdr.rx_head = precvframe->u.hdr.rx_data =
			precvframe->u.hdr.rx_tail = pkt_copy->data;
		precvframe->u.hdr.rx_end = pkt_copy->data + alloc_sz;

		recvframe_put(precvframe, पंचांगp_len);
		recvframe_pull(precvframe, drvinfo_sz + RXDESC_SIZE);
		/* because the endian issue, driver aव्योम reference to the
		 * rxstat after calling update_recvframe_attrib_from_recvstat();
		 */
		update_recvframe_attrib_from_recvstat(&precvframe->u.hdr.attrib,
						      prxstat);
		r8712_recv_entry(precvframe);
		transfer_len -= pkt_offset;
		pbuf += pkt_offset;
		pkt_cnt--;
		precvframe = शून्य;
		pkt_copy = शून्य;
	पूर्ण जबतक ((transfer_len > 0) && pkt_cnt > 0);
पूर्ण

अटल व्योम recv_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sk_buff *pskb;
	काष्ठा _adapter *padapter = from_tasklet(padapter, t,
						 recvpriv.recv_tasklet);
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;

	जबतक (शून्य != (pskb = skb_dequeue(&precvpriv->rx_skb_queue))) अणु
		recvbuf2recvframe(padapter, pskb);
		skb_reset_tail_poपूर्णांकer(pskb);
		pskb->len = 0;
		अगर (!skb_cloned(pskb))
			skb_queue_tail(&precvpriv->मुक्त_recv_skb_queue, pskb);
		अन्यथा
			consume_skb(pskb);
	पूर्ण
पूर्ण
