<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/socket.h>
#समावेश <linux/scatterlist.h>

#समावेश "usbip_common.h"
#समावेश "stub.h"

/* be in spin_lock_irqsave(&sdev->priv_lock, flags) */
व्योम stub_enqueue_ret_unlink(काष्ठा stub_device *sdev, __u32 seqnum,
			     __u32 status)
अणु
	काष्ठा stub_unlink *unlink;

	unlink = kzalloc(माप(काष्ठा stub_unlink), GFP_ATOMIC);
	अगर (!unlink) अणु
		usbip_event_add(&sdev->ud, VDEV_EVENT_ERROR_MALLOC);
		वापस;
	पूर्ण

	unlink->seqnum = seqnum;
	unlink->status = status;

	list_add_tail(&unlink->list, &sdev->unlink_tx);
पूर्ण

/**
 * stub_complete - completion handler of a usbip urb
 * @urb: poपूर्णांकer to the urb completed
 *
 * When a urb has completed, the USB core driver calls this function mostly in
 * the पूर्णांकerrupt context. To वापस the result of a urb, the completed urb is
 * linked to the pending list of वापसing.
 *
 */
व्योम stub_complete(काष्ठा urb *urb)
अणु
	काष्ठा stub_priv *priv = (काष्ठा stub_priv *) urb->context;
	काष्ठा stub_device *sdev = priv->sdev;
	अचिन्हित दीर्घ flags;

	usbip_dbg_stub_tx("complete! status %d\n", urb->status);

	चयन (urb->status) अणु
	हाल 0:
		/* OK */
		अवरोध;
	हाल -ENOENT:
		dev_info(&urb->dev->dev,
			 "stopped by a call to usb_kill_urb() because of cleaning up a virtual connection\n");
		वापस;
	हाल -ECONNRESET:
		dev_info(&urb->dev->dev,
			 "unlinked by a call to usb_unlink_urb()\n");
		अवरोध;
	हाल -EPIPE:
		dev_info(&urb->dev->dev, "endpoint %d is stalled\n",
			 usb_pipeendpoपूर्णांक(urb->pipe));
		अवरोध;
	हाल -ESHUTDOWN:
		dev_info(&urb->dev->dev, "device removed?\n");
		अवरोध;
	शेष:
		dev_info(&urb->dev->dev,
			 "urb completion with non-zero status %d\n",
			 urb->status);
		अवरोध;
	पूर्ण

	/*
	 * If the server अवरोधs single SG request पूर्णांकo the several URBs, the
	 * URBs must be reassembled beक्रमe sending completed URB to the vhci.
	 * Don't wake up the tx thपढ़ो until all the URBs are completed.
	 */
	अगर (priv->sgl) अणु
		priv->completed_urbs++;

		/* Only save the first error status */
		अगर (urb->status && !priv->urb_status)
			priv->urb_status = urb->status;

		अगर (priv->completed_urbs < priv->num_urbs)
			वापस;
	पूर्ण

	/* link a urb to the queue of tx. */
	spin_lock_irqsave(&sdev->priv_lock, flags);
	अगर (sdev->ud.tcp_socket == शून्य) अणु
		usbip_dbg_stub_tx("ignore urb for closed connection\n");
		/* It will be मुक्तd in stub_device_cleanup_urbs(). */
	पूर्ण अन्यथा अगर (priv->unlinking) अणु
		stub_enqueue_ret_unlink(sdev, priv->seqnum, urb->status);
		stub_मुक्त_priv_and_urb(priv);
	पूर्ण अन्यथा अणु
		list_move_tail(&priv->list, &sdev->priv_tx);
	पूर्ण
	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	/* wake up tx_thपढ़ो */
	wake_up(&sdev->tx_रुकोq);
पूर्ण

अटल अंतरभूत व्योम setup_base_pdu(काष्ठा usbip_header_basic *base,
				  __u32 command, __u32 seqnum)
अणु
	base->command	= command;
	base->seqnum	= seqnum;
	base->devid	= 0;
	base->ep	= 0;
	base->direction = 0;
