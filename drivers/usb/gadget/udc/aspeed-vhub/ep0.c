<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * aspeed-vhub -- Driver क्रम Aspeed SoC "vHub" USB gadget
 *
 * ep0.c - Endpoपूर्णांक 0 handling
 *
 * Copyright 2017 IBM Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/clk.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/dma-mapping.h>

#समावेश "vhub.h"

पूर्णांक ast_vhub_reply(काष्ठा ast_vhub_ep *ep, अक्षर *ptr, पूर्णांक len)
अणु
	काष्ठा usb_request *req = &ep->ep0.req.req;
	पूर्णांक rc;

	अगर (WARN_ON(ep->d_idx != 0))
		वापस std_req_stall;
	अगर (WARN_ON(!ep->ep0.dir_in))
		वापस std_req_stall;
	अगर (WARN_ON(len > AST_VHUB_EP0_MAX_PACKET))
		वापस std_req_stall;
	अगर (WARN_ON(req->status == -EINPROGRESS))
		वापस std_req_stall;

	req->buf = ptr;
	req->length = len;
	req->complete = शून्य;
	req->zero = true;

	/*
	 * Call पूर्णांकernal queue directly after dropping the lock. This is
	 * safe to करो as the reply is always the last thing करोne when
	 * processing a SETUP packet, usually as a tail call
	 */
	spin_unlock(&ep->vhub->lock);
	अगर (ep->ep.ops->queue(&ep->ep, req, GFP_ATOMIC))
		rc = std_req_stall;
	अन्यथा
		rc = std_req_data;
	spin_lock(&ep->vhub->lock);
	वापस rc;
पूर्ण

पूर्णांक __ast_vhub_simple_reply(काष्ठा ast_vhub_ep *ep, पूर्णांक len, ...)
अणु
	u8 *buffer = ep->buf;
	अचिन्हित पूर्णांक i;
	बहु_सूची args;

	बहु_शुरू(args, len);

	/* Copy data directly पूर्णांकo EP buffer */
	क्रम (i = 0; i < len; i++)
		buffer[i] = बहु_तर्क(args, पूर्णांक);
	बहु_पूर्ण(args);

	/* req->buf शून्य means data is alपढ़ोy there */
	वापस ast_vhub_reply(ep, शून्य, len);
पूर्ण

