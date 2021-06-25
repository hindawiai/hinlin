<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Karol Kosik <karo9@पूर्णांकeria.eu>
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 */

#समावेश <net/sock.h>
#समावेश <linux/list.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "usbip_common.h"
#समावेश "vudc.h"

अटल अंतरभूत व्योम setup_base_pdu(काष्ठा usbip_header_basic *base,
				  __u32 command, __u32 seqnum)
अणु
	base->command	= command;
	base->seqnum	= seqnum;
	base->devid	= 0;
	base->ep	= 0;
	base->direction = 0;
पूर्ण

अटल व्योम setup_ret_submit_pdu(काष्ठा usbip_header *rpdu, काष्ठा urbp *urb_p)
अणु
	setup_base_pdu(&rpdu->base, USBIP_RET_SUBMIT, urb_p->seqnum);
	usbip_pack_pdu(rpdu, urb_p->urb, USBIP_RET_SUBMIT, 1);
पूर्ण

अटल व्योम setup_ret_unlink_pdu(काष्ठा usbip_header *rpdu,
				 काष्ठा v_unlink *unlink)
अणु
	setup_base_pdu(&rpdu->base, USBIP_RET_UNLINK, unlink->seqnum);
	rpdu->u.ret_unlink.status = unlink->status;
पूर्ण

अटल पूर्णांक v_send_ret_unlink(काष्ठा vudc *udc, काष्ठा v_unlink *unlink)
अणु
	काष्ठा msghdr msg;
	काष्ठा kvec iov[1];
	माप_प्रकार txsize;

	पूर्णांक ret;
	काष्ठा usbip_header pdu_header;

	txsize = 0;
	स_रखो(&pdu_header, 0, माप(pdu_header));
	स_रखो(&msg, 0, माप(msg));
	स_रखो(&iov, 0, माप(iov));

	/* 1. setup usbip_header */
	setup_ret_unlink_pdu(&pdu_header, unlink);
	usbip_header_correct_endian(&pdu_header, 1);

	iov[0].iov_base = &pdu_header;
	iov[0].iov_len  = माप(pdu_header);
	txsize += माप(pdu_header);

	ret = kernel_sendmsg(udc->ud.tcp_socket, &msg, iov,
			     1, txsize);
	अगर (ret != txsize) अणु
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_TCP);
		अगर (ret >= 0)
			वापस -EPIPE;
		वापस ret;
	पूर्ण
	kमुक्त(unlink);

	वापस txsize;
पूर्ण

अटल पूर्णांक v_send_ret_submit(काष्ठा vudc *udc, काष्ठा urbp *urb_p)
अणु
	काष्ठा urb *urb = urb_p->urb;
	काष्ठा usbip_header pdu_header;
	काष्ठा usbip_iso_packet_descriptor *iso_buffer = शून्य;
	काष्ठा kvec *iov = शून्य;
	पूर्णांक iovnum = 0;
	पूर्णांक ret = 0;
	माप_प्रकार txsize;
	काष्ठा msghdr msg;

	txsize = 0;
	स_रखो(&pdu_header, 0, माप(pdu_header));
	स_रखो(&msg, 0, माप(msg));

	अगर (urb->actual_length > 0 && !urb->transfer_buffer) अणु
		dev_err(&udc->gadget.dev,
			"urb: actual_length %d transfer_buffer null\n",
			urb->actual_length);
		वापस -1;
	पूर्ण

	अगर (urb_p->type == USB_ENDPOINT_XFER_ISOC)
		iovnum = 2 + urb->number_of_packets;
	अन्यथा
		iovnum = 2;

	iov = kसुस्मृति(iovnum, माप(*iov), GFP_KERNEL);
	अगर (!iov) अणु
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_MALLOC);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	iovnum = 0;

	/* 1. setup usbip_header */
	setup_ret_submit_pdu(&pdu_header, urb_p);
	usbip_dbg_stub_tx("setup txdata seqnum: %d\n",
			  pdu_header.base.seqnum);
	usbip_header_correct_endian(&pdu_header, 1);

	iov[iovnum].iov_base = &pdu_header;
	iov[iovnum].iov_len  = माप(pdu_header);
	iovnum++;
	txsize += माप(pdu_header);

	/* 2. setup transfer buffer */
	अगर (urb_p->type != USB_ENDPOINT_XFER_ISOC &&
	    usb_pipein(urb->pipe) && urb->actual_length > 0) अणु
		iov[iovnum].iov_base = urb->transfer_buffer;
		iov[iovnum].iov_len  = urb->actual_length;
		iovnum++;
		txsize += urb->actual_length;
	पूर्ण अन्यथा अगर (urb_p->type == USB_ENDPOINT_XFER_ISOC &&
		usb_pipein(urb->pipe)) अणु
		/* FIXME - copypasted from stub_tx, refactor */
		पूर्णांक i;

		क्रम (i = 0; i < urb->number_of_packets; i++) अणु
			iov[iovnum].iov_base = urb->transfer_buffer +
				urb->iso_frame_desc[i].offset;
			iov[iovnum].iov_len =
				urb->iso_frame_desc[i].actual_length;
			iovnum++;
			txsize += urb->iso_frame_desc[i].actual_length;
		पूर्ण

		अगर (txsize != माप(pdu_header) + urb->actual_length) अणु
			usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_TCP);
			ret = -EPIPE;
			जाओ out;
		पूर्ण
	पूर्ण
	/* अन्यथा - no buffer to send */

	/* 3. setup iso_packet_descriptor */
	अगर (urb_p->type == USB_ENDPOINT_XFER_ISOC) अणु
		sमाप_प्रकार len = 0;

		iso_buffer = usbip_alloc_iso_desc_pdu(urb, &len);
		अगर (!iso_buffer) अणु
			usbip_event_add(&udc->ud,
					VUDC_EVENT_ERROR_MALLOC);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		iov[iovnum].iov_base = iso_buffer;
		iov[iovnum].iov_len  = len;
		txsize += len;
		iovnum++;
	पूर्ण

	ret = kernel_sendmsg(udc->ud.tcp_socket, &msg,
						iov,  iovnum, txsize);
	अगर (ret != txsize) अणु
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_TCP);
		अगर (ret >= 0)
			ret = -EPIPE;
		जाओ out;
	पूर्ण

