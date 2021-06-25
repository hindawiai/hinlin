<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  asus-laptop.c - Asus Laptop Support
 *
 *  Copyright (C) 2002-2005 Julien Lerouge, 2003-2006 Karol Kozimor
 *  Copyright (C) 2006-2007 Corentin Chary
 *  Copyright (C) 2011 Wind River Systems
 *
 *  The development page क्रम this driver is located at
 *  http://sourceक्रमge.net/projects/acpi4asus/
 *
 *  Credits:
 *  Pontus Fuchs   - Helper functions, cleanup
 *  Johann Wiesner - Small compile fixes
 *  John Belmonte  - ACPI code क्रम Toshiba laptop was a good starting poपूर्णांक.
 *  Eric Burghard  - LED display support क्रम W1N
 *  Josh Green     - Light Sens support
 *  Thomas Tuttle  - His first patch क्रम led support was very helpful
 *  Sam Lin        - GPS support
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/backlight.h>
#समावेश <linux/fb.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/video.h>

#घोषणा ASUS_LAPTOP_VERSION	"0.42"

#घोषणा ASUS_LAPTOP_NAME	"Asus Laptop Support"
#घोषणा ASUS_LAPTOP_CLASS	"hotkey"
#घोषणा ASUS_LAPTOP_DEVICE_NAME	"Hotkey"
#घोषणा ASUS_LAPTOP_खाता	KBUILD_MODNAME
#घोषणा ASUS_LAPTOP_PREFIX	"\\_SB.ATKD."

MODULE_AUTHOR("Julien Lerouge, Karol Kozimor, Corentin Chary");
MODULE_DESCRIPTION(ASUS_LAPTOP_NAME);
MODULE_LICENSE("GPL");

/*
 * WAPF defines the behavior of the Fn+Fx wlan key
 * The signअगरicance of values is yet to be found, but
 * most of the समय:
 * Bit | Bluetooth | WLAN
 *  0  | Hardware  | Hardware
 *  1  | Hardware  | Software
 *  4  | Software  | Software
 */
अटल uपूर्णांक wapf = 1;
module_param(wapf, uपूर्णांक, 0444);
MODULE_PARM_DESC(wapf, "WAPF value");

अटल अक्षर *wled_type = "unknown";
अटल अक्षर *bled_type = "unknown";

module_param(wled_type, अक्षरp, 0444);
MODULE_PARM_DESC(wled_type, "Set the wled type on boot "
		 "(unknown, led or rfkill). "
		 "default is unknown");

module_param(bled_type, अक्षरp, 0444);
MODULE_PARM_DESC(bled_type, "Set the bled type on boot "
		 "(unknown, led or rfkill). "
		 "default is unknown");

अटल पूर्णांक wlan_status = 1;
अटल पूर्णांक bluetooth_status = 1;
अटल पूर्णांक wimax_status = -1;
अटल पूर्णांक wwan_status = -1;
अटल पूर्णांक als_status;

module_param(wlan_status, पूर्णांक, 0444);
MODULE_PARM_DESC(wlan_status, "Set the wireless status on boot "
		 "(0 = disabled, 1 = enabled, -1 = don't do anything). "
		 "default is -1");

module_param(bluetooth_status, पूर्णांक, 0444);
MODULE_PARM_DESC(bluetooth_status, "Set the wireless status on boot "
		 "(0 = disabled, 1 = enabled, -1 = don't do anything). "
		 "default is -1");

module_param(wimax_status, पूर्णांक, 0444);
MODULE_PARM_DESC(wimax_status, "Set the wireless status on boot "
		 "(0 = disabled, 1 = enabled, -1 = don't do anything). "
		 "default is -1");

module_param(wwan_status, पूर्णांक, 0444);
MODULE_PARM_DESC(wwan_status, "Set the wireless status on boot "
		 "(0 = disabled, 1 = enabled, -1 = don't do anything). "
		 "default is -1");

module_param(als_status, पूर्णांक, 0444);
MODULE_PARM_DESC(als_status, "Set the ALS status on boot "
		 "(0 = disabled, 1 = enabled). "
		 "default is 0");

/*
 * Some events we use, same क्रम all Asus
 */
#घोषणा ATKD_BRNUP_MIN		0x10
#घोषणा ATKD_BRNUP_MAX		0x1f
#घोषणा ATKD_BRNDOWN_MIN	0x20
#घोषणा ATKD_BRNDOWN_MAX	0x2f
#घोषणा ATKD_BRNDOWN		0x20
#घोषणा ATKD_BRNUP		0x2f
#घोषणा ATKD_LCD_ON	0x33
#घोषणा ATKD_LCD_OFF	0x34

/*
 * Known bits वापसed by \_SB.ATKD.HWRS
 */
#घोषणा WL_HWRS		0x80
#घोषणा BT_HWRS		0x100

/*
 * Flags क्रम hotk status
 * WL_ON and BT_ON are also used क्रम wireless_status()
 */
#घोषणा WL_RSTS		0x01	/* पूर्णांकernal Wअगरi */
#घोषणा BT_RSTS		0x02	/* पूर्णांकernal Bluetooth */
#घोषणा WM_RSTS		0x08    /* पूर्णांकernal wimax */
#घोषणा WW_RSTS		0x20    /* पूर्णांकernal wwan */

/* WLED and BLED type */
#घोषणा TYPE_UNKNOWN	0
#घोषणा TYPE_LED	1
#घोषणा TYPE_RFKILL	2

/* LED */
#घोषणा METHOD_MLED		"MLED"
#घोषणा METHOD_TLED		"TLED"
#घोषणा METHOD_RLED		"RLED"	/* W1JC */
#घोषणा METHOD_PLED		"PLED"	/* A7J */
#घोषणा METHOD_GLED		"GLED"	/* G1, G2 (probably) */

/* LEDD */
#घोषणा METHOD_LEDD		"SLCM"

/*
 * Bluetooth and WLAN
 * WLED and BLED are not handled like other XLED, because in some dsdt
 * they also control the WLAN/Bluetooth device.
 */
#घोषणा METHOD_WLAN		"WLED"
#घोषणा METHOD_BLUETOOTH	"BLED"

/* WWAN and WIMAX */
#घोषणा METHOD_WWAN		"GSMC"
#घोषणा METHOD_WIMAX		"WMXC"

#घोषणा METHOD_WL_STATUS	"RSTS"

/* Brightness */
#घोषणा METHOD_BRIGHTNESS_SET	"SPLV"
#घोषणा METHOD_BRIGHTNESS_GET	"GPLV"

/* Display */
#घोषणा METHOD_SWITCH_DISPLAY	"SDSP"

#घोषणा METHOD_ALS_CONTROL	"ALSC" /* Z71A Z71V */
#घोषणा METHOD_ALS_LEVEL	"ALSL" /* Z71A Z71V */

/* GPS */
/* R2H use dअगरferent handle क्रम GPS on/off */
#घोषणा METHOD_GPS_ON		"SDON"
#घोषणा METHOD_GPS_OFF		"SDOF"
#घोषणा METHOD_GPS_STATUS	"GPST"

/* Keyboard light */
#घोषणा METHOD_KBD_LIGHT_SET	"SLKB"
#घोषणा METHOD_KBD_LIGHT_GET	"GLKB"

/* For Pegatron Lucid tablet */
#घोषणा DEVICE_NAME_PEGA	"Lucid"

#घोषणा METHOD_PEGA_ENABLE	"ENPR"
#घोषणा METHOD_PEGA_DISABLE	"DAPR"
#घोषणा PEGA_WLAN	0x00
#घोषणा PEGA_BLUETOOTH	0x01
#घोषणा PEGA_WWAN	0x02
#घोषणा PEGA_ALS	0x04
#घोषणा PEGA_ALS_POWER	0x05

#घोषणा METHOD_PEGA_READ	"RDLN"
#घोषणा PEGA_READ_ALS_H	0x02
#घोषणा PEGA_READ_ALS_L	0x03

#घोषणा PEGA_ACCEL_NAME "pega_accel"
#घोषणा PEGA_ACCEL_DESC "Pegatron Lucid Tablet Accelerometer"
#घोषणा METHOD_XLRX "XLRX"
#घोषणा METHOD_XLRY "XLRY"
#घोषणा METHOD_XLRZ "XLRZ"
#घोषणा PEGA_ACC_CLAMP 512 /* 1G accel is reported as ~256, so clamp to 2G */
#घोषणा PEGA_ACC_RETRIES 3

/*
 * Define a specअगरic led काष्ठाure to keep the मुख्य काष्ठाure clean
 */
काष्ठा asus_led अणु
	पूर्णांक wk;
	काष्ठा work_काष्ठा work;
	काष्ठा led_classdev led;
	काष्ठा asus_laptop *asus;
	स्थिर अक्षर *method;
पूर्ण;

/*
 * Same thing क्रम rfसमाप्त
 */
काष्ठा asus_rfसमाप्त अणु
	/* type of control. Maps to PEGA_* values or *_RSTS  */
	पूर्णांक control_id;
	काष्ठा rfसमाप्त *rfसमाप्त;
	काष्ठा asus_laptop *asus;
पूर्ण;

