<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _USB_OPS_LINUX_C_

#समावेश <drv_types.h>
#समावेश <recv_osdep.h>
#समावेश <rtw_sreset.h>

#घोषणा RTW_USB_CONTROL_MSG_TIMEOUT	500 /* ms */

#घोषणा MAX_USBCTRL_VENDORREQ_TIMES	10

#घोषणा ALIGNMENT_UNIT			16
#घोषणा MAX_VENDOR_REQ_CMD_SIZE	254
#घोषणा MAX_USB_IO_CTL_SIZE	(MAX_VENDOR_REQ_CMD_SIZE + ALIGNMENT_UNIT)

#घोषणा REALTEK_USB_VENQT_READ	(USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE)
#घोषणा REALTEK_USB_VENQT_WRITE	(USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE)

#घोषणा REALTEK_USB_VENQT_CMD_REQ	0x05
#घोषणा REALTEK_USB_VENQT_CMD_IDX	0x00

अटल व्योम पूर्णांकerrupt_handler_8188eu(काष्ठा adapter *adapt, u16 pkt_len, u8 *pbuf)
अणु
	काष्ठा hal_data_8188e *haldata = adapt->HalData;

	अगर (pkt_len != INTERRUPT_MSG_FORMAT_LEN) अणु
		DBG_88E("%s Invalid interrupt content length (%d)!\n", __func__, pkt_len);
		वापस;
	पूर्ण

	/*  HISR */
	स_नकल(&haldata->IntArray[0], &pbuf[USB_INTR_CONTENT_HISR_OFFSET], 4);
	स_नकल(&haldata->IntArray[1], &pbuf[USB_INTR_CONTENT_HISRE_OFFSET], 4);

	/*  C2H Event */
	अगर (pbuf[0] != 0)
		स_नकल(&haldata->C2hArray[0],
		       &pbuf[USB_INTR_CONTENT_C2H_OFFSET], 16);
पूर्ण

