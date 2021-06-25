<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Sony / PS2 / PS3 / PS4 BD devices.
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2008 Jiri Slaby
 *  Copyright (c) 2012 David Dillow <dave@thedillows.org>
 *  Copyright (c) 2006-2013 Jiri Kosina
 *  Copyright (c) 2013 Colin Leitner <colin.leitner@gmail.com>
 *  Copyright (c) 2014-2016 Frank Praznik <frank.praznik@gmail.com>
 *  Copyright (c) 2018 Todd Kelner
 *  Copyright (c) 2020 Pascal Giard <pascal.giard@etsmtl.ca>
 *  Copyright (c) 2020 Sanjay Govind <sanjay.govind9@gmail.com>
 */

/*
 */

/*
 * NOTE: in order क्रम the Sony PS3 BD Remote Control to be found by
 * a Bluetooth host, the key combination Start+Enter has to be kept pressed
 * क्रम about 7 seconds with the Bluetooth Host Controller in discovering mode.
 *
 * There will be no PIN request from the device.
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/idr.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb.h>
#समावेश <linux/समयr.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "hid-ids.h"

#घोषणा VAIO_RDESC_CONSTANT       BIT(0)
#घोषणा SIXAXIS_CONTROLLER_USB    BIT(1)
#घोषणा SIXAXIS_CONTROLLER_BT     BIT(2)
#घोषणा BUZZ_CONTROLLER           BIT(3)
#घोषणा PS3REMOTE                 BIT(4)
#घोषणा DUALSHOCK4_CONTROLLER_USB BIT(5)
#घोषणा DUALSHOCK4_CONTROLLER_BT  BIT(6)
#घोषणा DUALSHOCK4_DONGLE         BIT(7)
#घोषणा MOTION_CONTROLLER_USB     BIT(8)
#घोषणा MOTION_CONTROLLER_BT      BIT(9)
#घोषणा NAVIGATION_CONTROLLER_USB BIT(10)
#घोषणा NAVIGATION_CONTROLLER_BT  BIT(11)
#घोषणा SINO_LITE_CONTROLLER      BIT(12)
#घोषणा FUTUREMAX_DANCE_MAT       BIT(13)
#घोषणा NSG_MR5U_REMOTE_BT        BIT(14)
#घोषणा NSG_MR7U_REMOTE_BT        BIT(15)
#घोषणा SHANWAN_GAMEPAD           BIT(16)
#घोषणा GH_GUITAR_CONTROLLER      BIT(17)
#घोषणा GHL_GUITAR_PS3WIIU        BIT(18)

#घोषणा SIXAXIS_CONTROLLER (SIXAXIS_CONTROLLER_USB | SIXAXIS_CONTROLLER_BT)
#घोषणा MOTION_CONTROLLER (MOTION_CONTROLLER_USB | MOTION_CONTROLLER_BT)
#घोषणा NAVIGATION_CONTROLLER (NAVIGATION_CONTROLLER_USB |\
				NAVIGATION_CONTROLLER_BT)
#घोषणा DUALSHOCK4_CONTROLLER (DUALSHOCK4_CONTROLLER_USB |\
				DUALSHOCK4_CONTROLLER_BT | \
				DUALSHOCK4_DONGLE)
#घोषणा SONY_LED_SUPPORT (SIXAXIS_CONTROLLER | BUZZ_CONTROLLER |\
				DUALSHOCK4_CONTROLLER | MOTION_CONTROLLER |\
				NAVIGATION_CONTROLLER)
#घोषणा SONY_BATTERY_SUPPORT (SIXAXIS_CONTROLLER | DUALSHOCK4_CONTROLLER |\
				MOTION_CONTROLLER_BT | NAVIGATION_CONTROLLER)
#घोषणा SONY_FF_SUPPORT (SIXAXIS_CONTROLLER | DUALSHOCK4_CONTROLLER |\
				MOTION_CONTROLLER)
#घोषणा SONY_BT_DEVICE (SIXAXIS_CONTROLLER_BT | DUALSHOCK4_CONTROLLER_BT |\
			MOTION_CONTROLLER_BT | NAVIGATION_CONTROLLER_BT)
#घोषणा NSG_MRXU_REMOTE (NSG_MR5U_REMOTE_BT | NSG_MR7U_REMOTE_BT)

#घोषणा MAX_LEDS 4
#घोषणा NSG_MRXU_MAX_X 1667
#घोषणा NSG_MRXU_MAX_Y 1868

#घोषणा GHL_GUITAR_POKE_INTERVAL 10 /* In seconds */
#घोषणा GUITAR_TILT_USAGE 44

/* Magic value and data taken from GHLtarUtility:
 * https://github.com/ghlre/GHLtarUtility/blob/master/PS3Guitar.cs
 * Note: The Wii U and PS3 करोngles happen to share the same!
 */
अटल स्थिर u16 ghl_ps3wiiu_magic_value = 0x201;
अटल स्थिर अक्षर ghl_ps3wiiu_magic_data[] = अणु
	0x02, 0x08, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

/* PS/3 Motion controller */
अटल u8 motion_rdesc[] = अणु
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x04,         /*  Usage (Joystick),                   */
	0xA1, 0x01,         /*  Collection (Application),           */
	0xA1, 0x02,         /*      Collection (Logical),           */
	0x85, 0x01,         /*          Report ID (1),              */
	0x75, 0x01,         /*          Report Size (1),            */
	0x95, 0x15,         /*          Report Count (21),          */
	0x15, 0x00,         /*          Logical Minimum (0),        */
	0x25, 0x01,         /*          Logical Maximum (1),        */
	0x35, 0x00,         /*          Physical Minimum (0),       */
	0x45, 0x01,         /*          Physical Maximum (1),       */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x19, 0x01,         /*          Usage Minimum (01h),        */
	0x29, 0x15,         /*          Usage Maximum (15h),        */
	0x81, 0x02,         /*          Input (Variable),           * Buttons */
	0x95, 0x0B,         /*          Report Count (11),          */
	0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
	0x81, 0x03,         /*          Input (Constant, Variable), * Padding */
	0x15, 0x00,         /*          Logical Minimum (0),        */
	0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0xA1, 0x00,         /*          Collection (Physical),      */
	0x75, 0x08,         /*              Report Size (8),        */
	0x95, 0x01,         /*              Report Count (1),       */
	0x35, 0x00,         /*              Physical Minimum (0),   */
	0x46, 0xFF, 0x00,   /*              Physical Maximum (255), */
	0x09, 0x30,         /*              Usage (X),              */
	0x81, 0x02,         /*              Input (Variable),       * Trigger */
	0xC0,               /*          End Collection,             */
	0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x07,         /*          Report Count (7),           * skip 7 bytes */
	0x81, 0x02,         /*          Input (Variable),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x75, 0x10,         /*          Report Size (16),           */
	0x46, 0xFF, 0xFF,   /*          Physical Maximum (65535),   */
	0x27, 0xFF, 0xFF, 0x00, 0x00, /*      Logical Maximum (65535),    */
	0x95, 0x03,         /*          Report Count (3),           * 3x Accels */
	0x09, 0x33,         /*              Usage (rX),             */
	0x09, 0x34,         /*              Usage (rY),             */
	0x09, 0x35,         /*              Usage (rZ),             */
	0x81, 0x02,         /*          Input (Variable),           */
	0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
	0x95, 0x03,         /*          Report Count (3),           * Skip Accels 2nd frame */
	0x81, 0x02,         /*          Input (Variable),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x01,         /*          Usage (Poपूर्णांकer),            */
	0x95, 0x03,         /*          Report Count (3),           * 3x Gyros */
	0x81, 0x02,         /*          Input (Variable),           */
	0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
	0x95, 0x03,         /*          Report Count (3),           * Skip Gyros 2nd frame */
	0x81, 0x02,         /*          Input (Variable),           */
	0x75, 0x0C,         /*          Report Size (12),           */
	0x46, 0xFF, 0x0F,   /*          Physical Maximum (4095),    */
	0x26, 0xFF, 0x0F,   /*          Logical Maximum (4095),     */
	0x95, 0x04,         /*          Report Count (4),           * Skip Temp and Magnetometers */
	0x81, 0x02,         /*          Input (Variable),           */
	0x75, 0x08,         /*          Report Size (8),            */
	0x46, 0xFF, 0x00,   /*          Physical Maximum (255),     */
	0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
	0x95, 0x06,         /*          Report Count (6),           * Skip Timestamp and Extension Bytes */
	0x81, 0x02,         /*          Input (Variable),           */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x30,         /*          Report Count (48),          */
	0x09, 0x01,         /*          Usage (Poपूर्णांकer),            */
	0x91, 0x02,         /*          Output (Variable),          */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x30,         /*          Report Count (48),          */
	0x09, 0x01,         /*          Usage (Poपूर्णांकer),            */
	0xB1, 0x02,         /*          Feature (Variable),         */
	0xC0,               /*      End Collection,                 */
	0xA1, 0x02,         /*      Collection (Logical),           */
	0x85, 0x02,         /*          Report ID (2),              */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x30,         /*          Report Count (48),          */
	0x09, 0x01,         /*          Usage (Poपूर्णांकer),            */
	0xB1, 0x02,         /*          Feature (Variable),         */
	0xC0,               /*      End Collection,                 */
	0xA1, 0x02,         /*      Collection (Logical),           */
	0x85, 0xEE,         /*          Report ID (238),            */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x30,         /*          Report Count (48),          */
	0x09, 0x01,         /*          Usage (Poपूर्णांकer),            */
	0xB1, 0x02,         /*          Feature (Variable),         */
	0xC0,               /*      End Collection,                 */
	0xA1, 0x02,         /*      Collection (Logical),           */
	0x85, 0xEF,         /*          Report ID (239),            */
	0x75, 0x08,         /*          Report Size (8),            */
	0x95, 0x30,         /*          Report Count (48),          */
	0x09, 0x01,         /*          Usage (Poपूर्णांकer),            */
	0xB1, 0x02,         /*          Feature (Variable),         */
	0xC0,               /*      End Collection,                 */
	0xC0                /*  End Collection                      */
पूर्ण;

अटल u8 ps3remote_rdesc[] = अणु
	0x05, 0x01,          /* GUsagePage Generic Desktop */
	0x09, 0x05,          /* LUsage 0x05 [Game Pad] */
	0xA1, 0x01,          /* MCollection Application (mouse, keyboard) */

	 /* Use collection 1 क्रम joypad buttons */
	 0xA1, 0x02,         /* MCollection Logical (पूर्णांकerrelated data) */

	  /*
	   * Ignore the 1st byte, maybe it is used क्रम a controller
	   * number but it's not needed क्रम correct operation
	   */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x01,        /* GReportCount 0x01 [1] */
	  0x81, 0x01,        /* MInput 0x01 (Const[0] Arr[1] Abs[2]) */

	  /*
	   * Bytes from 2nd to 4th are a biपंचांगap क्रम joypad buttons, क्रम these
	   * buttons multiple keypresses are allowed
	   */
	  0x05, 0x09,        /* GUsagePage Button */
	  0x19, 0x01,        /* LUsageMinimum 0x01 [Button 1 (primary/trigger)] */
	  0x29, 0x18,        /* LUsageMaximum 0x18 [Button 24] */
	  0x14,              /* GLogicalMinimum [0] */
	  0x25, 0x01,        /* GLogicalMaximum 0x01 [1] */
	  0x75, 0x01,        /* GReportSize 0x01 [1] */
	  0x95, 0x18,        /* GReportCount 0x18 [24] */
	  0x81, 0x02,        /* MInput 0x02 (Data[0] Var[1] Abs[2]) */

	  0xC0,              /* MEndCollection */

	 /* Use collection 2 क्रम remote control buttons */
	 0xA1, 0x02,         /* MCollection Logical (पूर्णांकerrelated data) */

	  /* 5th byte is used क्रम remote control buttons */
	  0x05, 0x09,        /* GUsagePage Button */
	  0x18,              /* LUsageMinimum [No button pressed] */
	  0x29, 0xFE,        /* LUsageMaximum 0xFE [Button 254] */
	  0x14,              /* GLogicalMinimum [0] */
	  0x26, 0xFE, 0x00,  /* GLogicalMaximum 0x00FE [254] */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x01,        /* GReportCount 0x01 [1] */
	  0x80,              /* MInput  */

	  /*
	   * Ignore bytes from 6th to 11th, 6th to 10th are always स्थिरant at
	   * 0xff and 11th is क्रम press indication
	   */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x06,        /* GReportCount 0x06 [6] */
	  0x81, 0x01,        /* MInput 0x01 (Const[0] Arr[1] Abs[2]) */

	  /* 12th byte is क्रम battery strength */
	  0x05, 0x06,        /* GUsagePage Generic Device Controls */
	  0x09, 0x20,        /* LUsage 0x20 [Battery Strength] */
	  0x14,              /* GLogicalMinimum [0] */
	  0x25, 0x05,        /* GLogicalMaximum 0x05 [5] */
	  0x75, 0x08,        /* GReportSize 0x08 [8] */
	  0x95, 0x01,        /* GReportCount 0x01 [1] */
	  0x81, 0x02,        /* MInput 0x02 (Data[0] Var[1] Abs[2]) */

	  0xC0,              /* MEndCollection */

	 0xC0                /* MEndCollection [Game Pad] */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ps3remote_keymap_joypad_buttons[] = अणु
	[0x01] = KEY_SELECT,
	[0x02] = BTN_THUMBL,		/* L3 */
	[0x03] = BTN_THUMBR,		/* R3 */
	[0x04] = BTN_START,
	[0x05] = KEY_UP,
	[0x06] = KEY_RIGHT,
	[0x07] = KEY_DOWN,
	[0x08] = KEY_LEFT,
	[0x09] = BTN_TL2,		/* L2 */
	[0x0a] = BTN_TR2,		/* R2 */
	[0x0b] = BTN_TL,		/* L1 */
	[0x0c] = BTN_TR,		/* R1 */
	[0x0d] = KEY_OPTION,		/* options/triangle */
	[0x0e] = KEY_BACK,		/* back/circle */
	[0x0f] = BTN_0,			/* cross */
	[0x10] = KEY_SCREEN,		/* view/square */
	[0x11] = KEY_HOMEPAGE,		/* PS button */
	[0x14] = KEY_ENTER,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ps3remote_keymap_remote_buttons[] = अणु
	[0x00] = KEY_1,
	[0x01] = KEY_2,
	[0x02] = KEY_3,
	[0x03] = KEY_4,
	[0x04] = KEY_5,
	[0x05] = KEY_6,
	[0x06] = KEY_7,
	[0x07] = KEY_8,
	[0x08] = KEY_9,
	[0x09] = KEY_0,
	[0x0e] = KEY_ESC,		/* वापस */
	[0x0f] = KEY_CLEAR,
	[0x16] = KEY_EJECTCD,
	[0x1a] = KEY_MENU,		/* top menu */
	[0x28] = KEY_TIME,
	[0x30] = KEY_PREVIOUS,
	[0x31] = KEY_NEXT,
	[0x32] = KEY_PLAY,
	[0x33] = KEY_REWIND,		/* scan back */
	[0x34] = KEY_FORWARD,		/* scan क्रमward */
	[0x38] = KEY_STOP,
	[0x39] = KEY_PAUSE,
	[0x40] = KEY_CONTEXT_MENU,	/* pop up/menu */
	[0x60] = KEY_FRAMEBACK,		/* slow/step back */
	[0x61] = KEY_FRAMEFORWARD,	/* slow/step क्रमward */
	[0x63] = KEY_SUBTITLE,
	[0x64] = KEY_AUDIO,
	[0x65] = KEY_ANGLE,
	[0x70] = KEY_INFO,		/* display */
	[0x80] = KEY_BLUE,
	[0x81] = KEY_RED,
	[0x82] = KEY_GREEN,
	[0x83] = KEY_YELLOW,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक buzz_keymap[] = अणु
	/*
	 * The controller has 4 remote buzzers, each with one LED and 5
	 * buttons.
	 *
	 * We use the mapping chosen by the controller, which is:
	 *
	 * Key          Offset
	 * -------------------
	 * Buzz              1
	 * Blue              5
	 * Orange            4
	 * Green             3
	 * Yellow            2
	 *
	 * So, क्रम example, the orange button on the third buzzer is mapped to
	 * BTN_TRIGGER_HAPPY14
	 */
	 [1] = BTN_TRIGGER_HAPPY1,
	 [2] = BTN_TRIGGER_HAPPY2,
	 [3] = BTN_TRIGGER_HAPPY3,
	 [4] = BTN_TRIGGER_HAPPY4,
	 [5] = BTN_TRIGGER_HAPPY5,
	 [6] = BTN_TRIGGER_HAPPY6,
	 [7] = BTN_TRIGGER_HAPPY7,
	 [8] = BTN_TRIGGER_HAPPY8,
	 [9] = BTN_TRIGGER_HAPPY9,
	[10] = BTN_TRIGGER_HAPPY10,
	[11] = BTN_TRIGGER_HAPPY11,
	[12] = BTN_TRIGGER_HAPPY12,
	[13] = BTN_TRIGGER_HAPPY13,
	[14] = BTN_TRIGGER_HAPPY14,
	[15] = BTN_TRIGGER_HAPPY15,
	[16] = BTN_TRIGGER_HAPPY16,
	[17] = BTN_TRIGGER_HAPPY17,
	[18] = BTN_TRIGGER_HAPPY18,
	[19] = BTN_TRIGGER_HAPPY19,
	[20] = BTN_TRIGGER_HAPPY20,
