<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Apple USB BCM5974 (Macbook Air and Penryn Macbook Pro) multitouch driver
 *
 * Copyright (C) 2008	   Henrik Rydberg (rydberg@euromail.se)
 * Copyright (C) 2015      John Horan (knasher@gmail.com)
 *
 * The USB initialization and package decoding was made by
 * Scott Shawcroft as part of the touchd user-space driver project:
 * Copyright (C) 2008	   Scott Shawcroft (scott.shawcroft@gmail.com)
 *
 * The BCM5974 driver is based on the appletouch driver:
 * Copyright (C) 2001-2004 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2005      Johannes Berg (johannes@sipsolutions.net)
 * Copyright (C) 2005	   Stelian Pop (stelian@popies.net)
 * Copyright (C) 2005	   Frank Arnold (frank@scirocco-5v-turbo.de)
 * Copyright (C) 2005	   Peter Osterlund (petero2@telia.com)
 * Copyright (C) 2005	   Michael Hanselmann (linux-kernel@hansmi.ch)
 * Copyright (C) 2006	   Nicolas Boichat (nicolas@boichat.ch)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/mutex.h>
#समावेश <linux/input/mt.h>

#घोषणा USB_VENDOR_ID_APPLE		0x05ac

/* MacbookAir, aka wellspring */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING_ANSI	0x0223
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING_ISO	0x0224
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING_JIS	0x0225
/* MacbookProPenryn, aka wellspring2 */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING2_ANSI	0x0230
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING2_ISO	0x0231
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING2_JIS	0x0232
/* Macbook5,1 (unibody), aka wellspring3 */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING3_ANSI	0x0236
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING3_ISO	0x0237
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING3_JIS	0x0238
/* MacbookAir3,2 (unibody), aka wellspring5 */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING4_ANSI	0x023f
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING4_ISO	0x0240
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING4_JIS	0x0241
/* MacbookAir3,1 (unibody), aka wellspring4 */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING4A_ANSI	0x0242
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING4A_ISO	0x0243
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING4A_JIS	0x0244
/* Macbook8 (unibody, March 2011) */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING5_ANSI	0x0245
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING5_ISO	0x0246
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING5_JIS	0x0247
/* MacbookAir4,1 (unibody, July 2011) */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING6A_ANSI	0x0249
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING6A_ISO	0x024a
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING6A_JIS	0x024b
/* MacbookAir4,2 (unibody, July 2011) */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING6_ANSI	0x024c
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING6_ISO	0x024d
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING6_JIS	0x024e
/* Macbook8,2 (unibody) */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING5A_ANSI	0x0252
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING5A_ISO	0x0253
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING5A_JIS	0x0254
/* MacbookPro10,1 (unibody, June 2012) */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING7_ANSI	0x0262
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING7_ISO	0x0263
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING7_JIS	0x0264
/* MacbookPro10,2 (unibody, October 2012) */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING7A_ANSI	0x0259
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING7A_ISO	0x025a
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING7A_JIS	0x025b
/* MacbookAir6,2 (unibody, June 2013) */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING8_ANSI	0x0290
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING8_ISO	0x0291
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING8_JIS	0x0292
/* MacbookPro12,1 (2015) */
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING9_ANSI	0x0272
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING9_ISO	0x0273
#घोषणा USB_DEVICE_ID_APPLE_WELLSPRING9_JIS	0x0274

#घोषणा BCM5974_DEVICE(prod) अणु					\
	.match_flags = (USB_DEVICE_ID_MATCH_DEVICE |		\
			USB_DEVICE_ID_MATCH_INT_CLASS |		\
			USB_DEVICE_ID_MATCH_INT_PROTOCOL),	\
	.idVenकरोr = USB_VENDOR_ID_APPLE,			\
	.idProduct = (prod),					\
	.bInterfaceClass = USB_INTERFACE_CLASS_HID,		\
	.bInterfaceProtocol = USB_INTERFACE_PROTOCOL_MOUSE	\
