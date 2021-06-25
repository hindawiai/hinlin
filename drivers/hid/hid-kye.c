<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Kye/Genius devices not fully compliant with HID standard
 *
 *  Copyright (c) 2009 Jiri Kosina
 *  Copyright (c) 2009 Tomas Hanak
 *  Copyright (c) 2012 Nikolai Kondrashov
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

/* Original EasyPen i405X report descriptor size */
#घोषणा EASYPEN_I405X_RDESC_ORIG_SIZE	476

/* Fixed EasyPen i405X report descriptor */
अटल __u8 easypen_i405x_rdesc_fixed[] = अणु
	0x06, 0x00, 0xFF, /*  Usage Page (FF00h),             */
	0x09, 0x01,       /*  Usage (01h),                    */
	0xA1, 0x01,       /*  Collection (Application),       */
	0x85, 0x05,       /*    Report ID (5),                */
	0x09, 0x01,       /*    Usage (01h),                  */
	0x15, 0x80,       /*    Logical Minimum (-128),       */
	0x25, 0x7F,       /*    Logical Maximum (127),        */
	0x75, 0x08,       /*    Report Size (8),              */
	0x95, 0x07,       /*    Report Count (7),             */
	0xB1, 0x02,       /*    Feature (Variable),           */
	0xC0,             /*  End Collection,                 */
	0x05, 0x0D,       /*  Usage Page (Digitizer),         */
	0x09, 0x02,       /*  Usage (Pen),                    */
	0xA1, 0x01,       /*  Collection (Application),       */
	0x85, 0x10,       /*    Report ID (16),               */
	0x09, 0x20,       /*    Usage (Stylus),               */
	0xA0,             /*    Collection (Physical),        */
	0x14,             /*      Logical Minimum (0),        */
	0x25, 0x01,       /*      Logical Maximum (1),        */
	0x75, 0x01,       /*      Report Size (1),            */
	0x09, 0x42,       /*      Usage (Tip Switch),         */
	0x09, 0x44,       /*      Usage (Barrel Switch),      */
	0x09, 0x46,       /*      Usage (Tablet Pick),        */
	0x95, 0x03,       /*      Report Count (3),           */
	0x81, 0x02,       /*      Input (Variable),           */
	0x95, 0x04,       /*      Report Count (4),           */
	0x81, 0x03,       /*      Input (Constant, Variable), */
	0x09, 0x32,       /*      Usage (In Range),           */
	0x95, 0x01,       /*      Report Count (1),           */
	0x81, 0x02,       /*      Input (Variable),           */
	0x75, 0x10,       /*      Report Size (16),           */
	0x95, 0x01,       /*      Report Count (1),           */
	0xA4,             /*      Push,                       */
	0x05, 0x01,       /*      Usage Page (Desktop),       */
	0x55, 0xFD,       /*      Unit Exponent (-3),         */
	0x65, 0x13,       /*      Unit (Inch),                */
	0x34,             /*      Physical Minimum (0),       */
	0x09, 0x30,       /*      Usage (X),                  */
	0x46, 0x7C, 0x15, /*      Physical Maximum (5500),    */
	0x26, 0x00, 0x37, /*      Logical Maximum (14080),    */
	0x81, 0x02,       /*      Input (Variable),           */
	0x09, 0x31,       /*      Usage (Y),                  */
	0x46, 0xA0, 0x0F, /*      Physical Maximum (4000),    */
	0x26, 0x00, 0x28, /*      Logical Maximum (10240),    */
	0x81, 0x02,       /*      Input (Variable),           */
	0xB4,             /*      Pop,                        */
	0x09, 0x30,       /*      Usage (Tip Pressure),       */
	0x26, 0xFF, 0x03, /*      Logical Maximum (1023),     */
	0x81, 0x02,       /*      Input (Variable),           */
	0xC0,             /*    End Collection,               */
	0xC0              /*  End Collection                  */
पूर्ण;

/* Original MousePen i608X report descriptor size */
#घोषणा MOUSEPEN_I608X_RDESC_ORIG_SIZE	476

