<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * aspeed-vhub -- Driver क्रम Aspeed SoC "vHub" USB gadget
 *
 * hub.c - भव hub handling
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
#समावेश <linux/bcd.h>
#समावेश <linux/version.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "vhub.h"

/* usb 2.0 hub device descriptor
 *
 * A few things we may want to improve here:
 *
 *    - We may need to indicate TT support
 *    - We may need a device qualअगरier descriptor
 *	as devices can pretend to be usb1 or 2
 *    - Make vid/did overridable
 *    - make it look like usb1 अगर usb1 mode क्रमced
 */
#घोषणा KERNEL_REL	bin2bcd(LINUX_VERSION_MAJOR)
#घोषणा KERNEL_VER	bin2bcd(LINUX_VERSION_PATCHLEVEL)

क्रमागत अणु
	AST_VHUB_STR_INDEX_MAX = 4,
	AST_VHUB_STR_MANUF = 3,
	AST_VHUB_STR_PRODUCT = 2,
	AST_VHUB_STR_SERIAL = 1,
पूर्ण;

अटल स्थिर काष्ठा usb_device_descriptor ast_vhub_dev_desc = अणु
	.bLength		= USB_DT_DEVICE_SIZE,
	.bDescriptorType	= USB_DT_DEVICE,
	.bcdUSB			= cpu_to_le16(0x0200),
	.bDeviceClass		= USB_CLASS_HUB,
	.bDeviceSubClass	= 0,
	.bDeviceProtocol	= 1,
	.bMaxPacketSize0	= 64,
	.idVenकरोr		= cpu_to_le16(0x1d6b),
	.idProduct		= cpu_to_le16(0x0107),
	.bcdDevice		= cpu_to_le16(0x0100),
	.iManufacturer		= AST_VHUB_STR_MANUF,
	.iProduct		= AST_VHUB_STR_PRODUCT,
	.iSerialNumber		= AST_VHUB_STR_SERIAL,
	.bNumConfigurations	= 1,
पूर्ण;

/*
 * Configuration descriptor: same comments as above
 * regarding handling USB1 mode.
 */

/*
 * We करोn't use माप() as Linux definition of
 * काष्ठा usb_endpoपूर्णांक_descriptor contains 2
 * extra bytes
 */
#घोषणा AST_VHUB_CONF_DESC_SIZE	(USB_DT_CONFIG_SIZE + \
				 USB_DT_INTERFACE_SIZE + \
				 USB_DT_ENDPOINT_SIZE)

अटल स्थिर काष्ठा ast_vhub_full_cdesc ast_vhub_conf_desc = अणु
	.cfg = अणु
		.bLength		= USB_DT_CONFIG_SIZE,
		.bDescriptorType	= USB_DT_CONFIG,
		.wTotalLength		= cpu_to_le16(AST_VHUB_CONF_DESC_SIZE),
		.bNumInterfaces		= 1,
		.bConfigurationValue	= 1,
		.iConfiguration		= 0,
		.bmAttributes		= USB_CONFIG_ATT_ONE |
					  USB_CONFIG_ATT_SELFPOWER |
					  USB_CONFIG_ATT_WAKEUP,
		.bMaxPower		= 0,
	पूर्ण,
	.पूर्णांकf = अणु
		.bLength		= USB_DT_INTERFACE_SIZE,
		.bDescriptorType	= USB_DT_INTERFACE,
		.bInterfaceNumber	= 0,
		.bAlternateSetting	= 0,
		.bNumEndpoपूर्णांकs		= 1,
		.bInterfaceClass	= USB_CLASS_HUB,
		.bInterfaceSubClass	= 0,
		.bInterfaceProtocol	= 0,
		.iInterface		= 0,
	पूर्ण,
	.ep = अणु
		.bLength		= USB_DT_ENDPOINT_SIZE,
		.bDescriptorType	= USB_DT_ENDPOINT,
		.bEndpoपूर्णांकAddress	= 0x81,
		.bmAttributes		= USB_ENDPOINT_XFER_INT,
		.wMaxPacketSize		= cpu_to_le16(1),
		.bInterval		= 0x0c,
	पूर्ण,
पूर्ण;

#घोषणा AST_VHUB_HUB_DESC_SIZE	(USB_DT_HUB_NONVAR_SIZE + 2)

अटल स्थिर काष्ठा usb_hub_descriptor ast_vhub_hub_desc = अणु
	.bDescLength			= AST_VHUB_HUB_DESC_SIZE,
	.bDescriptorType		= USB_DT_HUB,
	.bNbrPorts			= AST_VHUB_NUM_PORTS,
	.wHubCharacteristics		= cpu_to_le16(HUB_CHAR_NO_LPSM),
	.bPwrOn2PwrGood			= 10,
	.bHubContrCurrent		= 0,
	.u.hs.DeviceRemovable[0]	= 0,
	.u.hs.DeviceRemovable[1]	= 0xff,
पूर्ण;

/*
 * These strings converted to UTF-16 must be smaller than
 * our EP0 buffer.
 */
