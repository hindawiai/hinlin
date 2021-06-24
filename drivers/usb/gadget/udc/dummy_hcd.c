<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * dummy_hcd.c -- Dummy/Loopback USB host and device emulator driver.
 *
 * Maपूर्णांकainer: Alan Stern <stern@rowland.harvard.edu>
 *
 * Copyright (C) 2003 David Brownell
 * Copyright (C) 2003-2005 Alan Stern
 */


/*
 * This exposes a device side "USB gadget" API, driven by requests to a
 * Linux-USB host controller driver.  USB traffic is simulated; there's
 * no need क्रम USB hardware.  Use this with two other drivers:
 *
 *  - Gadget driver, responding to requests (device);
 *  - Host-side device driver, as alपढ़ोy familiar in Linux.
 *
 * Having this all in one kernel can help some stages of development,
 * bypassing some hardware (and driver) issues.  UML could help too.
 *
 * Note: The emulation करोes not include isochronous transfers!
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा DRIVER_DESC	"USB Host+Gadget Emulator"
#घोषणा DRIVER_VERSION	"02 May 2005"

#घोषणा POWER_BUDGET	500	/* in mA; use 8 क्रम low-घातer port testing */
#घोषणा POWER_BUDGET_3	900	/* in mA */

अटल स्थिर अक्षर	driver_name[] = "dummy_hcd";
अटल स्थिर अक्षर	driver_desc[] = "USB Host+Gadget Emulator";

अटल स्थिर अक्षर	gadget_name[] = "dummy_udc";

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("David Brownell");
MODULE_LICENSE("GPL");

काष्ठा dummy_hcd_module_parameters अणु
	bool is_super_speed;
	bool is_high_speed;
	अचिन्हित पूर्णांक num;
पूर्ण;

अटल काष्ठा dummy_hcd_module_parameters mod_data = अणु
	.is_super_speed = false,
	.is_high_speed = true,
	.num = 1,
