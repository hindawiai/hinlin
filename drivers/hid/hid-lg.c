<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some logitech "special" devices
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2008 Jiri Slaby
 *  Copyright (c) 2010 Hendrik Iben
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/usb.h>
#समावेश <linux/रुको.h>

#समावेश "usbhid/usbhid.h"
#समावेश "hid-ids.h"
#समावेश "hid-lg.h"
#समावेश "hid-lg4ff.h"

#घोषणा LG_RDESC		0x001
#घोषणा LG_BAD_RELATIVE_KEYS	0x002
#घोषणा LG_DUPLICATE_USAGES	0x004
#घोषणा LG_EXPANDED_KEYMAP	0x010
#घोषणा LG_IGNORE_DOUBLED_WHEEL	0x020
#घोषणा LG_WIRELESS		0x040
#घोषणा LG_INVERT_HWHEEL	0x080
#घोषणा LG_NOGET		0x100
#घोषणा LG_FF			0x200
#घोषणा LG_FF2			0x400
#घोषणा LG_RDESC_REL_ABS	0x800
#घोषणा LG_FF3			0x1000
#घोषणा LG_FF4			0x2000

/* Size of the original descriptors of the Driving Force (and Pro) wheels */
#घोषणा DF_RDESC_ORIG_SIZE	130
#घोषणा DFP_RDESC_ORIG_SIZE	97
#घोषणा FV_RDESC_ORIG_SIZE	130
#घोषणा MOMO_RDESC_ORIG_SIZE	87
#घोषणा MOMO2_RDESC_ORIG_SIZE	87
#घोषणा FFG_RDESC_ORIG_SIZE	85
#घोषणा FG_RDESC_ORIG_SIZE	82

/* Fixed report descriptors क्रम Logitech Driving Force (and Pro)
 * wheel controllers
 *
 * The original descriptors hide the separate throttle and brake axes in
 * a custom venकरोr usage page, providing only a combined value as
 * GenericDesktop.Y.
 * These descriptors हटाओ the combined Y axis and instead report
 * separate throttle (Y) and brake (RZ).
 */
अटल __u8 df_rdesc_fixed[] = अणु
0x05, 0x01,         /*  Usage Page (Desktop),                   */
0x09, 0x04,         /*  Usage (Joystick),                       */
0xA1, 0x01,         /*  Collection (Application),               */
0xA1, 0x02,         /*      Collection (Logical),               */
0x95, 0x01,         /*          Report Count (1),               */
0x75, 0x0A,         /*          Report Size (10),               */
0x14,               /*          Logical Minimum (0),            */
0x26, 0xFF, 0x03,   /*          Logical Maximum (1023),         */
0x34,               /*          Physical Minimum (0),           */
0x46, 0xFF, 0x03,   /*          Physical Maximum (1023),        */
0x09, 0x30,         /*          Usage (X),                      */
0x81, 0x02,         /*          Input (Variable),               */
0x95, 0x0C,         /*          Report Count (12),              */
0x75, 0x01,         /*          Report Size (1),                */
0x25, 0x01,         /*          Logical Maximum (1),            */
0x45, 0x01,         /*          Physical Maximum (1),           */
0x05, 0x09,         /*          Usage (Buttons),                */
0x19, 0x01,         /*          Usage Minimum (1),              */
0x29, 0x0c,         /*          Usage Maximum (12),             */
0x81, 0x02,         /*          Input (Variable),               */
0x95, 0x02,         /*          Report Count (2),               */
0x06, 0x00, 0xFF,   /*          Usage Page (Venकरोr: 65280),     */
0x09, 0x01,         /*          Usage (?: 1),                   */
0x81, 0x02,         /*          Input (Variable),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),         */
0x95, 0x01,         /*          Report Count (1),               */
0x75, 0x08,         /*          Report Size (8),                */
0x81, 0x02,         /*          Input (Variable),               */
0x25, 0x07,         /*          Logical Maximum (7),            */
0x46, 0x3B, 0x01,   /*          Physical Maximum (315),         */
0x75, 0x04,         /*          Report Size (4),                */
0x65, 0x14,         /*          Unit (Degrees),                 */
0x09, 0x39,         /*          Usage (Hat Switch),             */
0x81, 0x42,         /*          Input (Variable, Null State),   */
0x75, 0x01,         /*          Report Size (1),                */
0x95, 0x04,         /*          Report Count (4),               */
0x65, 0x00,         /*          Unit (none),                    */
0x06, 0x00, 0xFF,   /*          Usage Page (Venकरोr: 65280),     */
0x09, 0x01,         /*          Usage (?: 1),                   */
0x25, 0x01,         /*          Logical Maximum (1),            */
0x45, 0x01,         /*          Physical Maximum (1),           */
0x81, 0x02,         /*          Input (Variable),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x95, 0x01,         /*          Report Count (1),               */
0x75, 0x08,         /*          Report Size (8),                */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),         */
0x09, 0x31,         /*          Usage (Y),                      */
0x81, 0x02,         /*          Input (Variable),               */
0x09, 0x35,         /*          Usage (Rz),                     */
0x81, 0x02,         /*          Input (Variable),               */
0xC0,               /*      End Collection,                     */
0xA1, 0x02,         /*      Collection (Logical),               */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),         */
0x95, 0x07,         /*          Report Count (7),               */
0x75, 0x08,         /*          Report Size (8),                */
0x09, 0x03,         /*          Usage (?: 3),                   */
0x91, 0x02,         /*          Output (Variable),              */
0xC0,               /*      End Collection,                     */
0xC0                /*  End Collection                          */
पूर्ण;

