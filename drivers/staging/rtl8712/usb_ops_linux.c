<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * usb_ops_linux.c
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

#घोषणा _HCI_OPS_OS_C_

#समावेश <linux/usb.h>

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "osdep_intf.h"
#समावेश "usb_ops.h"

#घोषणा	RTL871X_VENQT_READ	0xc0
#घोषणा	RTL871X_VENQT_WRITE	0x40

काष्ठा zero_bulkout_context अणु
	व्योम *pbuf;
	व्योम *purb;
	व्योम *pirp;
	व्योम *padapter;
पूर्ण;

uपूर्णांक r8712_usb_init_पूर्णांकf_priv(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv)
अणु
	pपूर्णांकfpriv->piorw_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!pपूर्णांकfpriv->piorw_urb)
		वापस _FAIL;
	init_completion(&pपूर्णांकfpriv->io_retevt_comp);
	वापस _SUCCESS;
पूर्ण

व्योम r8712_usb_unload_पूर्णांकf_priv(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv)
अणु
	अगर (pपूर्णांकfpriv->piorw_urb) अणु
		usb_समाप्त_urb(pपूर्णांकfpriv->piorw_urb);
		usb_मुक्त_urb(pपूर्णांकfpriv->piorw_urb);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ffaddr2pipehdl(काष्ठा dvobj_priv *pdvobj, u32 addr)
अणु
	अचिन्हित पूर्णांक pipe = 0;
	काष्ठा usb_device *pusbd = pdvobj->pusbdev;

	अगर (pdvobj->nr_endpoपूर्णांक == 11) अणु
		चयन (addr) अणु
		हाल RTL8712_DMA_BKQ:
			pipe = usb_sndbulkpipe(pusbd, 0x07);
			अवरोध;
		हाल RTL8712_DMA_BEQ:
			pipe = usb_sndbulkpipe(pusbd, 0x06);
			अवरोध;
		हाल RTL8712_DMA_VIQ:
			pipe = usb_sndbulkpipe(pusbd, 0x05);
			अवरोध;
		हाल RTL8712_DMA_VOQ:
			pipe = usb_sndbulkpipe(pusbd, 0x04);
			अवरोध;
		हाल RTL8712_DMA_BCNQ:
			pipe = usb_sndbulkpipe(pusbd, 0x0a);
			अवरोध;
		हाल RTL8712_DMA_BMCQ:	/* HI Queue */
			pipe = usb_sndbulkpipe(pusbd, 0x0b);
			अवरोध;
		हाल RTL8712_DMA_MGTQ:
			pipe = usb_sndbulkpipe(pusbd, 0x0c);
			अवरोध;
		हाल RTL8712_DMA_RX0FF:
			pipe = usb_rcvbulkpipe(pusbd, 0x03); /* in */
			अवरोध;
		हाल RTL8712_DMA_C2HCMD:
			pipe = usb_rcvbulkpipe(pusbd, 0x09); /* in */
			अवरोध;
		हाल RTL8712_DMA_H2CCMD:
			pipe = usb_sndbulkpipe(pusbd, 0x0d);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (pdvobj->nr_endpoपूर्णांक == 6) अणु
		चयन (addr) अणु
		हाल RTL8712_DMA_BKQ:
			pipe = usb_sndbulkpipe(pusbd, 0x07);
			अवरोध;
		हाल RTL8712_DMA_BEQ:
			pipe = usb_sndbulkpipe(pusbd, 0x06);
			अवरोध;
		हाल RTL8712_DMA_VIQ:
			pipe = usb_sndbulkpipe(pusbd, 0x05);
			अवरोध;
		हाल RTL8712_DMA_VOQ:
			pipe = usb_sndbulkpipe(pusbd, 0x04);
			अवरोध;
		हाल RTL8712_DMA_RX0FF:
		हाल RTL8712_DMA_C2HCMD:
			pipe = usb_rcvbulkpipe(pusbd, 0x03); /* in */
			अवरोध;
		हाल RTL8712_DMA_H2CCMD:
		हाल RTL8712_DMA_BCNQ:
		हाल RTL8712_DMA_BMCQ:
		हाल RTL8712_DMA_MGTQ:
			pipe = usb_sndbulkpipe(pusbd, 0x0d);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (pdvobj->nr_endpoपूर्णांक == 4) अणु
		चयन (addr) अणु
		हाल RTL8712_DMA_BEQ:
			pipe = usb_sndbulkpipe(pusbd, 0x06);
			अवरोध;
		हाल RTL8712_DMA_VOQ:
			pipe = usb_sndbulkpipe(pusbd, 0x04);
			अवरोध;
		हाल RTL8712_DMA_RX0FF:
		हाल RTL8712_DMA_C2HCMD:
			pipe = usb_rcvbulkpipe(pusbd, 0x03); /* in */
			अवरोध;
		हाल RTL8712_DMA_H2CCMD:
		हाल RTL8712_DMA_BCNQ:
		हाल RTL8712_DMA_BMCQ:
		हाल RTL8712_DMA_MGTQ:
			pipe = usb_sndbulkpipe(pusbd, 0x0d);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		pipe = 0;
	पूर्ण
	वापस pipe;