पूर्ण

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id bcm5974_table[] = अणु
	/* MacbookAir1.1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING_JIS),
	/* MacbookProPenryn */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING2_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING2_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING2_JIS),
	/* Macbook5,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING3_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING3_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING3_JIS),
	/* MacbookAir3,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING4_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING4_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING4_JIS),
	/* MacbookAir3,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING4A_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING4A_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING4A_JIS),
	/* MacbookPro8 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING5_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING5_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING5_JIS),
	/* MacbookAir4,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING6A_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING6A_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING6A_JIS),
	/* MacbookAir4,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING6_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING6_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING6_JIS),
	/* MacbookPro8,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING5A_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING5A_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING5A_JIS),
	/* MacbookPro10,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING7_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING7_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING7_JIS),
	/* MacbookPro10,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING7A_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING7A_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING7A_JIS),
	/* MacbookAir6,2 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING8_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING8_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING8_JIS),
	/* MacbookPro12,1 */
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING9_ANSI),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING9_ISO),
	BCM5974_DEVICE(USB_DEVICE_ID_APPLE_WELLSPRING9_JIS),
	/* Terminating entry */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, bcm5974_table);

MODULE_AUTHOR("Henrik Rydberg");
MODULE_DESCRIPTION("Apple USB BCM5974 multitouch driver");
MODULE_LICENSE("GPL");