अटल पूर्णांक recvbuf2recvframe(काष्ठा adapter *adapt, काष्ठा sk_buff *pskb)
अणु
	u8 *pbuf;
	u8 shअगरt_sz = 0;
	u16 pkt_cnt;
	u32 pkt_offset, skb_len, alloc_sz;
	s32 transfer_len;
	काष्ठा recv_stat *prxstat;
	काष्ठा phy_stat *pphy_status = शून्य;
	काष्ठा sk_buff *pkt_copy = शून्य;
	काष्ठा recv_frame *precvframe = शून्य;
	काष्ठा rx_pkt_attrib *pattrib = शून्य;
	काष्ठा hal_data_8188e *haldata = adapt->HalData;
	काष्ठा recv_priv *precvpriv = &adapt->recvpriv;
	काष्ठा __queue *pमुक्त_recv_queue = &precvpriv->मुक्त_recv_queue;

	transfer_len = (s32)pskb->len;
	pbuf = pskb->data;

	prxstat = (काष्ठा recv_stat *)pbuf;
	pkt_cnt = (le32_to_cpu(prxstat->rxdw2) >> 16) & 0xff;

	करो अणु
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
			 ("%s: rxdesc=offsset 0:0x%08x, 4:0x%08x, 8:0x%08x, C:0x%08x\n",
			  __func__, prxstat->rxdw0, prxstat->rxdw1,
			  prxstat->rxdw2, prxstat->rxdw4));

		prxstat = (काष्ठा recv_stat *)pbuf;

		precvframe = rtw_alloc_recvframe(pमुक्त_recv_queue);
		अगर (!precvframe) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
				 ("%s: precvframe==NULL\n", __func__));
			DBG_88E("%s()-%d: rtw_alloc_recvframe() failed! RX Drop!\n", __func__, __LINE__);
			जाओ _निकास_recvbuf2recvframe;
		पूर्ण

		INIT_LIST_HEAD(&precvframe->list);

		update_recvframe_attrib_88e(precvframe, prxstat);

		pattrib = &precvframe->attrib;

		अगर ((pattrib->crc_err) || (pattrib->icv_err)) अणु
			DBG_88E("%s: RX Warning! crc_err=%d icv_err=%d, skip!\n", __func__, pattrib->crc_err, pattrib->icv_err);

			rtw_मुक्त_recvframe(precvframe, pमुक्त_recv_queue);
			जाओ _निकास_recvbuf2recvframe;
		पूर्ण

		अगर ((pattrib->physt) && (pattrib->pkt_rpt_type == NORMAL_RX))
			pphy_status = (काष्ठा phy_stat *)(pbuf + RXDESC_OFFSET);

		pkt_offset = RXDESC_SIZE + pattrib->drvinfo_sz + pattrib->shअगरt_sz + pattrib->pkt_len;

		अगर ((pattrib->pkt_len <= 0) || (pkt_offset > transfer_len)) अणु
			RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
				 ("%s: pkt_len<=0\n", __func__));
			DBG_88E("%s()-%d: RX Warning!,pkt_len<=0 or pkt_offset> transfer_len\n", __func__, __LINE__);
			rtw_मुक्त_recvframe(precvframe, pमुक्त_recv_queue);
			जाओ _निकास_recvbuf2recvframe;
		पूर्ण

		/*	Modअगरied by Albert 20101213 */
		/*	For 8 bytes IP header alignment. */
		अगर (pattrib->qos)	/*	Qos data, wireless lan header length is 26 */
			shअगरt_sz = 6;
		अन्यथा
			shअगरt_sz = 0;

		skb_len = pattrib->pkt_len;

		/*  क्रम first fragment packet, driver need allocate 1536+drvinfo_sz+RXDESC_SIZE to defrag packet. */
		/*  modअगरy alloc_sz क्रम recvive crc error packet by thomas 2011-06-02 */
		अगर ((pattrib->mfrag == 1) && (pattrib->frag_num == 0)) अणु
			अगर (skb_len <= 1650)
				alloc_sz = 1664;
			अन्यथा
				alloc_sz = skb_len + 14;
		पूर्ण अन्यथा अणु
			alloc_sz = skb_len;
			/*	6 is क्रम IP header 8 bytes alignment in QoS packet हाल. */
			/*	8 is क्रम skb->data 4 bytes alignment. */
			alloc_sz += 14;
		पूर्ण

		pkt_copy = netdev_alloc_skb(adapt->pnetdev, alloc_sz);
		अगर (pkt_copy) अणु
			pkt_copy->dev = adapt->pnetdev;
			precvframe->pkt = pkt_copy;
			skb_reserve(pkt_copy, 8 - ((माप_प्रकार)(pkt_copy->data) & 7));/* क्रमce pkt_copy->data at 8-byte alignment address */
			skb_reserve(pkt_copy, shअगरt_sz);/* क्रमce ip_hdr at 8-byte alignment address according to shअगरt_sz. */
			skb_put_data(pkt_copy, (pbuf + pattrib->drvinfo_sz + RXDESC_SIZE), skb_len);
		पूर्ण अन्यथा अणु
			DBG_88E("%s: alloc_skb fail , drop frag frame\n",
				__func__);
			rtw_मुक्त_recvframe(precvframe, pमुक्त_recv_queue);
			जाओ _निकास_recvbuf2recvframe;
		पूर्ण

		चयन (haldata->UsbRxAggMode) अणु
		हाल USB_RX_AGG_DMA:
		हाल USB_RX_AGG_MIX:
			pkt_offset = (u16)round_up(pkt_offset, 128);
			अवरोध;
		हाल USB_RX_AGG_USB:
			pkt_offset = (u16)round_up(pkt_offset, 4);
			अवरोध;
		हाल USB_RX_AGG_DISABLE:
		शेष:
			अवरोध;
		पूर्ण
		अगर (pattrib->pkt_rpt_type == NORMAL_RX) अणु /* Normal rx packet */
			अगर (pattrib->physt)
				update_recvframe_phyinfo_88e(precvframe, pphy_status);
			अगर (rtw_recv_entry(precvframe) != _SUCCESS) अणु
				RT_TRACE(_module_rtl871x_recv_c_, _drv_err_,
					 ("%s: rtw_recv_entry(precvframe) != _SUCCESS\n",
					 __func__));
			पूर्ण
		पूर्ण अन्यथा अगर (pattrib->pkt_rpt_type == TX_REPORT1) अणु
			/* CCX-TXRPT ack क्रम xmit mgmt frames. */
			handle_txrpt_ccx_88e(adapt, precvframe->pkt->data);
			rtw_मुक्त_recvframe(precvframe, pमुक्त_recv_queue);
		पूर्ण अन्यथा अगर (pattrib->pkt_rpt_type == TX_REPORT2) अणु
			ODM_RA_TxRPT2Handle_8188E(&haldata->odmpriv,
						  precvframe->pkt->data,
						  pattrib->pkt_len,
						  pattrib->MacIDValidEntry[0],
						  pattrib->MacIDValidEntry[1]);
			rtw_मुक्त_recvframe(precvframe, pमुक्त_recv_queue);
		पूर्ण अन्यथा अगर (pattrib->pkt_rpt_type == HIS_REPORT) अणु
			पूर्णांकerrupt_handler_8188eu(adapt, pattrib->pkt_len, precvframe->pkt->data);
			rtw_मुक्त_recvframe(precvframe, pमुक्त_recv_queue);
		पूर्ण
		pkt_cnt--;
		transfer_len -= pkt_offset;
		pbuf += pkt_offset;
		precvframe = शून्य;
		pkt_copy = शून्य;

		अगर (transfer_len > 0 && pkt_cnt == 0)
			pkt_cnt = (le32_to_cpu(prxstat->rxdw2) >> 16) & 0xff;

	पूर्ण जबतक ((transfer_len > 0) && (pkt_cnt > 0));