/* Fixed MousePen i608X report descriptor */
अटल __u8 mousepen_i608x_rdesc_fixed[] = अणु
	0x06, 0x00, 0xFF, /*  Usage Page (FF00h),             */
	0x09, 0x01,       /*  Usage (01h),                    */
	0xA1, 0x01,       /*  Collection (Application),       */
	0x85, 0x05,       /*    Report ID (5),                */
	0x09, 0x01,       /*    Usage (01h),                  */
	0x15, 0x80,       /*    Logical Minimum (-128),       */
	0x25, 0x7F,       /*    Logical Maximum (127),        */
	0x75, 0x08,       /*    Report Size (8),              */
	0x95, 0x07,       /*    Report Count (7),             */
	0xB1, 0x02,       /*    Feature (Variable),           */
	0xC0,             /*  End Collection,                 */
	0x05, 0x0D,       /*  Usage Page (Digitizer),         */
	0x09, 0x02,       /*  Usage (Pen),                    */
	0xA1, 0x01,       /*  Collection (Application),       */
	0x85, 0x10,       /*    Report ID (16),               */
	0x09, 0x20,       /*    Usage (Stylus),               */
	0xA0,             /*    Collection (Physical),        */
	0x14,             /*      Logical Minimum (0),        */
	0x25, 0x01,       /*      Logical Maximum (1),        */
	0x75, 0x01,       /*      Report Size (1),            */
	0x09, 0x42,       /*      Usage (Tip Switch),         */
	0x09, 0x44,       /*      Usage (Barrel Switch),      */
	0x09, 0x46,       /*      Usage (Tablet Pick),        */
	0x95, 0x03,       /*      Report Count (3),           */
	0x81, 0x02,       /*      Input (Variable),           */
	0x95, 0x04,       /*      Report Count (4),           */
	0x81, 0x03,       /*      Input (Constant, Variable), */
	0x09, 0x32,       /*      Usage (In Range),           */
	0x95, 0x01,       /*      Report Count (1),           */
	0x81, 0x02,       /*      Input (Variable),           */
	0x75, 0x10,       /*      Report Size (16),           */
	0x95, 0x01,       /*      Report Count (1),           */
	0xA4,             /*      Push,                       */
	0x05, 0x01,       /*      Usage Page (Desktop),       */
	0x55, 0xFD,       /*      Unit Exponent (-3),         */
	0x65, 0x13,       /*      Unit (Inch),                */
	0x34,             /*      Physical Minimum (0),       */
	0x09, 0x30,       /*      Usage (X),                  */
	0x46, 0x40, 0x1F, /*      Physical Maximum (8000),    */
	0x26, 0x00, 0x50, /*      Logical Maximum (20480),    */
	0x81, 0x02,       /*      Input (Variable),           */
	0x09, 0x31,       /*      Usage (Y),                  */
	0x46, 0x70, 0x17, /*      Physical Maximum (6000),    */
	0x26, 0x00, 0x3C, /*      Logical Maximum (15360),    */
	0x81, 0x02,       /*      Input (Variable),           */
	0xB4,             /*      Pop,                        */
	0x09, 0x30,       /*      Usage (Tip Pressure),       */
	0x26, 0xFF, 0x03, /*      Logical Maximum (1023),     */
	0x81, 0x02,       /*      Input (Variable),           */
	0xC0,             /*    End Collection,               */
	0xC0,             /*  End Collection,                 */
	0x05, 0x01,       /*  Usage Page (Desktop),           */
	0x09, 0x02,       /*  Usage (Mouse),                  */
	0xA1, 0x01,       /*  Collection (Application),       */
	0x85, 0x11,       /*    Report ID (17),               */
	0x09, 0x01,       /*    Usage (Poपूर्णांकer),              */
	0xA0,             /*    Collection (Physical),        */
	0x14,             /*      Logical Minimum (0),        */
	0xA4,             /*      Push,                       */
	0x05, 0x09,       /*      Usage Page (Button),        */
	0x75, 0x01,       /*      Report Size (1),            */
	0x19, 0x01,       /*      Usage Minimum (01h),        */
	0x29, 0x03,       /*      Usage Maximum (03h),        */
	0x25, 0x01,       /*      Logical Maximum (1),        */
	0x95, 0x03,       /*      Report Count (3),           */
	0x81, 0x02,       /*      Input (Variable),           */
	0x95, 0x05,       /*      Report Count (5),           */
	0x81, 0x01,       /*      Input (Constant),           */
	0xB4,             /*      Pop,                        */
	0x95, 0x01,       /*      Report Count (1),           */
	0xA4,             /*      Push,                       */
	0x55, 0xFD,       /*      Unit Exponent (-3),         */
	0x65, 0x13,       /*      Unit (Inch),                */
	0x34,             /*      Physical Minimum (0),       */
	0x75, 0x10,       /*      Report Size (16),           */
	0x09, 0x30,       /*      Usage (X),                  */
	0x46, 0x40, 0x1F, /*      Physical Maximum (8000),    */
	0x26, 0x00, 0x50, /*      Logical Maximum (20480),    */
	0x81, 0x02,       /*      Input (Variable),           */
	0x09, 0x31,       /*      Usage (Y),                  */
	0x46, 0x70, 0x17, /*      Physical Maximum (6000),    */
	0x26, 0x00, 0x3C, /*      Logical Maximum (15360),    */
	0x81, 0x02,       /*      Input (Variable),           */
	0xB4,             /*      Pop,                        */
	0x75, 0x08,       /*      Report Size (8),            */
	0x09, 0x38,       /*      Usage (Wheel),              */
	0x15, 0xFF,       /*      Logical Minimum (-1),       */
	0x25, 0x01,       /*      Logical Maximum (1),        */
	0x81, 0x06,       /*      Input (Variable, Relative), */
	0x81, 0x01,       /*      Input (Constant),           */
	0xC0,             /*    End Collection,               */
	0xC0              /*  End Collection                  */
पूर्ण;

/* Original MousePen i608X v2 report descriptor size */
#घोषणा MOUSEPEN_I608X_V2_RDESC_ORIG_SIZE	482

