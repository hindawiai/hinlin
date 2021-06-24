<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * c67x00-hcd.c: Cypress C67X00 USB Host Controller Driver
 *
 * Copyright (C) 2006-2008 Barco N.V.
 *    Derived from the Cypress cy7c67200/300 ezusb linux driver and
 *    based on multiple host controller drivers inside the linux kernel.
 */

#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>

#समावेश "c67x00.h"
#समावेश "c67x00-hcd.h"

/* --------------------------------------------------------------------------
 * Root Hub Support
 */

अटल __u8 c67x00_hub_des[] = अणु
	0x09,			/*  __u8  bLength; */
	USB_DT_HUB,		/*  __u8  bDescriptorType; Hub-descriptor */
	0x02,			/*  __u8  bNbrPorts; */
	0x00,			/* __u16  wHubCharacteristics; */
	0x00,			/*   (per-port OC, no घातer चयनing) */
	0x32,			/*  __u8  bPwrOn2pwrGood; 2ms */
	0x00,			/*  __u8  bHubContrCurrent; 0 mA */
	0x00,			/*  __u8  DeviceRemovable; ** 7 Ports max ** */
	0xff,			/*  __u8  PortPwrCtrlMask; ** 7 ports max ** */
पूर्ण;

अटल व्योम c67x00_hub_reset_host_port(काष्ठा c67x00_sie *sie, पूर्णांक port)
अणु
	काष्ठा c67x00_hcd *c67x00 = sie->निजी_data;
	अचिन्हित दीर्घ flags;

	c67x00_ll_husb_reset(sie, port);

	spin_lock_irqsave(&c67x00->lock, flags);
	c67x00_ll_husb_reset_port(sie, port);
	spin_unlock_irqrestore(&c67x00->lock, flags);

	c67x00_ll_set_husb_eot(sie->dev, DEFAULT_EOT);
पूर्ण

अटल पूर्णांक c67x00_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	काष्ठा c67x00_sie *sie = c67x00->sie;
	u16 status;
	पूर्णांक i;

	*buf = 0;
	status = c67x00_ll_usb_get_status(sie);
	क्रम (i = 0; i < C67X00_PORTS; i++)
		अगर (status & PORT_CONNECT_CHANGE(i))
			*buf |= (1 << i);

	/* bit 0 denotes hub change, b1..n port change */
	*buf <<= 1;

	वापस !!*buf;
पूर्ण

