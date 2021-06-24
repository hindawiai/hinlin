<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  toshiba_acpi.c - Toshiba Laptop ACPI Extras
 *
 *  Copyright (C) 2002-2004 John Belmonte
 *  Copyright (C) 2008 Philip Langdale
 *  Copyright (C) 2010 Pierre Ducroquet
 *  Copyright (C) 2014-2016 Azael Avalos
 *
 *  The devolpment page क्रम this driver is located at
 *  http://memebeam.org/toys/ToshibaAcpiDriver.
 *
 *  Credits:
 *	Jonathan A. Buzzard - Toshiba HCI info, and critical tips on reverse
 *		engineering the Winकरोws drivers
 *	Yasushi Nagato - changes क्रम linux kernel 2.4 -> 2.5
 *	Rob Miller - TV out and hotkeys help
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा TOSHIBA_ACPI_VERSION	"0.24"
#घोषणा PROC_INTERFACE_VERSION	1

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/backlight.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/i8042.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/toshiba.h>
#समावेश <acpi/video.h>

MODULE_AUTHOR("John Belmonte");
MODULE_DESCRIPTION("Toshiba Laptop ACPI Extras Driver");
MODULE_LICENSE("GPL");

#घोषणा TOSHIBA_WMI_EVENT_GUID "59142400-C6A3-40FA-BADB-8A2652834100"

/* Scan code क्रम Fn key on TOS1900 models */
#घोषणा TOS1900_FN_SCAN		0x6e

/* Toshiba ACPI method paths */
#घोषणा METHOD_VIDEO_OUT	"\\_SB_.VALX.DSSX"

/*
 * The Toshiba configuration पूर्णांकerface is composed of the HCI and the SCI,
 * which are defined as follows:
 *
 * HCI is Toshiba's "Hardware Control Interface" which is supposed to
 * be unअगरorm across all their models.  Ideally we would just call
 * dedicated ACPI methods instead of using this primitive पूर्णांकerface.
 * However the ACPI methods seem to be incomplete in some areas (क्रम
 * example they allow setting, but not पढ़ोing, the LCD brightness value),
 * so this is still useful.
 *
 * SCI stands क्रम "System Configuration Interface" which aim is to
 * conceal dअगरferences in hardware between dअगरferent models.
 */

#घोषणा TCI_WORDS			6

/* Operations */
#घोषणा HCI_SET				0xff00
#घोषणा HCI_GET				0xfe00
#घोषणा SCI_OPEN			0xf100
#घोषणा SCI_CLOSE			0xf200
#घोषणा SCI_GET				0xf300
#घोषणा SCI_SET				0xf400

/* Return codes */
#घोषणा TOS_SUCCESS			0x0000
#घोषणा TOS_SUCCESS2			0x0001
#घोषणा TOS_OPEN_CLOSE_OK		0x0044
#घोषणा TOS_FAILURE			0x1000
#घोषणा TOS_NOT_SUPPORTED		0x8000
#घोषणा TOS_ALREADY_OPEN		0x8100
#घोषणा TOS_NOT_OPENED			0x8200
#घोषणा TOS_INPUT_DATA_ERROR		0x8300
#घोषणा TOS_WRITE_PROTECTED		0x8400
#घोषणा TOS_NOT_PRESENT			0x8600
#घोषणा TOS_FIFO_EMPTY			0x8c00
#घोषणा TOS_DATA_NOT_AVAILABLE		0x8d20
#घोषणा TOS_NOT_INITIALIZED		0x8d50
#घोषणा TOS_NOT_INSTALLED		0x8e00

/* Registers */
#घोषणा HCI_FAN				0x0004
#घोषणा HCI_TR_BACKLIGHT		0x0005
#घोषणा HCI_SYSTEM_EVENT		0x0016
#घोषणा HCI_VIDEO_OUT			0x001c
#घोषणा HCI_HOTKEY_EVENT		0x001e
#घोषणा HCI_LCD_BRIGHTNESS		0x002a
#घोषणा HCI_WIRELESS			0x0056
#घोषणा HCI_ACCELEROMETER		0x006d
#घोषणा HCI_COOLING_METHOD		0x007f
#घोषणा HCI_KBD_ILLUMINATION		0x0095
#घोषणा HCI_ECO_MODE			0x0097
#घोषणा HCI_ACCELEROMETER2		0x00a6
#घोषणा HCI_SYSTEM_INFO			0xc000
#घोषणा SCI_PANEL_POWER_ON		0x010d
#घोषणा SCI_ILLUMINATION		0x014e
#घोषणा SCI_USB_SLEEP_CHARGE		0x0150
#घोषणा SCI_KBD_ILLUM_STATUS		0x015c
#घोषणा SCI_USB_SLEEP_MUSIC		0x015e
#घोषणा SCI_USB_THREE			0x0169
#घोषणा SCI_TOUCHPAD			0x050e
#घोषणा SCI_KBD_FUNCTION_KEYS		0x0522

/* Field definitions */
#घोषणा HCI_ACCEL_MASK			0x7fff
#घोषणा HCI_ACCEL_सूचीECTION_MASK	0x8000
#घोषणा HCI_HOTKEY_DISABLE		0x0b
#घोषणा HCI_HOTKEY_ENABLE		0x09
#घोषणा HCI_HOTKEY_SPECIAL_FUNCTIONS	0x10
#घोषणा HCI_LCD_BRIGHTNESS_BITS		3
#घोषणा HCI_LCD_BRIGHTNESS_SHIFT	(16-HCI_LCD_BRIGHTNESS_BITS)
#घोषणा HCI_LCD_BRIGHTNESS_LEVELS	(1 << HCI_LCD_BRIGHTNESS_BITS)
#घोषणा HCI_MISC_SHIFT			0x10
#घोषणा HCI_SYSTEM_TYPE1		0x10
#घोषणा HCI_SYSTEM_TYPE2		0x11
#घोषणा HCI_VIDEO_OUT_LCD		0x1
#घोषणा HCI_VIDEO_OUT_CRT		0x2
#घोषणा HCI_VIDEO_OUT_TV		0x4
#घोषणा SCI_KBD_MODE_MASK		0x1f
#घोषणा SCI_KBD_MODE_FNZ		0x1
#घोषणा SCI_KBD_MODE_AUTO		0x2
#घोषणा SCI_KBD_MODE_ON			0x8
#घोषणा SCI_KBD_MODE_OFF		0x10
#घोषणा SCI_KBD_TIME_MAX		0x3c001a
#घोषणा HCI_WIRELESS_STATUS		0x1
#घोषणा HCI_WIRELESS_WWAN		0x3
#घोषणा HCI_WIRELESS_WWAN_STATUS	0x2000
#घोषणा HCI_WIRELESS_WWAN_POWER		0x4000
#घोषणा SCI_USB_CHARGE_MODE_MASK	0xff
#घोषणा SCI_USB_CHARGE_DISABLED		0x00
#घोषणा SCI_USB_CHARGE_ALTERNATE	0x09
#घोषणा SCI_USB_CHARGE_TYPICAL		0x11
#घोषणा SCI_USB_CHARGE_AUTO		0x21
#घोषणा SCI_USB_CHARGE_BAT_MASK		0x7
#घोषणा SCI_USB_CHARGE_BAT_LVL_OFF	0x1
#घोषणा SCI_USB_CHARGE_BAT_LVL_ON	0x4
#घोषणा SCI_USB_CHARGE_BAT_LVL		0x0200
#घोषणा SCI_USB_CHARGE_RAPID_DSP	0x0300

काष्ठा toshiba_acpi_dev अणु
	काष्ठा acpi_device *acpi_dev;
	स्थिर अक्षर *method_hci;
	काष्ठा input_dev *hotkey_dev;
	काष्ठा work_काष्ठा hotkey_work;
	काष्ठा backlight_device *backlight_dev;
	काष्ठा led_classdev led_dev;
	काष्ठा led_classdev kbd_led;
	काष्ठा led_classdev eco_led;
	काष्ठा miscdevice miscdev;
	काष्ठा rfसमाप्त *wwan_rfk;
	काष्ठा iio_dev *indio_dev;

	पूर्णांक क्रमce_fan;
	पूर्णांक last_key_event;
	पूर्णांक key_event_valid;
	पूर्णांक kbd_type;
	पूर्णांक kbd_mode;
	पूर्णांक kbd_समय;
	पूर्णांक usbsc_bat_level;
	पूर्णांक usbsc_mode_base;
	पूर्णांक hotkey_event_type;
	पूर्णांक max_cooling_method;

	अचिन्हित पूर्णांक illumination_supported:1;
	अचिन्हित पूर्णांक video_supported:1;
	अचिन्हित पूर्णांक fan_supported:1;
	अचिन्हित पूर्णांक प्रणाली_event_supported:1;
	अचिन्हित पूर्णांक ntfy_supported:1;
	अचिन्हित पूर्णांक info_supported:1;
	अचिन्हित पूर्णांक tr_backlight_supported:1;
	अचिन्हित पूर्णांक kbd_illum_supported:1;
	अचिन्हित पूर्णांक touchpad_supported:1;
	अचिन्हित पूर्णांक eco_supported:1;
	अचिन्हित पूर्णांक accelerometer_supported:1;
	अचिन्हित पूर्णांक usb_sleep_अक्षरge_supported:1;
	अचिन्हित पूर्णांक usb_rapid_अक्षरge_supported:1;
	अचिन्हित पूर्णांक usb_sleep_music_supported:1;
	अचिन्हित पूर्णांक kbd_function_keys_supported:1;
	अचिन्हित पूर्णांक panel_घातer_on_supported:1;
	अचिन्हित पूर्णांक usb_three_supported:1;
	अचिन्हित पूर्णांक wwan_supported:1;
	अचिन्हित पूर्णांक cooling_method_supported:1;
	अचिन्हित पूर्णांक sysfs_created:1;
	अचिन्हित पूर्णांक special_functions;

	bool kbd_event_generated;
	bool समाप्तचयन;
पूर्ण;

अटल काष्ठा toshiba_acpi_dev *toshiba_acpi;

अटल bool disable_hotkeys;
module_param(disable_hotkeys, bool, 0444);
MODULE_PARM_DESC(disable_hotkeys, "Disables the hotkeys activation");

अटल स्थिर काष्ठा acpi_device_id toshiba_device_ids[] = अणु
	अणु"TOS6200", 0पूर्ण,
	अणु"TOS6207", 0पूर्ण,
	अणु"TOS6208", 0पूर्ण,
	अणु"TOS1900", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, toshiba_device_ids);

अटल स्थिर काष्ठा key_entry toshiba_acpi_keymap[] = अणु
	अणु KE_KEY, 0x9e, अणु KEY_RFKILL पूर्ण पूर्ण,
	अणु KE_KEY, 0x101, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY, 0x102, अणु KEY_ZOOMOUT पूर्ण पूर्ण,
	अणु KE_KEY, 0x103, अणु KEY_ZOOMIN पूर्ण पूर्ण,
	अणु KE_KEY, 0x10f, अणु KEY_TAB पूर्ण पूर्ण,
	अणु KE_KEY, 0x12c, अणु KEY_KBDILLUMTOGGLE पूर्ण पूर्ण,
	अणु KE_KEY, 0x139, अणु KEY_ZOOMRESET पूर्ण पूर्ण,
	अणु KE_KEY, 0x13b, अणु KEY_COFFEE पूर्ण पूर्ण,
	अणु KE_KEY, 0x13c, अणु KEY_BATTERY पूर्ण पूर्ण,
	अणु KE_KEY, 0x13d, अणु KEY_SLEEP पूर्ण पूर्ण,
	अणु KE_KEY, 0x13e, अणु KEY_SUSPEND पूर्ण पूर्ण,
	अणु KE_KEY, 0x13f, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,
	अणु KE_KEY, 0x140, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0x141, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x142, अणु KEY_WLAN पूर्ण पूर्ण,
	अणु KE_KEY, 0x143, अणु KEY_TOUCHPAD_TOGGLE पूर्ण पूर्ण,
	अणु KE_KEY, 0x17f, अणु KEY_FN पूर्ण पूर्ण,
	अणु KE_KEY, 0xb05, अणु KEY_PROG2 पूर्ण पूर्ण,
	अणु KE_KEY, 0xb06, अणु KEY_WWW पूर्ण पूर्ण,
	अणु KE_KEY, 0xb07, अणु KEY_MAIL पूर्ण पूर्ण,
	अणु KE_KEY, 0xb30, अणु KEY_STOP पूर्ण पूर्ण,
	अणु KE_KEY, 0xb31, अणु KEY_PREVIOUSSONG पूर्ण पूर्ण,
	अणु KE_KEY, 0xb32, अणु KEY_NEXTSONG पूर्ण पूर्ण,
	अणु KE_KEY, 0xb33, अणु KEY_PLAYPAUSE पूर्ण पूर्ण,
	अणु KE_KEY, 0xb5a, अणु KEY_MEDIA पूर्ण पूर्ण,
	अणु KE_IGNORE, 0x1430, अणु KEY_RESERVED पूर्ण पूर्ण, /* Wake from sleep */
	अणु KE_IGNORE, 0x1501, अणु KEY_RESERVED पूर्ण पूर्ण, /* Output changed */
	अणु KE_IGNORE, 0x1502, अणु KEY_RESERVED पूर्ण पूर्ण, /* HDMI plugged/unplugged */
	अणु KE_IGNORE, 0x1ABE, अणु KEY_RESERVED पूर्ण पूर्ण, /* Protection level set */
	अणु KE_IGNORE, 0x1ABF, अणु KEY_RESERVED पूर्ण पूर्ण, /* Protection level off */
	अणु KE_END, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा key_entry toshiba_acpi_alt_keymap[] = अणु
	अणु KE_KEY, 0x102, अणु KEY_ZOOMOUT पूर्ण पूर्ण,
	अणु KE_KEY, 0x103, अणु KEY_ZOOMIN पूर्ण पूर्ण,
	अणु KE_KEY, 0x12c, अणु KEY_KBDILLUMTOGGLE पूर्ण पूर्ण,
	अणु KE_KEY, 0x139, अणु KEY_ZOOMRESET पूर्ण पूर्ण,
	अणु KE_KEY, 0x13c, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0x13d, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x13e, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,
	अणु KE_KEY, 0x13f, अणु KEY_TOUCHPAD_TOGGLE पूर्ण पूर्ण,
	अणु KE_KEY, 0x157, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY, 0x158, अणु KEY_WLAN पूर्ण पूर्ण,
	अणु KE_END, 0 पूर्ण,
