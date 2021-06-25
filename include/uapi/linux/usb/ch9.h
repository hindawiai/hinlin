<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file holds USB स्थिरants and काष्ठाures that are needed क्रम
 * USB device APIs.  These are used by the USB device model, which is
 * defined in chapter 9 of the USB 2.0 specअगरication and in the
 * Wireless USB 1.0 (spपढ़ो around).  Linux has several APIs in C that
 * need these:
 *
 * - the master/host side Linux-USB kernel driver API;
 * - the "usbfs" user space API; and
 * - the Linux "gadget" slave/device/peripheral side driver API.
 *
 * USB 2.0 adds an additional "On The Go" (OTG) mode, which lets प्रणालीs
 * act either as a USB master/host or as a USB slave/device.  That means
 * the master and slave side APIs benefit from working well together.
 *
 * There's also "Wireless USB", using low घातer लघु range radios क्रम
 * peripheral पूर्णांकerconnection but otherwise building on the USB framework.
 *
 * Note all descriptors are declared '__attribute__((packed))' so that:
 *
 * [a] they never get padded, either पूर्णांकernally (USB spec ग_लिखोrs
 *     probably handled that) or बाह्यally;
 *
 * [b] so that accessing bigger-than-a-bytes fields will never
 *     generate bus errors on any platक्रमm, even when the location of
 *     its descriptor inside a bundle isn't "naturally aligned", and
 *
 * [c] क्रम consistency, removing all करोubt even when it appears to
 *     someone that the two other poपूर्णांकs are non-issues क्रम that
 *     particular descriptor type.
 */

#अगर_अघोषित _UAPI__LINUX_USB_CH9_H
#घोषणा _UAPI__LINUX_USB_CH9_H

#समावेश <linux/types.h>	/* __u8 etc */
#समावेश <यंत्र/byteorder.h>	/* le16_to_cpu */

/*-------------------------------------------------------------------------*/

/* CONTROL REQUEST SUPPORT */

/*
 * USB directions
 *
 * This bit flag is used in endpoपूर्णांक descriptors' bEndpoपूर्णांकAddress field.
 * It's also one of three fields in control requests bRequestType.
 */
#घोषणा USB_सूची_OUT			0		/* to device */
#घोषणा USB_सूची_IN			0x80		/* to host */

/*
 * USB types, the second of three bRequestType fields
 */
#घोषणा USB_TYPE_MASK			(0x03 << 5)
#घोषणा USB_TYPE_STANDARD		(0x00 << 5)
#घोषणा USB_TYPE_CLASS			(0x01 << 5)
#घोषणा USB_TYPE_VENDOR			(0x02 << 5)
#घोषणा USB_TYPE_RESERVED		(0x03 << 5)

/*
 * USB recipients, the third of three bRequestType fields
 */
#घोषणा USB_RECIP_MASK			0x1f
#घोषणा USB_RECIP_DEVICE		0x00
#घोषणा USB_RECIP_INTERFACE		0x01
#घोषणा USB_RECIP_ENDPOINT		0x02
#घोषणा USB_RECIP_OTHER			0x03
/* From Wireless USB 1.0 */
#घोषणा USB_RECIP_PORT			0x04
#घोषणा USB_RECIP_RPIPE		0x05

/*
 * Standard requests, क्रम the bRequest field of a SETUP packet.
 *
 * These are qualअगरied by the bRequestType field, so that क्रम example
 * TYPE_CLASS or TYPE_VENDOR specअगरic feature flags could be retrieved
 * by a GET_STATUS request.
 */
#घोषणा USB_REQ_GET_STATUS		0x00
#घोषणा USB_REQ_CLEAR_FEATURE		0x01
#घोषणा USB_REQ_SET_FEATURE		0x03
#घोषणा USB_REQ_SET_ADDRESS		0x05
#घोषणा USB_REQ_GET_DESCRIPTOR		0x06
#घोषणा USB_REQ_SET_DESCRIPTOR		0x07
#घोषणा USB_REQ_GET_CONFIGURATION	0x08
#घोषणा USB_REQ_SET_CONFIGURATION	0x09
#घोषणा USB_REQ_GET_INTERFACE		0x0A
#घोषणा USB_REQ_SET_INTERFACE		0x0B
#घोषणा USB_REQ_SYNCH_FRAME		0x0C
#घोषणा USB_REQ_SET_SEL			0x30
#घोषणा USB_REQ_SET_ISOCH_DELAY		0x31

#घोषणा USB_REQ_SET_ENCRYPTION		0x0D	/* Wireless USB */
#घोषणा USB_REQ_GET_ENCRYPTION		0x0E
#घोषणा USB_REQ_RPIPE_ABORT		0x0E
#घोषणा USB_REQ_SET_HANDSHAKE		0x0F
#घोषणा USB_REQ_RPIPE_RESET		0x0F
#घोषणा USB_REQ_GET_HANDSHAKE		0x10
#घोषणा USB_REQ_SET_CONNECTION		0x11
#घोषणा USB_REQ_SET_SECURITY_DATA	0x12
#घोषणा USB_REQ_GET_SECURITY_DATA	0x13
#घोषणा USB_REQ_SET_WUSB_DATA		0x14
#घोषणा USB_REQ_LOOPBACK_DATA_WRITE	0x15
#घोषणा USB_REQ_LOOPBACK_DATA_READ	0x16
#घोषणा USB_REQ_SET_INTERFACE_DS	0x17

/* specअगरic requests क्रम USB Power Delivery */
#घोषणा USB_REQ_GET_PARTNER_PDO		20
#घोषणा USB_REQ_GET_BATTERY_STATUS	21
#घोषणा USB_REQ_SET_PDO			22
#घोषणा USB_REQ_GET_VDM			23
#घोषणा USB_REQ_SEND_VDM		24

/* The Link Power Management (LPM) ECN defines USB_REQ_TEST_AND_SET command,
 * used by hubs to put ports पूर्णांकo a new L1 suspend state, except that it
 * क्रमgot to define its number ...
 */

/*
 * USB feature flags are written using USB_REQ_अणुCLEAR,SETपूर्ण_FEATURE, and
 * are पढ़ो as a bit array वापसed by USB_REQ_GET_STATUS.  (So there
 * are at most sixteen features of each type.)  Hubs may also support a
 * new USB_REQ_TEST_AND_SET_FEATURE to put ports पूर्णांकo L1 suspend.
 */
