<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>

#समावेश "usbip_common.h"
#समावेश "vhci.h"

अटल व्योम setup_cmd_submit_pdu(काष्ठा usbip_header *pdup,  काष्ठा urb *urb)
अणु
	काष्ठा vhci_priv *priv = ((काष्ठा vhci_priv *)urb->hcpriv);
	काष्ठा vhci_device *vdev = priv->vdev;

	usbip_dbg_vhci_tx("URB, local devnum %u, remote devid %u\n",
			  usb_pipedevice(urb->pipe), vdev->devid);

	pdup->base.command   = USBIP_CMD_SUBMIT;
	pdup->base.seqnum    = priv->seqnum;
	pdup->base.devid     = vdev->devid;
	pdup->base.direction = usb_pipein(urb->pipe) ?
		USBIP_सूची_IN : USBIP_सूची_OUT;
	pdup->base.ep	     = usb_pipeendpoपूर्णांक(urb->pipe);

	usbip_pack_pdu(pdup, urb, USBIP_CMD_SUBMIT, 1);

	अगर (urb->setup_packet)
		स_नकल(pdup->u.cmd_submit.setup, urb->setup_packet, 8);
पूर्ण

अटल काष्ठा vhci_priv *dequeue_from_priv_tx(काष्ठा vhci_device *vdev)
अणु
	काष्ठा vhci_priv *priv, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vdev->priv_lock, flags);

	list_क्रम_each_entry_safe(priv, पंचांगp, &vdev->priv_tx, list) अणु
		list_move_tail(&priv->list, &vdev->priv_rx);
		spin_unlock_irqrestore(&vdev->priv_lock, flags);
		वापस priv;
	पूर्ण

	spin_unlock_irqrestore(&vdev->priv_lock, flags);

	वापस शून्य;
पूर्ण

अटल पूर्णांक vhci_send_cmd_submit(काष्ठा vhci_device *vdev)
अणु
	काष्ठा usbip_iso_packet_descriptor *iso_buffer = शून्य;
	काष्ठा vhci_priv *priv = शून्य;
	काष्ठा scatterlist *sg;

	काष्ठा msghdr msg;
	काष्ठा kvec *iov;
	माप_प्रकार txsize;

	माप_प्रकार total_size = 0;
	पूर्णांक iovnum;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	जबतक ((priv = dequeue_from_priv_tx(vdev)) != शून्य) अणु
		पूर्णांक ret;
		काष्ठा urb *urb = priv->urb;
		काष्ठा usbip_header pdu_header;

		txsize = 0;
		स_रखो(&pdu_header, 0, माप(pdu_header));
		स_रखो(&msg, 0, माप(msg));
		स_रखो(&iov, 0, माप(iov));

		usbip_dbg_vhci_tx("setup txdata urb seqnum %lu\n",
				  priv->seqnum);

		अगर (urb->num_sgs && usb_pipeout(urb->pipe))
			iovnum = 2 + urb->num_sgs;
		अन्यथा
			iovnum = 3;

		iov = kसुस्मृति(iovnum, माप(*iov), GFP_KERNEL);
		अगर (!iov) अणु
			usbip_event_add(&vdev->ud, SDEV_EVENT_ERROR_MALLOC);
			वापस -ENOMEM;
		पूर्ण

		अगर (urb->num_sgs)
			urb->transfer_flags |= URB_DMA_MAP_SG;

		/* 1. setup usbip_header */
		setup_cmd_submit_pdu(&pdu_header, urb);
		usbip_header_correct_endian(&pdu_header, 1);
		iovnum = 0;

		iov[iovnum].iov_base = &pdu_header;
		iov[iovnum].iov_len  = माप(pdu_header);
		txsize += माप(pdu_header);
		iovnum++;

		/* 2. setup transfer buffer */
		अगर (!usb_pipein(urb->pipe) && urb->transfer_buffer_length > 0) अणु
			अगर (urb->num_sgs &&
				      !usb_endpoपूर्णांक_xfer_isoc(&urb->ep->desc)) अणु
				क्रम_each_sg(urb->sg, sg, urb->num_sgs, i) अणु
					iov[iovnum].iov_base = sg_virt(sg);
					iov[iovnum].iov_len = sg->length;
					iovnum++;
				पूर्ण
			पूर्ण अन्यथा अणु
				iov[iovnum].iov_base = urb->transfer_buffer;
				iov[iovnum].iov_len  =
						urb->transfer_buffer_length;
				iovnum++;
			पूर्ण
			txsize += urb->transfer_buffer_length;
		पूर्ण

		/* 3. setup iso_packet_descriptor */
		अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
			sमाप_प्रकार len = 0;

			iso_buffer = usbip_alloc_iso_desc_pdu(urb, &len);
			अगर (!iso_buffer) अणु
				usbip_event_add(&vdev->ud,
						SDEV_EVENT_ERROR_MALLOC);
				जाओ err_iso_buffer;
			पूर्ण

			iov[iovnum].iov_base = iso_buffer;
			iov[iovnum].iov_len  = len;
			iovnum++;
			txsize += len;
		पूर्ण

		ret = kernel_sendmsg(vdev->ud.tcp_socket, &msg, iov, iovnum,
				     txsize);
		अगर (ret != txsize) अणु
			pr_err("sendmsg failed!, ret=%d for %zd\n", ret,
			       txsize);
			usbip_event_add(&vdev->ud, VDEV_EVENT_ERROR_TCP);
			err = -EPIPE;
			जाओ err_tx;
		पूर्ण

		kमुक्त(iov);
		/* This is only क्रम isochronous हाल */
		kमुक्त(iso_buffer);
		iso_buffer = शून्य;

		usbip_dbg_vhci_tx("send txdata\n");

		total_size += txsize;
	पूर्ण

	वापस total_size;