पूर्ण;

/*
 * List of models which have a broken acpi-video backlight पूर्णांकerface and thus
 * need to use the toshiba (venकरोr) पूर्णांकerface instead.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id toshiba_venकरोr_backlight_dmi[] = अणु
	अणुपूर्ण
पूर्ण;

/*
 * Utility
 */

अटल अंतरभूत व्योम _set_bit(u32 *word, u32 mask, पूर्णांक value)
अणु
	*word = (*word & ~mask) | (mask * value);
पूर्ण

/*
 * ACPI पूर्णांकerface wrappers
 */

अटल पूर्णांक ग_लिखो_acpi_पूर्णांक(स्थिर अक्षर *methodName, पूर्णांक val)
अणु
	acpi_status status;

	status = acpi_execute_simple_method(शून्य, (अक्षर *)methodName, val);
	वापस (status == AE_OK) ? 0 : -EIO;
पूर्ण

/*
 * Perक्रमm a raw configuration call.  Here we करोn't care about input or output
 * buffer क्रमmat.
 */
अटल acpi_status tci_raw(काष्ठा toshiba_acpi_dev *dev,
			   स्थिर u32 in[TCI_WORDS], u32 out[TCI_WORDS])
अणु
	जोड़ acpi_object in_objs[TCI_WORDS], out_objs[TCI_WORDS + 1];
	काष्ठा acpi_object_list params;
	काष्ठा acpi_buffer results;
	acpi_status status;
	पूर्णांक i;

	params.count = TCI_WORDS;
	params.poपूर्णांकer = in_objs;
	क्रम (i = 0; i < TCI_WORDS; ++i) अणु
		in_objs[i].type = ACPI_TYPE_INTEGER;
		in_objs[i].पूर्णांकeger.value = in[i];
	पूर्ण

	results.length = माप(out_objs);
	results.poपूर्णांकer = out_objs;

	status = acpi_evaluate_object(dev->acpi_dev->handle,
				      (अक्षर *)dev->method_hci, &params,
				      &results);
	अगर ((status == AE_OK) && (out_objs->package.count <= TCI_WORDS)) अणु
		क्रम (i = 0; i < out_objs->package.count; ++i)
			out[i] = out_objs->package.elements[i].पूर्णांकeger.value;
	पूर्ण

	वापस status;
पूर्ण

/*
 * Common hci tasks
 *
 * In addition to the ACPI status, the HCI प्रणाली वापसs a result which
 * may be useful (such as "not supported").
 */

अटल u32 hci_ग_लिखो(काष्ठा toshiba_acpi_dev *dev, u32 reg, u32 in1)
अणु
	u32 in[TCI_WORDS] = अणु HCI_SET, reg, in1, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status = tci_raw(dev, in, out);

	वापस ACPI_SUCCESS(status) ? out[0] : TOS_FAILURE;
पूर्ण

अटल u32 hci_पढ़ो(काष्ठा toshiba_acpi_dev *dev, u32 reg, u32 *out1)
अणु
	u32 in[TCI_WORDS] = अणु HCI_GET, reg, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status = tci_raw(dev, in, out);

	अगर (ACPI_FAILURE(status))
		वापस TOS_FAILURE;

	*out1 = out[2];

	वापस out[0];
पूर्ण

/*
 * Common sci tasks
 */