#घोषणा USB_DEVICE_SELF_POWERED		0	/* (पढ़ो only) */
#घोषणा USB_DEVICE_REMOTE_WAKEUP	1	/* dev may initiate wakeup */
#घोषणा USB_DEVICE_TEST_MODE		2	/* (wired high speed only) */
#घोषणा USB_DEVICE_BATTERY		2	/* (wireless) */
#घोषणा USB_DEVICE_B_HNP_ENABLE		3	/* (otg) dev may initiate HNP */
#घोषणा USB_DEVICE_WUSB_DEVICE		3	/* (wireless)*/
#घोषणा USB_DEVICE_A_HNP_SUPPORT	4	/* (otg) RH port supports HNP */
#घोषणा USB_DEVICE_A_ALT_HNP_SUPPORT	5	/* (otg) other RH port करोes */
#घोषणा USB_DEVICE_DEBUG_MODE		6	/* (special devices only) */

/*
 * Test Mode Selectors
 * See USB 2.0 spec Table 9-7
 */
#घोषणा	USB_TEST_J		1
#घोषणा	USB_TEST_K		2
#घोषणा	USB_TEST_SE0_NAK	3
#घोषणा	USB_TEST_PACKET		4
#घोषणा	USB_TEST_FORCE_ENABLE	5

/* Status Type */
#घोषणा USB_STATUS_TYPE_STANDARD	0
#घोषणा USB_STATUS_TYPE_PTM		1

/*
 * New Feature Selectors as added by USB 3.0
 * See USB 3.0 spec Table 9-7
 */
#घोषणा USB_DEVICE_U1_ENABLE	48	/* dev may initiate U1 transition */
#घोषणा USB_DEVICE_U2_ENABLE	49	/* dev may initiate U2 transition */
#घोषणा USB_DEVICE_LTM_ENABLE	50	/* dev may send LTM */
#घोषणा USB_INTRF_FUNC_SUSPEND	0	/* function suspend */

#घोषणा USB_INTR_FUNC_SUSPEND_OPT_MASK	0xFF00
/*
 * Suspend Options, Table 9-8 USB 3.0 spec
 */
#घोषणा USB_INTRF_FUNC_SUSPEND_LP	(1 << (8 + 0))
#घोषणा USB_INTRF_FUNC_SUSPEND_RW	(1 << (8 + 1))

/*
 * Interface status, Figure 9-5 USB 3.0 spec
 */
#घोषणा USB_INTRF_STAT_FUNC_RW_CAP     1
#घोषणा USB_INTRF_STAT_FUNC_RW         2

#घोषणा USB_ENDPOINT_HALT		0	/* IN/OUT will STALL */

/* Bit array elements as वापसed by the USB_REQ_GET_STATUS request. */
#घोषणा USB_DEV_STAT_U1_ENABLED		2	/* transition पूर्णांकo U1 state */
#घोषणा USB_DEV_STAT_U2_ENABLED		3	/* transition पूर्णांकo U2 state */
#घोषणा USB_DEV_STAT_LTM_ENABLED	4	/* Latency tolerance messages */

/*
 * Feature selectors from Table 9-8 USB Power Delivery spec
 */
#घोषणा USB_DEVICE_BATTERY_WAKE_MASK	40
#घोषणा USB_DEVICE_OS_IS_PD_AWARE	41
#घोषणा USB_DEVICE_POLICY_MODE		42
#घोषणा USB_PORT_PR_SWAP		43
#घोषणा USB_PORT_GOTO_MIN		44
#घोषणा USB_PORT_RETURN_POWER		45
#घोषणा USB_PORT_ACCEPT_PD_REQUEST	46
#घोषणा USB_PORT_REJECT_PD_REQUEST	47
#घोषणा USB_PORT_PORT_PD_RESET		48
#घोषणा USB_PORT_C_PORT_PD_CHANGE	49
#घोषणा USB_PORT_CABLE_PD_RESET		50
#घोषणा USB_DEVICE_CHARGING_POLICY	54

/**
 * काष्ठा usb_ctrlrequest - SETUP data क्रम a USB device control request
 * @bRequestType: matches the USB bmRequestType field
 * @bRequest: matches the USB bRequest field
 * @wValue: matches the USB wValue field (le16 byte order)
 * @wIndex: matches the USB wIndex field (le16 byte order)
 * @wLength: matches the USB wLength field (le16 byte order)
 *
 * This काष्ठाure is used to send control requests to a USB device.  It matches
 * the dअगरferent fields of the USB 2.0 Spec section 9.3, table 9-2.  See the
 * USB spec क्रम a fuller description of the dअगरferent fields, and what they are
 * used क्रम.
 *
 * Note that the driver क्रम any पूर्णांकerface can issue control requests.
 * For most devices, पूर्णांकerfaces करोn't coordinate with each other, so
 * such requests may be made at any समय.
 */
काष्ठा usb_ctrlrequest अणु
	__u8 bRequestType;
	__u8 bRequest;
	__le16 wValue;
	__le16 wIndex;
	__le16 wLength;
पूर्ण __attribute__ ((packed));

/*-------------------------------------------------------------------------*/

/*
 * STANDARD DESCRIPTORS ... as वापसed by GET_DESCRIPTOR, or
 * (rarely) accepted by SET_DESCRIPTOR.
 *
 * Note that all multi-byte values here are encoded in little endian
 * byte order "on the wire".  Within the kernel and when exposed
 * through the Linux-USB APIs, they are not converted to cpu byte
 * order; it is the responsibility of the client code to करो this.
 * The single exception is when device and configuration descriptors (but
 * not other descriptors) are पढ़ो from अक्षरacter devices
 * (i.e. /dev/bus/usb/BBB/DDD);
 * in this हाल the fields are converted to host endianness by the kernel.
 */

/*
 * Descriptor types ... USB 2.0 spec table 9.5
 */
#घोषणा USB_DT_DEVICE			0x01
#घोषणा USB_DT_CONFIG			0x02
#घोषणा USB_DT_STRING			0x03
#घोषणा USB_DT_INTERFACE		0x04
#घोषणा USB_DT_ENDPOINT			0x05
#घोषणा USB_DT_DEVICE_QUALIFIER		0x06
#घोषणा USB_DT_OTHER_SPEED_CONFIG	0x07
#घोषणा USB_DT_INTERFACE_POWER		0x08
/* these are from a minor usb 2.0 revision (ECN) */
#घोषणा USB_DT_OTG			0x09
#घोषणा USB_DT_DEBUG			0x0a
#घोषणा USB_DT_INTERFACE_ASSOCIATION	0x0b
/* these are from the Wireless USB spec */
#घोषणा USB_DT_SECURITY			0x0c
#घोषणा USB_DT_KEY			0x0d
#घोषणा USB_DT_ENCRYPTION_TYPE		0x0e
#घोषणा USB_DT_BOS			0x0f
#घोषणा USB_DT_DEVICE_CAPABILITY	0x10
#घोषणा USB_DT_WIRELESS_ENDPOINT_COMP	0x11
#घोषणा USB_DT_WIRE_ADAPTER		0x21
#घोषणा USB_DT_RPIPE			0x22
#घोषणा USB_DT_CS_RADIO_CONTROL		0x23
/* From the T10 UAS specअगरication */
#घोषणा USB_DT_PIPE_USAGE		0x24
/* From the USB 3.0 spec */
#घोषणा	USB_DT_SS_ENDPOINT_COMP		0x30
/* From the USB 3.1 spec */
#घोषणा	USB_DT_SSP_ISOC_ENDPOINT_COMP	0x31