पूर्ण

अटल व्योम usb_ग_लिखो_mem_complete(काष्ठा urb *purb)
अणु
	काष्ठा io_queue *pio_q = (काष्ठा io_queue *)purb->context;
	काष्ठा पूर्णांकf_hdl *pपूर्णांकf = &(pio_q->पूर्णांकf);
	काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv = pपूर्णांकf->pपूर्णांकfpriv;
	काष्ठा _adapter *padapter = (काष्ठा _adapter *)pपूर्णांकf->adapter;

	अगर (purb->status != 0) अणु
		अगर (purb->status == (-ESHUTDOWN))
			padapter->driver_stopped = true;
		अन्यथा
			padapter->surprise_हटाओd = true;
	पूर्ण
	complete(&pपूर्णांकfpriv->io_retevt_comp);
पूर्ण

व्योम r8712_usb_ग_लिखो_mem(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *wmem)
अणु
	अचिन्हित पूर्णांक pipe;
	काष्ठा _adapter *padapter = (काष्ठा _adapter *)pपूर्णांकfhdl->adapter;
	काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv = pपूर्णांकfhdl->pपूर्णांकfpriv;
	काष्ठा io_queue *pio_queue = padapter->pio_queue;
	काष्ठा dvobj_priv *pdvobj = (काष्ठा dvobj_priv *)pपूर्णांकfpriv->पूर्णांकf_dev;
	काष्ठा usb_device *pusbd = pdvobj->pusbdev;
	काष्ठा urb *piorw_urb = pपूर्णांकfpriv->piorw_urb;

	अगर ((padapter->driver_stopped) || (padapter->surprise_हटाओd) ||
	    (padapter->pwrctrlpriv.pnp_bstop_trx))
		वापस;
	/* translate DMA FIFO addr to pipehandle */
	pipe = ffaddr2pipehdl(pdvobj, addr);
	अगर (pipe == 0)
		वापस;
	usb_fill_bulk_urb(piorw_urb, pusbd, pipe,
			  wmem, cnt, usb_ग_लिखो_mem_complete,
			  pio_queue);
	usb_submit_urb(piorw_urb, GFP_ATOMIC);
	रुको_क्रम_completion_पूर्णांकerruptible(&pपूर्णांकfpriv->io_retevt_comp);
पूर्ण

