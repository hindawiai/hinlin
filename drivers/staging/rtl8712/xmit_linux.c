<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * xmit_linux.c
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

#घोषणा _XMIT_OSDEP_C_

#समावेश <linux/usb.h>
#समावेश <linux/ip.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/kmemleak.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

#समावेश "wifi.h"
#समावेश "mlme_osdep.h"
#समावेश "xmit_osdep.h"
#समावेश "osdep_intf.h"

अटल uपूर्णांक reमुख्यder_len(काष्ठा pkt_file *pfile)
अणु
	वापस (uपूर्णांक)(pfile->buf_len - ((addr_t)(pfile->cur_addr) -
	       (addr_t)(pfile->buf_start)));
पूर्ण

व्योम _r8712_खोलो_pktfile(_pkt *pktptr, काष्ठा pkt_file *pfile)
अणु
	pfile->pkt = pktptr;
	pfile->cur_addr = pfile->buf_start = pktptr->data;
	pfile->pkt_len = pfile->buf_len = pktptr->len;
	pfile->cur_buffer = pfile->buf_start;
पूर्ण

uपूर्णांक _r8712_pktfile_पढ़ो(काष्ठा pkt_file *pfile, u8 *rmem, uपूर्णांक rlen)
अणु
	uपूर्णांक len;

	len = reमुख्यder_len(pfile);
	len = (rlen > len) ? len : rlen;
	अगर (rmem)
		skb_copy_bits(pfile->pkt, pfile->buf_len - pfile->pkt_len,
			      rmem, len);
	pfile->cur_addr += len;
	pfile->pkt_len -= len;
	वापस len;
पूर्ण

sपूर्णांक r8712_enकरोfpktfile(काष्ठा pkt_file *pfile)
अणु
	वापस (pfile->pkt_len == 0);
पूर्ण


व्योम r8712_set_qos(काष्ठा pkt_file *ppktfile, काष्ठा pkt_attrib *pattrib)
अणु
	काष्ठा ethhdr etherhdr;
	काष्ठा iphdr ip_hdr;
	u16 UserPriority = 0;

	_r8712_खोलो_pktfile(ppktfile->pkt, ppktfile);
	_r8712_pktfile_पढ़ो(ppktfile, (अचिन्हित अक्षर *)&etherhdr, ETH_HLEN);

	/* get UserPriority from IP hdr*/
	अगर (pattrib->ether_type == 0x0800) अणु
		_r8712_pktfile_पढ़ो(ppktfile, (u8 *)&ip_hdr, माप(ip_hdr));
		/*UserPriority = (ntohs(ip_hdr.tos) >> 5) & 0x3 ;*/
		UserPriority = ip_hdr.tos >> 5;
	पूर्ण अन्यथा अणु
		/* "When priority processing of data frames is supported,
		 * a STA's SME should send EAPOL-Key frames at the highest
		 * priority."
		 */

		अगर (pattrib->ether_type == 0x888e)
			UserPriority = 7;
	पूर्ण
	pattrib->priority = UserPriority;
	pattrib->hdrlen = WLAN_HDR_A3_QOS_LEN;
	pattrib->subtype = WIFI_QOS_DATA_TYPE;
पूर्ण

व्योम r8712_SetFilter(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा _adapter *adapter = container_of(work, काष्ठा _adapter,
						wk_filter_rx_ff0);
	u8  oldvalue = 0x00, newvalue = 0x00;
	अचिन्हित दीर्घ irqL;

	oldvalue = r8712_पढ़ो8(adapter, 0x117);
	newvalue = oldvalue & 0xfe;
	r8712_ग_लिखो8(adapter, 0x117, newvalue);

	spin_lock_irqsave(&adapter->lock_rx_ff0_filter, irqL);
	adapter->blnEnableRxFF0Filter = 1;
	spin_unlock_irqrestore(&adapter->lock_rx_ff0_filter, irqL);
	करो अणु
		msleep(100);
	पूर्ण जबतक (adapter->blnEnableRxFF0Filter == 1);
	r8712_ग_लिखो8(adapter, 0x117, oldvalue);
पूर्ण

पूर्णांक r8712_xmit_resource_alloc(काष्ठा _adapter *padapter,
			      काष्ठा xmit_buf *pxmitbuf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		pxmitbuf->pxmit_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!pxmitbuf->pxmit_urb[i]) अणु
			netdev_err(padapter->pnetdev, "pxmitbuf->pxmit_urb[i] == NULL\n");
			वापस -ENOMEM;
		पूर्ण
		kmemleak_not_leak(pxmitbuf->pxmit_urb[i]);
	पूर्ण
	वापस 0;
पूर्ण

व्योम r8712_xmit_resource_मुक्त(काष्ठा _adapter *padapter,
			      काष्ठा xmit_buf *pxmitbuf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (pxmitbuf->pxmit_urb[i]) अणु
			usb_समाप्त_urb(pxmitbuf->pxmit_urb[i]);
			usb_मुक्त_urb(pxmitbuf->pxmit_urb[i]);
		पूर्ण
	पूर्ण
पूर्ण

व्योम r8712_xmit_complete(काष्ठा _adapter *padapter, काष्ठा xmit_frame *pxframe)
अणु
	अगर (pxframe->pkt)
		dev_kमुक्त_skb_any(pxframe->pkt);
	pxframe->pkt = शून्य;
पूर्ण

पूर्णांक r8712_xmit_entry(_pkt *pkt, काष्ठा  net_device *netdev)
अणु
	काष्ठा xmit_frame *xmitframe = शून्य;
	काष्ठा _adapter *adapter = netdev_priv(netdev);
	काष्ठा xmit_priv *xmitpriv = &(adapter->xmitpriv);

	अगर (!r8712_अगर_up(adapter))
		जाओ _xmit_entry_drop;

	xmitframe = r8712_alloc_xmitframe(xmitpriv);
	अगर (!xmitframe)
		जाओ _xmit_entry_drop;

	अगर (r8712_update_attrib(adapter, pkt, &xmitframe->attrib))
		जाओ _xmit_entry_drop;

	adapter->ledpriv.LedControlHandler(adapter, LED_CTL_TX);
	xmitframe->pkt = pkt;
	अगर (r8712_pre_xmit(adapter, xmitframe)) अणु
		/*dump xmitframe directly or drop xframe*/
		dev_kमुक्त_skb_any(pkt);
		xmitframe->pkt = शून्य;
	पूर्ण
	xmitpriv->tx_pkts++;
	xmitpriv->tx_bytes += xmitframe->attrib.last_txcmdsz;
	वापस 0;
_xmit_entry_drop:
	अगर (xmitframe)
		r8712_मुक्त_xmitframe(xmitpriv, xmitframe);
	xmitpriv->tx_drop++;
	dev_kमुक्त_skb_any(pkt);
	वापस 0;
पूर्ण