अटल स्थिर काष्ठा usb_string ast_vhub_str_array[] = अणु
	अणु
		.id = AST_VHUB_STR_SERIAL,
		.s = "00000000"
	पूर्ण,
	अणु
		.id = AST_VHUB_STR_PRODUCT,
		.s = "USB Virtual Hub"
	पूर्ण,
	अणु
		.id = AST_VHUB_STR_MANUF,
		.s = "Aspeed"
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_gadget_strings ast_vhub_strings = अणु
	.language = 0x0409,
	.strings = (काष्ठा usb_string *)ast_vhub_str_array
पूर्ण;

अटल पूर्णांक ast_vhub_hub_dev_status(काष्ठा ast_vhub_ep *ep,
				   u16 wIndex, u16 wValue)
अणु
	u8 st0;

	EPDBG(ep, "GET_STATUS(dev)\n");

	/*
	 * Mark it as self-घातered, I करोubt the BMC is घातered off
	 * the USB bus ...
	 */
	st0 = 1 << USB_DEVICE_SELF_POWERED;

	/*
	 * Need to द्विगुन check how remote wakeup actually works
	 * on that chip and what triggers it.
	 */
	अगर (ep->vhub->wakeup_en)
		st0 |= 1 << USB_DEVICE_REMOTE_WAKEUP;

	वापस ast_vhub_simple_reply(ep, st0, 0);
पूर्ण

अटल पूर्णांक ast_vhub_hub_ep_status(काष्ठा ast_vhub_ep *ep,
				  u16 wIndex, u16 wValue)
अणु
	पूर्णांक ep_num;
	u8 st0 = 0;

	ep_num = wIndex & USB_ENDPOINT_NUMBER_MASK;
	EPDBG(ep, "GET_STATUS(ep%d)\n", ep_num);

	/* On the hub we have only EP 0 and 1 */
	अगर (ep_num == 1) अणु
		अगर (ep->vhub->ep1_stalled)
			st0 |= 1 << USB_ENDPOINT_HALT;
	पूर्ण अन्यथा अगर (ep_num != 0)
		वापस std_req_stall;

	वापस ast_vhub_simple_reply(ep, st0, 0);
पूर्ण

अटल पूर्णांक ast_vhub_hub_dev_feature(काष्ठा ast_vhub_ep *ep,
				    u16 wIndex, u16 wValue,
				    bool is_set)
अणु
	EPDBG(ep, "%s_FEATURE(dev val=%02x)\n",
	      is_set ? "SET" : "CLEAR", wValue);

	अगर (wValue != USB_DEVICE_REMOTE_WAKEUP)
		वापस std_req_stall;

	ep->vhub->wakeup_en = is_set;
	EPDBG(ep, "Hub remote wakeup %s\n",
	      is_set ? "enabled" : "disabled");

	वापस std_req_complete;
पूर्ण

अटल पूर्णांक ast_vhub_hub_ep_feature(काष्ठा ast_vhub_ep *ep,
				   u16 wIndex, u16 wValue,
				   bool is_set)
अणु
	पूर्णांक ep_num;
	u32 reg;

	ep_num = wIndex & USB_ENDPOINT_NUMBER_MASK;
	EPDBG(ep, "%s_FEATURE(ep%d val=%02x)\n",
	      is_set ? "SET" : "CLEAR", ep_num, wValue);

	अगर (ep_num > 1)
		वापस std_req_stall;
	अगर (wValue != USB_ENDPOINT_HALT)
		वापस std_req_stall;
	अगर (ep_num == 0)
		वापस std_req_complete;

	EPDBG(ep, "%s stall on EP 1\n",
	      is_set ? "setting" : "clearing");

	ep->vhub->ep1_stalled = is_set;
	reg = पढ़ोl(ep->vhub->regs + AST_VHUB_EP1_CTRL);
	अगर (is_set) अणु
		reg |= VHUB_EP1_CTRL_STALL;
	पूर्ण अन्यथा अणु
		reg &= ~VHUB_EP1_CTRL_STALL;
		reg |= VHUB_EP1_CTRL_RESET_TOGGLE;
	पूर्ण
	ग_लिखोl(reg, ep->vhub->regs + AST_VHUB_EP1_CTRL);

	वापस std_req_complete;
पूर्ण

अटल पूर्णांक ast_vhub_rep_desc(काष्ठा ast_vhub_ep *ep,
			     u8 desc_type, u16 len)
