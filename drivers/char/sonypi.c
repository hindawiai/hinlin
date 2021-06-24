<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Sony Programmable I/O Control Device driver क्रम VAIO
 *
 * Copyright (C) 2007 Mattia Dongili <malattia@linux.it>
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

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/input.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/poll.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/err.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gfp.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/sonypi.h>

#घोषणा SONYPI_DRIVER_VERSION	 "1.26"

MODULE_AUTHOR("Stelian Pop <stelian@popies.net>");
MODULE_DESCRIPTION("Sony Programmable I/O Control Device driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(SONYPI_DRIVER_VERSION);

अटल पूर्णांक minor = -1;
module_param(minor, पूर्णांक, 0);
MODULE_PARM_DESC(minor,
		 "minor number of the misc device, default is -1 (automatic)");

अटल पूर्णांक verbose;		/* = 0 */
module_param(verbose, पूर्णांक, 0644);
MODULE_PARM_DESC(verbose, "be verbose, default is 0 (no)");

अटल पूर्णांक fnkeyinit;		/* = 0 */
module_param(fnkeyinit, पूर्णांक, 0444);
MODULE_PARM_DESC(fnkeyinit,
		 "set this if your Fn keys do not generate any event");

अटल पूर्णांक camera;		/* = 0 */
module_param(camera, पूर्णांक, 0444);
MODULE_PARM_DESC(camera,
		 "set this if you have a MotionEye camera (PictureBook series)");

अटल पूर्णांक compat;		/* = 0 */
module_param(compat, पूर्णांक, 0444);
MODULE_PARM_DESC(compat,
		 "set this if you want to enable backward compatibility mode");

अटल अचिन्हित दीर्घ mask = 0xffffffff;
module_param(mask, uदीर्घ, 0644);
MODULE_PARM_DESC(mask,
		 "set this to the mask of event you want to enable (see doc)");

अटल पूर्णांक useinput = 1;
module_param(useinput, पूर्णांक, 0444);
MODULE_PARM_DESC(useinput,
		 "set this if you would like sonypi to feed events to the input subsystem");

अटल पूर्णांक check_ioport = 1;
module_param(check_ioport, पूर्णांक, 0444);
MODULE_PARM_DESC(check_ioport,
		 "set this to 0 if you think the automatic ioport check for sony-laptop is wrong");

#घोषणा SONYPI_DEVICE_MODEL_TYPE1	1
#घोषणा SONYPI_DEVICE_MODEL_TYPE2	2
#घोषणा SONYPI_DEVICE_MODEL_TYPE3	3

/* type1 models use those */
#घोषणा SONYPI_IRQ_PORT			0x8034
#घोषणा SONYPI_IRQ_SHIFT		22
#घोषणा SONYPI_TYPE1_BASE		0x50
#घोषणा SONYPI_G10A			(SONYPI_TYPE1_BASE+0x14)
#घोषणा SONYPI_TYPE1_REGION_SIZE	0x08
#घोषणा SONYPI_TYPE1_EVTYPE_OFFSET	0x04

/* type2 series specअगरics */
#घोषणा SONYPI_SIRQ			0x9b
#घोषणा SONYPI_SLOB			0x9c
#घोषणा SONYPI_SHIB			0x9d
#घोषणा SONYPI_TYPE2_REGION_SIZE	0x20
#घोषणा SONYPI_TYPE2_EVTYPE_OFFSET	0x12

/* type3 series specअगरics */
#घोषणा SONYPI_TYPE3_BASE		0x40
#घोषणा SONYPI_TYPE3_GID2		(SONYPI_TYPE3_BASE+0x48) /* 16 bits */
#घोषणा SONYPI_TYPE3_MISC		(SONYPI_TYPE3_BASE+0x6d) /* 8 bits  */
#घोषणा SONYPI_TYPE3_REGION_SIZE	0x20
#घोषणा SONYPI_TYPE3_EVTYPE_OFFSET	0x12

/* battery / brightness addresses */
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

/* FAN0 inक्रमmation (reverse engineered from ACPI tables) */
#घोषणा SONYPI_FAN0_STATUS	0x93
#घोषणा SONYPI_TEMP_STATUS	0xC1

/* ioports used क्रम brightness and type2 events */
#घोषणा SONYPI_DATA_IOPORT	0x62
#घोषणा SONYPI_CST_IOPORT	0x66

/* The set of possible ioports */
काष्ठा sonypi_ioport_list अणु
	u16	port1;
	u16	port2;
पूर्ण;

अटल काष्ठा sonypi_ioport_list sonypi_type1_ioport_list[] = अणु
	अणु 0x10c0, 0x10c4 पूर्ण,	/* looks like the शेष on C1Vx */
	अणु 0x1080, 0x1084 पूर्ण,
	अणु 0x1090, 0x1094 पूर्ण,
	अणु 0x10a0, 0x10a4 पूर्ण,
	अणु 0x10b0, 0x10b4 पूर्ण,
	अणु 0x0, 0x0 पूर्ण
पूर्ण;

अटल काष्ठा sonypi_ioport_list sonypi_type2_ioport_list[] = अणु
	अणु 0x1080, 0x1084 पूर्ण,
	अणु 0x10a0, 0x10a4 पूर्ण,
	अणु 0x10c0, 0x10c4 पूर्ण,
	अणु 0x10e0, 0x10e4 पूर्ण,
	अणु 0x0, 0x0 पूर्ण
पूर्ण;

/* same as in type 2 models */
अटल काष्ठा sonypi_ioport_list *sonypi_type3_ioport_list =
	sonypi_type2_ioport_list;

/* The set of possible पूर्णांकerrupts */
काष्ठा sonypi_irq_list अणु
	u16	irq;
	u16	bits;
पूर्ण;

अटल काष्ठा sonypi_irq_list sonypi_type1_irq_list[] = अणु
	अणु 11, 0x2 पूर्ण,	/* IRQ 11, GO22=0,GO23=1 in AML */
	अणु 10, 0x1 पूर्ण,	/* IRQ 10, GO22=1,GO23=0 in AML */
	अणु  5, 0x0 पूर्ण,	/* IRQ  5, GO22=0,GO23=0 in AML */
	अणु  0, 0x3 पूर्ण	/* no IRQ, GO22=1,GO23=1 in AML */
पूर्ण;

अटल काष्ठा sonypi_irq_list sonypi_type2_irq_list[] = अणु
	अणु 11, 0x80 पूर्ण,	/* IRQ 11, 0x80 in SIRQ in AML */
	अणु 10, 0x40 पूर्ण,	/* IRQ 10, 0x40 in SIRQ in AML */
	अणु  9, 0x20 पूर्ण,	/* IRQ  9, 0x20 in SIRQ in AML */
	अणु  6, 0x10 पूर्ण,	/* IRQ  6, 0x10 in SIRQ in AML */
	अणु  0, 0x00 पूर्ण	/* no IRQ, 0x00 in SIRQ in AML */
पूर्ण;

/* same as in type2 models */
अटल काष्ठा sonypi_irq_list *sonypi_type3_irq_list = sonypi_type2_irq_list;

#घोषणा SONYPI_CAMERA_BRIGHTNESS		0
#घोषणा SONYPI_CAMERA_CONTRAST			1
#घोषणा SONYPI_CAMERA_HUE			2
#घोषणा SONYPI_CAMERA_COLOR			3
#घोषणा SONYPI_CAMERA_SHARPNESS			4

#घोषणा SONYPI_CAMERA_PICTURE			5
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
	अणु 0x5c, SONYPI_EVENT_PKEY_P1 पूर्ण,
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
	अणु 0x59, SONYPI_EVENT_WIRELESS_ON पूर्ण,
	अणु 0x5a, SONYPI_EVENT_WIRELESS_OFF पूर्ण,
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

अटल काष्ठा sonypi_eventtypes अणु
	पूर्णांक			model;
	u8			data;
	अचिन्हित दीर्घ		mask;
	काष्ठा sonypi_event *	events;
पूर्ण sonypi_eventtypes[] = अणु
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0, 0xffffffff, sonypi_releaseev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0x70, SONYPI_MEYE_MASK, sonypi_meyeev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0x30, SONYPI_LID_MASK, sonypi_lidev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0x60, SONYPI_CAPTURE_MASK, sonypi_captureev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0x10, SONYPI_JOGGER_MASK, sonypi_joggerev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0x20, SONYPI_FNKEY_MASK, sonypi_fnkeyev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0x30, SONYPI_BLUETOOTH_MASK, sonypi_blueev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0x40, SONYPI_PKEY_MASK, sonypi_pkeyev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0x30, SONYPI_MEMORYSTICK_MASK, sonypi_memorystickev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE1, 0x40, SONYPI_BATTERY_MASK, sonypi_batteryev पूर्ण,

	अणु SONYPI_DEVICE_MODEL_TYPE2, 0, 0xffffffff, sonypi_releaseev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x38, SONYPI_LID_MASK, sonypi_lidev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x11, SONYPI_JOGGER_MASK, sonypi_joggerev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x61, SONYPI_CAPTURE_MASK, sonypi_captureev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x21, SONYPI_FNKEY_MASK, sonypi_fnkeyev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x31, SONYPI_BLUETOOTH_MASK, sonypi_blueev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x08, SONYPI_PKEY_MASK, sonypi_pkeyev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x11, SONYPI_BACK_MASK, sonypi_backev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x21, SONYPI_HELP_MASK, sonypi_helpev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x21, SONYPI_ZOOM_MASK, sonypi_zoomev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x20, SONYPI_THUMBPHRASE_MASK, sonypi_thumbphraseev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x31, SONYPI_MEMORYSTICK_MASK, sonypi_memorystickev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x41, SONYPI_BATTERY_MASK, sonypi_batteryev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE2, 0x31, SONYPI_PKEY_MASK, sonypi_pkeyev पूर्ण,

	अणु SONYPI_DEVICE_MODEL_TYPE3, 0, 0xffffffff, sonypi_releaseev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE3, 0x21, SONYPI_FNKEY_MASK, sonypi_fnkeyev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE3, 0x31, SONYPI_WIRELESS_MASK, sonypi_wlessev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE3, 0x31, SONYPI_MEMORYSTICK_MASK, sonypi_memorystickev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE3, 0x41, SONYPI_BATTERY_MASK, sonypi_batteryev पूर्ण,
	अणु SONYPI_DEVICE_MODEL_TYPE3, 0x31, SONYPI_PKEY_MASK, sonypi_pkeyev पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

#घोषणा SONYPI_BUF_SIZE	128

/* Correspondance table between sonypi events and input layer events */
अटल काष्ठा अणु
	पूर्णांक sonypiev;
	पूर्णांक inputev;
पूर्ण sonypi_inputkeys[] = अणु
	अणु SONYPI_EVENT_CAPTURE_PRESSED,	 	KEY_CAMERA पूर्ण,
	अणु SONYPI_EVENT_FNKEY_ONLY, 		KEY_FN पूर्ण,
	अणु SONYPI_EVENT_FNKEY_ESC, 		KEY_FN_ESC पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F1, 		KEY_FN_F1 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F2, 		KEY_FN_F2 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F3, 		KEY_FN_F3 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F4, 		KEY_FN_F4 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F5, 		KEY_FN_F5 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F6, 		KEY_FN_F6 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F7, 		KEY_FN_F7 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F8, 		KEY_FN_F8 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F9,		KEY_FN_F9 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F10,		KEY_FN_F10 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F11, 		KEY_FN_F11 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F12,		KEY_FN_F12 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_1, 		KEY_FN_1 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_2, 		KEY_FN_2 पूर्ण,
	अणु SONYPI_EVENT_FNKEY_D,			KEY_FN_D पूर्ण,
	अणु SONYPI_EVENT_FNKEY_E,			KEY_FN_E पूर्ण,
	अणु SONYPI_EVENT_FNKEY_F,			KEY_FN_F पूर्ण,
	अणु SONYPI_EVENT_FNKEY_S,			KEY_FN_S पूर्ण,
	अणु SONYPI_EVENT_FNKEY_B,			KEY_FN_B पूर्ण,
	अणु SONYPI_EVENT_BLUETOOTH_PRESSED, 	KEY_BLUE पूर्ण,
	अणु SONYPI_EVENT_BLUETOOTH_ON, 		KEY_BLUE पूर्ण,
	अणु SONYPI_EVENT_PKEY_P1, 		KEY_PROG1 पूर्ण,
	अणु SONYPI_EVENT_PKEY_P2, 		KEY_PROG2 पूर्ण,
	अणु SONYPI_EVENT_PKEY_P3, 		KEY_PROG3 पूर्ण,
	अणु SONYPI_EVENT_BACK_PRESSED, 		KEY_BACK पूर्ण,
	अणु SONYPI_EVENT_HELP_PRESSED, 		KEY_HELP पूर्ण,
	अणु SONYPI_EVENT_ZOOM_PRESSED, 		KEY_ZOOM पूर्ण,
	अणु SONYPI_EVENT_THUMBPHRASE_PRESSED, 	BTN_THUMB पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

काष्ठा sonypi_keypress अणु
	काष्ठा input_dev *dev;
	पूर्णांक key;
पूर्ण;

अटल काष्ठा sonypi_device अणु
	काष्ठा pci_dev *dev;
	u16 irq;
	u16 bits;
	u16 ioport1;
	u16 ioport2;
	u16 region_size;
	u16 evtype_offset;
	पूर्णांक camera_घातer;
	पूर्णांक bluetooth_घातer;
	काष्ठा mutex lock;
	काष्ठा kfअगरo fअगरo;
	spinlock_t fअगरo_lock;
	रुको_queue_head_t fअगरo_proc_list;
	काष्ठा fasync_काष्ठा *fअगरo_async;
	पूर्णांक खोलो_count;
	पूर्णांक model;
	काष्ठा input_dev *input_jog_dev;
	काष्ठा input_dev *input_key_dev;
	काष्ठा work_काष्ठा input_work;
	काष्ठा kfअगरo input_fअगरo;
	spinlock_t input_fअगरo_lock;
पूर्ण sonypi_device;

#घोषणा ITERATIONS_LONG		10000
#घोषणा ITERATIONS_SHORT	10

#घोषणा रुको_on_command(quiet, command, iterations) अणु \
	अचिन्हित पूर्णांक n = iterations; \
	जबतक (--n && (command)) \
		udelay(1); \
	अगर (!n && (verbose || !quiet)) \
		prपूर्णांकk(KERN_WARNING "sonypi command failed at %s : %s (line %d)\n", __खाता__, __func__, __LINE__); \
पूर्ण

#अगर_घोषित CONFIG_ACPI
#घोषणा SONYPI_ACPI_ACTIVE (!acpi_disabled)
#अन्यथा
#घोषणा SONYPI_ACPI_ACTIVE 0
#पूर्ण_अगर				/* CONFIG_ACPI */

#अगर_घोषित CONFIG_ACPI
अटल काष्ठा acpi_device *sonypi_acpi_device;
अटल पूर्णांक acpi_driver_रेजिस्टरed;
#पूर्ण_अगर

अटल पूर्णांक sonypi_ec_ग_लिखो(u8 addr, u8 value)
अणु
#अगर_घोषित CONFIG_ACPI
	अगर (SONYPI_ACPI_ACTIVE)
		वापस ec_ग_लिखो(addr, value);
#पूर्ण_अगर
	रुको_on_command(1, inb_p(SONYPI_CST_IOPORT) & 3, ITERATIONS_LONG);
	outb_p(0x81, SONYPI_CST_IOPORT);
	रुको_on_command(0, inb_p(SONYPI_CST_IOPORT) & 2, ITERATIONS_LONG);
	outb_p(addr, SONYPI_DATA_IOPORT);
	रुको_on_command(0, inb_p(SONYPI_CST_IOPORT) & 2, ITERATIONS_LONG);
	outb_p(value, SONYPI_DATA_IOPORT);
	रुको_on_command(0, inb_p(SONYPI_CST_IOPORT) & 2, ITERATIONS_LONG);
	वापस 0;
पूर्ण

अटल पूर्णांक sonypi_ec_पढ़ो(u8 addr, u8 *value)
अणु
#अगर_घोषित CONFIG_ACPI
	अगर (SONYPI_ACPI_ACTIVE)
		वापस ec_पढ़ो(addr, value);
#पूर्ण_अगर
	रुको_on_command(1, inb_p(SONYPI_CST_IOPORT) & 3, ITERATIONS_LONG);
	outb_p(0x80, SONYPI_CST_IOPORT);
	रुको_on_command(0, inb_p(SONYPI_CST_IOPORT) & 2, ITERATIONS_LONG);
	outb_p(addr, SONYPI_DATA_IOPORT);
	रुको_on_command(0, inb_p(SONYPI_CST_IOPORT) & 2, ITERATIONS_LONG);
	*value = inb_p(SONYPI_DATA_IOPORT);
	वापस 0;
पूर्ण

अटल पूर्णांक ec_पढ़ो16(u8 addr, u16 *value)
अणु
	u8 val_lb, val_hb;
	अगर (sonypi_ec_पढ़ो(addr, &val_lb))
		वापस -1;
	अगर (sonypi_ec_पढ़ो(addr + 1, &val_hb))
		वापस -1;
	*value = val_lb | (val_hb << 8);
	वापस 0;
पूर्ण

/* Initializes the device - this comes from the AML code in the ACPI bios */
अटल व्योम sonypi_type1_srs(व्योम)
अणु
	u32 v;

	pci_पढ़ो_config_dword(sonypi_device.dev, SONYPI_G10A, &v);
	v = (v & 0xFFFF0000) | ((u32) sonypi_device.ioport1);
	pci_ग_लिखो_config_dword(sonypi_device.dev, SONYPI_G10A, v);

	pci_पढ़ो_config_dword(sonypi_device.dev, SONYPI_G10A, &v);
	v = (v & 0xFFF0FFFF) |
	    (((u32) sonypi_device.ioport1 ^ sonypi_device.ioport2) << 16);
	pci_ग_लिखो_config_dword(sonypi_device.dev, SONYPI_G10A, v);

	v = inl(SONYPI_IRQ_PORT);
	v &= ~(((u32) 0x3) << SONYPI_IRQ_SHIFT);
	v |= (((u32) sonypi_device.bits) << SONYPI_IRQ_SHIFT);
	outl(v, SONYPI_IRQ_PORT);

	pci_पढ़ो_config_dword(sonypi_device.dev, SONYPI_G10A, &v);
	v = (v & 0xFF1FFFFF) | 0x00C00000;
	pci_ग_लिखो_config_dword(sonypi_device.dev, SONYPI_G10A, v);
पूर्ण

अटल व्योम sonypi_type2_srs(व्योम)
अणु
	अगर (sonypi_ec_ग_लिखो(SONYPI_SHIB, (sonypi_device.ioport1 & 0xFF00) >> 8))
		prपूर्णांकk(KERN_WARNING "ec_write failed\n");
	अगर (sonypi_ec_ग_लिखो(SONYPI_SLOB, sonypi_device.ioport1 & 0x00FF))
		prपूर्णांकk(KERN_WARNING "ec_write failed\n");
	अगर (sonypi_ec_ग_लिखो(SONYPI_SIRQ, sonypi_device.bits))
		prपूर्णांकk(KERN_WARNING "ec_write failed\n");
	udelay(10);
पूर्ण

अटल व्योम sonypi_type3_srs(व्योम)
अणु
	u16 v16;
	u8  v8;

	/* This model type uses the same initialization of
	 * the embedded controller as the type2 models. */
	sonypi_type2_srs();

	/* Initialization of PCI config space of the LPC पूर्णांकerface bridge. */
	v16 = (sonypi_device.ioport1 & 0xFFF0) | 0x01;
	pci_ग_लिखो_config_word(sonypi_device.dev, SONYPI_TYPE3_GID2, v16);
	pci_पढ़ो_config_byte(sonypi_device.dev, SONYPI_TYPE3_MISC, &v8);
	v8 = (v8 & 0xCF) | 0x10;
	pci_ग_लिखो_config_byte(sonypi_device.dev, SONYPI_TYPE3_MISC, v8);
पूर्ण

/* Disables the device - this comes from the AML code in the ACPI bios */
अटल व्योम sonypi_type1_dis(व्योम)
अणु
	u32 v;

	pci_पढ़ो_config_dword(sonypi_device.dev, SONYPI_G10A, &v);
	v = v & 0xFF3FFFFF;
	pci_ग_लिखो_config_dword(sonypi_device.dev, SONYPI_G10A, v);

	v = inl(SONYPI_IRQ_PORT);
	v |= (0x3 << SONYPI_IRQ_SHIFT);
	outl(v, SONYPI_IRQ_PORT);
पूर्ण

अटल व्योम sonypi_type2_dis(व्योम)
अणु
	अगर (sonypi_ec_ग_लिखो(SONYPI_SHIB, 0))
		prपूर्णांकk(KERN_WARNING "ec_write failed\n");
	अगर (sonypi_ec_ग_लिखो(SONYPI_SLOB, 0))
		prपूर्णांकk(KERN_WARNING "ec_write failed\n");
	अगर (sonypi_ec_ग_लिखो(SONYPI_SIRQ, 0))
		prपूर्णांकk(KERN_WARNING "ec_write failed\n");
पूर्ण

अटल व्योम sonypi_type3_dis(व्योम)
अणु
	sonypi_type2_dis();
	udelay(10);
	pci_ग_लिखो_config_word(sonypi_device.dev, SONYPI_TYPE3_GID2, 0);
पूर्ण

अटल u8 sonypi_call1(u8 dev)
अणु
	u8 v1, v2;

	रुको_on_command(0, inb_p(sonypi_device.ioport2) & 2, ITERATIONS_LONG);
	outb(dev, sonypi_device.ioport2);
	v1 = inb_p(sonypi_device.ioport2);
	v2 = inb_p(sonypi_device.ioport1);
	वापस v2;
पूर्ण

अटल u8 sonypi_call2(u8 dev, u8 fn)
अणु
	u8 v1;

	रुको_on_command(0, inb_p(sonypi_device.ioport2) & 2, ITERATIONS_LONG);
	outb(dev, sonypi_device.ioport2);
	रुको_on_command(0, inb_p(sonypi_device.ioport2) & 2, ITERATIONS_LONG);
	outb(fn, sonypi_device.ioport1);
	v1 = inb_p(sonypi_device.ioport1);
	वापस v1;
पूर्ण

अटल u8 sonypi_call3(u8 dev, u8 fn, u8 v)
अणु
	u8 v1;

	रुको_on_command(0, inb_p(sonypi_device.ioport2) & 2, ITERATIONS_LONG);
	outb(dev, sonypi_device.ioport2);
	रुको_on_command(0, inb_p(sonypi_device.ioport2) & 2, ITERATIONS_LONG);
	outb(fn, sonypi_device.ioport1);
	रुको_on_command(0, inb_p(sonypi_device.ioport2) & 2, ITERATIONS_LONG);
	outb(v, sonypi_device.ioport1);
	v1 = inb_p(sonypi_device.ioport1);
	वापस v1;
पूर्ण

#अगर 0
/* Get brightness, hue etc. Unreliable... */
अटल u8 sonypi_पढ़ो(u8 fn)
अणु
	u8 v1, v2;
	पूर्णांक n = 100;

	जबतक (n--) अणु
		v1 = sonypi_call2(0x8f, fn);
		v2 = sonypi_call2(0x8f, fn);
		अगर (v1 == v2 && v1 != 0xff)
			वापस v1;
	पूर्ण
	वापस 0xff;
पूर्ण
#पूर्ण_अगर

/* Set brightness, hue etc */
अटल व्योम sonypi_set(u8 fn, u8 v)
अणु
	रुको_on_command(0, sonypi_call3(0x90, fn, v), ITERATIONS_SHORT);
पूर्ण

/* Tests अगर the camera is पढ़ोy */
अटल पूर्णांक sonypi_camera_पढ़ोy(व्योम)
अणु
	u8 v;

	v = sonypi_call2(0x8f, SONYPI_CAMERA_STATUS);
	वापस (v != 0xff && (v & SONYPI_CAMERA_STATUS_READY));
पूर्ण

/* Turns the camera off */
अटल व्योम sonypi_camera_off(व्योम)
अणु
	sonypi_set(SONYPI_CAMERA_PICTURE, SONYPI_CAMERA_MUTE_MASK);

	अगर (!sonypi_device.camera_घातer)
		वापस;

	sonypi_call2(0x91, 0);
	sonypi_device.camera_घातer = 0;
पूर्ण

/* Turns the camera on */
अटल व्योम sonypi_camera_on(व्योम)
अणु
	पूर्णांक i, j;

	अगर (sonypi_device.camera_घातer)
		वापस;

	क्रम (j = 5; j > 0; j--) अणु

		जबतक (sonypi_call2(0x91, 0x1))
			msleep(10);
		sonypi_call1(0x93);

		क्रम (i = 400; i > 0; i--) अणु
			अगर (sonypi_camera_पढ़ोy())
				अवरोध;
			msleep(10);
		पूर्ण
		अगर (i)
			अवरोध;
	पूर्ण

	अगर (j == 0) अणु
		prपूर्णांकk(KERN_WARNING "sonypi: failed to power on camera\n");
		वापस;
	पूर्ण

	sonypi_set(0x10, 0x5a);
	sonypi_device.camera_घातer = 1;
पूर्ण

/* sets the bluetooth subप्रणाली घातer state */
अटल व्योम sonypi_setbluetoothघातer(u8 state)
अणु
	state = !!state;

	अगर (sonypi_device.bluetooth_घातer == state)
		वापस;

	sonypi_call2(0x96, state);
	sonypi_call1(0x82);
	sonypi_device.bluetooth_घातer = state;
पूर्ण

अटल व्योम input_keyrelease(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sonypi_keypress kp;

	जबतक (kfअगरo_out_locked(&sonypi_device.input_fअगरo, (अचिन्हित अक्षर *)&kp,
			 माप(kp), &sonypi_device.input_fअगरo_lock)
			== माप(kp)) अणु
		msleep(10);
		input_report_key(kp.dev, kp.key, 0);
		input_sync(kp.dev);
	पूर्ण
पूर्ण

अटल व्योम sonypi_report_input_event(u8 event)
अणु
	काष्ठा input_dev *jog_dev = sonypi_device.input_jog_dev;
	काष्ठा input_dev *key_dev = sonypi_device.input_key_dev;
	काष्ठा sonypi_keypress kp = अणु शून्य पूर्ण;
	पूर्णांक i;

	चयन (event) अणु
	हाल SONYPI_EVENT_JOGDIAL_UP:
	हाल SONYPI_EVENT_JOGDIAL_UP_PRESSED:
		input_report_rel(jog_dev, REL_WHEEL, 1);
		input_sync(jog_dev);
		अवरोध;

	हाल SONYPI_EVENT_JOGDIAL_DOWN:
	हाल SONYPI_EVENT_JOGDIAL_DOWN_PRESSED:
		input_report_rel(jog_dev, REL_WHEEL, -1);
		input_sync(jog_dev);
		अवरोध;

	हाल SONYPI_EVENT_JOGDIAL_PRESSED:
		kp.key = BTN_MIDDLE;
		kp.dev = jog_dev;
		अवरोध;

	हाल SONYPI_EVENT_FNKEY_RELEASED:
		/* Nothing, not all VAIOs generate this event */
		अवरोध;

	शेष:
		क्रम (i = 0; sonypi_inputkeys[i].sonypiev; i++)
			अगर (event == sonypi_inputkeys[i].sonypiev) अणु
				kp.dev = key_dev;
				kp.key = sonypi_inputkeys[i].inputev;
				अवरोध;
			पूर्ण
		अवरोध;
	पूर्ण

	अगर (kp.dev) अणु
		input_report_key(kp.dev, kp.key, 1);
		input_sync(kp.dev);
		kfअगरo_in_locked(&sonypi_device.input_fअगरo,
			(अचिन्हित अक्षर *)&kp, माप(kp),
			&sonypi_device.input_fअगरo_lock);
		schedule_work(&sonypi_device.input_work);
	पूर्ण
पूर्ण

/* Interrupt handler: some event is available */
अटल irqवापस_t sonypi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	u8 v1, v2, event = 0;
	पूर्णांक i, j;

	v1 = inb_p(sonypi_device.ioport1);
	v2 = inb_p(sonypi_device.ioport1 + sonypi_device.evtype_offset);

	क्रम (i = 0; sonypi_eventtypes[i].model; i++) अणु
		अगर (sonypi_device.model != sonypi_eventtypes[i].model)
			जारी;
		अगर ((v2 & sonypi_eventtypes[i].data) !=
		    sonypi_eventtypes[i].data)
			जारी;
		अगर (!(mask & sonypi_eventtypes[i].mask))
			जारी;
		क्रम (j = 0; sonypi_eventtypes[i].events[j].event; j++) अणु
			अगर (v1 == sonypi_eventtypes[i].events[j].data) अणु
				event = sonypi_eventtypes[i].events[j].event;
				जाओ found;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (verbose)
		prपूर्णांकk(KERN_WARNING
		       "sonypi: unknown event port1=0x%02x,port2=0x%02x\n",
		       v1, v2);
	/* We need to वापस IRQ_HANDLED here because there *are*
	 * events beदीर्घing to the sonypi device we करोn't know about,
	 * but we still करोn't want those to pollute the logs... */
	वापस IRQ_HANDLED;

found:
	अगर (verbose > 1)
		prपूर्णांकk(KERN_INFO
		       "sonypi: event port1=0x%02x,port2=0x%02x\n", v1, v2);

	अगर (useinput)
		sonypi_report_input_event(event);

	kfअगरo_in_locked(&sonypi_device.fअगरo, (अचिन्हित अक्षर *)&event,
			माप(event), &sonypi_device.fअगरo_lock);
	समाप्त_fasync(&sonypi_device.fअगरo_async, SIGIO, POLL_IN);
	wake_up_पूर्णांकerruptible(&sonypi_device.fअगरo_proc_list);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sonypi_misc_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	वापस fasync_helper(fd, filp, on, &sonypi_device.fअगरo_async);
पूर्ण

अटल पूर्णांक sonypi_misc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&sonypi_device.lock);
	sonypi_device.खोलो_count--;
	mutex_unlock(&sonypi_device.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक sonypi_misc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&sonypi_device.lock);
	/* Flush input queue on first खोलो */
	अगर (!sonypi_device.खोलो_count)
		kfअगरo_reset(&sonypi_device.fअगरo);
	sonypi_device.खोलो_count++;
	mutex_unlock(&sonypi_device.lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sonypi_misc_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *pos)
अणु
	sमाप_प्रकार ret;
	अचिन्हित अक्षर c;

	अगर ((kfअगरo_len(&sonypi_device.fअगरo) == 0) &&
	    (file->f_flags & O_NONBLOCK))
		वापस -EAGAIN;

	ret = रुको_event_पूर्णांकerruptible(sonypi_device.fअगरo_proc_list,
				       kfअगरo_len(&sonypi_device.fअगरo) != 0);
	अगर (ret)
		वापस ret;

	जबतक (ret < count &&
	       (kfअगरo_out_locked(&sonypi_device.fअगरo, &c, माप(c),
				 &sonypi_device.fअगरo_lock) == माप(c))) अणु
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
	poll_रुको(file, &sonypi_device.fअगरo_proc_list, रुको);
	अगर (kfअगरo_len(&sonypi_device.fअगरo))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल दीर्घ sonypi_misc_ioctl(काष्ठा file *fp,
			     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret = 0;
	व्योम __user *argp = (व्योम __user *)arg;
	u8 val8;
	u16 val16;

	mutex_lock(&sonypi_device.lock);
	चयन (cmd) अणु
	हाल SONYPI_IOCGBRT:
		अगर (sonypi_ec_पढ़ो(SONYPI_LCD_LIGHT, &val8)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (copy_to_user(argp, &val8, माप(val8)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCSBRT:
		अगर (copy_from_user(&val8, argp, माप(val8))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (sonypi_ec_ग_लिखो(SONYPI_LCD_LIGHT, val8))
			ret = -EIO;
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
		अगर (sonypi_ec_पढ़ो(SONYPI_BAT_FLAGS, &val8)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		val8 &= 0x07;
		अगर (copy_to_user(argp, &val8, माप(val8)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCGBLUE:
		val8 = sonypi_device.bluetooth_घातer;
		अगर (copy_to_user(argp, &val8, माप(val8)))
			ret = -EFAULT;
		अवरोध;
	हाल SONYPI_IOCSBLUE:
		अगर (copy_from_user(&val8, argp, माप(val8))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		sonypi_setbluetoothघातer(val8);
		अवरोध;
	/* FAN Controls */
	हाल SONYPI_IOCGFAN:
		अगर (sonypi_ec_पढ़ो(SONYPI_FAN0_STATUS, &val8)) अणु
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
		अगर (sonypi_ec_ग_लिखो(SONYPI_FAN0_STATUS, val8))
			ret = -EIO;
		अवरोध;
	/* GET Temperature (useful under APM) */
	हाल SONYPI_IOCGTEMP:
		अगर (sonypi_ec_पढ़ो(SONYPI_TEMP_STATUS, &val8)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (copy_to_user(argp, &val8, माप(val8)))
			ret = -EFAULT;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&sonypi_device.lock);
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
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice sonypi_misc_device = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "sonypi",
	.fops		= &sonypi_misc_fops,
पूर्ण;

अटल व्योम sonypi_enable(अचिन्हित पूर्णांक camera_on)
अणु
	चयन (sonypi_device.model) अणु
	हाल SONYPI_DEVICE_MODEL_TYPE1:
		sonypi_type1_srs();
		अवरोध;
	हाल SONYPI_DEVICE_MODEL_TYPE2:
		sonypi_type2_srs();
		अवरोध;
	हाल SONYPI_DEVICE_MODEL_TYPE3:
		sonypi_type3_srs();
		अवरोध;
	पूर्ण

	sonypi_call1(0x82);
	sonypi_call2(0x81, 0xff);
	sonypi_call1(compat ? 0x92 : 0x82);

	/* Enable ACPI mode to get Fn key events */
	अगर (!SONYPI_ACPI_ACTIVE && fnkeyinit)
		outb(0xf0, 0xb2);

	अगर (camera && camera_on)
		sonypi_camera_on();
पूर्ण

अटल पूर्णांक sonypi_disable(व्योम)
अणु
	sonypi_call2(0x81, 0);	/* make sure we करोn't get any more events */
	अगर (camera)
		sonypi_camera_off();

	/* disable ACPI mode */
	अगर (!SONYPI_ACPI_ACTIVE && fnkeyinit)
		outb(0xf1, 0xb2);

	चयन (sonypi_device.model) अणु
	हाल SONYPI_DEVICE_MODEL_TYPE1:
		sonypi_type1_dis();
		अवरोध;
	हाल SONYPI_DEVICE_MODEL_TYPE2:
		sonypi_type2_dis();
		अवरोध;
	हाल SONYPI_DEVICE_MODEL_TYPE3:
		sonypi_type3_dis();
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक sonypi_acpi_add(काष्ठा acpi_device *device)
अणु
	sonypi_acpi_device = device;
	म_नकल(acpi_device_name(device), "Sony laptop hotkeys");
	म_नकल(acpi_device_class(device), "sony/hotkey");
	वापस 0;
पूर्ण

अटल पूर्णांक sonypi_acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	sonypi_acpi_device = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id sonypi_device_ids[] = अणु
	अणु"SNY6001", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver sonypi_acpi_driver = अणु
	.name           = "sonypi",
	.class          = "hkey",
	.ids            = sonypi_device_ids,
	.ops            = अणु
		           .add = sonypi_acpi_add,
			   .हटाओ = sonypi_acpi_हटाओ,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक sonypi_create_input_devices(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *jog_dev;
	काष्ठा input_dev *key_dev;
	पूर्णांक i;
	पूर्णांक error;

	sonypi_device.input_jog_dev = jog_dev = input_allocate_device();
	अगर (!jog_dev)
		वापस -ENOMEM;

	jog_dev->name = "Sony Vaio Jogdial";
	jog_dev->id.bustype = BUS_ISA;
	jog_dev->id.venकरोr = PCI_VENDOR_ID_SONY;
	jog_dev->dev.parent = &pdev->dev;

	jog_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	jog_dev->keybit[BIT_WORD(BTN_MOUSE)] = BIT_MASK(BTN_MIDDLE);
	jog_dev->relbit[0] = BIT_MASK(REL_WHEEL);

	sonypi_device.input_key_dev = key_dev = input_allocate_device();
	अगर (!key_dev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_jogdev;
	पूर्ण

	key_dev->name = "Sony Vaio Keys";
	key_dev->id.bustype = BUS_ISA;
	key_dev->id.venकरोr = PCI_VENDOR_ID_SONY;
	key_dev->dev.parent = &pdev->dev;

	/* Initialize the Input Drivers: special keys */
	key_dev->evbit[0] = BIT_MASK(EV_KEY);
	क्रम (i = 0; sonypi_inputkeys[i].sonypiev; i++)
		अगर (sonypi_inputkeys[i].inputev)
			set_bit(sonypi_inputkeys[i].inputev, key_dev->keybit);

	error = input_रेजिस्टर_device(jog_dev);
	अगर (error)
		जाओ err_मुक्त_keydev;

	error = input_रेजिस्टर_device(key_dev);
	अगर (error)
		जाओ err_unरेजिस्टर_jogdev;

	वापस 0;

 err_unरेजिस्टर_jogdev:
	input_unरेजिस्टर_device(jog_dev);
	/* Set to शून्य so we करोn't मुक्त it again below */
	jog_dev = शून्य;
 err_मुक्त_keydev:
	input_मुक्त_device(key_dev);
	sonypi_device.input_key_dev = शून्य;
 err_मुक्त_jogdev:
	input_मुक्त_device(jog_dev);
	sonypi_device.input_jog_dev = शून्य;

	वापस error;
पूर्ण

अटल पूर्णांक sonypi_setup_ioports(काष्ठा sonypi_device *dev,
				स्थिर काष्ठा sonypi_ioport_list *ioport_list)
अणु
	/* try to detect अगर sony-laptop is being used and thus
	 * has alपढ़ोy requested one of the known ioports.
	 * As in the deprecated check_region this is racy has we have
	 * multiple ioports available and one of them can be requested
	 * between this check and the subsequent request. Anyway, as an
	 * attempt to be some more user-मित्रly as we currently are,
	 * this is enough.
	 */
	स्थिर काष्ठा sonypi_ioport_list *check = ioport_list;
	जबतक (check_ioport && check->port1) अणु
		अगर (!request_region(check->port1,
				   sonypi_device.region_size,
				   "Sony Programmable I/O Device Check")) अणु
			prपूर्णांकk(KERN_ERR "sonypi: ioport 0x%.4x busy, using sony-laptop? "
					"if not use check_ioport=0\n",
					check->port1);
			वापस -EBUSY;
		पूर्ण
		release_region(check->port1, sonypi_device.region_size);
		check++;
	पूर्ण

	जबतक (ioport_list->port1) अणु

		अगर (request_region(ioport_list->port1,
				   sonypi_device.region_size,
				   "Sony Programmable I/O Device")) अणु
			dev->ioport1 = ioport_list->port1;
			dev->ioport2 = ioport_list->port2;
			वापस 0;
		पूर्ण
		ioport_list++;
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक sonypi_setup_irq(काष्ठा sonypi_device *dev,
				      स्थिर काष्ठा sonypi_irq_list *irq_list)
अणु
	जबतक (irq_list->irq) अणु

		अगर (!request_irq(irq_list->irq, sonypi_irq,
				 IRQF_SHARED, "sonypi", sonypi_irq)) अणु
			dev->irq = irq_list->irq;
			dev->bits = irq_list->bits;
			वापस 0;
		पूर्ण
		irq_list++;
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल व्योम sonypi_display_info(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "sonypi: detected type%d model, "
	       "verbose = %d, fnkeyinit = %s, camera = %s, "
	       "compat = %s, mask = 0x%08lx, useinput = %s, acpi = %s\n",
	       sonypi_device.model,
	       verbose,
	       fnkeyinit ? "on" : "off",
	       camera ? "on" : "off",
	       compat ? "on" : "off",
	       mask,
	       useinput ? "on" : "off",
	       SONYPI_ACPI_ACTIVE ? "on" : "off");
	prपूर्णांकk(KERN_INFO "sonypi: enabled at irq=%d, port1=0x%x, port2=0x%x\n",
	       sonypi_device.irq,
	       sonypi_device.ioport1, sonypi_device.ioport2);

	अगर (minor == -1)
		prपूर्णांकk(KERN_INFO "sonypi: device allocated minor is %d\n",
		       sonypi_misc_device.minor);
पूर्ण

अटल पूर्णांक sonypi_probe(काष्ठा platक्रमm_device *dev)
अणु
	स्थिर काष्ठा sonypi_ioport_list *ioport_list;
	स्थिर काष्ठा sonypi_irq_list *irq_list;
	काष्ठा pci_dev *pcidev;
	पूर्णांक error;

	prपूर्णांकk(KERN_WARNING "sonypi: please try the sony-laptop module instead "
			"and report failures, see also "
			"http://www.linux.it/~malattia/wiki/index.php/Sony_drivers\n");

	spin_lock_init(&sonypi_device.fअगरo_lock);
	error = kfअगरo_alloc(&sonypi_device.fअगरo, SONYPI_BUF_SIZE, GFP_KERNEL);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "sonypi: kfifo_alloc failed\n");
		वापस error;
	पूर्ण

	init_रुकोqueue_head(&sonypi_device.fअगरo_proc_list);
	mutex_init(&sonypi_device.lock);
	sonypi_device.bluetooth_घातer = -1;

	अगर ((pcidev = pci_get_device(PCI_VENDOR_ID_INTEL,
				     PCI_DEVICE_ID_INTEL_82371AB_3, शून्य)))
		sonypi_device.model = SONYPI_DEVICE_MODEL_TYPE1;
	अन्यथा अगर ((pcidev = pci_get_device(PCI_VENDOR_ID_INTEL,
					  PCI_DEVICE_ID_INTEL_ICH6_1, शून्य)))
		sonypi_device.model = SONYPI_DEVICE_MODEL_TYPE3;
	अन्यथा अगर ((pcidev = pci_get_device(PCI_VENDOR_ID_INTEL,
					  PCI_DEVICE_ID_INTEL_ICH7_1, शून्य)))
		sonypi_device.model = SONYPI_DEVICE_MODEL_TYPE3;
	अन्यथा
		sonypi_device.model = SONYPI_DEVICE_MODEL_TYPE2;

	अगर (pcidev && pci_enable_device(pcidev)) अणु
		prपूर्णांकk(KERN_ERR "sonypi: pci_enable_device failed\n");
		error = -EIO;
		जाओ err_put_pcidev;
	पूर्ण

	sonypi_device.dev = pcidev;

	अगर (sonypi_device.model == SONYPI_DEVICE_MODEL_TYPE1) अणु
		ioport_list = sonypi_type1_ioport_list;
		sonypi_device.region_size = SONYPI_TYPE1_REGION_SIZE;
		sonypi_device.evtype_offset = SONYPI_TYPE1_EVTYPE_OFFSET;
		irq_list = sonypi_type1_irq_list;
	पूर्ण अन्यथा अगर (sonypi_device.model == SONYPI_DEVICE_MODEL_TYPE2) अणु
		ioport_list = sonypi_type2_ioport_list;
		sonypi_device.region_size = SONYPI_TYPE2_REGION_SIZE;
		sonypi_device.evtype_offset = SONYPI_TYPE2_EVTYPE_OFFSET;
		irq_list = sonypi_type2_irq_list;
	पूर्ण अन्यथा अणु
		ioport_list = sonypi_type3_ioport_list;
		sonypi_device.region_size = SONYPI_TYPE3_REGION_SIZE;
		sonypi_device.evtype_offset = SONYPI_TYPE3_EVTYPE_OFFSET;
		irq_list = sonypi_type3_irq_list;
	पूर्ण

	error = sonypi_setup_ioports(&sonypi_device, ioport_list);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "sonypi: failed to request ioports\n");
		जाओ err_disable_pcidev;
	पूर्ण

	error = sonypi_setup_irq(&sonypi_device, irq_list);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "sonypi: request_irq failed\n");
		जाओ err_मुक्त_ioports;
	पूर्ण

	अगर (minor != -1)
		sonypi_misc_device.minor = minor;
	error = misc_रेजिस्टर(&sonypi_misc_device);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "sonypi: misc_register failed\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	sonypi_display_info();

	अगर (useinput) अणु

		error = sonypi_create_input_devices(dev);
		अगर (error) अणु
			prपूर्णांकk(KERN_ERR
				"sonypi: failed to create input devices\n");
			जाओ err_miscdev_unरेजिस्टर;
		पूर्ण

		spin_lock_init(&sonypi_device.input_fअगरo_lock);
		error = kfअगरo_alloc(&sonypi_device.input_fअगरo, SONYPI_BUF_SIZE,
				GFP_KERNEL);
		अगर (error) अणु
			prपूर्णांकk(KERN_ERR "sonypi: kfifo_alloc failed\n");
			जाओ err_inpdev_unरेजिस्टर;
		पूर्ण

		INIT_WORK(&sonypi_device.input_work, input_keyrelease);
	पूर्ण

	sonypi_enable(0);

	वापस 0;

 err_inpdev_unरेजिस्टर:
	input_unरेजिस्टर_device(sonypi_device.input_key_dev);
	input_unरेजिस्टर_device(sonypi_device.input_jog_dev);
 err_miscdev_unरेजिस्टर:
	misc_deरेजिस्टर(&sonypi_misc_device);
 err_मुक्त_irq:
	मुक्त_irq(sonypi_device.irq, sonypi_irq);
 err_मुक्त_ioports:
	release_region(sonypi_device.ioport1, sonypi_device.region_size);
 err_disable_pcidev:
	अगर (pcidev)
		pci_disable_device(pcidev);
 err_put_pcidev:
	pci_dev_put(pcidev);
	kfअगरo_मुक्त(&sonypi_device.fअगरo);

	वापस error;
पूर्ण

अटल पूर्णांक sonypi_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	sonypi_disable();

	synchronize_irq(sonypi_device.irq);
	flush_work(&sonypi_device.input_work);

	अगर (useinput) अणु
		input_unरेजिस्टर_device(sonypi_device.input_key_dev);
		input_unरेजिस्टर_device(sonypi_device.input_jog_dev);
		kfअगरo_मुक्त(&sonypi_device.input_fअगरo);
	पूर्ण

	misc_deरेजिस्टर(&sonypi_misc_device);

	मुक्त_irq(sonypi_device.irq, sonypi_irq);
	release_region(sonypi_device.ioport1, sonypi_device.region_size);

	अगर (sonypi_device.dev) अणु
		pci_disable_device(sonypi_device.dev);
		pci_dev_put(sonypi_device.dev);
	पूर्ण

	kfअगरo_मुक्त(&sonypi_device.fअगरo);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक old_camera_घातer;

अटल पूर्णांक sonypi_suspend(काष्ठा device *dev)
अणु
	old_camera_घातer = sonypi_device.camera_घातer;
	sonypi_disable();

	वापस 0;
पूर्ण

अटल पूर्णांक sonypi_resume(काष्ठा device *dev)
अणु
	sonypi_enable(old_camera_घातer);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sonypi_pm, sonypi_suspend, sonypi_resume);
#घोषणा SONYPI_PM	(&sonypi_pm)
#अन्यथा
#घोषणा SONYPI_PM	शून्य
#पूर्ण_अगर

अटल व्योम sonypi_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	sonypi_disable();
पूर्ण

अटल काष्ठा platक्रमm_driver sonypi_driver = अणु
	.driver		= अणु
		.name	= "sonypi",
		.pm	= SONYPI_PM,
	पूर्ण,
	.probe		= sonypi_probe,
	.हटाओ		= sonypi_हटाओ,
	.shutकरोwn	= sonypi_shutकरोwn,
पूर्ण;

अटल काष्ठा platक्रमm_device *sonypi_platक्रमm_device;

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

अटल पूर्णांक __init sonypi_init(व्योम)
अणु
	पूर्णांक error;

	prपूर्णांकk(KERN_INFO
		"sonypi: Sony Programmable I/O Controller Driver v%s.\n",
		SONYPI_DRIVER_VERSION);

	अगर (!dmi_check_प्रणाली(sonypi_dmi_table))
		वापस -ENODEV;

	error = platक्रमm_driver_रेजिस्टर(&sonypi_driver);
	अगर (error)
		वापस error;

	sonypi_platक्रमm_device = platक्रमm_device_alloc("sonypi", -1);
	अगर (!sonypi_platक्रमm_device) अणु
		error = -ENOMEM;
		जाओ err_driver_unरेजिस्टर;
	पूर्ण

	error = platक्रमm_device_add(sonypi_platक्रमm_device);
	अगर (error)
		जाओ err_मुक्त_device;

#अगर_घोषित CONFIG_ACPI
	अगर (acpi_bus_रेजिस्टर_driver(&sonypi_acpi_driver) >= 0)
		acpi_driver_रेजिस्टरed = 1;
#पूर्ण_अगर

	वापस 0;

 err_मुक्त_device:
	platक्रमm_device_put(sonypi_platक्रमm_device);
 err_driver_unरेजिस्टर:
	platक्रमm_driver_unरेजिस्टर(&sonypi_driver);
	वापस error;
पूर्ण

अटल व्योम __निकास sonypi_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_ACPI
	अगर (acpi_driver_रेजिस्टरed)
		acpi_bus_unरेजिस्टर_driver(&sonypi_acpi_driver);
#पूर्ण_अगर
	platक्रमm_device_unरेजिस्टर(sonypi_platक्रमm_device);
	platक्रमm_driver_unरेजिस्टर(&sonypi_driver);
	prपूर्णांकk(KERN_INFO "sonypi: removed.\n");
पूर्ण

module_init(sonypi_init);
module_निकास(sonypi_निकास);
