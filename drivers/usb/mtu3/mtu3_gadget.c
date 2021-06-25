<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtu3_gadget.c - MediaTek usb3 DRD peripheral support
 *
 * Copyright (C) 2016 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#समावेश "mtu3.h"
#समावेश "mtu3_trace.h"

व्योम mtu3_req_complete(काष्ठा mtu3_ep *mep,
		     काष्ठा usb_request *req, पूर्णांक status)
__releases(mep->mtu->lock)
__acquires(mep->mtu->lock)
अणु
	काष्ठा mtu3_request *mreq = to_mtu3_request(req);
	काष्ठा mtu3 *mtu = mreq->mtu;

	list_del(&mreq->list);
	अगर (req->status == -EINPROGRESS)
		req->status = status;

	trace_mtu3_req_complete(mreq);
	spin_unlock(&mtu->lock);

	/* ep0 makes use of PIO, needn't unmap it */
	अगर (mep->epnum)
		usb_gadget_unmap_request(&mtu->g, req, mep->is_in);

	dev_dbg(mtu->dev, "%s complete req: %p, sts %d, %d/%d\n",
		mep->name, req, req->status, req->actual, req->length);

	usb_gadget_giveback_request(&mep->ep, req);
	spin_lock(&mtu->lock);
पूर्ण

अटल व्योम nuke(काष्ठा mtu3_ep *mep, स्थिर पूर्णांक status)
अणु
	काष्ठा mtu3_request *mreq = शून्य;

	अगर (list_empty(&mep->req_list))
		वापस;

	dev_dbg(mep->mtu->dev, "abort %s's req: sts %d\n", mep->name, status);

	/* exclude EP0 */
	अगर (mep->epnum)
		mtu3_qmu_flush(mep);

	जबतक (!list_empty(&mep->req_list)) अणु
		mreq = list_first_entry(&mep->req_list,
					काष्ठा mtu3_request, list);
		mtu3_req_complete(mep, &mreq->request, status);
	पूर्ण
पूर्ण

