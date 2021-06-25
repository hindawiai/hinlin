<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>

#समावेश "usbip_common.h"
#समावेश "vhci.h"

/* get URB from transmitted urb queue. caller must hold vdev->priv_lock */
काष्ठा urb *pickup_urb_and_मुक्त_priv(काष्ठा vhci_device *vdev, __u32 seqnum)
अणु
	काष्ठा vhci_priv *priv, *पंचांगp;
	काष्ठा urb *urb = शून्य;
	पूर्णांक status;

	list_क्रम_each_entry_safe(priv, पंचांगp, &vdev->priv_rx, list) अणु
		अगर (priv->seqnum != seqnum)
			जारी;

		urb = priv->urb;
		status = urb->status;

		usbip_dbg_vhci_rx("find urb seqnum %u\n", seqnum);

		चयन (status) अणु
		हाल -ENOENT:
			fallthrough;
		हाल -ECONNRESET:
			dev_dbg(&urb->dev->dev,
				 "urb seq# %u was unlinked %ssynchronously\n",
				 seqnum, status == -ENOENT ? "" : "a");
			अवरोध;
		हाल -EINPROGRESS:
			/* no info output */
			अवरोध;
		शेष:
			dev_dbg(&urb->dev->dev,
				 "urb seq# %u may be in a error, status %d\n",
				 seqnum, status);
		पूर्ण

		list_del(&priv->list);
		kमुक्त(priv);
		urb->hcpriv = शून्य;

		अवरोध;
	पूर्ण

	वापस urb;
पूर्ण

अटल व्योम vhci_recv_ret_submit(काष्ठा vhci_device *vdev,
				 काष्ठा usbip_header *pdu)
अणु
	काष्ठा vhci_hcd *vhci_hcd = vdev_to_vhci_hcd(vdev);
	काष्ठा vhci *vhci = vhci_hcd->vhci;
	काष्ठा usbip_device *ud = &vdev->ud;
	काष्ठा urb *urb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vdev->priv_lock, flags);
	urb = pickup_urb_and_मुक्त_priv(vdev, pdu->base.seqnum);
	spin_unlock_irqrestore(&vdev->priv_lock, flags);

	अगर (!urb) अणु
		pr_err("cannot find a urb of seqnum %u max seqnum %d\n",
			pdu->base.seqnum,
			atomic_पढ़ो(&vhci_hcd->seqnum));
		usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);
		वापस;
	पूर्ण

	/* unpack the pdu to a urb */
	usbip_pack_pdu(pdu, urb, USBIP_RET_SUBMIT, 0);

	/* recv transfer buffer */
	अगर (usbip_recv_xbuff(ud, urb) < 0) अणु
		urb->status = -EPROTO;
		जाओ error;
	पूर्ण

	/* recv iso_packet_descriptor */
	अगर (usbip_recv_iso(ud, urb) < 0) अणु
		urb->status = -EPROTO;
		जाओ error;
	पूर्ण

	/* restore the padding in iso packets */
	usbip_pad_iso(ud, urb);

error:
	अगर (usbip_dbg_flag_vhci_rx)
		usbip_dump_urb(urb);

	अगर (urb->num_sgs)
		urb->transfer_flags &= ~URB_DMA_MAP_SG;

	usbip_dbg_vhci_rx("now giveback urb %u\n", pdu->base.seqnum);

	spin_lock_irqsave(&vhci->lock, flags);
	usb_hcd_unlink_urb_from_ep(vhci_hcd_to_hcd(vhci_hcd), urb);
	spin_unlock_irqrestore(&vhci->lock, flags);

	usb_hcd_giveback_urb(vhci_hcd_to_hcd(vhci_hcd), urb, urb->status);

	usbip_dbg_vhci_rx("Leave\n");
पूर्ण

अटल काष्ठा vhci_unlink *dequeue_pending_unlink(काष्ठा vhci_device *vdev,
						  काष्ठा usbip_header *pdu)
अणु
	काष्ठा vhci_unlink *unlink, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vdev->priv_lock, flags);

	list_क्रम_each_entry_safe(unlink, पंचांगp, &vdev->unlink_rx, list) अणु
		pr_info("unlink->seqnum %lu\n", unlink->seqnum);
		अगर (unlink->seqnum == pdu->base.seqnum) अणु
			usbip_dbg_vhci_rx("found pending unlink, %lu\n",
					  unlink->seqnum);
			list_del(&unlink->list);

			spin_unlock_irqrestore(&vdev->priv_lock, flags);
			वापस unlink;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&vdev->priv_lock, flags);

	वापस शून्य;
पूर्ण

अटल व्योम vhci_recv_ret_unlink(काष्ठा vhci_device *vdev,
				 काष्ठा usbip_header *pdu)