#घोषणा dprपूर्णांकk(level, क्रमmat, a...)\
	अणु अगर (debug >= level) prपूर्णांकk(KERN_DEBUG क्रमmat, ##a); पूर्ण

अटल पूर्णांक debug = 1;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Activate debugging output");

/* button data काष्ठाure */
काष्ठा bt_data अणु
	u8 unknown1;		/* स्थिरant */
	u8 button;		/* left button */
	u8 rel_x;		/* relative x coordinate */
	u8 rel_y;		/* relative y coordinate */
पूर्ण;

/* trackpad header types */
क्रमागत tp_type अणु
	TYPE1,			/* plain trackpad */
	TYPE2,			/* button पूर्णांकegrated in trackpad */
	TYPE3,			/* additional header fields since June 2013 */
	TYPE4			/* additional header field क्रम pressure data */
पूर्ण;

/* trackpad finger data offsets, le16-aligned */
#घोषणा HEADER_TYPE1		(13 * माप(__le16))
#घोषणा HEADER_TYPE2		(15 * माप(__le16))
#घोषणा HEADER_TYPE3		(19 * माप(__le16))
#घोषणा HEADER_TYPE4		(23 * माप(__le16))

/* trackpad button data offsets */
#घोषणा BUTTON_TYPE1		0
#घोषणा BUTTON_TYPE2		15
#घोषणा BUTTON_TYPE3		23
#घोषणा BUTTON_TYPE4		31

/* list of device capability bits */
#घोषणा HAS_INTEGRATED_BUTTON	1

/* trackpad finger data block size */
#घोषणा FSIZE_TYPE1		(14 * माप(__le16))
#घोषणा FSIZE_TYPE2		(14 * माप(__le16))
#घोषणा FSIZE_TYPE3		(14 * माप(__le16))
#घोषणा FSIZE_TYPE4		(15 * माप(__le16))

/* offset from header to finger काष्ठा */
#घोषणा DELTA_TYPE1		(0 * माप(__le16))
#घोषणा DELTA_TYPE2		(0 * माप(__le16))
#घोषणा DELTA_TYPE3		(0 * माप(__le16))
#घोषणा DELTA_TYPE4		(1 * माप(__le16))

/* usb control message mode चयन data */
#घोषणा USBMSG_TYPE1		8, 0x300, 0, 0, 0x1, 0x8
#घोषणा USBMSG_TYPE2		8, 0x300, 0, 0, 0x1, 0x8
#घोषणा USBMSG_TYPE3		8, 0x300, 0, 0, 0x1, 0x8
#घोषणा USBMSG_TYPE4		2, 0x302, 2, 1, 0x1, 0x0

/* Wellspring initialization स्थिरants */
#घोषणा BCM5974_WELLSPRING_MODE_READ_REQUEST_ID		1
#घोषणा BCM5974_WELLSPRING_MODE_WRITE_REQUEST_ID	9

/* trackpad finger काष्ठाure, le16-aligned */
काष्ठा tp_finger अणु
	__le16 origin;		/* zero when चयनing track finger */
	__le16 असल_x;		/* असलolute x coodinate */
	__le16 असल_y;		/* असलolute y coodinate */
	__le16 rel_x;		/* relative x coodinate */
	__le16 rel_y;		/* relative y coodinate */
	__le16 tool_major;	/* tool area, major axis */
	__le16 tool_minor;	/* tool area, minor axis */
	__le16 orientation;	/* 16384 when poपूर्णांक, अन्यथा 15 bit angle */
	__le16 touch_major;	/* touch area, major axis */
	__le16 touch_minor;	/* touch area, minor axis */
	__le16 unused[2];	/* zeros */
	__le16 pressure;	/* pressure on क्रमcetouch touchpad */
	__le16 multi;		/* one finger: varies, more fingers: स्थिरant */
पूर्ण __attribute__((packed,aligned(2)));

/* trackpad finger data size, empirically at least ten fingers */
#घोषणा MAX_FINGERS		16
#घोषणा MAX_FINGER_ORIENTATION	16384

/* device-specअगरic parameters */
काष्ठा bcm5974_param अणु
	पूर्णांक snratio;		/* संकेत-to-noise ratio */
	पूर्णांक min;		/* device minimum पढ़ोing */
	पूर्णांक max;		/* device maximum पढ़ोing */
पूर्ण;

/* device-specअगरic configuration */
काष्ठा bcm5974_config अणु
	पूर्णांक ansi, iso, jis;	/* the product id of this device */
	पूर्णांक caps;		/* device capability biपंचांगask */
	पूर्णांक bt_ep;		/* the endpoपूर्णांक of the button पूर्णांकerface */
	पूर्णांक bt_datalen;		/* data length of the button पूर्णांकerface */
	पूर्णांक tp_ep;		/* the endpoपूर्णांक of the trackpad पूर्णांकerface */
	क्रमागत tp_type tp_type;	/* type of trackpad पूर्णांकerface */
	पूर्णांक tp_header;		/* bytes in header block */
	पूर्णांक tp_datalen;		/* data length of the trackpad पूर्णांकerface */
	पूर्णांक tp_button;		/* offset to button data */
	पूर्णांक tp_fsize;		/* bytes in single finger block */
	पूर्णांक tp_delta;		/* offset from header to finger काष्ठा */
	पूर्णांक um_size;		/* usb control message length */
	पूर्णांक um_req_val;		/* usb control message value */
	पूर्णांक um_req_idx;		/* usb control message index */
	पूर्णांक um_चयन_idx;	/* usb control message mode चयन index */
	पूर्णांक um_चयन_on;	/* usb control message mode चयन on */
	पूर्णांक um_चयन_off;	/* usb control message mode चयन off */
	काष्ठा bcm5974_param p;	/* finger pressure limits */
	काष्ठा bcm5974_param w;	/* finger width limits */
	काष्ठा bcm5974_param x;	/* horizontal limits */
	काष्ठा bcm5974_param y;	/* vertical limits */
	काष्ठा bcm5974_param o;	/* orientation limits */
पूर्ण;

/* logical device काष्ठाure */
काष्ठा bcm5974 अणु
	अक्षर phys[64];
	काष्ठा usb_device *udev;	/* usb device */
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;	/* our पूर्णांकerface */
	काष्ठा input_dev *input;	/* input dev */
	काष्ठा bcm5974_config cfg;	/* device configuration */
	काष्ठा mutex pm_mutex;		/* serialize access to खोलो/suspend */
	पूर्णांक खोलोed;			/* 1: खोलोed, 0: बंदd */
	काष्ठा urb *bt_urb;		/* button usb request block */
	काष्ठा bt_data *bt_data;	/* button transferred data */
	काष्ठा urb *tp_urb;		/* trackpad usb request block */
	u8 *tp_data;			/* trackpad transferred data */
	स्थिर काष्ठा tp_finger *index[MAX_FINGERS];	/* finger index data */
	काष्ठा input_mt_pos pos[MAX_FINGERS];		/* position array */
	पूर्णांक slots[MAX_FINGERS];				/* slot assignments */
पूर्ण;

/* trackpad finger block data, le16-aligned */
अटल स्थिर काष्ठा tp_finger *get_tp_finger(स्थिर काष्ठा bcm5974 *dev, पूर्णांक i)
अणु
	स्थिर काष्ठा bcm5974_config *c = &dev->cfg;
	u8 *f_base = dev->tp_data + c->tp_header + c->tp_delta;

	वापस (स्थिर काष्ठा tp_finger *)(f_base + i * c->tp_fsize);
पूर्ण

#घोषणा DATAFORMAT(type)				\
	type,						\
	HEADER_##type,					\
	HEADER_##type + (MAX_FINGERS) * (FSIZE_##type),	\
	BUTTON_##type,					\
	FSIZE_##type,					\
	DELTA_##type,					\
	USBMSG_##type

/* logical संकेत quality */
#घोषणा SN_PRESSURE	45		/* pressure संकेत-to-noise ratio */
#घोषणा SN_WIDTH	25		/* width संकेत-to-noise ratio */
#घोषणा SN_COORD	250		/* coordinate संकेत-to-noise ratio */
#घोषणा SN_ORIENT	10		/* orientation संकेत-to-noise ratio */

/* device स्थिरants */
अटल स्थिर काष्ठा bcm5974_config bcm5974_config_table[] = अणु
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING_JIS,
		0,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE1),
		अणु SN_PRESSURE, 0, 256 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4824, 5342 पूर्ण,
		अणु SN_COORD, -172, 5820 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING2_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING2_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING2_JIS,
		0,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE1),
		अणु SN_PRESSURE, 0, 256 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4824, 4824 पूर्ण,
		अणु SN_COORD, -172, 4290 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING3_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING3_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING3_JIS,
		HAS_INTEGRATED_BUTTON,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE2),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4460, 5166 पूर्ण,
		अणु SN_COORD, -75, 6700 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING4_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING4_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING4_JIS,
		HAS_INTEGRATED_BUTTON,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE2),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4620, 5140 पूर्ण,
		अणु SN_COORD, -150, 6600 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING4A_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING4A_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING4A_JIS,
		HAS_INTEGRATED_BUTTON,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE2),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4616, 5112 पूर्ण,
		अणु SN_COORD, -142, 5234 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING5_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING5_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING5_JIS,
		HAS_INTEGRATED_BUTTON,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE2),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4415, 5050 पूर्ण,
		अणु SN_COORD, -55, 6680 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING6_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING6_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING6_JIS,
		HAS_INTEGRATED_BUTTON,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE2),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4620, 5140 पूर्ण,
		अणु SN_COORD, -150, 6600 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING5A_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING5A_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING5A_JIS,
		HAS_INTEGRATED_BUTTON,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE2),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4750, 5280 पूर्ण,
		अणु SN_COORD, -150, 6730 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING6A_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING6A_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING6A_JIS,
		HAS_INTEGRATED_BUTTON,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE2),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4620, 5140 पूर्ण,
		अणु SN_COORD, -150, 6600 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING7_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING7_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING7_JIS,
		HAS_INTEGRATED_BUTTON,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE2),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4750, 5280 पूर्ण,
		अणु SN_COORD, -150, 6730 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING7A_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING7A_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING7A_JIS,
		HAS_INTEGRATED_BUTTON,
		0x84, माप(काष्ठा bt_data),
		0x81, DATAFORMAT(TYPE2),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4750, 5280 पूर्ण,
		अणु SN_COORD, -150, 6730 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING8_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING8_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING8_JIS,
		HAS_INTEGRATED_BUTTON,
		0, माप(काष्ठा bt_data),
		0x83, DATAFORMAT(TYPE3),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4620, 5140 पूर्ण,
		अणु SN_COORD, -150, 6600 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणु
		USB_DEVICE_ID_APPLE_WELLSPRING9_ANSI,
		USB_DEVICE_ID_APPLE_WELLSPRING9_ISO,
		USB_DEVICE_ID_APPLE_WELLSPRING9_JIS,
		HAS_INTEGRATED_BUTTON,
		0, माप(काष्ठा bt_data),
		0x83, DATAFORMAT(TYPE4),
		अणु SN_PRESSURE, 0, 300 पूर्ण,
		अणु SN_WIDTH, 0, 2048 पूर्ण,
		अणु SN_COORD, -4828, 5345 पूर्ण,
		अणु SN_COORD, -203, 6803 पूर्ण,
		अणु SN_ORIENT, -MAX_FINGER_ORIENTATION, MAX_FINGER_ORIENTATION पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/* वापस the device-specअगरic configuration by device */