/* Fixed MousePen i608X v2 report descriptor */
अटल __u8 mousepen_i608x_v2_rdesc_fixed[] = अणु
	0x06, 0x00, 0xFF,             /*  Usage Page (FF00h),             */
	0x09, 0x01,                   /*  Usage (01h),                    */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x05,                   /*    Report ID (5),                */
	0x09, 0x01,                   /*    Usage (01h),                  */
	0x15, 0x80,                   /*    Logical Minimum (-128),       */
	0x25, 0x7F,                   /*    Logical Maximum (127),        */
	0x75, 0x08,                   /*    Report Size (8),              */
	0x95, 0x07,                   /*    Report Count (7),             */
	0xB1, 0x02,                   /*    Feature (Variable),           */
	0xC0,                         /*  End Collection,                 */
	0x05, 0x0D,                   /*  Usage Page (Digitizer),         */
	0x09, 0x02,                   /*  Usage (Pen),                    */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x10,                   /*    Report ID (16),               */
	0x09, 0x20,                   /*    Usage (Stylus),               */
	0xA0,                         /*    Collection (Physical),        */
	0x14,                         /*      Logical Minimum (0),        */
	0x25, 0x01,                   /*      Logical Maximum (1),        */
	0x75, 0x01,                   /*      Report Size (1),            */
	0x09, 0x42,                   /*      Usage (Tip Switch),         */
	0x09, 0x44,                   /*      Usage (Barrel Switch),      */
	0x09, 0x46,                   /*      Usage (Tablet Pick),        */
	0x95, 0x03,                   /*      Report Count (3),           */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x95, 0x04,                   /*      Report Count (4),           */
	0x81, 0x03,                   /*      Input (Constant, Variable), */
	0x09, 0x32,                   /*      Usage (In Range),           */
	0x95, 0x01,                   /*      Report Count (1),           */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x75, 0x10,                   /*      Report Size (16),           */
	0x95, 0x01,                   /*      Report Count (1),           */
	0xA4,                         /*      Push,                       */
	0x05, 0x01,                   /*      Usage Page (Desktop),       */
	0x55, 0xFD,                   /*      Unit Exponent (-3),         */
	0x65, 0x13,                   /*      Unit (Inch),                */
	0x34,                         /*      Physical Minimum (0),       */
	0x09, 0x30,                   /*      Usage (X),                  */
	0x46, 0x40, 0x1F,             /*      Physical Maximum (8000),    */
	0x27, 0x00, 0xA0, 0x00, 0x00, /*      Logical Maximum (40960),    */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x09, 0x31,                   /*      Usage (Y),                  */
	0x46, 0x70, 0x17,             /*      Physical Maximum (6000),    */
	0x26, 0x00, 0x78,             /*      Logical Maximum (30720),    */
	0x81, 0x02,                   /*      Input (Variable),           */
	0xB4,                         /*      Pop,                        */
	0x09, 0x30,                   /*      Usage (Tip Pressure),       */
	0x26, 0xFF, 0x07,             /*      Logical Maximum (2047),     */
	0x81, 0x02,                   /*      Input (Variable),           */
	0xC0,                         /*    End Collection,               */
	0xC0,                         /*  End Collection,                 */
	0x05, 0x01,                   /*  Usage Page (Desktop),           */
	0x09, 0x02,                   /*  Usage (Mouse),                  */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x11,                   /*    Report ID (17),               */
	0x09, 0x01,                   /*    Usage (Poपूर्णांकer),              */
	0xA0,                         /*    Collection (Physical),        */
	0x14,                         /*      Logical Minimum (0),        */
	0xA4,                         /*      Push,                       */
	0x05, 0x09,                   /*      Usage Page (Button),        */
	0x75, 0x01,                   /*      Report Size (1),            */
	0x19, 0x01,                   /*      Usage Minimum (01h),        */
	0x29, 0x03,                   /*      Usage Maximum (03h),        */
	0x25, 0x01,                   /*      Logical Maximum (1),        */
	0x95, 0x03,                   /*      Report Count (3),           */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x95, 0x05,                   /*      Report Count (5),           */
	0x81, 0x01,                   /*      Input (Constant),           */
	0xB4,                         /*      Pop,                        */
	0x95, 0x01,                   /*      Report Count (1),           */
	0xA4,                         /*      Push,                       */
	0x55, 0xFD,                   /*      Unit Exponent (-3),         */
	0x65, 0x13,                   /*      Unit (Inch),                */
	0x34,                         /*      Physical Minimum (0),       */
	0x75, 0x10,                   /*      Report Size (16),           */
	0x09, 0x30,                   /*      Usage (X),                  */
	0x46, 0x40, 0x1F,             /*      Physical Maximum (8000),    */
	0x27, 0x00, 0xA0, 0x00, 0x00, /*      Logical Maximum (40960),    */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x09, 0x31,                   /*      Usage (Y),                  */
	0x46, 0x70, 0x17,             /*      Physical Maximum (6000),    */
	0x26, 0x00, 0x78,             /*      Logical Maximum (30720),    */
	0x81, 0x02,                   /*      Input (Variable),           */
	0xB4,                         /*      Pop,                        */
	0x75, 0x08,                   /*      Report Size (8),            */
	0x09, 0x38,                   /*      Usage (Wheel),              */
	0x15, 0xFF,                   /*      Logical Minimum (-1),       */
	0x25, 0x01,                   /*      Logical Maximum (1),        */
	0x81, 0x06,                   /*      Input (Variable, Relative), */
	0x81, 0x01,                   /*      Input (Constant),           */
	0xC0,                         /*    End Collection,               */
	0xC0                          /*  End Collection                  */
