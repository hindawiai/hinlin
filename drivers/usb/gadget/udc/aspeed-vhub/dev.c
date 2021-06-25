<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * aspeed-vhub -- Driver क्रम Aspeed SoC "vHub" USB gadget
 *
 * dev.c - Inभागidual device/gadget management (ie, a port = a gadget)
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
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "vhub.h"

व्योम ast_vhub_dev_irq(काष्ठा ast_vhub_dev *d)
अणु
	u32 istat = पढ़ोl(d->regs + AST_VHUB_DEV_ISR);

	ग_लिखोl(istat, d->regs + AST_VHUB_DEV_ISR);

	अगर (istat & VHUV_DEV_IRQ_EP0_IN_ACK_STALL)
		ast_vhub_ep0_handle_ack(&d->ep0, true);
	अगर (istat & VHUV_DEV_IRQ_EP0_OUT_ACK_STALL)
		ast_vhub_ep0_handle_ack(&d->ep0, false);
	अगर (istat & VHUV_DEV_IRQ_EP0_SETUP)
		ast_vhub_ep0_handle_setup(&d->ep0);
पूर्ण

अटल व्योम ast_vhub_dev_enable(काष्ठा ast_vhub_dev *d)
अणु
	u32 reg, hmsk, i;

	अगर (d->enabled)
		वापस;

	/* Cleanup EP0 state */
	ast_vhub_reset_ep0(d);

	/* Enable device and its EP0 पूर्णांकerrupts */
	reg = VHUB_DEV_EN_ENABLE_PORT |
		VHUB_DEV_EN_EP0_IN_ACK_IRQEN |
		VHUB_DEV_EN_EP0_OUT_ACK_IRQEN |
		VHUB_DEV_EN_EP0_SETUP_IRQEN;
	अगर (d->gadget.speed == USB_SPEED_HIGH)
		reg |= VHUB_DEV_EN_SPEED_SEL_HIGH;
	ग_लिखोl(reg, d->regs + AST_VHUB_DEV_EN_CTRL);

	/* Enable device पूर्णांकerrupt in the hub as well */
	hmsk = VHUB_IRQ_DEVICE1 << d->index;
	reg = पढ़ोl(d->vhub->regs + AST_VHUB_IER);
	reg |= hmsk;
	ग_लिखोl(reg, d->vhub->regs + AST_VHUB_IER);

	/* Set EP0 DMA buffer address */
	ग_लिखोl(d->ep0.buf_dma, d->regs + AST_VHUB_DEV_EP0_DATA);

	/* Clear stall on all EPs */
	क्रम (i = 0; i < d->max_epns; i++) अणु
		काष्ठा ast_vhub_ep *ep = d->epns[i];

		अगर (ep && (ep->epn.stalled || ep->epn.wedged)) अणु
			ep->epn.stalled = false;
			ep->epn.wedged = false;
			ast_vhub_update_epn_stall(ep);
		पूर्ण
	पूर्ण

	/* Additional cleanups */
	d->wakeup_en = false;
	d->enabled = true;
पूर्ण

अटल व्योम ast_vhub_dev_disable(काष्ठा ast_vhub_dev *d)
अणु
	u32 reg, hmsk;

	अगर (!d->enabled)
		वापस;

	/* Disable device पूर्णांकerrupt in the hub */
	hmsk = VHUB_IRQ_DEVICE1 << d->index;
	reg = पढ़ोl(d->vhub->regs + AST_VHUB_IER);
	reg &= ~hmsk;
	ग_लिखोl(reg, d->vhub->regs + AST_VHUB_IER);

	/* Then disable device */
	ग_लिखोl(0, d->regs + AST_VHUB_DEV_EN_CTRL);
	d->gadget.speed = USB_SPEED_UNKNOWN;
	d->enabled = false;
पूर्ण

अटल पूर्णांक ast_vhub_dev_feature(काष्ठा ast_vhub_dev *d,
				u16 wIndex, u16 wValue,
				bool is_set)
अणु
	DDBG(d, "%s_FEATURE(dev val=%02x)\n",
	     is_set ? "SET" : "CLEAR", wValue);

	अगर (wValue != USB_DEVICE_REMOTE_WAKEUP)
		वापस std_req_driver;

	d->wakeup_en = is_set;

	वापस std_req_complete;
पूर्ण

