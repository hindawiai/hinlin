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

अटल पूर्णांक alloc_urb_from_cmd(काष्ठा urb **urbp,
			      काष्ठा usbip_header *pdu, u8 type)
अणु
	काष्ठा urb *urb;

	अगर (type == USB_ENDPOINT_XFER_ISOC)
		urb = usb_alloc_urb(pdu->u.cmd_submit.number_of_packets,
					  GFP_KERNEL);
	अन्यथा
		urb = usb_alloc_urb(0, GFP_KERNEL);

	अगर (!urb)
		जाओ err;

	usbip_pack_pdu(pdu, urb, USBIP_CMD_SUBMIT, 0);

	अगर (urb->transfer_buffer_length > 0) अणु
		urb->transfer_buffer = kzalloc(urb->transfer_buffer_length,
			GFP_KERNEL);
		अगर (!urb->transfer_buffer)
			जाओ मुक्त_urb;
	पूर्ण

	urb->setup_packet = kmemdup(&pdu->u.cmd_submit.setup, 8,
			    GFP_KERNEL);
	अगर (!urb->setup_packet)
		जाओ मुक्त_buffer;

	/*
	 * FIXME - we only setup pipe enough क्रम usbip functions
	 * to behave nicely
	 */
	urb->pipe |= pdu->base.direction == USBIP_सूची_IN ?
			USB_सूची_IN : USB_सूची_OUT;

	*urbp = urb;
	वापस 0;

मुक्त_buffer:
	kमुक्त(urb->transfer_buffer);
	urb->transfer_buffer = शून्य;
मुक्त_urb:
	usb_मुक्त_urb(urb);
err:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक v_recv_cmd_unlink(काष्ठा vudc *udc,
				काष्ठा usbip_header *pdu)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा urbp *urb_p;

	spin_lock_irqsave(&udc->lock, flags);
	list_क्रम_each_entry(urb_p, &udc->urb_queue, urb_entry) अणु
		अगर (urb_p->seqnum != pdu->u.cmd_unlink.seqnum)
			जारी;
		urb_p->urb->unlinked = -ECONNRESET;
		urb_p->seqnum = pdu->base.seqnum;
		v_kick_समयr(udc, jअगरfies);
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस 0;
	पूर्ण
	/* Not found, completed / not queued */
	spin_lock(&udc->lock_tx);
	v_enqueue_ret_unlink(udc, pdu->base.seqnum, 0);
	wake_up(&udc->tx_रुकोq);
	spin_unlock(&udc->lock_tx);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक v_recv_cmd_submit(काष्ठा vudc *udc,
				 काष्ठा usbip_header *pdu)
