<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *  Copyright (c) 2006-2007 Jiri Kosina
 */
/*
 *
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@ucw.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Reखुला
 */
#अगर_अघोषित __HID_H
#घोषणा __HID_H


#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/mod_devicetable.h> /* hid_device_id */
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/input.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/mutex.h>
#समावेश <linux/घातer_supply.h>
#समावेश <uapi/linux/hid.h>

/*
 * We parse each description item पूर्णांकo this काष्ठाure. Short items data
 * values are expanded to 32-bit चिन्हित पूर्णांक, दीर्घ items contain a poपूर्णांकer
 * पूर्णांकo the data area.
 */

काष्ठा hid_item अणु
	अचिन्हित  क्रमmat;
	__u8      size;
	__u8      type;
	__u8      tag;
	जोड़ अणु
	    __u8   u8;
	    __s8   s8;
	    __u16  u16;
	    __s16  s16;
	    __u32  u32;
	    __s32  s32;
	    __u8  *दीर्घdata;
	पूर्ण data;
पूर्ण;

/*
 * HID report item क्रमmat
 */

#घोषणा HID_ITEM_FORMAT_SHORT	0
#घोषणा HID_ITEM_FORMAT_LONG	1

/*
 * Special tag indicating दीर्घ items
 */

#घोषणा HID_ITEM_TAG_LONG	15

/*
 * HID report descriptor item type (prefix bit 2,3)
 */

#घोषणा HID_ITEM_TYPE_MAIN		0
#घोषणा HID_ITEM_TYPE_GLOBAL		1
#घोषणा HID_ITEM_TYPE_LOCAL		2
#घोषणा HID_ITEM_TYPE_RESERVED		3

/*
 * HID report descriptor मुख्य item tags
 */

#घोषणा HID_MAIN_ITEM_TAG_INPUT			8
#घोषणा HID_MAIN_ITEM_TAG_OUTPUT		9
#घोषणा HID_MAIN_ITEM_TAG_FEATURE		11
#घोषणा HID_MAIN_ITEM_TAG_BEGIN_COLLECTION	10
#घोषणा HID_MAIN_ITEM_TAG_END_COLLECTION	12

/*
 * HID report descriptor मुख्य item contents
 */

#घोषणा HID_MAIN_ITEM_CONSTANT		0x001
#घोषणा HID_MAIN_ITEM_VARIABLE		0x002
#घोषणा HID_MAIN_ITEM_RELATIVE		0x004
#घोषणा HID_MAIN_ITEM_WRAP		0x008
#घोषणा HID_MAIN_ITEM_NONLINEAR		0x010
#घोषणा HID_MAIN_ITEM_NO_PREFERRED	0x020
#घोषणा HID_MAIN_ITEM_शून्य_STATE	0x040
#घोषणा HID_MAIN_ITEM_VOLATILE		0x080
#घोषणा HID_MAIN_ITEM_BUFFERED_BYTE	0x100

/*
 * HID report descriptor collection item types
 */

#घोषणा HID_COLLECTION_PHYSICAL		0
#घोषणा HID_COLLECTION_APPLICATION	1
#घोषणा HID_COLLECTION_LOGICAL		2

/*
 * HID report descriptor global item tags
 */

#घोषणा HID_GLOBAL_ITEM_TAG_USAGE_PAGE		0
#घोषणा HID_GLOBAL_ITEM_TAG_LOGICAL_MINIMUM	1
#घोषणा HID_GLOBAL_ITEM_TAG_LOGICAL_MAXIMUM	2
#घोषणा HID_GLOBAL_ITEM_TAG_PHYSICAL_MINIMUM	3
#घोषणा HID_GLOBAL_ITEM_TAG_PHYSICAL_MAXIMUM	4
#घोषणा HID_GLOBAL_ITEM_TAG_UNIT_EXPONENT	5
#घोषणा HID_GLOBAL_ITEM_TAG_UNIT		6
#घोषणा HID_GLOBAL_ITEM_TAG_REPORT_SIZE		7
#घोषणा HID_GLOBAL_ITEM_TAG_REPORT_ID		8
#घोषणा HID_GLOBAL_ITEM_TAG_REPORT_COUNT	9
#घोषणा HID_GLOBAL_ITEM_TAG_PUSH		10
#घोषणा HID_GLOBAL_ITEM_TAG_POP			11

/*
 * HID report descriptor local item tags
 */

#घोषणा HID_LOCAL_ITEM_TAG_USAGE		0
#घोषणा HID_LOCAL_ITEM_TAG_USAGE_MINIMUM	1
#घोषणा HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM	2
#घोषणा HID_LOCAL_ITEM_TAG_DESIGNATOR_INDEX	3
#घोषणा HID_LOCAL_ITEM_TAG_DESIGNATOR_MINIMUM	4
#घोषणा HID_LOCAL_ITEM_TAG_DESIGNATOR_MAXIMUM	5
#घोषणा HID_LOCAL_ITEM_TAG_STRING_INDEX		7
#घोषणा HID_LOCAL_ITEM_TAG_STRING_MINIMUM	8
#घोषणा HID_LOCAL_ITEM_TAG_STRING_MAXIMUM	9
#घोषणा HID_LOCAL_ITEM_TAG_DELIMITER		10

/*
 * HID usage tables
 */

#घोषणा HID_USAGE_PAGE		0xffff0000

#घोषणा HID_UP_UNDEFINED	0x00000000
#घोषणा HID_UP_GENDESK		0x00010000
#घोषणा HID_UP_SIMULATION	0x00020000
#घोषणा HID_UP_GENDEVCTRLS	0x00060000
#घोषणा HID_UP_KEYBOARD		0x00070000
#घोषणा HID_UP_LED		0x00080000
#घोषणा HID_UP_BUTTON		0x00090000
#घोषणा HID_UP_ORDINAL		0x000a0000
#घोषणा HID_UP_TELEPHONY	0x000b0000
#घोषणा HID_UP_CONSUMER		0x000c0000
#घोषणा HID_UP_DIGITIZER	0x000d0000
#घोषणा HID_UP_PID		0x000f0000
#घोषणा HID_UP_BATTERY		0x00850000
#घोषणा HID_UP_HPVENDOR         0xff7f0000
#घोषणा HID_UP_HPVENDOR2        0xff010000
#घोषणा HID_UP_MSVENDOR		0xff000000
#घोषणा HID_UP_CUSTOM		0x00ff0000
#घोषणा HID_UP_LOGIVENDOR	0xffbc0000
#घोषणा HID_UP_LOGIVENDOR2   0xff090000
#घोषणा HID_UP_LOGIVENDOR3   0xff430000
#घोषणा HID_UP_LNVENDOR		0xffa00000
#घोषणा HID_UP_SENSOR		0x00200000
#घोषणा HID_UP_ASUSVENDOR	0xff310000
#घोषणा HID_UP_GOOGLEVENDOR	0xffd10000

#घोषणा HID_USAGE		0x0000ffff