पूर्ण;

/* Original EasyPen M610X report descriptor size */
#घोषणा EASYPEN_M610X_RDESC_ORIG_SIZE	476

/* Fixed EasyPen M610X report descriptor */
अटल __u8 easypen_m610x_rdesc_fixed[] = अणु
	0x06, 0x00, 0xFF,             /*  Usage Page (FF00h),             */
	0x09, 0x01,                   /*  Usage (01h),                    */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x05,                   /*    Report ID (5),                */
	0x09, 0x01,                   /*    Usage (01h),                  */
	0x15, 0x80,                   /*    Logical Minimum (-128),       */
	0x25, 0x7F,                   /*    Logical Maximum (127),        */
	0x75, 0x08,                   /*    Report Size (8),              */
	0x95, 0x07,                   /*    Report Count (7),             */
	0xB1, 0x02,                   /*    Feature (Variable),           */
	0xC0,                         /*  End Collection,                 */
	0x05, 0x0D,                   /*  Usage Page (Digitizer),         */
	0x09, 0x02,                   /*  Usage (Pen),                    */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x10,                   /*    Report ID (16),               */
	0x09, 0x20,                   /*    Usage (Stylus),               */
	0xA0,                         /*    Collection (Physical),        */
	0x14,                         /*      Logical Minimum (0),        */
	0x25, 0x01,                   /*      Logical Maximum (1),        */
	0x75, 0x01,                   /*      Report Size (1),            */
	0x09, 0x42,                   /*      Usage (Tip Switch),         */
	0x09, 0x44,                   /*      Usage (Barrel Switch),      */
	0x09, 0x46,                   /*      Usage (Tablet Pick),        */
	0x95, 0x03,                   /*      Report Count (3),           */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x95, 0x04,                   /*      Report Count (4),           */
	0x81, 0x03,                   /*      Input (Constant, Variable), */
	0x09, 0x32,                   /*      Usage (In Range),           */
	0x95, 0x01,                   /*      Report Count (1),           */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x75, 0x10,                   /*      Report Size (16),           */
	0x95, 0x01,                   /*      Report Count (1),           */
	0xA4,                         /*      Push,                       */
	0x05, 0x01,                   /*      Usage Page (Desktop),       */
	0x55, 0xFD,                   /*      Unit Exponent (-3),         */
	0x65, 0x13,                   /*      Unit (Inch),                */
	0x34,                         /*      Physical Minimum (0),       */
	0x09, 0x30,                   /*      Usage (X),                  */
	0x46, 0x10, 0x27,             /*      Physical Maximum (10000),   */
	0x27, 0x00, 0xA0, 0x00, 0x00, /*      Logical Maximum (40960),    */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x09, 0x31,                   /*      Usage (Y),                  */
	0x46, 0x6A, 0x18,             /*      Physical Maximum (6250),    */
	0x26, 0x00, 0x64,             /*      Logical Maximum (25600),    */
	0x81, 0x02,                   /*      Input (Variable),           */
	0xB4,                         /*      Pop,                        */
	0x09, 0x30,                   /*      Usage (Tip Pressure),       */
	0x26, 0xFF, 0x03,             /*      Logical Maximum (1023),     */
	0x81, 0x02,                   /*      Input (Variable),           */
	0xC0,                         /*    End Collection,               */
	0xC0,                         /*  End Collection,                 */
	0x05, 0x0C,                   /*  Usage Page (Consumer),          */
	0x09, 0x01,                   /*  Usage (Consumer Control),       */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x12,                   /*    Report ID (18),               */
	0x14,                         /*    Logical Minimum (0),          */
	0x25, 0x01,                   /*    Logical Maximum (1),          */
	0x75, 0x01,                   /*    Report Size (1),              */
	0x95, 0x04,                   /*    Report Count (4),             */
	0x0A, 0x1A, 0x02,             /*    Usage (AC Unकरो),              */
	0x0A, 0x79, 0x02,             /*    Usage (AC Reकरो Or Repeat),    */
	0x0A, 0x2D, 0x02,             /*    Usage (AC Zoom In),           */
	0x0A, 0x2E, 0x02,             /*    Usage (AC Zoom Out),          */
	0x81, 0x02,                   /*    Input (Variable),             */
	0x95, 0x01,                   /*    Report Count (1),             */
	0x75, 0x14,                   /*    Report Size (20),             */
	0x81, 0x03,                   /*    Input (Constant, Variable),   */
	0x75, 0x20,                   /*    Report Size (32),             */
	0x81, 0x03,                   /*    Input (Constant, Variable),   */
	0xC0                          /*  End Collection                  */
पूर्ण;


