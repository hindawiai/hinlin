<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Acer WMI Laptop Extras
 *
 *  Copyright (C) 2007-2009	Carlos Corbacho <carlos@strangeworlds.co.uk>
 *
 *  Based on acer_acpi:
 *    Copyright (C) 2005-2007	E.M. Smith
 *    Copyright (C) 2007-2008	Carlos Corbacho <cathectic@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/dmi.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/i8042.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <acpi/video.h>

MODULE_AUTHOR("Carlos Corbacho");
MODULE_DESCRIPTION("Acer Laptop WMI Extras Driver");
MODULE_LICENSE("GPL");

/*
 * Magic Number
 * Meaning is unknown - this number is required क्रम writing to ACPI क्रम AMW0
 * (it's also used in acerhk when directly accessing the BIOS)
 */
#घोषणा ACER_AMW0_WRITE	0x9610

/*
 * Bit masks क्रम the AMW0 पूर्णांकerface
 */
#घोषणा ACER_AMW0_WIRELESS_MASK  0x35
#घोषणा ACER_AMW0_BLUETOOTH_MASK 0x34
#घोषणा ACER_AMW0_MAILLED_MASK   0x31

/*
 * Method IDs क्रम WMID पूर्णांकerface
 */
#घोषणा ACER_WMID_GET_WIRELESS_METHODID		1
#घोषणा ACER_WMID_GET_BLUETOOTH_METHODID	2
#घोषणा ACER_WMID_GET_BRIGHTNESS_METHODID	3
#घोषणा ACER_WMID_SET_WIRELESS_METHODID		4
#घोषणा ACER_WMID_SET_BLUETOOTH_METHODID	5
#घोषणा ACER_WMID_SET_BRIGHTNESS_METHODID	6
#घोषणा ACER_WMID_GET_THREEG_METHODID		10
#घोषणा ACER_WMID_SET_THREEG_METHODID		11

/*
 * Acer ACPI method GUIDs
 */
#घोषणा AMW0_GUID1		"67C3371D-95A3-4C37-BB61-DD47B491DAAB"
#घोषणा AMW0_GUID2		"431F16ED-0C2B-444C-B267-27DEB140CF9C"
#घोषणा WMID_GUID1		"6AF4F258-B401-42FD-BE91-3D4AC2D7C0D3"
#घोषणा WMID_GUID2		"95764E09-FB56-4E83-B31A-37761F60994A"
#घोषणा WMID_GUID3		"61EF69EA-865C-4BC3-A502-A0DEBA0CB531"

/*
 * Acer ACPI event GUIDs
 */
#घोषणा ACERWMID_EVENT_GUID "676AA15E-6A47-4D9F-A2CC-1E6D18D14026"

MODULE_ALIAS("wmi:67C3371D-95A3-4C37-BB61-DD47B491DAAB");
MODULE_ALIAS("wmi:6AF4F258-B401-42FD-BE91-3D4AC2D7C0D3");
MODULE_ALIAS("wmi:676AA15E-6A47-4D9F-A2CC-1E6D18D14026");

क्रमागत acer_wmi_event_ids अणु
	WMID_HOTKEY_EVENT = 0x1,
	WMID_ACCEL_OR_KBD_DOCK_EVENT = 0x5,
पूर्ण;

अटल स्थिर काष्ठा key_entry acer_wmi_keymap[] __initस्थिर = अणु
	अणुKE_KEY, 0x01, अणुKEY_WLANपूर्ण पूर्ण,     /* WiFi */
	अणुKE_KEY, 0x03, अणुKEY_WLANपूर्ण पूर्ण,     /* WiFi */
	अणुKE_KEY, 0x04, अणुKEY_WLANपूर्ण पूर्ण,     /* WiFi */
	अणुKE_KEY, 0x12, अणुKEY_BLUETOOTHपूर्ण पूर्ण,	/* BT */
	अणुKE_KEY, 0x21, अणुKEY_PROG1पूर्ण पूर्ण,    /* Backup */
	अणुKE_KEY, 0x22, अणुKEY_PROG2पूर्ण पूर्ण,    /* Arcade */
	अणुKE_KEY, 0x23, अणुKEY_PROG3पूर्ण पूर्ण,    /* P_Key */
	अणुKE_KEY, 0x24, अणुKEY_PROG4पूर्ण पूर्ण,    /* Social networking_Key */
	अणुKE_KEY, 0x29, अणुKEY_PROG3पूर्ण पूर्ण,    /* P_Key क्रम TM8372 */
	अणुKE_IGNORE, 0x41, अणुKEY_MUTEपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x42, अणुKEY_PREVIOUSSONGपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x4d, अणुKEY_PREVIOUSSONGपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x43, अणुKEY_NEXTSONGपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x4e, अणुKEY_NEXTSONGपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x44, अणुKEY_PLAYPAUSEपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x4f, अणुKEY_PLAYPAUSEपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x45, अणुKEY_STOPपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x50, अणुKEY_STOPपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x48, अणुKEY_VOLUMEUPपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x49, अणुKEY_VOLUMEDOWNपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x4a, अणुKEY_VOLUMEDOWNपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x61, अणुKEY_SWITCHVIDEOMODEपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x62, अणुKEY_BRIGHTNESSUPपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x63, अणुKEY_BRIGHTNESSDOWNपूर्ण पूर्ण,
	अणुKE_KEY, 0x64, अणुKEY_SWITCHVIDEOMODEपूर्ण पूर्ण,	/* Display Switch */
	अणुKE_IGNORE, 0x81, अणुKEY_SLEEPपूर्ण पूर्ण,
	अणुKE_KEY, 0x82, अणुKEY_TOUCHPAD_TOGGLEपूर्ण पूर्ण,	/* Touch Pad Toggle */
	अणुKE_IGNORE, 0x84, अणुKEY_KBDILLUMTOGGLEपूर्ण पूर्ण, /* Automatic Keyboard background light toggle */
	अणुKE_KEY, KEY_TOUCHPAD_ON, अणुKEY_TOUCHPAD_ONपूर्ण पूर्ण,
	अणुKE_KEY, KEY_TOUCHPAD_OFF, अणुKEY_TOUCHPAD_OFFपूर्ण पूर्ण,
	अणुKE_IGNORE, 0x83, अणुKEY_TOUCHPAD_TOGGLEपूर्ण पूर्ण,
	अणुKE_KEY, 0x85, अणुKEY_TOUCHPAD_TOGGLEपूर्ण पूर्ण,
	अणुKE_KEY, 0x86, अणुKEY_WLANपूर्ण पूर्ण,
	अणुKE_KEY, 0x87, अणुKEY_POWERपूर्ण पूर्ण,
	अणुKE_END, 0पूर्ण
पूर्ण;

अटल काष्ठा input_dev *acer_wmi_input_dev;
अटल काष्ठा input_dev *acer_wmi_accel_dev;

काष्ठा event_वापस_value अणु
	u8 function;
	u8 key_num;
	u16 device_state;
	u16 reserved1;
	u8 kbd_करोck_state;
	u8 reserved2;
पूर्ण __attribute__((packed));

/*
 * GUID3 Get Device Status device flags
 */
#घोषणा ACER_WMID3_GDS_WIRELESS		(1<<0)	/* WiFi */
#घोषणा ACER_WMID3_GDS_THREEG		(1<<6)	/* 3G */
#घोषणा ACER_WMID3_GDS_WIMAX		(1<<7)	/* WiMAX */
#घोषणा ACER_WMID3_GDS_BLUETOOTH	(1<<11)	/* BT */
#घोषणा ACER_WMID3_GDS_RFBTN		(1<<14)	/* RF Button */

#घोषणा ACER_WMID3_GDS_TOUCHPAD		(1<<1)	/* Touchpad */

/* Hotkey Customized Setting and Acer Application Status.
 * Set Device Default Value and Report Acer Application Status.
 * When Acer Application starts, it will run this method to inक्रमm
 * BIOS/EC that Acer Application is on.
 * App Status
 *	Bit[0]: Launch Manager Status
 *	Bit[1]: ePM Status
 *	Bit[2]: Device Control Status
 *	Bit[3]: Acer Power Button Utility Status
 *	Bit[4]: RF Button Status
 *	Bit[5]: ODD PM Status
 *	Bit[6]: Device Default Value Control
 *	Bit[7]: Hall Sensor Application Status
 */
काष्ठा func_input_params अणु
	u8 function_num;        /* Function Number */
	u16 commun_devices;     /* Communication type devices शेष status */
	u16 devices;            /* Other type devices शेष status */
	u8 app_status;          /* Acer Device Status. LM, ePM, RF Button... */
	u8 app_mask;		/* Bit mask to app_status */
	u8 reserved;
पूर्ण __attribute__((packed));

काष्ठा func_वापस_value अणु
	u8 error_code;          /* Error Code */
	u8 ec_वापस_value;     /* EC Return Value */
	u16 reserved;
पूर्ण __attribute__((packed));

काष्ठा wmid3_gds_set_input_param अणु     /* Set Device Status input parameter */
	u8 function_num;        /* Function Number */
	u8 hotkey_number;       /* Hotkey Number */
	u16 devices;            /* Set Device */
	u8 volume_value;        /* Volume Value */
पूर्ण __attribute__((packed));

काष्ठा wmid3_gds_get_input_param अणु     /* Get Device Status input parameter */
	u8 function_num;	/* Function Number */
	u8 hotkey_number;	/* Hotkey Number */
	u16 devices;		/* Get Device */
पूर्ण __attribute__((packed));

काष्ठा wmid3_gds_वापस_value अणु	/* Get Device Status वापस value*/
	u8 error_code;		/* Error Code */
	u8 ec_वापस_value;	/* EC Return Value */
	u16 devices;		/* Current Device Status */
	u32 reserved;
पूर्ण __attribute__((packed));

काष्ठा hotkey_function_type_aa अणु
	u8 type;
	u8 length;
	u16 handle;
	u16 commun_func_biपंचांगap;
	u16 application_func_biपंचांगap;
	u16 media_func_biपंचांगap;
	u16 display_func_biपंचांगap;
	u16 others_func_biपंचांगap;
	u8 commun_fn_key_number;