#घोषणा HID_GD_POINTER		0x00010001
#घोषणा HID_GD_MOUSE		0x00010002
#घोषणा HID_GD_JOYSTICK		0x00010004
#घोषणा HID_GD_GAMEPAD		0x00010005
#घोषणा HID_GD_KEYBOARD		0x00010006
#घोषणा HID_GD_KEYPAD		0x00010007
#घोषणा HID_GD_MULTIAXIS	0x00010008
/*
 * Microsoft Win8 Wireless Radio Controls extensions CA, see:
 * http://www.usb.org/developers/hidpage/HUTRR40RadioHIDUsagesFinal.pdf
 */
#घोषणा HID_GD_WIRELESS_RADIO_CTLS	0x0001000c
/*
 * System Multi-Axis, see:
 * http://www.usb.org/developers/hidpage/HUTRR62_-_Generic_Desktop_CA_क्रम_System_Multi-Axis_Controllers.txt
 */
#घोषणा HID_GD_SYSTEM_MULTIAXIS	0x0001000e

#घोषणा HID_GD_X		0x00010030
#घोषणा HID_GD_Y		0x00010031
#घोषणा HID_GD_Z		0x00010032
#घोषणा HID_GD_RX		0x00010033
#घोषणा HID_GD_RY		0x00010034
#घोषणा HID_GD_RZ		0x00010035
#घोषणा HID_GD_SLIDER		0x00010036
#घोषणा HID_GD_DIAL		0x00010037
#घोषणा HID_GD_WHEEL		0x00010038
#घोषणा HID_GD_HATSWITCH	0x00010039
#घोषणा HID_GD_BUFFER		0x0001003a
#घोषणा HID_GD_BYTECOUNT	0x0001003b
#घोषणा HID_GD_MOTION		0x0001003c
#घोषणा HID_GD_START		0x0001003d
#घोषणा HID_GD_SELECT		0x0001003e
#घोषणा HID_GD_VX		0x00010040
#घोषणा HID_GD_VY		0x00010041
#घोषणा HID_GD_VZ		0x00010042
#घोषणा HID_GD_VBRX		0x00010043
#घोषणा HID_GD_VBRY		0x00010044
#घोषणा HID_GD_VBRZ		0x00010045
#घोषणा HID_GD_VNO		0x00010046
#घोषणा HID_GD_FEATURE		0x00010047
#घोषणा HID_GD_RESOLUTION_MULTIPLIER	0x00010048
#घोषणा HID_GD_SYSTEM_CONTROL	0x00010080
#घोषणा HID_GD_UP		0x00010090
#घोषणा HID_GD_DOWN		0x00010091
#घोषणा HID_GD_RIGHT		0x00010092
#घोषणा HID_GD_LEFT		0x00010093
/* Microsoft Win8 Wireless Radio Controls CA usage codes */
#घोषणा HID_GD_RFKILL_BTN	0x000100c6
#घोषणा HID_GD_RFKILL_LED	0x000100c7
#घोषणा HID_GD_RFKILL_SWITCH	0x000100c8

#घोषणा HID_DC_BATTERYSTRENGTH	0x00060020

#घोषणा HID_CP_CONSUMER_CONTROL	0x000c0001
#घोषणा HID_CP_AC_PAN		0x000c0238

#घोषणा HID_DG_DIGITIZER	0x000d0001
#घोषणा HID_DG_PEN		0x000d0002
#घोषणा HID_DG_LIGHTPEN		0x000d0003
#घोषणा HID_DG_TOUCHSCREEN	0x000d0004
#घोषणा HID_DG_TOUCHPAD		0x000d0005
#घोषणा HID_DG_WHITEBOARD	0x000d0006
#घोषणा HID_DG_STYLUS		0x000d0020
#घोषणा HID_DG_PUCK		0x000d0021
#घोषणा HID_DG_FINGER		0x000d0022
#घोषणा HID_DG_TIPPRESSURE	0x000d0030
#घोषणा HID_DG_BARRELPRESSURE	0x000d0031
#घोषणा HID_DG_INRANGE		0x000d0032
#घोषणा HID_DG_TOUCH		0x000d0033
#घोषणा HID_DG_UNTOUCH		0x000d0034
#घोषणा HID_DG_TAP		0x000d0035
#घोषणा HID_DG_TABLETFUNCTIONKEY	0x000d0039
#घोषणा HID_DG_PROGRAMCHANGEKEY	0x000d003a
#घोषणा HID_DG_BATTERYSTRENGTH	0x000d003b
#घोषणा HID_DG_INVERT		0x000d003c
#घोषणा HID_DG_TILT_X		0x000d003d
#घोषणा HID_DG_TILT_Y		0x000d003e
#घोषणा HID_DG_TWIST		0x000d0041
#घोषणा HID_DG_TIPSWITCH	0x000d0042
#घोषणा HID_DG_TIPSWITCH2	0x000d0043
#घोषणा HID_DG_BARRELSWITCH	0x000d0044
#घोषणा HID_DG_ERASER		0x000d0045
#घोषणा HID_DG_TABLETPICK	0x000d0046

#घोषणा HID_CP_CONSUMERCONTROL	0x000c0001
#घोषणा HID_CP_NUMERICKEYPAD	0x000c0002
#घोषणा HID_CP_PROGRAMMABLEBUTTONS	0x000c0003
#घोषणा HID_CP_MICROPHONE	0x000c0004
#घोषणा HID_CP_HEADPHONE	0x000c0005
#घोषणा HID_CP_GRAPHICEQUALIZER	0x000c0006
#घोषणा HID_CP_FUNCTIONBUTTONS	0x000c0036
#घोषणा HID_CP_SELECTION	0x000c0080
#घोषणा HID_CP_MEDIASELECTION	0x000c0087
#घोषणा HID_CP_SELECTDISC	0x000c00ba
#घोषणा HID_CP_VOLUMEUP		0x000c00e9
#घोषणा HID_CP_VOLUMEDOWN	0x000c00ea
#घोषणा HID_CP_PLAYBACKSPEED	0x000c00f1
#घोषणा HID_CP_PROXIMITY	0x000c0109
#घोषणा HID_CP_SPEAKERSYSTEM	0x000c0160
#घोषणा HID_CP_CHANNELLEFT	0x000c0161
#घोषणा HID_CP_CHANNELRIGHT	0x000c0162
#घोषणा HID_CP_CHANNELCENTER	0x000c0163
#घोषणा HID_CP_CHANNELFRONT	0x000c0164
#घोषणा HID_CP_CHANNELCENTERFRONT	0x000c0165
#घोषणा HID_CP_CHANNELSIDE	0x000c0166
#घोषणा HID_CP_CHANNELSURROUND	0x000c0167
#घोषणा HID_CP_CHANNELLOWFREQUENCYENHANCEMENT	0x000c0168
#घोषणा HID_CP_CHANNELTOP	0x000c0169
#घोषणा HID_CP_CHANNELUNKNOWN	0x000c016a
#घोषणा HID_CP_APPLICATIONLAUNCHBUTTONS	0x000c0180
#घोषणा HID_CP_GENERICGUIAPPLICATIONCONTROLS	0x000c0200

