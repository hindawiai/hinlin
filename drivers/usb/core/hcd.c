<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * (C) Copyright Linus Torvalds 1999
 * (C) Copyright Johannes Erdfelt 1999-2001
 * (C) Copyright Andreas Gal 1999
 * (C) Copyright Gregory P. Smith 1999
 * (C) Copyright Deti Fliegl 1999
 * (C) Copyright Randy Dunlap 2000
 * (C) Copyright David Brownell 2000-2002
 */

#समावेश <linux/bcd.h>
#समावेश <linux/module.h>
#समावेश <linux/version.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/utsname.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/types.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/पन.स>
#समावेश <linux/kcov.h>

#समावेश <linux/phy/phy.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/otg.h>

#समावेश "usb.h"
#समावेश "phy.h"


/*-------------------------------------------------------------------------*/

/*
 * USB Host Controller Driver framework
 *
 * Plugs पूर्णांकo usbcore (usb_bus) and lets HCDs share code, minimizing
 * HCD-specअगरic behaviors/bugs.
 *
 * This करोes error checks, tracks devices and urbs, and delegates to a
 * "hc_driver" only क्रम code (and data) that really needs to know about
 * hardware dअगरferences.  That includes root hub रेजिस्टरs, i/o queues,
 * and so on ... but as little अन्यथा as possible.
 *
 * Shared code includes most of the "root hub" code (these are emulated,
 * though each HC's hardware works dअगरferently) and PCI glue, plus request
 * tracking overhead.  The HCD code should only block on spinlocks or on
 * hardware handshaking; blocking on software events (such as other kernel
 * thपढ़ोs releasing resources, or completing actions) is all generic.
 *
 * Happens the USB 2.0 spec says this would be invisible inside the "USBD",
 * and includes mostly a "HCDI" (HCD Interface) aदीर्घ with some APIs used
 * only by the hub driver ... and that neither should be seen or used by
 * usb client device drivers.
 *
 * Contributors of ideas or unattributed patches include: David Brownell,
 * Roman Weissgaerber, Rory Bolt, Greg Kroah-Harपंचांगan, ...
 *
 * HISTORY:
 * 2002-02-21	Pull in most of the usb_bus support from usb.c; some
 *		associated cleanup.  "usb_hcd" still != "usb_bus".
 * 2001-12-12	Initial patch version क्रम Linux 2.5.1 kernel.
 */

/*-------------------------------------------------------------------------*/

/* Keep track of which host controller drivers are loaded */
अचिन्हित दीर्घ usb_hcds_loaded;
EXPORT_SYMBOL_GPL(usb_hcds_loaded);

/* host controllers we manage */
DEFINE_IDR (usb_bus_idr);
EXPORT_SYMBOL_GPL (usb_bus_idr);

/* used when allocating bus numbers */
#घोषणा USB_MAXBUS		64

/* used when updating list of hcds */
DEFINE_MUTEX(usb_bus_idr_lock);	/* exported only क्रम usbfs */
EXPORT_SYMBOL_GPL (usb_bus_idr_lock);

/* used क्रम controlling access to भव root hubs */
अटल DEFINE_SPINLOCK(hcd_root_hub_lock);

/* used when updating an endpoपूर्णांक's URB list */
अटल DEFINE_SPINLOCK(hcd_urb_list_lock);

/* used to protect against unlinking URBs after the device is gone */
अटल DEFINE_SPINLOCK(hcd_urb_unlink_lock);

/* रुको queue क्रम synchronous unlinks */
DECLARE_WAIT_QUEUE_HEAD(usb_समाप्त_urb_queue);

/*-------------------------------------------------------------------------*/

/*
 * Sharable chunks of root hub code.
 */

/*-------------------------------------------------------------------------*/
#घोषणा KERNEL_REL	bin2bcd(LINUX_VERSION_MAJOR)
#घोषणा KERNEL_VER	bin2bcd(LINUX_VERSION_PATCHLEVEL)

/* usb 3.1 root hub device descriptor */
अटल स्थिर u8 usb31_rh_dev_descriptor[18] = अणु
	0x12,       /*  __u8  bLength; */
	USB_DT_DEVICE, /* __u8 bDescriptorType; Device */
	0x10, 0x03, /*  __le16 bcdUSB; v3.1 */

	0x09,	    /*  __u8  bDeviceClass; HUB_CLASSCODE */
	0x00,	    /*  __u8  bDeviceSubClass; */
	0x03,       /*  __u8  bDeviceProtocol; USB 3 hub */
	0x09,       /*  __u8  bMaxPacketSize0; 2^9 = 512 Bytes */

	0x6b, 0x1d, /*  __le16 idVenकरोr; Linux Foundation 0x1d6b */
	0x03, 0x00, /*  __le16 idProduct; device 0x0003 */
	KERNEL_VER, KERNEL_REL, /*  __le16 bcdDevice */

	0x03,       /*  __u8  iManufacturer; */
	0x02,       /*  __u8  iProduct; */
	0x01,       /*  __u8  iSerialNumber; */
	0x01        /*  __u8  bNumConfigurations; */
पूर्ण;

/* usb 3.0 root hub device descriptor */
अटल स्थिर u8 usb3_rh_dev_descriptor[18] = अणु
	0x12,       /*  __u8  bLength; */
	USB_DT_DEVICE, /* __u8 bDescriptorType; Device */
	0x00, 0x03, /*  __le16 bcdUSB; v3.0 */

	0x09,	    /*  __u8  bDeviceClass; HUB_CLASSCODE */
	0x00,	    /*  __u8  bDeviceSubClass; */
	0x03,       /*  __u8  bDeviceProtocol; USB 3.0 hub */
	0x09,       /*  __u8  bMaxPacketSize0; 2^9 = 512 Bytes */

	0x6b, 0x1d, /*  __le16 idVenकरोr; Linux Foundation 0x1d6b */
	0x03, 0x00, /*  __le16 idProduct; device 0x0003 */
	KERNEL_VER, KERNEL_REL, /*  __le16 bcdDevice */

	0x03,       /*  __u8  iManufacturer; */
	0x02,       /*  __u8  iProduct; */
	0x01,       /*  __u8  iSerialNumber; */
	0x01        /*  __u8  bNumConfigurations; */
पूर्ण;

/* usb 2.5 (wireless USB 1.0) root hub device descriptor */
अटल स्थिर u8 usb25_rh_dev_descriptor[18] = अणु
	0x12,       /*  __u8  bLength; */
	USB_DT_DEVICE, /* __u8 bDescriptorType; Device */
	0x50, 0x02, /*  __le16 bcdUSB; v2.5 */

	0x09,	    /*  __u8  bDeviceClass; HUB_CLASSCODE */
	0x00,	    /*  __u8  bDeviceSubClass; */
	0x00,       /*  __u8  bDeviceProtocol; [ usb 2.0 no TT ] */
	0xFF,       /*  __u8  bMaxPacketSize0; always 0xFF (WUSB Spec 7.4.1). */

	0x6b, 0x1d, /*  __le16 idVenकरोr; Linux Foundation 0x1d6b */
	0x02, 0x00, /*  __le16 idProduct; device 0x0002 */
	KERNEL_VER, KERNEL_REL, /*  __le16 bcdDevice */

	0x03,       /*  __u8  iManufacturer; */
	0x02,       /*  __u8  iProduct; */
	0x01,       /*  __u8  iSerialNumber; */
	0x01        /*  __u8  bNumConfigurations; */
पूर्ण;

/* usb 2.0 root hub device descriptor */
अटल स्थिर u8 usb2_rh_dev_descriptor[18] = अणु
	0x12,       /*  __u8  bLength; */
	USB_DT_DEVICE, /* __u8 bDescriptorType; Device */
	0x00, 0x02, /*  __le16 bcdUSB; v2.0 */

	0x09,	    /*  __u8  bDeviceClass; HUB_CLASSCODE */
	0x00,	    /*  __u8  bDeviceSubClass; */
	0x00,       /*  __u8  bDeviceProtocol; [ usb 2.0 no TT ] */
	0x40,       /*  __u8  bMaxPacketSize0; 64 Bytes */

	0x6b, 0x1d, /*  __le16 idVenकरोr; Linux Foundation 0x1d6b */
	0x02, 0x00, /*  __le16 idProduct; device 0x0002 */
	KERNEL_VER, KERNEL_REL, /*  __le16 bcdDevice */

	0x03,       /*  __u8  iManufacturer; */
	0x02,       /*  __u8  iProduct; */
	0x01,       /*  __u8  iSerialNumber; */
	0x01        /*  __u8  bNumConfigurations; */
पूर्ण;

/* no usb 2.0 root hub "device qualifier" descriptor: one speed only */

/* usb 1.1 root hub device descriptor */
अटल स्थिर u8 usb11_rh_dev_descriptor[18] = अणु
	0x12,       /*  __u8  bLength; */
	USB_DT_DEVICE, /* __u8 bDescriptorType; Device */
	0x10, 0x01, /*  __le16 bcdUSB; v1.1 */

	0x09,	    /*  __u8  bDeviceClass; HUB_CLASSCODE */
	0x00,	    /*  __u8  bDeviceSubClass; */
	0x00,       /*  __u8  bDeviceProtocol; [ low/full speeds only ] */
	0x40,       /*  __u8  bMaxPacketSize0; 64 Bytes */

	0x6b, 0x1d, /*  __le16 idVenकरोr; Linux Foundation 0x1d6b */
	0x01, 0x00, /*  __le16 idProduct; device 0x0001 */
	KERNEL_VER, KERNEL_REL, /*  __le16 bcdDevice */

	0x03,       /*  __u8  iManufacturer; */
	0x02,       /*  __u8  iProduct; */
	0x01,       /*  __u8  iSerialNumber; */
	0x01        /*  __u8  bNumConfigurations; */
पूर्ण;


/*-------------------------------------------------------------------------*/

/* Configuration descriptors क्रम our root hubs */

अटल स्थिर u8 fs_rh_config_descriptor[] = अणु

	/* one configuration */
	0x09,       /*  __u8  bLength; */
	USB_DT_CONFIG, /* __u8 bDescriptorType; Configuration */
	0x19, 0x00, /*  __le16 wTotalLength; */
	0x01,       /*  __u8  bNumInterfaces; (1) */
	0x01,       /*  __u8  bConfigurationValue; */
	0x00,       /*  __u8  iConfiguration; */
	0xc0,       /*  __u8  bmAttributes;
				 Bit 7: must be set,
				     6: Self-घातered,
				     5: Remote wakeup,
				     4..0: resvd */
	0x00,       /*  __u8  MaxPower; */

	/* USB 1.1:
	 * USB 2.0, single TT organization (mandatory):
	 *	one पूर्णांकerface, protocol 0
	 *
	 * USB 2.0, multiple TT organization (optional):
	 *	two पूर्णांकerfaces, protocols 1 (like single TT)
	 *	and 2 (multiple TT mode) ... config is
	 *	someबार settable
	 *	NOT IMPLEMENTED
	 */

	/* one पूर्णांकerface */
	0x09,       /*  __u8  अगर_bLength; */
	USB_DT_INTERFACE,  /* __u8 अगर_bDescriptorType; Interface */
	0x00,       /*  __u8  अगर_bInterfaceNumber; */
	0x00,       /*  __u8  अगर_bAlternateSetting; */
	0x01,       /*  __u8  अगर_bNumEndpoपूर्णांकs; */
	0x09,       /*  __u8  अगर_bInterfaceClass; HUB_CLASSCODE */
	0x00,       /*  __u8  अगर_bInterfaceSubClass; */
	0x00,       /*  __u8  अगर_bInterfaceProtocol; [usb1.1 or single tt] */
	0x00,       /*  __u8  अगर_iInterface; */

	/* one endpoपूर्णांक (status change endpoपूर्णांक) */
	0x07,       /*  __u8  ep_bLength; */
	USB_DT_ENDPOINT, /* __u8 ep_bDescriptorType; Endpoपूर्णांक */
	0x81,       /*  __u8  ep_bEndpoपूर्णांकAddress; IN Endpoपूर्णांक 1 */
	0x03,       /*  __u8  ep_bmAttributes; Interrupt */
	0x02, 0x00, /*  __le16 ep_wMaxPacketSize; 1 + (MAX_ROOT_PORTS / 8) */
	0xff        /*  __u8  ep_bInterval; (255ms -- usb 2.0 spec) */
पूर्ण;

अटल स्थिर u8 hs_rh_config_descriptor[] = अणु

	/* one configuration */
	0x09,       /*  __u8  bLength; */
	USB_DT_CONFIG, /* __u8 bDescriptorType; Configuration */
	0x19, 0x00, /*  __le16 wTotalLength; */
	0x01,       /*  __u8  bNumInterfaces; (1) */
	0x01,       /*  __u8  bConfigurationValue; */
	0x00,       /*  __u8  iConfiguration; */
	0xc0,       /*  __u8  bmAttributes;
				 Bit 7: must be set,
				     6: Self-घातered,
				     5: Remote wakeup,
				     4..0: resvd */
	0x00,       /*  __u8  MaxPower; */

	/* USB 1.1:
	 * USB 2.0, single TT organization (mandatory):
	 *	one पूर्णांकerface, protocol 0
	 *
	 * USB 2.0, multiple TT organization (optional):
	 *	two पूर्णांकerfaces, protocols 1 (like single TT)
	 *	and 2 (multiple TT mode) ... config is
	 *	someबार settable
	 *	NOT IMPLEMENTED
	 */

	/* one पूर्णांकerface */
	0x09,       /*  __u8  अगर_bLength; */
	USB_DT_INTERFACE, /* __u8 अगर_bDescriptorType; Interface */
	0x00,       /*  __u8  अगर_bInterfaceNumber; */
	0x00,       /*  __u8  अगर_bAlternateSetting; */
	0x01,       /*  __u8  अगर_bNumEndpoपूर्णांकs; */
	0x09,       /*  __u8  अगर_bInterfaceClass; HUB_CLASSCODE */
	0x00,       /*  __u8  अगर_bInterfaceSubClass; */
	0x00,       /*  __u8  अगर_bInterfaceProtocol; [usb1.1 or single tt] */
	0x00,       /*  __u8  अगर_iInterface; */

	/* one endpoपूर्णांक (status change endpoपूर्णांक) */
	0x07,       /*  __u8  ep_bLength; */
	USB_DT_ENDPOINT, /* __u8 ep_bDescriptorType; Endpoपूर्णांक */
	0x81,       /*  __u8  ep_bEndpoपूर्णांकAddress; IN Endpoपूर्णांक 1 */
	0x03,       /*  __u8  ep_bmAttributes; Interrupt */
		    /* __le16 ep_wMaxPacketSize; 1 + (MAX_ROOT_PORTS / 8)
		     * see hub.c:hub_configure() क्रम details. */
	(USB_MAXCHILDREN + 1 + 7) / 8, 0x00,
	0x0c        /*  __u8  ep_bInterval; (256ms -- usb 2.0 spec) */
