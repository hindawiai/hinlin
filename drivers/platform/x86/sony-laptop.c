<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ACPI Sony Notebook Control Driver (SNC and SPIC)
 *
 * Copyright (C) 2004-2005 Stelian Pop <stelian@popies.net>
 * Copyright (C) 2007-2009 Mattia Dongili <malattia@linux.it>
 *
 * Parts of this driver inspired from asus_acpi.c and ibm_acpi.c
 * which are copyrighted by their respective authors.
 *
 * The SNY6001 driver part is based on the sonypi driver which includes
 * material from:
 *
 * Copyright (C) 2001-2005 Stelian Pop <stelian@popies.net>
 *
 * Copyright (C) 2005 Narayanan R S <nars@kadamba.org>
 *
 * Copyright (C) 2001-2002 Alcथखve <www.alcove.com>
 *
 * Copyright (C) 2001 Michael Ashley <m.ashley@unsw.edu.au>
 *
 * Copyright (C) 2001 Junichi Morita <jun1m@mars.dti.ne.jp>
 *
 * Copyright (C) 2000 Takaya Kinjo <t-kinjo@tc4.so-net.ne.jp>
 *
 * Copyright (C) 2000 Andrew Tridgell <tridge@valinux.com>
 *
 * Earlier work by Werner Almesberger, Paul `Rusty' Russell and Paul Mackerras.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/backlight.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sonypi.h>
#समावेश <linux/sony-laptop.h>
#समावेश <linux/rfसमाप्त.h>
#अगर_घोषित CONFIG_SONYPI_COMPAT
#समावेश <linux/poll.h>
#समावेश <linux/miscdevice.h>
#पूर्ण_अगर
#समावेश <linux/uaccess.h>
#समावेश <acpi/video.h>

#घोषणा dprपूर्णांकk(fmt, ...)			\
करो अणु						\
	अगर (debug)				\
		pr_warn(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा SONY_NC_CLASS		"sony-nc"
#घोषणा SONY_NC_HID		"SNY5001"
#घोषणा SONY_NC_DRIVER_NAME	"Sony Notebook Control Driver"

#घोषणा SONY_PIC_CLASS		"sony-pic"
#घोषणा SONY_PIC_HID		"SNY6001"
#घोषणा SONY_PIC_DRIVER_NAME	"Sony Programmable IO Control Driver"

MODULE_AUTHOR("Stelian Pop, Mattia Dongili");
MODULE_DESCRIPTION("Sony laptop extras driver (SPIC and SNC ACPI device)");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "set this to 1 (and RTFM) if you want to help "
		 "the development of this driver");

अटल पूर्णांक no_spic;		/* = 0 */
module_param(no_spic, पूर्णांक, 0444);
MODULE_PARM_DESC(no_spic,
		 "set this if you don't want to enable the SPIC device");

अटल पूर्णांक compat;		/* = 0 */
module_param(compat, पूर्णांक, 0444);
MODULE_PARM_DESC(compat,
		 "set this if you want to enable backward compatibility mode");

अटल अचिन्हित दीर्घ mask = 0xffffffff;
module_param(mask, uदीर्घ, 0644);
MODULE_PARM_DESC(mask,
		 "set this to the mask of event you want to enable (see doc)");

अटल पूर्णांक camera;		/* = 0 */
module_param(camera, पूर्णांक, 0444);
MODULE_PARM_DESC(camera,
		 "set this to 1 to enable Motion Eye camera controls "
		 "(only use it if you have a C1VE or C1VN model)");

#अगर_घोषित CONFIG_SONYPI_COMPAT
अटल पूर्णांक minor = -1;
module_param(minor, पूर्णांक, 0);
MODULE_PARM_DESC(minor,
		 "minor number of the misc device for the SPIC compatibility code, "
		 "default is -1 (automatic)");
#पूर्ण_अगर

अटल पूर्णांक kbd_backlight = -1;
module_param(kbd_backlight, पूर्णांक, 0444);
MODULE_PARM_DESC(kbd_backlight,
		 "set this to 0 to disable keyboard backlight, "
		 "1 to enable it with automatic control and 2 to have it always "
		 "on (default: no change from current value)");

अटल पूर्णांक kbd_backlight_समयout = -1;
module_param(kbd_backlight_समयout, पूर्णांक, 0444);
MODULE_PARM_DESC(kbd_backlight_समयout,
		 "meaningful values vary from 0 to 3 and their meaning depends "
		 "on the model (default: no change from current value)");

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम sony_nc_thermal_resume(व्योम);
#पूर्ण_अगर
अटल पूर्णांक sony_nc_kbd_backlight_setup(काष्ठा platक्रमm_device *pd,
		अचिन्हित पूर्णांक handle);
अटल व्योम sony_nc_kbd_backlight_cleanup(काष्ठा platक्रमm_device *pd,
		अचिन्हित पूर्णांक handle);

अटल पूर्णांक sony_nc_battery_care_setup(काष्ठा platक्रमm_device *pd,
		अचिन्हित पूर्णांक handle);
अटल व्योम sony_nc_battery_care_cleanup(काष्ठा platक्रमm_device *pd);

अटल पूर्णांक sony_nc_thermal_setup(काष्ठा platक्रमm_device *pd);
अटल व्योम sony_nc_thermal_cleanup(काष्ठा platक्रमm_device *pd);

अटल पूर्णांक sony_nc_lid_resume_setup(काष्ठा platक्रमm_device *pd,
				    अचिन्हित पूर्णांक handle);
अटल व्योम sony_nc_lid_resume_cleanup(काष्ठा platक्रमm_device *pd);

अटल पूर्णांक sony_nc_gfx_चयन_setup(काष्ठा platक्रमm_device *pd,
		अचिन्हित पूर्णांक handle);
अटल व्योम sony_nc_gfx_चयन_cleanup(काष्ठा platक्रमm_device *pd);
अटल पूर्णांक __sony_nc_gfx_चयन_status_get(व्योम);

अटल पूर्णांक sony_nc_highspeed_अक्षरging_setup(काष्ठा platक्रमm_device *pd);
अटल व्योम sony_nc_highspeed_अक्षरging_cleanup(काष्ठा platक्रमm_device *pd);

अटल पूर्णांक sony_nc_lowbatt_setup(काष्ठा platक्रमm_device *pd);
अटल व्योम sony_nc_lowbatt_cleanup(काष्ठा platक्रमm_device *pd);

अटल पूर्णांक sony_nc_fanspeed_setup(काष्ठा platक्रमm_device *pd);
अटल व्योम sony_nc_fanspeed_cleanup(काष्ठा platक्रमm_device *pd);

अटल पूर्णांक sony_nc_usb_अक्षरge_setup(काष्ठा platक्रमm_device *pd);
अटल व्योम sony_nc_usb_अक्षरge_cleanup(काष्ठा platक्रमm_device *pd);

अटल पूर्णांक sony_nc_panelid_setup(काष्ठा platक्रमm_device *pd);
अटल व्योम sony_nc_panelid_cleanup(काष्ठा platक्रमm_device *pd);

अटल पूर्णांक sony_nc_smart_conn_setup(काष्ठा platक्रमm_device *pd);
अटल व्योम sony_nc_smart_conn_cleanup(काष्ठा platक्रमm_device *pd);

अटल पूर्णांक sony_nc_touchpad_setup(काष्ठा platक्रमm_device *pd,
				  अचिन्हित पूर्णांक handle);
अटल व्योम sony_nc_touchpad_cleanup(काष्ठा platक्रमm_device *pd);

क्रमागत sony_nc_rfसमाप्त अणु
	SONY_WIFI,
	SONY_BLUETOOTH,
	SONY_WWAN,
	SONY_WIMAX,
	N_SONY_RFKILL,
पूर्ण;

अटल पूर्णांक sony_rfसमाप्त_handle;
अटल काष्ठा rfसमाप्त *sony_rfसमाप्त_devices[N_SONY_RFKILL];
अटल पूर्णांक sony_rfसमाप्त_address[N_SONY_RFKILL] = अणु0x300, 0x500, 0x700, 0x900पूर्ण;
अटल पूर्णांक sony_nc_rfसमाप्त_setup(काष्ठा acpi_device *device,
		अचिन्हित पूर्णांक handle);
अटल व्योम sony_nc_rfसमाप्त_cleanup(व्योम);
अटल व्योम sony_nc_rfसमाप्त_update(व्योम);

/*********** Input Devices ***********/

#घोषणा SONY_LAPTOP_BUF_SIZE	128
काष्ठा sony_laptop_input_s अणु
	atomic_t		users;
	काष्ठा input_dev	*jog_dev;
	काष्ठा input_dev	*key_dev;
	काष्ठा kfअगरo		fअगरo;
	spinlock_t		fअगरo_lock;
	काष्ठा समयr_list	release_key_समयr;
पूर्ण;

अटल काष्ठा sony_laptop_input_s sony_laptop_input = अणु
	.users = ATOMIC_INIT(0),
पूर्ण;

काष्ठा sony_laptop_keypress अणु
	काष्ठा input_dev *dev;
	पूर्णांक key;
पूर्ण;

/* Correspondance table between sonypi events
 * and input layer indexes in the keymap
 */
अटल स्थिर पूर्णांक sony_laptop_input_index[] = अणु
	-1,	/*  0 no event */
	-1,	/*  1 SONYPI_EVENT_JOGDIAL_DOWN */
	-1,	/*  2 SONYPI_EVENT_JOGDIAL_UP */
	-1,	/*  3 SONYPI_EVENT_JOGDIAL_DOWN_PRESSED */
	-1,	/*  4 SONYPI_EVENT_JOGDIAL_UP_PRESSED */
	-1,	/*  5 SONYPI_EVENT_JOGDIAL_PRESSED */
	-1,	/*  6 SONYPI_EVENT_JOGDIAL_RELEASED */
	 0,	/*  7 SONYPI_EVENT_CAPTURE_PRESSED */
	 1,	/*  8 SONYPI_EVENT_CAPTURE_RELEASED */
	 2,	/*  9 SONYPI_EVENT_CAPTURE_PARTIALPRESSED */
	 3,	/* 10 SONYPI_EVENT_CAPTURE_PARTIALRELEASED */
	 4,	/* 11 SONYPI_EVENT_FNKEY_ESC */
	 5,	/* 12 SONYPI_EVENT_FNKEY_F1 */
	 6,	/* 13 SONYPI_EVENT_FNKEY_F2 */
	 7,	/* 14 SONYPI_EVENT_FNKEY_F3 */
	 8,	/* 15 SONYPI_EVENT_FNKEY_F4 */
	 9,	/* 16 SONYPI_EVENT_FNKEY_F5 */
	10,	/* 17 SONYPI_EVENT_FNKEY_F6 */
	11,	/* 18 SONYPI_EVENT_FNKEY_F7 */
	12,	/* 19 SONYPI_EVENT_FNKEY_F8 */
	13,	/* 20 SONYPI_EVENT_FNKEY_F9 */
	14,	/* 21 SONYPI_EVENT_FNKEY_F10 */
	15,	/* 22 SONYPI_EVENT_FNKEY_F11 */
	16,	/* 23 SONYPI_EVENT_FNKEY_F12 */
	17,	/* 24 SONYPI_EVENT_FNKEY_1 */
	18,	/* 25 SONYPI_EVENT_FNKEY_2 */
	19,	/* 26 SONYPI_EVENT_FNKEY_D */
	20,	/* 27 SONYPI_EVENT_FNKEY_E */
	21,	/* 28 SONYPI_EVENT_FNKEY_F */
	22,	/* 29 SONYPI_EVENT_FNKEY_S */
	23,	/* 30 SONYPI_EVENT_FNKEY_B */
	24,	/* 31 SONYPI_EVENT_BLUETOOTH_PRESSED */
	25,	/* 32 SONYPI_EVENT_PKEY_P1 */
	26,	/* 33 SONYPI_EVENT_PKEY_P2 */
	27,	/* 34 SONYPI_EVENT_PKEY_P3 */
	28,	/* 35 SONYPI_EVENT_BACK_PRESSED */
	-1,	/* 36 SONYPI_EVENT_LID_CLOSED */
	-1,	/* 37 SONYPI_EVENT_LID_OPENED */
	29,	/* 38 SONYPI_EVENT_BLUETOOTH_ON */
	30,	/* 39 SONYPI_EVENT_BLUETOOTH_OFF */
	31,	/* 40 SONYPI_EVENT_HELP_PRESSED */
	32,	/* 41 SONYPI_EVENT_FNKEY_ONLY */
	33,	/* 42 SONYPI_EVENT_JOGDIAL_FAST_DOWN */
	34,	/* 43 SONYPI_EVENT_JOGDIAL_FAST_UP */
	35,	/* 44 SONYPI_EVENT_JOGDIAL_FAST_DOWN_PRESSED */
	36,	/* 45 SONYPI_EVENT_JOGDIAL_FAST_UP_PRESSED */
	37,	/* 46 SONYPI_EVENT_JOGDIAL_VFAST_DOWN */
	38,	/* 47 SONYPI_EVENT_JOGDIAL_VFAST_UP */
	39,	/* 48 SONYPI_EVENT_JOGDIAL_VFAST_DOWN_PRESSED */
	40,	/* 49 SONYPI_EVENT_JOGDIAL_VFAST_UP_PRESSED */
	41,	/* 50 SONYPI_EVENT_ZOOM_PRESSED */
	42,	/* 51 SONYPI_EVENT_THUMBPHRASE_PRESSED */
	43,	/* 52 SONYPI_EVENT_MEYE_FACE */
	44,	/* 53 SONYPI_EVENT_MEYE_OPPOSITE */
	45,	/* 54 SONYPI_EVENT_MEMORYSTICK_INSERT */
	46,	/* 55 SONYPI_EVENT_MEMORYSTICK_EJECT */
	-1,	/* 56 SONYPI_EVENT_ANYBUTTON_RELEASED */
	-1,	/* 57 SONYPI_EVENT_BATTERY_INSERT */
	-1,	/* 58 SONYPI_EVENT_BATTERY_REMOVE */
	-1,	/* 59 SONYPI_EVENT_FNKEY_RELEASED */
	47,	/* 60 SONYPI_EVENT_WIRELESS_ON */
	48,	/* 61 SONYPI_EVENT_WIRELESS_OFF */
	49,	/* 62 SONYPI_EVENT_ZOOM_IN_PRESSED */
	50,	/* 63 SONYPI_EVENT_ZOOM_OUT_PRESSED */
	51,	/* 64 SONYPI_EVENT_CD_EJECT_PRESSED */
	52,	/* 65 SONYPI_EVENT_MODEKEY_PRESSED */
	53,	/* 66 SONYPI_EVENT_PKEY_P4 */
	54,	/* 67 SONYPI_EVENT_PKEY_P5 */
	55,	/* 68 SONYPI_EVENT_SETTINGKEY_PRESSED */
	56,	/* 69 SONYPI_EVENT_VOLUME_INC_PRESSED */
	57,	/* 70 SONYPI_EVENT_VOLUME_DEC_PRESSED */
	-1,	/* 71 SONYPI_EVENT_BRIGHTNESS_PRESSED */
	58,	/* 72 SONYPI_EVENT_MEDIA_PRESSED */
	59,	/* 72 SONYPI_EVENT_VENDOR_PRESSED */
पूर्ण;

अटल पूर्णांक sony_laptop_input_keycode_map[] = अणु
	KEY_CAMERA,	/*  0 SONYPI_EVENT_CAPTURE_PRESSED */
	KEY_RESERVED,	/*  1 SONYPI_EVENT_CAPTURE_RELEASED */
	KEY_RESERVED,	/*  2 SONYPI_EVENT_CAPTURE_PARTIALPRESSED */
	KEY_RESERVED,	/*  3 SONYPI_EVENT_CAPTURE_PARTIALRELEASED */
	KEY_FN_ESC,	/*  4 SONYPI_EVENT_FNKEY_ESC */
	KEY_FN_F1,	/*  5 SONYPI_EVENT_FNKEY_F1 */
	KEY_FN_F2,	/*  6 SONYPI_EVENT_FNKEY_F2 */
	KEY_FN_F3,	/*  7 SONYPI_EVENT_FNKEY_F3 */
	KEY_FN_F4,	/*  8 SONYPI_EVENT_FNKEY_F4 */
	KEY_FN_F5,	/*  9 SONYPI_EVENT_FNKEY_F5 */
	KEY_FN_F6,	/* 10 SONYPI_EVENT_FNKEY_F6 */
	KEY_FN_F7,	/* 11 SONYPI_EVENT_FNKEY_F7 */
	KEY_FN_F8,	/* 12 SONYPI_EVENT_FNKEY_F8 */
	KEY_FN_F9,	/* 13 SONYPI_EVENT_FNKEY_F9 */
	KEY_FN_F10,	/* 14 SONYPI_EVENT_FNKEY_F10 */
	KEY_FN_F11,	/* 15 SONYPI_EVENT_FNKEY_F11 */
	KEY_FN_F12,	/* 16 SONYPI_EVENT_FNKEY_F12 */
	KEY_FN_1,	/* 17 SONYPI_EVENT_FNKEY_1 */
	KEY_FN_2,	/* 18 SONYPI_EVENT_FNKEY_2 */
	KEY_FN_D,	/* 19 SONYPI_EVENT_FNKEY_D */
	KEY_FN_E,	/* 20 SONYPI_EVENT_FNKEY_E */
	KEY_FN_F,	/* 21 SONYPI_EVENT_FNKEY_F */
	KEY_FN_S,	/* 22 SONYPI_EVENT_FNKEY_S */
	KEY_FN_B,	/* 23 SONYPI_EVENT_FNKEY_B */
	KEY_BLUETOOTH,	/* 24 SONYPI_EVENT_BLUETOOTH_PRESSED */
	KEY_PROG1,	/* 25 SONYPI_EVENT_PKEY_P1 */
	KEY_PROG2,	/* 26 SONYPI_EVENT_PKEY_P2 */
	KEY_PROG3,	/* 27 SONYPI_EVENT_PKEY_P3 */
	KEY_BACK,	/* 28 SONYPI_EVENT_BACK_PRESSED */
	KEY_BLUETOOTH,	/* 29 SONYPI_EVENT_BLUETOOTH_ON */
	KEY_BLUETOOTH,	/* 30 SONYPI_EVENT_BLUETOOTH_OFF */
	KEY_HELP,	/* 31 SONYPI_EVENT_HELP_PRESSED */
	KEY_FN,		/* 32 SONYPI_EVENT_FNKEY_ONLY */
	KEY_RESERVED,	/* 33 SONYPI_EVENT_JOGDIAL_FAST_DOWN */
	KEY_RESERVED,	/* 34 SONYPI_EVENT_JOGDIAL_FAST_UP */
	KEY_RESERVED,	/* 35 SONYPI_EVENT_JOGDIAL_FAST_DOWN_PRESSED */
	KEY_RESERVED,	/* 36 SONYPI_EVENT_JOGDIAL_FAST_UP_PRESSED */
	KEY_RESERVED,	/* 37 SONYPI_EVENT_JOGDIAL_VFAST_DOWN */
	KEY_RESERVED,	/* 38 SONYPI_EVENT_JOGDIAL_VFAST_UP */
	KEY_RESERVED,	/* 39 SONYPI_EVENT_JOGDIAL_VFAST_DOWN_PRESSED */
	KEY_RESERVED,	/* 40 SONYPI_EVENT_JOGDIAL_VFAST_UP_PRESSED */
	KEY_ZOOM,	/* 41 SONYPI_EVENT_ZOOM_PRESSED */
	BTN_THUMB,	/* 42 SONYPI_EVENT_THUMBPHRASE_PRESSED */
	KEY_RESERVED,	/* 43 SONYPI_EVENT_MEYE_FACE */
	KEY_RESERVED,	/* 44 SONYPI_EVENT_MEYE_OPPOSITE */
	KEY_RESERVED,	/* 45 SONYPI_EVENT_MEMORYSTICK_INSERT */
	KEY_RESERVED,	/* 46 SONYPI_EVENT_MEMORYSTICK_EJECT */
	KEY_WLAN,	/* 47 SONYPI_EVENT_WIRELESS_ON */
	KEY_WLAN,	/* 48 SONYPI_EVENT_WIRELESS_OFF */
	KEY_ZOOMIN,	/* 49 SONYPI_EVENT_ZOOM_IN_PRESSED */
	KEY_ZOOMOUT,	/* 50 SONYPI_EVENT_ZOOM_OUT_PRESSED */
	KEY_EJECTCD,	/* 51 SONYPI_EVENT_CD_EJECT_PRESSED */
	KEY_F13,	/* 52 SONYPI_EVENT_MODEKEY_PRESSED */
	KEY_PROG4,	/* 53 SONYPI_EVENT_PKEY_P4 */
	KEY_F14,	/* 54 SONYPI_EVENT_PKEY_P5 */
	KEY_F15,	/* 55 SONYPI_EVENT_SETTINGKEY_PRESSED */
	KEY_VOLUMEUP,	/* 56 SONYPI_EVENT_VOLUME_INC_PRESSED */
	KEY_VOLUMEDOWN,	/* 57 SONYPI_EVENT_VOLUME_DEC_PRESSED */
	KEY_MEDIA,	/* 58 SONYPI_EVENT_MEDIA_PRESSED */
	KEY_VENDOR,	/* 59 SONYPI_EVENT_VENDOR_PRESSED */
पूर्ण;

/* release buttons after a लघु delay अगर pressed */
अटल व्योम करो_sony_laptop_release_key(काष्ठा समयr_list *unused)
अणु
	काष्ठा sony_laptop_keypress kp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sony_laptop_input.fअगरo_lock, flags);

	अगर (kfअगरo_out(&sony_laptop_input.fअगरo,
		      (अचिन्हित अक्षर *)&kp, माप(kp)) == माप(kp)) अणु
		input_report_key(kp.dev, kp.key, 0);
		input_sync(kp.dev);
	पूर्ण

	/* If there is something in the fअगरo schedule next release. */
	अगर (kfअगरo_len(&sony_laptop_input.fअगरo) != 0)
		mod_समयr(&sony_laptop_input.release_key_समयr,
			  jअगरfies + msecs_to_jअगरfies(10));

	spin_unlock_irqrestore(&sony_laptop_input.fअगरo_lock, flags);
पूर्ण

/* क्रमward event to the input subप्रणाली */
अटल व्योम sony_laptop_report_input_event(u8 event)
अणु
	काष्ठा input_dev *jog_dev = sony_laptop_input.jog_dev;
	काष्ठा input_dev *key_dev = sony_laptop_input.key_dev;
	काष्ठा sony_laptop_keypress kp = अणु शून्य पूर्ण;
	पूर्णांक scancode = -1;

	अगर (event == SONYPI_EVENT_FNKEY_RELEASED ||
			event == SONYPI_EVENT_ANYBUTTON_RELEASED) अणु
		/* Nothing, not all VAIOs generate this event */
		वापस;
	पूर्ण

	/* report events */
	चयन (event) अणु
	/* jog_dev events */
	हाल SONYPI_EVENT_JOGDIAL_UP:
	हाल SONYPI_EVENT_JOGDIAL_UP_PRESSED:
		input_report_rel(jog_dev, REL_WHEEL, 1);
		input_sync(jog_dev);
		वापस;

	हाल SONYPI_EVENT_JOGDIAL_DOWN:
	हाल SONYPI_EVENT_JOGDIAL_DOWN_PRESSED:
		input_report_rel(jog_dev, REL_WHEEL, -1);
		input_sync(jog_dev);
		वापस;

	/* key_dev events */
	हाल SONYPI_EVENT_JOGDIAL_PRESSED:
		kp.key = BTN_MIDDLE;
		kp.dev = jog_dev;
		अवरोध;

	शेष:
		अगर (event >= ARRAY_SIZE(sony_laptop_input_index)) अणु
			dprपूर्णांकk("sony_laptop_report_input_event, event not known: %d\n", event);
			अवरोध;
		पूर्ण
		अगर ((scancode = sony_laptop_input_index[event]) != -1) अणु
			kp.key = sony_laptop_input_keycode_map[scancode];
			अगर (kp.key != KEY_UNKNOWN)
				kp.dev = key_dev;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (kp.dev) अणु
		/* अगर we have a scancode we emit it so we can always
		    remap the key */
		अगर (scancode != -1)
			input_event(kp.dev, EV_MSC, MSC_SCAN, scancode);
		input_report_key(kp.dev, kp.key, 1);
		input_sync(kp.dev);

		/* schedule key release */
		kfअगरo_in_locked(&sony_laptop_input.fअगरo,
				(अचिन्हित अक्षर *)&kp, माप(kp),
				&sony_laptop_input.fअगरo_lock);
		mod_समयr(&sony_laptop_input.release_key_समयr,
			  jअगरfies + msecs_to_jअगरfies(10));
	पूर्ण अन्यथा
		dprपूर्णांकk("unknown input event %.2x\n", event);
पूर्ण

अटल पूर्णांक sony_laptop_setup_input(काष्ठा acpi_device *acpi_device)
अणु
	काष्ठा input_dev *jog_dev;
	काष्ठा input_dev *key_dev;
	पूर्णांक i;
	पूर्णांक error;

	/* करोn't run again अगर alपढ़ोy initialized */
	अगर (atomic_add_वापस(1, &sony_laptop_input.users) > 1)
		वापस 0;

	/* kfअगरo */
	spin_lock_init(&sony_laptop_input.fअगरo_lock);
	error = kfअगरo_alloc(&sony_laptop_input.fअगरo,
			    SONY_LAPTOP_BUF_SIZE, GFP_KERNEL);
	अगर (error) अणु
		pr_err("kfifo_alloc failed\n");
		जाओ err_dec_users;
	पूर्ण

	समयr_setup(&sony_laptop_input.release_key_समयr,
		    करो_sony_laptop_release_key, 0);

	/* input keys */
	key_dev = input_allocate_device();
	अगर (!key_dev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_kfअगरo;
	पूर्ण

	key_dev->name = "Sony Vaio Keys";
	key_dev->id.bustype = BUS_ISA;
	key_dev->id.venकरोr = PCI_VENDOR_ID_SONY;
	key_dev->dev.parent = &acpi_device->dev;

	/* Initialize the Input Drivers: special keys */
	input_set_capability(key_dev, EV_MSC, MSC_SCAN);

	__set_bit(EV_KEY, key_dev->evbit);
	key_dev->keycodesize = माप(sony_laptop_input_keycode_map[0]);
	key_dev->keycodemax = ARRAY_SIZE(sony_laptop_input_keycode_map);
	key_dev->keycode = &sony_laptop_input_keycode_map;
	क्रम (i = 0; i < ARRAY_SIZE(sony_laptop_input_keycode_map); i++)
		__set_bit(sony_laptop_input_keycode_map[i], key_dev->keybit);
	__clear_bit(KEY_RESERVED, key_dev->keybit);

	error = input_रेजिस्टर_device(key_dev);
	अगर (error)
		जाओ err_मुक्त_keydev;

	sony_laptop_input.key_dev = key_dev;

	/* jogdial */
	jog_dev = input_allocate_device();
	अगर (!jog_dev) अणु
		error = -ENOMEM;
		जाओ err_unरेजिस्टर_keydev;
	पूर्ण

	jog_dev->name = "Sony Vaio Jogdial";
	jog_dev->id.bustype = BUS_ISA;
	jog_dev->id.venकरोr = PCI_VENDOR_ID_SONY;
	jog_dev->dev.parent = &acpi_device->dev;

	input_set_capability(jog_dev, EV_KEY, BTN_MIDDLE);
	input_set_capability(jog_dev, EV_REL, REL_WHEEL);

	error = input_रेजिस्टर_device(jog_dev);
	अगर (error)
		जाओ err_मुक्त_jogdev;

	sony_laptop_input.jog_dev = jog_dev;

	वापस 0;

err_मुक्त_jogdev:
	input_मुक्त_device(jog_dev);

err_unरेजिस्टर_keydev:
	input_unरेजिस्टर_device(key_dev);
	/* to aव्योम kref underflow below at input_मुक्त_device */
	key_dev = शून्य;

err_मुक्त_keydev:
	input_मुक्त_device(key_dev);

err_मुक्त_kfअगरo:
	kfअगरo_मुक्त(&sony_laptop_input.fअगरo);

err_dec_users:
	atomic_dec(&sony_laptop_input.users);
	वापस error;
पूर्ण

अटल व्योम sony_laptop_हटाओ_input(व्योम)
अणु
	काष्ठा sony_laptop_keypress kp = अणु शून्य पूर्ण;

	/* Cleanup only after the last user has gone */
	अगर (!atomic_dec_and_test(&sony_laptop_input.users))
		वापस;

	del_समयr_sync(&sony_laptop_input.release_key_समयr);

	/*
	 * Generate key-up events क्रम reमुख्यing keys. Note that we करोn't
	 * need locking since nobody is adding new events to the kfअगरo.
	 */
	जबतक (kfअगरo_out(&sony_laptop_input.fअगरo,
			 (अचिन्हित अक्षर *)&kp, माप(kp)) == माप(kp)) अणु
		input_report_key(kp.dev, kp.key, 0);
		input_sync(kp.dev);
	पूर्ण

	/* destroy input devs */
	input_unरेजिस्टर_device(sony_laptop_input.key_dev);
	sony_laptop_input.key_dev = शून्य;

	अगर (sony_laptop_input.jog_dev) अणु
		input_unरेजिस्टर_device(sony_laptop_input.jog_dev);
		sony_laptop_input.jog_dev = शून्य;
	पूर्ण

	kfअगरo_मुक्त(&sony_laptop_input.fअगरo);
पूर्ण

/*********** Platक्रमm Device ***********/

अटल atomic_t sony_pf_users = ATOMIC_INIT(0);
अटल काष्ठा platक्रमm_driver sony_pf_driver = अणु
	.driver = अणु
		   .name = "sony-laptop",
		   पूर्ण
पूर्ण;
अटल काष्ठा platक्रमm_device *sony_pf_device;

अटल पूर्णांक sony_pf_add(व्योम)
अणु
	पूर्णांक ret = 0;

	/* करोn't run again अगर alपढ़ोy initialized */
	अगर (atomic_add_वापस(1, &sony_pf_users) > 1)
		वापस 0;

	ret = platक्रमm_driver_रेजिस्टर(&sony_pf_driver);
	अगर (ret)
		जाओ out;

	sony_pf_device = platक्रमm_device_alloc("sony-laptop", -1);
	अगर (!sony_pf_device) अणु
		ret = -ENOMEM;
		जाओ out_platक्रमm_रेजिस्टरed;
	पूर्ण

	ret = platक्रमm_device_add(sony_pf_device);
	अगर (ret)
		जाओ out_platक्रमm_alloced;

	वापस 0;

      out_platक्रमm_alloced:
	platक्रमm_device_put(sony_pf_device);
	sony_pf_device = शून्य;
      out_platक्रमm_रेजिस्टरed:
	platक्रमm_driver_unरेजिस्टर(&sony_pf_driver);
      out:
	atomic_dec(&sony_pf_users);
	वापस ret;
पूर्ण

अटल व्योम sony_pf_हटाओ(व्योम)
अणु
	/* deरेजिस्टर only after the last user has gone */
	अगर (!atomic_dec_and_test(&sony_pf_users))
		वापस;

	platक्रमm_device_unरेजिस्टर(sony_pf_device);
	platक्रमm_driver_unरेजिस्टर(&sony_pf_driver);
पूर्ण

/*********** SNC (SNY5001) Device ***********/

/* the device uses 1-based values, जबतक the backlight subप्रणाली uses
   0-based values */
#घोषणा SONY_MAX_BRIGHTNESS	8

#घोषणा SNC_VALIDATE_IN		0
#घोषणा SNC_VALIDATE_OUT	1

अटल sमाप_प्रकार sony_nc_sysfs_show(काष्ठा device *, काष्ठा device_attribute *,
			      अक्षर *);
अटल sमाप_प्रकार sony_nc_sysfs_store(काष्ठा device *, काष्ठा device_attribute *,
			       स्थिर अक्षर *, माप_प्रकार);
अटल पूर्णांक boolean_validate(स्थिर पूर्णांक, स्थिर पूर्णांक);
अटल पूर्णांक brightness_शेष_validate(स्थिर पूर्णांक, स्थिर पूर्णांक);

काष्ठा sony_nc_value अणु
	अक्षर *name;		/* name of the entry */
	अक्षर **acpiget;		/* names of the ACPI get function */
	अक्षर **acpiset;		/* names of the ACPI set function */
	पूर्णांक (*validate)(स्थिर पूर्णांक, स्थिर पूर्णांक);	/* input/output validation */
	पूर्णांक value;		/* current setting */
	पूर्णांक valid;		/* Has ever been set */
	पूर्णांक debug;		/* active only in debug mode ? */
	काष्ठा device_attribute devattr;	/* sysfs attribute */
पूर्ण;

#घोषणा SNC_HANDLE_NAMES(_name, _values...) \
	अटल अक्षर *snc_##_name[] = अणु _values, शून्य पूर्ण

#घोषणा SNC_HANDLE(_name, _getters, _setters, _validate, _debug) \
	अणु \
		.name		= __stringअगरy(_name), \
		.acpiget	= _getters, \
		.acpiset	= _setters, \
		.validate	= _validate, \
		.debug		= _debug, \
		.devattr	= __ATTR(_name, 0, sony_nc_sysfs_show, sony_nc_sysfs_store), \
	पूर्ण

#घोषणा SNC_HANDLE_शून्य	अणु .name = शून्य पूर्ण

SNC_HANDLE_NAMES(fnkey_get, "GHKE");

SNC_HANDLE_NAMES(brightness_def_get, "GPBR");
SNC_HANDLE_NAMES(brightness_def_set, "SPBR");

SNC_HANDLE_NAMES(cdघातer_get, "GCDP");
SNC_HANDLE_NAMES(cdघातer_set, "SCDP", "CDPW");

SNC_HANDLE_NAMES(audioघातer_get, "GAZP");
SNC_HANDLE_NAMES(audioघातer_set, "AZPW");

SNC_HANDLE_NAMES(lanघातer_get, "GLNP");
SNC_HANDLE_NAMES(lanघातer_set, "LNPW");

SNC_HANDLE_NAMES(lidstate_get, "GLID");

SNC_HANDLE_NAMES(indicatorlamp_get, "GILS");
SNC_HANDLE_NAMES(indicatorlamp_set, "SILS");

SNC_HANDLE_NAMES(gainbass_get, "GMGB");
SNC_HANDLE_NAMES(gainbass_set, "CMGB");

SNC_HANDLE_NAMES(PID_get, "GPID");

SNC_HANDLE_NAMES(CTR_get, "GCTR");
SNC_HANDLE_NAMES(CTR_set, "SCTR");

SNC_HANDLE_NAMES(PCR_get, "GPCR");
SNC_HANDLE_NAMES(PCR_set, "SPCR");

SNC_HANDLE_NAMES(CMI_get, "GCMI");
SNC_HANDLE_NAMES(CMI_set, "SCMI");

अटल काष्ठा sony_nc_value sony_nc_values[] = अणु
	SNC_HANDLE(brightness_शेष, snc_brightness_def_get,
			snc_brightness_def_set, brightness_शेष_validate, 0),
	SNC_HANDLE(fnkey, snc_fnkey_get, शून्य, शून्य, 0),
	SNC_HANDLE(cdघातer, snc_cdघातer_get, snc_cdघातer_set, boolean_validate, 0),
	SNC_HANDLE(audioघातer, snc_audioघातer_get, snc_audioघातer_set,
			boolean_validate, 0),
	SNC_HANDLE(lanघातer, snc_lanघातer_get, snc_lanघातer_set,
			boolean_validate, 1),
	SNC_HANDLE(lidstate, snc_lidstate_get, शून्य,
			boolean_validate, 0),
	SNC_HANDLE(indicatorlamp, snc_indicatorlamp_get, snc_indicatorlamp_set,
			boolean_validate, 0),
	SNC_HANDLE(gainbass, snc_gainbass_get, snc_gainbass_set,
			boolean_validate, 0),
	/* unknown methods */
	SNC_HANDLE(PID, snc_PID_get, शून्य, शून्य, 1),
	SNC_HANDLE(CTR, snc_CTR_get, snc_CTR_set, शून्य, 1),
	SNC_HANDLE(PCR, snc_PCR_get, snc_PCR_set, शून्य, 1),
	SNC_HANDLE(CMI, snc_CMI_get, snc_CMI_set, शून्य, 1),
	SNC_HANDLE_शून्य
पूर्ण;

अटल acpi_handle sony_nc_acpi_handle;
अटल काष्ठा acpi_device *sony_nc_acpi_device = शून्य;

/*
 * acpi_evaluate_object wrappers
 * all useful calls पूर्णांकo SNC methods take one or zero parameters and वापस
 * पूर्णांकegers or arrays.
 */
अटल जोड़ acpi_object *__call_snc_method(acpi_handle handle, अक्षर *method,
		u64 *value)
अणु
	जोड़ acpi_object *result = शून्य;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	acpi_status status;

	अगर (value) अणु
		काष्ठा acpi_object_list params;
		जोड़ acpi_object in;
		in.type = ACPI_TYPE_INTEGER;
		in.पूर्णांकeger.value = *value;
		params.count = 1;
		params.poपूर्णांकer = &in;
		status = acpi_evaluate_object(handle, method, &params, &output);
		dprपूर्णांकk("__call_snc_method: [%s:0x%.8x%.8x]\n", method,
				(अचिन्हित पूर्णांक)(*value >> 32),
				(अचिन्हित पूर्णांक)*value & 0xffffffff);
	पूर्ण अन्यथा अणु
		status = acpi_evaluate_object(handle, method, शून्य, &output);
		dprपूर्णांकk("__call_snc_method: [%s]\n", method);
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Failed to evaluate [%s]\n", method);
		वापस शून्य;
	पूर्ण

	result = (जोड़ acpi_object *) output.poपूर्णांकer;
	अगर (!result)
		dprपूर्णांकk("No return object [%s]\n", method);

	वापस result;
पूर्ण

#घोषणा MIN(a, b)	(a > b ? b : a)
अटल पूर्णांक sony_nc_buffer_call(acpi_handle handle, अक्षर *name, u64 *value,
		व्योम *buffer, माप_प्रकार buflen)
अणु
	पूर्णांक ret = 0;
	माप_प्रकार len;
	जोड़ acpi_object *object = __call_snc_method(handle, name, value);

	अगर (!object)
		वापस -EINVAL;

	अगर (!buffer) अणु
		/* करो nothing */
	पूर्ण अन्यथा अगर (object->type == ACPI_TYPE_BUFFER) अणु
		len = MIN(buflen, object->buffer.length);
		स_रखो(buffer, 0, buflen);
		स_नकल(buffer, object->buffer.poपूर्णांकer, len);

	पूर्ण अन्यथा अगर (object->type == ACPI_TYPE_INTEGER) अणु
		len = MIN(buflen, माप(object->पूर्णांकeger.value));
		स_रखो(buffer, 0, buflen);
		स_नकल(buffer, &object->पूर्णांकeger.value, len);

	पूर्ण अन्यथा अणु
		pr_warn("Unexpected acpi_object: 0x%x\n", object->type);
		ret = -EINVAL;
	पूर्ण

	kमुक्त(object);
	वापस ret;
पूर्ण

अटल पूर्णांक sony_nc_पूर्णांक_call(acpi_handle handle, अक्षर *name, पूर्णांक *value, पूर्णांक
		*result)
अणु
	पूर्णांक ret;

	अगर (value) अणु
		u64 v = *value;

		ret = sony_nc_buffer_call(handle, name, &v, result,
				माप(*result));
	पूर्ण अन्यथा अणु
		ret =  sony_nc_buffer_call(handle, name, शून्य, result,
				माप(*result));
	पूर्ण
	वापस ret;
पूर्ण

काष्ठा sony_nc_handles अणु
	u16 cap[0x10];
	काष्ठा device_attribute devattr;
पूर्ण;

अटल काष्ठा sony_nc_handles *handles;

अटल sमाप_प्रकार sony_nc_handles_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(handles->cap); i++) अणु
		len += scnम_लिखो(buffer + len, PAGE_SIZE - len, "0x%.4x ",
				handles->cap[i]);
	पूर्ण
	len += scnम_लिखो(buffer + len, PAGE_SIZE - len, "\n");

	वापस len;
पूर्ण

अटल पूर्णांक sony_nc_handles_setup(काष्ठा platक्रमm_device *pd)
अणु
	पूर्णांक i, r, result, arg;

	handles = kzalloc(माप(*handles), GFP_KERNEL);
	अगर (!handles)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(handles->cap); i++) अणु
		arg = i + 0x20;
		r = sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SN00", &arg,
					&result);
		अगर (!r) अणु
			dprपूर्णांकk("caching handle 0x%.4x (offset: 0x%.2x)\n",
					result, i);
			handles->cap[i] = result;
		पूर्ण
	पूर्ण

	अगर (debug) अणु
		sysfs_attr_init(&handles->devattr.attr);
		handles->devattr.attr.name = "handles";
		handles->devattr.attr.mode = S_IRUGO;
		handles->devattr.show = sony_nc_handles_show;

		/* allow पढ़ोing capabilities via sysfs */
		अगर (device_create_file(&pd->dev, &handles->devattr)) अणु
			kमुक्त(handles);
			handles = शून्य;
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sony_nc_handles_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (handles) अणु
		अगर (debug)
			device_हटाओ_file(&pd->dev, &handles->devattr);
		kमुक्त(handles);
		handles = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sony_find_snc_handle(पूर्णांक handle)
अणु
	पूर्णांक i;

	/* not initialized yet, वापस early */
	अगर (!handles || !handle)
		वापस -EINVAL;

	क्रम (i = 0; i < 0x10; i++) अणु
		अगर (handles->cap[i] == handle) अणु
			dprपूर्णांकk("found handle 0x%.4x (offset: 0x%.2x)\n",
					handle, i);
			वापस i;
		पूर्ण
	पूर्ण
	dprपूर्णांकk("handle 0x%.4x not found\n", handle);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sony_call_snc_handle(पूर्णांक handle, पूर्णांक argument, पूर्णांक *result)
अणु
	पूर्णांक arg, ret = 0;
	पूर्णांक offset = sony_find_snc_handle(handle);

	अगर (offset < 0)
		वापस offset;

	arg = offset | argument;
	ret = sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SN07", &arg, result);
	dprपूर्णांकk("called SN07 with 0x%.4x (result: 0x%.4x)\n", arg, *result);
	वापस ret;
पूर्ण

/*
 * sony_nc_values input/output validate functions
 */

/* brightness_शेष_validate:
 *
 * manipulate input output values to keep consistency with the
 * backlight framework क्रम which brightness values are 0-based.
 */
अटल पूर्णांक brightness_शेष_validate(स्थिर पूर्णांक direction, स्थिर पूर्णांक value)
अणु
	चयन (direction) अणु
		हाल SNC_VALIDATE_OUT:
			वापस value - 1;
		हाल SNC_VALIDATE_IN:
			अगर (value >= 0 && value < SONY_MAX_BRIGHTNESS)
				वापस value + 1;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* boolean_validate:
 *
 * on input validate boolean values 0/1, on output just pass the
 * received value.
 */
अटल पूर्णांक boolean_validate(स्थिर पूर्णांक direction, स्थिर पूर्णांक value)
अणु
	अगर (direction == SNC_VALIDATE_IN) अणु
		अगर (value != 0 && value != 1)
			वापस -EINVAL;
	पूर्ण
	वापस value;
पूर्ण

/*
 * Sysfs show/store common to all sony_nc_values
 */
अटल sमाप_प्रकार sony_nc_sysfs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buffer)
अणु
	पूर्णांक value, ret = 0;
	काष्ठा sony_nc_value *item =
	    container_of(attr, काष्ठा sony_nc_value, devattr);

	अगर (!*item->acpiget)
		वापस -EIO;

	ret = sony_nc_पूर्णांक_call(sony_nc_acpi_handle, *item->acpiget, शून्य,
				&value);
	अगर (ret < 0)
		वापस -EIO;

	अगर (item->validate)
		value = item->validate(SNC_VALIDATE_OUT, value);

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार sony_nc_sysfs_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	पूर्णांक value;
	पूर्णांक ret = 0;
	काष्ठा sony_nc_value *item =
	    container_of(attr, काष्ठा sony_nc_value, devattr);

	अगर (!item->acpiset)
		वापस -EIO;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kstrtoपूर्णांक(buffer, 10, &value))
		वापस -EINVAL;

	अगर (item->validate)
		value = item->validate(SNC_VALIDATE_IN, value);

	अगर (value < 0)
		वापस value;

	ret = sony_nc_पूर्णांक_call(sony_nc_acpi_handle, *item->acpiset,
			       &value, शून्य);
	अगर (ret < 0)
		वापस -EIO;

	item->value = value;
	item->valid = 1;
	वापस count;
पूर्ण


/*
 * Backlight device
 */
काष्ठा sony_backlight_props अणु
	काष्ठा backlight_device *dev;
	पूर्णांक			handle;
	पूर्णांक			cmd_base;
	u8			offset;
	u8			maxlvl;
पूर्ण;
अटल काष्ठा sony_backlight_props sony_bl_props;

अटल पूर्णांक sony_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	पूर्णांक arg = bd->props.brightness + 1;
	वापस sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SBRT", &arg, शून्य);
पूर्ण

अटल पूर्णांक sony_backlight_get_brightness(काष्ठा backlight_device *bd)
अणु
	पूर्णांक value;

	अगर (sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "GBRT", शून्य, &value))
		वापस 0;
	/* brightness levels are 1-based, जबतक backlight ones are 0-based */
	वापस value - 1;
पूर्ण

अटल पूर्णांक sony_nc_get_brightness_ng(काष्ठा backlight_device *bd)
अणु
	पूर्णांक result;
	काष्ठा sony_backlight_props *sdev =
		(काष्ठा sony_backlight_props *)bl_get_data(bd);

	sony_call_snc_handle(sdev->handle, sdev->cmd_base + 0x100, &result);

	वापस (result & 0xff) - sdev->offset;
पूर्ण

अटल पूर्णांक sony_nc_update_status_ng(काष्ठा backlight_device *bd)
अणु
	पूर्णांक value, result;
	काष्ठा sony_backlight_props *sdev =
		(काष्ठा sony_backlight_props *)bl_get_data(bd);

	value = bd->props.brightness + sdev->offset;
	अगर (sony_call_snc_handle(sdev->handle, sdev->cmd_base | (value << 0x10),
				&result))
		वापस -EIO;

	वापस value;
पूर्ण

अटल स्थिर काष्ठा backlight_ops sony_backlight_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status = sony_backlight_update_status,
	.get_brightness = sony_backlight_get_brightness,
पूर्ण;
अटल स्थिर काष्ठा backlight_ops sony_backlight_ng_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status = sony_nc_update_status_ng,
	.get_brightness = sony_nc_get_brightness_ng,
पूर्ण;

/*
 * New SNC-only Vaios event mapping to driver known keys
 */
काष्ठा sony_nc_event अणु
	u8	data;
	u8	event;
पूर्ण;

अटल काष्ठा sony_nc_event sony_100_events[] = अणु
	अणु 0x90, SONYPI_EVENT_PKEY_P1 पूर्ण,
	अणु 0x10, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0x91, SONYPI_EVENT_PKEY_P2 पूर्ण,
	अणु 0x11, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0x81, SONYPI_EVENT_FNKEY_F1 पूर्ण,
	अणु 0x01, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x82, SONYPI_EVENT_FNKEY_F2 पूर्ण,
	अणु 0x02, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x83, SONYPI_EVENT_FNKEY_F3 पूर्ण,
	अणु 0x03, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x84, SONYPI_EVENT_FNKEY_F4 पूर्ण,
	अणु 0x04, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x85, SONYPI_EVENT_FNKEY_F5 पूर्ण,
	अणु 0x05, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x86, SONYPI_EVENT_FNKEY_F6 पूर्ण,
	अणु 0x06, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x87, SONYPI_EVENT_FNKEY_F7 पूर्ण,
	अणु 0x07, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x88, SONYPI_EVENT_FNKEY_F8 पूर्ण,
	अणु 0x08, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x89, SONYPI_EVENT_FNKEY_F9 पूर्ण,
	अणु 0x09, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x8A, SONYPI_EVENT_FNKEY_F10 पूर्ण,
	अणु 0x0A, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x8B, SONYPI_EVENT_FNKEY_F11 पूर्ण,
	अणु 0x0B, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x8C, SONYPI_EVENT_FNKEY_F12 पूर्ण,
	अणु 0x0C, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x9d, SONYPI_EVENT_ZOOM_PRESSED पूर्ण,
	अणु 0x1d, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0x9f, SONYPI_EVENT_CD_EJECT_PRESSED पूर्ण,
	अणु 0x1f, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0xa1, SONYPI_EVENT_MEDIA_PRESSED पूर्ण,
	अणु 0x21, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0xa4, SONYPI_EVENT_CD_EJECT_PRESSED पूर्ण,
	अणु 0x24, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0xa5, SONYPI_EVENT_VENDOR_PRESSED पूर्ण,
	अणु 0x25, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0xa6, SONYPI_EVENT_HELP_PRESSED पूर्ण,
	अणु 0x26, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0xa8, SONYPI_EVENT_FNKEY_1 पूर्ण,
	अणु 0x28, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा sony_nc_event sony_127_events[] = अणु
	अणु 0x81, SONYPI_EVENT_MODEKEY_PRESSED पूर्ण,
	अणु 0x01, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0x82, SONYPI_EVENT_PKEY_P1 पूर्ण,
	अणु 0x02, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0x83, SONYPI_EVENT_PKEY_P2 पूर्ण,
	अणु 0x03, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0x84, SONYPI_EVENT_PKEY_P3 पूर्ण,
	अणु 0x04, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0x85, SONYPI_EVENT_PKEY_P4 पूर्ण,
	अणु 0x05, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0x86, SONYPI_EVENT_PKEY_P5 पूर्ण,
	अणु 0x06, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0x87, SONYPI_EVENT_SETTINGKEY_PRESSED पूर्ण,
	अणु 0x07, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक sony_nc_hotkeys_decode(u32 event, अचिन्हित पूर्णांक handle)
अणु
	पूर्णांक ret = -EINVAL;
	अचिन्हित पूर्णांक result = 0;
	काष्ठा sony_nc_event *key_event;

	अगर (sony_call_snc_handle(handle, 0x200, &result)) अणु
		dprपूर्णांकk("Unable to decode event 0x%.2x 0x%.2x\n", handle,
				event);
		वापस -EINVAL;
	पूर्ण

	result &= 0xFF;

	अगर (handle == 0x0100)
		key_event = sony_100_events;
	अन्यथा
		key_event = sony_127_events;

	क्रम (; key_event->data; key_event++) अणु
		अगर (key_event->data == result) अणु
			ret = key_event->event;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!key_event->data)
		pr_info("Unknown hotkey 0x%.2x/0x%.2x (handle 0x%.2x)\n",
				event, result, handle);

	वापस ret;
पूर्ण

/*
 * ACPI callbacks
 */
क्रमागत event_types अणु
	HOTKEY = 1,
	KILLSWITCH,
	GFX_SWITCH
पूर्ण;
अटल व्योम sony_nc_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	u32 real_ev = event;
	u8 ev_type = 0;
	पूर्णांक ret;

	dprपूर्णांकk("sony_nc_notify, event: 0x%.2x\n", event);

	अगर (event >= 0x90) अणु
		अचिन्हित पूर्णांक result = 0;
		अचिन्हित पूर्णांक arg = 0;
		अचिन्हित पूर्णांक handle = 0;
		अचिन्हित पूर्णांक offset = event - 0x90;

		अगर (offset >= ARRAY_SIZE(handles->cap)) अणु
			pr_err("Event 0x%x outside of capabilities list\n",
					event);
			वापस;
		पूर्ण
		handle = handles->cap[offset];

		/* list of handles known क्रम generating events */
		चयन (handle) अणु
		/* hotkey event */
		हाल 0x0100:
		हाल 0x0127:
			ev_type = HOTKEY;
			ret = sony_nc_hotkeys_decode(event, handle);

			अगर (ret > 0) अणु
				sony_laptop_report_input_event(ret);
				real_ev = ret;
			पूर्ण

			अवरोध;

		/* wlan चयन */
		हाल 0x0124:
		हाल 0x0135:
			/* events on this handle are reported when the
			 * चयन changes position or क्रम battery
			 * events. We'll notअगरy both of them but only
			 * update the rfसमाप्त device status when the
			 * चयन is moved.
			 */
			ev_type = KILLSWITCH;
			sony_call_snc_handle(handle, 0x0100, &result);
			real_ev = result & 0x03;

			/* hw चयन event */
			अगर (real_ev == 1)
				sony_nc_rfसमाप्त_update();

			अवरोध;

		हाल 0x0128:
		हाल 0x0146:
			/* Hybrid GFX चयनing */
			sony_call_snc_handle(handle, 0x0000, &result);
			dprपूर्णांकk("GFX switch event received (reason: %s)\n",
					(result == 0x1) ? "switch change" :
					(result == 0x2) ? "output switch" :
					(result == 0x3) ? "output switch" :
					"");

			ev_type = GFX_SWITCH;
			real_ev = __sony_nc_gfx_चयन_status_get();
			अवरोध;

		हाल 0x015B:
			/* Hybrid GFX चयनing SVS151290S */
			ev_type = GFX_SWITCH;
			real_ev = __sony_nc_gfx_चयन_status_get();
			अवरोध;
		शेष:
			dprपूर्णांकk("Unknown event 0x%x for handle 0x%x\n",
					event, handle);
			अवरोध;
		पूर्ण

		/* clear the event (and the event reason when present) */
		arg = 1 << offset;
		sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SN05", &arg, &result);

	पूर्ण अन्यथा अणु
		/* old style event */
		ev_type = HOTKEY;
		sony_laptop_report_input_event(real_ev);
	पूर्ण
	acpi_bus_generate_netlink_event(sony_nc_acpi_device->pnp.device_class,
			dev_name(&sony_nc_acpi_device->dev), ev_type, real_ev);
पूर्ण

अटल acpi_status sony_walk_callback(acpi_handle handle, u32 level,
				      व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_device_info *info;

	अगर (ACPI_SUCCESS(acpi_get_object_info(handle, &info))) अणु
		pr_warn("method: name: %4.4s, args %X\n",
			(अक्षर *)&info->name, info->param_count);

		kमुक्त(info);
	पूर्ण

	वापस AE_OK;
पूर्ण

/*
 * ACPI device
 */
अटल व्योम sony_nc_function_setup(काष्ठा acpi_device *device,
		काष्ठा platक्रमm_device *pf_device)
अणु
	अचिन्हित पूर्णांक i, result, biपंचांगask, arg;

	अगर (!handles)
		वापस;

	/* setup found handles here */
	क्रम (i = 0; i < ARRAY_SIZE(handles->cap); i++) अणु
		अचिन्हित पूर्णांक handle = handles->cap[i];

		अगर (!handle)
			जारी;

		dprपूर्णांकk("setting up handle 0x%.4x\n", handle);

		चयन (handle) अणु
		हाल 0x0100:
		हाल 0x0101:
		हाल 0x0127:
			/* setup hotkeys */
			sony_call_snc_handle(handle, 0, &result);
			अवरोध;
		हाल 0x0102:
			/* setup hotkeys */
			sony_call_snc_handle(handle, 0x100, &result);
			अवरोध;
		हाल 0x0105:
		हाल 0x0148:
			/* touchpad enable/disable */
			result = sony_nc_touchpad_setup(pf_device, handle);
			अगर (result)
				pr_err("couldn't set up touchpad control function (%d)\n",
						result);
			अवरोध;
		हाल 0x0115:
		हाल 0x0136:
		हाल 0x013f:
			result = sony_nc_battery_care_setup(pf_device, handle);
			अगर (result)
				pr_err("couldn't set up battery care function (%d)\n",
						result);
			अवरोध;
		हाल 0x0119:
		हाल 0x015D:
			result = sony_nc_lid_resume_setup(pf_device, handle);
			अगर (result)
				pr_err("couldn't set up lid resume function (%d)\n",
						result);
			अवरोध;
		हाल 0x0122:
			result = sony_nc_thermal_setup(pf_device);
			अगर (result)
				pr_err("couldn't set up thermal profile function (%d)\n",
						result);
			अवरोध;
		हाल 0x0128:
		हाल 0x0146:
		हाल 0x015B:
			result = sony_nc_gfx_चयन_setup(pf_device, handle);
			अगर (result)
				pr_err("couldn't set up GFX Switch status (%d)\n",
						result);
			अवरोध;
		हाल 0x0131:
			result = sony_nc_highspeed_अक्षरging_setup(pf_device);
			अगर (result)
				pr_err("couldn't set up high speed charging function (%d)\n",
				       result);
			अवरोध;
		हाल 0x0124:
		हाल 0x0135:
			result = sony_nc_rfसमाप्त_setup(device, handle);
			अगर (result)
				pr_err("couldn't set up rfkill support (%d)\n",
						result);
			अवरोध;
		हाल 0x0137:
		हाल 0x0143:
		हाल 0x014b:
		हाल 0x014c:
		हाल 0x0153:
		हाल 0x0163:
			result = sony_nc_kbd_backlight_setup(pf_device, handle);
			अगर (result)
				pr_err("couldn't set up keyboard backlight function (%d)\n",
						result);
			अवरोध;
		हाल 0x0121:
			result = sony_nc_lowbatt_setup(pf_device);
			अगर (result)
				pr_err("couldn't set up low battery function (%d)\n",
				       result);
			अवरोध;
		हाल 0x0149:
			result = sony_nc_fanspeed_setup(pf_device);
			अगर (result)
				pr_err("couldn't set up fan speed function (%d)\n",
				       result);
			अवरोध;
		हाल 0x0155:
			result = sony_nc_usb_अक्षरge_setup(pf_device);
			अगर (result)
				pr_err("couldn't set up USB charge support (%d)\n",
						result);
			अवरोध;
		हाल 0x011D:
			result = sony_nc_panelid_setup(pf_device);
			अगर (result)
				pr_err("couldn't set up panel ID function (%d)\n",
				       result);
			अवरोध;
		हाल 0x0168:
			result = sony_nc_smart_conn_setup(pf_device);
			अगर (result)
				pr_err("couldn't set up smart connect support (%d)\n",
						result);
			अवरोध;
		शेष:
			जारी;
		पूर्ण
	पूर्ण

	/* Enable all events */
	arg = 0x10;
	अगर (!sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SN00", &arg, &biपंचांगask))
		sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SN02", &biपंचांगask,
				&result);
पूर्ण

अटल व्योम sony_nc_function_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अचिन्हित पूर्णांक i, result, biपंचांगask, handle;

	अगर (!handles)
		वापस;

	/* get enabled events and disable them */
	sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SN01", शून्य, &biपंचांगask);
	sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SN03", &biपंचांगask, &result);

	/* cleanup handles here */
	क्रम (i = 0; i < ARRAY_SIZE(handles->cap); i++) अणु

		handle = handles->cap[i];

		अगर (!handle)
			जारी;

		चयन (handle) अणु
		हाल 0x0105:
		हाल 0x0148:
			sony_nc_touchpad_cleanup(pd);
			अवरोध;
		हाल 0x0115:
		हाल 0x0136:
		हाल 0x013f:
			sony_nc_battery_care_cleanup(pd);
			अवरोध;
		हाल 0x0119:
		हाल 0x015D:
			sony_nc_lid_resume_cleanup(pd);
			अवरोध;
		हाल 0x0122:
			sony_nc_thermal_cleanup(pd);
			अवरोध;
		हाल 0x0128:
		हाल 0x0146:
		हाल 0x015B:
			sony_nc_gfx_चयन_cleanup(pd);
			अवरोध;
		हाल 0x0131:
			sony_nc_highspeed_अक्षरging_cleanup(pd);
			अवरोध;
		हाल 0x0124:
		हाल 0x0135:
			sony_nc_rfसमाप्त_cleanup();
			अवरोध;
		हाल 0x0137:
		हाल 0x0143:
		हाल 0x014b:
		हाल 0x014c:
		हाल 0x0153:
		हाल 0x0163:
			sony_nc_kbd_backlight_cleanup(pd, handle);
			अवरोध;
		हाल 0x0121:
			sony_nc_lowbatt_cleanup(pd);
			अवरोध;
		हाल 0x0149:
			sony_nc_fanspeed_cleanup(pd);
			अवरोध;
		हाल 0x0155:
			sony_nc_usb_अक्षरge_cleanup(pd);
			अवरोध;
		हाल 0x011D:
			sony_nc_panelid_cleanup(pd);
			अवरोध;
		हाल 0x0168:
			sony_nc_smart_conn_cleanup(pd);
			अवरोध;
		शेष:
			जारी;
		पूर्ण
	पूर्ण

	/* finally cleanup the handles list */
	sony_nc_handles_cleanup(pd);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम sony_nc_function_resume(व्योम)
अणु
	अचिन्हित पूर्णांक i, result, biपंचांगask, arg;

	dprपूर्णांकk("Resuming SNC device\n");

	क्रम (i = 0; i < ARRAY_SIZE(handles->cap); i++) अणु
		अचिन्हित पूर्णांक handle = handles->cap[i];

		अगर (!handle)
			जारी;

		चयन (handle) अणु
		हाल 0x0100:
		हाल 0x0101:
		हाल 0x0127:
			/* re-enable hotkeys */
			sony_call_snc_handle(handle, 0, &result);
			अवरोध;
		हाल 0x0102:
			/* re-enable hotkeys */
			sony_call_snc_handle(handle, 0x100, &result);
			अवरोध;
		हाल 0x0122:
			sony_nc_thermal_resume();
			अवरोध;
		हाल 0x0124:
		हाल 0x0135:
			sony_nc_rfसमाप्त_update();
			अवरोध;
		शेष:
			जारी;
		पूर्ण
	पूर्ण

	/* Enable all events */
	arg = 0x10;
	अगर (!sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SN00", &arg, &biपंचांगask))
		sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SN02", &biपंचांगask,
				&result);
पूर्ण

अटल पूर्णांक sony_nc_resume(काष्ठा device *dev)
अणु
	काष्ठा sony_nc_value *item;

	क्रम (item = sony_nc_values; item->name; item++) अणु
		पूर्णांक ret;

		अगर (!item->valid)
			जारी;
		ret = sony_nc_पूर्णांक_call(sony_nc_acpi_handle, *item->acpiset,
				       &item->value, शून्य);
		अगर (ret < 0) अणु
			pr_err("%s: %d\n", __func__, ret);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (acpi_has_method(sony_nc_acpi_handle, "ECON")) अणु
		पूर्णांक arg = 1;
		अगर (sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "ECON", &arg, शून्य))
			dprपूर्णांकk("ECON Method failed\n");
	पूर्ण

	अगर (acpi_has_method(sony_nc_acpi_handle, "SN00"))
		sony_nc_function_resume();

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sony_nc_pm, शून्य, sony_nc_resume);

अटल व्योम sony_nc_rfसमाप्त_cleanup(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < N_SONY_RFKILL; i++) अणु
		अगर (sony_rfसमाप्त_devices[i]) अणु
			rfसमाप्त_unरेजिस्टर(sony_rfसमाप्त_devices[i]);
			rfसमाप्त_destroy(sony_rfसमाप्त_devices[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sony_nc_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	पूर्णांक result;
	पूर्णांक argument = sony_rfसमाप्त_address[(दीर्घ) data] + 0x100;

	अगर (!blocked)
		argument |= 0x070000;

	वापस sony_call_snc_handle(sony_rfसमाप्त_handle, argument, &result);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops sony_rfसमाप्त_ops = अणु
	.set_block = sony_nc_rfसमाप्त_set,
पूर्ण;

अटल पूर्णांक sony_nc_setup_rfसमाप्त(काष्ठा acpi_device *device,
				क्रमागत sony_nc_rfसमाप्त nc_type)
अणु
	पूर्णांक err;
	काष्ठा rfसमाप्त *rfk;
	क्रमागत rfसमाप्त_type type;
	स्थिर अक्षर *name;
	पूर्णांक result;
	bool hwblock, swblock;

	चयन (nc_type) अणु
	हाल SONY_WIFI:
		type = RFKILL_TYPE_WLAN;
		name = "sony-wifi";
		अवरोध;
	हाल SONY_BLUETOOTH:
		type = RFKILL_TYPE_BLUETOOTH;
		name = "sony-bluetooth";
		अवरोध;
	हाल SONY_WWAN:
		type = RFKILL_TYPE_WWAN;
		name = "sony-wwan";
		अवरोध;
	हाल SONY_WIMAX:
		type = RFKILL_TYPE_WIMAX;
		name = "sony-wimax";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rfk = rfसमाप्त_alloc(name, &device->dev, type,
			   &sony_rfसमाप्त_ops, (व्योम *)nc_type);
	अगर (!rfk)
		वापस -ENOMEM;

	err = sony_call_snc_handle(sony_rfसमाप्त_handle, 0x200, &result);
	अगर (err < 0) अणु
		rfसमाप्त_destroy(rfk);
		वापस err;
	पूर्ण
	hwblock = !(result & 0x1);

	err = sony_call_snc_handle(sony_rfसमाप्त_handle,
				   sony_rfसमाप्त_address[nc_type],
				   &result);
	अगर (err < 0) अणु
		rfसमाप्त_destroy(rfk);
		वापस err;
	पूर्ण
	swblock = !(result & 0x2);

	rfसमाप्त_init_sw_state(rfk, swblock);
	rfसमाप्त_set_hw_state(rfk, hwblock);

	err = rfसमाप्त_रेजिस्टर(rfk);
	अगर (err) अणु
		rfसमाप्त_destroy(rfk);
		वापस err;
	पूर्ण
	sony_rfसमाप्त_devices[nc_type] = rfk;
	वापस err;
पूर्ण

अटल व्योम sony_nc_rfसमाप्त_update(व्योम)
अणु
	क्रमागत sony_nc_rfसमाप्त i;
	पूर्णांक result;
	bool hwblock;

	sony_call_snc_handle(sony_rfसमाप्त_handle, 0x200, &result);
	hwblock = !(result & 0x1);

	क्रम (i = 0; i < N_SONY_RFKILL; i++) अणु
		पूर्णांक argument = sony_rfसमाप्त_address[i];

		अगर (!sony_rfसमाप्त_devices[i])
			जारी;

		अगर (hwblock) अणु
			अगर (rfसमाप्त_set_hw_state(sony_rfसमाप्त_devices[i], true)) अणु
				/* we alपढ़ोy know we're blocked */
			पूर्ण
			जारी;
		पूर्ण

		sony_call_snc_handle(sony_rfसमाप्त_handle, argument, &result);
		rfसमाप्त_set_states(sony_rfसमाप्त_devices[i],
				  !(result & 0x2), false);
	पूर्ण
पूर्ण

अटल पूर्णांक sony_nc_rfसमाप्त_setup(काष्ठा acpi_device *device,
		अचिन्हित पूर्णांक handle)
अणु
	u64 offset;
	पूर्णांक i;
	अचिन्हित अक्षर buffer[32] = अणु 0 पूर्ण;

	offset = sony_find_snc_handle(handle);
	sony_rfसमाप्त_handle = handle;

	i = sony_nc_buffer_call(sony_nc_acpi_handle, "SN06", &offset, buffer,
			32);
	अगर (i < 0)
		वापस i;

	/* The buffer is filled with magic numbers describing the devices
	 * available, 0xff terminates the क्रमागतeration.
	 * Known codes:
	 *	0x00 WLAN
	 *	0x10 BLUETOOTH
	 *	0x20 WWAN GPRS-EDGE
	 *	0x21 WWAN HSDPA
	 *	0x22 WWAN EV-DO
	 *	0x23 WWAN GPS
	 *	0x25 Gobi WWAN no GPS
	 *	0x26 Gobi WWAN + GPS
	 *	0x28 Gobi WWAN no GPS
	 *	0x29 Gobi WWAN + GPS
	 *	0x30 WIMAX
	 *	0x50 Gobi WWAN no GPS
	 *	0x51 Gobi WWAN + GPS
	 *	0x70 no SIM card slot
	 *	0x71 SIM card slot
	 */
	क्रम (i = 0; i < ARRAY_SIZE(buffer); i++) अणु

		अगर (buffer[i] == 0xff)
			अवरोध;

		dprपूर्णांकk("Radio devices, found 0x%.2x\n", buffer[i]);

		अगर (buffer[i] == 0 && !sony_rfसमाप्त_devices[SONY_WIFI])
			sony_nc_setup_rfसमाप्त(device, SONY_WIFI);

		अगर (buffer[i] == 0x10 && !sony_rfसमाप्त_devices[SONY_BLUETOOTH])
			sony_nc_setup_rfसमाप्त(device, SONY_BLUETOOTH);

		अगर (((0xf0 & buffer[i]) == 0x20 ||
					(0xf0 & buffer[i]) == 0x50) &&
				!sony_rfसमाप्त_devices[SONY_WWAN])
			sony_nc_setup_rfसमाप्त(device, SONY_WWAN);

		अगर (buffer[i] == 0x30 && !sony_rfसमाप्त_devices[SONY_WIMAX])
			sony_nc_setup_rfसमाप्त(device, SONY_WIMAX);
	पूर्ण
	वापस 0;
पूर्ण

/* Keyboard backlight feature */
काष्ठा kbd_backlight अणु
	अचिन्हित पूर्णांक handle;
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक has_समयout;
	काष्ठा device_attribute mode_attr;
	काष्ठा device_attribute समयout_attr;
पूर्ण;

अटल काष्ठा kbd_backlight *kbdbl_ctl;

अटल sमाप_प्रकार __sony_nc_kbd_backlight_mode_set(u8 value)
अणु
	पूर्णांक result;

	अगर (value > 2)
		वापस -EINVAL;

	अगर (sony_call_snc_handle(kbdbl_ctl->handle,
				(value << 0x10) | (kbdbl_ctl->base), &result))
		वापस -EIO;

	/* Try to turn the light on/off immediately */
	अगर (value != 1)
		sony_call_snc_handle(kbdbl_ctl->handle,
				(value << 0x0f) | (kbdbl_ctl->base + 0x100),
				&result);

	kbdbl_ctl->mode = value;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sony_nc_kbd_backlight_mode_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ value;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value))
		वापस -EINVAL;

	ret = __sony_nc_kbd_backlight_mode_set(value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_kbd_backlight_mode_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	sमाप_प्रकार count = 0;
	count = snम_लिखो(buffer, PAGE_SIZE, "%d\n", kbdbl_ctl->mode);
	वापस count;
पूर्ण

अटल पूर्णांक __sony_nc_kbd_backlight_समयout_set(u8 value)
अणु
	पूर्णांक result;

	अगर (value > 3)
		वापस -EINVAL;

	अगर (sony_call_snc_handle(kbdbl_ctl->handle, (value << 0x10) |
				(kbdbl_ctl->base + 0x200), &result))
		वापस -EIO;

	kbdbl_ctl->समयout = value;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sony_nc_kbd_backlight_समयout_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ value;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value))
		वापस -EINVAL;

	ret = __sony_nc_kbd_backlight_समयout_set(value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_kbd_backlight_समयout_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	sमाप_प्रकार count = 0;
	count = snम_लिखो(buffer, PAGE_SIZE, "%d\n", kbdbl_ctl->समयout);
	वापस count;
पूर्ण

अटल पूर्णांक sony_nc_kbd_backlight_setup(काष्ठा platक्रमm_device *pd,
		अचिन्हित पूर्णांक handle)
अणु
	पूर्णांक result;
	पूर्णांक probe_base = 0;
	पूर्णांक ctl_base = 0;
	पूर्णांक ret = 0;

	अगर (kbdbl_ctl) अणु
		pr_warn("handle 0x%.4x: keyboard backlight setup already done for 0x%.4x\n",
				handle, kbdbl_ctl->handle);
		वापस -EBUSY;
	पूर्ण

	/* verअगरy the kbd backlight presence, some of these handles are not used
	 * क्रम keyboard backlight only
	 */
	चयन (handle) अणु
	हाल 0x0153:
		probe_base = 0x0;
		ctl_base = 0x0;
		अवरोध;
	हाल 0x0137:
		probe_base = 0x0B00;
		ctl_base = 0x0C00;
		अवरोध;
	शेष:
		probe_base = 0x0100;
		ctl_base = 0x4000;
		अवरोध;
	पूर्ण

	ret = sony_call_snc_handle(handle, probe_base, &result);
	अगर (ret)
		वापस ret;

	अगर ((handle == 0x0137 && !(result & 0x02)) ||
			!(result & 0x01)) अणु
		dprपूर्णांकk("no backlight keyboard found\n");
		वापस 0;
	पूर्ण

	kbdbl_ctl = kzalloc(माप(*kbdbl_ctl), GFP_KERNEL);
	अगर (!kbdbl_ctl)
		वापस -ENOMEM;

	kbdbl_ctl->mode = kbd_backlight;
	kbdbl_ctl->समयout = kbd_backlight_समयout;
	kbdbl_ctl->handle = handle;
	kbdbl_ctl->base = ctl_base;
	/* Some models करो not allow समयout control */
	kbdbl_ctl->has_समयout = handle != 0x0153;

	sysfs_attr_init(&kbdbl_ctl->mode_attr.attr);
	kbdbl_ctl->mode_attr.attr.name = "kbd_backlight";
	kbdbl_ctl->mode_attr.attr.mode = S_IRUGO | S_IWUSR;
	kbdbl_ctl->mode_attr.show = sony_nc_kbd_backlight_mode_show;
	kbdbl_ctl->mode_attr.store = sony_nc_kbd_backlight_mode_store;

	ret = device_create_file(&pd->dev, &kbdbl_ctl->mode_attr);
	अगर (ret)
		जाओ outkzalloc;

	__sony_nc_kbd_backlight_mode_set(kbdbl_ctl->mode);

	अगर (kbdbl_ctl->has_समयout) अणु
		sysfs_attr_init(&kbdbl_ctl->समयout_attr.attr);
		kbdbl_ctl->समयout_attr.attr.name = "kbd_backlight_timeout";
		kbdbl_ctl->समयout_attr.attr.mode = S_IRUGO | S_IWUSR;
		kbdbl_ctl->समयout_attr.show =
			sony_nc_kbd_backlight_समयout_show;
		kbdbl_ctl->समयout_attr.store =
			sony_nc_kbd_backlight_समयout_store;

		ret = device_create_file(&pd->dev, &kbdbl_ctl->समयout_attr);
		अगर (ret)
			जाओ ouपंचांगode;

		__sony_nc_kbd_backlight_समयout_set(kbdbl_ctl->समयout);
	पूर्ण


	वापस 0;

ouपंचांगode:
	device_हटाओ_file(&pd->dev, &kbdbl_ctl->mode_attr);
outkzalloc:
	kमुक्त(kbdbl_ctl);
	kbdbl_ctl = शून्य;
	वापस ret;
पूर्ण

अटल व्योम sony_nc_kbd_backlight_cleanup(काष्ठा platक्रमm_device *pd,
		अचिन्हित पूर्णांक handle)
अणु
	अगर (kbdbl_ctl && handle == kbdbl_ctl->handle) अणु
		device_हटाओ_file(&pd->dev, &kbdbl_ctl->mode_attr);
		अगर (kbdbl_ctl->has_समयout)
			device_हटाओ_file(&pd->dev, &kbdbl_ctl->समयout_attr);
		kमुक्त(kbdbl_ctl);
		kbdbl_ctl = शून्य;
	पूर्ण
पूर्ण

काष्ठा battery_care_control अणु
	काष्ठा device_attribute attrs[2];
	अचिन्हित पूर्णांक handle;
पूर्ण;
अटल काष्ठा battery_care_control *bcare_ctl;

अटल sमाप_प्रकार sony_nc_battery_care_limit_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक result, cmd;
	अचिन्हित दीर्घ value;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value))
		वापस -EINVAL;

	/*  limit values (2 bits):
	 *  00 - none
	 *  01 - 80%
	 *  10 - 50%
	 *  11 - 100%
	 *
	 *  bit 0: 0 disable BCL, 1 enable BCL
	 *  bit 1: 1 tell to store the battery limit (see bits 6,7) too
	 *  bits 2,3: reserved
	 *  bits 4,5: store the limit पूर्णांकo the EC
	 *  bits 6,7: store the limit पूर्णांकo the battery
	 */
	cmd = 0;

	अगर (value > 0) अणु
		अगर (value <= 50)
			cmd = 0x20;

		अन्यथा अगर (value <= 80)
			cmd = 0x10;

		अन्यथा अगर (value <= 100)
			cmd = 0x30;

		अन्यथा
			वापस -EINVAL;

		/*
		 * handle 0x0115 should allow storing on battery too;
		 * handle 0x0136 same as 0x0115 + health status;
		 * handle 0x013f, same as 0x0136 but no storing on the battery
		 */
		अगर (bcare_ctl->handle != 0x013f)
			cmd = cmd | (cmd << 2);

		cmd = (cmd | 0x1) << 0x10;
	पूर्ण

	अगर (sony_call_snc_handle(bcare_ctl->handle, cmd | 0x0100, &result))
		वापस -EIO;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_battery_care_limit_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक result, status;

	अगर (sony_call_snc_handle(bcare_ctl->handle, 0x0000, &result))
		वापस -EIO;

	status = (result & 0x01) ? ((result & 0x30) >> 0x04) : 0;
	चयन (status) अणु
	हाल 1:
		status = 80;
		अवरोध;
	हाल 2:
		status = 50;
		अवरोध;
	हाल 3:
		status = 100;
		अवरोध;
	शेष:
		status = 0;
		अवरोध;
	पूर्ण

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", status);
पूर्ण

अटल sमाप_प्रकार sony_nc_battery_care_health_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	sमाप_प्रकार count = 0;
	अचिन्हित पूर्णांक health;

	अगर (sony_call_snc_handle(bcare_ctl->handle, 0x0200, &health))
		वापस -EIO;

	count = snम_लिखो(buffer, PAGE_SIZE, "%d\n", health & 0xff);

	वापस count;
पूर्ण

अटल पूर्णांक sony_nc_battery_care_setup(काष्ठा platक्रमm_device *pd,
		अचिन्हित पूर्णांक handle)
अणु
	पूर्णांक ret = 0;

	bcare_ctl = kzalloc(माप(काष्ठा battery_care_control), GFP_KERNEL);
	अगर (!bcare_ctl)
		वापस -ENOMEM;

	bcare_ctl->handle = handle;

	sysfs_attr_init(&bcare_ctl->attrs[0].attr);
	bcare_ctl->attrs[0].attr.name = "battery_care_limiter";
	bcare_ctl->attrs[0].attr.mode = S_IRUGO | S_IWUSR;
	bcare_ctl->attrs[0].show = sony_nc_battery_care_limit_show;
	bcare_ctl->attrs[0].store = sony_nc_battery_care_limit_store;

	ret = device_create_file(&pd->dev, &bcare_ctl->attrs[0]);
	अगर (ret)
		जाओ outkzalloc;

	/* 0x0115 is क्रम models with no health reporting capability */
	अगर (handle == 0x0115)
		वापस 0;

	sysfs_attr_init(&bcare_ctl->attrs[1].attr);
	bcare_ctl->attrs[1].attr.name = "battery_care_health";
	bcare_ctl->attrs[1].attr.mode = S_IRUGO;
	bcare_ctl->attrs[1].show = sony_nc_battery_care_health_show;

	ret = device_create_file(&pd->dev, &bcare_ctl->attrs[1]);
	अगर (ret)
		जाओ outlimiter;

	वापस 0;

outlimiter:
	device_हटाओ_file(&pd->dev, &bcare_ctl->attrs[0]);

outkzalloc:
	kमुक्त(bcare_ctl);
	bcare_ctl = शून्य;

	वापस ret;
पूर्ण

अटल व्योम sony_nc_battery_care_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (bcare_ctl) अणु
		device_हटाओ_file(&pd->dev, &bcare_ctl->attrs[0]);
		अगर (bcare_ctl->handle != 0x0115)
			device_हटाओ_file(&pd->dev, &bcare_ctl->attrs[1]);

		kमुक्त(bcare_ctl);
		bcare_ctl = शून्य;
	पूर्ण
पूर्ण

काष्ठा snc_thermal_ctrl अणु
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक profiles;
	काष्ठा device_attribute mode_attr;
	काष्ठा device_attribute profiles_attr;
पूर्ण;
अटल काष्ठा snc_thermal_ctrl *th_handle;

#घोषणा THM_PROखाता_MAX 3
अटल स्थिर अक्षर * स्थिर snc_thermal_profiles[] = अणु
	"balanced",
	"silent",
	"performance"
पूर्ण;

अटल पूर्णांक sony_nc_thermal_mode_set(अचिन्हित लघु mode)
अणु
	अचिन्हित पूर्णांक result;

	/* the thermal profile seems to be a two bit biपंचांगask:
	 * lsb -> silent
	 * msb -> perक्रमmance
	 * no bit set is the normal operation and is always valid
	 * Some vaio models only have "balanced" and "performance"
	 */
	अगर ((mode && !(th_handle->profiles & mode)) || mode >= THM_PROखाता_MAX)
		वापस -EINVAL;

	अगर (sony_call_snc_handle(0x0122, mode << 0x10 | 0x0200, &result))
		वापस -EIO;

	th_handle->mode = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक sony_nc_thermal_mode_get(व्योम)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(0x0122, 0x0100, &result))
		वापस -EIO;

	वापस result & 0xff;
पूर्ण

अटल sमाप_प्रकार sony_nc_thermal_profiles_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	लघु cnt;
	माप_प्रकार idx = 0;

	क्रम (cnt = 0; cnt < THM_PROखाता_MAX; cnt++) अणु
		अगर (!cnt || (th_handle->profiles & cnt))
			idx += scnम_लिखो(buffer + idx, PAGE_SIZE - idx, "%s ",
					snc_thermal_profiles[cnt]);
	पूर्ण
	idx += scnम_लिखो(buffer + idx, PAGE_SIZE - idx, "\n");

	वापस idx;
पूर्ण

अटल sमाप_प्रकार sony_nc_thermal_mode_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित लघु cmd;
	माप_प्रकार len = count;

	अगर (count == 0)
		वापस -EINVAL;

	/* skip the newline अगर present */
	अगर (buffer[len - 1] == '\n')
		len--;

	क्रम (cmd = 0; cmd < THM_PROखाता_MAX; cmd++)
		अगर (म_भेदन(buffer, snc_thermal_profiles[cmd], len) == 0)
			अवरोध;

	अगर (sony_nc_thermal_mode_set(cmd))
		वापस -EIO;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_thermal_mode_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	sमाप_प्रकार count = 0;
	पूर्णांक mode = sony_nc_thermal_mode_get();

	अगर (mode < 0)
		वापस mode;

	count = snम_लिखो(buffer, PAGE_SIZE, "%s\n", snc_thermal_profiles[mode]);

	वापस count;
पूर्ण

अटल पूर्णांक sony_nc_thermal_setup(काष्ठा platक्रमm_device *pd)
अणु
	पूर्णांक ret = 0;
	th_handle = kzalloc(माप(काष्ठा snc_thermal_ctrl), GFP_KERNEL);
	अगर (!th_handle)
		वापस -ENOMEM;

	ret = sony_call_snc_handle(0x0122, 0x0000, &th_handle->profiles);
	अगर (ret) अणु
		pr_warn("couldn't to read the thermal profiles\n");
		जाओ outkzalloc;
	पूर्ण

	ret = sony_nc_thermal_mode_get();
	अगर (ret < 0) अणु
		pr_warn("couldn't to read the current thermal profile");
		जाओ outkzalloc;
	पूर्ण
	th_handle->mode = ret;

	sysfs_attr_init(&th_handle->profiles_attr.attr);
	th_handle->profiles_attr.attr.name = "thermal_profiles";
	th_handle->profiles_attr.attr.mode = S_IRUGO;
	th_handle->profiles_attr.show = sony_nc_thermal_profiles_show;

	sysfs_attr_init(&th_handle->mode_attr.attr);
	th_handle->mode_attr.attr.name = "thermal_control";
	th_handle->mode_attr.attr.mode = S_IRUGO | S_IWUSR;
	th_handle->mode_attr.show = sony_nc_thermal_mode_show;
	th_handle->mode_attr.store = sony_nc_thermal_mode_store;

	ret = device_create_file(&pd->dev, &th_handle->profiles_attr);
	अगर (ret)
		जाओ outkzalloc;

	ret = device_create_file(&pd->dev, &th_handle->mode_attr);
	अगर (ret)
		जाओ outprofiles;

	वापस 0;

outprofiles:
	device_हटाओ_file(&pd->dev, &th_handle->profiles_attr);
outkzalloc:
	kमुक्त(th_handle);
	th_handle = शून्य;
	वापस ret;
पूर्ण

अटल व्योम sony_nc_thermal_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (th_handle) अणु
		device_हटाओ_file(&pd->dev, &th_handle->profiles_attr);
		device_हटाओ_file(&pd->dev, &th_handle->mode_attr);
		kमुक्त(th_handle);
		th_handle = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम sony_nc_thermal_resume(व्योम)
अणु
	पूर्णांक status;

	अगर (!th_handle)
		वापस;

	status = sony_nc_thermal_mode_get();

	अगर (status != th_handle->mode)
		sony_nc_thermal_mode_set(th_handle->mode);
पूर्ण
#पूर्ण_अगर

/* resume on LID खोलो */
#घोषणा LID_RESUME_S5	0
#घोषणा LID_RESUME_S4	1
#घोषणा LID_RESUME_S3	2
#घोषणा LID_RESUME_MAX	3
काष्ठा snc_lid_resume_control अणु
	काष्ठा device_attribute attrs[LID_RESUME_MAX];
	अचिन्हित पूर्णांक status;
	पूर्णांक handle;
पूर्ण;
अटल काष्ठा snc_lid_resume_control *lid_ctl;

अटल sमाप_प्रकार sony_nc_lid_resume_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक pos = LID_RESUME_S5;
	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value) || value > 1)
		वापस -EINVAL;

	/* the value we have to ग_लिखो to SNC is a biपंचांगask:
	 * +--------------+
	 * | S3 | S4 | S5 |
	 * +--------------+
	 *   2    1    0
	 */
	जबतक (pos < LID_RESUME_MAX) अणु
		अगर (&lid_ctl->attrs[pos].attr == &attr->attr)
			अवरोध;
		pos++;
	पूर्ण
	अगर (pos == LID_RESUME_MAX)
		वापस -EINVAL;

	अगर (value)
		value = lid_ctl->status | (1 << pos);
	अन्यथा
		value = lid_ctl->status & ~(1 << pos);

	अगर (sony_call_snc_handle(lid_ctl->handle, value << 0x10 | 0x0100,
				&result))
		वापस -EIO;

	lid_ctl->status = value;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_lid_resume_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक pos = LID_RESUME_S5;

	जबतक (pos < LID_RESUME_MAX) अणु
		अगर (&lid_ctl->attrs[pos].attr == &attr->attr)
			वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n",
					(lid_ctl->status >> pos) & 0x01);
		pos++;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sony_nc_lid_resume_setup(काष्ठा platक्रमm_device *pd,
					अचिन्हित पूर्णांक handle)
अणु
	अचिन्हित पूर्णांक result;
	पूर्णांक i;

	अगर (sony_call_snc_handle(handle, 0x0000, &result))
		वापस -EIO;

	lid_ctl = kzalloc(माप(काष्ठा snc_lid_resume_control), GFP_KERNEL);
	अगर (!lid_ctl)
		वापस -ENOMEM;

	lid_ctl->status = result & 0x7;
	lid_ctl->handle = handle;

	sysfs_attr_init(&lid_ctl->attrs[0].attr);
	lid_ctl->attrs[LID_RESUME_S5].attr.name = "lid_resume_S5";
	lid_ctl->attrs[LID_RESUME_S5].attr.mode = S_IRUGO | S_IWUSR;
	lid_ctl->attrs[LID_RESUME_S5].show = sony_nc_lid_resume_show;
	lid_ctl->attrs[LID_RESUME_S5].store = sony_nc_lid_resume_store;

	अगर (handle == 0x0119) अणु
		sysfs_attr_init(&lid_ctl->attrs[1].attr);
		lid_ctl->attrs[LID_RESUME_S4].attr.name = "lid_resume_S4";
		lid_ctl->attrs[LID_RESUME_S4].attr.mode = S_IRUGO | S_IWUSR;
		lid_ctl->attrs[LID_RESUME_S4].show = sony_nc_lid_resume_show;
		lid_ctl->attrs[LID_RESUME_S4].store = sony_nc_lid_resume_store;

		sysfs_attr_init(&lid_ctl->attrs[2].attr);
		lid_ctl->attrs[LID_RESUME_S3].attr.name = "lid_resume_S3";
		lid_ctl->attrs[LID_RESUME_S3].attr.mode = S_IRUGO | S_IWUSR;
		lid_ctl->attrs[LID_RESUME_S3].show = sony_nc_lid_resume_show;
		lid_ctl->attrs[LID_RESUME_S3].store = sony_nc_lid_resume_store;
	पूर्ण
	क्रम (i = 0; i < LID_RESUME_MAX &&
			lid_ctl->attrs[i].attr.name; i++) अणु
		result = device_create_file(&pd->dev, &lid_ctl->attrs[i]);
		अगर (result)
			जाओ liderror;
	पूर्ण

	वापस 0;

liderror:
	क्रम (i--; i >= 0; i--)
		device_हटाओ_file(&pd->dev, &lid_ctl->attrs[i]);

	kमुक्त(lid_ctl);
	lid_ctl = शून्य;

	वापस result;
पूर्ण

अटल व्योम sony_nc_lid_resume_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	पूर्णांक i;

	अगर (lid_ctl) अणु
		क्रम (i = 0; i < LID_RESUME_MAX; i++) अणु
			अगर (!lid_ctl->attrs[i].attr.name)
				अवरोध;

			device_हटाओ_file(&pd->dev, &lid_ctl->attrs[i]);
		पूर्ण

		kमुक्त(lid_ctl);
		lid_ctl = शून्य;
	पूर्ण
पूर्ण

/* GFX Switch position */
क्रमागत gfx_चयन अणु
	SPEED,
	STAMINA,
	AUTO
पूर्ण;
काष्ठा snc_gfx_चयन_control अणु
	काष्ठा device_attribute attr;
	अचिन्हित पूर्णांक handle;
पूर्ण;
अटल काष्ठा snc_gfx_चयन_control *gfxs_ctl;

/* वापसs 0 क्रम speed, 1 क्रम stamina */
अटल पूर्णांक __sony_nc_gfx_चयन_status_get(व्योम)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(gfxs_ctl->handle,
				gfxs_ctl->handle == 0x015B ? 0x0000 : 0x0100,
				&result))
		वापस -EIO;

	चयन (gfxs_ctl->handle) अणु
	हाल 0x0146:
		/* 1: discrete GFX (speed)
		 * 0: पूर्णांकegrated GFX (stamina)
		 */
		वापस result & 0x1 ? SPEED : STAMINA;
	हाल 0x015B:
		/* 0: discrete GFX (speed)
		 * 1: पूर्णांकegrated GFX (stamina)
		 */
		वापस result & 0x1 ? STAMINA : SPEED;
	हाल 0x0128:
		/* it's a more elaborated biपंचांगask, क्रम now:
		 * 2: पूर्णांकegrated GFX (stamina)
		 * 0: discrete GFX (speed)
		 */
		dprपूर्णांकk("GFX Status: 0x%x\n", result);
		वापस result & 0x80 ? AUTO :
			result & 0x02 ? STAMINA : SPEED;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार sony_nc_gfx_चयन_status_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buffer)
अणु
	पूर्णांक pos = __sony_nc_gfx_चयन_status_get();

	अगर (pos < 0)
		वापस pos;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%s\n",
					pos == SPEED ? "speed" :
					pos == STAMINA ? "stamina" :
					pos == AUTO ? "auto" : "unknown");
पूर्ण

अटल पूर्णांक sony_nc_gfx_चयन_setup(काष्ठा platक्रमm_device *pd,
		अचिन्हित पूर्णांक handle)
अणु
	अचिन्हित पूर्णांक result;

	gfxs_ctl = kzalloc(माप(काष्ठा snc_gfx_चयन_control), GFP_KERNEL);
	अगर (!gfxs_ctl)
		वापस -ENOMEM;

	gfxs_ctl->handle = handle;

	sysfs_attr_init(&gfxs_ctl->attr.attr);
	gfxs_ctl->attr.attr.name = "gfx_switch_status";
	gfxs_ctl->attr.attr.mode = S_IRUGO;
	gfxs_ctl->attr.show = sony_nc_gfx_चयन_status_show;

	result = device_create_file(&pd->dev, &gfxs_ctl->attr);
	अगर (result)
		जाओ gfxerror;

	वापस 0;

gfxerror:
	kमुक्त(gfxs_ctl);
	gfxs_ctl = शून्य;

	वापस result;
पूर्ण

अटल व्योम sony_nc_gfx_चयन_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (gfxs_ctl) अणु
		device_हटाओ_file(&pd->dev, &gfxs_ctl->attr);

		kमुक्त(gfxs_ctl);
		gfxs_ctl = शून्य;
	पूर्ण
पूर्ण

/* High speed अक्षरging function */
अटल काष्ठा device_attribute *hsc_handle;

अटल sमाप_प्रकार sony_nc_highspeed_अक्षरging_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ value;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value) || value > 1)
		वापस -EINVAL;

	अगर (sony_call_snc_handle(0x0131, value << 0x10 | 0x0200, &result))
		वापस -EIO;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_highspeed_अक्षरging_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(0x0131, 0x0100, &result))
		वापस -EIO;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", result & 0x01);
पूर्ण

अटल पूर्णांक sony_nc_highspeed_अक्षरging_setup(काष्ठा platक्रमm_device *pd)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(0x0131, 0x0000, &result) || !(result & 0x01)) अणु
		/* some models advertise the handle but have no implementation
		 * क्रम it
		 */
		pr_info("No High Speed Charging capability found\n");
		वापस 0;
	पूर्ण

	hsc_handle = kzalloc(माप(काष्ठा device_attribute), GFP_KERNEL);
	अगर (!hsc_handle)
		वापस -ENOMEM;

	sysfs_attr_init(&hsc_handle->attr);
	hsc_handle->attr.name = "battery_highspeed_charging";
	hsc_handle->attr.mode = S_IRUGO | S_IWUSR;
	hsc_handle->show = sony_nc_highspeed_अक्षरging_show;
	hsc_handle->store = sony_nc_highspeed_अक्षरging_store;

	result = device_create_file(&pd->dev, hsc_handle);
	अगर (result) अणु
		kमुक्त(hsc_handle);
		hsc_handle = शून्य;
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sony_nc_highspeed_अक्षरging_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (hsc_handle) अणु
		device_हटाओ_file(&pd->dev, hsc_handle);
		kमुक्त(hsc_handle);
		hsc_handle = शून्य;
	पूर्ण
पूर्ण

/* low battery function */
अटल काष्ठा device_attribute *lowbatt_handle;

अटल sमाप_प्रकार sony_nc_lowbatt_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ value;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value) || value > 1)
		वापस -EINVAL;

	अगर (sony_call_snc_handle(0x0121, value << 8, &result))
		वापस -EIO;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_lowbatt_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(0x0121, 0x0200, &result))
		वापस -EIO;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", result & 1);
पूर्ण

अटल पूर्णांक sony_nc_lowbatt_setup(काष्ठा platक्रमm_device *pd)
अणु
	अचिन्हित पूर्णांक result;

	lowbatt_handle = kzalloc(माप(काष्ठा device_attribute), GFP_KERNEL);
	अगर (!lowbatt_handle)
		वापस -ENOMEM;

	sysfs_attr_init(&lowbatt_handle->attr);
	lowbatt_handle->attr.name = "lowbatt_hibernate";
	lowbatt_handle->attr.mode = S_IRUGO | S_IWUSR;
	lowbatt_handle->show = sony_nc_lowbatt_show;
	lowbatt_handle->store = sony_nc_lowbatt_store;

	result = device_create_file(&pd->dev, lowbatt_handle);
	अगर (result) अणु
		kमुक्त(lowbatt_handle);
		lowbatt_handle = शून्य;
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sony_nc_lowbatt_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (lowbatt_handle) अणु
		device_हटाओ_file(&pd->dev, lowbatt_handle);
		kमुक्त(lowbatt_handle);
		lowbatt_handle = शून्य;
	पूर्ण
पूर्ण

/* fan speed function */
अटल काष्ठा device_attribute *fan_handle, *hsf_handle;

अटल sमाप_प्रकार sony_nc_hsfan_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ value;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value) || value > 1)
		वापस -EINVAL;

	अगर (sony_call_snc_handle(0x0149, value << 0x10 | 0x0200, &result))
		वापस -EIO;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_hsfan_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(0x0149, 0x0100, &result))
		वापस -EIO;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", result & 0x01);
पूर्ण

अटल sमाप_प्रकार sony_nc_fanspeed_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(0x0149, 0x0300, &result))
		वापस -EIO;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", result & 0xff);
पूर्ण

अटल पूर्णांक sony_nc_fanspeed_setup(काष्ठा platक्रमm_device *pd)
अणु
	अचिन्हित पूर्णांक result;

	fan_handle = kzalloc(माप(काष्ठा device_attribute), GFP_KERNEL);
	अगर (!fan_handle)
		वापस -ENOMEM;

	hsf_handle = kzalloc(माप(काष्ठा device_attribute), GFP_KERNEL);
	अगर (!hsf_handle) अणु
		result = -ENOMEM;
		जाओ out_hsf_handle_alloc;
	पूर्ण

	sysfs_attr_init(&fan_handle->attr);
	fan_handle->attr.name = "fanspeed";
	fan_handle->attr.mode = S_IRUGO;
	fan_handle->show = sony_nc_fanspeed_show;
	fan_handle->store = शून्य;

	sysfs_attr_init(&hsf_handle->attr);
	hsf_handle->attr.name = "fan_forced";
	hsf_handle->attr.mode = S_IRUGO | S_IWUSR;
	hsf_handle->show = sony_nc_hsfan_show;
	hsf_handle->store = sony_nc_hsfan_store;

	result = device_create_file(&pd->dev, fan_handle);
	अगर (result)
		जाओ out_fan_handle;

	result = device_create_file(&pd->dev, hsf_handle);
	अगर (result)
		जाओ out_hsf_handle;

	वापस 0;

out_hsf_handle:
	device_हटाओ_file(&pd->dev, fan_handle);

out_fan_handle:
	kमुक्त(hsf_handle);
	hsf_handle = शून्य;

out_hsf_handle_alloc:
	kमुक्त(fan_handle);
	fan_handle = शून्य;
	वापस result;
पूर्ण

अटल व्योम sony_nc_fanspeed_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (fan_handle) अणु
		device_हटाओ_file(&pd->dev, fan_handle);
		kमुक्त(fan_handle);
		fan_handle = शून्य;
	पूर्ण
	अगर (hsf_handle) अणु
		device_हटाओ_file(&pd->dev, hsf_handle);
		kमुक्त(hsf_handle);
		hsf_handle = शून्य;
	पूर्ण
पूर्ण

/* USB अक्षरge function */
अटल काष्ठा device_attribute *uc_handle;

अटल sमाप_प्रकार sony_nc_usb_अक्षरge_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ value;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value) || value > 1)
		वापस -EINVAL;

	अगर (sony_call_snc_handle(0x0155, value << 0x10 | 0x0100, &result))
		वापस -EIO;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_usb_अक्षरge_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(0x0155, 0x0000, &result))
		वापस -EIO;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", result & 0x01);
पूर्ण

अटल पूर्णांक sony_nc_usb_अक्षरge_setup(काष्ठा platक्रमm_device *pd)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(0x0155, 0x0000, &result) || !(result & 0x01)) अणु
		/* some models advertise the handle but have no implementation
		 * क्रम it
		 */
		pr_info("No USB Charge capability found\n");
		वापस 0;
	पूर्ण

	uc_handle = kzalloc(माप(काष्ठा device_attribute), GFP_KERNEL);
	अगर (!uc_handle)
		वापस -ENOMEM;

	sysfs_attr_init(&uc_handle->attr);
	uc_handle->attr.name = "usb_charge";
	uc_handle->attr.mode = S_IRUGO | S_IWUSR;
	uc_handle->show = sony_nc_usb_अक्षरge_show;
	uc_handle->store = sony_nc_usb_अक्षरge_store;

	result = device_create_file(&pd->dev, uc_handle);
	अगर (result) अणु
		kमुक्त(uc_handle);
		uc_handle = शून्य;
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sony_nc_usb_अक्षरge_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (uc_handle) अणु
		device_हटाओ_file(&pd->dev, uc_handle);
		kमुक्त(uc_handle);
		uc_handle = शून्य;
	पूर्ण
पूर्ण

/* Panel ID function */
अटल काष्ठा device_attribute *panel_handle;

अटल sमाप_प्रकार sony_nc_panelid_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(0x011D, 0x0000, &result))
		वापस -EIO;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", result);
पूर्ण

अटल पूर्णांक sony_nc_panelid_setup(काष्ठा platक्रमm_device *pd)
अणु
	अचिन्हित पूर्णांक result;

	panel_handle = kzalloc(माप(काष्ठा device_attribute), GFP_KERNEL);
	अगर (!panel_handle)
		वापस -ENOMEM;

	sysfs_attr_init(&panel_handle->attr);
	panel_handle->attr.name = "panel_id";
	panel_handle->attr.mode = S_IRUGO;
	panel_handle->show = sony_nc_panelid_show;
	panel_handle->store = शून्य;

	result = device_create_file(&pd->dev, panel_handle);
	अगर (result) अणु
		kमुक्त(panel_handle);
		panel_handle = शून्य;
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sony_nc_panelid_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (panel_handle) अणु
		device_हटाओ_file(&pd->dev, panel_handle);
		kमुक्त(panel_handle);
		panel_handle = शून्य;
	पूर्ण
पूर्ण

/* smart connect function */
अटल काष्ठा device_attribute *sc_handle;

अटल sमाप_प्रकार sony_nc_smart_conn_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ value;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value) || value > 1)
		वापस -EINVAL;

	अगर (sony_call_snc_handle(0x0168, value << 0x10, &result))
		वापस -EIO;

	वापस count;
पूर्ण

अटल पूर्णांक sony_nc_smart_conn_setup(काष्ठा platक्रमm_device *pd)
अणु
	अचिन्हित पूर्णांक result;

	sc_handle = kzalloc(माप(काष्ठा device_attribute), GFP_KERNEL);
	अगर (!sc_handle)
		वापस -ENOMEM;

	sysfs_attr_init(&sc_handle->attr);
	sc_handle->attr.name = "smart_connect";
	sc_handle->attr.mode = S_IWUSR;
	sc_handle->show = शून्य;
	sc_handle->store = sony_nc_smart_conn_store;

	result = device_create_file(&pd->dev, sc_handle);
	अगर (result) अणु
		kमुक्त(sc_handle);
		sc_handle = शून्य;
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sony_nc_smart_conn_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (sc_handle) अणु
		device_हटाओ_file(&pd->dev, sc_handle);
		kमुक्त(sc_handle);
		sc_handle = शून्य;
	पूर्ण
पूर्ण

/* Touchpad enable/disable */
काष्ठा touchpad_control अणु
	काष्ठा device_attribute attr;
	पूर्णांक handle;
पूर्ण;
अटल काष्ठा touchpad_control *tp_ctl;

अटल sमाप_प्रकार sony_nc_touchpad_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक result;
	अचिन्हित दीर्घ value;

	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value) || value > 1)
		वापस -EINVAL;

	/* sysfs: 0 disabled, 1 enabled
	 * EC: 0 enabled, 1 disabled
	 */
	अगर (sony_call_snc_handle(tp_ctl->handle,
				(!value << 0x10) | 0x100, &result))
		वापस -EIO;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_nc_touchpad_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	अचिन्हित पूर्णांक result;

	अगर (sony_call_snc_handle(tp_ctl->handle, 0x000, &result))
		वापस -EINVAL;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", !(result & 0x01));
पूर्ण

अटल पूर्णांक sony_nc_touchpad_setup(काष्ठा platक्रमm_device *pd,
		अचिन्हित पूर्णांक handle)
अणु
	पूर्णांक ret = 0;

	tp_ctl = kzalloc(माप(काष्ठा touchpad_control), GFP_KERNEL);
	अगर (!tp_ctl)
		वापस -ENOMEM;

	tp_ctl->handle = handle;

	sysfs_attr_init(&tp_ctl->attr.attr);
	tp_ctl->attr.attr.name = "touchpad";
	tp_ctl->attr.attr.mode = S_IRUGO | S_IWUSR;
	tp_ctl->attr.show = sony_nc_touchpad_show;
	tp_ctl->attr.store = sony_nc_touchpad_store;

	ret = device_create_file(&pd->dev, &tp_ctl->attr);
	अगर (ret) अणु
		kमुक्त(tp_ctl);
		tp_ctl = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sony_nc_touchpad_cleanup(काष्ठा platक्रमm_device *pd)
अणु
	अगर (tp_ctl) अणु
		device_हटाओ_file(&pd->dev, &tp_ctl->attr);
		kमुक्त(tp_ctl);
		tp_ctl = शून्य;
	पूर्ण
पूर्ण

अटल व्योम sony_nc_backlight_ng_पढ़ो_limits(पूर्णांक handle,
		काष्ठा sony_backlight_props *props)
अणु
	u64 offset;
	पूर्णांक i;
	पूर्णांक lvl_table_len = 0;
	u8 min = 0xff, max = 0x00;
	अचिन्हित अक्षर buffer[32] = अणु 0 पूर्ण;

	props->handle = handle;
	props->offset = 0;
	props->maxlvl = 0xff;

	offset = sony_find_snc_handle(handle);

	/* try to पढ़ो the boundaries from ACPI tables, अगर we fail the above
	 * शेषs should be reasonable
	 */
	i = sony_nc_buffer_call(sony_nc_acpi_handle, "SN06", &offset, buffer,
			32);
	अगर (i < 0)
		वापस;

	चयन (handle) अणु
	हाल 0x012f:
	हाल 0x0137:
		lvl_table_len = 9;
		अवरोध;
	हाल 0x143:
	हाल 0x14b:
	हाल 0x14c:
		lvl_table_len = 16;
		अवरोध;
	पूर्ण

	/* the buffer lists brightness levels available, brightness levels are
	 * from position 0 to 8 in the array, other values are used by ALS
	 * control.
	 */
	क्रम (i = 0; i < lvl_table_len && i < ARRAY_SIZE(buffer); i++) अणु

		dprपूर्णांकk("Brightness level: %d\n", buffer[i]);

		अगर (!buffer[i])
			अवरोध;

		अगर (buffer[i] > max)
			max = buffer[i];
		अगर (buffer[i] < min)
			min = buffer[i];
	पूर्ण
	props->offset = min;
	props->maxlvl = max;
	dprपूर्णांकk("Brightness levels: min=%d max=%d\n", props->offset,
			props->maxlvl);
पूर्ण

अटल व्योम sony_nc_backlight_setup(व्योम)
अणु
	पूर्णांक max_brightness = 0;
	स्थिर काष्ठा backlight_ops *ops = शून्य;
	काष्ठा backlight_properties props;

	अगर (sony_find_snc_handle(0x12f) >= 0) अणु
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x0100;
		sony_nc_backlight_ng_पढ़ो_limits(0x12f, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	पूर्ण अन्यथा अगर (sony_find_snc_handle(0x137) >= 0) अणु
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x0100;
		sony_nc_backlight_ng_पढ़ो_limits(0x137, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	पूर्ण अन्यथा अगर (sony_find_snc_handle(0x143) >= 0) अणु
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x3000;
		sony_nc_backlight_ng_पढ़ो_limits(0x143, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	पूर्ण अन्यथा अगर (sony_find_snc_handle(0x14b) >= 0) अणु
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x3000;
		sony_nc_backlight_ng_पढ़ो_limits(0x14b, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	पूर्ण अन्यथा अगर (sony_find_snc_handle(0x14c) >= 0) अणु
		ops = &sony_backlight_ng_ops;
		sony_bl_props.cmd_base = 0x3000;
		sony_nc_backlight_ng_पढ़ो_limits(0x14c, &sony_bl_props);
		max_brightness = sony_bl_props.maxlvl - sony_bl_props.offset;

	पूर्ण अन्यथा अगर (acpi_has_method(sony_nc_acpi_handle, "GBRT")) अणु
		ops = &sony_backlight_ops;
		max_brightness = SONY_MAX_BRIGHTNESS - 1;

	पूर्ण अन्यथा
		वापस;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = max_brightness;
	sony_bl_props.dev = backlight_device_रेजिस्टर("sony", शून्य,
						      &sony_bl_props,
						      ops, &props);

	अगर (IS_ERR(sony_bl_props.dev)) अणु
		pr_warn("unable to register backlight device\n");
		sony_bl_props.dev = शून्य;
	पूर्ण अन्यथा
		sony_bl_props.dev->props.brightness =
			ops->get_brightness(sony_bl_props.dev);
पूर्ण

अटल व्योम sony_nc_backlight_cleanup(व्योम)
अणु
	backlight_device_unरेजिस्टर(sony_bl_props.dev);
पूर्ण

अटल पूर्णांक sony_nc_add(काष्ठा acpi_device *device)
अणु
	acpi_status status;
	पूर्णांक result = 0;
	काष्ठा sony_nc_value *item;

	sony_nc_acpi_device = device;
	म_नकल(acpi_device_class(device), "sony/hotkey");

	sony_nc_acpi_handle = device->handle;

	/* पढ़ो device status */
	result = acpi_bus_get_status(device);
	/* bail IFF the above call was successful and the device is not present */
	अगर (!result && !device->status.present) अणु
		dprपूर्णांकk("Device not present\n");
		result = -ENODEV;
		जाओ outwalk;
	पूर्ण

	result = sony_pf_add();
	अगर (result)
		जाओ outpresent;

	अगर (debug) अणु
		status = acpi_walk_namespace(ACPI_TYPE_METHOD,
				sony_nc_acpi_handle, 1, sony_walk_callback,
				शून्य, शून्य, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			pr_warn("unable to walk acpi resources\n");
			result = -ENODEV;
			जाओ outpresent;
		पूर्ण
	पूर्ण

	result = sony_laptop_setup_input(device);
	अगर (result) अणु
		pr_err("Unable to create input devices\n");
		जाओ outplatक्रमm;
	पूर्ण

	अगर (acpi_has_method(sony_nc_acpi_handle, "ECON")) अणु
		पूर्णांक arg = 1;
		अगर (sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "ECON", &arg, शून्य))
			dprपूर्णांकk("ECON Method failed\n");
	पूर्ण

	अगर (acpi_has_method(sony_nc_acpi_handle, "SN00")) अणु
		dprपूर्णांकk("Doing SNC setup\n");
		/* retrieve the available handles */
		result = sony_nc_handles_setup(sony_pf_device);
		अगर (!result)
			sony_nc_function_setup(device, sony_pf_device);
	पूर्ण

	अगर (acpi_video_get_backlight_type() == acpi_backlight_venकरोr)
		sony_nc_backlight_setup();

	/* create sony_pf sysfs attributes related to the SNC device */
	क्रम (item = sony_nc_values; item->name; ++item) अणु

		अगर (!debug && item->debug)
			जारी;

		/* find the available acpiget as described in the DSDT */
		क्रम (; item->acpiget && *item->acpiget; ++item->acpiget) अणु
			अगर (acpi_has_method(sony_nc_acpi_handle,
							*item->acpiget)) अणु
				dprपूर्णांकk("Found %s getter: %s\n",
						item->name, *item->acpiget);
				item->devattr.attr.mode |= S_IRUGO;
				अवरोध;
			पूर्ण
		पूर्ण

		/* find the available acpiset as described in the DSDT */
		क्रम (; item->acpiset && *item->acpiset; ++item->acpiset) अणु
			अगर (acpi_has_method(sony_nc_acpi_handle,
							*item->acpiset)) अणु
				dprपूर्णांकk("Found %s setter: %s\n",
						item->name, *item->acpiset);
				item->devattr.attr.mode |= S_IWUSR;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (item->devattr.attr.mode != 0) अणु
			result =
			    device_create_file(&sony_pf_device->dev,
					       &item->devattr);
			अगर (result)
				जाओ out_sysfs;
		पूर्ण
	पूर्ण

	pr_info("SNC setup done.\n");
	वापस 0;

out_sysfs:
	क्रम (item = sony_nc_values; item->name; ++item) अणु
		device_हटाओ_file(&sony_pf_device->dev, &item->devattr);
	पूर्ण
	sony_nc_backlight_cleanup();
	sony_nc_function_cleanup(sony_pf_device);
	sony_nc_handles_cleanup(sony_pf_device);

outplatक्रमm:
	sony_laptop_हटाओ_input();

outpresent:
	sony_pf_हटाओ();

outwalk:
	sony_nc_rfसमाप्त_cleanup();
	वापस result;
पूर्ण

अटल पूर्णांक sony_nc_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा sony_nc_value *item;

	sony_nc_backlight_cleanup();

	sony_nc_acpi_device = शून्य;

	क्रम (item = sony_nc_values; item->name; ++item) अणु
		device_हटाओ_file(&sony_pf_device->dev, &item->devattr);
	पूर्ण

	sony_nc_function_cleanup(sony_pf_device);
	sony_nc_handles_cleanup(sony_pf_device);
	sony_pf_हटाओ();
	sony_laptop_हटाओ_input();
	dprपूर्णांकk(SONY_NC_DRIVER_NAME " removed.\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id sony_device_ids[] = अणु
	अणुSONY_NC_HID, 0पूर्ण,
	अणुSONY_PIC_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sony_device_ids);

अटल स्थिर काष्ठा acpi_device_id sony_nc_device_ids[] = अणु
	अणुSONY_NC_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver sony_nc_driver = अणु
	.name = SONY_NC_DRIVER_NAME,
	.class = SONY_NC_CLASS,
	.ids = sony_nc_device_ids,
	.owner = THIS_MODULE,
	.ops = अणु
		.add = sony_nc_add,
		.हटाओ = sony_nc_हटाओ,
		.notअगरy = sony_nc_notअगरy,
		पूर्ण,
	.drv.pm = &sony_nc_pm,
पूर्ण;

/*********** SPIC (SNY6001) Device ***********/

#घोषणा SONYPI_DEVICE_TYPE1	0x00000001
#घोषणा SONYPI_DEVICE_TYPE2	0x00000002
#घोषणा SONYPI_DEVICE_TYPE3	0x00000004

#घोषणा SONYPI_TYPE1_OFFSET	0x04
#घोषणा SONYPI_TYPE2_OFFSET	0x12
#घोषणा SONYPI_TYPE3_OFFSET	0x12

काष्ठा sony_pic_ioport अणु
	काष्ठा acpi_resource_io	io1;
	काष्ठा acpi_resource_io	io2;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा sony_pic_irq अणु
	काष्ठा acpi_resource_irq	irq;
	काष्ठा list_head		list;
पूर्ण;

काष्ठा sonypi_eventtypes अणु
	u8			data;
	अचिन्हित दीर्घ		mask;
	काष्ठा sonypi_event	*events;
पूर्ण;

काष्ठा sony_pic_dev अणु
	काष्ठा acpi_device		*acpi_dev;
	काष्ठा sony_pic_irq		*cur_irq;
	काष्ठा sony_pic_ioport		*cur_ioport;
	काष्ठा list_head		पूर्णांकerrupts;
	काष्ठा list_head		ioports;
	काष्ठा mutex			lock;
	काष्ठा sonypi_eventtypes	*event_types;
	पूर्णांक                             (*handle_irq)(स्थिर u8, स्थिर u8);
	पूर्णांक				model;
	u16				evport_offset;
	u8				camera_घातer;
	u8				bluetooth_घातer;
	u8				wwan_घातer;
पूर्ण;

अटल काष्ठा sony_pic_dev spic_dev = अणु
	.पूर्णांकerrupts	= LIST_HEAD_INIT(spic_dev.पूर्णांकerrupts),
	.ioports	= LIST_HEAD_INIT(spic_dev.ioports),
पूर्ण;

अटल पूर्णांक spic_drv_रेजिस्टरed;

/* Event masks */
#घोषणा SONYPI_JOGGER_MASK			0x00000001
#घोषणा SONYPI_CAPTURE_MASK			0x00000002
#घोषणा SONYPI_FNKEY_MASK			0x00000004
#घोषणा SONYPI_BLUETOOTH_MASK			0x00000008
#घोषणा SONYPI_PKEY_MASK			0x00000010
#घोषणा SONYPI_BACK_MASK			0x00000020
#घोषणा SONYPI_HELP_MASK			0x00000040
#घोषणा SONYPI_LID_MASK				0x00000080
#घोषणा SONYPI_ZOOM_MASK			0x00000100
#घोषणा SONYPI_THUMBPHRASE_MASK			0x00000200
#घोषणा SONYPI_MEYE_MASK			0x00000400
#घोषणा SONYPI_MEMORYSTICK_MASK			0x00000800
#घोषणा SONYPI_BATTERY_MASK			0x00001000
#घोषणा SONYPI_WIRELESS_MASK			0x00002000

काष्ठा sonypi_event अणु
	u8	data;
	u8	event;
पूर्ण;

/* The set of possible button release events */
अटल काष्ठा sonypi_event sonypi_releaseev[] = अणु
	अणु 0x00, SONYPI_EVENT_ANYBUTTON_RELEASED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible jogger events  */
अटल काष्ठा sonypi_event sonypi_joggerev[] = अणु
	अणु 0x1f, SONYPI_EVENT_JOGDIAL_UP पूर्ण,
	अणु 0x01, SONYPI_EVENT_JOGDIAL_DOWN पूर्ण,
	अणु 0x5f, SONYPI_EVENT_JOGDIAL_UP_PRESSED पूर्ण,
	अणु 0x41, SONYPI_EVENT_JOGDIAL_DOWN_PRESSED पूर्ण,
	अणु 0x1e, SONYPI_EVENT_JOGDIAL_FAST_UP पूर्ण,
	अणु 0x02, SONYPI_EVENT_JOGDIAL_FAST_DOWN पूर्ण,
	अणु 0x5e, SONYPI_EVENT_JOGDIAL_FAST_UP_PRESSED पूर्ण,
	अणु 0x42, SONYPI_EVENT_JOGDIAL_FAST_DOWN_PRESSED पूर्ण,
	अणु 0x1d, SONYPI_EVENT_JOGDIAL_VFAST_UP पूर्ण,
	अणु 0x03, SONYPI_EVENT_JOGDIAL_VFAST_DOWN पूर्ण,
	अणु 0x5d, SONYPI_EVENT_JOGDIAL_VFAST_UP_PRESSED पूर्ण,
	अणु 0x43, SONYPI_EVENT_JOGDIAL_VFAST_DOWN_PRESSED पूर्ण,
	अणु 0x40, SONYPI_EVENT_JOGDIAL_PRESSED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible capture button events */
अटल काष्ठा sonypi_event sonypi_captureev[] = अणु
	अणु 0x05, SONYPI_EVENT_CAPTURE_PARTIALPRESSED पूर्ण,
	अणु 0x07, SONYPI_EVENT_CAPTURE_PRESSED पूर्ण,
	अणु 0x40, SONYPI_EVENT_CAPTURE_PRESSED पूर्ण,
	अणु 0x01, SONYPI_EVENT_CAPTURE_PARTIALRELEASED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible fnkeys events */
अटल काष्ठा sonypi_event sonypi_fnkeyev[] = अणु
	अणु 0x10, SONYPI_EVENT_FNKEY_ESC पूर्ण,
	अणु 0x11, SONYPI_EVENT_FNKEY_F1 पूर्ण,
	अणु 0x12, SONYPI_EVENT_FNKEY_F2 पूर्ण,
	अणु 0x13, SONYPI_EVENT_FNKEY_F3 पूर्ण,
	अणु 0x14, SONYPI_EVENT_FNKEY_F4 पूर्ण,
	अणु 0x15, SONYPI_EVENT_FNKEY_F5 पूर्ण,
	अणु 0x16, SONYPI_EVENT_FNKEY_F6 पूर्ण,
	अणु 0x17, SONYPI_EVENT_FNKEY_F7 पूर्ण,
	अणु 0x18, SONYPI_EVENT_FNKEY_F8 पूर्ण,
	अणु 0x19, SONYPI_EVENT_FNKEY_F9 पूर्ण,
	अणु 0x1a, SONYPI_EVENT_FNKEY_F10 पूर्ण,
	अणु 0x1b, SONYPI_EVENT_FNKEY_F11 पूर्ण,
	अणु 0x1c, SONYPI_EVENT_FNKEY_F12 पूर्ण,
	अणु 0x1f, SONYPI_EVENT_FNKEY_RELEASED पूर्ण,
	अणु 0x21, SONYPI_EVENT_FNKEY_1 पूर्ण,
	अणु 0x22, SONYPI_EVENT_FNKEY_2 पूर्ण,
	अणु 0x31, SONYPI_EVENT_FNKEY_D पूर्ण,
	अणु 0x32, SONYPI_EVENT_FNKEY_E पूर्ण,
	अणु 0x33, SONYPI_EVENT_FNKEY_F पूर्ण,
	अणु 0x34, SONYPI_EVENT_FNKEY_S पूर्ण,
	अणु 0x35, SONYPI_EVENT_FNKEY_B पूर्ण,
	अणु 0x36, SONYPI_EVENT_FNKEY_ONLY पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible program key events */
अटल काष्ठा sonypi_event sonypi_pkeyev[] = अणु
	अणु 0x01, SONYPI_EVENT_PKEY_P1 पूर्ण,
	अणु 0x02, SONYPI_EVENT_PKEY_P2 पूर्ण,
	अणु 0x04, SONYPI_EVENT_PKEY_P3 पूर्ण,
	अणु 0x20, SONYPI_EVENT_PKEY_P1 पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible bluetooth events */
अटल काष्ठा sonypi_event sonypi_blueev[] = अणु
	अणु 0x55, SONYPI_EVENT_BLUETOOTH_PRESSED पूर्ण,
	अणु 0x59, SONYPI_EVENT_BLUETOOTH_ON पूर्ण,
	अणु 0x5a, SONYPI_EVENT_BLUETOOTH_OFF पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible wireless events */
अटल काष्ठा sonypi_event sonypi_wlessev[] = अणु
	अणु 0x59, SONYPI_EVENT_IGNORE पूर्ण,
	अणु 0x5a, SONYPI_EVENT_IGNORE पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible back button events */
अटल काष्ठा sonypi_event sonypi_backev[] = अणु
	अणु 0x20, SONYPI_EVENT_BACK_PRESSED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible help button events */
अटल काष्ठा sonypi_event sonypi_helpev[] = अणु
	अणु 0x3b, SONYPI_EVENT_HELP_PRESSED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;


/* The set of possible lid events */
अटल काष्ठा sonypi_event sonypi_lidev[] = अणु
	अणु 0x51, SONYPI_EVENT_LID_CLOSED पूर्ण,
	अणु 0x50, SONYPI_EVENT_LID_OPENED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible zoom events */
अटल काष्ठा sonypi_event sonypi_zoomev[] = अणु
	अणु 0x39, SONYPI_EVENT_ZOOM_PRESSED पूर्ण,
	अणु 0x10, SONYPI_EVENT_ZOOM_IN_PRESSED पूर्ण,
	अणु 0x20, SONYPI_EVENT_ZOOM_OUT_PRESSED पूर्ण,
	अणु 0x04, SONYPI_EVENT_ZOOM_PRESSED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible thumbphrase events */
अटल काष्ठा sonypi_event sonypi_thumbphraseev[] = अणु
	अणु 0x3a, SONYPI_EVENT_THUMBPHRASE_PRESSED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible motioneye camera events */
अटल काष्ठा sonypi_event sonypi_meyeev[] = अणु
	अणु 0x00, SONYPI_EVENT_MEYE_FACE पूर्ण,
	अणु 0x01, SONYPI_EVENT_MEYE_OPPOSITE पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible memorystick events */
अटल काष्ठा sonypi_event sonypi_memorystickev[] = अणु
	अणु 0x53, SONYPI_EVENT_MEMORYSTICK_INSERT पूर्ण,
	अणु 0x54, SONYPI_EVENT_MEMORYSTICK_EJECT पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible battery events */
अटल काष्ठा sonypi_event sonypi_batteryev[] = अणु
	अणु 0x20, SONYPI_EVENT_BATTERY_INSERT पूर्ण,
	अणु 0x30, SONYPI_EVENT_BATTERY_REMOVE पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible volume events */
अटल काष्ठा sonypi_event sonypi_volumeev[] = अणु
	अणु 0x01, SONYPI_EVENT_VOLUME_INC_PRESSED पूर्ण,
	अणु 0x02, SONYPI_EVENT_VOLUME_DEC_PRESSED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/* The set of possible brightness events */
अटल काष्ठा sonypi_event sonypi_brightnessev[] = अणु
	अणु 0x80, SONYPI_EVENT_BRIGHTNESS_PRESSED पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा sonypi_eventtypes type1_events[] = अणु
	अणु 0, 0xffffffff, sonypi_releaseev पूर्ण,
	अणु 0x70, SONYPI_MEYE_MASK, sonypi_meyeev पूर्ण,
	अणु 0x30, SONYPI_LID_MASK, sonypi_lidev पूर्ण,
	अणु 0x60, SONYPI_CAPTURE_MASK, sonypi_captureev पूर्ण,
	अणु 0x10, SONYPI_JOGGER_MASK, sonypi_joggerev पूर्ण,
	अणु 0x20, SONYPI_FNKEY_MASK, sonypi_fnkeyev पूर्ण,
	अणु 0x30, SONYPI_BLUETOOTH_MASK, sonypi_blueev पूर्ण,
	अणु 0x40, SONYPI_PKEY_MASK, sonypi_pkeyev पूर्ण,
	अणु 0x30, SONYPI_MEMORYSTICK_MASK, sonypi_memorystickev पूर्ण,
	अणु 0x40, SONYPI_BATTERY_MASK, sonypi_batteryev पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
अटल काष्ठा sonypi_eventtypes type2_events[] = अणु
	अणु 0, 0xffffffff, sonypi_releaseev पूर्ण,
	अणु 0x38, SONYPI_LID_MASK, sonypi_lidev पूर्ण,
	अणु 0x11, SONYPI_JOGGER_MASK, sonypi_joggerev पूर्ण,
	अणु 0x61, SONYPI_CAPTURE_MASK, sonypi_captureev पूर्ण,
	अणु 0x21, SONYPI_FNKEY_MASK, sonypi_fnkeyev पूर्ण,
	अणु 0x31, SONYPI_BLUETOOTH_MASK, sonypi_blueev पूर्ण,
	अणु 0x08, SONYPI_PKEY_MASK, sonypi_pkeyev पूर्ण,
	अणु 0x11, SONYPI_BACK_MASK, sonypi_backev पूर्ण,
	अणु 0x21, SONYPI_HELP_MASK, sonypi_helpev पूर्ण,
	अणु 0x21, SONYPI_ZOOM_MASK, sonypi_zoomev पूर्ण,
	अणु 0x20, SONYPI_THUMBPHRASE_MASK, sonypi_thumbphraseev पूर्ण,
	अणु 0x31, SONYPI_MEMORYSTICK_MASK, sonypi_memorystickev पूर्ण,
	अणु 0x41, SONYPI_BATTERY_MASK, sonypi_batteryev पूर्ण,
	अणु 0x31, SONYPI_PKEY_MASK, sonypi_pkeyev पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
अटल काष्ठा sonypi_eventtypes type3_events[] = अणु
	अणु 0, 0xffffffff, sonypi_releaseev पूर्ण,
	अणु 0x21, SONYPI_FNKEY_MASK, sonypi_fnkeyev पूर्ण,
	अणु 0x31, SONYPI_WIRELESS_MASK, sonypi_wlessev पूर्ण,
	अणु 0x31, SONYPI_MEMORYSTICK_MASK, sonypi_memorystickev पूर्ण,
	अणु 0x41, SONYPI_BATTERY_MASK, sonypi_batteryev पूर्ण,
	अणु 0x31, SONYPI_PKEY_MASK, sonypi_pkeyev पूर्ण,
	अणु 0x05, SONYPI_PKEY_MASK, sonypi_pkeyev पूर्ण,
	अणु 0x05, SONYPI_ZOOM_MASK, sonypi_zoomev पूर्ण,
	अणु 0x05, SONYPI_CAPTURE_MASK, sonypi_captureev पूर्ण,
	अणु 0x05, SONYPI_PKEY_MASK, sonypi_volumeev पूर्ण,
	अणु 0x05, SONYPI_PKEY_MASK, sonypi_brightnessev पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

/* low level spic calls */
#घोषणा ITERATIONS_LONG		10000
#घोषणा ITERATIONS_SHORT	10
#घोषणा रुको_on_command(command, iterations) अणु				\
	अचिन्हित पूर्णांक n = iterations;					\
	जबतक (--n && (command))					\
		udelay(1);						\
	अगर (!n)								\
		dprपूर्णांकk("command failed at %s : %s (line %d)\n",	\
				__खाता__, __func__, __LINE__);	\
पूर्ण

अटल u8 sony_pic_call1(u8 dev)
अणु
	u8 v1, v2;

	रुको_on_command(inb_p(spic_dev.cur_ioport->io1.minimum + 4) & 2,
			ITERATIONS_LONG);
	outb(dev, spic_dev.cur_ioport->io1.minimum + 4);
	v1 = inb_p(spic_dev.cur_ioport->io1.minimum + 4);
	v2 = inb_p(spic_dev.cur_ioport->io1.minimum);
	dprपूर्णांकk("sony_pic_call1(0x%.2x): 0x%.4x\n", dev, (v2 << 8) | v1);
	वापस v2;
पूर्ण

अटल u8 sony_pic_call2(u8 dev, u8 fn)
अणु
	u8 v1;

	रुको_on_command(inb_p(spic_dev.cur_ioport->io1.minimum + 4) & 2,
			ITERATIONS_LONG);
	outb(dev, spic_dev.cur_ioport->io1.minimum + 4);
	रुको_on_command(inb_p(spic_dev.cur_ioport->io1.minimum + 4) & 2,
			ITERATIONS_LONG);
	outb(fn, spic_dev.cur_ioport->io1.minimum);
	v1 = inb_p(spic_dev.cur_ioport->io1.minimum);
	dprपूर्णांकk("sony_pic_call2(0x%.2x - 0x%.2x): 0x%.4x\n", dev, fn, v1);
	वापस v1;
पूर्ण

अटल u8 sony_pic_call3(u8 dev, u8 fn, u8 v)
अणु
	u8 v1;

	रुको_on_command(inb_p(spic_dev.cur_ioport->io1.minimum + 4) & 2, ITERATIONS_LONG);
	outb(dev, spic_dev.cur_ioport->io1.minimum + 4);
	रुको_on_command(inb_p(spic_dev.cur_ioport->io1.minimum + 4) & 2, ITERATIONS_LONG);
	outb(fn, spic_dev.cur_ioport->io1.minimum);
	रुको_on_command(inb_p(spic_dev.cur_ioport->io1.minimum + 4) & 2, ITERATIONS_LONG);
	outb(v, spic_dev.cur_ioport->io1.minimum);
	v1 = inb_p(spic_dev.cur_ioport->io1.minimum);
	dprपूर्णांकk("sony_pic_call3(0x%.2x - 0x%.2x - 0x%.2x): 0x%.4x\n",
			dev, fn, v, v1);
	वापस v1;
पूर्ण

/*
 * minidrivers क्रम SPIC models
 */
अटल पूर्णांक type3_handle_irq(स्थिर u8 data_mask, स्थिर u8 ev)
अणु
	/*
	 * 0x31 could mean we have to take some extra action and रुको क्रम
	 * the next irq क्रम some Type3 models, it will generate a new
	 * irq and we can पढ़ो new data from the device:
	 *  - 0x5c and 0x5f requires 0xA0
	 *  - 0x61 requires 0xB3
	 */
	अगर (data_mask == 0x31) अणु
		अगर (ev == 0x5c || ev == 0x5f)
			sony_pic_call1(0xA0);
		अन्यथा अगर (ev == 0x61)
			sony_pic_call1(0xB3);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम sony_pic_detect_device_type(काष्ठा sony_pic_dev *dev)
अणु
	काष्ठा pci_dev *pcidev;

	pcidev = pci_get_device(PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_82371AB_3, शून्य);
	अगर (pcidev) अणु
		dev->model = SONYPI_DEVICE_TYPE1;
		dev->evport_offset = SONYPI_TYPE1_OFFSET;
		dev->event_types = type1_events;
		जाओ out;
	पूर्ण

	pcidev = pci_get_device(PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_ICH6_1, शून्य);
	अगर (pcidev) अणु
		dev->model = SONYPI_DEVICE_TYPE2;
		dev->evport_offset = SONYPI_TYPE2_OFFSET;
		dev->event_types = type2_events;
		जाओ out;
	पूर्ण

	pcidev = pci_get_device(PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_ICH7_1, शून्य);
	अगर (pcidev) अणु
		dev->model = SONYPI_DEVICE_TYPE3;
		dev->handle_irq = type3_handle_irq;
		dev->evport_offset = SONYPI_TYPE3_OFFSET;
		dev->event_types = type3_events;
		जाओ out;
	पूर्ण

	pcidev = pci_get_device(PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_ICH8_4, शून्य);
	अगर (pcidev) अणु
		dev->model = SONYPI_DEVICE_TYPE3;
		dev->handle_irq = type3_handle_irq;
		dev->evport_offset = SONYPI_TYPE3_OFFSET;
		dev->event_types = type3_events;
		जाओ out;
	पूर्ण

	pcidev = pci_get_device(PCI_VENDOR_ID_INTEL,
			PCI_DEVICE_ID_INTEL_ICH9_1, शून्य);
	अगर (pcidev) अणु
		dev->model = SONYPI_DEVICE_TYPE3;
		dev->handle_irq = type3_handle_irq;
		dev->evport_offset = SONYPI_TYPE3_OFFSET;
		dev->event_types = type3_events;
		जाओ out;
	पूर्ण

	/* शेष */
	dev->model = SONYPI_DEVICE_TYPE2;
	dev->evport_offset = SONYPI_TYPE2_OFFSET;
	dev->event_types = type2_events;

out:
	pci_dev_put(pcidev);

	pr_info("detected Type%d model\n",
		dev->model == SONYPI_DEVICE_TYPE1 ? 1 :
		dev->model == SONYPI_DEVICE_TYPE2 ? 2 : 3);
पूर्ण

/* camera tests and घातeron/घातeroff */
#घोषणा SONYPI_CAMERA_PICTURE		5
#घोषणा SONYPI_CAMERA_CONTROL		0x10

#घोषणा SONYPI_CAMERA_BRIGHTNESS		0
#घोषणा SONYPI_CAMERA_CONTRAST			1
#घोषणा SONYPI_CAMERA_HUE			2
#घोषणा SONYPI_CAMERA_COLOR			3
#घोषणा SONYPI_CAMERA_SHARPNESS			4

#घोषणा SONYPI_CAMERA_EXPOSURE_MASK		0xC
#घोषणा SONYPI_CAMERA_WHITE_BALANCE_MASK	0x3
#घोषणा SONYPI_CAMERA_PICTURE_MODE_MASK		0x30
#घोषणा SONYPI_CAMERA_MUTE_MASK			0x40

/* the rest करोn't need a loop until not 0xff */
#घोषणा SONYPI_CAMERA_AGC			6
#घोषणा SONYPI_CAMERA_AGC_MASK			0x30
#घोषणा SONYPI_CAMERA_SHUTTER_MASK 		0x7

#घोषणा SONYPI_CAMERA_SHUTDOWN_REQUEST		7
#घोषणा SONYPI_CAMERA_CONTROL			0x10

#घोषणा SONYPI_CAMERA_STATUS 			7
#घोषणा SONYPI_CAMERA_STATUS_READY 		0x2
#घोषणा SONYPI_CAMERA_STATUS_POSITION		0x4

#घोषणा SONYPI_सूचीECTION_BACKWARDS 		0x4

#घोषणा SONYPI_CAMERA_REVISION 			8
#घोषणा SONYPI_CAMERA_ROMVERSION 		9

अटल पूर्णांक __sony_pic_camera_पढ़ोy(व्योम)
अणु
	u8 v;

	v = sony_pic_call2(0x8f, SONYPI_CAMERA_STATUS);
	वापस (v != 0xff && (v & SONYPI_CAMERA_STATUS_READY));
पूर्ण

अटल पूर्णांक __sony_pic_camera_off(व्योम)
अणु
	अगर (!camera) अणु
		pr_warn("camera control not enabled\n");
		वापस -ENODEV;
	पूर्ण

	रुको_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_PICTURE,
				SONYPI_CAMERA_MUTE_MASK),
			ITERATIONS_SHORT);

	अगर (spic_dev.camera_घातer) अणु
		sony_pic_call2(0x91, 0);
		spic_dev.camera_घातer = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __sony_pic_camera_on(व्योम)
अणु
	पूर्णांक i, j, x;

	अगर (!camera) अणु
		pr_warn("camera control not enabled\n");
		वापस -ENODEV;
	पूर्ण

	अगर (spic_dev.camera_घातer)
		वापस 0;

	क्रम (j = 5; j > 0; j--) अणु

		क्रम (x = 0; x < 100 && sony_pic_call2(0x91, 0x1); x++)
			msleep(10);
		sony_pic_call1(0x93);

		क्रम (i = 400; i > 0; i--) अणु
			अगर (__sony_pic_camera_पढ़ोy())
				अवरोध;
			msleep(10);
		पूर्ण
		अगर (i)
			अवरोध;
	पूर्ण

	अगर (j == 0) अणु
		pr_warn("failed to power on camera\n");
		वापस -ENODEV;
	पूर्ण

	रुको_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_CONTROL,
				0x5a),
			ITERATIONS_SHORT);

	spic_dev.camera_घातer = 1;
	वापस 0;
पूर्ण

/* External camera command (exported to the motion eye v4l driver) */
पूर्णांक sony_pic_camera_command(पूर्णांक command, u8 value)
अणु
	अगर (!camera)
		वापस -EIO;

	mutex_lock(&spic_dev.lock);

	चयन (command) अणु
	हाल SONY_PIC_COMMAND_SETCAMERA:
		अगर (value)
			__sony_pic_camera_on();
		अन्यथा
			__sony_pic_camera_off();
		अवरोध;
	हाल SONY_PIC_COMMAND_SETCAMERABRIGHTNESS:
		रुको_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_BRIGHTNESS, value),
				ITERATIONS_SHORT);
		अवरोध;
	हाल SONY_PIC_COMMAND_SETCAMERACONTRAST:
		रुको_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_CONTRAST, value),
				ITERATIONS_SHORT);
		अवरोध;
	हाल SONY_PIC_COMMAND_SETCAMERAHUE:
		रुको_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_HUE, value),
				ITERATIONS_SHORT);
		अवरोध;
	हाल SONY_PIC_COMMAND_SETCAMERACOLOR:
		रुको_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_COLOR, value),
				ITERATIONS_SHORT);
		अवरोध;
	हाल SONY_PIC_COMMAND_SETCAMERASHARPNESS:
		रुको_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_SHARPNESS, value),
				ITERATIONS_SHORT);
		अवरोध;
	हाल SONY_PIC_COMMAND_SETCAMERAPICTURE:
		रुको_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_PICTURE, value),
				ITERATIONS_SHORT);
		अवरोध;
	हाल SONY_PIC_COMMAND_SETCAMERAAGC:
		रुको_on_command(sony_pic_call3(0x90, SONYPI_CAMERA_AGC, value),
				ITERATIONS_SHORT);
		अवरोध;
	शेष:
		pr_err("sony_pic_camera_command invalid: %d\n", command);
		अवरोध;
	पूर्ण
	mutex_unlock(&spic_dev.lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sony_pic_camera_command);

/* gprs/edge modem (SZ460N and SZ210P), thanks to Joshua Wise */
अटल व्योम __sony_pic_set_wwanघातer(u8 state)
अणु
	state = !!state;
	अगर (spic_dev.wwan_घातer == state)
		वापस;
	sony_pic_call2(0xB0, state);
	sony_pic_call1(0x82);
	spic_dev.wwan_घातer = state;
पूर्ण

अटल sमाप_प्रकार sony_pic_wwanघातer_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ value;
	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value))
		वापस -EINVAL;

	mutex_lock(&spic_dev.lock);
	__sony_pic_set_wwanघातer(value);
	mutex_unlock(&spic_dev.lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_pic_wwanघातer_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	sमाप_प्रकार count;
	mutex_lock(&spic_dev.lock);
	count = snम_लिखो(buffer, PAGE_SIZE, "%d\n", spic_dev.wwan_घातer);
	mutex_unlock(&spic_dev.lock);
	वापस count;
पूर्ण

/* bluetooth subप्रणाली घातer state */
अटल व्योम __sony_pic_set_bluetoothघातer(u8 state)
अणु
	state = !!state;
	अगर (spic_dev.bluetooth_घातer == state)
		वापस;
	sony_pic_call2(0x96, state);
	sony_pic_call1(0x82);
	spic_dev.bluetooth_घातer = state;
पूर्ण

अटल sमाप_प्रकार sony_pic_bluetoothघातer_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ value;
	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value))
		वापस -EINVAL;

	mutex_lock(&spic_dev.lock);
	__sony_pic_set_bluetoothघातer(value);
	mutex_unlock(&spic_dev.lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_pic_bluetoothघातer_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	sमाप_प्रकार count = 0;
	mutex_lock(&spic_dev.lock);
	count = snम_लिखो(buffer, PAGE_SIZE, "%d\n", spic_dev.bluetooth_घातer);
	mutex_unlock(&spic_dev.lock);
	वापस count;
पूर्ण

/* fan speed */
/* FAN0 inक्रमmation (reverse engineered from ACPI tables) */
#घोषणा SONY_PIC_FAN0_STATUS	0x93
अटल पूर्णांक sony_pic_set_fanspeed(अचिन्हित दीर्घ value)
अणु
	वापस ec_ग_लिखो(SONY_PIC_FAN0_STATUS, value);
पूर्ण

अटल पूर्णांक sony_pic_get_fanspeed(u8 *value)
अणु
	वापस ec_पढ़ो(SONY_PIC_FAN0_STATUS, value);
पूर्ण

अटल sमाप_प्रकार sony_pic_fanspeed_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ value;
	अगर (count > 31)
		वापस -EINVAL;

	अगर (kम_से_अदीर्घ(buffer, 10, &value))
		वापस -EINVAL;

	अगर (sony_pic_set_fanspeed(value))
		वापस -EIO;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sony_pic_fanspeed_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buffer)
अणु
	u8 value = 0;
	अगर (sony_pic_get_fanspeed(&value))
		वापस -EIO;

	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", value);
पूर्ण

#घोषणा SPIC_ATTR(_name, _mode)					\
काष्ठा device_attribute spic_attr_##_name = __ATTR(_name,	\
		_mode, sony_pic_## _name ##_show,		\
		sony_pic_## _name ##_store)

अटल SPIC_ATTR(bluetoothघातer, 0644);
अटल SPIC_ATTR(wwanघातer, 0644);
अटल SPIC_ATTR(fanspeed, 0644);

अटल काष्ठा attribute *spic_attributes[] = अणु
	&spic_attr_bluetoothघातer.attr,
	&spic_attr_wwanघातer.attr,
	&spic_attr_fanspeed.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group spic_attribute_group = अणु
	.attrs = spic_attributes
पूर्ण;

/******** SONYPI compatibility **********/
#अगर_घोषित CONFIG_SONYPI_COMPAT

/* battery / brightness / temperature  addresses */
#घोषणा SONYPI_BAT_FLAGS	0x81
#घोषणा SONYPI_LCD_LIGHT	0x96
#घोषणा SONYPI_BAT1_PCTRM	0xa0
#घोषणा SONYPI_BAT1_LEFT	0xa2
#घोषणा SONYPI_BAT1_MAXRT	0xa4
#घोषणा SONYPI_BAT2_PCTRM	0xa8
#घोषणा SONYPI_BAT2_LEFT	0xaa
#घोषणा SONYPI_BAT2_MAXRT	0xac
#घोषणा SONYPI_BAT1_MAXTK	0xb0
#घोषणा SONYPI_BAT1_FULL	0xb2
#घोषणा SONYPI_BAT2_MAXTK	0xb8
#घोषणा SONYPI_BAT2_FULL	0xba
#घोषणा SONYPI_TEMP_STATUS	0xC1

काष्ठा sonypi_compat_s अणु
	काष्ठा fasync_काष्ठा	*fअगरo_async;
	काष्ठा kfअगरo		fअगरo;
	spinlock_t		fअगरo_lock;
	रुको_queue_head_t	fअगरo_proc_list;
	atomic_t		खोलो_count;
पूर्ण;
अटल काष्ठा sonypi_compat_s sonypi_compat = अणु
	.खोलो_count = ATOMIC_INIT(0),
पूर्ण;

अटल पूर्णांक sonypi_misc_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	वापस fasync_helper(fd, filp, on, &sonypi_compat.fअगरo_async);
पूर्ण

अटल पूर्णांक sonypi_misc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	atomic_dec(&sonypi_compat.खोलो_count);
	वापस 0;
पूर्ण

अटल पूर्णांक sonypi_misc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Flush input queue on first खोलो */
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sonypi_compat.fअगरo_lock, flags);

	अगर (atomic_inc_वापस(&sonypi_compat.खोलो_count) == 1)
		kfअगरo_reset(&sonypi_compat.fअगरo);

	spin_unlock_irqrestore(&sonypi_compat.fअगरo_lock, flags);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sonypi_misc_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *pos)
अणु
	sमाप_प्रकार ret;
	अचिन्हित अक्षर c;

	अगर ((kfअगरo_len(&sonypi_compat.fअगरo) == 0) &&
	    (file->f_flags & O_NONBLOCK))
		वापस -EAGAIN;

	ret = रुको_event_पूर्णांकerruptible(sonypi_compat.fअगरo_proc_list,
				       kfअगरo_len(&sonypi_compat.fअगरo) != 0);
	अगर (ret)
		वापस ret;

	जबतक (ret < count &&
	       (kfअगरo_out_locked(&sonypi_compat.fअगरo, &c, माप(c),
			  &sonypi_compat.fअगरo_lock) == माप(c))) अणु
		अगर (put_user(c, buf++))
			वापस -EFAULT;
		ret++;
	पूर्ण

	अगर (ret > 0) अणु
		काष्ठा inode *inode = file_inode(file);
		inode->i_aसमय = current_समय(inode);
	पूर्ण

	वापस ret;
पूर्ण

अटल __poll_t sonypi_misc_poll(काष्ठा file *file, poll_table *रुको)
अणु
	poll_रुको(file, &sonypi_compat.fअगरo_proc_list, रुको);
	अगर (kfअगरo_len(&sonypi_compat.fअगरo))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल पूर्णांक ec_पढ़ो16(u8 addr, u16 *value)
अणु
	u8 val_lb, val_hb;
	अगर (ec_पढ़ो(addr, &val_lb))
		वापस -1;
	अगर (ec_पढ़ो(addr + 1, &val_hb))
		वापस -1;
	*value = val_lb | (val_hb << 8);
	वापस 0;
पूर्ण

अटल दीर्घ sonypi_misc_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = 0;
	व्योम __user *argp = (व्योम __user *)arg;
	u8 val8;
	u16 val16;
	पूर्णांक value;

	mutex_lock(&spic_dev.lock);
	चयन (cmd) अणु
	हाल SONYPI_IOCGBRT:
		अगर (sony_bl_props.dev == शून्य) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "GBRT", शून्य,
					&value)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		val8 = ((value & 0xff) - 1) << 5;
		अगर (copy_to_user(argp, &val8, माप(val8)))
				ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCSBRT:
		अगर (sony_bl_props.dev == शून्य) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(&val8, argp, माप(val8))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		value = (val8 >> 5) + 1;
		अगर (sony_nc_पूर्णांक_call(sony_nc_acpi_handle, "SBRT", &value,
					शून्य)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		/* sync the backlight device status */
		sony_bl_props.dev->props.brightness =
		    sony_backlight_get_brightness(sony_bl_props.dev);
		अवरोध;
	हाल SONYPI_IOCGBAT1CAP:
		अगर (ec_पढ़ो16(SONYPI_BAT1_FULL, &val16)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (copy_to_user(argp, &val16, माप(val16)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCGBAT1REM:
		अगर (ec_पढ़ो16(SONYPI_BAT1_LEFT, &val16)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (copy_to_user(argp, &val16, माप(val16)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCGBAT2CAP:
		अगर (ec_पढ़ो16(SONYPI_BAT2_FULL, &val16)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (copy_to_user(argp, &val16, माप(val16)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCGBAT2REM:
		अगर (ec_पढ़ो16(SONYPI_BAT2_LEFT, &val16)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (copy_to_user(argp, &val16, माप(val16)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCGBATFLAGS:
		अगर (ec_पढ़ो(SONYPI_BAT_FLAGS, &val8)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		val8 &= 0x07;
		अगर (copy_to_user(argp, &val8, माप(val8)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCGBLUE:
		val8 = spic_dev.bluetooth_घातer;
		अगर (copy_to_user(argp, &val8, माप(val8)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCSBLUE:
		अगर (copy_from_user(&val8, argp, माप(val8))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		__sony_pic_set_bluetoothघातer(val8);
		अवरोध;
	/* FAN Controls */
	हाल SONYPI_IOCGFAN:
		अगर (sony_pic_get_fanspeed(&val8)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (copy_to_user(argp, &val8, माप(val8)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCSFAN:
		अगर (copy_from_user(&val8, argp, माप(val8))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (sony_pic_set_fanspeed(val8))
			ret = -EIO;
		अवरोध;
	/* GET Temperature (useful under APM) */
	हाल SONYPI_IOCGTEMP:
		अगर (ec_पढ़ो(SONYPI_TEMP_STATUS, &val8)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (copy_to_user(argp, &val8, माप(val8)))
			ret = -EFAULT;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&spic_dev.lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations sonypi_misc_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= sonypi_misc_पढ़ो,
	.poll		= sonypi_misc_poll,
	.खोलो		= sonypi_misc_खोलो,
	.release	= sonypi_misc_release,
	.fasync		= sonypi_misc_fasync,
	.unlocked_ioctl	= sonypi_misc_ioctl,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice sonypi_misc_device = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "sonypi",
	.fops		= &sonypi_misc_fops,
पूर्ण;

अटल व्योम sonypi_compat_report_event(u8 event)
अणु
	kfअगरo_in_locked(&sonypi_compat.fअगरo, (अचिन्हित अक्षर *)&event,
			माप(event), &sonypi_compat.fअगरo_lock);
	समाप्त_fasync(&sonypi_compat.fअगरo_async, SIGIO, POLL_IN);
	wake_up_पूर्णांकerruptible(&sonypi_compat.fअगरo_proc_list);
पूर्ण

अटल पूर्णांक sonypi_compat_init(व्योम)
अणु
	पूर्णांक error;

	spin_lock_init(&sonypi_compat.fअगरo_lock);
	error =
	 kfअगरo_alloc(&sonypi_compat.fअगरo, SONY_LAPTOP_BUF_SIZE, GFP_KERNEL);
	अगर (error) अणु
		pr_err("kfifo_alloc failed\n");
		वापस error;
	पूर्ण

	init_रुकोqueue_head(&sonypi_compat.fअगरo_proc_list);

	अगर (minor != -1)
		sonypi_misc_device.minor = minor;
	error = misc_रेजिस्टर(&sonypi_misc_device);
	अगर (error) अणु
		pr_err("misc_register failed\n");
		जाओ err_मुक्त_kfअगरo;
	पूर्ण
	अगर (minor == -1)
		pr_info("device allocated minor is %d\n",
			sonypi_misc_device.minor);

	वापस 0;

err_मुक्त_kfअगरo:
	kfअगरo_मुक्त(&sonypi_compat.fअगरo);
	वापस error;
पूर्ण

अटल व्योम sonypi_compat_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&sonypi_misc_device);
	kfअगरo_मुक्त(&sonypi_compat.fअगरo);
पूर्ण
#अन्यथा
अटल पूर्णांक sonypi_compat_init(व्योम) अणु वापस 0; पूर्ण
अटल व्योम sonypi_compat_निकास(व्योम) अणु पूर्ण
अटल व्योम sonypi_compat_report_event(u8 event) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SONYPI_COMPAT */

/*
 * ACPI callbacks
 */
अटल acpi_status
sony_pic_पढ़ो_possible_resource(काष्ठा acpi_resource *resource, व्योम *context)
अणु
	u32 i;
	काष्ठा sony_pic_dev *dev = (काष्ठा sony_pic_dev *)context;

	चयन (resource->type) अणु
	हाल ACPI_RESOURCE_TYPE_START_DEPENDENT:
		अणु
			/* start IO क्रमागतeration */
			काष्ठा sony_pic_ioport *ioport = kzalloc(माप(*ioport), GFP_KERNEL);
			अगर (!ioport)
				वापस AE_ERROR;

			list_add(&ioport->list, &dev->ioports);
			वापस AE_OK;
		पूर्ण

	हाल ACPI_RESOURCE_TYPE_END_DEPENDENT:
		/* end IO क्रमागतeration */
		वापस AE_OK;

	हाल ACPI_RESOURCE_TYPE_IRQ:
		अणु
			काष्ठा acpi_resource_irq *p = &resource->data.irq;
			काष्ठा sony_pic_irq *पूर्णांकerrupt = शून्य;
			अगर (!p || !p->पूर्णांकerrupt_count) अणु
				/*
				 * IRQ descriptors may have no IRQ# bits set,
				 * particularly those those w/ _STA disabled
				 */
				dprपूर्णांकk("Blank IRQ resource\n");
				वापस AE_OK;
			पूर्ण
			क्रम (i = 0; i < p->पूर्णांकerrupt_count; i++) अणु
				अगर (!p->पूर्णांकerrupts[i]) अणु
					pr_warn("Invalid IRQ %d\n",
						p->पूर्णांकerrupts[i]);
					जारी;
				पूर्ण
				पूर्णांकerrupt = kzalloc(माप(*पूर्णांकerrupt),
						GFP_KERNEL);
				अगर (!पूर्णांकerrupt)
					वापस AE_ERROR;

				list_add(&पूर्णांकerrupt->list, &dev->पूर्णांकerrupts);
				पूर्णांकerrupt->irq.triggering = p->triggering;
				पूर्णांकerrupt->irq.polarity = p->polarity;
				पूर्णांकerrupt->irq.shareable = p->shareable;
				पूर्णांकerrupt->irq.पूर्णांकerrupt_count = 1;
				पूर्णांकerrupt->irq.पूर्णांकerrupts[0] = p->पूर्णांकerrupts[i];
			पूर्ण
			वापस AE_OK;
		पूर्ण
	हाल ACPI_RESOURCE_TYPE_IO:
		अणु
			काष्ठा acpi_resource_io *io = &resource->data.io;
			काष्ठा sony_pic_ioport *ioport =
				list_first_entry(&dev->ioports, काष्ठा sony_pic_ioport, list);
			अगर (!io) अणु
				dprपूर्णांकk("Blank IO resource\n");
				वापस AE_OK;
			पूर्ण

			अगर (!ioport->io1.minimum) अणु
				स_नकल(&ioport->io1, io, माप(*io));
				dprपूर्णांकk("IO1 at 0x%.4x (0x%.2x)\n", ioport->io1.minimum,
						ioport->io1.address_length);
			पूर्ण
			अन्यथा अगर (!ioport->io2.minimum) अणु
				स_नकल(&ioport->io2, io, माप(*io));
				dprपूर्णांकk("IO2 at 0x%.4x (0x%.2x)\n", ioport->io2.minimum,
						ioport->io2.address_length);
			पूर्ण
			अन्यथा अणु
				pr_err("Unknown SPIC Type, more than 2 IO Ports\n");
				वापस AE_ERROR;
			पूर्ण
			वापस AE_OK;
		पूर्ण

	हाल ACPI_RESOURCE_TYPE_END_TAG:
		वापस AE_OK;

	शेष:
		dprपूर्णांकk("Resource %d isn't an IRQ nor an IO port\n",
			resource->type);
		वापस AE_CTRL_TERMINATE;

	पूर्ण
पूर्ण

अटल पूर्णांक sony_pic_possible_resources(काष्ठा acpi_device *device)
अणु
	पूर्णांक result = 0;
	acpi_status status = AE_OK;

	अगर (!device)
		वापस -EINVAL;

	/* get device status */
	/* see acpi_pci_link_get_current acpi_pci_link_get_possible */
	dprपूर्णांकk("Evaluating _STA\n");
	result = acpi_bus_get_status(device);
	अगर (result) अणु
		pr_warn("Unable to read status\n");
		जाओ end;
	पूर्ण

	अगर (!device->status.enabled)
		dprपूर्णांकk("Device disabled\n");
	अन्यथा
		dprपूर्णांकk("Device enabled\n");

	/*
	 * Query and parse 'method'
	 */
	dprपूर्णांकk("Evaluating %s\n", METHOD_NAME__PRS);
	status = acpi_walk_resources(device->handle, METHOD_NAME__PRS,
			sony_pic_पढ़ो_possible_resource, &spic_dev);
	अगर (ACPI_FAILURE(status)) अणु
		pr_warn("Failure evaluating %s\n", METHOD_NAME__PRS);
		result = -ENODEV;
	पूर्ण
end:
	वापस result;
पूर्ण

/*
 *  Disable the spic device by calling its _DIS method
 */
अटल पूर्णांक sony_pic_disable(काष्ठा acpi_device *device)
अणु
	acpi_status ret = acpi_evaluate_object(device->handle, "_DIS", शून्य,
					       शून्य);

	अगर (ACPI_FAILURE(ret) && ret != AE_NOT_FOUND)
		वापस -ENXIO;

	dprपूर्णांकk("Device disabled\n");
	वापस 0;
पूर्ण


/*
 *  Based on drivers/acpi/pci_link.c:acpi_pci_link_set
 *
 *  Call _SRS to set current resources
 */
अटल पूर्णांक sony_pic_enable(काष्ठा acpi_device *device,
		काष्ठा sony_pic_ioport *ioport, काष्ठा sony_pic_irq *irq)
अणु
	acpi_status status;
	पूर्णांक result = 0;
	/* Type 1 resource layout is:
	 *    IO
	 *    IO
	 *    IRQNoFlags
	 *    End
	 *
	 * Type 2 and 3 resource layout is:
	 *    IO
	 *    IRQNoFlags
	 *    End
	 */
	काष्ठा अणु
		काष्ठा acpi_resource res1;
		काष्ठा acpi_resource res2;
		काष्ठा acpi_resource res3;
		काष्ठा acpi_resource res4;
	पूर्ण *resource;
	काष्ठा acpi_buffer buffer = अणु 0, शून्य पूर्ण;

	अगर (!ioport || !irq)
		वापस -EINVAL;

	/* init acpi_buffer */
	resource = kzalloc(माप(*resource) + 1, GFP_KERNEL);
	अगर (!resource)
		वापस -ENOMEM;

	buffer.length = माप(*resource) + 1;
	buffer.poपूर्णांकer = resource;

	/* setup Type 1 resources */
	अगर (spic_dev.model == SONYPI_DEVICE_TYPE1) अणु

		/* setup io resources */
		resource->res1.type = ACPI_RESOURCE_TYPE_IO;
		resource->res1.length = माप(काष्ठा acpi_resource);
		स_नकल(&resource->res1.data.io, &ioport->io1,
				माप(काष्ठा acpi_resource_io));

		resource->res2.type = ACPI_RESOURCE_TYPE_IO;
		resource->res2.length = माप(काष्ठा acpi_resource);
		स_नकल(&resource->res2.data.io, &ioport->io2,
				माप(काष्ठा acpi_resource_io));

		/* setup irq resource */
		resource->res3.type = ACPI_RESOURCE_TYPE_IRQ;
		resource->res3.length = माप(काष्ठा acpi_resource);
		स_नकल(&resource->res3.data.irq, &irq->irq,
				माप(काष्ठा acpi_resource_irq));
		/* we requested a shared irq */
		resource->res3.data.irq.shareable = ACPI_SHARED;

		resource->res4.type = ACPI_RESOURCE_TYPE_END_TAG;
		resource->res4.length = माप(काष्ठा acpi_resource);
	पूर्ण
	/* setup Type 2/3 resources */
	अन्यथा अणु
		/* setup io resource */
		resource->res1.type = ACPI_RESOURCE_TYPE_IO;
		resource->res1.length = माप(काष्ठा acpi_resource);
		स_नकल(&resource->res1.data.io, &ioport->io1,
				माप(काष्ठा acpi_resource_io));

		/* setup irq resource */
		resource->res2.type = ACPI_RESOURCE_TYPE_IRQ;
		resource->res2.length = माप(काष्ठा acpi_resource);
		स_नकल(&resource->res2.data.irq, &irq->irq,
				माप(काष्ठा acpi_resource_irq));
		/* we requested a shared irq */
		resource->res2.data.irq.shareable = ACPI_SHARED;

		resource->res3.type = ACPI_RESOURCE_TYPE_END_TAG;
		resource->res3.length = माप(काष्ठा acpi_resource);
	पूर्ण

	/* Attempt to set the resource */
	dprपूर्णांकk("Evaluating _SRS\n");
	status = acpi_set_current_resources(device->handle, &buffer);

	/* check क्रम total failure */
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Error evaluating _SRS\n");
		result = -ENODEV;
		जाओ end;
	पूर्ण

	/* Necessary device initializations calls (from sonypi) */
	sony_pic_call1(0x82);
	sony_pic_call2(0x81, 0xff);
	sony_pic_call1(compat ? 0x92 : 0x82);

end:
	kमुक्त(resource);
	वापस result;
पूर्ण

/*****************
 *
 * ISR: some event is available
 *
 *****************/
अटल irqवापस_t sony_pic_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक i, j;
	u8 ev = 0;
	u8 data_mask = 0;
	u8 device_event = 0;

	काष्ठा sony_pic_dev *dev = (काष्ठा sony_pic_dev *) dev_id;

	ev = inb_p(dev->cur_ioport->io1.minimum);
	अगर (dev->cur_ioport->io2.minimum)
		data_mask = inb_p(dev->cur_ioport->io2.minimum);
	अन्यथा
		data_mask = inb_p(dev->cur_ioport->io1.minimum +
				dev->evport_offset);

	dprपूर्णांकk("event ([%.2x] [%.2x]) at port 0x%.4x(+0x%.2x)\n",
			ev, data_mask, dev->cur_ioport->io1.minimum,
			dev->evport_offset);

	अगर (ev == 0x00 || ev == 0xff)
		वापस IRQ_HANDLED;

	क्रम (i = 0; dev->event_types[i].mask; i++) अणु

		अगर ((data_mask & dev->event_types[i].data) !=
		    dev->event_types[i].data)
			जारी;

		अगर (!(mask & dev->event_types[i].mask))
			जारी;

		क्रम (j = 0; dev->event_types[i].events[j].event; j++) अणु
			अगर (ev == dev->event_types[i].events[j].data) अणु
				device_event =
					dev->event_types[i].events[j].event;
				/* some events may require ignoring */
				अगर (!device_event)
					वापस IRQ_HANDLED;
				जाओ found;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Still not able to decode the event try to pass
	 * it over to the minidriver
	 */
	अगर (dev->handle_irq && dev->handle_irq(data_mask, ev) == 0)
		वापस IRQ_HANDLED;

	dprपूर्णांकk("unknown event ([%.2x] [%.2x]) at port 0x%.4x(+0x%.2x)\n",
			ev, data_mask, dev->cur_ioport->io1.minimum,
			dev->evport_offset);
	वापस IRQ_HANDLED;

found:
	sony_laptop_report_input_event(device_event);
	sonypi_compat_report_event(device_event);
	वापस IRQ_HANDLED;
पूर्ण

/*****************
 *
 *  ACPI driver
 *
 *****************/
अटल पूर्णांक sony_pic_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा sony_pic_ioport *io, *पंचांगp_io;
	काष्ठा sony_pic_irq *irq, *पंचांगp_irq;

	अगर (sony_pic_disable(device)) अणु
		pr_err("Couldn't disable device\n");
		वापस -ENXIO;
	पूर्ण

	मुक्त_irq(spic_dev.cur_irq->irq.पूर्णांकerrupts[0], &spic_dev);
	release_region(spic_dev.cur_ioport->io1.minimum,
			spic_dev.cur_ioport->io1.address_length);
	अगर (spic_dev.cur_ioport->io2.minimum)
		release_region(spic_dev.cur_ioport->io2.minimum,
				spic_dev.cur_ioport->io2.address_length);

	sonypi_compat_निकास();

	sony_laptop_हटाओ_input();

	/* pf attrs */
	sysfs_हटाओ_group(&sony_pf_device->dev.kobj, &spic_attribute_group);
	sony_pf_हटाओ();

	list_क्रम_each_entry_safe(io, पंचांगp_io, &spic_dev.ioports, list) अणु
		list_del(&io->list);
		kमुक्त(io);
	पूर्ण
	list_क्रम_each_entry_safe(irq, पंचांगp_irq, &spic_dev.पूर्णांकerrupts, list) अणु
		list_del(&irq->list);
		kमुक्त(irq);
	पूर्ण
	spic_dev.cur_ioport = शून्य;
	spic_dev.cur_irq = शून्य;

	dprपूर्णांकk(SONY_PIC_DRIVER_NAME " removed.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक sony_pic_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक result;
	काष्ठा sony_pic_ioport *io, *पंचांगp_io;
	काष्ठा sony_pic_irq *irq, *पंचांगp_irq;

	spic_dev.acpi_dev = device;
	म_नकल(acpi_device_class(device), "sony/hotkey");
	sony_pic_detect_device_type(&spic_dev);
	mutex_init(&spic_dev.lock);

	/* पढ़ो _PRS resources */
	result = sony_pic_possible_resources(device);
	अगर (result) अणु
		pr_err("Unable to read possible resources\n");
		जाओ err_मुक्त_resources;
	पूर्ण

	/* setup input devices and helper fअगरo */
	result = sony_laptop_setup_input(device);
	अगर (result) अणु
		pr_err("Unable to create input devices\n");
		जाओ err_मुक्त_resources;
	पूर्ण

	result = sonypi_compat_init();
	अगर (result)
		जाओ err_हटाओ_input;

	/* request io port */
	list_क्रम_each_entry_reverse(io, &spic_dev.ioports, list) अणु
		अगर (request_region(io->io1.minimum, io->io1.address_length,
					"Sony Programmable I/O Device")) अणु
			dprपूर्णांकk("I/O port1: 0x%.4x (0x%.4x) + 0x%.2x\n",
					io->io1.minimum, io->io1.maximum,
					io->io1.address_length);
			/* Type 1 have 2 ioports */
			अगर (io->io2.minimum) अणु
				अगर (request_region(io->io2.minimum,
						io->io2.address_length,
						"Sony Programmable I/O Device")) अणु
					dprपूर्णांकk("I/O port2: 0x%.4x (0x%.4x) + 0x%.2x\n",
							io->io2.minimum, io->io2.maximum,
							io->io2.address_length);
					spic_dev.cur_ioport = io;
					अवरोध;
				पूर्ण
				अन्यथा अणु
					dprपूर्णांकk("Unable to get I/O port2: "
							"0x%.4x (0x%.4x) + 0x%.2x\n",
							io->io2.minimum, io->io2.maximum,
							io->io2.address_length);
					release_region(io->io1.minimum,
							io->io1.address_length);
				पूर्ण
			पूर्ण
			अन्यथा अणु
				spic_dev.cur_ioport = io;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!spic_dev.cur_ioport) अणु
		pr_err("Failed to request_region\n");
		result = -ENODEV;
		जाओ err_हटाओ_compat;
	पूर्ण

	/* request IRQ */
	list_क्रम_each_entry_reverse(irq, &spic_dev.पूर्णांकerrupts, list) अणु
		अगर (!request_irq(irq->irq.पूर्णांकerrupts[0], sony_pic_irq,
					0, "sony-laptop", &spic_dev)) अणु
			dprपूर्णांकk("IRQ: %d - triggering: %d - "
					"polarity: %d - shr: %d\n",
					irq->irq.पूर्णांकerrupts[0],
					irq->irq.triggering,
					irq->irq.polarity,
					irq->irq.shareable);
			spic_dev.cur_irq = irq;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!spic_dev.cur_irq) अणु
		pr_err("Failed to request_irq\n");
		result = -ENODEV;
		जाओ err_release_region;
	पूर्ण

	/* set resource status _SRS */
	result = sony_pic_enable(device, spic_dev.cur_ioport, spic_dev.cur_irq);
	अगर (result) अणु
		pr_err("Couldn't enable device\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	spic_dev.bluetooth_घातer = -1;
	/* create device attributes */
	result = sony_pf_add();
	अगर (result)
		जाओ err_disable_device;

	result = sysfs_create_group(&sony_pf_device->dev.kobj, &spic_attribute_group);
	अगर (result)
		जाओ err_हटाओ_pf;

	pr_info("SPIC setup done.\n");
	वापस 0;

err_हटाओ_pf:
	sony_pf_हटाओ();

err_disable_device:
	sony_pic_disable(device);

err_मुक्त_irq:
	मुक्त_irq(spic_dev.cur_irq->irq.पूर्णांकerrupts[0], &spic_dev);

err_release_region:
	release_region(spic_dev.cur_ioport->io1.minimum,
			spic_dev.cur_ioport->io1.address_length);
	अगर (spic_dev.cur_ioport->io2.minimum)
		release_region(spic_dev.cur_ioport->io2.minimum,
				spic_dev.cur_ioport->io2.address_length);

err_हटाओ_compat:
	sonypi_compat_निकास();

err_हटाओ_input:
	sony_laptop_हटाओ_input();

err_मुक्त_resources:
	list_क्रम_each_entry_safe(io, पंचांगp_io, &spic_dev.ioports, list) अणु
		list_del(&io->list);
		kमुक्त(io);
	पूर्ण
	list_क्रम_each_entry_safe(irq, पंचांगp_irq, &spic_dev.पूर्णांकerrupts, list) अणु
		list_del(&irq->list);
		kमुक्त(irq);
	पूर्ण
	spic_dev.cur_ioport = शून्य;
	spic_dev.cur_irq = शून्य;

	वापस result;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sony_pic_suspend(काष्ठा device *dev)
अणु
	अगर (sony_pic_disable(to_acpi_device(dev)))
		वापस -ENXIO;
	वापस 0;
पूर्ण

अटल पूर्णांक sony_pic_resume(काष्ठा device *dev)
अणु
	sony_pic_enable(to_acpi_device(dev),
			spic_dev.cur_ioport, spic_dev.cur_irq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sony_pic_pm, sony_pic_suspend, sony_pic_resume);

अटल स्थिर काष्ठा acpi_device_id sony_pic_device_ids[] = अणु
	अणुSONY_PIC_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver sony_pic_driver = अणु
	.name = SONY_PIC_DRIVER_NAME,
	.class = SONY_PIC_CLASS,
	.ids = sony_pic_device_ids,
	.owner = THIS_MODULE,
	.ops = अणु
		.add = sony_pic_add,
		.हटाओ = sony_pic_हटाओ,
		पूर्ण,
	.drv.pm = &sony_pic_pm,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id sonypi_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "Sony Vaio",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PCG-"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Sony Vaio",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "VGN-"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init sony_laptop_init(व्योम)
अणु
	पूर्णांक result;

	अगर (!no_spic && dmi_check_प्रणाली(sonypi_dmi_table)) अणु
		result = acpi_bus_रेजिस्टर_driver(&sony_pic_driver);
		अगर (result) अणु
			pr_err("Unable to register SPIC driver\n");
			जाओ out;
		पूर्ण
		spic_drv_रेजिस्टरed = 1;
	पूर्ण

	result = acpi_bus_रेजिस्टर_driver(&sony_nc_driver);
	अगर (result) अणु
		pr_err("Unable to register SNC driver\n");
		जाओ out_unरेजिस्टर_pic;
	पूर्ण

	वापस 0;

out_unरेजिस्टर_pic:
	अगर (spic_drv_रेजिस्टरed)
		acpi_bus_unरेजिस्टर_driver(&sony_pic_driver);
out:
	वापस result;
पूर्ण

अटल व्योम __निकास sony_laptop_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&sony_nc_driver);
	अगर (spic_drv_रेजिस्टरed)
		acpi_bus_unरेजिस्टर_driver(&sony_pic_driver);
पूर्ण

module_init(sony_laptop_init);
module_निकास(sony_laptop_निकास);