#घोषणा HID_DG_DEVICECONFIG	0x000d000e
#घोषणा HID_DG_DEVICESETTINGS	0x000d0023
#घोषणा HID_DG_AZIMUTH		0x000d003f
#घोषणा HID_DG_CONFIDENCE	0x000d0047
#घोषणा HID_DG_WIDTH		0x000d0048
#घोषणा HID_DG_HEIGHT		0x000d0049
#घोषणा HID_DG_CONTACTID	0x000d0051
#घोषणा HID_DG_INPUTMODE	0x000d0052
#घोषणा HID_DG_DEVICEINDEX	0x000d0053
#घोषणा HID_DG_CONTACTCOUNT	0x000d0054
#घोषणा HID_DG_CONTACTMAX	0x000d0055
#घोषणा HID_DG_SCANTIME		0x000d0056
#घोषणा HID_DG_SURFACESWITCH	0x000d0057
#घोषणा HID_DG_BUTTONSWITCH	0x000d0058
#घोषणा HID_DG_BUTTONTYPE	0x000d0059
#घोषणा HID_DG_BARRELSWITCH2	0x000d005a
#घोषणा HID_DG_TOOLSERIALNUMBER	0x000d005b
#घोषणा HID_DG_LATENCYMODE	0x000d0060

#घोषणा HID_BAT_ABSOLUTESTATखातापूर्णCHARGE	0x00850065

#घोषणा HID_VD_ASUS_CUSTOM_MEDIA_KEYS	0xff310076
/*
 * HID report types --- Ouch! HID spec says 1 2 3!
 */

#घोषणा HID_INPUT_REPORT	0
#घोषणा HID_OUTPUT_REPORT	1
#घोषणा HID_FEATURE_REPORT	2

#घोषणा HID_REPORT_TYPES	3

/*
 * HID connect requests
 */

#घोषणा HID_CONNECT_HIDINPUT		BIT(0)
#घोषणा HID_CONNECT_HIDINPUT_FORCE	BIT(1)
#घोषणा HID_CONNECT_HIDRAW		BIT(2)
#घोषणा HID_CONNECT_HIDDEV		BIT(3)
#घोषणा HID_CONNECT_HIDDEV_FORCE	BIT(4)
#घोषणा HID_CONNECT_FF			BIT(5)
#घोषणा HID_CONNECT_DRIVER		BIT(6)
#घोषणा HID_CONNECT_DEFAULT	(HID_CONNECT_HIDINPUT|HID_CONNECT_HIDRAW| \
		HID_CONNECT_HIDDEV|HID_CONNECT_FF)

/*
 * HID device quirks.
 */

/* 
 * Increase this अगर you need to configure more HID quirks at module load समय
 */
#घोषणा MAX_USBHID_BOOT_QUIRKS 4

#घोषणा HID_QUIRK_INVERT			BIT(0)
#घोषणा HID_QUIRK_NOTOUCH			BIT(1)
#घोषणा HID_QUIRK_IGNORE			BIT(2)
#घोषणा HID_QUIRK_NOGET				BIT(3)
#घोषणा HID_QUIRK_HIDDEV_FORCE			BIT(4)
#घोषणा HID_QUIRK_BADPAD			BIT(5)
#घोषणा HID_QUIRK_MULTI_INPUT			BIT(6)
#घोषणा HID_QUIRK_HIDINPUT_FORCE		BIT(7)
/* BIT(8) reserved क्रम backward compatibility, was HID_QUIRK_NO_EMPTY_INPUT */
/* BIT(9) reserved क्रम backward compatibility, was NO_INIT_INPUT_REPORTS */
#घोषणा HID_QUIRK_ALWAYS_POLL			BIT(10)
#घोषणा HID_QUIRK_INPUT_PER_APP			BIT(11)
#घोषणा HID_QUIRK_SKIP_OUTPUT_REPORTS		BIT(16)
#घोषणा HID_QUIRK_SKIP_OUTPUT_REPORT_ID		BIT(17)
#घोषणा HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP	BIT(18)
#घोषणा HID_QUIRK_HAVE_SPECIAL_DRIVER		BIT(19)
#घोषणा HID_QUIRK_INCREMENT_USAGE_ON_DUPLICATE	BIT(20)
#घोषणा HID_QUIRK_FULLSPEED_INTERVAL		BIT(28)
#घोषणा HID_QUIRK_NO_INIT_REPORTS		BIT(29)
#घोषणा HID_QUIRK_NO_IGNORE			BIT(30)
#घोषणा HID_QUIRK_NO_INPUT_SYNC			BIT(31)

/*
 * HID device groups
 *
 * Note: HID_GROUP_ANY is declared in linux/mod_devicetable.h
 * and has a value of 0x0000
 */
#घोषणा HID_GROUP_GENERIC			0x0001
#घोषणा HID_GROUP_MULTITOUCH			0x0002
#घोषणा HID_GROUP_SENSOR_HUB			0x0003
#घोषणा HID_GROUP_MULTITOUCH_WIN_8		0x0004

/*
 * Venकरोr specअगरic HID device groups
 */
#घोषणा HID_GROUP_RMI				0x0100
#घोषणा HID_GROUP_WACOM				0x0101
#घोषणा HID_GROUP_LOGITECH_DJ_DEVICE		0x0102
#घोषणा HID_GROUP_STEAM				0x0103
#घोषणा HID_GROUP_LOGITECH_27MHZ_DEVICE		0x0104
#घोषणा HID_GROUP_VIVALDI			0x0105

/*
 * HID protocol status
 */
#घोषणा HID_REPORT_PROTOCOL	1
#घोषणा HID_BOOT_PROTOCOL	0

/*
 * This is the global environment of the parser. This inक्रमmation is
 * persistent क्रम मुख्य-items. The global environment can be saved and
 * restored with PUSH/POP statements.
 */

काष्ठा hid_global अणु
	अचिन्हित usage_page;
	__s32    logical_minimum;
	__s32    logical_maximum;
	__s32    physical_minimum;
	__s32    physical_maximum;
	__s32    unit_exponent;
	अचिन्हित unit;
	अचिन्हित report_id;
	अचिन्हित report_size;
	अचिन्हित report_count;
पूर्ण;

/*
 * This is the local environment. It is persistent up the next मुख्य-item.
 */

#घोषणा HID_MAX_USAGES			12288
#घोषणा HID_DEFAULT_NUM_COLLECTIONS	16

काष्ठा hid_local अणु
	अचिन्हित usage[HID_MAX_USAGES]; /* usage array */
	u8 usage_size[HID_MAX_USAGES]; /* usage size array */
	अचिन्हित collection_index[HID_MAX_USAGES]; /* collection index array */
	अचिन्हित usage_index;
	अचिन्हित usage_minimum;
	अचिन्हित delimiter_depth;
	अचिन्हित delimiter_branch;
पूर्ण;

/*
 * This is the collection stack. We climb up the stack to determine
 * application and function of each field.
 */