अटल पूर्णांक ast_vhub_ep_feature(काष्ठा ast_vhub_dev *d,
			       u16 wIndex, u16 wValue, bool is_set)
अणु
	काष्ठा ast_vhub_ep *ep;
	पूर्णांक ep_num;

	ep_num = wIndex & USB_ENDPOINT_NUMBER_MASK;
	DDBG(d, "%s_FEATURE(ep%d val=%02x)\n",
	     is_set ? "SET" : "CLEAR", ep_num, wValue);
	अगर (ep_num == 0)
		वापस std_req_complete;
	अगर (ep_num >= d->max_epns || !d->epns[ep_num - 1])
		वापस std_req_stall;
	अगर (wValue != USB_ENDPOINT_HALT)
		वापस std_req_driver;

	ep = d->epns[ep_num - 1];
	अगर (WARN_ON(!ep))
		वापस std_req_stall;

	अगर (!ep->epn.enabled || !ep->ep.desc || ep->epn.is_iso ||
	    ep->epn.is_in != !!(wIndex & USB_सूची_IN))
		वापस std_req_stall;

	DDBG(d, "%s stall on EP %d\n",
	     is_set ? "setting" : "clearing", ep_num);
	ep->epn.stalled = is_set;
	ast_vhub_update_epn_stall(ep);

	वापस std_req_complete;
पूर्ण

अटल पूर्णांक ast_vhub_dev_status(काष्ठा ast_vhub_dev *d,
			       u16 wIndex, u16 wValue)
अणु
	u8 st0;

	DDBG(d, "GET_STATUS(dev)\n");

	st0 = d->gadget.is_selfघातered << USB_DEVICE_SELF_POWERED;
	अगर (d->wakeup_en)
		st0 |= 1 << USB_DEVICE_REMOTE_WAKEUP;

	वापस ast_vhub_simple_reply(&d->ep0, st0, 0);
पूर्ण

अटल पूर्णांक ast_vhub_ep_status(काष्ठा ast_vhub_dev *d,
			      u16 wIndex, u16 wValue)
अणु
	पूर्णांक ep_num = wIndex & USB_ENDPOINT_NUMBER_MASK;
	काष्ठा ast_vhub_ep *ep;
	u8 st0 = 0;

	DDBG(d, "GET_STATUS(ep%d)\n", ep_num);

	अगर (ep_num >= d->max_epns)
		वापस std_req_stall;
	अगर (ep_num != 0) अणु
		ep = d->epns[ep_num - 1];
		अगर (!ep)
			वापस std_req_stall;
		अगर (!ep->epn.enabled || !ep->ep.desc || ep->epn.is_iso ||
		    ep->epn.is_in != !!(wIndex & USB_सूची_IN))
			वापस std_req_stall;
		अगर (ep->epn.stalled)
			st0 |= 1 << USB_ENDPOINT_HALT;
	पूर्ण

	वापस ast_vhub_simple_reply(&d->ep0, st0, 0);
पूर्ण

अटल व्योम ast_vhub_dev_set_address(काष्ठा ast_vhub_dev *d, u8 addr)
अणु
	u32 reg;

	DDBG(d, "SET_ADDRESS: Got address %x\n", addr);

	reg = पढ़ोl(d->regs + AST_VHUB_DEV_EN_CTRL);
	reg &= ~VHUB_DEV_EN_ADDR_MASK;
	reg |= VHUB_DEV_EN_SET_ADDR(addr);
	ग_लिखोl(reg, d->regs + AST_VHUB_DEV_EN_CTRL);
पूर्ण

पूर्णांक ast_vhub_std_dev_request(काष्ठा ast_vhub_ep *ep,
			     काष्ठा usb_ctrlrequest *crq)
