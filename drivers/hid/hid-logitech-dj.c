<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  HID driver क्रम Logitech receivers
 *
 *  Copyright (c) 2011 Logitech
 */



#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/delay.h>
#समावेश <linux/usb.h> /* For to_usb_पूर्णांकerface क्रम kvm extra पूर्णांकf check */
#समावेश <यंत्र/unaligned.h>
#समावेश "hid-ids.h"

#घोषणा DJ_MAX_PAIRED_DEVICES			7
#घोषणा DJ_MAX_NUMBER_NOTIFS			8
#घोषणा DJ_RECEIVER_INDEX			0
#घोषणा DJ_DEVICE_INDEX_MIN			1
#घोषणा DJ_DEVICE_INDEX_MAX			7

#घोषणा DJREPORT_SHORT_LENGTH			15
#घोषणा DJREPORT_LONG_LENGTH			32

#घोषणा REPORT_ID_DJ_SHORT			0x20
#घोषणा REPORT_ID_DJ_LONG			0x21

#घोषणा REPORT_ID_HIDPP_SHORT			0x10
#घोषणा REPORT_ID_HIDPP_LONG			0x11
#घोषणा REPORT_ID_HIDPP_VERY_LONG		0x12

#घोषणा HIDPP_REPORT_SHORT_LENGTH		7
#घोषणा HIDPP_REPORT_LONG_LENGTH		20

#घोषणा HIDPP_RECEIVER_INDEX			0xff

#घोषणा REPORT_TYPE_RFREPORT_FIRST		0x01
#घोषणा REPORT_TYPE_RFREPORT_LAST		0x1F

/* Command Switch to DJ mode */
#घोषणा REPORT_TYPE_CMD_SWITCH			0x80
#घोषणा CMD_SWITCH_PARAM_DEVBITFIELD		0x00
#घोषणा CMD_SWITCH_PARAM_TIMEOUT_SECONDS	0x01
#घोषणा TIMEOUT_NO_KEEPALIVE			0x00

/* Command to Get the list of Paired devices */
#घोषणा REPORT_TYPE_CMD_GET_PAIRED_DEVICES	0x81

/* Device Paired Notअगरication */
#घोषणा REPORT_TYPE_NOTIF_DEVICE_PAIRED		0x41
#घोषणा SPFUNCTION_MORE_NOTIF_EXPECTED		0x01
#घोषणा SPFUNCTION_DEVICE_LIST_EMPTY		0x02
#घोषणा DEVICE_PAIRED_PARAM_SPFUNCTION		0x00
#घोषणा DEVICE_PAIRED_PARAM_EQUAD_ID_LSB	0x01
#घोषणा DEVICE_PAIRED_PARAM_EQUAD_ID_MSB	0x02
#घोषणा DEVICE_PAIRED_RF_REPORT_TYPE		0x03

/* Device Un-Paired Notअगरication */
#घोषणा REPORT_TYPE_NOTIF_DEVICE_UNPAIRED	0x40

/* Connection Status Notअगरication */
#घोषणा REPORT_TYPE_NOTIF_CONNECTION_STATUS	0x42
#घोषणा CONNECTION_STATUS_PARAM_STATUS		0x00
#घोषणा STATUS_LINKLOSS				0x01

/* Error Notअगरication */
#घोषणा REPORT_TYPE_NOTIF_ERROR			0x7F
#घोषणा NOTIF_ERROR_PARAM_ETYPE			0x00
#घोषणा ETYPE_KEEPALIVE_TIMEOUT			0x01

/* supported DJ HID && RF report types */
#घोषणा REPORT_TYPE_KEYBOARD			0x01
#घोषणा REPORT_TYPE_MOUSE			0x02
#घोषणा REPORT_TYPE_CONSUMER_CONTROL		0x03
#घोषणा REPORT_TYPE_SYSTEM_CONTROL		0x04
#घोषणा REPORT_TYPE_MEDIA_CENTER		0x08
#घोषणा REPORT_TYPE_LEDS			0x0E

/* RF Report types bitfield */
#घोषणा STD_KEYBOARD				BIT(1)
#घोषणा STD_MOUSE				BIT(2)
#घोषणा MULTIMEDIA				BIT(3)
#घोषणा POWER_KEYS				BIT(4)
#घोषणा KBD_MOUSE				BIT(5)
#घोषणा MEDIA_CENTER				BIT(8)
#घोषणा KBD_LEDS				BIT(14)
/* Fake (bitnr > NUMBER_OF_HID_REPORTS) bit to track HID++ capability */
#घोषणा HIDPP					BIT_ULL(63)

/* HID++ Device Connected Notअगरication */
#घोषणा REPORT_TYPE_NOTIF_DEVICE_CONNECTED	0x41
#घोषणा HIDPP_PARAM_PROTO_TYPE			0x00
#घोषणा HIDPP_PARAM_DEVICE_INFO			0x01
#घोषणा HIDPP_PARAM_EQUAD_LSB			0x02
#घोषणा HIDPP_PARAM_EQUAD_MSB			0x03
#घोषणा HIDPP_PARAM_27MHZ_DEVID			0x03
#घोषणा HIDPP_DEVICE_TYPE_MASK			GENMASK(3, 0)
#घोषणा HIDPP_LINK_STATUS_MASK			BIT(6)
#घोषणा HIDPP_MANUFACTURER_MASK			BIT(7)

#घोषणा HIDPP_DEVICE_TYPE_KEYBOARD		1
#घोषणा HIDPP_DEVICE_TYPE_MOUSE			2

#घोषणा HIDPP_SET_REGISTER			0x80
#घोषणा HIDPP_GET_LONG_REGISTER			0x83
#घोषणा HIDPP_REG_CONNECTION_STATE		0x02
#घोषणा HIDPP_REG_PAIRING_INFORMATION		0xB5
#घोषणा HIDPP_PAIRING_INFORMATION		0x20
#घोषणा HIDPP_FAKE_DEVICE_ARRIVAL		0x02

क्रमागत recvr_type अणु
	recvr_type_dj,
	recvr_type_hidpp,
	recvr_type_gaming_hidpp,
	recvr_type_mouse_only,
	recvr_type_27mhz,
	recvr_type_bluetooth,
	recvr_type_dinovo,
पूर्ण;

काष्ठा dj_report अणु
	u8 report_id;
	u8 device_index;
	u8 report_type;
	u8 report_params[DJREPORT_SHORT_LENGTH - 3];
पूर्ण;

काष्ठा hidpp_event अणु
	u8 report_id;
	u8 device_index;
	u8 sub_id;
	u8 params[HIDPP_REPORT_LONG_LENGTH - 3U];
पूर्ण __packed;

काष्ठा dj_receiver_dev अणु
	काष्ठा hid_device *mouse;
	काष्ठा hid_device *keyboard;
	काष्ठा hid_device *hidpp;
	काष्ठा dj_device *paired_dj_devices[DJ_MAX_PAIRED_DEVICES +
					    DJ_DEVICE_INDEX_MIN];
	काष्ठा list_head list;
	काष्ठा kref kref;
	काष्ठा work_काष्ठा work;
	काष्ठा kfअगरo notअगर_fअगरo;
	अचिन्हित दीर्घ last_query; /* in jअगरfies */
	bool पढ़ोy;
	क्रमागत recvr_type type;
	अचिन्हित पूर्णांक unnumbered_application;
	spinlock_t lock;
पूर्ण;

काष्ठा dj_device अणु
	काष्ठा hid_device *hdev;
	काष्ठा dj_receiver_dev *dj_receiver_dev;
	u64 reports_supported;
	u8 device_index;
पूर्ण;

#घोषणा WORKITEM_TYPE_EMPTY	0
#घोषणा WORKITEM_TYPE_PAIRED	1
#घोषणा WORKITEM_TYPE_UNPAIRED	2
#घोषणा WORKITEM_TYPE_UNKNOWN	255

काष्ठा dj_workitem अणु
	u8 type;		/* WORKITEM_TYPE_* */
	u8 device_index;
	u8 device_type;
	u8 quad_id_msb;
	u8 quad_id_lsb;
	u64 reports_supported;
पूर्ण;

/* Keyboard descriptor (1) */
अटल स्थिर अक्षर kbd_descriptor[] = अणु
	0x05, 0x01,		/* USAGE_PAGE (generic Desktop)     */
	0x09, 0x06,		/* USAGE (Keyboard)         */
	0xA1, 0x01,		/* COLLECTION (Application)     */
	0x85, 0x01,		/* REPORT_ID (1)            */
	0x95, 0x08,		/*   REPORT_COUNT (8)           */
	0x75, 0x01,		/*   REPORT_SIZE (1)            */
	0x15, 0x00,		/*   LOGICAL_MINIMUM (0)        */
	0x25, 0x01,		/*   LOGICAL_MAXIMUM (1)        */
	0x05, 0x07,		/*   USAGE_PAGE (Keyboard)      */
	0x19, 0xE0,		/*   USAGE_MINIMUM (Left Control)   */
	0x29, 0xE7,		/*   USAGE_MAXIMUM (Right GUI)      */
	0x81, 0x02,		/*   INPUT (Data,Var,Abs)       */
	0x95, 0x06,		/*   REPORT_COUNT (6)           */
	0x75, 0x08,		/*   REPORT_SIZE (8)            */
	0x15, 0x00,		/*   LOGICAL_MINIMUM (0)        */
	0x26, 0xFF, 0x00,	/*   LOGICAL_MAXIMUM (255)      */
	0x05, 0x07,		/*   USAGE_PAGE (Keyboard)      */
	0x19, 0x00,		/*   USAGE_MINIMUM (no event)       */
	0x2A, 0xFF, 0x00,	/*   USAGE_MAXIMUM (reserved)       */
	0x81, 0x00,		/*   INPUT (Data,Ary,Abs)       */
	0x85, 0x0e,		/* REPORT_ID (14)               */
	0x05, 0x08,		/*   USAGE PAGE (LED page)      */
	0x95, 0x05,		/*   REPORT COUNT (5)           */
	0x75, 0x01,		/*   REPORT SIZE (1)            */
	0x15, 0x00,		/*   LOGICAL_MINIMUM (0)        */
	0x25, 0x01,		/*   LOGICAL_MAXIMUM (1)        */
	0x19, 0x01,		/*   USAGE MINIMUM (1)          */
	0x29, 0x05,		/*   USAGE MAXIMUM (5)          */
	0x91, 0x02,		/*   OUTPUT (Data, Variable, Absolute)  */
	0x95, 0x01,		/*   REPORT COUNT (1)           */
	0x75, 0x03,		/*   REPORT SIZE (3)            */
	0x91, 0x01,		/*   OUTPUT (Constant)          */
	0xC0
पूर्ण;

/* Mouse descriptor (2)     */
अटल स्थिर अक्षर mse_descriptor[] = अणु
	0x05, 0x01,		/*  USAGE_PAGE (Generic Desktop)        */
	0x09, 0x02,		/*  USAGE (Mouse)                       */
	0xA1, 0x01,		/*  COLLECTION (Application)            */
	0x85, 0x02,		/*    REPORT_ID = 2                     */
	0x09, 0x01,		/*    USAGE (poपूर्णांकer)                   */
	0xA1, 0x00,		/*    COLLECTION (physical)             */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x01,		/*      USAGE_MIN (1)                   */
	0x29, 0x10,		/*      USAGE_MAX (16)                  */
	0x15, 0x00,		/*      LOGICAL_MIN (0)                 */
	0x25, 0x01,		/*      LOGICAL_MAX (1)                 */
	0x95, 0x10,		/*      REPORT_COUNT (16)               */
	0x75, 0x01,		/*      REPORT_SIZE (1)                 */
	0x81, 0x02,		/*      INPUT (data var असल)            */
	0x05, 0x01,		/*      USAGE_PAGE (generic desktop)    */
	0x16, 0x01, 0xF8,	/*      LOGICAL_MIN (-2047)             */
	0x26, 0xFF, 0x07,	/*      LOGICAL_MAX (2047)              */
	0x75, 0x0C,		/*      REPORT_SIZE (12)                */
	0x95, 0x02,		/*      REPORT_COUNT (2)                */
	0x09, 0x30,		/*      USAGE (X)                       */
	0x09, 0x31,		/*      USAGE (Y)                       */
	0x81, 0x06,		/*      INPUT                           */
	0x15, 0x81,		/*      LOGICAL_MIN (-127)              */
	0x25, 0x7F,		/*      LOGICAL_MAX (127)               */
	0x75, 0x08,		/*      REPORT_SIZE (8)                 */
	0x95, 0x01,		/*      REPORT_COUNT (1)                */
	0x09, 0x38,		/*      USAGE (wheel)                   */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x0C,		/*      USAGE_PAGE(consumer)            */
	0x0A, 0x38, 0x02,	/*      USAGE(AC Pan)                   */
	0x95, 0x01,		/*      REPORT_COUNT (1)                */
	0x81, 0x06,		/*      INPUT                           */
	0xC0,			/*    END_COLLECTION                    */
	0xC0,			/*  END_COLLECTION                      */