काष्ठा hid_collection अणु
	पूर्णांक parent_idx; /* device->collection */
	अचिन्हित type;
	अचिन्हित usage;
	अचिन्हित level;
पूर्ण;

काष्ठा hid_usage अणु
	अचिन्हित  hid;			/* hid usage code */
	अचिन्हित  collection_index;	/* index पूर्णांकo collection array */
	अचिन्हित  usage_index;		/* index पूर्णांकo usage array */
	__s8	  resolution_multiplier;/* Effective Resolution Multiplier
					   (HUT v1.12, 4.3.1), शेष: 1 */
	/* hidinput data */
	__s8	  wheel_factor;		/* 120/resolution_multiplier */
	__u16     code;			/* input driver code */
	__u8      type;			/* input driver type */
	__s8	  hat_min;		/* hat चयन fun */
	__s8	  hat_max;		/* ditto */
	__s8	  hat_dir;		/* ditto */
	__s16	  wheel_accumulated;	/* hi-res wheel */
पूर्ण;

काष्ठा hid_input;

काष्ठा hid_field अणु
	अचिन्हित  physical;		/* physical usage क्रम this field */
	अचिन्हित  logical;		/* logical usage क्रम this field */
	अचिन्हित  application;		/* application usage क्रम this field */
	काष्ठा hid_usage *usage;	/* usage table क्रम this function */
	अचिन्हित  maxusage;		/* maximum usage index */
	अचिन्हित  flags;		/* मुख्य-item flags (i.e. अस्थिर,array,स्थिरant) */
	अचिन्हित  report_offset;	/* bit offset in the report */
	अचिन्हित  report_size;		/* size of this field in the report */
	अचिन्हित  report_count;		/* number of this field in the report */
	अचिन्हित  report_type;		/* (input,output,feature) */
	__s32    *value;		/* last known value(s) */
	__s32     logical_minimum;
	__s32     logical_maximum;
	__s32     physical_minimum;
	__s32     physical_maximum;
	__s32     unit_exponent;
	अचिन्हित  unit;
	काष्ठा hid_report *report;	/* associated report */
	अचिन्हित index;			/* index पूर्णांकo report->field[] */
	/* hidinput data */
	काष्ठा hid_input *hidinput;	/* associated input काष्ठाure */
	__u16 dpad;			/* dpad input code */
पूर्ण;

#घोषणा HID_MAX_FIELDS 256

काष्ठा hid_report अणु
	काष्ठा list_head list;
	काष्ठा list_head hidinput_list;
	अचिन्हित पूर्णांक id;				/* id of this report */
	अचिन्हित पूर्णांक type;				/* report type */
	अचिन्हित पूर्णांक application;			/* application usage क्रम this report */
	काष्ठा hid_field *field[HID_MAX_FIELDS];	/* fields of the report */
	अचिन्हित maxfield;				/* maximum valid field index */
	अचिन्हित size;					/* size of the report (bits) */
	काष्ठा hid_device *device;			/* associated device */
पूर्ण;

#घोषणा HID_MAX_IDS 256

काष्ठा hid_report_क्रमागत अणु
	अचिन्हित numbered;
	काष्ठा list_head report_list;
	काष्ठा hid_report *report_id_hash[HID_MAX_IDS];
पूर्ण;

#घोषणा HID_MIN_BUFFER_SIZE	64		/* make sure there is at least a packet size of space */
#घोषणा HID_MAX_BUFFER_SIZE	16384		/* 16kb */
#घोषणा HID_CONTROL_FIFO_SIZE	256		/* to init devices with >100 reports */
#घोषणा HID_OUTPUT_FIFO_SIZE	64

काष्ठा hid_control_fअगरo अणु
	अचिन्हित अक्षर dir;
	काष्ठा hid_report *report;
	अक्षर *raw_report;
पूर्ण;

काष्ठा hid_output_fअगरo अणु
	काष्ठा hid_report *report;
	अक्षर *raw_report;
पूर्ण;

#घोषणा HID_CLAIMED_INPUT	BIT(0)
#घोषणा HID_CLAIMED_HIDDEV	BIT(1)
#घोषणा HID_CLAIMED_HIDRAW	BIT(2)
#घोषणा HID_CLAIMED_DRIVER	BIT(3)

#घोषणा HID_STAT_ADDED		BIT(0)
#घोषणा HID_STAT_PARSED		BIT(1)
#घोषणा HID_STAT_DUP_DETECTED	BIT(2)
#घोषणा HID_STAT_REPROBED	BIT(3)

काष्ठा hid_input अणु
	काष्ठा list_head list;
	काष्ठा hid_report *report;
	काष्ठा input_dev *input;
	स्थिर अक्षर *name;
	bool रेजिस्टरed;
	काष्ठा list_head reports;	/* the list of reports */
	अचिन्हित पूर्णांक application;	/* application usage क्रम this input */
पूर्ण;

क्रमागत hid_type अणु
	HID_TYPE_OTHER = 0,
	HID_TYPE_USBMOUSE,
	HID_TYPE_USBNONE
पूर्ण;

क्रमागत hid_battery_status अणु
	HID_BATTERY_UNKNOWN = 0,
	HID_BATTERY_QUERIED,		/* Kernel explicitly queried battery strength */
	HID_BATTERY_REPORTED,		/* Device sent unsolicited battery strength report */
पूर्ण;

काष्ठा hid_driver;
काष्ठा hid_ll_driver;

काष्ठा hid_device अणु							/* device report descriptor */
	__u8 *dev_rdesc;
	अचिन्हित dev_rsize;
	__u8 *rdesc;
	अचिन्हित rsize;
	काष्ठा hid_collection *collection;				/* List of HID collections */
	अचिन्हित collection_size;					/* Number of allocated hid_collections */
	अचिन्हित maxcollection;						/* Number of parsed collections */
	अचिन्हित maxapplication;					/* Number of applications */
	__u16 bus;							/* BUS ID */
	__u16 group;							/* Report group */
	__u32 venकरोr;							/* Venकरोr ID */
	__u32 product;							/* Product ID */
	__u32 version;							/* HID version */
	क्रमागत hid_type type;						/* device type (mouse, kbd, ...) */
	अचिन्हित country;						/* HID country */
	काष्ठा hid_report_क्रमागत report_क्रमागत[HID_REPORT_TYPES];
	काष्ठा work_काष्ठा led_work;					/* delayed LED worker */

	काष्ठा semaphore driver_input_lock;				/* protects the current driver */
	काष्ठा device dev;						/* device */
	काष्ठा hid_driver *driver;

	काष्ठा hid_ll_driver *ll_driver;
	काष्ठा mutex ll_खोलो_lock;
	अचिन्हित पूर्णांक ll_खोलो_count;

#अगर_घोषित CONFIG_HID_BATTERY_STRENGTH
	/*
	 * Power supply inक्रमmation क्रम HID devices which report
	 * battery strength. घातer_supply was successfully रेजिस्टरed अगर
	 * battery is non-शून्य.
	 */
	काष्ठा घातer_supply *battery;
	__s32 battery_capacity;
	__s32 battery_min;
	__s32 battery_max;
	__s32 battery_report_type;
	__s32 battery_report_id;
	क्रमागत hid_battery_status battery_status;
	bool battery_aव्योम_query;
	kसमय_प्रकार battery_ratelimit_समय;
