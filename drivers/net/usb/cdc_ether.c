<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CDC Ethernet based networking peripherals
 * Copyright (C) 2003-2005 by David Brownell
 * Copyright (C) 2006 by Ole Andre Vadla Ravnas (ActiveSync)
 */

// #घोषणा	DEBUG			// error path messages, extra info
// #घोषणा	VERBOSE			// more; success messages

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>


#अगर IS_ENABLED(CONFIG_USB_NET_RNDIS_HOST)

अटल पूर्णांक is_rndis(काष्ठा usb_पूर्णांकerface_descriptor *desc)
अणु
	वापस (desc->bInterfaceClass == USB_CLASS_COMM &&
		desc->bInterfaceSubClass == 2 &&
		desc->bInterfaceProtocol == 0xff);
पूर्ण

अटल पूर्णांक is_activesync(काष्ठा usb_पूर्णांकerface_descriptor *desc)
अणु
	वापस (desc->bInterfaceClass == USB_CLASS_MISC &&
		desc->bInterfaceSubClass == 1 &&
		desc->bInterfaceProtocol == 1);
पूर्ण

अटल पूर्णांक is_wireless_rndis(काष्ठा usb_पूर्णांकerface_descriptor *desc)
अणु
	वापस (desc->bInterfaceClass == USB_CLASS_WIRELESS_CONTROLLER &&
		desc->bInterfaceSubClass == 1 &&
		desc->bInterfaceProtocol == 3);
पूर्ण

अटल पूर्णांक is_novatel_rndis(काष्ठा usb_पूर्णांकerface_descriptor *desc)
अणु
	वापस (desc->bInterfaceClass == USB_CLASS_MISC &&
		desc->bInterfaceSubClass == 4 &&
		desc->bInterfaceProtocol == 1);
पूर्ण

#अन्यथा

#घोषणा is_rndis(desc)		0
#घोषणा is_activesync(desc)	0
#घोषणा is_wireless_rndis(desc)	0
#घोषणा is_novatel_rndis(desc)	0

#पूर्ण_अगर

अटल स्थिर u8 mbm_guid[16] = अणु
	0xa3, 0x17, 0xa8, 0x8b, 0x04, 0x5e, 0x4f, 0x01,
	0xa6, 0x07, 0xc0, 0xff, 0xcb, 0x7e, 0x39, 0x2a,
पूर्ण;

व्योम usbnet_cdc_update_filter(काष्ठा usbnet *dev)
अणु
	काष्ठा net_device	*net = dev->net;

	u16 cdc_filter = USB_CDC_PACKET_TYPE_सूचीECTED
			| USB_CDC_PACKET_TYPE_BROADCAST;

	/* filtering on the device is an optional feature and not worth
	 * the hassle so we just roughly care about snooping and अगर any
	 * multicast is requested, we take every multicast
	 */
	अगर (net->flags & IFF_PROMISC)
		cdc_filter |= USB_CDC_PACKET_TYPE_PROMISCUOUS;
	अगर (!netdev_mc_empty(net) || (net->flags & IFF_ALLMULTI))
		cdc_filter |= USB_CDC_PACKET_TYPE_ALL_MULTICAST;

	usb_control_msg(dev->udev,
			usb_sndctrlpipe(dev->udev, 0),
			USB_CDC_SET_ETHERNET_PACKET_FILTER,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			cdc_filter,
			dev->पूर्णांकf->cur_altsetting->desc.bInterfaceNumber,
			शून्य,
			0,
			USB_CTRL_SET_TIMEOUT
		);
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_cdc_update_filter);

/* We need to override usbnet_*_link_ksettings in bind() */
अटल स्थिर काष्ठा ethtool_ops cdc_ether_ethtool_ops = अणु
	.get_link		= usbnet_get_link,
	.nway_reset		= usbnet_nway_reset,
	.get_drvinfo		= usbnet_get_drvinfo,
	.get_msglevel		= usbnet_get_msglevel,
	.set_msglevel		= usbnet_set_msglevel,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_link_ksettings	= usbnet_get_link_ksettings_पूर्णांकernal,
	.set_link_ksettings	= शून्य,
पूर्ण;