अटल पूर्णांक mtu3_ep_enable(काष्ठा mtu3_ep *mep)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	स्थिर काष्ठा usb_ss_ep_comp_descriptor *comp_desc;
	काष्ठा mtu3 *mtu = mep->mtu;
	u32 पूर्णांकerval = 0;
	u32 mult = 0;
	u32 burst = 0;
	पूर्णांक max_packet;
	पूर्णांक ret;

	desc = mep->desc;
	comp_desc = mep->comp_desc;
	mep->type = usb_endpoपूर्णांक_type(desc);
	max_packet = usb_endpoपूर्णांक_maxp(desc);
	mep->maxp = max_packet & GENMASK(10, 0);

	चयन (mtu->g.speed) अणु
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(desc) ||
				usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
			पूर्णांकerval = desc->bInterval;
			पूर्णांकerval = clamp_val(पूर्णांकerval, 1, 16) - 1;
			अगर (usb_endpoपूर्णांक_xfer_isoc(desc) && comp_desc)
				mult = comp_desc->bmAttributes;
		पूर्ण
		अगर (comp_desc)
			burst = comp_desc->bMaxBurst;

		अवरोध;
	हाल USB_SPEED_HIGH:
		अगर (usb_endpoपूर्णांक_xfer_isoc(desc) ||
				usb_endpoपूर्णांक_xfer_पूर्णांक(desc)) अणु
			पूर्णांकerval = desc->bInterval;
			पूर्णांकerval = clamp_val(पूर्णांकerval, 1, 16) - 1;
			burst = (max_packet & GENMASK(12, 11)) >> 11;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध; /*others are ignored */
	पूर्ण

	dev_dbg(mtu->dev, "%s maxp:%d, interval:%d, burst:%d, mult:%d\n",
		__func__, mep->maxp, पूर्णांकerval, burst, mult);

	mep->ep.maxpacket = mep->maxp;
	mep->ep.desc = desc;
	mep->ep.comp_desc = comp_desc;

	/* slot मुख्यly affects bulk/isoc transfer, so ignore पूर्णांक */
	mep->slot = usb_endpoपूर्णांक_xfer_पूर्णांक(desc) ? 0 : mtu->slot;

	ret = mtu3_config_ep(mtu, mep, पूर्णांकerval, burst, mult);
	अगर (ret < 0)
		वापस ret;

	ret = mtu3_gpd_ring_alloc(mep);
	अगर (ret < 0) अणु
		mtu3_deconfig_ep(mtu, mep);
		वापस ret;
	पूर्ण

	mtu3_qmu_start(mep);

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_ep_disable(काष्ठा mtu3_ep *mep)
अणु
	काष्ठा mtu3 *mtu = mep->mtu;

	mtu3_qmu_stop(mep);

	/* पात all pending requests */
	nuke(mep, -ESHUTDOWN);
	mtu3_deconfig_ep(mtu, mep);
	mtu3_gpd_ring_मुक्त(mep);

	mep->desc = शून्य;
	mep->ep.desc = शून्य;
	mep->comp_desc = शून्य;
	mep->type = 0;
	mep->flags = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_gadget_ep_enable(काष्ठा usb_ep *ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा mtu3_ep *mep;
	काष्ठा mtu3 *mtu;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	अगर (!ep || !desc || desc->bDescriptorType != USB_DT_ENDPOINT) अणु
		pr_debug("%s invalid parameters\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!desc->wMaxPacketSize) अणु
		pr_debug("%s missing wMaxPacketSize\n", __func__);
		वापस -EINVAL;
	पूर्ण
	mep = to_mtu3_ep(ep);
	mtu = mep->mtu;

	/* check ep number and direction against endpoपूर्णांक */
	अगर (usb_endpoपूर्णांक_num(desc) != mep->epnum)
		वापस -EINVAL;

	अगर (!!usb_endpoपूर्णांक_dir_in(desc) ^ !!mep->is_in)
		वापस -EINVAL;

	dev_dbg(mtu->dev, "%s %s\n", __func__, ep->name);

	अगर (mep->flags & MTU3_EP_ENABLED) अणु
		dev_WARN_ONCE(mtu->dev, true, "%s is already enabled\n",
				mep->name);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&mtu->lock, flags);
	mep->desc = desc;
	mep->comp_desc = ep->comp_desc;

	ret = mtu3_ep_enable(mep);
	अगर (ret)
		जाओ error;

	mep->flags = MTU3_EP_ENABLED;
	mtu->active_ep++;

error:
	spin_unlock_irqrestore(&mtu->lock, flags);

	dev_dbg(mtu->dev, "%s active_ep=%d\n", __func__, mtu->active_ep);
	trace_mtu3_gadget_ep_enable(mep);

	वापस ret;
पूर्ण

अटल पूर्णांक mtu3_gadget_ep_disable(काष्ठा usb_ep *ep)
अणु
	काष्ठा mtu3_ep *mep = to_mtu3_ep(ep);
	काष्ठा mtu3 *mtu = mep->mtu;
	अचिन्हित दीर्घ flags;

	dev_dbg(mtu->dev, "%s %s\n", __func__, mep->name);
	trace_mtu3_gadget_ep_disable(mep);

	अगर (!(mep->flags & MTU3_EP_ENABLED)) अणु
		dev_warn(mtu->dev, "%s is already disabled\n", mep->name);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&mtu->lock, flags);
	mtu3_ep_disable(mep);
	mep->flags = 0;
	mtu->active_ep--;
	spin_unlock_irqrestore(&(mtu->lock), flags);

	dev_dbg(mtu->dev, "%s active_ep=%d, mtu3 is_active=%d\n",
		__func__, mtu->active_ep, mtu->is_active);

	वापस 0;
पूर्ण

काष्ठा usb_request *mtu3_alloc_request(काष्ठा usb_ep *ep, gfp_t gfp_flags)
अणु
	काष्ठा mtu3_ep *mep = to_mtu3_ep(ep);
	काष्ठा mtu3_request *mreq;

	mreq = kzalloc(माप(*mreq), gfp_flags);
	अगर (!mreq)
		वापस शून्य;

	mreq->request.dma = DMA_ADDR_INVALID;
	mreq->epnum = mep->epnum;
	mreq->mep = mep;
	trace_mtu3_alloc_request(mreq);

	वापस &mreq->request;
पूर्ण