अटल __u8 dfp_rdesc_fixed[] = अणु
0x05, 0x01,         /*  Usage Page (Desktop),                   */
0x09, 0x04,         /*  Usage (Joystick),                       */
0xA1, 0x01,         /*  Collection (Application),               */
0xA1, 0x02,         /*      Collection (Logical),               */
0x95, 0x01,         /*          Report Count (1),               */
0x75, 0x0E,         /*          Report Size (14),               */
0x14,               /*          Logical Minimum (0),            */
0x26, 0xFF, 0x3F,   /*          Logical Maximum (16383),        */
0x34,               /*          Physical Minimum (0),           */
0x46, 0xFF, 0x3F,   /*          Physical Maximum (16383),       */
0x09, 0x30,         /*          Usage (X),                      */
0x81, 0x02,         /*          Input (Variable),               */
0x95, 0x0E,         /*          Report Count (14),              */
0x75, 0x01,         /*          Report Size (1),                */
0x25, 0x01,         /*          Logical Maximum (1),            */
0x45, 0x01,         /*          Physical Maximum (1),           */
0x05, 0x09,         /*          Usage Page (Button),            */
0x19, 0x01,         /*          Usage Minimum (01h),            */
0x29, 0x0E,         /*          Usage Maximum (0Eh),            */
0x81, 0x02,         /*          Input (Variable),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x95, 0x01,         /*          Report Count (1),               */
0x75, 0x04,         /*          Report Size (4),                */
0x25, 0x07,         /*          Logical Maximum (7),            */
0x46, 0x3B, 0x01,   /*          Physical Maximum (315),         */
0x65, 0x14,         /*          Unit (Degrees),                 */
0x09, 0x39,         /*          Usage (Hat Switch),             */
0x81, 0x42,         /*          Input (Variable, Nullstate),    */
0x65, 0x00,         /*          Unit,                           */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),         */
0x75, 0x08,         /*          Report Size (8),                */
0x81, 0x01,         /*          Input (Constant),               */
0x09, 0x31,         /*          Usage (Y),                      */
0x81, 0x02,         /*          Input (Variable),               */
0x09, 0x35,         /*          Usage (Rz),                     */
0x81, 0x02,         /*          Input (Variable),               */
0x81, 0x01,         /*          Input (Constant),               */
0xC0,               /*      End Collection,                     */
0xA1, 0x02,         /*      Collection (Logical),               */
0x09, 0x02,         /*          Usage (02h),                    */
0x95, 0x07,         /*          Report Count (7),               */
0x91, 0x02,         /*          Output (Variable),              */
0xC0,               /*      End Collection,                     */
0xC0                /*  End Collection                          */
पूर्ण;

अटल __u8 fv_rdesc_fixed[] = अणु
0x05, 0x01,         /*  Usage Page (Desktop),                   */
0x09, 0x04,         /*  Usage (Joystick),                       */
0xA1, 0x01,         /*  Collection (Application),               */
0xA1, 0x02,         /*      Collection (Logical),               */
0x95, 0x01,         /*          Report Count (1),               */
0x75, 0x0A,         /*          Report Size (10),               */
0x15, 0x00,         /*          Logical Minimum (0),            */
0x26, 0xFF, 0x03,   /*          Logical Maximum (1023),         */
0x35, 0x00,         /*          Physical Minimum (0),           */
0x46, 0xFF, 0x03,   /*          Physical Maximum (1023),        */
0x09, 0x30,         /*          Usage (X),                      */
0x81, 0x02,         /*          Input (Variable),               */
0x95, 0x0C,         /*          Report Count (12),              */
0x75, 0x01,         /*          Report Size (1),                */
0x25, 0x01,         /*          Logical Maximum (1),            */
0x45, 0x01,         /*          Physical Maximum (1),           */
0x05, 0x09,         /*          Usage Page (Button),            */
0x19, 0x01,         /*          Usage Minimum (01h),            */
0x29, 0x0C,         /*          Usage Maximum (0Ch),            */
0x81, 0x02,         /*          Input (Variable),               */
0x95, 0x02,         /*          Report Count (2),               */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),             */
0x09, 0x01,         /*          Usage (01h),                    */
0x81, 0x02,         /*          Input (Variable),               */
0x09, 0x02,         /*          Usage (02h),                    */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),         */
0x95, 0x01,         /*          Report Count (1),               */
0x75, 0x08,         /*          Report Size (8),                */
0x81, 0x02,         /*          Input (Variable),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x25, 0x07,         /*          Logical Maximum (7),            */
0x46, 0x3B, 0x01,   /*          Physical Maximum (315),         */
0x75, 0x04,         /*          Report Size (4),                */
0x65, 0x14,         /*          Unit (Degrees),                 */
0x09, 0x39,         /*          Usage (Hat Switch),             */
0x81, 0x42,         /*          Input (Variable, Null State),   */
0x75, 0x01,         /*          Report Size (1),                */
0x95, 0x04,         /*          Report Count (4),               */
0x65, 0x00,         /*          Unit,                           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),             */
0x09, 0x01,         /*          Usage (01h),                    */
0x25, 0x01,         /*          Logical Maximum (1),            */
0x45, 0x01,         /*          Physical Maximum (1),           */
0x81, 0x02,         /*          Input (Variable),               */
0x05, 0x01,         /*          Usage Page (Desktop),           */
0x95, 0x01,         /*          Report Count (1),               */
0x75, 0x08,         /*          Report Size (8),                */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),         */
0x09, 0x31,         /*          Usage (Y),                      */
0x81, 0x02,         /*          Input (Variable),               */
0x09, 0x32,         /*          Usage (Z),                      */
0x81, 0x02,         /*          Input (Variable),               */
0xC0,               /*      End Collection,                     */
0xA1, 0x02,         /*      Collection (Logical),               */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),          */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),         */
0x95, 0x07,         /*          Report Count (7),               */
0x75, 0x08,         /*          Report Size (8),                */
0x09, 0x03,         /*          Usage (03h),                    */
0x91, 0x02,         /*          Output (Variable),              */
0xC0,               /*      End Collection,                     */
0xC0                /*  End Collection                          */
पूर्ण;