पूर्ण;

/* Mouse descriptor (2) क्रम 27 MHz receiver, only 8 buttons */
अटल स्थिर अक्षर mse_27mhz_descriptor[] = अणु
	0x05, 0x01,		/*  USAGE_PAGE (Generic Desktop)        */
	0x09, 0x02,		/*  USAGE (Mouse)                       */
	0xA1, 0x01,		/*  COLLECTION (Application)            */
	0x85, 0x02,		/*    REPORT_ID = 2                     */
	0x09, 0x01,		/*    USAGE (poपूर्णांकer)                   */
	0xA1, 0x00,		/*    COLLECTION (physical)             */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x01,		/*      USAGE_MIN (1)                   */
	0x29, 0x08,		/*      USAGE_MAX (8)                   */
	0x15, 0x00,		/*      LOGICAL_MIN (0)                 */
	0x25, 0x01,		/*      LOGICAL_MAX (1)                 */
	0x95, 0x08,		/*      REPORT_COUNT (8)                */
	0x75, 0x01,		/*      REPORT_SIZE (1)                 */
	0x81, 0x02,		/*      INPUT (data var असल)            */
	0x05, 0x01,		/*      USAGE_PAGE (generic desktop)    */
	0x16, 0x01, 0xF8,	/*      LOGICAL_MIN (-2047)             */
	0x26, 0xFF, 0x07,	/*      LOGICAL_MAX (2047)              */
	0x75, 0x0C,		/*      REPORT_SIZE (12)                */
	0x95, 0x02,		/*      REPORT_COUNT (2)                */
	0x09, 0x30,		/*      USAGE (X)                       */
	0x09, 0x31,		/*      USAGE (Y)                       */
	0x81, 0x06,		/*      INPUT                           */
	0x15, 0x81,		/*      LOGICAL_MIN (-127)              */
	0x25, 0x7F,		/*      LOGICAL_MAX (127)               */
	0x75, 0x08,		/*      REPORT_SIZE (8)                 */
	0x95, 0x01,		/*      REPORT_COUNT (1)                */
	0x09, 0x38,		/*      USAGE (wheel)                   */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x0C,		/*      USAGE_PAGE(consumer)            */
	0x0A, 0x38, 0x02,	/*      USAGE(AC Pan)                   */
	0x95, 0x01,		/*      REPORT_COUNT (1)                */
	0x81, 0x06,		/*      INPUT                           */
	0xC0,			/*    END_COLLECTION                    */
	0xC0,			/*  END_COLLECTION                      */
पूर्ण;

/* Mouse descriptor (2) क्रम Bluetooth receiver, low-res hwheel, 12 buttons */
अटल स्थिर अक्षर mse_bluetooth_descriptor[] = अणु
	0x05, 0x01,		/*  USAGE_PAGE (Generic Desktop)        */
	0x09, 0x02,		/*  USAGE (Mouse)                       */
	0xA1, 0x01,		/*  COLLECTION (Application)            */
	0x85, 0x02,		/*    REPORT_ID = 2                     */
	0x09, 0x01,		/*    USAGE (poपूर्णांकer)                   */
	0xA1, 0x00,		/*    COLLECTION (physical)             */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x01,		/*      USAGE_MIN (1)                   */
	0x29, 0x08,		/*      USAGE_MAX (8)                   */
	0x15, 0x00,		/*      LOGICAL_MIN (0)                 */
	0x25, 0x01,		/*      LOGICAL_MAX (1)                 */
	0x95, 0x08,		/*      REPORT_COUNT (8)                */
	0x75, 0x01,		/*      REPORT_SIZE (1)                 */
	0x81, 0x02,		/*      INPUT (data var असल)            */
	0x05, 0x01,		/*      USAGE_PAGE (generic desktop)    */
	0x16, 0x01, 0xF8,	/*      LOGICAL_MIN (-2047)             */
	0x26, 0xFF, 0x07,	/*      LOGICAL_MAX (2047)              */
	0x75, 0x0C,		/*      REPORT_SIZE (12)                */
	0x95, 0x02,		/*      REPORT_COUNT (2)                */
	0x09, 0x30,		/*      USAGE (X)                       */
	0x09, 0x31,		/*      USAGE (Y)                       */
	0x81, 0x06,		/*      INPUT                           */
	0x15, 0x81,		/*      LOGICAL_MIN (-127)              */
	0x25, 0x7F,		/*      LOGICAL_MAX (127)               */
	0x75, 0x08,		/*      REPORT_SIZE (8)                 */
	0x95, 0x01,		/*      REPORT_COUNT (1)                */
	0x09, 0x38,		/*      USAGE (wheel)                   */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x0C,		/*      USAGE_PAGE(consumer)            */
	0x0A, 0x38, 0x02,	/*      USAGE(AC Pan)                   */
	0x15, 0xF9,		/*      LOGICAL_MIN (-7)                */
	0x25, 0x07,		/*      LOGICAL_MAX (7)                 */
	0x75, 0x04,		/*      REPORT_SIZE (4)                 */
	0x95, 0x01,		/*      REPORT_COUNT (1)                */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x09,		/*      USAGE_MIN (9)                   */
	0x29, 0x0C,		/*      USAGE_MAX (12)                  */
	0x15, 0x00,		/*      LOGICAL_MIN (0)                 */
	0x25, 0x01,		/*      LOGICAL_MAX (1)                 */
	0x75, 0x01,		/*      REPORT_SIZE (1)                 */
	0x95, 0x04,		/*      REPORT_COUNT (4)                */
	0x81, 0x02,		/*      INPUT (Data,Var,Abs)            */
	0xC0,			/*    END_COLLECTION                    */
	0xC0,			/*  END_COLLECTION                      */
पूर्ण;

/* Mouse descriptor (5) क्रम Bluetooth receiver, normal-res hwheel, 8 buttons */
अटल स्थिर अक्षर mse5_bluetooth_descriptor[] = अणु
	0x05, 0x01,		/*  USAGE_PAGE (Generic Desktop)        */
	0x09, 0x02,		/*  Usage (Mouse)                       */
	0xa1, 0x01,		/*  Collection (Application)            */
	0x85, 0x05,		/*   Report ID (5)                      */
	0x09, 0x01,		/*   Usage (Poपूर्णांकer)                    */
	0xa1, 0x00,		/*   Collection (Physical)              */
	0x05, 0x09,		/*    Usage Page (Button)               */
	0x19, 0x01,		/*    Usage Minimum (1)                 */
	0x29, 0x08,		/*    Usage Maximum (8)                 */
	0x15, 0x00,		/*    Logical Minimum (0)               */
	0x25, 0x01,		/*    Logical Maximum (1)               */
	0x95, 0x08,		/*    Report Count (8)                  */
	0x75, 0x01,		/*    Report Size (1)                   */
	0x81, 0x02,		/*    Input (Data,Var,Abs)              */
	0x05, 0x01,		/*    Usage Page (Generic Desktop)      */
	0x16, 0x01, 0xf8,	/*    Logical Minimum (-2047)           */
	0x26, 0xff, 0x07,	/*    Logical Maximum (2047)            */
	0x75, 0x0c,		/*    Report Size (12)                  */
	0x95, 0x02,		/*    Report Count (2)                  */
	0x09, 0x30,		/*    Usage (X)                         */
	0x09, 0x31,		/*    Usage (Y)                         */
	0x81, 0x06,		/*    Input (Data,Var,Rel)              */
	0x15, 0x81,		/*    Logical Minimum (-127)            */
	0x25, 0x7f,		/*    Logical Maximum (127)             */
	0x75, 0x08,		/*    Report Size (8)                   */
	0x95, 0x01,		/*    Report Count (1)                  */
	0x09, 0x38,		/*    Usage (Wheel)                     */
	0x81, 0x06,		/*    Input (Data,Var,Rel)              */
	0x05, 0x0c,		/*    Usage Page (Consumer Devices)     */
	0x0a, 0x38, 0x02,	/*    Usage (AC Pan)                    */
	0x15, 0x81,		/*    Logical Minimum (-127)            */
	0x25, 0x7f,		/*    Logical Maximum (127)             */
	0x75, 0x08,		/*    Report Size (8)                   */
	0x95, 0x01,		/*    Report Count (1)                  */
	0x81, 0x06,		/*    Input (Data,Var,Rel)              */
	0xc0,			/*   End Collection                     */
	0xc0,			/*  End Collection                      */
पूर्ण;

/* Gaming Mouse descriptor (2) */
अटल स्थिर अक्षर mse_high_res_descriptor[] = अणु
	0x05, 0x01,		/*  USAGE_PAGE (Generic Desktop)        */
	0x09, 0x02,		/*  USAGE (Mouse)                       */
	0xA1, 0x01,		/*  COLLECTION (Application)            */
	0x85, 0x02,		/*    REPORT_ID = 2                     */
	0x09, 0x01,		/*    USAGE (poपूर्णांकer)                   */
	0xA1, 0x00,		/*    COLLECTION (physical)             */
	0x05, 0x09,		/*      USAGE_PAGE (buttons)            */
	0x19, 0x01,		/*      USAGE_MIN (1)                   */
	0x29, 0x10,		/*      USAGE_MAX (16)                  */
	0x15, 0x00,		/*      LOGICAL_MIN (0)                 */
	0x25, 0x01,		/*      LOGICAL_MAX (1)                 */
	0x95, 0x10,		/*      REPORT_COUNT (16)               */
	0x75, 0x01,		/*      REPORT_SIZE (1)                 */
	0x81, 0x02,		/*      INPUT (data var असल)            */
	0x05, 0x01,		/*      USAGE_PAGE (generic desktop)    */
	0x16, 0x01, 0x80,	/*      LOGICAL_MIN (-32767)            */
	0x26, 0xFF, 0x7F,	/*      LOGICAL_MAX (32767)             */
	0x75, 0x10,		/*      REPORT_SIZE (16)                */
	0x95, 0x02,		/*      REPORT_COUNT (2)                */
	0x09, 0x30,		/*      USAGE (X)                       */
	0x09, 0x31,		/*      USAGE (Y)                       */
	0x81, 0x06,		/*      INPUT                           */
	0x15, 0x81,		/*      LOGICAL_MIN (-127)              */
	0x25, 0x7F,		/*      LOGICAL_MAX (127)               */
	0x75, 0x08,		/*      REPORT_SIZE (8)                 */
	0x95, 0x01,		/*      REPORT_COUNT (1)                */
	0x09, 0x38,		/*      USAGE (wheel)                   */
	0x81, 0x06,		/*      INPUT                           */
	0x05, 0x0C,		/*      USAGE_PAGE(consumer)            */
	0x0A, 0x38, 0x02,	/*      USAGE(AC Pan)                   */
	0x95, 0x01,		/*      REPORT_COUNT (1)                */
	0x81, 0x06,		/*      INPUT                           */
	0xC0,			/*    END_COLLECTION                    */
	0xC0,			/*  END_COLLECTION                      */