पूर्ण;

/* The Navigation controller is a partial DS3 and uses the same HID report
 * and hence the same keymap indices, however not not all axes/buttons
 * are physically present. We use the same axis and button mapping as
 * the DS3, which uses the Linux gamepad spec.
 */
अटल स्थिर अचिन्हित पूर्णांक navigation_असलmap[] = अणु
	[0x30] = ABS_X,
	[0x31] = ABS_Y,
	[0x33] = ABS_Z, /* L2 */
पूर्ण;

/* Buttons not physically available on the device, but still available
 * in the reports are explicitly set to 0 क्रम करोcumentation purposes.
 */
अटल स्थिर अचिन्हित पूर्णांक navigation_keymap[] = अणु
	[0x01] = 0, /* Select */
	[0x02] = BTN_THUMBL, /* L3 */
	[0x03] = 0, /* R3 */
	[0x04] = 0, /* Start */
	[0x05] = BTN_DPAD_UP, /* Up */
	[0x06] = BTN_DPAD_RIGHT, /* Right */
	[0x07] = BTN_DPAD_DOWN, /* Down */
	[0x08] = BTN_DPAD_LEFT, /* Left */
	[0x09] = BTN_TL2, /* L2 */
	[0x0a] = 0, /* R2 */
	[0x0b] = BTN_TL, /* L1 */
	[0x0c] = 0, /* R1 */
	[0x0d] = BTN_NORTH, /* Triangle */
	[0x0e] = BTN_EAST, /* Circle */
	[0x0f] = BTN_SOUTH, /* Cross */
	[0x10] = BTN_WEST, /* Square */
	[0x11] = BTN_MODE, /* PS */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sixaxis_असलmap[] = अणु
	[0x30] = ABS_X,
	[0x31] = ABS_Y,
	[0x32] = ABS_RX, /* right stick X */
	[0x35] = ABS_RY, /* right stick Y */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sixaxis_keymap[] = अणु
	[0x01] = BTN_SELECT, /* Select */
	[0x02] = BTN_THUMBL, /* L3 */
	[0x03] = BTN_THUMBR, /* R3 */
	[0x04] = BTN_START, /* Start */
	[0x05] = BTN_DPAD_UP, /* Up */
	[0x06] = BTN_DPAD_RIGHT, /* Right */
	[0x07] = BTN_DPAD_DOWN, /* Down */
	[0x08] = BTN_DPAD_LEFT, /* Left */
	[0x09] = BTN_TL2, /* L2 */
	[0x0a] = BTN_TR2, /* R2 */
	[0x0b] = BTN_TL, /* L1 */
	[0x0c] = BTN_TR, /* R1 */
	[0x0d] = BTN_NORTH, /* Triangle */
	[0x0e] = BTN_EAST, /* Circle */
	[0x0f] = BTN_SOUTH, /* Cross */
	[0x10] = BTN_WEST, /* Square */
	[0x11] = BTN_MODE, /* PS */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ds4_असलmap[] = अणु
	[0x30] = ABS_X,
	[0x31] = ABS_Y,
	[0x32] = ABS_RX, /* right stick X */
	[0x33] = ABS_Z, /* L2 */
	[0x34] = ABS_RZ, /* R2 */
	[0x35] = ABS_RY, /* right stick Y */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ds4_keymap[] = अणु
	[0x1] = BTN_WEST, /* Square */
	[0x2] = BTN_SOUTH, /* Cross */
	[0x3] = BTN_EAST, /* Circle */
	[0x4] = BTN_NORTH, /* Triangle */
	[0x5] = BTN_TL, /* L1 */
	[0x6] = BTN_TR, /* R1 */
	[0x7] = BTN_TL2, /* L2 */
	[0x8] = BTN_TR2, /* R2 */
	[0x9] = BTN_SELECT, /* Share */
	[0xa] = BTN_START, /* Options */
	[0xb] = BTN_THUMBL, /* L3 */
	[0xc] = BTN_THUMBR, /* R3 */
	[0xd] = BTN_MODE, /* PS */
पूर्ण;

अटल स्थिर काष्ठा अणुपूर्णांक x; पूर्णांक y; पूर्ण ds4_hat_mapping[] = अणु
	अणु0, -1पूर्ण, अणु1, -1पूर्ण, अणु1, 0पूर्ण, अणु1, 1पूर्ण, अणु0, 1पूर्ण, अणु-1, 1पूर्ण, अणु-1, 0पूर्ण, अणु-1, -1पूर्ण,
	अणु0, 0पूर्ण
पूर्ण;

अटल क्रमागत घातer_supply_property sony_battery_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_STATUS,
पूर्ण;

काष्ठा sixaxis_led अणु
	u8 समय_enabled; /* the total समय the led is active (0xff means क्रमever) */
	u8 duty_length;  /* how दीर्घ a cycle is in deciseconds (0 means "really fast") */
	u8 enabled;
	u8 duty_off; /* % of duty_length the led is off (0xff means 100%) */
	u8 duty_on;  /* % of duty_length the led is on (0xff mean 100%) */
पूर्ण __packed;

काष्ठा sixaxis_rumble अणु
	u8 padding;
	u8 right_duration; /* Right motor duration (0xff means क्रमever) */
	u8 right_motor_on; /* Right (small) motor on/off, only supports values of 0 or 1 (off/on) */
	u8 left_duration;    /* Left motor duration (0xff means क्रमever) */
	u8 left_motor_क्रमce; /* left (large) motor, supports क्रमce values from 0 to 255 */
पूर्ण __packed;

काष्ठा sixaxis_output_report अणु
	u8 report_id;
	काष्ठा sixaxis_rumble rumble;
	u8 padding[4];
	u8 leds_biपंचांगap; /* biपंचांगap of enabled LEDs: LED_1 = 0x02, LED_2 = 0x04, ... */
	काष्ठा sixaxis_led led[4];    /* LEDx at (4 - x) */
	काष्ठा sixaxis_led _reserved; /* LED5, not actually soldered */
पूर्ण __packed;

जोड़ sixaxis_output_report_01 अणु
	काष्ठा sixaxis_output_report data;
	u8 buf[36];
पूर्ण;

काष्ठा motion_output_report_02 अणु
	u8 type, zero;
	u8 r, g, b;
	u8 zero2;
	u8 rumble;
पूर्ण;

#घोषणा DS4_FEATURE_REPORT_0x02_SIZE 37
#घोषणा DS4_FEATURE_REPORT_0x05_SIZE 41
#घोषणा DS4_FEATURE_REPORT_0x81_SIZE 7
#घोषणा DS4_FEATURE_REPORT_0xA3_SIZE 49
#घोषणा DS4_INPUT_REPORT_0x11_SIZE 78
#घोषणा DS4_OUTPUT_REPORT_0x05_SIZE 32
#घोषणा DS4_OUTPUT_REPORT_0x11_SIZE 78
#घोषणा SIXAXIS_REPORT_0xF2_SIZE 17
#घोषणा SIXAXIS_REPORT_0xF5_SIZE 8
#घोषणा MOTION_REPORT_0x02_SIZE 49

/* Offsets relative to USB input report (0x1). Bluetooth (0x11) requires an
 * additional +2.
 */
#घोषणा DS4_INPUT_REPORT_AXIS_OFFSET      1
#घोषणा DS4_INPUT_REPORT_BUTTON_OFFSET    5
#घोषणा DS4_INPUT_REPORT_TIMESTAMP_OFFSET 10
#घोषणा DS4_INPUT_REPORT_GYRO_X_OFFSET   13
#घोषणा DS4_INPUT_REPORT_BATTERY_OFFSET  30
#घोषणा DS4_INPUT_REPORT_TOUCHPAD_OFFSET 33

#घोषणा SENSOR_SUFFIX " Motion Sensors"
#घोषणा DS4_TOUCHPAD_SUFFIX " Touchpad"

/* Default to 4ms poll पूर्णांकerval, which is same as USB (not adjustable). */
#घोषणा DS4_BT_DEFAULT_POLL_INTERVAL_MS 4
#घोषणा DS4_BT_MAX_POLL_INTERVAL_MS 62
#घोषणा DS4_GYRO_RES_PER_DEG_S 1024
#घोषणा DS4_ACC_RES_PER_G      8192

#घोषणा SIXAXIS_INPUT_REPORT_ACC_X_OFFSET 41
#घोषणा SIXAXIS_ACC_RES_PER_G 113

अटल DEFINE_SPINLOCK(sony_dev_list_lock);
अटल LIST_HEAD(sony_device_list);
अटल DEFINE_IDA(sony_device_id_allocator);

/* Used क्रम calibration of DS4 accelerometer and gyro. */
काष्ठा ds4_calibration_data अणु
	पूर्णांक असल_code;
	लघु bias;
	/* Calibration requires scaling against a sensitivity value, which is a
	 * भग्न. Store sensitivity as a fraction to limit भग्नing poपूर्णांक
	 * calculations until final calibration.
	 */
	पूर्णांक sens_numer;
	पूर्णांक sens_denom;
पूर्ण;

क्रमागत ds4_करोngle_state अणु
	DONGLE_DISCONNECTED,
	DONGLE_CALIBRATING,
	DONGLE_CONNECTED,
	DONGLE_DISABLED
पूर्ण;

क्रमागत sony_worker अणु
	SONY_WORKER_STATE,
	SONY_WORKER_HOTPLUG
पूर्ण;

काष्ठा sony_sc अणु
	spinlock_t lock;
	काष्ठा list_head list_node;
	काष्ठा hid_device *hdev;
	काष्ठा input_dev *touchpad;
	काष्ठा input_dev *sensor_dev;
	काष्ठा led_classdev *leds[MAX_LEDS];
	अचिन्हित दीर्घ quirks;
	काष्ठा work_काष्ठा hotplug_worker;
	काष्ठा work_काष्ठा state_worker;
	व्योम (*send_output_report)(काष्ठा sony_sc *);
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply_desc battery_desc;
	पूर्णांक device_id;
	अचिन्हित fw_version;
	bool fw_version_created;
	अचिन्हित hw_version;
	bool hw_version_created;
	u8 *output_report_dmabuf;

#अगर_घोषित CONFIG_SONY_FF
	u8 left;
	u8 right;
#पूर्ण_अगर

	u8 mac_address[6];
	u8 hotplug_worker_initialized;
	u8 state_worker_initialized;
	u8 defer_initialization;
	u8 battery_capacity;
	पूर्णांक battery_status;
	u8 led_state[MAX_LEDS];
	u8 led_delay_on[MAX_LEDS];
	u8 led_delay_off[MAX_LEDS];
	u8 led_count;

	bool बारtamp_initialized;
	u16 prev_बारtamp;
	अचिन्हित पूर्णांक बारtamp_us;

	u8 ds4_bt_poll_पूर्णांकerval;
	क्रमागत ds4_करोngle_state ds4_करोngle_state;
	/* DS4 calibration data */
	काष्ठा ds4_calibration_data ds4_calib_data[6];
	/* GH Live */
	काष्ठा समयr_list ghl_poke_समयr;
	काष्ठा usb_ctrlrequest *ghl_cr;
	u8 *ghl_databuf;
पूर्ण;

अटल व्योम sony_set_leds(काष्ठा sony_sc *sc);

अटल अंतरभूत व्योम sony_schedule_work(काष्ठा sony_sc *sc,
				      क्रमागत sony_worker which)
अणु
	अचिन्हित दीर्घ flags;

	चयन (which) अणु
	हाल SONY_WORKER_STATE:
		spin_lock_irqsave(&sc->lock, flags);
		अगर (!sc->defer_initialization && sc->state_worker_initialized)
			schedule_work(&sc->state_worker);
		spin_unlock_irqrestore(&sc->lock, flags);
		अवरोध;
	हाल SONY_WORKER_HOTPLUG:
		अगर (sc->hotplug_worker_initialized)
			schedule_work(&sc->hotplug_worker);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ghl_magic_poke_cb(काष्ठा urb *urb)
अणु
	अगर (urb) अणु
		/* Free sc->ghl_cr and sc->ghl_databuf allocated in
		 * ghl_magic_poke()
		 */
		kमुक्त(urb->setup_packet);
		kमुक्त(urb->transfer_buffer);
	पूर्ण
पूर्ण

अटल व्योम ghl_magic_poke(काष्ठा समयr_list *t)
अणु
	काष्ठा sony_sc *sc = from_समयr(sc, t, ghl_poke_समयr);

	पूर्णांक ret;
	अचिन्हित पूर्णांक pipe;
	काष्ठा urb *urb;
	काष्ठा usb_device *usbdev = to_usb_device(sc->hdev->dev.parent->parent);
	स्थिर u16 poke_size =
		ARRAY_SIZE(ghl_ps3wiiu_magic_data);

	pipe = usb_sndctrlpipe(usbdev, 0);

	अगर (!sc->ghl_cr) अणु
		sc->ghl_cr = kzalloc(माप(*sc->ghl_cr), GFP_ATOMIC);
		अगर (!sc->ghl_cr)
			जाओ resched;
	पूर्ण

	अगर (!sc->ghl_databuf) अणु
		sc->ghl_databuf = kzalloc(poke_size, GFP_ATOMIC);
		अगर (!sc->ghl_databuf)
			जाओ resched;
	पूर्ण

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		जाओ resched;

	sc->ghl_cr->bRequestType =
		USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_सूची_OUT;
	sc->ghl_cr->bRequest = USB_REQ_SET_CONFIGURATION;
	sc->ghl_cr->wValue = cpu_to_le16(ghl_ps3wiiu_magic_value);
	sc->ghl_cr->wIndex = 0;
	sc->ghl_cr->wLength = cpu_to_le16(poke_size);
	स_नकल(sc->ghl_databuf, ghl_ps3wiiu_magic_data, poke_size);

	usb_fill_control_urb(
		urb, usbdev, pipe,
		(अचिन्हित अक्षर *) sc->ghl_cr, sc->ghl_databuf,
		poke_size, ghl_magic_poke_cb, शून्य);
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret < 0) अणु
		kमुक्त(sc->ghl_databuf);
		kमुक्त(sc->ghl_cr);
	पूर्ण
	usb_मुक्त_urb(urb);

resched:
	/* Reschedule क्रम next समय */
	mod_समयr(&sc->ghl_poke_समयr, jअगरfies + GHL_GUITAR_POKE_INTERVAL*HZ);
पूर्ण