अटल __u8 momo_rdesc_fixed[] = अणु
0x05, 0x01,         /*  Usage Page (Desktop),               */
0x09, 0x04,         /*  Usage (Joystick),                   */
0xA1, 0x01,         /*  Collection (Application),           */
0xA1, 0x02,         /*      Collection (Logical),           */
0x95, 0x01,         /*          Report Count (1),           */
0x75, 0x0A,         /*          Report Size (10),           */
0x15, 0x00,         /*          Logical Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Logical Maximum (1023),     */
0x35, 0x00,         /*          Physical Minimum (0),       */
0x46, 0xFF, 0x03,   /*          Physical Maximum (1023),    */
0x09, 0x30,         /*          Usage (X),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x95, 0x08,         /*          Report Count (8),           */
0x75, 0x01,         /*          Report Size (1),            */
0x25, 0x01,         /*          Logical Maximum (1),        */
0x45, 0x01,         /*          Physical Maximum (1),       */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x08,         /*          Usage Maximum (08h),        */
0x81, 0x02,         /*          Input (Variable),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x75, 0x0E,         /*          Report Size (14),           */
0x95, 0x01,         /*          Report Count (1),           */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),     */
0x09, 0x00,         /*          Usage (00h),                */
0x81, 0x02,         /*          Input (Variable),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x75, 0x08,         /*          Report Size (8),            */
0x09, 0x31,         /*          Usage (Y),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x09, 0x32,         /*          Usage (Z),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x01,         /*          Usage (01h),                */
0x81, 0x02,         /*          Input (Variable),           */
0xC0,               /*      End Collection,                 */
0xA1, 0x02,         /*      Collection (Logical),           */
0x09, 0x02,         /*          Usage (02h),                */
0x95, 0x07,         /*          Report Count (7),           */
0x91, 0x02,         /*          Output (Variable),          */
0xC0,               /*      End Collection,                 */
0xC0                /*  End Collection                      */
पूर्ण;

अटल __u8 momo2_rdesc_fixed[] = अणु
0x05, 0x01,         /*  Usage Page (Desktop),               */
0x09, 0x04,         /*  Usage (Joystick),                   */
0xA1, 0x01,         /*  Collection (Application),           */
0xA1, 0x02,         /*      Collection (Logical),           */
0x95, 0x01,         /*          Report Count (1),           */
0x75, 0x0A,         /*          Report Size (10),           */
0x15, 0x00,         /*          Logical Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Logical Maximum (1023),     */
0x35, 0x00,         /*          Physical Minimum (0),       */
0x46, 0xFF, 0x03,   /*          Physical Maximum (1023),    */
0x09, 0x30,         /*          Usage (X),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x95, 0x0A,         /*          Report Count (10),          */
0x75, 0x01,         /*          Report Size (1),            */
0x25, 0x01,         /*          Logical Maximum (1),        */
0x45, 0x01,         /*          Physical Maximum (1),       */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x0A,         /*          Usage Maximum (0Ah),        */
0x81, 0x02,         /*          Input (Variable),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x00,         /*          Usage (00h),                */
0x95, 0x04,         /*          Report Count (4),           */
0x81, 0x02,         /*          Input (Variable),           */
0x95, 0x01,         /*          Report Count (1),           */
0x75, 0x08,         /*          Report Size (8),            */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),     */
0x09, 0x01,         /*          Usage (01h),                */
0x81, 0x02,         /*          Input (Variable),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x09, 0x31,         /*          Usage (Y),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x09, 0x32,         /*          Usage (Z),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x00,         /*          Usage (00h),                */
0x81, 0x02,         /*          Input (Variable),           */
0xC0,               /*      End Collection,                 */
0xA1, 0x02,         /*      Collection (Logical),           */
0x09, 0x02,         /*          Usage (02h),                */
0x95, 0x07,         /*          Report Count (7),           */
0x91, 0x02,         /*          Output (Variable),          */
0xC0,               /*      End Collection,                 */
0xC0                /*  End Collection                      */
पूर्ण;