/*
 * This is the मुख्य काष्ठाure, we can use it to store anything पूर्णांकeresting
 * about the hotk device
 */
काष्ठा asus_laptop अणु
	अक्षर *name;		/* laptop name */

	काष्ठा acpi_table_header *dsdt_info;
	काष्ठा platक्रमm_device *platक्रमm_device;
	काष्ठा acpi_device *device;		/* the device we are in */
	काष्ठा backlight_device *backlight_device;

	काष्ठा input_dev *inputdev;
	काष्ठा key_entry *keymap;
	काष्ठा input_dev *pega_accel_poll;

	काष्ठा asus_led wled;
	काष्ठा asus_led bled;
	काष्ठा asus_led mled;
	काष्ठा asus_led tled;
	काष्ठा asus_led rled;
	काष्ठा asus_led pled;
	काष्ठा asus_led gled;
	काष्ठा asus_led kled;
	काष्ठा workqueue_काष्ठा *led_workqueue;

	पूर्णांक wled_type;
	पूर्णांक bled_type;
	पूर्णांक wireless_status;
	bool have_rsts;
	bool is_pega_lucid;
	bool pega_acc_live;
	पूर्णांक pega_acc_x;
	पूर्णांक pega_acc_y;
	पूर्णांक pega_acc_z;

	काष्ठा asus_rfसमाप्त wlan;
	काष्ठा asus_rfसमाप्त bluetooth;
	काष्ठा asus_rfसमाप्त wwan;
	काष्ठा asus_rfसमाप्त wimax;
	काष्ठा asus_rfसमाप्त gps;

	acpi_handle handle;	/* the handle of the hotk device */
	u32 ledd_status;	/* status of the LED display */
	u8 light_level;		/* light sensor level */
	u8 light_चयन;	/* light sensor चयन value */
	u16 event_count[128];	/* count क्रम each event TODO make this better */
पूर्ण;

अटल स्थिर काष्ठा key_entry asus_keymap[] = अणु
	/* Lenovo SL Specअगरic keycodes */
	अणुKE_KEY, 0x02, अणु KEY_SCREENLOCK पूर्ण पूर्ण,
	अणुKE_KEY, 0x05, अणु KEY_WLAN पूर्ण पूर्ण,
	अणुKE_KEY, 0x08, अणु KEY_F13 पूर्ण पूर्ण,
	अणुKE_KEY, 0x09, अणु KEY_PROG2 पूर्ण पूर्ण, /* Dock */
	अणुKE_KEY, 0x17, अणु KEY_ZOOM पूर्ण पूर्ण,
	अणुKE_KEY, 0x1f, अणु KEY_BATTERY पूर्ण पूर्ण,
	/* End of Lenovo SL Specअगरic keycodes */
	अणुKE_KEY, ATKD_BRNDOWN, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणुKE_KEY, ATKD_BRNUP, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणुKE_KEY, 0x30, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणुKE_KEY, 0x31, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणुKE_KEY, 0x32, अणु KEY_MUTE पूर्ण पूर्ण,
	अणुKE_KEY, 0x33, अणु KEY_DISPLAYTOGGLE पूर्ण पूर्ण, /* LCD on */
	अणुKE_KEY, 0x34, अणु KEY_DISPLAY_OFF पूर्ण पूर्ण, /* LCD off */
	अणुKE_KEY, 0x40, अणु KEY_PREVIOUSSONG पूर्ण पूर्ण,
	अणुKE_KEY, 0x41, अणु KEY_NEXTSONG पूर्ण पूर्ण,
	अणुKE_KEY, 0x43, अणु KEY_STOPCD पूर्ण पूर्ण, /* Stop/Eject */
	अणुKE_KEY, 0x45, अणु KEY_PLAYPAUSE पूर्ण पूर्ण,
	अणुKE_KEY, 0x4c, अणु KEY_MEDIA पूर्ण पूर्ण, /* WMP Key */
	अणुKE_KEY, 0x50, अणु KEY_EMAIL पूर्ण पूर्ण,
	अणुKE_KEY, 0x51, अणु KEY_WWW पूर्ण पूर्ण,
	अणुKE_KEY, 0x55, अणु KEY_CALC पूर्ण पूर्ण,
	अणुKE_IGNORE, 0x57, पूर्ण,  /* Battery mode */
	अणुKE_IGNORE, 0x58, पूर्ण,  /* AC mode */
	अणुKE_KEY, 0x5C, अणु KEY_SCREENLOCK पूर्ण पूर्ण,  /* Screenlock */
	अणुKE_KEY, 0x5D, अणु KEY_WLAN पूर्ण पूर्ण, /* WLAN Toggle */
	अणुKE_KEY, 0x5E, अणु KEY_WLAN पूर्ण पूर्ण, /* WLAN Enable */
	अणुKE_KEY, 0x5F, अणु KEY_WLAN पूर्ण पूर्ण, /* WLAN Disable */
	अणुKE_KEY, 0x60, अणु KEY_TOUCHPAD_ON पूर्ण पूर्ण,
	अणुKE_KEY, 0x61, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD only */
	अणुKE_KEY, 0x62, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT only */
	अणुKE_KEY, 0x63, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT */
	अणुKE_KEY, 0x64, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP TV */
	अणुKE_KEY, 0x65, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + TV */
	अणुKE_KEY, 0x66, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + TV */
	अणुKE_KEY, 0x67, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + TV */
	अणुKE_KEY, 0x6A, अणु KEY_TOUCHPAD_TOGGLE पूर्ण पूर्ण, /* Lock Touchpad Fn + F9 */
	अणुKE_KEY, 0x6B, अणु KEY_TOUCHPAD_TOGGLE पूर्ण पूर्ण, /* Lock Touchpad */
	अणुKE_KEY, 0x6C, अणु KEY_SLEEP पूर्ण पूर्ण, /* Suspend */
	अणुKE_KEY, 0x6D, अणु KEY_SLEEP पूर्ण पूर्ण, /* Hibernate */
	अणुKE_IGNORE, 0x6E, पूर्ण,  /* Low Battery notअगरication */
	अणुKE_KEY, 0x7D, अणु KEY_BLUETOOTH पूर्ण पूर्ण, /* Bluetooth Enable */
	अणुKE_KEY, 0x7E, अणु KEY_BLUETOOTH पूर्ण पूर्ण, /* Bluetooth Disable */
	अणुKE_KEY, 0x82, अणु KEY_CAMERA पूर्ण पूर्ण,
	अणुKE_KEY, 0x88, अणु KEY_RFKILL  पूर्ण पूर्ण, /* Radio Toggle Key */
	अणुKE_KEY, 0x8A, अणु KEY_PROG1 पूर्ण पूर्ण, /* Color enhancement mode */
	अणुKE_KEY, 0x8C, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP DVI only */
	अणुKE_KEY, 0x8D, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + DVI */
	अणुKE_KEY, 0x8E, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + DVI */
	अणुKE_KEY, 0x8F, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP TV + DVI */
	अणुKE_KEY, 0x90, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + DVI */
	अणुKE_KEY, 0x91, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + TV + DVI */
	अणुKE_KEY, 0x92, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + TV + DVI */
	अणुKE_KEY, 0x93, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + TV + DVI */
	अणुKE_KEY, 0x95, अणु KEY_MEDIA पूर्ण पूर्ण,
	अणुKE_KEY, 0x99, अणु KEY_PHONE पूर्ण पूर्ण,
	अणुKE_KEY, 0xA0, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP HDMI only */
	अणुKE_KEY, 0xA1, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + HDMI */
	अणुKE_KEY, 0xA2, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + HDMI */
	अणुKE_KEY, 0xA3, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP TV + HDMI */
	अणुKE_KEY, 0xA4, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + HDMI */
	अणुKE_KEY, 0xA5, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + TV + HDMI */
	अणुKE_KEY, 0xA6, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + TV + HDMI */
	अणुKE_KEY, 0xA7, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + TV + HDMI */
	अणुKE_KEY, 0xB5, अणु KEY_CALC पूर्ण पूर्ण,
	अणुKE_KEY, 0xC4, अणु KEY_KBDILLUMUP पूर्ण पूर्ण,
	अणुKE_KEY, 0xC5, अणु KEY_KBDILLUMDOWN पूर्ण पूर्ण,
	अणुKE_END, 0पूर्ण,
पूर्ण;


/*
 * This function evaluates an ACPI method, given an पूर्णांक as parameter, the
 * method is searched within the scope of the handle, can be शून्य. The output
 * of the method is written is output, which can also be शून्य
 *
 * वापसs 0 अगर ग_लिखो is successful, -1 अन्यथा.
 */
अटल पूर्णांक ग_लिखो_acpi_पूर्णांक_ret(acpi_handle handle, स्थिर अक्षर *method, पूर्णांक val,
			      काष्ठा acpi_buffer *output)