पूर्ण;

/* Consumer Control descriptor (3) */
अटल स्थिर अक्षर consumer_descriptor[] = अणु
	0x05, 0x0C,		/* USAGE_PAGE (Consumer Devices)       */
	0x09, 0x01,		/* USAGE (Consumer Control)            */
	0xA1, 0x01,		/* COLLECTION (Application)            */
	0x85, 0x03,		/* REPORT_ID = 3                       */
	0x75, 0x10,		/* REPORT_SIZE (16)                    */
	0x95, 0x02,		/* REPORT_COUNT (2)                    */
	0x15, 0x01,		/* LOGICAL_MIN (1)                     */
	0x26, 0xFF, 0x02,	/* LOGICAL_MAX (767)                   */
	0x19, 0x01,		/* USAGE_MIN (1)                       */
	0x2A, 0xFF, 0x02,	/* USAGE_MAX (767)                     */
	0x81, 0x00,		/* INPUT (Data Ary Abs)                */
	0xC0,			/* END_COLLECTION                      */
पूर्ण;				/*                                     */

/* System control descriptor (4) */
अटल स्थिर अक्षर syscontrol_descriptor[] = अणु
	0x05, 0x01,		/*   USAGE_PAGE (Generic Desktop)      */
	0x09, 0x80,		/*   USAGE (System Control)            */
	0xA1, 0x01,		/*   COLLECTION (Application)          */
	0x85, 0x04,		/*   REPORT_ID = 4                     */
	0x75, 0x02,		/*   REPORT_SIZE (2)                   */
	0x95, 0x01,		/*   REPORT_COUNT (1)                  */
	0x15, 0x01,		/*   LOGICAL_MIN (1)                   */
	0x25, 0x03,		/*   LOGICAL_MAX (3)                   */
	0x09, 0x82,		/*   USAGE (System Sleep)              */
	0x09, 0x81,		/*   USAGE (System Power Down)         */
	0x09, 0x83,		/*   USAGE (System Wake Up)            */
	0x81, 0x60,		/*   INPUT (Data Ary Abs NPrf Null)    */
	0x75, 0x06,		/*   REPORT_SIZE (6)                   */
	0x81, 0x03,		/*   INPUT (Cnst Var Abs)              */
	0xC0,			/*   END_COLLECTION                    */
पूर्ण;

/* Media descriptor (8) */
अटल स्थिर अक्षर media_descriptor[] = अणु
	0x06, 0xbc, 0xff,	/* Usage Page 0xffbc                   */
	0x09, 0x88,		/* Usage 0x0088                        */
	0xa1, 0x01,		/* BeginCollection                     */
	0x85, 0x08,		/*   Report ID 8                       */
	0x19, 0x01,		/*   Usage Min 0x0001                  */
	0x29, 0xff,		/*   Usage Max 0x00ff                  */
	0x15, 0x01,		/*   Logical Min 1                     */
	0x26, 0xff, 0x00,	/*   Logical Max 255                   */
	0x75, 0x08,		/*   Report Size 8                     */
	0x95, 0x01,		/*   Report Count 1                    */
	0x81, 0x00,		/*   Input                             */
	0xc0,			/* EndCollection                       */
पूर्ण;				/*                                     */

/* HIDPP descriptor */
अटल स्थिर अक्षर hidpp_descriptor[] = अणु
	0x06, 0x00, 0xff,	/* Usage Page (Venकरोr Defined Page 1)  */
	0x09, 0x01,		/* Usage (Venकरोr Usage 1)              */
	0xa1, 0x01,		/* Collection (Application)            */
	0x85, 0x10,		/*   Report ID (16)                    */
	0x75, 0x08,		/*   Report Size (8)                   */
	0x95, 0x06,		/*   Report Count (6)                  */
	0x15, 0x00,		/*   Logical Minimum (0)               */
	0x26, 0xff, 0x00,	/*   Logical Maximum (255)             */
	0x09, 0x01,		/*   Usage (Venकरोr Usage 1)            */
	0x81, 0x00,		/*   Input (Data,Arr,Abs)              */
	0x09, 0x01,		/*   Usage (Venकरोr Usage 1)            */
	0x91, 0x00,		/*   Output (Data,Arr,Abs)             */
	0xc0,			/* End Collection                      */
	0x06, 0x00, 0xff,	/* Usage Page (Venकरोr Defined Page 1)  */
	0x09, 0x02,		/* Usage (Venकरोr Usage 2)              */
	0xa1, 0x01,		/* Collection (Application)            */
	0x85, 0x11,		/*   Report ID (17)                    */
	0x75, 0x08,		/*   Report Size (8)                   */
	0x95, 0x13,		/*   Report Count (19)                 */
	0x15, 0x00,		/*   Logical Minimum (0)               */
	0x26, 0xff, 0x00,	/*   Logical Maximum (255)             */
	0x09, 0x02,		/*   Usage (Venकरोr Usage 2)            */
	0x81, 0x00,		/*   Input (Data,Arr,Abs)              */
	0x09, 0x02,		/*   Usage (Venकरोr Usage 2)            */
	0x91, 0x00,		/*   Output (Data,Arr,Abs)             */
	0xc0,			/* End Collection                      */
	0x06, 0x00, 0xff,	/* Usage Page (Venकरोr Defined Page 1)  */
	0x09, 0x04,		/* Usage (Venकरोr Usage 0x04)           */
	0xa1, 0x01,		/* Collection (Application)            */
	0x85, 0x20,		/*   Report ID (32)                    */
	0x75, 0x08,		/*   Report Size (8)                   */
	0x95, 0x0e,		/*   Report Count (14)                 */
	0x15, 0x00,		/*   Logical Minimum (0)               */
	0x26, 0xff, 0x00,	/*   Logical Maximum (255)             */
	0x09, 0x41,		/*   Usage (Venकरोr Usage 0x41)         */
	0x81, 0x00,		/*   Input (Data,Arr,Abs)              */
	0x09, 0x41,		/*   Usage (Venकरोr Usage 0x41)         */
	0x91, 0x00,		/*   Output (Data,Arr,Abs)             */
	0x85, 0x21,		/*   Report ID (33)                    */
	0x95, 0x1f,		/*   Report Count (31)                 */
	0x15, 0x00,		/*   Logical Minimum (0)               */
	0x26, 0xff, 0x00,	/*   Logical Maximum (255)             */
	0x09, 0x42,		/*   Usage (Venकरोr Usage 0x42)         */
	0x81, 0x00,		/*   Input (Data,Arr,Abs)              */
	0x09, 0x42,		/*   Usage (Venकरोr Usage 0x42)         */
	0x91, 0x00,		/*   Output (Data,Arr,Abs)             */
	0xc0,			/* End Collection                      */
पूर्ण;

/* Maximum size of all defined hid reports in bytes (including report id) */
#घोषणा MAX_REPORT_SIZE 8

/* Make sure all descriptors are present here */
#घोषणा MAX_RDESC_SIZE				\
	(माप(kbd_descriptor) +		\
	 माप(mse_bluetooth_descriptor) +	\
	 माप(mse5_bluetooth_descriptor) +	\
	 माप(consumer_descriptor) +		\
	 माप(syscontrol_descriptor) +	\
	 माप(media_descriptor) +	\
	 माप(hidpp_descriptor))

/* Number of possible hid report types that can be created by this driver.
 *
 * Right now, RF report types have the same report types (or report id's)
 * than the hid report created from those RF reports. In the future
 * this करोesnt have to be true.
 *
 * For instance, RF report type 0x01 which has a size of 8 bytes, corresponds
 * to hid report id 0x01, this is standard keyboard. Same thing applies to mice
 * reports and consumer control, etc. If a new RF report is created, it करोesn't
 * has to have the same report id as its corresponding hid report, so an
 * translation may have to take place क्रम future report types.
 */
#घोषणा NUMBER_OF_HID_REPORTS 32
अटल स्थिर u8 hid_reportid_size_map[NUMBER_OF_HID_REPORTS] = अणु
	[1] = 8,		/* Standard keyboard */
	[2] = 8,		/* Standard mouse */
	[3] = 5,		/* Consumer control */
	[4] = 2,		/* System control */
	[8] = 2,		/* Media Center */
पूर्ण;


#घोषणा LOGITECH_DJ_INTERFACE_NUMBER 0x02

अटल काष्ठा hid_ll_driver logi_dj_ll_driver;

अटल पूर्णांक logi_dj_recv_query_paired_devices(काष्ठा dj_receiver_dev *djrcv_dev);
अटल व्योम delayedwork_callback(काष्ठा work_काष्ठा *work);

अटल LIST_HEAD(dj_hdev_list);
अटल DEFINE_MUTEX(dj_hdev_list_lock);

अटल bool recvr_type_is_bluetooth(क्रमागत recvr_type type)
अणु
	वापस type == recvr_type_bluetooth || type == recvr_type_dinovo;
पूर्ण

/*
 * dj/HID++ receivers are really a single logical entity, but क्रम BIOS/Winकरोws
 * compatibility they have multiple USB पूर्णांकerfaces. On HID++ receivers we need
 * to listen क्रम input reports on both पूर्णांकerfaces. The functions below are used
 * to create a single काष्ठा dj_receiver_dev क्रम all पूर्णांकerfaces beदीर्घing to
 * a single USB-device / receiver.
 */
अटल काष्ठा dj_receiver_dev *dj_find_receiver_dev(काष्ठा hid_device *hdev,
						    क्रमागत recvr_type type)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev;
	अक्षर sep;

	/*
	 * The bluetooth receiver contains a built-in hub and has separate
	 * USB-devices क्रम the keyboard and mouse पूर्णांकerfaces.
	 */
	sep = recvr_type_is_bluetooth(type) ? '.' : '/';

	/* Try to find an alपढ़ोy-probed पूर्णांकerface from the same device */
	list_क्रम_each_entry(djrcv_dev, &dj_hdev_list, list) अणु
		अगर (djrcv_dev->mouse &&
		    hid_compare_device_paths(hdev, djrcv_dev->mouse, sep)) अणु
			kref_get(&djrcv_dev->kref);
			वापस djrcv_dev;
		पूर्ण
		अगर (djrcv_dev->keyboard &&
		    hid_compare_device_paths(hdev, djrcv_dev->keyboard, sep)) अणु
			kref_get(&djrcv_dev->kref);
			वापस djrcv_dev;
		पूर्ण
		अगर (djrcv_dev->hidpp &&
		    hid_compare_device_paths(hdev, djrcv_dev->hidpp, sep)) अणु
			kref_get(&djrcv_dev->kref);
			वापस djrcv_dev;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम dj_release_receiver_dev(काष्ठा kref *kref)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev = container_of(kref, काष्ठा dj_receiver_dev, kref);

	list_del(&djrcv_dev->list);
	kfअगरo_मुक्त(&djrcv_dev->notअगर_fअगरo);
	kमुक्त(djrcv_dev);
पूर्ण

अटल व्योम dj_put_receiver_dev(काष्ठा hid_device *hdev)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);

	mutex_lock(&dj_hdev_list_lock);

	अगर (djrcv_dev->mouse == hdev)
		djrcv_dev->mouse = शून्य;
	अगर (djrcv_dev->keyboard == hdev)
		djrcv_dev->keyboard = शून्य;
	अगर (djrcv_dev->hidpp == hdev)
		djrcv_dev->hidpp = शून्य;

	kref_put(&djrcv_dev->kref, dj_release_receiver_dev);

	mutex_unlock(&dj_hdev_list_lock);
पूर्ण