_निकास_recvbuf2recvframe:

	वापस _SUCCESS;
पूर्ण

अटल अचिन्हित पूर्णांक ffaddr2pipehdl(काष्ठा dvobj_priv *pdvobj, u32 addr)
अणु
	अचिन्हित पूर्णांक pipe = 0, ep_num = 0;
	काष्ठा usb_device *pusbd = pdvobj->pusbdev;

	अगर (addr == RECV_BULK_IN_ADDR) अणु
		pipe = usb_rcvbulkpipe(pusbd, pdvobj->RtInPipe[0]);
	पूर्ण अन्यथा अगर (addr == RECV_INT_IN_ADDR) अणु
		pipe = usb_rcvbulkpipe(pusbd, pdvobj->RtInPipe[1]);
	पूर्ण अन्यथा अगर (addr < HW_QUEUE_ENTRY) अणु
		ep_num = pdvobj->Queue2Pipe[addr];
		pipe = usb_sndbulkpipe(pusbd, ep_num);
	पूर्ण

	वापस pipe;
पूर्ण

अटल पूर्णांक
usbctrl_venकरोrreq(काष्ठा adapter *adapt, u16 value, व्योम *pdata, u16 len, u8 reqtype)
अणु
	काष्ठा dvobj_priv *dvobjpriv = adapter_to_dvobj(adapt);
	काष्ठा usb_device *udev = dvobjpriv->pusbdev;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक status = 0;
	u8 *pIo_buf;
	पूर्णांक venकरोrreq_बार = 0;

	अगर ((adapt->bSurpriseRemoved) || (adapt->pwrctrlpriv.pnp_bstop_trx)) अणु
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("%s:(adapt->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n",
			  __func__));
		status = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर (len > MAX_VENDOR_REQ_CMD_SIZE) अणु
		DBG_88E("[%s] Buffer len error ,vendor request failed\n", __func__);
		status = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&dvobjpriv->usb_venकरोr_req_mutex)) अणु
		status = -ERESTARTSYS;
		जाओ निकास;
	पूर्ण

	/*  Acquire IO memory क्रम venकरोrreq */
	pIo_buf = kदो_स्मृति(MAX_USB_IO_CTL_SIZE, GFP_ATOMIC);

	अगर (!pIo_buf) अणु
		status = -ENOMEM;
		जाओ release_mutex;
	पूर्ण

	अगर (reqtype == REALTEK_USB_VENQT_READ) अणु
		pipe = usb_rcvctrlpipe(udev, 0);
	पूर्ण अन्यथा अगर (reqtype == REALTEK_USB_VENQT_WRITE) अणु
		pipe = usb_sndctrlpipe(udev, 0);
	पूर्ण अन्यथा अणु
		status = -EINVAL;
		जाओ मुक्त_buf;
	पूर्ण

	जबतक (++venकरोrreq_बार <= MAX_USBCTRL_VENDORREQ_TIMES) अणु
		अगर (reqtype == REALTEK_USB_VENQT_READ)
			स_रखो(pIo_buf, 0, len);
		अन्यथा
			स_नकल(pIo_buf, pdata, len);

		status = usb_control_msg(udev, pipe, REALTEK_USB_VENQT_CMD_REQ,
					 reqtype, value, REALTEK_USB_VENQT_CMD_IDX,
					 pIo_buf, len, RTW_USB_CONTROL_MSG_TIMEOUT);

		अगर (status == len) अणु   /*  Success this control transfer. */
			अगर (reqtype == REALTEK_USB_VENQT_READ)
				स_नकल(pdata, pIo_buf,  len);
		पूर्ण अन्यथा अणु /*  error हालs */
			DBG_88E("reg 0x%x, usb %s %u fail, status:%d value=0x%x, vendorreq_times:%d\n",
				value, (reqtype == REALTEK_USB_VENQT_READ) ? "read" : "write",
				len, status, *(u32 *)pdata, venकरोrreq_बार);

			अगर (status < 0) अणु
				अगर (status == -ESHUTDOWN || status == -ENODEV)
					adapt->bSurpriseRemoved = true;
				अन्यथा
					adapt->HalData->srestpriv.wअगरi_error_status = USB_VEN_REQ_CMD_FAIL;
			पूर्ण अन्यथा अणु /*  status != len && status >= 0 */
				अगर (status > 0) अणु
					अगर (reqtype == REALTEK_USB_VENQT_READ) अणु
						/*  For Control पढ़ो transfer, we have to copy the पढ़ो data from pIo_buf to pdata. */
						स_नकल(pdata, pIo_buf,  len);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		/*  firmware करोwnload is checksummed, करोn't retry */
		अगर ((value >= FW_8188E_START_ADDRESS && value <= FW_8188E_END_ADDRESS) || status == len)
			अवरोध;
	पूर्ण