#पूर्ण_अगर

	अचिन्हित दीर्घ status;						/* see STAT flags above */
	अचिन्हित claimed;						/* Claimed by hidinput, hiddev? */
	अचिन्हित quirks;						/* Various quirks the device can pull on us */
	bool io_started;						/* If IO has started */

	काष्ठा list_head inमाला_दो;					/* The list of inमाला_दो */
	व्योम *hiddev;							/* The hiddev काष्ठाure */
	व्योम *hidraw;

	अक्षर name[128];							/* Device name */
	अक्षर phys[64];							/* Device physical location */
	अक्षर uniq[64];							/* Device unique identअगरier (serial #) */

	व्योम *driver_data;

	/* temporary hid_ff handling (until moved to the drivers) */
	पूर्णांक (*ff_init)(काष्ठा hid_device *);

	/* hiddev event handler */
	पूर्णांक (*hiddev_connect)(काष्ठा hid_device *, अचिन्हित पूर्णांक);
	व्योम (*hiddev_disconnect)(काष्ठा hid_device *);
	व्योम (*hiddev_hid_event) (काष्ठा hid_device *, काष्ठा hid_field *field,
				  काष्ठा hid_usage *, __s32);
	व्योम (*hiddev_report_event) (काष्ठा hid_device *, काष्ठा hid_report *);

	/* debugging support via debugfs */
	अचिन्हित लघु debug;
	काष्ठा dentry *debug_dir;
	काष्ठा dentry *debug_rdesc;
	काष्ठा dentry *debug_events;
	काष्ठा list_head debug_list;
	spinlock_t  debug_list_lock;
	रुको_queue_head_t debug_रुको;
पूर्ण;

#घोषणा to_hid_device(pdev) \
	container_of(pdev, काष्ठा hid_device, dev)

अटल अंतरभूत व्योम *hid_get_drvdata(काष्ठा hid_device *hdev)
अणु
	वापस dev_get_drvdata(&hdev->dev);
पूर्ण

अटल अंतरभूत व्योम hid_set_drvdata(काष्ठा hid_device *hdev, व्योम *data)
अणु
	dev_set_drvdata(&hdev->dev, data);
पूर्ण

#घोषणा HID_GLOBAL_STACK_SIZE 4
#घोषणा HID_COLLECTION_STACK_SIZE 4

#घोषणा HID_SCAN_FLAG_MT_WIN_8			BIT(0)
#घोषणा HID_SCAN_FLAG_VENDOR_SPECIFIC		BIT(1)
#घोषणा HID_SCAN_FLAG_GD_POINTER		BIT(2)

काष्ठा hid_parser अणु
	काष्ठा hid_global     global;
	काष्ठा hid_global     global_stack[HID_GLOBAL_STACK_SIZE];
	अचिन्हित पूर्णांक          global_stack_ptr;
	काष्ठा hid_local      local;
	अचिन्हित पूर्णांक         *collection_stack;
	अचिन्हित पूर्णांक          collection_stack_ptr;
	अचिन्हित पूर्णांक          collection_stack_size;
	काष्ठा hid_device    *device;
	अचिन्हित पूर्णांक          scan_flags;
पूर्ण;

काष्ठा hid_class_descriptor अणु
	__u8  bDescriptorType;
	__le16 wDescriptorLength;
पूर्ण __attribute__ ((packed));

काष्ठा hid_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__le16 bcdHID;
	__u8  bCountryCode;
	__u8  bNumDescriptors;

	काष्ठा hid_class_descriptor desc[1];
पूर्ण __attribute__ ((packed));

#घोषणा HID_DEVICE(b, g, ven, prod)					\
	.bus = (b), .group = (g), .venकरोr = (ven), .product = (prod)
#घोषणा HID_USB_DEVICE(ven, prod)				\
	.bus = BUS_USB, .venकरोr = (ven), .product = (prod)
#घोषणा HID_BLUETOOTH_DEVICE(ven, prod)					\
	.bus = BUS_BLUETOOTH, .venकरोr = (ven), .product = (prod)
#घोषणा HID_I2C_DEVICE(ven, prod)				\
	.bus = BUS_I2C, .venकरोr = (ven), .product = (prod)

#घोषणा HID_REPORT_ID(rep) \
	.report_type = (rep)
#घोषणा HID_USAGE_ID(uhid, utype, ucode) \
	.usage_hid = (uhid), .usage_type = (utype), .usage_code = (ucode)
/* we करोn't want to catch types and codes equal to 0 */
#घोषणा HID_TERMINATOR		(HID_ANY_ID - 1)

काष्ठा hid_report_id अणु
	__u32 report_type;
पूर्ण;
काष्ठा hid_usage_id अणु
	__u32 usage_hid;
	__u32 usage_type;
	__u32 usage_code;
पूर्ण;

/**
 * काष्ठा hid_driver
 * @name: driver name (e.g. "Footech_bar-wheel")
 * @id_table: which devices is this driver क्रम (must be non-शून्य क्रम probe
 * 	      to be called)
 * @dyn_list: list of dynamically added device ids
 * @dyn_lock: lock protecting @dyn_list
 * @match: check अगर the given device is handled by this driver
 * @probe: new device inserted
 * @हटाओ: device हटाओd (शून्य अगर not a hot-plug capable driver)
 * @report_table: on which reports to call raw_event (शून्य means all)
 * @raw_event: अगर report in report_table, this hook is called (शून्य means nop)
 * @usage_table: on which events to call event (शून्य means all)
 * @event: अगर usage in usage_table, this hook is called (शून्य means nop)
 * @report: this hook is called after parsing a report (शून्य means nop)
 * @report_fixup: called beक्रमe report descriptor parsing (शून्य means nop)
 * @input_mapping: invoked on input रेजिस्टरing beक्रमe mapping an usage
 * @input_mapped: invoked on input रेजिस्टरing after mapping an usage
 * @input_configured: invoked just beक्रमe the device is रेजिस्टरed
 * @feature_mapping: invoked on feature रेजिस्टरing
 * @suspend: invoked on suspend (शून्य means nop)
 * @resume: invoked on resume अगर device was not reset (शून्य means nop)
 * @reset_resume: invoked on resume अगर device was reset (शून्य means nop)
 *
 * probe should वापस -त्रुटि_सं on error, or 0 on success. During probe,
 * input will not be passed to raw_event unless hid_device_io_start is
 * called.
 *
 * raw_event and event should वापस negative on error, any other value will
 * pass the event on to .event() typically वापस 0 क्रम success.
 *
 * input_mapping shall वापस a negative value to completely ignore this usage
 * (e.g. द्विगुनd or invalid usage), zero to जारी with parsing of this
 * usage by generic code (no special handling needed) or positive to skip
 * generic parsing (needed special handling which was करोne in the hook alपढ़ोy)
 * input_mapped shall वापस negative to inक्रमm the layer that this usage
 * should not be considered क्रम further processing or zero to notअगरy that
 * no processing was perक्रमmed and should be करोne in a generic manner
 * Both these functions may be शून्य which means the same behavior as वापसing
 * zero from them.
 */