/* probes control पूर्णांकerface, claims data पूर्णांकerface, collects the bulk
 * endpoपूर्णांकs, activates data पूर्णांकerface (अगर needed), maybe sets MTU.
 * all pure cdc, except क्रम certain firmware workarounds, and knowing
 * that rndis uses one dअगरferent rule.
 */
पूर्णांक usbnet_generic_cdc_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	u8				*buf = पूर्णांकf->cur_altsetting->extra;
	पूर्णांक				len = पूर्णांकf->cur_altsetting->extralen;
	काष्ठा usb_पूर्णांकerface_descriptor	*d;
	काष्ठा cdc_state		*info = (व्योम *) &dev->data;
	पूर्णांक				status;
	पूर्णांक				rndis;
	bool				android_rndis_quirk = false;
	काष्ठा usb_driver		*driver = driver_of(पूर्णांकf);
	काष्ठा usb_cdc_parsed_header header;

	अगर (माप(dev->data) < माप(*info))
		वापस -गलत_तर्क;

	/* expect strict spec conक्रमmance क्रम the descriptors, but
	 * cope with firmware which stores them in the wrong place
	 */
	अगर (len == 0 && dev->udev->actconfig->extralen) अणु
		/* Motorola SB4100 (and others: Brad Hards says it's
		 * from a Broadcom design) put CDC descriptors here
		 */
		buf = dev->udev->actconfig->extra;
		len = dev->udev->actconfig->extralen;
		dev_dbg(&पूर्णांकf->dev, "CDC descriptors on config\n");
	पूर्ण

	/* Maybe CDC descriptors are after the endpoपूर्णांक?  This bug has
	 * been seen on some 2Wire Inc RNDIS-ish products.
	 */
	अगर (len == 0) अणु
		काष्ठा usb_host_endpoपूर्णांक	*hep;

		hep = पूर्णांकf->cur_altsetting->endpoपूर्णांक;
		अगर (hep) अणु
			buf = hep->extra;
			len = hep->extralen;
		पूर्ण
		अगर (len)
			dev_dbg(&पूर्णांकf->dev,
				"CDC descriptors on endpoint\n");
	पूर्ण

	/* this assumes that अगर there's a non-RNDIS venकरोr variant
	 * of cdc-acm, it'll fail RNDIS requests cleanly.
	 */
	rndis = (is_rndis(&पूर्णांकf->cur_altsetting->desc) ||
		 is_activesync(&पूर्णांकf->cur_altsetting->desc) ||
		 is_wireless_rndis(&पूर्णांकf->cur_altsetting->desc) ||
		 is_novatel_rndis(&पूर्णांकf->cur_altsetting->desc));

	स_रखो(info, 0, माप(*info));
	info->control = पूर्णांकf;

	cdc_parse_cdc_header(&header, पूर्णांकf, buf, len);

	info->u = header.usb_cdc_जोड़_desc;
	info->header = header.usb_cdc_header_desc;
	info->ether = header.usb_cdc_ether_desc;
	अगर (!info->u) अणु
		अगर (rndis)
			जाओ skip;
		अन्यथा /* in that हाल a quirk is mandatory */
			जाओ bad_desc;
	पूर्ण
	/* we need a master/control पूर्णांकerface (what we're
	 * probed with) and a slave/data पूर्णांकerface; जोड़
	 * descriptors sort this all out.
	 */
	info->control = usb_अगरnum_to_अगर(dev->udev, info->u->bMasterInterface0);
	info->data = usb_अगरnum_to_अगर(dev->udev, info->u->bSlaveInterface0);
	अगर (!info->control || !info->data) अणु
		dev_dbg(&पूर्णांकf->dev,
			"master #%u/%p slave #%u/%p\n",
			info->u->bMasterInterface0,
			info->control,
			info->u->bSlaveInterface0,
			info->data);
		/* fall back to hard-wiring क्रम RNDIS */
		अगर (rndis) अणु
			android_rndis_quirk = true;
			जाओ skip;
		पूर्ण
		जाओ bad_desc;
	पूर्ण
	अगर (info->control != पूर्णांकf) अणु
		dev_dbg(&पूर्णांकf->dev, "bogus CDC Union\n");
		/* Ambit USB Cable Modem (and maybe others)
		 * पूर्णांकerchanges master and slave पूर्णांकerface.
		 */
		अगर (info->data == पूर्णांकf) अणु
			info->data = info->control;
			info->control = पूर्णांकf;
		पूर्ण अन्यथा
			जाओ bad_desc;
	पूर्ण

	/* some devices merge these - skip class check */
	अगर (info->control == info->data)
		जाओ skip;

	/* a data पूर्णांकerface altsetting करोes the real i/o */
	d = &info->data->cur_altsetting->desc;
	अगर (d->bInterfaceClass != USB_CLASS_CDC_DATA) अणु
		dev_dbg(&पूर्णांकf->dev, "slave class %u\n", d->bInterfaceClass);
		जाओ bad_desc;
	पूर्ण
