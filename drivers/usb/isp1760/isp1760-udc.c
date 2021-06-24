<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the NXP ISP1761 device controller
 *
 * Copyright 2014 Ideas on Board Oy
 *
 * Contacts:
 *	Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb.h>

#समावेश "isp1760-core.h"
#समावेश "isp1760-regs.h"
#समावेश "isp1760-udc.h"

#घोषणा ISP1760_VBUS_POLL_INTERVAL	msecs_to_jअगरfies(500)

काष्ठा isp1760_request अणु
	काष्ठा usb_request req;
	काष्ठा list_head queue;
	काष्ठा isp1760_ep *ep;
	अचिन्हित पूर्णांक packet_size;
पूर्ण;

अटल अंतरभूत काष्ठा isp1760_udc *gadget_to_udc(काष्ठा usb_gadget *gadget)
अणु
	वापस container_of(gadget, काष्ठा isp1760_udc, gadget);
पूर्ण

अटल अंतरभूत काष्ठा isp1760_ep *ep_to_udc_ep(काष्ठा usb_ep *ep)
अणु
	वापस container_of(ep, काष्ठा isp1760_ep, ep);
पूर्ण

अटल अंतरभूत काष्ठा isp1760_request *req_to_udc_req(काष्ठा usb_request *req)
अणु
	वापस container_of(req, काष्ठा isp1760_request, req);
पूर्ण

अटल अंतरभूत u32 isp1760_udc_पढ़ो(काष्ठा isp1760_udc *udc, u16 reg)
अणु
	वापस isp1760_पढ़ो32(udc->regs, reg);
पूर्ण

अटल अंतरभूत व्योम isp1760_udc_ग_लिखो(काष्ठा isp1760_udc *udc, u16 reg, u32 val)
अणु
	isp1760_ग_लिखो32(udc->regs, reg, val);
पूर्ण

/* -----------------------------------------------------------------------------
 * Endpoपूर्णांक Management
 */

अटल काष्ठा isp1760_ep *isp1760_udc_find_ep(काष्ठा isp1760_udc *udc,
					      u16 index)
अणु
	अचिन्हित पूर्णांक i;

	अगर (index == 0)
		वापस &udc->ep[0];

	क्रम (i = 1; i < ARRAY_SIZE(udc->ep); ++i) अणु
		अगर (udc->ep[i].addr == index)
			वापस udc->ep[i].desc ? &udc->ep[i] : शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __isp1760_udc_select_ep(काष्ठा isp1760_ep *ep, पूर्णांक dir)
अणु
	isp1760_udc_ग_लिखो(ep->udc, DC_EPINDEX,
			  DC_ENDPIDX(ep->addr & USB_ENDPOINT_NUMBER_MASK) |
			  (dir == USB_सूची_IN ? DC_EPसूची : 0));
पूर्ण

/**
 * isp1760_udc_select_ep - Select an endpoपूर्णांक क्रम रेजिस्टर access
 * @ep: The endpoपूर्णांक
 *
 * The ISP1761 endpoपूर्णांक रेजिस्टरs are banked. This function selects the target
 * endpoपूर्णांक क्रम banked रेजिस्टर access. The selection reमुख्यs valid until the
 * next call to this function, the next direct access to the EPINDEX रेजिस्टर
 * or the next reset, whichever comes first.
 *
 * Called with the UDC spinlock held.
 */
अटल व्योम isp1760_udc_select_ep(काष्ठा isp1760_ep *ep)
अणु
	__isp1760_udc_select_ep(ep, ep->addr & USB_ENDPOINT_सूची_MASK);
पूर्ण

/* Called with the UDC spinlock held. */
अटल व्योम isp1760_udc_ctrl_send_status(काष्ठा isp1760_ep *ep, पूर्णांक dir)
अणु
	काष्ठा isp1760_udc *udc = ep->udc;

	/*
	 * Proceed to the status stage. The status stage data packet flows in
	 * the direction opposite to the data stage data packets, we thus need
	 * to select the OUT/IN endpoपूर्णांक क्रम IN/OUT transfers.
	 */
	isp1760_udc_ग_लिखो(udc, DC_EPINDEX, DC_ENDPIDX(0) |
			  (dir == USB_सूची_IN ? 0 : DC_EPसूची));
	isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_STATUS);

	/*
	 * The hardware will terminate the request स्वतःmatically and go back to
	 * the setup stage without notअगरying us.
	 */
	udc->ep0_state = ISP1760_CTRL_SETUP;
पूर्ण

/* Called without the UDC spinlock held. */
अटल व्योम isp1760_udc_request_complete(काष्ठा isp1760_ep *ep,
					 काष्ठा isp1760_request *req,
					 पूर्णांक status)
अणु
	काष्ठा isp1760_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;

	dev_dbg(ep->udc->isp->dev, "completing request %p with status %d\n",
		req, status);

	req->ep = शून्य;
	req->req.status = status;
	req->req.complete(&ep->ep, &req->req);

	spin_lock_irqsave(&udc->lock, flags);

	/*
	 * When completing control OUT requests, move to the status stage after
	 * calling the request complete callback. This gives the gadget an
	 * opportunity to stall the control transfer अगर needed.
	 */
	अगर (status == 0 && ep->addr == 0 && udc->ep0_dir == USB_सूची_OUT)
		isp1760_udc_ctrl_send_status(ep, USB_सूची_OUT);

	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

अटल व्योम isp1760_udc_ctrl_send_stall(काष्ठा isp1760_ep *ep)
अणु
	काष्ठा isp1760_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;

	dev_dbg(ep->udc->isp->dev, "%s(ep%02x)\n", __func__, ep->addr);

	spin_lock_irqsave(&udc->lock, flags);

	/* Stall both the IN and OUT endpoपूर्णांकs. */
	__isp1760_udc_select_ep(ep, USB_सूची_OUT);
	isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_STALL);
	__isp1760_udc_select_ep(ep, USB_सूची_IN);
	isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_STALL);

	/* A protocol stall completes the control transaction. */
	udc->ep0_state = ISP1760_CTRL_SETUP;

	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

/* -----------------------------------------------------------------------------
 * Data Endpoपूर्णांकs
 */

/* Called with the UDC spinlock held. */
अटल bool isp1760_udc_receive(काष्ठा isp1760_ep *ep,
				काष्ठा isp1760_request *req)