पूर्ण;
module_param_named(is_super_speed, mod_data.is_super_speed, bool, S_IRUGO);
MODULE_PARM_DESC(is_super_speed, "true to simulate SuperSpeed connection");
module_param_named(is_high_speed, mod_data.is_high_speed, bool, S_IRUGO);
MODULE_PARM_DESC(is_high_speed, "true to simulate HighSpeed connection");
module_param_named(num, mod_data.num, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(num, "number of emulated controllers");
/*-------------------------------------------------------------------------*/

/* gadget side driver data काष्ठाres */
काष्ठा dummy_ep अणु
	काष्ठा list_head		queue;
	अचिन्हित दीर्घ			last_io;	/* jअगरfies बारtamp */
	काष्ठा usb_gadget		*gadget;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	काष्ठा usb_ep			ep;
	अचिन्हित			halted:1;
	अचिन्हित			wedged:1;
	अचिन्हित			alपढ़ोy_seen:1;
	अचिन्हित			setup_stage:1;
	अचिन्हित			stream_en:1;
पूर्ण;

काष्ठा dummy_request अणु
	काष्ठा list_head		queue;		/* ep's requests */
	काष्ठा usb_request		req;
पूर्ण;

अटल अंतरभूत काष्ठा dummy_ep *usb_ep_to_dummy_ep(काष्ठा usb_ep *_ep)
अणु
	वापस container_of(_ep, काष्ठा dummy_ep, ep);
पूर्ण

अटल अंतरभूत काष्ठा dummy_request *usb_request_to_dummy_request
		(काष्ठा usb_request *_req)
अणु
	वापस container_of(_req, काष्ठा dummy_request, req);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Every device has ep0 क्रम control requests, plus up to 30 more endpoपूर्णांकs,
 * in one of two types:
 *
 *   - Configurable:  direction (in/out), type (bulk, iso, etc), and endpoपूर्णांक
 *     number can be changed.  Names like "ep-a" are used क्रम this type.
 *
 *   - Fixed Function:  in other हालs.  some अक्षरacteristics may be mutable;
 *     that'd be hardware-specअगरic.  Names like "ep12out-bulk" are used.
 *
 * Gadget drivers are responsible क्रम not setting up conflicting endpoपूर्णांक
 * configurations, illegal or unsupported packet lengths, and so on.
 */

अटल स्थिर अक्षर ep0name[] = "ep0";

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा usb_ep_caps caps;
पूर्ण ep_info[] = अणु
#घोषणा EP_INFO(_name, _caps) \
	अणु \
		.name = _name, \
		.caps = _caps, \
	पूर्ण

/* we करोn't provide isochronous endpoints since we don't support them */
#घोषणा TYPE_BULK_OR_INT	(USB_EP_CAPS_TYPE_BULK | USB_EP_CAPS_TYPE_INT)

	/* everyone has ep0 */
	EP_INFO(ep0name,
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL, USB_EP_CAPS_सूची_ALL)),
	/* act like a pxa250: fअगरteen fixed function endpoपूर्णांकs */
	EP_INFO("ep1in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep2out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
/*
	EP_INFO("ep3in-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep4out-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_OUT)),
*/
	EP_INFO("ep5in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep6in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep7out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
/*
	EP_INFO("ep8in-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep9out-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_OUT)),
*/
	EP_INFO("ep10in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep11in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep12out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
/*
	EP_INFO("ep13in-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep14out-iso",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ISO, USB_EP_CAPS_सूची_OUT)),
*/
	EP_INFO("ep15in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_सूची_IN)),

	/* or like sa1100: two fixed function endpoपूर्णांकs */
	EP_INFO("ep1out-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep2in-bulk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BULK, USB_EP_CAPS_सूची_IN)),

	/* and now some generic EPs so we have enough in multi config */
	EP_INFO("ep-aout",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep-bin",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep-cout",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep-dout",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep-ein",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep-fout",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep-gin",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep-hout",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep-iout",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep-jin",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep-kout",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_OUT)),
	EP_INFO("ep-lin",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_IN)),
	EP_INFO("ep-mout",
		USB_EP_CAPS(TYPE_BULK_OR_INT, USB_EP_CAPS_सूची_OUT)),

#अघोषित EP_INFO
पूर्ण;

#घोषणा DUMMY_ENDPOINTS	ARRAY_SIZE(ep_info)

/*-------------------------------------------------------------------------*/

#घोषणा FIFO_SIZE		64

काष्ठा urbp अणु
	काष्ठा urb		*urb;
	काष्ठा list_head	urbp_list;
	काष्ठा sg_mapping_iter	miter;
	u32			miter_started;
पूर्ण;


क्रमागत dummy_rh_state अणु
	DUMMY_RH_RESET,
	DUMMY_RH_SUSPENDED,
	DUMMY_RH_RUNNING
पूर्ण;

काष्ठा dummy_hcd अणु
	काष्ठा dummy			*dum;
	क्रमागत dummy_rh_state		rh_state;
	काष्ठा समयr_list		समयr;
	u32				port_status;
	u32				old_status;
	अचिन्हित दीर्घ			re_समयout;

	काष्ठा usb_device		*udev;
	काष्ठा list_head		urbp_list;
	काष्ठा urbp			*next_frame_urbp;

	u32				stream_en_ep;
	u8				num_stream[30 / 2];

	अचिन्हित			active:1;
	अचिन्हित			old_active:1;
	अचिन्हित			resuming:1;
पूर्ण;

काष्ठा dummy अणु
	spinlock_t			lock;

	/*
	 * DEVICE/GADGET side support
	 */
	काष्ठा dummy_ep			ep[DUMMY_ENDPOINTS];
	पूर्णांक				address;
	पूर्णांक				callback_usage;
	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;
	काष्ठा dummy_request		fअगरo_req;
	u8				fअगरo_buf[FIFO_SIZE];
	u16				devstatus;
	अचिन्हित			पूर्णांकs_enabled:1;
	अचिन्हित			udc_suspended:1;
	अचिन्हित			pullup:1;

	/*
	 * HOST side support
	 */
	काष्ठा dummy_hcd		*hs_hcd;
	काष्ठा dummy_hcd		*ss_hcd;
पूर्ण;

अटल अंतरभूत काष्ठा dummy_hcd *hcd_to_dummy_hcd(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा dummy_hcd *) (hcd->hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *dummy_hcd_to_hcd(काष्ठा dummy_hcd *dum)
अणु
	वापस container_of((व्योम *) dum, काष्ठा usb_hcd, hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा device *dummy_dev(काष्ठा dummy_hcd *dum)
अणु
	वापस dummy_hcd_to_hcd(dum)->self.controller;
पूर्ण

अटल अंतरभूत काष्ठा device *udc_dev(काष्ठा dummy *dum)
अणु
	वापस dum->gadget.dev.parent;
पूर्ण

अटल अंतरभूत काष्ठा dummy *ep_to_dummy(काष्ठा dummy_ep *ep)
अणु
	वापस container_of(ep->gadget, काष्ठा dummy, gadget);
पूर्ण

अटल अंतरभूत काष्ठा dummy_hcd *gadget_to_dummy_hcd(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा dummy *dum = container_of(gadget, काष्ठा dummy, gadget);
	अगर (dum->gadget.speed == USB_SPEED_SUPER)
		वापस dum->ss_hcd;
	अन्यथा
		वापस dum->hs_hcd;
पूर्ण

अटल अंतरभूत काष्ठा dummy *gadget_dev_to_dummy(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा dummy, gadget.dev);
पूर्ण

/*-------------------------------------------------------------------------*/

/* DEVICE/GADGET SIDE UTILITY ROUTINES */

/* called with spinlock held */
अटल व्योम nuke(काष्ठा dummy *dum, काष्ठा dummy_ep *ep)
अणु
	जबतक (!list_empty(&ep->queue)) अणु
		काष्ठा dummy_request	*req;

		req = list_entry(ep->queue.next, काष्ठा dummy_request, queue);
		list_del_init(&req->queue);
		req->req.status = -ESHUTDOWN;

		spin_unlock(&dum->lock);
		usb_gadget_giveback_request(&ep->ep, &req->req);
		spin_lock(&dum->lock);
	पूर्ण
पूर्ण

/* caller must hold lock */
अटल व्योम stop_activity(काष्ठा dummy *dum)
अणु
	पूर्णांक i;

	/* prevent any more requests */
	dum->address = 0;

	/* The समयr is left running so that outstanding URBs can fail */

	/* nuke any pending requests first, so driver i/o is quiesced */
	क्रम (i = 0; i < DUMMY_ENDPOINTS; ++i)
		nuke(dum, &dum->ep[i]);

	/* driver now करोes any non-usb quiescing necessary */
पूर्ण

/**
 * set_link_state_by_speed() - Sets the current state of the link according to
 *	the hcd speed
 * @dum_hcd: poपूर्णांकer to the dummy_hcd काष्ठाure to update the link state क्रम
 *
 * This function updates the port_status according to the link state and the
 * speed of the hcd.
 */
अटल व्योम set_link_state_by_speed(काष्ठा dummy_hcd *dum_hcd)
अणु
	काष्ठा dummy *dum = dum_hcd->dum;

	अगर (dummy_hcd_to_hcd(dum_hcd)->speed == HCD_USB3) अणु
		अगर ((dum_hcd->port_status & USB_SS_PORT_STAT_POWER) == 0) अणु
			dum_hcd->port_status = 0;
		पूर्ण अन्यथा अगर (!dum->pullup || dum->udc_suspended) अणु
			/* UDC suspend must cause a disconnect */
			dum_hcd->port_status &= ~(USB_PORT_STAT_CONNECTION |
						USB_PORT_STAT_ENABLE);
			अगर ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) != 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
		पूर्ण अन्यथा अणु
			/* device is connected and not suspended */
			dum_hcd->port_status |= (USB_PORT_STAT_CONNECTION |
						 USB_PORT_STAT_SPEED_5GBPS) ;
			अगर ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) == 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
			अगर ((dum_hcd->port_status & USB_PORT_STAT_ENABLE) &&
			    (dum_hcd->port_status &
			     USB_PORT_STAT_LINK_STATE) == USB_SS_PORT_LS_U0 &&
			    dum_hcd->rh_state != DUMMY_RH_SUSPENDED)
				dum_hcd->active = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((dum_hcd->port_status & USB_PORT_STAT_POWER) == 0) अणु
			dum_hcd->port_status = 0;
		पूर्ण अन्यथा अगर (!dum->pullup || dum->udc_suspended) अणु
			/* UDC suspend must cause a disconnect */
			dum_hcd->port_status &= ~(USB_PORT_STAT_CONNECTION |
						USB_PORT_STAT_ENABLE |
						USB_PORT_STAT_LOW_SPEED |
						USB_PORT_STAT_HIGH_SPEED |
						USB_PORT_STAT_SUSPEND);
			अगर ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) != 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
		पूर्ण अन्यथा अणु
			dum_hcd->port_status |= USB_PORT_STAT_CONNECTION;
			अगर ((dum_hcd->old_status &
			     USB_PORT_STAT_CONNECTION) == 0)
				dum_hcd->port_status |=
					(USB_PORT_STAT_C_CONNECTION << 16);
			अगर ((dum_hcd->port_status & USB_PORT_STAT_ENABLE) == 0)
				dum_hcd->port_status &= ~USB_PORT_STAT_SUSPEND;
			अन्यथा अगर ((dum_hcd->port_status &
				  USB_PORT_STAT_SUSPEND) == 0 &&
					dum_hcd->rh_state != DUMMY_RH_SUSPENDED)
				dum_hcd->active = 1;
		पूर्ण
	पूर्ण
पूर्ण

/* caller must hold lock */
अटल व्योम set_link_state(काष्ठा dummy_hcd *dum_hcd)
	__must_hold(&dum->lock)
अणु
	काष्ठा dummy *dum = dum_hcd->dum;
	अचिन्हित पूर्णांक घातer_bit;

	dum_hcd->active = 0;
	अगर (dum->pullup)
		अगर ((dummy_hcd_to_hcd(dum_hcd)->speed == HCD_USB3 &&
		     dum->gadget.speed != USB_SPEED_SUPER) ||
		    (dummy_hcd_to_hcd(dum_hcd)->speed != HCD_USB3 &&
		     dum->gadget.speed == USB_SPEED_SUPER))
			वापस;

	set_link_state_by_speed(dum_hcd);
	घातer_bit = (dummy_hcd_to_hcd(dum_hcd)->speed == HCD_USB3 ?
			USB_SS_PORT_STAT_POWER : USB_PORT_STAT_POWER);

	अगर ((dum_hcd->port_status & USB_PORT_STAT_ENABLE) == 0 ||
	     dum_hcd->active)
		dum_hcd->resuming = 0;

	/* Currently !connected or in reset */
	अगर ((dum_hcd->port_status & घातer_bit) == 0 ||
			(dum_hcd->port_status & USB_PORT_STAT_RESET) != 0) अणु
		अचिन्हित पूर्णांक disconnect = घातer_bit &
				dum_hcd->old_status & (~dum_hcd->port_status);
		अचिन्हित पूर्णांक reset = USB_PORT_STAT_RESET &
				(~dum_hcd->old_status) & dum_hcd->port_status;

		/* Report reset and disconnect events to the driver */
		अगर (dum->पूर्णांकs_enabled && (disconnect || reset)) अणु
			stop_activity(dum);
			++dum->callback_usage;
			spin_unlock(&dum->lock);
			अगर (reset)
				usb_gadget_udc_reset(&dum->gadget, dum->driver);
			अन्यथा
				dum->driver->disconnect(&dum->gadget);
			spin_lock(&dum->lock);
			--dum->callback_usage;
		पूर्ण
	पूर्ण अन्यथा अगर (dum_hcd->active != dum_hcd->old_active &&
			dum->पूर्णांकs_enabled) अणु
		++dum->callback_usage;
		spin_unlock(&dum->lock);
		अगर (dum_hcd->old_active && dum->driver->suspend)
			dum->driver->suspend(&dum->gadget);
		अन्यथा अगर (!dum_hcd->old_active &&  dum->driver->resume)
			dum->driver->resume(&dum->gadget);
		spin_lock(&dum->lock);
		--dum->callback_usage;
	पूर्ण

	dum_hcd->old_status = dum_hcd->port_status;
	dum_hcd->old_active = dum_hcd->active;
पूर्ण

/*-------------------------------------------------------------------------*/

/* DEVICE/GADGET SIDE DRIVER
 *
 * This only tracks gadget state.  All the work is करोne when the host
 * side tries some (emulated) i/o operation.  Real device controller
 * drivers would करो real i/o using dma, fअगरos, irqs, समयrs, etc.
 */

#घोषणा is_enabled(dum) \
	(dum->port_status & USB_PORT_STAT_ENABLE)

अटल पूर्णांक dummy_enable(काष्ठा usb_ep *_ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा dummy		*dum;
	काष्ठा dummy_hcd	*dum_hcd;
	काष्ठा dummy_ep		*ep;
	अचिन्हित		max;
	पूर्णांक			retval;

	ep = usb_ep_to_dummy_ep(_ep);
	अगर (!_ep || !desc || ep->desc || _ep->name == ep0name
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		वापस -EINVAL;
	dum = ep_to_dummy(ep);
	अगर (!dum->driver)
		वापस -ESHUTDOWN;

	dum_hcd = gadget_to_dummy_hcd(&dum->gadget);
	अगर (!is_enabled(dum_hcd))
		वापस -ESHUTDOWN;

	/*
	 * For HS/FS devices only bits 0..10 of the wMaxPacketSize represent the
	 * maximum packet size.
	 * For SS devices the wMaxPacketSize is limited by 1024.
	 */
	max = usb_endpoपूर्णांक_maxp(desc);

	/* drivers must not request bad settings, since lower levels
	 * (hardware or its drivers) may not check.  some endpoपूर्णांकs
	 * can't करो iso, many have maxpacket limitations, etc.
	 *
	 * since this "hardware" driver is here to help debugging, we
	 * have some extra sanity checks.  (there could be more though,
	 * especially क्रम "ep9out" style fixed function ones.)
	 */
	retval = -EINVAL;
	चयन (usb_endpoपूर्णांक_type(desc)) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (म_माला(ep->ep.name, "-iso")
				|| म_माला(ep->ep.name, "-int")) अणु
			जाओ करोne;
		पूर्ण
		चयन (dum->gadget.speed) अणु
		हाल USB_SPEED_SUPER:
			अगर (max == 1024)
				अवरोध;
			जाओ करोne;
		हाल USB_SPEED_HIGH:
			अगर (max == 512)
				अवरोध;
			जाओ करोne;
		हाल USB_SPEED_FULL:
			अगर (max == 8 || max == 16 || max == 32 || max == 64)
				/* we'll fake any legal size */
				अवरोध;
			/* save a वापस statement */
			fallthrough;
		शेष:
			जाओ करोne;
		पूर्ण
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		अगर (म_माला(ep->ep.name, "-iso")) /* bulk is ok */
			जाओ करोne;
		/* real hardware might not handle all packet sizes */
		चयन (dum->gadget.speed) अणु
		हाल USB_SPEED_SUPER:
		हाल USB_SPEED_HIGH:
			अगर (max <= 1024)
				अवरोध;
			/* save a वापस statement */
			fallthrough;
		हाल USB_SPEED_FULL:
			अगर (max <= 64)
				अवरोध;
			/* save a वापस statement */
			fallthrough;
		शेष:
			अगर (max <= 8)
				अवरोध;
			जाओ करोne;
		पूर्ण
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (म_माला(ep->ep.name, "-bulk")
				|| म_माला(ep->ep.name, "-int"))
			जाओ करोne;
		/* real hardware might not handle all packet sizes */
		चयन (dum->gadget.speed) अणु
		हाल USB_SPEED_SUPER:
		हाल USB_SPEED_HIGH:
			अगर (max <= 1024)
				अवरोध;
			/* save a वापस statement */
			fallthrough;
		हाल USB_SPEED_FULL:
			अगर (max <= 1023)
				अवरोध;
			/* save a वापस statement */
			fallthrough;
		शेष:
			जाओ करोne;
		पूर्ण
		अवरोध;
	शेष:
		/* few chips support control except on ep0 */
		जाओ करोne;
	पूर्ण

	_ep->maxpacket = max;
	अगर (usb_ss_max_streams(_ep->comp_desc)) अणु
		अगर (!usb_endpoपूर्णांक_xfer_bulk(desc)) अणु
			dev_err(udc_dev(dum), "Can't enable stream support on "
					"non-bulk ep %s\n", _ep->name);
			वापस -EINVAL;
		पूर्ण
		ep->stream_en = 1;
	पूर्ण
	ep->desc = desc;

	dev_dbg(udc_dev(dum), "enabled %s (ep%d%s-%s) maxpacket %d stream %s\n",
		_ep->name,
		desc->bEndpoपूर्णांकAddress & 0x0f,
		(desc->bEndpoपूर्णांकAddress & USB_सूची_IN) ? "in" : "out",
		usb_ep_type_string(usb_endpoपूर्णांक_type(desc)),
		max, ep->stream_en ? "enabled" : "disabled");

	/* at this poपूर्णांक real hardware should be NAKing transfers
	 * to that endpoपूर्णांक, until a buffer is queued to it.
	 */
	ep->halted = ep->wedged = 0;
	retval = 0;
करोne:
	वापस retval;
पूर्ण

अटल पूर्णांक dummy_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा dummy_ep		*ep;
	काष्ठा dummy		*dum;
	अचिन्हित दीर्घ		flags;

	ep = usb_ep_to_dummy_ep(_ep);
	अगर (!_ep || !ep->desc || _ep->name == ep0name)
		वापस -EINVAL;
	dum = ep_to_dummy(ep);

	spin_lock_irqsave(&dum->lock, flags);
	ep->desc = शून्य;
	ep->stream_en = 0;
	nuke(dum, ep);
	spin_unlock_irqrestore(&dum->lock, flags);

	dev_dbg(udc_dev(dum), "disabled %s\n", _ep->name);
	वापस 0;
पूर्ण

अटल काष्ठा usb_request *dummy_alloc_request(काष्ठा usb_ep *_ep,
		gfp_t mem_flags)
अणु
	काष्ठा dummy_request	*req;

	अगर (!_ep)
		वापस शून्य;

	req = kzalloc(माप(*req), mem_flags);
	अगर (!req)
		वापस शून्य;
	INIT_LIST_HEAD(&req->queue);
	वापस &req->req;
पूर्ण

अटल व्योम dummy_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा dummy_request	*req;

	अगर (!_ep || !_req) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	req = usb_request_to_dummy_request(_req);
	WARN_ON(!list_empty(&req->queue));
	kमुक्त(req);
पूर्ण

अटल व्योम fअगरo_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
पूर्ण

अटल पूर्णांक dummy_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
		gfp_t mem_flags)
अणु
	काष्ठा dummy_ep		*ep;
	काष्ठा dummy_request	*req;
	काष्ठा dummy		*dum;
	काष्ठा dummy_hcd	*dum_hcd;
	अचिन्हित दीर्घ		flags;

	req = usb_request_to_dummy_request(_req);
	अगर (!_req || !list_empty(&req->queue) || !_req->complete)
		वापस -EINVAL;

	ep = usb_ep_to_dummy_ep(_ep);
	अगर (!_ep || (!ep->desc && _ep->name != ep0name))
		वापस -EINVAL;

	dum = ep_to_dummy(ep);
	dum_hcd = gadget_to_dummy_hcd(&dum->gadget);
	अगर (!dum->driver || !is_enabled(dum_hcd))
		वापस -ESHUTDOWN;

#अगर 0
	dev_dbg(udc_dev(dum), "ep %p queue req %p to %s, len %d buf %p\n",
			ep, _req, _ep->name, _req->length, _req->buf);
#पूर्ण_अगर
	_req->status = -EINPROGRESS;
	_req->actual = 0;
	spin_lock_irqsave(&dum->lock, flags);

	/* implement an emulated single-request FIFO */
	अगर (ep->desc && (ep->desc->bEndpoपूर्णांकAddress & USB_सूची_IN) &&
			list_empty(&dum->fअगरo_req.queue) &&
			list_empty(&ep->queue) &&
			_req->length <= FIFO_SIZE) अणु
		req = &dum->fअगरo_req;
		req->req = *_req;
		req->req.buf = dum->fअगरo_buf;
		स_नकल(dum->fअगरo_buf, _req->buf, _req->length);
		req->req.context = dum;
		req->req.complete = fअगरo_complete;

		list_add_tail(&req->queue, &ep->queue);
		spin_unlock(&dum->lock);
		_req->actual = _req->length;
		_req->status = 0;
		usb_gadget_giveback_request(_ep, _req);
		spin_lock(&dum->lock);
	पूर्ण  अन्यथा
		list_add_tail(&req->queue, &ep->queue);
	spin_unlock_irqrestore(&dum->lock, flags);

	/* real hardware would likely enable transfers here, in हाल
	 * it'd been left NAKing.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा dummy_ep		*ep;
	काष्ठा dummy		*dum;
	पूर्णांक			retval = -EINVAL;
	अचिन्हित दीर्घ		flags;
	काष्ठा dummy_request	*req = शून्य;

	अगर (!_ep || !_req)
		वापस retval;
	ep = usb_ep_to_dummy_ep(_ep);
	dum = ep_to_dummy(ep);

	अगर (!dum->driver)
		वापस -ESHUTDOWN;

	local_irq_save(flags);
	spin_lock(&dum->lock);
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req) अणु
			list_del_init(&req->queue);
			_req->status = -ECONNRESET;
			retval = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&dum->lock);

	अगर (retval == 0) अणु
		dev_dbg(udc_dev(dum),
				"dequeued req %p from %s, len %d buf %p\n",
				req, _ep->name, _req->length, _req->buf);
		usb_gadget_giveback_request(_ep, _req);
	पूर्ण
	local_irq_restore(flags);
	वापस retval;
पूर्ण

अटल पूर्णांक
dummy_set_halt_and_wedge(काष्ठा usb_ep *_ep, पूर्णांक value, पूर्णांक wedged)
अणु
	काष्ठा dummy_ep		*ep;
	काष्ठा dummy		*dum;

	अगर (!_ep)
		वापस -EINVAL;
	ep = usb_ep_to_dummy_ep(_ep);
	dum = ep_to_dummy(ep);
	अगर (!dum->driver)
		वापस -ESHUTDOWN;
	अगर (!value)
		ep->halted = ep->wedged = 0;
	अन्यथा अगर (ep->desc && (ep->desc->bEndpoपूर्णांकAddress & USB_सूची_IN) &&
			!list_empty(&ep->queue))
		वापस -EAGAIN;
	अन्यथा अणु
		ep->halted = 1;
		अगर (wedged)
			ep->wedged = 1;
	पूर्ण
	/* FIXME clear emulated data toggle too */
	वापस 0;
पूर्ण

अटल पूर्णांक
dummy_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	वापस dummy_set_halt_and_wedge(_ep, value, 0);
पूर्ण

अटल पूर्णांक dummy_set_wedge(काष्ठा usb_ep *_ep)
अणु
	अगर (!_ep || _ep->name == ep0name)
		वापस -EINVAL;
	वापस dummy_set_halt_and_wedge(_ep, 1, 1);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops dummy_ep_ops = अणु
	.enable		= dummy_enable,
	.disable	= dummy_disable,

	.alloc_request	= dummy_alloc_request,
	.मुक्त_request	= dummy_मुक्त_request,

	.queue		= dummy_queue,
	.dequeue	= dummy_dequeue,

	.set_halt	= dummy_set_halt,
	.set_wedge	= dummy_set_wedge,
पूर्ण;

/*-------------------------------------------------------------------------*/

/* there are both host and device side versions of this call ... */
अटल पूर्णांक dummy_g_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा बारpec64 ts64;

	kसमय_get_ts64(&ts64);
	वापस ts64.tv_nsec / NSEC_PER_MSEC;
पूर्ण

अटल पूर्णांक dummy_wakeup(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा dummy_hcd *dum_hcd;

	dum_hcd = gadget_to_dummy_hcd(_gadget);
	अगर (!(dum_hcd->dum->devstatus & ((1 << USB_DEVICE_B_HNP_ENABLE)
				| (1 << USB_DEVICE_REMOTE_WAKEUP))))
		वापस -EINVAL;
	अगर ((dum_hcd->port_status & USB_PORT_STAT_CONNECTION) == 0)
		वापस -ENOLINK;
	अगर ((dum_hcd->port_status & USB_PORT_STAT_SUSPEND) == 0 &&
			 dum_hcd->rh_state != DUMMY_RH_SUSPENDED)
		वापस -EIO;

	/* FIXME: What अगर the root hub is suspended but the port isn't? */

	/* hub notices our request, issues करोwnstream resume, etc */
	dum_hcd->resuming = 1;
	dum_hcd->re_समयout = jअगरfies + msecs_to_jअगरfies(20);
	mod_समयr(&dummy_hcd_to_hcd(dum_hcd)->rh_समयr, dum_hcd->re_समयout);
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_set_selfघातered(काष्ठा usb_gadget *_gadget, पूर्णांक value)
अणु
	काष्ठा dummy	*dum;

	_gadget->is_selfघातered = (value != 0);
	dum = gadget_to_dummy_hcd(_gadget)->dum;
	अगर (value)
		dum->devstatus |= (1 << USB_DEVICE_SELF_POWERED);
	अन्यथा
		dum->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);
	वापस 0;
पूर्ण

अटल व्योम dummy_udc_update_ep0(काष्ठा dummy *dum)
अणु
	अगर (dum->gadget.speed == USB_SPEED_SUPER)
		dum->ep[0].ep.maxpacket = 9;
	अन्यथा
		dum->ep[0].ep.maxpacket = 64;
पूर्ण

अटल पूर्णांक dummy_pullup(काष्ठा usb_gadget *_gadget, पूर्णांक value)
अणु
	काष्ठा dummy_hcd *dum_hcd;
	काष्ठा dummy	*dum;
	अचिन्हित दीर्घ	flags;

	dum = gadget_dev_to_dummy(&_gadget->dev);
	dum_hcd = gadget_to_dummy_hcd(_gadget);

	spin_lock_irqsave(&dum->lock, flags);
	dum->pullup = (value != 0);
	set_link_state(dum_hcd);
	अगर (value == 0) अणु
		/*
		 * Emulate synchronize_irq(): रुको क्रम callbacks to finish.
		 * This seems to be the best place to emulate the call to
		 * synchronize_irq() that's in usb_gadget_हटाओ_driver().
		 * Doing it in dummy_udc_stop() would be too late since it
		 * is called after the unbind callback and unbind shouldn't
		 * be invoked until all the other callbacks are finished.
		 */
		जबतक (dum->callback_usage > 0) अणु
			spin_unlock_irqrestore(&dum->lock, flags);
			usleep_range(1000, 2000);
			spin_lock_irqsave(&dum->lock, flags);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dum->lock, flags);

	usb_hcd_poll_rh_status(dummy_hcd_to_hcd(dum_hcd));
	वापस 0;
पूर्ण

अटल व्योम dummy_udc_set_speed(काष्ठा usb_gadget *_gadget,
		क्रमागत usb_device_speed speed)
अणु
	काष्ठा dummy	*dum;

	dum = gadget_dev_to_dummy(&_gadget->dev);
	dum->gadget.speed = speed;
	dummy_udc_update_ep0(dum);
पूर्ण

अटल पूर्णांक dummy_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक dummy_udc_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops dummy_ops = अणु
	.get_frame	= dummy_g_get_frame,
	.wakeup		= dummy_wakeup,
	.set_selfघातered = dummy_set_selfघातered,
	.pullup		= dummy_pullup,
	.udc_start	= dummy_udc_start,
	.udc_stop	= dummy_udc_stop,
	.udc_set_speed	= dummy_udc_set_speed,
पूर्ण;

/*-------------------------------------------------------------------------*/

/* "function" sysfs attribute */
अटल sमाप_प्रकार function_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा dummy	*dum = gadget_dev_to_dummy(dev);

	अगर (!dum->driver || !dum->driver->function)
		वापस 0;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", dum->driver->function);
पूर्ण
अटल DEVICE_ATTR_RO(function);

/*-------------------------------------------------------------------------*/

/*
 * Driver registration/unregistration.
 *
 * This is basically hardware-specअगरic; there's usually only one real USB
 * device (not host) controller since that's how USB devices are पूर्णांकended
 * to work.  So most implementations of these api calls will rely on the
 * fact that only one driver will ever bind to the hardware.  But curious
 * hardware can be built with discrete components, so the gadget API करोesn't
 * require that assumption.
 *
 * For this emulator, it might be convenient to create a usb device
 * क्रम each driver that रेजिस्टरs:  just add to a big root hub.
 */

अटल पूर्णांक dummy_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा dummy_hcd	*dum_hcd = gadget_to_dummy_hcd(g);
	काष्ठा dummy		*dum = dum_hcd->dum;

	चयन (g->speed) अणु
	/* All the speeds we support */
	हाल USB_SPEED_LOW:
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_SUPER:
		अवरोध;
	शेष:
		dev_err(dummy_dev(dum_hcd), "Unsupported driver max speed %d\n",
				driver->max_speed);
		वापस -EINVAL;
	पूर्ण

	/*
	 * DEVICE side init ... the layer above hardware, which
	 * can't enumerate without help from the driver we're binding.
	 */

	spin_lock_irq(&dum->lock);
	dum->devstatus = 0;
	dum->driver = driver;
	dum->पूर्णांकs_enabled = 1;
	spin_unlock_irq(&dum->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक dummy_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा dummy_hcd	*dum_hcd = gadget_to_dummy_hcd(g);
	काष्ठा dummy		*dum = dum_hcd->dum;

	spin_lock_irq(&dum->lock);
	dum->पूर्णांकs_enabled = 0;
	stop_activity(dum);
	dum->driver = शून्य;
	spin_unlock_irq(&dum->lock);

	वापस 0;
पूर्ण

#अघोषित is_enabled

/* The gadget काष्ठाure is stored inside the hcd काष्ठाure and will be
 * released aदीर्घ with it. */
अटल व्योम init_dummy_udc_hw(काष्ठा dummy *dum)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&dum->gadget.ep_list);
	क्रम (i = 0; i < DUMMY_ENDPOINTS; i++) अणु
		काष्ठा dummy_ep	*ep = &dum->ep[i];

		अगर (!ep_info[i].name)
			अवरोध;
		ep->ep.name = ep_info[i].name;
		ep->ep.caps = ep_info[i].caps;
		ep->ep.ops = &dummy_ep_ops;
		list_add_tail(&ep->ep.ep_list, &dum->gadget.ep_list);
		ep->halted = ep->wedged = ep->alपढ़ोy_seen =
				ep->setup_stage = 0;
		usb_ep_set_maxpacket_limit(&ep->ep, ~0);
		ep->ep.max_streams = 16;
		ep->last_io = jअगरfies;
		ep->gadget = &dum->gadget;
		ep->desc = शून्य;
		INIT_LIST_HEAD(&ep->queue);
	पूर्ण

	dum->gadget.ep0 = &dum->ep[0].ep;
	list_del_init(&dum->ep[0].ep.ep_list);
	INIT_LIST_HEAD(&dum->fअगरo_req.queue);

#अगर_घोषित CONFIG_USB_OTG
	dum->gadget.is_otg = 1;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक dummy_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dummy	*dum;
	पूर्णांक		rc;

	dum = *((व्योम **)dev_get_platdata(&pdev->dev));
	/* Clear usb_gadget region क्रम new registration to udc-core */
	memzero_explicit(&dum->gadget, माप(काष्ठा usb_gadget));
	dum->gadget.name = gadget_name;
	dum->gadget.ops = &dummy_ops;
	अगर (mod_data.is_super_speed)
		dum->gadget.max_speed = USB_SPEED_SUPER;
	अन्यथा अगर (mod_data.is_high_speed)
		dum->gadget.max_speed = USB_SPEED_HIGH;
	अन्यथा
		dum->gadget.max_speed = USB_SPEED_FULL;

	dum->gadget.dev.parent = &pdev->dev;
	init_dummy_udc_hw(dum);

	rc = usb_add_gadget_udc(&pdev->dev, &dum->gadget);
	अगर (rc < 0)
		जाओ err_udc;

	rc = device_create_file(&dum->gadget.dev, &dev_attr_function);
	अगर (rc < 0)
		जाओ err_dev;
	platक्रमm_set_drvdata(pdev, dum);
	वापस rc;

err_dev:
	usb_del_gadget_udc(&dum->gadget);
err_udc:
	वापस rc;
पूर्ण

अटल पूर्णांक dummy_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dummy	*dum = platक्रमm_get_drvdata(pdev);

	device_हटाओ_file(&dum->gadget.dev, &dev_attr_function);
	usb_del_gadget_udc(&dum->gadget);
	वापस 0;
पूर्ण

अटल व्योम dummy_udc_pm(काष्ठा dummy *dum, काष्ठा dummy_hcd *dum_hcd,
		पूर्णांक suspend)
अणु
	spin_lock_irq(&dum->lock);
	dum->udc_suspended = suspend;
	set_link_state(dum_hcd);
	spin_unlock_irq(&dum->lock);
पूर्ण

अटल पूर्णांक dummy_udc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा dummy		*dum = platक्रमm_get_drvdata(pdev);
	काष्ठा dummy_hcd	*dum_hcd = gadget_to_dummy_hcd(&dum->gadget);

	dev_dbg(&pdev->dev, "%s\n", __func__);
	dummy_udc_pm(dum, dum_hcd, 1);
	usb_hcd_poll_rh_status(dummy_hcd_to_hcd(dum_hcd));
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_udc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dummy		*dum = platक्रमm_get_drvdata(pdev);
	काष्ठा dummy_hcd	*dum_hcd = gadget_to_dummy_hcd(&dum->gadget);

	dev_dbg(&pdev->dev, "%s\n", __func__);
	dummy_udc_pm(dum, dum_hcd, 0);
	usb_hcd_poll_rh_status(dummy_hcd_to_hcd(dum_hcd));
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dummy_udc_driver = अणु
	.probe		= dummy_udc_probe,
	.हटाओ		= dummy_udc_हटाओ,
	.suspend	= dummy_udc_suspend,
	.resume		= dummy_udc_resume,
	.driver		= अणु
		.name	= gadget_name,
	पूर्ण,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल अचिन्हित पूर्णांक dummy_get_ep_idx(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित पूर्णांक index;

	index = usb_endpoपूर्णांक_num(desc) << 1;
	अगर (usb_endpoपूर्णांक_dir_in(desc))
		index |= 1;
	वापस index;
पूर्ण

/* HOST SIDE DRIVER
 *
 * this uses the hcd framework to hook up to host side drivers.
 * its root hub will only have one device, otherwise it acts like
 * a normal host controller.
 *
 * when urbs are queued, they're just stuck on a list that we
 * scan in a समयr callback.  that callback connects ग_लिखोs from
 * the host with पढ़ोs from the device, and so on, based on the
 * usb 2.0 rules.
 */

अटल पूर्णांक dummy_ep_stream_en(काष्ठा dummy_hcd *dum_hcd, काष्ठा urb *urb)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc = &urb->ep->desc;
	u32 index;

	अगर (!usb_endpoपूर्णांक_xfer_bulk(desc))
		वापस 0;

	index = dummy_get_ep_idx(desc);
	वापस (1 << index) & dum_hcd->stream_en_ep;
पूर्ण

/*
 * The max stream number is saved as a nibble so क्रम the 30 possible endpoपूर्णांकs
 * we only 15 bytes of memory. Thereक्रमe we are limited to max 16 streams (0
 * means we use only 1 stream). The maximum according to the spec is 16bit so
 * अगर the 16 stream limit is about to go, the array size should be incremented
 * to 30 elements of type u16.
 */
अटल पूर्णांक get_max_streams_क्रम_pipe(काष्ठा dummy_hcd *dum_hcd,
		अचिन्हित पूर्णांक pipe)
अणु
	पूर्णांक max_streams;

	max_streams = dum_hcd->num_stream[usb_pipeendpoपूर्णांक(pipe)];
	अगर (usb_pipeout(pipe))
		max_streams >>= 4;
	अन्यथा
		max_streams &= 0xf;
	max_streams++;
	वापस max_streams;
पूर्ण

अटल व्योम set_max_streams_क्रम_pipe(काष्ठा dummy_hcd *dum_hcd,
		अचिन्हित पूर्णांक pipe, अचिन्हित पूर्णांक streams)
अणु
	पूर्णांक max_streams;

	streams--;
	max_streams = dum_hcd->num_stream[usb_pipeendpoपूर्णांक(pipe)];
	अगर (usb_pipeout(pipe)) अणु
		streams <<= 4;
		max_streams &= 0xf;
	पूर्ण अन्यथा अणु
		max_streams &= 0xf0;
	पूर्ण
	max_streams |= streams;
	dum_hcd->num_stream[usb_pipeendpoपूर्णांक(pipe)] = max_streams;
पूर्ण

अटल पूर्णांक dummy_validate_stream(काष्ठा dummy_hcd *dum_hcd, काष्ठा urb *urb)
अणु
	अचिन्हित पूर्णांक max_streams;
	पूर्णांक enabled;

	enabled = dummy_ep_stream_en(dum_hcd, urb);
	अगर (!urb->stream_id) अणु
		अगर (enabled)
			वापस -EINVAL;
		वापस 0;
	पूर्ण
	अगर (!enabled)
		वापस -EINVAL;

	max_streams = get_max_streams_क्रम_pipe(dum_hcd,
			usb_pipeendpoपूर्णांक(urb->pipe));
	अगर (urb->stream_id > max_streams) अणु
		dev_err(dummy_dev(dum_hcd), "Stream id %d is out of range.\n",
				urb->stream_id);
		BUG();
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_urb_enqueue(
	काष्ठा usb_hcd			*hcd,
	काष्ठा urb			*urb,
	gfp_t				mem_flags
) अणु
	काष्ठा dummy_hcd *dum_hcd;
	काष्ठा urbp	*urbp;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		rc;

	urbp = kदो_स्मृति(माप *urbp, mem_flags);
	अगर (!urbp)
		वापस -ENOMEM;
	urbp->urb = urb;
	urbp->miter_started = 0;

	dum_hcd = hcd_to_dummy_hcd(hcd);
	spin_lock_irqsave(&dum_hcd->dum->lock, flags);

	rc = dummy_validate_stream(dum_hcd, urb);
	अगर (rc) अणु
		kमुक्त(urbp);
		जाओ करोne;
	पूर्ण

	rc = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (rc) अणु
		kमुक्त(urbp);
		जाओ करोne;
	पूर्ण

	अगर (!dum_hcd->udev) अणु
		dum_hcd->udev = urb->dev;
		usb_get_dev(dum_hcd->udev);
	पूर्ण अन्यथा अगर (unlikely(dum_hcd->udev != urb->dev))
		dev_err(dummy_dev(dum_hcd), "usb_device address has changed!\n");

	list_add_tail(&urbp->urbp_list, &dum_hcd->urbp_list);
	urb->hcpriv = urbp;
	अगर (!dum_hcd->next_frame_urbp)
		dum_hcd->next_frame_urbp = urbp;
	अगर (usb_pipetype(urb->pipe) == PIPE_CONTROL)
		urb->error_count = 1;		/* mark as a new urb */

	/* kick the scheduler, it'll करो the rest */
	अगर (!समयr_pending(&dum_hcd->समयr))
		mod_समयr(&dum_hcd->समयr, jअगरfies + 1);

 करोne:
	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक dummy_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा dummy_hcd *dum_hcd;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		rc;

	/* giveback happens स्वतःmatically in समयr callback,
	 * so make sure the callback happens */
	dum_hcd = hcd_to_dummy_hcd(hcd);
	spin_lock_irqsave(&dum_hcd->dum->lock, flags);

	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (!rc && dum_hcd->rh_state != DUMMY_RH_RUNNING &&
			!list_empty(&dum_hcd->urbp_list))
		mod_समयr(&dum_hcd->समयr, jअगरfies);

	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक dummy_perक्रमm_transfer(काष्ठा urb *urb, काष्ठा dummy_request *req,
		u32 len)
अणु
	व्योम *ubuf, *rbuf;
	काष्ठा urbp *urbp = urb->hcpriv;
	पूर्णांक to_host;
	काष्ठा sg_mapping_iter *miter = &urbp->miter;
	u32 trans = 0;
	u32 this_sg;
	bool next_sg;

	to_host = usb_urb_dir_in(urb);
	rbuf = req->req.buf + req->req.actual;

	अगर (!urb->num_sgs) अणु
		ubuf = urb->transfer_buffer + urb->actual_length;
		अगर (to_host)
			स_नकल(ubuf, rbuf, len);
		अन्यथा
			स_नकल(rbuf, ubuf, len);
		वापस len;
	पूर्ण

	अगर (!urbp->miter_started) अणु
		u32 flags = SG_MITER_ATOMIC;

		अगर (to_host)
			flags |= SG_MITER_TO_SG;
		अन्यथा
			flags |= SG_MITER_FROM_SG;

		sg_miter_start(miter, urb->sg, urb->num_sgs, flags);
		urbp->miter_started = 1;
	पूर्ण
	next_sg = sg_miter_next(miter);
	अगर (next_sg == false) अणु
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण
	करो अणु
		ubuf = miter->addr;
		this_sg = min_t(u32, len, miter->length);
		miter->consumed = this_sg;
		trans += this_sg;

		अगर (to_host)
			स_नकल(ubuf, rbuf, this_sg);
		अन्यथा
			स_नकल(rbuf, ubuf, this_sg);
		len -= this_sg;

		अगर (!len)
			अवरोध;
		next_sg = sg_miter_next(miter);
		अगर (next_sg == false) अणु
			WARN_ON_ONCE(1);
			वापस -EINVAL;
		पूर्ण

		rbuf += this_sg;
	पूर्ण जबतक (1);

	sg_miter_stop(miter);
	वापस trans;
पूर्ण

/* transfer up to a frame's worth; caller must own lock */
अटल पूर्णांक transfer(काष्ठा dummy_hcd *dum_hcd, काष्ठा urb *urb,
		काष्ठा dummy_ep *ep, पूर्णांक limit, पूर्णांक *status)
अणु
	काष्ठा dummy		*dum = dum_hcd->dum;
	काष्ठा dummy_request	*req;
	पूर्णांक			sent = 0;

top:
	/* अगर there's no request queued, the device is NAKing; वापस */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अचिन्हित	host_len, dev_len, len;
		पूर्णांक		is_लघु, to_host;
		पूर्णांक		rescan = 0;

		अगर (dummy_ep_stream_en(dum_hcd, urb)) अणु
			अगर ((urb->stream_id != req->req.stream_id))
				जारी;
		पूर्ण

		/* 1..N packets of ep->ep.maxpacket each ... the last one
		 * may be लघु (including zero length).
		 *
		 * ग_लिखोr can send a zlp explicitly (length 0) or implicitly
		 * (length mod maxpacket zero, and 'zero' flag); they always
		 * terminate पढ़ोs.
		 */
		host_len = urb->transfer_buffer_length - urb->actual_length;
		dev_len = req->req.length - req->req.actual;
		len = min(host_len, dev_len);

		/* FIXME update emulated data toggle too */

		to_host = usb_urb_dir_in(urb);
		अगर (unlikely(len == 0))
			is_लघु = 1;
		अन्यथा अणु
			/* not enough bandwidth left? */
			अगर (limit < ep->ep.maxpacket && limit < len)
				अवरोध;
			len = min_t(अचिन्हित, len, limit);
			अगर (len == 0)
				अवरोध;

			/* send multiple of maxpacket first, then reमुख्यder */
			अगर (len >= ep->ep.maxpacket) अणु
				is_लघु = 0;
				अगर (len % ep->ep.maxpacket)
					rescan = 1;
				len -= len % ep->ep.maxpacket;
			पूर्ण अन्यथा अणु
				is_लघु = 1;
			पूर्ण

			len = dummy_perक्रमm_transfer(urb, req, len);

			ep->last_io = jअगरfies;
			अगर ((पूर्णांक)len < 0) अणु
				req->req.status = len;
			पूर्ण अन्यथा अणु
				limit -= len;
				sent += len;
				urb->actual_length += len;
				req->req.actual += len;
			पूर्ण
		पूर्ण

		/* लघु packets terminate, maybe with overflow/underflow.
		 * it's only really an error to ग_लिखो too much.
		 *
		 * partially filling a buffer optionally blocks queue advances
		 * (so completion handlers can clean up the queue) but we करोn't
		 * need to emulate such data-in-flight.
		 */
		अगर (is_लघु) अणु
			अगर (host_len == dev_len) अणु
				req->req.status = 0;
				*status = 0;
			पूर्ण अन्यथा अगर (to_host) अणु
				req->req.status = 0;
				अगर (dev_len > host_len)
					*status = -EOVERFLOW;
				अन्यथा
					*status = 0;
			पूर्ण अन्यथा अणु
				*status = 0;
				अगर (host_len > dev_len)
					req->req.status = -EOVERFLOW;
				अन्यथा
					req->req.status = 0;
			पूर्ण

		/*
		 * many requests terminate without a लघु packet.
		 * send a zlp अगर demanded by flags.
		 */
		पूर्ण अन्यथा अणु
			अगर (req->req.length == req->req.actual) अणु
				अगर (req->req.zero && to_host)
					rescan = 1;
				अन्यथा
					req->req.status = 0;
			पूर्ण
			अगर (urb->transfer_buffer_length == urb->actual_length) अणु
				अगर (urb->transfer_flags & URB_ZERO_PACKET &&
				    !to_host)
					rescan = 1;
				अन्यथा
					*status = 0;
			पूर्ण
		पूर्ण

		/* device side completion --> continuable */
		अगर (req->req.status != -EINPROGRESS) अणु
			list_del_init(&req->queue);

			spin_unlock(&dum->lock);
			usb_gadget_giveback_request(&ep->ep, &req->req);
			spin_lock(&dum->lock);

			/* requests might have been unlinked... */
			rescan = 1;
		पूर्ण

		/* host side completion --> terminate */
		अगर (*status != -EINPROGRESS)
			अवरोध;

		/* rescan to जारी with any other queued i/o */
		अगर (rescan)
			जाओ top;
	पूर्ण
	वापस sent;
पूर्ण

अटल पूर्णांक periodic_bytes(काष्ठा dummy *dum, काष्ठा dummy_ep *ep)
अणु
	पूर्णांक	limit = ep->ep.maxpacket;

	अगर (dum->gadget.speed == USB_SPEED_HIGH) अणु
		पूर्णांक	पंचांगp;

		/* high bandwidth mode */
		पंचांगp = usb_endpoपूर्णांक_maxp_mult(ep->desc);
		पंचांगp *= 8 /* applies to entire frame */;
		limit += limit * पंचांगp;
	पूर्ण
	अगर (dum->gadget.speed == USB_SPEED_SUPER) अणु
		चयन (usb_endpoपूर्णांक_type(ep->desc)) अणु
		हाल USB_ENDPOINT_XFER_ISOC:
			/* Sec. 4.4.8.2 USB3.0 Spec */
			limit = 3 * 16 * 1024 * 8;
			अवरोध;
		हाल USB_ENDPOINT_XFER_INT:
			/* Sec. 4.4.7.2 USB3.0 Spec */
			limit = 3 * 1024 * 8;
			अवरोध;
		हाल USB_ENDPOINT_XFER_BULK:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस limit;
पूर्ण

#घोषणा is_active(dum_hcd)	((dum_hcd->port_status & \
		(USB_PORT_STAT_CONNECTION | USB_PORT_STAT_ENABLE | \
			USB_PORT_STAT_SUSPEND)) \
		== (USB_PORT_STAT_CONNECTION | USB_PORT_STAT_ENABLE))

अटल काष्ठा dummy_ep *find_endpoपूर्णांक(काष्ठा dummy *dum, u8 address)
अणु
	पूर्णांक		i;

	अगर (!is_active((dum->gadget.speed == USB_SPEED_SUPER ?
			dum->ss_hcd : dum->hs_hcd)))
		वापस शून्य;
	अगर (!dum->पूर्णांकs_enabled)
		वापस शून्य;
	अगर ((address & ~USB_सूची_IN) == 0)
		वापस &dum->ep[0];
	क्रम (i = 1; i < DUMMY_ENDPOINTS; i++) अणु
		काष्ठा dummy_ep	*ep = &dum->ep[i];

		अगर (!ep->desc)
			जारी;
		अगर (ep->desc->bEndpoपूर्णांकAddress == address)
			वापस ep;
	पूर्ण
	वापस शून्य;
पूर्ण

#अघोषित is_active

#घोषणा Dev_Request	(USB_TYPE_STANDARD | USB_RECIP_DEVICE)
#घोषणा Dev_InRequest	(Dev_Request | USB_सूची_IN)
#घोषणा Intf_Request	(USB_TYPE_STANDARD | USB_RECIP_INTERFACE)
#घोषणा Intf_InRequest	(Intf_Request | USB_सूची_IN)
#घोषणा Ep_Request	(USB_TYPE_STANDARD | USB_RECIP_ENDPOINT)
#घोषणा Ep_InRequest	(Ep_Request | USB_सूची_IN)


/**
 * handle_control_request() - handles all control transfers
 * @dum_hcd: poपूर्णांकer to dummy (the_controller)
 * @urb: the urb request to handle
 * @setup: poपूर्णांकer to the setup data क्रम a USB device control
 *	 request
 * @status: poपूर्णांकer to request handling status
 *
 * Return 0 - अगर the request was handled
 *	  1 - अगर the request wasn't handles
 *	  error code on error
 */
अटल पूर्णांक handle_control_request(काष्ठा dummy_hcd *dum_hcd, काष्ठा urb *urb,
				  काष्ठा usb_ctrlrequest *setup,
				  पूर्णांक *status)
अणु
	काष्ठा dummy_ep		*ep2;
	काष्ठा dummy		*dum = dum_hcd->dum;
	पूर्णांक			ret_val = 1;
	अचिन्हित	w_index;
	अचिन्हित	w_value;

	w_index = le16_to_cpu(setup->wIndex);
	w_value = le16_to_cpu(setup->wValue);
	चयन (setup->bRequest) अणु
	हाल USB_REQ_SET_ADDRESS:
		अगर (setup->bRequestType != Dev_Request)
			अवरोध;
		dum->address = w_value;
		*status = 0;
		dev_dbg(udc_dev(dum), "set_address = %d\n",
				w_value);
		ret_val = 0;
		अवरोध;
	हाल USB_REQ_SET_FEATURE:
		अगर (setup->bRequestType == Dev_Request) अणु
			ret_val = 0;
			चयन (w_value) अणु
			हाल USB_DEVICE_REMOTE_WAKEUP:
				अवरोध;
			हाल USB_DEVICE_B_HNP_ENABLE:
				dum->gadget.b_hnp_enable = 1;
				अवरोध;
			हाल USB_DEVICE_A_HNP_SUPPORT:
				dum->gadget.a_hnp_support = 1;
				अवरोध;
			हाल USB_DEVICE_A_ALT_HNP_SUPPORT:
				dum->gadget.a_alt_hnp_support = 1;
				अवरोध;
			हाल USB_DEVICE_U1_ENABLE:
				अगर (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_U1_ENABLED;
				अन्यथा
					ret_val = -EOPNOTSUPP;
				अवरोध;
			हाल USB_DEVICE_U2_ENABLE:
				अगर (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_U2_ENABLED;
				अन्यथा
					ret_val = -EOPNOTSUPP;
				अवरोध;
			हाल USB_DEVICE_LTM_ENABLE:
				अगर (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_LTM_ENABLED;
				अन्यथा
					ret_val = -EOPNOTSUPP;
				अवरोध;
			शेष:
				ret_val = -EOPNOTSUPP;
			पूर्ण
			अगर (ret_val == 0) अणु
				dum->devstatus |= (1 << w_value);
				*status = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (setup->bRequestType == Ep_Request) अणु
			/* endpoपूर्णांक halt */
			ep2 = find_endpoपूर्णांक(dum, w_index);
			अगर (!ep2 || ep2->ep.name == ep0name) अणु
				ret_val = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			ep2->halted = 1;
			ret_val = 0;
			*status = 0;
		पूर्ण
		अवरोध;
	हाल USB_REQ_CLEAR_FEATURE:
		अगर (setup->bRequestType == Dev_Request) अणु
			ret_val = 0;
			चयन (w_value) अणु
			हाल USB_DEVICE_REMOTE_WAKEUP:
				w_value = USB_DEVICE_REMOTE_WAKEUP;
				अवरोध;
			हाल USB_DEVICE_U1_ENABLE:
				अगर (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_U1_ENABLED;
				अन्यथा
					ret_val = -EOPNOTSUPP;
				अवरोध;
			हाल USB_DEVICE_U2_ENABLE:
				अगर (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_U2_ENABLED;
				अन्यथा
					ret_val = -EOPNOTSUPP;
				अवरोध;
			हाल USB_DEVICE_LTM_ENABLE:
				अगर (dummy_hcd_to_hcd(dum_hcd)->speed ==
				    HCD_USB3)
					w_value = USB_DEV_STAT_LTM_ENABLED;
				अन्यथा
					ret_val = -EOPNOTSUPP;
				अवरोध;
			शेष:
				ret_val = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			अगर (ret_val == 0) अणु
				dum->devstatus &= ~(1 << w_value);
				*status = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (setup->bRequestType == Ep_Request) अणु
			/* endpoपूर्णांक halt */
			ep2 = find_endpoपूर्णांक(dum, w_index);
			अगर (!ep2) अणु
				ret_val = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			अगर (!ep2->wedged)
				ep2->halted = 0;
			ret_val = 0;
			*status = 0;
		पूर्ण
		अवरोध;
	हाल USB_REQ_GET_STATUS:
		अगर (setup->bRequestType == Dev_InRequest
				|| setup->bRequestType == Intf_InRequest
				|| setup->bRequestType == Ep_InRequest) अणु
			अक्षर *buf;
			/*
			 * device: remote wakeup, selfघातered
			 * पूर्णांकerface: nothing
			 * endpoपूर्णांक: halt
			 */
			buf = (अक्षर *)urb->transfer_buffer;
			अगर (urb->transfer_buffer_length > 0) अणु
				अगर (setup->bRequestType == Ep_InRequest) अणु
					ep2 = find_endpoपूर्णांक(dum, w_index);
					अगर (!ep2) अणु
						ret_val = -EOPNOTSUPP;
						अवरोध;
					पूर्ण
					buf[0] = ep2->halted;
				पूर्ण अन्यथा अगर (setup->bRequestType ==
					   Dev_InRequest) अणु
					buf[0] = (u8)dum->devstatus;
				पूर्ण अन्यथा
					buf[0] = 0;
			पूर्ण
			अगर (urb->transfer_buffer_length > 1)
				buf[1] = 0;
			urb->actual_length = min_t(u32, 2,
				urb->transfer_buffer_length);
			ret_val = 0;
			*status = 0;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस ret_val;
पूर्ण

/*
 * Drive both sides of the transfers; looks like irq handlers to both
 * drivers except that the callbacks are invoked from soft पूर्णांकerrupt
 * context.
 */
अटल व्योम dummy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा dummy_hcd	*dum_hcd = from_समयr(dum_hcd, t, समयr);
	काष्ठा dummy		*dum = dum_hcd->dum;
	काष्ठा urbp		*urbp, *पंचांगp;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			limit, total;
	पूर्णांक			i;

	/* simplistic model क्रम one frame's bandwidth */
	/* FIXME: account क्रम transaction and packet overhead */
	चयन (dum->gadget.speed) अणु
	हाल USB_SPEED_LOW:
		total = 8/*bytes*/ * 12/*packets*/;
		अवरोध;
	हाल USB_SPEED_FULL:
		total = 64/*bytes*/ * 19/*packets*/;
		अवरोध;
	हाल USB_SPEED_HIGH:
		total = 512/*bytes*/ * 13/*packets*/ * 8/*uframes*/;
		अवरोध;
	हाल USB_SPEED_SUPER:
		/* Bus speed is 500000 bytes/ms, so use a little less */
		total = 490000;
		अवरोध;
	शेष:	/* Can't happen */
		dev_err(dummy_dev(dum_hcd), "bogus device speed\n");
		total = 0;
		अवरोध;
	पूर्ण

	/* FIXME अगर HZ != 1000 this will probably misbehave ... */

	/* look at each urb queued by the host side driver */
	spin_lock_irqsave(&dum->lock, flags);

	अगर (!dum_hcd->udev) अणु
		dev_err(dummy_dev(dum_hcd),
				"timer fired with no URBs pending?\n");
		spin_unlock_irqrestore(&dum->lock, flags);
		वापस;
	पूर्ण
	dum_hcd->next_frame_urbp = शून्य;

	क्रम (i = 0; i < DUMMY_ENDPOINTS; i++) अणु
		अगर (!ep_info[i].name)
			अवरोध;
		dum->ep[i].alपढ़ोy_seen = 0;
	पूर्ण

restart:
	list_क्रम_each_entry_safe(urbp, पंचांगp, &dum_hcd->urbp_list, urbp_list) अणु
		काष्ठा urb		*urb;
		काष्ठा dummy_request	*req;
		u8			address;
		काष्ठा dummy_ep		*ep = शून्य;
		पूर्णांक			status = -EINPROGRESS;

		/* stop when we reach URBs queued after the समयr पूर्णांकerrupt */
		अगर (urbp == dum_hcd->next_frame_urbp)
			अवरोध;

		urb = urbp->urb;
		अगर (urb->unlinked)
			जाओ वापस_urb;
		अन्यथा अगर (dum_hcd->rh_state != DUMMY_RH_RUNNING)
			जारी;

		/* Used up this frame's bandwidth? */
		अगर (total <= 0)
			जारी;

		/* find the gadget's ep क्रम this request (अगर configured) */
		address = usb_pipeendpoपूर्णांक (urb->pipe);
		अगर (usb_urb_dir_in(urb))
			address |= USB_सूची_IN;
		ep = find_endpoपूर्णांक(dum, address);
		अगर (!ep) अणु
			/* set_configuration() disagreement */
			dev_dbg(dummy_dev(dum_hcd),
				"no ep configured for urb %p\n",
				urb);
			status = -EPROTO;
			जाओ वापस_urb;
		पूर्ण

		अगर (ep->alपढ़ोy_seen)
			जारी;
		ep->alपढ़ोy_seen = 1;
		अगर (ep == &dum->ep[0] && urb->error_count) अणु
			ep->setup_stage = 1;	/* a new urb */
			urb->error_count = 0;
		पूर्ण
		अगर (ep->halted && !ep->setup_stage) अणु
			/* NOTE: must not be iso! */
			dev_dbg(dummy_dev(dum_hcd), "ep %s halted, urb %p\n",
					ep->ep.name, urb);
			status = -EPIPE;
			जाओ वापस_urb;
		पूर्ण
		/* FIXME make sure both ends agree on maxpacket */

		/* handle control requests */
		अगर (ep == &dum->ep[0] && ep->setup_stage) अणु
			काष्ठा usb_ctrlrequest		setup;
			पूर्णांक				value;

			setup = *(काष्ठा usb_ctrlrequest *) urb->setup_packet;
			/* paranoia, in हाल of stale queued data */
			list_क्रम_each_entry(req, &ep->queue, queue) अणु
				list_del_init(&req->queue);
				req->req.status = -EOVERFLOW;
				dev_dbg(udc_dev(dum), "stale req = %p\n",
						req);

				spin_unlock(&dum->lock);
				usb_gadget_giveback_request(&ep->ep, &req->req);
				spin_lock(&dum->lock);
				ep->alपढ़ोy_seen = 0;
				जाओ restart;
			पूर्ण

			/* gadget driver never sees set_address or operations
			 * on standard feature flags.  some hardware करोesn't
			 * even expose them.
			 */
			ep->last_io = jअगरfies;
			ep->setup_stage = 0;
			ep->halted = 0;

			value = handle_control_request(dum_hcd, urb, &setup,
						       &status);

			/* gadget driver handles all other requests.  block
			 * until setup() वापसs; no reentrancy issues etc.
			 */
			अगर (value > 0) अणु
				++dum->callback_usage;
				spin_unlock(&dum->lock);
				value = dum->driver->setup(&dum->gadget,
						&setup);
				spin_lock(&dum->lock);
				--dum->callback_usage;

				अगर (value >= 0) अणु
					/* no delays (max 64KB data stage) */
					limit = 64*1024;
					जाओ treat_control_like_bulk;
				पूर्ण
				/* error, see below */
			पूर्ण

			अगर (value < 0) अणु
				अगर (value != -EOPNOTSUPP)
					dev_dbg(udc_dev(dum),
						"setup --> %d\n",
						value);
				status = -EPIPE;
				urb->actual_length = 0;
			पूर्ण

			जाओ वापस_urb;
		पूर्ण

		/* non-control requests */
		limit = total;
		चयन (usb_pipetype(urb->pipe)) अणु
		हाल PIPE_ISOCHRONOUS:
			/*
			 * We करोn't support isochronous.  But अगर we did,
			 * here are some of the issues we'd have to face:
			 *
			 * Is it urb->पूर्णांकerval since the last xfer?
			 * Use urb->iso_frame_desc[i].
			 * Complete whether or not ep has requests queued.
			 * Report अक्रमom errors, to debug drivers.
			 */
			limit = max(limit, periodic_bytes(dum, ep));
			status = -EINVAL;	/* fail all xfers */
			अवरोध;

		हाल PIPE_INTERRUPT:
			/* FIXME is it urb->पूर्णांकerval since the last xfer?
			 * this almost certainly polls too fast.
			 */
			limit = max(limit, periodic_bytes(dum, ep));
			fallthrough;

		शेष:
treat_control_like_bulk:
			ep->last_io = jअगरfies;
			total -= transfer(dum_hcd, urb, ep, limit, &status);
			अवरोध;
		पूर्ण

		/* incomplete transfer? */
		अगर (status == -EINPROGRESS)
			जारी;

वापस_urb:
		list_del(&urbp->urbp_list);
		kमुक्त(urbp);
		अगर (ep)
			ep->alपढ़ोy_seen = ep->setup_stage = 0;

		usb_hcd_unlink_urb_from_ep(dummy_hcd_to_hcd(dum_hcd), urb);
		spin_unlock(&dum->lock);
		usb_hcd_giveback_urb(dummy_hcd_to_hcd(dum_hcd), urb, status);
		spin_lock(&dum->lock);

		जाओ restart;
	पूर्ण

	अगर (list_empty(&dum_hcd->urbp_list)) अणु
		usb_put_dev(dum_hcd->udev);
		dum_hcd->udev = शून्य;
	पूर्ण अन्यथा अगर (dum_hcd->rh_state == DUMMY_RH_RUNNING) अणु
		/* want a 1 msec delay here */
		mod_समयr(&dum_hcd->समयr, jअगरfies + msecs_to_jअगरfies(1));
	पूर्ण

	spin_unlock_irqrestore(&dum->lock, flags);
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा PORT_C_MASK \
	((USB_PORT_STAT_C_CONNECTION \
	| USB_PORT_STAT_C_ENABLE \
	| USB_PORT_STAT_C_SUSPEND \
	| USB_PORT_STAT_C_OVERCURRENT \
	| USB_PORT_STAT_C_RESET) << 16)

अटल पूर्णांक dummy_hub_status(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा dummy_hcd	*dum_hcd;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			retval = 0;

	dum_hcd = hcd_to_dummy_hcd(hcd);

	spin_lock_irqsave(&dum_hcd->dum->lock, flags);
	अगर (!HCD_HW_ACCESSIBLE(hcd))
		जाओ करोne;

	अगर (dum_hcd->resuming && समय_after_eq(jअगरfies, dum_hcd->re_समयout)) अणु
		dum_hcd->port_status |= (USB_PORT_STAT_C_SUSPEND << 16);
		dum_hcd->port_status &= ~USB_PORT_STAT_SUSPEND;
		set_link_state(dum_hcd);
	पूर्ण

	अगर ((dum_hcd->port_status & PORT_C_MASK) != 0) अणु
		*buf = (1 << 1);
		dev_dbg(dummy_dev(dum_hcd), "port status 0x%08x has changes\n",
				dum_hcd->port_status);
		retval = 1;
		अगर (dum_hcd->rh_state == DUMMY_RH_SUSPENDED)
			usb_hcd_resume_root_hub(hcd);
	पूर्ण
करोne:
	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);
	वापस retval;
पूर्ण

/* usb 3.0 root hub device descriptor */
अटल काष्ठा अणु
	काष्ठा usb_bos_descriptor bos;
	काष्ठा usb_ss_cap_descriptor ss_cap;
पूर्ण __packed usb3_bos_desc = अणु

	.bos = अणु
		.bLength		= USB_DT_BOS_SIZE,
		.bDescriptorType	= USB_DT_BOS,
		.wTotalLength		= cpu_to_le16(माप(usb3_bos_desc)),
		.bNumDeviceCaps		= 1,
	पूर्ण,
	.ss_cap = अणु
		.bLength		= USB_DT_USB_SS_CAP_SIZE,
		.bDescriptorType	= USB_DT_DEVICE_CAPABILITY,
		.bDevCapabilityType	= USB_SS_CAP_TYPE,
		.wSpeedSupported	= cpu_to_le16(USB_5GBPS_OPERATION),
		.bFunctionalitySupport	= ilog2(USB_5GBPS_OPERATION),
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम
ss_hub_descriptor(काष्ठा usb_hub_descriptor *desc)
अणु
	स_रखो(desc, 0, माप *desc);
	desc->bDescriptorType = USB_DT_SS_HUB;
	desc->bDescLength = 12;
	desc->wHubCharacteristics = cpu_to_le16(
			HUB_CHAR_INDV_PORT_LPSM |
			HUB_CHAR_COMMON_OCPM);
	desc->bNbrPorts = 1;
	desc->u.ss.bHubHdrDecLat = 0x04; /* Worst हाल: 0.4 micro sec*/
	desc->u.ss.DeviceRemovable = 0;
पूर्ण

अटल अंतरभूत व्योम hub_descriptor(काष्ठा usb_hub_descriptor *desc)
अणु
	स_रखो(desc, 0, माप *desc);
	desc->bDescriptorType = USB_DT_HUB;
	desc->bDescLength = 9;
	desc->wHubCharacteristics = cpu_to_le16(
			HUB_CHAR_INDV_PORT_LPSM |
			HUB_CHAR_COMMON_OCPM);
	desc->bNbrPorts = 1;
	desc->u.hs.DeviceRemovable[0] = 0;
	desc->u.hs.DeviceRemovable[1] = 0xff;	/* PortPwrCtrlMask */
पूर्ण

अटल पूर्णांक dummy_hub_control(
	काष्ठा usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	अक्षर		*buf,
	u16		wLength
) अणु
	काष्ठा dummy_hcd *dum_hcd;
	पूर्णांक		retval = 0;
	अचिन्हित दीर्घ	flags;

	अगर (!HCD_HW_ACCESSIBLE(hcd))
		वापस -ETIMEDOUT;

	dum_hcd = hcd_to_dummy_hcd(hcd);

	spin_lock_irqsave(&dum_hcd->dum->lock, flags);
	चयन (typeReq) अणु
	हाल ClearHubFeature:
		अवरोध;
	हाल ClearPortFeature:
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			अगर (hcd->speed == HCD_USB3) अणु
				dev_dbg(dummy_dev(dum_hcd),
					 "USB_PORT_FEAT_SUSPEND req not "
					 "supported for USB 3.0 roothub\n");
				जाओ error;
			पूर्ण
			अगर (dum_hcd->port_status & USB_PORT_STAT_SUSPEND) अणु
				/* 20msec resume संकेतing */
				dum_hcd->resuming = 1;
				dum_hcd->re_समयout = jअगरfies +
						msecs_to_jअगरfies(20);
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			dev_dbg(dummy_dev(dum_hcd), "power-off\n");
			अगर (hcd->speed == HCD_USB3)
				dum_hcd->port_status &= ~USB_SS_PORT_STAT_POWER;
			अन्यथा
				dum_hcd->port_status &= ~USB_PORT_STAT_POWER;
			set_link_state(dum_hcd);
			अवरोध;
		हाल USB_PORT_FEAT_ENABLE:
		हाल USB_PORT_FEAT_C_ENABLE:
		हाल USB_PORT_FEAT_C_SUSPEND:
			/* Not allowed क्रम USB-3 */
			अगर (hcd->speed == HCD_USB3)
				जाओ error;
			fallthrough;
		हाल USB_PORT_FEAT_C_CONNECTION:
		हाल USB_PORT_FEAT_C_RESET:
			dum_hcd->port_status &= ~(1 << wValue);
			set_link_state(dum_hcd);
			अवरोध;
		शेष:
		/* Disallow INDICATOR and C_OVER_CURRENT */
			जाओ error;
		पूर्ण
		अवरोध;
	हाल GetHubDescriptor:
		अगर (hcd->speed == HCD_USB3 &&
				(wLength < USB_DT_SS_HUB_SIZE ||
				 wValue != (USB_DT_SS_HUB << 8))) अणु
			dev_dbg(dummy_dev(dum_hcd),
				"Wrong hub descriptor type for "
				"USB 3.0 roothub.\n");
			जाओ error;
		पूर्ण
		अगर (hcd->speed == HCD_USB3)
			ss_hub_descriptor((काष्ठा usb_hub_descriptor *) buf);
		अन्यथा
			hub_descriptor((काष्ठा usb_hub_descriptor *) buf);
		अवरोध;

	हाल DeviceRequest | USB_REQ_GET_DESCRIPTOR:
		अगर (hcd->speed != HCD_USB3)
			जाओ error;

		अगर ((wValue >> 8) != USB_DT_BOS)
			जाओ error;

		स_नकल(buf, &usb3_bos_desc, माप(usb3_bos_desc));
		retval = माप(usb3_bos_desc);
		अवरोध;

	हाल GetHubStatus:
		*(__le32 *) buf = cpu_to_le32(0);
		अवरोध;
	हाल GetPortStatus:
		अगर (wIndex != 1)
			retval = -EPIPE;

		/* whoever resets or resumes must GetPortStatus to
		 * complete it!!
		 */
		अगर (dum_hcd->resuming &&
				समय_after_eq(jअगरfies, dum_hcd->re_समयout)) अणु
			dum_hcd->port_status |= (USB_PORT_STAT_C_SUSPEND << 16);
			dum_hcd->port_status &= ~USB_PORT_STAT_SUSPEND;
		पूर्ण
		अगर ((dum_hcd->port_status & USB_PORT_STAT_RESET) != 0 &&
				समय_after_eq(jअगरfies, dum_hcd->re_समयout)) अणु
			dum_hcd->port_status |= (USB_PORT_STAT_C_RESET << 16);
			dum_hcd->port_status &= ~USB_PORT_STAT_RESET;
			अगर (dum_hcd->dum->pullup) अणु
				dum_hcd->port_status |= USB_PORT_STAT_ENABLE;

				अगर (hcd->speed < HCD_USB3) अणु
					चयन (dum_hcd->dum->gadget.speed) अणु
					हाल USB_SPEED_HIGH:
						dum_hcd->port_status |=
						      USB_PORT_STAT_HIGH_SPEED;
						अवरोध;
					हाल USB_SPEED_LOW:
						dum_hcd->dum->gadget.ep0->
							maxpacket = 8;
						dum_hcd->port_status |=
							USB_PORT_STAT_LOW_SPEED;
						अवरोध;
					शेष:
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		set_link_state(dum_hcd);
		((__le16 *) buf)[0] = cpu_to_le16(dum_hcd->port_status);
		((__le16 *) buf)[1] = cpu_to_le16(dum_hcd->port_status >> 16);
		अवरोध;
	हाल SetHubFeature:
		retval = -EPIPE;
		अवरोध;
	हाल SetPortFeature:
		चयन (wValue) अणु
		हाल USB_PORT_FEAT_LINK_STATE:
			अगर (hcd->speed != HCD_USB3) अणु
				dev_dbg(dummy_dev(dum_hcd),
					 "USB_PORT_FEAT_LINK_STATE req not "
					 "supported for USB 2.0 roothub\n");
				जाओ error;
			पूर्ण
			/*
			 * Since this is dummy we करोn't have an actual link so
			 * there is nothing to करो क्रम the SET_LINK_STATE cmd
			 */
			अवरोध;
		हाल USB_PORT_FEAT_U1_TIMEOUT:
		हाल USB_PORT_FEAT_U2_TIMEOUT:
			/* TODO: add suspend/resume support! */
			अगर (hcd->speed != HCD_USB3) अणु
				dev_dbg(dummy_dev(dum_hcd),
					 "USB_PORT_FEAT_U1/2_TIMEOUT req not "
					 "supported for USB 2.0 roothub\n");
				जाओ error;
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			/* Applicable only क्रम USB2.0 hub */
			अगर (hcd->speed == HCD_USB3) अणु
				dev_dbg(dummy_dev(dum_hcd),
					 "USB_PORT_FEAT_SUSPEND req not "
					 "supported for USB 3.0 roothub\n");
				जाओ error;
			पूर्ण
			अगर (dum_hcd->active) अणु
				dum_hcd->port_status |= USB_PORT_STAT_SUSPEND;

				/* HNP would happen here; क्रम now we
				 * assume b_bus_req is always true.
				 */
				set_link_state(dum_hcd);
				अगर (((1 << USB_DEVICE_B_HNP_ENABLE)
						& dum_hcd->dum->devstatus) != 0)
					dev_dbg(dummy_dev(dum_hcd),
							"no HNP yet!\n");
			पूर्ण
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			अगर (hcd->speed == HCD_USB3)
				dum_hcd->port_status |= USB_SS_PORT_STAT_POWER;
			अन्यथा
				dum_hcd->port_status |= USB_PORT_STAT_POWER;
			set_link_state(dum_hcd);
			अवरोध;
		हाल USB_PORT_FEAT_BH_PORT_RESET:
			/* Applicable only क्रम USB3.0 hub */
			अगर (hcd->speed != HCD_USB3) अणु
				dev_dbg(dummy_dev(dum_hcd),
					 "USB_PORT_FEAT_BH_PORT_RESET req not "
					 "supported for USB 2.0 roothub\n");
				जाओ error;
			पूर्ण
			fallthrough;
		हाल USB_PORT_FEAT_RESET:
			अगर (!(dum_hcd->port_status & USB_PORT_STAT_CONNECTION))
				अवरोध;
			/* अगर it's alपढ़ोy enabled, disable */
			अगर (hcd->speed == HCD_USB3) अणु
				dum_hcd->port_status =
					(USB_SS_PORT_STAT_POWER |
					 USB_PORT_STAT_CONNECTION |
					 USB_PORT_STAT_RESET);
			पूर्ण अन्यथा अणु
				dum_hcd->port_status &= ~(USB_PORT_STAT_ENABLE
					| USB_PORT_STAT_LOW_SPEED
					| USB_PORT_STAT_HIGH_SPEED);
				dum_hcd->port_status |= USB_PORT_STAT_RESET;
			पूर्ण
			/*
			 * We want to reset device status. All but the
			 * Self घातered feature
			 */
			dum_hcd->dum->devstatus &=
				(1 << USB_DEVICE_SELF_POWERED);
			/*
			 * FIXME USB3.0: what is the correct reset संकेतing
			 * पूर्णांकerval? Is it still 50msec as क्रम HS?
			 */
			dum_hcd->re_समयout = jअगरfies + msecs_to_jअगरfies(50);
			set_link_state(dum_hcd);
			अवरोध;
		हाल USB_PORT_FEAT_C_CONNECTION:
		हाल USB_PORT_FEAT_C_RESET:
		हाल USB_PORT_FEAT_C_ENABLE:
		हाल USB_PORT_FEAT_C_SUSPEND:
			/* Not allowed क्रम USB-3, and ignored क्रम USB-2 */
			अगर (hcd->speed == HCD_USB3)
				जाओ error;
			अवरोध;
		शेष:
		/* Disallow TEST, INDICATOR, and C_OVER_CURRENT */
			जाओ error;
		पूर्ण
		अवरोध;
	हाल GetPortErrorCount:
		अगर (hcd->speed != HCD_USB3) अणु
			dev_dbg(dummy_dev(dum_hcd),
				 "GetPortErrorCount req not "
				 "supported for USB 2.0 roothub\n");
			जाओ error;
		पूर्ण
		/* We'll always वापस 0 since this is a dummy hub */
		*(__le32 *) buf = cpu_to_le32(0);
		अवरोध;
	हाल SetHubDepth:
		अगर (hcd->speed != HCD_USB3) अणु
			dev_dbg(dummy_dev(dum_hcd),
				 "SetHubDepth req not supported for "
				 "USB 2.0 roothub\n");
			जाओ error;
		पूर्ण
		अवरोध;
	शेष:
		dev_dbg(dummy_dev(dum_hcd),
			"hub control req%04x v%04x i%04x l%d\n",
			typeReq, wValue, wIndex, wLength);
error:
		/* "protocol stall" on error */
		retval = -EPIPE;
	पूर्ण
	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);

	अगर ((dum_hcd->port_status & PORT_C_MASK) != 0)
		usb_hcd_poll_rh_status(hcd);
	वापस retval;
पूर्ण

अटल पूर्णांक dummy_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dummy_hcd *dum_hcd = hcd_to_dummy_hcd(hcd);

	dev_dbg(&hcd->self.root_hub->dev, "%s\n", __func__);

	spin_lock_irq(&dum_hcd->dum->lock);
	dum_hcd->rh_state = DUMMY_RH_SUSPENDED;
	set_link_state(dum_hcd);
	hcd->state = HC_STATE_SUSPENDED;
	spin_unlock_irq(&dum_hcd->dum->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dummy_hcd *dum_hcd = hcd_to_dummy_hcd(hcd);
	पूर्णांक rc = 0;

	dev_dbg(&hcd->self.root_hub->dev, "%s\n", __func__);

	spin_lock_irq(&dum_hcd->dum->lock);
	अगर (!HCD_HW_ACCESSIBLE(hcd)) अणु
		rc = -ESHUTDOWN;
	पूर्ण अन्यथा अणु
		dum_hcd->rh_state = DUMMY_RH_RUNNING;
		set_link_state(dum_hcd);
		अगर (!list_empty(&dum_hcd->urbp_list))
			mod_समयr(&dum_hcd->समयr, jअगरfies);
		hcd->state = HC_STATE_RUNNING;
	पूर्ण
	spin_unlock_irq(&dum_hcd->dum->lock);
	वापस rc;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत sमाप_प्रकार show_urb(अक्षर *buf, माप_प्रकार size, काष्ठा urb *urb)
अणु
	पूर्णांक ep = usb_pipeendpoपूर्णांक(urb->pipe);

	वापस scnम_लिखो(buf, size,
		"urb/%p %s ep%d%s%s len %d/%d\n",
		urb,
		(अणु अक्षर *s;
		चयन (urb->dev->speed) अणु
		हाल USB_SPEED_LOW:
			s = "ls";
			अवरोध;
		हाल USB_SPEED_FULL:
			s = "fs";
			अवरोध;
		हाल USB_SPEED_HIGH:
			s = "hs";
			अवरोध;
		हाल USB_SPEED_SUPER:
			s = "ss";
			अवरोध;
		शेष:
			s = "?";
			अवरोध;
		 पूर्ण s; पूर्ण),
		ep, ep ? (usb_urb_dir_in(urb) ? "in" : "out") : "",
		(अणु अक्षर *s; \
		चयन (usb_pipetype(urb->pipe)) अणु \
		हाल PIPE_CONTROL: \
			s = ""; \
			अवरोध; \
		हाल PIPE_BULK: \
			s = "-bulk"; \
			अवरोध; \
		हाल PIPE_INTERRUPT: \
			s = "-int"; \
			अवरोध; \
		शेष: \
			s = "-iso"; \
			अवरोध; \
		पूर्ण s; पूर्ण),
		urb->actual_length, urb->transfer_buffer_length);
पूर्ण

अटल sमाप_प्रकार urbs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा usb_hcd		*hcd = dev_get_drvdata(dev);
	काष्ठा dummy_hcd	*dum_hcd = hcd_to_dummy_hcd(hcd);
	काष्ठा urbp		*urbp;
	माप_प्रकार			size = 0;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dum_hcd->dum->lock, flags);
	list_क्रम_each_entry(urbp, &dum_hcd->urbp_list, urbp_list) अणु
		माप_प्रकार		temp;

		temp = show_urb(buf, PAGE_SIZE - size, urbp->urb);
		buf += temp;
		size += temp;
	पूर्ण
	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RO(urbs);

अटल पूर्णांक dummy_start_ss(काष्ठा dummy_hcd *dum_hcd)
अणु
	समयr_setup(&dum_hcd->समयr, dummy_समयr, 0);
	dum_hcd->rh_state = DUMMY_RH_RUNNING;
	dum_hcd->stream_en_ep = 0;
	INIT_LIST_HEAD(&dum_hcd->urbp_list);
	dummy_hcd_to_hcd(dum_hcd)->घातer_budget = POWER_BUDGET_3;
	dummy_hcd_to_hcd(dum_hcd)->state = HC_STATE_RUNNING;
	dummy_hcd_to_hcd(dum_hcd)->uses_new_polling = 1;
#अगर_घोषित CONFIG_USB_OTG
	dummy_hcd_to_hcd(dum_hcd)->self.otg_port = 1;
#पूर्ण_अगर
	वापस 0;

	/* FIXME 'urbs' should be a per-device thing, maybe in usbcore */
	वापस device_create_file(dummy_dev(dum_hcd), &dev_attr_urbs);
पूर्ण

अटल पूर्णांक dummy_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dummy_hcd	*dum_hcd = hcd_to_dummy_hcd(hcd);

	/*
	 * HOST side init ... we emulate a root hub that'll only ever
	 * talk to one device (the gadget side).  Also appears in sysfs,
	 * just like more familiar pci-based HCDs.
	 */
	अगर (!usb_hcd_is_primary_hcd(hcd))
		वापस dummy_start_ss(dum_hcd);

	spin_lock_init(&dum_hcd->dum->lock);
	समयr_setup(&dum_hcd->समयr, dummy_समयr, 0);
	dum_hcd->rh_state = DUMMY_RH_RUNNING;

	INIT_LIST_HEAD(&dum_hcd->urbp_list);

	hcd->घातer_budget = POWER_BUDGET;
	hcd->state = HC_STATE_RUNNING;
	hcd->uses_new_polling = 1;

#अगर_घोषित CONFIG_USB_OTG
	hcd->self.otg_port = 1;
#पूर्ण_अगर

	/* FIXME 'urbs' should be a per-device thing, maybe in usbcore */
	वापस device_create_file(dummy_dev(dum_hcd), &dev_attr_urbs);
पूर्ण

अटल व्योम dummy_stop(काष्ठा usb_hcd *hcd)
अणु
	device_हटाओ_file(dummy_dev(hcd_to_dummy_hcd(hcd)), &dev_attr_urbs);
	dev_info(dummy_dev(hcd_to_dummy_hcd(hcd)), "stopped\n");
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक dummy_h_get_frame(काष्ठा usb_hcd *hcd)
अणु
	वापस dummy_g_get_frame(शून्य);
पूर्ण

अटल पूर्णांक dummy_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा dummy *dum;

	dum = *((व्योम **)dev_get_platdata(hcd->self.controller));
	hcd->self.sg_tablesize = ~0;
	अगर (usb_hcd_is_primary_hcd(hcd)) अणु
		dum->hs_hcd = hcd_to_dummy_hcd(hcd);
		dum->hs_hcd->dum = dum;
		/*
		 * Mark the first roothub as being USB 2.0.
		 * The USB 3.0 roothub will be रेजिस्टरed later by
		 * dummy_hcd_probe()
		 */
		hcd->speed = HCD_USB2;
		hcd->self.root_hub->speed = USB_SPEED_HIGH;
	पूर्ण अन्यथा अणु
		dum->ss_hcd = hcd_to_dummy_hcd(hcd);
		dum->ss_hcd->dum = dum;
		hcd->speed = HCD_USB3;
		hcd->self.root_hub->speed = USB_SPEED_SUPER;
	पूर्ण
	वापस 0;
पूर्ण

/* Change a group of bulk endpoपूर्णांकs to support multiple stream IDs */
अटल पूर्णांक dummy_alloc_streams(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
	काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
	अचिन्हित पूर्णांक num_streams, gfp_t mem_flags)
अणु
	काष्ठा dummy_hcd *dum_hcd = hcd_to_dummy_hcd(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक max_stream;
	पूर्णांक ret_streams = num_streams;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक i;

	अगर (!num_eps)
		वापस -EINVAL;

	spin_lock_irqsave(&dum_hcd->dum->lock, flags);
	क्रम (i = 0; i < num_eps; i++) अणु
		index = dummy_get_ep_idx(&eps[i]->desc);
		अगर ((1 << index) & dum_hcd->stream_en_ep) अणु
			ret_streams = -EINVAL;
			जाओ out;
		पूर्ण
		max_stream = usb_ss_max_streams(&eps[i]->ss_ep_comp);
		अगर (!max_stream) अणु
			ret_streams = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (max_stream < ret_streams) अणु
			dev_dbg(dummy_dev(dum_hcd), "Ep 0x%x only supports %u "
					"stream IDs.\n",
					eps[i]->desc.bEndpoपूर्णांकAddress,
					max_stream);
			ret_streams = max_stream;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_eps; i++) अणु
		index = dummy_get_ep_idx(&eps[i]->desc);
		dum_hcd->stream_en_ep |= 1 << index;
		set_max_streams_क्रम_pipe(dum_hcd,
				usb_endpoपूर्णांक_num(&eps[i]->desc), ret_streams);
	पूर्ण
out:
	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);
	वापस ret_streams;
पूर्ण

/* Reverts a group of bulk endpoपूर्णांकs back to not using stream IDs. */
अटल पूर्णांक dummy_मुक्त_streams(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
	काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
	gfp_t mem_flags)
अणु
	काष्ठा dummy_hcd *dum_hcd = hcd_to_dummy_hcd(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&dum_hcd->dum->lock, flags);
	क्रम (i = 0; i < num_eps; i++) अणु
		index = dummy_get_ep_idx(&eps[i]->desc);
		अगर (!((1 << index) & dum_hcd->stream_en_ep)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_eps; i++) अणु
		index = dummy_get_ep_idx(&eps[i]->desc);
		dum_hcd->stream_en_ep &= ~(1 << index);
		set_max_streams_क्रम_pipe(dum_hcd,
				usb_endpoपूर्णांक_num(&eps[i]->desc), 0);
	पूर्ण
	ret = 0;
out:
	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);
	वापस ret;
पूर्ण

अटल काष्ठा hc_driver dummy_hcd = अणु
	.description =		(अक्षर *) driver_name,
	.product_desc =		"Dummy host controller",
	.hcd_priv_size =	माप(काष्ठा dummy_hcd),

	.reset =		dummy_setup,
	.start =		dummy_start,
	.stop =			dummy_stop,

	.urb_enqueue =		dummy_urb_enqueue,
	.urb_dequeue =		dummy_urb_dequeue,

	.get_frame_number =	dummy_h_get_frame,

	.hub_status_data =	dummy_hub_status,
	.hub_control =		dummy_hub_control,
	.bus_suspend =		dummy_bus_suspend,
	.bus_resume =		dummy_bus_resume,

	.alloc_streams =	dummy_alloc_streams,
	.मुक्त_streams =		dummy_मुक्त_streams,
पूर्ण;

अटल पूर्णांक dummy_hcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dummy		*dum;
	काष्ठा usb_hcd		*hs_hcd;
	काष्ठा usb_hcd		*ss_hcd;
	पूर्णांक			retval;

	dev_info(&pdev->dev, "%s, driver " DRIVER_VERSION "\n", driver_desc);
	dum = *((व्योम **)dev_get_platdata(&pdev->dev));

	अगर (mod_data.is_super_speed)
		dummy_hcd.flags = HCD_USB3 | HCD_SHARED;
	अन्यथा अगर (mod_data.is_high_speed)
		dummy_hcd.flags = HCD_USB2;
	अन्यथा
		dummy_hcd.flags = HCD_USB11;
	hs_hcd = usb_create_hcd(&dummy_hcd, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hs_hcd)
		वापस -ENOMEM;
	hs_hcd->has_tt = 1;

	retval = usb_add_hcd(hs_hcd, 0, 0);
	अगर (retval)
		जाओ put_usb2_hcd;

	अगर (mod_data.is_super_speed) अणु
		ss_hcd = usb_create_shared_hcd(&dummy_hcd, &pdev->dev,
					dev_name(&pdev->dev), hs_hcd);
		अगर (!ss_hcd) अणु
			retval = -ENOMEM;
			जाओ dealloc_usb2_hcd;
		पूर्ण

		retval = usb_add_hcd(ss_hcd, 0, 0);
		अगर (retval)
			जाओ put_usb3_hcd;
	पूर्ण
	वापस 0;

put_usb3_hcd:
	usb_put_hcd(ss_hcd);
dealloc_usb2_hcd:
	usb_हटाओ_hcd(hs_hcd);
put_usb2_hcd:
	usb_put_hcd(hs_hcd);
	dum->hs_hcd = dum->ss_hcd = शून्य;
	वापस retval;
पूर्ण

अटल पूर्णांक dummy_hcd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dummy		*dum;

	dum = hcd_to_dummy_hcd(platक्रमm_get_drvdata(pdev))->dum;

	अगर (dum->ss_hcd) अणु
		usb_हटाओ_hcd(dummy_hcd_to_hcd(dum->ss_hcd));
		usb_put_hcd(dummy_hcd_to_hcd(dum->ss_hcd));
	पूर्ण

	usb_हटाओ_hcd(dummy_hcd_to_hcd(dum->hs_hcd));
	usb_put_hcd(dummy_hcd_to_hcd(dum->hs_hcd));

	dum->hs_hcd = शून्य;
	dum->ss_hcd = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक dummy_hcd_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा usb_hcd		*hcd;
	काष्ठा dummy_hcd	*dum_hcd;
	पूर्णांक			rc = 0;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	hcd = platक्रमm_get_drvdata(pdev);
	dum_hcd = hcd_to_dummy_hcd(hcd);
	अगर (dum_hcd->rh_state == DUMMY_RH_RUNNING) अणु
		dev_warn(&pdev->dev, "Root hub isn't suspended!\n");
		rc = -EBUSY;
	पूर्ण अन्यथा
		clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	वापस rc;
पूर्ण

अटल पूर्णांक dummy_hcd_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd		*hcd;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	hcd = platक्रमm_get_drvdata(pdev);
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	usb_hcd_poll_rh_status(hcd);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dummy_hcd_driver = अणु
	.probe		= dummy_hcd_probe,
	.हटाओ		= dummy_hcd_हटाओ,
	.suspend	= dummy_hcd_suspend,
	.resume		= dummy_hcd_resume,
	.driver		= अणु
		.name	= driver_name,
	पूर्ण,
पूर्ण;

/*-------------------------------------------------------------------------*/
#घोषणा MAX_NUM_UDC	32
अटल काष्ठा platक्रमm_device *the_udc_pdev[MAX_NUM_UDC];
अटल काष्ठा platक्रमm_device *the_hcd_pdev[MAX_NUM_UDC];

अटल पूर्णांक __init init(व्योम)
अणु
	पूर्णांक	retval = -ENOMEM;
	पूर्णांक	i;
	काष्ठा	dummy *dum[MAX_NUM_UDC] = अणुपूर्ण;

	अगर (usb_disabled())
		वापस -ENODEV;

	अगर (!mod_data.is_high_speed && mod_data.is_super_speed)
		वापस -EINVAL;

	अगर (mod_data.num < 1 || mod_data.num > MAX_NUM_UDC) अणु
		pr_err("Number of emulated UDC must be in range of 1...%d\n",
				MAX_NUM_UDC);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < mod_data.num; i++) अणु
		the_hcd_pdev[i] = platक्रमm_device_alloc(driver_name, i);
		अगर (!the_hcd_pdev[i]) अणु
			i--;
			जबतक (i >= 0)
				platक्रमm_device_put(the_hcd_pdev[i--]);
			वापस retval;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < mod_data.num; i++) अणु
		the_udc_pdev[i] = platक्रमm_device_alloc(gadget_name, i);
		अगर (!the_udc_pdev[i]) अणु
			i--;
			जबतक (i >= 0)
				platक्रमm_device_put(the_udc_pdev[i--]);
			जाओ err_alloc_udc;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < mod_data.num; i++) अणु
		dum[i] = kzalloc(माप(काष्ठा dummy), GFP_KERNEL);
		अगर (!dum[i]) अणु
			retval = -ENOMEM;
			जाओ err_add_pdata;
		पूर्ण
		retval = platक्रमm_device_add_data(the_hcd_pdev[i], &dum[i],
				माप(व्योम *));
		अगर (retval)
			जाओ err_add_pdata;
		retval = platक्रमm_device_add_data(the_udc_pdev[i], &dum[i],
				माप(व्योम *));
		अगर (retval)
			जाओ err_add_pdata;
	पूर्ण

	retval = platक्रमm_driver_रेजिस्टर(&dummy_hcd_driver);
	अगर (retval < 0)
		जाओ err_add_pdata;
	retval = platक्रमm_driver_रेजिस्टर(&dummy_udc_driver);
	अगर (retval < 0)
		जाओ err_रेजिस्टर_udc_driver;

	क्रम (i = 0; i < mod_data.num; i++) अणु
		retval = platक्रमm_device_add(the_hcd_pdev[i]);
		अगर (retval < 0) अणु
			i--;
			जबतक (i >= 0)
				platक्रमm_device_del(the_hcd_pdev[i--]);
			जाओ err_add_hcd;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < mod_data.num; i++) अणु
		अगर (!dum[i]->hs_hcd ||
				(!dum[i]->ss_hcd && mod_data.is_super_speed)) अणु
			/*
			 * The hcd was added successfully but its probe
			 * function failed क्रम some reason.
			 */
			retval = -EINVAL;
			जाओ err_add_udc;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < mod_data.num; i++) अणु
		retval = platक्रमm_device_add(the_udc_pdev[i]);
		अगर (retval < 0) अणु
			i--;
			जबतक (i >= 0)
				platक्रमm_device_del(the_udc_pdev[i--]);
			जाओ err_add_udc;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < mod_data.num; i++) अणु
		अगर (!platक्रमm_get_drvdata(the_udc_pdev[i])) अणु
			/*
			 * The udc was added successfully but its probe
			 * function failed क्रम some reason.
			 */
			retval = -EINVAL;
			जाओ err_probe_udc;
		पूर्ण
	पूर्ण
	वापस retval;