पूर्ण;

अटल स्थिर u8 ss_rh_config_descriptor[] = अणु
	/* one configuration */
	0x09,       /*  __u8  bLength; */
	USB_DT_CONFIG, /* __u8 bDescriptorType; Configuration */
	0x1f, 0x00, /*  __le16 wTotalLength; */
	0x01,       /*  __u8  bNumInterfaces; (1) */
	0x01,       /*  __u8  bConfigurationValue; */
	0x00,       /*  __u8  iConfiguration; */
	0xc0,       /*  __u8  bmAttributes;
				 Bit 7: must be set,
				     6: Self-घातered,
				     5: Remote wakeup,
				     4..0: resvd */
	0x00,       /*  __u8  MaxPower; */

	/* one पूर्णांकerface */
	0x09,       /*  __u8  अगर_bLength; */
	USB_DT_INTERFACE, /* __u8 अगर_bDescriptorType; Interface */
	0x00,       /*  __u8  अगर_bInterfaceNumber; */
	0x00,       /*  __u8  अगर_bAlternateSetting; */
	0x01,       /*  __u8  अगर_bNumEndpoपूर्णांकs; */
	0x09,       /*  __u8  अगर_bInterfaceClass; HUB_CLASSCODE */
	0x00,       /*  __u8  अगर_bInterfaceSubClass; */
	0x00,       /*  __u8  अगर_bInterfaceProtocol; */
	0x00,       /*  __u8  अगर_iInterface; */

	/* one endpoपूर्णांक (status change endpoपूर्णांक) */
	0x07,       /*  __u8  ep_bLength; */
	USB_DT_ENDPOINT, /* __u8 ep_bDescriptorType; Endpoपूर्णांक */
	0x81,       /*  __u8  ep_bEndpoपूर्णांकAddress; IN Endpoपूर्णांक 1 */
	0x03,       /*  __u8  ep_bmAttributes; Interrupt */
		    /* __le16 ep_wMaxPacketSize; 1 + (MAX_ROOT_PORTS / 8)
		     * see hub.c:hub_configure() क्रम details. */
	(USB_MAXCHILDREN + 1 + 7) / 8, 0x00,
	0x0c,       /*  __u8  ep_bInterval; (256ms -- usb 2.0 spec) */

	/* one SuperSpeed endpoपूर्णांक companion descriptor */
	0x06,        /* __u8 ss_bLength */
	USB_DT_SS_ENDPOINT_COMP, /* __u8 ss_bDescriptorType; SuperSpeed EP */
		     /* Companion */
	0x00,        /* __u8 ss_bMaxBurst; allows 1 TX between ACKs */
	0x00,        /* __u8 ss_bmAttributes; 1 packet per service पूर्णांकerval */
	0x02, 0x00   /* __le16 ss_wBytesPerInterval; 15 bits क्रम max 15 ports */
पूर्ण;

/* authorized_शेष behaviour:
 * -1 is authorized क्रम all devices except wireless (old behaviour)
 * 0 is unauthorized क्रम all devices
 * 1 is authorized क्रम all devices
 * 2 is authorized क्रम पूर्णांकernal devices
 */
#घोषणा USB_AUTHORIZE_WIRED	-1
#घोषणा USB_AUTHORIZE_NONE	0
#घोषणा USB_AUTHORIZE_ALL	1
#घोषणा USB_AUTHORIZE_INTERNAL	2

