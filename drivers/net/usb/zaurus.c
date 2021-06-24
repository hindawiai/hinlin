<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2002 Pavel Machek <pavel@ucw.cz>
 * Copyright (C) 2002-2005 by David Brownell
 */

// #घोषणा	DEBUG			// error path messages, extra info
// #घोषणा	VERBOSE			// more; success messages

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>


/*
 * All known Zaurii lie about their standards conक्रमmance.  At least
 * the earliest SA-1100 models lie by saying they support CDC Ethernet.
 * Some later models (especially PXA-25x and PXA-27x based ones) lie
 * and say they support CDC MDLM (क्रम access to cell phone modems).
 *
 * There are non-Zaurus products that use these same protocols too.
 *
 * The annoying thing is that at the same समय Sharp was developing
 * that annoying standards-अवरोधing software, the Linux community had
 * a simple "CDC Subset" working reliably on the same SA-1100 hardware.
 * That is, the same functionality but not violating standards.
 *
 * The CDC Ethernet nonconक्रमmance poपूर्णांकs are troublesome to hosts
 * with a true CDC Ethernet implementation:
 *   - Framing appends a CRC, which the spec says drivers "must not" करो;
 *   - Transfers data in altsetting zero, instead of altsetting 1;
 *   - All these peripherals use the same ethernet address.
 *
 * The CDC MDLM nonconक्रमmance is less immediately troublesome, since all
 * MDLM implementations are quasi-proprietary anyway.
 */

अटल काष्ठा sk_buff *
zaurus_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags)
अणु
	पूर्णांक			padlen;
	काष्ठा sk_buff		*skb2;

	padlen = 2;
	अगर (!skb_cloned(skb)) अणु
		पूर्णांक	tailroom = skb_tailroom(skb);
		अगर ((padlen + 4) <= tailroom)
			जाओ करोne;
	पूर्ण
	skb2 = skb_copy_expand(skb, 0, 4 + padlen, flags);
	dev_kमुक्त_skb_any(skb);
	skb = skb2;
	अगर (skb) अणु
		u32		fcs;
करोne:
		fcs = crc32_le(~0, skb->data, skb->len);
		fcs = ~fcs;

		skb_put_u8(skb, fcs & 0xff);
		skb_put_u8(skb, (fcs >> 8) & 0xff);
		skb_put_u8(skb, (fcs >> 16) & 0xff);
		skb_put_u8(skb, (fcs >> 24) & 0xff);
	पूर्ण
	वापस skb;
पूर्ण

अटल पूर्णांक zaurus_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	/* Belcarra's funky framing has other options; mostly
	 * TRAILERS (!) with 4 bytes CRC, and maybe 2 pad bytes.
	 */
	dev->net->hard_header_len += 6;
	dev->rx_urb_size = dev->net->hard_header_len + dev->net->mtu;
	वापस usbnet_generic_cdc_bind(dev, पूर्णांकf);
पूर्ण

