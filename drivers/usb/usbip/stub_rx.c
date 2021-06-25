<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 */

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/scatterlist.h>

#समावेश "usbip_common.h"
#समावेश "stub.h"

अटल पूर्णांक is_clear_halt_cmd(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req;

	req = (काष्ठा usb_ctrlrequest *) urb->setup_packet;

	वापस (req->bRequest == USB_REQ_CLEAR_FEATURE) &&
	       (req->bRequestType == USB_RECIP_ENDPOINT) &&
	       (req->wValue == USB_ENDPOINT_HALT);
पूर्ण

अटल पूर्णांक is_set_पूर्णांकerface_cmd(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req;

	req = (काष्ठा usb_ctrlrequest *) urb->setup_packet;

	वापस (req->bRequest == USB_REQ_SET_INTERFACE) &&
		(req->bRequestType == USB_RECIP_INTERFACE);
पूर्ण

अटल पूर्णांक is_set_configuration_cmd(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req;

	req = (काष्ठा usb_ctrlrequest *) urb->setup_packet;

	वापस (req->bRequest == USB_REQ_SET_CONFIGURATION) &&
		(req->bRequestType == USB_RECIP_DEVICE);
पूर्ण

अटल पूर्णांक is_reset_device_cmd(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req;
	__u16 value;
	__u16 index;

	req = (काष्ठा usb_ctrlrequest *) urb->setup_packet;
	value = le16_to_cpu(req->wValue);
	index = le16_to_cpu(req->wIndex);

	अगर ((req->bRequest == USB_REQ_SET_FEATURE) &&
	    (req->bRequestType == USB_RT_PORT) &&
	    (value == USB_PORT_FEAT_RESET)) अणु
		usbip_dbg_stub_rx("reset_device_cmd, port %u\n", index);
		वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक tweak_clear_halt_cmd(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req;
	पूर्णांक target_endp;
	पूर्णांक target_dir;
	पूर्णांक target_pipe;
	पूर्णांक ret;

	req = (काष्ठा usb_ctrlrequest *) urb->setup_packet;

	/*
	 * The stalled endpoपूर्णांक is specअगरied in the wIndex value. The endpoपूर्णांक
	 * of the urb is the target of this clear_halt request (i.e., control
	 * endpoपूर्णांक).
	 */
	target_endp = le16_to_cpu(req->wIndex) & 0x000f;

	/* the stalled endpoपूर्णांक direction is IN or OUT?. USB_सूची_IN is 0x80.  */
	target_dir = le16_to_cpu(req->wIndex) & 0x0080;

	अगर (target_dir)
		target_pipe = usb_rcvctrlpipe(urb->dev, target_endp);
	अन्यथा
		target_pipe = usb_sndctrlpipe(urb->dev, target_endp);

	ret = usb_clear_halt(urb->dev, target_pipe);
	अगर (ret < 0)
		dev_err(&urb->dev->dev,
			"usb_clear_halt error: devnum %d endp %d ret %d\n",
			urb->dev->devnum, target_endp, ret);
	अन्यथा
		dev_info(&urb->dev->dev,
			 "usb_clear_halt done: devnum %d endp %d\n",
			 urb->dev->devnum, target_endp);

	वापस ret;
पूर्ण

अटल पूर्णांक tweak_set_पूर्णांकerface_cmd(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req;
	__u16 alternate;
	__u16 पूर्णांकerface;
	पूर्णांक ret;

	req = (काष्ठा usb_ctrlrequest *) urb->setup_packet;
	alternate = le16_to_cpu(req->wValue);
	पूर्णांकerface = le16_to_cpu(req->wIndex);

	usbip_dbg_stub_rx("set_interface: inf %u alt %u\n",
			  पूर्णांकerface, alternate);

	ret = usb_set_पूर्णांकerface(urb->dev, पूर्णांकerface, alternate);
	अगर (ret < 0)
		dev_err(&urb->dev->dev,
			"usb_set_interface error: inf %u alt %u ret %d\n",
			पूर्णांकerface, alternate, ret);
	अन्यथा
		dev_info(&urb->dev->dev,
			"usb_set_interface done: inf %u alt %u\n",
			पूर्णांकerface, alternate);

	वापस ret;
पूर्ण

अटल पूर्णांक tweak_set_configuration_cmd(काष्ठा urb *urb)
अणु
	काष्ठा stub_priv *priv = (काष्ठा stub_priv *) urb->context;
	काष्ठा stub_device *sdev = priv->sdev;
	काष्ठा usb_ctrlrequest *req;
	__u16 config;
	पूर्णांक err;

	req = (काष्ठा usb_ctrlrequest *) urb->setup_packet;
	config = le16_to_cpu(req->wValue);

	err = usb_set_configuration(sdev->udev, config);
	अगर (err && err != -ENODEV)
		dev_err(&sdev->udev->dev, "can't set config #%d, error %d\n",
			config, err);
	वापस 0;
पूर्ण

अटल पूर्णांक tweak_reset_device_cmd(काष्ठा urb *urb)
अणु
	काष्ठा stub_priv *priv = (काष्ठा stub_priv *) urb->context;
	काष्ठा stub_device *sdev = priv->sdev;

	dev_info(&urb->dev->dev, "usb_queue_reset_device\n");

	अगर (usb_lock_device_क्रम_reset(sdev->udev, शून्य) < 0) अणु
		dev_err(&urb->dev->dev, "could not obtain lock to reset device\n");
		वापस 0;
	पूर्ण
	usb_reset_device(sdev->udev);
	usb_unlock_device(sdev->udev);

	वापस 0;
पूर्ण

/*
 * clear_halt, set_पूर्णांकerface, and set_configuration require special tricks.
 */
अटल व्योम tweak_special_requests(काष्ठा urb *urb)
अणु
	अगर (!urb || !urb->setup_packet)
		वापस;

	अगर (usb_pipetype(urb->pipe) != PIPE_CONTROL)
		वापस;

	अगर (is_clear_halt_cmd(urb))
		/* tweak clear_halt */
		 tweak_clear_halt_cmd(urb);

	अन्यथा अगर (is_set_पूर्णांकerface_cmd(urb))
		/* tweak set_पूर्णांकerface */
		tweak_set_पूर्णांकerface_cmd(urb);

	अन्यथा अगर (is_set_configuration_cmd(urb))
		/* tweak set_configuration */
		tweak_set_configuration_cmd(urb);

	अन्यथा अगर (is_reset_device_cmd(urb))
		tweak_reset_device_cmd(urb);
	अन्यथा
		usbip_dbg_stub_rx("no need to tweak\n");
पूर्ण

/*
 * stub_recv_unlink() unlinks the URB by a call to usb_unlink_urb().
 * By unlinking the urb asynchronously, stub_rx can continuously
 * process coming urbs.  Even अगर the urb is unlinked, its completion
 * handler will be called and stub_tx will send a वापस pdu.
 *
 * See also comments about unlinking strategy in vhci_hcd.c.
 */
अटल पूर्णांक stub_recv_cmd_unlink(काष्ठा stub_device *sdev,
				काष्ठा usbip_header *pdu)
अणु
	पूर्णांक ret, i;
	अचिन्हित दीर्घ flags;
	काष्ठा stub_priv *priv;

	spin_lock_irqsave(&sdev->priv_lock, flags);

	list_क्रम_each_entry(priv, &sdev->priv_init, list) अणु
		अगर (priv->seqnum != pdu->u.cmd_unlink.seqnum)
			जारी;

		/*
		 * This matched urb is not completed yet (i.e., be in
		 * flight in usb hcd hardware/driver). Now we are
		 * cancelling it. The unlinking flag means that we are
		 * now not going to वापस the normal result pdu of a
		 * submission request, but going to वापस a result pdu
		 * of the unlink request.
		 */
		priv->unlinking = 1;

		/*
		 * In the हाल that unlinking flag is on, prev->seqnum
		 * is changed from the seqnum of the cancelling urb to
		 * the seqnum of the unlink request. This will be used
		 * to make the result pdu of the unlink request.
		 */
		priv->seqnum = pdu->base.seqnum;

		spin_unlock_irqrestore(&sdev->priv_lock, flags);

		/*
		 * usb_unlink_urb() is now out of spinlocking to aव्योम
		 * spinlock recursion since stub_complete() is
		 * someबार called in this context but not in the
		 * पूर्णांकerrupt context.  If stub_complete() is executed
		 * beक्रमe we call usb_unlink_urb(), usb_unlink_urb()
		 * will वापस an error value. In this हाल, stub_tx
		 * will वापस the result pdu of this unlink request
		 * though submission is completed and actual unlinking
		 * is not executed. OK?
		 */
		/* In the above हाल, urb->status is not -ECONNRESET,
		 * so a driver in a client host will know the failure
		 * of the unlink request ?
		 */
		क्रम (i = priv->completed_urbs; i < priv->num_urbs; i++) अणु
			ret = usb_unlink_urb(priv->urbs[i]);
			अगर (ret != -EINPROGRESS)
				dev_err(&priv->urbs[i]->dev->dev,
					"failed to unlink %d/%d urb of seqnum %lu, ret %d\n",
					i + 1, priv->num_urbs,
					priv->seqnum, ret);
		पूर्ण
		वापस 0;
	पूर्ण

	usbip_dbg_stub_rx("seqnum %d is not pending\n",
			  pdu->u.cmd_unlink.seqnum);

	/*
	 * The urb of the unlink target is not found in priv_init queue. It was
	 * alपढ़ोy completed and its results is/was going to be sent by a
	 * CMD_RET pdu. In this हाल, usb_unlink_urb() is not needed. We only
	 * वापस the completeness of this unlink request to vhci_hcd.
	 */
	stub_enqueue_ret_unlink(sdev, pdu->base.seqnum, 0);

	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक valid_request(काष्ठा stub_device *sdev, काष्ठा usbip_header *pdu)
अणु
	काष्ठा usbip_device *ud = &sdev->ud;
	पूर्णांक valid = 0;

	अगर (pdu->base.devid == sdev->devid) अणु
		spin_lock_irq(&ud->lock);
		अगर (ud->status == SDEV_ST_USED) अणु
			/* A request is valid. */
			valid = 1;
		पूर्ण
		spin_unlock_irq(&ud->lock);
	पूर्ण

	वापस valid;
पूर्ण

अटल काष्ठा stub_priv *stub_priv_alloc(काष्ठा stub_device *sdev,
					 काष्ठा usbip_header *pdu)
अणु
	काष्ठा stub_priv *priv;
	काष्ठा usbip_device *ud = &sdev->ud;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sdev->priv_lock, flags);

	priv = kmem_cache_zalloc(stub_priv_cache, GFP_ATOMIC);
	अगर (!priv) अणु
		dev_err(&sdev->udev->dev, "alloc stub_priv\n");
		spin_unlock_irqrestore(&sdev->priv_lock, flags);
		usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
		वापस शून्य;
	पूर्ण

	priv->seqnum = pdu->base.seqnum;
	priv->sdev = sdev;

	/*
	 * After a stub_priv is linked to a list_head,
	 * our error handler can मुक्त allocated data.
	 */
	list_add_tail(&priv->list, &sdev->priv_init);

	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	वापस priv;
पूर्ण

अटल पूर्णांक get_pipe(काष्ठा stub_device *sdev, काष्ठा usbip_header *pdu)
अणु
	काष्ठा usb_device *udev = sdev->udev;
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd = शून्य;
	पूर्णांक epnum = pdu->base.ep;
	पूर्णांक dir = pdu->base.direction;

	अगर (epnum < 0 || epnum > 15)
		जाओ err_ret;

	अगर (dir == USBIP_सूची_IN)
		ep = udev->ep_in[epnum & 0x7f];
	अन्यथा
		ep = udev->ep_out[epnum & 0x7f];
	अगर (!ep)
		जाओ err_ret;

	epd = &ep->desc;

	अगर (usb_endpoपूर्णांक_xfer_control(epd)) अणु
		अगर (dir == USBIP_सूची_OUT)
			वापस usb_sndctrlpipe(udev, epnum);
		अन्यथा
			वापस usb_rcvctrlpipe(udev, epnum);
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_bulk(epd)) अणु
		अगर (dir == USBIP_सूची_OUT)
			वापस usb_sndbulkpipe(udev, epnum);
		अन्यथा
			वापस usb_rcvbulkpipe(udev, epnum);
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(epd)) अणु
		अगर (dir == USBIP_सूची_OUT)
			वापस usb_sndपूर्णांकpipe(udev, epnum);
		अन्यथा
			वापस usb_rcvपूर्णांकpipe(udev, epnum);
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_isoc(epd)) अणु
		/* validate number of packets */
		अगर (pdu->u.cmd_submit.number_of_packets < 0 ||
		    pdu->u.cmd_submit.number_of_packets >
		    USBIP_MAX_ISO_PACKETS) अणु
			dev_err(&sdev->udev->dev,
				"CMD_SUBMIT: isoc invalid num packets %d\n",
				pdu->u.cmd_submit.number_of_packets);
			वापस -1;
		पूर्ण
		अगर (dir == USBIP_सूची_OUT)
			वापस usb_sndisocpipe(udev, epnum);
		अन्यथा
			वापस usb_rcvisocpipe(udev, epnum);
	पूर्ण

err_ret:
	/* NOT REACHED */
	dev_err(&sdev->udev->dev, "CMD_SUBMIT: invalid epnum %d\n", epnum);
	वापस -1;
पूर्ण

अटल व्योम masking_bogus_flags(काष्ठा urb *urb)
अणु
	पूर्णांक				xfertype;
	काष्ठा usb_device		*dev;
	काष्ठा usb_host_endpoपूर्णांक	*ep;
	पूर्णांक				is_out;
	अचिन्हित पूर्णांक	allowed;

	अगर (!urb || urb->hcpriv || !urb->complete)
		वापस;
	dev = urb->dev;
	अगर ((!dev) || (dev->state < USB_STATE_UNAUTHENTICATED))
		वापस;

	ep = (usb_pipein(urb->pipe) ? dev->ep_in : dev->ep_out)
		[usb_pipeendpoपूर्णांक(urb->pipe)];
	अगर (!ep)
		वापस;

	xfertype = usb_endpoपूर्णांक_type(&ep->desc);
	अगर (xfertype == USB_ENDPOINT_XFER_CONTROL) अणु
		काष्ठा usb_ctrlrequest *setup =
			(काष्ठा usb_ctrlrequest *) urb->setup_packet;

		अगर (!setup)
			वापस;
		is_out = !(setup->bRequestType & USB_सूची_IN) ||
			!setup->wLength;
	पूर्ण अन्यथा अणु
		is_out = usb_endpoपूर्णांक_dir_out(&ep->desc);
	पूर्ण

	/* enक्रमce simple/standard policy */
	allowed = (URB_NO_TRANSFER_DMA_MAP | URB_NO_INTERRUPT |
		   URB_सूची_MASK | URB_FREE_BUFFER);
	चयन (xfertype) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (is_out)
			allowed |= URB_ZERO_PACKET;
		fallthrough;
	शेष:			/* all non-iso endpoपूर्णांकs */
		अगर (!is_out)
			allowed |= URB_SHORT_NOT_OK;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		allowed |= URB_ISO_ASAP;
		अवरोध;
	पूर्ण
	urb->transfer_flags &= allowed;
पूर्ण

अटल पूर्णांक stub_recv_xbuff(काष्ठा usbip_device *ud, काष्ठा stub_priv *priv)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_urbs; i++) अणु
		ret = usbip_recv_xbuff(ud, priv->urbs[i]);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम stub_recv_cmd_submit(काष्ठा stub_device *sdev,
				 काष्ठा usbip_header *pdu)
अणु
	काष्ठा stub_priv *priv;
	काष्ठा usbip_device *ud = &sdev->ud;
	काष्ठा usb_device *udev = sdev->udev;
	काष्ठा scatterlist *sgl = शून्य, *sg;
	व्योम *buffer = शून्य;
	अचिन्हित दीर्घ दीर्घ buf_len;
	पूर्णांक nents;
	पूर्णांक num_urbs = 1;
	पूर्णांक pipe = get_pipe(sdev, pdu);
	पूर्णांक use_sg = pdu->u.cmd_submit.transfer_flags & URB_DMA_MAP_SG;
	पूर्णांक support_sg = 1;
	पूर्णांक np = 0;
	पूर्णांक ret, i;

	अगर (pipe == -1)
		वापस;

	/*
	 * Smatch reported the error हाल where use_sg is true and buf_len is 0.
	 * In this हाल, It adds SDEV_EVENT_ERROR_MALLOC and stub_priv will be
	 * released by stub event handler and connection will be shut करोwn.
	 */
	priv = stub_priv_alloc(sdev, pdu);
	अगर (!priv)
		वापस;

	buf_len = (अचिन्हित दीर्घ दीर्घ)pdu->u.cmd_submit.transfer_buffer_length;

	अगर (use_sg && !buf_len) अणु
		dev_err(&udev->dev, "sg buffer with zero length\n");
		जाओ err_दो_स्मृति;
	पूर्ण

	/* allocate urb transfer buffer, अगर needed */
	अगर (buf_len) अणु
		अगर (use_sg) अणु
			sgl = sgl_alloc(buf_len, GFP_KERNEL, &nents);
			अगर (!sgl)
				जाओ err_दो_स्मृति;

			/* Check अगर the server's HCD supports SG */
			अगर (!udev->bus->sg_tablesize) अणु
				/*
				 * If the server's HCD doesn't support SG, अवरोध
				 * a single SG request पूर्णांकo several URBs and map
				 * each SG list entry to corresponding URB
				 * buffer. The previously allocated SG list is
				 * stored in priv->sgl (If the server's HCD
				 * support SG, SG list is stored only in
				 * urb->sg) and it is used as an indicator that
				 * the server split single SG request पूर्णांकo
				 * several URBs. Later, priv->sgl is used by
				 * stub_complete() and stub_send_ret_submit() to
				 * reassemble the भागied URBs.
				 */
				support_sg = 0;
				num_urbs = nents;
				priv->completed_urbs = 0;
				pdu->u.cmd_submit.transfer_flags &=
								~URB_DMA_MAP_SG;
			पूर्ण
		पूर्ण अन्यथा अणु
			buffer = kzalloc(buf_len, GFP_KERNEL);
			अगर (!buffer)
				जाओ err_दो_स्मृति;
		पूर्ण
	पूर्ण

	/* allocate urb array */
	priv->num_urbs = num_urbs;
	priv->urbs = kदो_स्मृति_array(num_urbs, माप(*priv->urbs), GFP_KERNEL);
	अगर (!priv->urbs)
		जाओ err_urbs;

	/* setup a urb */
	अगर (support_sg) अणु
		अगर (usb_pipeisoc(pipe))
			np = pdu->u.cmd_submit.number_of_packets;

		priv->urbs[0] = usb_alloc_urb(np, GFP_KERNEL);
		अगर (!priv->urbs[0])
			जाओ err_urb;

		अगर (buf_len) अणु
			अगर (use_sg) अणु
				priv->urbs[0]->sg = sgl;
				priv->urbs[0]->num_sgs = nents;
				priv->urbs[0]->transfer_buffer = शून्य;
			पूर्ण अन्यथा अणु
				priv->urbs[0]->transfer_buffer = buffer;
			पूर्ण
		पूर्ण

		/* copy urb setup packet */
		priv->urbs[0]->setup_packet = kmemdup(&pdu->u.cmd_submit.setup,
					8, GFP_KERNEL);
		अगर (!priv->urbs[0]->setup_packet) अणु
			usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
			वापस;
		पूर्ण

		usbip_pack_pdu(pdu, priv->urbs[0], USBIP_CMD_SUBMIT, 0);
	पूर्ण अन्यथा अणु
		क्रम_each_sg(sgl, sg, nents, i) अणु
			priv->urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
			/* The URBs which is previously allocated will be मुक्तd
			 * in stub_device_cleanup_urbs() अगर error occurs.
			 */
			अगर (!priv->urbs[i])
				जाओ err_urb;

			usbip_pack_pdu(pdu, priv->urbs[i], USBIP_CMD_SUBMIT, 0);
			priv->urbs[i]->transfer_buffer = sg_virt(sg);
			priv->urbs[i]->transfer_buffer_length = sg->length;
		पूर्ण
		priv->sgl = sgl;
	पूर्ण

	क्रम (i = 0; i < num_urbs; i++) अणु
		/* set other members from the base header of pdu */
		priv->urbs[i]->context = (व्योम *) priv;
		priv->urbs[i]->dev = udev;
		priv->urbs[i]->pipe = pipe;
		priv->urbs[i]->complete = stub_complete;

		/* no need to submit an पूर्णांकercepted request, but harmless? */
		tweak_special_requests(priv->urbs[i]);

		masking_bogus_flags(priv->urbs[i]);
	पूर्ण

	अगर (stub_recv_xbuff(ud, priv) < 0)
		वापस;

	अगर (usbip_recv_iso(ud, priv->urbs[0]) < 0)
		वापस;

	/* urb is now पढ़ोy to submit */
	क्रम (i = 0; i < priv->num_urbs; i++) अणु
		ret = usb_submit_urb(priv->urbs[i], GFP_KERNEL);

		अगर (ret == 0)
			usbip_dbg_stub_rx("submit urb ok, seqnum %u\n",
					pdu->base.seqnum);
		अन्यथा अणु
			dev_err(&udev->dev, "submit_urb error, %d\n", ret);
			usbip_dump_header(pdu);
			usbip_dump_urb(priv->urbs[i]);

			/*
			 * Pessimistic.
			 * This connection will be discarded.
			 */
			usbip_event_add(ud, SDEV_EVENT_ERROR_SUBMIT);
			अवरोध;
		पूर्ण
	पूर्ण

	usbip_dbg_stub_rx("Leave\n");
	वापस;

err_urb:
	kमुक्त(priv->urbs);
err_urbs:
	kमुक्त(buffer);
	sgl_मुक्त(sgl);
err_दो_स्मृति:
	usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
पूर्ण

/* recv a pdu */
अटल व्योम stub_rx_pdu(काष्ठा usbip_device *ud)
अणु
	पूर्णांक ret;
	काष्ठा usbip_header pdu;
	काष्ठा stub_device *sdev = container_of(ud, काष्ठा stub_device, ud);
	काष्ठा device *dev = &sdev->udev->dev;

	usbip_dbg_stub_rx("Enter\n");

	स_रखो(&pdu, 0, माप(pdu));

	/* receive a pdu header */
	ret = usbip_recv(ud->tcp_socket, &pdu, माप(pdu));
	अगर (ret != माप(pdu)) अणु
		dev_err(dev, "recv a header, %d\n", ret);
		usbip_event_add(ud, SDEV_EVENT_ERROR_TCP);
		वापस;
	पूर्ण

	usbip_header_correct_endian(&pdu, 0);

	अगर (usbip_dbg_flag_stub_rx)
		usbip_dump_header(&pdu);

	अगर (!valid_request(sdev, &pdu)) अणु
		dev_err(dev, "recv invalid request\n");
		usbip_event_add(ud, SDEV_EVENT_ERROR_TCP);
		वापस;
	पूर्ण

	चयन (pdu.base.command) अणु
	हाल USBIP_CMD_UNLINK:
		stub_recv_cmd_unlink(sdev, &pdu);
		अवरोध;

	हाल USBIP_CMD_SUBMIT:
		stub_recv_cmd_submit(sdev, &pdu);
		अवरोध;

	शेष:
		/* NOTREACHED */
		dev_err(dev, "unknown pdu\n");
		usbip_event_add(ud, SDEV_EVENT_ERROR_TCP);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक stub_rx_loop(व्योम *data)
अणु
	काष्ठा usbip_device *ud = data;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (usbip_event_happened(ud))
			अवरोध;

		stub_rx_pdu(ud);
	पूर्ण

	वापस 0;
पूर्ण