अटल पूर्णांक authorized_शेष = USB_AUTHORIZE_WIRED;
module_param(authorized_शेष, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(authorized_शेष,
		"Default USB device authorization: 0 is not authorized, 1 is "
		"authorized, 2 is authorized for internal devices, -1 is "
		"authorized except for wireless USB (default, old behaviour)");
/*-------------------------------------------------------------------------*/

/**
 * ascii2desc() - Helper routine क्रम producing UTF-16LE string descriptors
 * @s: Null-terminated ASCII (actually ISO-8859-1) string
 * @buf: Buffer क्रम USB string descriptor (header + UTF-16LE)
 * @len: Length (in bytes; may be odd) of descriptor buffer.
 *
 * Return: The number of bytes filled in: 2 + 2*म_माप(s) or @len,
 * whichever is less.
 *
 * Note:
 * USB String descriptors can contain at most 126 अक्षरacters; input
 * strings दीर्घer than that are truncated.
 */
अटल अचिन्हित
ascii2desc(अक्षर स्थिर *s, u8 *buf, अचिन्हित len)
अणु
	अचिन्हित n, t = 2 + 2*म_माप(s);

	अगर (t > 254)
		t = 254;	/* Longest possible UTF string descriptor */
	अगर (len > t)
		len = t;

	t += USB_DT_STRING << 8;	/* Now t is first 16 bits to store */

	n = len;
	जबतक (n--) अणु
		*buf++ = t;
		अगर (!n--)
			अवरोध;
		*buf++ = t >> 8;
		t = (अचिन्हित अक्षर)*s++;
	पूर्ण
	वापस len;
पूर्ण

/**
 * rh_string() - provides string descriptors क्रम root hub
 * @id: the string ID number (0: langids, 1: serial #, 2: product, 3: venकरोr)
 * @hcd: the host controller क्रम this root hub
 * @data: buffer क्रम output packet
 * @len: length of the provided buffer
 *
 * Produces either a manufacturer, product or serial number string क्रम the
 * भव root hub device.
 *
 * Return: The number of bytes filled in: the length of the descriptor or
 * of the provided buffer, whichever is less.
 */
अटल अचिन्हित
rh_string(पूर्णांक id, काष्ठा usb_hcd स्थिर *hcd, u8 *data, अचिन्हित len)
अणु
	अक्षर buf[100];
	अक्षर स्थिर *s;
	अटल अक्षर स्थिर langids[4] = अणु4, USB_DT_STRING, 0x09, 0x04पूर्ण;

	/* language ids */
	चयन (id) अणु
	हाल 0:
		/* Array of LANGID codes (0x0409 is MSFT-speak क्रम "en-us") */
		/* See http://www.usb.org/developers/करोcs/USB_LANGIDs.pdf */
		अगर (len > 4)
			len = 4;
		स_नकल(data, langids, len);
		वापस len;
	हाल 1:
		/* Serial number */
		s = hcd->self.bus_name;
		अवरोध;
	हाल 2:
		/* Product name */
		s = hcd->product_desc;
		अवरोध;
	हाल 3:
		/* Manufacturer */
		snम_लिखो (buf, माप buf, "%s %s %s", init_utsname()->sysname,
			init_utsname()->release, hcd->driver->description);
		s = buf;
		अवरोध;
	शेष:
		/* Can't happen; caller guarantees it */
		वापस 0;
	पूर्ण

	वापस ascii2desc(s, data, len);
पूर्ण


/* Root hub control transfers execute synchronously */
अटल पूर्णांक rh_call_control (काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *cmd;
	u16		typeReq, wValue, wIndex, wLength;
	u8		*ubuf = urb->transfer_buffer;
	अचिन्हित	len = 0;
	पूर्णांक		status;
	u8		patch_wakeup = 0;
	u8		patch_protocol = 0;
	u16		tbuf_size;
	u8		*tbuf = शून्य;
	स्थिर u8	*bufp;

	might_sleep();

	spin_lock_irq(&hcd_root_hub_lock);
	status = usb_hcd_link_urb_to_ep(hcd, urb);
	spin_unlock_irq(&hcd_root_hub_lock);
	अगर (status)
		वापस status;
	urb->hcpriv = hcd;	/* Indicate it's queued */

	cmd = (काष्ठा usb_ctrlrequest *) urb->setup_packet;
	typeReq  = (cmd->bRequestType << 8) | cmd->bRequest;
	wValue   = le16_to_cpu (cmd->wValue);
	wIndex   = le16_to_cpu (cmd->wIndex);
	wLength  = le16_to_cpu (cmd->wLength);

	अगर (wLength > urb->transfer_buffer_length)
		जाओ error;

	/*
	 * tbuf should be at least as big as the
	 * USB hub descriptor.
	 */
	tbuf_size =  max_t(u16, माप(काष्ठा usb_hub_descriptor), wLength);
	tbuf = kzalloc(tbuf_size, GFP_KERNEL);
	अगर (!tbuf) अणु
		status = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	bufp = tbuf;


	urb->actual_length = 0;
	चयन (typeReq) अणु

	/* DEVICE REQUESTS */

	/* The root hub's remote wakeup enable bit is implemented using
	 * driver model wakeup flags.  If this प्रणाली supports wakeup
	 * through USB, userspace may change the शेष "allow wakeup"
	 * policy through sysfs or these calls.
	 *
	 * Most root hubs support wakeup from करोwnstream devices, क्रम
	 * runसमय घातer management (disabling USB घड़ीs and reducing
	 * VBUS घातer usage).  However, not all of them करो so; silicon,
	 * board, and BIOS bugs here are not uncommon, so these can't
	 * be treated quite like बाह्यal hubs.
	 *
	 * Likewise, not all root hubs will pass wakeup events upstream,
	 * to wake up the whole प्रणाली.  So करोn't assume root hub and
	 * controller capabilities are identical.
	 */

	हाल DeviceRequest | USB_REQ_GET_STATUS:
		tbuf[0] = (device_may_wakeup(&hcd->self.root_hub->dev)
					<< USB_DEVICE_REMOTE_WAKEUP)
				| (1 << USB_DEVICE_SELF_POWERED);
		tbuf[1] = 0;
		len = 2;
		अवरोध;
	हाल DeviceOutRequest | USB_REQ_CLEAR_FEATURE:
		अगर (wValue == USB_DEVICE_REMOTE_WAKEUP)
			device_set_wakeup_enable(&hcd->self.root_hub->dev, 0);
		अन्यथा
			जाओ error;
		अवरोध;
	हाल DeviceOutRequest | USB_REQ_SET_FEATURE:
		अगर (device_can_wakeup(&hcd->self.root_hub->dev)
				&& wValue == USB_DEVICE_REMOTE_WAKEUP)
			device_set_wakeup_enable(&hcd->self.root_hub->dev, 1);
		अन्यथा
			जाओ error;
		अवरोध;
	हाल DeviceRequest | USB_REQ_GET_CONFIGURATION:
		tbuf[0] = 1;
		len = 1;
		fallthrough;
	हाल DeviceOutRequest | USB_REQ_SET_CONFIGURATION:
		अवरोध;
	हाल DeviceRequest | USB_REQ_GET_DESCRIPTOR:
		चयन (wValue & 0xff00) अणु
		हाल USB_DT_DEVICE << 8:
			चयन (hcd->speed) अणु
			हाल HCD_USB32:
			हाल HCD_USB31:
				bufp = usb31_rh_dev_descriptor;
				अवरोध;
			हाल HCD_USB3:
				bufp = usb3_rh_dev_descriptor;
				अवरोध;
			हाल HCD_USB25:
				bufp = usb25_rh_dev_descriptor;
				अवरोध;
			हाल HCD_USB2:
				bufp = usb2_rh_dev_descriptor;
				अवरोध;
			हाल HCD_USB11:
				bufp = usb11_rh_dev_descriptor;
				अवरोध;
			शेष:
				जाओ error;
			पूर्ण
			len = 18;
			अगर (hcd->has_tt)
				patch_protocol = 1;
			अवरोध;
		हाल USB_DT_CONFIG << 8:
			चयन (hcd->speed) अणु
			हाल HCD_USB32:
			हाल HCD_USB31:
			हाल HCD_USB3:
				bufp = ss_rh_config_descriptor;
				len = माप ss_rh_config_descriptor;
				अवरोध;
			हाल HCD_USB25:
			हाल HCD_USB2:
				bufp = hs_rh_config_descriptor;
				len = माप hs_rh_config_descriptor;
				अवरोध;
			हाल HCD_USB11:
				bufp = fs_rh_config_descriptor;
				len = माप fs_rh_config_descriptor;
				अवरोध;
			शेष:
				जाओ error;
			पूर्ण
			अगर (device_can_wakeup(&hcd->self.root_hub->dev))
				patch_wakeup = 1;
			अवरोध;
		हाल USB_DT_STRING << 8:
			अगर ((wValue & 0xff) < 4)
				urb->actual_length = rh_string(wValue & 0xff,
						hcd, ubuf, wLength);
			अन्यथा /* unsupported IDs --> "protocol stall" */
				जाओ error;
			अवरोध;
		हाल USB_DT_BOS << 8:
			जाओ nongeneric;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल DeviceRequest | USB_REQ_GET_INTERFACE:
		tbuf[0] = 0;
		len = 1;
		fallthrough;
	हाल DeviceOutRequest | USB_REQ_SET_INTERFACE:
		अवरोध;
	हाल DeviceOutRequest | USB_REQ_SET_ADDRESS:
		/* wValue == urb->dev->devaddr */
		dev_dbg (hcd->self.controller, "root hub device address %d\n",
			wValue);
		अवरोध;

	/* INTERFACE REQUESTS (no defined feature/status flags) */

	/* ENDPOINT REQUESTS */

	हाल Endpoपूर्णांकRequest | USB_REQ_GET_STATUS:
		/* ENDPOINT_HALT flag */
		tbuf[0] = 0;
		tbuf[1] = 0;
		len = 2;
		fallthrough;
	हाल Endpoपूर्णांकOutRequest | USB_REQ_CLEAR_FEATURE:
	हाल Endpoपूर्णांकOutRequest | USB_REQ_SET_FEATURE:
		dev_dbg (hcd->self.controller, "no endpoint features yet\n");
		अवरोध;

	/* CLASS REQUESTS (and errors) */

	शेष:
nongeneric:
		/* non-generic request */
		चयन (typeReq) अणु
		हाल GetHubStatus:
			len = 4;
			अवरोध;
		हाल GetPortStatus:
			अगर (wValue == HUB_PORT_STATUS)
				len = 4;
			अन्यथा
				/* other port status types वापस 8 bytes */
				len = 8;
			अवरोध;
		हाल GetHubDescriptor:
			len = माप (काष्ठा usb_hub_descriptor);
			अवरोध;
		हाल DeviceRequest | USB_REQ_GET_DESCRIPTOR:
			/* len is वापसed by hub_control */
			अवरोध;
		पूर्ण
		status = hcd->driver->hub_control (hcd,
			typeReq, wValue, wIndex,
			tbuf, wLength);

		अगर (typeReq == GetHubDescriptor)
			usb_hub_adjust_deviceremovable(hcd->self.root_hub,
				(काष्ठा usb_hub_descriptor *)tbuf);
		अवरोध;
error:
		/* "protocol stall" on error */
		status = -EPIPE;
	पूर्ण

	अगर (status < 0) अणु
		len = 0;
		अगर (status != -EPIPE) अणु
			dev_dbg (hcd->self.controller,
				"CTRL: TypeReq=0x%x val=0x%x "
				"idx=0x%x len=%d ==> %d\n",
				typeReq, wValue, wIndex,
				wLength, status);
		पूर्ण
	पूर्ण अन्यथा अगर (status > 0) अणु
		/* hub_control may वापस the length of data copied. */
		len = status;
		status = 0;
	पूर्ण
	अगर (len) अणु
		अगर (urb->transfer_buffer_length < len)
			len = urb->transfer_buffer_length;
		urb->actual_length = len;
		/* always USB_सूची_IN, toward host */
		स_नकल (ubuf, bufp, len);

		/* report whether RH hardware supports remote wakeup */
		अगर (patch_wakeup &&
				len > दुरत्व (काष्ठा usb_config_descriptor,
						bmAttributes))
			((काष्ठा usb_config_descriptor *)ubuf)->bmAttributes
				|= USB_CONFIG_ATT_WAKEUP;

		/* report whether RH hardware has an पूर्णांकegrated TT */
		अगर (patch_protocol &&
				len > दुरत्व(काष्ठा usb_device_descriptor,
						bDeviceProtocol))
			((काष्ठा usb_device_descriptor *) ubuf)->
				bDeviceProtocol = USB_HUB_PR_HS_SINGLE_TT;
	पूर्ण

	kमुक्त(tbuf);
 err_alloc:

	/* any errors get वापसed through the urb completion */
	spin_lock_irq(&hcd_root_hub_lock);
	usb_hcd_unlink_urb_from_ep(hcd, urb);
	usb_hcd_giveback_urb(hcd, urb, status);
	spin_unlock_irq(&hcd_root_hub_lock);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Root Hub पूर्णांकerrupt transfers are polled using a समयr अगर the
 * driver requests it; otherwise the driver is responsible क्रम
 * calling usb_hcd_poll_rh_status() when an event occurs.
 *
 * Completion handler may not sleep. See usb_hcd_giveback_urb() क्रम details.
 */
व्योम usb_hcd_poll_rh_status(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा urb	*urb;
	पूर्णांक		length;
	अचिन्हित दीर्घ	flags;
	अक्षर		buffer[6];	/* Any root hubs with > 31 ports? */

	अगर (unlikely(!hcd->rh_pollable))
		वापस;
	अगर (!hcd->uses_new_polling && !hcd->status_urb)
		वापस;

	length = hcd->driver->hub_status_data(hcd, buffer);
	अगर (length > 0) अणु

		/* try to complete the status urb */
		spin_lock_irqsave(&hcd_root_hub_lock, flags);
		urb = hcd->status_urb;
		अगर (urb) अणु
			clear_bit(HCD_FLAG_POLL_PENDING, &hcd->flags);
			hcd->status_urb = शून्य;
			urb->actual_length = length;
			स_नकल(urb->transfer_buffer, buffer, length);

			usb_hcd_unlink_urb_from_ep(hcd, urb);
			usb_hcd_giveback_urb(hcd, urb, 0);
		पूर्ण अन्यथा अणु
			length = 0;
			set_bit(HCD_FLAG_POLL_PENDING, &hcd->flags);
		पूर्ण
		spin_unlock_irqrestore(&hcd_root_hub_lock, flags);
	पूर्ण

	/* The USB 2.0 spec says 256 ms.  This is बंद enough and won't
	 * exceed that limit अगर HZ is 100. The math is more clunky than
	 * maybe expected, this is to make sure that all समयrs क्रम USB devices
	 * fire at the same समय to give the CPU a अवरोध in between */
	अगर (hcd->uses_new_polling ? HCD_POLL_RH(hcd) :
			(length == 0 && hcd->status_urb != शून्य))
		mod_समयr (&hcd->rh_समयr, (jअगरfies/(HZ/4) + 1) * (HZ/4));
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_poll_rh_status);

/* समयr callback */
अटल व्योम rh_समयr_func (काष्ठा समयr_list *t)
अणु
	काष्ठा usb_hcd *_hcd = from_समयr(_hcd, t, rh_समयr);

	usb_hcd_poll_rh_status(_hcd);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक rh_queue_status (काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	पूर्णांक		retval;
	अचिन्हित दीर्घ	flags;
	अचिन्हित	len = 1 + (urb->dev->maxchild / 8);

	spin_lock_irqsave (&hcd_root_hub_lock, flags);
	अगर (hcd->status_urb || urb->transfer_buffer_length < len) अणु
		dev_dbg (hcd->self.controller, "not queuing rh status urb\n");
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण

	retval = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (retval)
		जाओ करोne;

	hcd->status_urb = urb;
	urb->hcpriv = hcd;	/* indicate it's queued */
	अगर (!hcd->uses_new_polling)
		mod_समयr(&hcd->rh_समयr, (jअगरfies/(HZ/4) + 1) * (HZ/4));

	/* If a status change has alपढ़ोy occurred, report it ASAP */
	अन्यथा अगर (HCD_POLL_PENDING(hcd))
		mod_समयr(&hcd->rh_समयr, jअगरfies);
	retval = 0;
 करोne:
	spin_unlock_irqrestore (&hcd_root_hub_lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक rh_urb_enqueue (काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(&urb->ep->desc))
		वापस rh_queue_status (hcd, urb);
	अगर (usb_endpoपूर्णांक_xfer_control(&urb->ep->desc))
		वापस rh_call_control (hcd, urb);
	वापस -EINVAL;
पूर्ण

/*-------------------------------------------------------------------------*/

/* Unlinks of root-hub control URBs are legal, but they करोn't करो anything
 * since these URBs always execute synchronously.
 */
अटल पूर्णांक usb_rh_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	अचिन्हित दीर्घ	flags;
	पूर्णांक		rc;

	spin_lock_irqsave(&hcd_root_hub_lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc)
		जाओ करोne;

	अगर (usb_endpoपूर्णांक_num(&urb->ep->desc) == 0) अणु	/* Control URB */
		;	/* Do nothing */

	पूर्ण अन्यथा अणु				/* Status URB */
		अगर (!hcd->uses_new_polling)
			del_समयr (&hcd->rh_समयr);
		अगर (urb == hcd->status_urb) अणु
			hcd->status_urb = शून्य;
			usb_hcd_unlink_urb_from_ep(hcd, urb);
			usb_hcd_giveback_urb(hcd, urb, status);
		पूर्ण
	पूर्ण
 करोne:
	spin_unlock_irqrestore(&hcd_root_hub_lock, flags);
	वापस rc;
पूर्ण


/*-------------------------------------------------------------------------*/

/**
 * usb_bus_init - shared initialization code
 * @bus: the bus काष्ठाure being initialized
 *
 * This code is used to initialize a usb_bus काष्ठाure, memory क्रम which is
 * separately managed.
 */
अटल व्योम usb_bus_init (काष्ठा usb_bus *bus)
अणु
	स_रखो (&bus->devmap, 0, माप(काष्ठा usb_devmap));

	bus->devnum_next = 1;

	bus->root_hub = शून्य;
	bus->busnum = -1;
	bus->bandwidth_allocated = 0;
	bus->bandwidth_पूर्णांक_reqs  = 0;
	bus->bandwidth_isoc_reqs = 0;
	mutex_init(&bus->devnum_next_mutex);
पूर्ण

/*-------------------------------------------------------------------------*/

/**
 * usb_रेजिस्टर_bus - रेजिस्टरs the USB host controller with the usb core
 * @bus: poपूर्णांकer to the bus to रेजिस्टर
 *
 * Context: task context, might sleep.
 *
 * Assigns a bus number, and links the controller पूर्णांकo usbcore data
 * काष्ठाures so that it can be seen by scanning the bus list.
 *
 * Return: 0 अगर successful. A negative error code otherwise.
 */
अटल पूर्णांक usb_रेजिस्टर_bus(काष्ठा usb_bus *bus)
अणु
	पूर्णांक result = -E2BIG;
	पूर्णांक busnum;

	mutex_lock(&usb_bus_idr_lock);
	busnum = idr_alloc(&usb_bus_idr, bus, 1, USB_MAXBUS, GFP_KERNEL);
	अगर (busnum < 0) अणु
		pr_err("%s: failed to get bus number\n", usbcore_name);
		जाओ error_find_busnum;
	पूर्ण
	bus->busnum = busnum;
	mutex_unlock(&usb_bus_idr_lock);

	usb_notअगरy_add_bus(bus);

	dev_info (bus->controller, "new USB bus registered, assigned bus "
		  "number %d\n", bus->busnum);
	वापस 0;

error_find_busnum:
	mutex_unlock(&usb_bus_idr_lock);
	वापस result;
पूर्ण

/**
 * usb_deरेजिस्टर_bus - deरेजिस्टरs the USB host controller
 * @bus: poपूर्णांकer to the bus to deरेजिस्टर
 *
 * Context: task context, might sleep.
 *
 * Recycles the bus number, and unlinks the controller from usbcore data
 * काष्ठाures so that it won't be seen by scanning the bus list.
 */
अटल व्योम usb_deरेजिस्टर_bus (काष्ठा usb_bus *bus)
अणु
	dev_info (bus->controller, "USB bus %d deregistered\n", bus->busnum);

	/*
	 * NOTE: make sure that all the devices are हटाओd by the
	 * controller code, as well as having it call this when cleaning
	 * itself up
	 */
	mutex_lock(&usb_bus_idr_lock);
	idr_हटाओ(&usb_bus_idr, bus->busnum);
	mutex_unlock(&usb_bus_idr_lock);

	usb_notअगरy_हटाओ_bus(bus);
पूर्ण

/**
 * रेजिस्टर_root_hub - called by usb_add_hcd() to रेजिस्टर a root hub
 * @hcd: host controller क्रम this root hub
 *
 * This function रेजिस्टरs the root hub with the USB subप्रणाली.  It sets up
 * the device properly in the device tree and then calls usb_new_device()
 * to रेजिस्टर the usb device.  It also assigns the root hub's USB address
 * (always 1).
 *
 * Return: 0 अगर successful. A negative error code otherwise.
 */
अटल पूर्णांक रेजिस्टर_root_hub(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा device *parent_dev = hcd->self.controller;
	काष्ठा usb_device *usb_dev = hcd->self.root_hub;
	स्थिर पूर्णांक devnum = 1;
	पूर्णांक retval;

	usb_dev->devnum = devnum;
	usb_dev->bus->devnum_next = devnum + 1;
	set_bit (devnum, usb_dev->bus->devmap.devicemap);
	usb_set_device_state(usb_dev, USB_STATE_ADDRESS);

	mutex_lock(&usb_bus_idr_lock);

	usb_dev->ep0.desc.wMaxPacketSize = cpu_to_le16(64);
	retval = usb_get_device_descriptor(usb_dev, USB_DT_DEVICE_SIZE);
	अगर (retval != माप usb_dev->descriptor) अणु
		mutex_unlock(&usb_bus_idr_lock);
		dev_dbg (parent_dev, "can't read %s device descriptor %d\n",
				dev_name(&usb_dev->dev), retval);
		वापस (retval < 0) ? retval : -EMSGSIZE;
	पूर्ण

	अगर (le16_to_cpu(usb_dev->descriptor.bcdUSB) >= 0x0201) अणु
		retval = usb_get_bos_descriptor(usb_dev);
		अगर (!retval) अणु
			usb_dev->lpm_capable = usb_device_supports_lpm(usb_dev);
		पूर्ण अन्यथा अगर (usb_dev->speed >= USB_SPEED_SUPER) अणु
			mutex_unlock(&usb_bus_idr_lock);
			dev_dbg(parent_dev, "can't read %s bos descriptor %d\n",
					dev_name(&usb_dev->dev), retval);
			वापस retval;
		पूर्ण
	पूर्ण

	retval = usb_new_device (usb_dev);
	अगर (retval) अणु
		dev_err (parent_dev, "can't register root hub for %s, %d\n",
				dev_name(&usb_dev->dev), retval);
	पूर्ण अन्यथा अणु
		spin_lock_irq (&hcd_root_hub_lock);
		hcd->rh_रेजिस्टरed = 1;
		spin_unlock_irq (&hcd_root_hub_lock);

		/* Did the HC die beक्रमe the root hub was रेजिस्टरed? */
		अगर (HCD_DEAD(hcd))
			usb_hc_died (hcd);	/* This समय clean up */
	पूर्ण
	mutex_unlock(&usb_bus_idr_lock);

	वापस retval;
पूर्ण

/*
 * usb_hcd_start_port_resume - a root-hub port is sending a resume संकेत
 * @bus: the bus which the root hub beदीर्घs to
 * @portnum: the port which is being resumed
 *
 * HCDs should call this function when they know that a resume संकेत is
 * being sent to a root-hub port.  The root hub will be prevented from
 * going पूर्णांकo स्वतःsuspend until usb_hcd_end_port_resume() is called.
 *
 * The bus's निजी lock must be held by the caller.
 */
व्योम usb_hcd_start_port_resume(काष्ठा usb_bus *bus, पूर्णांक portnum)
अणु
	अचिन्हित bit = 1 << portnum;

	अगर (!(bus->resuming_ports & bit)) अणु
		bus->resuming_ports |= bit;
		pm_runसमय_get_noresume(&bus->root_hub->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_start_port_resume);

/*
 * usb_hcd_end_port_resume - a root-hub port has stopped sending a resume संकेत
 * @bus: the bus which the root hub beदीर्घs to
 * @portnum: the port which is being resumed
 *
 * HCDs should call this function when they know that a resume संकेत has
 * stopped being sent to a root-hub port.  The root hub will be allowed to
 * स्वतःsuspend again.
 *
 * The bus's निजी lock must be held by the caller.
 */
व्योम usb_hcd_end_port_resume(काष्ठा usb_bus *bus, पूर्णांक portnum)
अणु
	अचिन्हित bit = 1 << portnum;

	अगर (bus->resuming_ports & bit) अणु
		bus->resuming_ports &= ~bit;
		pm_runसमय_put_noidle(&bus->root_hub->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_end_port_resume);

/*-------------------------------------------------------------------------*/

/**
 * usb_calc_bus_समय - approximate periodic transaction समय in nanoseconds
 * @speed: from dev->speed; USB_SPEED_अणुLOW,FULL,HIGHपूर्ण
 * @is_input: true अगरf the transaction sends data to the host
 * @isoc: true क्रम isochronous transactions, false क्रम पूर्णांकerrupt ones
 * @bytecount: how many bytes in the transaction.
 *
 * Return: Approximate bus समय in nanoseconds क्रम a periodic transaction.
 *
 * Note:
 * See USB 2.0 spec section 5.11.3; only periodic transfers need to be
 * scheduled in software, this function is only used क्रम such scheduling.
 */
दीर्घ usb_calc_bus_समय (पूर्णांक speed, पूर्णांक is_input, पूर्णांक isoc, पूर्णांक bytecount)
अणु
	अचिन्हित दीर्घ	पंचांगp;

	चयन (speed) अणु
	हाल USB_SPEED_LOW: 	/* INTR only */
		अगर (is_input) अणु
			पंचांगp = (67667L * (31L + 10L * BitTime (bytecount))) / 1000L;
			वापस 64060L + (2 * BW_HUB_LS_SETUP) + BW_HOST_DELAY + पंचांगp;
		पूर्ण अन्यथा अणु
			पंचांगp = (66700L * (31L + 10L * BitTime (bytecount))) / 1000L;
			वापस 64107L + (2 * BW_HUB_LS_SETUP) + BW_HOST_DELAY + पंचांगp;
		पूर्ण
	हाल USB_SPEED_FULL:	/* ISOC or INTR */
		अगर (isoc) अणु
			पंचांगp = (8354L * (31L + 10L * BitTime (bytecount))) / 1000L;
			वापस ((is_input) ? 7268L : 6265L) + BW_HOST_DELAY + पंचांगp;
		पूर्ण अन्यथा अणु
			पंचांगp = (8354L * (31L + 10L * BitTime (bytecount))) / 1000L;
			वापस 9107L + BW_HOST_DELAY + पंचांगp;
		पूर्ण
	हाल USB_SPEED_HIGH:	/* ISOC or INTR */
		/* FIXME adjust क्रम input vs output */
		अगर (isoc)
			पंचांगp = HS_NSECS_ISO (bytecount);
		अन्यथा
			पंचांगp = HS_NSECS (bytecount);
		वापस पंचांगp;
	शेष:
		pr_debug ("%s: bogus device speed!\n", usbcore_name);
		वापस -1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_calc_bus_समय);


/*-------------------------------------------------------------------------*/

/*
 * Generic HC operations.
 */

/*-------------------------------------------------------------------------*/

/**
 * usb_hcd_link_urb_to_ep - add an URB to its endpoपूर्णांक queue
 * @hcd: host controller to which @urb was submitted
 * @urb: URB being submitted
 *
 * Host controller drivers should call this routine in their enqueue()
 * method.  The HCD's निजी spinlock must be held and पूर्णांकerrupts must
 * be disabled.  The actions carried out here are required क्रम URB
 * submission, as well as क्रम endpoपूर्णांक shutकरोwn and क्रम usb_समाप्त_urb.
 *
 * Return: 0 क्रम no error, otherwise a negative error code (in which हाल
 * the enqueue() method must fail).  If no error occurs but enqueue() fails
 * anyway, it must call usb_hcd_unlink_urb_from_ep() beक्रमe releasing
 * the निजी spinlock and वापसing.
 */
पूर्णांक usb_hcd_link_urb_to_ep(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	पूर्णांक		rc = 0;

	spin_lock(&hcd_urb_list_lock);

	/* Check that the URB isn't being समाप्तed */
	अगर (unlikely(atomic_पढ़ो(&urb->reject))) अणु
		rc = -EPERM;
		जाओ करोne;
	पूर्ण

	अगर (unlikely(!urb->ep->enabled)) अणु
		rc = -ENOENT;
		जाओ करोne;
	पूर्ण

	अगर (unlikely(!urb->dev->can_submit)) अणु
		rc = -EHOSTUNREACH;
		जाओ करोne;
	पूर्ण

	/*
	 * Check the host controller's state and add the URB to the
	 * endpoपूर्णांक's queue.
	 */
	अगर (HCD_RH_RUNNING(hcd)) अणु
		urb->unlinked = 0;
		list_add_tail(&urb->urb_list, &urb->ep->urb_list);
	पूर्ण अन्यथा अणु
		rc = -ESHUTDOWN;
		जाओ करोne;
	पूर्ण
 करोne:
	spin_unlock(&hcd_urb_list_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_link_urb_to_ep);

/**
 * usb_hcd_check_unlink_urb - check whether an URB may be unlinked
 * @hcd: host controller to which @urb was submitted
 * @urb: URB being checked क्रम unlinkability
 * @status: error code to store in @urb अगर the unlink succeeds
 *
 * Host controller drivers should call this routine in their dequeue()
 * method.  The HCD's निजी spinlock must be held and पूर्णांकerrupts must
 * be disabled.  The actions carried out here are required क्रम making
 * sure than an unlink is valid.
 *
 * Return: 0 क्रम no error, otherwise a negative error code (in which हाल
 * the dequeue() method must fail).  The possible error codes are:
 *
 *	-EIDRM: @urb was not submitted or has alपढ़ोy completed.
 *		The completion function may not have been called yet.
 *
 *	-EBUSY: @urb has alपढ़ोy been unlinked.
 */
पूर्णांक usb_hcd_check_unlink_urb(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		पूर्णांक status)
अणु
	काष्ठा list_head	*पंचांगp;

	/* insist the urb is still queued */
	list_क्रम_each(पंचांगp, &urb->ep->urb_list) अणु
		अगर (पंचांगp == &urb->urb_list)
			अवरोध;
	पूर्ण
	अगर (पंचांगp != &urb->urb_list)
		वापस -EIDRM;

	/* Any status except -EINPROGRESS means something alपढ़ोy started to
	 * unlink this URB from the hardware.  So there's no more work to करो.
	 */
	अगर (urb->unlinked)
		वापस -EBUSY;
	urb->unlinked = status;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_check_unlink_urb);

/**
 * usb_hcd_unlink_urb_from_ep - हटाओ an URB from its endpoपूर्णांक queue
 * @hcd: host controller to which @urb was submitted
 * @urb: URB being unlinked
 *
 * Host controller drivers should call this routine beक्रमe calling
 * usb_hcd_giveback_urb().  The HCD's निजी spinlock must be held and
 * पूर्णांकerrupts must be disabled.  The actions carried out here are required
 * क्रम URB completion.
 */
व्योम usb_hcd_unlink_urb_from_ep(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	/* clear all state linking urb to this dev (and hcd) */
	spin_lock(&hcd_urb_list_lock);
	list_del_init(&urb->urb_list);
	spin_unlock(&hcd_urb_list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_unlink_urb_from_ep);

/*
 * Some usb host controllers can only perक्रमm dma using a small SRAM area.
 * The usb core itself is however optimized क्रम host controllers that can dma
 * using regular प्रणाली memory - like pci devices करोing bus mastering.
 *
 * To support host controllers with limited dma capabilities we provide dma
 * bounce buffers. This feature can be enabled by initializing
 * hcd->localmem_pool using usb_hcd_setup_local_mem().
 *
 * The initialized hcd->localmem_pool then tells the usb code to allocate all
 * data क्रम dma using the genalloc API.
 *
 * So, to summarize...
 *
 * - We need "local" memory, canonical example being
 *   a small SRAM on a discrete controller being the
 *   only memory that the controller can पढ़ो ...
 *   (a) "normal" kernel memory is no good, and
 *   (b) there's not enough to share
 *
 * - So we use that, even though the primary requirement
 *   is that the memory be "local" (hence addressable
 *   by that device), not "coherent".
 *
 */

अटल पूर्णांक hcd_alloc_coherent(काष्ठा usb_bus *bus,
			      gfp_t mem_flags, dma_addr_t *dma_handle,
			      व्योम **vaddr_handle, माप_प्रकार size,
			      क्रमागत dma_data_direction dir)
अणु
	अचिन्हित अक्षर *vaddr;

	अगर (*vaddr_handle == शून्य) अणु
		WARN_ON_ONCE(1);
		वापस -EFAULT;
	पूर्ण

	vaddr = hcd_buffer_alloc(bus, size + माप(vaddr),
				 mem_flags, dma_handle);
	अगर (!vaddr)
		वापस -ENOMEM;

	/*
	 * Store the भव address of the buffer at the end
	 * of the allocated dma buffer. The size of the buffer
	 * may be uneven so use unaligned functions instead
	 * of just rounding up. It makes sense to optimize क्रम
	 * memory footprपूर्णांक over access speed since the amount
	 * of memory available क्रम dma may be limited.
	 */
	put_unaligned((अचिन्हित दीर्घ)*vaddr_handle,
		      (अचिन्हित दीर्घ *)(vaddr + size));

	अगर (dir == DMA_TO_DEVICE)
		स_नकल(vaddr, *vaddr_handle, size);

	*vaddr_handle = vaddr;
	वापस 0;
पूर्ण

अटल व्योम hcd_मुक्त_coherent(काष्ठा usb_bus *bus, dma_addr_t *dma_handle,
			      व्योम **vaddr_handle, माप_प्रकार size,
			      क्रमागत dma_data_direction dir)
अणु
	अचिन्हित अक्षर *vaddr = *vaddr_handle;

	vaddr = (व्योम *)get_unaligned((अचिन्हित दीर्घ *)(vaddr + size));

	अगर (dir == DMA_FROM_DEVICE)
		स_नकल(vaddr, *vaddr_handle, size);

	hcd_buffer_मुक्त(bus, size + माप(vaddr), *vaddr_handle, *dma_handle);

	*vaddr_handle = vaddr;
	*dma_handle = 0;
पूर्ण

व्योम usb_hcd_unmap_urb_setup_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	अगर (IS_ENABLED(CONFIG_HAS_DMA) &&
	    (urb->transfer_flags & URB_SETUP_MAP_SINGLE))
		dma_unmap_single(hcd->self.sysdev,
				urb->setup_dma,
				माप(काष्ठा usb_ctrlrequest),
				DMA_TO_DEVICE);
	अन्यथा अगर (urb->transfer_flags & URB_SETUP_MAP_LOCAL)
		hcd_मुक्त_coherent(urb->dev->bus,
				&urb->setup_dma,
				(व्योम **) &urb->setup_packet,
				माप(काष्ठा usb_ctrlrequest),
				DMA_TO_DEVICE);

	/* Make it safe to call this routine more than once */
	urb->transfer_flags &= ~(URB_SETUP_MAP_SINGLE | URB_SETUP_MAP_LOCAL);
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_unmap_urb_setup_क्रम_dma);

अटल व्योम unmap_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	अगर (hcd->driver->unmap_urb_क्रम_dma)
		hcd->driver->unmap_urb_क्रम_dma(hcd, urb);
	अन्यथा
		usb_hcd_unmap_urb_क्रम_dma(hcd, urb);
पूर्ण

व्योम usb_hcd_unmap_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	क्रमागत dma_data_direction dir;

	usb_hcd_unmap_urb_setup_क्रम_dma(hcd, urb);

	dir = usb_urb_dir_in(urb) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	अगर (IS_ENABLED(CONFIG_HAS_DMA) &&
	    (urb->transfer_flags & URB_DMA_MAP_SG))
		dma_unmap_sg(hcd->self.sysdev,
				urb->sg,
				urb->num_sgs,
				dir);
	अन्यथा अगर (IS_ENABLED(CONFIG_HAS_DMA) &&
		 (urb->transfer_flags & URB_DMA_MAP_PAGE))
		dma_unmap_page(hcd->self.sysdev,
				urb->transfer_dma,
				urb->transfer_buffer_length,
				dir);
	अन्यथा अगर (IS_ENABLED(CONFIG_HAS_DMA) &&
		 (urb->transfer_flags & URB_DMA_MAP_SINGLE))
		dma_unmap_single(hcd->self.sysdev,
				urb->transfer_dma,
				urb->transfer_buffer_length,
				dir);
	अन्यथा अगर (urb->transfer_flags & URB_MAP_LOCAL)
		hcd_मुक्त_coherent(urb->dev->bus,
				&urb->transfer_dma,
				&urb->transfer_buffer,
				urb->transfer_buffer_length,
				dir);

	/* Make it safe to call this routine more than once */
	urb->transfer_flags &= ~(URB_DMA_MAP_SG | URB_DMA_MAP_PAGE |
			URB_DMA_MAP_SINGLE | URB_MAP_LOCAL);
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_unmap_urb_क्रम_dma);

अटल पूर्णांक map_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
			   gfp_t mem_flags)
अणु
	अगर (hcd->driver->map_urb_क्रम_dma)
		वापस hcd->driver->map_urb_क्रम_dma(hcd, urb, mem_flags);
	अन्यथा
		वापस usb_hcd_map_urb_क्रम_dma(hcd, urb, mem_flags);
पूर्ण

पूर्णांक usb_hcd_map_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
			    gfp_t mem_flags)
अणु
	क्रमागत dma_data_direction dir;
	पूर्णांक ret = 0;

	/* Map the URB's buffers क्रम DMA access.
	 * Lower level HCD code should use *_dma exclusively,
	 * unless it uses pio or talks to another transport,
	 * or uses the provided scatter gather list क्रम bulk.
	 */

	अगर (usb_endpoपूर्णांक_xfer_control(&urb->ep->desc)) अणु
		अगर (hcd->self.uses_pio_क्रम_control)
			वापस ret;
		अगर (hcd->localmem_pool) अणु
			ret = hcd_alloc_coherent(
					urb->dev->bus, mem_flags,
					&urb->setup_dma,
					(व्योम **)&urb->setup_packet,
					माप(काष्ठा usb_ctrlrequest),
					DMA_TO_DEVICE);
			अगर (ret)
				वापस ret;
			urb->transfer_flags |= URB_SETUP_MAP_LOCAL;
		पूर्ण अन्यथा अगर (hcd_uses_dma(hcd)) अणु
			अगर (object_is_on_stack(urb->setup_packet)) अणु
				WARN_ONCE(1, "setup packet is on stack\n");
				वापस -EAGAIN;
			पूर्ण

			urb->setup_dma = dma_map_single(
					hcd->self.sysdev,
					urb->setup_packet,
					माप(काष्ठा usb_ctrlrequest),
					DMA_TO_DEVICE);
			अगर (dma_mapping_error(hcd->self.sysdev,
						urb->setup_dma))
				वापस -EAGAIN;
			urb->transfer_flags |= URB_SETUP_MAP_SINGLE;
		पूर्ण
	पूर्ण

	dir = usb_urb_dir_in(urb) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	अगर (urb->transfer_buffer_length != 0
	    && !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)) अणु
		अगर (hcd->localmem_pool) अणु
			ret = hcd_alloc_coherent(
					urb->dev->bus, mem_flags,
					&urb->transfer_dma,
					&urb->transfer_buffer,
					urb->transfer_buffer_length,
					dir);
			अगर (ret == 0)
				urb->transfer_flags |= URB_MAP_LOCAL;
		पूर्ण अन्यथा अगर (hcd_uses_dma(hcd)) अणु
			अगर (urb->num_sgs) अणु
				पूर्णांक n;

				/* We करोn't support sg क्रम isoc transfers ! */
				अगर (usb_endpoपूर्णांक_xfer_isoc(&urb->ep->desc)) अणु
					WARN_ON(1);
					वापस -EINVAL;
				पूर्ण

				n = dma_map_sg(
						hcd->self.sysdev,
						urb->sg,
						urb->num_sgs,
						dir);
				अगर (n <= 0)
					ret = -EAGAIN;
				अन्यथा
					urb->transfer_flags |= URB_DMA_MAP_SG;
				urb->num_mapped_sgs = n;
				अगर (n != urb->num_sgs)
					urb->transfer_flags |=
							URB_DMA_SG_COMBINED;
			पूर्ण अन्यथा अगर (urb->sg) अणु
				काष्ठा scatterlist *sg = urb->sg;
				urb->transfer_dma = dma_map_page(
						hcd->self.sysdev,
						sg_page(sg),
						sg->offset,
						urb->transfer_buffer_length,
						dir);
				अगर (dma_mapping_error(hcd->self.sysdev,
						urb->transfer_dma))
					ret = -EAGAIN;
				अन्यथा
					urb->transfer_flags |= URB_DMA_MAP_PAGE;
			पूर्ण अन्यथा अगर (object_is_on_stack(urb->transfer_buffer)) अणु
				WARN_ONCE(1, "transfer buffer is on stack\n");
				ret = -EAGAIN;
			पूर्ण अन्यथा अणु
				urb->transfer_dma = dma_map_single(
						hcd->self.sysdev,
						urb->transfer_buffer,
						urb->transfer_buffer_length,
						dir);
				अगर (dma_mapping_error(hcd->self.sysdev,
						urb->transfer_dma))
					ret = -EAGAIN;
				अन्यथा
					urb->transfer_flags |= URB_DMA_MAP_SINGLE;
			पूर्ण
		पूर्ण
		अगर (ret && (urb->transfer_flags & (URB_SETUP_MAP_SINGLE |
				URB_SETUP_MAP_LOCAL)))
			usb_hcd_unmap_urb_क्रम_dma(hcd, urb);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_map_urb_क्रम_dma);

