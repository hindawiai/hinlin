<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PL-2301/2302 USB host-to-host link cables
 * Copyright (C) 2000-2005 by David Brownell
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
#समावेश <linux/usb/usbnet.h>


/*
 * Prolअगरic PL-2301/PL-2302 driver ... http://www.prolअगरic.com.tw/ 
 *
 * The protocol and handshaking used here should be bug-compatible
 * with the Linux 2.2 "plusb" driver, by Deti Fliegl.
 *
 * HEADS UP:  this handshaking isn't all that robust.  This driver
 * माला_लो confused easily अगर you unplug one end of the cable then
 * try to connect it again; you'll need to restart both ends. The
 * "naplink" software (used by some PlayStation/2 developers) करोes
 * the handshaking much better!   Also, someबार this hardware
 * seems to get wedged under load.  Prolअगरic करोcs are weak, and
 * करोn't identअगरy dअगरferences between PL2301 and PL2302, much less
 * anything to explain the dअगरferent PL2302 versions observed.
 *
 * NOTE:  pl2501 has several modes, including pl2301 and pl2302
 * compatibility.   Some करोcs suggest the dअगरference between 2301
 * and 2302 is only to make MS-Winकरोws use a dअगरferent driver...
 *
 * pl25a1 glue based on patch from Tony Gibbs.  Prolअगरic "docs" on
 * this chip are as usual incomplete about what control messages
 * are supported.
 */

/*
 * Bits 0-4 can be used क्रम software handshaking; they're set from
 * one end, cleared from the other, "read" with the पूर्णांकerrupt byte.
 */
#घोषणा	PL_S_EN		(1<<7)		/* (feature only) suspend enable */
/* reserved bit -- rx पढ़ोy (6) ? */
#घोषणा	PL_TX_READY	(1<<5)		/* (पूर्णांकerrupt only) transmit पढ़ोy */
#घोषणा	PL_RESET_OUT	(1<<4)		/* reset output pipe */
#घोषणा	PL_RESET_IN	(1<<3)		/* reset input pipe */
#घोषणा	PL_TX_C		(1<<2)		/* transmission complete */
#घोषणा	PL_TX_REQ	(1<<1)		/* transmission received */
#घोषणा	PL_PEER_E	(1<<0)		/* peer exists */

अटल अंतरभूत पूर्णांक
pl_venकरोr_req(काष्ठा usbnet *dev, u8 req, u8 val, u8 index)
अणु
	वापस usbnet_पढ़ो_cmd(dev, req,
				USB_सूची_IN | USB_TYPE_VENDOR |
				USB_RECIP_DEVICE,
				val, index, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक
pl_clear_QuickLink_features(काष्ठा usbnet *dev, पूर्णांक val)
अणु
	वापस pl_venकरोr_req(dev, 1, (u8) val, 0);
पूर्ण

अटल अंतरभूत पूर्णांक
pl_set_QuickLink_features(काष्ठा usbnet *dev, पूर्णांक val)
अणु
	वापस pl_venकरोr_req(dev, 3, (u8) val, 0);
पूर्ण

अटल पूर्णांक pl_reset(काष्ठा usbnet *dev)
अणु
	पूर्णांक status;

	/* some units seem to need this reset, others reject it utterly.
	 * FIXME be more like "naplink" or winकरोws drivers.
	 */
	status = pl_set_QuickLink_features(dev,
		PL_S_EN|PL_RESET_OUT|PL_RESET_IN|PL_PEER_E);
	अगर (status != 0 && netअगर_msg_probe(dev))
		netअगर_dbg(dev, link, dev->net, "pl_reset --> %d\n", status);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा driver_info	prolअगरic_info = अणु
	.description =	"Prolific PL-2301/PL-2302/PL-25A1/PL-27A1",
	.flags =	FLAG_POINTTOPOINT | FLAG_NO_SETINT,
		/* some PL-2302 versions seem to fail usb_set_पूर्णांकerface() */
	.reset =	pl_reset,
पूर्ण;


/*-------------------------------------------------------------------------*/

/*
 * Proilअगरic's name won't normally be on the cables, and
 * may not be on the device.
 */

अटल स्थिर काष्ठा usb_device_id	products [] = अणु

/* full speed cables */
अणु
	USB_DEVICE(0x067b, 0x0000),	// PL-2301
	.driver_info =	(अचिन्हित दीर्घ) &prolअगरic_info,
पूर्ण, अणु
	USB_DEVICE(0x067b, 0x0001),	// PL-2302
	.driver_info =	(अचिन्हित दीर्घ) &prolअगरic_info,
पूर्ण,

/* high speed cables */
अणु
	USB_DEVICE(0x067b, 0x25a1),     /* PL-25A1, no eeprom */
	.driver_info =  (अचिन्हित दीर्घ) &prolअगरic_info,
पूर्ण, अणु
	USB_DEVICE(0x050d, 0x258a),     /* Belkin F5U258/F5U279 (PL-25A1) */
	.driver_info =  (अचिन्हित दीर्घ) &prolअगरic_info,
पूर्ण, अणु
	USB_DEVICE(0x3923, 0x7825),     /* National Instruments USB
					 * Host-to-Host Cable
					 */
	.driver_info =  (अचिन्हित दीर्घ) &prolअगरic_info,

पूर्ण,

/* super speed cables */
अणु
	USB_DEVICE(0x067b, 0x27a1),     /* PL-27A1, no eeprom
					 * also: goobay Active USB 3.0
					 * Data Link,
					 * Unitek Y-3501
					 */
	.driver_info =  (अचिन्हित दीर्घ) &prolअगरic_info,
पूर्ण,

	अणु पूर्ण,		// END
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver plusb_driver = अणु
	.name =		"plusb",
	.id_table =	products,
	.probe =	usbnet_probe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(plusb_driver);

MODULE_AUTHOR("David Brownell");
MODULE_DESCRIPTION("Prolific PL-2301/2302/25A1/27A1 USB Host to Host Link Driver");
MODULE_LICENSE("GPL");