व्योम mtu3_मुक्त_request(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा mtu3_request *mreq = to_mtu3_request(req);

	trace_mtu3_मुक्त_request(mreq);
	kमुक्त(mreq);
पूर्ण

अटल पूर्णांक mtu3_gadget_queue(काष्ठा usb_ep *ep,
		काष्ठा usb_request *req, gfp_t gfp_flags)
अणु
	काष्ठा mtu3_ep *mep = to_mtu3_ep(ep);
	काष्ठा mtu3_request *mreq = to_mtu3_request(req);
	काष्ठा mtu3 *mtu = mep->mtu;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!req->buf)
		वापस -ENODATA;

	अगर (mreq->mep != mep)
		वापस -EINVAL;

	dev_dbg(mtu->dev, "%s %s EP%d(%s), req=%p, maxp=%d, len#%d\n",
		__func__, mep->is_in ? "TX" : "RX", mreq->epnum, ep->name,
		mreq, ep->maxpacket, mreq->request.length);

	अगर (req->length > GPD_BUF_SIZE ||
	    (mtu->gen2cp && req->length > GPD_BUF_SIZE_EL)) अणु
		dev_warn(mtu->dev,
			"req length > supported MAX:%d requested:%d\n",
			mtu->gen2cp ? GPD_BUF_SIZE_EL : GPD_BUF_SIZE,
			req->length);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* करोn't queue अगर the ep is करोwn */
	अगर (!mep->desc) अणु
		dev_dbg(mtu->dev, "req=%p queued to %s while it's disabled\n",
			req, ep->name);
		वापस -ESHUTDOWN;
	पूर्ण

	mreq->mtu = mtu;
	mreq->request.actual = 0;
	mreq->request.status = -EINPROGRESS;

	ret = usb_gadget_map_request(&mtu->g, req, mep->is_in);
	अगर (ret) अणु
		dev_err(mtu->dev, "dma mapping failed\n");
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&mtu->lock, flags);

	अगर (mtu3_prepare_transfer(mep)) अणु
		ret = -EAGAIN;
		जाओ error;
	पूर्ण

	list_add_tail(&mreq->list, &mep->req_list);
	mtu3_insert_gpd(mep, mreq);
	mtu3_qmu_resume(mep);

error:
	spin_unlock_irqrestore(&mtu->lock, flags);
	trace_mtu3_gadget_queue(mreq);

	वापस ret;
पूर्ण

अटल पूर्णांक mtu3_gadget_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा mtu3_ep *mep = to_mtu3_ep(ep);
	काष्ठा mtu3_request *mreq = to_mtu3_request(req);
	काष्ठा mtu3_request *r;
	काष्ठा mtu3 *mtu = mep->mtu;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (mreq->mep != mep)
		वापस -EINVAL;

	dev_dbg(mtu->dev, "%s : req=%p\n", __func__, req);
	trace_mtu3_gadget_dequeue(mreq);

	spin_lock_irqsave(&mtu->lock, flags);

	list_क्रम_each_entry(r, &mep->req_list, list) अणु
		अगर (r == mreq)
			अवरोध;
	पूर्ण
	अगर (r != mreq) अणु
		dev_dbg(mtu->dev, "req=%p not queued to %s\n", req, ep->name);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	mtu3_qmu_flush(mep);  /* REVISIT: set BPS ?? */
	mtu3_req_complete(mep, req, -ECONNRESET);
	mtu3_qmu_start(mep);

करोne:
	spin_unlock_irqrestore(&mtu->lock, flags);

	वापस ret;
पूर्ण

/*
 * Set or clear the halt bit of an EP.
 * A halted EP won't TX/RX any data but will queue requests.
 */
अटल पूर्णांक mtu3_gadget_ep_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा mtu3_ep *mep = to_mtu3_ep(ep);
	काष्ठा mtu3 *mtu = mep->mtu;
	काष्ठा mtu3_request *mreq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	dev_dbg(mtu->dev, "%s : %s...", __func__, ep->name);

	spin_lock_irqsave(&mtu->lock, flags);

	अगर (mep->type == USB_ENDPOINT_XFER_ISOC) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	mreq = next_request(mep);
	अगर (value) अणु
		/*
		 * If there is not request क्रम TX-EP, QMU will not transfer
		 * data to TX-FIFO, so no need check whether TX-FIFO
		 * holds bytes or not here
		 */
		अगर (mreq) अणु
			dev_dbg(mtu->dev, "req in progress, cannot halt %s\n",
				ep->name);
			ret = -EAGAIN;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		mep->flags &= ~MTU3_EP_WEDGE;
	पूर्ण

	dev_dbg(mtu->dev, "%s %s stall\n", ep->name, value ? "set" : "clear");

	mtu3_ep_stall_set(mep, value);

