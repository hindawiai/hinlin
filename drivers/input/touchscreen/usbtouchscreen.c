<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 * usbtouchscreen.c
 * Driver क्रम USB Touchscreens, supporting those devices:
 *  - eGalax Touchkit
 *    includes eTurboTouch CT-410/510/700
 *  - 3M/Microtouch  EX II series
 *  - ITM
 *  - PanJit TouchSet
 *  - eTurboTouch
 *  - Gunze AHL61
 *  - DMC TSC-10/25
 *  - IRTOUCHSYSTEMS/UNITOP
 *  - IdealTEK URTC1000
 *  - General Touch
 *  - GoTop Super_Q2/GogoPen/PenPower tablets
 *  - JASTEC USB touch controller/DigiTech DTR-02U
 *  - Zytronic capacitive touchscreen
 *  - NEXIO/iNexio
 *  - Elo TouchSystems 2700 IntelliTouch
 *  - EasyTouch USB Dual/Multi touch controller from Data Modul
 *
 * Copyright (C) 2004-2007 by Daniel Ritz <daniel.ritz@gmx.ch>
 * Copyright (C) by Todd E. Johnson (mtouchusb.c)
 *
 * Driver is based on touchkitusb.c
 * - ITM parts are from iपंचांगtouch.c
 * - 3M parts are from mtouchusb.c
 * - PanJit parts are from an unmerged driver by Lanslott Gish
 * - DMC TSC 10/25 are from Holger Schurig, with ideas from an unmerged
 *   driver from Marius Vollmer
 *
 *****************************************************************************/

//#घोषणा DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/mutex.h>

अटल bool swap_xy;
module_param(swap_xy, bool, 0644);
MODULE_PARM_DESC(swap_xy, "If set X and Y axes are swapped.");

अटल bool hwcalib_xy;
module_param(hwcalib_xy, bool, 0644);
MODULE_PARM_DESC(hwcalib_xy, "If set hw-calibrated X/Y are used if available");

/* device specअगरc data/functions */
काष्ठा usbtouch_usb;
काष्ठा usbtouch_device_info अणु
	पूर्णांक min_xc, max_xc;
	पूर्णांक min_yc, max_yc;
	पूर्णांक min_press, max_press;
	पूर्णांक rept_size;

	/*
	 * Always service the USB devices irq not just when the input device is
	 * खोलो. This is useful when devices have a watchकरोg which prevents us
	 * from periodically polling the device. Leave this unset unless your
	 * touchscreen device requires it, as it करोes consume more of the USB
	 * bandwidth.
	 */
	bool irq_always;

	व्योम (*process_pkt) (काष्ठा usbtouch_usb *usbtouch, अचिन्हित अक्षर *pkt, पूर्णांक len);

	/*
	 * used to get the packet len. possible वापस values:
	 * > 0: packet len
	 * = 0: skip one byte
	 * < 0: -वापस value more bytes needed
	 */
	पूर्णांक  (*get_pkt_len) (अचिन्हित अक्षर *pkt, पूर्णांक len);

	पूर्णांक  (*पढ़ो_data)   (काष्ठा usbtouch_usb *usbtouch, अचिन्हित अक्षर *pkt);
	पूर्णांक  (*alloc)       (काष्ठा usbtouch_usb *usbtouch);
	पूर्णांक  (*init)        (काष्ठा usbtouch_usb *usbtouch);
	व्योम (*निकास)	    (काष्ठा usbtouch_usb *usbtouch);
पूर्ण;

/* a usbtouch device */
काष्ठा usbtouch_usb अणु
	अचिन्हित अक्षर *data;
	dma_addr_t data_dma;
	पूर्णांक data_size;
	अचिन्हित अक्षर *buffer;
	पूर्णांक buf_len;
	काष्ठा urb *irq;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	काष्ठा input_dev *input;
	काष्ठा usbtouch_device_info *type;
	काष्ठा mutex pm_mutex;  /* serialize access to खोलो/suspend */
	bool is_खोलो;
	अक्षर name[128];
	अक्षर phys[64];
	व्योम *priv;

	पूर्णांक x, y;
	पूर्णांक touch, press;
पूर्ण;


/* device types */
क्रमागत अणु
	DEVTYPE_IGNORE = -1,
	DEVTYPE_EGALAX,
	DEVTYPE_PANJIT,
	DEVTYPE_3M,
	DEVTYPE_ITM,
	DEVTYPE_ETURBO,
	DEVTYPE_GUNZE,
	DEVTYPE_DMC_TSC10,
	DEVTYPE_IRTOUCH,
	DEVTYPE_IRTOUCH_HIRES,
	DEVTYPE_IDEALTEK,
	DEVTYPE_GENERAL_TOUCH,
	DEVTYPE_GOTOP,
	DEVTYPE_JASTEC,
	DEVTYPE_E2I,
	DEVTYPE_ZYTRONIC,
	DEVTYPE_TC45USB,
	DEVTYPE_NEXIO,
	DEVTYPE_ELO,
	DEVTYPE_ETOUCH,
पूर्ण;

#घोषणा USB_DEVICE_HID_CLASS(vend, prod) \
	.match_flags = USB_DEVICE_ID_MATCH_INT_CLASS \
		| USB_DEVICE_ID_MATCH_DEVICE, \
	.idVenकरोr = (vend), \
	.idProduct = (prod), \
	.bInterfaceClass = USB_INTERFACE_CLASS_HID