अणु
	माप_प्रकार dsize;
	काष्ठा ast_vhub *vhub = ep->vhub;

	EPDBG(ep, "GET_DESCRIPTOR(type:%d)\n", desc_type);

	/*
	 * Copy first to EP buffer and send from there, so
	 * we can करो some in-place patching अगर needed. We know
	 * the EP buffer is big enough but ensure that करोesn't
	 * change. We करो that now rather than later after we
	 * have checked sizes etc... to aव्योम a gcc bug where
	 * it thinks len is स्थिरant and barfs about पढ़ो
	 * overflows in स_नकल.
	 */
	चयन(desc_type) अणु
	हाल USB_DT_DEVICE:
		dsize = USB_DT_DEVICE_SIZE;
		स_नकल(ep->buf, &vhub->vhub_dev_desc, dsize);
		BUILD_BUG_ON(dsize > माप(vhub->vhub_dev_desc));
		BUILD_BUG_ON(USB_DT_DEVICE_SIZE >= AST_VHUB_EP0_MAX_PACKET);
		अवरोध;
	हाल USB_DT_CONFIG:
		dsize = AST_VHUB_CONF_DESC_SIZE;
		स_नकल(ep->buf, &vhub->vhub_conf_desc, dsize);
		BUILD_BUG_ON(dsize > माप(vhub->vhub_conf_desc));
		BUILD_BUG_ON(AST_VHUB_CONF_DESC_SIZE >= AST_VHUB_EP0_MAX_PACKET);
		अवरोध;
	हाल USB_DT_HUB:
		dsize = AST_VHUB_HUB_DESC_SIZE;
		स_नकल(ep->buf, &vhub->vhub_hub_desc, dsize);
		BUILD_BUG_ON(dsize > माप(vhub->vhub_hub_desc));
		BUILD_BUG_ON(AST_VHUB_HUB_DESC_SIZE >= AST_VHUB_EP0_MAX_PACKET);
		अवरोध;
	शेष:
		वापस std_req_stall;
	पूर्ण

	/* Crop requested length */
	अगर (len > dsize)
		len = dsize;

	/* Shoot it from the EP buffer */
	वापस ast_vhub_reply(ep, शून्य, len);
पूर्ण

अटल काष्ठा usb_gadget_strings*
ast_vhub_str_of_container(काष्ठा usb_gadget_string_container *container)
अणु
	वापस (काष्ठा usb_gadget_strings *)container->stash;
पूर्ण

अटल पूर्णांक ast_vhub_collect_languages(काष्ठा ast_vhub *vhub, व्योम *buf,
				      माप_प्रकार size)
अणु
	पूर्णांक rc, hdr_len, nlangs, max_langs;
	काष्ठा usb_gadget_strings *lang_str;
	काष्ठा usb_gadget_string_container *container;
	काष्ठा usb_string_descriptor *sdesc = buf;

	nlangs = 0;
	hdr_len = माप(काष्ठा usb_descriptor_header);
	max_langs = (size - hdr_len) / माप(sdesc->wData[0]);
	list_क्रम_each_entry(container, &vhub->vhub_str_desc, list) अणु
		अगर (nlangs >= max_langs)
			अवरोध;

		lang_str = ast_vhub_str_of_container(container);
		sdesc->wData[nlangs++] = cpu_to_le16(lang_str->language);
	पूर्ण

	rc = hdr_len + nlangs * माप(sdesc->wData[0]);
	sdesc->bLength = rc;
	sdesc->bDescriptorType = USB_DT_STRING;

	वापस rc;
पूर्ण

अटल काष्ठा usb_gadget_strings *ast_vhub_lookup_string(काष्ठा ast_vhub *vhub,
							 u16 lang_id)
अणु
	काष्ठा usb_gadget_strings *lang_str;
	काष्ठा usb_gadget_string_container *container;

	list_क्रम_each_entry(container, &vhub->vhub_str_desc, list) अणु
		lang_str = ast_vhub_str_of_container(container);
		अगर (lang_str->language == lang_id)
			वापस lang_str;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक ast_vhub_rep_string(काष्ठा ast_vhub_ep *ep,
			       u8 string_id, u16 lang_id,
			       u16 len)
अणु
	पूर्णांक rc;
	u8 buf[256];
	काष्ठा ast_vhub *vhub = ep->vhub;
	काष्ठा usb_gadget_strings *lang_str;

	अगर (string_id == 0) अणु
		rc = ast_vhub_collect_languages(vhub, buf, माप(buf));
	पूर्ण अन्यथा अणु
		lang_str = ast_vhub_lookup_string(vhub, lang_id);
		अगर (!lang_str)
			वापस std_req_stall;

		rc = usb_gadget_get_string(lang_str, string_id, buf);
	पूर्ण

	अगर (rc < 0 || rc >= AST_VHUB_EP0_MAX_PACKET)
		वापस std_req_stall;

	/* Shoot it from the EP buffer */
	स_नकल(ep->buf, buf, rc);
	वापस ast_vhub_reply(ep, शून्य, min_t(u16, rc, len));
पूर्ण

क्रमागत std_req_rc ast_vhub_std_hub_request(काष्ठा ast_vhub_ep *ep,
					 काष्ठा usb_ctrlrequest *crq)