अणु
	काष्ठा ast_vhub_dev *d = ep->dev;
	u16 wValue, wIndex;

	/* No driver, we shouldn't be enabled ... */
	अगर (!d->driver || !d->enabled) अणु
		EPDBG(ep,
		      "Device is wrong state driver=%p enabled=%d\n",
		      d->driver, d->enabled);
		वापस std_req_stall;
	पूर्ण

	/*
	 * Note: we used to reject/stall requests जबतक suspended,
	 * we करोn't करो that anymore as we seem to have हालs of
	 * mass storage getting very upset.
	 */

	/* First packet, grab speed */
	अगर (d->gadget.speed == USB_SPEED_UNKNOWN) अणु
		d->gadget.speed = ep->vhub->speed;
		अगर (d->gadget.speed > d->driver->max_speed)
			d->gadget.speed = d->driver->max_speed;
		DDBG(d, "fist packet, captured speed %d\n",
		     d->gadget.speed);
	पूर्ण

	wValue = le16_to_cpu(crq->wValue);
	wIndex = le16_to_cpu(crq->wIndex);

	चयन ((crq->bRequestType << 8) | crq->bRequest) अणु
		/* SET_ADDRESS */
	हाल DeviceOutRequest | USB_REQ_SET_ADDRESS:
		ast_vhub_dev_set_address(d, wValue);
		वापस std_req_complete;

		/* GET_STATUS */
	हाल DeviceRequest | USB_REQ_GET_STATUS:
		वापस ast_vhub_dev_status(d, wIndex, wValue);
	हाल InterfaceRequest | USB_REQ_GET_STATUS:
		वापस ast_vhub_simple_reply(ep, 0, 0);
	हाल Endpoपूर्णांकRequest | USB_REQ_GET_STATUS:
		वापस ast_vhub_ep_status(d, wIndex, wValue);

		/* SET/CLEAR_FEATURE */
	हाल DeviceOutRequest | USB_REQ_SET_FEATURE:
		वापस ast_vhub_dev_feature(d, wIndex, wValue, true);
	हाल DeviceOutRequest | USB_REQ_CLEAR_FEATURE:
		वापस ast_vhub_dev_feature(d, wIndex, wValue, false);
	हाल Endpoपूर्णांकOutRequest | USB_REQ_SET_FEATURE:
		वापस ast_vhub_ep_feature(d, wIndex, wValue, true);
	हाल Endpoपूर्णांकOutRequest | USB_REQ_CLEAR_FEATURE:
		वापस ast_vhub_ep_feature(d, wIndex, wValue, false);
	पूर्ण
	वापस std_req_driver;
पूर्ण