काष्ठा hid_driver अणु
	अक्षर *name;
	स्थिर काष्ठा hid_device_id *id_table;

	काष्ठा list_head dyn_list;
	spinlock_t dyn_lock;

	bool (*match)(काष्ठा hid_device *dev, bool ignore_special_driver);
	पूर्णांक (*probe)(काष्ठा hid_device *dev, स्थिर काष्ठा hid_device_id *id);
	व्योम (*हटाओ)(काष्ठा hid_device *dev);

	स्थिर काष्ठा hid_report_id *report_table;
	पूर्णांक (*raw_event)(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
			u8 *data, पूर्णांक size);
	स्थिर काष्ठा hid_usage_id *usage_table;
	पूर्णांक (*event)(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
			काष्ठा hid_usage *usage, __s32 value);
	व्योम (*report)(काष्ठा hid_device *hdev, काष्ठा hid_report *report);

	__u8 *(*report_fixup)(काष्ठा hid_device *hdev, __u8 *buf,
			अचिन्हित पूर्णांक *size);

	पूर्णांक (*input_mapping)(काष्ठा hid_device *hdev,
			काष्ठा hid_input *hidinput, काष्ठा hid_field *field,
			काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max);
	पूर्णांक (*input_mapped)(काष्ठा hid_device *hdev,
			काष्ठा hid_input *hidinput, काष्ठा hid_field *field,
			काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max);
	पूर्णांक (*input_configured)(काष्ठा hid_device *hdev,
				काष्ठा hid_input *hidinput);
	व्योम (*feature_mapping)(काष्ठा hid_device *hdev,
			काष्ठा hid_field *field,
			काष्ठा hid_usage *usage);
#अगर_घोषित CONFIG_PM
	पूर्णांक (*suspend)(काष्ठा hid_device *hdev, pm_message_t message);
	पूर्णांक (*resume)(काष्ठा hid_device *hdev);
	पूर्णांक (*reset_resume)(काष्ठा hid_device *hdev);
#पूर्ण_अगर
/* निजी: */
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा to_hid_driver(pdrv) \
	container_of(pdrv, काष्ठा hid_driver, driver)

/**
 * hid_ll_driver - low level driver callbacks
 * @start: called on probe to start the device
 * @stop: called on हटाओ
 * @खोलो: called by input layer on खोलो
 * @बंद: called by input layer on बंद
 * @घातer: request underlying hardware to enter requested घातer mode
 * @parse: this method is called only once to parse the device data,
 *	   shouldn't allocate anything to not leak memory
 * @request: send report request to device (e.g. feature report)
 * @रुको: रुको क्रम buffered io to complete (send/recv reports)
 * @raw_request: send raw report request to device (e.g. feature report)
 * @output_report: send output report to device
 * @idle: send idle request to device
 */
काष्ठा hid_ll_driver अणु
	पूर्णांक (*start)(काष्ठा hid_device *hdev);
	व्योम (*stop)(काष्ठा hid_device *hdev);

	पूर्णांक (*खोलो)(काष्ठा hid_device *hdev);
	व्योम (*बंद)(काष्ठा hid_device *hdev);

	पूर्णांक (*घातer)(काष्ठा hid_device *hdev, पूर्णांक level);

	पूर्णांक (*parse)(काष्ठा hid_device *hdev);

	व्योम (*request)(काष्ठा hid_device *hdev,
			काष्ठा hid_report *report, पूर्णांक reqtype);

	पूर्णांक (*रुको)(काष्ठा hid_device *hdev);

	पूर्णांक (*raw_request) (काष्ठा hid_device *hdev, अचिन्हित अक्षर reportnum,
			    __u8 *buf, माप_प्रकार len, अचिन्हित अक्षर rtype,
			    पूर्णांक reqtype);

	पूर्णांक (*output_report) (काष्ठा hid_device *hdev, __u8 *buf, माप_प्रकार len);

	पूर्णांक (*idle)(काष्ठा hid_device *hdev, पूर्णांक report, पूर्णांक idle, पूर्णांक reqtype);
पूर्ण;

बाह्य काष्ठा hid_ll_driver i2c_hid_ll_driver;
बाह्य काष्ठा hid_ll_driver hidp_hid_driver;
बाह्य काष्ठा hid_ll_driver uhid_hid_driver;
बाह्य काष्ठा hid_ll_driver usb_hid_driver;

अटल अंतरभूत bool hid_is_using_ll_driver(काष्ठा hid_device *hdev,
		काष्ठा hid_ll_driver *driver)
अणु
	वापस hdev->ll_driver == driver;
पूर्ण

#घोषणा	PM_HINT_FULLON	1<<5
#घोषणा PM_HINT_NORMAL	1<<1

/* Applications from HID Usage Tables 4/8/99 Version 1.1 */
/* We ignore a few input applications that are not widely used */
#घोषणा IS_INPUT_APPLICATION(a) \
		(((a >= HID_UP_GENDESK) && (a <= HID_GD_MULTIAXIS)) \
		|| ((a >= HID_DG_PEN) && (a <= HID_DG_WHITEBOARD)) \
		|| (a == HID_GD_SYSTEM_CONTROL) || (a == HID_CP_CONSUMER_CONTROL) \
		|| (a == HID_GD_WIRELESS_RADIO_CTLS))

/* HID core API */

बाह्य पूर्णांक hid_debug;

बाह्य bool hid_ignore(काष्ठा hid_device *);
बाह्य पूर्णांक hid_add_device(काष्ठा hid_device *);
बाह्य व्योम hid_destroy_device(काष्ठा hid_device *);

बाह्य काष्ठा bus_type hid_bus_type;

बाह्य पूर्णांक __must_check __hid_रेजिस्टर_driver(काष्ठा hid_driver *,
		काष्ठा module *, स्थिर अक्षर *mod_name);

/* use a define to aव्योम include chaining to get THIS_MODULE & मित्रs */
#घोषणा hid_रेजिस्टर_driver(driver) \
	__hid_रेजिस्टर_driver(driver, THIS_MODULE, KBUILD_MODNAME)

बाह्य व्योम hid_unरेजिस्टर_driver(काष्ठा hid_driver *);