अटल पूर्णांक sci_खोलो(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु SCI_OPEN, 0, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status = tci_raw(dev, in, out);

	अगर  (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to open SCI failed\n");
		वापस 0;
	पूर्ण

	अगर (out[0] == TOS_OPEN_CLOSE_OK) अणु
		वापस 1;
	पूर्ण अन्यथा अगर (out[0] == TOS_ALREADY_OPEN) अणु
		pr_info("Toshiba SCI already opened\n");
		वापस 1;
	पूर्ण अन्यथा अगर (out[0] == TOS_NOT_SUPPORTED) अणु
		/*
		 * Some BIOSes करो not have the SCI खोलो/बंद functions
		 * implemented and वापस 0x8000 (Not Supported), failing to
		 * रेजिस्टर some supported features.
		 *
		 * Simply वापस 1 अगर we hit those affected laptops to make the
		 * supported features work.
		 *
		 * In the हाल that some laptops really करो not support the SCI,
		 * all the SCI dependent functions check क्रम TOS_NOT_SUPPORTED,
		 * and thus, not रेजिस्टरing support क्रम the queried feature.
		 */
		वापस 1;
	पूर्ण अन्यथा अगर (out[0] == TOS_NOT_PRESENT) अणु
		pr_info("Toshiba SCI is not present\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sci_बंद(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु SCI_CLOSE, 0, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status = tci_raw(dev, in, out);

	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to close SCI failed\n");
		वापस;
	पूर्ण

	अगर (out[0] == TOS_OPEN_CLOSE_OK)
		वापस;
	अन्यथा अगर (out[0] == TOS_NOT_OPENED)
		pr_info("Toshiba SCI not opened\n");
	अन्यथा अगर (out[0] == TOS_NOT_PRESENT)
		pr_info("Toshiba SCI is not present\n");
पूर्ण

अटल u32 sci_पढ़ो(काष्ठा toshiba_acpi_dev *dev, u32 reg, u32 *out1)
अणु
	u32 in[TCI_WORDS] = अणु SCI_GET, reg, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status = tci_raw(dev, in, out);

	अगर (ACPI_FAILURE(status))
		वापस TOS_FAILURE;

	*out1 = out[2];

	वापस out[0];
पूर्ण

अटल u32 sci_ग_लिखो(काष्ठा toshiba_acpi_dev *dev, u32 reg, u32 in1)
अणु
	u32 in[TCI_WORDS] = अणु SCI_SET, reg, in1, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status = tci_raw(dev, in, out);

	वापस ACPI_SUCCESS(status) ? out[0] : TOS_FAILURE;
पूर्ण

/* Illumination support */
अटल व्योम toshiba_illumination_available(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु SCI_GET, SCI_ILLUMINATION, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	dev->illumination_supported = 0;

	अगर (!sci_खोलो(dev))
		वापस;

	status = tci_raw(dev, in, out);
	sci_बंद(dev);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to query Illumination support failed\n");
		वापस;
	पूर्ण

	अगर (out[0] != TOS_SUCCESS)
		वापस;

	dev->illumination_supported = 1;
पूर्ण

अटल व्योम toshiba_illumination_set(काष्ठा led_classdev *cdev,
				     क्रमागत led_brightness brightness)
अणु
	काष्ठा toshiba_acpi_dev *dev = container_of(cdev,
			काष्ठा toshiba_acpi_dev, led_dev);
	u32 result;
	u32 state;

	/* First request : initialize communication. */
	अगर (!sci_खोलो(dev))
		वापस;

	/* Switch the illumination on/off */
	state = brightness ? 1 : 0;
	result = sci_ग_लिखो(dev, SCI_ILLUMINATION, state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call for illumination failed\n");
पूर्ण

अटल क्रमागत led_brightness toshiba_illumination_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा toshiba_acpi_dev *dev = container_of(cdev,
			काष्ठा toshiba_acpi_dev, led_dev);
	u32 result;
	u32 state;

	/* First request : initialize communication. */
	अगर (!sci_खोलो(dev))
		वापस LED_OFF;

	/* Check the illumination */
	result = sci_पढ़ो(dev, SCI_ILLUMINATION, &state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE) अणु
		pr_err("ACPI call for illumination failed\n");
		वापस LED_OFF;
	पूर्ण अन्यथा अगर (result != TOS_SUCCESS) अणु
		वापस LED_OFF;
	पूर्ण

	वापस state ? LED_FULL : LED_OFF;
पूर्ण

/* KBD Illumination */
अटल व्योम toshiba_kbd_illum_available(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु SCI_GET, SCI_KBD_ILLUM_STATUS, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	dev->kbd_illum_supported = 0;
	dev->kbd_event_generated = false;

	अगर (!sci_खोलो(dev))
		वापस;

	status = tci_raw(dev, in, out);
	sci_बंद(dev);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to query kbd illumination support failed\n");
		वापस;
	पूर्ण

	अगर (out[0] != TOS_SUCCESS)
		वापस;

	/*
	 * Check क्रम keyboard backlight समयout max value,
	 * previous kbd backlight implementation set this to
	 * 0x3c0003, and now the new implementation set this
	 * to 0x3c001a, use this to distinguish between them.
	 */
	अगर (out[3] == SCI_KBD_TIME_MAX)
		dev->kbd_type = 2;
	अन्यथा
		dev->kbd_type = 1;
	/* Get the current keyboard backlight mode */
	dev->kbd_mode = out[2] & SCI_KBD_MODE_MASK;
	/* Get the current समय (1-60 seconds) */
	dev->kbd_समय = out[2] >> HCI_MISC_SHIFT;
	/* Flag as supported */
	dev->kbd_illum_supported = 1;
पूर्ण

अटल पूर्णांक toshiba_kbd_illum_status_set(काष्ठा toshiba_acpi_dev *dev, u32 समय)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_ग_लिखो(dev, SCI_KBD_ILLUM_STATUS, समय);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set KBD backlight status failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_kbd_illum_status_get(काष्ठा toshiba_acpi_dev *dev, u32 *समय)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_पढ़ो(dev, SCI_KBD_ILLUM_STATUS, समय);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get KBD backlight status failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल क्रमागत led_brightness toshiba_kbd_backlight_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा toshiba_acpi_dev *dev = container_of(cdev,
			काष्ठा toshiba_acpi_dev, kbd_led);
	u32 result;
	u32 state;

	/* Check the keyboard backlight state */
	result = hci_पढ़ो(dev, HCI_KBD_ILLUMINATION, &state);
	अगर (result == TOS_FAILURE) अणु
		pr_err("ACPI call to get the keyboard backlight failed\n");
		वापस LED_OFF;
	पूर्ण अन्यथा अगर (result != TOS_SUCCESS) अणु
		वापस LED_OFF;
	पूर्ण

	वापस state ? LED_FULL : LED_OFF;
पूर्ण

अटल व्योम toshiba_kbd_backlight_set(काष्ठा led_classdev *cdev,
				     क्रमागत led_brightness brightness)
अणु
	काष्ठा toshiba_acpi_dev *dev = container_of(cdev,
			काष्ठा toshiba_acpi_dev, kbd_led);
	u32 result;
	u32 state;

	/* Set the keyboard backlight state */
	state = brightness ? 1 : 0;
	result = hci_ग_लिखो(dev, HCI_KBD_ILLUMINATION, state);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set KBD Illumination mode failed\n");
पूर्ण

/* TouchPad support */
अटल पूर्णांक toshiba_touchpad_set(काष्ठा toshiba_acpi_dev *dev, u32 state)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_ग_लिखो(dev, SCI_TOUCHPAD, state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set the touchpad failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_touchpad_get(काष्ठा toshiba_acpi_dev *dev, u32 *state)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_पढ़ो(dev, SCI_TOUCHPAD, state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to query the touchpad failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

/* Eco Mode support */
अटल व्योम toshiba_eco_mode_available(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु HCI_GET, HCI_ECO_MODE, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	dev->eco_supported = 0;

	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get ECO led failed\n");
		वापस;
	पूर्ण

	अगर (out[0] == TOS_INPUT_DATA_ERROR) अणु
		/*
		 * If we receive 0x8300 (Input Data Error), it means that the
		 * LED device is present, but that we just screwed the input
		 * parameters.
		 *
		 * Let's query the status of the LED to see अगर we really have a
		 * success response, indicating the actual presense of the LED,
		 * bail out otherwise.
		 */
		in[3] = 1;
		status = tci_raw(dev, in, out);
		अगर (ACPI_FAILURE(status)) अणु
			pr_err("ACPI call to get ECO led failed\n");
			वापस;
		पूर्ण

		अगर (out[0] != TOS_SUCCESS)
			वापस;

		dev->eco_supported = 1;
	पूर्ण
पूर्ण

अटल क्रमागत led_brightness
toshiba_eco_mode_get_status(काष्ठा led_classdev *cdev)
अणु
	काष्ठा toshiba_acpi_dev *dev = container_of(cdev,
			काष्ठा toshiba_acpi_dev, eco_led);
	u32 in[TCI_WORDS] = अणु HCI_GET, HCI_ECO_MODE, 0, 1, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get ECO led failed\n");
		वापस LED_OFF;
	पूर्ण

	अगर (out[0] != TOS_SUCCESS)
		वापस LED_OFF;

	वापस out[2] ? LED_FULL : LED_OFF;
पूर्ण

अटल व्योम toshiba_eco_mode_set_status(काष्ठा led_classdev *cdev,
				     क्रमागत led_brightness brightness)
अणु
	काष्ठा toshiba_acpi_dev *dev = container_of(cdev,
			काष्ठा toshiba_acpi_dev, eco_led);
	u32 in[TCI_WORDS] = अणु HCI_SET, HCI_ECO_MODE, 0, 1, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	/* Switch the Eco Mode led on/off */
	in[2] = (brightness) ? 1 : 0;
	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status))
		pr_err("ACPI call to set ECO led failed\n");
पूर्ण

/* Accelerometer support */
अटल व्योम toshiba_accelerometer_available(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु HCI_GET, HCI_ACCELEROMETER2, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	dev->accelerometer_supported = 0;

	/*
	 * Check अगर the accelerometer call exists,
	 * this call also serves as initialization
	 */
	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to query the accelerometer failed\n");
		वापस;
	पूर्ण

	अगर (out[0] != TOS_SUCCESS)
		वापस;

	dev->accelerometer_supported = 1;
पूर्ण

अटल पूर्णांक toshiba_accelerometer_get(काष्ठा toshiba_acpi_dev *dev,
				     u32 *xy, u32 *z)
अणु
	u32 in[TCI_WORDS] = अणु HCI_GET, HCI_ACCELEROMETER, 0, 1, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	/* Check the Accelerometer status */
	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to query the accelerometer failed\n");
		वापस -EIO;
	पूर्ण

	अगर (out[0] == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	अगर (out[0] != TOS_SUCCESS)
		वापस -EIO;

	*xy = out[2];
	*z = out[4];

	वापस 0;
पूर्ण

/* Sleep (Charge and Music) utilities support */
अटल व्योम toshiba_usb_sleep_अक्षरge_available(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु SCI_GET, SCI_USB_SLEEP_CHARGE, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	dev->usb_sleep_अक्षरge_supported = 0;

	अगर (!sci_खोलो(dev))
		वापस;

	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get USB Sleep and Charge mode failed\n");
		sci_बंद(dev);
		वापस;
	पूर्ण

	अगर (out[0] != TOS_SUCCESS) अणु
		sci_बंद(dev);
		वापस;
	पूर्ण

	dev->usbsc_mode_base = out[4];

	in[5] = SCI_USB_CHARGE_BAT_LVL;
	status = tci_raw(dev, in, out);
	sci_बंद(dev);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get USB Sleep and Charge mode failed\n");
		वापस;
	पूर्ण

	अगर (out[0] != TOS_SUCCESS)
		वापस;

	dev->usbsc_bat_level = out[2];
	/* Flag as supported */
	dev->usb_sleep_अक्षरge_supported = 1;
पूर्ण

अटल पूर्णांक toshiba_usb_sleep_अक्षरge_get(काष्ठा toshiba_acpi_dev *dev,
					u32 *mode)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_पढ़ो(dev, SCI_USB_SLEEP_CHARGE, mode);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set USB S&C mode failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_usb_sleep_अक्षरge_set(काष्ठा toshiba_acpi_dev *dev,
					u32 mode)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_ग_लिखो(dev, SCI_USB_SLEEP_CHARGE, mode);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set USB S&C mode failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_sleep_functions_status_get(काष्ठा toshiba_acpi_dev *dev,
					      u32 *mode)
अणु
	u32 in[TCI_WORDS] = अणु SCI_GET, SCI_USB_SLEEP_CHARGE, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	in[5] = SCI_USB_CHARGE_BAT_LVL;
	status = tci_raw(dev, in, out);
	sci_बंद(dev);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get USB S&C battery level failed\n");
		वापस -EIO;
	पूर्ण

	अगर (out[0] == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	अगर (out[0] != TOS_SUCCESS)
		वापस -EIO;

	*mode = out[2];

	वापस 0;

पूर्ण

अटल पूर्णांक toshiba_sleep_functions_status_set(काष्ठा toshiba_acpi_dev *dev,
					      u32 mode)
अणु
	u32 in[TCI_WORDS] = अणु SCI_SET, SCI_USB_SLEEP_CHARGE, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	in[2] = mode;
	in[5] = SCI_USB_CHARGE_BAT_LVL;
	status = tci_raw(dev, in, out);
	sci_बंद(dev);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to set USB S&C battery level failed\n");
		वापस -EIO;
	पूर्ण

	अगर (out[0] == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस out[0] == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_usb_rapid_अक्षरge_get(काष्ठा toshiba_acpi_dev *dev,
					u32 *state)
अणु
	u32 in[TCI_WORDS] = अणु SCI_GET, SCI_USB_SLEEP_CHARGE, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	in[5] = SCI_USB_CHARGE_RAPID_DSP;
	status = tci_raw(dev, in, out);
	sci_बंद(dev);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get USB Rapid Charge failed\n");
		वापस -EIO;
	पूर्ण

	अगर (out[0] == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	अगर (out[0] != TOS_SUCCESS && out[0] != TOS_SUCCESS2)
		वापस -EIO;

	*state = out[2];

	वापस 0;
पूर्ण

अटल पूर्णांक toshiba_usb_rapid_अक्षरge_set(काष्ठा toshiba_acpi_dev *dev,
					u32 state)
अणु
	u32 in[TCI_WORDS] = अणु SCI_SET, SCI_USB_SLEEP_CHARGE, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	in[2] = state;
	in[5] = SCI_USB_CHARGE_RAPID_DSP;
	status = tci_raw(dev, in, out);
	sci_बंद(dev);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to set USB Rapid Charge failed\n");
		वापस -EIO;
	पूर्ण

	अगर (out[0] == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस (out[0] == TOS_SUCCESS || out[0] == TOS_SUCCESS2) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_usb_sleep_music_get(काष्ठा toshiba_acpi_dev *dev, u32 *state)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_पढ़ो(dev, SCI_USB_SLEEP_MUSIC, state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get Sleep and Music failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_usb_sleep_music_set(काष्ठा toshiba_acpi_dev *dev, u32 state)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_ग_लिखो(dev, SCI_USB_SLEEP_MUSIC, state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set Sleep and Music failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

/* Keyboard function keys */
अटल पूर्णांक toshiba_function_keys_get(काष्ठा toshiba_acpi_dev *dev, u32 *mode)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_पढ़ो(dev, SCI_KBD_FUNCTION_KEYS, mode);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get KBD function keys failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस (result == TOS_SUCCESS || result == TOS_SUCCESS2) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_function_keys_set(काष्ठा toshiba_acpi_dev *dev, u32 mode)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_ग_लिखो(dev, SCI_KBD_FUNCTION_KEYS, mode);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set KBD function keys failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस (result == TOS_SUCCESS || result == TOS_SUCCESS2) ? 0 : -EIO;
पूर्ण

/* Panel Power ON */
अटल पूर्णांक toshiba_panel_घातer_on_get(काष्ठा toshiba_acpi_dev *dev, u32 *state)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_पढ़ो(dev, SCI_PANEL_POWER_ON, state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get Panel Power ON failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_panel_घातer_on_set(काष्ठा toshiba_acpi_dev *dev, u32 state)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_ग_लिखो(dev, SCI_PANEL_POWER_ON, state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set Panel Power ON failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

/* USB Three */
अटल पूर्णांक toshiba_usb_three_get(काष्ठा toshiba_acpi_dev *dev, u32 *state)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_पढ़ो(dev, SCI_USB_THREE, state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get USB 3 failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस (result == TOS_SUCCESS || result == TOS_SUCCESS2) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_usb_three_set(काष्ठा toshiba_acpi_dev *dev, u32 state)
अणु
	u32 result;

	अगर (!sci_खोलो(dev))
		वापस -EIO;

	result = sci_ग_लिखो(dev, SCI_USB_THREE, state);
	sci_बंद(dev);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set USB 3 failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस (result == TOS_SUCCESS || result == TOS_SUCCESS2) ? 0 : -EIO;
पूर्ण

/* Hotkey Event type */
अटल पूर्णांक toshiba_hotkey_event_type_get(काष्ठा toshiba_acpi_dev *dev,
					 u32 *type)
अणु
	u32 in[TCI_WORDS] = अणु HCI_GET, HCI_SYSTEM_INFO, 0x03, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get System type failed\n");
		वापस -EIO;
	पूर्ण

	अगर (out[0] == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	अगर (out[0] != TOS_SUCCESS)
		वापस -EIO;

	*type = out[3];

	वापस 0;
पूर्ण

/* Wireless status (RFKill, WLAN, BT, WWAN) */
अटल पूर्णांक toshiba_wireless_status(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु HCI_GET, HCI_WIRELESS, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	in[3] = HCI_WIRELESS_STATUS;
	status = tci_raw(dev, in, out);

	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get Wireless status failed\n");
		वापस -EIO;
	पूर्ण

	अगर (out[0] == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	अगर (out[0] != TOS_SUCCESS)
		वापस -EIO;

	dev->समाप्तचयन = !!(out[2] & HCI_WIRELESS_STATUS);

	वापस 0;
पूर्ण

/* WWAN */
अटल व्योम toshiba_wwan_available(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु HCI_GET, HCI_WIRELESS, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	dev->wwan_supported = 0;

	/*
	 * WWAN support can be queried by setting the in[3] value to
	 * HCI_WIRELESS_WWAN (0x03).
	 *
	 * If supported, out[0] contains TOS_SUCCESS and out[2] contains
	 * HCI_WIRELESS_WWAN_STATUS (0x2000).
	 *
	 * If not supported, out[0] contains TOS_INPUT_DATA_ERROR (0x8300)
	 * or TOS_NOT_SUPPORTED (0x8000).
	 */
	in[3] = HCI_WIRELESS_WWAN;
	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get WWAN status failed\n");
		वापस;
	पूर्ण

	अगर (out[0] != TOS_SUCCESS)
		वापस;

	dev->wwan_supported = (out[2] == HCI_WIRELESS_WWAN_STATUS);
पूर्ण

अटल पूर्णांक toshiba_wwan_set(काष्ठा toshiba_acpi_dev *dev, u32 state)
अणु
	u32 in[TCI_WORDS] = अणु HCI_SET, HCI_WIRELESS, state, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	in[3] = HCI_WIRELESS_WWAN_STATUS;
	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to set WWAN status failed\n");
		वापस -EIO;
	पूर्ण

	अगर (out[0] == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	अगर (out[0] != TOS_SUCCESS)
		वापस -EIO;

	/*
	 * Some devices only need to call HCI_WIRELESS_WWAN_STATUS to
	 * (de)activate the device, but some others need the
	 * HCI_WIRELESS_WWAN_POWER call as well.
	 */
	in[3] = HCI_WIRELESS_WWAN_POWER;
	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to set WWAN power failed\n");
		वापस -EIO;
	पूर्ण

	अगर (out[0] == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस out[0] == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

/* Cooling Method */
अटल व्योम toshiba_cooling_method_available(काष्ठा toshiba_acpi_dev *dev)
अणु
	u32 in[TCI_WORDS] = अणु HCI_GET, HCI_COOLING_METHOD, 0, 0, 0, 0 पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	dev->cooling_method_supported = 0;
	dev->max_cooling_method = 0;

	status = tci_raw(dev, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to get Cooling Method failed\n");
		वापस;
	पूर्ण

	अगर (out[0] != TOS_SUCCESS && out[0] != TOS_SUCCESS2)
		वापस;

	dev->cooling_method_supported = 1;
	dev->max_cooling_method = out[3];
पूर्ण

अटल पूर्णांक toshiba_cooling_method_get(काष्ठा toshiba_acpi_dev *dev, u32 *state)
अणु
	u32 result = hci_पढ़ो(dev, HCI_COOLING_METHOD, state);

	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get Cooling Method failed\n");

	अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस (result == TOS_SUCCESS || result == TOS_SUCCESS2) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक toshiba_cooling_method_set(काष्ठा toshiba_acpi_dev *dev, u32 state)
अणु
	u32 result = hci_ग_लिखो(dev, HCI_COOLING_METHOD, state);

	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set Cooling Method failed\n");

	अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस (result == TOS_SUCCESS || result == TOS_SUCCESS2) ? 0 : -EIO;
पूर्ण

/* Transflective Backlight */
अटल पूर्णांक get_tr_backlight_status(काष्ठा toshiba_acpi_dev *dev, u32 *status)
अणु
	u32 result = hci_पढ़ो(dev, HCI_TR_BACKLIGHT, status);

	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get Transflective Backlight failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक set_tr_backlight_status(काष्ठा toshiba_acpi_dev *dev, u32 status)
अणु
	u32 result = hci_ग_लिखो(dev, HCI_TR_BACKLIGHT, !status);

	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set Transflective Backlight failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल काष्ठा proc_dir_entry *toshiba_proc_dir;

/* LCD Brightness */
अटल पूर्णांक __get_lcd_brightness(काष्ठा toshiba_acpi_dev *dev)
अणु
	पूर्णांक brightness = 0;
	u32 result;
	u32 value;

	अगर (dev->tr_backlight_supported) अणु
		पूर्णांक ret = get_tr_backlight_status(dev, &value);

		अगर (ret)
			वापस ret;
		अगर (value)
			वापस 0;
		brightness++;
	पूर्ण

	result = hci_पढ़ो(dev, HCI_LCD_BRIGHTNESS, &value);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get LCD Brightness failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ?
			brightness + (value >> HCI_LCD_BRIGHTNESS_SHIFT) :
			-EIO;
पूर्ण

अटल पूर्णांक get_lcd_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा toshiba_acpi_dev *dev = bl_get_data(bd);

	वापस __get_lcd_brightness(dev);
पूर्ण

अटल पूर्णांक lcd_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा toshiba_acpi_dev *dev = m->निजी;
	पूर्णांक levels;
	पूर्णांक value;

	अगर (!dev->backlight_dev)
		वापस -ENODEV;

	levels = dev->backlight_dev->props.max_brightness + 1;
	value = get_lcd_brightness(dev->backlight_dev);
	अगर (value < 0) अणु
		pr_err("Error reading LCD brightness\n");
		वापस value;
	पूर्ण

	seq_म_लिखो(m, "brightness:              %d\n", value);
	seq_म_लिखो(m, "brightness_levels:       %d\n", levels);

	वापस 0;
पूर्ण

अटल पूर्णांक lcd_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, lcd_proc_show, PDE_DATA(inode));
पूर्ण

अटल पूर्णांक set_lcd_brightness(काष्ठा toshiba_acpi_dev *dev, पूर्णांक value)
अणु
	u32 result;

	अगर (dev->tr_backlight_supported) अणु
		पूर्णांक ret = set_tr_backlight_status(dev, !value);

		अगर (ret)
			वापस ret;
		अगर (value)
			value--;
	पूर्ण

	value = value << HCI_LCD_BRIGHTNESS_SHIFT;
	result = hci_ग_लिखो(dev, HCI_LCD_BRIGHTNESS, value);
	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set LCD Brightness failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक set_lcd_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा toshiba_acpi_dev *dev = bl_get_data(bd);

	वापस set_lcd_brightness(dev, bd->props.brightness);
पूर्ण

अटल sमाप_प्रकार lcd_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा toshiba_acpi_dev *dev = PDE_DATA(file_inode(file));
	अक्षर cmd[42];
	माप_प्रकार len;
	पूर्णांक levels;
	पूर्णांक value;

	len = min(count, माप(cmd) - 1);
	अगर (copy_from_user(cmd, buf, len))
		वापस -EFAULT;
	cmd[len] = '\0';

	levels = dev->backlight_dev->props.max_brightness + 1;
	अगर (माला_पूछो(cmd, " brightness : %i", &value) != 1 &&
	    value < 0 && value > levels)
		वापस -EINVAL;

	अगर (set_lcd_brightness(dev, value))
		वापस -EIO;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops lcd_proc_ops = अणु
	.proc_खोलो	= lcd_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= lcd_proc_ग_लिखो,
पूर्ण;

/* Video-Out */
अटल पूर्णांक get_video_status(काष्ठा toshiba_acpi_dev *dev, u32 *status)
अणु
	u32 result = hci_पढ़ो(dev, HCI_VIDEO_OUT, status);

	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get Video-Out failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक video_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा toshiba_acpi_dev *dev = m->निजी;
	पूर्णांक is_lcd, is_crt, is_tv;
	u32 value;

	अगर (get_video_status(dev, &value))
		वापस -EIO;

	is_lcd = (value & HCI_VIDEO_OUT_LCD) ? 1 : 0;
	is_crt = (value & HCI_VIDEO_OUT_CRT) ? 1 : 0;
	is_tv = (value & HCI_VIDEO_OUT_TV) ? 1 : 0;

	seq_म_लिखो(m, "lcd_out:                 %d\n", is_lcd);
	seq_म_लिखो(m, "crt_out:                 %d\n", is_crt);
	seq_म_लिखो(m, "tv_out:                  %d\n", is_tv);

	वापस 0;
पूर्ण

अटल पूर्णांक video_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, video_proc_show, PDE_DATA(inode));
पूर्ण

अटल sमाप_प्रकार video_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा toshiba_acpi_dev *dev = PDE_DATA(file_inode(file));
	अक्षर *buffer;
	अक्षर *cmd;
	पूर्णांक lcd_out = -1, crt_out = -1, tv_out = -1;
	पूर्णांक reमुख्य = count;
	पूर्णांक value;
	पूर्णांक ret;
	u32 video_out;

	cmd = memdup_user_nul(buf, count);
	अगर (IS_ERR(cmd))
		वापस PTR_ERR(cmd);

	buffer = cmd;

	/*
	 * Scan expression.  Multiple expressions may be delimited with ;
	 * NOTE: To keep scanning simple, invalid fields are ignored.
	 */
	जबतक (reमुख्य) अणु
		अगर (माला_पूछो(buffer, " lcd_out : %i", &value) == 1)
			lcd_out = value & 1;
		अन्यथा अगर (माला_पूछो(buffer, " crt_out : %i", &value) == 1)
			crt_out = value & 1;
		अन्यथा अगर (माला_पूछो(buffer, " tv_out : %i", &value) == 1)
			tv_out = value & 1;
		/* Advance to one अक्षरacter past the next ; */
		करो अणु
			++buffer;
			--reमुख्य;
		पूर्ण जबतक (reमुख्य && *(buffer - 1) != ';');
	पूर्ण

	kमुक्त(cmd);

	ret = get_video_status(dev, &video_out);
	अगर (!ret) अणु
		अचिन्हित पूर्णांक new_video_out = video_out;

		अगर (lcd_out != -1)
			_set_bit(&new_video_out, HCI_VIDEO_OUT_LCD, lcd_out);
		अगर (crt_out != -1)
			_set_bit(&new_video_out, HCI_VIDEO_OUT_CRT, crt_out);
		अगर (tv_out != -1)
			_set_bit(&new_video_out, HCI_VIDEO_OUT_TV, tv_out);
		/*
		 * To aव्योम unnecessary video disruption, only ग_लिखो the new
		 * video setting अगर something changed.
		 */
		अगर (new_video_out != video_out)
			ret = ग_लिखो_acpi_पूर्णांक(METHOD_VIDEO_OUT, new_video_out);
	पूर्ण

	वापस ret ? -EIO : count;
पूर्ण

अटल स्थिर काष्ठा proc_ops video_proc_ops = अणु
	.proc_खोलो	= video_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= video_proc_ग_लिखो,
पूर्ण;

/* Fan status */
अटल पूर्णांक get_fan_status(काष्ठा toshiba_acpi_dev *dev, u32 *status)
अणु
	u32 result = hci_पढ़ो(dev, HCI_FAN, status);

	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to get Fan status failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक set_fan_status(काष्ठा toshiba_acpi_dev *dev, u32 status)
अणु
	u32 result = hci_ग_लिखो(dev, HCI_FAN, status);

	अगर (result == TOS_FAILURE)
		pr_err("ACPI call to set Fan status failed\n");
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस result == TOS_SUCCESS ? 0 : -EIO;
पूर्ण

अटल पूर्णांक fan_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा toshiba_acpi_dev *dev = m->निजी;
	u32 value;

	अगर (get_fan_status(dev, &value))
		वापस -EIO;

	seq_म_लिखो(m, "running:                 %d\n", (value > 0));
	seq_म_लिखो(m, "force_on:                %d\n", dev->क्रमce_fan);

	वापस 0;
पूर्ण

अटल पूर्णांक fan_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, fan_proc_show, PDE_DATA(inode));
पूर्ण

अटल sमाप_प्रकार fan_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा toshiba_acpi_dev *dev = PDE_DATA(file_inode(file));
	अक्षर cmd[42];
	माप_प्रकार len;
	पूर्णांक value;

	len = min(count, माप(cmd) - 1);
	अगर (copy_from_user(cmd, buf, len))
		वापस -EFAULT;
	cmd[len] = '\0';

	अगर (माला_पूछो(cmd, " force_on : %i", &value) != 1 &&
	    value != 0 && value != 1)
		वापस -EINVAL;

	अगर (set_fan_status(dev, value))
		वापस -EIO;

	dev->क्रमce_fan = value;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops fan_proc_ops = अणु
	.proc_खोलो	= fan_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= fan_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक keys_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा toshiba_acpi_dev *dev = m->निजी;

	seq_म_लिखो(m, "hotkey_ready:            %d\n", dev->key_event_valid);
	seq_म_लिखो(m, "hotkey:                  0x%04x\n", dev->last_key_event);

	वापस 0;
पूर्ण

अटल पूर्णांक keys_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, keys_proc_show, PDE_DATA(inode));
पूर्ण

अटल sमाप_प्रकार keys_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा toshiba_acpi_dev *dev = PDE_DATA(file_inode(file));
	अक्षर cmd[42];
	माप_प्रकार len;
	पूर्णांक value;

	len = min(count, माप(cmd) - 1);
	अगर (copy_from_user(cmd, buf, len))
		वापस -EFAULT;
	cmd[len] = '\0';

	अगर (माला_पूछो(cmd, " hotkey_ready : %i", &value) == 1 && value == 0)
		dev->key_event_valid = 0;
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops keys_proc_ops = अणु
	.proc_खोलो	= keys_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= keys_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक __maybe_unused version_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "driver:                  %s\n", TOSHIBA_ACPI_VERSION);
	seq_म_लिखो(m, "proc_interface:          %d\n", PROC_INTERFACE_VERSION);
	वापस 0;
पूर्ण

/*
 * Proc and module init
 */

#घोषणा PROC_TOSHIBA		"toshiba"

अटल व्योम create_toshiba_proc_entries(काष्ठा toshiba_acpi_dev *dev)
अणु
	अगर (dev->backlight_dev)
		proc_create_data("lcd", S_IRUGO | S_IWUSR, toshiba_proc_dir,
				 &lcd_proc_ops, dev);
	अगर (dev->video_supported)
		proc_create_data("video", S_IRUGO | S_IWUSR, toshiba_proc_dir,
				 &video_proc_ops, dev);
	अगर (dev->fan_supported)
		proc_create_data("fan", S_IRUGO | S_IWUSR, toshiba_proc_dir,
				 &fan_proc_ops, dev);
	अगर (dev->hotkey_dev)
		proc_create_data("keys", S_IRUGO | S_IWUSR, toshiba_proc_dir,
				 &keys_proc_ops, dev);
	proc_create_single_data("version", S_IRUGO, toshiba_proc_dir,
			version_proc_show, dev);
पूर्ण

अटल व्योम हटाओ_toshiba_proc_entries(काष्ठा toshiba_acpi_dev *dev)
अणु
	अगर (dev->backlight_dev)
		हटाओ_proc_entry("lcd", toshiba_proc_dir);
	अगर (dev->video_supported)
		हटाओ_proc_entry("video", toshiba_proc_dir);
	अगर (dev->fan_supported)
		हटाओ_proc_entry("fan", toshiba_proc_dir);
	अगर (dev->hotkey_dev)
		हटाओ_proc_entry("keys", toshiba_proc_dir);
	हटाओ_proc_entry("version", toshiba_proc_dir);
पूर्ण

अटल स्थिर काष्ठा backlight_ops toshiba_backlight_data = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.get_brightness = get_lcd_brightness,
	.update_status  = set_lcd_status,
पूर्ण;

/* Keyboard backlight work */
अटल व्योम toshiba_acpi_kbd_bl_work(काष्ठा work_काष्ठा *work);

अटल DECLARE_WORK(kbd_bl_work, toshiba_acpi_kbd_bl_work);

/*
 * Sysfs files
 */
अटल sमाप_प्रकार version_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", TOSHIBA_ACPI_VERSION);
पूर्ण
अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार fan_store(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक state;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &state);
	अगर (ret)
		वापस ret;

	अगर (state != 0 && state != 1)
		वापस -EINVAL;

	ret = set_fan_status(toshiba, state);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 value;
	पूर्णांक ret;

	ret = get_fan_status(toshiba, &value);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण
अटल DEVICE_ATTR_RW(fan);

अटल sमाप_प्रकार kbd_backlight_mode_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक mode;
	पूर्णांक ret;


	ret = kstrtoपूर्णांक(buf, 0, &mode);
	अगर (ret)
		वापस ret;

	/* Check क्रम supported modes depending on keyboard backlight type */
	अगर (toshiba->kbd_type == 1) अणु
		/* Type 1 supports SCI_KBD_MODE_FNZ and SCI_KBD_MODE_AUTO */
		अगर (mode != SCI_KBD_MODE_FNZ && mode != SCI_KBD_MODE_AUTO)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (toshiba->kbd_type == 2) अणु
		/* Type 2 करोesn't support SCI_KBD_MODE_FNZ */
		अगर (mode != SCI_KBD_MODE_AUTO && mode != SCI_KBD_MODE_ON &&
		    mode != SCI_KBD_MODE_OFF)
			वापस -EINVAL;
	पूर्ण

	/*
	 * Set the Keyboard Backlight Mode where:
	 *	Auto - KBD backlight turns off स्वतःmatically in given समय
	 *	FN-Z - KBD backlight "toggles" when hotkey pressed
	 *	ON   - KBD backlight is always on
	 *	OFF  - KBD backlight is always off
	 */

	/* Only make a change अगर the actual mode has changed */
	अगर (toshiba->kbd_mode != mode) अणु
		/* Shअगरt the समय to "base time" (0x3c0000 == 60 seconds) */
		पूर्णांक समय = toshiba->kbd_समय << HCI_MISC_SHIFT;

		/* OR the "base time" to the actual method क्रमmat */
		अगर (toshiba->kbd_type == 1) अणु
			/* Type 1 requires the current mode */
			समय |= toshiba->kbd_mode;
		पूर्ण अन्यथा अगर (toshiba->kbd_type == 2) अणु
			/* Type 2 requires the desired mode */
			समय |= mode;
		पूर्ण

		ret = toshiba_kbd_illum_status_set(toshiba, समय);
		अगर (ret)
			वापस ret;

		toshiba->kbd_mode = mode;
		toshiba_acpi->kbd_mode = mode;

		/*
		 * Some laptop models with the second generation backlit
		 * keyboard (type 2) करो not generate the keyboard backlight
		 * changed event (0x92), and thus, the driver will never update
		 * the sysfs entries.
		 *
		 * The event is generated right when changing the keyboard
		 * backlight mode and the *notअगरy function will set the
		 * kbd_event_generated to true.
		 *
		 * In हाल the event is not generated, schedule the keyboard
		 * backlight work to update the sysfs entries and emulate the
		 * event via genetlink.
		 */
		अगर (toshiba->kbd_type == 2 &&
		    !toshiba->kbd_event_generated)
			schedule_work(&kbd_bl_work);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार kbd_backlight_mode_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 समय;

	अगर (toshiba_kbd_illum_status_get(toshiba, &समय) < 0)
		वापस -EIO;

	वापस प्र_लिखो(buf, "%i\n", समय & SCI_KBD_MODE_MASK);
पूर्ण
अटल DEVICE_ATTR_RW(kbd_backlight_mode);

अटल sमाप_प्रकार kbd_type_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", toshiba->kbd_type);
पूर्ण
अटल DEVICE_ATTR_RO(kbd_type);

अटल sमाप_प्रकार available_kbd_modes_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);

	अगर (toshiba->kbd_type == 1)
		वापस प्र_लिखो(buf, "0x%x 0x%x\n",
			       SCI_KBD_MODE_FNZ, SCI_KBD_MODE_AUTO);

	वापस प्र_लिखो(buf, "0x%x 0x%x 0x%x\n",
		       SCI_KBD_MODE_AUTO, SCI_KBD_MODE_ON, SCI_KBD_MODE_OFF);
पूर्ण
अटल DEVICE_ATTR_RO(available_kbd_modes);

अटल sमाप_प्रकार kbd_backlight_समयout_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक समय;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &समय);
	अगर (ret)
		वापस ret;

	/* Check क्रम supported values depending on kbd_type */
	अगर (toshiba->kbd_type == 1) अणु
		अगर (समय < 0 || समय > 60)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (toshiba->kbd_type == 2) अणु
		अगर (समय < 1 || समय > 60)
			वापस -EINVAL;
	पूर्ण

	/* Set the Keyboard Backlight Timeout */

	/* Only make a change अगर the actual समयout has changed */
	अगर (toshiba->kbd_समय != समय) अणु
		/* Shअगरt the समय to "base time" (0x3c0000 == 60 seconds) */
		समय = समय << HCI_MISC_SHIFT;
		/* OR the "base time" to the actual method क्रमmat */
		अगर (toshiba->kbd_type == 1)
			समय |= SCI_KBD_MODE_FNZ;
		अन्यथा अगर (toshiba->kbd_type == 2)
			समय |= SCI_KBD_MODE_AUTO;

		ret = toshiba_kbd_illum_status_set(toshiba, समय);
		अगर (ret)
			वापस ret;

		toshiba->kbd_समय = समय >> HCI_MISC_SHIFT;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार kbd_backlight_समयout_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 समय;

	अगर (toshiba_kbd_illum_status_get(toshiba, &समय) < 0)
		वापस -EIO;

	वापस प्र_लिखो(buf, "%i\n", समय >> HCI_MISC_SHIFT);
पूर्ण
अटल DEVICE_ATTR_RW(kbd_backlight_समयout);

अटल sमाप_प्रकार touchpad_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक state;
	पूर्णांक ret;

	/* Set the TouchPad on/off, 0 - Disable | 1 - Enable */
	ret = kstrtoपूर्णांक(buf, 0, &state);
	अगर (ret)
		वापस ret;
	अगर (state != 0 && state != 1)
		वापस -EINVAL;

	ret = toshiba_touchpad_set(toshiba, state);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार touchpad_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 state;
	पूर्णांक ret;

	ret = toshiba_touchpad_get(toshiba, &state);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%i\n", state);
पूर्ण
अटल DEVICE_ATTR_RW(touchpad);

अटल sमाप_प्रकार usb_sleep_अक्षरge_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 mode;
	पूर्णांक ret;

	ret = toshiba_usb_sleep_अक्षरge_get(toshiba, &mode);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%x\n", mode & SCI_USB_CHARGE_MODE_MASK);
पूर्ण

अटल sमाप_प्रकार usb_sleep_अक्षरge_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक state;
	u32 mode;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &state);
	अगर (ret)
		वापस ret;
	/*
	 * Check क्रम supported values, where:
	 * 0 - Disabled
	 * 1 - Alternate (Non USB conक्रमmant devices that require more घातer)
	 * 2 - Auto (USB conक्रमmant devices)
	 * 3 - Typical
	 */
	अगर (state != 0 && state != 1 && state != 2 && state != 3)
		वापस -EINVAL;

	/* Set the USB अक्षरging mode to पूर्णांकernal value */
	mode = toshiba->usbsc_mode_base;
	अगर (state == 0)
		mode |= SCI_USB_CHARGE_DISABLED;
	अन्यथा अगर (state == 1)
		mode |= SCI_USB_CHARGE_ALTERNATE;
	अन्यथा अगर (state == 2)
		mode |= SCI_USB_CHARGE_AUTO;
	अन्यथा अगर (state == 3)
		mode |= SCI_USB_CHARGE_TYPICAL;

	ret = toshiba_usb_sleep_अक्षरge_set(toshiba, mode);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(usb_sleep_अक्षरge);

अटल sमाप_प्रकार sleep_functions_on_battery_show(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक bat_lvl, status;
	u32 state;
	पूर्णांक ret;
	पूर्णांक पंचांगp;

	ret = toshiba_sleep_functions_status_get(toshiba, &state);
	अगर (ret < 0)
		वापस ret;

	/* Determine the status: 0x4 - Enabled | 0x1 - Disabled */
	पंचांगp = state & SCI_USB_CHARGE_BAT_MASK;
	status = (पंचांगp == 0x4) ? 1 : 0;
	/* Determine the battery level set */
	bat_lvl = state >> HCI_MISC_SHIFT;

	वापस प्र_लिखो(buf, "%d %d\n", status, bat_lvl);
पूर्ण

अटल sमाप_प्रकार sleep_functions_on_battery_store(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 status;
	पूर्णांक value;
	पूर्णांक ret;
	पूर्णांक पंचांगp;

	ret = kstrtoपूर्णांक(buf, 0, &value);
	अगर (ret)
		वापस ret;

	/*
	 * Set the status of the function:
	 * 0 - Disabled
	 * 1-100 - Enabled
	 */
	अगर (value < 0 || value > 100)
		वापस -EINVAL;

	अगर (value == 0) अणु
		पंचांगp = toshiba->usbsc_bat_level << HCI_MISC_SHIFT;
		status = पंचांगp | SCI_USB_CHARGE_BAT_LVL_OFF;
	पूर्ण अन्यथा अणु
		पंचांगp = value << HCI_MISC_SHIFT;
		status = पंचांगp | SCI_USB_CHARGE_BAT_LVL_ON;
	पूर्ण
	ret = toshiba_sleep_functions_status_set(toshiba, status);
	अगर (ret < 0)
		वापस ret;

	toshiba->usbsc_bat_level = status >> HCI_MISC_SHIFT;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(sleep_functions_on_battery);

अटल sमाप_प्रकार usb_rapid_अक्षरge_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 state;
	पूर्णांक ret;

	ret = toshiba_usb_rapid_अक्षरge_get(toshiba, &state);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", state);
पूर्ण

अटल sमाप_प्रकार usb_rapid_अक्षरge_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक state;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &state);
	अगर (ret)
		वापस ret;
	अगर (state != 0 && state != 1)
		वापस -EINVAL;

	ret = toshiba_usb_rapid_अक्षरge_set(toshiba, state);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(usb_rapid_अक्षरge);

अटल sमाप_प्रकार usb_sleep_music_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 state;
	पूर्णांक ret;

	ret = toshiba_usb_sleep_music_get(toshiba, &state);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", state);
पूर्ण

अटल sमाप_प्रकार usb_sleep_music_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक state;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &state);
	अगर (ret)
		वापस ret;
	अगर (state != 0 && state != 1)
		वापस -EINVAL;

	ret = toshiba_usb_sleep_music_set(toshiba, state);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(usb_sleep_music);

अटल sमाप_प्रकार kbd_function_keys_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक mode;
	पूर्णांक ret;

	ret = toshiba_function_keys_get(toshiba, &mode);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", mode);
पूर्ण

अटल sमाप_प्रकार kbd_function_keys_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक mode;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &mode);
	अगर (ret)
		वापस ret;
	/*
	 * Check क्रम the function keys mode where:
	 * 0 - Normal operation (Fअणु1-12पूर्ण as usual and hotkeys via FN-Fअणु1-12पूर्ण)
	 * 1 - Special functions (Opposite of the above setting)
	 */
	अगर (mode != 0 && mode != 1)
		वापस -EINVAL;

	ret = toshiba_function_keys_set(toshiba, mode);
	अगर (ret)
		वापस ret;

	pr_info("Reboot for changes to KBD Function Keys to take effect");

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(kbd_function_keys);

अटल sमाप_प्रकार panel_घातer_on_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 state;
	पूर्णांक ret;

	ret = toshiba_panel_घातer_on_get(toshiba, &state);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", state);
पूर्ण

अटल sमाप_प्रकार panel_घातer_on_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक state;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &state);
	अगर (ret)
		वापस ret;
	अगर (state != 0 && state != 1)
		वापस -EINVAL;

	ret = toshiba_panel_घातer_on_set(toshiba, state);
	अगर (ret)
		वापस ret;

	pr_info("Reboot for changes to Panel Power ON to take effect");

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(panel_घातer_on);

अटल sमाप_प्रकार usb_three_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	u32 state;
	पूर्णांक ret;

	ret = toshiba_usb_three_get(toshiba, &state);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", state);
पूर्ण

अटल sमाप_प्रकार usb_three_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक state;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &state);
	अगर (ret)
		वापस ret;
	/*
	 * Check क्रम USB 3 mode where:
	 * 0 - Disabled (Acts like a USB 2 port, saving घातer)
	 * 1 - Enabled
	 */
	अगर (state != 0 && state != 1)
		वापस -EINVAL;

	ret = toshiba_usb_three_set(toshiba, state);
	अगर (ret)
		वापस ret;

	pr_info("Reboot for changes to USB 3 to take effect");

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(usb_three);

अटल sमाप_प्रकार cooling_method_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक state;
	पूर्णांक ret;

	ret = toshiba_cooling_method_get(toshiba, &state);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d %d\n", state, toshiba->max_cooling_method);
पूर्ण

अटल sमाप_प्रकार cooling_method_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	पूर्णांक state;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &state);
	अगर (ret)
		वापस ret;

	/*
	 * Check क्रम supported values
	 * Depending on the laptop model, some only support these two:
	 * 0 - Maximum Perक्रमmance
	 * 1 - Battery Optimized
	 *
	 * While some others support all three methods:
	 * 0 - Maximum Perक्रमmance
	 * 1 - Perक्रमmance
	 * 2 - Battery Optimized
	 */
	अगर (state < 0 || state > toshiba->max_cooling_method)
		वापस -EINVAL;

	ret = toshiba_cooling_method_set(toshiba, state);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(cooling_method);

अटल काष्ठा attribute *toshiba_attributes[] = अणु
	&dev_attr_version.attr,
	&dev_attr_fan.attr,
	&dev_attr_kbd_backlight_mode.attr,
	&dev_attr_kbd_type.attr,
	&dev_attr_available_kbd_modes.attr,
	&dev_attr_kbd_backlight_समयout.attr,
	&dev_attr_touchpad.attr,
	&dev_attr_usb_sleep_अक्षरge.attr,
	&dev_attr_sleep_functions_on_battery.attr,
	&dev_attr_usb_rapid_अक्षरge.attr,
	&dev_attr_usb_sleep_music.attr,
	&dev_attr_kbd_function_keys.attr,
	&dev_attr_panel_घातer_on.attr,
	&dev_attr_usb_three.attr,
	&dev_attr_cooling_method.attr,
	शून्य,
पूर्ण;

अटल umode_t toshiba_sysfs_is_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा toshiba_acpi_dev *drv = dev_get_drvdata(dev);
	bool exists = true;

	अगर (attr == &dev_attr_fan.attr)
		exists = (drv->fan_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_kbd_backlight_mode.attr)
		exists = (drv->kbd_illum_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_kbd_backlight_समयout.attr)
		exists = (drv->kbd_mode == SCI_KBD_MODE_AUTO) ? true : false;
	अन्यथा अगर (attr == &dev_attr_touchpad.attr)
		exists = (drv->touchpad_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_usb_sleep_अक्षरge.attr)
		exists = (drv->usb_sleep_अक्षरge_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_sleep_functions_on_battery.attr)
		exists = (drv->usb_sleep_अक्षरge_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_usb_rapid_अक्षरge.attr)
		exists = (drv->usb_rapid_अक्षरge_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_usb_sleep_music.attr)
		exists = (drv->usb_sleep_music_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_kbd_function_keys.attr)
		exists = (drv->kbd_function_keys_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_panel_घातer_on.attr)
		exists = (drv->panel_घातer_on_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_usb_three.attr)
		exists = (drv->usb_three_supported) ? true : false;
	अन्यथा अगर (attr == &dev_attr_cooling_method.attr)
		exists = (drv->cooling_method_supported) ? true : false;

	वापस exists ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group toshiba_attr_group = अणु
	.is_visible = toshiba_sysfs_is_visible,
	.attrs = toshiba_attributes,
पूर्ण;

अटल व्योम toshiba_acpi_kbd_bl_work(काष्ठा work_काष्ठा *work)
अणु
	/* Update the sysfs entries */
	अगर (sysfs_update_group(&toshiba_acpi->acpi_dev->dev.kobj,
			       &toshiba_attr_group))
		pr_err("Unable to update sysfs entries\n");

	/* Notअगरy LED subप्रणाली about keyboard backlight change */
	अगर (toshiba_acpi->kbd_type == 2 &&
	    toshiba_acpi->kbd_mode != SCI_KBD_MODE_AUTO)
		led_classdev_notअगरy_brightness_hw_changed(&toshiba_acpi->kbd_led,
				(toshiba_acpi->kbd_mode == SCI_KBD_MODE_ON) ?
				LED_FULL : LED_OFF);

	/* Emulate the keyboard backlight event */
	acpi_bus_generate_netlink_event(toshiba_acpi->acpi_dev->pnp.device_class,
					dev_name(&toshiba_acpi->acpi_dev->dev),
					0x92, 0);
पूर्ण

/*
 * IIO device
 */

क्रमागत toshiba_iio_accel_chan अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z
पूर्ण;

अटल पूर्णांक toshiba_iio_accel_get_axis(क्रमागत toshiba_iio_accel_chan chan)
अणु
	u32 xyval, zval;
	पूर्णांक ret;

	ret = toshiba_accelerometer_get(toshiba_acpi, &xyval, &zval);
	अगर (ret < 0)
		वापस ret;

	चयन (chan) अणु
	हाल AXIS_X:
		वापस xyval & HCI_ACCEL_सूचीECTION_MASK ?
			-(xyval & HCI_ACCEL_MASK) : xyval & HCI_ACCEL_MASK;
	हाल AXIS_Y:
		वापस (xyval >> HCI_MISC_SHIFT) & HCI_ACCEL_सूचीECTION_MASK ?
			-((xyval >> HCI_MISC_SHIFT) & HCI_ACCEL_MASK) :
			(xyval >> HCI_MISC_SHIFT) & HCI_ACCEL_MASK;
	हाल AXIS_Z:
		वापस zval & HCI_ACCEL_सूचीECTION_MASK ?
			-(zval & HCI_ACCEL_MASK) : zval & HCI_ACCEL_MASK;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक toshiba_iio_accel_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = toshiba_iio_accel_get_axis(chan->channel);
		अगर (ret == -EIO || ret == -ENODEV)
			वापस ret;

		*val = ret;

		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

#घोषणा TOSHIBA_IIO_ACCEL_CHANNEL(axis, chan) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.channel = chan, \
	.channel2 = IIO_MOD_##axis, \
	.output = 1, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec toshiba_iio_accel_channels[] = अणु
	TOSHIBA_IIO_ACCEL_CHANNEL(X, AXIS_X),
	TOSHIBA_IIO_ACCEL_CHANNEL(Y, AXIS_Y),
	TOSHIBA_IIO_ACCEL_CHANNEL(Z, AXIS_Z),
पूर्ण;

अटल स्थिर काष्ठा iio_info toshiba_iio_accel_info = अणु
	.पढ़ो_raw = &toshiba_iio_accel_पढ़ो_raw,
पूर्ण;

/*
 * Misc device
 */
अटल पूर्णांक toshiba_acpi_smm_bridge(SMMRegisters *regs)
अणु
	u32 in[TCI_WORDS] = अणु regs->eax, regs->ebx, regs->ecx,
			      regs->edx, regs->esi, regs->edi पूर्ण;
	u32 out[TCI_WORDS];
	acpi_status status;

	status = tci_raw(toshiba_acpi, in, out);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI call to query SMM registers failed\n");
		वापस -EIO;
	पूर्ण

	/* Fillout the SMM काष्ठा with the TCI call results */
	regs->eax = out[0];
	regs->ebx = out[1];
	regs->ecx = out[2];
	regs->edx = out[3];
	regs->esi = out[4];
	regs->edi = out[5];

	वापस 0;
पूर्ण

अटल दीर्घ toshiba_acpi_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	SMMRegisters __user *argp = (SMMRegisters __user *)arg;
	SMMRegisters regs;
	पूर्णांक ret;

	अगर (!argp)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल TOSH_SMM:
		अगर (copy_from_user(&regs, argp, माप(SMMRegisters)))
			वापस -EFAULT;
		ret = toshiba_acpi_smm_bridge(&regs);
		अगर (ret)
			वापस ret;
		अगर (copy_to_user(argp, &regs, माप(SMMRegisters)))
			वापस -EFAULT;
		अवरोध;
	हाल TOSHIBA_ACPI_SCI:
		अगर (copy_from_user(&regs, argp, माप(SMMRegisters)))
			वापस -EFAULT;
		/* Ensure we are being called with a SCI_अणुGET, SETपूर्ण रेजिस्टर */
		अगर (regs.eax != SCI_GET && regs.eax != SCI_SET)
			वापस -EINVAL;
		अगर (!sci_खोलो(toshiba_acpi))
			वापस -EIO;
		ret = toshiba_acpi_smm_bridge(&regs);
		sci_बंद(toshiba_acpi);
		अगर (ret)
			वापस ret;
		अगर (copy_to_user(argp, &regs, माप(SMMRegisters)))
			वापस -EFAULT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations toshiba_acpi_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl = toshiba_acpi_ioctl,
	.llseek		= noop_llseek,
पूर्ण;

/*
 * WWAN RFKill handlers
 */
अटल पूर्णांक toshiba_acpi_wwan_set_block(व्योम *data, bool blocked)
अणु
	काष्ठा toshiba_acpi_dev *dev = data;
	पूर्णांक ret;

	ret = toshiba_wireless_status(dev);
	अगर (ret)
		वापस ret;

	अगर (!dev->समाप्तचयन)
		वापस 0;

	वापस toshiba_wwan_set(dev, !blocked);
पूर्ण

अटल व्योम toshiba_acpi_wwan_poll(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data)
अणु
	काष्ठा toshiba_acpi_dev *dev = data;

	अगर (toshiba_wireless_status(dev))
		वापस;

	rfसमाप्त_set_hw_state(dev->wwan_rfk, !dev->समाप्तचयन);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops wwan_rfk_ops = अणु
	.set_block = toshiba_acpi_wwan_set_block,
	.poll = toshiba_acpi_wwan_poll,
पूर्ण;

अटल पूर्णांक toshiba_acpi_setup_wwan_rfसमाप्त(काष्ठा toshiba_acpi_dev *dev)
अणु
	पूर्णांक ret = toshiba_wireless_status(dev);

	अगर (ret)
		वापस ret;

	dev->wwan_rfk = rfसमाप्त_alloc("Toshiba WWAN",
				     &dev->acpi_dev->dev,
				     RFKILL_TYPE_WWAN,
				     &wwan_rfk_ops,
				     dev);
	अगर (!dev->wwan_rfk) अणु
		pr_err("Unable to allocate WWAN rfkill device\n");
		वापस -ENOMEM;
	पूर्ण

	rfसमाप्त_set_hw_state(dev->wwan_rfk, !dev->समाप्तचयन);

	ret = rfसमाप्त_रेजिस्टर(dev->wwan_rfk);
	अगर (ret) अणु
		pr_err("Unable to register WWAN rfkill device\n");
		rfसमाप्त_destroy(dev->wwan_rfk);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Hotkeys
 */
अटल पूर्णांक toshiba_acpi_enable_hotkeys(काष्ठा toshiba_acpi_dev *dev)
अणु
	acpi_status status;
	u32 result;

	status = acpi_evaluate_object(dev->acpi_dev->handle,
				      "ENAB", शून्य, शून्य);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	/*
	 * Enable the "Special Functions" mode only अगर they are
	 * supported and अगर they are activated.
	 */
	अगर (dev->kbd_function_keys_supported && dev->special_functions)
		result = hci_ग_लिखो(dev, HCI_HOTKEY_EVENT,
				   HCI_HOTKEY_SPECIAL_FUNCTIONS);
	अन्यथा
		result = hci_ग_लिखो(dev, HCI_HOTKEY_EVENT, HCI_HOTKEY_ENABLE);

	अगर (result == TOS_FAILURE)
		वापस -EIO;
	अन्यथा अगर (result == TOS_NOT_SUPPORTED)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल bool toshiba_acpi_i8042_filter(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
				      काष्ठा serio *port)
अणु
	अगर (str & I8042_STR_AUXDATA)
		वापस false;

	अगर (unlikely(data == 0xe0))
		वापस false;

	अगर ((data & 0x7f) == TOS1900_FN_SCAN) अणु
		schedule_work(&toshiba_acpi->hotkey_work);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम toshiba_acpi_hotkey_work(काष्ठा work_काष्ठा *work)
अणु
	acpi_handle ec_handle = ec_get_handle();
	acpi_status status;

	अगर (!ec_handle)
		वापस;

	status = acpi_evaluate_object(ec_handle, "NTFY", शून्य, शून्य);
	अगर (ACPI_FAILURE(status))
		pr_err("ACPI NTFY method execution failed\n");
पूर्ण

/*
 * Returns hotkey scancode, or < 0 on failure.
 */
अटल पूर्णांक toshiba_acpi_query_hotkey(काष्ठा toshiba_acpi_dev *dev)
अणु
	अचिन्हित दीर्घ दीर्घ value;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(dev->acpi_dev->handle, "INFO",
				      शून्य, &value);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("ACPI INFO method execution failed\n");
		वापस -EIO;
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम toshiba_acpi_report_hotkey(काष्ठा toshiba_acpi_dev *dev,
				       पूर्णांक scancode)
अणु
	अगर (scancode == 0x100)
		वापस;

	/* Act on key press; ignore key release */
	अगर (scancode & 0x80)
		वापस;

	अगर (!sparse_keymap_report_event(dev->hotkey_dev, scancode, 1, true))
		pr_info("Unknown key %x\n", scancode);
पूर्ण

अटल व्योम toshiba_acpi_process_hotkeys(काष्ठा toshiba_acpi_dev *dev)
अणु
	अगर (dev->info_supported) अणु
		पूर्णांक scancode = toshiba_acpi_query_hotkey(dev);

		अगर (scancode < 0) अणु
			pr_err("Failed to query hotkey event\n");
		पूर्ण अन्यथा अगर (scancode != 0) अणु
			toshiba_acpi_report_hotkey(dev, scancode);
			dev->key_event_valid = 1;
			dev->last_key_event = scancode;
		पूर्ण
	पूर्ण अन्यथा अगर (dev->प्रणाली_event_supported) अणु
		u32 result;
		u32 value;
		पूर्णांक retries = 3;

		करो अणु
			result = hci_पढ़ो(dev, HCI_SYSTEM_EVENT, &value);
			चयन (result) अणु
			हाल TOS_SUCCESS:
				toshiba_acpi_report_hotkey(dev, (पूर्णांक)value);
				dev->key_event_valid = 1;
				dev->last_key_event = value;
				अवरोध;
			हाल TOS_NOT_SUPPORTED:
				/*
				 * This is a workaround क्रम an unresolved
				 * issue on some machines where प्रणाली events
				 * sporadically become disabled.
				 */
				result = hci_ग_लिखो(dev, HCI_SYSTEM_EVENT, 1);
				अगर (result == TOS_SUCCESS)
					pr_notice("Re-enabled hotkeys\n");
				fallthrough;
			शेष:
				retries--;
				अवरोध;
			पूर्ण
		पूर्ण जबतक (retries && result != TOS_FIFO_EMPTY);
	पूर्ण
पूर्ण

अटल पूर्णांक toshiba_acpi_setup_keyboard(काष्ठा toshiba_acpi_dev *dev)
अणु
	स्थिर काष्ठा key_entry *keymap = toshiba_acpi_keymap;
	acpi_handle ec_handle;
	पूर्णांक error;

	अगर (disable_hotkeys) अणु
		pr_info("Hotkeys disabled by module parameter\n");
		वापस 0;
	पूर्ण

	अगर (wmi_has_guid(TOSHIBA_WMI_EVENT_GUID)) अणु
		pr_info("WMI event detected, hotkeys will not be monitored\n");
		वापस 0;
	पूर्ण

	error = toshiba_acpi_enable_hotkeys(dev);
	अगर (error)
		वापस error;

	अगर (toshiba_hotkey_event_type_get(dev, &dev->hotkey_event_type))
		pr_notice("Unable to query Hotkey Event Type\n");

	dev->hotkey_dev = input_allocate_device();
	अगर (!dev->hotkey_dev)
		वापस -ENOMEM;

	dev->hotkey_dev->name = "Toshiba input device";
	dev->hotkey_dev->phys = "toshiba_acpi/input0";
	dev->hotkey_dev->id.bustype = BUS_HOST;

	अगर (dev->hotkey_event_type == HCI_SYSTEM_TYPE1 ||
	    !dev->kbd_function_keys_supported)
		keymap = toshiba_acpi_keymap;
	अन्यथा अगर (dev->hotkey_event_type == HCI_SYSTEM_TYPE2 ||
		 dev->kbd_function_keys_supported)
		keymap = toshiba_acpi_alt_keymap;
	अन्यथा
		pr_info("Unknown event type received %x\n",
			dev->hotkey_event_type);
	error = sparse_keymap_setup(dev->hotkey_dev, keymap, शून्य);
	अगर (error)
		जाओ err_मुक्त_dev;

	/*
	 * For some machines the SCI responsible क्रम providing hotkey
	 * notअगरication करोesn't fire. We can trigger the notअगरication
	 * whenever the Fn key is pressed using the NTFY method, अगर
	 * supported, so अगर it's present set up an i8042 key filter
	 * क्रम this purpose.
	 */
	ec_handle = ec_get_handle();
	अगर (ec_handle && acpi_has_method(ec_handle, "NTFY")) अणु
		INIT_WORK(&dev->hotkey_work, toshiba_acpi_hotkey_work);

		error = i8042_install_filter(toshiba_acpi_i8042_filter);
		अगर (error) अणु
			pr_err("Error installing key filter\n");
			जाओ err_मुक्त_dev;
		पूर्ण

		dev->ntfy_supported = 1;
	पूर्ण

	/*
	 * Determine hotkey query पूर्णांकerface. Prefer using the INFO
	 * method when it is available.
	 */
	अगर (acpi_has_method(dev->acpi_dev->handle, "INFO"))
		dev->info_supported = 1;
	अन्यथा अगर (hci_ग_लिखो(dev, HCI_SYSTEM_EVENT, 1) == TOS_SUCCESS)
		dev->प्रणाली_event_supported = 1;

	अगर (!dev->info_supported && !dev->प्रणाली_event_supported) अणु
		pr_warn("No hotkey query interface found\n");
		जाओ err_हटाओ_filter;
	पूर्ण

	error = input_रेजिस्टर_device(dev->hotkey_dev);
	अगर (error) अणु
		pr_info("Unable to register input device\n");
		जाओ err_हटाओ_filter;
	पूर्ण

	वापस 0;

 err_हटाओ_filter:
	अगर (dev->ntfy_supported)
		i8042_हटाओ_filter(toshiba_acpi_i8042_filter);
 err_मुक्त_dev:
	input_मुक्त_device(dev->hotkey_dev);
	dev->hotkey_dev = शून्य;
	वापस error;
पूर्ण

अटल पूर्णांक toshiba_acpi_setup_backlight(काष्ठा toshiba_acpi_dev *dev)
अणु
	काष्ठा backlight_properties props;
	पूर्णांक brightness;
	पूर्णांक ret;

	/*
	 * Some machines करोn't support the backlight methods at all, and
	 * others support it पढ़ो-only. Either of these is pretty useless,
	 * so only रेजिस्टर the backlight device अगर the backlight method
	 * supports both पढ़ोs and ग_लिखोs.
	 */
	brightness = __get_lcd_brightness(dev);
	अगर (brightness < 0)
		वापस 0;
	/*
	 * If transflective backlight is supported and the brightness is zero
	 * (lowest brightness level), the set_lcd_brightness function will
	 * activate the transflective backlight, making the LCD appear to be
	 * turned off, simply increment the brightness level to aव्योम that.
	 */
	अगर (dev->tr_backlight_supported && brightness == 0)
		brightness++;
	ret = set_lcd_brightness(dev, brightness);
	अगर (ret) अणु
		pr_debug("Backlight method is read-only, disabling backlight support\n");
		वापस 0;
	पूर्ण

	/*
	 * Tell acpi-video-detect code to prefer venकरोr backlight on all
	 * प्रणालीs with transflective backlight and on dmi matched प्रणालीs.
	 */
	अगर (dev->tr_backlight_supported ||
	    dmi_check_प्रणाली(toshiba_venकरोr_backlight_dmi))
		acpi_video_set_dmi_backlight_type(acpi_backlight_venकरोr);

	अगर (acpi_video_get_backlight_type() != acpi_backlight_venकरोr)
		वापस 0;

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = HCI_LCD_BRIGHTNESS_LEVELS - 1;

	/* Adding an extra level and having 0 change to transflective mode */
	अगर (dev->tr_backlight_supported)
		props.max_brightness++;

	dev->backlight_dev = backlight_device_रेजिस्टर("toshiba",
						       &dev->acpi_dev->dev,
						       dev,
						       &toshiba_backlight_data,
						       &props);
	अगर (IS_ERR(dev->backlight_dev)) अणु
		ret = PTR_ERR(dev->backlight_dev);
		pr_err("Could not register toshiba backlight device\n");
		dev->backlight_dev = शून्य;
		वापस ret;
	पूर्ण

	dev->backlight_dev->props.brightness = brightness;
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_supported_features(काष्ठा toshiba_acpi_dev *dev)
अणु
	pr_info("Supported laptop features:");

	अगर (dev->hotkey_dev)
		pr_cont(" hotkeys");
	अगर (dev->backlight_dev)
		pr_cont(" backlight");
	अगर (dev->video_supported)
		pr_cont(" video-out");
	अगर (dev->fan_supported)
		pr_cont(" fan");
	अगर (dev->tr_backlight_supported)
		pr_cont(" transflective-backlight");
	अगर (dev->illumination_supported)
		pr_cont(" illumination");
	अगर (dev->kbd_illum_supported)
		pr_cont(" keyboard-backlight");
	अगर (dev->touchpad_supported)
		pr_cont(" touchpad");
	अगर (dev->eco_supported)
		pr_cont(" eco-led");
	अगर (dev->accelerometer_supported)
		pr_cont(" accelerometer-axes");
	अगर (dev->usb_sleep_अक्षरge_supported)
		pr_cont(" usb-sleep-charge");
	अगर (dev->usb_rapid_अक्षरge_supported)
		pr_cont(" usb-rapid-charge");
	अगर (dev->usb_sleep_music_supported)
		pr_cont(" usb-sleep-music");
	अगर (dev->kbd_function_keys_supported)
		pr_cont(" special-function-keys");
	अगर (dev->panel_घातer_on_supported)
		pr_cont(" panel-power-on");
	अगर (dev->usb_three_supported)
		pr_cont(" usb3");
	अगर (dev->wwan_supported)
		pr_cont(" wwan");
	अगर (dev->cooling_method_supported)
		pr_cont(" cooling-method");

	pr_cont("\n");
पूर्ण

अटल पूर्णांक toshiba_acpi_हटाओ(काष्ठा acpi_device *acpi_dev)
अणु
	काष्ठा toshiba_acpi_dev *dev = acpi_driver_data(acpi_dev);

	misc_deरेजिस्टर(&dev->miscdev);

	हटाओ_toshiba_proc_entries(dev);

	अगर (dev->accelerometer_supported && dev->indio_dev) अणु
		iio_device_unरेजिस्टर(dev->indio_dev);
		iio_device_मुक्त(dev->indio_dev);
	पूर्ण

	अगर (dev->sysfs_created)
		sysfs_हटाओ_group(&dev->acpi_dev->dev.kobj,
				   &toshiba_attr_group);

	अगर (dev->ntfy_supported) अणु
		i8042_हटाओ_filter(toshiba_acpi_i8042_filter);
		cancel_work_sync(&dev->hotkey_work);
	पूर्ण

	अगर (dev->hotkey_dev)
		input_unरेजिस्टर_device(dev->hotkey_dev);

	backlight_device_unरेजिस्टर(dev->backlight_dev);

	led_classdev_unरेजिस्टर(&dev->led_dev);
	led_classdev_unरेजिस्टर(&dev->kbd_led);
	led_classdev_unरेजिस्टर(&dev->eco_led);

	अगर (dev->wwan_rfk) अणु
		rfसमाप्त_unरेजिस्टर(dev->wwan_rfk);
		rfसमाप्त_destroy(dev->wwan_rfk);
	पूर्ण

	अगर (toshiba_acpi)
		toshiba_acpi = शून्य;

	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *find_hci_method(acpi_handle handle)
अणु
	अगर (acpi_has_method(handle, "GHCI"))
		वापस "GHCI";

	अगर (acpi_has_method(handle, "SPFC"))
		वापस "SPFC";

	वापस शून्य;
पूर्ण

अटल पूर्णांक toshiba_acpi_add(काष्ठा acpi_device *acpi_dev)
अणु
	काष्ठा toshiba_acpi_dev *dev;
	स्थिर अक्षर *hci_method;
	u32 dummy;
	पूर्णांक ret = 0;

	अगर (toshiba_acpi)
		वापस -EBUSY;

	pr_info("Toshiba Laptop ACPI Extras version %s\n",
	       TOSHIBA_ACPI_VERSION);

	hci_method = find_hci_method(acpi_dev->handle);
	अगर (!hci_method) अणु
		pr_err("HCI interface not found\n");
		वापस -ENODEV;
	पूर्ण

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->acpi_dev = acpi_dev;
	dev->method_hci = hci_method;
	dev->miscdev.minor = MISC_DYNAMIC_MINOR;
	dev->miscdev.name = "toshiba_acpi";
	dev->miscdev.fops = &toshiba_acpi_fops;

	ret = misc_रेजिस्टर(&dev->miscdev);
	अगर (ret) अणु
		pr_err("Failed to register miscdevice\n");
		kमुक्त(dev);
		वापस ret;
	पूर्ण

	acpi_dev->driver_data = dev;
	dev_set_drvdata(&acpi_dev->dev, dev);

	/* Query the BIOS क्रम supported features */

	/*
	 * The "Special Functions" are always supported by the laptops
	 * with the new keyboard layout, query क्रम its presence to help
	 * determine the keymap layout to use.
	 */
	ret = toshiba_function_keys_get(dev, &dev->special_functions);
	dev->kbd_function_keys_supported = !ret;

	dev->hotkey_event_type = 0;
	अगर (toshiba_acpi_setup_keyboard(dev))
		pr_info("Unable to activate hotkeys\n");

	/* Determine whether or not BIOS supports transflective backlight */
	ret = get_tr_backlight_status(dev, &dummy);
	dev->tr_backlight_supported = !ret;

	ret = toshiba_acpi_setup_backlight(dev);
	अगर (ret)
		जाओ error;

	toshiba_illumination_available(dev);
	अगर (dev->illumination_supported) अणु
		dev->led_dev.name = "toshiba::illumination";
		dev->led_dev.max_brightness = 1;
		dev->led_dev.brightness_set = toshiba_illumination_set;
		dev->led_dev.brightness_get = toshiba_illumination_get;
		led_classdev_रेजिस्टर(&acpi_dev->dev, &dev->led_dev);
	पूर्ण

	toshiba_eco_mode_available(dev);
	अगर (dev->eco_supported) अणु
		dev->eco_led.name = "toshiba::eco_mode";
		dev->eco_led.max_brightness = 1;
		dev->eco_led.brightness_set = toshiba_eco_mode_set_status;
		dev->eco_led.brightness_get = toshiba_eco_mode_get_status;
		led_classdev_रेजिस्टर(&dev->acpi_dev->dev, &dev->eco_led);
	पूर्ण

	toshiba_kbd_illum_available(dev);
	/*
	 * Only रेजिस्टर the LED अगर KBD illumination is supported
	 * and the keyboard backlight operation mode is set to FN-Z
	 * or we detect a second gen keyboard backlight
	 */
	अगर (dev->kbd_illum_supported &&
	    (dev->kbd_mode == SCI_KBD_MODE_FNZ || dev->kbd_type == 2)) अणु
		dev->kbd_led.name = "toshiba::kbd_backlight";
		dev->kbd_led.flags = LED_BRIGHT_HW_CHANGED;
		dev->kbd_led.max_brightness = 1;
		dev->kbd_led.brightness_set = toshiba_kbd_backlight_set;
		dev->kbd_led.brightness_get = toshiba_kbd_backlight_get;
		led_classdev_रेजिस्टर(&dev->acpi_dev->dev, &dev->kbd_led);
	पूर्ण

	ret = toshiba_touchpad_get(dev, &dummy);
	dev->touchpad_supported = !ret;

	toshiba_accelerometer_available(dev);
	अगर (dev->accelerometer_supported) अणु
		dev->indio_dev = iio_device_alloc(&acpi_dev->dev, माप(*dev));
		अगर (!dev->indio_dev) अणु
			pr_err("Unable to allocate iio device\n");
			जाओ iio_error;
		पूर्ण

		pr_info("Registering Toshiba accelerometer iio device\n");

		dev->indio_dev->info = &toshiba_iio_accel_info;
		dev->indio_dev->name = "Toshiba accelerometer";
		dev->indio_dev->modes = INDIO_सूचीECT_MODE;
		dev->indio_dev->channels = toshiba_iio_accel_channels;
		dev->indio_dev->num_channels =
					ARRAY_SIZE(toshiba_iio_accel_channels);

		ret = iio_device_रेजिस्टर(dev->indio_dev);
		अगर (ret < 0) अणु
			pr_err("Unable to register iio device\n");
			iio_device_मुक्त(dev->indio_dev);
		पूर्ण
	पूर्ण
iio_error:

	toshiba_usb_sleep_अक्षरge_available(dev);

	ret = toshiba_usb_rapid_अक्षरge_get(dev, &dummy);
	dev->usb_rapid_अक्षरge_supported = !ret;

	ret = toshiba_usb_sleep_music_get(dev, &dummy);
	dev->usb_sleep_music_supported = !ret;

	ret = toshiba_panel_घातer_on_get(dev, &dummy);
	dev->panel_घातer_on_supported = !ret;

	ret = toshiba_usb_three_get(dev, &dummy);
	dev->usb_three_supported = !ret;

	ret = get_video_status(dev, &dummy);
	dev->video_supported = !ret;

	ret = get_fan_status(dev, &dummy);
	dev->fan_supported = !ret;

	toshiba_wwan_available(dev);
	अगर (dev->wwan_supported)
		toshiba_acpi_setup_wwan_rfसमाप्त(dev);

	toshiba_cooling_method_available(dev);

	prपूर्णांक_supported_features(dev);

	ret = sysfs_create_group(&dev->acpi_dev->dev.kobj,
				 &toshiba_attr_group);
	अगर (ret) अणु
		dev->sysfs_created = 0;
		जाओ error;
	पूर्ण
	dev->sysfs_created = !ret;

	create_toshiba_proc_entries(dev);

	toshiba_acpi = dev;

	वापस 0;

error:
	toshiba_acpi_हटाओ(acpi_dev);
	वापस ret;
पूर्ण

अटल व्योम toshiba_acpi_notअगरy(काष्ठा acpi_device *acpi_dev, u32 event)
अणु
	काष्ठा toshiba_acpi_dev *dev = acpi_driver_data(acpi_dev);

	चयन (event) अणु
	हाल 0x80: /* Hotkeys and some प्रणाली events */
		/*
		 * Machines with this WMI GUID aren't supported due to bugs in
		 * their AML.
		 *
		 * Return silently to aव्योम triggering a netlink event.
		 */
		अगर (wmi_has_guid(TOSHIBA_WMI_EVENT_GUID))
			वापस;
		toshiba_acpi_process_hotkeys(dev);
		अवरोध;
	हाल 0x81: /* Dock events */
	हाल 0x82:
	हाल 0x83:
		pr_info("Dock event received %x\n", event);
		अवरोध;
	हाल 0x88: /* Thermal events */
		pr_info("Thermal event received\n");
		अवरोध;
	हाल 0x8f: /* LID बंदd */
	हाल 0x90: /* LID is बंदd and Dock has been ejected */
		अवरोध;
	हाल 0x8c: /* SATA घातer events */
	हाल 0x8b:
		pr_info("SATA power event received %x\n", event);
		अवरोध;
	हाल 0x92: /* Keyboard backlight mode changed */
		dev->kbd_event_generated = true;
		/* Update sysfs entries */
		अगर (sysfs_update_group(&acpi_dev->dev.kobj,
				       &toshiba_attr_group))
			pr_err("Unable to update sysfs entries\n");
		/* Notअगरy LED subप्रणाली about keyboard backlight change */
		अगर (dev->kbd_type == 2 && dev->kbd_mode != SCI_KBD_MODE_AUTO)
			led_classdev_notअगरy_brightness_hw_changed(&dev->kbd_led,
					(dev->kbd_mode == SCI_KBD_MODE_ON) ?
					LED_FULL : LED_OFF);
		अवरोध;
	हाल 0x85: /* Unknown */
	हाल 0x8d: /* Unknown */
	हाल 0x8e: /* Unknown */
	हाल 0x94: /* Unknown */
	हाल 0x95: /* Unknown */
	शेष:
		pr_info("Unknown event received %x\n", event);
		अवरोध;
	पूर्ण

	acpi_bus_generate_netlink_event(acpi_dev->pnp.device_class,
					dev_name(&acpi_dev->dev),
					event, (event == 0x80) ?
					dev->last_key_event : 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक toshiba_acpi_suspend(काष्ठा device *device)
अणु
	काष्ठा toshiba_acpi_dev *dev = acpi_driver_data(to_acpi_device(device));

	अगर (dev->hotkey_dev) अणु
		u32 result;

		result = hci_ग_लिखो(dev, HCI_HOTKEY_EVENT, HCI_HOTKEY_DISABLE);
		अगर (result != TOS_SUCCESS)
			pr_info("Unable to disable hotkeys\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक toshiba_acpi_resume(काष्ठा device *device)
अणु
	काष्ठा toshiba_acpi_dev *dev = acpi_driver_data(to_acpi_device(device));

	अगर (dev->hotkey_dev) अणु
		अगर (toshiba_acpi_enable_hotkeys(dev))
			pr_info("Unable to re-enable hotkeys\n");
	पूर्ण

	अगर (dev->wwan_rfk) अणु
		अगर (!toshiba_wireless_status(dev))
			rfसमाप्त_set_hw_state(dev->wwan_rfk, !dev->समाप्तचयन);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(toshiba_acpi_pm,
			 toshiba_acpi_suspend, toshiba_acpi_resume);

अटल काष्ठा acpi_driver toshiba_acpi_driver = अणु
	.name	= "Toshiba ACPI driver",
	.owner	= THIS_MODULE,
	.ids	= toshiba_device_ids,
	.flags	= ACPI_DRIVER_ALL_NOTIFY_EVENTS,
	.ops	= अणु
		.add		= toshiba_acpi_add,
		.हटाओ		= toshiba_acpi_हटाओ,
		.notअगरy		= toshiba_acpi_notअगरy,
	पूर्ण,
	.drv.pm	= &toshiba_acpi_pm,
पूर्ण;

अटल पूर्णांक __init toshiba_acpi_init(व्योम)
अणु
	पूर्णांक ret;

	toshiba_proc_dir = proc_सूची_गढ़ो(PROC_TOSHIBA, acpi_root_dir);
	अगर (!toshiba_proc_dir) अणु
		pr_err("Unable to create proc dir " PROC_TOSHIBA "\n");
		वापस -ENODEV;
	पूर्ण

	ret = acpi_bus_रेजिस्टर_driver(&toshiba_acpi_driver);
	अगर (ret) अणु
		pr_err("Failed to register ACPI driver: %d\n", ret);
		हटाओ_proc_entry(PROC_TOSHIBA, acpi_root_dir);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास toshiba_acpi_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&toshiba_acpi_driver);
	अगर (toshiba_proc_dir)
		हटाओ_proc_entry(PROC_TOSHIBA, acpi_root_dir);
पूर्ण

module_init(toshiba_acpi_init);
module_निकास(toshiba_acpi_निकास);