skip:
	/* Communcation class functions with bmCapabilities are not
	 * RNDIS.  But some Wireless class RNDIS functions use
	 * bmCapabilities क्रम their own purpose. The failsafe is
	 * thereक्रमe applied only to Communication class RNDIS
	 * functions.  The rndis test is redundant, but a cheap
	 * optimization.
	 */
	अगर (rndis && is_rndis(&पूर्णांकf->cur_altsetting->desc) &&
	    header.usb_cdc_acm_descriptor &&
	    header.usb_cdc_acm_descriptor->bmCapabilities) अणु
		dev_dbg(&पूर्णांकf->dev,
			"ACM capabilities %02x, not really RNDIS?\n",
			header.usb_cdc_acm_descriptor->bmCapabilities);
		जाओ bad_desc;
	पूर्ण

	अगर (header.usb_cdc_ether_desc && info->ether->wMaxSegmentSize) अणु
		dev->hard_mtu = le16_to_cpu(info->ether->wMaxSegmentSize);
		/* because of Zaurus, we may be ignoring the host
		 * side link address we were given.
		 */
	पूर्ण

	अगर (header.usb_cdc_mdlm_desc &&
	    स_भेद(header.usb_cdc_mdlm_desc->bGUID, mbm_guid, 16)) अणु
		dev_dbg(&पूर्णांकf->dev, "GUID doesn't match\n");
		जाओ bad_desc;
	पूर्ण

	अगर (header.usb_cdc_mdlm_detail_desc &&
		header.usb_cdc_mdlm_detail_desc->bLength <
			(माप(काष्ठा usb_cdc_mdlm_detail_desc) + 1)) अणु
		dev_dbg(&पूर्णांकf->dev, "Descriptor too short\n");
		जाओ bad_desc;
	पूर्ण



	/* Microsoft ActiveSync based and some regular RNDIS devices lack the
	 * CDC descriptors, so we'll hard-wire the पूर्णांकerfaces and not check
	 * क्रम descriptors.
	 *
	 * Some Android RNDIS devices have a CDC Union descriptor poपूर्णांकing
	 * to non-existing पूर्णांकerfaces.  Ignore that and attempt the same
	 * hard-wired 0 and 1 पूर्णांकerfaces.
	 */
	अगर (rndis && (!info->u || android_rndis_quirk)) अणु
		info->control = usb_अगरnum_to_अगर(dev->udev, 0);
		info->data = usb_अगरnum_to_अगर(dev->udev, 1);
		अगर (!info->control || !info->data || info->control != पूर्णांकf) अणु
			dev_dbg(&पूर्णांकf->dev,
				"rndis: master #0/%p slave #1/%p\n",
				info->control,
				info->data);
			जाओ bad_desc;
		पूर्ण

	पूर्ण अन्यथा अगर (!info->header || (!rndis && !info->ether)) अणु
		dev_dbg(&पूर्णांकf->dev, "missing cdc %s%s%sdescriptor\n",
			info->header ? "" : "header ",
			info->u ? "" : "union ",
			info->ether ? "" : "ether ");
		जाओ bad_desc;
	पूर्ण

	/* claim data पूर्णांकerface and set it up ... with side effects.
	 * network traffic can't flow until an altsetting is enabled.
	 */
	अगर (info->data != info->control) अणु
		status = usb_driver_claim_पूर्णांकerface(driver, info->data, dev);
		अगर (status < 0)
			वापस status;
	पूर्ण
	status = usbnet_get_endpoपूर्णांकs(dev, info->data);
	अगर (status < 0) अणु
		/* ensure immediate निकास from usbnet_disconnect */
		usb_set_पूर्णांकfdata(info->data, शून्य);
		अगर (info->data != info->control)
			usb_driver_release_पूर्णांकerface(driver, info->data);
		वापस status;
	पूर्ण

	/* status endpoपूर्णांक: optional क्रम CDC Ethernet, not RNDIS (or ACM) */
	अगर (info->data != info->control)
		dev->status = शून्य;
	अगर (info->control->cur_altsetting->desc.bNumEndpoपूर्णांकs == 1) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor	*desc;

		dev->status = &info->control->cur_altsetting->endpoपूर्णांक[0];
		desc = &dev->status->desc;
		अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(desc) ||
		    (le16_to_cpu(desc->wMaxPacketSize)
		     < माप(काष्ठा usb_cdc_notअगरication)) ||
		    !desc->bInterval) अणु
			dev_dbg(&पूर्णांकf->dev, "bad notification endpoint\n");
			dev->status = शून्य;
		पूर्ण
	पूर्ण
	अगर (rndis && !dev->status) अणु
		dev_dbg(&पूर्णांकf->dev, "missing RNDIS status endpoint\n");
		usb_set_पूर्णांकfdata(info->data, शून्य);
		usb_driver_release_पूर्णांकerface(driver, info->data);
		वापस -ENODEV;
	पूर्ण

	/* override ethtool_ops */
	dev->net->ethtool_ops = &cdc_ether_ethtool_ops;

	वापस 0;