अणु
	काष्ठा isp1760_udc *udc = ep->udc;
	अचिन्हित पूर्णांक len;
	u32 *buf;
	पूर्णांक i;

	isp1760_udc_select_ep(ep);
	len = isp1760_udc_पढ़ो(udc, DC_BUFLEN) & DC_DATACOUNT_MASK;

	dev_dbg(udc->isp->dev, "%s: received %u bytes (%u/%u done)\n",
		__func__, len, req->req.actual, req->req.length);

	len = min(len, req->req.length - req->req.actual);

	अगर (!len) अणु
		/*
		 * There's no data to be पढ़ो from the FIFO, acknowledge the RX
		 * पूर्णांकerrupt by clearing the buffer.
		 *
		 * TODO: What अगर another packet arrives in the meanसमय ? The
		 * datasheet करोesn't clearly करोcument how this should be
		 * handled.
		 */
		isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_CLBUF);
		वापस false;
	पूर्ण

	buf = req->req.buf + req->req.actual;

	/*
	 * Make sure not to पढ़ो more than one extra byte, otherwise data from
	 * the next packet might be हटाओd from the FIFO.
	 */
	क्रम (i = len; i > 2; i -= 4, ++buf)
		*buf = le32_to_cpu(isp1760_udc_पढ़ो(udc, DC_DATAPORT));
	अगर (i > 0)
		*(u16 *)buf = le16_to_cpu(पढ़ोw(udc->regs + DC_DATAPORT));

	req->req.actual += len;

	/*
	 * TODO: The लघु_not_ok flag isn't supported yet, but isn't used by
	 * any gadget driver either.
	 */

	dev_dbg(udc->isp->dev,
		"%s: req %p actual/length %u/%u maxpacket %u packet size %u\n",
		__func__, req, req->req.actual, req->req.length, ep->maxpacket,
		len);

	ep->rx_pending = false;

	/*
	 * Complete the request अगर all data has been received or अगर a लघु
	 * packet has been received.
	 */
	अगर (req->req.actual == req->req.length || len < ep->maxpacket) अणु
		list_del(&req->queue);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम isp1760_udc_transmit(काष्ठा isp1760_ep *ep,
				 काष्ठा isp1760_request *req)
अणु
	काष्ठा isp1760_udc *udc = ep->udc;
	u32 *buf = req->req.buf + req->req.actual;
	पूर्णांक i;

	req->packet_size = min(req->req.length - req->req.actual,
			       ep->maxpacket);

	dev_dbg(udc->isp->dev, "%s: transferring %u bytes (%u/%u done)\n",
		__func__, req->packet_size, req->req.actual,
		req->req.length);

	__isp1760_udc_select_ep(ep, USB_सूची_IN);

	अगर (req->packet_size)
		isp1760_udc_ग_लिखो(udc, DC_BUFLEN, req->packet_size);

	/*
	 * Make sure not to ग_लिखो more than one extra byte, otherwise extra data
	 * will stay in the FIFO and will be transmitted during the next control
	 * request. The endpoपूर्णांक control CLBUF bit is supposed to allow flushing
	 * the FIFO क्रम this kind of conditions, but करोesn't seem to work.
	 */
	क्रम (i = req->packet_size; i > 2; i -= 4, ++buf)
		isp1760_udc_ग_लिखो(udc, DC_DATAPORT, cpu_to_le32(*buf));
	अगर (i > 0)
		ग_लिखोw(cpu_to_le16(*(u16 *)buf), udc->regs + DC_DATAPORT);

	अगर (ep->addr == 0)
		isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_DSEN);
	अगर (!req->packet_size)
		isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_VENDP);
पूर्ण

अटल व्योम isp1760_ep_rx_पढ़ोy(काष्ठा isp1760_ep *ep)
अणु
	काष्ठा isp1760_udc *udc = ep->udc;
	काष्ठा isp1760_request *req;
	bool complete;

	spin_lock(&udc->lock);

	अगर (ep->addr == 0 && udc->ep0_state != ISP1760_CTRL_DATA_OUT) अणु
		spin_unlock(&udc->lock);
		dev_dbg(udc->isp->dev, "%s: invalid ep0 state %u\n", __func__,
			udc->ep0_state);
		वापस;
	पूर्ण

	अगर (ep->addr != 0 && !ep->desc) अणु
		spin_unlock(&udc->lock);
		dev_dbg(udc->isp->dev, "%s: ep%02x is disabled\n", __func__,
			ep->addr);
		वापस;
	पूर्ण

	अगर (list_empty(&ep->queue)) अणु
		ep->rx_pending = true;
		spin_unlock(&udc->lock);
		dev_dbg(udc->isp->dev, "%s: ep%02x (%p) has no request queued\n",
			__func__, ep->addr, ep);
		वापस;
	पूर्ण

	req = list_first_entry(&ep->queue, काष्ठा isp1760_request,
			       queue);
	complete = isp1760_udc_receive(ep, req);

	spin_unlock(&udc->lock);

	अगर (complete)
		isp1760_udc_request_complete(ep, req, 0);
पूर्ण

अटल व्योम isp1760_ep_tx_complete(काष्ठा isp1760_ep *ep)
अणु
	काष्ठा isp1760_udc *udc = ep->udc;
	काष्ठा isp1760_request *complete = शून्य;
	काष्ठा isp1760_request *req;
	bool need_zlp;

	spin_lock(&udc->lock);

	अगर (ep->addr == 0 && udc->ep0_state != ISP1760_CTRL_DATA_IN) अणु
		spin_unlock(&udc->lock);
		dev_dbg(udc->isp->dev, "TX IRQ: invalid endpoint state %u\n",
			udc->ep0_state);
		वापस;
	पूर्ण

	अगर (list_empty(&ep->queue)) अणु
		/*
		 * This can happen क्रम the control endpoपूर्णांक when the reply to
		 * the GET_STATUS IN control request is sent directly by the
		 * setup IRQ handler. Just proceed to the status stage.
		 */
		अगर (ep->addr == 0) अणु
			isp1760_udc_ctrl_send_status(ep, USB_सूची_IN);
			spin_unlock(&udc->lock);
			वापस;
		पूर्ण

		spin_unlock(&udc->lock);
		dev_dbg(udc->isp->dev, "%s: ep%02x has no request queued\n",
			__func__, ep->addr);
		वापस;
	पूर्ण

	req = list_first_entry(&ep->queue, काष्ठा isp1760_request,
			       queue);
	req->req.actual += req->packet_size;

	need_zlp = req->req.actual == req->req.length &&
		   !(req->req.length % ep->maxpacket) &&
		   req->packet_size && req->req.zero;

	dev_dbg(udc->isp->dev,
		"TX IRQ: req %p actual/length %u/%u maxpacket %u packet size %u zero %u need zlp %u\n",
		 req, req->req.actual, req->req.length, ep->maxpacket,
		 req->packet_size, req->req.zero, need_zlp);

	/*
	 * Complete the request अगर all data has been sent and we करोn't need to
	 * transmit a zero length packet.
	 */
	अगर (req->req.actual == req->req.length && !need_zlp) अणु
		complete = req;
		list_del(&req->queue);

		अगर (ep->addr == 0)
			isp1760_udc_ctrl_send_status(ep, USB_सूची_IN);

		अगर (!list_empty(&ep->queue))
			req = list_first_entry(&ep->queue,
					       काष्ठा isp1760_request, queue);
		अन्यथा
			req = शून्य;
	पूर्ण

	/*
	 * Transmit the next packet or start the next request, अगर any.
	 *
	 * TODO: If the endpoपूर्णांक is stalled the next request shouldn't be
	 * started, but what about the next packet ?
	 */
	अगर (req)
		isp1760_udc_transmit(ep, req);

	spin_unlock(&udc->lock);

	अगर (complete)
		isp1760_udc_request_complete(ep, complete, 0);