अणु
	काष्ठा acpi_object_list params;	/* list of input parameters (an पूर्णांक) */
	जोड़ acpi_object in_obj;	/* the only param we use */
	acpi_status status;

	अगर (!handle)
		वापस -1;

	params.count = 1;
	params.poपूर्णांकer = &in_obj;
	in_obj.type = ACPI_TYPE_INTEGER;
	in_obj.पूर्णांकeger.value = val;

	status = acpi_evaluate_object(handle, (अक्षर *)method, &params, output);
	अगर (status == AE_OK)
		वापस 0;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक ग_लिखो_acpi_पूर्णांक(acpi_handle handle, स्थिर अक्षर *method, पूर्णांक val)
अणु
	वापस ग_लिखो_acpi_पूर्णांक_ret(handle, method, val, शून्य);
पूर्ण

अटल पूर्णांक acpi_check_handle(acpi_handle handle, स्थिर अक्षर *method,
			     acpi_handle *ret)
अणु
	acpi_status status;

	अगर (method == शून्य)
		वापस -ENODEV;

	अगर (ret)
		status = acpi_get_handle(handle, (अक्षर *)method,
					 ret);
	अन्यथा अणु
		acpi_handle dummy;

		status = acpi_get_handle(handle, (अक्षर *)method,
					 &dummy);
	पूर्ण

	अगर (status != AE_OK) अणु
		अगर (ret)
			pr_warn("Error finding %s\n", method);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool asus_check_pega_lucid(काष्ठा asus_laptop *asus)
अणु
	वापस !म_भेद(asus->name, DEVICE_NAME_PEGA) &&
	   !acpi_check_handle(asus->handle, METHOD_PEGA_ENABLE, शून्य) &&
	   !acpi_check_handle(asus->handle, METHOD_PEGA_DISABLE, शून्य) &&
	   !acpi_check_handle(asus->handle, METHOD_PEGA_READ, शून्य);
पूर्ण

अटल पूर्णांक asus_pega_lucid_set(काष्ठा asus_laptop *asus, पूर्णांक unit, bool enable)
अणु
	अक्षर *method = enable ? METHOD_PEGA_ENABLE : METHOD_PEGA_DISABLE;
	वापस ग_लिखो_acpi_पूर्णांक(asus->handle, method, unit);
पूर्ण

अटल पूर्णांक pega_acc_axis(काष्ठा asus_laptop *asus, पूर्णांक curr, अक्षर *method)
अणु
	पूर्णांक i, delta;
	अचिन्हित दीर्घ दीर्घ val;
	क्रम (i = 0; i < PEGA_ACC_RETRIES; i++) अणु
		acpi_evaluate_पूर्णांकeger(asus->handle, method, शून्य, &val);

		/* The output is noisy.  From पढ़ोing the ASL
		 * dissassembly, समयout errors are वापसed with 1's
		 * in the high word, and the lack of locking around
		 * thei hi/lo byte पढ़ोs means that a transition
		 * between (क्रम example) -1 and 0 could be पढ़ो as
		 * 0xff00 or 0x00ff. */
		delta = असल(curr - (लघु)val);
		अगर (delta < 128 && !(val & ~0xffff))
			अवरोध;
	पूर्ण
	वापस clamp_val((लघु)val, -PEGA_ACC_CLAMP, PEGA_ACC_CLAMP);
पूर्ण

अटल व्योम pega_accel_poll(काष्ठा input_dev *input)
अणु
	काष्ठा device *parent = input->dev.parent;
	काष्ठा asus_laptop *asus = dev_get_drvdata(parent);

	/* In some हालs, the very first call to poll causes a
	 * recursive fault under the polldev worker.  This is
	 * apparently related to very early userspace access to the
	 * device, and perhaps a firmware bug. Fake the first report. */
	अगर (!asus->pega_acc_live) अणु
		asus->pega_acc_live = true;
		input_report_असल(input, ABS_X, 0);
		input_report_असल(input, ABS_Y, 0);
		input_report_असल(input, ABS_Z, 0);
		input_sync(input);
		वापस;
	पूर्ण

	asus->pega_acc_x = pega_acc_axis(asus, asus->pega_acc_x, METHOD_XLRX);
	asus->pega_acc_y = pega_acc_axis(asus, asus->pega_acc_y, METHOD_XLRY);
	asus->pega_acc_z = pega_acc_axis(asus, asus->pega_acc_z, METHOD_XLRZ);

	/* Note transक्रमm, convert to "right/up/out" in the native
	 * landscape orientation (i.e. the vector is the direction of
	 * "real up" in the device's cartiesian coordinates). */
	input_report_असल(input, ABS_X, -asus->pega_acc_x);
	input_report_असल(input, ABS_Y, -asus->pega_acc_y);
	input_report_असल(input, ABS_Z,  asus->pega_acc_z);
	input_sync(input);
पूर्ण

अटल व्योम pega_accel_निकास(काष्ठा asus_laptop *asus)
अणु
	अगर (asus->pega_accel_poll) अणु
		input_unरेजिस्टर_device(asus->pega_accel_poll);
		asus->pega_accel_poll = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक pega_accel_init(काष्ठा asus_laptop *asus)
अणु
	पूर्णांक err;
	काष्ठा input_dev *input;

	अगर (!asus->is_pega_lucid)
		वापस -ENODEV;

	अगर (acpi_check_handle(asus->handle, METHOD_XLRX, शून्य) ||
	    acpi_check_handle(asus->handle, METHOD_XLRY, शून्य) ||
	    acpi_check_handle(asus->handle, METHOD_XLRZ, शून्य))
		वापस -ENODEV;

	input = input_allocate_device();
	अगर (!input)
		वापस -ENOMEM;

	input->name = PEGA_ACCEL_DESC;
	input->phys = PEGA_ACCEL_NAME "/input0";
	input->dev.parent = &asus->platक्रमm_device->dev;
	input->id.bustype = BUS_HOST;

	input_set_असल_params(input, ABS_X,
			     -PEGA_ACC_CLAMP, PEGA_ACC_CLAMP, 0, 0);
	input_set_असल_params(input, ABS_Y,
			     -PEGA_ACC_CLAMP, PEGA_ACC_CLAMP, 0, 0);
	input_set_असल_params(input, ABS_Z,
			     -PEGA_ACC_CLAMP, PEGA_ACC_CLAMP, 0, 0);

	err = input_setup_polling(input, pega_accel_poll);
	अगर (err)
		जाओ निकास;

	input_set_poll_पूर्णांकerval(input, 125);
	input_set_min_poll_पूर्णांकerval(input, 50);
	input_set_max_poll_पूर्णांकerval(input, 2000);

	err = input_रेजिस्टर_device(input);
	अगर (err)
		जाओ निकास;

	asus->pega_accel_poll = input;
	वापस 0;

निकास:
	input_मुक्त_device(input);
	वापस err;
पूर्ण

/* Generic LED function */
अटल पूर्णांक asus_led_set(काष्ठा asus_laptop *asus, स्थिर अक्षर *method,
			 पूर्णांक value)
अणु
	अगर (!म_भेद(method, METHOD_MLED))
		value = !value;
	अन्यथा अगर (!म_भेद(method, METHOD_GLED))
		value = !value + 1;
	अन्यथा
		value = !!value;

	वापस ग_लिखो_acpi_पूर्णांक(asus->handle, method, value);
पूर्ण

/*
 * LEDs
 */
/* /sys/class/led handlers */
अटल व्योम asus_led_cdev_set(काष्ठा led_classdev *led_cdev,
			 क्रमागत led_brightness value)
अणु
	काष्ठा asus_led *led = container_of(led_cdev, काष्ठा asus_led, led);
	काष्ठा asus_laptop *asus = led->asus;

	led->wk = !!value;
	queue_work(asus->led_workqueue, &led->work);
पूर्ण

अटल व्योम asus_led_cdev_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asus_led *led = container_of(work, काष्ठा asus_led, work);
	काष्ठा asus_laptop *asus = led->asus;

	asus_led_set(asus, led->method, led->wk);
पूर्ण

अटल क्रमागत led_brightness asus_led_cdev_get(काष्ठा led_classdev *led_cdev)
अणु
	वापस led_cdev->brightness;
पूर्ण

/*
 * Keyboard backlight (also a LED)
 */
अटल पूर्णांक asus_kled_lvl(काष्ठा asus_laptop *asus)
अणु
	अचिन्हित दीर्घ दीर्घ kblv;
	काष्ठा acpi_object_list params;
	जोड़ acpi_object in_obj;
	acpi_status rv;

	params.count = 1;
	params.poपूर्णांकer = &in_obj;
	in_obj.type = ACPI_TYPE_INTEGER;
	in_obj.पूर्णांकeger.value = 2;

	rv = acpi_evaluate_पूर्णांकeger(asus->handle, METHOD_KBD_LIGHT_GET,
				   &params, &kblv);
	अगर (ACPI_FAILURE(rv)) अणु
		pr_warn("Error reading kled level\n");
		वापस -ENODEV;
	पूर्ण
	वापस kblv;
पूर्ण

अटल पूर्णांक asus_kled_set(काष्ठा asus_laptop *asus, पूर्णांक kblv)
अणु
	अगर (kblv > 0)
		kblv = (1 << 7) | (kblv & 0x7F);
	अन्यथा
		kblv = 0;

	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_KBD_LIGHT_SET, kblv)) अणु
		pr_warn("Keyboard LED display write failed\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम asus_kled_cdev_set(काष्ठा led_classdev *led_cdev,
			      क्रमागत led_brightness value)