अटल पूर्णांक guitar_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			  काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			  अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOR) अणु
		अचिन्हित पूर्णांक असल = usage->hid & HID_USAGE;

		अगर (असल == GUITAR_TILT_USAGE) अणु
			hid_map_usage_clear(hi, usage, bit, max, EV_ABS, ABS_RY);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ds4_show_poll_पूर्णांकerval(काष्ठा device *dev,
				काष्ठा device_attribute
				*attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%i\n", sc->ds4_bt_poll_पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार ds4_store_poll_पूर्णांकerval(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;
	u8 पूर्णांकerval;

	अगर (kstrtou8(buf, 0, &पूर्णांकerval))
		वापस -EINVAL;

	अगर (पूर्णांकerval > DS4_BT_MAX_POLL_INTERVAL_MS)
		वापस -EINVAL;

	spin_lock_irqsave(&sc->lock, flags);
	sc->ds4_bt_poll_पूर्णांकerval = पूर्णांकerval;
	spin_unlock_irqrestore(&sc->lock, flags);

	sony_schedule_work(sc, SONY_WORKER_STATE);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(bt_poll_पूर्णांकerval, 0644, ds4_show_poll_पूर्णांकerval,
		ds4_store_poll_पूर्णांकerval);

अटल sमाप_प्रकार sony_show_firmware_version(काष्ठा device *dev,
				काष्ठा device_attribute
				*attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%04x\n", sc->fw_version);
पूर्ण

अटल DEVICE_ATTR(firmware_version, 0444, sony_show_firmware_version, शून्य);

अटल sमाप_प्रकार sony_show_hardware_version(काष्ठा device *dev,
				काष्ठा device_attribute
				*attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);

	वापस snम_लिखो(buf, PAGE_SIZE, "0x%04x\n", sc->hw_version);
पूर्ण

अटल DEVICE_ATTR(hardware_version, 0444, sony_show_hardware_version, शून्य);

अटल u8 *motion_fixup(काष्ठा hid_device *hdev, u8 *rdesc,
			     अचिन्हित पूर्णांक *rsize)
अणु
	*rsize = माप(motion_rdesc);
	वापस motion_rdesc;
पूर्ण

अटल u8 *ps3remote_fixup(काष्ठा hid_device *hdev, u8 *rdesc,
			     अचिन्हित पूर्णांक *rsize)
अणु
	*rsize = माप(ps3remote_rdesc);
	वापस ps3remote_rdesc;
पूर्ण

अटल पूर्णांक ps3remote_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			     काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			     अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अचिन्हित पूर्णांक key = usage->hid & HID_USAGE;

	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
		वापस -1;

	चयन (usage->collection_index) अणु
	हाल 1:
		अगर (key >= ARRAY_SIZE(ps3remote_keymap_joypad_buttons))
			वापस -1;

		key = ps3remote_keymap_joypad_buttons[key];
		अगर (!key)
			वापस -1;
		अवरोध;
	हाल 2:
		अगर (key >= ARRAY_SIZE(ps3remote_keymap_remote_buttons))
			वापस -1;

		key = ps3remote_keymap_remote_buttons[key];
		अगर (!key)
			वापस -1;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	hid_map_usage_clear(hi, usage, bit, max, EV_KEY, key);
	वापस 1;
पूर्ण

अटल पूर्णांक navigation_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			  काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			  अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) अणु
		अचिन्हित पूर्णांक key = usage->hid & HID_USAGE;

		अगर (key >= ARRAY_SIZE(sixaxis_keymap))
			वापस -1;

		key = navigation_keymap[key];
		अगर (!key)
			वापस -1;

		hid_map_usage_clear(hi, usage, bit, max, EV_KEY, key);
		वापस 1;
	पूर्ण अन्यथा अगर (usage->hid == HID_GD_POINTER) अणु
		/* See comment in sixaxis_mapping, basically the L2 (and R2)
		 * triggers are reported through GD Poपूर्णांकer.
		 * In addition we ignore any analog button 'axes' and only
		 * support digital buttons.
		 */
		चयन (usage->usage_index) अणु
		हाल 8: /* L2 */
			usage->hid = HID_GD_Z;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण

		hid_map_usage_clear(hi, usage, bit, max, EV_ABS, usage->hid & 0xf);
		वापस 1;
	पूर्ण अन्यथा अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_GENDESK) अणु
		अचिन्हित पूर्णांक असल = usage->hid & HID_USAGE;

		अगर (असल >= ARRAY_SIZE(navigation_असलmap))
			वापस -1;

		असल = navigation_असलmap[असल];

		hid_map_usage_clear(hi, usage, bit, max, EV_ABS, असल);
		वापस 1;
	पूर्ण

	वापस -1;
पूर्ण


अटल पूर्णांक sixaxis_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			  काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			  अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) अणु
		अचिन्हित पूर्णांक key = usage->hid & HID_USAGE;

		अगर (key >= ARRAY_SIZE(sixaxis_keymap))
			वापस -1;

		key = sixaxis_keymap[key];
		hid_map_usage_clear(hi, usage, bit, max, EV_KEY, key);
		वापस 1;
	पूर्ण अन्यथा अगर (usage->hid == HID_GD_POINTER) अणु
		/* The DS3 provides analog values क्रम most buttons and even
		 * क्रम HAT axes through GD Poपूर्णांकer. L2 and R2 are reported
		 * among these as well instead of as GD Z / RZ. Remap L2
		 * and R2 and ignore other analog 'button axes' as there is
		 * no good way क्रम reporting them.
		 */
		चयन (usage->usage_index) अणु
		हाल 8: /* L2 */
			usage->hid = HID_GD_Z;
			अवरोध;
		हाल 9: /* R2 */
			usage->hid = HID_GD_RZ;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण

		hid_map_usage_clear(hi, usage, bit, max, EV_ABS, usage->hid & 0xf);
		वापस 1;
	पूर्ण अन्यथा अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_GENDESK) अणु
		अचिन्हित पूर्णांक असल = usage->hid & HID_USAGE;

		अगर (असल >= ARRAY_SIZE(sixaxis_असलmap))
			वापस -1;

		असल = sixaxis_असलmap[असल];

		hid_map_usage_clear(hi, usage, bit, max, EV_ABS, असल);
		वापस 1;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक ds4_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		       काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		       अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) अणु
		अचिन्हित पूर्णांक key = usage->hid & HID_USAGE;

		अगर (key >= ARRAY_SIZE(ds4_keymap))
			वापस -1;

		key = ds4_keymap[key];
		hid_map_usage_clear(hi, usage, bit, max, EV_KEY, key);
		वापस 1;
	पूर्ण अन्यथा अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_GENDESK) अणु
		अचिन्हित पूर्णांक असल = usage->hid & HID_USAGE;

		/* Let the HID parser deal with the HAT. */
		अगर (usage->hid == HID_GD_HATSWITCH)
			वापस 0;

		अगर (असल >= ARRAY_SIZE(ds4_असलmap))
			वापस -1;

		असल = ds4_असलmap[असल];
		hid_map_usage_clear(hi, usage, bit, max, EV_ABS, असल);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 *sony_report_fixup(काष्ठा hid_device *hdev, u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);

	अगर (sc->quirks & (SINO_LITE_CONTROLLER | FUTUREMAX_DANCE_MAT))
		वापस rdesc;

	/*
	 * Some Sony RF receivers wrongly declare the mouse poपूर्णांकer as a
	 * a स्थिरant non-data variable.
	 */
	अगर ((sc->quirks & VAIO_RDESC_CONSTANT) && *rsize >= 56 &&
	    /* usage page: generic desktop controls */
	    /* rdesc[0] == 0x05 && rdesc[1] == 0x01 && */
	    /* usage: mouse */
	    rdesc[2] == 0x09 && rdesc[3] == 0x02 &&
	    /* input (usage page क्रम x,y axes): स्थिरant, variable, relative */
	    rdesc[54] == 0x81 && rdesc[55] == 0x07) अणु
		hid_info(hdev, "Fixing up Sony RF Receiver report descriptor\n");
		/* input: data, variable, relative */
		rdesc[55] = 0x06;
	पूर्ण

	अगर (sc->quirks & MOTION_CONTROLLER)
		वापस motion_fixup(hdev, rdesc, rsize);

	अगर (sc->quirks & PS3REMOTE)
		वापस ps3remote_fixup(hdev, rdesc, rsize);

	/*
	 * Some knock-off USB करोngles incorrectly report their button count
	 * as 13 instead of 16 causing three non-functional buttons.
	 */
	अगर ((sc->quirks & SIXAXIS_CONTROLLER_USB) && *rsize >= 45 &&
		/* Report Count (13) */
		rdesc[23] == 0x95 && rdesc[24] == 0x0D &&
		/* Usage Maximum (13) */
		rdesc[37] == 0x29 && rdesc[38] == 0x0D &&
		/* Report Count (3) */
		rdesc[43] == 0x95 && rdesc[44] == 0x03) अणु
		hid_info(hdev, "Fixing up USB dongle report descriptor\n");
		rdesc[24] = 0x10;
		rdesc[38] = 0x10;
		rdesc[44] = 0x00;
	पूर्ण

	वापस rdesc;
पूर्ण

अटल व्योम sixaxis_parse_report(काष्ठा sony_sc *sc, u8 *rd, पूर्णांक size)
अणु
	अटल स्थिर u8 sixaxis_battery_capacity[] = अणु 0, 1, 25, 50, 75, 100 पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक offset;
	u8 battery_capacity;
	पूर्णांक battery_status;

	/*
	 * The sixaxis is अक्षरging अगर the battery value is 0xee
	 * and it is fully अक्षरged अगर the value is 0xef.
	 * It करोes not report the actual level जबतक अक्षरging so it
	 * is set to 100% जबतक अक्षरging is in progress.
	 */
	offset = (sc->quirks & MOTION_CONTROLLER) ? 12 : 30;

	अगर (rd[offset] >= 0xee) अणु
		battery_capacity = 100;
		battery_status = (rd[offset] & 0x01) ? POWER_SUPPLY_STATUS_FULL : POWER_SUPPLY_STATUS_CHARGING;
	पूर्ण अन्यथा अणु
		u8 index = rd[offset] <= 5 ? rd[offset] : 5;
		battery_capacity = sixaxis_battery_capacity[index];
		battery_status = POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण

	spin_lock_irqsave(&sc->lock, flags);
	sc->battery_capacity = battery_capacity;
	sc->battery_status = battery_status;
	spin_unlock_irqrestore(&sc->lock, flags);

	अगर (sc->quirks & SIXAXIS_CONTROLLER) अणु
		पूर्णांक val;

		offset = SIXAXIS_INPUT_REPORT_ACC_X_OFFSET;
		val = ((rd[offset+1] << 8) | rd[offset]) - 511;
		input_report_असल(sc->sensor_dev, ABS_X, val);

		/* Y and Z are swapped and inversed */
		val = 511 - ((rd[offset+5] << 8) | rd[offset+4]);
		input_report_असल(sc->sensor_dev, ABS_Y, val);

		val = 511 - ((rd[offset+3] << 8) | rd[offset+2]);
		input_report_असल(sc->sensor_dev, ABS_Z, val);

		input_sync(sc->sensor_dev);
	पूर्ण
पूर्ण

अटल व्योम dualshock4_parse_report(काष्ठा sony_sc *sc, u8 *rd, पूर्णांक size)
अणु
	काष्ठा hid_input *hidinput = list_entry(sc->hdev->inमाला_दो.next,
						काष्ठा hid_input, list);
	काष्ठा input_dev *input_dev = hidinput->input;
	अचिन्हित दीर्घ flags;
	पूर्णांक n, m, offset, num_touch_data, max_touch_data;
	u8 cable_state, battery_capacity;
	पूर्णांक battery_status;
	u16 बारtamp;

	/* When using Bluetooth the header is 2 bytes दीर्घer, so skip these. */
	पूर्णांक data_offset = (sc->quirks & DUALSHOCK4_CONTROLLER_BT) ? 2 : 0;

	/* Second bit of third button byte is क्रम the touchpad button. */
	offset = data_offset + DS4_INPUT_REPORT_BUTTON_OFFSET;
	input_report_key(sc->touchpad, BTN_LEFT, rd[offset+2] & 0x2);

	/*
	 * The शेष behavior of the Dualshock 4 is to send reports using
	 * report type 1 when running over Bluetooth. However, when feature
	 * report 2 is requested during the controller initialization it starts
	 * sending input reports in report 17. Since report 17 is undefined
	 * in the शेष HID descriptor, the HID layer won't generate events.
	 * While it is possible (and this was करोne beक्रमe) to fixup the HID
	 * descriptor to add this mapping, it was better to करो this manually.
	 * The reason is there were various pieces software both खोलो and बंदd
	 * source, relying on the descriptors to be the same across various
	 * operating प्रणालीs. If the descriptors wouldn't match some
	 * applications e.g. games on Wine would not be able to function due
	 * to dअगरferent descriptors, which such applications are not parsing.
	 */
	अगर (rd[0] == 17) अणु
		पूर्णांक value;

		offset = data_offset + DS4_INPUT_REPORT_AXIS_OFFSET;
		input_report_असल(input_dev, ABS_X, rd[offset]);
		input_report_असल(input_dev, ABS_Y, rd[offset+1]);
		input_report_असल(input_dev, ABS_RX, rd[offset+2]);
		input_report_असल(input_dev, ABS_RY, rd[offset+3]);

		value = rd[offset+4] & 0xf;
		अगर (value > 7)
			value = 8; /* Center 0, 0 */
		input_report_असल(input_dev, ABS_HAT0X, ds4_hat_mapping[value].x);
		input_report_असल(input_dev, ABS_HAT0Y, ds4_hat_mapping[value].y);

		input_report_key(input_dev, BTN_WEST, rd[offset+4] & 0x10);
		input_report_key(input_dev, BTN_SOUTH, rd[offset+4] & 0x20);
		input_report_key(input_dev, BTN_EAST, rd[offset+4] & 0x40);
		input_report_key(input_dev, BTN_NORTH, rd[offset+4] & 0x80);

		input_report_key(input_dev, BTN_TL, rd[offset+5] & 0x1);
		input_report_key(input_dev, BTN_TR, rd[offset+5] & 0x2);
		input_report_key(input_dev, BTN_TL2, rd[offset+5] & 0x4);
		input_report_key(input_dev, BTN_TR2, rd[offset+5] & 0x8);
		input_report_key(input_dev, BTN_SELECT, rd[offset+5] & 0x10);
		input_report_key(input_dev, BTN_START, rd[offset+5] & 0x20);
		input_report_key(input_dev, BTN_THUMBL, rd[offset+5] & 0x40);
		input_report_key(input_dev, BTN_THUMBR, rd[offset+5] & 0x80);

		input_report_key(input_dev, BTN_MODE, rd[offset+6] & 0x1);

		input_report_असल(input_dev, ABS_Z, rd[offset+7]);
		input_report_असल(input_dev, ABS_RZ, rd[offset+8]);

		input_sync(input_dev);
	पूर्ण

	/* Convert बारtamp (in 5.33us unit) to बारtamp_us */
	offset = data_offset + DS4_INPUT_REPORT_TIMESTAMP_OFFSET;
	बारtamp = get_unaligned_le16(&rd[offset]);
	अगर (!sc->बारtamp_initialized) अणु
		sc->बारtamp_us = ((अचिन्हित पूर्णांक)बारtamp * 16) / 3;
		sc->बारtamp_initialized = true;
	पूर्ण अन्यथा अणु
		u16 delta;

		अगर (sc->prev_बारtamp > बारtamp)
			delta = (U16_MAX - sc->prev_बारtamp + बारtamp + 1);
		अन्यथा
			delta = बारtamp - sc->prev_बारtamp;
		sc->बारtamp_us += (delta * 16) / 3;
	पूर्ण
	sc->prev_बारtamp = बारtamp;
	input_event(sc->sensor_dev, EV_MSC, MSC_TIMESTAMP, sc->बारtamp_us);

	offset = data_offset + DS4_INPUT_REPORT_GYRO_X_OFFSET;
	क्रम (n = 0; n < 6; n++) अणु
		/* Store data in पूर्णांक क्रम more precision during mult_frac. */
		पूर्णांक raw_data = (लघु)((rd[offset+1] << 8) | rd[offset]);
		काष्ठा ds4_calibration_data *calib = &sc->ds4_calib_data[n];

		/* High precision is needed during calibration, but the
		 * calibrated values are within 32-bit.
		 * Note: we swap numerator 'x' and 'numer' in mult_frac क्रम
		 *       precision reasons so we करोn't need 64-bit.
		 */
		पूर्णांक calib_data = mult_frac(calib->sens_numer,
					   raw_data - calib->bias,
					   calib->sens_denom);

		input_report_असल(sc->sensor_dev, calib->असल_code, calib_data);
		offset += 2;
	पूर्ण
	input_sync(sc->sensor_dev);

	/*
	 * The lower 4 bits of byte 30 (or 32 क्रम BT) contain the battery level
	 * and the 5th bit contains the USB cable state.
	 */
	offset = data_offset + DS4_INPUT_REPORT_BATTERY_OFFSET;
	cable_state = (rd[offset] >> 4) & 0x01;

	/*
	 * Interpretation of the battery_capacity data depends on the cable state.
	 * When no cable is connected (bit4 is 0):
	 * - 0:10: percentage in units of 10%.
	 * When a cable is plugged in:
	 * - 0-10: percentage in units of 10%.
	 * - 11: battery is full
	 * - 14: not अक्षरging due to Voltage or temperature error
	 * - 15: अक्षरge error
	 */
	अगर (cable_state) अणु
		u8 battery_data = rd[offset] & 0xf;

		अगर (battery_data < 10) अणु
			/* Take the mid-poपूर्णांक क्रम each battery capacity value,
			 * because on the hardware side 0 = 0-9%, 1=10-19%, etc.
			 * This matches official platक्रमm behavior, which करोes
			 * the same.
			 */
			battery_capacity = battery_data * 10 + 5;
			battery_status = POWER_SUPPLY_STATUS_CHARGING;
		पूर्ण अन्यथा अगर (battery_data == 10) अणु
			battery_capacity = 100;
			battery_status = POWER_SUPPLY_STATUS_CHARGING;
		पूर्ण अन्यथा अगर (battery_data == 11) अणु
			battery_capacity = 100;
			battery_status = POWER_SUPPLY_STATUS_FULL;
		पूर्ण अन्यथा अणु /* 14, 15 and undefined values */
			battery_capacity = 0;
			battery_status = POWER_SUPPLY_STATUS_UNKNOWN;
		पूर्ण
	पूर्ण अन्यथा अणु
		u8 battery_data = rd[offset] & 0xf;

		अगर (battery_data < 10)
			battery_capacity = battery_data * 10 + 5;
		अन्यथा /* 10 */
			battery_capacity = 100;

		battery_status = POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण

	spin_lock_irqsave(&sc->lock, flags);
	sc->battery_capacity = battery_capacity;
	sc->battery_status = battery_status;
	spin_unlock_irqrestore(&sc->lock, flags);

	/*
	 * The Dualshock 4 multi-touch trackpad data starts at offset 33 on USB
	 * and 35 on Bluetooth.
	 * The first byte indicates the number of touch data in the report.
	 * Trackpad data starts 2 bytes later (e.g. 35 क्रम USB).
	 */
	offset = data_offset + DS4_INPUT_REPORT_TOUCHPAD_OFFSET;
	max_touch_data = (sc->quirks & DUALSHOCK4_CONTROLLER_BT) ? 4 : 3;
	अगर (rd[offset] > 0 && rd[offset] <= max_touch_data)
		num_touch_data = rd[offset];
	अन्यथा
		num_touch_data = 1;
	offset += 1;

	क्रम (m = 0; m < num_touch_data; m++) अणु
		/* Skip past बारtamp */
		offset += 1;

		/*
		 * The first 7 bits of the first byte is a counter and bit 8 is
		 * a touch indicator that is 0 when pressed and 1 when not
		 * pressed.
		 * The next 3 bytes are two 12 bit touch coordinates, X and Y.
		 * The data क्रम the second touch is in the same क्रमmat and
		 * immediately follows the data क्रम the first.
		 */
		क्रम (n = 0; n < 2; n++) अणु
			u16 x, y;
			bool active;

			x = rd[offset+1] | ((rd[offset+2] & 0xF) << 8);
			y = ((rd[offset+2] & 0xF0) >> 4) | (rd[offset+3] << 4);

			active = !(rd[offset] >> 7);
			input_mt_slot(sc->touchpad, n);
			input_mt_report_slot_state(sc->touchpad, MT_TOOL_FINGER, active);

			अगर (active) अणु
				input_report_असल(sc->touchpad, ABS_MT_POSITION_X, x);
				input_report_असल(sc->touchpad, ABS_MT_POSITION_Y, y);
			पूर्ण

			offset += 4;
		पूर्ण
		input_mt_sync_frame(sc->touchpad);
		input_sync(sc->touchpad);
	पूर्ण