अटल स्थिर काष्ठा bcm5974_config *bcm5974_get_config(काष्ठा usb_device *udev)
अणु
	u16 id = le16_to_cpu(udev->descriptor.idProduct);
	स्थिर काष्ठा bcm5974_config *cfg;

	क्रम (cfg = bcm5974_config_table; cfg->ansi; ++cfg)
		अगर (cfg->ansi == id || cfg->iso == id || cfg->jis == id)
			वापस cfg;

	वापस bcm5974_config_table;
पूर्ण

/* convert 16-bit little endian to चिन्हित पूर्णांकeger */
अटल अंतरभूत पूर्णांक raw2पूर्णांक(__le16 x)
अणु
	वापस (चिन्हित लघु)le16_to_cpu(x);
पूर्ण

अटल व्योम set_असल(काष्ठा input_dev *input, अचिन्हित पूर्णांक code,
		    स्थिर काष्ठा bcm5974_param *p)
अणु
	पूर्णांक fuzz = p->snratio ? (p->max - p->min) / p->snratio : 0;
	input_set_असल_params(input, code, p->min, p->max, fuzz, 0);
पूर्ण

/* setup which logical events to report */
अटल व्योम setup_events_to_report(काष्ठा input_dev *input_dev,
				   स्थिर काष्ठा bcm5974_config *cfg)
