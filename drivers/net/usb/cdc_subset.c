<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Simple "CDC Subset" USB Networking Links
 * Copyright (C) 2000-2005 by David Brownell
 */

#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/usbnet.h>


/*
 * This supports simple USB network links that करोn't require any special
 * framing or hardware control operations.  The protocol used here is a
 * strict subset of CDC Ethernet, with three basic dअगरferences reflecting
 * the goal that almost any hardware should run it:
 *
 *  - Minimal runसमय control:  one पूर्णांकerface, no altsettings, and
 *    no venकरोr or class specअगरic control requests.  If a device is
 *    configured, it is allowed to exchange packets with the host.
 *    Fancier models would mean not working on some hardware.
 *
 *  - Minimal manufacturing control:  no IEEE "Organizationally
 *    Unique ID" required, or an EEPROMs to store one.  Each host uses
 *    one अक्रमom "locally assigned" Ethernet address instead, which can
 *    of course be overridden using standard tools like "ifconfig".
 *    (With 2^46 such addresses, same-net collisions are quite rare.)
 *
 *  - There is no additional framing data क्रम USB.  Packets are written
 *    exactly as in CDC Ethernet, starting with an Ethernet header and
 *    terminated by a लघु packet.  However, the host will never send a
 *    zero length packet; some प्रणालीs can't handle those robustly.
 *
 * Anything that can transmit and receive USB bulk packets can implement
 * this protocol.  That includes both smart peripherals and quite a lot
 * of "host-to-host" USB cables (which embed two devices back-to-back).
 *
 * Note that although Linux may use many of those host-to-host links
 * with this "cdc_subset" framing, that करोesn't mean there may not be a
 * better approach.  Handling the "other end unplugs/replugs" scenario
 * well tends to require chip-specअगरic venकरोr requests.  Also, Winकरोws
 * peers at the other end of host-to-host cables may expect their own
 * framing to be used rather than this "cdc_subset" model.
 */

