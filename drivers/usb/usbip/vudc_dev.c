<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Karol Kosik <karo9@पूर्णांकeria.eu>
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/file.h>
#समावेश <linux/byteorder/generic.h>

#समावेश "usbip_common.h"
#समावेश "vudc.h"

#घोषणा VIRTUAL_ENDPOINTS (1 /* ep0 */ + 15 /* in eps */ + 15 /* out eps */)

/* urb-related काष्ठाures alloc / मुक्त */


अटल व्योम मुक्त_urb(काष्ठा urb *urb)
अणु
	अगर (!urb)
		वापस;

	kमुक्त(urb->setup_packet);
	urb->setup_packet = शून्य;

	kमुक्त(urb->transfer_buffer);
	urb->transfer_buffer = शून्य;

	usb_मुक्त_urb(urb);
पूर्ण

काष्ठा urbp *alloc_urbp(व्योम)
अणु
	काष्ठा urbp *urb_p;

	urb_p = kzalloc(माप(*urb_p), GFP_KERNEL);
	अगर (!urb_p)
		वापस urb_p;

	urb_p->urb = शून्य;
	urb_p->ep = शून्य;
	INIT_LIST_HEAD(&urb_p->urb_entry);
	वापस urb_p;
पूर्ण

अटल व्योम मुक्त_urbp(काष्ठा urbp *urb_p)
अणु
	kमुक्त(urb_p);
पूर्ण

व्योम मुक्त_urbp_and_urb(काष्ठा urbp *urb_p)
अणु
	अगर (!urb_p)
		वापस;
	मुक्त_urb(urb_p->urb);
	मुक्त_urbp(urb_p);
पूर्ण


/* utilities ; almost verbatim from dummy_hcd.c */

/* called with spinlock held */
अटल व्योम nuke(काष्ठा vudc *udc, काष्ठा vep *ep)
अणु
	काष्ठा vrequest	*req;

	जबतक (!list_empty(&ep->req_queue)) अणु
		req = list_first_entry(&ep->req_queue, काष्ठा vrequest,
				       req_entry);
		list_del_init(&req->req_entry);
		req->req.status = -ESHUTDOWN;

		spin_unlock(&udc->lock);
		usb_gadget_giveback_request(&ep->ep, &req->req);
		spin_lock(&udc->lock);
	पूर्ण
पूर्ण

/* caller must hold lock */
अटल व्योम stop_activity(काष्ठा vudc *udc)
अणु
	पूर्णांक i;
	काष्ठा urbp *urb_p, *पंचांगp;

	udc->address = 0;

	क्रम (i = 0; i < VIRTUAL_ENDPOINTS; i++)
		nuke(udc, &udc->ep[i]);

	list_क्रम_each_entry_safe(urb_p, पंचांगp, &udc->urb_queue, urb_entry) अणु
		list_del(&urb_p->urb_entry);
		मुक्त_urbp_and_urb(urb_p);
	पूर्ण
पूर्ण

काष्ठा vep *vudc_find_endpoपूर्णांक(काष्ठा vudc *udc, u8 address)
अणु
	पूर्णांक i;

	अगर ((address & ~USB_सूची_IN) == 0)
		वापस &udc->ep[0];

	क्रम (i = 1; i < VIRTUAL_ENDPOINTS; i++) अणु
		काष्ठा vep *ep = &udc->ep[i];

		अगर (!ep->desc)
			जारी;
		अगर (ep->desc->bEndpoपूर्णांकAddress == address)
			वापस ep;
	पूर्ण
	वापस शून्य;
पूर्ण

/* gadget ops */

अटल पूर्णांक vgadget_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा बारpec64 now;
	काष्ठा vudc *udc = usb_gadget_to_vudc(_gadget);

	kसमय_get_ts64(&now);
	वापस ((now.tv_sec - udc->start_समय.tv_sec) * 1000 +
		(now.tv_nsec - udc->start_समय.tv_nsec) / NSEC_PER_MSEC)
			& 0x7FF;
पूर्ण

अटल पूर्णांक vgadget_set_selfघातered(काष्ठा usb_gadget *_gadget, पूर्णांक value)
अणु
	काष्ठा vudc *udc = usb_gadget_to_vudc(_gadget);

	अगर (value)
		udc->devstatus |= (1 << USB_DEVICE_SELF_POWERED);
	अन्यथा
		udc->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);
	वापस 0;
पूर्ण

