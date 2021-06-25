<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Karol Kosik <karo9@पूर्णांकeria.eu>
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *
 * Based on dummy_hcd.c, which is:
 * Copyright (C) 2003 David Brownell
 * Copyright (C) 2003-2005 Alan Stern
 */

#समावेश <linux/usb.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb/ch9.h>

#समावेश "vudc.h"

#घोषणा DEV_REQUEST	(USB_TYPE_STANDARD | USB_RECIP_DEVICE)
#घोषणा DEV_INREQUEST	(DEV_REQUEST | USB_सूची_IN)
#घोषणा INTF_REQUEST	(USB_TYPE_STANDARD | USB_RECIP_INTERFACE)
#घोषणा INTF_INREQUEST	(INTF_REQUEST | USB_सूची_IN)
#घोषणा EP_REQUEST	(USB_TYPE_STANDARD | USB_RECIP_ENDPOINT)
#घोषणा EP_INREQUEST	(EP_REQUEST | USB_सूची_IN)

अटल पूर्णांक get_frame_limit(क्रमागत usb_device_speed speed)
अणु
	चयन (speed) अणु
	हाल USB_SPEED_LOW:
		वापस 8 /*bytes*/ * 12 /*packets*/;
	हाल USB_SPEED_FULL:
		वापस 64 /*bytes*/ * 19 /*packets*/;
	हाल USB_SPEED_HIGH:
		वापस 512 /*bytes*/ * 13 /*packets*/ * 8 /*uframes*/;
	हाल USB_SPEED_SUPER:
		/* Bus speed is 500000 bytes/ms, so use a little less */
		वापस 490000;
	शेष:
		/* error */
		वापस -1;
	पूर्ण

पूर्ण

/*
 * handle_control_request() - handles all control transfers
 * @udc: poपूर्णांकer to vudc
 * @urb: the urb request to handle
 * @setup: poपूर्णांकer to the setup data क्रम a USB device control
 *	 request
 * @status: poपूर्णांकer to request handling status
 *
 * Return 0 - अगर the request was handled
 *	  1 - अगर the request wasn't handles
 *	  error code on error
 *
 * Adapted from drivers/usb/gadget/udc/dummy_hcd.c
 */
अटल पूर्णांक handle_control_request(काष्ठा vudc *udc, काष्ठा urb *urb,
				  काष्ठा usb_ctrlrequest *setup,
				  पूर्णांक *status)