bad_desc:
	dev_info(&dev->udev->dev, "bad CDC descriptors\n");
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_generic_cdc_bind);


/* like usbnet_generic_cdc_bind() but handles filter initialization
 * correctly
 */
पूर्णांक usbnet_ether_cdc_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक rv;

	rv = usbnet_generic_cdc_bind(dev, पूर्णांकf);
	अगर (rv < 0)
		जाओ bail_out;

	/* Some devices करोn't initialise properly. In particular
	 * the packet filter is not reset. There are devices that
	 * करोn't करो reset all the way. So the packet filter should
	 * be set to a sane initial value.
	 */
	usbnet_cdc_update_filter(dev);

bail_out:
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_ether_cdc_bind);

व्योम usbnet_cdc_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cdc_state		*info = (व्योम *) &dev->data;
	काष्ठा usb_driver		*driver = driver_of(पूर्णांकf);

	/* combined पूर्णांकerface - nothing  to करो */
	अगर (info->data == info->control)
		वापस;

	/* disconnect master --> disconnect slave */
	अगर (पूर्णांकf == info->control && info->data) अणु
		/* ensure immediate निकास from usbnet_disconnect */
		usb_set_पूर्णांकfdata(info->data, शून्य);
		usb_driver_release_पूर्णांकerface(driver, info->data);
		info->data = शून्य;
	पूर्ण

	/* and vice versa (just in हाल) */
	अन्यथा अगर (पूर्णांकf == info->data && info->control) अणु
		/* ensure immediate निकास from usbnet_disconnect */
		usb_set_पूर्णांकfdata(info->control, शून्य);
		usb_driver_release_पूर्णांकerface(driver, info->control);
		info->control = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_cdc_unbind);

/* Communications Device Class, Ethernet Control model
 *
 * Takes two पूर्णांकerfaces.  The DATA पूर्णांकerface is inactive till an altsetting
 * is selected.  Configuration data includes class descriptors.  There's
 * an optional status endpoपूर्णांक on the control पूर्णांकerface.
 *
 * This should पूर्णांकerop with whatever the 2.4 "CDCEther.c" driver
 * (by Brad Hards) talked with, with more functionality.
 */

अटल व्योम speed_change(काष्ठा usbnet *dev, __le32 *speeds)
अणु
	dev->tx_speed = __le32_to_cpu(speeds[0]);
	dev->rx_speed = __le32_to_cpu(speeds[1]);
पूर्ण