अटल पूर्णांक c67x00_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
			      u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	काष्ठा c67x00_sie *sie = c67x00->sie;
	u16 status, usb_status;
	पूर्णांक len = 0;
	अचिन्हित पूर्णांक port = wIndex-1;
	u16 wPortChange, wPortStatus;

	चयन (typeReq) अणु

	हाल GetHubStatus:
		*(__le32 *) buf = cpu_to_le32(0);
		len = 4;		/* hub घातer */
		अवरोध;

	हाल GetPortStatus:
		अगर (wIndex > C67X00_PORTS)
			वापस -EPIPE;

		status = c67x00_ll_usb_get_status(sie);
		usb_status = c67x00_ll_get_usb_ctl(sie);

		wPortChange = 0;
		अगर (status & PORT_CONNECT_CHANGE(port))
			wPortChange |= USB_PORT_STAT_C_CONNECTION;

		wPortStatus = USB_PORT_STAT_POWER;
		अगर (!(status & PORT_SE0_STATUS(port)))
			wPortStatus |= USB_PORT_STAT_CONNECTION;
		अगर (usb_status & LOW_SPEED_PORT(port)) अणु
			wPortStatus |= USB_PORT_STAT_LOW_SPEED;
			c67x00->low_speed_ports |= (1 << port);
		पूर्ण अन्यथा
			c67x00->low_speed_ports &= ~(1 << port);

		अगर (usb_status & SOF_EOP_EN(port))
			wPortStatus |= USB_PORT_STAT_ENABLE;

		*(__le16 *) buf = cpu_to_le16(wPortStatus);
		*(__le16 *) (buf + 2) = cpu_to_le16(wPortChange);
		len = 4;
		अवरोध;

	हाल SetHubFeature:	/* We करोn't implement these */
	हाल ClearHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
		हाल C_HUB_LOCAL_POWER:
			len = 0;
			अवरोध;

		शेष:
			वापस -EPIPE;
		पूर्ण
		अवरोध;

	हाल SetPortFeature:
		अगर (wIndex > C67X00_PORTS)
			वापस -EPIPE;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"SetPortFeature %d (SUSPEND)\n", port);
			len = 0;
			अवरोध;

		हाल USB_PORT_FEAT_RESET:
			c67x00_hub_reset_host_port(sie, port);
			len = 0;
			अवरोध;

		हाल USB_PORT_FEAT_POWER:
			/* Power always enabled */
			len = 0;
			अवरोध;

		शेष:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"%s: SetPortFeature %d (0x%04x) Error!\n",
				__func__, port, wValue);
			वापस -EPIPE;
		पूर्ण
		अवरोध;

	हाल ClearPortFeature:
		अगर (wIndex > C67X00_PORTS)
			वापस -EPIPE;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			/* Reset the port so that the c67x00 also notices the
			 * disconnect */
			c67x00_hub_reset_host_port(sie, port);
			len = 0;
			अवरोध;

		हाल USB_PORT_FEAT_C_ENABLE:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"ClearPortFeature (%d): C_ENABLE\n", port);
			len = 0;
			अवरोध;

		हाल USB_PORT_FEAT_SUSPEND:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"ClearPortFeature (%d): SUSPEND\n", port);
			len = 0;
			अवरोध;

		हाल USB_PORT_FEAT_C_SUSPEND:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"ClearPortFeature (%d): C_SUSPEND\n", port);
			len = 0;
			अवरोध;

		हाल USB_PORT_FEAT_POWER:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"ClearPortFeature (%d): POWER\n", port);
			वापस -EPIPE;

		हाल USB_PORT_FEAT_C_CONNECTION:
			c67x00_ll_usb_clear_status(sie,
						   PORT_CONNECT_CHANGE(port));
			len = 0;
			अवरोध;

		हाल USB_PORT_FEAT_C_OVER_CURRENT:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"ClearPortFeature (%d): OVER_CURRENT\n", port);
			len = 0;
			अवरोध;

		हाल USB_PORT_FEAT_C_RESET:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"ClearPortFeature (%d): C_RESET\n", port);
			len = 0;
			अवरोध;

		शेष:
			dev_dbg(c67x00_hcd_dev(c67x00),
				"%s: ClearPortFeature %d (0x%04x) Error!\n",
				__func__, port, wValue);
			वापस -EPIPE;
		पूर्ण
		अवरोध;

	हाल GetHubDescriptor:
		len = min_t(अचिन्हित पूर्णांक, माप(c67x00_hub_des), wLength);
		स_नकल(buf, c67x00_hub_des, len);
		अवरोध;

	शेष:
		dev_dbg(c67x00_hcd_dev(c67x00), "%s: unknown\n", __func__);
		वापस -EPIPE;
	पूर्ण

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------
 * Main part of host controller driver
 */

/*
 * c67x00_hcd_irq
 *
 * This function is called from the पूर्णांकerrupt handler in c67x00-drv.c
 */
अटल व्योम c67x00_hcd_irq(काष्ठा c67x00_sie *sie, u16 पूर्णांक_status, u16 msg)
अणु
	काष्ठा c67x00_hcd *c67x00 = sie->निजी_data;
	काष्ठा usb_hcd *hcd = c67x00_hcd_to_hcd(c67x00);

	/* Handle sie message flags */
	अगर (msg) अणु
		अगर (msg & HUSB_TDListDone)
			c67x00_sched_kick(c67x00);
		अन्यथा
			dev_warn(c67x00_hcd_dev(c67x00),
				 "Unknown SIE msg flag(s): 0x%04x\n", msg);
	पूर्ण

	अगर (unlikely(hcd->state == HC_STATE_HALT))
		वापस;

	अगर (!HCD_HW_ACCESSIBLE(hcd))
		वापस;

	/* Handle Start of frame events */
	अगर (पूर्णांक_status & SOFEOP_FLG(sie->sie_num)) अणु
		c67x00_ll_usb_clear_status(sie, SOF_EOP_IRQ_FLG);
		c67x00_sched_kick(c67x00);
	पूर्ण
पूर्ण

/*
 * c67x00_hcd_start: Host controller start hook
 */
अटल पूर्णांक c67x00_hcd_start(काष्ठा usb_hcd *hcd)
अणु
	hcd->uses_new_polling = 1;
	hcd->state = HC_STATE_RUNNING;
	set_bit(HCD_FLAG_POLL_RH, &hcd->flags);

	वापस 0;
पूर्ण