अणु
	काष्ठा vep	*ep2;
	पूर्णांक		ret_val = 1;
	अचिन्हित पूर्णांक	w_index;
	अचिन्हित पूर्णांक	w_value;

	w_index = le16_to_cpu(setup->wIndex);
	w_value = le16_to_cpu(setup->wValue);
	चयन (setup->bRequest) अणु
	हाल USB_REQ_SET_ADDRESS:
		अगर (setup->bRequestType != DEV_REQUEST)
			अवरोध;
		udc->address = w_value;
		ret_val = 0;
		*status = 0;
		अवरोध;
	हाल USB_REQ_SET_FEATURE:
		अगर (setup->bRequestType == DEV_REQUEST) अणु
			ret_val = 0;
			चयन (w_value) अणु
			हाल USB_DEVICE_REMOTE_WAKEUP:
				अवरोध;
			हाल USB_DEVICE_B_HNP_ENABLE:
				udc->gadget.b_hnp_enable = 1;
				अवरोध;
			हाल USB_DEVICE_A_HNP_SUPPORT:
				udc->gadget.a_hnp_support = 1;
				अवरोध;
			हाल USB_DEVICE_A_ALT_HNP_SUPPORT:
				udc->gadget.a_alt_hnp_support = 1;
				अवरोध;
			शेष:
				ret_val = -EOPNOTSUPP;
			पूर्ण
			अगर (ret_val == 0) अणु
				udc->devstatus |= (1 << w_value);
				*status = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (setup->bRequestType == EP_REQUEST) अणु
			/* endpoपूर्णांक halt */
			ep2 = vudc_find_endpoपूर्णांक(udc, w_index);
			अगर (!ep2 || ep2->ep.name == udc->ep[0].ep.name) अणु
				ret_val = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			ep2->halted = 1;
			ret_val = 0;
			*status = 0;
		पूर्ण
		अवरोध;
	हाल USB_REQ_CLEAR_FEATURE:
		अगर (setup->bRequestType == DEV_REQUEST) अणु
			ret_val = 0;
			चयन (w_value) अणु
			हाल USB_DEVICE_REMOTE_WAKEUP:
				w_value = USB_DEVICE_REMOTE_WAKEUP;
				अवरोध;

			हाल USB_DEVICE_U1_ENABLE:
			हाल USB_DEVICE_U2_ENABLE:
			हाल USB_DEVICE_LTM_ENABLE:
				ret_val = -EOPNOTSUPP;
				अवरोध;
			शेष:
				ret_val = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			अगर (ret_val == 0) अणु
				udc->devstatus &= ~(1 << w_value);
				*status = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (setup->bRequestType == EP_REQUEST) अणु
			/* endpoपूर्णांक halt */
			ep2 = vudc_find_endpoपूर्णांक(udc, w_index);
			अगर (!ep2) अणु
				ret_val = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			अगर (!ep2->wedged)
				ep2->halted = 0;
			ret_val = 0;
			*status = 0;
		पूर्ण
		अवरोध;
	हाल USB_REQ_GET_STATUS:
		अगर (setup->bRequestType == DEV_INREQUEST
				|| setup->bRequestType == INTF_INREQUEST
				|| setup->bRequestType == EP_INREQUEST) अणु
			अक्षर *buf;
			/*
			 * device: remote wakeup, selfघातered
			 * पूर्णांकerface: nothing
			 * endpoपूर्णांक: halt
			 */
			buf = (अक्षर *)urb->transfer_buffer;
			अगर (urb->transfer_buffer_length > 0) अणु
				अगर (setup->bRequestType == EP_INREQUEST) अणु
					ep2 = vudc_find_endpoपूर्णांक(udc, w_index);
					अगर (!ep2) अणु
						ret_val = -EOPNOTSUPP;
						अवरोध;
					पूर्ण
					buf[0] = ep2->halted;
				पूर्ण अन्यथा अगर (setup->bRequestType ==
					   DEV_INREQUEST) अणु
					buf[0] = (u8)udc->devstatus;
				पूर्ण अन्यथा
					buf[0] = 0;
			पूर्ण
			अगर (urb->transfer_buffer_length > 1)
				buf[1] = 0;
			urb->actual_length = min_t(u32, 2,
				urb->transfer_buffer_length);
			ret_val = 0;
			*status = 0;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस ret_val;
पूर्ण

/* Adapted from dummy_hcd.c ; caller must hold lock */
अटल पूर्णांक transfer(काष्ठा vudc *udc,
		काष्ठा urb *urb, काष्ठा vep *ep, पूर्णांक limit)
अणु
	काष्ठा vrequest	*req;
	पूर्णांक sent = 0;