/* PDA style devices are always connected अगर present */
अटल पूर्णांक always_connected (काष्ठा usbnet *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा driver_info	zaurus_sl5x00_info = अणु
	.description =	"Sharp Zaurus SL-5x00",
	.flags =	FLAG_POINTTOPOINT | FLAG_FRAMING_Z,
	.check_connect = always_connected,
	.bind =		zaurus_bind,
	.unbind =	usbnet_cdc_unbind,
	.tx_fixup =	zaurus_tx_fixup,
पूर्ण;
#घोषणा	ZAURUS_STRONGARM_INFO	((अचिन्हित दीर्घ)&zaurus_sl5x00_info)

अटल स्थिर काष्ठा driver_info	zaurus_pxa_info = अणु
	.description =	"Sharp Zaurus, PXA-2xx based",
	.flags =	FLAG_POINTTOPOINT | FLAG_FRAMING_Z,
	.check_connect = always_connected,
	.bind =		zaurus_bind,
	.unbind =	usbnet_cdc_unbind,
	.tx_fixup =	zaurus_tx_fixup,
पूर्ण;
#घोषणा	ZAURUS_PXA_INFO		((अचिन्हित दीर्घ)&zaurus_pxa_info)

अटल स्थिर काष्ठा driver_info	olympus_mxl_info = अणु
	.description =	"Olympus R1000",
	.flags =	FLAG_POINTTOPOINT | FLAG_FRAMING_Z,
	.check_connect = always_connected,
	.bind =		zaurus_bind,
	.unbind =	usbnet_cdc_unbind,
	.tx_fixup =	zaurus_tx_fixup,
पूर्ण;
#घोषणा	OLYMPUS_MXL_INFO	((अचिन्हित दीर्घ)&olympus_mxl_info)


/* Some more recent products using Lineo/Belcarra code will wrongly claim
 * CDC MDLM conक्रमmance.  They aren't conक्रमmant:  data endpoपूर्णांकs live
 * in the control पूर्णांकerface, there's no data interface, and it's not used
 * to talk to a cell phone radio.  But at least we can detect these two
 * pseuकरो-classes, rather than growing this product list with entries क्रम
 * each new nonconक्रमmant product (sigh).
 */
अटल स्थिर u8 safe_guid[16] = अणु
	0x5d, 0x34, 0xcf, 0x66, 0x11, 0x18, 0x11, 0xd6,
	0xa2, 0x1a, 0x00, 0x01, 0x02, 0xca, 0x9a, 0x7f,
पूर्ण;
अटल स्थिर u8 blan_guid[16] = अणु
	0x74, 0xf0, 0x3d, 0xbd, 0x1e, 0xc1, 0x44, 0x70,
	0xa3, 0x67, 0x71, 0x34, 0xc9, 0xf5, 0x54, 0x37,
पूर्ण;

अटल पूर्णांक blan_mdlm_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	u8				*buf = पूर्णांकf->cur_altsetting->extra;
	पूर्णांक				len = पूर्णांकf->cur_altsetting->extralen;
	काष्ठा usb_cdc_mdlm_desc	*desc = शून्य;
	काष्ठा usb_cdc_mdlm_detail_desc	*detail = शून्य;

	जबतक (len > 3) अणु
		अगर (buf [1] != USB_DT_CS_INTERFACE)
			जाओ next_desc;

		/* use bDescriptorSubType, and just verअगरy that we get a
		 * "BLAN" (or "SAFE") descriptor.
		 */
		चयन (buf [2]) अणु
		हाल USB_CDC_MDLM_TYPE:
			अगर (desc) अणु
				dev_dbg(&पूर्णांकf->dev, "extra MDLM\n");
				जाओ bad_desc;
			पूर्ण
			desc = (व्योम *) buf;
			अगर (desc->bLength != माप *desc) अणु
				dev_dbg(&पूर्णांकf->dev, "MDLM len %u\n",
					desc->bLength);
				जाओ bad_desc;
			पूर्ण
			/* expect bcdVersion 1.0, ignore */
			अगर (स_भेद(&desc->bGUID, blan_guid, 16) &&
			    स_भेद(&desc->bGUID, safe_guid, 16)) अणु
				/* hey, this one might _really_ be MDLM! */
				dev_dbg(&पूर्णांकf->dev, "MDLM guid\n");
				जाओ bad_desc;
			पूर्ण
			अवरोध;
		हाल USB_CDC_MDLM_DETAIL_TYPE:
			अगर (detail) अणु
				dev_dbg(&पूर्णांकf->dev, "extra MDLM detail\n");
				जाओ bad_desc;
			पूर्ण
			detail = (व्योम *) buf;
			चयन (detail->bGuidDescriptorType) अणु
			हाल 0:			/* "SAFE" */
				अगर (detail->bLength != (माप *detail + 2))
					जाओ bad_detail;
				अवरोध;
			हाल 1:			/* "BLAN" */
				अगर (detail->bLength != (माप *detail + 3))
					जाओ bad_detail;
				अवरोध;
			शेष:
				जाओ bad_detail;
			पूर्ण

			/* assuming we either noticed BLAN alपढ़ोy, or will
			 * find it soon, there are some data bytes here:
			 *  - bmNetworkCapabilities (unused)
			 *  - bmDataCapabilities (bits, see below)
			 *  - bPad (ignored, क्रम PADAFTER -- BLAN-only)
			 * bits are:
			 *  - 0x01 -- Zaurus framing (add CRC)
			 *  - 0x02 -- PADBEFORE (CRC includes some padding)
			 *  - 0x04 -- PADAFTER (some padding after CRC)
			 *  - 0x08 -- "fermat" packet mangling (क्रम hw bugs)
			 * the PADBEFORE appears not to matter; we पूर्णांकerop
			 * with devices that use it and those that करोn't.
			 */
			अगर ((detail->bDetailData[1] & ~0x02) != 0x01) अणु
				/* bmDataCapabilities == 0 would be fine too,
				 * but framing is minidriver-coupled क्रम now.
				 */
bad_detail:
				dev_dbg(&पूर्णांकf->dev,
						"bad MDLM detail, %d %d %d\n",
						detail->bLength,
						detail->bDetailData[0],
						detail->bDetailData[2]);
				जाओ bad_desc;
			पूर्ण

			/* same extra framing as क्रम non-BLAN mode */
			dev->net->hard_header_len += 6;
			dev->rx_urb_size = dev->net->hard_header_len
					+ dev->net->mtu;
			अवरोध;
		पूर्ण
next_desc:
		len -= buf [0];	/* bLength */
		buf += buf [0];
	पूर्ण

	अगर (!desc || !detail) अणु
		dev_dbg(&पूर्णांकf->dev, "missing cdc mdlm %s%sdescriptor\n",
			desc ? "" : "func ",
			detail ? "" : "detail ");
		जाओ bad_desc;
	पूर्ण

	/* There's probably a CDC Ethernet descriptor there, but we can't
	 * rely on the Ethernet address it provides since not all venकरोrs
	 * bother to make it unique.  Likewise there's no poपूर्णांक in tracking
	 * of the CDC event notअगरications.
	 */
	वापस usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);