पूर्ण

अटल पूर्णांक __isp1760_udc_set_halt(काष्ठा isp1760_ep *ep, bool halt)
अणु
	काष्ठा isp1760_udc *udc = ep->udc;

	dev_dbg(udc->isp->dev, "%s: %s halt on ep%02x\n", __func__,
		halt ? "set" : "clear", ep->addr);

	अगर (ep->desc && usb_endpoपूर्णांक_xfer_isoc(ep->desc)) अणु
		dev_dbg(udc->isp->dev, "%s: ep%02x is isochronous\n", __func__,
			ep->addr);
		वापस -EINVAL;
	पूर्ण

	isp1760_udc_select_ep(ep);
	isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, halt ? DC_STALL : 0);

	अगर (ep->addr == 0) अणु
		/* When halting the control endpoपूर्णांक, stall both IN and OUT. */
		__isp1760_udc_select_ep(ep, USB_सूची_IN);
		isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, halt ? DC_STALL : 0);
	पूर्ण अन्यथा अगर (!halt) अणु
		/* Reset the data PID by cycling the endpoपूर्णांक enable bit. */
		u16 eptype = isp1760_udc_पढ़ो(udc, DC_EPTYPE);

		isp1760_udc_ग_लिखो(udc, DC_EPTYPE, eptype & ~DC_EPENABLE);
		isp1760_udc_ग_लिखो(udc, DC_EPTYPE, eptype);

		/*
		 * Disabling the endpoपूर्णांक emptied the transmit FIFO, fill it
		 * again अगर a request is pending.
		 *
		 * TODO: Does the gadget framework require synchronizatino with
		 * the TX IRQ handler ?
		 */
		अगर ((ep->addr & USB_सूची_IN) && !list_empty(&ep->queue)) अणु
			काष्ठा isp1760_request *req;

			req = list_first_entry(&ep->queue,
					       काष्ठा isp1760_request, queue);
			isp1760_udc_transmit(ep, req);
		पूर्ण
	पूर्ण

	ep->halted = halt;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Control Endpoपूर्णांक
 */

अटल पूर्णांक isp1760_udc_get_status(काष्ठा isp1760_udc *udc,
				  स्थिर काष्ठा usb_ctrlrequest *req)
अणु
	काष्ठा isp1760_ep *ep;
	u16 status;

	अगर (req->wLength != cpu_to_le16(2) || req->wValue != cpu_to_le16(0))
		वापस -EINVAL;

	चयन (req->bRequestType) अणु
	हाल USB_सूची_IN | USB_RECIP_DEVICE:
		status = udc->devstatus;
		अवरोध;

	हाल USB_सूची_IN | USB_RECIP_INTERFACE:
		status = 0;
		अवरोध;

	हाल USB_सूची_IN | USB_RECIP_ENDPOINT:
		ep = isp1760_udc_find_ep(udc, le16_to_cpu(req->wIndex));
		अगर (!ep)
			वापस -EINVAL;

		status = 0;
		अगर (ep->halted)
			status |= 1 << USB_ENDPOINT_HALT;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	isp1760_udc_ग_लिखो(udc, DC_EPINDEX, DC_ENDPIDX(0) | DC_EPसूची);
	isp1760_udc_ग_लिखो(udc, DC_BUFLEN, 2);

	ग_लिखोw(cpu_to_le16(status), udc->regs + DC_DATAPORT);

	isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_DSEN);

	dev_dbg(udc->isp->dev, "%s: status 0x%04x\n", __func__, status);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1760_udc_set_address(काष्ठा isp1760_udc *udc, u16 addr)
अणु
	अगर (addr > 127) अणु
		dev_dbg(udc->isp->dev, "invalid device address %u\n", addr);
		वापस -EINVAL;
	पूर्ण

	अगर (udc->gadget.state != USB_STATE_DEFAULT &&
	    udc->gadget.state != USB_STATE_ADDRESS) अणु
		dev_dbg(udc->isp->dev, "can't set address in state %u\n",
			udc->gadget.state);
		वापस -EINVAL;
	पूर्ण

	usb_gadget_set_state(&udc->gadget, addr ? USB_STATE_ADDRESS :
			     USB_STATE_DEFAULT);

	isp1760_udc_ग_लिखो(udc, DC_ADDRESS, DC_DEVEN | addr);

	spin_lock(&udc->lock);
	isp1760_udc_ctrl_send_status(&udc->ep[0], USB_सूची_OUT);
	spin_unlock(&udc->lock);

	वापस 0;
पूर्ण

अटल bool isp1760_ep0_setup_standard(काष्ठा isp1760_udc *udc,
				       काष्ठा usb_ctrlrequest *req)