अटल स्थिर काष्ठा usb_device_id usbtouch_devices[] = अणु
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_EGALAX
	/* ignore the HID capable devices, handled by usbhid */
	अणुUSB_DEVICE_HID_CLASS(0x0eef, 0x0001), .driver_info = DEVTYPE_IGNOREपूर्ण,
	अणुUSB_DEVICE_HID_CLASS(0x0eef, 0x0002), .driver_info = DEVTYPE_IGNOREपूर्ण,

	/* normal device IDs */
	अणुUSB_DEVICE(0x3823, 0x0001), .driver_info = DEVTYPE_EGALAXपूर्ण,
	अणुUSB_DEVICE(0x3823, 0x0002), .driver_info = DEVTYPE_EGALAXपूर्ण,
	अणुUSB_DEVICE(0x0123, 0x0001), .driver_info = DEVTYPE_EGALAXपूर्ण,
	अणुUSB_DEVICE(0x0eef, 0x0001), .driver_info = DEVTYPE_EGALAXपूर्ण,
	अणुUSB_DEVICE(0x0eef, 0x0002), .driver_info = DEVTYPE_EGALAXपूर्ण,
	अणुUSB_DEVICE(0x1234, 0x0001), .driver_info = DEVTYPE_EGALAXपूर्ण,
	अणुUSB_DEVICE(0x1234, 0x0002), .driver_info = DEVTYPE_EGALAXपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_PANJIT
	अणुUSB_DEVICE(0x134c, 0x0001), .driver_info = DEVTYPE_PANJITपूर्ण,
	अणुUSB_DEVICE(0x134c, 0x0002), .driver_info = DEVTYPE_PANJITपूर्ण,
	अणुUSB_DEVICE(0x134c, 0x0003), .driver_info = DEVTYPE_PANJITपूर्ण,
	अणुUSB_DEVICE(0x134c, 0x0004), .driver_info = DEVTYPE_PANJITपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_3M
	अणुUSB_DEVICE(0x0596, 0x0001), .driver_info = DEVTYPE_3Mपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ITM
	अणुUSB_DEVICE(0x0403, 0xf9e9), .driver_info = DEVTYPE_ITMपूर्ण,
	अणुUSB_DEVICE(0x16e3, 0xf9e9), .driver_info = DEVTYPE_ITMपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ETURBO
	अणुUSB_DEVICE(0x1234, 0x5678), .driver_info = DEVTYPE_ETURBOपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_GUNZE
	अणुUSB_DEVICE(0x0637, 0x0001), .driver_info = DEVTYPE_GUNZEपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_DMC_TSC10
	अणुUSB_DEVICE(0x0afa, 0x03e8), .driver_info = DEVTYPE_DMC_TSC10पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_IRTOUCH
	अणुUSB_DEVICE(0x255e, 0x0001), .driver_info = DEVTYPE_IRTOUCHपूर्ण,
	अणुUSB_DEVICE(0x595a, 0x0001), .driver_info = DEVTYPE_IRTOUCHपूर्ण,
	अणुUSB_DEVICE(0x6615, 0x0001), .driver_info = DEVTYPE_IRTOUCHपूर्ण,
	अणुUSB_DEVICE(0x6615, 0x0012), .driver_info = DEVTYPE_IRTOUCH_HIRESपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_IDEALTEK
	अणुUSB_DEVICE(0x1391, 0x1000), .driver_info = DEVTYPE_IDEALTEKपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_GENERAL_TOUCH
	अणुUSB_DEVICE(0x0dfc, 0x0001), .driver_info = DEVTYPE_GENERAL_TOUCHपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_GOTOP
	अणुUSB_DEVICE(0x08f2, 0x007f), .driver_info = DEVTYPE_GOTOPपूर्ण,
	अणुUSB_DEVICE(0x08f2, 0x00ce), .driver_info = DEVTYPE_GOTOPपूर्ण,
	अणुUSB_DEVICE(0x08f2, 0x00f4), .driver_info = DEVTYPE_GOTOPपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_JASTEC
	अणुUSB_DEVICE(0x0f92, 0x0001), .driver_info = DEVTYPE_JASTECपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_E2I
	अणुUSB_DEVICE(0x1ac7, 0x0001), .driver_info = DEVTYPE_E2Iपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ZYTRONIC
	अणुUSB_DEVICE(0x14c8, 0x0003), .driver_info = DEVTYPE_ZYTRONICपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ETT_TC45USB
	/* TC5UH */
	अणुUSB_DEVICE(0x0664, 0x0309), .driver_info = DEVTYPE_TC45USBपूर्ण,
	/* TC4UM */
	अणुUSB_DEVICE(0x0664, 0x0306), .driver_info = DEVTYPE_TC45USBपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_NEXIO
	/* data पूर्णांकerface only */
	अणुUSB_DEVICE_AND_INTERFACE_INFO(0x10f0, 0x2002, 0x0a, 0x00, 0x00),
		.driver_info = DEVTYPE_NEXIOपूर्ण,
	अणुUSB_DEVICE_AND_INTERFACE_INFO(0x1870, 0x0001, 0x0a, 0x00, 0x00),
		.driver_info = DEVTYPE_NEXIOपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ELO
	अणुUSB_DEVICE(0x04e7, 0x0020), .driver_info = DEVTYPE_ELOपूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_EASYTOUCH
	अणुUSB_DEVICE(0x7374, 0x0001), .driver_info = DEVTYPE_ETOUCHपूर्ण,
#पूर्ण_अगर

	अणुपूर्ण
पूर्ण;