अटल काष्ठा dj_receiver_dev *dj_get_receiver_dev(काष्ठा hid_device *hdev,
						   क्रमागत recvr_type type,
						   अचिन्हित पूर्णांक application,
						   bool is_hidpp)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev;

	mutex_lock(&dj_hdev_list_lock);

	djrcv_dev = dj_find_receiver_dev(hdev, type);
	अगर (!djrcv_dev) अणु
		djrcv_dev = kzalloc(माप(*djrcv_dev), GFP_KERNEL);
		अगर (!djrcv_dev)
			जाओ out;

		INIT_WORK(&djrcv_dev->work, delayedwork_callback);
		spin_lock_init(&djrcv_dev->lock);
		अगर (kfअगरo_alloc(&djrcv_dev->notअगर_fअगरo,
			    DJ_MAX_NUMBER_NOTIFS * माप(काष्ठा dj_workitem),
			    GFP_KERNEL)) अणु
			kमुक्त(djrcv_dev);
			djrcv_dev = शून्य;
			जाओ out;
		पूर्ण
		kref_init(&djrcv_dev->kref);
		list_add_tail(&djrcv_dev->list, &dj_hdev_list);
		djrcv_dev->last_query = jअगरfies;
		djrcv_dev->type = type;
	पूर्ण

	अगर (application == HID_GD_KEYBOARD)
		djrcv_dev->keyboard = hdev;
	अगर (application == HID_GD_MOUSE)
		djrcv_dev->mouse = hdev;
	अगर (is_hidpp)
		djrcv_dev->hidpp = hdev;

	hid_set_drvdata(hdev, djrcv_dev);
out:
	mutex_unlock(&dj_hdev_list_lock);
	वापस djrcv_dev;
पूर्ण

अटल व्योम logi_dj_recv_destroy_djhid_device(काष्ठा dj_receiver_dev *djrcv_dev,
					      काष्ठा dj_workitem *workitem)
अणु
	/* Called in delayed work context */
	काष्ठा dj_device *dj_dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&djrcv_dev->lock, flags);
	dj_dev = djrcv_dev->paired_dj_devices[workitem->device_index];
	djrcv_dev->paired_dj_devices[workitem->device_index] = शून्य;
	spin_unlock_irqrestore(&djrcv_dev->lock, flags);

	अगर (dj_dev != शून्य) अणु
		hid_destroy_device(dj_dev->hdev);
		kमुक्त(dj_dev);
	पूर्ण अन्यथा अणु
		hid_err(djrcv_dev->hidpp, "%s: can't destroy a NULL device\n",
			__func__);
	पूर्ण
पूर्ण

अटल व्योम logi_dj_recv_add_djhid_device(काष्ठा dj_receiver_dev *djrcv_dev,
					  काष्ठा dj_workitem *workitem)
अणु
	/* Called in delayed work context */
	काष्ठा hid_device *djrcv_hdev = djrcv_dev->hidpp;
	काष्ठा hid_device *dj_hiddev;
	काष्ठा dj_device *dj_dev;
	u8 device_index = workitem->device_index;
	अचिन्हित दीर्घ flags;

	/* Device index goes from 1 to 6, we need 3 bytes to store the
	 * semicolon, the index, and a null terminator
	 */
	अचिन्हित अक्षर पंचांगpstr[3];

	/* We are the only one ever adding a device, no need to lock */
	अगर (djrcv_dev->paired_dj_devices[device_index]) अणु
		/* The device is alपढ़ोy known. No need to पुनः_स्मृतिate it. */
		dbg_hid("%s: device is already known\n", __func__);
		वापस;
	पूर्ण

	dj_hiddev = hid_allocate_device();
	अगर (IS_ERR(dj_hiddev)) अणु
		hid_err(djrcv_hdev, "%s: hid_allocate_dev failed\n", __func__);
		वापस;
	पूर्ण

	dj_hiddev->ll_driver = &logi_dj_ll_driver;

	dj_hiddev->dev.parent = &djrcv_hdev->dev;
	dj_hiddev->bus = BUS_USB;
	dj_hiddev->venकरोr = djrcv_hdev->venकरोr;
	dj_hiddev->product = (workitem->quad_id_msb << 8) |
			      workitem->quad_id_lsb;
	अगर (workitem->device_type) अणु
		स्थिर अक्षर *type_str = "Device";

		चयन (workitem->device_type) अणु
		हाल 0x01: type_str = "Keyboard";	अवरोध;
		हाल 0x02: type_str = "Mouse";		अवरोध;
		हाल 0x03: type_str = "Numpad";		अवरोध;
		हाल 0x04: type_str = "Presenter";	अवरोध;
		हाल 0x07: type_str = "Remote Control";	अवरोध;
		हाल 0x08: type_str = "Trackball";	अवरोध;
		हाल 0x09: type_str = "Touchpad";	अवरोध;
		पूर्ण
		snम_लिखो(dj_hiddev->name, माप(dj_hiddev->name),
			"Logitech Wireless %s PID:%04x",
			type_str, dj_hiddev->product);
	पूर्ण अन्यथा अणु
		snम_लिखो(dj_hiddev->name, माप(dj_hiddev->name),
			"Logitech Wireless Device PID:%04x",
			dj_hiddev->product);
	पूर्ण

	अगर (djrcv_dev->type == recvr_type_27mhz)
		dj_hiddev->group = HID_GROUP_LOGITECH_27MHZ_DEVICE;
	अन्यथा
		dj_hiddev->group = HID_GROUP_LOGITECH_DJ_DEVICE;

	स_नकल(dj_hiddev->phys, djrcv_hdev->phys, माप(djrcv_hdev->phys));
	snम_लिखो(पंचांगpstr, माप(पंचांगpstr), ":%d", device_index);
	strlcat(dj_hiddev->phys, पंचांगpstr, माप(dj_hiddev->phys));

	dj_dev = kzalloc(माप(काष्ठा dj_device), GFP_KERNEL);

	अगर (!dj_dev) अणु
		hid_err(djrcv_hdev, "%s: failed allocating dj_dev\n", __func__);
		जाओ dj_device_allocate_fail;
	पूर्ण

	dj_dev->reports_supported = workitem->reports_supported;
	dj_dev->hdev = dj_hiddev;
	dj_dev->dj_receiver_dev = djrcv_dev;
	dj_dev->device_index = device_index;
	dj_hiddev->driver_data = dj_dev;

	spin_lock_irqsave(&djrcv_dev->lock, flags);
	djrcv_dev->paired_dj_devices[device_index] = dj_dev;
	spin_unlock_irqrestore(&djrcv_dev->lock, flags);

	अगर (hid_add_device(dj_hiddev)) अणु
		hid_err(djrcv_hdev, "%s: failed adding dj_device\n", __func__);
		जाओ hid_add_device_fail;
	पूर्ण

	वापस;

hid_add_device_fail:
	spin_lock_irqsave(&djrcv_dev->lock, flags);
	djrcv_dev->paired_dj_devices[device_index] = शून्य;
	spin_unlock_irqrestore(&djrcv_dev->lock, flags);
	kमुक्त(dj_dev);
dj_device_allocate_fail:
	hid_destroy_device(dj_hiddev);
पूर्ण

अटल व्योम delayedwork_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev =
		container_of(work, काष्ठा dj_receiver_dev, work);

	काष्ठा dj_workitem workitem;
	अचिन्हित दीर्घ flags;
	पूर्णांक count;
	पूर्णांक retval;

	dbg_hid("%s\n", __func__);

	spin_lock_irqsave(&djrcv_dev->lock, flags);

	/*
	 * Since we attach to multiple पूर्णांकerfaces, we may get scheduled beक्रमe
	 * we are bound to the HID++ पूर्णांकerface, catch this.
	 */
	अगर (!djrcv_dev->पढ़ोy) अणु
		pr_warn("%s: delayedwork queued before hidpp interface was enumerated\n",
			__func__);
		spin_unlock_irqrestore(&djrcv_dev->lock, flags);
		वापस;
	पूर्ण

	count = kfअगरo_out(&djrcv_dev->notअगर_fअगरo, &workitem, माप(workitem));

	अगर (count != माप(workitem)) अणु
		spin_unlock_irqrestore(&djrcv_dev->lock, flags);
		वापस;
	पूर्ण

	अगर (!kfअगरo_is_empty(&djrcv_dev->notअगर_fअगरo))
		schedule_work(&djrcv_dev->work);

	spin_unlock_irqrestore(&djrcv_dev->lock, flags);

	चयन (workitem.type) अणु
	हाल WORKITEM_TYPE_PAIRED:
		logi_dj_recv_add_djhid_device(djrcv_dev, &workitem);
		अवरोध;
	हाल WORKITEM_TYPE_UNPAIRED:
		logi_dj_recv_destroy_djhid_device(djrcv_dev, &workitem);
		अवरोध;
	हाल WORKITEM_TYPE_UNKNOWN:
		retval = logi_dj_recv_query_paired_devices(djrcv_dev);
		अगर (retval) अणु
			hid_err(djrcv_dev->hidpp, "%s: logi_dj_recv_query_paired_devices error: %d\n",
				__func__, retval);
		पूर्ण
		अवरोध;
	हाल WORKITEM_TYPE_EMPTY:
		dbg_hid("%s: device list is empty\n", __func__);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Someबार we receive reports क्रम which we करो not have a paired dj_device
 * associated with the device_index or report-type to क्रमward the report to.
 * This means that the original "device paired" notअगरication corresponding
 * to the dj_device never arrived to this driver. Possible reasons क्रम this are:
 * 1) hid-core discards all packets coming from a device during probe().
 * 2) अगर the receiver is plugged पूर्णांकo a KVM चयन then the pairing reports
 * are only क्रमwarded to it अगर the focus is on this PC.
 * This function deals with this by re-asking the receiver क्रम the list of
 * connected devices in the delayed work callback.
 * This function MUST be called with djrcv->lock held.
 */
अटल व्योम logi_dj_recv_queue_unknown_work(काष्ठा dj_receiver_dev *djrcv_dev)
अणु
	काष्ठा dj_workitem workitem = अणु .type = WORKITEM_TYPE_UNKNOWN पूर्ण;

	/* Rate limit queries करोne because of unhandled reports to 2/sec */
	अगर (समय_beक्रमe(jअगरfies, djrcv_dev->last_query + HZ / 2))
		वापस;

	kfअगरo_in(&djrcv_dev->notअगर_fअगरo, &workitem, माप(workitem));
	schedule_work(&djrcv_dev->work);
पूर्ण

अटल व्योम logi_dj_recv_queue_notअगरication(काष्ठा dj_receiver_dev *djrcv_dev,
					   काष्ठा dj_report *dj_report)
अणु
	/* We are called from atomic context (tasklet && djrcv->lock held) */
	काष्ठा dj_workitem workitem = अणु
		.device_index = dj_report->device_index,
	पूर्ण;

	चयन (dj_report->report_type) अणु
	हाल REPORT_TYPE_NOTIF_DEVICE_PAIRED:
		workitem.type = WORKITEM_TYPE_PAIRED;
		अगर (dj_report->report_params[DEVICE_PAIRED_PARAM_SPFUNCTION] &
		    SPFUNCTION_DEVICE_LIST_EMPTY) अणु
			workitem.type = WORKITEM_TYPE_EMPTY;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल REPORT_TYPE_NOTIF_DEVICE_UNPAIRED:
		workitem.quad_id_msb =
			dj_report->report_params[DEVICE_PAIRED_PARAM_EQUAD_ID_MSB];
		workitem.quad_id_lsb =
			dj_report->report_params[DEVICE_PAIRED_PARAM_EQUAD_ID_LSB];
		workitem.reports_supported = get_unaligned_le32(
						dj_report->report_params +
						DEVICE_PAIRED_RF_REPORT_TYPE);
		workitem.reports_supported |= HIDPP;
		अगर (dj_report->report_type == REPORT_TYPE_NOTIF_DEVICE_UNPAIRED)
			workitem.type = WORKITEM_TYPE_UNPAIRED;
		अवरोध;
	शेष:
		logi_dj_recv_queue_unknown_work(djrcv_dev);
		वापस;
	पूर्ण

	kfअगरo_in(&djrcv_dev->notअगर_fअगरo, &workitem, माप(workitem));
	schedule_work(&djrcv_dev->work);