/* Original PenSketch M912 report descriptor size */
#घोषणा PENSKETCH_M912_RDESC_ORIG_SIZE	482

/* Fixed PenSketch M912 report descriptor */
अटल __u8 pensketch_m912_rdesc_fixed[] = अणु
	0x05, 0x01,                   /*  Usage Page (Desktop),           */
	0x08,                         /*  Usage (00h),                    */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x05,                   /*    Report ID (5),                */
	0x06, 0x00, 0xFF,             /*    Usage Page (FF00h),           */
	0x09, 0x01,                   /*    Usage (01h),                  */
	0x15, 0x81,                   /*    Logical Minimum (-127),       */
	0x25, 0x7F,                   /*    Logical Maximum (127),        */
	0x75, 0x08,                   /*    Report Size (8),              */
	0x95, 0x07,                   /*    Report Count (7),             */
	0xB1, 0x02,                   /*    Feature (Variable),           */
	0xC0,                         /*  End Collection,                 */
	0x05, 0x0D,                   /*  Usage Page (Digitizer),         */
	0x09, 0x02,                   /*  Usage (Pen),                    */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x10,                   /*    Report ID (16),               */
	0x09, 0x20,                   /*    Usage (Stylus),               */
	0xA0,                         /*    Collection (Physical),        */
	0x09, 0x42,                   /*      Usage (Tip Switch),         */
	0x09, 0x44,                   /*      Usage (Barrel Switch),      */
	0x09, 0x46,                   /*      Usage (Tablet Pick),        */
	0x14,                         /*      Logical Minimum (0),        */
	0x25, 0x01,                   /*      Logical Maximum (1),        */
	0x75, 0x01,                   /*      Report Size (1),            */
	0x95, 0x03,                   /*      Report Count (3),           */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x95, 0x04,                   /*      Report Count (4),           */
	0x81, 0x03,                   /*      Input (Constant, Variable), */
	0x09, 0x32,                   /*      Usage (In Range),           */
	0x95, 0x01,                   /*      Report Count (1),           */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x75, 0x10,                   /*      Report Size (16),           */
	0x95, 0x01,                   /*      Report Count (1),           */
	0xA4,                         /*      Push,                       */
	0x05, 0x01,                   /*      Usage Page (Desktop),       */
	0x55, 0xFD,                   /*      Unit Exponent (-3),         */
	0x65, 0x13,                   /*      Unit (Inch),                */
	0x14,                         /*      Logical Minimum (0),        */
	0x34,                         /*      Physical Minimum (0),       */
	0x09, 0x30,                   /*      Usage (X),                  */
	0x27, 0x00, 0xF0, 0x00, 0x00, /*      Logical Maximum (61440),    */
	0x46, 0xE0, 0x2E,             /*      Physical Maximum (12000),   */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x09, 0x31,                   /*      Usage (Y),                  */
	0x27, 0x00, 0xB4, 0x00, 0x00, /*      Logical Maximum (46080),    */
	0x46, 0x28, 0x23,             /*      Physical Maximum (9000),    */
	0x81, 0x02,                   /*      Input (Variable),           */
	0xB4,                         /*      Pop,                        */
	0x09, 0x30,                   /*      Usage (Tip Pressure),       */
	0x14,                         /*      Logical Minimum (0),        */
	0x26, 0xFF, 0x07,             /*      Logical Maximum (2047),     */
	0x81, 0x02,                   /*      Input (Variable),           */
	0xC0,                         /*    End Collection,               */
	0xC0,                         /*  End Collection,                 */
	0x05, 0x0D,                   /*  Usage Page (Digitizer),         */
	0x09, 0x21,                   /*  Usage (Puck),                   */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x11,                   /*    Report ID (17),               */
	0x09, 0x21,                   /*    Usage (Puck),                 */
	0xA0,                         /*    Collection (Physical),        */
	0x05, 0x09,                   /*      Usage Page (Button),        */
	0x75, 0x01,                   /*      Report Size (1),            */
	0x19, 0x01,                   /*      Usage Minimum (01h),        */
	0x29, 0x03,                   /*      Usage Maximum (03h),        */
	0x14,                         /*      Logical Minimum (0),        */
	0x25, 0x01,                   /*      Logical Maximum (1),        */
	0x95, 0x03,                   /*      Report Count (3),           */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x95, 0x04,                   /*      Report Count (4),           */
	0x81, 0x01,                   /*      Input (Constant),           */
	0x95, 0x01,                   /*      Report Count (1),           */
	0x0B, 0x32, 0x00, 0x0D, 0x00, /*      Usage (Digitizer In Range), */
	0x14,                         /*      Logical Minimum (0),        */
	0x25, 0x01,                   /*      Logical Maximum (1),        */
	0x81, 0x02,                   /*      Input (Variable),           */
	0xA4,                         /*      Push,                       */
	0x05, 0x01,                   /*      Usage Page (Desktop),       */
	0x75, 0x10,                   /*      Report Size (16),           */
	0x95, 0x01,                   /*      Report Count (1),           */
	0x55, 0xFD,                   /*      Unit Exponent (-3),         */
	0x65, 0x13,                   /*      Unit (Inch),                */
	0x14,                         /*      Logical Minimum (0),        */
	0x34,                         /*      Physical Minimum (0),       */
	0x09, 0x30,                   /*      Usage (X),                  */
	0x27, 0x00, 0xF0, 0x00, 0x00, /*      Logical Maximum (61440),    */
	0x46, 0xE0, 0x2E,             /*      Physical Maximum (12000),   */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x09, 0x31,                   /*      Usage (Y),                  */
	0x27, 0x00, 0xB4, 0x00, 0x00, /*      Logical Maximum (46080),    */
	0x46, 0x28, 0x23,             /*      Physical Maximum (9000),    */
	0x81, 0x02,                   /*      Input (Variable),           */
	0x09, 0x38,                   /*      Usage (Wheel),              */
	0x75, 0x08,                   /*      Report Size (8),            */
	0x95, 0x01,                   /*      Report Count (1),           */
	0x15, 0xFF,                   /*      Logical Minimum (-1),       */
	0x25, 0x01,                   /*      Logical Maximum (1),        */
	0x34,                         /*      Physical Minimum (0),       */
	0x44,                         /*      Physical Maximum (0),       */
	0x81, 0x06,                   /*      Input (Variable, Relative), */
	0xB4,                         /*      Pop,                        */
	0xC0,                         /*    End Collection,               */
	0xC0,                         /*  End Collection,                 */
	0x05, 0x0C,                   /*  Usage Page (Consumer),          */
	0x09, 0x01,                   /*  Usage (Consumer Control),       */
	0xA1, 0x01,                   /*  Collection (Application),       */
	0x85, 0x12,                   /*    Report ID (18),               */
	0x14,                         /*    Logical Minimum (0),          */
	0x25, 0x01,                   /*    Logical Maximum (1),          */
	0x75, 0x01,                   /*    Report Size (1),              */
	0x95, 0x08,                   /*    Report Count (8),             */
	0x05, 0x0C,                   /*    Usage Page (Consumer),        */
	0x0A, 0x6A, 0x02,             /*    Usage (AC Delete),            */
	0x0A, 0x1A, 0x02,             /*    Usage (AC Unकरो),              */
	0x0A, 0x01, 0x02,             /*    Usage (AC New),               */
	0x0A, 0x2F, 0x02,             /*    Usage (AC Zoom),              */
	0x0A, 0x25, 0x02,             /*    Usage (AC Forward),           */
	0x0A, 0x24, 0x02,             /*    Usage (AC Back),              */
	0x0A, 0x2D, 0x02,             /*    Usage (AC Zoom In),           */
	0x0A, 0x2E, 0x02,             /*    Usage (AC Zoom Out),          */
	0x81, 0x02,                   /*    Input (Variable),             */
	0x95, 0x30,                   /*    Report Count (48),            */
	0x81, 0x03,                   /*    Input (Constant, Variable),   */
	0xC0                          /*  End Collection                  */