अटल __u8 ffg_rdesc_fixed[] = अणु
0x05, 0x01,         /*  Usage Page (Desktop),               */
0x09, 0x04,         /*  Usage (Joystik),                    */
0xA1, 0x01,         /*  Collection (Application),           */
0xA1, 0x02,         /*      Collection (Logical),           */
0x95, 0x01,         /*          Report Count (1),           */
0x75, 0x0A,         /*          Report Size (10),           */
0x15, 0x00,         /*          Logical Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Logical Maximum (1023),     */
0x35, 0x00,         /*          Physical Minimum (0),       */
0x46, 0xFF, 0x03,   /*          Physical Maximum (1023),    */
0x09, 0x30,         /*          Usage (X),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x95, 0x06,         /*          Report Count (6),           */
0x75, 0x01,         /*          Report Size (1),            */
0x25, 0x01,         /*          Logical Maximum (1),        */
0x45, 0x01,         /*          Physical Maximum (1),       */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x06,         /*          Usage Maximum (06h),        */
0x81, 0x02,         /*          Input (Variable),           */
0x95, 0x01,         /*          Report Count (1),           */
0x75, 0x08,         /*          Report Size (8),            */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),     */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x01,         /*          Usage (01h),                */
0x81, 0x02,         /*          Input (Variable),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x81, 0x01,         /*          Input (Constant),           */
0x09, 0x31,         /*          Usage (Y),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x09, 0x32,         /*          Usage (Z),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x01,         /*          Usage (01h),                */
0x81, 0x02,         /*          Input (Variable),           */
0xC0,               /*      End Collection,                 */
0xA1, 0x02,         /*      Collection (Logical),           */
0x09, 0x02,         /*          Usage (02h),                */
0x95, 0x07,         /*          Report Count (7),           */
0x91, 0x02,         /*          Output (Variable),          */
0xC0,               /*      End Collection,                 */
0xC0                /*  End Collection                      */
पूर्ण;

अटल __u8 fg_rdesc_fixed[] = अणु
0x05, 0x01,         /*  Usage Page (Desktop),               */
0x09, 0x04,         /*  Usage (Joystik),                    */
0xA1, 0x01,         /*  Collection (Application),           */
0xA1, 0x02,         /*      Collection (Logical),           */
0x15, 0x00,         /*          Logical Minimum (0),        */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
0x35, 0x00,         /*          Physical Minimum (0),       */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),     */
0x75, 0x08,         /*          Report Size (8),            */
0x95, 0x01,         /*          Report Count (1),           */
0x09, 0x30,         /*          Usage (X),                  */
0x81, 0x02,         /*          Input (Variable),           */
0xA4,               /*  Push,                               */
0x25, 0x01,         /*          Logical Maximum (1),        */
0x45, 0x01,         /*          Physical Maximum (1),       */
0x75, 0x01,         /*          Report Size (1),            */
0x95, 0x02,         /*          Report Count (2),           */
0x81, 0x01,         /*          Input (Constant),           */
0x95, 0x06,         /*          Report Count (6),           */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x06,         /*          Usage Maximum (06h),        */
0x81, 0x02,         /*          Input (Variable),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0xB4,               /*  Pop,                                */
0x81, 0x02,         /*          Input (Constant),           */
0x09, 0x31,         /*          Usage (Y),                  */
0x81, 0x02,         /*          Input (Variable),           */
0x09, 0x32,         /*          Usage (Z),                  */
0x81, 0x02,         /*          Input (Variable),           */
0xC0,               /*      End Collection,                 */
0xA1, 0x02,         /*      Collection (Logical),           */
0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
0x46, 0xFF, 0x00,   /*          Physical Maximum (255),     */
0x75, 0x08,         /*          Report Size (8),            */
0x95, 0x04,         /*          Report Count (4),           */
0x09, 0x02,         /*          Usage (02h),                */
0xB1, 0x02,         /*          Feature (Variable),         */
0xC0,               /*      End Collection,                 */
0xC0                /*  End Collection,                     */
पूर्ण;

/*
 * Certain Logitech keyboards send in report #3 keys which are far
 * above the logical maximum described in descriptor. This extends
 * the original value of 0x28c of logical maximum to 0x104d
 */