/**
 * module_hid_driver() - Helper macro क्रम रेजिस्टरing a HID driver
 * @__hid_driver: hid_driver काष्ठा
 *
 * Helper macro क्रम HID drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_hid_driver(__hid_driver) \
	module_driver(__hid_driver, hid_रेजिस्टर_driver, \
		      hid_unरेजिस्टर_driver)

बाह्य व्योम hidinput_hid_event(काष्ठा hid_device *, काष्ठा hid_field *, काष्ठा hid_usage *, __s32);
बाह्य व्योम hidinput_report_event(काष्ठा hid_device *hid, काष्ठा hid_report *report);
बाह्य पूर्णांक hidinput_connect(काष्ठा hid_device *hid, अचिन्हित पूर्णांक क्रमce);
बाह्य व्योम hidinput_disconnect(काष्ठा hid_device *);

पूर्णांक hid_set_field(काष्ठा hid_field *, अचिन्हित, __s32);
पूर्णांक hid_input_report(काष्ठा hid_device *, पूर्णांक type, u8 *, u32, पूर्णांक);
पूर्णांक hidinput_find_field(काष्ठा hid_device *hid, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, काष्ठा hid_field **field);
काष्ठा hid_field *hidinput_get_led_field(काष्ठा hid_device *hid);
अचिन्हित पूर्णांक hidinput_count_leds(काष्ठा hid_device *hid);
__s32 hidinput_calc_असल_res(स्थिर काष्ठा hid_field *field, __u16 code);
व्योम hid_output_report(काष्ठा hid_report *report, __u8 *data);
पूर्णांक __hid_request(काष्ठा hid_device *hid, काष्ठा hid_report *rep, पूर्णांक reqtype);
u8 *hid_alloc_report_buf(काष्ठा hid_report *report, gfp_t flags);
काष्ठा hid_device *hid_allocate_device(व्योम);
काष्ठा hid_report *hid_रेजिस्टर_report(काष्ठा hid_device *device,
				       अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक id,
				       अचिन्हित पूर्णांक application);
पूर्णांक hid_parse_report(काष्ठा hid_device *hid, __u8 *start, अचिन्हित size);
काष्ठा hid_report *hid_validate_values(काष्ठा hid_device *hid,
				       अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक id,
				       अचिन्हित पूर्णांक field_index,
				       अचिन्हित पूर्णांक report_counts);

व्योम hid_setup_resolution_multiplier(काष्ठा hid_device *hid);
पूर्णांक hid_खोलो_report(काष्ठा hid_device *device);
पूर्णांक hid_check_keys_pressed(काष्ठा hid_device *hid);
पूर्णांक hid_connect(काष्ठा hid_device *hid, अचिन्हित पूर्णांक connect_mask);
व्योम hid_disconnect(काष्ठा hid_device *hid);
bool hid_match_one_id(स्थिर काष्ठा hid_device *hdev,
		      स्थिर काष्ठा hid_device_id *id);
स्थिर काष्ठा hid_device_id *hid_match_id(स्थिर काष्ठा hid_device *hdev,
					 स्थिर काष्ठा hid_device_id *id);
स्थिर काष्ठा hid_device_id *hid_match_device(काष्ठा hid_device *hdev,
					     काष्ठा hid_driver *hdrv);
bool hid_compare_device_paths(काष्ठा hid_device *hdev_a,
			      काष्ठा hid_device *hdev_b, अक्षर separator);
s32 hid_snto32(__u32 value, अचिन्हित n);
__u32 hid_field_extract(स्थिर काष्ठा hid_device *hid, __u8 *report,
		     अचिन्हित offset, अचिन्हित n);

/**
 * hid_device_io_start - enable HID input during probe, हटाओ
 *
 * @hid: the device
 *
 * This should only be called during probe or हटाओ and only be
 * called by the thपढ़ो calling probe or हटाओ. It will allow
 * incoming packets to be delivered to the driver.
 */
अटल अंतरभूत व्योम hid_device_io_start(काष्ठा hid_device *hid) अणु
	अगर (hid->io_started) अणु
		dev_warn(&hid->dev, "io already started\n");
		वापस;
	पूर्ण
	hid->io_started = true;
	up(&hid->driver_input_lock);
पूर्ण

/**
 * hid_device_io_stop - disable HID input during probe, हटाओ
 *
 * @hid: the device
 *
 * Should only be called after hid_device_io_start. It will prevent
 * incoming packets from going to the driver क्रम the duration of
 * probe, हटाओ. If called during probe, packets will still go to the
 * driver after probe is complete. This function should only be called
 * by the thपढ़ो calling probe or हटाओ.
 */
अटल अंतरभूत व्योम hid_device_io_stop(काष्ठा hid_device *hid) अणु
	अगर (!hid->io_started) अणु
		dev_warn(&hid->dev, "io already stopped\n");
		वापस;
	पूर्ण
	hid->io_started = false;
	करोwn(&hid->driver_input_lock);
पूर्ण

/**
 * hid_map_usage - map usage input bits
 *
 * @hidinput: hidinput which we are पूर्णांकerested in
 * @usage: usage to fill in
 * @bit: poपूर्णांकer to input->अणुपूर्णbit (out parameter)
 * @max: maximal valid usage->code to consider later (out parameter)
 * @type: input event type (EV_KEY, EV_REL, ...)
 * @c: code which corresponds to this usage and type
 *
 * The value poपूर्णांकed to by @bit will be set to शून्य अगर either @type is
 * an unhandled event type, or अगर @c is out of range क्रम @type. This
 * can be used as an error condition.
 */
अटल अंतरभूत व्योम hid_map_usage(काष्ठा hid_input *hidinput,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max,
		__u8 type, अचिन्हित पूर्णांक c)
अणु
	काष्ठा input_dev *input = hidinput->input;
	अचिन्हित दीर्घ *bmap = शून्य;
	अचिन्हित पूर्णांक limit = 0;

	चयन (type) अणु
	हाल EV_ABS:
		bmap = input->असलbit;
		limit = ABS_MAX;
		अवरोध;
	हाल EV_REL:
		bmap = input->relbit;
		limit = REL_MAX;
		अवरोध;
	हाल EV_KEY:
		bmap = input->keybit;
		limit = KEY_MAX;
		अवरोध;
	हाल EV_LED:
		bmap = input->ledbit;
		limit = LED_MAX;
		अवरोध;
	पूर्ण

	अगर (unlikely(c > limit || !bmap)) अणु
		pr_warn_ratelimited("%s: Invalid code %d type %d\n",
				    input->name, c, type);
		*bit = शून्य;
		वापस;
	पूर्ण

	usage->type = type;
	usage->code = c;
	*max = limit;
	*bit = bmap;
पूर्ण

/**
 * hid_map_usage_clear - map usage input bits and clear the input bit
 *
 * @hidinput: hidinput which we are पूर्णांकerested in
 * @usage: usage to fill in
 * @bit: poपूर्णांकer to input->अणुपूर्णbit (out parameter)
 * @max: maximal valid usage->code to consider later (out parameter)
 * @type: input event type (EV_KEY, EV_REL, ...)
 * @c: code which corresponds to this usage and type
 *
 * The same as hid_map_usage, except the @c bit is also cleared in supported
 * bits (@bit).
 */
अटल अंतरभूत व्योम hid_map_usage_clear(काष्ठा hid_input *hidinput,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max,
		__u8 type, __u16 c)
अणु
	hid_map_usage(hidinput, usage, bit, max, type, c);
	अगर (*bit)
		clear_bit(usage->code, *bit);
पूर्ण