पूर्ण

अटल व्योम setup_ret_submit_pdu(काष्ठा usbip_header *rpdu, काष्ठा urb *urb)
अणु
	काष्ठा stub_priv *priv = (काष्ठा stub_priv *) urb->context;

	setup_base_pdu(&rpdu->base, USBIP_RET_SUBMIT, priv->seqnum);
	usbip_pack_pdu(rpdu, urb, USBIP_RET_SUBMIT, 1);
पूर्ण

अटल व्योम setup_ret_unlink_pdu(काष्ठा usbip_header *rpdu,
				 काष्ठा stub_unlink *unlink)
अणु
	setup_base_pdu(&rpdu->base, USBIP_RET_UNLINK, unlink->seqnum);
	rpdu->u.ret_unlink.status = unlink->status;
पूर्ण

अटल काष्ठा stub_priv *dequeue_from_priv_tx(काष्ठा stub_device *sdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा stub_priv *priv, *पंचांगp;

	spin_lock_irqsave(&sdev->priv_lock, flags);

	list_क्रम_each_entry_safe(priv, पंचांगp, &sdev->priv_tx, list) अणु
		list_move_tail(&priv->list, &sdev->priv_मुक्त);
		spin_unlock_irqrestore(&sdev->priv_lock, flags);
		वापस priv;
	पूर्ण

	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	वापस शून्य;
पूर्ण

अटल पूर्णांक stub_send_ret_submit(काष्ठा stub_device *sdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा stub_priv *priv, *पंचांगp;

	काष्ठा msghdr msg;
	माप_प्रकार txsize;

	माप_प्रकार total_size = 0;

	जबतक ((priv = dequeue_from_priv_tx(sdev)) != शून्य) अणु
		काष्ठा urb *urb = priv->urbs[0];
		काष्ठा usbip_header pdu_header;
		काष्ठा usbip_iso_packet_descriptor *iso_buffer = शून्य;
		काष्ठा kvec *iov = शून्य;
		काष्ठा scatterlist *sg;
		u32 actual_length = 0;
		पूर्णांक iovnum = 0;
		पूर्णांक ret;
		पूर्णांक i;

		txsize = 0;
		स_रखो(&pdu_header, 0, माप(pdu_header));
		स_रखो(&msg, 0, माप(msg));

		अगर (urb->actual_length > 0 && !urb->transfer_buffer &&
		   !urb->num_sgs) अणु
			dev_err(&sdev->udev->dev,
				"urb: actual_length %d transfer_buffer null\n",
				urb->actual_length);
			वापस -1;
		पूर्ण

		अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS)
			iovnum = 2 + urb->number_of_packets;
		अन्यथा अगर (usb_pipein(urb->pipe) && urb->actual_length > 0 &&
			urb->num_sgs)
			iovnum = 1 + urb->num_sgs;
		अन्यथा अगर (usb_pipein(urb->pipe) && priv->sgl)
			iovnum = 1 + priv->num_urbs;
		अन्यथा
			iovnum = 2;

		iov = kसुस्मृति(iovnum, माप(काष्ठा kvec), GFP_KERNEL);

		अगर (!iov) अणु
			usbip_event_add(&sdev->ud, SDEV_EVENT_ERROR_MALLOC);
			वापस -1;
		पूर्ण

		iovnum = 0;

		/* 1. setup usbip_header */
		setup_ret_submit_pdu(&pdu_header, urb);
		usbip_dbg_stub_tx("setup txdata seqnum: %d\n",
				  pdu_header.base.seqnum);

		अगर (priv->sgl) अणु
			क्रम (i = 0; i < priv->num_urbs; i++)
				actual_length += priv->urbs[i]->actual_length;

			pdu_header.u.ret_submit.status = priv->urb_status;
			pdu_header.u.ret_submit.actual_length = actual_length;
		पूर्ण

		usbip_header_correct_endian(&pdu_header, 1);

		iov[iovnum].iov_base = &pdu_header;
		iov[iovnum].iov_len  = माप(pdu_header);
		iovnum++;
		txsize += माप(pdu_header);

		/* 2. setup transfer buffer */
		अगर (usb_pipein(urb->pipe) && priv->sgl) अणु
			/* If the server split a single SG request पूर्णांकo several
			 * URBs because the server's HCD doesn't support SG,
			 * reassemble the split URB buffers पूर्णांकo a single
			 * वापस command.
			 */
			क्रम (i = 0; i < priv->num_urbs; i++) अणु
				iov[iovnum].iov_base =
					priv->urbs[i]->transfer_buffer;
				iov[iovnum].iov_len =
					priv->urbs[i]->actual_length;
				iovnum++;
			पूर्ण
			txsize += actual_length;
		पूर्ण अन्यथा अगर (usb_pipein(urb->pipe) &&
		    usb_pipetype(urb->pipe) != PIPE_ISOCHRONOUS &&
		    urb->actual_length > 0) अणु
			अगर (urb->num_sgs) अणु
				अचिन्हित पूर्णांक copy = urb->actual_length;
				पूर्णांक size;

				क्रम_each_sg(urb->sg, sg, urb->num_sgs, i) अणु
					अगर (copy == 0)
						अवरोध;

					अगर (copy < sg->length)
						size = copy;
					अन्यथा
						size = sg->length;

					iov[iovnum].iov_base = sg_virt(sg);
					iov[iovnum].iov_len = size;

					iovnum++;
					copy -= size;
				पूर्ण
			पूर्ण अन्यथा अणु
				iov[iovnum].iov_base = urb->transfer_buffer;
				iov[iovnum].iov_len  = urb->actual_length;
				iovnum++;
			पूर्ण
			txsize += urb->actual_length;
		पूर्ण अन्यथा अगर (usb_pipein(urb->pipe) &&
			   usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
			/*
			 * For isochronous packets: actual length is the sum of
			 * the actual length of the inभागidual, packets, but as
			 * the packet offsets are not changed there will be
			 * padding between the packets. To optimally use the
			 * bandwidth the padding is not transmitted.
			 */

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
				dev_err(&sdev->udev->dev,
					"actual length of urb %d does not match iso packet sizes %zu\n",
					urb->actual_length,
					txsize-माप(pdu_header));
				kमुक्त(iov);
				usbip_event_add(&sdev->ud,
						SDEV_EVENT_ERROR_TCP);
				वापस -1;
			पूर्ण
		पूर्ण

		/* 3. setup iso_packet_descriptor */
		अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
			sमाप_प्रकार len = 0;

			iso_buffer = usbip_alloc_iso_desc_pdu(urb, &len);
			अगर (!iso_buffer) अणु
				usbip_event_add(&sdev->ud,
						SDEV_EVENT_ERROR_MALLOC);
				kमुक्त(iov);
				वापस -1;
			पूर्ण

			iov[iovnum].iov_base = iso_buffer;
			iov[iovnum].iov_len  = len;
			txsize += len;
			iovnum++;
		पूर्ण

		ret = kernel_sendmsg(sdev->ud.tcp_socket, &msg,
						iov,  iovnum, txsize);
		अगर (ret != txsize) अणु
			dev_err(&sdev->udev->dev,
				"sendmsg failed!, retval %d for %zd\n",
				ret, txsize);
			kमुक्त(iov);
			kमुक्त(iso_buffer);
			usbip_event_add(&sdev->ud, SDEV_EVENT_ERROR_TCP);
			वापस -1;
		पूर्ण

		kमुक्त(iov);
		kमुक्त(iso_buffer);

		total_size += txsize;
	पूर्ण

	spin_lock_irqsave(&sdev->priv_lock, flags);
	list_क्रम_each_entry_safe(priv, पंचांगp, &sdev->priv_मुक्त, list) अणु
		stub_मुक्त_priv_and_urb(priv);
	पूर्ण
	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	वापस total_size;
पूर्ण

अटल काष्ठा stub_unlink *dequeue_from_unlink_tx(काष्ठा stub_device *sdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा stub_unlink *unlink, *पंचांगp;

	spin_lock_irqsave(&sdev->priv_lock, flags);

	list_क्रम_each_entry_safe(unlink, पंचांगp, &sdev->unlink_tx, list) अणु
		list_move_tail(&unlink->list, &sdev->unlink_मुक्त);
		spin_unlock_irqrestore(&sdev->priv_lock, flags);
		वापस unlink;
	पूर्ण

	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	वापस शून्य;
पूर्ण

अटल पूर्णांक stub_send_ret_unlink(काष्ठा stub_device *sdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा stub_unlink *unlink, *पंचांगp;

	काष्ठा msghdr msg;
	काष्ठा kvec iov[1];
	माप_प्रकार txsize;

	माप_प्रकार total_size = 0;

	जबतक ((unlink = dequeue_from_unlink_tx(sdev)) != शून्य) अणु
		पूर्णांक ret;
		काष्ठा usbip_header pdu_header;

		txsize = 0;
		स_रखो(&pdu_header, 0, माप(pdu_header));
		स_रखो(&msg, 0, माप(msg));
		स_रखो(&iov, 0, माप(iov));

		usbip_dbg_stub_tx("setup ret unlink %lu\n", unlink->seqnum);

		/* 1. setup usbip_header */
		setup_ret_unlink_pdu(&pdu_header, unlink);
		usbip_header_correct_endian(&pdu_header, 1);

		iov[0].iov_base = &pdu_header;
		iov[0].iov_len  = माप(pdu_header);
		txsize += माप(pdu_header);

		ret = kernel_sendmsg(sdev->ud.tcp_socket, &msg, iov,
				     1, txsize);
		अगर (ret != txsize) अणु
			dev_err(&sdev->udev->dev,
				"sendmsg failed!, retval %d for %zd\n",
				ret, txsize);
			usbip_event_add(&sdev->ud, SDEV_EVENT_ERROR_TCP);
			वापस -1;
		पूर्ण

		usbip_dbg_stub_tx("send txdata\n");
		total_size += txsize;
	पूर्ण

	spin_lock_irqsave(&sdev->priv_lock, flags);

	list_क्रम_each_entry_safe(unlink, पंचांगp, &sdev->unlink_मुक्त, list) अणु
		list_del(&unlink->list);
		kमुक्त(unlink);
	पूर्ण

	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	वापस total_size;
पूर्ण

पूर्णांक stub_tx_loop(व्योम *data)
अणु
	काष्ठा usbip_device *ud = data;
	काष्ठा stub_device *sdev = container_of(ud, काष्ठा stub_device, ud);

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (usbip_event_happened(ud))
			अवरोध;

		/*
		 * send_ret_submit comes earlier than send_ret_unlink.  stub_rx
		 * looks at only priv_init queue. If the completion of a URB is
		 * earlier than the receive of CMD_UNLINK, priv is moved to
		 * priv_tx queue and stub_rx करोes not find the target priv. In
		 * this हाल, vhci_rx receives the result of the submit request
		 * and then receives the result of the unlink request. The
		 * result of the submit is given back to the usbcore as the
		 * completion of the unlink request. The request of the
		 * unlink is ignored. This is ok because a driver who calls
		 * usb_unlink_urb() understands the unlink was too late by
		 * getting the status of the given-backed URB which has the
		 * status of usb_submit_urb().
		 */
		अगर (stub_send_ret_submit(sdev) < 0)
			अवरोध;

		अगर (stub_send_ret_unlink(sdev) < 0)
			अवरोध;

		रुको_event_पूर्णांकerruptible(sdev->tx_रुकोq,
					 (!list_empty(&sdev->priv_tx) ||
					  !list_empty(&sdev->unlink_tx) ||
					  kthपढ़ो_should_stop()));
	पूर्ण

	वापस 0;
पूर्ण