मुक्त_buf:
	kमुक्त(pIo_buf);
release_mutex:
	mutex_unlock(&dvobjpriv->usb_venकरोr_req_mutex);
निकास:
	वापस status;
पूर्ण

u8 usb_पढ़ो8(काष्ठा adapter *adapter, u32 addr)
अणु
	u16 wvalue = (u16)(addr & 0xffff);
	u8 data;

	usbctrl_venकरोrreq(adapter, wvalue, &data, 1, REALTEK_USB_VENQT_READ);

	वापस data;
पूर्ण

u16 usb_पढ़ो16(काष्ठा adapter *adapter, u32 addr)
अणु
	u16 wvalue = (u16)(addr & 0xffff);
	__le32 data;

	usbctrl_venकरोrreq(adapter, wvalue, &data, 2, REALTEK_USB_VENQT_READ);

	वापस (u16)(le32_to_cpu(data) & 0xffff);
पूर्ण

u32 usb_पढ़ो32(काष्ठा adapter *adapter, u32 addr)
अणु
	u16 wvalue = (u16)(addr & 0xffff);
	__le32 data;

	usbctrl_venकरोrreq(adapter, wvalue, &data, 4, REALTEK_USB_VENQT_READ);

	वापस le32_to_cpu(data);
पूर्ण