अणु
	__set_bit(EV_ABS, input_dev->evbit);

	/* क्रम synaptics only */
	input_set_असल_params(input_dev, ABS_PRESSURE, 0, 256, 5, 0);
	input_set_असल_params(input_dev, ABS_TOOL_WIDTH, 0, 16, 0, 0);

	/* finger touch area */
	set_असल(input_dev, ABS_MT_TOUCH_MAJOR, &cfg->w);
	set_असल(input_dev, ABS_MT_TOUCH_MINOR, &cfg->w);
	/* finger approach area */
	set_असल(input_dev, ABS_MT_WIDTH_MAJOR, &cfg->w);
	set_असल(input_dev, ABS_MT_WIDTH_MINOR, &cfg->w);
	/* finger orientation */
	set_असल(input_dev, ABS_MT_ORIENTATION, &cfg->o);
	/* finger position */
	set_असल(input_dev, ABS_MT_POSITION_X, &cfg->x);
	set_असल(input_dev, ABS_MT_POSITION_Y, &cfg->y);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_LEFT, input_dev->keybit);

	अगर (cfg->caps & HAS_INTEGRATED_BUTTON)
		__set_bit(INPUT_PROP_BUTTONPAD, input_dev->propbit);

	input_mt_init_slots(input_dev, MAX_FINGERS,
		INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED | INPUT_MT_TRACK);
पूर्ण

/* report button data as logical button state */
अटल पूर्णांक report_bt_state(काष्ठा bcm5974 *dev, पूर्णांक size)
अणु
	अगर (size != माप(काष्ठा bt_data))
		वापस -EIO;

	dprपूर्णांकk(7,
		"bcm5974: button data: %x %x %x %x\n",
		dev->bt_data->unknown1, dev->bt_data->button,
		dev->bt_data->rel_x, dev->bt_data->rel_y);

	input_report_key(dev->input, BTN_LEFT, dev->bt_data->button);
	input_sync(dev->input);

	वापस 0;
पूर्ण

अटल व्योम report_finger_data(काष्ठा input_dev *input, पूर्णांक slot,
			       स्थिर काष्ठा input_mt_pos *pos,
			       स्थिर काष्ठा tp_finger *f)
अणु
	input_mt_slot(input, slot);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, true);

	input_report_असल(input, ABS_MT_TOUCH_MAJOR,
			 raw2पूर्णांक(f->touch_major) << 1);
	input_report_असल(input, ABS_MT_TOUCH_MINOR,
			 raw2पूर्णांक(f->touch_minor) << 1);
	input_report_असल(input, ABS_MT_WIDTH_MAJOR,
			 raw2पूर्णांक(f->tool_major) << 1);
	input_report_असल(input, ABS_MT_WIDTH_MINOR,
			 raw2पूर्णांक(f->tool_minor) << 1);
	input_report_असल(input, ABS_MT_ORIENTATION,
			 MAX_FINGER_ORIENTATION - raw2पूर्णांक(f->orientation));
	input_report_असल(input, ABS_MT_POSITION_X, pos->x);
	input_report_असल(input, ABS_MT_POSITION_Y, pos->y);
पूर्ण

अटल व्योम report_synaptics_data(काष्ठा input_dev *input,
				  स्थिर काष्ठा bcm5974_config *cfg,
				  स्थिर काष्ठा tp_finger *f, पूर्णांक raw_n)
अणु
	पूर्णांक असल_p = 0, असल_w = 0;

	अगर (raw_n) अणु
		पूर्णांक p = raw2पूर्णांक(f->touch_major);
		पूर्णांक w = raw2पूर्णांक(f->tool_major);
		अगर (p > 0 && raw2पूर्णांक(f->origin)) अणु
			असल_p = clamp_val(256 * p / cfg->p.max, 0, 255);
			असल_w = clamp_val(16 * w / cfg->w.max, 0, 15);
		पूर्ण
	पूर्ण

	input_report_असल(input, ABS_PRESSURE, असल_p);
	input_report_असल(input, ABS_TOOL_WIDTH, असल_w);
पूर्ण