अणु
	काष्ठा asus_led *led = container_of(led_cdev, काष्ठा asus_led, led);
	काष्ठा asus_laptop *asus = led->asus;

	led->wk = value;
	queue_work(asus->led_workqueue, &led->work);
पूर्ण

अटल व्योम asus_kled_cdev_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asus_led *led = container_of(work, काष्ठा asus_led, work);
	काष्ठा asus_laptop *asus = led->asus;

	asus_kled_set(asus, led->wk);
पूर्ण

अटल क्रमागत led_brightness asus_kled_cdev_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा asus_led *led = container_of(led_cdev, काष्ठा asus_led, led);
	काष्ठा asus_laptop *asus = led->asus;

	वापस asus_kled_lvl(asus);
पूर्ण

अटल व्योम asus_led_निकास(काष्ठा asus_laptop *asus)
अणु
	led_classdev_unरेजिस्टर(&asus->wled.led);
	led_classdev_unरेजिस्टर(&asus->bled.led);
	led_classdev_unरेजिस्टर(&asus->mled.led);
	led_classdev_unरेजिस्टर(&asus->tled.led);
	led_classdev_unरेजिस्टर(&asus->pled.led);
	led_classdev_unरेजिस्टर(&asus->rled.led);
	led_classdev_unरेजिस्टर(&asus->gled.led);
	led_classdev_unरेजिस्टर(&asus->kled.led);

	अगर (asus->led_workqueue) अणु
		destroy_workqueue(asus->led_workqueue);
		asus->led_workqueue = शून्य;
	पूर्ण
पूर्ण

/*  Ugly macro, need to fix that later */
अटल पूर्णांक asus_led_रेजिस्टर(काष्ठा asus_laptop *asus,
			     काष्ठा asus_led *led,
			     स्थिर अक्षर *name, स्थिर अक्षर *method)
अणु
	काष्ठा led_classdev *led_cdev = &led->led;

	अगर (!method || acpi_check_handle(asus->handle, method, शून्य))
		वापस 0; /* Led not present */

	led->asus = asus;
	led->method = method;

	INIT_WORK(&led->work, asus_led_cdev_update);
	led_cdev->name = name;
	led_cdev->brightness_set = asus_led_cdev_set;
	led_cdev->brightness_get = asus_led_cdev_get;
	led_cdev->max_brightness = 1;
	वापस led_classdev_रेजिस्टर(&asus->platक्रमm_device->dev, led_cdev);
पूर्ण

अटल पूर्णांक asus_led_init(काष्ठा asus_laptop *asus)
अणु
	पूर्णांक r = 0;

	/*
	 * The Pegatron Lucid has no physical leds, but all methods are
	 * available in the DSDT...
	 */
	अगर (asus->is_pega_lucid)
		वापस 0;

	/*
	 * Functions that actually update the LED's are called from a
	 * workqueue. By करोing this as separate work rather than when the LED
	 * subप्रणाली asks, we aव्योम messing with the Asus ACPI stuff during a
	 * potentially bad समय, such as a समयr पूर्णांकerrupt.
	 */
	asus->led_workqueue = create_singlethपढ़ो_workqueue("led_workqueue");
	अगर (!asus->led_workqueue)
		वापस -ENOMEM;

	अगर (asus->wled_type == TYPE_LED)
		r = asus_led_रेजिस्टर(asus, &asus->wled, "asus::wlan",
				      METHOD_WLAN);
	अगर (r)
		जाओ error;
	अगर (asus->bled_type == TYPE_LED)
		r = asus_led_रेजिस्टर(asus, &asus->bled, "asus::bluetooth",
				      METHOD_BLUETOOTH);
	अगर (r)
		जाओ error;
	r = asus_led_रेजिस्टर(asus, &asus->mled, "asus::mail", METHOD_MLED);
	अगर (r)
		जाओ error;
	r = asus_led_रेजिस्टर(asus, &asus->tled, "asus::touchpad", METHOD_TLED);
	अगर (r)
		जाओ error;
	r = asus_led_रेजिस्टर(asus, &asus->rled, "asus::record", METHOD_RLED);
	अगर (r)
		जाओ error;
	r = asus_led_रेजिस्टर(asus, &asus->pled, "asus::phone", METHOD_PLED);
	अगर (r)
		जाओ error;
	r = asus_led_रेजिस्टर(asus, &asus->gled, "asus::gaming", METHOD_GLED);
	अगर (r)
		जाओ error;
	अगर (!acpi_check_handle(asus->handle, METHOD_KBD_LIGHT_SET, शून्य) &&
	    !acpi_check_handle(asus->handle, METHOD_KBD_LIGHT_GET, शून्य)) अणु
		काष्ठा asus_led *led = &asus->kled;
		काष्ठा led_classdev *cdev = &led->led;

		led->asus = asus;

		INIT_WORK(&led->work, asus_kled_cdev_update);
		cdev->name = "asus::kbd_backlight";
		cdev->brightness_set = asus_kled_cdev_set;
		cdev->brightness_get = asus_kled_cdev_get;
		cdev->max_brightness = 3;
		r = led_classdev_रेजिस्टर(&asus->platक्रमm_device->dev, cdev);
	पूर्ण
error:
	अगर (r)
		asus_led_निकास(asus);
	वापस r;
पूर्ण

/*
 * Backlight device
 */
अटल पूर्णांक asus_पढ़ो_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा asus_laptop *asus = bl_get_data(bd);
	अचिन्हित दीर्घ दीर्घ value;
	acpi_status rv;

	rv = acpi_evaluate_पूर्णांकeger(asus->handle, METHOD_BRIGHTNESS_GET,
				   शून्य, &value);
	अगर (ACPI_FAILURE(rv)) अणु
		pr_warn("Error reading brightness\n");
		वापस 0;
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक asus_set_brightness(काष्ठा backlight_device *bd, पूर्णांक value)
अणु
	काष्ठा asus_laptop *asus = bl_get_data(bd);

	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_BRIGHTNESS_SET, value)) अणु
		pr_warn("Error changing brightness\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक update_bl_status(काष्ठा backlight_device *bd)
अणु
	पूर्णांक value = bd->props.brightness;

	वापस asus_set_brightness(bd, value);
पूर्ण

अटल स्थिर काष्ठा backlight_ops asusbl_ops = अणु
	.get_brightness = asus_पढ़ो_brightness,
	.update_status = update_bl_status,
पूर्ण;

अटल पूर्णांक asus_backlight_notअगरy(काष्ठा asus_laptop *asus)
अणु
	काष्ठा backlight_device *bd = asus->backlight_device;
	पूर्णांक old = bd->props.brightness;

	backlight_क्रमce_update(bd, BACKLIGHT_UPDATE_HOTKEY);

	वापस old;
पूर्ण

अटल पूर्णांक asus_backlight_init(काष्ठा asus_laptop *asus)
अणु
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;

	अगर (acpi_check_handle(asus->handle, METHOD_BRIGHTNESS_GET, शून्य) ||
	    acpi_check_handle(asus->handle, METHOD_BRIGHTNESS_SET, शून्य))
		वापस 0;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.max_brightness = 15;
	props.type = BACKLIGHT_PLATFORM;

	bd = backlight_device_रेजिस्टर(ASUS_LAPTOP_खाता,
				       &asus->platक्रमm_device->dev, asus,
				       &asusbl_ops, &props);
	अगर (IS_ERR(bd)) अणु
		pr_err("Could not register asus backlight device\n");
		asus->backlight_device = शून्य;
		वापस PTR_ERR(bd);
	पूर्ण

	asus->backlight_device = bd;
	bd->props.brightness = asus_पढ़ो_brightness(bd);
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);
	वापस 0;
पूर्ण

अटल व्योम asus_backlight_निकास(काष्ठा asus_laptop *asus)
अणु
	backlight_device_unरेजिस्टर(asus->backlight_device);
	asus->backlight_device = शून्य;
पूर्ण

/*
 * Platक्रमm device handlers
 */

/*
 * We ग_लिखो our info in page, we begin at offset off and cannot ग_लिखो more
 * than count bytes. We set eof to 1 अगर we handle those 2 values. We वापस the
 * number of bytes written in page
 */