top:
	/* अगर there's no request queued, the device is NAKing; वापस */
	list_क्रम_each_entry(req, &ep->req_queue, req_entry) अणु
		अचिन्हित पूर्णांक	host_len, dev_len, len;
		व्योम		*ubuf_pos, *rbuf_pos;
		पूर्णांक		is_लघु, to_host;
		पूर्णांक		rescan = 0;

		/*
		 * 1..N packets of ep->ep.maxpacket each ... the last one
		 * may be लघु (including zero length).
		 *
		 * ग_लिखोr can send a zlp explicitly (length 0) or implicitly
		 * (length mod maxpacket zero, and 'zero' flag); they always
		 * terminate पढ़ोs.
		 */
		host_len = urb->transfer_buffer_length - urb->actual_length;
		dev_len = req->req.length - req->req.actual;
		len = min(host_len, dev_len);

		to_host = usb_pipein(urb->pipe);
		अगर (unlikely(len == 0))
			is_लघु = 1;
		अन्यथा अणु
			/* send multiple of maxpacket first, then reमुख्यder */
			अगर (len >= ep->ep.maxpacket) अणु
				is_लघु = 0;
				अगर (len % ep->ep.maxpacket > 0)
					rescan = 1;
				len -= len % ep->ep.maxpacket;
			पूर्ण अन्यथा अणु
				is_लघु = 1;
			पूर्ण

			ubuf_pos = urb->transfer_buffer + urb->actual_length;
			rbuf_pos = req->req.buf + req->req.actual;

			अगर (urb->pipe & USB_सूची_IN)
				स_नकल(ubuf_pos, rbuf_pos, len);
			अन्यथा
				स_नकल(rbuf_pos, ubuf_pos, len);

			urb->actual_length += len;
			req->req.actual += len;
			sent += len;
		पूर्ण

		/*
		 * लघु packets terminate, maybe with overflow/underflow.
		 * it's only really an error to ग_लिखो too much.
		 *
		 * partially filling a buffer optionally blocks queue advances
		 * (so completion handlers can clean up the queue) but we करोn't
		 * need to emulate such data-in-flight.
		 */
		अगर (is_लघु) अणु
			अगर (host_len == dev_len) अणु
				req->req.status = 0;
				urb->status = 0;
			पूर्ण अन्यथा अगर (to_host) अणु
				req->req.status = 0;
				अगर (dev_len > host_len)
					urb->status = -EOVERFLOW;
				अन्यथा
					urb->status = 0;
			पूर्ण अन्यथा अणु
				urb->status = 0;
				अगर (host_len > dev_len)
					req->req.status = -EOVERFLOW;
				अन्यथा
					req->req.status = 0;
			पूर्ण

		/* many requests terminate without a लघु packet */
		/* also check अगर we need to send zlp */
		पूर्ण अन्यथा अणु
			अगर (req->req.length == req->req.actual) अणु
				अगर (req->req.zero && to_host)
					rescan = 1;
				अन्यथा
					req->req.status = 0;
			पूर्ण
			अगर (urb->transfer_buffer_length == urb->actual_length) अणु
				अगर (urb->transfer_flags & URB_ZERO_PACKET &&
				    !to_host)
					rescan = 1;
				अन्यथा
					urb->status = 0;
			पूर्ण
		पूर्ण

		/* device side completion --> continuable */
		अगर (req->req.status != -EINPROGRESS) अणु

			list_del_init(&req->req_entry);
			spin_unlock(&udc->lock);
			usb_gadget_giveback_request(&ep->ep, &req->req);
			spin_lock(&udc->lock);

			/* requests might have been unlinked... */
			rescan = 1;
		पूर्ण

		/* host side completion --> terminate */
		अगर (urb->status != -EINPROGRESS)
			अवरोध;

		/* rescan to जारी with any other queued i/o */
		अगर (rescan)
			जाओ top;
	पूर्ण
	वापस sent;
पूर्ण

अटल व्योम v_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा vudc *udc = from_समयr(udc, t, tr_समयr.समयr);
	काष्ठा transfer_समयr *समयr = &udc->tr_समयr;
	काष्ठा urbp *urb_p, *पंचांगp;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_ep *_ep;
	काष्ठा vep *ep;
	पूर्णांक ret = 0;
	पूर्णांक total, limit;

	spin_lock_irqsave(&udc->lock, flags);

	total = get_frame_limit(udc->gadget.speed);
	अगर (total < 0) अणु	/* unknown speed, or not set yet */
		समयr->state = VUDC_TR_IDLE;
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस;
	पूर्ण
	/* is it next frame now? */
	अगर (समय_after(jअगरfies, समयr->frame_start + msecs_to_jअगरfies(1))) अणु
		समयr->frame_limit = total;
		/* FIXME: how to make it accurate? */
		समयr->frame_start = jअगरfies;
	पूर्ण अन्यथा अणु
		total = समयr->frame_limit;
	पूर्ण

	/* We have to clear ep0 flags separately as it's not on the list */
	udc->ep[0].alपढ़ोy_seen = 0;
	list_क्रम_each_entry(_ep, &udc->gadget.ep_list, ep_list) अणु
		ep = to_vep(_ep);
		ep->alपढ़ोy_seen = 0;
	पूर्ण

