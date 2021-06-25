<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (C) 2004 Texas Instruments */

/*
 * This OTG and Embedded Host list is "Targeted Peripheral List".
 * It should mostly use of USB_DEVICE() or USB_DEVICE_VER() entries..
 *
 * YOU _SHOULD_ CHANGE THIS LIST TO MATCH YOUR PRODUCT AND ITS TESTING!
 */

अटल काष्ठा usb_device_id productlist_table[] = अणु

/* hubs are optional in OTG, but very handy ... */
अणु USB_DEVICE_INFO(USB_CLASS_HUB, 0, 0), पूर्ण,
अणु USB_DEVICE_INFO(USB_CLASS_HUB, 0, 1), पूर्ण,

#अगर_घोषित	CONFIG_USB_PRINTER		/* ignoring nonअटल linkage! */
/* FIXME actually, prपूर्णांकers are NOT supposed to use device classes;
 * they're supposed to use पूर्णांकerface classes...
 */
अणु USB_DEVICE_INFO(7, 1, 1) पूर्ण,
अणु USB_DEVICE_INFO(7, 1, 2) पूर्ण,
अणु USB_DEVICE_INFO(7, 1, 3) पूर्ण,
#पूर्ण_अगर

#अगर_घोषित	CONFIG_USB_NET_CDCETHER
/* Linux-USB CDC Ethernet gadget */
अणु USB_DEVICE(0x0525, 0xa4a1), पूर्ण,
/* Linux-USB CDC Ethernet + RNDIS gadget */
अणु USB_DEVICE(0x0525, 0xa4a2), पूर्ण,
#पूर्ण_अगर

#अगर	IS_ENABLED(CONFIG_USB_TEST)
/* gadget zero, क्रम testing */
अणु USB_DEVICE(0x0525, 0xa4a0), पूर्ण,
#पूर्ण_अगर

अणु पूर्ण	/* Terminating entry */
पूर्ण;

अटल पूर्णांक is_targeted(काष्ठा usb_device *dev)
अणु
	काष्ठा usb_device_id	*id = productlist_table;

	/* HNP test device is _never_ targeted (see OTG spec 6.6.6) */
	अगर ((le16_to_cpu(dev->descriptor.idVenकरोr) == 0x1a0a &&
	     le16_to_cpu(dev->descriptor.idProduct) == 0xbadd))
		वापस 0;

	/* OTG PET device is always targeted (see OTG 2.0 ECN 6.4.2) */
	अगर ((le16_to_cpu(dev->descriptor.idVenकरोr) == 0x1a0a &&
	     le16_to_cpu(dev->descriptor.idProduct) == 0x0200))
		वापस 1;

	/* NOTE: can't use usb_match_id() since पूर्णांकerface caches
	 * aren't set up yet. this is cut/paste from that code.
	 */
	क्रम (id = productlist_table; id->match_flags; id++) अणु
		अगर ((id->match_flags & USB_DEVICE_ID_MATCH_VENDOR) &&
		    id->idVenकरोr != le16_to_cpu(dev->descriptor.idVenकरोr))
			जारी;

		अगर ((id->match_flags & USB_DEVICE_ID_MATCH_PRODUCT) &&
		    id->idProduct != le16_to_cpu(dev->descriptor.idProduct))
			जारी;

		/* No need to test id->bcdDevice_lo != 0, since 0 is never
		   greater than any अचिन्हित number. */
		अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_LO) &&
		    (id->bcdDevice_lo > le16_to_cpu(dev->descriptor.bcdDevice)))
			जारी;

		अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_HI) &&
		    (id->bcdDevice_hi < le16_to_cpu(dev->descriptor.bcdDevice)))
			जारी;

		अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_CLASS) &&
		    (id->bDeviceClass != dev->descriptor.bDeviceClass))
			जारी;

		अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_SUBCLASS) &&
		    (id->bDeviceSubClass != dev->descriptor.bDeviceSubClass))
			जारी;

		अगर ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_PROTOCOL) &&
		    (id->bDeviceProtocol != dev->descriptor.bDeviceProtocol))
			जारी;

		वापस 1;
	पूर्ण

	/* add other match criteria here ... */


	/* OTG MESSAGE: report errors here, customize to match your product */
	dev_err(&dev->dev, "device v%04x p%04x is not supported\n",
		le16_to_cpu(dev->descriptor.idVenकरोr),
		le16_to_cpu(dev->descriptor.idProduct));

	वापस 0;
पूर्ण