पूर्ण

/*
 * Some quad/bluetooth keyboards have a builtin touchpad in this हाल we see
 * only 1 paired device with a device_type of REPORT_TYPE_KEYBOARD. For the
 * touchpad to work we must also क्रमward mouse input reports to the dj_hiddev
 * created क्रम the keyboard (instead of क्रमwarding them to a second paired
 * device with a device_type of REPORT_TYPE_MOUSE as we normally would).
 *
 * On Dinovo receivers the keyboard's touchpad and an optional paired actual
 * mouse send separate input reports, INPUT(2) aka STD_MOUSE क्रम the mouse
 * and INPUT(5) aka KBD_MOUSE क्रम the keyboard's touchpad.
 *
 * On MX5x00 receivers (which can also be paired with a Dinovo keyboard)
 * INPUT(2) is used क्रम both an optional paired actual mouse and क्रम the
 * keyboard's touchpad.
 */
अटल स्थिर u16 kbd_builtin_touchpad_ids[] = अणु
	0xb309, /* Dinovo Edge */
	0xb30c, /* Dinovo Mini */
पूर्ण;

अटल व्योम logi_hidpp_dev_conn_notअगर_equad(काष्ठा hid_device *hdev,
					    काष्ठा hidpp_event *hidpp_report,
					    काष्ठा dj_workitem *workitem)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);
	पूर्णांक i, id;

	workitem->type = WORKITEM_TYPE_PAIRED;
	workitem->device_type = hidpp_report->params[HIDPP_PARAM_DEVICE_INFO] &
				HIDPP_DEVICE_TYPE_MASK;
	workitem->quad_id_msb = hidpp_report->params[HIDPP_PARAM_EQUAD_MSB];
	workitem->quad_id_lsb = hidpp_report->params[HIDPP_PARAM_EQUAD_LSB];
	चयन (workitem->device_type) अणु
	हाल REPORT_TYPE_KEYBOARD:
		workitem->reports_supported |= STD_KEYBOARD | MULTIMEDIA |
					       POWER_KEYS | MEDIA_CENTER |
					       HIDPP;
		id = (workitem->quad_id_msb << 8) | workitem->quad_id_lsb;
		क्रम (i = 0; i < ARRAY_SIZE(kbd_builtin_touchpad_ids); i++) अणु
			अगर (id == kbd_builtin_touchpad_ids[i]) अणु
				अगर (djrcv_dev->type == recvr_type_dinovo)
					workitem->reports_supported |= KBD_MOUSE;
				अन्यथा
					workitem->reports_supported |= STD_MOUSE;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल REPORT_TYPE_MOUSE:
		workitem->reports_supported |= STD_MOUSE | HIDPP;
		अगर (djrcv_dev->type == recvr_type_mouse_only)
			workitem->reports_supported |= MULTIMEDIA;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम logi_hidpp_dev_conn_notअगर_27mhz(काष्ठा hid_device *hdev,
					    काष्ठा hidpp_event *hidpp_report,
					    काष्ठा dj_workitem *workitem)
अणु
	workitem->type = WORKITEM_TYPE_PAIRED;
	workitem->quad_id_lsb = hidpp_report->params[HIDPP_PARAM_27MHZ_DEVID];
	चयन (hidpp_report->device_index) अणु
	हाल 1: /* Index 1 is always a mouse */
	हाल 2: /* Index 2 is always a mouse */
		workitem->device_type = HIDPP_DEVICE_TYPE_MOUSE;
		workitem->reports_supported |= STD_MOUSE | HIDPP;
		अवरोध;
	हाल 3: /* Index 3 is always the keyboard */
	हाल 4: /* Index 4 is used क्रम an optional separate numpad */
		workitem->device_type = HIDPP_DEVICE_TYPE_KEYBOARD;
		workitem->reports_supported |= STD_KEYBOARD | MULTIMEDIA |
					       POWER_KEYS | HIDPP;
		अवरोध;
	शेष:
		hid_warn(hdev, "%s: unexpected device-index %d", __func__,
			 hidpp_report->device_index);
	पूर्ण
पूर्ण

अटल व्योम logi_hidpp_recv_queue_notअगर(काष्ठा hid_device *hdev,
					काष्ठा hidpp_event *hidpp_report)
अणु
	/* We are called from atomic context (tasklet && djrcv->lock held) */
	काष्ठा dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);
	स्थिर अक्षर *device_type = "UNKNOWN";
	काष्ठा dj_workitem workitem = अणु
		.type = WORKITEM_TYPE_EMPTY,
		.device_index = hidpp_report->device_index,
	पूर्ण;

	चयन (hidpp_report->params[HIDPP_PARAM_PROTO_TYPE]) अणु
	हाल 0x01:
		device_type = "Bluetooth";
		/* Bluetooth connect packet contents is the same as (e)QUAD */
		logi_hidpp_dev_conn_notअगर_equad(hdev, hidpp_report, &workitem);
		अगर (!(hidpp_report->params[HIDPP_PARAM_DEVICE_INFO] &
						HIDPP_MANUFACTURER_MASK)) अणु
			hid_info(hdev, "Non Logitech device connected on slot %d\n",
				 hidpp_report->device_index);
			workitem.reports_supported &= ~HIDPP;
		पूर्ण
		अवरोध;
	हाल 0x02:
		device_type = "27 Mhz";
		logi_hidpp_dev_conn_notअगर_27mhz(hdev, hidpp_report, &workitem);
		अवरोध;
	हाल 0x03:
		device_type = "QUAD or eQUAD";
		logi_hidpp_dev_conn_notअगर_equad(hdev, hidpp_report, &workitem);
		अवरोध;
	हाल 0x04:
		device_type = "eQUAD step 4 DJ";
		logi_hidpp_dev_conn_notअगर_equad(hdev, hidpp_report, &workitem);
		अवरोध;
	हाल 0x05:
		device_type = "DFU Lite";
		अवरोध;
	हाल 0x06:
		device_type = "eQUAD step 4 Lite";
		logi_hidpp_dev_conn_notअगर_equad(hdev, hidpp_report, &workitem);
		अवरोध;
	हाल 0x07:
		device_type = "eQUAD step 4 Gaming";
		logi_hidpp_dev_conn_notअगर_equad(hdev, hidpp_report, &workitem);
		workitem.reports_supported |= STD_KEYBOARD;
		अवरोध;
	हाल 0x08:
		device_type = "eQUAD step 4 for gamepads";
		अवरोध;
	हाल 0x0a:
		device_type = "eQUAD nano Lite";
		logi_hidpp_dev_conn_notअगर_equad(hdev, hidpp_report, &workitem);
		अवरोध;
	हाल 0x0c:
		device_type = "eQUAD Lightspeed 1";
		logi_hidpp_dev_conn_notअगर_equad(hdev, hidpp_report, &workitem);
		workitem.reports_supported |= STD_KEYBOARD;
		अवरोध;
	हाल 0x0d:
		device_type = "eQUAD Lightspeed 1.1";
		logi_hidpp_dev_conn_notअगर_equad(hdev, hidpp_report, &workitem);
		workitem.reports_supported |= STD_KEYBOARD;
		अवरोध;
	हाल 0x0f:
		device_type = "eQUAD Lightspeed 1.2";
		logi_hidpp_dev_conn_notअगर_equad(hdev, hidpp_report, &workitem);
		workitem.reports_supported |= STD_KEYBOARD;
		अवरोध;
	पूर्ण

	/* custom receiver device (eg. घातerplay) */
	अगर (hidpp_report->device_index == 7) अणु
		workitem.reports_supported |= HIDPP;
	पूर्ण

	अगर (workitem.type == WORKITEM_TYPE_EMPTY) अणु
		hid_warn(hdev,
			 "unusable device of type %s (0x%02x) connected on slot %d",
			 device_type,
			 hidpp_report->params[HIDPP_PARAM_PROTO_TYPE],
			 hidpp_report->device_index);
		वापस;
	पूर्ण

	hid_info(hdev, "device of type %s (0x%02x) connected on slot %d",
		 device_type, hidpp_report->params[HIDPP_PARAM_PROTO_TYPE],
		 hidpp_report->device_index);

	kfअगरo_in(&djrcv_dev->notअगर_fअगरo, &workitem, माप(workitem));
	schedule_work(&djrcv_dev->work);
पूर्ण

अटल व्योम logi_dj_recv_क्रमward_null_report(काष्ठा dj_receiver_dev *djrcv_dev,
					     काष्ठा dj_report *dj_report)
अणु
	/* We are called from atomic context (tasklet && djrcv->lock held) */
	अचिन्हित पूर्णांक i;
	u8 reportbuffer[MAX_REPORT_SIZE];
	काष्ठा dj_device *djdev;

	djdev = djrcv_dev->paired_dj_devices[dj_report->device_index];

	स_रखो(reportbuffer, 0, माप(reportbuffer));

	क्रम (i = 0; i < NUMBER_OF_HID_REPORTS; i++) अणु
		अगर (djdev->reports_supported & (1 << i)) अणु
			reportbuffer[0] = i;
			अगर (hid_input_report(djdev->hdev,
					     HID_INPUT_REPORT,
					     reportbuffer,
					     hid_reportid_size_map[i], 1)) अणु
				dbg_hid("hid_input_report error sending null "
					"report\n");
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम logi_dj_recv_क्रमward_dj(काष्ठा dj_receiver_dev *djrcv_dev,
				    काष्ठा dj_report *dj_report)
अणु
	/* We are called from atomic context (tasklet && djrcv->lock held) */
	काष्ठा dj_device *dj_device;

	dj_device = djrcv_dev->paired_dj_devices[dj_report->device_index];

	अगर ((dj_report->report_type > ARRAY_SIZE(hid_reportid_size_map) - 1) ||
	    (hid_reportid_size_map[dj_report->report_type] == 0)) अणु
		dbg_hid("invalid report type:%x\n", dj_report->report_type);
		वापस;
	पूर्ण

	अगर (hid_input_report(dj_device->hdev,
			HID_INPUT_REPORT, &dj_report->report_type,
			hid_reportid_size_map[dj_report->report_type], 1)) अणु
		dbg_hid("hid_input_report error\n");
	पूर्ण
पूर्ण

अटल व्योम logi_dj_recv_क्रमward_report(काष्ठा dj_device *dj_dev, u8 *data,
					पूर्णांक size)
अणु
	/* We are called from atomic context (tasklet && djrcv->lock held) */
	अगर (hid_input_report(dj_dev->hdev, HID_INPUT_REPORT, data, size, 1))
		dbg_hid("hid_input_report error\n");
पूर्ण

अटल व्योम logi_dj_recv_क्रमward_input_report(काष्ठा hid_device *hdev,
					      u8 *data, पूर्णांक size)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);
	काष्ठा dj_device *dj_dev;
	अचिन्हित दीर्घ flags;
	u8 report = data[0];
	पूर्णांक i;

	अगर (report > REPORT_TYPE_RFREPORT_LAST) अणु
		hid_err(hdev, "Unexpected input report number %d\n", report);
		वापस;
	पूर्ण

	spin_lock_irqsave(&djrcv_dev->lock, flags);
	क्रम (i = 0; i < (DJ_MAX_PAIRED_DEVICES + DJ_DEVICE_INDEX_MIN); i++) अणु
		dj_dev = djrcv_dev->paired_dj_devices[i];
		अगर (dj_dev && (dj_dev->reports_supported & BIT(report))) अणु
			logi_dj_recv_क्रमward_report(dj_dev, data, size);
			spin_unlock_irqrestore(&djrcv_dev->lock, flags);
			वापस;
		पूर्ण
	पूर्ण

	logi_dj_recv_queue_unknown_work(djrcv_dev);
	spin_unlock_irqrestore(&djrcv_dev->lock, flags);

	dbg_hid("No dj-devs handling input report number %d\n", report);