/*-------------------------------------------------------------------------*/

/* may be called in any context with a valid urb->dev usecount
 * caller surrenders "ownership" of urb
 * expects usb_submit_urb() to have sanity checked and conditioned all
 * inमाला_दो in the urb
 */
पूर्णांक usb_hcd_submit_urb (काष्ठा urb *urb, gfp_t mem_flags)
अणु
	पूर्णांक			status;
	काष्ठा usb_hcd		*hcd = bus_to_hcd(urb->dev->bus);

	/* increment urb's reference count as part of giving it to the HCD
	 * (which will control it).  HCD guarantees that it either वापसs
	 * an error or calls giveback(), but not both.
	 */
	usb_get_urb(urb);
	atomic_inc(&urb->use_count);
	atomic_inc(&urb->dev->urbnum);
	usbmon_urb_submit(&hcd->self, urb);

	/* NOTE requirements on root-hub callers (usbfs and the hub
	 * driver, क्रम now):  URBs' urb->transfer_buffer must be
	 * valid and usb_buffer_अणुsync,unmapपूर्ण() not be needed, since
	 * they could clobber root hub response data.  Also, control
	 * URBs must be submitted in process context with पूर्णांकerrupts
	 * enabled.
	 */

	अगर (is_root_hub(urb->dev)) अणु
		status = rh_urb_enqueue(hcd, urb);
	पूर्ण अन्यथा अणु
		status = map_urb_क्रम_dma(hcd, urb, mem_flags);
		अगर (likely(status == 0)) अणु
			status = hcd->driver->urb_enqueue(hcd, urb, mem_flags);
			अगर (unlikely(status))
				unmap_urb_क्रम_dma(hcd, urb);
		पूर्ण
	पूर्ण

	अगर (unlikely(status)) अणु
		usbmon_urb_submit_error(&hcd->self, urb, status);
		urb->hcpriv = शून्य;
		INIT_LIST_HEAD(&urb->urb_list);
		atomic_dec(&urb->use_count);
		atomic_dec(&urb->dev->urbnum);
		अगर (atomic_पढ़ो(&urb->reject))
			wake_up(&usb_समाप्त_urb_queue);
		usb_put_urb(urb);
	पूर्ण
	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