/* Conventional codes क्रम class-specअगरic descriptors.  The convention is
 * defined in the USB "Common Class" Spec (3.11).  Inभागidual class specs
 * are authoritative क्रम their usage, not the "common class" ग_लिखोup.
 */
#घोषणा USB_DT_CS_DEVICE		(USB_TYPE_CLASS | USB_DT_DEVICE)
#घोषणा USB_DT_CS_CONFIG		(USB_TYPE_CLASS | USB_DT_CONFIG)
#घोषणा USB_DT_CS_STRING		(USB_TYPE_CLASS | USB_DT_STRING)
#घोषणा USB_DT_CS_INTERFACE		(USB_TYPE_CLASS | USB_DT_INTERFACE)
#घोषणा USB_DT_CS_ENDPOINT		(USB_TYPE_CLASS | USB_DT_ENDPOINT)

/* All standard descriptors have these 2 fields at the beginning */
काष्ठा usb_descriptor_header अणु
	__u8  bLength;
	__u8  bDescriptorType;
पूर्ण __attribute__ ((packed));


/*-------------------------------------------------------------------------*/

/* USB_DT_DEVICE: Device descriptor */
काष्ठा usb_device_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__le16 bcdUSB;
	__u8  bDeviceClass;
	__u8  bDeviceSubClass;
	__u8  bDeviceProtocol;
	__u8  bMaxPacketSize0;
	__le16 idVenकरोr;
	__le16 idProduct;
	__le16 bcdDevice;
	__u8  iManufacturer;
	__u8  iProduct;
	__u8  iSerialNumber;
	__u8  bNumConfigurations;
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_DEVICE_SIZE		18


/*
 * Device and/or Interface Class codes
 * as found in bDeviceClass or bInterfaceClass
 * and defined by www.usb.org करोcuments
 */
#घोषणा USB_CLASS_PER_INTERFACE		0	/* क्रम DeviceClass */
#घोषणा USB_CLASS_AUDIO			1
#घोषणा USB_CLASS_COMM			2
#घोषणा USB_CLASS_HID			3
#घोषणा USB_CLASS_PHYSICAL		5
#घोषणा USB_CLASS_STILL_IMAGE		6
#घोषणा USB_CLASS_PRINTER		7
#घोषणा USB_CLASS_MASS_STORAGE		8
#घोषणा USB_CLASS_HUB			9
#घोषणा USB_CLASS_CDC_DATA		0x0a
#घोषणा USB_CLASS_CSCID			0x0b	/* chip+ smart card */
#घोषणा USB_CLASS_CONTENT_SEC		0x0d	/* content security */
#घोषणा USB_CLASS_VIDEO			0x0e
#घोषणा USB_CLASS_WIRELESS_CONTROLLER	0xe0
#घोषणा USB_CLASS_PERSONAL_HEALTHCARE	0x0f
#घोषणा USB_CLASS_AUDIO_VIDEO		0x10
#घोषणा USB_CLASS_BILLBOARD		0x11
#घोषणा USB_CLASS_USB_TYPE_C_BRIDGE	0x12
#घोषणा USB_CLASS_MISC			0xef
#घोषणा USB_CLASS_APP_SPEC		0xfe
#घोषणा USB_CLASS_VENDOR_SPEC		0xff

#घोषणा USB_SUBCLASS_VENDOR_SPEC	0xff

/*-------------------------------------------------------------------------*/

/* USB_DT_CONFIG: Configuration descriptor inक्रमmation.
 *
 * USB_DT_OTHER_SPEED_CONFIG is the same descriptor, except that the
 * descriptor type is dअगरferent.  Highspeed-capable devices can look
 * dअगरferent depending on what speed they're currently running.  Only
 * devices with a USB_DT_DEVICE_QUALIFIER have any OTHER_SPEED_CONFIG
 * descriptors.
 */
काष्ठा usb_config_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__le16 wTotalLength;
	__u8  bNumInterfaces;
	__u8  bConfigurationValue;
	__u8  iConfiguration;
	__u8  bmAttributes;
	__u8  bMaxPower;
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_CONFIG_SIZE		9

/* from config descriptor bmAttributes */
#घोषणा USB_CONFIG_ATT_ONE		(1 << 7)	/* must be set */
#घोषणा USB_CONFIG_ATT_SELFPOWER	(1 << 6)	/* self घातered */
#घोषणा USB_CONFIG_ATT_WAKEUP		(1 << 5)	/* can wakeup */
#घोषणा USB_CONFIG_ATT_BATTERY		(1 << 4)	/* battery घातered */

/*-------------------------------------------------------------------------*/

/* USB String descriptors can contain at most 126 अक्षरacters. */
#घोषणा USB_MAX_STRING_LEN	126

/* USB_DT_STRING: String descriptor */
काष्ठा usb_string_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__le16 wData[1];		/* UTF-16LE encoded */
पूर्ण __attribute__ ((packed));

/* note that "string" zero is special, it holds language codes that
 * the device supports, not Unicode अक्षरacters.
 */

/*-------------------------------------------------------------------------*/

/* USB_DT_INTERFACE: Interface descriptor */
काष्ठा usb_पूर्णांकerface_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bInterfaceNumber;
	__u8  bAlternateSetting;
	__u8  bNumEndpoपूर्णांकs;
	__u8  bInterfaceClass;
	__u8  bInterfaceSubClass;
	__u8  bInterfaceProtocol;
	__u8  iInterface;
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_INTERFACE_SIZE		9

/*-------------------------------------------------------------------------*/