bad_desc:
	dev_info(&dev->udev->dev, "unsupported MDLM descriptors\n");
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा driver_info	bogus_mdlm_info = अणु
	.description =	"pseudo-MDLM (BLAN) device",
	.flags =	FLAG_POINTTOPOINT | FLAG_FRAMING_Z,
	.check_connect = always_connected,
	.tx_fixup =	zaurus_tx_fixup,
	.bind =		blan_mdlm_bind,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id	products [] = अणु
#घोषणा	ZAURUS_MASTER_INTERFACE \
	.bInterfaceClass	= USB_CLASS_COMM, \
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_ETHERNET, \
	.bInterfaceProtocol	= USB_CDC_PROTO_NONE

/* SA-1100 based Sharp Zaurus ("collie"), or compatible. */
अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x04DD,
	.idProduct		= 0x8004,
	ZAURUS_MASTER_INTERFACE,
	.driver_info = ZAURUS_STRONGARM_INFO,
पूर्ण,

/* PXA-2xx based models are also lying-about-cdc.  If you add any
 * more devices that claim to be CDC Ethernet, make sure they get
 * added to the blacklist in cdc_ether too.
 *
 * NOTE:  OpenZaurus versions with 2.6 kernels won't use these entries,
 * unlike the older ones with 2.4 "embedix" kernels.
 */
अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x04DD,
	.idProduct		= 0x8005,	/* A-300 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info = ZAURUS_PXA_INFO,
पूर्ण, अणु
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x04DD,
	.idProduct		= 0x8006,	/* B-500/SL-5600 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info = ZAURUS_PXA_INFO,
पूर्ण, अणु
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
	          | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr		= 0x04DD,
	.idProduct		= 0x8007,	/* C-700 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info = ZAURUS_PXA_INFO,
पूर्ण, अणु
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr               = 0x04DD,
	.idProduct              = 0x9031,	/* C-750 C-760 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info = ZAURUS_PXA_INFO,
पूर्ण, अणु
	/* C-750/C-760/C-860/SL-C3000 PDA in MDLM mode */
	USB_DEVICE_AND_INTERFACE_INFO(0x04DD, 0x9031, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_MDLM, USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ) &bogus_mdlm_info,
पूर्ण, अणु
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr               = 0x04DD,
	.idProduct              = 0x9032,	/* SL-6000 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info = ZAURUS_PXA_INFO,
पूर्ण, अणु
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVenकरोr               = 0x04DD,
	/* reported with some C860 units */
	.idProduct              = 0x9050,	/* C-860 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info = ZAURUS_PXA_INFO,
पूर्ण,
अणु
	/* Motorola Rokr E6 */
	USB_DEVICE_AND_INTERFACE_INFO(0x22b8, 0x6027, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_MDLM, USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ) &bogus_mdlm_info,
पूर्ण, अणु
	/* Motorola MOTOMAGX phones */
	USB_DEVICE_AND_INTERFACE_INFO(0x22b8, 0x6425, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_MDLM, USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ) &bogus_mdlm_info,
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
	.driver_info = OLYMPUS_MXL_INFO,
पूर्ण,

/* Logitech Harmony 900 - uses the pseuकरो-MDLM (BLAN) driver */
अणु
	USB_DEVICE_AND_INTERFACE_INFO(0x046d, 0xc11f, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_MDLM, USB_CDC_PROTO_NONE),
	.driver_info = (अचिन्हित दीर्घ) &bogus_mdlm_info,
पूर्ण,
	अणु पूर्ण,		// END
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver zaurus_driver = अणु
	.name =		"zaurus",
	.id_table =	products,
	.probe =	usbnet_probe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(zaurus_driver);

MODULE_AUTHOR("Pavel Machek, David Brownell");
MODULE_DESCRIPTION("Sharp Zaurus PDA, and compatible products");
MODULE_LICENSE("GPL");