अटल व्योम usb_पढ़ो_port_complete(काष्ठा urb *purb)
अणु
	काष्ठा recv_buf *precvbuf = (काष्ठा recv_buf *)purb->context;
	काष्ठा adapter *adapt = (काष्ठा adapter *)precvbuf->adapter;
	काष्ठा recv_priv *precvpriv = &adapt->recvpriv;

	RT_TRACE(_module_hci_ops_os_c_, _drv_err_, ("%s!!!\n", __func__));

	अगर (adapt->bSurpriseRemoved || adapt->bDriverStopped || adapt->bReadPortCancel) अणु
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("%s:bDriverStopped(%d) OR bSurpriseRemoved(%d)\n",
			 __func__, adapt->bDriverStopped,
			 adapt->bSurpriseRemoved));

		precvbuf->reuse = true;
		DBG_88E("%s() RX Warning! bDriverStopped(%d) OR bSurpriseRemoved(%d) bReadPortCancel(%d)\n",
			__func__, adapt->bDriverStopped,
			adapt->bSurpriseRemoved, adapt->bReadPortCancel);
		वापस;
	पूर्ण

	अगर (purb->status == 0) अणु /* SUCCESS */
		अगर ((purb->actual_length > MAX_RECVBUF_SZ) || (purb->actual_length < RXDESC_SIZE)) अणु
			RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
				 ("%s: (purb->actual_length > MAX_RECVBUF_SZ) || (purb->actual_length < RXDESC_SIZE)\n",
				 __func__));
			precvbuf->reuse = true;
			usb_पढ़ो_port(adapt, RECV_BULK_IN_ADDR, precvbuf);
			DBG_88E("%s()-%d: RX Warning!\n", __func__, __LINE__);
		पूर्ण अन्यथा अणु
			skb_put(precvbuf->pskb, purb->actual_length);
			skb_queue_tail(&precvpriv->rx_skb_queue, precvbuf->pskb);

			अगर (skb_queue_len(&precvpriv->rx_skb_queue) <= 1)
				tasklet_schedule(&precvpriv->recv_tasklet);

			precvbuf->pskb = शून्य;
			precvbuf->reuse = false;
			usb_पढ़ो_port(adapt, RECV_BULK_IN_ADDR, precvbuf);
		पूर्ण
	पूर्ण अन्यथा अणु
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("%s : purb->status(%d) != 0\n",
			  __func__, purb->status));

		DBG_88E("###=> %s => urb status(%d)\n", __func__, purb->status);
		skb_put(precvbuf->pskb, purb->actual_length);
		precvbuf->pskb = शून्य;

		चयन (purb->status) अणु
		हाल -EINVAL:
		हाल -EPIPE:
		हाल -ENODEV:
		हाल -ESHUTDOWN:
			adapt->bSurpriseRemoved = true;
			fallthrough;
		हाल -ENOENT:
			adapt->bDriverStopped = true;
			RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
				 ("%s:bDriverStopped=true\n", __func__));
			अवरोध;
		हाल -EPROTO:
		हाल -EOVERFLOW:
			adapt->HalData->srestpriv.wअगरi_error_status = USB_READ_PORT_FAIL;
			precvbuf->reuse = true;
			usb_पढ़ो_port(adapt, RECV_BULK_IN_ADDR, precvbuf);
			अवरोध;
		हाल -EINPROGRESS:
			DBG_88E("ERROR: URB IS IN PROGRESS!\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u32 usb_पढ़ो_port(काष्ठा adapter *adapter, u32 addr, काष्ठा recv_buf *precvbuf)
अणु
	काष्ठा urb *purb = शून्य;
	काष्ठा dvobj_priv *pdvobj = adapter_to_dvobj(adapter);
	काष्ठा recv_priv *precvpriv = &adapter->recvpriv;
	काष्ठा usb_device *pusbd = pdvobj->pusbdev;
	पूर्णांक err;
	अचिन्हित पूर्णांक pipe;
	u32 ret = _SUCCESS;

	अगर (adapter->bDriverStopped || adapter->bSurpriseRemoved ||
	    adapter->pwrctrlpriv.pnp_bstop_trx) अणु
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("%s:(adapt->bDriverStopped ||adapt->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n",
			  __func__));
		वापस _FAIL;
	पूर्ण

	अगर (!precvbuf) अणु
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("%s:precvbuf==NULL\n", __func__));
		वापस _FAIL;
	पूर्ण

	अगर (!precvbuf->reuse || !precvbuf->pskb) अणु
		precvbuf->pskb = skb_dequeue(&precvpriv->मुक्त_recv_skb_queue);
		अगर (precvbuf->pskb)
			precvbuf->reuse = true;
	पूर्ण

	/* re-assign क्रम linux based on skb */
	अगर (!precvbuf->reuse || !precvbuf->pskb) अणु
		precvbuf->pskb = netdev_alloc_skb(adapter->pnetdev, MAX_RECVBUF_SZ);
		अगर (!precvbuf->pskb) अणु
			RT_TRACE(_module_hci_ops_os_c_, _drv_err_, ("init_recvbuf(): alloc_skb fail!\n"));
			DBG_88E("#### %s() alloc_skb fail!#####\n", __func__);
			वापस _FAIL;
		पूर्ण
	पूर्ण अन्यथा अणु /* reuse skb */
		precvbuf->reuse = false;
	पूर्ण

	purb = precvbuf->purb;

	/* translate DMA FIFO addr to pipehandle */
	pipe = ffaddr2pipehdl(pdvobj, addr);

	usb_fill_bulk_urb(purb, pusbd, pipe,
			  precvbuf->pskb->data,
			  MAX_RECVBUF_SZ,
			  usb_पढ़ो_port_complete,
			  precvbuf);/* context is precvbuf */

	err = usb_submit_urb(purb, GFP_ATOMIC);
	अगर ((err) && (err != (-EPERM))) अणु
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("cannot submit rx in-token(err=0x%.8x), URB_STATUS =0x%.8x",
			 err, purb->status));
		DBG_88E("cannot submit rx in-token(err = 0x%08x),urb_status = %d\n",
			err, purb->status);
		ret = _FAIL;
	पूर्ण

	वापस ret;