अणु
	काष्ठा ast_vhub *vhub = ep->vhub;
	u16 wValue, wIndex, wLength;

	wValue = le16_to_cpu(crq->wValue);
	wIndex = le16_to_cpu(crq->wIndex);
	wLength = le16_to_cpu(crq->wLength);

	/* First packet, grab speed */
	अगर (vhub->speed == USB_SPEED_UNKNOWN) अणु
		u32 ustat = पढ़ोl(vhub->regs + AST_VHUB_USBSTS);
		अगर (ustat & VHUB_USBSTS_HISPEED)
			vhub->speed = USB_SPEED_HIGH;
		अन्यथा
			vhub->speed = USB_SPEED_FULL;
		UDCDBG(vhub, "USB status=%08x speed=%s\n", ustat,
		       vhub->speed == USB_SPEED_HIGH ? "high" : "full");
	पूर्ण

	चयन ((crq->bRequestType << 8) | crq->bRequest) अणु
		/* SET_ADDRESS */
	हाल DeviceOutRequest | USB_REQ_SET_ADDRESS:
		EPDBG(ep, "SET_ADDRESS: Got address %x\n", wValue);
		ग_लिखोl(wValue, vhub->regs + AST_VHUB_CONF);
		वापस std_req_complete;

		/* GET_STATUS */
	हाल DeviceRequest | USB_REQ_GET_STATUS:
		वापस ast_vhub_hub_dev_status(ep, wIndex, wValue);
	हाल InterfaceRequest | USB_REQ_GET_STATUS:
		वापस ast_vhub_simple_reply(ep, 0, 0);
	हाल Endpoपूर्णांकRequest | USB_REQ_GET_STATUS:
		वापस ast_vhub_hub_ep_status(ep, wIndex, wValue);

		/* SET/CLEAR_FEATURE */
	हाल DeviceOutRequest | USB_REQ_SET_FEATURE:
		वापस ast_vhub_hub_dev_feature(ep, wIndex, wValue, true);
	हाल DeviceOutRequest | USB_REQ_CLEAR_FEATURE:
		वापस ast_vhub_hub_dev_feature(ep, wIndex, wValue, false);
	हाल Endpoपूर्णांकOutRequest | USB_REQ_SET_FEATURE:
		वापस ast_vhub_hub_ep_feature(ep, wIndex, wValue, true);
	हाल Endpoपूर्णांकOutRequest | USB_REQ_CLEAR_FEATURE:
		वापस ast_vhub_hub_ep_feature(ep, wIndex, wValue, false);

		/* GET/SET_CONFIGURATION */
	हाल DeviceRequest | USB_REQ_GET_CONFIGURATION:
		वापस ast_vhub_simple_reply(ep, 1);
	हाल DeviceOutRequest | USB_REQ_SET_CONFIGURATION:
		अगर (wValue != 1)
			वापस std_req_stall;
		वापस std_req_complete;

		/* GET_DESCRIPTOR */
	हाल DeviceRequest | USB_REQ_GET_DESCRIPTOR:
		चयन (wValue >> 8) अणु
		हाल USB_DT_DEVICE:
		हाल USB_DT_CONFIG:
			वापस ast_vhub_rep_desc(ep, wValue >> 8,
						 wLength);
		हाल USB_DT_STRING:
			वापस ast_vhub_rep_string(ep, wValue & 0xff,
						   wIndex, wLength);
		पूर्ण
		वापस std_req_stall;

		/* GET/SET_INTERFACE */
	हाल DeviceRequest | USB_REQ_GET_INTERFACE:
		वापस ast_vhub_simple_reply(ep, 0);
	हाल DeviceOutRequest | USB_REQ_SET_INTERFACE:
		अगर (wValue != 0 || wIndex != 0)
			वापस std_req_stall;
		वापस std_req_complete;
	पूर्ण
	वापस std_req_stall;
पूर्ण

अटल व्योम ast_vhub_update_hub_ep1(काष्ठा ast_vhub *vhub,
				    अचिन्हित पूर्णांक port)
अणु
	/* Update HW EP1 response */
	u32 reg = पढ़ोl(vhub->regs + AST_VHUB_EP1_STS_CHG);
	u32 pmask = (1 << (port + 1));
	अगर (vhub->ports[port].change)
		reg |= pmask;
	अन्यथा
		reg &= ~pmask;
	ग_लिखोl(reg, vhub->regs + AST_VHUB_EP1_STS_CHG);
पूर्ण

अटल व्योम ast_vhub_change_port_stat(काष्ठा ast_vhub *vhub,
				      अचिन्हित पूर्णांक port,
				      u16 clr_flags,
				      u16 set_flags,
				      bool set_c)
अणु
	काष्ठा ast_vhub_port *p = &vhub->ports[port];
	u16 prev;

	/* Update port status */
	prev = p->status;
	p->status = (prev & ~clr_flags) | set_flags;
	DDBG(&p->dev, "port %d status %04x -> %04x (C=%d)\n",
	     port + 1, prev, p->status, set_c);

	/* Update change bits अगर needed */
	अगर (set_c) अणु
		u16 chg = p->status ^ prev;

		/* Only these are relevant क्रम change */
		chg &= USB_PORT_STAT_C_CONNECTION |
		       USB_PORT_STAT_C_ENABLE |
		       USB_PORT_STAT_C_SUSPEND |
		       USB_PORT_STAT_C_OVERCURRENT |
		       USB_PORT_STAT_C_RESET |
		       USB_PORT_STAT_C_L1;

		/*
		 * We only set USB_PORT_STAT_C_ENABLE अगर we are disabling
		 * the port as per USB spec, otherwise MacOS माला_लो upset
		 */
		अगर (p->status & USB_PORT_STAT_ENABLE)
			chg &= ~USB_PORT_STAT_C_ENABLE;

		p->change = chg;
		ast_vhub_update_hub_ep1(vhub, port);
	पूर्ण
पूर्ण

अटल व्योम ast_vhub_send_host_wakeup(काष्ठा ast_vhub *vhub)
अणु
	u32 reg = पढ़ोl(vhub->regs + AST_VHUB_CTRL);
	UDCDBG(vhub, "Waking up host !\n");
	reg |= VHUB_CTRL_MANUAL_REMOTE_WAKEUP;
	ग_लिखोl(reg, vhub->regs + AST_VHUB_CTRL);
