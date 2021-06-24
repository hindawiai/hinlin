<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   imon.c:	input and display driver क्रम SoundGraph iMON IR/VFD/LCD
 *
 *   Copyright(C) 2010  Jarod Wilson <jarod@wilsonet.com>
 *   Portions based on the original lirc_imon driver,
 *	Copyright(C) 2004  Venky Raju(dev@venky.ws)
 *
 *   Huge thanks to R. Geoff Newbury क्रम invaluable debugging on the
 *   0xffdc iMON devices, and क्रम sending me one to hack on, without
 *   which the support क्रम them wouldn't be nearly as good. Thanks
 *   also to the numerous 0xffdc device owners that tested स्वतः-config
 *   support क्रम me and provided debug dumps from their devices.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ratelimit.h>

#समावेश <linux/input.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <media/rc-core.h>

#समावेश <linux/समयr.h>

#घोषणा MOD_AUTHOR	"Jarod Wilson <jarod@wilsonet.com>"
#घोषणा MOD_DESC	"Driver for SoundGraph iMON MultiMedia IR/Display"
#घोषणा MOD_NAME	"imon"
#घोषणा MOD_VERSION	"0.9.4"

#घोषणा DISPLAY_MINOR_BASE	144
#घोषणा DEVICE_NAME	"lcd%d"

#घोषणा BUF_CHUNK_SIZE	8
#घोषणा BUF_SIZE	128

#घोषणा BIT_DURATION	250	/* each bit received is 250us */

#घोषणा IMON_CLOCK_ENABLE_PACKETS	2

/*** P R O T O T Y P E S ***/

/* USB Callback prototypes */
अटल पूर्णांक imon_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		      स्थिर काष्ठा usb_device_id *id);
अटल व्योम imon_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
अटल व्योम usb_rx_callback_पूर्णांकf0(काष्ठा urb *urb);
अटल व्योम usb_rx_callback_पूर्णांकf1(काष्ठा urb *urb);
अटल व्योम usb_tx_callback(काष्ठा urb *urb);

/* suspend/resume support */
अटल पूर्णांक imon_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
अटल पूर्णांक imon_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message);

/* Display file_operations function prototypes */
अटल पूर्णांक display_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक display_बंद(काष्ठा inode *inode, काष्ठा file *file);

/* VFD ग_लिखो operation */
अटल sमाप_प्रकार vfd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार n_bytes, loff_t *pos);

/* LCD file_operations override function prototypes */
अटल sमाप_प्रकार lcd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार n_bytes, loff_t *pos);

/*** G L O B A L S ***/

काष्ठा imon_panel_key_table अणु
	u64 hw_code;
	u32 keycode;
पूर्ण;

काष्ठा imon_usb_dev_descr अणु
	__u16 flags;
#घोषणा IMON_NO_FLAGS 0
#घोषणा IMON_NEED_20MS_PKT_DELAY 1
#घोषणा IMON_SUPPRESS_REPEATED_KEYS 2
	काष्ठा imon_panel_key_table key_table[];
पूर्ण;

काष्ठा imon_context अणु
	काष्ठा device *dev;
	/* Newer devices have two पूर्णांकerfaces */
	काष्ठा usb_device *usbdev_पूर्णांकf0;
	काष्ठा usb_device *usbdev_पूर्णांकf1;

	bool display_supported;		/* not all controllers करो */
	bool display_isखोलो;		/* display port has been खोलोed */
	bool rf_device;			/* true अगर iMON 2.4G LT/DT RF device */
	bool rf_isassociating;		/* RF remote associating */
	bool dev_present_पूर्णांकf0;		/* USB device presence, पूर्णांकerface 0 */
	bool dev_present_पूर्णांकf1;		/* USB device presence, पूर्णांकerface 1 */

	काष्ठा mutex lock;		/* to lock this object */
	रुको_queue_head_t हटाओ_ok;	/* For unexpected USB disconnects */

	काष्ठा usb_endpoपूर्णांक_descriptor *rx_endpoपूर्णांक_पूर्णांकf0;
	काष्ठा usb_endpoपूर्णांक_descriptor *rx_endpoपूर्णांक_पूर्णांकf1;
	काष्ठा usb_endpoपूर्णांक_descriptor *tx_endpoपूर्णांक;
	काष्ठा urb *rx_urb_पूर्णांकf0;
	काष्ठा urb *rx_urb_पूर्णांकf1;
	काष्ठा urb *tx_urb;
	bool tx_control;
	अचिन्हित अक्षर usb_rx_buf[8];
	अचिन्हित अक्षर usb_tx_buf[8];
	अचिन्हित पूर्णांक send_packet_delay;

	काष्ठा tx_t अणु
		अचिन्हित अक्षर data_buf[35];	/* user data buffer */
		काष्ठा completion finished;	/* रुको क्रम ग_लिखो to finish */
		bool busy;			/* ग_लिखो in progress */
		पूर्णांक status;			/* status of tx completion */
	पूर्ण tx;

	u16 venकरोr;			/* usb venकरोr ID */
	u16 product;			/* usb product ID */

	काष्ठा rc_dev *rdev;		/* rc-core device क्रम remote */
	काष्ठा input_dev *idev;		/* input device क्रम panel & IR mouse */
	काष्ठा input_dev *touch;	/* input device क्रम touchscreen */

	spinlock_t kc_lock;		/* make sure we get keycodes right */
	u32 kc;				/* current input keycode */
	u32 last_keycode;		/* last reported input keycode */
	u32 rc_scancode;		/* the computed remote scancode */
	u8 rc_toggle;			/* the computed remote toggle bit */
	u64 rc_proto;			/* iMON or MCE (RC6) IR protocol? */
	bool release_code;		/* some keys send a release code */

	u8 display_type;		/* store the display type */
	bool pad_mouse;			/* toggle kbd(0)/mouse(1) mode */

	अक्षर name_rdev[128];		/* rc input device name */
	अक्षर phys_rdev[64];		/* rc input device phys path */

	अक्षर name_idev[128];		/* input device name */
	अक्षर phys_idev[64];		/* input device phys path */

	अक्षर name_touch[128];		/* touch screen name */
	अक्षर phys_touch[64];		/* touch screen phys path */
	काष्ठा समयr_list tसमयr;	/* touch screen समयr */
	पूर्णांक touch_x;			/* x coordinate on touchscreen */
	पूर्णांक touch_y;			/* y coordinate on touchscreen */
	स्थिर काष्ठा imon_usb_dev_descr *dev_descr;
					/* device description with key */
					/* table क्रम front panels */
पूर्ण;

#घोषणा TOUCH_TIMEOUT	(HZ/30)

/* vfd अक्षरacter device file operations */
अटल स्थिर काष्ठा file_operations vfd_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= &display_खोलो,
	.ग_लिखो		= &vfd_ग_लिखो,
	.release	= &display_बंद,
	.llseek		= noop_llseek,
पूर्ण;

/* lcd अक्षरacter device file operations */
अटल स्थिर काष्ठा file_operations lcd_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= &display_खोलो,
	.ग_लिखो		= &lcd_ग_लिखो,
	.release	= &display_बंद,
	.llseek		= noop_llseek,
पूर्ण;

क्रमागत अणु
	IMON_DISPLAY_TYPE_AUTO = 0,
	IMON_DISPLAY_TYPE_VFD  = 1,
	IMON_DISPLAY_TYPE_LCD  = 2,
	IMON_DISPLAY_TYPE_VGA  = 3,
	IMON_DISPLAY_TYPE_NONE = 4,
पूर्ण;

क्रमागत अणु
	IMON_KEY_IMON	= 0,
	IMON_KEY_MCE	= 1,
	IMON_KEY_PANEL	= 2,
पूर्ण;

अटल काष्ठा usb_class_driver imon_vfd_class = अणु
	.name		= DEVICE_NAME,
	.fops		= &vfd_fops,
	.minor_base	= DISPLAY_MINOR_BASE,
पूर्ण;

अटल काष्ठा usb_class_driver imon_lcd_class = अणु
	.name		= DEVICE_NAME,
	.fops		= &lcd_fops,
	.minor_base	= DISPLAY_MINOR_BASE,
पूर्ण;

/* imon receiver front panel/knob key table */
अटल स्थिर काष्ठा imon_usb_dev_descr imon_शेष_table = अणु
	.flags = IMON_NO_FLAGS,
	.key_table = अणु
		अणु 0x000000000f00ffeell, KEY_MEDIA पूर्ण, /* Go */
		अणु 0x000000001200ffeell, KEY_UP पूर्ण,
		अणु 0x000000001300ffeell, KEY_DOWN पूर्ण,
		अणु 0x000000001400ffeell, KEY_LEFT पूर्ण,
		अणु 0x000000001500ffeell, KEY_RIGHT पूर्ण,
		अणु 0x000000001600ffeell, KEY_ENTER पूर्ण,
		अणु 0x000000001700ffeell, KEY_ESC पूर्ण,
		अणु 0x000000001f00ffeell, KEY_AUDIO पूर्ण,
		अणु 0x000000002000ffeell, KEY_VIDEO पूर्ण,
		अणु 0x000000002100ffeell, KEY_CAMERA पूर्ण,
		अणु 0x000000002700ffeell, KEY_DVD पूर्ण,
		अणु 0x000000002300ffeell, KEY_TV पूर्ण,
		अणु 0x000000002b00ffeell, KEY_EXIT पूर्ण,
		अणु 0x000000002c00ffeell, KEY_SELECT पूर्ण,
		अणु 0x000000002d00ffeell, KEY_MENU पूर्ण,
		अणु 0x000000000500ffeell, KEY_PREVIOUS पूर्ण,
		अणु 0x000000000700ffeell, KEY_REWIND पूर्ण,
		अणु 0x000000000400ffeell, KEY_STOP पूर्ण,
		अणु 0x000000003c00ffeell, KEY_PLAYPAUSE पूर्ण,
		अणु 0x000000000800ffeell, KEY_FASTFORWARD पूर्ण,
		अणु 0x000000000600ffeell, KEY_NEXT पूर्ण,
		अणु 0x000000010000ffeell, KEY_RIGHT पूर्ण,
		अणु 0x000001000000ffeell, KEY_LEFT पूर्ण,
		अणु 0x000000003d00ffeell, KEY_SELECT पूर्ण,
		अणु 0x000100000000ffeell, KEY_VOLUMEUP पूर्ण,
		अणु 0x010000000000ffeell, KEY_VOLUMEDOWN पूर्ण,
		अणु 0x000000000100ffeell, KEY_MUTE पूर्ण,
		/* 0xffdc iMON MCE VFD */
		अणु 0x00010000ffffffeell, KEY_VOLUMEUP पूर्ण,
		अणु 0x01000000ffffffeell, KEY_VOLUMEDOWN पूर्ण,
		अणु 0x00000001ffffffeell, KEY_MUTE पूर्ण,
		अणु 0x0000000fffffffeell, KEY_MEDIA पूर्ण,
		अणु 0x00000012ffffffeell, KEY_UP पूर्ण,
		अणु 0x00000013ffffffeell, KEY_DOWN पूर्ण,
		अणु 0x00000014ffffffeell, KEY_LEFT पूर्ण,
		अणु 0x00000015ffffffeell, KEY_RIGHT पूर्ण,
		अणु 0x00000016ffffffeell, KEY_ENTER पूर्ण,
		अणु 0x00000017ffffffeell, KEY_ESC पूर्ण,
		/* iMON Knob values */
		अणु 0x000100ffffffffeell, KEY_VOLUMEUP पूर्ण,
		अणु 0x010000ffffffffeell, KEY_VOLUMEDOWN पूर्ण,
		अणु 0x000008ffffffffeell, KEY_MUTE पूर्ण,
		अणु 0, KEY_RESERVED पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा imon_usb_dev_descr imon_OEM_VFD = अणु
	.flags = IMON_NEED_20MS_PKT_DELAY,
	.key_table = अणु
		अणु 0x000000000f00ffeell, KEY_MEDIA पूर्ण, /* Go */
		अणु 0x000000001200ffeell, KEY_UP पूर्ण,
		अणु 0x000000001300ffeell, KEY_DOWN पूर्ण,
		अणु 0x000000001400ffeell, KEY_LEFT पूर्ण,
		अणु 0x000000001500ffeell, KEY_RIGHT पूर्ण,
		अणु 0x000000001600ffeell, KEY_ENTER पूर्ण,
		अणु 0x000000001700ffeell, KEY_ESC पूर्ण,
		अणु 0x000000001f00ffeell, KEY_AUDIO पूर्ण,
		अणु 0x000000002b00ffeell, KEY_EXIT पूर्ण,
		अणु 0x000000002c00ffeell, KEY_SELECT पूर्ण,
		अणु 0x000000002d00ffeell, KEY_MENU पूर्ण,
		अणु 0x000000000500ffeell, KEY_PREVIOUS पूर्ण,
		अणु 0x000000000700ffeell, KEY_REWIND पूर्ण,
		अणु 0x000000000400ffeell, KEY_STOP पूर्ण,
		अणु 0x000000003c00ffeell, KEY_PLAYPAUSE पूर्ण,
		अणु 0x000000000800ffeell, KEY_FASTFORWARD पूर्ण,
		अणु 0x000000000600ffeell, KEY_NEXT पूर्ण,
		अणु 0x000000010000ffeell, KEY_RIGHT पूर्ण,
		अणु 0x000001000000ffeell, KEY_LEFT पूर्ण,
		अणु 0x000000003d00ffeell, KEY_SELECT पूर्ण,
		अणु 0x000100000000ffeell, KEY_VOLUMEUP पूर्ण,
		अणु 0x010000000000ffeell, KEY_VOLUMEDOWN पूर्ण,
		अणु 0x000000000100ffeell, KEY_MUTE पूर्ण,
		/* 0xffdc iMON MCE VFD */
		अणु 0x00010000ffffffeell, KEY_VOLUMEUP पूर्ण,
		अणु 0x01000000ffffffeell, KEY_VOLUMEDOWN पूर्ण,
		अणु 0x00000001ffffffeell, KEY_MUTE पूर्ण,
		अणु 0x0000000fffffffeell, KEY_MEDIA पूर्ण,
		अणु 0x00000012ffffffeell, KEY_UP पूर्ण,
		अणु 0x00000013ffffffeell, KEY_DOWN पूर्ण,
		अणु 0x00000014ffffffeell, KEY_LEFT पूर्ण,
		अणु 0x00000015ffffffeell, KEY_RIGHT पूर्ण,
		अणु 0x00000016ffffffeell, KEY_ENTER पूर्ण,
		अणु 0x00000017ffffffeell, KEY_ESC पूर्ण,
		/* iMON Knob values */
		अणु 0x000100ffffffffeell, KEY_VOLUMEUP पूर्ण,
		अणु 0x010000ffffffffeell, KEY_VOLUMEDOWN पूर्ण,
		अणु 0x000008ffffffffeell, KEY_MUTE पूर्ण,
		अणु 0, KEY_RESERVED पूर्ण,
	पूर्ण