पूर्ण

अटल पूर्णांक logi_dj_recv_send_report(काष्ठा dj_receiver_dev *djrcv_dev,
				    काष्ठा dj_report *dj_report)
अणु
	काष्ठा hid_device *hdev = djrcv_dev->hidpp;
	काष्ठा hid_report *report;
	काष्ठा hid_report_क्रमागत *output_report_क्रमागत;
	u8 *data = (u8 *)(&dj_report->device_index);
	अचिन्हित पूर्णांक i;

	output_report_क्रमागत = &hdev->report_क्रमागत[HID_OUTPUT_REPORT];
	report = output_report_क्रमागत->report_id_hash[REPORT_ID_DJ_SHORT];

	अगर (!report) अणु
		hid_err(hdev, "%s: unable to find dj report\n", __func__);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < DJREPORT_SHORT_LENGTH - 1; i++)
		report->field[0]->value[i] = data[i];

	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक logi_dj_recv_query_hidpp_devices(काष्ठा dj_receiver_dev *djrcv_dev)
अणु
	अटल स्थिर u8 ढाँचा[] = अणु
		REPORT_ID_HIDPP_SHORT,
		HIDPP_RECEIVER_INDEX,
		HIDPP_SET_REGISTER,
		HIDPP_REG_CONNECTION_STATE,
		HIDPP_FAKE_DEVICE_ARRIVAL,
		0x00, 0x00
	पूर्ण;
	u8 *hidpp_report;
	पूर्णांक retval;

	hidpp_report = kmemdup(ढाँचा, माप(ढाँचा), GFP_KERNEL);
	अगर (!hidpp_report)
		वापस -ENOMEM;

	retval = hid_hw_raw_request(djrcv_dev->hidpp,
				    REPORT_ID_HIDPP_SHORT,
				    hidpp_report, माप(ढाँचा),
				    HID_OUTPUT_REPORT,
				    HID_REQ_SET_REPORT);

	kमुक्त(hidpp_report);
	वापस (retval < 0) ? retval : 0;
पूर्ण

अटल पूर्णांक logi_dj_recv_query_paired_devices(काष्ठा dj_receiver_dev *djrcv_dev)
अणु
	काष्ठा dj_report *dj_report;
	पूर्णांक retval;

	djrcv_dev->last_query = jअगरfies;

	अगर (djrcv_dev->type != recvr_type_dj)
		वापस logi_dj_recv_query_hidpp_devices(djrcv_dev);

	dj_report = kzalloc(माप(काष्ठा dj_report), GFP_KERNEL);
	अगर (!dj_report)
		वापस -ENOMEM;
	dj_report->report_id = REPORT_ID_DJ_SHORT;
	dj_report->device_index = HIDPP_RECEIVER_INDEX;
	dj_report->report_type = REPORT_TYPE_CMD_GET_PAIRED_DEVICES;
	retval = logi_dj_recv_send_report(djrcv_dev, dj_report);
	kमुक्त(dj_report);
	वापस retval;
पूर्ण


अटल पूर्णांक logi_dj_recv_चयन_to_dj_mode(काष्ठा dj_receiver_dev *djrcv_dev,
					  अचिन्हित समयout)
अणु
	काष्ठा hid_device *hdev = djrcv_dev->hidpp;
	काष्ठा dj_report *dj_report;
	u8 *buf;
	पूर्णांक retval = 0;

	dj_report = kzalloc(माप(काष्ठा dj_report), GFP_KERNEL);
	अगर (!dj_report)
		वापस -ENOMEM;

	अगर (djrcv_dev->type == recvr_type_dj) अणु
		dj_report->report_id = REPORT_ID_DJ_SHORT;
		dj_report->device_index = HIDPP_RECEIVER_INDEX;
		dj_report->report_type = REPORT_TYPE_CMD_SWITCH;
		dj_report->report_params[CMD_SWITCH_PARAM_DEVBITFIELD] = 0x3F;
		dj_report->report_params[CMD_SWITCH_PARAM_TIMEOUT_SECONDS] =
								(u8)समयout;

		retval = logi_dj_recv_send_report(djrcv_dev, dj_report);

		/*
		 * Ugly sleep to work around a USB 3.0 bug when the receiver is
		 * still processing the "switch-to-dj" command जबतक we send an
		 * other command.
		 * 50 msec should gives enough समय to the receiver to be पढ़ोy.
		 */
		msleep(50);
	पूर्ण

	/*
	 * Magical bits to set up hidpp notअगरications when the dj devices
	 * are connected/disconnected.
	 *
	 * We can reuse dj_report because HIDPP_REPORT_SHORT_LENGTH is smaller
	 * than DJREPORT_SHORT_LENGTH.
	 */
	buf = (u8 *)dj_report;

	स_रखो(buf, 0, HIDPP_REPORT_SHORT_LENGTH);

	buf[0] = REPORT_ID_HIDPP_SHORT;
	buf[1] = HIDPP_RECEIVER_INDEX;
	buf[2] = 0x80;
	buf[3] = 0x00;
	buf[4] = 0x00;
	buf[5] = 0x09;
	buf[6] = 0x00;

	hid_hw_raw_request(hdev, REPORT_ID_HIDPP_SHORT, buf,
			HIDPP_REPORT_SHORT_LENGTH, HID_OUTPUT_REPORT,
			HID_REQ_SET_REPORT);

	kमुक्त(dj_report);
	वापस retval;
पूर्ण


अटल पूर्णांक logi_dj_ll_खोलो(काष्ठा hid_device *hid)
अणु
	dbg_hid("%s: %s\n", __func__, hid->phys);
	वापस 0;

पूर्ण

अटल व्योम logi_dj_ll_बंद(काष्ठा hid_device *hid)
अणु
	dbg_hid("%s: %s\n", __func__, hid->phys);
पूर्ण

/*
 * Register 0xB5 is "pairing information". It is solely पूर्णांकended क्रम the
 * receiver, so करो not overग_लिखो the device index.
 */
अटल u8 unअगरying_pairing_query[]  = अणु REPORT_ID_HIDPP_SHORT,
					HIDPP_RECEIVER_INDEX,
					HIDPP_GET_LONG_REGISTER,
					HIDPP_REG_PAIRING_INFORMATION पूर्ण;
अटल u8 unअगरying_pairing_answer[] = अणु REPORT_ID_HIDPP_LONG,
					HIDPP_RECEIVER_INDEX,
					HIDPP_GET_LONG_REGISTER,
					HIDPP_REG_PAIRING_INFORMATION पूर्ण;

अटल पूर्णांक logi_dj_ll_raw_request(काष्ठा hid_device *hid,
				  अचिन्हित अक्षर reportnum, __u8 *buf,
				  माप_प्रकार count, अचिन्हित अक्षर report_type,
				  पूर्णांक reqtype)
अणु
	काष्ठा dj_device *djdev = hid->driver_data;
	काष्ठा dj_receiver_dev *djrcv_dev = djdev->dj_receiver_dev;
	u8 *out_buf;
	पूर्णांक ret;

	अगर ((buf[0] == REPORT_ID_HIDPP_SHORT) ||
	    (buf[0] == REPORT_ID_HIDPP_LONG) ||
	    (buf[0] == REPORT_ID_HIDPP_VERY_LONG)) अणु
		अगर (count < 2)
			वापस -EINVAL;

		/* special हाल where we should not overग_लिखो
		 * the device_index */
		अगर (count == 7 && !स_भेद(buf, unअगरying_pairing_query,
					  माप(unअगरying_pairing_query)))
			buf[4] = (buf[4] & 0xf0) | (djdev->device_index - 1);
		अन्यथा
			buf[1] = djdev->device_index;
		वापस hid_hw_raw_request(djrcv_dev->hidpp, reportnum, buf,
				count, report_type, reqtype);
	पूर्ण

	अगर (buf[0] != REPORT_TYPE_LEDS)
		वापस -EINVAL;

	अगर (djrcv_dev->type != recvr_type_dj && count >= 2) अणु
		अगर (!djrcv_dev->keyboard) अणु
			hid_warn(hid, "Received REPORT_TYPE_LEDS request before the keyboard interface was enumerated\n");
			वापस 0;
		पूर्ण
		/* usbhid overrides the report ID and ignores the first byte */
		वापस hid_hw_raw_request(djrcv_dev->keyboard, 0, buf, count,
					  report_type, reqtype);
	पूर्ण

	out_buf = kzalloc(DJREPORT_SHORT_LENGTH, GFP_ATOMIC);
	अगर (!out_buf)
		वापस -ENOMEM;

	अगर (count > DJREPORT_SHORT_LENGTH - 2)
		count = DJREPORT_SHORT_LENGTH - 2;

	out_buf[0] = REPORT_ID_DJ_SHORT;
	out_buf[1] = djdev->device_index;
	स_नकल(out_buf + 2, buf, count);

	ret = hid_hw_raw_request(djrcv_dev->hidpp, out_buf[0], out_buf,
		DJREPORT_SHORT_LENGTH, report_type, reqtype);

	kमुक्त(out_buf);
	वापस ret;
पूर्ण

अटल व्योम rdcat(अक्षर *rdesc, अचिन्हित पूर्णांक *rsize, स्थिर अक्षर *data, अचिन्हित पूर्णांक size)
अणु
	स_नकल(rdesc + *rsize, data, size);
	*rsize += size;
पूर्ण

अटल पूर्णांक logi_dj_ll_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा dj_device *djdev = hid->driver_data;
	अचिन्हित पूर्णांक rsize = 0;
	अक्षर *rdesc;
	पूर्णांक retval;

	dbg_hid("%s\n", __func__);

	djdev->hdev->version = 0x0111;
	djdev->hdev->country = 0x00;

	rdesc = kदो_स्मृति(MAX_RDESC_SIZE, GFP_KERNEL);
	अगर (!rdesc)
		वापस -ENOMEM;

	अगर (djdev->reports_supported & STD_KEYBOARD) अणु
		dbg_hid("%s: sending a kbd descriptor, reports_supported: %llx\n",
			__func__, djdev->reports_supported);
		rdcat(rdesc, &rsize, kbd_descriptor, माप(kbd_descriptor));
	पूर्ण

	अगर (djdev->reports_supported & STD_MOUSE) अणु
		dbg_hid("%s: sending a mouse descriptor, reports_supported: %llx\n",
			__func__, djdev->reports_supported);
		अगर (djdev->dj_receiver_dev->type == recvr_type_gaming_hidpp ||
		    djdev->dj_receiver_dev->type == recvr_type_mouse_only)
			rdcat(rdesc, &rsize, mse_high_res_descriptor,
			      माप(mse_high_res_descriptor));
		अन्यथा अगर (djdev->dj_receiver_dev->type == recvr_type_27mhz)
			rdcat(rdesc, &rsize, mse_27mhz_descriptor,
			      माप(mse_27mhz_descriptor));
		अन्यथा अगर (recvr_type_is_bluetooth(djdev->dj_receiver_dev->type))
			rdcat(rdesc, &rsize, mse_bluetooth_descriptor,
			      माप(mse_bluetooth_descriptor));
		अन्यथा
			rdcat(rdesc, &rsize, mse_descriptor,
			      माप(mse_descriptor));
	पूर्ण

	अगर (djdev->reports_supported & KBD_MOUSE) अणु
		dbg_hid("%s: sending a kbd-mouse descriptor, reports_supported: %llx\n",
			__func__, djdev->reports_supported);
		rdcat(rdesc, &rsize, mse5_bluetooth_descriptor,
		      माप(mse5_bluetooth_descriptor));
	पूर्ण

	अगर (djdev->reports_supported & MULTIMEDIA) अणु
		dbg_hid("%s: sending a multimedia report descriptor: %llx\n",
			__func__, djdev->reports_supported);
		rdcat(rdesc, &rsize, consumer_descriptor, माप(consumer_descriptor));
	पूर्ण

	अगर (djdev->reports_supported & POWER_KEYS) अणु
		dbg_hid("%s: sending a power keys report descriptor: %llx\n",
			__func__, djdev->reports_supported);
		rdcat(rdesc, &rsize, syscontrol_descriptor, माप(syscontrol_descriptor));
	पूर्ण

	अगर (djdev->reports_supported & MEDIA_CENTER) अणु
		dbg_hid("%s: sending a media center report descriptor: %llx\n",
			__func__, djdev->reports_supported);
		rdcat(rdesc, &rsize, media_descriptor, माप(media_descriptor));
	पूर्ण

	अगर (djdev->reports_supported & KBD_LEDS) अणु
		dbg_hid("%s: need to send kbd leds report descriptor: %llx\n",
			__func__, djdev->reports_supported);
	पूर्ण

	अगर (djdev->reports_supported & HIDPP) अणु
		dbg_hid("%s: sending a HID++ descriptor, reports_supported: %llx\n",
			__func__, djdev->reports_supported);
		rdcat(rdesc, &rsize, hidpp_descriptor,
		      माप(hidpp_descriptor));
	पूर्ण

	retval = hid_parse_report(hid, rdesc, rsize);
	kमुक्त(rdesc);

	वापस retval;