व्योम usbnet_cdc_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	काष्ठा usb_cdc_notअगरication	*event;

	अगर (urb->actual_length < माप(*event))
		वापस;

	/* SPEED_CHANGE can get split पूर्णांकo two 8-byte packets */
	अगर (test_and_clear_bit(EVENT_STS_SPLIT, &dev->flags)) अणु
		speed_change(dev, (__le32 *) urb->transfer_buffer);
		वापस;
	पूर्ण

	event = urb->transfer_buffer;
	चयन (event->bNotअगरicationType) अणु
	हाल USB_CDC_NOTIFY_NETWORK_CONNECTION:
		netअगर_dbg(dev, समयr, dev->net, "CDC: carrier %s\n",
			  event->wValue ? "on" : "off");
		usbnet_link_change(dev, !!event->wValue, 0);
		अवरोध;
	हाल USB_CDC_NOTIFY_SPEED_CHANGE:	/* tx/rx rates */
		netअगर_dbg(dev, समयr, dev->net, "CDC: speed change (len %d)\n",
			  urb->actual_length);
		अगर (urb->actual_length != (माप(*event) + 8))
			set_bit(EVENT_STS_SPLIT, &dev->flags);
		अन्यथा
			speed_change(dev, (__le32 *) &event[1]);
		अवरोध;
	/* USB_CDC_NOTIFY_RESPONSE_AVAILABLE can happen too (e.g. RNDIS),
	 * but there are no standard क्रमmats क्रम the response data.
	 */
	शेष:
		netdev_err(dev->net, "CDC: unexpected notification %02x!\n",
			   event->bNotअगरicationType);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_cdc_status);

पूर्णांक usbnet_cdc_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक				status;
	काष्ठा cdc_state		*info = (व्योम *) &dev->data;

	BUILD_BUG_ON((माप(((काष्ठा usbnet *)0)->data)
			< माप(काष्ठा cdc_state)));

	status = usbnet_ether_cdc_bind(dev, पूर्णांकf);
	अगर (status < 0)
		वापस status;

	status = usbnet_get_ethernet_addr(dev, info->ether->iMACAddress);
	अगर (status < 0) अणु
		usb_set_पूर्णांकfdata(info->data, शून्य);
		usb_driver_release_पूर्णांकerface(driver_of(पूर्णांकf), info->data);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbnet_cdc_bind);

अटल पूर्णांक usbnet_cdc_zte_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक status = usbnet_cdc_bind(dev, पूर्णांकf);

	अगर (!status && (dev->net->dev_addr[0] & 0x02))
		eth_hw_addr_अक्रमom(dev->net);

	वापस status;
पूर्ण

/* Make sure packets have correct destination MAC address
 *
 * A firmware bug observed on some devices (ZTE MF823/831/910) is that the
 * device sends packets with a अटल, bogus, अक्रमom MAC address (event अगर
 * device MAC address has been updated). Always set MAC address to that of the
 * device.
 */
अटल पूर्णांक usbnet_cdc_zte_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	अगर (skb->len < ETH_HLEN || !(skb->data[0] & 0x02))
		वापस 1;

	skb_reset_mac_header(skb);
	ether_addr_copy(eth_hdr(skb)->h_dest, dev->net->dev_addr);

	वापस 1;
पूर्ण

/* Ensure correct link state
 *
 * Some devices (ZTE MF823/831/910) export two carrier on notअगरications when
 * connected. This causes the link state to be incorrect. Work around this by
 * always setting the state to off, then on.
 */
अटल व्योम usbnet_cdc_zte_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	काष्ठा usb_cdc_notअगरication *event;

	अगर (urb->actual_length < माप(*event))
		वापस;

	event = urb->transfer_buffer;

	अगर (event->bNotअगरicationType != USB_CDC_NOTIFY_NETWORK_CONNECTION) अणु
		usbnet_cdc_status(dev, urb);
		वापस;
	पूर्ण

	netअगर_dbg(dev, समयr, dev->net, "CDC: carrier %s\n",
		  event->wValue ? "on" : "off");

	अगर (event->wValue &&
	    netअगर_carrier_ok(dev->net))
		netअगर_carrier_off(dev->net);

	usbnet_link_change(dev, !!event->wValue, 0);
पूर्ण

अटल स्थिर काष्ठा driver_info	cdc_info = अणु
	.description =	"CDC Ethernet Device",
	.flags =	FLAG_ETHER | FLAG_POINTTOPOINT,
	.bind =		usbnet_cdc_bind,
	.unbind =	usbnet_cdc_unbind,
	.status =	usbnet_cdc_status,
	.set_rx_mode =	usbnet_cdc_update_filter,
	.manage_घातer =	usbnet_manage_घातer,