अटल पूर्णांक vgadget_pullup(काष्ठा usb_gadget *_gadget, पूर्णांक value)
अणु
	काष्ठा vudc *udc = usb_gadget_to_vudc(_gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;


	spin_lock_irqsave(&udc->lock, flags);
	value = !!value;
	अगर (value == udc->pullup)
		जाओ unlock;

	udc->pullup = value;
	अगर (value) अणु
		udc->gadget.speed = min_t(u8, USB_SPEED_HIGH,
					   udc->driver->max_speed);
		udc->ep[0].ep.maxpacket = 64;
		/*
		 * This is the first place where we can ask our
		 * gadget driver क्रम descriptors.
		 */
		ret = get_gadget_descs(udc);
		अगर (ret) अणु
			dev_err(&udc->gadget.dev, "Unable go get desc: %d", ret);
			जाओ unlock;
		पूर्ण

		spin_unlock_irqrestore(&udc->lock, flags);
		usbip_start_eh(&udc->ud);
	पूर्ण अन्यथा अणु
		/* Invalidate descriptors */
		udc->desc_cached = 0;

		spin_unlock_irqrestore(&udc->lock, flags);
		usbip_event_add(&udc->ud, VUDC_EVENT_REMOVED);
		usbip_stop_eh(&udc->ud); /* Wait क्रम eh completion */
	पूर्ण

	वापस 0;

unlock:
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक vgadget_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा vudc *udc = usb_gadget_to_vudc(g);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	udc->driver = driver;
	udc->pullup = udc->connected = udc->desc_cached = 0;
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक vgadget_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा vudc *udc = usb_gadget_to_vudc(g);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	udc->driver = शून्य;
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops vgadget_ops = अणु
	.get_frame	= vgadget_get_frame,
	.set_selfघातered = vgadget_set_selfघातered,
	.pullup		= vgadget_pullup,
	.udc_start	= vgadget_udc_start,
	.udc_stop	= vgadget_udc_stop,
पूर्ण;


/* endpoपूर्णांक ops */

अटल पूर्णांक vep_enable(काष्ठा usb_ep *_ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा vep	*ep;
	काष्ठा vudc	*udc;
	अचिन्हित पूर्णांक	maxp;
	अचिन्हित दीर्घ	flags;

	ep = to_vep(_ep);
	udc = ep_to_vudc(ep);

	अगर (!_ep || !desc || ep->desc || _ep->caps.type_control
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		वापस -EINVAL;

	अगर (!udc->driver)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&udc->lock, flags);

	maxp = usb_endpoपूर्णांक_maxp(desc);
	_ep->maxpacket = maxp;
	ep->desc = desc;
	ep->type = usb_endpoपूर्णांक_type(desc);
	ep->halted = ep->wedged = 0;

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक vep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा vep *ep;
	काष्ठा vudc *udc;
	अचिन्हित दीर्घ flags;

	ep = to_vep(_ep);
	udc = ep_to_vudc(ep);
	अगर (!_ep || !ep->desc || _ep->caps.type_control)
		वापस -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);
	ep->desc = शून्य;
	nuke(udc, ep);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा usb_request *vep_alloc_request(काष्ठा usb_ep *_ep,
		gfp_t mem_flags)
अणु
	काष्ठा vrequest *req;

	अगर (!_ep)
		वापस शून्य;

	req = kzalloc(माप(*req), mem_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->req_entry);

	वापस &req->req;
पूर्ण

अटल व्योम vep_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा vrequest *req;

	/* ep is always valid here - see usb_ep_मुक्त_request() */
	अगर (!_req)
		वापस;

	req = to_vrequest(_req);
	kमुक्त(req);
पूर्ण

अटल पूर्णांक vep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
		gfp_t mem_flags)
अणु
	काष्ठा vep *ep;
	काष्ठा vrequest *req;
	काष्ठा vudc *udc;
	अचिन्हित दीर्घ flags;

	अगर (!_ep || !_req)
		वापस -EINVAL;

	ep = to_vep(_ep);
	req = to_vrequest(_req);
	udc = ep_to_vudc(ep);

	spin_lock_irqsave(&udc->lock, flags);
	_req->actual = 0;
	_req->status = -EINPROGRESS;

	list_add_tail(&req->req_entry, &ep->req_queue);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक vep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा vep *ep;
	काष्ठा vrequest *req;
	काष्ठा vudc *udc;
	काष्ठा vrequest *lst;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	अगर (!_ep || !_req)
		वापस ret;

	ep = to_vep(_ep);
	req = to_vrequest(_req);
	udc = req->udc;

	अगर (!udc->driver)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&udc->lock, flags);
	list_क्रम_each_entry(lst, &ep->req_queue, req_entry) अणु
		अगर (&lst->req == _req) अणु
			list_del_init(&lst->req_entry);
			_req->status = -ECONNRESET;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (ret == 0)
		usb_gadget_giveback_request(_ep, _req);

	वापस ret;