अणु
	bool stall;

	चयन (req->bRequest) अणु
	हाल USB_REQ_GET_STATUS:
		वापस isp1760_udc_get_status(udc, req);

	हाल USB_REQ_CLEAR_FEATURE:
		चयन (req->bRequestType) अणु
		हाल USB_सूची_OUT | USB_RECIP_DEVICE: अणु
			/* TODO: Handle remote wakeup feature. */
			वापस true;
		पूर्ण

		हाल USB_सूची_OUT | USB_RECIP_ENDPOINT: अणु
			u16 index = le16_to_cpu(req->wIndex);
			काष्ठा isp1760_ep *ep;

			अगर (req->wLength != cpu_to_le16(0) ||
			    req->wValue != cpu_to_le16(USB_ENDPOINT_HALT))
				वापस true;

			ep = isp1760_udc_find_ep(udc, index);
			अगर (!ep)
				वापस true;

			spin_lock(&udc->lock);

			/*
			 * If the endpoपूर्णांक is wedged only the gadget can clear
			 * the halt feature. Pretend success in that हाल, but
			 * keep the endpoपूर्णांक halted.
			 */
			अगर (!ep->wedged)
				stall = __isp1760_udc_set_halt(ep, false);
			अन्यथा
				stall = false;

			अगर (!stall)
				isp1760_udc_ctrl_send_status(&udc->ep[0],
							     USB_सूची_OUT);

			spin_unlock(&udc->lock);
			वापस stall;
		पूर्ण

		शेष:
			वापस true;
		पूर्ण
		अवरोध;

	हाल USB_REQ_SET_FEATURE:
		चयन (req->bRequestType) अणु
		हाल USB_सूची_OUT | USB_RECIP_DEVICE: अणु
			/* TODO: Handle remote wakeup and test mode features */
			वापस true;
		पूर्ण

		हाल USB_सूची_OUT | USB_RECIP_ENDPOINT: अणु
			u16 index = le16_to_cpu(req->wIndex);
			काष्ठा isp1760_ep *ep;

			अगर (req->wLength != cpu_to_le16(0) ||
			    req->wValue != cpu_to_le16(USB_ENDPOINT_HALT))
				वापस true;

			ep = isp1760_udc_find_ep(udc, index);
			अगर (!ep)
				वापस true;

			spin_lock(&udc->lock);

			stall = __isp1760_udc_set_halt(ep, true);
			अगर (!stall)
				isp1760_udc_ctrl_send_status(&udc->ep[0],
							     USB_सूची_OUT);

			spin_unlock(&udc->lock);
			वापस stall;
		पूर्ण

		शेष:
			वापस true;
		पूर्ण
		अवरोध;

	हाल USB_REQ_SET_ADDRESS:
		अगर (req->bRequestType != (USB_सूची_OUT | USB_RECIP_DEVICE))
			वापस true;

		वापस isp1760_udc_set_address(udc, le16_to_cpu(req->wValue));

	हाल USB_REQ_SET_CONFIGURATION:
		अगर (req->bRequestType != (USB_सूची_OUT | USB_RECIP_DEVICE))
			वापस true;

		अगर (udc->gadget.state != USB_STATE_ADDRESS &&
		    udc->gadget.state != USB_STATE_CONFIGURED)
			वापस true;

		stall = udc->driver->setup(&udc->gadget, req) < 0;
		अगर (stall)
			वापस true;

		usb_gadget_set_state(&udc->gadget, req->wValue ?
				     USB_STATE_CONFIGURED : USB_STATE_ADDRESS);

		/*
		 * SET_CONFIGURATION (and SET_INTERFACE) must reset the halt
		 * feature on all endpoपूर्णांकs. There is however no need to करो so
		 * explicitly here as the gadget driver will disable and
		 * reenable endpoपूर्णांकs, clearing the halt feature.
		 */
		वापस false;

	शेष:
		वापस udc->driver->setup(&udc->gadget, req) < 0;
	पूर्ण
पूर्ण