पूर्ण;

अटल स्थिर काष्ठा driver_info	zte_cdc_info = अणु
	.description =	"ZTE CDC Ethernet Device",
	.flags =	FLAG_ETHER | FLAG_POINTTOPOINT,
	.bind =		usbnet_cdc_zte_bind,
	.unbind =	usbnet_cdc_unbind,
	.status =	usbnet_cdc_zte_status,
	.set_rx_mode =	usbnet_cdc_update_filter,
	.manage_घातer =	usbnet_manage_घातer,
	.rx_fixup = usbnet_cdc_zte_rx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info wwan_info = अणु
	.description =	"Mobile Broadband Network Device",
	.flags =	FLAG_WWAN,
	.bind =		usbnet_cdc_bind,
	.unbind =	usbnet_cdc_unbind,
	.status =	usbnet_cdc_status,
	.set_rx_mode =	usbnet_cdc_update_filter,
	.manage_घातer =	usbnet_manage_घातer,
पूर्ण;

/*-------------------------------------------------------------------------*/

#घोषणा HUAWEI_VENDOR_ID	0x12D1
#घोषणा NOVATEL_VENDOR_ID	0x1410
#घोषणा ZTE_VENDOR_ID		0x19D2
#घोषणा DELL_VENDOR_ID		0x413C
#घोषणा REALTEK_VENDOR_ID	0x0bda
#घोषणा SAMSUNG_VENDOR_ID	0x04e8
#घोषणा LENOVO_VENDOR_ID	0x17ef
#घोषणा LINKSYS_VENDOR_ID	0x13b1
#घोषणा NVIDIA_VENDOR_ID	0x0955
#घोषणा HP_VENDOR_ID		0x03f0
#घोषणा MICROSOFT_VENDOR_ID	0x045e
#घोषणा UBLOX_VENDOR_ID		0x1546
#घोषणा TPLINK_VENDOR_ID	0x2357
#घोषणा AQUANTIA_VENDOR_ID	0x2eca
#घोषणा ASIX_VENDOR_ID		0x0b95

अटल स्थिर काष्ठा usb_device_id	products[] = अणु
/* BLACKLIST !!
 *
 * First blacklist any products that are egregiously nonconक्रमmant
 * with the CDC Ethernet specs.  Minor braindamage we cope with; when
 * they're not even trying, needing a separate driver is only the first
 * of the dअगरferences to show up.
 */

#घोषणा	ZAURUS_MASTER_INTERFACE \
	.bInterfaceClass	= USB_CLASS_COMM, \
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_ETHERNET, \
	.bInterfaceProtocol	= USB_CDC_PROTO_NONE

/* SA-1100 based Sharp Zaurus ("collie"), or compatible;
 * wire-incompatible with true CDC Ethernet implementations.
 * (And, it seems, needlessly so...)
 */
अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x04DD,
	.idProduct		= 0x8004,
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
पूर्ण,

/* PXA-25x based Sharp Zaurii.  Note that it seems some of these
 * (later models especially) may have shipped only with firmware
 * advertising false "CDC MDLM" compatibility ... but we're not
 * clear which models did that, so क्रम now let's assume the worst.
 */
अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x04DD,
	.idProduct		= 0x8005,	/* A-300 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x04DD,
	.idProduct		= 0x8006,	/* B-500/SL-5600 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
पूर्ण, अणु
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x04DD,
	.idProduct		= 0x8007,	/* C-700 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
पूर्ण, अणु
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr               = 0x04DD,
	.idProduct              = 0x9031,	/* C-750 C-760 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
पूर्ण, अणु
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr               = 0x04DD,
	.idProduct              = 0x9032,	/* SL-6000 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
पूर्ण, अणु
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr               = 0x04DD,
	/* reported with some C860 units */
	.idProduct              = 0x9050,	/* C-860 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
पूर्ण,

/* Olympus has some models with a Zaurus-compatible option.
 * R-1000 uses a FreeScale i.MXL cpu (ARMv4T)
 */