पूर्ण;

/* imon receiver front panel/knob key table क्रम DH102*/
अटल स्थिर काष्ठा imon_usb_dev_descr imon_DH102 = अणु
	.flags = IMON_NO_FLAGS,
	.key_table = अणु
		अणु 0x000100000000ffeell, KEY_VOLUMEUP पूर्ण,
		अणु 0x010000000000ffeell, KEY_VOLUMEDOWN पूर्ण,
		अणु 0x000000010000ffeell, KEY_MUTE पूर्ण,
		अणु 0x0000000f0000ffeell, KEY_MEDIA पूर्ण,
		अणु 0x000000120000ffeell, KEY_UP पूर्ण,
		अणु 0x000000130000ffeell, KEY_DOWN पूर्ण,
		अणु 0x000000140000ffeell, KEY_LEFT पूर्ण,
		अणु 0x000000150000ffeell, KEY_RIGHT पूर्ण,
		अणु 0x000000160000ffeell, KEY_ENTER पूर्ण,
		अणु 0x000000170000ffeell, KEY_ESC पूर्ण,
		अणु 0x0000002b0000ffeell, KEY_EXIT पूर्ण,
		अणु 0x0000002c0000ffeell, KEY_SELECT पूर्ण,
		अणु 0x0000002d0000ffeell, KEY_MENU पूर्ण,
		अणु 0, KEY_RESERVED पूर्ण
	पूर्ण
पूर्ण;

/* imon ultrabay front panel key table */
अटल स्थिर काष्ठा imon_usb_dev_descr ultrabay_table = अणु
	.flags = IMON_SUPPRESS_REPEATED_KEYS,
	.key_table = अणु
		अणु 0x0000000f0000ffeell, KEY_MEDIA पूर्ण,      /* Go */
		अणु 0x000000000100ffeell, KEY_UP पूर्ण,
		अणु 0x000000000001ffeell, KEY_DOWN पूर्ण,
		अणु 0x000000160000ffeell, KEY_ENTER पूर्ण,
		अणु 0x0000001f0000ffeell, KEY_AUDIO पूर्ण,      /* Music */
		अणु 0x000000200000ffeell, KEY_VIDEO पूर्ण,      /* Movie */
		अणु 0x000000210000ffeell, KEY_CAMERA पूर्ण,     /* Photo */
		अणु 0x000000270000ffeell, KEY_DVD पूर्ण,        /* DVD */
		अणु 0x000000230000ffeell, KEY_TV पूर्ण,         /* TV */
		अणु 0x000000050000ffeell, KEY_PREVIOUS पूर्ण,   /* Previous */
		अणु 0x000000070000ffeell, KEY_REWIND पूर्ण,
		अणु 0x000000040000ffeell, KEY_STOP पूर्ण,
		अणु 0x000000020000ffeell, KEY_PLAYPAUSE पूर्ण,
		अणु 0x000000080000ffeell, KEY_FASTFORWARD पूर्ण,
		अणु 0x000000060000ffeell, KEY_NEXT पूर्ण,       /* Next */
		अणु 0x000100000000ffeell, KEY_VOLUMEUP पूर्ण,
		अणु 0x010000000000ffeell, KEY_VOLUMEDOWN पूर्ण,
		अणु 0x000000010000ffeell, KEY_MUTE पूर्ण,
		अणु 0, KEY_RESERVED पूर्ण,
	पूर्ण
पूर्ण;

/*
 * USB Device ID क्रम iMON USB Control Boards
 *
 * The Winकरोws drivers contain 6 dअगरferent inf files, more or less one क्रम
 * each new device until the 0x0034-0x0046 devices, which all use the same
 * driver. Some of the devices in the 34-46 range haven't been definitively
 * identअगरied yet. Early devices have either a TriGem Computer, Inc. or a
 * Samsung venकरोr ID (0x0aa8 and 0x04e8 respectively), जबतक all later
 * devices use the SoundGraph venकरोr ID (0x15c2). This driver only supports
 * the ffdc and later devices, which करो onboard decoding.
 */
अटल स्थिर काष्ठा usb_device_id imon_usb_id_table[] = अणु
	/*
	 * Several devices with this same device ID, all use iMON_PAD.inf
	 * SoundGraph iMON PAD (IR & VFD)
	 * SoundGraph iMON PAD (IR & LCD)
	 * SoundGraph iMON Knob (IR only)
	 */
	अणु USB_DEVICE(0x15c2, 0xffdc),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_table पूर्ण,

	/*
	 * Newer devices, all driven by the latest iMON Winकरोws driver, full
	 * list of device IDs extracted via 'strings Setup/data1.hdr |grep 15c2'
	 * Need user input to fill in details on unknown devices.
	 */
	/* SoundGraph iMON OEM Touch LCD (IR & 7" VGA LCD) */
	अणु USB_DEVICE(0x15c2, 0x0034),
	  .driver_info = (अचिन्हित दीर्घ)&imon_DH102 पूर्ण,
	/* SoundGraph iMON OEM Touch LCD (IR & 4.3" VGA LCD) */
	अणु USB_DEVICE(0x15c2, 0x0035),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* SoundGraph iMON OEM VFD (IR & VFD) */
	अणु USB_DEVICE(0x15c2, 0x0036),
	  .driver_info = (अचिन्हित दीर्घ)&imon_OEM_VFD पूर्ण,
	/* device specअगरics unknown */
	अणु USB_DEVICE(0x15c2, 0x0037),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* SoundGraph iMON OEM LCD (IR & LCD) */
	अणु USB_DEVICE(0x15c2, 0x0038),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* SoundGraph iMON UltraBay (IR & LCD) */
	अणु USB_DEVICE(0x15c2, 0x0039),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* device specअगरics unknown */
	अणु USB_DEVICE(0x15c2, 0x003a),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* device specअगरics unknown */
	अणु USB_DEVICE(0x15c2, 0x003b),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* SoundGraph iMON OEM Inside (IR only) */
	अणु USB_DEVICE(0x15c2, 0x003c),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* device specअगरics unknown */
	अणु USB_DEVICE(0x15c2, 0x003d),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* device specअगरics unknown */
	अणु USB_DEVICE(0x15c2, 0x003e),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* device specअगरics unknown */
	अणु USB_DEVICE(0x15c2, 0x003f),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* device specअगरics unknown */
	अणु USB_DEVICE(0x15c2, 0x0040),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* SoundGraph iMON MINI (IR only) */
	अणु USB_DEVICE(0x15c2, 0x0041),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* Antec Veris Mulसमयdia Station EZ External (IR only) */
	अणु USB_DEVICE(0x15c2, 0x0042),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* Antec Veris Mulसमयdia Station Basic Internal (IR only) */
	अणु USB_DEVICE(0x15c2, 0x0043),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* Antec Veris Mulसमयdia Station Elite (IR & VFD) */
	अणु USB_DEVICE(0x15c2, 0x0044),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* Antec Veris Mulसमयdia Station Premiere (IR & LCD) */
	अणु USB_DEVICE(0x15c2, 0x0045),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	/* device specअगरics unknown */
	अणु USB_DEVICE(0x15c2, 0x0046),
	  .driver_info = (अचिन्हित दीर्घ)&imon_शेष_tableपूर्ण,
	अणुपूर्ण
पूर्ण;

/* USB Device data */
अटल काष्ठा usb_driver imon_driver = अणु
	.name		= MOD_NAME,
	.probe		= imon_probe,
	.disconnect	= imon_disconnect,
	.suspend	= imon_suspend,
	.resume		= imon_resume,
	.id_table	= imon_usb_id_table,
पूर्ण;

/* to prevent races between खोलो() and disconnect(), probing, etc */
अटल DEFINE_MUTEX(driver_lock);

/* Module bookkeeping bits */
MODULE_AUTHOR(MOD_AUTHOR);
MODULE_DESCRIPTION(MOD_DESC);
MODULE_VERSION(MOD_VERSION);
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(usb, imon_usb_id_table);