पूर्ण __attribute__((packed));

/*
 * Interface capability flags
 */
#घोषणा ACER_CAP_MAILLED		BIT(0)
#घोषणा ACER_CAP_WIRELESS		BIT(1)
#घोषणा ACER_CAP_BLUETOOTH		BIT(2)
#घोषणा ACER_CAP_BRIGHTNESS		BIT(3)
#घोषणा ACER_CAP_THREEG			BIT(4)
#घोषणा ACER_CAP_SET_FUNCTION_MODE	BIT(5)
#घोषणा ACER_CAP_KBD_DOCK		BIT(6)

/*
 * Interface type flags
 */
क्रमागत पूर्णांकerface_flags अणु
	ACER_AMW0,
	ACER_AMW0_V2,
	ACER_WMID,
	ACER_WMID_v2,
पूर्ण;

#घोषणा ACER_DEFAULT_WIRELESS  0
#घोषणा ACER_DEFAULT_BLUETOOTH 0
#घोषणा ACER_DEFAULT_MAILLED   0
#घोषणा ACER_DEFAULT_THREEG    0

अटल पूर्णांक max_brightness = 0xF;

अटल पूर्णांक mailled = -1;
अटल पूर्णांक brightness = -1;
अटल पूर्णांक threeg = -1;
अटल पूर्णांक क्रमce_series;
अटल पूर्णांक क्रमce_caps = -1;
अटल bool ec_raw_mode;
अटल bool has_type_aa;
अटल u16 commun_func_biपंचांगap;
अटल u8 commun_fn_key_number;

module_param(mailled, पूर्णांक, 0444);
module_param(brightness, पूर्णांक, 0444);
module_param(threeg, पूर्णांक, 0444);
module_param(क्रमce_series, पूर्णांक, 0444);
module_param(क्रमce_caps, पूर्णांक, 0444);
module_param(ec_raw_mode, bool, 0444);
MODULE_PARM_DESC(mailled, "Set initial state of Mail LED");
MODULE_PARM_DESC(brightness, "Set initial LCD backlight brightness");
MODULE_PARM_DESC(threeg, "Set initial state of 3G hardware");
MODULE_PARM_DESC(क्रमce_series, "Force a different laptop series");
MODULE_PARM_DESC(क्रमce_caps, "Force the capability bitmask to this value");
MODULE_PARM_DESC(ec_raw_mode, "Enable EC raw mode");

काष्ठा acer_data अणु
	पूर्णांक mailled;
	पूर्णांक threeg;
	पूर्णांक brightness;
पूर्ण;

काष्ठा acer_debug अणु
	काष्ठा dentry *root;
	u32 wmid_devices;
पूर्ण;

अटल काष्ठा rfसमाप्त *wireless_rfसमाप्त;
अटल काष्ठा rfसमाप्त *bluetooth_rfसमाप्त;
अटल काष्ठा rfसमाप्त *threeg_rfसमाप्त;
अटल bool rfसमाप्त_inited;

/* Each low-level पूर्णांकerface must define at least some of the following */
काष्ठा wmi_पूर्णांकerface अणु
	/* The WMI device type */
	u32 type;

	/* The capabilities this पूर्णांकerface provides */
	u32 capability;

	/* Private data क्रम the current पूर्णांकerface */
	काष्ठा acer_data data;

	/* debugfs entries associated with this पूर्णांकerface */
	काष्ठा acer_debug debug;
पूर्ण;

/* The अटल पूर्णांकerface poपूर्णांकer, poपूर्णांकs to the currently detected पूर्णांकerface */
अटल काष्ठा wmi_पूर्णांकerface *पूर्णांकerface;

/*
 * Embedded Controller quirks
 * Some laptops require us to directly access the EC to either enable or query
 * features that are not available through WMI.
 */

काष्ठा quirk_entry अणु
	u8 wireless;
	u8 mailled;
	s8 brightness;
	u8 bluetooth;
पूर्ण;

अटल काष्ठा quirk_entry *quirks;

अटल व्योम __init set_quirks(व्योम)
अणु
	अगर (quirks->mailled)
		पूर्णांकerface->capability |= ACER_CAP_MAILLED;

	अगर (quirks->brightness)
		पूर्णांकerface->capability |= ACER_CAP_BRIGHTNESS;
पूर्ण

अटल पूर्णांक __init dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	quirks = dmi->driver_data;
	वापस 1;
पूर्ण

अटल पूर्णांक __init set_क्रमce_caps(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	अगर (क्रमce_caps == -1) अणु
		क्रमce_caps = (uपूर्णांकptr_t)dmi->driver_data;
		pr_info("Found %s, set force_caps to 0x%x\n", dmi->ident, क्रमce_caps);
	पूर्ण
	वापस 1;
पूर्ण

अटल काष्ठा quirk_entry quirk_unknown = अणु
पूर्ण;

अटल काष्ठा quirk_entry quirk_acer_aspire_1520 = अणु
	.brightness = -1,
पूर्ण;

अटल काष्ठा quirk_entry quirk_acer_travelmate_2490 = अणु
	.mailled = 1,
पूर्ण;

/* This AMW0 laptop has no bluetooth */
अटल काष्ठा quirk_entry quirk_medion_md_98300 = अणु
	.wireless = 1,
पूर्ण;

अटल काष्ठा quirk_entry quirk_fujitsu_amilo_li_1718 = अणु
	.wireless = 2,
पूर्ण;

अटल काष्ठा quirk_entry quirk_lenovo_ideapad_s205 = अणु
	.wireless = 3,
पूर्ण;

/* The Aspire One has a dummy ACPI-WMI पूर्णांकerface - disable it */
अटल स्थिर काष्ठा dmi_प्रणाली_id acer_blacklist[] __initस्थिर = अणु
	अणु
		.ident = "Acer Aspire One (SSD)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AOA110"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Acer Aspire One (HDD)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AOA150"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id amw0_whitelist[] __initस्थिर = अणु
	अणु
		.ident = "Acer",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Gateway",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Gateway"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Packard Bell",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Packard Bell"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * This quirk table is only क्रम Acer/Gateway/Packard Bell family
 * that those machines are supported by acer-wmi driver.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id acer_quirks[] __initस्थिर = अणु
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 1360",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 1360"),
		पूर्ण,
		.driver_data = &quirk_acer_aspire_1520,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 1520",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 1520"),
		पूर्ण,
		.driver_data = &quirk_acer_aspire_1520,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 3100",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 3100"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 3610",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 3610"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 5100",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5100"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 5610",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5610"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 5630",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5630"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 5650",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5650"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 5680",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5680"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer Aspire 9110",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 9110"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer TravelMate 2490",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 2490"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Acer TravelMate 4200",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 4200"),
		पूर्ण,
		.driver_data = &quirk_acer_travelmate_2490,
	पूर्ण,
	अणु
		.callback = set_क्रमce_caps,
		.ident = "Acer Aspire Switch 10E SW3-016",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire SW3-016"),
		पूर्ण,
		.driver_data = (व्योम *)ACER_CAP_KBD_DOCK,
	पूर्ण,
	अणु
		.callback = set_क्रमce_caps,
		.ident = "Acer Aspire Switch 10 SW5-012",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire SW5-012"),
		पूर्ण,
		.driver_data = (व्योम *)ACER_CAP_KBD_DOCK,
	पूर्ण,
	अणु
		.callback = set_क्रमce_caps,
		.ident = "Acer One 10 (S1003)",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "One S1003"),
		पूर्ण,
		.driver_data = (व्योम *)ACER_CAP_KBD_DOCK,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * This quirk list is क्रम those non-acer machines that have AMW0_GUID1
 * but supported by acer-wmi in past days. Keeping this quirk list here
 * is only क्रम backward compatible. Please करो not add new machine to
 * here anymore. Those non-acer machines should be supported by
 * appropriate wmi drivers.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id non_acer_quirks[] __initस्थिर = अणु
	अणु
		.callback = dmi_matched,
		.ident = "Fujitsu Siemens Amilo Li 1718",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Li 1718"),
		पूर्ण,
		.driver_data = &quirk_fujitsu_amilo_li_1718,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Medion MD 98300",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDION"),
			DMI_MATCH(DMI_PRODUCT_NAME, "WAM2030"),
		पूर्ण,
		.driver_data = &quirk_medion_md_98300,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Lenovo Ideapad S205",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "10382LG"),
		पूर्ण,
		.driver_data = &quirk_lenovo_ideapad_s205,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Lenovo Ideapad S205 (Brazos)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Brazos"),
		पूर्ण,
		.driver_data = &quirk_lenovo_ideapad_s205,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Lenovo 3000 N200",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "0687A31"),
		पूर्ण,
		.driver_data = &quirk_fujitsu_amilo_li_1718,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Lenovo Ideapad S205-10382JG",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "10382JG"),
		पूर्ण,
		.driver_data = &quirk_lenovo_ideapad_s205,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Lenovo Ideapad S205-1038DPG",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "1038DPG"),
		पूर्ण,
		.driver_data = &quirk_lenovo_ideapad_s205,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init