पूर्ण

अटल पूर्णांक
vep_set_halt_and_wedge(काष्ठा usb_ep *_ep, पूर्णांक value, पूर्णांक wedged)
अणु
	काष्ठा vep *ep;
	काष्ठा vudc *udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	ep = to_vep(_ep);
	अगर (!_ep)
		वापस -EINVAL;

	udc = ep_to_vudc(ep);
	अगर (!udc->driver)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&udc->lock, flags);
	अगर (!value)
		ep->halted = ep->wedged = 0;
	अन्यथा अगर (ep->desc && (ep->desc->bEndpoपूर्णांकAddress & USB_सूची_IN) &&
			!list_empty(&ep->req_queue))
		ret = -EAGAIN;
	अन्यथा अणु
		ep->halted = 1;
		अगर (wedged)
			ep->wedged = 1;
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक
vep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	वापस vep_set_halt_and_wedge(_ep, value, 0);
पूर्ण

अटल पूर्णांक vep_set_wedge(काष्ठा usb_ep *_ep)
अणु
	वापस vep_set_halt_and_wedge(_ep, 1, 1);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops vep_ops = अणु
	.enable		= vep_enable,
	.disable	= vep_disable,

	.alloc_request	= vep_alloc_request,
	.मुक्त_request	= vep_मुक्त_request,

	.queue		= vep_queue,
	.dequeue	= vep_dequeue,

	.set_halt	= vep_set_halt,
	.set_wedge	= vep_set_wedge,
पूर्ण;


/* shutकरोwn / reset / error handlers */

अटल व्योम vudc_shutकरोwn(काष्ठा usbip_device *ud)
अणु
	काष्ठा vudc *udc = container_of(ud, काष्ठा vudc, ud);
	पूर्णांक call_disconnect = 0;
	अचिन्हित दीर्घ flags;

	dev_dbg(&udc->pdev->dev, "device shutdown");
	अगर (ud->tcp_socket)
		kernel_sock_shutकरोwn(ud->tcp_socket, SHUT_RDWR);

	अगर (ud->tcp_rx) अणु
		kthपढ़ो_stop_put(ud->tcp_rx);
		ud->tcp_rx = शून्य;
	पूर्ण
	अगर (ud->tcp_tx) अणु
		kthपढ़ो_stop_put(ud->tcp_tx);
		ud->tcp_tx = शून्य;
	पूर्ण

	अगर (ud->tcp_socket) अणु
		sockfd_put(ud->tcp_socket);
		ud->tcp_socket = शून्य;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);
	stop_activity(udc);
	अगर (udc->connected && udc->driver->disconnect)
		call_disconnect = 1;
	udc->connected = 0;
	spin_unlock_irqrestore(&udc->lock, flags);
	अगर (call_disconnect)
		udc->driver->disconnect(&udc->gadget);
पूर्ण

अटल व्योम vudc_device_reset(काष्ठा usbip_device *ud)
अणु
	काष्ठा vudc *udc = container_of(ud, काष्ठा vudc, ud);
	अचिन्हित दीर्घ flags;

	dev_dbg(&udc->pdev->dev, "device reset");
	spin_lock_irqsave(&udc->lock, flags);
	stop_activity(udc);
	spin_unlock_irqrestore(&udc->lock, flags);
	अगर (udc->driver)
		usb_gadget_udc_reset(&udc->gadget, udc->driver);
	spin_lock_irqsave(&ud->lock, flags);
	ud->status = SDEV_ST_AVAILABLE;
	spin_unlock_irqrestore(&ud->lock, flags);
पूर्ण

अटल व्योम vudc_device_unusable(काष्ठा usbip_device *ud)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ud->lock, flags);
	ud->status = SDEV_ST_ERROR;
	spin_unlock_irqrestore(&ud->lock, flags);
पूर्ण

/* device setup / cleanup */

काष्ठा vudc_device *alloc_vudc_device(पूर्णांक devid)
अणु
	काष्ठा vudc_device *udc_dev = शून्य;

	udc_dev = kzalloc(माप(*udc_dev), GFP_KERNEL);
	अगर (!udc_dev)
		जाओ out;

	INIT_LIST_HEAD(&udc_dev->dev_entry);

	udc_dev->pdev = platक्रमm_device_alloc(GADGET_NAME, devid);
	अगर (!udc_dev->pdev) अणु
		kमुक्त(udc_dev);
		udc_dev = शून्य;
	पूर्ण