out:
	kमुक्त(iov);
	kमुक्त(iso_buffer);
	मुक्त_urbp_and_urb(urb_p);
	अगर (ret < 0)
		वापस ret;
	वापस txsize;
पूर्ण

अटल पूर्णांक v_send_ret(काष्ठा vudc *udc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा tx_item *txi;
	माप_प्रकार total_size = 0;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&udc->lock_tx, flags);
	जबतक (!list_empty(&udc->tx_queue)) अणु
		txi = list_first_entry(&udc->tx_queue, काष्ठा tx_item,
				       tx_entry);
		list_del(&txi->tx_entry);
		spin_unlock_irqrestore(&udc->lock_tx, flags);

		चयन (txi->type) अणु
		हाल TX_SUBMIT:
			ret = v_send_ret_submit(udc, txi->s);
			अवरोध;
		हाल TX_UNLINK:
			ret = v_send_ret_unlink(udc, txi->u);
			अवरोध;
		पूर्ण
		kमुक्त(txi);

		अगर (ret < 0)
			वापस ret;

		total_size += ret;

		spin_lock_irqsave(&udc->lock_tx, flags);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock_tx, flags);
	वापस total_size;
पूर्ण


पूर्णांक v_tx_loop(व्योम *data)
अणु
	काष्ठा usbip_device *ud = (काष्ठा usbip_device *) data;
	काष्ठा vudc *udc = container_of(ud, काष्ठा vudc, ud);
	पूर्णांक ret;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (usbip_event_happened(&udc->ud))
			अवरोध;
		ret = v_send_ret(udc);
		अगर (ret < 0) अणु
			pr_warn("v_tx exit with error %d", ret);
			अवरोध;
		पूर्ण
		रुको_event_पूर्णांकerruptible(udc->tx_रुकोq,
					 (!list_empty(&udc->tx_queue) ||
					 kthपढ़ो_should_stop()));
	पूर्ण

	वापस 0;
पूर्ण

/* called with spinlocks held */
व्योम v_enqueue_ret_unlink(काष्ठा vudc *udc, __u32 seqnum, __u32 status)
अणु
	काष्ठा tx_item *txi;
	काष्ठा v_unlink *unlink;

	txi = kzalloc(माप(*txi), GFP_ATOMIC);
	अगर (!txi) अणु
		usbip_event_add(&udc->ud, VDEV_EVENT_ERROR_MALLOC);
		वापस;
	पूर्ण
	unlink = kzalloc(माप(*unlink), GFP_ATOMIC);
	अगर (!unlink) अणु
		kमुक्त(txi);
		usbip_event_add(&udc->ud, VDEV_EVENT_ERROR_MALLOC);
		वापस;
	पूर्ण

	unlink->seqnum = seqnum;
	unlink->status = status;
	txi->type = TX_UNLINK;
	txi->u = unlink;

	list_add_tail(&txi->tx_entry, &udc->tx_queue);
पूर्ण

/* called with spinlocks held */
व्योम v_enqueue_ret_submit(काष्ठा vudc *udc, काष्ठा urbp *urb_p)
अणु
	काष्ठा tx_item *txi;

	txi = kzalloc(माप(*txi), GFP_ATOMIC);
	अगर (!txi) अणु
		usbip_event_add(&udc->ud, VDEV_EVENT_ERROR_MALLOC);
		वापस;
	पूर्ण

	txi->type = TX_SUBMIT;
	txi->s = urb_p;

	list_add_tail(&txi->tx_entry, &udc->tx_queue);
पूर्ण