अटल bool debug;
module_param(debug, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug messages: 0=no, 1=yes (default: no)");

/* lcd, vfd, vga or none? should be स्वतः-detected, but can be overridden... */
अटल पूर्णांक display_type;
module_param(display_type, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(display_type, "Type of attached display. 0=autodetect, 1=vfd, 2=lcd, 3=vga, 4=none (default: autodetect)");

अटल पूर्णांक pad_stabilize = 1;
module_param(pad_stabilize, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(pad_stabilize, "Apply stabilization algorithm to iMON PAD presses in arrow key mode. 0=disable, 1=enable (default).");

/*
 * In certain use हालs, mouse mode isn't really helpful, and could actually
 * cause confusion, so allow disabling it when the IR device is खोलो.
 */
अटल bool nomouse;
module_param(nomouse, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(nomouse, "Disable mouse input device mode when IR device is open. 0=don't disable, 1=disable. (default: don't disable)");

/* threshold at which a pad push रेजिस्टरs as an arrow key in kbd mode */
अटल पूर्णांक pad_thresh;
module_param(pad_thresh, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(pad_thresh, "Threshold at which a pad push registers as an arrow key in kbd mode (default: 28)");


अटल व्योम मुक्त_imon_context(काष्ठा imon_context *ictx)
अणु
	काष्ठा device *dev = ictx->dev;

	usb_मुक्त_urb(ictx->tx_urb);
	usb_मुक्त_urb(ictx->rx_urb_पूर्णांकf0);
	usb_मुक्त_urb(ictx->rx_urb_पूर्णांकf1);
	kमुक्त(ictx);

	dev_dbg(dev, "%s: iMON context freed\n", __func__);
पूर्ण

/*
 * Called when the Display device (e.g. /dev/lcd0)
 * is खोलोed by the application.
 */
अटल पूर्णांक display_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	काष्ठा imon_context *ictx = शून्य;
	पूर्णांक subminor;
	पूर्णांक retval = 0;

	/* prevent races with disconnect */
	mutex_lock(&driver_lock);

	subminor = iminor(inode);
	पूर्णांकerface = usb_find_पूर्णांकerface(&imon_driver, subminor);
	अगर (!पूर्णांकerface) अणु
		pr_err("could not find interface for minor %d\n", subminor);
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण
	ictx = usb_get_पूर्णांकfdata(पूर्णांकerface);

	अगर (!ictx) अणु
		pr_err("no context found for minor %d\n", subminor);
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	mutex_lock(&ictx->lock);

	अगर (!ictx->display_supported) अणु
		pr_err("display not supported by device\n");
		retval = -ENODEV;
	पूर्ण अन्यथा अगर (ictx->display_isखोलो) अणु
		pr_err("display port is already open\n");
		retval = -EBUSY;
	पूर्ण अन्यथा अणु
		ictx->display_isखोलो = true;
		file->निजी_data = ictx;
		dev_dbg(ictx->dev, "display port opened\n");
	पूर्ण

	mutex_unlock(&ictx->lock);

निकास:
	mutex_unlock(&driver_lock);
	वापस retval;
पूर्ण

/*
 * Called when the display device (e.g. /dev/lcd0)
 * is बंदd by the application.
 */
अटल पूर्णांक display_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा imon_context *ictx = शून्य;
	पूर्णांक retval = 0;

	ictx = file->निजी_data;

	अगर (!ictx) अणु
		pr_err("no context for device\n");
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&ictx->lock);

	अगर (!ictx->display_supported) अणु
		pr_err("display not supported by device\n");
		retval = -ENODEV;
	पूर्ण अन्यथा अगर (!ictx->display_isखोलो) अणु
		pr_err("display is not open\n");
		retval = -EIO;
	पूर्ण अन्यथा अणु
		ictx->display_isखोलो = false;
		dev_dbg(ictx->dev, "display port closed\n");
	पूर्ण

	mutex_unlock(&ictx->lock);
	वापस retval;
पूर्ण

/*
 * Sends a packet to the device -- this function must be called with
 * ictx->lock held, or its unlock/lock sequence जबतक रुकोing क्रम tx
 * to complete can/will lead to a deadlock.
 */
अटल पूर्णांक send_packet(काष्ठा imon_context *ictx)
अणु
	अचिन्हित पूर्णांक pipe;
	अचिन्हित दीर्घ समयout;
	पूर्णांक पूर्णांकerval = 0;
	पूर्णांक retval = 0;
	काष्ठा usb_ctrlrequest *control_req = शून्य;

	/* Check अगर we need to use control or पूर्णांकerrupt urb */
	अगर (!ictx->tx_control) अणु
		pipe = usb_sndपूर्णांकpipe(ictx->usbdev_पूर्णांकf0,
				      ictx->tx_endpoपूर्णांक->bEndpoपूर्णांकAddress);
		पूर्णांकerval = ictx->tx_endpoपूर्णांक->bInterval;

		usb_fill_पूर्णांक_urb(ictx->tx_urb, ictx->usbdev_पूर्णांकf0, pipe,
				 ictx->usb_tx_buf,
				 माप(ictx->usb_tx_buf),
				 usb_tx_callback, ictx, पूर्णांकerval);

		ictx->tx_urb->actual_length = 0;
	पूर्ण अन्यथा अणु
		/* fill request पूर्णांकo kदो_स्मृति'ed space: */
		control_req = kदो_स्मृति(माप(*control_req), GFP_KERNEL);
		अगर (control_req == शून्य)
			वापस -ENOMEM;

		/* setup packet is '21 09 0200 0001 0008' */
		control_req->bRequestType = 0x21;
		control_req->bRequest = 0x09;
		control_req->wValue = cpu_to_le16(0x0200);
		control_req->wIndex = cpu_to_le16(0x0001);
		control_req->wLength = cpu_to_le16(0x0008);

		/* control pipe is endpoपूर्णांक 0x00 */
		pipe = usb_sndctrlpipe(ictx->usbdev_पूर्णांकf0, 0);

		/* build the control urb */
		usb_fill_control_urb(ictx->tx_urb, ictx->usbdev_पूर्णांकf0,
				     pipe, (अचिन्हित अक्षर *)control_req,
				     ictx->usb_tx_buf,
				     माप(ictx->usb_tx_buf),
				     usb_tx_callback, ictx);
		ictx->tx_urb->actual_length = 0;
	पूर्ण

	reinit_completion(&ictx->tx.finished);
	ictx->tx.busy = true;
	smp_rmb(); /* ensure later पढ़ोers know we're busy */

	retval = usb_submit_urb(ictx->tx_urb, GFP_KERNEL);
	अगर (retval) अणु
		ictx->tx.busy = false;
		smp_rmb(); /* ensure later पढ़ोers know we're not busy */
		pr_err_ratelimited("error submitting urb(%d)\n", retval);
	पूर्ण अन्यथा अणु
		/* Wait क्रम transmission to complete (or पात) */
		mutex_unlock(&ictx->lock);
		retval = रुको_क्रम_completion_पूर्णांकerruptible(
				&ictx->tx.finished);
		अगर (retval) अणु
			usb_समाप्त_urb(ictx->tx_urb);
			pr_err_ratelimited("task interrupted\n");
		पूर्ण
		mutex_lock(&ictx->lock);

		retval = ictx->tx.status;
		अगर (retval)
			pr_err_ratelimited("packet tx failed (%d)\n", retval);
	पूर्ण

	kमुक्त(control_req);

	/*
	 * Induce a mandatory delay beक्रमe वापसing, as otherwise,
	 * send_packet can get called so rapidly as to overwhelm the device,
	 * particularly on faster प्रणालीs and/or those with quirky usb.
	 */
	समयout = msecs_to_jअगरfies(ictx->send_packet_delay);
	set_current_state(TASK_INTERRUPTIBLE);
	schedule_समयout(समयout);

	वापस retval;
पूर्ण

/*
 * Sends an associate packet to the iMON 2.4G.
 *
 * This might not be such a good idea, since it has an id collision with
 * some versions of the "IR & VFD" combo. The only way to determine अगर it
 * is an RF version is to look at the product description string. (Which
 * we currently करो not fetch).
 */
अटल पूर्णांक send_associate_24g(काष्ठा imon_context *ictx)
अणु
	पूर्णांक retval;
	स्थिर अचिन्हित अक्षर packet[8] = अणु 0x01, 0x00, 0x00, 0x00,
					  0x00, 0x00, 0x00, 0x20 पूर्ण;

	अगर (!ictx) अणु
		pr_err("no context for device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!ictx->dev_present_पूर्णांकf0) अणु
		pr_err("no iMON device present\n");
		वापस -ENODEV;
	पूर्ण

	स_नकल(ictx->usb_tx_buf, packet, माप(packet));
	retval = send_packet(ictx);

	वापस retval;
पूर्ण

/*
 * Sends packets to setup and show घड़ी on iMON display
 *
 * Arguments: year - last 2 digits of year, month - 1..12,
 * day - 1..31, करोw - day of the week (0-Sun...6-Sat),
 * hour - 0..23, minute - 0..59, second - 0..59
 */
अटल पूर्णांक send_set_imon_घड़ी(काष्ठा imon_context *ictx,
			       अचिन्हित पूर्णांक year, अचिन्हित पूर्णांक month,
			       अचिन्हित पूर्णांक day, अचिन्हित पूर्णांक करोw,
			       अचिन्हित पूर्णांक hour, अचिन्हित पूर्णांक minute,
			       अचिन्हित पूर्णांक second)
अणु
	अचिन्हित अक्षर घड़ी_enable_pkt[IMON_CLOCK_ENABLE_PACKETS][8];
	पूर्णांक retval = 0;
	पूर्णांक i;

	अगर (!ictx) अणु
		pr_err("no context for device\n");
		वापस -ENODEV;
	पूर्ण

	चयन (ictx->display_type) अणु
	हाल IMON_DISPLAY_TYPE_LCD:
		घड़ी_enable_pkt[0][0] = 0x80;
		घड़ी_enable_pkt[0][1] = year;
		घड़ी_enable_pkt[0][2] = month-1;
		घड़ी_enable_pkt[0][3] = day;
		घड़ी_enable_pkt[0][4] = hour;
		घड़ी_enable_pkt[0][5] = minute;
		घड़ी_enable_pkt[0][6] = second;

		घड़ी_enable_pkt[1][0] = 0x80;
		घड़ी_enable_pkt[1][1] = 0;
		घड़ी_enable_pkt[1][2] = 0;
		घड़ी_enable_pkt[1][3] = 0;
		घड़ी_enable_pkt[1][4] = 0;
		घड़ी_enable_pkt[1][5] = 0;
		घड़ी_enable_pkt[1][6] = 0;

		अगर (ictx->product == 0xffdc) अणु
			घड़ी_enable_pkt[0][7] = 0x50;
			घड़ी_enable_pkt[1][7] = 0x51;
		पूर्ण अन्यथा अणु
			घड़ी_enable_pkt[0][7] = 0x88;
			घड़ी_enable_pkt[1][7] = 0x8a;
		पूर्ण

		अवरोध;

	हाल IMON_DISPLAY_TYPE_VFD:
		घड़ी_enable_pkt[0][0] = year;
		घड़ी_enable_pkt[0][1] = month-1;
		घड़ी_enable_pkt[0][2] = day;
		घड़ी_enable_pkt[0][3] = करोw;
		घड़ी_enable_pkt[0][4] = hour;
		घड़ी_enable_pkt[0][5] = minute;
		घड़ी_enable_pkt[0][6] = second;
		घड़ी_enable_pkt[0][7] = 0x40;

		घड़ी_enable_pkt[1][0] = 0;
		घड़ी_enable_pkt[1][1] = 0;
		घड़ी_enable_pkt[1][2] = 1;
		घड़ी_enable_pkt[1][3] = 0;
		घड़ी_enable_pkt[1][4] = 0;
		घड़ी_enable_pkt[1][5] = 0;
		घड़ी_enable_pkt[1][6] = 0;
		घड़ी_enable_pkt[1][7] = 0x42;

		अवरोध;

	शेष:
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < IMON_CLOCK_ENABLE_PACKETS; i++) अणु
		स_नकल(ictx->usb_tx_buf, घड़ी_enable_pkt[i], 8);
		retval = send_packet(ictx);
		अगर (retval) अणु
			pr_err("send_packet failed for packet %d\n", i);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

/*
 * These are the sysfs functions to handle the association on the iMON 2.4G LT.
 */
अटल sमाप_प्रकार show_associate_remote(काष्ठा device *d,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा imon_context *ictx = dev_get_drvdata(d);

	अगर (!ictx)
		वापस -ENODEV;

	mutex_lock(&ictx->lock);
	अगर (ictx->rf_isassociating)
		strscpy(buf, "associating\n", PAGE_SIZE);
	अन्यथा
		strscpy(buf, "closed\n", PAGE_SIZE);

	dev_info(d, "Visit https://www.lirc.org/html/imon-24g.html for instructions on how to associate your iMON 2.4G DT/LT remote\n");
	mutex_unlock(&ictx->lock);
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार store_associate_remote(काष्ठा device *d,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा imon_context *ictx;

	ictx = dev_get_drvdata(d);

	अगर (!ictx)
		वापस -ENODEV;

	mutex_lock(&ictx->lock);
	ictx->rf_isassociating = true;
	send_associate_24g(ictx);
	mutex_unlock(&ictx->lock);

	वापस count;
पूर्ण

/*
 * sysfs functions to control पूर्णांकernal imon घड़ी
 */
अटल sमाप_प्रकार show_imon_घड़ी(काष्ठा device *d,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा imon_context *ictx = dev_get_drvdata(d);
	माप_प्रकार len;

	अगर (!ictx)
		वापस -ENODEV;

	mutex_lock(&ictx->lock);

	अगर (!ictx->display_supported) अणु
		len = snम_लिखो(buf, PAGE_SIZE, "Not supported.");
	पूर्ण अन्यथा अणु
		len = snम_लिखो(buf, PAGE_SIZE,
			"To set the clock on your iMON display:\n"
			"# date \"+%%y %%m %%d %%w %%H %%M %%S\" > imon_clock\n"
			"%s", ictx->display_isखोलो ?
			"\nNOTE: imon device must be closed\n" : "");
	पूर्ण

	mutex_unlock(&ictx->lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार store_imon_घड़ी(काष्ठा device *d,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा imon_context *ictx = dev_get_drvdata(d);
	sमाप_प्रकार retval;
	अचिन्हित पूर्णांक year, month, day, करोw, hour, minute, second;

	अगर (!ictx)
		वापस -ENODEV;

	mutex_lock(&ictx->lock);

	अगर (!ictx->display_supported) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण अन्यथा अगर (ictx->display_isखोलो) अणु
		retval = -EBUSY;
		जाओ निकास;
	पूर्ण

	अगर (माला_पूछो(buf, "%u %u %u %u %u %u %u",	&year, &month, &day, &करोw,
		   &hour, &minute, &second) != 7) अणु
		retval = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर ((month < 1 || month > 12) ||
	    (day < 1 || day > 31) || (करोw > 6) ||
	    (hour > 23) || (minute > 59) || (second > 59)) अणु
		retval = -EINVAL;
		जाओ निकास;
	पूर्ण

	retval = send_set_imon_घड़ी(ictx, year, month, day, करोw,
				     hour, minute, second);
	अगर (retval)
		जाओ निकास;

	retval = count;
निकास:
	mutex_unlock(&ictx->lock);

	वापस retval;
पूर्ण


अटल DEVICE_ATTR(imon_घड़ी, S_IWUSR | S_IRUGO, show_imon_घड़ी,
		   store_imon_घड़ी);

अटल DEVICE_ATTR(associate_remote, S_IWUSR | S_IRUGO, show_associate_remote,
		   store_associate_remote);

अटल काष्ठा attribute *imon_display_sysfs_entries[] = अणु
	&dev_attr_imon_घड़ी.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group imon_display_attr_group = अणु
	.attrs = imon_display_sysfs_entries
पूर्ण;

अटल काष्ठा attribute *imon_rf_sysfs_entries[] = अणु
	&dev_attr_associate_remote.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group imon_rf_attr_group = अणु
	.attrs = imon_rf_sysfs_entries
पूर्ण;

/*
 * Writes data to the VFD.  The iMON VFD is 2x16 अक्षरacters
 * and requires data in 5 consecutive USB पूर्णांकerrupt packets,
 * each packet but the last carrying 7 bytes.
 *
 * I करोn't know अगर the VFD board supports features such as
 * scrolling, clearing rows, blanking, etc. so at
 * the caller must provide a full screen of data.  If fewer
 * than 32 bytes are provided spaces will be appended to
 * generate a full screen.
 */
अटल sमाप_प्रकार vfd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार n_bytes, loff_t *pos)
अणु
	पूर्णांक i;
	पूर्णांक offset;
	पूर्णांक seq;
	पूर्णांक retval = 0;
	काष्ठा imon_context *ictx;
	अटल स्थिर अचिन्हित अक्षर vfd_packet6[] = अणु
		0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF पूर्ण;

	ictx = file->निजी_data;
	अगर (!ictx) अणु
		pr_err_ratelimited("no context for device\n");
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&ictx->lock);

	अगर (!ictx->dev_present_पूर्णांकf0) अणु
		pr_err_ratelimited("no iMON device present\n");
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	अगर (n_bytes <= 0 || n_bytes > 32) अणु
		pr_err_ratelimited("invalid payload size\n");
		retval = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (copy_from_user(ictx->tx.data_buf, buf, n_bytes)) अणु
		retval = -EFAULT;
		जाओ निकास;
	पूर्ण

	/* Pad with spaces */
	क्रम (i = n_bytes; i < 32; ++i)
		ictx->tx.data_buf[i] = ' ';

	क्रम (i = 32; i < 35; ++i)
		ictx->tx.data_buf[i] = 0xFF;

	offset = 0;
	seq = 0;

	करो अणु
		स_नकल(ictx->usb_tx_buf, ictx->tx.data_buf + offset, 7);
		ictx->usb_tx_buf[7] = (अचिन्हित अक्षर) seq;

		retval = send_packet(ictx);
		अगर (retval) अणु
			pr_err_ratelimited("send packet #%d failed\n", seq / 2);
			जाओ निकास;
		पूर्ण अन्यथा अणु
			seq += 2;
			offset += 7;
		पूर्ण

	पूर्ण जबतक (offset < 35);

	/* Send packet #6 */
	स_नकल(ictx->usb_tx_buf, &vfd_packet6, माप(vfd_packet6));
	ictx->usb_tx_buf[7] = (अचिन्हित अक्षर) seq;
	retval = send_packet(ictx);
	अगर (retval)
		pr_err_ratelimited("send packet #%d failed\n", seq / 2);

निकास:
	mutex_unlock(&ictx->lock);

	वापस (!retval) ? n_bytes : retval;
पूर्ण

/*
 * Writes data to the LCD.  The iMON OEM LCD screen expects 8-byte
 * packets. We accept data as 16 hexadecimal digits, followed by a
 * newline (to make it easy to drive the device from a command-line
 * -- even though the actual binary data is a bit complicated).
 *
 * The device itself is not a "traditional" text-mode display. It's
 * actually a 16x96 pixel biपंचांगap display. That means अगर you want to
 * display text, you've got to have your own "font" and translate the
 * text पूर्णांकo biपंचांगaps क्रम display. This is really flexible (you can
 * display whatever diacritics you need, and so on), but it's also
 * a lot more complicated than most LCDs...
 */
अटल sमाप_प्रकार lcd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार n_bytes, loff_t *pos)
अणु
	पूर्णांक retval = 0;
	काष्ठा imon_context *ictx;

	ictx = file->निजी_data;
	अगर (!ictx) अणु
		pr_err_ratelimited("no context for device\n");
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&ictx->lock);

	अगर (!ictx->display_supported) अणु
		pr_err_ratelimited("no iMON display present\n");
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	अगर (n_bytes != 8) अणु
		pr_err_ratelimited("invalid payload size: %d (expected 8)\n",
				   (पूर्णांक)n_bytes);
		retval = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (copy_from_user(ictx->usb_tx_buf, buf, 8)) अणु
		retval = -EFAULT;
		जाओ निकास;
	पूर्ण

	retval = send_packet(ictx);
	अगर (retval) अणु
		pr_err_ratelimited("send packet failed!\n");
		जाओ निकास;
	पूर्ण अन्यथा अणु
		dev_dbg(ictx->dev, "%s: write %d bytes to LCD\n",
			__func__, (पूर्णांक) n_bytes);
	पूर्ण
निकास:
	mutex_unlock(&ictx->lock);
	वापस (!retval) ? n_bytes : retval;
पूर्ण

/*
 * Callback function क्रम USB core API: transmit data
 */
अटल व्योम usb_tx_callback(काष्ठा urb *urb)
अणु
	काष्ठा imon_context *ictx;

	अगर (!urb)
		वापस;
	ictx = (काष्ठा imon_context *)urb->context;
	अगर (!ictx)
		वापस;

	ictx->tx.status = urb->status;

	/* notअगरy रुकोers that ग_लिखो has finished */
	ictx->tx.busy = false;
	smp_rmb(); /* ensure later पढ़ोers know we're not busy */
	complete(&ictx->tx.finished);
पूर्ण

/*
 * report touchscreen input
 */
अटल व्योम imon_touch_display_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा imon_context *ictx = from_समयr(ictx, t, tसमयr);

	अगर (ictx->display_type != IMON_DISPLAY_TYPE_VGA)
		वापस;

	input_report_असल(ictx->touch, ABS_X, ictx->touch_x);
	input_report_असल(ictx->touch, ABS_Y, ictx->touch_y);
	input_report_key(ictx->touch, BTN_TOUCH, 0x00);
	input_sync(ictx->touch);
पूर्ण

/*
 * iMON IR receivers support two dअगरferent संकेत sets -- those used by
 * the iMON remotes, and those used by the Winकरोws MCE remotes (which is
 * really just RC-6), but only one or the other at a समय, as the संकेतs
 * are decoded onboard the receiver.
 *
 * This function माला_लो called two dअगरferent ways, one way is from
 * rc_रेजिस्टर_device, क्रम initial protocol selection/setup, and the other is
 * via a userspace-initiated protocol change request, either by direct sysfs
 * prodding or by something like ir-keytable. In the rc_रेजिस्टर_device हाल,
 * the imon context lock is alपढ़ोy held, but when initiated from userspace,
 * it is not, so we must acquire it prior to calling send_packet, which
 * requires that the lock is held.
 */
अटल पूर्णांक imon_ir_change_protocol(काष्ठा rc_dev *rc, u64 *rc_proto)
अणु
	पूर्णांक retval;
	काष्ठा imon_context *ictx = rc->priv;
	काष्ठा device *dev = ictx->dev;
	bool unlock = false;
	अचिन्हित अक्षर ir_proto_packet[] = अणु
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86 पूर्ण;

	अगर (*rc_proto && !(*rc_proto & rc->allowed_protocols))
		dev_warn(dev, "Looks like you're trying to use an IR protocol this device does not support\n");

	अगर (*rc_proto & RC_PROTO_BIT_RC6_MCE) अणु
		dev_dbg(dev, "Configuring IR receiver for MCE protocol\n");
		ir_proto_packet[0] = 0x01;
		*rc_proto = RC_PROTO_BIT_RC6_MCE;
	पूर्ण अन्यथा अगर (*rc_proto & RC_PROTO_BIT_IMON) अणु
		dev_dbg(dev, "Configuring IR receiver for iMON protocol\n");
		अगर (!pad_stabilize)
			dev_dbg(dev, "PAD stabilize functionality disabled\n");
		/* ir_proto_packet[0] = 0x00; // alपढ़ोy the शेष */
		*rc_proto = RC_PROTO_BIT_IMON;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Unsupported IR protocol specified, overriding to iMON IR protocol\n");
		अगर (!pad_stabilize)
			dev_dbg(dev, "PAD stabilize functionality disabled\n");
		/* ir_proto_packet[0] = 0x00; // alपढ़ोy the शेष */
		*rc_proto = RC_PROTO_BIT_IMON;
	पूर्ण

	स_नकल(ictx->usb_tx_buf, &ir_proto_packet, माप(ir_proto_packet));

	अगर (!mutex_is_locked(&ictx->lock)) अणु
		unlock = true;
		mutex_lock(&ictx->lock);
	पूर्ण

	retval = send_packet(ictx);
	अगर (retval)
		जाओ out;

	ictx->rc_proto = *rc_proto;
	ictx->pad_mouse = false;

out:
	अगर (unlock)
		mutex_unlock(&ictx->lock);

	वापस retval;
पूर्ण

/*
 * The directional pad behaves a bit dअगरferently, depending on whether this is
 * one of the older ffdc devices or a newer device. Newer devices appear to
 * have a higher resolution matrix क्रम more precise mouse movement, but it
 * makes things overly sensitive in keyboard mode, so we करो some पूर्णांकeresting
 * contortions to make it less touchy. Older devices run through the same
 * routine with लघुer समयout and a smaller threshold.
 */
अटल पूर्णांक stabilize(पूर्णांक a, पूर्णांक b, u16 समयout, u16 threshold)
अणु
	kसमय_प्रकार ct;
	अटल kसमय_प्रकार prev_समय;
	अटल kसमय_प्रकार hit_समय;
	अटल पूर्णांक x, y, prev_result, hits;
	पूर्णांक result = 0;
	दीर्घ msec, msec_hit;

	ct = kसमय_get();
	msec = kसमय_ms_delta(ct, prev_समय);
	msec_hit = kसमय_ms_delta(ct, hit_समय);

	अगर (msec > 100) अणु
		x = 0;
		y = 0;
		hits = 0;
	पूर्ण

	x += a;
	y += b;

	prev_समय = ct;

	अगर (असल(x) > threshold || असल(y) > threshold) अणु
		अगर (असल(y) > असल(x))
			result = (y > 0) ? 0x7F : 0x80;
		अन्यथा
			result = (x > 0) ? 0x7F00 : 0x8000;

		x = 0;
		y = 0;

		अगर (result == prev_result) अणु
			hits++;

			अगर (hits > 3) अणु
				चयन (result) अणु
				हाल 0x7F:
					y = 17 * threshold / 30;
					अवरोध;
				हाल 0x80:
					y -= 17 * threshold / 30;
					अवरोध;
				हाल 0x7F00:
					x = 17 * threshold / 30;
					अवरोध;
				हाल 0x8000:
					x -= 17 * threshold / 30;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (hits == 2 && msec_hit < समयout) अणु
				result = 0;
				hits = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			prev_result = result;
			hits = 1;
			hit_समय = ct;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल u32 imon_remote_key_lookup(काष्ठा imon_context *ictx, u32 scancode)
अणु
	u32 keycode;
	u32 release;
	bool is_release_code = false;

	/* Look क्रम the initial press of a button */
	keycode = rc_g_keycode_from_table(ictx->rdev, scancode);
	ictx->rc_toggle = 0x0;
	ictx->rc_scancode = scancode;

	/* Look क्रम the release of a button */
	अगर (keycode == KEY_RESERVED) अणु
		release = scancode & ~0x4000;
		keycode = rc_g_keycode_from_table(ictx->rdev, release);
		अगर (keycode != KEY_RESERVED)
			is_release_code = true;
	पूर्ण

	ictx->release_code = is_release_code;

	वापस keycode;
पूर्ण

अटल u32 imon_mce_key_lookup(काष्ठा imon_context *ictx, u32 scancode)
अणु
	u32 keycode;

#घोषणा MCE_KEY_MASK 0x7000
#घोषणा MCE_TOGGLE_BIT 0x8000

	/*
	 * On some receivers, mce keys decode to 0x8000f04xx and 0x8000f84xx
	 * (the toggle bit flipping between alternating key presses), जबतक
	 * on other receivers, we see 0x8000f74xx and 0x8000ff4xx. To keep
	 * the table trim, we always or in the bits to look up 0x8000ff4xx,
	 * but we can't or them पूर्णांकo all codes, as some keys are decoded in
	 * a dअगरferent way w/o the same use of the toggle bit...
	 */
	अगर (scancode & 0x80000000)
		scancode = scancode | MCE_KEY_MASK | MCE_TOGGLE_BIT;

	ictx->rc_scancode = scancode;
	keycode = rc_g_keycode_from_table(ictx->rdev, scancode);

	/* not used in mce mode, but make sure we know its false */
	ictx->release_code = false;

	वापस keycode;
पूर्ण

अटल u32 imon_panel_key_lookup(काष्ठा imon_context *ictx, u64 code)
अणु
	स्थिर काष्ठा imon_panel_key_table *key_table;
	u32 keycode = KEY_RESERVED;
	पूर्णांक i;

	key_table = ictx->dev_descr->key_table;

	क्रम (i = 0; key_table[i].hw_code != 0; i++) अणु
		अगर (key_table[i].hw_code == (code | 0xffee)) अणु
			keycode = key_table[i].keycode;
			अवरोध;
		पूर्ण
	पूर्ण
	ictx->release_code = false;
	वापस keycode;
पूर्ण

अटल bool imon_mouse_event(काष्ठा imon_context *ictx,
			     अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	चिन्हित अक्षर rel_x = 0x00, rel_y = 0x00;
	u8 right_shअगरt = 1;
	bool mouse_input = true;
	पूर्णांक dir = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ictx->kc_lock, flags);

	/* newer iMON device PAD or mouse button */
	अगर (ictx->product != 0xffdc && (buf[0] & 0x01) && len == 5) अणु
		rel_x = buf[2];
		rel_y = buf[3];
		right_shअगरt = 1;
	/* 0xffdc iMON PAD or mouse button input */
	पूर्ण अन्यथा अगर (ictx->product == 0xffdc && (buf[0] & 0x40) &&
			!((buf[1] & 0x01) || ((buf[1] >> 2) & 0x01))) अणु
		rel_x = (buf[1] & 0x08) | (buf[1] & 0x10) >> 2 |
			(buf[1] & 0x20) >> 4 | (buf[1] & 0x40) >> 6;
		अगर (buf[0] & 0x02)
			rel_x |= ~0x0f;
		rel_x = rel_x + rel_x / 2;
		rel_y = (buf[2] & 0x08) | (buf[2] & 0x10) >> 2 |
			(buf[2] & 0x20) >> 4 | (buf[2] & 0x40) >> 6;
		अगर (buf[0] & 0x01)
			rel_y |= ~0x0f;
		rel_y = rel_y + rel_y / 2;
		right_shअगरt = 2;
	/* some ffdc devices decode mouse buttons dअगरferently... */
	पूर्ण अन्यथा अगर (ictx->product == 0xffdc && (buf[0] == 0x68)) अणु
		right_shअगरt = 2;
	/* ch+/- buttons, which we use क्रम an emulated scroll wheel */
	पूर्ण अन्यथा अगर (ictx->kc == KEY_CHANNELUP && (buf[2] & 0x40) != 0x40) अणु
		dir = 1;
	पूर्ण अन्यथा अगर (ictx->kc == KEY_CHANNELDOWN && (buf[2] & 0x40) != 0x40) अणु
		dir = -1;
	पूर्ण अन्यथा
		mouse_input = false;

	spin_unlock_irqrestore(&ictx->kc_lock, flags);

	अगर (mouse_input) अणु
		dev_dbg(ictx->dev, "sending mouse data via input subsystem\n");

		अगर (dir) अणु
			input_report_rel(ictx->idev, REL_WHEEL, dir);
		पूर्ण अन्यथा अगर (rel_x || rel_y) अणु
			input_report_rel(ictx->idev, REL_X, rel_x);
			input_report_rel(ictx->idev, REL_Y, rel_y);
		पूर्ण अन्यथा अणु
			input_report_key(ictx->idev, BTN_LEFT, buf[1] & 0x1);
			input_report_key(ictx->idev, BTN_RIGHT,
					 buf[1] >> right_shअगरt & 0x1);
		पूर्ण
		input_sync(ictx->idev);
		spin_lock_irqsave(&ictx->kc_lock, flags);
		ictx->last_keycode = ictx->kc;
		spin_unlock_irqrestore(&ictx->kc_lock, flags);
	पूर्ण

	वापस mouse_input;
पूर्ण

अटल व्योम imon_touch_event(काष्ठा imon_context *ictx, अचिन्हित अक्षर *buf)
अणु
	mod_समयr(&ictx->tसमयr, jअगरfies + TOUCH_TIMEOUT);
	ictx->touch_x = (buf[0] << 4) | (buf[1] >> 4);
	ictx->touch_y = 0xfff - ((buf[2] << 4) | (buf[1] & 0xf));
	input_report_असल(ictx->touch, ABS_X, ictx->touch_x);
	input_report_असल(ictx->touch, ABS_Y, ictx->touch_y);
	input_report_key(ictx->touch, BTN_TOUCH, 0x01);
	input_sync(ictx->touch);
पूर्ण

अटल व्योम imon_pad_to_keys(काष्ठा imon_context *ictx, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक dir = 0;
	चिन्हित अक्षर rel_x = 0x00, rel_y = 0x00;
	u16 समयout, threshold;
	u32 scancode = KEY_RESERVED;
	अचिन्हित दीर्घ flags;

	/*
	 * The imon directional pad functions more like a touchpad. Bytes 3 & 4
	 * contain a position coordinate (x,y), with each component ranging
	 * from -14 to 14. We want to करोwn-sample this to only 4 discrete values
	 * क्रम up/करोwn/left/right arrow keys. Also, when you get too बंद to
	 * diagonals, it has a tendency to jump back and क्रमth, so lets try to
	 * ignore when they get too बंद.
	 */
	अगर (ictx->product != 0xffdc) अणु
		/* first, pad to 8 bytes so it conक्रमms with everything अन्यथा */
		buf[5] = buf[6] = buf[7] = 0;
		समयout = 500;	/* in msecs */
		/* (2*threshold) x (2*threshold) square */
		threshold = pad_thresh ? pad_thresh : 28;
		rel_x = buf[2];
		rel_y = buf[3];

		अगर (ictx->rc_proto == RC_PROTO_BIT_IMON && pad_stabilize) अणु
			अगर ((buf[1] == 0) && ((rel_x != 0) || (rel_y != 0))) अणु
				dir = stabilize((पूर्णांक)rel_x, (पूर्णांक)rel_y,
						समयout, threshold);
				अगर (!dir) अणु
					spin_lock_irqsave(&ictx->kc_lock,
							  flags);
					ictx->kc = KEY_UNKNOWN;
					spin_unlock_irqrestore(&ictx->kc_lock,
							       flags);
					वापस;
				पूर्ण
				buf[2] = dir & 0xFF;
				buf[3] = (dir >> 8) & 0xFF;
				scancode = be32_to_cpu(*((__be32 *)buf));
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Hack alert: instead of using keycodes, we have
			 * to use hard-coded scancodes here...
			 */
			अगर (असल(rel_y) > असल(rel_x)) अणु
				buf[2] = (rel_y > 0) ? 0x7F : 0x80;
				buf[3] = 0;
				अगर (rel_y > 0)
					scancode = 0x01007f00; /* KEY_DOWN */
				अन्यथा
					scancode = 0x01008000; /* KEY_UP */
			पूर्ण अन्यथा अणु
				buf[2] = 0;
				buf[3] = (rel_x > 0) ? 0x7F : 0x80;
				अगर (rel_x > 0)
					scancode = 0x0100007f; /* KEY_RIGHT */
				अन्यथा
					scancode = 0x01000080; /* KEY_LEFT */
			पूर्ण
		पूर्ण

	/*
	 * Handle on-board decoded pad events क्रम e.g. older VFD/iMON-Pad
	 * device (15c2:ffdc). The remote generates various codes from
	 * 0x68nnnnB7 to 0x6AnnnnB7, the left mouse button generates
	 * 0x688301b7 and the right one 0x688481b7. All other keys generate
	 * 0x2nnnnnnn. Position coordinate is encoded in buf[1] and buf[2] with
	 * reversed endianness. Extract direction from buffer, rotate endianness,
	 * adjust sign and feed the values पूर्णांकo stabilize(). The resulting codes
	 * will be 0x01008000, 0x01007F00, which match the newer devices.
	 */
	पूर्ण अन्यथा अणु
		समयout = 10;	/* in msecs */
		/* (2*threshold) x (2*threshold) square */
		threshold = pad_thresh ? pad_thresh : 15;

		/* buf[1] is x */
		rel_x = (buf[1] & 0x08) | (buf[1] & 0x10) >> 2 |
			(buf[1] & 0x20) >> 4 | (buf[1] & 0x40) >> 6;
		अगर (buf[0] & 0x02)
			rel_x |= ~0x10+1;
		/* buf[2] is y */
		rel_y = (buf[2] & 0x08) | (buf[2] & 0x10) >> 2 |
			(buf[2] & 0x20) >> 4 | (buf[2] & 0x40) >> 6;
		अगर (buf[0] & 0x01)
			rel_y |= ~0x10+1;

		buf[0] = 0x01;
		buf[1] = buf[4] = buf[5] = buf[6] = buf[7] = 0;

		अगर (ictx->rc_proto == RC_PROTO_BIT_IMON && pad_stabilize) अणु
			dir = stabilize((पूर्णांक)rel_x, (पूर्णांक)rel_y,
					समयout, threshold);
			अगर (!dir) अणु
				spin_lock_irqsave(&ictx->kc_lock, flags);
				ictx->kc = KEY_UNKNOWN;
				spin_unlock_irqrestore(&ictx->kc_lock, flags);
				वापस;
			पूर्ण
			buf[2] = dir & 0xFF;
			buf[3] = (dir >> 8) & 0xFF;
			scancode = be32_to_cpu(*((__be32 *)buf));
		पूर्ण अन्यथा अणु
			/*
			 * Hack alert: instead of using keycodes, we have
			 * to use hard-coded scancodes here...
			 */
			अगर (असल(rel_y) > असल(rel_x)) अणु
				buf[2] = (rel_y > 0) ? 0x7F : 0x80;
				buf[3] = 0;
				अगर (rel_y > 0)
					scancode = 0x01007f00; /* KEY_DOWN */
				अन्यथा
					scancode = 0x01008000; /* KEY_UP */
			पूर्ण अन्यथा अणु
				buf[2] = 0;
				buf[3] = (rel_x > 0) ? 0x7F : 0x80;
				अगर (rel_x > 0)
					scancode = 0x0100007f; /* KEY_RIGHT */
				अन्यथा
					scancode = 0x01000080; /* KEY_LEFT */
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (scancode) अणु
		spin_lock_irqsave(&ictx->kc_lock, flags);
		ictx->kc = imon_remote_key_lookup(ictx, scancode);
		spin_unlock_irqrestore(&ictx->kc_lock, flags);
	पूर्ण
पूर्ण

/*
 * figure out अगर these is a press or a release. We करोn't actually
 * care about repeats, as those will be स्वतः-generated within the IR
 * subप्रणाली क्रम repeating scancodes.
 */
अटल पूर्णांक imon_parse_press_type(काष्ठा imon_context *ictx,
				 अचिन्हित अक्षर *buf, u8 ktype)
अणु
	पूर्णांक press_type = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ictx->kc_lock, flags);

	/* key release of 0x02XXXXXX key */
	अगर (ictx->kc == KEY_RESERVED && buf[0] == 0x02 && buf[3] == 0x00)
		ictx->kc = ictx->last_keycode;

	/* mouse button release on (some) 0xffdc devices */
	अन्यथा अगर (ictx->kc == KEY_RESERVED && buf[0] == 0x68 && buf[1] == 0x82 &&
		 buf[2] == 0x81 && buf[3] == 0xb7)
		ictx->kc = ictx->last_keycode;

	/* mouse button release on (some other) 0xffdc devices */
	अन्यथा अगर (ictx->kc == KEY_RESERVED && buf[0] == 0x01 && buf[1] == 0x00 &&
		 buf[2] == 0x81 && buf[3] == 0xb7)
		ictx->kc = ictx->last_keycode;

	/* mce-specअगरic button handling, no keyup events */
	अन्यथा अगर (ktype == IMON_KEY_MCE) अणु
		ictx->rc_toggle = buf[2];
		press_type = 1;

	/* incoherent or irrelevant data */
	पूर्ण अन्यथा अगर (ictx->kc == KEY_RESERVED)
		press_type = -EINVAL;

	/* key release of 0xXXXXXXb7 key */
	अन्यथा अगर (ictx->release_code)
		press_type = 0;

	/* this is a button press */
	अन्यथा
		press_type = 1;

	spin_unlock_irqrestore(&ictx->kc_lock, flags);

	वापस press_type;
पूर्ण

/*
 * Process the incoming packet
 */
अटल व्योम imon_incoming_packet(काष्ठा imon_context *ictx,
				 काष्ठा urb *urb, पूर्णांक पूर्णांकf)
अणु
	पूर्णांक len = urb->actual_length;
	अचिन्हित अक्षर *buf = urb->transfer_buffer;
	काष्ठा device *dev = ictx->dev;
	अचिन्हित दीर्घ flags;
	u32 kc;
	u64 scancode;
	पूर्णांक press_type = 0;
	kसमय_प्रकार t;
	अटल kसमय_प्रकार prev_समय;
	u8 ktype;

	/* filter out junk data on the older 0xffdc imon devices */
	अगर ((buf[0] == 0xff) && (buf[1] == 0xff) && (buf[2] == 0xff))
		वापस;

	/* Figure out what key was pressed */
	अगर (len == 8 && buf[7] == 0xee) अणु
		scancode = be64_to_cpu(*((__be64 *)buf));
		ktype = IMON_KEY_PANEL;
		kc = imon_panel_key_lookup(ictx, scancode);
		ictx->release_code = false;
	पूर्ण अन्यथा अणु
		scancode = be32_to_cpu(*((__be32 *)buf));
		अगर (ictx->rc_proto == RC_PROTO_BIT_RC6_MCE) अणु
			ktype = IMON_KEY_IMON;
			अगर (buf[0] == 0x80)
				ktype = IMON_KEY_MCE;
			kc = imon_mce_key_lookup(ictx, scancode);
		पूर्ण अन्यथा अणु
			ktype = IMON_KEY_IMON;
			kc = imon_remote_key_lookup(ictx, scancode);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&ictx->kc_lock, flags);
	/* keyboard/mouse mode toggle button */
	अगर (kc == KEY_KEYBOARD && !ictx->release_code) अणु
		ictx->last_keycode = kc;
		अगर (!nomouse) अणु
			ictx->pad_mouse = !ictx->pad_mouse;
			dev_dbg(dev, "toggling to %s mode\n",
				ictx->pad_mouse ? "mouse" : "keyboard");
			spin_unlock_irqrestore(&ictx->kc_lock, flags);
			वापस;
		पूर्ण अन्यथा अणु
			ictx->pad_mouse = false;
			dev_dbg(dev, "mouse mode disabled, passing key value\n");
		पूर्ण
	पूर्ण

	ictx->kc = kc;
	spin_unlock_irqrestore(&ictx->kc_lock, flags);

	/* send touchscreen events through input subप्रणाली अगर touchpad data */
	अगर (ictx->touch && len == 8 && buf[7] == 0x86) अणु
		imon_touch_event(ictx, buf);
		वापस;

	/* look क्रम mouse events with pad in mouse mode */
	पूर्ण अन्यथा अगर (ictx->pad_mouse) अणु
		अगर (imon_mouse_event(ictx, buf, len))
			वापस;
	पूर्ण

	/* Now क्रम some special handling to convert pad input to arrow keys */
	अगर (((len == 5) && (buf[0] == 0x01) && (buf[4] == 0x00)) ||
	    ((len == 8) && (buf[0] & 0x40) &&
	     !(buf[1] & 0x1 || buf[1] >> 2 & 0x1))) अणु
		len = 8;
		imon_pad_to_keys(ictx, buf);
	पूर्ण

	अगर (debug) अणु
		prपूर्णांकk(KERN_INFO "intf%d decoded packet: %*ph\n",
		       पूर्णांकf, len, buf);
	पूर्ण

	press_type = imon_parse_press_type(ictx, buf, ktype);
	अगर (press_type < 0)
		जाओ not_input_data;

	अगर (ktype != IMON_KEY_PANEL) अणु
		अगर (press_type == 0)
			rc_keyup(ictx->rdev);
		अन्यथा अणु
			क्रमागत rc_proto proto;

			अगर (ictx->rc_proto == RC_PROTO_BIT_RC6_MCE)
				proto = RC_PROTO_RC6_MCE;
			अन्यथा अगर (ictx->rc_proto == RC_PROTO_BIT_IMON)
				proto = RC_PROTO_IMON;
			अन्यथा
				वापस;

			rc_keyकरोwn(ictx->rdev, proto, ictx->rc_scancode,
				   ictx->rc_toggle);

			spin_lock_irqsave(&ictx->kc_lock, flags);
			ictx->last_keycode = ictx->kc;
			spin_unlock_irqrestore(&ictx->kc_lock, flags);
		पूर्ण
		वापस;
	पूर्ण

	/* Only panel type events left to process now */
	spin_lock_irqsave(&ictx->kc_lock, flags);

	t = kसमय_get();
	/* KEY repeats from knob and panel that need to be suppressed */
	अगर (ictx->kc == KEY_MUTE ||
	    ictx->dev_descr->flags & IMON_SUPPRESS_REPEATED_KEYS) अणु
		अगर (ictx->kc == ictx->last_keycode &&
		    kसमय_ms_delta(t, prev_समय) < ictx->idev->rep[REP_DELAY]) अणु
			spin_unlock_irqrestore(&ictx->kc_lock, flags);
			वापस;
		पूर्ण
	पूर्ण

	prev_समय = t;
	kc = ictx->kc;

	spin_unlock_irqrestore(&ictx->kc_lock, flags);

	input_report_key(ictx->idev, kc, press_type);
	input_sync(ictx->idev);

	/* panel keys करोn't generate a release */
	input_report_key(ictx->idev, kc, 0);
	input_sync(ictx->idev);

	spin_lock_irqsave(&ictx->kc_lock, flags);
	ictx->last_keycode = kc;
	spin_unlock_irqrestore(&ictx->kc_lock, flags);

	वापस;

not_input_data:
	अगर (len != 8) अणु
		dev_warn(dev, "imon %s: invalid incoming packet size (len = %d, intf%d)\n",
			 __func__, len, पूर्णांकf);
		वापस;
	पूर्ण

	/* iMON 2.4G associate frame */
	अगर (buf[0] == 0x00 &&
	    buf[2] == 0xFF &&				/* REFID */
	    buf[3] == 0xFF &&
	    buf[4] == 0xFF &&
	    buf[5] == 0xFF &&				/* iMON 2.4G */
	   ((buf[6] == 0x4E && buf[7] == 0xDF) ||	/* LT */
	    (buf[6] == 0x5E && buf[7] == 0xDF))) अणु	/* DT */
		dev_warn(dev, "%s: remote associated refid=%02X\n",
			 __func__, buf[1]);
		ictx->rf_isassociating = false;
	पूर्ण
पूर्ण

/*
 * Callback function क्रम USB core API: receive data
 */
अटल व्योम usb_rx_callback_पूर्णांकf0(काष्ठा urb *urb)
अणु
	काष्ठा imon_context *ictx;
	पूर्णांक पूर्णांकfnum = 0;

	अगर (!urb)
		वापस;

	ictx = (काष्ठा imon_context *)urb->context;
	अगर (!ictx)
		वापस;

	/*
	 * अगर we get a callback beक्रमe we're करोne configuring the hardware, we
	 * can't yet process the data, as there's nowhere to send it, but we
	 * still need to submit a new rx URB to aव्योम wedging the hardware
	 */
	अगर (!ictx->dev_present_पूर्णांकf0)
		जाओ out;

	चयन (urb->status) अणु
	हाल -ENOENT:		/* usbcore unlink successful! */
		वापस;

	हाल -ESHUTDOWN:	/* transport endpoपूर्णांक was shut करोwn */
		अवरोध;

	हाल 0:
		imon_incoming_packet(ictx, urb, पूर्णांकfnum);
		अवरोध;

	शेष:
		dev_warn(ictx->dev, "imon %s: status(%d): ignored\n",
			 __func__, urb->status);
		अवरोध;
	पूर्ण

out:
	usb_submit_urb(ictx->rx_urb_पूर्णांकf0, GFP_ATOMIC);
पूर्ण

अटल व्योम usb_rx_callback_पूर्णांकf1(काष्ठा urb *urb)
अणु
	काष्ठा imon_context *ictx;
	पूर्णांक पूर्णांकfnum = 1;

	अगर (!urb)
		वापस;

	ictx = (काष्ठा imon_context *)urb->context;
	अगर (!ictx)
		वापस;

	/*
	 * अगर we get a callback beक्रमe we're करोne configuring the hardware, we
	 * can't yet process the data, as there's nowhere to send it, but we
	 * still need to submit a new rx URB to aव्योम wedging the hardware
	 */
	अगर (!ictx->dev_present_पूर्णांकf1)
		जाओ out;

	चयन (urb->status) अणु
	हाल -ENOENT:		/* usbcore unlink successful! */
		वापस;

	हाल -ESHUTDOWN:	/* transport endpoपूर्णांक was shut करोwn */
		अवरोध;

	हाल 0:
		imon_incoming_packet(ictx, urb, पूर्णांकfnum);
		अवरोध;

	शेष:
		dev_warn(ictx->dev, "imon %s: status(%d): ignored\n",
			 __func__, urb->status);
		अवरोध;
	पूर्ण

out:
	usb_submit_urb(ictx->rx_urb_पूर्णांकf1, GFP_ATOMIC);
पूर्ण

/*
 * The 0x15c2:0xffdc device ID was used क्रम umpteen dअगरferent imon
 * devices, and all of them स्थिरantly spew पूर्णांकerrupts, even when there
 * is no actual data to report. However, byte 6 of this buffer looks like
 * its unique across device variants, so we're trying to key off that to
 * figure out which display type (अगर any) and what IR protocol the device
 * actually supports. These devices have their IR protocol hard-coded पूर्णांकo
 * their firmware, they can't be changed on the fly like the newer hardware.
 */
अटल व्योम imon_get_ffdc_type(काष्ठा imon_context *ictx)
अणु
	u8 ffdc_cfg_byte = ictx->usb_rx_buf[6];
	u8 detected_display_type = IMON_DISPLAY_TYPE_NONE;
	u64 allowed_protos = RC_PROTO_BIT_IMON;

	चयन (ffdc_cfg_byte) अणु
	/* iMON Knob, no display, iMON IR + vol knob */
	हाल 0x21:
		dev_info(ictx->dev, "0xffdc iMON Knob, iMON IR");
		ictx->display_supported = false;
		अवरोध;
	/* iMON 2.4G LT (usb stick), no display, iMON RF */
	हाल 0x4e:
		dev_info(ictx->dev, "0xffdc iMON 2.4G LT, iMON RF");
		ictx->display_supported = false;
		ictx->rf_device = true;
		अवरोध;
	/* iMON VFD, no IR (करोes have vol knob tho) */
	हाल 0x35:
		dev_info(ictx->dev, "0xffdc iMON VFD + knob, no IR");
		detected_display_type = IMON_DISPLAY_TYPE_VFD;
		अवरोध;
	/* iMON VFD, iMON IR */
	हाल 0x24:
	हाल 0x30:
	हाल 0x85:
		dev_info(ictx->dev, "0xffdc iMON VFD, iMON IR");
		detected_display_type = IMON_DISPLAY_TYPE_VFD;
		अवरोध;
	/* iMON VFD, MCE IR */
	हाल 0x46:
	हाल 0x9e:
		dev_info(ictx->dev, "0xffdc iMON VFD, MCE IR");
		detected_display_type = IMON_DISPLAY_TYPE_VFD;
		allowed_protos = RC_PROTO_BIT_RC6_MCE;
		अवरोध;
	/* iMON VFD, iMON or MCE IR */
	हाल 0x7e:
		dev_info(ictx->dev, "0xffdc iMON VFD, iMON or MCE IR");
		detected_display_type = IMON_DISPLAY_TYPE_VFD;
		allowed_protos |= RC_PROTO_BIT_RC6_MCE;
		अवरोध;
	/* iMON LCD, MCE IR */
	हाल 0x9f:
		dev_info(ictx->dev, "0xffdc iMON LCD, MCE IR");
		detected_display_type = IMON_DISPLAY_TYPE_LCD;
		allowed_protos = RC_PROTO_BIT_RC6_MCE;
		अवरोध;
	/* no display, iMON IR */
	हाल 0x26:
		dev_info(ictx->dev, "0xffdc iMON Inside, iMON IR");
		ictx->display_supported = false;
		अवरोध;
	/* Soundgraph iMON UltraBay */
	हाल 0x98:
		dev_info(ictx->dev, "0xffdc iMON UltraBay, LCD + IR");
		detected_display_type = IMON_DISPLAY_TYPE_LCD;
		allowed_protos = RC_PROTO_BIT_IMON | RC_PROTO_BIT_RC6_MCE;
		ictx->dev_descr = &ultrabay_table;
		अवरोध;

	शेष:
		dev_info(ictx->dev, "Unknown 0xffdc device, defaulting to VFD and iMON IR");
		detected_display_type = IMON_DISPLAY_TYPE_VFD;
		/*
		 * We करोn't know which one it is, allow user to set the
		 * RC6 one from userspace अगर IMON wasn't correct.
		 */
		allowed_protos |= RC_PROTO_BIT_RC6_MCE;
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_CONT " (id 0x%02x)\n", ffdc_cfg_byte);

	ictx->display_type = detected_display_type;
	ictx->rc_proto = allowed_protos;
पूर्ण

अटल व्योम imon_set_display_type(काष्ठा imon_context *ictx)
अणु
	u8 configured_display_type = IMON_DISPLAY_TYPE_VFD;

	/*
	 * Try to स्वतः-detect the type of display अगर the user hasn't set
	 * it by hand via the display_type modparam. Default is VFD.
	 */

	अगर (display_type == IMON_DISPLAY_TYPE_AUTO) अणु
		चयन (ictx->product) अणु
		हाल 0xffdc:
			/* set in imon_get_ffdc_type() */
			configured_display_type = ictx->display_type;
			अवरोध;
		हाल 0x0034:
		हाल 0x0035:
			configured_display_type = IMON_DISPLAY_TYPE_VGA;
			अवरोध;
		हाल 0x0038:
		हाल 0x0039:
		हाल 0x0045:
			configured_display_type = IMON_DISPLAY_TYPE_LCD;
			अवरोध;
		हाल 0x003c:
		हाल 0x0041:
		हाल 0x0042:
		हाल 0x0043:
			configured_display_type = IMON_DISPLAY_TYPE_NONE;
			ictx->display_supported = false;
			अवरोध;
		हाल 0x0036:
		हाल 0x0044:
		शेष:
			configured_display_type = IMON_DISPLAY_TYPE_VFD;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		configured_display_type = display_type;
		अगर (display_type == IMON_DISPLAY_TYPE_NONE)
			ictx->display_supported = false;
		अन्यथा
			ictx->display_supported = true;
		dev_info(ictx->dev, "%s: overriding display type to %d via modparam\n",
			 __func__, display_type);
	पूर्ण

	ictx->display_type = configured_display_type;
पूर्ण

अटल काष्ठा rc_dev *imon_init_rdev(काष्ठा imon_context *ictx)
अणु
	काष्ठा rc_dev *rdev;
	पूर्णांक ret;
	अटल स्थिर अचिन्हित अक्षर fp_packet[] = अणु
		0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88 पूर्ण;

	rdev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!rdev) अणु
		dev_err(ictx->dev, "remote control dev allocation failed\n");
		जाओ out;
	पूर्ण

	snम_लिखो(ictx->name_rdev, माप(ictx->name_rdev),
		 "iMON Remote (%04x:%04x)", ictx->venकरोr, ictx->product);
	usb_make_path(ictx->usbdev_पूर्णांकf0, ictx->phys_rdev,
		      माप(ictx->phys_rdev));
	strlcat(ictx->phys_rdev, "/input0", माप(ictx->phys_rdev));

	rdev->device_name = ictx->name_rdev;
	rdev->input_phys = ictx->phys_rdev;
	usb_to_input_id(ictx->usbdev_पूर्णांकf0, &rdev->input_id);
	rdev->dev.parent = ictx->dev;

	rdev->priv = ictx;
	/* iMON PAD or MCE */
	rdev->allowed_protocols = RC_PROTO_BIT_IMON | RC_PROTO_BIT_RC6_MCE;
	rdev->change_protocol = imon_ir_change_protocol;
	rdev->driver_name = MOD_NAME;

	/* Enable front-panel buttons and/or knobs */
	स_नकल(ictx->usb_tx_buf, &fp_packet, माप(fp_packet));
	ret = send_packet(ictx);
	/* Not fatal, but warn about it */
	अगर (ret)
		dev_info(ictx->dev, "panel buttons/knobs setup failed\n");

	अगर (ictx->product == 0xffdc) अणु
		imon_get_ffdc_type(ictx);
		rdev->allowed_protocols = ictx->rc_proto;
	पूर्ण

	imon_set_display_type(ictx);

	अगर (ictx->rc_proto == RC_PROTO_BIT_RC6_MCE)
		rdev->map_name = RC_MAP_IMON_MCE;
	अन्यथा
		rdev->map_name = RC_MAP_IMON_PAD;

	ret = rc_रेजिस्टर_device(rdev);
	अगर (ret < 0) अणु
		dev_err(ictx->dev, "remote input dev register failed\n");
		जाओ out;
	पूर्ण

	वापस rdev;

out:
	rc_मुक्त_device(rdev);
	वापस शून्य;
पूर्ण

अटल काष्ठा input_dev *imon_init_idev(काष्ठा imon_context *ictx)
अणु
	स्थिर काष्ठा imon_panel_key_table *key_table;
	काष्ठा input_dev *idev;
	पूर्णांक ret, i;

	key_table = ictx->dev_descr->key_table;

	idev = input_allocate_device();
	अगर (!idev)
		जाओ out;

	snम_लिखो(ictx->name_idev, माप(ictx->name_idev),
		 "iMON Panel, Knob and Mouse(%04x:%04x)",
		 ictx->venकरोr, ictx->product);
	idev->name = ictx->name_idev;

	usb_make_path(ictx->usbdev_पूर्णांकf0, ictx->phys_idev,
		      माप(ictx->phys_idev));
	strlcat(ictx->phys_idev, "/input1", माप(ictx->phys_idev));
	idev->phys = ictx->phys_idev;

	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP) | BIT_MASK(EV_REL);

	idev->keybit[BIT_WORD(BTN_MOUSE)] =
		BIT_MASK(BTN_LEFT) | BIT_MASK(BTN_RIGHT);
	idev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y) |
		BIT_MASK(REL_WHEEL);

	/* panel and/or knob code support */
	क्रम (i = 0; key_table[i].hw_code != 0; i++) अणु
		u32 kc = key_table[i].keycode;
		__set_bit(kc, idev->keybit);
	पूर्ण

	usb_to_input_id(ictx->usbdev_पूर्णांकf0, &idev->id);
	idev->dev.parent = ictx->dev;
	input_set_drvdata(idev, ictx);

	ret = input_रेजिस्टर_device(idev);
	अगर (ret < 0) अणु
		dev_err(ictx->dev, "input dev register failed\n");
		जाओ out;
	पूर्ण

	वापस idev;