out:
	वापस udc_dev;
पूर्ण

व्योम put_vudc_device(काष्ठा vudc_device *udc_dev)
अणु
	platक्रमm_device_put(udc_dev->pdev);
	kमुक्त(udc_dev);
पूर्ण

अटल पूर्णांक init_vudc_hw(काष्ठा vudc *udc)
अणु
	पूर्णांक i;
	काष्ठा usbip_device *ud = &udc->ud;
	काष्ठा vep *ep;

	udc->ep = kसुस्मृति(VIRTUAL_ENDPOINTS, माप(*udc->ep), GFP_KERNEL);
	अगर (!udc->ep)
		जाओ nomem_ep;

	INIT_LIST_HEAD(&udc->gadget.ep_list);

	/* create ep0 and 15 in, 15 out general purpose eps */
	क्रम (i = 0; i < VIRTUAL_ENDPOINTS; ++i) अणु
		पूर्णांक is_out = i % 2;
		पूर्णांक num = (i + 1) / 2;

		ep = &udc->ep[i];

		प्र_लिखो(ep->name, "ep%d%s", num,
			i ? (is_out ? "out" : "in") : "");
		ep->ep.name = ep->name;

		ep->ep.ops = &vep_ops;

		usb_ep_set_maxpacket_limit(&ep->ep, ~0);
		ep->ep.max_streams = 16;
		ep->gadget = &udc->gadget;
		INIT_LIST_HEAD(&ep->req_queue);

		अगर (i == 0) अणु
			/* ep0 */
			ep->ep.caps.type_control = true;
			ep->ep.caps.dir_out = true;
			ep->ep.caps.dir_in = true;

			udc->gadget.ep0 = &ep->ep;
		पूर्ण अन्यथा अणु
			/* All other eps */
			ep->ep.caps.type_iso = true;
			ep->ep.caps.type_पूर्णांक = true;
			ep->ep.caps.type_bulk = true;

			अगर (is_out)
				ep->ep.caps.dir_out = true;
			अन्यथा
				ep->ep.caps.dir_in = true;

			list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);
		पूर्ण
	पूर्ण

	spin_lock_init(&udc->lock);
	spin_lock_init(&udc->lock_tx);
	INIT_LIST_HEAD(&udc->urb_queue);
	INIT_LIST_HEAD(&udc->tx_queue);
	init_रुकोqueue_head(&udc->tx_रुकोq);

	spin_lock_init(&ud->lock);
	mutex_init(&ud->sysfs_lock);
	ud->status = SDEV_ST_AVAILABLE;
	ud->side = USBIP_VUDC;

	ud->eh_ops.shutकरोwn = vudc_shutकरोwn;
	ud->eh_ops.reset    = vudc_device_reset;
	ud->eh_ops.unusable = vudc_device_unusable;

	v_init_समयr(udc);
	वापस 0;

nomem_ep:
		वापस -ENOMEM;
पूर्ण

अटल व्योम cleanup_vudc_hw(काष्ठा vudc *udc)
अणु
	kमुक्त(udc->ep);
पूर्ण

/* platक्रमm driver ops */

पूर्णांक vudc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vudc *udc;
	पूर्णांक ret = -ENOMEM;

	udc = kzalloc(माप(*udc), GFP_KERNEL);
	अगर (!udc)
		जाओ out;

	udc->gadget.name = GADGET_NAME;
	udc->gadget.ops = &vgadget_ops;
	udc->gadget.max_speed = USB_SPEED_HIGH;
	udc->gadget.dev.parent = &pdev->dev;
	udc->pdev = pdev;

	ret = init_vudc_hw(udc);
	अगर (ret)
		जाओ err_init_vudc_hw;

	ret = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	अगर (ret < 0)
		जाओ err_add_udc;

	platक्रमm_set_drvdata(pdev, udc);

	वापस ret;

err_add_udc:
	cleanup_vudc_hw(udc);
err_init_vudc_hw:
	kमुक्त(udc);
out:
	वापस ret;
पूर्ण

पूर्णांक vudc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vudc *udc = platक्रमm_get_drvdata(pdev);

	usb_del_gadget_udc(&udc->gadget);
	cleanup_vudc_hw(udc);
	kमुक्त(udc);
	वापस 0;
पूर्ण