err_probe_udc:
	क्रम (i = 0; i < mod_data.num; i++)
		platक्रमm_device_del(the_udc_pdev[i]);
err_add_udc:
	क्रम (i = 0; i < mod_data.num; i++)
		platक्रमm_device_del(the_hcd_pdev[i]);
err_add_hcd:
	platक्रमm_driver_unरेजिस्टर(&dummy_udc_driver);
err_रेजिस्टर_udc_driver:
	platक्रमm_driver_unरेजिस्टर(&dummy_hcd_driver);
err_add_pdata:
	क्रम (i = 0; i < mod_data.num; i++)
		kमुक्त(dum[i]);
	क्रम (i = 0; i < mod_data.num; i++)
		platक्रमm_device_put(the_udc_pdev[i]);
err_alloc_udc:
	क्रम (i = 0; i < mod_data.num; i++)
		platक्रमm_device_put(the_hcd_pdev[i]);
	वापस retval;
पूर्ण
module_init(init);

अटल व्योम __निकास cleanup(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mod_data.num; i++) अणु
		काष्ठा dummy *dum;

		dum = *((व्योम **)dev_get_platdata(&the_udc_pdev[i]->dev));

		platक्रमm_device_unरेजिस्टर(the_udc_pdev[i]);
		platक्रमm_device_unरेजिस्टर(the_hcd_pdev[i]);
		kमुक्त(dum);
	पूर्ण
	platक्रमm_driver_unरेजिस्टर(&dummy_udc_driver);
	platक्रमm_driver_unरेजिस्टर(&dummy_hcd_driver);
पूर्ण
module_निकास(cleanup);