पूर्ण

अटल पूर्णांक logi_dj_ll_start(काष्ठा hid_device *hid)
अणु
	dbg_hid("%s\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम logi_dj_ll_stop(काष्ठा hid_device *hid)
अणु
	dbg_hid("%s\n", __func__);
पूर्ण


अटल काष्ठा hid_ll_driver logi_dj_ll_driver = अणु
	.parse = logi_dj_ll_parse,
	.start = logi_dj_ll_start,
	.stop = logi_dj_ll_stop,
	.खोलो = logi_dj_ll_खोलो,
	.बंद = logi_dj_ll_बंद,
	.raw_request = logi_dj_ll_raw_request,
पूर्ण;

अटल पूर्णांक logi_dj_dj_event(काष्ठा hid_device *hdev,
			     काष्ठा hid_report *report, u8 *data,
			     पूर्णांक size)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);
	काष्ठा dj_report *dj_report = (काष्ठा dj_report *) data;
	अचिन्हित दीर्घ flags;

	/*
	 * Here we receive all data coming from अगरace 2, there are 3 हालs:
	 *
	 * 1) Data is पूर्णांकended क्रम this driver i. e. data contains arrival,
	 * departure, etc notअगरications, in which हाल we queue them क्रम delayed
	 * processing by the work queue. We वापस 1 to hid-core as no further
	 * processing is required from it.
	 *
	 * 2) Data inक्रमms a connection change, अगर the change means rf link
	 * loss, then we must send a null report to the upper layer to discard
	 * potentially pressed keys that may be repeated क्रमever by the input
	 * layer. Return 1 to hid-core as no further processing is required.
	 *
	 * 3) Data is an actual input event from a paired DJ device in which
	 * हाल we क्रमward it to the correct hid device (via hid_input_report()
	 * ) and वापस 1 so hid-core करोes not anything अन्यथा with it.
	 */

	अगर ((dj_report->device_index < DJ_DEVICE_INDEX_MIN) ||
	    (dj_report->device_index > DJ_DEVICE_INDEX_MAX)) अणु
		/*
		 * Device index is wrong, bail out.
		 * This driver can ignore safely the receiver notअगरications,
		 * so ignore those reports too.
		 */
		अगर (dj_report->device_index != DJ_RECEIVER_INDEX)
			hid_err(hdev, "%s: invalid device index:%d\n",
				__func__, dj_report->device_index);
		वापस false;
	पूर्ण

	spin_lock_irqsave(&djrcv_dev->lock, flags);

	अगर (!djrcv_dev->paired_dj_devices[dj_report->device_index]) अणु
		/* received an event क्रम an unknown device, bail out */
		logi_dj_recv_queue_notअगरication(djrcv_dev, dj_report);
		जाओ out;
	पूर्ण

	चयन (dj_report->report_type) अणु
	हाल REPORT_TYPE_NOTIF_DEVICE_PAIRED:
		/* pairing notअगरications are handled above the चयन */
		अवरोध;
	हाल REPORT_TYPE_NOTIF_DEVICE_UNPAIRED:
		logi_dj_recv_queue_notअगरication(djrcv_dev, dj_report);
		अवरोध;
	हाल REPORT_TYPE_NOTIF_CONNECTION_STATUS:
		अगर (dj_report->report_params[CONNECTION_STATUS_PARAM_STATUS] ==
		    STATUS_LINKLOSS) अणु
			logi_dj_recv_क्रमward_null_report(djrcv_dev, dj_report);
		पूर्ण
		अवरोध;
	शेष:
		logi_dj_recv_क्रमward_dj(djrcv_dev, dj_report);
	पूर्ण

out:
	spin_unlock_irqrestore(&djrcv_dev->lock, flags);

	वापस true;
पूर्ण

अटल पूर्णांक logi_dj_hidpp_event(काष्ठा hid_device *hdev,
			     काष्ठा hid_report *report, u8 *data,
			     पूर्णांक size)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);
	काष्ठा hidpp_event *hidpp_report = (काष्ठा hidpp_event *) data;
	काष्ठा dj_device *dj_dev;
	अचिन्हित दीर्घ flags;
	u8 device_index = hidpp_report->device_index;

	अगर (device_index == HIDPP_RECEIVER_INDEX) अणु
		/* special हाल were the device wants to know its unअगरying
		 * name */
		अगर (size == HIDPP_REPORT_LONG_LENGTH &&
		    !स_भेद(data, unअगरying_pairing_answer,
			    माप(unअगरying_pairing_answer)))
			device_index = (data[4] & 0x0F) + 1;
		अन्यथा
			वापस false;
	पूर्ण

	/*
	 * Data is from the HID++ collection, in this हाल, we क्रमward the
	 * data to the corresponding child dj device and वापस 0 to hid-core
	 * so he data also goes to the hidraw device of the receiver. This
	 * allows a user space application to implement the full HID++ routing
	 * via the receiver.
	 */

	अगर ((device_index < DJ_DEVICE_INDEX_MIN) ||
	    (device_index > DJ_DEVICE_INDEX_MAX)) अणु
		/*
		 * Device index is wrong, bail out.
		 * This driver can ignore safely the receiver notअगरications,
		 * so ignore those reports too.
		 */
		hid_err(hdev, "%s: invalid device index:%d\n", __func__,
			hidpp_report->device_index);
		वापस false;
	पूर्ण

	spin_lock_irqsave(&djrcv_dev->lock, flags);

	dj_dev = djrcv_dev->paired_dj_devices[device_index];

	/*
	 * With 27 MHz receivers, we करो not get an explicit unpair event,
	 * हटाओ the old device अगर the user has paired a *dअगरferent* device.
	 */
	अगर (djrcv_dev->type == recvr_type_27mhz && dj_dev &&
	    hidpp_report->sub_id == REPORT_TYPE_NOTIF_DEVICE_CONNECTED &&
	    hidpp_report->params[HIDPP_PARAM_PROTO_TYPE] == 0x02 &&
	    hidpp_report->params[HIDPP_PARAM_27MHZ_DEVID] !=
						dj_dev->hdev->product) अणु
		काष्ठा dj_workitem workitem = अणु
			.device_index = hidpp_report->device_index,
			.type = WORKITEM_TYPE_UNPAIRED,
		पूर्ण;
		kfअगरo_in(&djrcv_dev->notअगर_fअगरo, &workitem, माप(workitem));
		/* logi_hidpp_recv_queue_notअगर will queue the work */
		dj_dev = शून्य;
	पूर्ण

	अगर (dj_dev) अणु
		logi_dj_recv_क्रमward_report(dj_dev, data, size);
	पूर्ण अन्यथा अणु
		अगर (hidpp_report->sub_id == REPORT_TYPE_NOTIF_DEVICE_CONNECTED)
			logi_hidpp_recv_queue_notअगर(hdev, hidpp_report);
		अन्यथा
			logi_dj_recv_queue_unknown_work(djrcv_dev);
	पूर्ण

	spin_unlock_irqrestore(&djrcv_dev->lock, flags);

	वापस false;
पूर्ण

अटल पूर्णांक logi_dj_raw_event(काष्ठा hid_device *hdev,
			     काष्ठा hid_report *report, u8 *data,
			     पूर्णांक size)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);
	dbg_hid("%s, size:%d\n", __func__, size);

	अगर (!djrcv_dev)
		वापस 0;

	अगर (!hdev->report_क्रमागत[HID_INPUT_REPORT].numbered) अणु

		अगर (djrcv_dev->unnumbered_application == HID_GD_KEYBOARD) अणु
			/*
			 * For the keyboard, we can reuse the same report by
			 * using the second byte which is स्थिरant in the USB
			 * HID report descriptor.
			 */
			data[1] = data[0];
			data[0] = REPORT_TYPE_KEYBOARD;

			logi_dj_recv_क्रमward_input_report(hdev, data, size);

			/* restore previous state */
			data[0] = data[1];
			data[1] = 0;
		पूर्ण
		/*
		 * Mouse-only receivers send unnumbered mouse data. The 27 MHz
		 * receiver uses 6 byte packets, the nano receiver 8 bytes.
		 */
		अगर (djrcv_dev->unnumbered_application == HID_GD_MOUSE &&
		    size <= 8) अणु
			u8 mouse_report[9];

			/* Prepend report id */
			mouse_report[0] = REPORT_TYPE_MOUSE;
			स_नकल(mouse_report + 1, data, size);
			logi_dj_recv_क्रमward_input_report(hdev, mouse_report,
							  size + 1);
		पूर्ण

		वापस false;
	पूर्ण

	चयन (data[0]) अणु
	हाल REPORT_ID_DJ_SHORT:
		अगर (size != DJREPORT_SHORT_LENGTH) अणु
			hid_err(hdev, "Short DJ report bad size (%d)", size);
			वापस false;
		पूर्ण
		वापस logi_dj_dj_event(hdev, report, data, size);
	हाल REPORT_ID_DJ_LONG:
		अगर (size != DJREPORT_LONG_LENGTH) अणु
			hid_err(hdev, "Long DJ report bad size (%d)", size);
			वापस false;
		पूर्ण
		वापस logi_dj_dj_event(hdev, report, data, size);
	हाल REPORT_ID_HIDPP_SHORT:
		अगर (size != HIDPP_REPORT_SHORT_LENGTH) अणु
			hid_err(hdev, "Short HID++ report bad size (%d)", size);
			वापस false;
		पूर्ण
		वापस logi_dj_hidpp_event(hdev, report, data, size);
	हाल REPORT_ID_HIDPP_LONG:
		अगर (size != HIDPP_REPORT_LONG_LENGTH) अणु
			hid_err(hdev, "Long HID++ report bad size (%d)", size);
			वापस false;
		पूर्ण
		वापस logi_dj_hidpp_event(hdev, report, data, size);
	पूर्ण

	logi_dj_recv_क्रमward_input_report(hdev, data, size);

	वापस false;
पूर्ण