/* this makes the hcd giveback() the urb more quickly, by kicking it
 * off hardware queues (which may take a जबतक) and वापसing it as
 * soon as practical.  we've already set up the urb's वापस status,
 * but we can't know अगर the callback completed alपढ़ोy.
 */
अटल पूर्णांक unlink1(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	पूर्णांक		value;

	अगर (is_root_hub(urb->dev))
		value = usb_rh_urb_dequeue(hcd, urb, status);
	अन्यथा अणु

		/* The only reason an HCD might fail this call is अगर
		 * it has not yet fully queued the urb to begin with.
		 * Such failures should be harmless. */
		value = hcd->driver->urb_dequeue(hcd, urb, status);
	पूर्ण
	वापस value;
पूर्ण

/*
 * called in any context
 *
 * caller guarantees urb won't be recycled till both unlink()
 * and the urb's completion function वापस
 */
पूर्णांक usb_hcd_unlink_urb (काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा usb_hcd		*hcd;
	काष्ठा usb_device	*udev = urb->dev;
	पूर्णांक			retval = -EIDRM;
	अचिन्हित दीर्घ		flags;

	/* Prevent the device and bus from going away जबतक
	 * the unlink is carried out.  If they are alपढ़ोy gone
	 * then urb->use_count must be 0, since disconnected
	 * devices can't have any active URBs.
	 */
	spin_lock_irqsave(&hcd_urb_unlink_lock, flags);
	अगर (atomic_पढ़ो(&urb->use_count) > 0) अणु
		retval = 0;
		usb_get_dev(udev);
	पूर्ण
	spin_unlock_irqrestore(&hcd_urb_unlink_lock, flags);
	अगर (retval == 0) अणु
		hcd = bus_to_hcd(urb->dev->bus);
		retval = unlink1(hcd, urb, status);
		अगर (retval == 0)
			retval = -EINPROGRESS;
		अन्यथा अगर (retval != -EIDRM && retval != -EBUSY)
			dev_dbg(&udev->dev, "hcd_unlink_urb %pK fail %d\n",
					urb, retval);
		usb_put_dev(udev);
	पूर्ण
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम __usb_hcd_giveback_urb(काष्ठा urb *urb)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(urb->dev->bus);
	काष्ठा usb_anchor *anchor = urb->anchor;
	पूर्णांक status = urb->unlinked;

	urb->hcpriv = शून्य;
	अगर (unlikely((urb->transfer_flags & URB_SHORT_NOT_OK) &&
	    urb->actual_length < urb->transfer_buffer_length &&
	    !status))
		status = -EREMOTEIO;

	unmap_urb_क्रम_dma(hcd, urb);
	usbmon_urb_complete(&hcd->self, urb, status);
	usb_anchor_suspend_wakeups(anchor);
	usb_unanchor_urb(urb);
	अगर (likely(status == 0))
		usb_led_activity(USB_LED_EVENT_HOST);

	/* pass ownership to the completion handler */
	urb->status = status;
	/*
	 * This function can be called in task context inside another remote
	 * coverage collection section, but kcov करोesn't support that kind of
	 * recursion yet. Only collect coverage in softirq context क्रम now.
	 */
	kcov_remote_start_usb_softirq((u64)urb->dev->bus->busnum);
	urb->complete(urb);
	kcov_remote_stop_softirq();

	usb_anchor_resume_wakeups(anchor);
	atomic_dec(&urb->use_count);
	अगर (unlikely(atomic_पढ़ो(&urb->reject)))
		wake_up(&usb_समाप्त_urb_queue);
	usb_put_urb(urb);
पूर्ण

अटल व्योम usb_giveback_urb_bh(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा giveback_urb_bh *bh = from_tasklet(bh, t, bh);
	काष्ठा list_head local_list;

	spin_lock_irq(&bh->lock);
	bh->running = true;
 restart:
	list_replace_init(&bh->head, &local_list);
	spin_unlock_irq(&bh->lock);

	जबतक (!list_empty(&local_list)) अणु
		काष्ठा urb *urb;

		urb = list_entry(local_list.next, काष्ठा urb, urb_list);
		list_del_init(&urb->urb_list);
		bh->completing_ep = urb->ep;
		__usb_hcd_giveback_urb(urb);
		bh->completing_ep = शून्य;
	पूर्ण

	/* check अगर there are new URBs to giveback */
	spin_lock_irq(&bh->lock);
	अगर (!list_empty(&bh->head))
		जाओ restart;
	bh->running = false;
	spin_unlock_irq(&bh->lock);
पूर्ण

/**
 * usb_hcd_giveback_urb - वापस URB from HCD to device driver
 * @hcd: host controller वापसing the URB
 * @urb: urb being वापसed to the USB device driver.
 * @status: completion status code क्रम the URB.
 *
 * Context: atomic. The completion callback is invoked in caller's context.
 * For HCDs with HCD_BH flag set, the completion callback is invoked in tasklet
 * context (except क्रम URBs submitted to the root hub which always complete in
 * caller's context).
 *
 * This hands the URB from HCD to its USB device driver, using its
 * completion function.  The HCD has मुक्तd all per-urb resources
 * (and is करोne using urb->hcpriv).  It also released all HCD locks;
 * the device driver won't cause problems अगर it मुक्तs, modअगरies,
 * or resubmits this URB.
 *
 * If @urb was unlinked, the value of @status will be overridden by
 * @urb->unlinked.  Erroneous लघु transfers are detected in हाल
 * the HCD hasn't checked क्रम them.
 */
व्योम usb_hcd_giveback_urb(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा giveback_urb_bh *bh;
	bool running, high_prio_bh;

	/* pass status to tasklet via unlinked */
	अगर (likely(!urb->unlinked))
		urb->unlinked = status;

	अगर (!hcd_giveback_urb_in_bh(hcd) && !is_root_hub(urb->dev)) अणु
		__usb_hcd_giveback_urb(urb);
		वापस;
	पूर्ण

	अगर (usb_pipeisoc(urb->pipe) || usb_pipeपूर्णांक(urb->pipe)) अणु
		bh = &hcd->high_prio_bh;
		high_prio_bh = true;
	पूर्ण अन्यथा अणु
		bh = &hcd->low_prio_bh;
		high_prio_bh = false;
	पूर्ण

	spin_lock(&bh->lock);
	list_add_tail(&urb->urb_list, &bh->head);
	running = bh->running;
	spin_unlock(&bh->lock);

	अगर (running)
		;
	अन्यथा अगर (high_prio_bh)
		tasklet_hi_schedule(&bh->bh);
	अन्यथा
		tasklet_schedule(&bh->bh);
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_giveback_urb);

/*-------------------------------------------------------------------------*/

/* Cancel all URBs pending on this endpoपूर्णांक and रुको क्रम the endpoपूर्णांक's
 * queue to drain completely.  The caller must first insure that no more
 * URBs can be submitted क्रम this endpoपूर्णांक.
 */
व्योम usb_hcd_flush_endpoपूर्णांक(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा usb_hcd		*hcd;
	काष्ठा urb		*urb;

	अगर (!ep)
		वापस;
	might_sleep();
	hcd = bus_to_hcd(udev->bus);

	/* No more submits can occur */
	spin_lock_irq(&hcd_urb_list_lock);
rescan:
	list_क्रम_each_entry_reverse(urb, &ep->urb_list, urb_list) अणु
		पूर्णांक	is_in;

		अगर (urb->unlinked)
			जारी;
		usb_get_urb (urb);
		is_in = usb_urb_dir_in(urb);
		spin_unlock(&hcd_urb_list_lock);

		/* kick hcd */
		unlink1(hcd, urb, -ESHUTDOWN);
		dev_dbg (hcd->self.controller,
			"shutdown urb %pK ep%d%s-%s\n",
			urb, usb_endpoपूर्णांक_num(&ep->desc),
			is_in ? "in" : "out",
			usb_ep_type_string(usb_endpoपूर्णांक_type(&ep->desc)));
		usb_put_urb (urb);

		/* list contents may have changed */
		spin_lock(&hcd_urb_list_lock);
		जाओ rescan;
	पूर्ण
	spin_unlock_irq(&hcd_urb_list_lock);

	/* Wait until the endpoपूर्णांक queue is completely empty */
	जबतक (!list_empty (&ep->urb_list)) अणु
		spin_lock_irq(&hcd_urb_list_lock);

		/* The list may have changed जबतक we acquired the spinlock */
		urb = शून्य;
		अगर (!list_empty (&ep->urb_list)) अणु
			urb = list_entry (ep->urb_list.prev, काष्ठा urb,
					urb_list);
			usb_get_urb (urb);
		पूर्ण
		spin_unlock_irq(&hcd_urb_list_lock);

		अगर (urb) अणु
			usb_समाप्त_urb (urb);
			usb_put_urb (urb);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * usb_hcd_alloc_bandwidth - check whether a new bandwidth setting exceeds
 *				the bus bandwidth
 * @udev: target &usb_device
 * @new_config: new configuration to install
 * @cur_alt: the current alternate पूर्णांकerface setting
 * @new_alt: alternate पूर्णांकerface setting that is being installed
 *
 * To change configurations, pass in the new configuration in new_config,
 * and pass शून्य क्रम cur_alt and new_alt.
 *
 * To reset a device's configuration (put the device in the ADDRESSED state),
 * pass in शून्य क्रम new_config, cur_alt, and new_alt.
 *
 * To change alternate पूर्णांकerface settings, pass in शून्य क्रम new_config,
 * pass in the current alternate पूर्णांकerface setting in cur_alt,
 * and pass in the new alternate पूर्णांकerface setting in new_alt.
 *
 * Return: An error अगर the requested bandwidth change exceeds the
 * bus bandwidth or host controller पूर्णांकernal resources.
 */
पूर्णांक usb_hcd_alloc_bandwidth(काष्ठा usb_device *udev,
		काष्ठा usb_host_config *new_config,
		काष्ठा usb_host_पूर्णांकerface *cur_alt,
		काष्ठा usb_host_पूर्णांकerface *new_alt)
अणु
	पूर्णांक num_पूर्णांकfs, i, j;
	काष्ठा usb_host_पूर्णांकerface *alt = शून्य;
	पूर्णांक ret = 0;
	काष्ठा usb_hcd *hcd;
	काष्ठा usb_host_endpoपूर्णांक *ep;

	hcd = bus_to_hcd(udev->bus);
	अगर (!hcd->driver->check_bandwidth)
		वापस 0;

	/* Configuration is being हटाओd - set configuration 0 */
	अगर (!new_config && !cur_alt) अणु
		क्रम (i = 1; i < 16; ++i) अणु
			ep = udev->ep_out[i];
			अगर (ep)
				hcd->driver->drop_endpoपूर्णांक(hcd, udev, ep);
			ep = udev->ep_in[i];
			अगर (ep)
				hcd->driver->drop_endpoपूर्णांक(hcd, udev, ep);
		पूर्ण
		hcd->driver->check_bandwidth(hcd, udev);
		वापस 0;
	पूर्ण
	/* Check अगर the HCD says there's enough bandwidth.  Enable all endpoपूर्णांकs
	 * each पूर्णांकerface's alt setting 0 and ask the HCD to check the bandwidth
	 * of the bus.  There will always be bandwidth क्रम endpoपूर्णांक 0, so it's
	 * ok to exclude it.
	 */
	अगर (new_config) अणु
		num_पूर्णांकfs = new_config->desc.bNumInterfaces;
		/* Remove endpoपूर्णांकs (except endpoपूर्णांक 0, which is always on the
		 * schedule) from the old config from the schedule
		 */
		क्रम (i = 1; i < 16; ++i) अणु
			ep = udev->ep_out[i];
			अगर (ep) अणु
				ret = hcd->driver->drop_endpoपूर्णांक(hcd, udev, ep);
				अगर (ret < 0)
					जाओ reset;
			पूर्ण
			ep = udev->ep_in[i];
			अगर (ep) अणु
				ret = hcd->driver->drop_endpoपूर्णांक(hcd, udev, ep);
				अगर (ret < 0)
					जाओ reset;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < num_पूर्णांकfs; ++i) अणु
			काष्ठा usb_host_पूर्णांकerface *first_alt;
			पूर्णांक अगरace_num;

			first_alt = &new_config->पूर्णांकf_cache[i]->altsetting[0];
			अगरace_num = first_alt->desc.bInterfaceNumber;
			/* Set up endpoपूर्णांकs क्रम alternate पूर्णांकerface setting 0 */
			alt = usb_find_alt_setting(new_config, अगरace_num, 0);
			अगर (!alt)
				/* No alt setting 0? Pick the first setting. */
				alt = first_alt;

			क्रम (j = 0; j < alt->desc.bNumEndpoपूर्णांकs; j++) अणु
				ret = hcd->driver->add_endpoपूर्णांक(hcd, udev, &alt->endpoपूर्णांक[j]);
				अगर (ret < 0)
					जाओ reset;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (cur_alt && new_alt) अणु
		काष्ठा usb_पूर्णांकerface *अगरace = usb_अगरnum_to_अगर(udev,
				cur_alt->desc.bInterfaceNumber);

		अगर (!अगरace)
			वापस -EINVAL;
		अगर (अगरace->resetting_device) अणु
			/*
			 * The USB core just reset the device, so the xHCI host
			 * and the device will think alt setting 0 is installed.
			 * However, the USB core will pass in the alternate
			 * setting installed beक्रमe the reset as cur_alt.  Dig
			 * out the alternate setting 0 काष्ठाure, or the first
			 * alternate setting अगर a broken device करोesn't have alt
			 * setting 0.
			 */
			cur_alt = usb_altnum_to_altsetting(अगरace, 0);
			अगर (!cur_alt)
				cur_alt = &अगरace->altsetting[0];
		पूर्ण

		/* Drop all the endpoपूर्णांकs in the current alt setting */
		क्रम (i = 0; i < cur_alt->desc.bNumEndpoपूर्णांकs; i++) अणु
			ret = hcd->driver->drop_endpoपूर्णांक(hcd, udev,
					&cur_alt->endpoपूर्णांक[i]);
			अगर (ret < 0)
				जाओ reset;
		पूर्ण
		/* Add all the endpoपूर्णांकs in the new alt setting */
		क्रम (i = 0; i < new_alt->desc.bNumEndpoपूर्णांकs; i++) अणु
			ret = hcd->driver->add_endpoपूर्णांक(hcd, udev,
					&new_alt->endpoपूर्णांक[i]);
			अगर (ret < 0)
				जाओ reset;
		पूर्ण
	पूर्ण
	ret = hcd->driver->check_bandwidth(hcd, udev);
reset:
	अगर (ret < 0)
		hcd->driver->reset_bandwidth(hcd, udev);
	वापस ret;
पूर्ण

/* Disables the endpoपूर्णांक: synchronizes with the hcd to make sure all
 * endpoपूर्णांक state is gone from hardware.  usb_hcd_flush_endpoपूर्णांक() must
 * have been called previously.  Use क्रम set_configuration, set_पूर्णांकerface,
 * driver removal, physical disconnect.
 *
 * example:  a qh stored in ep->hcpriv, holding state related to endpoपूर्णांक
 * type, maxpacket size, toggle, halt status, and scheduling.
 */
व्योम usb_hcd_disable_endpoपूर्णांक(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा usb_hcd		*hcd;

	might_sleep();
	hcd = bus_to_hcd(udev->bus);
	अगर (hcd->driver->endpoपूर्णांक_disable)
		hcd->driver->endpoपूर्णांक_disable(hcd, ep);
पूर्ण

/**
 * usb_hcd_reset_endpoपूर्णांक - reset host endpoपूर्णांक state
 * @udev: USB device.
 * @ep:   the endpoपूर्णांक to reset.
 *
 * Resets any host endpoपूर्णांक state such as the toggle bit, sequence
 * number and current winकरोw.
 */
व्योम usb_hcd_reset_endpoपूर्णांक(काष्ठा usb_device *udev,
			    काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(udev->bus);

	अगर (hcd->driver->endpoपूर्णांक_reset)
		hcd->driver->endpoपूर्णांक_reset(hcd, ep);
	अन्यथा अणु
		पूर्णांक epnum = usb_endpoपूर्णांक_num(&ep->desc);
		पूर्णांक is_out = usb_endpoपूर्णांक_dir_out(&ep->desc);
		पूर्णांक is_control = usb_endpoपूर्णांक_xfer_control(&ep->desc);

		usb_settoggle(udev, epnum, is_out, 0);
		अगर (is_control)
			usb_settoggle(udev, epnum, !is_out, 0);
	पूर्ण
पूर्ण

/**
 * usb_alloc_streams - allocate bulk endpoपूर्णांक stream IDs.
 * @पूर्णांकerface:		alternate setting that includes all endpoपूर्णांकs.
 * @eps:		array of endpoपूर्णांकs that need streams.
 * @num_eps:		number of endpoपूर्णांकs in the array.
 * @num_streams:	number of streams to allocate.
 * @mem_flags:		flags hcd should use to allocate memory.
 *
 * Sets up a group of bulk endpoपूर्णांकs to have @num_streams stream IDs available.
 * Drivers may queue multiple transfers to dअगरferent stream IDs, which may
 * complete in a dअगरferent order than they were queued.
 *
 * Return: On success, the number of allocated streams. On failure, a negative
 * error code.
 */
पूर्णांक usb_alloc_streams(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
		अचिन्हित पूर्णांक num_streams, gfp_t mem_flags)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा usb_device *dev;
	पूर्णांक i, ret;

	dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	hcd = bus_to_hcd(dev->bus);
	अगर (!hcd->driver->alloc_streams || !hcd->driver->मुक्त_streams)
		वापस -EINVAL;
	अगर (dev->speed < USB_SPEED_SUPER)
		वापस -EINVAL;
	अगर (dev->state < USB_STATE_CONFIGURED)
		वापस -ENODEV;

	क्रम (i = 0; i < num_eps; i++) अणु
		/* Streams only apply to bulk endpoपूर्णांकs. */
		अगर (!usb_endpoपूर्णांक_xfer_bulk(&eps[i]->desc))
			वापस -EINVAL;
		/* Re-alloc is not allowed */
		अगर (eps[i]->streams)
			वापस -EINVAL;
	पूर्ण

	ret = hcd->driver->alloc_streams(hcd, dev, eps, num_eps,
			num_streams, mem_flags);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < num_eps; i++)
		eps[i]->streams = ret;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_alloc_streams);

/**
 * usb_मुक्त_streams - मुक्त bulk endpoपूर्णांक stream IDs.
 * @पूर्णांकerface:	alternate setting that includes all endpoपूर्णांकs.
 * @eps:	array of endpoपूर्णांकs to हटाओ streams from.
 * @num_eps:	number of endpoपूर्णांकs in the array.
 * @mem_flags:	flags hcd should use to allocate memory.
 *
 * Reverts a group of bulk endpoपूर्णांकs back to not using stream IDs.
 * Can fail अगर we are given bad arguments, or HCD is broken.
 *
 * Return: 0 on success. On failure, a negative error code.
 */
पूर्णांक usb_मुक्त_streams(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
		gfp_t mem_flags)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा usb_device *dev;
	पूर्णांक i, ret;

	dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	hcd = bus_to_hcd(dev->bus);
	अगर (dev->speed < USB_SPEED_SUPER)
		वापस -EINVAL;

	/* Double-मुक्त is not allowed */
	क्रम (i = 0; i < num_eps; i++)
		अगर (!eps[i] || !eps[i]->streams)
			वापस -EINVAL;

	ret = hcd->driver->मुक्त_streams(hcd, dev, eps, num_eps, mem_flags);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < num_eps; i++)
		eps[i]->streams = 0;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_मुक्त_streams);

/* Protect against drivers that try to unlink URBs after the device
 * is gone, by रुकोing until all unlinks क्रम @udev are finished.
 * Since we करोn't currently track URBs by device, simply रुको until
 * nothing is running in the locked region of usb_hcd_unlink_urb().
 */
व्योम usb_hcd_synchronize_unlinks(काष्ठा usb_device *udev)
अणु
	spin_lock_irq(&hcd_urb_unlink_lock);
	spin_unlock_irq(&hcd_urb_unlink_lock);
पूर्ण

/*-------------------------------------------------------------------------*/

/* called in any context */
पूर्णांक usb_hcd_get_frame_number (काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd	*hcd = bus_to_hcd(udev->bus);

	अगर (!HCD_RH_RUNNING(hcd))
		वापस -ESHUTDOWN;
	वापस hcd->driver->get_frame_number (hcd);
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित	CONFIG_PM

पूर्णांक hcd_bus_suspend(काष्ठा usb_device *rhdev, pm_message_t msg)
अणु
	काष्ठा usb_hcd	*hcd = bus_to_hcd(rhdev->bus);
	पूर्णांक		status;
	पूर्णांक		old_state = hcd->state;

	dev_dbg(&rhdev->dev, "bus %ssuspend, wakeup %d\n",
			(PMSG_IS_AUTO(msg) ? "auto-" : ""),
			rhdev->करो_remote_wakeup);
	अगर (HCD_DEAD(hcd)) अणु
		dev_dbg(&rhdev->dev, "skipped %s of dead bus\n", "suspend");
		वापस 0;
	पूर्ण

	अगर (!hcd->driver->bus_suspend) अणु
		status = -ENOENT;
	पूर्ण अन्यथा अणु
		clear_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);
		hcd->state = HC_STATE_QUIESCING;
		status = hcd->driver->bus_suspend(hcd);
	पूर्ण
	अगर (status == 0) अणु
		usb_set_device_state(rhdev, USB_STATE_SUSPENDED);
		hcd->state = HC_STATE_SUSPENDED;

		अगर (!PMSG_IS_AUTO(msg))
			usb_phy_roothub_suspend(hcd->self.sysdev,
						hcd->phy_roothub);

		/* Did we race with a root-hub wakeup event? */
		अगर (rhdev->करो_remote_wakeup) अणु
			अक्षर	buffer[6];

			status = hcd->driver->hub_status_data(hcd, buffer);
			अगर (status != 0) अणु
				dev_dbg(&rhdev->dev, "suspend raced with wakeup event\n");
				hcd_bus_resume(rhdev, PMSG_AUTO_RESUME);
				status = -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_lock_irq(&hcd_root_hub_lock);
		अगर (!HCD_DEAD(hcd)) अणु
			set_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);
			hcd->state = old_state;
		पूर्ण
		spin_unlock_irq(&hcd_root_hub_lock);
		dev_dbg(&rhdev->dev, "bus %s fail, err %d\n",
				"suspend", status);
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक hcd_bus_resume(काष्ठा usb_device *rhdev, pm_message_t msg)
अणु
	काष्ठा usb_hcd	*hcd = bus_to_hcd(rhdev->bus);
	पूर्णांक		status;
	पूर्णांक		old_state = hcd->state;

	dev_dbg(&rhdev->dev, "usb %sresume\n",
			(PMSG_IS_AUTO(msg) ? "auto-" : ""));
	अगर (HCD_DEAD(hcd)) अणु
		dev_dbg(&rhdev->dev, "skipped %s of dead bus\n", "resume");
		वापस 0;
	पूर्ण

	अगर (!PMSG_IS_AUTO(msg)) अणु
		status = usb_phy_roothub_resume(hcd->self.sysdev,
						hcd->phy_roothub);
		अगर (status)
			वापस status;
	पूर्ण

	अगर (!hcd->driver->bus_resume)
		वापस -ENOENT;
	अगर (HCD_RH_RUNNING(hcd))
		वापस 0;

	hcd->state = HC_STATE_RESUMING;
	status = hcd->driver->bus_resume(hcd);
	clear_bit(HCD_FLAG_WAKEUP_PENDING, &hcd->flags);
	अगर (status == 0)
		status = usb_phy_roothub_calibrate(hcd->phy_roothub);

	अगर (status == 0) अणु
		काष्ठा usb_device *udev;
		पूर्णांक port1;

		spin_lock_irq(&hcd_root_hub_lock);
		अगर (!HCD_DEAD(hcd)) अणु
			usb_set_device_state(rhdev, rhdev->actconfig
					? USB_STATE_CONFIGURED
					: USB_STATE_ADDRESS);
			set_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);
			hcd->state = HC_STATE_RUNNING;
		पूर्ण
		spin_unlock_irq(&hcd_root_hub_lock);

		/*
		 * Check whether any of the enabled ports on the root hub are
		 * unsuspended.  If they are then a TRSMRCY delay is needed
		 * (this is what the USB-2 spec calls a "global resume").
		 * Otherwise we can skip the delay.
		 */
		usb_hub_क्रम_each_child(rhdev, port1, udev) अणु
			अगर (udev->state != USB_STATE_NOTATTACHED &&
					!udev->port_is_suspended) अणु
				usleep_range(10000, 11000);	/* TRSMRCY */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		hcd->state = old_state;
		usb_phy_roothub_suspend(hcd->self.sysdev, hcd->phy_roothub);
		dev_dbg(&rhdev->dev, "bus %s fail, err %d\n",
				"resume", status);
		अगर (status != -ESHUTDOWN)
			usb_hc_died(hcd);
	पूर्ण
	वापस status;