अटल व्योम isp1760_ep0_setup(काष्ठा isp1760_udc *udc)
अणु
	जोड़ अणु
		काष्ठा usb_ctrlrequest r;
		u32 data[2];
	पूर्ण req;
	अचिन्हित पूर्णांक count;
	bool stall = false;

	spin_lock(&udc->lock);

	isp1760_udc_ग_लिखो(udc, DC_EPINDEX, DC_EP0SETUP);

	count = isp1760_udc_पढ़ो(udc, DC_BUFLEN) & DC_DATACOUNT_MASK;
	अगर (count != माप(req)) अणु
		spin_unlock(&udc->lock);

		dev_err(udc->isp->dev, "invalid length %u for setup packet\n",
			count);

		isp1760_udc_ctrl_send_stall(&udc->ep[0]);
		वापस;
	पूर्ण

	req.data[0] = isp1760_udc_पढ़ो(udc, DC_DATAPORT);
	req.data[1] = isp1760_udc_पढ़ो(udc, DC_DATAPORT);

	अगर (udc->ep0_state != ISP1760_CTRL_SETUP) अणु
		spin_unlock(&udc->lock);
		dev_dbg(udc->isp->dev, "unexpected SETUP packet\n");
		वापस;
	पूर्ण

	/* Move to the data stage. */
	अगर (!req.r.wLength)
		udc->ep0_state = ISP1760_CTRL_STATUS;
	अन्यथा अगर (req.r.bRequestType & USB_सूची_IN)
		udc->ep0_state = ISP1760_CTRL_DATA_IN;
	अन्यथा
		udc->ep0_state = ISP1760_CTRL_DATA_OUT;

	udc->ep0_dir = req.r.bRequestType & USB_सूची_IN;
	udc->ep0_length = le16_to_cpu(req.r.wLength);

	spin_unlock(&udc->lock);

	dev_dbg(udc->isp->dev,
		"%s: bRequestType 0x%02x bRequest 0x%02x wValue 0x%04x wIndex 0x%04x wLength 0x%04x\n",
		__func__, req.r.bRequestType, req.r.bRequest,
		le16_to_cpu(req.r.wValue), le16_to_cpu(req.r.wIndex),
		le16_to_cpu(req.r.wLength));

	अगर ((req.r.bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		stall = isp1760_ep0_setup_standard(udc, &req.r);
	अन्यथा
		stall = udc->driver->setup(&udc->gadget, &req.r) < 0;

	अगर (stall)
		isp1760_udc_ctrl_send_stall(&udc->ep[0]);
पूर्ण

/* -----------------------------------------------------------------------------
 * Gadget Endpoपूर्णांक Operations
 */

अटल पूर्णांक isp1760_ep_enable(काष्ठा usb_ep *ep,
			     स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा isp1760_ep *uep = ep_to_udc_ep(ep);
	काष्ठा isp1760_udc *udc = uep->udc;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक type;

	dev_dbg(uep->udc->isp->dev, "%s\n", __func__);

	/*
	 * Validate the descriptor. The control endpoपूर्णांक can't be enabled
	 * manually.
	 */
	अगर (desc->bDescriptorType != USB_DT_ENDPOINT ||
	    desc->bEndpoपूर्णांकAddress == 0 ||
	    desc->bEndpoपूर्णांकAddress != uep->addr ||
	    le16_to_cpu(desc->wMaxPacketSize) > ep->maxpacket) अणु
		dev_dbg(udc->isp->dev,
			"%s: invalid descriptor type %u addr %02x ep addr %02x max packet size %u/%u\n",
			__func__, desc->bDescriptorType,
			desc->bEndpoपूर्णांकAddress, uep->addr,
			le16_to_cpu(desc->wMaxPacketSize), ep->maxpacket);
		वापस -EINVAL;
	पूर्ण

	चयन (usb_endpoपूर्णांक_type(desc)) अणु
	हाल USB_ENDPOINT_XFER_ISOC:
		type = DC_ENDPTYP_ISOC;
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		type = DC_ENDPTYP_BULK;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		type = DC_ENDPTYP_INTERRUPT;
		अवरोध;
	हाल USB_ENDPOINT_XFER_CONTROL:
	शेष:
		dev_dbg(udc->isp->dev, "%s: control endpoints unsupported\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);

	uep->desc = desc;
	uep->maxpacket = le16_to_cpu(desc->wMaxPacketSize);
	uep->rx_pending = false;
	uep->halted = false;
	uep->wedged = false;

	isp1760_udc_select_ep(uep);
	isp1760_udc_ग_लिखो(udc, DC_EPMAXPKTSZ, uep->maxpacket);
	isp1760_udc_ग_लिखो(udc, DC_BUFLEN, uep->maxpacket);
	isp1760_udc_ग_लिखो(udc, DC_EPTYPE, DC_EPENABLE | type);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1760_ep_disable(काष्ठा usb_ep *ep)
अणु
	काष्ठा isp1760_ep *uep = ep_to_udc_ep(ep);
	काष्ठा isp1760_udc *udc = uep->udc;
	काष्ठा isp1760_request *req, *nreq;
	LIST_HEAD(req_list);
	अचिन्हित दीर्घ flags;

	dev_dbg(udc->isp->dev, "%s\n", __func__);

	spin_lock_irqsave(&udc->lock, flags);

	अगर (!uep->desc) अणु
		dev_dbg(udc->isp->dev, "%s: endpoint not enabled\n", __func__);
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	uep->desc = शून्य;
	uep->maxpacket = 0;

	isp1760_udc_select_ep(uep);
	isp1760_udc_ग_लिखो(udc, DC_EPTYPE, 0);

	/* TODO Synchronize with the IRQ handler */

	list_splice_init(&uep->queue, &req_list);

	spin_unlock_irqrestore(&udc->lock, flags);

	list_क्रम_each_entry_safe(req, nreq, &req_list, queue) अणु
		list_del(&req->queue);
		isp1760_udc_request_complete(uep, req, -ESHUTDOWN);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा usb_request *isp1760_ep_alloc_request(काष्ठा usb_ep *ep,
						    gfp_t gfp_flags)
अणु
	काष्ठा isp1760_request *req;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	वापस &req->req;
पूर्ण

अटल व्योम isp1760_ep_मुक्त_request(काष्ठा usb_ep *ep, काष्ठा usb_request *_req)
अणु
	काष्ठा isp1760_request *req = req_to_udc_req(_req);

	kमुक्त(req);
पूर्ण

अटल पूर्णांक isp1760_ep_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *_req,
			    gfp_t gfp_flags)
अणु
	काष्ठा isp1760_request *req = req_to_udc_req(_req);
	काष्ठा isp1760_ep *uep = ep_to_udc_ep(ep);
	काष्ठा isp1760_udc *udc = uep->udc;
	bool complete = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	spin_lock_irqsave(&udc->lock, flags);

	dev_dbg(udc->isp->dev,
		"%s: req %p (%u bytes%s) ep %p(0x%02x)\n", __func__, _req,
		_req->length, _req->zero ? " (zlp)" : "", uep, uep->addr);

	req->ep = uep;

	अगर (uep->addr == 0) अणु
		अगर (_req->length != udc->ep0_length &&
		    udc->ep0_state != ISP1760_CTRL_DATA_IN) अणु
			dev_dbg(udc->isp->dev,
				"%s: invalid length %u for req %p\n",
				__func__, _req->length, req);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		चयन (udc->ep0_state) अणु
		हाल ISP1760_CTRL_DATA_IN:
			dev_dbg(udc->isp->dev, "%s: transmitting req %p\n",
				__func__, req);

			list_add_tail(&req->queue, &uep->queue);
			isp1760_udc_transmit(uep, req);
			अवरोध;

		हाल ISP1760_CTRL_DATA_OUT:
			list_add_tail(&req->queue, &uep->queue);
			__isp1760_udc_select_ep(uep, USB_सूची_OUT);
			isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_DSEN);
			अवरोध;

		हाल ISP1760_CTRL_STATUS:
			complete = true;
			अवरोध;

		शेष:
			dev_dbg(udc->isp->dev, "%s: invalid ep0 state\n",
				__func__);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (uep->desc) अणु
		bool empty = list_empty(&uep->queue);

		list_add_tail(&req->queue, &uep->queue);
		अगर ((uep->addr & USB_सूची_IN) && !uep->halted && empty)
			isp1760_udc_transmit(uep, req);
		अन्यथा अगर (!(uep->addr & USB_सूची_IN) && uep->rx_pending)
			complete = isp1760_udc_receive(uep, req);
	पूर्ण अन्यथा अणु
		dev_dbg(udc->isp->dev,
			"%s: can't queue request to disabled ep%02x\n",
			__func__, uep->addr);
		ret = -ESHUTDOWN;
	पूर्ण

करोne:
	अगर (ret < 0)
		req->ep = शून्य;

	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (complete)
		isp1760_udc_request_complete(uep, req, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक isp1760_ep_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *_req)
अणु
	काष्ठा isp1760_request *req = req_to_udc_req(_req);
	काष्ठा isp1760_ep *uep = ep_to_udc_ep(ep);
	काष्ठा isp1760_udc *udc = uep->udc;
	अचिन्हित दीर्घ flags;

	dev_dbg(uep->udc->isp->dev, "%s(ep%02x)\n", __func__, uep->addr);

	spin_lock_irqsave(&udc->lock, flags);

	अगर (req->ep != uep)
		req = शून्य;
	अन्यथा
		list_del(&req->queue);

	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (!req)
		वापस -EINVAL;

	isp1760_udc_request_complete(uep, req, -ECONNRESET);
	वापस 0;
पूर्ण

अटल पूर्णांक __isp1760_ep_set_halt(काष्ठा isp1760_ep *uep, bool stall, bool wedge)
अणु
	काष्ठा isp1760_udc *udc = uep->udc;
	पूर्णांक ret;

	अगर (!uep->addr) अणु
		/*
		 * Halting the control endpoपूर्णांक is only valid as a delayed error
		 * response to a SETUP packet. Make sure EP0 is in the right
		 * stage and that the gadget isn't trying to clear the halt
		 * condition.
		 */
		अगर (WARN_ON(udc->ep0_state == ISP1760_CTRL_SETUP || !stall ||
			     wedge)) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (uep->addr && !uep->desc) अणु
		dev_dbg(udc->isp->dev, "%s: ep%02x is disabled\n", __func__,
			uep->addr);
		वापस -EINVAL;
	पूर्ण

	अगर (uep->addr & USB_सूची_IN) अणु
		/* Refuse to halt IN endpoपूर्णांकs with active transfers. */
		अगर (!list_empty(&uep->queue)) अणु
			dev_dbg(udc->isp->dev,
				"%s: ep%02x has request pending\n", __func__,
				uep->addr);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	ret = __isp1760_udc_set_halt(uep, stall);
	अगर (ret < 0)
		वापस ret;

	अगर (!uep->addr) अणु
		/*
		 * Stalling EP0 completes the control transaction, move back to
		 * the SETUP state.
		 */
		udc->ep0_state = ISP1760_CTRL_SETUP;
		वापस 0;
	पूर्ण

	अगर (wedge)
		uep->wedged = true;
	अन्यथा अगर (!stall)
		uep->wedged = false;

	वापस 0;
पूर्ण

अटल पूर्णांक isp1760_ep_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा isp1760_ep *uep = ep_to_udc_ep(ep);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	dev_dbg(uep->udc->isp->dev, "%s: %s halt on ep%02x\n", __func__,
		value ? "set" : "clear", uep->addr);

	spin_lock_irqsave(&uep->udc->lock, flags);
	ret = __isp1760_ep_set_halt(uep, value, false);
	spin_unlock_irqrestore(&uep->udc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक isp1760_ep_set_wedge(काष्ठा usb_ep *ep)
अणु
	काष्ठा isp1760_ep *uep = ep_to_udc_ep(ep);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	dev_dbg(uep->udc->isp->dev, "%s: set wedge on ep%02x)\n", __func__,
		uep->addr);

	spin_lock_irqsave(&uep->udc->lock, flags);
	ret = __isp1760_ep_set_halt(uep, true, true);
	spin_unlock_irqrestore(&uep->udc->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम isp1760_ep_fअगरo_flush(काष्ठा usb_ep *ep)
अणु
	काष्ठा isp1760_ep *uep = ep_to_udc_ep(ep);
	काष्ठा isp1760_udc *udc = uep->udc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);

	isp1760_udc_select_ep(uep);

	/*
	 * Set the CLBUF bit twice to flush both buffers in हाल द्विगुन
	 * buffering is enabled.
	 */
	isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_CLBUF);
	isp1760_udc_ग_लिखो(udc, DC_CTRLFUNC, DC_CLBUF);

	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops isp1760_ep_ops = अणु
	.enable = isp1760_ep_enable,
	.disable = isp1760_ep_disable,
	.alloc_request = isp1760_ep_alloc_request,
	.मुक्त_request = isp1760_ep_मुक्त_request,
	.queue = isp1760_ep_queue,
	.dequeue = isp1760_ep_dequeue,
	.set_halt = isp1760_ep_set_halt,
	.set_wedge = isp1760_ep_set_wedge,
	.fअगरo_flush = isp1760_ep_fअगरo_flush,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Device States
 */

/* Called with the UDC spinlock held. */
अटल व्योम isp1760_udc_connect(काष्ठा isp1760_udc *udc)
अणु
	usb_gadget_set_state(&udc->gadget, USB_STATE_POWERED);
	mod_समयr(&udc->vbus_समयr, jअगरfies + ISP1760_VBUS_POLL_INTERVAL);
पूर्ण

/* Called with the UDC spinlock held. */
अटल व्योम isp1760_udc_disconnect(काष्ठा isp1760_udc *udc)
अणु
	अगर (udc->gadget.state < USB_STATE_POWERED)
		वापस;

	dev_dbg(udc->isp->dev, "Device disconnected in state %u\n",
		 udc->gadget.state);

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	usb_gadget_set_state(&udc->gadget, USB_STATE_ATTACHED);

	अगर (udc->driver->disconnect)
		udc->driver->disconnect(&udc->gadget);

	del_समयr(&udc->vbus_समयr);

	/* TODO Reset all endpoपूर्णांकs ? */
पूर्ण

अटल व्योम isp1760_udc_init_hw(काष्ठा isp1760_udc *udc)
अणु
	/*
	 * The device controller currently shares its पूर्णांकerrupt with the host
	 * controller, the DC_IRQ polarity and संकेतing mode are ignored. Set
	 * the to active-low level-triggered.
	 *
	 * Configure the control, in and out pipes to generate पूर्णांकerrupts on
	 * ACK tokens only (and NYET क्रम the out pipe). The शेष
	 * configuration also generates an पूर्णांकerrupt on the first NACK token.
	 */
	isp1760_udc_ग_लिखो(udc, DC_INTCONF, DC_CDBGMOD_ACK | DC_DDBGMODIN_ACK |
			  DC_DDBGMODOUT_ACK_NYET);

	isp1760_udc_ग_लिखो(udc, DC_INTENABLE, DC_IEPRXTX(7) | DC_IEPRXTX(6) |
			  DC_IEPRXTX(5) | DC_IEPRXTX(4) | DC_IEPRXTX(3) |
			  DC_IEPRXTX(2) | DC_IEPRXTX(1) | DC_IEPRXTX(0) |
			  DC_IEP0SETUP | DC_IEVBUS | DC_IERESM | DC_IESUSP |
			  DC_IEHS_STA | DC_IEBRST);

	अगर (udc->connected)
		isp1760_set_pullup(udc->isp, true);

	isp1760_udc_ग_लिखो(udc, DC_ADDRESS, DC_DEVEN);
पूर्ण

अटल व्योम isp1760_udc_reset(काष्ठा isp1760_udc *udc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);

	/*
	 * The bus reset has reset most रेजिस्टरs to their शेष value,
	 * reinitialize the UDC hardware.
	 */
	isp1760_udc_init_hw(udc);

	udc->ep0_state = ISP1760_CTRL_SETUP;
	udc->gadget.speed = USB_SPEED_FULL;

	usb_gadget_udc_reset(&udc->gadget, udc->driver);

	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

अटल व्योम isp1760_udc_suspend(काष्ठा isp1760_udc *udc)
अणु
	अगर (udc->gadget.state < USB_STATE_DEFAULT)
		वापस;

	अगर (udc->driver->suspend)
		udc->driver->suspend(&udc->gadget);
पूर्ण

अटल व्योम isp1760_udc_resume(काष्ठा isp1760_udc *udc)
अणु
	अगर (udc->gadget.state < USB_STATE_DEFAULT)
		वापस;

	अगर (udc->driver->resume)
		udc->driver->resume(&udc->gadget);
पूर्ण

/* -----------------------------------------------------------------------------
 * Gadget Operations
 */

अटल पूर्णांक isp1760_udc_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा isp1760_udc *udc = gadget_to_udc(gadget);

	वापस isp1760_udc_पढ़ो(udc, DC_FRAMENUM) & ((1 << 11) - 1);
पूर्ण

अटल पूर्णांक isp1760_udc_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा isp1760_udc *udc = gadget_to_udc(gadget);

	dev_dbg(udc->isp->dev, "%s\n", __func__);
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक isp1760_udc_set_selfघातered(काष्ठा usb_gadget *gadget,
				       पूर्णांक is_selfघातered)
अणु
	काष्ठा isp1760_udc *udc = gadget_to_udc(gadget);

	अगर (is_selfघातered)
		udc->devstatus |= 1 << USB_DEVICE_SELF_POWERED;
	अन्यथा
		udc->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1760_udc_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा isp1760_udc *udc = gadget_to_udc(gadget);

	isp1760_set_pullup(udc->isp, is_on);
	udc->connected = is_on;

	वापस 0;
पूर्ण

अटल पूर्णांक isp1760_udc_start(काष्ठा usb_gadget *gadget,
			     काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा isp1760_udc *udc = gadget_to_udc(gadget);
	अचिन्हित दीर्घ flags;

	/* The hardware करोesn't support low speed. */
	अगर (driver->max_speed < USB_SPEED_FULL) अणु
		dev_err(udc->isp->dev, "Invalid gadget driver\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);

	अगर (udc->driver) अणु
		dev_err(udc->isp->dev, "UDC already has a gadget driver\n");
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस -EBUSY;
	पूर्ण

	udc->driver = driver;

	spin_unlock_irqrestore(&udc->lock, flags);

	dev_dbg(udc->isp->dev, "starting UDC with driver %s\n",
		driver->function);

	udc->devstatus = 0;
	udc->connected = true;

	usb_gadget_set_state(&udc->gadget, USB_STATE_ATTACHED);

	/* DMA isn't supported yet, don't enable the DMA घड़ी. */
	isp1760_udc_ग_लिखो(udc, DC_MODE, DC_GLINTENA);

	isp1760_udc_init_hw(udc);

	dev_dbg(udc->isp->dev, "UDC started with driver %s\n",
		driver->function);

	वापस 0;
पूर्ण

अटल पूर्णांक isp1760_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा isp1760_udc *udc = gadget_to_udc(gadget);
	अचिन्हित दीर्घ flags;

	dev_dbg(udc->isp->dev, "%s\n", __func__);

	del_समयr_sync(&udc->vbus_समयr);

	isp1760_udc_ग_लिखो(udc, DC_MODE, 0);

	spin_lock_irqsave(&udc->lock, flags);
	udc->driver = शून्य;
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops isp1760_udc_ops = अणु
	.get_frame = isp1760_udc_get_frame,
	.wakeup = isp1760_udc_wakeup,
	.set_selfघातered = isp1760_udc_set_selfघातered,
	.pullup = isp1760_udc_pullup,
	.udc_start = isp1760_udc_start,
	.udc_stop = isp1760_udc_stop,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Interrupt Handling
 */

अटल irqवापस_t isp1760_udc_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा isp1760_udc *udc = dev;
	अचिन्हित पूर्णांक i;
	u32 status;

	status = isp1760_udc_पढ़ो(udc, DC_INTERRUPT)
	       & isp1760_udc_पढ़ो(udc, DC_INTENABLE);
	isp1760_udc_ग_लिखो(udc, DC_INTERRUPT, status);

	अगर (status & DC_IEVBUS) अणु
		dev_dbg(udc->isp->dev, "%s(VBUS)\n", __func__);
		/* The VBUS पूर्णांकerrupt is only triggered when VBUS appears. */
		spin_lock(&udc->lock);
		isp1760_udc_connect(udc);
		spin_unlock(&udc->lock);
	पूर्ण

	अगर (status & DC_IEBRST) अणु
		dev_dbg(udc->isp->dev, "%s(BRST)\n", __func__);

		isp1760_udc_reset(udc);
	पूर्ण

	क्रम (i = 0; i <= 7; ++i) अणु
		काष्ठा isp1760_ep *ep = &udc->ep[i*2];

		अगर (status & DC_IEPTX(i)) अणु
			dev_dbg(udc->isp->dev, "%s(EPTX%u)\n", __func__, i);
			isp1760_ep_tx_complete(ep);
		पूर्ण

		अगर (status & DC_IEPRX(i)) अणु
			dev_dbg(udc->isp->dev, "%s(EPRX%u)\n", __func__, i);
			isp1760_ep_rx_पढ़ोy(i ? ep - 1 : ep);
		पूर्ण
	पूर्ण

	अगर (status & DC_IEP0SETUP) अणु
		dev_dbg(udc->isp->dev, "%s(EP0SETUP)\n", __func__);

		isp1760_ep0_setup(udc);
	पूर्ण

	अगर (status & DC_IERESM) अणु
		dev_dbg(udc->isp->dev, "%s(RESM)\n", __func__);
		isp1760_udc_resume(udc);
	पूर्ण

	अगर (status & DC_IESUSP) अणु
		dev_dbg(udc->isp->dev, "%s(SUSP)\n", __func__);

		spin_lock(&udc->lock);
		अगर (!(isp1760_udc_पढ़ो(udc, DC_MODE) & DC_VBUSSTAT))
			isp1760_udc_disconnect(udc);
		अन्यथा
			isp1760_udc_suspend(udc);
		spin_unlock(&udc->lock);
	पूर्ण

	अगर (status & DC_IEHS_STA) अणु
		dev_dbg(udc->isp->dev, "%s(HS_STA)\n", __func__);
		udc->gadget.speed = USB_SPEED_HIGH;
	पूर्ण

	वापस status ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम isp1760_udc_vbus_poll(काष्ठा समयr_list *t)
अणु
	काष्ठा isp1760_udc *udc = from_समयr(udc, t, vbus_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);

	अगर (!(isp1760_udc_पढ़ो(udc, DC_MODE) & DC_VBUSSTAT))
		isp1760_udc_disconnect(udc);
	अन्यथा अगर (udc->gadget.state >= USB_STATE_POWERED)
		mod_समयr(&udc->vbus_समयr,
			  jअगरfies + ISP1760_VBUS_POLL_INTERVAL);

	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

/* -----------------------------------------------------------------------------
 * Registration
 */

अटल व्योम isp1760_udc_init_eps(काष्ठा isp1760_udc *udc)
अणु
	अचिन्हित पूर्णांक i;

	INIT_LIST_HEAD(&udc->gadget.ep_list);

	क्रम (i = 0; i < ARRAY_SIZE(udc->ep); ++i) अणु
		काष्ठा isp1760_ep *ep = &udc->ep[i];
		अचिन्हित पूर्णांक ep_num = (i + 1) / 2;
		bool is_in = !(i & 1);

		ep->udc = udc;

		INIT_LIST_HEAD(&ep->queue);

		ep->addr = (ep_num && is_in ? USB_सूची_IN : USB_सूची_OUT)
			 | ep_num;
		ep->desc = शून्य;

		प्र_लिखो(ep->name, "ep%u%s", ep_num,
			ep_num ? (is_in ? "in" : "out") : "");

		ep->ep.ops = &isp1760_ep_ops;
		ep->ep.name = ep->name;

		/*
		 * Hardcode the maximum packet sizes क्रम now, to 64 bytes क्रम
		 * the control endpoपूर्णांक and 512 bytes क्रम all other endpoपूर्णांकs.
		 * This fits in the 8kB FIFO without द्विगुन-buffering.
		 */
		अगर (ep_num == 0) अणु
			usb_ep_set_maxpacket_limit(&ep->ep, 64);
			ep->ep.caps.type_control = true;
			ep->ep.caps.dir_in = true;
			ep->ep.caps.dir_out = true;
			ep->maxpacket = 64;
			udc->gadget.ep0 = &ep->ep;
		पूर्ण अन्यथा अणु
			usb_ep_set_maxpacket_limit(&ep->ep, 512);
			ep->ep.caps.type_iso = true;
			ep->ep.caps.type_bulk = true;
			ep->ep.caps.type_पूर्णांक = true;
			ep->maxpacket = 0;
			list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);
		पूर्ण

		अगर (is_in)
			ep->ep.caps.dir_in = true;
		अन्यथा
			ep->ep.caps.dir_out = true;
	पूर्ण
पूर्ण

अटल पूर्णांक isp1760_udc_init(काष्ठा isp1760_udc *udc)
अणु
	u16 scratch;
	u32 chipid;

	/*
	 * Check that the controller is present by writing to the scratch
	 * रेजिस्टर, modअगरying the bus pattern by पढ़ोing from the chip ID
	 * रेजिस्टर, and पढ़ोing the scratch रेजिस्टर value back. The chip ID
	 * and scratch रेजिस्टर contents must match the expected values.
	 */
	isp1760_udc_ग_लिखो(udc, DC_SCRATCH, 0xbabe);
	chipid = isp1760_udc_पढ़ो(udc, DC_CHIPID);
	scratch = isp1760_udc_पढ़ो(udc, DC_SCRATCH);

	अगर (scratch != 0xbabe) अणु
		dev_err(udc->isp->dev,
			"udc: scratch test failed (0x%04x/0x%08x)\n",
			scratch, chipid);
		वापस -ENODEV;
	पूर्ण

	अगर (chipid != 0x00011582 && chipid != 0x00158210) अणु
		dev_err(udc->isp->dev, "udc: invalid chip ID 0x%08x\n", chipid);
		वापस -ENODEV;
	पूर्ण

	/* Reset the device controller. */
	isp1760_udc_ग_लिखो(udc, DC_MODE, DC_SFRESET);
	usleep_range(10000, 11000);
	isp1760_udc_ग_लिखो(udc, DC_MODE, 0);
	usleep_range(10000, 11000);

	वापस 0;
पूर्ण

पूर्णांक isp1760_udc_रेजिस्टर(काष्ठा isp1760_device *isp, पूर्णांक irq,
			 अचिन्हित दीर्घ irqflags)
अणु
	काष्ठा isp1760_udc *udc = &isp->udc;
	पूर्णांक ret;

	udc->irq = -1;
	udc->isp = isp;
	udc->regs = isp->regs;

	spin_lock_init(&udc->lock);
	समयr_setup(&udc->vbus_समयr, isp1760_udc_vbus_poll, 0);

	ret = isp1760_udc_init(udc);
	अगर (ret < 0)
		वापस ret;

	udc->irqname = kaप्र_लिखो(GFP_KERNEL, "%s (udc)", dev_name(isp->dev));
	अगर (!udc->irqname)
		वापस -ENOMEM;

	ret = request_irq(irq, isp1760_udc_irq, IRQF_SHARED | irqflags,
			  udc->irqname, udc);
	अगर (ret < 0)
		जाओ error;

	udc->irq = irq;

	/*
	 * Initialize the gadget अटल fields and रेजिस्टर its device. Gadget
	 * fields that vary during the lअगरe समय of the gadget are initialized
	 * by the UDC core.
	 */
	udc->gadget.ops = &isp1760_udc_ops;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.max_speed = USB_SPEED_HIGH;
	udc->gadget.name = "isp1761_udc";

	isp1760_udc_init_eps(udc);

	ret = usb_add_gadget_udc(isp->dev, &udc->gadget);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	अगर (udc->irq >= 0)
		मुक्त_irq(udc->irq, udc);
	kमुक्त(udc->irqname);

	वापस ret;
पूर्ण

व्योम isp1760_udc_unरेजिस्टर(काष्ठा isp1760_device *isp)
अणु
	काष्ठा isp1760_udc *udc = &isp->udc;

	अगर (!udc->isp)
		वापस;

	usb_del_gadget_udc(&udc->gadget);

	मुक्त_irq(udc->irq, udc);
	kमुक्त(udc->irqname);
पूर्ण