पूर्ण

व्योम rtw_hal_inirp_deinit(काष्ठा adapter *padapter)
अणु
	पूर्णांक i;
	काष्ठा recv_buf *precvbuf;

	precvbuf = padapter->recvpriv.precv_buf;

	DBG_88E("%s\n", __func__);

	padapter->bReadPortCancel = true;

	क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
		precvbuf->reuse = true;
		अगर (precvbuf->purb)
			usb_समाप्त_urb(precvbuf->purb);
		precvbuf++;
	पूर्ण
पूर्ण

पूर्णांक usb_ग_लिखो8(काष्ठा adapter *adapter, u32 addr, u8 val)
अणु
	u16 wvalue = (u16)(addr & 0xffff);
	u8 data = val;

	वापस usbctrl_venकरोrreq(adapter, wvalue, &data, 1, REALTEK_USB_VENQT_WRITE);
पूर्ण

पूर्णांक usb_ग_लिखो16(काष्ठा adapter *adapter, u32 addr, u16 val)
अणु
	u16 wvalue = (u16)(addr & 0xffff);
	__le32 data = cpu_to_le32(val & 0xffff);

	वापस usbctrl_venकरोrreq(adapter, wvalue, &data, 2, REALTEK_USB_VENQT_WRITE);
पूर्ण

पूर्णांक usb_ग_लिखो32(काष्ठा adapter *adapter, u32 addr, u32 val)
अणु
	u16 wvalue = (u16)(addr & 0xffff);
	__le32 data = cpu_to_le32(val);

	वापस usbctrl_venकरोrreq(adapter, wvalue, &data, 4, REALTEK_USB_VENQT_WRITE);
पूर्ण

अटल व्योम usb_ग_लिखो_port_complete(काष्ठा urb *purb)
अणु
	काष्ठा xmit_buf *pxmitbuf = (काष्ठा xmit_buf *)purb->context;
	काष्ठा adapter *padapter = pxmitbuf->padapter;
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;

	चयन (pxmitbuf->flags) अणु
	हाल VO_QUEUE_INX:
		pxmitpriv->voq_cnt--;
		अवरोध;
	हाल VI_QUEUE_INX:
		pxmitpriv->viq_cnt--;
		अवरोध;
	हाल BE_QUEUE_INX:
		pxmitpriv->beq_cnt--;
		अवरोध;
	हाल BK_QUEUE_INX:
		pxmitpriv->bkq_cnt--;
		अवरोध;
	हाल HIGH_QUEUE_INX:
#अगर_घोषित CONFIG_88EU_AP_MODE
		rtw_chk_hi_queue_cmd(padapter);