पूर्ण

/* Workqueue routine क्रम root-hub remote wakeup */
अटल व्योम hcd_resume_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_hcd *hcd = container_of(work, काष्ठा usb_hcd, wakeup_work);
	काष्ठा usb_device *udev = hcd->self.root_hub;

	usb_remote_wakeup(udev);
पूर्ण

/**
 * usb_hcd_resume_root_hub - called by HCD to resume its root hub
 * @hcd: host controller क्रम this root hub
 *
 * The USB host controller calls this function when its root hub is
 * suspended (with the remote wakeup feature enabled) and a remote
 * wakeup request is received.  The routine submits a workqueue request
 * to resume the root hub (that is, manage its करोwnstream ports again).
 */
व्योम usb_hcd_resume_root_hub (काष्ठा usb_hcd *hcd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave (&hcd_root_hub_lock, flags);
	अगर (hcd->rh_रेजिस्टरed) अणु
		pm_wakeup_event(&hcd->self.root_hub->dev, 0);
		set_bit(HCD_FLAG_WAKEUP_PENDING, &hcd->flags);
		queue_work(pm_wq, &hcd->wakeup_work);
	पूर्ण
	spin_unlock_irqrestore (&hcd_root_hub_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_resume_root_hub);

#पूर्ण_अगर	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

#अगर_घोषित	CONFIG_USB_OTG

/**
 * usb_bus_start_क्रमागत - start immediate क्रमागतeration (क्रम OTG)
 * @bus: the bus (must use hcd framework)
 * @port_num: 1-based number of port; usually bus->otg_port
 * Context: atomic
 *
 * Starts क्रमागतeration, with an immediate reset followed later by
 * hub_wq identअगरying and possibly configuring the device.
 * This is needed by OTG controller drivers, where it helps meet
 * HNP protocol timing requirements क्रम starting a port reset.
 *
 * Return: 0 अगर successful.
 */
पूर्णांक usb_bus_start_क्रमागत(काष्ठा usb_bus *bus, अचिन्हित port_num)
अणु
	काष्ठा usb_hcd		*hcd;
	पूर्णांक			status = -EOPNOTSUPP;

	/* NOTE: since HNP can't start by grabbing the bus's address0_sem,
	 * boards with root hubs hooked up to पूर्णांकernal devices (instead of
	 * just the OTG port) may need more attention to resetting...
	 */
	hcd = bus_to_hcd(bus);
	अगर (port_num && hcd->driver->start_port_reset)
		status = hcd->driver->start_port_reset(hcd, port_num);

	/* allocate hub_wq लघुly after (first) root port reset finishes;
	 * it may issue others, until at least 50 msecs have passed.
	 */
	अगर (status == 0)
		mod_समयr(&hcd->rh_समयr, jअगरfies + msecs_to_jअगरfies(10));
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(usb_bus_start_क्रमागत);

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/**
 * usb_hcd_irq - hook IRQs to HCD framework (bus glue)
 * @irq: the IRQ being उठाओd
 * @__hcd: poपूर्णांकer to the HCD whose IRQ is being संकेतed
 *
 * If the controller isn't HALTed, calls the driver's irq handler.
 * Checks whether the controller is now dead.
 *
 * Return: %IRQ_HANDLED अगर the IRQ was handled. %IRQ_NONE otherwise.
 */
irqवापस_t usb_hcd_irq (पूर्णांक irq, व्योम *__hcd)
अणु
	काष्ठा usb_hcd		*hcd = __hcd;
	irqवापस_t		rc;

	अगर (unlikely(HCD_DEAD(hcd) || !HCD_HW_ACCESSIBLE(hcd)))
		rc = IRQ_NONE;
	अन्यथा अगर (hcd->driver->irq(hcd) == IRQ_NONE)
		rc = IRQ_NONE;
	अन्यथा
		rc = IRQ_HANDLED;

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_irq);