पूर्ण

अटल व्योम nsg_mrxu_parse_report(काष्ठा sony_sc *sc, u8 *rd, पूर्णांक size)
अणु
	पूर्णांक n, offset, relx, rely;
	u8 active;

	/*
	 * The NSG-MRxU multi-touch trackpad data starts at offset 1 and
	 *   the touch-related data starts at offset 2.
	 * For the first byte, bit 0 is set when touchpad button is pressed.
	 * Bit 2 is set when a touch is active and the drag (Fn) key is pressed.
	 * This drag key is mapped to BTN_LEFT.  It is operational only when a 
	 *   touch poपूर्णांक is active.
	 * Bit 4 is set when only the first touch poपूर्णांक is active.
	 * Bit 6 is set when only the second touch poपूर्णांक is active.
	 * Bits 5 and 7 are set when both touch poपूर्णांकs are active.
	 * The next 3 bytes are two 12 bit X/Y coordinates क्रम the first touch.
	 * The following byte, offset 5, has the touch width and length.
	 *   Bits 0-4=X (width), bits 5-7=Y (length).
	 * A चिन्हित relative X coordinate is at offset 6.
	 * The bytes at offset 7-9 are the second touch X/Y coordinates.
	 * Offset 10 has the second touch width and length.
	 * Offset 11 has the relative Y coordinate.
	 */
	offset = 1;

	input_report_key(sc->touchpad, BTN_LEFT, rd[offset] & 0x0F);
	active = (rd[offset] >> 4);
	relx = (s8) rd[offset+5];
	rely = ((s8) rd[offset+10]) * -1;

	offset++;

	क्रम (n = 0; n < 2; n++) अणु
		u16 x, y;
		u8 contactx, contacty;

		x = rd[offset] | ((rd[offset+1] & 0x0F) << 8);
		y = ((rd[offset+1] & 0xF0) >> 4) | (rd[offset+2] << 4);

		input_mt_slot(sc->touchpad, n);
		input_mt_report_slot_state(sc->touchpad, MT_TOOL_FINGER, active & 0x03);

		अगर (active & 0x03) अणु
			contactx = rd[offset+3] & 0x0F;
			contacty = rd[offset+3] >> 4;
			input_report_असल(sc->touchpad, ABS_MT_TOUCH_MAJOR,
				max(contactx, contacty));
			input_report_असल(sc->touchpad, ABS_MT_TOUCH_MINOR,
				min(contactx, contacty));
			input_report_असल(sc->touchpad, ABS_MT_ORIENTATION,
				(bool) (contactx > contacty));
			input_report_असल(sc->touchpad, ABS_MT_POSITION_X, x);
			input_report_असल(sc->touchpad, ABS_MT_POSITION_Y,
				NSG_MRXU_MAX_Y - y);
			/*
			 * The relative coordinates beदीर्घ to the first touch
			 * poपूर्णांक, when present, or to the second touch poपूर्णांक
			 * when the first is not active.
			 */
			अगर ((n == 0) || ((n == 1) && (active & 0x01))) अणु
				input_report_rel(sc->touchpad, REL_X, relx);
				input_report_rel(sc->touchpad, REL_Y, rely);
			पूर्ण
		पूर्ण

		offset += 5;
		active >>= 2;
	पूर्ण

	input_mt_sync_frame(sc->touchpad);

	input_sync(sc->touchpad);
पूर्ण

अटल पूर्णांक sony_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *rd, पूर्णांक size)
अणु
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);

	/*
	 * Sixaxis HID report has acclerometers/gyro with MSByte first, this
	 * has to be BYTE_SWAPPED beक्रमe passing up to joystick पूर्णांकerface
	 */
	अगर ((sc->quirks & SIXAXIS_CONTROLLER) && rd[0] == 0x01 && size == 49) अणु
		/*
		 * When connected via Bluetooth the Sixaxis occasionally sends
		 * a report with the second byte 0xff and the rest zeroed.
		 *
		 * This report करोes not reflect the actual state of the
		 * controller must be ignored to aव्योम generating false input
		 * events.
		 */
		अगर (rd[1] == 0xff)
			वापस -EINVAL;

		swap(rd[41], rd[42]);
		swap(rd[43], rd[44]);
		swap(rd[45], rd[46]);
		swap(rd[47], rd[48]);

		sixaxis_parse_report(sc, rd, size);
	पूर्ण अन्यथा अगर ((sc->quirks & MOTION_CONTROLLER_BT) && rd[0] == 0x01 && size == 49) अणु
		sixaxis_parse_report(sc, rd, size);
	पूर्ण अन्यथा अगर ((sc->quirks & NAVIGATION_CONTROLLER) && rd[0] == 0x01 &&
			size == 49) अणु
		sixaxis_parse_report(sc, rd, size);
	पूर्ण अन्यथा अगर ((sc->quirks & DUALSHOCK4_CONTROLLER_USB) && rd[0] == 0x01 &&
			size == 64) अणु
		dualshock4_parse_report(sc, rd, size);
	पूर्ण अन्यथा अगर (((sc->quirks & DUALSHOCK4_CONTROLLER_BT) && rd[0] == 0x11 &&
			size == 78)) अणु
		/* CRC check */
		u8 bthdr = 0xA1;
		u32 crc;
		u32 report_crc;

		crc = crc32_le(0xFFFFFFFF, &bthdr, 1);
		crc = ~crc32_le(crc, rd, DS4_INPUT_REPORT_0x11_SIZE-4);
		report_crc = get_unaligned_le32(&rd[DS4_INPUT_REPORT_0x11_SIZE-4]);
		अगर (crc != report_crc) अणु
			hid_dbg(sc->hdev, "DualShock 4 input report's CRC check failed, received crc 0x%0x != 0x%0x\n",
				report_crc, crc);
			वापस -EILSEQ;
		पूर्ण

		dualshock4_parse_report(sc, rd, size);
	पूर्ण अन्यथा अगर ((sc->quirks & DUALSHOCK4_DONGLE) && rd[0] == 0x01 &&
			size == 64) अणु
		अचिन्हित दीर्घ flags;
		क्रमागत ds4_करोngle_state करोngle_state;

		/*
		 * In the हाल of a DS4 USB करोngle, bit[2] of byte 31 indicates
		 * अगर a DS4 is actually connected (indicated by '0').
		 * For non-करोngle, this bit is always 0 (connected).
		 */
		bool connected = (rd[31] & 0x04) ? false : true;

		spin_lock_irqsave(&sc->lock, flags);
		करोngle_state = sc->ds4_करोngle_state;
		spin_unlock_irqrestore(&sc->lock, flags);

		/*
		 * The करोngle always sends input reports even when no
		 * DS4 is attached. When a DS4 is connected, we need to
		 * obtain calibration data beक्रमe we can use it.
		 * The code below tracks करोngle state and kicks of
		 * calibration when needed and only allows us to process
		 * input अगर a DS4 is actually connected.
		 */
		अगर (करोngle_state == DONGLE_DISCONNECTED && connected) अणु
			hid_info(sc->hdev, "DualShock 4 USB dongle: controller connected\n");
			sony_set_leds(sc);

			spin_lock_irqsave(&sc->lock, flags);
			sc->ds4_करोngle_state = DONGLE_CALIBRATING;
			spin_unlock_irqrestore(&sc->lock, flags);

			sony_schedule_work(sc, SONY_WORKER_HOTPLUG);

			/* Don't process the report since we don't have
			 * calibration data, but let hidraw have it anyway.
			 */
			वापस 0;
		पूर्ण अन्यथा अगर ((करोngle_state == DONGLE_CONNECTED ||
			    करोngle_state == DONGLE_DISABLED) && !connected) अणु
			hid_info(sc->hdev, "DualShock 4 USB dongle: controller disconnected\n");

			spin_lock_irqsave(&sc->lock, flags);
			sc->ds4_करोngle_state = DONGLE_DISCONNECTED;
			spin_unlock_irqrestore(&sc->lock, flags);

			/* Return 0, so hidraw can get the report. */
			वापस 0;
		पूर्ण अन्यथा अगर (करोngle_state == DONGLE_CALIBRATING ||
			   करोngle_state == DONGLE_DISABLED ||
			   करोngle_state == DONGLE_DISCONNECTED) अणु
			/* Return 0, so hidraw can get the report. */
			वापस 0;
		पूर्ण

		dualshock4_parse_report(sc, rd, size);

	पूर्ण अन्यथा अगर ((sc->quirks & NSG_MRXU_REMOTE) && rd[0] == 0x02) अणु
		nsg_mrxu_parse_report(sc, rd, size);
		वापस 1;
	पूर्ण

	अगर (sc->defer_initialization) अणु
		sc->defer_initialization = 0;
		sony_schedule_work(sc, SONY_WORKER_STATE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sony_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);

	अगर (sc->quirks & BUZZ_CONTROLLER) अणु
		अचिन्हित पूर्णांक key = usage->hid & HID_USAGE;

		अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
			वापस -1;

		चयन (usage->collection_index) अणु
		हाल 1:
			अगर (key >= ARRAY_SIZE(buzz_keymap))
				वापस -1;

			key = buzz_keymap[key];
			अगर (!key)
				वापस -1;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण

		hid_map_usage_clear(hi, usage, bit, max, EV_KEY, key);
		वापस 1;
	पूर्ण

	अगर (sc->quirks & PS3REMOTE)
		वापस ps3remote_mapping(hdev, hi, field, usage, bit, max);

	अगर (sc->quirks & NAVIGATION_CONTROLLER)
		वापस navigation_mapping(hdev, hi, field, usage, bit, max);

	अगर (sc->quirks & SIXAXIS_CONTROLLER)
		वापस sixaxis_mapping(hdev, hi, field, usage, bit, max);

	अगर (sc->quirks & DUALSHOCK4_CONTROLLER)
		वापस ds4_mapping(hdev, hi, field, usage, bit, max);

	अगर (sc->quirks & GH_GUITAR_CONTROLLER)
		वापस guitar_mapping(hdev, hi, field, usage, bit, max);

	/* Let hid-core decide क्रम the others */
	वापस 0;
पूर्ण

अटल पूर्णांक sony_रेजिस्टर_touchpad(काष्ठा sony_sc *sc, पूर्णांक touch_count,
		पूर्णांक w, पूर्णांक h, पूर्णांक touch_major, पूर्णांक touch_minor, पूर्णांक orientation)