अणु
	पूर्णांक ret = 0;
	काष्ठा urbp *urb_p;
	u8 address;
	अचिन्हित दीर्घ flags;

	urb_p = alloc_urbp();
	अगर (!urb_p) अणु
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_MALLOC);
		वापस -ENOMEM;
	पूर्ण

	/* base.ep is pipeendpoपूर्णांक(pipe) */
	address = pdu->base.ep;
	अगर (pdu->base.direction == USBIP_सूची_IN)
		address |= USB_सूची_IN;

	spin_lock_irq(&udc->lock);
	urb_p->ep = vudc_find_endpoपूर्णांक(udc, address);
	अगर (!urb_p->ep) अणु
		/* we करोn't know the type, there may be isoc data! */
		dev_err(&udc->pdev->dev, "request to nonexistent endpoint");
		spin_unlock_irq(&udc->lock);
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_TCP);
		ret = -EPIPE;
		जाओ मुक्त_urbp;
	पूर्ण
	urb_p->type = urb_p->ep->type;
	spin_unlock_irq(&udc->lock);

	urb_p->new = 1;
	urb_p->seqnum = pdu->base.seqnum;

	अगर (urb_p->ep->type == USB_ENDPOINT_XFER_ISOC) अणु
		/* validate packet size and number of packets */
		अचिन्हित पूर्णांक maxp, packets, bytes;

		maxp = usb_endpoपूर्णांक_maxp(urb_p->ep->desc);
		maxp *= usb_endpoपूर्णांक_maxp_mult(urb_p->ep->desc);
		bytes = pdu->u.cmd_submit.transfer_buffer_length;
		packets = DIV_ROUND_UP(bytes, maxp);

		अगर (pdu->u.cmd_submit.number_of_packets < 0 ||
		    pdu->u.cmd_submit.number_of_packets > packets) अणु
			dev_err(&udc->gadget.dev,
				"CMD_SUBMIT: isoc invalid num packets %d\n",
				pdu->u.cmd_submit.number_of_packets);
			ret = -EMSGSIZE;
			जाओ मुक्त_urbp;
		पूर्ण
	पूर्ण

	ret = alloc_urb_from_cmd(&urb_p->urb, pdu, urb_p->ep->type);
	अगर (ret) अणु
		usbip_event_add(&udc->ud, VUDC_EVENT_ERROR_MALLOC);
		ret = -ENOMEM;
		जाओ मुक्त_urbp;
	पूर्ण

	urb_p->urb->status = -EINPROGRESS;

	/* FIXME: more pipe setup to please usbip_common */
	urb_p->urb->pipe &= ~(3 << 30);
	चयन (urb_p->ep->type) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		urb_p->urb->pipe |= (PIPE_BULK << 30);
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		urb_p->urb->pipe |= (PIPE_INTERRUPT << 30);
		अवरोध;
	हाल USB_ENDPOINT_XFER_CONTROL:
		urb_p->urb->pipe |= (PIPE_CONTROL << 30);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		urb_p->urb->pipe |= (PIPE_ISOCHRONOUS << 30);
		अवरोध;
	पूर्ण
	ret = usbip_recv_xbuff(&udc->ud, urb_p->urb);
	अगर (ret < 0)
		जाओ मुक्त_urbp;

	ret = usbip_recv_iso(&udc->ud, urb_p->urb);
	अगर (ret < 0)
		जाओ मुक्त_urbp;

	spin_lock_irqsave(&udc->lock, flags);
	v_kick_समयr(udc, jअगरfies);
	list_add_tail(&urb_p->urb_entry, &udc->urb_queue);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;

मुक्त_urbp:
	मुक्त_urbp_and_urb(urb_p);
	वापस ret;
पूर्ण

अटल पूर्णांक v_rx_pdu(काष्ठा usbip_device *ud)
अणु
	पूर्णांक ret;
	काष्ठा usbip_header pdu;
	काष्ठा vudc *udc = container_of(ud, काष्ठा vudc, ud);

	स_रखो(&pdu, 0, माप(pdu));
	ret = usbip_recv(ud->tcp_socket, &pdu, माप(pdu));
	अगर (ret != माप(pdu)) अणु
		usbip_event_add(ud, VUDC_EVENT_ERROR_TCP);
		अगर (ret >= 0)
			वापस -EPIPE;
		वापस ret;
	पूर्ण
	usbip_header_correct_endian(&pdu, 0);

	spin_lock_irq(&ud->lock);
	ret = (ud->status == SDEV_ST_USED);
	spin_unlock_irq(&ud->lock);
	अगर (!ret) अणु
		usbip_event_add(ud, VUDC_EVENT_ERROR_TCP);
		वापस -EBUSY;
	पूर्ण

	चयन (pdu.base.command) अणु
	हाल USBIP_CMD_UNLINK:
		ret = v_recv_cmd_unlink(udc, &pdu);
		अवरोध;
	हाल USBIP_CMD_SUBMIT:
		ret = v_recv_cmd_submit(udc, &pdu);
		अवरोध;
	शेष:
		ret = -EPIPE;
		pr_err("rx: unknown command");
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक v_rx_loop(व्योम *data)
अणु
	काष्ठा usbip_device *ud = data;
	पूर्णांक ret = 0;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (usbip_event_happened(ud))
			अवरोध;
		ret = v_rx_pdu(ud);
		अगर (ret < 0) अणु
			pr_warn("v_rx exit with error %d", ret);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