/*
 * c67x00_hcd_stop: Host controller stop hook
 */
अटल व्योम c67x00_hcd_stop(काष्ठा usb_hcd *hcd)
अणु
	/* Nothing to करो */
पूर्ण

अटल पूर्णांक c67x00_hcd_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	u16 temp_val;

	dev_dbg(c67x00_hcd_dev(c67x00), "%s\n", __func__);
	temp_val = c67x00_ll_husb_get_frame(c67x00->sie);
	temp_val &= HOST_FRAME_MASK;
	वापस temp_val ? (temp_val - 1) : HOST_FRAME_MASK;
पूर्ण

अटल स्थिर काष्ठा hc_driver c67x00_hc_driver = अणु
	.description	= "c67x00-hcd",
	.product_desc	= "Cypress C67X00 Host Controller",
	.hcd_priv_size	= माप(काष्ठा c67x00_hcd),
	.flags		= HCD_USB11 | HCD_MEMORY,

	/*
	 * basic lअगरecycle operations
	 */
	.start		= c67x00_hcd_start,
	.stop		= c67x00_hcd_stop,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue	= c67x00_urb_enqueue,
	.urb_dequeue	= c67x00_urb_dequeue,
	.endpoपूर्णांक_disable = c67x00_endpoपूर्णांक_disable,

	/*
	 * scheduling support
	 */
	.get_frame_number = c67x00_hcd_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data = c67x00_hub_status_data,
	.hub_control	= c67x00_hub_control,
पूर्ण;

/* ---------------------------------------------------------------------
 * Setup/Tearकरोwn routines
 */

पूर्णांक c67x00_hcd_probe(काष्ठा c67x00_sie *sie)
अणु
	काष्ठा c67x00_hcd *c67x00;
	काष्ठा usb_hcd *hcd;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (usb_disabled())
		वापस -ENODEV;

	hcd = usb_create_hcd(&c67x00_hc_driver, sie_dev(sie), "c67x00_sie");
	अगर (!hcd) अणु
		retval = -ENOMEM;
		जाओ err0;
	पूर्ण
	c67x00 = hcd_to_c67x00_hcd(hcd);

	spin_lock_init(&c67x00->lock);
	c67x00->sie = sie;

	INIT_LIST_HEAD(&c67x00->list[PIPE_ISOCHRONOUS]);
	INIT_LIST_HEAD(&c67x00->list[PIPE_INTERRUPT]);
	INIT_LIST_HEAD(&c67x00->list[PIPE_CONTROL]);
	INIT_LIST_HEAD(&c67x00->list[PIPE_BULK]);
	c67x00->urb_count = 0;
	INIT_LIST_HEAD(&c67x00->td_list);
	c67x00->td_base_addr = CY_HCD_BUF_ADDR + SIE_TD_OFFSET(sie->sie_num);
	c67x00->buf_base_addr = CY_HCD_BUF_ADDR + SIE_BUF_OFFSET(sie->sie_num);
	c67x00->max_frame_bw = MAX_FRAME_BW_STD;

	c67x00_ll_husb_init_host_port(sie);

	init_completion(&c67x00->endpoपूर्णांक_disable);
	retval = c67x00_sched_start_scheduler(c67x00);
	अगर (retval)
		जाओ err1;

	retval = usb_add_hcd(hcd, 0, 0);
	अगर (retval) अणु
		dev_dbg(sie_dev(sie), "%s: usb_add_hcd returned %d\n",
			__func__, retval);
		जाओ err2;
	पूर्ण

	device_wakeup_enable(hcd->self.controller);

	spin_lock_irqsave(&sie->lock, flags);
	sie->निजी_data = c67x00;
	sie->irq = c67x00_hcd_irq;
	spin_unlock_irqrestore(&sie->lock, flags);

	वापस retval;

 err2:
	c67x00_sched_stop_scheduler(c67x00);
 err1:
	usb_put_hcd(hcd);
 err0:
	वापस retval;
पूर्ण

/* may be called with controller, bus, and devices active */
व्योम c67x00_hcd_हटाओ(काष्ठा c67x00_sie *sie)
अणु
	काष्ठा c67x00_hcd *c67x00 = sie->निजी_data;
	काष्ठा usb_hcd *hcd = c67x00_hcd_to_hcd(c67x00);

	c67x00_sched_stop_scheduler(c67x00);
	usb_हटाओ_hcd(hcd);
	usb_put_hcd(hcd);
पूर्ण