अटल sमाप_प्रकार infos_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *page)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);
	पूर्णांक len = 0;
	अचिन्हित दीर्घ दीर्घ temp;
	अक्षर buf[16];		/* enough क्रम all info */
	acpi_status rv;

	/*
	 * We use the easy way, we करोn't care of off and count,
	 * so we करोn't set eof to 1
	 */

	len += प्र_लिखो(page, ASUS_LAPTOP_NAME " " ASUS_LAPTOP_VERSION "\n");
	len += प्र_लिखो(page + len, "Model reference    : %s\n", asus->name);
	/*
	 * The SFUN method probably allows the original driver to get the list
	 * of features supported by a given model. For now, 0x0100 or 0x0800
	 * bit signअगरies that the laptop is equipped with a Wi-Fi MiniPCI card.
	 * The signअगरicance of others is yet to be found.
	 */
	rv = acpi_evaluate_पूर्णांकeger(asus->handle, "SFUN", शून्य, &temp);
	अगर (ACPI_SUCCESS(rv))
		len += प्र_लिखो(page + len, "SFUN value         : %#x\n",
			       (uपूर्णांक) temp);
	/*
	 * The HWRS method वापस inक्रमmations about the hardware.
	 * 0x80 bit is क्रम WLAN, 0x100 क्रम Bluetooth.
	 * 0x40 क्रम WWAN, 0x10 क्रम WIMAX.
	 * The signअगरicance of others is yet to be found.
	 * We करोn't currently use this क्रम device detection, and it
	 * takes several seconds to run on some प्रणालीs.
	 */
	rv = acpi_evaluate_पूर्णांकeger(asus->handle, "HWRS", शून्य, &temp);
	अगर (ACPI_SUCCESS(rv))
		len += प्र_लिखो(page + len, "HWRS value         : %#x\n",
			       (uपूर्णांक) temp);
	/*
	 * Another value क्रम userspace: the ASYM method वापसs 0x02 क्रम
	 * battery low and 0x04 क्रम battery critical, its पढ़ोings tend to be
	 * more accurate than those provided by _BST.
	 * Note: since not all the laptops provide this method, errors are
	 * silently ignored.
	 */
	rv = acpi_evaluate_पूर्णांकeger(asus->handle, "ASYM", शून्य, &temp);
	अगर (ACPI_SUCCESS(rv))
		len += प्र_लिखो(page + len, "ASYM value         : %#x\n",
			       (uपूर्णांक) temp);
	अगर (asus->dsdt_info) अणु
		snम_लिखो(buf, 16, "%d", asus->dsdt_info->length);
		len += प्र_लिखो(page + len, "DSDT length        : %s\n", buf);
		snम_लिखो(buf, 16, "%d", asus->dsdt_info->checksum);
		len += प्र_लिखो(page + len, "DSDT checksum      : %s\n", buf);
		snम_लिखो(buf, 16, "%d", asus->dsdt_info->revision);
		len += प्र_लिखो(page + len, "DSDT revision      : %s\n", buf);
		snम_लिखो(buf, 7, "%s", asus->dsdt_info->oem_id);
		len += प्र_लिखो(page + len, "OEM id             : %s\n", buf);
		snम_लिखो(buf, 9, "%s", asus->dsdt_info->oem_table_id);
		len += प्र_लिखो(page + len, "OEM table id       : %s\n", buf);
		snम_लिखो(buf, 16, "%x", asus->dsdt_info->oem_revision);
		len += प्र_लिखो(page + len, "OEM revision       : 0x%s\n", buf);
		snम_लिखो(buf, 5, "%s", asus->dsdt_info->asl_compiler_id);
		len += प्र_लिखो(page + len, "ASL comp vendor id : %s\n", buf);
		snम_लिखो(buf, 16, "%x", asus->dsdt_info->asl_compiler_revision);
		len += प्र_लिखो(page + len, "ASL comp revision  : 0x%s\n", buf);
	पूर्ण

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(infos);

अटल sमाप_प्रकार sysfs_acpi_set(काष्ठा asus_laptop *asus,
			      स्थिर अक्षर *buf, माप_प्रकार count,
			      स्थिर अक्षर *method)
अणु
	पूर्णांक rv, value;

	rv = kstrtoपूर्णांक(buf, 0, &value);
	अगर (rv < 0)
		वापस rv;

	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, method, value))
		वापस -ENODEV;
	वापस count;
पूर्ण

/*
 * LEDD display
 */
अटल sमाप_प्रकार ledd_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "0x%08x\n", asus->ledd_status);
पूर्ण

अटल sमाप_प्रकार ledd_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);
	पूर्णांक rv, value;

	rv = kstrtoपूर्णांक(buf, 0, &value);
	अगर (rv < 0)
		वापस rv;

	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_LEDD, value)) अणु
		pr_warn("LED display write failed\n");
		वापस -ENODEV;
	पूर्ण

	asus->ledd_status = (u32) value;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(ledd);

/*
 * Wireless
 */
अटल पूर्णांक asus_wireless_status(काष्ठा asus_laptop *asus, पूर्णांक mask)
अणु
	अचिन्हित दीर्घ दीर्घ status;
	acpi_status rv = AE_OK;

	अगर (!asus->have_rsts)
		वापस (asus->wireless_status & mask) ? 1 : 0;

	rv = acpi_evaluate_पूर्णांकeger(asus->handle, METHOD_WL_STATUS,
				   शून्य, &status);
	अगर (ACPI_FAILURE(rv)) अणु
		pr_warn("Error reading Wireless status\n");
		वापस -EINVAL;
	पूर्ण
	वापस !!(status & mask);
पूर्ण

/*
 * WLAN
 */
अटल पूर्णांक asus_wlan_set(काष्ठा asus_laptop *asus, पूर्णांक status)
अणु
	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_WLAN, !!status)) अणु
		pr_warn("Error setting wlan status to %d\n", status);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार wlan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", asus_wireless_status(asus, WL_RSTS));
पूर्ण

अटल sमाप_प्रकार wlan_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस sysfs_acpi_set(asus, buf, count, METHOD_WLAN);
पूर्ण
अटल DEVICE_ATTR_RW(wlan);

/*e
 * Bluetooth
 */
अटल पूर्णांक asus_bluetooth_set(काष्ठा asus_laptop *asus, पूर्णांक status)
अणु
	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_BLUETOOTH, !!status)) अणु
		pr_warn("Error setting bluetooth status to %d\n", status);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार bluetooth_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", asus_wireless_status(asus, BT_RSTS));
पूर्ण

अटल sमाप_प्रकार bluetooth_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस sysfs_acpi_set(asus, buf, count, METHOD_BLUETOOTH);
पूर्ण
अटल DEVICE_ATTR_RW(bluetooth);

/*
 * Wimax
 */
अटल पूर्णांक asus_wimax_set(काष्ठा asus_laptop *asus, पूर्णांक status)
अणु
	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_WIMAX, !!status)) अणु
		pr_warn("Error setting wimax status to %d\n", status);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार wimax_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", asus_wireless_status(asus, WM_RSTS));
पूर्ण

अटल sमाप_प्रकार wimax_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस sysfs_acpi_set(asus, buf, count, METHOD_WIMAX);
पूर्ण
अटल DEVICE_ATTR_RW(wimax);

/*
 * Wwan
 */
अटल पूर्णांक asus_wwan_set(काष्ठा asus_laptop *asus, पूर्णांक status)
अणु
	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_WWAN, !!status)) अणु
		pr_warn("Error setting wwan status to %d\n", status);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार wwan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", asus_wireless_status(asus, WW_RSTS));
पूर्ण

अटल sमाप_प्रकार wwan_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस sysfs_acpi_set(asus, buf, count, METHOD_WWAN);
पूर्ण
अटल DEVICE_ATTR_RW(wwan);

/*
 * Display
 */
अटल व्योम asus_set_display(काष्ठा asus_laptop *asus, पूर्णांक value)
अणु
	/* no sanity check needed क्रम now */
	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_SWITCH_DISPLAY, value))
		pr_warn("Error setting display\n");
	वापस;
पूर्ण

/*
 * Experimental support क्रम display चयनing. As of now: 1 should activate
 * the LCD output, 2 should करो क्रम CRT, 4 क्रम TV-Out and 8 क्रम DVI.
 * Any combination (bitwise) of these will suffice. I never actually tested 4
 * displays hooked up simultaneously, so be warned. See the acpi4asus README
 * क्रम more info.
 */
अटल sमाप_प्रकार display_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);
	पूर्णांक rv, value;

	rv = kstrtoपूर्णांक(buf, 0, &value);
	अगर (rv < 0)
		वापस rv;

	asus_set_display(asus, value);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(display);

/*
 * Light Sens
 */
अटल व्योम asus_als_चयन(काष्ठा asus_laptop *asus, पूर्णांक value)
अणु
	पूर्णांक ret;

	अगर (asus->is_pega_lucid) अणु
		ret = asus_pega_lucid_set(asus, PEGA_ALS, value);
		अगर (!ret)
			ret = asus_pega_lucid_set(asus, PEGA_ALS_POWER, value);
	पूर्ण अन्यथा अणु
		ret = ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_ALS_CONTROL, value);
	पूर्ण
	अगर (ret)
		pr_warn("Error setting light sensor switch\n");

	asus->light_चयन = value;
पूर्ण

अटल sमाप_प्रकार ls_चयन_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", asus->light_चयन);
पूर्ण

अटल sमाप_प्रकार ls_चयन_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);
	पूर्णांक rv, value;

	rv = kstrtoपूर्णांक(buf, 0, &value);
	अगर (rv < 0)
		वापस rv;

	asus_als_चयन(asus, value ? 1 : 0);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(ls_चयन);

अटल व्योम asus_als_level(काष्ठा asus_laptop *asus, पूर्णांक value)
अणु
	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, METHOD_ALS_LEVEL, value))
		pr_warn("Error setting light sensor level\n");
	asus->light_level = value;
पूर्ण

