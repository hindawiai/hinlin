<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * recv_linux.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>.
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RECV_OSDEP_C_

#समावेश <linux/usb.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "wifi.h"
#समावेश "recv_osdep.h"
#समावेश "osdep_intf.h"
#समावेश "ethernet.h"
#समावेश <linux/अगर_arp.h>
#समावेश "usb_ops.h"

/*init os related resource in काष्ठा recv_priv*/
/*alloc os related resource in जोड़ recv_frame*/
व्योम r8712_os_recv_resource_alloc(काष्ठा _adapter *padapter,
				  जोड़ recv_frame *precvframe)
अणु
	precvframe->u.hdr.pkt_newalloc = शून्य;
	precvframe->u.hdr.pkt = शून्य;
पूर्ण

/*alloc os related resource in काष्ठा recv_buf*/
पूर्णांक r8712_os_recvbuf_resource_alloc(काष्ठा _adapter *padapter,
				    काष्ठा recv_buf *precvbuf)
अणु
	पूर्णांक res = 0;

	precvbuf->irp_pending = false;
	precvbuf->purb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!precvbuf->purb)
		res = -ENOMEM;
	precvbuf->pskb = शून्य;
	precvbuf->pallocated_buf = शून्य;
	precvbuf->pbuf = शून्य;
	precvbuf->pdata = शून्य;
	precvbuf->phead = शून्य;
	precvbuf->ptail = शून्य;
	precvbuf->pend = शून्य;
	precvbuf->transfer_len = 0;
	precvbuf->len = 0;
	वापस res;
पूर्ण

/*मुक्त os related resource in काष्ठा recv_buf*/
व्योम r8712_os_recvbuf_resource_मुक्त(काष्ठा _adapter *padapter,
				    काष्ठा recv_buf *precvbuf)
अणु
	अगर (precvbuf->pskb)
		dev_kमुक्त_skb_any(precvbuf->pskb);
	अगर (precvbuf->purb) अणु
		usb_समाप्त_urb(precvbuf->purb);
		usb_मुक्त_urb(precvbuf->purb);
	पूर्ण
पूर्ण

व्योम r8712_handle_tkip_mic_err(काष्ठा _adapter *adapter, u8 bgroup)
अणु
	जोड़ iwreq_data wrqu;
	काष्ठा iw_michaelmicfailure ev;
	काष्ठा mlme_priv *mlmepriv  = &adapter->mlmepriv;

	स_रखो(&ev, 0x00, माप(ev));
	अगर (bgroup)
		ev.flags |= IW_MICFAILURE_GROUP;
	अन्यथा
		ev.flags |= IW_MICFAILURE_PAIRWISE;
	ev.src_addr.sa_family = ARPHRD_ETHER;
	ether_addr_copy(ev.src_addr.sa_data, &mlmepriv->assoc_bssid[0]);
	स_रखो(&wrqu, 0x00, माप(wrqu));
	wrqu.data.length = माप(ev);
	wireless_send_event(adapter->pnetdev, IWEVMICHAELMICFAILURE, &wrqu,
			    (अक्षर *)&ev);
पूर्ण

व्योम r8712_recv_indicatepkt(काष्ठा _adapter *adapter,
			    जोड़ recv_frame *recvframe)
अणु
	काष्ठा recv_priv *recvpriv;
	काष्ठा  __queue	*मुक्त_recv_queue;
	_pkt *skb;
	काष्ठा rx_pkt_attrib *attrib = &recvframe->u.hdr.attrib;

	recvpriv = &adapter->recvpriv;
	मुक्त_recv_queue = &recvpriv->मुक्त_recv_queue;
	skb = recvframe->u.hdr.pkt;
	अगर (!skb)
		जाओ _recv_indicatepkt_drop;
	skb->data = recvframe->u.hdr.rx_data;
	skb->len = recvframe->u.hdr.len;
	skb_set_tail_poपूर्णांकer(skb, skb->len);
	अगर ((attrib->tcpchk_valid == 1) && (attrib->tcp_chkrpt == 1))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	अन्यथा
		skb->ip_summed = CHECKSUM_NONE;
	skb->dev = adapter->pnetdev;
	skb->protocol = eth_type_trans(skb, adapter->pnetdev);
	netअगर_rx(skb);
	recvframe->u.hdr.pkt = शून्य; /* poपूर्णांकers to शून्य beक्रमe
				      * r8712_मुक्त_recvframe()
				      */
	r8712_मुक्त_recvframe(recvframe, मुक्त_recv_queue);
	वापस;
_recv_indicatepkt_drop:
	 /*enqueue back to मुक्त_recv_queue*/
	अगर (recvframe)
		r8712_मुक्त_recvframe(recvframe, मुक्त_recv_queue);
	recvpriv->rx_drop++;
पूर्ण

अटल व्योम _r8712_reordering_ctrl_समयout_handler (काष्ठा समयr_list *t)
अणु
	काष्ठा recv_reorder_ctrl *reorder_ctrl =
			 from_समयr(reorder_ctrl, t, reordering_ctrl_समयr);

	r8712_reordering_ctrl_समयout_handler(reorder_ctrl);
पूर्ण

व्योम r8712_init_recv_समयr(काष्ठा recv_reorder_ctrl *preorder_ctrl)
अणु
	समयr_setup(&preorder_ctrl->reordering_ctrl_समयr,
		    _r8712_reordering_ctrl_समयout_handler, 0);
पूर्ण