पूर्ण;

/* Original EasyPen M406XE report descriptor size */
#घोषणा EASYPEN_M406XE_RDESC_ORIG_SIZE	476

/* Fixed EasyPen M406XE  report descriptor */
अटल __u8 easypen_m406xe_rdesc_fixed[] = अणु
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x01,         /*  Usage (01h),                        */
	0xA1, 0x01,         /*  Collection (Application),           */
	0x85, 0x05,         /*      Report ID (5),                  */
	0x09, 0x01,         /*      Usage (01h),                    */
	0x15, 0x80,         /*      Logical Minimum (-128),         */
	0x25, 0x7F,         /*      Logical Maximum (127),          */
	0x75, 0x08,         /*      Report Size (8),                */
	0x95, 0x07,         /*      Report Count (7),               */
	0xB1, 0x02,         /*      Feature (Variable),             */
	0xC0,               /*  End Collection,                     */
	0x05, 0x0D,         /*  Usage Page (Digitizer),             */
	0x09, 0x02,         /*  Usage (Pen),                        */
	0xA1, 0x01,         /*  Collection (Application),           */
	0x85, 0x10,         /*      Report ID (16),                 */
	0x09, 0x20,         /*      Usage (Stylus),                 */
	0xA0,               /*      Collection (Physical),          */
	0x14,               /*          Logical Minimum (0),        */
	0x25, 0x01,         /*          Logical Maximum (1),        */
	0x75, 0x01,         /*          Report Size (1),            */
	0x09, 0x42,         /*          Usage (Tip Switch),         */
	0x09, 0x44,         /*          Usage (Barrel Switch),      */
	0x09, 0x46,         /*          Usage (Tablet Pick),        */
	0x95, 0x03,         /*          Report Count (3),           */
	0x81, 0x02,         /*          Input (Variable),           */
	0x95, 0x04,         /*          Report Count (4),           */
	0x81, 0x03,         /*          Input (Constant, Variable), */
	0x09, 0x32,         /*          Usage (In Range),           */
	0x95, 0x01,         /*          Report Count (1),           */
	0x81, 0x02,         /*          Input (Variable),           */
	0x75, 0x10,         /*          Report Size (16),           */
	0x95, 0x01,         /*          Report Count (1),           */
	0xA4,               /*          Push,                       */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x55, 0xFD,         /*          Unit Exponent (-3),         */
	0x65, 0x13,         /*          Unit (Inch),                */
	0x34,               /*          Physical Minimum (0),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x46, 0x70, 0x17,   /*          Physical Maximum (6000),    */
	0x26, 0x00, 0x3C,   /*          Logical Maximum (15360),    */
	0x81, 0x02,         /*          Input (Variable),           */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x46, 0xA0, 0x0F,   /*          Physical Maximum (4000),    */
	0x26, 0x00, 0x28,   /*          Logical Maximum (10240),    */
	0x81, 0x02,         /*          Input (Variable),           */
	0xB4,               /*          Pop,                        */
	0x09, 0x30,         /*          Usage (Tip Pressure),       */
	0x26, 0xFF, 0x03,   /*          Logical Maximum (1023),     */
	0x81, 0x02,         /*          Input (Variable),           */
	0xC0,               /*      End Collection,                 */
	0xC0,               /*  End Collection                      */
	0x05, 0x0C,         /*  Usage Page (Consumer),              */
	0x09, 0x01,         /*  Usage (Consumer Control),           */
	0xA1, 0x01,         /*  Collection (Application),           */
	0x85, 0x12,         /*      Report ID (18),                 */
	0x14,               /*      Logical Minimum (0),            */
	0x25, 0x01,         /*      Logical Maximum (1),            */
	0x75, 0x01,         /*      Report Size (1),                */
	0x95, 0x04,         /*      Report Count (4),               */
	0x0A, 0x79, 0x02,   /*      Usage (AC Reकरो Or Repeat),      */
	0x0A, 0x1A, 0x02,   /*      Usage (AC Unकरो),                */
	0x0A, 0x2D, 0x02,   /*      Usage (AC Zoom In),             */
	0x0A, 0x2E, 0x02,   /*      Usage (AC Zoom Out),            */
	0x81, 0x02,         /*      Input (Variable),               */
	0x95, 0x34,         /*      Report Count (52),              */
	0x81, 0x03,         /*      Input (Constant, Variable),     */
	0xC0                /*  End Collection                      */