करोne:
	spin_unlock_irqrestore(&mtu->lock, flags);
	trace_mtu3_gadget_ep_set_halt(mep);

	वापस ret;
पूर्ण

/* Sets the halt feature with the clear requests ignored */
अटल पूर्णांक mtu3_gadget_ep_set_wedge(काष्ठा usb_ep *ep)
अणु
	काष्ठा mtu3_ep *mep = to_mtu3_ep(ep);

	mep->flags |= MTU3_EP_WEDGE;

	वापस usb_ep_set_halt(ep);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops mtu3_ep_ops = अणु
	.enable = mtu3_gadget_ep_enable,
	.disable = mtu3_gadget_ep_disable,
	.alloc_request = mtu3_alloc_request,
	.मुक्त_request = mtu3_मुक्त_request,
	.queue = mtu3_gadget_queue,
	.dequeue = mtu3_gadget_dequeue,
	.set_halt = mtu3_gadget_ep_set_halt,
	.set_wedge = mtu3_gadget_ep_set_wedge,
पूर्ण;

अटल पूर्णांक mtu3_gadget_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा mtu3 *mtu = gadget_to_mtu3(gadget);

	वापस (पूर्णांक)mtu3_पढ़ोl(mtu->mac_base, U3D_USB20_FRAME_NUM);
पूर्ण