अणु
	काष्ठा vhci_hcd *vhci_hcd = vdev_to_vhci_hcd(vdev);
	काष्ठा vhci *vhci = vhci_hcd->vhci;
	काष्ठा vhci_unlink *unlink;
	काष्ठा urb *urb;
	अचिन्हित दीर्घ flags;

	usbip_dump_header(pdu);

	unlink = dequeue_pending_unlink(vdev, pdu);
	अगर (!unlink) अणु
		pr_info("cannot find the pending unlink %u\n",
			pdu->base.seqnum);
		वापस;
	पूर्ण

	spin_lock_irqsave(&vdev->priv_lock, flags);
	urb = pickup_urb_and_मुक्त_priv(vdev, unlink->unlink_seqnum);
	spin_unlock_irqrestore(&vdev->priv_lock, flags);

	अगर (!urb) अणु
		/*
		 * I get the result of a unlink request. But, it seems that I
		 * alपढ़ोy received the result of its submit result and gave
		 * back the URB.
		 */
		pr_info("the urb (seqnum %d) was already given back\n",
			pdu->base.seqnum);
	पूर्ण अन्यथा अणु
		usbip_dbg_vhci_rx("now giveback urb %d\n", pdu->base.seqnum);

		/* If unlink is successful, status is -ECONNRESET */
		urb->status = pdu->u.ret_unlink.status;
		pr_info("urb->status %d\n", urb->status);

		spin_lock_irqsave(&vhci->lock, flags);
		usb_hcd_unlink_urb_from_ep(vhci_hcd_to_hcd(vhci_hcd), urb);
		spin_unlock_irqrestore(&vhci->lock, flags);

		usb_hcd_giveback_urb(vhci_hcd_to_hcd(vhci_hcd), urb, urb->status);
	पूर्ण

	kमुक्त(unlink);
पूर्ण

अटल पूर्णांक vhci_priv_tx_empty(काष्ठा vhci_device *vdev)
अणु
	पूर्णांक empty = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vdev->priv_lock, flags);
	empty = list_empty(&vdev->priv_rx);
	spin_unlock_irqrestore(&vdev->priv_lock, flags);

	वापस empty;
पूर्ण

/* recv a pdu */
अटल व्योम vhci_rx_pdu(काष्ठा usbip_device *ud)
अणु
	पूर्णांक ret;
	काष्ठा usbip_header pdu;
	काष्ठा vhci_device *vdev = container_of(ud, काष्ठा vhci_device, ud);

	usbip_dbg_vhci_rx("Enter\n");

	स_रखो(&pdu, 0, माप(pdu));

	/* receive a pdu header */
	ret = usbip_recv(ud->tcp_socket, &pdu, माप(pdu));
	अगर (ret < 0) अणु
		अगर (ret == -ECONNRESET)
			pr_info("connection reset by peer\n");
		अन्यथा अगर (ret == -EAGAIN) अणु
			/* ignore अगर connection was idle */
			अगर (vhci_priv_tx_empty(vdev))
				वापस;
			pr_info("connection timed out with pending urbs\n");
		पूर्ण अन्यथा अगर (ret != -ERESTARTSYS)
			pr_info("xmit failed %d\n", ret);

		usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);
		वापस;
	पूर्ण
	अगर (ret == 0) अणु
		pr_info("connection closed");
		usbip_event_add(ud, VDEV_EVENT_DOWN);
		वापस;
	पूर्ण
	अगर (ret != माप(pdu)) अणु
		pr_err("received pdu size is %d, should be %d\n", ret,
		       (अचिन्हित पूर्णांक)माप(pdu));
		usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);
		वापस;
	पूर्ण

	usbip_header_correct_endian(&pdu, 0);

	अगर (usbip_dbg_flag_vhci_rx)
		usbip_dump_header(&pdu);

	चयन (pdu.base.command) अणु
	हाल USBIP_RET_SUBMIT:
		vhci_recv_ret_submit(vdev, &pdu);
		अवरोध;
	हाल USBIP_RET_UNLINK:
		vhci_recv_ret_unlink(vdev, &pdu);
		अवरोध;
	शेष:
		/* NOT REACHED */
		pr_err("unknown pdu %u\n", pdu.base.command);
		usbip_dump_header(&pdu);
		usbip_event_add(ud, VDEV_EVENT_ERROR_TCP);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक vhci_rx_loop(व्योम *data)
अणु
	काष्ठा usbip_device *ud = data;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (usbip_event_happened(ud))
			अवरोध;

		usbip_kcov_remote_start(ud);
		vhci_rx_pdu(ud);
		usbip_kcov_remote_stop();
	पूर्ण

	वापस 0;
पूर्ण