पूर्ण

व्योम ast_vhub_device_connect(काष्ठा ast_vhub *vhub,
			     अचिन्हित पूर्णांक port, bool on)
अणु
	अगर (on)
		ast_vhub_change_port_stat(vhub, port, 0,
					  USB_PORT_STAT_CONNECTION, true);
	अन्यथा
		ast_vhub_change_port_stat(vhub, port,
					  USB_PORT_STAT_CONNECTION |
					  USB_PORT_STAT_ENABLE,
					  0, true);

	/*
	 * If the hub is set to wakup the host on connection events
	 * then send a wakeup.
	 */
	अगर (vhub->wakeup_en)
		ast_vhub_send_host_wakeup(vhub);
पूर्ण

अटल व्योम ast_vhub_wake_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ast_vhub *vhub = container_of(work,
					     काष्ठा ast_vhub,
					     wake_work);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	/*
	 * Wake all sleeping ports. If a port is suspended by
	 * the host suspend (without explicit state suspend),
	 * we let the normal host wake path deal with it later.
	 */
	spin_lock_irqsave(&vhub->lock, flags);
	क्रम (i = 0; i < vhub->max_ports; i++) अणु
		काष्ठा ast_vhub_port *p = &vhub->ports[i];

		अगर (!(p->status & USB_PORT_STAT_SUSPEND))
			जारी;
		ast_vhub_change_port_stat(vhub, i,
					  USB_PORT_STAT_SUSPEND,
					  0, true);
		ast_vhub_dev_resume(&p->dev);
	पूर्ण
	ast_vhub_send_host_wakeup(vhub);
	spin_unlock_irqrestore(&vhub->lock, flags);
पूर्ण

व्योम ast_vhub_hub_wake_all(काष्ठा ast_vhub *vhub)
अणु
	/*
	 * A device is trying to wake the world, because this
	 * can recurse पूर्णांकo the device, we अवरोध the call chain
	 * using a work queue
	 */
	schedule_work(&vhub->wake_work);
पूर्ण

अटल व्योम ast_vhub_port_reset(काष्ठा ast_vhub *vhub, u8 port)
अणु
	काष्ठा ast_vhub_port *p = &vhub->ports[port];
	u16 set, clr, speed;

	/* First mark disabled */
	ast_vhub_change_port_stat(vhub, port,
				  USB_PORT_STAT_ENABLE |
				  USB_PORT_STAT_SUSPEND,
				  USB_PORT_STAT_RESET,
				  false);

	अगर (!p->dev.driver)
		वापस;

	/*
	 * This will either "start" the port or reset the
	 * device अगर alपढ़ोy started...
	 */
	ast_vhub_dev_reset(&p->dev);

	/* Grab the right speed */
	speed = p->dev.driver->max_speed;
	अगर (speed == USB_SPEED_UNKNOWN || speed > vhub->speed)
		speed = vhub->speed;

	चयन (speed) अणु
	हाल USB_SPEED_LOW:
		set = USB_PORT_STAT_LOW_SPEED;
		clr = USB_PORT_STAT_HIGH_SPEED;
		अवरोध;
	हाल USB_SPEED_FULL:
		set = 0;
		clr = USB_PORT_STAT_LOW_SPEED |
			USB_PORT_STAT_HIGH_SPEED;
		अवरोध;
	हाल USB_SPEED_HIGH:
		set = USB_PORT_STAT_HIGH_SPEED;
		clr = USB_PORT_STAT_LOW_SPEED;
		अवरोध;
	शेष:
		UDCDBG(vhub, "Unsupported speed %d when"
		       " connecting device\n",
		       speed);
		वापस;
	पूर्ण
	clr |= USB_PORT_STAT_RESET;
	set |= USB_PORT_STAT_ENABLE;

	/* This should ideally be delayed ... */
	ast_vhub_change_port_stat(vhub, port, clr, set, true);
पूर्ण

अटल क्रमागत std_req_rc ast_vhub_set_port_feature(काष्ठा ast_vhub_ep *ep,
						 u8 port, u16 feat)
अणु
	काष्ठा ast_vhub *vhub = ep->vhub;
	काष्ठा ast_vhub_port *p;

	अगर (port == 0 || port > vhub->max_ports)
		वापस std_req_stall;
	port--;
	p = &vhub->ports[port];

	चयन(feat) अणु
	हाल USB_PORT_FEAT_SUSPEND:
		अगर (!(p->status & USB_PORT_STAT_ENABLE))
			वापस std_req_complete;
		ast_vhub_change_port_stat(vhub, port,
					  0, USB_PORT_STAT_SUSPEND,
					  false);
		ast_vhub_dev_suspend(&p->dev);
		वापस std_req_complete;
	हाल USB_PORT_FEAT_RESET:
		EPDBG(ep, "Port reset !\n");
		ast_vhub_port_reset(vhub, port);
		वापस std_req_complete;
	हाल USB_PORT_FEAT_POWER:
		/*
		 * On Power-on, we mark the connected flag changed,
		 * अगर there's a connected device, some hosts will
		 * otherwise fail to detect it.
		 */
		अगर (p->status & USB_PORT_STAT_CONNECTION) अणु
			p->change |= USB_PORT_STAT_C_CONNECTION;
			ast_vhub_update_hub_ep1(vhub, port);
		पूर्ण
		वापस std_req_complete;
	हाल USB_PORT_FEAT_TEST:
	हाल USB_PORT_FEAT_INDICATOR:
		/* We करोn't करो anything with these */
		वापस std_req_complete;
	पूर्ण
	वापस std_req_stall;