अटल पूर्णांक mtu3_gadget_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा mtu3 *mtu = gadget_to_mtu3(gadget);
	अचिन्हित दीर्घ flags;

	dev_dbg(mtu->dev, "%s\n", __func__);

	/* remote wakeup feature is not enabled by host */
	अगर (!mtu->may_wakeup)
		वापस  -EOPNOTSUPP;

	spin_lock_irqsave(&mtu->lock, flags);
	अगर (mtu->g.speed >= USB_SPEED_SUPER) अणु
		mtu3_setbits(mtu->mac_base, U3D_LINK_POWER_CONTROL, UX_EXIT);
	पूर्ण अन्यथा अणु
		mtu3_setbits(mtu->mac_base, U3D_POWER_MANAGEMENT, RESUME);
		spin_unlock_irqrestore(&mtu->lock, flags);
		usleep_range(10000, 11000);
		spin_lock_irqsave(&mtu->lock, flags);
		mtu3_clrbits(mtu->mac_base, U3D_POWER_MANAGEMENT, RESUME);
	पूर्ण
	spin_unlock_irqrestore(&mtu->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_gadget_set_self_घातered(काष्ठा usb_gadget *gadget,
		पूर्णांक is_selfघातered)
अणु
	काष्ठा mtu3 *mtu = gadget_to_mtu3(gadget);

	mtu->is_self_घातered = !!is_selfघातered;
	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_gadget_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा mtu3 *mtu = gadget_to_mtu3(gadget);
	अचिन्हित दीर्घ flags;

	dev_dbg(mtu->dev, "%s (%s) for %sactive device\n", __func__,
		is_on ? "on" : "off", mtu->is_active ? "" : "in");

	/* we'd rather not pullup unless the device is active. */
	spin_lock_irqsave(&mtu->lock, flags);

	is_on = !!is_on;
	अगर (!mtu->is_active) अणु
		/* save it क्रम mtu3_start() to process the request */
		mtu->softconnect = is_on;
	पूर्ण अन्यथा अगर (is_on != mtu->softconnect) अणु
		mtu->softconnect = is_on;
		mtu3_dev_on_off(mtu, is_on);
	पूर्ण

	spin_unlock_irqrestore(&mtu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_gadget_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा mtu3 *mtu = gadget_to_mtu3(gadget);
	अचिन्हित दीर्घ flags;

	अगर (mtu->gadget_driver) अणु
		dev_err(mtu->dev, "%s is already bound to %s\n",
			mtu->g.name, mtu->gadget_driver->driver.name);
		वापस -EBUSY;
	पूर्ण

	dev_dbg(mtu->dev, "bind driver %s\n", driver->function);

	spin_lock_irqsave(&mtu->lock, flags);

	mtu->softconnect = 0;
	mtu->gadget_driver = driver;

	अगर (mtu->ssusb->dr_mode == USB_DR_MODE_PERIPHERAL)
		mtu3_start(mtu);

	spin_unlock_irqrestore(&mtu->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम stop_activity(काष्ठा mtu3 *mtu)
अणु
	काष्ठा usb_gadget_driver *driver = mtu->gadget_driver;
	पूर्णांक i;

	/* करोn't disconnect if it's not connected */
	अगर (mtu->g.speed == USB_SPEED_UNKNOWN)
		driver = शून्य;
	अन्यथा
		mtu->g.speed = USB_SPEED_UNKNOWN;

	/* deactivate the hardware */
	अगर (mtu->softconnect) अणु
		mtu->softconnect = 0;
		mtu3_dev_on_off(mtu, 0);
	पूर्ण

	/*
	 * समाप्तing any outstanding requests will quiesce the driver;
	 * then report disconnect
	 */
	nuke(mtu->ep0, -ESHUTDOWN);
	क्रम (i = 1; i < mtu->num_eps; i++) अणु
		nuke(mtu->in_eps + i, -ESHUTDOWN);
		nuke(mtu->out_eps + i, -ESHUTDOWN);
	पूर्ण

	अगर (driver) अणु
		spin_unlock(&mtu->lock);
		driver->disconnect(&mtu->g);
		spin_lock(&mtu->lock);
	पूर्ण
पूर्ण

अटल पूर्णांक mtu3_gadget_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा mtu3 *mtu = gadget_to_mtu3(g);
	अचिन्हित दीर्घ flags;

	dev_dbg(mtu->dev, "%s\n", __func__);

	spin_lock_irqsave(&mtu->lock, flags);

	stop_activity(mtu);
	mtu->gadget_driver = शून्य;

	अगर (mtu->ssusb->dr_mode == USB_DR_MODE_PERIPHERAL)
		mtu3_stop(mtu);

	spin_unlock_irqrestore(&mtu->lock, flags);

	synchronize_irq(mtu->irq);
	वापस 0;
पूर्ण

अटल व्योम
mtu3_gadget_set_speed(काष्ठा usb_gadget *g, क्रमागत usb_device_speed speed)
अणु
	काष्ठा mtu3 *mtu = gadget_to_mtu3(g);
	अचिन्हित दीर्घ flags;

	dev_dbg(mtu->dev, "%s %s\n", __func__, usb_speed_string(speed));

	spin_lock_irqsave(&mtu->lock, flags);
	mtu3_set_speed(mtu, speed);
	spin_unlock_irqrestore(&mtu->lock, flags);
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops mtu3_gadget_ops = अणु
	.get_frame = mtu3_gadget_get_frame,
	.wakeup = mtu3_gadget_wakeup,
	.set_selfघातered = mtu3_gadget_set_self_घातered,
	.pullup = mtu3_gadget_pullup,
	.udc_start = mtu3_gadget_start,
	.udc_stop = mtu3_gadget_stop,
	.udc_set_speed = mtu3_gadget_set_speed,
पूर्ण;

अटल व्योम mtu3_state_reset(काष्ठा mtu3 *mtu)
अणु
	mtu->address = 0;
	mtu->ep0_state = MU3D_EP0_STATE_SETUP;
	mtu->may_wakeup = 0;
	mtu->u1_enable = 0;
	mtu->u2_enable = 0;
	mtu->delayed_status = false;
	mtu->test_mode = false;
पूर्ण

अटल व्योम init_hw_ep(काष्ठा mtu3 *mtu, काष्ठा mtu3_ep *mep,
		u32 epnum, u32 is_in)
अणु
	mep->epnum = epnum;
	mep->mtu = mtu;
	mep->is_in = is_in;

	INIT_LIST_HEAD(&mep->req_list);

	प्र_लिखो(mep->name, "ep%d%s", epnum,
		!epnum ? "" : (is_in ? "in" : "out"));

	mep->ep.name = mep->name;
	INIT_LIST_HEAD(&mep->ep.ep_list);

	/* initialize maxpacket as SS */
	अगर (!epnum) अणु
		usb_ep_set_maxpacket_limit(&mep->ep, 512);
		mep->ep.caps.type_control = true;
		mep->ep.ops = &mtu3_ep0_ops;
		mtu->g.ep0 = &mep->ep;
	पूर्ण अन्यथा अणु
		usb_ep_set_maxpacket_limit(&mep->ep, 1024);
		mep->ep.caps.type_iso = true;
		mep->ep.caps.type_bulk = true;
		mep->ep.caps.type_पूर्णांक = true;
		mep->ep.ops = &mtu3_ep_ops;
		list_add_tail(&mep->ep.ep_list, &mtu->g.ep_list);
	पूर्ण

	dev_dbg(mtu->dev, "%s, name=%s, maxp=%d\n", __func__, mep->ep.name,
		 mep->ep.maxpacket);

	अगर (!epnum) अणु
		mep->ep.caps.dir_in = true;
		mep->ep.caps.dir_out = true;
	पूर्ण अन्यथा अगर (is_in) अणु
		mep->ep.caps.dir_in = true;
	पूर्ण अन्यथा अणु
		mep->ep.caps.dir_out = true;
	पूर्ण
पूर्ण

अटल व्योम mtu3_gadget_init_eps(काष्ठा mtu3 *mtu)
अणु
	u8 epnum;

	/* initialize endpoपूर्णांक list just once */
	INIT_LIST_HEAD(&(mtu->g.ep_list));

	dev_dbg(mtu->dev, "%s num_eps(1 for a pair of tx&rx ep)=%d\n",
		__func__, mtu->num_eps);

	init_hw_ep(mtu, mtu->ep0, 0, 0);
	क्रम (epnum = 1; epnum < mtu->num_eps; epnum++) अणु
		init_hw_ep(mtu, mtu->in_eps + epnum, epnum, 1);
		init_hw_ep(mtu, mtu->out_eps + epnum, epnum, 0);
	पूर्ण
पूर्ण

पूर्णांक mtu3_gadget_setup(काष्ठा mtu3 *mtu)
अणु
	mtu->g.ops = &mtu3_gadget_ops;
	mtu->g.max_speed = mtu->max_speed;
	mtu->g.speed = USB_SPEED_UNKNOWN;
	mtu->g.sg_supported = 0;
	mtu->g.name = MTU3_DRIVER_NAME;
	mtu->is_active = 0;
	mtu->delayed_status = false;

	mtu3_gadget_init_eps(mtu);

	वापस usb_add_gadget_udc(mtu->dev, &mtu->g);
पूर्ण

व्योम mtu3_gadget_cleanup(काष्ठा mtu3 *mtu)
अणु
	usb_del_gadget_udc(&mtu->g);
पूर्ण

व्योम mtu3_gadget_resume(काष्ठा mtu3 *mtu)
अणु
	dev_dbg(mtu->dev, "gadget RESUME\n");
	अगर (mtu->gadget_driver && mtu->gadget_driver->resume) अणु
		spin_unlock(&mtu->lock);
		mtu->gadget_driver->resume(&mtu->g);
		spin_lock(&mtu->lock);
	पूर्ण
पूर्ण

/* called when SOF packets stop क्रम 3+ msec or enters U3 */
व्योम mtu3_gadget_suspend(काष्ठा mtu3 *mtu)
अणु
	dev_dbg(mtu->dev, "gadget SUSPEND\n");
	अगर (mtu->gadget_driver && mtu->gadget_driver->suspend) अणु
		spin_unlock(&mtu->lock);
		mtu->gadget_driver->suspend(&mtu->g);
		spin_lock(&mtu->lock);
	पूर्ण
पूर्ण

/* called when VBUS drops below session threshold, and in other हालs */
व्योम mtu3_gadget_disconnect(काष्ठा mtu3 *mtu)
अणु
	dev_dbg(mtu->dev, "gadget DISCONNECT\n");
	अगर (mtu->gadget_driver && mtu->gadget_driver->disconnect) अणु
		spin_unlock(&mtu->lock);
		mtu->gadget_driver->disconnect(&mtu->g);
		spin_lock(&mtu->lock);
	पूर्ण

	mtu3_state_reset(mtu);
	usb_gadget_set_state(&mtu->g, USB_STATE_NOTATTACHED);
पूर्ण

व्योम mtu3_gadget_reset(काष्ठा mtu3 *mtu)
अणु
	dev_dbg(mtu->dev, "gadget RESET\n");

	/* report disconnect, अगर we didn't flush EP state */
	अगर (mtu->g.speed != USB_SPEED_UNKNOWN)
		mtu3_gadget_disconnect(mtu);
	अन्यथा
		mtu3_state_reset(mtu);
पूर्ण