out:
	input_मुक्त_device(idev);
	वापस शून्य;
पूर्ण

अटल काष्ठा input_dev *imon_init_touch(काष्ठा imon_context *ictx)
अणु
	काष्ठा input_dev *touch;
	पूर्णांक ret;

	touch = input_allocate_device();
	अगर (!touch)
		जाओ touch_alloc_failed;

	snम_लिखो(ictx->name_touch, माप(ictx->name_touch),
		 "iMON USB Touchscreen (%04x:%04x)",
		 ictx->venकरोr, ictx->product);
	touch->name = ictx->name_touch;

	usb_make_path(ictx->usbdev_पूर्णांकf1, ictx->phys_touch,
		      माप(ictx->phys_touch));
	strlcat(ictx->phys_touch, "/input2", माप(ictx->phys_touch));
	touch->phys = ictx->phys_touch;

	touch->evbit[0] =
		BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	touch->keybit[BIT_WORD(BTN_TOUCH)] =
		BIT_MASK(BTN_TOUCH);
	input_set_असल_params(touch, ABS_X,
			     0x00, 0xfff, 0, 0);
	input_set_असल_params(touch, ABS_Y,
			     0x00, 0xfff, 0, 0);

	input_set_drvdata(touch, ictx);

	usb_to_input_id(ictx->usbdev_पूर्णांकf1, &touch->id);
	touch->dev.parent = ictx->dev;
	ret = input_रेजिस्टर_device(touch);
	अगर (ret <  0) अणु
		dev_info(ictx->dev, "touchscreen input dev register failed\n");
		जाओ touch_रेजिस्टर_failed;
	पूर्ण

	वापस touch;