err_tx:
	kमुक्त(iso_buffer);
err_iso_buffer:
	kमुक्त(iov);

	वापस err;
पूर्ण

अटल काष्ठा vhci_unlink *dequeue_from_unlink_tx(काष्ठा vhci_device *vdev)
अणु
	काष्ठा vhci_unlink *unlink, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vdev->priv_lock, flags);

	list_क्रम_each_entry_safe(unlink, पंचांगp, &vdev->unlink_tx, list) अणु
		list_move_tail(&unlink->list, &vdev->unlink_rx);
		spin_unlock_irqrestore(&vdev->priv_lock, flags);
		वापस unlink;
	पूर्ण

	spin_unlock_irqrestore(&vdev->priv_lock, flags);

	वापस शून्य;
पूर्ण

अटल पूर्णांक vhci_send_cmd_unlink(काष्ठा vhci_device *vdev)
अणु
	काष्ठा vhci_unlink *unlink = शून्य;

	काष्ठा msghdr msg;
	काष्ठा kvec iov;
	माप_प्रकार txsize;
	माप_प्रकार total_size = 0;

	जबतक ((unlink = dequeue_from_unlink_tx(vdev)) != शून्य) अणु
		पूर्णांक ret;
		काष्ठा usbip_header pdu_header;

		स_रखो(&pdu_header, 0, माप(pdu_header));
		स_रखो(&msg, 0, माप(msg));
		स_रखो(&iov, 0, माप(iov));

		usbip_dbg_vhci_tx("setup cmd unlink, %lu\n", unlink->seqnum);

		/* 1. setup usbip_header */
		pdu_header.base.command = USBIP_CMD_UNLINK;
		pdu_header.base.seqnum  = unlink->seqnum;
		pdu_header.base.devid	= vdev->devid;
		pdu_header.base.ep	= 0;
		pdu_header.u.cmd_unlink.seqnum = unlink->unlink_seqnum;

		usbip_header_correct_endian(&pdu_header, 1);

		iov.iov_base = &pdu_header;
		iov.iov_len  = माप(pdu_header);
		txsize = माप(pdu_header);

		ret = kernel_sendmsg(vdev->ud.tcp_socket, &msg, &iov, 1, txsize);
		अगर (ret != txsize) अणु
			pr_err("sendmsg failed!, ret=%d for %zd\n", ret,
			       txsize);
			usbip_event_add(&vdev->ud, VDEV_EVENT_ERROR_TCP);
			वापस -1;
		पूर्ण

		usbip_dbg_vhci_tx("send txdata\n");

		total_size += txsize;
	पूर्ण

	वापस total_size;
पूर्ण

पूर्णांक vhci_tx_loop(व्योम *data)
अणु
	काष्ठा usbip_device *ud = data;
	काष्ठा vhci_device *vdev = container_of(ud, काष्ठा vhci_device, ud);

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (vhci_send_cmd_submit(vdev) < 0)
			अवरोध;

		अगर (vhci_send_cmd_unlink(vdev) < 0)
			अवरोध;

		रुको_event_पूर्णांकerruptible(vdev->रुकोq_tx,
					 (!list_empty(&vdev->priv_tx) ||
					  !list_empty(&vdev->unlink_tx) ||
					  kthपढ़ो_should_stop()));

		usbip_dbg_vhci_tx("pending urbs ?, now wake up\n");
	पूर्ण

	वापस 0;
पूर्ण