अटल व्योम r8712_usb_पढ़ो_port_complete(काष्ठा urb *purb)
अणु
	uपूर्णांक isevt;
	__le32 *pbuf;
	काष्ठा recv_buf	*precvbuf = (काष्ठा recv_buf *)purb->context;
	काष्ठा _adapter *padapter = (काष्ठा _adapter *)precvbuf->adapter;
	काष्ठा recv_priv *precvpriv = &padapter->recvpriv;

	अगर (padapter->surprise_हटाओd || padapter->driver_stopped)
		वापस;
	अगर (purb->status == 0) अणु /* SUCCESS */
		अगर ((purb->actual_length > (MAX_RECVBUF_SZ)) ||
		    (purb->actual_length < RXDESC_SIZE)) अणु
			r8712_पढ़ो_port(padapter, precvpriv->ff_hwaddr, 0,
				  (अचिन्हित अक्षर *)precvbuf);
		पूर्ण अन्यथा अणु
			_pkt *pskb = precvbuf->pskb;

			precvbuf->transfer_len = purb->actual_length;
			pbuf = (__le32 *)precvbuf->pbuf;
			isevt = le32_to_cpu(*(pbuf + 1)) & 0x1ff;
			अगर ((isevt & 0x1ff) == 0x1ff) अणु
				r8712_rxcmd_event_hdl(padapter, pbuf);
				skb_queue_tail(&precvpriv->rx_skb_queue, pskb);
				r8712_पढ़ो_port(padapter, precvpriv->ff_hwaddr,
						0, (अचिन्हित अक्षर *)precvbuf);
			पूर्ण अन्यथा अणु
				skb_put(pskb, purb->actual_length);
				skb_queue_tail(&precvpriv->rx_skb_queue, pskb);
				tasklet_hi_schedule(&precvpriv->recv_tasklet);
				r8712_पढ़ो_port(padapter, precvpriv->ff_hwaddr,
						0, (अचिन्हित अक्षर *)precvbuf);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (purb->status) अणु
		हाल -EINVAL:
		हाल -EPIPE:
		हाल -ENODEV:
		हाल -ESHUTDOWN:
			padapter->driver_stopped = true;
			अवरोध;
		हाल -ENOENT:
			अगर (!padapter->suspended) अणु
				padapter->driver_stopped = true;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल -EPROTO:
			r8712_पढ़ो_port(padapter, precvpriv->ff_hwaddr, 0,
				  (अचिन्हित अक्षर *)precvbuf);
			अवरोध;
		हाल -EINPROGRESS:
			netdev_err(padapter->pnetdev, "ERROR: URB IS IN PROGRESS!\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u32 r8712_usb_पढ़ो_port(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *rmem)
अणु
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err;
	u32 पंचांगpaddr = 0;
	पूर्णांक alignment = 0;
	u32 ret = _SUCCESS;
	काष्ठा urb *purb = शून्य;
	काष्ठा recv_buf	*precvbuf = (काष्ठा recv_buf *)rmem;
	काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv = pपूर्णांकfhdl->pपूर्णांकfpriv;
	काष्ठा dvobj_priv *pdvobj = (काष्ठा dvobj_priv *)pपूर्णांकfpriv->पूर्णांकf_dev;
	काष्ठा _adapter *adapter = pdvobj->padapter;
	काष्ठा recv_priv *precvpriv = &adapter->recvpriv;
	काष्ठा usb_device *pusbd = pdvobj->pusbdev;

	अगर (adapter->driver_stopped || adapter->surprise_हटाओd ||
	    adapter->pwrctrlpriv.pnp_bstop_trx || !precvbuf)
		वापस _FAIL;
	r8712_init_recvbuf(adapter, precvbuf);
	/* Try to use skb from the मुक्त queue */
	precvbuf->pskb = skb_dequeue(&precvpriv->मुक्त_recv_skb_queue);

	अगर (!precvbuf->pskb) अणु
		precvbuf->pskb = netdev_alloc_skb(adapter->pnetdev,
				 MAX_RECVBUF_SZ + RECVBUFF_ALIGN_SZ);
		अगर (!precvbuf->pskb)
			वापस _FAIL;
		पंचांगpaddr = (addr_t)precvbuf->pskb->data;
		alignment = पंचांगpaddr & (RECVBUFF_ALIGN_SZ - 1);
		skb_reserve(precvbuf->pskb,
			    (RECVBUFF_ALIGN_SZ - alignment));
		precvbuf->phead = precvbuf->pskb->head;
		precvbuf->pdata = precvbuf->pskb->data;
		precvbuf->ptail = skb_tail_poपूर्णांकer(precvbuf->pskb);
		precvbuf->pend = skb_end_poपूर्णांकer(precvbuf->pskb);
		precvbuf->pbuf = precvbuf->pskb->data;
	पूर्ण अन्यथा अणु /* skb is reused */
		precvbuf->phead = precvbuf->pskb->head;
		precvbuf->pdata = precvbuf->pskb->data;
		precvbuf->ptail = skb_tail_poपूर्णांकer(precvbuf->pskb);
		precvbuf->pend = skb_end_poपूर्णांकer(precvbuf->pskb);
		precvbuf->pbuf = precvbuf->pskb->data;
	पूर्ण
	purb = precvbuf->purb;
	/* translate DMA FIFO addr to pipehandle */
	pipe = ffaddr2pipehdl(pdvobj, addr);
	usb_fill_bulk_urb(purb, pusbd, pipe,
			  precvbuf->pbuf, MAX_RECVBUF_SZ,
			  r8712_usb_पढ़ो_port_complete,
			  precvbuf);
	err = usb_submit_urb(purb, GFP_ATOMIC);
	अगर ((err) && (err != (-EPERM)))
		ret = _FAIL;
	वापस ret;
पूर्ण

व्योम r8712_usb_पढ़ो_port_cancel(काष्ठा _adapter *padapter)
अणु
	पूर्णांक i;
	काष्ठा recv_buf *precvbuf;

	precvbuf = (काष्ठा recv_buf *)padapter->recvpriv.precv_buf;
	क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
		अगर (precvbuf->purb)
			usb_समाप्त_urb(precvbuf->purb);
		precvbuf++;
	पूर्ण
पूर्ण

व्योम r8712_xmit_bh(काष्ठा tasklet_काष्ठा *t)
अणु
	पूर्णांक ret = false;
	काष्ठा _adapter *padapter = from_tasklet(padapter, t,
						 xmitpriv.xmit_tasklet);
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	अगर (padapter->driver_stopped ||
	    padapter->surprise_हटाओd) अणु
		netdev_err(padapter->pnetdev, "xmit_bh => driver_stopped or surprise_removed\n");
		वापस;
	पूर्ण
	ret = r8712_xmitframe_complete(padapter, pxmitpriv, शून्य);
	अगर (!ret)
		वापस;
	tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);