touch_रेजिस्टर_failed:
	input_मुक्त_device(touch);

touch_alloc_failed:
	वापस शून्य;
पूर्ण

अटल bool imon_find_endpoपूर्णांकs(काष्ठा imon_context *ictx,
				काष्ठा usb_host_पूर्णांकerface *अगरace_desc)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *rx_endpoपूर्णांक = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *tx_endpoपूर्णांक = शून्य;
	पूर्णांक अगरnum = अगरace_desc->desc.bInterfaceNumber;
	पूर्णांक num_endpts = अगरace_desc->desc.bNumEndpoपूर्णांकs;
	पूर्णांक i, ep_dir, ep_type;
	bool ir_ep_found = false;
	bool display_ep_found = false;
	bool tx_control = false;

	/*
	 * Scan the endpoपूर्णांक list and set:
	 *	first input endpoपूर्णांक = IR endpoपूर्णांक
	 *	first output endpoपूर्णांक = display endpoपूर्णांक
	 */
	क्रम (i = 0; i < num_endpts && !(ir_ep_found && display_ep_found); ++i) अणु
		ep = &अगरace_desc->endpoपूर्णांक[i].desc;
		ep_dir = ep->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK;
		ep_type = usb_endpoपूर्णांक_type(ep);

		अगर (!ir_ep_found && ep_dir == USB_सूची_IN &&
		    ep_type == USB_ENDPOINT_XFER_INT) अणु

			rx_endpoपूर्णांक = ep;
			ir_ep_found = true;
			dev_dbg(ictx->dev, "%s: found IR endpoint\n", __func__);

		पूर्ण अन्यथा अगर (!display_ep_found && ep_dir == USB_सूची_OUT &&
			   ep_type == USB_ENDPOINT_XFER_INT) अणु
			tx_endpoपूर्णांक = ep;
			display_ep_found = true;
			dev_dbg(ictx->dev, "%s: found display endpoint\n", __func__);
		पूर्ण
	पूर्ण

	अगर (अगरnum == 0) अणु
		ictx->rx_endpoपूर्णांक_पूर्णांकf0 = rx_endpoपूर्णांक;
		/*
		 * tx is used to send अक्षरacters to lcd/vfd, associate RF
		 * remotes, set IR protocol, and maybe more...
		 */
		ictx->tx_endpoपूर्णांक = tx_endpoपूर्णांक;
	पूर्ण अन्यथा अणु
		ictx->rx_endpoपूर्णांक_पूर्णांकf1 = rx_endpoपूर्णांक;
	पूर्ण

	/*
	 * If we didn't find a display endpoपूर्णांक, this is probably one of the
	 * newer iMON devices that use control urb instead of पूर्णांकerrupt
	 */
	अगर (!display_ep_found) अणु
		tx_control = true;
		display_ep_found = true;
		dev_dbg(ictx->dev, "%s: device uses control endpoint, not interface OUT endpoint\n",
			__func__);
	पूर्ण

	/*
	 * Some iMON receivers have no display. Unक्रमtunately, it seems
	 * that SoundGraph recycles device IDs between devices both with
	 * and without... :\
	 */
	अगर (ictx->display_type == IMON_DISPLAY_TYPE_NONE) अणु
		display_ep_found = false;
		dev_dbg(ictx->dev, "%s: device has no display\n", __func__);
	पूर्ण

	/*
	 * iMON Touch devices have a VGA touchscreen, but no "display", as
	 * that refers to e.g. /dev/lcd0 (a अक्षरacter device LCD or VFD).
	 */
	अगर (ictx->display_type == IMON_DISPLAY_TYPE_VGA) अणु
		display_ep_found = false;
		dev_dbg(ictx->dev, "%s: iMON Touch device found\n", __func__);
	पूर्ण

	/* Input endpoपूर्णांक is mandatory */
	अगर (!ir_ep_found)
		pr_err("no valid input (IR) endpoint found\n");

	ictx->tx_control = tx_control;

	अगर (display_ep_found)
		ictx->display_supported = true;

	वापस ir_ep_found;