/*-------------------------------------------------------------------------*/

/* Workqueue routine क्रम when the root-hub has died. */
अटल व्योम hcd_died_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_hcd *hcd = container_of(work, काष्ठा usb_hcd, died_work);
	अटल अक्षर *env[] = अणु
		"ERROR=DEAD",
		शून्य
	पूर्ण;

	/* Notअगरy user space that the host controller has died */
	kobject_uevent_env(&hcd->self.root_hub->dev.kobj, KOBJ_OFFLINE, env);
पूर्ण

/**
 * usb_hc_died - report abnormal shutकरोwn of a host controller (bus glue)
 * @hcd: poपूर्णांकer to the HCD representing the controller
 *
 * This is called by bus glue to report a USB host controller that died
 * जबतक operations may still have been pending.  It's called स्वतःmatically
 * by the PCI glue, so only glue क्रम non-PCI busses should need to call it.
 *
 * Only call this function with the primary HCD.
 */
व्योम usb_hc_died (काष्ठा usb_hcd *hcd)
अणु
	अचिन्हित दीर्घ flags;

	dev_err (hcd->self.controller, "HC died; cleaning up\n");

	spin_lock_irqsave (&hcd_root_hub_lock, flags);
	clear_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);
	set_bit(HCD_FLAG_DEAD, &hcd->flags);
	अगर (hcd->rh_रेजिस्टरed) अणु
		clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);

		/* make hub_wq clean up old urbs and devices */
		usb_set_device_state (hcd->self.root_hub,
				USB_STATE_NOTATTACHED);
		usb_kick_hub_wq(hcd->self.root_hub);
	पूर्ण
	अगर (usb_hcd_is_primary_hcd(hcd) && hcd->shared_hcd) अणु
		hcd = hcd->shared_hcd;
		clear_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);
		set_bit(HCD_FLAG_DEAD, &hcd->flags);
		अगर (hcd->rh_रेजिस्टरed) अणु
			clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);

			/* make hub_wq clean up old urbs and devices */
			usb_set_device_state(hcd->self.root_hub,
					USB_STATE_NOTATTACHED);
			usb_kick_hub_wq(hcd->self.root_hub);
		पूर्ण
	पूर्ण

	/* Handle the हाल where this function माला_लो called with a shared HCD */
	अगर (usb_hcd_is_primary_hcd(hcd))
		schedule_work(&hcd->died_work);
	अन्यथा
		schedule_work(&hcd->primary_hcd->died_work);

	spin_unlock_irqrestore (&hcd_root_hub_lock, flags);
	/* Make sure that the other roothub is also deallocated. */
पूर्ण
EXPORT_SYMBOL_GPL (usb_hc_died);

/*-------------------------------------------------------------------------*/

अटल व्योम init_giveback_urb_bh(काष्ठा giveback_urb_bh *bh)
अणु

	spin_lock_init(&bh->lock);
	INIT_LIST_HEAD(&bh->head);
	tasklet_setup(&bh->bh, usb_giveback_urb_bh);
पूर्ण

काष्ठा usb_hcd *__usb_create_hcd(स्थिर काष्ठा hc_driver *driver,
		काष्ठा device *sysdev, काष्ठा device *dev, स्थिर अक्षर *bus_name,
		काष्ठा usb_hcd *primary_hcd)
अणु
	काष्ठा usb_hcd *hcd;

	hcd = kzalloc(माप(*hcd) + driver->hcd_priv_size, GFP_KERNEL);
	अगर (!hcd)
		वापस शून्य;
	अगर (primary_hcd == शून्य) अणु
		hcd->address0_mutex = kदो_स्मृति(माप(*hcd->address0_mutex),
				GFP_KERNEL);
		अगर (!hcd->address0_mutex) अणु
			kमुक्त(hcd);
			dev_dbg(dev, "hcd address0 mutex alloc failed\n");
			वापस शून्य;
		पूर्ण
		mutex_init(hcd->address0_mutex);
		hcd->bandwidth_mutex = kदो_स्मृति(माप(*hcd->bandwidth_mutex),
				GFP_KERNEL);
		अगर (!hcd->bandwidth_mutex) अणु
			kमुक्त(hcd->address0_mutex);
			kमुक्त(hcd);
			dev_dbg(dev, "hcd bandwidth mutex alloc failed\n");
			वापस शून्य;
		पूर्ण
		mutex_init(hcd->bandwidth_mutex);
		dev_set_drvdata(dev, hcd);
	पूर्ण अन्यथा अणु
		mutex_lock(&usb_port_peer_mutex);
		hcd->address0_mutex = primary_hcd->address0_mutex;
		hcd->bandwidth_mutex = primary_hcd->bandwidth_mutex;
		hcd->primary_hcd = primary_hcd;
		primary_hcd->primary_hcd = primary_hcd;
		hcd->shared_hcd = primary_hcd;
		primary_hcd->shared_hcd = hcd;
		mutex_unlock(&usb_port_peer_mutex);
	पूर्ण

	kref_init(&hcd->kref);

	usb_bus_init(&hcd->self);
	hcd->self.controller = dev;
	hcd->self.sysdev = sysdev;
	hcd->self.bus_name = bus_name;

	समयr_setup(&hcd->rh_समयr, rh_समयr_func, 0);
#अगर_घोषित CONFIG_PM
	INIT_WORK(&hcd->wakeup_work, hcd_resume_work);
#पूर्ण_अगर

	INIT_WORK(&hcd->died_work, hcd_died_work);

	hcd->driver = driver;
	hcd->speed = driver->flags & HCD_MASK;
	hcd->product_desc = (driver->product_desc) ? driver->product_desc :
			"USB Host Controller";
	वापस hcd;
पूर्ण
EXPORT_SYMBOL_GPL(__usb_create_hcd);

/**
 * usb_create_shared_hcd - create and initialize an HCD काष्ठाure
 * @driver: HC driver that will use this hcd
 * @dev: device क्रम this HC, stored in hcd->self.controller
 * @bus_name: value to store in hcd->self.bus_name
 * @primary_hcd: a poपूर्णांकer to the usb_hcd काष्ठाure that is sharing the
 *              PCI device.  Only allocate certain resources क्रम the primary HCD
 *
 * Context: task context, might sleep.
 *
 * Allocate a काष्ठा usb_hcd, with extra space at the end क्रम the
 * HC driver's निजी data.  Initialize the generic members of the
 * hcd काष्ठाure.
 *
 * Return: On success, a poपूर्णांकer to the created and initialized HCD काष्ठाure.
 * On failure (e.g. अगर memory is unavailable), %शून्य.
 */
काष्ठा usb_hcd *usb_create_shared_hcd(स्थिर काष्ठा hc_driver *driver,
		काष्ठा device *dev, स्थिर अक्षर *bus_name,
		काष्ठा usb_hcd *primary_hcd)
अणु
	वापस __usb_create_hcd(driver, dev, dev, bus_name, primary_hcd);
पूर्ण
EXPORT_SYMBOL_GPL(usb_create_shared_hcd);

/**
 * usb_create_hcd - create and initialize an HCD काष्ठाure
 * @driver: HC driver that will use this hcd
 * @dev: device क्रम this HC, stored in hcd->self.controller
 * @bus_name: value to store in hcd->self.bus_name
 *
 * Context: task context, might sleep.
 *
 * Allocate a काष्ठा usb_hcd, with extra space at the end क्रम the
 * HC driver's निजी data.  Initialize the generic members of the
 * hcd काष्ठाure.
 *
 * Return: On success, a poपूर्णांकer to the created and initialized HCD
 * काष्ठाure. On failure (e.g. अगर memory is unavailable), %शून्य.
 */
काष्ठा usb_hcd *usb_create_hcd(स्थिर काष्ठा hc_driver *driver,
		काष्ठा device *dev, स्थिर अक्षर *bus_name)
अणु
	वापस __usb_create_hcd(driver, dev, dev, bus_name, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(usb_create_hcd);

/*
 * Roothubs that share one PCI device must also share the bandwidth mutex.
 * Don't deallocate the bandwidth_mutex until the last shared usb_hcd is
 * deallocated.
 *
 * Make sure to deallocate the bandwidth_mutex only when the last HCD is
 * मुक्तd.  When hcd_release() is called क्रम either hcd in a peer set,
 * invalidate the peer's ->shared_hcd and ->primary_hcd poपूर्णांकers.
 */
अटल व्योम hcd_release(काष्ठा kref *kref)
अणु
	काष्ठा usb_hcd *hcd = container_of (kref, काष्ठा usb_hcd, kref);

	mutex_lock(&usb_port_peer_mutex);
	अगर (hcd->shared_hcd) अणु
		काष्ठा usb_hcd *peer = hcd->shared_hcd;

		peer->shared_hcd = शून्य;
		peer->primary_hcd = शून्य;
	पूर्ण अन्यथा अणु
		kमुक्त(hcd->address0_mutex);
		kमुक्त(hcd->bandwidth_mutex);
	पूर्ण
	mutex_unlock(&usb_port_peer_mutex);
	kमुक्त(hcd);
पूर्ण

काष्ठा usb_hcd *usb_get_hcd (काष्ठा usb_hcd *hcd)
अणु
	अगर (hcd)
		kref_get (&hcd->kref);
	वापस hcd;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_hcd);

व्योम usb_put_hcd (काष्ठा usb_hcd *hcd)
अणु
	अगर (hcd)
		kref_put (&hcd->kref, hcd_release);
पूर्ण
EXPORT_SYMBOL_GPL(usb_put_hcd);

पूर्णांक usb_hcd_is_primary_hcd(काष्ठा usb_hcd *hcd)
अणु
	अगर (!hcd->primary_hcd)
		वापस 1;
	वापस hcd == hcd->primary_hcd;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_is_primary_hcd);

पूर्णांक usb_hcd_find_raw_port_number(काष्ठा usb_hcd *hcd, पूर्णांक port1)
अणु
	अगर (!hcd->driver->find_raw_port_number)
		वापस port1;

	वापस hcd->driver->find_raw_port_number(hcd, port1);
पूर्ण

अटल पूर्णांक usb_hcd_request_irqs(काष्ठा usb_hcd *hcd,
		अचिन्हित पूर्णांक irqnum, अचिन्हित दीर्घ irqflags)
अणु
	पूर्णांक retval;

	अगर (hcd->driver->irq) अणु

		snम_लिखो(hcd->irq_descr, माप(hcd->irq_descr), "%s:usb%d",
				hcd->driver->description, hcd->self.busnum);
		retval = request_irq(irqnum, &usb_hcd_irq, irqflags,
				hcd->irq_descr, hcd);
		अगर (retval != 0) अणु
			dev_err(hcd->self.controller,
					"request interrupt %d failed\n",
					irqnum);
			वापस retval;
		पूर्ण
		hcd->irq = irqnum;
		dev_info(hcd->self.controller, "irq %d, %s 0x%08llx\n", irqnum,
				(hcd->driver->flags & HCD_MEMORY) ?
					"io mem" : "io base",
					(अचिन्हित दीर्घ दीर्घ)hcd->rsrc_start);
	पूर्ण अन्यथा अणु
		hcd->irq = 0;
		अगर (hcd->rsrc_start)
			dev_info(hcd->self.controller, "%s 0x%08llx\n",
					(hcd->driver->flags & HCD_MEMORY) ?
					"io mem" : "io base",
					(अचिन्हित दीर्घ दीर्घ)hcd->rsrc_start);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Beक्रमe we मुक्त this root hub, flush in-flight peering attempts
 * and disable peer lookups
 */