restart:
	list_क्रम_each_entry_safe(urb_p, पंचांगp, &udc->urb_queue, urb_entry) अणु
		काष्ठा urb *urb = urb_p->urb;

		ep = urb_p->ep;
		अगर (urb->unlinked)
			जाओ वापस_urb;
		अगर (समयr->state != VUDC_TR_RUNNING)
			जारी;

		अगर (!ep) अणु
			urb->status = -EPROTO;
			जाओ वापस_urb;
		पूर्ण

		/* Used up bandwidth? */
		अगर (total <= 0 && ep->type == USB_ENDPOINT_XFER_BULK)
			जारी;

		अगर (ep->alपढ़ोy_seen)
			जारी;
		ep->alपढ़ोy_seen = 1;
		अगर (ep == &udc->ep[0] && urb_p->new) अणु
			ep->setup_stage = 1;
			urb_p->new = 0;
		पूर्ण
		अगर (ep->halted && !ep->setup_stage) अणु
			urb->status = -EPIPE;
			जाओ वापस_urb;
		पूर्ण

		अगर (ep == &udc->ep[0] && ep->setup_stage) अणु
			/* TODO - flush any stale requests */
			ep->setup_stage = 0;
			ep->halted = 0;

			ret = handle_control_request(udc, urb,
				(काष्ठा usb_ctrlrequest *) urb->setup_packet,
				(&urb->status));
			अगर (ret > 0) अणु
				spin_unlock(&udc->lock);
				ret = udc->driver->setup(&udc->gadget,
					(काष्ठा usb_ctrlrequest *)
					urb->setup_packet);
				spin_lock(&udc->lock);
			पूर्ण
			अगर (ret >= 0) अणु
				/* no delays (max 64kb data stage) */
				limit = 64 * 1024;
				जाओ treat_control_like_bulk;
			पूर्ण अन्यथा अणु
				urb->status = -EPIPE;
				urb->actual_length = 0;
				जाओ वापस_urb;
			पूर्ण
		पूर्ण

		limit = total;
		चयन (ep->type) अणु
		हाल USB_ENDPOINT_XFER_ISOC:
			/* TODO: support */
			urb->status = -EXDEV;
			अवरोध;

		हाल USB_ENDPOINT_XFER_INT:
			/*
			 * TODO: figure out bandwidth guarantees
			 * क्रम now, give unlimited bandwidth
			 */
			limit += urb->transfer_buffer_length;
			fallthrough;
		शेष:
treat_control_like_bulk:
			total -= transfer(udc, urb, ep, limit);
		पूर्ण
		अगर (urb->status == -EINPROGRESS)
			जारी;

वापस_urb:
		अगर (ep)
			ep->alपढ़ोy_seen = ep->setup_stage = 0;

		spin_lock(&udc->lock_tx);
		list_del(&urb_p->urb_entry);
		अगर (!urb->unlinked) अणु
			v_enqueue_ret_submit(udc, urb_p);
		पूर्ण अन्यथा अणु
			v_enqueue_ret_unlink(udc, urb_p->seqnum,
					     urb->unlinked);
			मुक्त_urbp_and_urb(urb_p);
		पूर्ण
		wake_up(&udc->tx_रुकोq);
		spin_unlock(&udc->lock_tx);

		जाओ restart;
	पूर्ण

	/* TODO - also रुको on empty usb_request queues? */
	अगर (list_empty(&udc->urb_queue))
		समयr->state = VUDC_TR_IDLE;
	अन्यथा
		mod_समयr(&समयr->समयr,
			  समयr->frame_start + msecs_to_jअगरfies(1));

	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

/* All समयr functions are run with udc->lock held */

व्योम v_init_समयr(काष्ठा vudc *udc)
अणु
	काष्ठा transfer_समयr *t = &udc->tr_समयr;

	समयr_setup(&t->समयr, v_समयr, 0);
	t->state = VUDC_TR_STOPPED;
पूर्ण

व्योम v_start_समयr(काष्ठा vudc *udc)
अणु
	काष्ठा transfer_समयr *t = &udc->tr_समयr;

	dev_dbg(&udc->pdev->dev, "timer start");
	चयन (t->state) अणु
	हाल VUDC_TR_RUNNING:
		वापस;
	हाल VUDC_TR_IDLE:
		वापस v_kick_समयr(udc, jअगरfies);
	हाल VUDC_TR_STOPPED:
		t->state = VUDC_TR_IDLE;
		t->frame_start = jअगरfies;
		t->frame_limit = get_frame_limit(udc->gadget.speed);
		वापस v_kick_समयr(udc, jअगरfies);
	पूर्ण
पूर्ण

व्योम v_kick_समयr(काष्ठा vudc *udc, अचिन्हित दीर्घ समय)
अणु
	काष्ठा transfer_समयr *t = &udc->tr_समयr;

	dev_dbg(&udc->pdev->dev, "timer kick");
	चयन (t->state) अणु
	हाल VUDC_TR_RUNNING:
		वापस;
	हाल VUDC_TR_IDLE:
		t->state = VUDC_TR_RUNNING;
		fallthrough;
	हाल VUDC_TR_STOPPED:
		/* we may want to kick समयr to unqueue urbs */
		mod_समयr(&t->समयr, समय);
	पूर्ण
पूर्ण

व्योम v_stop_समयr(काष्ठा vudc *udc)
अणु
	काष्ठा transfer_समयr *t = &udc->tr_समयr;

	/* समयr itself will take care of stopping */
	dev_dbg(&udc->pdev->dev, "timer stop");
	t->state = VUDC_TR_STOPPED;
पूर्ण