पूर्ण

अटल काष्ठा imon_context *imon_init_पूर्णांकf0(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा imon_context *ictx;
	काष्ठा urb *rx_urb;
	काष्ठा urb *tx_urb;
	काष्ठा device *dev = &पूर्णांकf->dev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	पूर्णांक ret = -ENOMEM;

	ictx = kzalloc(माप(*ictx), GFP_KERNEL);
	अगर (!ictx)
		जाओ निकास;

	rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!rx_urb)
		जाओ rx_urb_alloc_failed;
	tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!tx_urb)
		जाओ tx_urb_alloc_failed;

	mutex_init(&ictx->lock);
	spin_lock_init(&ictx->kc_lock);

	mutex_lock(&ictx->lock);

	ictx->dev = dev;
	ictx->usbdev_पूर्णांकf0 = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));
	ictx->rx_urb_पूर्णांकf0 = rx_urb;
	ictx->tx_urb = tx_urb;
	ictx->rf_device = false;

	init_completion(&ictx->tx.finished);

	ictx->venकरोr  = le16_to_cpu(ictx->usbdev_पूर्णांकf0->descriptor.idVenकरोr);
	ictx->product = le16_to_cpu(ictx->usbdev_पूर्णांकf0->descriptor.idProduct);

	/* save drive info क्रम later accessing the panel/knob key table */
	ictx->dev_descr = (काष्ठा imon_usb_dev_descr *)id->driver_info;
	/* शेष send_packet delay is 5ms but some devices need more */
	ictx->send_packet_delay = ictx->dev_descr->flags &
				  IMON_NEED_20MS_PKT_DELAY ? 20 : 5;

	ret = -ENODEV;
	अगरace_desc = पूर्णांकf->cur_altsetting;
	अगर (!imon_find_endpoपूर्णांकs(ictx, अगरace_desc)) अणु
		जाओ find_endpoपूर्णांक_failed;
	पूर्ण

	usb_fill_पूर्णांक_urb(ictx->rx_urb_पूर्णांकf0, ictx->usbdev_पूर्णांकf0,
		usb_rcvपूर्णांकpipe(ictx->usbdev_पूर्णांकf0,
			ictx->rx_endpoपूर्णांक_पूर्णांकf0->bEndpoपूर्णांकAddress),
		ictx->usb_rx_buf, माप(ictx->usb_rx_buf),
		usb_rx_callback_पूर्णांकf0, ictx,
		ictx->rx_endpoपूर्णांक_पूर्णांकf0->bInterval);

	ret = usb_submit_urb(ictx->rx_urb_पूर्णांकf0, GFP_KERNEL);
	अगर (ret) अणु
		pr_err("usb_submit_urb failed for intf0 (%d)\n", ret);
		जाओ urb_submit_failed;
	पूर्ण

	ictx->idev = imon_init_idev(ictx);
	अगर (!ictx->idev) अणु
		dev_err(dev, "%s: input device setup failed\n", __func__);
		जाओ idev_setup_failed;
	पूर्ण

	ictx->rdev = imon_init_rdev(ictx);
	अगर (!ictx->rdev) अणु
		dev_err(dev, "%s: rc device setup failed\n", __func__);
		जाओ rdev_setup_failed;
	पूर्ण

	ictx->dev_present_पूर्णांकf0 = true;

	mutex_unlock(&ictx->lock);
	वापस ictx;