पूर्ण

अटल क्रमागत std_req_rc ast_vhub_clr_port_feature(काष्ठा ast_vhub_ep *ep,
						 u8 port, u16 feat)
अणु
	काष्ठा ast_vhub *vhub = ep->vhub;
	काष्ठा ast_vhub_port *p;

	अगर (port == 0 || port > vhub->max_ports)
		वापस std_req_stall;
	port--;
	p = &vhub->ports[port];

	चयन(feat) अणु
	हाल USB_PORT_FEAT_ENABLE:
		ast_vhub_change_port_stat(vhub, port,
					  USB_PORT_STAT_ENABLE |
					  USB_PORT_STAT_SUSPEND, 0,
					  false);
		ast_vhub_dev_suspend(&p->dev);
		वापस std_req_complete;
	हाल USB_PORT_FEAT_SUSPEND:
		अगर (!(p->status & USB_PORT_STAT_SUSPEND))
			वापस std_req_complete;
		ast_vhub_change_port_stat(vhub, port,
					  USB_PORT_STAT_SUSPEND, 0,
					  false);
		ast_vhub_dev_resume(&p->dev);
		वापस std_req_complete;
	हाल USB_PORT_FEAT_POWER:
		/* We करोn't करो घातer control */
		वापस std_req_complete;
	हाल USB_PORT_FEAT_INDICATOR:
		/* We करोn't have indicators */
		वापस std_req_complete;
	हाल USB_PORT_FEAT_C_CONNECTION:
	हाल USB_PORT_FEAT_C_ENABLE:
	हाल USB_PORT_FEAT_C_SUSPEND:
	हाल USB_PORT_FEAT_C_OVER_CURRENT:
	हाल USB_PORT_FEAT_C_RESET:
		/* Clear state-change feature */
		p->change &= ~(1u << (feat - 16));
		ast_vhub_update_hub_ep1(vhub, port);
		वापस std_req_complete;
	पूर्ण
	वापस std_req_stall;
पूर्ण

अटल क्रमागत std_req_rc ast_vhub_get_port_stat(काष्ठा ast_vhub_ep *ep,
					      u8 port)
अणु
	काष्ठा ast_vhub *vhub = ep->vhub;
	u16 stat, chg;

	अगर (port == 0 || port > vhub->max_ports)
		वापस std_req_stall;
	port--;

	stat = vhub->ports[port].status;
	chg = vhub->ports[port].change;

	/* We always have घातer */
	stat |= USB_PORT_STAT_POWER;

	EPDBG(ep, " port status=%04x change=%04x\n", stat, chg);

	वापस ast_vhub_simple_reply(ep,
				     stat & 0xff,
				     stat >> 8,
				     chg & 0xff,
				     chg >> 8);
पूर्ण

क्रमागत std_req_rc ast_vhub_class_hub_request(काष्ठा ast_vhub_ep *ep,
					   काष्ठा usb_ctrlrequest *crq)
अणु
	u16 wValue, wIndex, wLength;

	wValue = le16_to_cpu(crq->wValue);
	wIndex = le16_to_cpu(crq->wIndex);
	wLength = le16_to_cpu(crq->wLength);

	चयन ((crq->bRequestType << 8) | crq->bRequest) अणु
	हाल GetHubStatus:
		EPDBG(ep, "GetHubStatus\n");
		वापस ast_vhub_simple_reply(ep, 0, 0, 0, 0);
	हाल GetPortStatus:
		EPDBG(ep, "GetPortStatus(%d)\n", wIndex & 0xff);
		वापस ast_vhub_get_port_stat(ep, wIndex & 0xf);
	हाल GetHubDescriptor:
		अगर (wValue != (USB_DT_HUB << 8))
			वापस std_req_stall;
		EPDBG(ep, "GetHubDescriptor(%d)\n", wIndex & 0xff);
		वापस ast_vhub_rep_desc(ep, USB_DT_HUB, wLength);
	हाल SetHubFeature:
	हाल ClearHubFeature:
		EPDBG(ep, "Get/SetHubFeature(%d)\n", wValue);
		/* No feature, just complete the requests */
		अगर (wValue == C_HUB_LOCAL_POWER ||
		    wValue == C_HUB_OVER_CURRENT)
			वापस std_req_complete;
		वापस std_req_stall;
	हाल SetPortFeature:
		EPDBG(ep, "SetPortFeature(%d,%d)\n", wIndex & 0xf, wValue);
		वापस ast_vhub_set_port_feature(ep, wIndex & 0xf, wValue);
	हाल ClearPortFeature:
		EPDBG(ep, "ClearPortFeature(%d,%d)\n", wIndex & 0xf, wValue);
		वापस ast_vhub_clr_port_feature(ep, wIndex & 0xf, wValue);
	हाल ClearTTBuffer:
	हाल ResetTT:
	हाल StopTT:
		वापस std_req_complete;
	हाल GetTTState:
		वापस ast_vhub_simple_reply(ep, 0, 0, 0, 0);
	शेष:
		EPDBG(ep, "Unknown class request\n");
	पूर्ण
	वापस std_req_stall;