/* report trackpad data as logical trackpad state */
अटल पूर्णांक report_tp_state(काष्ठा bcm5974 *dev, पूर्णांक size)
अणु
	स्थिर काष्ठा bcm5974_config *c = &dev->cfg;
	स्थिर काष्ठा tp_finger *f;
	काष्ठा input_dev *input = dev->input;
	पूर्णांक raw_n, i, n = 0;

	अगर (size < c->tp_header || (size - c->tp_header) % c->tp_fsize != 0)
		वापस -EIO;

	raw_n = (size - c->tp_header) / c->tp_fsize;

	क्रम (i = 0; i < raw_n; i++) अणु
		f = get_tp_finger(dev, i);
		अगर (raw2पूर्णांक(f->touch_major) == 0)
			जारी;
		dev->pos[n].x = raw2पूर्णांक(f->असल_x);
		dev->pos[n].y = c->y.min + c->y.max - raw2पूर्णांक(f->असल_y);
		dev->index[n++] = f;
	पूर्ण

	input_mt_assign_slots(input, dev->slots, dev->pos, n, 0);

	क्रम (i = 0; i < n; i++)
		report_finger_data(input, dev->slots[i],
				   &dev->pos[i], dev->index[i]);

	input_mt_sync_frame(input);

	report_synaptics_data(input, c, get_tp_finger(dev, 0), raw_n);

	/* later types report button events via पूर्णांकegrated button only */
	अगर (c->caps & HAS_INTEGRATED_BUTTON) अणु
		पूर्णांक ibt = raw2पूर्णांक(dev->tp_data[c->tp_button]);
		input_report_key(input, BTN_LEFT, ibt);
	पूर्ण

	input_sync(input);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5974_wellspring_mode(काष्ठा bcm5974 *dev, bool on)
अणु
	स्थिर काष्ठा bcm5974_config *c = &dev->cfg;
	पूर्णांक retval = 0, size;
	अक्षर *data;

	/* Type 3 करोes not require a mode चयन */
	अगर (c->tp_type == TYPE3)
		वापस 0;

	data = kदो_स्मृति(c->um_size, GFP_KERNEL);
	अगर (!data) अणु
		dev_err(&dev->पूर्णांकf->dev, "out of memory\n");
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	/* पढ़ो configuration */
	size = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
			BCM5974_WELLSPRING_MODE_READ_REQUEST_ID,
			USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			c->um_req_val, c->um_req_idx, data, c->um_size, 5000);

	अगर (size != c->um_size) अणु
		dev_err(&dev->पूर्णांकf->dev, "could not read from device\n");
		retval = -EIO;
		जाओ out;
	पूर्ण

	/* apply the mode चयन */
	data[c->um_चयन_idx] = on ? c->um_चयन_on : c->um_चयन_off;

	/* ग_लिखो configuration */
	size = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
			BCM5974_WELLSPRING_MODE_WRITE_REQUEST_ID,
			USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			c->um_req_val, c->um_req_idx, data, c->um_size, 5000);

	अगर (size != c->um_size) अणु
		dev_err(&dev->पूर्णांकf->dev, "could not write to device\n");
		retval = -EIO;
		जाओ out;
	पूर्ण

	dprपूर्णांकk(2, "bcm5974: switched to %s mode.\n",
		on ? "wellspring" : "normal");

 out:
	kमुक्त(data);
	वापस retval;
पूर्ण

अटल व्योम bcm5974_irq_button(काष्ठा urb *urb)
अणु
	काष्ठा bcm5974 *dev = urb->context;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	पूर्णांक error;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -EOVERFLOW:
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		dev_dbg(&पूर्णांकf->dev, "button urb shutting down: %d\n",
			urb->status);
		वापस;
	शेष:
		dev_dbg(&पूर्णांकf->dev, "button urb status: %d\n", urb->status);
		जाओ निकास;
	पूर्ण

	अगर (report_bt_state(dev, dev->bt_urb->actual_length))
		dprपूर्णांकk(1, "bcm5974: bad button package, length: %d\n",
			dev->bt_urb->actual_length);

निकास:
	error = usb_submit_urb(dev->bt_urb, GFP_ATOMIC);
	अगर (error)
		dev_err(&पूर्णांकf->dev, "button urb failed: %d\n", error);
पूर्ण

अटल व्योम bcm5974_irq_trackpad(काष्ठा urb *urb)
अणु
	काष्ठा bcm5974 *dev = urb->context;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = dev->पूर्णांकf;
	पूर्णांक error;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -EOVERFLOW:
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		dev_dbg(&पूर्णांकf->dev, "trackpad urb shutting down: %d\n",
			urb->status);
		वापस;
	शेष:
		dev_dbg(&पूर्णांकf->dev, "trackpad urb status: %d\n", urb->status);
		जाओ निकास;
	पूर्ण

	/* control response ignored */
	अगर (dev->tp_urb->actual_length == 2)
		जाओ निकास;

	अगर (report_tp_state(dev, dev->tp_urb->actual_length))
		dprपूर्णांकk(1, "bcm5974: bad trackpad package, length: %d\n",
			dev->tp_urb->actual_length);