#पूर्ण_अगर
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (padapter->bSurpriseRemoved || padapter->bDriverStopped ||
	    padapter->bWritePortCancel) अणु
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("%s:bDriverStopped(%d) OR bSurpriseRemoved(%d)",
			  __func__, padapter->bDriverStopped,
			  padapter->bSurpriseRemoved));
		DBG_88E("%s(): TX Warning! bDriverStopped(%d) OR bSurpriseRemoved(%d) bWritePortCancel(%d) pxmitbuf->ext_tag(%x)\n",
			__func__, padapter->bDriverStopped,
			padapter->bSurpriseRemoved, padapter->bReadPortCancel,
			pxmitbuf->ext_tag);

		जाओ check_completion;
	पूर्ण

	अगर (purb->status) अणु
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("%s : purb->status(%d) != 0\n",
			  __func__, purb->status));
		DBG_88E("###=> %s status(%d)\n", __func__, purb->status);
		अगर ((purb->status == -EPIPE) || (purb->status == -EPROTO)) अणु
			sreset_set_wअगरi_error_status(padapter, USB_WRITE_PORT_FAIL);
		पूर्ण अन्यथा अगर (purb->status == -EINPROGRESS) अणु
			RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
				 ("%s: EINPROGRESS\n", __func__));
			जाओ check_completion;
		पूर्ण अन्यथा अगर (purb->status == -ENOENT) अणु
			DBG_88E("%s: -ENOENT\n", __func__);
			जाओ check_completion;
		पूर्ण अन्यथा अगर (purb->status == -ECONNRESET) अणु
			DBG_88E("%s: -ECONNRESET\n", __func__);
			जाओ check_completion;
		पूर्ण अन्यथा अगर (purb->status == -ESHUTDOWN) अणु
			RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
				 ("%s: ESHUTDOWN\n", __func__));
			padapter->bDriverStopped = true;
			RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
				 ("%s:bDriverStopped = true\n", __func__));
			जाओ check_completion;
		पूर्ण अन्यथा अणु
			padapter->bSurpriseRemoved = true;
			DBG_88E("bSurpriseRemoved = true\n");
			RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
				 ("%s:bSurpriseRemoved = true\n", __func__));
			जाओ check_completion;
		पूर्ण
	पूर्ण

check_completion:
	rtw_sctx_करोne_err(&pxmitbuf->sctx,
			  purb->status ? RTW_SCTX_DONE_WRITE_PORT_ERR :
			  RTW_SCTX_DONE_SUCCESS);

	rtw_मुक्त_xmitbuf(pxmitpriv, pxmitbuf);

	tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);
पूर्ण

u32 usb_ग_लिखो_port(काष्ठा adapter *padapter, u32 addr, u32 cnt, काष्ठा xmit_buf *xmitbuf)
अणु
	अचिन्हित दीर्घ irqL;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक status;
	u32 ret = _FAIL;
	काष्ठा urb *purb = शून्य;
	काष्ठा dvobj_priv *pdvobj = adapter_to_dvobj(padapter);
	काष्ठा xmit_priv *pxmitpriv = &padapter->xmitpriv;
	काष्ठा xmit_frame *pxmitframe = (काष्ठा xmit_frame *)xmitbuf->priv_data;
	काष्ठा usb_device *pusbd = pdvobj->pusbdev;

	RT_TRACE(_module_hci_ops_os_c_, _drv_err_, ("+%s\n", __func__));

	अगर ((padapter->bDriverStopped) || (padapter->bSurpriseRemoved) ||
	    (padapter->pwrctrlpriv.pnp_bstop_trx)) अणु
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("%s:( padapter->bDriverStopped ||padapter->bSurpriseRemoved ||adapter->pwrctrlpriv.pnp_bstop_trx)!!!\n",
			  __func__));
		rtw_sctx_करोne_err(&xmitbuf->sctx, RTW_SCTX_DONE_TX_DENY);
		जाओ निकास;
	पूर्ण

	spin_lock_irqsave(&pxmitpriv->lock, irqL);

	चयन (addr) अणु
	हाल VO_QUEUE_INX:
		pxmitpriv->voq_cnt++;
		xmitbuf->flags = VO_QUEUE_INX;
		अवरोध;
	हाल VI_QUEUE_INX:
		pxmitpriv->viq_cnt++;
		xmitbuf->flags = VI_QUEUE_INX;
		अवरोध;
	हाल BE_QUEUE_INX:
		pxmitpriv->beq_cnt++;
		xmitbuf->flags = BE_QUEUE_INX;
		अवरोध;
	हाल BK_QUEUE_INX:
		pxmitpriv->bkq_cnt++;
		xmitbuf->flags = BK_QUEUE_INX;
		अवरोध;
	हाल HIGH_QUEUE_INX:
		xmitbuf->flags = HIGH_QUEUE_INX;
		अवरोध;
	शेष:
		xmitbuf->flags = MGT_QUEUE_INX;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&pxmitpriv->lock, irqL);

	purb	= xmitbuf->pxmit_urb[0];

	/* translate DMA FIFO addr to pipehandle */
	pipe = ffaddr2pipehdl(pdvobj, addr);

	usb_fill_bulk_urb(purb, pusbd, pipe,
			  pxmitframe->buf_addr, /*  xmitbuf->pbuf */
			  cnt,
			  usb_ग_लिखो_port_complete,
			  xmitbuf);/* context is xmitbuf */

	status = usb_submit_urb(purb, GFP_ATOMIC);
	अगर (status) अणु
		rtw_sctx_करोne_err(&xmitbuf->sctx, RTW_SCTX_DONE_WRITE_PORT_ERR);
		DBG_88E("%s, status =%d\n", __func__, status);
		RT_TRACE(_module_hci_ops_os_c_, _drv_err_,
			 ("%s(): usb_submit_urb, status =%x\n",
			  __func__, status));

		अगर (status == -ENODEV)
			padapter->bDriverStopped = true;

		जाओ निकास;
	पूर्ण

	ret = _SUCCESS;

	RT_TRACE(_module_hci_ops_os_c_, _drv_err_, ("-%s\n", __func__));