अटल __u8 *lg_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा lg_drv_data *drv_data = hid_get_drvdata(hdev);

	अगर ((drv_data->quirks & LG_RDESC) && *rsize >= 91 && rdesc[83] == 0x26 &&
			rdesc[84] == 0x8c && rdesc[85] == 0x02) अणु
		hid_info(hdev,
			 "fixing up Logitech keyboard report descriptor\n");
		rdesc[84] = rdesc[89] = 0x4d;
		rdesc[85] = rdesc[90] = 0x10;
	पूर्ण
	अगर ((drv_data->quirks & LG_RDESC_REL_ABS) && *rsize >= 51 &&
			rdesc[32] == 0x81 && rdesc[33] == 0x06 &&
			rdesc[49] == 0x81 && rdesc[50] == 0x06) अणु
		hid_info(hdev,
			 "fixing up rel/abs in Logitech report descriptor\n");
		rdesc[33] = rdesc[50] = 0x02;
	पूर्ण

	चयन (hdev->product) अणु

	हाल USB_DEVICE_ID_LOGITECH_WINGMAN_FG:
		अगर (*rsize == FG_RDESC_ORIG_SIZE) अणु
			hid_info(hdev,
				"fixing up Logitech Wingman Formula GP report descriptor\n");
			rdesc = fg_rdesc_fixed;
			*rsize = माप(fg_rdesc_fixed);
		पूर्ण अन्यथा अणु
			hid_info(hdev,
				"rdesc size test failed for formula gp\n");
		पूर्ण
		अवरोध;


	हाल USB_DEVICE_ID_LOGITECH_WINGMAN_FFG:
		अगर (*rsize == FFG_RDESC_ORIG_SIZE) अणु
			hid_info(hdev,
				"fixing up Logitech Wingman Formula Force GP report descriptor\n");
			rdesc = ffg_rdesc_fixed;
			*rsize = माप(ffg_rdesc_fixed);
		पूर्ण
		अवरोध;

	/* Several wheels report as this id when operating in emulation mode. */
	हाल USB_DEVICE_ID_LOGITECH_WHEEL:
		अगर (*rsize == DF_RDESC_ORIG_SIZE) अणु
			hid_info(hdev,
				"fixing up Logitech Driving Force report descriptor\n");
			rdesc = df_rdesc_fixed;
			*rsize = माप(df_rdesc_fixed);
		पूर्ण
		अवरोध;

	हाल USB_DEVICE_ID_LOGITECH_MOMO_WHEEL:
		अगर (*rsize == MOMO_RDESC_ORIG_SIZE) अणु
			hid_info(hdev,
				"fixing up Logitech Momo Force (Red) report descriptor\n");
			rdesc = momo_rdesc_fixed;
			*rsize = माप(momo_rdesc_fixed);
		पूर्ण
		अवरोध;

	हाल USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2:
		अगर (*rsize == MOMO2_RDESC_ORIG_SIZE) अणु
			hid_info(hdev,
				"fixing up Logitech Momo Racing Force (Black) report descriptor\n");
			rdesc = momo2_rdesc_fixed;
			*rsize = माप(momo2_rdesc_fixed);
		पूर्ण
		अवरोध;

	हाल USB_DEVICE_ID_LOGITECH_VIBRATION_WHEEL:
		अगर (*rsize == FV_RDESC_ORIG_SIZE) अणु
			hid_info(hdev,
				"fixing up Logitech Formula Vibration report descriptor\n");
			rdesc = fv_rdesc_fixed;
			*rsize = माप(fv_rdesc_fixed);
		पूर्ण
		अवरोध;

	हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
		अगर (*rsize == DFP_RDESC_ORIG_SIZE) अणु
			hid_info(hdev,
				"fixing up Logitech Driving Force Pro report descriptor\n");
			rdesc = dfp_rdesc_fixed;
			*rsize = माप(dfp_rdesc_fixed);
		पूर्ण
		अवरोध;

	हाल USB_DEVICE_ID_LOGITECH_WII_WHEEL:
		अगर (*rsize >= 101 && rdesc[41] == 0x95 && rdesc[42] == 0x0B &&
				rdesc[47] == 0x05 && rdesc[48] == 0x09) अणु
			hid_info(hdev, "fixing up Logitech Speed Force Wireless report descriptor\n");
			rdesc[41] = 0x05;
			rdesc[42] = 0x09;
			rdesc[47] = 0x95;
			rdesc[48] = 0x0B;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस rdesc;
पूर्ण

#घोषणा lg_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
		EV_KEY, (c))