अटल पूर्णांक logi_dj_probe(काष्ठा hid_device *hdev,
			 स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;
	काष्ठा hid_report *rep;
	काष्ठा dj_receiver_dev *djrcv_dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	अचिन्हित पूर्णांक no_dj_पूर्णांकerfaces = 0;
	bool has_hidpp = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	/*
	 * Call to usbhid to fetch the HID descriptors of the current
	 * पूर्णांकerface subsequently call to the hid/hid-core to parse the
	 * fetched descriptors.
	 */
	retval = hid_parse(hdev);
	अगर (retval) अणु
		hid_err(hdev, "%s: parse failed\n", __func__);
		वापस retval;
	पूर्ण

	/*
	 * Some KVMs add an extra पूर्णांकerface क्रम e.g. mouse emulation. If we
	 * treat these as logitech-dj पूर्णांकerfaces then this causes input events
	 * reported through this extra पूर्णांकerface to not be reported correctly.
	 * To aव्योम this, we treat these as generic-hid devices.
	 */
	चयन (id->driver_data) अणु
	हाल recvr_type_dj:		no_dj_पूर्णांकerfaces = 3; अवरोध;
	हाल recvr_type_hidpp:		no_dj_पूर्णांकerfaces = 2; अवरोध;
	हाल recvr_type_gaming_hidpp:	no_dj_पूर्णांकerfaces = 3; अवरोध;
	हाल recvr_type_mouse_only:	no_dj_पूर्णांकerfaces = 2; अवरोध;
	हाल recvr_type_27mhz:		no_dj_पूर्णांकerfaces = 2; अवरोध;
	हाल recvr_type_bluetooth:	no_dj_पूर्णांकerfaces = 2; अवरोध;
	हाल recvr_type_dinovo:		no_dj_पूर्णांकerfaces = 2; अवरोध;
	पूर्ण
	अगर (hid_is_using_ll_driver(hdev, &usb_hid_driver)) अणु
		पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
		अगर (पूर्णांकf && पूर्णांकf->altsetting->desc.bInterfaceNumber >=
							no_dj_पूर्णांकerfaces) अणु
			hdev->quirks |= HID_QUIRK_INPUT_PER_APP;
			वापस hid_hw_start(hdev, HID_CONNECT_DEFAULT);
		पूर्ण
	पूर्ण

	rep_क्रमागत = &hdev->report_क्रमागत[HID_INPUT_REPORT];

	/* no input reports, bail out */
	अगर (list_empty(&rep_क्रमागत->report_list))
		वापस -ENODEV;

	/*
	 * Check क्रम the HID++ application.
	 * Note: we should theoretically check क्रम HID++ and DJ
	 * collections, but this will करो.
	 */
	list_क्रम_each_entry(rep, &rep_क्रमागत->report_list, list) अणु
		अगर (rep->application == 0xff000001)
			has_hidpp = true;
	पूर्ण

	/*
	 * Ignore पूर्णांकerfaces without DJ/HID++ collection, they will not carry
	 * any data, करोnt create any hid_device क्रम them.
	 */
	अगर (!has_hidpp && id->driver_data == recvr_type_dj)
		वापस -ENODEV;

	/* get the current application attached to the node */
	rep = list_first_entry(&rep_क्रमागत->report_list, काष्ठा hid_report, list);
	djrcv_dev = dj_get_receiver_dev(hdev, id->driver_data,
					rep->application, has_hidpp);
	अगर (!djrcv_dev) अणु
		hid_err(hdev, "%s: dj_get_receiver_dev failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	अगर (!rep_क्रमागत->numbered)
		djrcv_dev->unnumbered_application = rep->application;

	/* Starts the usb device and connects to upper पूर्णांकerfaces hiddev and
	 * hidraw */
	retval = hid_hw_start(hdev, HID_CONNECT_HIDRAW|HID_CONNECT_HIDDEV);
	अगर (retval) अणु
		hid_err(hdev, "%s: hid_hw_start returned error\n", __func__);
		जाओ hid_hw_start_fail;
	पूर्ण

	अगर (has_hidpp) अणु
		retval = logi_dj_recv_चयन_to_dj_mode(djrcv_dev, 0);
		अगर (retval < 0) अणु
			hid_err(hdev, "%s: logi_dj_recv_switch_to_dj_mode returned error:%d\n",
				__func__, retval);
			जाओ चयन_to_dj_mode_fail;
		पूर्ण
	पूर्ण

	/* This is enabling the polling urb on the IN endpoपूर्णांक */
	retval = hid_hw_खोलो(hdev);
	अगर (retval < 0) अणु
		hid_err(hdev, "%s: hid_hw_open returned error:%d\n",
			__func__, retval);
		जाओ llखोलो_failed;
	पूर्ण

	/* Allow incoming packets to arrive: */
	hid_device_io_start(hdev);

	अगर (has_hidpp) अणु
		spin_lock_irqsave(&djrcv_dev->lock, flags);
		djrcv_dev->पढ़ोy = true;
		spin_unlock_irqrestore(&djrcv_dev->lock, flags);
		retval = logi_dj_recv_query_paired_devices(djrcv_dev);
		अगर (retval < 0) अणु
			hid_err(hdev, "%s: logi_dj_recv_query_paired_devices error:%d\n",
				__func__, retval);
			/*
			 * This can happen with a KVM, let the probe succeed,
			 * logi_dj_recv_queue_unknown_work will retry later.
			 */
		पूर्ण
	पूर्ण

	वापस 0;

llखोलो_failed:
चयन_to_dj_mode_fail:
	hid_hw_stop(hdev);

hid_hw_start_fail:
	dj_put_receiver_dev(hdev);
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक logi_dj_reset_resume(काष्ठा hid_device *hdev)
अणु
	पूर्णांक retval;
	काष्ठा dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);

	अगर (!djrcv_dev || djrcv_dev->hidpp != hdev)
		वापस 0;

	retval = logi_dj_recv_चयन_to_dj_mode(djrcv_dev, 0);
	अगर (retval < 0) अणु
		hid_err(hdev, "%s: logi_dj_recv_switch_to_dj_mode returned error:%d\n",
			__func__, retval);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम logi_dj_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा dj_receiver_dev *djrcv_dev = hid_get_drvdata(hdev);
	काष्ठा dj_device *dj_dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	dbg_hid("%s\n", __func__);

	अगर (!djrcv_dev)
		वापस hid_hw_stop(hdev);

	/*
	 * This ensures that अगर the work माला_लो requeued from another
	 * पूर्णांकerface of the same receiver it will be a no-op.
	 */
	spin_lock_irqsave(&djrcv_dev->lock, flags);
	djrcv_dev->पढ़ोy = false;
	spin_unlock_irqrestore(&djrcv_dev->lock, flags);

	cancel_work_sync(&djrcv_dev->work);

	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);

	/*
	 * For proper operation we need access to all पूर्णांकerfaces, so we destroy
	 * the paired devices when we're unbound from any पूर्णांकerface.
	 *
	 * Note we may still be bound to other पूर्णांकerfaces, sharing the same
	 * djrcv_dev, so we need locking here.
	 */
	क्रम (i = 0; i < (DJ_MAX_PAIRED_DEVICES + DJ_DEVICE_INDEX_MIN); i++) अणु
		spin_lock_irqsave(&djrcv_dev->lock, flags);
		dj_dev = djrcv_dev->paired_dj_devices[i];
		djrcv_dev->paired_dj_devices[i] = शून्य;
		spin_unlock_irqrestore(&djrcv_dev->lock, flags);
		अगर (dj_dev != शून्य) अणु
			hid_destroy_device(dj_dev->hdev);
			kमुक्त(dj_dev);
		पूर्ण
	पूर्ण

	dj_put_receiver_dev(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id logi_dj_receivers[] = अणु
	अणु /* Logitech unअगरying receiver (0xc52b) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_LOGITECH_UNIFYING_RECEIVER),
	 .driver_data = recvr_type_djपूर्ण,
	अणु /* Logitech unअगरying receiver (0xc532) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_LOGITECH_UNIFYING_RECEIVER_2),
	 .driver_data = recvr_type_djपूर्ण,

	अणु /* Logitech Nano mouse only receiver (0xc52f) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
			 USB_DEVICE_ID_LOGITECH_न_अंकO_RECEIVER),
	 .driver_data = recvr_type_mouse_onlyपूर्ण,
	अणु /* Logitech Nano (non DJ) receiver (0xc534) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
			 USB_DEVICE_ID_LOGITECH_न_अंकO_RECEIVER_2),
	 .driver_data = recvr_type_hidppपूर्ण,

	अणु /* Logitech G700(s) receiver (0xc531) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
			 USB_DEVICE_ID_LOGITECH_G700_RECEIVER),
	 .driver_data = recvr_type_gaming_hidppपूर्ण,
	अणु /* Logitech G602 receiver (0xc537) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		0xc537),
	 .driver_data = recvr_type_gaming_hidppपूर्ण,
	अणु /* Logitech lightspeed receiver (0xc539) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_LOGITECH_न_अंकO_RECEIVER_LIGHTSPEED_1),
	 .driver_data = recvr_type_gaming_hidppपूर्ण,
	अणु /* Logitech घातerplay receiver (0xc53a) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_LOGITECH_न_अंकO_RECEIVER_POWERPLAY),
	 .driver_data = recvr_type_gaming_hidppपूर्ण,
	अणु /* Logitech lightspeed receiver (0xc53f) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_LOGITECH_न_अंकO_RECEIVER_LIGHTSPEED_1_1),
	 .driver_data = recvr_type_gaming_hidppपूर्ण,

	अणु /* Logitech 27 MHz HID++ 1.0 receiver (0xc513) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_MX3000_RECEIVER),
	 .driver_data = recvr_type_27mhzपूर्ण,
	अणु /* Logitech 27 MHz HID++ 1.0 receiver (0xc517) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_S510_RECEIVER_2),
	 .driver_data = recvr_type_27mhzपूर्ण,
	अणु /* Logitech 27 MHz HID++ 1.0 mouse-only receiver (0xc51b) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_LOGITECH_27MHZ_MOUSE_RECEIVER),
	 .driver_data = recvr_type_27mhzपूर्ण,

	अणु /* Logitech MX5000 HID++ / bluetooth receiver keyboard पूर्णांकf. (0xc70e) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_MX5000_RECEIVER_KBD_DEV),
	 .driver_data = recvr_type_bluetoothपूर्ण,
	अणु /* Logitech MX5000 HID++ / bluetooth receiver mouse पूर्णांकf. (0xc70a) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_MX5000_RECEIVER_MOUSE_DEV),
	 .driver_data = recvr_type_bluetoothपूर्ण,
	अणु /* Logitech MX5500 HID++ / bluetooth receiver keyboard पूर्णांकf. (0xc71b) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_MX5500_RECEIVER_KBD_DEV),
	 .driver_data = recvr_type_bluetoothपूर्ण,
	अणु /* Logitech MX5500 HID++ / bluetooth receiver mouse पूर्णांकf. (0xc71c) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_MX5500_RECEIVER_MOUSE_DEV),
	 .driver_data = recvr_type_bluetoothपूर्ण,

	अणु /* Logitech Dinovo Edge HID++ / bluetooth receiver keyboard पूर्णांकf. (0xc713) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_DINOVO_EDGE_RECEIVER_KBD_DEV),
	 .driver_data = recvr_type_dinovoपूर्ण,
	अणु /* Logitech Dinovo Edge HID++ / bluetooth receiver mouse पूर्णांकf. (0xc714) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_DINOVO_EDGE_RECEIVER_MOUSE_DEV),
	 .driver_data = recvr_type_dinovoपूर्ण,
	अणु /* Logitech DiNovo Mini HID++ / bluetooth receiver mouse पूर्णांकf. (0xc71e) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_DINOVO_MINI_RECEIVER_KBD_DEV),
	 .driver_data = recvr_type_dinovoपूर्ण,
	अणु /* Logitech DiNovo Mini HID++ / bluetooth receiver keyboard पूर्णांकf. (0xc71f) */
	  HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_DINOVO_MINI_RECEIVER_MOUSE_DEV),
	 .driver_data = recvr_type_dinovoपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, logi_dj_receivers);

अटल काष्ठा hid_driver logi_djreceiver_driver = अणु
	.name = "logitech-djreceiver",
	.id_table = logi_dj_receivers,
	.probe = logi_dj_probe,
	.हटाओ = logi_dj_हटाओ,
	.raw_event = logi_dj_raw_event,
#अगर_घोषित CONFIG_PM
	.reset_resume = logi_dj_reset_resume,
#पूर्ण_अगर
पूर्ण;

module_hid_driver(logi_djreceiver_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Logitech");
MODULE_AUTHOR("Nestor Lopez Casado");
MODULE_AUTHOR("nlopezcasad@logitech.com");