अटल sमाप_प्रकार ls_level_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", asus->light_level);
पूर्ण

अटल sमाप_प्रकार ls_level_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);
	पूर्णांक rv, value;

	rv = kstrtoपूर्णांक(buf, 0, &value);
	अगर (rv < 0)
		वापस rv;

	value = (0 < value) ? ((15 < value) ? 15 : value) : 0;
	/* 0 <= value <= 15 */
	asus_als_level(asus, value);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(ls_level);

अटल पूर्णांक pega_पूर्णांक_पढ़ो(काष्ठा asus_laptop *asus, पूर्णांक arg, पूर्णांक *result)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	पूर्णांक err = ग_लिखो_acpi_पूर्णांक_ret(asus->handle, METHOD_PEGA_READ, arg,
				     &buffer);
	अगर (!err) अणु
		जोड़ acpi_object *obj = buffer.poपूर्णांकer;
		अगर (obj && obj->type == ACPI_TYPE_INTEGER)
			*result = obj->पूर्णांकeger.value;
		अन्यथा
			err = -EIO;
	पूर्ण
	वापस err;
पूर्ण

अटल sमाप_प्रकार ls_value_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);
	पूर्णांक err, hi, lo;

	err = pega_पूर्णांक_पढ़ो(asus, PEGA_READ_ALS_H, &hi);
	अगर (!err)
		err = pega_पूर्णांक_पढ़ो(asus, PEGA_READ_ALS_L, &lo);
	अगर (!err)
		वापस प्र_लिखो(buf, "%d\n", 10 * hi + lo);
	वापस err;
पूर्ण
अटल DEVICE_ATTR_RO(ls_value);

/*
 * GPS
 */
अटल पूर्णांक asus_gps_status(काष्ठा asus_laptop *asus)
अणु
	अचिन्हित दीर्घ दीर्घ status;
	acpi_status rv;

	rv = acpi_evaluate_पूर्णांकeger(asus->handle, METHOD_GPS_STATUS,
				   शून्य, &status);
	अगर (ACPI_FAILURE(rv)) अणु
		pr_warn("Error reading GPS status\n");
		वापस -ENODEV;
	पूर्ण
	वापस !!status;
पूर्ण

अटल पूर्णांक asus_gps_चयन(काष्ठा asus_laptop *asus, पूर्णांक status)
अणु
	स्थिर अक्षर *meth = status ? METHOD_GPS_ON : METHOD_GPS_OFF;

	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, meth, 0x02))
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार gps_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", asus_gps_status(asus));
पूर्ण

अटल sमाप_प्रकार gps_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);
	पूर्णांक rv, value;
	पूर्णांक ret;

	rv = kstrtoपूर्णांक(buf, 0, &value);
	अगर (rv < 0)
		वापस rv;
	ret = asus_gps_चयन(asus, !!value);
	अगर (ret)
		वापस ret;
	rfसमाप्त_set_sw_state(asus->gps.rfसमाप्त, !value);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(gps);

/*
 * rfसमाप्त
 */
अटल पूर्णांक asus_gps_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	काष्ठा asus_laptop *asus = data;

	वापस asus_gps_चयन(asus, !blocked);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops asus_gps_rfसमाप्त_ops = अणु
	.set_block = asus_gps_rfसमाप्त_set,
पूर्ण;

अटल पूर्णांक asus_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	काष्ठा asus_rfसमाप्त *rfk = data;
	काष्ठा asus_laptop *asus = rfk->asus;

	अगर (rfk->control_id == WL_RSTS)
		वापस asus_wlan_set(asus, !blocked);
	अन्यथा अगर (rfk->control_id == BT_RSTS)
		वापस asus_bluetooth_set(asus, !blocked);
	अन्यथा अगर (rfk->control_id == WM_RSTS)
		वापस asus_wimax_set(asus, !blocked);
	अन्यथा अगर (rfk->control_id == WW_RSTS)
		वापस asus_wwan_set(asus, !blocked);

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops asus_rfसमाप्त_ops = अणु
	.set_block = asus_rfसमाप्त_set,
पूर्ण;

अटल व्योम asus_rfसमाप्त_terminate(काष्ठा asus_rfसमाप्त *rfk)
अणु
	अगर (!rfk->rfसमाप्त)
		वापस ;

	rfसमाप्त_unरेजिस्टर(rfk->rfसमाप्त);
	rfसमाप्त_destroy(rfk->rfसमाप्त);
	rfk->rfसमाप्त = शून्य;
पूर्ण

अटल व्योम asus_rfसमाप्त_निकास(काष्ठा asus_laptop *asus)
अणु
	asus_rfसमाप्त_terminate(&asus->wwan);
	asus_rfसमाप्त_terminate(&asus->bluetooth);
	asus_rfसमाप्त_terminate(&asus->wlan);
	asus_rfसमाप्त_terminate(&asus->gps);
पूर्ण

अटल पूर्णांक asus_rfसमाप्त_setup(काष्ठा asus_laptop *asus, काष्ठा asus_rfसमाप्त *rfk,
			     स्थिर अक्षर *name, पूर्णांक control_id, पूर्णांक type,
			     स्थिर काष्ठा rfसमाप्त_ops *ops)
अणु
	पूर्णांक result;

	rfk->control_id = control_id;
	rfk->asus = asus;
	rfk->rfसमाप्त = rfसमाप्त_alloc(name, &asus->platक्रमm_device->dev,
				   type, ops, rfk);
	अगर (!rfk->rfसमाप्त)
		वापस -EINVAL;

	result = rfसमाप्त_रेजिस्टर(rfk->rfसमाप्त);
	अगर (result) अणु
		rfसमाप्त_destroy(rfk->rfसमाप्त);
		rfk->rfसमाप्त = शून्य;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक asus_rfसमाप्त_init(काष्ठा asus_laptop *asus)
अणु
	पूर्णांक result = 0;

	अगर (asus->is_pega_lucid)
		वापस -ENODEV;

	अगर (!acpi_check_handle(asus->handle, METHOD_GPS_ON, शून्य) &&
	    !acpi_check_handle(asus->handle, METHOD_GPS_OFF, शून्य) &&
	    !acpi_check_handle(asus->handle, METHOD_GPS_STATUS, शून्य))
		result = asus_rfसमाप्त_setup(asus, &asus->gps, "asus-gps",
					   -1, RFKILL_TYPE_GPS,
					   &asus_gps_rfसमाप्त_ops);
	अगर (result)
		जाओ निकास;


	अगर (!acpi_check_handle(asus->handle, METHOD_WLAN, शून्य) &&
	    asus->wled_type == TYPE_RFKILL)
		result = asus_rfसमाप्त_setup(asus, &asus->wlan, "asus-wlan",
					   WL_RSTS, RFKILL_TYPE_WLAN,
					   &asus_rfसमाप्त_ops);
	अगर (result)
		जाओ निकास;

	अगर (!acpi_check_handle(asus->handle, METHOD_BLUETOOTH, शून्य) &&
	    asus->bled_type == TYPE_RFKILL)
		result = asus_rfसमाप्त_setup(asus, &asus->bluetooth,
					   "asus-bluetooth", BT_RSTS,
					   RFKILL_TYPE_BLUETOOTH,
					   &asus_rfसमाप्त_ops);
	अगर (result)
		जाओ निकास;

	अगर (!acpi_check_handle(asus->handle, METHOD_WWAN, शून्य))
		result = asus_rfसमाप्त_setup(asus, &asus->wwan, "asus-wwan",
					   WW_RSTS, RFKILL_TYPE_WWAN,
					   &asus_rfसमाप्त_ops);
	अगर (result)
		जाओ निकास;

	अगर (!acpi_check_handle(asus->handle, METHOD_WIMAX, शून्य))
		result = asus_rfसमाप्त_setup(asus, &asus->wimax, "asus-wimax",
					   WM_RSTS, RFKILL_TYPE_WIMAX,
					   &asus_rfसमाप्त_ops);
	अगर (result)
		जाओ निकास;

निकास:
	अगर (result)
		asus_rfसमाप्त_निकास(asus);

	वापस result;
पूर्ण

अटल पूर्णांक pega_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	काष्ठा asus_rfसमाप्त *rfk = data;

	पूर्णांक ret = asus_pega_lucid_set(rfk->asus, rfk->control_id, !blocked);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops pega_rfसमाप्त_ops = अणु
	.set_block = pega_rfसमाप्त_set,
पूर्ण;

अटल पूर्णांक pega_rfसमाप्त_setup(काष्ठा asus_laptop *asus, काष्ठा asus_rfसमाप्त *rfk,
			     स्थिर अक्षर *name, पूर्णांक controlid, पूर्णांक rfसमाप्त_type)
अणु
	वापस asus_rfसमाप्त_setup(asus, rfk, name, controlid, rfसमाप्त_type,
				 &pega_rfसमाप्त_ops);
पूर्ण