अटल व्योम usb_put_invalidate_rhdev(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा usb_device *rhdev;

	mutex_lock(&usb_port_peer_mutex);
	rhdev = hcd->self.root_hub;
	hcd->self.root_hub = शून्य;
	mutex_unlock(&usb_port_peer_mutex);
	usb_put_dev(rhdev);
पूर्ण

/**
 * usb_add_hcd - finish generic HCD काष्ठाure initialization and रेजिस्टर
 * @hcd: the usb_hcd काष्ठाure to initialize
 * @irqnum: Interrupt line to allocate
 * @irqflags: Interrupt type flags
 *
 * Finish the reमुख्यing parts of generic HCD initialization: allocate the
 * buffers of consistent memory, रेजिस्टर the bus, request the IRQ line,
 * and call the driver's reset() and start() routines.
 */
पूर्णांक usb_add_hcd(काष्ठा usb_hcd *hcd,
		अचिन्हित पूर्णांक irqnum, अचिन्हित दीर्घ irqflags)
अणु
	पूर्णांक retval;
	काष्ठा usb_device *rhdev;

	अगर (!hcd->skip_phy_initialization && usb_hcd_is_primary_hcd(hcd)) अणु
		hcd->phy_roothub = usb_phy_roothub_alloc(hcd->self.sysdev);
		अगर (IS_ERR(hcd->phy_roothub))
			वापस PTR_ERR(hcd->phy_roothub);

		retval = usb_phy_roothub_init(hcd->phy_roothub);
		अगर (retval)
			वापस retval;

		retval = usb_phy_roothub_set_mode(hcd->phy_roothub,
						  PHY_MODE_USB_HOST_SS);
		अगर (retval)
			retval = usb_phy_roothub_set_mode(hcd->phy_roothub,
							  PHY_MODE_USB_HOST);
		अगर (retval)
			जाओ err_usb_phy_roothub_घातer_on;

		retval = usb_phy_roothub_घातer_on(hcd->phy_roothub);
		अगर (retval)
			जाओ err_usb_phy_roothub_घातer_on;
	पूर्ण

	dev_info(hcd->self.controller, "%s\n", hcd->product_desc);

	चयन (authorized_शेष) अणु
	हाल USB_AUTHORIZE_NONE:
		hcd->dev_policy = USB_DEVICE_AUTHORIZE_NONE;
		अवरोध;

	हाल USB_AUTHORIZE_ALL:
		hcd->dev_policy = USB_DEVICE_AUTHORIZE_ALL;
		अवरोध;

	हाल USB_AUTHORIZE_INTERNAL:
		hcd->dev_policy = USB_DEVICE_AUTHORIZE_INTERNAL;
		अवरोध;

	हाल USB_AUTHORIZE_WIRED:
	शेष:
		hcd->dev_policy = hcd->wireless ?
			USB_DEVICE_AUTHORIZE_NONE : USB_DEVICE_AUTHORIZE_ALL;
		अवरोध;
	पूर्ण

	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	/* per शेष all पूर्णांकerfaces are authorized */
	set_bit(HCD_FLAG_INTF_AUTHORIZED, &hcd->flags);

	/* HC is in reset state, but accessible.  Now करो the one-समय init,
	 * bottom up so that hcds can customize the root hubs beक्रमe hub_wq
	 * starts talking to them.  (Note, bus id is asचिन्हित early too.)
	 */
	retval = hcd_buffer_create(hcd);
	अगर (retval != 0) अणु
		dev_dbg(hcd->self.sysdev, "pool alloc failed\n");
		जाओ err_create_buf;
	पूर्ण

	retval = usb_रेजिस्टर_bus(&hcd->self);
	अगर (retval < 0)
		जाओ err_रेजिस्टर_bus;

	rhdev = usb_alloc_dev(शून्य, &hcd->self, 0);
	अगर (rhdev == शून्य) अणु
		dev_err(hcd->self.sysdev, "unable to allocate root hub\n");
		retval = -ENOMEM;
		जाओ err_allocate_root_hub;
	पूर्ण
	mutex_lock(&usb_port_peer_mutex);
	hcd->self.root_hub = rhdev;
	mutex_unlock(&usb_port_peer_mutex);

	rhdev->rx_lanes = 1;
	rhdev->tx_lanes = 1;
	rhdev->ssp_rate = USB_SSP_GEN_UNKNOWN;

	चयन (hcd->speed) अणु
	हाल HCD_USB11:
		rhdev->speed = USB_SPEED_FULL;
		अवरोध;
	हाल HCD_USB2:
		rhdev->speed = USB_SPEED_HIGH;
		अवरोध;
	हाल HCD_USB25:
		rhdev->speed = USB_SPEED_WIRELESS;
		अवरोध;
	हाल HCD_USB3:
		rhdev->speed = USB_SPEED_SUPER;
		अवरोध;
	हाल HCD_USB32:
		rhdev->rx_lanes = 2;
		rhdev->tx_lanes = 2;
		rhdev->ssp_rate = USB_SSP_GEN_2x2;
		rhdev->speed = USB_SPEED_SUPER_PLUS;
		अवरोध;
	हाल HCD_USB31:
		rhdev->ssp_rate = USB_SSP_GEN_2x1;
		rhdev->speed = USB_SPEED_SUPER_PLUS;
		अवरोध;
	शेष:
		retval = -EINVAL;
		जाओ err_set_rh_speed;
	पूर्ण

	/* wakeup flag init शेषs to "everything works" क्रम root hubs,
	 * but drivers can override it in reset() अगर needed, aदीर्घ with
	 * recording the overall controller's प्रणाली wakeup capability.
	 */
	device_set_wakeup_capable(&rhdev->dev, 1);

	/* HCD_FLAG_RH_RUNNING करोesn't matter until the root hub is
	 * रेजिस्टरed.  But since the controller can die at any समय,
	 * let's initialize the flag beक्रमe touching the hardware.
	 */
	set_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);

	/* "reset" is misnamed; its role is now one-समय init. the controller
	 * should alपढ़ोy have been reset (and boot firmware kicked off etc).
	 */
	अगर (hcd->driver->reset) अणु
		retval = hcd->driver->reset(hcd);
		अगर (retval < 0) अणु
			dev_err(hcd->self.controller, "can't setup: %d\n",
					retval);
			जाओ err_hcd_driver_setup;
		पूर्ण
	पूर्ण
	hcd->rh_pollable = 1;

	retval = usb_phy_roothub_calibrate(hcd->phy_roothub);
	अगर (retval)
		जाओ err_hcd_driver_setup;

	/* NOTE: root hub and controller capabilities may not be the same */
	अगर (device_can_wakeup(hcd->self.controller)
			&& device_can_wakeup(&hcd->self.root_hub->dev))
		dev_dbg(hcd->self.controller, "supports USB remote wakeup\n");

	/* initialize tasklets */
	init_giveback_urb_bh(&hcd->high_prio_bh);
	init_giveback_urb_bh(&hcd->low_prio_bh);

	/* enable irqs just beक्रमe we start the controller,
	 * अगर the BIOS provides legacy PCI irqs.
	 */
	अगर (usb_hcd_is_primary_hcd(hcd) && irqnum) अणु
		retval = usb_hcd_request_irqs(hcd, irqnum, irqflags);
		अगर (retval)
			जाओ err_request_irq;
	पूर्ण

	hcd->state = HC_STATE_RUNNING;
	retval = hcd->driver->start(hcd);
	अगर (retval < 0) अणु
		dev_err(hcd->self.controller, "startup error %d\n", retval);
		जाओ err_hcd_driver_start;
	पूर्ण

	/* starting here, usbcore will pay attention to this root hub */
	retval = रेजिस्टर_root_hub(hcd);
	अगर (retval != 0)
		जाओ err_रेजिस्टर_root_hub;

	अगर (hcd->uses_new_polling && HCD_POLL_RH(hcd))
		usb_hcd_poll_rh_status(hcd);

	वापस retval;

err_रेजिस्टर_root_hub:
	hcd->rh_pollable = 0;
	clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	del_समयr_sync(&hcd->rh_समयr);
	hcd->driver->stop(hcd);
	hcd->state = HC_STATE_HALT;
	clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	del_समयr_sync(&hcd->rh_समयr);
err_hcd_driver_start:
	अगर (usb_hcd_is_primary_hcd(hcd) && hcd->irq > 0)
		मुक्त_irq(irqnum, hcd);
err_request_irq:
err_hcd_driver_setup:
err_set_rh_speed:
	usb_put_invalidate_rhdev(hcd);
err_allocate_root_hub:
	usb_deरेजिस्टर_bus(&hcd->self);
err_रेजिस्टर_bus:
	hcd_buffer_destroy(hcd);
err_create_buf:
	usb_phy_roothub_घातer_off(hcd->phy_roothub);
err_usb_phy_roothub_घातer_on:
	usb_phy_roothub_निकास(hcd->phy_roothub);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(usb_add_hcd);

/**
 * usb_हटाओ_hcd - shutकरोwn processing क्रम generic HCDs
 * @hcd: the usb_hcd काष्ठाure to हटाओ
 *
 * Context: task context, might sleep.
 *
 * Disconnects the root hub, then reverses the effects of usb_add_hcd(),
 * invoking the HCD's stop() method.
 */
व्योम usb_हटाओ_hcd(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा usb_device *rhdev = hcd->self.root_hub;

	dev_info(hcd->self.controller, "remove, state %x\n", hcd->state);

	usb_get_dev(rhdev);
	clear_bit(HCD_FLAG_RH_RUNNING, &hcd->flags);
	अगर (HC_IS_RUNNING (hcd->state))
		hcd->state = HC_STATE_QUIESCING;

	dev_dbg(hcd->self.controller, "roothub graceful disconnect\n");
	spin_lock_irq (&hcd_root_hub_lock);
	hcd->rh_रेजिस्टरed = 0;
	spin_unlock_irq (&hcd_root_hub_lock);

#अगर_घोषित CONFIG_PM
	cancel_work_sync(&hcd->wakeup_work);
#पूर्ण_अगर
	cancel_work_sync(&hcd->died_work);

	mutex_lock(&usb_bus_idr_lock);
	usb_disconnect(&rhdev);		/* Sets rhdev to शून्य */
	mutex_unlock(&usb_bus_idr_lock);

	/*
	 * tasklet_समाप्त() isn't needed here because:
	 * - driver's disconnect() called from usb_disconnect() should
	 *   make sure its URBs are completed during the disconnect()
	 *   callback
	 *
	 * - it is too late to run complete() here since driver may have
	 *   been हटाओd alपढ़ोy now
	 */

	/* Prevent any more root-hub status calls from the समयr.
	 * The HCD might still restart the समयr (अगर a port status change
	 * पूर्णांकerrupt occurs), but usb_hcd_poll_rh_status() won't invoke
	 * the hub_status_data() callback.
	 */
	hcd->rh_pollable = 0;
	clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	del_समयr_sync(&hcd->rh_समयr);

	hcd->driver->stop(hcd);
	hcd->state = HC_STATE_HALT;

	/* In हाल the HCD restarted the समयr, stop it again. */
	clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	del_समयr_sync(&hcd->rh_समयr);

	अगर (usb_hcd_is_primary_hcd(hcd)) अणु
		अगर (hcd->irq > 0)
			मुक्त_irq(hcd->irq, hcd);
	पूर्ण

	usb_deरेजिस्टर_bus(&hcd->self);
	hcd_buffer_destroy(hcd);

	usb_phy_roothub_घातer_off(hcd->phy_roothub);
	usb_phy_roothub_निकास(hcd->phy_roothub);

	usb_put_invalidate_rhdev(hcd);
	hcd->flags = 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_हटाओ_hcd);

व्योम
usb_hcd_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);

	/* No need क्रम pm_runसमय_put(), we're shutting करोwn */
	pm_runसमय_get_sync(&dev->dev);

	अगर (hcd->driver->shutकरोwn)
		hcd->driver->shutकरोwn(hcd);
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_platक्रमm_shutकरोwn);

पूर्णांक usb_hcd_setup_local_mem(काष्ठा usb_hcd *hcd, phys_addr_t phys_addr,
			    dma_addr_t dma, माप_प्रकार size)
अणु
	पूर्णांक err;
	व्योम *local_mem;

	hcd->localmem_pool = devm_gen_pool_create(hcd->self.sysdev, 4,
						  dev_to_node(hcd->self.sysdev),
						  dev_name(hcd->self.sysdev));
	अगर (IS_ERR(hcd->localmem_pool))
		वापस PTR_ERR(hcd->localmem_pool);

	local_mem = devm_memremap(hcd->self.sysdev, phys_addr,
				  size, MEMREMAP_WC);
	अगर (IS_ERR(local_mem))
		वापस PTR_ERR(local_mem);

	/*
	 * Here we pass a dma_addr_t but the arg type is a phys_addr_t.
	 * It's not backed by system memory and thus there's no kernel mapping
	 * क्रम it.
	 */
	err = gen_pool_add_virt(hcd->localmem_pool, (अचिन्हित दीर्घ)local_mem,
				dma, size, dev_to_node(hcd->self.sysdev));
	अगर (err < 0) अणु
		dev_err(hcd->self.sysdev, "gen_pool_add_virt failed with %d\n",
			err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_setup_local_mem);

/*-------------------------------------------------------------------------*/

#अगर IS_ENABLED(CONFIG_USB_MON)

स्थिर काष्ठा usb_mon_operations *mon_ops;

/*
 * The registration is unlocked.
 * We करो it this way because we करो not want to lock in hot paths.
 *
 * Notice that the code is minimally error-proof. Because usbmon needs
 * symbols from usbcore, usbcore माला_लो referenced and cannot be unloaded first.
 */

पूर्णांक usb_mon_रेजिस्टर(स्थिर काष्ठा usb_mon_operations *ops)
अणु

	अगर (mon_ops)
		वापस -EBUSY;

	mon_ops = ops;
	mb();
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL (usb_mon_रेजिस्टर);

व्योम usb_mon_deरेजिस्टर (व्योम)
अणु

	अगर (mon_ops == शून्य) अणु
		prपूर्णांकk(KERN_ERR "USB: monitor was not registered\n");
		वापस;
	पूर्ण
	mon_ops = शून्य;
	mb();
पूर्ण
EXPORT_SYMBOL_GPL (usb_mon_deरेजिस्टर);

#पूर्ण_अगर /* CONFIG_USB_MON || CONFIG_USB_MON_MODULE */