पूर्ण;

अटल __u8 *kye_consumer_control_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize, पूर्णांक offset, स्थिर अक्षर *device_name) अणु
	/*
	 * the fixup that need to be करोne:
	 *   - change Usage Maximum in the Consumer Control
	 *     (report ID 3) to a reasonable value
	 */
	अगर (*rsize >= offset + 31 &&
	    /* Usage Page (Consumer Devices) */
	    rdesc[offset] == 0x05 && rdesc[offset + 1] == 0x0c &&
	    /* Usage (Consumer Control) */
	    rdesc[offset + 2] == 0x09 && rdesc[offset + 3] == 0x01 &&
	    /*   Usage Maximum > 12287 */
	    rdesc[offset + 10] == 0x2a && rdesc[offset + 12] > 0x2f) अणु
		hid_info(hdev, "fixing up %s report descriptor\n", device_name);
		rdesc[offset + 12] = 0x2f;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल __u8 *kye_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_KYE_ERGO_525V:
		/* the fixups that need to be करोne:
		 *   - change led usage page to button क्रम extra buttons
		 *   - report size 8 count 1 must be size 1 count 8 क्रम button
		 *     bitfield
		 *   - change the button usage range to 4-7 क्रम the extra
		 *     buttons
		 */
		अगर (*rsize >= 75 &&
			rdesc[61] == 0x05 && rdesc[62] == 0x08 &&
			rdesc[63] == 0x19 && rdesc[64] == 0x08 &&
			rdesc[65] == 0x29 && rdesc[66] == 0x0f &&
			rdesc[71] == 0x75 && rdesc[72] == 0x08 &&
			rdesc[73] == 0x95 && rdesc[74] == 0x01) अणु
			hid_info(hdev,
				 "fixing up Kye/Genius Ergo Mouse "
				 "report descriptor\n");
			rdesc[62] = 0x09;
			rdesc[64] = 0x04;
			rdesc[66] = 0x07;
			rdesc[72] = 0x01;
			rdesc[74] = 0x08;
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_KYE_EASYPEN_I405X:
		अगर (*rsize == EASYPEN_I405X_RDESC_ORIG_SIZE) अणु
			rdesc = easypen_i405x_rdesc_fixed;
			*rsize = माप(easypen_i405x_rdesc_fixed);
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_KYE_MOUSEPEN_I608X:
		अगर (*rsize == MOUSEPEN_I608X_RDESC_ORIG_SIZE) अणु
			rdesc = mousepen_i608x_rdesc_fixed;
			*rsize = माप(mousepen_i608x_rdesc_fixed);
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_KYE_MOUSEPEN_I608X_V2:
		अगर (*rsize == MOUSEPEN_I608X_V2_RDESC_ORIG_SIZE) अणु
			rdesc = mousepen_i608x_v2_rdesc_fixed;
			*rsize = माप(mousepen_i608x_v2_rdesc_fixed);
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_KYE_EASYPEN_M610X:
		अगर (*rsize == EASYPEN_M610X_RDESC_ORIG_SIZE) अणु
			rdesc = easypen_m610x_rdesc_fixed;
			*rsize = माप(easypen_m610x_rdesc_fixed);
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_KYE_EASYPEN_M406XE:
		अगर (*rsize == EASYPEN_M406XE_RDESC_ORIG_SIZE) अणु
			rdesc = easypen_m406xe_rdesc_fixed;
			*rsize = माप(easypen_m406xe_rdesc_fixed);
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_KYE_PENSKETCH_M912:
		अगर (*rsize == PENSKETCH_M912_RDESC_ORIG_SIZE) अणु
			rdesc = pensketch_m912_rdesc_fixed;
			*rsize = माप(pensketch_m912_rdesc_fixed);
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_GENIUS_GILA_GAMING_MOUSE:
		rdesc = kye_consumer_control_fixup(hdev, rdesc, rsize, 104,
					"Genius Gila Gaming Mouse");
		अवरोध;
	हाल USB_DEVICE_ID_GENIUS_GX_IMPERATOR:
		rdesc = kye_consumer_control_fixup(hdev, rdesc, rsize, 83,
					"Genius Gx Imperator Keyboard");
		अवरोध;
	हाल USB_DEVICE_ID_GENIUS_MANTICORE:
		rdesc = kye_consumer_control_fixup(hdev, rdesc, rsize, 104,
					"Genius Manticore Keyboard");
		अवरोध;
	पूर्ण
	वापस rdesc;