/**
 * hid_parse - parse HW reports
 *
 * @hdev: hid device
 *
 * Call this from probe after you set up the device (अगर needed). Your
 * report_fixup will be called (अगर non-शून्य) after पढ़ोing raw report from
 * device beक्रमe passing it to hid layer क्रम real parsing.
 */
अटल अंतरभूत पूर्णांक __must_check hid_parse(काष्ठा hid_device *hdev)
अणु
	वापस hid_खोलो_report(hdev);
पूर्ण

पूर्णांक __must_check hid_hw_start(काष्ठा hid_device *hdev,
			      अचिन्हित पूर्णांक connect_mask);
व्योम hid_hw_stop(काष्ठा hid_device *hdev);
पूर्णांक __must_check hid_hw_खोलो(काष्ठा hid_device *hdev);
व्योम hid_hw_बंद(काष्ठा hid_device *hdev);

/**
 * hid_hw_घातer - requests underlying HW to go पूर्णांकo given घातer mode
 *
 * @hdev: hid device
 * @level: requested घातer level (one of %PM_HINT_* defines)
 *
 * This function requests underlying hardware to enter requested घातer
 * mode.
 */

अटल अंतरभूत पूर्णांक hid_hw_घातer(काष्ठा hid_device *hdev, पूर्णांक level)
अणु
	वापस hdev->ll_driver->घातer ? hdev->ll_driver->घातer(hdev, level) : 0;
पूर्ण


/**
 * hid_hw_request - send report request to device
 *
 * @hdev: hid device
 * @report: report to send
 * @reqtype: hid request type
 */
अटल अंतरभूत व्योम hid_hw_request(काष्ठा hid_device *hdev,
				  काष्ठा hid_report *report, पूर्णांक reqtype)
अणु
	अगर (hdev->ll_driver->request)
		वापस hdev->ll_driver->request(hdev, report, reqtype);

	__hid_request(hdev, report, reqtype);
पूर्ण

/**
 * hid_hw_raw_request - send report request to device
 *
 * @hdev: hid device
 * @reportnum: report ID
 * @buf: in/out data to transfer
 * @len: length of buf
 * @rtype: HID report type
 * @reqtype: HID_REQ_GET_REPORT or HID_REQ_SET_REPORT
 *
 * Return: count of data transferred, negative अगर error
 *
 * Same behavior as hid_hw_request, but with raw buffers instead.
 */
अटल अंतरभूत पूर्णांक hid_hw_raw_request(काष्ठा hid_device *hdev,
				  अचिन्हित अक्षर reportnum, __u8 *buf,
				  माप_प्रकार len, अचिन्हित अक्षर rtype, पूर्णांक reqtype)
अणु
	अगर (len < 1 || len > HID_MAX_BUFFER_SIZE || !buf)
		वापस -EINVAL;

	वापस hdev->ll_driver->raw_request(hdev, reportnum, buf, len,
						    rtype, reqtype);
पूर्ण

/**
 * hid_hw_output_report - send output report to device
 *
 * @hdev: hid device
 * @buf: raw data to transfer
 * @len: length of buf
 *
 * Return: count of data transferred, negative अगर error
 */
अटल अंतरभूत पूर्णांक hid_hw_output_report(काष्ठा hid_device *hdev, __u8 *buf,
					माप_प्रकार len)
अणु
	अगर (len < 1 || len > HID_MAX_BUFFER_SIZE || !buf)
		वापस -EINVAL;

	अगर (hdev->ll_driver->output_report)
		वापस hdev->ll_driver->output_report(hdev, buf, len);

	वापस -ENOSYS;
पूर्ण

/**
 * hid_hw_idle - send idle request to device
 *
 * @hdev: hid device
 * @report: report to control
 * @idle: idle state
 * @reqtype: hid request type
 */
अटल अंतरभूत पूर्णांक hid_hw_idle(काष्ठा hid_device *hdev, पूर्णांक report, पूर्णांक idle,
		पूर्णांक reqtype)
अणु
	अगर (hdev->ll_driver->idle)
		वापस hdev->ll_driver->idle(hdev, report, idle, reqtype);

	वापस 0;
पूर्ण

/**
 * hid_hw_रुको - रुको क्रम buffered io to complete
 *
 * @hdev: hid device
 */
अटल अंतरभूत व्योम hid_hw_रुको(काष्ठा hid_device *hdev)
अणु
	अगर (hdev->ll_driver->रुको)
		hdev->ll_driver->रुको(hdev);
पूर्ण

/**
 * hid_report_len - calculate the report length
 *
 * @report: the report we want to know the length
 */
अटल अंतरभूत u32 hid_report_len(काष्ठा hid_report *report)
अणु
	वापस DIV_ROUND_UP(report->size, 8) + (report->id > 0);
पूर्ण

पूर्णांक hid_report_raw_event(काष्ठा hid_device *hid, पूर्णांक type, u8 *data, u32 size,
		पूर्णांक पूर्णांकerrupt);

/* HID quirks API */
अचिन्हित दीर्घ hid_lookup_quirk(स्थिर काष्ठा hid_device *hdev);
पूर्णांक hid_quirks_init(अक्षर **quirks_param, __u16 bus, पूर्णांक count);
व्योम hid_quirks_निकास(__u16 bus);

#अगर_घोषित CONFIG_HID_PID
पूर्णांक hid_pidff_init(काष्ठा hid_device *hid);
#अन्यथा
#घोषणा hid_pidff_init शून्य
#पूर्ण_अगर

#घोषणा dbg_hid(fmt, ...)						\
करो अणु									\
	अगर (hid_debug)							\
		prपूर्णांकk(KERN_DEBUG "%s: " fmt, __खाता__, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा hid_err(hid, fmt, ...)				\
	dev_err(&(hid)->dev, fmt, ##__VA_ARGS__)
#घोषणा hid_notice(hid, fmt, ...)			\
	dev_notice(&(hid)->dev, fmt, ##__VA_ARGS__)
#घोषणा hid_warn(hid, fmt, ...)				\
	dev_warn(&(hid)->dev, fmt, ##__VA_ARGS__)
#घोषणा hid_info(hid, fmt, ...)				\
	dev_info(&(hid)->dev, fmt, ##__VA_ARGS__)
#घोषणा hid_dbg(hid, fmt, ...)				\
	dev_dbg(&(hid)->dev, fmt, ##__VA_ARGS__)

#घोषणा hid_err_once(hid, fmt, ...)			\
	dev_err_once(&(hid)->dev, fmt, ##__VA_ARGS__)
#घोषणा hid_notice_once(hid, fmt, ...)			\
	dev_notice_once(&(hid)->dev, fmt, ##__VA_ARGS__)
#घोषणा hid_warn_once(hid, fmt, ...)			\
	dev_warn_once(&(hid)->dev, fmt, ##__VA_ARGS__)
#घोषणा hid_info_once(hid, fmt, ...)			\
	dev_info_once(&(hid)->dev, fmt, ##__VA_ARGS__)
#घोषणा hid_dbg_once(hid, fmt, ...)			\
	dev_dbg_once(&(hid)->dev, fmt, ##__VA_ARGS__)

#पूर्ण_अगर