निकास:
	अगर (ret != _SUCCESS)
		rtw_मुक्त_xmitbuf(pxmitpriv, xmitbuf);
	वापस ret;
पूर्ण

व्योम usb_ग_लिखो_port_cancel(काष्ठा adapter *padapter)
अणु
	पूर्णांक i, j;
	काष्ठा xmit_buf *pxmitbuf = (काष्ठा xmit_buf *)padapter->xmitpriv.pxmitbuf;

	DBG_88E("%s\n", __func__);

	padapter->bWritePortCancel = true;

	क्रम (i = 0; i < NR_XMITBUFF; i++) अणु
		क्रम (j = 0; j < 8; j++) अणु
			अगर (pxmitbuf->pxmit_urb[j])
				usb_समाप्त_urb(pxmitbuf->pxmit_urb[j]);
		पूर्ण
		pxmitbuf++;
	पूर्ण

	pxmitbuf = (काष्ठा xmit_buf *)padapter->xmitpriv.pxmit_extbuf;
	क्रम (i = 0; i < NR_XMIT_EXTBUFF; i++) अणु
		क्रम (j = 0; j < 8; j++) अणु
			अगर (pxmitbuf->pxmit_urb[j])
				usb_समाप्त_urb(pxmitbuf->pxmit_urb[j]);
		पूर्ण
		pxmitbuf++;
	पूर्ण
पूर्ण

व्योम rtl8188eu_recv_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sk_buff *pskb;
	काष्ठा adapter *adapt = from_tasklet(adapt, t, recvpriv.recv_tasklet);
	काष्ठा recv_priv *precvpriv = &adapt->recvpriv;

	जबतक (शून्य != (pskb = skb_dequeue(&precvpriv->rx_skb_queue))) अणु
		अगर ((adapt->bDriverStopped) || (adapt->bSurpriseRemoved)) अणु
			DBG_88E("recv_tasklet => bDriverStopped or bSurpriseRemoved\n");
			dev_kमुक्त_skb_any(pskb);
			अवरोध;
		पूर्ण
		recvbuf2recvframe(adapt, pskb);
		skb_reset_tail_poपूर्णांकer(pskb);
		pskb->len = 0;
		skb_queue_tail(&precvpriv->मुक्त_recv_skb_queue, pskb);
	पूर्ण
पूर्ण

व्योम rtl8188eu_xmit_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा adapter *adapt = from_tasklet(adapt, t, xmitpriv.xmit_tasklet);
	काष्ठा xmit_priv *pxmitpriv = &adapt->xmitpriv;

	अगर (check_fwstate(&adapt->mlmepriv, _FW_UNDER_SURVEY))
		वापस;

	जबतक (1) अणु
		अगर ((adapt->bDriverStopped) ||
		    (adapt->bSurpriseRemoved) ||
		    (adapt->bWritePortCancel)) अणु
			DBG_88E("xmit_tasklet => bDriverStopped or bSurpriseRemoved or bWritePortCancel\n");
			अवरोध;
		पूर्ण

		अगर (!rtl8188eu_xmitframe_complete(adapt, pxmitpriv))
			अवरोध;
	पूर्ण
पूर्ण