निकास:
	error = usb_submit_urb(dev->tp_urb, GFP_ATOMIC);
	अगर (error)
		dev_err(&पूर्णांकf->dev, "trackpad urb failed: %d\n", error);
पूर्ण

/*
 * The Wellspring trackpad, like many recent Apple trackpads, share
 * the usb device with the keyboard. Since keyboards are usually
 * handled by the HID प्रणाली, the device ends up being handled by two
 * modules. Setting up the device thereक्रमe becomes slightly
 * complicated. To enable multitouch features, a mode चयन is
 * required, which is usually applied via the control पूर्णांकerface of the
 * device.  It can be argued where this चयन should take place. In
 * some drivers, like appletouch, the चयन is made during
 * probe. However, the hid module may also alter the state of the
 * device, resulting in trackpad malfunction under certain
 * circumstances. To get around this problem, there is at least one
 * example that utilizes the USB_QUIRK_RESET_RESUME quirk in order to
 * receive a reset_resume request rather than the normal resume.
 * Since the implementation of reset_resume is equal to mode चयन
 * plus start_traffic, it seems easier to always करो the चयन when
 * starting traffic on the device.
 */
अटल पूर्णांक bcm5974_start_traffic(काष्ठा bcm5974 *dev)
अणु
	पूर्णांक error;

	error = bcm5974_wellspring_mode(dev, true);
	अगर (error) अणु
		dprपूर्णांकk(1, "bcm5974: mode switch failed\n");
		जाओ err_out;
	पूर्ण

	अगर (dev->bt_urb) अणु
		error = usb_submit_urb(dev->bt_urb, GFP_KERNEL);
		अगर (error)
			जाओ err_reset_mode;
	पूर्ण

	error = usb_submit_urb(dev->tp_urb, GFP_KERNEL);
	अगर (error)
		जाओ err_समाप्त_bt;

	वापस 0;

err_समाप्त_bt:
	usb_समाप्त_urb(dev->bt_urb);
err_reset_mode:
	bcm5974_wellspring_mode(dev, false);
err_out:
	वापस error;
पूर्ण

अटल व्योम bcm5974_छोड़ो_traffic(काष्ठा bcm5974 *dev)
अणु
	usb_समाप्त_urb(dev->tp_urb);
	usb_समाप्त_urb(dev->bt_urb);
	bcm5974_wellspring_mode(dev, false);
पूर्ण

/*
 * The code below implements खोलो/बंद and manual suspend/resume.
 * All functions may be called in अक्रमom order.
 *
 * Opening a suspended device fails with EACCES - permission denied.
 *
 * Failing a resume leaves the device resumed but बंदd.
 */
अटल पूर्णांक bcm5974_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा bcm5974 *dev = input_get_drvdata(input);
	पूर्णांक error;

	error = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (error)
		वापस error;

	mutex_lock(&dev->pm_mutex);

	error = bcm5974_start_traffic(dev);
	अगर (!error)
		dev->खोलोed = 1;

	mutex_unlock(&dev->pm_mutex);

	अगर (error)
		usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस error;
पूर्ण

अटल व्योम bcm5974_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा bcm5974 *dev = input_get_drvdata(input);

	mutex_lock(&dev->pm_mutex);

	bcm5974_छोड़ो_traffic(dev);
	dev->खोलोed = 0;

	mutex_unlock(&dev->pm_mutex);

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
पूर्ण