व्योम ast_vhub_ep0_handle_setup(काष्ठा ast_vhub_ep *ep)
अणु
	काष्ठा usb_ctrlrequest crq;
	क्रमागत std_req_rc std_req_rc;
	पूर्णांक rc = -ENODEV;

	अगर (WARN_ON(ep->d_idx != 0))
		वापस;

	/*
	 * Grab the setup packet from the chip and byteswap
	 * पूर्णांकeresting fields
	 */
	स_नकल_fromio(&crq, ep->ep0.setup, माप(crq));

	EPDBG(ep, "SETUP packet %02x/%02x/%04x/%04x/%04x [%s] st=%d\n",
	      crq.bRequestType, crq.bRequest,
	       le16_to_cpu(crq.wValue),
	       le16_to_cpu(crq.wIndex),
	       le16_to_cpu(crq.wLength),
	       (crq.bRequestType & USB_सूची_IN) ? "in" : "out",
	       ep->ep0.state);

	/*
	 * Check our state, cancel pending requests अगर needed
	 *
	 * Note: Under some circumstances, we can get a new setup
	 * packet जबतक रुकोing क्रम the stall ack, just accept it.
	 *
	 * In any हाल, a SETUP packet in wrong state should have
	 * reset the HW state machine, so let's just log, nuke
	 * requests, move on.
	 */
	अगर (ep->ep0.state != ep0_state_token &&
	    ep->ep0.state != ep0_state_stall) अणु
		EPDBG(ep, "wrong state\n");
		ast_vhub_nuke(ep, -EIO);
	पूर्ण

	/* Calculate next state क्रम EP0 */
	ep->ep0.state = ep0_state_data;
	ep->ep0.dir_in = !!(crq.bRequestType & USB_सूची_IN);

	/* If this is the vHub, we handle requests dअगरferently */
	std_req_rc = std_req_driver;
	अगर (ep->dev == शून्य) अणु
		अगर ((crq.bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
			std_req_rc = ast_vhub_std_hub_request(ep, &crq);
		अन्यथा अगर ((crq.bRequestType & USB_TYPE_MASK) == USB_TYPE_CLASS)
			std_req_rc = ast_vhub_class_hub_request(ep, &crq);
		अन्यथा
			std_req_rc = std_req_stall;
	पूर्ण अन्यथा अगर ((crq.bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		std_req_rc = ast_vhub_std_dev_request(ep, &crq);

	/* Act upon result */
	चयन(std_req_rc) अणु
	हाल std_req_complete:
		जाओ complete;
	हाल std_req_stall:
		जाओ stall;
	हाल std_req_driver:
		अवरोध;
	हाल std_req_data:
		वापस;
	पूर्ण

	/* Pass request up to the gadget driver */
	अगर (WARN_ON(!ep->dev))
		जाओ stall;
	अगर (ep->dev->driver) अणु
		EPDBG(ep, "forwarding to gadget...\n");
		spin_unlock(&ep->vhub->lock);
		rc = ep->dev->driver->setup(&ep->dev->gadget, &crq);
		spin_lock(&ep->vhub->lock);
		EPDBG(ep, "driver returned %d\n", rc);
	पूर्ण अन्यथा अणु
		EPDBG(ep, "no gadget for request !\n");
	पूर्ण
	अगर (rc >= 0)
		वापस;

 stall:
	EPDBG(ep, "stalling\n");
	ग_लिखोl(VHUB_EP0_CTRL_STALL, ep->ep0.ctlstat);
	ep->ep0.state = ep0_state_stall;
	ep->ep0.dir_in = false;
	वापस;

 complete:
	EPVDBG(ep, "sending [in] status with no data\n");
	ग_लिखोl(VHUB_EP0_TX_BUFF_RDY, ep->ep0.ctlstat);
	ep->ep0.state = ep0_state_status;
	ep->ep0.dir_in = false;
पूर्ण


अटल व्योम ast_vhub_ep0_करो_send(काष्ठा ast_vhub_ep *ep,
				 काष्ठा ast_vhub_req *req)
अणु
	अचिन्हित पूर्णांक chunk;
	u32 reg;

	/* If this is a 0-length request, it's the gadget trying to
	 * send a status on our behalf. We take it from here.
	 */
	अगर (req->req.length == 0)
		req->last_desc = 1;

	/* Are we करोne ? Complete request, otherwise रुको क्रम next पूर्णांकerrupt */
	अगर (req->last_desc >= 0) अणु
		EPVDBG(ep, "complete send %d/%d\n",
		       req->req.actual, req->req.length);
		ep->ep0.state = ep0_state_status;
		ग_लिखोl(VHUB_EP0_RX_BUFF_RDY, ep->ep0.ctlstat);
		ast_vhub_करोne(ep, req, 0);
		वापस;
	पूर्ण

	/*
	 * Next chunk cropped to max packet size. Also check अगर this
	 * is the last packet
	 */
	chunk = req->req.length - req->req.actual;
	अगर (chunk > ep->ep.maxpacket)
		chunk = ep->ep.maxpacket;
	अन्यथा अगर ((chunk < ep->ep.maxpacket) || !req->req.zero)
		req->last_desc = 1;

	EPVDBG(ep, "send chunk=%d last=%d, req->act=%d mp=%d\n",
	       chunk, req->last_desc, req->req.actual, ep->ep.maxpacket);

	/*
	 * Copy data अगर any (पूर्णांकernal requests alपढ़ोy have data
	 * in the EP buffer)
	 */
	अगर (chunk && req->req.buf)
		स_नकल(ep->buf, req->req.buf + req->req.actual, chunk);

	vhub_dma_workaround(ep->buf);

	/* Remember chunk size and trigger send */
	reg = VHUB_EP0_SET_TX_LEN(chunk);
	ग_लिखोl(reg, ep->ep0.ctlstat);
	ग_लिखोl(reg | VHUB_EP0_TX_BUFF_RDY, ep->ep0.ctlstat);
	req->req.actual += chunk;
पूर्ण

अटल व्योम ast_vhub_ep0_rx_prime(काष्ठा ast_vhub_ep *ep)
अणु
	EPVDBG(ep, "rx prime\n");

	/* Prime endpoपूर्णांक क्रम receiving data */
	ग_लिखोl(VHUB_EP0_RX_BUFF_RDY, ep->ep0.ctlstat);
पूर्ण

अटल व्योम ast_vhub_ep0_करो_receive(काष्ठा ast_vhub_ep *ep, काष्ठा ast_vhub_req *req,
				    अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक reमुख्य;
	पूर्णांक rc = 0;

	/* We are receiving... grab request */
	reमुख्य = req->req.length - req->req.actual;

	EPVDBG(ep, "receive got=%d remain=%d\n", len, reमुख्य);

	/* Are we getting more than asked ? */
	अगर (len > reमुख्य) अणु
		EPDBG(ep, "receiving too much (ovf: %d) !\n",
		      len - reमुख्य);
		len = reमुख्य;
		rc = -EOVERFLOW;
	पूर्ण
	अगर (len && req->req.buf)
		स_नकल(req->req.buf + req->req.actual, ep->buf, len);
	req->req.actual += len;

	/* Done ? */
	अगर (len < ep->ep.maxpacket || len == reमुख्य) अणु
		ep->ep0.state = ep0_state_status;
		ग_लिखोl(VHUB_EP0_TX_BUFF_RDY, ep->ep0.ctlstat);
		ast_vhub_करोne(ep, req, rc);
	पूर्ण अन्यथा
		ast_vhub_ep0_rx_prime(ep);
पूर्ण

व्योम ast_vhub_ep0_handle_ack(काष्ठा ast_vhub_ep *ep, bool in_ack)
अणु
	काष्ठा ast_vhub_req *req;
	काष्ठा ast_vhub *vhub = ep->vhub;
	काष्ठा device *dev = &vhub->pdev->dev;
	bool stall = false;
	u32 stat;

	/* Read EP0 status */
	stat = पढ़ोl(ep->ep0.ctlstat);

	/* Grab current request अगर any */
	req = list_first_entry_or_null(&ep->queue, काष्ठा ast_vhub_req, queue);

	EPVDBG(ep, "ACK status=%08x,state=%d is_in=%d in_ack=%d req=%p\n",
		stat, ep->ep0.state, ep->ep0.dir_in, in_ack, req);

	चयन(ep->ep0.state) अणु
	हाल ep0_state_token:
		/* There should be no request queued in that state... */
		अगर (req) अणु
			dev_warn(dev, "request present while in TOKEN state\n");
			ast_vhub_nuke(ep, -EINVAL);
		पूर्ण
		dev_warn(dev, "ack while in TOKEN state\n");
		stall = true;
		अवरोध;
	हाल ep0_state_data:
		/* Check the state bits corresponding to our direction */
		अगर ((ep->ep0.dir_in && (stat & VHUB_EP0_TX_BUFF_RDY)) ||
		    (!ep->ep0.dir_in && (stat & VHUB_EP0_RX_BUFF_RDY)) ||
		    (ep->ep0.dir_in != in_ack)) अणु
			/* In that हाल, ignore पूर्णांकerrupt */
			dev_warn(dev, "irq state mismatch");
			अवरोध;
		पूर्ण
		/*
		 * We are in data phase and there's no request, something is
		 * wrong, stall
		 */
		अगर (!req) अणु
			dev_warn(dev, "data phase, no request\n");
			stall = true;
			अवरोध;
		पूर्ण

		/* We have a request, handle data transfers */
		अगर (ep->ep0.dir_in)
			ast_vhub_ep0_करो_send(ep, req);
		अन्यथा
			ast_vhub_ep0_करो_receive(ep, req, VHUB_EP0_RX_LEN(stat));
		वापस;
	हाल ep0_state_status:
		/* Nuke stale requests */
		अगर (req) अणु
			dev_warn(dev, "request present while in STATUS state\n");
			ast_vhub_nuke(ep, -EINVAL);
		पूर्ण

		/*
		 * If the status phase completes with the wrong ack, stall
		 * the endpoपूर्णांक just in हाल, to पात whatever the host
		 * was करोing.
		 */
		अगर (ep->ep0.dir_in == in_ack) अणु
			dev_warn(dev, "status direction mismatch\n");
			stall = true;
		पूर्ण
		अवरोध;
	हाल ep0_state_stall:
		/*
		 * There shouldn't be any request left, but nuke just in हाल
		 * otherwise the stale request will block subsequent ones
		 */
		ast_vhub_nuke(ep, -EIO);
		अवरोध;
	पूर्ण

	/* Reset to token state or stall */
	अगर (stall) अणु
		ग_लिखोl(VHUB_EP0_CTRL_STALL, ep->ep0.ctlstat);
		ep->ep0.state = ep0_state_stall;
	पूर्ण अन्यथा
		ep->ep0.state = ep0_state_token;
पूर्ण

अटल पूर्णांक ast_vhub_ep0_queue(काष्ठा usb_ep* u_ep, काष्ठा usb_request *u_req,
			      gfp_t gfp_flags)
अणु
	काष्ठा ast_vhub_req *req = to_ast_req(u_req);
	काष्ठा ast_vhub_ep *ep = to_ast_ep(u_ep);
	काष्ठा ast_vhub *vhub = ep->vhub;
	काष्ठा device *dev = &vhub->pdev->dev;
	अचिन्हित दीर्घ flags;

	/* Paranoid cheks */
	अगर (!u_req || (!u_req->complete && !req->पूर्णांकernal)) अणु
		dev_warn(dev, "Bogus EP0 request ! u_req=%p\n", u_req);
		अगर (u_req) अणु
			dev_warn(dev, "complete=%p internal=%d\n",
				 u_req->complete, req->पूर्णांकernal);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	/* Not endpoपूर्णांक 0 ? */
	अगर (WARN_ON(ep->d_idx != 0))
		वापस -EINVAL;

	/* Disabled device */
	अगर (ep->dev && !ep->dev->enabled)
		वापस -ESHUTDOWN;

	/* Data, no buffer and not पूर्णांकernal ? */
	अगर (u_req->length && !u_req->buf && !req->पूर्णांकernal) अणु
		dev_warn(dev, "Request with no buffer !\n");
		वापस -EINVAL;
	पूर्ण

	EPVDBG(ep, "enqueue req @%p\n", req);
	EPVDBG(ep, "  l=%d zero=%d noshort=%d is_in=%d\n",
	       u_req->length, u_req->zero,
	       u_req->लघु_not_ok, ep->ep0.dir_in);

	/* Initialize request progress fields */
	u_req->status = -EINPROGRESS;
	u_req->actual = 0;
	req->last_desc = -1;
	req->active = false;

	spin_lock_irqsave(&vhub->lock, flags);

	/* EP0 can only support a single request at a समय */
	अगर (!list_empty(&ep->queue) ||
	    ep->ep0.state == ep0_state_token ||
	    ep->ep0.state == ep0_state_stall) अणु
		dev_warn(dev, "EP0: Request in wrong state\n");
	        EPVDBG(ep, "EP0: list_empty=%d state=%d\n",
		       list_empty(&ep->queue), ep->ep0.state);
		spin_unlock_irqrestore(&vhub->lock, flags);
		वापस -EBUSY;
	पूर्ण

	/* Add request to list and kick processing अगर empty */
	list_add_tail(&req->queue, &ep->queue);

	अगर (ep->ep0.dir_in) अणु
		/* IN request, send data */
		ast_vhub_ep0_करो_send(ep, req);
	पूर्ण अन्यथा अगर (u_req->length == 0) अणु
		/* 0-len request, send completion as rx */
		EPVDBG(ep, "0-length rx completion\n");
		ep->ep0.state = ep0_state_status;
		ग_लिखोl(VHUB_EP0_TX_BUFF_RDY, ep->ep0.ctlstat);
		ast_vhub_करोne(ep, req, 0);
	पूर्ण अन्यथा अणु
		/* OUT request, start receiver */
		ast_vhub_ep0_rx_prime(ep);
	पूर्ण

	spin_unlock_irqrestore(&vhub->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ast_vhub_ep0_dequeue(काष्ठा usb_ep* u_ep, काष्ठा usb_request *u_req)
अणु
	काष्ठा ast_vhub_ep *ep = to_ast_ep(u_ep);
	काष्ठा ast_vhub *vhub = ep->vhub;
	काष्ठा ast_vhub_req *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -EINVAL;

	spin_lock_irqsave(&vhub->lock, flags);

	/* Only one request can be in the queue */
	req = list_first_entry_or_null(&ep->queue, काष्ठा ast_vhub_req, queue);

	/* Is it ours ? */
	अगर (req && u_req == &req->req) अणु
		EPVDBG(ep, "dequeue req @%p\n", req);

		/*
		 * We करोn't have to deal with "active" as all
		 * DMAs go to the EP buffers, not the request.
		 */
		ast_vhub_करोne(ep, req, -ECONNRESET);

		/* We करो stall the EP to clean things up in HW */
		ग_लिखोl(VHUB_EP0_CTRL_STALL, ep->ep0.ctlstat);
		ep->ep0.state = ep0_state_status;
		ep->ep0.dir_in = false;
		rc = 0;
	पूर्ण
	spin_unlock_irqrestore(&vhub->lock, flags);
	वापस rc;
पूर्ण


अटल स्थिर काष्ठा usb_ep_ops ast_vhub_ep0_ops = अणु
	.queue		= ast_vhub_ep0_queue,
	.dequeue	= ast_vhub_ep0_dequeue,
	.alloc_request	= ast_vhub_alloc_request,
	.मुक्त_request	= ast_vhub_मुक्त_request,
पूर्ण;

व्योम ast_vhub_reset_ep0(काष्ठा ast_vhub_dev *dev)
अणु
	काष्ठा ast_vhub_ep *ep = &dev->ep0;

	ast_vhub_nuke(ep, -EIO);
	ep->ep0.state = ep0_state_token;
पूर्ण


व्योम ast_vhub_init_ep0(काष्ठा ast_vhub *vhub, काष्ठा ast_vhub_ep *ep,
		       काष्ठा ast_vhub_dev *dev)
अणु
	स_रखो(ep, 0, माप(*ep));

	INIT_LIST_HEAD(&ep->ep.ep_list);
	INIT_LIST_HEAD(&ep->queue);
	ep->ep.ops = &ast_vhub_ep0_ops;
	ep->ep.name = "ep0";
	ep->ep.caps.type_control = true;
	usb_ep_set_maxpacket_limit(&ep->ep, AST_VHUB_EP0_MAX_PACKET);
	ep->d_idx = 0;
	ep->dev = dev;
	ep->vhub = vhub;
	ep->ep0.state = ep0_state_token;
	INIT_LIST_HEAD(&ep->ep0.req.queue);
	ep->ep0.req.पूर्णांकernal = true;

	/* Small dअगरference between vHub and devices */
	अगर (dev) अणु
		ep->ep0.ctlstat = dev->regs + AST_VHUB_DEV_EP0_CTRL;
		ep->ep0.setup = vhub->regs +
			AST_VHUB_SETUP0 + 8 * (dev->index + 1);
		ep->buf = vhub->ep0_bufs +
			AST_VHUB_EP0_MAX_PACKET * (dev->index + 1);
		ep->buf_dma = vhub->ep0_bufs_dma +
			AST_VHUB_EP0_MAX_PACKET * (dev->index + 1);
	पूर्ण अन्यथा अणु
		ep->ep0.ctlstat = vhub->regs + AST_VHUB_EP0_CTRL;
		ep->ep0.setup = vhub->regs + AST_VHUB_SETUP0;
		ep->buf = vhub->ep0_bufs;
		ep->buf_dma = vhub->ep0_bufs_dma;
	पूर्ण
पूर्ण