पूर्ण

व्योम ast_vhub_hub_suspend(काष्ठा ast_vhub *vhub)
अणु
	अचिन्हित पूर्णांक i;

	UDCDBG(vhub, "USB bus suspend\n");

	अगर (vhub->suspended)
		वापस;

	vhub->suspended = true;

	/*
	 * Forward to unsuspended ports without changing
	 * their connection status.
	 */
	क्रम (i = 0; i < vhub->max_ports; i++) अणु
		काष्ठा ast_vhub_port *p = &vhub->ports[i];

		अगर (!(p->status & USB_PORT_STAT_SUSPEND))
			ast_vhub_dev_suspend(&p->dev);
	पूर्ण
पूर्ण

व्योम ast_vhub_hub_resume(काष्ठा ast_vhub *vhub)
अणु
	अचिन्हित पूर्णांक i;

	UDCDBG(vhub, "USB bus resume\n");

	अगर (!vhub->suspended)
		वापस;

	vhub->suspended = false;

	/*
	 * Forward to unsuspended ports without changing
	 * their connection status.
	 */
	क्रम (i = 0; i < vhub->max_ports; i++) अणु
		काष्ठा ast_vhub_port *p = &vhub->ports[i];

		अगर (!(p->status & USB_PORT_STAT_SUSPEND))
			ast_vhub_dev_resume(&p->dev);
	पूर्ण
पूर्ण

व्योम ast_vhub_hub_reset(काष्ठा ast_vhub *vhub)
अणु
	अचिन्हित पूर्णांक i;

	UDCDBG(vhub, "USB bus reset\n");

	/*
	 * Is the speed known ? If not we करोn't care, we aren't
	 * initialized yet and ports haven't been enabled.
	 */
	अगर (vhub->speed == USB_SPEED_UNKNOWN)
		वापस;

	/* We aren't suspended anymore obviously */
	vhub->suspended = false;

	/* No speed set */
	vhub->speed = USB_SPEED_UNKNOWN;

	/* Wakeup not enabled anymore */
	vhub->wakeup_en = false;

	/*
	 * Clear all port status, disable gadमाला_लो and "suspend"
	 * them. They will be woken up by a port reset.
	 */
	क्रम (i = 0; i < vhub->max_ports; i++) अणु
		काष्ठा ast_vhub_port *p = &vhub->ports[i];

		/* Only keep the connected flag */
		p->status &= USB_PORT_STAT_CONNECTION;
		p->change = 0;

		/* Suspend the gadget अगर any */
		ast_vhub_dev_suspend(&p->dev);
	पूर्ण

	/* Cleanup HW */
	ग_लिखोl(0, vhub->regs + AST_VHUB_CONF);
	ग_लिखोl(0, vhub->regs + AST_VHUB_EP0_CTRL);
	ग_लिखोl(VHUB_EP1_CTRL_RESET_TOGGLE |
	       VHUB_EP1_CTRL_ENABLE,
	       vhub->regs + AST_VHUB_EP1_CTRL);
	ग_लिखोl(0, vhub->regs + AST_VHUB_EP1_STS_CHG);
पूर्ण

अटल व्योम ast_vhub_of_parse_dev_desc(काष्ठा ast_vhub *vhub,
				       स्थिर काष्ठा device_node *vhub_np)
अणु
	u16 id;
	u32 data;

	अगर (!of_property_पढ़ो_u32(vhub_np, "vhub-vendor-id", &data)) अणु
		id = (u16)data;
		vhub->vhub_dev_desc.idVenकरोr = cpu_to_le16(id);
	पूर्ण
	अगर (!of_property_पढ़ो_u32(vhub_np, "vhub-product-id", &data)) अणु
		id = (u16)data;
		vhub->vhub_dev_desc.idProduct = cpu_to_le16(id);
	पूर्ण
	अगर (!of_property_पढ़ो_u32(vhub_np, "vhub-device-revision", &data)) अणु
		id = (u16)data;
		vhub->vhub_dev_desc.bcdDevice = cpu_to_le16(id);
	पूर्ण
पूर्ण

अटल व्योम ast_vhub_fixup_usb1_dev_desc(काष्ठा ast_vhub *vhub)
अणु
	vhub->vhub_dev_desc.bcdUSB = cpu_to_le16(0x0100);
	vhub->vhub_dev_desc.bDeviceProtocol = 0;
पूर्ण

