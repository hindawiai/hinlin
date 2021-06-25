<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * epस्वतःconf.c -- endpoपूर्णांक स्वतःconfiguration क्रम usb gadget drivers
 *
 * Copyright (C) 2004 David Brownell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>

#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

/**
 * usb_ep_स्वतःconfig_ss() - choose an endpoपूर्णांक matching the ep
 * descriptor and ep companion descriptor
 * @gadget: The device to which the endpoपूर्णांक must beदीर्घ.
 * @desc: Endpoपूर्णांक descriptor, with endpoपूर्णांक direction and transfer mode
 *    initialized.  For periodic transfers, the maximum packet
 *    size must also be initialized.  This is modअगरied on
 *    success.
 * @ep_comp: Endpoपूर्णांक companion descriptor, with the required
 *    number of streams. Will be modअगरied when the chosen EP
 *    supports a dअगरferent number of streams.
 *
 * This routine replaces the usb_ep_स्वतःconfig when needed
 * superspeed enhancments. If such enhancemnets are required,
 * the FD should call usb_ep_स्वतःconfig_ss directly and provide
 * the additional ep_comp parameter.
 *
 * By choosing an endpoपूर्णांक to use with the specअगरied descriptor,
 * this routine simplअगरies writing gadget drivers that work with
 * multiple USB device controllers.  The endpoपूर्णांक would be
 * passed later to usb_ep_enable(), aदीर्घ with some descriptor.
 *
 * That second descriptor won't always be the same as the first one.
 * For example, isochronous endpoपूर्णांकs can be स्वतःconfigured क्रम high
 * bandwidth, and then used in several lower bandwidth altsettings.
 * Also, high and full speed descriptors will be dअगरferent.
 *
 * Be sure to examine and test the results of स्वतःconfiguration
 * on your hardware.  This code may not make the best choices
 * about how to use the USB controller, and it can't know all
 * the restrictions that may apply. Some combinations of driver
 * and hardware won't be able to स्वतःconfigure.
 *
 * On success, this वापसs an claimed usb_ep, and modअगरies the endpoपूर्णांक
 * descriptor bEndpoपूर्णांकAddress.  For bulk endpoपूर्णांकs, the wMaxPacket value
 * is initialized as अगर the endpoपूर्णांक were used at full speed and
 * the bmAttribute field in the ep companion descriptor is
 * updated with the asचिन्हित number of streams अगर it is
 * dअगरferent from the original value. To prevent the endpoपूर्णांक
 * from being वापसed by a later स्वतःconfig call, claims it by
 * assigning ep->claimed to true.
 *
 * On failure, this वापसs a null endpoपूर्णांक descriptor.
 */
काष्ठा usb_ep *usb_ep_स्वतःconfig_ss(
	काष्ठा usb_gadget		*gadget,
	काष्ठा usb_endpoपूर्णांक_descriptor	*desc,
	काष्ठा usb_ss_ep_comp_descriptor *ep_comp
)
अणु
	काष्ठा usb_ep	*ep;

	अगर (gadget->ops->match_ep) अणु
		ep = gadget->ops->match_ep(gadget, desc, ep_comp);
		अगर (ep)
			जाओ found_ep;
	पूर्ण

	/* Second, look at endpoपूर्णांकs until an unclaimed one looks usable */
	list_क्रम_each_entry (ep, &gadget->ep_list, ep_list) अणु
		अगर (usb_gadget_ep_match_desc(gadget, ep, desc, ep_comp))
			जाओ found_ep;
	पूर्ण

	/* Fail */
	वापस शून्य;
found_ep:

	/*
	 * If the protocol driver hasn't yet decided on wMaxPacketSize
	 * and wants to know the maximum possible, provide the info.
	 */
	अगर (desc->wMaxPacketSize == 0)
		desc->wMaxPacketSize = cpu_to_le16(ep->maxpacket_limit);

	/* report address */
	desc->bEndpoपूर्णांकAddress &= USB_सूची_IN;
	अगर (है_अंक(ep->name[2])) अणु
		u8 num = simple_म_से_अदीर्घ(&ep->name[2], शून्य, 10);
		desc->bEndpoपूर्णांकAddress |= num;
	पूर्ण अन्यथा अगर (desc->bEndpoपूर्णांकAddress & USB_सूची_IN) अणु
		अगर (++gadget->in_epnum > 15)
			वापस शून्य;
		desc->bEndpoपूर्णांकAddress = USB_सूची_IN | gadget->in_epnum;
	पूर्ण अन्यथा अणु
		अगर (++gadget->out_epnum > 15)
			वापस शून्य;
		desc->bEndpoपूर्णांकAddress |= gadget->out_epnum;
	पूर्ण

	ep->address = desc->bEndpoपूर्णांकAddress;
	ep->desc = शून्य;
	ep->comp_desc = शून्य;
	ep->claimed = true;
	वापस ep;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_स्वतःconfig_ss);