/*****************************************************************************
 * e2i Part
 */

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_E2I
अटल पूर्णांक e2i_init(काष्ठा usbtouch_usb *usbtouch)
अणु
	पूर्णांक ret;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(usbtouch->पूर्णांकerface);

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
	                      0x01, 0x02, 0x0000, 0x0081,
	                      शून्य, 0, USB_CTRL_SET_TIMEOUT);

	dev_dbg(&usbtouch->पूर्णांकerface->dev,
		"%s - usb_control_msg - E2I_RESET - bytes|err: %d\n",
		__func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक e2i_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	पूर्णांक पंचांगp = (pkt[0] << 8) | pkt[1];
	dev->x  = (pkt[2] << 8) | pkt[3];
	dev->y  = (pkt[4] << 8) | pkt[5];

	पंचांगp = पंचांगp - 0xA000;
	dev->touch = (पंचांगp > 0);
	dev->press = (पंचांगp > 0 ? पंचांगp : 0);

	वापस 1;
पूर्ण
#पूर्ण_अगर


/*****************************************************************************
 * eGalax part
 */

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_EGALAX

#अगर_अघोषित MULTI_PACKET
#घोषणा MULTI_PACKET
#पूर्ण_अगर

#घोषणा EGALAX_PKT_TYPE_MASK		0xFE
#घोषणा EGALAX_PKT_TYPE_REPT		0x80
#घोषणा EGALAX_PKT_TYPE_DIAG		0x0A

अटल पूर्णांक egalax_init(काष्ठा usbtouch_usb *usbtouch)
अणु
	पूर्णांक ret, i;
	अचिन्हित अक्षर *buf;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(usbtouch->पूर्णांकerface);

	/*
	 * An eGalax diagnostic packet kicks the device पूर्णांकo using the right
	 * protocol.  We send a "check active" packet.  The response will be
	 * पढ़ो later and ignored.
	 */

	buf = kदो_स्मृति(3, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = EGALAX_PKT_TYPE_DIAG;
	buf[1] = 1;	/* length */
	buf[2] = 'A';	/* command - check active */

	क्रम (i = 0; i < 3; i++) अणु
		ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				      0,
				      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				      0, 0, buf, 3,
				      USB_CTRL_SET_TIMEOUT);
		अगर (ret >= 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		अगर (ret != -EPIPE)
			अवरोध;
	पूर्ण

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक egalax_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	अगर ((pkt[0] & EGALAX_PKT_TYPE_MASK) != EGALAX_PKT_TYPE_REPT)
		वापस 0;

	dev->x = ((pkt[3] & 0x0F) << 7) | (pkt[4] & 0x7F);
	dev->y = ((pkt[1] & 0x0F) << 7) | (pkt[2] & 0x7F);
	dev->touch = pkt[0] & 0x01;

	वापस 1;
पूर्ण

अटल पूर्णांक egalax_get_pkt_len(अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	चयन (buf[0] & EGALAX_PKT_TYPE_MASK) अणु
	हाल EGALAX_PKT_TYPE_REPT:
		वापस 5;

	हाल EGALAX_PKT_TYPE_DIAG:
		अगर (len < 2)
			वापस -1;

		वापस buf[1] + 2;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * EasyTouch part
 */

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_EASYTOUCH

#अगर_अघोषित MULTI_PACKET
#घोषणा MULTI_PACKET
#पूर्ण_अगर

#घोषणा ETOUCH_PKT_TYPE_MASK		0xFE
#घोषणा ETOUCH_PKT_TYPE_REPT		0x80
#घोषणा ETOUCH_PKT_TYPE_REPT2		0xB0
#घोषणा ETOUCH_PKT_TYPE_DIAG		0x0A

अटल पूर्णांक etouch_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	अगर ((pkt[0] & ETOUCH_PKT_TYPE_MASK) != ETOUCH_PKT_TYPE_REPT &&
		(pkt[0] & ETOUCH_PKT_TYPE_MASK) != ETOUCH_PKT_TYPE_REPT2)
		वापस 0;

	dev->x = ((pkt[1] & 0x1F) << 7) | (pkt[2] & 0x7F);
	dev->y = ((pkt[3] & 0x1F) << 7) | (pkt[4] & 0x7F);
	dev->touch = pkt[0] & 0x01;

	वापस 1;
पूर्ण

अटल पूर्णांक etouch_get_pkt_len(अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	चयन (buf[0] & ETOUCH_PKT_TYPE_MASK) अणु
	हाल ETOUCH_PKT_TYPE_REPT:
	हाल ETOUCH_PKT_TYPE_REPT2:
		वापस 5;

	हाल ETOUCH_PKT_TYPE_DIAG:
		अगर (len < 2)
			वापस -1;

		वापस buf[1] + 2;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * PanJit Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_PANJIT
अटल पूर्णांक panjit_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	dev->x = ((pkt[2] & 0x0F) << 8) | pkt[1];
	dev->y = ((pkt[4] & 0x0F) << 8) | pkt[3];
	dev->touch = pkt[0] & 0x01;

	वापस 1;
पूर्ण
#पूर्ण_अगर


/*****************************************************************************
 * 3M/Microtouch Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_3M

#घोषणा MTOUCHUSB_ASYNC_REPORT          1
#घोषणा MTOUCHUSB_RESET                 7
#घोषणा MTOUCHUSB_REQ_CTRLLR_ID         10

#घोषणा MTOUCHUSB_REQ_CTRLLR_ID_LEN	16

अटल पूर्णांक mtouch_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	अगर (hwcalib_xy) अणु
		dev->x = (pkt[4] << 8) | pkt[3];
		dev->y = 0xffff - ((pkt[6] << 8) | pkt[5]);
	पूर्ण अन्यथा अणु
		dev->x = (pkt[8] << 8) | pkt[7];
		dev->y = (pkt[10] << 8) | pkt[9];
	पूर्ण
	dev->touch = (pkt[2] & 0x40) ? 1 : 0;

	वापस 1;
पूर्ण

काष्ठा mtouch_priv अणु
	u8 fw_rev_major;
	u8 fw_rev_minor;
पूर्ण;

अटल sमाप_प्रकार mtouch_firmware_rev_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *output)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usbtouch_usb *usbtouch = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा mtouch_priv *priv = usbtouch->priv;

	वापस scnम_लिखो(output, PAGE_SIZE, "%1x.%1x\n",
			 priv->fw_rev_major, priv->fw_rev_minor);
पूर्ण
अटल DEVICE_ATTR(firmware_rev, 0444, mtouch_firmware_rev_show, शून्य);

अटल काष्ठा attribute *mtouch_attrs[] = अणु
	&dev_attr_firmware_rev.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mtouch_attr_group = अणु
	.attrs = mtouch_attrs,
पूर्ण;

अटल पूर्णांक mtouch_get_fw_revision(काष्ठा usbtouch_usb *usbtouch)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(usbtouch->पूर्णांकerface);
	काष्ठा mtouch_priv *priv = usbtouch->priv;
	u8 *buf;
	पूर्णांक ret;

	buf = kzalloc(MTOUCHUSB_REQ_CTRLLR_ID_LEN, GFP_NOIO);
	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      MTOUCHUSB_REQ_CTRLLR_ID,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, 0, buf, MTOUCHUSB_REQ_CTRLLR_ID_LEN,
			      USB_CTRL_SET_TIMEOUT);
	अगर (ret != MTOUCHUSB_REQ_CTRLLR_ID_LEN) अणु
		dev_warn(&usbtouch->पूर्णांकerface->dev,
			 "Failed to read FW rev: %d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		जाओ मुक्त;
	पूर्ण

	priv->fw_rev_major = buf[3];
	priv->fw_rev_minor = buf[4];

	ret = 0;

मुक्त:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक mtouch_alloc(काष्ठा usbtouch_usb *usbtouch)
अणु
	पूर्णांक ret;

	usbtouch->priv = kदो_स्मृति(माप(काष्ठा mtouch_priv), GFP_KERNEL);
	अगर (!usbtouch->priv)
		वापस -ENOMEM;

	ret = sysfs_create_group(&usbtouch->पूर्णांकerface->dev.kobj,
				 &mtouch_attr_group);
	अगर (ret) अणु
		kमुक्त(usbtouch->priv);
		usbtouch->priv = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtouch_init(काष्ठा usbtouch_usb *usbtouch)
अणु
	पूर्णांक ret, i;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(usbtouch->पूर्णांकerface);

	ret = mtouch_get_fw_revision(usbtouch);
	अगर (ret)
		वापस ret;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
	                      MTOUCHUSB_RESET,
	                      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	                      1, 0, शून्य, 0, USB_CTRL_SET_TIMEOUT);
	dev_dbg(&usbtouch->पूर्णांकerface->dev,
		"%s - usb_control_msg - MTOUCHUSB_RESET - bytes|err: %d\n",
		__func__, ret);
	अगर (ret < 0)
		वापस ret;
	msleep(150);

	क्रम (i = 0; i < 3; i++) अणु
		ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				      MTOUCHUSB_ASYNC_REPORT,
				      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				      1, 1, शून्य, 0, USB_CTRL_SET_TIMEOUT);
		dev_dbg(&usbtouch->पूर्णांकerface->dev,
			"%s - usb_control_msg - MTOUCHUSB_ASYNC_REPORT - bytes|err: %d\n",
			__func__, ret);
		अगर (ret >= 0)
			अवरोध;
		अगर (ret != -EPIPE)
			वापस ret;
	पूर्ण

	/* Default min/max xy are the raw values, override अगर using hw-calib */
	अगर (hwcalib_xy) अणु
		input_set_असल_params(usbtouch->input, ABS_X, 0, 0xffff, 0, 0);
		input_set_असल_params(usbtouch->input, ABS_Y, 0, 0xffff, 0, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtouch_निकास(काष्ठा usbtouch_usb *usbtouch)
अणु
	काष्ठा mtouch_priv *priv = usbtouch->priv;

	sysfs_हटाओ_group(&usbtouch->पूर्णांकerface->dev.kobj, &mtouch_attr_group);
	kमुक्त(priv);
पूर्ण
#पूर्ण_अगर


/*****************************************************************************
 * ITM Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ITM
अटल पूर्णांक iपंचांग_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	पूर्णांक touch;
	/*
	 * ITM devices report invalid x/y data अगर not touched.
	 * अगर the screen was touched beक्रमe but is not touched any more
	 * report touch as 0 with the last valid x/y data once. then stop
	 * reporting data until touched again.
	 */
	dev->press = ((pkt[2] & 0x01) << 7) | (pkt[5] & 0x7F);

	touch = ~pkt[7] & 0x20;
	अगर (!touch) अणु
		अगर (dev->touch) अणु
			dev->touch = 0;
			वापस 1;
		पूर्ण

		वापस 0;
	पूर्ण

	dev->x = ((pkt[0] & 0x1F) << 7) | (pkt[3] & 0x7F);
	dev->y = ((pkt[1] & 0x1F) << 7) | (pkt[4] & 0x7F);
	dev->touch = touch;

	वापस 1;
पूर्ण
#पूर्ण_अगर


/*****************************************************************************
 * eTurboTouch part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ETURBO
#अगर_अघोषित MULTI_PACKET
#घोषणा MULTI_PACKET
#पूर्ण_अगर
अटल पूर्णांक eturbo_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	अचिन्हित पूर्णांक shअगरt;

	/* packets should start with sync */
	अगर (!(pkt[0] & 0x80))
		वापस 0;

	shअगरt = (6 - (pkt[0] & 0x03));
	dev->x = ((pkt[3] << 7) | pkt[4]) >> shअगरt;
	dev->y = ((pkt[1] << 7) | pkt[2]) >> shअगरt;
	dev->touch = (pkt[0] & 0x10) ? 1 : 0;

	वापस 1;
पूर्ण

अटल पूर्णांक eturbo_get_pkt_len(अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	अगर (buf[0] & 0x80)
		वापस 5;
	अगर (buf[0] == 0x01)
		वापस 3;
	वापस 0;
पूर्ण
#पूर्ण_अगर


/*****************************************************************************
 * Gunze part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_GUNZE
अटल पूर्णांक gunze_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	अगर (!(pkt[0] & 0x80) || ((pkt[1] | pkt[2] | pkt[3]) & 0x80))
		वापस 0;

	dev->x = ((pkt[0] & 0x1F) << 7) | (pkt[2] & 0x7F);
	dev->y = ((pkt[1] & 0x1F) << 7) | (pkt[3] & 0x7F);
	dev->touch = pkt[0] & 0x20;

	वापस 1;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * DMC TSC-10/25 Part
 *
 * Documentation about the controller and it's protocol can be found at
 *   http://www.dmccoltd.com/files/controler/tsc10usb_pi_e.pdf
 *   http://www.dmccoltd.com/files/controler/tsc25_usb_e.pdf
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_DMC_TSC10

/* supported data rates. currently using 130 */
#घोषणा TSC10_RATE_POINT	0x50
#घोषणा TSC10_RATE_30		0x40
#घोषणा TSC10_RATE_50		0x41
#घोषणा TSC10_RATE_80		0x42
#घोषणा TSC10_RATE_100		0x43
#घोषणा TSC10_RATE_130		0x44
#घोषणा TSC10_RATE_150		0x45

/* commands */
#घोषणा TSC10_CMD_RESET		0x55
#घोषणा TSC10_CMD_RATE		0x05
#घोषणा TSC10_CMD_DATA1		0x01

अटल पूर्णांक dmc_tsc10_init(काष्ठा usbtouch_usb *usbtouch)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(usbtouch->पूर्णांकerface);
	पूर्णांक ret = -ENOMEM;
	अचिन्हित अक्षर *buf;

	buf = kदो_स्मृति(2, GFP_NOIO);
	अगर (!buf)
		जाओ err_nobuf;
	/* reset */
	buf[0] = buf[1] = 0xFF;
	ret = usb_control_msg(dev, usb_rcvctrlpipe (dev, 0),
	                      TSC10_CMD_RESET,
	                      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	                      0, 0, buf, 2, USB_CTRL_SET_TIMEOUT);
	अगर (ret < 0)
		जाओ err_out;
	अगर (buf[0] != 0x06) अणु
		ret = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* TSC-25 data sheet specअगरies a delay after the RESET command */
	msleep(150);

	/* set coordinate output rate */
	buf[0] = buf[1] = 0xFF;
	ret = usb_control_msg(dev, usb_rcvctrlpipe (dev, 0),
	                      TSC10_CMD_RATE,
	                      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	                      TSC10_RATE_150, 0, buf, 2, USB_CTRL_SET_TIMEOUT);
	अगर (ret < 0)
		जाओ err_out;
	अगर ((buf[0] != 0x06) && (buf[0] != 0x15 || buf[1] != 0x01)) अणु
		ret = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* start sending data */
	ret = usb_control_msg(dev, usb_rcvctrlpipe (dev, 0),
	                      TSC10_CMD_DATA1,
	                      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	                      0, 0, शून्य, 0, USB_CTRL_SET_TIMEOUT);
err_out:
	kमुक्त(buf);
err_nobuf:
	वापस ret;
पूर्ण


अटल पूर्णांक dmc_tsc10_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	dev->x = ((pkt[2] & 0x03) << 8) | pkt[1];
	dev->y = ((pkt[4] & 0x03) << 8) | pkt[3];
	dev->touch = pkt[0] & 0x01;

	वापस 1;
पूर्ण
#पूर्ण_अगर


/*****************************************************************************
 * IRTOUCH Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_IRTOUCH
अटल पूर्णांक irtouch_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	dev->x = (pkt[3] << 8) | pkt[2];
	dev->y = (pkt[5] << 8) | pkt[4];
	dev->touch = (pkt[1] & 0x03) ? 1 : 0;

	वापस 1;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * ET&T TC5UH/TC4UM part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ETT_TC45USB
अटल पूर्णांक tc45usb_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	dev->x = ((pkt[2] & 0x0F) << 8) | pkt[1];
	dev->y = ((pkt[4] & 0x0F) << 8) | pkt[3];
	dev->touch = pkt[0] & 0x01;

	वापस 1;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * IdealTEK URTC1000 Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_IDEALTEK
#अगर_अघोषित MULTI_PACKET
#घोषणा MULTI_PACKET
#पूर्ण_अगर
अटल पूर्णांक idealtek_get_pkt_len(अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	अगर (buf[0] & 0x80)
		वापस 5;
	अगर (buf[0] == 0x01)
		वापस len;
	वापस 0;
पूर्ण

अटल पूर्णांक idealtek_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	चयन (pkt[0] & 0x98) अणु
	हाल 0x88:
		/* touch data in IdealTEK mode */
		dev->x = (pkt[1] << 5) | (pkt[2] >> 2);
		dev->y = (pkt[3] << 5) | (pkt[4] >> 2);
		dev->touch = (pkt[0] & 0x40) ? 1 : 0;
		वापस 1;

	हाल 0x98:
		/* touch data in MT emulation mode */
		dev->x = (pkt[2] << 5) | (pkt[1] >> 2);
		dev->y = (pkt[4] << 5) | (pkt[3] >> 2);
		dev->touch = (pkt[0] & 0x40) ? 1 : 0;
		वापस 1;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * General Touch Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_GENERAL_TOUCH
अटल पूर्णांक general_touch_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	dev->x = (pkt[2] << 8) | pkt[1];
	dev->y = (pkt[4] << 8) | pkt[3];
	dev->press = pkt[5] & 0xff;
	dev->touch = pkt[0] & 0x01;

	वापस 1;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * GoTop Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_GOTOP
अटल पूर्णांक जाओp_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	dev->x = ((pkt[1] & 0x38) << 4) | pkt[2];
	dev->y = ((pkt[1] & 0x07) << 7) | pkt[3];
	dev->touch = pkt[0] & 0x01;

	वापस 1;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * JASTEC Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_JASTEC
अटल पूर्णांक jastec_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	dev->x = ((pkt[0] & 0x3f) << 6) | (pkt[2] & 0x3f);
	dev->y = ((pkt[1] & 0x3f) << 6) | (pkt[3] & 0x3f);
	dev->touch = (pkt[0] & 0x40) >> 6;

	वापस 1;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * Zytronic Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ZYTRONIC
अटल पूर्णांक zytronic_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकerface;

	चयन (pkt[0]) अणु
	हाल 0x3A: /* command response */
		dev_dbg(&पूर्णांकf->dev, "%s: Command response %d\n", __func__, pkt[1]);
		अवरोध;

	हाल 0xC0: /* करोwn */
		dev->x = (pkt[1] & 0x7f) | ((pkt[2] & 0x07) << 7);
		dev->y = (pkt[3] & 0x7f) | ((pkt[4] & 0x07) << 7);
		dev->touch = 1;
		dev_dbg(&पूर्णांकf->dev, "%s: down %d,%d\n", __func__, dev->x, dev->y);
		वापस 1;

	हाल 0x80: /* up */
		dev->x = (pkt[1] & 0x7f) | ((pkt[2] & 0x07) << 7);
		dev->y = (pkt[3] & 0x7f) | ((pkt[4] & 0x07) << 7);
		dev->touch = 0;
		dev_dbg(&पूर्णांकf->dev, "%s: up %d,%d\n", __func__, dev->x, dev->y);
		वापस 1;

	शेष:
		dev_dbg(&पूर्णांकf->dev, "%s: Unknown return %d\n", __func__, pkt[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * NEXIO Part
 */
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_NEXIO

#घोषणा NEXIO_TIMEOUT	5000
#घोषणा NEXIO_बफ_मानE	1024
#घोषणा NEXIO_THRESHOLD	50

काष्ठा nexio_priv अणु
	काष्ठा urb *ack;
	अचिन्हित अक्षर *ack_buf;
पूर्ण;

काष्ठा nexio_touch_packet अणु
	u8	flags;		/* 0xe1 = touch, 0xe1 = release */
	__be16	data_len;	/* total bytes of touch data */
	__be16	x_len;		/* bytes क्रम X axis */
	__be16	y_len;		/* bytes क्रम Y axis */
	u8	data[];
पूर्ण __attribute__ ((packed));

अटल अचिन्हित अक्षर nexio_ack_pkt[2] = अणु 0xaa, 0x02 पूर्ण;
अटल अचिन्हित अक्षर nexio_init_pkt[4] = अणु 0x82, 0x04, 0x0a, 0x0f पूर्ण;

अटल व्योम nexio_ack_complete(काष्ठा urb *urb)
अणु
पूर्ण

अटल पूर्णांक nexio_alloc(काष्ठा usbtouch_usb *usbtouch)
अणु
	काष्ठा nexio_priv *priv;
	पूर्णांक ret = -ENOMEM;

	usbtouch->priv = kदो_स्मृति(माप(काष्ठा nexio_priv), GFP_KERNEL);
	अगर (!usbtouch->priv)
		जाओ out_buf;

	priv = usbtouch->priv;

	priv->ack_buf = kmemdup(nexio_ack_pkt, माप(nexio_ack_pkt),
				GFP_KERNEL);
	अगर (!priv->ack_buf)
		जाओ err_priv;

	priv->ack = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!priv->ack) अणु
		dev_dbg(&usbtouch->पूर्णांकerface->dev,
			"%s - usb_alloc_urb failed: usbtouch->ack\n", __func__);
		जाओ err_ack_buf;
	पूर्ण

	वापस 0;

err_ack_buf:
	kमुक्त(priv->ack_buf);
err_priv:
	kमुक्त(priv);
out_buf:
	वापस ret;
पूर्ण

अटल पूर्णांक nexio_init(काष्ठा usbtouch_usb *usbtouch)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(usbtouch->पूर्णांकerface);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = usbtouch->पूर्णांकerface->cur_altsetting;
	काष्ठा nexio_priv *priv = usbtouch->priv;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक actual_len, i;
	अचिन्हित अक्षर *buf;
	अक्षर *firmware_ver = शून्य, *device_name = शून्य;
	पूर्णांक input_ep = 0, output_ep = 0;

	/* find first input and output endpoपूर्णांक */
	क्रम (i = 0; i < पूर्णांकerface->desc.bNumEndpoपूर्णांकs; i++) अणु
		अगर (!input_ep &&
		    usb_endpoपूर्णांक_dir_in(&पूर्णांकerface->endpoपूर्णांक[i].desc))
			input_ep = पूर्णांकerface->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress;
		अगर (!output_ep &&
		    usb_endpoपूर्णांक_dir_out(&पूर्णांकerface->endpoपूर्णांक[i].desc))
			output_ep = पूर्णांकerface->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress;
	पूर्ण
	अगर (!input_ep || !output_ep)
		वापस -ENXIO;

	buf = kदो_स्मृति(NEXIO_बफ_मानE, GFP_NOIO);
	अगर (!buf)
		जाओ out_buf;

	/* two empty पढ़ोs */
	क्रम (i = 0; i < 2; i++) अणु
		ret = usb_bulk_msg(dev, usb_rcvbulkpipe(dev, input_ep),
				   buf, NEXIO_बफ_मानE, &actual_len,
				   NEXIO_TIMEOUT);
		अगर (ret < 0)
			जाओ out_buf;
	पूर्ण

	/* send init command */
	स_नकल(buf, nexio_init_pkt, माप(nexio_init_pkt));
	ret = usb_bulk_msg(dev, usb_sndbulkpipe(dev, output_ep),
			   buf, माप(nexio_init_pkt), &actual_len,
			   NEXIO_TIMEOUT);
	अगर (ret < 0)
		जाओ out_buf;

	/* पढ़ो replies */
	क्रम (i = 0; i < 3; i++) अणु
		स_रखो(buf, 0, NEXIO_बफ_मानE);
		ret = usb_bulk_msg(dev, usb_rcvbulkpipe(dev, input_ep),
				   buf, NEXIO_बफ_मानE, &actual_len,
				   NEXIO_TIMEOUT);
		अगर (ret < 0 || actual_len < 1 || buf[1] != actual_len)
			जारी;
		चयन (buf[0]) अणु
		हाल 0x83:	/* firmware version */
			अगर (!firmware_ver)
				firmware_ver = kstrdup(&buf[2], GFP_NOIO);
			अवरोध;
		हाल 0x84:	/* device name */
			अगर (!device_name)
				device_name = kstrdup(&buf[2], GFP_NOIO);
			अवरोध;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_INFO "Nexio device: %s, firmware version: %s\n",
	       device_name, firmware_ver);

	kमुक्त(firmware_ver);
	kमुक्त(device_name);

	usb_fill_bulk_urb(priv->ack, dev, usb_sndbulkpipe(dev, output_ep),
			  priv->ack_buf, माप(nexio_ack_pkt),
			  nexio_ack_complete, usbtouch);
	ret = 0;

out_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम nexio_निकास(काष्ठा usbtouch_usb *usbtouch)
अणु
	काष्ठा nexio_priv *priv = usbtouch->priv;

	usb_समाप्त_urb(priv->ack);
	usb_मुक्त_urb(priv->ack);
	kमुक्त(priv->ack_buf);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक nexio_पढ़ो_data(काष्ठा usbtouch_usb *usbtouch, अचिन्हित अक्षर *pkt)
अणु
	काष्ठा device *dev = &usbtouch->पूर्णांकerface->dev;
	काष्ठा nexio_touch_packet *packet = (व्योम *) pkt;
	काष्ठा nexio_priv *priv = usbtouch->priv;
	अचिन्हित पूर्णांक data_len = be16_to_cpu(packet->data_len);
	अचिन्हित पूर्णांक x_len = be16_to_cpu(packet->x_len);
	अचिन्हित पूर्णांक y_len = be16_to_cpu(packet->y_len);
	पूर्णांक x, y, begin_x, begin_y, end_x, end_y, w, h, ret;

	/* got touch data? */
	अगर ((pkt[0] & 0xe0) != 0xe0)
		वापस 0;

	अगर (data_len > 0xff)
		data_len -= 0x100;
	अगर (x_len > 0xff)
		x_len -= 0x80;

	/* send ACK */
	ret = usb_submit_urb(priv->ack, GFP_ATOMIC);
	अगर (ret)
		dev_warn(dev, "Failed to submit ACK URB: %d\n", ret);

	अगर (!usbtouch->type->max_xc) अणु
		usbtouch->type->max_xc = 2 * x_len;
		input_set_असल_params(usbtouch->input, ABS_X,
				     0, usbtouch->type->max_xc, 0, 0);
		usbtouch->type->max_yc = 2 * y_len;
		input_set_असल_params(usbtouch->input, ABS_Y,
				     0, usbtouch->type->max_yc, 0, 0);
	पूर्ण
	/*
	 * The device reports state of IR sensors on X and Y axes.
	 * Each byte represents "darkness" percentage (0-100) of one element.
	 * 17" touchscreen reports only 64 x 52 bytes so the resolution is low.
	 * This also means that there's a limited multi-touch capability but
	 * it's disabled (and untested) here as there's no X driver क्रम that.
	 */
	begin_x = end_x = begin_y = end_y = -1;
	क्रम (x = 0; x < x_len; x++) अणु
		अगर (begin_x == -1 && packet->data[x] > NEXIO_THRESHOLD) अणु
			begin_x = x;
			जारी;
		पूर्ण
		अगर (end_x == -1 && begin_x != -1 && packet->data[x] < NEXIO_THRESHOLD) अणु
			end_x = x - 1;
			क्रम (y = x_len; y < data_len; y++) अणु
				अगर (begin_y == -1 && packet->data[y] > NEXIO_THRESHOLD) अणु
					begin_y = y - x_len;
					जारी;
				पूर्ण
				अगर (end_y == -1 &&
				    begin_y != -1 && packet->data[y] < NEXIO_THRESHOLD) अणु
					end_y = y - 1 - x_len;
					w = end_x - begin_x;
					h = end_y - begin_y;
#अगर 0
					/* multi-touch */
					input_report_असल(usbtouch->input,
						    ABS_MT_TOUCH_MAJOR, max(w,h));
					input_report_असल(usbtouch->input,
						    ABS_MT_TOUCH_MINOR, min(x,h));
					input_report_असल(usbtouch->input,
						    ABS_MT_POSITION_X, 2*begin_x+w);
					input_report_असल(usbtouch->input,
						    ABS_MT_POSITION_Y, 2*begin_y+h);
					input_report_असल(usbtouch->input,
						    ABS_MT_ORIENTATION, w > h);
					input_mt_sync(usbtouch->input);
#पूर्ण_अगर
					/* single touch */
					usbtouch->x = 2 * begin_x + w;
					usbtouch->y = 2 * begin_y + h;
					usbtouch->touch = packet->flags & 0x01;
					begin_y = end_y = -1;
					वापस 1;
				पूर्ण
			पूर्ण
			begin_x = end_x = -1;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर


/*****************************************************************************
 * ELO part
 */

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ELO

अटल पूर्णांक elo_पढ़ो_data(काष्ठा usbtouch_usb *dev, अचिन्हित अक्षर *pkt)
अणु
	dev->x = (pkt[3] << 8) | pkt[2];
	dev->y = (pkt[5] << 8) | pkt[4];
	dev->touch = pkt[6] > 0;
	dev->press = pkt[6];

	वापस 1;
पूर्ण
#पूर्ण_अगर


/*****************************************************************************
 * the dअगरferent device descriptors
 */
#अगर_घोषित MULTI_PACKET
अटल व्योम usbtouch_process_multi(काष्ठा usbtouch_usb *usbtouch,
				   अचिन्हित अक्षर *pkt, पूर्णांक len);
#पूर्ण_अगर

अटल काष्ठा usbtouch_device_info usbtouch_dev_info[] = अणु
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ELO
	[DEVTYPE_ELO] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.max_press	= 0xff,
		.rept_size	= 8,
		.पढ़ो_data	= elo_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_EGALAX
	[DEVTYPE_EGALAX] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x07ff,
		.min_yc		= 0x0,
		.max_yc		= 0x07ff,
		.rept_size	= 16,
		.process_pkt	= usbtouch_process_multi,
		.get_pkt_len	= egalax_get_pkt_len,
		.पढ़ो_data	= egalax_पढ़ो_data,
		.init		= egalax_init,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_PANJIT
	[DEVTYPE_PANJIT] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.rept_size	= 8,
		.पढ़ो_data	= panjit_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_3M
	[DEVTYPE_3M] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x4000,
		.min_yc		= 0x0,
		.max_yc		= 0x4000,
		.rept_size	= 11,
		.पढ़ो_data	= mtouch_पढ़ो_data,
		.alloc		= mtouch_alloc,
		.init		= mtouch_init,
		.निकास		= mtouch_निकास,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ITM
	[DEVTYPE_ITM] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.max_press	= 0xff,
		.rept_size	= 8,
		.पढ़ो_data	= iपंचांग_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ETURBO
	[DEVTYPE_ETURBO] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x07ff,
		.min_yc		= 0x0,
		.max_yc		= 0x07ff,
		.rept_size	= 8,
		.process_pkt	= usbtouch_process_multi,
		.get_pkt_len	= eturbo_get_pkt_len,
		.पढ़ो_data	= eturbo_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_GUNZE
	[DEVTYPE_GUNZE] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.rept_size	= 4,
		.पढ़ो_data	= gunze_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_DMC_TSC10
	[DEVTYPE_DMC_TSC10] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x03ff,
		.min_yc		= 0x0,
		.max_yc		= 0x03ff,
		.rept_size	= 5,
		.init		= dmc_tsc10_init,
		.पढ़ो_data	= dmc_tsc10_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_IRTOUCH
	[DEVTYPE_IRTOUCH] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.rept_size	= 8,
		.पढ़ो_data	= irtouch_पढ़ो_data,
	पूर्ण,

	[DEVTYPE_IRTOUCH_HIRES] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x7fff,
		.min_yc		= 0x0,
		.max_yc		= 0x7fff,
		.rept_size	= 8,
		.पढ़ो_data	= irtouch_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_IDEALTEK
	[DEVTYPE_IDEALTEK] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.rept_size	= 8,
		.process_pkt	= usbtouch_process_multi,
		.get_pkt_len	= idealtek_get_pkt_len,
		.पढ़ो_data	= idealtek_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_GENERAL_TOUCH
	[DEVTYPE_GENERAL_TOUCH] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x7fff,
		.min_yc		= 0x0,
		.max_yc		= 0x7fff,
		.rept_size	= 7,
		.पढ़ो_data	= general_touch_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_GOTOP
	[DEVTYPE_GOTOP] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x03ff,
		.min_yc		= 0x0,
		.max_yc		= 0x03ff,
		.rept_size	= 4,
		.पढ़ो_data	= जाओp_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_JASTEC
	[DEVTYPE_JASTEC] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.rept_size	= 4,
		.पढ़ो_data	= jastec_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_E2I
	[DEVTYPE_E2I] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x7fff,
		.min_yc		= 0x0,
		.max_yc		= 0x7fff,
		.rept_size	= 6,
		.init		= e2i_init,
		.पढ़ो_data	= e2i_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ZYTRONIC
	[DEVTYPE_ZYTRONIC] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x03ff,
		.min_yc		= 0x0,
		.max_yc		= 0x03ff,
		.rept_size	= 5,
		.पढ़ो_data	= zytronic_पढ़ो_data,
		.irq_always     = true,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_ETT_TC45USB
	[DEVTYPE_TC45USB] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x0fff,
		.min_yc		= 0x0,
		.max_yc		= 0x0fff,
		.rept_size	= 5,
		.पढ़ो_data	= tc45usb_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर

#अगर_घोषित CONFIG_TOUCHSCREEN_USB_NEXIO
	[DEVTYPE_NEXIO] = अणु
		.rept_size	= 1024,
		.irq_always	= true,
		.पढ़ो_data	= nexio_पढ़ो_data,
		.alloc		= nexio_alloc,
		.init		= nexio_init,
		.निकास		= nexio_निकास,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TOUCHSCREEN_USB_EASYTOUCH
	[DEVTYPE_ETOUCH] = अणु
		.min_xc		= 0x0,
		.max_xc		= 0x07ff,
		.min_yc		= 0x0,
		.max_yc		= 0x07ff,
		.rept_size	= 16,
		.process_pkt	= usbtouch_process_multi,
		.get_pkt_len	= etouch_get_pkt_len,
		.पढ़ो_data	= etouch_पढ़ो_data,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;


/*****************************************************************************
 * Generic Part
 */
अटल व्योम usbtouch_process_pkt(काष्ठा usbtouch_usb *usbtouch,
                                 अचिन्हित अक्षर *pkt, पूर्णांक len)
अणु
	काष्ठा usbtouch_device_info *type = usbtouch->type;

	अगर (!type->पढ़ो_data(usbtouch, pkt))
			वापस;

	input_report_key(usbtouch->input, BTN_TOUCH, usbtouch->touch);

	अगर (swap_xy) अणु
		input_report_असल(usbtouch->input, ABS_X, usbtouch->y);
		input_report_असल(usbtouch->input, ABS_Y, usbtouch->x);
	पूर्ण अन्यथा अणु
		input_report_असल(usbtouch->input, ABS_X, usbtouch->x);
		input_report_असल(usbtouch->input, ABS_Y, usbtouch->y);
	पूर्ण
	अगर (type->max_press)
		input_report_असल(usbtouch->input, ABS_PRESSURE, usbtouch->press);
	input_sync(usbtouch->input);
पूर्ण


#अगर_घोषित MULTI_PACKET
अटल व्योम usbtouch_process_multi(काष्ठा usbtouch_usb *usbtouch,
                                   अचिन्हित अक्षर *pkt, पूर्णांक len)
अणु
	अचिन्हित अक्षर *buffer;
	पूर्णांक pkt_len, pos, buf_len, पंचांगp;

	/* process buffer */
	अगर (unlikely(usbtouch->buf_len)) अणु
		/* try to get size */
		pkt_len = usbtouch->type->get_pkt_len(
				usbtouch->buffer, usbtouch->buf_len);

		/* drop? */
		अगर (unlikely(!pkt_len))
			जाओ out_flush_buf;

		/* need to append -pkt_len bytes beक्रमe able to get size */
		अगर (unlikely(pkt_len < 0)) अणु
			पूर्णांक append = -pkt_len;
			अगर (unlikely(append > len))
			       append = len;
			अगर (usbtouch->buf_len + append >= usbtouch->type->rept_size)
				जाओ out_flush_buf;
			स_नकल(usbtouch->buffer + usbtouch->buf_len, pkt, append);
			usbtouch->buf_len += append;

			pkt_len = usbtouch->type->get_pkt_len(
					usbtouch->buffer, usbtouch->buf_len);
			अगर (pkt_len < 0)
				वापस;
		पूर्ण

		/* append */
		पंचांगp = pkt_len - usbtouch->buf_len;
		अगर (usbtouch->buf_len + पंचांगp >= usbtouch->type->rept_size)
			जाओ out_flush_buf;
		स_नकल(usbtouch->buffer + usbtouch->buf_len, pkt, पंचांगp);
		usbtouch_process_pkt(usbtouch, usbtouch->buffer, pkt_len);

		buffer = pkt + पंचांगp;
		buf_len = len - पंचांगp;
	पूर्ण अन्यथा अणु
		buffer = pkt;
		buf_len = len;
	पूर्ण

	/* loop over the received packet, process */
	pos = 0;
	जबतक (pos < buf_len) अणु
		/* get packet len */
		pkt_len = usbtouch->type->get_pkt_len(buffer + pos,
							buf_len - pos);

		/* unknown packet: skip one byte */
		अगर (unlikely(!pkt_len)) अणु
			pos++;
			जारी;
		पूर्ण

		/* full packet: process */
		अगर (likely((pkt_len > 0) && (pkt_len <= buf_len - pos))) अणु
			usbtouch_process_pkt(usbtouch, buffer + pos, pkt_len);
		पूर्ण अन्यथा अणु
			/* incomplete packet: save in buffer */
			स_नकल(usbtouch->buffer, buffer + pos, buf_len - pos);
			usbtouch->buf_len = buf_len - pos;
			वापस;
		पूर्ण
		pos += pkt_len;
	पूर्ण

out_flush_buf:
	usbtouch->buf_len = 0;
	वापस;
पूर्ण
#पूर्ण_अगर


अटल व्योम usbtouch_irq(काष्ठा urb *urb)
अणु
	काष्ठा usbtouch_usb *usbtouch = urb->context;
	काष्ठा device *dev = &usbtouch->पूर्णांकerface->dev;
	पूर्णांक retval;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ETIME:
		/* this urb is timing out */
		dev_dbg(dev,
			"%s - urb timed out - was the device unplugged?\n",
			__func__);
		वापस;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -EPIPE:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shutting down with status: %d\n",
			__func__, urb->status);
		वापस;
	शेष:
		dev_dbg(dev, "%s - nonzero urb status received: %d\n",
			__func__, urb->status);
		जाओ निकास;
	पूर्ण

	usbtouch->type->process_pkt(usbtouch, usbtouch->data, urb->actual_length);

निकास:
	usb_mark_last_busy(पूर्णांकerface_to_usbdev(usbtouch->पूर्णांकerface));
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(dev, "%s - usb_submit_urb failed with result: %d\n",
			__func__, retval);
पूर्ण

अटल पूर्णांक usbtouch_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा usbtouch_usb *usbtouch = input_get_drvdata(input);
	पूर्णांक r;

	usbtouch->irq->dev = पूर्णांकerface_to_usbdev(usbtouch->पूर्णांकerface);

	r = usb_स्वतःpm_get_पूर्णांकerface(usbtouch->पूर्णांकerface) ? -EIO : 0;
	अगर (r < 0)
		जाओ out;

	mutex_lock(&usbtouch->pm_mutex);
	अगर (!usbtouch->type->irq_always) अणु
		अगर (usb_submit_urb(usbtouch->irq, GFP_KERNEL)) अणु
			r = -EIO;
			जाओ out_put;
		पूर्ण
	पूर्ण

	usbtouch->पूर्णांकerface->needs_remote_wakeup = 1;
	usbtouch->is_खोलो = true;
out_put:
	mutex_unlock(&usbtouch->pm_mutex);
	usb_स्वतःpm_put_पूर्णांकerface(usbtouch->पूर्णांकerface);
out:
	वापस r;
पूर्ण

अटल व्योम usbtouch_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा usbtouch_usb *usbtouch = input_get_drvdata(input);
	पूर्णांक r;

	mutex_lock(&usbtouch->pm_mutex);
	अगर (!usbtouch->type->irq_always)
		usb_समाप्त_urb(usbtouch->irq);
	usbtouch->is_खोलो = false;
	mutex_unlock(&usbtouch->pm_mutex);

	r = usb_स्वतःpm_get_पूर्णांकerface(usbtouch->पूर्णांकerface);
	usbtouch->पूर्णांकerface->needs_remote_wakeup = 0;
	अगर (!r)
		usb_स्वतःpm_put_पूर्णांकerface(usbtouch->पूर्णांकerface);
पूर्ण

अटल पूर्णांक usbtouch_suspend
(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usbtouch_usb *usbtouch = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_समाप्त_urb(usbtouch->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक usbtouch_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbtouch_usb *usbtouch = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक result = 0;

	mutex_lock(&usbtouch->pm_mutex);
	अगर (usbtouch->is_खोलो || usbtouch->type->irq_always)
		result = usb_submit_urb(usbtouch->irq, GFP_NOIO);
	mutex_unlock(&usbtouch->pm_mutex);

	वापस result;
पूर्ण

अटल पूर्णांक usbtouch_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbtouch_usb *usbtouch = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक err = 0;

	/* reinit the device */
	अगर (usbtouch->type->init) अणु
		err = usbtouch->type->init(usbtouch);
		अगर (err) अणु
			dev_dbg(&पूर्णांकf->dev,
				"%s - type->init() failed, err: %d\n",
				__func__, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* restart IO अगर needed */
	mutex_lock(&usbtouch->pm_mutex);
	अगर (usbtouch->is_खोलो)
		err = usb_submit_urb(usbtouch->irq, GFP_NOIO);
	mutex_unlock(&usbtouch->pm_mutex);

	वापस err;
पूर्ण

अटल व्योम usbtouch_मुक्त_buffers(काष्ठा usb_device *udev,
				  काष्ठा usbtouch_usb *usbtouch)
अणु
	usb_मुक्त_coherent(udev, usbtouch->data_size,
			  usbtouch->data, usbtouch->data_dma);
	kमुक्त(usbtouch->buffer);
पूर्ण

अटल काष्ठा usb_endpoपूर्णांक_descriptor *
usbtouch_get_input_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < पूर्णांकerface->desc.bNumEndpoपूर्णांकs; i++)
		अगर (usb_endpoपूर्णांक_dir_in(&पूर्णांकerface->endpoपूर्णांक[i].desc))
			वापस &पूर्णांकerface->endpoपूर्णांक[i].desc;

	वापस शून्य;
पूर्ण

अटल पूर्णांक usbtouch_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usbtouch_usb *usbtouch;
	काष्ठा input_dev *input_dev;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usbtouch_device_info *type;
	पूर्णांक err = -ENOMEM;

	/* some devices are ignored */
	अगर (id->driver_info == DEVTYPE_IGNORE)
		वापस -ENODEV;

	endpoपूर्णांक = usbtouch_get_input_endpoपूर्णांक(पूर्णांकf->cur_altsetting);
	अगर (!endpoपूर्णांक)
		वापस -ENXIO;

	usbtouch = kzalloc(माप(काष्ठा usbtouch_usb), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!usbtouch || !input_dev)
		जाओ out_मुक्त;

	mutex_init(&usbtouch->pm_mutex);

	type = &usbtouch_dev_info[id->driver_info];
	usbtouch->type = type;
	अगर (!type->process_pkt)
		type->process_pkt = usbtouch_process_pkt;

	usbtouch->data_size = type->rept_size;
	अगर (type->get_pkt_len) अणु
		/*
		 * When dealing with variable-length packets we should
		 * not request more than wMaxPacketSize bytes at once
		 * as we करो not know अगर there is more data coming or
		 * we filled exactly wMaxPacketSize bytes and there is
		 * nothing अन्यथा.
		 */
		usbtouch->data_size = min(usbtouch->data_size,
					  usb_endpoपूर्णांक_maxp(endpoपूर्णांक));
	पूर्ण

	usbtouch->data = usb_alloc_coherent(udev, usbtouch->data_size,
					    GFP_KERNEL, &usbtouch->data_dma);
	अगर (!usbtouch->data)
		जाओ out_मुक्त;

	अगर (type->get_pkt_len) अणु
		usbtouch->buffer = kदो_स्मृति(type->rept_size, GFP_KERNEL);
		अगर (!usbtouch->buffer)
			जाओ out_मुक्त_buffers;
	पूर्ण

	usbtouch->irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!usbtouch->irq) अणु
		dev_dbg(&पूर्णांकf->dev,
			"%s - usb_alloc_urb failed: usbtouch->irq\n", __func__);
		जाओ out_मुक्त_buffers;
	पूर्ण

	usbtouch->पूर्णांकerface = पूर्णांकf;
	usbtouch->input = input_dev;

	अगर (udev->manufacturer)
		strlcpy(usbtouch->name, udev->manufacturer, माप(usbtouch->name));

	अगर (udev->product) अणु
		अगर (udev->manufacturer)
			strlcat(usbtouch->name, " ", माप(usbtouch->name));
		strlcat(usbtouch->name, udev->product, माप(usbtouch->name));
	पूर्ण

	अगर (!म_माप(usbtouch->name))
		snम_लिखो(usbtouch->name, माप(usbtouch->name),
			"USB Touchscreen %04x:%04x",
			 le16_to_cpu(udev->descriptor.idVenकरोr),
			 le16_to_cpu(udev->descriptor.idProduct));

	usb_make_path(udev, usbtouch->phys, माप(usbtouch->phys));
	strlcat(usbtouch->phys, "/input0", माप(usbtouch->phys));

	input_dev->name = usbtouch->name;
	input_dev->phys = usbtouch->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकf->dev;

	input_set_drvdata(input_dev, usbtouch);

	input_dev->खोलो = usbtouch_खोलो;
	input_dev->बंद = usbtouch_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X, type->min_xc, type->max_xc, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, type->min_yc, type->max_yc, 0, 0);
	अगर (type->max_press)
		input_set_असल_params(input_dev, ABS_PRESSURE, type->min_press,
		                     type->max_press, 0, 0);

	अगर (usb_endpoपूर्णांक_type(endpoपूर्णांक) == USB_ENDPOINT_XFER_INT)
		usb_fill_पूर्णांक_urb(usbtouch->irq, udev,
			 usb_rcvपूर्णांकpipe(udev, endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 usbtouch->data, usbtouch->data_size,
			 usbtouch_irq, usbtouch, endpoपूर्णांक->bInterval);
	अन्यथा
		usb_fill_bulk_urb(usbtouch->irq, udev,
			 usb_rcvbulkpipe(udev, endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 usbtouch->data, usbtouch->data_size,
			 usbtouch_irq, usbtouch);

	usbtouch->irq->dev = udev;
	usbtouch->irq->transfer_dma = usbtouch->data_dma;
	usbtouch->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* device specअगरic allocations */
	अगर (type->alloc) अणु
		err = type->alloc(usbtouch);
		अगर (err) अणु
			dev_dbg(&पूर्णांकf->dev,
				"%s - type->alloc() failed, err: %d\n",
				__func__, err);
			जाओ out_मुक्त_urb;
		पूर्ण
	पूर्ण

	/* device specअगरic initialisation*/
	अगर (type->init) अणु
		err = type->init(usbtouch);
		अगर (err) अणु
			dev_dbg(&पूर्णांकf->dev,
				"%s - type->init() failed, err: %d\n",
				__func__, err);
			जाओ out_करो_निकास;
		पूर्ण
	पूर्ण

	err = input_रेजिस्टर_device(usbtouch->input);
	अगर (err) अणु
		dev_dbg(&पूर्णांकf->dev,
			"%s - input_register_device failed, err: %d\n",
			__func__, err);
		जाओ out_करो_निकास;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, usbtouch);

	अगर (usbtouch->type->irq_always) अणु
		/* this can't fail */
		usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
		err = usb_submit_urb(usbtouch->irq, GFP_KERNEL);
		अगर (err) अणु
			usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);
			dev_err(&पूर्णांकf->dev,
				"%s - usb_submit_urb failed with result: %d\n",
				__func__, err);
			जाओ out_unरेजिस्टर_input;
		पूर्ण
	पूर्ण

	वापस 0;

out_unरेजिस्टर_input:
	input_unरेजिस्टर_device(input_dev);
	input_dev = शून्य;
out_करो_निकास:
	अगर (type->निकास)
		type->निकास(usbtouch);
out_मुक्त_urb:
	usb_मुक्त_urb(usbtouch->irq);
out_मुक्त_buffers:
	usbtouch_मुक्त_buffers(udev, usbtouch);
out_मुक्त:
	input_मुक्त_device(input_dev);
	kमुक्त(usbtouch);
	वापस err;
पूर्ण

अटल व्योम usbtouch_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbtouch_usb *usbtouch = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!usbtouch)
		वापस;

	dev_dbg(&पूर्णांकf->dev,
		"%s - usbtouch is initialized, cleaning up\n", __func__);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	/* this will stop IO via बंद */
	input_unरेजिस्टर_device(usbtouch->input);
	usb_मुक्त_urb(usbtouch->irq);
	अगर (usbtouch->type->निकास)
		usbtouch->type->निकास(usbtouch);
	usbtouch_मुक्त_buffers(पूर्णांकerface_to_usbdev(पूर्णांकf), usbtouch);
	kमुक्त(usbtouch);
पूर्ण

MODULE_DEVICE_TABLE(usb, usbtouch_devices);

अटल काष्ठा usb_driver usbtouch_driver = अणु
	.name		= "usbtouchscreen",
	.probe		= usbtouch_probe,
	.disconnect	= usbtouch_disconnect,
	.suspend	= usbtouch_suspend,
	.resume		= usbtouch_resume,
	.reset_resume	= usbtouch_reset_resume,
	.id_table	= usbtouch_devices,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(usbtouch_driver);

MODULE_AUTHOR("Daniel Ritz <daniel.ritz@gmx.ch>");
MODULE_DESCRIPTION("USB Touchscreen Driver");
MODULE_LICENSE("GPL");

MODULE_ALIAS("touchkitusb");
MODULE_ALIAS("itmtouch");
MODULE_ALIAS("mtouchusb");