अटल पूर्णांक ast_vhub_udc_wakeup(काष्ठा usb_gadget* gadget)
अणु
	काष्ठा ast_vhub_dev *d = to_ast_dev(gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -EINVAL;

	spin_lock_irqsave(&d->vhub->lock, flags);
	अगर (!d->wakeup_en)
		जाओ err;

	DDBG(d, "Device initiated wakeup\n");

	/* Wakeup the host */
	ast_vhub_hub_wake_all(d->vhub);
	rc = 0;
 err:
	spin_unlock_irqrestore(&d->vhub->lock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक ast_vhub_udc_get_frame(काष्ठा usb_gadget* gadget)
अणु
	काष्ठा ast_vhub_dev *d = to_ast_dev(gadget);

	वापस (पढ़ोl(d->vhub->regs + AST_VHUB_USBSTS) >> 16) & 0x7ff;
पूर्ण

अटल व्योम ast_vhub_dev_nuke(काष्ठा ast_vhub_dev *d)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < d->max_epns; i++) अणु
		अगर (!d->epns[i])
			जारी;
		ast_vhub_nuke(d->epns[i], -ESHUTDOWN);
	पूर्ण
पूर्ण

अटल पूर्णांक ast_vhub_udc_pullup(काष्ठा usb_gadget* gadget, पूर्णांक on)
अणु
	काष्ठा ast_vhub_dev *d = to_ast_dev(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->vhub->lock, flags);

	DDBG(d, "pullup(%d)\n", on);

	/* Mark disconnected in the hub */
	ast_vhub_device_connect(d->vhub, d->index, on);

	/*
	 * If enabled, nuke all requests अगर any (there shouldn't be)
	 * and disable the port. This will clear the address too.
	 */
	अगर (d->enabled) अणु
		ast_vhub_dev_nuke(d);
		ast_vhub_dev_disable(d);
	पूर्ण

	spin_unlock_irqrestore(&d->vhub->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ast_vhub_udc_start(काष्ठा usb_gadget *gadget,
			      काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा ast_vhub_dev *d = to_ast_dev(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->vhub->lock, flags);

	DDBG(d, "start\n");

	/* We करोn't करो much more until the hub enables us */
	d->driver = driver;
	d->gadget.is_selfघातered = 1;

	spin_unlock_irqrestore(&d->vhub->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा usb_ep *ast_vhub_udc_match_ep(काष्ठा usb_gadget *gadget,
					    काष्ठा usb_endpoपूर्णांक_descriptor *desc,
					    काष्ठा usb_ss_ep_comp_descriptor *ss)
अणु
	काष्ठा ast_vhub_dev *d = to_ast_dev(gadget);
	काष्ठा ast_vhub_ep *ep;
	काष्ठा usb_ep *u_ep;
	अचिन्हित पूर्णांक max, addr, i;

	DDBG(d, "Match EP type %d\n", usb_endpoपूर्णांक_type(desc));

	/*
	 * First we need to look क्रम an existing unclaimed EP as another
	 * configuration may have alपढ़ोy associated a bunch of EPs with
	 * this gadget. This duplicates the code in usb_ep_स्वतःconfig_ss()
	 * unक्रमtunately.
	 */
	list_क्रम_each_entry(u_ep, &gadget->ep_list, ep_list) अणु
		अगर (usb_gadget_ep_match_desc(gadget, u_ep, desc, ss)) अणु
			DDBG(d, " -> using existing EP%d\n",
			     to_ast_ep(u_ep)->d_idx);
			वापस u_ep;
		पूर्ण
	पूर्ण

	/*
	 * We didn't find one, we need to grab one from the pool.
	 *
	 * First let's करो some sanity checking
	 */
	चयन(usb_endpoपूर्णांक_type(desc)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		/* Only EP0 can be a control endpoपूर्णांक */
		वापस शून्य;
	हाल USB_ENDPOINT_XFER_ISOC:
		/* ISO:	 limit 1023 bytes full speed, 1024 high/super speed */
		अगर (gadget_is_dualspeed(gadget))
			max = 1024;
		अन्यथा
			max = 1023;
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (gadget_is_dualspeed(gadget))
			max = 512;
		अन्यथा
			max = 64;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		अगर (gadget_is_dualspeed(gadget))
			max = 1024;
		अन्यथा
			max = 64;
		अवरोध;
	पूर्ण
	अगर (usb_endpoपूर्णांक_maxp(desc) > max)
		वापस शून्य;

	/*
	 * Find a मुक्त EP address क्रम that device. We can't
	 * let the generic code assign these as it would
	 * create overlapping numbers क्रम IN and OUT which
	 * we करोn't support, so also create a suitable name
	 * that will allow the generic code to use our
	 * asचिन्हित address.
	 */
	क्रम (i = 0; i < d->max_epns; i++)
		अगर (d->epns[i] == शून्य)
			अवरोध;
	अगर (i >= d->max_epns)
		वापस शून्य;
	addr = i + 1;

	/*
	 * Now grab an EP from the shared pool and associate
	 * it with our device
	 */
	ep = ast_vhub_alloc_epn(d, addr);
	अगर (!ep)
		वापस शून्य;
	DDBG(d, "Allocated epn#%d for port EP%d\n",
	     ep->epn.g_idx, addr);

	वापस &ep->ep;
पूर्ण

अटल पूर्णांक ast_vhub_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा ast_vhub_dev *d = to_ast_dev(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->vhub->lock, flags);

	DDBG(d, "stop\n");

	d->driver = शून्य;
	d->gadget.speed = USB_SPEED_UNKNOWN;

	ast_vhub_dev_nuke(d);

	अगर (d->enabled)
		ast_vhub_dev_disable(d);

	spin_unlock_irqrestore(&d->vhub->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops ast_vhub_udc_ops = अणु
	.get_frame	= ast_vhub_udc_get_frame,
	.wakeup		= ast_vhub_udc_wakeup,
	.pullup		= ast_vhub_udc_pullup,
	.udc_start	= ast_vhub_udc_start,
	.udc_stop	= ast_vhub_udc_stop,
	.match_ep	= ast_vhub_udc_match_ep,
पूर्ण;

व्योम ast_vhub_dev_suspend(काष्ठा ast_vhub_dev *d)
अणु
	अगर (d->driver && d->driver->suspend) अणु
		spin_unlock(&d->vhub->lock);
		d->driver->suspend(&d->gadget);
		spin_lock(&d->vhub->lock);
	पूर्ण
पूर्ण

व्योम ast_vhub_dev_resume(काष्ठा ast_vhub_dev *d)
अणु
	अगर (d->driver && d->driver->resume) अणु
		spin_unlock(&d->vhub->lock);
		d->driver->resume(&d->gadget);
		spin_lock(&d->vhub->lock);
	पूर्ण
पूर्ण

व्योम ast_vhub_dev_reset(काष्ठा ast_vhub_dev *d)
अणु
	/* No driver, just disable the device and वापस */
	अगर (!d->driver) अणु
		ast_vhub_dev_disable(d);
		वापस;
	पूर्ण

	/* If the port isn't enabled, just enable it */
	अगर (!d->enabled) अणु
		DDBG(d, "Reset of disabled device, enabling...\n");
		ast_vhub_dev_enable(d);
	पूर्ण अन्यथा अणु
		DDBG(d, "Reset of enabled device, resetting...\n");
		spin_unlock(&d->vhub->lock);
		usb_gadget_udc_reset(&d->gadget, d->driver);
		spin_lock(&d->vhub->lock);

		/*
		 * Disable and maybe re-enable HW, this will clear the address
		 * and speed setting.
		 */
		ast_vhub_dev_disable(d);
		ast_vhub_dev_enable(d);
	पूर्ण
पूर्ण

व्योम ast_vhub_del_dev(काष्ठा ast_vhub_dev *d)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->vhub->lock, flags);
	अगर (!d->रेजिस्टरed) अणु
		spin_unlock_irqrestore(&d->vhub->lock, flags);
		वापस;
	पूर्ण
	d->रेजिस्टरed = false;
	spin_unlock_irqrestore(&d->vhub->lock, flags);

	usb_del_gadget_udc(&d->gadget);
	device_unरेजिस्टर(d->port_dev);
	kमुक्त(d->epns);
पूर्ण

अटल व्योम ast_vhub_dev_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

पूर्णांक ast_vhub_init_dev(काष्ठा ast_vhub *vhub, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा ast_vhub_dev *d = &vhub->ports[idx].dev;
	काष्ठा device *parent = &vhub->pdev->dev;
	पूर्णांक rc;

	d->vhub = vhub;
	d->index = idx;
	d->name = devm_kaप्र_लिखो(parent, GFP_KERNEL, "port%d", idx+1);
	d->regs = vhub->regs + 0x100 + 0x10 * idx;

	ast_vhub_init_ep0(vhub, &d->ep0, d);

	/*
	 * A USB device can have up to 30 endpoपूर्णांकs besides control
	 * endpoपूर्णांक 0.
	 */
	d->max_epns = min_t(u32, vhub->max_epns, 30);
	d->epns = kसुस्मृति(d->max_epns, माप(*d->epns), GFP_KERNEL);
	अगर (!d->epns)
		वापस -ENOMEM;

	/*
	 * The UDC core really needs us to have separate and uniquely
	 * named "parent" devices क्रम each port so we create a sub device
	 * here क्रम that purpose
	 */
	d->port_dev = kzalloc(माप(काष्ठा device), GFP_KERNEL);
	अगर (!d->port_dev) अणु
		rc = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण
	device_initialize(d->port_dev);
	d->port_dev->release = ast_vhub_dev_release;
	d->port_dev->parent = parent;
	dev_set_name(d->port_dev, "%s:p%d", dev_name(parent), idx + 1);
	rc = device_add(d->port_dev);
	अगर (rc)
		जाओ fail_add;

	/* Populate gadget */
	INIT_LIST_HEAD(&d->gadget.ep_list);
	d->gadget.ops = &ast_vhub_udc_ops;
	d->gadget.ep0 = &d->ep0.ep;
	d->gadget.name = KBUILD_MODNAME;
	अगर (vhub->क्रमce_usb1)
		d->gadget.max_speed = USB_SPEED_FULL;
	अन्यथा
		d->gadget.max_speed = USB_SPEED_HIGH;
	d->gadget.speed = USB_SPEED_UNKNOWN;
	d->gadget.dev.of_node = vhub->pdev->dev.of_node;

	rc = usb_add_gadget_udc(d->port_dev, &d->gadget);
	अगर (rc != 0)
		जाओ fail_udc;
	d->रेजिस्टरed = true;

	वापस 0;
 fail_udc:
	device_del(d->port_dev);
 fail_add:
	put_device(d->port_dev);
 fail_alloc:
	kमुक्त(d->epns);

	वापस rc;
पूर्ण