#अगर defined(CONFIG_USB_EPSON2888) || defined(CONFIG_USB_ARMLINUX)
/* PDA style devices are always connected अगर present */
अटल पूर्णांक always_connected (काष्ठा usbnet *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित	CONFIG_USB_ALI_M5632
#घोषणा	HAVE_HARDWARE

/*-------------------------------------------------------------------------
 *
 * ALi M5632 driver ... करोes high speed
 *
 * NOTE that the MS-Winकरोws drivers क्रम this chip use some funky and
 * (naturally) unकरोcumented 7-byte prefix to each packet, so this is a
 * हाल where we करोn't currently पूर्णांकeroperate.  Also, once you unplug
 * one end of the cable, you need to replug the other end too ... since
 * chip करोcs are unavailable, there's no way to reset the relevant state
 * लघु of a घातer cycle.
 *
 *-------------------------------------------------------------------------*/

अटल व्योम m5632_recover(काष्ठा usbnet *dev)
अणु
	काष्ठा usb_device	*udev = dev->udev;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf = dev->पूर्णांकf;
	पूर्णांक r;

	r = usb_lock_device_क्रम_reset(udev, पूर्णांकf);
	अगर (r < 0)
		वापस;

	usb_reset_device(udev);
	usb_unlock_device(udev);
पूर्ण

अटल स्थिर काष्ठा driver_info	ali_m5632_info = अणु
	.description =	"ALi M5632",
	.flags       = FLAG_POINTTOPOINT,
	.recover     = m5632_recover,
पूर्ण;

#पूर्ण_अगर

#अगर_घोषित	CONFIG_USB_AN2720
#घोषणा	HAVE_HARDWARE

/*-------------------------------------------------------------------------
 *
 * AnchorChips 2720 driver ... http://www.cypress.com
 *
 * This करोesn't seem to have a way to detect whether the peer is
 * connected, or need any reset handshaking.  It's got pretty big
 * पूर्णांकernal buffers (handles most of a frame's worth of data).
 * Chip data sheets करोn't describe any venकरोr control messages.
 *
 *-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा driver_info	an2720_info = अणु
	.description =	"AnchorChips/Cypress 2720",
	.flags       = FLAG_POINTTOPOINT,
	// no reset available!
	// no check_connect available!

	.in = 2, .out = 2,		// direction distinguishes these
पूर्ण;

#पूर्ण_अगर	/* CONFIG_USB_AN2720 */


#अगर_घोषित	CONFIG_USB_BELKIN
#घोषणा	HAVE_HARDWARE

/*-------------------------------------------------------------------------
 *
 * Belkin F5U104 ... two NetChip 2280 devices + Aपंचांगel AVR microcontroller
 *
 * ... also two eTEK designs, including one sold as "Advance USBNET"
 *
 *-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा driver_info	belkin_info = अणु
	.description =	"Belkin, eTEK, or compatible",
	.flags       = FLAG_POINTTOPOINT,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_USB_BELKIN */



#अगर_घोषित	CONFIG_USB_EPSON2888
#घोषणा	HAVE_HARDWARE

/*-------------------------------------------------------------------------
 *
 * EPSON USB clients
 *
 * This is the same idea as Linux PDAs (below) except the firmware in the
 * device might not be Tux-घातered.  Epson provides reference firmware that
 * implements this पूर्णांकerface.  Product developers can reuse or modअगरy that
 * code, such as by using their own product and venकरोr codes.
 *
 * Support was from Juro Bystricky <bystricky.juro@erd.epson.com>
 *
 *-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा driver_info	epson2888_info = अणु
	.description =	"Epson USB Device",
	.check_connect = always_connected,
	.flags = FLAG_POINTTOPOINT,

	.in = 4, .out = 3,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_USB_EPSON2888 */


/*-------------------------------------------------------------------------
 *
 * info from Jonathan McDowell <noodles@earth.li>
 *
 *-------------------------------------------------------------------------*/
#अगर_घोषित CONFIG_USB_KC2190
#घोषणा HAVE_HARDWARE
अटल स्थिर काष्ठा driver_info kc2190_info = अणु
	.description =  "KC Technology KC-190",
	.flags = FLAG_POINTTOPOINT,
पूर्ण;
#पूर्ण_अगर /* CONFIG_USB_KC2190 */


#अगर_घोषित	CONFIG_USB_ARMLINUX
#घोषणा	HAVE_HARDWARE

/*-------------------------------------------------------------------------
 *
 * Intel's SA-1100 chip पूर्णांकegrates basic USB support, and is used
 * in PDAs like some iPaqs, the Yopy, some Zaurus models, and more.
 * When they run Linux, arch/arm/mach-sa1100/usb-eth.c may be used to
 * network using minimal USB framing data.
 *
 * This describes the driver currently in standard ARM Linux kernels.
 * The Zaurus uses a dअगरferent driver (see later).
 *
 * PXA25x and PXA210 use XScale cores (ARM v5TE) with better USB support
 * and dअगरferent USB endpoपूर्णांक numbering than the SA1100 devices.  The
 * mach-pxa/usb-eth.c driver re-uses the device ids from mach-sa1100
 * so we rely on the endpoपूर्णांक descriptors.
 *
 *-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा driver_info	linuxdev_info = अणु
	.description =	"Linux Device",
	.check_connect = always_connected,
	.flags = FLAG_POINTTOPOINT,
पूर्ण;

अटल स्थिर काष्ठा driver_info	yopy_info = अणु
	.description =	"Yopy",
	.check_connect = always_connected,
	.flags = FLAG_POINTTOPOINT,
पूर्ण;

अटल स्थिर काष्ठा driver_info	blob_info = अणु
	.description =	"Boot Loader OBject",
	.check_connect = always_connected,
	.flags = FLAG_POINTTOPOINT,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_USB_ARMLINUX */


/*-------------------------------------------------------------------------*/

#अगर_अघोषित	HAVE_HARDWARE
#warning You need to configure some hardware क्रम this driver
#पूर्ण_अगर

/*
 * chip venकरोr names won't normally be on the cables, and
 * may not be on the device.
 */

अटल स्थिर काष्ठा usb_device_id	products [] = अणु

#अगर_घोषित	CONFIG_USB_ALI_M5632
अणु
	USB_DEVICE (0x0402, 0x5632),	// ALi शेषs
	.driver_info =	(अचिन्हित दीर्घ) &ali_m5632_info,
पूर्ण,
अणु
	USB_DEVICE (0x182d,0x207c),	// SiteCom CN-124
	.driver_info =	(अचिन्हित दीर्घ) &ali_m5632_info,
पूर्ण,
#पूर्ण_अगर

#अगर_घोषित	CONFIG_USB_AN2720
अणु
	USB_DEVICE (0x0547, 0x2720),	// AnchorChips शेषs
	.driver_info =	(अचिन्हित दीर्घ) &an2720_info,
पूर्ण, अणु
	USB_DEVICE (0x0547, 0x2727),	// Xircom PGUNET
	.driver_info =	(अचिन्हित दीर्घ) &an2720_info,
पूर्ण,
#पूर्ण_अगर

#अगर_घोषित	CONFIG_USB_BELKIN
अणु
	USB_DEVICE (0x050d, 0x0004),	// Belkin
	.driver_info =	(अचिन्हित दीर्घ) &belkin_info,
पूर्ण, अणु
	USB_DEVICE (0x056c, 0x8100),	// eTEK
	.driver_info =	(अचिन्हित दीर्घ) &belkin_info,
पूर्ण, अणु
	USB_DEVICE (0x0525, 0x9901),	// Advance USBNET (eTEK)
	.driver_info =	(अचिन्हित दीर्घ) &belkin_info,
पूर्ण,
#पूर्ण_अगर

#अगर_घोषित	CONFIG_USB_EPSON2888
अणु
	USB_DEVICE (0x0525, 0x2888),	// EPSON USB client
	.driver_info	= (अचिन्हित दीर्घ) &epson2888_info,
पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_KC2190
अणु
	USB_DEVICE (0x050f, 0x0190),	// KC-190
	.driver_info =	(अचिन्हित दीर्घ) &kc2190_info,
पूर्ण,
#पूर्ण_अगर

#अगर_घोषित	CONFIG_USB_ARMLINUX
/*
 * SA-1100 using standard ARM Linux kernels, or compatible.
 * Often used when talking to Linux PDAs (iPaq, Yopy, etc).
 * The sa-1100 "usb-eth" driver handles the basic framing.
 *
 * PXA25x or PXA210 ...  these use a "usb-eth" driver much like
 * the sa1100 one, but hardware uses dअगरferent endpoपूर्णांक numbers.
 *
 * Or the Linux "Ethernet" gadget on hardware that can't talk
 * CDC Ethernet (e.g., no altsettings), in either of two modes:
 *  - acting just like the old "usb-eth" firmware, though
 *    the implementation is dअगरferent
 *  - supporting RNDIS as the first/शेष configuration क्रम
 *    MS-Winकरोws पूर्णांकerop; Linux needs to use the other config
 */
अणु
	// 1183 = 0x049F, both used as hex values?
	// Compaq "Itsy" venकरोr/product id
	USB_DEVICE (0x049F, 0x505A),	// usb-eth, or compatible
	.driver_info =	(अचिन्हित दीर्घ) &linuxdev_info,
पूर्ण, अणु
	USB_DEVICE (0x0E7E, 0x1001),	// G.Mate "Yopy"
	.driver_info =	(अचिन्हित दीर्घ) &yopy_info,
पूर्ण, अणु
	USB_DEVICE (0x8086, 0x07d3),	// "blob" bootloader
	.driver_info =	(अचिन्हित दीर्घ) &blob_info,
पूर्ण, अणु
	USB_DEVICE (0x1286, 0x8001),    // "blob" bootloader
	.driver_info =  (अचिन्हित दीर्घ) &blob_info,
पूर्ण, अणु
	// Linux Ethernet/RNDIS gadget, mostly on PXA, second config
	// e.g. Gumstix, current OpenZaurus, ... or anything अन्यथा
	// that just enables this gadget option.
	USB_DEVICE (0x0525, 0xa4a2),
	.driver_info =	(अचिन्हित दीर्घ) &linuxdev_info,
पूर्ण,
#पूर्ण_अगर

	अणु पूर्ण,		// END
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

/*-------------------------------------------------------------------------*/
अटल पूर्णांक dummy_prereset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
        वापस 0;
पूर्ण

अटल पूर्णांक dummy_postreset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
        वापस 0;
पूर्ण

अटल काष्ठा usb_driver cdc_subset_driver = अणु
	.name =		"cdc_subset",
	.probe =	usbnet_probe,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.pre_reset =	dummy_prereset,
	.post_reset =	dummy_postreset,
	.disconnect =	usbnet_disconnect,
	.id_table =	products,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(cdc_subset_driver);

MODULE_AUTHOR("David Brownell");
MODULE_DESCRIPTION("Simple 'CDC Subset' USB networking links");
MODULE_LICENSE("GPL");