rdev_setup_failed:
	input_unरेजिस्टर_device(ictx->idev);
idev_setup_failed:
	usb_समाप्त_urb(ictx->rx_urb_पूर्णांकf0);
urb_submit_failed:
find_endpoपूर्णांक_failed:
	usb_put_dev(ictx->usbdev_पूर्णांकf0);
	mutex_unlock(&ictx->lock);
	usb_मुक्त_urb(tx_urb);
tx_urb_alloc_failed:
	usb_मुक्त_urb(rx_urb);
rx_urb_alloc_failed:
	kमुक्त(ictx);
निकास:
	dev_err(dev, "unable to initialize intf0, err %d\n", ret);

	वापस शून्य;
पूर्ण

अटल काष्ठा imon_context *imon_init_पूर्णांकf1(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					    काष्ठा imon_context *ictx)
अणु
	काष्ठा urb *rx_urb;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	पूर्णांक ret = -ENOMEM;

	rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!rx_urb)
		जाओ rx_urb_alloc_failed;

	mutex_lock(&ictx->lock);

	अगर (ictx->display_type == IMON_DISPLAY_TYPE_VGA) अणु
		समयr_setup(&ictx->tसमयr, imon_touch_display_समयout, 0);
	पूर्ण

	ictx->usbdev_पूर्णांकf1 = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));
	ictx->rx_urb_पूर्णांकf1 = rx_urb;

	ret = -ENODEV;
	अगरace_desc = पूर्णांकf->cur_altsetting;
	अगर (!imon_find_endpoपूर्णांकs(ictx, अगरace_desc))
		जाओ find_endpoपूर्णांक_failed;

	अगर (ictx->display_type == IMON_DISPLAY_TYPE_VGA) अणु
		ictx->touch = imon_init_touch(ictx);
		अगर (!ictx->touch)
			जाओ touch_setup_failed;
	पूर्ण अन्यथा
		ictx->touch = शून्य;

	usb_fill_पूर्णांक_urb(ictx->rx_urb_पूर्णांकf1, ictx->usbdev_पूर्णांकf1,
		usb_rcvपूर्णांकpipe(ictx->usbdev_पूर्णांकf1,
			ictx->rx_endpoपूर्णांक_पूर्णांकf1->bEndpoपूर्णांकAddress),
		ictx->usb_rx_buf, माप(ictx->usb_rx_buf),
		usb_rx_callback_पूर्णांकf1, ictx,
		ictx->rx_endpoपूर्णांक_पूर्णांकf1->bInterval);

	ret = usb_submit_urb(ictx->rx_urb_पूर्णांकf1, GFP_KERNEL);

	अगर (ret) अणु
		pr_err("usb_submit_urb failed for intf1 (%d)\n", ret);
		जाओ urb_submit_failed;
	पूर्ण

	ictx->dev_present_पूर्णांकf1 = true;

	mutex_unlock(&ictx->lock);
	वापस ictx;