अणु
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr               = 0x07B4,
	.idProduct              = 0x0F02,	/* R-1000 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
पूर्ण,

/* LG Electronics VL600 wants additional headers on every frame */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(0x1004, 0x61aa, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Logitech Harmony 900 - uses the pseuकरो-MDLM (BLAN) driver */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(0x046d, 0xc11f, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_MDLM, USB_CDC_PROTO_NONE),
	.driver_info		= 0,
पूर्ण,

/* Novatel USB551L and MC551 - handled by qmi_wwan */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(NOVATEL_VENDOR_ID, 0xB001, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Novatel E362 - handled by qmi_wwan */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(NOVATEL_VENDOR_ID, 0x9010, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Dell Wireless 5800 (Novatel E362) - handled by qmi_wwan */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(DELL_VENDOR_ID, 0x8195, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Dell Wireless 5800 (Novatel E362) - handled by qmi_wwan */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(DELL_VENDOR_ID, 0x8196, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Dell Wireless 5804 (Novatel E371) - handled by qmi_wwan */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(DELL_VENDOR_ID, 0x819b, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Novatel Expedite E371 - handled by qmi_wwan */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(NOVATEL_VENDOR_ID, 0x9011, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* HP lt2523 (Novatel E371) - handled by qmi_wwan */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(HP_VENDOR_ID, 0x421d, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* AnyDATA ADU960S - handled by qmi_wwan */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(0x16d5, 0x650a, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Huawei E1820 - handled by qmi_wwan */
अणु
	USB_DEVICE_INTERFACE_NUMBER(HUAWEI_VENDOR_ID, 0x14ac, 1),
	.driver_info = 0,
पूर्ण,

/* Realtek RTL8152 Based USB 2.0 Ethernet Adapters */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(REALTEK_VENDOR_ID, 0x8152, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Realtek RTL8153 Based USB 3.0 Ethernet Adapters */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(REALTEK_VENDOR_ID, 0x8153, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Samsung USB Ethernet Adapters */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(SAMSUNG_VENDOR_ID, 0xa101, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

#अगर IS_ENABLED(CONFIG_USB_RTL8152)
/* Linksys USB3GIGV1 Ethernet Adapter */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(LINKSYS_VENDOR_ID, 0x0041, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,
#पूर्ण_अगर

/* ThinkPad USB-C Dock (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(LENOVO_VENDOR_ID, 0x3062, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* ThinkPad Thunderbolt 3 Dock (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(LENOVO_VENDOR_ID, 0x3069, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* ThinkPad Thunderbolt 3 Dock Gen 2 (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(LENOVO_VENDOR_ID, 0x3082, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Lenovo Thinkpad USB 3.0 Ethernet Adapters (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(LENOVO_VENDOR_ID, 0x7205, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Lenovo USB C to Ethernet Adapter (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(LENOVO_VENDOR_ID, 0x720c, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Lenovo USB-C Travel Hub (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(LENOVO_VENDOR_ID, 0x7214, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Lenovo Powered USB-C Travel Hub (4X90S92381, based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(LENOVO_VENDOR_ID, 0x721e, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* ThinkPad USB-C Dock Gen 2 (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(LENOVO_VENDOR_ID, 0xa387, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* NVIDIA Tegra USB 3.0 Ethernet Adapters (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(NVIDIA_VENDOR_ID, 0x09ff, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Microsoft Surface 2 करोck (based on Realtek RTL8152) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(MICROSOFT_VENDOR_ID, 0x07ab, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Microsoft Surface Ethernet Adapter (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(MICROSOFT_VENDOR_ID, 0x07c6, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Microsoft Surface Ethernet Adapter (based on Realtek RTL8153B) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(MICROSOFT_VENDOR_ID, 0x0927, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* TP-LINK UE300 USB 3.0 Ethernet Adapters (based on Realtek RTL8153) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(TPLINK_VENDOR_ID, 0x0601, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* Aquantia AQtion USB to 5GbE Controller (based on AQC111U) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(AQUANTIA_VENDOR_ID, 0xc101,
				      USB_CLASS_COMM, USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* ASIX USB 3.1 Gen1 to 5G Multi-Gigabit Ethernet Adapter(based on AQC111U) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(ASIX_VENDOR_ID, 0x2790, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* ASIX USB 3.1 Gen1 to 2.5G Multi-Gigabit Ethernet Adapter(based on AQC112U) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(ASIX_VENDOR_ID, 0x2791, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* USB-C 3.1 to 5GBASE-T Ethernet Adapter (based on AQC111U) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(0x20f4, 0xe05a, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* QNAP QNA-UC5G1T USB to 5GbE Adapter (based on AQC111U) */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(0x1c04, 0x0015, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = 0,
पूर्ण,

/* WHITELIST!!!
 *
 * CDC Ether uses two पूर्णांकerfaces, not necessarily consecutive.
 * We match the मुख्य पूर्णांकerface, ignoring the optional device
 * class so we could handle devices that aren't exclusively
 * CDC ether.
 *
 * NOTE:  this match must come AFTER entries blacklisting devices
 * because of bugs/quirks in a given product (like Zaurus, above).
 */
अणु
	/* ZTE (Vodafone) K3805-Z */
	USB_DEVICE_AND_INTERFACE_INFO(ZTE_VENDOR_ID, 0x1003, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* ZTE (Vodafone) K3806-Z */
	USB_DEVICE_AND_INTERFACE_INFO(ZTE_VENDOR_ID, 0x1015, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* ZTE (Vodafone) K4510-Z */
	USB_DEVICE_AND_INTERFACE_INFO(ZTE_VENDOR_ID, 0x1173, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* ZTE (Vodafone) K3770-Z */
	USB_DEVICE_AND_INTERFACE_INFO(ZTE_VENDOR_ID, 0x1177, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* ZTE (Vodafone) K3772-Z */
	USB_DEVICE_AND_INTERFACE_INFO(ZTE_VENDOR_ID, 0x1181, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* Telit modules */
	USB_VENDOR_AND_INTERFACE_INFO(0x1bc7, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = (kernel_uदीर्घ_t) &wwan_info,
पूर्ण, अणु
	/* Dell DW5580 modules */
	USB_DEVICE_AND_INTERFACE_INFO(DELL_VENDOR_ID, 0x81ba, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = (kernel_uदीर्घ_t)&wwan_info,
पूर्ण, अणु
	/* Huawei ME906 and ME909 */
	USB_DEVICE_AND_INTERFACE_INFO(HUAWEI_VENDOR_ID, 0x15c1, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* ZTE modules */
	USB_VENDOR_AND_INTERFACE_INFO(ZTE_VENDOR_ID, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&zte_cdc_info,
पूर्ण, अणु
	/* U-blox TOBY-L2 */
	USB_DEVICE_AND_INTERFACE_INFO(UBLOX_VENDOR_ID, 0x1143, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* U-blox SARA-U2 */
	USB_DEVICE_AND_INTERFACE_INFO(UBLOX_VENDOR_ID, 0x1104, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* Cपूर्णांकerion PLS8 modem by GEMALTO */
	USB_DEVICE_AND_INTERFACE_INFO(0x1e2d, 0x0061, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* Cपूर्णांकerion AHS3 modem by GEMALTO */
	USB_DEVICE_AND_INTERFACE_INFO(0x1e2d, 0x0055, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	/* Cपूर्णांकerion PLS83/PLS63 modem by GEMALTO/THALES */
	USB_DEVICE_AND_INTERFACE_INFO(0x1e2d, 0x0069, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET,
				      USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण, अणु
	USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_ETHERNET,
			USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ) &cdc_info,
पूर्ण, अणु
	USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_MDLM,
			USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,

पूर्ण, अणु
	/* Various Huawei modems with a network port like the UMG1831 */
	USB_VENDOR_AND_INTERFACE_INFO(HUAWEI_VENDOR_ID, USB_CLASS_COMM,
				      USB_CDC_SUBCLASS_ETHERNET, 255),
	.driver_info = (अचिन्हित दीर्घ)&wwan_info,
पूर्ण,
	अणु पूर्ण,		/* END */
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver cdc_driver = अणु
	.name =		"cdc_ether",
	.id_table =	products,
	.probe =	usbnet_probe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.reset_resume =	usbnet_resume,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(cdc_driver);

MODULE_AUTHOR("David Brownell");
MODULE_DESCRIPTION("USB CDC Ethernet devices");
MODULE_LICENSE("GPL");