पूर्ण

/**
 * kye_tablet_enable() - Enable fully-functional tablet mode by setting a special feature report.
 *
 * @hdev:	HID device
 *
 * The specअगरic report ID and data were discovered by snअगरfing the
 * Winकरोws driver traffic.
 */
अटल पूर्णांक kye_tablet_enable(काष्ठा hid_device *hdev)
अणु
	काष्ठा list_head *list;
	काष्ठा list_head *head;
	काष्ठा hid_report *report;
	__s32 *value;

	list = &hdev->report_क्रमागत[HID_FEATURE_REPORT].report_list;
	list_क्रम_each(head, list) अणु
		report = list_entry(head, काष्ठा hid_report, list);
		अगर (report->id == 5)
			अवरोध;
	पूर्ण

	अगर (head == list) अणु
		hid_err(hdev, "tablet-enabling feature report not found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (report->maxfield < 1 || report->field[0]->report_count < 7) अणु
		hid_err(hdev, "invalid tablet-enabling feature report\n");
		वापस -ENODEV;
	पूर्ण

	value = report->field[0]->value;

	value[0] = 0x12;
	value[1] = 0x10;
	value[2] = 0x11;
	value[3] = 0x12;
	value[4] = 0x00;
	value[5] = 0x00;
	value[6] = 0x00;
	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक kye_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err;
	पूर्ण

	चयन (id->product) अणु
	हाल USB_DEVICE_ID_KYE_EASYPEN_I405X:
	हाल USB_DEVICE_ID_KYE_MOUSEPEN_I608X:
	हाल USB_DEVICE_ID_KYE_MOUSEPEN_I608X_V2:
	हाल USB_DEVICE_ID_KYE_EASYPEN_M610X:
	हाल USB_DEVICE_ID_KYE_EASYPEN_M406XE:
	हाल USB_DEVICE_ID_KYE_PENSKETCH_M912:
		ret = kye_tablet_enable(hdev);
		अगर (ret) अणु
			hid_err(hdev, "tablet enabling failed\n");
			जाओ enabling_err;
		पूर्ण
		अवरोध;
	हाल USB_DEVICE_ID_GENIUS_MANTICORE:
		/*
		 * The manticore keyboard needs to have all the पूर्णांकerfaces
		 * खोलोed at least once to be fully functional.
		 */
		अगर (hid_hw_खोलो(hdev))
			hid_hw_बंद(hdev);
		अवरोध;
	पूर्ण

	वापस 0;
enabling_err:
	hid_hw_stop(hdev);
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id kye_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE, USB_DEVICE_ID_KYE_ERGO_525V) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_I405X) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE,
				USB_DEVICE_ID_KYE_MOUSEPEN_I608X) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE,
				USB_DEVICE_ID_KYE_MOUSEPEN_I608X_V2) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_M610X) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE,
				USB_DEVICE_ID_KYE_EASYPEN_M406XE) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE,
				USB_DEVICE_ID_GENIUS_GILA_GAMING_MOUSE) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE,
				USB_DEVICE_ID_GENIUS_GX_IMPERATOR) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE,
				USB_DEVICE_ID_GENIUS_MANTICORE) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_KYE,
				USB_DEVICE_ID_KYE_PENSKETCH_M912) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, kye_devices);

अटल काष्ठा hid_driver kye_driver = अणु
	.name = "kye",
	.id_table = kye_devices,
	.probe = kye_probe,
	.report_fixup = kye_report_fixup,
पूर्ण;
module_hid_driver(kye_driver);

MODULE_LICENSE("GPL");