urb_submit_failed:
	अगर (ictx->touch)
		input_unरेजिस्टर_device(ictx->touch);
touch_setup_failed:
find_endpoपूर्णांक_failed:
	usb_put_dev(ictx->usbdev_पूर्णांकf1);
	mutex_unlock(&ictx->lock);
	usb_मुक्त_urb(rx_urb);
rx_urb_alloc_failed:
	dev_err(ictx->dev, "unable to initialize intf1, err %d\n", ret);

	वापस शून्य;
पूर्ण

अटल व्योम imon_init_display(काष्ठा imon_context *ictx,
			      काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret;

	dev_dbg(ictx->dev, "Registering iMON display with sysfs\n");

	/* set up sysfs entry क्रम built-in घड़ी */
	ret = sysfs_create_group(&पूर्णांकf->dev.kobj, &imon_display_attr_group);
	अगर (ret)
		dev_err(ictx->dev, "Could not create display sysfs entries(%d)",
			ret);

	अगर (ictx->display_type == IMON_DISPLAY_TYPE_LCD)
		ret = usb_रेजिस्टर_dev(पूर्णांकf, &imon_lcd_class);
	अन्यथा
		ret = usb_रेजिस्टर_dev(पूर्णांकf, &imon_vfd_class);
	अगर (ret)
		/* Not a fatal error, so ignore */
		dev_info(ictx->dev, "could not get a minor number for display\n");

पूर्ण

/*
 * Callback function क्रम USB core API: Probe
 */
अटल पूर्णांक imon_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		      स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usbdev = शून्य;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc = शून्य;
	काष्ठा usb_पूर्णांकerface *first_अगर;
	काष्ठा device *dev = &पूर्णांकerface->dev;
	पूर्णांक अगरnum, sysfs_err;
	पूर्णांक ret = 0;
	काष्ठा imon_context *ictx = शून्य;
	काष्ठा imon_context *first_अगर_ctx = शून्य;
	u16 venकरोr, product;

	usbdev     = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	अगरnum      = अगरace_desc->desc.bInterfaceNumber;
	venकरोr     = le16_to_cpu(usbdev->descriptor.idVenकरोr);
	product    = le16_to_cpu(usbdev->descriptor.idProduct);

	dev_dbg(dev, "%s: found iMON device (%04x:%04x, intf%d)\n",
		__func__, venकरोr, product, अगरnum);

	/* prevent races probing devices w/multiple पूर्णांकerfaces */
	mutex_lock(&driver_lock);

	first_अगर = usb_अगरnum_to_अगर(usbdev, 0);
	अगर (!first_अगर) अणु
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	first_अगर_ctx = usb_get_पूर्णांकfdata(first_अगर);

	अगर (अगरnum == 0) अणु
		ictx = imon_init_पूर्णांकf0(पूर्णांकerface, id);
		अगर (!ictx) अणु
			pr_err("failed to initialize context!\n");
			ret = -ENODEV;
			जाओ fail;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* this is the secondary पूर्णांकerface on the device */

		/* fail early अगर first पूर्णांकf failed to रेजिस्टर */
		अगर (!first_अगर_ctx) अणु
			ret = -ENODEV;
			जाओ fail;
		पूर्ण

		ictx = imon_init_पूर्णांकf1(पूर्णांकerface, first_अगर_ctx);
		अगर (!ictx) अणु
			pr_err("failed to attach to context!\n");
			ret = -ENODEV;
			जाओ fail;
		पूर्ण

	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकerface, ictx);

	अगर (अगरnum == 0) अणु
		mutex_lock(&ictx->lock);

		अगर (product == 0xffdc && ictx->rf_device) अणु
			sysfs_err = sysfs_create_group(&पूर्णांकerface->dev.kobj,
						       &imon_rf_attr_group);
			अगर (sysfs_err)
				pr_err("Could not create RF sysfs entries(%d)\n",
				       sysfs_err);
		पूर्ण

		अगर (ictx->display_supported)
			imon_init_display(ictx, पूर्णांकerface);

		mutex_unlock(&ictx->lock);
	पूर्ण

	dev_info(dev, "iMON device (%04x:%04x, intf%d) on usb<%d:%d> initialized\n",
		 venकरोr, product, अगरnum,
		 usbdev->bus->busnum, usbdev->devnum);

	mutex_unlock(&driver_lock);
	usb_put_dev(usbdev);

	वापस 0;

fail:
	mutex_unlock(&driver_lock);
	usb_put_dev(usbdev);
	dev_err(dev, "unable to register, err %d\n", ret);

	वापस ret;
पूर्ण

/*
 * Callback function क्रम USB core API: disconnect
 */
अटल व्योम imon_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा imon_context *ictx;
	काष्ठा device *dev;
	पूर्णांक अगरnum;

	/* prevent races with multi-पूर्णांकerface device probing and display_खोलो */
	mutex_lock(&driver_lock);

	ictx = usb_get_पूर्णांकfdata(पूर्णांकerface);
	dev = ictx->dev;
	अगरnum = पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;

	/*
	 * sysfs_हटाओ_group is safe to call even अगर sysfs_create_group
	 * hasn't been called
	 */
	sysfs_हटाओ_group(&पूर्णांकerface->dev.kobj, &imon_display_attr_group);
	sysfs_हटाओ_group(&पूर्णांकerface->dev.kobj, &imon_rf_attr_group);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	/* Abort ongoing ग_लिखो */
	अगर (ictx->tx.busy) अणु
		usb_समाप्त_urb(ictx->tx_urb);
		complete(&ictx->tx.finished);
	पूर्ण

	अगर (अगरnum == 0) अणु
		ictx->dev_present_पूर्णांकf0 = false;
		usb_समाप्त_urb(ictx->rx_urb_पूर्णांकf0);
		usb_put_dev(ictx->usbdev_पूर्णांकf0);
		input_unरेजिस्टर_device(ictx->idev);
		rc_unरेजिस्टर_device(ictx->rdev);
		अगर (ictx->display_supported) अणु
			अगर (ictx->display_type == IMON_DISPLAY_TYPE_LCD)
				usb_deरेजिस्टर_dev(पूर्णांकerface, &imon_lcd_class);
			अन्यथा अगर (ictx->display_type == IMON_DISPLAY_TYPE_VFD)
				usb_deरेजिस्टर_dev(पूर्णांकerface, &imon_vfd_class);
		पूर्ण
	पूर्ण अन्यथा अणु
		ictx->dev_present_पूर्णांकf1 = false;
		usb_समाप्त_urb(ictx->rx_urb_पूर्णांकf1);
		usb_put_dev(ictx->usbdev_पूर्णांकf1);
		अगर (ictx->display_type == IMON_DISPLAY_TYPE_VGA) अणु
			input_unरेजिस्टर_device(ictx->touch);
			del_समयr_sync(&ictx->tसमयr);
		पूर्ण
	पूर्ण

	अगर (!ictx->dev_present_पूर्णांकf0 && !ictx->dev_present_पूर्णांकf1)
		मुक्त_imon_context(ictx);

	mutex_unlock(&driver_lock);

	dev_dbg(dev, "%s: iMON device (intf%d) disconnected\n",
		__func__, अगरnum);
पूर्ण

अटल पूर्णांक imon_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा imon_context *ictx = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक अगरnum = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	अगर (अगरnum == 0)
		usb_समाप्त_urb(ictx->rx_urb_पूर्णांकf0);
	अन्यथा
		usb_समाप्त_urb(ictx->rx_urb_पूर्णांकf1);

	वापस 0;
पूर्ण

अटल पूर्णांक imon_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक rc = 0;
	काष्ठा imon_context *ictx = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक अगरnum = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	अगर (अगरnum == 0) अणु
		usb_fill_पूर्णांक_urb(ictx->rx_urb_पूर्णांकf0, ictx->usbdev_पूर्णांकf0,
			usb_rcvपूर्णांकpipe(ictx->usbdev_पूर्णांकf0,
				ictx->rx_endpoपूर्णांक_पूर्णांकf0->bEndpoपूर्णांकAddress),
			ictx->usb_rx_buf, माप(ictx->usb_rx_buf),
			usb_rx_callback_पूर्णांकf0, ictx,
			ictx->rx_endpoपूर्णांक_पूर्णांकf0->bInterval);

		rc = usb_submit_urb(ictx->rx_urb_पूर्णांकf0, GFP_ATOMIC);

	पूर्ण अन्यथा अणु
		usb_fill_पूर्णांक_urb(ictx->rx_urb_पूर्णांकf1, ictx->usbdev_पूर्णांकf1,
			usb_rcvपूर्णांकpipe(ictx->usbdev_पूर्णांकf1,
				ictx->rx_endpoपूर्णांक_पूर्णांकf1->bEndpoपूर्णांकAddress),
			ictx->usb_rx_buf, माप(ictx->usb_rx_buf),
			usb_rx_callback_पूर्णांकf1, ictx,
			ictx->rx_endpoपूर्णांक_पूर्णांकf1->bInterval);

		rc = usb_submit_urb(ictx->rx_urb_पूर्णांकf1, GFP_ATOMIC);
	पूर्ण

	वापस rc;
पूर्ण

module_usb_driver(imon_driver);