video_set_backlight_video_venकरोr(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	पूर्णांकerface->capability &= ~ACER_CAP_BRIGHTNESS;
	pr_info("Brightness must be controlled by generic video driver\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id video_venकरोr_dmi_table[] __initस्थिर = अणु
	अणु
		.callback = video_set_backlight_video_venकरोr,
		.ident = "Acer TravelMate 4750",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 4750"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = video_set_backlight_video_venकरोr,
		.ident = "Acer Extensa 5235",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Extensa 5235"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = video_set_backlight_video_venकरोr,
		.ident = "Acer TravelMate 5760",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TravelMate 5760"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = video_set_backlight_video_venकरोr,
		.ident = "Acer Aspire 5750",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5750"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = video_set_backlight_video_venकरोr,
		.ident = "Acer Aspire 5741",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5741"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * Note no video_set_backlight_video_venकरोr, we must use the
		 * acer पूर्णांकerface, as there is no native backlight पूर्णांकerface.
		 */
		.ident = "Acer KAV80",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "KAV80"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/* Find which quirks are needed क्रम a particular venकरोr/ model pair */
अटल व्योम __init find_quirks(व्योम)
अणु
	अगर (!क्रमce_series) अणु
		dmi_check_प्रणाली(acer_quirks);
		dmi_check_प्रणाली(non_acer_quirks);
	पूर्ण अन्यथा अगर (क्रमce_series == 2490) अणु
		quirks = &quirk_acer_travelmate_2490;
	पूर्ण

	अगर (quirks == शून्य)
		quirks = &quirk_unknown;
पूर्ण

/*
 * General पूर्णांकerface convenience methods
 */

अटल bool has_cap(u32 cap)
अणु
	वापस पूर्णांकerface->capability & cap;
पूर्ण

/*
 * AMW0 (V1) पूर्णांकerface
 */
काष्ठा wmab_args अणु
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
पूर्ण;

काष्ठा wmab_ret अणु
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
	u32 eex;
पूर्ण;

अटल acpi_status wmab_execute(काष्ठा wmab_args *regbuf,
काष्ठा acpi_buffer *result)
अणु
	काष्ठा acpi_buffer input;
	acpi_status status;
	input.length = माप(काष्ठा wmab_args);
	input.poपूर्णांकer = (u8 *)regbuf;

	status = wmi_evaluate_method(AMW0_GUID1, 0, 1, &input, result);

	वापस status;
पूर्ण

अटल acpi_status AMW0_get_u32(u32 *value, u32 cap)
अणु
	पूर्णांक err;
	u8 result;

	चयन (cap) अणु
	हाल ACER_CAP_MAILLED:
		चयन (quirks->mailled) अणु
		शेष:
			err = ec_पढ़ो(0xA, &result);
			अगर (err)
				वापस AE_ERROR;
			*value = (result >> 7) & 0x1;
			वापस AE_OK;
		पूर्ण
		अवरोध;
	हाल ACER_CAP_WIRELESS:
		चयन (quirks->wireless) अणु
		हाल 1:
			err = ec_पढ़ो(0x7B, &result);
			अगर (err)
				वापस AE_ERROR;
			*value = result & 0x1;
			वापस AE_OK;
		हाल 2:
			err = ec_पढ़ो(0x71, &result);
			अगर (err)
				वापस AE_ERROR;
			*value = result & 0x1;
			वापस AE_OK;
		हाल 3:
			err = ec_पढ़ो(0x78, &result);
			अगर (err)
				वापस AE_ERROR;
			*value = result & 0x1;
			वापस AE_OK;
		शेष:
			err = ec_पढ़ो(0xA, &result);
			अगर (err)
				वापस AE_ERROR;
			*value = (result >> 2) & 0x1;
			वापस AE_OK;
		पूर्ण
		अवरोध;
	हाल ACER_CAP_BLUETOOTH:
		चयन (quirks->bluetooth) अणु
		शेष:
			err = ec_पढ़ो(0xA, &result);
			अगर (err)
				वापस AE_ERROR;
			*value = (result >> 4) & 0x1;
			वापस AE_OK;
		पूर्ण
		अवरोध;
	हाल ACER_CAP_BRIGHTNESS:
		चयन (quirks->brightness) अणु
		शेष:
			err = ec_पढ़ो(0x83, &result);
			अगर (err)
				वापस AE_ERROR;
			*value = result;
			वापस AE_OK;
		पूर्ण
		अवरोध;
	शेष:
		वापस AE_ERROR;
	पूर्ण
	वापस AE_OK;
पूर्ण

अटल acpi_status AMW0_set_u32(u32 value, u32 cap)
अणु
	काष्ठा wmab_args args;

	args.eax = ACER_AMW0_WRITE;
	args.ebx = value ? (1<<8) : 0;
	args.ecx = args.edx = 0;

	चयन (cap) अणु
	हाल ACER_CAP_MAILLED:
		अगर (value > 1)
			वापस AE_BAD_PARAMETER;
		args.ebx |= ACER_AMW0_MAILLED_MASK;
		अवरोध;
	हाल ACER_CAP_WIRELESS:
		अगर (value > 1)
			वापस AE_BAD_PARAMETER;
		args.ebx |= ACER_AMW0_WIRELESS_MASK;
		अवरोध;
	हाल ACER_CAP_BLUETOOTH:
		अगर (value > 1)
			वापस AE_BAD_PARAMETER;
		args.ebx |= ACER_AMW0_BLUETOOTH_MASK;
		अवरोध;
	हाल ACER_CAP_BRIGHTNESS:
		अगर (value > max_brightness)
			वापस AE_BAD_PARAMETER;
		चयन (quirks->brightness) अणु
		शेष:
			वापस ec_ग_लिखो(0x83, value);
		पूर्ण
	शेष:
		वापस AE_ERROR;
	पूर्ण

	/* Actually करो the set */
	वापस wmab_execute(&args, शून्य);
पूर्ण

अटल acpi_status __init AMW0_find_mailled(व्योम)
अणु
	काष्ठा wmab_args args;
	काष्ठा wmab_ret ret;
	acpi_status status = AE_OK;
	काष्ठा acpi_buffer out = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;

	args.eax = 0x86;
	args.ebx = args.ecx = args.edx = 0;

	status = wmab_execute(&args, &out);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = (जोड़ acpi_object *) out.poपूर्णांकer;
	अगर (obj && obj->type == ACPI_TYPE_BUFFER &&
	obj->buffer.length == माप(काष्ठा wmab_ret)) अणु
		ret = *((काष्ठा wmab_ret *) obj->buffer.poपूर्णांकer);
	पूर्ण अन्यथा अणु
		kमुक्त(out.poपूर्णांकer);
		वापस AE_ERROR;
	पूर्ण

	अगर (ret.eex & 0x1)
		पूर्णांकerface->capability |= ACER_CAP_MAILLED;

	kमुक्त(out.poपूर्णांकer);

	वापस AE_OK;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id norfसमाप्त_ids[] __initस्थिर = अणु
	अणु "VPC2004", 0पूर्ण,
	अणु "IBM0068", 0पूर्ण,
	अणु "LEN0068", 0पूर्ण,
	अणु "SNY5001", 0पूर्ण,	/* sony-laptop in अक्षरge */
	अणु "HPQ6601", 0पूर्ण,
	अणु "", 0पूर्ण,
पूर्ण;

अटल पूर्णांक __init AMW0_set_cap_acpi_check_device(व्योम)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	क्रम (id = norfसमाप्त_ids; id->id[0]; id++)
		अगर (acpi_dev_found(id->id))
			वापस true;

	वापस false;
पूर्ण

अटल acpi_status __init AMW0_set_capabilities(व्योम)
अणु
	काष्ठा wmab_args args;
	काष्ठा wmab_ret ret;
	acpi_status status;
	काष्ठा acpi_buffer out = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;

	/*
	 * On laptops with this strange GUID (non Acer), normal probing करोesn't
	 * work.
	 */
	अगर (wmi_has_guid(AMW0_GUID2)) अणु
		अगर ((quirks != &quirk_unknown) ||
		    !AMW0_set_cap_acpi_check_device())
			पूर्णांकerface->capability |= ACER_CAP_WIRELESS;
		वापस AE_OK;
	पूर्ण

	args.eax = ACER_AMW0_WRITE;
	args.ecx = args.edx = 0;

	args.ebx = 0xa2 << 8;
	args.ebx |= ACER_AMW0_WIRELESS_MASK;

	status = wmab_execute(&args, &out);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = out.poपूर्णांकer;
	अगर (obj && obj->type == ACPI_TYPE_BUFFER &&
	obj->buffer.length == माप(काष्ठा wmab_ret)) अणु
		ret = *((काष्ठा wmab_ret *) obj->buffer.poपूर्णांकer);
	पूर्ण अन्यथा अणु
		status = AE_ERROR;
		जाओ out;
	पूर्ण

	अगर (ret.eax & 0x1)
		पूर्णांकerface->capability |= ACER_CAP_WIRELESS;

	args.ebx = 2 << 8;
	args.ebx |= ACER_AMW0_BLUETOOTH_MASK;

	/*
	 * It's ok to use existing buffer क्रम next wmab_execute call.
	 * But we need to kमुक्त(out.poपूर्णांकer) अगर next wmab_execute fail.
	 */
	status = wmab_execute(&args, &out);
	अगर (ACPI_FAILURE(status))
		जाओ out;

	obj = (जोड़ acpi_object *) out.poपूर्णांकer;
	अगर (obj && obj->type == ACPI_TYPE_BUFFER
	&& obj->buffer.length == माप(काष्ठा wmab_ret)) अणु
		ret = *((काष्ठा wmab_ret *) obj->buffer.poपूर्णांकer);
	पूर्ण अन्यथा अणु
		status = AE_ERROR;
		जाओ out;
	पूर्ण

	अगर (ret.eax & 0x1)
		पूर्णांकerface->capability |= ACER_CAP_BLUETOOTH;

	/*
	 * This appears to be safe to enable, since all Wistron based laptops
	 * appear to use the same EC रेजिस्टर क्रम brightness, even अगर they
	 * dअगरfer क्रम wireless, etc
	 */
	अगर (quirks->brightness >= 0)
		पूर्णांकerface->capability |= ACER_CAP_BRIGHTNESS;

	status = AE_OK;
out:
	kमुक्त(out.poपूर्णांकer);
	वापस status;
पूर्ण

अटल काष्ठा wmi_पूर्णांकerface AMW0_पूर्णांकerface = अणु
	.type = ACER_AMW0,
पूर्ण;

अटल काष्ठा wmi_पूर्णांकerface AMW0_V2_पूर्णांकerface = अणु
	.type = ACER_AMW0_V2,
पूर्ण;

/*
 * New पूर्णांकerface (The WMID पूर्णांकerface)
 */
अटल acpi_status
WMI_execute_u32(u32 method_id, u32 in, u32 *out)
अणु
	काष्ठा acpi_buffer input = अणु (acpi_size) माप(u32), (व्योम *)(&in) पूर्ण;
	काष्ठा acpi_buffer result = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	u32 पंचांगp = 0;
	acpi_status status;

	status = wmi_evaluate_method(WMID_GUID1, 0, method_id, &input, &result);

	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = (जोड़ acpi_object *) result.poपूर्णांकer;
	अगर (obj) अणु
		अगर (obj->type == ACPI_TYPE_BUFFER &&
			(obj->buffer.length == माप(u32) ||
			obj->buffer.length == माप(u64))) अणु
			पंचांगp = *((u32 *) obj->buffer.poपूर्णांकer);
		पूर्ण अन्यथा अगर (obj->type == ACPI_TYPE_INTEGER) अणु
			पंचांगp = (u32) obj->पूर्णांकeger.value;
		पूर्ण
	पूर्ण

	अगर (out)
		*out = पंचांगp;

	kमुक्त(result.poपूर्णांकer);

	वापस status;
पूर्ण

अटल acpi_status WMID_get_u32(u32 *value, u32 cap)
अणु
	acpi_status status;
	u8 पंचांगp;
	u32 result, method_id = 0;

	चयन (cap) अणु
	हाल ACER_CAP_WIRELESS:
		method_id = ACER_WMID_GET_WIRELESS_METHODID;
		अवरोध;
	हाल ACER_CAP_BLUETOOTH:
		method_id = ACER_WMID_GET_BLUETOOTH_METHODID;
		अवरोध;
	हाल ACER_CAP_BRIGHTNESS:
		method_id = ACER_WMID_GET_BRIGHTNESS_METHODID;
		अवरोध;
	हाल ACER_CAP_THREEG:
		method_id = ACER_WMID_GET_THREEG_METHODID;
		अवरोध;
	हाल ACER_CAP_MAILLED:
		अगर (quirks->mailled == 1) अणु
			ec_पढ़ो(0x9f, &पंचांगp);
			*value = पंचांगp & 0x1;
			वापस 0;
		पूर्ण
		fallthrough;
	शेष:
		वापस AE_ERROR;
	पूर्ण
	status = WMI_execute_u32(method_id, 0, &result);

	अगर (ACPI_SUCCESS(status))
		*value = (u8)result;

	वापस status;
पूर्ण

अटल acpi_status WMID_set_u32(u32 value, u32 cap)
अणु
	u32 method_id = 0;
	अक्षर param;

	चयन (cap) अणु
	हाल ACER_CAP_BRIGHTNESS:
		अगर (value > max_brightness)
			वापस AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_BRIGHTNESS_METHODID;
		अवरोध;
	हाल ACER_CAP_WIRELESS:
		अगर (value > 1)
			वापस AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_WIRELESS_METHODID;
		अवरोध;
	हाल ACER_CAP_BLUETOOTH:
		अगर (value > 1)
			वापस AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_BLUETOOTH_METHODID;
		अवरोध;
	हाल ACER_CAP_THREEG:
		अगर (value > 1)
			वापस AE_BAD_PARAMETER;
		method_id = ACER_WMID_SET_THREEG_METHODID;
		अवरोध;
	हाल ACER_CAP_MAILLED:
		अगर (value > 1)
			वापस AE_BAD_PARAMETER;
		अगर (quirks->mailled == 1) अणु
			param = value ? 0x92 : 0x93;
			i8042_lock_chip();
			i8042_command(&param, 0x1059);
			i8042_unlock_chip();
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		वापस AE_ERROR;
	पूर्ण
	वापस WMI_execute_u32(method_id, (u32)value, शून्य);
पूर्ण

अटल acpi_status wmid3_get_device_status(u32 *value, u16 device)
अणु
	काष्ठा wmid3_gds_वापस_value वापस_value;
	acpi_status status;
	जोड़ acpi_object *obj;
	काष्ठा wmid3_gds_get_input_param params = अणु
		.function_num = 0x1,
		.hotkey_number = commun_fn_key_number,
		.devices = device,
	पूर्ण;
	काष्ठा acpi_buffer input = अणु
		माप(काष्ठा wmid3_gds_get_input_param),
		&params
	पूर्ण;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	status = wmi_evaluate_method(WMID_GUID3, 0, 0x2, &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = output.poपूर्णांकer;

	अगर (!obj)
		वापस AE_ERROR;
	अन्यथा अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		kमुक्त(obj);
		वापस AE_ERROR;
	पूर्ण
	अगर (obj->buffer.length != 8) अणु
		pr_warn("Unknown buffer length %d\n", obj->buffer.length);
		kमुक्त(obj);
		वापस AE_ERROR;
	पूर्ण

	वापस_value = *((काष्ठा wmid3_gds_वापस_value *)obj->buffer.poपूर्णांकer);
	kमुक्त(obj);

	अगर (वापस_value.error_code || वापस_value.ec_वापस_value)
		pr_warn("Get 0x%x Device Status failed: 0x%x - 0x%x\n",
			device,
			वापस_value.error_code,
			वापस_value.ec_वापस_value);
	अन्यथा
		*value = !!(वापस_value.devices & device);

	वापस status;
पूर्ण

अटल acpi_status wmid_v2_get_u32(u32 *value, u32 cap)
अणु
	u16 device;

	चयन (cap) अणु
	हाल ACER_CAP_WIRELESS:
		device = ACER_WMID3_GDS_WIRELESS;
		अवरोध;
	हाल ACER_CAP_BLUETOOTH:
		device = ACER_WMID3_GDS_BLUETOOTH;
		अवरोध;
	हाल ACER_CAP_THREEG:
		device = ACER_WMID3_GDS_THREEG;
		अवरोध;
	शेष:
		वापस AE_ERROR;
	पूर्ण
	वापस wmid3_get_device_status(value, device);
पूर्ण

अटल acpi_status wmid3_set_device_status(u32 value, u16 device)
अणु
	काष्ठा wmid3_gds_वापस_value वापस_value;
	acpi_status status;
	जोड़ acpi_object *obj;
	u16 devices;
	काष्ठा wmid3_gds_get_input_param get_params = अणु
		.function_num = 0x1,
		.hotkey_number = commun_fn_key_number,
		.devices = commun_func_biपंचांगap,
	पूर्ण;
	काष्ठा acpi_buffer get_input = अणु
		माप(काष्ठा wmid3_gds_get_input_param),
		&get_params
	पूर्ण;
	काष्ठा wmid3_gds_set_input_param set_params = अणु
		.function_num = 0x2,
		.hotkey_number = commun_fn_key_number,
		.devices = commun_func_biपंचांगap,
	पूर्ण;
	काष्ठा acpi_buffer set_input = अणु
		माप(काष्ठा wmid3_gds_set_input_param),
		&set_params
	पूर्ण;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer output2 = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	status = wmi_evaluate_method(WMID_GUID3, 0, 0x2, &get_input, &output);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = output.poपूर्णांकer;

	अगर (!obj)
		वापस AE_ERROR;
	अन्यथा अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		kमुक्त(obj);
		वापस AE_ERROR;
	पूर्ण
	अगर (obj->buffer.length != 8) अणु
		pr_warn("Unknown buffer length %d\n", obj->buffer.length);
		kमुक्त(obj);
		वापस AE_ERROR;
	पूर्ण

	वापस_value = *((काष्ठा wmid3_gds_वापस_value *)obj->buffer.poपूर्णांकer);
	kमुक्त(obj);

	अगर (वापस_value.error_code || वापस_value.ec_वापस_value) अणु
		pr_warn("Get Current Device Status failed: 0x%x - 0x%x\n",
			वापस_value.error_code,
			वापस_value.ec_वापस_value);
		वापस status;
	पूर्ण

	devices = वापस_value.devices;
	set_params.devices = (value) ? (devices | device) : (devices & ~device);

	status = wmi_evaluate_method(WMID_GUID3, 0, 0x1, &set_input, &output2);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = output2.poपूर्णांकer;

	अगर (!obj)
		वापस AE_ERROR;
	अन्यथा अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		kमुक्त(obj);
		वापस AE_ERROR;
	पूर्ण
	अगर (obj->buffer.length != 4) अणु
		pr_warn("Unknown buffer length %d\n", obj->buffer.length);
		kमुक्त(obj);
		वापस AE_ERROR;
	पूर्ण

	वापस_value = *((काष्ठा wmid3_gds_वापस_value *)obj->buffer.poपूर्णांकer);
	kमुक्त(obj);

	अगर (वापस_value.error_code || वापस_value.ec_वापस_value)
		pr_warn("Set Device Status failed: 0x%x - 0x%x\n",
			वापस_value.error_code,
			वापस_value.ec_वापस_value);

	वापस status;
पूर्ण

अटल acpi_status wmid_v2_set_u32(u32 value, u32 cap)
अणु
	u16 device;

	चयन (cap) अणु
	हाल ACER_CAP_WIRELESS:
		device = ACER_WMID3_GDS_WIRELESS;
		अवरोध;
	हाल ACER_CAP_BLUETOOTH:
		device = ACER_WMID3_GDS_BLUETOOTH;
		अवरोध;
	हाल ACER_CAP_THREEG:
		device = ACER_WMID3_GDS_THREEG;
		अवरोध;
	शेष:
		वापस AE_ERROR;
	पूर्ण
	वापस wmid3_set_device_status(value, device);
पूर्ण

अटल व्योम __init type_aa_dmi_decode(स्थिर काष्ठा dmi_header *header, व्योम *d)
अणु
	काष्ठा hotkey_function_type_aa *type_aa;

	/* We are looking क्रम OEM-specअगरic Type AAh */
	अगर (header->type != 0xAA)
		वापस;

	has_type_aa = true;
	type_aa = (काष्ठा hotkey_function_type_aa *) header;

	pr_info("Function bitmap for Communication Button: 0x%x\n",
		type_aa->commun_func_biपंचांगap);
	commun_func_biपंचांगap = type_aa->commun_func_biपंचांगap;

	अगर (type_aa->commun_func_biपंचांगap & ACER_WMID3_GDS_WIRELESS)
		पूर्णांकerface->capability |= ACER_CAP_WIRELESS;
	अगर (type_aa->commun_func_biपंचांगap & ACER_WMID3_GDS_THREEG)
		पूर्णांकerface->capability |= ACER_CAP_THREEG;
	अगर (type_aa->commun_func_biपंचांगap & ACER_WMID3_GDS_BLUETOOTH)
		पूर्णांकerface->capability |= ACER_CAP_BLUETOOTH;
	अगर (type_aa->commun_func_biपंचांगap & ACER_WMID3_GDS_RFBTN)
		commun_func_biपंचांगap &= ~ACER_WMID3_GDS_RFBTN;

	commun_fn_key_number = type_aa->commun_fn_key_number;
पूर्ण

अटल acpi_status __init WMID_set_capabilities(व्योम)
अणु
	काष्ठा acpi_buffer out = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;
	u32 devices;

	status = wmi_query_block(WMID_GUID2, 0, &out);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = (जोड़ acpi_object *) out.poपूर्णांकer;
	अगर (obj) अणु
		अगर (obj->type == ACPI_TYPE_BUFFER &&
			(obj->buffer.length == माप(u32) ||
			obj->buffer.length == माप(u64))) अणु
			devices = *((u32 *) obj->buffer.poपूर्णांकer);
		पूर्ण अन्यथा अगर (obj->type == ACPI_TYPE_INTEGER) अणु
			devices = (u32) obj->पूर्णांकeger.value;
		पूर्ण अन्यथा अणु
			kमुक्त(out.poपूर्णांकer);
			वापस AE_ERROR;
		पूर्ण
	पूर्ण अन्यथा अणु
		kमुक्त(out.poपूर्णांकer);
		वापस AE_ERROR;
	पूर्ण

	pr_info("Function bitmap for Communication Device: 0x%x\n", devices);
	अगर (devices & 0x07)
		पूर्णांकerface->capability |= ACER_CAP_WIRELESS;
	अगर (devices & 0x40)
		पूर्णांकerface->capability |= ACER_CAP_THREEG;
	अगर (devices & 0x10)
		पूर्णांकerface->capability |= ACER_CAP_BLUETOOTH;

	अगर (!(devices & 0x20))
		max_brightness = 0x9;

	kमुक्त(out.poपूर्णांकer);
	वापस status;
पूर्ण

अटल काष्ठा wmi_पूर्णांकerface wmid_पूर्णांकerface = अणु
	.type = ACER_WMID,
पूर्ण;

अटल काष्ठा wmi_पूर्णांकerface wmid_v2_पूर्णांकerface = अणु
	.type = ACER_WMID_v2,
पूर्ण;

/*
 * Generic Device (पूर्णांकerface-independent)
 */

अटल acpi_status get_u32(u32 *value, u32 cap)
अणु
	acpi_status status = AE_ERROR;

	चयन (पूर्णांकerface->type) अणु
	हाल ACER_AMW0:
		status = AMW0_get_u32(value, cap);
		अवरोध;
	हाल ACER_AMW0_V2:
		अगर (cap == ACER_CAP_MAILLED) अणु
			status = AMW0_get_u32(value, cap);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल ACER_WMID:
		status = WMID_get_u32(value, cap);
		अवरोध;
	हाल ACER_WMID_v2:
		अगर (cap & (ACER_CAP_WIRELESS |
			   ACER_CAP_BLUETOOTH |
			   ACER_CAP_THREEG))
			status = wmid_v2_get_u32(value, cap);
		अन्यथा अगर (wmi_has_guid(WMID_GUID2))
			status = WMID_get_u32(value, cap);
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल acpi_status set_u32(u32 value, u32 cap)
अणु
	acpi_status status;

	अगर (पूर्णांकerface->capability & cap) अणु
		चयन (पूर्णांकerface->type) अणु
		हाल ACER_AMW0:
			वापस AMW0_set_u32(value, cap);
		हाल ACER_AMW0_V2:
			अगर (cap == ACER_CAP_MAILLED)
				वापस AMW0_set_u32(value, cap);

			/*
			 * On some models, some WMID methods करोn't toggle
			 * properly. For those हालs, we want to run the AMW0
			 * method afterwards to be certain we've really toggled
			 * the device state.
			 */
			अगर (cap == ACER_CAP_WIRELESS ||
				cap == ACER_CAP_BLUETOOTH) अणु
				status = WMID_set_u32(value, cap);
				अगर (ACPI_FAILURE(status))
					वापस status;

				वापस AMW0_set_u32(value, cap);
			पूर्ण
			fallthrough;
		हाल ACER_WMID:
			वापस WMID_set_u32(value, cap);
		हाल ACER_WMID_v2:
			अगर (cap & (ACER_CAP_WIRELESS |
				   ACER_CAP_BLUETOOTH |
				   ACER_CAP_THREEG))
				वापस wmid_v2_set_u32(value, cap);
			अन्यथा अगर (wmi_has_guid(WMID_GUID2))
				वापस WMID_set_u32(value, cap);
			fallthrough;
		शेष:
			वापस AE_BAD_PARAMETER;
		पूर्ण
	पूर्ण
	वापस AE_BAD_PARAMETER;
पूर्ण

अटल व्योम __init acer_commandline_init(व्योम)
अणु
	/*
	 * These will all fail silently अगर the value given is invalid, or the
	 * capability isn't available on the given पूर्णांकerface
	 */
	अगर (mailled >= 0)
		set_u32(mailled, ACER_CAP_MAILLED);
	अगर (!has_type_aa && threeg >= 0)
		set_u32(threeg, ACER_CAP_THREEG);
	अगर (brightness >= 0)
		set_u32(brightness, ACER_CAP_BRIGHTNESS);
पूर्ण

/*
 * LED device (Mail LED only, no other LEDs known yet)
 */
अटल व्योम mail_led_set(काष्ठा led_classdev *led_cdev,
क्रमागत led_brightness value)
अणु
	set_u32(value, ACER_CAP_MAILLED);
पूर्ण

अटल काष्ठा led_classdev mail_led = अणु
	.name = "acer-wmi::mail",
	.brightness_set = mail_led_set,
पूर्ण;

अटल पूर्णांक acer_led_init(काष्ठा device *dev)
अणु
	वापस led_classdev_रेजिस्टर(dev, &mail_led);
पूर्ण

अटल व्योम acer_led_निकास(व्योम)
अणु
	set_u32(LED_OFF, ACER_CAP_MAILLED);
	led_classdev_unरेजिस्टर(&mail_led);
पूर्ण

/*
 * Backlight device
 */
अटल काष्ठा backlight_device *acer_backlight_device;

अटल पूर्णांक पढ़ो_brightness(काष्ठा backlight_device *bd)
अणु
	u32 value;
	get_u32(&value, ACER_CAP_BRIGHTNESS);
	वापस value;
पूर्ण

अटल पूर्णांक update_bl_status(काष्ठा backlight_device *bd)
अणु
	पूर्णांक पूर्णांकensity = bd->props.brightness;

	अगर (bd->props.घातer != FB_BLANK_UNBLANK)
		पूर्णांकensity = 0;
	अगर (bd->props.fb_blank != FB_BLANK_UNBLANK)
		पूर्णांकensity = 0;

	set_u32(पूर्णांकensity, ACER_CAP_BRIGHTNESS);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops acer_bl_ops = अणु
	.get_brightness = पढ़ो_brightness,
	.update_status = update_bl_status,
पूर्ण;

अटल पूर्णांक acer_backlight_init(काष्ठा device *dev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bd;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = max_brightness;
	bd = backlight_device_रेजिस्टर("acer-wmi", dev, शून्य, &acer_bl_ops,
				       &props);
	अगर (IS_ERR(bd)) अणु
		pr_err("Could not register Acer backlight device\n");
		acer_backlight_device = शून्य;
		वापस PTR_ERR(bd);
	पूर्ण

	acer_backlight_device = bd;

	bd->props.घातer = FB_BLANK_UNBLANK;
	bd->props.brightness = पढ़ो_brightness(bd);
	backlight_update_status(bd);
	वापस 0;
पूर्ण

अटल व्योम acer_backlight_निकास(व्योम)
अणु
	backlight_device_unरेजिस्टर(acer_backlight_device);
पूर्ण

/*
 * Accelerometer device
 */
अटल acpi_handle gsensor_handle;

अटल पूर्णांक acer_gsensor_init(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_buffer output;
	जोड़ acpi_object out_obj;

	output.length = माप(out_obj);
	output.poपूर्णांकer = &out_obj;
	status = acpi_evaluate_object(gsensor_handle, "_INI", शून्य, &output);
	अगर (ACPI_FAILURE(status))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक acer_gsensor_खोलो(काष्ठा input_dev *input)
अणु
	वापस acer_gsensor_init();
पूर्ण

अटल पूर्णांक acer_gsensor_event(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_buffer output;
	जोड़ acpi_object out_obj[5];

	अगर (!acer_wmi_accel_dev)
		वापस -1;

	output.length = माप(out_obj);
	output.poपूर्णांकer = out_obj;

	status = acpi_evaluate_object(gsensor_handle, "RDVL", शून्य, &output);
	अगर (ACPI_FAILURE(status))
		वापस -1;

	अगर (out_obj->package.count != 4)
		वापस -1;

	input_report_असल(acer_wmi_accel_dev, ABS_X,
		(s16)out_obj->package.elements[0].पूर्णांकeger.value);
	input_report_असल(acer_wmi_accel_dev, ABS_Y,
		(s16)out_obj->package.elements[1].पूर्णांकeger.value);
	input_report_असल(acer_wmi_accel_dev, ABS_Z,
		(s16)out_obj->package.elements[2].पूर्णांकeger.value);
	input_sync(acer_wmi_accel_dev);
	वापस 0;
पूर्ण

/*
 * Switch series keyboard करोck status
 */
अटल पूर्णांक acer_kbd_करोck_state_to_sw_tablet_mode(u8 kbd_करोck_state)
अणु
	चयन (kbd_करोck_state) अणु
	हाल 0x01: /* Docked, traditional clamshell laptop mode */
		वापस 0;
	हाल 0x04: /* Stand-alone tablet */
	हाल 0x40: /* Docked, tent mode, keyboard not usable */
		वापस 1;
	शेष:
		pr_warn("Unknown kbd_dock_state 0x%02x\n", kbd_करोck_state);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम acer_kbd_करोck_get_initial_state(व्योम)
अणु
	u8 *output, input[8] = अणु 0x05, 0x00, पूर्ण;
	काष्ठा acpi_buffer input_buf = अणु माप(input), input पूर्ण;
	काष्ठा acpi_buffer output_buf = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;
	पूर्णांक sw_tablet_mode;

	status = wmi_evaluate_method(WMID_GUID3, 0, 0x2, &input_buf, &output_buf);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Error getting keyboard-dock initial status: %s\n",
		       acpi_क्रमmat_exception(status));
		वापस;
	पूर्ण

	obj = output_buf.poपूर्णांकer;
	अगर (!obj || obj->type != ACPI_TYPE_BUFFER || obj->buffer.length != 8) अणु
		pr_err("Unexpected output format getting keyboard-dock initial status\n");
		जाओ out_मुक्त_obj;
	पूर्ण

	output = obj->buffer.poपूर्णांकer;
	अगर (output[0] != 0x00 || (output[3] != 0x05 && output[3] != 0x45)) अणु
		pr_err("Unexpected output [0]=0x%02x [3]=0x%02x getting keyboard-dock initial status\n",
		       output[0], output[3]);
		जाओ out_मुक्त_obj;
	पूर्ण

	sw_tablet_mode = acer_kbd_करोck_state_to_sw_tablet_mode(output[4]);
	input_report_चयन(acer_wmi_input_dev, SW_TABLET_MODE, sw_tablet_mode);

out_मुक्त_obj:
	kमुक्त(obj);
पूर्ण

अटल व्योम acer_kbd_करोck_event(स्थिर काष्ठा event_वापस_value *event)
अणु
	पूर्णांक sw_tablet_mode;

	अगर (!has_cap(ACER_CAP_KBD_DOCK))
		वापस;

	sw_tablet_mode = acer_kbd_करोck_state_to_sw_tablet_mode(event->kbd_करोck_state);
	input_report_चयन(acer_wmi_input_dev, SW_TABLET_MODE, sw_tablet_mode);
	input_sync(acer_wmi_input_dev);
पूर्ण

/*
 * Rfसमाप्त devices
 */
अटल व्योम acer_rfसमाप्त_update(काष्ठा work_काष्ठा *ignored);
अटल DECLARE_DELAYED_WORK(acer_rfसमाप्त_work, acer_rfसमाप्त_update);
अटल व्योम acer_rfसमाप्त_update(काष्ठा work_काष्ठा *ignored)
अणु
	u32 state;
	acpi_status status;

	अगर (has_cap(ACER_CAP_WIRELESS)) अणु
		status = get_u32(&state, ACER_CAP_WIRELESS);
		अगर (ACPI_SUCCESS(status)) अणु
			अगर (quirks->wireless == 3)
				rfसमाप्त_set_hw_state(wireless_rfसमाप्त, !state);
			अन्यथा
				rfसमाप्त_set_sw_state(wireless_rfसमाप्त, !state);
		पूर्ण
	पूर्ण

	अगर (has_cap(ACER_CAP_BLUETOOTH)) अणु
		status = get_u32(&state, ACER_CAP_BLUETOOTH);
		अगर (ACPI_SUCCESS(status))
			rfसमाप्त_set_sw_state(bluetooth_rfसमाप्त, !state);
	पूर्ण

	अगर (has_cap(ACER_CAP_THREEG) && wmi_has_guid(WMID_GUID3)) अणु
		status = get_u32(&state, ACER_WMID3_GDS_THREEG);
		अगर (ACPI_SUCCESS(status))
			rfसमाप्त_set_sw_state(threeg_rfसमाप्त, !state);
	पूर्ण

	schedule_delayed_work(&acer_rfसमाप्त_work, round_jअगरfies_relative(HZ));
पूर्ण

अटल पूर्णांक acer_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	acpi_status status;
	u32 cap = (अचिन्हित दीर्घ)data;

	अगर (rfसमाप्त_inited) अणु
		status = set_u32(!blocked, cap);
		अगर (ACPI_FAILURE(status))
			वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops acer_rfसमाप्त_ops = अणु
	.set_block = acer_rfसमाप्त_set,
पूर्ण;

अटल काष्ठा rfसमाप्त *acer_rfसमाप्त_रेजिस्टर(काष्ठा device *dev,
					   क्रमागत rfसमाप्त_type type,
					   अक्षर *name, u32 cap)
अणु
	पूर्णांक err;
	काष्ठा rfसमाप्त *rfसमाप्त_dev;
	u32 state;
	acpi_status status;

	rfसमाप्त_dev = rfसमाप्त_alloc(name, dev, type,
				  &acer_rfसमाप्त_ops,
				  (व्योम *)(अचिन्हित दीर्घ)cap);
	अगर (!rfसमाप्त_dev)
		वापस ERR_PTR(-ENOMEM);

	status = get_u32(&state, cap);

	err = rfसमाप्त_रेजिस्टर(rfसमाप्त_dev);
	अगर (err) अणु
		rfसमाप्त_destroy(rfसमाप्त_dev);
		वापस ERR_PTR(err);
	पूर्ण

	अगर (ACPI_SUCCESS(status))
		rfसमाप्त_set_sw_state(rfसमाप्त_dev, !state);

	वापस rfसमाप्त_dev;
पूर्ण

अटल पूर्णांक acer_rfसमाप्त_init(काष्ठा device *dev)
अणु
	पूर्णांक err;

	अगर (has_cap(ACER_CAP_WIRELESS)) अणु
		wireless_rfसमाप्त = acer_rfसमाप्त_रेजिस्टर(dev, RFKILL_TYPE_WLAN,
			"acer-wireless", ACER_CAP_WIRELESS);
		अगर (IS_ERR(wireless_rfसमाप्त)) अणु
			err = PTR_ERR(wireless_rfसमाप्त);
			जाओ error_wireless;
		पूर्ण
	पूर्ण

	अगर (has_cap(ACER_CAP_BLUETOOTH)) अणु
		bluetooth_rfसमाप्त = acer_rfसमाप्त_रेजिस्टर(dev,
			RFKILL_TYPE_BLUETOOTH, "acer-bluetooth",
			ACER_CAP_BLUETOOTH);
		अगर (IS_ERR(bluetooth_rfसमाप्त)) अणु
			err = PTR_ERR(bluetooth_rfसमाप्त);
			जाओ error_bluetooth;
		पूर्ण
	पूर्ण

	अगर (has_cap(ACER_CAP_THREEG)) अणु
		threeg_rfसमाप्त = acer_rfसमाप्त_रेजिस्टर(dev,
			RFKILL_TYPE_WWAN, "acer-threeg",
			ACER_CAP_THREEG);
		अगर (IS_ERR(threeg_rfसमाप्त)) अणु
			err = PTR_ERR(threeg_rfसमाप्त);
			जाओ error_threeg;
		पूर्ण
	पूर्ण

	rfसमाप्त_inited = true;

	अगर ((ec_raw_mode || !wmi_has_guid(ACERWMID_EVENT_GUID)) &&
	    has_cap(ACER_CAP_WIRELESS | ACER_CAP_BLUETOOTH | ACER_CAP_THREEG))
		schedule_delayed_work(&acer_rfसमाप्त_work,
			round_jअगरfies_relative(HZ));

	वापस 0;

error_threeg:
	अगर (has_cap(ACER_CAP_BLUETOOTH)) अणु
		rfसमाप्त_unरेजिस्टर(bluetooth_rfसमाप्त);
		rfसमाप्त_destroy(bluetooth_rfसमाप्त);
	पूर्ण
error_bluetooth:
	अगर (has_cap(ACER_CAP_WIRELESS)) अणु
		rfसमाप्त_unरेजिस्टर(wireless_rfसमाप्त);
		rfसमाप्त_destroy(wireless_rfसमाप्त);
	पूर्ण
error_wireless:
	वापस err;
पूर्ण

अटल व्योम acer_rfसमाप्त_निकास(व्योम)
अणु
	अगर ((ec_raw_mode || !wmi_has_guid(ACERWMID_EVENT_GUID)) &&
	    has_cap(ACER_CAP_WIRELESS | ACER_CAP_BLUETOOTH | ACER_CAP_THREEG))
		cancel_delayed_work_sync(&acer_rfसमाप्त_work);

	अगर (has_cap(ACER_CAP_WIRELESS)) अणु
		rfसमाप्त_unरेजिस्टर(wireless_rfसमाप्त);
		rfसमाप्त_destroy(wireless_rfसमाप्त);
	पूर्ण

	अगर (has_cap(ACER_CAP_BLUETOOTH)) अणु
		rfसमाप्त_unरेजिस्टर(bluetooth_rfसमाप्त);
		rfसमाप्त_destroy(bluetooth_rfसमाप्त);
	पूर्ण

	अगर (has_cap(ACER_CAP_THREEG)) अणु
		rfसमाप्त_unरेजिस्टर(threeg_rfसमाप्त);
		rfसमाप्त_destroy(threeg_rfसमाप्त);
	पूर्ण
	वापस;
पूर्ण

अटल व्योम acer_wmi_notअगरy(u32 value, व्योम *context)
अणु
	काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	काष्ठा event_वापस_value वापस_value;
	acpi_status status;
	u16 device_state;
	स्थिर काष्ठा key_entry *key;
	u32 scancode;

	status = wmi_get_event_data(value, &response);
	अगर (status != AE_OK) अणु
		pr_warn("bad event status 0x%x\n", status);
		वापस;
	पूर्ण

	obj = (जोड़ acpi_object *)response.poपूर्णांकer;

	अगर (!obj)
		वापस;
	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		pr_warn("Unknown response received %d\n", obj->type);
		kमुक्त(obj);
		वापस;
	पूर्ण
	अगर (obj->buffer.length != 8) अणु
		pr_warn("Unknown buffer length %d\n", obj->buffer.length);
		kमुक्त(obj);
		वापस;
	पूर्ण

	वापस_value = *((काष्ठा event_वापस_value *)obj->buffer.poपूर्णांकer);
	kमुक्त(obj);

	चयन (वापस_value.function) अणु
	हाल WMID_HOTKEY_EVENT:
		device_state = वापस_value.device_state;
		pr_debug("device state: 0x%x\n", device_state);

		key = sparse_keymap_entry_from_scancode(acer_wmi_input_dev,
							वापस_value.key_num);
		अगर (!key) अणु
			pr_warn("Unknown key number - 0x%x\n",
				वापस_value.key_num);
		पूर्ण अन्यथा अणु
			scancode = वापस_value.key_num;
			चयन (key->keycode) अणु
			हाल KEY_WLAN:
			हाल KEY_BLUETOOTH:
				अगर (has_cap(ACER_CAP_WIRELESS))
					rfसमाप्त_set_sw_state(wireless_rfसमाप्त,
						!(device_state & ACER_WMID3_GDS_WIRELESS));
				अगर (has_cap(ACER_CAP_THREEG))
					rfसमाप्त_set_sw_state(threeg_rfसमाप्त,
						!(device_state & ACER_WMID3_GDS_THREEG));
				अगर (has_cap(ACER_CAP_BLUETOOTH))
					rfसमाप्त_set_sw_state(bluetooth_rfसमाप्त,
						!(device_state & ACER_WMID3_GDS_BLUETOOTH));
				अवरोध;
			हाल KEY_TOUCHPAD_TOGGLE:
				scancode = (device_state & ACER_WMID3_GDS_TOUCHPAD) ?
						KEY_TOUCHPAD_ON : KEY_TOUCHPAD_OFF;
			पूर्ण
			sparse_keymap_report_event(acer_wmi_input_dev, scancode, 1, true);
		पूर्ण
		अवरोध;
	हाल WMID_ACCEL_OR_KBD_DOCK_EVENT:
		acer_gsensor_event();
		acer_kbd_करोck_event(&वापस_value);
		अवरोध;
	शेष:
		pr_warn("Unknown function number - %d - %d\n",
			वापस_value.function, वापस_value.key_num);
		अवरोध;
	पूर्ण
पूर्ण

अटल acpi_status __init
wmid3_set_function_mode(काष्ठा func_input_params *params,
			काष्ठा func_वापस_value *वापस_value)
अणु
	acpi_status status;
	जोड़ acpi_object *obj;

	काष्ठा acpi_buffer input = अणु माप(काष्ठा func_input_params), params पूर्ण;
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	status = wmi_evaluate_method(WMID_GUID3, 0, 0x1, &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = output.poपूर्णांकer;

	अगर (!obj)
		वापस AE_ERROR;
	अन्यथा अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		kमुक्त(obj);
		वापस AE_ERROR;
	पूर्ण
	अगर (obj->buffer.length != 4) अणु
		pr_warn("Unknown buffer length %d\n", obj->buffer.length);
		kमुक्त(obj);
		वापस AE_ERROR;
	पूर्ण

	*वापस_value = *((काष्ठा func_वापस_value *)obj->buffer.poपूर्णांकer);
	kमुक्त(obj);

	वापस status;
पूर्ण

अटल पूर्णांक __init acer_wmi_enable_ec_raw(व्योम)
अणु
	काष्ठा func_वापस_value वापस_value;
	acpi_status status;
	काष्ठा func_input_params params = अणु
		.function_num = 0x1,
		.commun_devices = 0xFFFF,
		.devices = 0xFFFF,
		.app_status = 0x00,		/* Launch Manager Deactive */
		.app_mask = 0x01,
	पूर्ण;

	status = wmid3_set_function_mode(&params, &वापस_value);

	अगर (वापस_value.error_code || वापस_value.ec_वापस_value)
		pr_warn("Enabling EC raw mode failed: 0x%x - 0x%x\n",
			वापस_value.error_code,
			वापस_value.ec_वापस_value);
	अन्यथा
		pr_info("Enabled EC raw mode\n");

	वापस status;
पूर्ण

अटल पूर्णांक __init acer_wmi_enable_lm(व्योम)
अणु
	काष्ठा func_वापस_value वापस_value;
	acpi_status status;
	काष्ठा func_input_params params = अणु
		.function_num = 0x1,
		.commun_devices = 0xFFFF,
		.devices = 0xFFFF,
		.app_status = 0x01,            /* Launch Manager Active */
		.app_mask = 0x01,
	पूर्ण;

	status = wmid3_set_function_mode(&params, &वापस_value);

	अगर (वापस_value.error_code || वापस_value.ec_वापस_value)
		pr_warn("Enabling Launch Manager failed: 0x%x - 0x%x\n",
			वापस_value.error_code,
			वापस_value.ec_वापस_value);

	वापस status;
पूर्ण

अटल पूर्णांक __init acer_wmi_enable_rf_button(व्योम)
अणु
	काष्ठा func_वापस_value वापस_value;
	acpi_status status;
	काष्ठा func_input_params params = अणु
		.function_num = 0x1,
		.commun_devices = 0xFFFF,
		.devices = 0xFFFF,
		.app_status = 0x10,            /* RF Button Active */
		.app_mask = 0x10,
	पूर्ण;

	status = wmid3_set_function_mode(&params, &वापस_value);

	अगर (वापस_value.error_code || वापस_value.ec_वापस_value)
		pr_warn("Enabling RF Button failed: 0x%x - 0x%x\n",
			वापस_value.error_code,
			वापस_value.ec_वापस_value);

	वापस status;
पूर्ण

अटल पूर्णांक __init acer_wmi_accel_setup(व्योम)
अणु
	काष्ठा acpi_device *adev;
	पूर्णांक err;

	adev = acpi_dev_get_first_match_dev("BST0001", शून्य, -1);
	अगर (!adev)
		वापस -ENODEV;

	gsensor_handle = acpi_device_handle(adev);
	acpi_dev_put(adev);

	acer_wmi_accel_dev = input_allocate_device();
	अगर (!acer_wmi_accel_dev)
		वापस -ENOMEM;

	acer_wmi_accel_dev->खोलो = acer_gsensor_खोलो;

	acer_wmi_accel_dev->name = "Acer BMA150 accelerometer";
	acer_wmi_accel_dev->phys = "wmi/input1";
	acer_wmi_accel_dev->id.bustype = BUS_HOST;
	acer_wmi_accel_dev->evbit[0] = BIT_MASK(EV_ABS);
	input_set_असल_params(acer_wmi_accel_dev, ABS_X, -16384, 16384, 0, 0);
	input_set_असल_params(acer_wmi_accel_dev, ABS_Y, -16384, 16384, 0, 0);
	input_set_असल_params(acer_wmi_accel_dev, ABS_Z, -16384, 16384, 0, 0);

	err = input_रेजिस्टर_device(acer_wmi_accel_dev);
	अगर (err)
		जाओ err_मुक्त_dev;

	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(acer_wmi_accel_dev);
	वापस err;
पूर्ण

अटल पूर्णांक __init acer_wmi_input_setup(व्योम)
अणु
	acpi_status status;
	पूर्णांक err;

	acer_wmi_input_dev = input_allocate_device();
	अगर (!acer_wmi_input_dev)
		वापस -ENOMEM;

	acer_wmi_input_dev->name = "Acer WMI hotkeys";
	acer_wmi_input_dev->phys = "wmi/input0";
	acer_wmi_input_dev->id.bustype = BUS_HOST;

	err = sparse_keymap_setup(acer_wmi_input_dev, acer_wmi_keymap, शून्य);
	अगर (err)
		जाओ err_मुक्त_dev;

	अगर (has_cap(ACER_CAP_KBD_DOCK))
		input_set_capability(acer_wmi_input_dev, EV_SW, SW_TABLET_MODE);

	status = wmi_install_notअगरy_handler(ACERWMID_EVENT_GUID,
						acer_wmi_notअगरy, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		err = -EIO;
		जाओ err_मुक्त_dev;
	पूर्ण

	अगर (has_cap(ACER_CAP_KBD_DOCK))
		acer_kbd_करोck_get_initial_state();

	err = input_रेजिस्टर_device(acer_wmi_input_dev);
	अगर (err)
		जाओ err_uninstall_notअगरier;

	वापस 0;

err_uninstall_notअगरier:
	wmi_हटाओ_notअगरy_handler(ACERWMID_EVENT_GUID);
err_मुक्त_dev:
	input_मुक्त_device(acer_wmi_input_dev);
	वापस err;
पूर्ण

अटल व्योम acer_wmi_input_destroy(व्योम)
अणु
	wmi_हटाओ_notअगरy_handler(ACERWMID_EVENT_GUID);
	input_unरेजिस्टर_device(acer_wmi_input_dev);
पूर्ण

/*
 * debugfs functions
 */
अटल u32 get_wmid_devices(व्योम)
अणु
	काष्ठा acpi_buffer out = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;
	u32 devices = 0;

	status = wmi_query_block(WMID_GUID2, 0, &out);
	अगर (ACPI_FAILURE(status))
		वापस 0;

	obj = (जोड़ acpi_object *) out.poपूर्णांकer;
	अगर (obj) अणु
		अगर (obj->type == ACPI_TYPE_BUFFER &&
			(obj->buffer.length == माप(u32) ||
			obj->buffer.length == माप(u64))) अणु
			devices = *((u32 *) obj->buffer.poपूर्णांकer);
		पूर्ण अन्यथा अगर (obj->type == ACPI_TYPE_INTEGER) अणु
			devices = (u32) obj->पूर्णांकeger.value;
		पूर्ण
	पूर्ण

	kमुक्त(out.poपूर्णांकer);
	वापस devices;
पूर्ण

/*
 * Platक्रमm device
 */
अटल पूर्णांक acer_platक्रमm_probe(काष्ठा platक्रमm_device *device)
अणु
	पूर्णांक err;

	अगर (has_cap(ACER_CAP_MAILLED)) अणु
		err = acer_led_init(&device->dev);
		अगर (err)
			जाओ error_mailled;
	पूर्ण

	अगर (has_cap(ACER_CAP_BRIGHTNESS)) अणु
		err = acer_backlight_init(&device->dev);
		अगर (err)
			जाओ error_brightness;
	पूर्ण

	err = acer_rfसमाप्त_init(&device->dev);
	अगर (err)
		जाओ error_rfसमाप्त;

	वापस err;

error_rfसमाप्त:
	अगर (has_cap(ACER_CAP_BRIGHTNESS))
		acer_backlight_निकास();
error_brightness:
	अगर (has_cap(ACER_CAP_MAILLED))
		acer_led_निकास();
error_mailled:
	वापस err;
पूर्ण

अटल पूर्णांक acer_platक्रमm_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	अगर (has_cap(ACER_CAP_MAILLED))
		acer_led_निकास();
	अगर (has_cap(ACER_CAP_BRIGHTNESS))
		acer_backlight_निकास();

	acer_rfसमाप्त_निकास();
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acer_suspend(काष्ठा device *dev)
अणु
	u32 value;
	काष्ठा acer_data *data = &पूर्णांकerface->data;

	अगर (!data)
		वापस -ENOMEM;

	अगर (has_cap(ACER_CAP_MAILLED)) अणु
		get_u32(&value, ACER_CAP_MAILLED);
		set_u32(LED_OFF, ACER_CAP_MAILLED);
		data->mailled = value;
	पूर्ण

	अगर (has_cap(ACER_CAP_BRIGHTNESS)) अणु
		get_u32(&value, ACER_CAP_BRIGHTNESS);
		data->brightness = value;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acer_resume(काष्ठा device *dev)
अणु
	काष्ठा acer_data *data = &पूर्णांकerface->data;

	अगर (!data)
		वापस -ENOMEM;

	अगर (has_cap(ACER_CAP_MAILLED))
		set_u32(data->mailled, ACER_CAP_MAILLED);

	अगर (has_cap(ACER_CAP_BRIGHTNESS))
		set_u32(data->brightness, ACER_CAP_BRIGHTNESS);

	अगर (acer_wmi_accel_dev)
		acer_gsensor_init();

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा acer_suspend	शून्य
#घोषणा acer_resume	शून्य
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(acer_pm, acer_suspend, acer_resume);

अटल व्योम acer_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा acer_data *data = &पूर्णांकerface->data;

	अगर (!data)
		वापस;

	अगर (has_cap(ACER_CAP_MAILLED))
		set_u32(LED_OFF, ACER_CAP_MAILLED);
पूर्ण

अटल काष्ठा platक्रमm_driver acer_platक्रमm_driver = अणु
	.driver = अणु
		.name = "acer-wmi",
		.pm = &acer_pm,
	पूर्ण,
	.probe = acer_platक्रमm_probe,
	.हटाओ = acer_platक्रमm_हटाओ,
	.shutकरोwn = acer_platक्रमm_shutकरोwn,
पूर्ण;

अटल काष्ठा platक्रमm_device *acer_platक्रमm_device;

अटल व्योम हटाओ_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(पूर्णांकerface->debug.root);
पूर्ण

अटल व्योम __init create_debugfs(व्योम)
अणु
	पूर्णांकerface->debug.root = debugfs_create_dir("acer-wmi", शून्य);

	debugfs_create_u32("devices", S_IRUGO, पूर्णांकerface->debug.root,
			   &पूर्णांकerface->debug.wmid_devices);
पूर्ण

अटल पूर्णांक __init acer_wmi_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("Acer Laptop ACPI-WMI Extras\n");

	अगर (dmi_check_प्रणाली(acer_blacklist)) अणु
		pr_info("Blacklisted hardware detected - not loading\n");
		वापस -ENODEV;
	पूर्ण

	find_quirks();

	/*
	 * The AMW0_GUID1 wmi is not only found on Acer family but also other
	 * machines like Lenovo, Fujitsu and Medion. In the past days,
	 * acer-wmi driver handled those non-Acer machines by quirks list.
	 * But actually acer-wmi driver was loaded on any machines that have
	 * AMW0_GUID1. This behavior is strange because those machines should
	 * be supported by appropriate wmi drivers. e.g. fujitsu-laptop,
	 * ideapad-laptop. So, here checks the machine that has AMW0_GUID1
	 * should be in Acer/Gateway/Packard Bell white list, or it's alपढ़ोy
	 * in the past quirk list.
	 */
	अगर (wmi_has_guid(AMW0_GUID1) &&
	    !dmi_check_प्रणाली(amw0_whitelist) &&
	    quirks == &quirk_unknown) अणु
		pr_debug("Unsupported machine has AMW0_GUID1, unable to load\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Detect which ACPI-WMI पूर्णांकerface we're using.
	 */
	अगर (wmi_has_guid(AMW0_GUID1) && wmi_has_guid(WMID_GUID1))
		पूर्णांकerface = &AMW0_V2_पूर्णांकerface;

	अगर (!wmi_has_guid(AMW0_GUID1) && wmi_has_guid(WMID_GUID1))
		पूर्णांकerface = &wmid_पूर्णांकerface;

	अगर (wmi_has_guid(WMID_GUID3))
		पूर्णांकerface = &wmid_v2_पूर्णांकerface;

	अगर (पूर्णांकerface)
		dmi_walk(type_aa_dmi_decode, शून्य);

	अगर (wmi_has_guid(WMID_GUID2) && पूर्णांकerface) अणु
		अगर (!has_type_aa && ACPI_FAILURE(WMID_set_capabilities())) अणु
			pr_err("Unable to detect available WMID devices\n");
			वापस -ENODEV;
		पूर्ण
		/* WMID always provides brightness methods */
		पूर्णांकerface->capability |= ACER_CAP_BRIGHTNESS;
	पूर्ण अन्यथा अगर (!wmi_has_guid(WMID_GUID2) && पूर्णांकerface && !has_type_aa && क्रमce_caps == -1) अणु
		pr_err("No WMID device detection method found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (wmi_has_guid(AMW0_GUID1) && !wmi_has_guid(WMID_GUID1)) अणु
		पूर्णांकerface = &AMW0_पूर्णांकerface;

		अगर (ACPI_FAILURE(AMW0_set_capabilities())) अणु
			pr_err("Unable to detect available AMW0 devices\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (wmi_has_guid(AMW0_GUID1))
		AMW0_find_mailled();

	अगर (!पूर्णांकerface) अणु
		pr_err("No or unsupported WMI interface, unable to load\n");
		वापस -ENODEV;
	पूर्ण

	set_quirks();

	अगर (dmi_check_प्रणाली(video_venकरोr_dmi_table))
		acpi_video_set_dmi_backlight_type(acpi_backlight_venकरोr);

	अगर (acpi_video_get_backlight_type() != acpi_backlight_venकरोr)
		पूर्णांकerface->capability &= ~ACER_CAP_BRIGHTNESS;

	अगर (wmi_has_guid(WMID_GUID3))
		पूर्णांकerface->capability |= ACER_CAP_SET_FUNCTION_MODE;

	अगर (क्रमce_caps != -1)
		पूर्णांकerface->capability = क्रमce_caps;

	अगर (wmi_has_guid(WMID_GUID3) &&
	    (पूर्णांकerface->capability & ACER_CAP_SET_FUNCTION_MODE)) अणु
		अगर (ACPI_FAILURE(acer_wmi_enable_rf_button()))
			pr_warn("Cannot enable RF Button Driver\n");

		अगर (ec_raw_mode) अणु
			अगर (ACPI_FAILURE(acer_wmi_enable_ec_raw())) अणु
				pr_err("Cannot enable EC raw mode\n");
				वापस -ENODEV;
			पूर्ण
		पूर्ण अन्यथा अगर (ACPI_FAILURE(acer_wmi_enable_lm())) अणु
			pr_err("Cannot enable Launch Manager mode\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर (ec_raw_mode) अणु
		pr_info("No WMID EC raw mode enable method\n");
	पूर्ण

	अगर (wmi_has_guid(ACERWMID_EVENT_GUID)) अणु
		err = acer_wmi_input_setup();
		अगर (err)
			वापस err;
		err = acer_wmi_accel_setup();
		अगर (err && err != -ENODEV)
			pr_warn("Cannot enable accelerometer\n");
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&acer_platक्रमm_driver);
	अगर (err) अणु
		pr_err("Unable to register platform driver\n");
		जाओ error_platक्रमm_रेजिस्टर;
	पूर्ण

	acer_platक्रमm_device = platक्रमm_device_alloc("acer-wmi", -1);
	अगर (!acer_platक्रमm_device) अणु
		err = -ENOMEM;
		जाओ error_device_alloc;
	पूर्ण

	err = platक्रमm_device_add(acer_platक्रमm_device);
	अगर (err)
		जाओ error_device_add;

	अगर (wmi_has_guid(WMID_GUID2)) अणु
		पूर्णांकerface->debug.wmid_devices = get_wmid_devices();
		create_debugfs();
	पूर्ण

	/* Override any initial settings with values from the commandline */
	acer_commandline_init();

	वापस 0;

error_device_add:
	platक्रमm_device_put(acer_platक्रमm_device);
error_device_alloc:
	platक्रमm_driver_unरेजिस्टर(&acer_platक्रमm_driver);
error_platक्रमm_रेजिस्टर:
	अगर (wmi_has_guid(ACERWMID_EVENT_GUID))
		acer_wmi_input_destroy();
	अगर (acer_wmi_accel_dev)
		input_unरेजिस्टर_device(acer_wmi_accel_dev);

	वापस err;
पूर्ण

अटल व्योम __निकास acer_wmi_निकास(व्योम)
अणु
	अगर (wmi_has_guid(ACERWMID_EVENT_GUID))
		acer_wmi_input_destroy();

	अगर (acer_wmi_accel_dev)
		input_unरेजिस्टर_device(acer_wmi_accel_dev);

	हटाओ_debugfs();
	platक्रमm_device_unरेजिस्टर(acer_platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&acer_platक्रमm_driver);

	pr_info("Acer Laptop WMI Extras unloaded\n");
	वापस;
पूर्ण

module_init(acer_wmi_init);
module_निकास(acer_wmi_निकास);