/* USB_DT_ENDPOINT: Endpoपूर्णांक descriptor */
काष्ठा usb_endpoपूर्णांक_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bEndpoपूर्णांकAddress;
	__u8  bmAttributes;
	__le16 wMaxPacketSize;
	__u8  bInterval;

	/* NOTE:  these two are _only_ in audio endpoपूर्णांकs. */
	/* use USB_DT_ENDPOINT*_SIZE in bLength, not माप. */
	__u8  bRefresh;
	__u8  bSynchAddress;
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_ENDPOINT_SIZE		7
#घोषणा USB_DT_ENDPOINT_AUDIO_SIZE	9	/* Audio extension */


/*
 * Endpoपूर्णांकs
 */
#घोषणा USB_ENDPOINT_NUMBER_MASK	0x0f	/* in bEndpoपूर्णांकAddress */
#घोषणा USB_ENDPOINT_सूची_MASK		0x80

#घोषणा USB_ENDPOINT_XFERTYPE_MASK	0x03	/* in bmAttributes */
#घोषणा USB_ENDPOINT_XFER_CONTROL	0
#घोषणा USB_ENDPOINT_XFER_ISOC		1
#घोषणा USB_ENDPOINT_XFER_BULK		2
#घोषणा USB_ENDPOINT_XFER_INT		3
#घोषणा USB_ENDPOपूर्णांक_उच्च_ADJUSTABLE	0x80

#घोषणा USB_ENDPOपूर्णांक_उच्चP_MASK	0x07ff
#घोषणा USB_EP_MAXP_MULT_SHIFT	11
#घोषणा USB_EP_MAXP_MULT_MASK	(3 << USB_EP_MAXP_MULT_SHIFT)
#घोषणा USB_EP_MAXP_MULT(m) \
	(((m) & USB_EP_MAXP_MULT_MASK) >> USB_EP_MAXP_MULT_SHIFT)

/* The USB 3.0 spec redefines bits 5:4 of bmAttributes as पूर्णांकerrupt ep type. */
#घोषणा USB_ENDPOINT_INTRTYPE		0x30
#घोषणा USB_ENDPOINT_INTR_PERIODIC	(0 << 4)
#घोषणा USB_ENDPOINT_INTR_NOTIFICATION	(1 << 4)

#घोषणा USB_ENDPOINT_SYNCTYPE		0x0c
#घोषणा USB_ENDPOINT_SYNC_NONE		(0 << 2)
#घोषणा USB_ENDPOINT_SYNC_ASYNC		(1 << 2)
#घोषणा USB_ENDPOINT_SYNC_ADAPTIVE	(2 << 2)
#घोषणा USB_ENDPOINT_SYNC_SYNC		(3 << 2)

#घोषणा USB_ENDPOINT_USAGE_MASK		0x30
#घोषणा USB_ENDPOINT_USAGE_DATA		0x00
#घोषणा USB_ENDPOINT_USAGE_FEEDBACK	0x10
#घोषणा USB_ENDPOINT_USAGE_IMPLICIT_FB	0x20	/* Implicit feedback Data endpoपूर्णांक */

/*-------------------------------------------------------------------------*/

/**
 * usb_endpoपूर्णांक_num - get the endpoपूर्णांक's number
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns @epd's number: 0 to 15.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_num(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस epd->bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK;
पूर्ण

/**
 * usb_endpoपूर्णांक_type - get the endpoपूर्णांक's transfer type
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns one of USB_ENDPOINT_XFER_अणुCONTROL, ISOC, BULK, INTपूर्ण according
 * to @epd's transfer type.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_type(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
पूर्ण

/**
 * usb_endpoपूर्णांक_dir_in - check अगर the endpoपूर्णांक has IN direction
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक is of type IN, otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_dir_in(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस ((epd->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK) == USB_सूची_IN);
पूर्ण

/**
 * usb_endpoपूर्णांक_dir_out - check अगर the endpoपूर्णांक has OUT direction
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक is of type OUT, otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_dir_out(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस ((epd->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK) == USB_सूची_OUT);
पूर्ण

/**
 * usb_endpoपूर्णांक_xfer_bulk - check अगर the endpoपूर्णांक has bulk transfer type
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक is of type bulk, otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_xfer_bulk(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		USB_ENDPOINT_XFER_BULK);
पूर्ण

/**
 * usb_endpoपूर्णांक_xfer_control - check अगर the endpoपूर्णांक has control transfer type
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक is of type control, otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_xfer_control(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		USB_ENDPOINT_XFER_CONTROL);
पूर्ण

/**
 * usb_endpoपूर्णांक_xfer_पूर्णांक - check अगर the endpoपूर्णांक has पूर्णांकerrupt transfer type
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक is of type पूर्णांकerrupt, otherwise it वापसs
 * false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_xfer_पूर्णांक(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		USB_ENDPOINT_XFER_INT);
पूर्ण

/**
 * usb_endpoपूर्णांक_xfer_isoc - check अगर the endpoपूर्णांक has isochronous transfer type
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक is of type isochronous, otherwise it वापसs
 * false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_xfer_isoc(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		USB_ENDPOINT_XFER_ISOC);
पूर्ण

/**
 * usb_endpoपूर्णांक_is_bulk_in - check अगर the endpoपूर्णांक is bulk IN
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक has bulk transfer type and IN direction,
 * otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_is_bulk_in(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस usb_endpoपूर्णांक_xfer_bulk(epd) && usb_endpoपूर्णांक_dir_in(epd);
पूर्ण

/**
 * usb_endpoपूर्णांक_is_bulk_out - check अगर the endpoपूर्णांक is bulk OUT
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक has bulk transfer type and OUT direction,
 * otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_is_bulk_out(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस usb_endpoपूर्णांक_xfer_bulk(epd) && usb_endpoपूर्णांक_dir_out(epd);
पूर्ण

/**
 * usb_endpoपूर्णांक_is_पूर्णांक_in - check अगर the endpoपूर्णांक is पूर्णांकerrupt IN
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक has पूर्णांकerrupt transfer type and IN direction,
 * otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_is_पूर्णांक_in(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस usb_endpoपूर्णांक_xfer_पूर्णांक(epd) && usb_endpoपूर्णांक_dir_in(epd);
पूर्ण

/**
 * usb_endpoपूर्णांक_is_पूर्णांक_out - check अगर the endpoपूर्णांक is पूर्णांकerrupt OUT
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक has पूर्णांकerrupt transfer type and OUT direction,
 * otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_is_पूर्णांक_out(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस usb_endpoपूर्णांक_xfer_पूर्णांक(epd) && usb_endpoपूर्णांक_dir_out(epd);
पूर्ण

/**
 * usb_endpoपूर्णांक_is_isoc_in - check अगर the endpoपूर्णांक is isochronous IN
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक has isochronous transfer type and IN direction,
 * otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_is_isoc_in(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस usb_endpoपूर्णांक_xfer_isoc(epd) && usb_endpoपूर्णांक_dir_in(epd);
पूर्ण

/**
 * usb_endpoपूर्णांक_is_isoc_out - check अगर the endpoपूर्णांक is isochronous OUT
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns true अगर the endpoपूर्णांक has isochronous transfer type and OUT direction,
 * otherwise it वापसs false.
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_is_isoc_out(
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस usb_endpoपूर्णांक_xfer_isoc(epd) && usb_endpoपूर्णांक_dir_out(epd);
पूर्ण

/**
 * usb_endpoपूर्णांक_maxp - get endpoपूर्णांक's max packet size
 * @epd: endpoपूर्णांक to be checked
 *
 * Returns @epd's max packet bits [10:0]
 */
अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_maxp(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस __le16_to_cpu(epd->wMaxPacketSize) & USB_ENDPOपूर्णांक_उच्चP_MASK;
पूर्ण

/**
 * usb_endpoपूर्णांक_maxp_mult - get endpoपूर्णांक's transactional opportunities
 * @epd: endpoपूर्णांक to be checked
 *
 * Return @epd's wMaxPacketSize[12:11] + 1
 */
अटल अंतरभूत पूर्णांक
usb_endpoपूर्णांक_maxp_mult(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	पूर्णांक maxp = __le16_to_cpu(epd->wMaxPacketSize);

	वापस USB_EP_MAXP_MULT(maxp) + 1;
पूर्ण

अटल अंतरभूत पूर्णांक usb_endpoपूर्णांक_पूर्णांकerrupt_type(
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	वापस epd->bmAttributes & USB_ENDPOINT_INTRTYPE;
पूर्ण

/*-------------------------------------------------------------------------*/

/* USB_DT_SSP_ISOC_ENDPOINT_COMP: SuperSpeedPlus Isochronous Endpoपूर्णांक Companion
 * descriptor
 */
काष्ठा usb_ssp_isoc_ep_comp_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__le16 wReseved;
	__le32 dwBytesPerInterval;
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_SSP_ISOC_EP_COMP_SIZE		8

/*-------------------------------------------------------------------------*/

/* USB_DT_SS_ENDPOINT_COMP: SuperSpeed Endpoपूर्णांक Companion descriptor */
काष्ठा usb_ss_ep_comp_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bMaxBurst;
	__u8  bmAttributes;
	__le16 wBytesPerInterval;
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_SS_EP_COMP_SIZE		6

/* Bits 4:0 of bmAttributes अगर this is a bulk endpoपूर्णांक */
अटल अंतरभूत पूर्णांक
usb_ss_max_streams(स्थिर काष्ठा usb_ss_ep_comp_descriptor *comp)
अणु
	पूर्णांक		max_streams;

	अगर (!comp)
		वापस 0;

	max_streams = comp->bmAttributes & 0x1f;

	अगर (!max_streams)
		वापस 0;

	max_streams = 1 << max_streams;

	वापस max_streams;
पूर्ण

/* Bits 1:0 of bmAttributes अगर this is an isoc endpoपूर्णांक */
#घोषणा USB_SS_MULT(p)			(1 + ((p) & 0x3))
/* Bit 7 of bmAttributes अगर a SSP isoc endpoपूर्णांक companion descriptor exists */
#घोषणा USB_SS_SSP_ISOC_COMP(p)		((p) & (1 << 7))

/*-------------------------------------------------------------------------*/

/* USB_DT_DEVICE_QUALIFIER: Device Qualअगरier descriptor */
काष्ठा usb_qualअगरier_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__le16 bcdUSB;
	__u8  bDeviceClass;
	__u8  bDeviceSubClass;
	__u8  bDeviceProtocol;
	__u8  bMaxPacketSize0;
	__u8  bNumConfigurations;
	__u8  bRESERVED;
पूर्ण __attribute__ ((packed));


/*-------------------------------------------------------------------------*/

/* USB_DT_OTG (from OTG 1.0a supplement) */
काष्ठा usb_otg_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bmAttributes;	/* support क्रम HNP, SRP, etc */
पूर्ण __attribute__ ((packed));

/* USB_DT_OTG (from OTG 2.0 supplement) */
काष्ठा usb_otg20_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bmAttributes;	/* support क्रम HNP, SRP and ADP, etc */
	__le16 bcdOTG;		/* OTG and EH supplement release number
				 * in binary-coded decimal(i.e. 2.0 is 0200H)
				 */
पूर्ण __attribute__ ((packed));

/* from usb_otg_descriptor.bmAttributes */
#घोषणा USB_OTG_SRP		(1 << 0)
#घोषणा USB_OTG_HNP		(1 << 1)	/* swap host/device roles */
#घोषणा USB_OTG_ADP		(1 << 2)	/* support ADP */

#घोषणा OTG_STS_SELECTOR	0xF000		/* OTG status selector */
/*-------------------------------------------------------------------------*/

/* USB_DT_DEBUG:  क्रम special highspeed devices, replacing serial console */
काष्ठा usb_debug_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	/* bulk endpoपूर्णांकs with 8 byte maxpacket */
	__u8  bDebugInEndpoपूर्णांक;
	__u8  bDebugOutEndpoपूर्णांक;
पूर्ण __attribute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_DT_INTERFACE_ASSOCIATION: groups पूर्णांकerfaces */
काष्ठा usb_पूर्णांकerface_assoc_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bFirstInterface;
	__u8  bInterfaceCount;
	__u8  bFunctionClass;
	__u8  bFunctionSubClass;
	__u8  bFunctionProtocol;
	__u8  iFunction;
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_INTERFACE_ASSOCIATION_SIZE	8

/*-------------------------------------------------------------------------*/

/* USB_DT_SECURITY:  group of wireless security descriptors, including
 * encryption types available क्रम setting up a CC/association.
 */
काष्ठा usb_security_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__le16 wTotalLength;
	__u8  bNumEncryptionTypes;
पूर्ण __attribute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_DT_KEY:  used with अणुGET,SETपूर्ण_SECURITY_DATA; only खुला keys
 * may be retrieved.
 */
काष्ठा usb_key_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  tTKID[3];
	__u8  bReserved;
	__u8  bKeyData[0];
पूर्ण __attribute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_DT_ENCRYPTION_TYPE:  bundled in DT_SECURITY groups */
काष्ठा usb_encryption_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bEncryptionType;
#घोषणा	USB_ENC_TYPE_UNSECURE		0
#घोषणा	USB_ENC_TYPE_WIRED		1	/* non-wireless mode */
#घोषणा	USB_ENC_TYPE_CCM_1		2	/* aes128/cbc session */
#घोषणा	USB_ENC_TYPE_RSA_1		3	/* rsa3072/sha1 auth */
	__u8  bEncryptionValue;		/* use in SET_ENCRYPTION */
	__u8  bAuthKeyIndex;
पूर्ण __attribute__((packed));


/*-------------------------------------------------------------------------*/

/* USB_DT_BOS:  group of device-level capabilities */
काष्ठा usb_bos_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__le16 wTotalLength;
	__u8  bNumDeviceCaps;
पूर्ण __attribute__((packed));

#घोषणा USB_DT_BOS_SIZE		5
/*-------------------------------------------------------------------------*/

/* USB_DT_DEVICE_CAPABILITY:  grouped with BOS */
काष्ठा usb_dev_cap_header अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDevCapabilityType;
पूर्ण __attribute__((packed));

#घोषणा	USB_CAP_TYPE_WIRELESS_USB	1

काष्ठा usb_wireless_cap_descriptor अणु	/* Ultra Wide Band */
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDevCapabilityType;

	__u8  bmAttributes;
#घोषणा	USB_WIRELESS_P2P_DRD		(1 << 1)
#घोषणा	USB_WIRELESS_BEACON_MASK	(3 << 2)
#घोषणा	USB_WIRELESS_BEACON_SELF	(1 << 2)
#घोषणा	USB_WIRELESS_BEACON_सूचीECTED	(2 << 2)
#घोषणा	USB_WIRELESS_BEACON_NONE	(3 << 2)
	__le16 wPHYRates;	/* bit rates, Mbps */
#घोषणा	USB_WIRELESS_PHY_53		(1 << 0)	/* always set */
#घोषणा	USB_WIRELESS_PHY_80		(1 << 1)
#घोषणा	USB_WIRELESS_PHY_107		(1 << 2)	/* always set */
#घोषणा	USB_WIRELESS_PHY_160		(1 << 3)
#घोषणा	USB_WIRELESS_PHY_200		(1 << 4)	/* always set */
#घोषणा	USB_WIRELESS_PHY_320		(1 << 5)
#घोषणा	USB_WIRELESS_PHY_400		(1 << 6)
#घोषणा	USB_WIRELESS_PHY_480		(1 << 7)
	__u8  bmTFITXPowerInfo;	/* TFI घातer levels */
	__u8  bmFFITXPowerInfo;	/* FFI घातer levels */
	__le16 bmBandGroup;
	__u8  bReserved;
पूर्ण __attribute__((packed));

#घोषणा USB_DT_USB_WIRELESS_CAP_SIZE	11

/* USB 2.0 Extension descriptor */
#घोषणा	USB_CAP_TYPE_EXT		2

काष्ठा usb_ext_cap_descriptor अणु		/* Link Power Management */
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDevCapabilityType;
	__le32 bmAttributes;
#घोषणा USB_LPM_SUPPORT			(1 << 1)	/* supports LPM */
#घोषणा USB_BESL_SUPPORT		(1 << 2)	/* supports BESL */
#घोषणा USB_BESL_BASELINE_VALID		(1 << 3)	/* Baseline BESL valid*/
#घोषणा USB_BESL_DEEP_VALID		(1 << 4)	/* Deep BESL valid */
#घोषणा USB_SET_BESL_BASELINE(p)	(((p) & 0xf) << 8)
#घोषणा USB_SET_BESL_DEEP(p)		(((p) & 0xf) << 12)
#घोषणा USB_GET_BESL_BASELINE(p)	(((p) & (0xf << 8)) >> 8)
#घोषणा USB_GET_BESL_DEEP(p)		(((p) & (0xf << 12)) >> 12)
पूर्ण __attribute__((packed));

#घोषणा USB_DT_USB_EXT_CAP_SIZE	7

/*
 * SuperSpeed USB Capability descriptor: Defines the set of SuperSpeed USB
 * specअगरic device level capabilities
 */
#घोषणा		USB_SS_CAP_TYPE		3
काष्ठा usb_ss_cap_descriptor अणु		/* Link Power Management */
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDevCapabilityType;
	__u8  bmAttributes;
#घोषणा USB_LTM_SUPPORT			(1 << 1) /* supports LTM */
	__le16 wSpeedSupported;
#घोषणा USB_LOW_SPEED_OPERATION		(1)	 /* Low speed operation */
#घोषणा USB_FULL_SPEED_OPERATION	(1 << 1) /* Full speed operation */
#घोषणा USB_HIGH_SPEED_OPERATION	(1 << 2) /* High speed operation */
#घोषणा USB_5GBPS_OPERATION		(1 << 3) /* Operation at 5Gbps */
	__u8  bFunctionalitySupport;
	__u8  bU1devExitLat;
	__le16 bU2DevExitLat;
पूर्ण __attribute__((packed));

#घोषणा USB_DT_USB_SS_CAP_SIZE	10

/*
 * Container ID Capability descriptor: Defines the instance unique ID used to
 * identअगरy the instance across all operating modes
 */
#घोषणा	CONTAINER_ID_TYPE	4
काष्ठा usb_ss_container_id_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDevCapabilityType;
	__u8  bReserved;
	__u8  ContainerID[16]; /* 128-bit number */
पूर्ण __attribute__((packed));

#घोषणा USB_DT_USB_SS_CONTN_ID_SIZE	20

/*
 * SuperSpeed Plus USB Capability descriptor: Defines the set of
 * SuperSpeed Plus USB specअगरic device level capabilities
 */
#घोषणा	USB_SSP_CAP_TYPE	0xa
काष्ठा usb_ssp_cap_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDevCapabilityType;
	__u8  bReserved;
	__le32 bmAttributes;
#घोषणा USB_SSP_SUBLINK_SPEED_ATTRIBS	(0x1f << 0) /* sublink speed entries */
#घोषणा USB_SSP_SUBLINK_SPEED_IDS	(0xf << 5)  /* speed ID entries */
	__le16  wFunctionalitySupport;
#घोषणा USB_SSP_MIN_SUBLINK_SPEED_ATTRIBUTE_ID	(0xf)
#घोषणा USB_SSP_MIN_RX_LANE_COUNT		(0xf << 8)
#घोषणा USB_SSP_MIN_TX_LANE_COUNT		(0xf << 12)
	__le16 wReserved;
	__le32 bmSublinkSpeedAttr[1]; /* list of sublink speed attrib entries */
#घोषणा USB_SSP_SUBLINK_SPEED_SSID	(0xf)		/* sublink speed ID */
#घोषणा USB_SSP_SUBLINK_SPEED_LSE	(0x3 << 4)	/* Lanespeed exponent */
#घोषणा USB_SSP_SUBLINK_SPEED_LSE_BPS		0
#घोषणा USB_SSP_SUBLINK_SPEED_LSE_KBPS		1
#घोषणा USB_SSP_SUBLINK_SPEED_LSE_MBPS		2
#घोषणा USB_SSP_SUBLINK_SPEED_LSE_GBPS		3

#घोषणा USB_SSP_SUBLINK_SPEED_ST	(0x3 << 6)	/* Sublink type */
#घोषणा USB_SSP_SUBLINK_SPEED_ST_SYM_RX		0
#घोषणा USB_SSP_SUBLINK_SPEED_ST_ASYM_RX	1
#घोषणा USB_SSP_SUBLINK_SPEED_ST_SYM_TX		2
#घोषणा USB_SSP_SUBLINK_SPEED_ST_ASYM_TX	3

#घोषणा USB_SSP_SUBLINK_SPEED_RSVD	(0x3f << 8)	/* Reserved */
#घोषणा USB_SSP_SUBLINK_SPEED_LP	(0x3 << 14)	/* Link protocol */
#घोषणा USB_SSP_SUBLINK_SPEED_LP_SS		0
#घोषणा USB_SSP_SUBLINK_SPEED_LP_SSP		1

#घोषणा USB_SSP_SUBLINK_SPEED_LSM	(0xff << 16)	/* Lanespeed mantissa */
पूर्ण __attribute__((packed));

/*
 * USB Power Delivery Capability Descriptor:
 * Defines capabilities क्रम PD
 */
/* Defines the various PD Capabilities of this device */
#घोषणा USB_PD_POWER_DELIVERY_CAPABILITY	0x06
/* Provides inक्रमmation on each battery supported by the device */
#घोषणा USB_PD_BATTERY_INFO_CAPABILITY		0x07
/* The Consumer अक्षरacteristics of a Port on the device */
#घोषणा USB_PD_PD_CONSUMER_PORT_CAPABILITY	0x08
/* The provider अक्षरacteristics of a Port on the device */
#घोषणा USB_PD_PD_PROVIDER_PORT_CAPABILITY	0x09

काष्ठा usb_pd_cap_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDevCapabilityType; /* set to USB_PD_POWER_DELIVERY_CAPABILITY */
	__u8  bReserved;
	__le32 bmAttributes;
#घोषणा USB_PD_CAP_BATTERY_CHARGING	(1 << 1) /* supports Battery Charging specअगरication */
#घोषणा USB_PD_CAP_USB_PD		(1 << 2) /* supports USB Power Delivery specअगरication */
#घोषणा USB_PD_CAP_PROVIDER		(1 << 3) /* can provide घातer */
#घोषणा USB_PD_CAP_CONSUMER		(1 << 4) /* can consume घातer */
#घोषणा USB_PD_CAP_CHARGING_POLICY	(1 << 5) /* supports CHARGING_POLICY feature */
#घोषणा USB_PD_CAP_TYPE_C_CURRENT	(1 << 6) /* supports घातer capabilities defined in the USB Type-C Specअगरication */

#घोषणा USB_PD_CAP_PWR_AC		(1 << 8)
#घोषणा USB_PD_CAP_PWR_BAT		(1 << 9)
#घोषणा USB_PD_CAP_PWR_USE_V_BUS	(1 << 14)

	__le16 bmProviderPorts; /* Bit zero refers to the UFP of the device */
	__le16 bmConsumerPorts;
	__le16 bcdBCVersion;
	__le16 bcdPDVersion;
	__le16 bcdUSBTypeCVersion;
पूर्ण __attribute__((packed));

काष्ठा usb_pd_cap_battery_info_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDevCapabilityType;
	/* Index of string descriptor shall contain the user मित्रly name क्रम this battery */
	__u8 iBattery;
	/* Index of string descriptor shall contain the Serial Number String क्रम this battery */
	__u8 iSerial;
	__u8 iManufacturer;
	__u8 bBatteryId; /* uniquely identअगरies this battery in status Messages */
	__u8 bReserved;
	/*
	 * Shall contain the Battery Charge value above which this
	 * battery is considered to be fully अक्षरged but not necessarily
	 * ै topped off.ै 
	 */
	__le32 dwChargedThreshold; /* in mWh */
	/*
	 * Shall contain the minimum अक्षरge level of this battery such
	 * that above this threshold, a device can be assured of being
	 * able to घातer up successfully (see Battery Charging 1.2).
	 */
	__le32 dwWeakThreshold; /* in mWh */
	__le32 dwBatteryDesignCapacity; /* in mWh */
	__le32 dwBatteryLastFullअक्षरgeCapacity; /* in mWh */
पूर्ण __attribute__((packed));

काष्ठा usb_pd_cap_consumer_port_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDevCapabilityType;
	__u8 bReserved;
	__u8 bmCapabilities;
/* port will oerate under: */
#घोषणा USB_PD_CAP_CONSUMER_BC		(1 << 0) /* BC */
#घोषणा USB_PD_CAP_CONSUMER_PD		(1 << 1) /* PD */
#घोषणा USB_PD_CAP_CONSUMER_TYPE_C	(1 << 2) /* USB Type-C Current */
	__le16 wMinVoltage; /* in 50mV units */
	__le16 wMaxVoltage; /* in 50mV units */
	__u16 wReserved;
	__le32 dwMaxOperatingPower; /* in 10 mW - operating at steady state */
	__le32 dwMaxPeakPower; /* in 10mW units - operating at peak घातer */
	__le32 dwMaxPeakPowerTime; /* in 100ms units - duration of peak */
#घोषणा USB_PD_CAP_CONSUMER_UNKNOWN_PEAK_POWER_TIME 0xffff
पूर्ण __attribute__((packed));

काष्ठा usb_pd_cap_provider_port_descriptor अणु
	__u8 bLength;
	__u8 bDescriptorType;
	__u8 bDevCapabilityType;
	__u8 bReserved1;
	__u8 bmCapabilities;
/* port will oerate under: */
#घोषणा USB_PD_CAP_PROVIDER_BC		(1 << 0) /* BC */
#घोषणा USB_PD_CAP_PROVIDER_PD		(1 << 1) /* PD */
#घोषणा USB_PD_CAP_PROVIDER_TYPE_C	(1 << 2) /* USB Type-C Current */
	__u8 bNumOfPDObjects;
	__u8 bReserved2;
	__le32 wPowerDataObject[];
पूर्ण __attribute__((packed));

/*
 * Precision समय measurement capability descriptor: advertised by devices and
 * hubs that support PTM
 */
#घोषणा	USB_PTM_CAP_TYPE	0xb
काष्ठा usb_pपंचांग_cap_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDevCapabilityType;
पूर्ण __attribute__((packed));

#घोषणा USB_DT_USB_PTM_ID_SIZE		3
/*
 * The size of the descriptor क्रम the Sublink Speed Attribute Count
 * (SSAC) specअगरied in bmAttributes[4:0]. SSAC is zero-based
 */
#घोषणा USB_DT_USB_SSP_CAP_SIZE(ssac)	(12 + (ssac + 1) * 4)

/*-------------------------------------------------------------------------*/

/* USB_DT_WIRELESS_ENDPOINT_COMP:  companion descriptor associated with
 * each endpoपूर्णांक descriptor क्रम a wireless device
 */
काष्ठा usb_wireless_ep_comp_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bMaxBurst;
	__u8  bMaxSequence;
	__le16 wMaxStreamDelay;
	__le16 wOverTheAirPacketSize;
	__u8  bOverTheAirInterval;
	__u8  bmCompAttributes;
#घोषणा USB_ENDPOINT_SWITCH_MASK	0x03	/* in bmCompAttributes */
#घोषणा USB_ENDPOINT_SWITCH_NO		0
#घोषणा USB_ENDPOINT_SWITCH_SWITCH	1
#घोषणा USB_ENDPOINT_SWITCH_SCALE	2
पूर्ण __attribute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_REQ_SET_HANDSHAKE is a four-way handshake used between a wireless
 * host and a device क्रम connection set up, mutual authentication, and
 * exchanging लघु lived session keys.  The handshake depends on a CC.
 */
काष्ठा usb_handshake अणु
	__u8 bMessageNumber;
	__u8 bStatus;
	__u8 tTKID[3];
	__u8 bReserved;
	__u8 CDID[16];
	__u8 nonce[16];
	__u8 MIC[8];
पूर्ण __attribute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_REQ_SET_CONNECTION modअगरies or revokes a connection context (CC).
 * A CC may also be set up using non-wireless secure channels (including
 * wired USB!), and some devices may support CCs with multiple hosts.
 */
काष्ठा usb_connection_context अणु
	__u8 CHID[16];		/* persistent host id */
	__u8 CDID[16];		/* device id (unique w/in host context) */
	__u8 CK[16];		/* connection key */
पूर्ण __attribute__((packed));

/*-------------------------------------------------------------------------*/

/* USB 2.0 defines three speeds, here's how Linux identअगरies them */

क्रमागत usb_device_speed अणु
	USB_SPEED_UNKNOWN = 0,			/* क्रमागतerating */
	USB_SPEED_LOW, USB_SPEED_FULL,		/* usb 1.1 */
	USB_SPEED_HIGH,				/* usb 2.0 */
	USB_SPEED_WIRELESS,			/* wireless (usb 2.5) */
	USB_SPEED_SUPER,			/* usb 3.0 */
	USB_SPEED_SUPER_PLUS,			/* usb 3.1 */
पूर्ण;


क्रमागत usb_device_state अणु
	/* NOTATTACHED isn't in the USB spec, and this state acts
	 * the same as ATTACHED ... but it's clearer this way.
	 */
	USB_STATE_NOTATTACHED = 0,

	/* chapter 9 and authentication (wireless) device states */
	USB_STATE_ATTACHED,
	USB_STATE_POWERED,			/* wired */
	USB_STATE_RECONNECTING,			/* auth */
	USB_STATE_UNAUTHENTICATED,		/* auth */
	USB_STATE_DEFAULT,			/* limited function */
	USB_STATE_ADDRESS,
	USB_STATE_CONFIGURED,			/* most functions */

	USB_STATE_SUSPENDED

	/* NOTE:  there are actually four dअगरferent SUSPENDED
	 * states, वापसing to POWERED, DEFAULT, ADDRESS, or
	 * CONFIGURED respectively when SOF tokens flow again.
	 * At this level there's no dअगरference between L1 and L2
	 * suspend states.  (L2 being original USB 1.1 suspend.)
	 */
पूर्ण;

क्रमागत usb3_link_state अणु
	USB3_LPM_U0 = 0,
	USB3_LPM_U1,
	USB3_LPM_U2,
	USB3_LPM_U3
पूर्ण;

/*
 * A U1 समयout of 0x0 means the parent hub will reject any transitions to U1.
 * 0xff means the parent hub will accept transitions to U1, but will not
 * initiate a transition.
 *
 * A U1 समयout of 0x1 to 0x7F also causes the hub to initiate a transition to
 * U1 after that many microseconds.  Timeouts of 0x80 to 0xFE are reserved
 * values.
 *
 * A U2 समयout of 0x0 means the parent hub will reject any transitions to U2.
 * 0xff means the parent hub will accept transitions to U2, but will not
 * initiate a transition.
 *
 * A U2 समयout of 0x1 to 0xFE also causes the hub to initiate a transition to
 * U2 after N*256 microseconds.  Thereक्रमe a U2 समयout value of 0x1 means a U2
 * idle समयr of 256 microseconds, 0x2 means 512 microseconds, 0xFE means
 * 65.024ms.
 */
#घोषणा USB3_LPM_DISABLED		0x0
#घोषणा USB3_LPM_U1_MAX_TIMEOUT		0x7F
#घोषणा USB3_LPM_U2_MAX_TIMEOUT		0xFE
#घोषणा USB3_LPM_DEVICE_INITIATED	0xFF

काष्ठा usb_set_sel_req अणु
	__u8	u1_sel;
	__u8	u1_pel;
	__le16	u2_sel;
	__le16	u2_pel;
पूर्ण __attribute__ ((packed));

/*
 * The Set System Exit Latency control transfer provides one byte each क्रम
 * U1 SEL and U1 PEL, so the max निकास latency is 0xFF.  U2 SEL and U2 PEL each
 * are two bytes दीर्घ.
 */
#घोषणा USB3_LPM_MAX_U1_SEL_PEL		0xFF
#घोषणा USB3_LPM_MAX_U2_SEL_PEL		0xFFFF

/*-------------------------------------------------------------------------*/

/*
 * As per USB compliance update, a device that is actively drawing
 * more than 100mA from USB must report itself as bus-घातered in
 * the GetStatus(DEVICE) call.
 * https://compliance.usb.org/index.asp?UpdateFile=Electrical&Format=Standard#34
 */
#घोषणा USB_SELF_POWER_VBUS_MAX_DRAW		100

#पूर्ण_अगर /* _UAPI__LINUX_USB_CH9_H */