अटल पूर्णांक bcm5974_suspend(काष्ठा usb_पूर्णांकerface *अगरace, pm_message_t message)
अणु
	काष्ठा bcm5974 *dev = usb_get_पूर्णांकfdata(अगरace);

	mutex_lock(&dev->pm_mutex);

	अगर (dev->खोलोed)
		bcm5974_छोड़ो_traffic(dev);

	mutex_unlock(&dev->pm_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm5974_resume(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा bcm5974 *dev = usb_get_पूर्णांकfdata(अगरace);
	पूर्णांक error = 0;

	mutex_lock(&dev->pm_mutex);

	अगर (dev->खोलोed)
		error = bcm5974_start_traffic(dev);

	mutex_unlock(&dev->pm_mutex);

	वापस error;
पूर्ण

अटल पूर्णांक bcm5974_probe(काष्ठा usb_पूर्णांकerface *अगरace,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(अगरace);
	स्थिर काष्ठा bcm5974_config *cfg;
	काष्ठा bcm5974 *dev;
	काष्ठा input_dev *input_dev;
	पूर्णांक error = -ENOMEM;

	/* find the product index */
	cfg = bcm5974_get_config(udev);

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(काष्ठा bcm5974), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!dev || !input_dev) अणु
		dev_err(&अगरace->dev, "out of memory\n");
		जाओ err_मुक्त_devs;
	पूर्ण

	dev->udev = udev;
	dev->पूर्णांकf = अगरace;
	dev->input = input_dev;
	dev->cfg = *cfg;
	mutex_init(&dev->pm_mutex);

	/* setup urbs */
	अगर (cfg->tp_type == TYPE1) अणु
		dev->bt_urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!dev->bt_urb)
			जाओ err_मुक्त_devs;
	पूर्ण

	dev->tp_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->tp_urb)
		जाओ err_मुक्त_bt_urb;

	अगर (dev->bt_urb) अणु
		dev->bt_data = usb_alloc_coherent(dev->udev,
					  dev->cfg.bt_datalen, GFP_KERNEL,
					  &dev->bt_urb->transfer_dma);
		अगर (!dev->bt_data)
			जाओ err_मुक्त_urb;
	पूर्ण

	dev->tp_data = usb_alloc_coherent(dev->udev,
					  dev->cfg.tp_datalen, GFP_KERNEL,
					  &dev->tp_urb->transfer_dma);
	अगर (!dev->tp_data)
		जाओ err_मुक्त_bt_buffer;

	अगर (dev->bt_urb)
		usb_fill_पूर्णांक_urb(dev->bt_urb, udev,
				 usb_rcvपूर्णांकpipe(udev, cfg->bt_ep),
				 dev->bt_data, dev->cfg.bt_datalen,
				 bcm5974_irq_button, dev, 1);

	usb_fill_पूर्णांक_urb(dev->tp_urb, udev,
			 usb_rcvपूर्णांकpipe(udev, cfg->tp_ep),
			 dev->tp_data, dev->cfg.tp_datalen,
			 bcm5974_irq_trackpad, dev, 1);

	/* create bcm5974 device */
	usb_make_path(udev, dev->phys, माप(dev->phys));
	strlcat(dev->phys, "/input0", माप(dev->phys));

	input_dev->name = "bcm5974";
	input_dev->phys = dev->phys;
	usb_to_input_id(dev->udev, &input_dev->id);
	/* report driver capabilities via the version field */
	input_dev->id.version = cfg->caps;
	input_dev->dev.parent = &अगरace->dev;

	input_set_drvdata(input_dev, dev);

	input_dev->खोलो = bcm5974_खोलो;
	input_dev->बंद = bcm5974_बंद;

	setup_events_to_report(input_dev, cfg);

	error = input_रेजिस्टर_device(dev->input);
	अगर (error)
		जाओ err_मुक्त_buffer;

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(अगरace, dev);

	वापस 0;

err_मुक्त_buffer:
	usb_मुक्त_coherent(dev->udev, dev->cfg.tp_datalen,
		dev->tp_data, dev->tp_urb->transfer_dma);
err_मुक्त_bt_buffer:
	अगर (dev->bt_urb)
		usb_मुक्त_coherent(dev->udev, dev->cfg.bt_datalen,
				  dev->bt_data, dev->bt_urb->transfer_dma);
err_मुक्त_urb:
	usb_मुक्त_urb(dev->tp_urb);
err_मुक्त_bt_urb:
	usb_मुक्त_urb(dev->bt_urb);
err_मुक्त_devs:
	usb_set_पूर्णांकfdata(अगरace, शून्य);
	input_मुक्त_device(input_dev);
	kमुक्त(dev);
	वापस error;
पूर्ण

अटल व्योम bcm5974_disconnect(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा bcm5974 *dev = usb_get_पूर्णांकfdata(अगरace);

	usb_set_पूर्णांकfdata(अगरace, शून्य);

	input_unरेजिस्टर_device(dev->input);
	usb_मुक्त_coherent(dev->udev, dev->cfg.tp_datalen,
			  dev->tp_data, dev->tp_urb->transfer_dma);
	अगर (dev->bt_urb)
		usb_मुक्त_coherent(dev->udev, dev->cfg.bt_datalen,
				  dev->bt_data, dev->bt_urb->transfer_dma);
	usb_मुक्त_urb(dev->tp_urb);
	usb_मुक्त_urb(dev->bt_urb);
	kमुक्त(dev);
पूर्ण

अटल काष्ठा usb_driver bcm5974_driver = अणु
	.name			= "bcm5974",
	.probe			= bcm5974_probe,
	.disconnect		= bcm5974_disconnect,
	.suspend		= bcm5974_suspend,
	.resume			= bcm5974_resume,
	.id_table		= bcm5974_table,
	.supports_स्वतःsuspend	= 1,
पूर्ण;

module_usb_driver(bcm5974_driver);