अटल पूर्णांक pega_rfसमाप्त_init(काष्ठा asus_laptop *asus)
अणु
	पूर्णांक ret = 0;

	अगर(!asus->is_pega_lucid)
		वापस -ENODEV;

	ret = pega_rfसमाप्त_setup(asus, &asus->wlan, "pega-wlan",
				PEGA_WLAN, RFKILL_TYPE_WLAN);
	अगर(ret)
		जाओ निकास;

	ret = pega_rfसमाप्त_setup(asus, &asus->bluetooth, "pega-bt",
				PEGA_BLUETOOTH, RFKILL_TYPE_BLUETOOTH);
	अगर(ret)
		जाओ निकास;

	ret = pega_rfसमाप्त_setup(asus, &asus->wwan, "pega-wwan",
				PEGA_WWAN, RFKILL_TYPE_WWAN);

निकास:
	अगर (ret)
		asus_rfसमाप्त_निकास(asus);

	वापस ret;
पूर्ण

/*
 * Input device (i.e. hotkeys)
 */
अटल व्योम asus_input_notअगरy(काष्ठा asus_laptop *asus, पूर्णांक event)
अणु
	अगर (!asus->inputdev)
		वापस ;
	अगर (!sparse_keymap_report_event(asus->inputdev, event, 1, true))
		pr_info("Unknown key %x pressed\n", event);
पूर्ण

अटल पूर्णांक asus_input_init(काष्ठा asus_laptop *asus)
अणु
	काष्ठा input_dev *input;
	पूर्णांक error;

	input = input_allocate_device();
	अगर (!input)
		वापस -ENOMEM;

	input->name = "Asus Laptop extra buttons";
	input->phys = ASUS_LAPTOP_खाता "/input0";
	input->id.bustype = BUS_HOST;
	input->dev.parent = &asus->platक्रमm_device->dev;

	error = sparse_keymap_setup(input, asus_keymap, शून्य);
	अगर (error) अणु
		pr_err("Unable to setup input device keymap\n");
		जाओ err_मुक्त_dev;
	पूर्ण
	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		pr_warn("Unable to register input device\n");
		जाओ err_मुक्त_dev;
	पूर्ण

	asus->inputdev = input;
	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(input);
	वापस error;
पूर्ण

अटल व्योम asus_input_निकास(काष्ठा asus_laptop *asus)
अणु
	अगर (asus->inputdev)
		input_unरेजिस्टर_device(asus->inputdev);
	asus->inputdev = शून्य;
पूर्ण

/*
 * ACPI driver
 */
अटल व्योम asus_acpi_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा asus_laptop *asus = acpi_driver_data(device);
	u16 count;

	/* TODO Find a better way to handle events count. */
	count = asus->event_count[event % 128]++;
	acpi_bus_generate_netlink_event(asus->device->pnp.device_class,
					dev_name(&asus->device->dev), event,
					count);

	अगर (event >= ATKD_BRNUP_MIN && event <= ATKD_BRNUP_MAX)
		event = ATKD_BRNUP;
	अन्यथा अगर (event >= ATKD_BRNDOWN_MIN &&
		 event <= ATKD_BRNDOWN_MAX)
		event = ATKD_BRNDOWN;

	/* Brightness events are special */
	अगर (event == ATKD_BRNDOWN || event == ATKD_BRNUP) अणु
		अगर (asus->backlight_device != शून्य) अणु
			/* Update the backlight device. */
			asus_backlight_notअगरy(asus);
			वापस ;
		पूर्ण
	पूर्ण

	/* Accelerometer "coarse orientation change" event */
	अगर (asus->pega_accel_poll && event == 0xEA) अणु
		kobject_uevent(&asus->pega_accel_poll->dev.kobj, KOBJ_CHANGE);
		वापस ;
	पूर्ण

	asus_input_notअगरy(asus, event);
पूर्ण

अटल काष्ठा attribute *asus_attributes[] = अणु
	&dev_attr_infos.attr,
	&dev_attr_wlan.attr,
	&dev_attr_bluetooth.attr,
	&dev_attr_wimax.attr,
	&dev_attr_wwan.attr,
	&dev_attr_display.attr,
	&dev_attr_ledd.attr,
	&dev_attr_ls_value.attr,
	&dev_attr_ls_level.attr,
	&dev_attr_ls_चयन.attr,
	&dev_attr_gps.attr,
	शून्य
पूर्ण;