अणु
	माप_प्रकार name_sz;
	अक्षर *name;
	पूर्णांक ret;

	sc->touchpad = devm_input_allocate_device(&sc->hdev->dev);
	अगर (!sc->touchpad)
		वापस -ENOMEM;

	input_set_drvdata(sc->touchpad, sc);
	sc->touchpad->dev.parent = &sc->hdev->dev;
	sc->touchpad->phys = sc->hdev->phys;
	sc->touchpad->uniq = sc->hdev->uniq;
	sc->touchpad->id.bustype = sc->hdev->bus;
	sc->touchpad->id.venकरोr = sc->hdev->venकरोr;
	sc->touchpad->id.product = sc->hdev->product;
	sc->touchpad->id.version = sc->hdev->version;

	/* Append a suffix to the controller name as there are various
	 * DS4 compatible non-Sony devices with dअगरferent names.
	 */
	name_sz = म_माप(sc->hdev->name) + माप(DS4_TOUCHPAD_SUFFIX);
	name = devm_kzalloc(&sc->hdev->dev, name_sz, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;
	snम_लिखो(name, name_sz, "%s" DS4_TOUCHPAD_SUFFIX, sc->hdev->name);
	sc->touchpad->name = name;

	/* We map the button underneath the touchpad to BTN_LEFT. */
	__set_bit(EV_KEY, sc->touchpad->evbit);
	__set_bit(BTN_LEFT, sc->touchpad->keybit);
	__set_bit(INPUT_PROP_BUTTONPAD, sc->touchpad->propbit);

	input_set_असल_params(sc->touchpad, ABS_MT_POSITION_X, 0, w, 0, 0);
	input_set_असल_params(sc->touchpad, ABS_MT_POSITION_Y, 0, h, 0, 0);

	अगर (touch_major > 0) अणु
		input_set_असल_params(sc->touchpad, ABS_MT_TOUCH_MAJOR, 
			0, touch_major, 0, 0);
		अगर (touch_minor > 0)
			input_set_असल_params(sc->touchpad, ABS_MT_TOUCH_MINOR, 
				0, touch_minor, 0, 0);
		अगर (orientation > 0)
			input_set_असल_params(sc->touchpad, ABS_MT_ORIENTATION, 
				0, orientation, 0, 0);
	पूर्ण

	अगर (sc->quirks & NSG_MRXU_REMOTE) अणु
		__set_bit(EV_REL, sc->touchpad->evbit);
	पूर्ण

	ret = input_mt_init_slots(sc->touchpad, touch_count, INPUT_MT_POINTER);
	अगर (ret < 0)
		वापस ret;

	ret = input_रेजिस्टर_device(sc->touchpad);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sony_रेजिस्टर_sensors(काष्ठा sony_sc *sc)
अणु
	माप_प्रकार name_sz;
	अक्षर *name;
	पूर्णांक ret;
	पूर्णांक range;

	sc->sensor_dev = devm_input_allocate_device(&sc->hdev->dev);
	अगर (!sc->sensor_dev)
		वापस -ENOMEM;

	input_set_drvdata(sc->sensor_dev, sc);
	sc->sensor_dev->dev.parent = &sc->hdev->dev;
	sc->sensor_dev->phys = sc->hdev->phys;
	sc->sensor_dev->uniq = sc->hdev->uniq;
	sc->sensor_dev->id.bustype = sc->hdev->bus;
	sc->sensor_dev->id.venकरोr = sc->hdev->venकरोr;
	sc->sensor_dev->id.product = sc->hdev->product;
	sc->sensor_dev->id.version = sc->hdev->version;

	/* Append a suffix to the controller name as there are various
	 * DS4 compatible non-Sony devices with dअगरferent names.
	 */
	name_sz = म_माप(sc->hdev->name) + माप(SENSOR_SUFFIX);
	name = devm_kzalloc(&sc->hdev->dev, name_sz, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;
	snम_लिखो(name, name_sz, "%s" SENSOR_SUFFIX, sc->hdev->name);
	sc->sensor_dev->name = name;

	अगर (sc->quirks & SIXAXIS_CONTROLLER) अणु
		/* For the DS3 we only support the accelerometer, which works
		 * quite well even without calibration. The device also has
		 * a 1-axis gyro, but it is very dअगरficult to manage from within
		 * the driver even to get data, the sensor is inaccurate and
		 * the behavior is very dअगरferent between hardware revisions.
		 */
		input_set_असल_params(sc->sensor_dev, ABS_X, -512, 511, 4, 0);
		input_set_असल_params(sc->sensor_dev, ABS_Y, -512, 511, 4, 0);
		input_set_असल_params(sc->sensor_dev, ABS_Z, -512, 511, 4, 0);
		input_असल_set_res(sc->sensor_dev, ABS_X, SIXAXIS_ACC_RES_PER_G);
		input_असल_set_res(sc->sensor_dev, ABS_Y, SIXAXIS_ACC_RES_PER_G);
		input_असल_set_res(sc->sensor_dev, ABS_Z, SIXAXIS_ACC_RES_PER_G);
	पूर्ण अन्यथा अगर (sc->quirks & DUALSHOCK4_CONTROLLER) अणु
		range = DS4_ACC_RES_PER_G*4;
		input_set_असल_params(sc->sensor_dev, ABS_X, -range, range, 16, 0);
		input_set_असल_params(sc->sensor_dev, ABS_Y, -range, range, 16, 0);
		input_set_असल_params(sc->sensor_dev, ABS_Z, -range, range, 16, 0);
		input_असल_set_res(sc->sensor_dev, ABS_X, DS4_ACC_RES_PER_G);
		input_असल_set_res(sc->sensor_dev, ABS_Y, DS4_ACC_RES_PER_G);
		input_असल_set_res(sc->sensor_dev, ABS_Z, DS4_ACC_RES_PER_G);

		range = DS4_GYRO_RES_PER_DEG_S*2048;
		input_set_असल_params(sc->sensor_dev, ABS_RX, -range, range, 16, 0);
		input_set_असल_params(sc->sensor_dev, ABS_RY, -range, range, 16, 0);
		input_set_असल_params(sc->sensor_dev, ABS_RZ, -range, range, 16, 0);
		input_असल_set_res(sc->sensor_dev, ABS_RX, DS4_GYRO_RES_PER_DEG_S);
		input_असल_set_res(sc->sensor_dev, ABS_RY, DS4_GYRO_RES_PER_DEG_S);
		input_असल_set_res(sc->sensor_dev, ABS_RZ, DS4_GYRO_RES_PER_DEG_S);

		__set_bit(EV_MSC, sc->sensor_dev->evbit);
		__set_bit(MSC_TIMESTAMP, sc->sensor_dev->mscbit);
	पूर्ण

	__set_bit(INPUT_PROP_ACCELEROMETER, sc->sensor_dev->propbit);

	ret = input_रेजिस्टर_device(sc->sensor_dev);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Sending HID_REQ_GET_REPORT changes the operation mode of the ps3 controller
 * to "operational".  Without this, the ps3 controller will not report any
 * events.
 */
अटल पूर्णांक sixaxis_set_operational_usb(काष्ठा hid_device *hdev)
अणु
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);
	स्थिर पूर्णांक buf_size =
		max(SIXAXIS_REPORT_0xF2_SIZE, SIXAXIS_REPORT_0xF5_SIZE);
	u8 *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(hdev, 0xf2, buf, SIXAXIS_REPORT_0xF2_SIZE,
				 HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
	अगर (ret < 0) अणु
		hid_err(hdev, "can't set operational mode: step 1\n");
		जाओ out;
	पूर्ण

	/*
	 * Some compatible controllers like the Speedlink Strike FX and
	 * Gasia need another query plus an USB पूर्णांकerrupt to get operational.
	 */
	ret = hid_hw_raw_request(hdev, 0xf5, buf, SIXAXIS_REPORT_0xF5_SIZE,
				 HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
	अगर (ret < 0) अणु
		hid_err(hdev, "can't set operational mode: step 2\n");
		जाओ out;
	पूर्ण

	/*
	 * But the USB पूर्णांकerrupt would cause SHANWAN controllers to
	 * start rumbling non-stop, so skip step 3 क्रम these controllers.
	 */
	अगर (sc->quirks & SHANWAN_GAMEPAD)
		जाओ out;

	ret = hid_hw_output_report(hdev, buf, 1);
	अगर (ret < 0) अणु
		hid_info(hdev, "can't set operational mode: step 3, ignoring\n");
		ret = 0;
	पूर्ण

out:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक sixaxis_set_operational_bt(काष्ठा hid_device *hdev)
अणु
	अटल स्थिर u8 report[] = अणु 0xf4, 0x42, 0x03, 0x00, 0x00 पूर्ण;
	u8 *buf;
	पूर्णांक ret;

	buf = kmemdup(report, माप(report), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(hdev, buf[0], buf, माप(report),
				  HID_FEATURE_REPORT, HID_REQ_SET_REPORT);

	kमुक्त(buf);

	वापस ret;
पूर्ण

/*
 * Request DS4 calibration data क्रम the motion sensors.
 * For Bluetooth this also affects the operating mode (see below).
 */
अटल पूर्णांक dualshock4_get_calibration_data(काष्ठा sony_sc *sc)
अणु
	u8 *buf;
	पूर्णांक ret;
	लघु gyro_pitch_bias, gyro_pitch_plus, gyro_pitch_minus;
	लघु gyro_yaw_bias, gyro_yaw_plus, gyro_yaw_minus;
	लघु gyro_roll_bias, gyro_roll_plus, gyro_roll_minus;
	लघु gyro_speed_plus, gyro_speed_minus;
	लघु acc_x_plus, acc_x_minus;
	लघु acc_y_plus, acc_y_minus;
	लघु acc_z_plus, acc_z_minus;
	पूर्णांक speed_2x;
	पूर्णांक range_2g;

	/* For Bluetooth we use a dअगरferent request, which supports CRC.
	 * Note: in Bluetooth mode feature report 0x02 also changes the state
	 * of the controller, so that it sends input reports of type 0x11.
	 */
	अगर (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE)) अणु
		पूर्णांक retries;

		buf = kदो_स्मृति(DS4_FEATURE_REPORT_0x02_SIZE, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		/* We should normally receive the feature report data we asked
		 * क्रम, but hidraw applications such as Steam can issue feature
		 * reports as well. In particular क्रम Dongle reconnects, Steam
		 * and this function are competing resulting in often receiving
		 * data क्रम a dअगरferent HID report, so retry a few बार.
		 */
		क्रम (retries = 0; retries < 3; retries++) अणु
			ret = hid_hw_raw_request(sc->hdev, 0x02, buf,
						 DS4_FEATURE_REPORT_0x02_SIZE,
						 HID_FEATURE_REPORT,
						 HID_REQ_GET_REPORT);
			अगर (ret < 0)
				जाओ err_stop;

			अगर (buf[0] != 0x02) अणु
				अगर (retries < 2) अणु
					hid_warn(sc->hdev, "Retrying DualShock 4 get calibration report (0x02) request\n");
					जारी;
				पूर्ण अन्यथा अणु
					ret = -EILSEQ;
					जाओ err_stop;
				पूर्ण
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		u8 bthdr = 0xA3;
		u32 crc;
		u32 report_crc;
		पूर्णांक retries;

		buf = kदो_स्मृति(DS4_FEATURE_REPORT_0x05_SIZE, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		क्रम (retries = 0; retries < 3; retries++) अणु
			ret = hid_hw_raw_request(sc->hdev, 0x05, buf,
						 DS4_FEATURE_REPORT_0x05_SIZE,
						 HID_FEATURE_REPORT,
						 HID_REQ_GET_REPORT);
			अगर (ret < 0)
				जाओ err_stop;

			/* CRC check */
			crc = crc32_le(0xFFFFFFFF, &bthdr, 1);
			crc = ~crc32_le(crc, buf, DS4_FEATURE_REPORT_0x05_SIZE-4);
			report_crc = get_unaligned_le32(&buf[DS4_FEATURE_REPORT_0x05_SIZE-4]);
			अगर (crc != report_crc) अणु
				hid_warn(sc->hdev, "DualShock 4 calibration report's CRC check failed, received crc 0x%0x != 0x%0x\n",
					report_crc, crc);
				अगर (retries < 2) अणु
					hid_warn(sc->hdev, "Retrying DualShock 4 get calibration report request\n");
					जारी;
				पूर्ण अन्यथा अणु
					ret = -EILSEQ;
					जाओ err_stop;
				पूर्ण
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	gyro_pitch_bias  = get_unaligned_le16(&buf[1]);
	gyro_yaw_bias    = get_unaligned_le16(&buf[3]);
	gyro_roll_bias   = get_unaligned_le16(&buf[5]);
	अगर (sc->quirks & DUALSHOCK4_CONTROLLER_USB) अणु
		gyro_pitch_plus  = get_unaligned_le16(&buf[7]);
		gyro_pitch_minus = get_unaligned_le16(&buf[9]);
		gyro_yaw_plus    = get_unaligned_le16(&buf[11]);
		gyro_yaw_minus   = get_unaligned_le16(&buf[13]);
		gyro_roll_plus   = get_unaligned_le16(&buf[15]);
		gyro_roll_minus  = get_unaligned_le16(&buf[17]);
	पूर्ण अन्यथा अणु
		/* BT + Dongle */
		gyro_pitch_plus  = get_unaligned_le16(&buf[7]);
		gyro_yaw_plus    = get_unaligned_le16(&buf[9]);
		gyro_roll_plus   = get_unaligned_le16(&buf[11]);
		gyro_pitch_minus = get_unaligned_le16(&buf[13]);
		gyro_yaw_minus   = get_unaligned_le16(&buf[15]);
		gyro_roll_minus  = get_unaligned_le16(&buf[17]);
	पूर्ण
	gyro_speed_plus  = get_unaligned_le16(&buf[19]);
	gyro_speed_minus = get_unaligned_le16(&buf[21]);
	acc_x_plus       = get_unaligned_le16(&buf[23]);
	acc_x_minus      = get_unaligned_le16(&buf[25]);
	acc_y_plus       = get_unaligned_le16(&buf[27]);
	acc_y_minus      = get_unaligned_le16(&buf[29]);
	acc_z_plus       = get_unaligned_le16(&buf[31]);
	acc_z_minus      = get_unaligned_le16(&buf[33]);

	/* Set gyroscope calibration and normalization parameters.
	 * Data values will be normalized to 1/DS4_GYRO_RES_PER_DEG_S degree/s.
	 */
	speed_2x = (gyro_speed_plus + gyro_speed_minus);
	sc->ds4_calib_data[0].असल_code = ABS_RX;
	sc->ds4_calib_data[0].bias = gyro_pitch_bias;
	sc->ds4_calib_data[0].sens_numer = speed_2x*DS4_GYRO_RES_PER_DEG_S;
	sc->ds4_calib_data[0].sens_denom = gyro_pitch_plus - gyro_pitch_minus;

	sc->ds4_calib_data[1].असल_code = ABS_RY;
	sc->ds4_calib_data[1].bias = gyro_yaw_bias;
	sc->ds4_calib_data[1].sens_numer = speed_2x*DS4_GYRO_RES_PER_DEG_S;
	sc->ds4_calib_data[1].sens_denom = gyro_yaw_plus - gyro_yaw_minus;

	sc->ds4_calib_data[2].असल_code = ABS_RZ;
	sc->ds4_calib_data[2].bias = gyro_roll_bias;
	sc->ds4_calib_data[2].sens_numer = speed_2x*DS4_GYRO_RES_PER_DEG_S;
	sc->ds4_calib_data[2].sens_denom = gyro_roll_plus - gyro_roll_minus;

	/* Set accelerometer calibration and normalization parameters.
	 * Data values will be normalized to 1/DS4_ACC_RES_PER_G G.
	 */
	range_2g = acc_x_plus - acc_x_minus;
	sc->ds4_calib_data[3].असल_code = ABS_X;
	sc->ds4_calib_data[3].bias = acc_x_plus - range_2g / 2;
	sc->ds4_calib_data[3].sens_numer = 2*DS4_ACC_RES_PER_G;
	sc->ds4_calib_data[3].sens_denom = range_2g;

	range_2g = acc_y_plus - acc_y_minus;
	sc->ds4_calib_data[4].असल_code = ABS_Y;
	sc->ds4_calib_data[4].bias = acc_y_plus - range_2g / 2;
	sc->ds4_calib_data[4].sens_numer = 2*DS4_ACC_RES_PER_G;
	sc->ds4_calib_data[4].sens_denom = range_2g;

	range_2g = acc_z_plus - acc_z_minus;
	sc->ds4_calib_data[5].असल_code = ABS_Z;
	sc->ds4_calib_data[5].bias = acc_z_plus - range_2g / 2;
	sc->ds4_calib_data[5].sens_numer = 2*DS4_ACC_RES_PER_G;
	sc->ds4_calib_data[5].sens_denom = range_2g;

err_stop:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम dualshock4_calibration_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sony_sc *sc = container_of(work, काष्ठा sony_sc, hotplug_worker);
	अचिन्हित दीर्घ flags;
	क्रमागत ds4_करोngle_state करोngle_state;
	पूर्णांक ret;

	ret = dualshock4_get_calibration_data(sc);
	अगर (ret < 0) अणु
		/* This call is very unlikely to fail क्रम the करोngle. When it
		 * fails we are probably in a very bad state, so mark the
		 * करोngle as disabled. We will re-enable the करोngle अगर a new
		 * DS4 hotplug is detect from sony_raw_event as any issues
		 * are likely resolved then (the करोngle is quite stupid).
		 */
		hid_err(sc->hdev, "DualShock 4 USB dongle: calibration failed, disabling device\n");
		करोngle_state = DONGLE_DISABLED;
	पूर्ण अन्यथा अणु
		hid_info(sc->hdev, "DualShock 4 USB dongle: calibration completed\n");
		करोngle_state = DONGLE_CONNECTED;
	पूर्ण

	spin_lock_irqsave(&sc->lock, flags);
	sc->ds4_करोngle_state = करोngle_state;
	spin_unlock_irqrestore(&sc->lock, flags);
पूर्ण

अटल पूर्णांक dualshock4_get_version_info(काष्ठा sony_sc *sc)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(DS4_FEATURE_REPORT_0xA3_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(sc->hdev, 0xA3, buf,
				 DS4_FEATURE_REPORT_0xA3_SIZE,
				 HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	अगर (ret < 0) अणु
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	sc->hw_version = get_unaligned_le16(&buf[35]);
	sc->fw_version = get_unaligned_le16(&buf[41]);

	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल व्योम sixaxis_set_leds_from_id(काष्ठा sony_sc *sc)
अणु
	अटल स्थिर u8 sixaxis_leds[10][4] = अणु
				अणु 0x01, 0x00, 0x00, 0x00 पूर्ण,
				अणु 0x00, 0x01, 0x00, 0x00 पूर्ण,
				अणु 0x00, 0x00, 0x01, 0x00 पूर्ण,
				अणु 0x00, 0x00, 0x00, 0x01 पूर्ण,
				अणु 0x01, 0x00, 0x00, 0x01 पूर्ण,
				अणु 0x00, 0x01, 0x00, 0x01 पूर्ण,
				अणु 0x00, 0x00, 0x01, 0x01 पूर्ण,
				अणु 0x01, 0x00, 0x01, 0x01 पूर्ण,
				अणु 0x00, 0x01, 0x01, 0x01 पूर्ण,
				अणु 0x01, 0x01, 0x01, 0x01 पूर्ण
	पूर्ण;

	पूर्णांक id = sc->device_id;

	BUILD_BUG_ON(MAX_LEDS < ARRAY_SIZE(sixaxis_leds[0]));

	अगर (id < 0)
		वापस;

	id %= 10;
	स_नकल(sc->led_state, sixaxis_leds[id], माप(sixaxis_leds[id]));
पूर्ण

अटल व्योम dualshock4_set_leds_from_id(काष्ठा sony_sc *sc)
अणु
	/* The first 4 color/index entries match what the PS4 assigns */
	अटल स्थिर u8 color_code[7][3] = अणु
			/* Blue   */	अणु 0x00, 0x00, 0x40 पूर्ण,
			/* Red	  */	अणु 0x40, 0x00, 0x00 पूर्ण,
			/* Green  */	अणु 0x00, 0x40, 0x00 पूर्ण,
			/* Pink   */	अणु 0x20, 0x00, 0x20 पूर्ण,
			/* Orange */	अणु 0x02, 0x01, 0x00 पूर्ण,
			/* Teal   */	अणु 0x00, 0x01, 0x01 पूर्ण,
			/* White  */	अणु 0x01, 0x01, 0x01 पूर्ण
	पूर्ण;

	पूर्णांक id = sc->device_id;

	BUILD_BUG_ON(MAX_LEDS < ARRAY_SIZE(color_code[0]));

	अगर (id < 0)
		वापस;

	id %= 7;
	स_नकल(sc->led_state, color_code[id], माप(color_code[id]));
पूर्ण

अटल व्योम buzz_set_leds(काष्ठा sony_sc *sc)
अणु
	काष्ठा hid_device *hdev = sc->hdev;
	काष्ठा list_head *report_list =
		&hdev->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा hid_report *report = list_entry(report_list->next,
		काष्ठा hid_report, list);
	s32 *value = report->field[0]->value;

	BUILD_BUG_ON(MAX_LEDS < 4);

	value[0] = 0x00;
	value[1] = sc->led_state[0] ? 0xff : 0x00;
	value[2] = sc->led_state[1] ? 0xff : 0x00;
	value[3] = sc->led_state[2] ? 0xff : 0x00;
	value[4] = sc->led_state[3] ? 0xff : 0x00;
	value[5] = 0x00;
	value[6] = 0x00;
	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);
पूर्ण

अटल व्योम sony_set_leds(काष्ठा sony_sc *sc)
अणु
	अगर (!(sc->quirks & BUZZ_CONTROLLER))
		sony_schedule_work(sc, SONY_WORKER_STATE);
	अन्यथा
		buzz_set_leds(sc);
पूर्ण

अटल व्योम sony_led_set_brightness(काष्ठा led_classdev *led,
				    क्रमागत led_brightness value)
अणु
	काष्ठा device *dev = led->dev->parent;
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा sony_sc *drv_data;

	पूर्णांक n;
	पूर्णांक क्रमce_update;

	drv_data = hid_get_drvdata(hdev);
	अगर (!drv_data) अणु
		hid_err(hdev, "No device data\n");
		वापस;
	पूर्ण

	/*
	 * The Sixaxis on USB will override any LED settings sent to it
	 * and keep flashing all of the LEDs until the PS button is pressed.
	 * Updates, even अगर redundant, must be always be sent to the
	 * controller to aव्योम having to toggle the state of an LED just to
	 * stop the flashing later on.
	 */
	क्रमce_update = !!(drv_data->quirks & SIXAXIS_CONTROLLER_USB);

	क्रम (n = 0; n < drv_data->led_count; n++) अणु
		अगर (led == drv_data->leds[n] && (क्रमce_update ||
			(value != drv_data->led_state[n] ||
			drv_data->led_delay_on[n] ||
			drv_data->led_delay_off[n]))) अणु

			drv_data->led_state[n] = value;

			/* Setting the brightness stops the blinking */
			drv_data->led_delay_on[n] = 0;
			drv_data->led_delay_off[n] = 0;

			sony_set_leds(drv_data);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल क्रमागत led_brightness sony_led_get_brightness(काष्ठा led_classdev *led)
अणु
	काष्ठा device *dev = led->dev->parent;
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा sony_sc *drv_data;

	पूर्णांक n;

	drv_data = hid_get_drvdata(hdev);
	अगर (!drv_data) अणु
		hid_err(hdev, "No device data\n");
		वापस LED_OFF;
	पूर्ण

	क्रम (n = 0; n < drv_data->led_count; n++) अणु
		अगर (led == drv_data->leds[n])
			वापस drv_data->led_state[n];
	पूर्ण

	वापस LED_OFF;
पूर्ण

अटल पूर्णांक sony_led_blink_set(काष्ठा led_classdev *led, अचिन्हित दीर्घ *delay_on,
				अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा device *dev = led->dev->parent;
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा sony_sc *drv_data = hid_get_drvdata(hdev);
	पूर्णांक n;
	u8 new_on, new_off;

	अगर (!drv_data) अणु
		hid_err(hdev, "No device data\n");
		वापस -EINVAL;
	पूर्ण

	/* Max delay is 255 deciseconds or 2550 milliseconds */
	अगर (*delay_on > 2550)
		*delay_on = 2550;
	अगर (*delay_off > 2550)
		*delay_off = 2550;

	/* Blink at 1 Hz अगर both values are zero */
	अगर (!*delay_on && !*delay_off)
		*delay_on = *delay_off = 500;

	new_on = *delay_on / 10;
	new_off = *delay_off / 10;

	क्रम (n = 0; n < drv_data->led_count; n++) अणु
		अगर (led == drv_data->leds[n])
			अवरोध;
	पूर्ण

	/* This LED is not रेजिस्टरed on this device */
	अगर (n >= drv_data->led_count)
		वापस -EINVAL;

	/* Don't schedule work if the values didn't change */
	अगर (new_on != drv_data->led_delay_on[n] ||
		new_off != drv_data->led_delay_off[n]) अणु
		drv_data->led_delay_on[n] = new_on;
		drv_data->led_delay_off[n] = new_off;
		sony_schedule_work(drv_data, SONY_WORKER_STATE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sony_leds_init(काष्ठा sony_sc *sc)
अणु
	काष्ठा hid_device *hdev = sc->hdev;
	पूर्णांक n, ret = 0;
	पूर्णांक use_ds4_names;
	काष्ठा led_classdev *led;
	माप_प्रकार name_sz;
	अक्षर *name;
	माप_प्रकार name_len;
	स्थिर अक्षर *name_fmt;
	अटल स्थिर अक्षर * स्थिर ds4_name_str[] = अणु "red", "green", "blue",
						  "global" पूर्ण;
	u8 max_brightness[MAX_LEDS] = अणु [0 ... (MAX_LEDS - 1)] = 1 पूर्ण;
	u8 use_hw_blink[MAX_LEDS] = अणु 0 पूर्ण;

	BUG_ON(!(sc->quirks & SONY_LED_SUPPORT));

	अगर (sc->quirks & BUZZ_CONTROLLER) अणु
		sc->led_count = 4;
		use_ds4_names = 0;
		name_len = म_माप("::buzz#");
		name_fmt = "%s::buzz%d";
		/* Validate expected report अक्षरacteristics. */
		अगर (!hid_validate_values(hdev, HID_OUTPUT_REPORT, 0, 0, 7))
			वापस -ENODEV;
	पूर्ण अन्यथा अगर (sc->quirks & DUALSHOCK4_CONTROLLER) अणु
		dualshock4_set_leds_from_id(sc);
		sc->led_state[3] = 1;
		sc->led_count = 4;
		स_रखो(max_brightness, 255, 3);
		use_hw_blink[3] = 1;
		use_ds4_names = 1;
		name_len = 0;
		name_fmt = "%s:%s";
	पूर्ण अन्यथा अगर (sc->quirks & MOTION_CONTROLLER) अणु
		sc->led_count = 3;
		स_रखो(max_brightness, 255, 3);
		use_ds4_names = 1;
		name_len = 0;
		name_fmt = "%s:%s";
	पूर्ण अन्यथा अगर (sc->quirks & NAVIGATION_CONTROLLER) अणु
		अटल स्थिर u8 navigation_leds[4] = अणु0x01, 0x00, 0x00, 0x00पूर्ण;

		स_नकल(sc->led_state, navigation_leds, माप(navigation_leds));
		sc->led_count = 1;
		स_रखो(use_hw_blink, 1, 4);
		use_ds4_names = 0;
		name_len = म_माप("::sony#");
		name_fmt = "%s::sony%d";
	पूर्ण अन्यथा अणु
		sixaxis_set_leds_from_id(sc);
		sc->led_count = 4;
		स_रखो(use_hw_blink, 1, 4);
		use_ds4_names = 0;
		name_len = म_माप("::sony#");
		name_fmt = "%s::sony%d";
	पूर्ण

	/*
	 * Clear LEDs as we have no way of पढ़ोing their initial state. This is
	 * only relevant अगर the driver is loaded after somebody actively set the
	 * LEDs to on
	 */
	sony_set_leds(sc);

	name_sz = म_माप(dev_name(&hdev->dev)) + name_len + 1;

	क्रम (n = 0; n < sc->led_count; n++) अणु

		अगर (use_ds4_names)
			name_sz = म_माप(dev_name(&hdev->dev)) + म_माप(ds4_name_str[n]) + 2;

		led = devm_kzalloc(&hdev->dev, माप(काष्ठा led_classdev) + name_sz, GFP_KERNEL);
		अगर (!led) अणु
			hid_err(hdev, "Couldn't allocate memory for LED %d\n", n);
			वापस -ENOMEM;
		पूर्ण

		name = (व्योम *)(&led[1]);
		अगर (use_ds4_names)
			snम_लिखो(name, name_sz, name_fmt, dev_name(&hdev->dev),
			ds4_name_str[n]);
		अन्यथा
			snम_लिखो(name, name_sz, name_fmt, dev_name(&hdev->dev), n + 1);
		led->name = name;
		led->brightness = sc->led_state[n];
		led->max_brightness = max_brightness[n];
		led->flags = LED_CORE_SUSPENDRESUME;
		led->brightness_get = sony_led_get_brightness;
		led->brightness_set = sony_led_set_brightness;

		अगर (use_hw_blink[n])
			led->blink_set = sony_led_blink_set;

		sc->leds[n] = led;

		ret = devm_led_classdev_रेजिस्टर(&hdev->dev, led);
		अगर (ret) अणु
			hid_err(hdev, "Failed to register LED %d\n", n);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sixaxis_send_output_report(काष्ठा sony_sc *sc)
अणु
	अटल स्थिर जोड़ sixaxis_output_report_01 शेष_report = अणु
		.buf = अणु
			0x01,
			0x01, 0xff, 0x00, 0xff, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0xff, 0x27, 0x10, 0x00, 0x32,
			0x00, 0x00, 0x00, 0x00, 0x00
		पूर्ण
	पूर्ण;
	काष्ठा sixaxis_output_report *report =
		(काष्ठा sixaxis_output_report *)sc->output_report_dmabuf;
	पूर्णांक n;

	/* Initialize the report with शेष values */
	स_नकल(report, &शेष_report, माप(काष्ठा sixaxis_output_report));

#अगर_घोषित CONFIG_SONY_FF
	report->rumble.right_motor_on = sc->right ? 1 : 0;
	report->rumble.left_motor_क्रमce = sc->left;
#पूर्ण_अगर

	report->leds_biपंचांगap |= sc->led_state[0] << 1;
	report->leds_biपंचांगap |= sc->led_state[1] << 2;
	report->leds_biपंचांगap |= sc->led_state[2] << 3;
	report->leds_biपंचांगap |= sc->led_state[3] << 4;

	/* Set flag क्रम all leds off, required क्रम 3rd party INTEC controller */
	अगर ((report->leds_biपंचांगap & 0x1E) == 0)
		report->leds_biपंचांगap |= 0x20;

	/*
	 * The LEDs in the report are indexed in reverse order to their
	 * corresponding light on the controller.
	 * Index 0 = LED 4, index 1 = LED 3, etc...
	 *
	 * In the हाल of both delay values being zero (blinking disabled) the
	 * शेष report values should be used or the controller LED will be
	 * always off.
	 */
	क्रम (n = 0; n < 4; n++) अणु
		अगर (sc->led_delay_on[n] || sc->led_delay_off[n]) अणु
			report->led[3 - n].duty_off = sc->led_delay_off[n];
			report->led[3 - n].duty_on = sc->led_delay_on[n];
		पूर्ण
	पूर्ण

	/* SHANWAN controllers require output reports via पूर्णांकr channel */
	अगर (sc->quirks & SHANWAN_GAMEPAD)
		hid_hw_output_report(sc->hdev, (u8 *)report,
				माप(काष्ठा sixaxis_output_report));
	अन्यथा
		hid_hw_raw_request(sc->hdev, report->report_id, (u8 *)report,
				माप(काष्ठा sixaxis_output_report),
				HID_OUTPUT_REPORT, HID_REQ_SET_REPORT);
पूर्ण

अटल व्योम dualshock4_send_output_report(काष्ठा sony_sc *sc)
अणु
	काष्ठा hid_device *hdev = sc->hdev;
	u8 *buf = sc->output_report_dmabuf;
	पूर्णांक offset;

	/*
	 * NOTE: The lower 6 bits of buf[1] field of the Bluetooth report
	 * control the पूर्णांकerval at which Dualshock 4 reports data:
	 * 0x00 - 1ms
	 * 0x01 - 1ms
	 * 0x02 - 2ms
	 * 0x3E - 62ms
	 * 0x3F - disabled
	 */
	अगर (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE)) अणु
		स_रखो(buf, 0, DS4_OUTPUT_REPORT_0x05_SIZE);
		buf[0] = 0x05;
		buf[1] = 0x07; /* blink + LEDs + motor */
		offset = 4;
	पूर्ण अन्यथा अणु
		स_रखो(buf, 0, DS4_OUTPUT_REPORT_0x11_SIZE);
		buf[0] = 0x11;
		buf[1] = 0xC0 /* HID + CRC */ | sc->ds4_bt_poll_पूर्णांकerval;
		buf[3] = 0x07; /* blink + LEDs + motor */
		offset = 6;
	पूर्ण

#अगर_घोषित CONFIG_SONY_FF
	buf[offset++] = sc->right;
	buf[offset++] = sc->left;
#अन्यथा
	offset += 2;
#पूर्ण_अगर

	/* LED 3 is the global control */
	अगर (sc->led_state[3]) अणु
		buf[offset++] = sc->led_state[0];
		buf[offset++] = sc->led_state[1];
		buf[offset++] = sc->led_state[2];
	पूर्ण अन्यथा अणु
		offset += 3;
	पूर्ण

	/* If both delay values are zero the DualShock 4 disables blinking. */
	buf[offset++] = sc->led_delay_on[3];
	buf[offset++] = sc->led_delay_off[3];

	अगर (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE))
		hid_hw_output_report(hdev, buf, DS4_OUTPUT_REPORT_0x05_SIZE);
	अन्यथा अणु
		/* CRC generation */
		u8 bthdr = 0xA2;
		u32 crc;

		crc = crc32_le(0xFFFFFFFF, &bthdr, 1);
		crc = ~crc32_le(crc, buf, DS4_OUTPUT_REPORT_0x11_SIZE-4);
		put_unaligned_le32(crc, &buf[74]);
		hid_hw_output_report(hdev, buf, DS4_OUTPUT_REPORT_0x11_SIZE);
	पूर्ण
पूर्ण

अटल व्योम motion_send_output_report(काष्ठा sony_sc *sc)
अणु
	काष्ठा hid_device *hdev = sc->hdev;
	काष्ठा motion_output_report_02 *report =
		(काष्ठा motion_output_report_02 *)sc->output_report_dmabuf;

	स_रखो(report, 0, MOTION_REPORT_0x02_SIZE);

	report->type = 0x02; /* set leds */
	report->r = sc->led_state[0];
	report->g = sc->led_state[1];
	report->b = sc->led_state[2];

#अगर_घोषित CONFIG_SONY_FF
	report->rumble = max(sc->right, sc->left);
#पूर्ण_अगर

	hid_hw_output_report(hdev, (u8 *)report, MOTION_REPORT_0x02_SIZE);
पूर्ण

अटल अंतरभूत व्योम sony_send_output_report(काष्ठा sony_sc *sc)
अणु
	अगर (sc->send_output_report)
		sc->send_output_report(sc);
पूर्ण

अटल व्योम sony_state_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sony_sc *sc = container_of(work, काष्ठा sony_sc, state_worker);

	sc->send_output_report(sc);
पूर्ण

अटल पूर्णांक sony_allocate_output_report(काष्ठा sony_sc *sc)
अणु
	अगर ((sc->quirks & SIXAXIS_CONTROLLER) ||
			(sc->quirks & NAVIGATION_CONTROLLER))
		sc->output_report_dmabuf =
			devm_kदो_स्मृति(&sc->hdev->dev,
				माप(जोड़ sixaxis_output_report_01),
				GFP_KERNEL);
	अन्यथा अगर (sc->quirks & DUALSHOCK4_CONTROLLER_BT)
		sc->output_report_dmabuf = devm_kदो_स्मृति(&sc->hdev->dev,
						DS4_OUTPUT_REPORT_0x11_SIZE,
						GFP_KERNEL);
	अन्यथा अगर (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE))
		sc->output_report_dmabuf = devm_kदो_स्मृति(&sc->hdev->dev,
						DS4_OUTPUT_REPORT_0x05_SIZE,
						GFP_KERNEL);
	अन्यथा अगर (sc->quirks & MOTION_CONTROLLER)
		sc->output_report_dmabuf = devm_kदो_स्मृति(&sc->hdev->dev,
						MOTION_REPORT_0x02_SIZE,
						GFP_KERNEL);
	अन्यथा
		वापस 0;

	अगर (!sc->output_report_dmabuf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SONY_FF
अटल पूर्णांक sony_play_effect(काष्ठा input_dev *dev, व्योम *data,
			    काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा sony_sc *sc = hid_get_drvdata(hid);

	अगर (effect->type != FF_RUMBLE)
		वापस 0;

	sc->left = effect->u.rumble.strong_magnitude / 256;
	sc->right = effect->u.rumble.weak_magnitude / 256;

	sony_schedule_work(sc, SONY_WORKER_STATE);
	वापस 0;
पूर्ण

अटल पूर्णांक sony_init_ff(काष्ठा sony_sc *sc)
अणु
	काष्ठा hid_input *hidinput;
	काष्ठा input_dev *input_dev;

	अगर (list_empty(&sc->hdev->inमाला_दो)) अणु
		hid_err(sc->hdev, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(sc->hdev->inमाला_दो.next, काष्ठा hid_input, list);
	input_dev = hidinput->input;

	input_set_capability(input_dev, EV_FF, FF_RUMBLE);
	वापस input_ff_create_memless(input_dev, शून्य, sony_play_effect);
पूर्ण

#अन्यथा
अटल पूर्णांक sony_init_ff(काष्ठा sony_sc *sc)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक sony_battery_get_property(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property psp,
				     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sony_sc *sc = घातer_supply_get_drvdata(psy);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u8 battery_capacity;
	पूर्णांक battery_status;

	spin_lock_irqsave(&sc->lock, flags);
	battery_capacity = sc->battery_capacity;
	battery_status = sc->battery_status;
	spin_unlock_irqrestore(&sc->lock, flags);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_DEVICE;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = battery_capacity;
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = battery_status;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sony_battery_probe(काष्ठा sony_sc *sc, पूर्णांक append_dev_id)
अणु
	स्थिर अक्षर *battery_str_fmt = append_dev_id ?
		"sony_controller_battery_%pMR_%i" :
		"sony_controller_battery_%pMR";
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = sc, पूर्ण;
	काष्ठा hid_device *hdev = sc->hdev;
	पूर्णांक ret;

	/*
	 * Set the शेष battery level to 100% to aव्योम low battery warnings
	 * अगर the battery is polled beक्रमe the first device report is received.
	 */
	sc->battery_capacity = 100;

	sc->battery_desc.properties = sony_battery_props;
	sc->battery_desc.num_properties = ARRAY_SIZE(sony_battery_props);
	sc->battery_desc.get_property = sony_battery_get_property;
	sc->battery_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	sc->battery_desc.use_क्रम_apm = 0;
	sc->battery_desc.name = devm_kaप्र_लिखो(&hdev->dev, GFP_KERNEL,
					  battery_str_fmt, sc->mac_address, sc->device_id);
	अगर (!sc->battery_desc.name)
		वापस -ENOMEM;

	sc->battery = devm_घातer_supply_रेजिस्टर(&hdev->dev, &sc->battery_desc,
					    &psy_cfg);
	अगर (IS_ERR(sc->battery)) अणु
		ret = PTR_ERR(sc->battery);
		hid_err(hdev, "Unable to register battery device\n");
		वापस ret;
	पूर्ण

	घातer_supply_घातers(sc->battery, &hdev->dev);
	वापस 0;
पूर्ण

/*
 * If a controller is plugged in via USB जबतक alपढ़ोy connected via Bluetooth
 * it will show up as two devices. A global list of connected controllers and
 * their MAC addresses is मुख्यtained to ensure that a device is only connected
 * once.
 *
 * Some USB-only devices masquerade as Sixaxis controllers and all have the
 * same dummy Bluetooth address, so a comparison of the connection type is
 * required.  Devices are only rejected in the हाल where two devices have
 * matching Bluetooth addresses on dअगरferent bus types.
 */
अटल अंतरभूत पूर्णांक sony_compare_connection_type(काष्ठा sony_sc *sc0,
						काष्ठा sony_sc *sc1)
अणु
	स्थिर पूर्णांक sc0_not_bt = !(sc0->quirks & SONY_BT_DEVICE);
	स्थिर पूर्णांक sc1_not_bt = !(sc1->quirks & SONY_BT_DEVICE);

	वापस sc0_not_bt == sc1_not_bt;
पूर्ण

अटल पूर्णांक sony_check_add_dev_list(काष्ठा sony_sc *sc)
अणु
	काष्ठा sony_sc *entry;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&sony_dev_list_lock, flags);

	list_क्रम_each_entry(entry, &sony_device_list, list_node) अणु
		ret = स_भेद(sc->mac_address, entry->mac_address,
				माप(sc->mac_address));
		अगर (!ret) अणु
			अगर (sony_compare_connection_type(sc, entry)) अणु
				ret = 1;
			पूर्ण अन्यथा अणु
				ret = -EEXIST;
				hid_info(sc->hdev,
				"controller with MAC address %pMR already connected\n",
				sc->mac_address);
			पूर्ण
			जाओ unlock;
		पूर्ण
	पूर्ण

	ret = 0;
	list_add(&(sc->list_node), &sony_device_list);

unlock:
	spin_unlock_irqrestore(&sony_dev_list_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम sony_हटाओ_dev_list(काष्ठा sony_sc *sc)
अणु
	अचिन्हित दीर्घ flags;

	अगर (sc->list_node.next) अणु
		spin_lock_irqsave(&sony_dev_list_lock, flags);
		list_del(&(sc->list_node));
		spin_unlock_irqrestore(&sony_dev_list_lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक sony_get_bt_devaddr(काष्ठा sony_sc *sc)
अणु
	पूर्णांक ret;

	/* HIDP stores the device MAC address as a string in the uniq field. */
	ret = म_माप(sc->hdev->uniq);
	अगर (ret != 17)
		वापस -EINVAL;

	ret = माला_पूछो(sc->hdev->uniq,
		"%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		&sc->mac_address[5], &sc->mac_address[4], &sc->mac_address[3],
		&sc->mac_address[2], &sc->mac_address[1], &sc->mac_address[0]);

	अगर (ret != 6)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sony_check_add(काष्ठा sony_sc *sc)
अणु
	u8 *buf = शून्य;
	पूर्णांक n, ret;

	अगर ((sc->quirks & DUALSHOCK4_CONTROLLER_BT) ||
	    (sc->quirks & MOTION_CONTROLLER_BT) ||
	    (sc->quirks & NAVIGATION_CONTROLLER_BT) ||
	    (sc->quirks & SIXAXIS_CONTROLLER_BT)) अणु
		/*
		 * sony_get_bt_devaddr() attempts to parse the Bluetooth MAC
		 * address from the uniq string where HIDP stores it.
		 * As uniq cannot be guaranteed to be a MAC address in all हालs
		 * a failure of this function should not prevent the connection.
		 */
		अगर (sony_get_bt_devaddr(sc) < 0) अणु
			hid_warn(sc->hdev, "UNIQ does not contain a MAC address; duplicate check skipped\n");
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE)) अणु
		buf = kदो_स्मृति(DS4_FEATURE_REPORT_0x81_SIZE, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		/*
		 * The MAC address of a DS4 controller connected via USB can be
		 * retrieved with feature report 0x81. The address begins at
		 * offset 1.
		 */
		ret = hid_hw_raw_request(sc->hdev, 0x81, buf,
				DS4_FEATURE_REPORT_0x81_SIZE, HID_FEATURE_REPORT,
				HID_REQ_GET_REPORT);

		अगर (ret != DS4_FEATURE_REPORT_0x81_SIZE) अणु
			hid_err(sc->hdev, "failed to retrieve feature report 0x81 with the DualShock 4 MAC address\n");
			ret = ret < 0 ? ret : -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		स_नकल(sc->mac_address, &buf[1], माप(sc->mac_address));

		snम_लिखो(sc->hdev->uniq, माप(sc->hdev->uniq),
			 "%pMR", sc->mac_address);
	पूर्ण अन्यथा अगर ((sc->quirks & SIXAXIS_CONTROLLER_USB) ||
			(sc->quirks & NAVIGATION_CONTROLLER_USB)) अणु
		buf = kदो_स्मृति(SIXAXIS_REPORT_0xF2_SIZE, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;

		/*
		 * The MAC address of a Sixaxis controller connected via USB can
		 * be retrieved with feature report 0xf2. The address begins at
		 * offset 4.
		 */
		ret = hid_hw_raw_request(sc->hdev, 0xf2, buf,
				SIXAXIS_REPORT_0xF2_SIZE, HID_FEATURE_REPORT,
				HID_REQ_GET_REPORT);

		अगर (ret != SIXAXIS_REPORT_0xF2_SIZE) अणु
			hid_err(sc->hdev, "failed to retrieve feature report 0xf2 with the Sixaxis MAC address\n");
			ret = ret < 0 ? ret : -EINVAL;
			जाओ out_मुक्त;
		पूर्ण

		/*
		 * The Sixaxis device MAC in the report is big-endian and must
		 * be byte-swapped.
		 */
		क्रम (n = 0; n < 6; n++)
			sc->mac_address[5-n] = buf[4+n];

		snम_लिखो(sc->hdev->uniq, माप(sc->hdev->uniq),
			 "%pMR", sc->mac_address);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	ret = sony_check_add_dev_list(sc);

out_मुक्त:

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक sony_set_device_id(काष्ठा sony_sc *sc)
अणु
	पूर्णांक ret;

	/*
	 * Only DualShock 4 or Sixaxis controllers get an id.
	 * All others are set to -1.
	 */
	अगर ((sc->quirks & SIXAXIS_CONTROLLER) ||
	    (sc->quirks & DUALSHOCK4_CONTROLLER)) अणु
		ret = ida_simple_get(&sony_device_id_allocator, 0, 0,
					GFP_KERNEL);
		अगर (ret < 0) अणु
			sc->device_id = -1;
			वापस ret;
		पूर्ण
		sc->device_id = ret;
	पूर्ण अन्यथा अणु
		sc->device_id = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sony_release_device_id(काष्ठा sony_sc *sc)
अणु
	अगर (sc->device_id >= 0) अणु
		ida_simple_हटाओ(&sony_device_id_allocator, sc->device_id);
		sc->device_id = -1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sony_init_output_report(काष्ठा sony_sc *sc,
				व्योम (*send_output_report)(काष्ठा sony_sc *))
अणु
	sc->send_output_report = send_output_report;

	अगर (!sc->state_worker_initialized)
		INIT_WORK(&sc->state_worker, sony_state_worker);

	sc->state_worker_initialized = 1;
पूर्ण

अटल अंतरभूत व्योम sony_cancel_work_sync(काष्ठा sony_sc *sc)
अणु
	अचिन्हित दीर्घ flags;

	अगर (sc->hotplug_worker_initialized)
		cancel_work_sync(&sc->hotplug_worker);
	अगर (sc->state_worker_initialized) अणु
		spin_lock_irqsave(&sc->lock, flags);
		sc->state_worker_initialized = 0;
		spin_unlock_irqrestore(&sc->lock, flags);
		cancel_work_sync(&sc->state_worker);
	पूर्ण
पूर्ण

अटल पूर्णांक sony_input_configured(काष्ठा hid_device *hdev,
					काष्ठा hid_input *hidinput)
अणु
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);
	पूर्णांक append_dev_id;
	पूर्णांक ret;

	ret = sony_set_device_id(sc);
	अगर (ret < 0) अणु
		hid_err(hdev, "failed to allocate the device id\n");
		जाओ err_stop;
	पूर्ण

	ret = append_dev_id = sony_check_add(sc);
	अगर (ret < 0)
		जाओ err_stop;

	ret = sony_allocate_output_report(sc);
	अगर (ret < 0) अणु
		hid_err(hdev, "failed to allocate the output report buffer\n");
		जाओ err_stop;
	पूर्ण

	अगर (sc->quirks & NAVIGATION_CONTROLLER_USB) अणु
		/*
		 * The Sony Sixaxis करोes not handle HID Output Reports on the
		 * Interrupt EP like it could, so we need to क्रमce HID Output
		 * Reports to use HID_REQ_SET_REPORT on the Control EP.
		 *
		 * There is also another issue about HID Output Reports via USB,
		 * the Sixaxis करोes not want the report_id as part of the data
		 * packet, so we have to discard buf[0] when sending the actual
		 * control message, even क्रम numbered reports, humpf!
		 *
		 * Additionally, the Sixaxis on USB isn't properly initialized
		 * until the PS logo button is pressed and as such won't retain
		 * any state set by an output report, so the initial
		 * configuration report is deferred until the first input
		 * report arrives.
		 */
		hdev->quirks |= HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP;
		hdev->quirks |= HID_QUIRK_SKIP_OUTPUT_REPORT_ID;
		sc->defer_initialization = 1;

		ret = sixaxis_set_operational_usb(hdev);
		अगर (ret < 0) अणु
			hid_err(hdev, "Failed to set controller into operational mode\n");
			जाओ err_stop;
		पूर्ण

		sony_init_output_report(sc, sixaxis_send_output_report);
	पूर्ण अन्यथा अगर (sc->quirks & NAVIGATION_CONTROLLER_BT) अणु
		/*
		 * The Navigation controller wants output reports sent on the ctrl
		 * endpoपूर्णांक when connected via Bluetooth.
		 */
		hdev->quirks |= HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP;

		ret = sixaxis_set_operational_bt(hdev);
		अगर (ret < 0) अणु
			hid_err(hdev, "Failed to set controller into operational mode\n");
			जाओ err_stop;
		पूर्ण

		sony_init_output_report(sc, sixaxis_send_output_report);
	पूर्ण अन्यथा अगर (sc->quirks & SIXAXIS_CONTROLLER_USB) अणु
		/*
		 * The Sony Sixaxis करोes not handle HID Output Reports on the
		 * Interrupt EP and the device only becomes active when the
		 * PS button is pressed. See comment क्रम Navigation controller
		 * above क्रम more details.
		 */
		hdev->quirks |= HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP;
		hdev->quirks |= HID_QUIRK_SKIP_OUTPUT_REPORT_ID;
		sc->defer_initialization = 1;

		ret = sixaxis_set_operational_usb(hdev);
		अगर (ret < 0) अणु
			hid_err(hdev, "Failed to set controller into operational mode\n");
			जाओ err_stop;
		पूर्ण

		ret = sony_रेजिस्टर_sensors(sc);
		अगर (ret) अणु
			hid_err(sc->hdev,
			"Unable to initialize motion sensors: %d\n", ret);
			जाओ err_stop;
		पूर्ण

		sony_init_output_report(sc, sixaxis_send_output_report);
	पूर्ण अन्यथा अगर (sc->quirks & SIXAXIS_CONTROLLER_BT) अणु
		/*
		 * The Sixaxis wants output reports sent on the ctrl endpoपूर्णांक
		 * when connected via Bluetooth.
		 */
		hdev->quirks |= HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP;

		ret = sixaxis_set_operational_bt(hdev);
		अगर (ret < 0) अणु
			hid_err(hdev, "Failed to set controller into operational mode\n");
			जाओ err_stop;
		पूर्ण

		ret = sony_रेजिस्टर_sensors(sc);
		अगर (ret) अणु
			hid_err(sc->hdev,
			"Unable to initialize motion sensors: %d\n", ret);
			जाओ err_stop;
		पूर्ण

		sony_init_output_report(sc, sixaxis_send_output_report);
	पूर्ण अन्यथा अगर (sc->quirks & DUALSHOCK4_CONTROLLER) अणु
		ret = dualshock4_get_calibration_data(sc);
		अगर (ret < 0) अणु
			hid_err(hdev, "Failed to get calibration data from Dualshock 4\n");
			जाओ err_stop;
		पूर्ण

		ret = dualshock4_get_version_info(sc);
		अगर (ret < 0) अणु
			hid_err(sc->hdev, "Failed to get version data from Dualshock 4\n");
			जाओ err_stop;
		पूर्ण

		ret = device_create_file(&sc->hdev->dev, &dev_attr_firmware_version);
		अगर (ret) अणु
			hid_err(sc->hdev, "can't create sysfs firmware_version attribute err: %d\n", ret);
			जाओ err_stop;
		पूर्ण
		sc->fw_version_created = true;

		ret = device_create_file(&sc->hdev->dev, &dev_attr_hardware_version);
		अगर (ret) अणु
			hid_err(sc->hdev, "can't create sysfs hardware_version attribute err: %d\n", ret);
			जाओ err_stop;
		पूर्ण
		sc->hw_version_created = true;

		/*
		 * The Dualshock 4 touchpad supports 2 touches and has a
		 * resolution of 1920x942 (44.86 करोts/mm).
		 */
		ret = sony_रेजिस्टर_touchpad(sc, 2, 1920, 942, 0, 0, 0);
		अगर (ret) अणु
			hid_err(sc->hdev,
			"Unable to initialize multi-touch slots: %d\n",
			ret);
			जाओ err_stop;
		पूर्ण

		ret = sony_रेजिस्टर_sensors(sc);
		अगर (ret) अणु
			hid_err(sc->hdev,
			"Unable to initialize motion sensors: %d\n", ret);
			जाओ err_stop;
		पूर्ण

		अगर (sc->quirks & DUALSHOCK4_CONTROLLER_BT) अणु
			sc->ds4_bt_poll_पूर्णांकerval = DS4_BT_DEFAULT_POLL_INTERVAL_MS;
			ret = device_create_file(&sc->hdev->dev, &dev_attr_bt_poll_पूर्णांकerval);
			अगर (ret)
				hid_warn(sc->hdev,
				 "can't create sysfs bt_poll_interval attribute err: %d\n",
				 ret);
		पूर्ण

		अगर (sc->quirks & DUALSHOCK4_DONGLE) अणु
			INIT_WORK(&sc->hotplug_worker, dualshock4_calibration_work);
			sc->hotplug_worker_initialized = 1;
			sc->ds4_करोngle_state = DONGLE_DISCONNECTED;
		पूर्ण

		sony_init_output_report(sc, dualshock4_send_output_report);
	पूर्ण अन्यथा अगर (sc->quirks & NSG_MRXU_REMOTE) अणु
		/*
		 * The NSG-MRxU touchpad supports 2 touches and has a
		 * resolution of 1667x1868
		 */
		ret = sony_रेजिस्टर_touchpad(sc, 2,
			NSG_MRXU_MAX_X, NSG_MRXU_MAX_Y, 15, 15, 1);
		अगर (ret) अणु
			hid_err(sc->hdev,
			"Unable to initialize multi-touch slots: %d\n",
			ret);
			जाओ err_stop;
		पूर्ण

	पूर्ण अन्यथा अगर (sc->quirks & MOTION_CONTROLLER) अणु
		sony_init_output_report(sc, motion_send_output_report);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	अगर (sc->quirks & SONY_LED_SUPPORT) अणु
		ret = sony_leds_init(sc);
		अगर (ret < 0)
			जाओ err_stop;
	पूर्ण

	अगर (sc->quirks & SONY_BATTERY_SUPPORT) अणु
		ret = sony_battery_probe(sc, append_dev_id);
		अगर (ret < 0)
			जाओ err_stop;

		/* Open the device to receive reports with battery info */
		ret = hid_hw_खोलो(hdev);
		अगर (ret < 0) अणु
			hid_err(hdev, "hw open failed\n");
			जाओ err_stop;
		पूर्ण
	पूर्ण

	अगर (sc->quirks & SONY_FF_SUPPORT) अणु
		ret = sony_init_ff(sc);
		अगर (ret < 0)
			जाओ err_बंद;
	पूर्ण

	वापस 0;
err_बंद:
	hid_hw_बंद(hdev);
err_stop:
	/* Piggy back on the शेष ds4_bt_ poll_पूर्णांकerval to determine
	 * अगर we need to हटाओ the file as we करोn't know क्रम sure अगर we
	 * executed that logic.
	 */
	अगर (sc->ds4_bt_poll_पूर्णांकerval)
		device_हटाओ_file(&sc->hdev->dev, &dev_attr_bt_poll_पूर्णांकerval);
	अगर (sc->fw_version_created)
		device_हटाओ_file(&sc->hdev->dev, &dev_attr_firmware_version);
	अगर (sc->hw_version_created)
		device_हटाओ_file(&sc->hdev->dev, &dev_attr_hardware_version);
	sony_cancel_work_sync(sc);
	sony_हटाओ_dev_list(sc);
	sony_release_device_id(sc);
	वापस ret;
पूर्ण

अटल पूर्णांक sony_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ quirks = id->driver_data;
	काष्ठा sony_sc *sc;
	अचिन्हित पूर्णांक connect_mask = HID_CONNECT_DEFAULT;

	अगर (!म_भेद(hdev->name, "FutureMax Dance Mat"))
		quirks |= FUTUREMAX_DANCE_MAT;

	अगर (!म_भेद(hdev->name, "SHANWAN PS3 GamePad"))
		quirks |= SHANWAN_GAMEPAD;

	sc = devm_kzalloc(&hdev->dev, माप(*sc), GFP_KERNEL);
	अगर (sc == शून्य) अणु
		hid_err(hdev, "can't alloc sony descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&sc->lock);

	sc->quirks = quirks;
	hid_set_drvdata(hdev, sc);
	sc->hdev = hdev;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण

	अगर (sc->quirks & VAIO_RDESC_CONSTANT)
		connect_mask |= HID_CONNECT_HIDDEV_FORCE;
	अन्यथा अगर (sc->quirks & SIXAXIS_CONTROLLER)
		connect_mask |= HID_CONNECT_HIDDEV_FORCE;

	/* Patch the hw version on DS3/4 compatible devices, so applications can
	 * distinguish between the शेष HID mappings and the mappings defined
	 * by the Linux game controller spec. This is important क्रम the SDL2
	 * library, which has a game controller database, which uses device ids
	 * in combination with version as a key.
	 */
	अगर (sc->quirks & (SIXAXIS_CONTROLLER | DUALSHOCK4_CONTROLLER))
		hdev->version |= 0x8000;

	ret = hid_hw_start(hdev, connect_mask);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	/* sony_input_configured can fail, but this करोesn't result
	 * in hid_hw_start failures (पूर्णांकended). Check whether
	 * the HID layer claimed the device अन्यथा fail.
	 * We करोn't know the actual reason क्रम the failure, most
	 * likely it is due to EEXIST in हाल of द्विगुन connection
	 * of USB and Bluetooth, but could have been due to ENOMEM
	 * or other reasons as well.
	 */
	अगर (!(hdev->claimed & HID_CLAIMED_INPUT)) अणु
		hid_err(hdev, "failed to claim input\n");
		hid_hw_stop(hdev);
		वापस -ENODEV;
	पूर्ण

	अगर (sc->quirks & GHL_GUITAR_PS3WIIU) अणु
		समयr_setup(&sc->ghl_poke_समयr, ghl_magic_poke, 0);
		mod_समयr(&sc->ghl_poke_समयr,
			  jअगरfies + GHL_GUITAR_POKE_INTERVAL*HZ);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sony_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);

	अगर (sc->quirks & GHL_GUITAR_PS3WIIU)
		del_समयr_sync(&sc->ghl_poke_समयr);

	hid_hw_बंद(hdev);

	अगर (sc->quirks & DUALSHOCK4_CONTROLLER_BT)
		device_हटाओ_file(&sc->hdev->dev, &dev_attr_bt_poll_पूर्णांकerval);

	अगर (sc->fw_version_created)
		device_हटाओ_file(&sc->hdev->dev, &dev_attr_firmware_version);

	अगर (sc->hw_version_created)
		device_हटाओ_file(&sc->hdev->dev, &dev_attr_hardware_version);

	sony_cancel_work_sync(sc);

	sony_हटाओ_dev_list(sc);

	sony_release_device_id(sc);

	hid_hw_stop(hdev);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक sony_suspend(काष्ठा hid_device *hdev, pm_message_t message)
अणु
#अगर_घोषित CONFIG_SONY_FF

	/* On suspend stop any running क्रमce-feedback events */
	अगर (SONY_FF_SUPPORT) अणु
		काष्ठा sony_sc *sc = hid_get_drvdata(hdev);

		sc->left = sc->right = 0;
		sony_send_output_report(sc);
	पूर्ण

#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक sony_resume(काष्ठा hid_device *hdev)
अणु
	काष्ठा sony_sc *sc = hid_get_drvdata(hdev);

	/*
	 * The Sixaxis and navigation controllers on USB need to be
	 * reinitialized on resume or they won't behave properly.
	 */
	अगर ((sc->quirks & SIXAXIS_CONTROLLER_USB) ||
		(sc->quirks & NAVIGATION_CONTROLLER_USB)) अणु
		sixaxis_set_operational_usb(sc->hdev);
		sc->defer_initialization = 1;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा hid_device_id sony_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS3_CONTROLLER),
		.driver_data = SIXAXIS_CONTROLLER_USB पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_NAVIGATION_CONTROLLER),
		.driver_data = NAVIGATION_CONTROLLER_USB पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_NAVIGATION_CONTROLLER),
		.driver_data = NAVIGATION_CONTROLLER_BT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_MOTION_CONTROLLER),
		.driver_data = MOTION_CONTROLLER_USB पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_MOTION_CONTROLLER),
		.driver_data = MOTION_CONTROLLER_BT पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS3_CONTROLLER),
		.driver_data = SIXAXIS_CONTROLLER_BT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_VAIO_VGX_MOUSE),
		.driver_data = VAIO_RDESC_CONSTANT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_VAIO_VGP_MOUSE),
		.driver_data = VAIO_RDESC_CONSTANT पूर्ण,
	/*
	 * Wired Buzz Controller. Reported as Sony Hub from its USB ID and as
	 * Logitech joystick from the device descriptor.
	 */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_BUZZ_CONTROLLER),
		.driver_data = BUZZ_CONTROLLER पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_WIRELESS_BUZZ_CONTROLLER),
		.driver_data = BUZZ_CONTROLLER पूर्ण,
	/* PS3 BD Remote Control */
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS3_BDREMOTE),
		.driver_data = PS3REMOTE पूर्ण,
	/* Logitech Harmony Adapter क्रम PS3 */
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_HARMONY_PS3),
		.driver_data = PS3REMOTE पूर्ण,
	/* SMK-Link PS3 BD Remote Control */
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SMK, USB_DEVICE_ID_SMK_PS3_BDREMOTE),
		.driver_data = PS3REMOTE पूर्ण,
	/* Sony Dualshock 4 controllers क्रम PS4 */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER),
		.driver_data = DUALSHOCK4_CONTROLLER_USB पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER),
		.driver_data = DUALSHOCK4_CONTROLLER_BT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER_2),
		.driver_data = DUALSHOCK4_CONTROLLER_USB पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER_2),
		.driver_data = DUALSHOCK4_CONTROLLER_BT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTROLLER_DONGLE),
		.driver_data = DUALSHOCK4_DONGLE पूर्ण,
	/* Nyko Core Controller क्रम PS3 */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SINO_LITE, USB_DEVICE_ID_SINO_LITE_CONTROLLER),
		.driver_data = SIXAXIS_CONTROLLER_USB | SINO_LITE_CONTROLLER पूर्ण,
	/* SMK-Link NSG-MR5U Remote Control */
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SMK, USB_DEVICE_ID_SMK_NSG_MR5U_REMOTE),
		.driver_data = NSG_MR5U_REMOTE_BT पूर्ण,
	/* SMK-Link NSG-MR7U Remote Control */
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SMK, USB_DEVICE_ID_SMK_NSG_MR7U_REMOTE),
		.driver_data = NSG_MR7U_REMOTE_BT पूर्ण,
	/* Guitar Hero Live PS3 and Wii U guitar करोngles */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY_RHYTHM, USB_DEVICE_ID_SONY_PS3WIIU_GHLIVE_DONGLE),
		.driver_data = GHL_GUITAR_PS3WIIU | GH_GUITAR_CONTROLLER पूर्ण,
	/* Guitar Hero PC Guitar Dongle */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ACTIVISION, USB_DEVICE_ID_ACTIVISION_GUITAR_DONGLE),
		.driver_data = GH_GUITAR_CONTROLLER पूर्ण,
	/* Guitar Hero PS3 World Tour Guitar Dongle */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY_RHYTHM, USB_DEVICE_ID_SONY_PS3_GUITAR_DONGLE),
		.driver_data = GH_GUITAR_CONTROLLER पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, sony_devices);

अटल काष्ठा hid_driver sony_driver = अणु
	.name             = "sony",
	.id_table         = sony_devices,
	.input_mapping    = sony_mapping,
	.input_configured = sony_input_configured,
	.probe            = sony_probe,
	.हटाओ           = sony_हटाओ,
	.report_fixup     = sony_report_fixup,
	.raw_event        = sony_raw_event,

#अगर_घोषित CONFIG_PM
	.suspend          = sony_suspend,
	.resume	          = sony_resume,
	.reset_resume     = sony_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init sony_init(व्योम)
अणु
	dbg_hid("Sony:%s\n", __func__);

	वापस hid_रेजिस्टर_driver(&sony_driver);
पूर्ण

अटल व्योम __निकास sony_निकास(व्योम)
अणु
	dbg_hid("Sony:%s\n", __func__);

	hid_unरेजिस्टर_driver(&sony_driver);
	ida_destroy(&sony_device_id_allocator);
पूर्ण
module_init(sony_init);
module_निकास(sony_निकास);

MODULE_LICENSE("GPL");