पूर्ण

अटल व्योम usb_ग_लिखो_port_complete(काष्ठा urb *purb)
अणु
	पूर्णांक i;
	काष्ठा xmit_frame *pxmitframe = (काष्ठा xmit_frame *)purb->context;
	काष्ठा xmit_buf *pxmitbuf = pxmitframe->pxmitbuf;
	काष्ठा _adapter *padapter = pxmitframe->padapter;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;

	चयन (pattrib->priority) अणु
	हाल 1:
	हाल 2:
		pxmitpriv->bkq_cnt--;
		अवरोध;
	हाल 4:
	हाल 5:
		pxmitpriv->viq_cnt--;
		अवरोध;
	हाल 6:
	हाल 7:
		pxmitpriv->voq_cnt--;
		अवरोध;
	हाल 0:
	हाल 3:
	शेष:
		pxmitpriv->beq_cnt--;
		अवरोध;
	पूर्ण
	pxmitpriv->txirp_cnt--;
	क्रम (i = 0; i < 8; i++) अणु
		अगर (purb == pxmitframe->pxmit_urb[i]) अणु
			pxmitframe->bpending[i] = false;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (padapter->surprise_हटाओd)
		वापस;
	चयन (purb->status) अणु
	हाल 0:
		अवरोध;
	शेष:
		netdev_warn(padapter->pnetdev,
				"r8712u: pipe error: (%d)\n", purb->status);
		अवरोध;
	पूर्ण
	/* not to consider tx fragment */
	r8712_मुक्त_xmitframe_ex(pxmitpriv, pxmitframe);
	r8712_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);
	tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);
पूर्ण