अटल काष्ठा usb_gadget_string_container*
ast_vhub_str_container_alloc(काष्ठा ast_vhub *vhub)
अणु
	अचिन्हित पूर्णांक size;
	काष्ठा usb_string *str_array;
	काष्ठा usb_gadget_strings *lang_str;
	काष्ठा usb_gadget_string_container *container;

	size = माप(*container);
	size += माप(काष्ठा usb_gadget_strings);
	size += माप(काष्ठा usb_string) * AST_VHUB_STR_INDEX_MAX;
	container = devm_kzalloc(&vhub->pdev->dev, size, GFP_KERNEL);
	अगर (!container)
		वापस ERR_PTR(-ENOMEM);

	lang_str = ast_vhub_str_of_container(container);
	str_array = (काष्ठा usb_string *)(lang_str + 1);
	lang_str->strings = str_array;
	वापस container;
पूर्ण

अटल व्योम ast_vhub_str_deep_copy(काष्ठा usb_gadget_strings *dest,
				   स्थिर काष्ठा usb_gadget_strings *src)
अणु
	काष्ठा usb_string *src_array = src->strings;
	काष्ठा usb_string *dest_array = dest->strings;

	dest->language = src->language;
	अगर (src_array && dest_array) अणु
		करो अणु
			*dest_array = *src_array;
			dest_array++;
			src_array++;
		पूर्ण जबतक (src_array->s);
	पूर्ण
पूर्ण

अटल पूर्णांक ast_vhub_str_alloc_add(काष्ठा ast_vhub *vhub,
				  स्थिर काष्ठा usb_gadget_strings *src_str)
अणु
	काष्ठा usb_gadget_strings *dest_str;
	काष्ठा usb_gadget_string_container *container;

	container = ast_vhub_str_container_alloc(vhub);
	अगर (IS_ERR(container))
		वापस PTR_ERR(container);

	dest_str = ast_vhub_str_of_container(container);
	ast_vhub_str_deep_copy(dest_str, src_str);
	list_add_tail(&container->list, &vhub->vhub_str_desc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	u8 id;
पूर्ण str_id_map[] = अणु
	अणु"manufacturer",	AST_VHUB_STR_MANUFपूर्ण,
	अणु"product",		AST_VHUB_STR_PRODUCTपूर्ण,
	अणु"serial-number",	AST_VHUB_STR_SERIALपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक ast_vhub_of_parse_str_desc(काष्ठा ast_vhub *vhub,
				      स्थिर काष्ठा device_node *desc_np)
अणु
	u32 langid;
	पूर्णांक ret = 0;
	पूर्णांक i, offset;
	स्थिर अक्षर *str;
	काष्ठा device_node *child;
	काष्ठा usb_string str_array[AST_VHUB_STR_INDEX_MAX];
	काष्ठा usb_gadget_strings lang_str = अणु
		.strings = (काष्ठा usb_string *)str_array,
	पूर्ण;

	क्रम_each_child_of_node(desc_np, child) अणु
		अगर (of_property_पढ़ो_u32(child, "reg", &langid))
			जारी; /* no language identअगरier specअगरied */

		अगर (!usb_validate_langid(langid))
			जारी; /* invalid language identअगरier */

		lang_str.language = langid;
		क्रम (i = offset = 0; str_id_map[i].name; i++) अणु
			str = of_get_property(child, str_id_map[i].name, शून्य);
			अगर (str) अणु
				str_array[offset].s = str;
				str_array[offset].id = str_id_map[i].id;
				offset++;
			पूर्ण
		पूर्ण
		str_array[offset].id = 0;
		str_array[offset].s = शून्य;

		ret = ast_vhub_str_alloc_add(vhub, &lang_str);
		अगर (ret) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ast_vhub_init_desc(काष्ठा ast_vhub *vhub)
अणु
	पूर्णांक ret;
	काष्ठा device_node *desc_np;
	स्थिर काष्ठा device_node *vhub_np = vhub->pdev->dev.of_node;

	/* Initialize vhub Device Descriptor. */
	स_नकल(&vhub->vhub_dev_desc, &ast_vhub_dev_desc,
		माप(vhub->vhub_dev_desc));
	ast_vhub_of_parse_dev_desc(vhub, vhub_np);
	अगर (vhub->क्रमce_usb1)
		ast_vhub_fixup_usb1_dev_desc(vhub);

	/* Initialize vhub Configuration Descriptor. */
	स_नकल(&vhub->vhub_conf_desc, &ast_vhub_conf_desc,
		माप(vhub->vhub_conf_desc));

	/* Initialize vhub Hub Descriptor. */
	स_नकल(&vhub->vhub_hub_desc, &ast_vhub_hub_desc,
		माप(vhub->vhub_hub_desc));
	vhub->vhub_hub_desc.bNbrPorts = vhub->max_ports;

	/* Initialize vhub String Descriptors. */
	INIT_LIST_HEAD(&vhub->vhub_str_desc);
	desc_np = of_get_child_by_name(vhub_np, "vhub-strings");
	अगर (desc_np)
		ret = ast_vhub_of_parse_str_desc(vhub, desc_np);
	अन्यथा
		ret = ast_vhub_str_alloc_add(vhub, &ast_vhub_strings);

	वापस ret;
पूर्ण

पूर्णांक ast_vhub_init_hub(काष्ठा ast_vhub *vhub)
अणु
	vhub->speed = USB_SPEED_UNKNOWN;
	INIT_WORK(&vhub->wake_work, ast_vhub_wake_work);

	वापस ast_vhub_init_desc(vhub);
पूर्ण