अटल पूर्णांक lg_ultrax_remote_mapping(काष्ठा hid_input *hi,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_LOGIVENDOR)
		वापस 0;

	set_bit(EV_REP, hi->input->evbit);
	चयन (usage->hid & HID_USAGE) अणु
	/* Reported on Logitech Ultra X Media Remote */
	हाल 0x004: lg_map_key_clear(KEY_AGAIN);	अवरोध;
	हाल 0x00d: lg_map_key_clear(KEY_HOME);		अवरोध;
	हाल 0x024: lg_map_key_clear(KEY_SHUFFLE);	अवरोध;
	हाल 0x025: lg_map_key_clear(KEY_TV);		अवरोध;
	हाल 0x026: lg_map_key_clear(KEY_MENU);		अवरोध;
	हाल 0x031: lg_map_key_clear(KEY_AUDIO);	अवरोध;
	हाल 0x032: lg_map_key_clear(KEY_TEXT);		अवरोध;
	हाल 0x033: lg_map_key_clear(KEY_LAST);		अवरोध;
	हाल 0x047: lg_map_key_clear(KEY_MP3);		अवरोध;
	हाल 0x048: lg_map_key_clear(KEY_DVD);		अवरोध;
	हाल 0x049: lg_map_key_clear(KEY_MEDIA);	अवरोध;
	हाल 0x04a: lg_map_key_clear(KEY_VIDEO);	अवरोध;
	हाल 0x04b: lg_map_key_clear(KEY_ANGLE);	अवरोध;
	हाल 0x04c: lg_map_key_clear(KEY_LANGUAGE);	अवरोध;
	हाल 0x04d: lg_map_key_clear(KEY_SUBTITLE);	अवरोध;
	हाल 0x051: lg_map_key_clear(KEY_RED);		अवरोध;
	हाल 0x052: lg_map_key_clear(KEY_CLOSE);	अवरोध;

	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक lg_wireless_mapping(काष्ठा hid_input *hi, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMER)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	हाल 0x1001: lg_map_key_clear(KEY_MESSENGER);		अवरोध;
	हाल 0x1003: lg_map_key_clear(KEY_SOUND);		अवरोध;
	हाल 0x1004: lg_map_key_clear(KEY_VIDEO);		अवरोध;
	हाल 0x1005: lg_map_key_clear(KEY_AUDIO);		अवरोध;
	हाल 0x100a: lg_map_key_clear(KEY_DOCUMENTS);		अवरोध;
	/* The following two entries are Playlist 1 and 2 on the MX3200 */
	हाल 0x100f: lg_map_key_clear(KEY_FN_1);		अवरोध;
	हाल 0x1010: lg_map_key_clear(KEY_FN_2);		अवरोध;
	हाल 0x1011: lg_map_key_clear(KEY_PREVIOUSSONG);	अवरोध;
	हाल 0x1012: lg_map_key_clear(KEY_NEXTSONG);		अवरोध;
	हाल 0x1013: lg_map_key_clear(KEY_CAMERA);		अवरोध;
	हाल 0x1014: lg_map_key_clear(KEY_MESSENGER);		अवरोध;
	हाल 0x1015: lg_map_key_clear(KEY_RECORD);		अवरोध;
	हाल 0x1016: lg_map_key_clear(KEY_PLAYER);		अवरोध;
	हाल 0x1017: lg_map_key_clear(KEY_EJECTCD);		अवरोध;
	हाल 0x1018: lg_map_key_clear(KEY_MEDIA);		अवरोध;
	हाल 0x1019: lg_map_key_clear(KEY_PROG1);		अवरोध;
	हाल 0x101a: lg_map_key_clear(KEY_PROG2);		अवरोध;
	हाल 0x101b: lg_map_key_clear(KEY_PROG3);		अवरोध;
	हाल 0x101c: lg_map_key_clear(KEY_CYCLEWINDOWS);	अवरोध;
	हाल 0x101f: lg_map_key_clear(KEY_ZOOMIN);		अवरोध;
	हाल 0x1020: lg_map_key_clear(KEY_ZOOMOUT);		अवरोध;
	हाल 0x1021: lg_map_key_clear(KEY_ZOOMRESET);		अवरोध;
	हाल 0x1023: lg_map_key_clear(KEY_CLOSE);		अवरोध;
	हाल 0x1027: lg_map_key_clear(KEY_MENU);		अवरोध;
	/* this one is marked as 'Rotate' */
	हाल 0x1028: lg_map_key_clear(KEY_ANGLE);		अवरोध;
	हाल 0x1029: lg_map_key_clear(KEY_SHUFFLE);		अवरोध;
	हाल 0x102a: lg_map_key_clear(KEY_BACK);		अवरोध;
	हाल 0x102b: lg_map_key_clear(KEY_CYCLEWINDOWS);	अवरोध;
	हाल 0x102d: lg_map_key_clear(KEY_WWW);			अवरोध;
	/* The following two are 'Start/answer call' and 'End/reject call'
	   on the MX3200 */
	हाल 0x1031: lg_map_key_clear(KEY_OK);			अवरोध;
	हाल 0x1032: lg_map_key_clear(KEY_CANCEL);		अवरोध;
	हाल 0x1041: lg_map_key_clear(KEY_BATTERY);		अवरोध;
	हाल 0x1042: lg_map_key_clear(KEY_WORDPROCESSOR);	अवरोध;
	हाल 0x1043: lg_map_key_clear(KEY_SPREADSHEET);		अवरोध;
	हाल 0x1044: lg_map_key_clear(KEY_PRESENTATION);	अवरोध;
	हाल 0x1045: lg_map_key_clear(KEY_UNDO);		अवरोध;
	हाल 0x1046: lg_map_key_clear(KEY_REDO);		अवरोध;
	हाल 0x1047: lg_map_key_clear(KEY_PRINT);		अवरोध;
	हाल 0x1048: lg_map_key_clear(KEY_SAVE);		अवरोध;
	हाल 0x1049: lg_map_key_clear(KEY_PROG1);		अवरोध;
	हाल 0x104a: lg_map_key_clear(KEY_PROG2);		अवरोध;
	हाल 0x104b: lg_map_key_clear(KEY_PROG3);		अवरोध;
	हाल 0x104c: lg_map_key_clear(KEY_PROG4);		अवरोध;

	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक lg_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	/* extended mapping क्रम certain Logitech hardware (Logitech cordless
	   desktop LX500) */
	अटल स्थिर u8 e_keymap[] = अणु
		  0,216,  0,213,175,156,  0,  0,  0,  0,
		144,  0,  0,  0,  0,  0,  0,  0,  0,212,
		174,167,152,161,112,  0,  0,  0,154,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,183,184,185,186,187,
		188,189,190,191,192,193,194,  0,  0,  0
	पूर्ण;
	काष्ठा lg_drv_data *drv_data = hid_get_drvdata(hdev);
	अचिन्हित पूर्णांक hid = usage->hid;

	अगर (hdev->product == USB_DEVICE_ID_LOGITECH_RECEIVER &&
			lg_ultrax_remote_mapping(hi, usage, bit, max))
		वापस 1;

	अगर ((drv_data->quirks & LG_WIRELESS) && lg_wireless_mapping(hi, usage, bit, max))
		वापस 1;

	अगर ((hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
		वापस 0;

	hid &= HID_USAGE;

	/* Special handling क्रम Logitech Cordless Desktop */
	अगर (field->application == HID_GD_MOUSE) अणु
		अगर ((drv_data->quirks & LG_IGNORE_DOUBLED_WHEEL) &&
				(hid == 7 || hid == 8))
			वापस -1;
	पूर्ण अन्यथा अणु
		अगर ((drv_data->quirks & LG_EXPANDED_KEYMAP) &&
				hid < ARRAY_SIZE(e_keymap) &&
				e_keymap[hid] != 0) अणु
			hid_map_usage(hi, usage, bit, max, EV_KEY,
					e_keymap[hid]);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lg_input_mapped(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा lg_drv_data *drv_data = hid_get_drvdata(hdev);

	अगर ((drv_data->quirks & LG_BAD_RELATIVE_KEYS) && usage->type == EV_KEY &&
			(field->flags & HID_MAIN_ITEM_RELATIVE))
		field->flags &= ~HID_MAIN_ITEM_RELATIVE;

	अगर ((drv_data->quirks & LG_DUPLICATE_USAGES) && (usage->type == EV_KEY ||
			 usage->type == EV_REL || usage->type == EV_ABS))
		clear_bit(usage->code, *bit);

	/* Ensure that Logitech wheels are not given a शेष fuzz/flat value */
	अगर (usage->type == EV_ABS && (usage->code == ABS_X ||
			usage->code == ABS_Y || usage->code == ABS_Z ||
			usage->code == ABS_RZ)) अणु
		चयन (hdev->product) अणु
		हाल USB_DEVICE_ID_LOGITECH_G29_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_WINGMAN_FG:
		हाल USB_DEVICE_ID_LOGITECH_WINGMAN_FFG:
		हाल USB_DEVICE_ID_LOGITECH_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_MOMO_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_DFP_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_G25_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_DFGT_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_G27_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_WII_WHEEL:
		हाल USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2:
		हाल USB_DEVICE_ID_LOGITECH_VIBRATION_WHEEL:
			field->application = HID_GD_MULTIAXIS;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lg_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा lg_drv_data *drv_data = hid_get_drvdata(hdev);

	अगर ((drv_data->quirks & LG_INVERT_HWHEEL) && usage->code == REL_HWHEEL) अणु
		input_event(field->hidinput->input, usage->type, usage->code,
				-value);
		वापस 1;
	पूर्ण
	अगर (drv_data->quirks & LG_FF4) अणु
		वापस lg4ff_adjust_input_event(hdev, field, usage, value, drv_data);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lg_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *rd, पूर्णांक size)
अणु
	काष्ठा lg_drv_data *drv_data = hid_get_drvdata(hdev);

	अगर (drv_data->quirks & LG_FF4)
		वापस lg4ff_raw_event(hdev, report, rd, size, drv_data);

	वापस 0;
पूर्ण

अटल पूर्णांक lg_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा usb_पूर्णांकerface *अगरace = to_usb_पूर्णांकerface(hdev->dev.parent);
	__u8 अगरace_num = अगरace->cur_altsetting->desc.bInterfaceNumber;
	अचिन्हित पूर्णांक connect_mask = HID_CONNECT_DEFAULT;
	काष्ठा lg_drv_data *drv_data;
	पूर्णांक ret;

	/* G29 only work with the 1st पूर्णांकerface */
	अगर ((hdev->product == USB_DEVICE_ID_LOGITECH_G29_WHEEL) &&
	    (अगरace_num != 0)) अणु
		dbg_hid("%s: ignoring ifnum %d\n", __func__, अगरace_num);
		वापस -ENODEV;
	पूर्ण

	drv_data = kzalloc(माप(काष्ठा lg_drv_data), GFP_KERNEL);
	अगर (!drv_data) अणु
		hid_err(hdev, "Insufficient memory, cannot allocate driver data\n");
		वापस -ENOMEM;
	पूर्ण
	drv_data->quirks = id->driver_data;

	hid_set_drvdata(hdev, (व्योम *)drv_data);

	अगर (drv_data->quirks & LG_NOGET)
		hdev->quirks |= HID_QUIRK_NOGET;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (drv_data->quirks & (LG_FF | LG_FF2 | LG_FF3 | LG_FF4))
		connect_mask &= ~HID_CONNECT_FF;

	ret = hid_hw_start(hdev, connect_mask);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	/* Setup wireless link with Logitech Wii wheel */
	अगर (hdev->product == USB_DEVICE_ID_LOGITECH_WII_WHEEL) अणु
		अटल स्थिर अचिन्हित अक्षर cbuf[] = अणु
			0x00, 0xAF,  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		पूर्ण;
		u8 *buf = kmemdup(cbuf, माप(cbuf), GFP_KERNEL);

		अगर (!buf) अणु
			ret = -ENOMEM;
			जाओ err_stop;
		पूर्ण

		ret = hid_hw_raw_request(hdev, buf[0], buf, माप(cbuf),
					HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
		अगर (ret >= 0) अणु
			/* insert a little delay of 10 jअगरfies ~ 40ms */
			रुको_queue_head_t रुको;
			init_रुकोqueue_head (&रुको);
			रुको_event_पूर्णांकerruptible_समयout(रुको, 0,
							 msecs_to_jअगरfies(40));

			/* Select अक्रमom Address */
			buf[1] = 0xB2;
			get_अक्रमom_bytes(&buf[2], 2);

			ret = hid_hw_raw_request(hdev, buf[0], buf, माप(cbuf),
					HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
		पूर्ण
		kमुक्त(buf);
	पूर्ण

	अगर (drv_data->quirks & LG_FF)
		ret = lgff_init(hdev);
	अन्यथा अगर (drv_data->quirks & LG_FF2)
		ret = lg2ff_init(hdev);
	अन्यथा अगर (drv_data->quirks & LG_FF3)
		ret = lg3ff_init(hdev);
	अन्यथा अगर (drv_data->quirks & LG_FF4)
		ret = lg4ff_init(hdev);

	अगर (ret)
		जाओ err_stop;

	वापस 0;

err_stop:
	hid_hw_stop(hdev);
err_मुक्त:
	kमुक्त(drv_data);
	वापस ret;
पूर्ण

अटल व्योम lg_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा lg_drv_data *drv_data = hid_get_drvdata(hdev);
	अगर (drv_data->quirks & LG_FF4)
		lg4ff_deinit(hdev);
	hid_hw_stop(hdev);
	kमुक्त(drv_data);
पूर्ण

अटल स्थिर काष्ठा hid_device_id lg_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_S510_RECEIVER),
		.driver_data = LG_RDESC | LG_WIRELESS पूर्ण,

	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_RECEIVER),
		.driver_data = LG_BAD_RELATIVE_KEYS पूर्ण,

	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_DINOVO_DESKTOP),
		.driver_data = LG_DUPLICATE_USAGES पूर्ण,

	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_ELITE_KBD),
		.driver_data = LG_IGNORE_DOUBLED_WHEEL | LG_EXPANDED_KEYMAP पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_CORDLESS_DESKTOP_LX500),
		.driver_data = LG_IGNORE_DOUBLED_WHEEL | LG_EXPANDED_KEYMAP पूर्ण,

	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_EXTREME_3D),
		.driver_data = LG_NOGET पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_DUAL_ACTION),
		.driver_data = LG_NOGET पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_WHEEL),
		.driver_data = LG_NOGET | LG_FF4 पूर्ण,

	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_RUMBLEPAD_CORD),
		.driver_data = LG_FF2 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_RUMBLEPAD),
		.driver_data = LG_FF पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_RUMBLEPAD2_2),
		.driver_data = LG_FF पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_G29_WHEEL),
		.driver_data = LG_FF4 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_WINGMAN_F3D),
		.driver_data = LG_FF पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_FORCE3D_PRO),
		.driver_data = LG_FF पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_MOMO_WHEEL),
		.driver_data = LG_NOGET | LG_FF4 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_MOMO_WHEEL2),
		.driver_data = LG_FF4 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_VIBRATION_WHEEL),
		.driver_data = LG_FF2 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_G25_WHEEL),
		.driver_data = LG_FF4 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_DFGT_WHEEL),
		.driver_data = LG_FF4 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_G27_WHEEL),
		.driver_data = LG_FF4 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_DFP_WHEEL),
		.driver_data = LG_NOGET | LG_FF4 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_WII_WHEEL),
		.driver_data = LG_FF4 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_WINGMAN_FG),
		.driver_data = LG_NOGET पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_WINGMAN_FFG),
		.driver_data = LG_NOGET | LG_FF4 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_RUMBLEPAD2),
		.driver_data = LG_NOGET | LG_FF2 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_LOGITECH_FLIGHT_SYSTEM_G940),
		.driver_data = LG_FF3 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_SPACENAVIGATOR),
		.driver_data = LG_RDESC_REL_ABS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH, USB_DEVICE_ID_SPACETRAVELLER),
		.driver_data = LG_RDESC_REL_ABS पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, lg_devices);

अटल काष्ठा hid_driver lg_driver = अणु
	.name = "logitech",
	.id_table = lg_devices,
	.report_fixup = lg_report_fixup,
	.input_mapping = lg_input_mapping,
	.input_mapped = lg_input_mapped,
	.event = lg_event,
	.raw_event = lg_raw_event,
	.probe = lg_probe,
	.हटाओ = lg_हटाओ,
पूर्ण;
module_hid_driver(lg_driver);

#अगर_घोषित CONFIG_LOGIWHEELS_FF
पूर्णांक lg4ff_no_स्वतःचयन = 0;
module_param_named(lg4ff_no_स्वतःचयन, lg4ff_no_स्वतःचयन, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(lg4ff_no_स्वतःचयन, "Do not switch multimode wheels to their native mode automatically");
#पूर्ण_अगर

MODULE_LICENSE("GPL");