u32 r8712_usb_ग_लिखो_port(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *wmem)
अणु
	अचिन्हित दीर्घ irqL;
	पूर्णांक i, status;
	अचिन्हित पूर्णांक pipe;
	u32 ret, bग_लिखोzero;
	काष्ठा urb *purb = शून्य;
	काष्ठा _adapter *padapter = (काष्ठा _adapter *)pपूर्णांकfhdl->adapter;
	काष्ठा dvobj_priv *pdvobj = &padapter->dvobjpriv;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा xmit_frame *pxmitframe = (काष्ठा xmit_frame *)wmem;
	काष्ठा usb_device *pusbd = pdvobj->pusbdev;
	काष्ठा pkt_attrib *pattrib = &pxmitframe->attrib;

	अगर ((padapter->driver_stopped) || (padapter->surprise_हटाओd) ||
	    (padapter->pwrctrlpriv.pnp_bstop_trx))
		वापस _FAIL;
	क्रम (i = 0; i < 8; i++) अणु
		अगर (!pxmitframe->bpending[i]) अणु
			spin_lock_irqsave(&pxmitpriv->lock, irqL);
			pxmitpriv->txirp_cnt++;
			pxmitframe->bpending[i]  = true;
			चयन (pattrib->priority) अणु
			हाल 1:
			हाल 2:
				pxmitpriv->bkq_cnt++;
				अवरोध;
			हाल 4:
			हाल 5:
				pxmitpriv->viq_cnt++;
				अवरोध;
			हाल 6:
			हाल 7:
				pxmitpriv->voq_cnt++;
				अवरोध;
			हाल 0:
			हाल 3:
			शेष:
				pxmitpriv->beq_cnt++;
				अवरोध;
			पूर्ण
			spin_unlock_irqrestore(&pxmitpriv->lock, irqL);
			pxmitframe->sz[i] = (u16)cnt;
			purb = pxmitframe->pxmit_urb[i];
			अवरोध;
		पूर्ण
	पूर्ण
	bग_लिखोzero = false;
	अगर (pdvobj->ishighspeed) अणु
		अगर (cnt > 0 && cnt % 512 == 0)
			bग_लिखोzero = true;
	पूर्ण अन्यथा अणु
		अगर (cnt > 0 && cnt % 64 == 0)
			bग_लिखोzero = true;
	पूर्ण
	/* translate DMA FIFO addr to pipehandle */
	pipe = ffaddr2pipehdl(pdvobj, addr);
	अगर (pxmitpriv->मुक्त_xmitbuf_cnt % NR_XMITBUFF == 0)
		purb->transfer_flags  &=  (~URB_NO_INTERRUPT);
	अन्यथा
		purb->transfer_flags  |=  URB_NO_INTERRUPT;
	अगर (bग_लिखोzero)
		cnt += 8;
	usb_fill_bulk_urb(purb, pusbd, pipe,
			  pxmitframe->mem_addr,
			  cnt, usb_ग_लिखो_port_complete,
			  pxmitframe); /* context is xmit_frame */
	status = usb_submit_urb(purb, GFP_ATOMIC);
	अगर (!status)
		ret = _SUCCESS;
	अन्यथा
		ret = _FAIL;
	वापस ret;
पूर्ण

व्योम r8712_usb_ग_लिखो_port_cancel(काष्ठा _adapter *padapter)
अणु
	पूर्णांक i, j;
	काष्ठा xmit_buf	*pxmitbuf = (काष्ठा xmit_buf *)
				     padapter->xmitpriv.pxmitbuf;

	क्रम (i = 0; i < NR_XMITBUFF; i++) अणु
		क्रम (j = 0; j < 8; j++) अणु
			अगर (pxmitbuf->pxmit_urb[j])
				usb_समाप्त_urb(pxmitbuf->pxmit_urb[j]);
		पूर्ण
		pxmitbuf++;
	पूर्ण
पूर्ण

पूर्णांक r8712_usbctrl_venकरोrreq(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv, u8 request, u16 value,
		      u16 index, व्योम *pdata, u16 len, u8 requesttype)
अणु
	अचिन्हित पूर्णांक pipe;
	पूर्णांक status;
	u8 reqtype;
	काष्ठा dvobj_priv *pdvobjpriv = (काष्ठा dvobj_priv *)
					 pपूर्णांकfpriv->पूर्णांकf_dev;
	काष्ठा usb_device *udev = pdvobjpriv->pusbdev;
	/* For mstar platक्रमm, mstar suggests the address क्रम USB IO
	 * should be 16 bytes alignment. Trying to fix it here.
	 */
	u8 *palloc_buf, *pIo_buf;

	palloc_buf = kदो_स्मृति((u32)len + 16, GFP_ATOMIC);
	अगर (!palloc_buf)
		वापस -ENOMEM;
	pIo_buf = palloc_buf + 16 - ((addr_t)(palloc_buf) & 0x0f);
	अगर (requesttype == 0x01) अणु
		pipe = usb_rcvctrlpipe(udev, 0); /* पढ़ो_in */
		reqtype =  RTL871X_VENQT_READ;
	पूर्ण अन्यथा अणु
		pipe = usb_sndctrlpipe(udev, 0); /* ग_लिखो_out */
		reqtype =  RTL871X_VENQT_WRITE;
		स_नकल(pIo_buf, pdata, len);
	पूर्ण
	status = usb_control_msg(udev, pipe, request, reqtype, value, index,
				 pIo_buf, len, HZ / 2);
	अगर (status > 0) अणु  /* Success this control transfer. */
		अगर (requesttype == 0x01) अणु
			/* For Control पढ़ो transfer, we have to copy the पढ़ो
			 * data from pIo_buf to pdata.
			 */
			स_नकल(pdata, pIo_buf,  status);
		पूर्ण
	पूर्ण
	kमुक्त(palloc_buf);
	वापस status;
पूर्ण