/**
 * usb_ep_स्वतःconfig() - choose an endpoपूर्णांक matching the
 * descriptor
 * @gadget: The device to which the endpoपूर्णांक must beदीर्घ.
 * @desc: Endpoपूर्णांक descriptor, with endpoपूर्णांक direction and transfer mode
 *	initialized.  For periodic transfers, the maximum packet
 *	size must also be initialized.  This is modअगरied on success.
 *
 * By choosing an endpoपूर्णांक to use with the specअगरied descriptor, this
 * routine simplअगरies writing gadget drivers that work with multiple
 * USB device controllers.  The endpoपूर्णांक would be passed later to
 * usb_ep_enable(), aदीर्घ with some descriptor.
 *
 * That second descriptor won't always be the same as the first one.
 * For example, isochronous endpoपूर्णांकs can be स्वतःconfigured क्रम high
 * bandwidth, and then used in several lower bandwidth altsettings.
 * Also, high and full speed descriptors will be dअगरferent.
 *
 * Be sure to examine and test the results of स्वतःconfiguration on your
 * hardware.  This code may not make the best choices about how to use the
 * USB controller, and it can't know all the restrictions that may apply.
 * Some combinations of driver and hardware won't be able to स्वतःconfigure.
 *
 * On success, this वापसs an claimed usb_ep, and modअगरies the endpoपूर्णांक
 * descriptor bEndpoपूर्णांकAddress.  For bulk endpoपूर्णांकs, the wMaxPacket value
 * is initialized as अगर the endpoपूर्णांक were used at full speed. Because of
 * that the users must consider adjusting the स्वतःconfigured descriptor.
 * To prevent the endpoपूर्णांक from being वापसed by a later स्वतःconfig call,
 * claims it by assigning ep->claimed to true.
 *
 * On failure, this वापसs a null endpoपूर्णांक descriptor.
 */
काष्ठा usb_ep *usb_ep_स्वतःconfig(
	काष्ठा usb_gadget		*gadget,
	काष्ठा usb_endpoपूर्णांक_descriptor	*desc
)
अणु
	काष्ठा usb_ep	*ep;
	u8		type;

	ep = usb_ep_स्वतःconfig_ss(gadget, desc, शून्य);
	अगर (!ep)
		वापस शून्य;

	type = desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;

	/* report (variable) full speed bulk maxpacket */
	अगर (type == USB_ENDPOINT_XFER_BULK) अणु
		पूर्णांक size = ep->maxpacket_limit;

		/* min() करोesn't work on bitfields with gcc-3.5 */
		अगर (size > 64)
			size = 64;
		desc->wMaxPacketSize = cpu_to_le16(size);
	पूर्ण

	वापस ep;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_स्वतःconfig);

/**
 * usb_ep_स्वतःconfig_release - releases endpoपूर्णांक and set it to initial state
 * @ep: endpoपूर्णांक which should be released
 *
 * This function can be used during function bind क्रम endpoपूर्णांकs obtained
 * from usb_ep_स्वतःconfig(). It unclaims endpoपूर्णांक claimed by
 * usb_ep_स्वतःconfig() to make it available क्रम other functions. Endpoपूर्णांक
 * which was released is no दीर्घer invalid and shouldn't be used in
 * context of function which released it.
 */
व्योम usb_ep_स्वतःconfig_release(काष्ठा usb_ep *ep)
अणु
	ep->claimed = false;
	ep->driver_data = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_स्वतःconfig_release);

/**
 * usb_ep_स्वतःconfig_reset - reset endpoपूर्णांक स्वतःconfig state
 * @gadget: device क्रम which स्वतःconfig state will be reset
 *
 * Use this क्रम devices where one configuration may need to assign
 * endpoपूर्णांक resources very dअगरferently from the next one.  It clears
 * state such as ep->claimed and the record of asचिन्हित endpoपूर्णांकs
 * used by usb_ep_स्वतःconfig().
 */
व्योम usb_ep_स्वतःconfig_reset (काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_ep	*ep;

	list_क्रम_each_entry (ep, &gadget->ep_list, ep_list) अणु
		ep->claimed = false;
		ep->driver_data = शून्य;
	पूर्ण
	gadget->in_epnum = 0;
	gadget->out_epnum = 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_स्वतःconfig_reset);