अटल umode_t asus_sysfs_is_visible(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr,
				    पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा asus_laptop *asus = dev_get_drvdata(dev);
	acpi_handle handle = asus->handle;
	bool supported;

	अगर (asus->is_pega_lucid) अणु
		/* no ls_level पूर्णांकerface on the Lucid */
		अगर (attr == &dev_attr_ls_चयन.attr)
			supported = true;
		अन्यथा अगर (attr == &dev_attr_ls_level.attr)
			supported = false;
		अन्यथा
			जाओ normal;

		वापस supported ? attr->mode : 0;
	पूर्ण

normal:
	अगर (attr == &dev_attr_wlan.attr) अणु
		supported = !acpi_check_handle(handle, METHOD_WLAN, शून्य);

	पूर्ण अन्यथा अगर (attr == &dev_attr_bluetooth.attr) अणु
		supported = !acpi_check_handle(handle, METHOD_BLUETOOTH, शून्य);

	पूर्ण अन्यथा अगर (attr == &dev_attr_display.attr) अणु
		supported = !acpi_check_handle(handle, METHOD_SWITCH_DISPLAY, शून्य);

	पूर्ण अन्यथा अगर (attr == &dev_attr_wimax.attr) अणु
		supported =
			!acpi_check_handle(asus->handle, METHOD_WIMAX, शून्य);

	पूर्ण अन्यथा अगर (attr == &dev_attr_wwan.attr) अणु
		supported = !acpi_check_handle(asus->handle, METHOD_WWAN, शून्य);

	पूर्ण अन्यथा अगर (attr == &dev_attr_ledd.attr) अणु
		supported = !acpi_check_handle(handle, METHOD_LEDD, शून्य);

	पूर्ण अन्यथा अगर (attr == &dev_attr_ls_चयन.attr ||
		   attr == &dev_attr_ls_level.attr) अणु
		supported = !acpi_check_handle(handle, METHOD_ALS_CONTROL, शून्य) &&
			!acpi_check_handle(handle, METHOD_ALS_LEVEL, शून्य);
	पूर्ण अन्यथा अगर (attr == &dev_attr_ls_value.attr) अणु
		supported = asus->is_pega_lucid;
	पूर्ण अन्यथा अगर (attr == &dev_attr_gps.attr) अणु
		supported = !acpi_check_handle(handle, METHOD_GPS_ON, शून्य) &&
			    !acpi_check_handle(handle, METHOD_GPS_OFF, शून्य) &&
			    !acpi_check_handle(handle, METHOD_GPS_STATUS, शून्य);
	पूर्ण अन्यथा अणु
		supported = true;
	पूर्ण

	वापस supported ? attr->mode : 0;
पूर्ण


अटल स्थिर काष्ठा attribute_group asus_attr_group = अणु
	.is_visible	= asus_sysfs_is_visible,
	.attrs		= asus_attributes,
पूर्ण;

अटल पूर्णांक asus_platक्रमm_init(काष्ठा asus_laptop *asus)
अणु
	पूर्णांक result;

	asus->platक्रमm_device = platक्रमm_device_alloc(ASUS_LAPTOP_खाता, -1);
	अगर (!asus->platक्रमm_device)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(asus->platक्रमm_device, asus);

	result = platक्रमm_device_add(asus->platक्रमm_device);
	अगर (result)
		जाओ fail_platक्रमm_device;

	result = sysfs_create_group(&asus->platक्रमm_device->dev.kobj,
				    &asus_attr_group);
	अगर (result)
		जाओ fail_sysfs;

	वापस 0;

fail_sysfs:
	platक्रमm_device_del(asus->platक्रमm_device);
fail_platक्रमm_device:
	platक्रमm_device_put(asus->platक्रमm_device);
	वापस result;
पूर्ण

अटल व्योम asus_platक्रमm_निकास(काष्ठा asus_laptop *asus)
अणु
	sysfs_हटाओ_group(&asus->platक्रमm_device->dev.kobj, &asus_attr_group);
	platक्रमm_device_unरेजिस्टर(asus->platक्रमm_device);
पूर्ण

अटल काष्ठा platक्रमm_driver platक्रमm_driver = अणु
	.driver = अणु
		.name = ASUS_LAPTOP_खाता,
	पूर्ण,
पूर्ण;

/*
 * This function is used to initialize the context with right values. In this
 * method, we can make all the detection we want, and modअगरy the asus_laptop
 * काष्ठा
 */
अटल पूर्णांक asus_laptop_get_info(काष्ठा asus_laptop *asus)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *model = शून्य;
	अचिन्हित दीर्घ दीर्घ bsts_result;
	अक्षर *string = शून्य;
	acpi_status status;

	/*
	 * Get DSDT headers early enough to allow क्रम dअगरferentiating between
	 * models, but late enough to allow acpi_bus_रेजिस्टर_driver() to fail
	 * beक्रमe करोing anything ACPI-specअगरic. Should we encounter a machine,
	 * which needs special handling (i.e. its hotkey device has a dअगरferent
	 * HID), this bit will be moved.
	 */
	status = acpi_get_table(ACPI_SIG_DSDT, 1, &asus->dsdt_info);
	अगर (ACPI_FAILURE(status))
		pr_warn("Couldn't get the DSDT table header\n");

	/* We have to ग_लिखो 0 on init this far क्रम all ASUS models */
	अगर (ग_लिखो_acpi_पूर्णांक_ret(asus->handle, "INIT", 0, &buffer)) अणु
		pr_err("Hotkey initialization failed\n");
		वापस -ENODEV;
	पूर्ण

	/* This needs to be called क्रम some laptops to init properly */
	status =
	    acpi_evaluate_पूर्णांकeger(asus->handle, "BSTS", शून्य, &bsts_result);
	अगर (ACPI_FAILURE(status))
		pr_warn("Error calling BSTS\n");
	अन्यथा अगर (bsts_result)
		pr_notice("BSTS called, 0x%02x returned\n",
		       (uपूर्णांक) bsts_result);

	/* This too ... */
	अगर (ग_लिखो_acpi_पूर्णांक(asus->handle, "CWAP", wapf))
		pr_err("Error calling CWAP(%d)\n", wapf);
	/*
	 * Try to match the object वापसed by INIT to the specअगरic model.
	 * Handle every possible object (or the lack of thereof) the DSDT
	 * ग_लिखोrs might throw at us. When in trouble, we pass शून्य to
	 * asus_model_match() and try something completely dअगरferent.
	 */
	अगर (buffer.poपूर्णांकer) अणु
		model = buffer.poपूर्णांकer;
		चयन (model->type) अणु
		हाल ACPI_TYPE_STRING:
			string = model->string.poपूर्णांकer;
			अवरोध;
		हाल ACPI_TYPE_BUFFER:
			string = model->buffer.poपूर्णांकer;
			अवरोध;
		शेष:
			string = "";
			अवरोध;
		पूर्ण
	पूर्ण
	asus->name = kstrdup(string, GFP_KERNEL);
	अगर (!asus->name) अणु
		kमुक्त(buffer.poपूर्णांकer);
		वापस -ENOMEM;
	पूर्ण

	अगर (string)
		pr_notice("  %s model detected\n", string);

	अगर (!acpi_check_handle(asus->handle, METHOD_WL_STATUS, शून्य))
		asus->have_rsts = true;

	kमुक्त(model);

	वापस AE_OK;
पूर्ण

अटल पूर्णांक asus_acpi_init(काष्ठा asus_laptop *asus)
अणु
	पूर्णांक result = 0;

	result = acpi_bus_get_status(asus->device);
	अगर (result)
		वापस result;
	अगर (!asus->device->status.present) अणु
		pr_err("Hotkey device not present, aborting\n");
		वापस -ENODEV;
	पूर्ण

	result = asus_laptop_get_info(asus);
	अगर (result)
		वापस result;

	अगर (!म_भेद(bled_type, "led"))
		asus->bled_type = TYPE_LED;
	अन्यथा अगर (!म_भेद(bled_type, "rfkill"))
		asus->bled_type = TYPE_RFKILL;

	अगर (!म_भेद(wled_type, "led"))
		asus->wled_type = TYPE_LED;
	अन्यथा अगर (!म_भेद(wled_type, "rfkill"))
		asus->wled_type = TYPE_RFKILL;

	अगर (bluetooth_status >= 0)
		asus_bluetooth_set(asus, !!bluetooth_status);

	अगर (wlan_status >= 0)
		asus_wlan_set(asus, !!wlan_status);

	अगर (wimax_status >= 0)
		asus_wimax_set(asus, !!wimax_status);

	अगर (wwan_status >= 0)
		asus_wwan_set(asus, !!wwan_status);

	/* Keyboard Backlight is on by शेष */
	अगर (!acpi_check_handle(asus->handle, METHOD_KBD_LIGHT_SET, शून्य))
		asus_kled_set(asus, 1);

	/* LED display is off by शेष */
	asus->ledd_status = 0xFFF;

	/* Set initial values of light sensor and level */
	asus->light_चयन = !!als_status;
	asus->light_level = 5;	/* level 5 क्रम sensor sensitivity */

	अगर (asus->is_pega_lucid) अणु
		asus_als_चयन(asus, asus->light_चयन);
	पूर्ण अन्यथा अगर (!acpi_check_handle(asus->handle, METHOD_ALS_CONTROL, शून्य) &&
		   !acpi_check_handle(asus->handle, METHOD_ALS_LEVEL, शून्य)) अणु
		asus_als_चयन(asus, asus->light_चयन);
		asus_als_level(asus, asus->light_level);
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम asus_dmi_check(व्योम)
अणु
	स्थिर अक्षर *model;

	model = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	अगर (!model)
		वापस;

	/* On L1400B WLED control the sound card, करोn't mess with it ... */
	अगर (म_भेदन(model, "L1400B", 6) == 0) अणु
		wlan_status = -1;
	पूर्ण
पूर्ण

अटल bool asus_device_present;

अटल पूर्णांक asus_acpi_add(काष्ठा acpi_device *device)
अणु
	काष्ठा asus_laptop *asus;
	पूर्णांक result;

	pr_notice("Asus Laptop Support version %s\n",
		  ASUS_LAPTOP_VERSION);
	asus = kzalloc(माप(काष्ठा asus_laptop), GFP_KERNEL);
	अगर (!asus)
		वापस -ENOMEM;
	asus->handle = device->handle;
	म_नकल(acpi_device_name(device), ASUS_LAPTOP_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ASUS_LAPTOP_CLASS);
	device->driver_data = asus;
	asus->device = device;

	asus_dmi_check();

	result = asus_acpi_init(asus);
	अगर (result)
		जाओ fail_platक्रमm;

	/*
	 * Need platक्रमm type detection first, then the platक्रमm
	 * device.  It is used as a parent क्रम the sub-devices below.
	 */
	asus->is_pega_lucid = asus_check_pega_lucid(asus);
	result = asus_platक्रमm_init(asus);
	अगर (result)
		जाओ fail_platक्रमm;

	अगर (acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
		result = asus_backlight_init(asus);
		अगर (result)
			जाओ fail_backlight;
	पूर्ण

	result = asus_input_init(asus);
	अगर (result)
		जाओ fail_input;

	result = asus_led_init(asus);
	अगर (result)
		जाओ fail_led;

	result = asus_rfसमाप्त_init(asus);
	अगर (result && result != -ENODEV)
		जाओ fail_rfसमाप्त;

	result = pega_accel_init(asus);
	अगर (result && result != -ENODEV)
		जाओ fail_pega_accel;

	result = pega_rfसमाप्त_init(asus);
	अगर (result && result != -ENODEV)
		जाओ fail_pega_rfसमाप्त;

	asus_device_present = true;
	वापस 0;

fail_pega_rfसमाप्त:
	pega_accel_निकास(asus);
fail_pega_accel:
	asus_rfसमाप्त_निकास(asus);
fail_rfसमाप्त:
	asus_led_निकास(asus);
fail_led:
	asus_input_निकास(asus);
fail_input:
	asus_backlight_निकास(asus);
fail_backlight:
	asus_platक्रमm_निकास(asus);
fail_platक्रमm:
	kमुक्त(asus);

	वापस result;
पूर्ण

अटल पूर्णांक asus_acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा asus_laptop *asus = acpi_driver_data(device);

	asus_backlight_निकास(asus);
	asus_rfसमाप्त_निकास(asus);
	asus_led_निकास(asus);
	asus_input_निकास(asus);
	pega_accel_निकास(asus);
	asus_platक्रमm_निकास(asus);

	kमुक्त(asus->name);
	kमुक्त(asus);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id asus_device_ids[] = अणु
	अणु"ATK0100", 0पूर्ण,
	अणु"ATK0101", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, asus_device_ids);

अटल काष्ठा acpi_driver asus_acpi_driver = अणु
	.name = ASUS_LAPTOP_NAME,
	.class = ASUS_LAPTOP_CLASS,
	.owner = THIS_MODULE,
	.ids = asus_device_ids,
	.flags = ACPI_DRIVER_ALL_NOTIFY_EVENTS,
	.ops = अणु
		.add = asus_acpi_add,
		.हटाओ = asus_acpi_हटाओ,
		.notअगरy = asus_acpi_notअगरy,
		पूर्ण,
पूर्ण;

अटल पूर्णांक __init asus_laptop_init(व्योम)
अणु
	पूर्णांक result;

	result = platक्रमm_driver_रेजिस्टर(&platक्रमm_driver);
	अगर (result < 0)
		वापस result;

	result = acpi_bus_रेजिस्टर_driver(&asus_acpi_driver);
	अगर (result < 0)
		जाओ fail_acpi_driver;
	अगर (!asus_device_present) अणु
		result = -ENODEV;
		जाओ fail_no_device;
	पूर्ण
	वापस 0;

fail_no_device:
	acpi_bus_unरेजिस्टर_driver(&asus_acpi_driver);
fail_acpi_driver:
	platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
	वापस result;
पूर्ण

अटल व्योम __निकास asus_laptop_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&asus_acpi_driver);
	platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
पूर्ण

module_init(asus_laptop_init);
module_निकास(asus_laptop_निकास);
